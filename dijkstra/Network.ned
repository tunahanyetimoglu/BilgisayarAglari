


simple Computer
{
    parameters:
        @display("i=block/routing");
    gates:
        input i[];
        output o[];
}

network Network
{
    @display("bgb=3592.1213,1401.3888");
    types:
        channel Channel extends ned.DelayChannel
        {
            @backbone;
    		double cost = default(1);
    		double lenght = default(1);
        }
    submodules:
        node[50]: Computer;
    connections:
        for i=0..24 {
            node[i*2].o++ --> Channel {cost = i+1; lenght = i + 2;}  --> node[i+2].i++;
        }
        for i=0..10 {
            node[i*4].o++ --> Channel {cost = i+1; lenght = i * 2;}  --> node[i].i++;
        }
        for i=0..15 {
            node[i*3].o++ --> Channel {cost = i+4; lenght = i + 3;}  --> node[i*2].i++;
            node[i].o++ --> Channel {cost = i+5; lenght = i + 2;}  --> node[i*3].i++;
        }
        for i=0..48 {
            node[i].o++ --> Channel {cost = i*2; lenght = i + 5;}  --> node[i+1].i++;
            node[i].i++ <-- Channel {cost = i*3; lenght = i + 1;}  <-- node[i+1].o++;
        }
}

