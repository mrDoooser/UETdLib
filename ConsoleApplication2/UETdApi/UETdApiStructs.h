#pragma once
//#include "pch.h"
#include <string>

// overloaded
namespace detail {
	template <class... Fs>
	struct overload;

	template <class F>
	struct overload<F> : public F {
		explicit overload(F f) : F(f) {
		}
	};
	template <class F, class... Fs>
	struct overload<F, Fs...>
		: public overload<F>
		, overload<Fs...> {
		overload(F f, Fs... fs) : overload<F>(f), overload<Fs...>(fs...) {
		}
		using overload<F>::operator();
		using overload<Fs...>::operator();
	};
}  // namespace detail

template <class... F>
auto overloaded(F... f) {
	return detail::overload<F...>(f...);
}

struct FTdApiInitParams
{
	int32_t api_id_;
	std::string api_hash_;
	std::string system_language_code_ = "en";
	std::string device_model_ = "Desktop";
	std::string system_version_ = "Unknown";
	std::string application_version_ = "1.0";
	std::string database_directory_ = "UEChatTest";

};
