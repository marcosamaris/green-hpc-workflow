#!/usr/bin/env bash

echo "host, cores, total_tasks, tasks_completed, failed_tasks, computation_time input_time, output_time, average_computation_time, total_energy_consumption, completed_time"

platform="../platforms/cloud_batch_platform.xml"

for recipe in ../datas/* ; do
    my_recipe=$(basename "$recipe")
    if [[ "$my_recipe" =~ ^montage-workflow-[0-9]+-[0-9]+\.json$ ]]; then
        execute_recipe="../datas/$my_recipe"
        $(./../build/my-wrench-simulator "$platform" "$execute_recipe" --wrench-energy-simulation)
    fi
done

exit