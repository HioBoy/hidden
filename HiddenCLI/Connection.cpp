#include "Connection.h"

using namespace std;

Connection::Connection(Arguments& args) :
	m_context(nullptr)
{
	wstring arg;

	if (!args.Probe(arg))
		return;

	do
	{
		if (arg == L"/gate")
		{
			args.SwitchToNext();
			if (!args.GetNext(m_deviceName))
				throw WException(-2, L"Error, mismatched argument for command 'gate'");
		}
		else
		{
			break;
		}
	} 
	while (args.Probe(arg));
}

Connection::~Connection()
{
	if (m_context)
		Hid_Destroy(m_context);
}

void Connection::Open()
{
	HidStatus status;
	const wchar_t* deviceName = nullptr;

	if (m_deviceName.size())
		deviceName = m_deviceName.c_str();

	status = Hid_Initialize(&m_context, deviceName);
	if (!HID_STATUS_SUCCESSFUL(status))
		throw WException(HID_STATUS_CODE(status), L"Error, can't connect to gate");
}

HidContext Connection::GetContext()
{
	return m_context;
}

