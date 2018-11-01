#!/bin/bash

p=$(dirname "${0}")
cd "${p}"

#export JAVA_HOME=/home/davidkbd/programas/jrockit-jdk1.6.0_24-R28.1.3-4.0.1
export JAVA_HOME=/home/davidkbd/programas/jdk1.7.0_04
export GENDEV=/home/davidkbd/gendev/gendev/build

#echo "#ifndef LEVEL01_B_XPM" > src/dkbd/maps/level01_b.h
#echo "#define LEVEL01_B_XPM" >> src/dkbd/maps/level01_b.h
#echo "" >> src/dkbd/maps/level01_b.h
#cat src/dkbd/maps/level01_b.xpm | sed 's/static/static const/g' >> src/dkbd/maps/level01_b.h
#echo "" >> src/dkbd/maps/level01_b.h
#echo "#endif" >> src/dkbd/maps/level01_b.h

#echo "#ifndef LEVEL01_XPM" > src/dkbd/maps/level01.h
#echo "#define LEVEL01_XPM" >> src/dkbd/maps/level01.h
#echo "" >> src/dkbd/maps/level01.h
#cat src/dkbd/maps/level01.xpm | sed 's/static/static const/g' >> src/dkbd/maps/level01.h
#echo "" >> src/dkbd/maps/level01.h
#echo "#endif" >> src/dkbd/maps/level01.h

#make -f makefile.gen all
make -f makefile.gen clean all debug
[[ $? -eq 0 ]] || exit 1


wine /home/davidkbd/programas/Gens_KMod_v0.7.3/gens.exe "${PWD/\/home\/davidkbd/C:\/users\/davidkbd\/My Documents}/out/rom.bin" &


#wine /home/davidkbd/programas/KegaFusion/Fusion.exe "${PWD/\/home\/davidkbd/C:\/users\/davidkbd\/My Documents}/out/rom.bin"

#wine ~/programas/Regen/Regen.exe "${PWD/\/home\/davidkbd/C:\/users\/davidkbd\/My Documents}/out/rom.bin"
