// $Id: Graph.h 55034 2004-01-01 21:01:01Z shuston $

#ifndef GRAPH_H
#define GRAPH_H

#include "Graphable_Element.h"

class Graph
  {
  public:
    Graph()
    {
    }

    void graph( char * filename, Graphable_Element_List & data );
  };

#endif /* GRAPH_H */
