#include<iostream>
using namespace std;

struct Point 
{
   float x, y;
};

struct seg
{
   Point p1, p2;
};

bool onSeg(seg S1, Point p) 
{        
   if(p.x <= max(S1.p1.x, S1.p2.x) && p.x <= min(S1.p1.x, S1.p2.x) &&
      (p.y <= max(S1.p1.y, S1.p2.y) && p.y <= min(S1.p1.y, S1.p2.y)))

   return true;
   return false;
}

int Orientation(Point a, Point b, Point c) 
{
   int val = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);
   if (val == 0)
      return 0;           
   else if(val < 0)
      return 2;          
      return 1;          
}

bool isIntersect(seg S1, seg S2) 
{
   
   int O1 = Orientation(S1.p1, S1.p2, S2.p1);
   int O2 = Orientation(S1.p1, S1.p2, S2.p2);
   int O3 = Orientation(S2.p1, S2.p2, S1.p1);
   int O4 = Orientation(S2.p1, S2.p2, S1.p2);

   if(O1 != O2 && O3 != O4)
      return true;           
   if(O1==0 && onSeg(S1, S2.p1))       
      return true;
   if(O2==0 && onSeg(S1, S2.p2))        
      return true;
   if(O3==0 && onSeg(S2, S1.p1))      
      return true;
   if(O4==0 && onSeg(S2, S1.p2)) 
      return true;
   return false;
}

bool Inside(Point poly[], int n, Point p)
{
   if(n < 3)
      return false;                  
   seg exline = {p, {9999, p.y}};   
   int count = 0;
   int i = 0;
   do {
      seg side = {poly[i], poly[(i+1)%n]};    
      if(isIntersect(side, exline)) {          
         if(Orientation(side.p1, p, side.p2) == 0)
            return onSeg(side, p);
         count++;
      }
      i = (i+1)%n;
   } while(i != 0);
      return count&1;            
}

int main() 
{
   Point polygon[] = {{1, 0}, {8, 3}, {8,8}, {1, 5}};
   Point p = {3,5};
   int n = 4;

   if(Inside(polygon, n, p))
      cout << "True.";
   else
      cout << "False.";
}
