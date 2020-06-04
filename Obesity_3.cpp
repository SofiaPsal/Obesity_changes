#include <vector>
#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <dos.h>
#include <conio.h>
#include <windows.h>

using namespace std;
const int size=40;

class point{
	
	public:
		
	vector<vector<int> >grid;
	vector<vector<int> >generate;
	vector<vector<int> >risks;
	vector<int> store;
	vector<vector<int> >limit;
	vector<vector<int> >ho1;
	vector<vector<int> >ho2;
	
	int state;
	int times=0;
	int total=0;
	int sum=0;
	bool flag=false;
	bool f=false;
	int count=0;
	int counter=0;
	int t=0;
	int c1,c2,c3,c4;
	int tl=10;
	int ts=4;

//Συνάρτηση για το χρωματισμό των κελιών του πλέγματος ανάλογα με την κατάστασή τους		
void drawLine(int x, int y){
	
	int l=7;
	if(state==0)
        setcolor(5);
    else if(state==1)
        setcolor(15);
    else if(state==2)
    	setcolor(14);
    else if(state==3)
    	setcolor(2);
    else
    	setcolor(0);
            
for(int i=0; i<5; i++)
    line(x*l+20,y*l+i,x*l+25,y*l+i);
       
}

bool compare(int a, int b){
	bool n=false;
	
	for(int i=0; i<store.size(); i+=2){
		
			if(a==store[i] && b==store[i+1]){
				
				generate[a][b]=3;
				n=true;
				return n;
			}
		
	}
}


//Συνάρτηση για την εφαρμογή των κανόνων μετάβασης καταστάσεων
void newstate(int osum1,int hsum1,int osum2, int hsum2,int i,int j){
bool s=compare(i,j);

	int vou=-3;
	int vl=-1;
	int vhl=2;

	
	float ah1,ah2,ao1,ao2,ar;
	//Ορισμός των παραμέτρων επιρροής
	ah1=1;
	ah2=0.5;
	ao1=1;
	ao2=0.5;
	ar=0.5;
	int stoixeio=grid[i][j];
	//Προσθήκη των παρακάτω σχολίων για την εφαρμοφή του 1ου είδους παρεμβάσεων
	
	//if(osum1+osum2>5 && s==false){
	//	store.push_back(i);
	//	store.push_back(j);
	//	risks[i][j]-=3;
	//}
	int risk=risks[i][j];
//Υπολογισμός του μετρητή HO(t) για κάθε άτομο του πλέγματος
//Προσθήκη των παρακάτω σχολίων για την εφαρμοφή του 1ου είδους παρεμβάσεων
//if(osum1+osum2>20 && stoixeio<=1){
//		ao1=ah1=0.5;
//		ao2=ah2=0.25;
//		ho2[i][j]= -ar*risk - ah1*hsum1  - ah2*hsum2 + ao1*osum1 + ao2*osum2 + ho1[i][j];
//	}else{
	ho2[i][j]= -ar*risk + ah1*hsum1 + ah2*hsum2 - ao1*osum1 - ao2*osum2 + ho1[i][j];
//}	
	
 	int ho=ho2[i][j];
 	limit[i][j]-=1;
 	//Αν το άτομο είναι παχύσαρκο μπορεί να μεταβεί στην κατάσταση οριακά παχύσαρκος
 	if(stoixeio==0){
 		if(limit[i][j]<=0){
 			if(ho<vou){		
			generate[i][j]=0;
			ho1[i][j]=ho-vou;
			
			}else{
				generate[i][j]=1;
				ho1[i][j]=0;
				limit[i][j]=tl;
						
		}
	}else{
		generate[i][j]=0;
		ho1[i][j]=ho-vou;
	}
		
	//Αν το άτομο είναι οριακά παχύσαρκο μπορεί να μεταβεί στην κατάσταση παχύσαρκος, οριακά υγιής και υγιής
	}else if(stoixeio==1){
		if(limit[i][j]<=0){
			if(ho<vou){		
				generate[i][j]=0;
				ho1[i][j]=ho-vou;
				limit[i][j]=ts;
			}else if(ho<vl){
				generate[i][j]=1;
				ho1[i][j]=0;
			}else if(ho<vhl){
				generate[i][j]=2;
				ho1[i][j]=0;
				limit[i][j]=tl;
			}else if(ho>=vhl){
				generate[i][j]=3;
				ho1[i][j]=ho-vhl;
				limit[i][j]=ts;
			}
		}else{
			generate[i][j]=1;
		}
		
	//Αν το άτομο είναι οριακά υγιές μπορεί να μεταβεί στην κατάσταση παχύσαρκος, οριακά παχύσαρκος και υγιής
	}else if(stoixeio==2){
		if(limit[i][j]<=0){
			if(ho<vou){
				generate[i][j]=0;
				ho1[i][j]=ho-vou;
				limit[i][j]=ts;
			}else if(ho<vl){
				generate[i][j]=1;
				ho1[i][j]=0;
				limit[i][j]=tl;
			}else if(ho<vhl){
				generate[i][j]=2;
				ho1[i][j]=0;
				
			}else if(ho>=vhl){
				generate[i][j]=3;
				ho1[i][j]=ho-vhl;
				limit[i][j]=ts;
			}
		}else{
			generate[i][j]=2;
		}
		
	//Αν το άτομο είναι υγιές μπορεί να μεταβεί στην κατάσταση οριακά υγιής	
	}else if(stoixeio==3){
		if(limit[i][j]<=0){
			if(ho<vhl){
				generate[i][j]=2;
				ho1[i][j]=0;
				limit[i][j]=tl;
			}else if(ho>=vhl){
				generate[i][j]=3;
				ho1[i][j]=ho-vhl;
			}
		}else{
			generate[i][j]=3;
			ho1[i][j]=ho-vhl;
		}
		
	//Αν το κελί είναι κενό παραμένει κενό
	}else if(stoixeio==4){
		generate[i][j]=4;
	}
}
//Συνάρτηση που ελέγχει αν το πλέγμα βρίσκεται σε κατάσταση ισορροπίας
bool stable(){
flag=true;	
for(int i=0; i<grid.size(); i++){
	for(int j=0; j<grid.size(); j++){
		if(grid[i][j]!=generate[i][j]){
			flag=false;
			i=grid.size();
			j=grid.size();
		}
	}
	}
	return(flag);
	
}
//Συνάρτηση για την εκτύπωση του πλέγματος και του πληθυσμού κάθε κατηγορίας
void printGrid(){
	
int total1, total2, total3, total4, total5;
total1=total2=total3=total4=total5=0;

for(int i=0; i<grid.size(); i++){	
	for(int j=0; j<grid.size(); j++){
		cout<<grid[i][j]<<" ";
	}
	cout<<endl;
}

	for(int i=0; i<grid.size(); i++){
		for(int j=0; j<grid.size(); j++){
			if(grid[i][j]==0)
				total1++;
			if(grid[i][j]==1)
				total2++;
			if(grid[i][j]==2)
				total3++;
			if(grid[i][j]==3)
				total4++;
			if(grid[i][j]==4)
				total5++;	
		}
	}
			
	cout<<"Arithmos paxusarkwn="<<total1<<endl;
	cout<<"Arithmos oriaka paxusarkwn="<<total2<<endl;
	cout<<"Arithmos oriaka ugiwn="<<total3<<endl;
	cout<<"Arithmos ugiwn="<<total4<<endl;
	cout<<"Arithmos kenwn keliwn="<<total5<<endl;
	
		
	for(int i=0; i<grid.size(); i++){
		for(int j=0; j<grid.size(); j++){
			state=grid[i][j];
			drawLine(j,i);
				
			}
			cout<<endl;
		}
}

//Συνάρτηση παραγωγής της επόμενης κατάστασης του πλέγματος
void Generate(){
	
int exit_code = 10; 
bool same=false;

count++;
same=stable();


		for(int i=0; i<grid.size(); i++){
			for(int j=0; j<grid.size(); j++){
				grid[i][j]=generate[i][j];
			}
		}
		
		cout<<"Plegma epomenhs genias: \n";
		printGrid();
	
	
	cout<<endl;		
}

//Συνάρτηση υπολογισμού των γειτόνων κάθε κελιού του πλέγματος 
void neighbors(){
	int ob1,ob2,ob,heal1,heal2,heal,sum,c;
	int size=grid.size();
	bool normal=false;

	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			sum=c=0;
			ob1=ob2=ob=0;
			heal1=heal2=heal=0;
		//Γειτονιά Moore ακτίνας 1
			if(i!=0){
				sum++;
				if(grid[i-1][j]<=1){
					ob1++;	
				}else{
					if(grid[i-1][j]!=4)		
					heal1++;	
				}
			}else{
				if(grid[size-1][j]<=1){
					ob1++;	
				}else{
					if(grid[i+1][j]!=4)		
					heal1++;	
				}
			}
			
			
			
			if(j!=0){
				sum++;
				if(grid[i][j-1]<=1){
				ob1++;	
				}else{
					if(grid[i][j-1]!=4)
					heal1++;
				}
			}else{
				if(grid[i][size-1]<=1){
				ob1++;	
				}else{
					if(grid[i][size-1]!=4)
					heal1++;
				}
			}
			
			
			
			if(i!=size-1){
				sum++;
				if(grid[i+1][j]<=1){
				ob1++;	
			}else{
				if(grid[i+1][j]!=4)
				heal1++;
				
			}	
			}else{
				if(grid[0][j]<=1){
				ob1++;	
			}else{
				if(grid[0][j]!=4)
				heal1++;
				
			}	
			}
			
			
			
			if(j!=size-1){
				sum++;
				if(grid[i][j+1]<=1){
				ob1++;	
			}else{
				if(grid[i][j+1]!=4)
				heal1++;
				
			}		
			}else{
				if(grid[i][0]<=1){
				ob1++;	
			}else{
				if(grid[i][0]!=4)
				heal1++;
				
			}	
			}
			
			
		
			if(i!=0 && j!=0){
				sum++;
				if(grid[i-1][j-1]<=1){
				ob1++;	
			}else{
				if(grid[i-1][j-1]!=4)
				heal1++;
				
			}
			}else if(j!=0){
				if(grid[size-1][j-1]<=1){
				ob1++;	
			}else{
				if(grid[size-1][j-1]!=4)
				heal1++;
				
			}
			}else if(i!=0){
				if(grid[i-1][size-1]<=1){
				ob1++;	
			}else{
				if(grid[i-1][size-1]!=4)
				heal1++;
				
			}
			}else{
				if(grid[size-1][size-1]<=1){
				ob1++;
				}else{
					if(grid[size-1][size-1]!=4)
					heal1++;
				}
			}
			
		
			
			if(i!=size-1 && j!=0){
				sum++;
				if(grid[i+1][j-1]<=1){
				ob1++;	
			}else{
				if(grid[i+1][j-1]!=4)
				heal1++;
				
			}
			}else if(j!=0){
				if(grid[0][j-1]<=1){
				ob1++;	
			}else{
				if(grid[0][j-1]!=4)
				heal1++;
				
			}
			}else if(i!=size-1){
				if(grid[i+1][size-1]<=1){
				ob1++;	
			}else{
				if(grid[i+1][size-1]!=4)
				heal1++;
				
			}
			}else{
				if(grid[1][size-1]<=1){
				ob1++;
				}else{
					if(grid[1][size-1]!=4)
					heal1++;
				}
			}
			
			
			
			if(i!=size-1 && j!=size-1){
				sum++;
				if(grid[i+1][j+1]<=1){
					ob1++;	
				}else{
					if(grid[i+1][j+1]!=4)
					heal1++;
					
				}	
			}else if(j!=size-1){
				if(grid[0][j+1]<=1){
					ob1++;	
				}else{
					if(grid[0][j+1]!=4)
					heal1++;
					
				}
			}else if(i!=size-1){
				if(grid[i+1][0]<=1){
					ob1++;	
				}else{
					if(grid[i+1][0]!=4)
					heal1++;
					
				}
			}else{
				if(grid[1][1]<=1){
					ob1++;	
				}else{
					if(grid[1][1]!=4)
					heal1++;
					
				}
			}
			
			
			
			if(i!=0 && j!=size-1){
				sum++;
				if(grid[i-1][j+1]<=1){
				ob1++;	
			}else{
				if(grid[i-1][j+1]!=4)
				heal1++;
				
			}
		}else if(j!=size-1){
			if(grid[size-1][j+1]<=1){
				ob1++;	
			}else{
				if(grid[size-1][j+1]!=4)
				heal1++;
			}
		}else if(i!=0){
			if(grid[i-1][0]<=1){
				ob1++;	
			}else{
				if(grid[i-1][0]!=4)
				heal1++;
				
			}
		}else{
			if(grid[size-1][1]<=1){
				ob1++;	
			}else{
				if(grid[size-1][1]!=4)
				heal1++;
				
			}
		}
//Γειτονιά Moore ακτίνας 2	
			
			if(i>1){
				c++;
				if(grid[i-2][j]<=1){
					ob2++;	
				}else{
					if(grid[i-2][j]!=4)		
					heal2++;	
				}	
			}else if(i==1){
				if(grid[size-1][j]<=1){
					ob2++;	
				}else{
					if(grid[size-1][j]!=4)		
					heal2++;	
				}
			}else if(i==0){
				if(grid[size-2][j]<=1){
					ob2++;	
				}else{
					if(grid[size-2][j]!=4)		
					heal2++;	
				}
			}


		if(j>1){
			c++;
				if(grid[i][j-2]<=1){
					
				ob2++;	
			}else{
				if(grid[i][j-2]!=4)
				heal2++;
				
			}
			}else if(j==1){
				if(grid[i][size-1]<=1){
					
				ob2++;	
			}else{
				if(grid[i][size-1]!=4)
				heal2++;
				
			}
			}else if(j==0){
				if(grid[i][size-2]<=1){
					
				ob2++;	
			}else{
				if(grid[i][size-2]!=4)
				heal2++;
				
			}
			}

		if(i<size-2){
			c++;
				if(grid[i+2][j]<=1){
				
				ob2++;	
			}else{
				if(grid[i+2][j]!=4)
				heal2++;
				
			}
		}else if(i==size-2){
				if(grid[0][j]<=1){
				
				ob2++;	
			}else{
				if(grid[0][j]!=4)
				heal2++;
				
			}
		}else if(i==size-1){
				if(grid[1][j]<=1){
				
				ob2++;	
			}else{
				if(grid[1][j]!=4)
				heal2++;
				
			}
			}

		if(j<size-2){
			c++;
				if(grid[i][j+2]<=1){
					
					ob2++;	
				}else{
					if(grid[i][j+2]!=4)
						heal2++;
				
				}		
			}else if(j==size-2){
					if(grid[i][0]<=1){
					
					ob2++;	
				}else{
					if(grid[i][0]!=4)
						heal2++;
				
				}
			}else if(j==size-1){
					if(grid[i][1]<=1){
					
					ob2++;	
				}else{
					if(grid[i][1]!=4)
						heal2++;
				
				}
			}

		if(i>1 && j>1){
			c++;
				if(grid[i-2][j-2]<=1){
				
				ob2++;	
			}else{
				if(grid[i-2][j-2]!=4)
				heal2++;
				
			}
		}else if(i==1 && j>1){
				if(grid[size-1][j-2]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][j-2]!=4)
				heal2++;
			}
		}else if(i==0 && j>1){
				if(grid[size-2][j-2]<=1){
				
				ob2++;	
			}else{
				if(grid[size-2][j-2]!=4)
				heal2++;
				
			}
		}else if(j==1 && i>1){
					if(grid[i-2][size-1]<=1){
					
					ob2++;	
				}else{
					if(grid[i-2][size-1]!=4)
					heal2++;
					
				}
			}else if(j==0 && i>1){
					if(grid[i-2][size-2]<=1){
					
					ob2++;	
				}else{
					if(grid[i-2][size-2]!=4)
					heal2++;
					
				}
			}else if(i==0 && j==0){
				if(grid[size-2][size-2]<=1){
					
					ob2++;	
				}else{
					if(grid[size-2][size-2]!=4)
					heal2++;
					
				}
		
			}else if(i==1 && j==1){
					if(grid[size-1][size-1]<=1){
					
					ob2++;	
				}else{
					if(grid[size-1][size-1]!=4)
					heal2++;
					
				}
			}else if(i==0 && j==1){
				if(grid[size-2][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[size-2][size-1]!=4)
				heal2++;
				
			}
			}else if(i==1 && j==0){
				if(grid[size-1][size-2]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][size-2]!=4)
				heal2++;
				
			}
			}
				
		if(i<(size-2) && j>1){
			c++;
				if(grid[i+2][j-2]<=1){
				
				ob2++;	
			}else{
				if(grid[i+2][j-2]!=4)
				heal2++;
				
			}
			}else if(i==size-2 && j>1){
				if(grid[0][j-2]<=1){
				
				ob2++;	
			}else{
				if(grid[0][j-2]!=4)
				heal2++;
				
			}
			}else if(i==size-1 && j>1){
				if(grid[1][j-2]<=1){
				
				ob2++;	
			}else{
				if(grid[1][j-2]!=4)
				heal2++;
				
			}
			}else if(j==1 && i<size-2){
				if(grid[i+2][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[i+2][size-1]!=4)
				heal2++;
				
			}
			}else if(j==0 && i<size-2){
				if(grid[i+2][size-2]<=1){
				
				ob2++;	
			}else{
				if(grid[i+2][size-2]!=4)
				heal2++;
				
			}
			}else if(i==size-2 && j==0){
				if(grid[0][size-2]<=1){
				
				ob2++;	
			}else{
				if(grid[0][size-2]!=4)
				heal2++;
				
			}
			}else if(i==size-1 && j==1){
				if(grid[1][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[1][size-1]!=4)
				heal2++;
				
			}
			}else if(i==size-2 && j==1){
				if(grid[0][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[0][size-1]!=4)
				heal2++;
				
			}
			}else if(i==size-1 && j==0){
				if(grid[1][size-2]<=1){
				
				ob2++;	
			}else{
				if(grid[1][size-2]!=4)
				heal2++;
				
			}
			}
			
			
		if(i<(size-2) && j<(size-2)){
			c++;
				if(grid[i+2][j+2]<=1){
					
					ob2++;	
				}else{
					if(grid[i+2][j+2]!=4)
					heal2++;
					
				}
		}else if(i==size-2 && j<size-2){
			if(grid[0][j+2]<=1){
					
					ob2++;	
				}else{
					if(grid[0][j+2]!=4)
					heal2++;
					
				}
		}else if(i==size-1 && j<size-2){
			if(grid[1][j+2]<=1){
					
					ob2++;	
				}else{
					if(grid[1][j+2]!=4)
					heal2++;
					
				}
		}else if(i<size-2 && j==size-2){
			if(grid[i+2][0]<=1){
					
					ob2++;	
				}else{
					if(grid[i+2][0]!=4)
					heal2++;
					
				}
		}else if(i<size-2 && j==size-1){
			if(grid[i+2][1]<=1){
					
					ob2++;	
				}else{
					if(grid[i+2][1]!=4)
					heal2++;
					
				}
		}else if(i==size-2 && j==size-2){
			if(grid[0][0]<=1){
					
					ob2++;	
				}else{
					if(grid[0][0]!=4)
					heal2++;
					
				}
		}else if(i==size-2 && j==size-1){
			if(grid[0][1]<=1){
					
					ob2++;	
				}else{
					if(grid[0][1]!=4)
					heal2++;
					
				}
		}else if(i==size-1 && j==size-2){
			if(grid[1][0]<=1){
					
					ob2++;	
				}else{
					if(grid[1][0]!=4)
					heal2++;
					
				}
		}else if(i==size-1 && j==size-1){
			if(grid[1][1]<=1){
					
					ob2++;	
				}else{
					if(grid[1][1]!=4)
					heal2++;
					
				}
		}

		if(i>1 && j<(size-2)){
			c++;
			if(grid[i-2][j+2]<=1 ){
				ob2++;	
			}else{
				if(grid[i-2][j+2]!=4)
				heal2++;			
			}
		}else if(i==1 && j<size-2){
			if(grid[size-1][j+2]<=1 ){				
				ob2++;	
			}else{
				if(grid[size-1][j+2]!=4)
				heal2++;
				
			}
		}else if(i==0 && j<size-2){
			if(grid[size-2][j+2]<=1 ){
				
				ob2++;	
			}else{
				if(grid[size-2][j+2]!=4)
				heal2++;
				
			}
		}else if(i>1 && j==size-2){
			if(grid[i-2][0]<=1 ){
				
				ob2++;	
			}else{
				if(grid[i-2][0]!=4)
				heal2++;
				
			}
		}else if(i>1 && j==size-1){
			if(grid[i-2][1]<=1 ){
				
				ob2++;	
			}else{
				if(grid[i-2][1]!=4)
				heal2++;
				
			}
	
		}else if(i==1 && j==size-2){
			if(grid[size-1][0]<=1 ){
				
				ob2++;	
			}else{
				if(grid[size-1][0]!=4)
				heal2++;
				
			}
		}else if(i==0 && j==size-1){
			if(grid[size-2][1]<=1 ){
				
				ob2++;	
			}else{
				if(grid[size-2][1]!=4)
				heal2++;
				
			}
		}else if(i==1 && j==size-1){
			if(grid[size-1][1]<=1 ){
				
				ob2++;	
			}else{
				if(grid[size-1][1]!=4)
				heal2++;
				
			}
		}else if(i==0 && j==size-2){
			if(grid[size-2][0]<=1 ){
				
				ob2++;	
			}else{
				if(grid[size-2][0]!=4)
				heal2++;
				
			}
		}
		
		if(i>1 && j!=0){
			c++;
			if(grid[i-2][j-1]<=1){
				
				ob2++;	
			}else{
				if(grid[i-2][j-1]!=4)
				heal2++;
				
			}
		}else if(i==1 && j!=0){
			if(grid[size-1][j-1]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][j-1]!=4)
				heal2++;
				
			}
		}else if(i==0 && j!=0){
			if(grid[size-2][j-1]<=1){
				
				ob2++;	
			}else{
				if(grid[size-2][j-1]!=4)
				heal2++;
				
			}
		}else if(i>1 && j==0){
			if(grid[i-2][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[i-2][size-1]!=4)
				heal2++;
				
			}
		}else if(i==1 && j==0){
			if(grid[size-1][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][size-1]!=4)
				heal2++;
				
			}
		}else if(i==0 && j==0){
			if(grid[size-2][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[size-2][size-1]!=4)
				heal2++;
				
			}
		}
		
		if(i>1 && j<size-1){
			c++;
			if(grid[i-2][j+1]<=1){
				
				ob2++;	
			}else{
				if(grid[i-2][j+1]!=4)
				heal2++;
				
			}
			
		}else if(i==1 && j<size-1){
			if(grid[size-1][j+1]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][j+1]!=4)
				heal2++;
				
			}
		}else if(i==0 && j<size-1){
			if(grid[size-2][j+1]<=1){
				
				ob2++;	
			}else{
				if(grid[size-2][j+1]!=4)
				heal2++;
				
			}
		}else if(i>1 && j==size-1){
			if(grid[i-2][0]<=1){
				
				ob2++;	
			}else{
				if(grid[i-2][0]!=4)
				heal2++;
				
			}
		}else if(i==1 && j==size-1){
			if(grid[size-1][0]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][0]!=4)
				heal2++;
				
			}
		}else if(i==0 && j==size-1){
			if(grid[size-2][0]<=1){
				
				ob2++;	
			}else{
				if(grid[size-2][0]!=4)
				heal2++;
				
			}
		}
		
		if(i!=0 && j<(size-2)){
			c++;
			if(grid[i-1][j+2]<=1){
				
				ob2++;	
			}else{
				if(grid[i-1][j+2]!=4)
				heal2++;
				
			}
		}else if(i==0 && j<size-2){
			if(grid[size-1][j+2]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][j+2]!=4)
				heal2++;
				
			}
		}else if(i!=0 && j==size-2){
			if(grid[i-1][0]<=1){
				
				ob2++;	
			}else{
				if(grid[i-1][0]!=4)
				heal2++;
				
			}
		}else if(i!=0 && j==size-1){
			if(grid[i-1][1]<=1){
				
				ob2++;	
			}else{
				if(grid[i-1][1]!=4)
				heal2++;
				
			}
		}else if(i==0 && j==size-2){
			if(grid[size-1][0]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][0]!=4)
				heal2++;
				
			}
		}else if(i==0 && j==size-1){
			if(grid[size-1][1]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][1]!=4)
				heal2++;
				
			}
		}
		
		if(i<(size-1) && j<(size-2)){
			c++;
			if(grid[i+1][j+2]<=1){
				
				ob2++;	
			}else{
				if(grid[i+1][j+2]!=4)
				heal2++;
				
			}
		}else if(i==size-1 && j<size-2){
			if(grid[0][j+2]<=1){
				
				ob2++;	
			}else{
				if(grid[0][j+2]!=4)
				heal2++;
				
			}
		}else if(i<size-1 && j==size-2){
			if(grid[i+1][0]<=1){
				
				ob2++;	
			}else{
				if(grid[i+1][0]!=4)
				heal2++;
				
			}
		}else if(i<size-1 && j==size-1){
			if(grid[i+1][1]<=1){
				
				ob2++;	
			}else{
				if(grid[i+1][1]!=4)
				heal2++;
				
			}
		}else if(i==size-1 && j==size-2){
			if(grid[0][0]<=1){
				
				ob2++;	
			}else{
				if(grid[0][0]!=4)
				heal2++;
				
			}
		}else if(i==size-1 && j==size-1){
			if(grid[0][1]<=1){
				
				ob2++;	
			}else{
				if(grid[0][1]!=4)
				heal2++;
				
			}
		}
		
		
		if(i<(size-2) && j<(size-1)){
			c++;
			if(grid[i+2][j+1]<=1){
				
				ob2++;	
			}else{
				if(grid[i+2][j+1]!=4)
				heal2++;
				
			}
		}else if(i==size-2 && j<size-1){
			if(grid[0][j+1]<=1){
				
				ob2++;	
			}else{
				if(grid[0][j+1]!=4)
				heal2++;
				
			}
		}else if(i==size-1 && j<size-1){
			if(grid[1][j+1]<=1){
				
				ob2++;	
			}else{
				if(grid[1][j+1]!=4)
				heal2++;
				
			}
		}else if(i<size-2 && j==size-1){
			if(grid[i+2][0]<=1){
				
				ob2++;	
			}else{
				if(grid[i+2][0]!=4)
				heal2++;
	
			}
		}else if(i==size-2 && j==size-1){
			if(grid[0][0]<=1){
				
				ob2++;	
			}else{
				if(grid[0][0]!=4)
				heal2++;
				
			}
		}else if(i==size-1 && j==size-1){
			if(grid[1][0]<=1){
				
				ob2++;	
			}else{
				if(grid[1][0]!=4)
				heal2++;
				
			}
		}
//Edw eixe la8os!!!!!!!!!!!!!!!!!!!!!!!
		if(i<(size-2) && j!=0){
			c++;
			if(grid[i+2][j-1]<=1){
				
				ob2++;	
			}else{
				if(grid[i+2][j-1]!=4)
				heal2++;
				
			}
		}else if(i==size-2 && j!=0){
			if(grid[0][j-1]<=1){
				
				ob2++;	
			}else{
				if(grid[0][j-1]!=4)
				heal2++;
				
			}
		}else if(i==size-1 && j!=0){
			if(grid[1][j-1]<=1){
				
				ob2++;	
			}else{
				if(grid[1][j-1]!=4)
				heal2++;
				
			}
		}else if(i<size-2 && j==0){
			if(grid[i+2][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[i+2][size-1]!=4)
				heal2++;
				
			}
		}else if(i==size-2 && j==0){
			if(grid[0][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[0][size-1]!=4)
				heal2++;
				
			}
		}else if(i==size-1 && j==0){
			if(grid[1][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[1][size-1]!=4)
				heal2++;
				
			}
		}
		
		
		if(i<(size-1) && j>1){
			c++;
			if(grid[i+1][j-2]<=1){
				
				ob2++;	
			}else{
				if(grid[i+1][j-2]!=4)
				heal2++;
				
			}
		}else if(i==size-1 && j>1){
			if(grid[0][j-2]<=1){
				
				ob2++;	
			}else{
				if(grid[0][j-2]!=4)
				heal2++;
			}
		}else if(i<size-1 && j==1){
			if(grid[i+1][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[i+1][size-1]!=4)
				heal2++;
				
			}
		}else if(i<size-1 && j==0){
			if(grid[i+1][size-2]<=1){
				
				ob2++;	
			}else{
				if(grid[i+1][size-2]!=4)
				heal2++;
				
			}
		}else if(i==size-1 && j==1){
			if(grid[0][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[0][size-1]!=4)
				heal2++;
				
			}
		}else if(i==size-1 && j==0){
			if(grid[0][size-2]<=1){
				
				ob2++;	
			}else{
				if(grid[0][size-2]!=4)
				heal2++;
				
			}
		}
		
		if(i!=0 && j>1){
			c++;
			if(grid[i-1][j-2]<=1){
				
				ob2++;	
			}else{
				if(grid[i-1][j-2]!=4)
				heal2++;
				
			}
		
		}else if(i==0 && j>1){
			if(grid[size-1][j-2]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][j-2]!=4)
				heal2++;
				
			}
		}else if(i!=0 && j==1){
			if(grid[i-1][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[i-1][size-1]!=4)
				heal2++;
				
			}
		}else if(i!=0 && j==0){
			if(grid[i-1][size-2]<=1){
				
				ob2++;	
			}else{
				if(grid[i-1][size-2]!=4)
				heal2++;
				
			}
		}else if(i==0 && j==1){
			if(grid[size-1][size-1]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][size-1]!=4)
				heal2++;
				
			}
		}else if(i==0 && j==0){
			if(grid[size-1][size-2]<=1){
				
				ob2++;	
			}else{
				if(grid[size-1][size-2]!=4)
				heal2++;
				
			}
		}


	newstate(ob1,heal1,ob2,heal2,i,j);
		
		}
	}
		
t++;

Generate();
}	

//Συνάρτηση για την πραγματοποίηση αρχικοποιήσεων
void initiallization(){
		int t1, t2, t3, t4, t5;
	t1=t2=t3=t4=t5=0;	
	for(int i=0; i<size; i++){
		
		vector<int>temp;
		vector<int>r;
		vector<int>n;

	for(int j=0; j<size; j++){
		temp.push_back(rand()%5);
		r.push_back(rand()%8);
		n.push_back(0);
	}
	//Αρχικοποίηση της τρέχουσας κατάστασης κάθε ατόμου που ανήκει στο πλέγμα
	grid.push_back(temp);
	//Αρχικοποίηση επόμενης κατάστασης κάθε ατόμου που ανήκει στο πλέγμα
	generate.push_back(n);
	//Αρχικοποίηση των τιμών παραγόντων κινδύνου κάθε ατόμου που ανήκει στο πλέγμα 
	risks.push_back(r);
	limit.push_back(n);
}
for(int i=0; i<size; i++){
	vector<int>c1;
	vector<int>c2; 
	for(int j=0; j<size; j++){
		c1.push_back(0);
		
	}
	//Αρχικοποίηση βαθμού αντίστασης κάθε ατόμου στη μεταβολή κατάστασης
	ho1.push_back(c1);
	//Αρχικοποίηση μετρητή HO(t) για κάθε άτομο που περιλαμβάνεται στο πλέγμα
	ho2.push_back(c1);
}
//Αρχικοποίηση απαιτούμενου χρόνου παραμονής ανάλογα με τρέχουσα κατάσταση
for(int i=0; i<size; i++){
	for(int j=0; j<size; j++){
		if(grid[i][j]==0 || grid[i][j]==3){
			limit[i][j]=ts;
		}else if(grid[i][j]<=2){
			limit[i][j]=tl;
		}
		
	}
}

cout<<"Arxiko plegma: \n";
printGrid();
}
	
};

int main(){
	

    int gd = DETECT, gm;  
    
    initgraph(&gd, &gm, ""); 
	
 	point a;
 	a.initiallization();
 	delay(50);
 //Εκτέλεση αλγορίθμου 45 φορές
 for(int k=0; k<45; k++){
		a.neighbors();
	}
	
    getch(); 
    closegraph(); 
  
    return 0; 
}
