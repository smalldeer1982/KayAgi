# Moscow Gorillas

## 题目描述

In winter, the inhabitants of the Moscow Zoo are very bored, in particular, it concerns gorillas. You decided to entertain them and brought a permutation $ p $ of length $ n $ to the zoo.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

The gorillas had their own permutation $ q $ of length $ n $ . They suggested that you count the number of pairs of integers $ l, r $ ( $ 1 \le l \le r \le n $ ) such that $ \operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r])=\operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r]) $ .

The $ \operatorname{MEX} $ of the sequence is the minimum integer positive number missing from this sequence. For example, $ \operatorname{MEX}([1, 3]) = 2 $ , $ \operatorname{MEX}([5]) = 1 $ , $ \operatorname{MEX}([3, 1, 2, 6]) = 4 $ .

You do not want to risk your health, so you will not dare to refuse the gorillas.

## 说明/提示

In the first example, two segments are correct – $ [1, 3] $ with $ \operatorname{MEX} $ equal to $ 4 $ in both arrays and $ [3, 3] $ with $ \operatorname{MEX} $ equal to $ 1 $ in both of arrays.

In the second example, for example, the segment $ [1, 4] $ is correct, and the segment $ [6, 7] $ isn't correct, because $ \operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4) $ .

## 样例 #1

### 输入

```
3
1 3 2
2 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4```

### 输出

```
16```

## 样例 #3

### 输入

```
6
1 2 3 4 5 6
6 5 4 3 2 1```

### 输出

```
11```

# 题解

## 作者：TernaryTree (赞：8)

阳间 CF 赛时切 D 祭。

***

首先我们求出两个排列中每个数出现的位置 $s,t$。

考虑枚举 $\operatorname{mex}$（以下简称 $m$）。$m=1$ 时在 $p$ 排列中 $1$ 出现在 $s_1$ 的位置，$q$ 排列中 $1$ 出现在 $t_1$。不妨设 $s_1\le t_1$（如果不满足，直接交换两者即可，因为此时交换 $p,q$ 效果等价）。那么此时，显然子段不可以跨过 $s_1$ 和 $t_1$。来张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rdswmgfc.png)

此时我们可以在 $[1,s_1)$，$(s_1,t_1)$，$(t_1,n]$ 中分别任意选择左端点与右端点，排列组合一下即可。这一段的核心代码：

```cpp
int k1 = s[1], k2 = t[1];
if (k1 > k2) swap(k1, k2);
if (1 <= k1 - 1) {
    ans += k1 * (k1 - 1) / 2;
}
if (k2 + 1 <= n) {
    ans += (n - k2 + 1) * (n - k2) / 2;
}
if (k1 < k2) {
    ans += (k2 - k1 - 1) * (k2 - k1) / 2;
}
```

接下来考虑枚举 $m$ 到 $i$。由 $m$ 的性质可以得到，$1\sim i-1$ 的所有数都必须出现在区间内，而 $i$ 不能出现。记 $1\sim i-1$ 中所有数在 $p,q$ 中最左的与最右的，这是 $i=5$ 的一张示意图：

![](https://cdn.luogu.com.cn/upload/image_hosting/v64xqr05.png)

也就是说如果我们要选择一个区间使得 $m=i$ 的话，那么 $1\sim i-1$ 都必须被覆盖，也就是说左端点只能在 $l$ 左边或者 $l$ 自己，右端点只能在 $r$ 右边或者 $r$ 自己。

但是还有一个条件，是选定的区间中 $i$ 不能存在，否则 $m\gt i$。$p$ 中 $i$ 出现位置为 $s_i$，$q$ 中 $i$ 出现位置为 $t_i$，若前者较大则交换。接下来是分类讨论：

- #### $l\le s_i\le r$ 或 $l\le t_i\le r$

  不可能满足条件。因为合法的区间既要包含 $[l,r]$ 又不能包含 $i$，故更新 $l,r$，舍去。
  
- #### $1\le s_i,t_i\lt l$

   ![](https://cdn.luogu.com.cn/upload/image_hosting/z9xmv9ar.png)
  
  显然，左端点取值范围为 $(\max(s_i,t_i),l]$。右端点取值范围为 $[r,n]$。方案数为 $(n-r+1)\times (l-\max(s_i,t_i))$。
  
- #### $r\le s_i,t_i\le n$

   ![](https://cdn.luogu.com.cn/upload/image_hosting/edgimirg.png)
   
  与上一种情况同理，方案数为 $l\times (\min(s_i,t_i)-r)$。
  
- #### $1\le s_i \lt l$ 且 $r\lt t_i\le n$

   ![](https://cdn.luogu.com.cn/upload/image_hosting/6qkqomvg.png)
   
  显然左端点取值范围为 $(s_i,l]$，右端点为 $[r,t_i)$。方案数为 $(l-s_i)\times (t_i-r)$。
  
每次 $l,r$ 更新将自身与 $s_i,t_i$ 分别取 $\min$ 和 $\max$ 即可，最后答案要加上 $1$，因为我们统计的是 $1\le m\le n$ 的答案，但是 $m=n+1$ 有一种情况，就是整个排列全选。

丑陋的赛时代码：

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 2e5 + 1;

int n, ans;
int p[maxn];
int q[maxn];
int s[maxn];
int t[maxn];

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        s[p[i]] = i;
    }for (int i = 1; i <= n; i++) {
        cin >> q[i];
        t[q[i]] = i;
    }
    int k1 = s[1], k2 = t[1];
    if (k1 > k2) swap(k1, k2);
    if (1 <= k1 - 1) {
        ans += k1 * (k1 - 1) / 2;
    }
    if (k2 + 1 <= n) {
        ans += (n - k2 + 1) * (n - k2) / 2;
    }
    if (k1 < k2) {
        ans += (k2 - k1 - 1) * (k2 - k1) / 2;
    }
    int l = k1, r = k2;
    for (int m = 2; m <= n; m++) {
        k1 = s[m], k2 = t[m];
        if (k1 > k2) swap(k1, k2);
        if (l <= k1 && k1 <= r || l <= k2 && k2 <= r) {
            
        l = min(l, k1);
        r = max(r, k2);
            continue;
        }
        if (k1 < l && k2 < l) {
            ans += (n - r + 1) * (l - k2);
        }
        if (k1 > r && k2 > r) {
            ans += (k1 - r) * l;
        }
        if (k1 < l && k2 > r) {
            ans += (l - k1) * (k2 - r);
        }
        l = min(l, k1);
        r = max(r, k2);
    }
    cout << ans+1;
    return 0;
}
```

---

## 作者：lizhous (赞：4)

[洛谷](https://www.luogu.com.cn/problem/CF1793D)

[CF](http://codeforces.com/problemset/problem/1793/D)

## 分析
MEX 这个东西不太好做。

一种比较套路的想法是枚举 MEX，统计满足要求的区间，在这题上正好适用。

设我们枚举的 MEX 为 $M$，我们考虑什么情况下 $\text{MEX}([p_l,p_{l+1},\cdots,p_r])=\text{MEX}([q_l,q_{l+1},\cdots,q_r])=M$。显然 $[p_l,p_{l+1},\cdots,p_r]$ 与 $[q_l,q_{l+1},\cdots,q_r]$ 都包含所有 $1$ 至 $M-1$ 的数且都不包含 $M$。

考虑第一个条件，找到最短的区间满足该条件，因为两个序列都是排列，同一个数不会出现两次，所以所有完全包含该区间的区间满足要求，其余都不满足要求。

考虑第二个条件，我们发现两个值为 $M$ 的数将区间划分成三段，跨段取的两个区间中必然有一个存在 $M$，而不跨段就必然不存在 $M$。

满足上述条件，我们可以求出满足要求的区间左端点取值范围 $[lmi,lma]$ 和右端点取值范围 $[rmi,rma]$，统计即可。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
int T,n,a[200001],b[200001],na[200001],nb[200001],l,r,ans;
int get(int l,int r) //左右端点在[l,r]内的区间计数
{
	if(l>r) return 0;
	return (r-l+2)*(r-l+1)/2;
}
int geter(int l1,int r1,int l2,int r2) //左右端点的取值范围，求出满足条件的区间个数
{
	return (r1-l1+1)*(r2-l2+1);
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		na[a[i]]=i; //桶存，方便后续处理
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&b[i]);
		nb[b[i]]=i;
	}
	ans=0;
   //MEX为1的区间计数
	ans+=get(1,min(na[1],nb[1])-1);
	ans+=get(min(na[1],nb[1])+1,max(na[1],nb[1])-1);
	ans+=get(max(na[1],nb[1])+1,n);
	l=min(na[1],nb[1]);//必须包含的区间处理
	r=max(na[1],nb[1]);
	for(int i=2;i<=n;i++)
	{
		int ll=min(na[i],nb[i]),rr=max(na[i],nb[i]);
		if(r<ll) //包含区间在左边点的左边
		{
			ans+=geter(1,l,r,ll-1);
		}
		if(l>ll&&r<rr) //包含区间在中间
		{
			ans+=geter(ll+1,l,r,rr-1);
		}
		if(l>rr) //包含区间在右边
		{
			ans+=geter(rr+1,l,r,n);
		}
		l=min(l,ll);
		r=max(r,rr);
	}
	cout<<ans+1; //要加上MEX为n+1的情况
}
```
很好理解

---

## 作者：寻逍遥2006 (赞：2)

记在两个排列中 $i$ 的位置分别在 $l_i$ 和 $r_i$ ，其中 $l_i \leqslant r_i$ 。

考虑 $\operatorname{MEX}$ 的性质：在不包含 $1$ 的情况之下，无论如何，答案为 $1$ 。

所以最直观的考虑就是先看两个数列中 $1$ 的情况，只要不包含这两个 $1$ 的 $\operatorname{MEX}$ 必然是 $1$ ，具体分别考虑在 $l_1$ 左侧，在 $l_1$ 和 $r_1$ 之间，在 $r_1$ 右侧即可。

这样子，我们就可以尝试依次考虑 $\operatorname{MEX}=2,3\dots n$ 的情况。

例如 $\operatorname{MEX}=2$ 时，这个区间必然会包含 $l_1$ 和 $r_1$ ，也就是包含区间 $[l_1,r_1]$ ，但同时它又不能包含两个 $2$ ，发现只有在 $[l_2,r_2]\cap[l_1,r_1]=\varnothing$ 或 $l_2<l_1\leqslant r_1<r_2$ 是才可能成立。也是分为三种情况，分别讨论即可。

因为接下来的 $\operatorname{MEX}$ 需要包含 $1$ 和 $2$ ，则取 $L=\min(l_1,l_2)$ 和 $R=\max(r_1,r_2)$ 为新的边界即可。

最后需要加上 $\operatorname{MEX}=n+1$ 为唯一一种情况 $[1,n]$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int Qread()
{
	int x=0;bool f=false;char ch=getchar();
	while(ch<'0'||ch>'9') f|=('-'==ch),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return f?-x:x; 
}
int n,l,r,L,R;
long long ans;
int p[200010],q[200010];
int locp[200010],locq[200010];
int main()
{
	n=Qread();
	for(int i=1;i<=n;i++) locp[p[i]=Qread()]=i;
	for(int i=1;i<=n;i++) locq[q[i]=Qread()]=i;
	l=min(locp[1],locq[1]),r=max(locp[1],locq[1]);
	ans=1ll*l*(l-1)/2+1ll*(n-r)*(n-r+1)/2+1ll*(r-l-1)*(r-l)/2;
	for(int i=2;i<=n;i++)
	{
		L=min(locp[i],locq[i]),R=max(locp[i],locq[i]);
		if(L<l&&r<R) ans+=1ll*(l-L)*(R-r);
		else if(R<l) ans+=1ll*(l-R)*(n-r+1);
		else if(r<L) ans+=1ll*l*(L-r);
		l=min(l,L),r=max(r,R);
	}
	ans+=1;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：hcywoi (赞：1)

### 【题意】

- 给定两个长度为 $n$ 的排列 $p, q$。
- 求有多少对数对 $(l, r)(1\le l\le r\le n)$ 满足 $\operatorname{MEX}(p_l, p_{l+1},\cdots, p_{r})=\operatorname{MEX}(q_l, q_{l+1},\cdots, q_{r})$。

### Solution

- 我们枚举 $\operatorname{mex}(2\le \operatorname{mex}\le n+1)$。
- 如果区间 $l\sim r$ 合法，则满足 $l\sim r$ 中, $1\sim \operatorname{mex}-1$ 都出现，且 $\operatorname{mex}$ 没有出现。
- 枚举过程中记录 $\operatorname{maxl}, \operatorname{minr}$，$\operatorname{maxl}$ 表示满足 $1\sim \operatorname{mex}-1$ 都出现的最大 $l$，$\operatorname{minr}$ 也同理。
- 对于一个 $\operatorname{mex}$，求出 $\operatorname{minl}, \operatorname{maxr}$，分别表示不包含 $\operatorname{mex}$ 的最小 $l$ 和不包含 $\operatorname{mex}$ 的最大 $r$。
- 这个 $\operatorname{mex}$ 对答案的贡献为 $(\operatorname{maxl} - \operatorname{minl}+1)\times (\operatorname{maxr}-\operatorname{minr}+1)$。
- 最后特判 $\operatorname{mex}=1$ 的情况即可。

[代码。](https://codeforces.com/contest/1793/submission/194182057)

---

## 作者：zac2010 (赞：1)

由于给的是个排列，做法是从 $1$ 到 $n$ 去考虑每个数会作为多少个区间缺少的数中的最小值。我们的顺序是从 $1$ 开始从小到大。

首先，我们能通过映射得到 $ia$ 以及 $ib$ 也就是当前数值分别在 $p$ 和 $q$ 两个数组中的位置。

接着可得缺少当前值 $x$ 的区间必定是不包含 $ia$ 和 $ib$ 两个位置的区间，而这样的区间的个数可以通过计算得到，比如说一个 $n$ 是 $7$ 的序列，数值 $1$ 在第一个排列中位于 $4$ 的位置，在第二个排列中位于 $6$ 的位置，那么合法的区间就是 $1 \le l,r < 4$ 以及 $4 < l,r < 6$ 和 $6 < l,r \le 7$ 的。

最后要考虑怎么使 $i$ 变成没出现过的正整数中最小的，我们只需要区间包含 $1$ 到 $i-1$ 中的所有数即可。

别忘加上 $l=1$ 且 $r=n$ 的情况，最小没出现过的正整数是 $n+1$ 所以对答案有 $1$ 的贡献。

[代码](https://codeforces.com/contest/1793/submission/193464301)。

---

## 作者：Feyn (赞：1)

考场上脑瘫了交了 N 发。

显然考虑两个排列中满足 $\text{MEX}=x$ 的区间有哪些。显然这个区间不能包含 $x$，然后这个区间必须包含 $1\dots x-1$ 中的所有数，否则这个区间的 $\text{MEX}$ 就会小于 $x$。于是记这个排列中 $x$ 的位置是 $p$，$1\dots x-1$ 中最靠前的位置是 $a$，最靠后的位置是 $b$，那么一个合法的区间 $[l,r]$ 一定满足 $l\le a\le b\le r$ 并且 $l>p$ 或者 $r<p$。于是就可以求出一个合法区间左右端点可能的取值范围，然后对另一个排列也这么做一次，那么这部分的答案就是两个排列左端点取值范围的交集乘上右端点取值范围的交集，比较好理解。然后就是 $\text{MEX}=1$ 的部分需要稍微特殊处理一下。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long 
using namespace std;
const int N=200010;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,a[N],b[N];

struct node{
	int xl,xr,yl,yr;
}p[N],q[N];

int mn[N],mx[N],pl[N];
void solve(int c[],node w[]){
	for(int i=1;i<=m;i++)pl[c[i]]=i;
	int nowMin=1e9,nowMax=-1;
	for(int i=1;i<=m;i++){
		if(nowMin>pl[i])w[i]=(node){pl[i]+1,nowMin,nowMax,m};
		if(nowMax<pl[i])w[i]=(node){1,nowMin,nowMax,pl[i]-1};
		nowMin=min(nowMin,pl[i]);
		nowMax=max(nowMax,pl[i]);
	}
}

inline int sol(int xl,int xr,int yl,int yr){
	if(xl<=0||xr<=0||yl<=0||yr<=0)return 0;
	return max(0ll,min(xr,yr)-max(xl,yl)+1);
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);
	for(int i=1;i<=m;i++)read(a[i]);
	for(int i=1;i<=m;i++)read(b[i]);
	solve(a,p);solve(b,q);int ans=1;
	for(int i=2;i<=m;i++){
		ans+=sol(p[i].xl,p[i].xr,q[i].xl,q[i].xr)
			*sol(p[i].yl,p[i].yr,q[i].yl,q[i].yr);
	}
	for(int i=1;i<=m;i++){
		if(a[i]!=1)continue;
		for(int j=1;j<=m;j++){
			if(b[j]!=1)continue;
			int pre=min(i-1,j-1),suf=min(m-i,m-j),mid=max(0ll,max(j-i,i-j)-1);
			ans+=pre*(pre+1)/2+suf*(suf+1)/2+mid*(mid+1)/2;
		}
	}
	printf("%lld\n",ans);
	
	return 0;
}
```

---

## 作者：_Fatalis_ (赞：0)

这是一道 MEX 相关问题，但解决这道题目的方法也许以后在别处能用得到。

简单来说，$\text{MEX}$ 是一个深奥莫测的黑盒子。丢进去一个 $(l, r)$ 很难通过简单的分析或处理得到 $\text{MEX}$ 的值。

于是，我们反向思考，既然很难分析或计算出 $\text{MEX}$ 的值，那不如反过来枚举在不同 $\text{MEX}$ 值下的情况总数。正好，本题目要求统计方案数，正好适合这种方法。

更进一步分析，对于一个 $\text{MEX}$ 值，仅仅要求在区间 $[l, r]$ 中，存在 $[1, \text{MEX})$ 且不存在 $\text{MEX}$。

为了 $O(1)$ 统计区间方案数，一种常见的思想：计算边界可能，结合统计。

本题中，首先边界必须完全包含 $[1, \text{MEX})$。这一步可以随着 $\text{MEX}$ 的增加逐步移动双指针完成。

其次，边界不能跨越 $\text{MEX}$。于是分析题目，序列中会出现两个位置的 $\text{MEX}$，将整个序列划分为三块。只要边界不跨越这三块的边界，都算正确。

![](https://cdn.luogu.com.cn/upload/image_hosting/povzmskq.png)

如图所示。

于是，$O(1)$ 统计，$O(n)$ 模拟，总计 $O(n)$。

参考代码：

```cpp
// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

int n;
int a[200005], amap[200005];
int b[200005], bmap[200005];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 0; i < n; i++) {
        read(a[i]); amap[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        read(b[i]); bmap[b[i]] = i;
    }

    int ans = 1; // [1, n]
    int l = 11451419, r = -11451419;

    // count MEX != 1
    for (int i = 1; i < n; i++) {
        int MEX = i + 1; // i hate MEX
        l = std::min(l, amap[i]);
        l = std::min(l, bmap[i]); 
        r = std::max(r, amap[i]);
        r = std::max(r, bmap[i]);
        // now we get [l, r] that valid for MEX -1.

        int M1 = std::min(amap[MEX], bmap[MEX]), M2 = std::max(amap[MEX], bmap[MEX]);
        // then [0, M1 - 1], [M1 + 1, M2 - 1], [M2 + 1, n - 1];
        // for three square
        
        if (l >= 0 && r < M1) { // all in (1)
            ans += (l - 0 + 1) * (M1 - 1 - r + 1);
        } if (l > M1 && r < M2) { // all in (2)
            ans += (l - (M1 + 1) + 1) * (M2 - 1 - r + 1);
        } if (l > M2 && r < n) {
            ans += (l - (M2 + 1) + 1) * (n - 1 - r + 1);
        }
    }

    // count MEX = 1
    int M1 = std::min(amap[1], bmap[1]), M2 = std::max(amap[1], bmap[1]);

    ans += M1 * (M1 - 1) / 2 + M1;
    ans += (M2 - M1 - 1) * (M2 - M1 - 2) / 2 + (M2 - M1 - 1
    ans += (n - M2 - 1) * (n - M2 - 2) / 2 + (n - M2 - 1);

    printf("%lld\n", ans);
    return 0;
}

```

---

最近的状态真的需要调整。做题的感觉需要重新找回，希望今年能不再遗憾 归终。

2 月份，6 月中考，10-11 月 CSP。

两年的遗憾，我理应拿回属于我的自豪。

---

