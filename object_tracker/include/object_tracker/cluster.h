#pragma once

#include <object_tracker/define.h>
#include <list>

namespace TeamKR
{

class Cluster
{
public:
	Cluster();

	~Cluster();

public:
	Cluster* clone(Cluster* rhs) const;

	void add(const Vector3& point, int hitCount, value_type intensity, value_type minZ);

	const Vector3& min() const;

	const Vector3& max() const;

	Vector3 center() const;

	const Vector3& top() const;

	int pointCount() const;

	value_type maxIntensity() const;

	value_type area() const;

private:
	int pointCount_;
	std::list<Vector3> points_;
	Vector3 min_;
	Vector3 max_;
	value_type maxIntensity_;
	Vector3 top_;
};

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

class ClusterBuilder
{
public:
	struct Index
	{
		Index(int _x, int _y)
		{
			x = _x;
			y = _y;
		}

		int x;
		int y;
	};

	struct Value
	{
		Value()
		{
			hit = 0;
			top = value_type(-1000.0);
			topx = value_type(0);
			topy = value_type(0);
			base = value_type(1000.0);
			intensity = value_type(0);
		}

		void clear()
		{
			hit = 0;
			top = value_type(-1000.0);
			topx = value_type(0);
			topy = value_type(0);
			base = value_type(1000.0);
			intensity = value_type(0);
		}

		int hit;
		value_type top;
		value_type topx;
		value_type topy;
		value_type base;
		value_type intensity;
	};

public:
	ClusterBuilder(value_type centerX, value_type centerY);

	~ClusterBuilder();

	void run(const PCLPointVector& points, const BitVector& filterBV, std::list<Cluster*>& clusters);

private:
	void clear();

	void hit(const PCLPoint& point);

	int hitCount(int ix, int iy) const;

	value_type top(int ix, int iy) const;

	void addPoint(int ix, int iy, Cluster* cluster);

private:
	value_type centerX_;
	value_type centerY_;
	value_type originX_;
	value_type originY_;
	value_type baseZ_;
	value_type radius_;
	int iwidth_;
	int iradius_;
	int iradius2_;
	Value** valuemap_;
	char** bitmap_;
};

}
