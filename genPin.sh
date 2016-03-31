gcc genPinwheels.c -lm -o pinwheel
./pinwheel > output/pinwheel.txt
time ../graphics4160/raytra/raytra output/pinwheel.txt output/pinwheel.exr 3 1
exrdisplay output/pinwheel.exr
