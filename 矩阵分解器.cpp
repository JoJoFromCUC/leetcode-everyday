#include<iostream>
#include<iomanip>
#include<math.h>
using namespace std;


//�н�������
void rowChange(double a[][20], int d, int i, int j)//dΪ����ά����i,jҪ����������
{
	double t; int k;
	for (k = 0; k < d; k++)
	{
		t = a[i][k];
		a[i][k] = a[j][k];
		a[j][k] = t;
	}
}

//���������
void printMatrix(double a[][20], int d)
{
	int i, j;
	for (i = 0; i < d; i++)
	{
		for (j = 0; j < d; j++)
			cout << setw(10) << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}
//�������˷�
void multiply(double a[][20], double b[][20], int d,int y)
{
	int i, j;
	double c[20][20];
	for (i = 0; i < d; i++)
	{
		for (j = 0; j < d; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < d;k++)
				c[i][j] += a[i][k] * b[k][j];	
		}
	}
	for (i = 0; i <d; i++)
	{
		for (j = 0; j < d; j++)
		{
			if (y == 1)
				a[i][j] = fabs(c[i][j])>1e-12?c[i][j]:0;
			else
				b[i][j] = fabs(c[i][j])>1e-12? c[i][j] : 0;
		}
	}
}


//LU�ֽ⺯��
void LU(double A[][20], int d)
{
	int i,j,t;
	double k;
	double l[20][20] = { 0 }, u[20][20] = { 0 }, p[20][20] = { 0 },a[20][20];//��ʼ��
	for (i = 0; i < d; i++)
	{
		for (j = 0; j < d; j++)
			a[i][j] = A[i][j];
	}
	for (i = 0; i < d; i++)
		p[i][i] = 1;//P����λ��
	for (i = 0; i < d - 1; i++)
	{
		//����Ԫ������
		k = fabs(a[i][i]); int m = 0;
		for (t = i + 1; t < d; t++)
		{
			if (k < fabs(a[t][i]))
			{
				k = a[t][i];
				j = t;
				m = 1;
			}
		}
		if (m)
		{
			rowChange(a, d, i, j);
			rowChange(p, d, i, j);
		}

		//������Ԫ����
		for (j = i + 1; j < d; j++)//j��������t������
		{
			a[j][i] = a[j][i] / a[i][i];
			for (t = i + 1; t < d; t++)
				a[j][t] -= a[j][i] * a[i][t];
		}
	}
	//L�����U����Ļ�ȡ
	for (i = 0; i < d; i++)
	{
		l[i][i] = 1;
		for (j = 0; j < i; j++)
			l[i][j] = a[i][j];
		for (j = i; j < d; j++)
			u[i][j] = a[i][j];
	}

	//������
	cout << "LU�ֽ���Ϊ" << endl;
	cout << "L����Ϊ:" << endl<<endl;
	printMatrix(l, d);
	cout << "U����Ϊ��" << endl;
	printMatrix(u, d);
	cout << "P����Ϊ��" << endl;
	printMatrix(p, d);

}


//Gram-Schmidt�ֽ�
void schmidt(double a[][20], int d)//a[][]�Ǵ��ֽ����,d ��ʾά��
{
	int i, j, k;
	double q[20][20], r[20][20] = { 0 };

	//��q��ʼ��Ϊ��a��ͬ�ľ���
	for (i = 0; i < d; i++)
	{
		for (j = 0; j < d; j++)
			q[i][j] = a[i][j];
	}
	for (i = 0; i < d; i++)
	{
		for (j = 0; j < i; j++)
		{
			//����r[j]][i]
			for (k = 0; k < d; k++)
				r[j][i] += q[k][j] * a[k][i];
			//�������q�ĵ�i��
			for (k = 0; k < d; k++)
				q[k][i] -= q[k][j]*r[j][i]  ;
		}
		//����r[i][i]
		for (k = 0; k < d; k++)
			r[i][i] += q[k][i] * q[k][i];
		r[i][i] = sqrt(r[i][i]);
		//��һ��q����ĵ�i��
		for (k = 0; k < d; k++)
			q[k][i] /= r[i][i];
	}
	cout << "Gram-Schmidt�ֽ���Ϊ:" << endl;
	cout << "Q����Ϊ:" << endl<<endl;
	printMatrix(q, d);
	cout << "R����Ϊ:" << endl;
	printMatrix(r, d);
}

//householder�ֽ�
void householder(double A[][20], int d)//���ֽ����A[][]��d��ʾά��
{
	int k,l;
	//�ֽ��Q������q[][]���ֽ��R������������a[][]��
	double u[20], p[20][20], q[20][20] = {0}, a[20][20];//p[][]���м����
	double norm,s,sum;
	for (k = 0; k < d; k++)
	{
		for (l = 0; l < d; l++)
			a[k][l] = A[k][l];
	}
	//q����λ��ʼ��
	for (k = 0; k < d; k++)
		q[k][k] = 1;
	
	for (int i = 0; i < d-1; i++)
	{
		norm = 0; s = 0,sum=0;
		//����u[]����u[i]=a[][i]-||a[][i]||*e1
		for ( k = i; k < d; k++)
		{
			u[k - i] = a[k][i];
			norm += u[k-i] * u[k-i];
		}
		norm = sqrt(norm);
		u[0] -= norm;
		for (k = i; k < d; k++)
			sum += u[k]*u[k];
		//����p[][]����
		for (k = 0; k < d; k++)
		{//p����λ��ʼ��
			for (l = 0; l < d; l++)
			{
				if (k == l)
					p[k][l] = 1;
				else
					p[k][l] = 0;
			}
		}
		if (sum)
		{
			for (k = 0; k < d - i; k++)
				s += u[k] * u[k];
			for (k = i; k < d; k++)
			{
				for (l = i; l < d; l++)
				{
					if (k == l)
						p[k][l] = 1 - 2 / s*u[k - i] * u[l - i];//����p[][i]=a[][i]-2*u*ut/(ut*u)
					else
						p[k][l] = 0 - 2 / s*u[k - i] * u[l - i];
				}
			}
		}	//q=p1*p2*p3,r=p3*p2*p1*a
		multiply(q, p, d, 1);//q=q*p;q=p1*p2*p3
		multiply(p, a, d, 0);//a=p*a
	}
	//������
	cout << "Householder�ֽ���Ϊ��" << endl;
	cout << "Q����Ϊ��" << endl;
	printMatrix(q, d);
	cout << "R����Ϊ��" << endl;
	printMatrix(a, d);
}

//Givens �ֽ�
void givens(double A[][20], int d)
{
	//a[][]�Ǵ��ֽ����(Q=T12*T13*T23;R=T23*T13*T12*A)
	double t[20][20] = { 0 }, q[20][20] = { 0 },a[20][20];
	int i, j;
	for (i = 0; i < d; i++)
	{
		for (j = 0; j < d; j++)
			a[i][j] = A[i][j];
	}
	for (i = 0; i < d; i++)
	{//q����λ��ʼ��
		q[i][i] = 1;
	}
	for (int i = 0; i < d; i++)
	{
		for (int j = i+1; j < d; j++)
		{
			//t����λ��ʼ��
			for (int k = 0; k < d; k++)
			{
				for (int l = 0; l < d; l++)
				{
					if (k == l)
						t[k][l] = 1;
					else
						t[k][l] = 0;
				}
			}
			//����t����
			t[i][i] = a[i][i] / sqrt(a[i][i] * a[i][i] + a[j][i] * a[j][i]);
			t[i][j] = a[j][i] / sqrt(a[i][i] * a[i][i] + a[j][i] * a[j][i]);
			t[j][j] = t[i][i];
			t[j][i] = -1 * t[i][j];

			multiply(q, t, d, 1);//q=q*t
			multiply(t, a, d, 0);//a=t*a
		}
	}
	//������ս��
	cout << "Givens�ֽ���Ϊ��:" << endl;
	cout << "Q����Ϊ:" << endl;
	printMatrix(q, d);
	cout << "R����Ϊ:" << endl;
	printMatrix(a, d);
}
int main()
{
	double a[20][20];
	int i,j,d;
	cout << "���������ά��:" << endl;
	cin >> d;
	cout << "���������Ԫ��:" << endl;
	for (i = 0; i < d; i++)
	for (j = 0; j < d; j++)
	cin >> a[i][j];
	cout << "�������Ϊ:" << endl;
	printMatrix(a, d);
	do
	{
		cout << "��ѡ��ֽⷽ��:" << endl << "1:LU�ֽ�" << endl << "2:Gram-schmidt�ֽ�" << endl << "3:Householder�ֽ�" << endl << "4:Givens�ֽ�" << endl;
		cin >> i;
		switch (i)
		{
		case 1:LU(a, d); break;
		case 2:schmidt(a, d); break;
		case 3:householder(a, d); break;
		case 4:givens(a, d); break;
		default:cout << "�ǺϷ����룡" << endl;
		}
		cout << "ѡ����������?       1:��  0:��" << endl;
		cin >> j;
	} while (j);
}
