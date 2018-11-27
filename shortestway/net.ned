


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
    @display("bgb=1939.535,744.5675");
    submodules:
        node[50] : Computer;
    connections:
       for i = 0..24 {
        node[i*2].o++ --> node[i+2].i++;
		}
		for i = 0..10{
		    node[i*4].o++ --> node[i].i++;
		}
		for i = 0..15{
		    node[i*3].o++ --> node[i*2].i++;
		    node[i].o++ --> node[i*3].i++;
		}
		for i= 0..48{
		    node[i].o++ --> node[i+1].i++;
		    node[i].i++ <-- node[i+1].o++;
		}
}

