
#include "Primatives.h"

#define RESOLUTION_DEFAULT 2

void CreateCylinder(int mesh);
void CreateCone(int mesh);
void CreateSphere(int mesh);
void CreateTube(int mesh);
void CreateTorus(int mesh);

enum ShapeOptions {CUBE, CYLINDER, CONE, SPHERE, TUBE, TORUS };
enum MeshOptions {POLYGON, TRIANGLE};

class Shape {
    public:
        virtual ~Shape() {};
        virtual int GetNumVertices() {return 0;};
        virtual int GetNumVertPFace(){return 0;}
        virtual int GetResolution() {return 0;};
        virtual int GetMeshType() {return 0;};
        virtual int GetNumFaces() {return 0;}
        virtual Polygon* GetFaces() {return 0;};
        virtual void Print() {};
};

class Cube: public Shape {
    int faces = 6;
    
    Polygon* cubeFaces; //top, bot, left, right,back, front

    int meshType;
    int resolution; // n 
    int size;
    

    public:
        Cube(int meshType, int resolution);
        void PolygonCube(); 
        void TriangleCube();
        Polygon PolygonFace(int selector);
        //overrides
        int GetNumFaces();
        int GetNumVertPFace();
        int GetNumVertices();
        int GetResolution() ;
        int GetMeshType() ;
        Polygon* GetFaces();
        void Print();
};

/*TEST DATA PLEASE IGNORE*/
static const float cube_vertex_buffer_data[] = {
    // a cube has six sides and each face can be divided into triangles
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f,  // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,  // 3
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f, // 3 end
    1.0f, 1.0f,-1.0f, //4
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f, //4end
    -1.0f,-1.0f,-1.0f, //5
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f, //5end
    1.0f,-1.0f, 1.0f, //6
    -1.0f,-1.0f, 1.0f, 
    -1.0f,-1.0f,-1.0f, //6end
    -1.0f, 1.0f, 1.0f, //7
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f, //7end
    1.0f, 1.0f, 1.0f, // 8 
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f, // 8 end
    1.0f,-1.0f,-1.0f, // 9
    1.0f, 1.0f, 1.0f, 
    1.0f,-1.0f, 1.0f, // 9 end
    1.0f, 1.0f, 1.0f, // 10
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, //10 end
    1.0f, 1.0f, 1.0f, // 11
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f, // 11 end
    1.0f, 1.0f, 1.0f, // 12
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f // 12 end
};

static const float cube_color_buffer_data[] = {
    // One colour for each vertex
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};