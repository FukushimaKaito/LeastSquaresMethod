/*-----------------------------------------------
課題10 最小二乗法

4I31 福嶋　開人
2015/01/30
----------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KB 1024//文字サイズ
#define M 3
#define N 4

/*	関数プロトタイプ宣言	*/
void zensin(void);//前進消去
double pibot(int);//ピボット選択
void koutai(void);//後退代入

double a[M][N];

struct abc
{
	double x;
	double y;
};

int main(void) {

	//変数を宣言
	char buf[KB];//行数読み込み
	FILE *fp = NULL;//ファイルポインタ
	int L;//行数格納
	struct abc *data;//データ格納構造体

	printf("課題10 最小二乗法\n");

	//ファイルをおっぷん
	if ((fopen_s(&fp, "C:\\Users\\kaito\\Desktop\\xydata2014.txt", "r")) != 0){
		printf("ファイルのオープンに失敗しました．\n");
		return 1;//異常終了
	}

	//行数を読み込み
	fgets(buf, KB, fp);
	L = atoi(buf);

	//配列を動的確保(1000×1000の正方配列)
	if ((data = (struct abc*)malloc(sizeof(struct abc)*L)) == NULL){
		printf("メモリの確保に失敗しました.\n");
		return 1;//異常終了
	}


	//配列に値を格納するし，表示
	for (int i = 0; i < L; i++)
	{
		fscanf_s(fp, "%lf%lf", &data[i].x, &data[i].y);
		printf("%lf	%lf\n", data[i].x, data[i].y);
	}

	//ファイルのクローズ
	fclose(fp);

	for (int i = 0; i < L; i++)
	{
		a[0][0] += pow(data[i].x, 4);			//x^4
		a[0][1] += pow(data[i].x, 3);			//x^3
		a[0][2] += pow(data[i].x, 2);			//x^2
		a[1][2] += data[i].x;					//x
		a[0][3] += pow(data[i].x, 2)*data[i].y;	//x^2*y
		a[1][3] += data[i].x * data[i].y;		//xy
		a[2][3] += data[i].y;					//y

	}

	/*データの整理*/
	a[1][0] = a[0][1];				//x^3
	a[1][1] = a[2][0] = a[0][2];	//x^2
	a[2][1] = a[1][2];				//x
	a[2][2] = L;					//n個

	/*ガウスの消去法適用*/
	zensin();//前進消去
	koutai();//後退代入

	/*	解答表示*/
	printf("３元連立1次連立方程式の係数です．\n");
	printf("a=%lf\n", a[0][M]);
	printf("b=%lf\n", a[1][M]);
	printf("c=%lf\n", a[2][M]);


	//動的確保の解放
	free(data);

	getch();
	return 0;
}
/*		前進消去	*/
void zensin(void)
{
	for (int k = 0; k <= M - 1; k++)
	{
		double p = pibot(k);
		for (int j = k + 1; j <= N - 1; j++){
			a[k][j] = a[k][j] / p;
		}
		for (int i = k + 1; i <= M - 1; i++){
			for (int j = k + 1; j <= N - 1; j++){
				a[i][j] = a[i][j] - a[i][k] * a[k][j];
			}
		}
	}
}

/*		ピボット選択	*/
double pibot(int k)
{
	int l = k;
	double p = a[k][k];
	for (int j = k + 1; j <= M - 1; j++){
		if (fabs(p) < fabs(a[j][k])){
			l = j;
			p = a[j][k];
		}
	}
	if (l != k){
		for (int j = k; j <= N - 1; j++){
			double w = a[k][j];
			a[k][j] = a[l][j];
			a[l][j] = w;
		}
	}
	return(p);
}

/*	後退代入		*/
void koutai(void)
{
	for (int k = M - 2; k >= 0; k--){
		for (int i = k + 1; i <= M - 1; i++){
			a[k][M] = a[k][M] - a[k][i] * a[i][M];
		}
	}
}