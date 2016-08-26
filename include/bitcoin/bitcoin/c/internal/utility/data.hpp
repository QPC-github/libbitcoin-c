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
#ifndef LIBBITCOIN_C_INTERNAL_DATA_HPP
#define LIBBITCOIN_C_INTERNAL_DATA_HPP

#include <bitcoin/bitcoin/utility/data.hpp>

extern "C" {

struct bc_data_chunk_t
{
    libbitcoin::data_chunk* obj;
};

#define BC_IMPLEMENT_BYTE_ARRAY(typename) \
    \
    size_t bc_##typename##_size() \
    { \
        return libbitcoin::typename##_size; \
    } \
    bc_##typename##_t* bc_create_##typename() \
    { \
        return new bc_##typename##_t{ new libbitcoin::typename }; \
    } \
    bc_##typename##_t* bc_create_##typename##_Data(const uint8_t* data) \
    { \
        bc_##typename##_t* self = new bc_##typename##_t{ \
            new libbitcoin::typename }; \
        std::copy_n(data, bc_##typename##_size(), self->obj->data()); \
        return self; \
    } \
    void bc_destroy_##typename(bc_##typename##_t* self) \
    { \
        delete self->obj; \
        delete self; \
    } \
    uint8_t* bc_##typename##_data(bc_##typename##_t* self) \
    { \
        return self->obj->data(); \
    } \
    const uint8_t* bc_##typename##_cdata(const bc_##typename##_t* self) \
    { \
        return self->obj->data(); \
    }

}

#endif
