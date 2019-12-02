#pragma once

#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "UETdApiStructs.h"
#include "Delegate.hpp"

#include <td/telegram/Client.h>
#include <td/telegram/td_api.h>
#include <td/telegram/td_api.hpp>



#define DLL_EXPORT __declspec(dllexport)	



#ifdef __cplusplus		
extern "C"
{
#endif
	namespace td_api = td::td_api;
	class UETdApi
	{
	public:
		__declspec(dllexport) UETdApi();
		__declspec(dllexport) ~UETdApi();

		//__declspec(dllexport)  float GetValue();

		//__declspec(dllexport) void TdExample();

		__declspec(dllexport) bool Initialized() { return bInitialized; };

		__declspec(dllexport) void Initialize(FTdApiInitParams *init_params);

		__declspec(dllexport) void ReadData();

		//void Initialize(std::string api_id_, std::string api_hash_, std::string system_language_code_ = "en", std::string device_model_ = "Desktop", std::string system_version_ = "Unknown", std::string application_version_ = "1.0", std::string database_directory_ = "UEChatTest");

		//void Initialize(FTdApiInitParams init_params);


	private:
		using Object = td::td_api::object_ptr<td::td_api::Object>;
		std::unique_ptr<td::Client> client_;

		bool bInitialized{ false };

		td::td_api::object_ptr<td::td_api::AuthorizationState> authorization_state_;
		bool are_authorized_{ false };
		bool need_restart_{ false };
		std::uint64_t current_query_id_{ 0 };
		std::uint64_t authentication_query_id_{ 0 };

		std::map<std::uint64_t, std::function<void(Object)>> handlers_;

		std::map<std::int32_t, td::td_api::object_ptr<td::td_api::user>> users_;

		std::map<std::int64_t, std::string> chat_title_;

		FTdApiInitParams *init_params_;

	private:
		void SetClient();
		
		void OnAuthorizationStateUpdate();
		void Restart();
		void SendQuery(td_api::object_ptr<td_api::Function> f, std::function<void(Object)> handler);
		std::uint64_t NextQueryID();
		auto CreateAuthenticationQueryHandler();
		void CheckAuthenticationError(Object object);
		void ProcessUpdate(td_api::object_ptr<td_api::Object> update);
		std::string GetUserName(std::int32_t user_id);
		void ProcessResponse(td::Client::Response response);

		// Authorization
		void AuthorizationStateReady();
		void AuthorizationStateLoggingOut();
		void AuthorizationStateClosing();
		void AuthorizationStateClosed();
		void AuthorizationStateWaitCode();
		void AuthorizationStateWaitRegistration();
		void AuthorizationStateWaitPassword();
		void AuthorizationStateWaitPhoneNumber();
		void AuthorizationStateWaitEncryptionKey();
		void AuthorizationStateWaitTdlibParameters();

	public:
		// callback 
		Delegate OnAuthorizationStateReady;
		Delegate OnAuthorizationStateLoggingOut;
		Delegate OnAuthorizationStateClosing;
		Delegate OnAuthorizationStateClosed;
		Delegate OnAuthorizationStateWaitCode;
		Delegate OnAuthorizationStateWaitRegistration;
		Delegate OnAuthorizationStateWaitPassword;
		Delegate OnAuthorizationStateWaitPhoneNumber;
		Delegate OnAuthorizationStateWaitEncryptionKey;
		Delegate OnAuthorizationStateWaitTdlibParameters;

		std::function<void(void)> func = nullptr;
		
	};

#ifdef __cplusplus
}
#endif


