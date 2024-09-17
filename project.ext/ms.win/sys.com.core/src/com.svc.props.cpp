/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Aug-2024 at 22:10:49.5257162, UTC+7, Novosibirsk, Sunday;
	This is Stroke Over project shared variant-struct-based property interface implementation file;
*/
#include "com.svc.props.h"

using namespace shared::sys_core::com;

/////////////////////////////////////////////////////////////////////////////

CProperty:: CProperty (_prop_id _n_id) : m_value(0), m_id(_n_id) {}
CProperty:: CProperty (const _variant_t& _value) : CProperty() { *this << _value; }
CProperty:: CProperty (const CProperty& _src) : CProperty() { *this = _src; }
CProperty:: CProperty (CProperty&& _victim) : CProperty() { *this = _victim; }
CProperty::~CProperty (void) {
	this->Clear();
}

/////////////////////////////////////////////////////////////////////////////

err_code    CProperty::Clear (void) {

	err_code n_result = TErrCodes::no_error;

	try {
		this->m_value.Clear();
	}
	catch (const _com_error _error){ n_result = _error.Error(); }

	return n_result;
}

_prop_id    CProperty::Id (void) const { return this->m_id; }
bool        CProperty::Id (_prop_id _n_id) {
	_n_id;
	const bool  b_changed = (_n_id != this->Id());
	if (true == b_changed)
		this->m_id = _n_id;
	return b_changed;
}

const
_variant_t& CProperty::Get (void) const { return this->m_value; }
err_code    CProperty::Set (const _variant_t& _value) {
	_value;
	err_code n_result = TErrCodes::no_error;

	try {
		this->m_value.Clear();
		this->m_value = _value;
	}
	catch (const _com_error _error) {
		n_result = _error.Error();
	}

	return n_result;
}

const
_variant_t& CProperty::Value(void) const { return this->Get(); }
err_code    CProperty::Value(const _variant_t& _value) { return this->Set(_value); }

/////////////////////////////////////////////////////////////////////////////

CProperty& CProperty::operator = (const CProperty& _src) { *this << _src.Get() << _src.Id(); return *this; }
CProperty& CProperty::operator = (CProperty&& _victim) {

	*this << _victim.Get();
	CProperty& victim_ = const_cast<CProperty&>(_victim); victim_.Clear();
	return *this;
}

CProperty& CProperty::operator <<(const _prop_id _n_id) { this->Id(_n_id); return *this; }

CProperty& CProperty::operator <<(const _variant_t& _value) { this->Set(_value); return *this; }
const
CProperty& CProperty::operator >>(_variant_t& _out) const {
	try {
		_out.Clear(); _out = this->Get();
	}
	catch(const _com_error) {}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////