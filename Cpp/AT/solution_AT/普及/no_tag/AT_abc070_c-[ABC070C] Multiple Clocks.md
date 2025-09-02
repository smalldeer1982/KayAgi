# [ABC070C] Multiple Clocks

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc070/tasks/abc070_c

$ N $ 台の時計があり、$ i(1≦i≦N) $ 番目の時計の針はちょうど $ T_i $ 秒で時計盤を $ 1 $ 周します。   
 最初、全ての時計の針は真っ直ぐ上に向いており、止まっています。   
 イルカは、全ての時計の針を同時に動かし始めました。   
 再び、全ての時計の針が真っ直ぐ上に向くのは何秒後でしょうか?

## 说明/提示

### 制約

- $ 1≦N≦100 $
- $ 1≦T_i≦10^{18} $
- 入力は全て整数である。
- 答えは $ 10^{18} $ 秒以内である。

### Sample Explanation 1

$ 2 $ つの時計があり、各時計の針が真っ直ぐ上に向くのは以下の時刻です。 - $ 1 $ 番目の時計の針: 時計の針を動かし始めてから、$ 2 $ 秒後、$ 4 $ 秒後、$ 6 $ 秒後、$ ... $ - $ 2 $ 番目の時計の針: 時計の針を動かし始めてから、$ 3 $ 秒後、$ 6 $ 秒後、$ 9 $ 秒後、$ ... $ したがって、$ 2 $ つの時計の針が真っ直ぐ上に向くのにかかる秒数は $ 6 $ 秒となります。

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
6```

## 样例 #2

### 输入

```
5
2
5
10
1000000000000000000
1000000000000000000```

### 输出

```
1000000000000000000```

# 题解

## 作者：Zachary_Cloud (赞：5)

## $题意$

很明显，这道题目就是让我们求 $n$ 个数的**最小公倍数**。

首先，我们先要求出 $2$ 个数的最小公倍数。

于是，我们得出了时间复杂度为 $O(nm)$ 的求最小公倍数的算法：

```cpp
int lcm(int n,int m) {
	for (int i=max(n,m); i<=n*m; i++)
		if (i%n==0&&i%m==0) return i;
}
```

可是，这显然过不了题目的数据 $1≤T_i≤10^{18}$。

这时，我们需要一种更高级的求最小公倍数的算法：$\large\color{red}\texttt{辗转相除法}$

辗转相除法实质上只是一种求最大公约数的算法，但我们知道：$lcm(n,m)=nm/gcd(n,m)$


```cpp
int gcd(int n,int m) {
	return (m==0)?n:gcd(m,n%m);
}
int lcm(int n,int m) {
	return n*m/gcd(n,m);
}
```

那么求多个数的最小公倍数就迎刃而解了。

## $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b) {  //最大公约数
	return (b==0)?a:gcd(b,a%b);
}
ll lcm(ll a,ll b) {  //最小公倍数
	return a/gcd(a,b)*b;
}
ll n,tem,a;
int main() {
// 	freopen("AT2692.in","r",stdin);
// 	freopen("AT2692.out","w",stdout);
	scanf("%lld",&n);
	tem=1; //开始赋值为1
	for (int i=1; i<=n; i++) scanf("%lld",&a),tem=lcm(tem,a);  //求lcm
	printf("%lld",tem);
	return 0;
}
```


---

## 作者：Fido_Puppy (赞：3)

相信学过小学奥数的同学都知道，这题就是求 $\texttt{N}$ 个数的最小公倍数。

怎么求 $\texttt{N}$ 个数的最小公倍数，首先就要解决两个数的最小公倍数怎么求。

首先， 我们可以定义一个 $\texttt{s}$，它为其中一个数的倍数，接着只要判断是否是另一个数的倍数就行了。

设求 $\texttt{n}$ 和 $\texttt{m}$ 的最小公倍数。

```pascal
s:=n;
while s mod m<>0 do s:=s+n;
```
但是这并不是最快的。

我们都知道 $lcm(i,j)=i*j/gcd(i,j)$。

而 $gcd(i,j)$ 可以用辗转相除法。

```pascal
function gcd(a,b:longint):longint;
begin
  if b=0 then exit(a) else exit(gcd(b,a mod b));
end;
function lcm(a,b:longint):longint;
begin
  exit(a div gcd(a,b)*b);
end;
```

求 $\texttt{N}$ 个数的最小公倍数其实就设一个变量 $\texttt{t}$ 。

```pascal
t:=1;
for i:=1 to n do t:=lcm(t,a[i]);
```

代码已经很简单了，这里就不给出了。

---

## 作者：BotDand (赞：2)

# $\text{Problems}$
有$n$台钟表，第$i$个钟表的秒针经过$t_i$秒绕表盘一周。最初，所有的钟表的秒针都指向上方。某人开始同时顺时针拨动所有时钟的秒针。下一次所有的时钟的秒针都向上是在几秒后？
# $\text{Answer}$
显而易见，这题是要求$n$个数的最小公倍数。

显然$\operatorname{lcm}(x,y)=\dfrac{x \times y}{\gcd(x,y)}$

给个$\gcd$的伪代码：
```cpp
int gcd(int x,int y)
{
	if(!y) return x;
	return gcd(y,x%y);
}
```
# $\text{Code}$
老代码。
```pascal
var
  n,i:longint;
  a:array[1..100] of qword;
 function gys(x,y:qword):qword;
  begin
    if y=0 then exit(x);exit(gys(y,x mod y));
  end;
begin
  readln(n);
  for i:=1 to n do readln(a[i]);
  for i:=2 to n do a[i]:=a[i] div gys(a[i],a[i-1])*a[i-1];
  writeln(a[n]);
end.
```


---

## 作者：yu__xuan (赞：1)

这是一个简单的数论吧。

## **思路：求n个数的最小公倍数**
类似于这一题:[P4057 [Code+#1]晨跑](https://www.luogu.org/problemnew/show/P4057)

但我感觉这题要难一些。我太弱了！！！
```cpp
inline long long read(){
	long long x=0;
	bool f=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=!f;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0',c=getchar();
	}
	return f?-x:x;
}//读入优化，可以快一点。
```


```cpp
unsigned long long gcd(unsigned long long x,unsigned long long y){
	if(y==0) return x;
	else return gcd(y,x%y);
}//辗转相除法
```

不明白辗转相除法的[康康](https://baike.baidu.com/item/%E8%BE%97%E8%BD%AC%E7%9B%B8%E9%99%A4%E6%B3%95)

怎么求最小公倍数：两数的积除两数的最大公约数。不明白的就百度吧。

假设有三个数a,b,c。这三个数的最小公倍数就是其中两个数的最小公倍数与另一个数的最小公倍数。所以n个数我们可以不断求其中两个数的最小公倍数。然后就行了。数据比较大用无符号长整型就可以了。

**Code：**
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
unsigned long long a[101];
inline long long read(){
	long long x=0;
	bool f=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=!f;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0',c=getchar();
	}
	return f?-x:x;
}
unsigned long long gcd(unsigned long long x,unsigned long long y){
	if(y==0) return x;
	else return gcd(y,x%y);
}
int main(){
	int n;
	n=read();//多少个表
	for(int i=1;i<=n;++i){
		a[i]=read();
	}//每个表多长时间转一周。
	for(int i=2;i<=n;++i){
		a[i]=a[i]/gcd(a[i],a[i-1])*a[i-1];
	}//求两个数的最小公倍数并更新第二个数。
	cout<<a[n];//输出答案。
	puts("");//换行。
	return 0;
}
```

---

## 作者：MattL (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT2692) & [原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/2692) & [双倍经验](https://www.luogu.com.cn/problem/P4057)

~~这题根本算不上黄题，只有橙题的难度……~~

---

**解题思路：**

学过一点点小学奥数的都知道，这题是要我们求这几个数的**最小公倍数**。

众所周知，$\operatorname{lcm}(x,y)=\dfrac{x \times y}{\gcd(x,y)}$ 。所以，我们只需要求最大公因数即可。

- 我们小学用的是什么方法？

- 写因数？$10^{18}$，一定会 TLE 的。

- 短除法？也要求因数，应该也会 TLE 的。

- 怎么办呢？

用**辗转相除法**，辗转相除法的时间复杂度是 $\Theta(\log_2 n)$！！！

首先，我们先来看看辗转相除法的弱化版：辗转相减法。

因为 $\gcd(x,y)=\gcd(x-y,y)(x\geqslant y,y\ne0)$，所以我们就可以用这个式子递推了。

但……$x<y$ 咋办？我们把 $x$ 和 $y$ 交换即可。所以，当 $x< y$ 时，$\gcd(x,y)=\gcd(y,x)(x< y,y\ne0)$

那……$y=0$ 呢？那恭喜你，你的 $x$ 就是答案啦！

所以，我们可以写出函数：

```cpp
inline long long gcd(long long q,long long w)
{
    if(w==0)return q;
    if(q<w)return gcd(w,q);
    return gcd(q-w,w);
}
```

相信你现在一定会辗转相减法了，那么我们再来看看它的升级版：辗转相除法

辗转相除法就是可以优化多次减法法步骤。其实和辗转相减法差不多，我们直接来看代码吧：

```cpp
inline long long gcd(long long q,long long w)
{
    return (w==0)?q:gcd(w,q%w);//当w==0了，直接返回q，否则交换、取模
}
```

---

**代码：**

现在你一定理解解法了吧，我们来看完整代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;
inline long long read()
{
    register long long x=0,f=1;
    register char c=getchar();
    while(c<'0'||c>'9')if(c=='-'){f=-1,c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}

long long t,n,ans=1;
inline long long qp(long long q,long long w)
{
    return (w==0)?q:qp(w,q%w);
}

int main() {
    n=read();
    while (n--)
    {
        t=read();
        ans=t/qp(ans,t)*ans;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：cjZYZtcl (赞：0)

## 题意很明显，让我们求 $n$ 个数的最小公倍数。
那怎么求呢？

我们求两个数的最小公倍数的方法是 $x*y/gcd(x,y)$ ，那么求多个数也是同理，所有数的乘积除以相邻两个数的最大公约数即可。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
int gcd(int x, int y){
	if(y == 0) return x;
	return gcd(y, x % y);
}
signed main(){
	int n = read(), sum = 1;
	for(int i = 1; i <= n; i++){
		int x = read();
		sum = sum / gcd(sum, x) * x;
	}
	write(sum);
}
```


---

## 作者：tZEROちゃん (赞：0)

### Description

> 求 $n$ 个数的最小公倍数

### Solution

为什么答案会是这 $n$ 个数的最小公倍数。

第一个指针会在 $(t_1 \times 1)\ \tt{s}$，$(t_1 \times 2)\ \tt{s}$，$(t_1 \times 3)\ \tt{s}$，$\cdots$ 的时候指向上方。        
第二个指针会在 $(t_2 \times 1)\ \tt{s}$，$(t_2 \times 2)\ \tt{s}$，$(t_2 \times 3)\ \tt{s}$，$\cdots$ 的时候指向上方。       
$\cdots$          
那么显然，第 $n$ 个指针会在 $(t_n \times 1)\ \tt{s}$，$(t_n \times 2)\ \tt{s}$，$(t_n \times 3)\ \tt{s}$，$\cdots$ 的时候指向上方。

那么如果在第 $k\ \tt{s}$ 后都指向上方，$k$ 显然是 $t_1$ 的倍数，$t_2$ 的倍数，$\cdots$，$t_n$ 的倍数。

所以这道题目就是求 $t_1, t_2, \cdots, t_n$ 的最小公倍数。



### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
int main() {
	int t;
	cin >> t;
	ull ans; cin >> ans;
	for (int i = 1; i < t; i++) {
		ull b;
		cin >> b;
		//cout << ans << ' ';
		ans = ans / __gcd(ans, b) * b;
	}
	cout << ans;
}
```

---

## 作者：TRZ_2007 (赞：0)

**题解 [AT2692 【[ABC070C] Multiple Clocks】](https://www.luogu.com.cn/problem/AT2692)**

# Solution  
这道题其他 dalao 们可能都认为太简单了就没有讲结论是怎么来的（~~不过的确是显然~~），所以先讲一下为什么是所有数的最小公倍数。  
放开有 $n$ 个数字的情况，先看看有两个数字的情况。刚刚开始的思路肯定是很暴力的枚举每一个时间，看看两针是否重合，以 t[1] = 4,t[2] = 6 为例如图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/7th5ery2.png)  

得出两个数字的结论之后，我们就可以轻易的得出最终的答案就是所有数字的最小公倍数。  

但是还要注意一点，这题的数据范围有一点大，需要一些~~技巧~~。  
~~最小公倍数总没有人不会求了吧~~  

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

const int N = 109;

ll a[N];
int n;

int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		scanf("%llu",&a[i]);
	}
	for(int i = 2;i <= n;i++) {
		a[i] = a[i] / __gcd(a[i],a[i - 1]) * a[i - 1];//注意，由于10^32还是超过了ull的最大范围，所以我们做的时候要先除后乘。
	}
	printf("%llu\n",a[n]);
	return 0;
}
```

---

## 作者：Star_Wind (赞：0)

这题看似是黄题，但其实是恶评一道。读过小学五年级的人都知道，要使这些指针再次指向同一个位置，就是求这些数的最小公倍数。

求一行数的最小公倍数，其实就是求$\text{lcm}(......\text{lcm}( \text{lcm}(a_1,a_2),a_3)......,a_n)$ ，知道两个数的最小公倍数就是它们的乘积除以它们的最大公约数，代码就好办了。

注意要开 ull ，并且求的时候要用$a_i/\text{gcd}(a_i,a_{i-1})*a_i$ ，不然两个乘在一起会爆掉

AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long a[233],t;
int n;
unsigned long long gcd(unsigned long long a,unsigned long long b)
{
	if(a%b==0) return b;
	else return gcd(b,a%b);
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=2;i<=n;i++)
      a[i]=a[i]/gcd(a[i],a[i-1])*a[i-1];
    cout<<a[n]<<endl;
    return 0;
}
```


---

## 作者：Black_Porridge (赞：0)

原题[戳我](https://atcoder.jp/contests/abc070/tasks/abc070_c)

分析题意,不难得此题为求$n$个数的最小公倍数~~又是一道语文题~~.

求最小公倍数,用辗转相除法即可.

具体做法为:
用较大数除以较小数，再用出现的余数（第一余数）去除除数，再用出现的余数（第二余数）去除第一余数，如此反复，直到最后余数是0为止。如果是求两个数的最大公约数，那么最后的除数就是这两个数的最大公约数。(参考百度知道)

用代码表示为:

```
 while(k!=0)
        {
            a=b;
            b=k;
            k=a%b;//辗转相除
        }
```
#### 这道题一定要开$long$  $long$!!!

$code:$
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{ 
    ll N;
    cin>>N;
    vector<ll> T(N);//闲到飞起定义一个动态数组 这里说一下定义方法为:vector <数据类型> 数组名称
    for(ll i=0;i<N;i++)
    {
        cin>>T[i];//输入
    }
    sort(T.begin(),T.end());//排序
    for(ll i=0;i<N-1;i++)
    {
        ll a,b;
        if(T[i]<T[i+1])
        {
            a=T[i+1];
            b=T[i];
        }
        else
        {
            a=T[i];
            b=T[i+1];
        }
        ll k=a%b;
        while(k!=0)
        {
            a=b;
            b=k;
            k=a%b;//辗转相除
        }
        T[i+1]=T[i]/b*T[i+1];
    }
    cout<<T[N-1]<<endl;
   完结~
}
```

---

