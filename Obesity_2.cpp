#include <vector>
#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;
const int size=80;

class point{
	public:
		
	vector<vector<int> >grid;
	vector<vector<int> >generate;
	vector<vector<int> >risks;
	vector<int> store;
	vector<vector<int> >cells;
	vector<vector<int> >n_risks;
	vector<vector<float> >ho1;
	vector<vector<float> >ho2;
	vector<vector<int> >limit;
	int state;
	int count=0;
	int counter=0;
	int result=size/10;
	bool metraw=false;
	int s=-4;
	int t=0;
	int diafora=1;
	int times=0;
	int total=0;
	int total1, total2;
	bool flag=false;
	int c1,c2,c3,c4;
	int ts=10;
	int tl=4;
	
//Συνάρτηση για το χρωματισμό των κελιών του πλέγματος ανάλογα με την κατάστασή τους
void drawLine(int x, int y){
int l=7;
int step=40;
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
    line(x*l+step,y*l+i,x*l+step+5,y*l+i);
}

//Σύγκριση κελιού (i,j) με στοιχεία του vector store, ο οποίος αποθηκεύει τα κελιά στα οποία έχουν γίνει παρεμβάσεις  
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
void newstate(int osum,int hsum, int i, int j){
bool s=compare(i,j);
	
	float vou=-3;
	float vl=-1;
	float vhl=2;
	
	float ah,ao;
	float ar;
	int k,l;
	//Ορισμός των παραμέτρων επιρροής 
	ah=1.05;
	ao=1;
	ar=0.5;
	int stoixeio=grid[i][j];
	//Προσθήκη των παρακάτω σχολίων για την εφαρμοφή του 1ου είδους παρεμβάσεων
	
	//if(osum>5 && s==false){
	//	store.push_back(i);
	//	store.push_back(j);
	//	risks[i][j]-=3;
	//}
	int risk=risks[i][j];
	
	//Υπολογισμός του μετρητή HO(t) για κάθε άτομο που ανήκει στο πλέγμα
	
	//Προσθήκη των παρακάτω σχολίων για την εφαρμοφή του 2ου είδους παρεμβάσεων
	//if(osum>5 && stoixeio<=1){
	//	ao=ah=0.5;
	//	ho2[i][j]= -ar*risk - ah*hsum + ao*osum + ho1[i][j];
	//}else{
		ho2[i][j]= -ar*risk + ah*hsum - ao*osum + ho1[i][j];
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
int stable(){
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

for(int i=0; i<cells.size(); i++){	
	for(int j=0; j<cells.size(); j++){
		cout<<cells[i][j]<<" ";
	}
	cout<<endl;
}


	for(int i=0; i<cells.size(); i++){
		for(int j=0; j<cells.size(); j++){
			if(cells[i][j]==0)
				total1++;
			if(cells[i][j]==1)
				total2++;
			if(cells[i][j]==2)
				total3++;
			if(cells[i][j]==3)
				total4++;
			if(cells[i][j]==4)
				total5++;	
		}
	}
			
	cout<<"Arithmos paxusarkwn="<<total1<<endl;
	cout<<"Arithmos oriaka paxusarkwn="<<total2<<endl;
	cout<<"Arithmos oriaka ugiwn="<<total3<<endl;
	cout<<"Arithmos ugiwn="<<total4<<endl;
	cout<<"Arithmos kenwn keliwn="<<total5<<endl;
	
		
	for(int i=0; i<cells.size(); i++){
		for(int j=0; j<cells.size(); j++){
			state=cells[i][j];
			drawLine(j,i);
				
			}
			cout<<endl;
		}
}

//Συνάρτηση παραγωγής της επόμενης κατάστασης του πλέγματος
void Generate(){
count++;
bool same=false;

int exit_code = 10; 

same=stable();

//Η επόμενη κατάσταση του πλέγματος γίνεται η τρέχουσα
		for(int i=0; i<grid.size(); i++){
			for(int j=0; j<grid.size(); j++){
				grid[i][j]=generate[i][j];
			}
		}
		join();
		cout<<"Plegma epomenhs genias: \n";
		printGrid();
		

}

//Συνάρτηση υπολογισμού των γειτόνων κάθε κελιού του πλέγματος 
double neighbors(){
		
	int ob,heal,sum,c,k,l;
	int size=grid.size();
	bool normal=false;
	c1=c2=c3=c4=0;
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			
			ob=0;
			heal=0;
			sum=0;
			
			if(i!=0){
				sum++;
				if(grid[i-1][j]<=1){
					ob++;	
				}else{
					if(grid[i-1][j]!=4)		
					heal++;	
				}
			}else{
				if(grid[size-1][j]<=1){
					ob++;	
				}else{
					if(grid[i+1][j]!=4)		
					heal++;	
				}
			}
			
			
			
			if(j!=0){
				sum++;
				if(grid[i][j-1]<=1){
				ob++;	
				}else{
					if(grid[i][j-1]!=4)
					heal++;
				}
			}else{
				if(grid[i][size-1]<=1){
				ob++;	
				}else{
					if(grid[i][size-1]!=4)
					heal++;
				}
			}
			
			
			
			if(i!=size-1){
				sum++;
				if(grid[i+1][j]<=1){
				ob++;	
			}else{
				if(grid[i+1][j]!=4)
				heal++;
				
			}	
			}else{
				if(grid[0][j]<=1){
				ob++;	
			}else{
				if(grid[0][j]!=4)
				heal++;
				
			}	
			}
			
			
			
			if(j!=size-1){
				sum++;
				if((grid[i][j+1]==0 || grid[i][j+1]==1)){
				ob++;	
			}else{
				if(grid[i][j+1]!=4)
				heal++;
				
			}		
			}else{
				if(grid[i][0]<=1){
				ob++;	
			}else{
				if(grid[i][0]!=4)
				heal++;
				
			}	
			}
			
			
		
			if(i!=0 && j!=0){
				sum++;
				if(grid[i-1][j-1]<=1){
				ob++;	
			}else{
				if(grid[i-1][j-1]!=4)
				heal++;
				
			}
			}else if(j!=0){
				if(grid[size-1][j-1]<=1){
				ob++;	
			}else{
				if(grid[size-1][j-1]!=4)
				heal++;
				
			}
			}else if(i!=0){
				if(grid[i-1][size-1]<=1){
				ob++;	
			}else{
				if(grid[i-1][size-1]!=4)
				heal++;
				
			}
			}else{
				if(grid[size-1][size-1]<=1){
				ob++;
				}else{
					if(grid[size-1][size-1]!=4)
					heal++;
				}
			}
			
		
			
			if(i!=size-1 && j!=0){
				sum++;
				if(grid[i+1][j-1]<=1){
				ob++;	
			}else{
				if(grid[i+1][j-1]!=4)
				heal++;
				
			}
			}else if(j!=0){
				if(grid[0][j-1]<=1){
				ob++;	
			}else{
				if(grid[0][j-1]!=4)
				heal++;
				
			}
			}else if(i!=size-1){
				if(grid[i+1][size-1]<=1){
				ob++;	
			}else{
				if(grid[i+1][size-1]!=4)
				heal++;
				
			}
			}else{
				if(grid[1][size-1]<=1){
				ob++;
				}else{
					if(grid[1][size-1]!=4)
					heal++;
				}
			}
			
			
			
			if(i!=size-1 && j!=size-1){
				sum++;
				if(grid[i+1][j+1]<=1){
					ob++;	
				}else{
					if(grid[i+1][j+1]!=4)
					heal++;
					
				}	
			}else if(j!=size-1){
				if(grid[0][j+1]<=1){
					ob++;	
				}else{
					if(grid[0][j+1]!=4)
					heal++;
					
				}
			}else if(i!=size-1){
				if(grid[i+1][0]<=1){
					ob++;	
				}else{
					if(grid[i+1][0]!=4)
					heal++;
					
				}
			}else{
				if(grid[1][1]<=1){
					ob++;	
				}else{
					if(grid[1][1]!=4)
					heal++;
					
				}
			}
			
			
			
			if(i!=0 && j!=size-1){
				sum++;
				if(grid[i-1][j+1]<=1){
				ob++;	
			}else{
				if(grid[i-1][j+1]!=4)
				heal++;
				
			}
		}else if(j!=size-1){
			if(grid[size-1][j+1]<=1){
				ob++;	
			}else{
				if(grid[size-1][j+1]!=4)
				heal++;
			}
		}else if(i!=0){
			if(grid[i-1][0]<=1){
				ob++;	
			}else{
				if(grid[i-1][0]!=4)
				heal++;
				
			}
		}else{
			if(grid[size-1][1]<=1){
				ob++;	
			}else{
				if(grid[size-1][1]!=4)
				heal++;
				
			}
		}
		newstate(ob,heal,i,j);
				
	}	
}
	
Generate();

}

//Συνάρτηση εύρεσης μέσης τιμής των παραγόντων κινδύνου μιας γειτονιάς με 4 κελιά
int findAverage(int a, int b){
	
	int avg=0;
	for(int x=a; x<a+2; x++){
		for(int y=b; y<b+2; y++){
			avg+=risks[x][y];
		}
	}
	return avg/4;
}

//Συνάρτηση για την εύρεση της επικρατούσας κατάστασης μεταξύ 4 γειτονικών κελιών
int findMajority(int a, int b){

	int c0,c1,c2,c3,c4,c,max,max2;
	int number=4;
	c0=0;
	c1=0;
	c2=0;
	c3=0;
	c4=0;
	c=0;
	max=0;
	max2=0;
	
		
	for(int x=a; x<(a+2); x++){
		
		for(int y=b; y<(b+2); y++){
			if(grid[x][y]==0){
				c0++;
			}else if(grid[x][y]==1){
				c1++;
			}else if(grid[x][y]==2){
				c2++;
			}else if(grid[x][y]==3){
				c3++;
			}else {
				c4++;
			}
		}
	
	}
	
	if(c0>max)	max=c0;
	if(c1>max)	max=c1;
	if(c2>max)	max=c2;
	if(c3>max)	max=c3;
	if(c4>max)	max=c4;
	
	
	if((max>2) || ((c4==1) && (max==2))){
		if(max==c0)			return 0;
		else if(max==c1)	return 1;
		else if(max==c2)	return 2;
		else if(max==c3)	return 3;
		else				return 4;	
	}else{
		if(c4>0){
			for(int x=0; x<c4; x++){
				number--;
			}
		}
			
		max=(1*c1+2*c2+3*c3)/number;
		
		if(((c1+2*c2+3*c3) % number)/number >=0.5)
			c=1;
		else
			c=0;
		return(max+c);
	}
}

//Συνάρτηση δημιουργίας νέου πλέγματος στο οποίο περιοχές 4 κελιών συγχωνεύονται σε 1 κελί
int join(){
	
	int k,l;
	int t1, t2, t3, t4, t5;
	t1=t2=t3=t4=t5=0;
	t++;
	k=0;
	for(int i=0; i<grid.size()-1; i+=2){	
		l=0;
		for(int j=0; j<grid.size()-1; j+=2){
			
			cells[k][l]=findMajority(i, j);

			n_risks[k][l]=findAverage(i, j);
			
			if(l>=grid.size()-2)		
				l=grid.size();
				
			l++;
		}
		k++;
		if(k>=grid.size()-2){
			k=grid.size();
		}
}
if(t==1){
	cout<<"Plegma me 4 geitones/keli:  \n";
printGrid();
}
}

//Συνάρτηση για την πραγματοποίηση αρχικοποιήσεων
void initiallization(){
	
	for(int i=0; i<size; i++){
		
		vector<int>temp;
		vector<int>n;
		vector<int>r;
		
	for(int j=0; j<size; j++){
		temp.push_back(rand()%5);
		n.push_back(0);
		r.push_back(rand()%8);

	}
	//Αρχικοποίηση της τρέχουσας κατάστασης κάθε ατόμου που ανήκει στο πλέγμα
	grid.push_back(temp);
	//Αρχικοποίηση επόμενης κατάστασης κάθε ατόμου που ανήκει στο πλέγμα
	generate.push_back(n);
	//Αρχικοποίηση των τιμών παραγόντων κινδύνου κάθε ατόμου που ανήκει στο πλέγμα 
	risks.push_back(r);
	//Αρχικοποίηση απαιτούμενου χρόνου παραμονής ανάλογα με την αρχκή κατάσταση
	limit.push_back(n);
}

for(int i=0; i<size/2; i++){
	vector<int>p1;
	vector<int>p2;
	for(int j=0; j<size/2; j++){
		p1.push_back(1);
		p2.push_back(4);
	}
	//Αρχικοποίση των κελιών του πλέγματος (4 άτομα/κελί)
	cells.push_back(p1);
	//Αρχικοποίση των παραγόντων κινδύνου των κελιών του πλέγματος (4 άτομα/κελί)
	n_risks.push_back(p2);
}
for(int i=0; i<size; i++){
	vector<float>c1;
	vector<float>c2; 
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
}
};

int main(){
	   
    int gd = DETECT, gm;  
    int count=0;
    initgraph(&gd, &gm, ""); 
	
 	point a;
 	a.initiallization();
 	delay(50);
 	a.join();
 	
	//Εκτέλεση αλγορίθμου 45 φορές
	for(int k=0; k<45; k++){
		a.neighbors();
	}
		
	
    
    getch(); 
    closegraph(); 
  
    return 0; 
}



