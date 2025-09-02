# Two Prefixes

## 题目描述

米莎今天又没有完成数学作业。作为惩罚，老师 Dr. Andrew 决定给他一个很难但毫无用处的任务。

Dr. Andrew 在黑板上写了两个仅由小写英文字母组成的字符串 $s$ 和 $t$。他提醒米莎，字符串的前缀是指通过去掉若干（可能为零）个末尾字符后得到的字符串；两个字符串的连接是指将第二个字符串接在第一个字符串右侧形成的新字符串。

老师要求米莎在黑板上写出所有由 $s$ 的某个非空前缀和 $t$ 的某个非空前缀连接而成的字符串。当米莎完成后，Dr. Andrew 问他一共有多少个不同的字符串。米莎花了几乎整节课才完成这个任务。

现在他请求你写一个程序自动完成这个任务。

## 说明/提示

在第一个样例中，字符串 $s$ 有三个非空前缀：{a, ab, aba}。字符串 $t$ 有两个非空前缀：{a, aa}。总共，米莎写出了五个不同的字符串：{aa, aaa, aba, abaa, abaaa}。字符串 abaa 被写了两次。

在第二个样例中，米莎写出了八个不同的字符串：{aa, aaa, aaaa, aaaaa, aaaaaa, aaaaaaa, aaaaaaaa, aaaaaaaaa}。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
aba
aa
```

### 输出

```
5
```

## 样例 #2

### 输入

```
aaaaa
aaaa
```

### 输出

```
8
```

# 题解

## 作者：EndSaH (赞：8)

[欢迎光临个人博客](https://endsah.cf/blog/CF1090J-Two-Prefixes/#more)

# Solution

后缀自动机做法还不会，略。

**对文本串 $T$ 建出 KMP 自动机，匹配串 $S$ 在上面跑所到的最终节点 $u$ 满足 $u$ 所代表的 $T$ 的前缀是最长的，能匹配 $S$ 的某个后缀的前缀节点**。

考虑简单容斥，总字符串数为 $|S| \times |T|$，减去重复字符串数。

假设 $a, a'(|a| < |a'|)$ 和 $b, b'$ 分别为 $S, T$ 的某个前缀，并且 $a + b = a' + b'$。

那么 $b'$ 一定为 $b$ 的某个 border（换言之，$b'$ 既是 $b$ 的前缀，也是 $b$ 的后缀）。

![](https://endsah.cf/uploads/pic/gp.png)

紫色和蓝色部分分别相同。

可以得到 $a'$ 的去掉 $a$ 的那段后缀和 $b$ 去掉 $b'$ 的部分（也就是紫色部分）完全一样。因为后缀的前缀相当于子串，所以枚举所有的 $b$，令 $b'$ 为 $b$ **最长**的 border，用 $b' - b$ 得到 $T$ 的一段前缀，这段前缀在 $S$ 中作为子串出现的次数就是重复次数。

为何不是所有 border 而是最长的 border，是因为要避免重复减去。

![](https://endsah.cf/uploads/pic/gp2.png)

黄色部分为 $T _j$ 的最长的 border，蓝线部分相同。由上面的内容，$S _i + T _{j} = S _{BLUE} + T _{YELLOW}$。此时视作删去 $S _i + T _j$，而非删去 $S _{BLUE} + T _{YELLOW}$。

如果计算所有的 border，$S _i + T _j$ 这个不合法的贡献就有可能会被删去多于一次。因为对于任意的 $S _i + T _j$ 都是删除不少于一次，所以一定不合法。取最长的 border 是为了保证能删除所有的不合法的情况。

现在还需要解决找到 $T$ 的某一个前缀在 $S$ 中出现了几次的问题。将 $T$ 的 KMP 自动机建出来，用 $S$ 的字符逐个匹配，可以得到 $S$ 的所有后缀与 $T$ 能匹配的最长公共前缀。

设 $u$ 是 $S$ 的某个后缀匹配到的最长公共前缀的前缀节点，那么需要在 fail 树上将 $u$ 到根的路径全部 +1，因为 $u$ 仅代表最长而不是所有，需要将是它的 border 的前缀都 +1。

这是个简单的树上差分问题，统计完后直接做就行。

$O(n)$。代码里面记得注意一些细节，因为不能够接空串。也不需要显式的建出 KMP 自动机并补转移边，直接暴力跳 fail 就行了，复杂度是对的。

# Code

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int maxN = 1e5 + 5;

int n, m;
LL ans;
int fail[maxN], cnt[maxN];
char S[maxN], T[maxN];

int main()
{
    freopen("password.in", "r", stdin);
    freopen("password.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> (S + 1) >> (T + 1);
    n = strlen(S + 1), m = strlen(T + 1);
    for (int i = 2, j = 0; i <= m; ++i)
    {
        while (j and T[j + 1] != T[i])
            j = fail[j];
        j += (T[j + 1] == T[i]);
        fail[i] = j;
    }
    for (int i = 1, j = 0; i <= n; ++i)
    {
        while (j and T[j + 1] != S[i])
            j = fail[j];
        j += (T[j + 1] == S[i]);
        if (j < i)
            ++cnt[j];
        else
            ++cnt[fail[j]];
    }
    for (int i = m; i; --i)
        cnt[fail[i]] += cnt[i];
    (ans = n) *= m;
    for (int i = 1; i <= m; ++i)
        if (fail[i] and i - fail[i] > 0)
            ans -= cnt[i - fail[i]];
    cout << ans << endl;
    return 0;
}
```


---

## 作者：happybob (赞：1)

题意：

给定字符串 $s,t$，求 $s$ 非空前缀与 $t$ 非空前缀拼接后得到的本质不同字符串个数。

$1 \leq |s|,|t| \leq 10^5$，字符集为小写英文字母。

解法：

假设 $n = |s|$，$m = |t|$。

考虑对于每个本质不同字符串，在最小的 $s$ 的前缀位置统计答案。

不难发现对于每个 $i$，有且仅有一段后缀 $[j,m]$ 符合 $s[1 \cdots i]+t[1 \cdots j]$ 是之前没有出现过的。我们考虑二分这个 $j$，问题变为给定 $i,j$，判断是否存在 $x < i$ 使得 $s[1 \cdots x]+t[1\cdots i+j-x]=s[1 \cdots i]+t[1 \cdots j]$。容易发现本质相当于我们找到 $s[1 \cdots i]$ 的某个后缀，其与 $t$ 的某个前缀相等，然后把 $t[1 \cdots j]$ 往后平移相同。

将 $t$ 与 $s$ 拼在一起，中间加个特殊符号。那么我们要找的后缀其实就是 Fail 树上的祖先。但是如果我们选了 $s[1 \cdots i]$ 的一段长度为 $k$ 的后缀，还需要判断 $t[1 \cdots j]=t[k+1\cdots k+j]$ 是否成立。注意到这等价于 $\operatorname{LCP}(t,t[k+1\cdots m]) \geq j$ 是否成立。于是先对 $t$ 做一下 exKMP，然后在树上预处理每个点到根的点权最大值即可做到 $O(1)$ 判定。

实际实现中不需要显式建树。

[Submission Link.](https://codeforces.com/contest/1090/submission/293639967)

---

## 作者：cike_bilibili (赞：0)

首先本质不同我们不好求，直接考虑转成相同计数。

先讨论两个相同的时候长什么样子。

![image](https://cdn.luogu.com.cn/upload/image_hosting/nj8rv62z.png)

如图，一个 X 串与 Y 串在不同位置划分，两串相等，那么一定有绿串既是后缀，也是 T 串的前缀，也就是说，绿串一定是 T 串的一个 border。

我们考虑什么时候算重，又如上图我们既可以从红蓝处划分，也可以从蓝绿处划分，事实上我们需要记录蓝串在 S 串中的出现次数即可，直接算会算重，我们只需要令绿串是最大 border 就可以避免算重了。

我们需要统计 T 任意前缀在 S 串中的出现次数，我们考虑枚举 S 的前缀，对于每个前缀统计后缀，我们对 T 串建 KMP 自动机，考虑在 fail 树上操作，我们让 S 作为信号序列在自动机中匹配，最后停留到的点的所有 border 均在这个后缀出现（注意如果 S 的当前前缀全被匹配上了，就要去掉整串，因为这样 S 的前缀就是空串了，否则整串也算一个 border），fail 树上祖先链加就行了。

---

## 作者：_edge_ (赞：0)

$\log^2$ 做法，建议大家不要模仿（

我们会发现，SA 也是能做本质不同的子串个数的，但是前提是对每个后缀排序，我们可以把这个限制稍微扩充一下，即为给定你 $n$ 个字符串，对他们进行排序之后就能和 SA 一样求本质不同的子串个数。

首先你不能把所有的字符串都拿出来，因为总长度是平方级别的。

其次 SA 那套后缀的倍增好像挪不过来，只能考虑简单一点。

我们直接对 $s$ 的 $n$ 个前缀和 $t$ 拼起来的结果进行排序，然后就会发现排序的过程只需要支持比较任意两个字符串的大小，也就是求他们的 LCP，那很简单了，只需要对 $s$ 和 $t$ 都哈希一下，然后拼起来即可。

然后 SA 那套是所有子串减掉 height 数组的总和，但是我们这里必须要让他们取出的前缀非空。

因此对于一个字符串的贡献是 $m$，但是两个字符串的公共部分似乎有些不太好算。

比方说对于三个字符串 $s_1,s_2,s_3$，设 `aaa` 为我们要统计的，那么如果 $s_1$ 里面出现了 `aaa` 并且他以及超过了 $s_1$ 在 $s$ 的那段前缀，那么我们就需要对 `aaa` 统计贡献，但是如果 $s_2$ 在 $s$ 的前缀以及包含了 `aaa`，那么 `aaa` 不被统计贡献，如果 $s_3$ 又有了 `aaa` 那么我们会误以为这个是可以统计的，但是实际上不行。

所以在这里处理的时候需要用一个 vis 数组，表示对于当前字符串 $s$，$1$ 到 $i$ 这一段前缀是否已经被统计进贡献了，这个只涉及区间推平和区间加，线段树维护即可。

值得一提的是，用 stable_sort 会使得调用 cmp 次数减少，常数变优秀。

```cpp
// T3
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#define ull unsigned long long  
#define fi first
#define se second
using namespace std;
const int base=233;
const int Mod=1e9+7;
const int INF=2e5+5;
struct Ha{
	ull hash1[INF],base1[INF];
	int hash2[INF],base2[INF];
	ull Get(int l,int r) {return hash1[r]-hash1[l-1]*base1[r-l+1];}
	int Get1(int l,int r) {return (hash2[r]-1ll*hash2[l-1]*base2[r-l+1]%Mod+Mod)%Mod;}
	pair<ull,int> Get3(int l,int r) {return {Get(l,r),Get1(l,r)};}
	void init(string s1,int n) {
		base1[0]=base2[0]=1;
		for (int i=1;i<=n;i++) base1[i]=base1[i-1]*base;
		for (int i=1;i<=n;i++) base2[i]=1ll*base2[i-1]*base%Mod;
		for (int i=1;i<=n;i++) hash1[i]=(hash1[i-1]*base+s1[i]);
		for (int i=1;i<=n;i++) hash2[i]=(1ll*hash2[i-1]*base%Mod+s1[i])%Mod;
	}
}H1,H2;
string s,t;
int n,m,p[INF],p1[INF],vis[INF];
pair <ull,int> check(int x,int y) {
	if (x>=y) return H1.Get3(1,y);
	else {
		pair<ull,int> it=H1.Get3(1,x);
		pair<ull,int> it2=H2.Get3(1,y-x);
		it.fi=it.fi*H2.base1[y-x]+it2.fi;
		it.se=(1ll*it.se*H2.base2[y-x]%Mod+it2.se)%Mod;
		return it;
	}
}
int LCP(int x,int y) {
	int l=1,r=min(y+m,x+m),ans=0;
	while (l<=r) {
		int Mid=(l+r)>>1;
		if (check(x,Mid)==check(y,Mid)) l=(ans=Mid)+1;
		else r=Mid-1;
	}
	return ans;
}
bool cmp(int x,int y) {
	int it=LCP(x,y);
	if (it==x+m) return 1;
	else if (it==y+m) return 0;
	else {
		char A1=0,B1=0;it++;
		if (it>x) A1=t[it-x];
		else A1=s[it];
		if (it>y) B1=t[it-y];
		else B1=s[it];
		return A1<B1;
	}
}
struct Segment{
	#define ll tl[id]
	#define rr tr[id]
	#define ls(x) x<<1
	#define rs(x) x<<1|1
	int tl[INF<<2],tr[INF<<2],sum[INF<<2],lazy[INF<<2];
	void push_up(int id) {sum[id]=sum[ls(id)]+sum[rs(id)];}
	void push_down(int id) {
		if (lazy[id]==-1) return ;
		int rt=ls(id);
		sum[rt]=lazy[id]*(tr[rt]-tl[rt]+1);
		lazy[rt]=lazy[id];

		rt=rs(id);
		sum[rt]=lazy[id]*(tr[rt]-tl[rt]+1);
		lazy[rt]=lazy[id];

		lazy[id]=-1;
	}
	void build(int l,int r,int id) {
		ll=l;rr=r;lazy[id]=-1;
		if (ll==rr) return ;
		int Mid=(ll+rr)>>1;
		build(l,Mid,ls(id));
		build(Mid+1,r,rs(id));
		push_up(id);
	}
	void add(int l,int r,int x,int id) {
		if (l<=ll && rr<=r) {
			if (x) sum[id]=rr-ll+1;
			else sum[id]=0;
			lazy[id]=x;
			return ;
		}
		push_down(id);
		int Mid=(ll+rr)>>1;
		if (l<=Mid) add(l,r,x,ls(id));
		if (Mid<r) add(l,r,x,rs(id));
		push_up(id);
	}
	int query(int l,int r,int id) {
		if (l<=ll && rr<=r) return sum[id];
		int Mid=(ll+rr)>>1;push_down(id);
		if (l>Mid) return query(l,r,rs(id));
		else if (r<=Mid) return query(l,r,ls(id));
		else return query(l,r,ls(id))+query(l,r,rs(id));
	}
}T1;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>s>>t;
	n=s.size();m=t.size();
	s=" "+s;t=" "+t;
	H1.init(s,n);H2.init(t,m);
	for (int i=1;i<=n;i++) p[i]=i;
	stable_sort(p+1,p+1+n,cmp);
	for (int i=1;i<=n;i++) p1[i]=p[i];
	long long ans=m;
	T1.build(1,n+m,1);
	T1.add(p[1]+1,p[1]+m,1,1);
    // for (int i=p[1]+1;i<=p[1]+m;i++) vis[i]=1;
	for (int i=2;i<=n;i++) {
		int it=LCP(p1[i-1],p1[i]),la=ans;
		if (p[i]+1<=it) ans-=T1.query(p[i]+1,it,1);
		if (it+1<=m+p[i]) T1.add(it+1,m+p[i],0,1);
		if (p[i]+1<=m+p[i]) T1.add(p[i]+1,m+p[i],1,1);
		// for (int j=p[i]+1;j<=it;j++) ans-=vis[j];
		// for (int j=it+1;j<=m+p[i];j++) vis[j]=0; 
		// for (int j=p[i]+1;j<=m+p[i];j++) vis[j]=1;
        ans+=m;
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：cmll02 (赞：0)

我不会 AC 自动机。

容斥，每个串只计算 $t$ 的前缀最短的一次出现。

考虑怎么样会重复。

举个例子（CF test 6）:

```
nn qnnq
nnqnn q
```

观察一下，发现算重与这个 $t$ 前缀的 border 有关。

记 $t$ 的第 $i$ 个前缀为 $T_i$，则重复次数就是 $T_{i-border(i)}$ 在 $s$ 中的出现次数。

预处理一下 $T_i$ 在 $s$ 中的出现次数，可以使用 SAM 或者其他奇奇怪怪的东西，然后上个 KMP 就做完了。


实现细节：由于前缀非空，$s_1$ 必然在结果串里，可以忽略 $s_1$ 后再跑程序。

[code](https://codeforces.com/contest/1090/submission/141794865)

---

