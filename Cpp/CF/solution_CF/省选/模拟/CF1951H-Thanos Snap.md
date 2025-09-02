# Thanos Snap

## 题目描述

[Piotr Rubik - Psalm dla Ciebie](https://youtu.be/3WWwuA6twKI)

ඞ



There is an array $ a $ of size $ 2^k $ for some positive integer $ k $ , which is initially a permutation of values from $ 1 $ to $ 2^k $ . Alice and Bob play the following game on the array $ a $ . First, a value $ t $ between $ 1 $ and $ k $ is shown to both Alice and Bob. Then, for exactly $ t $ turns, the following happens:

- Alice either does nothing, or chooses two distinct elements of the array $ a $ and swaps them.
- Bob chooses either the left half or the right half of the array $ a $ and erases it.

The score of the game is defined as the maximum value in $ a $ after all $ t $ turns have been played. Alice wants to maximize this score, while Bob wants to minimize it.

You need to output $ k $ numbers: the score of the game if both Alice and Bob play optimally for $ t $ from $ 1 $ to $ k $ .

## 说明/提示

In the third test case, for $ t = 2 $ , the game could have proceeded as follows:

- Initially, $ a = [5, 1, 6, 4, 7, 2, 8, 3] $ .
- Alice swaps $ a_6 $ and $ a_8 $ , $ a $ becomes $ [5, 1, 6, 4, 7, 3, 8, 2] $ .
- Bob erases the right half of the array, $ a $ becomes $ [5, 1, 6, 4] $ .
- Alice does nothing, $ a $ remains as $ [5, 1, 6, 4] $ .
- Bob erases the right half of the array, $ a $ becomes $ [5, 1] $ .
- The game ends with a score of $ 5 $ .

## 样例 #1

### 输入

```
5
1
1 2
2
4 3 2 1
3
5 1 6 4 7 2 8 3
4
10 15 6 12 1 3 4 9 13 5 7 16 14 11 2 8
5
32 2 5 23 19 17 31 7 29 3 4 16 13 9 30 24 14 1 8 20 6 15 26 18 10 27 22 12 25 21 28 11```

### 输出

```
1
3 1
7 5 1
15 13 9 1
31 28 25 17 1```

# 题解

## 作者：Caiest_Oier (赞：4)

# [CF1951H](https://www.luogu.com.cn/problem/CF1951H)      

首先上一个二分答案，将所有大于等于 mid 的点设为 1，其它设为 0。建出线段树，首先有前提条件，如果当前在一个深度为 $x$ 的节点（根节点深度为 1），则当前节点区间内至少有 $2^{t-x+1}$ 个 1，否则每次挑少的一侧走下去，必定失败。        

有了这个条件后，一次操作可以看作将某个点变为 1，另外一个点变为 0 实际上可以不用考虑。因为子树内 1 的个数足够，所以一定可以挑得出一个叶子节点有多个 1，将其 1 挪走一个到另外点上，是不影响的。   

于是令 $dp_i$ 表示当前在 $i$ 节点，至少需要提前操作多少次才能保证从当前节点往下走不输。对于叶子节点，如果有 1，则 $dp$ 值为 0，否则为 1。对于非叶子节点，首先要将节点内凑够 $2^{t-x+1}$ 个 1，然后与左右儿子 $dp$ 值之和 $-1$ 取 $\max$。如果 $dp_1=0$ 则合法。复杂度 $O(n\log^2 n)$。     

代码：    

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[2000003];
int val[8000003],dp[8000003],lft,rgt,mid,divd,pre[2000003];
void build(int now,int l,int r,int dep){
    val[now]=pre[r]-pre[l-1];
    if(dep==divd){
        dp[now]=(val[now]==0);
        return;
    }
    build(now*2,l,((l+r)>>1),dep+1);
    build(now*2+1,((l+r)>>1)+1,r,dep+1);
    dp[now]=max(0,dp[now*2]+dp[now*2+1]-1);
    dp[now]=max(dp[now],(1<<(divd-dep))-val[now]);
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>k;
        n=(1<<k);
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=k;i++){
            divd=i;
            lft=1;
            rgt=n;
            while(lft<rgt){
                mid=((lft+rgt)>>1)+1;
                for(int j=1;j<=n;j++)pre[j]=pre[j-1]+(a[j]>=mid);
                build(1,1,n,0);
                if(dp[1]<=0)lft=mid;
                else rgt=mid-1;
            }
            cout<<lft<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/CF1951H)

**题目大意**
> 给定 $1\sim 2^n$ 的一个排列，Alice 和 Bob 轮流操作 $t$ 轮：
> 
> - 在每轮中，Alice 可以选择两个数交换（可以不操作），然后 Bob 把序列的前一半或后一半删掉。
> 
> 最终的权值为剩下的数中的最大值，Alice 想最大化权值，Bob 想最小化权值，对于 $t=1\sim n$，分别求出最终的权值。
> 
> 数据范围：$n\le 20$。

**思路分析**

考虑先二分，转成 01 序列，只要最终权值为 $1$ 即可，然后可以 dp，把每个长度为 $2^{n-t}$ 的段看成叶子建二叉树。

对于每个节点 $u$，设 $u$ 对应的区间为 $[i,i+2^k)$，记 $f_u$ 表示：若博弈过程中第 $s$ 步进入到该区间，最终能得到 $1$，那么至少要在第 $1\sim s-1$ 步中几次操作这个区间。

首先我们要求 $u$ 中 $1$ 的个数 $c$ 不少于 $2^{k-t}$ 个，因此 $f_u\gets 2^{k-t}-c$，若 $u$ 不是叶子节点，还有 $f_u\gets f_{ls}+f_{rs}-1$，其中 $-1$ 表示可以在这一层交换一次。

时间复杂度 $\mathcal O(n^22^n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1<<20],c[1<<20|1],f[1<<21];
bool check(int n,int k,int lim) {
	for(int i=0;i<(1<<n);++i) c[i+1]=c[i]+(a[i]>=lim);
	for(int d=k;~d;--d) {
		int p=(1<<d);
		for(int i=0;i<p;++i) f[p+i]=max(0,(1<<(k-d))-c[(i+1)<<(n-d)]+c[i<<(n-d)]);
		if(d<k) for(int i=p;i<2*p;++i) f[i]=max(f[i],f[i<<1]+f[i<<1|1]-1);
	}
	return !f[1];
}
void solve() {
	int n;
	scanf("%d",&n);
	for(int i=0;i<(1<<n);++i) scanf("%d",&a[i]);
	for(int k=1;k<=n;++k) {
		int x=0;
		for(int d=n-1;~d;--d) if(check(n,k,x|1<<d)) x|=1<<d;
		printf("%d ",x);
	}
	puts("");
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Frodo (赞：1)

## 思路

给出一种 $\Theta(k2^k)$ 的做法。

对每组数据的每个 $t$，使用二分答案 $ans$。

对每一个 $0 \leq i < 2^k$，令 $b_i=[a_i\geq ans]$。

判断 $ans$ 是否可达到，即判断在 $b$ 上进行时是否可得到 $1$。

对每一个 $0 \leq i < 2^t$，令 $cnt_i = \sum_{j=2^{k-t}i}^{2^{k-t}(i+1)-1} b_j$。

二分时可以维护 $cnt$，只会修改 $\Theta(2^k)$ 次。

在 $cnt$ 上建立与线段树类似的满二叉树，然后 dp。

令 $dp_i$ 表示进入 $i$ 所表示的区间（设为 $[l,l+2^p-1]$）时，若可得到 $1$ 至少需要与区间外交换几次。

容易发现 $dp_i \leftarrow \max(0,2^{p-t}-\sum_{j=l}^{l+2^p-1} cnt_j)$。

若 $i$ 有子节点，则 $dp_i \leftarrow \max(dp_i,dp_{lson_i}+dp_{rson_i}-1)$。

## 时间复杂度

对每组数据的每个 $t$，二分时每次判定，因为 dp 状态个数为 $\Theta(2^t)$，转移的复杂度为 $\Theta(1)$，则复杂度为 $\Theta(2^t)$。

每次二分，维护 $cnt$ 复杂度为 $\Theta(2^k)$，判断为 $\Theta(k2^t)$，则复杂度为 $\Theta(2^k+k2^t)$。

所以总复杂度为 $\Theta(\sum_{i=t}^k 2^k+k2^t) = \Theta(k2^k)$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1050000;
int T,k,id[N],cnt[N],a[N],b[N];
bool check(int n){
	for(int i=0;i<n;i++) a[i]=max(1-cnt[i],0ll),b[i]=max(0ll,cnt[i]-1);
	while(n>1){
		for(int i=0;i<(n>>1);i++){
			a[i]=a[i<<1]+a[i<<1|1],b[i]=b[i<<1]+b[i<<1|1];
			if(a[i]&&b[i]) a[i]--,b[i]--;
		}
		n>>=1;
	}
	return !a[0];
}
void solve(){
	cin>>k;
	for(int i=0,w;i<(1<<k);i++) cin>>w,id[w-1]=i;
	for(int i=1;i<=k;i++){
		for(int j=0;j<(1<<i);j++) cnt[j]=0;
		int l=0,r=(1<<k)-1,mid;
		while(l<r){
			mid=(l+r+1)>>1;
			for(int j=mid;j<=r;j++) cnt[id[j]>>(k-i)]++;
			if(check(1<<i)){
				l=mid;
				for(int j=mid;j<=r;j++) cnt[id[j]>>(k-i)]--;
			}
			else r=mid-1;
		}
		cout<<r+1<<' ';
	}
	cout<<'\n';
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：daduoli (赞：0)

前言：这个题感觉可能因为放的位置比较靠后，导致这个题的评分虚高。

首先我们看到这个东西很容易想到二分把他转成 $01$ 序列，其实就是二分一个 $x$，令 $\ge x$ 的数为 $1$，$<x$ 的数为 $0$。

如果我们合法，当且仅当无论玩家二怎么走，都可以保证最后的块中含有至少一个 $1$。

设最后块的大小为 $len$，那么显然有 $2^n-x+1\ge \frac n{len}$，因为显然要满足每个块至少有一个 $1$，上面这是必要条件。

对于一个块而言，如果他有多于一个 $1$，那么多出的部分都可以给其他块，这个是没有问题的，而我们每次操作实际上是从有多的 $1$ 的块中拿一个给没有 $1$ 的块，这个也是显然的。

对于下面我们令 $n=2^n$。

我们有若干层，$([1,n]),([1,\frac n2],[\frac n2+1,n])\dots([1,len],[len+1,2len]\dots,[n-len+1,n])$。

对于第一层 $[1,n]$ 的操作可以对于全局操作，而对于倒数第二层的操作，只能对于一个 $[klen+1,klen+2len]$ 这样的区间进行操作。

也就是说层数越深，操作的限制越紧，套路地，我们优先考虑限制紧的操作。

从深层往浅层考虑，提前预处理出每个块是否需要支援一个 $1$，以及有多少个多出的 $1$。

对于当前层如果存在多出的 $1$，且存在需要支援的块，那么直接支援一个过去即可。

这样不断往上合并两个小的块，最后得到我们最大的块 $[1,n]$，如果此时仍然存在块需要支援那么显然非法，否则合法。

时间复杂度 $O(n\log^2 n)$。

我还有一个奇妙的心路历程，就是我一开始想的是如何如何分配可以获得的 $1$，使得左右儿子都合法，于是我就想着求左右儿子至少需要多少个 $1$ 才能合法。

然后我们要处理出 $f_{i,j}$ 表示区间 $[i,j]$ 需要在浅层支援至少多少个 $1$ 才能合法，而这样的话我们需要优先遍历子树，然后将左右儿子合并起来，这样的话我们就可以知道还差多少个块要支援，然后就会发现这个过程实际上是倒着做的，然后就可以了。

如果有写错的，可以私信我。

```
#include<bits/stdc++.h>
#define Yzl unsigned int
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
typedef long long LL;

using namespace std;

const Yzl Lty=20120712;

const int MAXN=1.1e6;
int n,m;
int a[MAXN],sum[MAXN],t[MAXN],nd[MAXN];
pi solve(int l,int r) {
	if(l==r) return mp(t[l],nd[l]);
	int mid=(l+r)/2;
	pi l1=solve(l,mid);
	pi l2=solve(mid+1,r);
	l1.fi+=l2.fi;
	l1.se+=l2.se;
	if(l1.fi&&l1.se) --l1.fi,--l1.se;
	return l1;
}
bool chk(int lim,int len) {
	for(int i=1;i<=m;++i) sum[i]=sum[i-1]+(a[i]>=lim);
	int total=0;
	for(int i=1;i<=m;i+=len) {
		int l=i,r=i+len-1;
		++total; int ls=sum[r]-sum[l-1];
		t[total]=nd[total]=0;
		if(ls>0) t[total]=ls-1;
		else nd[total]=1;
	}
	pi ans=solve(1,total);
	return (!ans.se);
}
int erfind(int x) {
	int l=0,r=m-(n/x)+2,mid;
	while(l+1<r) {
		mid=(l+r)/2;
		if(chk(mid,x)) l=mid;
		else r=mid;
	}
	return l;
}
void vmain() {
	scanf("%d",&n); m=(1<<n);
	for(int i=1;i<=m;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) {
		int lim=(1<<(n-i));
		printf("%d ",erfind(lim));
	} puts("");
}
int main () {
	int T;
	scanf("%d",&T);
	while(T--) vmain();
	return 0;
}
```

---

