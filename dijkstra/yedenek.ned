


simple yedekComputer1
{
    parameters:
        @display("i=block/routing");
    gates:
        input i[];
        output o[];
}

network yedekNetwork
{
    @display("bgb=1939.535,744.5675");
     types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
            @backbone;
    		double cost = default(1);
    		double lenght = default(1);
        }
    submodules:
        computer: Computer {
            @display("p=47.855,54.8925");
        }
        computer1: Computer {
            @display("p=174.53,54.8925");
        }
        computer2: Computer {
            @display("p=92.895004,175.9375");
        }
        computer3: Computer {
            @display("p=905.0225,74.5975");
        }
        computer4: Computer {
            @display("p=1097.85,91.4875");
        }
        computer5: Computer {
            @display("p=945.84,454.6225");
        }
        computer6: Computer {
            @display("p=809.3125,544.7025");
        }
        computer7: Computer {
            @display("p=782.57,309.65");
        }
        computer8: Computer {
            @display("p=715.01,129.49");
        }
        computer9: Computer {
            @display("p=558.7775,63.3375");
        }
        computer10: Computer {
            @display("p=945.84,244.905");
        }
        computer11: Computer {
            @display("p=503.885,418.0275");
        }
        computer12: Computer {
            @display("p=426.4725,190.0125");
        }
        computer13: Computer {
            @display("p=371.58002,74.5975");
        }
        computer14: Computer {
            @display("p=73.19,409.58252");
        }
        computer15: Computer {
            @display("p=1207.635,677.0075");
        }
        computer16: Computer {
            @display("p=976.805,643.22754");
        }
        computer17: Computer {
            @display("p=174.53,311.0575");
        }
        computer18: Computer {
            @display("p=591.15,489.81");
        }
        computer19: Computer {
            @display("p=280.0925,208.31");
        }
        computer20: Computer {
            @display("p=356.0975,381.4325");
        }
        computer21: Computer {
            @display("p=1169.6326,544.7025");
        }
        computer22: Computer {
            @display("p=1086.59,364.5425");
        }
        computer23: Computer {
            @display("p=626.3375,285.7225");
        }
        computer24: Computer {
            @display("p=1216.0801,216.755");
        }
        computer25: Computer {
            @display("p=1348.385,74.5975");
        }
        computer26: Computer {
            @display("p=253.35,489.81");
        }
        computer27: Computer {
            @display("p=1317.42,454.6225");
        }
        computer28: Computer {
            @display("p=1439.8726,677.0075");
        }
        computer29: Computer {
            @display("p=782.57,677.0075");
        }
        computer30: Computer {
            @display("p=410.99002,544.7025");
        }
        computer31: Computer {
            @display("p=599.59503,627.745");
        }
        computer32: Computer {
            @display("p=1384.98,263.2025");
        }
        computer33: Computer {
            @display("p=1458.17,409.58252");
        }
        computer34: Computer {
            @display("p=1573.5851,74.5975");
        }
        computer35: Computer {
            @display("p=356.0975,688.2675");
        }
        computer36: Computer {
            @display("p=754.42004,436.325");
        }
        computer37: Computer {
            @display("p=161.8625,698.12");
        }
        computer38: Computer {
            @display("p=73.19,572.85254");
        }
        computer39: Computer {
            @display("p=1715.7426,161.8625");
        }
        computer40: Computer {
            @display("p=1850.8625,74.5975");
        }
        computer41: Computer {
            @display("p=1558.1025,263.2025");
        }
        computer42: Computer {
            @display("p=1850.8625,230.83");
        }
        computer43: Computer {
            @display("p=1394.8325,572.85254");
        }
        computer44: Computer {
            @display("p=1864.9375,381.4325");
        }
        computer45: Computer {
            @display("p=1698.8525,389.8775");
        }
        computer46: Computer {
            @display("p=1628.4775,509.515");
        }
        computer47: Computer {
            @display("p=1725.5951,603.8175");
        }
        computer48: Computer {
            @display("p=1822.7125,498.255");
        }
        computer49: Computer {
            @display("p=1573.5851,658.71");
        }
        computer50: Computer {
            @display("p=1831.1576,677.0075");
        }
    connections:
        computer.o++ -->Channel {cost = 3; lenght = 5;} --> computer1.i++;
        computer1.o++ -->Channel {cost = 3; lenght = 5;} --> computer13.i++;
        computer13.o++ -->Channel {cost = 3; lenght = 5;} --> computer12.i++;
        computer12.o++ --> Channel {cost = 3; lenght = 5;} --> computer23.i++;
        computer23.o++ --> computer7.i++;
        computer7.o++ --> computer10.i++;
        computer10.o++ --> computer24.i++;
        computer24.o++ --> computer32.i++;
        computer32.o++ --> computer41.i++;
        computer41.o++ --> computer39.i++;
        computer39.o++ --> computer42.i++;
        computer42.o++ --> computer44.i++;
        computer44.o++ --> computer48.i++;
        computer48.o++ --> computer50.i++;
        computer50.o++ --> computer47.i++;
        computer47.o++ --> computer46.i++;
        computer46.o++ --> computer45.i++;
        computer40.o++ --> computer45.i++;
        computer40.o++ --> computer39.i++;
        computer40.o++ --> computer34.i++;
        computer34.o++ --> computer25.i++;
        computer25.o++ --> computer4.i++;
        computer4.o++ --> computer22.i++;
        computer22.o++ --> computer21.i++;
        computer21.o++ --> computer27.i++;
        computer27.o++ --> computer43.i++;
        computer43.o++ --> computer15.i++;
        computer15.o++ --> computer28.i++;
        computer28.o++ --> computer49.i++;
        computer49.o++ --> computer33.i++;
        computer33.o++ --> computer41.i++;
        computer32.o++ --> computer5.i++;
        computer5.o++ --> computer16.i++;
        computer16.o++ --> computer29.i++;
        computer29.o++ --> computer6.i++;
        computer6.o++ --> computer36.i++;
        computer36.o++ --> computer31.i++;
        computer31.o++ --> computer18.i++;
        computer18.o++ --> computer11.i++;
        computer11.o++ --> computer30.i++;
        computer30.o++ --> computer35.i++;
        computer35.o++ --> computer26.i++;
        computer26.o++ --> computer20.i++;
        computer20.o++ --> computer17.i++;
        computer17.o++ --> computer14.i++;
        computer14.o++ --> computer38.i++;
        computer38.o++ --> computer37.i++;
        computer37.o++ --> computer26.i++;
        computer26.o++ --> computer14.i++;
        computer14.o++ --> computer2.i++;
        computer2.o++ --> computer19.i++;
        computer20.o++ --> computer19.i++;
        computer19.o++ --> computer13.i++;
        computer13.o++ --> computer9.i++;
        computer9.o++ --> computer8.i++;
        computer8.o++ --> computer3.i++;
        computer3.o++ --> computer10.i++;
        computer10.o++ --> computer5.i++;
        computer2.o++ --> computer1.i++;
        computer13.o++ --> computer19.i++;
        computer20.o++ --> computer11.i++;
        computer30.o++ --> computer20.i++;
        computer35.o++ --> computer31.i++;
        computer2.o++ --> computer17.i++;
        computer.o++ --> computer2.i++;
        computer41.o++ --> computer32.i++;
}

