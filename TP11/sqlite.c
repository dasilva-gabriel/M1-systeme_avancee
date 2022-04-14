
#define LEN 64

typedef struct query {
   int select;
   char from[LEN];
   int where;
   char equals[LEN];
} query;