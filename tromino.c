#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//creates matrix
int** createTromino(int n, int r, int c){
  int i, j, random;
  int** rows = malloc(n*sizeof(float*));
  for (int i=0; i < n; ++i)
  {
    rows[i]= malloc(n*sizeof(float));
    for(j = 0; j < n; j++){
      random = rand() % 10;
      rows[i][j] = random;
    }
  }
  rows[r][c] = 'X';
  return rows;
}

void displayMatrix(int** matrix, int n, int r, int c){
  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      if(i == r && j == c) 
        printf("X ");
      else
        printf("%d ", -matrix[i][j]);
    }
    printf("\n");
  }
}

int dd = 1;

void trominoTile(int** matrix, int n, int r, int c, int rowMin, int rowMax, int colMin, int colMax){
  int i, j, k, l;
  int x1, y1, x2, y2, x3, y3, x4, y4;
  int rr = -dd;
  dd++;
  //base case
  if(n == 2){
    /* displayMatrix(matrix, n); */
    for(i = rowMin; i < rowMax; i++){
      for(j = colMin; j < colMax; j++){
        if(matrix[i][j] >= 0){
          matrix[i][j] = rr;
        }
      }
    }
    return;
  }
  //insert tromino at middle


  x1 = (rowMax - rowMin)/2 - 1;
  y1 = (colMax - colMin)/2 - 1;

  x2 = (rowMax - rowMin)/2 - 1;
  y2 = (colMax - colMin)/2;

  x3 = (rowMax - rowMin)/2;
  y3 = (colMax - colMin)/2 - 1;

  x4 = (rowMax - rowMin)/2;
  y4 = (colMax - colMin)/2;

  if(r < (rowMax-rowMin)/2 && c < (colMax-colMin)/2) {
    x1 = r;
    y1 = c;
    matrix[x2][y2] = rr;
    matrix[x3][y3] = rr;
    matrix[x4][y4] = rr;
  }

  if(r < (rowMax-rowMin)/2 && c >= (colMax-colMin)/2) {
    x2 = r;
    y2 = c;
    matrix[x1][y1] = rr;
    matrix[x3][y3] = rr;
    matrix[x4][y4] = rr;
  }

  if(r >= (rowMax-rowMin)/2 && c < (colMax-colMin)/2) {
    x3 = r;
    y3 = c;
    matrix[x1][y1] = rr;
    matrix[x2][y2] = rr;
    matrix[x4][y4] = rr;
  }

  if(r >= (rowMax-rowMin)/2 && c >= (colMax-colMin)/2) {
    x4 = r;
    y4 = c;
    matrix[x1][y1] = rr;
    matrix[x2][y2] = rr;
    matrix[x3][y3] = rr;
  }

  //recursion
  trominoTile(matrix, n/2, x1, y1, rowMin, rowMax/2, colMin, colMax/2);
  trominoTile(matrix, n/2, x2, y2, rowMin, (rowMax-rowMin)/2, (colMax-colMin)/2, colMax);
  trominoTile(matrix, n/2, x3, y3, rowMax/2, rowMax, colMin, colMax/2);
  trominoTile(matrix, n/2, x4, y4, rowMax/2, rowMax, colMax/2, colMax);
}

int main(int argc, char *argv[]){
  if(argc >= 4){
    srand((unsigned int)time(NULL));
    int n = atoi(argv[1]);
    int r = atoi(argv[2]);
    int c = atoi(argv[3]);
    if(n < 1 || ((n == 1) && (r >= 2)) || ((n == 1) && (c >= 2))){
      printf("Please provide appropriate size and coordinates\n");
      return 0;
    }
    int p = pow(2, n);
    if(p <= r || p <= c){
      printf("Please provide appropriate size and coordinates.\n");
      return 0;
    }
    //creating tromino
    int** tromino = createTromino(p, r, c);
    trominoTile(tromino, p, r, c, 0, p, 0, p);
    displayMatrix(tromino, p, r, c);

    for(int i=0; i<p; i++)
      free(tromino[i]);
    free(tromino);
    return 0;
  }
  else{
    printf("Three inputs are required as command line argument.\n");
  }
}
