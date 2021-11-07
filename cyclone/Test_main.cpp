#include <iostream>
#include "particle.h"

using namespace std;

int main()
{
	cyclone::Particle p1;
	p1.setPosition(1, 2, 3);
	cout << p1.getPosition().x << endl;
	cout << p1.getPosition().y << endl;
	cout << p1.getPosition().z << endl;
	
}