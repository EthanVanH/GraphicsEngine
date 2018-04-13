/*REAL QUICK*/
/*Implementation of an image class that stores a 3d array */
/*Being an array of colours at x y coordinates*/
/*also dda algorithm for drawing lines between points*/

#include "Image.h"
Point p0;

Image::Image(){
    for(int i = 0; i < DEFAULT_RES; i++){
        for(int j = 0; j < DEFAULT_RES; j++){
            for(int k = 0; k < 3; k++){
                img[i][j][k] = DEFAULT_BACKGROUND;
            }
        }
    }
}

void Image::swap(Point p1, Point p2){
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int Image::distSq(Point p1, Point p2){
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}

int Image::orientation(Point p, Point q, Point r){
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

int Image::compare(const void *vp1, const void *vp2){
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;
 
   // Find orientation
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
 
   return (o == 2)? -1: 1;
}

void Image::Sort(Point* points, int n){
    // Find the bottommost point
   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;
 
     // Pick the bottom-most or chose the left
     // most point in case of tie
     if ((y < ymin) || (ymin == y &&
         points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }
 
   // Place the bottom-most point at first position
   swap(points[0], points[min]);
 
   // Sort n-1 points with respect to the first point.
   // A point p1 comes before p2 in sorted ouput if p2
   // has larger polar angle (in counterclockwise
   // direction) than p1
   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);
 
   // If two or more points make same angle with p0,
   // Remove all but the one that is farthest from p0
   // Remember that, in above sorting, our criteria was
   // to keep the farthest point at the end when more than
   // one points have same angle.
   int m = 1; // Initialize size of modified array
   for (int i=1; i<n; i++)
   {
       // Keep removing i while angle of i and i+1 is same
       // with respect to p0
       while (i < n-1 && orientation(p0, points[i],
                                    points[i+1]) == 0)
          i++;
 
       points[m] = points[i];
       m++;  // Update size of modified array
   }
 
}

void Image::Clip(Point* points, int numpoints, ViewSpace *vs){ 
    if(!CLIPPING){
        return;
    }

    for(int i = 0; i < numpoints; i++){
        // float pX, pY;
        // pX = points[i].x;
        // pY = points[i].y;

        cout << "I need to re think this";
    }
}


void Image::DDA(Point* points, int numpoints){
    Point One;
    Point Two;
    float dx;
    float dy;
    float end;
    float nx;
    float ny;
    
    vector <Point> lines;
     
    Sort(points,numpoints);
    #ifdef TESTING
    cout << "DDA sorted points\n";
    
    for(int i = 0; i < numpoints; i++){
        cout << "Point X: " << points[i].x << " Y: " << points[i].y << "\n";
    }
    #endif
    for(int i = 0; i < numpoints; i++){
        One = points[i];
        
        int j = (i < numpoints - 1 ? i + 1: 0);
        Two = points[j];

        dx = Two.x - One.x;
        dy = Two.y - One.y;
        
        #ifdef TESTING
        cout << "Point One x: " << One.x << " y: " <<  One.y << " To ";
        cout << "Point Two x: " << Two.x << " y: " <<  Two.y << "\n";
        cout << "dx is " << dx << " before slope\n";
        cout << "dy is " << dy << " before slope\n";
        #endif

        if(fabs(dx) >= fabs(dy)){
            end = fabs(dx);
        }else{
            end = fabs(dy);
        }
        
        dx = dx/end;
        dy = dy/end;
        
        nx = One.x;
        ny = One.y;
       
        #ifdef TESTING           
        cout << "End is " << end << "\n";
        cout << "dx = " << dx << "\n";
        cout << "dy = " << dy << "\n";
        cout << "nx = " << nx << "\n";
        cout << "ny = " << ny << "\n";
        #endif
        for(int k = 0; k < end; k++){
            int x = round(nx);
            int y = round(ny);
            Point newP;
            newP.x = x;
            newP.y = y;

            newP.r = One.r;        
            newP.g = One.g;
            newP.b = One.b;        

            lines.push_back(newP);

            img[x][y][0] = One.r;
            img[x][y][1] = One.g;
            img[x][y][2] = One.b;
            nx += dx;
            ny += dy;
        }
    }

    if(numpoints > 2){
        Rastorize(lines);
    }
}


void Image::Rastorize(vector<Point> & lines){
    //For each point on a line
    //find the point on another line that is colinear
    //these are the start and end points
    //step along the axis they are colinear and fill that in with point colour
        //oh this step is literally the dda between two points
    if(lines.empty()){
        return;
    }
    for(int i = 0; i < lines.size(); i++){
        for(int j = 0; j < lines.size(); j++){
            if(lines[i].x == lines[j].x || lines[i].y == lines[j].y){
                //colinear x situation
                Point* points = new Point[2];
                points[0] = lines[i];
                points[1] = lines[j];
                
                //Trim extremes
                if(points[0].x > points[1].x){
                    points[0].x--;
                    points[1].x++;
                }else{
                    points[1].x--;
                    points[0].x++;
                }

                if(points[0].y > points[1].y){
                    points[0].y--;
                    points[1].y++;
                }else{
                    points[1].y--;
                    points[0].y++;
                }
                //if the trim makes these points the same dont draw lines between them
                if(points[0].x == points[1].x && points[0].y == points[1].y){
                    break;
                }
                DDA(points, 2);
            }
            
        }
    }
    
}
