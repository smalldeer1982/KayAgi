# Rock-paper-scissors

## 题目描述

### 题面描述

三个人玩石头剪刀布，问谁赢了。

## 样例 #1

### 输入

```
rock
rock
rock
```

### 输出

```
?
```

## 样例 #2

### 输入

```
paper
rock
rock
```

### 输出

```
F
```

## 样例 #3

### 输入

```
scissors
rock
rock
```

### 输出

```
?
```

## 样例 #4

### 输入

```
scissors
paper
rock
```

### 输出

```
?
```

# 题解

## 作者：Liveddd (赞：8)

看到没人跟我做的一样，赶紧来水一发题解~~（一想到前几篇题解都没有通过就十分悲伤QAQ）

看到这几个单词（就是石头剪刀布啦~~），每个首字母都不一样，so，我们只需要判断首字母是那种状态了

废话少说，上代码！！！（个人觉得还是比较简洁的~~）

```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2,s3;
int main()
{
	cin>>s1>>s2>>s3;
	if((s1[0]=='r'&&s2[0]=='s'&&s3[0]=='s')||(s1[0]=='s'&&s2[0]=='p'&&s3[0]=='p')||(s1[0]=='p'&&s2[0]=='r'&&s3[0]=='r'))//判断第一个人赢的情况
		cout<<"F\n";
	else if((s2[0]=='r'&&s1[0]=='s'&&s3[0]=='s')||(s2[0]=='s'&&s1[0]=='p'&&s3[0]=='p')||(s2[0]=='p'&&s1[0]=='r'&&s3[0]=='r'))//判断第二个人赢的情况
		cout<<"M\n";
	else if((s3[0]=='r'&&s1[0]=='s'&&s2[0]=='s')||(s3[0]=='s'&&s1[0]=='p'&&s2[0]=='p')||(s3[0]=='p'&&s1[0]=='r'&&s2[0]=='r'))//判断第三个人赢的情况
		cout<<"S\n";
	else //若都不满足以上条件就是不确定
		cout<<"?\n";
    return 0;//华丽结束~~
}
```

88，我们下次债见~~

---

## 作者：张文奕 (赞：7)

这题直接根据题意暴力模拟就可以了。
话不多说，直接上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string a,b,c;
    cin>>a>>b>>c;
    int x,y,z;
    if (a=="rock") x=1;
    if (a=="scissors") x=2;
    if (a=="paper") x=3;
    if (b=="rock") y=1;
    if (b=="scissors") y=2;
    if (b=="paper") y=3;
    if (c=="rock") z=1;
    if (c=="scissors") z=2;
    if (c=="paper") z=3;
    //以上这一段均为预处理，下面判断更方便
    if (x==1&&y==2&&z==2){
        printf ("F");
        return 0;
    }
    if (x==2&&y==3&&z==3){
        printf ("F");
        return 0;
    }
    if (x==3&&y==1&&z==1){
        printf ("F");
        return 0;
    }
    //F胜的3种情况
    if (y==1&&x==2&&z==2){
        printf ("M");
        return 0;
    }
    if (y==2&&x==3&&z==3){
        printf ("M");
        return 0;
    }
    if (y==3&&x==1&&z==1){
        printf ("M");
        return 0;
    }
    //M胜的3种情况
    if (z==1&&x==2&&y==2){
        printf ("S");
        return 0;
    }
    if (z==2&&x==3&&y==3){
        printf ("S");
        return 0;
    }
    if (z==3&&x==1&&y==1){
        printf ("S");
        return 0;
    }
    //S胜的3种情况
    printf ("?");
    //否则胜负不明
    return 0;
}
```

---

## 作者：lzy755277 (赞：2)

分析：

1.函数：判断两个人之间的胜负情况；

2.主程序：调用函数，判断是谁赢，输出“F”，“M”或“S”。如果无，输出“？”；

上代码：
```cpp
#include<iostream>
#include<string>
using namespace std;
int win(string a,string b)
{
	if(a=="rock"&&b=="scissors"||a=="scissors"&&b=="paper"||a=="paper"&&b=="rock")return 1;//如果赢了返回1；
	else return -1;//如果输了返回-1；
}
int main()
{
	string a,b,c;
	cin>>a>>b>>c;//输入出的手势；
	if(win(a,b)==1/*如果第一个人赢第二个人*/&&win(a,c)==1/*且第一个人赢第三个人*/)cout<<"F";//输出“F”，下同；
	else if(win(b,a)==1&&win(b,c)==1)cout<<"M";
	else if(win(c,a)==1&&win(c,b)==1)cout<<"S";
	else cout<<"?";//否则输出“？”；
    return 0;//完美结束；
}
```

---

## 作者：TCZN (赞：1)

~~蒟蒻又来发题解啦~~

蒟蒻看见题目标签中有枚举、暴力

所以就用暴力枚举的方法做啦

咳咳（言归正传）

实际上此题还是挺~~水~~有难度的

思路为：暴力枚举

直接枚举9种赢的情况就行，可以9个if判断，也可以像我这样直接一个lf，后面else if嵌套

```pascal
var
  a,b,c:string;
begin
 readln(a);//一定要分别读入，而且要用readln，蒟蒻在这个地方被卡了好长时间，还有read读入会读入空格，所以要用readln，他会把空格吃掉
 readln(b);
 readln(c);
  if (a='rock') and (b='scissors') and (c='scissors') then writeln('F') //暴力枚举9种赢的情况，每个人赢的情况有3种，一个if直接过
   else if (a='scissors') and (b='paper') and (c='paper') then writeln('F')
    else if (a='paper') and (b='rock') and (c='rock') then writeln('F')
     else if (b='rock') and (a='scissors') and (c='scissors') then writeln('M')
      else if (b='scissors') and (a='paper') and (c='paper') then writeln('M')
       else if (b='paper') and (a='rock') and (c='rock') then writeln('M')
        else if (c='rock') and (a='scissors') and (b='scissors') then writeln('S')
         else if (c='paper') and (b='rock') and (a='rock') then writeln('S')
          else if (c='scissors') and (b='paper') and (a='paper') then writeln('S')
           else writeln('?'); //最后记得加上胜负不分的情况
end.
```
够暴力吧，直接枚举9种情况（蒟蒻打了好长时间的，望通过）

---

## 作者：longyuxuan (赞：1)

这题思路只有一个，就是暴力。
题目讲了，只有当一个人赢两个人才算获胜，否则就是不分胜负，我们可以就这可情况进行枚举，而且这样枚举可以降低错误率，~~你把所有情况枚举出来也行，只不过打代码很麻烦~~
程序如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4];//a数组用来记录石头，剪刀和布的出现次数
string s[4];
int main()
{
	for(int i=1;i<=3;i++)
	{
		cin>>s[i];
        //记录石头，剪刀和布的出现次数
		if(s[i][0]=='r')  a[1]++;
		else if(s[i][0]=='s')  a[2]++;
		else a[3]++;
        //由于石头，剪刀和布英文首字母不一样，我们只需挑第一个字母来记录就可以了，代码比较好打
	}
	if((a[1]==1&&a[2]==2)||(a[2]==1&&a[3]==2)||(a[3]==1&&a[1]==2))//如果有一个人赢了其他两个人的时候
	{
		if(s[1]==s[2])  cout<<'S';//当两个人相同时，另一个不同的则是赢家
		else if(s[2]==s[3])  cout<<'F';
		else cout<<'M';
	}
	else  cout<<'?';//胜负未分
	return 0;
} 
```
总的来说，我这份代码比较简洁，比较好打，而且比较好纠错。
~~我想看看会不会有题解发个特别长的纯暴力~~

~~我的代码做了错误化处理，不能复制，但不影响理解~~

---

## 作者：judgejudge (赞：0)

# 本题解比较通俗易懂
首先我们看这道题，想要输出F,M,S，就必须满足有**两个字符串是相等的**。然而我们怎么判断是否相等，大部分人都选择一个个比较，而我就用了一种方法：

```cpp
cin>>st[0]>>st[1]>>st[2];
	st[3]=st[0];//这样我们就可以比较第一个字符串和第三个字符串
	for(i=0;i<3;i++)//然后进入for循环比较
```
这样就可以用for循环来进行比较啦。

之后就是比较常规的操作。

奉上AC代码：
```cpp
#include <iostream>
#include <string>
using namespace std;
int f(string sa,string sb){//return 1表示sa赢，2表示sb赢
	if(sa[0]=='s'&&sb[0]=='r')return 2;
	if(sa[0]=='r'&&sb[0]=='s')return 1;
	if(sa[0]=='s'&&sb[0]=='p')return 1;
	if(sa[0]=='p'&&sb[0]=='s')return 2;
	if(sa[0]=='r'&&sb[0]=='p')return 2;
	if(sa[0]=='p'&&sb[0]=='r')return 1;
	if(sa[0]==sb[0])return 3;
}
int main(){
	int i,j,k,n;
	string st[4];
	cin>>st[0]>>st[1]>>st[2];
	st[3]=st[0];
	for(i=0;i<3;i++)
	if(st[i]==st[i+1]){
		if(i==0)k=2;
		if(i==1)k=0;
		if(i==2)k=1;
		j=f(st[i],st[k]);
		if(j==2){//因为f函数中sb不是与另外两个相等（如果相等return 3），这样如果sb赢就满足条件
			if(k==0)cout<<"F";
			if(k==1)cout<<"M";
			if(k==2)cout<<"S";
			return 0;//省时间，直接结束程序
		}
	}
	cout<<"?"<<endl;//如果没有必定输出？
	return 0;
}
```





---

## 作者：魁父 (赞：0)

### 果然，CF的题都是水题，这题是非常简单的


----------------------------------------华丽的分割线--------------------------------------------
```pascal
var
 st1,st2,st3:string;
function sta(a,b,c:string):boolean;
begin
  if (a='rock')and(b='scissors')and(c='scissors') then exit(true);
  if (a='scissors')and(b='paper')and(c='paper') then exit(true);
  if (a='paper')and(b='rock')and(c='rock') then exit(true);
  exit(false);
end;//判断
begin
  readln(st1);readln(st2);readln(st3);
  if sta(st1,st2,st3) then begin writeln('F');exit;end;
  if sta(st2,st1,st3) then begin writeln('M');exit;end;//注意，这里和上面不同
  if sta(st3,st2,st1) then begin writeln('S');exit;end;//注意，这里和上面不同
  writeln('?');
end.
```
这就搞定啦

---

## 作者：Messi李 (赞：0)

咳咳 听说~~有人想看看纯暴力~~

但是我就是来了个超长判断

无脑代码上

```
#include<bits/stdc++.h>
using namespace std;
string s1,s2,s3;
int main()
{
    cin>>s1>>s2>>s3;//输入
    //判断多种情况
    if(s2 == "rock" && s1 == "scissors" && s1 == s3) cout<<"M"<<endl;
    else if(s1 == "rock" && s2 == "scissors" && s2 == s3) cout<<"F"<<endl;
    else if(s3 == "rock" && s1 == "scissors" && s2 == s1) cout<<"S"<<endl;
    //石头获胜情况
    else if(s1 == "scissors" && s2 == "paper" && s2 == s3) cout<<"F"<<endl;
    else if(s2 == "scissors" && s1 == "paper" && s1 == s3) cout<<"M"<<endl;
    else if(s3 == "scissors" && s2 == "paper" && s2 == s1) cout<<"S"<<endl;
    //剪刀获胜情况
    else if(s1 == "paper" && s2 == "rock" && s2 == s3) cout<<"F"<<endl;
    else if(s2 == "paper" && s1 == "rock" && s1 == s3) cout<<"M"<<endl;
    else if(s3 == "paper" && s2 == "rock" && s2 == s1) cout<<"S"<<endl;
    //布获胜情况
    else cout<<"?"<<endl;//没有获胜者情况
}
```

想我这样就是打的麻烦一点，没那么简洁

---

## 作者：陈灏 (赞：0)

# 这一道题，其实直接用判断就行了！
-------------------------------------------------------------


第一个人是**a**

第二个人是**b**

第三个人是**c**

## 各类判断
```cpp
	if(b=="rock"&&a=="scissors"&&a==c)
	{
		cout<<"M"<<endl;	//如果第二个人赢了输出"M"
	}
    	else if(a=="rock"&&b=="scissors"&&b==c)
	{
		cout<<"F"<<endl;	//如果第一个人赢了输出"F"
	}
    	else if(c=="rock"&&a=="scissors"&&b==a)
	{
		cout<<"S"<<endl;	//如果第三个人赢了输出"S"
	}
    	else if(a=="scissors"&&b=="paper"&&b==c)
	{
		cout<<"F"<<endl;	//如果第一个人赢了输出"F"
	}
    	else if(b=="scissors"&&a=="paper"&&a==c)
	{
		cout<<"M"<<endl;	//如果第二个人赢了输出"M"
	}
    	else if(c=="scissors"&&b=="paper"&&b==a)
	{
		cout<<"S"<<endl;	//如果第三个人赢了输出"S"
	}
    	else if(a=="paper"&&b=="rock"&&b==c)
	{
		cout<<"F"<<endl;	//如果第一个人赢了输出"F"
	}
    	else if(b=="paper"&&a=="rock"&&a==c)
	{
		cout<<"M"<<endl;	//如果第二个人赢了输出"M"
	}
    	else if(c=="paper"&&b=="rock"&&b==a)
	{
		cout<<"S"<<endl;	//如果第三个人赢了输出"S"
	}
    	else
	{
		cout<<"?"<<endl;	//如果胜负不分输出"?"
	}
    	return 0;
```
---
## 注意
## 一切判断语句都要考虑周到
## 缺一不可！
## 完整代码
-----------------------------------------------------------------

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,c;
int main()
{
    cin>>a>>b>>c;
    	if(b=="rock"&&a=="scissors"&&a==c)
	{
		cout<<"M"<<endl;	//如果第二个人赢了输出"M"
	}
    	else if(a=="rock"&&b=="scissors"&&b==c)
	{
		cout<<"F"<<endl;	//如果第一个人赢了输出"F"
	}
    	else if(c=="rock"&&a=="scissors"&&b==a)
	{
		cout<<"S"<<endl;	//如果第三个人赢了输出"S"
	}
    	else if(a=="scissors"&&b=="paper"&&b==c)
	{
		cout<<"F"<<endl;	//如果第一个人赢了输出"F"
	}
    	else if(b=="scissors"&&a=="paper"&&a==c)
	{
		cout<<"M"<<endl;	//如果第二个人赢了输出"M"
	}
    	else if(c=="scissors"&&b=="paper"&&b==a)
	{
		cout<<"S"<<endl;	//如果第三个人赢了输出"S"
	}
    	else if(a=="paper"&&b=="rock"&&b==c)
	{
		cout<<"F"<<endl;	//如果第一个人赢了输出"F"
	}
    	else if(b=="paper"&&a=="rock"&&a==c)
	{
		cout<<"M"<<endl;	//如果第二个人赢了输出"M"
	}
    	else if(c=="paper"&&b=="rock"&&b==a)
	{
		cout<<"S"<<endl;	//如果第三个人赢了输出"S"
	}
    	else
	{
		cout<<"?"<<endl;	//如果胜负不分输出"?"
	}
    	return 0;
}
```






---

