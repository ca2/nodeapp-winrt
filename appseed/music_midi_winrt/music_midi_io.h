#pragma once


using namespace Platform;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Devices::Midi;

namespace music
{


   namespace midi
   {


      namespace winrt
      {


         public ref class message_io sealed
         {
         public:
            message_io();
            virtual ~message_io();

            void ScenarioInit();
            void ScenarioClose();

            //void ShowStatusMessage(String^ text);
            //void ShowExceptionMessage(Exception^ ex);

            //void EnableMessageBuilding();
            //void ResetMessageBuilding(bool resetMessageType);



            void OnMessageReceived(MidiInPort ^sender, MidiMessageReceivedEventArgs ^args);

            DeviceInformation^ GetDeviceInformationForInPort(String^ friendlyName);
            DeviceInformation^ GetDeviceInformationForOutPort(String^ friendlyName);

            void CloseInPort(String^ portId);
            void CloseOutPort(String^ portId);

            int get_out_port_count();
            String ^ get_out_port_name(int i);
            void select_out_port(String ^ str);

            void add_out_port(String ^ portId);
            void clear_out_ports();

//            void send(MidiMessageType etype);

            void note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity);
            void note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity);
            void program_change(int iChannel, unsigned char uchProgram);
            void control_change(int iChannel, unsigned char uchController, unsigned char uchValue);
            void pitch_bend(int iChannel, unsigned short ushBend);
            void send(IMidiMessage ^ message);

         private:
            map<MidiMessageType, MidiMessageType, string> _messageTypeMap;
            MidiMessageType _messageType;
            array<MidiInPort^> _midiInPortArray;
            array<IMidiOutPort^> _midiOutPortArray;
            
            stringa m_straOut;

            ref class MidiDeviceWatcher sealed
            {
            public:
               MidiDeviceWatcher(message_io ^ io, String ^ midiSelector);
               virtual ~MidiDeviceWatcher();
               void Start();
               void Stop();
               DeviceInformationCollection^ GetDeviceInformationCollection();
               void UpdatePorts();

            private:

               void OnPortAdded(DeviceWatcher^ deviceWatcher, DeviceInformation^ devInfo);
               void OnPortRemoved(DeviceWatcher^ deviceWatcher, DeviceInformationUpdate^ devInfoUpdate);
               void OnPortUpdated(DeviceWatcher^ deviceWatcher, DeviceInformationUpdate^ devInfoUpdate);
               void OnPortEnumCompleted(DeviceWatcher^ deviceWatcher, Object^ obj);

               Windows::Foundation::EventRegistrationToken _portAddedToken;
               Windows::Foundation::EventRegistrationToken _portRemovedToken;
               Windows::Foundation::EventRegistrationToken _portUpdatedToken;
               Windows::Foundation::EventRegistrationToken _portEnumCompleteToken;

               message_io ^ m_io;
               String ^ _midiSelectorString;
               DeviceWatcher ^ _deviceWatcher;
               DeviceInformationCollection^ _devInfoCollection;
               bool _enumCompleted;
            };

            MidiDeviceWatcher ^ _midiInDeviceWatcher;
            MidiDeviceWatcher ^ _midiOutDeviceWatcher;
         };
      }

   }

}

