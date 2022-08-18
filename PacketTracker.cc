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

#include "PacketTracker.h"
#include <cstdio>
#include <iostream>

#include "inet/transportlayer/contract/udp/UdpControlInfo.h"

Define_Module(PacketTracker);

void PacketTracker::initialize()
{
    std::string labelParam = par("packetLabels");
    for (int i = 0; i < MAX_FILTERS; i++) {
        filters[i] = "";
        matches[i] = 0;
    }

    int filterIdx = 0;

    while (filterIdx < MAX_FILTERS && labelParam.length() > 0) {
        int idx = labelParam.find(',', 0);
        if (idx > -1) {
            filters[filterIdx] = labelParam.substr(0, idx);
            EV << labelParam.substr(0, idx);
            labelParam = labelParam.substr(0, idx + 2);
        } else {
            filters[filterIdx] = labelParam;
            break;
        }
        filterIdx++;
    }
}

void PacketTracker::handleMessage(cMessage *msg)
{

    if (msg->isSelfMessage()) {
            ASSERT(msg == selfMsg);
    } else if (msg->arrivedOn("in")) {
        if (msg->getKind() ==  UDP_I_DATA) {
            for (int i = 0; i < MAX_FILTERS; i++) {
                cPatternMatcher matcher(filters[i], true, true, true);
                if (matcher.matches(msg->getName())) {
                    matches[i]++;
                }
            }
        }
    }
}

void PacketTracker::finish()
{
    for (int i = 0; i < MAX_FILTERS; i++) {
        if (!(filters[i].compare(""))) {
            char buffer[100];
            sprintf(buffer, "PacketsReceived-%s", filters[i]);
            recordScalar(buffer, matches[i]);
        }
    }
}

int PacketTracker::countChars(char c, std::string str)
{
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == c) count++;
    }
    return count;
}
