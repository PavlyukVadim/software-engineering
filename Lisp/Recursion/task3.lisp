(DEFUN min-from-pair (x y)
  (IF (< x y) x y))

(DEFUN min-from-list (x) 
  (COND ((= (length x) 1) (CAR x))
        ((= (length x) 2) (min-from-pair (CAR x) (cadr x)))
        (T (min-from-pair (CAR x) (min-from-list (CDR x))))))
 
(DEFUN remove-el-from-list (l elem)
  (COND ((NULL l) NIL)
        ((EQ elem (CAR l)) (CDR l))
        (T (CONS (CAR l) (remove-el-from-list (CDR l) elem)))))

 
(DEFUN shaker-sort (l) 
  (COND ((NULL l) NIL)
        (T (CONS (min-from-list l) (shaker-sort (remove-el-from-list l (min-from-list l)))))))
 
(print (shaker-sort `(4 5 99 8 2 0 -16)))
