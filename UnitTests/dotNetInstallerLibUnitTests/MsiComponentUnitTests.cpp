#include "StdAfx.h"
#include "MsiComponentUnitTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DVLib::UnitTests::MsiComponentUnitTests);

using namespace DVLib::UnitTests;

void MsiComponentUnitTests::testExec()
{
	MsiComponent component;
	component.package = L"msidoesntexist.msi"; 
	component.cmdparameters = L"/qn";
	component.Exec();
	// msi file cannot be opened
	CPPUNIT_ASSERT(1619 == component.Wait());
}
