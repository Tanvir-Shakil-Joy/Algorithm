#include<bits/stdc++.h>

using namespace std;

/*##############################----------##--Quick Hull--##----------##############################*/

#define pi pair<int, int>
set<pi> hull;

int findSide(pi p1, pi p2, pi p) {
    int val = (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

int dist(pi p, pi q) {
    return (p.second - q.second) * (p.second - q.second) + (p.first - q.first) * (p.first - q.first);
}

int lineDist(pi p1, pi p2, pi p) {
    return abs ((p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first));
}

void quickHull(pi a[], int n, pi p1, pi p2, int side) {
    int ind = -1;
    int max_dist = 0;
    for (int i=0; i<n; i++) {
        int temp = lineDist(p1, p2, a[i]);
        if (findSide(p1, p2, a[i]) == side && temp > max_dist) {
            ind = i;
            max_dist = temp;
        }
    }
    if (ind == -1) {
        hull.insert(p1);
        hull.insert(p2);
        return;
    }
    quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
    quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1));
}

void printHull(pi a[], int n) {
    if (n < 3) {
        cout << "Convex hull not possible\n";
        return;
    }
    int min_x = 0, max_x = 0;
    for (int i=1; i<n; i++) {
        if (a[i].first < a[min_x].first)
            min_x = i;
        if (a[i].first > a[max_x].first)
            max_x = i;
    }
    quickHull(a, n, a[min_x], a[max_x], 1);
    quickHull(a, n, a[min_x], a[max_x], -1);
    while (!hull.empty()) {
        cout << "(" <<( *hull.begin()).first << ", " << (*hull.begin()).second << ") ";
        hull.erase(hull.begin());
    }
}

/*##############################----------##--Graham Scan--##----------##############################*/

struct point {
    int x, y;
};

point p0;

point secondTop(stack<point> &stk) {
    point temp_point = stk.top();
    stk.pop();
    point res = stk.top();
    stk.push(temp_point);
    return res;
}

int squaredDist(point p1, point p2) {
    return ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int direction(point a, point b, point c) {
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0)
        return 0;
    else if (val < 0)
        return 2;
    return 1;
}

int comp(const void *point1, const void *point2) {
    point *p1 = (point *)point1;
    point *p2 = (point *)point2;
    int dir = direction(p0, *p1, *p2);
    if (dir == 0)
        return (squaredDist(p0, *p2) >= squaredDist(p0, *p1)) ? -1 : 1;
    return (dir == 2) ? -1 : 1;
}

vector<point> findConvexHull(point points[], int n) {
    vector<point> convex_hull_points;
    int min_y = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < min_y) || (min_y == y) && points[i].x < points[min].x) {
            min_y = points[i].y;
            min = i;
        }
    }
    swap(points[0], points[min]);
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(point), comp);
    int arr_size = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && direction(p0, points[i], points[i + 1]) == 0)
            i++;
        points[arr_size] = points[i];
        arr_size++;
    }
    if (arr_size < 3)
        return convex_hull_points;
    stack<point> stk;
    stk.push(points[0]);
    stk.push(points[1]);
    stk.push(points[2]);
    for (int i = 3; i < arr_size; i++) {
        while (direction(secondTop(stk), stk.top(), points[i]) != 2)
            stk.pop();
        stk.push(points[i]);
    }
    while (!stk.empty()) {
        convex_hull_points.push_back(stk.top());
        stk.pop();
    }
    return convex_hull_points;
}

int main() {
    int n;
    point points[5000];
    ifstream inp("convexhull.txt");
    if (inp.is_open()) {
        inp >> n;
        for (int i = 0; i < n; i++) {
            point p;
            inp >> p.x;
            inp >> p.y;
            points[i] = p;
        }
    }
    vector<point> result;
    result = findConvexHull(points, n);
    cout << endl << "Boundary points of convex hull for Graham Scan are: " << endl << endl;
    vector<point>::iterator it;
    for (it = result.begin(); it != result.end(); it++)
        cout << "(" << it->x << ", " << it->y << ") ";
    cout << endl;
    cout << endl << "Boundary points of convex hull for Quick Hull are: " << endl << endl;
    pi array[5000];
    ifstream in("convexhull.txt");
    if (in.is_open()) {
        in >> n;
        for (int i = 0; i < n; i++) {
            int a, b;
            in >> a;
            in >> b;
            array[i] = {a, b};
        }
    }
    printHull(array, n);
    cout << endl;
    return 0;
}