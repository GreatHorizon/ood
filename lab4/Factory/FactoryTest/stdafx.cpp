// stdafx.cpp : source file that includes just the standard includes
// libpainter-tests.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


// Ñîîáùàåì áèáëèîòåêå boost test, ÷òî ôóíêöèÿ main áóäåò ïðåäîñòàâëåíà íàìè (äëÿ ïðåäâàðèòåëüíîãî êîíôèãóðèðîâàíèÿ áèáëèîòåêè), 
// à íå ñãåíåðèðîâàíà boost-îì çà íàñ
#define BOOST_TEST_NO_MAIN 
// ïîäêëþ÷àåì ðåàëèçàöèþ boost test
#pragma warning (push, 3)
#pragma warning (disable:4702)
#include <boost/test/included/unit_test.hpp>
#pragma warning (pop)