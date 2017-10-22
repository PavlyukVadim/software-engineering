; Language of the gossiper in Lisp

(defun split (word)
  (split-word nil
  (coerce (string word) 'list)))


(defun split-word (begin end)
  (cond
  ((null end) (list begin end))
  ((consonant? (first end))
  (split-word
  (v-end begin (first end))
  (rest end)))
  ((dolgaya-nach? end)
  (list (append begin
  (list (first end)
  (second end)))
  (cddr end)))
  (t (list (v-end begin (first end))
  (rest end)))))


(defun v-end (spisok element)
  (append spisok (list element)))

(defun vowel? (letter)
  (member letter *vowel*))
  
(setq *vowel* '(#\A #\E #\I #\O #\U #\Y #\a #\o));

(defun consonant? (letter)
  (not (vowel? letter)))


(defun dolgaya-nach? (word)
  (and (vowel? (first word))
  (eql (first word)
  (second word))))


(defun translate-word(word key)
  (let ((chastislova (split word))
  (chastikey (split key)))
  (vowel-length (first chastislova)
  (second chastislova)
  (first chastikey)
  (second chastikey))))


(defun vowel-length (begin1 end1 begin2 end2)
  (cond
    ((dolgaya-kon? begin1)
    (cond
    ((dolgaya-kon? begin2)
    (pom-chasti begin1 end1 begin2 end2))
    (t (pom-chasti (decrease begin1) end1
    (increase begin2) end2))))
    ((dolgaya-kon? begin2)
    (pom-chasti
    (increase begin1) end2
    (decrease begin2) end2))
    (t (pom-chasti begin1 end1 begin2 end2))))


(defun dolgaya-kon? (word)
  (dolgaya-nach? (reverse word)))


(defun decrease (slog)
  (if (not (rest slog))
    nil
    (cons (first slog) (decrease (rest slog)))))


(defun increase (slog)
  (if (null (rest slog))
  (cons (first slog) slog)
  (cons (first slog)
  (increase (rest slog)))))


(defun pom-chasti
  (begin1 end1 begin2 end2)
  (list (sozv begin1 end1)
  (sozv begin2 end2)))


(defun sozv (begin end)
  (cond ((join begin (forward end)))
        (t (join begin (back end)))))


(defun forward (word)
  (sublis
  '((#\U . #\Y) (#\A . #\a) (#\O . #\o))
  word))


(defun back (word)
  (sublis
  '((#\Y . #\U) (#\a . #\A) (#\o . #\O))
  word))
  (defun join(begin end)
  (intern (coerce (append begin end)
  'string)))


(print (translate-word 'hello 'world)
