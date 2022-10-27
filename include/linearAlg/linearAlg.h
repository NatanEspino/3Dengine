static const double PI = 3.14159265359;
typedef struct mat4 {
    float m[16];
} mat4;

typedef union vec4 {
    float m[4];
    struct {
        float x,y,z,w;
    };
}vec4;

static const mat4 IDENTITY_MATRIX = {
    1.0f,0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,0.0f,
    0.0f,0.0f,1.0f,0.0f,
    0.0f,0.0f,0.0f,1.0f
};

static const mat4 ZERO_MATRIX = {
    0.0f,0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,0.0f
};

vec4 multMatVec4(const mat4 *m, const vec4 *v);
mat4 multMat4(const mat4 *a, const mat4 *b);
mat4 ortho(float left, float right, float bottom, float top, float near, float far);
mat4 perspective(float fovy, float aspectRatio, float near, float far);
void rotateMat4X(mat4 *mat, float angle);
void rotateMat4Y(mat4 *mat, float angle);
void rotateMat4Z(mat4 *mat, float angle);
void translate(mat4 *mat, float x, float y, float z);
void scale(mat4 *mat, float x, float y, float z);
void printMat4(mat4 *mat);