
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
        int n;
          @display("bgb=3592.1213,1401.3888");
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = default(1ms);
        }
    submodules:
        node[n]: Node;
    connections :
        
	for i=0..n-1, for j=0..n-1 {
		node[i].gate++ <--> Channel {delay = intuniform(0ms,100000ms); } <--> node[j].gate++
		if i!=j;
	}
}
