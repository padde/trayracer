#ifndef BUW_PIXEL_HPP
#define BUW_PIXEL_HPP

// header, system
#include <iosfwd>

// header, project
#include <rgb.hpp>

//! @author Bauhaus Uni Weimar
//! @date ???
//! @brief ... Basic pixel class
//

class pixel {
public : // c'tor

  //! @param x x-coordinate
  //! @param y y-coordinate

  pixel(std::size_t x = 0, std::size_t y = 0);
  ~pixel();

public : // methods 

  void print(std::ostream&) const;

public : // member

  std::size_t x;
  std::size_t y;
  rgb color;
};

std::ostream& operator<<(std::ostream&, const pixel&);

#endif // BUW_PIXEL_HPP
