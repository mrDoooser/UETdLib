#include "pch.h"
#include "UETdApiL.h"

UETdApi::UETdApi()
{
	init_params_ = new FTdApiInitParams();
	SetClient();
}

UETdApi::~UETdApi()
{

}

void UETdApi::SetClient()
{
	td::Client::execute({ 0, td_api::make_object<td_api::setLogVerbosityLevel>(1) });
	client_ = std::make_unique<td::Client>();

}

void UETdApi::Initialize(FTdApiInitParams* init_params)
{
	//FTdApiInitParams new_params;
	this->init_params_ = init_params;
	bInitialized = true;
	//OnAuthorizationStateUpdate();

	//if (OnAuthorizationStateWaitEncryptionKey_ != nullptr)
	//	OnAuthorizationStateWaitEncryptionKey_();
	//OnAuthorizationStateReady();

	//ProcessResponse(client_->receive(10));
	Loop();
}

void UETdApi::Loop()
{
	while (true) {
		std::cerr << " UETdApi::Loop" << std::endl;
		if (need_restart_)
		{
			Restart();
		}
		else if (!are_authorized_)
		{
			ProcessResponse(client_->receive(10));
		}
		else
		{
			auto response = client_->receive(0);
			if (response.object) 
			{
				ProcessResponse(std::move(response));
			}
		}
	}
}

void UETdApi::Restart() {
	client_.reset();
	SetClient();
}

void UETdApi::SendQuery(td_api::object_ptr<td_api::Function> f, std::function<void(Object)> handler)
{
	auto query_id = NextQueryID();
	if (handler) {
		handlers_.emplace(query_id, std::move(handler));
	}
	client_->send({ query_id, std::move(f) });
}

void UETdApi::ProcessResponse(td::Client::Response response)
{
	if (!response.object) {
		return;
	}

	std::cerr << " --- response ---" << std::endl;
	std::cerr << response.id << " " << to_string(response.object) << std::endl;

	if (response.id == 0) {
		return ProcessUpdate(std::move(response.object));
	}
	auto it = handlers_.find(response.id);
	if (it != handlers_.end()) {
		it->second(std::move(response.object));
	}
}

std::string UETdApi::GetUserName(std::int32_t user_id)
{
	auto it = users_.find(user_id);
	if (it == users_.end()) {
		return "unknown user";
	}
	return it->second->first_name_ + " " + it->second->last_name_;
}

void UETdApi::ProcessUpdate(td_api::object_ptr<td_api::Object> update)
{
	td_api::downcast_call(
		*update, overloaded(
			[this](td_api::updateAuthorizationState& update_authorization_state) {
		authorization_state_ = std::move(update_authorization_state.authorization_state_);
		OnAuthorizationStateUpdate();
	},
			[this](td_api::updateNewChat& update_new_chat) {
		chat_title_[update_new_chat.chat_->id_] = update_new_chat.chat_->title_;
	},
		[this](td_api::updateChatTitle& update_chat_title) {
		chat_title_[update_chat_title.chat_id_] = update_chat_title.title_;
	},
		[this](td_api::updateUser& update_user) {
		auto user_id = update_user.user_->id_;
		users_[user_id] = std::move(update_user.user_);
	},
		[this](td_api::updateNewMessage& update_new_message) {
		auto chat_id = update_new_message.message_->chat_id_;
		auto sender_user_name = GetUserName(update_new_message.message_->sender_user_id_);
		std::string text;
		if (update_new_message.message_->content_->get_id() == td_api::messageText::ID) {
			text = static_cast<td_api::messageText&>(*update_new_message.message_->content_).text_->text_;
		}
		std::cerr << "Got message: [chat_id:" << chat_id << "] [from:" << sender_user_name << "] ["
			<< text << "]" << std::endl;
	},
		[](auto& update) {}));
}

auto UETdApi::CreateAuthenticationQueryHandler()
{
	return [this, id = authentication_query_id_](Object object) {
		if (id == authentication_query_id_) {
			CheckAuthenticationError(std::move(object));
		}
	};
}

void UETdApi::CheckAuthenticationError(Object object)
{
	if (object->get_id() == td_api::error::ID) {
		auto error = td::move_tl_object_as<td_api::error>(object);
		std::cerr << "Error: " << to_string(error);
		OnAuthorizationStateUpdate();
	}
}

void UETdApi::OnAuthorizationStateUpdate()
{
	authentication_query_id_++;

	td_api::downcast_call(
		*authorization_state_,
		overloaded(
			[this](td_api::authorizationStateReady&) {
		AuthorizationStateReady();
		//are_authorized_ = true;
		//std::cerr << "Got authorization" << std::endl;
	},
			[this](td_api::authorizationStateLoggingOut&) {
		AuthorizationStateLoggingOut();
		//are_authorized_ = false;
		//std::cerr << "Logging out" << std::endl;
	},
		[this](td_api::authorizationStateClosing&) {
		AuthorizationStateClosing();
		//std::cerr << "Closing" << std::endl; 
	},
		[this](td_api::authorizationStateClosed&) {
		AuthorizationStateClosed();
		//are_authorized_ = false;
		//need_restart_ = true;
		//std::cerr << "Terminated" << std::endl;
	},
		[this](td_api::authorizationStateWaitCode&) {
		AuthorizationStateWaitCode();
		//std::cerr << "Enter authentication code: ";
		//std::string code;
		//std::cin >> code;
		//SendQuery(td_api::make_object<td_api::checkAuthenticationCode>(code),
		//	CreateAuthenticationQueryHandler());
	},
		[this](td_api::authorizationStateWaitRegistration&) {
		AuthorizationStateWaitRegistration();
		//std::string first_name;
		//std::string last_name;
		//std::cerr << "Enter your first name: ";
		//std::cin >> first_name;
		//std::cerr << "Enter your last name: ";
		//std::cin >> last_name;
		//SendQuery(td_api::make_object<td_api::registerUser>(first_name, last_name),
		//	CreateAuthenticationQueryHandler());
	},
		[this](td_api::authorizationStateWaitPassword&) {
		AuthorizationStateWaitPassword();
		//std::cerr << "Enter authentication password: ";
		//std::string password;
		//std::cin >> password;
		//SendQuery(td_api::make_object<td_api::checkAuthenticationPassword>(password),
		//	CreateAuthenticationQueryHandler());
	},
		[this](td_api::authorizationStateWaitPhoneNumber&) {
		AuthorizationStateWaitPhoneNumber();
		//std::cerr << "Enter phone number: ";
		//std::string phone_number;
		//std::cin >> phone_number;
		//SendQuery(td_api::make_object<td_api::setAuthenticationPhoneNumber>(phone_number, nullptr),
		//	CreateAuthenticationQueryHandler());
	},
		[this](td_api::authorizationStateWaitEncryptionKey&) {
		AuthorizationStateWaitEncryptionKey();
		//std::cerr << "Enter encryption key or DESTROY: ";
		//std::string key;
		//std::getline(std::cin, key);
		//if (key == "DESTROY") {
		//	SendQuery(td_api::make_object<td_api::destroy>(), CreateAuthenticationQueryHandler());
		//}
		//else {
		//	SendQuery(td_api::make_object<td_api::checkDatabaseEncryptionKey>(std::move(key)),
		//		CreateAuthenticationQueryHandler());
		//}
	},
		[this](td_api::authorizationStateWaitTdlibParameters&) {
		AuthorizationStateWaitTdlibParameters();
		//auto parameters = td_api::make_object<td_api::tdlibParameters>();
		//parameters->database_directory_ = init_params_->database_directory_;
		//parameters->use_message_database_ = true;
		//parameters->use_secret_chats_ = true;
		//parameters->api_id_ = init_params_->api_id_; //1168701;
		//parameters->api_hash_ = init_params_->api_hash_; //"bb8f4331914e98f512c8bae1deed523e";
		//parameters->system_language_code_ = init_params_->system_language_code_; //"en";
		//parameters->device_model_ = init_params_->device_model_; //"Desktop";
		//parameters->system_version_ = init_params_->system_version_; //"Unknown";
		//parameters->application_version_ = init_params_->application_version_; //"1.0";
		//parameters->enable_storage_optimizer_ = true;
		//SendQuery(td_api::make_object<td_api::setTdlibParameters>(std::move(parameters)),
		//	CreateAuthenticationQueryHandler());
	}
		)
	);
}

std::uint64_t UETdApi::NextQueryID()
{
	return ++current_query_id_;
}

void UETdApi::AuthorizationStateReady()
{
	if (func != nullptr)
		func();

	OnAuthorizationStateReady();
	are_authorized_ = true;
	std::cerr << "Got authorization" << std::endl;
}

void UETdApi::AuthorizationStateLoggingOut()
{
	if (func != nullptr)
		func();

	OnAuthorizationStateLoggingOut();
	are_authorized_ = false;
	std::cerr << "Logging out" << std::endl;
}

void UETdApi::AuthorizationStateClosing()
{
	if (func != nullptr)
		func();

	OnAuthorizationStateClosing();
	std::cerr << "Closing" << std::endl;
}

void UETdApi::AuthorizationStateClosed()
{
	if (func != nullptr)
		func();
	OnAuthorizationStateClosed();
	are_authorized_ = false;
	need_restart_ = true;
	std::cerr << "Terminated" << std::endl;
}

void UETdApi::AuthorizationStateWaitCode()
{
	if (func != nullptr)
		func();
	OnAuthorizationStateWaitCode();
	std::cerr << "Enter authentication code: ";
	std::string code;
	std::cin >> code;
	SendQuery(td_api::make_object<td_api::checkAuthenticationCode>(code),
		CreateAuthenticationQueryHandler());
}

void UETdApi::AuthorizationStateWaitRegistration()
{
	if (func != nullptr)
		func();
	OnAuthorizationStateWaitRegistration();
	std::string first_name;
	std::string last_name;
	std::cerr << "Enter your first name: ";
	std::cin >> first_name;
	std::cerr << "Enter your last name: ";
	std::cin >> last_name;
	SendQuery(td_api::make_object<td_api::registerUser>(first_name, last_name),
		CreateAuthenticationQueryHandler());
}

void UETdApi::AuthorizationStateWaitPassword()
{
	if (func != nullptr)
		func();
	OnAuthorizationStateWaitPassword();
	std::cerr << "Enter authentication password: ";
	std::string password;
	std::cin >> password;
	SendQuery(td_api::make_object<td_api::checkAuthenticationPassword>(password),
		CreateAuthenticationQueryHandler());
}

void UETdApi::AuthorizationStateWaitPhoneNumber()
{
	if (func != nullptr)
		func();
	OnAuthorizationStateWaitPhoneNumber();
	std::cerr << "Enter phone number: ";
	std::string phone_number;
	std::cin >> phone_number;
	SendQuery(td_api::make_object<td_api::setAuthenticationPhoneNumber>(phone_number, nullptr),
		CreateAuthenticationQueryHandler());
}

void UETdApi::AuthorizationStateWaitEncryptionKey()
{
	if (func != nullptr)
		func();
	OnAuthorizationStateWaitEncryptionKey();
	std::cerr << "Enter encryption key or DESTROY: ";
	std::string key;
	std::getline(std::cin, key);
	if (key == "DESTROY") {
		SendQuery(td_api::make_object<td_api::destroy>(), CreateAuthenticationQueryHandler());
	}
	else {
		SendQuery(td_api::make_object<td_api::checkDatabaseEncryptionKey>(std::move(key)),
			CreateAuthenticationQueryHandler());
	}
}

void UETdApi::AuthorizationStateWaitTdlibParameters()
{
	OnAuthorizationStateWaitTdlibParameters();
	if (func != nullptr)
		func();
	auto parameters = td_api::make_object<td_api::tdlibParameters>();
	parameters->database_directory_ = init_params_->database_directory_;
	parameters->use_message_database_ = true;
	parameters->use_secret_chats_ = true;
	parameters->api_id_ = init_params_->api_id_; //1168701;
	parameters->api_hash_ = init_params_->api_hash_; //"bb8f4331914e98f512c8bae1deed523e";
	parameters->system_language_code_ = init_params_->system_language_code_; //"en";
	parameters->device_model_ = init_params_->device_model_; //"Desktop";
	parameters->system_version_ = init_params_->system_version_; //"Unknown";
	parameters->application_version_ = init_params_->application_version_; //"1.0";
	parameters->enable_storage_optimizer_ = true;
	SendQuery(td_api::make_object<td_api::setTdlibParameters>(std::move(parameters)),
		CreateAuthenticationQueryHandler());
}