
#include <array>
#include <vector>
#include <iostream>
#include <assert.h>
#include <numeric>
#include <algorithm>
#include <memory>
#include<fstream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

namespace KDTree
{
	double strtodouble(string num) {
		double res;
		stringstream stream(num);
		stream >> res;
		return res;
	}
	using CuttimgDim = char;
	struct Point
	{
		double p[2];
		Point(double x = 0, double y = 0) :p{ x,y } {}
		bool operator==(const Point& rp) const
		{
			return (p[0] == rp[0] && p[1] == rp[1]);
		}
		double operator[](CuttimgDim c) const
		{
			assert(c < 2 && c >= 0);
			return p[c];
		}
		static const Point* min(const Point* p1, const Point* p2, CuttimgDim c)
		{
			if (p1 && p2)
			{
				if ((*p1)[c] < (*p2)[c])
					return p1;
				return p2;
			}
			if (!p1)
				return p2;
			return p1;
		}
		static const Point* max(const Point* p1, const Point* p2, CuttimgDim c)
		{
			if (p1 && p2)
			{
				if ((*p1)[c] < (*p2)[c])
					return p2;
				return p1;
			}
			if (!p1)
				return p2;
			return p1;
		}
	};


	struct city_info
	{
		//ascii_name,country name,longitude, latitude, and population
		city_info(Point p = Point()) :location(p), ascii_name(""), country_name(""), population("0"), left(nullptr), right(nullptr)
		{
		}
		Point location;

		string ascii_name;
		string country_name;
		string population;


		city_info* left, * right;

		city_info* next = nullptr;
		int split = 0;
	};



	class kd_tree
	{
	public:
		vector<city_info> mCitysuffer;
		vector<city_info> Cities;
		vector<city_info*> sameplacecities;
		city_info* cityroot = nullptr;
		size_t buffercityIndex = 0;
		city_info* nearestcity = nullptr;;
		double nearest_dis = 0;
		size_t n = 0;

		void construt(string filename, vector<city_info>& pnts)
		{
			ifstream csvInput(filename);
			vector<string> lines;
			string line, word, temp;
			int count = 0;
			getline(csvInput, temp);
			while (getline(csvInput, line)) {

				lines.clear();

				// used for breaking words 
				stringstream breakline(line);

				// read every column data of a row and 
				// store it in a string variable, 'word' 
				while (getline(breakline, word, ',')) {

					// add all the column data 
					// of a row to a vector 
					lines.push_back(word);

				}
				Point p = { strtodouble(lines[2]),strtodouble(lines[3]) };
				city_info city;
				city.location = p;
				city.ascii_name = lines[1];
				city.country_name = lines[4];
				city.population = lines[9];
				if (city.population == "")
				{
					city.population = "0";
				}
					
				Cities.push_back(city);

			}
			cityconstrut(pnts);
		}

		void cityconstrut(vector<city_info>& pnts)
		{
			mCitysuffer.reserve(pnts.size());
			mCitysuffer.emplace_back(pnts[0]);
			cityroot = &mCitysuffer[buffercityIndex++];
			for (int i = 1; i < pnts.size(); ++i)
			{
				cityinsert(pnts[i], cityroot, 0);
			}
		}
		city_info* cityinsert(city_info& p, city_info* node, CuttimgDim c)
		{

			CuttimgDim nextCD = 1 - c;
			if (node == nullptr)
			{
				mCitysuffer.emplace_back(p);
				return &mCitysuffer[buffercityIndex++];
			}

			if (p.location == node->location)
			{

				node->next = &p;
				//cout << "The city location is" << p.location[0] << "," << p.location[1] << endl;
				return node;
			}

			if (p.location[c] < node->location[c])
			{

				node->left = cityinsert(p, node->left, nextCD);
			}
			else
			{

				node->right = cityinsert(p, node->right, nextCD);
			}


			return node;
		}

		void Print()
		{
			Print(cityroot);

		}
		void Print(city_info* root)
		{
			if (root == nullptr)
				return;
			Print(root->left);
			cout << "[" << root->location[0] << "," << root->location[1] << "]" << endl;
			if (root->next != nullptr)
				cout << "[" << root->next->location[0] << "," << root->next->location[1] << "]" << endl;
			Print(root->right);

		}

		city_info* Findthenearestcity(Point& city)
		{
			if (&city == nullptr)
			{
				cout << "ERROR" << endl;
			}
			nearestcity = nullptr;
			n = 0;
			nearest_dis = 0;
			NN(cityroot, city, 0);
			return nearestcity;

		}

		void NN(city_info* root, Point& city, size_t index)
		{
			if (root == nullptr)
			{
				return;
			}
			n++;
			double dist = GetDistance(root->location, city);
			if (nearestcity == nullptr || dist < nearest_dis)
			{
				nearest_dis = dist;
				nearestcity = root;
			}
			if (nearest_dis == 0)
			{
				return;
			}
			double dist2 = root->location[index] - city[index];
			index = (index + 1) % 2;
			if (dist2 > 0)
			{
				NN(root->left, city, index);
				NN(root->right, city, index);

			}
			else
			{
				NN(root->right, city, index);
				NN(root->left, city, index);
			}

		}

		void SearchNearestPoint()
		{
			double x, y;
			cout << "Enter the location to find the nearest city" << endl;
			cout << "[latitude]X: ";
			cin >> x;
			cout << "[longitude]Y: ";
			cin >> y;
			Point c = { x,y };
			SearchNearestPoint(c);
		}
		void SearchNearestPoint(Point A)
		{
			city_info city;
			city_info* nearcity;
			nearcity = Findthenearestcity(A);
			nearcity = FindTheCity(nearcity->location);
			cout << "The nearest city is " << " [" << nearcity->location[0]
				<< "," << nearcity->location[1] << "]  " << nearcity->ascii_name << ", " << nearcity->country_name;
			while (nearcity->next != nullptr)
			{
				nearcity = nearcity->next;
				cout << "; " << nearcity->ascii_name << ", " << nearcity->country_name;

			}

			cout << endl;

		}

		double GetDistance(Point p, Point n)
		{
			double sum = 0;
			for (int i = 0; i < 2; i++)
			{
				sum += pow(p[i] - n[i], 2);
			}
			return sqrt(sum);
		}


		city_info* FindTheCity(Point p)
		{

			for (int i = 0; i < mCitysuffer.size(); i++)
			{
				if (mCitysuffer[i].location == p)
				{

					sameplacecities.push_back(&mCitysuffer[i]);
				}

			}
			return sameplacecities[0];

		}


		city_info* FindTheCity(string city_name, string country_name)
		{

			for (int i = 0; i < mCitysuffer.size(); i++)
			{
				if (mCitysuffer[i].ascii_name.compare(city_name) == 0 &&
					mCitysuffer[i].country_name.compare(country_name) == 0)
				{
					cout << "The city " << "[" << mCitysuffer[i].location[0] << "," << mCitysuffer[i].location[1] << "], " <<
						mCitysuffer[i].ascii_name << ", " << mCitysuffer[i].country_name <<", "<< mCitysuffer[i].population<< " is found" << endl;
					return &mCitysuffer[i];
				}

			}
			return nullptr;


		}

		void FindCity()
		{
			string x, y;
			city_info* city;
			cout << "Enter the country and city name to find the city" << endl;
			cout << "Enter the country name " << endl;
			cout << "Country: ";
			getline(cin, x);

			cout << "Enter the city name" << endl;
			cout << "City: ";
			getline(cin, y);

			city = FindTheCity(y, x);
			if (city == nullptr)
			{
				cout << "There is no such city" << endl;
			}


		}


	};

}

using namespace KDTree;
int main()
{
	kd_tree theTree;
	theTree.construt("worldcities.csv", theTree.Cities);

	//theTree.cityconstrut(theTree.Cities);
	theTree.FindCity();
	cout << endl;
	theTree.SearchNearestPoint();

	system("pause");
	return 0;
}