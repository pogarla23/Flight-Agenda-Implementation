#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <climits>
#include <queue>
#include <sstream>

/*
Algorithm 
    If you start at a certain vertex to find the shortest path each line has a certain value.


    initially every vertex is infinity 
    you select the shortest path vertex 
    
    once selected, check whether that current 
    vertex if there is any other shortest path

    there is a shortest path of one vertex to another
    then it will udpate the shortest path to
    

    Consider a single edge path
    1. From current vertex, label the value of other vertexes from their edge distance
        - INITIALLY/from beginning if the current doesn't have a direct (one to one) path with another vertex, label as infinity 

    2. Select the shortest path of the current 
    vertex to it's neighbor, make neighbor current

    3. perform relaxation (some can relax or not)

    4. repeat from step 2


    relaxation
    - check what neighbors are connected that have not been assigned as current (or parent of)

    - if distance of vertex current(value of vertex) to the cost distance from current to v < distance of vertex v

    - distance/value of v = distance/value of u + cost distance from current to v  

    - Note: even if the neighbor has been modified to a finite number, it still needs to be modified from the conditions in relaxation

    
*/
using namespace std;

class Edge;

class Vertex {
public:
    string code; //name of airport
    int dvalue; //value at vertex 
    Edge* parentedge;  //it's previous edge
    vector<Edge*> adjlist; //the neighbor edges
    Vertex(string code) : code(code), dvalue(INT_MAX), parentedge(nullptr) {} 
};

class Edge {
public:
    int depttime, arrtime;
    Vertex* origin; //what we start from 
    Vertex* dest; //where we end
    string airline, flno;

    Edge(const string& airline, const string& flno, Vertex* origin, Vertex* dest, int depttime, int arrtime)
        : airline(airline), flno(flno), origin(origin), dest(dest), depttime(depttime), arrtime(arrtime) {}
};

class CompareVertices {
public:
    bool operator()(const Vertex* v1, const Vertex* v2) {
        return v1->dvalue > v2->dvalue; // Min-heap based on dvalue
    }
};

class Graph {
public:
    map<string, Vertex*> vmap;
    vector<Edge*> elist;
    priority_queue<Vertex*, vector<Vertex*>, CompareVertices> heap;

    void readAirports(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            exit(EXIT_FAILURE);
        }

        string line;
        while (getline(file, line)) {
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line.empty()) 
                continue;

            Vertex* v = new Vertex(line);
            vmap[line] = v;
        }

        file.close(); 
    }

    void readFlights(const string& filename) {
        
        ifstream file(filename);
        if (!file.is_open()) {
            
            exit(EXIT_FAILURE);
        }

        string line;
        getline(file, line);
        while (getline(file, line)) {
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line.empty()) 
                continue;

            istringstream iss(line);
            string airline, flno, originCode, destCode;
            int depttime, arrtime;

            if (!(iss >> airline >> flno >> originCode >> destCode >> depttime >> arrtime)) {
                continue;
            }

            if (vmap.find(originCode) == vmap.end() || vmap.find(destCode) == vmap.end()) {
                continue;
            }

            Vertex* origin = vmap[originCode];
            Vertex* dest = vmap[destCode];
            Edge* e = new Edge(airline, flno, origin, dest, depttime, arrtime);
            elist.push_back(e);
            origin->adjlist.push_back(e);
        }

        file.close(); 
        
    }

    int dijkstra(const string& srcCode, const string& sinkCode, int starttime) {
  
        for (auto& it: vmap){ //changes all the new d values as 0
            it.second->dvalue= INT_MAX;
    
        }

        Vertex* v= vmap[srcCode]; //takes current
        
        v->dvalue = starttime; //assigns to start time
        heap.push(v); //into priority queue


        
        while (!heap.empty()){  //while the priority queue isn't empty
            
            Vertex* current = heap.top(); //takes top of current
            cout<<"current flight"<<current->code<<endl;
            heap.pop();  //pops it

            for (Edge* e : current->adjlist) {  //goes to each edge
                relax(e); 
            }  
        }
        return vmap[sinkCode]->parentedge->arrtime; //return
        
    }


    void decreaseKey(Vertex* v, int key) { //modify if in relax met condition
        
        v->dvalue = key; 
        heap.push(v); 
        return; 
        
    }


    void relax(Edge* e) {
        Vertex* u = e->origin; 
        Vertex* v = e->dest; 
       
       
        if ((v->dvalue > e->arrtime) && (u->dvalue <= e->depttime)){  //uses the compare func for object overload 
            v->dvalue = e->arrtime; 
            v->parentedge = e;
            decreaseKey(v, v->dvalue); 
        }
        return; 
    }

    void printPath(const string& code) {
        Edge* e = vmap[code]->parentedge;
        if (!e) return;
        
    }
};
int main(int argc, char* argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }

    string airportsFile = "airports.txt";
    string flightsFile = "flights.txt";

    Graph graph;
    graph.readAirports(airportsFile);
    graph.readFlights(flightsFile);

    int startTime = stoi(argv[3]);
    int shortestPath = graph.dijkstra(argv[1], argv[2], startTime);
    cout << shortestPath << endl;

    return 0;
}
