#include <iostream>
#include "event/EventThread.hpp"

static void sayHello(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg)
{
	std::reference_wrapper<bricksvm::event::EventThread>	src = msg.getParameter<std::reference_wrapper<bricksvm::event::EventThread> >(0);

	std::cout << "msg : " << msg.getParameter<int>(1) << std::endl;

	src.get().emit("toto", thread, 10);
}

static void onFinished(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg)
{
	std::cout << "finished with status" << msg.getParameter<int>(1) << std::endl;
}

int main()
{
	try
	{
		bricksvm::event::EventThread	device1("test");
		bricksvm::event::EventThread	device2("blabla");

		device1.on("sayHello", &sayHello);
		device2.on("toto", &onFinished);
		std::cout << "device 1 : " << &device1 << std::endl;
		device1.emit("sayHello", device2, 5);
		_sleep(10000);
	}
	catch (std::runtime_error &err)
	{
		std::cout << err.what() << std::endl;
	}
	return 0;
}