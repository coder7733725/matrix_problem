#include "quad.h"
#include <iostream>
#include <set>
#include <stack>

const int Quad::s_NW = 1;
const int Quad::s_NE = 2;
const int Quad::s_SW = 3;
const int Quad::s_SE = 4;

int** Quad::matrix = 0;

const int MIN_QUAD_SIZE = 1;

using namespace std;


Quad* Quad::create_quad(int** matrix, int n)
{
	Quad::matrix = matrix;
	Quad* root = new Quad(n,Position(0,0));
	create_children(root);
	return root;
}

bool Quad::is_leaf_node()
{
	if( this->NE == 0 && this->NW == 0 && this->SE == 0 && this->SW == 0 )
	{
		return true;
	}
	return false;
}

bool Quad::is_node(Color color)
{
	bool all_same=true;
	for( int i =0; i < this->size && all_same; ++i )
	{
		for(int j=0;j < this->size && all_same; ++j)
		{
			all_same &= (this->matrix[this->position.x+i][this->position.y+j] == color);
		}
	}
	return all_same;
}

void Quad::create_children(Quad* root)
{
	if(root == 0 )
	{
		return;
	}
	int q_size = root->size/2;
	if( q_size == 0 )
	{
		return;
	}
	if(root->is_node(black) || root->is_node(white) )
	{
		return;
	}
	Quad* node;

	root->NW = new Quad( root->position, q_size);
	root->NE = new Quad( Position(root->position.x,root->position.y+q_size), q_size);
	root->SW = new Quad( Position(root->position.x+q_size,root->position.y), q_size);
	root->SE = new Quad( Position(root->position.x+q_size,root->position.y+q_size), q_size);
	if(q_size >= MIN_QUAD_SIZE )
	{
		create_children(root->NE);
		create_children(root->NW);
		create_children(root->SE);
		create_children(root->SW);
	}
	
}

Quad* process_matrix(int n)
{
	int** matrix=new int*[n];
	for(int i=0; i< n; ++i)
	{
		matrix[i] = new int[n];
	}
	char* cinput=new char[n+1];
	int i=0;
	while(i<n)
	{
		int j=0;
		while(j<n)
		{
			cin>>cinput[j++];
		}
		
		cinput[j] = 0;
		j=0;
		for(int k=0; k<n; ++k)
		{
			matrix[i][k] = cinput[k] - '0';
		}
		++i;
	}
	Quad* root = Quad::create_quad(matrix,n);
	delete cinput;
	return root;	
}

bool Quad::is_black_node()
{
	if(this->size == 1 && this->matrix[this->position.x][this->position.y] == 1 )
	{
		return true;
	}
	return false;
}

int reverse(int n)
{
	int num=0;
	while(n)
	{
		num = num*10 + (n%10);
		n /= 10;
	}
	return num;
}

int calculate_base5(stack<int> path)
{
	int num=0;
	while(!path.empty())
	{
		num = num * 5 + path.top();
		path.pop();
	}
	return num;
}

int frombase10tobase5(int n)
{
	int num=reverse(n);
	int pow5=1;
	int val=0;
	while(num)
	{
		val = val * 5 + num%10;
		num /= 10;
	}
	return val;
}

void black_nodes(Quad* root,stack<int> path,std::set<int>& black_nodes_base10)
{
	if( root == 0 )
	{
		return;
	}
	if( root->is_leaf_node() && root->is_node(black) )
	{
		int val = calculate_base5(path);
		//cout << "\nposition : (" << root->position.x << " , " << root->position.y << ") val : " << val << " size : " << root->size <<"\n";
		black_nodes_base10.insert( val );
		return;
	}
	path.push(Quad::s_NW);
	black_nodes( root->NW,path,black_nodes_base10 );
	path.pop();

	path.push(Quad::s_NE);
	black_nodes( root->NE,path,black_nodes_base10 );
	path.pop();

	path.push(Quad::s_SW);
	black_nodes( root->SW , path, black_nodes_base10);
	path.pop();

	path.push(Quad::s_SE);
	black_nodes( root->SE , path,black_nodes_base10 );
	path.pop();

}

int main(int argc , char** argv)
{
	int n;
	cin >> n;
	Quad* root = process_matrix(n);

	std::set<int> black_nodes_base10;
	stack<int> path;

	black_nodes(root,path,black_nodes_base10);
	int count=0;
	for( int val : black_nodes_base10)
	{
		cout << val << " ";
		++count;
		if(count %12 == 0)
		{
			cout<<endl;
		}

	}
	cout << endl;
	cout << "Total number of black nodes = " << count ;
	cout << endl;
	return 0;
}
