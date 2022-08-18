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

package mine;

// numOfHosts: 10
// parametric: false
// static:     true

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.INetworkNode;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;
import inet.physicallayer.contract.packetlevel.IRadioMedium;
import inet.environment.common.PhysicalEnvironment;

network Multihop
{
    parameters:
        @display("bgb=1000,800;bgg=100,1,grey95");
        @figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);

        @figure[rcvdPkText](type=indicatorText; pos=380,20; anchor=w; font=,18; textFormat="Host B packets received: %g"; initialValue=0);
        @statistic[packetReceived](source=hostB.app[0].packetReceived; record=figure(count); targetFigure=rcvdPkText);
        @statistic[logPacketReceived](source=hostB.app[0].packetReceived; record=vector(count));
        @statistic[logPacketSent](source=hostA.app[0].packetSent; record=vector(count));
    submodules:
        visualizer: IntegratedCanvasVisualizer {
            @display("p=580,125");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=580,200");
        }
        radioMedium: <default("UnitDiskRadioMedium")> like IRadioMedium {
            @display("p=500,125");
        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=500,200");
        }
        hostA: <default("WirelessHost")> like INetworkNode {
            @display("p=50,325");
        }
        hostB: <default("WirelessHost")> like INetworkNode {
            @display("p=550,725");
        }
        hostC: <default("WirelessHost")> like INetworkNode {
            @display("p=200,325");
        }
        hostD: <default("WirelessHost")> like INetworkNode {
            @display("p=400,325");
        }
        hostE: <default("WirelessHost")> like INetworkNode {
            @display("p=200,525");
        }
        hostF: <default("WirelessHost")> like INetworkNode {
            @display("p=400,525");
        }
        hostG: <default("WirelessHost")> like INetworkNode {
            @display("p=200,725");
        }
        hostH: <default("WirelessHost")> like INetworkNode {
            @display("p=400,725");
        }
        packetTrackerG:PacketTracker {
            @display("p=640,125");
        }
        packetTrackerH:PacketTracker {
            @display("p=640,200");
        }
}
