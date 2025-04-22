#!/usr/bin/env bash

platform="platforms/apollo_2000_platform.xml"

echo "Escolha o workflow para executar:"
echo "1 - blast (simula a execução de buscas em bases de dados biológicas.)"
echo "2 - montage (realiza a montagem de mosaicos de imagens astronômicas.)"
read -p "Digite 1 ou 2: " escolha

case $escolha in
    1)
        workflow_dir="workflows/blast"
        ;;
    2)
        workflow_dir="workflows/montage"
        ;;
    *)
        echo "Opção inválida. Saindo..."
        exit 1
        ;;
esac

for recipe in "$workflow_dir"/* ; do
    my_recipe=$(basename "$recipe")
    if [[ "$my_recipe" =~ \.json$ ]]; then
        execute_recipe="$workflow_dir/$my_recipe"
        ./build/my-wrench-simulator "$platform" "$execute_recipe" --wrench-energy-simulation
    fi
done

echo "Todos os recipes foram executados."

exit
