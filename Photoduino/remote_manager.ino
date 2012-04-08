// Command codes
#define REMOTE_CMD_REMOTE_MODE_START                    0x01
#define REMOTE_CMD_REMOTE_MODE_STOP                     0x02
#define REMOTE_CMD_PARAM_REQUEST                        0x04
#define REMOTE_CMD_PARAM_UPDATE                         0x05  
#define REMOTE_CMD_SENSOR_BROADCASTING_START            0x06
#define REMOTE_CMD_SENSOR_BROADCASTING_STOP             0x07
#define REMOTE_CMD_MANUAL_CONTROL_AF_START              0x0A
#define REMOTE_CMD_MANUAL_CONTROL_AF_STOP               0x0B
#define REMOTE_CMD_MANUAL_CONTROL_SHUTTER_START         0x0C
#define REMOTE_CMD_MANUAL_CONTROL_SHUTTER_STOP          0x0D
#define REMOTE_CMD_MANUAL_CONTROL_SHOOT_FLASH1          0x0E
#define REMOTE_CMD_MANUAL_CONTROL_SHOOT_FLASH2          0x0F
#define REMOTE_CMD_MANUAL_CONTROL_DEVICE_ON             0x10
#define REMOTE_CMD_MANUAL_CONTROL_DEVICE_OFF            0x11
#define REMOTE_CMD_TEST_MAKE_DROPS                      0x12
#define REMOTE_CMD_RUN_INTERVALOMETER_MODE              0x13
#define REMOTE_CMD_RUN_SENSOR_TRIGGER_MODE              0x14
#define REMOTE_CMD_CANCEL_RUNMODE                       0x15
    
// Response codes
#define REMOTE_RSP_REPORT_REMOTE_MODE                   0x01
#define REMOTE_RSP_REPORT_PARAM                         0x02
#define REMOTE_RSP_REPORT_SENSOR_READ                   0x03
#define REMOTE_RSP_REPORT_SYSTEM_BUSY                   0x05
#define REMOTE_RSP_REPORT_SYSTEM_IDLE                   0x06


// On sysex message from host
void sysexCallback(byte command, byte argc, byte*argv)
{
    
    switch(command){
      
       case REMOTE_CMD_REMOTE_MODE_START            : remote_mode_start(); break;   
       case REMOTE_CMD_REMOTE_MODE_STOP             : remote_mode_stop(); break;               
       
       case REMOTE_CMD_PARAM_REQUEST                : remote_report_param(argc, argv); break;   
       case REMOTE_CMD_PARAM_UPDATE                 : remote_set_param(argc, argv); break;       
       
       case REMOTE_CMD_SENSOR_BROADCASTING_START    : remoteSensorBroadcasting = true; break;  
       case REMOTE_CMD_SENSOR_BROADCASTING_STOP     : remoteSensorBroadcasting = false; break;  
       
       case REMOTE_CMD_MANUAL_CONTROL_AF_START      : camera_autofocusBegin(0); break;
       case REMOTE_CMD_MANUAL_CONTROL_AF_STOP       : camera_autofocusEnd(); break;   
       case REMOTE_CMD_MANUAL_CONTROL_SHUTTER_START : camera_shutterBegin(0); break;   
       case REMOTE_CMD_MANUAL_CONTROL_SHUTTER_STOP  : camera_shutterEnd(0);break;  
       
       case REMOTE_CMD_MANUAL_CONTROL_SHOOT_FLASH1  : flash_shoot(0, PINS_FLASH1); break;
       case REMOTE_CMD_MANUAL_CONTROL_SHOOT_FLASH2  : flash_shoot(0, PINS_FLASH2); break;
       
       case REMOTE_CMD_MANUAL_CONTROL_DEVICE_ON     : digitalWrite(PINS_DEVICE,HIGH); break;
       case REMOTE_CMD_MANUAL_CONTROL_DEVICE_OFF    : digitalWrite(PINS_DEVICE,LOW); break;
       
       case REMOTE_CMD_TEST_MAKE_DROPS              : remote_report_system_busy(false); 
                                                      electrovalve_makeDrops(); 
                                                      remote_report_system_idle(); 
                                                      break;
                                                      
       case REMOTE_CMD_RUN_INTERVALOMETER_MODE      : remote_report_system_busy(true); 
                                                      runAs_intervalometer(); 
                                                      remote_report_system_idle(); 
                                                      controller_showRemoteMode();
                                                      break;
                                                      
       case REMOTE_CMD_RUN_SENSOR_TRIGGER_MODE      : remote_report_system_busy(true); 
                                                      runAs_sensorTriggerMode();
                                                      remote_report_system_idle(); 
                                                      controller_showRemoteMode();
                                                      break;
       
       case REMOTE_CMD_CANCEL_RUNMODE               : cancelFlag = true;
                                                      break;
       
              
       default:  Firmata.sendString("Unknown command");
                 break;      
    }
}

// Report version of firmware
void remote_mode_start(){
  
  remoteMode = true; 
  byte FirmwareVersion[3] = { 1, CODE_MAJOR_VERSION, CODE_MINOR_VERSION };
  Firmata.sendSysex(REMOTE_RSP_REPORT_REMOTE_MODE, 3, FirmwareVersion);
             
}

// Report version of firmware
void remote_mode_stop(){
  
  remoteMode = false; 
  byte FirmwareVersion[3] = { 0, CODE_MAJOR_VERSION, CODE_MINOR_VERSION };
  Firmata.sendSysex(REMOTE_RSP_REPORT_REMOTE_MODE, 3, FirmwareVersion);
             
}

// Report param value from eeprom
void remote_report_param(byte argc, byte *argv){
  
  // Read value from eeprom
  unsigned int address =  argv[0];
  unsigned int value = eeprom_readInt(address); 
  
  // Create response including the value code
  byte response[3] = {};
  response[0] = argv[0];
  response[1] = value/256;
  response[2] = value % 256;
  
  // Send response
  Firmata.sendSysex(REMOTE_RSP_REPORT_PARAM, 3, response);
  
}

// Set param value in eeprom
void remote_set_param(byte argc, byte *argv){
    
  unsigned int address = argv[0];
  unsigned int value = argv[1]*256+argv[2];
  
  eeprom_writeInt(address, value); 
  config_loadBackup_all();
  backlight_init();
  
}

// Sensor broadcasting
void remote_sensor_broadcast(){
    
   byte sensorType = sensorTriggerMode_sensorType;
   boolean sensorOverflow = false;
   
   unsigned int sensorValue;
   unsigned int *sensorLimit;
   byte sensorPin;
   byte sensorMode;
     
   sensor_getConfiguration(sensorType, &sensorLimit, &sensorPin, &sensorMode);
   sensorValue = sensor_read(sensorPin);
   
   
   if ( ((sensorMode==SENSOR_MODE_HIGHER && sensorValue >= *sensorLimit) || 
         (sensorMode==SENSOR_MODE_LOWER  && sensorValue <= *sensorLimit)) ) {
         //buzzer_beep(100); 
         sensorOverflow = true;
   } else {
         sensorOverflow = false;
         //delay(20);  
   }
   
   byte responseValues[4] = {sensorType, sensorValue/256, sensorValue % 256, sensorOverflow};  
   
   Firmata.sendSysex(REMOTE_RSP_REPORT_SENSOR_READ, 4, responseValues); 
   delay(1);
}

void remote_report_system_busy(boolean cancelable){
   
  byte response[1] = {cancelable};
   Firmata.sendSysex(REMOTE_RSP_REPORT_SYSTEM_BUSY, 1, response); 
}

void remote_report_system_idle(){
  cancelFlag = false;
  Firmata.sendSysex(REMOTE_RSP_REPORT_SYSTEM_IDLE, 0, 0); 
}



