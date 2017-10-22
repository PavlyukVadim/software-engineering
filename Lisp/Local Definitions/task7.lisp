(setq vowels '(а е ё и о у ы э ю я))

(defun split-str (src)
  (setq wordlist (list))
  (setq len (strlen src))
  (setq cnt 0)
  (setq letter cnt)
  (while (setq cnt (vl-string-search pat src letter))
    (setq word (substr src (1+ letter) (- cnt letter)))
    (setq letter (+ cnt len))
    (setq wordlist (append wordlist (list word))))
  (setq wordlist (append wordlist (list (substr src (1+ letter)))))) 

(defun vowel?(chr lst_vowels)
  (member chr lst_vowels))
 
(defun ins (s)
  (cond ((vowel? s vowels) (pack (list s '-)))
        (t s)))
 
(defun divide-word (word)
  (cond
    ((null word) nil)
      (cons (ins (car word)) (divide-word (cdr word)))))
 
(defun syllables (txt)
  (mapcar #'(lambda (s) (pack (divide-word (unpack s)))) txt))
 
(defun divide-string (txt)
  (mapcar #'(lambda (s) (syllables s)) (split-str txt)))

(print (divide-string "пример текста"))
