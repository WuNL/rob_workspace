; Auto-generated. Do not edit!


(cl:in-package dlut_motor_hokuyo-msg)


;//! \htmlinclude UInt32.msg.html

(cl:defclass <UInt32> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type cl:integer
    :initform 0))
)

(cl:defclass UInt32 (<UInt32>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <UInt32>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'UInt32)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dlut_motor_hokuyo-msg:<UInt32> is deprecated: use dlut_motor_hokuyo-msg:UInt32 instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <UInt32>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dlut_motor_hokuyo-msg:data-val is deprecated.  Use dlut_motor_hokuyo-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <UInt32>) ostream)
  "Serializes a message object of type '<UInt32>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'data)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'data)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'data)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'data)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <UInt32>) istream)
  "Deserializes a message object of type '<UInt32>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'data)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'data)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'data)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'data)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<UInt32>)))
  "Returns string type for a message object of type '<UInt32>"
  "dlut_motor_hokuyo/UInt32")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'UInt32)))
  "Returns string type for a message object of type 'UInt32"
  "dlut_motor_hokuyo/UInt32")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<UInt32>)))
  "Returns md5sum for a message object of type '<UInt32>"
  "304a39449588c7f8ce2df6e8001c5fce")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'UInt32)))
  "Returns md5sum for a message object of type 'UInt32"
  "304a39449588c7f8ce2df6e8001c5fce")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<UInt32>)))
  "Returns full string definition for message of type '<UInt32>"
  (cl:format cl:nil "uint32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'UInt32)))
  "Returns full string definition for message of type 'UInt32"
  (cl:format cl:nil "uint32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <UInt32>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <UInt32>))
  "Converts a ROS message object to a list"
  (cl:list 'UInt32
    (cl:cons ':data (data msg))
))
