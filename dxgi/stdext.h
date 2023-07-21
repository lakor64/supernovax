#pragma once

#include <functional>

/*!
* This class allows to use a GUID in a hash table for unordred_map
*/
template <>
struct std::hash<GUID>
{
	std::size_t operator()(GUID const& s) const noexcept
	{
		RPC_STATUS err;
		return UuidHash((UUID*) & s, &err);
	}
};
