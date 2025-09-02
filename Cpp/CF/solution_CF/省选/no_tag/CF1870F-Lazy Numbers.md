# Lazy Numbers

## 题目描述

You are given positive integers $ n $ and $ k $ . For each number from $ 1 $ to $ n $ , we write its representation in the number system with base $ k $ (without leading zeros) and then sort the resulting array in lexicographic order as strings. In the sorted array, we number the elements from $ 1 $ to $ n $ (i.e., indexing starts from $ 1 $ ). Find the number of values $ i $ such that the representation of number $ i $ is at the $ i $ -th position in the sorted array of representations.

Examples of representations: $ 1 $ in any number system is equal to $ 1 $ , $ 7 $ with $ k = 3 $ is written as $ 21 $ , and $ 81 $ with $ k = 9 $ is written as $ 100 $ .

## 说明/提示

In the first test case, for numbers $ 1 $ and $ 2 $ , their representations are at positions $ 1 $ and $ 2 $ respectively.

In the second test case, the sorted array is $ [1_2 = 1, 10_2 = 2, 100_2 = 4, 11_2 = 3] $ , and only the representations of numbers $ 1 $ and $ 2 $ are at the required positions.

In the third test case, the sorted array is $ [1_4 = 1, 10_4 = 4, 11_4 = 5, 12_4 = 6, 2_4 = 2, 3_4 = 3] $ , and only the number $ 1 $ is at its position.

## 样例 #1

### 输入

```
8
2 2
4 2
6 4
33 2
532 13
780011804570805480 3788
366364720306464627 4702032149561577
293940402103595405 2```

### 输出

```
2
2
1
3
1
3789
1
7```

# 题解

## 作者：imsaileach (赞：9)

## CF 1870 F - Lazy Numbers

### 题意

给定 $n,k$ ，设 $rank_i$ 表示 $i$ 的无前导 $0$ 的 $k$ 进制串在 $[1,n]$ 所有数的无前导 $0$ 的 $k$ 进制串中的字典序排名（从小到大）。求 $rank_i=i,i\in [1,n]$ 的 $i$ 的个数。

$n,k \le 10^{18}$

### 思路

如果把 $[1,n]$ 的所有数以 $k$ 进制加入 trie 树（高位在深度低处），并钦定每个点的 $k$ 个分支按从小到大的顺序从左往右排列。再钦定每种遍历顺序都需要从左到右（遍历不包含 trie 树的根）。那么显然某个点所代表的数一定等于这个点的 BFS 序。又由字典序的定义，可知这个点所代表的数的 $rank$ 一定等于这个点的 DFS 序。所以我们相当于要在 trie 树上找 BFS 序等于 DFS 序的点的个数。

然后我们观察 trie 树的每一层的点，发现从左往右相邻点的 BFS 序一定增加 $1$，DFS 序一定增加 $\ge 1$，所以 DFS 序和 BFS 序的差在同一层中从左往右一定单调不减。所以我们可以对于每一层二分，找到中间存在的一段差全为 $0$ 的区间并统计答案。

所以压力给到求一个点的 DFS 序。了解到有人这里用了数位 DP，但其实可以直接利用 trie 树的形态统计字典序小于这个点的数的个数，即为 DFS 序：

1. 从 trie 树根部到这个点的链上的任意一点，它的分支（在 $[0,k)$ 中选择）只要小于它在链上所选的分支，那么这个分支的子树中的所有点都满足字典序小于我们想求 DFS 序的点，可以统计答案。
2. 从 trie 树根部到这个点的链上的非根，非这个点本身的一个点一定满足字典序小于我们想求 DFS 序的点（为其前缀，且不为整个串）。
3. 可以发现除了如上两种点需要被统计外，没有其他点需要被统计。

简单的说，我们可以在这个进制串后面补一些 $0$ 使这个串的长度等于 trie 树的深度，而显然 trie 树上这个进制串形成的链的左侧的所有点都满足条件，以及本身进制串的非空前缀（长度小于这个进制串本身）所代表的点也满足条件。

所以我们可以在 $O(\log_k{n})$ 的时间内求出一个点的 DFS 序。

在考虑上二分、枚举 trie 树每一层的循环以及多测，总的时间复杂度为 $O(T\log_2(n)\log_k^2(n))$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define i32 int
#define i64 long long
#define i128 __int128_t
i32 T, eu, bu;
i128 n, k, ls[70], rs[70], Ans;
i128 b[70];
i128 read (){
    i128 a = 0;
    char c = getchar ();
    while (c < '0' || c > '9')
        c = getchar ();
    while (c >= '0' && c <= '9'){
        a = (a << 3) + (a << 1) + c - '0';
        c = getchar ();
    }
    return a;
}
void write (i128 p){
    if (p > (i128) 9)
        write (p / 10);
    putchar (p % 10 + '0');
}
i128 Calc (i128 x){
    i128 res = 0, pre = 0;
    bu = 0;
    while (x > 0){
        b[++ bu] = x % k;
        x /= k;
    }
    for (i32 i = 1;i <= bu - i;++ i)
        swap (b[i], b[bu - i + 1]);
    for (i32 i = 1;i <= bu;++ i){
        pre = pre * k + b[i];
        res += min (pre, rs[i]) - ls[i] + 1;
    }
    for (i32 i = bu + 1;i <= eu;++ i){
        pre *= k;
        res += min (pre - 1, rs[i]) - ls[i] + 1;
    }
    return res;
}
i32 main (){
    T = (i32) read ();
    while (T --){
        n = read ();
        k = read ();
        eu = 0;
        Ans = (i128) 0;
        for (i128 pw = 1;pw <= n;pw *= k){
            ++ eu;
            ls[eu] = pw;
            rs[eu] = min (pw * k - (i128) 1, n);
        }
        for (i128 i = 1;i <= eu;++ i){
            i128 L, R, l0 = 0, r0 = 0, mid, res;
            L = ls[i], R = rs[i];
            while (L <= R){
                mid = (L + R) >> 1;
                res = Calc (mid) - mid;
                if (res == (i128) 0)
                    l0 = mid;
                if (res < (i128) 0)
                    L = mid + 1;
                else
                    R = mid - 1;
            }
            if (l0 == 0)
                continue;
            L = ls[i], R = rs[i];
            while (L <= R){
                mid = (L + R) >> 1;
                res = Calc (mid) - mid;
                if (res == 0)
                    r0 = mid;
                if (res > 0)
                    R = mid - 1;
                else
                    L = mid + 1;
            }
            Ans += r0 - l0 + (i128) 1;
        }
        write (Ans);
        puts ("");
    }
    return 0;
}
```





---

## 作者：Hkueen (赞：6)

# [[CF1870F] Lazy Numbers](https://codeforces.com/problemset/problem/1870/F)

## 0. 题意

给定一个 $n$ 和一个 $k\ (n,k\le 10^{18})$，要求把从 $1$ 到 $n$ 每个数转化成 $k$ 进制，并对新序列进行字典序从小到大排序。输出原序列上和新序列上排名相同的数的数量。多测 $T\ (T\le 1000)$ 组。

---

## 1. 正文

注意到字典序这个东西，这很容易令人联想到字典树。

我们尝试把每个数放进字典树里：

比如 $n=20,k=2$，此时建出的树如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/88es5qgm.png)

惊喜地发现，一个点的 BFS 序就等于它的十进制大小；

而一个点的 DFS 序则对应它 $k$ 进制下的字典序大小。

**原问题转化成求满足 $dfn_u=bfn_u$ 的数量。**

---

在字典树的每一层中，从 $x$ 到 $x+1$，BFS 序一定增加 $1$，DFS 序的增量则 $\ge 1$。

因此，每一层的 $dfn_u-bfn_u$ 值组成的序列单调不降。

**我们只需要在每一层二分得到 $dfn_u-bfn_u=0$ 的区间大小即可。**

---

现在的问题只剩下怎么快速求得 $dfn_u-bfn_u$ 的值。

$bfn$ 的值就等于它本身。

考虑 $dfn$，

继续观察刚刚这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/88es5qgm.png)

比如我现在要求 $3$ 的 $dfn$ 序：

先把 $3$ 这个数 $k$ 进制拆分，得到 $(11)_2$。

考虑序列的第一位：$1$，因为拆分序列的第一位不可能是 $0$，所以 $1$ 的左边有 $(2-1)-1=0$ 棵子树，不用管了。

考虑序列的第二位：$1$，这一位可能出现 $0$ 了，所以 $1$ 的左边有 $2-1=1$ 棵子树，需要计算；

怎么算？发现字典树的子树性质特别好：第一层 $k^0$ 个点，第二层 $k^1$ 个点，第 $i$ 层 $k^{i-1}$ 个点。

所以**当 $n$ 是 $k$ 的连续整数次幂之和的时候，一棵根节点深度为 $i$ 的子树一共有 $k^0+k^1...+k^{dep_n-i}$ 个点**，这显然是可以 $O(1)$ 算的。

但是 $n$ 很可能不满足。这时就会像上图一样，在最下面一层挂上一些点。

没关系，我们可以先按照满足约束的 $n$ 来计算，再加上这一部分的贡献。

具体来说，在得到某个子树的大小的同时，我们显然也可以得到它最下面一层的点数，记为 $s$，那么这棵子树的下面就可以挂 $k\times s$ 个点。因此在这里一共就是 $2^0+2^1+2^2+\min(5,2^3)$ 个点。

这样我们就算完了所有 $3$ 左边的点的数量。只需把从根到 $3$ 这条路径上的每个前缀也累加进答案，就得到了 $3$ 的 $dfn$ 序。

即 $dfn_3=2^0+2^1+2^2+\min(5,2^3)+2=14$。

由此， $dfn$ 的问题解决。

---

时间复杂度：

多测 + 枚举每一层 + 二分 + 计算 $dfn$ = $O(T \log _k n \log ^2 n)$。

## 2.Code

```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll re(){
    ll x=0;
    char c=getchar();
    while(c<48||c>57)c=getchar();
    while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x;
}
void wr(ll x){
    if(x>9)wr(x/10);
    putchar(x%10|48);
}
__int128 p[100];
ll len,mx[64],k,ad;
__int128 sum[64];
void chai(ll n){
    ll p=n;
    memset(mx,0,sizeof mx);
    memset(sum,0,sizeof sum);
    len=0;
    while(n){
        mx[++len]=n%k;
        n/=k;
    }
    n=p;
    __int128 x=k-1;
    for(;n>=x;n-=x,x*=k);
    ad=n;//最下面挂着的点的数量 
    sum[0]=::p[0]=1;
    for(__int128 x=k,i=1;i<=len;++i,x*=k)sum[i]=sum[i-1]+x,::p[i]=x;
}
ll a[64],n;
ll dfn(ll x){
    memset(a,0,sizeof a);
    ll m=0;
    while(x){
        a[++m]=x%k;
        x/=k;
    }
    for(ll i=m;i;--i){//让 x的k进制划分数组 与 n的k进制划分数组 对齐 
        a[len-(m-i)]=a[i];
        if(i!=len-(m-i))a[i]=0;
    }
    ll res=0,les=ad;
    for(ll i=len;i;--i){
        if(!a[i])continue;
        if(i==len){
            res+=(a[i]-1)*sum[i-(ad!=0)-1];
            __int128 x=min(p[k,i-(ad!=0)]*(a[i]-1),(__int128)les);
            res+=x;
            les-=x;
        }
        else{
            res+=a[i]*sum[i-(ad!=0)-1];
            __int128 x=min(p[k,i-(ad!=0)]*a[i],(__int128)les);
            res+=x;
            les-=x;
        }
    }
    res+=m;//加上x的前缀 
    return res;
}
ll calc(ll l,ll r){
    ll p=l,q=r,opt1=-1,opt2=-1;
    while(l<=r){
        ll mid=(l+r)>>1,df=dfn(mid);
        if(df-mid>0)r=mid-1,q=mid-1;
        else if(df-mid<0)l=mid+1,p=mid+1;
        else opt1=mid,r=mid-1,p=mid;
    }
    l=p,r=q;
    while(l<=r){
        ll mid=(l+r)>>1,df=dfn(mid);
        if(df-mid>0)r=mid-1;
        else if(df-mid<0)l=mid+1;
        else opt2=mid,l=mid+1;
    }
    if(opt1==-1||opt2==-1)return 0;
    return opt2-opt1+1;
}
ll ans,l,r,i;
void work(){
    n=re();
    k=re();
    chai(n);
    ans=0;
    __int128 o=k-1;
    for(l=1,r=min(o,(__int128)n);l<=n;){
        ans+=calc(l,r);
        o*=k,l=r+1,r=min((__int128)n,o+l-1);
    }
    wr(ans);
    puts("");
}
int T;
int main(){
    T=re();
    while(T--)work();
    return 0;
}
```

---

## 作者：Leasier (赞：4)

直接考虑 $k$ 进制下位数不同的数是很抽象的，考虑两个位数相同的 $p < q$，可以发现此时 $rk_p < rk_q$。

设 $f(x) = rk_x - x$，则我们需要求 $f(x) = 0$ 的 $x$ 个数。

考虑位数相同的 $x, x + 1$ 间 $x$ 的关系，此时 $rk_{x + 1} - rk_x \geq 1$，则 $f(x + 1) - f(x) \geq 0$。

于是我们对位数相同的数二分出 $f(x) = 0$ 的 $x$ 所在区间即可。

时间复杂度为 $O(T \log n \log_k^2 n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;
typedef __int128 lll;

int lenn;
ll n, k;
ll power[67];

inline ll max(ll a, ll b){
	return a > b ? a : b;
}

inline lll min(lll a, lll b){
	return a < b ? a : b;
}

inline ll calc(ll x){
	int lenx = 0;
	ll t = x, ans;
	while (t > 0){
		lenx++;
		t /= k;
	}
	ans = x - power[lenx - 1] + 1;
	t = x;
	for (int i = 1; i < lenx; i++){
		t /= k;
		ans += t - power[i - 1] + 1;
	}
	t = x;
	for (int i = lenx + 1; i <= lenn; i++){
		t = min((lll)t * k, n + 1);
		ans += t - power[i - 1];
	}
	return ans;
}

inline ll solve(ll l, ll r){
	if (l > r) return 0;
	ll L = l, R = r, lpos = -1;
	while (L <= R){
		ll mid = (L + R) >> 1;
		if (calc(mid) >= mid){
			R = mid - 1;
			lpos = mid;
		} else {
			L = mid + 1;
		}
	}
	if (lpos == -1 || calc(lpos) > lpos) return 0;
	ll rpos = -1;
	L = lpos;
	R = r;
	while (L <= R){
		ll mid = (L + R) >> 1;
		if (calc(mid) == mid){
			L = mid + 1;
			rpos = mid;
		} else {
			R = mid - 1;
		}
	}
	return rpos == -1 ? 0 : rpos - lpos + 1;
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		ll t, ans = 1;
		scanf("%lld %lld", &n, &k);
		lenn = 0;
		t = n;
		while (t > 0){
			lenn++;
			t /= k;
		}
		power[0] = 1;
		for (int j = 1; j < lenn; j++){
			power[j] = power[j - 1] * k;
		}
		for (ll j = 1; ; ){
			lll up = (lll)j * k;
			ans += solve(max(j, 2), min(up - 1, n));
			if (up > n) break;
			j = up;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Register_int (赞：4)

有一个简单的观察，对于所有长度相等的数，他的数值和字典序是同时递增的。也就是说，我们只要二分第一个与最后一个两者相等的位置，就能得出长度为 $l$ 时的答案。

考虑如何求单个数 $a$ 的字典序。这相当于是求有多少个字典序小于等于他的数。先枚举这个数 $b$ 的长度 $l_b$，设要求的数长度为 $l_a$，有以下两种情况：

- $l_b\le l_a$，此时这个数需要满足前 $l_b$ 位小于等于 $a$ 的前 $l_b$ 位，直接计算即可。

- $l_b>l_a$，此时这个数需要满足前 $l_a$ 位小于 $a$，剩下可以随便填。

处理下边界即可。总时间复杂度 $O(T\log n\cdot\log_k^2n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int t; ll n, m, p[64], ans; int tp;

inline 
ll calc(int l, ll x) {
	ll res = 0, y = x;
	for (int i = l; ~i; i--) res += y - p[i] + 1, y /= m;
	if (l == tp) return res - x;
	for (int i = l + 1; i < tp; i++) res += (__int128)p[i - l] * x - p[i];
	res += min((__int128)n + 1, (__int128)p[tp - l] * x) - p[tp];
	return res - x;
}

ll l, r, mid, x, y;

int main() {
	for (scanf("%d", &t), *p = 1; t--;) {
		scanf("%lld%lld", &n, &m), ans = 0;
		for (tp = 0; p[tp] <= n / m; tp++, p[tp] = p[tp - 1] * m);
		for (int i = 0; i <= tp; i++) {
			l = p[i], r = i == tp ? n : p[i + 1] - 1;
			for (; l <= r; calc(i, mid = l + r >> 1) < 0 ? l = mid + 1 : r = mid - 1); x = l;
			l = p[i], r = i == tp ? n : p[i + 1] - 1;
			for (; l <= r; calc(i, mid = l + r >> 1) > 0 ? r = mid - 1 : l = mid + 1); y = r;
			ans += max<ll>(0, y - x + 1);
		}
		printf("%lld\n", ans);
	}
}
```

---

## 作者：Pekac (赞：2)

[CF1870F](https://www.luogu.com.cn/problem/CF1870F)

题意：给一个长度为 $n$ 的排列，求在其在 $k$ 进制下按字典序排序后 $\sum[p_i=i]$ 的值（$n\le10^{18}$）。

直接做是不好办的，只能在一些数中找到 $p_i$ 的大小关系。

在手摸的过程中会发现一些长度相等的数之间会插入一些其它长度的数，很麻烦，考虑按长度分类。然后就可以发现 $k$ 进制表示中长度均为 $l$ 的数一定有 $i<j$ 则 $p_i<p_j$。考虑从这里下手。

把这个东西看作一个类似于分段函数的东西，$f_l(i)=p_i$，$l$ 表示的是长度。其中 $p_i$ 的求解是简单的，从前往后扫一遍即可。

观察这个函数，发现肯定是递增的，那么在这个函数中符合条件的点一定在 $x-y=0$ 的直线上，容易发现如果有符合条件的点，一定只有一段区间内的点落在直线上，因为 $f_l'(i)$ 始终 $\ge 1$。

但这样并不好统计，显然的，因为 $x-y=0$ 的斜率为 $1$，令 $g_l(i)=f_l(i)-i$，就变为了统计一个不降的序列的值为 $0$ 的区间的长度。因为不能从前往后扫，二分两次即可。

代码：
```cpp
typedef long long ll;
ll n,m;
ll pw[65],c;
ll calc(ll a,ll b,ll c){
	if(!b||!c)return 0;
	return (b<=a/c)?(b*c):a;
}
ll check(int len,ll mid){
	ll res=0,tmp=mid;
	for(int i=len;i>=0;i--)res+=tmp-pw[i]+1,tmp/=m;
	if(len==c)return res;
	for(int i=len+1;i<c;i++)res+=pw[i-len]*(mid-pw[len]);
	res+=calc(n+1,pw[c-len],mid)-pw[c];
	return res;
}
void solve(){
	cin>>n>>m;
	pw[c=0]=1;while(pw[c]<=n/m)pw[c+1]=pw[c]*m,c++;
	ll ans=0;
	for(int i=0;i<=c;i++){
		ll l=pw[i],r=((i==c)?n:(pw[i+1]-1)),L=r+1,R=l-1;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(check(i,mid)>=mid)r=mid-1;
			else l=mid+1;
		}
		L=l;l=pw[i],r=((i==c)?n:(pw[i+1]-1));
		while(l<=r){
			ll mid=(l+r)>>1;
			if(check(i,mid)<=mid)l=mid+1;
			else r=mid-1;
		}
		R=r;
		ans+=max(0ll,R-L+1);
	}
	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;while(T--)solve();
	return 0;
}
```

---

## 作者：spdarkle (赞：1)

巧妙的问题！

首先考虑，我们设 $pos_i$ 为 $i$ 在 $k$ 进制表示下的字符串能排到第几位，我们即求 $\sum_{i=1}^n[pos_i=i]$。

对于 $pos$ 的性质：不难发现对于 $i,j\in[k^a,\min(n,k^{a+1}-1)],i<j$，则可以立即给出 $pos_i<pos_j$。

证明是简单的，我们只需要考虑二者字符串的最长公共前缀的下一个位置即可。

思维难度给到了这个地方：

对于 $i\in [k^a,\min(n,k^{a+1}-1)],i+1\in [k^a,\min(n,k^{a+1}-1)]$，容易发现，$pos_{i+1}-pos_i\ge 1$。

进而，我们设 $d(i)=pos_i-i$，容易发现在上述情况下，$d(i+1)-d(i)=pos_{i+1}-pos_i-1\ge 0$。

这说明什么？

我们将 $d$ 函数按照 $k$ 的次幂分段为 $d_0,d_1\dots d_{\log_k n}$ 个函数，这些函数都是单调的。

而我们对于每一个函数求出零点所在区间，即可统计到答案。

那么再对于 $i\in [k^a,\min(n,k^{a+1}-1)],i+1\notin [k^a,\min(n,k^{a+1}-1)],i>1$ 的情况，显然是无解的。因为 $pos_{i+1}$ 必然小于 $pos_i$。证明同样可以考虑最长公共前缀的下一个元素。但此时注意特判 $i=1$ 的情况。

此时问题就变为了足够快地求解 $pos_i$，结合二分函数零点即可做到 $O(T\log_{k}^2w)$，其中 $w$ 是求解单个 $pos$ 的复杂度。

对于单个 $pos_x$ 的求解，可以通过两个方向来考虑。

记 $x$ 的 $k$ 进制表示为 $s_0s_1\dots s_c$，其中 $t_i=(s_0s_1\dots s_i)_k$
首先是 $k$ 进制字符串长度比 $x$ 的小的。

我们依次从 $c$ 到 $0$ 扫描，设当前扫描的有 $i(i\le c)$ 位。

可以考虑求出 $i$ 位的字符串的最小值，然后直接由 $t_i$ 做差即可（这里为什么对，请自己思考亦或者看代码下方）。注意这个最小值其实就是 $k^i$。所以贡献就是 $t_i-k^i+1$。因为此时 $t_i$ 的字典序也是比 $x$ 小的。

然后长度比 $x$ 大的同理计算，但那个加上一就没了，因为取不到 $t$。

需要注意 $n$ 的边界以及 $nk$ 可能会导致六十四位溢出的问题。

```cpp
#include<iostream>
using namespace std;
#define N 105
#define int long long
int pw[N],n,k,tot;
void init(){
	tot=0;pw[0]=1;int tmp=n;
	while(n/k>=pw[tot]&&pw[tot]*k<=n)pw[tot+1]=pw[tot]*k,++tot;
}
int get(int x,int dep){
	int cnt=x-pw[dep]+1;
	int tmp=x;
	for(int i=dep-1;i>=0;--i){
		tmp/=k,cnt+=tmp-pw[i]+1;
	}
	tmp=x;for(int i=dep+1;i<=tot;i++){
		if(n/k>=tmp&&tmp*k<=n)tmp*=k;//这里是一个小trick，防止爆精度
		else tmp=n+1;
		tmp=min(tmp,n+1);cnt+=tmp-pw[i];
	}
	return cnt;
}
int find(int dep){
	int l=pw[dep],r=(dep==tot?n:pw[dep+1]-1);
	int l1=l-1,l2=l,r1=r,r2=r+1;
	while(l1<r1){
		int mid=l1+r1+1>>1;
		if(get(mid,dep)>=mid)r1=mid-1;
		else l1=mid;
	} 
	while(l2<r2){
		int mid=l2+r2>>1;
		if(get(mid,dep)>mid)r2=mid;
		else l2=mid+1; 
	}
	if(l1<l2)return l2-l1-1;
	return 0;
}
signed main(){
	int t;cin>>t;
	while(t--){
		cin>>n>>k;
		init();int res=0;
		for(int i=0;i<=tot;i++)res+=find(i);
		cout<<res<<"\n";
	}
}
```

这里具体求解 $pos$ 的过程可能并非很直观，但官方题解给出了一种更好的理解方式。

定义一颗广义的字典树。其每个点的 $k$ 进制字典序即根节点到所有节点的路径上的边所代表的字符串。

注意根节点的儿子不含有零，但其他的节点儿子都有零。将儿子按照 $0\dots k-1$ 排序。

此时注意到这一棵广义字典树的广度优先遍历即为序列 $1,2,3\dots n$，而深度优先遍历（先得根节点，再依次进入每一个儿子）就是 $pos_1,pos_2\dots pos_n$。

那么后面的分析过程是相似的，我们本质上是对每一层进行操作，然后对于除 $i=1$ 之外的所有情况跨层无解。

而对于统计 $pos$ 的过程，等价于求这一层中在点 $t$ 前的点的个数。从 $x$ 往上走要算自己，往下走不算。

这样我们就 $O(t\log^3_{k}n)$ 地解决了这个问题。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1870F)

**题目大意**

> 给定 $n,k$，求 $1\sim n$ 在 $k$ 进制下有多少个数值等于其字典序排名。
>
> 数据范围：$n,k\le 10^{18}$。

**思路分析**

求正整数的字典序排名可以直接建 Trie，那么数值等于其 bfs 序，字典序排名等于其 dfs 序。

对每层的节点分别考虑，同层节点 bfs 序每次 $+1$，而 dfs 序每次增量 $\ge 1$，因此两者之差单调递增，可以二分出 $=0$ 的区间。

那么我们只要支持快速计算每个数的字典序排名，逐层计数即可。

时间复杂度 $\mathcal O(\log^3n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h> 
#define ll long long
#define LL __int128
using namespace std;
ll n,m,pw[65],len;
ll rk(int k,ll x) {
	ll s=0,y=x;
	for(int i=k;~i;--i) s+=y-pw[i]+1,y/=m;
	if(k==len) return s;
	for(int i=k+1;i<len;++i) s+=(x-pw[k])*pw[i-k];
	s+=min((LL)n+1,(LL)x*pw[len-k])-pw[len];
	return s;
}
void solve() {
	scanf("%lld%lld",&n,&m),len=0;
	for(pw[0]=1;(LL)pw[len]*m<=n;++len) pw[len+1]=pw[len]*m;
	ll ans=0;
	for(int i=0;i<=len;++i) {
		ll L=pw[i],R=(i==len?n:pw[i+1]-1);
		auto find=[&](ll d) {
			ll l=L,r=R,p=l-1;
			while(l<=r) {
				ll mid=(l+r)>>1;
				if(rk(i,mid)-mid<=d) p=mid,l=mid+1;
				else r=mid-1;
			}
			return p;
		};
		ans+=find(0)-find(-1);
	}
	printf("%lld\n",ans);
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

