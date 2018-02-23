#include "Scene.h"
#include "Image.h"

void ViewSpace::SetupViewSpace(float psi, float theta, float r){
    Vertex* k;
    float *viewpoint = new float[3];
    N = new Vertex();
    V = new Vertex();
    U = new Vertex();

    ViewDirection = -1; // looking into the screen

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
    V =  new Vertex(*k - *N * (N->DotProduct(k))); 
    V = V->normalize();
    
    U = new Vertex (N->CrossProduct(V));
    
    nearPlane =  *N * 1.5f *ViewDirection;
    farPlane = *N * 20.0f *ViewDirection;
    d = nearPlane.z;
    f = farPlane.z;
    //h causes segfault if it is too low? wtf
    h = DEFAULT_RES/2; // chosen for the near plane to be the final image. 
    
    float xidentity[4] = {d, 0.0, 0.0, 0};
    float yidentity[4] = {0.0, d, 0.0, 0};
    float zidentity[4] = {0.0, 0.0, d, 0};
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

ViewSpace::ViewSpace() {
    //C, the viewpoint is equal to, with r as the radial distance
    //psi as the elevation angle from the plane defined by x and y
    //theta as the angle to halfway between x and y
    float psi = 3.1415/2 - 3.1415/8; // between -pi/2 and pi/2
    float theta = 45; //Pretty sure the azimuth here should be 45 as the angle from x to y should be 90
    float r = 10; // these should be input
                    //OR RATHER COULD BE
    SetupViewSpace(psi, theta, r);
    
}

ViewSpace::ViewSpace(float psi, float theta, float r) { // psi must be between -pi.2 and pi/2
    //C, the viewpoint is equal to, with r as the radial distance
    //psi as the elevation angle from the plane defined by x and y
    //theta as the angle to halfway between x and y

    if(psi > 3.1415/2 || psi < -1*(3.1415/2)){
        printf("Given psi value did not pass, setting psi to default");
        psi = 3.1415/2 - 3.1415/8;
    }

    SetupViewSpace(psi, theta, r);
}



//takes a point in 3d space and returns true if it is contained within the view volume
bool ViewSpace::isInViewVolume(Matrix *point){
    float max;
    float min;
    float x = point->m[0][0];
    float y = point->m[0][1];
    float z = point->m[0][2];

    max = (h/d) * (z);
    if(max < 0){
        max = max * -1;
    }
    min = max * -1;
    

    // cout << min << ' ' << max << "\n"; 
    // cout << x << ' ' << y<< ' ' << z<< ' ' << "\n";
    // cout << d << ' ' << f << '\n';
    
    // if(x > max || x < min){
    //     cout << "x  is fucked "<< x <<"\n";
    // }

    // if(y > max || y < min){
    //     cout << "y  is fucked "<< x <<"\n";;
    // }


    // if(z > f || z > d){
    //     cout << "d is " << d<<'\n';
    //     cout << "f is " << f <<'\n';
    //     cout << z << "z  is fucked \n";

    // }

    if(d < 0.0f && f < 0.0f){
        if(x > max || x < min || y > max || y < min || z > d || z < f){
            cout << "not in vv A\n";

            return false;
        }
    }
    else{
        if(x > max || x < min || y > max || y < min || z < d || z > f){
            cout << "not in vv B\n";

            return false;
        }
    }
    return true;
}


//
//World space 
//

WorldSpace::WorldSpace() {
    float tx = 75;
    float ty = 40;
    float tz = -15;
    
    float xidentity[4] = {100.0, 0.0, 0.0, tx};
    float yidentity[4] = {0.0, 100.0, 0.0, ty};
    float zidentity[4] = {0.0, 0.0, 100.0, tz};
    float widentity[4] = {0,0,0,1};

    Space->MInsertColumn(xidentity, 0);
    Space->MInsertColumn(yidentity, 1);
    Space->MInsertColumn(zidentity, 2);
    Space->MInsertColumn(widentity, 3);

    //Demonstraton purposes only
    cout << "The World transformation matrix is\n";
    Space->Print();

}

WorldSpace::WorldSpace(float tx, float ty, float tz) {
    float xidentity[4] = {100.0, 0.0, 0.0, tx};
    float yidentity[4] = {0.0, 100.0, 0.0, ty};
    float zidentity[4] = {0.0, 0.0, 100.0, tz};
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