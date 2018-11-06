for i in $(seq 1 16)
do
	size=$[ ${i} * 16 - 16 ]
	convert ingame_floor.png       -crop 16x16+0+${size} ../../map_gen/tiles/${i}.png
	convert ingame_floor2.png      -crop 16x16+0+${size} ../../map_gen/tiles/$[${i} + 16].png
	convert ingame_wall.png        -crop 16x16+0+${size} ../../map_gen/tiles/$[${i} + 32].png
	convert ingame_background.png  -crop 16x16+0+${size} ../../map_gen/tiles/$[${i} + 48].png
	convert ingame_background2.png -crop 16x16+0+${size} ../../map_gen/tiles/$[${i} + 64].png
	convert ingame_background3.png -crop 16x16+0+${size} ../../map_gen/tiles/$[${i} + 80].png
	convert ingame_background4.png -crop 16x16+0+${size} ../../map_gen/tiles/$[${i} + 96].png
	convert ingame_background5.png -crop 16x16+0+${size} ../../map_gen/tiles/$[${i} + 112].png
	convert ingame_background6.png -crop 16x16+0+${size} ../../map_gen/tiles/$[${i} + 128].png
done

