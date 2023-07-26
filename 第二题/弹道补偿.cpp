#include<iostream>
#include<cmath>

using namespace std;

const double PI = 3.141592689795358979323846;
const double g = 9.8;          //重力加速度
const double m = 0.0031;       //弹丸质量
const double v0 = 30.0;        //初始速度
const double theta0 = 20.0;    //初始角度(度制数)
const double dt = 0.001;       //时间间隔
const double Cd = 0.47;        //阻力系统
const double rho = 1.169;      //空气密度
const double A = 0.00226;      //截面积

//dt时间内的水平位移：
double xtFunction(double v0, double t)
{
    return v0 / (Cd * A * rho * v0 * t + 1) * dt;
}

//实际落点：
double ballisticCompensation(double tempPoint_x, double tempPoint_y, double rad)
{
    //水平初速度：
    double v0_x = v0 * cos(rad);
    //求解飞行时间：
    double flightTime = 0;
    double x = 0;
    while (x < tempPoint_x)
    {
        x += xtFunction(v0, flightTime);
        flightTime += dt;
    }
    //垂直速度：
    double v0_y = v0 * sin(rad);
    //实际落点垂直高度：
    double realPoint_y = v0_y * flightTime - (1.0 / 2.0 * g * flightTime * flightTime);
    return realPoint_y;
}

int main()
{
    double targetDistance;
    cout << "请输入目标距离：";
    cin >> targetDistance;

    double rad = theta0 * PI / 180.0;  //角度转化为弧度
    double targetPoint_x = targetDistance * cos(rad);  //目标水平距离
    double targetPoint_y = targetDistance * sin(rad);  // 目标垂直距离
    double theta = theta0;  //每次偏转角度
    double tempPoint_y = targetPoint_y;  //临时垂直距离
    double realPoint_y;  //实际落点垂直距离：
    double deltaH = 0;  //误差

    for (int i = 1; i <= 20; i++)
    {
        //计算落点和误差：
        realPoint_y = ballisticCompensation(targetPoint_x, tempPoint_y, rad);
        deltaH = targetPoint_y - realPoint_y;

        cout << "第" << i << "次迭代：仰角：" << theta << "，临时目标点y值："
             << tempPoint_y << "，高度误差：" << deltaH << endl;

        //调整临时目标高度和角度：
        tempPoint_y = tempPoint_y + deltaH;
        rad = atan(tempPoint_y / targetPoint_x);
        theta = rad * 180.0 / PI;
    }
    return 0;
}