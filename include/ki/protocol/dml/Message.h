#pragma once
#include "MessageHeader.h"
#include "../../util/Serializable.h"
#include "../../dml/Record.h"
#include <iostream>

namespace ki
{
namespace protocol
{
namespace dml
{
	class MessageTemplate;

	class Message final : public util::Serializable
	{
	public:
		Message(const MessageTemplate *message_template = nullptr);
		virtual ~Message();

		const MessageTemplate *get_template() const;
		void set_template(const MessageTemplate *message_template);

		ki::dml::Record *get_record();
		const ki::dml::Record *get_record() const;

		ki::dml::FieldBase *get_field(std::string name);
		const ki::dml::FieldBase *get_field(std::string name) const;

		uint8_t get_service_id() const;
		uint8_t get_type() const;
		uint16_t get_message_size() const;
		std::string get_handler() const;
		uint8_t get_access_level() const;

		void write_to(std::ostream &ostream) const override final;
		void read_from(std::istream &istream) override final;
		size_t get_size() const override final;

		void set_raw_data(const std::vector<char>& data);
		const std::vector<char> get_raw_data() const {
			return m_raw_data;
		}

		void set_header(MessageHeader header) {
			m_header = header;
		}

		void set_record(ki::dml::Record* record) {
			m_record = record;
		}

		void set_header_consumed(bool header_consumed) {
			m_header_consumed = header_consumed;
		}
	private:
		const MessageTemplate *m_template;
		ki::dml::Record *m_record;
		bool m_header_consumed = false;

		// This is used to store raw data when a Message is
		// constructed without a MessageTemplate.
		MessageHeader m_header;
		std::vector<char> m_raw_data;
	};
}
}
}