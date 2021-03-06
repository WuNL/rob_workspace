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
 * Auto-generated by genmsg_cpp from file /home/rob/catkin_ws/src/dlut_move_base/msg/Laser.msg
 *
 */


#ifndef DLUT_MOVE_BASE_MESSAGE_LASER_H
#define DLUT_MOVE_BASE_MESSAGE_LASER_H


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
struct Laser_
{
  typedef Laser_<ContainerAllocator> Type;

  Laser_()
    : is_rotate(false)
    , num(0)
    , freq(0)  {
    }
  Laser_(const ContainerAllocator& _alloc)
    : is_rotate(false)
    , num(0)
    , freq(0)  {
    }



   typedef uint8_t _is_rotate_type;
  _is_rotate_type is_rotate;

   typedef int16_t _num_type;
  _num_type num;

   typedef int16_t _freq_type;
  _freq_type freq;




  typedef boost::shared_ptr< ::dlut_move_base::Laser_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::dlut_move_base::Laser_<ContainerAllocator> const> ConstPtr;

}; // struct Laser_

typedef ::dlut_move_base::Laser_<std::allocator<void> > Laser;

typedef boost::shared_ptr< ::dlut_move_base::Laser > LaserPtr;
typedef boost::shared_ptr< ::dlut_move_base::Laser const> LaserConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::dlut_move_base::Laser_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::dlut_move_base::Laser_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::dlut_move_base::Laser_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::dlut_move_base::Laser_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dlut_move_base::Laser_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dlut_move_base::Laser_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dlut_move_base::Laser_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dlut_move_base::Laser_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::dlut_move_base::Laser_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bae97466fa81f80169d3d7d75e5910a7";
  }

  static const char* value(const ::dlut_move_base::Laser_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xbae97466fa81f801ULL;
  static const uint64_t static_value2 = 0x69d3d7d75e5910a7ULL;
};

template<class ContainerAllocator>
struct DataType< ::dlut_move_base::Laser_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dlut_move_base/Laser";
  }

  static const char* value(const ::dlut_move_base::Laser_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::dlut_move_base::Laser_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool is_rotate\n\
int16 num\n\
int16 freq\n\
";
  }

  static const char* value(const ::dlut_move_base::Laser_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::dlut_move_base::Laser_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.is_rotate);
      stream.next(m.num);
      stream.next(m.freq);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct Laser_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::dlut_move_base::Laser_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::dlut_move_base::Laser_<ContainerAllocator>& v)
  {
    s << indent << "is_rotate: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.is_rotate);
    s << indent << "num: ";
    Printer<int16_t>::stream(s, indent + "  ", v.num);
    s << indent << "freq: ";
    Printer<int16_t>::stream(s, indent + "  ", v.freq);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DLUT_MOVE_BASE_MESSAGE_LASER_H
