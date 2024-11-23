#!/usr/bin/env bash

platform="platforms/cloud_batch_platform.xml"

for recipe in workflows/* ; do
    my_recipe=$(basename "$recipe")
    if [[ "$my_recipe" =~ ^blast-workflow-[0-9]+-[0-9]+\.json$ ]]; then
        execute_recipe="workflows/$my_recipe"
        $(build/my-wrench-simulator "$platform" "$execute_recipe" --wrench-energy-simulation)
    fi
done

echo "All recipes have been executed"

exit