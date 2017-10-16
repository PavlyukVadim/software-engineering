(defun remove-nth (n list)
  (if (or (zerop n) (null list))
      (cdr list)
      (cons (car list) (remove-nth (1- n) (cdr list)))))

(defun remove-by-deep-nth (n deep list)
  (cond ((null list) nil)
        ((atom list) list)
        ((= deep 0) (remove-nth n list))
        (t
          (if (atom (car list))
              (cons (remove-by-deep-nth n deep (car list)) (remove-by-deep-nth n deep (cdr list)))
              (cons (remove-by-deep-nth n (1- deep) (car list)) (remove-by-deep-nth n deep (cdr list)))))))

(print (remove-by-deep-nth 0 1 '(0 1 2 (3 4) (5 6) (7 8 (9 0)))))
