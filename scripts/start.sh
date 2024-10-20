#!/usr/bin/env bash

platform="../platforms/cloud_batch_platform.xml"

for recipe in ../datas/* ; do
    my_recipe=$(basename "$recipe")
    if [[ "$my_recipe" =~ ^montage-workflow-[0-9]+-[0-9]+\.json$ ]]; then
        execute_recipe="../datas/$my_recipe"
        $(./../build/my-wrench-simulator "$platform" "$execute_recipe" --wrench-energy-simulation)
    fi
done

echo "All recipes have been executed"

exit