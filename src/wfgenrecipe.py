import pathlib
from wfcommons.wfchef.recipes import MontageRecipe
from wfcommons import WorkflowGenerator

amount_recipe = int(input('Type of amount of recipe: '))

try:
    if amount_recipe > 59:
        for amount_tasks in range(60, amount_recipe, 1):
            generator = WorkflowGenerator(MontageRecipe.from_num_tasks(amount_tasks))
            workflows = generator.build_workflows(1)
            
            for index, workflow in enumerate(workflows):
                workflow.write_json(pathlib.Path(f'montage-workflow-{amount_tasks}-{index}.json'))
    else:
        print('Amount of recipes must be greater than 0!')
finally:
    print('DONE!')
