#ifndef PARCER_H
#define PARCER_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned v_count;
  unsigned f_count;
  float* vertexes;
  unsigned* faces;

  float XYZ[2][3];
} Model;

Model* Parser(const char* path);
void CountAttribute(Model* model, FILE* file);
void LoadData(Model* model, FILE* file);

#endif  // PARCER_H
