/*********************************************
 *
 *  (c) Borce Gjorgjievski
 *  Empirically Comparing HeapSort and MergeSort	 
 *
 *******************************************/

#define NUM 10
const int MAXSIZE=10000;


#include <stdlib.h>
#include <time.h>

int b[NUM]; /* external array needed for mergesort */
int comparisons = 0; /* number of comparisons in mergesort */   
int comps = 0;       /* number of comparisons in heapsort */

void merge(int data[], int first, int split, int last) 
{
  /* Merges the two halves into a temporary array, then copies
     the sorted elements back into the original array. */
  
  int index;
  int tracer1 = first;
  int tracer2 = split+1;
  int temp[MAXSIZE];
  
  index = first;
  
  /* Do this until one of the halves is emptied. */
  while (tracer1 <= split && tracer2 <= last) 
    {
      if (data[tracer1] < data[tracer2]) 
	temp[index++] = data[tracer1++];
      else 
	temp[index++] = data[tracer2++];
      ++comparisons;
    } 
  
  /* Now copy the leftover elements from the non-empty half. */
  while (tracer2 <= last)   /* right half is non-empty */
    temp[index++] = data[tracer2++];
  while (tracer1 <= split)  /* left half is non-empty */
    temp[index++] = data[tracer1++];
  
  /* Copy from temporary array back into data. */
  for (index = first; index <= last; ++index)
    data[index] = temp[index];
  return;
}

void merge_sort(int data[], int first, int last) 
{
  int split;
  
  if (first < last) 
    {
      split = (first + last)/2; 
      merge_sort(data, first, split);
      merge_sort(data, split + 1, last);
      merge(data, first, split, last);
    }
  return;
}

int downheap (int a[], int N, int k)
  {
    int j, v;

    v =a[k];
    while (k<=N/2)
      {
	j = k+k;
	if (j<N && a[j] < a[j+1]) 
	{
	  j++;
	  comps++;
	}
       if (v>= a[j]) break;
       a[k] = a[j]; 
       k=j;
    } /* while */
   a[k] = v;
  }

int heapsort (int a[], int N) 
{
  int k, t;

  for(k=N/2; k>= 0; k--) downheap(a, N, k);
  while (N > 0)
    {
      t = a[0];
      a[0] = a[N];
      a[N] = t;
      downheap(a, --N, 0);
    }
  return;
}

randomarray(int N, int a[])
{
  int i=0;

  if (N<1) return;
  srand(time(NULL));
  while (i < N) {
    a[i] = (int) rand() / 10000000;
    i++;
  }
}

printarray(int N, int a[])
{
  int i=0;

  if (N<1) return;
  while (i < N) {
    printf("element[%2d] = %12d\n", i, a[i]);
    i++;
  }
}

duplicatearray(int N, int a[], int b[])
{
  while (N) {
    --N; 
    b[N] = a[N];
  }
}

main () 
{
  int a[NUM], c[NUM];
  
  randomarray(NUM, a);
  printf ("********  Empirically comparing mergesort and heapsort\n");
  printf("We are sorting the following random array: \n");
  printarray (NUM, a);
  duplicatearray(NUM, a, c);

  merge_sort (a, 0, NUM-1);
  heapsort(c, NUM-1);
  printf ("Mergesort needed %d comparisons, while Heapsort needed %d comparisons\n", comparisons, comps);

  printf("Sorted array from mergesort: \n");
  printarray(NUM, a);
  printf("Sorted array from heapsort: \n");
  printarray(NUM, c);
}


