.SUBCKT A2O1A1Ixp33_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM7 net06 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 Y C net06 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net015 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net06 A1 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 Y C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 Y B net2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net2 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net2 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT A2O1A1Ixp5_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM9 Y C net039 VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net045 A1 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM4 net039 A2 net045 VSS nmos_rvt w=108.00n l=20n nfin=4
MM6 net039 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net038 A1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 Y B net038 VDD pmos_rvt w=27.0n l=20n nfin=1
MM1 net038 A2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 Y C VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT A2O1A1O1Ixp33_ASAP7_6t_R A1 A2 B C D VDD VSS Y
MM5 net4 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net15 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net4 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 Y D net15 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net15 B net4 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 Y D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net25 A2 net12 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net12 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 VSS A1 net25 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net12 C Y VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AND2x2_ASAP7_6t_R A B VDD VSS Y
MM4 Y net10 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM1 net10 B VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM0 net10 A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM5 Y net10 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM3 net20 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net10 B net20 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AND2x4_ASAP7_6t_R A B VDD VSS Y
MM4 Y net9 VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM1 net9 B VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM0 net9 A VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM5 Y net9 VSS VSS nmos_rvt w=216.00n l=20n nfin=8
MM3 net19 A VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM2 net9 B net19 VSS nmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT AND2x6_ASAP7_6t_R A B VDD VSS Y
MM4 Y net9 VDD VDD pmos_rvt w=324.00n l=20n nfin=12
MM1 net9 B VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM0 net9 A VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM5 Y net9 VSS VSS nmos_rvt w=324.00n l=20n nfin=12
MM3 net19 A VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM2 net9 B net19 VSS nmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT AND3x1_ASAP7_6t_R A B C VDD VSS Y
MM6 Y net61 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net61 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net61 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net61 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y net61 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net61 A net72 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net72 B net71 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net71 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AND3x2_ASAP7_6t_R A B C VDD VSS Y
MM6 Y net61 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM5 net61 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net61 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net61 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y net61 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM0 net61 A net72 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net72 B net71 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net71 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AND3x4_ASAP7_6t_R A B C VDD VSS Y
MM6 Y net83 VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM5 net83 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net83 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net83 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y net83 VSS VSS nmos_rvt w=216.00n l=20n nfin=8
MM0 net83 A net89 VSS nmos_rvt w=108.00n l=20n nfin=4
MM1 net89 B net90 VSS nmos_rvt w=108.00n l=20n nfin=4
MM2 net90 C VSS VSS nmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT AND4x1_ASAP7_6t_R A B C D VDD VSS Y
MM8 Y net12 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net12 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net12 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net12 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net12 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 Y net12 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 pd3 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 pd2 B pd3 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 pd1 C pd2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net12 D pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AND4x2_ASAP7_6t_R A B C D VDD VSS Y
MM5 net33 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net33 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net33 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net33 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y net33 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM9 net15 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net16 C net15 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net17 B net16 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net33 A net17 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y net33 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT AND5x1_ASAP7_6t_R A B C D E VDD VSS Y
MM11 Y net011 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net29 E VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net30 D net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net024 B net023 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net011 A net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net023 C net30 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net011 E VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net011 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net011 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net011 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y net011 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net011 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AND5x2_ASAP7_6t_R A B C D E VDD VSS Y
MM1 Y net14 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM9 net14 E VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net14 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net14 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net14 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net14 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 Y net14 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM6 net33 E VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net34 D net33 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net32 B net35 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net14 A net32 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net35 C net34 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO211x1_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM7 Y net95 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 net95 A1 net100 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net95 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net95 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net100 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net99 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net96 C net99 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 Y net95 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net95 A2 net96 VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 net95 A1 net96 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO211x2_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM8 Y net014 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM4 net014 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net014 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net23 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 net014 A1 net23 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 Y net014 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM6 net016 C net22 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net22 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net014 A2 net016 VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 net014 A1 net016 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO21x1_ASAP7_6t_R A1 A2 B VDD VSS Y
MM3 net043 A1 net046 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 Y net043 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net046 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net043 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 VDD B net042 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 Y net043 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net042 A1 net043 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net042 A2 net043 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO21x2_ASAP7_6t_R A1 A2 B VDD VSS Y
MM7 Y net16 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM4 net16 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net16 A1 net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net29 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 Y net16 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM5 net18 A2 net16 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 VDD B net18 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net18 A1 net16 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO221x1_ASAP7_6t_R A1 A2 B1 B2 C VDD VSS Y
MM4 Y yn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM28 yn C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM27 net23 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM26 yn B1 net23 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 yn A1 net24 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net24 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y yn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 s1 C s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM32 s2 B2 yn VDD pmos_rvt w=54.0n l=20n nfin=2
MM31 s1 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM30 s2 B1 yn VDD pmos_rvt w=54.0n l=20n nfin=2
MM29 s1 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO221x2_ASAP7_6t_R A1 A2 B1 B2 C VDD VSS Y
MM4 Y yn VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM28 yn C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM27 net23 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM26 yn B1 net23 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 yn A1 net24 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net24 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y yn VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM1 s1 C s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM32 s2 B2 yn VDD pmos_rvt w=54.0n l=20n nfin=2
MM31 s1 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM30 s2 B1 yn VDD pmos_rvt w=54.0n l=20n nfin=2
MM29 s1 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO222x1_ASAP7_6t_R A1 A2 B1 B2 C1 C2 VDD VSS Y
MM9 Y net118 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 net118 B1 net124 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net118 C1 net123 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net118 A1 net125 VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 net124 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net123 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net125 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net115 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net115 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net114 B2 net115 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net114 B1 net115 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 Y net118 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net118 C2 net114 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net118 C1 net114 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO222x2_ASAP7_6t_R A1 A2 B1 B2 C1 C2 VDD VSS Y
MM8 Y net23 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM5 net23 C2 net17 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net17 B2 net18 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net18 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net23 C1 net17 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net17 B1 net18 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net18 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net37 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 net23 B1 net37 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net36 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net23 C1 net36 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 Y net23 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM7 net38 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net23 A1 net38 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO22x1_ASAP7_6t_R A1 A2 B1 B2 VDD VSS Y
MM5 net18 B2 net13 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net18 B1 net13 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net13 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y net18 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net13 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net29 B1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net30 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net18 B2 net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net18 A2 net30 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y net18 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO22x2_ASAP7_6t_R A1 A2 B1 B2 VDD VSS Y
MM5 net18 B2 net13 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net18 B1 net13 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net13 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y net18 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM2 net13 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net29 B1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net30 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net18 B2 net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net18 A2 net30 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y net18 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT AO311x1_ASAP7_6t_R A1 A2 A3 B C VDD VSS Y
MM11 Y net111 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net111 A1 net114 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net114 A2 net115 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net111 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net111 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net115 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 Y net111 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net110 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net110 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net110 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net116 B net110 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net111 C net116 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO311x2_ASAP7_6t_R A1 A2 A3 B C VDD VSS Y
MM11 Y net117 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM2 net117 A1 net120 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net120 A2 net121 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net117 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net117 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net121 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 Y net117 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM10 net116 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net116 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net116 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net122 B net116 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net117 C net122 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO31x1_ASAP7_6t_R A1 A2 A3 B VDD VSS Y
MM6 net055 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y net056 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net055 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net056 B net055 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net055 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net059 A2 net060 VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net056 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net060 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net056 A1 net059 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y net056 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO31x2_ASAP7_6t_R A1 A2 A3 B VDD VSS Y
MM0 Y net18 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM5 net18 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net29 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net18 A1 net30 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net30 A2 net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 Y net18 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM9 net18 B net23 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net23 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net23 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net23 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO321x1_ASAP7_6t_R A1 A2 A3 B1 B2 C VDD VSS Y
MM16 Y net127 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net127 B2 net132 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 net127 A1 net133 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net133 A2 net134 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net127 C VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 net132 B1 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 net134 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 Y net127 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net126 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net126 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net126 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net125 C net126 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net127 B2 net125 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net127 B1 net125 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO321x2_ASAP7_6t_R A1 A2 A3 B1 B2 C VDD VSS Y
MM16 Y net131 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM11 net131 B2 net136 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 net131 A1 net137 VSS nmos_rvt w=27.0n l=20n nfin=1
MM3 net137 A2 net138 VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 net131 C VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 net136 B1 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 net138 A3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM17 Y net131 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM10 net130 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net130 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net130 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net129 C net130 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net131 B2 net129 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net131 B1 net129 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO322x1_ASAP7_6t_R A1 A2 A3 B1 B2 C1 C2 VDD VSS Y
MM16 Y net25 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net50 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net25 C1 net50 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net51 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net25 B1 net51 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net52 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net49 A2 net52 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net25 A1 net49 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 Y net25 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 net27 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net25 C2 net53 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net53 B2 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net27 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net25 C1 net53 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net53 B1 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net27 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO322x2_ASAP7_6t_R A1 A2 A3 B1 B2 C1 C2 VDD VSS Y
MM16 Y net25 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM6 net50 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net25 C1 net50 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net51 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net25 B1 net51 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net52 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net49 A2 net52 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net25 A1 net49 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 Y net25 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM13 net27 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net25 C2 net53 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net53 B2 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net27 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net25 C1 net53 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net53 B1 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net27 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO32x1_ASAP7_6t_R A1 A2 A3 B1 B2 VDD VSS Y
MM21 Y net08 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net08 A1 net24 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net24 A2 net25 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net25 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 net26 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 net08 B1 net26 VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 Y net08 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net10 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net10 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net10 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 net08 B2 net10 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net08 B1 net10 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO32x2_ASAP7_6t_R A1 A2 A3 B1 B2 VDD VSS Y
MM21 Y net08 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM0 net08 A1 net24 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 net24 A2 net25 VSS nmos_rvt w=27.0n l=20n nfin=1
MM3 net25 A3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM18 net26 B2 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM13 net08 B1 net26 VSS nmos_rvt w=27.0n l=20n nfin=1
MM20 Y net08 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM1 net10 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net10 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net10 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 net08 B2 net10 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net08 B1 net10 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO331x1_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C VDD VSS Y
MM0 Y yb VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM23 net24 B3 net034 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 net034 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 net24 B2 net034 VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 net034 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM27 yb C net24 VDD pmos_rvt w=54.0n l=20n nfin=2
MM20 net24 B1 net034 VDD pmos_rvt w=54.0n l=20n nfin=2
MM24 net034 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y yb VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM22 yb C VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM19 net31 B3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM18 net32 B2 net31 VSS nmos_rvt w=27.0n l=20n nfin=1
MM17 yb B1 net32 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 n2 A3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM15 n1 A2 n2 VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 yb A1 n1 VSS nmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT AO331x2_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C VDD VSS Y
MM0 Y yb VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM23 net24 B3 net034 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 net034 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 net24 B2 net034 VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 net034 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM27 yb C net24 VDD pmos_rvt w=54.0n l=20n nfin=2
MM20 net24 B1 net034 VDD pmos_rvt w=54.0n l=20n nfin=2
MM24 net034 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y yb VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM22 yb C VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM19 net31 B3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM18 net32 B2 net31 VSS nmos_rvt w=27.0n l=20n nfin=1
MM17 yb B1 net32 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 n2 A3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM15 n1 A2 n2 VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 yb A1 n1 VSS nmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT AO332x1_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 VDD VSS Y
MM20 net053 B2 net57 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net035 A1 net55 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 Y net035 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net55 A2 net54 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net54 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 net59 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 net035 C1 net59 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net035 B1 net56 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net56 B2 net053 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net57 B3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net035 C1 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net035 C2 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 s1 B2 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM24 Y net035 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM17 s2 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 s2 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 s2 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 s1 B3 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 s1 B2 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 s1 B1 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO332x2_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 VDD VSS Y
MM20 net053 B2 net57 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net035 A1 net55 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 Y net035 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM1 net55 A2 net54 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net54 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 net59 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 net035 C1 net59 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net035 B1 net56 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net56 B2 net053 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net57 B3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net035 C1 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net035 C2 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 s1 B2 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM24 Y net035 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM17 s2 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 s2 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 s2 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 s1 B3 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 s1 B2 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 s1 B1 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO333x1_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 C3 VDD VSS Y
MM3 Y net40 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net40 C1 net55 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net55 C2 net54 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net54 C3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM19 net58 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 net59 A2 net58 VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 net40 A1 net59 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net40 B3 net56 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net56 B2 net57 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net57 B1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net40 A1 net22 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net40 A2 net22 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net40 A3 net22 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 Y net40 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM17 net24 C3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 net24 C2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 net24 C1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 net22 B3 net24 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net22 B2 net24 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net22 B1 net24 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO333x2_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 C3 VDD VSS Y
MM3 Y net40 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM0 net40 C1 net55 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net55 C2 net54 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net54 C3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM19 net58 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 net59 A2 net58 VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 net40 A1 net59 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net40 B3 net56 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net56 B2 net57 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net57 B1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net40 A1 net22 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net40 A2 net22 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net40 A3 net22 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 Y net40 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM17 net24 C3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 net24 C2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 net24 C1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 net22 B3 net24 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net22 B2 net24 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net22 B1 net24 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO33x1_ASAP7_6t_R A1 A2 A3 B1 B2 B3 VDD VSS Y
MM24 Y net122 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net122 B1 net124 VSS nmos_rvt w=27.0n l=20n nfin=1
MM7 net122 A1 net126 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 net124 B2 net123 VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 net126 A2 net125 VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 net123 B3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 net125 A3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 net114 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net114 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 net114 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net122 B3 net114 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net122 B2 net114 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net122 B1 net114 VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 Y net122 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AO33x2_ASAP7_6t_R A1 A2 A3 B1 B2 B3 VDD VSS Y
MM25 Y net020 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM6 net020 B3 net15 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net15 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net15 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net020 B2 net15 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net020 B1 net15 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 net15 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM24 Y net020 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM10 net020 B1 net39 VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 net022 B3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 net39 B2 net022 VSS nmos_rvt w=27.0n l=20n nfin=1
MM7 net020 A1 net40 VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 net024 A3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 net40 A2 net024 VSS nmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT AOI211xp25_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM20 Y C VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM3 Y B VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 Y A2 net32 VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 net32 A1 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM21 net17 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net17 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net34 B net17 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y C net34 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI211xp5_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM5 net047 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 Y A2 net047 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 Y C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM21 net042 A2 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM0 net042 A1 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM6 net046 B net042 VDD pmos_rvt w=108.00n l=20n nfin=4
MM7 Y C net046 VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT AOI21x1_ASAP7_6t_R A1 A2 B VDD VSS Y
MM4 Y B VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM3 Y A1 net29 VSS nmos_rvt w=108.00n l=20n nfin=4
MM2 net29 A2 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM5 net18 A2 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM0 Y B net18 VDD pmos_rvt w=108.00n l=20n nfin=4
MM1 net18 A1 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT AOI21xp25_ASAP7_6t_R A1 A2 B VDD VSS Y
MM4 Y B VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM3 Y A1 net29 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 net29 A2 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 net18 A2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM0 Y B net18 VDD pmos_rvt w=27.0n l=20n nfin=1
MM1 net18 A1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT AOI21xp5_ASAP7_6t_R A1 A2 B VDD VSS Y
MM4 Y B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y A1 net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net29 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net18 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 Y B net18 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net18 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI221xp25_ASAP7_6t_R A1 A2 B1 B2 C VDD VSS Y
MM28 Y C VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM27 net23 B2 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM26 Y B1 net23 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 Y A1 net24 VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 net24 A2 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 net012 C net16 VDD pmos_rvt w=54.0n l=20n nfin=2
MM32 net16 B2 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM31 net012 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM30 net16 B1 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM29 net012 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI221xp5_ASAP7_6t_R A1 A2 B1 B2 C VDD VSS Y
MM28 Y C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM27 net23 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM26 Y B1 net23 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 Y A1 net24 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net24 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 s1 C s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM32 s2 B2 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM31 s1 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM30 s2 B1 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM29 s1 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI222xp25_ASAP7_6t_R A1 A2 B1 B2 C1 C2 VDD VSS Y
MM6 net50 C2 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 Y C1 net50 VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 net51 B2 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM3 Y B1 net51 VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 net49 A2 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 Y A1 net49 VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 Y A2 net53 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net53 B2 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net27 C2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 Y A1 net53 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net53 B1 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net27 C1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI22xp25_ASAP7_6t_R A1 A2 B1 B2 VDD VSS Y
MM5 Y B2 net13 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 Y B1 net13 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net13 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net13 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net29 B1 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 net30 A1 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM7 Y B2 net29 VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 Y A2 net30 VSS nmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT AOI22xp5_ASAP7_6t_R A1 A2 B1 B2 VDD VSS Y
MM5 Y A2 net13 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 Y A1 net13 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net13 B2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net13 B1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net29 B1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net30 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 Y B2 net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 Y A2 net30 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI311xp33_ASAP7_6t_R A1 A2 A3 B C VDD VSS Y
MM0 Y C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 Y B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net29 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 Y A1 net30 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net30 A2 net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 Y C net020 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net020 B net23 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net23 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net23 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net23 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI31xp33_ASAP7_6t_R A1 A2 A3 B VDD VSS Y
MM5 Y B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net29 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 Y A1 net30 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net30 A2 net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 Y B net23 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net23 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net23 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net23 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI31xp67_ASAP7_6t_R A1 A2 A3 B VDD VSS Y
MM5 Y B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net29 A3 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM2 Y A1 net30 VSS nmos_rvt w=108.00n l=20n nfin=4
MM3 net30 A2 net29 VSS nmos_rvt w=108.00n l=20n nfin=4
MM9 Y B net23 VDD pmos_rvt w=108.00n l=20n nfin=4
MM10 net23 A3 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM7 net23 A2 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM6 net23 A1 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT AOI321xp17_ASAP7_6t_R A1 A2 A3 B1 B2 C VDD VSS Y
MM11 Y B2 net026 VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 Y C VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 net026 B1 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 net29 A3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 Y A1 net30 VSS nmos_rvt w=27.0n l=20n nfin=1
MM3 net30 A2 net29 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 Y B2 net013 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net013 C net23 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 Y B1 net013 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net23 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net23 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net23 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI322xp17_ASAP7_6t_R A1 A2 A3 B1 B2 C1 C2 VDD VSS Y
MM6 net50 C2 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 Y C1 net50 VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 net51 B2 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM3 Y B1 net51 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 net52 A3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 net49 A2 net52 VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 Y A1 net49 VSS nmos_rvt w=27.0n l=20n nfin=1
MM13 net53 A3 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 Y C2 net53 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net53 A2 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net27 B2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 Y C1 net53 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net53 A1 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net27 B1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI32xp33_ASAP7_6t_R A1 A2 A3 B1 B2 VDD VSS Y
MM0 Y A1 net24 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net24 A2 net25 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net25 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 net26 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 Y B1 net26 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net10 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net10 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net10 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 Y B2 net10 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 Y B1 net10 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI331xp17_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C VDD VSS Y
MM17 Y C VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 Y B1 net063 VSS nmos_rvt w=27.0n l=20n nfin=1
MM11 net063 B2 net064 VSS nmos_rvt w=27.0n l=20n nfin=1
MM10 net064 B3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM3 net25 A3 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 Y A1 net26 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 net26 A2 net25 VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 net031 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net031 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net031 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net030 B1 net031 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y C net030 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net030 B2 net031 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net030 B3 net031 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI332xp17_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 VDD VSS Y
MM20 net053 B2 net57 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y A1 net55 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net55 A2 net54 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net54 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 net59 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 Y C1 net59 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 Y B1 net56 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net56 B2 net053 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net57 B3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 Y C1 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 Y C2 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 s1 B2 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM17 s2 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 s2 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 s2 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 s1 B3 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 s1 B2 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 s1 B1 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI333xp17_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 C3 VDD VSS Y
MM0 Y C1 net55 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net55 C2 net54 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net54 C3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM19 net58 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 net59 A2 net58 VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 Y A1 net59 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 Y B1 net56 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net56 B2 net051 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net051 B3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 Y A1 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 Y A2 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 Y A3 s1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM17 s2 C3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 s2 C2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 s2 C1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 s1 B3 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 s1 B2 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 s1 B1 s2 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT AOI33xp33_ASAP7_6t_R A1 A2 A3 B1 B2 B3 VDD VSS Y
MM44 Y B1 net52 VSS nmos_rvt w=54.0n l=20n nfin=2
MM45 net52 B2 net51 VSS nmos_rvt w=54.0n l=20n nfin=2
MM48 net51 B3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM39 Y A3 net54 VSS nmos_rvt w=54.0n l=20n nfin=2
MM46 net54 A2 net53 VSS nmos_rvt w=54.0n l=20n nfin=2
MM47 net53 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM33 net015 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM35 Y B1 net015 VDD pmos_rvt w=54.0n l=20n nfin=2
MM32 net015 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM38 Y B2 net015 VDD pmos_rvt w=54.0n l=20n nfin=2
MM31 net015 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM37 Y B3 net015 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT BUFx10_ASAP7_6t_R A VDD VSS Y
MM0 AN A VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM1 Y AN VDD VDD pmos_rvt w=540.0n l=20n nfin=20
MM2 AN A VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM3 Y AN VSS VSS nmos_rvt w=540.0n l=20n nfin=20
.ENDS


.SUBCKT BUFx12_ASAP7_6t_R A VDD VSS Y
MM1 Y AN VDD VDD pmos_rvt w=648.00n l=20n nfin=24
MM0 AN A VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM3 Y AN VSS VSS nmos_rvt w=648.00n l=20n nfin=24
MM2 AN A VSS VSS nmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT BUFx12q_ASAP7_6t_R A VDD VSS Y
MM1 Y AN VDD VDD pmos_rvt w=648.00n l=20n nfin=24
MM0 AN A VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM3 Y AN VSS VSS nmos_rvt w=648.00n l=20n nfin=24
MM2 AN A VSS VSS nmos_rvt w=216.00n l=20n nfin=8
.ENDS


.SUBCKT BUFx16q_ASAP7_6t_R A VDD VSS Y
MM1 Y AN VDD VDD pmos_rvt w=864.00n l=20n nfin=32
MM0 AN A VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM3 Y AN VSS VSS nmos_rvt w=864.00n l=20n nfin=32
MM2 AN A VSS VSS nmos_rvt w=216.00n l=20n nfin=8
.ENDS


.SUBCKT BUFx24_ASAP7_6t_R A VDD VSS Y
MM1 Y AN VDD VDD pmos_rvt w=1.296u l=20n nfin=48
MM0 AN A VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM3 Y AN VSS VSS nmos_rvt w=1.296u l=20n nfin=48
MM2 AN A VSS VSS nmos_rvt w=216.00n l=20n nfin=8
.ENDS


.SUBCKT BUFx2_ASAP7_6t_R A VDD VSS Y
MM3 Y AN VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM2 AN A VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 Y AN VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM1 AN A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT BUFx3_ASAP7_6t_R A VDD VSS Y
MM1 Y AN VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM0 AN A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 AN A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y AN VSS VSS nmos_rvt w=162.00n l=20n nfin=6
.ENDS


.SUBCKT BUFx4_ASAP7_6t_R A VDD VSS Y
MM1 Y AN VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM0 AN A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 AN A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y AN VSS VSS nmos_rvt w=216.00n l=20n nfin=8
.ENDS


.SUBCKT BUFx4q_ASAP7_6t_R A VDD VSS Y
MM1 Y AN VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM0 AN A VDD VDD pmos_rvt w=81.0n l=20n nfin=3
MM3 Y AN VSS VSS nmos_rvt w=216.00n l=20n nfin=8
MM2 AN A VSS VSS nmos_rvt w=81.0n l=20n nfin=3
.ENDS


.SUBCKT BUFx5_ASAP7_6t_R A VDD VSS Y
MM1 Y AN VDD VDD pmos_rvt w=270.0n l=20n nfin=10
MM0 AN A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 Y AN VSS VSS nmos_rvt w=270.0n l=20n nfin=10
MM2 AN A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT BUFx6q_ASAP7_6t_R A VDD VSS Y
MM1 Y AN VDD VDD pmos_rvt w=324.00n l=20n nfin=12
MM0 AN A VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM3 Y AN VSS VSS nmos_rvt w=324.00n l=20n nfin=12
MM2 AN A VSS VSS nmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT BUFx8_ASAP7_6t_R A VDD VSS Y
MM0 AN A VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM1 Y AN VDD VDD pmos_rvt w=432.00n l=20n nfin=16
MM2 AN A VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM3 Y AN VSS VSS nmos_rvt w=432.00n l=20n nfin=16
.ENDS


.SUBCKT DFFARHQNx1_ASAP7_6t_R CLK D QN RESETN VDD VSS
MM46 VSS MH MS VSS nmos_rvt w=27.0n l=20n nfin=1
MM24 QN SH VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 VSS MS net050 VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net050 RESETN net10 VSS nmos_rvt w=27.0n l=20n nfin=1
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 net047 RESETN SS VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkb net10 VSS nmos_rvt w=27.0n l=20n nfin=1
MM27 VSS SH net047 VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 MH clkn pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 VSS SS net049 VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkb SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 SH clkn net049 VSS nmos_rvt w=27.0n l=20n nfin=1
MM26 VDD RESETN SS VDD pmos_rvt w=27.0n l=20n nfin=1
MM29 SH clkb net030 VDD pmos_rvt w=27n l=20n nfin=1
MM25 QN SH VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 VDD MH MS VDD pmos_rvt w=27.0n l=20n nfin=1
MM17 VDD SS net030 VDD pmos_rvt w=27.0n l=20n nfin=1
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 MS clkn SH VDD pmos_rvt w=27.0n l=20n nfin=1
MM1 MH clkb pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 MH clkn net53 VDD pmos_rvt w=27n l=20n nfin=1
MM8 VDD MS net53 VDD pmos_rvt w=27.0n l=20n nfin=1
MM19 VDD SH SS VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 VDD RESETN net53 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT DFFASHQNx1_ASAP7_6t_R CLK D QN SETN VDD VSS
MM46 VSS MH net051 VSS nmos_rvt w=27.0n l=20n nfin=1
MM24 QN SH VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 VSS MS net050 VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 MH clkb net050 VSS nmos_rvt w=27.0n l=20n nfin=1
MM27 VSS SH SS VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 MH clkn pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 net048 SS net049 VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkb SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM7 net051 SETN MS VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 SH clkn net049 VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 VSS SETN net048 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 VDD SETN net030 VDD pmos_rvt w=27.0n l=20n nfin=1
MM29 SH clkb net030 VDD pmos_rvt w=27n l=20n nfin=1
MM25 QN SH VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM47 VDD SETN MS VDD pmos_rvt w=27.0n l=20n nfin=1
MM6 VDD MH MS VDD pmos_rvt w=27.0n l=20n nfin=1
MM17 VDD SS net030 VDD pmos_rvt w=27.0n l=20n nfin=1
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 MS clkn SH VDD pmos_rvt w=27.0n l=20n nfin=1
MM1 MH clkb pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 MH clkn net53 VDD pmos_rvt w=27n l=20n nfin=1
MM8 VDD MS net53 VDD pmos_rvt w=27.0n l=20n nfin=1
MM19 VDD SH SS VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT DFFASRHQNx1_ASAP7_6t_R CLK D QN RESETN SETN VDD VSS
MM46 VSS MH net051 VSS nmos_rvt w=27.0n l=20n nfin=1
MM24 QN SH VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 VSS MS net050 VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net050 RESETN net10 VSS nmos_rvt w=27.0n l=20n nfin=1
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 net047 RESETN SS VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkb net10 VSS nmos_rvt w=27.0n l=20n nfin=1
MM27 VSS SH net047 VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 MH clkn pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 net048 SS net049 VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkb SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM7 net051 SETN MS VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 SH clkn net049 VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 VSS SETN net048 VSS nmos_rvt w=27.0n l=20n nfin=1
MM26 VDD RESETN SS VDD pmos_rvt w=27.0n l=20n nfin=1
MM16 VDD SETN net030 VDD pmos_rvt w=27.0n l=20n nfin=1
MM29 SH clkb net030 VDD pmos_rvt w=27n l=20n nfin=1
MM25 QN SH VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM47 VDD SETN MS VDD pmos_rvt w=27.0n l=20n nfin=1
MM6 VDD MH MS VDD pmos_rvt w=27.0n l=20n nfin=1
MM17 VDD SS net030 VDD pmos_rvt w=27.0n l=20n nfin=1
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 MS clkn SH VDD pmos_rvt w=27.0n l=20n nfin=1
MM1 MH clkb pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 MH clkn net53 VDD pmos_rvt w=27n l=20n nfin=1
MM8 VDD MS net53 VDD pmos_rvt w=27.0n l=20n nfin=1
MM19 VDD SH SS VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 VDD RESETN net53 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT DFFHQNx1_ASAP7_6t_R CLK D QN VDD VSS
MM24 QN SH VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 SH clkn pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkb SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 MH clkn pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 QN SH VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkb pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkn SH VDD pmos_rvt w=27n l=20n nfin=1
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkn pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM1 MH clkb pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT DFFHQNx2_ASAP7_6t_R CLK D QN VDD VSS
MM44 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM43 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM42 QN net0100 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM36 net097 clkb net0100 VSS nmos_rvt w=27.0n l=20n nfin=1
MM35 net0102 net0100 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM34 net097 net089 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM33 net089 clkn pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM32 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM27 net0100 clkn pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM26 net089 clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 pd5 net0102 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 pd3 net097 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM47 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM46 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM45 QN net0100 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM41 net097 clkn net0100 VDD pmos_rvt w=27n l=20n nfin=1
MM40 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM39 net089 clkb pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM38 net0102 net0100 VDD VDD pmos_rvt w=27n l=20n nfin=1
MM37 net097 net089 VDD VDD pmos_rvt w=27n l=20n nfin=1
MM31 pd2 net097 VDD VDD pmos_rvt w=27n l=20n nfin=1
MM30 pd4 net0102 VDD VDD pmos_rvt w=27n l=20n nfin=1
MM29 net089 clkn pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM28 net0100 clkb pd4 VDD pmos_rvt w=27n l=20n nfin=1
.ENDS


.SUBCKT DFFHQNx3_ASAP7_6t_R CLK D QN VDD VSS
MM47 QN SH VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM39 MS clkb SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM38 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM37 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM36 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM35 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM34 MH clkn pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM33 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM28 SH clkn pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM27 MH clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM26 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM48 QN SH VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM46 MS clkn SH VDD pmos_rvt w=27.0n l=20n nfin=1
MM45 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM44 MH clkb pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM43 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM42 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM41 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM40 MS MH VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM32 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM31 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM30 MH clkn pd2 VDD pmos_rvt w=27.0n l=20n nfin=1
MM29 SH clkb pd4 VDD pmos_rvt w=27n l=20n nfin=1
.ENDS


.SUBCKT DFFHQx4_ASAP7_6t_R CLK D Q VDD VSS
MM62 Q net0114 VSS VSS nmos_rvt w=216.00n l=20n nfin=8
MM61 net0114 SH VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM55 MS clkb SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM44 SH clkn pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM54 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM53 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM52 MH clkn pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM51 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM43 MH clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM39 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM40 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM42 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM41 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM64 net0114 SH VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM63 Q net0114 VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM60 MS clkn SH VDD pmos_rvt w=27.0n l=20n nfin=1
MM59 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM58 MH clkb pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM57 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM56 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM49 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM45 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM48 MH clkn pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM47 SH clkb pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM50 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM46 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT DFFLQNx1_ASAP7_6t_R CLK D QN VDD VSS
MM45 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM44 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM42 QN SH VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net0111 net097 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 net0109 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM26 MH clkn net0111 VSS nmos_rvt w=27.0n l=20n nfin=1
MM27 SH clkb net0109 VSS nmos_rvt w=27.0n l=20n nfin=1
MM32 net0113 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM33 net097 clkn SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM34 MH clkb net0113 VSS nmos_rvt w=54.0n l=20n nfin=2
MM35 net097 MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM36 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM47 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM46 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM43 QN SH VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM41 net097 clkb SH VDD pmos_rvt w=27n l=20n nfin=1
MM40 net0114 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM39 MH clkn net0114 VDD pmos_rvt w=54.0n l=20n nfin=2
MM28 MH clkb net0112 VDD pmos_rvt w=27.0n l=20n nfin=1
MM29 SH clkn net0110 VDD pmos_rvt w=27.0n l=20n nfin=1
MM30 net0112 net097 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM31 net0110 SS VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM37 net097 MH VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM38 SS SH VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT DFFLQNx2_ASAP7_6t_R CLK D QN VDD VSS
MM17 SH clkb pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 MH clkn pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkn SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 MH clkb pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM24 QN SH VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkb pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkb SH VDD pmos_rvt w=27n l=20n nfin=1
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM25 QN SH VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkn pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM1 MH clkn pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT DFFLQNx3_ASAP7_6t_R CLK D QN VDD VSS
MM17 SH clkb pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM49 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM24 QN SH VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 MH clkn pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM48 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 MH clkb pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 MS clkn SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM13 MS clkb SH VDD pmos_rvt w=27n l=20n nfin=1
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkb pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM51 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM25 QN SH VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM50 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkn pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM1 MH clkn pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
.ENDS


.SUBCKT DFFLQx4_ASAP7_6t_R CLK D Q VDD VSS
MM4 MH clkb pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 SH clkb pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM52 Q QN VSS VSS nmos_rvt w=216.00n l=20n nfin=8
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 MS clkn SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 MH clkn pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM24 QN SH VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 QN SH VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkb pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkb SH VDD pmos_rvt w=27n l=20n nfin=1
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkn pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM1 MH clkn pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM53 Q QN VDD VDD pmos_rvt w=216.00n l=20n nfin=8
.ENDS


.SUBCKT DHLx1_ASAP7_6t_R CLK D Q VDD VSS
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 MH clkb pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 Q MH VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net088 MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkn pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 net088 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 MH clkn pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 Q MH VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net088 MH VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 pd2 net088 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM10 MH clkb pd2 VDD pmos_rvt w=27n l=20n nfin=1
.ENDS


.SUBCKT DHLx2_ASAP7_6t_R CLK D Q VDD VSS
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 MH clkb pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 Q MH VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM6 net088 MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkn pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 net088 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 MH clkn pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 Q MH VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM12 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net088 MH VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 pd2 net088 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM10 MH clkb pd2 VDD pmos_rvt w=27n l=20n nfin=1
.ENDS


.SUBCKT DHLx3_ASAP7_6t_R CLK D Q VDD VSS
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 MH clkb pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 Q MH VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM6 net088 MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkn pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 net088 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 MH clkn pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 Q MH VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM12 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net088 MH VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 pd2 net088 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM10 MH clkb pd2 VDD pmos_rvt w=27n l=20n nfin=1
.ENDS


.SUBCKT DLLx1_ASAP7_6t_R CLK D Q VDD VSS
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 MH clkn pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 Q MH VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net088 MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 net088 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 MH clkb pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 Q MH VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net088 MH VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 pd2 net088 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM10 MH clkn pd2 VDD pmos_rvt w=27n l=20n nfin=1
.ENDS


.SUBCKT DLLx2_ASAP7_6t_R CLK D Q VDD VSS
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 MH clkn pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 Q MH VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM6 net088 MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 net088 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 MH clkb pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 Q MH VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM12 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net088 MH VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 pd2 net088 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM10 MH clkn pd2 VDD pmos_rvt w=27n l=20n nfin=1
.ENDS


.SUBCKT DLLx3_ASAP7_6t_R CLK D Q VDD VSS
MM5 pd1 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 MH clkn pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 Q MH VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM6 net088 MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 net088 VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 MH clkb pu1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 pu1 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 Q MH VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM12 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net088 MH VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 pd2 net088 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM10 MH clkn pd2 VDD pmos_rvt w=27n l=20n nfin=1
.ENDS


.SUBCKT FAxp33_ASAP7_6t_R A B CI CON SN VDD VSS
MM22 SN CI net081 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 net081 B net082 VDD pmos_rvt w=54.0n l=20n nfin=2
MM20 net082 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SN CON net027 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net027 CI VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 net027 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net027 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 CON A net37 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net37 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net27 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 CON CI net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net27 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 SN CI net080 VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 net080 B net079 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 net079 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM19 VSS CI net067 VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 VSS B net067 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 VSS A net067 VSS nmos_rvt w=54.0n l=20n nfin=2
MM16 net067 CON SN VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 VSS B net25 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 VSS B net36 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 VSS A net25 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net36 A CON VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net25 CI CON VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT HAxp5_ASAP7_6t_R A B CON SN VDD VSS
MM4 net015 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net015 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 SN CON net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 CON B net43 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net43 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net041 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 SN B net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 SN CON VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 CON A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 CON B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT HB1x1_ASAP7_6t_R A VDD VSS Y
MM23 Y net7 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 net7 A VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM22 Y net7 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 net7 A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT HB2x1_ASAP7_6t_R A VDD VSS Y
MM5 Y Abar VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net17 A VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 Abar A net17 VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 Y Abar VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net16 A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 Abar A net16 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT HB3x1_ASAP7_6t_R A VDD VSS Y
MM3 Y net11 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net11 A net18 VDD pmos_rvt w=27n l=20n nfin=1
MM1 net18 A net19 VDD pmos_rvt w=27n l=20n nfin=1
MM0 net19 A VDD VDD pmos_rvt w=27n l=20n nfin=1
MM7 net16 A VSS VSS nmos_rvt w=27n l=20n nfin=1
MM4 Y net11 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net11 A net17 VSS nmos_rvt w=27n l=20n nfin=1
MM6 net17 A net16 VSS nmos_rvt w=27n l=20n nfin=1
.ENDS


.SUBCKT HB4x1_ASAP7_6t_R A VDD VSS Y
MM9 net16 A net17 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 net17 A VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM3 net5 A net18 VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 Y net5 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net18 A net16 VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 net20 A net21 VDD pmos_rvt w=27.0n l=20n nfin=1
MM5 net21 A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 net5 A net19 VDD pmos_rvt w=27.0n l=20n nfin=1
MM4 net19 A net20 VDD pmos_rvt w=27.0n l=20n nfin=1
MM1 Y net5 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT INVx11_ASAP7_6t_R A VDD VSS Y
MM0 Y A VSS VSS nmos_rvt w=594.00n l=20n nfin=22
MM1 Y A VDD VDD pmos_rvt w=594.00n l=20n nfin=22
.ENDS


.SUBCKT INVx13_ASAP7_6t_R A VDD VSS Y
MM0 Y A VSS VSS nmos_rvt w=702.00n l=20n nfin=26
MM1 Y A VDD VDD pmos_rvt w=702.00n l=20n nfin=26
.ENDS


.SUBCKT INVx1_ASAP7_6t_R A VDD VSS Y
MM0 Y A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 Y A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT INVx2_ASAP7_6t_R A VDD VSS Y
MM0 Y A VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM1 Y A VDD VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT INVx3_ASAP7_6t_R A VDD VSS Y
MM0 Y A VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM1 Y A VDD VDD pmos_rvt w=162.00n l=20n nfin=6
.ENDS


.SUBCKT INVx4_ASAP7_6t_R A VDD VSS Y
MM0 Y A VSS VSS nmos_rvt w=216.00n l=20n nfin=8
MM1 Y A VDD VDD pmos_rvt w=216.00n l=20n nfin=8
.ENDS


.SUBCKT INVx5_ASAP7_6t_R A VDD VSS Y
MM0 Y A VSS VSS nmos_rvt w=270.0n l=20n nfin=10
MM1 Y A VDD VDD pmos_rvt w=270.0n l=20n nfin=10
.ENDS


.SUBCKT INVx6_ASAP7_6t_R A VDD VSS Y
MM0 Y A VSS VSS nmos_rvt w=324.00n l=20n nfin=12
MM1 Y A VDD VDD pmos_rvt w=324.00n l=20n nfin=12
.ENDS


.SUBCKT INVx8_ASAP7_6t_R A VDD VSS Y
MM0 Y A VSS VSS nmos_rvt w=432.00n l=20n nfin=16
MM1 Y A VDD VDD pmos_rvt w=432.00n l=20n nfin=16
.ENDS


.SUBCKT INVxp5_ASAP7_6t_R A VDD VSS Y
MM0 Y A VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 Y A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT MAJIxp5_ASAP7_6t_R A B C VDD VSS Y
MM4 net17 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y B net17 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net1 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net1 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y A net1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 Y A net1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net16 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 Y B net16 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net3 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net3 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 Y A net3 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 Y A net3 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT MAJx1_ASAP7_6t_R A B C VDD VSS Y
MM13 maji C net020 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net17 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 maji C net17 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net020 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net1 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 maji B net1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 Y maji VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 maji C net018 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net16 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 maji C net16 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net018 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net3 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 maji B net3 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 Y maji VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT MAJx2_ASAP7_6t_R A B C VDD VSS Y
MM13 maji C net020 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net17 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 maji C net17 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net020 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net1 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 maji B net1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 Y maji VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM12 maji C net018 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net16 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 maji C net16 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net018 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net3 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 maji B net3 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 Y maji VDD VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT MAJx3_ASAP7_6t_R A B C VDD VSS Y
MM13 maji C net020 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net17 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 maji C net17 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net020 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net1 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 maji B net1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 Y maji VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM12 maji C net018 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net16 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 maji C net16 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net018 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net3 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 maji B net3 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 Y maji VDD VDD pmos_rvt w=162.00n l=20n nfin=6
.ENDS


.SUBCKT NAND2x1_ASAP7_6t_R A B VDD VSS Y
MM3 net16 A VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM2 Y B net16 VSS nmos_rvt w=108.00n l=20n nfin=4
MM1 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 Y A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NAND2x1p5_ASAP7_6t_R A B VDD VSS Y
MM3 net16 A VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM2 Y B net16 VSS nmos_rvt w=162.00n l=20n nfin=6
MM1 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 Y A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NAND2x2_ASAP7_6t_R A B VDD VSS Y
MM3 net16 A VSS VSS nmos_rvt w=216.00n l=20n nfin=8
MM2 Y B net16 VSS nmos_rvt w=216.00n l=20n nfin=8
MM1 Y B VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM0 Y A VDD VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT NAND2xp5R_ASAP7_6t_R A B VDD VSS Y
MM3 net16 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 Y B net16 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 Y A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NAND2xp5_ASAP7_6t_R A B VDD VSS Y
MM3 net16 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 Y B net16 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 Y B VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM0 Y A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT NAND3x1_ASAP7_6t_R A B C VDD VSS Y
MM0 Y A net22 VSS nmos_rvt w=162.00n l=20n nfin=6
MM1 net22 B net21 VSS nmos_rvt w=162.00n l=20n nfin=6
MM2 net21 C VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM3 Y A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 Y C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NAND3x2_ASAP7_6t_R A B C VDD VSS Y
MM0 Y A net22 VSS nmos_rvt w=324.00n l=20n nfin=12
MM1 net22 B net21 VSS nmos_rvt w=324.00n l=20n nfin=12
MM2 net21 C VSS VSS nmos_rvt w=324.00n l=20n nfin=12
MM3 Y A VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM4 Y B VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM5 Y C VDD VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT NAND3xp33R_ASAP7_6t_R A B C VDD VSS Y
MM0 Y A net22 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net22 B net21 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net21 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 Y C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NAND3xp33_ASAP7_6t_R A B C VDD VSS Y
MM0 Y A net22 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net22 B net21 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net21 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM4 Y B VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM5 Y C VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT NAND4xp25R_ASAP7_6t_R A B C D VDD VSS Y
MM5 pd3 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 pd2 C pd3 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 pd1 B pd2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y A pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 Y D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 Y C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NAND4xp25_ASAP7_6t_R A B C D VDD VSS Y
MM5 pd3 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 pd2 C pd3 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 pd1 B pd2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y A pd1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 Y D VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM6 Y C VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 Y B VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM1 Y A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT NAND4xp75_ASAP7_6t_R A B C D VDD VSS Y
MM5 pd3 D VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM3 pd2 C pd3 VSS nmos_rvt w=162.00n l=20n nfin=6
MM4 pd1 B pd2 VSS nmos_rvt w=162.00n l=20n nfin=6
MM0 Y A pd1 VSS nmos_rvt w=162.00n l=20n nfin=6
MM7 Y D VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM6 Y C VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM2 Y B VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM1 Y A VDD VDD pmos_rvt w=162.00n l=20n nfin=6
.ENDS


.SUBCKT NAND5xp2R_ASAP7_6t_R A B C D E VDD VSS Y
MM6 net29 E VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net30 D net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net024 B net023 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y A net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net023 C net30 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 Y E VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 Y D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 Y A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NAND5xp2_ASAP7_6t_R A B C D E VDD VSS Y
MM6 net29 E VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net30 D net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net024 B net023 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y A net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net023 C net30 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 Y E VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM8 Y D VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM7 Y C VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 Y B VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM10 Y A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT NOR2x1_ASAP7_6t_R A B VDD VSS Y
MM2 VSS A Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 VSS B Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net16 B Y VDD pmos_rvt w=108.00n l=20n nfin=4
MM3 VDD A net16 VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT NOR2x2R_ASAP7_6t_R A B VDD VSS Y
MM2 VSS A Y VSS nmos_rvt w=108.00n l=20n nfin=4
MM1 VSS B Y VSS nmos_rvt w=108.00n l=20n nfin=4
MM4 net16 B Y VDD pmos_rvt w=162.00n l=20n nfin=6
MM3 VDD A net16 VDD pmos_rvt w=162.00n l=20n nfin=6
.ENDS


.SUBCKT NOR2x2_ASAP7_6t_R A B VDD VSS Y
MM2 VSS A Y VSS nmos_rvt w=108.00n l=20n nfin=4
MM1 VSS B Y VSS nmos_rvt w=108.00n l=20n nfin=4
MM4 net16 B Y VDD pmos_rvt w=216.00n l=20n nfin=8
MM3 VDD A net16 VDD pmos_rvt w=216.00n l=20n nfin=8
.ENDS


.SUBCKT NOR2xp5_ASAP7_6t_R A B VDD VSS Y
MM2 VSS A Y VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 VSS B Y VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 net16 B Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 VDD A net16 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NOR3x1_ASAP7_6t_R A B C VDD VSS Y
MM14 Y C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 Y B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 Y A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net21 C VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM10 net22 B net21 VDD pmos_rvt w=162.00n l=20n nfin=6
MM11 Y A net22 VDD pmos_rvt w=162.00n l=20n nfin=6
.ENDS


.SUBCKT NOR3x1f_ASAP7_6t_R A B C VDD VSS Y
MM14 Y C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 Y B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 Y A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net21 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net22 B net21 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 Y A net22 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NOR3x2_ASAP7_6t_R A B C VDD VSS Y
MM14 Y C VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM13 Y B VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM12 Y A VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM8 net21 C VDD VDD pmos_rvt w=324.00n l=20n nfin=12
MM10 net22 B net21 VDD pmos_rvt w=324.00n l=20n nfin=12
MM11 Y A net22 VDD pmos_rvt w=324.00n l=20n nfin=12
.ENDS


.SUBCKT NOR3xp33_ASAP7_6t_R A B C VDD VSS Y
MM14 Y C VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM13 Y B VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 Y A VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 net21 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net22 B net21 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 Y A net22 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NOR4x3f_ASAP7_6t_R A B C D VDD VSS Y
MM7 Y A pd1 VDD pmos_rvt w=162.00n l=20n nfin=6
MM6 pd1 B pd2 VDD pmos_rvt w=162.00n l=20n nfin=6
MM5 pd2 C pd3 VDD pmos_rvt w=162.00n l=20n nfin=6
MM4 pd3 D VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM3 Y D VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM2 Y C VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM1 Y B VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM0 Y A VSS VSS nmos_rvt w=162.00n l=20n nfin=6
.ENDS


.SUBCKT NOR4xp25_ASAP7_6t_R A B C D VDD VSS Y
MM7 Y A pd1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 pd1 B pd2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 pd2 C pd3 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 pd3 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 Y D VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 Y C VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 Y B VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 Y A VSS VSS nmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT NOR5x1f_ASAP7_6t_R A B C D E VDD VSS Y
MM9 Y A net024 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net024 B net023 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net30 D net29 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net29 E VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net023 C net30 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 Y E VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 Y C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 Y B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT NOR5xp2_ASAP7_6t_R A B C D E VDD VSS Y
MM1 VSS A Y VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 VSS B Y VSS nmos_rvt w=27.0n l=20n nfin=1
MM7 VSS C Y VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 VSS D Y VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 VSS E Y VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 net108 A Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net111 B net108 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net110 C net111 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net109 D net110 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 VDD E net109 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT O2A1O1A1Ixp33_ASAP7_6t_R A1 A2 B C D VDD VSS Y
MM10 net048 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 VDD B net047 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net047 A2 net048 VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 VDD D Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 Y C net047 VDD pmos_rvt w=54.0n l=20n nfin=2
MM20 net046 D Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM21 net044 B net046 VSS nmos_rvt w=54.0n l=20n nfin=2
MM22 VSS C net046 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 VSS A1 net044 VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 VSS A2 net044 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT O2A1O1Ixp33_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM6 VSS C Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net020 B Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 VSS A2 net020 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 VSS A1 net020 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 VDD B net017 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net017 C Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 VDD A2 net06 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net06 A1 net017 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT O2A1O1Ixp5_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM0 VSS A1 net014 VSS nmos_rvt w=27.0n l=20n nfin=1
MM3 net014 B Y VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 VSS A2 net014 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 VSS C Y VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 net045 C Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 VDD A1 net019 VDD pmos_rvt w=108.00n l=20n nfin=4
MM4 net019 A2 net045 VDD pmos_rvt w=108.00n l=20n nfin=4
MM6 VDD B net045 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA211x1_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM41 net99 A2 net94 VSS nmos_rvt w=54.0n l=20n nfin=2
MM40 net99 A1 net94 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 Y net99 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM42 net94 B net100 VSS nmos_rvt w=54.0n l=20n nfin=2
MM43 net100 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM36 net101 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM39 net99 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM38 net99 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 Y net99 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM37 net99 A2 net101 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA211x2_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM0 Y net019 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM39 net019 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM38 net019 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM37 net019 A2 net20 VDD pmos_rvt w=54.0n l=20n nfin=2
MM36 net20 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y net019 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM41 net019 A2 net10 VSS nmos_rvt w=54.0n l=20n nfin=2
MM43 net19 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM40 net019 A1 net10 VSS nmos_rvt w=54.0n l=20n nfin=2
MM42 net10 B net19 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA21x1_ASAP7_6t_R A1 A2 B VDD VSS Y
MM11 Y net041 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net041 A2 net042 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net041 A1 net042 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net042 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 VDD A2 net046 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 VDD B net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 net046 A1 net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 Y net041 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA21x2_ASAP7_6t_R A1 A2 B VDD VSS Y
MM3 Y net25 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM2 net25 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net25 A2 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net27 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y net25 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM6 net11 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net25 A2 net11 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net25 A1 net11 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA221x1_ASAP7_6t_R A1 A2 B1 B2 C VDD VSS Y
MM4 Y yn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 s1 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 s2 C s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 yn B1 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 s1 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 yn B2 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y yn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net054 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net053 B2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 yn A1 net054 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 yn C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 yn B1 net053 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA221x2_ASAP7_6t_R A1 A2 B1 B2 C VDD VSS Y
MM4 Y yn VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM11 s1 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 s2 C s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 yn B1 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 s1 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 yn B2 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y yn VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM5 net054 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net053 B2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 yn A1 net054 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 yn C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 yn B1 net053 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA222x1_ASAP7_6t_R A1 A2 B1 B2 C1 C2 VDD VSS Y
MM5 net121 B1 net129 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net129 B2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net130 C2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net121 C1 net130 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net128 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net121 A1 net128 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y net121 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 net119 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net119 C1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y net121 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net121 A2 net120 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net121 A1 net120 VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 net120 B2 net119 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net120 B1 net119 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA222x2_ASAP7_6t_R A1 A2 B1 B2 C1 C2 VDD VSS Y
MM1 Y net061 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM3 net061 A1 net070 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net070 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net061 C1 net068 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net068 C2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net069 B2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net061 B1 net069 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net060 B1 net059 VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 net060 B2 net059 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net061 A1 net060 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net061 A2 net060 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y net061 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM10 net059 C1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 net059 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA22x1_ASAP7_6t_R A1 A2 B1 B2 VDD VSS Y
MM8 net18 B2 net042 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net18 A2 net043 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net042 B1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y net18 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net043 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM17 net18 B1 net034 VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 net034 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM16 net18 B2 net034 VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 net034 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y net18 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA22x2_ASAP7_6t_R A1 A2 B1 B2 VDD VSS Y
MM9 Y net033 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM3 net3 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net033 A2 net3 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net3 B1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net033 A1 net3 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net13 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net033 A2 net13 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net14 B1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 Y net033 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM10 net033 B2 net14 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA311x1_ASAP7_6t_R A1 A2 A3 B C VDD VSS Y
MM0 Y net119 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net116 C net119 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net113 B net116 VSS nmos_rvt w=54.0n l=20n nfin=2
MM22 VSS A3 net113 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 VSS A1 net113 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 VSS A2 net113 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 Y net119 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 net117 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net118 A2 net117 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net119 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net119 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net119 A1 net118 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA311x2_ASAP7_6t_R A1 A2 A3 B C VDD VSS Y
MM0 Y net146 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM10 net143 C net146 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net140 B net143 VSS nmos_rvt w=54.0n l=20n nfin=2
MM22 VSS A3 net140 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 VSS A1 net140 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 VSS A2 net140 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 Y net146 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM16 net144 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net145 A2 net144 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net146 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net146 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net146 A1 net145 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA31x1_ASAP7_6t_R A1 A2 A3 B VDD VSS Y
MM9 Y yn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net012 B yn VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 VSS A1 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 VSS A2 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 VSS A3 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 Y yn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 yn B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 yn A1 net36 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net36 A2 net37 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net37 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA31x2_ASAP7_6t_R A1 A2 A3 B VDD VSS Y
MM9 Y yn VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM4 net012 B yn VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 VSS A1 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 VSS A2 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 VSS A3 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 Y yn VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM7 yn B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 yn A1 net36 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net36 A2 net37 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net37 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA321x1_ASAP7_6t_R A1 A2 A3 B1 B2 C VDD VSS Y
MM1 Y net127 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net125 B2 net127 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net125 B1 net127 VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 net124 C net125 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 VSS A3 net124 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 VSS A2 net124 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 VSS A1 net124 VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 Y net127 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 VDD A3 net141 VDD pmos_rvt w=27.0n l=20n nfin=1
MM0 VDD C net127 VDD pmos_rvt w=27.0n l=20n nfin=1
MM5 VDD B1 net139 VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 net141 A2 net140 VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 net139 B2 net127 VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 net140 A1 net127 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OA321x2_ASAP7_6t_R A1 A2 A3 B1 B2 C VDD VSS Y
MM1 Y net131 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM8 net129 B2 net131 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net129 B1 net131 VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 net128 C net129 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 VSS A3 net128 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 VSS A2 net128 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 VSS A1 net128 VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 Y net131 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM4 VDD A3 net145 VDD pmos_rvt w=27.0n l=20n nfin=1
MM0 VDD C net131 VDD pmos_rvt w=27.0n l=20n nfin=1
MM5 VDD B1 net143 VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 net145 A2 net144 VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 net143 B2 net131 VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 net144 A1 net131 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OA322x1_ASAP7_6t_R A1 A2 A3 B1 B2 C1 C2 VDD VSS Y
MM16 Y yn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM32 net048 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 yn C1 net046 VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net046 B1 net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM31 yn C2 net046 VSS nmos_rvt w=54.0n l=20n nfin=2
MM34 net048 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM33 net048 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM30 net046 B2 net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 Y yn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM25 net064 C2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 yn A3 net066 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 yn C1 net064 VDD pmos_rvt w=54.0n l=20n nfin=2
MM24 net065 B1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net067 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM23 yn B2 net065 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 net066 A2 net067 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA322x2_ASAP7_6t_R A1 A2 A3 B1 B2 C1 C2 VDD VSS Y
MM16 Y yn VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM32 net048 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 yn C1 net046 VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net046 B1 net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM31 yn C2 net046 VSS nmos_rvt w=54.0n l=20n nfin=2
MM34 net048 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM33 net048 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM30 net046 B2 net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 Y yn VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM25 net064 C2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 yn A3 net066 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 yn C1 net064 VDD pmos_rvt w=54.0n l=20n nfin=2
MM24 net065 B1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net067 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM23 yn B2 net065 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 net066 A2 net067 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA32x1_ASAP7_6t_R A1 A2 A3 B1 B2 VDD VSS Y
MM21 Y net051 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net051 B2 net049 VSS nmos_rvt w=54.0n l=20n nfin=2
MM27 net049 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net051 B1 net049 VSS nmos_rvt w=54.0n l=20n nfin=2
MM30 net049 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM28 net049 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 Y net051 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM24 net051 A1 net057 VDD pmos_rvt w=27.0n l=20n nfin=1
MM22 net058 A3 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM26 net056 B2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM23 net057 A2 net058 VDD pmos_rvt w=27.0n l=20n nfin=1
MM25 net051 B1 net056 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OA32x2_ASAP7_6t_R A1 A2 A3 B1 B2 VDD VSS Y
MM21 Y net051 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM29 net051 B2 net049 VSS nmos_rvt w=54.0n l=20n nfin=2
MM27 net049 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net051 B1 net049 VSS nmos_rvt w=54.0n l=20n nfin=2
MM30 net049 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM28 net049 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 Y net051 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM24 net051 A1 net057 VDD pmos_rvt w=27.0n l=20n nfin=1
MM22 net058 A3 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM26 net056 B2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM23 net057 A2 net058 VDD pmos_rvt w=27.0n l=20n nfin=1
MM25 net051 B1 net056 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OA331x1_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C VDD VSS Y
MM4 net012 B3 net031 VSS nmos_rvt w=54.0n l=20n nfin=2
MM18 VSS net027 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 VSS A1 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 VSS A2 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 VSS A3 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net012 B1 net031 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net031 C net027 VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net012 B2 net031 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 VDD C net027 VDD pmos_rvt w=27.0n l=20n nfin=1
MM12 net033 B1 net027 VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 net063 B2 net033 VDD pmos_rvt w=27.0n l=20n nfin=1
MM10 VDD B3 net063 VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 VDD A3 net26 VDD pmos_rvt w=27.0n l=20n nfin=1
MM14 net037 A1 net027 VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 net26 A2 net037 VDD pmos_rvt w=27.0n l=20n nfin=1
MM19 VDD net027 Y VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA331x2_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C VDD VSS Y
MM24 VSS net071 Y VSS nmos_rvt w=108.00n l=20n nfin=4
MM23 net070 C net071 VSS nmos_rvt w=54.0n l=20n nfin=2
MM22 net067 B3 net070 VSS nmos_rvt w=54.0n l=20n nfin=2
MM21 net067 B2 net070 VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 net067 B1 net070 VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 VSS A2 net067 VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 VSS A1 net067 VSS nmos_rvt w=54.0n l=20n nfin=2
MM16 VSS A3 net067 VSS nmos_rvt w=54.0n l=20n nfin=2
MM31 VDD C net071 VDD pmos_rvt w=27.0n l=20n nfin=1
MM30 VDD B3 net085 VDD pmos_rvt w=27.0n l=20n nfin=1
MM29 net085 B2 net086 VDD pmos_rvt w=27.0n l=20n nfin=1
MM28 net086 B1 net071 VDD pmos_rvt w=27.0n l=20n nfin=1
MM27 VDD A3 net084 VDD pmos_rvt w=27.0n l=20n nfin=1
MM26 net084 A2 net083 VDD pmos_rvt w=27.0n l=20n nfin=1
MM25 net083 A1 net071 VDD pmos_rvt w=27.0n l=20n nfin=1
MM0 VDD net071 Y VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT OA332x1_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 VDD VSS Y
MM7 s1 C1 net022 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 s1 C2 net022 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 VSS net022 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM22 s1 B2 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 VSS A3 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM16 VSS A2 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 VSS A1 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 s2 B3 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 s2 B2 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 s2 B1 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 net053 B2 net56 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net041 A1 net022 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net55 A2 net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 VDD A3 net55 VDD pmos_rvt w=54.0n l=20n nfin=2
MM24 VDD net022 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM18 VDD C2 net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net045 C1 net022 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net043 B1 net022 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net56 B2 net043 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 VDD B3 net053 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA332x2_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 VDD VSS Y
MM7 s1 C1 net022 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 s1 C2 net022 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 VSS net022 Y VSS nmos_rvt w=108.00n l=20n nfin=4
MM22 s1 B2 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 VSS A3 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM16 VSS A2 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 VSS A1 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 s2 B3 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 s2 B2 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 s2 B1 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 net053 B2 net56 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net041 A1 net022 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net55 A2 net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 VDD A3 net55 VDD pmos_rvt w=54.0n l=20n nfin=2
MM24 VDD net022 Y VDD pmos_rvt w=108.00n l=20n nfin=4
MM18 VDD C2 net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net045 C1 net022 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net043 B1 net022 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net56 B2 net043 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 VDD B3 net053 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA333x1_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 C3 VDD VSS Y
MM20 VDD net027 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 VDD C3 net040 VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 net040 C2 net086 VDD pmos_rvt w=54.0n l=20n nfin=2
MM17 net086 C1 net027 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 VDD B3 net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net041 B2 net087 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net087 B1 net027 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 VDD A3 net038 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net038 A2 net084 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net084 A1 net027 VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 Y net027 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net068 B3 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM21 net068 B2 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net068 B1 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net015 C3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net015 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 net015 C1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net027 A3 net068 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net027 A2 net068 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net027 A1 net068 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA333x2_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 C3 VDD VSS Y
MM20 VDD net027 Y VDD pmos_rvt w=54.0n l=20n nfin=4
MM13 VDD C3 net040 VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 net040 C2 net086 VDD pmos_rvt w=54.0n l=20n nfin=2
MM17 net086 C1 net027 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 VDD B3 net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net041 B2 net087 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net087 B1 net027 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 VDD A3 net038 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net038 A2 net084 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net084 A1 net027 VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 Y net027 VSS VSS nmos_rvt w=54.0n l=20n nfin=4
MM6 net068 B3 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM21 net068 B2 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net068 B1 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net015 C3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net015 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 net015 C1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net027 A3 net068 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net027 A2 net068 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 net027 A1 net068 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OA33x1_ASAP7_6t_R A1 A2 A3 B1 B2 B3 VDD VSS Y
MM3 net126 B3 net125 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net126 B2 net125 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 Y net126 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net126 B1 net125 VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net125 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net125 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net125 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 net132 B1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM12 net133 A1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM9 net134 A2 net133 VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 net131 B2 net132 VDD pmos_rvt w=27.0n l=20n nfin=1
MM14 Y net126 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net126 B3 net131 VDD pmos_rvt w=27.0n l=20n nfin=1
MM6 net126 A3 net134 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OA33x2_ASAP7_6t_R A1 A2 A3 B1 B2 B3 VDD VSS Y
MM7 Y net015 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM5 net21 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net015 B3 net21 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net21 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net015 B2 net21 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net21 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net015 B1 net21 VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 Y net015 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM13 net34 B1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 net33 B2 net34 VDD pmos_rvt w=27.0n l=20n nfin=1
MM8 net015 B3 net33 VDD pmos_rvt w=27.0n l=20n nfin=1
MM12 net35 A1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM9 net36 A2 net35 VDD pmos_rvt w=27.0n l=20n nfin=1
MM6 net015 A3 net36 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OAI211xp33_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM39 Y C VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM38 Y B VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM37 Y A2 net20 VDD pmos_rvt w=27.0n l=20n nfin=1
MM36 net20 A1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM41 Y A2 net10 VSS nmos_rvt w=54.0n l=20n nfin=2
MM43 net19 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM40 Y A1 net10 VSS nmos_rvt w=54.0n l=20n nfin=2
MM42 net10 B net19 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI211xp67b_ASAP7_6t_R A1 A2 B C VDD VSS Y
MM8 net050 B net043 VSS nmos_rvt w=108.00n l=20n nfin=4
MM9 Y C net050 VSS nmos_rvt w=108.00n l=20n nfin=4
MM2 net043 A2 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM1 net043 A1 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM13 net051 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 Y A2 net051 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 Y C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI21xp25_ASAP7_6t_R A1 A2 B VDD VSS Y
MM2 Y B VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM1 Y A2 net27 VDD pmos_rvt w=27.0n l=20n nfin=1
MM0 net27 A1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM6 net11 B VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM5 Y A2 net11 VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 Y A1 net11 VSS nmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OAI21xp5_ASAP7_6t_R A1 A2 B VDD VSS Y
MM12 net039 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y A2 net039 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 Y A2 net032 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 Y A1 net032 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net032 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI21xp5b_ASAP7_6t_R A1 A2 B VDD VSS Y
MM2 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y A2 net27 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net27 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net11 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 Y A2 net11 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 Y A1 net11 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI221xp33_ASAP7_6t_R A1 A2 B1 B2 C VDD VSS Y
MM12 VSS A2 net042 VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 VSS A1 net042 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net042 B2 net044 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net042 B1 net044 VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 net044 C Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y A1 net048 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 Y B1 net047 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net047 B2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 Y C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM30 net048 A2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI221xp33f_ASAP7_6t_R A1 A2 B1 B2 C VDD VSS Y
MM11 net15 B2 net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net29 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net29 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net15 B1 net29 VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 Y C net15 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 Y C VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 Y B2 net32 VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 net32 B1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM1 Y A2 net30 VDD pmos_rvt w=27.0n l=20n nfin=1
MM0 net30 A1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OAI222xp33_ASAP7_6t_R A1 A2 B1 B2 C1 C2 VDD VSS Y
MM7 net28 C2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM6 Y C1 net28 VDD pmos_rvt w=27.0n l=20n nfin=1
MM5 Y B1 net29 VDD pmos_rvt w=27.0n l=20n nfin=1
MM4 net29 B2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 Y A1 net30 VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 net30 A2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM13 net010 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 net011 B2 net010 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 Y A2 net011 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net010 C1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net011 B1 net010 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 Y A1 net011 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI22xp5_ASAP7_6t_R A1 A2 B1 B2 VDD VSS Y
MM3 net3 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 Y A2 net3 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net3 B1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y A1 net3 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net13 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 Y A2 net13 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net14 B1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 Y B2 net14 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI311xp33_ASAP7_6t_R A1 A2 A3 B C VDD VSS Y
MM16 net037 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 Y A1 net30 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net30 A2 net037 VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 VSS A3 net011 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 VSS A1 net011 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net022 C Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net011 B net022 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 VSS A2 net011 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI31x1f_ASAP7_6t_R A1 A2 A3 B VDD VSS Y
MM17 net039 A1 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM16 net039 A3 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM19 Y B net039 VSS nmos_rvt w=108.00n l=20n nfin=4
MM18 net039 A2 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM23 net047 A1 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM22 net048 A2 net047 VDD pmos_rvt w=108.00n l=20n nfin=4
MM21 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM20 Y A3 net048 VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT OAI31xp5f_ASAP7_6t_R A1 A2 A3 B VDD VSS Y
MM1 net039 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 Y B net039 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net039 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 net039 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 Y B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net047 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM13 net048 A2 net047 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 Y A3 net048 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI321xp33_ASAP7_6t_R A1 A2 A3 B1 B2 C VDD VSS Y
MM8 net013 B2 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 net012 C net013 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net013 B1 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 VSS A3 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 VSS A2 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 VSS A1 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net031 B2 Y VDD pmos_rvt w=27.0n l=20n nfin=1
MM0 VDD C Y VDD pmos_rvt w=27.0n l=20n nfin=1
MM5 VDD B1 net031 VDD pmos_rvt w=27.0n l=20n nfin=1
MM4 VDD A3 net032 VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 net29 A1 Y VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 net032 A2 net29 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OAI322xp33_ASAP7_6t_R A1 A2 A3 B1 B2 C1 C2 VDD VSS Y
MM16 net037 A1 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM7 net28 C2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM6 Y C1 net28 VDD pmos_rvt w=27.0n l=20n nfin=1
MM5 Y B1 net29 VDD pmos_rvt w=27.0n l=20n nfin=1
MM4 net29 B2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 Y A3 net30 VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 net30 A2 net037 VDD pmos_rvt w=27.0n l=20n nfin=1
MM22 net026 A3 net022 VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 net022 C1 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 net026 A2 net022 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 VSS B2 net026 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net022 C2 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net026 A1 net022 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 VSS B1 net026 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI322xp33b_ASAP7_6t_R A1 A2 A3 B1 B2 C1 C2 VDD VSS Y
MM3 net047 A2 net046 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net047 A3 net046 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net047 A1 net046 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 Y C2 net047 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net046 B2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net046 B1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y C1 net047 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net058 A3 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM12 Y A1 net021 VDD pmos_rvt w=27.0n l=20n nfin=1
MM9 Y C1 net024 VDD pmos_rvt w=27.0n l=20n nfin=1
MM8 net024 C2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM13 net021 A2 net058 VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 Y B1 net022 VDD pmos_rvt w=27.0n l=20n nfin=1
MM7 net022 B2 VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OAI32xp5f_ASAP7_6t_R A1 A2 A3 B1 B2 VDD VSS Y
MM22 net039 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 net039 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 net039 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 Y B1 net039 VSS nmos_rvt w=54.0n l=20n nfin=2
MM26 Y B2 net039 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 net045 A3 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net044 B2 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 net046 A2 net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 Y B1 net044 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 Y A1 net046 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI331xp33_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C VDD VSS Y
MM4 net012 B3 net031 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 VSS A1 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 VSS A2 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 VSS A3 net012 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net012 B1 net031 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net031 C Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net012 B2 net031 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 VDD C Y VDD pmos_rvt w=27.0n l=20n nfin=1
MM12 net033 B1 Y VDD pmos_rvt w=27.0n l=20n nfin=1
MM11 net063 B2 net033 VDD pmos_rvt w=27.0n l=20n nfin=1
MM10 VDD B3 net063 VDD pmos_rvt w=27.0n l=20n nfin=1
MM3 VDD A3 net26 VDD pmos_rvt w=27.0n l=20n nfin=1
MM14 net037 A1 Y VDD pmos_rvt w=27.0n l=20n nfin=1
MM2 net26 A2 net037 VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT OAI332xp33_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 VDD VSS Y
MM7 s1 C1 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 s1 C2 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM22 s1 B2 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 VSS A3 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM16 VSS A2 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 VSS A1 s2 VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 s2 B3 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 s2 B2 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 s2 B1 s1 VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 net053 B2 net56 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net041 A1 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net55 A2 net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 VDD A3 net55 VDD pmos_rvt w=54.0n l=20n nfin=2
MM18 VDD C2 net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net045 C1 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net043 B1 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net56 B2 net043 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 VDD B3 net053 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI333xp33_ASAP7_6t_R A1 A2 A3 B1 B2 B3 C1 C2 C3 VDD VSS Y
MM13 VDD C3 net040 VDD pmos_rvt w=54.0n l=20n nfin=2
MM14 net084 A1 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 net040 C2 net086 VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 net058 B1 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net041 B2 net058 VDD pmos_rvt w=54.0n l=20n nfin=2
MM17 net086 C1 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 VDD A3 net038 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 VDD B3 net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net038 A2 net084 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net068 B1 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net015 C3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 Y A2 net068 VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 Y A3 net068 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 net068 B3 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 Y A1 net068 VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 net015 C1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net068 B2 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net015 C2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OAI33xp5f_ASAP7_6t_R A1 A2 A3 B1 B2 B3 VDD VSS Y
MM4 Y B2 net050 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 net050 A2 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net050 A3 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 Y B3 net050 VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 Y B1 net050 VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net050 A1 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net063 B1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net065 A1 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net064 B2 net063 VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net066 A2 net065 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y B3 net064 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 Y A3 net066 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OR2x2_ASAP7_6t_R A B VDD VSS Y
MM5 VSS net7 Y VSS nmos_rvt w=108.00n l=20n nfin=4
MM1 VSS B net7 VSS nmos_rvt w=27.0n l=20n nfin=1
MM2 VSS A net7 VSS nmos_rvt w=27.0n l=20n nfin=1
MM0 VDD net7 Y VDD pmos_rvt w=108.00n l=20n nfin=4
MM4 net15 B net7 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 VDD A net15 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OR2x3R_ASAP7_6t_R A B VDD VSS Y
MM8 VSS net031 Y VSS nmos_rvt w=162.00n l=20n nfin=6
MM7 VSS B net031 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 VSS A net031 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 VDD A net035 VDD pmos_rvt w=108.00n l=20n nfin=4
MM10 net035 B net031 VDD pmos_rvt w=108.00n l=20n nfin=4
MM9 VDD net031 Y VDD pmos_rvt w=324.00n l=20n nfin=12
.ENDS


.SUBCKT OR2x4_ASAP7_6t_R A B VDD VSS Y
MM8 VSS net031 Y VSS nmos_rvt w=216.00n l=20n nfin=8
MM7 VSS B net031 VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 VSS A net031 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 VDD A net035 VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net035 B net031 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 VDD net031 Y VDD pmos_rvt w=216.00n l=20n nfin=8
.ENDS


.SUBCKT OR3x1_ASAP7_6t_R A B C VDD VSS Y
MM1 Y net61 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM14 net61 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 net61 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 net61 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 Y net61 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM8 net66 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 net67 B net66 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net61 A net67 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OR3x2_ASAP7_6t_R A B C VDD VSS Y
MM5 Y net042 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM4 net042 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net042 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net042 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 net046 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net045 B net046 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y net042 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM6 net042 A net045 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OR3x4_ASAP7_6t_R A B C VDD VSS Y
MM5 Y net042 VSS VSS nmos_rvt w=216.00n l=20n nfin=8
MM4 net042 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net042 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net042 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM15 net046 C VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 net045 B net046 VDD pmos_rvt w=54.0n l=20n nfin=2
MM7 Y net042 VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM6 net042 A net045 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OR4x1_ASAP7_6t_R A B C D VDD VSS Y
MM14 Y net049 VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 net049 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 net049 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net049 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net049 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM19 pd3 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM18 pd2 C pd3 VDD pmos_rvt w=54.0n l=20n nfin=2
MM17 pd1 B pd2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 net049 A pd1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 Y net049 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OR4x2_ASAP7_6t_R A B C D VDD VSS Y
MM14 Y net059 VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM13 net059 D VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM12 net059 C VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net059 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net059 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM19 pd3 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM18 pd2 C pd3 VDD pmos_rvt w=54.0n l=20n nfin=2
MM17 pd1 B pd2 VDD pmos_rvt w=54.0n l=20n nfin=2
MM16 net059 A pd1 VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 Y net059 VDD VDD pmos_rvt w=108.00n l=20n nfin=4
.ENDS


.SUBCKT OR5x1_ASAP7_6t_R A B C D E VDD VSS Y
MM9 VSS E net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 VSS D net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 VSS C net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 VSS B net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 VSS net024 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 VSS A net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 VDD net024 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 VDD E net027 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net027 D net29 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net30 B net023 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net023 A net024 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net29 C net30 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT OR5x2_ASAP7_6t_R A B C D E VDD VSS Y
MM9 VSS E net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM8 VSS D net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM7 VSS C net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 VSS B net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 VSS net024 Y VSS nmos_rvt w=108.00n l=20n nfin=4
MM10 VSS A net024 VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 VDD net024 Y VDD pmos_rvt w=108.00n l=20n nfin=4
MM6 VDD E net027 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 net027 D net29 VDD pmos_rvt w=54.0n l=20n nfin=2
MM4 net30 B net023 VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net023 A net024 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net29 C net30 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT SDFHx1_ASAP7_6t_R CLK D QN SE SI VDD VSS
MM30 SEn SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 QN SH VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 MH clkn net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 SH clkn pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkb SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 net0102 SEn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net0101 SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net048 SI net0101 VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net048 D net0102 VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 QN SH VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 MH clkb net050 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net050 SE net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM27 net050 SI net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 net045 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkb pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM2 net045 SEn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkn SH VDD pmos_rvt w=27n l=20n nfin=1
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkn pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM31 SEn SE VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT SDFHx2_ASAP7_6t_R CLK D QN SE SI VDD VSS
MM30 SEn SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 QN SH VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM4 MH clkn net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 SH clkn pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkb SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 net0102 SEn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net0101 SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net048 SI net0101 VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net048 D net0102 VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 QN SH VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 MH clkb net050 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net050 SE net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM27 net050 SI net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 net045 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkb pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM2 net045 SEn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkn SH VDD pmos_rvt w=27n l=20n nfin=1
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkn pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM31 SEn SE VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT SDFHx3_ASAP7_6t_R CLK D QN SE SI VDD VSS
MM30 SEn SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 QN SH VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM4 MH clkn net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 SH clkn pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkb SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 net0102 SEn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net0101 SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net048 SI net0101 VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net048 D net0102 VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 QN SH VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 MH clkb net050 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net050 SE net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM27 net050 SI net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 net045 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkb pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM2 net045 SEn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkn SH VDD pmos_rvt w=27n l=20n nfin=1
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkn pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM31 SEn SE VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT SDFHx4_ASAP7_6t_R CLK D QN SE SI VDD VSS
MM30 SEn SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 QN SH VSS VSS nmos_rvt w=216.00n l=20n nfin=8
MM4 MH clkn net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 SH clkn pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkb SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkb pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 net0102 SEn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net0101 SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net048 SI net0101 VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net048 D net0102 VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 QN SH VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 MH clkb net050 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net050 SE net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM27 net050 SI net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 net045 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkb pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM2 net045 SEn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkn SH VDD pmos_rvt w=27n l=20n nfin=1
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkn pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM31 SEn SE VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT SDFLx1_ASAP7_6t_R CLK D QN SE SI VDD VSS
MM30 SEn SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 QN SH VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 MH clkb net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 SH clkb pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkn SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkn pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 net0102 SEn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net0101 SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net048 SI net0101 VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net048 D net0102 VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 QN SH VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 MH clkn net050 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net050 SE net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM27 net050 SI net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 net045 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkn pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM2 net045 SEn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkb SH VDD pmos_rvt w=27n l=20n nfin=1
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkb pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM31 SEn SE VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT SDFLx2_ASAP7_6t_R CLK D QN SE SI VDD VSS
MM30 SEn SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 QN SH VSS VSS nmos_rvt w=108.00n l=20n nfin=4
MM4 MH clkb net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 SH clkb pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkn SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkn pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 net0102 SEn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net0101 SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net048 SI net0101 VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net048 D net0102 VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 QN SH VDD VDD pmos_rvt w=108.00n l=20n nfin=4
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 MH clkn net050 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net050 SE net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM27 net050 SI net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 net045 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkn pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM2 net045 SEn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkb SH VDD pmos_rvt w=27n l=20n nfin=1
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkb pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM31 SEn SE VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT SDFLx3_ASAP7_6t_R CLK D QN SE SI VDD VSS
MM30 SEn SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 QN SH VSS VSS nmos_rvt w=162.00n l=20n nfin=6
MM4 MH clkb net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 SH clkb pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkn SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkn pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 net0102 SEn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net0101 SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net048 SI net0101 VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net048 D net0102 VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 QN SH VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 MH clkn net050 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net050 SE net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM27 net050 SI net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 net045 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkn pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM2 net045 SEn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkb SH VDD pmos_rvt w=27n l=20n nfin=1
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkb pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM31 SEn SE VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT SDFLx4_ASAP7_6t_R CLK D QN SE SI VDD VSS
MM30 SEn SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM24 QN SH VSS VSS nmos_rvt w=216.00n l=20n nfin=8
MM4 MH clkb net048 VSS nmos_rvt w=54.0n l=20n nfin=2
MM23 clkb clkn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM20 clkn CLK VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM17 SH clkb pd5 VSS nmos_rvt w=27.0n l=20n nfin=1
MM16 pd5 SS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM14 SS SH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM12 MS clkn SH VSS nmos_rvt w=27.0n l=20n nfin=1
MM9 MH clkn pd3 VSS nmos_rvt w=27.0n l=20n nfin=1
MM8 pd3 MS VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM6 MS MH VSS VSS nmos_rvt w=27.0n l=20n nfin=1
MM28 net0102 SEn VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 net0101 SE VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net048 SI net0101 VSS nmos_rvt w=54.0n l=20n nfin=2
MM29 net048 D net0102 VSS nmos_rvt w=54.0n l=20n nfin=2
MM25 QN SH VDD VDD pmos_rvt w=216.00n l=20n nfin=8
MM22 clkb clkn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 MH clkn net050 VDD pmos_rvt w=54.0n l=20n nfin=2
MM21 clkn CLK VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 net050 SE net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM27 net050 SI net045 VDD pmos_rvt w=54.0n l=20n nfin=2
MM26 net045 D VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM19 pd4 SS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM18 SH clkn pd4 VDD pmos_rvt w=27n l=20n nfin=1
MM2 net045 SEn VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM15 SS SH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM13 MS clkb SH VDD pmos_rvt w=27n l=20n nfin=1
MM11 pd2 MS VDD VDD pmos_rvt w=27n l=20n nfin=1
MM10 MH clkb pd2 VDD pmos_rvt w=27n l=20n nfin=1
MM7 MS MH VDD VDD pmos_rvt w=27n l=20n nfin=1
MM31 SEn SE VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT XNOR2x2_ASAP7_6t_R A B VDD VSS Y
MM11 VSS A net047 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net047 B xor VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 VSS net036 xor VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 VSS xor Y VSS nmos_rvt w=108.00n l=20n nfin=4
MM0 VSS A net036 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 VSS B net036 VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 VDD A net019 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 VDD B net019 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net019 net036 xor VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 VDD xor Y VDD pmos_rvt w=108.00n l=20n nfin=4
MM2 net048 B net036 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 VDD A net048 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT XNOR2xp5_ASAP7_6t_R A B VDD VSS Y
MM4 net015 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net015 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 Y net29 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net29 B net43 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net43 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net041 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 Y B net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 Y net29 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net29 A VDD VDD pmos_rvt w=27.0n l=20n nfin=1
MM1 net29 B VDD VDD pmos_rvt w=27.0n l=20n nfin=1
.ENDS


.SUBCKT XNOR2xp5f_ASAP7_6t_R A B VDD VSS Y
MM4 net015 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM5 net015 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM6 Y net29 net015 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net29 B net43 VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net43 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM11 net041 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM10 Y B net041 VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 Y net29 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM0 net29 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net29 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT XOR2x2_ASAP7_6t_R A B VDD VSS Y
MM6 xor net067 net071 VSS nmos_rvt w=54.0n l=20n nfin=2
MM2 net067 B net079 VSS nmos_rvt w=54.0n l=20n nfin=2
MM13 VSS xor Y VSS nmos_rvt w=108.00n l=20n nfin=4
MM5 net071 B VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM3 net079 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM4 net071 A VSS VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 xor B net078 VDD pmos_rvt w=54.0n l=20n nfin=2
MM1 net067 B VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM12 VDD xor Y VDD pmos_rvt w=108.00n l=20n nfin=4
MM0 net067 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM9 xor net067 VDD VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 net078 A VDD VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT XOR2xp5_ASAP7_6t_R A B VDD VSS Y
MM11 VSS A net047 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net047 B Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 VSS net036 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 VSS A net036 VSS nmos_rvt w=27.0n l=20n nfin=1
MM1 VSS B net036 VSS nmos_rvt w=27.0n l=20n nfin=1
MM4 VDD A net019 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 VDD B net019 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net019 net036 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net048 B net036 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 VDD A net048 VDD pmos_rvt w=54.0n l=20n nfin=2
.ENDS


.SUBCKT XOR2xp5r_ASAP7_6t_R A B VDD VSS Y
MM4 VDD A net019 VDD pmos_rvt w=54.0n l=20n nfin=2
MM5 VDD B net019 VDD pmos_rvt w=54.0n l=20n nfin=2
MM6 net019 net036 Y VDD pmos_rvt w=54.0n l=20n nfin=2
MM2 net048 B net036 VDD pmos_rvt w=54.0n l=20n nfin=2
MM3 VDD A net048 VDD pmos_rvt w=54.0n l=20n nfin=2
MM11 VSS A net047 VSS nmos_rvt w=54.0n l=20n nfin=2
MM10 net047 B Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM9 VSS net036 Y VSS nmos_rvt w=54.0n l=20n nfin=2
MM0 VSS A net036 VSS nmos_rvt w=54.0n l=20n nfin=2
MM1 VSS B net036 VSS nmos_rvt w=54.0n l=20n nfin=2
.ENDS


