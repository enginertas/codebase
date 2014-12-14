(define (next month)
        (first (bf (member month '(january february march april may june july august september october november december)))))

(define (divisable? no x) (= (remainder no x) 0))

(define (leap_year year) (if (divisable? year 100 ) 
                        (divisable? year 400) (divisable? year 4)))

(define (next_day date) 
  (cond ( (equal? (first (bf date)) 'february) 
        (cond ( (< (first date) 28) (se (+ (first date) 1) (bf date)))
              ( (= (first date) 28) (if (leap_year (last date)) (se (+ (first date) 1) (bf date)) (se '1 'March (last date))))
              (  (= (first date) 29) (if (leap_year (last date)) (se '1 'March (last date)) '(invalid date)))
              ( else '(invalid date))))
        
        ( (equal? (first (bf date)) 'december)
        (cond ( (< (first date) 31) (se (+ (first date) 1) (bf date)))
              ( (= (first date) 31) (se '1 'January (+ (last date) 1)))
              ( else '(invalid date))))

        ( (member? (first (bf date)) '(january march may july august october))
        (cond ( (< (first date) 31) (se (+ (first date) 1) (bf date)))
              ( (= (first date) 31) (se '1 (next (first (bf date))) (last date)))
              ( else '(invalid date))))
        
        ( (member? (first (bf date)) '(april june september november))
        (cond ( (< (first date) 30) (se (+ (first date) 1) (bf date)))
              ( (= (first date) 30) (se '1 (next (first (bf date))) (last date)))
              (else '(invalid date))))))
