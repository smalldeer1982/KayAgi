# Bit++

## 题目描述

The classic programming language of Bitland is Bit++. This language is so peculiar and complicated.

The language is that peculiar as it has exactly one variable, called $ x $ . Also, there are two operations:

- Operation ++ increases the value of variable $ x $ by 1.
- Operation -- decreases the value of variable $ x $ by 1.

A statement in language Bit++ is a sequence, consisting of exactly one operation and one variable $ x $ . The statement is written without spaces, that is, it can only contain characters "+", "-", "X". Executing a statement means applying the operation it contains.

A programme in Bit++ is a sequence of statements, each of them needs to be executed. Executing a programme means executing all the statements it contains.

You're given a programme in language Bit++. The initial value of $ x $ is $ 0 $ . Execute the programme and find its final value (the value of the variable when this programme is executed).

## 样例 #1

### 输入

```
1
++X
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
X++
--X
```

### 输出

```
0
```

# 题解

## 作者：Bronya18C (赞：7)

## 题意描述

- 有一种语言叫Bit++语言，只有一个变量 X ，初始为 00 。

- 有一个 nn 行的Bit++语言的程序，每行只有一条语句，为X++,++X,X--,--X中的一种。其中X++,++X表示把 X加 11 ，X--,--X表示把 X 减 11 。

- 输出最终 X 的值。

---
## 做法
- 首先，我们仔细观察题目，本蒟蒻** 发现++X和X++中间的“+”是相同的。同理，X--和--X也是一样的。**

- 然后，我们根据找到的规律去做，判断中间是‘+’还是‘-’去++，或--。记得，从零开始，所以是**S[1]**。

- 记得回车（~~手动滑稽~~）

---
## 附上本蒟蒻的代码

```
#include<bits/stdc++.h>

using namespace std;
long long a,ans;
string S;
int main()
{
 cin>>a;
 for(int i=0;i<a;i++)
 {
  cin>>S;
  if(S[1]=='+')ans++;
  else ans--; 
 }
 cout<<ans<<endl;
 return 0;
}
```

---

## 作者：Jinyeke (赞：5)

### 题目：有一种语言叫Bit++语言，只有一个变量 X ，初始为 0 。有一个 nn 行的Bit++语言的程序，每行只有一条语句，为X++,++X,X--,--X中的一种。其中X++,++X表示把 X 加 11 ，X--,--X表示把 X 减 1 。输出最终 XX的值。
#### 这题竟然没有p党发题解，本小蒟蒻忍不住，其实这题最主要地就是一个判断，下面是代码（pascal）
```pascal
var
 i,n,x:longint;
 s:string;//最好定义一个字符串，不定义的话就得定3个字符
begin
 readln(n);
 x:=0;//清零是种好习惯
 for i:=1 to n do
  begin
   readln(s);//输入s串
   if (s='++X') or (s='X++') then inc(x)//如果是'++X' 或'X++‘x的值就+1，不然就-1（因为只有两种可能，一种是+1，一种是-1）
   else x:=x-1;//不符合加的条件就-1
  end;
 write(x);//输出n轮后x的值
end.

```
## 共建文明洛谷，请勿Ctrl+C！


---

## 作者：_短笛无腔_ (赞：2)

No.1：不需要考虑++或--的位置！

不论++或--在前在后，后面总是要返回的！

No.2：有种情况是这样的

2
    
X++
    
--X

这种加减位置不同的也不需要过多判断，总是要返回的，一个判断带过。

最后：

$AC$ $CODE$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int main(){
    int x=0,n;
    string m[205];
    scanf("%d",&n);
    for(int a=0;a<n;a++)cin>>m[a];
    for(int b=0;b<n;b++){
        if(m[b]=="X++"||m[b]=="++X")x++;//如果要增加就++
        else if(m[b]=="X--"||m[b]=="--X")x--;//是减少就--
    }
    printf("%d",x);
    return 0;
}
```


---

## 作者：AutumnKite (赞：1)

按题意模拟即可。

蒟蒻丑陋的代码：

```cpp
#include <cstdio>
#include <string>
#include <cstring>
char s[5];
int n,x;
int main(){
    scanf("%d",&n),x=0;
    while(n--){
        scanf("%s",s);
        if(std::string(s)=="X++"||std::string(s)=="++X") x++;else x--;
    }
    return printf("%d",x),0;
}
```

---

## 作者：人间凡人 (赞：1)

这是一道字符串模拟典型例题。

思路：假设最终答案为$ans$,如果输入的为$++X$或$X++$ 就将$ans+1$ 否则就将$ans-1$,最终输出$ans$即可。

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int n,x;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s=="++X"||s=="X++")x++;
		else x--;
	}
	printf("%d\n",x);
	return 0;
}

```


---

## 作者：KazamiHina (赞：0)

~~众所周知，这是一道 **H2O** 题目~~

### 直接上代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int Q,x;
string f;//f表示输入的字符串

int main()
{
	cin>>Q;//输入行数
	for(int i=1;i<=Q;i++)
	{
		cin>>f;//输入每行的语句
		if(f=="X++" || f=="++X")x++;//如果是 X++ 或 ++X 则 x++
		if(f=="X--" || f=="--X")x--;//如果是 X-- 或 --X 则 x--
	}
	cout<<x;//开心的输出
	return 0;//写return是个好习惯
}
```

### 祝AC

---

## 作者：hzy2023_ (赞：0)

### 可能与楼上楼下有些相似，但是我用的是字符串
思路相似，直接上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
string s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s[1]=='+') ans++;
		else ans--;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：丁丁の丁丁 (赞：0)

字符串典型例题
（char和string都可以）
~~~~
#include<bits/stdc++.h>//万能头文件不解释
using namespace std;
int main()
{
	long long n,i,s=0;//因为（X）他的初始值为0；
	string o;
	cin>>n;
	for(i=1;i<=n;i++)//简介明了的for循环
	{
		cin>>o;//循环内输入字符串
		if(o=="++X"||o=="X++") s++;//判断他是不是++X||X++，是的话+1；
		else s--;//否则-1；
	}
	cout<<s;
	return 0;
}

---

## 作者：我是一个蒟蒻 (赞：0)

## 这题考的是判断，可以用char，也可以用string。
# 上代码：
## 单个字符：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    scanf("%d\n",&n);
    long long x=0;
    char a,b,c;
    for(int i=0;i<n;i++)
    {
        scanf("%c%c%c\n",&a,&b,&c);
        if((a=='X' && b=='+' && c=='+') || (a=='+' && b=='+' && c=='X'))
        {
            x++;
        }
        if((a=='X' && b=='-' && c=='-') || (a=='-' && b=='-' && c=='X'))
        {
            x--;
        }
    }
    printf("%lld\n",x);
    return 0;
}
```

## string:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    scanf("%d\n",&n);
    long long x=0;
    string s;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        if(s[1)=='+';
        {
            x++;
        }
        if(s[1]=='-')
        {
            x--;
        }
    }
    printf("%lld\n",x);
    return 0;
}
```

---

## 作者：绝尘影_Sheldow (赞：0)

# CF282A 【Bit++】

怎么说呢……这的确是一道大 $H_2O$ 题。

然并卵！我们仍旧要用珂（~~科~~）学的眼光看待每一道题。

首先，这是一道字符串题。（~~废话~~）

输入的字符串只有以下4种：

$X++$、$++X$、$X--$、$--X$。

我们通过观察发现：

每个字符串的第二个字符，恰好就代表了这个字符串要求的运算！

所以我们只需根据每个字符串的第二个字符对$X$进行加减就好了。

注意： **string** 类型的下标是从 $0$ 开始的，所以我们要判断的字符的下标是 $1$。

代码如下：

```
//为了防抄袭，我在程序中留了一处错误
#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int main()                     //万年开头
{
	int n,x=0;
	cin>>n;                //字符串个数
	for(int i=1;i<=n;i++)
	{
	    string s;
	    cin>>s;
	    if(s[1]==‘+’)      //判断第二个字符
	    {
	        x++;	       //模拟运算
	    }
	    else
	    {
	        x--;
	    }
	}
	cout<<x;	       //输出结果
	return 0;	       //程序拜拜
}
```


---

## 作者：紫金依旧 (赞：0)

# 大致思路:

1. 这里的x为最后的值,再加上数据并不非常毒瘤,所以就是一道非常简单的模拟题.

2. 通过读题可以得知,总共只有四种语句,而其中只要含有‘+’字符的即为将x加一,否则就减一.

3. 如何最简单的判断是加是减呢?其实通过观察可以得知,是加是减是体现在第二个字符上的.

4. 当你明白了这些,且这道题岂不是轻轻松松?

上代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s;//s为累加
string a;//用于输入字符
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;//输入
		if(a[1]=='+')//如果第二个字符为加
			s++;//累加
		else//否则
			s--;//减一
	}
	cout<<s;
	return 0;
}
```

# 最后的最后——管理求过啊


---

