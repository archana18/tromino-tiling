//tromino.o: tromino.c 
	//gcc -static tromino.c -lm -o tromino.out
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int tile_count = 0;
void create_mat(int size, int mat[][size]);
void display_mat(int size, int mat[][size]);
void create_mat(int size, int mat[][size])
{
  int i, j;
  for(i = 0; i < size; i ++)
    for(j = 0; j < size; j ++)
        mat[i][j] = 0;
}


void display_mat(int size, int mat[][size])
{
  int i, j;
  for(i = 0; i < size; i ++)  
    for(j = 0; j < size; j ++)
    {
      if(mat[i][j] == -1)      
        printf("%5c", 'X');
      else      
        printf("%5d", mat[i][j]);      
    }
    printf("\n");  
}


void tromino_tile(int actual_size, int current_size, int mat[][actual_size], int start_x, int start_y, int hole_x, int hole_y)
{
  int i, j;
  tile_count ++;
  if(current_size == 2 )
  {
    for(i = start_x; i < start_x + current_size; i ++)
      for(j = start_y; j < start_y + current_size; j ++)
      {
        if(hole_x != i || hole_y != j)
        {
          mat[i][j] = tile_count;
        }
      }
  }
  else
  {
    int new_size = current_size / 2;
    int new_hole_x , new_hole_y;
    int new_count = tile_count;
    if(hole_x < start_x + new_size && hole_y < start_y + new_size)
      tromino_tile(actual_size, new_size, mat, start_x, start_y , hole_x, hole_y);
    else
    {
      new_hole_x = start_x + new_size - 1;
      new_hole_y = start_y + new_size - 1;
      mat[new_hole_x][new_hole_y] = new_count;
      tromino_tile(actual_size, new_size, mat, start_x, start_y , new_hole_x, new_hole_y);
    }

    if(hole_x < start_x + new_size && hole_y >= start_y + new_size)
      tromino_tile(actual_size, new_size, mat, start_x,  start_y + new_size , hole_x, hole_y);
      
    else
    {
      new_hole_x = start_x + new_size - 1;
      new_hole_y = start_y + new_size;
      mat[new_hole_x][new_hole_y] = new_count;
      tromino_tile(actual_size, new_size, mat, start_x, start_y + new_size , new_hole_x, new_hole_y);
    }

    if(hole_x >= start_x + new_size && hole_y < start_y + new_size)
    
      tromino_tile(actual_size, new_size, mat, start_x + new_size, start_y , hole_x, hole_y);
    
    else
    {
      new_hole_x = start_x + new_size ;
      new_hole_y = start_y + new_size - 1;
      mat[new_hole_x][new_hole_y] = new_count;
      tromino_tile(actual_size, new_size, mat, start_x + new_size, start_y , new_hole_x, new_hole_y);
    }

    if(hole_x >= start_x + new_size && hole_y >= start_y + new_size)
    
      tromino_tile(actual_size, new_size, mat, start_x + new_size, start_y + new_size, hole_x, hole_y);
    
    else
    {
      new_hole_x = start_x + new_size ;
      new_hole_y = start_y + new_size ;
      mat[new_hole_x][new_hole_y] = new_count;
      tromino_tile(actual_size, new_size, mat, start_x + new_size, start_y +new_size, new_hole_x, new_hole_y);
    }
  }
}

void trominoTile(int size, int mat[][size], int hole_x, int hole_y)
{
  tromino_tile(size, size, mat, 0, 0, hole_x, hole_y);
}

void main( int args, char * argv[])
{
  int s, hole_x, hole_y; 
  s = atoi(argv[1]);
  s = pow(2, s);
  int mat[s][s];
  hole_x = atoi(argv[2]);
  hole_y = atoi(argv[3]);
  create_mat(s, mat);
  mat[hole_x][hole_y] = -1;
  trominoTile(s, mat, hole_x, hole_y);
  display_mat(s, mat); 
}
