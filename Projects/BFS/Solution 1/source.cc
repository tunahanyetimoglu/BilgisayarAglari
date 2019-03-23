#include <string.h>
#include <mesaj_m.h>
#include <omnetpp.h>

using namespace omnetpp;


class RBFS : public cSimpleModule
{
private:
    double my_cost;                         // her düðümün ulaþýlma maaliyetini kendisinde tutmak için
    bool parent;                            // parent var mý yok mu ? deðiþkeni
    std::vector< cGate* > children;         // çocuklarýn tutulduðu vector
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
   //     dispStr.parse("p=40,20;i=abstract/opticalrouter;i2=status/disconnect");  // Root düðümü belirginleþtirmek için görünüþünü deðiþtir
        my_cost = 0;                                                             // Root düðümün kendine maaliyeti 0 olduðu için maliyetini 0 yap
        parent = true;
        scheduleAt(0.0, sendMessage("layer", 0));                               // mesajý ve maliyeti gönder
    }
}
void RBFS::handleMessage(cMessage *msg){

    LayerMSG *layerMessage = check_and_cast<LayerMSG *>(msg);                                 // cMessage check et
    double message_cost = layerMessage->getCost();                                            // mesajýn maliyetini al
    int type = layerMessage->getType();                                                           // mesajýn tipini al // 0 layer 1 ack -1 reject
    switch(type){
        case (0):
            if(layerMessage->getArrivalGateId() != -1){
                int index = layerMessage->getArrivalGate()->getIndex();
                cDelayChannel * channel = check_and_cast<cDelayChannel*>(gate("gate$o",index)->getChannel()); // Mesajýn yol aldýðý kanalý al
                double channel_cost = channel->par("cost");                                           // Kanalýn üstündeki delayý al
                double total_cost = channel_cost + message_cost;                                            // Mesajýn geçtiði kanalýn delayý ile mesajýn çýktýðý noda gelene kadar yollarýn delayýný topla
                if(my_cost > total_cost && parent == false){                                   // bir düðüm layer mesajý aldýðýnda gelen mesajýn maliyeti daha az mý diye kontrol et
                    parent = true;
                    my_cost = total_cost;                                                      // az ise düðüm layer bilgisini güncelle
                    send(sendMessage("Ack", my_cost),"gate$o",index);               // yeni düðüme mesaj bas

                    for(int i = 0; i < this->gateCount() / 2; i ++){
                        if(layerMessage->arrivedOn("gate$i",i)) { continue ;}
                        send(sendMessage("layer(l+1)", my_cost),"gate$o",i);      // Komþulara yeni layer bilgisini ilet
                    }
               }else{
                    send(sendMessage("Reject", 0),"gate$o",index);                       // parenti varsa ve yeni gelen layer mesajý daha az masraflý deðilse reject mesajý gönder
                }
            }else{
                    for(int i = 0; i < this->gateCount() / 2; i ++){
                    if(layerMessage->arrivedOn("gate$i",i)) { continue ;}
                    send(sendMessage("layer", 0),"gate$o",i);
                    }
             }
            break;
        case (1):
            children.push_back(msg->getArrivalGate()->getPreviousGate());  // ack mesajý gönderen düðüme child olarak ekle
            EV << getName() << "'s children : ";
            for(int i = 0 ; i < children.size(); i ++){
                EV << children.at(i)->getOwner()->getFullName() << ",";
            }
            EV << "\n";
            break;
        case (-1):
            cDisplayString& arrivalDispStr = gate("gate$o", layerMessage->getArrivalGate()->getIndex())->getDisplayString();  // gelen mesaj reject ise aradý baðlantýyý al
            arrivalDispStr.parse("ls=,0");                                                                            // baðlantý sil ( daha doðrusu simülasyonda görünmez yapýyor )
            break;
    }
    delete layerMessage;
}

LayerMSG *RBFS::sendMessage(const char *name,double cost)
{
    LayerMSG *msg = new LayerMSG(name);            // layer paketinden mesaj üret

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

