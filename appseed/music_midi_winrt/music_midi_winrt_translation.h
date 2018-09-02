#pragma once


#define MIDIMSG(status,channel,data1,data2) ( (uint32_t)((status<<4) | channel | (data1<<8) | (data2<<16)) )


namespace music
{


   namespace midi
   {

      
      namespace winrt
      {


         CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_WINRT ::multimedia::e_result translate_hr(HRESULT hr);


      } // namespace winrt


   } // namespace midi


} // namespace music