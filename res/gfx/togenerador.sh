i=1
for y in {0..22}
do
	for x in {0..7}
	do
		convert deathegg_taller/plana_tileset.png \
                           -crop 16x16+$[ ${x} * 16 ]+$[ ${y} * 16 ] \
                           ../../map_gen/tiles/${i}.png
		i=$[$i + 1]
	done
done

i=1
for y in {0..22}
do
	for x in {0..7}
	do
		n=$i
		[[ $i -lt 100 ]] && n=0$i
		[[ $i -lt 10 ]] && n=00$i
		convert deathegg_taller/plana_tileset.png \
			-crop 8x8+$[ ${x} * 16 ]+$[ ${y} * 16 ] \
			tmp_${n}.png
		i=$[$i + 1]
		n=$i
		[[ $i -lt 100 ]] && n=0$i
		[[ $i -lt 10 ]] && n=00$i
		convert deathegg_taller/plana_tileset.png \
			-crop 8x8+$[ ${x} * 16 + 8 ]+$[ ${y} * 16 ] \
			tmp_${n}.png
		i=$[$i + 1]
		n=$i
		[[ $i -lt 100 ]] && n=0$i
		[[ $i -lt 10 ]] && n=00$i
		convert deathegg_taller/plana_tileset.png \
			-crop 8x8+$[ ${x} * 16 ]+$[ ${y} * 16 + 8 ] \
			tmp_${n}.png
		i=$[$i + 1]
		n=$i
		[[ $i -lt 100 ]] && n=0$i
		[[ $i -lt 10 ]] && n=00$i
		convert deathegg_taller/plana_tileset.png \
			-crop 8x8+$[ ${x} * 16 + 8 ]+$[ ${y} * 16 + 8 ] \
			tmp_${n}.png
		i=$[$i + 1]
	done
done

montage tmp_*.png -tile 16x -geometry +0+0 plana_deathegg_taller.png

rm -frv tmp.sh
rm -fr tmp_*.png

