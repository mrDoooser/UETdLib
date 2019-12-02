#pragma once
#include "UETdApiStructs.h"
#include "Delegate.hpp"
class UETdApi;

class UETdApiLibrary
{
public:
	__declspec(dllexport) UETdApiLibrary();

	__declspec(dllexport) ~UETdApiLibrary();

	__declspec(dllexport) bool Initialized();

	__declspec(dllexport) void Initialize(FTdApiInitParams* init_params);

	//__declspec(dllexport) void SetCallbackFunc(void (*func)());
	//
	//__declspec(dllexport) void SetCallbackFunc(std::function<void()>func);

	__declspec(dllexport) Delegate* GetDelegateAuthorizationStateReady();
	__declspec(dllexport) Delegate* GetDelegateAuthorizationStateLoggingOut();
	__declspec(dllexport) Delegate* GetDelegateAuthorizationStateClosing();
	__declspec(dllexport) Delegate* GetDelegateAuthorizationStateClosed();
	__declspec(dllexport) Delegate* GetDelegateAuthorizationStateWaitCode();
	__declspec(dllexport) Delegate* GetDelegateAuthorizationStateWaitRegistration();
	__declspec(dllexport) Delegate* GetDelegateAuthorizationStateWaitPassword();
	__declspec(dllexport) Delegate* GetDelegateAuthorizationStateWaitPhoneNumber();
	__declspec(dllexport) Delegate* GetDelegateAuthorizationStateWaitEncryptionKey();
	__declspec(dllexport) Delegate* GetDelegateAuthorizationStateWaitTdlibParameters();

	__declspec(dllexport) void SetFunc(std::function<void(void)> func);
private:
	UETdApi* API;
};





