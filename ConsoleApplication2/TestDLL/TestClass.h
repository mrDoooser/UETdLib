#pragma once

#define DLL_EXPORT __declspec(dllexport)	

//#include <td/telegram/Client.h>
//#include <td/telegram/td_api.h>
//#include <td/telegram/td_api.hpp>

#ifdef __cplusplus		
extern "C"
{
#endif
	//namespace td_api = td::td_api;
	class TestClass
	{
	public:
		__declspec(dllexport)  float GetValue();

		__declspec(dllexport) void TdExample();

		//private:
		//	std::unique_ptr<td::Client>  client_;
	};

#ifdef __cplusplus
}
#endif