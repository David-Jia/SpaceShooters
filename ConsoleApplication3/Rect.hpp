//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2015 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef SFML_RECT_HPP
#define SFML_RECT_HPP

// Headers
#include <SFML/System/Vector2.hpp>
#include <algorithm>


namespace sf
{
	template <typename T>
	class Rect
	{
		public:
			
			Rect();

			Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight);
			
			Rect(const Vector2<T>& position, const Vector2<T>& size);
			
			template <typename U>
			explicit Rect(const Rect<U>& rectangle);
			
			bool contains(T x, T y) const;
			
			bool contains(const Vector2<T>& point) const;
			
			bool intersects(const Rect<T>& rectangle) const;
			
			bool intersects(const Rect<T>& rectangle, Rect<T>& intersection) const;
			
			// Member data
			T left;
			T top;
			T width;
			T height;
	};

template <typename T>
bool operator ==(const Rect<T>& left, const Rect<T>& right);

template <typename T>
bool operator !=(const Rect<T>& left, const Rect<T>& right);
	
#include <SFML/Graphics/Rect.inl>
		
// Create typedefs for the most common types
typedef Rect<int>   IntRect;
typedef Rect<float> FloatRect;

} // namespace sf

#endif // SFML_RECT_HPP