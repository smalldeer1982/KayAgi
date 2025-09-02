# Little Pony and Crystal Mine

## 题目描述

Twilight Sparkle once got a crystal from the Crystal Mine. A crystal of size $ n $ ( $ n $ is odd; $ n>1 $ ) is an $ n×n $ matrix with a diamond inscribed into it.

You are given an odd integer $ n $ . You need to draw a crystal of size $ n $ . The diamond cells of the matrix should be represented by character "D". All other cells of the matrix should be represented by character "\*". Look at the examples to understand what you need to draw.

## 样例 #1

### 输入

```
3
```

### 输出

```
*D*
DDD
*D*
```

## 样例 #2

### 输入

```
5
```

### 输出

```
**D**
*DDD*
DDDDD
*DDD*
**D**
```

## 样例 #3

### 输入

```
7
```

### 输出

```
***D***
**DDD**
*DDDDD*
DDDDDDD
*DDDDD*
**DDD**
***D***
```

# 题解

## 作者：Pkixzx (赞：7)

$$\Huge\text{模拟}$$
这就是一道模拟的~~大水~~题。

建立一个n*n的矩阵，按照题目给的样例一步一步地模拟就可以啦！

如：
输入
3

输出：

*D *

DDD

*D *

蒟蒻将前两行分为一部分，将最后一行分成一部分，然后输出。
前一部分为：
```
for(i=1;i<=n/2+1;i++)
{
    for(j=1;j<=(n-t)/2;j++)
    cout<<"*";
    for(j=1;j<=t;j++)
    cout<<"D";
    for(j=1;j<=(n-t)/2;j++)
    cout<<"*";
    cout<<endl;
    t+=2;
}
t-=4;
```
这一部分输出的是：

*D *

DDD



------------
第二部分为：
```
for(i=1;i<=n/2;i++)
{
    for(j=1;j<=(n-t)/2;j++)
    cout<<"*";
    for(j=1;j<=t;j++)
    cout<<"D";
    for(j=1;j<=(n-t)/2;j++)
    cout<<"*";
    cout<<endl;
    t-=2;
}
```


------------
那么完整的代码为：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long i,j,k,n,m,t=1,l,r,t1=0,x,y;
    cin>>n;
    for(i=1;i<=n/2+1;i++)
    {
    	for(j=1;j<=(n-t)/2;j++)
    	cout<<"*";
    	for(j=1;j<=t;j++)
    	cout<<"D";
    	for(j=1;j<=(n-t)/2;j++)
    	cout<<"*";
    	cout<<endl;
    	t+=2;
	}	
	for(i=1;i<=n/2;i++)
    {
    	for(j=1;j<=(n-t)/2;j++)
    	cout<<"*";
    	for(j=1;j<=t;j++)
    	cout<<"D";
    	for(j=1;j<=(n-t)/2;j++)
    	cout<<"*";
    	cout<<endl;
    	t-=2;
	}
    return 0;
}
```
注：直接提交最后面的代码有惊喜哦！

---

## 作者：zhangjiacheng (赞：3)

Pascal题解！P党福利啦！

模拟大法好。。。

代码如下：
```pascal
var n,i,j:longint;a:array[0..101,0..101]of char;
begin
  readln(n);
  for i:=1 to n div 2 do
    for j:=n div 2+1+1-i to n div 2+1-1+i do
    a[i,j]:='D';//本段存储上半部分的“D”
  for i:=1 to n do a[n div 2+1,i]:='D';//中间那一段全是“D”
  for i:=n downto n div 2+2 do
    for j:=1 to n do
    a[i,j]:=a[n-i+1,j];//下半部分从上面翻下来
  for i:=1 to n do
    for j:=1 to n do
    if a[i,j]<>'D'then a[i,j]:='*';//如果不是“D”就是“*”
  for i:=1 to n do
  begin
    for j:=1 to n do
    write(a[i,j]);//全部输出
    writeln;
  end;
end.
```


---

## 作者：purple7 (赞：1)

本人的此题的思路与他人不太一样，为染色，使用两个表示列的指针 $l$ 和 $r$，以及一个表示行的 $top$ 指针。  
一开始 $l$ 和 $r$ 在中间位置即 $n/2+1$，$top$ 则在1的位置。  
当 $top$ 还没到行的一半时，$l$ 和 $r$ 是向外拓展的，而到了行的一半之后，$l$ 和 $r$ 就要向内收缩。  
每次将 $l$ 和 $r$ 之间的数组即 $a(top,i) (l \leq        i \leq r)$ 染色成D。  
最后将整个二维数组输出，被染色的部分输出D，否则就输出*。  
下面附上代码       

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int l,r;//l和r分别是两个指针，其作用上文已经讲过。
char a[1000][1000];//这个是二维数组。
int main()
{
	cin>>n;
	int top=0;
	l=r=n/2+1;//初始化定义，l和r在中间，而因为是++top，所以top初始化为0。
	while(top<n/2+1)
	{
		++top;//行加一
		for(int i=l;i<=r;i++)
		a[top][i]='D';//将l和r中间的部分进行染色。
		l--;r++;//l和r向外拓展。
	}//进行前半部分的染色。
	l=2,r=n-1,top=n/2+1;//中间部分初始化时将 l 定为2， r 定为n-1，是因为直接从中间后的下一行开始了。
	while(top<=n)
	{
		++top;
		for(int i=l;i<=r;i++)
		a[top][i]='D';
		l++;
		r--;
	}//进行后半部分的染色，过程同上，只是 l 和 r 向内收缩
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		if(a[i][j]=='D')
		cout<<"D";
		else
		cout<<"*";
		cout<<endl;
	}//输出整个二维数组，如果被染色就输出 D ，未被染色就输出 * 。
	return 0;
}

```
本题解释到此为止，因为是第一次写题解，所以有些部分写的还不太好，请见谅。



---

## 作者：一滴小水滴 (赞：1)

### ~~我想会不会有人打表呢qwq？~~

其实这道题我们可以找一找规律。

先看一看给的几个样例：
```cpp
3
*D*
DDD
*D*

5
**D**
*DDD*
DDDDD
*DDD*
**D**

7
***D***
**DDD**
*DDDDD*
DDDDDDD
*DDDDD*
**DDD**
***D***
```

仔细看一看样例就可以知道，D是呈一个菱形状，矩阵的其它部分则都是*。

我们来找一找规律：
* 如果当前行<中间行，那么D的个数每次+2，如果当前行>=中间行，D的个数每次-2
* 每行 * 的个数就是（n（列数）-d（当前行D的个数）/2 （如果有不理解的可以自己摸索一下）。

既然规律已经跟大家说明清楚了，直接用二重循环就可以解决问题了。大家可以尝试自己做一做，做不出来就参考一下AC代码。
```cpp
//我也没有什么好讲的了，你们自己看吧。
#include<bits/stdc++.h>
using namespace std;
int n,d=1;  //记得把d先初始化为1。
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=(n-d)/2;j++)
			cout<<'*';
		for(int j=1;j<=d;j++)
			cout<<'D';
		for(int j=1;j<=(n-d)/2;j++)
			cout<<'*';
		cout<<endl;
		if(i<=floor(n/2))d+=2;
		else d-=2;
	}
	return 0;
}
```

---

## 作者：PC_DOS (赞：1)

本题为一道模拟题，观察题面和样例可以看出，对于大小为S的水晶(钻石?)，其每行的构成符合以下规则:

```
string(Line_i)=|i|*'*' + (S-2*|i|)*'D' + |i|*'*' , -(S-1)/2 <= i <= (S-1)/2
```

即对于第i行，有|i|个星号，(S-2*|i|)个D，|i|个星号，其中-(S-1)/2 <= i <= (S-1)/2，|i|表示i的绝对值。 

于是我们可以得到代码:

```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
string CreateRequiedString(long long nCount, char chrChrarater){ //创建由特定字符chrChrarater组成的长度为nCount的字符串的函数
	int i;
	string sAns;
	for (i = 1; i <= nCount; ++i)
		sAns += chrChrarater;
	return sAns;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int iSize; //尺寸
	register int i; //循环计数器
	cin >> iSize; //读入尺寸
	for (i = -(iSize - 1) / 2; i <= (iSize - 1) / 2; ++i){ //循环输出
		cout << CreateRequiedString(abs(i), '*') << CreateRequiedString(iSize - 2 * abs(i), 'D') << CreateRequiedString(abs(i), '*') << endl; //对于第i行，有|i|个'*'，(S-2*|i|)个'D'，|i|个'*'，其中-(S-1)/2 <= i <= (S-1)/2，|i|表示i的绝对值
	}
	return 0; //结束
}
```

---

## 作者：AveMarina (赞：0)

## 入门题
### 思路
首先观察样例，可以发现第一行不管有多少个字符，中间一定是D，而结合题目给的n是奇数可以得出结论： __第一行的(n >> 1) + 1这列的元素一定是D（这里我的下标从1开始）__，相信大家对这种写法不是很陌生，没错，这就是线段树里确定中间位置和左/右子树编号的写法的结合，功能同(n / 2) + 1。既然我扯到了线段树，大家就应该能猜到接下来的操作和 __区间__ 有关系了。如果我们将每个D的所在列的编号看做一个区间，不难发现这样一个事实： __在图像的上半部分，也就是包括全是D那一行的所有上一行，从第一行开始，D的位置在$[l, r]（此时l == r)，此后每一行，D的位置都是在上一行的区间上左右扩张得来的，即 [l - 1, r + 1] 。而图像的下半部分同理，是在上一行的区间上左右缩减来的，即[l + 1, r - 1]。__ 得出了这样的结论写两层循环判断下区间是进行扩张还是缩减就行了。
### 代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int main() {
	int n, l, r, val = 1, line;
	scanf("%d", &n);
	l = r = line = (n >> 1) + 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
        	cout << (j >= l && j <= r ? 'D' : '*');
		}
		if (i >= line) val = - 1;
		l -= val, r += val;
		puts("");
	}
	return 0;
}
```
### 题外话
其实这类题承载着我初学C语言时的一些特殊记忆。大约两三年前自学C，已经记不清那时候看的什么书了（可能是谭老的绿书，也可能是c primer plus)，总之类似的用循环打印各类字符图形的题往往能让我做上很长时间（怀疑智商那种），现在反观真是很有意思（思来想去还是把这段话留着吧）...

---

## 作者：YosemiteHe (赞：0)

小马大法好！

先分析一下，以样例 $\#2$ 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/ofxf9u75.png)

也就是说，先输出 $(n - i) ÷ 2$ 个 `*` 号，再输出 $i$ 个 `D` 号，最后输出 $(n - i) ÷ 2$ 个 `*` 号。


正着输出一遍，倒着输出一遍。循环时，$i$ 每次增加（减少）$2$。

Code：

```cpp
#include <bits/stdc++.h>//头文件
#define int long long//个人习惯
using namespace std;//命名空间
inline int read() { //快读
	int f = 1, v = 0;
	char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {v = v * 10 + c - '0'; c = getchar();}
	return v * f;
}
int n = read();//定义+读入
signed main(void) { //主函数
	for (int i = 1; i <= n; i += 2) { //输出上半部分和中间的 n 个 “D”
		for (int j = 1; j <= (n - i) / 2; ++j) {
			cout << "*";//输出 (n - i) / 2 个 “*”
		}
		for (int j = 1; j <= i; ++j) {
			cout << "D";
		}
		for (int j = 1; j <= (n - i) / 2; ++j) {
			cout << "*";
		}
		cout << endl;//注意换行
	}
	for (int i = n - 2; i >= 1; i -= 2) { //注意，输出上半部分时中间的 n 个 “D” 已经输出完毕，因此要从 n - 2 开始第二轮输出
		for (int j = 1; j <= (n - i) / 2; ++j) {
			cout << "*";
		}
		for (int j = 1; j <= i; ++j) {
			cout << "D";
		}
		for (int j = 1; j <= (n - i) / 2; ++j) {
			cout << "*";
		}
		cout << endl;
	}
	return 0;//结束
}
```

---

## 作者：TRZ_2007 (赞：0)

# Solution
拿到这道题目，就可以看出它是一道模拟题。分析一下样例：  
![](https://cdn.luogu.com.cn/upload/image_hosting/b1r9ip6w.png)  
我们可以看见，输出样例被我分成了4部分。先看用黑线隔开的。  
可以发现，当$n=7$时，上半部分是$1 $到$ \dfrac{n}{2}$，下半部分是$\dfrac{n}{2} $到$ n$，中间全输。  
红线隔开的也差不多。  
这样我们就可以利用黑色来模拟输出过程。  
# Code 
```cpp
#include <bits/stdc++.h>
using namespace std;

namespace IO {
	#pragma GCC target("avx")
	#pragma GCC optimize("Og")
	#pragma GCC optimize("Ofast")
	
	template<class T>
	inline void read(T& x) {
		x = 0;
		char ch;
		while(ch < '0' || ch > '9') {
			ch = getchar();
		}
		while(ch >= '0' && ch <= '9') {
			x = x * 10 + ch - '0';
			ch = getchar();
		}
	}
	
	template<class T>
	inline void write(T x) {
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
};

using namespace IO;

const int N = 110;

int n;
char str[N][N];

int main() {
	read(n);
	for(int i = 1;i <= n/2;i++) {//1st 2nd
		for(int j = 1;j <= n/2 - i + 1;j++) {// 1st
			putchar('*');
		}
		for(int j = 1;j <= 2*i-1;j++) {//全输
			putchar('D');
		}
		for(int j = 1;j <= n/2 - i + 1;j++) {// 2nd
			putchar('*');
		}
		puts("");
	}
	for(int i = 1;i <= n;i++) putchar('D');puts("");
	for(int i = n/2;i >= 1;i--) {// 3rd 4th
		for(int j = 1;j <= n/2 - i + 1;j++) {// 3rd
			putchar('*');
		}
		for(int j = 1;j <= 2*i-1;j++) {//全输
			putchar('D');
		}
		for(int j = 1;j <= n/2 - i + 1;j++) {// 4th
			putchar('*');
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Frank_R_Z (赞：0)

###
俗话说得好，~~暴力出奇迹~~。
直接疯狂模拟，把整个输出分成三份，以全是D的那一行为分界线，尝试for输出。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		if(i<=n/2)//不打=就WA了
		{
			for(int j=1;j<=(n-(2*i-1))/2;j++)cout<<"*";//前半部分的模拟
			for(int j=1;j<=2*i-1;j++)cout<<"D";
			for(int j=1;j<=(n-(2*i-1))/2;j++)cout<<"*";
			cout<<endl;
		}
		else if(i==n/2+1)//这里直接输出，但要注意只有用i==n/2+1才能起到作用
		{
			for(int j=1;j<=n;j++)
			{
				cout<<"D";
			}
			cout<<endl;
			continue;
		}
		else if(i>=n/2)
		{
			k=n-i;
			for(int j=1;j<=(n-(2*k+1))/2;j++)cout<<"*";//注意，后半部分的完全相反
			for(int j=1;j<=2*k+1;j++)cout<<"D";
			for(int j=1;j<=(n-(2*k+1))/2;j++)cout<<"*";
			cout<<endl;
		}
	}
	return 0;
}
//输出一块钻石'''

```
~~我不会说我调了20分钟的~~




---

## 作者：damage (赞：0)

## 题解

一道关于字符输出膜拟题！

我们发现它是一个上下（当然左右也是，只是```C++```默认不是竖着输出）对称的图形，并且最中间一行（记得$n$是奇数）根本没有```*```，我们就假设那一行为第$0$行。

那么共有$n$行，分别为第$(-\frac{n}{2}) - (\frac{n}{2})$行（此处$n$为整型，所以除以$2$自动取整）。

则发现在第$i$（$(-\frac{n}{2})\leq{i}\leq{(\frac{n}{2})}$）行左边（第一个```D```左边）有$\vert{i}\vert$个```*```（别忘了绝对值），右边也是；而中间则有$n-2\vert{i}\vert$个```D```，共$n$个字符。

所以只需要循环输出即可！

---

# 代码

```cpp
#include<stdio.h>
int n,k;
int abs(int x) //绝对值
{
	return x>0? x:-x;
}
int main()
{
	scanf("%d",&n);
	k=n>>1; //k为n的一半
	for(register int i=-k;i<=k;++i) //i的范围
	{
		for(register int j=0;j<abs(i);++j) putchar('*'); //|i|个*
		for(register int j=0;j<(n-abs(i<<1));++j) putchar('D'); //n-2|i|个D
		for(register int j=0;j<abs(i);++j) putchar('*'); //|i|个*
		putchar('\n');
	}
	return 0;
}
```

---

## 说明

关于本篇涉及到的位运算的讲解（其实就一种，大佬们肯定都会）

```x>>1```表示```x/2```，其实$x$>>$i$ $=\frac{x}{2^{i}}$。

```x<<1```表示```x*2```，其实$x$<<$i$ $=x\times{2^{i}}$。

---

