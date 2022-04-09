#pragma once
#include<vector>

namespace gateway
{
	namespace common
	{
		//测点值类型枚举
		enum class ValueType :int8_t
		{
			kErrorType = 0,
			kBool,
			kChar,
			kByte,
			kShort,
			kWord,
			kInt,
			kDWord,
			kLong,
			kULong,
			kFloat,
			kDouble,
			kString,
			kFloatArray,
			kDoubleArray
		};

		//值状态类型枚举
		enum class ValueStatus :int8_t
		{
			kUnKnow = 0,		//未知错误
			kCollectGood,		//采集正常
			kCollectError,		//采集错误
			kUnInit,			//未初始化
			kCollectBad,		//采集坏点
			kTagNotExist,		//测点不存在
			
		};

#pragma pack(push)
#pragma pack(1)
		struct PtrValue {
			void*  ptr;
			uint32_t length;
			uint32_t capacity;
			PtrValue() :
				ptr(nullptr),
				length(0),
				capacity(0)
			{
			}
		};

		union ValueUnion {
			bool boolValue_;
			int8_t charValue_;
			uint8_t byteValue_;
			int16_t shortValue_;
			uint16_t wordValue_;
			int32_t intValue_;
			uint32_t dWordValue_;
			int64_t longValue_;
			uint64_t uLongValue_;
			float floatValue_;
			double doubleValue_;
			PtrValue ptrValue_;
			ValueUnion() :ptrValue_()
			{}
			ValueUnion(const bool &value) :boolValue_(value)
			{}
			ValueUnion(const int8_t &value) :charValue_(value)
			{}
			ValueUnion(const uint8_t &value) :byteValue_(value)
			{}
			ValueUnion(const int16_t &value) :shortValue_(value)
			{}
			ValueUnion(const uint16_t &value) :wordValue_(value)
			{}
			ValueUnion(const int32_t &value) :intValue_(value)
			{}
			ValueUnion(const uint32_t &value) :dWordValue_(value)
			{}
			ValueUnion(const int64_t &value) :longValue_(value)
			{}
			ValueUnion(const uint64_t &value) :uLongValue_(value)
			{}
			ValueUnion(const float &value) :floatValue_(value)
			{}
			ValueUnion(const double &value) :doubleValue_(value)
			{}
		};

		class TagValue {
		public:
			TagValue() :
				valueUnion_(),
				valueType_(ValueType::kErrorType),
				valueTime_(0),
				valueStatus_(ValueStatus::kUnInit)
			{
			}
			~TagValue()
			{
				if (valueType_ == ValueType::kString || valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.length = 0;
					valueUnion_.ptrValue_.capacity = 0;
				}
			}

			bool CheckValueOut(double maxValue, double minValue) const
			{
				switch (valueType_)
				{
				case ValueType::kBool:
					if (valueUnion_.boolValue_ > maxValue || valueUnion_.boolValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kChar:
					if (valueUnion_.charValue_ > maxValue || valueUnion_.charValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kByte:
					if (valueUnion_.byteValue_ > maxValue || valueUnion_.byteValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kShort:
					if (valueUnion_.shortValue_ > maxValue || valueUnion_.shortValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kWord:
					if (valueUnion_.wordValue_ > maxValue || valueUnion_.wordValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kInt:
					if (valueUnion_.intValue_ > maxValue || valueUnion_.intValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kDWord:
					if (valueUnion_.dWordValue_ > maxValue || valueUnion_.dWordValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kLong:
					if (valueUnion_.longValue_ > maxValue || valueUnion_.longValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kULong:
					if (valueUnion_.uLongValue_ > maxValue || valueUnion_.uLongValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kFloat:
					if (valueUnion_.floatValue_ > maxValue || valueUnion_.floatValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kDouble:
					if (valueUnion_.doubleValue_ > maxValue || valueUnion_.doubleValue_ < minValue)
					{
						return true;
					}
					break;
				case ValueType::kString:
				case ValueType::kFloatArray:
				case ValueType::kDoubleArray:

					break;
				default:
					break;
				}
				return false;
			}

			void Calc(float rate, float offset)
			{
				switch (valueType_)
				{
				case ValueType::kBool:
					valueUnion_.boolValue_ = valueUnion_.boolValue_*rate + offset;
					break;
				case ValueType::kChar:
					valueUnion_.doubleValue_ = valueUnion_.charValue_*rate + offset;
					valueType_ = ValueType::kDouble;
					break;
				case ValueType::kByte:
					valueUnion_.doubleValue_ = valueUnion_.byteValue_*rate + offset;
					valueType_ = ValueType::kDouble;
					break;
				case ValueType::kShort:
					valueUnion_.doubleValue_ = valueUnion_.shortValue_*rate + offset;
					valueType_ = ValueType::kDouble;
					break;
				case ValueType::kWord:
					valueUnion_.doubleValue_ = valueUnion_.wordValue_*rate + offset;
					valueType_ = ValueType::kDouble;
					break;
				case ValueType::kInt:
					valueUnion_.doubleValue_ = valueUnion_.intValue_*rate + offset;
					valueType_ = ValueType::kDouble;
					break;
				case ValueType::kDWord:
					valueUnion_.doubleValue_ = valueUnion_.dWordValue_*rate + offset;
					valueType_ = ValueType::kDouble;
					break;
				case ValueType::kLong:
					valueUnion_.doubleValue_ = valueUnion_.longValue_*rate + offset;
					valueType_ = ValueType::kDouble;
					break;
				case ValueType::kULong:
					valueUnion_.doubleValue_ = valueUnion_.uLongValue_*rate + offset;
					valueType_ = ValueType::kDouble;
					break;
				case ValueType::kFloat:
					valueUnion_.floatValue_ = valueUnion_.floatValue_*rate + offset;
					break;
				case ValueType::kDouble:
					valueUnion_.doubleValue_ = valueUnion_.doubleValue_*rate + offset;
					break;
				case ValueType::kString:
					break;
				case ValueType::kFloatArray:
				{
					float* floatPtr = static_cast<float*>(valueUnion_.ptrValue_.ptr);
					for (int index = 0; index < valueUnion_.ptrValue_.length / sizeof(float); ++index)
					{
						floatPtr[index] = floatPtr[index] * rate + offset;
					}
					break;
				}
				case ValueType::kDoubleArray:
				{
					double* doublePtr = static_cast<double*>(valueUnion_.ptrValue_.ptr);
					for (int index = 0; index < valueUnion_.ptrValue_.length / sizeof(double); ++index)
					{
						doublePtr[index] = doublePtr[index] * rate + offset;
					}
					break;
				}
				default:
					break;
				}
			}

			TagValue(const TagValue &value)
			{
				valueType_ = value.valueType_;
				valueTime_ = value.valueTime_;
				valueStatus_ = value.valueStatus_;
				switch (valueType_)
				{
				case ValueType::kBool:
					valueUnion_.boolValue_ = value.valueUnion_.boolValue_;
					break;
				case ValueType::kChar:
					valueUnion_.charValue_ = value.valueUnion_.charValue_;
					break;
				case ValueType::kByte:
					valueUnion_.byteValue_ = value.valueUnion_.byteValue_;
					break;
				case ValueType::kShort:
					valueUnion_.shortValue_ = value.valueUnion_.shortValue_;
					break;
				case ValueType::kWord:
					valueUnion_.wordValue_ = value.valueUnion_.wordValue_;
					break;
				case ValueType::kInt:
					valueUnion_.intValue_ = value.valueUnion_.intValue_;
					break;
				case ValueType::kDWord:
					valueUnion_.dWordValue_ = value.valueUnion_.dWordValue_;
					break;
				case ValueType::kLong:
					valueUnion_.longValue_ = value.valueUnion_.longValue_;
					break;
				case ValueType::kULong:
					valueUnion_.uLongValue_ = value.valueUnion_.uLongValue_;
					break;
				case ValueType::kFloat:
					valueUnion_.floatValue_ = value.valueUnion_.floatValue_;
					break;
				case ValueType::kDouble:
					valueUnion_.doubleValue_ = value.valueUnion_.doubleValue_;
					break;
				case ValueType::kString:
				case ValueType::kFloatArray:
				case ValueType::kDoubleArray:
					valueUnion_.ptrValue_.length = value.valueUnion_.ptrValue_.length;
					valueUnion_.ptrValue_.capacity = value.valueUnion_.ptrValue_.capacity;
					valueUnion_.ptrValue_.ptr = new char[valueUnion_.ptrValue_.capacity]{ 0 };
					memcpy_s(valueUnion_.ptrValue_.ptr, valueUnion_.ptrValue_.capacity, value.valueUnion_.ptrValue_.ptr, value.valueUnion_.ptrValue_.length);
					break;
				default:
					break;
				}
			}
			TagValue(TagValue &&value) noexcept
			{
				valueType_ = value.valueType_;
				value.valueType_ = ValueType::kErrorType;
				valueTime_ = value.valueTime_;
				valueStatus_ = value.valueStatus_;
				switch (valueType_)
				{
				case ValueType::kBool:
					valueUnion_.boolValue_ = value.valueUnion_.boolValue_;
					break;
				case ValueType::kChar:
					valueUnion_.charValue_ = value.valueUnion_.charValue_;
					break;
				case ValueType::kByte:
					valueUnion_.byteValue_ = value.valueUnion_.byteValue_;
					break;
				case ValueType::kShort:
					valueUnion_.shortValue_ = value.valueUnion_.shortValue_;
					break;
				case ValueType::kWord:
					valueUnion_.wordValue_ = value.valueUnion_.wordValue_;
					break;
				case ValueType::kInt:
					valueUnion_.intValue_ = value.valueUnion_.intValue_;
					break;
				case ValueType::kDWord:
					valueUnion_.dWordValue_ = value.valueUnion_.dWordValue_;
					break;
				case ValueType::kLong:
					valueUnion_.longValue_ = value.valueUnion_.longValue_;
					break;
				case ValueType::kULong:
					valueUnion_.uLongValue_ = value.valueUnion_.uLongValue_;
					break;
				case ValueType::kFloat:
					valueUnion_.floatValue_ = value.valueUnion_.floatValue_;
					break;
				case ValueType::kDouble:
					valueUnion_.doubleValue_ = value.valueUnion_.doubleValue_;
					break;
				case ValueType::kString:
				case ValueType::kFloatArray:
				case ValueType::kDoubleArray:
					valueUnion_.ptrValue_.length = value.valueUnion_.ptrValue_.length;
					valueUnion_.ptrValue_.capacity = value.valueUnion_.ptrValue_.capacity;
					valueUnion_.ptrValue_.ptr = value.valueUnion_.ptrValue_.ptr;
					value.valueUnion_.ptrValue_.ptr = nullptr;
					value.valueUnion_.ptrValue_.length = 0;
					value.valueUnion_.ptrValue_.capacity = 0;
					break;
				default:
					break;
				}
			}

			TagValue& operator=(const TagValue &value)
			{
				valueType_ = value.valueType_;
				valueTime_ = value.valueTime_;
				valueStatus_ = value.valueStatus_;
				switch (valueType_)
				{
				case ValueType::kBool:
					valueUnion_.boolValue_ = value.valueUnion_.boolValue_;
					break;
				case ValueType::kChar:
					valueUnion_.charValue_ = value.valueUnion_.charValue_;
					break;
				case ValueType::kByte:
					valueUnion_.byteValue_ = value.valueUnion_.byteValue_;
					break;
				case ValueType::kShort:
					valueUnion_.shortValue_ = value.valueUnion_.shortValue_;
					break;
				case ValueType::kWord:
					valueUnion_.wordValue_ = value.valueUnion_.wordValue_;
					break;
				case ValueType::kInt:
					valueUnion_.intValue_ = value.valueUnion_.intValue_;
					break;
				case ValueType::kDWord:
					valueUnion_.dWordValue_ = value.valueUnion_.dWordValue_;
					break;
				case ValueType::kLong:
					valueUnion_.longValue_ = value.valueUnion_.longValue_;
					break;
				case ValueType::kULong:
					valueUnion_.uLongValue_ = value.valueUnion_.uLongValue_;
					break;
				case ValueType::kFloat:
					valueUnion_.floatValue_ = value.valueUnion_.floatValue_;
					break;
				case ValueType::kDouble:
					valueUnion_.doubleValue_ = value.valueUnion_.doubleValue_;
					break;
				case ValueType::kString:
				case ValueType::kFloatArray:
				case ValueType::kDoubleArray:
					if (valueUnion_.ptrValue_.ptr != nullptr)
					{
						delete[] valueUnion_.ptrValue_.ptr;
					}
					valueUnion_.ptrValue_.length = value.valueUnion_.ptrValue_.length;
					valueUnion_.ptrValue_.capacity = value.valueUnion_.ptrValue_.capacity;
					valueUnion_.ptrValue_.ptr = new char[valueUnion_.ptrValue_.capacity]{ 0 };
					memcpy_s(valueUnion_.ptrValue_.ptr, valueUnion_.ptrValue_.capacity, value.valueUnion_.ptrValue_.ptr, value.valueUnion_.ptrValue_.length);
					break;
				default:
					break;
				}
				return *this;
			}
			TagValue& operator=(TagValue &&value)noexcept
			{
				valueType_ = value.valueType_;
				valueTime_ = value.valueTime_;
				valueStatus_ = value.valueStatus_;
				value.valueType_ = ValueType::kErrorType;
				switch (valueType_)
				{
				case ValueType::kBool:
					valueUnion_.boolValue_ = value.valueUnion_.boolValue_;
					break;
				case ValueType::kChar:
					valueUnion_.charValue_ = value.valueUnion_.charValue_;
					break;
				case ValueType::kByte:
					valueUnion_.byteValue_ = value.valueUnion_.byteValue_;
					break;
				case ValueType::kShort:
					valueUnion_.shortValue_ = value.valueUnion_.shortValue_;
					break;
				case ValueType::kWord:
					valueUnion_.wordValue_ = value.valueUnion_.wordValue_;
					break;
				case ValueType::kInt:
					valueUnion_.intValue_ = value.valueUnion_.intValue_;
					break;
				case ValueType::kDWord:
					valueUnion_.dWordValue_ = value.valueUnion_.dWordValue_;
					break;
				case ValueType::kLong:
					valueUnion_.longValue_ = value.valueUnion_.longValue_;
					break;
				case ValueType::kULong:
					valueUnion_.uLongValue_ = value.valueUnion_.uLongValue_;
					break;
				case ValueType::kFloat:
					valueUnion_.floatValue_ = value.valueUnion_.floatValue_;
					break;
				case ValueType::kDouble:
					valueUnion_.doubleValue_ = value.valueUnion_.doubleValue_;
					break;
				case ValueType::kString:
				case ValueType::kFloatArray:
				case ValueType::kDoubleArray: {
					if (valueUnion_.ptrValue_.ptr != nullptr)
					{
						delete[] valueUnion_.ptrValue_.ptr;
					}
					valueUnion_.ptrValue_.length = value.valueUnion_.ptrValue_.length;
					valueUnion_.ptrValue_.capacity = value.valueUnion_.ptrValue_.capacity;
					valueUnion_.ptrValue_.ptr = value.valueUnion_.ptrValue_.ptr;
					value.valueUnion_.ptrValue_.ptr = nullptr;
					value.valueUnion_.ptrValue_.length = 0;
					value.valueUnion_.ptrValue_.capacity = 0;
					break;
				}

				default:
					break;
				}
				return *this;
			}
			friend std::ostream& operator<<(std::ostream& os, const TagValue &value)
			{
				switch (value.valueType_)
				{
				case ValueType::kBool:
					os << "bool = " << value.valueUnion_.boolValue_;
					break;
				case ValueType::kChar:
					os << "char = " << value.valueUnion_.charValue_;
					break;
				case ValueType::kByte:
					os << "byte = " << value.valueUnion_.byteValue_;
					break;
				case ValueType::kShort:
					os << "short = " << value.valueUnion_.shortValue_;
					break;
				case ValueType::kWord:
					os << "word = " << value.valueUnion_.wordValue_;
					break;
				case ValueType::kInt:
					os << "int = " << value.valueUnion_.intValue_;
					break;
				case ValueType::kDWord:
					os << "dword = " << value.valueUnion_.dWordValue_;
					break;
				case ValueType::kLong:
					os << "long = " << value.valueUnion_.longValue_;
					break;
				case ValueType::kULong:
					os << "ulong = " << value.valueUnion_.uLongValue_;
					break;
				case ValueType::kFloat:
					os << "float = " << value.valueUnion_.floatValue_;
					break;
				case ValueType::kDouble:
					os << "double = " << value.valueUnion_.doubleValue_;
					break;
				case ValueType::kString:
					os << "string = " << static_cast<char*>(value.valueUnion_.ptrValue_.ptr);
					break;
				case ValueType::kFloatArray:
					for (int i = 0; i < value.valueUnion_.ptrValue_.length / sizeof(float); ++i)
					{
						os << "float[" << i << "] = " << static_cast<float*>(value.valueUnion_.ptrValue_.ptr)[i] << std::endl;
					}
					break;
				case ValueType::kDoubleArray:
					for (int i = 0; i < value.valueUnion_.ptrValue_.length / sizeof(double); ++i)
					{
						os << "double[" << i << "] = " << static_cast<double*>(value.valueUnion_.ptrValue_.ptr)[i] << std::endl;
					}
					break;
				default:
					break;
				}
				return os;
			}
			bool operator==(const TagValue &value) const
			{
				bool result = false;
				switch (valueType_)
				{
				case ValueType::kBool: {
					if (valueUnion_.boolValue_ == value.valueUnion_.boolValue_)
					{
						result = true;
					}
					break;
				}
				case ValueType::kChar: {
					if (valueUnion_.charValue_ == value.valueUnion_.charValue_)
					{
						result = true;
					}
					break;
				}
				case ValueType::kByte: {
					if (valueUnion_.byteValue_ == value.valueUnion_.byteValue_)
					{
						result = true;
					}
					break;
				}
				case ValueType::kShort: {
					if (valueUnion_.shortValue_ == value.valueUnion_.shortValue_)
					{
						result = true;
					}
					break;
				}

				case ValueType::kWord: {
					if (valueUnion_.wordValue_ == value.valueUnion_.wordValue_)
					{
						result = true;
					}
					break;
				}

				case ValueType::kInt: {
					if (valueUnion_.intValue_ == value.valueUnion_.intValue_)
					{
						result = true;
					}
					break;
				}

				case ValueType::kDWord: {
					if (valueUnion_.dWordValue_ == value.valueUnion_.dWordValue_)
					{
						result = true;
					}
					break;
				}

				case ValueType::kLong: {
					if (valueUnion_.longValue_ == value.valueUnion_.longValue_)
					{
						result = true;
					}
					break;
				}

				case ValueType::kULong: {
					if (valueUnion_.uLongValue_ == value.valueUnion_.uLongValue_)
					{
						result = true;
					}
					break;
				}

				case ValueType::kFloat: {
					if (valueUnion_.floatValue_ - value.valueUnion_.floatValue_ <= 0.001 && valueUnion_.floatValue_ - value.valueUnion_.floatValue_ >= -0.001)
					{
						result = true;
					}
					break;
				}

				case ValueType::kDouble: {
					if (valueUnion_.doubleValue_ - value.valueUnion_.doubleValue_ <= 0.00001 && valueUnion_.doubleValue_ - value.valueUnion_.doubleValue_ >= -0.00001)
					{
						result = true;
					}
					break;
				}

				case ValueType::kString:
				case ValueType::kFloatArray:
				case ValueType::kDoubleArray: {
					if (valueUnion_.ptrValue_.length != value.valueUnion_.ptrValue_.length)
						break;
					int length = valueUnion_.ptrValue_.length;
					int count = 0;
					while (count < length)
					{
						if (((char*)valueUnion_.ptrValue_.ptr)[count] != ((char*)value.valueUnion_.ptrValue_.ptr)[count])
						{
							return false;
						}
						++count;
					}
					result = true;
					break;
				}

				default:
					break;
				}
				return result;
			}

			void SetValue(const bool &boolValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kBool;
				valueUnion_.boolValue_ = boolValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const int8_t &charValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kChar;
				valueUnion_.charValue_ = charValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const uint8_t &byteValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kByte;
				valueUnion_.byteValue_ = byteValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const int16_t &shortValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kShort;
				valueUnion_.shortValue_ = shortValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const uint16_t &wordValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kWord;
				valueUnion_.wordValue_ = wordValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const int32_t &intValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kInt;
				valueUnion_.intValue_ = intValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const uint32_t &dWordValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kDWord;
				valueUnion_.dWordValue_ = dWordValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const int64_t &longValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kLong;
				valueUnion_.longValue_ = longValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const uint64_t &uLongValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kULong;
				valueUnion_.uLongValue_ = uLongValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const float &floatValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kFloat;
				valueUnion_.floatValue_ = floatValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const double &doubleValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				if (valueType_ == ValueType::kFloatArray || valueType_ == ValueType::kDoubleArray || valueType_ == ValueType::kString)
				{
					delete[] valueUnion_.ptrValue_.ptr;
					valueUnion_.ptrValue_.ptr = nullptr;
					valueUnion_.ptrValue_.capacity = 0;
					valueUnion_.ptrValue_.length = 0;
				}
				valueType_ = ValueType::kDouble;
				valueUnion_.doubleValue_ = doubleValue;
				valueTime_ = timestamp;
				valueStatus_ = status;
			}

			void SetValue(const std::string &strValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				try
				{
					if (valueType_ != ValueType::kFloatArray && valueType_ != ValueType::kDoubleArray && valueType_ != ValueType::kString)
					{
						valueUnion_.ptrValue_.ptr = nullptr;
						valueUnion_.ptrValue_.capacity = 0;
						valueUnion_.ptrValue_.length = 0;
					}

					if (valueUnion_.ptrValue_.capacity < strValue.size())
					{
						delete[] valueUnion_.ptrValue_.ptr;
						valueUnion_.ptrValue_.capacity = strValue.size() * 2;
						valueUnion_.ptrValue_.ptr = new char[valueUnion_.ptrValue_.capacity]{ 0 };
					}
					valueUnion_.ptrValue_.length = strValue.size();
					memcpy_s(valueUnion_.ptrValue_.ptr, valueUnion_.ptrValue_.capacity, strValue.data(), valueUnion_.ptrValue_.length);
					valueTime_ = timestamp;
					valueType_ = ValueType::kString;
					valueStatus_ = status;
				}
				catch (std::exception &e)
				{

				}
			}

			void SetValue(const std::vector<float> &floatArrayValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				try
				{
					if (valueType_ != ValueType::kFloatArray && valueType_ != ValueType::kDoubleArray && valueType_ != ValueType::kString)
					{
						valueUnion_.ptrValue_.ptr = nullptr;
						valueUnion_.ptrValue_.capacity = 0;
						valueUnion_.ptrValue_.length = 0;
					}

					if (valueUnion_.ptrValue_.capacity < floatArrayValue.size() * sizeof(float))
					{
						delete[] valueUnion_.ptrValue_.ptr;
						valueUnion_.ptrValue_.capacity = floatArrayValue.size() * sizeof(float) * 2;
						valueUnion_.ptrValue_.ptr = new char[valueUnion_.ptrValue_.capacity]{ 0 };
					}
					valueUnion_.ptrValue_.length = floatArrayValue.size() * sizeof(float);
					memcpy_s(valueUnion_.ptrValue_.ptr, valueUnion_.ptrValue_.capacity, floatArrayValue.data(), valueUnion_.ptrValue_.length);
					valueType_ = ValueType::kFloatArray;
					valueTime_ = timestamp;
					valueStatus_ = status;
				}
				catch (std::exception &e)
				{

				}
			}

			void SetValue(const float* floatPtr, const int &arraySize, const uint64_t &timestamp, const ValueStatus &status)
			{
				try
				{
					if (valueType_ != ValueType::kFloatArray && valueType_ != ValueType::kDoubleArray && valueType_ != ValueType::kString)
					{
						valueUnion_.ptrValue_.ptr = nullptr;
						valueUnion_.ptrValue_.capacity = 0;
						valueUnion_.ptrValue_.length = 0;
					}

					if (valueUnion_.ptrValue_.capacity < arraySize * sizeof(float))
					{
						delete[] valueUnion_.ptrValue_.ptr;
						valueUnion_.ptrValue_.capacity = arraySize * sizeof(float) * 2;
						valueUnion_.ptrValue_.ptr = new char[valueUnion_.ptrValue_.capacity]{ 0 };
					}
					valueUnion_.ptrValue_.length = arraySize * sizeof(float);
					memcpy_s(valueUnion_.ptrValue_.ptr, valueUnion_.ptrValue_.capacity, floatPtr, valueUnion_.ptrValue_.length);
					valueType_ = ValueType::kFloatArray;
					valueTime_ = timestamp;
					valueStatus_ = status;
				}
				catch (std::exception &e)
				{

				}
			}

			
			void SetValue(const std::vector<double> &doubleArrayValue, const uint64_t &timestamp, const ValueStatus &status)
			{
				try
				{
					if (valueType_ != ValueType::kFloatArray && valueType_ != ValueType::kDoubleArray && valueType_ != ValueType::kString)
					{
						valueUnion_.ptrValue_.ptr = nullptr;
						valueUnion_.ptrValue_.capacity = 0;
						valueUnion_.ptrValue_.length = 0;
					}

					if (valueUnion_.ptrValue_.capacity < doubleArrayValue.size() * sizeof(double))
					{
						delete[] valueUnion_.ptrValue_.ptr;
						valueUnion_.ptrValue_.capacity = doubleArrayValue.size() * sizeof(double) * 2;
						valueUnion_.ptrValue_.ptr = new char[valueUnion_.ptrValue_.capacity]{ 0 };
					}
					valueUnion_.ptrValue_.length = doubleArrayValue.size() * sizeof(double);
					memcpy_s(valueUnion_.ptrValue_.ptr, valueUnion_.ptrValue_.capacity, doubleArrayValue.data(), valueUnion_.ptrValue_.length);
					valueType_ = ValueType::kDoubleArray;
					valueTime_ = timestamp;
					valueStatus_ = status;
				}
				catch (std::exception &e)
				{

				}
			}

			void SetValue(const double* doublePtr,const int &doubleSize, const uint64_t &timestamp, const ValueStatus &status)
			{
				try
				{
					if (valueType_ != ValueType::kFloatArray && valueType_ != ValueType::kDoubleArray && valueType_ != ValueType::kString)
					{
						valueUnion_.ptrValue_.ptr = nullptr;
						valueUnion_.ptrValue_.capacity = 0;
						valueUnion_.ptrValue_.length = 0;
					}

					if (valueUnion_.ptrValue_.capacity < doubleSize * sizeof(double))
					{
						delete[] valueUnion_.ptrValue_.ptr;
						valueUnion_.ptrValue_.capacity = doubleSize * sizeof(double) * 2;
						valueUnion_.ptrValue_.ptr = new char[valueUnion_.ptrValue_.capacity]{ 0 };
					}
					valueUnion_.ptrValue_.length = doubleSize * sizeof(double);
					memcpy_s(valueUnion_.ptrValue_.ptr, valueUnion_.ptrValue_.capacity, doublePtr, valueUnion_.ptrValue_.length);
					valueType_ = ValueType::kDoubleArray;
					valueTime_ = timestamp;
					valueStatus_ = status;
				}
				catch (std::exception &e)
				{

				}
			}

			
			void GetValue(bool &value, uint64_t &timestamp, ValueStatus &status) const
			{
				value = valueUnion_.boolValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(int8_t &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value = valueUnion_.charValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(uint8_t &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value = valueUnion_.byteValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(int16_t &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value = valueUnion_.shortValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(uint16_t &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value = valueUnion_.wordValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(int32_t &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value = valueUnion_.intValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(uint32_t &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value = valueUnion_.dWordValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(int64_t &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value = valueUnion_.longValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(uint64_t &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value = valueUnion_.uLongValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(float &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value = valueUnion_.floatValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(double &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value = valueUnion_.doubleValue_;
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(std::string &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value.clear();
				value.reserve(valueUnion_.ptrValue_.length);
				value.append(static_cast<char*>(valueUnion_.ptrValue_.ptr), valueUnion_.ptrValue_.length);
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(std::vector<float> &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value.clear();
				int num = valueUnion_.ptrValue_.length / sizeof(float);
				value.reserve(num);
				for (int i = 0; i < num; ++i)
				{
					value.emplace_back(static_cast<float*>(valueUnion_.ptrValue_.ptr)[i]);
				}
				timestamp = valueTime_;
				status = valueStatus_;
			}
			void GetValue(std::vector<double> &value, uint64_t &timestamp, ValueStatus &status)const
			{
				value.clear();
				int num = valueUnion_.ptrValue_.length / sizeof(double);
				value.reserve(num);
				for (int i = 0; i < num; ++i)
				{
					value.emplace_back(static_cast<double*>(valueUnion_.ptrValue_.ptr)[i]);
				}
				timestamp = valueTime_;
				status = valueStatus_;
			}
			bool GetBoolValue() const
			{
				return valueUnion_.boolValue_;
			}
			int8_t GetCharValue() const
			{
				return valueUnion_.charValue_;
			}
			uint8_t GetByteValue() const
			{
				return valueUnion_.byteValue_;
			}
			int16_t GetShortValue() const
			{
				return valueUnion_.shortValue_;
			}
			uint16_t GetWordValue() const
			{
				return valueUnion_.wordValue_;
			}
			int32_t GetIntValue() const
			{
				return valueUnion_.intValue_;
			}
			uint32_t GetDWordValue() const
			{
				return valueUnion_.dWordValue_;
			}
			int64_t GetLongValue() const
			{
				return valueUnion_.longValue_;
			}
			uint64_t GetULongValue() const
			{
				return valueUnion_.uLongValue_;
			}
			float GetFloatValue() const
			{
				return valueUnion_.floatValue_;
			}
			double GetDoubleValue() const
			{
				return valueUnion_.doubleValue_;
			}
			std::string GetStringValue() const
			{
				if (valueType_ != ValueType::kString)
				{
					return "";
				}
				return std::string(static_cast<char*>(valueUnion_.ptrValue_.ptr), valueUnion_.ptrValue_.length);
			}

			std::vector<float> GetFloatVectorArrayValue() const
			{
				std::vector<float> value;
				if (valueType_ != ValueType::kFloatArray)
				{
					return value;
				}
				value.clear();
				int num = valueUnion_.ptrValue_.length / sizeof(float);
				value.reserve(num);
				for (int i = 0; i < num; ++i)
				{
					value.emplace_back(static_cast<float*>(valueUnion_.ptrValue_.ptr)[i]);
				}
				return std::move(value);
			}

			std::vector<double> GetDoubleVectorArrayValue() const
			{
				std::vector<double> value;
				if (valueType_ != ValueType::kDoubleArray)
				{
					return value;
				}
				value.clear();
				int num = valueUnion_.ptrValue_.length / sizeof(double);
				value.reserve(num);
				for (int i = 0; i < num; ++i)
				{
					value.emplace_back(static_cast<double*>(valueUnion_.ptrValue_.ptr)[i]);
				}
				return std::move(value);
			}

			ValueType GetValueType() const
			{
				return valueType_;
			}

			ValueStatus GetValueStatus() const
			{
				return valueStatus_;
			}

			uint64_t GetValueTime() const
			{
				return valueTime_;
			}
			//转换为string用于存储至缓存或历史库
			std::string ToSaveString()
			{
				std::string dataStr;
				uint16_t size = 0;
				dataStr.append(reinterpret_cast<char*>(&valueType_), sizeof(ValueType));
				switch (valueType_)
				{
				case ValueType::kBool:
					size = sizeof(bool);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.boolValue_), size);
					break;
				case ValueType::kChar:
					size = sizeof(int8_t);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.charValue_), size);
					break;
				case ValueType::kByte:
					size = sizeof(uint8_t);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.byteValue_), size);
					break;
				case ValueType::kShort:
					size = sizeof(int16_t);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.shortValue_), size);
					break;
				case ValueType::kWord:
					size = sizeof(uint16_t);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.wordValue_), size);
					break;
				case ValueType::kInt:
					size = sizeof(int32_t);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.intValue_), size);
					break;
				case ValueType::kDWord:
					size = sizeof(uint32_t);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.dWordValue_), size);
					break;
				case ValueType::kLong:
					size = sizeof(int64_t);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.longValue_), size);
					break;
				case ValueType::kULong:
					size = sizeof(uint64_t);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.uLongValue_), size);
					break;
				case ValueType::kFloat:
					size = sizeof(float);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.floatValue_), size);
					break;
				case ValueType::kDouble:
					size = sizeof(double);
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(&valueUnion_.doubleValue_), size);
					break;
				case ValueType::kString:
				case ValueType::kFloatArray:
				case ValueType::kDoubleArray:
					size = valueUnion_.ptrValue_.length;
					dataStr.append(reinterpret_cast<char*>(&size), sizeof(size));
					dataStr.append(reinterpret_cast<char*>(valueUnion_.ptrValue_.ptr), size);
					break;
				case ValueType::kErrorType:
					break;
				default:
					break;
				}
				return std::move(dataStr);
			}

			void FormSaveString(const std::string &dataStr)
			{
				if (dataStr.size() < sizeof(ValueType) + sizeof(uint16_t))
				{
					return;
				}
				auto ptr = dataStr.data();
				uint16_t size = 0;
				valueType_ = *reinterpret_cast<const ValueType*>(ptr);
				ptr += sizeof(ValueType);
				size = *reinterpret_cast<const uint16_t*>(ptr);
				ptr += sizeof(uint16_t);
				switch (valueType_)
				{
				case ValueType::kBool:
					valueUnion_.boolValue_ = *reinterpret_cast<const bool*>(ptr);
					break;
				case ValueType::kChar:
					valueUnion_.charValue_ = *reinterpret_cast<const int8_t*>(ptr);
					break;
				case ValueType::kByte:
					valueUnion_.byteValue_ = *reinterpret_cast<const uint8_t*>(ptr);
					break;
				case ValueType::kShort:
					valueUnion_.shortValue_ = *reinterpret_cast<const int16_t*>(ptr);
					break;
				case ValueType::kWord:
					valueUnion_.wordValue_ = *reinterpret_cast<const uint16_t*>(ptr);
					break;
				case ValueType::kInt:
					valueUnion_.intValue_ = *reinterpret_cast<const int32_t*>(ptr);
					break;
				case ValueType::kDWord:
					valueUnion_.dWordValue_ = *reinterpret_cast<const uint32_t*>(ptr);
					break;
				case ValueType::kLong:
					valueUnion_.longValue_ = *reinterpret_cast<const int64_t*>(ptr);
					break;
				case ValueType::kULong:
					valueUnion_.uLongValue_ = *reinterpret_cast<const uint64_t*>(ptr);
					break;
				case ValueType::kFloat:
					valueUnion_.floatValue_ = *reinterpret_cast<const float*>(ptr);
					break;
				case ValueType::kDouble:
					valueUnion_.doubleValue_ = *reinterpret_cast<const double*>(ptr);
					break;
				case ValueType::kString:
				case ValueType::kFloatArray:
				case ValueType::kDoubleArray:
					if (valueUnion_.ptrValue_.ptr != nullptr)
					{
						delete[] valueUnion_.ptrValue_.ptr;
					}
					valueUnion_.ptrValue_.ptr = new char[size] {0};
					memcpy_s(valueUnion_.ptrValue_.ptr, size, ptr, size);
					valueUnion_.ptrValue_.length = size;
					break;
				case ValueType::kErrorType:
					break;
				default:
					break;
				}

			}

		private:
			ValueUnion valueUnion_;
			ValueType valueType_;
			uint64_t valueTime_;
			ValueStatus valueStatus_;
		};
#pragma pack(pop)
		
	}//common
	
}//gateway

