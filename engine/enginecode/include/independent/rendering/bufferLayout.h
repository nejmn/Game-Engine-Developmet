
/** \file shaderDataType.h */

#pragma once

#include "shaderDataType.h"
#include <vector>
/** 
*class Buffer Element
** \brief A class which holds data about a single element in a buffer layout
*/

namespace Engine
{
	class BufferElement
	{
	public:
		ShaderDataType m_dataType; //!<Type of data type
		uint32_t m_size; //!<size of the data
		uint32_t m_offset; //!< offset in bytes 
		bool m_normalised; //!< is it going to be normalised or not?

		BufferElement() {} //!<Default contructor
		BufferElement(ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType),
			m_size(SDT::size(dataType)),
			m_offset(0),
			m_normalised(normalised)
		{} //!< constructor with parameteres 
	};
	/**
	*class Buffer Layout
	** \brief Holds vertex buffer data
	*/
	class BufferLayout
	{
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& element) : m_elements(element) { calcStrideAndOffset(); }
		inline uint32_t getStride() const { return m_stride; }
		void addElement(BufferElement element);
		inline std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

	private:
		std::vector<BufferElement> m_elements; //!< Buffer elements
		uint32_t m_stride; //! Width of the bytes in a buffer line
		void calcStrideAndOffset(); //!<Calculate stride and offsets based on elements
	};


}