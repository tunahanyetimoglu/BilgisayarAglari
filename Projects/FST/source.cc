#include "MainHeader.h"


class Node : public cSimpleModule
{
private:
    std::vector<std::string> children;
protected:
    virtual Message *generateMessage(const char *name,short int kind);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

};

int gIndex,gId,mCode;

Define_Module(Node);

void Node::initialize()
{
    if (getIndex() == ROOT_INT) {
        par("hasParent") = true;
        Message *msg = generateMessage("Probe", 2);
        scheduleAt(0.0, msg);
    }
}

void Node::handleMessage(cMessage *msg)
{
    Message *mmsg = check_and_cast<Message *>(msg);
    mCode = mmsg->getMessageCode();
    if(mCode == 0){
        cDisplayString& arrivalDispStr = gate(GATENAME, mmsg->getArrivalGate()->getIndex())->getDisplayString();
        arrivalDispStr.parse("ls=,0");
    }
    else{
         switch(mCode){
             case (PROBECODE):
                     gId =  msg->getArrivalGateId();
                     if( gId != -1){
                         gIndex = msg->getArrivalGate()->getIndex();
                         if(par("hasParent").boolValue() == false){
                             par("hasParent") = true;
                             send(generateMessage("Ack", 1), GATENAME, gIndex);
                             cDisplayString& arrivalDispStr = gate(GATENAME, gIndex)->getDisplayString();
                             arrivalDispStr.parse("ls=green,3");

                             for(int i = 0; i < this->gateCount() / 2; i++){
                                 if(msg->arrivedOn(GATENAME_i, i)){continue;}
                                 send(generateMessage("Probe", 2), GATENAME, i);
                             }
                         }else{
                             send(generateMessage("Reject", 0), GATENAME, gIndex);
                         }
                     }else{
                         for(int i = 0; i < this->gateCount() / 2; i++){
                             if(msg->arrivedOn(GATENAME_i, i)){continue;}
                         send(generateMessage("Probe", 2),GATENAME, i);
                         }
                     }
                     break;
             case (ACKCODE):
                     children.push_back(msg->getArrivalGate()->getPreviousGate()->getOwner()->getFullName());
                     cDisplayString& arrivalDispStr = gate(GATENAME, msg->getArrivalGate()->getIndex())->getDisplayString();
                     arrivalDispStr.parse("ls=blue,5");

                     EV << getFullName() << "'s childs: ";
                     for(int i = 0; i < children.size(); i++){
                         EV << children.at(i) << " , ";
                     }
                     EV << endl;
                     break;
         }
    }
    delete mmsg;
}

Message *Node::generateMessage(const char *name,short int kind)
{
    Message *msg = new Message(name,kind);
    if(strcmp(name, "Probe") == 0){
        msg->setMessageCode(2);
    }else if(strcmp(name,"Ack") == 0){
        msg->setMessageCode(1);
    }else if(strcmp(name,"Reject") == 0){
        msg->setMessageCode(0);
    }
    return msg;
}

