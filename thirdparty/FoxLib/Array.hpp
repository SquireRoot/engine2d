/*Convenient array types.*/
#pragma once
#include "Types.hpp"

#include <cstring>

namespace foxlib {
	
//Simple array with no memory management
template<typename elemType>
struct array {
	elemType* b;
	fuint len;

	array<elemType>& initEmpty() {
		this->len = 0;
		return *this;
	}

	elemType& at(fuint indx) const {
		assert(indx < this->len);
		return this->b[indx];
	}

	elemType& atUnbounded(fuint indx) const {
		return this->b[indx];
	}

	elemType& operator[](fuint indx) const {
		return this->at(indx);
	}

	bool operator==(const array<elemType>& other) const {
		if (this->len == other.len) {
			return std::memcmp(this->b, other.b, this->len*sizeof(elemType)) == 0;
		}
		return false;
	}

	bool isEmpty() {
		return this->len == 0;
	}
	
	array<elemType> subArray(fuint indxStart, fuint indxEndExcl) {
		array<elemType> sub;
		sub.b = this->b + indxStart;
		sub.len = indxEndExcl - indxStart;
		return sub;
	}
		
	array<elemType> subArray(fuint indxEndExcl) {
		return this->subArray(0, indxEndExcl);
	}
};

}
