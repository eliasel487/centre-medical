void triParEchange(int tab[], int n){
    int pge;
    while (n>1){
        pge = plusGrand(tab,n);
        echanger(tab,pge,n-1);
        n = n - 1;
    }
}

void echanger(int tab[], int i, int j){
    int aux;
    aux = tab[i];
    tab[i] = tab[j];
    tab[j] = aux;
}

int plusGrand(int tab[], int n){
    int i, pge=0;
    for (i=0;i<n;i++){
        if (tab[i]>tab[pge])
            pge = i;
    }
    return pge;
}

void fusion(int R[], int n, int S[], int m, int T[]){
    int i=0, j=0, k=0;
    while (i<n && j<m){
        if (R[i] <= S[j]){
            T[k] = R[i];
            i++;
            k++;
        }
        else{
            T[k]=S[j];
            j++;
            k++;
        }
    }
    while(i<n){
        T[k]=R[i];
        i++;
        k++;

    }
    while(j<m){
        T[k]=S[j];
        j++;
        k++
    }
}

void copier(int T[], int i, int j, int R[]){
    int k=0;
    while(i<j){
        R[k]=T[i];
        i++;
        k++;
    }
}

void trifusion(int tab[], int m){
    if (n==1)
        return;
    int *R, *S;
    R = (int*)malloc((n/2)*sizeof(int));
    S = (int*)malloc((n-n/2)*sizeof(int));
    if (R == NULL || S == NULL)
        exit(1);
    copier(T,0,n/2,R);
    copier(T,n/2,n,S);
    trifusion(R,n/2);
    trifusionf(S,n-n/2);
    fusion(R,n/2,S,n-n/2,T);
    free(R);
    free(S);
}