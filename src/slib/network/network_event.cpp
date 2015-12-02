#include "../../../inc/slib/network/event.h"
#include "../../../inc/slib/core/thread.h"

SLIB_NETWORK_NAMESPACE_BEGIN
SocketEvent::SocketEvent()
{
}

SocketEvent::~SocketEvent()
{
}

sl_bool SocketEvent::setup(sl_uint32 events)
{
	Ref<Socket> socket = m_socket;
	if (socket.isNotNull() && socket->isOpened()) {
		if (socket->setNonBlockingMode(sl_true)) {
			return __setup(events);
		}
	}
	return sl_false;
}

sl_uint32 SocketEvent::waitEvents(sl_int32 timeout)
{
	sl_uint32 events;
	Ref<SocketEvent> ev = this;
	if (waitMultipleEvents(&ev, &events, 1, timeout)) {
		return events;
	}
	return 0;
}

sl_bool SocketEvent::__wait(sl_int32 timeout)
{
	if (waitEvents(timeout) != 0) {
		return sl_true;
	}
	return sl_false;
}

#define _MAX_WAIT_EVENTS 64
sl_bool SocketEvent::waitMultipleEvents(const Ref<SocketEvent>* events, sl_uint32* status, sl_uint32 count, sl_int32 timeout)
{
	if (count == 0 || count > _MAX_WAIT_EVENTS) { // WSA_MAXIMUM_WAIT_EVENTS
		return sl_false;
	}
	Ref<Thread> thread = Thread::getCurrent();
	if (thread.isNotNull()) {
		if (thread->isStopping()) {
			return sl_false;
		}
		thread->setWaitingEvent(events[0].get());
	}
	sl_bool ret = __waitMultipleEvents(events, status, count, timeout);
	if (thread.isNotNull()) {
		thread->clearWaitingEvent();
	}
	return ret;
}

Ref<SocketEvent> SocketEvent::create(const Ref<Socket>& socket, sl_uint32 events)
{
	Ref<SocketEvent> ev = SocketEvent::create(socket);
	if (ev.isNotNull()) {
		if (ev->setup(events)) {
			return ev;
		}
	}
	return Ref<SocketEvent>::null();
}

Ref<SocketEvent> SocketEvent::createRead(const Ref<Socket>& socket)
{
	return SocketEvent::create(socket, eventRead | eventClose);
}

Ref<SocketEvent> SocketEvent::createWrite(const Ref<Socket>& socket)
{
	return SocketEvent::create(socket, eventWrite | eventClose);
}

Ref<SocketEvent> SocketEvent::createReadWrite(const Ref<Socket>& socket)
{
	return SocketEvent::create(socket, eventRead | eventWrite | eventClose);
}
SLIB_NETWORK_NAMESPACE_END
