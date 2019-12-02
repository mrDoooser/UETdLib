#include "pch.h"
#include "TestClass.h"

#include <td/telegram/Client.h>
#include <td/telegram/td_api.h>
#include <td/telegram/td_api.hpp>


float TestClass::GetValue()
{
	return 2.52f;
}

void TestClass::TdExample()
{
	td::Client::execute({ 0, td::td_api::make_object<td::td_api::setLogVerbosityLevel>(1) });
}
