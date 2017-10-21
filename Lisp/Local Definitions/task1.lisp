;factorial using lambda in Common lisp

(defun factorial (n)
  (cond ((= n 0) 1)
        (t ((lambda (x y)(* x y))
          n (factorial (1- n))))))

(print (factorial 7))
