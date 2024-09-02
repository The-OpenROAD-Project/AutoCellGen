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

### Installing with CMake

Use the following commands to checkout the git repository and build the Csyn-fp library and excutable.

```
git clone [TODO : create github repository]
cd AutoCellGen
cd MAKE
cd PLACE
cd csyn_fp
mkdir build
cd build
cmake ..
make
```

If you make changes to `CMakeLists.txt` you may need to clean out existing CMake cached variable values by deleting all of the files in the build directory.





## Generating transistor placement

### Placement setups

To generate placements, input parameter setups are required.

Input parameters can be modified in the file noted below.

```
./AutoCellGen/DATA/input/placement_file.style  
```

Each input parameter is explained by comments. Please modify the input parameters according to the comments.



### Generating transistor placement

Use the following commands to execute csyn-fp to  generate transistor placement.

```
cd AutoCellGen
cd MAKE
cd PLACE
./1.run_csyn_fp ${netlist_file}
./:update_and_clear
```



An example of a netlist file is provided below. You can use this file as an input example.

Netlist files we provided are from https://github.com/The-OpenROAD-Project/asap7

```
ASAP7 6-track standard cell library netlist : ./AutoCellGen/DATA/input/asap7sc6t.sp
ASAP7 7.5-track standard cell library netlist : ./AutoCellGen/DATA/input/asap7sc7p5t.sp
```



Output files are saved in the folder noted below.

**placement file**

```
./AutoCellGen/MAKE/PLACE/output/placement
```

**IO net file**

```
./AutoCellGen/MAKE/PLACE/output/IOnet
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





## Authors

- SNUCAD, Seoul National University
- Kyeonghyeon Baek, Sehyeon Chung, Handong Cho, Hyunbae Seo, Kyu-myung Choi, Taewhan Kim

## References

- K. Baek and T. Kim, "Simultaneous Transistor Folding and Placement in Standard Cell Layout Synthesis", [PDF](./DOC/Simultaneous_Transistor_Folding_and_Placement_in_Standard_Cell_Layout_Synthesis.pdf), IEEE/ACM International Conference on Computer Aided Design, 2021.

## License

BSD 3-Clause License. See LICENSE(./LICENSE) file.

