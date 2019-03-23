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
    if(getIndex() == 1) { // getIndex == ROOT_Index ( Root olmas� istenen d���m�n index de�erini girin)

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
        if(lmsg->getArrivalGateId() != -1){                                                 // Mesaj�n Root D���mden mi geldi�ine bak
            int index = msg->getArrivalGate()->getIndex();                                  // Mesaj�n Ula�t��� Gate'in indexisin al
            cDelayChannel * channel = check_and_cast<cDelayChannel*>(gate("gate$o",index)->getChannel()); // Mesaj�n yol ald��� kanal� al
            delay = channel->getDelay().dbl();                                               // Kanal�n �st�ndeki delay� al
            double layer = delay + previousDelay;                                            // Mesaj�n ge�ti�i kanal�n delay� ile mesaj�n ��kt��� noda gelene kadar yollar�n delay�n� topla

            if(par("my_layer").doubleValue() > layer && parent == false){                                   // bir d���m layer mesaj� ald���nda gelen mesaj�n maliyeti daha az m� diye kontrol et
                parent = true;
                par("my_layer") = layer;                                                      // az ise d���m layer bilgisini g�ncelle
                send(generateMessage("Ack", 1, par("my_layer")),"gate$o",index);               // yeni d���me mesaj bas

                for(int i = 0; i < this->gateCount() / 2; i ++){
                    if(lmsg->arrivedOn("gate$i",i)) { continue ;}
                    send(generateMessage("new_layer", 2, par("my_layer")),"gate$o",i);      // Kom�ulara yeni layer bilgisini ilet
                }
            }
            else{
                send(generateMessage("Reject", 0, 0),"gate$o",index);                       // parenti varsa ve yeni gelen layer mesaj� daha az masrafl� de�ilse reject mesaj� g�nder
            }
        }else{
            for(int i = 0; i < this->gateCount() / 2; i ++){
                if(lmsg->arrivedOn("gate$i",i)) { continue ;}
                send(generateMessage("layer", 2, 0),"gate$o",i);
            }
        }
    }else if (strcmp(msg->getName(),"Ack") == 0){                                               // mesaj ack ise
            children.push_back(msg->getArrivalGate()->getPreviousGate()->getOwner()->getFullName());  // ack mesaj� g�nderen d���me child olarak ekle
            EV << getFullName() << "'s children : ";
            for(int i = 0 ; i < children.size(); i ++){
                EV << children.at(i) << ",";
            }
            EV << "\n";
    }else{
        cDisplayString& arrivalDispStr = gate("gate$o", lmsg->getArrivalGate()->getIndex())->getDisplayString();  // gelen mesaj reject ise arad� ba�lant�y� al
        arrivalDispStr.parse("ls=,0");                                                                            // ba�lant� sil ( daha do�rusu sim�lasyonda g�r�nmez yap�yor )
    }
}

layerM *Random::generateMessage(const char *name,short int kind,double delay)
{
    layerM *msg = new layerM(name,kind);            // layer paketinden mesaj �ret

    if(strcmp(name, "layer") == 0){
        msg->setDelay(delay);                       // bu metodla �retilen mesaja verilen delay s�resini ata
    }else if(strcmp(name, "new_layer") == 0){
        msg->setDelay(delay);
    }
    return msg;
}

