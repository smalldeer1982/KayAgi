# Red and Blue Balls

## 题目描述

一个栈内初始有n个红色和蓝色的小球，请你按照以下规则进行操作
1.只要栈顶的小球是红色的，将其取出，直到栈顶的球是蓝色
2.然后将栈顶的蓝球变成红色
3.最后放入若干个蓝球直到栈中的球数为n
以上3步骤为一次操作
如栈中都是红色球，则操作停止，请问几次操作后停止
ainta出完题发现他自己不能AC所以想请你帮忙

## 说明/提示

50%的数据，1<=n<=20

100%的数据，1<=n<=50

翻译提供者：leonyy

## 样例 #1

### 输入

```
3
RBR
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
RBBR
```

### 输出

```
6
```

## 样例 #3

### 输入

```
5
RBBRR
```

### 输出

```
6
```

# 题解

## 作者：泰勒斯威夫特 (赞：4)

很容易发现,栈中**靠上的蓝色球**的出栈,对它下方的蓝色球没有影响.

举个例子:
![举例1](https://cdn.luogu.com.cn/upload/pic/61353.png)

**第一步中靠上的蓝色球**在**第三步**出栈了,这一过程对它下面的蓝色球(即**第一步中靠下的蓝色球**)没有产生影响.

这启示我们**由上到下**分别计算每一颗(初始状态下的)蓝色球出栈需要的步数,再相加得到答案.

不妨设$f(x)$表示离栈顶距离为$x$的蓝色球出栈需要的步数,那么上面的样例的答案即为$f(2)+f(3)$,即"离栈顶距离为$2$的蓝色球出栈所需步数$+$离栈顶距离为$3$的蓝色球出栈所需步数".

接下来的问题就是求$f(x)$函数的值.

显然$f(1)=1$,即如果该球在栈顶,出栈需要$1$步操作.

考虑更一般的情况,我们会发现一个蓝色球想出栈的第一步,一定是将该蓝色球所在位置变为红色球,再将上方所有红色球变为蓝色球.

例如上面例子中的$"3\rightarrow4"$这一步,原在**从顶到下第三个位置**的蓝色球想出栈,第一步就是把**从顶到下第三个位置**变为红色球,同时把**从顶到下第一/二个位置**变为蓝色球.

于是可以得到递推方程:

$$f(x)=f(1)+f(2)+...+f(x-1)+1\quad(x\geq2)$$

也就是说,从顶到下第$x$个位置的蓝色球想出栈,等效于先**走一步**变为 "**$x$位置红,$1...x-1$位置蓝**",再让$1...x-1$位置的蓝色球依次出栈.

由于这道题数据范围较小,我们当然可以$O(n^2)$计算所有$f(x)$的值,但我们也可以推推通项公式.

由递推式,有
$$f(i-1)=f(1)+f(2)+...+f(i-2)+1$$
所以
$$f(i)=f(1)+f(2)+...+f(i-2)+f(i-1)+1$$
$$f(i)=[f(1)+f(2)+...+f(i-2)+1)]+f(i-1)$$
$$f(i)=2\times f(i-1)$$

所以

$$f(i)=2^{i-1}$$

所以

$$ans= \sum_{if \space s[i]==B} (2^{i-1})$$

实际代码中,需要注意字符串的下标从$0$开始.

### 代码
```
#include<bits/stdc++.h>
using namespace std;

int n;
long long ans,p;
string s;

int main()
{
	cin>>n>>s;
	for(int i=0;i<s.size();i++)
	{
		p= i==0? 1 : p*2;
		if(s[i]=='B')
			ans+=p;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Tritiger彪 (赞：3)

此题为找规律题，我们随便打几个表可以发现，当当前字符串的第i个字符为B时，答案就需要加上2^i次方，所以此题很容易得到正解
代码如下
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define inf 0x7fffffff
using namespace std;
int n,st[51];char a[51];
long long ans;
long long pow(int x)
{
     long long s=1;
     for(int i=1;i<x;i++)
         s*=2;
     return s;
 }
int main()
{
    scanf("%d",&n);
    scanf("%s",a);
    for(int i=1;i<=n;i++)
       if(a[i-1]=='R')st[i]=1;
       else st[i]=2;  
    for(int i=1;i<=n;i++)if(st[i]==2)ans+=pow(i);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Engulf (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF399B)

[或许更好的阅读体验](https://www.luogu.com.cn/blog/t-m-j-y-h-0-9/solution-cf399b)

## 分析

本题暴力解法会 TLE，所以我们需要进一步分析。

定义状态 $a_i$ 表示把前 $i$ 个球全部变为红色的步数，那么如果第 $i$ 个球是蓝色的话，我们需要做如下操作：

1. 把前 $i-1$ 个球弹出；

2. 把第 $i$ 个球变成红色；

3. 把第 $i$ 个球前面填上蓝色球。

显然，既然取到了第 $i$ 个球，那这个球前面的一定都是红球，需要 $a_{i-1}$ 次转换，那么转移方程如下：

$$a_i=\begin{cases}1,&i=1,\\\sum\limits_{j=1}^{i-1}a_{j}+1,&i\ge2.\end{cases}$$

最后，统计：

$$\sum_{i=1,s_i=\texttt{B}}^{n}a_i$$

就是最终的答案。其中 $s_i$ 表示第 $i$ 个球的颜色。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[55];
int n;
char s[55];
int main(){
	cin>>n>>s+1;
	a[1]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++)a[i]+=a[j];
		a[i]++;
	}
	long long ans=0;
	for(int i=1;i<=n;i++)if(s[i]=='B')ans+=a[i];
	cout<<ans;
	//system("pause");
}
```

---

## 作者：yzh_Error404 (赞：2)

看到这道题的第一反应：~~懵逼~~

先做一遍模拟

1.每次把栈顶的所有红球取出

2.把发现的第一个蓝球替换成红球

3.用蓝球填满空缺


![第三个样例](https://cdn.luogu.com.cn/upload/image_hosting/lui7tys7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

可以发现找到的第一个蓝球前的所有红球全变蓝了

而这个蓝球变成了红球

所以第$i$个蓝球的操作次数等于前面所有变蓝的球的操作次数之和

可以推出$f[i]=\sum_{j=1}^{i-1}f[j]$

而前面的次数又可以递推

可以得出每一个位置上的蓝球代表的操作次数

![](https://cdn.luogu.com.cn/upload/image_hosting/t3j1n0u1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

上代码

码风极丑（勿喷
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
unsigned long long ans;
string a;
int main()
{
	cin>>n;
	cin>>a;
	for(register int i=0;i<n;i++)
    		if(a[i]=='B')ans+=pow(2,i);//根据上图推出
	cout<<ans;
	return 0;
}
```


---

## 作者：happybob (赞：0)

# 题意

给定一个栈，按照题意模拟每次操作，问一共会做多少次操作。

# 解法

明显暴力不可行，但是我们发现假设这个栈从下到上定义为 $a_1, a_2, a_3, \cdots, a_n$，设 $a_1 = 1$ 表示蓝色，$a_1 = 2$ 表示红色，那么 $ans = \sum_{i=1}^n \begin{cases} a_i = 1 & 2^{(i-1)} \\ \text{otherwise} & 0\end{cases}$ 。

注意字符串起始下标为 $0$ 即可。

代码：

```cpp
#pragma GCC optimize("-Ofast")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
string s;

signed main()
{
	scanf("%lld", &n);
	cin >> s;
	int l = s.size() - 1, cnt = 0;
	reverse(s.begin(), s.end());
	for (register int i = l; i >= 0; i--)
	{
		if (s[i] == 'B')
		{
			int nx = i + 1;
			int sum = l - nx + 1;
			cnt += 1ll << sum;
		}
	}
	printf("%lld\n", cnt);
	return 0;
}
```


---

## 作者：mango09 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF399B)

[~~更差的阅读体验~~](https://www.luogu.com.cn/blog/305532/post-ti-xie-cf399b)

**思路**

考场上直接模拟 TLE 50 分，得换一个方法。

为方便描述，记蓝球为 B，红球为 R；

我们定义 $f_i$ 为把深度 $i$ 的 $a_i$ B 变成 R 的操作数，那么在变色之前 $a_i$ 一定前面的都是 R 。

那么变色之前的最后一步显然是将上面所有的 R 都拿走，再把 $a_i$ 变色，在它上面放满 B。然后再进行直到上面的 B 全部变成 R。

则有递推式：

$\boxed{f_i=\sum\limits_{j=1}^{i-1}f_j+1}$

又有 $f_1=1$，则 $f_i=2f_{i-1}$。

即 $f_i=2^{i-1}$。

**代码**

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;

int n, x, ans;
char c;

signed main()
{
	scanf("%lld\n", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%c", &c);
		if (i == 1)
		{
			x = 1;
		}
		else
		{
			x <<= 1;
		}
		if (c == 'B')
		{
			ans += x;
		}
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：lxgw (赞：0)

upd 2021-04-26: 更正了之前的一些笔误。

#### [原题传送门](https://www.luogu.com.cn/problem/CF399B)
### 思路
~~考试的时候打表找规律 A 的~~。

不妨把这个栈内的求得排列看成二进制下的一个数，红球代表该数位为1，蓝球则代表0。发现它的操作中类似于二进制加法中的进位：
1. 把红球取出：加1时，末尾的1全部进位，剩0；
2. 把栈顶蓝球变为红球：进位来的一个1；
3. 补蓝球：进位后的1全部变为0.

即题目所求为把原有二进制数每次加 1 ，多少次后可以得到 $(11\dots 1) _ {2}$（共 $n$ 个 1） 。


所以不妨设球数为 $n$ ，$a$ 表示栈中球原二进制下转为十进制后的数，则答案为 $(2^n-1)-a$ 。

代码就不贴了。

完结撒花~

谢谢 qwq 。

---

## 作者：ycyoi (赞：0)

[CF399B Red and Blue Balls](https://www.luogu.com.cn/problem/CF399B)

本体乍一看实际上是一道模拟，但是他的复杂度是$2^n$,所以我们要从别的方向来思考这道题。
### 题意
本题实际上就是求将所有蓝色球排出需要多少次，而我们发现，深度为$i$的蓝色球，他排除需要的次数便是$2^{i-1}$，证明如下：

我们设$f_i$为把 i 以及其上面的全部翻转为红色的步骤数，那么显然，如果$a_i=$ B ,那么在翻$a_i$之前一定他前面的都是 R 那么之后的第一步一定是将所有的$a_i$上面的拿走，把$a_i$变色，把$a_i$上面全部填充成B。根据定义，很容易得到递推式$(\sum\limits_{j=1}^{i-1}f_j)+1$

再根据$f_{i-1}$
 的定义，很容易得到递推式优化$f_i=2\times f_{i-1}$
边界条件为$f_i=1$这很显然，所以我们直接可以用运算符 << 解决这个问题。

### 代码实现
```cpp
#include<bits/stdc++.h>
typedef long long ll;
inline ll read();//快读
using namespace std;
ll n,i,ans;
char c;
signed main() {
	cin.tie(0);//cin加速  
	n=read();
	for(i=1; i<=n; i++) {
		cin>>c;
		if(c=='B') {
			ans+=1LL<<(i-1);//1LL避免溢出  
		}
	}
	printf("%lld\n",ans); 
}
inline ll read() { //快读
	ll s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'&&ch!=EOF) {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
```


---

## 作者：liuzitong (赞：0)

这个题一开始我把左右搞反了

结果考试0分

反过来就对了。。。。

-------
分割线

如果一个栈中最低端已经是红球就相当于不用处理栈底

假设一个栈中只有蓝球，会是多少步呢？

由打表可知：前5项为

1 3 7 15 31

有什么规律呢？
1 + 2 = 3
3 + 4 = 7
7 + 8 = 15
....

好了如果栈底是红球剩下的就是蓝球，而栈底无影响，现在这种情况我们知道了

可是。。。大多数不是这样

比如红红蓝红蓝红。。。。

这怎么办？？

我们尝试转换已知问题，发现红红...蓝只需要一步即可变为

蓝蓝...红

然后这样每次栈顶是蓝色用第一种方法解决，不是就花一步转换


```cpp
#include<bits/stdc++.h>

using namespace std;

long long n,a[1001];
char ch;
long long b[60] = {0,1,3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383,32767,65535,131071,262143,524287,1048575,2097151,4194303,8388607,16777215,33554431,67108863,134217727,268435455,536870911,1073741823,2147483647,4294967295,8589934591,17179869183,34359738367,68719476735,137438953471,274877906943,549755813887,1099511627775,2199023255551,4398046511103,8796093022207,17592186044415,35184372088831,70368744177663,140737488355327,281474976710655,562949953421311,1125899906842623};
//long long c[60] = {0,1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648,4294967296,8589934592,17179869184,34359738368,68719476736,137438953472,274877906944,549755813888,1099511627776,2199023255552,4398046511104,8796093022208,17592186044416,35184372088832,70368744177664,140737488355328,281474976710656,562949953421312};//打表(因为只有50的数据范围

int main() {
	cin>>n;
	/*
	string s;
	cin>>s;
	int len = s.length();
	for(int i = 0;i < len;++i){
		a[i + 1] = s[i] - 'B';
	}
	*/
	ch = getchar();
	while(ch < 'A' || ch > 'Z')//去掉多余字符
		ch = getchar();
	for(long long i = 1; i <= n; ++i) {
		a[i] = ch - 'B';
		ch = getchar();
	}//16为红0为蓝
	long long y = n,tot = 0,x = 0;
	x = 0;
	for(int i = n; i >= 1; --i) {//把栈顶连续蓝的转换成红的
		if(a[i] == 0) {
			x ++;
			a[i] = 16;
		} else {
			y = i;
			break;
		}
	}
	tot += b[x];
	for(int i = y; i > 0; --i) {//如果是蓝的，花一步转换为一直问题
		x++;
		if(a[i] == 0) {
			tot += b[x - 1] + 1;
		}
	}
	
	cout<<tot<<endl;

	return 0;
}

```


---

