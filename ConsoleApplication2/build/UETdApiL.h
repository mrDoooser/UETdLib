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


namespace td_api = td::td_api;
class UETdApi
{
public:
	UETdApi();
	~UETdApi();

	bool Initialized() { return bInitialized; };

	void Initialize(FTdApiInitParams* init_params);


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

	FTdApiInitParams* init_params_;

private:
	void SetClient();
	void Loop();
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



