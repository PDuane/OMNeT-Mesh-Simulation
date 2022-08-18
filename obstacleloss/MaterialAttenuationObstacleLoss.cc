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

#include "MaterialAttenuationObstacleLoss.h"

namespace inet {

namespace physicallayer {

using namespace inet::physicalenvironment;

Define_Module(MaterialAttenuationObstacleLoss);

void MaterialAttenuationObstacleLoss::MaterialAttenuationObstacleLoss() {}

void MaterialAttenuationObstacleLoss::initialize()
{
    if (stage == INITSTAGE_LOCAL) {
        medium = check_and_cast<IRadioMedium *>(getParentModule());
        physicalEnvironment = getModuleFromPar<IPhysicalEnvironment>(par("physicalEnvironmentModule"), this);
    }
}

std::ostream& IdealObstacleLoss::printToStream(std::ostream& stream, int level) const
{
    return stream << "MaterialAttenuationObstacleLoss";
}

void MaterialAttenuationObstacleLoss::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

} // namespace physicallayer
} // namespace inet
