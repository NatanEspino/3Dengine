#include <linearAlg/linearAlg.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

vec4 multMatVec4(const mat4 *mat, const vec4 *vec){
    vec4 out;
    for (int i = 0; i < 4; i++){
        out.m[i] = 
        mat->m[i*4+0] * vec->x +
        mat->m[i*4+1] * vec->y +
        mat->m[i*4+2] * vec->z +
        mat->m[i*4+3] * vec->w;
    }
    return out;
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



void translate(mat4 *mat, float x, float y, float z){
    mat4 translation = IDENTITY_MATRIX;
    translation.m[3] = x;
    translation.m[7] = y;
    translation.m[11] = z;
    (*mat) = multMat4(&translation, mat);
}

void scale(mat4 *mat, float x, float y, float z){
    mat4 scaling = IDENTITY_MATRIX;
    scaling.m[0] = x;
    scaling.m[5] = y;
    scaling.m[10] = z;
    (*mat) = multMat4(&scaling, mat);
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

