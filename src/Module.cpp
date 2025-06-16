#include <Module.hpp>

#include <App.hpp>

int Module::lastID = 0;

Module::Module(std::weak_ptr<App> app)
	:	app(app), ID(ID++)
{ }

int Module::GetID() const {
	return ID;
}

void Module::QueueFree()
{
	queuedForDeletion = true;
}

bool Module::QueuedForDeletion() const
{
	return queuedForDeletion;
}