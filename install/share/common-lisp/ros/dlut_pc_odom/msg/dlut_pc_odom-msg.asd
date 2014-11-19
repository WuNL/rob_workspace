
(cl:in-package :asdf)

(defsystem "dlut_pc_odom-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "UInt32" :depends-on ("_package_UInt32"))
    (:file "_package_UInt32" :depends-on ("_package"))
    (:file "motor" :depends-on ("_package_motor"))
    (:file "_package_motor" :depends-on ("_package"))
  ))