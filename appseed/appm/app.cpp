#include "framework.h"
#include <DirectXMath.h>

#undef System

using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace DirectX;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::System;
using namespace Windows::Graphics::Display;





[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
   
   auto source = ::metrowin::new_directx_application_source("m_app.exe : app=bergedge");

   ::Windows::ApplicationModel::Core::CoreApplication::Run(source);
   
   return 0;

}
