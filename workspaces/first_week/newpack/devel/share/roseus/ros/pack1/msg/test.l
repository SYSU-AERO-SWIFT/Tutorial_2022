;; Auto-generated. Do not edit!


(when (boundp 'pack1::test)
  (if (not (find-package "PACK1"))
    (make-package "PACK1"))
  (shadow 'test (find-package "PACK1")))
(unless (find-package "PACK1::TEST")
  (make-package "PACK1::TEST"))

(in-package "ROS")
;;//! \htmlinclude test.msg.html


(defclass pack1::test
  :super ros::object
  :slots (_num ))

(defmethod pack1::test
  (:init
   (&key
    ((:num __num) 0)
    )
   (send-super :init)
   (setq _num (round __num))
   self)
  (:num
   (&optional __num)
   (if __num (setq _num __num)) _num)
  (:serialization-length
   ()
   (+
    ;; int8 _num
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _num
       (write-byte _num s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _num
     (setq _num (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _num 127) (setq _num (- _num 256)))
   ;;
   self)
  )

(setf (get pack1::test :md5sum-) "cf992509827662516557e7b1f30e20ce")
(setf (get pack1::test :datatype-) "pack1/test")
(setf (get pack1::test :definition-)
      "int8 num



")



(provide :pack1/test "cf992509827662516557e7b1f30e20ce")


