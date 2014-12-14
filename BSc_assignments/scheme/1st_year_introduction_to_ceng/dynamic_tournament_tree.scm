;*****dtt-cons****Making initial position******
(define (dtt-cons firstTourMatches)
	(dtt-cons-helper (make-query firstTourMatches) (count firstTourMatches)))

(define (dtt-cons-helper firstTourMatches n) 
;when only one match is played in tour delete the extra '(? ?)
 (cond ((< n 2) (make-node '? (children (car firstTourMatches))))
       ((= n 2) (make-node '? firstTourMatches)) ;when count=2, combine solely with ?
       (else (dtt-cons-helper (make-tree firstTourMatches) (/ n 2)))))

(define (make-query firstTourMatches) ;combining of ? and team name
  (if (null? firstTourMatches) '() (let ((A (car firstTourMatches)))
     (cons (make-node '(? ?) (list (make-node (list (car A) '?) '())
       (make-node (list (cadr A) '?) '()))) (make-query (cdr firstTourMatches))))))

(define (make-tree firstTourMatches) ;make entire tree if count>2
  (if (null? firstTourMatches) '() (let ((A (cdr firstTourMatches)))
     (make-node (make-node '(? ?) (append (make-node (car firstTourMatches) '())
      	(make-node (car A) '())))  (make-tree (cdr A))))))

;******dtt-matches***to see which matches will be played***
(define (dtt-matches tournamentTree) (dtt-matches-helper (children tournamentTree)))

(define (dtt-matches-helper tournamentTree)
  (if (null? tournamentTree) '()
    (let ((A (car tournamentTree))) (let ((Y (cadr tournamentTree)))
     (let ((AD (datum A))) (let ((X (car AD)))
      (if (equal? (cadr AD) '?)
         (if (equal? X '?)
	  (append (dtt-matches-helper (children A)) (dtt-matches-helper (children Y)))
	   (cons (list X (car (datum Y)))
		 (dtt-matches-helper (children Y)))) '())))))))

;*******dtt-update - update the tree********
(define (dtt-update tournamentTree tourMatches) ;****updating the first part
 (let ((C (children tournamentTree)))  
   (let ((A (car C))) (let ((B (cadr C))) 
     (let ((AD (datum A))) (let ((X (car AD))) (let ((Y (car (datum B))))
       (if (equal? X '?)
 	(make-node '? (append (make-node (dtt-update-helper (children A) tourMatches) '()) 
	 		      (make-node (dtt-update-helper (children B) tourMatches) '())))
	  (let ((SEARCH (search-list X Y tourMatches))) (make-node (caddr SEARCH) 
       (list (make-node (list X (car SEARCH)) (dtt-update-helper (children A) tourMatches))
       	     (make-node (list Y (cadr SEARCH)) 
	     (dtt-update-helper (children B) tourMatches)))))))))))))

(define (dtt-update-helper tournamentTree tourMatches) ;***updating the rest
 (if (null? tournamentTree) '() 
    (let ((A (car tournamentTree))) (let ((B (cadr tournamentTree))) 
     (let ((AD (datum A))) (let ((X (car AD))) (let ((Y (car (datum B))))
       (if (equal? (cadr AD) '?) 
        (if (equal? X '?)  (make-node '(? ?)
 	  (append (make-node (dtt-update-helper (children A) tourMatches) '())
                  (make-node (dtt-update-helper (children B) tourMatches) '())))
  (let ((SEARCH (search-list X Y tourMatches)))
    (make-node (list (caddr SEARCH) '?) 
     (list (make-node (list X (car SEARCH)) (dtt-update-helper (children A) tourMatches))
       	   (make-node (list Y (cadr SEARCH)) 
	     (dtt-update-helper (children B) tourMatches)))))) tournamentTree))))))))

(define (search-list team1 team2 tourMatches) ;****score entering and determining the winner
  (if (null? tourMatches) '(? ?)
    (let ((A (car tourMatches))) (let ((Score1 (cadr A))) (let ((Score2 (cadddr A)))
      (cond ((equal? team1 (car A)) (list Score1 Score2
		(if (> Score1 Score2) team1 team2)))
	    ((equal? team1 (caddr A)) (list Score2 Score1 
		(if (> Score1 Score2) team2 team1)))
	    (else (search-list team1 team2 (cdr tourMatches)))))))))