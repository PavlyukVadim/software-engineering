(defun filter-list (L1)
  (cond (
    (and (symbolp (car L1)) (symbolp (car (last L1))))
    (list (car L1) (car (last L1)))
  ) (T (cons (car L1) (cddr L1))))
)
(print (filter-list '(:a 1 2 3 :b) ))
(print (filter-list '(:a 1 2 3 4) ))
