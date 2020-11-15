#include "stdafx.h"
#include <boost/algorithm/string/replace.hpp>
#include <boost/test/output/compiler_log_formatter.hpp>

using namespace std;

using boost::unit_test::test_unit_type;

class SpecLogFormatter :
	public boost::unit_test::output::compiler_log_formatter
{
	virtual void test_unit_start(std::ostream& os, boost::unit_test::test_unit const& tu) override
	{
		os << string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << endl;

		m_indent += 2;
	}



	virtual void test_unit_finish(ostream& /*os*/, boost::unit_test::test_unit const& /*tu*/, unsigned long /*elapsed*/) override
	{
		m_indent -= 2;
	}

	int m_indent = 0;
};

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}