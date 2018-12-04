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

class testComputer : public cSimpleModule{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(testComputer);

void testComputer :: initialize(){

    std::vector<std::string> nedTypes;
    nedTypes.push_back("testComputer");
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
    EV << "Node : " << getName() << "       -   Weight : " << sourceNode->getWeight() << "\n";
    if (strcmp("computer", getName()) == 0){
        
        cTopology::Node *sourceNode = topo->getNodeFor(this);
        sourceNode->disable();
           
        cTopology::Node *destNode = topo->getNode(atoi(DEST_NODE));
        sourceNode->enable();
        topo->calculateWeightedSingleShortestPathsTo(destNode);
            
        cGate *c = sourceNode->getPath(0)->getLocalGate();
                   char msgname[20];
                    sprintf(msgname, "Node : -%d", getIndex());
                    cMessage *msg = new cMessage(msgname);
                   send(msg,c);
        }
}
void testComputer::handleMessage(cMessage *msg)
{
        std::vector<std::string> nedTypes;
        nedTypes.push_back("testComputer");

        //Create cTopology Object
        cTopology *topo = new cTopology("topo");

        topo->extractByNedTypeName(nedTypes);
        
        cTopology::Node *sourceNode = topo->getNodeFor(this);
        sourceNode->disable();

        cTopology::Node *destNode = topo->getNode(atoi(DEST_NODE));
        sourceNode->enable();

        topo->calculateWeightedSingleShortestPathsTo(destNode);

        if(sourceNode->getNumPaths() != 0){
            cGate *c = sourceNode->getPath(0)->getLocalGate();
            simtime_t eed = simTime() - msg->getCreationTime();

            send(msg,c);
        }
}
