#pragma once
#include <ynbt/Internal/YNBTByteStream.hpp>
#include <absl/container/flat_hash_map.h>
#include <ynbt/Internal/YNBTWriterConcept.hpp>
#include <variant>
#include <functional>

namespace YNBT
{
	class EndTag;
	class ByteTag;
	class ShortTag;
	class IntTag;
	class LongTag;
	class FloatTag;
	class DoubleTag;
	class ByteArrayTag;
	class StringTag;
	class ListTag;
	class CompoundTag;
	class IntArrayTag;
	class LongArrayTag;

	enum class TagID
	{
		EndTag,
		ByteTag,
		ShortTag,
		IntTag,
		LongTag,
		FloatTag,
		DoubleTag,
		ByteArrayTag,
		StringTag,
		ListTag,
		CompoundTag,
		IntArrayTag,
		LongArrayTag
	};

	using Tag = std::variant<EndTag, ByteTag, ShortTag, IntTag, LongTag, FloatTag, DoubleTag, ByteArrayTag, StringTag, ListTag, CompoundTag, IntArrayTag, LongArrayTag>;

	static Tag TagFromId(uint8_t  id);

	class EndTag
	{
	public:
		EndTag() {}
		template<NBTInterfaceImpl T>
		EndTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI8(0, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		EndTag&& Read(BinaryStream<uint8_t>& stream)
		{
			T::ReadI8(stream);
			return std::move(*this);
		}
		uint8_t  GetID() const
		{
			return 0;
		}
		const std::string& GetName() const
		{
			return "TAG_End";
		}
		uint8_t  GetValue() const
		{
			return 0;
		}
	};

	template<NBTInterfaceImpl Interface, typename T>
	void CallWriteViaSize(const T& val, BinaryStream<uint8_t>& stream)
	{
		if constexpr (std::is_integral_v<T>)
		{
			if constexpr (sizeof(T) == 1)
				Interface::WriteI8((int8_t)val, stream);
			else if constexpr (sizeof(T) == 2)
				Interface::WriteI16((int16_t)val, stream);
			else if constexpr (sizeof(T) == 4)
				Interface::WriteI32((int)val, stream);
			else if constexpr (sizeof(T) == 8)
				Interface::WriteI64((int64_t)val, stream);
		}
		else if constexpr (std::is_floating_point_v<T>)
		{
			if constexpr (sizeof(T) == 4)
				Interface::WriteF32(val, stream);
			else if constexpr (sizeof(T) == 8)
				Interface::WriteF64(val, stream);
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			Interface::WriteString(val, stream);
		}
	}

	template<NBTInterfaceImpl Interface, typename T>
	T CallReadViaSize(BinaryStream<uint8_t>& stream)
	{
		if constexpr (std::is_same_v<T, std::string>)
		{
			return Interface::ReadString(stream);
		}
		else if constexpr (std::is_integral_v<T>)
		{
			if constexpr (sizeof(T) == 1)
				return (T)Interface::ReadI8(stream);
			else if constexpr (sizeof(T) == 2)
				return (T)Interface::ReadI16(stream);
			else if constexpr (sizeof(T) == 4)
				return (T)Interface::ReadI32(stream);
			else if constexpr (sizeof(T) == 8)
				return (T)Interface::ReadI64(stream);
		}
		else if constexpr (std::is_floating_point_v<T>)
		{
			if constexpr (sizeof(T) == 4)
				return Interface::ReadF32(stream);
			else if constexpr (sizeof(T) == 8)
				return Interface::ReadF64(stream);
		}
	}


	template<typename T, uint8_t  id>
	class BasicTagNoReadWrite
	{
	protected:
		T mValue;
	public:
		using self = BasicTagNoReadWrite<T, id>;
		BasicTagNoReadWrite(T&& value) : mValue(std::move(value)) {}
		BasicTagNoReadWrite(const T& value = T{}) : mValue(value) {}
		uint8_t  GetID() const
		{
			return id;
		}
		const T& GetValue() const
		{
			return mValue;
		}

		T& GetValue()
		{
			return mValue;
		}
		void SetValue(const decltype(mValue)& value) { mValue = value; }

		decltype(mValue) operator++() { mValue++; return mValue; }
		decltype(mValue) operator++(int) { mValue++; return mValue; }

		decltype(mValue) operator--() { mValue--; return mValue; }
		decltype(mValue) operator--(int) { mValue--; return mValue; }

		decltype(mValue) operator+=(T value) { mValue += value; return mValue; }
		decltype(mValue) operator+=(self value) { mValue += value; return mValue; }
		decltype(mValue) operator-=(T value) { mValue -= value; return mValue; }
		decltype(mValue) operator-=(self value) { mValue -= value; return mValue; }
		decltype(mValue) operator*=(T value) { mValue *= value; return mValue; }
		decltype(mValue) operator*=(self value) { mValue *= value; return mValue; }
		decltype(mValue) operator/=(T value) { mValue /= value; return mValue; }
		decltype(mValue) operator/=(self value) { mValue /= value; return mValue; }
		decltype(mValue) operator%=(T value) { mValue %= value; return mValue; }
		decltype(mValue) operator%=(self value) { mValue %= value; return mValue; }
		decltype(mValue) operator&=(T value) { mValue &= value; return mValue; }
		decltype(mValue) operator&=(self value) { mValue &= value; return mValue; }
		decltype(mValue) operator|=(T value) { mValue |= value; return mValue; }
		decltype(mValue) operator|=(self value) { mValue |= value; return mValue; }
		decltype(mValue) operator^=(T value) { mValue ^= value; return mValue; }
		decltype(mValue) operator^=(self value) { mValue ^= value; return mValue; }
		decltype(mValue) operator<<=(T value) { mValue <<= value; return mValue; }
		decltype(mValue) operator<<=(self value) { mValue <<= value; return mValue; }
		decltype(mValue) operator>>=(T value) { mValue>>= value; return mValue; }
		decltype(mValue) operator>>=(self value) { mValue>>= value; return mValue; }
		decltype(mValue) operator+(T value) { return mValue + value; }
		decltype(mValue) operator+(self value) { return mValue + value; }
		decltype(mValue) operator-(T value) { return mValue - value; }
		decltype(mValue) operator-(self value) { return mValue - value; }
		decltype(mValue) operator*(T value) { return mValue * value; }
		decltype(mValue) operator*(self value) { return mValue * value; }
		decltype(mValue) operator/(T value) { return mValue / value; }
		decltype(mValue) operator/(self value) { return mValue / value; }
		decltype(mValue) operator%(T value) { return mValue % value; }
		decltype(mValue) operator%(self value) { return mValue % value; }
		decltype(mValue) operator&(T value) { return mValue & value; }
		decltype(mValue) operator&(self value) { return mValue & value; }
		decltype(mValue) operator|(T value) { return mValue | value; }
		decltype(mValue) operator|(self value) { return mValue | value; }
		decltype(mValue) operator^(T value) { return mValue ^ value; }
		decltype(mValue) operator^(self value) { return mValue ^ value; }
		decltype(mValue) operator<<(T value) { return mValue << value; }
		decltype(mValue) operator<<(self value) { return mValue << value; }
		decltype(mValue) operator>>(T value) { return mValue>> value; }
		decltype(mValue) operator>>(self value) { return mValue>> value; }
		decltype(mValue) operator-() { return -mValue; }
		decltype(mValue) operator~() { return ~mValue; }
		bool operator==(T value) { return mValue == value; }
		bool operator==(self value) { return mValue == value; }
		bool operator!=(T value) { return mValue != value; }
		bool operator!=(self value) { return mValue != value; }

		bool operator<(T value) { return mValue < value; }
		bool operator<(self value) { return mValue < value; }
		bool operator>(T value) { return mValue> value; }
		bool operator>(self value) { return mValue> value; }
		bool operator<=(T value) { return mValue <= value; }
		bool operator<=(self value) { return mValue <= value; }
		bool operator>=(T value) { return mValue>= value; }
		bool operator>=(self value) { return mValue>= value; }
		bool operator&&(T value) { return mValue && value; }
		bool operator&&(self value) { return mValue && value; }
		bool operator||(T value) { return mValue || value; }
		bool operator||(self value) { return mValue || value; }
		bool operator!() { return !mValue; }
		operator T& () { return mValue; }
	};

	template<typename T, uint8_t  id>
	class BasicTag : public BasicTagNoReadWrite<T, id>
	{
	public:
		using BasicTagNoReadWrite<T, id>::BasicTagNoReadWrite;
		BasicTag(T&& value) : BasicTagNoReadWrite<T, id>(std::move(value)) { }
		BasicTag(const T& value) : BasicTagNoReadWrite<T, id>(value) { }

		template<NBTInterfaceImpl Interace>
		BasicTag&& Write(BinaryStream<uint8_t>& stream)
		{
			CallWriteViaSize<Interace, T>(this->mValue, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl Interace>
		BasicTag&& Read(BinaryStream<uint8_t>& stream)
		{
			this->mValue = CallReadViaSize<Interace, T>(stream);
			return std::move(*this);
		}
	};

	class ByteTag : public BasicTag<int8_t, 1>
	{
	public:
		ByteTag(int8_t  value = { 0 }) : BasicTag<int8_t, 1>(value) {}
		const std::string& GetName() const
		{
			return "TAG_Byte";
		}
	};
	class ShortTag : public BasicTag<int16_t, 2>
	{
	public:
		ShortTag(int16_t value = { 0 }) : BasicTag<int16_t, 2>(value) {}
		const std::string& GetName() const
		{
			return "TAG_int16_t";
		}
	};
	class IntTag : public BasicTag<int, 3>
	{
	public:
		IntTag(int value = { 0 }) : BasicTag<int, 3>(value) {}
		const std::string& GetName() const
		{
			return "TAG_Int";
		}
	};
	class LongTag : public BasicTag<int64_t, 4>
	{
	public:
		LongTag(int64_t value = { 0 }) : BasicTag<int64_t, 4>(value) {}
		const std::string& GetName() const
		{
			return "TAG_Long";
		}
	};
	class FloatTag : public BasicTag<float, 5>
	{
	public:
		FloatTag(float value = { 0 }) : BasicTag<float, 5>(value) {}
		const std::string& GetName() const
		{
			return "TAG_Float";
		}
	};
	class DoubleTag : public BasicTag<double, 6>
	{
	public:
		DoubleTag(double value = { 0 }) : BasicTag<double, 6>(value) {}
		const std::string& GetName() const
		{
			return "TAG_Double";
		}
	};

	class ByteArrayTag : public BasicTagNoReadWrite<std::vector<uint8_t>, 7>
	{
	public:
		ByteArrayTag(const std::vector<uint8_t>& value = {}) : BasicTagNoReadWrite<std::vector<uint8_t>, 7>(value) {}
		ByteArrayTag(std::vector<uint8_t>&& value) : BasicTagNoReadWrite<std::vector<uint8_t>, 7>(std::move(value)) {}
		template<NBTInterfaceImpl T>
		ByteArrayTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI32(this->mValue.size(), stream);
			stream.WriteBuff(this->mValue);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		ByteArrayTag&& Read(BinaryStream<uint8_t>& stream)
		{
			this->mValue.resize(T::ReadI32(stream));
			for (size_t i = 0; i < mValue.size(); i++)
				this->mValue[i] = T::ReadI8(stream);
			return std::move(*this);
		}
		uint8_t  GetID() const
		{
			return 7;
		}
		const std::string& GetName() const
		{
			return "TAG_Byte_Array";
		}
	};
	class StringTag : public BasicTagNoReadWrite<std::string, 8>
	{
	public:
		StringTag(const std::string& value = {}) : BasicTagNoReadWrite<std::string, 8>(value) {}
		StringTag(std::string&& value) : BasicTagNoReadWrite<std::string, 8>(std::move(value)) {}

		template<NBTInterfaceImpl T>
		StringTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteString(this->mValue, stream);
			return std::move(*this);
		}

		template<NBTInterfaceImpl T>
		StringTag&& Read(BinaryStream<uint8_t>& stream)
		{
			this->mValue = T::ReadString(stream);
			return std::move(*this);
		}

		const std::string& GetName() const
		{
			return "TAG_String";
		}
	};
	class ListTag : public BasicTagNoReadWrite<std::vector<Tag>, 9>
	{
	public:
		ListTag(const std::vector<Tag>& value = {}) : self(value) {}
		ListTag(std::vector<Tag>&& value) : self(std::move(value)) {}
		template<typename T>
		ListTag(const std::vector<T>& value);
		template<typename T>
		ListTag(std::vector<T>&& value);
		template<NBTInterfaceImpl T>
		ListTag&& Write(BinaryStream<uint8_t>& stream)
		{
			if (this->mValue.empty())
			{
				T::WriteI8(0, stream);
				T::WriteI32(0, stream);
				return std::move(*this);
			}
			std::visit([&stream](auto&& arg) { T::WriteI8(arg.GetID(), stream); }, this->mValue[0]);
			T::WriteI32(this->mValue.size(), stream);
			for (auto& tag : this->mValue)
				std::visit([&stream](auto&& arg) { arg.Write<T>(stream); }, tag);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		ListTag&& Read(BinaryStream<uint8_t>& stream)
		{
			uint8_t  id = T::ReadI8(stream);
			size_t size = T::ReadI32(stream);
			this->mValue.resize(size);
			for (size_t i = 0; i < size; i++)
			{
				auto tag = TagFromId(id);
				std::visit([&stream](auto&& arg) { arg.Read<T>(stream); }, tag);
				if (id == 10)
					stream.Read(); // Skip 1 byte for the end tag
				this->mValue[i] = tag;
			}
			return std::move(*this);
		}
		const std::string& GetName() const
		{
			return "TAG_List";
		}

		template<typename T>
		void push_back(const T& tag);
		template<typename T>
		void push_back(T&& tag);
		template<typename T>
		T& operator[](size_t index)
		{
			return std::get<T>(mValue[index]);
		}
		template<typename T>
		const T& operator[](size_t index) const
		{
			return std::get<T>(mValue[index]);
		}

		template<typename T>
		class ConversionIter;

		auto begin() const
		{
			return mValue.begin();
		}

		template<typename T>
		ConversionIter<T> begin() const
		{
			return get_converted_iter_begin<T>();
		}

		template<typename T>
		ConversionIter<T> begin()
		{
			return get_converted_iter_begin<T>();
		}


		auto end() const
		{
			return mValue.end();
		}

		template<typename T>
		auto end() const
		{
			return get_converted_iter_end<T>();
		}

		template<typename T>
		auto end()
		{
			return get_converted_iter_end<T>();
		}

		auto begin()
		{
			return mValue.begin();
		}

		auto end()
		{
			return mValue.end();
		}

		void clear()
		{
			mValue.clear();
		}

		size_t size() const
		{
			return mValue.size();
		}

		template<typename T>
		ConversionIter<T> get_converted_iter_begin()
		{
			return ConversionIter<T>(mValue.data());
		}
		template<typename T>
		ConversionIter<T> get_converted_iter_begin() const
		{
			return ConversionIter<T>(mValue.data());
		}
		template<typename T>
		ConversionIter<T> get_converted_iter_end()
		{
			return ConversionIter<T>(mValue.data() + mValue.size());
		}
		template<typename T>
		ConversionIter<T> get_converted_iter_end() const
		{
			return ConversionIter<T>(mValue.data() + mValue.size());
		}

		template<typename T>
		void for_each(const std::function<void(const T&)>& mCallback) const;

		template<typename T>
		void for_each(const std::function<void(T&)>& mCallback);

		bool holds_tag(TagID id) const;


	};
	class IntArrayTag : public BasicTagNoReadWrite<std::vector<int>, 11>
	{
	public:
		IntArrayTag(const std::vector<int>& value = {}) : self(value) {}
		IntArrayTag(std::vector<int>&& value) : self(std::move(value)) {}
		template<NBTInterfaceImpl T>
		IntArrayTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI32(this->mValue.size(), stream);
			for (auto& value : this->mValue)
				T::WriteI32(value, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		IntArrayTag&& Read(BinaryStream<uint8_t>& stream)
		{
			this->mValue.resize(T::ReadI32(stream));
			for (size_t i = 0; i < this->mValue.size(); i++)
				this->mValue[i] = T::ReadI32(stream);
			return std::move(*this);
		}
		const std::string& GetName() const
		{
			return "TAG_List";
		}
	};
	class LongArrayTag : public BasicTagNoReadWrite<std::vector<int64_t>, 12>
	{
	public:
		LongArrayTag(const std::vector<int64_t>& value = {}) : self(value) {}
		LongArrayTag(std::vector<int64_t>&& value) : self(std::move(value)) {}
		template<NBTInterfaceImpl T>
		LongArrayTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI32(this->mValue.size(), stream);
			for (auto& value : this->mValue)
				T::WriteI64(value, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		LongArrayTag&& Read(BinaryStream<uint8_t>& stream)
		{
			this->mValue.resize(T::ReadI32(stream));
			for (size_t i = 0; i < this->mValue.size(); i++)
				this->mValue[i] = T::ReadI64(stream);
			return std::move(*this);
		}

		const std::string& GetName() const
		{
			return "TAG_Long_Array";
		}
	};
	class CompoundTag : public BasicTagNoReadWrite<absl::flat_hash_map<std::string, Tag>, 10>
	{
	public:
		CompoundTag(const absl::flat_hash_map<std::string, Tag>& value = {}) : self(value) {}
		CompoundTag(absl::flat_hash_map<std::string, Tag>&& value) : self(std::move(value)) {}
		CompoundTag(
			const std::initializer_list<std::pair<std::string, Tag>>& value) : self(value) {}
		template<NBTInterfaceImpl T>
		CompoundTag&& Write(BinaryStream<uint8_t>& stream)
		{
			for (auto& [name, tag] : this->mValue)
			{
				T::WriteI8(tag.index(), stream);
				T::WriteString(name, stream);
				std::visit([&stream](auto&& arg) { arg.Write<T>(stream); }, tag);
			}
			T::WriteI8(0, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		CompoundTag&& Read(BinaryStream<uint8_t>& stream)
		{
			int8_t id = stream.Peak();
			bool isNested = false;
			while (id != 0 && isNested == false)
			{
				id = stream.Read();
				if (id == 10)
					isNested = true;
				auto name = T::ReadString(stream);
				auto tag = TagFromId(id);
				std::visit([&stream](auto&& arg) { arg.Read<T>(stream); }, tag);
				this->mValue[name] = tag;
				id = stream.Peak();
				if (isNested && id == 0)
				{
					stream.Read();
					id = stream.Peak();
					isNested = false;
				}
			}
			return std::move(*this);
		}
		uint8_t  GetID() const
		{
			return 10;
		}
		const std::string& GetName() const
		{
			return "TAG_Compound";
		}
		const absl::flat_hash_map<std::string, Tag>& GetValue() const
		{
			return this->mValue;
		}

		size_t size() const
		{
			return this->mValue.size();
		}

		bool empty() const
		{
			return this->mValue.empty();
		}

		Tag& operator[](const std::string& key)
		{
			return this->mValue[key];
		}

		const Tag& operator[](const std::string& key) const
		{
			return this->mValue.at(key);
		}

		template<typename T>
		T& get(const std::string& key)
		{
			return std::get<T>(this->mValue[key]);
		}

		template<typename T>
		const T& get(const std::string& key) const
		{
			return std::get<T>(this->mValue.at(key));
		}

		template<typename T>
		void set(const std::string& key, const T& value)
		{
			this->mValue[key] = value;
		}
		template<typename T>
		void set(const std::string& key, T&& value)
		{
			this->mValue[key] = std::move(value);
		}

		auto find(const std::string& key) const
		{
			return this->mValue.find(key);
		}

		auto find(const std::string& key)
		{
			return this->mValue.find(key);
		}

		auto begin() const
		{
			return this->mValue.begin();
		}

		auto end() const
		{
			return this->mValue.end();
		}

		auto begin()
		{
			return this->mValue.begin();
		}

		auto end()
		{
			return this->mValue.end();
		}

	};

	static Tag TagFromId(uint8_t  id)
	{
		switch (id)
		{
		case 0: return EndTag();
		case 1: return ByteTag();
		case 2: return ShortTag();
		case 3: return IntTag();
		case 4: return LongTag();
		case 5: return FloatTag();
		case 6: return DoubleTag();
		case 7: return ByteArrayTag();
		case 8: return StringTag();
		case 9: return ListTag();
		case 10: return CompoundTag();
		case 11: return IntArrayTag();
			/*case 12: return LongArrayTag(); */
		default: return EndTag();
		}

	}



	/*
	* DONOT MOVE THESE
	* They are here to deal with some template jank and they explode if inside the ListTag classes lol
	*/
	template<typename T>
	void ListTag::push_back(const T& tag)
	{
		if (this->mValue.empty())
		{
			this->mValue.push_back(tag);
			return;
		}
		if (this->mValue[0].index() != tag.GetID())
			throw std::runtime_error("Invalid tag type");
		this->mValue.push_back(tag);
	}

	template<typename T>
	void ListTag::push_back(T&& tag)
	{
		if (this->mValue.empty())
		{
			this->mValue.push_back(std::move(tag));
			return;
		}
		if (this->mValue[0].index() != tag.GetID())
			throw std::runtime_error("Invalid tag type");
		this->mValue.push_back(std::move(tag));
	}

	template<typename T>
	void ListTag::for_each(const std::function<void(const T&)>& mCallback) const
	{
		for (auto it = get_converted_iter_begin<T>(); it != get_converted_iter_end<T>(); ++it)
			mCallback(*it);
	}

	template<typename T>
	void ListTag::for_each(const std::function<void(T&)>& mCallback)
	{
		for (auto it = get_converted_iter_begin<T>(); it != get_converted_iter_end<T>(); ++it)
			mCallback(*it);
	}
	template<typename T>
	ListTag::ListTag(const std::vector<T>& value)
	{
		for (auto& val : value)
			mValue.push_back(val);
	}


	template<typename T>
	ListTag::ListTag(std::vector<T>&& value)
	{
		for (auto& val : value)
			mValue.push_back(std::move(val));
	}

	template<typename T>
	class ListTag::ConversionIter
	{
	public:
		ConversionIter(Tag* current) : mCurrent(current) {}

		T& operator*() {
			return std::get<T>(*mCurrent);
		}

		bool operator!=(const ListTag::ConversionIter<T>& other)
		{
			return mCurrent != other.mCurrent;
		}

		ConversionIter& operator++() {
			mCurrent++;
			return *this;
		}
	private:
		Tag* mCurrent;
	};
}