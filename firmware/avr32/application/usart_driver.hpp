#ifndef USART_DRIVER_H
#define USART_DRIVER_H

class IEcgDataAcceptor;

namespace usart
{
	void init(IEcgDataAcceptor* acceptor);
	void reset();
	void enable();
	void disable();
}

#endif
