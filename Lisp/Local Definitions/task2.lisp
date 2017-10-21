; lisp function for differentiation

(defun deriv (f)
  (cond ((numberp f) 0)
        ((eq f 'x) 1)
        ((eq (car f) '+) `(+ ,(deriv (cadr f)) ,(deriv (caddr f))))
        ((eq (car f) '-) `(- ,(deriv (cadr f)) ,(deriv (caddr f))))
        ((eq (car f) '*) `(+ (* ,(caddr f) ,(deriv (cadr f))) (* ,(cadr f) ,(deriv (caddr f)))))
        ((eq (car f) 'sin) `(* (cos ,(cadr f)) ,(deriv (cadr f))))
        ((eq (car f) 'cos) `(* (- (cos ,(cadr f)) ,(deriv (cadr f)))))
        ((eq (car f) 'exp) `(* (exp ,(cadr f)) (deriv (cadr f))))
        ((eq (car f) '^) `(* (* ,(caddr f) (^ ,(cadr f) (- ,(caddr f) 1))) ,(deriv (cadr f))))
        (t (format t "~%Syntax error. Unexpected symbol: ~S" (car f)))))

(print(deriv '(^ x 2)))
