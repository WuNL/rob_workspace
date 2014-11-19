; Auto-generated. Do not edit!


(cl:in-package dlut_move_base-msg)


;//! \htmlinclude Laser.msg.html

(cl:defclass <Laser> (roslisp-msg-protocol:ros-message)
  ((is_rotate
    :reader is_rotate
    :initarg :is_rotate
    :type cl:boolean
    :initform cl:nil)
   (num
    :reader num
    :initarg :num
    :type cl:fixnum
    :initform 0)
   (freq
    :reader freq
    :initarg :freq
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Laser (<Laser>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Laser>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Laser)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dlut_move_base-msg:<Laser> is deprecated: use dlut_move_base-msg:Laser instead.")))

(cl:ensure-generic-function 'is_rotate-val :lambda-list '(m))
(cl:defmethod is_rotate-val ((m <Laser>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dlut_move_base-msg:is_rotate-val is deprecated.  Use dlut_move_base-msg:is_rotate instead.")
  (is_rotate m))

(cl:ensure-generic-function 'num-val :lambda-list '(m))
(cl:defmethod num-val ((m <Laser>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dlut_move_base-msg:num-val is deprecated.  Use dlut_move_base-msg:num instead.")
  (num m))

(cl:ensure-generic-function 'freq-val :lambda-list '(m))
(cl:defmethod freq-val ((m <Laser>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dlut_move_base-msg:freq-val is deprecated.  Use dlut_move_base-msg:freq instead.")
  (freq m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Laser>) ostream)
  "Serializes a message object of type '<Laser>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_rotate) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'num)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'freq)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Laser>) istream)
  "Deserializes a message object of type '<Laser>"
    (cl:setf (cl:slot-value msg 'is_rotate) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'num) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'freq) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Laser>)))
  "Returns string type for a message object of type '<Laser>"
  "dlut_move_base/Laser")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Laser)))
  "Returns string type for a message object of type 'Laser"
  "dlut_move_base/Laser")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Laser>)))
  "Returns md5sum for a message object of type '<Laser>"
  "bae97466fa81f80169d3d7d75e5910a7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Laser)))
  "Returns md5sum for a message object of type 'Laser"
  "bae97466fa81f80169d3d7d75e5910a7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Laser>)))
  "Returns full string definition for message of type '<Laser>"
  (cl:format cl:nil "bool is_rotate~%int16 num~%int16 freq~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Laser)))
  "Returns full string definition for message of type 'Laser"
  (cl:format cl:nil "bool is_rotate~%int16 num~%int16 freq~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Laser>))
  (cl:+ 0
     1
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Laser>))
  "Converts a ROS message object to a list"
  (cl:list 'Laser
    (cl:cons ':is_rotate (is_rotate msg))
    (cl:cons ':num (num msg))
    (cl:cons ':freq (freq msg))
))
