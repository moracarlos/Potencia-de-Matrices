#include <iostream> //cout
#include <string>   //find, substr
#include <string.h> //strcmp
#include <stack>
#include <vector>
#include <math.h>   //pow
using namespace std;

//Clases
class Par{
    public: char x;
    public: char y;
    public: Par(char x, char y){
        this->x=x;
        this->y=y;
    }
};

//Variables globales
stack< Par* > pila;
int k;
long long result=1000000007;
long long n;
vector< vector<long long> > unidad; //T
vector< vector<long long> > compuesta; //T^n
vector<long long> l1; //Para la primera linea de entrada - ai
vector<long long> l2; //Para la segunda linea de entrada - F0
vector<long long> final; //Fn

//Prototipos de funciones
void apilado(long long n);
void calculo();
void multiply (int m);
void armarMatriz();
void getFinal();

//Estructura
int main(){
    cin>>k;
    int i,j,m;
    for (i=0; i<k;i++){//Leer primera linea
        cin>>m;
        l1.push_back(m%result);
    }
    for (i=0;i<k;i++){//Leer segunda linea
        cin>>m;
        l2.push_back(m%result);
    }
    cin>>n;
    apilado(n);
    armarMatriz();
    calculo();
    getFinal();
    if(final.size()>1){
    	cout<<final[0]%result<<endl;
    }else{
	cout<<final[0]%result<<endl;   
    }	
    
    return 0;
}

void apilado (long long n){
    while (n!=1){
        if (n%2==1){ //Impar
            Par* par=new Par('c', 'u');
            pila.push(par);
            n--;
        }else{ //Par
            Par* par= new Par ('c', 'c');
            pila.push(par);
            n=n/2;
        }
    }
}

void armarMatriz(){ //Arma la matriz T y la guarda en unidad y compuesta
    int i,j, t;
    t=k-1;
    vector <long long> fila;
    for (i=0;i<k;i++){
        for (j=0;j<k;j++){
            if (i!=k-1){
                if ((i+1)!=j){
                    fila.push_back(0);
                }else{
                    fila.push_back(1);
                }
            }else{
                fila.push_back(l1[j]);
                t--;
            }
        }
        unidad.push_back(fila);
        compuesta.push_back(fila);
        fila.clear();
    }
}

void calculo(){
    Par* par; int i=0;
    while (!pila.empty()){
    i++;
        par=pila.top(); 
        pila.pop();
        if (par->y=='u'){
            multiply(1); //CASO 1: Multiplicar compuesta = compuesta * unidad
        }
        if (par->y=='c'){
            multiply(2); //CASO 2: Multiplicar compuesta=compuesta*compuesta
        }
    }
}

void multiply(int m){
    int i,j,h;
    long long pos=0;
    vector< vector<long long> > compuesta_aux;
    vector<long long> fila;
    if(m==1){ //CASO 1: Multiplicar compuesta = compuesta * unidad
        for(i=0; i<k; i++){
            for(j=0; j<k; j++){
                for(h=0; h<k; h++){
                    pos=((pos%result)+((compuesta[i][h]%result)*(unidad[h][j]%result))%result)%result;
                }
                fila.push_back(pos%result);
                pos=0;
            }
            compuesta_aux.push_back(fila);
            fila.clear();
        }
        compuesta=compuesta_aux;
    }
    if(m==2){ //CASO 2: Multiplicar compuesta=compuesta*compuesta
        for(i=0; i<k; i++){
            for(j=0; j<k; j++){
                for(h=0; h<k; h++){
                    pos=((pos%result)+((compuesta[i][h]%result)*(compuesta[h][j]%result))%result)%result;
                }
                fila.push_back(pos%result);
                pos=0;
            }
            compuesta_aux.push_back(fila);
            fila.clear();
        }
        compuesta=compuesta_aux;
    }
    compuesta_aux.clear();
}

void getFinal(){ //Multiplicar compuesta*Vector
    int i,j;
    long long pos=0;
    for(i=0; i<k; i++){
        for(j=0; j<k; j++){
            pos=((pos%result)+((compuesta[i][j]%result)*(l2[j]%result))%result)%result;
        }
        final.push_back(pos%result);
        pos=0;
    }
}
