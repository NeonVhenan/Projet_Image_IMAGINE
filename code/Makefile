recalage : recalage.o image_ppm.o
	gcc recalage.o image_ppm.o -o recalage -lm

recalage.o : recalage.c image_ppm.h
	gcc recalage.c -c -lm


dechiffrement : dechiffrement.o image_ppm.o
	gcc dechiffrement.o image_ppm.o -o dechiffrement -lm

dechiffrement.o : dechiffrement.c image_ppm.h
	gcc dechiffrement.c -c -lm


chiffrement : chiffrement.o image_ppm.o
	gcc chiffrement.o image_ppm.o -o chiffrement -lm

chiffrement.o : chiffrement.c image_ppm.h
	gcc chiffrement.c -c -lm


psnr : psnr.o image_ppm.o
	gcc psnr.o image_ppm.o -o psnr -lm

psnr.o : psnr.c
	gcc psnr.c -c -lm


modif : modif.o image_ppm.o
	gcc modif.o image_ppm.o -o modif -lm

modif.o : modif.c image_ppm.h
	gcc modif.c -c -lm

gradient : gradient.o image_ppm.o
	gcc gradient.o image_ppm.o -o gradient -lm

gradient.o : gradient.c
	gcc gradient.c -c -lm

image_ppm.o : image_ppm.c image_ppm.h
	gcc image_ppm.c -c -lm


clean :
	rm -rf *.o
	rm -f chiffrement dechiffrement recalage psnr modif gradient
