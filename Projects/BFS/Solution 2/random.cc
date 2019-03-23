/*
 * test.cc
 *
 *  Created on: 16 Oca 2019
 *      Author: tuhanan
 */

#include <string.h>
#include <message_m.h>
#include <omnetpp.h>

using namespace omnetpp;

class Random : public cSimpleModule
{
private:
    double delay;
    double time;
    bool parent;
    std::vector<std::string> children;
protected:
    virtual layerM  *generateMessage(const char *name,short int kind,double delay);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Random);

void Random::initialize(){
    parent = false;
    if(getIndex() == 1) { // getIndex == ROOT_Index ( Root olmasý istenen düðümün index deðerini girin)

        setName("Root");
        par("my_layer") = 0.0;     // Rootun layer = 0
        parent = true;
        scheduleAt(0.0, generateMessage("layer", 2, 0));
    }
}
void Random::handleMessage(cMessage *msg){

    layerM *lmsg = check_and_cast<layerM *>(msg);     // cMessage check et
    double previousDelay = lmsg->getDelay();   //

    if(strcmp(lmsg->getName(),"layer") == 0 || strcmp(lmsg->getName(), "new_layer") == 0){  // Mesaj layer(l) ve ya layer(l+1) mi diye bak
        if(lmsg->getArrivalGateId() != -1){                                                 // Mesajýn Root Düðümden mi geldiðine bak
            int index = msg->getArrivalGate()->getIndex();                                  // Mesajýn Ulaþtýðý Gate'in indexisin al
            cDelayChannel * channel = check_and_cast<cDelayChannel*>(gate("gate$o",index)->getChannel()); // Mesajýn yol aldýðý kanalý al
            delay = channel->getDelay().dbl();                                               // Kanalýn üstündeki delayý al
            double layer = delay + previousDelay;                                            // Mesajýn geçtiði kanalýn delayý ile mesajýn çýktýðý noda gelene kadar yollarýn delayýný topla

            if(par("my_layer").doubleValue() > layer && parent == false){                                   // bir düðüm layer mesajý aldýðýnda gelen mesajýn maliyeti daha az mý diye kontrol et
                parent = true;
                par("my_layer") = layer;                                                      // az ise düðüm layer bilgisini güncelle
                send(generateMessage("Ack", 1, par("my_layer")),"gate$o",index);               // yeni düðüme mesaj bas

                for(int i = 0; i < this->gateCount() / 2; i ++){
                    if(lmsg->arrivedOn("gate$i",i)) { continue ;}
                    send(generateMessage("new_layer", 2, par("my_layer")),"gate$o",i);      // Komþulara yeni layer bilgisini ilet
                }
            }
            else{
                send(generateMessage("Reject", 0, 0),"gate$o",index);                       // parenti varsa ve yeni gelen layer mesajý daha az masraflý deðilse reject mesajý gönder
            }
        }else{
            for(int i = 0; i < this->gateCount() / 2; i ++){
                if(lmsg->arrivedOn("gate$i",i)) { continue ;}
                send(generateMessage("layer", 2, 0),"gate$o",i);
            }
        }
    }else if (strcmp(msg->getName(),"Ack") == 0){                                               // mesaj ack ise
            children.push_back(msg->getArrivalGate()->getPreviousGate()->getOwner()->getFullName());  // ack mesajý gönderen düðüme child olarak ekle
            EV << getFullName() << "'s children : ";
            for(int i = 0 ; i < children.size(); i ++){
                EV << children.at(i) << ",";
            }
            EV << "\n";
    }else{
        cDisplayString& arrivalDispStr = gate("gate$o", lmsg->getArrivalGate()->getIndex())->getDisplayString();  // gelen mesaj reject ise aradý baðlantýyý al
        arrivalDispStr.parse("ls=,0");                                                                            // baðlantý sil ( daha doðrusu simülasyonda görünmez yapýyor )
    }
}

layerM *Random::generateMessage(const char *name,short int kind,double delay)
{
    layerM *msg = new layerM(name,kind);            // layer paketinden mesaj üret

    if(strcmp(name, "layer") == 0){
        msg->setDelay(delay);                       // bu metodla üretilen mesaja verilen delay süresini ata
    }else if(strcmp(name, "new_layer") == 0){
        msg->setDelay(delay);
    }
    return msg;
}

