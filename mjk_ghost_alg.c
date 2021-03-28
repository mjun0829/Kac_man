#include <stdio.h>
#include <stdlib.h>

int **mk_2d_array_pointer(int **, int row, int col);
void free_2d_array_pointer(int **, int row);
void print_2d_array(int **, int row, int col);
int **moving(int **, int row, int col);

enum var{
	Wall = 100
};

int **mk_2d_array_pointer(int **mat, int row, int col){
	mat = malloc(sizeof(int *) * row);
        for(int x = 0; x < row; x++){
                mat[x] = malloc(sizeof(int) * col);
                for(int y = 0; y < col; y++){
                        mat[x][y] = 0;
			if(x == row - 2 || y == col - 2){
				mat[x][y] = Wall;
			}
                }
        }
	mat[0][col - 2] = 0;
	mat[row - 1][col - 2] = 0;
	mat[row - 2][0] = 0;
	mat[row - 2][col - 1] = 0;
	mat[row - 3][1] = Wall;
	
        return mat;
}

void free_2d_array_pointer(int **mat, int row){
        for(int x = 0; x < row; x++){
                free(mat[x]);
        }
        free(mat);
}

void print_2d_array(int **mat, int row, int col){
	for(int x = 0; x < row; x++){
		for(int y = 0; y < col; y++){
			if(mat[x][y] != Wall){
				printf("%d ", mat[x][y]%10);
			}
			if(mat[x][y] == Wall){
				printf("W ");
			}
		}
		printf("\n");
	}
}

int **moving(int **mat, int row, int col){
	int ghost_x = 0, ghost_y = 0, count = 0;
	int desti_x = row - 1, desti_y = col - 1;
	while(desti_x - ghost_x != 0 || desti_y - ghost_y != 0){
		printf("fuck %d %d \n", ghost_x, ghost_y);
		count++;
		mat[ghost_x][ghost_y] = count;
		if((desti_x - ghost_x == desti_y - ghost_y) && mat[ghost_x + 1][ghost_y] != Wall){
			ghost_x++;
			continue;
		}
		if((desti_x - ghost_x > desti_y - ghost_y) && mat[ghost_x + 1][ghost_y] != Wall){
			ghost_x++;
			continue;
		}
		if((desti_x - ghost_x < desti_y - ghost_y) && mat[ghost_x][ghost_y + 1] != Wall){
			ghost_y++;
			continue;
		}
		if(mat[ghost_x + 1][ghost_y] == Wall && mat[ghost_x][ghost_y + 1] != Wall){
			ghost_y++;
			continue;
		}
		if(mat[ghost_x][ghost_y + 1] == Wall && mat[ghost_x + 1][ghost_y] != Wall){
			ghost_x++;
			continue;
		}
		if(mat[ghost_x + 1][ghost_y] == Wall && mat[ghost_x][ghost_y + 1] == Wall){
			int end_x = ghost_x + 2;
			while(ghost_x != end_x){
				while(mat[ghost_x + 1][ghost_y] == Wall && mat[ghost_x][ghost_y - 1] != Wall){
					printf("fuck %d %d \n", ghost_x, ghost_y);
					count++;
					mat[ghost_x][ghost_y] = count;
					ghost_y--;
				}
				while((ghost_x != end_x) && mat[ghost_x + 1][ghost_y] != Wall){
					printf("fuck %d %d \n", ghost_x, ghost_y);
					count++;
					mat[ghost_x][ghost_y] = count;
					ghost_x++;
					
				}
				while(mat[ghost_x][ghost_y - 1] == Wall && mat[ghost_x - 1][ghost_y] != Wall){
                                        printf("fuck %d %d \n", ghost_x, ghost_y);
                                        count++;
                                        mat[ghost_x][ghost_y] = count;
                                        ghost_x--;
                                }
				while((ghost_x != end_x) && mat[ghost_x][ghost_y - 1] != Wall){
                                        printf("fuck %d %d \n", ghost_x, ghost_y);
                                        count++;
                                        mat[ghost_x][ghost_y] = count;
                                        ghost_y--;
					if(mat[ghost_x + 1][ghost_y] != Wall){
						break;
					}
                                }			
			}
		}
	}
	return mat;
}

int main(){
	int **mat, row = 10, col = 10;
	mat = mk_2d_array_pointer(mat, row, col);
	mat = moving(mat, row, col);
	print_2d_array(mat, row, col);
	free_2d_array_pointer(mat, row);
}
