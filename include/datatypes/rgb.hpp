#ifndef BUW_RGB_HPP
#define BUW_RGB_HPP

// header, system
#include <iosfwd>


class rgb {
public : // enums, typedefs
  enum component {r, g, b};
  typedef float value_t;
 
public : // c'tor
  rgb();
  rgb(rgb const&);
  rgb(value_t const& rgb);
  rgb(value_t r, value_t g, value_t b); 

  ~rgb();

public : // methods
  void swap(rgb&);
  void print(std::ostream& os) const;

  rgb& max_to_one ();
  rgb& powc ( float exp );

  value_t&       operator[](enum component);
  const value_t& operator[](enum component) const;

  rgb& operator= (const rgb&);
  void operator+=(const rgb&);
  void operator*=(const rgb&);
  void operator*=(const float&);
  void operator/=(const float&);

  friend rgb operator* (const rgb&, const rgb&);
  friend rgb operator* (const rgb&, const float&);
  friend rgb operator* (const float&, const rgb&);

  friend rgb operator/ (const rgb&, const float&);
  friend rgb operator/ (const float&, const rgb&);

private: // members
  value_t data_[3]; // rgb
};

rgb operator+(const rgb& a, const rgb& b);
std::ostream& operator<<(std::ostream& os, rgb const&);

#endif // BUW_RGB_HPP
