
(cl:in-package :asdf)

(defsystem "pack1-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "test" :depends-on ("_package_test"))
    (:file "_package_test" :depends-on ("_package"))
  ))