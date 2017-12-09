(defun make-relay (production type model)
  (list :production production :type type :model model))

; global variable
(defvar *db* nil)

; add new record
(defun add-record (relay)
  (push relay *db*))

; formatted output
(defun dump-db ()
  (dolist (relay *db*)
    (format t "~{~a:~10t~a~%~}~%" relay)))

; select values from db
(defun select (selector-fn)
  (remove-if-not selector-fn *db*))

; get type of relay
(defun type-selector (type)
  (lambda (relay) (equal (getf relay :type) type)))

; generates expression, that returns all records about relays
(defun where (&key production type model)
  (lambda (relay)
    (and
      (if production (equal (getf relay :production) production) t)
      (if type (equal (getf relay :type) type) t)
      (if model (equal (getf relay :model) model) t))))

; update and use args to set new value
(defun update (selector-fn &key production type model (ripped nil ripped-p))
  (setf *db*
    (mapcar
      (lambda (row)
        (when (funcall selector-fn row)
          (if production (setf (getf row :production) production))
          (if type (setf (getf row :type) type))
          (if model (setf (getf row :model) model)))
        row)
      *db*)))

; remove strings from db
(defun delete-rows (selector-fn)
  (setf *db* (remove-if selector-fn *db*)))

; search by value
(defun make-comparison-expr (field value)
  (list 'equal (list 'getf 'relay field) value))
