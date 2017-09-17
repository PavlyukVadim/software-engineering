(setq L1 '(PRIM SD FLAG () (GHG)))
(setq L2 '(1 56 98 52))
(setq L3 '(T 2 3 4 Y H))

(defun union-lists ()
  (list (fifth L1) (third L2) (second L3))
)
(print (union-lists))

; version 2
(defun union-lists ()
  (list (car (cddddr L1)) (caddr L2) (cadr L3))
)
(print (union-lists))
