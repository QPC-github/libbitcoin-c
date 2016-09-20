/**
 * Copyright (c) 2011-2016 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/bitcoin/c/chain/output.h>
#include <bitcoin/bitcoin/c/internal/chain/output.hpp>

#include <bitcoin/bitcoin/c/internal/chain/point.hpp>
#include <bitcoin/bitcoin/c/internal/chain/script/script.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

BC_IMPLEMENT_VECTOR(output_list, bc_output_t,
    bc_destroy_output, libbitcoin::chain::output::list);

BC_IMPLEMENT_VECTOR(output_info_list, bc_output_info_t,
    bc_destroy_output_info, libbitcoin::chain::output_info::list);

extern "C" {

// Static functions
bc_output_t* bc_output_factory_from_data(const bc_data_chunk_t* data)
{
    return new bc_output_t{ new libbitcoin::chain::output(
        libbitcoin::chain::output::factory_from_data(*data->obj)) };
}
// Constructor
bc_output_t* bc_create_output()
{
    return new bc_output_t{ new libbitcoin::chain::output };
}
// Destructor
void bc_destroy_output(bc_output_t* self)
{
    delete self->obj;
    delete self;
}
// Member functions
bool bc_output_from_data(bc_output_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}
bc_data_chunk_t* bc_output_to_data(const bc_output_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}
bc_string_t* bc_output_to_string(const bc_output_t* self, uint32_t flags)
{
    return bc_create_string_StdString(self->obj->to_string(flags));
}
bool bc_output_is_valid(const bc_output_t* self)
{
    return self->obj->is_valid();
}
void bc_output_reset(bc_output_t* self)
{
    self->obj->reset();
}
uint64_t bc_output_serialized_size(const bc_output_t* self)
{
    return self->obj->serialized_size();
}
// Member variables
uint64_t bc_output_value(const bc_output_t* self)
{
    return self->obj->value;
}
void bc_output_set_value(bc_output_t* self, uint64_t value)
{
    self->obj->value = value;
}
bc_script_t* bc_output_script(const bc_output_t* self)
{
    return new bc_script_t{ new libbitcoin::chain::script(
        self->obj->script) };
}
void bc_output_set_script(bc_output_t* self, const bc_script_t* script)
{
    self->obj->script = *script->obj;
}

bc_output_info_t* bc_create_output_info()
{
    return new bc_output_info_t{ new libbitcoin::chain::output_info };
}
void bc_destroy_output_info(bc_output_info_t* self)
{
    delete self->obj;
    delete self;
}
bc_output_point_t* bc_output_info_point(const bc_output_info_t* self)
{
    return new bc_output_point_t{ new libbitcoin::chain::output_point(
        self->obj->point) };
}
void bc_output_info_set_point(bc_output_info_t* self,
    const bc_output_point_t* point)
{
    self->obj->point = *point->obj;
}
uint64_t bc_output_info_value(const bc_output_info_t* self)
{
    return self->obj->value;
}
void bc_output_info_set_value(bc_output_info_t* self, uint64_t value)
{
    self->obj->value = value;
}

} // extern C

