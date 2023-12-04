#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "dxl.hpp"
using namespace std;
bool ctrl_c_pressed = false;
void ctrlc(int) { ctrl_c_pressed = true; }
int main(void)
{
	Dxl mx;
	struct timeval start, end1;
	double time1;
	signal(SIGINT, ctrlc); //�ñ׳� �ڵ鷯 ����
	if (!mx.open()) { cout << "dynamixel open error" << endl; return -1; }
	while (true)
	{
		gettimeofday(&start, NULL);
		mx.setVelocity(50, -50); //���� �ӵ���� ����
		usleep(3000 * 1000); //3�� sleep
		mx.setVelocity(-50, -50); //��ȸ�� �ӵ���� ����
		usleep(3000 * 1000); //3�� sleep
		mx.setVelocity(-50, 50); //���� �ӵ���� ����
		usleep(3000 * 1000); //3�� sleep
		mx.setVelocity(50, 50); //��ȸ�� �ӵ���� ����
		usleep(3000 * 1000); //3�� sleep
		mx.setVelocity(0, 0); //���� �ӵ���� ����
		usleep(3000 * 1000); //3�� sleep
		if (ctrl_c_pressed) break; //Ctrl+c ������ Ż��
		gettimeofday(&end1, NULL);
		time1 = end1.tv_sec - start.tv_sec
			+ (end1.tv_usec - start.tv_usec) / 1000000.0;
		cout << "time:" << time1 << endl; //����ð� ���
	}
	mx.close(); //��ġ�ݱ�
	return 0;
}