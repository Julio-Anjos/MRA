MRA++ 
===

MapReduce with Adapted Algorithms to Heterogeneous Environments, is based on MRSG Project.

To run the example, follow these steps:

1) Make sure you have installed SimGrid (3.11  recommended).
   (http://simgrid.gforge.inria.fr/)

2) Inside MRA's root and examples directories, edit the Makefiles and change
   the INSTALL_PATH variable to match your SimGrid installation path
   (e.g. /usr).

3) Compile MRA with 'make' in the command line, and then do the same for the example.

4) Execute the example (./run.sh).


Into examples folder, has platform samples. Install the python before for running,  in order to create another platforms.

Syntax: platform_file.xml num_workers cores_per_node_min[:numCores_max] cpu_min[:cpu_max] latency_min[:latency_max] bw_min[:bw_max]'
	
	./create-mra-plat.py platform_file.xml 5 2 1e9 1e-4 1.25e8'
	
	Or: ./create-mra-plat.py platform_file.xml 10 2 4e9:7e9 1e-4 1.25e8
	Or: ./create-mra-plat.py platform_file.xml 10 2 7e9 1e-4 1.25e6:1.25e8
	Or: ./create-mra-plat.py platform_file.xml 10 2 7e9 1e-4:1e-2 1.25e8
	Or: ./create-mra-plat.py platform_file.xml 10 2 7e9 1e-4:1e-2 1.25e6:1.25e8
	Or: ./create-mra-plat.py platform_file.xml 10 2 4e9:7e9 1e-4:1e-2 1.25e6:1.25e8

  ./create-mra-depoly.py platform_file.xml
  
   
 After you need to change user functions on hello.c


