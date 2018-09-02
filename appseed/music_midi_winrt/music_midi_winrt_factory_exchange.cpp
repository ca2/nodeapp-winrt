#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace winrt
      {


         factory_exchange::factory_exchange(::aura::application * papp) :
            ::object(papp) //,
            //::multimedia::winrt::factory_exchange(papp)
         {

            System.factory().cloneable_large < sequence                    >  (System.type_info < ::music::midi::sequence                  > ());
            System.factory().cloneable_large < buffer                      >  (System.type_info < ::music::midi::file::buffer                 > ());
            System.factory().cloneable_large < sequence_thread             >  (System.type_info < ::music::midi::sequence_thread                 > ());
            System.factory().cloneable_large < player::player              >  (System.type_info < ::music::midi::player::player                 > ());
            System.factory().cloneable_large < midi              >(System.type_info < ::music::midi::midi>());
            //System.factory().cloneable_large < player:: player_interface   >  (System.type_info < ::music::midi::player::player_interface                 > ());

         }


         factory_exchange::~factory_exchange()
         {

         }


      } // namespace winrt


   } // namespace midi_winrt


} // namespace music


void ca2_factory_exchange(::aura::application * papp)
{

   ::music::midi::winrt::factory_exchange factoryexchange(papp);

}









