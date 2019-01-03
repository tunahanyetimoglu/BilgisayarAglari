


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
            delay = default(1ms);
        }
    submodules:
        node[50]: Computer;
    connections:
        for i=0..24 {
            node[i*2].o++ --> Channel {delay = 100ms; }  --> node[i+2].i++;
        }
        for i=0..10 {
            node[i*4].o++ --> Channel {delay = 200ms; }  --> node[i].i++;
        }
        for i=0..15 {  
            node[i*3].o++ --> Channel {delay = 300ms; }  --> node[i*2].i++;
            node[i].o++ --> Channel {delay = 400ms;}  --> node[i*3].i++;
        }
        for i=0..48 {
            node[i].o++ --> Channel {delay = 500ms;}  --> node[i+1].i++;
            node[i].i++ <-- Channel {delay = 500ms;}  <-- node[i+1].o++;
        }
}

