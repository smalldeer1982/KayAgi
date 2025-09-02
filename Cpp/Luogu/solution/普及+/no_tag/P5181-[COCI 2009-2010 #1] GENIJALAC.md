# [COCI 2009/2010 #1] GENIJALAC

## 题目描述

 **译自 [COCI 2009.10](http://hsin.hr/coci/archive/2009_2010/) T5「[GENIJALAC](http://hsin.hr/coci/archive/2009_2010/contest1_tasks.pdf)」**

Mirko 发明了一台打乱机。机器接受一个 $N$ 列、无限行的纸带作为输入和输出。这 $N$ 列依次编号为 $1\ldots N$。

开始时，只有纸带的第一行写了数，其下方的每一行都是空白的。  
在纸带的第一行中，每列有一个整数，第 $i$ 列上写了整数 $i$。  
另外，Mirko 给出了一个打乱排列，这是一个长度为 $N$ 的排列 $s_1,$ $s_2,$ $\ldots,$ $s_N$。

有一个行指针，开始时指向首行。  
每次运行该机器时，机器会将当前行（行指针所指向的行）位于第 $i$ 列的数放到下一行的第 $s_i$ 列上，$N$ 个数都放好后，指针将下移一行。

Mirko 运行了该机器无限次。现在 Mirko 将纸带的前 $C$ 列和后 $D$ 列剪掉了，我们称之为新的纸带。

试问：在新纸带的第 $A\sim B$ 行中，有多少行与新纸带的首行相同。

## 说明/提示

#### 样例说明 1
```plain
+-----+
|1 2 3|4 <--
|1 3 4|2
|1 4 2|3
|1 2 3|4 <--
|1 3 4|2
+-----+
 1 4 2 3
 1 2 3 4
```

#### 样例说明 2
```plain
1 2 3 4 5 6 7
2 3 1 6 4 7 5
 +-------+
3|1 2 7 6|5 4
1|2 3 5 7|4 6
2|3 1 4 5|6 7
3|1 2 6 4|7 5
1|2 3 7 6|5 4
2|3 1 5 7|4 6
 +-------+
3 1 2 4 5 6 7
1 2 3 6 4 7 5
```

#### 样例说明 3
```plain
1 2 3 4 5 6
     +-----+
6 3 5|4 2 1|
1 5 2|4 3 6|
6 2 3|4 5 1|
1 3 5|4 2 6|
6 5 2|4 3 1|
1 2 3|4 5 6| <--
6 3 5|4 2 1|
1 5 2|4 3 6|
6 2 3|4 5 1|
1 3 5|4 2 6|
     +-----+
```

#### 数据范围与提示
对于 $40\%$ 的数据，$A,$ $B,$ $C,$ $D,$ $N\le 2000$。  
对于所有数据，$1\le N\le 5\times 10^5,$ $1\le A, B\le 10^{12},$ $0\le C,$ $D\le N,$ $C+D\le N$。

## 样例 #1

### 输入

```
4 1 5 0 1
1 3 4 2```

### 输出

```
2```

## 样例 #2

### 输入

```
7 3 8 1 2
2 3 1 6 4 7 5```

### 输出

```
0```

## 样例 #3

### 输入

```
6 2 11 3 0
6 3 5 4 2 1```

### 输出

```
1```

# 题解

## 作者：sukimo (赞：6)

思路不难想，对于每一个在没有剪掉的列上的数，只需判断它移多少次就可以回到原位，然后答案就是**每一个合法的列移动次数的最大公倍数**。题目中$n$很大，所以用$O(n)$算法来求，根据题目数据性质，我们可以发现$s$数组构成了一个图，且这个图每个点必只有一条入边（某位置转移到它这里，不可能两个位置转移到同一个地方）一条出边（向下一个位置转移），那么最终的图应该与下图类似，是由一些互不干扰的有向环构成的。

![p](https://cdn.luogu.com.cn/upload/image_hosting/v24q5zzn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这就是说，对于在同一环里的两点，它们的移回次数肯定是相同的，所以在一个环里只需统计一次贡献。这样用标记数组就大大的提升了效率。

最后记得开$long\ long$！

$code:$

```
#include<algorithm>
#include<cstdio>
#define ll long long
using namespace std;
bool mark[500005];int mark_cnt,turn[500005];
int dfs(int x){
	if(mark[x])return 0;mark_cnt++;mark[x]=1;return 1+dfs(turn[x]);
}
ll _ceil(ll x,ll y){return (x+y-1)/y;}//手写向上取整函数 
int main(){
	int n,c,d;ll a,b,cnt;scanf("%d%lld%lld%d%d",&n,&a,&b,&c,&d);
	for(int i=1;i<=n;i++)scanf("%d",&turn[i]);
	for(int i=c+1;i<=n-d;i++){
		if(mark[i])continue;//若它被标记过，则与它所属同一个环的某个数已经贡献过
		ll qck=dfs(i);
		cnt=(i!=c+1?cnt/__gcd(cnt,qck)*qck:qck);//第一个特判 
		if(mark_cnt==n-c-d)break;//找完了提前退出 
	}
	printf("%lld",_ceil(b,cnt)-_ceil(a-1,cnt));
	return 0;
}
```


---

## 作者：HeCao2008 (赞：1)

[更好的阅读体验](https://www.luogu.com.cn/blog/C-SHANGHAI/solution-p5181)

[题目传送门](https://www.luogu.com.cn/problem/P5181)



思路：找循环节

我们可以先找每一位的**小循环节**，然后大循环节就是这些小循环节的**最小公倍数**。
  
找小循环节十分简单，因为每一个数在一次操作后指向另一个数，然后会指回来，这像极了**有向图找环**。
  
然而事实上确实是这样，用 dfs 找环就可以了。
  
对于每一个小循环节，需要维护它们的最小公倍数，而最小公倍数则是  $\frac{a\times b}{\gcd(a,b)} $
  对于每一个新的数加入，对于每一步的维护语句是这样的：
 
`ans=ans/__gcd(ans,len)*len; `


然后这道题就做完了，代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=514514;
int n,a,b,c,d,ans;
int edge[maxn],visit[maxn],sum;
int ceil_(int a,int b){return (a+b-1)/b;}
int dfs(int x){
	if(visit[x])return 0;
	sum++;
	visit[x]=1;
	return dfs(edge[x])+1;
} //找环
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>a>>b>>c>>d;
	for(int i=1;i<=n;i++)cin>>edge[i];
	for(int i=c+1;i<=n-d;i++){
		if(visit[i])continue;
		int len=dfs(i);
		if(i==c+1)ans=len;
		else ans=ans/__gcd(ans,len)*len;
		if(sum==n-c-d)break; //如果全搜完了就结束
	}
	/*int aa,bb;
	if((b/ans)*ans!=b)aa=b/ans+1;
	if(((a-1)/ans)*ans!=b)bb=(a-1)/ans+1;
	cout<<aa-bb<<endl;*/ //这里我试图写向上取整，最后失败了，别这么写。
	cout<<ceil_(b,ans)-ceil_(a-1,ans)<<endl;
	return 0;
}
```

**谢谢大家的阅读！**

---

## 作者：_byta (赞：1)

由于给出的变化序列是排列，所以每个数交换若干次后肯定会回到初始位置。

我们可以先求出每个数交换几次后回到原位，即每个数的循环节。

那要让他们同时回到原位，我们肯定要交换 $C + 1$ 到 $n - D$ 这些数的循环节的最小公倍数次，计它为 $k$。

最后只要求出在 $A$ 和 $B$ 范围内有多少个数模 $k$ 余 $1$ 就行了。

代码非常短。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100002;
int n, m, l, r, p, t, k = 1, ans, sum, tot, cnt, a[N], b[N], c[N], d[N], A, B, C, D;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
	{
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int lcm(int x, int y) { return x * y / gcd(x, y); }
signed main()
{
	n = read(); A = read(); B = read(); C = read(); D = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = C + 1; i <= n - D; i++)
	{
	    t = a[i]; b[i] = 1;
	    while (t != i) t = a[t], b[i]++;
	    k = lcm(k, b[i]);
	}
	tot = (A - 1) / k + 1;
	cnt = (B - 1) / k + 1;
	if((A - 1) % k == 0) tot--;
	cout << cnt - tot << endl;
	return 0;
}
```


---

## 作者：VitrelosTia (赞：0)

显然这个东西的变化是有规律的，所以我们先考虑找到第一个相同的行。

对于第一行的一个位置，我们可以让它一直往下变化并记录长度，假如现在变化到的位置是曾经到过的那么就可以不变化了。那么这样我们就知道了每一个位置第一次重复出现的位置。

那么这就是对于一个位置的一个循环了。我们只需要求出 $c + 1$ 到 $n - d$ 列的位置的最小公倍数显然就是第一个相同的行数。

最后，假设第一个相同的行数是 $l$，那么 $1$ 到 $b$ 行显然有 $\lceil \dfrac{b}{l} \rceil$ 个相同的行，而 $1$ 到 $a - 1$ 行有 $\lceil \dfrac{a - 1}{l} \rceil$ 个相同的行，最后答案就是这两个相减了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int lcm(int x, int y) {
	return x * y / __gcd(x, y);
}
const int M = 5e5 + 5;
int n, a, b, c, d, s[M];

int id[M], len[M];
bool vis[M];

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> a >> b >> c >> d;
	for (int i = 1; i <= n; i++) cin >> s[i];
	int pos = 0;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) pos++;
		while (!vis[i]) {
			vis[i] = true;
			id[i] = pos;
			len[pos]++;
			i = s[i];
		}
	}
	int l = 1;
	for (int i = c + 1; i <= n - d; i++) l = lcm(l, len[id[i]]);
	cout << ceil(1.0 * b / l) - ceil(1.0 * a / l);
	return 0;
}
```

---

## 作者：CJ_Fu (赞：0)

[P5181 [COCI2009-2010#1] GENIJALAC](https://www.luogu.com.cn/problem/P5181)

考虑连边 $i\to a_i$，这样会构成若干个环，而环的大小即为该环的循环节。

而多个环的循环节为它们的 $\operatorname{lcm}$，这个易证。

对于一段区间，由于初始 $i,a_i$ 是排列，所以区间即使仅与环相交（不包含），该环的贡献也是它的大小。

于是我们记 $S$ 为与 $[C+1,n-D]$ 有交集的环的集合，对 $S$ 中的环的大小取 $\operatorname{lcm}$ 即可。
时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define fastIO ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int maxn=5e5+3;
int n,A,B,C,D,nxt[maxn];
int col[maxn],c,siz[maxn];
int T=1;
int lcm(int a,int b){return a/__gcd(a,b)*b;}
int query(int x){
    if(!x) return 0;
    return (x-1)/T+1;
}
signed main(){
	fastIO;
	cin>>n>>A>>B>>C>>D;
	for(int i=1;i<=n;i++) cin>>nxt[i];
	for(int i=1;i<=n;i++){// 染色找环
		if(!col[i]){
			c++;
			for(int j=i;!col[j];j=nxt[j])
siz[col[j]=c]++;
		}
	}
	for(int i=C+1;i<=n-D;i++)
		T=lcm(T,siz[col[i]]);
	cout<<query(B)-query(A-1);
	return 0;
}
```

---

## 作者：free_fall (赞：0)

题目给出一个排列 $s_1,s_2,…s_N$，每次操作将 $i$ 上的数放到 $s_i$ 上，求运行了 $A-1 \sim B-1$ 次的排列中第 $C+1 \sim n-D$ 个数全部与初始值相同的个数。

因为 $s$ 数组是长度为 $n$ 的排列，可以视作若干个环，经过环的大小次数的操作后，这个环上的数与初始值相同。

于是我们对于 $C+1 \sim n-D$ 中每一个数所在的环的大小取 $lcm$，就是这个区间对应的循环节。

然后我们分别求出 $1 \sim A$ 和 $1 \sim B-1$ 中出现的次数，相减即为最终答案，时间复杂度为 $O(n)$，具体实现见代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,a,b,c,d,to[N],mark[N],len=1,ans;
void dfs(int now){
	if(mark[to[now]])return;
	mark[to[now]]=mark[now]+1;
	dfs(to[now]);
	mark[now]=mark[to[now]];
	return;
}
signed main(){
	scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d);
	for(int i=1;i<=n;i++){
		scanf("%lld",&to[i]);
	}
	for(int i=1;i<=n;i++){
		if(!mark[i]){
			mark[i]=1;
			dfs(i);
		}
	}
	for(int i=c+1;i<=n-d;i++){
		len=len/__gcd(len,mark[i])*mark[i];
		if(len>b){
			printf("0");
			return 0;
		}
	}
	ans=(b-1)/len+1;
	if(a-2!=-1)ans-=(a-2)/len+1;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：y3kkc (赞：0)

## 题意  
见[洛谷](https://www.luogu.com.cn/problem/P5181)。  
## 分析  
首先看数据范围，$1 \le A,B \le 10^{12}$，预示了该题可能的做法。  

倍增？矩阵？递归？找循环节？前三种显然都不可行，那么我们可以尝试去找循环节。  

将原序列想象成一个点集，每个牌的下一个位置当做一条有向边。  

不难发现每个点只有一条出边，且每个点入度为 1。

所以该图的性质就是若干个环组成。  

那么对于每一个节点，它的循环节就是他所在的环的大小。  

于是，我们可以预处理出 $[C + 1, N - D]$ 所有数都与原序列相等的循环节。  

很显然它是这个区间所有数的最小公倍数，计这个最小公倍数为 $gg$。  

最后对于查询 $[A ,B]$ 里的结果，我们发现它满足区间可减性，于是套路地转换为前缀和的形式相减即可。  

对于一个区间 $[1, x]$，它满足题意的个数为 $[1,x]$ 中模 $gg$ 与 1 同余的个数，我们除一除便可 $O(1)$ 计算了。  

最后还有一点小细节，$x$ 可能比 1 还小，这需要特判返回 0，~~不然连样例都过不了~~。  
## 代码  
```cpp
#include <cstdio>
#define int long long
namespace Faster {
//char buf[1 << 23], *p1 = buf, *p2 = buf;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++)
inline int read() {
    int num = 0, sgn = 1;
    char ch = getchar();
    for (; ch < 48 || ch > 57; ch = getchar())
        if (ch == '-')
            sgn = -1;
    for (; ch >= 48 && ch <= 57; ch = getchar()) num = (num << 3) + (num << 1) + (ch & 15);
    return sgn * num;
}
inline void write(int num) {
    static int sta[39], top = 0;
    if (num < 0)
        putchar('-'), num *= -1;
    do
        sta[++top] = num % 10, num /= 10;
    while (num);
    while (top) putchar(sta[top--] | 48);
    return;
}
} using namespace Faster;
const int N = 5e5 + 9;
int n, a, b, c, d, gg;
int p[N], to[N], cnt[N];
int st[N], top;
bool vis[N];
inline int gcd(int u, int v) {
	while (u % v) u %= v, u ^= v ^= u ^= v;
	return v;
}
inline int lcm(int u, int v) {
	return u / gcd(u, v) * v;
}
inline int calc(int x) {
	if (x == 0)
		return 0;
	return (x - 1) / gg + 1;
}
signed main() {
	n = read(), a = read(), b = read(), c = read(), d = read();
	for (int i = 1; i <= n; ++i) p[i] = read();
	for (int i = 1; i <= n; ++i) to[p[i]] = i;
	
	for (int i = 1; i <= n; ++i) {
		if (vis[i])
			continue;
		int u = i;
		int cntt = 0;
		while (!vis[u]) {
			vis[u] = 1;
			st[++top] = u;
			++cntt;
			u = to[u];
		}
		while (top) cnt[st[top--]] = cntt;
	}
	gg = 1;
	for (int i = c + 1; i <= n - d; ++i) {
		gg = lcm(gg, cnt[i]);
	}
	printf("%lld\n", calc(b) - calc(a - 1));
    return 0;
}
```  
## 总结  
解决该问题的关键点在于：  

* 发现每个位置的循环节，并求出 $[C + 1, N - D]$ 的循环节。  



---

## 作者：LanrTabe (赞：0)

欢迎来[Blog](https://www.cnblogs.com/LanrTabe/p/10370039.html)玩啊~

题目链接：

[Luogu5181](https://www.luogu.org/problemnew/show/P5181)

一个简单题？

首先对$[C+1,n-D]$中的每个数字求出循环节，求$Lcm$即是整段的循环节。

然后判断$[A,B]$中有几个数满足$x-1\equiv 0(mod\ Lcm)$。

求循环节暴力可过。。

其实求循环节是可以$O(n)$的。

每一次求循环节得到一个环，那么环上所有点的循环节都是此次求出的循环节。

那么就可以$O(n)$得到所有循环节。

代码：

```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
typedef long long ll;

const ll llMax=1e13;
ll Gcd(const ll a,const ll b){return b?Gcd(b,a%b):a;}
ll Lcm(const ll a,const ll b){return a/Gcd(a,b)*b;}
int n,s[500005];
bool v[500005];
ll a,b,c,d,Mfo=1;

void DFS(const int x,const int St,const int Nt)//x 现在的位置 St 此次起点 Nt 已经经过节点数
{
    if(v[x])
    {
        if(x!=St)puts("0"),exit(0);//形成环，但是St不在环上，即St没有循环节
        Mfo=Lcm(Mfo,Nt);//求Lcm
        if(Mfo>=llMax)puts("0"),exit(0);//循环节过大，那么[A,B]中没有满足要求的数
        return;
    }
    v[x]=true,DFS(s[x],St,Nt+1);
}

int main()
{
    std::cin>>n>>a>>b>>c>>d;
    for(int i=1;i<=n;++i)scanf("%d",&s[i]);
    for(int i=c+1;i<=n-d;++i)
        if(!v[i])DFS(i,i,0);//不求减去的
    ll l=std::max(a-1,(ll)1),r=std::max(b-1,(ll)1);//把[A,B]中所有数-1,求有多少数是Lcm的倍数
    if(l%Mfo)l=(l/Mfo+1)*Mfo;
    if(r%Mfo)r=r/Mfo*Mfo;
    std::cout<<(r-l)/Mfo+1+(a==1)<<std::endl;//特判第1个
    return 0;
}
```

---

