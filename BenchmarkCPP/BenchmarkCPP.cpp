#include "Utility.cpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <random>
#include <map>
#include <chrono>
#include <functional>
using namespace std;
using namespace Utility;

class Vector2 {
public:
	float x;
	float y;
	static Vector2 up() { return Vector2(0, 1); }
	static Vector2 down() { return Vector2(0, -1); }
	static Vector2 right() { return Vector2(1, 0); }
	static Vector2 left() { return Vector2(-1, 0); }

	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vector2() {
		this->x = 0;
		this->y = 0;
	}

	static float Distance(Vector2 from, Vector2 to) {
		return sqrt(pow(abs(from.x - to.x), 2) + pow(abs(from.y - to.y), 2));
	}

	operator std::string() const { return "{x: " + toString(x) + " y: " + toString(y) + "}"; }
	Vector2 operator ++() { this->x++; this->y++; return *this; }
	Vector2 operator --() { this->x--; this->y--; return *this; }
	void operator +=(Vector2 v2) { this->x += v2.x; this->y += v2.y; }
	void operator -=(Vector2 v2) { this->x -= v2.x; this->y -= v2.y; }
	void operator +(Vector2 v2) { this->x += v2.x; this->y += v2.y; }
	void operator -(Vector2 v2) { this->x -= v2.x; this->y -= v2.y; }
	void operator +=(Vector2Int v2) { this->x += v2.x; this->y += v2.y; }
	void operator -=(Vector2Int v2) { this->x -= v2.x; this->y -= v2.y; }
	void operator +(Vector2Int v2) { this->x += v2.x; this->y += v2.y; }
	void operator -(Vector2Int v2) { this->x -= v2.x; this->y -= v2.y; }
	void operator *(float f) { this->x *= f; this->y *= f; }
	void operator *=(float f) { this->x *= f; this->y *= f; }
	void operator /(float f) { this->x /= f; this->y /= f; }
	void operator /=(float f) { this->x /= f; this->y /= f; }
};

class Vector2Int {
public:
	int x;
	int y;
	static Vector2Int up() { return Vector2Int(0, 1); }
	static Vector2Int down() { return Vector2Int(0, -1); }
	static Vector2Int right() { return Vector2Int(1, 0); }
	static Vector2Int left() { return Vector2Int(-1, 0); }

	Vector2Int(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Vector2Int() {
		this->x = 0;
		this->y = 0;
	}

	static float Distance(Vector2Int from, Vector2Int to) {
		return sqrt(pow(from.x - to.x, 2) + pow(from.y - to.y, 2));
	}

	operator std::string() const { return "{x: " + toString(x) + " y: " + toString(y) + "}"; }
	Vector2Int operator ++() { this->x++; this->y++; return *this; }
	Vector2Int operator --() { this->x--; this->y--; return *this; }
	void operator +=(Vector2Int v2) { this->x += v2.x; this->y += v2.y; }
	void operator -=(Vector2Int v2) { this->x -= v2.x; this->y -= v2.y; }
	Vector2Int operator +(Vector2Int v2) { this->x += v2.x; this->y += v2.y; return *this; }//todo fix the other operators
	void operator -(Vector2Int v2) { this->x -= v2.x; this->y -= v2.y; }
	void operator *(float f) { this->x *= f; this->y *= f; }
	void operator *=(float f) { this->x *= f; this->y *= f; }
	void operator /(float f) { this->x /= f; this->y /= f; }
	void operator /=(float f) { this->x /= f; this->y /= f; }
	bool operator ==(Vector2Int v2) { return (this->x == v2.x && this->y == v2.y) ? true : false; }
};

const Vector2Int directions[8] = { Vector2Int(0, -1),  Vector2Int(-1, 0),  Vector2Int(1, 0),  Vector2Int(0, 1),  Vector2Int(1, 1),  Vector2Int(-1, 1),  Vector2Int(1, -1), Vector2Int(-1, -1) };

Vector2 ifelseTest(float angle) {
	Vector2 instPlace = Vector2(0, 0);
	if (abs(angle) > 22.5f && abs(angle) <= 67.5f)
		instPlace = (angle > 0) ? Vector2(-.7f, .7f) : Vector2(.7f, .7f);
	else if (abs(angle) > 67.5f && abs(angle) <= 112.5f)
		instPlace = (angle > 0) ? Vector2::left() : Vector2::right();
	else if (abs(angle) > 112.5f && abs(angle) <= 157.5f)
		instPlace = (angle > 0) ? Vector2(-.7f, -.7f) : Vector2(.7f, -.7f);
	else
		instPlace = (abs(angle) > 90) ? Vector2::down() : Vector2::up();
	return instPlace;
}

Vector2 ternaryTest(float signedAngle) {

	return (signedAngle > 0) ? (abs(signedAngle) < 22.5f) ? Vector2::up() : (abs(signedAngle) < 67.5f) ? Vector2(-.7f, .7f) : (abs(signedAngle) < 112.5f) ? Vector2::left() : (abs(signedAngle) < 157.5f) ? Vector2(-.7f, -.7f) : Vector2::down() : (abs(signedAngle) < 22.5f) ? Vector2::up() : (abs(signedAngle) < 67.5f) ? Vector2(.7f, .7f) : (abs(signedAngle) < 112.5f) ? Vector2::right() : (abs(signedAngle) < 157.5f) ? Vector2(.7f, -.7f) : Vector2::down();
}

void Vector2Benchmark(int numOfThreads) {
	cout << "number of threads: " << numOfThreads << "\n";
	cout << fixed;
	cout.precision(2);
	vector<thread*> threads;
	vector<int> counting;
	default_random_engine generator;
	uniform_real_distribution<float> distribution(-180, 180);
	auto randAngle = bind(distribution, generator);
	vector<double> ternary, ifelse;
	long long iterations = 500, iterationsPerTest = 1000000, totalIterationsMain = 0;
	long long iterations2 = iterations * 2;
	system("pause");
	cout << "Starting\n\n";
	for (int c = 0; c < numOfThreads; c++) {
		threads.push_back(new thread([&]() {
			while (counting.size() < iterations) {
				counting.push_back(1);
				long long totalIterations = 0;
				double tern = 0, ifel = 0;
				auto start = chrono::high_resolution_clock::now();
				float signedAngle = randAngle();
				for (long long i2 = 0; i2 < iterationsPerTest; i2++) {
					signedAngle = randAngle();
					Vector2 returnedV2 = ifelseTest(signedAngle);
					totalIterations++;
				}
				auto end = chrono::high_resolution_clock::now();
				chrono::duration<double, std::milli> elapsed = end - start;
				ifel = elapsed.count();
				elapsed.zero();
				ifelse.push_back(ifel);
				start = chrono::high_resolution_clock::now();
				for (int i2 = 0; i2 < iterationsPerTest; i2++) {
					signedAngle = randAngle();
					Vector2 returnedV2 = ternaryTest(signedAngle);
					totalIterations++;
				}
				end = chrono::high_resolution_clock::now();
				elapsed = end - start;
				tern = elapsed.count();
				ternary.push_back(tern);
				totalIterationsMain += totalIterations;
				cout << endl << "ifelse - " << toString(ifel) << endl << "ternary - " << toString(tern) << endl;
			}
			cout << "\nInverting\n";
			this_thread::sleep_for(1500ms);
			while (counting.size() < iterations2) {
				counting.push_back(1);
				long long totalIterations2 = 0;
				double tern = 0, ifel = 0;
				float signedAngle = randAngle();
				auto start = chrono::high_resolution_clock::now();
				for (long long i2 = 0; i2 < iterationsPerTest; i2++) {
					signedAngle = randAngle();
					Vector2 returnedV2 = ternaryTest(signedAngle);
					totalIterations2++;
				}
				auto end = chrono::high_resolution_clock::now();
				chrono::duration<double, std::milli> elapsed = end - start;
				tern = elapsed.count();
				elapsed.zero();
				ternary.push_back(tern);
				start = chrono::high_resolution_clock::now();
				for (long long i2 = 0; i2 < iterationsPerTest; i2++) {
					signedAngle = randAngle();
					Vector2 returnedV2 = ifelseTest(signedAngle);
					totalIterations2++;
				}
				end = chrono::high_resolution_clock::now();
				elapsed = end - start;
				ifel = elapsed.count();
				ifelse.push_back(ifel);
				totalIterationsMain += totalIterations2;
				cout << endl << "ifelse - " << toString(ifel) << endl << "ternary - " << toString(tern) << endl;
			}
			}));
		cout << "Thread " << c << " - Starting\n";
	}
	for (thread*& th : threads) {
		th->join();
	}
	double totalTime = 0;
	for (double time : ifelse) {
		totalTime += time;
	}
	cout << "\nAvg ifelse: " << toString(totalTime / ifelse.size());
	totalTime = 0;
	for (double time : ternary) {
		totalTime += time;
	}
	cout << "\nAvg ternary: " << toString(totalTime / ternary.size());
	cout << "\ntotal iterations: " << totalIterationsMain << "\n";
	system("pause");
	for (thread*& t : threads)
		delete t;
	threads.clear();
	counting.clear();
	ternary.clear();
	ifelse.clear();
}

class Node {
public:
	bool isWalkable = true, isNull = false;
	Node* parent = nullptr;
	Vector2Int position;
	float distanceToTarget = NAN, cost = 1, weight;
	float F() { return (distanceToTarget != NAN && cost != NAN) ? (distanceToTarget + cost) : NAN; }

	Node() {
		this->position = Vector2Int();
		this->weight = 1;
		this->isNull = true;
	}

	Node(Vector2Int pos, float weight = 1) {
		this->position = pos;
		this->weight = weight;
	}

	void ResetNode() {
		this->parent = nullptr;
		this->distanceToTarget = NAN;
		this->cost = 1;
	}
};

class NodeManager {
public:
	vector<map<Vector2Int, Node>> Maps;

	static map<Vector2Int, Node> NewMapStruct() {
		Vector2Int startingPos = Vector2Int(0, 0);
		Vector2Int endingPos = Vector2Int(200, 150);
		Vector2Int currentPos = Vector2Int(startingPos.x, startingPos.y);
		map<Vector2Int, Node> newMap;
		while (currentPos.x <= endingPos.x) {
			currentPos.y = startingPos.y;
			while (currentPos.y <= endingPos.y) {
				Node newNode = Node(currentPos);
				newMap.insert(pair<Vector2Int, Node>(currentPos, newNode));
				currentPos.y++;
			}
			currentPos.x++;
		}
		return newMap;
	}

	static void CreateWalls(int startingNodeX, int endingNodeX, int startingNodeY, int endingNodeY, map<Vector2Int, Node>& map)
	{
		int currentMod;
		currentMod = startingNodeY;
		while (currentMod <= endingNodeY)
		{
			try {
				map.at(Vector2Int(startingNodeX, currentMod)).isWalkable = false;
			}
			catch (out_of_range e) {}
			currentMod++;
		}
		currentMod = startingNodeX;
		while (currentMod <= endingNodeX)
		{
			try {
				map.at(Vector2Int(currentMod, endingNodeY)).isWalkable = false;
			}
			catch (out_of_range e) {}
			currentMod++;
		}
	}

	static void CreateWallX(int startingNodeX, int endingNodeX, int Y, map<Vector2Int, Node>& map)
	{
		int currentMod = startingNodeX;
		while (currentMod <= endingNodeX)
		{
			try {
				map.at(Vector2Int(currentMod, Y)).isWalkable = false;
			}
			catch (out_of_range e) {}
			currentMod++;
		}
	}

	static void CreateWallY(int startingNodeY, int endingNodeY, int X, map<Vector2Int, Node>& map)
	{
		int currentMod = startingNodeY;
		while (currentMod <= endingNodeY)
		{
			try {
				map.at(Vector2Int(X, currentMod)).isWalkable = false;
			}
			catch (out_of_range e) {}
			currentMod++;
		}
	}

	void CreatMaps() {
		map<Vector2Int, Node> newMap = NewMapStruct();
		CreateWalls(50, 110, 0, 120, newMap);
		CreateWalls(100, 200, 40, 90, newMap);
		CreateWalls(150, 175, 0, 60, newMap);
		Maps.push_back(newMap);
		map<Vector2Int, Node> newMap2 = NewMapStruct();
		CreateWallY(75, 150, 100, newMap2);
		CreateWallX(100, 130, 75, newMap2);
		Maps.push_back(newMap2);
		map<Vector2Int, Node> newMap3 = NewMapStruct();
		CreateWallY(20, 150, 20, newMap3);
		CreateWallX(20, 180, 20, newMap3);
		CreateWallY(20, 130, 180, newMap3);
		CreateWallX(50, 180, 130, newMap3);
		CreateWallY(50, 130, 50, newMap3);
		CreateWallX(50, 150, 50, newMap3);
		CreateWallY(50, 100, 150, newMap3);
		CreateWallX(100, 150, 100, newMap3);
		CreateWallY(75, 100, 100, newMap3);
		CreateWallX(100, 125, 75, newMap3);
		CreateWallY(75, 85, 125, newMap3);
		Maps.push_back(newMap3);
	}

	static Node FindClosestNode(Vector2 position, map<Vector2Int, Node>& map) {
		Vector2Int convPos = Vector2Int((int)position.x, (int)position.y);
		try {
			return map.at(convPos);
		}
		catch (out_of_range e) {
			return Node();
		}
	}

	static Node FindClosestNodeOutsideGrid(Vector2 position, map<Vector2Int, Node>& map)
	{
		Node bestMatch = Node();
		float distance;
		float previousDistance = INFINITY;
		for (auto& value : map)
		{
			distance = Vector2::Distance(position, Vector2(value.second.position.x, value.second.position.y));
			if (distance < previousDistance)
				bestMatch = value.second;
			previousDistance = distance;
		}
		return bestMatch;
	}

	static Node* FindExactNode(Vector2Int position, map<Vector2Int, Node>& map)
	{
		try {
			return &map.at(position);
		}
		catch (out_of_range e) {
			return nullptr;
		}
	}

	static vector<Node*> GetConnectedNodes(Node node, map<Vector2Int, Node>& map)
	{
		vector<Node*> connectedNodes;
		Vector2Int v2Int = node.position;
		for (Vector2Int dir : directions)
		{
			try {
				connectedNodes.push_back(FindExactNode(dir + v2Int, map));
			}
			catch (out_of_range) {}
		}
		return connectedNodes;
	}

	static void ResetAllNodes(map<Vector2Int, Node> dict)
	{
		for (auto& value : dict)
		{
			value.second.ResetNode();
		}
	}
};

struct SortByF {
	inline bool operator() (Node* n1, Node* n2)
	{
		return (n1->F() < n2->F());
	}
};

class AStar {
public:
	static bool containsSameVector2(vector<Node*>& vec, Node* node) {
		for (Node* tNode : vec) {
			if (tNode->position == node->position)
				return true;
		}
		return false;
	}

	static bool existInVector(vector<Node*>& vec, Node* node) {
		for (Node* tNode : vec) {
			if (tNode == node)
				return true;
		}
		return false;
	}

	static vector<Node*> Pathfinding(Vector2 start, Vector2 end, map<Vector2Int, Node>& map) {
		NodeManager::ResetAllNodes(map);
		vector<Node*> path;
		Node* startNode = &NodeManager::FindClosestNode(start, map);
		Node* endNode = &NodeManager::FindClosestNode(end, map);
		vector<Node*> closedList;
		vector<Node*> openList;
		vector<Node*> connectedNodes;
		Node* current = startNode;
		openList.push_back(current);
		while (openList.size() > 0 && !containsSameVector2(closedList, endNode)) {
			current = openList[0];
			openList.erase(openList.begin());
			closedList.push_back(current);
			if (containsSameVector2(closedList, endNode))
				break;
			connectedNodes = NodeManager::GetConnectedNodes(*current, map);
			for (Node* node : connectedNodes) {
				if (node == nullptr)
					continue;
				if (!existInVector(closedList, node) && node->isWalkable) {
					if (!existInVector(openList, node)) {
						node->parent = current;
						node->distanceToTarget = Vector2Int::Distance(node->position, endNode->position);
						node->cost = node->weight + node->parent->cost;
						openList.push_back(node);
					}
				}
			}
			sort(openList.begin(), openList.end(), SortByF());
		}
		vector<Node*> empty;
		if (!existInVector(closedList, current) || !containsSameVector2(closedList, endNode))
			return empty;
		Node* temp = closedList.back();
		do {
			path.push_back(temp);
			temp = temp->parent;
		} while (temp != startNode && temp != nullptr);
		return path;
	}
};

int main()
{
	const int numOfThreads = thread::hardware_concurrency();
	Vector2Benchmark(numOfThreads);
}