/*-----------------------------------------------
�ۑ�10 �ŏ����@

4I31 �����@�J�l
2015/01/30
----------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KB 1024//�����T�C�Y
#define M 3
#define N 4

/*	�֐��v���g�^�C�v�錾	*/
void zensin(void);//�O�i����
double pibot(int);//�s�{�b�g�I��
void koutai(void);//��ޑ��

double a[M][N];

struct abc
{
	double x;
	double y;
};

int main(void) {

	//�ϐ���錾
	char buf[KB];//�s���ǂݍ���
	FILE *fp = NULL;//�t�@�C���|�C���^
	int L;//�s���i�[
	struct abc *data;//�f�[�^�i�[�\����

	printf("�ۑ�10 �ŏ����@\n");

	//�t�@�C���������Ղ�
	if ((fopen_s(&fp, "C:\\Users\\kaito\\Desktop\\xydata2014.txt", "r")) != 0){
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����D\n");
		return 1;//�ُ�I��
	}

	//�s����ǂݍ���
	fgets(buf, KB, fp);
	L = atoi(buf);

	//�z��𓮓I�m��(1000�~1000�̐����z��)
	if ((data = (struct abc*)malloc(sizeof(struct abc)*L)) == NULL){
		printf("�������̊m�ۂɎ��s���܂���.\n");
		return 1;//�ُ�I��
	}


	//�z��ɒl���i�[���邵�C�\��
	for (int i = 0; i < L; i++)
	{
		fscanf_s(fp, "%lf%lf", &data[i].x, &data[i].y);
		printf("%lf	%lf\n", data[i].x, data[i].y);
	}

	//�t�@�C���̃N���[�Y
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

	/*�f�[�^�̐���*/
	a[1][0] = a[0][1];				//x^3
	a[1][1] = a[2][0] = a[0][2];	//x^2
	a[2][1] = a[1][2];				//x
	a[2][2] = L;					//n��

	/*�K�E�X�̏����@�K�p*/
	zensin();//�O�i����
	koutai();//��ޑ��

	/*	�𓚕\��*/
	printf("�R���A��1���A���������̌W���ł��D\n");
	printf("a=%lf\n", a[0][M]);
	printf("b=%lf\n", a[1][M]);
	printf("c=%lf\n", a[2][M]);


	//���I�m�ۂ̉��
	free(data);

	getch();
	return 0;
}
/*		�O�i����	*/
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

/*		�s�{�b�g�I��	*/
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

/*	��ޑ��		*/
void koutai(void)
{
	for (int k = M - 2; k >= 0; k--){
		for (int i = k + 1; i <= M - 1; i++){
			a[k][M] = a[k][M] - a[k][i] * a[i][M];
		}
	}
}