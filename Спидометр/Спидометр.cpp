#include <iostream>
#include <cstdio> 

int main(){
	double speed = 0.0; // Начальная скорость
	const double max_speed = 150.0; // Максимальная скорость
	const double min_speed = 0.01;	//Минимальная скорость для остановки
	char speed_str[50]; //Буфер для строки спидометра

	do {
		double delta;
		std::cout << "Speed delta: ";
		std::cin >> delta;

		speed += delta;
		if (speed > max_speed) {
			speed = max_speed;
		}else if (speed < 0) {
			speed = 0;
		}

		sprintf_s(speed_str,sizeof(speed_str), "Speed: %.1f", speed);
		
		std::cout << speed_str << std::endl;
		
	} while (speed > min_speed);

	std::cout << "The car has stopped. " << std::endl;

	return 0;
}