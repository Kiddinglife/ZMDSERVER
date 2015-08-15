﻿#include "TestCases.h"
#include "net\net_common.h"

int main(int argc, char* argv[ ])
{
	/*
	std::ofstream os(( std::string(argv[0]) + ".log" ).c_str());
	My_Log_Msg_Callback lmc;
	ACE_Log_Msg_Callback *oldcallback = ACE_LOG_MSG->msg_callback(&lmc);
	lmc.oldcallback(oldcallback);
	My_Log_Msg_Backend lmb;     /// ACE_Log_Msg::CUSTOM
	ACE_Log_Msg_Backend *oldbackend = ACE_LOG_MSG->msg_backend(&lmb);
	lmb.oldbackend(oldbackend);
	ACE_LOG_MSG->open(prog_name,
	ACE_Log_Msg::STDERR | ACE_Log_Msg::OSTREAM4rf7y 
	| ACE_Log_Msg::MSG_CALLBACK | ACE_Log_Msg::CUSTOM,
	logger_key);
	*/
	//extern KBE_SRV_COMPONENT_TYPE g_componentType;

	g_componentType = CONSOLE;
	std::string nn(GET_KBE_SRV_COMPONENT_TYPE_NAME(g_componentType));
	std::ofstream normaln(( nn + ".log" ).c_str());
	n = &nn;
	normal = &normaln;
	ACE_LOG_MSG->msg_ostream(normal, 0);
	ACE_LOG_MSG->open("MyTest", ACE_Log_Msg::STDERR | ACE_Log_Msg::OSTREAM);
	TRACE("main");
	testing::InitGoogleTest(&argc, argv);
	TRACE_RETURN(RUN_ALL_TESTS());
}