#include "ki/dml/Field.h"
#include "ki/util/ValueBytes.h"
#include <algorithm>

namespace ki
{
namespace dml
{
	template <>
	void IntField::write_to(std::ostream &ostream) const
	{
		ValueBytes<INT> data;
		data.value = m_value;
		if (data.buff[0] == ((m_value & 0xFF000000) >> 24))
			std::reverse(&data.buff[0], &data.buff[4]);
		ostream.write(data.buff, sizeof(INT));
	}

	template <>
	void IntField::read_from(std::istream &istream)
	{
		ValueBytes<INT> data;
		istream.read(data.buff, sizeof(INT));
		if (istream.fail())
		{
			std::ostringstream oss;
			oss << "Not enough data was available to read INT value (" << m_name << ").";
			throw parse_error(oss.str());
		}

		ValueBytes<USHRT> endianness_check;
		endianness_check.value = 0x0102;
		if (endianness_check.buff[0] == 0x01)
			std::reverse(&data.buff[0], &data.buff[4]);

		m_value = data.value;
	}

	template <>
	size_t IntField::get_size() const
	{
		return sizeof(INT);
	}

	template <>
	const std::string IntField::get_type_name() const
	{
		return "INT";
	}
}
}
