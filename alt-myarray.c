#include "myarray.h"




// This private function returns (conceptually) a[j].
void* _altElementFromIndexOfMyArray(myArray *a, int j)
{

  // the array is just a block of
  // memory pointed to by a->d (see myarray.h for a description of myArray)

  // The block of memory pointed to by a->d is a block of bytes
  // so the jth element (a->d[j]) is at offset a->d + j.

  // But each element of myArray will be at
  // offset (a->d + (j * size of the element defined by controlBlock)).


    return  ( a->d + ( j* (a->cb ).sz  ));
}

//calls _elementFromIndexOfMyArray after checking j is less than lenght of array
void* altElementFromIndexOfMyArray(myArray *a,int j){

  if( j < lengthOfMyArray(a) )
  {
    return _altElementFromIndexOfMyArray(a,j);
  }
  else{
    return NULL; // there's no elements more than or equal to j
  }

}

//inserts a new array element p into myArray "a" at position j
void altInsertAtMyArray(myArray *a, void *p, unsigned j)
{


//if j is greater than length of array, it will resize the array
//using altReserveMyArray()
  if( j >= lengthOfMyArray(a) )
  {

    // make sure enough space in array to insert element at position j
    altReserveMyArray( a, j - lengthOfMyArray(a) );

  }
  else{
    // move elements j to the ( lengthOfMyArray -1 )
    memmove( altElementFromIndexOfMyArray( a, j+1 ),
    altElementFromIndexOfMyArray ( a,j ), (  (a->index -j )*(a->cb).sz  )  );


  }

   //if copy function from controlBlock does not exist, the use memcpy.
	if( a->cb.copy ) // if this was not null, then function exists
	{
		  a->cb.copy(altElementFromIndexOfMyArray ( a,j ), p );
	}


  a->index++;

  //  return insertAtMyArray(a,p,j);
}

//determines if capacity is enough to support "by" more elements
void altReserveMyArray(myArray *a, int by){


 //size allocated for array a is a->capacity

 //determine if capacity is enough to support "by" more elements
 if(  a->capacity < by  )
 {
 
   if ( a->capacity == 0 )
   {
     a->capacity = 2;
   }
   while( a->capacity < lengthOfMyArray(a) + by )
   {
           a->capacity = (a->capacity)*2;
   }
      // copy explicit value of char* d into a


    a->d = ( char* )realloc( a->d, a->capacity);
   // length of myArray "a" including container and data "d"
   // is size_of( a->d )
   // length of just the container i.e. myArray "a"
   // is size_of( sightings_t)
   //
   // size_of( a->d ) / size_of(sightings_t)
   // is the length of d in that array but without the array.



 }

}


// This function resizes the array by:::
void altResizeMyArray(myArray *dst, int num){




  // (1) deleting all elements whose index is greater than or equal to num
  if( dst->index >= num )
  {
    int counterAL = lengthOfMyArray(dst) - num;

    if( dst->cb.dtor ) // if this was not null to see if the dtor function is there
    {
      eraseMyArray(dst, lengthOfMyArray(dst) , counterAL) ;
      // for loop from index to num using dtor controlBlock
    
    }


  }

  // (2)reserving space for new elements if num is greater than or equal to length
  // of the array
  if( num >= ( lengthOfMyArray(dst) ) )
  {
    // call altReserveMyArray or reserveMyArray ??
    altReserveMyArray( dst, num );

    // After the space is reserved,
    // all elements in the new space (those whose index greater
    // than or equal to num) are initialized (assuming the init function isn't NULL)

    // If init is NULL, then new space is simply zeroed out using memset
    if ( (dst->cb).init == NULL );
    {

      memset( dst->d,0, (dst->cb).sz ) ;//string, value, number of bytes set to the value

    }
  }






  // Note that sizeof is the size in units of char, which
  // is why the division of " sizeof (int)"" is needed.
  // Sizeof is not a function.
  // The parentheses are only needed when the argument is a type,
  // if the argument is a cast-like expression (e.g. sizeof (int)).
  // It is possible to use without naming actual types, by doing sizeof on data instead.
dst->index = num;


    //return resizeMyArray(dst,num);
}
