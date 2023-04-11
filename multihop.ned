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
import inet.common.scenario.ScenarioManager;

network Multihop
{
    parameters:
        @display("bgb=770,1105;bgg=100,1,grey95");
        @figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);

//        @figure[rcvdPkText](type=indicatorText; pos=200,20; anchor=w; font=,14; textFormat="Host B packets received: %g"; initialValue=0);
//        @statistic[packetReceived](source=hostB.app[0].packetReceived; record=figure(count); targetFigure=rcvdPkText);
//        @statistic[logPacketReceived](source=hostB.app[0].packetReceived; record=vector(count));
//        @statistic[logPacketSent](source=hostA.app[0].packetSent; record=vector(count));
//        @statistic[hostRPosition](source=hostR.mobility.xPos; record=vector);
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
        scenarioManager: ScenarioManager {
            @display("p=660,125");
        }
        hostA: <default("WirelessHost")> like INetworkNode {
            @display("p=152.5,487.5");
        }
        hostB: <default("WirelessHost")> like INetworkNode {
            @display("p=152.5,642.5");
        }
        hostC: <default("WirelessHost")> like INetworkNode {
            @display("p=307.5,642.5");
        }
        hostD: <default("WirelessHost")> like INetworkNode {
            @display("p=307.5,797.5");
        }
        hostE: <default("WirelessHost")> like INetworkNode {
            @display("p=462.5,797.5");
        }
        hostF: <default("WirelessHost")> like INetworkNode {
            @display("p=462.5,952.5");
        }
        hostG: <default("WirelessHost")> like INetworkNode {
            @display("p=617.5,952.5");
        }
		hostR: <default("WirelessHost")> like INetworkNode {
            @display("p=152.5,335");
        }
}
