//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

//
// message_io.xaml.cpp
// Implementation of the message_io class
//

#include "framework.h"

using namespace Windows::Foundation;
using namespace Platform;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::Storage::Streams;
using namespace Windows::Devices::Midi;

namespace music
{

   namespace midi
   {

      namespace winrt
      {


         message_io::message_io()
            :
            _messageTypeMap(nullptr),
            _messageType(MidiMessageType::None),
            _midiInDeviceWatcher(nullptr),
            _midiOutDeviceWatcher(nullptr)
         {
            _messageTypeMap.set_at(MidiMessageType::ActiveSensing, "Active Sensing");
            _messageTypeMap.set_at(MidiMessageType::ChannelPressure, "Channel Pressure");
            _messageTypeMap.set_at(MidiMessageType::Continue, "Continue");
            _messageTypeMap.set_at(MidiMessageType::ControlChange, "Control Change");
            _messageTypeMap.set_at(MidiMessageType::MidiTimeCode, "MIDI Time Code");
            //_messageTypeMap.set_at(MidiMessageType::None, "None");
            _messageTypeMap.set_at(MidiMessageType::NoteOff, "Note Off");
            _messageTypeMap.set_at(MidiMessageType::NoteOn, "Note On");
            _messageTypeMap.set_at(MidiMessageType::PitchBendChange, "Pitch Bend Change");
            _messageTypeMap.set_at(MidiMessageType::PolyphonicKeyPressure, "Polyphonic Key Pressure");
            _messageTypeMap.set_at(MidiMessageType::ProgramChange, "Program Change");
            _messageTypeMap.set_at(MidiMessageType::SongPositionPointer, "Song Position Pointer");
            _messageTypeMap.set_at(MidiMessageType::SongSelect, "Song Select");
            _messageTypeMap.set_at(MidiMessageType::Start, "Start");
            _messageTypeMap.set_at(MidiMessageType::Stop, "Stop");
            _messageTypeMap.set_at(MidiMessageType::SystemExclusive, "System Exclusive");
            _messageTypeMap.set_at(MidiMessageType::SystemReset, "System Reset");
            _messageTypeMap.set_at(MidiMessageType::TimingClock, "Timing Clock");
            _messageTypeMap.set_at(MidiMessageType::TuneRequest, "Tune Request");

            ScenarioInit();



            // start the MIDI In and Out device watcher
            //_midiInDeviceWatcher = ref new MidiDeviceWatcher(this, MidiInPort::GetDeviceSelector());
            _midiOutDeviceWatcher = ref new MidiDeviceWatcher(this, MidiOutPort::GetDeviceSelector());

            //_midiInDeviceWatcher->Start();
            _midiOutDeviceWatcher->Start();

         }

         message_io::~message_io()
         {
            _midiInDeviceWatcher->Stop();
            _midiOutDeviceWatcher->Stop();
         }

         void  message_io::ScenarioInit()
         {


         }

         void  message_io::ScenarioClose()
         {
         }

         //void message_io::ShowStatusMessage(String^ text)
         //{



         //}


         void message_io::OnMessageReceived(MidiInPort ^sender, MidiMessageReceivedEventArgs ^args)
         {
            //IMidiMessage^ midiMessage = args->Message;

            //create_task(Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High,
            //   ref new Windows::UI::Core::DispatchedHandler([this, sender, midiMessage]()
            //{
            //   String^ outputString = midiMessage->Timestamp.Duration + ", " + _messageTypeMap->Lookup(midiMessage->Type);

            //   switch (midiMessage->Type)
            //   {
            //   case MidiMessageType::NoteOff:
            //   {
            //      MidiNoteOffMessage^ noteOff = static_cast<MidiNoteOffMessage ^>(midiMessage);

            //      outputString += ", Channel:" + noteOff->Channel + ", Note:" + noteOff->Note + ", Velocity:" + noteOff->Velocity;
            //      break;
            //   }
            //   case MidiMessageType::NoteOn:
            //   {
            //      MidiNoteOnMessage^ noteOn = static_cast<MidiNoteOnMessage ^>(midiMessage);

            //      outputString += ", Channel:" + noteOn->Channel + ", Note:" + noteOn->Note + ", Velocity:" + noteOn->Velocity;
            //      break;
            //   }
            //   case MidiMessageType::PolyphonicKeyPressure:
            //   {
            //      MidiPolyphonicKeyPressureMessage^ polyKeyMessage = static_cast<MidiPolyphonicKeyPressureMessage ^>(midiMessage);

            //      outputString += ", Channel:" + polyKeyMessage->Channel + ", Note:" + polyKeyMessage->Note + ", Pressure:" + polyKeyMessage->Pressure;
            //      break;

            //   }
            //   case MidiMessageType::ControlChange:
            //   {
            //      MidiControlChangeMessage^ controlMessage = static_cast<MidiControlChangeMessage ^>(midiMessage);

            //      outputString += ", Channel:" + controlMessage->Channel + ", Controller:" + controlMessage->Controller + ", Value:" + controlMessage->ControlValue;
            //      break;

            //   }
            //   case MidiMessageType::ProgramChange:
            //   {

            //      MidiProgramChangeMessage^ programMessage = static_cast<MidiProgramChangeMessage ^>(midiMessage);

            //      outputString += ", Channel:" + programMessage->Channel + ", Program:" + programMessage->Program;
            //      break;

            //   }
            //   case MidiMessageType::ChannelPressure:
            //   {
            //      MidiChannelPressureMessage^ channelPressureMessage = static_cast<MidiChannelPressureMessage ^>(midiMessage);

            //      outputString += ", Channel:" + channelPressureMessage->Channel + ", Pressure:" + channelPressureMessage->Pressure;
            //      break;

            //   }
            //   case MidiMessageType::PitchBendChange:
            //   {
            //      MidiPitchBendChangeMessage^ pitchBendMessage = static_cast<MidiPitchBendChangeMessage ^>(midiMessage);

            //      outputString += ", Channel:" + pitchBendMessage->Channel + ", Bend:" + pitchBendMessage->Bend;
            //      break;

            //   }
            //   case MidiMessageType::SystemExclusive:
            //   {
            //      MidiSystemExclusiveMessage^ sysExMessage = static_cast<MidiSystemExclusiveMessage ^>(midiMessage);
            //      DataReader^ sysExReader = DataReader::FromBuffer(sysExMessage->RawData);

            //      outputString += ", ";

            //      while (sysExReader->UnconsumedBufferLength > 0)
            //      {
            //         // prepare SysEx message for printing to the screen.
            //         // convert bytes to hex strings.
            //         Array<wchar_t>^ byteInHex = ref new Array<wchar_t>(3);
            //         byte byteRead = sysExReader->ReadByte();

            //         swprintf_s(byteInHex->Data, sizeof(byteInHex->Length), L"%02X", byteRead);
            //         String^ hexString = ref new String(byteInHex->Data);

            //         outputString += hexString + " ";
            //      }
            //      break;

            //   }
            //   case MidiMessageType::MidiTimeCode:
            //   {
            //      MidiTimeCodeMessage^ mtcMessage = static_cast<MidiTimeCodeMessage ^>(midiMessage);

            //      outputString += ", Type:" + mtcMessage->FrameType + ", Values:" + mtcMessage->Values;
            //      break;

            //   }
            //   case MidiMessageType::SongPositionPointer:
            //   {
            //      MidiSongPositionPointerMessage^ songPositionMessage = static_cast<MidiSongPositionPointerMessage ^>(midiMessage);

            //      outputString += ", Beats:" + songPositionMessage->Beats;
            //      break;

            //   }
            //   case MidiMessageType::SongSelect:
            //   {
            //      MidiSongSelectMessage^ songSelectMessage = static_cast<MidiSongSelectMessage ^>(midiMessage);

            //      outputString += ", Song:" + songSelectMessage->Song;
            //      break;

            //   }
            //   case MidiMessageType::TuneRequest:
            //   {
            //      MidiTuneRequestMessage^ tuneRequestMessage = static_cast<MidiTuneRequestMessage ^>(midiMessage);

            //      break;

            //   }
            //   case MidiMessageType::TimingClock:
            //   {
            //      MidiTimingClockMessage^ timingClockMessage = static_cast<MidiTimingClockMessage ^>(midiMessage);

            //      break;

            //   }
            //   case MidiMessageType::Start:
            //   {
            //      MidiStartMessage^ startMessage = static_cast<MidiStartMessage ^>(midiMessage);

            //      break;

            //   }
            //   case MidiMessageType::Continue:
            //   {
            //      MidiContinueMessage^ continueMessage = static_cast<MidiContinueMessage ^>(midiMessage);

            //      break;

            //   }
            //   case MidiMessageType::Stop:
            //   {
            //      MidiStopMessage^ stopMessage = static_cast<MidiStopMessage ^>(midiMessage);

            //      break;

            //   }
            //   case MidiMessageType::ActiveSensing:
            //   {
            //      MidiActiveSensingMessage^ activeSensingMessage = static_cast<MidiActiveSensingMessage ^>(midiMessage);

            //      break;

            //   }
            //   case MidiMessageType::SystemReset:
            //   {
            //      MidiSystemResetMessage^ systemResetMessage = static_cast<MidiSystemResetMessage ^>(midiMessage);

            //      break;

            //   }
            //   case MidiMessageType::None:
            //   default:
            //      break;
            //   }

            //   _messageOutputListBox->Items->Append(outputString);
            //})));
         }

         DeviceInformation^ message_io::GetDeviceInformationForInPort(String^ friendlyName)
         {
            DeviceInformation^ retValue = nullptr;
            DeviceInformationCollection^ inputCollection = _midiInDeviceWatcher->GetDeviceInformationCollection();

            for (index i = 0; i < inputCollection->Size; i++)
            {
               
               DeviceInformation^ devInfo = inputCollection->GetAt(i);

               if (0 == String::CompareOrdinal(devInfo->Name, friendlyName))
               {

                  retValue = devInfo;

               }

            }

            return retValue;
         }

         DeviceInformation^ message_io::GetDeviceInformationForOutPort(String^ friendlyName)
         {
            DeviceInformation^ retValue = nullptr;
            DeviceInformationCollection^ inputCollection = _midiOutDeviceWatcher->GetDeviceInformationCollection();

            for (index i = 0; i < inputCollection->Size; i++)
            {

               DeviceInformation^ devInfo = inputCollection->GetAt(i);

               if (0 == String::CompareOrdinal(devInfo->Name, friendlyName))
               {

                  retValue = devInfo;
                  break;

               }
            }

            return retValue;

         }

         void message_io::CloseInPort(String^ portId)
         {
            for (unsigned int index = 0; index < _midiInPortArray.get_size(); index++)
            {
               if (0 == String::CompareOrdinal(_midiInPortArray[index]->DeviceId, portId))
               {
                  _midiInPortArray.remove_at(index);

                  return;
               }
            }
         }

         void message_io::CloseOutPort(String^ portId)
         {
            for (unsigned int index = 0; index < _midiOutPortArray.get_size(); index++)
            {
               if (0 == String::CompareOrdinal(_midiOutPortArray[index]->DeviceId, portId))
               {
                  _midiOutPortArray.remove_at(index);

                  return;
               }
            }
         }

         message_io::MidiDeviceWatcher::MidiDeviceWatcher(message_io ^io, String ^ midiSelector)
            : m_io(io),_midiSelectorString(midiSelector),
            _deviceWatcher(nullptr),
            _devInfoCollection(nullptr),
            _enumCompleted(false)
         {
            _deviceWatcher = DeviceInformation::CreateWatcher(midiSelector);

            _portAddedToken = _deviceWatcher->Added += ref new TypedEventHandler<DeviceWatcher ^, DeviceInformation ^>(this, &message_io::MidiDeviceWatcher::OnPortAdded);
            _portRemovedToken = _deviceWatcher->Removed += ref new TypedEventHandler<DeviceWatcher ^, DeviceInformationUpdate ^>(this, &message_io::MidiDeviceWatcher::OnPortRemoved);
            _portUpdatedToken = _deviceWatcher->Updated += ref new TypedEventHandler<DeviceWatcher ^, DeviceInformationUpdate ^>(this, &message_io::MidiDeviceWatcher::OnPortUpdated);
            _portEnumCompleteToken = _deviceWatcher->EnumerationCompleted += ref new TypedEventHandler<DeviceWatcher ^, Object ^>(this, &message_io::MidiDeviceWatcher::OnPortEnumCompleted);
         }

         message_io::MidiDeviceWatcher::~MidiDeviceWatcher()
         {
            _deviceWatcher->Added -= _portAddedToken;
            _deviceWatcher->Removed -= _portRemovedToken;
            _deviceWatcher->Updated -= _portUpdatedToken;
            _deviceWatcher->EnumerationCompleted -= _portEnumCompleteToken;
         }

         void message_io::MidiDeviceWatcher::Start()
         {
            _deviceWatcher->Start();
         }

         void message_io::MidiDeviceWatcher::Stop()
         {
            _deviceWatcher->Stop();
         }

         DeviceInformationCollection^ message_io::MidiDeviceWatcher::GetDeviceInformationCollection()
         {
            return _devInfoCollection;
         }

         
         void message_io::MidiDeviceWatcher::UpdatePorts()
         {

            DeviceInformationCollection^ deviceInfoCollection = ::wait(DeviceInformation::FindAllAsync(_midiSelectorString));

            m_io->clear_out_ports();

            if ((deviceInfoCollection == nullptr) || (deviceInfoCollection->Size == 0))
            {


            }
            else
            {

               _devInfoCollection = deviceInfoCollection;

               for (index i = 0; i < deviceInfoCollection->Size; i++)
               {

                  DeviceInformation ^ devInfo = deviceInfoCollection->GetAt(i);

                  m_io->add_out_port(devInfo->Name);

               }

            }

         }

         void message_io::MidiDeviceWatcher::OnPortAdded(DeviceWatcher^ deviceWatcher, DeviceInformation^ devInfo)
         {
            if (_enumCompleted)
            {
               //create_task(_coreDispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High,
               //   ref new Windows::UI::Core::DispatchedHandler([this]()
               //{
                  UpdatePorts();
//               })));
            }
         }

         void message_io::MidiDeviceWatcher::OnPortRemoved(DeviceWatcher^ deviceWatcher, DeviceInformationUpdate^ devInfoUpdate)
         {
            if (_enumCompleted)
            {
               //_coreDispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High,
               //   ref new Windows::UI::Core::DispatchedHandler([this]()
               //{
                  UpdatePorts();
               //}));
            }
         }

         void message_io::MidiDeviceWatcher::OnPortUpdated(DeviceWatcher^ deviceWatcher, DeviceInformationUpdate^ devInfoUpdate)
         {
            if (_enumCompleted)
            {
               //_coreDispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High,
               //   ref new Windows::UI::Core::DispatchedHandler([this]()
               //{
                  UpdatePorts();
               //}));
            }
         }

         void message_io::MidiDeviceWatcher::OnPortEnumCompleted(DeviceWatcher^ deviceWatcher, Object^ obj)
         {
            _enumCompleted = true;

            //_coreDispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High,
            //   ref new Windows::UI::Core::DispatchedHandler([this]()
            //{
               UpdatePorts();
            //}));
         }


         int message_io::get_out_port_count()
         {

            return m_straOut.get_size();

         }


         String^ message_io::get_out_port_name(int i)
         {

            return m_straOut[i];

         }

         void message_io::select_out_port(String ^ str)
         {
            _midiOutPortArray.remove_all();

            DeviceInformation^ portToOpen = GetDeviceInformationForOutPort(str);

            if (portToOpen != nullptr)
            {
               
               IMidiOutPort^ outPort = ::wait(MidiOutPort::FromIdAsync(portToOpen->Id));

               if (outPort != nullptr)
               {

                  _midiOutPortArray.add(outPort);

               }

            }

         }

         void message_io::add_out_port(String ^ portId)
         {

            m_straOut.add(portId);

         }

         void message_io::clear_out_ports()
         {

            m_straOut.remove_all();

         }


         //void message_io::send(MidiMessageType etype)
         //{

         //   IMidiMessage^ midiMessage;

         //   switch (etype)
         //   {
         //      //case MidiMessageType::NoteOff:

         //      //   midiMessage = ref new MidiNoteOffMessage(_field1IntValue, _field2IntValue, _field3IntValue);
         //      //   break;

         //   case MidiMessageType::NoteOn:

         //      //midiMessage = ref new MidiNoteOnMessage(iChannel, uchNote, uchVelocity);
         //      break;

         //      //case MidiMessageType::PolyphonicKeyPressure:

         //      //   midiMessage = ref new MidiPolyphonicKeyPressureMessage(_field1IntValue, _field2IntValue, _field3IntValue);
         //      //   break;

               //case MidiMessageType::ControlChange:

               //   midiMessage = ref new MidiControlChangeMessage(_field1IntValue, _field2IntValue, _field3IntValue);
               //   break;

               //case MidiMessageType::ProgramChange:

               //   midiMessage = ref new MidiProgramChangeMessage(_field1IntValue, _field2IntValue);
               //   break;

               //case MidiMessageType::ChannelPressure:

               //   midiMessage = ref new MidiChannelPressureMessage(_field1IntValue, _field2IntValue);
               //   break;

               //case MidiMessageType::PitchBendChange:

               //   midiMessage = ref new MidiPitchBendChangeMessage(_field1IntValue, _field2IntValue);
               //   break;

               //case MidiMessageType::SystemExclusive:
               //{
               //   DataWriter^ dataWriter = ref new DataWriter();

               //   // expecting a string of format "NN NN NN NN...." where NN is a byte in hex
               //   int len = _sendMessageTextBox->Text->Length();
               //   if (0 == len)
               //   {
               //      return;
               //   }

               //   const wchar_t* startPointer = _sendMessageTextBox->Text->Data();
               //   wchar_t* endPointer = nullptr;

               //   do
               //   {
               //      byte midiByte = (byte)wcstoul(startPointer, &endPointer, 16);
               //      if (endPointer == startPointer)
               //      {
               //         // conversion failed, bail out
               //         break;
               //      }

               //      dataWriter->WriteByte(midiByte);

               //      // prep for next iteration
               //      startPointer = endPointer;
               //   } while (nullptr != endPointer);

               //   midiMessage = ref new MidiSystemExclusiveMessage(dataWriter->DetachBuffer());
               //   break;
               //}
               //case MidiMessageType::MidiTimeCode:

               //   midiMessage = ref new MidiTimeCodeMessage(_field1IntValue, _field2IntValue);
               //   break;

               //case MidiMessageType::SongPositionPointer:

               //   midiMessage = ref new MidiSongPositionPointerMessage(_field1IntValue);
               //   break;

               //case MidiMessageType::SongSelect:

               //   midiMessage = ref new MidiSongSelectMessage(_field1IntValue);
               //   break;

               //case MidiMessageType::TuneRequest:

               //   midiMessage = ref new MidiTuneRequestMessage();
               //   break;

               //case MidiMessageType::TimingClock:

               //   midiMessage = ref new MidiTimingClockMessage();
               //   break;

               //case MidiMessageType::Start:

               //   midiMessage = ref new MidiStartMessage();
               //   break;

               //case MidiMessageType::Continue:

               //   midiMessage = ref new MidiContinueMessage();
               //   break;

               //case MidiMessageType::Stop:

               //   midiMessage = ref new MidiStopMessage();
               //   break;

               //case MidiMessageType::ActiveSensing:

               //   midiMessage = ref new MidiActiveSensingMessage();
               //   break;

               //case MidiMessageType::SystemReset:

               //   midiMessage = ref new MidiSystemResetMessage();
               //   break;

               //case MidiMessageType::None:
         //   default:
         //      return;
         //   }

         //   send(midiMessage);

         //}

         void message_io::send(IMidiMessage ^ message)
         {
            for (auto out : _midiOutPortArray)
            {
               out->SendMessage(message);

            }

         }

         void message_io::note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity)
         {

            iChannel = clip(0, 15, iChannel);

            uchNote = clip(0, 127, uchNote);

            uchVelocity = clip(0, 127, uchVelocity);

            IMidiMessage ^ message = ref new MidiNoteOnMessage(iChannel, uchNote, uchVelocity);

            send(message);

         }

         void message_io::note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity)
         {

            iChannel = clip(0, 15, iChannel);

            uchNote = clip(0, 127, uchNote);

            uchVelocity = clip(0, 127, uchVelocity);

            IMidiMessage ^ message = ref new MidiNoteOffMessage(iChannel, uchNote, uchVelocity);

            send(message);

         }

         void message_io::program_change(int iChannel, unsigned char uchProgram)
         {

            IMidiMessage ^ message = ref new MidiProgramChangeMessage(iChannel, uchProgram);

            send(message);

         }

         void message_io::control_change(int iChannel, unsigned char uchController, unsigned char uchValue)
         {

            IMidiMessage ^ message = ref new MidiControlChangeMessage(iChannel, uchController, uchValue);

            send(message);

         }
         
         void message_io::pitch_bend(int iChannel, unsigned short ushBend)
         {

            
            IMidiMessage ^ message = ref new MidiPitchBendChangeMessage(iChannel, ushBend);

            send(message);

         }


      } // namespace winrt

   } // namespace midi

} // namespace music



