#pragma once

//--------- Intersection ----------------------------------

// ���� ab�� �����ϴ� ������ ���� cd�� �����ϴ� ������ �����ϴ� ���� Ȯ���ϰ�,
// �����ϸ� �� ������ ���Ѵ�.
template <typename T>
bool lineIntersection(Vec2D<T> a, Vec2D<T> b, Vec2D<T> c, Vec2D<T> d, Vec2D<double>& out) {
    T det = (b - a).cross(d - c);
    if (isZero(det))
        return false;
    double det2 = (c - a).cross(d - c) / (double)det;
    out.x = a.x + (b.x - a.x) * det2;
    out.y = a.y + (b.y - a.y) * det2;
    return true;
}

template <typename T>
static bool parallelSegments(Vec2D<T> a, Vec2D<T> b, Vec2D<T> c, Vec2D<T> d, Vec2D<double>& out) {
    if (b < a)
        swap(a, b);
    if (d < c)
        swap(c, d);

    if (!(b - a).isCollinear(c - a) || (b < c) || (d < a))
        return false;

    if (a < c) {
        out.x = c.x;
        out.y = c.y;
    } else {
        out.x = a.x;
        out.y = a.y;
    }

    return true;
}

template <typename T>
static bool isBoundingRectangle(Vec2D<T> p, Vec2D<T> a, Vec2D<T> b) {
    if (b < a)
        swap(a, b);
    return (p == a) || (p == b) || (a < p && p < b);
}

// ab ���а� cd ������ �������� ���θ� Ȯ���ϰ�, ���ܴٸ� �� ������ ���Ѵ�.
template <typename T>
bool segmentIntersection(Vec2D<T> a, Vec2D<T> b, Vec2D<T> c, Vec2D<T> d, Vec2D<double>& out) {
    if (!lineIntersection(a, b, c, d, out))
        return parallelSegments(a, b, c, d, out);
    return inBoundingRectangle(out, Vec2D<double>(a), Vec2D<double>(b)) &&
        inBoundingRectangle(out, Vec2D<double>(c), Vec2D<double>(d));
}

// ab ���а� cd ������ �������� ���� Ȯ��
template <typename T>
bool isSegmentIntersect(Vec2D<T> a, Vec2D<T> b, Vec2D<T> c, Vec2D<T> d) {
    T ab = (b - a).cross(c - a) * (b - a).cross(d - a);
    T cd = (d - c).cross(a - c) * (d - c).cross(b - c);

    // �� ������ �� �������� �ְų� ������ ����
    if (ab == 0 && cd == 0) {
        if (b < a)
            swap(a, b);
        if (d < c)
            swap(c, d);
        return !(b < c || d < a);
    }

    return ab <= 0 && cd <= 0;
}


//--------- Point to Line ---------------------------------

template <typename T>
Vec2D<double> perpendicularFoot(Vec2D<T> p, Vec2D<T> a, Vec2D<T> b) {
    Vec2D<double> r = (p - a).project(b - a);
    r.x += a.x;
    r.y += a.y;
    return r;
}

template <typename T>
double distancePointToLine(Vec2D<T> p, Vec2D<T> a, Vec2D<T> b) {
    Vec2D<double> foot = perpendicularFoot(p, a, b);
    return hypot(p.x - foot.x, p.y - foot.y);
}
