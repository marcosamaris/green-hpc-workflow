# #!/usr/bin/env bash

# platform="platforms/apollo_2000_platform.xml"

# echo "Escolha o workflow para executar:"
# echo "1 - blast (simula a execução de buscas em bases de dados biológicas.)"
# echo "2 - montage (realiza a montagem de mosaicos de imagens astronômicas.)"
# read -p "Digite 1 ou 2: " escolha

# case $escolha in
#     1)
#         workflow_dir="workflows/blast"
#         ;;
#     2)
#         workflow_dir="workflows/montage"
#         ;;
#     *)
#         echo "Opção inválida. Saindo..."
#         exit 1
#         ;;
# esac

# for recipe in "$workflow_dir"/* ; do
#     my_recipe=$(basename "$recipe")
#     if [[ "$my_recipe" =~ \.json$ ]]; then
#         execute_recipe="$workflow_dir/$my_recipe"
#         ./build/my-wrench-simulator "$platform" "$execute_recipe" --wrench-energy-simulation
#     fi
# done

# echo "Todos os recipes foram executados."

# exit


#!/usr/bin/env bash

#!/usr/bin/env bash

#!/usr/bin/env bash

platform="platforms/apollo_2000_platform.xml"
workflow_dir="workflows"

echo "Executando todos os arquivos .json encontrados recursivamente na pasta '$workflow_dir' em ordem alfabética:"

find "$workflow_dir" -type f -name "*.json" -print0 | sort -z | while IFS= read -r -d $'\0' recipe_path; do
    recipe_file=$(basename "$recipe_path")
    recipe_dir=$(dirname "$recipe_path")

    echo "  - Executando recipe: '$recipe_file' na pasta: '$recipe_dir'"
    ./build/my-wrench-simulator --wrench-commport-pool-size=20000 "$platform" "$recipe_path" --wrench-energy-simulation

    if [ $? -ne 0 ]; then
        echo "    Erro ao executar o recipe '$recipe_file' na pasta: '$recipe_dir'."
    fi
done

echo ""
echo "------------------------------------------------------------------"
echo "Fim da execução dos recipes encontrados recursivamente em '$workflow_dir'."

exit 0