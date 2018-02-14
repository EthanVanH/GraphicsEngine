#include "Scene.h"

ViewSpace::ViewSpace() {
    //C, the viewpoint is equal to, with r as the radial distance
    //psi as the elevation angle from the plane defined by x and y
    //theta as the angle to halfway between x and y
    float psi = 3.1415/2 - 3.1415/8; // between -pi/2 and pi/2
    float theta = 45; //Pretty sure the azimuth here should be 45 as the angle from x to y should be 90
    float r = 10; // these should be input
                    //OR RATHER COULD BE
    Vertex* k;
    float *viewpoint = new float[3];
    N = new Vertex();
    V = new Vertex();
    U = new Vertex();

    ViewDirection = -1; // llooking into the screen

    viewpoint[0] = (r * cos(psi) * cos(theta));
    viewpoint[1] = (r * cos(psi) * sin(theta));
    viewpoint[2] = (r * sin(psi));

    N->x = 0 - viewpoint[0];
    N->z = 0 - viewpoint[1];
    N->z = 0 - viewpoint[2];

    N->x = 1/N->x;
    N->y = 1/N->y;
    N->z = 1/N->z;
    //TODO
    k = new Vertex(0,0,1);// this is right. right?
    V =  new Vertex(*k - *N * (N->DotProduct(k))); //????
    V = V->normalize();
    
    U = new Vertex (N->CrossProduct(V));
    /*what a clust fuck that was*/
    nearPlane = 2 * viewpoint[2];
    farPlane = 4 * nearPlane;
    h = 1000; // IDK I JUST PICKED AT RANDOM ITS BASICALLY APERATURE RIGHT I CAN DO THAT

    float xidentity[4] = {nearPlane, 0.0, 0.0, 0};
    float yidentity[4] = {0.0, nearPlane, 0.0, 0};
    float zidentity[4] = {0.0, 0.0, nearPlane, 0};
    float widentity[4] = {0,0,1,0};


    Space->MInsertColumn(xidentity, 0);
    Space->MInsertColumn(yidentity, 1);
    Space->MInsertColumn(zidentity, 2);
    Space->MInsertColumn(widentity, 3);
    //Demonstraton purposes only
    cout << "The View transformation matrix is\n";
    Space->Print();
    //
}

ViewSpace::ViewSpace(float psi, float theta, float r) { // psi must be between -pi.2 and pi/2
    //C, the viewpoint is equal to, with r as the radial distance
    //psi as the elevation angle from the plane defined by x and y
    //theta as the angle to halfway between x and y

    if(psi > 3.1415/2 || psi < -1*(3.1415/2)){
        printf("Given psi value did not pass, setting psi to default");
        psi = 3.1415/2 - 3.1415/8;
    }

    float *viewpoint = new float[3];
    N = new Vertex();
    V = new Vertex();
    U = new Vertex();

    ViewDirection = -1; // llooking into the screen

    viewpoint[0] = (r * cos(psi) * cos(theta));
    viewpoint[1] = (r * cos(psi) * sin(theta));
    viewpoint[2] = (r * sin(psi));

    nearPlane = 2 * viewpoint[2];
    farPlane = 4 * nearPlane;
    h = 1000; // IDK I JUST PICKED AT RANDOM ITS BASICALLY APERATURE RIGHT I CAN DO THAT

    float xidentity[4] = {nearPlane, 0.0, 0.0, viewpoint[0]};
    float yidentity[4] = {0.0, nearPlane, 0.0, viewpoint[1]};
    float zidentity[4] = {0.0, 0.0, nearPlane, viewpoint[2]};
    float widentity[4] = {0,0,0,1};


    Space->MInsertColumn(xidentity, 0);
    Space->MInsertColumn(yidentity, 1);
    Space->MInsertColumn(zidentity, 2);
    Space->MInsertColumn(widentity, 3);
    //Demonstraton purposes only
    cout << "The View transformation matrix is\n";
    Space->Print();
    //
}

//takes a point in 3d space and returns true if it is contained within the view volume
bool ViewSpace::isInViewVolume(Matrix *point){
    float max;
    float min;
    float x = point->m[0][0];
    float y = point->m[0][1];
    float z = point->m[0][2];

    max = (h/nearPlane) * (z);
    if(max < 0){
        max = max*-1;
    }
    min = max * -1;
    

    //cout << min << ' ' << max << "||" << x<< ' ' << y<< ' ' << z<< ' ' << "||" << nearPlane<< ' ' << farPlane << '\n';
    if(x > max || x < min || y > max || y < min || z < nearPlane || z > farPlane){
        cout << "not in vv\n";

        return false;
    }
    return true;
}


//
//World space 
//

WorldSpace::WorldSpace() {
    float tx = 1;
    float ty = 10;
    float tz = 35;
    float xidentity[4] = {1.0, 0.0, 0.0, tx};
    float yidentity[4] = {0.0, 1.0, 0.0, ty};
    float zidentity[4] = {0.0, 0.0, 1.0, tz};
    float widentity[4] = {0,0,0,1};


    Space->MInsertColumn(xidentity, 0);
    Space->MInsertColumn(yidentity, 1);
    Space->MInsertColumn(zidentity, 2);
    Space->MInsertColumn(widentity, 3);

    //Demonstraton purposes only
    cout << "The World transformation matrix is\n";
    Space->Print();
    //

}