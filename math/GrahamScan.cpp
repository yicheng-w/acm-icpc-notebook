#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;


struct pt
{
    int x, y;

    bool operator < (pt b) const
    {
        if (y < b.y)
        {
            return true;
        }
        else if(y == b.y)
        {
            if (x < b.x)
            {
                return true;
            }

        }
        return false;
    }
};

bool onSegment(pt p, pt q, pt r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(pt a, pt b, pt c)
{
    long long val1 = (long long) (b.y - a.y) * (c.x - b.x);
    long long val2 = (long long) (b.x - a.x) * (c.y - b.y);

    if (val1 < val2)
    {
        return -1; //counterclockwise
    }
    else if (val1 > val2)
    {
        return 1; //clockwise
    }
    else
    {
        return 0; //collinear
    }
}

bool onLine(pt a, pt b, pt c) //true if b is on ac
{
    if (orientation(a, b, c) != 0)
    {
        return false;
    }
    return onSegment(a, b, c);

}

vector <pt> grahamScan(vector <pt> points) //creates clockwise convex polygon
{
    pt bottom = points[0];

    for (int i = 1; i < points.size(); i++)
    {
        if (points[i].y == bottom.y)
        {
            if (points[i].x < bottom.x)
            {
                bottom = points[i];
            }
        }
        else if(points[i].y < bottom.y)
        {
            bottom = points[i];
        }
    }

    sort(points.begin(), points.end(),
         [bottom](pt a, pt b)
         {
            if (a.x == bottom.x and a.y == bottom.y)
            {
                return true;
            }
            if (b.x == bottom.x and b.y == bottom.y)
            {
                return false;
            }
            int orient = orientation(bottom, a, b);
            if (orient == 0)
            {
                int dista = abs(a.x - bottom.x);
                int distb = abs(b.x - bottom.x);

                if (dista == distb)
                {
                    return b < a;
                }
                return dista > distb;
            }
            return orient == 1;
         });

    bool includeNext = true;


    vector <pt> vPoints = {points[0]};
    vector <pt> skipped;
    for (int i = 1; i < points.size(); i++)
    {
        if (includeNext)
        {
            vPoints.push_back(points[i]);
        }
        else
        {
            skipped.push_back(points[i]);
        }

        includeNext = true;
        if(orientation(points[0], points[i], points[i + 1]) == 0)
        {
            includeNext = false;
        }
    }

    vector <pt> hull;
    hull.push_back(vPoints[0]);
    hull.push_back(vPoints[1]);
    hull.push_back(vPoints[2]);

    for (int i = 3; i < vPoints.size(); i++)
    {
        while (orientation(hull[hull.size() - 2], hull[hull.size() - 1], vPoints[i]) == -1) // != 1 if you don't want points on hull, == -1 if include points on hull
        {
            hull.pop_back();
        }
        hull.push_back(vPoints[i]);
    }

    //Rest is only needed if you want to include points on hull


    pt first_start = hull[0];
    pt first_end = hull[1];

    pt last_start = hull[0];
    pt last_end = hull[hull.size() - 1];

    //points were sorted: furthest to closest
    vector <pt> onStart; //points on first line segment of hull
    vector <pt> onEnd; //points on last line segment of hull

    for (pt p: skipped)
    {
        if (onLine(first_start, p, first_end))
        {
            onStart.push_back(p);
        }
        else if(onLine(last_start, p, last_end))
        {
            onEnd.push_back(p);
        }
    }

    vector <pt> hullCopy(hull);

    int hSize = hullCopy.size();
    int sSize = onStart.size();
    int eSize = onEnd.size();

    hull.resize(hSize + sSize + eSize);

    hull[0] = hullCopy[0];
    for (int i = 0; i < sSize; i++)
    {
        hull[1 + i] = onStart[sSize - i - 1]; //reversed b/c points are furthest to closest
    }
    for (int i = 1; i < hSize; i++)
    {
        hull[i + sSize] = hullCopy[i];
    }
    for (int i = 0; i < eSize; i++)
    {
        hull[i + sSize + hSize] = onEnd[i];
    }


    return hull;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin>>n;
    vector <pt> points(n);

    for (int i = 0; i < n; i++)
    {
        cin>>points[i].x>>points[i].y;
    }
    vector <pt> hull = grahamScan(points);
    for (pt p: hull)
    {
        cout<<p.x<<" "<<p.y<<endl;
    }



	return 0;
}
