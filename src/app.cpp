#include "app.h"

App *
app_get()
{
  static App *result;
  if (result == NULL) {
    result = (App *)malloc(sizeof(App));
    memset(result, 0, sizeof(App));
  }
  return result;
}
