; Caesar Cipher in Lisp

(defun encipher-char (ch key)
  (let* ((c  (char-code  ch)) (la (char-code #\a)) (ua (char-code #\A))
         (base (cond ((<= la c (char-code #\z)) la)
                     ((<= ua c (char-code #\Z)) ua)
                     (nil))))
    (if base (code-char (+ (mod (+ (- c base) key) 26) base)) ch)))

(defun caesar-cipher (str key)
  (map 'string #'(lambda (c) (encipher-char c key)) str))

(defun caesar-decipher (str key) (caesar-cipher str (- key)))

;(print (caesar-cipher "hello world" 1))
