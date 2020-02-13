class MyClass
{
public:
  MyClass(int data) : m_data{data} { }

  int getData() const { return m_data; }
  void setData(int data) { m_data = data; }

private:
  int m_data;
};
