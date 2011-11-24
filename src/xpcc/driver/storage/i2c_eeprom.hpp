// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2009, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
// ----------------------------------------------------------------------------

#ifndef XPCC__I2C_EEPROM_HPP
#define XPCC__I2C_EEPROM_HPP

#include <xpcc/driver/connectivity/i2c/sync_master.hpp>

namespace xpcc
{
	/**
	 * \brief	I2C Eeprom
	 * 
	 * Compatible with the 24C256 family and other I2C eeprom with an
	 * 16-bit address pointer.
	 * 
	 * For example:
\verbatim
24xx256	- base address 0xA0
\endverbatim
	 * 
	 * \ingroup	storage
	 * \author	Fabian Greif
	 */
	template <typename I2C>
	class I2cEeprom
	{
	public:
		I2cEeprom(uint8_t address);
		
		/**
		 * \brief	Write byte
		 * 
		 * \param	address		Address
		 * \param	data		Data byte
		 * 
		 * \return	\c true	if the data could be written,
		 * 			\c false otherwise
		 */
		bool
		writeByte(uint16_t address, uint8_t data) const;
		
		/**
		 * \brief	Write block
		 * 
		 * \param	address		Address
		 * \param	data		Data block
		 * \param	bytes		Number of bytes to be written
		 * 
		 * \return	\c true	if the data could be written,
		 * 			\c false otherwise
		 */
		bool
		write(uint16_t address, const uint8_t *data, uint8_t bytes) const;
		
		/**
		 * \brief	Convenience function
		 *  
		 * Shortcut for:
		 * \code
		 * return write(address, static_cast<const uint8_t *>(&data), sizeof(T));
		 * \endcode
		 */
		template <typename T>
		inline bool
		write(uint16_t address, const T& data) const;
		
		/// Read byte
		bool
		readByte(uint16_t address, uint8_t &data) const;
		
		/// Read block
		bool
		read(uint16_t address, uint8_t *data, uint8_t bytes) const;
		
		/**
		 * \brief	Convenience function
		 * 
		 * Shortcut for:
		 * \code
		 * return read(address, static_cast<uint8_t *>(&data), sizeof(T));
		 * \endcode
		 */
		template <typename T>
		inline bool
		read(uint16_t address, T& data) const;

		/**
		 * \brief	Check if the device is accessable
		 *
		 * \return	\c true the device responds to its address,
		 * 			\c false otherwise, i.a. if bus was not free, statrcondition failed or device did not responded.
		 */
		bool
		isAvailable() const;
	private:
		const uint8_t deviceAddress;
		typedef xpcc::i2c::SyncMaster<I2C> MySyncI2C;
	};
}

#include "i2c_eeprom_impl.hpp"

#endif // XPCC__I2C_EEPROM_HPP