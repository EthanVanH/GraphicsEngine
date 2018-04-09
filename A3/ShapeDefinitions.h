
#include "Primatives.h"

#define RESOLUTION_DEFAULT 5 

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

class Cylinder: public Shape{
    int surfaces = 3;
    int faces; // count of polygons
    int h = 10; // height of cylinder default
    int r = 4; // radius of cylinder default
    Polygon* cylinderFaces; //top, bot, the wrapping each divided by resolution

    int meshType;
    int resolution; // n 
    int size;
    
    private:
        void GenerateVerts();
    public:
        Cylinder(int meshType, int resolution);
        void PolygonCylinder(); 
        void TriangleCylinder();
        Polygon PolygonFace(int selector);
        //overrides
        int GetNumFaces();
        int GetNumVertPFace(Polygon *face);
        int GetNumVertPFace();
        int GetNumVertices();
        int GetResolution() ;
        int GetMeshType() ;
        Polygon* GetFaces();
        void Print();
};
