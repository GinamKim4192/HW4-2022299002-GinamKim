#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [김기남]  [2022299002] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}


int** create_matrix(int row, int col)
{
    // 배열의 Index는 양수여야함.
	if (row <= 0 || col <= 0) {
		printf("row and col must be positive number\n");
		return NULL;
	}
    /* row를 동적메모리로 할당하고 row안에
    각각의 스칼라값에 따른 동적메모리로 한 번 더 할당함.*/
	int** matrix = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * col);
	}
    // 행렬은 빈 값이 되어서는 안됨.
	if (matrix == NULL) {
		printf("Current matrix is Null.\n");
		return NULL;
	}

	return matrix;
}

void print_matrix(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) {
		printf("row and col must be positive number\n");
		return ;
	}
    /* 행(column)우선 방식으로 행렬을 반복문을 돌며 각 스칼라값을 출력함.
       행(row)이 바뀔때마다 줄바꿈을 하여 다음행에 접근함. */
    for (int m_row = 0; m_row < row; m_row++) {
		for (int m_col = 0; m_col < col; m_col++)
			printf("%d ", matrix[m_row][m_col]);
		printf("\n");
	}
	 if (matrix == NULL) {
		printf("Current matrix is Null.\n");
		return ;
	}
}


int free_matrix(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) {
		printf("row and col must be positive number\n");
        return -1;
	}
    /* 동적 메모리 할당은 마지막에 할당을 반드시 해주어야 하므로
       각 스칼라 값을 할당해제 한 뒤 마지막에 시작주소가 할당된 matrix또한 해제해줌.*/
	for (int m_row = 0; m_row < row; m_row++) {
		free(matrix[m_row]);
	}
	free(matrix);
    return 1;
}


int fill_data(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) {
		printf("row and col must be positive number\n");
		return -1;
	}
    /* 행 우선 방식으로 접근하여 각 행렬의 스칼라 값을 할당함.
       이중 반복문을 사용하여 특정 행에 대한 열 할당이 종료되었을 때,
       다음 행에 접근하여 열(column)들을 할당함.*/
    for (int m_row = 0; m_row < row; m_row++)
		for (int m_col = 0; m_col < col; m_col++)
			matrix[m_row][m_col] = rand() % 20;
    return 1;
    if (matrix == NULL) {
		printf("Current matrix is Null.\n");
		return -1;
	}
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("row and col must be positive number\n");
        return -1;
    }
    /* 행 우선 방식으로 두 행렬의 동일한 row,col위치에 있는 각 스칼라값들을 반복문을 돌며 더함
       특정 row, col에서 더한 값은 matrix_reuslt의 해당 위치에 할당함.*/
    int** matrix_result = create_matrix(row, col);
    for (int m_row = 0; m_row < row; m_row++)
        for (int m_col = 0; m_col < col; m_col++)
            matrix_result[m_row][m_col] = matrix_a[m_row][m_col] + matrix_b[m_row][m_col];
    print_matrix(matrix_result, row, col);
    free_matrix(matrix_result, row, col);
    return 1;
    if (matrix_a == NULL || matrix_b ==NULL) {
        printf("Current matrix is Null.\n");
        return -1;
    }
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("row and col must be positive number\n");
        return -1;
    }
    /* 행 우선 방식으로 두 행렬의 동일한 row,col위치에 있는 각 스칼라값들을 반복문을 돌며 뺌
       특정 row, col에서 뺀 값은 matrix_reuslt의 해당 위치에 할당함.*/
    int** matrix_result = create_matrix(row, col);
    for (int m_row = 0; m_row < row; m_row++)
        for (int m_col = 0; m_col < col; m_col++)
            matrix_result[m_row][m_col] = matrix_a[m_row][m_col] - matrix_b[m_row][m_col];
    print_matrix(matrix_result, row, col);
    free_matrix(matrix_result, row, col);
    return 1;
    if (matrix_a == NULL || matrix_b == NULL) {
        printf("Current matrix is Null.\n");
        return -1;
    }
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	if (row <= 0 || col <= 0) {
		printf("row and col must be positive number\n");
		return -1;
	}
    /* 2차원의 전치행렬은 matrix_a[row][col]에 할당된 값(allocated_value)을
       matrix_b[col][row]에 위에서 할당된 값(allocated_value)을 할당해줌. */
	for (int m_row = 0; m_row < row; m_row++) {
		for (int m_col = 0; m_col < col; m_col++)
			matrix_t[m_row][m_col] = matrix[m_col][m_row];
    return 1;
	}
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Current matrices are Null.\n");
		return -1;
	}
}

int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_result = create_matrix(row, row);
	if (row <= 0 || col <= 0) {
		printf("row and col must be positive number\n");
		return -1;
	}
    /* 행렬의 곱은 A행렬의 특정 행(또는 열)들의 값과
       B행렬의 특정 열(또는 행)들의 각 원소들을 곱한 후 더해준 값임.
       따라서 누적된 temp의 값을 특정 위치에 값을 할당 한 후
       0으로 초기화를 해줌*/
	for (int m_row = 0; m_row < row; m_row++) {
		for (int t_row = 0; t_row < row; t_row++) {
			int temp = 0;
			for (int b_col = 0; b_col < col; b_col++)
				temp += matrix_a[m_row][b_col] * matrix_t[b_col][t_row];
			matrix_result[m_row][t_row] = temp;
		}
	}

    print_matrix(matrix_result, row, col);
    return 1;
    if (matrix_t == NULL || matrix_result ==NULL) {
		printf("Current matrices are Null.\n");
		return -1;
	}

}