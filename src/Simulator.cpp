
/**
 * Copyright (c) 2017-2021. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/**
 ** This is the main function for a WRENCH simulator. The simulator takes
 ** a input an XML platform description file. It generates a workflow with
 ** a simple diamond structure, instantiates a few services on the platform, and
 ** starts an execution controller to execute the workflow using these services
 ** using a simple greedy algorithm.
 **/

#include <iostream>
#include <stdexcept>
#include <wrench-dev.h>
#include <wrench/services/file_registry/FileRegistryService.h>

#include "Controller.h"
#include "wrench/tools/wfcommons/WfCommonsWorkflowParse.h"

/**
 * @brief The Simulator's main function
 *
 * @param argc: argument count
 * @param argv: argument array
 * @return 0 on success, non-zero otherwise
 */
int main(int argc, char **argv) {

    /* Create a WRENCH simulation object */
    auto simulation = wrench::Simulation::createSimulation();

    /* Initialize the simulation */
    simulation->init(&argc, argv);

    /* Parsing of the command-line arguments */
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <xml platform file> [--log=controller.threshold=info | --wrench-full-log]" << std::endl;
        exit(1);
    }

    /* The first argument is the platform description file, written in XML following the SimGrid-defined DTD */
    char *platform_file = argv[1];
    /* The second argument is the workflow description file, written in JSON using WfCommons's WfFormat format */
    char *workflow_file = argv[2];

    /* Reading and parsing the workflow description file to create a wrench::workflow object */
    std::cerr << "Loading workflow..." << std::endl;
    std::shared_ptr<wrench::Workflow> workflow;
    workflow = wrench::WfCommonsWorkflowParse::CreateWorkflowFromJSON(workflow_file, "100Gf", true);
    std::cerr << "The workflow has " << workflow->getNumberOfTasks() << " tasks " << std::endl;
    std::cerr.flush();

    /* Reading and parsing the platform description file to instantiate a simulated platform */
    std::cerr << "Instaling SimGrid platform..." << std::endl;
    simulation->instantiatePlatform(platform_file);

    /* List of storage services */
    std::set<std::shared_ptr<wrench::StorageService>> storage_services;

    std::cerr << "Instantiating a SimpleStorageService on WMSHost " << std::endl;
    auto storage_service = simulation->add(wrench::SimpleStorageService::createSimpleStorageService({"WMSHost"}, {"/"}));
    storage_services.insert(storage_service);

    /* List of computer services */
    std::set<std::shared_ptr<wrench::ComputeService>> compute_services;

		/* Configures a batch computing service */
    std::shared_ptr<wrench::BatchComputeService> batch_compute_service;

    #ifndef ENABLE_BATSCHED
        std::string scheduling_algorithm = "conservative_bf_core_level";
    #else
        std::string scheduling_algorithm = "conservative_bf";
    #endif
        try {
          batch_compute_service = simulation->add(new wrench::BatchComputeService(
						{"BatchHeadNode"}, {{"BatchNode1"}, {"BatchNode2"}}, "",
						{{wrench::BatchComputeServiceProperty::BATCH_SCHEDULING_ALGORITHM, scheduling_algorithm}},
						{{wrench::BatchComputeServiceMessagePayload::STOP_DAEMON_MESSAGE_PAYLOAD, 2048}}));
        } catch (std::invalid_argument &e) {
					std::cerr << "Error: " << e.what() << std::endl;
					std::exit(1);
				}
    
		/* Instantiating the WMS for executing workflow */	
		std::cerr << "Instatiating a WMS on WMSHost..." << std::endl;
		auto wms = simulation->add(
				new wrench::SimpleWMS(workflow, batch_compute_service, storage_service, {"WMSHost"}));

		/* Instantiate a file registry service to be started on some host */
		std::string file_registry_service_host = hostname_list[(hostname_list.size() > 2) ? 1 : 0];
		std::cerr << "Instantiating a FileRegistryService on " << file_registry_service_host << "..." << std::endl;
		auto file_registry_service = simulation->add(new wrench::FileRegistryService(file_registry_service_host));

		std:cerr << "Staging input files..." << std::endl;
		for (auto const &f: workflow->getInputFiles()) {
			try {
				simulation->stageFile(f, storage_services);
			} catch (std::runtime_error &e) {
				std::cerr << "Exception: " << e.what() << std::endl;
				return 0;
			}
		}

		/* Enable some output Workflow Task time stamps */
		simulation->getOutput().enableWorkflowTaskTimestamps(true);
		/* Enable some output Energy time stamps */
		simulation->getOutput().enableEnergyTimestamps(true);

    /* Launch the simulation */
		std::cerr << "Launching the Simulation..." << std::endl;
		try {
    	simulation->launch();
		} catch (std::runtime_error &e) {
			std::cerr << "Exception: " << e.what() << std::endl;
			return 0;
		}
		std::cerr << "Simulation Done!" << std::endl;
		std::cerr << "Workflow completed at time: " << workflow->getCompletionDate() << std::endl;

		simulation->getOutput().dumpWorkflowGraphJSON(workflow, "/temp/workflow.json", true);

    return 0;
}
