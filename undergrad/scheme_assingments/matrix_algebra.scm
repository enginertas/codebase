;********Rational simplifier*************
(define (simplify num denum) 
            (let ((A (gcd num denum))) 
              (let ((B (list (/ num A) (/ denum A))))
                    (if (= (last B) 1) (first  B) B))))

;********Defining the type of the variable in functions(matrix or rational operations)
(define (ls? a)
	(if (list? a) (if (list? (car a)) #t #f) #f)) 

;********Sumation of two lists***********
(define (list-sum rat1 rat2)
	(let ((ONE (car rat1)))  
   	  (let ((TWO (cadr rat1))) 
            (let ((THREE (car rat2))) 
             (let ((FOUR (cadr rat2)))
              (let ((NUM (+ (* ONE FOUR) (* TWO THREE)))) 
               (let ((DENUM (* TWO FOUR)))
                (simplify NUM DENUM))))))))

;********Sumation of one list and a rational*****
(define (list-int-sum int rat)
      (list (+ (car rat) (* int (cadr rat))) (cadr rat)))

;********Sumation of two rationals********
(define (sum-two-rat rat1 rat2)
   (if (list? rat1) 
     (if (list? rat2)  (list-sum rat1 rat2) (list-int-sum rat2 rat1))
     (if (list? rat2)  (list-int-sum rat1 rat2) (+ rat1 rat2))))

;********Sumation of lots of rationals*****
(define (ratsum sumlist) (reduce (lambda (x y) (sum-two-rat x y)) sumlist))

;********Difference between two rationals**
(define (ratdiff rat1 rat2)
    (if (list? rat1) 
       (if (list? rat2)  (list-diff rat1 rat2) (list-int-diff rat1 rat2))
       (if (list? rat2)  (list-int-diff rat1 rat2) (- rat1 rat2))))

;********Difference between the lists******
(define (list-diff rat1 rat2)
  (let ((ONE (car rat1)))  
    (let ((TWO (cadr rat1))) 
     (let ((THREE (car rat2))) 
      (let ((FOUR (cadr rat2)))
       (let ((NUM (- (* ONE FOUR) (* TWO THREE)))) 
        (let ((DENUM (* TWO FOUR)))
          (simplify NUM DENUM))))))))

;********Difference between a list and a number
(define (list-int-diff rat1 rat2)
   (if (list? rat1) (list (- (car rat1) (* (cadr rat1) rat2)) (cadr rat1))
	(list (- (* rat1 (cadr rat2)) (car rat2)) (cadr rat2))))

;********Multiplication of two rationals***
(define (multi-two-rat rat1 rat2)
	(if (list? rat1)
	   (if (list? rat2) (list-multi rat1 rat2) (list-int-multi rat2 rat1))
	   (if (list? rat2) (list-int-multi rat1 rat2) (* rat1 rat2))))

;*********Multiplication of a number and a list***
(define (list-int-multi int rat)
	(simplify (* int (car rat)) (* (cadr rat))))

;**********Multiplication of lists
(define (list-multi rat1 rat2)
   (let ((NUM (* (car rat1) (car rat2))))
     (let ((DENUM (* (cadr rat1) (cadr rat2))))
	(simplify NUM DENUM))))

;********Sumation of rows of matrices*******
(define (sum-row row1 row2)
  (if (null? row1) '()
   (cons (sum-two-rat (car row1) (car row2)) (sum-row (cdr row1) (cdr row2)))))

;********Sumation of two matrices***********
(define (sum-two-matrix matrix1 matrix2)
  (if (null? matrix1) '()
   (cons (sum-row (car matrix1) (car matrix2))
	(sum-two-matrix (cdr matrix1) (cdr matrix2)))))

;********Sumation of lots of matrices*******
(define (matrix-sum sumlist)
  (reduce (lambda (x y) (sum-two-matrix x y)) sumlist))

;********Major sum operation****************
(define (majorsum sumlist)
  (let ((A (car sumlist))) (if (ls? A) (matrix-sum sumlist) (ratsum sumlist))))

;********Difference between rows************
(define (diff-row row1 row2)
  (if (null? row1) '()
   (cons (ratdiff (car row1) (car row2)) (diff-row (cdr row1) (cdr row2)))))

;********Difference between matrices*******
(define (matdiff difflist)
  (let ((A (car difflist))) 
   (let ((B (cadr difflist)))
    (if (null? A) '()
     (cons (diff-row (car A) (car B))
	(matdiff (list (cdr A) (cdr B))))))))

;*******Major difference operation*********
(define (majordiff difflist)
  (let ((A (car difflist))) 
   (let ((B (cadr difflist)))
    (if (ls? A) 
	(matdiff difflist) (ratdiff A B)))))

;********Multiplying row by a rational******
(define (row-by-rational a row)
   (if (null? row) '()
     (cons (multi-two-rat a (car row)) (row-by-rational a (cdr row)))))

;********Multiplying matrix by a rational***
(define (matrix-by-rational a matrix) ;multiplyer a matrix by rational number
  (if (null? matrix) '()
   (cons (row-by-rational a (car matrix))
	(matrix-by-rational a (cdr matrix)))))

;********Multiplying matrix by a matrix******
;****Changes the rows and coloumns with each other like transpoze
(define (transpoze matrix)
    (if (null? (cadr matrix)) '()
	(cons (map car matrix) (transpoze (map cdr matrix)))))

;********Multiplying two rows(coloumns are changed to rows before)****
(define (multi-rows row1 row2) (ratsum (multi-rows-helper row1 row2)))

(define (multi-rows-helper row1 row2)
    (if (null? row1) '()
      (cons (multi-two-rat (car row1) (car row2)) (multi-rows-helper (cdr row1) (cdr row2)))))

;********Multiplying matrix by row***********
(define (matrix-by-row row matrix)
	(if (null? matrix) '()
	(cons (multi-rows row (car matrix)) (matrix-by-row row (cdr matrix)))))

;********Multiplying two matrices*******
(define (matrix-by-matrix matrix1 matrix2) (matrix-helper matrix1 (transpoze matrix2))) 

(define (matrix-helper matrix1 matrix2)
	(if (null? matrix1) '()
	(cons (matrix-by-row (car matrix1) matrix2) (matrix-helper (cdr matrix1) matrix2))))

;********Major Multiplication************
(define (multimajor multilist)
   (reduce (lambda (x y) 
	(if (ls? x) 
	 (if (ls? y) (matrix-by-matrix x y) (matrix-by-rational y x))
	    (if (ls? y) (matrix-by-rational x y) (multi-two-rat x y)))) multilist)) 

;********mateval: main function******
(define (mateval worktree)
   (if (null? worktree) '() 
    (let ((A (car worktree)))
      (cond ( (equal? A '+) (majorsum (mateval (cdr worktree))))
	    ( (equal? A '-) (majordiff (mateval (cdr worktree))))
	    ( (equal? A '*) (multimajor (mateval (cdr worktree))))
	    ( (equal? A 'matinv) (matinv (mateval (cadr worktree))))
	    ( (list? A)    (cons (mateval A) (mateval (cdr worktree))))
	    ( else (cons A (mateval (cdr worktree))))))))

;****************After that part matrix inversion************
;************************************************************
;********Makes an identity row**********
(define (identity-row n1 n2)
 	(if (= n2 0) '() 
        (cons (if (= n1 n2) 1 0) (identity-row n1 (- n2 1)))))

;*********Composes a matrix with identity matrix*********
(define (compose matrix n1 n2)
	(if (null? matrix) '()
	(cons (append (car matrix) (identity-row n1 n2)) 
	 	(compose (cdr matrix) (- n1 1) n2))))

;*********Decomposes matrix and gets inverse matrix*******
(define (decompose matrix n)
	(if (null? matrix) '()
	  (cons ((repeated cdr n) (car matrix)) (decompose (cdr matrix) n))))

;********Makes row operation for elimination******
(define (row-operation refrow row x)
    (diff-row row (row-by-rational 
	(multi-two-rat (turn (car ((repeated cdr x) refrow))) (car ((repeated cdr x) row)))
		refrow)))

;********Makes reference operation for elimination
(define (ref-operation refrow x)
	(row-by-rational (turn (car ((repeated cdr x) refrow))) refrow))

;********Inverses a rational*********************
(define (turn rat) 
  (let ((A (if (list? rat) 
    (list (cadr rat) (car rat)) (list 1 rat))))
      (let ((B (cadr A))) (if (< B 0) (list (- (car A)) (- B)) A)))) 

;*******Interchanges a matrix********************
(define (interchange matrix n1 n2 f)
   (let ((X (car matrix)))
     (if (= n1 n2) 
	(if (equal? (car ((repeated cdr f) X)) 0)
	   (find-row matrix f) matrix)
	      (cons X (interchange (cdr matrix) (- n1 1) n2 f)))))

;*******Finds a suitable row if current row isn't suitable*******
(define (find-row matrix f)
  (let ((A (car matrix)))
    (if (null? matrix) '() 
      (if (equal? (car ((repeated cdr f) A)) 0)
	(append (find-row (cdr matrix) f) (list A)) matrix))))

;********Elimination in rows****************
(define (eliminate-in-rows matrix n1 n2 refrow f)
  (if (= n1 0) '()
    (let ((A (car matrix)))
      (if (= n1 n2) (cons (ref-operation A f)
	(eliminate-in-rows (cdr matrix) (- n1 1) n2 refrow f)) 
	  (cons (row-operation refrow A f) 
	   (eliminate-in-rows (cdr matrix) (- n1 1) n2 refrow f))))))

;********Elimination in cols******************
(define (eliminate-in-cols matrix n1 n-cons)
  (if (= n1 0) matrix
    (let ((F (- n-cons n1)))
      (let ((MATRIX (interchange matrix n-cons n1  F)))
	(let ((REFROW (car ((repeated cdr F) MATRIX))))
 (eliminate-in-cols (eliminate-in-rows MATRIX  n-cons n1 REFROW F) (- n1 1) n-cons))))))

;********Here is the matrix inversion - Gauss-Jordan Elimination***********
(define (matinv matrix)
   (let ((N (count matrix)))
     (let ((MATRIX (compose matrix N N))) 
       (let ((OPER (eliminate-in-cols MATRIX N N)))
	 (decompose OPER N)))))

