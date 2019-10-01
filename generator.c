/*
 * generator.c
 *
 *  Created on: Oct 20, 2017
 *      Author: npp
 */
/*
 * Модуль генерирует карту типа "подземелья".
 * Алгориитм работает на клеточных автоматах.
 * Оригинаный код принадлежит  Jim Babcock
 * Статья откуда взято: http://www.roguebasin.com/index.php?title=Cellular_Automata_Method_for_Generating_Random_Cave-Like_Levels
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TILE_FLOOR 0
#define TILE_WALL 1

typedef struct {
	int r1_cutoff, r2_cutoff;
	int reps;
} generation_params;

int **grid;
int **grid2;

int fillprob = 40;
int r1_cutoff = 5, r2_cutoff = 2;
int size_x = 64, size_y = 20;
generation_params *params;

generation_params *params_set;
int generations;

int randpick(void)
{
	if(rand()%100 < fillprob)
		return TILE_WALL;
	else
		return TILE_FLOOR;
}

void initmap(void)
{
	int xi, yi;

	grid  = (int**)malloc(sizeof(int*) * size_y);
	grid2 = (int**)malloc(sizeof(int*) * size_y);

	for(yi=0; yi<size_y; yi++)
	{
		grid [yi] = (int*)malloc(sizeof(int) * size_x);
		grid2[yi] = (int*)malloc(sizeof(int) * size_x);
	}

	for(yi=1; yi<size_y-1; yi++)
	for(xi=1; xi<size_x-1; xi++)
		grid[yi][xi] = randpick();

	for(yi=0; yi<size_y; yi++)
	for(xi=0; xi<size_x; xi++)
		grid2[yi][xi] = TILE_WALL;

	for(yi=0; yi<size_y; yi++)
		grid[yi][0] = grid[yi][size_x-1] = TILE_WALL;
	for(xi=0; xi<size_x; xi++)
		grid[0][xi] = grid[size_y-1][xi] = TILE_WALL;
}

void generation(void)
{
	int xi, yi, ii, jj;

	for(yi=1; yi<size_y-1; yi++)
	for(xi=1; xi<size_x-1; xi++)
	{
		int adjcount_r1 = 0,
		    adjcount_r2 = 0;

		for(ii=-1; ii<=1; ii++)
		for(jj=-1; jj<=1; jj++)
		{
			if(grid[yi+ii][xi+jj] != TILE_FLOOR)
				adjcount_r1++;
		}
		for(ii=yi-2; ii<=yi+2; ii++)
		for(jj=xi-2; jj<=xi+2; jj++)
		{
			if(abs(ii-yi)==2 && abs(jj-xi)==2)
				continue;
			if(ii<0 || jj<0 || ii>=size_y || jj>=size_x)
				continue;
			if(grid[ii][jj] != TILE_FLOOR)
				adjcount_r2++;
		}
		if(adjcount_r1 >= params->r1_cutoff || adjcount_r2 <= params->r2_cutoff)
			grid2[yi][xi] = TILE_WALL;
		else
			grid2[yi][xi] = TILE_FLOOR;
	}
	for(yi=1; yi<size_y-1; yi++)
	for(xi=1; xi<size_x-1; xi++)
		grid[yi][xi] = grid2[yi][xi];
}

void printfunc(void)
{
	int ii;

	printf("W[0](p) = rand[0,100) < %i\n", fillprob);

	for(ii=0; ii<generations; ii++)
	{
		printf("Repeat %i: W'(p) = R[1](p) >= %i",
			params_set[ii].reps, params_set[ii].r1_cutoff);

		if(params_set[ii].r2_cutoff >= 0)
			printf(" || R[2](p) <= %i\n", params_set[ii].r2_cutoff);
		else
			putchar('\n');
	}
}

void printmap(void)
{
	int xi, yi;

	for(yi=0; yi<size_y; yi++)
	{
		for(xi=0; xi<size_x; xi++)
		{
			switch(grid[yi][xi]) {
				case TILE_WALL:  putchar('B'); break;
				case TILE_FLOOR: putchar(' '); break;
			}
		}
		putchar('\n');
	}
}



int main_gen(int x_in, int y_in, int fillprob_in, int r1_in, int r2_in, int reps_in)
{
	int ii, jj;

	size_x     = x_in;
	size_y     = y_in;
	fillprob   = fillprob_in;

	generations = 1;

	params = params_set = (generation_params*)malloc( sizeof(generation_params) * generations );

		params->r1_cutoff  = r1_in;
		params->r2_cutoff  = r2_in;
		params->reps = reps_in;
		params++;

	srand(time(NULL));

	initmap();

	for(ii=0; ii<generations; ii++)
	{
		params = &params_set[ii];
		for(jj=0; jj<params->reps; jj++)
			generation();
	}
	printfunc();
	printmap();
	return 0;
}
