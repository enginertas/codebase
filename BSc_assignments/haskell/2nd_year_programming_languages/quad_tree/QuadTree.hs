module QuadTree (QuadTree,new,insert,delete,(+),(-),(*),negate) where
	
data QuadTree = Null |Empty Point Point | Full Point Point | Tree Point Point QuadTree QuadTree QuadTree QuadTree deriving Eq
type Point = (Integer,Integer)

empty		::QuadTree->Bool
empty(Empty p1 p2)=True
empty Null = False
empty (Full p1 p2)=False
empty (Tree p1 p2 qt1 qt2 qt3 qt4) = False

full		::QuadTree->Bool
full(Full p1 p2)=True
full Null = False
full (Empty p1 p2)=False
full (Tree p1 p2 qt1 qt2 qt3 qt4) = False

nll		::QuadTree->Bool
nll(Empty p1 p2)= False
nll Null = True
nll (Full p1 p2)=False
nll (Tree p1 p2 qt1 qt2 qt3 qt4) = False

isTree		::QuadTree->Bool
isTree (Empty p1 p2) =False
isTree Null = False
isTree (Full p1 p2)= False
isTree(Tree p1 p2 qt1 qt2 qt3 qt4) = True

getPoint1	::QuadTree->Point
getPoint1(Empty p1 p2)=p1
getPoint1(Full p1 p2)=p1
getPoint1(Tree p1 p2 qt1 qt2 qt3 qt4)=p1

getPoint2	::QuadTree->Point
getPoint2(Empty p1 p2)=p2
getPoint2(Full p1 p2)=p2
getPoint2(Tree p1 p2 qt1 qt2 qt3 qt4)=p2


upperleft	::QuadTree->QuadTree
upperleft(Tree p1 p2 qt1 qt2 qt3 qt4)= qt1
upperleft(Empty p1 p2)
	|((fst p1)==(fst p2))	= Null
	|otherwise 	= Empty ((fst p1),truncate (fromInteger((snd p2)+ (snd p1)+1)*0.5)) (truncate (fromInteger ((fst p1)+(fst p2)-1)*0.5),(snd p2))
upperleft(Full p1 p2)
	|((fst p1)==(fst p2))	= Null
	|otherwise 	= Full ((fst p1),truncate (fromInteger((snd p2)+ (snd p1)+1)*0.5)) (truncate (fromInteger ((fst p1)+(fst p2)-1)*0.5),(snd p2))
	
upperright	::QuadTree->QuadTree
upperright(Tree p1 p2 qt1 qt2 qt3 qt4)= qt2
upperright(Empty p1 p2)= Empty (truncate (fromInteger((fst p1)+(fst p2)+1)*0.5),truncate (fromInteger((snd p2)+ (snd p1)+1)*0.5)) p2
upperright(Full p1 p2) = Full (truncate (fromInteger((fst p1)+(fst p2)+1)*0.5),truncate (fromInteger((snd p2)+ (snd p1)+1)*0.5)) p2

bottomleft	::QuadTree->QuadTree
bottomleft(Tree p1 p2 qt1 qt2 qt3 qt4)= qt3
bottomleft(Empty p1 p2)
	|((fst p1) == (fst p2))||((snd p1)==(snd p2))	= Null
	|otherwise	= Empty p1 (truncate (fromInteger((fst p1)+(fst p2)-1)*0.5),truncate (fromInteger((snd p2)+ (snd p1)-1)*0.5))
bottomleft(Full p1 p2)
	|((fst p1) == (fst p2))||((snd p1)==(snd p2))	= Null
	|otherwise	= Full p1 (truncate (fromInteger((fst p1)+(fst p2)-1)*0.5),truncate (fromInteger((snd p2)+ (snd p1)-1)*0.5))

bottomright	::QuadTree->QuadTree
bottomright(Tree p1 p2 qt1 qt2 qt3 qt4)= qt4
bottomright(Empty p1 p2)
	|(snd p1)==(snd p2)	= Null
	|otherwise	= Empty (truncate (fromInteger ((fst p1)+(fst p2)+1)*0.5),(snd p1)) ((fst p2),truncate (fromInteger((snd p2)+ (snd p1)-1)*0.5))
bottomright(Full p1 p2)
	|(snd p1)==(snd p2)	= Null
	|otherwise	= Full (truncate (fromInteger ((fst p1)+(fst p2)+1)*0.5),(snd p1)) ((fst p2),truncate (fromInteger((snd p2)+ (snd p1)-1)*0.5))


new		::Integer->QuadTree
new n = Empty (0,0) (n-1, n-1)
		
putn		::Integer->String
putn 0 = ""
putn n = "\t" ++ putn (n-1)


instance Show QuadTree where
	show a = show2 a 0 0
		
show2		::QuadTree->Integer->Integer->String

show2 Null a x = ""

show2 (Empty p1 p2) a n
	|a==0 = "(" ++ "(" ++ show(fst p1) ++ "," ++ show(snd p1) ++ ")" ++" "++ "(" ++ show(fst p2) ++ "," ++ show(snd p2) ++ ")" ++ " "++ "Empty"++")"
	|otherwise	= "\t" ++ (show2 (Empty p1 p2) (a-1) n)

show2 (Full p1 p2) a n 
	|a==0 ="(" ++ "(" ++ show(fst p1) ++ "," ++ show(snd p1) ++ ")" ++ " "++ "(" ++ show(fst p2) ++ "," ++ show(snd p2) ++ ")" ++ " "++ "Full"++")"
	|otherwise 	= "\t" ++ (show2 (Full p1 p2) (a-1) n)

show2 (Tree p1 p2 qt1 qt2 qt3 qt4) a n 
	|a==0 = let
			s1 = (show2 qt2 (n+1) (n+1))
			x1 = if s1=="" then "" else "\n"++s1
			s2 = (show2 qt1 (n+1) (n+1))
			x2 = if s2=="" then "" else "\n"++s2
			s3 = (show2 qt3 (n+1) (n+1))
			x3 = if s3=="" then "" else "\n"++s3
			s4 = (show2 qt4 (n+1) (n+1)) 
			x4 = if s4=="" then "" else "\n"++s4
		in "(" ++ x1 ++ x2 ++ x3 ++ x4 ++ "\n" ++ (putn n) ++ ")"
	 
	|otherwise = "\t"++ show2 (Tree p1 p2 qt1 qt2 qt3 qt4) (a-1) n 

checkIfInside	::Integer->Integer->Point->Bool
checkIfInside x y (p1,p2)
	|x>y		= False
	|x>=p1 && x<=p2	= True
	|otherwise	= checkIfInside (x+1) y (p1,p2)


doesInclude	::QuadTree->Point->Point->Bool
doesInclude qt p1 p2 =
	let 	point1 = getPoint1(qt)
		point2 = getPoint2(qt)
	in	checkIfInside (fst point1) (fst point2) (fst p1, fst p2) && checkIfInside (snd point1) (snd point2) (snd p1, snd p2)

insert		::(Point,Point)->QuadTree->QuadTree
insert (p1,p2) Null = Null
insert (p1,p2) quad
	|((snd p1)>=(snd p2))&& ((fst p1)>=(fst p2)) =
		
		let 	point1 = getPoint1(quad)
			point2 = getPoint2(quad)
		
		in if(doesInclude quad p2 p1)
			then if ((doesInclude (Empty point1 point1) p2 p1) && (doesInclude (Empty point2 point2) p2 p1))
				then Full point1 point2
				else let l1 = (insert (p2,p1) (upperleft quad))
					 l2 = (insert (p2,p1) (upperright quad))
					 l3 = (insert (p2,p1) (bottomleft quad))
					 l4 = (insert (p2,p1) (bottomright quad))			
				     in if (((full l1)||(nll l1)) && (full l2) && ((nll l3) || (full l3)) && ((nll l4) || (full l4)))
						then Full point1 point2
						else Tree point1 point2 l1 l2 l3 l4 			 
			else quad
	
	|((snd p1)<=(snd p2))&& ((fst p1)<=(fst p2)) =
		
		let 	point1 = getPoint1(quad)
			point2 = getPoint2(quad)
		
		in if(doesInclude quad p1 p2)
			then if ((doesInclude (Empty point1 point1) p1 p2) && (doesInclude (Empty point2 point2) p1 p2))
				then Full point1 point2
				else let l1 = (insert (p1,p2) (upperleft quad))
					 l2 = (insert (p1,p2) (upperright quad))
					 l3 = (insert (p1,p2) (bottomleft quad))
					 l4 = (insert (p1,p2) (bottomright quad))			
				      in if (((full l1)||(nll l1)) && (full l2) && ((nll l3) || (full l3)) && ((nll l4) || (full l4)))
						then Full point1 point2
						else Tree point1 point2 l1 l2 l3 l4 			 
			else quad

delete		::(Point,Point)->QuadTree->QuadTree
delete (p1,p2) Null = Null
delete (p1,p2) quad
	|((snd p1)>=(snd p2)) && ((fst p1)>=(fst p2)) =
		
		let 	point1 = getPoint1(quad)
			point2 = getPoint2(quad)
		
		in if(doesInclude quad p2 p1)
			then if ((doesInclude (Empty point1 point1) p2 p1) && (doesInclude (Empty point2 point2) p2 p1))
				then Empty point1 point2
				else let l1 = (delete (p2,p1) (upperleft quad))
					 l2 = (delete (p2,p1) (upperright quad))
					 l3 = (delete (p2,p1) (bottomleft quad))
					 l4 = (delete (p2,p1) (bottomright quad))			
				     in if (((empty l1)||(nll l1)) && (empty l2) && ((nll l3) || (empty l3)) && ((nll l4) || (empty l4)))
						then Empty point1 point2
						else Tree point1 point2 l1 l2 l3 l4 			 
			else quad
	
	|((snd p1)<=(snd p2)) && ((fst p1)<=(fst p2)) =
		
		let 	point1 = getPoint1(quad)
			point2 = getPoint2(quad)
		
		in if(doesInclude quad p1 p2)
			then if ((doesInclude (Empty point1 point1) p1 p2) && (doesInclude (Empty point2 point2) p1 p2))
				then Empty point1 point2
				else let l1 = (delete (p1,p2) (upperleft quad))
					 l2 = (delete (p1,p2) (upperright quad))
					 l3 = (delete (p1,p2) (bottomleft quad))
					 l4 = (delete (p1,p2) (bottomright quad))			
				     in if (((empty l1)||(nll l1)) && (empty l2) && ((nll l3) || (empty l3)) && ((nll l4) || (empty l4)))
						then Empty point1 point2
						else Tree point1 point2 l1 l2 l3 l4 	 
			else quad

instance Num QuadTree where
	(+) Null Null = Null

	(+) (Empty p1 p2) qt
		|(p1==(getPoint1 qt) && p2==(getPoint2 qt)) = qt

	(+) (Full p1 p2) qt
		|(p1==(getPoint1 qt) && p2==(getPoint2 qt)) = (Full p1 p2)

	(+) (Tree p1 p2 qt1 qt2 qt3 qt4) qt
		|(isTree qt) && (p1==(getPoint1 qt) && p2==(getPoint2 qt))	
			= let 	l1 = qt1 + (upperleft qt)
				l2 = qt2 + (upperright qt)
				l3 = qt3 + (bottomleft qt)
				l4 = qt4 + (bottomright qt)
			  in
				if (((full l1)||(nll l1)) && (full l2) && ((nll l3) || (full l3)) && ((nll l4) || (full l4)))
					then (Full p1 p2)
					else (Tree p1 p2 l1 l2 l3 l4)
					
		|(empty qt)  && (p1==(getPoint1 qt) && p2==(getPoint2 qt))	= (Tree p1 p2 qt1 qt2 qt3 qt4)
		|(full qt)   && (p1==(getPoint1 qt) && p2==(getPoint2 qt))	= (Full p1 p2)

	
	negate Null = Null
	negate (Empty p1 p2) = Full p1 p2
	negate (Full p1 p2) = Empty p1 p2
	negate (Tree p1 p2 qt1 qt2 qt3 qt4) = Tree p1 p2 (negate qt1) (negate qt2) (negate qt3) (negate qt4)


	(-) Null Null = Null
	
	(-) (Empty p1 p2) qt
		|(p1==(getPoint1 qt) && p2==(getPoint2 qt)) = Empty p1 p2

	(-) (Full p1 p2) qt
		|(p1==(getPoint1 qt) && p2==(getPoint2 qt)) = negate qt

	(-) (Tree p1 p2 qt1 qt2 qt3 qt4) qt
		|(isTree qt) && (p1==(getPoint1 qt) && p2==(getPoint2 qt))
			= let 	l1 = qt1 - (upperleft qt)
				l2 = qt2 - (upperright qt)
				l3 = qt3 - (bottomleft qt)
				l4 = qt4 - (bottomright qt)
			  in if (((empty l1)||(nll l1)) && (empty l2) && ((nll l3) || (empty l3)) && ((nll l4) || (empty l4)))
				then (Empty p1 p2)
				else (Tree p1 p2 l1 l2 l3 l4)
		
		|(empty qt)  && (p1==(getPoint1 qt) && p2==(getPoint2 qt))	= (Tree p1 p2 qt1 qt2 qt3 qt4)
		|(full qt)   && (p1==(getPoint1 qt) && p2==(getPoint2 qt))	= Empty p1 p2


	(*) Null Null = Null
	
	(*) (Empty p1 p2) qt
		|(p1==(getPoint1 qt) && p2==(getPoint2 qt)) = Empty p1 p2

	(*) (Full p1 p2) qt
		|(p1==(getPoint1 qt) && p2==(getPoint2 qt)) = qt

	(*) (Tree p1 p2 qt1 qt2 qt3 qt4) qt
		|(isTree qt) && (p1==(getPoint1 qt) && p2==(getPoint2 qt))
			= let 	l1 = qt1 * (upperleft qt)
				l2 = qt2 * (upperright qt)
				l3 = qt3 * (bottomleft qt)
				l4 = qt4 * (bottomright qt)
			  in if (((empty l1)||(nll l1)) && (empty l2) && ((nll l3) || (empty l3)) && ((nll l4) || (empty l4)))
				then (Empty p1 p2)
				else (Tree p1 p2 l1 l2 l3 l4)

		|(empty qt)  && (p1==(getPoint1 qt) && p2==(getPoint2 qt))	= Empty p1 p2
		|(full qt)   && (p1==(getPoint1 qt) && p2==(getPoint2 qt))	= (Tree p1 p2 qt1 qt2 qt3 qt4)

	
