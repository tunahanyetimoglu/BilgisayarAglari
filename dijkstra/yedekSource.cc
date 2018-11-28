/*
 * source.cc
 *
 *  Created on: 26 Kas 2018
 *      Author: tuhanan
 */

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

#define DEST_NODE "4"

using namespace omnetpp;

class yedekComputer : public cSimpleModule{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(yedekComputer);

void yedekComputer :: initialize(){

                    std::vector<std::string> nedTypes;
                      nedTypes.push_back("yedekComputer");
                      cTopology *topo = new cTopology("topo");
                      topo->extractByNedTypeName(nedTypes);
                      for(int i=0;i<4;i++){
                           cTopology::Node *node = topo->getNode(i);
                           if(i == 0) {
                               node->setWeight(5);
                           }else if(i == 1){
                               node->setWeight(1);
                           }else if(i == 2){
                               node->setWeight(30);
                           }else if(i == 3){
                               node->setWeight(1);
                           }else{
                               node-> setWeight(10);
                           }
                      }
                           if (strcmp("computer", getName()) == 0) {
    //if(getIndex() == 0){


                   // Extracting the topology from a network.
                   //Extracts model topology by the fully qualified NED type name of the modules.
                   //All modules whose getNedTypeName() is listed in the given string vector will get included.
                   //Returns the graph node which corresponds to the given module in the network.
                   //If no graph node corresponds to the module, the method returns NULL.
                   //This method assumes that the topology corresponds to the network, that is, it was probably created with one of the extract...() functions.
                   cTopology::Node *sourceNode = topo->getNodeFor(this);
                   sourceNode->disable();

                   //Returns pointer to the ith node in the graph.
                   //Node's methods can be used to further examine the node's connectivity, etc.
                   cTopology::Node *destNode = topo->getNode(atoi(DEST_NODE));
                   sourceNode->enable();
                   //Apply the Dijkstra algorithm to find all shortest paths to the given graph node.
                   //The paths found can be extracted via Node's methods.
                   //topo->calculateUnweightedSingleShortestPathsTo(destNode);


                   //Apply the Dijkstra algorithm to find all shortest paths to the given graph node.
                   //The paths found can be extracted via Node's methods.     !--- Uses weights in nodes and links. ---!
                   topo->calculateWeightedSingleShortestPathsTo(destNode);

                   cGate *c = sourceNode->getPath(0)->getLocalGate();
                   char msgname[20];
                    sprintf(msgname, "Node : -%d", getIndex());
                    cMessage *msg = new cMessage(msgname);
                   send(msg,c);
        }
}
void yedekComputer::handleMessage(cMessage *msg)
{
        std::vector<std::string> nedTypes;
        nedTypes.push_back("yedekComputer");

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
        sourceNode->disable();

        //Returns pointer to the ith node in the graph.
        //Node's methods can be used to further examine the node's connectivity, etc.
        cTopology::Node *destNode = topo->getNode(atoi(DEST_NODE));
        sourceNode->enable();

        //Apply the Dijkstra algorithm to find all shortest paths to the given graph node.
        //The paths found can be extracted via Node's methods.
        //topo->calculateUnweightedSingleShortestPathsTo(destNode);

        //Apply the Dijkstra algorithm to find all shortest paths to the given graph node.
        //The paths found can be extracted via Node's methods.     !--- Uses weights in nodes and links. ---!
        topo->calculateWeightedSingleShortestPathsTo(destNode);



        if(sourceNode->getNumPaths() != 0){
            cGate *c = sourceNode->getPath(0)->getLocalGate();
            simtime_t eed = simTime() - msg->getCreationTime();

            send(msg,c);
        }
}


