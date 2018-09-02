#include "framework.h"
#include "appm.h"
#include "BasicTimer.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

appm::appm() :
    m_windowClosed(false)
{
}

void appm::Initialize(CoreApplicationView^ applicationView)
{
    applicationView->Activated +=
        ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &appm::OnActivated);

    CoreApplication::Suspending +=
        ref new EventHandler<SuspendingEventArgs^>(this, &appm::OnSuspending);

    CoreApplication::Resuming +=
        ref new EventHandler<Platform::Object^>(this, &appm::OnResuming);

    m_renderer = ref new CubeRenderer();
}

void appm::SetWindow(CoreWindow^ window)
{
    window->SizeChanged += 
        ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &appm::OnWindowSizeChanged);

    window->Closed += 
        ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &appm::OnWindowClosed);

    window->PointerCursor = ref new CoreCursor(CoreCursorType::Arrow, 0);

    m_renderer->Initialize(CoreWindow::GetForCurrentThread());
}

void appm::Load(Platform::String^ entryPoint)
{
}

void appm::Run()
{
    BasicTimer^ timer = ref new BasicTimer();

    while (!m_windowClosed)
    {
        timer->Update();
        CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
        m_renderer->Update(timer->Total, timer->Delta);
        m_renderer->Render();
        m_renderer->Present(); // This call is synchronized to the display frame rate.
    }
}

void appm::Uninitialize()
{
}

void appm::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
    m_renderer->UpdateForWindowSizeChange();
}

void appm::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
    m_windowClosed = true;
}

void appm::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
    CoreWindow::GetForCurrentThread()->Activate();
}

void appm::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
    // Save application state after requesting a deferral. Holding a deferral
    // indicates that the application is busy performing suspending operations.
    // Be aware that a deferral may not be held indefinitely. After about five
    // seconds, the application will be forced to exit.
     SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

     // Insert your code here

     deferral->Complete();
}
 
void appm::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
}

IFrameworkView^ Direct3DApplicationSource::CreateView()
{
    return ref new appm();
}

[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
    auto direct3DApplicationSource = ref new Direct3DApplicationSource();
    CoreApplication::Run(direct3DApplicationSource);
    return 0;
}
