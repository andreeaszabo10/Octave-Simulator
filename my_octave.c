#include <stdio.h>
#include <stdlib.h>
#define const 10007

//citirea unei matrice de la tastatura
void citire(int idx, int m, int n, int ***mat, int *suma)
{
	int i, j;
//citesc elementele matricei si calculez suma lor
	suma[idx] = 0;
	for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j) {
			scanf("%d", &mat[idx][i][j]);
			suma[idx] = suma[idx] + mat[idx][i][j];
		}
//verific daca suma e pozitiva sau nu si calculez noua suma conform cerintei
	if (suma[idx] >= 0)
		suma[idx] = suma[idx] % const;
	else
		suma[idx] = suma[idx] % const + const;
}

//printarea unei matrici
void scriere(int idx, int m, int n, int ***mat)
{
	int i, j;
//afisez fiecare element al matricei indicate % 10007
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j)
			printf("%d ", mat[idx][i][j] % const);
		printf("\n");
	}
}

//operatia de afisare dimensiunilor unei matrice
void opD(int *linii, int *cols, int idx)
{
	int indx;
//citesc indexul de la tastatura
	scanf("%d", &indx);
//afisez dimensiunile daca exista matricea cu indexul respectiv
	if (idx < indx || indx < 0)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", linii[indx], cols[indx]);
}

//operatia de printare a unei matrice
void opP(int *linii, int *cols, int idx, int ***mat, int *v)
{
	int indx;
//citesc indexul de la tastatura
	scanf("%d", &indx);
//printez matricea daca exista o matrice cu indexul respectiv
	if (idx < indx || indx < 0)
		printf("No matrix with the given index\n");
	else
		scriere(v[indx], linii[indx], cols[indx], mat);
}

//inmultirea a doua matrice
void prod(int i1, int i2, int idx, int *linii, int *cols, int ***mat, int *v)
{
int i, j, k;
//noua matrice are acelasi nr de linii ca prima si de coloane ca a doua
for (i = 0; i < linii[i1]; ++i) {
	for (j = 0; j < cols[i2]; ++j) {
		mat[idx][i][j] = 0;
		for (k = 0; k < cols[i1]; ++k)
			mat[idx][i][j] += (mat[v[i1]][i][k] * mat[v[i2]][k][j]) % const;
		if (mat[idx][i][j] >= 0)
			mat[idx][i][j] = mat[idx][i][j] % const;
		else
			mat[idx][i][j] = mat[idx][i][j] % const + const;
		}
	}
}

//operatia de inmultire a doua matrice
void opM(int idx, int *l, int *c, int *v, int ****mat, int *s, int i1, int i2)
{
	int i, j;
	idx++;
//ca sa nu se suprascrie vreo matrice dupa ordonare
	if (v[idx - 1] == idx) {
		v[idx] = idx + 1;
		*mat = (int ***)realloc(*mat, (idx + 2) * sizeof(int **));
	} else {
		v[idx] = idx;
		*mat = (int ***)realloc(*mat, (idx + 1) * sizeof(int **));
	}
	s[idx] = 0;
//am alocat memorie pentru noua matrice
	(*mat)[v[idx]] = (int **)malloc(l[i1] * sizeof(int *));
	for (i = 0; i < l[i1]; ++i)
		(*mat)[v[idx]][i] = (int *)malloc(c[i2] * sizeof(int));
	prod(i1, i2, v[idx], l, c, *mat, v);
//calculez suma pentru noua matrice
	for (i = 0; i < l[i1]; ++i)
		for (j = 0; j < c[i2]; ++j)
			s[idx] = s[idx] + (*mat)[v[idx]][i][j];
	if (s[idx] >= 0)
		s[idx] = s[idx] % const;
	else
		s[idx] = s[idx] % const + const;
//noua matrice are acelasi nr de linii ca prima si de coloane ca a doua
	l[idx] = l[i1];
	c[idx] = c[i2];
}

//calcularea transpusei
void transpunere(int m, int n, int **a, int **transpusa)
{
	int i, j;
	for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
			transpusa[j][i] = a[i][j];
}

//operatia de transpunere a unei matrice
void opT(int indx, int *linii, int *cols, int ***mat, int *v, int idx)
{
	int i, aux, j;
//citesc indexul si calculez transpusa daca exista matricea cu acel index
	scanf("%d", &indx);
	if (idx < indx || indx < 0) {
		printf("No matrix with the given index\n");
	} else {
//aloc memorie pentru o matrice auxiliara in care calculez transpusa
		int **transpusa;
			transpusa = (int **)malloc(cols[indx] * sizeof(int *));
		for (i = 0; i < cols[indx]; ++i)
			transpusa[i] = (int *)malloc(linii[indx] * sizeof(int));
//aloc memorie pentru o matrice in care copiez elementele matricei principale
		int **a;
		a = (int **)malloc(linii[indx] * sizeof(int *));
		for (i = 0; i < linii[indx]; ++i)
			a[i] = (int *)malloc(cols[indx] * sizeof(int));
//copiez elementele si eliberez matricea
		for (i = 0; i < linii[indx]; ++i) {
			for (int j = 0; j < cols[indx]; ++j)
				a[i][j] = mat[v[indx]][i][j];
			free(mat[v[indx]][i]);
		}
		free(mat[v[indx]]);
//aloc memorie pentru matricea noua si copiez elementele transpusei in ea
		mat[v[indx]] = (int **)malloc(cols[indx] * sizeof(int *));
		for (i = 0; i < cols[indx]; ++i)
			mat[v[indx]][i] = (int *)malloc(linii[indx] * sizeof(int));
		transpunere(linii[indx], cols[indx], a, transpusa);
		for (i = 0; i < cols[indx]; ++i)
			for (j = 0; j < linii[indx]; ++j)
				mat[v[indx]][i][j] = transpusa[i][j];
//eliberez memoria matricelor auxiliare si retin noile dimensiuni
		for (i = 0; i < cols[indx]; ++i)
			free(transpusa[i]);
		free(transpusa);
		aux = linii[indx];
		linii[indx] = cols[indx];
		cols[indx] = aux;
		for (i = 0; i < cols[indx]; ++i)
			free(a[i]);
		free(a);
	}
}

//operatia de ordonare a matricelor
void opO(int idx, int *suma, int *linii, int *cols, int *v)
{
	int i, j, aux;
//algoritm de sortare crescatoare a caracteristicilor unei matrice
	for (i = 0; i < idx; ++i)
		for (j = i + 1; j < idx + 1; ++j)
			if (suma[i] > suma[j]) {
//interschimb indecsii din vectorul v, sumele, numarul de linii si de coloane
				aux = linii[i];
				linii[i] = linii[j];
				linii[j] = aux;
				aux = cols[i];
				cols[i] = cols[j];
				cols[j] = aux;
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
				aux = suma[i];
				suma[i] = suma[j];
				suma[j] = aux;
			}
}

//operatia de redimensionare
void opC(int ****mat, int idx, int *linii, int *cols, int *v, int *suma)
{
	int indx, lin, col, i, j, *w, *a, **maux;
//citesc nr de linii si aloc memorie unui vector care retine indecsii liniilor
	scanf("%d %d", &indx, &lin);
	w = malloc(lin * sizeof(int));
	for (i = 0; i < lin; ++i)
		scanf("%d", &w[i]);
//la fel si pentru coloane
	scanf("%d", &col);
	a = malloc(col * sizeof(int));
	for (i = 0; i < col; ++i)
		scanf("%d", &a[i]);
//aloc memorie pentru o matrice auxiliara care retine elementele noii matrice
	maux = (int **)malloc(lin * sizeof(int *));
	for (i = 0; i < lin; ++i)
		maux[i] = (int *)malloc(col * sizeof(int));
//verific daca se poate efectua operatia
	if (idx < indx || indx < 0) {
		printf("No matrix with the given index\n");
	} else {
		for (i = 0; i < lin; ++i)
			for (j = 0; j < col; ++j)
				maux[i][j] = (*mat)[v[indx]][w[i]][a[j]];
//eliberez matricea si ii aloc memorie pentru noile dimensiuni
		for (i = 0; i < linii[indx]; ++i)
			free((*mat)[v[indx]][i]);
		free((*mat)[v[indx]]);
		(*mat)[v[indx]] = (int **)malloc(lin * sizeof(int *));
		for (i = 0; i < lin; ++i)
			(*mat)[v[indx]][i] = (int *)malloc(col * sizeof(int));
		linii[indx] = lin;
		cols[indx] = col;
//pun elementele din matricea auxiliara in cea principala si fac suma
		suma[indx] = 0;
		for (i = 0; i < lin; ++i)
			for (j = 0; j < col; ++j) {
				(*mat)[v[indx]][i][j] = maux[i][j];
				suma[indx] = suma[indx] + (*mat)[v[indx]][i][j];
			}
		if (suma[indx] >= 0)
			suma[indx] = suma[indx] % const;
		else
			suma[indx] = suma[indx] % const + const;
	}
//eliberez resursele auxiliare
	free(w);
	free(a);
	for (i = 0; i < lin; ++i)
		free(maux[i]);
	free(maux);
}

//operatia de eliminare a unei matrice
void opF(int idx, int indx, int *linii, int ***mat, int *v, int *col, int *suma)
{
	int i, j;
//daca matricea care trebuie eliberata e ultima din lista ii dau free
	if (indx == idx) {
		for (i = 0; i < linii[indx]; ++i)
			free(mat[v[indx]][i]);
		free(mat[v[indx]]);
	} else {
//altfel, schimb matricele, incepand de la matricea care trebuie eliberata
		for (j = indx; j < idx; ++j) {
//eliberez memoria pt matrice si ii aloc memorie dupa dimensiunile urmatoarei
			for (i = 0; i < linii[j]; ++i)
				free(mat[v[j]][i]);
			free(mat[v[j]]);
			mat[v[j]] = (int **)malloc(linii[j + 1] * sizeof(int *));
			for (i = 0; i < linii[j + 1]; ++i)
				mat[v[j]][i] = (int *)malloc(col[j + 1] * sizeof(int));
//mut elementele din matricea urmatoare in cea curenta
			for (i = 0; i < linii[j + 1]; ++i)
				for (int k = 0; k < col[j + 1]; ++k)
					mat[v[j]][i][k] = mat[v[j + 1]][i][k];
//matricea curenta primeste caracteristicile urmatoarei din lista
			linii[j] = linii[j + 1];
			col[j] = col[j + 1];
			suma[j] = suma[j + 1];
		}
//eliberez ultima matrice, dupa ce a fost retinuta cu o pozitie in fata
		for (i = 0; i < linii[idx]; ++i)
			free(mat[v[idx]][i]);
		free(mat[v[idx]]);
	}
}

//ridicare la putere a unei matrice
void putere(int **a, long exp, int linii, int **rez)
{
	int i, j, k, **prod;
//aloc memorie pentru matricea in care voi retine produsele
	prod = (int **)malloc(linii * sizeof(int *));
	if (!prod) {
		printf("Alocarea a esuat");
		prod = NULL;
		return;
	}
	for (i = 0; i < linii; ++i)
		prod[i] = (int *)malloc(linii * sizeof(int));
//initializez matricea rezultat cu I3
	for (i = 0; i < linii; ++i)
		for (j = 0; j < linii; ++j) {
			if (i == j)
				rez[i][j] = 1;
			else
				rez[i][j] = 0;
		}
//iau fiecare bit din reprezentarea binara a exponentului
	while (exp > 0) {
//daca exp e impar matricea rezultat devine produsul dintre ea si matricea a
		if (exp % 2 == 1) {
//algoritmul de inmultire a doua matrice patratice
			for (i = 0; i < linii; ++i) {
				for (j = 0; j < linii; ++j) {
					prod[i][j] = 0;
					for (k = 0; k < linii; ++k)
						prod[i][j] = prod[i][j] + (rez[i][k] * a[k][j]) % const;
					if (prod[i][j] >= 0)
						prod[i][j] = prod[i][j] % const;
					else
						prod[i][j] = prod[i][j] % const + const;
				}
			}
//elementele matricei rezultat devin elementele matricei produs
			for (i = 0; i < linii; ++i)
				for (j = 0; j < linii; ++j)
					rez[i][j] = prod[i][j];
		}
//matricea a este ridicata la patrat
//algoritmul de inmultire a doua matrice patratice
		for (i = 0; i < linii; ++i) {
			for (j = 0; j < linii; ++j) {
				prod[i][j] = 0;
				for (k = 0; k < linii; ++k)
					prod[i][j] = prod[i][j] + (a[i][k] * a[k][j]) % const;
				if (prod[i][j] >= 0)
					prod[i][j] = prod[i][j] % const;
				else
					prod[i][j] = prod[i][j] % const + const;
			}
		}
//elementele matricei a devin elementele matricei produs
		for (i = 0; i < linii; ++i)
			for (j = 0; j < linii; ++j)
				a[i][j] = prod[i][j];
//impart exponentul la 2 ca sa ajung la urmatorul bit
		exp = exp / 2;
	}
//eliberez matricea produs
	for (i = 0; i < linii; ++i)
		free(prod[i]);
	free(prod);
}

//operatia de ridicare la putere
void opR(int *v, int *l, int *c, int indx, long p, int ****mat, int *s)
{
	int i, j, **aux, **rez;
//aloc memorie pentru matricea rezultat si cea auxiliara
	rez = (int **)malloc(l[indx] * sizeof(int *));
	if (!rez) {
		printf("Alocarea a esuat");
		rez = NULL;
		return;
	}
	for (i = 0; i < l[indx]; ++i)
		rez[i] = (int *)malloc(l[indx] * sizeof(int));
	aux = (int **)malloc(l[indx] * sizeof(int *));
	if (!aux) {
		printf("Alocarea a esuat");
		aux = NULL;
		return;
	}
	for (i = 0; i < l[indx]; ++i)
		aux[i] = (int *)malloc(l[indx] * sizeof(int));
//matricea auxiliara primeste elementele matricei care trebuie ridicata
	for (i = 0; i < l[indx]; ++i)
		for (j = 0; j < l[indx]; ++j)
			aux[i][j] = (*mat)[v[indx]][i][j];
//efectuez operatia de ridicare la putere
	putere(aux, p, l[indx], rez);
//matricea principala primeste elementele matricei rezultat
	for (i = 0; i < l[indx]; ++i)
		for (j = 0; j < l[indx]; ++j) {
			if (rez[i][j] >= 0)
				rez[i][j] = rez[i][j] % const;
			else
				rez[i][j] = rez[i][j] % const + const;
			(*mat)[v[indx]][i][j] = rez[i][j];
		}
//eliberez resursele auxiliare
	for (i = 0; i < l[indx]; ++i) {
		free(rez[i]);
		free(aux[i]);
	}
	free(aux);
	free(rez);
//calculez suma pentru noua matrice
	s[indx] = 0;
	for (i = 0; i < l[indx]; ++i)
		for (j = 0; j < c[indx]; ++j)
			s[indx] = s[indx] + (*mat)[v[indx]][i][j] % const;
	if (s[indx] >= 0)
		s[indx] = s[indx] % const;
	else
		s[indx] = s[indx] % const + const;
}

//alocare de memorie pentru vectorul suma, de indecsi(*v), de linii si coloane
void initializare(int **linii, int **cols, int **v, int **suma)
{
	int i;
	*suma = malloc(2000 * sizeof(int));
	for (i = 0; i < 2000; ++i)
		(*suma)[i] = 0;
	*v = malloc(2000 * sizeof(int));
	*linii = malloc(2000 * sizeof(int));
	*cols = malloc(2000 * sizeof(int));
}

//operatia pentru introducerea unei matrice
void opL(int **linii, int **cols, int **v, int ****mat, int idx)
{
	int i, lin, col;
	scanf("%d %d", &lin, &col);
//aloc daca este prima matrice introdusa, realoc altfel
//folosesc programare defensiva
	if (!(*mat)) {
		(*mat) = (int ***)malloc((idx + 1) * sizeof(int **));
		if (!(*mat)) {
			printf("Alocarea a esuat");
			*mat = NULL;
			return;
		}
	} else {
		(*mat) = (int ***)realloc((*mat), (idx + 1) * sizeof(int **));
		if (!(*mat)) {
			printf("Alocarea a esuat");
			*mat = NULL;
			return;
		}
	}
	(*v)[idx] = idx;
	(*linii)[idx] = lin;
	(*cols)[idx] = col;
	(*mat)[idx] = (int **)malloc(lin * sizeof(int *));
	for (i = 0; i < lin; ++i)
		(*mat)[idx][i] = (int *)malloc(col * sizeof(int));
}

//operatia de eliberare a resurselor
void opQ(int idx, int **linii, int **cols, int ****mat, int **v, int **s)
{	int i, j;
//eliberez memoria pentru toate cele idx + 1 matrice
	for (i = 0; i <= idx; ++i) {
		for (j = 0; j < (*linii)[i]; ++j)
			free((*mat)[(*v)[i]][j]);
		if ((*mat)[(*v)[i]])
			free((*mat)[(*v)[i]]);
	}
	free(*mat);
//eliberez memoria pentru vectorii care retineau caracteristicile matricelor
	free(*linii);
	free(*cols);
	free(*s);
	free(*v);
}

//adunarea a doua matrice
int **adunare(int m, int **a, int **b)
{
	int **sum, i, j;
//aloc memorie pentru matricea rezultat si efectuez suma
	sum = (int **)malloc(m * sizeof(int *));
	for (i = 0; i < m; ++i)
		sum[i] = (int *)malloc(m * sizeof(int));
	for (i = 0; i < m; ++i)
		for (j = 0; j < m; ++j)
			sum[i][j] = 0;
	for (i = 0; i < m; ++i)
		for (j = 0; j < m; ++j) {
			if ((a[i][j] + b[i][j]) >= 0)
				sum[i][j] = (a[i][j] + b[i][j]) % const;
			else
				sum[i][j] = (a[i][j] + b[i][j]) % const + const;
		}
	return sum;
}

//diferenta a doua matrice
int **dif(int m, int **a, int **b)
{
	int **diferenta, i, j;
//aloc memorie pentru matricea rezultat si fac diferenta
	diferenta = (int **)malloc(m * sizeof(int *));
	for (i = 0; i < m; ++i)
		diferenta[i] = (int *)malloc(m * sizeof(int));
	for (i = 0; i < m; ++i)
		for (j = 0; j < m; ++j)
			diferenta[i][j] = 0;
	for (i = 0; i < m; ++i)
		for (j = 0; j < m; ++j) {
			if ((a[i][j] - b[i][j]) >= 0)
				diferenta[i][j] = (a[i][j] - b[i][j]) % const;
			else
				diferenta[i][j] = (a[i][j] - b[i][j]) % const + const;
		}
	return diferenta;
}

//alocare pentru 5 matrice auxiliare
void aloc1(int ***m1, int ***m2, int ***m3, int ***m4, int ***m5, int k)
{	int i;
	*m1 = (int **)malloc(k * sizeof(int *));
	*m2 = (int **)malloc(k * sizeof(int *));
	*m3 = (int **)malloc(k * sizeof(int *));
	*m4 = (int **)malloc(k * sizeof(int *));
	*m5 = (int **)malloc(k * sizeof(int *));
	for (i = 0; i < k; ++i) {
		(*m1)[i] = (int *)malloc(k * sizeof(int));
		(*m2)[i] = (int *)malloc(k * sizeof(int));
		(*m3)[i] = (int *)malloc(k * sizeof(int));
		(*m4)[i] = (int *)malloc(k * sizeof(int));
		(*m5)[i] = (int *)malloc(k * sizeof(int));
	}
}

//alocare pentru 4 matrice (2 functii ptr nr de linii in "strassen")
void aloc2(int ***c1, int ***c2, int ***c3, int ***c4, int k)
{	int i;
	*c1 = (int **)malloc(k * sizeof(int *));
	*c2 = (int **)malloc(k * sizeof(int *));
	*c3 = (int **)malloc(k * sizeof(int *));
	*c4 = (int **)malloc(k * sizeof(int *));
	for (i = 0; i < k; ++i) {
		(*c1)[i] = (int *)malloc(k * sizeof(int));
		(*c2)[i] = (int *)malloc(k * sizeof(int));
		(*c3)[i] = (int *)malloc(k * sizeof(int));
		(*c4)[i] = (int *)malloc(k * sizeof(int));
	}
}

//eliberarea memoriei a 5 matrice auxiliare
void free1(int ***m1, int ***m2, int ***m3, int ***m4, int ***m5, int k)
{
	int i;
	for (i = 0; i < k; ++i) {
		free((*m1)[i]);
		free((*m2)[i]);
		free((*m3)[i]);
		free((*m4)[i]);
		free((*m5)[i]);
	}
	free(*m1);
	free(*m2);
	free(*m3);
	free(*m4);
	free(*m5);
}

//eliberarea memoriei a 4 matrice (2 functii ptr nr de linii in "strassen")
void free2(int ***c1, int ***c2, int ***c3, int ***c4, int k)
{
	int i;
	for (i = 0; i < k; ++i) {
		free((*c1)[i]);
		free((*c2)[i]);
		free((*c3)[i]);
		free((*c4)[i]);
	}
	free(*c1);
	free(*c2);
	free(*c3);
	free(*c4);
}

//reconstruirea primului careu al matricei rezultat
void reconstruire(int k, int **c1, int **c)
{	int i, j;
//pun in primul careu al matricei c elementele din matricea auxiliara c1
	for (i = 0; i < k; ++i)
		for (j = 0; j < k; ++j) {
			if (c1[i][j] >= 0)
				c[i][j] = c1[i][j] % const;
			else
				c[i][j] = c1[i][j] % const + const;
		}
}

//algoritmul strassen
int **strassen(int **a, int **b, int n)
{	int **c, i, j, **aux2, **aux3, **aux4, **aux5;
	c = (int **)malloc(n * sizeof(int *)); //alocarea pentru matricea rezultat
	for (i = 0; i < n; ++i)
		c[i] = (int *)malloc(n * sizeof(int));
	if (n == 1) { //daca matricea e de 1 pe 1
		c[0][0] = (a[0][0] * b[0][0]) % const;
		return c;
	}
	int k = n / 2, **a1, **a2, **a3, **a4, **b1, **b2, **b3, **b4, **aux1;
	int **m1, **m2, **m3, **m4, **m5, **m6, **m7, **c1, **c2, **c3, **c4;
	aloc2(&b1, &b2, &b3, &b4, k);//alocarea memoriei pentru resursele auxiliare
	aloc2(&a1, &a2, &a3, &a4, k);
	for (i = 0; i < k; ++i) //impartirea in careuri a celor 2 matrice
		for (j = 0; j < k; ++j) {
			a1[i][j] = a[i][j];
			a2[i][j] = a[i][j + k];
			a3[i][j] = a[i + k][j];
			a4[i][j] = a[i + k][j + k];
			b1[i][j] = b[i][j];
			b2[i][j] = b[i][j + k];
			b3[i][j] = b[i + k][j];
			b4[i][j] = b[i + k][j + k];
		}
	aux1 = adunare(k, a1, a4);//matrice auxiliare pentru eliberarea memoriei
	aux2 = adunare(k, b1, b4);
	aux3 = adunare(k, a3, a4);
	aux4 = dif(k, b2, b4);
	aux5 = dif(k, b3, b1);
	m1 = strassen(aux1, aux2, k);//matricele m sunt aflate cu formule recursiv
	m2 = strassen(aux3, b1, k);
	m3 = strassen(a1, aux4, k);
	m4 = strassen(a4, aux5, k);
	free1(&aux1, &aux2, &aux3, &aux4, &aux5, k);//eliberare memorie operatii
	aux1 = adunare(k, a1, a2);//matrice auxiliare pentru eliberarea memoriei
	aux2 = dif(k, a3, a1);
	aux3 = adunare(k, b1, b2);
	aux4 = dif(k, a2, a4);
	aux5 = adunare(k, b3, b4);
	m5 = strassen(aux1, b4, k);
	m6 = strassen(aux2, aux3, k);
	m7 = strassen(aux4, aux5, k);
	free1(&aux1, &aux2, &aux3, &aux4, &aux5, k);//eliberare memorie operatii
	aux1 = adunare(k, m1, m4);//matrice auxiliare pentru eliberarea memoriei
	aux2 = dif(k, aux1, m5);
	aux3 = dif(k, m1, m2);
	aux4 = adunare(k, aux3, m3);
	c1 = adunare(k, aux2, m7);//calculul celor 4 careuri ale matricei rezultat
	c2 = adunare(k, m3, m5);
	c3 = adunare(k, m2, m4);
	c4 = adunare(k, aux4, m6);
	free2(&aux1, &aux2, &aux3, &aux4, k);//eliberare memorie operatii
	reconstruire(k, c1, c); //reconstruirea primului careu al matricei rezultat
	for (i = 0; i < k; ++i) //reconstruire careu 2 in matricea mare
		for (j = k; j < n; ++j) {
			if (c2[i][j - k] >= 0)
				c[i][j] = c2[i][j - k] % const;
			else
				c[i][j] = c2[i][j - k] % const + const;
		}
	for (i = k; i < n; ++i) //reconstruire careu 3 in matricea mare
		for (j = 0; j < k; ++j) {
			if (c3[i - k][j] >= 0)
				c[i][j] = c3[i - k][j] % const;
			else
				c[i][j] = c3[i - k][j] % const + const;
		}
	for (i = k; i < n; ++i) //reconstruire careu 4 in matricea mare
		for (j = k; j < n; ++j) {
			if (c4[i - k][j - k] >= 0)
				c[i][j] = c4[i - k][j - k] % const;
			else
				c[i][j] = c4[i - k][j - k] % const + const;
		}
//eliberarea resurselor auxiliare
	free1(&m1, &m2, &m3, &m4, &m5, k);
	free1(&m6, &m7, &a1, &a2, &a3, k);
	free1(&b1, &b2, &b3, &b4, &a4, k);
	free2(&c1, &c2, &c3, &c4, k);
	return c;
}

//operatia cu algoritmul lui strassen
void opS(int *v, int *l, int *c, int i1, int i2, int ****mat, int idx, int *s)
{	int i, j, **aux;
//aloc memorie pentru noua matrice si ii retin caracteristicile
	v[idx] = idx;
	l[idx] = l[i1];
	c[idx] = c[i2];
	(*mat) = (int ***)realloc((*mat), (idx + 1) * sizeof(int **));
	(*mat)[v[idx]] = (int **)malloc(l[i1] * sizeof(int *));
	for (i = 0; i < l[i1]; ++i)
		(*mat)[v[idx]][i] = (int *)malloc(l[i1] * sizeof(int));
//efectuez algoritmul si retin rezultatul in matricea aux
	aux = strassen((*mat)[v[i1]], (*mat)[v[i2]], l[i1]);
//retin elementele rezultatului in matricea principala, eliberez memoria pt aux
	for (i = 0; i < l[i1]; ++i) {
		for (j = 0; j < c[i2]; ++j) {
			(*mat)[v[idx]][i][j] = aux[i][j];
			s[idx] = s[idx] + (*mat)[v[idx]][i][j];
		}
		free(aux[i]);
	}
	free(aux);
//calculez suma elementelor noii matrice
	if (s[idx] >= 0)
		s[idx] = s[idx] % const;
	else
		s[idx] = s[idx] % const + const;
}

//citirea unui caracter invalid
void mesaj(char op)
{
	if (op != 'L' && op != ' ' && op != 'M' && op != 'T' && op != 'S')
		if (op != 'P' && op != 'O' && op != 'C' && op != 'D' && op != 'Q')
			if (op != 'R' && op != '\n' && op != 'F')
				printf("Unrecognized command\n");
}

int main(void)
{	//declararea variabilelor
	int idx = -1, ***mat = NULL, indx, *linii, *cols, i1, i2, *suma, *v, x = 1;
	long exp;
	char op;
	while (scanf("%c", &op)) {
		if (op == 'L') {
			idx++;
			if (idx == 0 && x == 1) { //daca e prima matrice introdusa
				initializare(&linii, &cols, &v, &suma);
				x = 0; //daca este 0 -> a fost introdusa cel putin o matrice
			}
			opL(&linii, &cols, &v, &mat, idx);
			citire(idx, linii[idx], cols[idx], mat, suma);
		}
		if (op == 'D')
			opD(linii, cols, idx);
		if (op == 'P')
			opP(linii, cols, idx, mat, v);
		if (op == 'C')
			opC(&mat, idx, linii, cols, v, suma);
		if (op == 'M') { //citesc indicii celor 2 matrice
			scanf("%d %d", &i1, &i2); //verific daca se poate face operatia
			if (idx < i1 || idx < i2 || i1 < 0 || i2 < 0) {
				printf("No matrix with the given index\n");
			} else {
				if (cols[i1] != linii[i2]) {
					printf("Cannot perform matrix multiplication\n");
				} else {
					opM(idx, linii, cols, v, &mat, suma, i1, i2);
					idx++;
				}
			}
		}
		if (op == 'O')
			opO(idx, suma, linii, cols, v);
		if (op == 'T')
			opT(indx, linii, cols, mat, v, idx);
		if (op == 'R') {
			scanf("%d %ld", &indx, &exp);
			if (idx < indx || indx < 0) { //verific daca se poate face operatia
				printf("No matrix with the given index\n");
			} else {
				if (exp < 0) { //daca puterea e negativa
					printf("Power should be positive\n");
				} else {
					if (cols[indx] != linii[indx]) //daca nu e patratica
						printf("Cannot perform matrix multiplication\n");
					else
						opR(v, linii, cols, indx, exp, &mat, suma);
				}
			}
		}
		if (op == 'F') {
			scanf("%d", &indx); //verific daca se poate face operatia
			if (idx < indx || indx < 0) {
				printf("No matrix with the given index\n");
			} else {
				opF(idx, indx, linii, mat, v, cols, suma);
				idx--;
			}
		}
		if (op == 'Q') {
			opQ(idx, &linii, &cols, &mat, &v, &suma);
			break; //programul se opreste la intalnirea lui "Q"
		}
		if (op == 'S') {
			scanf("%d %d", &i1, &i2); //verific daca se poate face operatia
			if (idx < i1 || idx < i2 || i1 < 0 || i2 < 0) {
				printf("No matrix with the given index\n");
			} else {
				if (cols[i1] != linii[i2]) {
					printf("Cannot perform matrix multiplication\n");
				} else {
					idx++;
					opS(v, linii, cols, i1, i2, &mat, idx, suma);
				}
			}
		}
		mesaj(op); //verific daca este o comanda nerecunoscuta
	}
}
