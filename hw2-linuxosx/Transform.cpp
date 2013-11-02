// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
        // YOUR CODE FOR HW1 HERE
        mat3 kx( 0.0f , axis.z ,-axis.y,
            -axis.z, 0.0f , axis.x,
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

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
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
    mine = glm::transpose(mine);
    mat4 glat = glm::lookAt(eye,center,up);
    return mine;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	float f = 1.0/tan(glm::radians(fovy/2));
	float th = f/aspect;
	float A = (zNear+zFar)/(zNear - zFar);
	float B = 2*zNear*zFar/(zNear - zFar);
	mat4 ret = mat4(
					th,0 ,0 ,0,
					0 ,f ,0 ,0,
					0 ,0 ,A ,B,
					0 ,0 ,-1,0);
	ret = glm::transpose(ret);
	mat4 glp =  glm::perspective(fovy,aspect,zNear,zFar);
	mat4 diff = ret-glp;
	return glp;



}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret( sx,0 ,0, 0,
              0 ,sy,0, 0,
              0 ,0 ,sz,0,
              0 ,0 ,0 ,1);
    ret = glm::transpose(ret);
    mat4 gls = glm::scale(mat4(1.0f),vec3(sx,sy,sz));
    mat4 diff = ret-gls;
    return gls;

}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret( 1,0,0, tx,
              0,1,0, ty,
              0,0,1, tz,
              0,0,0, 1);
    ret = glm::transpose(ret);
    mat4 glt = glm::translate(mat4(1.0f),vec3(tx,ty,tz));
    mat4 diff = ret-glt;
    return glt;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
