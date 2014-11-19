; Auto-generated. Do not edit!


(cl:in-package dlut_move_base-msg)


;//! \htmlinclude Height.msg.html

(cl:defclass <Height> (roslisp-msg-protocol:ros-message)
  ((freq
    :reader freq
    :initarg :freq
    :type cl:integer
    :initform 0)
   (pulse
    :reader pulse
    :initarg :pulse
    :type cl:integer
    :initform 0)
   (stop
    :reader stop
    :initarg :stop
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Height (<Height>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Height>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Height)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dlut_move_base-msg:<Height> is deprecated: use dlut_move_base-msg:Height instead.")))

(cl:ensure-generic-function 'freq-val :lambda-list '(m))
(cl:defmethod freq-val ((m <Height>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dlut_move_base-msg:freq-val is deprecated.  Use dlut_move_base-msg:freq instead.")
  (freq m))

(cl:ensure-generic-function 'pulse-val :lambda-list '(m))
(cl:defmethod pulse-val ((m <Height>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dlut_move_base-msg:pulse-val is deprecated.  Use dlut_move_base-msg:pulse instead.")
  (pulse m))

(cl:ensure-generic-function 'stop-val :lambda-list '(m))
(cl:defmethod stop-val ((m <Height>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dlut_move_base-msg:stop-val is deprecated.  Use dlut_move_base-msg:stop instead.")
  (stop m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Height>) ostream)
  "Serializes a message object of type '<Height>"
  (cl:let* ((signed (cl:slot-value msg 'freq)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'pulse)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'stop) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Height>) istream)
  "Deserializes a message object of type '<Height>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'freq) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'pulse) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:slot-value msg 'stop) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Height>)))
  "Returns string type for a message object of type '<Height>"
  "dlut_move_base/Height")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Height)))
  "Returns string type for a message object of type 'Height"
  "dlut_move_base/Height")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Height>)))
  "Returns md5sum for a message object of type '<Height>"
  "ad3bfdee1ea76a2325489c5ae28e3056")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Height)))
  "Returns md5sum for a message object of type 'Height"
  "ad3bfdee1ea76a2325489c5ae28e3056")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Height>)))
  "Returns full string definition for message of type '<Height>"
  (cl:format cl:nil "int32 freq~%int32 pulse~%bool stop~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Height)))
  "Returns full string definition for message of type 'Height"
  (cl:format cl:nil "int32 freq~%int32 pulse~%bool stop~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Height>))
  (cl:+ 0
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Height>))
  "Converts a ROS message object to a list"
  (cl:list 'Height
    (cl:cons ':freq (freq msg))
    (cl:cons ':pulse (pulse msg))
    (cl:cons ':stop (stop msg))
))
