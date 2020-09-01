/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2020 Hermann Detz <hermann.detz@gmail.com>                 *
 *                                                                         *
 *  This library is free software; you can redistribute it and/or          *
 *  modify it under the terms of the GNU Lesser General Public             *
 *  License as published by the Free Software Foundation;                  *
 *  version 3 of the License.                                              *
 *                                                                         *
 *  This library is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *  Lesser General Public License for more details.                        *
 *                                                                         *
 *  You should have received a copy of the GNU Lesser General Public       *
 *  License along with this library; If not, see                           *
 *  <http://www.gnu.org/licenses/>.                                        *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef INTEGRATIONPLUGINWS281XSPI_H
#define INTEGRATIONPLUGINWS281XSPI_H

#include "integrations/integrationplugin.h"

#include "ws281xspicontroller.h"

class IntegrationPluginWs281xspi : public IntegrationPlugin
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "io.nymea.IntegrationPlugin" FILE "integrationpluginws281xspi.json")
    Q_INTERFACES(IntegrationPlugin)


public:
    explicit IntegrationPluginWs281xspi();

    void init() override;
    void setupThing(ThingSetupInfo *info) override;
    void postSetupThing(Thing *thing) override;
    void executeAction(ThingActionInfo *info) override;
    void thingRemoved(Thing *thing) override;

    // Event handlers
    void onBrightnessChanged(const int brightness);
    void onColorChanged(const QColor &color);
    void onPowerChanged(const bool power);

private:
    Ws281xSpiController *m_controller;

};

#endif // INTEGRATIONPLUGINWS281XSPI_H
