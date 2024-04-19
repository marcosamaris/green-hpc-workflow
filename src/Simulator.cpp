
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
#include <wrench-dev.h>

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

    /* List of storage service */
    std::set<std::shared_ptr<wrench::storageService>> storage_service;

    std::cerr << "Instantiating a SimpleStorageService on WMSHost " << std::endl;
    auto storage_service = simulation->add(wrench::SimpleStorageService::createSimpleStorageService({"WMSHost"}, {"/"}));
    storage_service.insert(storage_service);

    
    /* Instantiating the simulated platform */
    simulation->instantiatePlatform(argv[1]);

    /* Instantiate a storage service on the platform */
    auto storage_service = simulation->add(wrench::SimpleStorageService::createSimpleStorageService(
            "StorageHost", {"/"}, {}, {}));

    /* Instantiate a bare-metal compute service on the platform */
    auto baremetal_service = simulation->add(new wrench::BareMetalComputeService(
            "ComputeHost", {"ComputeHost"}, "", {}, {}));

    /* Instantiate an execution controller */
    auto controller = simulation->add(
            new wrench::Controller(baremetal_service, storage_service, "UserHost"));

    /* Launch the simulation */
    simulation->launch();

    return 0;
}
