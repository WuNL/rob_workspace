/* Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Auto-generated by genmsg_cpp from file /home/rob/catkin_ws/src/dlut_move_base/msg/Color.msg
 *
 */


#ifndef DLUT_MOVE_BASE_MESSAGE_COLOR_H
#define DLUT_MOVE_BASE_MESSAGE_COLOR_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace dlut_move_base
{
template <class ContainerAllocator>
struct Color_
{
  typedef Color_<ContainerAllocator> Type;

  Color_()
    : r(0)
    , g(0)
    , b(0)  {
    }
  Color_(const ContainerAllocator& _alloc)
    : r(0)
    , g(0)
    , b(0)  {
    }



   typedef uint8_t _r_type;
  _r_type r;

   typedef uint8_t _g_type;
  _g_type g;

   typedef uint8_t _b_type;
  _b_type b;




  typedef boost::shared_ptr< ::dlut_move_base::Color_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::dlut_move_base::Color_<ContainerAllocator> const> ConstPtr;

}; // struct Color_

typedef ::dlut_move_base::Color_<std::allocator<void> > Color;

typedef boost::shared_ptr< ::dlut_move_base::Color > ColorPtr;
typedef boost::shared_ptr< ::dlut_move_base::Color const> ColorConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::dlut_move_base::Color_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::dlut_move_base::Color_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace dlut_move_base

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'dlut_move_base': ['/home/rob/catkin_ws/src/dlut_move_base/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::dlut_move_base::Color_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::dlut_move_base::Color_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dlut_move_base::Color_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dlut_move_base::Color_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dlut_move_base::Color_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dlut_move_base::Color_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::dlut_move_base::Color_<ContainerAllocator> >
{
  static const char* value()
  {
    return "353891e354491c51aabe32df673fb446";
  }

  static const char* value(const ::dlut_move_base::Color_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x353891e354491c51ULL;
  static const uint64_t static_value2 = 0xaabe32df673fb446ULL;
};

template<class ContainerAllocator>
struct DataType< ::dlut_move_base::Color_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dlut_move_base/Color";
  }

  static const char* value(const ::dlut_move_base::Color_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::dlut_move_base::Color_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint8 r\n\
uint8 g\n\
uint8 b\n\
";
  }

  static const char* value(const ::dlut_move_base::Color_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::dlut_move_base::Color_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.r);
      stream.next(m.g);
      stream.next(m.b);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct Color_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::dlut_move_base::Color_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::dlut_move_base::Color_<ContainerAllocator>& v)
  {
    s << indent << "r: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.r);
    s << indent << "g: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.g);
    s << indent << "b: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.b);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DLUT_MOVE_BASE_MESSAGE_COLOR_H
