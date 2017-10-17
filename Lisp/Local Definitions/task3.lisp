;old version
; (defun merge-sorted-lists (l-1 l-2)
;   (cond ((null l-1) l-2)
;         ((null l-2) l-1)
;         ((> (car l-1) (car l-2)) 
;           (cons (car l-2) (merge-sorted-lists l-1 (cdr l-2))))
;         (t (cons (car l-1) (merge-sorted-lists (cdr l-1) l-2)))))

(defun merge-sorted-lists (l-1 l-2)
  (let ((res nil))
    (loop
      (cond ((null l-1) (return (append (reverse res) l-2)))
            ((null l-2) (return (append (reverse res) l-1)))
            ((> (car l-1) (car l-2)) (push (car l-2) res) (pop l-2))
            (t (push (car l-1) res) (pop l-1))))))

(print (merge-sorted-lists '(1 3 9) '(0 1 2 4 5)))
