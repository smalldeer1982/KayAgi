# A and B and Chess

## 题目描述

A和B正在准备参加编程比赛。

为了锻炼他们的逻辑思维能力从而更好地解决问题，A和B决定来下棋。在游戏期间，A突然想要知道哪位玩家占得了优势。

对于每个棋子我们知道它们的权势值：

皇后的值是9；
车的值是5；
象（相）的值是3；
骑士的值也是3；
卒（兵）的值是1；
国王的值不考虑在优势评估中.
一个玩家的优势值是他在棋盘上所有棋子权势值的总和。

因为A不喜欢算数，所以他请求你告诉他哪位玩家的占有优势？（即优势值更大）

## 说明/提示

对于样例一，白方总值为9，黑方总值为5，所以输出"White"。

对于样例二，两方总值均为39，输出"Draw"。

对于样例三，白方总值为9，黑方总值为16，输出"Black"。

Translated by @lonelysir

## 样例 #1

### 输入

```
...QK...
........
........
........
........
........
........
...rk...
```

### 输出

```
White
```

## 样例 #2

### 输入

```
rnbqkbnr
pppppppp
........
........
........
........
PPPPPPPP
RNBQKBNR
```

### 输出

```
Draw
```

## 样例 #3

### 输入

```
rppppppr
...k....
........
........
........
........
K...Q...
........
```

### 输出

```
Black
```

# 题解

## 作者：引领天下 (赞：8)

此题就是一个模拟题，但是如果一个个判断会很烦，而且代码量会很多，这里我就提出一种更好的方法：

事先开一个数值数组，对特殊的字符位置赋值

然后直接累加就好了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,s[200];//数值数组
//ans累加白方比黑房多的分数
char a;
int main(){
    s['Q']=9,s['q']=-9;
    //这里以白方为基准，其实用黑方也是一样的效果
    //既然对白方是9分，那么如果黑方再来一个就得是-9分（抵消）
    //以下同理
    s['R']=5,s['r']=-5;
    s['B']=s['N']=3,s['b']=s['n']=-3;
    s['P']=1,s['p']=-1;
    for (int i=0;i<8;i++)
    for (int j=0;j<8;j++){
        cin>>a;
        ans+=s[a];
    }
    if (ans<0)printf ("Black");//白方比黑方多负分，当然黑方输出
    else if (ans)printf ("White");//同理
    else printf ("Draw");
}
```

---

## 作者：唐太宗 (赞：3)

# 来发篇题解。。

其实这就是一道统计+模拟经典题,但一个个去判断很麻烦。这里介绍一个关联式容器map,这是一个下标可以是任何类型的东西的数组。如果不会的话,参考c++一本通第171页或者 [点这儿](https://baike.so.com/doc/5344447-10557937.html)

比如你可以定义一个map<string,int>q;意思是q是一个关联式容器，可以从string映射至int了,举个例子:你可以赋值,如q["wdjadf"]=2,那么q["wdjadf"]就有一个值2了。(如果没用万能头文件,要记得写#include<map>!
  
据此可以求出棋盘上白方黑方各自总和，比大小之后程序就AC啦\(^o^)/~

# 上代码:
```cpp
#include<bits/stdc++.h>//万能头文件,以后再也不用记得那么多复杂头文件啦
using namespace std;
map<char,int> ma;//定义关联式容器ma;
char x;
int i,answ,ansb;//白色总和与黑色总和
int main(){
	ios::sync_with_stdio(false);//优化，打消iostream输入输出缓存，使cin和cout与scanf和printf相差无几
	ma['Q']=9;ma['B']=3;
	ma['N']=3;ma['R']=5;
	ma['P']=1;ma['K']=0;
	ma['q']=9;ma['b']=3;
	ma['n']=3;ma['r']=5;
	ma['p']=1;ma['k']=0;
    //对皇后,卒等赋值(值为其权值)
	while(i!=64){
		i++;//输入64个字符
		cin>>x;//边输入边操作
	    if(x>='a'&&x<='z')ansb+=ma[x];
	    if(x>='A'&&x<='Z')answ+=ma[x];
	}//如果是小写，那么就是黑方的子;大写则是白方的子;否则是'.',不用考虑。
	if(ansb==answ)cout<<"Draw";
	if(answ>ansb)cout<<"White";
	if(answ<ansb)cout<<"Black";//比大小,输出何方优势大
	return 0;//千万别漏这句,考试会暴零的
}
```
求过

---

## 作者：Vader10 (赞：2)

### 这道题，就边输入边算分，输入完了，分就算完了，一比较就行了。
AC代码：
```
#include<iostream>
using namespace std;
char board[10][10];
int b,w;
int main(){
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            cin>>board[i][j];
            if(board[i][j]=='Q')w+=9;
            else if(board[i][j]=='R')w+=5;
            else if(board[i][j]=='B')w+=3;
            else if(board[i][j]=='N')w+=3;
            else if(board[i][j]=='P')w+=1;
            else if(board[i][j]=='q')b+=9;
            else if(board[i][j]=='r')b+=5;
            else if(board[i][j]=='b')b+=3;
            else if(board[i][j]=='n')b+=3;
            else if(board[i][j]=='p')b+=1;
        }
    }
    if(w==b)cout<<"Draw"<<endl;
    else if(w<b)cout<<"Black"<<endl;
    else cout<<"White"<<endl;
    return 0;
}
```

---

## 作者：yuzhechuan (赞：2)

```cpp
#include<bits/stdc++.h>//万能库
using namespace std;
int black,white;//变量名简单易懂
char c;
int main()
{
    while(cin>>c)//如果能读进...
    {   //处理大写字母（白色）
    	if(c=='Q')white+=9;//白后
    	if(c=='R')white+=5;//白车
    	if(c=='B')white+=3;//白象
    	if(c=='N')white+=3;//白马
    	if(c=='P')white+=1;//白卒
    	//处理小写字母（黑色）
    	if(c=='q')black+=9;//（以此类推）
    	if(c=='r')black+=5;
    	if(c=='b')black+=3;
    	if(c=='n')black+=3;
    	if(c=='p')black+=1;
	}
	if(white==black)cout<<"Draw";//如果分数相同
	if(white<black)cout<<"Black";//如果白优胜
	if(white>black)cout<<"White";//如果黑优胜
}
```

---

## 作者：Andysun06 (赞：2)

# 题解 CF519A
--------------
### 一道水题~~~直接上代码：
    program andyCF519A;//防抄袭
    var a:array[1..10,1..10]of char;
    i,j,x,w:longint;
    begin
    for i:=1 to 8 do
    begin
     for j:=1 to 8 do
     begin
    read(a[i,j]);//输入a[i,j]
    if (a[i,j]='Q') then//如果=Q，w:=w+9;
     w:=w+9;
    if (a[i,j]='R') then//如果=R，w:=w+5;   
     w:=w+5;
    if (a[i,j]='P') then//如果=P，w:=w+1;
     w:=w+1;
    if (a[i,j]='B')or(a[i,j]='N') then//如果=B or N，w:=w+3;
     w:=w+3;
    if (a[i,j]='q') then//如果=q，x:=x+9;
     x:=x+9;
    if (a[i,j]='r') then//如果=r，x:=x+5;
     x:=x+5;
    if (a[i,j]='p') then//如果=p，x:=x+1;
     x:=x+1;
    if (a[i,j]='b')or(a[i,j]='n') then//如果=b or n，x:=x+3;
     x:=x+3;
    end;
    readln;//换行输入
    end;
    if w>x then//如果w>x
     writeln('White');//输出
    if w=x then//如果w=x
     writeln('Draw');//输出
    if w<x then//如果x>w
     writeln('Black');//输出
    end.

---

## 作者：远山淡影 (赞：0)

蒟蒻题解，大佬勿喷
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
int a,b;
int bj(int x,int y)//一个比较函数 
{
	//三种情况 
	if(x>y)
	{
		printf("White\n");
		return 0;
	}
	if(x==y)
	{
		printf("Draw\n");
		return 0;
	}
	if(x<y)
	{
		printf("Black\n");
		return 0;
	}
}
int main()
{
	for(int i=1;i<=8;i++)
	{
		for(int j=1;j<=8;j++)
		{
			char s;
			cin>>s;//输入，用scanf不行 
			if(s=='Q')
			{
				a+=9;
			}
			else if(s=='R')
			{
				a+=5;
			}
			else if(s=='B')
			{
				a+=3;
			}
			else if(s=='N')
			{
				a+=3;
			}
			else if(s=='P')
			{
				a+=1;
			}
			//A的优势值 
			else if(s=='q')
			{
				b+=9;
			}
			else if(s=='r')
			{
				b+=5;
			}
			else if(s=='b')
			{
				b+=3;
			}
			else if(s=='n')
			{
				b+=3;
			}
			else if(s=='p')
			{
				b+=1;
			}
			//B的优势值 
		}
	}
	bj(a,b);//秀一波函数。。。 
	return 0;
}
```

---

