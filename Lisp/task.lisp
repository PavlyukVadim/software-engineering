(DEFUN my-task(l)
  (COND ((NULL l) '())
        ((ATOM l) (LIST l))
        
  )
)



(DEFUN my-task(l-1 l-2)
       (print l-1)
       (print l-2)
       (print "------------")
  (COND ((NULL l-1) '())
        ((NULL l-2) '())
        ((ATOM l-1)
         (COND ((ATOM l-2) (COND ((EQ l-1 l-2) l-1)
                                 (T '())))
               (T (CONS (my-task l-1 (car l-2)) (my-task l-1 (cdr l-2))))))
        (T (append (my-task (car l-1) l-2) (my-task (cdr l-1) l-2)))
  )
)


(print (my-task '(1 2 3) '(2 1 3)))

