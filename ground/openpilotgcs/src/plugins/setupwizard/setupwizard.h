/**
 ******************************************************************************
 *
 * @file       setupwizard.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup Setup Wizard  Plugin
 * @{
 * @brief A Wizards to make the initial setup easy for everyone.
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>
#include "levellingutil.h"
#include <coreplugin/icore.h>
#include <coreplugin/connectionmanager.h>
#include "uavobjectmanager.h"
#include "mixersettings.h"


class SetupWizard : public QWizard
{
    Q_OBJECT

public:
    SetupWizard(QWidget *parent = 0);
    int nextId() const;
    enum CONTROLLER_SELECTION_MODE {CONTROLLER_SELECTION_AUTOMATIC, CONTROLLER_SELECTION_MANUAL, CONTROLLER_SELECTION_UNKNOWN};
    enum CONTROLLER_TYPE {CONTROLLER_UNKNOWN, CONTROLLER_CC, CONTROLLER_CC3D, CONTROLLER_REVO, CONTROLLER_PIPX};
    enum VEHICLE_TYPE {VEHICLE_UNKNOWN, VEHICLE_MULTI, VEHICLE_FIXEDWING, VEHICLE_HELI, VEHICLE_SURFACE};
    enum VEHICLE_SUB_TYPE {MULTI_ROTOR_UNKNOWN, MULTI_ROTOR_TRI_Y, MULTI_ROTOR_QUAD_X, MULTI_ROTOR_QUAD_PLUS,
                               MULTI_ROTOR_HEXA, MULTI_ROTOR_HEXA_H, MULTI_ROTOR_HEXA_COAX_Y, MULTI_ROTOR_OCTO,
                               MULTI_ROTOR_OCTO_V, MULTI_ROTOR_OCTO_COAX_X, MULTI_ROTOR_OCTO_COAX_PLUS, FIXED_WING_AILERON,
                               FIXED_WING_VTAIL, HELI_CCPM};
    enum ESC_TYPE {ESC_DEFAULT, ESC_RAPID, ESC_UNKNOWN};
    enum INPUT_TYPE {INPUT_PWM, INPUT_PPM, INPUT_SBUS, INPUT_DSM, INPUT_UNKNOWN};

    void setControllerSelectionMode(SetupWizard::CONTROLLER_SELECTION_MODE mode) { m_controllerSelectionMode = mode; }
    SetupWizard::CONTROLLER_SELECTION_MODE getControllerSelectionMode() const { return m_controllerSelectionMode; }

    void setControllerType(SetupWizard::CONTROLLER_TYPE type) { m_controllerType = type; }
    SetupWizard::CONTROLLER_TYPE getControllerType() const { return m_controllerType; }

    void setVehicleType(SetupWizard::VEHICLE_TYPE type) { m_vehicleType = type; }
    SetupWizard::VEHICLE_TYPE getVehicleType() const { return m_vehicleType; }

    void setVehicleSubType(SetupWizard::VEHICLE_SUB_TYPE type) { m_vehicleSubType = type; }
    SetupWizard::VEHICLE_SUB_TYPE getVehicleSubType() const { return m_vehicleSubType; }

    void setInputType(SetupWizard::INPUT_TYPE type) { m_inputType = type; }
    SetupWizard::INPUT_TYPE getInputType() const { return m_inputType; }

    void setESCType(SetupWizard::ESC_TYPE type) { m_escType = type; }
    SetupWizard::ESC_TYPE getESCType() const { return m_escType; }

    void setLevellingBias(accelGyroBias bias) { m_levellingBias = bias; m_levellingPerformed = true; }
    bool isLevellingPerformed() { return m_levellingPerformed; }
    accelGyroBias getLevellingBias() const { return m_levellingBias; }


    QString getSummaryText();

    Core::ConnectionManager* getConnectionManager() {
        if (!m_connectionManager) {
            m_connectionManager = Core::ICore::instance()->connectionManager();
            Q_ASSERT(m_connectionManager);
        }
        return m_connectionManager;
    }
public slots:
    void exportConfiguration();
    void writeConfiguration();

private:
    static const qint16 DEFAULT_ESC_FREQUENCE = 50;
    static const qint16 RAPID_ESC_FREQUENCE = 400;

    enum {PAGE_START, PAGE_CONTROLLER, PAGE_VEHICLES, PAGE_MULTI, PAGE_FIXEDWING,
          PAGE_HELI, PAGE_SURFACE, PAGE_INPUT, PAGE_OUTPUT, PAGE_LEVELLING,
          PAGE_FLASH, PAGE_SUMMARY, PAGE_NOTYETIMPLEMENTED, PAGE_END};
    void createPages();

    CONTROLLER_SELECTION_MODE m_controllerSelectionMode;
    CONTROLLER_TYPE m_controllerType;
    VEHICLE_TYPE m_vehicleType;
    VEHICLE_SUB_TYPE m_vehicleSubType;
    INPUT_TYPE m_inputType;
    ESC_TYPE m_escType;
    bool m_levellingPerformed;
    accelGyroBias m_levellingBias;

    Core::ConnectionManager *m_connectionManager;

    UAVObjectManager *getUAVObjectManager();

    void applyConfiguration();
    void applyHardwareConfiguration(UAVObjectManager *uavoMgr);
    void applyVehicleConfiguration(UAVObjectManager *uavoMgr);
    void applyOutputConfiguration(UAVObjectManager *uavoMgr);
    void applyLevellingConfiguration(UAVObjectManager *uavoMgr);

    void resetVehicleConfig(UAVObjectManager *uavoMgr);
    void resetMixerVectors(MixerSettings::DataFields data, qint8 channelIndex);

    void setupTriCopter(UAVObjectManager *uavoMgr);
    void setupQuadCopter(UAVObjectManager *uavoMgr);
    void setupHexaCopter(UAVObjectManager *uavoMgr);
    void setupOctoCopter(UAVObjectManager *uavoMgr);
};

#endif // SETUPWIZARD_H
