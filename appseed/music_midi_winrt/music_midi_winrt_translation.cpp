#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace winrt
      {


         ::multimedia::e_result translate_hr(HRESULT hr)
         {

            if(SUCCEEDED(hr))
            {

               return ::multimedia::result_success;

            }
            else
            {

               return ::multimedia::result_error;

            }

         }


      } // namespace winrt

   } // namespace midi_winrt


} // namespace music      