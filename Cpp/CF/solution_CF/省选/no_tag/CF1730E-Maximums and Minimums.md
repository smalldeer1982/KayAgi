# Maximums and Minimums

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ of positive integers.

Find the number of pairs of indices $ (l, r) $ , where $ 1 \le l \le r \le n $ , that pass the check. The check is performed in the following manner:

1. The minimum and maximum numbers are found among $ a_l, a_{l+1}, \ldots, a_r $ .
2. The check is passed if the maximum number is divisible by the minimum number.

## 说明/提示

Below $ x \mid y $ denotes that $ y $ is divisible by $ x $ .

In the first test case, there is one pair $ (1, 1) $ , the maximum for this pair is $ 1 $ , the minimum is also $ 1 $ , $ 1 \mid 1 $ , so the check is passed, and the answer is $ 1 $ .

In the second test case, there are $ 3 $ segments:

- $ (1, 1) $ : the maximum is $ 2 $ , the minimum is $ 2 $ , $ 2 \mid 2 $ , so the check is passed.
- $ (1, 2) $ : the maximum is $ 4 $ , the minimum is $ 2 $ , $ 2 \mid 4 $ , so the check is passed.
- $ (2, 2) $ : the maximum is $ 4 $ , the minimum is $ 4 $ , $ 4 \mid 4 $ , so the check is passed.

In the third test case, there are $ 3 $ segments:

- $ (1, 1) $ : the maximum is $ 2 $ , the minimum is $ 2 $ , $ 2 \mid 2 $ , so the check is passed.
- $ (1, 2) $ : the maximum is $ 3 $ , the minimum is $ 2 $ , $ 3 $ isn't divisible by $ 2 $ , so the check is failed.
- $ (2, 2) $ : the maximum is $ 3 $ , the minimum is $ 3 $ , $ 3 \mid 3 $ , so the check is passed.

## 样例 #1

### 输入

```
6
1
1
2
2 4
2
2 3
4
2 4 7 14
7
16 5 18 7 7 12 14
6
16 14 2 6 16 2```

### 输出

```
1
3
2
7
10
19```

# 题解

## 作者：灵茶山艾府 (赞：8)

### 算法框架

枚举 $v=a_i$ 及其因子 $d$（最多 $240$ 个因子），计算子数组左边界的范围，和右边界的范围，使左右边界之内的数，最大值恰好是 $v$ 且最小值恰好是 $d$。

### 细节

看上去思路比较简单，但是实现起来还是有些技巧的。

1. 预处理每个数的因子列表，这可以反向枚举因子及其倍数得到。
2. 用 [单调栈](https://www.bilibili.com/video/BV1VN411J7S7/) 预处理：
   - $a_i$ 左边最近更大或相等元素的下标 $\textit{leftHi}_i$。如果不存在则为 $-1$。
   - $a_i$ 右边最近更大元素的下标 $\textit{rightHi}_i$。如果不存在则为 $n$。
   - $a_i$ 左边最近更小元素的下标 $\textit{leftLo}_i$。如果不存在则为 $-1$。
   - $a_i$ 右边最近更小元素的下标 $\textit{rightLo}_i$。如果不存在则为 $n$。
3. 预处理 $a$ 中相同元素的下标列表 $\textit{pos}$。其中 $\textit{pos}_v$ 表示 $v$ 在 $a$ 中的下标列表（下标从小到大）。
4. 枚举 $v=a_i$ 及其因子 $d$。设 $l=\textit{leftHi}_i,\ r=\textit{rightHi}_i$。
5. 第一种情况：如果 $v$ 左侧最近 $d$ 存在，设其下标为 $j$，那么子数组左端点范围为 $(\max(\textit{leftLo}_j, l), j]$，右端点范围为 $[i, \min(\textit{rightLo}_j, r))$，两个范围长度的乘积加入答案中。注意前提是 $j > l$ 且 $\textit{rightLo}_j > i$。然后更新 $l$ 为 $\max(l,j)$，防止情况二重复统计。
6. 第二种情况：如果 $v$ 右侧最近 $d$ 存在，设其下标为 $j$，那么子数组左端点范围为 $(\max(\textit{leftLo}_j, l), i]$，右端点范围为 $[j, \min(\textit{rightLo}_j, r))$，两个范围长度的乘积加入答案中。注意前提是 $j < r$ 且 $\textit{leftLo}_j < i$。

怎么找 $v$ 左右最近的 $d$ 的下标？在遍历 $a$ 的同时维护 $\textit{pos}$ 列表，对于在 $a_i$ 左侧的相同数字，我们只保留最大的小于 $i$ 的下标。

下面的实现单独判断了 $d=v$ 的情况，此时子数组左端点为 $i$，右端点范围为 $[i, \min(\textit{rightLo}_i, r))$。

```go
package main
import ("bufio";."fmt";"os")
func min(a, b int) int { if b < a { return b }; return a }
func max(a, b int) int { if b > a { return b }; return a }

func main() {
	in := bufio.NewReader(os.Stdin)
	const mx = 1000001
	divisors := [mx][]uint32{}
	for i := uint32(1); i < mx; i++ {
		for j := i * 2; j < mx; j += i {
			divisors[j] = append(divisors[j], i)
		}
	}

	var T, n int
	pos := [mx][]int{}
	for Fscan(in, &T); T > 0; T-- {
		for i := range pos {
			pos[i] = pos[i][:0]
		}
		Fscan(in, &n)
		a := make([]int, n)
		for i := range a {
			Fscan(in, &a[i])
			pos[a[i]] = append(pos[a[i]], i)
		}

		leftHi := make([]int, n)  // >= a[i]
		rightHi := make([]int, n) // > a[i]
		leftLo := make([]int, n)  // < a[i]
		rightLo := make([]int, n) // < a[i]
		s := []int{-1} // 哨兵
		t := []int{-1}
		for i, v := range a {
			for len(s) > 1 && v > a[s[len(s)-1]] {
				rightHi[s[len(s)-1]] = i
				s = s[:len(s)-1]
			}
			leftHi[i] = s[len(s)-1]
			s = append(s, i)

			for len(t) > 1 && v <= a[t[len(t)-1]] {
				t = t[:len(t)-1]
			}
			leftLo[i] = t[len(t)-1]
			t = append(t, i)
		}
		for _, i := range s[1:] {
			rightHi[i] = n
		}

		t = append(t[:0], n)
		for i := n - 1; i >= 0; i-- {
			v := a[i]
			for len(t) > 1 && v <= a[t[len(t)-1]] {
				t = t[:len(t)-1]
			}
			rightLo[i] = t[len(t)-1]
			t = append(t, i)
		}

		ans := 0
		for i, v := range a { // 最大值为 v
			r := rightHi[i]
			ans += min(rightLo[i], r) - i // 最小值为 v
			for _, d := range divisors[v] { // 最小值为 d
				ps := pos[d]
				l := leftHi[i]
				if len(ps) > 0 && ps[0] < i {
					j := ps[0] // v 左侧最近 d 的下标
					ps = ps[1:]
					if j > l && rightLo[j] > i {
						ans += (j - max(leftLo[j], l)) * (min(rightLo[j], r) - i)
					}
					l = max(l, j) // 避免重复统计
				}
				if len(ps) > 0 {
					j := ps[0] // v 右侧最近 d 的下标
					if j < r && leftLo[j] < i {
						ans += (i - max(leftLo[j], l)) * (min(rightLo[j], r) - j)
					}
				}
			}
			// v 左侧每个数只保留其最右的下标
			if len(pos[v]) > 1 && pos[v][1] == i {
				pos[v] = pos[v][1:]
			}
		}
		Println(ans)
	}
}
```

- 时间复杂度：预处理 $\mathcal{O}(U\log U)$，其中 $U=10^6$。每组数据 $\mathcal{O}(nD)$，其中 $D=240$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)


---

## 作者：xianggl (赞：7)

题意：

给定一个长度为 $n$ 数组 $a$，求有多少个区间 $[l, r]$，满足 $\min(l, r) | \max(l, r)$。

$1 \leq n \leq 5 \times 10 ^ 5$，$1 \leq a[i] \leq 10 ^ 6$

题解：

因为 $a$ 中的数不是只出现一次，所以枚举倍数不现实，考虑枚举最大值，然后枚举因数。

令在 $i$ 前第一个比 $i$ 小的位置为 $pre[i]$，$suf[i]$ 同理。

若当前枚举到的位置为 $i$，以 $i$ 为最大值的区间为 $[l, r]$。

考虑枚举一个 $x$ 为 $a[i]$ 的真因数， $x = a[i]$ 的情况分出去方便讨论，这种情况读者自行思考不难。

令 $pl$ 为 $x$ 在 $i$ 前第一个出现的位置，$pr$ 为 $x$ 在 $i$ 后第一个出现的位置。

若 $pl$，$pr$ 都存在，且在 $[l, r]$ 中，考虑用只选一端的总和减去两端都选，即为：

$(pl - \max(l - 1, pre[pl])) \times (\min(r + 1, suf[pr]) - i) + 
(i - \max(l - 1, pre[pl])) \times (\min(r + 1, suf[pr]) - pr) - 
(pl - \max(l - 1, pre[pl])) \times (\min(r + 1, suf[pr]) - pr)$

当然还要考虑 $[pl + 1, i]$ 和 $[i, pr - 1]$ 的最小值是否 $> x$，否则就只能选一边，或都不能选。

若只有一边，左边即为 $(\min(r + 1, suf[p]) - i) \times (p - \max(l - 1, pre[p]))$，右边即为 $(\min(r + 1, suf[p]) - p) \times (i - \max(l - 1, pre[p]))$

那么如何维护这个位置？

把 $x$ 出现的位置放进一个 vector s，用一个指针 $cnt[x]$ 表示当前是 $x$ 第几次出现，$s[x][cnt[x]]$ 即为 $pl$，$s[x][cnt[x] + 1]$ 即为 $pr$。

时间复杂度 $O(n \times d)$。

Code:

```
#include <bits/stdc++.h>
#define ri register int
#define ll long long
#define fi first
#define se second
using namespace std;
const int Maxn=5e5;
const int Maxm=1e6;
const int Inf=1e9;
vector<int>d[Maxm+5],s[Maxm+5];
int cnt[Maxm+5];
int mn[19][Maxn+5],log_2[Maxn+5];
stack<int>stk;
void sieve(int n) {
	for(ri i=1;i<=n;i++)
		for(ri j=2*i;j<=n;j+=i)d[j].emplace_back(i);
	for(ri i=1;i<=n;i++)cnt[i]=-1;
}
inline int query(int l,int r) {
	if(l>r)return Inf;
	int t=log_2[r-l+1];
	return min(mn[t][l],mn[t][r-(1<<t)+1]);
}
void build_st(auto &a,int n) {
	log_2[0]=-1;
	for(ri i=1;i<=n;i++)log_2[i]=log_2[i>>1]+1;
	for(ri i=1;i<=n;i++)mn[0][i]=a[i];
	for(ri j=1;j<=log_2[n];j++)
		for(ri i=1;i<=n-(1<<j)+1;i++)mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
}
void solve() {
	int n;
	scanf("%d",&n);
	vector<int>a(n+1),pre(n+1),suf(n+1),L(n+1),R(n+1);
	for(ri i=1;i<=n;i++)scanf("%d",&a[i]),s[a[i]].push_back(i);
	vector<int>stk;
	for(ri i=1;i<=n;i++) {
		while(!stk.empty()&&a[stk.back()]>=a[i])stk.pop_back();
		if(!stk.empty())pre[i]=stk.back();
		else pre[i]=0;
		stk.emplace_back(i);
	}
	stk.clear();
	for(ri i=n;i>=1;i--) {
		while(!stk.empty()&&a[stk.back()]>=a[i])stk.pop_back();
		if(!stk.empty())suf[i]=stk.back();
		else suf[i]=n+1;
		stk.emplace_back(i);
	}
	stk.clear();
	for(ri i=1;i<=n;i++) {
		while(!stk.empty()&&a[stk.back()]<a[i])stk.pop_back();
		if(!stk.empty())L[i]=stk.back();
		else L[i]=0;
		stk.emplace_back(i);
	}
	stk.clear();
	for(ri i=n;i>=1;i--) {
		while(!stk.empty()&&a[stk.back()]<=a[i])stk.pop_back();
		if(!stk.empty())R[i]=stk.back();
		else R[i]=n+1;
		stk.emplace_back(i);
	}
	stk.clear();
	build_st(a,n);
	ll ans=0;
	for(ri i=1;i<=n;i++) {
		int t=a[i],l=L[i]+1,r=R[i]-1;
		//printf("%d %d %d %d %d\n",i,l,r,pre[i],suf[i]);
		ans+=1ll*(min(r+1,suf[i])-i)*(i-max(l-1,pre[i]));
		for(ri &x:d[t]) {
			if(cnt[x]>=0&&cnt[x]<(int)s[x].size()-1&&l<=s[x][cnt[x]]&&s[x][cnt[x]+1]<=r) {
				int pl=s[x][cnt[x]],pr=s[x][cnt[x]+1];
				if(query(pl+1,i)>x&&query(i,pr-1)>x) {
					ans+=1ll*(pl-max(l-1,pre[pl]))*(min(r+1,suf[pr])-i);
					ans+=1ll*(i-max(l-1,pre[pl]))*(min(r+1,suf[pr])-pr);
					ans-=1ll*(pl-max(l-1,pre[pl]))*(min(r+1,suf[pr])-pr);
				}
				else if(query(pl+1,i)>x) {
					ans+=1ll*(pl-max(l-1,pre[pl]))*(min(r+1,suf[pl])-i);
				}
				else if(query(i,pr-1)>x) {
					ans+=1ll*(min(r+1,suf[pr])-pr)*(i-max(l-1,pre[pr]));
				}
			}
			else if(cnt[x]>=0&&l<=s[x][cnt[x]]) {
				int p=s[x][cnt[x]];
				if(query(p+1,i)>x) {
					ans+=1ll*(min(r+1,suf[p])-i)*(p-max(l-1,pre[p]));
				}
			}
			else if(cnt[x]<(int)s[x].size()-1&&s[x][cnt[x]+1]<=r) {
				int p=s[x][cnt[x]+1];
				if(query(i,p-1)>x) {
					ans+=1ll*(min(r+1,suf[p])-p)*(i-max(l-1,pre[p]));
				}
			}
		}
		++cnt[a[i]];
		//printf("ans: %lld\n",ans); 
	}
	printf("%lld\n",ans);
	for(ri i=1;i<=n;i++)s[a[i]].clear(),cnt[a[i]]=-1;
}
int main() {
	sieve(Maxm);
	int T;
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}

```


---

## 作者：wishapig (赞：5)

考虑枚举最大值的位置 $i$，以及 $a[i]$ 的一个因子 $d$ 为区间最小值（先排除区间最小值等于最大值的情况，这个是容易计算的）。

为防止算重，先定义：

- $P[i]$ 表示 $i$ 之前第一个 $\ge a[i]$ 的位置（不存在则为 $0$）。
- $S[i]$ 表示 $i$ 之后第一个 $>a[i]$ 的位置（不存在则为 $n+1$）。 

则计数 “区间左端点在 $[P[i]+1,i]$ 中，右端点在 $[i,S[i]-1]$ 中，区间 $\min=d$ 的区间个数”。

记 $l=P[i]+1$，$r=S[i]-1$。

找到 $i$ 前第一个 $d$ 的位置 $L$，$i$ 后第一个 $d$ 的位置 $R$。

再求出：

- $pre[i]$ 表示 $i$ 前第一个 $<a[i]$ 的位置（不存在则为 $0$）。
- $suf[i]$ 表示 $i$ 后第一个 $<a[i]$ 的位置（不存在则为 $n+1$）。

那么：

- 若 $L<l$ 或 $suf[L]<i$，那么 $L$ 不合法，不能取左边的这个 $d$。
- 若 $R>r$ 或 $pre[R]>i$，那么 $R$ 不合法，不能取右边的这个 $d$。

然后分三种情况讨论

第一种，$L,R$ 都合法，左右的 $d$ 都取：
$$
(L-\max(l,pre[L]+1)+1)\cdot(\min(r,suf[R]-1)-R+1)
$$
第二种，$L$ 合法，只取左边的 $d$：
$$
(L-\max(l,pre[L]+1)+1)\cdot (\min(r,R-1,suf[L]-1)-i+1)
$$
第三种，$R$ 合法，只取右边的 $d$：
$$
(i-\max(l,L+1,pre[R]+1)+1)\cdot (\min(r,suf[R]-1)-R+1)
$$
全部加起来即可。

总复杂度为 $O(A\ln A+\sum nD)$，其中 $A$ 为值域， $D$ 为最大因子个数，$10^6$ 内为 $240$。

前面的 $P[],S[],pre[],suf[]$ 都可以用单调栈线性求出，$i$ 左右第一个 $d$ 的位置可以拿 `vector` 直接存。

具体见代码，还是比较简短的。

```c++
const int N=1e6+5;
int Head[N],vet[N*15],Next[N*15];
int pre[N],suf[N],P[N],S[N],stk[N],a[N];
int T,n,lst,top,edgenum; long long ans;
vector<int> vecL[N],vecR[N];
void add(int u, int v){
	edgenum++;
	vet[edgenum]=v;
	Next[edgenum]=Head[u];
	Head[u]=edgenum;
}
char buf[1<<24],*iS=buf;
#define gc() (*iS++)
inline int read(){
	char ch=gc(); int x=0;
	while (!isdigit(ch)) ch=gc();
	while (isdigit(ch)) x=x*10+ch-'0',ch=gc();
	return x;
}
int main(){
	for (int i=1; i<=1000000; i++)
		for (int j=i*2; j<=1000000; j+=i) add(j,i);
	fread(buf,1,1<<24,stdin);
	for (T=read(); T; T--){
		n=read(); lst=ans=0;
		for (int i=1; i<=n; i++){
			a[i]=read();
			if (a[i]!=a[i-1]) lst=i;
			ans+=i-lst+1;
		}
		stk[top=0]= 0 ; for (int i=1; i<=n; i++){ while (top && a[stk[top]]>=a[i]) top--; pre[i]=stk[top]; stk[++top]=i; }
		stk[top=0]=n+1; for (int i=n; i>=1; i--){ while (top && a[stk[top]]>=a[i]) top--; suf[i]=stk[top]; stk[++top]=i; }
		stk[top=0]= 0 ; for (int i=1; i<=n; i++){ while (top && a[stk[top]]< a[i]) top--;   P[i]=stk[top]; stk[++top]=i; }
		stk[top=0]=n+1; for (int i=n; i>=1; i--){ while (top && a[stk[top]]<=a[i]) top--;   S[i]=stk[top]; stk[++top]=i; }
		for (int i=n; i>=1; i--) vecR[a[i]].push_back(i);
		for (int i=1; i<=n; i++){
			vecR[a[i]].pop_back();
			int l=P[i]+1,r=S[i]-1;
			for (int e=Head[a[i]]; e; e=Next[e]){
				int d=vet[e];
				int L=vecL[d].empty()?l-1:vecL[d].back(); if (suf[L]<i) L=l-1;
				int R=vecR[d].empty()?r+1:vecR[d].back(); if (pre[R]>i) R=r+1;
				if (L<l && R>r) continue;
				if (L>=l && R<=r) ans+=1ll*(L-max(l,pre[L]+1)+1)*(min(r,suf[R]-1)-R+1);
				if (L>=l) ans+=1ll*(L-max(l,pre[L]+1)+1)*(min(min(r,R-1),suf[L]-1)-i+1);
				if (R<=r) ans+=1ll*(i-max(max(l,L+1),pre[R]+1)+1)*(min(r,suf[R]-1)-R+1);
			}
			vecL[a[i]].push_back(i);
		}
		printf("%lld\n",ans);
		for (int i=1; i<=n; i++){
			pre[i]=suf[i]=P[i]=S[i]=0;
			vecL[a[i]].clear(),vecR[a[i]].clear();
		}
	}
}
```






---

## 作者：zac2010 (赞：1)

### 解题思路

考虑枚举最小值 $x$ 以及枚举最大值 $y$。

每次再枚举 $y$ 在原序列出现的位置 $i$，则容易计算对答案的贡献：
* 我们拿最小值 $\geq x$ 的方案数，减去最小值 $>x$ 的方案数。

具体的，我们按照 $x$ 从大到小处理，利用并查集维护 $a_i\geq x$ 的连续段左右端点 $[l1,r1]$。初始拿到 $a$ 时再维护出 $a_i$ 作为最大值的区间 $[l2,r2]$。
那么 $\geq x$ 的方案数就是满足条件的区间 $[l,r]$ 的个数，其中 $(i-\max(l1,l2)+1)(\min(r1,r2)-i+1)$。

时间复杂度为 $O(nD)$，其中 $D$ 是 $10^6$ 内的最大因子个数。

### 代码实现


```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for (int i = (a); i <= (b); ++i)
#define FR(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 10, V = 1e6;
int n, a[N], l[N], r[N];
int tp, stk[N];
vector<int> pos[N];
struct DSU {
    int fa[N];
    void Init(int n) {
        iota(fa, fa + n + 1, 0);
    }
    int Find(int u) {
        return fa[u] == u? u : fa[u] = Find(fa[u]);
    }
    void Union(int u, int v) {
        fa[Find(v)] = Find(u);
    }
} Dl, Dr;
ll Calc(int x) {
    ll ret = 0;
    for (int y = x; y <= V; y += x) {
        for (int i: pos[y]) {
            int L = max(l[i], Dl.Find(i));
            int R = min(r[i], Dr.Find(i));
            ret += (ll)(i - L) * (R - i);
        }
    }
    return ret;
}
void Solve() {
    scanf("%d", &n);
    FL(i, 1, V) {
        pos[i].clear();
    }
    FL(i, 1, n) {
        scanf("%d", &a[i]);
        pos[a[i]].emplace_back(i);
    }
    tp = 0;
    FL(i, 1, n) {
        while (tp && a[stk[tp]] < a[i]) {
            r[stk[tp--]] = i;
        }
        l[i] = stk[tp];
        r[i] = n + 1;
        stk[++tp] = i;
    }

    Dl.Init(n + 1);
    Dr.Init(n + 1);
    ll ans = 0;
    FR(x, V, 1) {
        if (pos[x].empty()) continue;
        ans -= Calc(x);
        for (int i: pos[x]) {
            Dl.Union(i - 1, i);
            Dr.Union(i + 1, i);
        }
        ans += Calc(x);
    }
    printf("%lld\n", ans);
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        Solve();
    }
    return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

可爱的题目。我们实际上有两种策略：

- 枚举区间的最小值，找到符合的左右端点使得最大值是最小值的倍数。
- 枚举区间的最大值，找到符合的左右端点使得最小值是最大值的因子。

事实上，我们理应实现后者，因为数据范围内任何一个数的因子个数只有 $240$ 左右，而倍数个数可以高达 $1 \times 10^6$。（我卡了很久就是因为一根筋地想枚举最小值。）

假设我们想让 $d$ 成为最小的数，需要满足：

- 区间里面含有 $d$。这个只需要关注最大值左边和右边第一个 $d$ 的情况。
- 区间里面不含有小于 $d$ 的数。这个可以通过我们包含的 $d$ 左右第一个小于它的数的位置判断。

于是分类讨论只包含了左边第一个 $d$、只包含了右边第一个 $d$、同时包含了两个 $d$ 即可。

借鉴了题解区一个小技巧，对于每种数使用两个 `vector` 来找到最大值前面第一个 $d$ 和后面第一个 $d$。其他的用单调栈维护即可。

复杂度 $O(nd)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10,MAXM=1e6+10;
int n,T,m=1000000,a[MAXN];
vector<int> frac[MAXM];
int lb[MAXN],rb[MAXN],ls[MAXN],rs[MAXN]; //注意，只有 lb 是左边第一个大于等于不是严格的 
void init(void) {ffor(i,1,m) ffor(j,1,m/i) frac[i*j].push_back(i);return ;}
void clear(stack<int> &st) {while(!st.empty()) st.pop(); return ;}
vector<int> occl[MAXM],occr[MAXM];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T; init();
	while(T--) {
		cin>>n; ffor(i,1,n) cin>>a[i];
		stack<int> st; st.push(0);
		ffor(i,1,n) {while(st.top()!=0&&a[st.top()]<a[i]) st.pop();lb[i]=st.top(),st.push(i);}
		clear(st),st.push(0);
		ffor(i,1,n) {while(st.top()!=0&&a[st.top()]>=a[i]) st.pop();ls[i]=st.top(),st.push(i);}
		clear(st),st.push(n+1);
		roff(i,n,1) {while(st.top()!=n+1&&a[st.top()]<=a[i]) st.pop();rb[i]=st.top(),st.push(i);}
		clear(st),st.push(n+1);
		roff(i,n,1) {while(st.top()!=n+1&&a[st.top()]>=a[i]) st.pop();rs[i]=st.top(),st.push(i);}
		
		roff(i,n,1) occr[a[i]].push_back(i); long long ans=0;
		ffor(i,1,n) {
			occr[a[i]].pop_back();
			int l=lb[i]+1,r=rb[i]-1;
			for(auto div:frac[a[i]]) {
				if(div==a[i]) {
					int ll=max(l,ls[i]+1),rr=min(r,rs[i]-1);
					ans+=1ll*(i-ll+1)*(rr-i+1);
					continue ;
				}
				int bl=l,br=r,nl=bl-1,nr=br+1,flgl=0,flgr=0; //bound & need
				if(occl[div].size()) nl=max(nl,occl[div][occl[div].size()-1]);
				if(occr[div].size()) nr=min(nr,occr[div][occr[div].size()-1]);
				if(nl!=bl-1&&rs[nl]>i) {
					//我想包含 nl，但不包含 nr
					int lmin=max(bl,ls[nl]+1),lmax=nl;
					int rmin=i,rmax=nr-1;
					rmax=min(rmax,rs[nl]-1);
					ans+=1ll*(lmax-lmin+1)*(rmax-rmin+1);
				}
				if(nr!=br+1&&ls[nr]<i) {
					int rmin=nr,rmax=min(br,rs[nr]-1);
					int lmin=nl+1,lmax=i;
					lmin=max(lmin,ls[nr]+1);
					ans+=1ll*(lmax-lmin+1)*(rmax-rmin+1);
				}
				if(nl!=bl-1&&nr!=br+1&&ls[nr]<nl&&rs[nl]>nr) {
					int lmin=max(bl,ls[nl]+1),lmax=nl,rmin=nr,rmax=min(br,rs[nr]-1);
					ans+=1ll*(lmax-lmin+1)*(rmax-rmin+1);	
				}
			}
			occl[a[i]].push_back(i);	
		}
		cout<<ans<<'\n';
		ffor(i,1,n) occl[a[i]].clear(),occr[a[i]].clear();
	}
	return 0;
}
```

---

