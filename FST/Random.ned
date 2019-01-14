


simple Node
{
    bool hasParent = default(false);
    @display("i=abstract/penguin");
    gates:
        inout gate[];
}

network RandomNetwork
{
    parameters:
        int n;  // Number of Nodes
    @display("bgb=3592.1213,1401.3888");
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = default(1ms);
        }
    submodules:
        node[n]: Node;
    connections:
        for i=0..int(n/2)-1 {
            node[i].gate++ <--> Channel {delay = intuniform(0ms, 10000ms); }  <--> node[i+4].gate++;
        }
        for i=0..int(n/5)+5{
            node[i*3].gate++ <--> Channel {delay = intuniform(0ms,1000ms); } <--> node[i+3].gate++;
        }
        for i=1..int(n/3)-3{
            node[i*3].gate++ <--> Channel {delay = intuniform(0ms, 1000ms); } <--> node[i+1].gate++;
        }
        for i=7..int(n-15){
            node[i].gate++ <--> Channel {delay = intuniform(0ms,1000ms); } <--> node[i+14].gate++;
        }
}

