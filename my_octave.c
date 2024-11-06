#include <stdio.h>
#include <stdlib.h>
#define MOD 10007
struct matrice {
	int **mat;
	int coloane, linii;
};

void eroare(void)
{
	fprintf(stderr, "Nu s a reusit alocarea\n");
	exit(-2);
}

// functie care aloca memorie
int **alocare_matrice(int n, int m)
{
	int **mat1;
	mat1 = (int **)malloc(n * sizeof(int *));
	// programare defensiva
	if (!mat1)
		eroare();

	int i;
	for (i = 0; i < n; i++)
		mat1[i] = (int *)malloc(m * sizeof(int));
	return mat1;
}

// functie pentru a realoca memorie
struct matrice *realocare_matrice(struct matrice *mat1, int marime)
{
	struct matrice *mat2;
	mat2 = realloc(mat1, marime * sizeof(struct matrice));
	// programare defensiva
	if (!mat2) {
		fprintf(stderr, "nu s a reusit alocarea\n");
		free(mat1);
		exit(-2);
	}
	return mat2;
}

// functie care citeste o noua matrice
// si o adauga in lista de matrice
struct matrice *citire_matrice(struct matrice *mat1, int *nr, int *marime)
{
	if (*nr == *marime - 1) {
		*marime = *marime + 1;
		mat1 = realocare_matrice(mat1, *marime);
	}
	// aloc spatiu pentru matricea nou citita
	mat1[*nr].mat = alocare_matrice(mat1[*nr].linii, mat1[*nr].coloane);
	int i, j;
	for (i = 0; i < mat1[*nr].linii; i++)
		for (j = 0; j < mat1[*nr].coloane; j++)
			scanf("%d", &mat1[*nr].mat[i][j]);
	(*nr)++;
	return mat1;
}

// determina dimensiunile unei matrice
void det_dimensiuni(struct matrice *mat1, int nr, int index)
{
	if (index < 0 || index >= nr) {
		printf("No matrix with the given index\n");
	} else {
		int linii, coloane;
		linii = mat1[index].linii;
		coloane = mat1[index].coloane;
		printf("%d %d\n", linii, coloane);
		}
}

// afisarea unei matrice
void afisare_mat(struct matrice *mat1, int nr, int index)
{
	// verificare daca exista matricea
	// cu indexul cerut
	if (index < 0 || index >= nr) {
		printf("No matrix with the given index\n");
	} else {
		int i, j, nr_lin, nr_col;
		nr_lin = mat1[index].linii;
		nr_col = mat1[index].coloane;
		for (i = 0; i < nr_lin; i++) {
			for (j = 0; j < nr_col; j++)
				printf("%d ", mat1[index].mat[i][j]);
			printf("\n");
		}
	}
}

// functie care elibereaza memoria
// pentru o singura matrice
void matrice_elibmemorie(int **mat1, int n)
{
	int i;
	// daca exista matricea atunci
	// voi elibera spatiul ocupat
	if (mat1) {
		for (i = 0; i < n; i++)
			if (mat1[i])
				free(mat1[i]);
		free(mat1);
	}
}

void mat_redimensionare(struct matrice *mat1, int nr, int index)
{
	int lin, col, i, j;
	scanf("%d", &lin);
	int *lin_redim, *col_redim;
	// aloc spatiu pentru lniile
	// dupa care ar trebui facuta redimensionarea
	lin_redim = (int *)malloc(lin * sizeof(int));
	// programare defensiva
	if (!lin_redim)
		eroare();
	for (i = 0; i < lin; i++)
		scanf("%d", &lin_redim[i]);

	scanf("%d", &col);
	// aloc spatiu pentru coloanele
	// pentru care ar trebui facuta redimensionarea
	col_redim = (int *)malloc(col * sizeof(int));
	// programare defensiva
	if (!col_redim)
		eroare();
	for (i = 0; i < col; i++)
		scanf("%d", &col_redim[i]);

	// verificare daca matricea exista
	if (index < 0 || index >= nr) {
		printf("No matrix with the given index\n");
		free(lin_redim);
		free(col_redim);
		return;
	}
	int **auxmat;
	// aloc spatiu pentru matricea
	// pe care o voi forma dupa redimensionare
	auxmat = alocare_matrice(lin, col);
	for (i = 0; i < lin; i++)
		for (j = 0; j < col; j++)
			auxmat[i][j] = mat1[index].mat[lin_redim[i]][col_redim[j]];
	// eliberez matricea anterioara
	// pentru a face spatiu pentru cea ceruta
	matrice_elibmemorie(mat1[index].mat, mat1[index].linii);

	// atribui dimensiunile noi
	// pentru matricea nou creata
	mat1[index].mat = auxmat;
	mat1[index].linii = lin;
	mat1[index].coloane = col;

	free(lin_redim);
	free(col_redim);
}

// functie pentru inmultirea a doua matrice
struct matrice *inmultire_mat(struct matrice *mat1, int *nr, int *marime)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);
	// verific daca exista matricea cu indexul curent
	if (index1 < 0 || index2 < 0 || index1 >= *nr || index2 >= *nr) {
		printf("No matrix with the given index\n");
		return mat1;
	}

	if (mat1[index1].coloane != mat1[index2].linii) {
		printf("Cannot perform matrix multiplication\n");
		return mat1;
	}
	int i, nr_col2, **suma, j, k, nr_lin1, nr_lin2;
	nr_col2 = mat1[index2].coloane;
	nr_lin1 = mat1[index1].linii;
	nr_lin2 = mat1[index2].linii;

	if (*nr == *marime - 1) {
		*marime = *marime + 1;
		mat1 = realocare_matrice(mat1, *marime);
	}
	// aloc memorie pentru matricea ajutatoare
	// necesara realizarii inmultirii
	suma = alocare_matrice(nr_lin1, nr_col2);
	for (i = 0; i < nr_lin1; i++) {
		for (j = 0; j < nr_col2; j++) {
			suma[i][j] = 0;
			for (k = 0; k < nr_lin2; k++) {
				suma[i][j] += mat1[index1].mat[i][k] * mat1[index2].mat[k][j];
				suma[i][j] = suma[i][j] % MOD;
				suma[i][j] = ((suma[i][j] % MOD) + MOD) % MOD;
			}
		}
	}
	// voi adauga in lista o noua matrice
	// care va primi dimensiunile noi create
	mat1[*nr].mat = suma;
	mat1[*nr].linii = mat1[index1].linii;
	mat1[*nr].coloane = mat1[index2].coloane;
	(*nr)++;
	return mat1;
}

void transpunere_mat(struct matrice *mat1, int nr, int index)
{
	int i, j, **matnou;
	if (index < 0 || index >= nr) {
		printf("No matrix with the given index\n");
	} else {
		int linii = mat1[index].linii;
		int col = mat1[index].coloane;
		matnou = alocare_matrice(col, linii);
		// formez matricea transpusa
		// unde liniile vor deveni coloane si coloanele linii
		for (i = 0; i < linii; i++)
			for (j = 0; j < col; j++)
				matnou[j][i] = mat1[index].mat[i][j];
		// eliberez memoria pentru matricea anterioara
		// pentru a pune in locu ei matricea transpusa
		matrice_elibmemorie(mat1[index].mat, mat1[index].linii);

		mat1[index].mat = matnou;
		mat1[index].linii = col;
		mat1[index].coloane = linii;
	}
}

// functie de eliberare memorie pentru o functie cu indexul dat
void eliberare_memorie(struct matrice *mat1, int *nr, int index)
{
	int i;
	if (index < 0 || index >= *nr) {
		printf("No matrix with the given index\n");
	} else {
		matrice_elibmemorie(mat1[index].mat, mat1[index].linii);
		for (i = index + 1; i < *nr; i++)
			mat1[i - 1] = mat1[i];
		//descresc nr total de matrice din memorie
		(*nr)--;
	}
}

// functie pentru eliberarea memoriei tuturor matricilor
void eliberare_total_resurse(struct matrice *mat1, int nr)
{
	int i, j;
	for (i = 0; i < nr; i++) {
		for (j = 0; j < mat1[i].linii; j++)
			if (mat1[i].mat[j])
				free(mat1[i].mat[j]);
		if (mat1[i].mat)
			free(mat1[i].mat);
	}
	if (mat1)
		free(mat1);
}

// functie pentru a inmulti 2 matrici
void multiplic(int **mat1, int **mat2, int nr_linii)
{
	int **mat = alocare_matrice(nr_linii, nr_linii);
	int i, j, k;
	for (i = 0; i < nr_linii; i++) {
		for (j = 0; j < nr_linii; j++) {
			mat[i][j] = 0;
			for (k = 0; k < nr_linii; k++) {
				mat[i][j] = (mat[i][j] + mat1[i][k] * mat2[k][j]) % MOD;
				mat[i][j] = ((mat[i][j] % MOD) + MOD) % MOD;
			}
		}
	}

	for (int i = 0; i < nr_linii; i++) {
		for (int j = 0; j < nr_linii; j++)
			mat1[i][j] = mat[i][j];
	}
	// eliberez memoria alocata matricei mat
	matrice_elibmemorie(mat, nr_linii);
}

// functie pentru ridicarea la putere
void putere_matrice(struct matrice *mat1, int index, int nr, int putere)
{
	if (index < 0 || index >= nr) {
		printf("No matrix with the given index\n");
	} else if (putere < 0) {
		printf("Power should be positive\n");
	} else if (mat1[index].linii != mat1[index].coloane) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		int i, j, nr_linii = mat1[index].linii;
		struct matrice aux;
		int **aux_mat = alocare_matrice(nr_linii, nr_linii);
		aux.mat = aux_mat;
		aux.linii = nr_linii;
		aux.coloane = nr_linii;
		// matricea identitate
		for (i = 0; i < nr_linii; i++) {
			for (j = 0; j < nr_linii; j++)
				aux.mat[i][j] = mat1[index].mat[i][j];
		}

		putere--;
		while (putere > 0) {
			if (putere % 2 == 1)
				multiplic(mat1[index].mat, aux.mat, nr_linii);

			multiplic(aux.mat, aux.mat, nr_linii);
			putere /= 2;
		}
		matrice_elibmemorie(aux_mat, nr_linii);
	}
}

void sortare_mat(struct matrice *mat1, int nr)
{
	int i, j, k, *suma, sum;
	struct matrice sumaux;
	suma = (int *)malloc(nr * sizeof(int));
	if (!suma)
		eroare();
	for (k = 0; k < nr; k++) {
		suma[k] = 0;
		int linii, coloane;
		linii = mat1[k].linii;
		coloane = mat1[k].coloane;
		for (i = 0; i < linii; i++) {
			for (j = 0; j < coloane; j++) {
				suma[k] = (suma[k] + mat1[k].mat[i][j]) % MOD;
				suma[k] = ((suma[k] % MOD) + MOD) % MOD;
			}
		}
	}

	// voi sorta in functie de suma colectia de matrice
	// inclusiv sortez si sumele curente
	for (i = 0; i < nr - 1; i++) {
		for (j = i + 1; j < nr; j++) {
			if (suma[i] > suma[j]) {
				sumaux = mat1[i];
				mat1[i] = mat1[j];
				mat1[j] = sumaux;
				sum = suma[i];
				suma[i] = suma[j];
				suma[j] = sum;
			}
		}
	}
	if (suma)
		free(suma);
}

void adunare(struct matrice *m1, struct matrice *m2, struct matrice *m3, int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			(*m3).mat[i][j] = ((*m1).mat[i][j] + (*m2).mat[i][j]) % MOD;
			(*m3).mat[i][j] = (((*m3).mat[i][j] % MOD) + MOD) % MOD;
		}
	}
}

void scadere(struct matrice *m1, struct matrice *m2, struct matrice *m3, int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			(*m3).mat[i][j] = ((*m1).mat[i][j] - (*m2).mat[i][j]) % MOD;
			(*m3).mat[i][j] = (((*m3).mat[i][j] % MOD) + MOD) % MOD;
		}
	}
}

// functie recursiva pentru strassen
// am nevoie de 3 matrice pentru a realiza operatiile
void strassen(struct matrice *m1, struct matrice *m2, struct matrice *m3, int n)
{
	if (n == 1) {
		(*m3).mat[0][0] = (*m1).mat[0][0] * (*m2).mat[0][0];
		return;
	}
	int i, j;
	int n2 = n / 2;
	struct matrice *mat;
	mat = (struct matrice *)malloc(21 * sizeof(struct matrice));
	// programare defensiva
	if (!mat)
		eroare();

	for (i = 0; i < 21; i++) {
		mat[i].mat = alocare_matrice(n2, n2);
		mat[i].linii = n2;
		mat[i].coloane = n2;
	}
	for (i = 0; i < n2; i++) {
		for (j = 0; j < n2; j++) {
			mat[0].mat[i][j] = (*m1).mat[i][j];
			mat[1].mat[i][j] = (*m1).mat[i][j + n2];
			mat[2].mat[i][j] = (*m1).mat[i + n2][j];
			mat[3].mat[i][j] = (*m1).mat[i + n2][j + n2];
			mat[4].mat[i][j] = (*m2).mat[i][j];
			mat[5].mat[i][j] = (*m2).mat[i][j + n2];
			mat[6].mat[i][j] = (*m2).mat[i + n2][j];
			mat[7].mat[i][j] = (*m2).mat[i + n2][j + n2];
		}
	}
	for (i = 0; i < n2; i++) {
		for (j = 0; j < n2; j++) {
			(*m3).mat[i][j] = mat[8].mat[i][j];
			(*m3).mat[i][j + n2] = mat[9].mat[i][j];
			(*m3).mat[i + n2][j] = mat[10].mat[i][j];
			(*m3).mat[i + n2][j + n2] = mat[11].mat[i][j];
		}
	}
	adunare(&mat[0], &mat[3], &mat[19], n2);
	adunare(&mat[4], &mat[7], &mat[20], n2);
	strassen(&mat[19], &mat[20], &mat[12], n2);
	adunare(&mat[2], &mat[3], &mat[19], n2);
	strassen(&mat[19], &mat[4], &mat[13], n2);
	scadere(&mat[5], &mat[7], &mat[20], n2);
	strassen(&mat[0], &mat[20], &mat[14], n2);
	scadere(&mat[6], &mat[4], &mat[20], n2);
	strassen(&mat[3], &mat[20], &mat[15], n2);
	adunare(&mat[0], &mat[1], &mat[19], n2);
	strassen(&mat[19], &mat[7], &mat[16], n2);
	scadere(&mat[2], &mat[0], &mat[19], n2);
	adunare(&mat[4], &mat[5], &mat[20], n2);
	strassen(&mat[19], &mat[20], &mat[17], n2);
	scadere(&mat[1], &mat[3], &mat[19], n2);
	adunare(&mat[6], &mat[7], &mat[20], n2);
	strassen(&mat[19], &mat[20], &mat[18], n2);
	adunare(&mat[14], &mat[16], &mat[9], n2);
	adunare(&mat[13], &mat[15], &mat[10], n2);
	adunare(&mat[12], &mat[15], &mat[19], n2);
	adunare(&mat[19], &mat[18], &mat[20], n2);
	scadere(&mat[20], &mat[16], &mat[8], n2);
	adunare(&mat[12], &mat[14], &mat[19], n2);
	adunare(&mat[19], &mat[17], &mat[20], n2);
	scadere(&mat[20], &mat[13], &mat[11], n2);
	for (i = 0; i < n2; i++) {
		for (j = 0; j < n2; j++) {
			(*m3).mat[i][j] = mat[8].mat[i][j];
			(*m3).mat[i][j + n2] = mat[9].mat[i][j];
			(*m3).mat[i + n2][j] = mat[10].mat[i][j];
			(*m3).mat[i + n2][j + n2] = mat[11].mat[i][j];
		}
	}

	// eliberez memoria pentru matricile
	// formate anterior cu dimensiunea n/2
	for (int i = 0; i < 21; i++)
		matrice_elibmemorie(mat[i].mat, n2);
	free(mat);
}

struct matrice *init_strassen(struct matrice *mat1, int *nr, int marime)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);
	if (index1 < 0 || index2 < 0 || index1 >= *nr || index2 >= *nr) {
		printf("No matrix with the given index\n");
	} else if (mat1[index1].coloane != mat1[index2].linii ||
	mat1[index1].linii != mat1[index1].coloane ||
	mat1[index2].linii != mat1[index2].coloane) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		struct matrice mat;
		mat.mat = alocare_matrice(mat1[index1].linii, mat1[index2].coloane);
		mat.linii = mat1[index1].linii;
		mat.coloane = mat1[index2].coloane;
		// apelez functia strassen
		strassen(&mat1[index1], &mat1[index2], &mat, mat.linii);
		// verific daca este loc pentru a adauga matricea nou creata
		if (*nr == marime - 1) {
			marime = marime + 1;
			mat1 = realocare_matrice(mat1, marime);
		}
		// matricea nou creata va primi
		// dimensiunile corespunzatoare
		mat1[*nr].mat = mat.mat;
		mat1[*nr].linii = mat1[index1].linii;
		mat1[*nr].coloane = mat1[index2].coloane;
		(*nr)++;
	}
	return mat1;
}

int main(void)
{
	char chr;
	int nr = 0, marime = 1, ok = 1;
	struct matrice *mat1;
	mat1 = (struct matrice *)malloc(marime * sizeof(struct matrice));
	// programare defensiva
	if (!mat1)
		eroare();

	scanf(" %c", &chr);
	while (ok == 1) {
		if (chr == 'L') {
			scanf("%d%d", &mat1[nr].linii, &mat1[nr].coloane);
			mat1 = citire_matrice(mat1, &nr, &marime);
		} else if (chr == 'D') {
			int index;
			scanf("%d", &index);
			det_dimensiuni(mat1, nr, index);
		} else if (chr == 'P') {
			int index;
			scanf("%d", &index);
			afisare_mat(mat1, nr, index);
		} else if (chr == 'C') {
			int index;
			scanf("%d", &index);
			mat_redimensionare(mat1, nr, index);
		} else if (chr == 'M') {
			mat1 = inmultire_mat(mat1, &nr, &marime);
		} else if (chr == 'T') {
			int index;
			scanf("%d", &index);
			transpunere_mat(mat1, nr, index);
		} else if (chr == 'F') {
			int index;
			scanf("%d", &index);
			eliberare_memorie(mat1, &nr, index);
		} else if (chr == 'R') {
			int index, power;
			scanf("%d%d", &index, &power);
			putere_matrice(mat1, index, nr, power);
		} else if (chr == 'O') {
			sortare_mat(mat1, nr);
		} else if (chr == 'S') {
			mat1 = init_strassen(mat1, &nr, marime);
		} else if (chr == 'Q') {
			ok = 0;
		} else {
			printf("Unrecognized command\n");
		}

		scanf(" %c", &chr);
	}
	eliberare_total_resurse(mat1, nr);
	return 0;
}
