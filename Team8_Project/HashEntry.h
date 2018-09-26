#ifndef HashEntry_h
#define HashEntry_h

// ENTRY CLASS
template <class keyType, class dataType>
class Entry
{
private:
	dataType data;
	keyType key;
public:
	Entry();
	Entry(const dataType &);
	Entry(const keyType &, const dataType&);

	keyType getKey() const;
	dataType getData() const;
	void setData(const dataType&);
	void setKey(const keyType&);
};

//Default constructor
template <class keyType, class dataType>
Entry<keyType, dataType>::Entry() { }

//constructor that populates data member variable
template <class keyType, class dataType>
Entry<keyType, dataType>::Entry(const dataType &d) : data(d) { }

//constructor that populates key and data member variables
template <class keyType, class dataType>
Entry<keyType, dataType>::Entry(const keyType &k, const dataType &d) : data(d), key(k) { }

//Accessors
template <class keyType, class dataType>
keyType	Entry<keyType, dataType>::getKey() const
{
	return key;
}

template <class keyType, class dataType>
dataType Entry<keyType, dataType>::getData() const
{
	return data;
}

//Mutators
template <class keyType, class dataType>
void Entry<keyType, dataType>::setData(const dataType& d)
{
	data = d;
}

template <class keyType, class dataType>
void Entry<keyType, dataType>::setKey(const keyType& k)
{
	key = k;
}

#endif