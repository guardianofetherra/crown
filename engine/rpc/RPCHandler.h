/*
Copyright (c) 2013 Daniele Bartolini, Michele Rossi
Copyright (c) 2012 Daniele Bartolini, Simone Boscaratto

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "Hash.h"
#include "JSONParser.h"
#include "StringUtils.h"

namespace crown
{

class TCPClient;
class RPCServer;

class RPCHandler
{
public:

						RPCHandler(const char* type);
	uint32_t			type() const { return m_type; }
	virtual void		execute_command(RPCServer* server, TCPClient* client, const char* message) = 0;

private:

	uint32_t			m_type;
	RPCHandler*			m_next;

private:

	friend class		RPCServer;
};

//-----------------------------------------------------------------------------
RPCHandler::RPCHandler(const char* type)
	: m_type(hash::murmur2_32(type, string::strlen(type), 0)), m_next(NULL)
{
}

class RPCScriptHandler : public RPCHandler
{
public:

			RPCScriptHandler();
	void	execute_command(RPCServer* server, TCPClient* client, const char* message);
};

class RPCStatsHandler : public RPCHandler
{
public:

			RPCStatsHandler();
	void	execute_command(RPCServer* server, TCPClient* client, const char* message);
};

class RPCPingHandler : public RPCHandler
{
public:

			RPCPingHandler();
	void	execute_command(RPCServer* server, TCPClient* client, const char* message);
};

} // namespace crown
