//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

simple FST
{
    parameters:
        bool hasParent = default(false);
        @display("i=abstract/penguin");
    gates:
        inout gate[];
}

network Network
{
    @display("bgb=2530.076,1506.242");
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = default(1ms);
        }
    submodules:
        a: FST {
            @display("p=461.88,1005.872");
        }
        b: FST;
        c: FST {
            @display("p=325.882,161.658");
        }
        d: FST {
            @display("p=1534.468,128.3");
        }
        e: FST {
            @display("p=1585.788,467.012");
        }
        f: FST {
            @display("p=1619.146,949.42");
        }
    connections:
        a.gate++ <--> Channel {  delay = 100ms; } <--> b.gate++;
        b.gate++ <--> Channel {  delay = 100ms; } <--> d.gate++;
        d.gate++ <--> Channel {  delay = 150ms; } <--> e.gate++;
        c.gate++ <--> Channel {  delay = 150ms; } <--> d.gate++;
        c.gate++ <--> Channel {  delay = 25ms; } <--> b.gate++;
        e.gate++ <--> Channel {  delay = 250ms; } <--> a.gate++;
        b.gate++ <--> Channel {  delay = 100ms; } <--> e.gate++;
        e.gate++ <--> Channel {  delay = 150ms; } <--> f.gate++;
        f.gate++ <--> Channel {  delay = 100ms; } <--> a.gate++;
}
