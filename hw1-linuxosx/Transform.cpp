// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE
	mat3 kx( 0.0f  , axis.z ,-axis.y,
            -axis.z, 0.0f   , axis.x,
             axis.y,-axis.x, 0.0f);

	float rads= glm::radians(degrees);
	return mat3()*cos(rads)
			+kx*sin(rads)
			+(1-cos(rads))*glm::outerProduct(axis,axis);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	eye = rotate(degrees,glm::normalize(up))*eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 axis = glm::normalize(glm::cross(up,eye));
	//vec3 axis=vec3(1,0,0);
	eye = rotate(-degrees,axis)*eye;
	up = rotate(-degrees,axis)*up;

}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
	// You will change this return call
	mat4 mine = mat4(
			u.x, u.y, u.z,-glm::dot(u, eye),
			v.x, v.y, v.z,-glm::dot(v, eye),
			w.x, w.y, w.z,-glm::dot(w, eye),
			0, 0, 0, 1);
	return glm::transpose(mine);
	//return glm::lookAt(eye,vec3(0,0,0),up);
}

Transform::Transform() {

}

Transform::~Transform() {

}
