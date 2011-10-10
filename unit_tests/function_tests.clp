(defglobal ?*value-list* = (create$ a b c))


(deffunction call-class_method_mf1 ()
  (return (class_method_mf1 ?*value-list*))
)

(deffunction call-class_method_mf4 ()
  (return (class_method_mf4 "foo" 5 ?*value-list* 1))
)
