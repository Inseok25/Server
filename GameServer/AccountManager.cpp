#include "pch.h"
#include "AccountManager.h"
#include "Usermanager.h"

void AccountManager::ProcessLogin()
{
	lock_guard<mutex> guard(_mutex);

	User* user = UserManager::Instance()->GetUser(100);
}
