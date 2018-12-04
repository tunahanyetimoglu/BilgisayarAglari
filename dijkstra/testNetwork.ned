


simple testComputer
{
    parameters:
        @display("i=block/routing");
        volatile double weight = default(10) @unit();
    gates:
        input i[];
        output o[];

}

network testNetwork
{
    @display("bgb=782,160");

    submodules:
        computer: testComputer {
            @display("p=121,13");
			weight = 20;

        }
        computer1: testComputer {
            @display("p=428,30");            
			weight = 15;
        }
        computer2: testComputer;
        computer3: testComputer {
            @display("p=273,59;b=,,rect");
        }
        computer4: testComputer {	
            @display("p=389,127");
        }
    connections:
        computer.o++  --> computer1.i++;
        computer.o++  --> computer2.i++;
        computer1.o++  --> computer3.i++;
        computer2.o++ --> computer4.i++;
        computer3.o++ --> computer4.i++;
}
