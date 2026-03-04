#include<stdio.h>
int main(){

    int n, i,j,k,x ;
    printf("Enter the number of nodes : ");
    scanf("%d",&n);

    int routing_table[n][n];

    printf("Enter the routing table : ");

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("\n[%d][%d]",i,j);
            scanf("%d",&routing_table[i][j]);

        }
    }

    for(x=0;x<n;x++){
        
        for(i=0;i<n;i++){

            for(j=0;j<n;j++){

                for(k=0;k<n;k++){

                    if(routing_table[i][j]>routing_table[i][k]+routing_table[k][j]){
                        routing_table[i][j]=routing_table[i][k]+routing_table[k][j];

                    }

                }
            }
            
        
        }
        

    }

    printf("\n Distance Vector Table : \n");

    for(j=0;j<n;j++){

        for(k=0;k<n;k++){

                   
            printf("%d\t",routing_table[j][k]) ;        

        }
         
        printf("\n"); 
    }

}    