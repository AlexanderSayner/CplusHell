# CPlusHell
Test project on Unreal Engine 4

Russian language is coming soon...

Тестовый проект с игрой на Unreal Engine 4. 

Разработка документации на русском языке ведётся и будет опубликована здесь в будущих обновлениях.

## Table of contents
1. [Game made on Unreal Engine 4](#game-made-on-unreal-engine-4)
2. [Clone repository with HTTP](#clone-repository-with-http)
3. [For developers](#for-developers)
4. [Code conventions](#code-conventions)

#### Game made on Unreal Engine 4
[Table of contents](#Table-of-contents)

This game is my sandbox. 
Made with Unreal Engine 4.26 

#### Clone repository with HTTP
[Table of contents](#Table-of-contents)

Go to the folder you want to download project. Type 
```shall
git clone https://github.com/AlexanderSayner/CplusHell.git
```

Then see CplusHell folder with a project.
For opening project in unreal editor just double click on CplusHell.uproject file.
Fot editing sources in your IDE, double click on CplusHell.sln file.

In Editor you can change default IDE for Unreal Engine. Click Edit -> Editor Preferences -> Source Code -> chose your favourite IDE in Source Code Editor option. 

#### For developer launch
[Table of contents](#Table-of-contents)

First of all, install MC Visual Studio Community 2019 for Unreal Engine. Then open the solution on directory root. Starting debug splution initialise opening Unreal Engine 4 editor.

Or just open solution and Unreal Engine project in the same time, then in Visual Studion go 

Debug -> Attach to Process... -> start filter with "edit" -> attach unreal engine editor

Then VS should start debug process.

Also you can use another IDE that you like.    

#### Code conventions
[Table of contents](#Table-of-contents)

Declaration rules
* Constructor
* Delegates
* UFUNCTION
* Casual functions

Commit messages should contain only Latin symbols and numbers. Punctuation marks are not allowed. Every word in commit message should begin with upper case letter. Only upper case commit messages are inappropriate. 

Before commit you must be sure that project hasn't got any build errors and packaging is fine.

Any warnings in console are not welcome.  
