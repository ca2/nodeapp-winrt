#pragma once


#include "app-veriwell/appseed/multimedia/multimedia/multimedia.h"


#if defined(_VERIWELL_MULTIMEDIA_MUSIC_MIDI_WINRT_LIBRARY)
   #define CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_WINRT  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_WINRT  CLASS_DECL_IMPORT
#endif

//#include <collection.h>

/* MIDI data block header */
typedef struct midihdr_tag {
   LPSTR       lpData;               /* pointer to locked data block */
   DWORD       dwBufferLength;       /* length of data in data block */
   DWORD       dwBytesRecorded;      /* used for input only */
   DWORD_PTR   dwUser;               /* for client's use */
   DWORD       dwFlags;              /* assorted flags (see defines) */
   struct midihdr_tag far *lpNext;   /* reserved for driver */
   DWORD_PTR   reserved;             /* reserved for driver */

   DWORD       dwOffset;             /* Callback offset into buffer */
   DWORD_PTR   dwReserved[8];        /* Reserved for MMSYSTEM */
} MIDIHDR, *PMIDIHDR, NEAR *NPMIDIHDR, FAR *LPMIDIHDR;


typedef struct midievent_tag
{
   DWORD       dwDeltaTime;          /* Ticks since last event */
   DWORD       dwStreamID;           /* Reserved; must be zero */
   DWORD       dwEvent;              /* Event type and parameters */
   DWORD       dwParms[1];           /* Parameters if this is a long event */
} MIDIEVENT;



//using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Platform;
//using namespace Windows::UI;
//using namespace Windows::UI::Core;
//using namespace Windows::UI::Xaml;
//using namespace Windows::UI::Xaml::Controls;
//using namespace Windows::UI::Xaml::Navigation;
//using namespace Windows::Storage::Streams;
using namespace Windows::Devices::Midi;

//using namespace SDKSample::MIDI;
//using namespace concurrency;

#include "music_midi_winrt_translation.h"

#include "music_midi_winrt_sequence.h"

#include "music_midi_io.h"

#include "player/music_midi_winrt_player.h"

#include "music_midi_winrt_out.h"

#include "music_midi_winrt_file.h"
          
#include "music_midi_winrt_sequence_thread.h"

#include "music_midi_winrt_thread.h"

#include "music_midi_winrt_factory_exchange.h"



#include "music_midi_winrt_midi.h"

