/*
 * source.cc
 *
 *  Created on: 26 Kas 2018
 *      Author: tuhanan
 */

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

#define DEST_NODE "45"
#define SOURCE_NODE 27

using namespace omnetpp;

class Computer : public cSimpleModule{
    private:
        double weight ;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Computer);

void Computer :: initialize(){
    //an STL string vector
    std::vector<std::string> nedTypes;
    nedTypes.push_back("Computer");
    cTopology *topo = new cTopology("topo");
    // Extracting the topology from a network.
    //Extracts model topology by the fully qualified NED type name of the modules.
    //All modules whose getNedTypeName() is listed in the given string vector will get included.
    topo->extractByNedTypeName(nedTypes);
    cTopology::Node *node = topo->getNodeFor(this);
    weight =  intuniform(0, 10000);
    node->setWeight(weight);
    EV <<"\n Index : " << getIndex() << " - weigt : " << node->getWeight() << "\n";
    if(getIndex() == SOURCE_NODE){
        //Returns the graph node which corresponds to the given module in the network.
        //If no graph node corresponds to the module, the method returns NULL.
        //This method assumes that the topology corresponds to the network, that is, it was probably created with one of the extract...() functions.
        cTopology::Node *sourceNode = topo->getNodeFor(this);

        //Returns pointer to the ith node in the graph.
        //Node's methods can be used to further examine the node's connectivity, etc.
        cTopology::Node *destNode = topo->getNode(atoi(DEST_NODE));

        //Apply the Dijkstra algorithm to find all shortest paths to the given graph node.
        //The paths found can be extracted via Node's methods.
        //topo->calculateUnweightedSingleShortestPathsTo(destNode);


        //Apply the Dijkstra algorithm to find all shortest paths to the given graph node.
        //The paths found can be extracted via Node's methods.     !--- Uses weights in nodes and links. ---!
        topo->calculateWeightedSingleShortestPathsTo(destNode);

        cGate *c = sourceNode->getPath(0)->getLocalGate();      // getLocalGate:  returns  the gates at the local  end of this connection
        char msgname[20];
        sprintf(msgname, "Node : -%d", getIndex());
        cMessage *msg = new cMessage(msgname);
        send(msg,c);
    }
}
void Computer::handleMessage(cMessage *msg)
{
        std::vector<std::string> nedTypes;
        nedTypes.push_back("Computer");

        //Create cTopology Object
        cTopology *topo = new cTopology("topo");

        // Extracting the topology from a network.
        //Extracts model topology by the fully qualified NED type name of the modules.
        //All modules whose getNedTypeName() is listed in the given string vector will get included.
        topo->extractByNedTypeName(nedTypes);

        //Returns the graph node which corresponds to the given module in the network.
        //If no graph node corresponds to the module, the method returns NULL.
        //This method assumes that the topology corresponds to the network, that is, it was probably created with one of the extract...() functions.
        cTopology::Node *sourceNode = topo->getNodeFor(this);


        //Returns pointer to the ith node in the graph.
        //Node's methods can be used to further examine the node's connectivity, etc.
        cTopology::Node *destNode = topo->getNode(atoi(DEST_NODE));

        //Apply the Dijkstra algorithm to find all shortest paths to the given graph node.
        //The paths found can be extracted via Node's methods.
        //topo->calculateUnweightedSingleShortestPathsTo(destNode);

        //Apply the Dijkstra algorithm to find all shortest paths to the given graph node.
        //The paths found can be extracted via Node's methods.     !--- Uses weights in nodes and links. ---!
        topo->calculateWeightedSingleShortestPathsTo(destNode);

        if(sourceNode->getNumPaths() != 0){
            cGate *c = sourceNode->getPath(0)->getLocalGate();
            send(msg,c);
        }
}


