(setq L1 '(PRIM SD FLAG () (GHG)))
(setq L2 '(1 56 98 52))
(setq L3 '(T 2 3 4 Y H))

(print
((lambda (l-1 l-2 l-3)
  (list (car l-1) (car l-2) (car l-3)))
  L1 L2 L3)
)
