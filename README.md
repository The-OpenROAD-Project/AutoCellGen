# AutoCellGen

AutoCellGen is a standard cell layout generator that encompasses netlist, transistor placement, routing, and GDS flow. As a standalone executable, it can be used to generate a standard cell library.



## Csyn-fp (netlist to transistor placement)

Csyn-fp generates transistor placements from cell netlists. As a standalone executable, it can convert netlist files (.cdl / .sp files) into transistor placements.

This program is based on the content of the following paper.

Baek, Kyeonghyeon, and Taewhan Kim. "Simultaneous transistor folding and placement in standard cell layout synthesis." *2021 IEEE/ACM International Conference On Computer Aided Design (ICCAD)*. IEEE, 2021.



## Build

Csyn-fp is built with CMake.



### Prerequisites

The build dependency versions are shown below. Other versions may work, but these are the versions used for development.

```
Ubuntu   20.04
cmake    3.27.7        
gcc      11.4.0
```



### Z3 SMT solver

We use Z3 SMT solver to execute in-cell route process.

The github repository of Z3 SMT solver : https://github.com/Z3Prover/z3

The version we used are shown below.

```
Z3		4.8.11.0
```

To achieve the correct results, **you must use the exact version as we provided**. Other versions may cause errors. 



### Installing with CMake

Use the following commands to checkout the git repository and build the Csyn-fp library and executable.

**git clone & move to default directory**

```
git clone [TODO : create github repository]
cd AutoCellGen
cd MAKE
cd PLACE
cd csyn_fp
```



**build Z3 solver library**

We have included the Z3 solver library we used in the path below.

```
./AutoCellGen/MAKE/PLACE/csyn_fp/z3
```

You can directly generate the Z3 executable file using the command below.

```
cd z3
mkdir build
cmake ..
make
```

It is also available for download & build from the Z3 solver GitHub repository mentioned above.

If you download z3 from GitHub, you should place it in the `./AutoCellGen/MAKE/PLACE/csyn_fp` directory.



**build Csyn-fp library**

```
cd ../..
mkdir build
cd build
cmake ..
make
```

If you make changes to `CMakeLists.txt` you may need to clean out existing CMake cached variable values by deleting all of the files in the build directory.





## Run

### Placement setups

To generate placements, input parameter setups are required.

Input parameters can be modified in the file noted below.

```
./AutoCellGen/DATA/input/placement_file.style  
```

Each input parameter is explained by comments. Please modify the input parameters according to the comments.



### Generating transistor placement & Execute in-cell route

Use the following commands to execute csyn-fp to  generate transistor placement & execute in-cell route

```
cd AutoCellGen
cd MAKE
cd PLACE
./1.run_csyn_fp ${netlist_file}
```



An example of a netlist file is provided below. You can use this file as an input example.

Netlist file we provided is from https://github.com/The-OpenROAD-Project/asap7

```
ASAP7 7.5-track standard cell library netlist : ./AutoCellGen/DATA/input/asap7sc7p5t.sp
```



Output files are saved in the folder noted below.

**placement file**

```
./AutoCellGen/MAKE/PLACE/output/placement
```



**placement file Description**

The placement results are listed sequentially from the left column.

Here is the output file format.

```
-------- Solution 0 --------
[Column 1]
NMOS : ${NMOS_name}(${fin_number}) [${source_net} ${gate_net} ${drain_net}], PMOS : ${PMOS_name}(${fin_number}) [${source_net} ${gate_net} ${drain_net}]
...

```

The placement file output example is represented below.

```
-------- Solution 0 --------
[Column 1]
NMOS : MMN0(2) [EN SE VSS], PMOS : MMP(2) [VDD SE net22]
...

```



**IO net file**

```
./AutoCellGen/MAKE/PLACE/output/IOnet
```



**GDS file**

```
./AutoCellGen/MAKE/PLACE/output/gds
```

Note that SNUCell1.0 may produce some cells with design rule violation. In such case, a manual modification is required.
A next version will fix this problem.





## Authors

- SNUCAD, Seoul National University
- Kyeonghyeon Baek, Sehyeon Chung, Handong Cho, Hyunbae Seo, Kyu-myung Choi, Taewhan Kim
