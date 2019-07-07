
enum Color{white=0, black};

struct Position
{
	int x;
	int y;
	Position(int _x, int _y):x(_x),y(_y){}
};

class Quad
{
	public:

	Position position;
	static int** matrix;
	int size;

	Quad* NW;
	Quad* NE;
	Quad* SW;
	Quad* SE;
	
	public:
	
	void init_children()
	{
		this->NW = 0;
		this->NE = 0;
		this->SW = 0;
		this->SE = 0;
	}

	Quad(Position _start, int _size):position(_start),size(_size)
	{
		init_children();
	}

	Quad(int _size, Position _start=Position(0,0)):size(_size), position(_start)
	{
		init_children();
	}
	
	bool is_leaf_node();
	bool is_black_node();
	bool is_node(Color color);

	static Quad* create_quad(int** matrix, int n);

	static void create_children(Quad* root);

	static const int s_NW;
	static const int s_SW;
	static const int s_SE;
	static const int s_NE;
};


