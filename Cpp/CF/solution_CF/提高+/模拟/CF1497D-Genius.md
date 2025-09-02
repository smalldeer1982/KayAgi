# Genius

## 题目描述

注意内存限制

$n$个问题从$i$到$n$编号,
第$i$个问题给出
$c_i=2^i$,
$tag_i$,
$s_i$

解决问题$i$后解决问题$j$条件是:
$IQ<|c_i-c_j|$且$tag_i\neq tag_j$

在解决完$i$后解决了$j$,
你的$IQ$变为$IQ=|c_i-c_j|$,
同时获得$|s_i-s_j|$分

问题解决的次数和顺序不受限制

一开始$IQ=0$,
求最高可获得的分数

## 样例 #1

### 输入

```
5
4
1 2 3 4
5 10 15 20
4
1 2 1 2
5 10 15 20
4
2 2 4 1
2 8 19 1
2
1 1
6 9
1
1
666```

### 输出

```
35
30
42
0
0```

# 题解

## 作者：Fairicle (赞：4)

初看题目，很容易想到 DP，因为是跳来跳去，有明显的从一个点到另一个点的转移，转移也有权值，于是考虑怎么 DP。

首先发现这个转移是有限制的，不好处理。$c_i$ 的形式很特殊，是 $2^k$，可以发现一些性质。

首先发现，对于 $i\neq j,|c_i-c_j|$ 两两不同，这个易证。这条性质没什么用，最多让我们不需要考虑权值相同的情况。

其次发现，如果 $i$ 之前的点全部在 $1$ 到 $i-1$ 内互相转移，那么 $i$ 可以转移到前面的任意一点，前面的任意一点也可以转移到 $i$。

那么逐渐清晰了，可以先顺序从 $1$ 到 $n$ 枚举 $i$，让它和前面的点互相转移。问题来了：前面的点的枚举顺序是什么？如果从 $1$ 到 $i-1$ 枚举，可能会造成先从 $x$ 转移到 $i$ 再从 $i$ 转移到 $y$ $(x<y)$ 的情况，此时是不合法的，因为 $c$ 没有满足条件。所以倒序从 $i-1$ 到 $1$ 枚举第二维即可。

$tag$ 的限制只需要判 $i,j$ 的 $tag$ 是否相等即可。

code：

```cpp
#define ll long 
#define ri register int
#define N 5010
int t,n,tag[N],s[N];
ll f[N];
inline int lowbit(int x){return x & ( - x ) ;}
int main()
{
	t=rd();
	while(t--){
        n=rd();
        for(ri i=1;i<=n;++i) tag[i]=rd();
        for(ri i=1;i<=n;++i) s[i]=rd();
        for(ri i=1;i<=n;++i)
        for(ri j=i-1;j>=1;--j){
            if(tag[i]==tag[j]) continue;
            ll tmpi=f[i],tmpj=f[j],del=abs(s[i]-s[j]);
            f[i]=max(f[i],tmpj+del);
            f[j]=max(f[j],tmpi+del);
        }
        cout<<*max_element(f+1,f+1+n)<<endl;
        for(ri i=1;i<=n;++i) f[i]=0;
    }
    return 0;
}

```


---

## 作者：冷却心 (赞：3)

简单题，难度虚高 2500*。个人感觉 2300*。

注意到 $\text{IQ}$ 在任意时刻都是某两个幂之差，所以我们有状态 $f_{i,j,0/1}$ 表示当前 $\text{IQ}=c_i-c_j$，且上一题是 $i$ 或者 $j$ 的最大分数，要求 $i<j$。容易发现对于标签 $\text{tag}$ 的限制等于对每个状态 $f_{i,j,0/1}$ 要求必须满足 $\mathrm{tag}_i \ne \mathrm{tag}_j$。于是下文不再讨论这个限制。

根据 $\text{IQ}$ 单调递增，那么 $f_{i,j,0/1}$ 的转移要么 $i$ 变大要么 $j$ 变小，于是不会成环。我们考虑按 $i$ 分层，逐层转移。有三种转移：

- $i$ 变大：枚举 $k>i$，转移 $f_{k,i,0} \gets f_{i,j,0} + |s_i-s_k|$，以及 $f_{k,j,0} \gets f_{i,j,1} + |s_j - s_k|$。
- $j$ 变小：枚举 $k<j$，转移 $f_{i,k,1} \gets f_{i,j,0}+|s_i-s_k|$。

转移看起来是 $\mathcal O(n^3)$ 的，实际上第一种转移的第一个和 $j$ 无关，第二个和 $i$ 无关，于是可以开一个数组先取一遍 $\max$ 然后再一次转移，第二种转移时同一层内的一个前缀 $\max$，所以最终复杂度 $\mathcal O(n^2)$，不明意义的卡空间所以滚动一下空间复杂度 $\mathcal O(n)$。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 5e3 + 10;
int n, A[N], S[N]; LL DP[N][2], mx[N];

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	while (_ --) {
		cin >> n; 
		for (int i = 1; i <= n; i ++) cin >> A[i];
		for (int i = 1; i <= n; i ++) cin >> S[i];
		for (int i = 1; i <= n; i ++) 
			mx[i] = 0, DP[i][0] = DP[i][1] = -1e18;
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j < i; j ++) if (A[i] != A[j]) DP[j][0] = mx[j] + abs(S[i] - S[j]);
			LL tmp = 0;
			for (int j = i - 1; j >= 1; j --) if (A[i] != A[j])
				DP[j][1] = tmp + abs(S[i] - S[j]), tmp = max(tmp, DP[j][0]);
			for (int j = 1; j < i; j ++) if (A[i] != A[j])
				mx[i] = max(mx[i], DP[j][0]), mx[j] = max(mx[j], DP[j][1]);
		} LL Ans = 0;
		for (int i = 1; i <= n; i ++) Ans = max(Ans, mx[i]);
		cout << Ans << "\n";
	}
	return 0;
}
```

---

## 作者：lsj2009 (赞：2)

### Solution

一开始被题面吓到了，但仔细一想应该算是比较萌萌的题目。

我们考虑把问题 $i$ 向问题 $j$ 连边（需要满足 $tag_i\ne tag_j$），边权为一个二元组 $(|c_i-c_j|,|s_i-s_j|)$。

则题目等价于求一条路径满足边权上二元组第一个数单调递增，使得第二个数和最大。

这个我们只需要把所有边加进去，然后按第一维排个序，拿出来，令 $f_v\gets f_u+w$，就行了（$w$ 为二元组第二个元素）。

但是这个题比较难绷得一点是，空间只有 $32\text{MB}$，$\Theta(n^2)$ 得数组是开不下的，怎么办？

用到本题的一个性质：$c_i=2^i$，我们发现，从 $1$ 到 $n$ 枚举 $i$，再从 $i-1$ 到 $1$ 枚举 $j$，经过的边权必然单调递增，令 $f_j\gets f_i+|s_i-s_j|$ 即可。

然后就做完了，时间复杂度 $\Theta(n^2)$，空间复杂度 $\Theta(n)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=5e3+5;
int f[N],a[N],b[N];
signed main() {
    int T;
    scanf("%lld",&T);
    while(T--) {
        int n;
        scanf("%lld",&n);
        rep(i,1,n)
            f[i]=0;
        rep(i,1,n)
            scanf("%lld",&a[i]);
        rep(i,1,n)
            scanf("%lld",&b[i]);
        rep(i,1,n) {
            per(j,i-1,1) {
                if(a[i]==a[j])
                    continue;
                int v1=f[i],v2=f[j],val=abs(b[i]-b[j]);
                chkmax(f[i],v2+val);
                chkmax(f[j],v1+val);
            }
        }
        int ans=0;
        rep(i,1,n)
            chkmax(ans,f[i]);
        printf("%lld\n",ans);
    } 
    return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：1)

神题啊！

考虑建出 $n$ 个点的完全图，两个 $tag$ 不相同的点 $i,j$ 间的边权为 $|c_i-c_j|$，价值为 $|s_i-s_j|$。

则我们需要找出一条路径，边权严格递增，且价值最大。

注意到空间限制我们并不能二维 dp，只能一维 dp，但是麻烦的地方在于每个点的下一步能转移到哪里还和上一个点有关系，很烦。

可以考虑按边权严格递增的顺序计算每条边 $(i,j),i<j,tag_i\neq tag_j$上的转移，这样的话我们能够保证所有转移一定是合法的，而且不会漏掉任何情况。

令 $f_i$ 表示当前位于点 $i$ 能获得的最大价值，初始化 $f_i$ 全为 $0$。

由于二进制表示的性质，对于边 $(i,j),i<j,tag_i\neq tag_j$，$j$ 越大，其边权一定越大，而 $j$ 相同的情况下，$i$ 越小，其边权一定越大，形成了易于描述的偏序关系。

所以直接外层循环枚举 $j$ 从 $1$ 到 $n$，内层循环枚举 $i$ 从 $j-1$ 到 $1$。用 $f_i$ 和 $f_j$ 互相更新即可。

---

