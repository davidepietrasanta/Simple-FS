#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Nodo {  
	char nome[255]; // controllare poi che non superi 255 caratteri
	int essere; // 0 dir, 1 file
	char contenuto[500]; // controllare che non superi di 255 caratteri
	int Nfigli;// tiene il conto dei figli di una dir
	struct Nodo *DirFiglio; // Figlio directory
	struct Nodo *FileFiglio; // Figlio file
	struct Nodo *padre;
	struct Nodo *dF;
	struct Nodo *sF;
};


struct Nodo root = {"root", 0, "", 0, NULL, NULL, NULL, NULL, NULL };
// inizializza la root


void inizializzatore(struct Nodo **elemento, int l)// inizializza il nodo
{ 	int i;
	for(i=0; i<l; i++)
	{ elemento[i]=NULL; }
}

int len(char *s)    // restituisce la lunghezza della stringa
{ int i;
  for(i=0; *(s+i)!='\0' ; i++)
  ;
  return i;
} 


int alfanumerico(char *s){ // 0 se s e' alfanumerico
        int l=len(s);
	if (l<=0) return 0;
	int i;
	for(i=0; i<l; i++)
	{ if(! (*(s+i)>='0' && *(s+i)<='9' || *(s+i)>='A' && *(s+i)<='Z' || *(s+i)>='a' && *(s+i)<='z')) 
	return 0;
	}
	return 1;
}

int alfanumericospa(char *s){ // 0 se s e' alfanumerico con spazi
        int l=len(s);
    if (l<=0) return 0;
    int i;
    for(i=0; i<l; i++)
        { if(! (*(s+i)>='0' && *(s+i)<='9' || *(s+i)>='A' && *(s+i)<='Z' || *(s+i)>='a' && *(s+i)<='z' || *(s+i) == ' '))
    return 0;
    }
    return 1;
}


char *perc(char *s) // restituisce il puntatore al percorso
{while(*(s)!='/') 
	{s++;}
 return s;}
 
int ig(char *s) // lunghezza s fino al primo spazio
{int i=0;
 while(*(s)!=' ' && *(s)!='\0') 
	{s++;
	 i++;}
 return i--;}

void istr(char *s, char *l) // restituisce l'istruzione della stringa s in l
{ int k=ig(s);
  int i;
  for(i=0;i<k;i++)
  	{*(l+i)=*(s+i);}
  *(l+i)='\0';
}


void reverse(char * stringa) 
{ int i,j;
  int l=len(stringa);
  for(i=0, j=l-1; i<l/2; i++, j--)
  	{char temp=stringa[i];
  	 stringa[i]=stringa[j];
  	 stringa[j]=temp;
  	}
 }

void naming(char *s, char *nomeSpa, char *risultato) // restituisce l'ultima parola del percorso senza gli spazi, se risultato==b sbagliato 
{ int l=strlen(s);
  //printf("1 %d\n",l);
  int i;
  int j=0;
  for(i=l-1;i>=0 && s[i]!='/';i--)
  	{if(s[i]!=' ' && j<256)
  		{nomeSpa[j]=s[i];
  		 j=j+1;}
  	}
  if(j==256 && nomeSpa[255]!='/')
  {strcpy(risultato,"b");}
  else
  {nomeSpa[j]='\0';
  reverse(nomeSpa);
  nomeSpa[j]='\0';
  strcpy(risultato,"a");}
  
}


void w2(char *s,char *r,char *risultato) // ritorna tutto cio' che c'e' tra le "_" di s in r, risultato=a se ok, altrimenti b
{ int l=len(s);
  int i;
  int j=0;
  int cont=0;
  for(i=0; cont<2 && i<l ; i++)
  	{if(cont==1)
  		 {*(r+j)=*(s+i);
  		 j=j+1;}
  	 if(*(s+i)=='"')
  		{cont=cont+1;}
  		 
  	}
  	
  if(cont<2)
  	{strcpy(r,"");
  	 	strcpy(risultato,"b"); }
  else 
  	{*(r+j-1)='\0';
  	 //printf("%s\n",r);
  	 //printf("%d\n",alfanumerico(r));
  	 if(alfanumericospa(r)!=1)
  	 	strcpy(risultato,"b");
  	 else 	
  	 	strcpy(risultato,"a");}
   	
}

int last(char *p)// ritorna il numero di caratteri prima dell'ultimo /
{ int l=len(p);
  int i;
  for(i=l;*(p+i)!='/' ; i--)
  ;
  return i;
}

void NomeFind(char *s,char *RNodoFind) //Ritorna una stringa con dentro il nome dopo i primi spazi, esempio "find ciao  " ritorna ciao in RNodoFind. RNodoFind e' piu' grande di quel che dovebbe, se ci sono spazi dopo NOME
{ int l=len(s);
  int sp=ig(s); //caratteri fino al primo spazio
  int i;
  int j=0;
  for(i=sp;i<l;i++)
  	{ if(s[i]!=' ')
  	  	{RNodoFind[j]=s[i];
  	  	 j=j+1;}
  	}
  RNodoFind[j]='\0';
}
 

 
int controllo2(char *nome, struct Nodo *padre) // controlla che nella stessa dir non ci siano cose con nome uguali, 0 se e' unico, 1 altrimenti
{ 	struct Nodo *F= NULL;
	// controlla nelle dir
	if (padre->DirFiglio!=NULL) 
		F=padre->DirFiglio;
	while(F!=NULL)
	{ if (strcmp(F->nome,nome)==0) 
	  	return 1;
	  if (F->dF!=NULL) 
	  	F=F->dF;
	  else 
	  	F=NULL;}
	// controlla nei file  	
	if (padre->FileFiglio!=NULL) 
		F=padre->FileFiglio;
	while(F!=NULL)
	{ if (strcmp(F->nome,nome)==0) 
	  	return 1;
	  if (F->dF!=NULL) 
	  	F=F->dF;
	  else 
	  	F=NULL;}
		
	return 0;
}

struct Nodo *TrovaPadre(char *percorso) //esegue il percorso e ritorna una copia del nodo corrispondente a quel percorso  
{    struct Nodo * nodePath= &root;
    int n=0,f=0,segnalino=1;
    
    if (strlen(percorso)==0) return nodePath;
    if (percorso[0]=='/') percorso=percorso+1;
    else return NULL;
    
    for(n=0; n<strlen(percorso)+1 && segnalino==1; n++)
    {
        if (percorso[n]=='/' || percorso[n]=='\0'){
            segnalino=0;
                
            char app[255]="";

            struct Nodo * nodePathSon=NULL;

            //splitta le directory del path
            strncpy(app, percorso+f, n-f);
            f=n+1;
            //printf("%i , %s \n", n, app);

            //cerca figlio
            for(int k=0; k<=1 && segnalino==0; k++){    
                
                //prima controlla le cartelle poi i file
                if (k==0 && nodePath->DirFiglio!=NULL) nodePathSon= nodePath->DirFiglio;                
                if (k==1 && nodePath->FileFiglio!=NULL) nodePathSon= nodePath->FileFiglio;
                
                if (nodePathSon!=NULL){
    
                    if (strcmp(nodePathSon->nome,app)==0){
                        nodePath=nodePathSon;
                        segnalino=1;
                        break;
                    }
                    //printf("%i , %s \n", n, path);    
                    while (nodePathSon->dF!=NULL && segnalino==0){
                        nodePathSon=nodePathSon->dF;

                        if (strcmp(nodePathSon->nome,app)==0){
                            nodePath=nodePathSon;
                            segnalino=1;
                            break;
                        }
                    }
                }
            }
            
        }
        
    }
    if (segnalino==1){
        return nodePath;
    }
    else{
        return NULL;
    }
    
}


int contatore(char *percorso) // conta le / della stringa, dunque la profondita'
{ int i;
  int cont=0;
  for(i=0; *(percorso+i)!='\0' ; i++)
  {if(*(percorso+i)=='/')
     cont=cont+1;}
  return cont;
}


struct Nodo *create(char *nome, char *percorso, int essere, char *contenuto) 
{	
	struct Nodo *nuovo;
	struct Nodo *padre=TrovaPadre(percorso);
	
	if (padre==NULL) 
	{//printf("Percorso errato\n"); 
	return NULL;}  
	
	if (alfanumerico(nome)==0)
	{//printf("Nome non alfanumerico o troppo lungo\n");
	return NULL;}  
	
	if (padre->essere==1)
	{//printf("I file non possono avere figli\n");
	return NULL;}  
	
	if (controllo2(nome,padre)==1) 
	{//printf("Esiste un'altra risorsa con lo stesso nome\n");
	return NULL;} 
	
	if (len(nome)>255) 
	{//printf("Il nome deve essere piu' corto di 255 caratteri\n");
	return NULL;} 
	
	if(contatore(percorso)>254)
	{//printf("La profondita' massima e' 255\n");
	return NULL;} 
	
	if(padre->Nfigli>1023) // quindi da 1024 compreso in su
	{//	printf("Una directory puo' avere massimo 1024 figli\n");
		return NULL;} 
	
	
	padre->Nfigli=(padre->Nfigli)+1;
	nuovo=(struct Nodo*)malloc(sizeof(struct Nodo));
	nuovo->sF=NULL;
	nuovo->dF=NULL;
	nuovo->DirFiglio=NULL;
	nuovo->FileFiglio=NULL;
	strcpy(nuovo->nome, nome);
	nuovo->essere=essere;
	nuovo->padre=padre;
	
	// prima le dir per rendere piu' veloce
	if(essere==0) // dir
	{if (padre->DirFiglio!=NULL){
		nuovo->dF=padre->DirFiglio;
		nuovo->dF->sF=nuovo; // cosi' assegno i fratelli
		}
	padre->DirFiglio=nuovo;
	}
	
	else // file
	{strcpy(nuovo->contenuto,contenuto);
	if (padre->FileFiglio!=NULL){
		nuovo->dF=padre->FileFiglio;
		nuovo->dF->sF=nuovo; // cosi' assegno i fratelli
		}
	 padre->FileFiglio=nuovo;
	}
	
	return nuovo;
}

void percorsoNodo(struct Nodo *n, char *registro) //char *registro serve per salvare fuori, se no va tutto eliminato, carica in registro il percorso del nodo n
{ if(n->padre!=NULL && strcmp(n->padre->nome,"root")!=0)
	{percorsoNodo(n->padre,registro);}
	strcat(registro,"/");
	strcat(registro,n->nome);
	//printf("2%s\n",registro);
}

void find(char *nome, struct Nodo *radice, char *registro,int *cont) //ritorna la posizione dei vari file con lo stesso nome in registro, cont lo si imposta a 0, radice lo si imposta =&root, in registro vanno i percorsi
{ if(strcmp(radice->nome,nome)==0)
  	{*cont=*cont+1;
  	 //printf("cont %d\n",*cont);
  	 percorsoNodo(radice,registro);
  	 strcat(registro,"$");
  	 	} // cosi' facendo ogni percorso e' diviso da un $
  
  if(radice->DirFiglio!=NULL)
  	{find(nome, radice->DirFiglio,registro,cont);}
  if(radice->FileFiglio!=NULL)
  	{find(nome, radice->FileFiglio,registro,cont);}
  if(radice->dF!=NULL)
  	{find(nome, radice->dF,registro,cont);}
 }
 

void StampaFind(char *s, int cont)//stampa matr, mentre prende le robe da s. Da implementare la stampa ordinata
{int l=len(s);
 int i;
 char matr[cont+1][l]; // sara' piu' lunga del dovuto
 int k=0;
 int j=0;
 if(l<1)
 	;
 else // if(s[i]=='$') allora tolgo $ e metto '\n ok '
	{for(i=0;i<l;i++)
	 	{if(s[i]!='$' && s[i+1]!='$')
	 		{ matr[k][j]=s[i];
	 		  j=j+1;}
	 	 else if(s[i]!='$' && s[i+1]=='$')
	 		{ matr[k][j]=s[i];
	 		  j=j+1;
	 		  matr[k][j]='\0';}
	 	 else if(s[i]=='$') //&& s[i+1]!='\0')
	 		{k=k+1;
	 		 j=0;}
	 	
	 	}
	  
	 }
//InsertionSort, vedere se va bene, altrimenti implementare Shellsort
char key[l];
strcpy(key,"");
 for(i=1;i<cont;i++)
	{
	 strcpy(key,matr[i]);
       	 j=i-1;
       	 
	 while (j>= 0 && strcmp(matr[j],key)>0 )
		{strcpy(matr[j+1],matr[j]);
           	 j=j-1;}
           	 
	 strcpy(matr[j+1],key);
	}


// stampa la matr
 for(k=0;k<cont;k++)
 	{
 		{printf("ok ");
 		printf("%s",matr[k]);
 		printf("\n");}
 	}
 	

}

void delete(struct Nodo *nodoDelete)
{if(nodoDelete->sF==NULL && nodoDelete->dF==NULL)
	{if(nodoDelete->essere==0) //dir
			{nodoDelete->padre->DirFiglio=NULL;}
	if(nodoDelete->essere==1) //file
		{nodoDelete->padre->FileFiglio=NULL;}
	}
 else
 	{if(nodoDelete->dF!=NULL && nodoDelete->sF!=NULL)
		{nodoDelete->sF->dF=nodoDelete->dF;
		 nodoDelete->dF->sF=nodoDelete->sF;}
	 else if(nodoDelete->sF==NULL && nodoDelete->dF!=NULL)
		 {if(nodoDelete->essere==0) //dir
			{nodoDelete->padre->DirFiglio=nodoDelete->dF;
			 nodoDelete->dF->sF=NULL;}
		if(nodoDelete->essere==1) //file
			{nodoDelete->padre->FileFiglio=nodoDelete->dF;
			 nodoDelete->dF->sF=NULL;}
		nodoDelete->dF->sF=NULL;
		}
	else if(nodoDelete->dF==NULL && nodoDelete->sF!=NULL)
		{nodoDelete->sF->dF=NULL;}			
	 }

	nodoDelete->padre->Nfigli=(nodoDelete->padre->Nfigli)-1;
	//diminuire di 1 il Nfigli del padre
	free(nodoDelete);
}

void deleteTOT(struct Nodo *nodoDelete)//serve per salvare momentaneamente, in caso non la facessi ricorsiva lo porto dentro la funzione
{if(nodoDelete->essere==1 || nodoDelete->Nfigli==0)//file o dir senza figli
	{delete(nodoDelete);}
 else //dir con figli
 	{if (nodoDelete->DirFiglio!=NULL) 
 		delete(nodoDelete->DirFiglio);
	 if (nodoDelete->FileFiglio!=NULL) 
		delete(nodoDelete->FileFiglio);
	 if (nodoDelete->dF!=NULL) 
		delete(nodoDelete->dF);

	  delete(nodoDelete);
	 }
 
}


void StampaAlbero(int n, struct Nodo * sNode)
	{int i;
	for(i=0; i<n; i++)
		{printf("  ");}
	if(sNode->essere==0)
	printf("%s.dir \n", sNode->nome);
	else
	printf("%s.file \n", sNode->nome);
	
	
	if (sNode->DirFiglio!=NULL) StampaAlbero(n+1, sNode->DirFiglio);
	if (sNode->FileFiglio!=NULL) StampaAlbero(n+1, sNode->FileFiglio);
	if (sNode->dF!=NULL) StampaAlbero(n, sNode->dF);
	}


void avvio() // magari da problemi sul reset dei vettori, verificare in caso
{ 

  char stringa[100000]; // secondo me andra' sistemata la dimensione
  char percorso[100000]; // da aumentare
  char nome[257]; // questo invece va bene cosi'
  struct Nodo *nodo;
  int exit=0;
  
  while(exit==0)
  { nodo=NULL;
    strcpy(percorso,"");
    strcpy(stringa,"");
    strcpy(nome,""); // azzero le stringhe per il giro dopo
    fgets(stringa,100000, stdin);
    stringa[strcspn(stringa,"\n")]='\0';
    int LenStringa=len(stringa);
    char istruzione[LenStringa];
    strcpy(istruzione,"");
    istr(stringa,istruzione); // ora dentro istruzione c'e' l'istruzione
   
    //CREATE
    if(strcmp(istruzione,"create")==0)
    { strcpy(percorso,perc(stringa));
      int LastPercorso=last(percorso);
      char risultato[2];
      char percorsoNoName[LastPercorso+1];
      strcpy(percorsoNoName,"");
      naming(percorso,nome,risultato);
      strncpy(percorsoNoName,percorso,LastPercorso);
      percorsoNoName[LastPercorso]='\0';
      if(strcmp(risultato,"a")==0)
      {nodo=create(nome,percorsoNoName,1,"");}
      //free(percorsoNoName);
      if (nodo!= NULL) 
          printf("ok\n");
      else 
          printf("no\n");
    }
    //CREATE_DIR
    if(strcmp(istruzione,"create_dir")==0)
    { strcpy(percorso,perc(stringa));
      int LastPercorso=last(percorso);
      char risultato[2];
      char percorsoNoName[LastPercorso+1]; 
      strcpy(percorsoNoName,"");
      naming(percorso,nome,risultato);
      strncpy(percorsoNoName,percorso,LastPercorso);
      percorsoNoName[LastPercorso]='\0';
      if(strcmp(risultato,"a")==0)
      {nodo=create(nome,percorsoNoName,0,"");}
      //free(percorsoNoName);
      if (nodo!= NULL) 
          printf("ok\n");
      else 
          printf("no\n");
    }
    //EXIT
    if(strcmp(istruzione,"exit")==0)
    {exit=1;}
    //READ
    if(strcmp(istruzione,"read")==0) // inutile chiamare una funzione per una cosa che si fa solo una volta, perdita di tempo per il compilatore
    { nodo=TrovaPadre(perc(stringa));
      if(nodo==NULL)
          printf("no\n");
      else
          {if(nodo->essere==1)
        printf("contenuto %s\n", nodo->contenuto);
    else
        printf("no\n");                 
    }
     }
     //WRITE
     if(strcmp(istruzione, "write")==0)
    {char testo[500]="";//va dichiarato cosi' se no poi da problemi quando si sovrascrive
     char conte[LenStringa]; // piu' lunga del dovuto
     char IstrPerc[len(perc(stringa))];
     char risultato[2];
     w2(stringa,conte,risultato);
     //printf("%s\n",risultato);
     int l=len(conte); // lunghezza contenuto
     if(l>500 || strcmp(risultato,"b")==0 )
         {printf("no\n");}
     else 
         {strcpy(testo,conte);}
     istr(perc(stringa),IstrPerc);
     strcpy(percorso,IstrPerc);
     nodo=TrovaPadre(percorso);
     if(nodo==NULL )// || alfanumerico(testo)==0) 
         {printf("no\n");
	  
	}
    else if(nodo!=NULL && strcmp(risultato,"a")==0 && l<=500)
    {    if(nodo->essere==1 )
            {int l=len(testo);
            strcpy(nodo->contenuto, testo); // cosi' sovrascrive
            printf("ok %i\n",l);}
        else
            printf("no\n");                 
    }
         
    }
    //FIND
    if(strcmp(istruzione, "find")==0)
     {char registro[100000];
      registro[0]='\0';
      int sp=ig(stringa); 
      char nomefind[LenStringa-sp];
      strcpy(nomefind,"");
      struct Nodo *radice=&root;
      //int l=len(perc(stringa)); //roba strana
      NomeFind(stringa,nomefind);
      //printf("%s\n",nomefind);
      int cont=0; //numero di oggetti trovati con quel nome
      find(nomefind,radice,registro,&cont);
      //printf("%d\n",cont);
      if(len(registro)==0)
          {printf("no\n");}
      else
          {//printf("%s\n",registro);
           StampaFind(registro,cont);}
      }
      
     //STAMPA ALBERO
    if(strcmp(istruzione,"stampa")==0 || strcmp(istruzione,"ls")==0 || strcmp(istruzione,"print")==0)
    {printf("\033[31mFILE SYSTEM\033[0m\n"); // stampa rossa di file system prima dell'inizio della stampa dell'albero
     StampaAlbero(0,&root);
     printf("\033[31mEND\033[0m\n");} 
     
    //DELETE
    if(strcmp(istruzione, "delete")==0)
     {struct Nodo *nodoDelete=TrovaPadre(perc(stringa));
      if(nodoDelete!=NULL && nodoDelete->FileFiglio==NULL && nodoDelete->DirFiglio==NULL) //|| nodoDelete->Nfigli!=0)
      	{delete(nodoDelete);
         printf("ok\n");}
          
      else
          {printf("no\n");}
      }
    //DELETE_R
    if(strcmp(istruzione, "delete_r")==0)
     {struct Nodo *nodoDelete=TrovaPadre(perc(stringa));
      if(nodoDelete==NULL)
          printf("no\n");
      else
          {if(nodoDelete->Nfigli==0)
              printf("ok\n"); 
           else
               {deleteTOT(nodoDelete);
               printf("ok\n");}
           }
     }
	
  } // while
 
} // funzione

int main()
{      	
	avvio();
	
	
	return 0;
}


