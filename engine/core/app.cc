//------------------------------------------------------------------------------
// app.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "app.h"
#include <cassert>

namespace Core
{

//------------------------------------------------------------------------------
/**
*/
App::App() :
	isOpen(false)
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
App::~App()
{
	// empty
}


//------------------------------------------------------------------------------
/**
*/
bool
App::Open()
{
	assert(!this->isOpen);
	this->isOpen = true;
	return true;
}

//------------------------------------------------------------------------------
/**
*/
void
App::Run()
{
	// override in subclass
}

//------------------------------------------------------------------------------
/**
*/
void
App::Close()
{
	assert(this->isOpen);
	this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
*/
void
App::Exit()
{

}

} // namespace Application