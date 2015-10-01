
inline const float* Matrix::operator[](int row) const
{
	return &m_Entry[4 * row];
}

inline float* Matrix::operator[] (int row)
{
	return &m_Entry[4 * row];
}

inline const float& Matrix::operator() (int row, int column) const
{
	return m_Entry[column + 4 * row];
}

inline float& Matrix::operator() (int row, int column)
{
	return m_Entry[column + 4 * row];
}
