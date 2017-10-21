; the simplest interpreter of the Lisp programs in Lisp

(defun my-eval (expression)
  (cond
    ((atom expression)
      (cond
        ((eq expression 't1) 't1)
        ((eq expression 'nil) 'nil1)
        ((numberp expression) expression)
        ((car (assoc expression links)))
        (t (expressiont t "~Error. Atom doesn't have lins: ~S" expression))
        ((atom (car expression))
          (cond
            ((eq (car expression) 'quote1) (cadr expression))
            ((eq (car expression) 'cond1) (eval-cond (cdr expression) links))
            ((get (car expression) 'fn)
              (my-apply (get (car expression) 'fn)
                      (eval-list (cdr expression) links) 
                      links))
            (t (my-apply (car expression)
                       (eval-list (cdr expression) links)
                       links))))
        (t (my-apply (car expression)
                   (eval-list (cdr expression) links)
                   links))))))
                

(defun eval-cond (branches context)
  (cond
    ((null branches) 'nil1)
    ((not (eq (my-eval (caar branches) context) 'nil1))
     (my-eval (cadar branches) context))
  (t (eval-cond (cdr branches) context))))


(defun my-apply (func args links)
  (cond ((atom func)
    (cond
      ((eq func 'car1) (cond ((eq (car args) 'nil1) 'nil1)
                             (t (caar args))))
      ((eq func 'cdr1) (cond ((eq (car args) 'nil1) 'nil1) ((null (cdar args)) 'nil1)
                             (t (cdar args))))
      ((eq func 'cons1) (cond ((eq (cadr args) 'nil1) (list (car args)))
                              (t (cons (car args) (cadr args)))))
      ((eq func 'atom1) (cond ((atom (car args)) 't1)
                              (t 'nil1)))
      ((eq func 'equal1) (cond ((equal (car args) (cadr args)) 't1) (t 'nil1)))
      (t (expressiont t "~%Unknown function: ~S" func))))
      ((eq (car func) 'lambda1) (my-eval (caddr func)
                                       (create-links (cadr func) args links)))
      (t (expressiont t "~%It's not the lambdas call: ~S" func))))


(defun create-links
  (expressionl factik env)
    (cond
      ((null expressionl) env)
      (t (acons (car expressionl)
                (car factik)
                (create-links (cdr expressionl)
                              (cdr factik)
                              env)))))


(defun eval-list (params links)
  (cond
    ((null params) nil)
    (t (cons (my-eval (car params) links)
              (eval-list (cdr params) links)))))


;(print (my-eval (* 5 2 4)))
