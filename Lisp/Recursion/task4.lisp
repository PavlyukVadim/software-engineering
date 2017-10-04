(DEFUN merge-sorted-lists (l-1 l-2)
  (COND ((NULL l-1) l-2)
        ((NULL l-2) l-1)
        ((> (CAR l-1) (CAR l-2)) 
        	(CONS (CAR l-2) (merge-sorted-lists l-1 (CDR l-2))))
        (T (CONS (CAR l-1) (merge-sorted-lists (CDR l-1) l-2)))))
 
(print (merge-sorted-lists '(1 3 9) '(0 1 2 4 5)))
