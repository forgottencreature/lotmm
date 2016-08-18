#include <iostream>
#include "Camera.hpp"

void Camera::move(sf::Vector2<float> target){
	_pos = _pos + target;
}

void Camera::setTarget(sf::Vector2<float> target){
	_target = target;
}

sf::Vector2f Camera::update(){
	sf::Vector2f resultant,resp,resd,resi;
	float m=.08,n=.001,o=.008;

	_dist = _target - _pos;
	_deriv = _dist - _lastdist;
	resp = _dist*m;
	resd = _deriv*o;
	resi = _integ*n;
	//resultant = (_dist*m) + (_integ*n) + (_deriv*o);
	resultant = resp + resd + resi;

	//system("cls");
	_integ = _integ + _dist;
	_lastdist = _dist;
	move(resultant);
	//std::cout << "Pos:" << _pos.x << ","<< _pos.y << "\tTarget:" << _target.x << ","<< _target.y << "\tDist:" << _dist.x << ","<< _dist.y << "\tDeriv:" << _deriv.x << ","<< _deriv.y << "\tInteg:" << _integ.x << ","<< _integ.y << "\n\n";
	//std::cout << "Resp:" << resp.x << ","<< resp.y << "\tResd:" << resd.x << ","<< resd.y << "\tResi:" << resi.x << ","<< resi.y << "\tResult:" << resultant.x << ","<< resultant.y << "\n\n" << "--------------------------------------------------------------------------------------\n";
	return resultant;

}
