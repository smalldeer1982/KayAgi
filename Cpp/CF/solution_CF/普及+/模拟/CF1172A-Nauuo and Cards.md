# Nauuo and Cards

## 题目描述

Nauuo is a girl who loves playing cards.

One day she was playing cards but found that the cards were mixed with some empty ones.

There are $ n $ cards numbered from $ 1 $ to $ n $ , and they were mixed with another $ n $ empty cards. She piled up the $ 2n $ cards and drew $ n $ of them. The $ n $ cards in Nauuo's hands are given. The remaining $ n $ cards in the pile are also given in the order from top to bottom.

In one operation she can choose a card in her hands and play it — put it at the bottom of the pile, then draw the top card from the pile.

Nauuo wants to make the $ n $ numbered cards piled up in increasing order (the $ i $ -th card in the pile from top to bottom is the card $ i $ ) as quickly as possible. Can you tell her the minimum number of operations?

## 说明/提示

Example 1

We can play the card $ 2 $ and draw the card $ 3 $ in the first operation. After that, we have $ [0,3,0] $ in hands and the cards in the pile are $ [0,1,2] $ from top to bottom.

Then, we play the card $ 3 $ in the second operation. The cards in the pile are $ [1,2,3] $ , in which the cards are piled up in increasing order.

Example 2

Play an empty card and draw the card $ 1 $ , then play $ 1 $ , $ 2 $ , $ 3 $ in order.

## 样例 #1

### 输入

```
3
0 2 0
3 0 1
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
0 2 0
1 0 3
```

### 输出

```
4```

## 样例 #3

### 输入

```
11
0 0 0 5 0 0 0 4 0 0 11
9 2 6 0 8 1 7 0 3 0 10
```

### 输出

```
18```

# 题解

## 作者：VenusM1nT (赞：13)

```
我喜欢 2C/1A (cards)。很考验代码细心能力，是一道好题。
 - By Sooke
```

结论题。

考虑使用 $0$ 牌和不使用 $0$ 牌，如果必须使用 $0$ 牌，那么最好的办法就是把所有数字牌拿到手中，再按顺序摆回去，这样的操作次数是 $\max(pos[i]-i+n+1)$，否则次数为第一个 $pos[i]≥i$ 的 $pos[i]-i$。

```cpp
#include<bits/stdc++.h>
#define MAXN 200005
#define inf 1919810
#define reg register
#define inl inline
using namespace std;
int n,a[MAXN],b[MAXN],pos[MAXN],ans,Ans=inf;
int main()
{
	scanf("%d",&n);
	for(reg int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(reg int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		pos[b[i]]=i;
	}
	for(reg int i=1;i<=n;i++) ans=max(ans,pos[i]-i+n+1);
	for(reg int i=1;i<=n;i++)
	{
		if(pos[i]>=i)
		{
			Ans=pos[i]-i;
			break;
		}
	}
	for(reg int i=1;i<=n;i++)
	{
		if((pos[i]<i && Ans<pos[i]-i+n+1) || (pos[i]>=i && Ans!=pos[i]-i))
		{
			Ans=inf;
			break;
		}
	}
	printf("%d\n",Ans==inf?ans:Ans);
	return 0;
}
```

---

## 作者：include13_fAKe (赞：5)

## 前言
这个国庆，老师给我们布置了很多题，有些还有些难（老师说都是普及组赛前的训练题，他说，我们现在做的题比普及组难一些，到时候考试就觉得题目简单了，没想到，那里面还有**一黑两紫**）。这是其中一道。老师还跟我们说，一定不要看题解，我也严格照做了。

没想到最后我还能独立地把这个题做出来（估计这个题是其中最简单的吧。但我用了近 $2$ 个小时，如果我在当时能够准时参加比赛，整场比赛的时间也只够我想这一个题了，我真是太逊了），写篇题解纪念吧。
## 题意
给定两摞牌，每一摞有 $n$ 张。每张上面都写有一个数。

在这 $2n$ 张牌上的 $2n$ 个数中，有 $n$ 个为 $0$，还有 $n$ 个分别为 $1\sim n$。

可以进行以下操作若干次：

- 在第一摞里任选一张牌放到第二摞的最下面，然后将第二摞牌最上面的牌放到第一摞中。

例如，原本第二摞从上到下分别是 $3,0,7,0,0,1,4$，现在要把一张写有 $2$ 的牌放进来，第二摞变成 $0,7,0,0,1,4,2$。 

问至少要进行多少次操作，才能使得第二摞从上到下分别为 $1\sim n$。
## 思路
首先可以确定一点的是，**最后 $\bm n$ 步，必然是写有数字 $\bm{1\sim n}$ 的 $\bm n$ 张牌依次放入第二摞的末尾**（**可能没有 $\bm n$ 步，则每一步都是这样的操作，但不是从写有 $\bm 1$ 的牌开始**。样例一就是这样的）。

**可以首先排除掉样例一这种情况。**

但是如果把样例一改成
```cpp
3
0 0 2
0 3 1
```
则我们在放牌的时候，放完了 $2$，会发现 $3$ 在第二摞当中，无法放到第二摞的末尾。所以此时需要用 $3$ 步把 $3$ 和 $1$ 放到第一摞，然后重新开始放，一共需要 $3+3=6$ 步。这就**不是**我们要排除的情况。

但是如果是
```cpp
7
0 0 5 0 0 0 0
6 7 0 1 2 3 4
```
的话，可以先把 $5$ 放进去，然后放 $6$ 和 $7$。

为什么这个时候可以呢？**因为我们在放 $\bm 5$ 的时候，$\bm 6$ 已经在第一摞里面了**（原因之前讲过）**。同样，我们在放 $\bm 6$ 的时候，$\bm 7$ 已经在第一摞里面了。**

我们可以检测每一个在第二摞的上面的数**能不能及时进入第一摞**（进入的方式及原因之前讲过）。如果都可以，就**是**我们要排除的情况。

在这组输入中，$6$ 需要第二个放入，就需要在 $1$ 步以内进入第一摞。实际上，因为 $6$ 在第二摞的第一个位置，所以可以在第 $1$ 步进入第一摞，符合要求。

然后考虑其他情况。

可以明确的是，**首先要将一些第二摞里的牌放入第一摞**。

可以算一下**至少要放多少张牌进第一摞**。但要注意刚刚讲到的那种情况。

以样例三为例，要先放 $7$ 张牌进第一摞，然后再按照 $1\sim n$ 的顺序将牌放入第二摞。**注意在 $\bm{1,2}$ 放入第二摞以后，$\bm 3$ 被放进了第一摞。** 总共 $7+11=18$ 次操作。

据说还可以用二分，但不如我的这种做法简单。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[2*114514];
int b[2*114514];
int solve(){
	int x=b[n];
	for(int i=n;i>=1;i--){
		if(b[i]!=b[n]-(n-i))	return -1;
		if(b[i]==1)	break;
	}
	for(int i=1;i<=n-b[n];i++){
		if(b[i]<=i+b[n]&&b[i]!=0)	return -1;
	}
	return b[n];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
	}
	int e=solve();
//	cout<<e<<endl;
	if(e!=-1){
		printf("%d\n",n-e);
		return 0;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(b[i]!=0){
			ans=max(ans,i-b[i]+1);
		}
	}
	printf("%d\n",ans+n);
	return 0;
}
```
若有没讲到的，请自行理解。

---

## 作者：Fading (赞：5)

原来是一道结论题...

我想了一个乱搞贪心写了$30$分钟...

------------

### 结论$1$

此问题一定有解，且解的上界为$O(n)$级别。

证明很简单吧，直接收完所有牌并打出所有$0$，然后再按序打出$1\sim n$的所有牌。

### 结论$2$

最优解一定是在一个时间点，按序打出$k\sim n$的所有牌。

证明很显然。

### 结论$3$

在手上有$0$，且堆底不是$1\sim i$的情况下，打出$(i+1)\sim n$的牌来换取堆顶牌不是最优的。

证明很显然。

### 收牌

我们定义一个收牌操作，就是把$0$放入堆底，把堆顶取出来放在手上。

显然如果你的手上全部都是$1\sim n$，就无法收牌。但是这种情况我们不考虑，因为如果这种情况发生，最优解就是直接打出所有牌的方案。

------------

接下来我们分两种情况讨论：

### 第一种

手上的牌可以直接按序打出成为$1\sim n$(样例$1$)

而且一定是这样子的：

```......1,2,3...i-1,i```

底部连续。

手上有$i+1$,且可以依次打出$(i+1)\sim n$（可以打完一张后从堆顶取出新牌）

### 第二种

非第一种情况。

怎么解决呢？

有一种思路，就是找到$1$（若手牌有$1$就不找了），收入手中，然后按序打出$1\sim n$的所有牌。但是前提是$1\sim n$的牌可以在打出的时候存在。

所以我们要继续收牌，找一个合适的时候打出$1$，然后再按序打出所有牌成为$1\sim n$

怎么找到最合适的时机呢？

我们先把去掉$1$的堆状态处理出来，设为$b$数组。

$b_1$为堆顶，$b_n$为堆底。

枚举$i$，如果$b_i>0$且$b_i<i+1$，那么按序收牌的时候一定打不出这张牌（轮到这个牌的时候手上没有）

所以一定要再收$i-b_i+1$次牌，保证打出$b_i-1$后一定可以继续打出$b_i$

可以画画图理解一下。

根据上述的结论，这样贪心是对的。

所以最优解就是直接取一个最大值，然后按序打出。

### 正解

第一种显然更优但是可能无解，而第二种是一定有解的。

所以特判一下就好了。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
ll tot,x,n,m,pos[1000001],b[1000001];
signed main(){
    n=read();
    for (int i=1;i<=n;i++) x=read();
    for (int i=1;i<=n;i++){
        b[i]=read();
        if (b[i]) pos[b[i]]=i;
    }
    bool flag=(pos[1]?0:1);
    int now=n-pos[1]+1;
    for (int i=1;i<=pos[1]-1;i++){
        if (flag) break;
        if (b[i]&&b[i]-(i+now)<=0) flag=1;
    }
    for (int i=pos[1]+1;i<=n;i++){
        if (flag) break;
        if (b[i]!=i-pos[1]+1) flag=1;
    }
    if (!flag){//第一种
        cout<<n-now;return 0;
    }
    int dep1=0;//找到1的步数
    if (!pos[1]) dep1=pos[1];
    for (int i=1;i<=n;i++) b[i]=b[i+dep1];
    int dep2=0;//再收几次牌后打出1
    for (int i=1;i<=n;i++){
        if (b[i]&&b[i]<i+1) dep2=max(1LL*dep2,i-b[i]+1);
    }
    cout<<n+dep1+dep2;
    return 0;
}
```

---

## 作者：ouuan (赞：3)

首先尝试不打空白牌能否直接完成。如果能就是最优解，否则最优解一定是先打若干空白牌然后再也不打空白牌。计 $p_i$ 为 $i$ 在牌堆的初始位置（初始在手上为 $0$），那么答案为 $\max\limits_{i = 1}^n(p_i - i + 1 + n)$（每张牌最早在第 $p_i + 1$ 张被打出，还要打 $n-i$ 张）。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 200010;

int n, a[N], b[N], p[N], ans;

int main()
{
    int i, j;

    scanf("%d", &n);

    for (i = 1; i <= n; ++i)
    {
        scanf("%d", a + i);
        p[a[i]] = 0;
    }

    for (i = 1; i <= n; ++i)
    {
        scanf("%d", b + i);
        p[b[i]] = i;
    }

    if (p[1])
    {
        for (i = 2; p[i] == p[1] + i - 1; ++i);
        if (p[i - 1] == n)
        {
            for (j = i; j <= n && p[j] <= j - i; ++j);
            if (j > n)
            {
                printf("%d", n - i + 1);
                return 0;
            }
        }
    }

    for (i = 1; i <= n; ++i) ans = max(ans, p[i] - i + 1 + n);

    printf("%d", ans);

    return 0;
}
```

---

## 作者：Day_Tao (赞：2)

## CF1172A

### 题意

有 $2n$ 张牌，其中 $n$ 张是标有 $1$ 到 $n$ 的牌，$n$ 张是 $0$ 牌，你手中有 $n$ 张，牌堆里有 $n$ 张。现在可以进行操作：向牌底插入你手中的一张牌，再在牌顶拿走一张牌。求让牌堆从上到下顺序变成 $1 \cdots n$ 需要的最小操作次数。

### 分析

这是道分类讨论的结论题。容易发现可以分为这两种情况：

- 在牌堆中的最后已经有了 $1,2,3,\cdots ,m-1,m$ 的序列，长度为 $m$ 。

  这样就有可能可以可以直接完成。设 $1$ 的位置为 $k$，操作次数就是 $n-k$。但是不难发现这种方法很容易被卡掉，如果手中没有所需要的下一张牌，那么就需要进行另一种分类讨论了。这个可以并到第二种情况里。

- 除了第一种情况的所有情况。

   这些情况可以统一处理。可以分为以下几种情况：
   - 第一种情况给卡下来的。
   
   - $1$ 号牌在牌堆中但是并不满足 $1$ 的条件。
   
   - $1$ 号牌在手中。
   
   这几个情况都是需要将 $1$ 号牌拿到手中，最后再一次性打出 $1$ 到 $n$ 的牌。那如何判断能否一次性打出呢？这里我给出一组样例：
   ```cpp
   10
   0 0 5 0 7 0 0 6 1 4
   0 2 3 0 0 5 0 8 10 0
   ```
   如果这时将 $1$ 号牌打出，那么会得到一张 $0$，然后会发现手上并没有 $2$ 号牌。那么也无法达成题目要求了。所以可以选择先打出一张 $0$，然后拿到牌顶的 $0$，再打出一张 $0$，就能拿到 $2$ 号牌了。以此类推。当然，不用担心没有 $0$ 可以打了，因为 $0$ 一共有 $n$ 张，最坏情况就是手中全是非 $0$，牌堆中全是 $0$。最后可以发现，**当第 $i$ 张牌的序号小于等于 $i$ 时，这张牌之前的所有牌必须先给拿走**。设这样操作了 $k$ 次，那么加上后面打出 $1$ 到 $n$ 张牌，就是 $n+k$ 次操作。
   
在这时，你可以发现似乎你自己手中的牌，也就是 $a$ 数组没啥用……
### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pqg priority_queue<int,vector<int>,greater<int>>
#define pql priority_queue<int,vector<int>,less<int>>
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define scnaf scanf
#define rt register int
#define int long long
const int MAX = 2e5+5;
int n,a[MAX],b[MAX],k;
bool f;
inline void solve2() {      //第二种情况
	int k=0;
	for(int i=1; i<=n; i++)
		if(b[i]!=0&&b[i]<=i)
			k=max(k,i-b[i]+1);      //使第i张牌移到能取的最大位置所需的操作次数
	printf("%lld",n+k);
}
inline void solve1() {     //1号牌在牌堆里的情况
	for(int i=1; i<k; i++)
		if(b[i]!=0&&b[i]<=i+n-k+1) {
			solve2();      //被卡掉
			return ;
		}
	for(int i=k+1; i<=n; i++)
		if(b[i-1]+1!=b[i]) {
			solve2();     //不满足1之后的数字逐个＋1递增
			return ;
		}
	printf("%lld",k-1);   //都满足则输出
}
signed main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%lld",&n);
	for(int i=1; i<=n; i++)
		scanf("%lld",&a[i]);
	for(int i=1; i<=n; i++) {
		scanf("%lld",&b[i]);
		if(b[i]==1)
			k=i;   //记录1号牌的位置
	}
	if(k!=0)
		solve1();
	else
		solve2();
	return 0;
}
```

### END

---

## 作者：zrzluck99 (赞：2)

这 CF #div.2 的第三题我调了一个多小时 ~~（然而比赛时还是没有调出来）~~

orz那些秒过这题的大佬

首先看着这玩意像队列，我就开了个队列QAQ

很显然操作次数最大不超过 $2n$ （把所有卡片拿走再放回去也就 $2n$ 次），经过一番~~瞎搞~~思考，我们发现可以分成操作次数 $\le n$ 与 $\gt n$ 两种情况讨论。

考虑 $\le n$ 的情况：

e.g.

```
0 4 5 0 6 0 0 0 8
7 0 9 0 0 0 1 2 3  <--our queue
```

要想 $\le n$ ，也就要满足没有一次操作放的是 $0$ 。由于卡片 $1$ 肯定不能动，$1$ 以后的数字也肯定不能动，这就要求 $1$ 以后的数字已经排好。而卡片 $1$ 之前的数字，判断一遍能否保证每次都能取到下一张卡片就行了。

对于 $\gt n$ 的情况，只需要跑一遍队列模拟即可。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// 快速I/O一家

ll read(){
    ll s=0,w=1; char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') w=-1; ch=getchar();}
    while (ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0', ch=getchar();
    return s*w;
}

void write(ll s){
    if (s<0) putchar('-'), s=-s;
    if (s>9) write(s/10);
    putchar(s%10+'0');
}

void writeln(ll s){
    write(s); putchar('\n');
}

void writeln(){
    putchar('\n');
}

struct Queue{   // 搞个大队列
    ll a[10000001],l,r;
    Queue(){
        memset(a,0,sizeof(a)); l = r = 0;
    }
    void push(ll x){
        a[r++] = x;
    }
    void pop(){
        l++;
    }
    ll front(){
        return a[l];
    }
    ll tail(){
        return a[r-1];
    }
    bool empty(){
        return l==r;
    }
    void clear(){
        l = r = 0;
    }
    ll check(){   // 这里是判断<=n次的
        ll t = l; while (a[t]!=1&&t<r) t++;   // 找卡片1
        for (int i=t+1;i<r;i++) if (a[i]-a[i-1]!=1) return -1;   // 卡片1后必须有序
        for (int i=0;i<t;i++) if (a[i]<r-t+i-l+2&&a[i]!=0) return -1;   // 判断卡片1前是否所有卡片都能取到
        return t-l;  //如果可以则返回
    }
}q;

bool vis[10000001];

int main(){   // 主程序
    ios::sync_with_stdio(false);
    ll n = read();
    for (int i=1;i<=n;i++) {ll x = read(); if (x) vis[x] = 1;}
    for (int i=1;i<=n;i++) {ll x = read(); q.push(x);}  //push进队列
    ll tmp = q.check();
    if (tmp!=-1) {writeln(tmp); exit(0);}  //判断<=n的情况
    ll ans = 0;
    for (int i=1;i<=n;i++){  //模拟队列
        while (!vis[i]) {if (q.front()) vis[q.front()] = 1; q.pop(); q.push(0); ans++;}
        if (q.front()) vis[q.front()] = 1; q.pop(); vis[i] = 0; q.push(i); ans++;
    }
    writeln(ans);
    return 0;
}
```

---

## 作者：Frozencode (赞：1)

这里用的是二分的思路，二分**打多少张空牌后**打出$1$，值得注意的是有些情况下不打空牌也能符合要求，这就要求我们在前面先检验下这个情况。细节见注释:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=500010;
const ll INF=2147483647;
ll n,a[maxn],b[maxn],l,r,tem,pd=0;
vector<ll> e;
bool vis[maxn];
bool check(ll x)//x即打出x张空牌，check函数用模拟来检验答案的可行性。
{
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)vis[a[i]]=1;
	for(int i=1;i<=x;i++)vis[b[i]]=1;
	for(int i=1;i<=n;i++)//i为当前打序号为i的牌
	{
		if(x+i>n)return true;//x+i>n说明已经把原先牌堆里的牌都抽上来了，所以是肯定可行的。
		if(!vis[i])return false;//如果该打这张牌的时候没抽上手那就不行。
		vis[b[i+x]]=1;//标记新抽的牌。
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)
	{
		e.push_back(b[i]);
		if(a[i])pd=1;
		vis[a[i]]=1;
	}
	if(pd)//下面的程序模拟了不打空牌的情况。
	{
		for(int i=1;i<=n;i++)
		{
			if(vis[i])
			{
				tem=i;//tem为手上有的序号最小的牌。
				break;
			}
		}
		for(int i=tem;i<=n;i++)
		{
			if(!vis[i])//检验手上是否有序号为i的牌
			{
				pd=0;
				break;
			}
			vis[b[i-tem+1]]=1;
			e.push_back(i);//这里的e用来模拟出完牌之后的牌堆。
		}
	}
	if(pd)
	{
		for(int i=n-tem+2;i<e.size();i++)//如果牌能够顺利打出，那么检验牌库是否单调，因为前n-tem+1张牌已经被我们抽上来了，所以现在堆顶的第一张牌是第n-tem+2张。
		{
			if(e[i]!=e[i-1]+1)//不单调就不行。
			{
				pd=0;
				break;
			}
		}
		if(pd)
		{
			cout<<n-tem+1;
			return 0;
		}
	}
	pd=0;//下面这段用来特判不打牌就可行的情况...
	for(int i=1;i<n;i++)
	{
		if(b[i]+1!=b[i+1])
		{
			pd=1;
			break;
		}
	}
	if(!pd)
	{
		cout<<0;
		return 0;
	}
	l=0,r=n;//这里才是重头戏二分...
	while(l<r-1)//答案区间左开右闭
	{
		ll mid=(l+r)>>1;
		if(check(mid))
		{
			r=mid;
		}
		else
		{
			l=mid;
		}
	}
	cout<<r+n;
	return 0;
}
```


---

## 作者：StudyingFather (赞：1)

**Unofficial Solution to this contest also available in [Studying Father's Blog](https://studyingfather.com/archives/1304).**

------------

分两种情况考虑：

如果不用将牌堆中的每一张牌都抽出牌堆，显然最小操作数为牌堆每张牌上的数字和它的目标位置差值的最大值。

否则，牌堆中的每张牌都会被抽出一次，我们需要算出牌堆中的每张牌被抽出花费的时间和每张牌从手牌放到对应位置需要的时间。答案就是每张牌这两部分时间和的最大值。

问题就剩下如何判断当前局面对应哪一种情况。

考虑编号为 $ 1 $ 的牌，如果它刚开始在手牌里，显然剩下的牌都需要被抽出一次。

否则，我们需要计算在 $ 1 $ 号牌被抽出前，剩下所有的牌是否都能到达预定位置，且当前牌堆中任意一张牌与 $ 1 $ 号牌的相对位置差与最终局面的相对位置差是否相等。如果相对位置差完全相等，或是无需抽出 $ 1 $ 号牌即可让剩下的牌都能到预定位置，就按第一种情况处理即可。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[200005],b[200005],res1[200005],res2[200005],pos[200005],n;
int main()
{
 scanf("%d",&n);
 for(int i=1;i<=n;i++)
 {
  scanf("%d",&a[i]);
  res1[i]=n-i+1;
 }
 for(int i=1;i<=n;i++)
 {
  scanf("%d",&b[i]);
  res2[b[i]]=i;
  pos[b[i]]=i;
 }
 int flag=1;
 for(int i=2;i<=n;i++)
  if(res2[1]<=res1[i]+res2[i]&&pos[i]-pos[1]!=i-1)
  {
   flag=0;
   break;
  }
 if(pos[1]==0)flag=0;
 if(!flag)
 {
  int ans=0;
  for(int i=1;i<=n;i++)
   ans=max(ans,res1[i]+res2[i]);
  printf("%d\n",ans);
 }
 else
 {
  int ans=0;
  for(int i=1;i<=n;i++)
   if(i>b[i])ans=max(ans,i-b[i]);
  printf("%d\n",ans);
 }
 return 0;
}
```


---

