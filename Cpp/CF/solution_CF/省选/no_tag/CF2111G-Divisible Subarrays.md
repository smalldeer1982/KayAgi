# Divisible Subarrays

## 题目描述

Technically, this is an interactive problem.

An array $ a $ of $ m $ numbers is called divisible if at least one of the following conditions holds:

- There exists an index $ i $ ( $ 1 \le i < m $ ) and an integer $ x $ such that for all indices $ j $ ( $ j \le i $ ), it holds that $ a_{j} \le x $ and for all indices $ k $ ( $ k > i $ ), it holds that $ a_{k} > x $ .
- There exists an index $ i $ ( $ 1 \le i < m $ ) and an integer $ x $ such that for all indices $ j $ ( $ j \le i $ ), it holds that $ a_{j} > x $ and for all indices $ k $ ( $ k > i $ ), it holds that $ a_{k} \le x $ .

You are given a permutation $ p $ of integers $ 1, 2, \dots, n $ . Your task is to answer queries of the following form fast: if we take only the segment \[ $ l $ , $ r $ \] from the permutation, that is, the numbers $ p_{l}, p_{l + 1}, \dots, p_{r} $ , is this subarray of numbers divisible?

Queries will be submitted in interactive mode in groups of $ 10 $ , meaning you will not receive the next group of queries until you output all answers for the current group.

## 样例 #1

### 输入

```
7
4 2 3 6 1 5 7
20
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
4 5
4 6
5 6
1 7
2 7
3 7
4 7
5 7```

### 输出

```
YES
YES
YES
YES
NO
YES
YES
YES
NO
YES
YES
NO
YES
YES
YES
YES
YES
YES
YES
YES```

# 题解

## 作者：StayAlone (赞：3)

可以倍增。

原问题等价于，询问是否存在 $k\in [l, r)$，使得 $\max\limits_{i\in [l, k]}\{a_i\}< \min\limits_{i\in (k, r]}\{a_i\}$（正反各做一遍）。

令 $f(i)$ 表示 $i$ 右侧第一个比 $a_i$ 大的位置，可单调栈处理。定义 $f^x(i)=f(f^{x-1}(i)), f^0(i)=i$。

对于询问 $[l, r]$，显然前缀 $\max$ 是一个分段函数，而对于每一段平台，$k$ 尽量取大最优。即，$k+1$ 的取值只可能是 $\{f^i(l)\}$。

若允许枚举 $k$，当 $k=f^i(l)-1$ 时，$\max\limits_{j\in [l, k]}\{a_j\}=a_{f^{i-1}(l)}$。此时的合法条件为 $\min\limits_{j\in [f^i(l), r]}\{a_j\}>a_{f^{i-1}(l)}$。

换个角度：使用 ST 表 + 二分，预处理 $g_i$ 表示最大的 $R$ 使得 $\min\limits_{j\in [f(i), R]}\{a_j\}>a_i$，则上面的合法条件转为 $g_{f^{i-1}(l)}\ge r$。

于是发现不用枚举了，若 $\max\limits_{i\ge 0\land f^i(l)\le r} \{g_{f^i(l)}\}\ge r$，则存在合法划分。该部分可用倍增解决。

时间复杂度 $\mathcal O((n+q)\log n)$，空间复杂度 $\mathcal O(n\log n)$。

```cpp
struct {
    int a[MAXN], f[20][MAXN], mxg[20][MAXN], mn[20][MAXN];
 
    il void init() {
        vector <int> st;
        rep2(i, n, 1) {
            while (st.size() && a[i] > a[st.back()]) st.pop_back();
            f[0][i] = st.size() ? st.back() : n + 1; st.eb(i);
        }
        rep1(i, 1, n) mn[0][i] = a[i];
        rep1(i, 1, 19) rep1(j, 1, n - (1 << i) + 1) mn[i][j] = min(mn[i - 1][j], mn[i - 1][j + (1 << i - 1)]);
        rep1(i, 1, 19) rep1(j, 1, n) f[i][j] = f[i - 1][f[i - 1][j]];
        auto query = [&](int l, int r) {
            int k = __lg(r - l + 1);
            return min(mn[k][l], mn[k][r - (1 << k) + 1]);
        };
        rep1(i, 1, n) {
            int l = f[0][i] - 1, r = n;
            while (l ^ r) {
                int mid = l + r + 1 >> 1;
                if (query(f[0][i], mid) > a[i]) l = mid;
                else r = mid - 1;
            } mxg[0][i] = l;
        }
        rep1(i, 1, 19) rep1(j, 1, n) mxg[i][j] = max(mxg[i - 1][j], mxg[i - 1][f[i - 1][j]]);
    }
 
    il int query(int l, int r) {
        int ans = 0, t = l;
        rep2(i, 19, 0) if (f[i][t] && f[i][t] <= r) gmax(ans, mxg[i][t]), t = f[i][t];
        return ans >= r;
    }
} T, T2;
 
int main() {
    read(n); rer(i, 1, n, a);
    rep1(i, 1, n) T.a[i] = T2.a[n - i + 1] = a[i];
    T.init(); T2.init();
    for (int Q = read(), l, r; Q--; ) {
        read(l, r), puts(T.query(l, r) | T2.query(n - r + 1, n - l + 1) ? "YES" : "NO");
        if (Q % 10 == 0) fflush(stdout);
    }
    return 0;
}
```

---

## 作者：zxh923 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF2111G)

### 思路

这个交互其实就是个强制在线，没有其他用处。

为了方便，对于一个横坐标 $x_1\sim x_2$，纵坐标 $y_1\sim y_2$ 的矩阵。我们用 $(x_1,x_2,y_1,y_2)$ 来描述。

首先考虑对于每一个 $l$，二分一个最远的 $r$ 使得 $[l,r]$ 合法。

然后你仔细想一下，发现如果一个区间 $[l,r]$ 合法，它的分界点在 $r$ 的话，$[l,r-1]$ 未必合法。所以这个二分是假的。

转化一下题意：把原排列按是否 $\le x$ 搞成 $01$ 序列，那么合法的序列就是一段 $0$ 拼上一段 $1$。

这个东西直接套路的扫描线扫值域就行，发现每次会有一个 $0$ 变为 $1$。

注意到每次合法的区间相当于，从序列里选出来恰好由一段 $0$ 一段 $1$ 构成，且左右端点两边的数都与端点不相同的子段。然后就是在左边那段选一个位置，右边那段选一个位置，比方说选了 $l,r$，那么区间 $[l,r]$ 就是合法的。

注意到对于每两个相邻的连续段，合法的区间形如一个矩阵（左端点（横坐标）在 $[l,x]$，右端点（纵坐标）在 $[x+1,r]$）。

然后我们就需要，支持 $q$ 次询问一个点是否被某个矩形覆盖过。

不难发现每次 $01$ 序列变化后，变化的矩阵数量为 $O(1)$ 级别的，所以可以暴力搞出来所有矩阵，然后直接上主席树维护。

但是这个东西会有一些冗余。注意到我们只需要考虑之前没有出现的矩形。

比方说现在有三个 $01$ 连续段，中间的连续段有一个 $0$ 要变成 $1$。首先新增的是改的那个位置到原来它所在段的每个位置（除了自己）。

然后如果这个位置 $i$ 旁边有至少一个 $1$，还会增加形如 $(x,y,i,i)$ 或 $(i,i,x,y)$ 的矩阵。

于是我们把所有矩形搞了出来，把这个矩形的贡献拆到 $x_1$ 和 $x_2+1$ 上丢进主席树里维护就好了。由于每次更改是区间加，所以要标记永久化。

### 代码

```cpp
#include<bits/stdc++.h>
// #define int long long
#define N 800005
#define inf 2e18
#define mod 1000000007
#define pii pair<int,int>
#define x first
#define y second
using namespace std;
int T=1,n,q,a[N],p[N],rt[N],bel[N];
struct node{
    int l1,r1,l2,r2;
};
struct seg{
    int l,r,v;
};
vector<node>all;
vector<seg>qry[N];
struct dsgt{
    int ls[N<<5],rs[N<<5],tr[N<<5],lzy[N<<5],cnt;
    int build(int l,int r){
        int p=++cnt;
        if(l==r)return p;
        int mid=l+r>>1;
        ls[p]=build(l,mid);
        rs[p]=build(mid+1,r);
        return p;
    }
    void modify(int &p,int pre,int l,int r,int L,int R,int v){
        p=++cnt;
        tr[p]=tr[pre]+(min(r,R)-max(l,L)+1)*v;
        lzy[p]=lzy[pre];
        ls[p]=ls[pre];
        rs[p]=rs[pre];
        if(l>=L&&r<=R){
            lzy[p]+=v;
            return;
        }
        int mid=l+r>>1;
        if(L<=mid)modify(ls[p],ls[pre],l,mid,L,R,v);
        if(R>mid)modify(rs[p],rs[pre],mid+1,r,L,R,v);
    }
    int qry(int p,int l,int r,int L,int R,int sum){
        if(l>=L&&r<=R)return tr[p]+sum*(r-l+1);
        int mid=l+r>>1;
        int res=0;
        if(L<=mid)res+=qry(ls[p],l,mid,L,R,sum+lzy[p]);
        if(R>mid)res+=qry(rs[p],mid+1,r,L,R,sum+lzy[p]);
        return res;
    }
}dsgt;
void solve(int cs){
    if(!cs)return;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        p[a[i]]=i;
    }
    set<int>s0,s1;
    s0.insert(0);
    s0.insert(n+1);
    s1.insert(0);
    s1.insert(n+1);
    for(int i=1;i<=n;i++){
        s0.insert(i);
    }
    for(int j=1;j<=n;j++){
        int i=p[j];
        auto ao=s1.lower_bound(i);
        int nxt=(*ao)-1;
        ao--;
        int pre=(*ao)+1;
        if(a[i-1]>a[i])all.push_back({pre,i-1,i,i});
        if(a[i+1]>a[i])all.push_back({i,i,i+1,nxt});
        s0.erase(i);
        s1.insert(i);
        if(a[i-1]>a[i]&&a[i+1]>a[i])continue;
        if(a[i-1]<a[i]&&a[i+1]<a[i]){
            auto it1=s0.upper_bound(i);
            int r=(*it1)-1;
            it1--;
            int l=(*it1)+1;
            auto it=s1.lower_bound(l);it--;
            int L=(*it)+1;
            it=s1.upper_bound(r);
            int R=(*it)-1;
            all.push_back({L,l-1,l,r});
            all.push_back({l,r,r+1,R});
        }
        else{
            if(a[i-1]<a[i]){
                auto it1=s0.lower_bound(i);it1--;
                int r=(*it1);
                if(r>0){
                    auto it=s1.lower_bound(r);it--;
                    int l=(*it)+1;
                    all.push_back({l,r,i,i});
                }
            }
            else{
                auto it1=s0.upper_bound(i);
                int l=(*it1);
                if(l<n+1){
                    auto it=s1.upper_bound(l);
                    int r=(*it)-1;
                    all.push_back({i,i,l,r});
                }
            }
        }
    }
    for(auto it:all){
        if(it.l1>it.r1||it.l2>it.r2)continue;
        qry[it.l1].push_back({it.l2,it.r2,1});
        qry[it.r1+1].push_back({it.l2,it.r2,-1});
    }
    rt[0]=dsgt.build(1,n);
    for(int i=1;i<=n;i++){
        dsgt.modify(rt[i],rt[i-1],1,n,1,n,0);
        for(auto it:qry[i]){
            dsgt.modify(rt[i],rt[i],1,n,it.l,it.r,it.v);
        }
    }
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        int l,r;
        scanf("%d%d",&l,&r);;
        if(dsgt.qry(rt[l],1,n,r,r,0))printf("YES\n");
        else printf("NO\n");
        if(i%10==0)fflush(stdout);
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    // init();
    // cin>>T;
    for(int cs=1;cs<=T;cs++){
        solve(cs);
    }
    return 0;
}
```

---

## 作者：IkunTeddy (赞：2)

Edu 考以前 CF 的原？


# 题目分析

原题 [CF1887D Split](https://www.luogu.com.cn/problem/CF1887D)。

我们先考虑原题，因为可以离线，所以会稍微弱一点。

这类子区间问题，显然可以直接猫树做，但不好推广至在线。

看到跟最值相关，我们考虑**枚举最值**，算合法的包含其的区间。

我们不妨枚举左半边的最大值 $i$ 。考虑左端点的范围，令 $x$ 为 $i$ 左边第一个大于 $a_i$ 的下标，那么显然有 $x<l\le i$。

接下来考虑右端点的范围，令 $y$ 为 $i$ 右边第一个大于 $a_i$ 的下标，那么显然我们将分解点放在 $y-1$ 最优，这样可以使右边的最小值尽可能大。令 $z$ 为 $y$ 右边第一个小于 $a_i$ 的下标，显然有 $y\le r<z$。

我们发现需要求解的下标都是有关 $a_i$ 的偏序关系，所以我们按**值域扫描线**，再用 set 维护下标信息即可。

综上，所有以 $i$ 作为左半边最大值的合法区间已求出。现在问题转化为矩阵加，单点查。离线下来树状数组即可。

回到本题，两种情况基本类似，正反各做一遍即可，就不赘述了。问题在于解决在线的问题，对于此类问题的通用解法就是用**主席树维护每个扫描线版本的信息**，以做到在线查询。

时间复杂度 $O((n+q)\log n)$，空间复杂度 $O(n\log n)$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
//
const int maxn=2e5+10;
int n,q;
int s[maxn],p[maxn];
int ans[maxn];
set<int>S1,S2;
struct Update{int l,r,k;};
struct Query{int l,id;};
vector<Update>upt[maxn];
struct node{
	int ls,rs;
	int tag;
}tree[maxn*100];
int rt[maxn],nodecnt;
int copynode(int p){
	int v=++nodecnt;
	tree[v]=tree[p];
	return v;
}
int update(int p,int l,int r,int L,int R,int k){
	int v=copynode(p);
	if(l>=L&&r<=R)return tree[v].tag+=k,v;
	int mid=(l+r)>>1;
	if(L<=mid)tree[v].ls=update(tree[p].ls,l,mid,L,R,k);
	if(R>mid)tree[v].rs=update(tree[p].rs,mid+1,r,L,R,k);
	return v;
}
int ask(int v,int l,int r,int x){
	if(l==r)return tree[v].tag;
	int mid=(l+r)>>1;
	if(x<=mid)return ask(tree[v].ls,l,mid,x)+tree[v].tag;
	else return ask(tree[v].rs,mid+1,r,x)+tree[v].tag;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&s[i]),p[s[i]]=i;
	S1.insert(0),S1.insert(n+1),S2.insert(0),S2.insert(n+1);
	for(int i=1;i<=n;i++)S2.insert(i);
	for(int x=1;x<=n;x++){
		int i=p[x],L1,R1=i,L2,R2;
		S2.erase(i),S1.insert(i);
		L1=*(--S2.lower_bound(i))+1,L2=*S2.lower_bound(i),R2=*S1.lower_bound(L2)-1;
		upt[L2].push_back({L1,R1,1});
		upt[R2+1].push_back({L1,R1,-1});
	}
	S1.clear(),S2.clear();
	S1.insert(0),S1.insert(n+1),S2.insert(0),S2.insert(n+1);
	for(int i=1;i<=n;i++)S2.insert(i);
	for(int x=1;x<=n;x++){
		int i=p[x],L1,R1,L2=i,R2;
		S2.erase(i),S1.insert(i);
		R2=*S2.lower_bound(i)-1,R1=*(--S2.lower_bound(i)),L1=*(--S1.lower_bound(R1))+1;
		upt[L2].push_back({L1,R1,1});
		upt[R2+1].push_back({L1,R1,-1});
	}
	for(int i=1;i<=n;i++){
		rt[i]=rt[i-1];
		for(Update p:upt[i])rt[i]=update(rt[i],1,n,p.l,p.r,p.k);
	}
	scanf("%d",&q);
	for(int i=1,l,r;i<=q;i++){
		scanf("%d%d",&l,&r);
		if(ask(rt[r],1,n,l))printf("YES\n");
		else printf("NO\n");
		if(i%10==0)fflush(stdout);
	}

	
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

倍增，但是想法不同。

两种限制显然是对称的，因此只需要考虑第一种限制。

下文中分割点指的是对于 $[l,r]$ 的分割点 $p$，分割得到 $[l,p-1],[p,r]$ 这两个区间。

对于一个分割点 $p(p\ne l)$，我们容易有 $a_{p-1}<a_p$，否则把 $p-1$ 划给 $p$ 一定不劣。

对于每个位置 $i$，我们单调栈求出 $f_i$ 表示 $i$ 前面第一个小于 $a_i$ 的位置，然后 ST 表+二分找到 $g_i$ 表示最小的满足 $\max\{a_{g_i,\cdots f_i}\}<a_i$ 的位置。

然后对于每次查询，容易想到枚举最小值，从 $r$ 一直通过 $r\to f_r$ 的方式，这样显然能遍历所有后缀最小值，只需要保证在路径上 $g_r\le l$ 即可，注意这里判断 $r$ 的时候还需要保证 $f_r\ge l$，否则左边会是一个空区间。 

然后你就会发现这个路径是固定的，倍增即可。

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N=2e5+5;
int n,q,a[N],f[N][20],g[N][20],ff[N][20],gg[N][20],st_max[N][20],st_min[N][20];
stack<int> s;
int qmax(int l,int r){
	int k=__lg(r-l+1);
	return max(st_max[l][k],st_max[r-(1<<k)+1][k]);
}
int qmin(int l,int r){
	int k=__lg(r-l+1);
	return min(st_min[l][k],st_min[r-(1<<k)+1][k]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),st_max[i][0]=st_min[i][0]=a[i];
	for(int i=1;i<=__lg(n);++i) for(int j=1;j+(1<<i)-1<=n;++j){
		st_max[j][i]=max(st_max[j][i-1],st_max[j+(1<<i-1)][i-1]);
		st_min[j][i]=min(st_min[j][i-1],st_min[j+(1<<i-1)][i-1]);
	}
	for(int i=n;i;--i){
		while(s.size()&&a[s.top()]>a[i]){
			f[s.top()][0]=i;
			s.pop();
		}
		s.emplace(i);
	}
	while(s.size()) f[s.top()][0]=0,s.pop();
	for(int i=1;i<=n;++i){
		if(!f[i][0]){
			g[i][0]=inf;
			continue;
		}
		int l=1,r=f[i][0];
		while(l<r){
			int mid=l+r>>1;
			if(qmax(mid,f[i][0])<a[i]) r=mid;
			else l=mid+1;
		}
		g[i][0]=r;
	}
	for(int i=n;i;--i){
		while(s.size()&&a[s.top()]<a[i]){
			ff[s.top()][0]=i;
			s.pop();
		}
		s.emplace(i);
	}
	while(s.size()) ff[s.top()][0]=0,s.pop();
	for(int i=1;i<=n;++i){
		if(!ff[i][0]){
			gg[i][0]=inf;
			continue;
		}
		int l=1,r=ff[i][0];
		while(l<r){
			int mid=l+r>>1;
			if(qmin(mid,ff[i][0])>a[i]) r=mid;
			else l=mid+1;
		}
		gg[i][0]=r;
	}
	for(int i=1;i<=__lg(n);++i) for(int j=1;j<=n;++j){
		f[j][i]=f[f[j][i-1]][i-1];
		g[j][i]=min(g[j][i-1],g[f[j][i-1]][i-1]);
		ff[j][i]=ff[ff[j][i-1]][i-1];
		gg[j][i]=min(gg[j][i-1],gg[ff[j][i-1]][i-1]);
	}
	scanf("%d",&q);
	while(q){
		q-=10;
		for(int i=1;i<=10;++i){
			int l,r,p,res=inf;
			scanf("%d%d",&l,&r),p=r;
			for(int k=__lg(n);~k;--k) if(f[p][k]>=l){
				res=min(res,g[p][k]);
				p=f[p][k];
			}
			p=r;
			for(int k=__lg(n);~k;--k) if(ff[p][k]>=l){
				res=min(res,gg[p][k]);
				p=ff[p][k];
			}
			if(res<=l) puts("YES");
			else puts("NO");
		}
		fflush(stdout);
	}
	return 0;
}
```

---

## 作者：masonpop (赞：1)

做这题上来啪的一下就是一个伪算以为自己会了还写了一些奇异搞笑注释结果 wa on 14，乐。不过又想了一下就会正解了，注释是不是没写错来着。

固定 $x$，将 $\le x$ 的看作 $0$，$>x$ 的看作 $1$，那么区间合法等价于其由一段前缀 $0$ 和一段后缀 $1$ 构成。提取出相邻两段极长的 $0,1$，那么合法的区间形如 $L\in [l_0,r_0],R\in [l_1,r_1]$，对应到二维平面上是一个矩形。考虑按 $x$ 的大小扫，那么每次相当于把一个 $1$ 变成 $0$，可能会产生一个新的 $0$ 连续段，找出加入后的极长连续段，以及其之后的极长 $1$ 连续段，那么只是相当于新加入一个矩形！

于是问题就很简单了，给定 $O(n)$ 次矩形加，然后 $q$ 次单点查，强制在线。直接扫描线即可。把扫描线时的线段树可持久化一下就行了。感觉这个强制在线是纯乐子（

找连续段部分写的是 BIT 套二分，改成线段树二分很容易做到单 $\log$。

[submission](https://codeforces.com/contest/2111/submission/322870409)。

---

