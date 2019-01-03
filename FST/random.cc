#include <string.h>
#include <omnetpp.h>

#define ROOT "node23"
#define  GATENAME "g$o"
#define GATENAME_i "g$i"

#define PROBE new cMessage("Probe",1)
#define ACK new cMessage("Ack",2)
#define REJECT new cMessage("Reject")

#define PROBECODE 1
#define ACKCODE 2
#define REJECTCODE 0

using namespace omnetpp;

class Node : public cSimpleModule
{
private:

    bool hasParent;
    int gateIndex;
    int gateId;
    int messageCode;
    std::vector<std::string> children;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Node);


void Node::initialize()
{
    hasParent = false;
    if (strcmp(ROOT,getName()) == 0) {
        hasParent = true;
        //this->setName("ROOT");
        scheduleAt(0.0, PROBE);
    }
}
void Node::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(), "Probe") == 0){
            gateId =  msg->getArrivalGateId();
            if( gateId != -1){
                gateIndex = msg->getArrivalGate()->getIndex();
                if(hasParent == false){
                    hasParent = true;
                    send(ACK, GATENAME, gateIndex);
                    cDisplayString& arrivalDispStr = gate(GATENAME, gateIndex)->getDisplayString();
                    arrivalDispStr.parse("ls=red,3");

                    for(int i = 0; i < this->gateCount() / 2; i++){
                            if(msg->arrivedOn(GATENAME_i, i)){continue;}
                            send(PROBE, GATENAME, i);
                    }
                }else{
                    send(REJECT, GATENAME, gateIndex);
                }
            }else{

                for(int i = 0; i < this->gateCount() / 2; i++){
                        if(msg->arrivedOn(GATENAME_i, i)){continue;}
                        send(PROBE,GATENAME, i);
                }
            }
        }else if(strcmp(msg->getName(), "Ack") == 0){
            children.push_back(msg->getArrivalGate()->getPreviousGate()->getOwner()->getName());
            cDisplayString& arrivalDispStr = gate(GATENAME, msg->getArrivalGate()->getIndex())->getDisplayString();
            arrivalDispStr.parse("ls=blue,5");

            EV << getName() << "'s childs: ";
            for(int i = 0; i < children.size(); i++){
                EV << children.at(i) << " , ";
            }
            EV << "\n";
        }else if(strcmp(msg->getName(), "Reject") == 0){
            cDisplayString& arrivalDispStr = gate(GATENAME, msg->getArrivalGate()->getIndex())->getDisplayString();
            arrivalDispStr.parse("ls=,0");
        }
        delete msg;
}

