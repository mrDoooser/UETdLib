#include "pch.h"
#include "UETdApiL.h"
#include "UETdApiLibraryL.h"


UETdApiLibrary::UETdApiLibrary()
{
	API = new UETdApi();
}

UETdApiLibrary::~UETdApiLibrary()
{

}

void UETdApiLibrary::Initialize(FTdApiInitParams* init_params)
{
	API->Initialize(init_params);

	//Result(1);
}

bool UETdApiLibrary::Initialized()
{
	return API->Initialized();
};

//void UETdApiLibrary::SetCallbackFunc(std::function<void()>func)
//{
//	//API->OnAuthorizationStateWaitEncryptionKey = func;
//	//API->OnAuthorizationStateWaitEncryptionKey_ = func;
//}
//
//void UETdApiLibrary::SetCallbackFunc(void (*func)())
//{
//	//API->OnAuthorizationStateWaitEncryptionKey = func;
//}

Delegate* UETdApiLibrary::GetDelegateAuthorizationStateReady()
{
	return &API->OnAuthorizationStateReady;
}

Delegate* UETdApiLibrary::GetDelegateAuthorizationStateLoggingOut()
{
	return &API->OnAuthorizationStateLoggingOut;
}

Delegate* UETdApiLibrary::GetDelegateAuthorizationStateClosing()
{
	return &API->OnAuthorizationStateClosing;
}

Delegate* UETdApiLibrary::GetDelegateAuthorizationStateClosed()
{
	return &API->OnAuthorizationStateClosed;
}

Delegate* UETdApiLibrary::GetDelegateAuthorizationStateWaitCode()
{
	return &API->OnAuthorizationStateWaitCode;
}

Delegate* UETdApiLibrary::GetDelegateAuthorizationStateWaitRegistration()
{
	return &API->OnAuthorizationStateWaitRegistration;
}

Delegate* UETdApiLibrary::GetDelegateAuthorizationStateWaitPassword()
{
	return &API->OnAuthorizationStateWaitPassword;
}

Delegate* UETdApiLibrary::GetDelegateAuthorizationStateWaitPhoneNumber()
{
	return &API->OnAuthorizationStateWaitPhoneNumber;
}

Delegate* UETdApiLibrary::GetDelegateAuthorizationStateWaitEncryptionKey()
{
	return &API->OnAuthorizationStateWaitEncryptionKey;
}

Delegate* UETdApiLibrary::GetDelegateAuthorizationStateWaitTdlibParameters()
{
	return &API->OnAuthorizationStateWaitTdlibParameters;
}

void UETdApiLibrary::SetFunc(std::function<void(void)> func)
{
	API->func = func;
}