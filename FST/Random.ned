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

simple Node {
    parameters:
        @display("i=abstract/router_vs");
    gates:
        inout g[];
}

network RandomNetwork {
      types:
        channel Link extends ned.DelayChannel
        {
            delay = default(1ms);
        }
    submodules:
        node0 : Node;
        node1 : Node;
        node2 : Node;
        node3 : Node;
        node4 : Node;
        node5 : Node;
        node6 : Node;
        node7 : Node;
        node8 : Node;
        node9 : Node;
        node10 : Node;
        node11 : Node;
        node12 : Node;
        node13 : Node;
        node14 : Node;
        node15 : Node;
        node16 : Node;
        node17 : Node;
        node18 : Node;
        node19 : Node;
        node20 : Node;
        node21 : Node;
        node22 : Node;
        node23 : Node;
        node24 : Node;
        node25 : Node;
        node26 : Node;
        node27 : Node;
        node28 : Node;
        node29 : Node;
        node30 : Node;
        node31 : Node;
        node32 : Node;
        node33 : Node;
        node34 : Node;
        node35 : Node;
        node36 : Node;
        node37 : Node;
        node38 : Node;
        node39 : Node;
        node40 : Node;
        node41 : Node;
        node42 : Node;
        node43 : Node;
        node44 : Node;
        node45 : Node;
        node46 : Node;
        node47 : Node;
        node48 : Node;
        node49 : Node;
    connections:
        node0.g++ <--> Link <--> node1.g++;
        node0.g++ <--> Link <--> node2.g++;
        node0.g++ <--> Link <--> node3.g++;
        node0.g++ <--> Link <--> node5.g++;
        node1.g++ <--> Link <--> node3.g++;
        node1.g++ <--> Link <--> node22.g++;
        node1.g++ <--> Link <--> node8.g++;
        node1.g++ <--> Link <--> node26.g++;
        node2.g++ <--> Link <--> node19.g++;
        node2.g++ <--> Link <--> node4.g++;
        node2.g++ <--> Link <--> node12.g++;
        node2.g++ <--> Link <--> node15.g++;
        node3.g++ <--> Link <--> node36.g++;
        node3.g++ <--> Link <--> node10.g++;
        node3.g++ <--> Link <--> node13.g++;
        node3.g++ <--> Link <--> node14.g++;
        node4.g++ <--> Link <--> node17.g++;
        node4.g++ <--> Link <--> node7.g++;
        node4.g++ <--> Link <--> node41.g++;
        node5.g++ <--> Link <--> node6.g++;
        node5.g++ <--> Link <--> node9.g++;
        node6.g++ <--> Link <--> node35.g++;
        node6.g++ <--> Link <--> node28.g++;
        node6.g++ <--> Link <--> node47.g++;
        node7.g++ <--> Link <--> node32.g++;
        node7.g++ <--> Link <--> node39.g++;
        node7.g++ <--> Link <--> node43.g++;
        node7.g++ <--> Link <--> node13.g++;
        node8.g++ <--> Link <--> node22.g++;
        node8.g++ <--> Link <--> node24.g++;
        node8.g++ <--> Link <--> node11.g++;
        node8.g++ <--> Link <--> node44.g++;
        node9.g++ <--> Link <--> node26.g++;
        node10.g++ <--> Link <--> node32.g++;
        node10.g++ <--> Link <--> node25.g++;
        node10.g++ <--> Link <--> node26.g++;
        node10.g++ <--> Link <--> node15.g++;
        node11.g++ <--> Link <--> node16.g++;
        node11.g++ <--> Link <--> node23.g++;
        node11.g++ <--> Link <--> node29.g++;
        node11.g++ <--> Link <--> node30.g++;
        node12.g++ <--> Link <--> node33.g++;
        node12.g++ <--> Link <--> node25.g++;
        node13.g++ <--> Link <--> node21.g++;
        node14.g++ <--> Link <--> node48.g++;
        node14.g++ <--> Link <--> node34.g++;
        node14.g++ <--> Link <--> node28.g++;
        node14.g++ <--> Link <--> node45.g++;
        node14.g++ <--> Link <--> node29.g++;
        node14.g++ <--> Link <--> node46.g++;
        node16.g++ <--> Link <--> node18.g++;
        node16.g++ <--> Link <--> node40.g++;
        node16.g++ <--> Link <--> node28.g++;
        node17.g++ <--> Link <--> node42.g++;
        node17.g++ <--> Link <--> node29.g++;
        node18.g++ <--> Link <--> node40.g++;
        node18.g++ <--> Link <--> node42.g++;
        node19.g++ <--> Link <--> node20.g++;
        node19.g++ <--> Link <--> node31.g++;
        node21.g++ <--> Link <--> node24.g++;
        node21.g++ <--> Link <--> node25.g++;
        node21.g++ <--> Link <--> node30.g++;
        node22.g++ <--> Link <--> node49.g++;
        node23.g++ <--> Link <--> node37.g++;
        node23.g++ <--> Link <--> node38.g++;
        node23.g++ <--> Link <--> node27.g++;
        node24.g++ <--> Link <--> node32.g++;
        node24.g++ <--> Link <--> node48.g++;
        node24.g++ <--> Link <--> node30.g++;
        node26.g++ <--> Link <--> node38.g++;
        node26.g++ <--> Link <--> node42.g++;
        node26.g++ <--> Link <--> node28.g++;
        node26.g++ <--> Link <--> node29.g++;
        node28.g++ <--> Link <--> node44.g++;
        node31.g++ <--> Link <--> node41.g++;
        node33.g++ <--> Link <--> node44.g++;
        node34.g++ <--> Link <--> node49.g++;
        node35.g++ <--> Link <--> node37.g++;
        node37.g++ <--> Link <--> node49.g++;
        node39.g++ <--> Link <--> node43.g++;
}
