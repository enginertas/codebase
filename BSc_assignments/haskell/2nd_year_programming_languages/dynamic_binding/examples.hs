addStack([ ("global", "a"),  ("global:f", "g")]) "global:g:h" [Var "b",Func {name="main",locals=[Var "x", Var "y"],body=[UseVar "x", CallFunc "f"]} ,Var "a"]
addStack([ ("global", "main"),  ("global:f", "g")]) "global:g:h" []
addStack([ ("global", "main"),  ("global:f", "g")]) "global:g:h" [Func {name="main",locals=[Var "x", Var "y"],body=[UseVar "x", CallFunc "f"]}]


addFuncStack [("global:f",Func {name="main",locals=[Var "x", Var "y"],body=[UseVar "x", CallFunc "f"]})] "global:g:h" [Var "a", Var "b",Func {name="main",locals=[Var "x", Var "y"],body=[UseVar "x", CallFunc "f"]}, Var "a"]

searchVar "a" [("global","a"),("global:f","g"),("global:g:h","b"),("global:g:h","a")] [ ]
searchVar "g" [("global","a"),("global:f","g"),("global:g:h","b"),("global:g:h","a")] [ ]
searchVar "c" [("global","a"),("global:f","g"),("global:g:h","b"),("global:g:h","a")] [ ]


trace [Var "x",Var "y",Func{name="h",locals=[Var "a",Func{name="g",locals=[Var"x",Func{name="f",locals=[Var "x"],body=[UseVar "x"]}],body=[CallFunc "f",UseVar "x"]}],body=[CallFunc "f",CallFunc "g"]},Func{name="main",locals=[Var "x",Var "y"],body=[UseVar"x",CallFunc "h"]}]

