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
#include <cmath>
#include "inet/common/ModuleAccess.h"

namespace inet {

namespace physicallayer {

using namespace inet::physicalenvironment;

Define_Module(MaterialAttenuationObstacleLoss);

MaterialAttenuationObstacleLoss::MaterialAttenuationObstacleLoss() {}

void MaterialAttenuationObstacleLoss::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        medium = check_and_cast<IRadioMedium *>(getParentModule());
        physicalEnvironment = getModuleFromPar<IPhysicalEnvironment>(par("physicalEnvironmentModule"), this);
    }
}

std::ostream& MaterialAttenuationObstacleLoss::printToStream(std::ostream& stream, int level) const
{
    return stream << "MaterialAttenuationObstacleLoss";
}

double MaterialAttenuationObstacleLoss::computeObstacleLoss(Hz frequency, const Coord& transmissionPosition, const Coord& receptionPosition) const
{
    TotalObstacleLossComputation obstacleLossVisitor(this, transmissionPosition, receptionPosition);
    physicalEnvironment->visitObjects(&obstacleLossVisitor, LineSegment(transmissionPosition, receptionPosition));
    return obstacleLossVisitor.getTotalLoss();
}

MaterialAttenuationObstacleLoss::TotalObstacleLossComputation::TotalObstacleLossComputation(const MaterialAttenuationObstacleLoss *obstacleLoss, const Coord& transmissionPosition, const Coord& receptionPosition) :
    totalLoss(1),
    obstacleLoss(obstacleLoss),
    transmissionPosition(transmissionPosition),
    receptionPosition(receptionPosition)
{
}

double MaterialAttenuationObstacleLoss::computeLoss(const IMaterial *material, m distance) const
{
    // We will use the "relative permittivity" attribute of the material to represent signal loss
    //     (in dB) per meter
    // Relative permittivity is not the correct term for this, but OMNeT++ does not seem to have
    //     an easy way to add a custom material property, so I am repurposing an existing but
    //     unused value
    double lpm = material->getRelativePermittivity();
    // Loss = 10^(-dBloss/10)
    double l = pow(10, -(lpm * distance.get()) / 10);
    return l;
}

void MaterialAttenuationObstacleLoss::TotalObstacleLossComputation::visit(const cObject *object) const
{
    totalLoss *= obstacleLoss->computeObjectLoss(check_and_cast<const IPhysicalObject *>(object), transmissionPosition, receptionPosition);
}

// Add in frequency dependence later
double MaterialAttenuationObstacleLoss::computeObjectLoss(const IPhysicalObject *object, const Coord& transmissionPosition, const Coord& receptionPosition) const
{
    double totalLoss = 1;
    const ShapeBase *shape = object->getShape();
    const Coord& position = object->getPosition();
    const Quaternion& orientation = object->getOrientation();
    RotationMatrix rotation(orientation.toEulerAngles());
    const LineSegment lineSegment(rotation.rotateVectorInverse(transmissionPosition - position), rotation.rotateVectorInverse(receptionPosition - position));
    Coord intersection1, intersection2, normal1, normal2;
    bool hasIntersections = shape->computeIntersection(lineSegment, intersection1, intersection2, normal1, normal2);
    if (hasIntersections && (intersection1 != intersection2))
    {
        const IMaterial *material = object->getMaterial();
        double intersectionDistance = intersection2.distance(intersection1);
        totalLoss *= computeLoss(material, m(intersectionDistance));
    }
    return totalLoss;
}


} // namespace physicallayer
} // namespace inet
