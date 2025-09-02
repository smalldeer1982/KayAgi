# [JOIG 2025] 神経衰弱 2 / Pair Matching 2

## 题目描述

有 $2N$ 张卡牌从左到右依次放在桌子上，编号为 $1,2,\ldots,2N$，卡牌 $i$ 上写有整数 $A_i$。对于 $x=1,2,\ldots,N$，存在恰好两张卡牌上写的整数为 $x$。

海狸比太郎决定用这些卡牌玩一个叫做“神经衰弱”的游戏；该游戏的流程如下：

- 依次考虑卡牌 $i=1,2,\ldots,2N$：
  1. 比太郎决定是否拿起这张卡牌：如果他决定拿起，那么依次进行以下的步骤 2 至步骤 5；如果他决定不拿起（跳过该卡牌），则跳过以下的步骤；
  2. 如果比太郎的手中持有一张写有 $A_i$ 的卡牌，那么该卡牌和卡牌 $i$ 同时消失，他获得 $V_{A_i}$ 分；
  3. 如果比太郎左手中有一张卡牌，那么他将其丢弃；
  4. 如果比太郎右手中有一张卡牌，那么他将其转移到左手；
  5. 如果卡牌 $i$ 没有在步骤 2 中消失，那么他将其放在右手中。
  
通过上面的流程，每次得到的分数之和即为比太郎的最终得分。

请求出比太郎能获得的最大得分。

## 说明/提示

#### 【样例解释 #1】

比太郎可以通过以下流程获得分数 $13$：

1. 拿起卡牌 $1$，该卡牌上面写着 $1$；由于比太郎没有其他写着 $1$ 的纸牌，所以他将其放在右手中；
2. 跳过卡牌 $2$；
3. 拿起卡牌 $3$，该卡牌上面写着 $3$；由于比太郎没有其他写着 $3$ 的纸牌，所以卡牌 $1$ 从右手转移到了左手，他将卡牌 $3$ 放在右手中；
4. 拿起卡牌 $4$，该卡牌上面写着 $1$；由于卡牌 $1$ 上也写着 $1$，所以两张牌都消失了，他获得 $V_1=5$ 分，卡牌 $3$ 则从右手转移到了左手；
5. 跳过卡牌 $5$；
6. 拿起卡牌 $6$，该卡牌上面写着 $3$；由于卡牌 $3$ 上也写着 $3$，所以两张牌都消失了，他获得 $V_3=8$ 分，此时他两只手上都没有任何卡牌了。

可以证明这是最优的。

该样例满足子任务 $1,2,3,4,5,6,8,9$ 的限制。

#### 【样例解释 #2】

比太郎可以通过拿起卡牌 $1,2,3,4,5,6,8$ 来获得分数 $V_1+V_2+V_3=156$。可以证明这是最优的。

该样例满足子任务 $3,4,5,6,8,9$ 的限制。

#### 【样例解释 #3】

该样例满足子任务 $4,5,6,8,9$ 的限制。

#### 【样例解释 #4】

该样例满足子任务 $4,5,6,7,8,9$ 的限制。

#### 【数据范围】

- $1\le N\le 4\times 10^5$；
- $A_1,A_2,\ldots,A_{2N}$ 中，对于 $x=1,2,\ldots,N$，$x$ 正好出现两次；
- $1\le V_k\le 10^9$。

#### 【子任务】

1. （$8$ 分）$(A_1,A_2,\ldots,A_N)=(1,2,\ldots,N)$，$N\le 5000$；
2. （$12$ 分）$(A_1,A_2,\ldots,A_N)=(1,2,\ldots,N)$；
3. （$6$ 分）$N\le 9$；
4. （$9$ 分）$N\le 18$；
5. （$16$ 分）$N\le 300$
6. （$18$ 分）$N\le 3000$；
7. （$18$ 分）$N\le 1.5\times 10^5$，$V_k\le 1(1\le k\le N)$；
8. （$8$ 分）$N\le 1.5\times 10^5$；
9. （$5$ 分）无附加限制。

## 样例 #1

### 输入

```
3
1 2 3 1 2 3
5 2 8```

### 输出

```
13```

## 样例 #2

### 输入

```
4
1 2 1 2 3 4 4 3
39 62 55 21```

### 输出

```
156```

## 样例 #3

### 输入

```
10
7 2 5 8 4 10 8 2 7 5 6 3 4 1 10 9 9 1 6 3
185163245 734376902 849123714 97860221 844860642 689054872 471545587 607735137 664633003 831663829```

### 输出

```
3117416130```

## 样例 #4

### 输入

```
15
4 3 8 3 10 15 14 1 12 4 13 1 6 7 10 15 2 8 12 2 9 11 11 13 5 9 14 5 6 7
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
6```

# 题解

## 作者：ZHR100102 (赞：7)

质量还行的线段树优化 DP。

手膜样例不难发现，**一张牌在和另一张牌匹配后，中间不能再有匹配的牌了**，因为这样会把前一个匹配的牌挤出左手。同时因为只有两只手，所以**不能同时匹配三张及以上的牌**。

因此对于任意两对匹配的牌，只可能有两种关系：
- 相交关系。且一对匹配的牌**最多只能和另一对匹配的牌相交**。
- 不交关系。

于是设计 DP：$dp_i$ 表示考虑前 $i$ 位的最大答案。为了方便统计答案，我们强制匹配牌的贡献在右端点计算；与另一对牌相交的，以靠右的一对牌为准。那么有三类转移：
- 继承状态：$dp_i=\max(dp_i,dp_{i-1})$。
- 与其他对匹配的牌不交的转移：$dp_i=\max(dp_i,dp_{pre_{a_i}}+V_{a_{i}})$。
- 与某一对牌相交的转移：$dp_i =\max(dp_i,dp_{pre_{a_k}}+V_{a_k}+V_{a_i})$。其中 $a_k$ 是某一对经过了 $pre_{a_i}$ 的牌，即 $pre_{a_k}<pre_{a_i}<k <i$。

其中，$pre_x$ 表示第一个 $x$ 的位置。

前两种转移是容易的，考虑如何优化第三种转移。发现把有关 $k$ 的变量提出来，是不含其它变量的，而对于有关 $k$ 的两个不等限制，可以用一个类似二维数点的东西解决。但是我不会二维数点！

正着不好做，于是考虑**反向计算，让每个 $k$ 给会贡献到的 $pre_{a_i}$ 做贡献**。发现只要 $pre_{a_k} <pre_{a_i}<k$ 的时候贡献就能被计算，因此维护一个求区间 $\max$，单点查的**线段树**，算贡献的时候把 $[pre_{a_k},k]$ 区间贡献一个 $dp_{pre_{a_k}}+V_k$ 即可。

时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define lc (p<<1)
#define rc ((p<<1)|1)
using namespace std;
typedef long long ll;
const int N=1000005;
const ll inf=0x3f3f3f3f3f3f3f3f;
ll n,a[N],b[N],dp[N],pre[N];
struct Node{
	int l,r;
	ll v,tag;
};
struct Segtree{
	Node tr[4*N];
	void pushup(int p)
	{
		tr[p].v=max(tr[lc].v,tr[rc].v);
	}
	void pushdown(int p)
	{
		if(tr[p].tag!=-inf)
		{
			tr[lc].tag=max(tr[lc].tag,tr[p].tag);
			tr[lc].v=max(tr[lc].v,tr[p].tag);
			tr[rc].tag=max(tr[rc].tag,tr[p].tag);
			tr[rc].v=max(tr[rc].v,tr[p].tag);			
		}
		tr[p].tag=-inf;
	}
	void build(int p,int ln,int rn)
	{
		tr[p]={ln,rn,-inf,-inf};
		if(ln==rn)return;
		int mid=(ln+rn)>>1;
		build(lc,ln,mid);
		build(rc,mid+1,rn);
		pushup(p);
	}
	void update(int p,int ln,int rn,ll x)
	{
		if(ln<=tr[p].l&&tr[p].r<=rn)
		{
			tr[p].v=max(tr[p].v,x);
			tr[p].tag=max(tr[p].tag,x);
			return;
		}
		pushdown(p);
		int mid=(tr[p].l+tr[p].r)>>1;
		if(ln<=mid)update(lc,ln,rn,x);
		if(rn>=mid+1)update(rc,ln,rn,x);
		pushup(p);
	}
	ll query(int p,int x)
	{
		if(tr[p].l==x&&tr[p].r==x)return tr[p].v;
		pushdown(p);
		int mid=(tr[p].l+tr[p].r)>>1;
		if(x<=mid)return query(lc,x);
		else return query(rc,x);
	}
}tr1;
int main()
{
//	freopen("smash.in","r",stdin);
//	freopen("smash.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=2*n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	memset(dp,-0x3f,sizeof(dp));
	dp[0]=0;
	tr1.build(1,1,2*n);
	for(int i=1;i<=2*n;i++)
	{
		dp[i]=max(dp[i],dp[i-1]);
		if(pre[a[i]])
		{
			dp[i]=max(dp[i],tr1.query(1,int(pre[a[i]]))+b[a[i]]);
			dp[i]=max(dp[i],dp[pre[a[i]]]+b[a[i]]);
			tr1.update(1,pre[a[i]],i,dp[pre[a[i]]]+b[a[i]]);
		}
		pre[a[i]]=i;
	}
	cout<<dp[2*n];
	return 0;
}
```

---

## 作者：GUO120822 (赞：5)

树状数组优化 DP。

容易发现，两个相同的东西间隔不会超过一。

$dp_i$ 表示最后一个选了 $i$ 位置的最大价值。

不选，$dp_i=dp_{i-1}$。

选，有两种。

第一种，$dp_i=dp_{pre_i}+v_{a_i}$。

第二种，$dp_i=dp_{pre_j}+v_{a_i}+v_{a_j}$，条件是 $pre_j<pre_i<j<i$。

然后树状数组优化，复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct FSI{
	template<typename T>
	FSI& operator >> (T &res){
		res=0;T f=1;char ch=getchar();
		while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
		while (isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
		res*=f;
		return *this;
	}
}scan;
typedef long long ll;
const int N=4e5+10;
int n,a[N<<1],v[N],i,j,pre[N<<1],last[N];
ll dp[N<<1],c[N<<1];
int lowbit(int x){return x&(-x);}
void motify(int x,ll v)
{
	int i;
	for (i=x;i<=2*n;i+=lowbit(i)) c[i]=max(c[i],v);
}
ll query(int x)
{
	ll res=0,i;
	for (i=x;i>0;i-=lowbit(i)) res=max(res,c[i]);
	return res;
}
int main()
{
	scan>>n;
	for (i=1;i<=2*n;i++) scan>>a[i];
	for (i=1;i<=n;i++) scan>>v[i];
	for (i=1;i<=2*n;i++)
	{
		pre[i]=last[a[i]];
		last[a[i]]=i;
	}
	for (i=1;i<=2*n;i++)
	{
		dp[i]=dp[i-1];
		if (pre[i]) 
		{
			dp[i]=max(dp[i],dp[pre[i]]+v[a[i]]);
			dp[i]=max(dp[i],query(pre[i]-1)+v[a[i]]);
			motify(pre[i],dp[pre[i]]+v[a[i]]);
		}
	}
	printf("%lld",dp[2*n]);
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：5)

我们加入 $A_i$ 一定是为了得到 $A_i$ 对应的贡献。因为加入 $A_i$ 不会让手的空间更宽阔，甚至可能会导致一些卡牌消失，得不偿失。

所以我们一定是成对选择，且每对都必须匹配上。

考虑颜色 $x$ 在什么情况下会匹配上。

如果两个 $x$ 中间有超过 $2$ 个其它的卡牌，则 $x$ 就会消失。

所以两个 $x$ 之间最多有 $1$ 个卡牌。

这样最终的选择序列由形如 $xx$ 或 $xyxy$ 的部分拼接，对其 dp。

设 $pre_i$ 是 $A_i$ 上一次出现的位置。$dp_i$ 表示最后一个选的 $A_i$，且与上一个 $A_i$ 之间没有其它卡牌的答案；$g_i$ 表示最后一个选的 $A_i$，且与上一个 $A_i$ 之间有其他卡牌的答案。注意，这些都只在 $i$ 是 $A_i$ 第二次出现时设计。

转移很简单，$dp_i$ 从 $pre_i$ 之前的位置取最大值再加上 $V_{A_i}$ 即可，$g_i$ 从 $pre_j<pre_i$ 的 $dp_j$ 转移过来就可以，后者树状数组处理，总复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n-1
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=8e5+5,M=1e6+5,inf=(1LL<<29)-1,mod=1e9+7;
const ll llf=1e18;
int n,a[N],v[N],pre[N],dp[N][2],p[N],Mx[N];
int t[N];
inline void ad(int x,int k){
	while(x<=n*2)t[x]=max(t[x],k),x+=x&-x;
}
inline int query(int x){
	int ans=0;
	while(x)ans=max(ans,t[x]),x-=x&-x;
	return ans;
}
inline void Main(){
	n=read();
	rep(i,1,n<<1)a[i]=read();
	rep(i,1,n<<1){
		if(p[a[i]])pre[i]=p[a[i]];
		else p[a[i]]=i;
	}
	repn(i)v[i]=read();
	rep(i,1,n<<1){
		if(!pre[i])Mx[i]=Mx[i-1];
		else {
			dp[i][1]=query(pre[i])+v[a[i]];
			dp[i][0]=Mx[pre[i]-1]+v[a[i]];
			ad(pre[i],dp[i][0]);
			Mx[i]=max(max(dp[i][0],dp[i][1]),Mx[i-1]);
		}
	}
	cout <<Mx[n<<1];
}
signed main(){
    int T=1;
	while(T--)Main();
	return 0;
}

```

---

## 作者：cengzh (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P11727)

调了整整两天，特此纪念。

(Update 2025/2/16：改了一下描述结构类型的格式捏。)

(Update 2025/2/19：没发现哪里有空格的错误。。。但是发现了另一处错误。)

(Update 2025/2/24：等了好久啊啊啊终于知道改哪里了。)

#

# 正文

第一眼动态规划，因为不同的选择之间会有很大的关联因素，贪心显然是不行的。

题面是比较抽象的，我们需要看出来题目在考什么。

从题目看能推出什么性质呢？

我们可以发现，两种相同的牌得分的结构只有两种：`abab` 型和 `aabb` 型，这里舍去了中间不相同的号码。

因为只有左右手可以放牌，类似于 `abcabc` 和 `abccab` 的结构都会使 `c` 将先前的 `a` 踢出去，从而得到 `bcbc` 的结构，这是可以与上方的 `abab` 相对应的。

我们设 $dp_i$ 为考虑到第 $i$ 张牌时的最大得分，$arr_i$ 为第 $i$ 张牌的编号，$last_i$ 为 $arr_i$ 第一次出现的位置。

分类讨论：

若不选这张牌，$dp_i = dp_{i-1}$。

若选了这张牌，根据我们的得分结构，它允许中间有另一张牌得分，并且满足 `abab` 型。所以有 $dp_i = \max(dp_{last_j} + v_{arr_j} + v_{arr_i})$，其中 $last_j < last_i < j < i$。

值得注意的是，以上式子保证了选取的 `b` 不会与 `a` 产生其它类型得分结构。

同时还考虑 `aabb` 结构，$dp_i = \max(dp_{i},dp_{last_i} + v_{arr_i})$。

容易写出以下 57pts 代码，时间复杂度接近 $O(n^2)$。


```c
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 400005;
long long dp[MAXN*2];
long long v[MAXN];
int arr[MAXN*2];
int chk[MAXN];
int last[MAXN*2];

int main(void) {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n * 2; i++) {
        scanf("%d", &arr[i]);
        if (chk[arr[i]] != 0) {
            last[i] = chk[arr[i]];
        }
        chk[arr[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
    }

    long long ans = 0;
    v[0] = 0;
    for (int i = 1; i <= n * 2; i++) {
        dp[i] = dp[i - 1];
        if (last[i] != 0) {
            // 考虑abab结构
            for (int j = i - 1; j > last[i]; j--) {
                if (last[j] != 0 && last[j] < last[i]) {
                    dp[i] = max(dp[i], dp[last[j]] + v[arr[j]] + v[arr[i]]);
                }
            }
            // 考虑aa结构
            dp[i] = max(dp[i], dp[last[i]] + v[arr[i]]);
        }
        ans = max(ans, dp[i]);
    }

    printf("%lld", ans);

    return 0;
}
```
如何优化？求最大值容易想到线段树，但是这里的最大值是有限制条件的。

这里我想了很多办法，包括笛卡尔树、主席树等等。

**在没有思路的时候，不妨换一个角度思考。**

注意到，我们只是想找到所有穿过 $last_j$ 的手牌对的 $dp_{last_i} + v_{arr_i}$ 最大值。

我们不妨用线段树维护这个最大值。

当一个手牌对 $(last_i,i)$ 产生时，它只对从 $last_i$ 到 $i$ 之间的手牌有影响，所以我们用 $dp_{last_i} + v_{arr_i}$ 将 $last_i$ 到 $i$ 之间所有手牌记录下来的最大值更新。

那么当在 $j$ 位置上时，$last_j$ 位置记录下的最大值就是所有符合跨过 $last_j$ 的手牌对的 $dp_{last_i} + v_{arr_i}$ 的最大值。

最后根据原代码将求最大值的部分修改即可。

请看代码：


```c
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 400005; 
long long dp[MAXN];
long long v[MAXN];
int arr[MAXN*2];
int chk[MAXN];
int last[MAXN*2];

struct Tree
{
	long long data;
	long long tag;
};

struct Tree Tree[MAXN*2*4]; 


void add_tag(int node,long long x)
{
	Tree[node].tag = max(Tree[node].tag,x);
	Tree[node].data = max(Tree[node].data,x);
	return ;
}

void push_down(int node)
{
	if (Tree[node].tag)
	{
		add_tag(node*2,Tree[node].tag);
		add_tag(node*2+1,Tree[node].tag);
		Tree[node].tag = 0; 
	}
	return ;
}

void upd(int node,int l,int r,int tl,int tr,long long x)
{
	if (tl <= l && r <= tr)
	{	
		
		add_tag(node,x);
	
		return ;
	}
	int mid = (l+r) / 2;
	
	push_down(node);
	
	if (mid >= tl)
	{
		upd(node*2,l,mid,tl,tr,x);
	}
	if (mid < tr)
	{
		upd(node*2+1,mid+1,r,tl,tr,x);
	}
	
	Tree[node].data = max(Tree[node*2].data,Tree[node*2+1].data);
	
	return ;
}

long long query(int node,int l,int r,int tl,int tr)
{
	if (tl <= l && r <= tr)
	{
		return Tree[node].data;
	}
	
	int mid = (l+r) / 2;
	
	push_down(node);
	
	long long res1=0,res2=0;
	
	if (mid >= tl)
	{
		res1 = query(node*2,l,mid,tl,tr);
	}
	if (mid < tr)
	{
		res2 = query(node*2+1,mid+1,r,tl,tr);
	}
	
	return max(res1,res2);
}

int main(void) {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n * 2; i++) {
        scanf("%d", &arr[i]);
        if (chk[arr[i]] != 0) {
            last[i] = chk[arr[i]];
        }
        chk[arr[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
    }

    long long ans = 0;
    v[0] = 0;
    for (int i = 1; i <= n * 2; i++) {
        dp[i] = dp[i - 1];
        if (last[i] != 0) {
        	dp[i] = max(dp[i],query(1,1,2*n,last[i],last[i]) + v[arr[i]]);
        	dp[i] = max(dp[i], dp[last[i]] + v[arr[i]]);
        	upd(1,1,2*n,last[i],i,dp[last[i]]+v[arr[i]]);
        }        
    }

    printf("%lld", dp[n*2]);

    return 0;
}
```

---

## 作者：ydzr00000 (赞：1)

提供一个线段树写法。

首先，如果一张写有 $X$ 的数字的卡牌最终没有获得 $V_X$ 的分数，那么这张卡牌只是在占用空间，并没有什么大用处，据此得到：“一张写有数字 $X$ 的卡牌如果被拿起，一定会得到 $V_X$ 的分数”。

假设两张写有数字 $X$ 的卡牌之间夹有写着数字 $Y,Z$ 的卡牌，即 `XYZX`，尝试全部拿起，那么过程一定是这样的：

1. 左手空着，右手拿起写有数字 $X$ 的卡牌。
2. 左手拿着写有数字 $X$ 的卡牌，右手拿起写有数字 $Y$ 的卡牌。
3. 左手不得不丢弃写有数字 $X$ 的卡牌，此时的卡牌上的数字为 $Z$。

据此可以得到：任何一对写有相同数字的卡牌之间最多选择拿起一张卡牌。

于是，拿起的卡牌的结构肯定是 `XX` 的形式与 `XYXY` 的形式，不可能是 `XYZXYZ` 或者 `XYXZYZ` 之类的形式。

考虑 DP，设 $f_i$ 表示考虑到了前 $i$ 张卡牌，设 $L_i,R_i$ 分别是写有数字 $i$ 的卡牌中，较左边的那一张的编号与较右边的那一张的编号，能够得到的最大分数，转移分三种：

1. 不拿第 $i$ 张卡牌，那么转移为 $f_i\gets f_{i-1}$。
2. 拿 $A_i$ 所对应的数字的卡牌，要求 $R_{A_i} = i$，且以 `XX` 的形式拿取，转移为 $f_i\gets f_{L_{A_i} - 1} + V_{A_i}$。
3. 拿 $A_i$ 所对应的数字的卡牌，要求 $R_{A_i} = i$，且以 `XYXY` 的形式拿取，转移为 $f_i\gets \underset{1\leq j\leq N, L_j < L_{A_i} < R_j < i}{\max} f_{L_j - 1} + V_{A_i} + V_{j}$，其含义是将 $A_i$ 视作 `Y` 并枚举可能的 `X` 求出最大收益。

暴力转移可以做到 $\mathcal{O}(N^2)$ 的复杂度。

瓶颈在于第三类转移，观察其转移式子，其目的是找到满足 $L_j < L_{A_i} < R_j$ 中 $f_{L_j - 1} + V_j$ 的最大值，按顺序扫描所以 $< i$ 的限制直接忽略，没有则视作 $0$，也即每遇到一个 $R_j$，就可以为 $[L_j, R_j]$ 内的每一个 $L_{A_i}$ 提供一个 $f_{L_j - 1} + V_j$ 的可能收益，最终每次转移时需要求出对应的 $L_{A_i}$ 的最大收益。总结一下：区间 checkmax，单点求值，可以用线段树维护。

综上，每次遇到一个 $R_j$ 的时候，先在线段树上查询搞定第三类转移，然后在线段树上更新最大值即可，时间复杂度为 $\mathcal{O}(N\log_2 N)$。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
class SegmentTree{
    private:
        struct node{
            long long val;
            long long tag;
        };
        vector<node>seg;
        inline void pushdown(int id)
        {
            seg[id<<1].val=max(seg[id<<1].val,seg[id].tag);
            seg[id<<1|1].val=max(seg[id<<1|1].val,seg[id].tag);
            seg[id<<1].tag=max(seg[id<<1].tag,seg[id].tag);
            seg[id<<1|1].tag=max(seg[id<<1|1].tag,seg[id].tag);
            seg[id].tag=0;
        }
        inline void pushup(int id)
        {
            seg[id].val=max(seg[id<<1].val,seg[id<<1|1].val);
        }
    public:
        inline void init(int n){seg.resize(n<<2|1);}
        inline void build(int l,int r,int id)
        {
            seg[id].tag=0;
            if(l==r)
            {
                seg[id].val=0;
                return;
            }
            int mid=(l+r)>>1;
            build(l,mid,id<<1);
            build(mid+1,r,id<<1|1);
            pushup(id);
        }
        inline void update(int l,int r,int id,int head,int tail,long long val)
        {
            if(l>=head&&r<=tail)
            {
                seg[id].val=max(seg[id].val,val);
                seg[id].tag=max(seg[id].tag,val);
                return;
            }
            pushdown(id);
            int mid=(l+r)>>1;
            if(mid>=head)
                update(l,mid,id<<1,head,tail,val);
            if(mid<tail)
                update(mid+1,r,id<<1|1,head,tail,val);
            pushup(id);
        }
        inline long long query(int l,int r,int id,int pos)
        {
            if(l==r)
                return seg[id].val;
            pushdown(id);
            int mid=(l+r)>>1;
            if(mid>=pos)
                return query(l,mid,id<<1,pos);
            return query(mid+1,r,id<<1|1,pos);
        }
};
SegmentTree S;
int main(){
    int n;
    scanf("%d",&n);
    vector<int>card(n<<1|1,0);
    for(int i=1;i<=(n<<1);i++)
        scanf("%d",&card[i]);
    vector<int>V(n+1,-1);
    for(int i=1;i<=n;i++)
        scanf("%d",&V[i]);
    vector<int>L(n+1,-1),R(n+1,-1);
    for(int i=1;i<=(n<<1);i++)
    {
        int x=card[i];
        if(L[x]==-1)
            L[x]=i;
        else
            R[x]=i;
    }
    vector<long long>dp(n<<1|1,0);
    S.init(n<<1);S.build(1,n<<1,1);
    for(int i=1;i<=(n<<1);i++)
    {
        dp[i]=dp[i-1];
        int x=card[i];
        if(R[x]==i)
        {
            dp[i]=max(dp[i],dp[L[x]-1]+V[x]);
            dp[i]=max(dp[i],S.query(1,n<<1,1,L[x])+V[x]);
            S.update(1,n<<1,1,L[x],R[x],dp[L[x]-1]+V[x]);
        }
    }
    printf("%lld\n",dp[n<<1]);
    
    return 0;
}
```

---

## 作者：poembelief (赞：1)

# 前言
~~怎么会有人做得出第五题做不出第四题啊！~~
# 题意
[题目传送门](https://www.luogu.com.cn/problem/P11727)
# 分析
最开始看到五个操作的时候，差点以为是大模拟，险些把我劝退，还好读懂题目之后，发现这题其实很像 [CSP-S 2024 T3](https://www.luogu.com.cn/problem/P11233)，不过本题要更复杂一些。

类似的，我们把相同的两张牌的下标转化成一个区间，手玩一下就可以发现：**区间包含是不合法的，每个区间最多与另一个区间交叉**。

因此，我们可以注意到：交集为空的两个区间的信息是一定可以累加的，存在包含关系的两个区间的信息是一定不可以累加的，存在交集但无包含关系的两个区间需要分类讨论。

这不是明显可以 DP 嘛！

我们可以发现，区间之间只可交叉一次的限制在于一张牌在被拿起后，若想要有贡献，最多只能再拿起一张其它牌。我们已经确认可以使用 DP，那么显然设计状态的时候多加一维即可，即：

$f_{i,0}$ 表示 $A_i$ 产生贡献且手上有另一张同样的牌时的最大答案。

$f_{i,1}$ 表示 $A_i$ 产生贡献且右手上有另一张同样的牌时的最大答案。

至于状态转移——状态都设计出来了，转移不是非常显然？不过需要注意：

1. 操作 2 中的两张牌会同时消失，这本来会影响答案的传递，但是题目又限制了每种牌最多出现两次，所以直接把 $f_{i,1}$ 的信息存在**第二张牌的位置**即可。

2. 转移时需要求前缀最大值，这个可以线性转移有点困难，因为 $f_{i,0}$ 需要存在**第一张牌的位置**以排除包含情况的答案贡献。本题也比较特殊，可以用线段树也可以用树状数组，下面的代码用的是树状数组。


# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
/*
	f[i][0]：第一张牌正在手上 
	f[i][1]：第一张牌正在右手上 
*/
const int N=1e6+5;
int n,a[N],la[N],now[N];
long long v[N],f[N][2],t1[N],t2[N];
void add1(int x,long long v){
	for(;x<=n;x+=x&-x){
		t1[x]=max(t1[x],v);
	}
}
long long ask1(int x){
	long long ans=0;
	for(;x;x-=x&-x){
		ans=max(ans,t1[x]);
	}
	return ans;
}
void add2(int x,long long v){
	for(;x<=n;x+=x&-x){
		t2[x]=max(t2[x],v);
	}
}
long long ask2(int x){
	long long ans=0;
	for(;x;x-=x&-x){
		ans=max(ans,t2[x]);
	}
	return ans;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen("tx.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=(n<<1);i++){
		scanf("%d",&a[i]);
		la[i]=now[a[i]];
		now[a[i]]=i;
	}
	for(int i=1;i<=n;i++) scanf("%lld",&v[i]);
	n<<=1;
	for(int i=1;i<=n;i++){
		if(!la[i]) continue;
		f[i][0]=max(ask1(la[i]),ask2(la[i]))+v[a[i]];
		f[i][1]=ask1(la[i])+v[a[i]];
		add1(i,f[i][0]);
		add2(la[i],f[i][1]);
	}
	printf("%lld\n",ask1(n));
	return 0;
}
```

---

## 作者：DengStar (赞：1)

### $O(N^{3})$ dp

由于一个人最多同时持有两张牌，所以容易想到一个 trivial 的 dp 状态设计：设 $f(i, x, y)$ 表示考虑到第 $i$ 张牌，左手上的牌为 $x$，右手上的牌为 $y$（没有牌则为 $0$）时能获得的最大收益。这个状态包含的信息显然是足够的。分别讨论要不要拿第 $i$ 张牌，容易列出转移方程（为方便，下面的 $a \gets b$ 实际上表示 $a \gets \max(a, b)$）：

1. 拿第 $i$ 张牌：
   1. 如果 $x = A_{i}$，则 $f(i + 1, y, 0) \gets f(i, x, y) + V_{A_{i}}$；
   2. 如果 $y = A_{i}$，则 $f(i + 1, 0, 0) \gets f(i, x, y) + V_{A_{i}}$;
   3. 否则 $f(i + 1, y, A_{i}) \gets f(i, x, y)$。
2. 不拿第 $i$ 张牌：$f(i + 1, x, y) \gets f(i, x, y)$。

初始化 $f(1, 0, 0) = 0$，其它状态为 $-\infty$，表示无法达到。答案为 $f(2N + 1, \cdot, \cdot)$ 中的最大值。

状态数 $O(N^{3})$，转移时间复杂度 $O(1)$，总时间复杂度 $O(N^{3})$，可以得到 37pts。

由于状态数太多，这种状态设计是完全没有前途的。

### $O(N^{2})$ dp

dp 的一个常见优化方向是**发掘性质，避免无用决策**。本题中，我们可以发现这样一个性质：如果拿了一张牌 $\texttt{a}$，之后又拿了两张不是 $\texttt{a}$ 的牌，$\texttt{a}$ 就会从手牌中移出，**而没有带来任何收益**。这实际上和拿 $\texttt{a}$ 没有任何区别。也就是说，只有这些决策是有用的：**如果拿了一张牌，接下来拿的两张牌内必须有一张相同的牌。**

进一步，可以发现总共只有两种拿牌的方式：

1. 连续拿两张相同的牌，形如 $\texttt{aa}$。
2. 交替拿完两种牌，形如 $\texttt{abab}$。

最终，实际拿牌的序列可以表示为这两种情况的拼接，例如 $\texttt{aabbcdcd}$。

根据这个性质，可以考虑这样进行 dp：对于一种牌 $\texttt{a}$，它**第二次**出现的时候，分 $\texttt{aa}$ 和 $\texttt{baba}$ 两种情况转移。设 $f(i)$ 表示考虑完第 $i$ 张后可以取得的最大收益，记 $pos(\texttt{a}, 1/2)$ 表示第 $\texttt{a}$ 种牌第 $1/2$ 次出现时的位置，那么选择第一种拿牌方式，可以获得 $f(pos(\texttt{a}, 1) - 1) + V_{\texttt{a}}$ 的收益；否则枚举满足 $pos(\texttt{b}, 1) < pos(\texttt{a}, 1) < pos(\texttt{b}, 2) < pos(\texttt{a}, 2)$ 的卡牌 $\texttt{b}$，选择 $\texttt{baba}$ 可以获得 $f(pos(\texttt{b}, 1) - 1) + V_{\texttt{b}} + V_{\texttt{a}}$ 的收益。最后不要忘了令 $f(i) \gets \max(f(i), f(i - 1))$。

参考代码如下（部分变量名称可能不同）：

```cpp
for(int i = 1; i <= 2 * n; i++) {
    if(pos[a[i]][0] == i) { // first time
        f[i] = f[i - 1]; continue;
    }
    i64 tmp1 = f[pos[a[i]][0] - 1] + val[a[i]] /*aa*/, tmp2 = 0;
    for(int j = pos[a[i]][0] + 1; j < i; j++) {
        if(pos[a[j]][1] == j && pos[a[j]][0] < pos[a[i]][0]) { // baba
            chmax(tmp2, f[pos[a[j]][0] - 1] + val[a[j]] + val[a[i]]);
        }
    }
    f[i] = max({f[i - 1], tmp1, tmp2});
}
```

这样 dp 的状态数为 $O(N)$，转移的时间复杂度为 $O(N)$，总时间复杂度为 $O(N^{2})$，瓶颈主要在于 $\texttt{baba}$ 类型的转移。可以获得 51pts。

### $O(N \log N)$ dp（正解）

$O(N^{2})$ dp 优化的前途显然比 $O(N^{3})$ dp 要大得多，因为它的状态数只有 $O(N)$，我们只需考虑怎么优化转移过程。

现在我们的瓶颈在于枚举满足 $pos(\texttt{b}, 1) < pos(\texttt{a}, 1) < pos(\texttt{b}, 2) < pos(\texttt{a}, 2)$ 的 $\texttt{b}$ 找最大值的过程。自然想到用数据结构优化找最值的过程，但我们发现很难限制“$pos(\texttt{b}, 1) < pos(\texttt{a}, 1) < pos(\texttt{b}, 2) < pos(\texttt{a}, 2)$”这个条件。

不妨换一个转移顺序：对于每对牌，在**第一次**出现的位置转移，即假设 $A_{i}$ 第一次出现的位置为 $i$。再设一个状态 $g(i)$ 表示限制 $A_{i}$ 的两张牌必须连续取（即形如“$\texttt{aa}$”）时，前 $i$ 张牌可以获得的最大收益（如果 $i$ 不是 $A_{i}$ 第二次出现的位置，则 $g(i) = 0$，这是自然的）。那么显然就有：
$$
g(pos(A_{i}, 2)) \gets f(i - 1) + V_{A_{i}}
$$
设 $g$ 这个状态的目的在于优化 $f$ 的转移。只需考虑 $\texttt{baba}$ 这种形式：实际上，只要在 $j \in (i, pos(A_{i}, 2))$ 这个区间内找到 $g(j)$ 的最大值即可。假设 $A_{j}$ 对应的牌为 $\texttt{b}$，由于我们按 $i$ 从小到大转移，所以如果 $f(j) \neq 0$，那么 $\texttt{b}$ 就一定满足了 $pos(\texttt{b}, 1) < pos(\texttt{a}, 1) < pos(\texttt{b}, 2) < pos(\texttt{a}, 2)$。又由于 $g(j)$ 限制了 $\texttt{b}$ 必须两张连续取，这种情况下就可以把第一个 $\texttt{a}$ 插入到两张连续的 $\texttt{b}$ 中，形成 $\texttt{baba}$ 这种形式。因此，这个转移是正确的，即
$$
f(pos(A_{i}, 2)) \gets V_{A_{i}} + \max_{j} g(j)
$$
其中的 $j$ 满足 $pos(A_{j}, 1) < pos(A_{i}, 1) < pos(A_{j}, 2) < pos(A_{i}, 2)$。以及不要忘了令 $f(i) \gets \max(f(i), f(i - 1))$。

用单点修改，区间求 $\max$ 的线段树维护 $g$ 数组，可以做到 $O(N \log N)$ 的时间复杂度。[AC 记录](https://www.luogu.com.cn/record/202835624)

参考代码如下（部分变量名称可能不同）：

```cpp
for(int i = 1; i <= 2 * n; i++) {
    if(pos[a[i]][1] == i) { // second time
       chmax(f[i], max(tr.query(i, i), f[i - 1]));
       continue;
    }
    f[pos[a[i]][1]] = val[a[i]] + tr.query(i, pos[a[i]][1]);
    tr.change(pos[a[i]][1], f[i - 1] + val[a[i]]);
    chmax(f[i], f[i - 1]);
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目分析

因为我们只有两只手，所以对于一对相同元素 $a_j,a_i(j<i)$，想要使它们配对中间就不能拿两张及以上的牌，否则就会把 $a_j$ 挤出左手。这样，我们就可以 DP 了。令 $p_i$ 表示整数 $i$ 第一次出现的位置，$dp_i$ 表示前 $i$ 张牌能获得的最大得分。我们可以考虑以下转移：

- 如果我们不拿第 $i$ 张牌，则 $dp_i=dp_i-1$。
- 如果我们拿第 $i$ 张牌，且在 $p_i$ 和 $i$ 之间不拿任何牌，则 $dp_i=dp_{p_i}+v_{a_i}$。
- 如果我们拿 $i$ 张牌，且在 $p_i$ 和 $i$ 之间拿一张牌，则 $dp_i=\max_{p_{a_j}<p_{a_i}<j<i}{(dp_{p_{a_j}}+v_{a_j}+v_{a_i})}$。

但是，这样做的时间复杂的为 $O(n^2)$，如何优化呢？前两个转移显然不需要优化，重点来看第三个转移。注意到 $p_{a_j}<p_{a_i}<j$，即 $\forall p_{a_i} \in (p_{a_j},p_{a_i})$，$dp_i$ 都能从 $dp_{p_{a_j}}$ 转移过来，因此我们可以维护一棵区间修改，求单点最大值的线段树来进行优化。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define all(vec) vec.begin(),vec.end()
#define fr first
#define sc second
#define pq priority_queue
#define gr greater
#define lc(x) x<<1
#define rc(x) x<<1|1
using ll=long long;
using db=double;
using i128=__int128;
using pii=pair<int,int>;

const int N=4e5+5;
int n,a[2*N],b[N],pos[N];
ll dp[2*N];

namespace SGT{
    struct node{
        int l,r;
        ll tag,ma;
    }bt[8*N];
    
    void pushup(int x){bt[x].ma=max(bt[lc(x)].ma,bt[rc(x)].ma);}

    void pushdown(int x){
        if(bt[x].tag!=-1){
            bt[lc(x)].ma=max(bt[lc(x)].ma,bt[x].tag),bt[lc(x)].tag=max(bt[lc(x)].tag,bt[x].tag);
            bt[rc(x)].ma=max(bt[rc(x)].ma,bt[x].tag),bt[rc(x)].tag=max(bt[rc(x)].tag,bt[x].tag);
        }
        bt[x].tag=-1;
    }

    void build(int x,int l,int r){
        bt[x].l=l,bt[x].r=r,bt[x].tag=-1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(lc(x),l,mid);
        build(rc(x),mid+1,r);
        pushup(x);
    }

    void modify(int x,int l,int r,ll v){
        if(bt[x].l>=l&&bt[x].r<=r){
            bt[x].tag=max(bt[x].tag,v),bt[x].ma=max(bt[x].ma,v);
            return;
        }
        pushdown(x);
        int mid=(bt[x].l+bt[x].r)>>1;
        if(l<=mid) modify(lc(x),l,r,v);
        if(r>mid) modify(rc(x),l,r,v);
        pushup(x);
    }

    ll query(int x,int p){
        if(bt[x].l==p&&bt[x].r==p) return bt[x].ma;
        pushdown(x);
        int mid=(bt[x].l+bt[x].r)>>1;
        if(p<=mid) return query(lc(x),p);
        else return query(rc(x),p);
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=2*n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];

    SGT::build(1,1,2*n);
    for(int i=1;i<=2*n;i++){
        dp[i]=dp[i-1];
        if(pos[a[i]]){
            dp[i]=max(dp[i],dp[pos[a[i]]]+b[a[i]]);
            dp[i]=max(dp[i],SGT::query(1,pos[a[i]])+b[a[i]]);
            SGT::modify(1,pos[a[i]],i,dp[pos[a[i]]]+b[a[i]]);
        }
        pos[a[i]]=i;
    }

    cout<<dp[2*n]<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T=1;
    // cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：114514lhc (赞：0)

感觉挺不错的一题   
先说一个结论：如果你想拿两张相同牌，那么他们之间的牌你只能拿一张或不拿。  
因为如果你拿了两张及张以上，那么根据步骤 $3,4$ ，你拿的之前的牌就会被先换到左手，然后扔掉，造成无意义拿取。   
由上述结论，我们可推出你拿的牌的序列必然可被分成 $x,x$ (相同牌之间不拿)和 $y,x,y,x$ (拿一张)两种结构，之后就简单了。   
定义 $mx_i$ 为前 $i$ 张牌中可拿到的最大价值, $c_i$ 为 $a_i$ 另一次出现的位置  
1. 若以 $x,x$ 结构结尾，则 $mx_i(\text{第二个 }x)=mx_{c_i-1}(\text{第一个 }x\text{ 前一个})+v_{a_i}$
2. 若以 $y,x,y,x$ 结构结尾，则从 $1$ 到 $c_i-1$ 枚举 $j(\text{第一个 }y)$ ,若 $c_j(\text{第二个 }y) \ge c_i(\text{第一个 }x)$ 且 $c_j \le i(\text{第二个 }x)$ ，则 $mx_i=mx_{j-1}+v_{a_i}+v_{a_j}$

 $mx_i$ 就是上面两种情况和 $mx_{i-1}$ 的最大值。   
 但这是 $n^2$ 的，会TLE，所以我们要将枚举 $j$ 的过程压缩。不难发现，枚举 $j$ 其实就是找区间最大值，我们可以把这项重任浇给线段树，每次查询 $1$ 到 $c_i-1$ 最大值，求完 $mx_i$ 后，把 $c_i$ 修改成 $mx_{c_i-1}+v_{a_i}$ 即可。  
 聪明的你可能会问：用线段树怎么判断 $c_j \ge c_i$ 和 $c_j \le i$ ，确实无法判断，但也不用判断，如果不符合这俩条件，就会变成 $y,y,x,x$ 结构（根据线段树修改顺序，不会诞生 $y,x,x,y$ 结构），这符合1号结构，也合法。   
 代码如下（马蜂抽象）
 
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[814514],v[814514],mx[814514],la[814514],c[814514];
int l[11451400],r[11451400],k[11451400];
//以下线段树
void build(int t,int ll,int rr)
{
    l[t]=ll;r[t]=rr;
    if(ll==rr)return;
    int mid=(ll+rr)/2;
    build(t*2,ll,mid);
    build(t*2+1,mid+1,rr);
}
void tree1(int t,int x,int y)
{
    if(l[t]==r[t]){k[t]=y;return;}
    int mid=(l[t]+r[t])/2;
    if(x<=mid)tree1(t*2,x,y);
    else tree1(t*2+1,x,y);
    k[t]=max(k[t*2],k[t*2+1]);
}
int tree2(int t,int ll,int rr)
{
    if(l[t]>rr||r[t]<ll)return 0;
    if(l[t]>=ll&&r[t]<=rr)return k[t];
    return max(tree2(t*2,ll,rr),tree2(t*2+1,ll,rr));
}
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n*2;i++)
    {
        cin>>a[i];
        if(la[a[i]])c[i]=la[a[i]],c[la[a[i]]]=i;
        la[a[i]]=i;
    }//找另一个a_i出现位置
    int ans=0;
    build(1,0,n*2);
    for(int i=1;i<=n;i++)cin>>v[i];
    for(int i=1;i<=n*2;i++)
    {
        mx[i]=mx[i-1];
        if(!c[i])continue;
        mx[i]=max(mx[i],mx[c[i]-1]+v[a[i]]);
        mx[i]=max(mx[i],tree2(1,1,c[i]-1)+v[a[i]]);
        tree1(1,c[i],v[a[i]]+mx[c[i]-1]);//单点修改c_i
    }
    cout<<mx[2*n];
    return 0;
}

```

---

## 作者：ELECTRODE_kaf (赞：0)

首先可以发现选择的牌必须产生贡献（否则只会占用空间不如不选）。其次产生贡献的一对牌之间最多再选择一张牌（否则前一张牌会被扔掉），所以最佳选择方案一定形如 AABB 或 ABAB。

预处理每个 $A_i$ 上次出现的位置 $pre_i$（未出现过则为 $0$）。

考虑 DP。设 $dp_i$ 表示消除 $A_i$ 的最大价值。此时有两种转移方式：①从 $A_{pre_i}$ 之前转移；②从一个 $pre_j<pre_i$ 转移。称它们为第 $1/2$ 种方式。设 $dp_{i,0/1}$ 表示以第 $1/2$ 种方式消除 $A_i$ 的最大价值。第一种方式从最大值转移。第二种方式则需要将 $dp_{i,0}$ 记录在 $pre_i$ 的位置上，然后从 $j\le pre_i$ 的位置转移。树状数组维护。

```cpp
const ll N = 8e5 + 10;
ll n, a[N], v[N], pre[N], dp[N][2], temp[N], ans[N], bt[N];

ll lowbit(ll x) {
	return x & -x;
}

void add(ll p, ll x) {
	while (p <= n * 2) {
		update(bt[p], x, max);
		p += lowbit(p);
	}
}

ll query(ll p) {
	ll ret = 0;

	while (p) {
		update(ret, bt[p], max);
		p -= lowbit(p);
	}

	return ret;
}

ll max3(ll a, ll b, ll c) {
	return max(max(a, b), c);
}

int main() {
	cin >> n;
//	memset(temp,0,sizeof(temp));
//	memset(dp,0,sizeof(dp));
//	memset(pre,0,sizeof(pre));

	rep(i, 1, n * 2)
		cin >> a[i];

	rep(i, 1, n * 2) {
		if (temp[a[i]])
			pre[i] = temp[a[i]];
		else
			temp[a[i]] = i;
	}

	rep(i, 1, n) cin >> v[i];

	rep(i, 1, n * 2) {
		if (pre[i] == 0)
			ans[i] = ans[i - 1];
		else {
			dp[i][1] = query(pre[i]) + v[a[i]];
			dp[i][0] = ans[pre[i] - 1] + v[a[i]];
			add(pre[i], dp[i][0]);
			update(ans[i], max3(dp[i][0], dp[i][1], ans[i - 1]), max);
		}
	}

	cout << ans[n * 2];
}
```

---

