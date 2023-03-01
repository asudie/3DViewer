#include "parser.h"

Model *Parser(const char *path) {
  FILE *file = fopen(path, "r");

  Model *temp = NULL;
  if (!file) {
    printf("File (%s) is not opened", path);
  } else {
    temp = (Model *)malloc(sizeof(Model));

    CountAttribute(temp, file);
    LoadData(temp, file);
  }
  pclose(file);
  return temp;
}

void CountAttribute(Model *model, FILE *file) {
  char *line = NULL;
  size_t size = 0;

  model->v_count = 0U;
  model->f_count = 0U;

  while ((int)getline(&line, &size, file) != -1) {
    if (!strncmp(line, "v ", (size_t)2)) {
      model->v_count++;
    }
    if (!strncmp(line, "f ", (size_t)2)) {
      model->f_count++;
    }
  }
  rewind(file);
  free(line);
}

void LoadData(Model *model, FILE *file) {
  char *line = NULL;
  size_t size = 0, idx_v = 1, idx_f = 0;

  model->vertexes =
      (float *)malloc(3U * ((model->v_count + 1U)) * sizeof(float));
  model->faces = (unsigned *)malloc(3U * model->f_count * sizeof(unsigned));

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == 0) {
        model->XYZ[i][j] = INFINITY;
      } else {
        model->XYZ[i][j] = -INFINITY;
      }
    }
  }

  while ((int)getline(&line, &size, file) != -1) {
    if (!strncmp(line, "v ", (size_t)2)) {
      char *anchor = line;
      ++anchor;
      for (unsigned i = 0; i < 3; ++i) {
        model->vertexes[idx_v * 3U + i] = (float)strtod(anchor, &anchor);

        if (model->XYZ[0][i] > model->vertexes[idx_v * 3U + i]) {
          model->XYZ[0][i] = model->vertexes[idx_v * 3U + i];
        } else if (model->XYZ[1][i] < model->vertexes[idx_v * 3U + i]) {
          model->XYZ[1][i] = model->vertexes[idx_v * 3U + i];
        }
      }
      ++idx_v;
    } else if (!strncmp(line, "f ", (size_t)2)) {
      char *anchor = line;
      ++anchor;
      for (unsigned i = 0; i < 3U && *anchor != '\n'; ++i) {
        model->faces[idx_f * 3U + i] = (unsigned)strtod(anchor, &anchor);
        while (*anchor != ' ' && *anchor != '\n') {
          ++anchor;
        }
      }
      ++idx_f;
    }
  }

  rewind(file);
  free(line);
}
