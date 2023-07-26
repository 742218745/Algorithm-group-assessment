#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// �������˲�����
class KalmanFilter {
private:
    double x;  // ״̬����
    double P;  // �������Э����
    double Q;  // ϵͳ����Э����
    double R;  // ��������Э����

public:
    KalmanFilter(double initial_x, double initial_P, double process_noise, double measurement_noise) {
        x = initial_x;
        P = initial_P;
        Q = process_noise;
        R = measurement_noise;
    }

    double update(double measurement) {
        // Ԥ�ⲽ��
        double x_pred = x;
        double P_pred = P + Q;

        // ���²���
        double K = P_pred / (P_pred + R);
        x = x_pred + K * (measurement - x_pred);
        P = (1 - K) * P_pred;

        return x;
    }
};

int main()
{
    vector<double> Y = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, NAN, NAN, NAN, 21, 22, 23 };

    // ��ʼ���������˲���
    double initial_x = Y[0];
    double initial_P = 1.0;
    double process_noise = 0.5;
    double measurement_noise = 0.1;
    KalmanFilter kf(initial_x, initial_P, process_noise, measurement_noise);

    // ʹ�ÿ������˲����岹ȱʧֵ
    double measurement;
    double interpolated_value;
    for (int i = 0; i < Y.size(); i++)
    {
        measurement = Y[i];
        interpolated_value = kf.update(measurement);

        // �������ȱʧֵ���򽫹���ֵ��Ϊ��һ������ֵ
        if (i < Y.size() - 1)
            if (isnan(Y[i + 1]) && i < Y.size() - 1)
            {
                Y[i + 1] = interpolated_value;
            }
    }

    // ����岹�������
    cout << "�岹������У�" << endl;
    for (int i = 0; i < Y.size(); i++) {
        cout << Y[i] << " ";
    }
    cout << endl;

    return 0;
}