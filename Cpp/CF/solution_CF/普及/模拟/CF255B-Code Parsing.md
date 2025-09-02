# Code Parsing

## 题目描述

Little Vitaly loves different algorithms. Today he has invented a new algorithm just for you. Vitaly's algorithm works with string $ s $ , consisting of characters "x" and "y", and uses two following operations at runtime:

1. Find two consecutive characters in the string, such that the first of them equals "y", and the second one equals "x" and swap them. If there are several suitable pairs of characters, we choose the pair of characters that is located closer to the beginning of the string.
2. Find in the string two consecutive characters, such that the first of them equals "x" and the second one equals "y". Remove these characters from the string. If there are several suitable pairs of characters, we choose the pair of characters that is located closer to the beginning of the string.

The input for the new algorithm is string $ s $ , and the algorithm works as follows:

1. If you can apply at least one of the described operations to the string, go to step 2 of the algorithm. Otherwise, stop executing the algorithm and print the current string.
2. If you can apply operation 1, then apply it. Otherwise, apply operation 2. After you apply the operation, go to step 1 of the algorithm.

Now Vitaly wonders, what is going to be printed as the result of the algorithm's work, if the input receives string $ s $ .

## 说明/提示

In the first test the algorithm will end after the first step of the algorithm, as it is impossible to apply any operation. Thus, the string won't change.

In the second test the transformation will be like this:

1. string "yxyxy" transforms into string "xyyxy";
2. string "xyyxy" transforms into string "xyxyy";
3. string "xyxyy" transforms into string "xxyyy";
4. string "xxyyy" transforms into string "xyy";
5. string "xyy" transforms into string "y".

As a result, we've got string "y".

In the third test case only one transformation will take place: string "xxxxxy" transforms into string "xxxx". Thus, the answer will be string "xxxx".

## 样例 #1

### 输入

```
x
```

### 输出

```
x
```

## 样例 #2

### 输入

```
yxyxy
```

### 输出

```
y
```

## 样例 #3

### 输入

```
xxxxxy
```

### 输出

```
xxxx
```

# 题解

## 作者：liupan2010 (赞：3)

前言：

这可能是题解中代码较短的，速度还算比较快。

[题目传送门](https://www.luogu.com.cn/problem/CF255B)

------------

思路： 
	
```yx``` 会被交换为 ```xy```，```xy``` 会被直接删除。

那么如果 ```x``` 的数量大于 ```y```，那么就只剩下 ```x```，否则只剩下 ```y```。

------------

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string str;
int main()
{
	cin>>str;
	int i,x=count(str.begin(),str.end(),'x'),y=count(str.begin(),str.end(),'y');//count是STL函数，这个函数用于统计某一值在一定范围内出现的次数。 
    for(i=1;i<=abs(x-y);i++)
        printf("%c",(x>y)?'x':'y');//此处的意思为：如果x的数量大于y,就输出x,否则输出y. 
	return 0;
}
```

------------

后记：

发现许多神犇写的都比我简单明了多了，把上面的 **最** 改成了 **较** 。

将 ```count``` 函数的介绍修改。

改了下全半角空格与逗号。

------------

---

## 作者：wangyi_c (赞：3)

[你谷题目传送门](https://www.luogu.com.cn/problem/CF255B)

[CF 题目传送门](https://codeforces.com/problemset/problem/255/B)

建议评 $\text{\color{orange}橙}$。

## 1.题目大意

给出由 ```x``` 和 ```y``` 组成的字符串，出现 ```yx``` 时交换它们，出现 ```xy``` 时删除它们。

## 2.思路讲解

先观察样例，发现答案的字符串都是由清一色的 ```x``` 或 ```y``` 组成，知道这应该是道规律题。再看，当出现 ```xy``` 时，会直接删除；而 ```yx``` 会先换成 ```xy``` 再删除。

我们可以发现规律：

- 当 ```x``` 的数量小于 ```y``` 的数量，那么 ```x``` 将会被删完，剩下 ```y```的数量为 ```y``` 的数量减去 ```x``` 的数量。

-  当 ```y``` 的数量小于 ```x``` 的数量，那么 ```y``` 将会被删完，剩下 ```x``` 的数量为 ```x``` 的数量减去 ```y``` 的数量。

## 3.未 AC，waiting 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define fast ios::sync_with_stdio(0);cin.tie(0);cout.tie(0); 
using namespace std;
int count_x,count_y;
char ch;
signed main(){
    fast
	while(cin>>ch){
		if(ch=='x') count_x++;//累加x
		else count_y++;//累加y
	}
	if(count_x<count_y){
		for(int i=1;i<=count_y-count_x;i++){
			cout<<'y';
		}
	}
	else{
		for(int i=1;i<=count_x-count_y;i++){
			cout<<'x';
		}
	}
    return 0;
}
```
_THE END_

谢谢观看

By wangyi

---

## 作者：Yang_OIer (赞：2)

## 题目大意
给定一个由 $x$ 和 $y$ 组成的字符串，出现 $yx$ 时交换顺序，出现 $xy$ 时删除，结束。
## 解题思路

我们可以统计一下下，统计出 $x$ 和 $y$ 的数量，~~（好像就AK了）~~ 求出两者之间的最大值，大减小，然后输出。

## 代码部分：
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
string s;int x,y,i;
int main(){
	cin>>s;
	for(i=0;s[i]!=0;i++)
		if(s[i]=='x')//统计x的数量 
			x++;
		else //统计y的数量
			y++;
	if(x>y)	
		for(i=0;i<x-y;i++)
			cout<<"x";
	else	
		for(i=0;i<y-x;++i)
			cout<<'y';
	return 0;
}
```


---

## 作者：yzm0325 (赞：0)

好久没用 Python 了，这次就来一发 Python 题解。

## 思路

首先输入不用多讲，$s$ 是只包含 `x` 和 `y` 的字符串，$x$ 和 $y$ 分别是它们的数量。

我们发现题目中会把 `yx` 交换为 `xy`，而 `xy` 又会接着被删除，也就是只要有成对的 `x` 和 `y` 就会删除。所以就简单了，只要统计出 `x` 和 `y` 的数量，然后输出还没抵消掉的就行了（小的会被抵消完）。

输出这一部分首先判断 $x$ 和 $y$ 哪个大，若 $x$ 大输出 $x-y$ 个 `x`（即那些还没抵消的），反之亦然。这里运用了三元操作符。

## code

```python
s = input()
x = 0
y = 0
for i in s:
    if i == 'x': x += 1
    else: y += 1
print('x' * (x - y) if x > y else 'y' * (y - x)) # 三元操作符
```

一共七行，Python 果然简便啊……

接下来讲讲 Python 的三元操作符，其实和 C++ 的三目运算符差不多，它的格式是这样的：

```python
条件成立时的值 if 条件 else 条件不成立时的值
```

如，程序中的 `print('x' * (x - y) if x > y else 'y' * (y - x))`，它就相当于：

```python
if x > y:
	print('x' * (x - y))
else:
	print('y' * (y - x))
```

适当的使用它会简化代码，但使用不当反而会让代码失去可读性，比如在分类讨论，多个 `if` 语句连写的时候。

完结撒花！谢谢观看！

---

## 作者：WA_sir (赞：0)

## [题目](https://codeforces.com/problemset/problem/255/B)|[链接](https://www.luogu.com.cn/problem/CF255B)

题中的操作，无非就是将所有能配对的 "x" 和 "y" 消除后求剩下的。这里不多说了。

提供短小的代码。
## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char z;int x,y;
int main(){
	while(cin>>z)z-'y'?x++:y++;
	z=x>y?'x':'y';
	x=abs(x-y);
	while(x--)cout<<z;
	return 0;
}
```
感谢阅读！

---

## 作者：L_zaa_L (赞：0)

## 分析
那么我们知道，出现第一种情况时，他就会一直执行操作一，就会把所有的```x```移动到前面，从```x```到```y```的连接处，就会执行操作二，那么最后的结果肯定只剩下一个字母（要么一个不剩），既然一个```x```可以换一个```y```，那么，$\left|Num_X+Num_Y\right|$（$Num_X$ 指```x```的数量，$Num_Y$ 指```y```的数量），字符串就是由最多的哪一个组成的。

## Code
```
#include<bits/stdc++.h>
using namespace std;
int n,s1,s2;
string a;
int main(){
	cin>>a;
	for(int i=0;i<a.size();i++){
		if(a[i]=='x') s1++;
		else s2++;
		//记录两个字符出现的次数
	}
	if(s1>s2){
		s1-=s2;
		for(int i=1;i<=s1;i++) cout<<"x";
	}
	else{
		s2-=s1;
		for(int i=1;i<=s2;i++) cout<<"y";
	}
	return 0;
}
```

---

## 作者：DioxygenDifluoride (赞：0)

### 题目大意
给定一个由 $\texttt{x}$ 和 $\texttt{y}$ 组成的字符串，出现 $\texttt{yx}$ 时交换顺序，出现 $\texttt{xy}$ 时删除，直到你不能操作时输出这个字符串。
### 解题思路
我们可以用一个统计的方法，统计出 $\texttt{x}$ 和 $\texttt{y}$ 的数量，求出两者之间的最大值，然后输出。
### 代码实现
```cpp
#include<stdio.h>
char s[1000001];
int x,y;
main(){
	scanf("%s",s);
	for(int i=0;s[i];++i)
		if(s[i]=='x')++x;
		else ++y;
	if(x>y)	for(int i=0;i<x-y;++i)putchar('x');
	else	for(int i=0;i<y-x;++i)putchar('y');
}
```

---

## 作者：wangkangyou (赞：0)

我们分析一下题目给的两个操作：

1. 把 `yx` 变成 `xy`；
2. 删除 `xy`；

我们可以从这两个操作中发现，无论是 `xy` 还是 `yx` ，只要是 `x` 和 `y` 相邻的，都可以被删除。

举个栗子：

若有一个 `xy` 字符串，我们可以直接删除；
若有一个 `yx` 字符串，我们可以先动用操作 1，使它变成 `xy` 字符串，然后用操作 2 删除。

然后我们看样例，输出的总是清一色的 `x` 或 `y` 。(不信的朋友们可以自己手玩几个样例试试)因为每次删除都要消耗一组 `x` 和 `y`，于是输出的个数就是 `x` 和 `y` 之间个数的差。

上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read (){
	int sum = 0, f = 1;
	char ch = getchar ();
	for(;!isdigit (ch); ch = getchar ()) if (ch == '-') f = -1;
	for(;isdigit (ch); ch = getchar ()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * f;
}
void write (int x){
	if (x < 0) putchar ('-'), x = -x;
	if (x > 9) write (x / 10);
	putchar ('0' + x % 10);
	return;
}
signed main(){
	string str;
	cin >> str;
	int a = 0, b = 0;
	for (int i = 0; i < str.size(); ++ i){
		if (str[i] == 'x') 		a ++;
		else if (str[i] == 'y') b ++;
	}
	if (a > b){
		for (int i = 1; i <= a - b; ++ i) putchar ('x'); 
	}else if (a < b){
		for (int i = 1; i <= b - a; ++ i) putchar ('y');
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 原题：[CF255B Code Parsing](https://www.luogu.com.cn/problem/CF255B)

## 一、题目大意

给出由 ```x``` 和 ```y``` 组成的字符串，出现 ```yx``` 时交换它们，出现 ```xy``` 时删除它们，直到你不能操作时输出这个字符串。

## 二、分析

对于任意两个相邻的字母，有四种情况

1. 为 ```xy``` 直接删除；
2. 为 ```yx``` 先交换为 ```xy``` 再删除；
3. 为 ```xx``` 时不用管它；
4. 为 ```yy``` 时也不用管它。

所以对于任意两个相邻且不同的字母，在两步之内肯定会被消掉。

所以可以统计 ```x``` 和 ```y``` 的数量，然后判断那种多，然后输出答案即可。

## 三、code

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,len;
string s;
int main(){
	cin>>s;
	len=s.size();
	for(int i=0;i<len;i++)
		if(s[i]=='x')x++;
		else y++;
	if(x>y)
		while((x--)-y)
			putchar('x');
	else
		while((y--)-x)
			putchar('y');
	return 0;
}
```

---

## 作者：_easy_ (赞：0)

# 思路
思维题。

简单思考后可以发现：最后输出的字符串只能是全 $\texttt{x}$ 或全 $\texttt{y}$，否则就可以执行操作。但是模拟是肯定行不通的，于是我们简单观察一下样例就可以发现：输出的个数恰好是 $\texttt{x}$ 与 $\texttt{y}$ 的差值，而字母也恰好是多的那个。

**证明**：现在假设有 $a$ 个 $\texttt{x}$ 和 $b$ 个 $\texttt{y}$。每一个 $\texttt{x}$ 与 $\texttt{y}$ 相邻就会在两步之内被消除，以此类推，可以得出最后输出的肯定是多的那个（因为少的那个全部都被消除了），而个数恰好是多的减去少的。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
string c;
int a,b;
int main(){
	cin>>c;
	for(int i=0;i<c.size();i++){
		if(c[i]=='x'){
			a++;
		}else{
			b++;
		}
	}
	if(a>b){
		a-=b;
		while(a--){
			cout<<"x";
		}
	}else{
		b-=a;
		while(b--){
			cout<<"y";
		}
	}
	return 0;
}
```

---

## 作者：ylinxin2010 (赞：0)

## CF255B题解

**题目翻译：**

出现``yx``时交换顺序，出现``xy``时删除，长度小于等于 $10^6$ 目标为求出最后的字符串。

------------

首先我们可以肯定暴力枚举是不可行的。

我么可以分析出最后只能包含``x``或``y``。

既然如此，我们可以分别统计``x``与``y``的个数，并求出哪个大一些，输出大一些的那个即可。

接下来——上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	int x=0, y=0;
	cin>>s;
	for(int i=0;i<s.size();i++)
		if(s[i]=='x')
			x++;
		else
			y++;
	if(x>y)
		for(int i=1;i<=x-y;i++)
			cout<<'x';
	else
		for(int i=1;i<=y-x;i++)
			cout<<'y';
	return 0;
}
```

---

## 作者：Yhlo_Yzj (赞：0)

## CF255B 题解
**本题题意**：钦定一个由 $x$ 和 $y$ 组成的字符串。
1. 出现 $xy$ 时交换他们

1. 出现 $xy$ 时删除他们

**注**：当你不能操作时，输出字符串

**本题思路————统计**

1. 统计 $x$ 和 $y$ 的数量

1. 判断是 $x$ 多还是 $y$ 多

1. 输出即可

接下来————上代码

### $code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string str;
	cin>>str;
	if(str.size()==1){
		cout<<str;
		return 0;
	}	
	int y=0,x=0; 
	for(int i=0;i<str.size();i++){
		if(str[i]=='x'){//统计数量
			x++;
		}else
		{
			y++;
		}
	}
	if(x>y){
		for(int i=1;i<=x-y;i++){//判断是x多还是y多
			cout<<'x';
		}
	}else{
		for(int i=1;i<=y-x;i++){
			cout<<'y';
		}
	}
}
```


---

