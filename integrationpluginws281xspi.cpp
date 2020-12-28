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

#include "plugininfo.h"
#include "integrationpluginws281xspi.h"

#include "integrations/thing.h"

#include <QDebug>
#include <QColor>

#include <iostream>

IntegrationPluginWs281xspi::IntegrationPluginWs281xspi()
{

}

void IntegrationPluginWs281xspi::init()
{
    // Initialisation can be done here.
    qCDebug(dcWs281xspi()) << "Plugin initialized.";
}

void IntegrationPluginWs281xspi::setupThing(ThingSetupInfo *info)
{
    // A thing is being set up. Use info->thing() to get details of the thing, do
    // the required setup (e.g. connect to the device) and call info->finish() when done.

    qCDebug(dcWs281xspi()) << "Setup thing" << info->thing();

    Thing *thing = info->thing();

    if (thing->thingClassId() == ws281xspiThingClassId) {
        m_controller = new Ws281xSpiController();

        // connect signals
        // param types (values are initialized already, but need
        // to be propagated to the controller)
        m_controller->setLength(thing->paramValue(ws281xspiThingLengthParamTypeId).value<int>());

        // settings

        // state types
        connect(m_controller, &Ws281xSpiController::brightnessChanged, this, &IntegrationPluginWs281xspi::onBrightnessChanged);
        connect(m_controller, &Ws281xSpiController::colorChanged, this, &IntegrationPluginWs281xspi::onColorChanged);
        connect(m_controller, &Ws281xSpiController::powerChanged, this, &IntegrationPluginWs281xspi::onPowerChanged);
    }

    info->finish(Thing::ThingErrorNoError);
}

void IntegrationPluginWs281xspi::postSetupThing(Thing *thing) {
    if (thing->thingClassId() == ws281xspiThingClassId) {
        // AFter the thing is configured, send the stored settings to the controller
        if (m_controller != nullptr) {
            m_controller->setBrightness(thing->paramValue(ws281xspiBrightnessActionBrightnessParamTypeId).value<int>());
            m_controller->setColor(thing->paramValue(ws281xspiColorActionColorParamTypeId).value<QColor>());
            m_controller->setPower(thing->paramValue(ws281xspiPowerActionPowerParamTypeId).value<bool>());
        }
    }
}

void IntegrationPluginWs281xspi::executeAction(ThingActionInfo *info)
{
    Thing *thing = info->thing();
    Action action = info->action();
    bool controllerResult{};

    // An action is being executed. Use info->action() to get details about the action,
    // do the required operations (e.g. send a command to the network) and call info->finish() when done.

    qCDebug(dcWs281xspi()) << "Executing action for thing" << info->thing() << info->action().actionTypeId().toString() << info->action().params();

    if (thing->thingClassId() == ws281xspiThingClassId) {
        if (action.actionTypeId() == ws281xspiBrightnessActionTypeId) {
            if (m_controller != nullptr) {
                controllerResult = m_controller->setBrightness(action.param(ws281xspiBrightnessActionBrightnessParamTypeId).value().value<int>());

                if (controllerResult == false) {
                    info->finish(Thing::ThingErrorInvalidParameter);
                }
            }
        }

        if (action.actionTypeId() == ws281xspiColorActionTypeId) {
            if (m_controller != nullptr) {
                controllerResult = m_controller->setColor(action.param(ws281xspiColorActionColorParamTypeId).value().value<QColor>());

                if (controllerResult == false) {
                    info->finish(Thing::ThingErrorInvalidParameter);
                }
            }
        }

        if (action.actionTypeId() == ws281xspiPowerActionTypeId) {
            if (m_controller != nullptr) {
                controllerResult = m_controller->setPower(action.param(ws281xspiPowerActionPowerParamTypeId).value().value<bool>());

                if (controllerResult == false) {
                    info->finish(Thing::ThingErrorHardwareNotAvailable);
                }
            }
        }

    }

    if (controllerResult == true) {
        info->finish(Thing::ThingErrorNoError);
    }
}

void IntegrationPluginWs281xspi::thingRemoved(Thing *thing)
{
    // A thing is being removed from the system. Do the required cleanup
    // (e.g. disconnect from the device) here.

    qCDebug(dcWs281xspi()) << "Remove thing" << thing;

    if (m_controller != nullptr) {
        if (m_controller->setBrightness(WS281X_MIN_BRIGHTNESS) == true) {
            delete m_controller;
            m_controller = nullptr;
        }
    }
}

void IntegrationPluginWs281xspi::onBrightnessChanged(const int brightness)
{
    qCDebug(dcWs281xspi()) << "brightness changed: " << brightness;

    foreach (Thing* thing, myThings()) {
        thing->setStateValue(ws281xspiBrightnessActionTypeId, brightness);
    }
}

void IntegrationPluginWs281xspi::onColorChanged(const QColor &color)
{
    qCDebug(dcWs281xspi()) << "color changed: " << color.name();

    foreach (Thing* thing, myThings()) {
        thing->setStateValue(ws281xspiColorActionTypeId, color);
    }
}

void IntegrationPluginWs281xspi::onPowerChanged(const bool power)
{
    qCDebug(dcWs281xspi()) << "power changed" << power;

    foreach (Thing* thing, myThings()) {
        thing->setStateValue(ws281xspiPowerActionTypeId, power);
    }
}

