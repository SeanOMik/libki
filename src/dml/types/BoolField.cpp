#include "ki/dml/Field.h"
#include "ki/util/ValueBytes.h"

namespace ki
{
namespace dml
{
	template <>
	void BoolField::write_to(std::ostream &ostream) const
	{
		ValueBytes<BOOL> data;
		data.value = m_value;
		ostream.write(data.buff, sizeof(BOOL));
	}

	template <>
	void BoolField::read_from(std::istream &istream)
	{
		ValueBytes<BOOL> data;
		istream.read(data.buff, sizeof(BOOL));
		if (istream.fail())
		{
			std::ostringstream oss;
			oss << "Not enough data was available to read BOOL value (" << m_name << ").";
			throw parse_error(oss.str());
		}
		m_value = data.value;
	}

	template <>
	size_t BoolField::get_size() const
	{
		return sizeof(BOOL);
	}

	template <>
	const std::string BoolField::get_type_name() const
	{
		return "BOOL";
	}

	template <>
	std::string BoolField::get_value_string() const
	{
		std::ostringstream oss;
		oss << (int16_t)m_value;
		return oss.str();
	}

	template <>
	void BoolField::set_value_from_string(std::string value)
	{
		std::istringstream iss(value);
		int16_t temp = 0;
		iss >> temp;
		m_value = temp & 0xFF;
	}
}
}