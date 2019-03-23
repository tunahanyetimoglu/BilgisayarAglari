#include <string.h>
#include <mesaj_m.h>
#include <omnetpp.h>

using namespace omnetpp;


class RBFS : public cSimpleModule
{
private:
    double my_cost;                         // her d���m�n ula��lma maaliyetini kendisinde tutmak i�in
    bool parent;                            // parent var m� yok mu ? de�i�keni
    std::vector< cGate* > children;         // �ocuklar�n tutuldu�u vector
protected:
    virtual LayerMSG  *sendMessage(const char *name,double cost);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(RBFS);

void RBFS::initialize(){
    parent = false;
    my_cost = 9999999999999;
    if(getIndex() == 0){
        cDisplayString& dispStr = getDisplayString();
   //     dispStr.parse("p=40,20;i=abstract/opticalrouter;i2=status/disconnect");  // Root d���m� belirginle�tirmek i�in g�r�n���n� de�i�tir
        my_cost = 0;                                                             // Root d���m�n kendine maaliyeti 0 oldu�u i�in maliyetini 0 yap
        parent = true;
        scheduleAt(0.0, sendMessage("layer", 0));                               // mesaj� ve maliyeti g�nder
    }
}
void RBFS::handleMessage(cMessage *msg){

    LayerMSG *layerMessage = check_and_cast<LayerMSG *>(msg);                                 // cMessage check et
    double message_cost = layerMessage->getCost();                                            // mesaj�n maliyetini al
    int type = layerMessage->getType();                                                           // mesaj�n tipini al // 0 layer 1 ack -1 reject
    switch(type){
        case (0):
            if(layerMessage->getArrivalGateId() != -1){
                int index = layerMessage->getArrivalGate()->getIndex();
                cDelayChannel * channel = check_and_cast<cDelayChannel*>(gate("gate$o",index)->getChannel()); // Mesaj�n yol ald��� kanal� al
                double channel_cost = channel->par("cost");                                           // Kanal�n �st�ndeki delay� al
                double total_cost = channel_cost + message_cost;                                            // Mesaj�n ge�ti�i kanal�n delay� ile mesaj�n ��kt��� noda gelene kadar yollar�n delay�n� topla
                if(my_cost > total_cost && parent == false){                                   // bir d���m layer mesaj� ald���nda gelen mesaj�n maliyeti daha az m� diye kontrol et
                    parent = true;
                    my_cost = total_cost;                                                      // az ise d���m layer bilgisini g�ncelle
                    send(sendMessage("Ack", my_cost),"gate$o",index);               // yeni d���me mesaj bas

                    for(int i = 0; i < this->gateCount() / 2; i ++){
                        if(layerMessage->arrivedOn("gate$i",i)) { continue ;}
                        send(sendMessage("layer(l+1)", my_cost),"gate$o",i);      // Kom�ulara yeni layer bilgisini ilet
                    }
               }else{
                    send(sendMessage("Reject", 0),"gate$o",index);                       // parenti varsa ve yeni gelen layer mesaj� daha az masrafl� de�ilse reject mesaj� g�nder
                }
            }else{
                    for(int i = 0; i < this->gateCount() / 2; i ++){
                    if(layerMessage->arrivedOn("gate$i",i)) { continue ;}
                    send(sendMessage("layer", 0),"gate$o",i);
                    }
             }
            break;
        case (1):
            children.push_back(msg->getArrivalGate()->getPreviousGate());  // ack mesaj� g�nderen d���me child olarak ekle
            EV << getName() << "'s children : ";
            for(int i = 0 ; i < children.size(); i ++){
                EV << children.at(i)->getOwner()->getFullName() << ",";
            }
            EV << "\n";
            break;
        case (-1):
            cDisplayString& arrivalDispStr = gate("gate$o", layerMessage->getArrivalGate()->getIndex())->getDisplayString();  // gelen mesaj reject ise arad� ba�lant�y� al
            arrivalDispStr.parse("ls=,0");                                                                            // ba�lant� sil ( daha do�rusu sim�lasyonda g�r�nmez yap�yor )
            break;
    }
    delete layerMessage;
}

LayerMSG *RBFS::sendMessage(const char *name,double cost)
{
    LayerMSG *msg = new LayerMSG(name);            // layer paketinden mesaj �ret

    if((strcmp(name, "layer") == 0) || (strcmp(name, "layer(l+1)") == 0)){
        msg->setCost(cost);
        msg->setType(0);
    }else if(strcmp(name, "Ack") == 0){
        msg->setType(1);
    }else{
        msg->setType(-1);
    }
    return msg;
}

