#ifndef _GRAPHCOLOR_H
#define _GRAPHCOLOR_H

#include "Module.decl.h" 

/*readonly*/ 
extern CProxy_Main mainProxy;
extern AdjListType adjList_;
extern int vertices_;
extern int chromaticNum_;

class Main : public CBase_Main {
  private:
    std::string filename, newGraph;
  
  public:
    Main(CkArgMsg* msg);
    Main(CkMigrateMessage* msg);

    void parseCommandLine(int argc, char **argv);
    void readDataFromPython(int argc, char **argv);
    
    void done();
    void populateInitialState(std::vector<vertex>&);
};

class Node: public CBase_Node {
  Node_SDAG_CODE

  private:
    std::vector<vertex> node_state_;
    bool is_root_;
    CProxy_Node parent_;
    int uncolored_num_;//number of uncolored vertex
    int child_num_;
    int child_finished_;

  public:
    // default constructor creats root node
    Node(bool isRoot, int n, CProxy_Node parent);
    Node(std::vector<vertex> state, bool isRoot,
            int n, CProxy_Node parent);
    Node (CkMigrateMessage*);
    // ?? what this used for
    void testGraph(std::vector<vertex>& );
    // return the most constrained vertex id/index in vector
    int getNextConstraintVertex();
    // update a passed in state
    // by coloring vertex[vIndex] with color c
    void updateState(std::vector<vertex> & state, int vIndex, int c);
    // print out graph colored states
    void printGraph();
    // color the remaining part of graph locally
    // return succeed or not
    bool colorLocally();
};


#endif
