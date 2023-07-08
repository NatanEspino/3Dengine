#include <linearAlg/linearAlg.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

vec3 normalize(vec3 v){
	float norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	vec3 unit = {{ v.x / norm, v.y / norm, v.z / norm }};
	return unit;
}

vec3 addVec(vec3 u, vec3 v){
	vec3 out = {{ u.x + v.x, u.y + v.y, u.z + v.z }};
	return out;
}

vec3 scaleVec(vec3 v, float scalar){
	vec3 out = {{v.x * scalar, v.y * scalar, v.z * scalar}};
	return out;
}
vec3 crossProduct(vec3 u, vec3 v){
	vec3 norm = {{u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x}};
	return norm;
}

mat4 multMat4(const mat4 *a, const mat4 *b){
    mat4 out;
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++){
            out.m[4*i + j] = 
                a->m[4*i + 0] * b->m[j+0] +
                a->m[4*i + 1] * b->m[j+4] +
                a->m[4*i + 2] * b->m[j+8] +
                a->m[4*i + 3] * b->m[j+12];
        }
    return out;
    
}

mat4 ortho(float left, float right, float bottom, float top, float near, float far){
    mat4 out = IDENTITY_MATRIX;
    out.m[0] = 2/(right-left);
    out.m[5] = 2/(top-bottom);
    out.m[10] = -2/(far-near);
    out.m[3] = -(right + left)/(right-left);
    out.m[7] = -(top + bottom)/(top - bottom);
    out.m[11] = -(far + near)/(far-near);
    return out;
}

mat4 perspective(float fovy, float aspectRatio, float near, float far){
    mat4 out = ZERO_MATRIX;
    float tanHalfFovy = tanf(fovy / 2);
    out.m[0] = 1/(aspectRatio * tanHalfFovy);
    out.m[5] = 1/tanHalfFovy;
    out.m[10] = -(far + near)/(far-near);
    out.m[11] = -(2*far*near)/(far-near);
    out.m[14] = -1;
    return out;
}

mat4 lookAt(vec3 pos, vec3 target, vec3 up){
	vec3 direction = normalize(addVec(pos, scaleVec(target, -1.0f)));
	vec3 right = crossProduct(up, direction);
	mat4 out = {{
		right.x, right.y, right.z, -(right.x * pos.x + right.y * pos.y + right.z * pos.z),
		up.x, up.y, up.z, -(up.x * pos.x + up.y * pos.y + up.z * pos.z),
		direction.x, direction.y, direction.z, -(direction.x * pos.x + direction.y * pos.y + direction.z * pos.z),
		0.0f, 0.0f, 0.0f, 1.0f
	}};
	return out;
}




void rotateMat4X(mat4 *mat, float angle){
    mat4 rotate = IDENTITY_MATRIX;
    float cosine = cosf(angle);
    float sine = sinf(angle);
    rotate.m[5] = cosine;
    rotate.m[6] = -sine;
    rotate.m[9] = sine;
    rotate.m[10] = cosine;
    (*mat) = multMat4(&rotate, mat);
}

void rotateMat4Y(mat4 *mat, float angle){
    mat4 rotate = IDENTITY_MATRIX;
    float cosine = cosf(angle);
    float sine = sinf(angle);
    rotate.m[0] = cosine;
    rotate.m[2] = sine;
    rotate.m[8] = -sine;
    rotate.m[10] = cosine;
    (*mat) = multMat4(&rotate, mat);
}

void rotateMat4Z(mat4 *mat, float angle){
    mat4 rotate = IDENTITY_MATRIX;
    float cosine = cosf(angle);
    float sine = sinf(angle);
    rotate.m[0] = cosine;
    rotate.m[1] = -sine;
    rotate.m[4] = sine;
    rotate.m[5] = cosine;
    (*mat) = multMat4(&rotate, mat);
}

void rotateMat4Axis(mat4 *mat, vec3 axis, float angle){
	vec3 u = normalize(axis);
	float cosine = cosf(angle);
	float sine = sinf(angle);
	float diff = 1.0f - cosine;
	mat4 rotate = {{
		cosine + u.x * u.x * diff, u.x * u.y * diff - u.z * sine, u.x * u.z * diff + u.y * sine, 0.0f,
		u.y * u.x * diff + u.z * sine, cosine + u.y * u.y * diff, u.y * u.z * diff - u.x * sine, 0.0f,
		u.z * u.x * diff - u.y * sine, u.z * u.y * diff + u.x * sine, cosine + u.z * u.z * diff, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	}};
	(*mat) = multMat4(&rotate, mat);
	
}

void translate(mat4 *mat, vec3 displacement){
    mat4 translation = IDENTITY_MATRIX;
    translation.m[3] = displacement.x;
    translation.m[7] = displacement.y;
    translation.m[11] = displacement.z;
    (*mat) = multMat4(&translation, mat);
}

void scale(mat4 *mat, float x, float y, float z){
    mat4 scaling = IDENTITY_MATRIX;
    scaling.m[0] = x;
    scaling.m[5] = y;
    scaling.m[10] = z;
    (*mat) = multMat4(&scaling, mat);
}

void printVec3(vec3 v) {
	printf("(%f, %f, %f)\n", v.x, v.y, v.z);
}

void printMat4(mat4 *mat){
    for (int i=0; i< 16; i++){
        printf("%f ", mat->m[i]);
        if ((i + 1) % 4 == 0){
            printf("\n");
        }
    }
    printf("\n");
}

