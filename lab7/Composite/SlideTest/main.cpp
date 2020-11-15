// libpainter-tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/algorithm/string/replace.hpp>
#pragma warning (push, 3)
#include <boost/test/output/compiler_log_formatter.hpp>
#pragma warning (pop)

/*
Äàííûé êëàññ óïðàâëÿåò ôîðìàèòðîâàíèåì æóðíàëà çàïóñêà òåñòîâ
Äëÿ òîãî, ÷òîáû óâèäåòü ðåçóëüòàò, ïðèëîæåíèå äîëæíî áûòü çàïóùåíî ñ êëþ÷¸ì --log_level=test_suite (ñì. Post-build event â íàñòðîéêàõ ïðîåêòà)
*/
class SpecLogFormatter :
	public boost::unit_test::output::compiler_log_formatter
{
	virtual void test_unit_start(std::ostream& os, boost::unit_test::test_unit const& tu) override
	{
		// ïåðåä çàïóñêîì test unit-à âûâîäèì èìÿ test unit-à, çàìåíÿÿ ñèìâîë ïîä÷åðêèâàíèÿ íà ïðîáåë
		os << std::string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		// óâåëè÷èâàåì îòñòóï äëÿ âûâîäà èìåí ïîñëåäóþùèõ test unit-îâ â âèäå äåðåâà
		m_indent += 2;
	}

	virtual void test_unit_finish(std::ostream&/*os*/, boost::unit_test::test_unit const& /*tu*/, unsigned long /*elapsed*/) override
	{
		// ïî îêîí÷àíèè test unit-à óìåíüøàåì îòñòóï
		m_indent -= 2;
	}

	int m_indent = 0;
};

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	// Çàìåíèëè èìÿ log formatter íà ïîëüçîâàòåëüñêèé
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	// Èìÿ êîðíåâîãî íàáîðà òåñòîâ - All tests
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	// Çàïóñêàåì òåñòû, ïåðåäàâàÿ ïàðàìåòðû êîìàíäíîé ñòðîêè è êàñòîìíóþ ôóíêöèþ èíèöèàëèçàöèè òåñòîâ
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}