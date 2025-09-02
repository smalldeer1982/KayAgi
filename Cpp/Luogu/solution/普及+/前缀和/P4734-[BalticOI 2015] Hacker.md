# [BalticOI 2015] Hacker

## 题目描述

### 题面描述

Byteasar 获得了今年国际黑客奥林匹克竞赛的参赛资格。竞赛的任务之一是与系统操作员竞争。有从 $1$ 到 $n$ 编号的 $n$ 台计算机，以环形连接，即计算机 $i$ 和 $i+1$ 连接（其中 $i = 1,2,\dots,n-1$），特别地，计算机 $n$ 和 $1$ 也连接。

这个任务是黑客和系统操作员之间的游戏：

- Byteasar 先走。之后，操作员和 Byteasar 交替移动。
- Byteasar 的第一步是选择任何一台计算机并对其进行黑客攻击。
- 在他的第一步中，操作员选择任何未被黑客攻击的计算机并对其进行保护。
- 在接下来的所有动作中，Byteasar 要么什么都不做，要么选择任何既没有被黑客攻击也没有受到保护的计算机，并直接链接到任何被黑客攻击的计算机，然后对其进行黑客攻击。
- 在接下来的所有动作中，操作员要么什么都不做，要么选择任何既没有被黑客攻击也没有受到保护的计算机，直接链接到任何受保护的计算机并对其进行保护。
- 一旦两人在接下来的两个动作中都没有做任何事情，游戏就结束了。

在游戏开始时，没有任何一台电脑被黑客攻击或受到保护。

每台计算机 $i$ 都有一个特定的值 $v_i$，该值指定了存储在其上的数据的价值。Byteasar 最终获得的分数就是所有被他攻击的计算机的 $v$ 值之和。

虽然 Byteasar 是一个很好的黑客，但对算法一无所知——这就是为什么他要求你编写一个程序来计算他的最大可能分数，假设操作员按最优策略。

## 样例 #1

### 输入

```
4
7 6 8 4```

### 输出

```
13```

## 样例 #2

### 输入

```
5
1 1 1 1 1```

### 输出

```
3```

# 题解

## 作者：WarningQAQ (赞：6)

## 分析：
我们发现假如第一步选择位置 $i$ ，那么系统操作者能把 $\text{Byteasar}$ 限制成经过 $i$ 的长度为 $\lceil \dfrac{n}{2} \rceil$ 。

的任意一个序列。那么系统操作者肯定会选择价值最小的那个。

现在问题就是求出经过每个位置的长度为 $\lceil \dfrac{n}{2} \rceil$ 。

的序列的价值的最小值，然后每个位置最小值的最大值就是答案。

现在考虑怎么求出这个最大值。

我们发现这样的序列一共只有 $n$ 个，我们可以对这 $n$ 个序列的价值从大到小排个序。

然后对每个序列的范围做一下区间覆盖。显然当一个位置被覆盖了 $\lceil \dfrac{n}{2} \rceil$  次的时候，当前的序列的价值就是答案。

区间覆盖线段树就可以了。

[$\text{code1}$](https://www.luogu.com.cn/paste/hpuvfsnu)

BUT~~T~~！

线段树虽然能过，但是好慢啊。

我们发现，用线段树进行操作好像有点多余，其实完全可以只通过前缀和 $+$ 二分的方式来维护序列。

~~再加一点点优化。。。~~

我们的简短的代码就完成力！~~线段树就是弱欸。~~

[$\text{code2}$](https://www.luogu.com.cn/paste/x1b8tz3t)


完力，[推销博客](https://www.cnblogs.com/nakiri-ayame-suki/)。

---

## 作者：tanghg (赞：4)

对于这种题目一般可以先断环成链。

发现先手所得到的值是一个长度为 $\lceil \frac{n}{2}\rceil$ 的区间，我们希望让它的元素之和能取到最大，但发现后手会让我们取不到最大。

假设我们从第 $i$ 台电脑开始，那么后手一定会让我们取到一个所有经过这个点的区间之和的最小值。所以我们只要让这个最小值最大即可。

对于做法先做一个前缀和，之后用 ST 表记录从这个点开始的长度为 $\lceil \frac{n}{2}\rceil$ 的区间元素之和，然后枚举每一个电脑 $i$，能够经过它的区间起始位置在 $[i-\lceil \frac{n}{2}\rceil+1,i]$ 之间。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN=1e6+5;
ll n,a[MAXN],f[MAXN];
ll st[MAXN][20],lg[MAXN];
ll query(ll l,ll r){
	ll len=lg[r-l+1];
	return min(st[l][len],st[r-(1<<len)+1][len]);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		a[n+i]=a[i];
	}
	for(int i=1;i<=2*n;++i){
		f[i]=f[i-1]+a[i];
	}
	ll sa=ceil(n*1.0/2);
	for(int i=2;i<MAXN;++i){
		lg[i]=lg[i>>1]+1;
	}
	for(int i=1;i<=2*n;++i){
		st[i][0]=f[i+sa-1]-f[i-1];
	}
	for(int l=1;l<=lg[2*n];++l){
		for(int i=1;i+(1<<l)-1<=2*n;++i){
			st[i][l]=min(st[i][l-1],st[i+(1<<(l-1))][l-1]);
		}
	}
	ll ans=0;
	for(int i=sa;i<=2*n;++i){
		ans=max(ans,query(i-sa+1,i));
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：MagicalGirl_0d00 (赞：1)

### 怎么花了整整个半小时啊
会发现一个非常有趣的事实：

如果 Hacker 第一步选了一个 $i$，那么保护者肯定可以让它选择包含 $i$ 的一个权值最小且长度为 $\frac{n}{2}$ 向上取整的区间。

手玩一下可以发现这个规律。

证明的话，你可以在你在想控制 hacker 选的区间的端点旁边，如果 hacker 想要逃离这个区间就把它拦住就行了。

包含 $i$ 的最小区间可以直接使用单调队列来做，具体实现方法就是一个点 $i$ 表示一个 $[i,i+\lceil \frac{n}{2} \rceil -1]$ 的区间，然后维护它就行了。

$O(n)$ 好奇为何会有二分标签。
### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000001],ans,sum[1000001];
deque<int> q;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i];
	}
	for(int i=1;i<=2*n;i++){
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=(n+1)/2-1;i++){
		while(q.size()&&q.front()+(n+1)/2-1<i) q.pop_front();
		while(q.size()&&sum[q.back()+(n+1)/2-1]-sum[q.back()-1]>sum[i+(n+1)/2-1]-sum[i-1]) q.pop_back();
		q.push_back(i);
	}
	for(int i=(n+1)/2;i+(n+1)/2-1<=2*n;i++){
		while(q.size()&&q.front()+(n+1)/2-1<i) q.pop_front();
		while(q.size()&&sum[q.back()+(n+1)/2-1]-sum[q.back()-1]>sum[i+(n+1)/2-1]-sum[i-1]) q.pop_back();
		q.push_back(i);
		ans=max(ans,sum[q.front()+(n+1)/2-1]-sum[q.front()-1]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lzhm (赞：1)

# P4734 解题记录

## 分析

首先可以知道 Byteasar 选的长度为 $\lceil \frac{n}{2} \rceil$。

假设当前 Byteasar 的最佳决策点为 $i$，因为只能选连续的，所以选出来的答案一定为一段包含 $i$ 位置的区间。

继续发掘一下。

发现对于另一方，他一定有一种决策使得 Byteasar 只能选择和最小的一段区间（建议手摸一下）。

此时问题转化为枚举每一个 $i \in [1,n]$，需要找到包含位置 $i$ 的长度为 $\lceil \frac{n}{2} \rceil$ 的一段连续区间的最小值，最后对所有最小值取 $\max$ 即为所求。

## 实现

线段树。

记 $len$ 表示 $\lceil \frac{n}{2} \rceil$。

记 $val_l$ 表示以 $l$ 为左端点的长度为 $len$ 的区间和。

答案为 $i \in [1,n]$，$\max\{ \min(val_j) \}$，$j \in [i-len+1,i]$。

具体实现注意破环成链以及边界情况。

下面是代码。

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int MAXN=1e6+10;
int n;
int a[MAXN],sum[MAXN];
#define lson p<<1
#define rson p<<1|1
int minn[MAXN<<2];
void update(int p,int l,int r,int pos,int val){
	if(l==r) return minn[p]=val,void();
	int mid=(l+r)>>1;
	if(pos<=mid) update(lson,l,mid,pos,val);
	else update(rson,mid+1,r,pos,val);
	minn[p]=min(minn[lson],minn[rson]);
}
int query(int p,int l,int r,int L,int R){
	if(L<=l && r<=R) return minn[p];
	int mid=(l+r)>>1,ans=inf;
	if(L<=mid) ans=min(ans,query(lson,l,mid,L,R));
	if(R>mid) ans=min(ans,query(rson,mid+1,r,L,R));
	return ans;
}
signed main(){
//	freopen("hac3d.in","r",stdin);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	memset(minn,0x3f,sizeof minn);
	for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
	for(int i=1;i<=n*2;i++) sum[i]=sum[i-1]+a[i];
	int len=(n+1)/2;
	for(int i=1;i<=n*2;i++) if(i+len-1<=2*n) update(1,1,n*2,i,sum[i+len-1]-sum[i-1]);
	int ans=0;
	for(int i=1;i<=n*2;i++) if(i-len+1>=1 && i+len-1<=2*n) ans=max(ans,query(1,1,n*2,i-len+1,i));
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：船酱魔王 (赞：1)

## Changelog

修改了变量名可能导致难以理解代码意图的部分（码风），抱歉浪费管理员时间重新审核。

## 题意回顾

在一个长度为 $ n $ 的环上，黑白方轮流操作：

* 对于首轮操作，在环上任选一个结点作为初始操作点，这个结点不能已经被操作；

* 操作方选择一个与被己方操作结点相邻且未被任何一方操作的结点操作，或选择跳过；

* 如果双方均选择跳过，那么游戏结束。

黑方先行，黑方想要最大化黑方操作结点的点权和，白方想要最小化，求出双方均按照最优操作时的这个值。

$ 2 \le n \le 5 \times 10^5 $，点权均为正整数且不超过 $ 2 \times 10^3 $。

## 分析

不难发现双方操作的格子数量一定，且都为一个连续段。

考虑黑方如果选择了一个操作点，那么白方可以通过堵住一个连续段的端点往外一个点并且不断在环上在这个连续段外向另一个端点延伸，使得黑方的控制范围必须为这个连续段，因此我们只需要找到每个位置包含这个位置的长度符合要求的连续段的和最小的一个，求出所有位置这个值的最大值即可。

区间更新较小值操作难做，但这是离线问题。我们把所有长度符合要求的连续段按照和从大到小排序，每次用连续段的和进行区间覆盖即可。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5e5 + 5;
int n;
int a[N];
int sum[N];
int d[N * 4];
int rq[N], st[N];
void update(int l, int r, int v, int s, int t, int p) {
    if(l <= s && t <= r) {d[p] = v; return;}
    int mid = (s + t) >> 1;
    if(d[p]) d[p * 2] = d[p * 2 + 1] = d[p], d[p] = 0;
    if(l <= mid) update(l, r, v, s, mid, p * 2);
    if(mid < r) update(l, r, v, mid + 1, t, p * 2 + 1);
}
bool cmp(int x, int y) {
    return rq[x] > rq[y];
}
int ans = 0;
void findans(int s, int t, int p) {
    if(s == t) {ans = max(ans, d[p]); return;}
    int mid = (s + t) >> 1;
    if(d[p]) d[p * 2] = d[p * 2 + 1] = d[p], d[p] = 0;
    findans(s, mid, p * 2);
    findans(mid + 1, t, p * 2 + 1);
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
    int o = (n + 1) / 2;
    for(int i = 1; i <= n; i++) {
        int j = i + o - 1;
        rq[i] = (j <= n) ? (sum[j] - sum[i - 1]) : (sum[n] - sum[i - 1] + sum[j - n]), st[i] = i;
    }
    sort(st + 1, st + n + 1, cmp);
    for(int ii = 1; ii <= n; ii++) {
        int i = st[ii];
        int j = i + o - 1;
        if(j <= n) update(i, j, rq[i], 1, n, 1);
        else {
            j -= n;
            update(i, n, rq[i], 1, n, 1);
            update(1, j, rq[i], 1, n, 1);
        }
    }
    findans(1, n, 1);
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：_EternalRegrets_ (赞：1)

## P4734 题解

### 题意描述：
有 $n$ 个点，每个点都有数值，连接成环。

有两个人，玩家 $A$ 先选择一个点，让自己的分数增加点上的数值。之后，玩家 $B$ 选择一个点，使得玩家 $A$ 不能选择这个点（不可以选择 $A$ 已经选过的点）。

除了每人的第一个选择，每人只可以选择和自己已经选择过的点所相邻的点。求出玩家 $A$ 可以得到的最高分数。

### Solution:
可以讨论玩家 $A$ 选的的第一个点。对于玩家 $B$，一定可以让 $A$ 只可以选择到当前的最小值。（后附证明）

$A$ 可以选择 $\lceil \frac{n}{2} \rceil$ 个点。所以，我们就可以预处理出长度为 $\lceil \frac{n}{2} \rceil$ 的序列。用单调队列算出对于每一种第一个点的选择方法，包含这个点的最小序列长度。

### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[1500005];
int in[1500005];
int ans=-1;

deque <int> q;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin>>n;

    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i+n]=a[i];
    }

    int x; x=(n+1)/2;
    for(int i=1;i<=x;i++){
        in[1]+=a[i];
    }
    in[0]=a[n];

    //cout<<in[1]<<" ";
    for(int i=x+1;i<=n+n+x-1;i++){
        in[i-x+1]=in[i-x]+a[i]-a[i-x];
        //cout<<in[i-x+1]<<" ";
    }
    
    for(int i=1;i<=x;i++){
        while(!q.empty() && in[q.back()]>=in[i]){
            q.pop_back();
        }
        q.push_back(i);
    }

    for(int i=1;i<=n+x;i++){
    	while(!q.empty() && in[q.back()]>=in[i]){
            q.pop_back();
        }
    	
        while(!q.empty() && i-q.front()>=x){
            q.pop_front();
        }

        q.push_back(i);
        ans=max(ans,in[q.front()]);
    }

    cout<<ans;
    return 0;
}
```

### 证明：$B$ 一定可以限制 $A$ 的选择范围
$A$ 选择第一个之后，$B$ 可以选择所对应的最小值的对应区间边界向外一格（左右均可）。之后，从一端向另一端去连续选。如果 $A$ 可以选择到留下的点（区间边上那个），$B$ 直接选择留下的点。之后就是填满环的过程了。

---

## 作者：wjr_jok (赞：0)

不难发现 Byteasar 可以控制一串相连的长度为 $\lceil \frac{n}{2} \rceil$ 的电脑，所以考虑枚举 Byteasar 最初选择的点，然后用前缀和求得答案。

需要注意的是系统操作者是会选择最优策略的，即让 Byteasar 的分数尽量少，然后手玩一下可以发现系统操作者可以通过改变最初选择的点来控制 Byteasar 选择的电脑串位置（如下图）。

![](https://cdn.fzoi.top/upload/user/st20251822/24112608164137.png)

黑色的点代表 Byteasar，每种颜色的线段为系统操作者最初选择相同颜色的点后两者电脑串的分界线，可以发现能将所有可能的电脑串分出来。

所以用线段树维护区间（包含某个点的所有电脑串）最小值，然后枚举 Byteasar 最初选择的点取最大值即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+1;
int n,fj,l,r,ans;
int xl[N],qzh[N],ok[N],tree[N<<2],minn[N<<2];
void build(int k,int l,int r){
	if(l==r){
		tree[k]=minn[k]=ok[l];
		return;
	}
	int mid=(l+r)/2;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	minn[k]=min(minn[k*2],minn[k*2+1]);
}
int ask(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		return minn[k];
	}
	int mid=(l+r)/2,cnt=INT_MAX;
	if(x<=mid){
		cnt=min(cnt,ask(k*2,l,mid,x,y));
	}
	if(y>mid){
		cnt=min(cnt,ask(k*2+1,mid+1,r,x,y));
	}
	return cnt;
}//建树+区间查
signed main(){
	cin>>n,fj=n/2+(n%2);
	for(int i=1;i<=n;i++){
		cin>>xl[i],qzh[i]=qzh[i-1]+xl[i];
	}
	for(int i=1;i<=n-fj+1;i++){
		ok[i]=qzh[i+fj-1]-qzh[i-1];
	}
	for(int i=n-fj+2;i<=n;i++){
		ok[i]=qzh[n]-qzh[i-1]+qzh[fj-n+i-1];
	}//处理电脑串前缀和，这里没有破环成链所以分开写了
	build(1,1,n);
	for(int i=1;i<fj;i++){
		l=i,r=n-fj+i+1;
		ans=max(ans,min(ask(1,1,n,1,l),ask(1,1,n,r,n)));
	}
	for(int i=fj;i<=n;i++){
		l=i-fj+1,r=i;
		ans=max(ans,ask(1,1,n,l,r));
	}//枚举最初选择的点取分数最大值
	cout<<ans;
	return 0;
}
```

---

