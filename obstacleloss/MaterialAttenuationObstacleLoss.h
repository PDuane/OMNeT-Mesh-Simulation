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

#ifndef __INET4_MATERIALATTENUATIONOBSTACLELOSS_H_
#define __INET4_MATERIALATTENUATIONOBSTACLELOSS_H_

#include "inet/common/IVisitor.h"
#include "inet/common/figures/TrailFigure.h"
#include "inet/environment/contract/IPhysicalEnvironment.h"
#include "inet/physicallayer/base/packetlevel/TracingObstacleLossBase.h"
#include "inet/physicallayer/contract/packetlevel/IRadioMedium.h"

namespace inet {

namespace physicallayer {

    class INET_API MaterialAttenuationObstacleLoss : public TracingObstacleLossBase
    {
      protected:
        class TotalObstacleLossComputation : public IVisitor
        {
          protected:
            const MaterialAttenuationObstacleLoss *obstacleLoss = nullptr;
            const Coord transmissionPosition;
            const Coord receptionPosition;
            mutable bool isObstacleFound_ = false;

          public:
            TotalObstacleLossComputation(const IdealObstacleLoss *obstacleLoss, const Coord& transmissionPosition, const Coord& receptionPosition);
            void visit(const cObject *object) const override;
            bool isObstacleFound() const { return isObstacleFound_; }
        };

        /** @name Parameters */
        //@{
        /**
         * The radio medium where the radio signal propagation takes place.
         */
        IRadioMedium *medium = nullptr;
        /**
         * The physical environment that provides to obstacles.
         */
        physicalenvironment::IPhysicalEnvironment *physicalEnvironment = nullptr;
        //@}

      protected:
        virtual void initialize(int stage) override;

        virtual bool isObstacle(const physicalenvironment::IPhysicalObject *object, const Coord& transmissionPosition, const Coord& receptionPosition) const;

      public:
        MaterialAttenuationObstacleLoss();
        virtual std::ostream& printToStream(std::ostream& stream, int level) const override;
        virtual double computeObstacleLoss(Hz frequency, const Coord& transmissionPosition, const Coord& receptionPosition) const override;
    };

}
}

#endif
