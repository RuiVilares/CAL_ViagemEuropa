/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

/** @defgroup Graph Graph
* @{
* Functions for graph configuration
*/

#include <vector>
#include <algorithm>   
#include <queue>
#include <list>
#include <limits>
#include <cmath>
using namespace std;


/**Class that represents a edge.
*
*/
template <class T> class Edge;

/**Class that represents a graph
*
*/
template <class T> class Graph;

/**
*Global variable used in graph manipulation
*/
const int NOT_VISITED = 0;

/**
*Global variable used in graph manipulation
*/
const int BEING_VISITED = 1;

/**
*Global variable used in graph manipulation
*/
const int DONE_VISITED = 2;

/**
*Global variable used in graph manipulation
*/
const int INT_INFINITY = INT_MAX; 

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

/**Represents vertexes (cities)
*
*/
template <class T>
class Vertex {
	T info; // City information
	vector<Edge<T>  > adj; // Vector with adjacent edges
public:
	/**
	* @brief Vertex constructor
	*/
	Vertex(T in);
	friend class Graph<T>;

	/**
	* @brief Function to add a edge
	*
	* @param dest Vertex destination
	* @param w Vertex weight  
	*/
	void addEdge(Vertex<T> *dest, double w);

	/**
	* @brief Remove edge
	*
	* @param d Vertex destination
	* @return Boolean validation 
	*/
	bool removeEdgeTo(Vertex<T> *d);

	/**
	* @brief Get vertex info
	*
	* @return City information
	*/
	T getInfo() const;

	/**
	* @brief Set vertex info
	*
	* @param info City information
	*/
	void setInfo(T info);

	/**
	* @brief Get adjacent edges
	*
	* @return Vector with adjacent edges
	*/
	vector<Edge<T>> getAdj();

	/**
	* @brief Operator < overloading
	*
	* @param vertex Vertex to compare
	* @return boolean answer
	*/
	bool operator<(const Vertex<T> vertex);

	/**
	* @brief Vertex path
	*
	* @return Vertex pointer
	*/
	Vertex* path;
};


template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}
template <class T>
vector<Edge<T>> Vertex<T>::getAdj(){
	return adj;
}

template <class T>
Vertex<T>::Vertex(T in): info(in) {
	path = NULL;
}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest,w);
	adj.push_back(edgeD);
}

//--
template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}



template <class T>
void Vertex<T>::setInfo(T info) {
	this->info = info;
}




/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */

/**Class edge definition 
*
*/
template <class T>
class Edge {
	Vertex<T> * dest; // Vertex destination
	double weight; // Edge weight
public:
	
	/**
	* @brief Edge construtor
	*
	* @param d Vertex destination
	* @param w edge weight
	*/
	Edge(Vertex<T> *d, double w);

	/**
	* @brief Get vertex destination 
	*
	* @return Vertex
	*/
	Vertex<T>* getDest();

	/**
	* @brief Get edge weight
	*
	* @return edge weight
	*/
	double getWeight();
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w){}

template <class T>
Vertex<T>* Edge<T>::getDest(){
	return dest;
}

template <class T>
double Edge<T>::getWeight(){
	return weight;
}



/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet; // vector with vertexes
	
	//floydWarshall variables
	double ** W;   //weight
	int ** P;   //path

	//Branch and bound variables;
	int** totalP; // Total pleausure
	double ** cost; // Cost 
	double maxBound; // Maximum bound
	double totalCost; // Total cost
	string hamiltonPath; // Hamilton path

public:

	/**
	* @brief Add vertex to the vector 
	*
	* @param in vertex to add
	* @return boolean answer
	*/
	bool addVertex(const T &in);
	
	/**
	* @brief Add edge between sourc and dest
	*
	* @param sourc Source vertex
	* @param dest Destination vertex
	* @param w edge weight
	* @return boolean answer
	*/
	bool addEdge(const T &sourc, const T &dest, double w);

	/**
	* @brief Remove vertex
	*
	* @param in Vertex to remove
	* @return boolean answer
	*/
	bool removeVertex(const T &in);

	/**
	* @brief Remove edge between two vertexes
	*
	* @param sourc Source vertex
	* @param dest Destination vertex
	* @return boolean answer
	*/
	bool removeEdge(const T &sourc, const T &dest);

	/**
	* @brief Get vertexes vector
	*
	* @return vertexes vector
	*/
	vector<Vertex<T> * > getVertexSet() const;

	/**
	* @brief Get number of vertexes
	*
	* @return number of vertexes
	*/
	int getNumVertex() const;

	/**
	* @brief Get a specific vertex
	*
	* @param v vertex
	* @return Specific vertex
	*/
	Vertex<T>* getVertex(const T &v) const;

	/**
	* @brief Get a path
	*
	* @param origin Origin vertex
	* @param dest Destination vertex
	* @return Vector with vertexes in the path
	*/
	vector<T> getPath(const T &origin, const T &dest);


	/**
	* @brief Get cities total time
	*
	* @param city Indexes cities vector 
	* @return Total time in every cities
	*/
	double getCityTime(const vector<int> &city);


	/**
	* @brief Branch and bound auxiliary function
	*
	* @param src Source index
	* @param dst Destination index
	* @param path Hamilton Path
	* @param cost2 Cost
	* @param bound Bound
	* @return auxiliary solution
	*/
	double bb_aux(int src, int dst, string path, double ** cost2, double bound);

	/**
	* @brief Matrix row reduction
	*
	* @param costP Cost
	* @param bound Bound
	*/
	void rowReduction(double ** costP, double &bound);

	/**
	* @brief Matrix colum reduction
	*
	* @param costP Cost
	* @param bound Bound
	*/
	void columReduction(double ** costP, double &bound);

	/**
	* @brief Branch and Bound algorithm 
	*
	*/
	void BB_TSP();

	/**
	* @brief Get Hamilton Path
	*
	* @return string with the solution
	*/
	string getHamiltonPath();

	/**
	* @brief Get total cost
	*
	* @return Total cost
	*/
	double getTotalCost();

	/**
	* @brief Knapsack Algorithm
	*
	* @param maxTime max available time
	*/
	void knapsack(unsigned int maxTime);

	/**
	* @brief Knapsack Solution
	*
	* @param maxTime max available time
	* @return Vector with vertex index solution
	*/
	vector<int> getKnapsackSolution(unsigned int maxTime);

	/**
	* @brief Get edge weight
	*
	* @param i vertex index
	* @param j vertex index
	* @return Edge weigth 
	*/
	double getW(int i, int j);

	/**
	* @brief Floyd-Warshall Algorithm
	*
	*/
	void floydWarshallShortestPath();

	/**
	* @brief Edge cost
	*
	* @param vOrigIndex origin vertex index
	* @param vDestIndex destination vertex index
	* @return Edge cost
	*/
	double edgeCost(int vOrigIndex, int vDestIndex);

	/**
	* @brief Get Floyd-Warshall Path
	*
	* @param origin origin vertex
	* @param dest destination vertex
	* @return Vector with vertexes in the path
	*/
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);

	/**
	* @brief Floyd-Warshall Path auxiliary  function
	*
	* @param index1 origin vertex index
	* @param index2 destination index
	* @param res destination Vector with vertexes
	*/
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);

	/**
	* @brief Swap two indices
	*
	* @param i vertex index
	* @param j vertex index
	*/
	void swap(int i, int j);
};


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge<T> >::iterator itAdj= v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje= v->adj.end();
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vD->indegree++;
	vS->addEdge(vD,w);

	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2)
		return false;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}

template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}



template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest){

	list<T> buffer;
	Vertex<T>* v = getVertex(dest);

	buffer.push_front(v->info);
	while ( v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if( v->path != NULL )
		buffer.push_front(v->path->info);


	vector<T> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	return res;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest){

	int originIndex = -1, destinationIndex = -1;

	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if(vertexSet[i]->info == origin)
			originIndex = i;
		if(vertexSet[i]->info == dest)
			destinationIndex = i;

		if(originIndex != -1 && destinationIndex != -1)
			break;
	}


	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if(W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if(P[originIndex][destinationIndex] != -1)
	{
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex,destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);


	return res;
}



template<class T>
void Graph<T>::getfloydWarshallPathAux(int index1, int index2, vector<T> & res)
{
	if(P[index1][index2] != -1)
	{
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2],index2, res);
	}
}


template<class T>
double Graph<T>::edgeCost(int vOrigIndex, int vDestIndex)
{
	if(vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for(unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++)
	{
		if(vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_INFINITY;
}


template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new double * [vertexSet.size()];
	P = new int * [vertexSet.size()];
	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		W[i] = new double[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for(unsigned int j = 0; j < vertexSet.size(); j++)
		{
			W[i][j] = edgeCost(i,j);
			P[i][j] = -1;
		}
	}


	for(unsigned int k = 0; k < vertexSet.size(); k++)
		for(unsigned int i = 0; i < vertexSet.size(); i++)
			for(unsigned int j = 0; j < vertexSet.size(); j++)
			{
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem convém considerar essa soma
				if(W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				double val = min ( W[i][j], W[i][k]+W[k][j] );
				if(val != W[i][j])
				{
					W[i][j] = val;
					P[i][j] = k;
				}
			}
}
/*
nedds to be a city graph or the type has to have the methods getTimeInHours() and getPleasure()
*/
template <class T>
void Graph<T>::knapsack(unsigned int maxTime){
		T src = vertexSet[0]->getInfo();
		if (maxTime == 0){
			return;
		}
		totalP = new int*[getNumVertex() + 1];
		for (int i = 0; i < getNumVertex() + 1; ++i)
			totalP[i] = new int[maxTime + 1];


		for (size_t j = 0; j <= maxTime; j++)
			totalP[0][j] = 0;


		for (size_t i = 1; i <= vertexSet.size(); i++){
			for (size_t j = 0; j <= maxTime; j++){
				if (!(src == vertexSet[i - 1]->getInfo()) && vertexSet[i - 1]->getInfo().getTimeInHours() < (double)j){
					int index = (j - round(vertexSet[i - 1]->getInfo().getTimeInHours()));
					int pleasure = vertexSet[i - 1]->getInfo().getPleasure() + totalP[i - 1][index];
					if (totalP[i - 1][j] >= pleasure)
						totalP[i][j] = totalP[i - 1][j];
					else
						totalP[i][j] = pleasure;
				}	
				else{
					totalP[i][j] = totalP[i - 1][j];
				}
			}
		}

}
template<class T>
vector<int> Graph<T>::getKnapsackSolution(unsigned int maxTime){
	vector<int> retorno;
	retorno.push_back(0);
	int i = getNumVertex();
	int k = maxTime;
	while (i > 0 && k > 0){
		if (totalP[i][k] != totalP[i - 1][k]){
			retorno.push_back(i-1);
			k -= round(vertexSet[i - 1]->getInfo().getTimeInHours());
			i--;
		}
		else
			i--;
	}

	retorno.push_back(0);
	return retorno;
}
template<class T>
void Graph<T>::rowReduction(double ** costP, double &bound){
	for(size_t i = 0; i < vertexSet.size(); i++){
		double rmin = INT_INFINITY;
		for (size_t j = 0; j < vertexSet.size(); j++){
			if (i != j && costP[i][j] < rmin){
				rmin = costP[i][j];
			}
		}
		for (size_t j = 0; j < vertexSet.size(); j++){
			if (costP[i][j] != INT_INFINITY)
				costP[i][j] -= rmin;
		}
		if (rmin != INT_INFINITY){
			bound += rmin;
		}
	}
}
template<class T>
void Graph<T>::columReduction(double ** costP, double &bound){
	for (size_t j = 0; j < vertexSet.size(); j++){
		double cmin = INT_INFINITY;
		for (size_t i = 0; i < vertexSet.size(); i++){
			if (i != j && costP[i][j] < cmin){
				cmin = costP[i][j];
			}
		}
		for (size_t i = 0; i < vertexSet.size(); i++){
			if (costP[i][j] != INT_INFINITY)
				costP[i][j] -= cmin;
		}
		if (cmin != INT_INFINITY){
			bound += cmin;
		}
	}
}
template<class T>
double Graph<T>::bb_aux(int src, int dst, string path, double ** cost2, double bound2){
	if (bound2 > totalCost){
		return INT_INFINITY;
	}
	double newBound = bound2;
	int choosen = -1;
	double ** costP = new double*[getNumVertex()];
	for (size_t i = 0; i < vertexSet.size(); i++){
		costP[i] = new double[getNumVertex()];
		for (size_t j = 0; j < vertexSet.size(); j++)
		{
			costP[i][j] = cost2[i][j];
		}
	}

	for (size_t i = 0; i < vertexSet.size(); i++){
		costP[src][i] = INT_INFINITY;
		costP[i][dst] = INT_INFINITY;
	}
	costP[dst][src] = INT_INFINITY;
	rowReduction(costP, newBound);
	columReduction(costP, newBound);
	for (size_t j = 0; j < vertexSet.size(); j++){
		if (costP[dst][j] != INT_INFINITY){
			newBound += costP[dst][j];
			double boundP = bb_aux(dst, j, path + to_string(j) + "-", costP, newBound);
			if (boundP <= newBound)
			{
				newBound = boundP;
				choosen = j;
			}
			newBound -= costP[dst][j];
		}
	}
	if (choosen == -1){
		if (path.size() == (getNumVertex() + 1) * 2 && newBound < totalCost){
			hamiltonPath = path;
			hamiltonPath.resize(hamiltonPath.size()-1);
			totalCost = newBound;
			cout << hamiltonPath << endl;
		}
	}
	return newBound;
}
template<class T>
void Graph<T>::BB_TSP(){
	cost = new double*[getNumVertex()];
	double bound = 0;
	totalCost = INT_INFINITY;
	
	string path;

	for (size_t i = 0; i < vertexSet.size(); i++){
		cost[i] = new double[getNumVertex()];
		for (size_t j = 0; j < vertexSet.size(); j++)
		{
			cost[i][j] = edgeCost(i, j);
			if (cost[i][j] == 0)
			{
				cost[i][j] = INT_INFINITY;
			}
		}
	}
	rowReduction(cost,bound);
	columReduction(cost,bound);
	path = to_string(0) + "-";
	double newBound;
	for (size_t j = 0; j < vertexSet.size(); j++)
	{
		if (cost[0][j] != INT_INFINITY){
			bound += cost[0][j];
			newBound = bb_aux(0, j, path + to_string(j) + "-", cost, bound);
			bound -= cost[0][j];
		}
	}
}
template<class T>
string Graph<T>::getHamiltonPath(){
	return hamiltonPath;
}
template<class T>
double Graph<T>::getTotalCost(){
	return totalCost;
}
template<class T>
double Graph<T>::getCityTime(const vector<int> &city){
	double total = 0;
	for (size_t i = 0; i < city.size(); i++)
	{
		total += vertexSet[city[i]]->getInfo().getTimeInHours();
	}
	return total;
}
template<class T>
double Graph<T>::getW(int i, int j){
	return W[i][j];
}
template<class T>
void Graph<T>::swap(int i, int j){
	Vertex<T> * v1= vertexSet[i];
	vertexSet[i] = vertexSet[j];
	vertexSet[j] = v1;
}

/** @} */

#endif /* GRAPH_H_ */
