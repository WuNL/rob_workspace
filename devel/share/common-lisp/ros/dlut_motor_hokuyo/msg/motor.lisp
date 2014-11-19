; Auto-generated. Do not edit!


(cl:in-package dlut_motor_hokuyo-msg)


;//! \htmlinclude motor.msg.html

(cl:defclass <motor> (roslisp-msg-protocol:ros-message)
  ((motor_freq
    :reader motor_freq
    :initarg :motor_freq
    :type dlut_motor_hokuyo-msg:UInt32
    :initform (cl:make-instance 'dlut_motor_hokuyo-msg:UInt32))
   (num_of_pulse_per_circle
    :reader num_of_pulse_per_circle
    :initarg :num_of_pulse_per_circle
    :type dlut_motor_hokuyo-msg:UInt32
    :initform (cl:make-instance 'dlut_motor_hokuyo-msg:UInt32)))
)

(cl:defclass motor (<motor>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <motor>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'motor)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dlut_motor_hokuyo-msg:<motor> is deprecated: use dlut_motor_hokuyo-msg:motor instead.")))

(cl:ensure-generic-function 'motor_freq-val :lambda-list '(m))
(cl:defmethod motor_freq-val ((m <motor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dlut_motor_hokuyo-msg:motor_freq-val is deprecated.  Use dlut_motor_hokuyo-msg:motor_freq instead.")
  (motor_freq m))

(cl:ensure-generic-function 'num_of_pulse_per_circle-val :lambda-list '(m))
(cl:defmethod num_of_pulse_per_circle-val ((m <motor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dlut_motor_hokuyo-msg:num_of_pulse_per_circle-val is deprecated.  Use dlut_motor_hokuyo-msg:num_of_pulse_per_circle instead.")
  (num_of_pulse_per_circle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <motor>) ostream)
  "Serializes a message object of type '<motor>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'motor_freq) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'num_of_pulse_per_circle) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <motor>) istream)
  "Deserializes a message object of type '<motor>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'motor_freq) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'num_of_pulse_per_circle) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<motor>)))
  "Returns string type for a message object of type '<motor>"
  "dlut_motor_hokuyo/motor")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'motor)))
  "Returns string type for a message object of type 'motor"
  "dlut_motor_hokuyo/motor")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<motor>)))
  "Returns md5sum for a message object of type '<motor>"
  "151060cee652980d6292a2bc72f122c9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'motor)))
  "Returns md5sum for a message object of type 'motor"
  "151060cee652980d6292a2bc72f122c9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<motor>)))
  "Returns full string definition for message of type '<motor>"
  (cl:format cl:nil "UInt32 motor_freq         #the frequency we send the pulse to the motor~%UInt32 num_of_pulse_per_circle	#the number of the pulse a circle of sick~%~%================================================================================~%MSG: dlut_motor_hokuyo/UInt32~%uint32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'motor)))
  "Returns full string definition for message of type 'motor"
  (cl:format cl:nil "UInt32 motor_freq         #the frequency we send the pulse to the motor~%UInt32 num_of_pulse_per_circle	#the number of the pulse a circle of sick~%~%================================================================================~%MSG: dlut_motor_hokuyo/UInt32~%uint32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <motor>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'motor_freq))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'num_of_pulse_per_circle))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <motor>))
  "Converts a ROS message object to a list"
  (cl:list 'motor
    (cl:cons ':motor_freq (motor_freq msg))
    (cl:cons ':num_of_pulse_per_circle (num_of_pulse_per_circle msg))
))
