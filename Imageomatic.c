/*

	Imageomatic module body

largura maxima = 100 colunas
tab = 4 espaços
0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789

	Este ficheiro constitui apenas um ponto de partida para o
	seu trabalho. Todo este ficheiro pode e deve ser alterado
	à vontade, a começar por este comentário.


 IDENTIFICAÇÃO DOS AUTORES -
	Guilherme Fernandes
*/

#include "Imageomatic.h"

#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
/*** TYPE Int2 ***/

/* More Int2 functions, in case you need them */

/*** TYPE Pixel ***/

/* More Pixel functions, in case you need them */

/*** TYPE Image ***/

void initialization(void)
{
	// This function is automatically called when the interpreter starts.
	// If you need to perform some initialization, this is the place
	// to write the initialization code.
}

Int2 imageCopy(Image img, Int2 n, Image res)
{
	Int2 i;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{
			res[i.x][i.y] = img[i.x][i.y];
		}
	return n;
}

Pixel pixelGrayScale(Pixel pixel)
{
	return pixelGray(pixelGrayAverage(pixel));
}

Int2 imageGrayscale(Image img, Int2 n, Image res)
{
	Int2 i;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{
			res[i.x][i.y] = pixelGrayScale(img[i.x][i.y]);
		}
	return n;
}

Pixel pixelNegativeScale(Pixel pixel)
{
	Pixel newPixel = {MAX_COLOR - pixel.red, MAX_COLOR - pixel.green, MAX_COLOR - pixel.blue};
	return newPixel;
}

Int2 imageNegative(Image img, Int2 n, Image res)
{
	Int2 i;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{
			res[i.x][i.y] = pixelNegativeScale(img[i.x][i.y]);
		}
	return n;
}

Int2 imageHalf(Image img, Int2 n, Image res)
{
	Int2 i;
	for (i.y = 0; 2 * i.y < n.y; i.y++)
		for (i.x = 0; 2 * i.x < n.x; i.x++)
		{

			res[i.x][i.y] = img[2 * i.x][2 * i.y];
		}
	return i;
}
Pixel hexToPixel(unsigned int hex)
{
	Pixel x;
	x.red = ((hex >> 16) & 0xFF);
	x.green = ((hex >> 18) & 0xFF);
	x.blue = ((hex)&0xFF);
	return x;
}

Pixel readColors(String color)
{
	unsigned int hex;
	char col[100];
	FILE *fp;
	if ((fp = fopen(colorsFileName, "r")) == NULL)
		printf("FILE NOT FOUND! WE ARE LOOKING FOR %s FILE\n", colorsFileName);
	bool found = false;
	while (!found && (fscanf(fp, "%x %s\n", &hex, col)) != EOF)
	{
		col[99] = '\0';
		if (strcmp(color, col) == 0)
			found = true;
	}
	fclose(fp);

	Pixel x = {0, 0, 0};
	if (found)
		x = hexToPixel(hex);
	return x;
}

Int2 imagePaint(String cor, Int2 n, Image res)
{
	Pixel pixel = readColors(cor);
	Int2 i;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{

			res[i.x][i.y] = pixel;
		}
	return n;
}

Int2 imageRotation90(Image img, Int2 n, Image res)
{
	Int2 i;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{
			res[n.x - i.y][i.x] = img[i.x][i.y];
		}
	return n;
}

Int2 imagePosterize(Image img, Int2 n, int factor, Image res)
{
	int max = 256 / (1 << factor);
	Int2 i;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{
			Pixel pixel = img[i.x][i.y];
			pixel.blue = (pixel.blue / max) * max;
			pixel.red = (pixel.red / max) * max;
			pixel.green = (pixel.green / max) * max;
			res[i.x][i.y] = pixel;
		}
	return n;
}

Int2 imageDroplet(Int2 n, Image res)
{
	Int2 center = int2Half(n);
	Int2 i;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{
			int dist = int2Distance(center, i);
			int c = 0.7 * MAX_COLOR + 0.3 * sin(dist / 20.0) * MAX_COLOR;
			Pixel pixel = {c, c, c};

			res[i.x][i.y] = pixel;
		}
	return n;
}

Pixel pixelAverage(Image img, Int2 p, int nivel)
{
	int n = 2 * nivel + 1;
	int si = p.x - n / 2;
	if (si < 0)
		si = 0;
	int sj = p.y - n / 2;
	if (sj < 0)
		sj = 0;
	int nP = 0;
	int green = 0, red = 0, blue = 0;
	Pixel pixel;
	for (int i = si; i <= p.x + n / 2; i++)
		for (int j = sj; j <= p.y + n / 2; j++)
		{
			pixel = img[i][j];
			green += pixel.green;
			red += pixel.red;
			blue += pixel.blue;
			nP++;
		}
	pixel.green = green / nP;
	pixel.red = red / nP;
	pixel.blue = blue / nP;
	return pixel;
}

Int2 imageBlur(Image img, Int2 n, int nivel, Image res)
{
	Int2 i;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{
			res[i.x][i.y] = pixelAverage(img, i, nivel);
		}
	return n;
}

Pixel applyMask(Pixel pixel1, Pixel pixel2)
{
	double scale;
	Pixel newPixel;
	scale = (pixel2.red * 1.0) / MAX_COLOR;
	newPixel.red = scale * pixel1.red;
	scale = (pixel2.blue * 1.0) / MAX_COLOR;
	newPixel.blue = scale * pixel1.blue;
	scale = (pixel2.green * 1.0) / MAX_COLOR;
	newPixel.green = scale * pixel1.green;
	return newPixel;
}

Int2 imageMask(Image img1, Int2 n1, Image img2, Int2 n2, Image res) // pre: int2Equals(n1, n2)
{
	Int2 i;
	for (i.y = 0; i.y < n1.y; i.y++)
		for (i.x = 0; i.x < n1.x; i.x++)
		{

			Pixel pixel1 = img1[i.x][i.y];
			Pixel pixel2 = img2[i.x][i.y];
			res[i.x][i.y] = applyMask(pixel1, pixel2);
		}
	return n1;
}

Int2 drawAxes(Image res, Int2 n)
{
	Int2 center = int2Half(n);
	for (int i = 0; i < n.y; i++)
	{
		res[center.x][i] = black;
		res[i][center.y] = black;
	}
	return n;
}

Int2 drawFunc(DoubleFun fun, int scale, Int2 n, Image res)
{
	Int2 center = int2Half(n);
	for (int x = -center.x; x <= center.x; x++)
	{
		int xA = x;
		double y = fun(x / (1.0 * scale));
		if (x < 0)
			xA = center.x + xA;
		else
			xA += center.x;
		y *= scale;
		if (y < 0)
			y = abs(y) + center.y;
		else
			y = center.y - y;
		if (y < MAX_Y)
			res[xA][(int)(y)] = black;
	}
	return n;
}

Int2 imageFunctionPlotting(DoubleFun fun, int scale, Int2 n, Image res)
{
	Int2 i;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
			res[i.x][i.y] = white;
	drawFunc(fun, scale, n, res);
	drawAxes(res, n);
	return n;
}

Int2 imageOrderedDithering(Image img, Int2 n, Image res)
{
#define INDEX_SIDE 8
	Byte indexMatrix[INDEX_SIDE][INDEX_SIDE] = {
		{0, 32, 8, 40, 2, 34, 10, 42},
		{48, 16, 56, 24, 50, 18, 58, 26},
		{12, 44, 4, 36, 14, 46, 6, 28},
		{60, 28, 52, 20, 62, 30, 54, 22},
		{3, 35, 11, 43, 1, 33, 9, 41},
		{51, 19, 59, 27, 49, 17, 57, 25},
		{15, 47, 7, 39, 13, 45, 5, 37},
		{63, 31, 55, 23, 61, 29, 53, 21}};
	Int2 i;
	Pixel pixel;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{
			int grayAverage = pixelGrayAverage(img[i.x][i.y]);
			double intensity = grayAverage / 4.0;
			Byte b = indexMatrix[i.x % INDEX_SIDE][i.y % INDEX_SIDE];
			if (intensity > b)
				pixel = white;
			else
				pixel = black;
			res[i.x][i.y] = pixel;
		}
	return n;
}

char cleanChar(char asciiChar)
{
	if (asciiChar < 0x20 || asciiChar > 0x5F || asciiChar == 0x40)
		return '?';
	else
		return (char)(asciiChar);
}

char sixBitFromAscii(char asciiChar)
{
	if (asciiChar >= 0x60 || asciiChar == 0x40)
	{
		return '?';
	}
	else if (asciiChar == 0x00)
		return '\0';
	else
	{
		return (char)(asciiChar - 0x20);
	}
}

char asciiFromSixBit(char sixBit)
{
	if (sixBit == 0x00)
		return (char)sixBit;
	return (char)(sixBit + 0x20);
}

void convertStringToASCII(String s)
{
	char curr;
	int i = 0;
	do
	{
		*(s + i) = toupper(*(s + i));
		curr = *(s + i);
		*(s + i) = sixBitFromAscii(curr);
		i++;
	} while (curr != '\0');
}

Pixel processPixel(Pixel p, char charc)
{
	Pixel n;
	int twoBits = (charc & 0x30);
	twoBits = twoBits << 2;
	int mask = 0x3f;
	int x = p.red & mask;
	n.red = x | twoBits;
	twoBits = (charc & 0x0C);
	twoBits = twoBits << 4;
	x = p.green & mask;
	n.green = x | twoBits;
	twoBits = (charc & 0x03);
	twoBits = twoBits << 6;
	x = p.blue & mask;
	n.blue = x | twoBits;
	return n;
}

char takeCharFromPixel(Pixel p)
{
	char c = 0x00;
	int mask = 0xC0;
	int bits = (p.red & mask) >> 2;
	c = c | bits;
	bits = (p.green & mask) >> 4;
	c = c | bits;
	bits = (p.blue & mask) >> 6;
	c = c | bits;
	return c;
}

Int2 revImageSteganography(Image img, Int2 n, String a)
{
	Int2 i;
	int pos = 0;
	bool found = false;
	for (i.y = 0; i.y < n.y && !found; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{
			char c = asciiFromSixBit(takeCharFromPixel(img[i.x][i.y]));
			*(a + pos) = c;
			if (c == 0x00)
			{
				*(a + pos) = '\0';
				found = true;
				break;
			}
			pos++;
		}
	return n;
}

Int2 imageSteganography(Image img, Int2 n, String s, Image res)
{
	int len = strlen(s);
	convertStringToASCII(s);
	int writed = 0;
	Int2 i;
	for (i.y = 0; i.y < n.y; i.y++)
		for (i.x = 0; i.x < n.x; i.x++)
		{
			if (writed <= len)
			{
				res[i.x][i.y] = processPixel(img[i.x][i.y], *(s + writed));
				writed++;
			}
			else
				res[i.x][i.y] = img[i.x][i.y];
		}

	if (writed < len)
		res[i.x - 1][i.y - 1] = processPixel(img[i.x - 1][i.y - 1], sixBitFromAscii('\0'));
	return n;
}

void imageTests(void)
{
	static Image img, img2, res;
	Int2 n;

	// Q
	n = imageLoad("img/frutos.png", img);
	n = imageGrayscale(img, n, res);
	imageStore("img/cinzento.png", res, n);

	// N
	n = imageLoad("img/frutos.png", img);
	n = imageNegative(img, n, res);
	imageStore("img/negativo.png", res, n);

	// H
	n = imageLoad("img/frutos.png", img);
	n = imageHalf(img, n, res);
	imageStore("img/metade.png", res, n);

	// P
	n = int2(512, 512);
	n = imagePaint("green", n, res);
	imageStore("img/pintar.png", res, n);

	// R
	n = imageLoad("img/frutos.png", img);
	n = imageRotation90(img, n, res);
	imageStore("img/rotacao_90.png", res, n);

	// O
	n = imageLoad("img/frutos.png", img);
	n = imagePosterize(img, n, 3, res);
	imageStore("img/poster.png", res, n);

	// G
	n = int2(512, 512);
	n = imageDroplet(n, res);
	imageStore("img/goticula.png", res, n);

	// D
	n = imageLoad("img/frutos.png", img);
	n = imageBlur(img, n, 5, res);
	imageStore("img/desfocado.png", res, n);

	// M
	n = imageLoad("img/frutos.png", img);
	n = imageDroplet(n, img2);
	n = imageMask(img, n, img2, n, res);
	imageStore("img/mascarar.png", res, n);

	// F
	n = int2(512, 512);
	n = imageFunctionPlotting(sin, 50, n, res);
	imageStore("img/funcao.png", res, n);

	// T
	n = imageLoad("img/frutos.png", img);
	n = imageOrderedDithering(img, n, res);
	imageStore("img/matizacao.png", res, n);

	// E
	n = imageLoad("img/frutos.png", img);
	n = imageSteganography(img, n, "atacamos ao amanhecer", res);
	imageStore("img/esteganografia.png", res, n);
}
