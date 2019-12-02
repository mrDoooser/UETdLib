#pragma once
#include "UETdApiStructs.h"
#include "Delegate.hpp"
#include <functional>
//#include "UETdApi.h"
//#include "pch.h"

#define DLL_EXPORT __declspec(dllexport)	

class UETdApi;

#ifdef __cplusplus		
extern "C"
{
#endif
	class UETdApiLibrary
	{
	public:
		__declspec(dllexport) UETdApiLibrary();
		
		__declspec(dllexport) ~UETdApiLibrary();

		__declspec(dllexport) bool Initialized();

		__declspec(dllexport) void Initialize(FTdApiInitParams *init_params);

		__declspec(dllexport) void ReadData();

		__declspec(dllexport) void SetFunc(std::function<void(void)> func);

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

	private:
		UETdApi* API;
	};
#ifdef __cplusplus
}
#endif




