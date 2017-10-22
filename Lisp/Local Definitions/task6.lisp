; check if letter is vowel
(defun vowel? (char) (find char "aeiou" :test #'char-equal))


; count number of vowels letters in string
; (print (count-vowels "Hello World")) 3
(defun count-vowels (str)
  (defun vowel? (char) (find char "aeiou" :test #'char-equal))
  (cond ((= (length str) 0) 0)
        ((vowel? (char str 0)) (+ 1 (count-vowels (subseq str 1))))
        (t (count-vowels (subseq str 1)))))
    

(defun comparator-by-vowels(str1 str2)
  (cond ((> (count-vowels str1) (count-vowels str2)) T)))


(defun sort-strings-by-vowels (vector)
  (sort vector #'comparator-by-vowels))


(defun sort-text-by-vowels (text)
  (cond ((NULL text) NIL)
        (t (cons (sort-strings-by-vowels (car text)) (sort-text-by-vowels (cdr text))))))

(print (sort-text-by-vowels '(("Hello" "World") ("Heeeo" "Woooooorld") ("dsfsH" "aaaa"))))
