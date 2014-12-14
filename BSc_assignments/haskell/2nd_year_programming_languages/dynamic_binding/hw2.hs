import Hw2_Data

isFunc::Decl->Bool
isFunc(Func {name=a , locals=b, body=c })=True
isFunc(Var x)=False

isUse::Command->Bool
isUse(UseVar x)=True
isUse(CallFunc x)=False

comStr::Command->String
comStr(UseVar str)=str
comStr(CallFunc str)=str

varName::Decl->String
varName(Var str)=str

lasts::[a]->a
lasts [x] = x
lasts (x:xs) = lasts xs 

addStack		::[(String,String)]->String->Decls->[(String,String)]

addStack st scope [ ]		= st
addStack st scope (x:xs)
		|isFunc x 	= addStack st scope xs 
		|otherwise 	= addStack (st ++[(scope, varName x)]) scope xs


addFuncStack		::[(String,Decl)]->String->Decls->[(String,Decl)]

addFuncStack fs scope [ ] 	= fs
addFuncStack fs scope (x:xs)
		|isFunc x	= addFuncStack (fs ++ [(scope, x)]) scope xs
		|otherwise	= addFuncStack fs scope xs


searchVar		::String->[(String,String)]->String->String

searchVar str [ ] result	= result
searchVar str (x:xs) result
		|(snd x == str)	= searchVar str xs ((fst x) ++ ":" ++ str)
		|otherwise	= searchVar str xs result


findFunc		::String->[(String,Decl)]->(String,Decl)->(String,Decl)

findFunc str [ ] f	 	= f
findFunc str (x:xs) f
	|name(snd x)== str	= findFunc str xs x
	|otherwise		= findFunc str xs f


execute			::[Command]->[(String,String)]->[(String,Decl)]->String->([String], Bool)

execute [ ] st fs scope	= (["Return "++ scope],False)
execute (x:xs) st fs scope

	|isUse x 	= let 
				w =(searchVar (comStr x) st [ ]) 
			  in if w==[]
				then (["Invalid reference "++ (comStr x)], True)
				else  
					let 
						result = (execute xs st fs scope) 
					in if (snd result)
						then (["Use Variable "++ w] ++ (fst result) , True)
						else (["Use Variable "++ w] ++ (fst result) , False)
	
	|otherwise	= let 
				f = findFunc (comStr x) fs ([],Func {name=[], locals=[], body=[]})
			  in if (fst f)==[]	
				then  (["Function " ++ (comStr x) ++ " is not found"], True)
				else  	
					let 
						w  = (fst f) ++ ":" ++ name(snd f) 
						p1 = execute (body(snd f)) (addStack st w (locals(snd f))) (addFuncStack fs w (locals(snd f))) w
						p2 = execute xs st fs scope
					in if (snd p1)
						then (["Call "++ w] ++ (fst p1) , True)
						else (["Call "++ w] ++ (fst p1) ++ (fst p2) , False)


trace3			::[(String,String)]->[(String,Decl)]->[(String,Decl)]->[String]
trace3 st fs [ ]		= ["Error: main is not found"]
trace3 st fs (x:xs)
	|name(snd x)=="main"	= ["Call global:main"] ++ 
		fst (execute (body(snd x)) (addStack st "global:main" (locals(snd x))) (addFuncStack fs "global:main" (locals(snd x))) "global:main")
	|otherwise		= trace3 st fs xs


trace2			::Decls->[(String,String)]->[(String,Decl)]->[String]

trace2 [ ] st fs 		= trace3 st fs fs
trace2 (x:xs) st fs
	|isFunc x		= trace2 xs st (fs ++ [("global" , x)])
	|otherwise		= trace2 xs (st ++ [("global" , varName x)] ) fs


trace			:: Decls -> [String]
trace x = trace2 x [ ] [ ]





