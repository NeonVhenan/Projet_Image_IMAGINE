dechiffrement : dechiffrement.o image_ppm.o
	gcc dechiffrement.o image_ppm.o -o dechiffrement -lm

dechiffrement.o : dechiffrement.c
	gcc dechiffrement.c -c -lm


chiffrement : chiffrement.o image_ppm.o
	gcc chiffrement.o image_ppm.o -o chiffrement -lm

chiffrement.o : chiffrement.c
	gcc chiffrement.c -c -lm


psnr : psnr.o image_ppm.o
	gcc psnr.o image_ppm.o -o psnr -lm

psnr.o : psnr.c
	gcc psnr.c -c -lm


image_ppm.o : image_ppm.c image_ppm.h
	gcc image_ppm.c -c -lm


clean :
	rm -rf *.o
	rm -f chiffrement
	rm -f psnr
