#define DO_CONCAT(x, y)     x ## y
#define CONCAT(x, y)        DO_CONCAT(x, y)
#define UNIQ_ID             CONCAT(name, __LINE__)