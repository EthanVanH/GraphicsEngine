A shape projection program
*******************************************************************
CIS*4800 Assignment 2
Author: Ethan Van Houtven
studentNo: 0851811

*******************************************************************
1.0 Users Manual

1.1 Purpose
    This program is supposed to create a model of a 3d shape in terms of polygons and then take this model and project it on a 2d plane defined by a view matrix.

1.2 Installation
    This program is written in c++
    It is composed of the sourcefiles
        AssignmentTwo.cpp
        Cube.cpp
        Primatives.cpp
        Matrix.cpp
        Scene.cpp
    The header files
        image.h
        Primatives.h
        ShapeDefinitions.h
        Matrix.h
        Scene.h
    One makefile
        Makefile
    And this README.txt
To compile the program on a linux machine
    navigate to the directory containing the project
        cd "path/to/your/directory"
    run the make command
        >make
    Then run the 'Graphics' executable
        ./Graphics
The program will prompt you for further input in specification of what shape you desire.

1.3 Input
    There is no input to the program at this time, as only the cuve is being placed into the world coordinate system.
1.4 Output
    The program will output to a terminal a system of coordinates representing the cube as it was on modeling and then as it is after transformations.


*******************************************************************
2. Results and Product Evaluation

2.1 Results
    The results of this program are working as intended from my understanding of the requirements. It models a shape and then translates the shape using 
    a system of linear equations in the form of a matrix. The World matrix is functioning at this point as just a way to expand from a model coordinate system. The view matrix 
    can be modified to change the view volume easily. The viewport is set as required in project specification, by its spherical coordinates 
    C(r*cos(psi)cos(thera), r*cos(psi)*sin(theta), r*sin(psi))

2.2 Product Evaluation
    The program is currently stable. All variables are controlled. This means that while it impossible to currently model shapes other than a cube,
    the program works. Modeling of other shapes is planned for the demo.
    
*******************************************************************
3. Technical Discussion

#shape modeling
    Shape modeled as in last Assignment. All values are either 1 or -1 as NDC space. This makes it easy to translate the shape into workd space.
    Each face of the polygon indicates a coordinate that is static, ie, if the front face is being modeled, z is always -1. Note that z is modeled as extending into
    the screen. In the pseudocode below you will see the use of n, n represents teh number of triangles being modeled. In this program it is left at 2 per face as 
    there was no call for being able to mutate the face of the cube. These values allow us create more verticies on each face.
    for each surface of shape
    for each polygon on surface
        for each vertex on polygon
            polygon<-vertexData
                coordinate  = 2/n* i - 1
                coordinate attached to face = 1 || -1
                    if top face y is 1
                    if front face z is -1 

#creation of viewspace matrix
 The viewspace matrix is best understood as a camera placed in the world space, turned to face the origin. As such it can be imagined as a transformation matrix.
 The same transformation we would apply to me the camera to where it can watch the origin of the world space. 
 The position of the camera is decided by the sperical coordinates found in the world by the following formula, C(r*cos(psi)cos(thera), r*cos(psi)*sin(theta), r*sin(psi))
    where theta represents half the angle between axis and psi represents teh angle of elevation and r is the radial distance from the origin.
    The end result of this is a matrix in the form 1 0 0 r*cos(psi)cost(theta)
                                                   0 1 0 r*cos(psi)sin(theta)
                                                   0 0 1 r*sin(psi)

#creation of world space matrix
    The world space matrix functions as a set of translations away from the origin, which in this case we can assume the shape was modeled at.
    As the world space and object space can coincide.
    For us that means we need to move the object towards the view volume. As there is one object there is currently no need to worry about collision.
#creation of projecton matrix
    The projection matrix is essentially taking coordinates in one system and projecting them into another thus we can use the affine plane
    for this we use the z value of the near plane of the viewspace, d. However this is not an Geometric translation so the last row needs to be changed.
     So 
        d 0 0 0
        0 d 0 0
        0 0 d 0
        0 0 1 0
#projection translation
    The projection translation is a bit special, to correct to the coordinates we check if the w value is anything other than 1, if it is
    a non affine transformation took place. To correct we simply divide x, y and z by w.
    
#translations by matrix
 Translations are made simple by the presence of the 4th coordinate, the w value as it is named in this program. We can use that to make translations simply
 a matrix multiplication.
 V` = MV every time.





