data Tree= Empty|Leaf Char|Branch Char Tree Tree deriving Show

getHead		::Tree->Char
getHead(Branch op tree1 tree2) = op
getHead(Leaf no)='0' 

isEmpty		::Tree->Bool
isEmpty(Empty)=True
isEmpty(Branch op tree1 tree2)=False
isEmpty(Leaf no)=False

isUnary		::Tree->Bool
isUnary(Branch op tree1 tree2)= isEmpty(tree1)||isEmpty(tree2)

treetoinfix	:: Tree ->String
treetoinfix(Empty)=""
treetoinfix(Leaf no) = [no]
treetoinfix(Branch op tree1 tree2)=
	case op of
	'+'->treetoinfix tree1 ++ [op] ++ treetoinfix tree2
	'-' -> 
		case isEmpty(tree1) of
		True-> [op] ++
			case getHead(tree2) of
				'+'-> ['('] ++ treetoinfix tree2 ++[')']
				'-' -> 
					case isUnary(tree2) of
					True->treetoinfix tree2
					False->['('] ++ treetoinfix tree2 ++[')']
				'*'-> treetoinfix tree2
				'/' -> treetoinfix tree2
				'0'-> treetoinfix tree2
		False->
			case isEmpty(tree2) of
			True->[op] ++
				case getHead(tree1) of
				'+'-> ['('] ++ treetoinfix tree1 ++[')']
				'-' -> 
					case isUnary(tree1) of
					True->treetoinfix tree1
					False->['('] ++ treetoinfix tree1 ++[')']
				'*'-> treetoinfix tree1
				'/' -> treetoinfix tree1
				'0'-> treetoinfix tree1
			False->
				case getHead(tree2) of
				'+'->treetoinfix tree1 ++ [op] ++ ['('] ++ treetoinfix tree2 ++[')']
				'-' -> treetoinfix tree1 ++ [op] ++ 
					case isUnary(tree2) of
					True->treetoinfix tree2
					False->['('] ++ treetoinfix tree2 ++[')']
				'*'->  treetoinfix tree1 ++ [op] ++ treetoinfix tree2
				'/' ->  treetoinfix tree1 ++ [op] ++ treetoinfix tree2
				'0'->  treetoinfix tree1 ++ [op] ++  treetoinfix tree2
	'*'->
		case getHead(tree1) of
		'+'->['(']++treetoinfix tree1++[')']  
		'-' ->
			case isUnary(tree1) of
			True->treetoinfix tree1
			False->['(']++treetoinfix tree1 ++[')']	
		'*'-> treetoinfix tree1   
		'/' -> treetoinfix tree1
		'0'-> treetoinfix tree1
		++ [op]++
		case getHead(tree2) of
		'+'->['(']++treetoinfix tree2++[')']  
		'-' ->
			case isUnary(tree2) of
			True->treetoinfix tree2
			False->['(']++treetoinfix tree2 ++[')']
		'*'-> treetoinfix tree2   
		'/' -> treetoinfix tree2
		'0'-> treetoinfix tree2
	'/'->
		case getHead(tree1) of
		'+'->['(']++treetoinfix tree1++[')']  
		'-' ->
			case isUnary(tree1) of
			True->treetoinfix tree1
			False->['(']++treetoinfix tree1 ++[')']
		'*'-> treetoinfix tree1   
		'/' -> treetoinfix tree1
		'0'-> treetoinfix tree1
		++ [op]++
		case getHead(tree2) of
		'+'->['(']++treetoinfix tree2++[')']  
		'-' ->
			case isUnary(tree2) of
			True->treetoinfix tree2
			False->['(']++treetoinfix tree2 ++[')']
		'*'->['('] ++treetoinfix tree2 ++[')']
		'/' ->['('] ++treetoinfix tree2++[')']
		'0'-> treetoinfix tree2