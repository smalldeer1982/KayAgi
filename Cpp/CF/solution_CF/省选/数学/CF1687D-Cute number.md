# Cute number

## 题目描述

> 蓝智力相当高，尤其擅长数学。据说连人类所无法想象程度的计算都能够在瞬间完成。——《东方求闻史纪》

[八云蓝](https://www.luogu.com.cn/user/149196)是一个很喜欢出可爱的数学题的可爱的女孩子。

定义 $f(x)$ 表示严格大于 $x$ 的最小的完全平方数，定义 $g(x)$ 为小于等于 $x$ 的最大的完全平方数。例如，$f(1)=f(2)=g(4)=g(8)=4$。

蓝认为，一个正整数是“可爱”的，当且仅当 $x-g(x)<f(x)-x$，例如，$1,5,11$ 是可爱的正整数，而 $3,8,15$ 不是。

蓝给了你一个长度为 $n$ 的正整数数列 $a_i$，你需要帮她找到最小的非负整数 $k$，使得对于 $\forall i$，$a_i+k$ 是可爱的。

## 样例 #1

### 输入

```
4
1 3 8 10```

### 输出

```
1```

## 样例 #2

### 输入

```
5
2 3 8 9 11```

### 输出

```
8```

## 样例 #3

### 输入

```
8
1 2 3 4 5 6 7 8```

### 输出

```
48```

# 题解

## 作者：周子衡 (赞：8)

为了方便读者理解，我们在数轴上将所有可爱的数（下面称好数）用黑色标出来，其余数用白色标出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/qkihdf6v.png)

可以发现，好数和坏数的段交错排列，好数的段长依次为 $2,3,4,...$，坏数的段长依次为 $1,2,3,...$。

令 $V=a_n$。不难发现，$a_1+k$ 取在第 $V$ 个好段的段头一定可以。这样我们只需要枚举所有 $< V$ 的段，看看 $a_1+k$ 能否取在这些段中即可。

考虑固定 $a_1+k$ 在第 $i$ 段中。可以发现，$k$ 一共有 $i+1$ 个可取的值，且当 $k$ 逐渐变化时，某个 $a_i + k$ 可能会从黑段移到白段，或从白段移到黑段。由于后面的所有段长都 $\geq i$，可以知道某个元素一旦移动到异色的格子，那么其颜色就不会发生改变。也就是说，我们不能把一个原来已经在黑格上的元素移动到白格上，同时要把原来在白格上的元素移到黑格上。可以发现，这其实限制了 $k$ 的上下界。

我们考虑这些上、下界如何计算。初始时令 $a_1+k$ 刚好为第 $i$ 段段首（即 $a_1+k=i^2$），考虑对每个白段，找到该白段内最小的 $a$，它限制了 $k$ 的下界；对每个黑段，找到该黑段内最大的 $a$，它限制了 $k$ 的上界。

可以发现，由于每段长度都 $\geq i$，这样一共只会枚举 $O(\dfrac{V}{i})$ 段。考虑预处理出每个位置的前驱后继，这样可以 $O(1)$ 获取每个段内的信息。总时间复杂度 $O(\dfrac{V}{1}+\dfrac{V}{2}+\cdots +\dfrac{V}{V})=O(V\log V)$。

```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

int a[2000000];
bool cnt[5000000];int nxt[5000000],pre[5000000];

const int N=4e6;

int main()
{
	int n=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=2;i<=n;i++)
	{
		cnt[a[i]-a[1]]=1;
	}
	nxt[N]=N;for(int i=N-1;i>=0;i--)if(cnt[i])nxt[i]=i;else nxt[i]=nxt[i+1];
	pre[0]=-1;for(int i=1;i<=N;i++)if(cnt[i])pre[i]=i;else pre[i]=pre[i-1];
	for(long long i=1;i<=a[n];i++)
	{
		if(i*(i+1)<a[1])continue;
		int lb=0,rb=i;if(a[1]>i*i)lb=a[1]-i*i;
		int l=0,r=i;
		for(int j=i;;j++)
		{
			if(pre[r]>=l)rb=min(rb,r-pre[r]);
			l+=2*j+1;
			if(nxt[r+1]<l)lb=max(lb,l-nxt[r+1]);
			r+=2*j+2;
			if(l>a[n]-a[1])break;
		}
		if(lb<=rb)
		{
			printf("%lld",i*i+lb-a[1]);
			break;
		}
	}
}
```

---

## 作者：monstersqwq (赞：7)

注意，这个做法复杂度为 $O(n+v\sqrt v)$，其中 $v$ 是值域，但是常数极小，且极难卡满，在实际运行中甚至快于不少正解。

首先观察一下这个所谓“好”的数有什么特点，大概长这样：

$1,2,4,5,6,9,10,11,12,16,17,18,19,20$，发现“好”的数连续出现，不是“好”的数也是连续出现，出现次数为 $2,1,3,2,4,3,5,4\cdots$。

先把 $k=0$ 判掉（这里出了两个巨大的错误竟然过了 pretest）

接下来首先发现一个简单的结论：对于答案 $k$，至少存在一个 $a_i$ 使得 $a_i+k$ 是完全平方数，设平方根为 $l$。

证明：若不存在某个 $a_i+k$ 是完全平方数，由于所有好数连续段都以完全平方数开头，所以将 $k$ 减一必然也满足条件。

接下来考虑枚举 $i,l$，注意到由于 $a_i+k$ 前面有长为 $l-1$ 的不好数的连续段，那么 $l-1\le a_i-a_{i-1}-1$，可以发现对于所有 $i\ge 2$，$l$ 的个数的总和是 $O(v)$ 级别的，对于 $i=1$，由于当 $l$ 过大时其后面必然存在极长的好数的连续段，必然满足条件，所以也是 $O(v)$ 的，接下来只需要考虑如何快速判断某个 $k$ 是否符合条件。

这个判断实际上只需要判断不好数连续段中有没有原序列中的数，这个实际上可以暴力，每次算出不好数连续段的左右界，预处理值域上的前缀和即可，这里的时间复杂度可以分析出来是 $O(\sqrt v)$ 的。

总复杂度 $O(n+v\sqrt v)$，进行一些简单的剪枝之后跑得飞快。

---

## 作者：UltiMadow (赞：5)

赛后用了 10min 调出来.jpg

先随便写几个数，发现符合条件的数为 $[k^2,k^2+k]$，我们称 $[k^2,k^2+k]$ 为第 $k$ 段

写出来发现是连续 $2$ 个数，再间隔 $1$ 个数，再连续 $3$ 个数，再间隔 $2$ 个数，也就是连续 $k+1$ 个数，再间隔 $k$ 个数

所以考虑枚举第一个数所在的 $k$，然后把 $a_{i+1}-a_{i}\le k$ 的数全部合并起来，变成一些区间 $[l_1,r_1],\dots,[l_p,r_p]$，显然统一区间中的数都要在同一段中

记 $del$ 为为了让所有的左端点合法最少还要右移多少，$lmt$ 为为了让所有的右端点合法最大能右移多少

每次枚举一段区间，计算 $del$ 和 $lmt$，如果 $del>lmt$ 或者当前区间内还有数不合法那么当前的 $k$ 就是不合法的

由于 $k=a_n$ 时所有数一定都可以放入第 $k$ 段，所以枚举 $k$ 的量为值域 $w$，而每次枚举的 $k$ 时区间数为 $\frac wk$，所以总时间复杂度 $\mathcal O(w\ln w)$

注意特殊处理一下 $k=\lfloor\sqrt a_1\rfloor$ 的那一段（我偷了个懒直接枚举了，实际上直接枚举会让复杂度变成 $\mathcal O(n\sqrt w)$，但毕竟常数小也能过）

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 2000010
using namespace std;
int n,a[MAXN];
int f[MAXN];
int get(int x){return f[x]==x?x:f[x]=get(f[x]);}
int lb(int x){int now=sqrt(x);return now*now;}
int rb(int x){int now=sqrt(x);return (now+1)*(now+1);}
bool check(int x){return x-lb(x)<rb(x)-x;}
int getr(int x){int now=sqrt(x);return now*(now+1);}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)f[i]=i;
	int ans=0;
	for(;check(ans+a[1]);ans++){
		bool fl=1;
		for(int i=1;i<=n;i++)
			if(!check(a[i]+ans)){fl=0;break;}
		if(fl)return printf("%lld",ans),0;
	}
	for(int k=1+(int)sqrt(a[1]);;k++){
		for(int i=get(1);i<n;i=get(i)){
			if(a[i+1]-a[i]<=k)f[i]=i+1;
			else i++;
		}int del=0,fir=k*k-a[1],fl=1,lmt=k;
		for(int i=1;i<=n;i++){
			int l=a[i],r=a[get(i)];
			if(!check(l+fir+del))del+=rb(l+fir+del)-(l+fir+del);
			int d=getr(l+fir+del)-(l+fir+del)+1;
			if(del>lmt||r-l+1>d){fl=0;break;}
			lmt=min(lmt,getr(r+fir+del)-(r+fir+del)+del);i=get(i);
		}
		if(fl)return printf("%lld",fir+del),0;
	}
	return 0;
}
```

---

## 作者：dead_X (赞：4)

记值域为 $A$。

- Observation 1

只有 $[x^2,x(x+1)]$ 之间的数才是满足要求的。

- Observation 2

如果 $a_1$ 变成 $A^2$，所有数一定都满足条件，因此 $a_1$ 所在的 $x$ 只有 $A$ 种情况。

考虑枚举 $x$，遍历每个数，对于满足这个 $x$ 的所有 $k$，$a_i+k$ 都存在唯一的 $x'$。

证明非常显然，一共只有 $x+1$ 个 $k$，而跨越两段至少需要 $x+2$ 个。

将每个数的合法区间取交集的左端点就是答案，于是我们在 $O(nA)$ 的时间内解决了问题。

- Observation 3

假如我们已经选定了 $x$，我们可以发现一个事实：对于 $i=2\sim n$，如果 $a_i-a_{i-1}\leq x$，那么它们的 $x'$ 一定是相同的，证明同 $a_i+k$ 存在唯一的 $x'$。

于是我们可以在枚举到 $x$ 之后将两个相差不超过 $x$ 的数压起来，对于整段计算答案。

不难发现一个相差为 $d$ 的 gap 会被计算 $d$ 次，因此总时间复杂度 $O(n+A)$，但是要乘一个开根号的常数，所以跑着挺慢的。

## 代码

```cpp
// Problem: D. Cute number
// Contest: Codeforces - Codeforces Round #796 (Div. 1)
// URL: https://codeforces.com/contest/1687/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//回家？我没有家可以回，我没有退路。
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003],l[1000003],r[1000003];
int pre[1000003],nxt[1000003];
vector<int> f[2000003];
int fr(int x)//valid or next valid
{
	int t=sqrt(x);
	if(t*t<=x&&x<=t*(t+1)) return t;
	return t+1;
}
signed main()
{
	int n=read();
	nxt[0]=1;
	for(int i=1; i<=n; ++i) 
		l[i]=r[i]=a[i]=read();
	for(int i=1; i<=n; ++i)
		pre[i]=i-1,nxt[i]=i+1;
	for(int i=1; i<n; ++i) 
		f[a[i+1]-a[i]].push_back(i);
	for(int i=0; i<=2000000; ++i)
	{
		for(int j:f[i])
			l[nxt[j]]=l[j],
			nxt[pre[j]]=nxt[j],
			pre[nxt[j]]=pre[j];
		int L=max(0ll,i*i-l[1]),R=i*(i+1)-l[1];
		for(int j=nxt[0],x,tl,tr; L<=R&&j<=n; j=nxt[j])
			x=fr(l[j]+L),tl=max(0ll,x*x-l[j]),
			tr=x*(x+1)-r[j],L=max(L,tl),R=min(R,tr);
		if(L<=R) printf("%lld\n",L),exit(0);
	}
	puts("-1");
	return 0;
}
```

---

## 作者：minstdfx (赞：2)

~~对立，我的对立，呜呜呜呜呜呜 616 你还我对立~~  
~~等会我太菜了打不动 arcaea 啊，那没事了~~

根据定义，我们设 $g(x)=a^2,f(x)=(a+1)^2$，可爱数的集合为 $P$，值域为 $M=a_n$。

$$x-a^2<(a+1)^2-x$$
$$2x<2a^2+2a+1$$
$$x<a^2+a+\frac 1 2$$
$$\because a^2+a=a(a+1) \in Z,x \in Z$$
$$\therefore x\le a(a+1)$$

$$\therefore P\cap[a^2,(a+1)^2)=\{x\mid x \le a(a+1)\}$$

显然，$\forall a_i \in [1,M]$，$a'_i=a_i+M^2-1\in [M,M^2+M-1]$ 均符合条件。

因而 $k < M^2$。

我们假设 $a'_1$ 被钦定到 $[v^2,v(v+1)]$ 里面。

当它在区间左端点 $a_1+m=v^2$ 时，设此时的每一项为 $b_i=a_i+(v^2-a_1)(b_1=v^2)$。

那么必然有 $b_1=v^2 \le a'_1\le v^2+v=a_1+v$，所以令 $p=a'_i-b_i \in [0,v]$，此时 $k=p+v^2-a_1$。

- 若 $c^2 \le b_i \le c^2+c\:(v\le c)$，则 $a'_i=b_i+p\le c^2+c+p <c^2+2c+1=(c+1)^2$。
- 若 $c^2+c \le b_i \le (c+1)^2\:(v\le c)$，则 $a'_i=b_i+p\le (c+1)^2+p <(c+1)^2+c+1$。

第一条说明在挪动第一项的时候，原本已经满足的可以变得不满足，但是变不回去。我们可以找到每段 $[w^2,w(w+1)]$ 可行的 $b_i$ 中最大的，这限制了 $k$ 的上界（$b_i+p \le w(w+1)\Rightarrow a_i+k \le w(w+1)$）。

第二条则说明我们需要尽力挪动使得原本不满足的变成满足的。同理每段中最小的限制了下界。

枚举每个 $v \le M$，与处理一下就可以 $O(1)$ 搞每一段。~~总复杂度调和级数，$O(M\log M)$。~~

我们可以发现 $i$ 被统计了 $a_i-a_{i-1}$ 次，所以复杂度是线性的。感谢 @realMatrixCascade 指出错误。

出题人可爱，贴贴


---

## 作者：tybbs (赞：1)

一个不太一样的做法。


显然，cute number 构成若干个连续段，第 $i$ 段为 $[(i-1)^2,(i-1)\times i]$。  
不妨把 $A$ 按升序排序。考虑 $A_i$ 最终可能的值域，也可以分为若干个连续段 $[l_k,r_k]$，满足 $r_k-l_k+1\le k$。我们考察 $A_i$ 到 $A_{i+1}$ 连续段的变化情况。设 $d=A_{i+1}-A_i$。  
对于 $k>d$，显然 $[l_k,r_k]$ 后会跟有一个长度为 $k-1$ 的不合法连续段，所以 $[l_k+d,r_k+d]$ 不会进入另一个 cute number 段。可以直接打一个标记，表示 $[l_k,r_k]$ 更新为 $[l_k+d,\min(r_k+d,lim)]$，其中 $lim=\lfloor\sqrt{l_k}\rfloor\times( \lfloor\sqrt{l_k}\rfloor+1)$。    
对于 $k\le d$，$[l_k+d,r_k+d]$ 可能会与另一个 cute number 段相交，但只会和单个段相交，应为 $r_k-l_k+1$ 的长度不能覆盖一个不合法连续段。所以直接暴力修改 $[l_k,r_k]$，并更新标记中的 $lim$ 即可。   
显然 $\sum d=\max{A_i}$，所以总复杂度 $O((n+V)\log V)$。

[code](https://www.luogu.com.cn/paste/9wgwa3kz)

---

## 作者：HNOIRPplusplus (赞：0)

首先我们可以打表发现，对于一个正整数 $n$，所有在 $\left[n^2,n(n+1)\right]$ 中间的数都是可爱的，而所有在 $\left(n(n+1),(n+1)^2\right)$ 中间的数都是不合法的。具体地，在下面我把可爱的数标上红色：

$$\red{1},\red{2},3,\red{4},\red{5},\red{6},7,8,\red{9},\red{10},\red{11},\red{12},13,14,15,\dots$$

我们发现这些段的长度规律十分清晰。（当然，平方数的性质决定了这一点。）

我们考虑，首先钦定一个数，让它能够落在其中的一个红色段内。比如钦定 $a_1+k$ 属于某一个特定的红色段，则 $k$ 将会有一个上界和一个下界，不妨假设为 $l,r$，则 $a_1+l$ 是某个平方数，$a_1+r$ 是某个形如 $n(n+1)$ 的东西。

不考虑重复的数，则 $a_2>a_1$。则 $a_2+l$ 到 $a_2+r$ 中间最多只有两段不一样的颜色。  
因为 $a_2>a_1$，所以 $\left[a_2+l,a_2+r\right]$ 在 $\left[a_1+l,a_1+r\right]$ 的右侧，而 $\left[a_1+l,a_1+r\right]$ 这个红色段右边最短的段也就是长度为 $(r-l)$ 的一个黑色段，其它段的长度都至少是 $(r-l+1)$。  
而 $\left[a_2+l,a_2+r\right]$ 的长度只有 $(r-l+1)$，故不可能有横跨三个颜色段的情况。

于是，对于接下来的每一个 $a_i$，$\left[a_i+l,a_i+r\right]$ 这个区间中只会有一段连续的红色，而这一段红色可以对区间左右端点开根而求出。我们将上下界缩小到新的限制即可。

我们从最左边的红色块开始，一共最多可能要枚举 $O(V)$ 个块，而每次检查可能是 $O(n)$ 的。虽然很明显跑不满，但是仍然完全无法通过。所以我们考虑优化。

于是抛开元素，我们对于每一个块进行考虑。

对于一个红色的块，假设该块的位置为 $\left[lx, rx\right]$，且当前的上下界为 $l,r$。则，值处于 $\left[lx-r,rx-l\right]$ 中间的元素都是可以落到这个红色块内的，同时前面也证明了这些元素必定只能落到这个红色块内了。从而，只有该区间中最左侧和最右侧的元素是有用的，我们仅用这两个元素来更新上下界。

对于一个黑色的块，也假设该块的位置为 $\left[lx, rx\right]$，且当前的上下界为 $l,r$。则，值处于 $\left[lx-l,rx-r\right]$ 中间的元素都是无法避免要落到这个黑色块内的，如果该区间内有元素那就直接暴毙了。

对于块内左右的位置，我们可以用值域线段树维护。不用 ST 表是因为我拼尽全力开不下（悲痛）。而对于块内具体有几个元素，用值域前缀和维护即可。~~然后我一开始用线段树维护区间和 T 飞了。~~

时间复杂度大概是 $O(V\log V\log N)$ 的并且带有不小的常数。不过肯定也跑不满，所以我们愉快的用将近一千毫秒通过此题。

代码：
``` cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)

using namespace std;

const int N = 2000005;

int a[N];
int tr[4 * N];
int presum[N];

inline int read() {
  int x = 0;
  char c = getchar();
  while(!isdigit(c)) {
    c = getchar();
  }
  while(isdigit(c)) {
    x = x * 10 + (c ^ 48);
    c = getchar();
	}
  return x;
}

void modify(int id, int l, int r, int p) {
  if (l == r) {
    tr[id]++;
    return;
  }
  int mid = (l + r) / 2;
  if (p <= mid) {
    modify(id * 2, l, mid, p);
  } else {
    modify(id * 2 + 1, mid + 1, r, p);
  }
  tr[id] = tr[id * 2] + tr[id * 2 + 1];
}

int querysum(long long l, long long r) {
  if(l > r) {
    return 0;
  }
  return presum[min(r, N - 1ll)] - presum[max(l - 1, 0ll)];
}

int queryl(int id, int l, int r, int ql, int qr) {
  if (r < ql || qr < l || qr < ql || tr[id] == 0) {
    return -1;
  }
  if (l == r) {
    return l;
  }
  int mid = (l + r) / 2, ans = queryl(id * 2, l, mid, ql, qr);
  return (ans == -1 ? queryl(id * 2 + 1, mid + 1, r, ql, qr) : ans);
}

int queryr(int id, int l, int r, int ql, int qr) {
  if (r < ql || qr < l || qr < ql || tr[id] == 0) {
    return -1;
  }
  if (l == r) {
    return l;
  }
  int mid = (l + r) / 2, ans = queryr(id * 2 + 1, mid + 1, r, ql, qr);
  return (ans == -1 ? queryr(id * 2, l, mid, ql, qr) : ans);
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int n = 100000;
  n = read();
  for (int i = 1; i <= n; i++) {
    a[i] = read();
  }
  n = unique(a + 1, a + n + 1) - (a + 1);
  for (int i = 1; i <= n; i++) {
    modify(1, 1, N, a[i]);
    presum[a[i]]++;
  }
  for (int i = 1; i < N; i++) {
    presum[i] += presum[i - 1];
  }
  for (long long i = 1; ; i++) {
    if (i * (i + 1) < a[1]) {
      continue;
    }
    long long l = max(i * i - a[1], 0ll), r = i * (i + 1) - a[1], cnt = 1;
    for (long long j = i; cnt < n && l <= r; j++) {
      int sum = querysum(max(a[1] + 1ll, j * j - r), j * (j + 1) - l);
      if (sum) {
        int lb = queryl(1, 1, N, max(a[1] + 1ll, j * j - r), j * (j + 1) - l), rb = queryr(1, 1, N, max(a[1] + 1ll, j * j - r), j * (j + 1) - l);
        if (lb + l < j * j) {
          l = j * j - lb;
        }
        if (rb + r > j * (j + 1)) {
          r = j * (j + 1) - rb;
        }
      }
      cnt += sum;
      sum = querysum(max(a[1] + 1ll, j * (j + 1) + 1 - l), (j + 1) * (j + 1) - 1 - r);
      if (sum) {
        break;
      }
    }
    if (cnt == n && l <= r) {
      cout << l << '\n';
      return 0;
    }
  }
}
```

---

## 作者：happybob (赞：0)

注意到满足 $x-g(x) < f(x)-x$ 的 $x$ 为 $1,2,4,5,6,9,10,11,12,\cdots$，在数轴上来看，构成了长度为 $2,3,4,\cdots$ 的连续段，且段之间是长度为 $1,2,3,\cdots$ 的连续段。第 $i$ 个可行连续段的起点为 $i^2$，长度为 $i+1$

。

考虑枚举 $a_1 + k$ 在第 $i$ 段开头，注意到 $i=a_n$ 则一定符合条件，所以 $i \leq a_n$。

$a_1+k$ 在开头时取值为 $k$，$k'$ 是我们真正需要的答案。此时可以对 $k'$ 求出一个范围，但是同时对于后面的每一段，$a_i + k$ 若在可行段内，则 $a_i + k'$ 不能进入下一段，同时 $a_i + k$ 若不在可行段内则 $a_i + k'$ 必然恰好切换一段。

注意到每次往后枚举段的复杂度为 $O(\dfrac{V}{i})$，所以总复杂度是调和级数的。

---

## 作者：沉石鱼惊旋 (赞：0)

# 题意

定义 $g(x)$ 为 $\max\{k^2\mid k\in \mathbb{N}\land k^2\leq x\}$，定义 $f(x)$ 为 $\max\{k^2\mid k\in \mathbb{N}\land k^2\gt x\}$。称 $x$ 是好的当且仅当 $x-g(x)\lt f(x)-x$。

给定 $n$ 个数 $a_i$，求最小的 $k$ 使得对于所有 $i$，$a_i+k$ 都是好的。

$1\leq n\leq 10^6$，$1\leq a_i\leq 2\times 10^6$。

# 做法

约定 $V=a_n\leq 2\times 10^6$。

先把这个不等式解一下，就是 $k^2\leq x\leq k(k+1)$。

画一下这个数轴，大概是 $[1,2],3,[4,5,6],7,8,[9,10,11,12],13,14,15\dots$，可以发现连续段长度是 $2,1,3,2,4,3,5,4$。奇偶项分别是等差数列。

发现答案的平方根其实不会很大，因为必然能选择 $k=a_n^2-a_1$ 有解。所以答案的平方根只有 $\mathcal O(V)$。

考虑枚举答案的平方根，或者说是 $a_1$ 枚举在哪一个合法段内然后算出这个段内还要多少增量。

第 $x$ 个合法段长度为 $x$，所以我们只有 $\mathcal O(V/x)$ 个合法段。全部扫一遍复杂度是调和级数的。

发现每个数会有几个合法的 $k$ 的区间。但是再观察一步，会发现合法区间只会有一个。因为这个区间长度是等差数列，所以一个数不可能先从合法转成不合法再从不合法转成合法（同时 $a_1$ 仍然在第 $x$ 段内）。

算出每个数的合法区间求交，左端点即为 $a_1$ 移动到这一块之后还要移动几步。

如果 $a_1$ 仍然在初始的块内有点特殊，写的不好可能要特判点东西。

复杂度 $\mathcal O(V\log V)$。

# 代码

<https://codeforces.com/problemset/submission/1687/311341914>

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
typedef long long ll;
template <typename T>
void chkmx(T &x, T y) { x = max(x, y); }
template <typename T>
void chkmn(T &x, T y) { x = min(x, y); }
int n;
ll a[1000020];
int nxt[2000020];
int main()
{
    read(n);
    for (int i = 1; i <= n; i++)
        read(a[i]);
    for (int i = 0; i <= 2000000; i++)
        nxt[i] = upper_bound(a + 1, a + n + 1, i) - a;
    for (ll x = 1; x <= a[n]; x++)
    {
        if (x * (x + 1) < a[1])
            continue;
        ll l = 0, r = x;
        ll k = max(0LL, x * x - a[1]);
        for (ll y = x; (y - 1) * y - k < a[n]; y++)
        {
            int p = (y - 1) * y - k < 0 ? 1 : nxt[(y - 1) * y - k];
            int q = y * (y + 1) - k > 2000000 ? n : nxt[y * (y + 1) - k] - 1;
            chkmx(l, y * y - (a[p] + k));
            chkmn(r, y * (y + 1) - (a[q] + k));
        }
        if (r < l)
            continue;
        return cout << k + l << '\n', 0;
    }
    cout << -1 << '\n';
    return 0;
}
```

---

## 作者：intel_core (赞：0)

注意到答案的上界是 $a_n^2-a_1$，且 $[x^2,x(x+1)]$ 内的数都是好的，很明显，合法段和不合法段的长度都是公差为 $1$ 的等差数列。

枚举 $a_1+k$ 所在的段 $i$，那么只用考虑 $\frac{V}{i}$ 个段即可。因为段长不断增加，所以在保证 $a_1+k$ 合法的过程中 $k$ 增大时剩下的所有数的合法情况最多只会变化一次。

这样就可以直接推出每个数应该在哪个块里，把所有限制求一个交即可。

复杂度是自然对数 $O(n\log V)$。

---

