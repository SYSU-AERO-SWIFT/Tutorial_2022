;; Auto-generated. Do not edit!


(when (boundp 'pack2::test)
  (if (not (find-package "PACK2"))
    (make-package "PACK2"))
  (shadow 'test (find-package "PACK2")))
(unless (find-package "PACK2::TEST")
  (make-package "PACK2::TEST"))
(unless (find-package "PACK2::TESTREQUEST")
  (make-package "PACK2::TESTREQUEST"))
(unless (find-package "PACK2::TESTRESPONSE")
  (make-package "PACK2::TESTRESPONSE"))

(in-package "ROS")





(defclass pack2::testRequest
  :super ros::object
  :slots (_ran ))

(defmethod pack2::testRequest
  (:init
   (&key
    ((:ran __ran) 0.0)
    )
   (send-super :init)
   (setq _ran (float __ran))
   self)
  (:ran
   (&optional __ran)
   (if __ran (setq _ran __ran)) _ran)
  (:serialization-length
   ()
   (+
    ;; float32 _ran
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _ran
       (sys::poke _ran (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _ran
     (setq _ran (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass pack2::testResponse
  :super ros::object
  :slots ())

(defmethod pack2::testResponse
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass pack2::test
  :super ros::object
  :slots ())

(setf (get pack2::test :md5sum-) "0bf7337b4741e03b661dce528144e36a")
(setf (get pack2::test :datatype-) "pack2/test")
(setf (get pack2::test :request) pack2::testRequest)
(setf (get pack2::test :response) pack2::testResponse)

(defmethod pack2::testRequest
  (:response () (instance pack2::testResponse :init)))

(setf (get pack2::testRequest :md5sum-) "0bf7337b4741e03b661dce528144e36a")
(setf (get pack2::testRequest :datatype-) "pack2/testRequest")
(setf (get pack2::testRequest :definition-)
      "float32 ran

---



")

(setf (get pack2::testResponse :md5sum-) "0bf7337b4741e03b661dce528144e36a")
(setf (get pack2::testResponse :datatype-) "pack2/testResponse")
(setf (get pack2::testResponse :definition-)
      "float32 ran

---



")



(provide :pack2/test "0bf7337b4741e03b661dce528144e36a")


