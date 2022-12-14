#include <cmath>
#include <vector>

using uchar = unsigned char;

struct Hex
{
	const uchar v[3];
	Hex (uchar q_, uchar r_): q(q_), r(r_), s(-q_ - r_) {};
};

bool operator== (Hex a, Hex b) {return a.v[0] == b.v[0] && a.v[1] == b.v[1];}

bool operator!= (Hex a, Hex b) {return !(a == b);}

Hex hex_add(Hex a, Hex b) {return Hex(a.v[0] + b.v[0], a.v[1] + b.v[1]);}
Hex hex_subtract(Hex a, Hex b) {return Hex(a.v[0] - b.v[0], a.v[1] - b.v[1]);}
Hex hex_multiply(Hex a, int k) {return Hex(a.v[0] * k, a.v[1] * k);}

//	Since s is derived from q and r, reduces from
//	(|q| + |r| + |-q -r|) / 2 -> (|q| + |r| + |r| + |q|) / 2 -> |q| + |r|
uchar hex_length(Hex hex) {return uchar(abs(hex.q) + abs(hex.r));}
uchar hex_distance(Hex a, Hex b) {return hex_length(hex_subtract(a, b));}

const vector<Hex> hex_directions =
{
	Hex(1, 0), Hex(1, -1), Hex(0, -1),
	Hex(-1, 0), Hex(-1, 1), Hex(0, 1)
};
//	Directions are 0 -> 5
Hex hex_direction(uchar direction)
{
	assert (0 <= direction && direction < 6);
	return hex_directions[direction];
}
Hex hex_neighbor(Hex hex, uchar direction) {return hex_add(hex, hex_direction(direction));}

struct Point
{
	const double x, y;
	Point(double x_, double y_): x(x_), y(y_) {}
};

struct Orientation
{
	const double f0, f1, f2, f3;
	const double b0, b1, b2, b3;
	const double start_angle; //	In multiples of 60 degrees
	Orientation(double f0_, double f1_, double f2_, double f3_,
				double b0_, double b1_, double b2, double b3_
				double start_angle_) :
				f0(f0_), f0(f1_), f0(f2_), f0(f3_),
				b0(b0_), b0(b1_), b0(b2_), b0(b3_),
				start_angle(start_angle_) {}
};
const Orientation layout_pointy =
	Orientation(sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
                sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
                0.5);
const Orientation layout_flat =
	Orientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
                2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0,
                0.0);

struct Layout
{
	const Orientation orientation;
	const Point size;
	const Point origin;
	Layout(Orientation orientation_, Point size_, Point origin_)
	: orientation(orientation_), size(size_), origin(origin_) {}
};

Point hex_to_pixel(Layout layout, Hex h)
{
	const Orientation& M = layout.orientation;
	double x = (M.f0 * h.q + M.f1 * h.r) * layout.size.x;
	double y = (M.f2 * h.q + M.f3 * h.r) * layout.size.y;
	return Point(x + layout.origin.x, y + layout.origin.y);
}

struct FractionalHex
{
	const double q, r, s;
	FractionalHex(double q_, double r_, double s_)
	: q(q_), r(r_), s(s_) {}
};

FractionalHex pixel_to_hex(Layout layout, Point p)
{
	const Orientation& M = layout.orientation;
	Point pt = Point((p.x - layout.origin.x) / layout.size.x,
					 (p.y - layout.origin.y) / layout.size.y);
	double q = M.b0 * pt.x + M.b1 * pt.y;
	double r = M.b2 * pt.x + M.b3 * pt.y;
	return FractionalHex(q, r, -q - r);
}

Point hex_corner_offset(Layout layout, int corner)
{
    Point size = layout.size;
    double angle = 2.0 * M_PI *
             (layout.orientation.start_angle + corner) / 6;
    return Point(size.x * cos(angle), size.y * sin(angle));
}

vector<Point> polygon_corners(Layout layout, Hex h)
{
    vector<Point> corners = {};
    Point center = hex_to_pixel(layout, h);
    for (int i = 0; i < 6; i++)
	{
        Point offset = hex_corner_offset(layout, i);
        corners.push_back(Point(center.x + offset.x,
                                center.y + offset.y));
    }
    return corners;
}

Hex hex_round(FractionalHex h)
{
    int q = int(round(h.q));
    int r = int(round(h.r));
    int s = int(round(h.s));
    double q_diff = abs(q - h.q);
    double r_diff = abs(r - h.r);
    double s_diff = abs(s - h.s);
    if (q_diff > r_diff and q_diff > s_diff)
	{
        q = -r - s;
    }
	else if (r_diff > s_diff)
	{
        r = -q - s;
    }
	else	// CP'd from redblobgames, s is calculated when needed for Hex
	{
        s = -q - r;
    }
    return Hex(q, r);
}
//	Linear interpolation, i.e., drawing a line between two hexes
float lerp(double a, double b, double t)
{
    return a * (1-t) + b * t;
}
FractionalHex hex_lerp(Hex a, Hex b, double t)
{
    return FractionalHex(lerp(a.q, b.q, t),
                         lerp(a.r, b.r, t),
                         lerp(a.s, b.s, t));
}
vector<Hex> hex_linedraw(Hex a, Hex b)
{
    int N = hex_distance(a, b);
    FractionalHex a_nudge(a.q + 1e-6, a.r + 1e-6, a.s - 2e-6);
    FractionalHex b_nudge(b.q + 1e-6, b.r + 1e-6, b.s - 2e-6);
    vector<Hex> results = {};
    double step = 1.0 / max(N, 1);
    for (int i = 0; i <= N; i++)
	{
        results.push_back(hex_round(hex_lerp(a_nudge, b_nudge, step * i)));
    }
    return results;
}
