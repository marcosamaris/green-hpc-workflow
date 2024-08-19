ls
cd build/
ls
cmake ..
make
./my-wrench-simulator ../data/cloud_batch_platform.xml ../data/montage-workflow-60-0.json 
./my-wrench-simulator ../data/cloud_batch_platform.xml ../data/montage-workflow-60-0.json --wrench-energy-simulation
./my-wrench-simulator ../data/cloud_batch_platform.xml ../data/montage-workflow-61-0.json --wrench-energy-simulation
ls
