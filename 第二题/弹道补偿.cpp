#include<iostream>
#include<cmath>

using namespace std;

const double PI = 3.141592689795358979323846;
const double g = 9.8;                    //�������ٶ�
const double m = 0.0031;             //��������
const double v0 = 30.0;                //��ʼ�ٶ�
const double theta0 = 20.0;         //��ʼ�Ƕ�(������)
const double dt = 0.001;              //ʱ����
const double Cd = 0.47;               //����ϵͳ
const double rho = 1.169;            //�����ܶ�
const double A = 0.00226;           //�����

//dtʱ���ڵ�ˮƽλ�ƣ�
double xtFunction(double v0, double t)
{
	return v0 / (Cd * A * rho * v0 * t + 1) * dt;
}

//ʵ����㣺
double ballisticCompensation(double tempPoint_x, double tempPoint_y, double rad)
{
	//ˮƽ���ٶȣ�
	double v0_x = v0 * cos(rad);
	//����ʱ�䣺
	double flightTime = 0;
	double x = 0;
    while (x < tempPoint_x)
	{
		x += xtFunction(v0, flightTime);
		flightTime += dt;
	}
    //��ֱ�ٶȣ�
	double v0_y = v0 * sin(rad);
	//ʵ����㴹ֱ�߶ȣ�
	double realPoint_y = v0_y * flightTime - (1.0 / 2.0 * g * flightTime * flightTime);
    return realPoint_y;
}

int main()
{
	double targetDistance;
	cout << "������Ŀ����룺";
	cin >> targetDistance;

	//�Ƕ�ת��Ϊ���ȣ�
	double rad = theta0 * PI / 180.0;
	//Ŀ��ˮƽ���룺
	double targetPoint_x = targetDistance * cos(rad);
	// Ŀ�괹ֱ���룺
	double targetPoint_y = targetDistance * sin(rad);
	
	//ÿ��ƫת�Ƕȣ�
	double theta = theta0;
	//��ʱ��ֱ���룺
	double tempPoint_y = targetPoint_y;
	//ʵ����㴹ֱ���룺
	double realPoint_y;
	//��
	double deltaH = 0;

	for (int i = 1; i <= 50; i++)
	{
		//ʵ�����߶ȣ�
		realPoint_y = ballisticCompensation(targetPoint_x, tempPoint_y, rad);
		//����������
		deltaH = targetPoint_y - realPoint_y;
		cout << "��" << i << "�ε��������ǣ�" << theta << "����ʱĿ���yֵ��"
			<< tempPoint_y << "���߶���" << deltaH << endl;
		//������ʱĿ��߶ȣ�
		tempPoint_y = tempPoint_y + deltaH;
		//�����Ƕȣ�
		rad = atan(tempPoint_y / targetPoint_x);
		theta = rad * 180.0 / PI;
	}
	return 0;
}