
Int2 int2Zero = {0, 0};
Int2 int2Error = {-1, -1};

Int2 int2(int x, int y)
{
	Int2 t = {x, y};
	return t;
}

bool int2Equals(Int2 a, Int2 b)
{
	return a.x == b.x && a.y == b.y;
}

bool int2LessThan(Int2 a, Int2 b)
{
	return a.x < b.x && a.y < b.y;
}