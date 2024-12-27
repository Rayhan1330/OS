#include <stdio.h>
#include <stdlib.h>


void display_matrix(int **arr,int c,int r){
	for(int i=0;i<c;i++){
		for(int j=0;j<r;j++){
			printf("%d ",arr[i][j]);		
		}
		printf("\n");	
	}
	printf("\n");	
}

void safety_seq(int **avl,int **max,int **alloc,int **need,int c,int r,int *safety,int *work){
    int *completed = (int *)malloc(c*sizeof(int));
    int *visit = (int *)malloc(c*sizeof(int));
    for(int i=0;i<c;i++){
        visit[i] = 0;
        completed[i] = 0;
    }

	for(int i=0;i<c;i++){
		for(int j=0;j<r;j++){
			need[i][j] = max[i][j] - alloc[i][j];
            if(need[i][j]<0) need[i][j] = 0;
		}
	}
	
    int no_of_proc=0;
    int brk_con=0;
    while(brk_con == 0){
        if(no_of_proc==c) break;
        for(int i=0;i<c;i++){
            int chk = 0;
            visit[i]++;
            if(completed[i]==1) continue;
            for(int j = 0;j<r;j++){
                if(need[i][j]>work[j]){
                    chk = 1;
                    break;
                }
            }
            if(chk==0 && completed[i]==0){
                completed[i]=1;
                safety[no_of_proc++] = i;
                for(int j=0;j<r;j++){
                    avl[i][j] = *(work + j);
                    work[j] = work[j] + alloc[i][j];
                    
                }
                
            }
            if(completed[i] == 0 && visit[i]>=2){
                brk_con=1;
                printf("\nUNSAFE STATE\n\n");
                break;
            }
        }
    }
    
		
}

int main(void){
	int **avl,**max,**need,**alloc;
	int *safety,*work;
	int c,r;
    int lc = 0;
	while(1){
		printf("1.Read data\n");
		printf("2.Print data \n");
		printf("3.Safety sequence \n");
		printf("4.Exit\n\n");
		int choice;
		printf("Enter your option: ");
		scanf("%d",&choice);
		if(choice==4) break;
		else if(choice==2){
            if(lc==0){
                printf("Enter some data first\n");
                continue;
            }
			printf("MAX\n\n");
			display_matrix(max,c,r);
			printf("ALLOTTED\n\n");
			display_matrix(alloc,c,r);
			printf("WORK \n\n");
			display_matrix(avl,c,r);
            printf("NEED \n\n");
            display_matrix(need,c,r);
            printf("AVAILABLE \n\n");
            for(int i=0;i<r;i++) printf("%d ",work[i]);
            printf("\n\n");
		}
		else if(choice==1){
            if(lc>=1){
                free(avl);
                free(max);
                free(need);
                free(alloc);
                free(safety);
                free(work);
            }
			printf("Number of processes: ");
			scanf("%d",&c);
			printf("Number of resources: ");
			scanf("%d",&r);
            safety = (int *)malloc(c*sizeof(int));
            work = (int *)malloc(r*sizeof(int));
			avl = (int **)malloc(c*sizeof(int *));
			for(int i=0;i<c;i++) avl[i] = (int *)malloc(r*sizeof(int));
			for(int i=0;i<r;i++){
				printf("Enter available resources of %c: ",i+65);
				scanf("%d",&work[i]);
			}
            printf("\n");
			max = (int **)malloc(c*sizeof(int *));
			for(int i=0;i<c;i++) max[i] = (int *)malloc(r*sizeof(int));
			for(int i=0;i<c;i++){
				for(int j=0;j<r;j++){
					printf("Enter maximum resources for P%d of type %c: ",i,j+65);
					scanf("%d",&max[i][j]);	
				}
                printf("\n");
			}
			alloc = (int **)malloc(c*sizeof(int *));
			for(int i=0;i<c;i++) alloc[i] = (int *)malloc(r*sizeof(int));
			for(int i=0;i<c;i++){
				for(int j=0;j<r;j++){
					printf("Enter allotted resources for P%d of type %c: ",i,j+65);
					scanf("%d",&alloc[i][j]);	
				}
                printf("\n");
			}
			need = (int **)malloc(c*sizeof(int *));
			for(int i=0;i<c;i++) need[i] = (int *)malloc(r*sizeof(int));
			safety_seq(avl,max,alloc,need,c,r,safety,work);

		}
        else if(choice==3){
            if(lc==0){
                printf("Enter some data first\n");
                continue;
            }
            for(int i=0;i<c;i++){
                printf("P%d,",safety[i]);
            }
            printf("\n\n");
        }
        lc++;
	}
		
}	
