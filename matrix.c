// stdlib
#include <stdio.h>
#include <stdlib.h>

// local
#include "matrix.h"

#define ROWS 3
#define COLS 3

void initMatrix(matrix_t *matrix) {
  matrix->data = malloc(matrix->rows * sizeof(double *));
  if (!matrix->data) {
    freeMatrix(matrix);
    return;
  }
  for (int i = 0; i < matrix->rows; i++) {
    matrix->data[i] = malloc(matrix->cols * sizeof(double));
    if (!matrix->data[i]) {
      freeMatrix(matrix);
      return;
    }
  }
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      matrix->data[i][j] = 0;
    }
  }
}

void assignValueInMatrix(matrix_t *matrix, int row, int col, double val) {
  if (!matrix->data) {
    initMatrix(matrix);
  }
  if (!(row >= matrix->rows) && !(col >= matrix->cols) && !(row < 0) &&
      !(col < 0)) {
    matrix->data[row][col] = val;
  }
}

void multiplyMatrixByNumber(matrix_t *matrix, double val) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      matrix->data[i][j] = matrix->data[i][j] * val;
    }
  }
}

matrix_t *multiplyMatrices(matrix_t *mf, matrix_t *ms) {
  if (mf->cols != ms->rows) {
    return NULL;
  }
  int rows = mf->rows;
  int cols = ms->cols;
  matrix_t *m = malloc(sizeof(matrix_t));
  if (!m) {
    return NULL;
  }
  m->rows = rows;
  m->cols = cols;
  initMatrix(m);
  for (int i = 0; i < mf->rows; i++) {
    for (int j = 0; j < ms->cols; j++) {
      double sum = 0.0;
      for (int k = 0; k < mf->cols; k++) {
        sum += mf->data[i][k] * ms->data[k][j];
      }
      m->data[i][j] = sum;
    }
  }
  return m;
}

void freeMatrix(matrix_t *matrix) {
  if (!matrix) {
    return;
  }
  for (int i = 0; i < matrix->rows; i++) {
    free(matrix->data[i]);
  }
  free(matrix->data);
  free(matrix);
}

void stdoutMatrix(matrix_t *matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    printf("[ ");
    for (int j = 0; j < matrix->cols; j++) {
      printf("%.2f ", matrix->data[i][j]);
    }
    printf("]\n");
  }
}

int main(void) {
  matrix_t *mf = malloc(sizeof(matrix_t));
  mf->rows = ROWS;
  mf->cols = COLS;
  mf->data = NULL;
  assignValueInMatrix(mf, 0, 0, 1);
  assignValueInMatrix(mf, 0, 1, 2);
  assignValueInMatrix(mf, 0, 2, 3);

  assignValueInMatrix(mf, 1, 0, 4);
  assignValueInMatrix(mf, 1, 1, 5);
  assignValueInMatrix(mf, 1, 2, 6);

  assignValueInMatrix(mf, 2, 0, 7);
  assignValueInMatrix(mf, 2, 1, 8);
  assignValueInMatrix(mf, 2, 2, 9);

  //  stdoutMatrix(mf);
  //  multiplyMatrixByNumber(mf, 2.00);
  //  stdoutMatrix(mf);

  matrix_t *ms = malloc(sizeof(matrix_t));
  ms->rows = ROWS;
  ms->cols = COLS;
  ms->data = NULL;
  assignValueInMatrix(ms, 0, 0, 1);
  assignValueInMatrix(ms, 0, 1, 2);
  assignValueInMatrix(ms, 0, 2, 3);

  assignValueInMatrix(ms, 1, 0, 4);
  assignValueInMatrix(ms, 1, 1, 5);
  assignValueInMatrix(ms, 1, 2, 6);

  assignValueInMatrix(ms, 2, 0, 7);
  assignValueInMatrix(ms, 2, 1, 8);
  assignValueInMatrix(ms, 2, 2, 9);

  matrix_t *m = multiplyMatrices(mf, ms);
  stdoutMatrix(m);
  freeMatrix(mf);
  freeMatrix(ms);
  freeMatrix(m);
}
