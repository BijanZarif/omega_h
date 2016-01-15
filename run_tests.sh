#!/bin/bash -ex

$VALGRIND ./bin/loop.exe
if [ "LOOP_MODE" -eq "cuda" ]; then
  return
fi
$VALGRIND ./bin/box.exe --file ./data/box.vtu --dim 2 --refinements 6
$VALGRIND ./bin/vtkdiff.exe ./data/box.vtu ./data/box.vtu
$VALGRIND ./bin/node_ele.exe ./data/xgc.node ./data/xgc.ele ./data/xgc.vtu
$VALGRIND ./bin/from_gmsh.exe ./data/cube.msh ./data/cube.vtu
if [ "$USE_MPI" -eq "1" ]; then
  $MPIRUN -np 2 $VALGRIND ./bin/migrate.exe
  $MPIRUN -np 2 $VALGRIND ./bin/conform.exe
fi
$VALGRIND ./bin/warp.exe
if [ "$PATIENT" -eq "1" ]; then
  $VALGRIND ./bin/warp_3d.exe
fi