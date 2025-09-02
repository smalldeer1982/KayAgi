# Palindrome Partition

## 题目描述

A substring is a continuous and non-empty segment of letters from a given string, without any reorders.

An even palindrome is a string that reads the same backward as forward and has an even length. For example, strings "zz", "abba", "abccba" are even palindromes, but strings "codeforces", "reality", "aba", "c" are not.

A beautiful string is an even palindrome or a string that can be partitioned into some smaller even palindromes.

You are given a string $ s $ , consisting of $ n $ lowercase Latin letters. Count the number of beautiful substrings of $ s $ .

## 说明/提示

In the first test case, the beautiful substrings are "abaaba", "baab", "aa".

In the last test case, the beautiful substrings are "aa" (counted twice), "abba", "bb", "bbaa", "abbaaa".

## 样例 #1

### 输入

```
6
6
abaaba
1
a
2
aa
6
abcdef
12
accabccbacca
6
abbaaa```

### 输出

```
3
0
1
0
14
6```

# 题解

## 作者：ExplodingKonjac (赞：22)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1827C)**

稍微不一样的做法。

## 题目分析

假设我们把一个空隙 $(i,i+1)$ 看做一个点 $i\ (0\le i\le n)$，对于一个偶回文子串 $s[l:r]$，在点 $l-1,r$ 之间连一条**无向**边。那么一个子串 $[l,r]$ 是 beautiful 的，当且仅当存在一条 $l-1\leadsto r$ 的路径。

那么假设能够把图建出来，答案就是对所有极大连通块 $S$ 的 $\dfrac{|S|(|S|-1)}{2}$ 求和。

先跑一遍 Manacher 算法，得到每个空隙 $(i,i+1)$ 的回文半径 $p_i$。那么 $i,i-1,\dots,i-p_i$ 需要分别向 $i,i+1,\dots,i+p_i$ 连边。这个可以使用 [[SCOI2016] 萌萌哒](https://www.luogu.com.cn/problem/P3295) 的技巧在 $O(n\log n)$ 的时间内解决。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

// 省略快读

int T,n,p[500005];
char s[500005];

void manacher()
{
	static char tmp[1000005];
	static int f[1000005];
	int m=0;
	for(int i=1;i<=n;i++) tmp[++m]=s[i],tmp[++m]='#';
	tmp[0]='$',tmp[m--]='\0';
	for(int i=1,j=0,mx=0;i<=m;i++)
	{
		f[i]=0;
		if(i<mx) f[i]=min(f[j*2-i],mx-i);
		while(tmp[i-f[i]]==tmp[i+f[i]]) f[i]++;
		if(i+f[i]>mx) j=i,mx=i+f[i];
	}
	for(int i=1;i<n;i++) p[i]=f[i<<1]>>1;
}

vector<int> mdf[20];
int fa[1000005],siz[1000005],ffa[1000005];
inline void init()
{ for(int i=0;i<=2*n;i++) fa[i]=i,siz[i]=(i<=n); }
inline int findFa(int x)
{ return x!=fa[x]?fa[x]=findFa(fa[x]):x; }
inline void merge(int x,int y)
{ x=findFa(x),y=findFa(y);if(x!=y)fa[y]=x,siz[x]+=siz[y],siz[y]=0; }

int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n>>(s+1);
		manacher();
		for(int i=1;i<n;i++)
			if(p[i]) mdf[__lg(p[i]+1)].push_back(i);
		iota(ffa,ffa+2*n+1,0);
		for(int k=__lg(n);k>=0;k--)
		{
			init();
			for(int i=0;i+(1<<(k+1))-1<=2*n;i++)
			{
				merge(i,ffa[i]);
				merge(i+(1<<k),ffa[i]+(1<<k));
			}
			for(auto &i: mdf[k])
			{
				int l1=i-p[i],r1=i,l2=i,r2=i+p[i];
				tie(l2,r2)=pair(2*n-r2,2*n-l2);
				merge(l1,l2);
				merge(r1-(1<<k)+1,r2-(1<<k)+1);
			}
			copy(fa,fa+2*n+1,ffa);
			mdf[k].clear();
		}
		for(int i=0;i<=n;i++) merge(i,2*n-i);
		LL ans=0;
		for(int i=0;i<=2*n;i++)
			if(findFa(i)==i) ans+=LL(siz[i])*siz[i];
		qout<<(ans-n-1)/2<<'\n';
	}
	return 0;
}
```


---

## 作者：Alex_Wei (赞：11)

### [CF1827C Palindrome Partition](https://www.luogu.com.cn/problem/CF1827C)

对于一个偶回文串，若它有一个偶回文串后缀，那它一定可以划分为若干更短的偶回文串。根据回文串的性质手动模拟一下即可。

因此，对于每个好串，将其划分为极小偶回文串的方式是唯一的：找到最短偶回文串后缀，然后删去。这给予我们如下 DP 思路：

设 $f_i$ 表示以 $i$ 结尾的最短偶回文串长度，$g_i$ 表示以 $i$ 结尾的好串数量。若 $f_i$ 不存在，则 $g_i = 0$。否则 $g_i = 1 + g_{i - f_i}$。

借助 Manacher 求出以每个间隔为回文中心的最大回文半径（以间隔为回文中心保证了回文串长度为偶数），按位置从小到大考虑每个间隔，就是对 $f$ 做区间赋值。倒过来考虑到间隔 $i - 1\sim i$ 时，相当于：将一段左端点为 $i$ 的区间内所有还未被删去的位置的 $f$ 值赋为某个关于 $i, j$ 的值，并将这些位置删去。用双向链表维护即可做到 $\mathcal{O}(n)$。

[代码](https://codeforces.com/contest/1827/submission/205930853)。

---

## 作者：henrytb (赞：6)

我寻思这题的 manacher 做法应该不需要什么区间覆盖啊？更不需要什么区间覆盖倒着做变成并查集的那个 trick。直接用单调栈就好了，$O(n)$。但是看题解没人这么写。

具体来讲，还是设 $f_i$（代码里用的是 $g$）表示 $i$ 结尾的好串个数，然后考虑转移。

首先肯定是得挖掉一个以 $i$ 结尾的偶回文串用来转移。但是直接枚举所有偶回文串用来转移可能会数重。但是可以证明，除了以 $i$ 结尾的**最短偶回文串**以外，其他的以 $i$ 结尾的偶回文串都可以被若干偶回文串拼接表示（证明很容易，留作思考）。那么转移式子就出来了，$f_i = 1 + f_{i - t}$，其中 $t$ 为 $i$ 结尾的最短偶回文串长度。

现在问题就是对每个 $i$ 想要知道以 $i$ 结尾的最短偶回文串长度了。考虑 manacher 的时候对于每个偶回文中心都能求出一个最长的管辖范围，而且对于一个 $i$，以它结尾的最短偶回文串一定是所有能覆盖它的偶回文串中心中**最靠右的**。那么假如一个偶回文中心既比后面的某个偶回文中心靠前，又比后面的那个管辖范围要靠前，那么它就废了，可以直接用单调栈维护。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 1e6 + 10;
int _, n, nn;
char s[N], ss[N];
int f[N], mx, mxid, g[N];
int stk[N], top = 0;
int main() {
    for (scanf("%d", &_); _; --_) {
        scanf("%d%s", &n, s + 1);
        nn = 0;
        ss[0] = '$';
        ss[++nn] = '#';
        rep(i, 1, n) {
            ss[++nn] = s[i];
            ss[++nn] = '#';
        }
        ss[++nn] = '@';
        mx = 0; mxid = 0;
        rep(i, 1, nn) {
            f[i] = 0;
            if (i <= mx) f[i] = min(f[mxid * 2 - i], mx - i);
            while (ss[i + f[i] + 1] == ss[i - f[i] - 1]) ++f[i];
            if (i + f[i] > mx) mx = i + f[i], mxid = i;
        }
        long long ans = 0;
        top = 0;
        rep(i, 1, n) {
            while (top && stk[top] / 2 + f[stk[top]] / 2 < i - 1 + f[2 * i - 1] / 2) --top;
            stk[++top] = 2 * i - 1;
            while (top && stk[top] / 2 + f[stk[top]] / 2 < i) --top;
            if (top) g[i] = 1 + g[stk[top] - 1 - i], ans += g[i];
            else g[i] = 0;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：chlchl (赞：4)

## 题意
定义满足下面任意一个条件的字符串为“好串”：
- 它是个偶回文串；
- 它可以拆分成连续若干个子串，使得每个子串都是“好串”。

现给定一个字符串，求其子串中有多少个“好串”。

## Solution
这道题非常不戳，跟其他两位大佬一起探讨出来了做法。

首先，还是一个重要且关键的性质：一个偶回文串，如果有一个非自身的偶回文串后缀，那么它一定可以被拆成若干个更小的偶回文串。

这个性质显然：根据回文性，它一定也拥有一个偶回文串前缀，且长度相同。然后，你就会发现，除去一头一尾，中间那个部分必然是一个回文串，所以它至少能拆成三个小的偶回文串。

如果这个偶回文串后缀长度大于一半，显然通过一次对称也是能够证明的。

所以，为了避免算重，我们要把所有这样的字符串全部拆开。

一个快速的方法是，把整个字符串拆成若干个“极小的”偶回文串，维护 $len_i$ 表示以 $i$ 为结尾的最短偶回文串的长度。

然后考虑一个 dp。设 $f_i$ 为以 $i$ 结尾的“好串”个数。则 $f_i$ 可以这么转移得到：
- $len_i=0$，没有好串出现，$f_i=0$。
- $len_i\ne 0$，$f_i=f_{i-len_i}+1$，因为 $[len_i+1,i]$ 是一个好串也仅多出这一个好串。

答案就是 $\sum\limits_{i=1}^{n}f_i$，线性时间线性空间，十分优秀。

所以只需要解决如何快速求出 $len$ 数组的问题。

回文问题自然想到 ~~PAM~~ manacher。但是 manacher 跑出来的 $p_i$ 是以 $i$ 为回文中心的回文半径的长度，我要求的却是以 $i$ 为结尾，怎么办呢？

想想，中心 + 回文半径影响的是一个区间，我们可以对其做一次覆盖，将 $[i,i+p_i-1]$ 这个区间全部覆盖成 $i$。这样，拿 $i$ 减掉覆盖在它上面的那个数，就是 $len_i$ 的值。

为了保证 $len$ 的意义（即要保证它是最小长度），我们从前往后跑一次 manacher，每次求出来之后直接覆盖掉即可，这样最晚覆盖的一定是离 $i$ 最近的，就可以令它长度尽量小了。

查询的时候就单点查询即可。使用 ~~树状数组或 ODT~~ 线段树维护即可。

时间复杂度 $O(n\log n)$。

还行，代码也不是很难写。整题下来，感觉上比费解的 B、比困难的 D、E 好一点。

ps：这道题的数据居然放过了我错误的 manacher 板子，跑 manacher 时的边界应该是 $2n+2$，但是我写了 $n$ 居然过了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 10;
int T, n, p[N << 1], f[N];
int val[N << 2], tag[N << 2];
char s[N << 1], t[N];


#define ls(o) (o << 1)
#define rs(o) (o << 1 | 1)

void build(int o, int l, int r){
	val[o] = tag[o] = 0;
	if(l == r)
		return ;
	int mid = (l + r) >> 1;
	build(ls(o), l, mid);
	build(rs(o), mid + 1, r);
}

void pushdown(int o){
	if(!tag[o])
		return ;
	val[ls(o)] = val[rs(o)] = tag[o];
	tag[ls(o)] = tag[rs(o)] = tag[o];
	tag[o] = 0;
}

void update(int o, int l, int r, int s, int t, int x){
	if(l >= s && r <= t){
		val[o] = tag[o] = x;
		return ;
	}
	int mid = (l + r) >> 1;
	pushdown(o);
	if(s <= mid)
		update(ls(o), l, mid, s, t, x);
	if(t > mid)
		update(rs(o), mid + 1, r, s, t, x);
	val[o] = max(val[ls(o)], val[rs(o)]);
}

int query(int o, int l, int r, int p){
	if(l == r)
		return val[o];
	int mid = (l + r) >> 1;
	pushdown(o);
	if(p <= mid)
		return query(ls(o), l, mid, p);
	return query(rs(o), mid + 1, r, p);
}


main(){
	scanf("%lld", &T);
	while(T--){
		if(n)
			build(1, 1, n);
		for(int i=1;i<=n;i++)
			p[i] = 0;
		for(int i=1;i<=n*2;i++)
			s[i] = 0;
		scanf("%lld", &n);
		scanf("%s", t + 1);
		for(int i=1;i<=n*2+2;i++)
			s[i] = '#';
		for(int i=1;i<=n;i++){
			s[i * 2] = t[i];
			f[i] = 0;
			update(1, 1, n, i, i, i);
		}
		int mr = 0, md = 0;
		for(int i=1;i<=2*n+2;i++){
			if(i <= mr)
				p[i] = min(p[md * 2 - i], p[md] + md - i);
			else
				p[i] = 1;
			while(s[i - p[i]] == s[i + p[i]])
				++p[i];
			if(i + p[i] > mr)
				mr = i + p[i], md = i;
			if((i & 1) && p[i] > 1)//偶回文
				update(1, 1, n, (i + 1) / 2, i / 2 + p[i] / 2, i / 2);//这个边界自己推，需要维护的是倍长之前的信息 
		}
		int ans = 0;
		for(int i=1;i<=n;i++){
			int l = (i - query(1, 1, n, i)) * 2;
			f[i] = (l ? f[i - l] + 1 : 0);
			ans += f[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：include_BM (赞：4)

设 $f_i$ 表示以 $i$ 结尾的好的子串个数，$\mathit{mn}_i$ 表示以 $i$ 为右端点的最短的偶数回文串为 $[\mathit{mn}_i,i]$，因为以 $i$ 结尾的好的子串一定包含 $[\mathit{mn}_i,i]$，且以 $i$ 结尾的好的子串去掉 $[\mathit{mn}_i,i]$ 也是好的，可以得到转移方程：

$$f_i=f_{\mathit{mn}_i-1}+1$$

设 $[\mathit{mn}_i,i]$ 的回文中心为 $\mathit{md}_i$（取两个回文中心中较小的一个），直接求 $\mathit{mn}_i$ 可能不好求，所以我们可以尝试先求 $\mathit{md}_i$，再由 $\mathit{md}_i$ 得到 $\mathit{mn}_i$。

先对 $s$ 跑一遍 [manacher][def_manacher]，求出每个位置的最长回文半径 $p_i$，枚举每个偶数回文的中心 $i$（即 manacher 过程中加入的特殊点），那么在原串中 $\left[\left \lfloor\tfrac{i}{2}\right \rfloor+1,\left \lfloor\tfrac{i}{2}\right \rfloor+\left \lfloor\tfrac{p_i}{2}\right \rfloor\right]$ 的范围内都存在以 $\left \lfloor\tfrac{i}{2}\right \rfloor,\left \lfloor\tfrac{i}{2}\right \rfloor+1$ 为回文中心的偶数回文串，即我们需要给这一段的 $\mathit{md}_j$ 和 $\left \lfloor\tfrac{i}{2}\right \rfloor$ 取 $\max$。

那么从大到小枚举 $i$，区间覆盖即可，代码中 $\mathit{md}_i$ 表示 $i$ 右边第一个还没被改过的位置，用并查集维护。

最终答案即为 $\sum f_i$。

```cpp
const int N=1e6+10;
int n,mn[N],p[N],num,fa[N]; ll f[N],ans; char s[N],t[N];

int getf(int x){return x==fa[x]?x:fa[x]=getf(fa[x]);}
inline void chg(int l,int r,int k){
    for(int i=getf(l);i<=r;i=getf(i+1)) mn[i]=k,fa[i]=getf(i+1);
}

signed main(){
    for(int T=read();T;--T){
        n=read(),scanf("%s",s+1),t[num=1]='|',ans=0;
        for(int i=1;i<=n;++i) t[++num]=s[i],t[++num]='|';
        for(int i=1,mid=0,r=0;i<=num;++i){
            if(i<=r) p[i]=min(p[2*mid-i],r-i); else p[i]=1;
            while(i-p[i]>=1&&i+p[i]<=num&&t[i-p[i]]==t[i+p[i]]) ++p[i];
            if(i+p[i]>r) mid=i,r=i+p[i];
        }
        for(int i=1;i<=n+1;++i) fa[i]=i,mn[i]=1e8;
        for(int i=num;i>=1;i-=2) chg(i/2+1,i/2+p[i]/2,i/2);
        for(int i=1;i<=n;++i) mn[i]=2*mn[i]+1-i,f[i]=0;
        for(int i=1;i<=n;++i) if(mn[i]<=i) f[i]=f[mn[i]-1]+1;
        for(int i=1;i<=n;++i) ans+=f[i];
        printf("%lld\n",ans);
    }
    return 0;
}
```

[def_manacher]: https://www.luogu.com.cn/problem/P3805

---

## 作者：cwfxlh (赞：3)

## [CF1827C](https://www.luogu.com.cn/problem/CF1827C)   
不是很难，比这场的 B 好多了。    

考虑对于一个美丽的字符串，它一定有一个唯一的最小偶回文拆分，接下来证明。   

因为对于一个偶回文串，如果其存在一个偶回文串后缀，则其必定可以再次拆分。假设大回文串长度为 $2x$，回文后缀长为 $k$，如果 $k\leq x$，则 $[2x-k+1,2x]$ 与 $[1,k]$ 与 $[k+1,2x-k]$，均为偶回文串，就完成了一次分解。如果长度过半，可以用对称性对称过去解决。    

所以说，如果存在多个最小偶回文拆分（这里最小的定义为段数最多），那么一定存在其中一个的拆分属于另一边某一个字符串的后缀，就不是最小偶回文拆分了（语文不好将就着看吧）。     

于是我们考虑 $dp$。首先预处理出每个点的最长回文半径，因为不会马拉车，所以写了 $\Theta(n\log n)$ 的二分字符串哈希。令 $g_i$ 表示以 $i$ 为结尾的最短偶回文串长度，$f_i$ 表示以 $i$ 结尾的美丽串个数，则有如下转移：  

如果 $g_i=0$，$f_i=0$。   
否则 $f_i=f_{i-g_i}+1$。   

对于 $g_i$ 可以使用线段树来维护，复杂度带一个 $\log$，实现的不好可能会 [TLE](https://codeforc.es/contest/1827/submission/205985055)，于是就写完了，复杂度 $\Theta(n\log n)$。  

[代码](https://codeforc.es/contest/1827/submission/205987760)

---

## 作者：WRuperD (赞：2)

**回文串题还在写马拉车？时代的眼泪！**

涉及算法：PAM。

考虑对于每一个结尾 $i$ 设 $f_i$ 为以 $i$ 结尾的好的字符串的数量。显然的，我们只需要找到以 $i$ 结尾的偶回文串中最短的那个，设其长度为 $x$ 则有 $f_i = f_{i-x} + 1$.

找到以 $i$ 结尾的偶回文串中最短的长度只需要在回文自动机上面跳 $cur$ 的 $fail$ 然后判断当前是否为偶回文串即可。但是这样子复杂度不正确。所以你不用每次暴力跳，你只需要在建图的时候预处理一下即可。

比同名题目好做多了。

[代码](https://codeforces.com/contest/1827/submission/241700005)

---

## 作者：Hisaishi_Kanade (赞：2)

首先一个自然的思路是把 $s$ 划分成若干极小的偶数长度回文区间。

考虑如何去做这个东西，我们先对 $s$ 进行[ manacher 算法](https://oi-wiki.org/string/manacher/)。一个常用的技巧是在原字符串没两个字符之间插入一个不在字符串内的字符 `#`。 

设 $p_i$ 表示以 $i$ 为回文中心，其最大回文半径（当 $s_i$ 为 `#` 时这个回文串长度为偶数）。我们维护目前找到过的回文区间的最大的右端点 $r$，以及他对应的左端点 $l$，接下来我们要求解 $p_i$。

考虑最暴力的做法，暴力拓展 $p_i$ 直到 $i+p_i+1$ 和 $i-p_i-1$ 这两个点不相等。单次的复杂度 $O(n)$。

+ $i\le r$  

令 $i^\prime$ 表示 $i$ 在 $[l,r]$ 的对应端点。当 ${i^\prime}-p_{i^\prime}$ 不小于 $l$ 时，此时对于 $[i-p_{i^\prime}, i+p_{i^\prime}]$ 和 $[{i^\prime}-p_{i^\prime},{i^\prime}+p_{i^\prime}]$ 这两个区间必然是相等的，否则只能确定 $i$ 为中点，$r$ 为右端点的区间和 ${i^\prime}$ 为中点，$l$ 为左端点这个区间相等。

所以这不意味着 $p_i=p_{i^\prime}$，只能通过 $[l,r]$ 的回文确定在 $[l,r]$ 内其相等，而之外的都不能确定。

那么 $p_i\gets \min(p_{i^\prime},r-i)$，然后暴力拓展 $p_i$，正确性是显然的。

+ $i>r$

对于这种情况直接暴力拓展。

+ 复杂度证明

这东西看起来是非常假的，两种情况似乎都会暴力拓展。

但是考虑到那个变化的 $r$，每一次暴力拓展中的 $p_i\gets p_i+1$，其都会自增 $1$！

那么，$r$ 从 $1$ 走到 $n$，也就是暴力拓展中 $p_i$ 的变化次数也是 $n$！

而对于 $i$ 的枚举，其也是显然为 $n$，所以总复杂度 $O(n)$！
 
给出 [P3805](https://www.luogu.com.cn/problem/P3805) 的 AC [代码](https://www.luogu.com.cn/paste/hnyyr7nr)。


+ 本题求解

好，现在我们已经可以求出每个点最大回文半径了，偶数长的话我们限制这个点是 `#` 即可。

好考虑如何求解，设 $f(i)$ 表示 $i$ 结尾的美丽串个数，设 $j$ 表示最靠右的使得 $[i,j]$ 是回文串且中点是个 `#`，则可以得到 $f(i)=f(j-1)+1$，因为任意一个 $f(j-1)$ 里的美丽串都可以接上 $[j,i]$ 使其变成新的美丽串。

考虑如何取维护这个东西，求 $j$ 难，求 $i,j$ 中点就好了嘛。

对于每个为 `#` 的 $s_k$，我们得到了其回文半径 $p_i$ 对吧，则对于 $[k+1,k+p_i]$ 中不为 `#` 的，其在原串中的位置 $i$ 与其所对应的 $j$ 的中点会 $\ge k$。

那么这其实就是一个区间取 $\max$，显然可以通过倒序枚举 `#` 的位置使之转化为将空白的区域覆盖。

而这是什么，是[白雪皑皑](https://www.luogu.com.cn/problem/P2391)，用并查集维护向后最先一个空白的位置，由于每个点只在覆盖时访问一次，并查集复杂度当成常数，总复杂度 $O(n)$。

不过这里用线段树或者其他的什么数据结构应该也可以。 

```cpp 
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static int _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline int read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int N=1e6+5, inf=2e9;
const ll illf=1e18;
int qt, n, i, l, r; ll ans;
char d[N], str[N];
int mj[N], j[N], f[N], p[N];
inline void brute(int i) {while(d[i-p[i]-1]==d[i+p[i]+1]) ++p[i]; return ;}
int fa[N];
inline int find(int x) {while(x!=fa[x]) x=fa[x]=fa[fa[x]]; return x;}
int main()
{
	scanf("%d", &qt);
	while(qt--)
	{
		scanf("%d %s", &n, str+1); rep(i, 1, n) f[i]=0, mj[i]=1e9;
		ans=0;d[0]='@'; rep(i, 1, n) d[i*2]=str[i], d[i*2-1]='#'; d[2*n+1]='#'; d[2*n+2]='$'; n=2*n+1;
		rep(i, 1, n) fa[i]=i;
		int r=0, pos=0; rep(i, 1, n)
		{
			if(i<=r) p[i]=min(r-i, p[2*pos-i]); else p[i]=0;
			brute(i); if(i+(p[i])>r) r=i+p[i], pos=i;
		}
		rep(i, 1, n) fa[i]=i; req(i, n, 1)
		{
			l=(i+1)/2; r=i/2+(p[i]+1)/2;
			pos=find(l);
			while(pos<=r)
			{
				mj[pos]=(i+1)/2;
				pos=fa[pos]=find(pos+1);
			}
			--i;
		} n/=2;
		rep(i, 1, n) j[i]=mj[i]*2-i-1;
		rep(i, 1, n) if(j[i]<=i) ans+=f[i]=f[j[i]-1]+1; printf("%lld\n", ans);
	}
}

```


---

## 作者：sanaka87 (赞：2)

首先可以想到暴力 $\text{dp}$，但是发现暴力 $\text{dp}$ 不仅复杂度是 $O(n^2)$，而且也会算重。那么如何不重不漏而且很快的转移呢？

对于一个回文串，如果它有一个长度 $\le\frac L2$ 的长度为偶数的 $\text{border}$，那么我们肯定可以把它拆分成三部分：左边，右边和中间，这三部分都是回文串。这启发我们想到一个贪心结论：以 $i$ 结尾的 $\text{beautiful string}$ 结尾一定包括**以 $i$ 为右端点的最短回文串，且左边还是一个 $\text{beautiful string}$（或者空）**。那么直接 $\text{dp}_i=1+\text{dp}_{i-l}$ 就做完了。

细思极恐地发现还是有点问题，有没有可能出现这样的情况：左边一个非 $\text{beautiful string}$ 可以和这个最短的以 $i$ 结尾的回文串并在一起形成 $\text{beautiful string}$？

考虑一下这种情况怎么样才会发生。当我们贪心地把 $\text{beautiful string}$ 拆分以后，最右边的串，不是以 $i$ 为右端点的最短回文串，而是另一个包含“以 $i$ 为右端点的最短回文串”的回文串。这样这个大回文串以小回文串作为 $\text{border}$，但是小回文串的长度却 $\ge\frac L2$。我们接下来证明这种情况不存在，也就是说：

> **命题**：如果一个长度为偶数的回文串存在一个长度为偶数的 $\text{border}$，那么一定存在一个长度 $\le\frac L2$ 的 $\text{border}$。

证明：根据 $\text{border}$ 和周期的对应关系，假设存在一个长度 $>\frac L2$ 的 $\text{border}$ $x$，那么 $(L-1)\bmod (L-x)+1$ 一定是 $\text{border}$ 且长度 $<\frac L2$。

这其实就是一个 $\text{border}$ 的经典性质的应用：

> **命题**：一个字符串如果存在 $\text{border}$，那么一定存在长度 $\le\frac L2$ 的 $\text{border}$。

证明完了这个结论我们发现如果如果这种情况真的发生了，那么小回文串一定不是最小的。那么就矛盾了。

于是问题变成如何寻找以 $i$ 结尾的最小回文串。考虑回文自动机，因为其 $\text{fail}$ 树上对应了所有的 $\text{border}$，那么，如果在 $\text{fail}$ 树其到根节点的链上存在一个长度为偶数的字符串，那么肯定可以拆分。在构建回文自动机的时候我们正好可以得到以 $i$ 结尾的最长字符串所在的节点，直接在 $\text{fail}$ 树上维护一个到根节点的最小偶数长度即可。时间复杂度 $O(n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct PAT{
    int las,cnt,mi[2000001],fail[2000001],g[2000001][26],len[2000001];
    ll dp[1000001];
    inline void init(){
    	for (int i=0;i<=cnt;i++){
            fail[i]=len[i]=dp[i]=0;mi[i]=0x3f3f3f3f;memset(g[i],0,sizeof g[i]);
    	}
    	las=0,cnt=1;fail[0]=1;len[1]=-1;mi[0]=mi[1]=0x3f3f3f3f;
    }
    inline void insert(char *a){
        int L=strlen(a+1);
        ll _=0;
        for (int i=0;i<=L;i++) dp[i]=0;
        for (int i=1;i<=L;i++){
            int u=las;
            while (a[i-len[u]-1]!=a[i]) u=fail[u];
            if (!g[u][a[i]-'a']){
                len[++cnt]=len[u]+2;
                int v=fail[u];
                while (a[i-len[v]-1]!=a[i]) v=fail[v];
                fail[cnt]=g[v][a[i]-'a'];
                g[u][a[i]-'a']=cnt;
                if (len[cnt]%2==0) mi[cnt]=min(mi[fail[cnt]],len[cnt]);
                else mi[cnt]=mi[fail[cnt]];
            }
            las=g[u][a[i]-'a'];
            if (mi[las]!=0x3f3f3f3f) dp[i]+=1+dp[i-mi[las]];
            _+=dp[i];
        }
        cout<<_<<endl;
    }
}pat;
char s[1000001];
int n,T;
int main(){
    cin>>T;
    while (T--){
        scanf("%d",&n);
        scanf("%s",s+1);
        pat.init();
        pat.insert(s);
    }
}
```


---

## 作者：Yansuan_HCl (赞：1)

为什么会想到建图啊？？

两个相邻偶回文串之间能拼接，启发我们用一些结构连接相邻的偶回文串。注意不到一个偶回文串的终点可能是下一个偶回文串的起点的前一个点，且这种关系具有传递性。注意不到这样相当于从回文串起点的前一个点跳到回文串的终点，一条路径是一个合法的拼接。

于是可以开始建图。若 $s[l,r]$ 为偶回文串，则将 $l-1$ 连向 $r$。需要对子回文串也进行同样的操作（例如 $l \to r-1$），可以用 [P3295](https://www.luogu.com.cn/problem/P3295) 的技术解决。顺序上有一些不一样，为了实现方便可以把反串拼在原串后面，这样连接就是按顺序的；最后把对称点连起来即可。

```cpp
#include <bits/stdc++.h>
#define ms(x, v) memset(x, v, sizeof(x))
#define il __attribute__((always_inline)) static
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
template <class T> using BS = basic_string<T>;

template <class T> void rd(T& s) {
	int c = getchar(); T f = 1; s = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) { s = s * 10 + (c ^ 48); c = getchar(); }
	s *= f;
}
template <class T, class... Y> void rd(T& x, Y&... y) { rd(x), rd(y...); }
#define meow(...) fprintf(stderr, __VA_ARGS__)
#define Assert(e, v) if (!(e)) exit(v);

// ¿¼ÂÇ½¨Í¼£º¶ÔÓÚÒ»¸öÅ¼»ØÎÄ×Ó´®£¬´Ó l-1 Á¬Ïò r
// Ò»¸öºÏ·¨µÄ×Ö´®ÊÇÒ»ÌõÂ·¾¶
// Ö»ÓÐµ¥Ïò±ß£¬µÈ¼ÛÎÞÏòÍ¼£¬Ò»¸öÁ¬Í¨¿éÑ¡Á½¸öµã
// Çø¼äµãÏòÇø¼äÁ¬±ß

const int N = 1000005;
#define Lg(x) __lg(x)

int n; char s[N];

struct DSU {
	int fa[N], siz[N];
	void init() {
		U (i, 0, n) fa[i] = i, siz[i] = 1;
		siz[0] = 1;
		U (i, n + 1, n * 2) fa[i] = i, siz[i] = 0;
	}
	int get(int p) { for (; p != fa[p]; p = fa[p] = fa[fa[p]]); return p; }
	void merge(int u, int v) {
		u = get(u); v = get(v);
		if (u != v) {
			fa[u] = v;
			siz[v] += siz[u];
		}
	}
};
DSU dsu[21];
void conn(int l, int r, int len) { // Á¬Ïò·´´®µÄÏàÓ¦Î»ÖÃ 
	r = n * 2 + 1 - r;
	int g = Lg(len);
	dsu[g].merge(l, r);
	dsu[g].merge(l + len - (1 << g), r + len - (1 << g));
}
void pushdown(int g) {
	U (i, 0, n * 2 - (1 << g)) {
		int fa = dsu[g].get(i);
		dsu[g - 1].merge(i, fa);
		dsu[g - 1].merge(i + (1 << (g - 1)), fa + (1 << (g - 1)));
	}
}

int r[N]; // ri: ÒÔ i+0.5 ÎªÖÐÐÄµÄ»ØÎÄ°ë¾¶
void manacher() {
	static char t[N]; static int h[N];
	U (i, 1, n) t[i * 2] = s[i], t[i * 2 - 1] = '#';
	t[n * 2 + 1] = '#';
	t[0] = '!'; t[n * 2 + 2] = '@';
	
	for (int i = 1, mid = 0, rad = 0; i <= n * 2 + 1; ++i) {
		h[i] = 1;
		if (i < mid + rad)
			h[i] = max(h[i], min(h[2 * mid - i], mid + rad - i));
		while (t[i + h[i]] == t[i - h[i]] && h[i] < i)
			++h[i];
		if (i + h[i] > mid + rad)
			mid = i, rad = h[i];
	}
	U (i, 0, n)
		r[i] = h[i * 2 + 1] - 1;
}

void solve() {
	U (i, 0, 20)
		dsu[i].init();
	U (i, 0, n) if (r[i]) {
		assert(!(r[i] & 1));
		r[i] /= 2; // ×÷Îª°ë¾¶ 
		int b = i - r[i], e = i + r[i];
		conn(b, e, r[i]);
	}
	U (i, 1, n) dsu[0].merge(i, n * 2 + 1 - i);
	D (i, 20, 1) pushdown(i);
	ll ans = 0;
	U (i, 0, n * 2) if (dsu[0].get(i) == i) {
		ll sz = dsu[0].siz[i];
		ans += sz * (sz - 1) / 2;
	}
	cout << ans << endl;
}

int main() {
	int T; rd(T);
	while (T--) {
		rd(n);
		scanf("%s", s + 1);
		manacher();
		solve();
	}
}
```

---

## 作者：LinkyChristian (赞：1)

观察题目，很容易想到 dp 状态，设 $f_i$ 表示以 $i$ 结尾的所有“好串”个数。

想到我们可以枚举所有的以 $i$ 结尾的偶回文串，设以 $i$ 结尾的偶回文串集合为 $S$，可以列出方程

$$f_i=\sum \limits_{t\in S} f_{i-len_t}+1$$

但这样显然是错的，因为一个偶回文串本身也可能是由多个偶回文串拼接而成的，这样就会重复贡献。

考虑如果一个偶回文串如果拥有一个偶回文串作为其后缀，则一定可以被多个偶回文串拼接而成，反之则必然不能。我们称没有偶回文串作后缀的偶回文串为最简偶回文串。

任务变成了需要找到以每个位置为结尾的最简偶回文串（必然只有一个，否则一定会有一个是另一个的后缀），我们设其长度为 $mn_i$，考虑用 PAM 来解决这个问题。

我们设 $ed_p$ 表示 PAM 上节点 $p$ 的最简偶回文后缀长度，首先让 $ed_p=ed_{fail_p}$，如果此时 $ed_p$ 为 $0$ 且 $len_p$ 为偶数，那么自己就是自己的最简偶回文后缀，使 $ed_p=len_p$，$mn_i$ 直接为长度为 $i$ 的前缀对应的最长回文后缀的最简偶回文后缀即可。

转移公式：

$$
f_i=0 \ (mn_i=0) 
$$

$$
f_i=f_{i-mn_i}+1 (mn_i \neq 0)
$$

代码也很好写

```cpp
#include<bits/stdc++.h>
#define N 500010
using namespace std;
char s[N];
int n,ch[N][26],las,p,q,len[N*26],fail[N*26],tot,ed[N*26],mn[N],f[N];
void init() {
	for(int i=0; i<=n; i++) f[i]=mn[i]=0,memset(ch[i],0,sizeof(ch[i]));
	for(int i=0; i<=tot; i++) ed[i]=0; 
	s[0]=-1,fail[0]=1,las=0;
	len[0]=0,len[1]=-1,tot=1;
}
int nw(int x) {len[++tot]=x; return tot;}
int getfail(int x,int pos) {
	while(s[pos-len[x]-1]!=s[pos]) x=fail[x];
	return x;
}
int read() {
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)) f=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch)) res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return f*res;
}
void ins(int c,int i) {
	p=getfail(las,i);
	if(!ch[p][c]) {
		q=nw(len[p]+2);
		fail[q]=ch[getfail(fail[p],i)][c];
		ed[q]=ed[fail[q]];
		if(!ed[q]&&len[q]%2==0) ed[q]=len[q];
		ch[p][c]=q;
	} las=ch[p][c],mn[i]=ed[las];
}
int main() {
	int T=read();
	while(T--) {
		n=read();
		scanf("%s",s+1);
		init();
		for(int i=1; i<=n; i++) ins(s[i]-'a',i);
		for(int i=1; i<=n; i++) if(mn[i]) f[i]=f[i-mn[i]]+1; 
		long long ans=0;
		for(int i=1; i<=n; i++) ans+=f[i];
		printf("%lld\n",ans); 
	}
}
```


---

## 作者：hhhqx (赞：0)

# CF1827C Palindrome Partition 题解
## 题面
[题目传送门](https://www.luogu.com.cn/problem/CF1827C)。

称一个字符串是好的，当且仅当它是一个长度为偶数的回文串或由若干长度为偶数的回文串拼接而成。

给定一个长度为 $n$ 的字符串 $s$，求有多少 $s$ 的子串是好的。

$ 1 \le n \le 5 \cdot 10^5$，$s$ 仅包含小写字母。
## 与 CSP-S 2023 T2 的区别
千万不要说这两题重了，免得别人来笑话。

举一个例子，`abbcca`，可以思考一下。
## 分析
那么这题多半是只能老老实实去找回文串。考虑使用**回文树**。

先来分析回文串的性质。
- 设 $s[l,r]$ 为回文串，若 $s[x,r]$ 也为回文串（$\left\lfloor \frac{l+r+1}{2}\right\rfloor \le x \le r$）。
- 则 $s[l,l+(r-x+1)-1]$ 也为回文串（因为整体回文，所以右边会问则左边也回文）。
- 则 $s[l+(r-x+1),x-1]$ 也为回文串（因为整体回文）。

如果通过第一个假设，判断 $s[l,r]$ 是好的就不需要判断 $s[l,r]$ 是否回文，只用判断它内部是否可以组成。
## 思路
我们知道在字符串位置 $i$，在回文树位置 $j$，只用不断跳后缀链接，设当前位置回文串的长度为 $l$，则 $s[i-l+1,i]$ 为回文串。

设对于所有 $l$ 为**偶数**，组成一个序列  $L_1<L_2<L_3<\cdots<L_k$，那么 $s[i-L_x+1,i]$ （$2 \le x \le k$）必定可以被除自己的回文串组成（通过分析容易知道）。

那么我们只用对于每个 $i$ 找到 $L_1$（可以用路径压缩来解决满足复杂度要求），则 $dp_i=dp_{L_1}+1$，若没有 $L_1$，则 $dp_i=0$。

最后答案为 $\sum_{x=1}^{n}{dp_x}$。

时间复杂度 $O(n \log n)$，瓶颈在找到 $L_1$。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using Pair = pair<LL, LL>;

const int MAXN = 1e6 + 3;

int n;
string s;
int trie[MAXN][26], cv = 1, len[MAXN], _len[MAXN], pos[MAXN]/*原串中出现位置*/, nxt[MAXN]/*后缀链接*/;
int fa[MAXN];
LL dp[MAXN], ans = 0;

int Getf(int x){
  if(fa[x] <= 1|| fa[x] == x || Getf(fa[x]) == 0 || _len[Getf(fa[x])] == 0){
    return (len[x] % 2 == 0 ? fa[x] = x : fa[x] = 0);
  }else return fa[x] = Getf(fa[x]);
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  cin >> T;
  while(T--){
    cin >> n >> s, s = " " + s;
    for(int i = 0; i <= cv; i++){
      for(int col = 0; col < 26; col++) trie[i][col] = 0;
    }
    cv = 1;
    ans = 0;
    _len[0] = len[0] = -1, nxt[0] = 0, _len[1] = len[1] = 0, nxt[1] = 0;
    for(int i = 1, j = 1 /* i-1 的后缀的最长回文后缀对应回文树上的节点编号 */; i <= n; i++){
      while(s[i] != s[i - len[j] - 1]) j = nxt[j];
      if(!trie[j][s[i] - 'a']){
        trie[j][s[i] - 'a'] = ++cv;
        _len[cv] = len[cv] = len[j] + 2;
        pos[cv] = i - len[cv] + 1;
        for(int &k = (nxt[cv] = nxt[j]); s[i] != s[i - len[k] - 1]; k = nxt[k]);
        // 也可以写成 for(int &k = nxt[cv] = nxt[j]; s[i] != s[i - len[k] - 1]; k = nxt[k]);

        if(len[cv] > 1) fa[cv] = nxt[cv] = trie[nxt[cv]][s[i] - 'a'];
        else fa[cv] = nxt[cv] = 1;
      }
      j = trie[j][s[i] - 'a'];
      if(Getf(j) != 0) _len[j] = _len[Getf(j)];
      else _len[j] = 0;
      dp[i] = (_len[j] == 0 ? 0 : dp[i - _len[j]] + 1), ans += dp[i];
    }
    cout << ans << "\n";
  }
  return 0;
}
/*
6
abaaba
1 2 1 1 1
1 2 0 1 1**
2 3 1 1 1
2 3 0 1 1**
3 4 2 2 3
3 4 0 2 3**
4 5 2 2 2
*/
```

---

## 作者：AtomAlpaca (赞：0)

## 题意
简要题意：称一个字符串是好的，当且仅当这个是偶回文串，或由多个偶回文串拼接得到。给定字符串 $s$，求 $s$ 有多少好的子串。

$|s| \le 5\times10^5$。

## 题解

设 $f_i$ 为结尾位置为 $i$ 的好串数量，$g_i$ 为结尾位置为 $i$ 的极短偶回文串的长度，如果不存在 $g_i$ 为 $0$。

考虑到当且仅当向一个好串后方接上一个偶回文串，这个串依然是好串；且极短偶回文串本身也是一个好串，我们可以写出转移方程：

$$
f_i =
\left\{ 

\begin{aligned} 

& 0, &if \ g_i=0

\\

&f_{i-g_i} + 1, &otherwise

\end{aligned}

 \right.
$$

因为每次向后面加上的都是极短的偶回文串，这种 dp 方式一定是不重不漏的。答案即为 $\sum_{i=1}^{|s|}{f_i}$。

现在问题转化为令快速求 $g$。考虑每次求 $g$ 其实就是找字符串的最短的一段偶后缀，这和回文自动机的构造过程很相似。我们考虑对自动机上每个节点维护一个变量 $h$，表示这个节点代表的回文串的短偶回文串长度，那么每次插入完一个字符，这个位置的 $g$ 就等于 $h_{last}$。

考虑如何维护 $h$。只有两种情况对 $h$ 有贡献，一是这个节点有一段真后缀是偶回文串，此时 $h_u=h_{fail_u}$；二是自己本身是一个偶回文串，此时 $h_u=len_u$。

整理一下：

$$
h_u =
\left\{ 

\begin{aligned} 

& h_{fail_u}, &h_{fail_u} \ne 0

\\

& len_u, & f_{fail_u} = 0\ and\ len_u \operatorname {mod} 2=0

\\

&0, &otherwise

\end{aligned}

 \right.
$$
在插入字符时维护即可。由于回文自动机复杂度是线性的，整体复杂度为 $O(|s|)$。

## 代码

个人的回文自动机是按照 SAM 的写法改的，和主流写法不太一样，可能看起来有点奇怪。

``` c++
#include <bits/stdc++.h>

typedef long long ll;

const int MAX = 5e5 + 5;
ll T, n, lst, tot, ans;
ll h[MAX], g[MAX], f[MAX];
char s[MAX];

struct E { ll l, f, c[27]; } t[MAX];

void init()
{
  lst = tot = 2;
  t[1].f = t[2].f = 1;
  t[1].l = -1; t[2].l = 0;
}

void clear()
{
  ans = 0;
  for (int i = 1; i <= tot; ++i)
  {
    t[i].f = t[i].l = 0; h[i] = 0;
    for (int j = 0; j <= 26; ++j) { t[i].c[j] = 0; }
  }
  for (int i = 1; i <= n; ++i) { f[i] = g[i] = 0; }
  init();
}

void add(int k, int c)
{
  int p = lst;
  while (s[k - t[p].l - 1] - 'a' != c) { p = t[p].f; }
  if (t[p].c[c]) { lst = t[p].c[c]; g[k] = h[lst]; return ; }
  int np = ++tot, q = t[p].f;
  while (s[k - t[q].l - 1] - 'a' != c) { q = t[q].f; }
  if (t[q].c[c]) { t[np].f = t[q].c[c]; } else { t[np].f = 2; }
  t[p].c[c] = np; t[np].l = t[p].l + 2;
  h[np] = h[t[np].f]; if (!h[np] and !(t[np].l & 1)) { h[np] = t[np].l; }
  lst = t[p].c[c]; g[k] = h[lst];
}

void solve()
{
  clear();
  scanf("%lld%s", &n, s + 1);
  for (int i = 1; i <= n; ++i) { add(i, s[i] - 'a'); }
  for (int i = 1; i <= n; ++i) { if (g[i]) { f[i] = 1 + f[i - g[i]]; } ans += f[i]; }
  printf("%lld\n", ans);
}

int main()
{
  scanf("%lld", &T); while (T--) { solve(); }
}
```

---

