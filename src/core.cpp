#include "core.h"

Core *
core_get()
{
  static Core *result;
  if (result == NULL) {
    result = (Core *)malloc(sizeof(Core));
    memset(result, 0, sizeof(Core));
  }
  return result;
}
