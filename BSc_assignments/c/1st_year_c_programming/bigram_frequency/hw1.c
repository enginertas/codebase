#include <stdio.h>

int Tot_Lang=0;
long diagram[10][27][27],Tot_Bgm[10];


/*getting all bigrams in input*/
int take_input(void){

	char c1=0,c2;
	int lang,i;

	while(1){
		c2=getchar();  /*take a character for testing*/
		
		if (c2=='#') { /*test it*/
			lang=getchar()-48;
			c1=0;
			Tot_Lang++;
			}
		
		else if (c2=='?'){  
			lang=0;
			c1=0;
			}
		
		else if (c2==EOF){
			diagram[0][c1][0]++; /*putting the last space*/	

		/*converting consecutive spaces to single space*/
			for(i=Tot_Lang;i>=0;i--)
				diagram[i][0][0]=0;
			return 0;
			}	
		
		else if (c2>=65 && c2<=90) {
			c2-=64;
			diagram[lang][c1][c2]++;
			c1=c2;
			}
		
		else {
			c2=0;
			diagram[lang][c1][c2]++;
			c1=0;
		     }
	}
}
/*counting total bigram numbers of languages*/
void total_bigram(void){
	
  int i,j,k;
  
  for(i=0;i<=Tot_Lang;i++)
	for(j=0;j<=26;j++)
	  for(k=0;k<=26;k++)
		Tot_Bgm[i]+=diagram[i][j][k];

}

/*finding dissimilarity of languages*/
int dissimilarity(void){
	
  int i,j,k,r;
  float temp,dis[10]={0,0,0,0,0,0,0,0,0,0},c;  

  for(i=1;i<=Tot_Lang;i++)
	for(j=0;j<=26;j++)
	  for(k=0;k<=26;k++){
     		c=((float)diagram[i][j][k]/Tot_Bgm[i])-((float)diagram[0][j][k]/Tot_Bgm[0]);
  	
		if(c<0) dis[i]-=c;
		else dis[i]+=c;
	  }
  
  temp=dis[1];
  r=1;
  for(i=2;i<=Tot_Lang;i++){ /*finding the most similar one*/
	
 	 if(dis[i]<=temp) {
	  r=i;
	  temp=dis[i];
	 }
	 else ;
  }
  return r;
}

int main(void){

	take_input();
	total_bigram();
	printf("%d",dissimilarity());

return 0;
}

