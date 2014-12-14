module Hw2_Data where

data Decl = Var String | Func { name::String, locals::Decls, body::[Command] }

type Decls = [Decl]

data Command = UseVar String | CallFunc String
         deriving Show


instance Show Decl where
        show t = prettyprint t "" where
                prettyprint (Func {name=n, locals=l, body=com}) ind =
                        let
                                pplocals [] = ""
                                pplocals (a:ar) = (prettyprint a (ind ++ "    ")) ++ "\n" ++ (pplocals ar)
                                ppcoms [] = ""
                                ppcoms ((UseVar s):rest) = ind ++ "    " ++ s ++ ";\n" ++ (ppcoms rest)
                                ppcoms ((CallFunc s):rest) = ind ++ "    " ++ s ++ "();\n" ++ (ppcoms rest)
                        in
                                ind ++ "function " ++ n ++ "() {" ++ "\n" ++
                                (pplocals l) ++ "\n" ++ (ppcoms com) ++ ind ++ "}"
                prettyprint (Var s) ind =  ind ++ "var " ++ s ++ ";"
