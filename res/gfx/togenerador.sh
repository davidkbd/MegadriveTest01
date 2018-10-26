for i in $(seq 1 16)
do
	size=$[ ${i} * 16 - 16 ]
	convert ingame_floor.png -crop 16x16+0+${size} ${i}.png
	convert ingame_floor2.png -crop 16x16+0+${size} $[${i} + 16].png
	convert ingame_background.png -crop 16x16+0+${size} $[${i} + 32].png
done

