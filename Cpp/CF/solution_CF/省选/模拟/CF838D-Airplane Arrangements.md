# Airplane Arrangements

## 题目描述

There is an airplane which has $ n $ rows from front to back. There will be $ m $ people boarding this airplane.

This airplane has an entrance at the very front and very back of the plane.

Each person has some assigned seat. It is possible for multiple people to have the same assigned seat. The people will then board the plane one by one starting with person $ 1 $ . Each person can independently choose either the front entrance or back entrance to enter the plane.

When a person walks into the plane, they will walk directly to their assigned seat. Then, while the seat they’re looking at is occupied, they will keep moving one space in the same direction. A passenger will get angry if they reach the end of the row without finding their assigned seat.

Find the number of ways to assign tickets to the passengers and board the plane without anyone getting angry. Two ways are different if there exists a passenger who chose a different entrance in both ways, or the assigned seat is different. Print this count modulo $ 10^{9}+7 $ .

## 说明/提示

Here, we will denote a passenger by which seat they were assigned, and which side they came from (either "F" or "B" for front or back, respectively).

For example, one valid way is 3B, 3B, 3B (i.e. all passengers were assigned seat 3 and came from the back entrance). Another valid way would be 2F, 1B, 3F.

One invalid way would be 2B, 2B, 2B, since the third passenger would get to the front without finding a seat.

## 样例 #1

### 输入

```
3 3
```

### 输出

```
128
```

# 题解

## 作者：Soulist (赞：29)

好仙的题啊 TAT


直接计数非常困难，我们考虑转换，假想每个人随机指定一个位置并开始走，求最后合法的概率。

然而这样计算仍然非常困难，注意到每个人可以往左走也可以往右走，我们将之想象成在一个 $1\to n$ 的环上『顺时针』/『逆时针』走，然而这样无法表示非法的情况，考虑在 $1$ 与 $n$ 的接口处增加一个位置 $n+1$，那么如果这个位置被占据了就说明状态非法，否则均合法。

于是我们只需要统计给一个 $n+1$ 的环分配 $m$ 个人任意走最后使得 $n+1$ 没有被占据的概率即可，如果认为初始可以配置在 $n+1$ 处，那么显然在这个环上的每个位置都是等价的，所以概率均相同，于是一个位置被占据的概率为 $\frac{m}{n+1}$，可以得到答案发生的概率为 $\frac{n+1-m}{n+1}$，乘以方案数 $(2\times (n+1))^m$ 即可。



---

## 作者：Karry5307 (赞：16)

### 题意

飞机上有 $n$ 个座位，$m$ 个人每个人有一个目标座位。每个人会依次从前门和后门中的一个进来然后找到目标座位。如果目标座位有人的话就会一直往另一边走直到找到一个座位坐下。求每个人都能找到一个座位的方案数。

$\texttt{Data Range:}1\leq m,n\leq 10^6$

### 题解

好题。

如果题做得多的就会知道有个题叫[淘米神的树](https://www.luogu.com.cn/problem/P5450)，发现这个题目人可以从两个门中选一个进来，那个题是一开始两个点中选一个操作，所以考虑类似那个题一样的，在前门和后门中设一个虚拟节点，也就是变成一个长度为 $n+1$ 的环。这个时候每个人会从某一个地方出现然后走，总方案数为 $(2(n+1))^m$。

接下来考虑排除不合法的。注意到，如果 $n+1$ 位置被占的话就不合法了（相当于这个人走了一圈回来），同时因为环上每个位置等价，所以说 $n+1$ 位置被占的概率为 $\frac{m}{n+1}$，于是答案为 $\frac{n+1-m}{n+1}(2(n+1))^m$。

### 代码

```cpp
// 我和 tommy0103 贴贴/qq
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51,MOD=1e9+7;
ll n,m;
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
    	neg=-1;
    	ch=getchar();
	}
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
	ll res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
int main()
{
	n=read(),m=read();
	printf("%d\n",(li)(n+1-m)*qpow(n+1,MOD-2)%MOD*qpow(2*(n+1),m)%MOD);
}
```



---

## 作者：jun头吉吉 (赞：9)

## 题意
一共 $n$ 个位置，你需要为 $m$ 个人定方向和位置，每个人会按顺序找到这个方向在定下的位置之后的第一个空的坐下。

求让每个人都能坐下的方案数。
## 题解
首先声明这是一篇充(da)满(biao)了(zhao)智(gui)慧(lv) 的题解，因为笔者不会高妙的做法。

首先我们考虑 $n=m$ 的情况，时光倒流，让每个人按顺序从位置上回去。那么如果我们当前让某个位置的人回去了，那么考虑他原来想要的位置可以是那些。分析一波发现一定要在同一个连续段内，而方案数考虑两个方向恰好就是这个连续段的长度 $+1$。然后我们就可以 $\rm dp$ 了，记 $f_i$ 表示长度为 $i$ 的连续段走人走到空的方案数，不妨枚举走的是 $j$，那么变成两个不相干的连续段，一共还要走 $i-1$ 人，分配顺序就是 $\binom{i-1}{j-1}$，也就是：
$$
f_{i}=(i+1)\times \sum_{j=1}^{i}\binom{i-1}{j-1} f_{j-1}\times f_{i-j}
$$
边界是 $f_0=1$。但是这个 $\rm dp$ 是 $\mathcal O(n^2)$ 的。但是通过一些人(O)类(E)智(I)慧(S)我们可以得到 $f_i=2(2i+2)^{i-1}$。

我们现在已经成功解决 $n=m$ 的情况了，但问题是不一定最后的局面是连续的。我们首先枚举最后有 $k$ 段，那么每一段都是独立的。那么我们有 $k-1$ 个间隔，必须大于 $0$，还有开头和结尾的两端可以为 $0$，于是就相当于 $n-m+2$ 分给 $k+1$ 个大于 $0$ 的变量，方案数是 $\binom{n-m+1}k$。记 $F(x)$ 为 $\{f_1,f_2,\dots\}$ 的 $\mathrm{EGF}$，那么答案就是

$$
m![x^m]\sum_{k=0}\binom{n-m+1}{k}F^k(x)=m![x^m](F(x)+1)^{n-m+1}
$$

如果直接多项式快速幂显然是过不了的，更何况模数是 $10^9+7$，我们还得继续推柿子。

记 $n'=n-m+1$，然后稍微化一点：
$$
m![x^m]\left(\sum_{i=0}\frac{2(2i+2)^{i-1}}{i!}x^i\right)^{n'}=2^m\times m![x^m]\left(\sum_{i=0}\frac{(i+1)^{i-1}}{i!}x^i\right)^{n'}
$$
然后好像我就不会了，只好打表找规律力。把 $m![x^m]\text{后面一坨}$ 放进表格里：

|       | $n'=1$ | $n'=2$ | $n'=3$  | $n'=4$  | $n'=5$  | $n'=6$  | $n'=7$   | 插值多项式 |
| ----- | ------ | ------ | ------- | ------- | ------- | ------- | -------- | ---------- |
| $m=1$ | $1$    | $2$    | $3$     | $4$     | $5$     | $6$     | $7$      | $n$        |
| $m=2$ | $3$    | $8$    | $15$    | $24$    | $35$    | $48$    | $63$     | $n(n+2)$   |
| $m=3$ | $16$   | $50$   | $108$   | $196$   | $320$   | $486$   | $700$    | $n(n+3)^2$ |
| $m=4$ | $125$  | $432$  | $1029$  | $2048$  | $3645$  | $6000$  | $9317$   | $n(n+4)^3$ |
| $m=5$ | $1296$ | $4802$ | $12288$ | $26244$ | $50000$ | $87846$ | $145152$ | $n(n+5)^4$ |

我们大胆猜测 $m$ 对应的多项式是 $n(n+m)^{m-1}$，于是答案就是：
$$
2^m\times n'\times(n'+m)^{m-1}
$$
## 代码
```cpp
int n,m;
signed main(){
	read(n,m);n=n-m+1;
	write(((mint(2)^m)*n*(mint(n+m)^m-1)).x);
}
```

---

## 作者：JK_LOVER (赞：7)

## 题意
有 $n$ 个座位， $m$ 个人，每个人可以从任意一个座位出发，可向左，也可向右，在第一个空位坐下，求问方案数。
## 分析
我们发现这个问题极不好 $dp$ ，考虑数学方法 
$$
ans=sum\times P(true)
$$
我们先假想一个新的节点 $n+1$ ，$n+1$ 号节点与剩下的 $n$ 个节点，构成一个环。那么每一个点其实是等价的，因为每个人是随机选择一个座位开始的。那么总数为：
$$
sum = (2\times(n+1))^m
$$
当一个方案不合法时，当且仅当第 $n+1$ 有人占据。那么因为每个人也是等价的，所以 $n+1$ 被占据的概率为：
$$
P(false) = \frac{m}{n+1} \Rightarrow P(true) = \frac{n+1-m}{n+1}
$$
$$
ans = sum\times P(true) = (2\times(n+1) )^m\times \frac{(n+1-m)}{n+1}
$$
那么代码就非常简单了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
#define LL long long 
LL fpow(LL a,LL b)
{
	LL x = 1;
	while(b)
	{
		if(1&b){
			(x*=a)%=mod;
		}
		(a=(a*a))%=mod;
		b = b>>1;
	}
	return x;
}
int n,m;
int main()
{
	cin>>n>>m;
	LL ans = fpow(2*n+2,m);
	cout<<(((ans)*(n+1-m)+mod)%mod*fpow(n+1,mod-2))%mod<<endl;
}
```
[地址](https://www.luogu.com.cn/blog/xzc/solution-cf838d)

---

## 作者：tommymio (赞：3)

通过将一个前后都可以走的模型转化到环上，并添加点 $n+1$ 判断非法情况。从前门进入对应为从点 $n+1$ 出发顺时针走，从后门进入对应为从点 $n+1$ 出发逆时针走。

**这一做法的正确性建立在环上的情况和题目中给出的情况一一映射。**

为什么 $n$ 个点就不可以呢？因为我们无法判断非法情况。为什么加了一个点就可以呢？因为这样可以判断从点 $n+1$ 顺时针 $/$ 逆时针出发走了一圈又回到 $n+1$ 的情况，在题目中对应的就是这个人没有找到位置。只要出现一个人找不到位置就是非法的，所以符合题意。

那么总情况数为 $(2\times(n+1))^m$，去掉不合法的占比 $\frac{m}{n+1}$，答案即为 $\frac{n+1-m}{n+1}\times(2\times(n+1))^m$。

代码非常短，我感觉贴了和没贴一样（雾

```cpp
//tommy 和 karry 贴贴（逃
#include<cstdio>
const int mod=1e9+7;
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline int pow(int x,int p) {int res=1;for(;p;p>>=1) {if(p&1) res=1ll*res*x%mod; x=x*1ll*x%mod;} return res;}
int main() {
    int n=read(),m=read();
    printf("%lld\n",(n+1-m)*1ll*pow(n+1,mod-2)%mod*1ll*pow(2*(n+1),m)%mod);
    return 0;
}
```

---

## 作者：KingPowers (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF838D)

考虑将这条长度为 $n$ 的链首尾相接，并新加一个 $n+1$ 号点，这样就变成了一个长度为 $n+1$ 的环。

环相对于链的好处就是它是对称的，并且我们不难发现原问题的不合法方案也就对应了这个环上第 $n+1$ 的点被占据的方案。

由于是环，每个点不被占的概率是相同的，也就是 $\frac{n+1-m}{n+1}$。$m$ 个人可以任选 $n+1$ 个位置以及左右方向，总方案数为 $2^m(n+1)^m$。将它们相乘即可得到答案。

```cpp
#define int long long
int n,m,ans; 
int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=(res*x)%mod;
		x=(x*x)%mod;y>>=1;
	}
	return res;
}
void Main(){
	cin>>n>>m;
	int p=(n+1-m)*qpow(n+1,mod-2)%mod;
	int cnt=qpow(2,m)*qpow(n+1,m)%mod;
	cout<<p*cnt%mod<<'\n';
}
```

---

## 作者：Fiendish (赞：2)

题目的解法非常巧妙，我们可以想到在一号座位和 $n$ 号座位之间放置一个座位，编号为 $n+1$，再将所有座位连接起来形成一个环。

显然，一个人往一个方向走，一共有 $(2(n+1))^m$ 种情况。而每个座位没有被占据的概率是 $\frac{n+1-m}{n+1}$，两者相乘，即为答案。

贴上丑陋的代码：
```cpp
#include<iostream>
#define int long long
using namespace std;
int n,m;
const int p=1e9+7;
int qpow(int a,int b){//快速幂
	int ans=1;
	for(;b>0;b>>=1,a=a*a%p)
		if(b&1) ans=ans*a%p;
	return ans;
}
int inv(int x){//求乘法逆元，用于取模
	return qpow(x,p-2);
}
signed main(){
	cin>>n>>m;
	cout<<(n+1-m)*inv(n+1)%p*qpow(2*(n+1),m)%p;
} 
```
若有疏漏、不详之处，恳请各位大佬指出。

---

## 作者：Underage_potato (赞：1)

## Solution

在编号为 $n$ 的座位后面新添加一个座位，将其编号为 $n+1$，然后将其与编号为 $1$ 的座位连起来，形成一个环。

比较显然的可以看出：

- 每个人从任意一个点向任意一个方向走的方案数有 $(2(n+1))^m$ 种。

- 而每个座位没有被人占的概率为 $\frac{n-m+1}{n+1} $。

然后将上面两者相乘就是答案。

记得取模！！！

## AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7; 
long long qpow(long long a,long long b){
	long long ans=1,base=a;
	while(b>0){
		if(b&1){
			ans*=base;
			ans%=MOD;
		}
		base*=base;
		base%=MOD;
		b>>=1;
	}
	return ans;
}
inline int read(){int x=0,w=1;char ch=0;while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}return x*w;}
signed main(){
	long long n=read(),m=read();
	printf("%lld",(n+1-m)*qpow(n+1,MOD-2)%MOD*qpow(2*(n+1),m)%MOD);
	return 0;
}
```


---

## 作者：FreedomKing (赞：0)

### 思路

考虑把一列座位看成一个长度为 $n$ 的环，其中编号 $n+1$ 的点为间隔点（不能被占据），每次每个人可以选一个起点逆时针或顺时针走到第一个空位上。如果编号为 $n+1$ 的点被人占据了显然不合法，否则肯定合法。

由于这是一个环，因此最终每个点没被占据的概率都是相同的。即一个点最终没被占据的概率是 $\frac{n+1-m}{n+1}$，乘以方案数 $2^m(n+1)^m$ 即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=1e9+7;
int a[N],n,m,t,k;
int power(int a,int b,int mod){ 
	int t=1;
	while(b>0){
		if(b%2==1) t=(t*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return t;
}
signed main(){
	cin>>n>>m;
	cout<<(((n+1-m)*power(n+1,mod-2,mod))%mod*(power(2*(n+1),m,mod)%mod))%mod;
	return 0;
}
```

---

## 作者：_ReClouds_ (赞：0)

[更好但或许会更卡的阅读体验](https://reclouds.github.io/post/%E3%80%90%E9%A2%98%E8%A7%A3%E3%80%91CF838D%20Airplane%20Arrangements%20%E9%A2%98%E8%A7%A3.html)

------

妙妙题。

首先进行一步转化：把前门和后门一起看作第 $n + 1$ 个座位，这样所有座位将会呈一个有 $n + 1$ 个节点的环。

我们考虑一种方式，将每一种原方案与每一种环上方案一一对应：把从前门进和从后门进分别转化为从环上的 $n + 1$ 号节点开始顺时针走和逆时针走，并将环上方案不合法的条件设为有人走到了 $n + 1$ 号节点上。那么，我们的任务也就转化为统计有多少环上方案使得没有人走到 $n + 1$ 号节点上。

然而这样转化还不能解决本题，因为环上方案暂时不存在比较优秀的性质。因此，我们还需加上一条限制：令 $n + 1$ 号节点同样为可供选择的位置。可以发现，加上这条限制后，不仅每一种原合法方案和每一种环上合法方案仍然能够一一对应，而且我们得到了一个十分优秀的性质：环上的每一个节点都是等价的。

于此本题的解法便呼之欲出了。我们不妨设每一个节点最终被走到的概率均为 $p$，那么由于被走到的节点总数为 $m$，若我们将其看做期望，则根据期望的线性性，有 $p \cdot (n+ 1) = m$，即 $p = \dfrac{m}{n +1}$，而概率 $p$ 反映的实际上就是不合法方案的占比，因此答案即为总方案数乘上 $1 - p$。总方案数并不难得出，为 $2^m \cdot (n+ 1)^m$。

综上所述，本题的答案即为 $\displaystyle \frac{n +1 - m}{n+ 1} \cdot 2^m \cdot (n+ 1)^m$。

---

## 作者：Chthologist7507 (赞：0)

按照 wzy 鸽鸽的说法好像是哪一年 PKU 集训的试机题？

神仙题。

考虑将飞机掰弯成 一个环，前后门为第 $n+1$ 个节点，从该节点出发顺时针/逆时针走，走到第 $n+1$ 个节点就是不合法的。

然后统计一下共有 $(2\times(n+1))^m$ 种情况，由于占据每一个点的概率相等，有 $\dfrac m{n+1}$ 的概率占领了 $n+1$ 号点，那么答案即 $\dfrac{n+1-m}{n+1}(2\times(n+1))^m$。

为什么是对的？正确的原因在于环上的每一个点和飞机的每一个座位一一对应，环上每一种走法和每一个乘客的选择一一对应。

[code](https://codeforces.com/contest/838/submission/166702760)

---

