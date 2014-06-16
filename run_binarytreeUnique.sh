#!bin/bash

valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_SYS_IDX_SYS_CT_10033_10035 ./BinaryTreeUnique_string 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_CT_10033_10035
valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_cmp_SYS_IDX_SYS_CT_10033_10035 ./BinaryTreeUnique_string_cmp 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_CT_10033_10035
ms_print ./massif/massif_SYS_IDX_SYS_CT_10033_10035 > ./graph_massif/graph_massif_SYS_IDX_SYS_CT_10033_10035
ms_print ./massif/massif_cmp_SYS_IDX_SYS_CT_10033_10035 > ./graph_massif/graph_massif_cmp_SYS_IDX_SYS_CT_10033_10035

valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_SYS_IDX_SYS_CT_10067_10069 ./BinaryTreeUnique_string 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_CT_10067_10069
valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_cmp_SYS_IDX_SYS_CT_10067_10069 ./BinaryTreeUnique_string_cmp 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_CT_10067_10069
ms_print ./massif/massif_SYS_IDX_SYS_CT_10067_10069 > ./graph_massif/graph_massif_SYS_IDX_SYS_CT_10067_10069
ms_print ./massif/massif_cmp_SYS_IDX_SYS_CT_10067_10069 > ./graph_massif/graph_massif_cmp_SYS_IDX_SYS_CT_10067_10069

valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_SYS_IDX_SYS_PK_10022_10023 ./BinaryTreeUnique_string 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_PK_10022_10023
valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_cmp_SYS_IDX_SYS_PK_10022_10023 ./BinaryTreeUnique_string_cmp 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_PK_10022_10023
ms_print ./massif/massif_SYS_IDX_SYS_PK_10022_10023 > ./graph_massif/graph_massif_SYS_IDX_SYS_PK_10022_10023
ms_print ./massif/massif_cmp_SYS_IDX_SYS_PK_10022_10023 > ./graph_massif/graph_massif_cmp_SYS_IDX_SYS_PK_10022_10023

valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_SYS_IDX_SYS_PK_10032_10034 ./BinaryTreeUnique_string 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_PK_10032_10034
valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_cmp_SYS_IDX_SYS_PK_10032_10034 ./BinaryTreeUnique_string_cmp 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_PK_10032_10034
ms_print ./massif/massif_SYS_IDX_SYS_PK_10032_10034 > ./graph_massif/graph_massif_SYS_IDX_SYS_PK_10032_10034
ms_print ./massif/massif_cmp_SYS_IDX_SYS_PK_10032_10034 > ./graph_massif/graph_massif_cmp_SYS_IDX_SYS_PK_10032_10034

valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_SYS_IDX_SYS_PK_10056_10057 ./BinaryTreeUnique_string 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_PK_10056_10057
valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_cmp_SYS_IDX_SYS_PK_10056_10057 ./BinaryTreeUnique_string_cmp 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_PK_10056_10057
ms_print ./massif/massif_SYS_IDX_SYS_PK_10056_10057 > ./graph_massif/graph_massif_SYS_IDX_SYS_PK_10056_10057
ms_print ./massif/massif_cmp_SYS_IDX_SYS_PK_10056_10057 > ./graph_massif/graph_massif_cmp_SYS_IDX_SYS_PK_10056_10057

valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_SYS_IDX_SYS_PK_10066_10068 ./BinaryTreeUnique_string 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_PK_10066_10068
valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_cmp_SYS_IDX_SYS_PK_10066_10068 ./BinaryTreeUnique_string_cmp 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_PK_10066_10068
ms_print ./massif/massif_SYS_IDX_SYS_PK_10066_10068 > ./graph_massif/graph_massif_SYS_IDX_SYS_PK_10066_10068
ms_print ./massif/massif_cmp_SYS_IDX_SYS_PK_10066_10068 > ./graph_massif/graph_massif_cmp_SYS_IDX_SYS_PK_10066_10068

valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_SYS_IDX_SYS_PK_10082_10083 ./BinaryTreeUnique_string 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_PK_10082_10083
valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_cmp_SYS_IDX_SYS_PK_10082_10083 ./BinaryTreeUnique_string_cmp 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_SYS_PK_10082_10083
ms_print ./massif/massif_SYS_IDX_SYS_PK_10082_10083 > ./graph_massif/graph_massif_SYS_IDX_SYS_PK_10082_10083
ms_print ./massif/massif_cmp_SYS_IDX_SYS_PK_10082_10083 > ./graph_massif/graph_massif_cmp_SYS_IDX_SYS_PK_10082_10083

valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_SYS_IDX_W_PK_ARRAY_10018 ./BinaryTreeUnique_string 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_W_PK_ARRAY_10018 
valgrind --tool=massif --time-unit=B --massif-out-file=./massif/massif_cmp_SYS_IDX_W_PK_ARRAY_10018 ./BinaryTreeUnique_string_cmp 10000000 ../h-store/inputMasstree/inMT_SYS_IDX_W_PK_ARRAY_10018 
ms_print ./massif/massif_SYS_IDX_W_PK_ARRAY_10018 > ./graph_massif/graph_massif_SYS_IDX_W_PK_ARRAY_10018
ms_print ./massif/massif_cmp_SYS_IDX_W_PK_ARRAY_10018 > ./graph_massif/graph_massif_cmp_SYS_IDX_W_PK_ARRAY_10018

