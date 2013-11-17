template <typename FloatType, int num_coeffs, const FloatType* coeffs, int period>
class FirFilter {
public:
	
	FirFilter():
		current_index_(0),
		skip_(0)
	{
		for(int i = 0; i < num_coeffs; ++i)
		history_[i] = 0.0;
	}
	
	void put(FloatType value) 
	{
		history_[current_index_++] = value;
		if(current_index_ == num_coeffs)
			current_index_ = 0;
		skip_ = 0;
	}
	
	void skip()
	{
		skip_++;
	}

	FloatType get() 
	{
		FloatType output = 0.0;
		int index = current_index_;
		for(int i = skip_; i < num_coeffs; i += period)
		{
			if(index != 0)
			{
				--index;
			} else {
				index = num_coeffs - 1;
			}
			output += history_[index] * coeffs[i];
		}
		return output;
	}

private:
	FloatType history_[num_coeffs];
	int current_index_;
	int skip_;
};
