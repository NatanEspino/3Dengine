static const double PI = 3.14159265359;

typedef struct mat4 {
    float m[16];
} mat4;

typedef union vec3 {
    float m[3];
    struct {
        float x,y,z;
    };
}vec3;

static const vec3 iHat = {{1.0f, 0.0f, 0.0f}}, jHat = {{0.0f, 1.0f, 0.0f}}, kHat = {{0.0f, 0.0f, 1.0f}};

static const mat4 IDENTITY_MATRIX = {{
    1.0f,0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,0.0f,
    0.0f,0.0f,1.0f,0.0f,
    0.0f,0.0f,0.0f,1.0f
}};

static const mat4 ZERO_MATRIX = {{
    0.0f,0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,0.0f
}};


vec3 normalize(vec3 v);
vec3 addVec(vec3 u, vec3 v);
vec3 scaleVec(vec3 v, float scalar);
vec3 crossProduct(vec3 u, vec3 v);
mat4 multMat4(const mat4 *a, const mat4 *b);
mat4 ortho(float left, float right, float bottom, float top, float near, float far);
mat4 perspective(float fovy, float aspectRatio, float near, float far);
mat4 lookAt(vec3 pos, vec3 target, vec3 up);
void rotateMat4X(mat4 *mat, float angle);
void rotateMat4Y(mat4 *mat, float angle);
void rotateMat4Z(mat4 *mat, float angle);
void rotateMat4Axis(mat4 *mat, vec3 axis, float angle);
void translate(mat4 *mat, vec3 displacement);
void scale(mat4 *mat, float x, float y, float z);
void printVec3(vec3 v);
void printMat4(mat4 *mat);