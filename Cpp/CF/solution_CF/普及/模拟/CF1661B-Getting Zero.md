# Getting Zero

## 题目描述

Suppose you have an integer $ v $ . In one operation, you can:

- either set $ v = (v + 1) \bmod 32768 $
- or set $ v = (2 \cdot v) \bmod 32768 $ .

You are given $ n $ integers $ a_1, a_2, \dots, a_n $ . What is the minimum number of operations you need to make each $ a_i $ equal to $ 0 $ ?

## 说明/提示

Let's consider each $ a_i $ :

- $ a_1 = 19 $ . You can, firstly, increase it by one to get $ 20 $ and then multiply it by two $ 13 $ times. You'll get $ 0 $ in $ 1 + 13 = 14 $ steps.
- $ a_2 = 32764 $ . You can increase it by one $ 4 $ times: $ 32764 \rightarrow 32765 \rightarrow 32766 \rightarrow 32767 \rightarrow 0 $ .
- $ a_3 = 10240 $ . You can multiply it by two $ 4 $ times: $ 10240 \rightarrow 20480 \rightarrow 8192 \rightarrow 16384 \rightarrow 0 $ .
- $ a_4 = 49 $ . You can multiply it by two $ 15 $ times.

## 样例 #1

### 输入

```
4
19 32764 10240 49```

### 输出

```
14 4 4 15```

# 题解

## 作者：Exber (赞：6)

## 做法

贪心。

注意到题目的本质是让操作之后的 $a_i$ 二进制中后 $15$ 位都为 $0$（因为 $32768=2^{15}$）。

考虑只进行乘 $2$（左移）操作时的答案。显然，我们记二进制字符串中最靠右（位权最低）的 $1$ 的位置为 $pos$，那么答案就是 $15-pos$，因为左移那么多次就可以让后 $15$ 位都为 $0$。特别的，如果 $pos>15$ 即后 $15$ 位已经 $0$ 那么答案就为 $0$。

接下来考虑加法。加法的意义在于进位，因为遇到连续的 $1$ 加法就是性价比最高的操作。加法肯定在左移之前进行，因为左移之后所有的 $1$ 距离最低位都更加“远”了。加法的次数一定在 $15$ 次以内，因为左移 $15$ 次就已经满足条件了。

所以先枚举加法的次数，再求出左移的次数相加取最小值即可。

## AC 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <cstring>

using namespace std;

struct node
{
};

int n;

inline int calc(int x)
{
	int pos=15;
	for(int i=0;i<=15;i++)
	{
		if(x&(1<<i))
		{
			pos=i;
			break;
		}
	}
	return 15-pos;
}

inline void slove()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		int ans=1e8;
		for(int j=0;j<=15;j++)
		{
			ans=min(ans,j+calc((x+j)%32768)); 
		}
		printf("%d ",ans);
	}
}

int main()
{
	int _=1;
//	scanf("%d",&_);
	while(_--)
	{
		slove();
	}
	return 0;
}
```

---

## 作者：Pig_py (赞：5)

首先我们知道有 $1\le a_{i}\le 32768$ 并且你需要通过让 $a_{i}$ 增加再对 $32768$ 取模让它变成零，不难想到如果这个数小于 $32768$ 肯定是不行的。并且，顺序一定是先加后乘，这样才能让它尽可能大。

另外，我们知道 $2^{15}$ 就是 $32768$ 本身，所以答案超过 $15$ 是不可能的。既然如此，我们就分别枚举加和乘的数量就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	scanf("%d",&n);
	int a[32780];
	int powm[25];
	powm[15]=32768;
	for(int i=14;i>=0;i--)powm[i]=powm[i+1]/2;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		int ans=15;
		for(int j=0;j<=15;j++){//枚举加 
			for(int k=0;k<=15-j;k++){//枚举乘二 
				if(((a[i]+j)*powm[k])%32768==0){
					ans=min(ans,j+k);
					break;
				}
			}
		}
		printf("%d ",ans);
	}
	return 0;
}    
```


---

## 作者：Cappuccino_mjj (赞：1)

不知道为什么，看到这道题就直接想用广搜来做，然后神奇地过了！

---

## [题目传送门](https://www.luogu.com.cn/problem/CF1661B)

题目意思：

给你 $n$ 个数 $v$，你可以对它进行两种操作：将 $v$ 变成 $(v + 1) \% 32768$ 或者 $2\times v\%32768$，求将 $v$ 变成 $0$ 需要的最少的操作数。

---

思路：
1. 首先我们发现 $n$ 和 $v$ 最大只有 $32768$，所以广搜时间不会爆。
2. 于是我们用广搜将一个数的所有情况枚举并取变成 $0$ 的最少操作数即可。

---

代码：
```cpp
#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
struct node
{
	int x;
	int s;
};
int bfs(int x)
{
	int vis[50000];//标记当前状态是否遇过
	memset(vis,0,sizeof vis);
	queue<node>q;
	q.push(node{x,0});
	vis[x]=1;
	if(x==0)return 0;//如果是0直接返回0步
	while(!q.empty())
	{
		node t=q.front();
		q.pop();
		if(((t.x+1)%32768==0)||((2*t.x)%32768==0))
			return t.s+1;//变成0了就输出步数
		if(!vis[(t.x+1)%32768])
		{//第一种操作
			q.push(node{(t.x+1)%32768,t.s+1});
			vis[(t.x+1)%32768]=1;
		}
		if(!vis[(2*t.x)%32768])
		{//第二种操作
			q.push(node{(2*t.x)%32768,t.s+1});
			vis[(2*t.x)%32768]=1;
		}
	}
	return -1;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1,x;i<=n;i++)
	{
		cin>>x;
		cout<<bfs(x)<<" ";
	}
	return 0;
}
```

---

完美撒花~

---

## 作者：yanhao40340 (赞：1)

### 题意
给定 $n$ 个数，对于一个数 $v$，你有两种操作使它变为 $0$：

- $v \gets (v+1)\bmod 32768$
- $v \gets (2 \times v)\bmod 32768$

输出每一个数变为 $0$ 的最小操作数。
### 分析
~~显而易见，~~ $32768$ 是 $2^{15}$。所以，这道题我们可以从因子 $2$ 的数量来考虑。由于 $2^{15}|v$ 是 $v \equiv 0\pmod{32768}$ 的充分必要条件，所以这道题就变成了用两种操作使一个数的因子 $2$ 的数量达到 $15$ 个。

先考虑操作 $2$，显而易见，使用一次就可以增加一个因数 $2$。所以不论什么数字，它的最小操作数一定小于等于 $15$。

再考虑操作 $1$，只有当用操作 $1$ 可以更快的增长 $v$ 的因子 $2$ 的数量时才会用它，那么考虑打表。预处理出每一个小于 $32768$ 的数的因子 $2$ 的数量，然后相对于 $v$ 将增加的因子 $2$ 的数量与只用操作二达到此数量的次数进行比较。如果操作 $1$ 的操作次数更少，那么使用操作 $1$。

由于最小操作数不大于 $15$，所以枚举操作 $1$ 时只用枚举 $15$ 次即可。

码量不大，而且时间复杂度约为 $O(n)$，可以通过。
### 代码
```cpp
#include <iostream>
#include <cmath>
using namespace std;
const int mod=32768;
int a[mod+20];
void ready(){
	a[0]=15;
	for (int i=1;i<mod+20;++i)
		a[i]=log2(i&(-i));//用于计算a[i]含有因子2的数量
	return;
}
int main(){
	ready();
	int t,n;scanf("%d",&t);
	while (t--){
		scanf("%d",&n);n%=mod;//记得取模，WA了四发
		int f1=0,f2=0;
		for (int i=1;i<=15;++i)//枚举操作1的次数
			if (a[i+n]-i>a[f1+n]-f1) f1=i;
		f2=15-a[n+f1];//还差的因子2的数量用操作2补齐
		printf("%d ",f1+f2);//不是换行
	}
	putchar('\n');
	return 0;
} 
```

---

## 作者：Rnfmabj (赞：1)

做题背景：拉了。大概是全场唯一一个 B 吃罚时的人。



------------

## 题意

给定 $n$ 个不大于 $32768$ 的正整数，对于每个正整数，有两个操作：

- 操作 $A$ ：使正整数 $x$ 变为 $x+1$ 。

- 操作 $B$ ：使正整数 $x$ 变为 $2x$ 。

对每个正整数 $x$ ，求操作次数最少的方案，使得 $x \equiv 0(mod 32768)$ 。

要求回答操作次数。

$n \leq 32768$ 。


## 思路

察觉：$32768=2^{15}$ 。

两个简单的事实：

1. 最多只会有 $32768$ 个不同的正整数 ~~废话~~

1. 答案最大为 $15$ 。

理由很简单，因为任意一个正整数一定能通过 $15$ 次 $B$ 操作变为 $32768$ 的倍数。 ~~你都乘上了一个32768了你还能不是它倍数？？？~~

而一个 $2$ 的整数次幂的最少操作次数必然是 $15-k$ ,其中 $k$ 为 $2$ 的幂 。

接着这么想：相对于一个奇数而言，一个为 $2$ 的倍数的整数能省掉 $1$ 次 $B$ 操作，为 $4$ 的倍数的整数能省掉 $2$ 次 $B$ 操作，为 $8$ 的倍数的整数能省掉 $3$ 次 $B$ 操作 ……

而这样的整数也能通过操作 $A$ “ 造福 ” 其前面的数：如果 $x$ 能 “ 省 ” 下 $2$ 次操作，那么 $x-1$ 就能通过一次 $A$ 操作变为 $x$ ,使 $x-1$ 也减少 $(2-1)$ 次操作，诸如此类。

那么这个过程我们就可以通过一个简单的筛子实现：$2^0$ 有 $15$ 次（初始化）， $2^1$ 有 $14$ 次，然后造福一下前一个数，$2^2$ 有 $13$ 次，然后造福一下前两个数……

~~然后我们就能成功打表过题了~~

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define R read()
#define file(a) freopen(#a".in","r",stdin),freopen(#a".out","w",stdout)
using namespace std;
inline ll read() {
	ll s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
inline void write(ll x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10),x%=10;
	putchar('0'+x);
}//Don't use it for CF.
inline void wk(ll x){write(x);putchar(' ');}
inline void we(ll x){write(x);putchar('\n');}
ll f[40000];//随便开的4e4
void work(){
	for(ll i=1;i<=32768;i++)f[i]=15;//初始化：全是15次
	for(ll i=1;i<=15;i++){
		ll x=1;
		for(ll j=1;j<=i;j++)x<<=1;//x变为2的i次幂
		for(ll j=1;j*x<=32768;j++){//枚举x的整数倍，优化该正整数的操作数
			f[j*x]--;
			for(ll k=1;k<=i;k++)f[j*x-k]=min(f[j*x]+k,f[j*x-k]);//造福前人
		}
	}
}
signed main(){
	work();//预处理打表
	ll n=R;
	for(ll i=1;i<=n;i++){
		ll x=R;
		wk(f[x]);//直接回答
	}
	return 0;
}
```




------------

题外话：

我：按理来说 B 的任何一个通过代码都不可能被叉，因为 $sub2$ 的 $T=32768$ ，涵盖了所有情况，即使是故意的也没法动手脚吧？

KemononeRou ：其实是可以的（比如写个 

```cpp
if(T == 114 + 514) return 0;
```


（清脆的打脸声）

---

## 作者：yeshubo_qwq (赞：0)

题外话：我们老师把 $a_i=32768$ 时的输出造成了 $0$……

思路：

先用 bfs 预处理出所有 $a_i$ 的答案 ~~（当然直接打表也很好）~~，然后每次 $O\left(1\right)$ 回答即可。

显然，最后的答案是 $0$，我们可以通过 bfs 倒推预处理出所有 $a_i$ 的答案。

我们只需要考虑对于一个数 $x$ 而言，有哪些情况会得到它。

+ $\left(y\times2 \right) \pmod {32768}$ 取模没有影响 $y\times2$ 的值。

+ $\left(y\times2 \right) \pmod {32768}$ 取模影响了 $y\times2$ 的值，使其变小。

+ 以及 $\left(y+1 \right) \pmod {32768}$。

注意：bfs 预处理时不会处理出 $32768$ 的答案，因此要单独赋值 $1$。

$1$ 是这样得到的：$\left(32768 \times 2\right) \pmod {32768}=0$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int v[33000],s[33000],x,y,T;
queue <int> q;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	v[0]=1;q.push(0);
	while (!q.empty()){
		x=q.front();q.pop();
		y=x/2;
		if (x%2==0&&!v[y])//判断 x%2==0 防止 x 是奇数导致答案错误
			s[y]=s[x]+1,v[y]=1,q.push(y);
		y=(x+32768)/2;
		if ((x+32768)%2==0&&!v[y])//同上 
			s[y]=s[x]+1,v[y]=1,q.push(y);
		y=(x==0?32767:x-1);
		if (!v[y])
			s[y]=s[x]+1,v[y]=1,q.push(y);
	}
	s[32768]=1;
	cin>>T;while (T--) cin>>x,cout<<s[x]<<' ';
	return 0;
}
```


---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1661B)

## 题意

对于一个整数 $v(0\le v <32768)$，可以进行如下操作之一改变 $v$ 的值无限次：

- $v\Leftarrow (v+1)\bmod 32768$。
- $v\Leftarrow (2\times v)\bmod 32768$。

记 $d_v$ 为整数 $v$ 被改变至 $0$ 的最小次数，给出一个 $n$ 个数的数列 $a_{1\sim n}(0\le a_i <32768)$，求出所有的 $d_{a_i}$。

## 分析

先把所有的 $d_v$ 预处理出来，再处理询问。

显然将 $v$ 改为 $0$ 的最小次数就是将 $0$ 改为 $v$ 的最小次数，所以操作是可以反着来的，又有 $d_0=0$，因此我们把每个数 $v$ 想象成顶点，根据操作来连边，我们可以通过求反图的最短路来求出所有的 $d_v$，一个 $\text{bfs}$ 就可以实现。

那么应该如何连反边呢，假设我们已经求出了 $d_v$，那么在原图上它可以由以下三个数得到：

- $(v-1+32768)\bmod32768$。
- $(v\div2)\bmod32768\ (v\pmod 2=0)$。
- $((v+32768)\div2)\bmod32768\ (v\pmod 2=0)$。

因此在 $\text{bfs}$ 中判断这些数是否被更新了，如果没被更新过就更新并加入队列。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=4e4+10;
int n,m=32768,a[N],d[N];
queue<int>q;
int main(){
	for(int i=1;i<m;i++)
		d[i]=-1;
	d[0]=0;
	q.push(0);
	while(q.size()){
		int x=q.front();
		q.pop();
		if(d[(x-1+m)%m]==-1){
			d[(x-1+m)%m]=d[x]+1;
			q.push((x-1+m)%m);
		}
		if(x%2==0&&d[x/2]==-1){
			d[x/2]=d[x]+1;
			q.push(x/2);
		}
		if(x%2==0&&d[(x+m)/2]==-1){
			d[(x+m)/2]=d[x]+1;
			q.push((x+m)/2);
		}
	}
	n=read();
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cout<<d[a[i]]<<" ";
	return 0;
}
```


---

## 作者：StayAlone (赞：0)

赛时一遍过，思路比较清新，不是 bfs 或 dp，$O(n\log n)$。

### 题意 

给定 $n$ 个数 $x$，每次可以对它进行两种操作的其中之一：
1. $x = 2x \bmod 32768$
2. $x = (x + 1)\bmod 32768$  

对于每一个 $x$，求最小操作次数，使得 $x = 0$。  

### 思路  

注意到 $32768 = 2^{15}$ 比较小，思路也可以往 $2$ 次幂上靠。  

对于每一个 $i\in[0, 15]$，我们可以找到一个最小的 $t$，使得 $t \times 2^i \geqslant x$，此时目标就是 $32768t$。令 $p = t \times 2^i$，所需要的步数是 $p - x + 15 - i$。这个应该比较好理解，就是让 $x$ 先加到 $p$，再让它操作 $15 - i$ 次 $1$，变成 $32768p$。  

求每一次的 $t$ 也很简单，随便除一下就能得到。

所以答案就是 $\min\limits_{i\in[0, 15]}{p - x + 15 - i}$。  

[AC code 记录](https://codeforces.com/contest/1661/submission/153176337)  

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rep2(i, l, r) for (int i = l; i >= int(r); --i)
#define cop(i, l, r, a, b) rep1(i, l, r) a[i] = b[i]
#define rep(i, x) for (int i = pnt[x]; i; i = nxt[i])
#define rer(i, l, r, a) rep1(i, l, r) read(a[i])
#define rew(i, l, r, a, ch) rep1(i, l, r) write(a[i], ch)
#define ptc putchar
#define il inline
#define rout return 0
using namespace std;
const int MAXN = 1e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
// ..... 奇妙缺省源
using namespace stupid_lrc;
int n, cnt, a[MAXN];
const int p = log2(32768);

il int gans(int x) {
	int ans = INF;
	rep1(i, 0, p) {
		int t = x / (1 << i) + bool(x % (1 << i));
		int now = t * (1 << i);
		ans = my_min(ans, now - x + p - i);
	}
	return ans;
}

int main() {
	read(n); rer(i, 1, n, a);
	rep1(i, 1, n) write(gans(a[i]), ' ');
	rout;
}
```

---

