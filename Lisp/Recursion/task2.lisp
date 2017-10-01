; Sorting algorithms/Shell sort in Common Lisp

(DEFUN insert (l x)
  (COND ((NULL l) (LIST x))
        ((> (CAR l) x) (CONS x l))
        (T (CONS (CAR l) (insert (CDR l) x)))))

(DEFUN my-sort (x s)
  (COND ((NULL x) s)
        (T (my-sort (CDR x) (insert s (CAR x))))))

(DEFUN gap-sort (l gap res-l)
  (COND ((NULL l) res-l)
        (T (COND ((> gap (length l)) (APPEND res-l (mysort l)))
        (T (APPEND res-l (mysort (subseq l 0 gap)) (gap-sort (subseq l gap (length l)) gap res-l)))))))

(DEFUN shell-sort (l gaps) 
  (COND ((NULL (CDR gaps)) (gap-sort l (CAR gaps) '()))
        (T (shell-sort (gap-sort l (CAR gaps) '()) (CDR gaps)))))

(print(shell-sort '(5 4 1 8 9 450 999) '(4 8 7 98 14)))
