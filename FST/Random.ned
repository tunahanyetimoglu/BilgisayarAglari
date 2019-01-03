


simple Node
{
        @display("i=abstract/penguin");
    gates:
        inout g[];
}

network RandomNetwork
{
    parameters:
        int n = 150;  // Number of Nodes
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
            node[i].g++ <--> Channel {delay = intuniform(0ms, 10000ms); }  <--> node[i+4].g++;
        }
        for i=0..int(n/5)+5{
            node[i*3].g++ <--> Channel {delay = intuniform(0ms,1000ms); } <--> node[i+3].g++;
        }
        for i=1..int(n/3)-3{
            node[i*3].g++ <--> Channel {delay = intuniform(0ms, 1000ms); } <--> node[i+25].g++;
        }
        for i=7..int(n-15){
            node[i].g++ <--> Channel {delay = intuniform(0ms,1000ms); } <--> node[i+14].g++;
        }
}

