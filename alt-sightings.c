#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> /* time_t, struct tm, time, localtime */

#include "myarray.h"

/* represents data about where a bird was seen  */
typedef struct {
  struct tm *localDT;   /* time, look at time.h */
  char *bird;           /* name of bird         */
  char *where;          /* location seen        */
} sighting_t;

/*
 * time_t datatype is a data type in the ISO C library defined for storing system
 * time values. These values are returned from the standard time() library function. This type is a typedef defined in the standard header
 *
 */


/* only thing needs to be initialized is time
   strings can be set to NULL                   */
void sighting_init(void *src) {

    time_t now;
    now = time (NULL);

  // $ man localtime : return value points to a statically allocated struct
  // Statically allocated objects should not be passed to free()
    struct tm *localDT;
    localDT = localtime (&now);

    ((sighting_t *) src)->localDT = localDT;
    ((sighting_t *) src)->bird = NULL;
    ((sighting_t *) src)->where = NULL;
}

/* copy over everything */
void sighting_copy(void *_dst, const void *_src)
{


  //pointer cast:
  sighting_t *d = ( sighting_t *)_dst;
  sighting_t *s = ( sighting_t *)_src;

  // reallocate
  d->localDT = s->localDT;
  d->bird = strdup( s->bird );
  d->where = strdup( s->where );

}

/* free everything */
void sighting_dtor(void *_elt) {

  sighting_t *e = ( sighting_t *)_elt;

  // dynamically allocated:
  //  char *bird;
  //  char *where;


  if( e->bird != NULL )
  {
    free( e->bird );
  }

  if( e->where != NULL )
  {
    free( e->where );
  }

}

// struct inline initilization : arrangement of functions must match
// controlBlock struct delaration
controlBlock sighting_cb = {sizeof(sighting_t), sighting_init, sighting_copy, sighting_dtor};

/* method to build a NEW sighting, just for harness */
sighting_t *constructSighting(char *bird, char *where) {

    sighting_t* sight = malloc(sizeof(sighting_t));   // equivalent to NEW in C++
    sighting_cb.init( sight );

    sight-> bird = strdup(bird);
    sight-> where = strdup(where);
    return sight;


}

/* helper method to print out date */
char *printRep4DT(struct tm *localDT) {
  char printBuf[256];
  strftime (printBuf, 256, "%a %D %r", localDT);
  char *printableDT = strdup(printBuf);
  return printableDT;
}

/* another helper method to print out date */
void display(sighting_t * sighting) {
  char *printRep = printRep4DT(sighting->localDT);
  printf("[%s] %s at %s\n", printRep, sighting->bird, sighting->where);
  free(printRep);
}

/* test harness */
int main() {
  myArray *sightings;
  sighting_t *sighting;

  sighting_t *seeds[] = {
    constructSighting("Robin", "College Woods"),
    constructSighting("Screeching Owl", "College Woods"),
    constructSighting("Yellow Belly Finch", "Oyster River Forest")
  };

  sightings = newMyArray(&sighting_cb);

  for(int i = 0; i < sizeof(seeds)/sizeof(sighting_t*); i++) {
    pushMyArray(sightings, seeds[i]);
  }
  printf("length %d\n", lengthOfMyArray(sightings));

  sighting = NULL;
  while( (sighting = (sighting_t*) nextElementOfMyArray(sightings,sighting))) {
    display(sighting);
  }

  printf("length %d\n", lengthOfMyArray(sightings));
  printf("capacity %d\n", capacityOfMyArray(sightings));
  resizeMyArray(sightings, 4);

  printf("length %d\n", lengthOfMyArray(sightings));
  printf("capacity %d\n", capacityOfMyArray(sightings));

  sighting = NULL;
  while( (sighting = (sighting_t*) nextElementOfMyArray(sightings,sighting))) {
    display(sighting);
  }
  printf("remove last index\n");
  popMyArray(sightings);


  printf("inserting in the middle\n");
  sighting = constructSighting("Bluebird", "Mill Pond");
  insertAtMyArray(sightings, sighting, 3);
  sighting = constructSighting("Red Winged Blackbird", "Mill Pond");
  insertAtMyArray(sightings, sighting, 3);

  sighting = NULL;
  while( (sighting = (sighting_t*) nextElementOfMyArray(sightings,sighting))) {
    display(sighting);
  }

  freeMyArray(sightings);

  return 0;
}
