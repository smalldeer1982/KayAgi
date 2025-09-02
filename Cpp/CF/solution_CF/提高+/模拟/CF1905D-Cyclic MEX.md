# Cyclic MEX

## 题目描述

For an array $ a $ , define its cost as $ \sum_{i=1}^{n} \operatorname{mex} ^\dagger ([a_1,a_2,\ldots,a_i]) $ .

You are given a permutation $ ^\ddagger $ $ p $ of the set $ \{0,1,2,\ldots,n-1\} $ . Find the maximum cost across all cyclic shifts of $ p $ .

 $ ^\dagger\operatorname{mex}([b_1,b_2,\ldots,b_m]) $ is the smallest non-negative integer $ x $ such that $ x $ does not occur among $ b_1,b_2,\ldots,b_m $ .

 $ ^\ddagger $ A permutation of the set $ \{0,1,2,...,n-1\} $ is an array consisting of $ n $ distinct integers from $ 0 $ to $ n-1 $ in arbitrary order. For example, $ [1,2,0,4,3] $ is a permutation, but $ [0,1,1] $ is not a permutation ( $ 1 $ appears twice in the array), and $ [0,2,3] $ is also not a permutation ( $ n=3 $ but there is $ 3 $ in the array).

## 说明/提示

In the first test case, the cyclic shift that yields the maximum cost is $ [2,1,0,5,4,3] $ with cost $ 0+0+3+3+3+6=15 $ .

In the second test case, the cyclic shift that yields the maximum cost is $ [0,2,1] $ with cost $ 1+1+3=5 $ .

## 样例 #1

### 输入

```
4
6
5 4 3 2 1 0
3
2 1 0
8
2 3 6 7 0 1 4 5
1
0```

### 输出

```
15
5
31
1```

# 题解

## 作者：wxzzzz (赞：7)

### 思路

首先肯定要枚举循环节，考虑以 $O(\log n)$ 的时间复杂度求出全局 $\operatorname{mex}$ 之和。

对于一个数 $i$，$1\sim i-1$ 中 $p_i$ 一定没有出现过（因为是个排列），此时 $p_i$ 就可以作为 $1\sim i-1$ 中所有点的候选 $\operatorname{mex}$。

显然，某个位置的 $\operatorname{mex}$ 便是其所有候选 $\operatorname{mex}$ 取 $\min$。

因此，对于每个位置 $i$，需要更新：$\forall j\in[1,i-1],\operatorname{mex}_j\gets \min(\operatorname{mex}_j,p_i)$。

对于一次循环移位，操作是将 $p_1$ 移至 $p_n$，更新：$\forall i\in[1,n-1],\operatorname{mex}_i\gets \min(\operatorname{mex}_i,p_n)$， $\operatorname{mex}_n$ 则显然是全局 $\operatorname{mex}$，即 $n$。

上述过程显然是吉司机线段树板子，但是发现 $\operatorname{mex}_j$ 单调不减，因此可以直接在线段树上递归处理 $\operatorname{mex}_j<p_i$ 的 $j$，其过程在单调不减序列上相当于线段树二分，时间复杂度 $O(\log n)$。

具体实现详见代码。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, p[2000005];
long long ans;
struct node {
    int l, r, to, minn, maxn;
    long long sum;
} t[2000005 << 2];
void pushup(int p) {
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    t[p].minn = min(t[p << 1].minn, t[p << 1 | 1].minn);
    t[p].maxn = max(t[p << 1].maxn, t[p << 1 | 1].maxn);
}
void pushdown(int p) {
    if (t[p].to == -1)
        return;

    t[p << 1].sum = 1ll * (t[p << 1].r - t[p << 1].l + 1) * t[p].to;
    t[p << 1].minn = t[p << 1].maxn = t[p << 1].to = t[p].to;
    t[p << 1 | 1].sum = 1ll * (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * t[p].to;
    t[p << 1 | 1].minn = t[p << 1 | 1].maxn = t[p << 1 | 1].to = t[p].to;
    t[p].to = -1;
}
void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    t[p].to = -1;

    if (l == r) {
        t[p].maxn = t[p].minn = t[p].sum = 1e9;
        return;
    }

    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}
void change(int p, int l, int r, int k) {
    if (t[p].maxn <= k)
        return;

    if (t[p].l >= l && t[p].r <= r && t[p].minn > k) {
        t[p].sum = 1ll * (t[p].r - t[p].l + 1) * k;
        t[p].maxn = t[p].minn = k;
        t[p].to = k;
        return;
    }

    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;

    if (l <= mid)
        change(p << 1, l, r, k);

    if (mid < r)
        change(p << 1 | 1, l, r, k);

    pushup(p);
}
long long query(int p, int l, int r) {
    if (t[p].l >= l && t[p].r <= r)
        return t[p].sum;

    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    long long ret = 0;

    if (l <= mid)
        ret += query(p << 1, l, r);

    if (mid < r)
        ret += query(p << 1 | 1, l, r);

    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;

    while (T--) {
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> p[i];

        build(1, 1, n * 2);

        for (int i = 2; i <= n; i++)
            change(1, 1, i - 1, p[i]);

        change(1, n, n, n);
        ans = query(1, 1, n);

        for (int pl = 2, pr; pl <= n; pl++) {
            pr = pl + n - 1;
            change(1, pl - 1, pl - 1, 0);
            change(1, pl, pr - 1, p[pl - 1]);
            change(1, pr, pr, n);
            ans = max(ans, query(1, pl, pr));
        }

        cout << ans << '\n';
    }

    return 0;
}
```

### 后记

话说这题 VP 赛场上没看，赛后 @[modfish](https://www.luogu.com.cn/user/605226) 告诉我这题，并说这题很简单，然后语文课上想出来了（雾

这题一开始也卡了几分钟，直到我想起[我们尊敬的学长](https://www.luogu.com.cn/user/229378)所说：

> 很多题一时半会儿没有思路，这时候多在草稿纸上写写画画，常常能得到启发。

便画了个图，就会了。

令人不得不感慨：画图是 OI 之母。

---

## 作者：MoyunAllgorithm (赞：5)

与官方题解和题解区的不同，本 $O(N)$ 题解不需要压缩状态，也不需要 `deque` 之类的东西。

**分析**

看到 Cycle Shift 轮换想到把序列复制一份连起来考虑。这样更加方便。

在这个比原来的长度长一倍的新序列上，定义 $l(i)$ 表示 $i$ 左边第一个 $<a_i$ 的元素的下标。特别地，若 $a_i=0$，$l(i)=\max(i-N+1,1)$。

容易发现 $l(i)$ 的意义是：在 $[l(i),i)$ 内的元素的前缀 $\text{MEX}$ 为 $a_i$。

在这个序列上维护长度为 $N$ 的滑动区间。初始它包含 $[1,N]$。这时如何求出当前答案？设 $i=N$。答案加上 $a_i \times (i-l(i))$，因为这段区间内的元素的前缀 $\text{MEX}=a_i$。随后 $i := l(i)$。这样就能得到该区间的答案（最后不要忘了加上 $N$）。

求出区间在 $[1,N]$ 的答案，怎么求出 $[2,N+1],[3,N+2],\cdots,[N-1,2N-1]$ 的答案呢？

当区间往右移动一格，会带来以下影响：

- 左侧元素离开；

- 右侧元素进入。设右端点为 $R$，则 $[l(R),R)$ 内的元素的 $\text{MEX}$ 变为 $a_R$。

对于左侧元素离开，容易处理。如果 $0$ 离开了答案 $-1$；否则 $-0$。

对于右侧元素进入，发现很难处理。因为这段受影响的区间原来的 $\text{MEX}$ 我们难以求出。从 $R-1$ 跳 $l$ 跳到 $l(R)$ 固然可行，但时间难以保证。

定义 $\text{sum}(i)$ 表示从 $i$ 下标一直跳 $l$，跳到值为 $0$ 的元素时停止，这一路径的 $\text{MEX}$ 和。

$\text{sum}(i)=\text{sum}(l(i))+a_i \times (i-l(i))$。

则右侧元素带来的删除为 $\text{sum}(R-1)-\text{sum}(l(R))$。之后加上新元素带来的 $a_R \times (R-l(R))$ 即可。

$O(N)$。

```cpp
#include <bits/stdc++.h>
#define PII pair<int,int>
#define LL long long
using namespace std;
const int MAXN=2e6+5;
int T;
int N,tp;
int a[MAXN],sta[MAXN],l[MAXN];
LL sum[MAXN];
LL ans=0;
vector<int>gra[MAXN];
int in[MAXN];
bool Go(int x,int y)
{
    if(y<a[x]) return 1;
    if(a[x]==0&&y==0) return 1;
    return 0;
}
int main()
{
	//freopen("c.in","r",stdin);
	//freopen("c.out","w",stdout);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        for(int i=1;i<=N;i++) scanf("%d",&a[i]);
        for(int i=N+1;i<=2*N;i++) a[i]=a[i-N];
        for(int i=1;i<=2*N;i++) l[i]=0;
        tp=0;
        for(int i=2*N;i;i--)
        {
            while(tp&&Go(sta[tp],a[i]))
            {
                l[sta[tp]]=i;
                tp--;
            }
            sta[++tp]=i;
        }
        for(int i=1;i<=tp;i++) l[sta[tp]]=1;
        for(int i=1;i<=2*N;i++) if(a[i]==0) l[i]=max(1,i-N+1);
        //for(int i=1;i<=2*N;i++) printf("[%d]",l[i]);
        ans=0;
        LL res=0;
        for(int i=1;i<=2*N;i++) gra[i].clear();
        for(int i=2;i<=2*N;i++) if(a[i]) gra[l[i]].push_back(i);
        for(int i=1;i<=2*N;i++) if(a[i]==0) sum[i]=0;
        for(int i=1;i<=2*N;i++) 
        {
            for(int j:gra[i]) sum[j]=sum[i]+1ll*a[j]*(j-i);
        }
        //f/or(int i=1;i<=2*N;i++) printf("S%lld\n",sum[i]);
        res=sum[N]+N;
        ans=max(ans,res);
        //printf("%d %lld\n",N,res);
        for(int i=N+1;i<2*N;i++)
        {
            res-=(a[i-N]==0)?1:0;
            res-=sum[i-1]-sum[l[i]];
            res+=1ll*a[i]*(i-l[i]);
            if(a[i]==0) res=N;
            ans=max(ans,res);
          //  printf("RES%d %lld\n",i,res);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：zhlzt (赞：5)

### 题解
让我们分析一下序列在向左循环移位时，每个前缀 $\text{mex}$ 的值是如何变化的（注意到 $p$ 是 $0\sim n-1$ 的排列）：

- 第一个前缀 $\text{mex}$ 被弹出。
- 每个前缀 $\text{mex}$ 的值小于 $p_1$ 时不会发生变化。
- 值大于 $p_1$ 的每个前缀 $\text{mex}$ 变为 $p_1$ 。
- $n$ 被追加到后面。

让我们对前缀 $\text{mex}$ 进行压缩（即保留其值及其出现次数，而不是保留多个相同的值）。易知前缀 $\text{mex}$ 的值是单调不降的，因此我们可以用一个单调队列来简单地模拟上述的存储方式。

这个解决方案只需 $O(n)$ 的时间复杂度。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+10;
int p[maxn];
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",p+i);
		deque<pair<int,int> >dq; 
		/* 定义单调队列，
		first 表示值，second表示数量 */
		vector<int>cnt(n+1);
		int mex=0; ll sum=0;
		for(int i=1;i<=n;i++){
			cnt[p[i]]++;
			while(cnt[mex]) mex++;
			dq.push_back({mex,1}); sum+=mex;
		}
		ll ans=sum;
		for(int i=1;i<n;i++){
			pair<int,int> cur={p[i],0};
			sum-=dq.front().first;
			dq.front().second--;
			/* 当 i 成为序列之首时， 
			其对应的 mex 也必定是最小的 */ 
			if(dq.front().second==0) dq.pop_front();
			while(!dq.empty()){
				if(dq.back().first<p[i]) break;
				sum-=1ll*dq.back().first*dq.back().second;
				cur.second+=dq.back().second; 
				dq.pop_back();
			} 
			dq.push_back(cur);
			sum+=1ll*cur.first*cur.second;
			dq.push_back({n,1}); sum+=n;
			ans=max(ans,sum);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Creeper_l (赞：5)

> 题意：给定一个长度为 $n$ 的排列 $a$，$a_i \in [0,n-1]$。你可以将这个排列进行循环移位，最小化 $\sum_{i=1}^{n} \text{mex}_{j=1}^i a_j$ 的值。

首先我们可以先计算出最初情况下每一个 $i$ 位置的 $\text{mex}$ 值。这个序列一定是单调非严格递增的。

首先有一个比较显然的 $\text{Trick}$：$\text{mex}_{j=1}^{i}a_j=\min_{j=i+1}^n a_j$。

考虑将 $a_1$ 循环移到第 $n$ 位后会有什么影响。首先所有位置的 $\text{mex}$ 值都要向左移动一位，第 $n$ 位的值一定还是 $n$。对于现在 $1$ 到 $i-1$ 位上的值，因为第 $n$ 位上的值变为了 $a_1$，而原来这些位置并没有算上 $a_1$ 对他们的贡献，所以这些位置上的值都要和 $a_1$ 取 $\min$。

上述过程可以用单调队列维护。具体的，每次循环移位需要执行以下几步操作：

- 将 $a_1$（队首）弹出。

- 将队尾大于 $a_1$ 的数弹出，并在队尾插入相等数量的 $a_1$。

- 在队尾插入 $n$。

为了保证 $O(n)$ 的时间复杂度，我们不用插入相同的数，而是直接记录这个数的数量即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair <int,int> pii;
const int MAXN = 1e6 + 10;
typedef pair <int,int> pii;
deque <pii> q;
int t,n,a[MAXN],mex[MAXN],ans,sum;
signed main()
{
	cin >> t;
	while(t--)
	{
		while(!q.empty()) q.pop_front();
		cin >> n;
		for(int i = 1;i <= n;i++) cin >> a[i];
		for(int i = 1;i <= n + 1;i++) mex[i] = 1e18;
		mex[n] = n;
		for(int i = n;i >= 1;i--) mex[i - 1] = min(mex[i],a[i]); 
		mex[0] = -1;ans = 0;
		for(int i = 1;i <= n;i++)
		{
			if(mex[i] != mex[i - 1]) q.push_back(make_pair(mex[i],1));
			else 
			{
				pii tmp = make_pair(q.back().first,q.back().second + 1);
				q.pop_back(),q.push_back(tmp);
			}
			ans += mex[i];
		}
		sum = ans;
		for(int i = 1;i < n;i++)
		{
			sum -= q.front().first;
			if(q.front().second == 1) q.pop_front();
			else q.front().second--;	
			int num = 0;
			while(!q.empty() && q.back().first > a[i]) 
			{
				sum -= q.back().first * q.back().second;
				num += q.back().second;
				q.pop_back();
			}
			sum += n,sum += num * a[i];
			q.push_back(make_pair(a[i],num));
			q.push_back(make_pair(n,1));
			ans = max(ans,sum);
		}
		cout << ans << endl;
	}
    return 0;
}



```


---

## 作者：Comentropy (赞：4)

## 题意

定义集合运算 ```mex``` 为集合内未出现的最小非负整数。

给一个 $0\sim n-1$ 的排列 $p$，问其所有循环排列的前缀集合的 ```mex``` 值之和，即 
$$
\sum_{i=1}^n mex \{p_1,p_2,\dots, p_i\}
$$

的最大值。

## 解法

我们不妨向左循环移动，进行考虑（好想一点）。维护一个队列，考虑每次移动对于总和的影响:

1. 弹出第一个前缀的 ```mex```。 
2. 对于每个前缀的 ```mex``` 值小于 $p_1$（移动后的首项）时，其值不会发生影响；对于值大于 $p_1$ 的，将其 ```mex``` 值改为 $p_1$。
3. 根据定义，最后一项的 ```mex``` 值为 $n$，于是将 $n$ 加入队尾。 

上述过程的进行可以压缩每个值的数量，因为很显然，前缀集合的 ```mex``` 值是单调不下降的。

于是每次的 ```mex``` 值，可以从后向前枚举，然后再将修改后的一项加入队尾。

最后，很显然，前面移来的一项，也会加入队尾，根据 ```mex``` 的定义，其值为 $n$。

经过如此的压缩，要处理的项逐渐减少，总的时间复杂度为 $O(n)$。

具体地，可以做如下思考：每次将数移至队尾，下一次再更新，要更新的只有当前队尾，和前面大于当前数的 ```mex```。如果当前操作数多，那么，这一次会将相当多的数都压缩成同一堆，下一次再更新的时候的数目会变少。以上为感性理解。

具体证明十分冗长，在此给出一个思路，如果将 $a_i$ 移动，则，除队尾外 $\forall mex<a_i$，据此可以展开证明。

均摊下来，每次做 $O(1)$ 次操作。

实现时注意 ```long long```，代码如下。

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<deque>
using namespace std;
const int N=1e6+50;
int a[N];
bool f[N];
void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),f[i]=false;
	f[0]=false;
	deque<pair<int,int> > q;
	int now=0;
	long long sum=0;
	for(int i=1;i<=n;i++){
		f[a[i]]=true;
		while(f[now])
			now++;
		q.push_back({now,1});
		sum+=now;
	}
	long long ans=sum;
	for(int i=1;i<n;i++){
		pair<int,int> tmp={a[i],0};
		sum-=q.front().first;
		q.front().second--;
		if(!q.front().second)
			q.pop_front();
		while(!q.empty() && q.back().first>=a[i]){
			sum-=(long long)q.back().first*q.back().second;
			tmp.second+=q.back().second;
			q.pop_back();
		}
		q.push_back(tmp);
		sum+=n+1ll*tmp.first*tmp.second;
		q.push_back({n,1});
		ans=max(ans,sum);
	}
	printf("%lld\n",ans);
	return ;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--)
		solve();
	return 0;
}
```


---

## 作者：harmis_yz (赞：3)

## 分析

乱搞题。

右移若干次很显然可以破环成链，然后 $l,r$ 指针在这个长度为 $2n$ 的序列上右移。每种状态的答案就是 $[l,r]$ 的答案。

考虑相邻两种状态的变化量。设上一次 $l'$ 指向的值为 $p_{l'}$，则到当前状态的变化量就是：$-\operatorname{mex}(p_{l'})-sum + cnt \times p_{l'}+n$。第一项和最后一项很显然，就是 $l'$ 从开头变到结尾了。第二项 $sum$ 表示 $\operatorname{mex}$ 值比 $p_{l'}$ 大的和。因为在现在的前 $n-1$ 项中 $\operatorname{mex}$ 值是不可能超过 $p_{l'}$ 的（$p_{l'}$ 空出来了）。第三项的 $cnt$ 就是比 $p_{l'}$ 大的值的数量。

这个变化量用线段树乱搞就行了，相当于是区间赋值。在线段树上二分，统计一下最大值和最小值即可。最后的求某种状态 $\operatorname{mex}$ 值之和就是区间 $[l,r]$ 的和。复杂度 $O(n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define re register
#define il inline
 
const int N=1e6+5,M=1e7+5;
int n,p[N];
bool cnt[N];
struct tree{
	long long l,r,sum,lz,mx,mi;
}tr[M];
 
il void up(int now){
	tr[now].sum=tr[now<<1].sum+tr[now<<1|1].sum;
	tr[now].mx=max(tr[now<<1].mx,tr[now<<1|1].mx);
	tr[now].mi=min(tr[now<<1].mi,tr[now<<1|1].mi);
	return ;
}
il void down(int now){
	if(tr[now].lz!=-1){
		tr[now<<1].lz=tr[now<<1|1].lz=tr[now].lz;
		tr[now<<1].sum=(tr[now<<1].r-tr[now<<1].l+1)*tr[now].lz;
		tr[now<<1|1].sum=(tr[now<<1|1].r-tr[now<<1|1].l+1)*tr[now].lz;
		tr[now<<1].mx=tr[now<<1|1].mx=tr[now].lz;
		tr[now<<1].mi=tr[now<<1|1].mi=tr[now].lz;
		tr[now].lz=-1;
	}
	return ;
}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r,tr[now].sum=0,tr[now].lz=-1,tr[now].mx=0,tr[now].mi=1e18;
	if(l==r) return ;
	int mid=l+r>>1;
	build(now<<1,l,mid),build(now<<1|1,mid+1,r);
	return ;
}
il void insert(int now,int l,int r,int k){
	if(tr[now].l>=l&&tr[now].r<=r){
		tr[now].lz=k,tr[now].sum=(tr[now].r-tr[now].l+1)*k;
		tr[now].mx=k,
		tr[now].mi=k;
		return ;
	}
	down(now);
	int mid=tr[now].l+tr[now].r>>1;
	if(l<=mid) insert(now<<1,l,r,k);
	if(mid<r) insert(now<<1|1,l,r,k);
	up(now);return ;
}
il void insert2(int now,int l,int r,int k){
	if(tr[now].l>=l&&tr[now].r<=r){
		down(now);
		if(tr[now].mi>k){
			tr[now].lz=k,tr[now].sum=(tr[now].r-tr[now].l+1)*k;
			tr[now].mx=tr[now].mi=k;return ;
		}	
		if(tr[now<<1].mx>k) insert2(now<<1,l,r,k);
		if(tr[now<<1|1].mx>k) insert2(now<<1|1,l,r,k);
		up(now);return ;
	}
	down(now);
	int mid=tr[now].l+tr[now].r>>1;
	if(l<=mid&&tr[now<<1].mx>k) insert2(now<<1,l,r,k);
	if(mid<r&&tr[now<<1|1].mx>k) insert2(now<<1|1,l,r,k);
	up(now);return ;
}
il long long query(int now,int l,int r){
	if(tr[now].l>=l&&tr[now].r<=r) return tr[now].sum;
	down(now);
	int mid=tr[now].l+tr[now].r>>1;
	long long ans=0;
	if(l<=mid) ans+=query(now<<1,l,r);
	if(mid<r) ans+=query(now<<1|1,l,r);
	up(now);
	return ans;
}
 
il void solve(){
	scanf("%d",&n);
	for(re int i=1;i<=n;++i) scanf("%d",&p[i]);
	build(1,1,n*2);int lst=0;
	for(re int i=1;i<=n;++i){
		cnt[p[i]]=1;
		while(cnt[lst]) ++lst;
		insert(1,i,i,lst);
	}
	for(re int i=0;i<=n;++i) cnt[i]=0;
	long long maxx=query(1,1,n);
	int l=1,r=n;
	for(re int i=1;i<=n;++i){
		int now=p[l];
		int L=l+1,R=r;
		insert2(1,L,R,now);
		++l,++r;
		insert(1,r,r,n);
		maxx=max(maxx,query(1,l,r));
	}
	cout<<maxx<<"\n";return ; 
}
 
signed main(){
	int t;cin>>t;while(t--)
	solve();
	return 0;
}
```


---

## 作者：phigy (赞：2)

我们注意到排列 $p$ 有结论 $\text{mex}_{j=1}^ip_j=\min_{j=i+1}^np_j$。

因为 $\text{mex}_{j=1}^ip_j$ 表示最小的不在 $1$ 到 $i$ 的 $p$ 中出现的自然数，而在 $i+1$ 到 $n$ 中出现的数一定不在 $1$ 到 $i$ 中出现，并且 $p$ 包含 $0$ 到 $n-1$ 的所有数，故结论正确。

因此我们可以 $O(n)$ 求出初始 $b_i=\text{mex}_{j=1}^ip_j$ ，同时我们注意到 $b$ 是单调递增的。

观察一次位移操作 $b$ 会发生什么，首先有 $b_{i+1}\to b_i$，然后所有的 $b$ 对位移到末尾的 $a$ 取 $\min$，最后 $n\to b_n$。

我们注意到无论何时 $b$ 都是单调递增的，所以我们使用单调队列维护每个 $b$ 的出现次数，一次位移时将最小的 $b$ 减少一个，如果没有了就弹出，然后将 $>a$ 的 $b$ 弹出，然后插入等同于弹出数量的 $a$ 最后插入 $n$ 即可。

注意到每个 $a$ 入队和出队均为 $1$ 次，所以复杂度为 $O(n)$。

```cpp
#include <bits/stdc++.h>

#define REN 1000000
#define MAXN (REN+5)
#define int long long

using namespace std;

int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)) {if(c=='-') {f=-1;} c=getchar();}
    while(isdigit(c))  {x=x*10+c-'0';c=getchar();}
    return x*f;
}


int T;
int n;
int a[MAXN];
int st[MAXN],num[MAXN],l=1,r;
int mex[MAXN];
int t[MAXN];
int ans;
signed main()
{
    int i,j,k;
    T=read();
    while(T--)
    {
        l=1;r=0;
        n=read();
        for(i=1;i<=n;i++)
        {
            a[i]=read();
        }
        int minn=n,now=0;
        for(i=n;i>=1;i--)
        {
            now+=minn;
            mex[i]=minn;
            minn=min(minn,a[i]);
        }
        for(i=1;i<=n;i++)
        {
            if(mex[i]!=mex[i-1]||i==1)
            {
                r++;
                st[r]=mex[i];
                num[r]=1;
            }
            else
            {
                num[r]++;
            }
        }
        ans=now;
        for(i=1;i<n;i++)
        {
            num[l]--;
            now-=st[l];
            if(num[l]==0) {l++;}
            int cnt=0;
            while(st[r]>a[i]&&r>=l)
            {
                now-=st[r]*num[r];
                cnt+=num[r];
                r--;
            }
            r++;
            st[r]=a[i];
            num[r]=cnt;
            now+=cnt*a[i];
            r++;
            st[r]=n;
            num[r]=1;
            now+=n;
            ans=max(ans,now);
        }
        cout<<ans<<'\n';
        for(i=1;i<=n;i++) {t[a[i]]=0;}
    }
    return 0;
}
```


---

## 作者：huangrenheluogu (赞：2)

考虑序列动态的转动过程。

我们考虑一个比较具有代表性的转动。

![](https://cdn.luogu.com.cn/upload/image_hosting/gf7md6jn.png)

说明：上面是数组，下面是 $a_1\sim a_i$ 的 $\operatorname{mex}$ 值，由于 $a_1\sim a_n$ 的 $\operatorname{mex}$ 值显然是 $n$，因此不写了。

接下来，我们把 $2$ 移到后面，看看发生了什么。

![](https://cdn.luogu.com.cn/upload/image_hosting/3xrcgd1h.png)

发现，总共的总和 $res$ 减少了 $a_1\sim a_2$ 的贡献，并且在末尾大于等于 $a_1$ 的地方都变成了 $a_1$，并且序列后面增加了一个 $a_1$。

考虑怎么维护。

用 deque 暴力维护是 $O(n^2)$ 的。

可以用线段树维护下面的数组，然后二分查找断点，这样是 $O(n\log^2 n)$ 的，然后赛时就卡在这里了，最后没打。

可以用带权的 deque 维护即可，复杂度 $O(n)$，记录每一个数的值和数量。

注意写代码的时候 $n=2$ 的时候可能会在空的 deque 里取元素，害得我 RE 了好几发。

[code](https://codeforces.com/contest/1905/submission/237585597)

---

## 作者：xiaosi4081 (赞：1)

每次把序列最前面的数 $x$ 移动到序列最后面，观察这个操作对前缀 $\mathrm{mex}$ 的改变，记 $s_i$ 为以 $i$ 结尾的前缀 $\mathrm{mex}$。那么首先先把 $s_{[2, n]}$ 移动到 $s_{[1, n-1]}$，然后对于 $s_i$：

* 当 $s_i < x$ 时，将 $x$ 放到后面不会对其产生任何影响。
* 没有 $s_i = x$ 的情况。
* 当 $s_i > x$ 时，发现前缀缺失了 $x$，所以 $s_i \leftarrow x$（易得 $1 \sim x-1$ 都出现在以 $i$ 的前缀内，否则 $s_i < x$）

最后 $s_n \leftarrow n$。

然后 $s_i$ 单调不降，然后用单调队列维护，做完了。

```c++
#include<bits/stdc++.h>
#define pii pair<int, int>
#define int long long
using namespace std;
const int N = 2e6+5;
int t, n, p[N*2], vis[N*2], cur = 0;
deque<pii> q;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t--){
		cin >> n; q.clear();
		for(int i = 0; i <= n; i++) vis[i] = 0;
		for(int i = 1; i <= n; i++) cin >> p[i]; 
		int res = 0, ans = 0; cur = 0;
		for(int i = 1; i <= n; i++){
			vis[p[i]] = 1;
			while(vis[cur]) ++cur;
			q.push_back({cur, i});
			res += cur;
		} ans = res;
		for(int i = n+1; i < n*2; i++){
			int lst = q.front().first;
			res -= lst, q.pop_front();
			if(q.empty() || q.front().second != i-n+1) q.push_front({lst, i-n+1});
			int cur = i;
			while(q.size() && q.back().first >= p[i-n]){
				res -= q.back().first*(cur-q.back().second);
				cur = q.back().second;
				q.pop_back();
			}
			if(cur <= i) res += (i-cur)*p[i-n];
			if(cur <= i) q.push_back({p[i-n], cur});
			q.push_back({n, i}), res += n;
			ans = max(ans, res);
		} cout << ans << endl;
	} return 0;
}
```

---

## 作者：ARIS2_0 (赞：1)

这是一篇实现比较简单的题解，只使用了单调栈和普通线段树（无需二分），时间复杂度 $O(n\log n)$。

### 思路

对于一个长度为 $n$，数字从 $0$ 到 $n-1$ 的排列 $a$，我们有 $\operatorname{mex}(\{a_1,a_2,\dots,a_x\})=\min(a_{x+1},a_{x+2},\dots a_n)$，特别地，$\operatorname{mex}(\{a_1,a_2,\dots,a_n\})=n$。则题目转化为求 $\max(\sum_{i=1}^{n-1} \min(a_{i+1},a_{i+2},\dots,a_n)+n)$。

称 $\min(a_{i+1},a_{i+2},\dots,a_n)$ 为第 $i$ 位数字的贡献，特别地，第 $n$ 位的贡献为 $n$。 可以发现：

- 题目所求权值为第 $1$ 位到第 $n$ 位的贡献和。

- **只有不在 $0$ 前面的数字才有贡献**。

那么我们可以转化一下样例，本来是：

|$a_1$|$a_2$|$a_3$|$a_4$|$a_5$|$a_6$|
|:-:|:-:|:-:|:-:|:-:|:-:|
|5|4|3|2|1|0|
|4|3|2|1|0|5|
|3|2|1|0|5|4|
|2|1|0|5|4|3|
|1|0|5|4|3|2|
|0|5|4|3|2|1|

因为我们不关心 $0$ 前面的数字，可以变为（注意下表的下标不是原题的下标）：

|$a_1$|$a_2$|$a_3$|$a_4$|$a_5$|$a_6$|
|:-:|:-:|:-:|:-:|:-:|:-:|
|0|/|/|/|/|/|
|0|5|/|/|/|/|
|0|5|4|/|/|/|
|0|5|4|3|/|/|
|0|5|4|3|2|/|
|0|5|4|3|2|1|

发现实质上就是给定一个初始为 $0$ 的数列，每次往最后面加一个数，那么，原题变为：

给定一个初始为 $0$ 的数列，每次向数列最后面加一个数，同时计算贡献和，求操作 $n$ 次后，这 $n$ 个贡献和的最大值。特别地，初始那个 $0$ 的贡献为 $n$（因为它在第 $n$ 位）。

考虑加入第 $i$ 个数后会对每位贡献产生什么影响：此时，第 $i$ 个数的贡献为 $n$（因为它在第 $n$ 位），而第 $bef_i$ 到第 $i-1$ 个数的贡献会被改为 $a_i$（非输入的 $a_i$，而是指此时的第 $i$ 个数），其中 $bef_i$ 为最大的满足第 $pos$ 个数小于第 $i$ 个数的 $pos$。

这个修改是正确的，因为第 $bef_i+1$ 位到第 $i$ 位的数字都不小于第 $i$ 位的数字，而因为第 $bef_i$ 位数字的存在，第 $1$ 位到第 $bef_i$ 位数字的贡献不受影响。

至此，题目操作简化如下（使用伪代码，其中数组 $a$ 是通过若干次右移后满足 $a_1=0$ 的输入排列，$p_i$ 代表第 $i$ 个数的贡献，$bef_i$ 是对于**进行上述操作后的 $a$**，满足 $a_{bef_i}<a_i,bef_i<i$ 且 $bef_i$ 最大化）：

```cpp
p[1]=n;//先把0加进去
int ans=n;
for(int i=2;i<=n;i++){
    p[i]=n;
    p[bef[i]]=p[bef[i]+1]=...=p[i-1]=a[i];
    ans=max(ans,p[1]+p[2]+...+p[i]);
}
```

### 实现

发现 $p$ 数组需要支持区间修改、查询区间和，使用线段树维护，而 $bef_i$ 可以**等 $a$ 转换完毕后**使用单调栈求解，于是本题就做完了。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//10年OI一场空，不开long long见祖宗
const int inf=1e18,maxn=1e6+10;
int a[2*maxn],bef[maxn];//为了转换a要断环成链，数组a开了两倍空间
void ycl(int n){//用单调栈预处理bef数组
    stack<int>s;//s中存放的是编号而不是具体的值
    s.push(1);
    for(int i=2;i<=n;i++){
        while(s.size() and a[s.top()]>a[i])s.pop();
        bef[i]=s.top();//因为a[1]=0，所以栈不会为空
        s.push(i);
    }
}
int w[4*maxn],tag[2*maxn];//线段树数组和tag数组，4倍空间
bool inr(int l,int r,int cl,int cr){return cl<=l and r<=cr;}//[l,r]被完全包含于[cl,cr]
bool outr(int al,int ar,int bl,int br){return ar<bl or br<al;}//[al,ar]与[bl,br]无交
void pushup(int id){w[id]=w[id*2]+w[id*2+1];}
void maketag(int id,int len,int num){w[id]=num*len;}
void pushdown(int id,int l,int r){
    if(tag[id]){
        int mid=(l+r)/2;
        maketag(id*2,mid-l+1,tag[id]);
        maketag(id*2+1,r-mid,tag[id]);
        tag[id]=0;
    }
}
void change(int id,int l,int r,int cl,int cr,int num){//现在遍历到编号为id的区间[l,r]，需要修改的区间是[cl,cr]，要修改成num。
//下面check函数的id,l,r,cl,cr同理
    if(inr(l,r,cl,cr)){maketag(id,r-l+1,num);return;}
    if(outr(l,r,cl,cr))return;
    pushdown(id,l,r);
    int mid=(l+r)/2;
    change(id*2,l,mid,cl,cr,num);
    change(id*2+1,mid+1,r,cl,cr,num);
    pushup(id);
}
int check(int id,int l,int r,int cl,int cr){
    if(inr(l,r,cl,cr))return w[id];
    if(outr(l,r,cl,cr))return 0;
    pushdown(id,l,r);
    int mid=(l+r)/2;
    return check(id*2,l,mid,cl,cr)+check(id*2+1,mid+1,r,cl,cr);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
    while(t--){
        int n;cin>>n;
        for(int i=1;i<=4*n;i++){//多测清空
            w[i]=0;
            tag[i]=0;//因为修改的时候不会修改成0，所以可以初始化为0
        }
        int st=0;//记录原排列里0的位置
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(a[i]==0)st=i;
            a[n+i]=a[i];//断环成链
        }
        for(int i=1;i<=n;i++)a[i]=a[i+st-1];//更新a[1~n]
        ycl(n);//预处理出bef数组
        change(1,1,n,1,1,n);//p[1]=n
        int ans=n;
        for(int i=2;i<=n;i++){
            change(1,1,n,i,i,n);//p[i]=n;
            change(1,1,n,bef[i],i-1,a[i]);//p[bef[i]~i-1]=a[i]
            ans=max(ans,check(1,1,n,1,i));
        }
        cout<<ans<<"\n";
    }
	return 0;
}
```

---

## 作者：Locix_Elaina_Celome (赞：1)

# [CF1905D Cyclic MEX](https://www.luogu.com.cn/problem/CF1905D) 题解

## 题意

>对于一个给定的排列，求将其循环位移任意次后「每个前缀的 mex」的和 的最大值。

## 题解

考虑确定 $p$ 的情况下怎么求答案。

设一个数组 $q[p[i]]=\min(i,q[p[i]-1])$，也就是将 $p$ 的值与下标交换一下然后做前缀 $\min$。

发现对于一个数 $i$，其能产生贡献的次数就是 $n-q[i]$，因为从这里往后才能使 $[1,i]$ 的所有数都出现。

所以对于一个确定的状态答案就是 $n^2 - \sum q_i$。

再考虑如果我们把数组循环位移一位会发生什么。

假设我们把一个数 $x$ 从最开头扔到了最末尾，于是发现所有数的下标会 $-1$，然后 $x$ 的下标 $+n$，转到 $q$ 上就是所有数 $-1$ 然后把 $[x,n+1]$ 全部修改为 $n-1$。

所以枚举循环变化的次数，把 $q$ 数组 $-1$，$q_{[x,n-1]}$ 求改为 $n-1$，然后统计 $q$ 数组的和，取最大。

用线段树维护即可。

```cpp

using namespace std;
#include<bits/stdc++.h>
//#include<cstdio>
//#include<cstring>
//#include<string>
//#include<iostream>
//#include<utility>
//#include<algorithm>
#define MAX(x,y) (x<y?y:x)
#define MIN(x,y) (x<y?x:y)
#define ABS(x) (x<0?-x:x)
#define lb(x) ((x)&(-(x)))
#define N 1000005
#define LL long long
#define LD long double
#define int LL
//#define double LD
#define P 1000000007
#ifdef _WIN32
#define Rand() ((rand()<<16)|rand())
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#elif _WINDOWS_
#define Rand() ((rand()<<16)|rand())
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#else
#define Rand() (rand())
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
constexpr double EPS=(1e-6);
#ifdef int
constexpr int INF=1211081101201201140;
#else
constexpr int INF=1145141919;
#endif
template<typename T>T Max(T x,T y){return MAX(x,y);}
template<typename T>T Min(T x,T y){return MIN(x,y);}
template<typename T>T Abs(T x){return ABS(x);}
template<typename T>void Swap(T&x,T&y){x^=y^=x^=y;}
template<typename T>T Gcd(T x,T y){while(y^=x^=y^=x%=y);return x;}
template<typename T>
T qp(T a,T b){T sum=1;
while(b){if(b&1)sum=(sum*a)%P;a=(a*a)%P;b>>=1;}return sum;}
template<typename T>
void read(T&x){
x=0;char c=getchar();/*T fl=1;*/
while(c<'0'||c>'9'){/*if(c == '-')fl=-1;*/c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}/*x*=fl;*/}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);}
int n;
int a[N];
struct st{
	int sm[N<<2],l1[N<<2],l2[N<<2];
	void add1(const int& u,const int& l,const int& r,const int& x){//区间修改
		l2[u]=0;
		l1[u]=x;
		sm[u]=(r-l+1)*x;
	}
	void add2(const int& u,const int& l,const int& r,const int& x){//区间+
		if(l1[u]>-INF)l1[u]+=x;
		else l2[u]+=x;
		sm[u]+=(r-l+1)*x;
	}
	void psd(const int& u,const int& l,const int& r){
		if(l1[u]>-INF){
			const int mid=(l+r)>>1;
			add1(u<<1,l,mid,l1[u]);
			add1(u<<1|1,mid+1,r,l1[u]);
			l1[u]=-INF;
		}
		if(l2[u]!=0){
			const int mid=(l+r)>>1;
			add2(u<<1,l,mid,l2[u]);
			add2(u<<1|1,mid+1,r,l2[u]);
			l2[u]=0;
		}
	}
	int ask(const int& u,const int& l,const int& r,const int& x,const int& y){
		if(r<x||y<l)return 0;
		if(x<=l&&r<=y)return sm[u];
		psd(u,l,r);
		const int mid=(l+r)>>1;
		return ask(u<<1,l,mid,x,y)+ask(u<<1|1,mid+1,r,x,y);
	}
	void add1(const int& u,const int& l,const int& r,const int& x,const int& y,const int& num){
		if(r<x||y<l)return ;
		if(x<=l&&r<=y){
			add1(u,l,r,num);
			return ;
		}
		psd(u,l,r);
		const int mid=(l+r)>>1;
		add1(u<<1,l,mid,x,y,num);
		add1(u<<1|1,mid+1,r,x,y,num);
		sm[u]=sm[u<<1]+sm[u<<1|1];
	}
	void add2(const int& u,const int& l,const int& r,const int& x,const int& y,const int& num){
		if(r<x||y<l)return ;
		if(x<=l&&r<=y){
			add2(u,l,r,num);
			return ;
		}
		psd(u,l,r);
		const int mid=(l+r)>>1;
		add2(u<<1,l,mid,x,y,num);
		add2(u<<1|1,mid+1,r,x,y,num);
		sm[u]=sm[u<<1]+sm[u<<1|1];
	}
	void build(int u,int l,int r,int* a){
		l1[u]=-INF;
		l2[u]=0;
		if(l==r){
			sm[u]=a[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(u<<1,l,mid,a);
		build(u<<1|1,mid+1,r,a);
		sm[u]=sm[u<<1]+sm[u<<1|1];
	}
}t;
int rev[N];
int rm[N]; 
#undef int
int main(){
#define int LL
	int T;
	read(T);
	while(T--){
		read(n);
		int ans=0;
		for(int i=0;i<n;i++)read(a[i]),rev[a[i]]=i;
		for(int i=0;i<n;i++)rm[i]=Max(rm[i-1],rev[i]);
		t.build(1,0,n-1,rm);
		ans=n*n-t.ask(1,0,n-1,0,n-1);
		for(int i=1;i<n;i++){
			t.add2(1,0,n-1,0,n-1,-1);
			t.add1(1,0,n-1,a[i-1],n-1,n-1);
			ans=Max(ans,n*n-t.ask(1,0,n-1,0,n-1));
		}
		write(ans);
		puts("");
	}
	return 0;
#undef int
}

```

---

## 作者：Rt__ (赞：0)

[CF1905D Cyclic MEX](https://www.luogu.com.cn/problem/CF1905D)
## 题意简述
定义一个长为 $n$ 的 $a$ 数组的**代价**为：
> $$
> \sum_{i = 1}^{n} mex([a_1,a_2,...a_i])
> $$ 
其中 $mex([[a_1,a_2,...a_i]])$ 表示集合 $[a_1,a_2,...a_i]$ 中未涵盖的最小的非负整数。~~（好像在 sg 函数里面见过…）~~

给定一个序列，要求在这个序列**循环位移**的过程中，最大的代价是多少。

循环位移： 

>{$a_1,a_2,...a_{n - 1},a_n$} $->$ 
>{$a_2,a_3,...a_n,a_1$}


## 思路
推一下性质。我们把每一个位置的 mex 函数求出来，可以很容易的发现，它是单调递增的（因为不可能位置 $1$ 到 $j$ 中有 $x$ ， $1$ 到 $j + 1$ 中没有 $x$ 。）。

然后考虑一下循环位移后序列的变化情况：当向前循环位移一位后，第一位的数字会跑到最后去，此时第 $2$ 个数到第 $n$ 个数的前面都没有了 $a_i$ ，那么这对他们的 mex 值有什么影响嘛？可以发现，由于是未出现的最小值，所以当后面的数的 mex 值小于它时，没有变化；但当大于它时，因为它已经移到了序列的最后面，所以不在那些数的前面出现，所以只需要把所有 mex 值大于它的位置改为它，并且把最前面的数移到最后面， mex 值改为 $n$ （因为整个序列 $0$ 到 $n - 1$ 在他前面都出现过了）就可以了。答案很显然是整个区间的 mex 值求和。

区间修改，单点修改，区间求和，很显然我们可以用线段树来实现。这里有两种实现方法（其实写起来差不太多）：

1. 开一个线段树维护长度为 $n$ 的序列，初始值就是每个点的 mex 值，每次循环移位就对整个区间进行修改，每个点维护的值就是循环位移前的位置。移 $i$ 位置时，其余位置的 mex 值大于 $i$ 的改成 $i$ 的 mex 值， $i$ 改为 $n$ 。
2. 根据上面的第一个性质，我们可以用线段树维护一个长度为 $2 * n$ 的区间（破环成链）， $1$ 到 $n$ 赋值为每个位置的初始 mex 值，后面的位置赋值为正无穷（维持区间单调性），每次操作，长度为 $n$ 区间向后平移， $i$ 位置赋值为 $0$ ，是 $i + n$ 赋值为 $n$ ，不断向右平移即可。由于是具有单调性，所以修改查询都相当于在线段树上二分。

## 代码
（由于 $n$ 和 $t$ 都很大，用 cin cout 时一定要关同步流）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;

ll a[N];
int b[N];
struct node{
	int l, r;
	ll sum, minn, maxx, flag;
}tr[4 * N];
void up(int u){
	tr[u]. sum = tr[u << 1]. sum + tr[u << 1 | 1]. sum;
	tr[u]. minn = min(tr[u << 1]. minn, tr[u << 1 | 1]. minn);
	tr[u]. maxx = max(tr[u << 1]. maxx, tr[u << 1 | 1]. maxx);
	return;
}
void build(int u, int l, int r){
	tr[u] = {l, r};
	if(l == r){
		tr[u]. minn = tr[u]. maxx = tr[u]. sum = b[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	up(u);
	return;
}
int n;
void down(int u){
	if(tr[u]. flag){
		tr[u << 1]. minn = tr[u]. flag % (n + 1);
		tr[u << 1]. maxx = tr[u]. flag % (n + 1);
		tr[u << 1]. flag = tr[u]. flag;
		tr[u << 1 | 1]. minn = tr[u]. flag % (n + 1);
		tr[u << 1 | 1]. maxx = tr[u]. flag % (n + 1);
		tr[u << 1 | 1]. flag = tr[u]. flag;
		tr[u << 1]. sum =tr[u]. flag % (n + 1) * (tr[u << 1]. r - tr[u << 1]. l + 1);
		tr[u << 1 | 1]. sum =tr[u]. flag % (n + 1) * (tr[u << 1 | 1]. r - tr[u << 1 | 1]. l + 1);
		tr[u]. flag = 0;
	}
	return;
}
void change(int u, ll x){
	if(tr[u]. minn >= x % (n + 1)){
		tr[u]. sum = (tr[u]. r - tr[u]. l + 1) * (x % (n + 1));
		tr[u]. minn = x % (n + 1);
		tr[u]. maxx = x % (n + 1);
		tr[u]. flag = x;
		return;
	}
	down(u);
	if(tr[u << 1]. maxx >= x % (n + 1)){
		change(u << 1, x);
	}
	if(tr[u << 1 | 1]. maxx >= x % (n + 1)){
		change(u << 1 | 1, x);
	}
	up(u);
	return;
}
void change1(int u, ll ww, int x){
	if(tr[u]. l == x && tr[u].r == x){
		tr[u]. maxx = tr[u].minn = tr[u].sum = ww;
		return;
	}
	down(u);
	int mid = (tr[u]. l + tr[u]. r) >> 1;
	if(x <= mid)change1(u << 1, ww, x);
	else change1(u << 1 | 1, ww, x);
	up(u);
	return;
}
bool st[N];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t --){
		memset(tr, 0, sizeof(tr[0]) * n);
		memset(st, 0, sizeof(st[0]) * n);
		cin >> n;
		int now = 0;
		for(int i = 1; i <= n; i ++){
			cin >> a[i];
			st[a[i]] = 1;
			while(st[now])now ++;
			b[i] = now;
		}
		build(1, 1, n);
		ll ans = 0;
		for(int i = 1; i <= n; i ++){
			ans = max(ans, tr[1]. sum);
//			for(int i = 1; i <= n; i ++)cout << query(1, i, i) << ' ';
//			cout << endl;
			if(a[i] == 0)a[i] = n + 1;
//			cout << a[i] << endl;
			change(1, a[i]);
			change1(1, n, i);
		}
		cout << ans << endl;
	}
	return 0;
}

```

---

## 作者：AKPC (赞：0)

注意到 $p$ 是一个排列，那么可以推导出以下条件：

- 对于区间 $[l,r]$，有 $\text{mex}_{i=l}^{r}p_i=\min\{n,\min_{i=1}^{l-1}p_i,\min_{r+1}^np_i\}$，即区间内 $\text{mex}$ 等于区间外 $\min$（特殊情况：$l=1,r=n$ 的时候 $\text{mex}=n$）。

我们建一个包含 $[0,n]$ 内整数的 $\text{set}$，把区间内每个数从中划掉，显然最后 $\text{set}$ 的最小值就是区间内 $\text{mex}$，这是求序列 $\text{mex}$ 的常见套路。

然而抛开 $l=1,r=n$ 的情况，那么 $\text{set}$ 在初始的时候就不用包含 $n$ 这个值了。我们发现 $p$ 正好可以看做这样的 $\text{set}$，而去掉区间内所有值之后剩下的正好是区间外的所有值，所以求区间外 $\min$ 即可。

然而发现对于一个移位完毕且最优的 $p$，后缀 $\min$ 的和加上 $n$ 即为最终答案。一个 $n^2$ 的做法就是对 $n$ 个不同的排列求后缀 $\min$。

还可以优化，因为后缀 $\min$ 单调递增，而且移位这个操作显然可以用队列很容易地维护，所以考虑单调队列，第 $i$ 次移位，对于每个后缀 $\min$ 大于 $p_i$ 的位置直接把他弹出，然后放入同等数量的 $p_i$，但是这样复杂度还是 $n^2$，发现每个 $p_i$ 相等的最长块数量在不断减少，所以对于每个 $p_i$ 相等的最长块我们把他压缩成一个 $\text{pair}$，保存 $p$ 值和块长，因为初始块最多 $n$ 个，所以时间复杂度 $\Theta(n)$。

[code](/paste/m92bryhz)。

---

## 作者：XYQ_102 (赞：0)

首先对于静态的序列，我们容易求出对于 $i = 1 \sim n$ 有多长时间满足 $\text{mex} \ge i$，显然这个时间一定是一个后缀。可以发现答案就是这些时间加起来。

所以我们只需要维护这个东西就行了。

循环位移过程相当于把当前最前的数移到最后，假设这个数是 $x$，可以发现对于 $i \in [x + 1, n]$，$\text{mex} \ge i$  只有在最后的时刻，即整个数组都出现后才能满足，这个操作等价于把 $[x + 1, n]$ 修改为 $1$。

然后对于 $i \in [1,x]$，可以发现 $\text{mex} \ge i$ 的时间会加 $1$，对应 $[1,x]$ 的区间加操作。

所以你只需要一个支持区间加和区间赋值和区间求和的数据结构,其实就是线段树。
## Code 
```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<numeric>
#include<functional>
using namespace std;
using LL = long long;

struct Info{
    LL sum = 0; int len = 0;
};

struct Tag{
    int add = 0;
	int same = -1;
};

Info operator+(const Info &a, const Info &b){
    return {a.sum + b.sum, a.len + b.len};
}

void apply(Info &x, Tag &a, Tag f){
    if (f.same != -1){
        x.sum = 1LL * x.len * f.same;
        a.same = f.same;
        a.add = 0;
    }
    x.sum += 1LL * x.len * f.add;
    a.add += f.add;
}

template<class Info, class Tag>
struct LazySegmentTree{
    int n;
    vector<Info> info;
    vector<Tag> tag;

    LazySegmentTree() {}

    LazySegmentTree(int n, Info _init = Info()){
        init(vector<Info>(n, _init));
    }

    LazySegmentTree(const vector<Info> &_init){
        init(_init);
    }

    void init(const vector<Info> &_init){
        n = (int)_init.size();
        info.assign((n << 2) + 1, Info());
        tag.assign((n << 2) + 1, Tag());
        function<void(int, int, int)> build = [&](int p, int l, int r){
            if (l == r){
                info[p] = _init[l - 1];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }
    
    void pull(int p){
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    
    void apply(int p, const Tag &v){
        ::apply(info[p], tag[p], v);
    }
    
    void push(int p){
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    
    void modify(int p, int l, int r, int x, const Info &v){
        if (l == r){
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x <= m){
            modify(2 * p, l, m, x, v);
        } 
        else{
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }
    
    void modify(int p, const Info &v){
        modify(1, 1, n, p, v);
    }
    
    Info query(int p, int l, int r, int x, int y){
        if (l > y || r < x){
            return Info();
        }
        if (l >= x && r <= y){
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m + 1, r, x, y);
    }
    
    Info query(int l, int r){
        return query(1, 1, n, l, r);
    }
    
    void modify(int p, int l, int r, int x, int y, const Tag &v){
        if (l > y || r < x){
            return;
        }
        if (l >= x && r <= y){
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        modify(2 * p, l, m, x, y, v);
        modify(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    
    void modify(int l, int r, const Tag &v){
        return modify(1, 1, n, l, r, v);
    }
};

int main(){

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<int> a(n), p(n);
        for(int i = 0; i < n; i++) 
            cin >> a[i], p[a[i]] = i;
        for(int i = 1; i < n; i++){
            p[i] = max(p[i], p[i - 1]);
        }
        vector<Info> init(n);
        for(int i = 0; i < n; i++){
            init[i].sum = n - p[i];
            init[i].len = 1;
        }
        LazySegmentTree<Info, Tag> seg(init);
        LL ans = seg.query(1, n).sum;
        for(int i = 0; i + 1 < n; i++){
            int x = a[i];
            seg.modify(x + 1, n, {0, 1});
            seg.modify(1, x, {1, -1});
            ans = max(ans, seg.query(1, n).sum);
        }
        cout << ans << '\n';
    }
}
```

---

## 作者：Lightwhite (赞：0)

妙妙题。场上为了维护码了个巨大线段树，直接爆炸。

首先，考虑维护 $a$ 的前缀 MEX 序列 $p$ 每次循环移位后的改变。

先求出最开始的序列 $p$。不难发现将 $a$ 循环移位后，会将原来的 $p_1$ 删除，并在 $p$ 序列最后添加一个 $n$。删除第一个数是因为 $a_1$ 被移动到了最后，添加 $n$ 是因为整个序列的 MEX 一定是 $n$。

然后，由于曾经的 $a_1$ 被移动到了最后，那么现在的序列 $p$ 的前 $n-1$ 位均小于等于 $a_1$。

考虑怎么维护这东西。

我考场上想，这就是单点赋值、区间 checkmin、区间查询和的线段树。恶心。又发现序列 $p$ 是单调的。因此 checkmin 可以维护一下最大最小值，线段树二分后做一个区间赋值即可。码一晚上，哈哈。

还是太复杂了。于是你发现可以直接维护连续段，随着一次次的 checkmin，连续端只会合并不会分裂，除了第一个数被放到了后面。然后 deque 维护一下即可。由于每次在序列中 checkmin 枚举了几个连续段，就会合并几个连续段，因此复杂度是 $O(n)$ 的。

```cpp
// STOOOOOOOOOOOOOOOOOOOOOOOOO hzt CCCCCCCCCCCCCCCCCCCCCCCORZ
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <deque>

using namespace std;
using LL = long long;
using PII = pair<int, int>;
constexpr int kN = 1e6 + 1;

int T, n, p[kN];
int t[kN], mex;
LL ans;
deque<PII> Q;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> p[i];
      t[p[i]]++;
      for (; t[mex] > 0; mex++) {
      }
      Q.emplace_back(mex, 1);
      ans += mex;
    }
    for (LL i = 1, c = ans; i < n; i++) {
      c -= Q.front().first;
      Q.front().second--;
      if (Q.front().second == 0) {
        Q.pop_front();
      }
      int r = 0;
      for (; !Q.empty() && Q.back().first >= p[i]; Q.pop_back()) {
        c -= 1ll * Q.back().first * Q.back().second;
        r += Q.back().second;
      }
      c += 1ll * p[i] * r + n;
      Q.emplace_back(p[i], r);
      Q.emplace_back(n, 1);
      ans = max(ans, c);
    }
    cout << ans << '\n';

    mex = 0;
    fill_n(t, n, 0);
    Q.clear(), ans = 0;
  }
  return 0;
}
```

---

