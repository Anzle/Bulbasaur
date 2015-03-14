#include <stdio.h>
#include <string.h>
 
int main()
{
   char a[100], b[100];
 
   printf("Enter the first string\n");
   gets(a);
 
   printf("Enter the second string\n");
   gets(b);
 
   if (strcmp(a,b) == 0)
      printf("Entered strings are equal.\n");
   else
      printf("Entered strings are not equal.\n");
 
   return 0;
}

int main()
{
   int m, n, c, d, first[10][10], second[10][10], sum[10][10];
 
   printf("Enter the number of rows and columns of matrix\n");
   scanf("%d%d", &m, &n);
   printf("Enter the elements of first matrix\n");
 
   for (c = 0; c < m; c++)
      for (d = 0; d < n; d++)
         scanf("%d", &first[c][d]);
 
   printf("Enter the elements of second matrix\n");
 
   for (c = 0; c < m; c++)
      for (d = 0 ; d < n; d++)
            scanf("%d", &second[c][d]);
 
   printf("Sum of entered matrices:-\n");
 
   for (c = 0; c < m; c++) {
      for (d = 0 ; d < n; d++) {
         sum[c][d] = first[c][d] + second[c][d];
         printf("%d\t", sum[c][d]);
      }
      printf("\n");
   }
 
   return 0;
}

int main()
{
   char source[1000], destination[1000];
 
   printf("Input a string\n");
   gets(source);
 
   strcpy(destination, source);
 
   printf("Source string:      \"%s\"\n", source);
   printf("Destination string: \"%s\"\n", destination);
 
   return 0;
}

int main()
{
  int m, n, p, q, c, d, k, sum = 0;
  int first[10][10], second[10][10], multiply[10][10];
 
  printf("Enter the number of rows and columns of first matrix\n");
  scanf("%d%d", &m, &n);
  printf("Enter the elements of first matrix\n");
 
  for (c = 0; c < m; c++)
    for (d = 0; d < n; d++)
      scanf("%d", &first[c][d]);
 
  printf("Enter the number of rows and columns of second matrix\n");
  scanf("%d%d", &p, &q);
 
  if (n != p)
    printf("Matrices with entered orders can't be multiplied with each other.\n");
  else
  {
    printf("Enter the elements of second matrix\n");
 
    for (c = 0; c < p; c++)
      for (d = 0; d < q; d++)
        scanf("%d", &second[c][d]);
 
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++) {
        for (k = 0; k < p; k++) {
          sum = sum + first[c][k]*second[k][d];
        }
 
        multiply[c][d] = sum;
        sum = 0;
      }
    }
 
    printf("Product of entered matrices:-\n");
 
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++)
        printf("%d\t", multiply[c][d]);
 
      printf("\n");
    }
  }
 
  return 0;
}

int main()
{
   int m, n, c, d, matrix[10][10], transpose[10][10];
 
   printf("Enter the number of rows and columns of matrix\n");
   scanf("%d%d", &m, &n);
 
   printf("Enter the elements of matrix\n");
 
   for (c = 0; c < m; c++)
      for(d = 0; d < n; d++)
         scanf("%d",&matrix[c][d]);
 
   for (c = 0; c < m; c++)
      for( d = 0 ; d < n ; d++ )
         transpose[d][c] = matrix[c][d];
 
   printf("Transpose of entered matrix :-\n");
 
   for (c = 0; c < n; c++) {
      for (d = 0; d < m; d++)
         printf("%d\t",transpose[c][d]);
      printf("\n");
   }
 
   return 0;
}

int main()
{
   char string[100];
   int c = 0, count[26] = {0};
 
   printf("Enter a string\n");
   gets(string);
 
   while (string[c] != '\0')
   {
      /** Considering characters from 'a' to 'z' only
          and ignoring others */
 
      if (string[c] >= 'a' && string[c] <= 'z') 
         count[string[c]-'a']++;
 
      c++;
   }
 
   for (c = 0; c < 26; c++)
   {
      /** Printing only those characters 
          whose count is at least 1 */
 
      if (count[c] != 0)
         printf("%c occurs %d times in the entered string.\n",c+'a',count[c]);
   }
 
   return 0;
}