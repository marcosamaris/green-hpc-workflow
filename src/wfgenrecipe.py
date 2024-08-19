import pathlib
from wfcommons.wfchef.recipes import MontageRecipe
from wfcommons import WorkflowGenerator

try:
    amount_recipe = int(input('Type amount of recipe: '))
except ValueError:
    print('Please enter a valid integer.')
    exit(1)


MIN_TASKS = 60

output_dir = pathlib.Path(__file__).parent.parent / 'data'
output_dir.mkdir(parents=True, exist_ok=True)

for amount_tasks in range(MIN_TASKS, amount_recipe + MIN_TASKS):
    generator = WorkflowGenerator(MontageRecipe.from_num_tasks(amount_tasks))
    workflows = generator.build_workflows(1)
    
    for index, workflow in enumerate(workflows):
        output_path = output_dir / f'montage-workflow-{amount_tasks}-{index}.json'
        try:
            workflow.write_json(output_path)
        except Exception as e:
            print(f"Error writing {output_path}: {e}")

