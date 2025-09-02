# [ZYOI Round1] Bird/鸟

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/hdzxjtsk.png)

江豚吹浪立，沙鸟得鱼闲。

## 题目描述

有一只鸟在 $n$ 棵树之间飞行，第 $i$ 棵树的高度为 $a_i$，从左到右排列。这只鸟太肥了，不能往高处飞，只能朝左或右两个方向滑翔。

若这只鸟现在站着的树高度为 $a_i$，那么这只鸟可以飞到的树高度必须小于 $a_i$，且飞行时经过的树高度也都需要小于 $a_i$。

这只鸟有 $k$ 张瞬移卡，第 $i$ 张卡的魔力值为 $b_i$。这只鸟可以在任意一棵树上选择使用瞬移卡，瞬移到高度不超过该瞬移卡魔力值的一棵树上（如果鸟当前所在的树高度不超过瞬移卡的魔力值，则它可以瞬移到当前所在的树上）。但是它只能按照给出的顺序使用瞬移卡。数据保证所有瞬移卡都可以使用（即不存在一张瞬移卡，魔力值小于所有树的高度）。

这只鸟初始位置在第一棵树上，请求出它最多可以飞行几次（不包含瞬移）。

注意：鸟可以重复经过同一棵树。

## 说明/提示

对于 $10\%$ 的数据，$1 \le n,k \le 10$。

对于 $30\%$ 的数据，$1 \le n,k \le 5 \times 10^3$。  

对于 $70\%$ 的数据，$1 \le n,k \le 10^5$。  

对于 $100\%$ 的数据，$1 \le n,k \le 3 \times 10^5$，$0 \le a_i,b_i \le 10^9$。

## 样例 #1

### 输入

```
3 1
1 5 2
6```

### 输出

```
1```

## 样例 #2

### 输入

```
5 2
1 3 2 7 1
4 10```

### 输出

```
3```

# 题解

## 作者：sqrtqwq (赞：11)

考虑维护一个大根的笛卡尔树。那么从一颗树跳到下一棵树的操作就类似于从一个点跳到他在笛卡尔树上的一个儿子。

那么对于一个节点 $i$ 考虑去维护 $dp_i$ 表示从节点 $i$ 开始，能跳多少次即节点 $i$ 向下的最长链长度。

那么我们直接从根节点开始开始 $dp$，那么转移即为：

$$dp_u = \min(dp_{ls} - [a_{ls} = a_{u}],dp_{rs} - [a_{rs} = a_u]) + 1$$

然后对于使用魔力，我们可以直接用双指针去找最高可以在那一棵树开始即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 3e5 + 10;
int n,k,a[maxn],b[maxn],ch[maxn][2];
int stk[maxn],dp[maxn],top;
int maxx[maxn];
pair<int,int> p[maxn];
void build()
{
    for(int i = 1;i <= n;i++)
    {
        int pos = 0;
        while(top && a[stk[top]] <= a[i])pos = stk[top],top--;
        if(top)ch[stk[top]][1] = i;
        ch[i][0] = pos;stk[++top] = i;
    }
}

void turns(int u,int ls){dp[u] = max(dp[u],dp[ls] - (a[u] == a[ls]) + 1);}

void dfs(int u)
{
    if(ch[u][0])dfs(ch[u][0]),turns(u,ch[u][0]);
    if(ch[u][1])dfs(ch[u][1]),turns(u,ch[u][1]);
}

signed main()
{
    cin >> n >> k;
    for(int i = 1;i <= n;i++)cin >> a[i],p[i] = {a[i],i};
    for(int i = 1;i <= k;i++)cin >> b[i];
    build();dfs(stk[1]);sort(p + 1,p + n + 1);sort(b + 1,b + k + 1);
    int ans = dp[1];
    for(int i = 1;i <= n;i++)maxx[i] = max(maxx[i - 1],dp[p[i].second]);
    int j = 1;
    for(int i = 1;i <= n;i++)
    {
        while(p[i].first == p[i + 1].first)i++;
        while(b[j] < p[i + 1].first && j <= k)ans += maxx[i],j++;
    }
    while(j <= k)ans += maxx[n],j++;
    cout << ans;
    return 0;
}

```

---

## 作者：云浅知处 (赞：6)

我们考虑处理出来从第 $i$ 棵树能够飞行的最多次数 $f_i$，那么对于瞬移卡就可以按照 $b_i$ 排序然后二分再求一个前缀的最大 $f_i$ 来处理掉。

注意到 $f_i$ 满足一个转移方程就是 $f_i=\max\{f_j+1|\forall p\in(i,j],a_p<a_i\}$。这是 $j>i$ 的情况，$j<i$ 的情况是类似的。

因此可以先用单调栈处理出来 $L_i$ 和 $R_i$ 表示 $i$ 左右两侧离 $i$ 最近的 $\ge a_i$ 的数的位置，那么转移方程就相当于 $f_i=\max\{f_j+1|j\in[L_i+1,R_i-1]\}$。用线段树维护单点修改与区间查询最大值，可以做到 $O(n\log n+k\log n)$，常数优秀的话可以通过。注意转移需要按照 $a_i$ 递增的顺序。（当时场上写的这个用 zkw 过了=w=）

其实注意到一个性质就是：如果设 $x,y$ 分别为 $[L_i+1,i)$ 与 $(i,R_i-1]$ 中的最大值位置，那么最优情况下第一步一定是飞到 $x,y$ 中的一个。建出笛卡尔树，那么 $x,y$ 就相当于 $i$ 的左右子节点，在笛卡尔树上 dp 即可。注意这种情况需要讨论 $a_y=a_i$ 的情况。时间复杂度是 $O(n+k\log n)$。

给出 $O(n\log n+k\log n)$ 的 AC 代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

const int MN=5e5+5;
int dp[MN],n,k,a[MN],b[MN];

struct SegTree{
	int d[MN<<2],N,M;
	
	void pre(){
		memset(d,0,sizeof(d));
		for(N=1,M=0;N<=n+1;N<<=1,M++);
	}
	
	void modify(int x,int v){
		x+=N,d[x]=max(d[x],v);
		while(x)x>>=1,d[x]=max(d[x<<1],d[x<<1|1]);
	}
	
	int query(int l,int r){
		int ans=0;
		for(l=l+N-1,r=r+N+1;l^r^1;l>>=1,r>>=1){
			if(~l&1)ans=max(ans,d[l^1]);
			if(r&1)ans=max(ans,d[r^1]);
		}
		return ans;
	}
}tree;

pair<int,int>stk[MN];
int top=0;

int L[MN],R[MN],premax[MN];
pair<int,int>val[MN];

#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define OK puts("OK")

const int INF=1e9;

signed main(void){
	
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif		
	
	n=read(),k=read();
	for(int i=1;i<=n;i++)val[i].fi=a[i]=read(),val[i].se=i;
	for(int i=1;i<=k;i++)b[i]=read();
	sort(val+1,val+n+1);
	
	for(int i=1;i<=n;i++){
		while(top&&stk[top-1].fi<a[i])top--;
		if(top==0)L[i]=0;
		else L[i]=stk[top-1].se;
		stk[top++]=mk(a[i],i);
	}top=0;
	for(int i=n;i>=1;i--){
		while(top&&stk[top-1].fi<a[i])top--;
		if(top==0)R[i]=n+1;
		else R[i]=stk[top-1].se;
		stk[top++]=mk(a[i],i);
	}
	
	tree.pre();
	for(int i=1;i<=n;i++){
		int id=val[i].se;
		if(L[id]+1==R[id]-1)dp[id]=0;
		else dp[id]=tree.query(L[id]+1,R[id]-1)+1;
		tree.modify(id,dp[id]);
	}
	
	for(int i=1;i<=n;i++)premax[i]=max(premax[i-1],dp[val[i].se]);
	
	int ans=dp[1];
	for(int i=1;i<=k;i++){
		int pos=upper_bound(val+1,val+n+1,mk(b[i],INF))-val-1;
		ans+=premax[pos];
	}
	
	cout<<ans<<endl;
    return 0;
}
```

---

## 作者：meifan666 (赞：5)

### 题目大意
一只鸟在
$n$
棵树中从第一棵树开始飞行，每次只能从现在站着的树上，飞到更矮的树上，且途径的树也要比原来的树矮。鸟可以按顺序使用瞬移卡，每张卡能直接让鸟瞬移到高度不超过其魔力值的树。问鸟最多能飞几次。
### 思路
鸟的飞行有如下性质：第一，鸟只能往更低的树上飞。第二，鸟肯定不能在不使用瞬移卡的前提下，在一棵树左右来回飞，因为这样一定会被这棵树挡住。

由此，我们就想到维护一棵大根堆的**笛卡尔树**。每棵树，即每个节点能飞行的最大次数就是这个节点往下的最长链的长度。如果再使用记忆化搜索的话，我们就可以将这个步骤的时间压缩至
$O(n)$，这个时间复杂度还是能接受的。

然后，我们根据大根堆的性质，就能知道根节点一定是高度最大的树，记录编号后我们就从它开始搜索。

那么怎么使用瞬移卡？很容易知道，若要最大化飞行次数，则瞬移卡需要用在既满足高度不超过其魔法值，飞行的最大次数又是最大的树上。由此，我们将问题转换为怎么快速找这种树。

我们可以先将树按高度排序，然后用一个栈维护。遍历每棵树时，若其高度大于等于栈顶的树，且它的飞行最大次数小于等于栈顶的树，那么，这个新来的树一定对我们没用；如果它的高度等于栈顶的树，且它的飞行最大次数大于等于栈顶的树，那么，栈顶的树也一定对我们没用。

在这样的筛法下，我们筛选了一组对答案有用的树，并且这些树有一个可喜的性质：它们的高度单调递增，最大飞行次数也是单调递增。由此，你想到了什么？没错，我们可以将其**二分**！到了这一步，我们再把所有思路连起来，就能愉快地过了这道题了。

最后贴上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,root,t,cnt,magic[300100],ans;
struct tree{
	int val,fly,lson,rson,id;
}tr[300100];
int a[300100];//存入待选树
void update(int x){
	if(x==0)return;
	update(tr[x].lson);update(tr[x].rson);
	int a=tr[tr[x].lson].fly,b=tr[tr[x].rson].fly;
	if(tr[x].val==tr[tr[x].lson].val)a--;
	if(tr[x].val==tr[tr[x].rson].val)b--;
	tr[x].fly=max(a,b)+1;
}
stack<int>p;
bool cmp(tree x,tree y){
	return x.val<y.val;
}
int find(int x){
	int l=1,r=cnt,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(tr[a[mid]].val>x)r=mid-1;
		else l=mid+1,ans=mid;
	}
	return ans;
}
signed main(){
	cin>>n>>k;
	tr[0].fly=-1,tr[0].val=-1;
	for(int i=1;i<=n;i++){
		cin>>tr[i].val;
		if(tr[i].val>=t)t=tr[i].val,root=i;
		tr[i].id=i;
	}
	for(int i=1;i<=n;i++){
		int t=-1;
		while(!p.empty()&&tr[p.top()].val<=tr[i].val){
			t=p.top();p.pop();
		}
		if(!p.empty())tr[p.top()].rson=i;
		if(t!=-1)tr[i].lson=t;
		p.push(i);
	}//建立笛卡尔树，飞行次数就是节点的最长链
	update(root);
	ans=tr[1].fly;
	sort(tr+1,tr+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(tr[a[cnt]].val<=tr[i].val&&tr[a[cnt]].fly>=tr[i].fly)continue;
		if(tr[a[cnt]].val==tr[i].val&&tr[a[cnt]].fly<=tr[i].fly)--cnt;
		a[++cnt]=i;//如此筛选可以保证a中的树高度、贡献值单调递增
	}
	for(int i=1;i<=k;i++)cin>>magic[i];
	t=1;
	while(t<=k)ans+=tr[a[find(magic[t])]].fly,t++;
	cout<<ans;
	return 0;
}
```

---

## 作者：SSER_ZRQ (赞：5)

#  Bird题解

听说这题是用笛卡尔树秒的，但因本蒟蒻太菜，不会。于是用了另外的一些~~乱搞~~巧妙的做法。这里将以不同的分分段讲解。

## $10pts$
爆搜即可。注意几个细节:

一，使用各个卡牌之间相互独立，因此将各个卡牌分开选；

二，每一次飞要飞到不能再飞为止，不然一定是亏的；

[Bird 10pts代码](https://www.luogu.com.cn/paste/h4vzgkfp)

## $30pts$


加上记忆化即可得 $30pts$

[Bird 30pts代码](https://www.luogu.com.cn/paste/lowgaob1)


## $70pts$


减去无用状态！！！

可以发现，在第 $x$ 个点时，并不是飞到的每个点都是最优的。

如果飞到点 $y$, 且有另外的能飞到的一个点z使得 $a[z]>a[y]$，则可以先飞到 $z$，再由 $z$ 飞到 $y$。

设x位置左边第一个 $\geqslant x$ 的数的下标为 $L[x]$，右边为 $R[x]$。

最终得出结论：$x$ 只有飞到 $L[x]\cdots x-1$ 中的最大值们与 $x+1\cdots R[x]$ 中的最大值们时才有可能得到最大值。

**为什么要强调“们”呢？？？**

最大值不一定只有一个，各个最大值之间可能答案不同。

如何优化查询答案的时间？

将卡牌数组排好序（因为不同的顺序使用答案相同）

再将存树的高度的数组加上下标排好序。

因为 $b[i+1]\geqslant b[i]$，且 $a[i+1]\geqslant a[i]$.

用一个变量存上一个 $b[i]$ 到的节点与答案，$b[i+1]$ 时继续访问，更新最大值即可。

时间复杂度：$O(n^2+nlogn+mlogm)$

注：由于本题数据水，可以卡到 $100pts$。

[70~100pts](https://www.luogu.com.cn/paste/9u1v18e3)


## $100pts$



仔细想一想，在查找最大值们的时候可能会超时。

设 $x$ 位置左边第一个 $\geqslant x$ 的数的下标为 $L[x]$，右边为 $R[x]$。

既然查到 $y$ 时 $a[y]<a[x]$，那么根据定义，$a[L[y]+1\cdots y-1]<a[y]<a[x]$。

那么只需直接跳到 $L[y]$ 就可以了！！！

$O(n\log n+m\log m)$
且常数极小


[AC代码](https://www.luogu.com.cn/paste/z5lhjx5g)

---

## 作者：Alstar (赞：5)

## 神说，笛卡尔树秒了
如果不知道笛卡尔树的，可以去 [OIwiki](https://oi-wiki.org/ds/cartesian-tree/) 里了解一下。接下来的讲解将依照笛卡尔树展开。

这是一种理解起来很方便，虽然不怎么常用的构造树，复杂度是 $O(n)$。

### 解题思路

OK，想必你已经大致了解了笛卡尔树是什么东西。

由题可得，设 $sum[i]$ 为第$i$棵树能飞行的次数，那么 $sum[i]=\max (sum[x]+1,sum[y]+1)$。$xy $ 即通过树 $i$ 可以飞到的树。

我们观察题目不难发现，对于任意一棵树，想要飞的最多，下一步应该飞到**这棵树左侧或右侧可到达的最高的树**，因为左侧或右侧其它的树都可以通过这棵树飞到。

因此，我们可以构建一个大根的笛卡尔树。对于每一个节点，它的左儿子和右儿子即它左边和右边最大的那个节点。

接着我们依据公式 $sum[i]=\max\ (sum[ls[i]]+1,sum[rs[i]]+1)$，搜索得出每个节点可以飞行的次数。

最后，依据 $b$ 数组，将 $\max(sum[i\ (a[i]<b[j])\ ])$ 加起来即可得出答案。

**特别地**，对于左右儿子节点与本节点相同的情况，根据题目与解法推理可得，只需要不记录相同的儿子节点即可(就是 $sum[i]$ 不加一)。

时间复杂度的大头反而是排序，其余都是 $O(n)$ 级别的。

$O(n+nlogn)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=3e5+5;
int n,k,ans;
int b[N],cot[N];
int rs[N],ls[N],sta[N],top,root;
struct str{
	int num,sum;
}a[N];

bool cmp(int x,int y){ return x>y; }
bool cmp2(str x,str y){ return x.sum>y.sum; }

int solve(int p)
{
	if(p==0)
		return 0;
	if(a[ls[p]].num==a[p].num)//左右儿子节点相同的情况 
		a[p].sum=max(a[p].sum,solve(ls[p]));
	else
		a[p].sum=max(a[p].sum,solve(ls[p])+1); 
	if(a[rs[p]].num==a[p].num)
		a[p].sum=max(a[p].sum,solve(rs[p]));
	else
		a[p].sum=max(a[p].sum,solve(rs[p])+1); 
	
	return a[p].sum;
}

int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].num;		
		if(a[i].num>a[root].num)
			root=i;
	}
	for(int i=1;i<=k;i++)
		cin>>b[i];
	sort(b+1,b+1+n,cmp);
	//构建笛卡尔树 
	for(int i=1;i<=n;i++)
	{
		int p=top;
		while(a[i].num>a[sta[p]].num && p>0) p--;
		if(p>0) rs[sta[p]]=i;
		if(p<top) ls[i]=sta[p+1];
		sta[++p]=i;
		top=p;
	}
	//搜索求sum 
	solve(root);
	ans+=a[1].sum-1;//记得要减 1 
	sort(a+1,a+1+n,cmp2);
	top=1;
	for(int i=1;i<=n;i++)
	{
		while(b[top]>=a[i].num && top<=k)
		{
			ans+=a[i].sum-1;
			top++;
		}
	}
	cout<<ans;
	return 0;
}
```
求过。

想过审好难啊QWQ。

---

## 作者：WFHFAQFXY (赞：4)

# P8051 Bird
### 前置知识：本题解使用： ST 表（线段树也可以）, dfs ，笛卡尔树，可以分别进行练习后来看

![](https://cdn.luogu.com.cn/upload/image_hosting/hdzxjtsk.png)

# 思路
直接看题目时，会发现难以下手。鸟的飞行不但目的地不可以高于现在的，连过程中也不可以有高于现在的，使其实现难度较大，况且瞬移卡的存在更加大了难度。

## 笛卡尔树的建立

但是此时，由鸟飞性质，发现了它的飞行轨迹类似于堆（只能从大飞到小，中间还不能有大于现在的，否则与堆的性质相矛盾），此时如果对笛卡尔树的性质了解较深的同学可能就会想到笛卡尔树了，它的堆和二叉搜索树的性质符合这道题。（还有一个原因关于其二叉搜索树，便于统计答案。）

那么好，我们就先建一颗笛卡尔树，并且可以取等（单调栈部分）。接下来，就是对于瞬移卡的操作。

代码如下：

```cpp
void build()
{
    int tp=0;
    for(int i=1;i<=n;i++)
    {
        int k=tp;
        while(k&&a[stk[k]]<=a[i]) k--;
        if(k) rf[stk[k]]=i;
        if(k<tp) lf[i]=stk[k+1];
        k++;
        stk[k]=i;
        tp=k;
    }
    rt=stk[1];
}
```


## 瞬移卡

看到瞬移卡的性质，我们不难想到每一次肯定可以选择使本次操作利益最大的操作。但是注意，利益最大的树不一定是最高的树，所以不能直接找。

而这个时候，就要想到 ST 表（或者线段树）了，用它来查询区间内的最大利益。

由贪心思想，在这里区间越大，就越有可能存在更大的利益。那么我们可以二分，寻找到那个刚刚好可选与不可选的分界线，由此来找到 ST 表查询的右端点。

代码如下：

```cpp
int rmq(int l,int r)
{
	int y=log2(r-l+1);
    return max(st[r+1-(1<<y)][y],st[l][y]);
}
for(int j=1;(1<<j)<=n;j++)
    {
        for(int i=1;i+(1<<j-1)-1<=n;i++)
        {
            st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
        }
    }
    for(int i=1;i<=m;i++)
    {
        int k=rd(),h=lower_bound(lf+1,lf+1+n,k)-lf-1;//lf为高度
        cnt+=rmq(1,h);
    }
```
## 预处理

按照我们的思路，最后的问题就是实现如何预处理出利益了。由笛卡尔树的二叉搜索树性质，直接 dfs 来寻找与统计即可。

但是，对于高度相同的节点，我们要进行特殊处理，相同的只能算一遍。具体的见代码：


```cpp
int dfs(int nw)
{
    if(lf[nw]+rf[nw]==0) return 0;
    if(!rf[nw]) 
    {
        int h=dfs(lf[nw])+1;
        if(a[lf[nw]]==a[nw]) 
        {
            h--;
        }
        c[nw].cf=h;
        return h;
    }
    if(!lf[nw])
    {
        int h=dfs(rf[nw])+1;
        if(a[rf[nw]]==a[nw]) 
        {
            h--;
        }
        c[nw].cf=h;
        return h;
    }
    int d=dfs(lf[nw])+1,e=dfs(rf[nw])+1;
    if(a[rf[nw]]==a[nw]) 
    {
        e--;
    }
    if(a[lf[nw]]==a[nw]) 
    {
        d--;
    }
    c[nw].cf=max(d,max(e,c[nw].cf));
    return max(d,max(e,c[nw].cf));
}
```

至此，实现结束，连起来，通过此题。

---

## 作者：Swordmaker (赞：4)

# Bird

# 前置知识

本题可能用到二叉搜索树，笛卡尔树，堆等知识，如果对这些知识不熟，可以先做几道模板题。  

# 思路分析

由于本题对于鸟飞行的限制，需要维护一个具有**单调性**的序列，只有这样才能保证鸟在飞行时经过的树和目标位置的树都严格小于等于出发的树。

# 数据结构

既然是单调，那么就能想到**堆**了。
那么这里抛出一个问题:这里要运用大根堆还是小根堆？
显然，鸟向低处飞。那么可以考略使用**笛卡尔树**。通过其**二叉搜索树**的特性，通过**维护右链**来记录从每棵树起飞能经过的**最大树的数量**。这里可以运用数组等来记录，也可以使用 $ST$ 表等，在此不一一赘述了。

# Code

建立笛卡尔树的过程如下:
```
void build()//利用（手写）单调栈构建笛卡尔树 
{
	for(int i=1;i<=n;i++)
	{
		num=top;
		while(num&&a[stk[num]].val<a[i].val) num--;
		if(num) rc[stk[num]]=i;
		if(num<top) lc[i]=stk[num+1];
		stk[++num]=i;
		top=num;
	}
	return;
}
```

搜索的过程如下
```
int dfs(int rt)//寻找以每个点为根最多能经过的树的数量
{
	if(!lc[rt]&&!rc[rt]) return 0;//没有孩子，返回0 
	if(lc[rt]&&!rc[rt])//只有左孩子，向左递归求解 
	{
		int now=dfs(lc[rt])+1;
		if(a[lc[rt]].val==a[rt].val) now--;
		a[rt].pass=now;
		return now;
	}
	if(!lc[rt]&&rc[rt])//只有右孩子，向右递归求解 
	{
		int now=dfs(rc[rt])+1;
		if(a[rc[rt]].val==a[rt].val) now--;
		a[rt].pass=now;
		return now;
	}
	int nowlc=dfs(lc[rt])+1;
	int nowrc=dfs(rc[rt])+1;
	if(lc[rt]&&rc[rt])//既有左孩子，又有有孩子 
	{
		if(a[lc[rt]].val==a[rt].val) nowlc--;
		if(a[rc[rt]].val==a[rt].val) nowrc--;
		a[rt].pass=max(nowlc,nowrc);//数量需要取两者之间的较大值 
	}
	return max(max(nowlc,nowrc),a[rt].pass);
} 
```

结构体
```
struct node
{
	int val,pass;//val表示高度，pass表示从当前的位置开始飞最多能经过树的数量 
}a[N];
```

其余部分请大家自己补充完成哦

---

## 作者：Big_Dinosaur (赞：3)

这是模拟赛的 T1。~~我不会笛卡尔树却切了。~~

### 思路
首先考虑 $k=0$ 的做法。

若从 $i$ 可以直接飞到 $j$，连一条从 $i$ 到 $j$ 的有向边，长度为 $1$，则答案就是从 $1$ 出发的最长路。

但是当树高度依次递减时边为 $n^2$ 级别的，显然会炸。

接下来考虑减少边数目，考虑按结尾分析。看下图，分析 $5$ 号树为结尾的最长路（为方便，竖线就是树）：

![](https://cdn.luogu.com.cn/upload/image_hosting/39ygsmdk.png)

其中绿色表示可以直接到 $5$ 号，橙色表示不可以直接到 $5$ 号，可以发现：

- $5$ 号左侧，绿色竖线长度从右到左高度递增。
- $5$ 号右侧，绿色竖线长度从左到右高度递增。

其中，$1$ 号、$3$ 号、$4$ 号均可到达 $5$ 号，同时 $1$ 可以到 $3$ 号，$3$ 可以到 $4$ 号，$4$ 可以到 $5$ 号，此时最长路为 $1\to 3\to 4\to 5$。右边也类似，最长路为 $8\to6\to5$。

根据上图，只需将**两边**与其最近的可到达的点与其连边即可，其他的边无效。若无则不连，如 $8$ 号右侧。找点可以用单调栈。

进一步，可发现连成最长路无后效性，可以 DP。

若 $k$ 不为 $0$，怎么办？

首先，什么时候传送？当然是到路径终点。

接下来，在哪里传送？可传送到的点终飞行距离最大的。

但是，上面 DP 只求出 $1$ 为起点的答案，怎么办？用两种方法。

1. 对每个点都做一遍
2. 建高度为无穷大的“超级原点”，从“超级原点”开始 DP。

最大的问题来了：树很高，既不能暴力找，也不可以记录每个高度对应最大答案。没事，可以离散化就能记录，最后对于每个高度 $i$，记录答案为 $\max_{j=1}^ih_j$，$h_j$ 为高度为 $j$ 的最大答案。

最后将所有答案加起来就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
namespace IO {
	inline int r() {
		int x = 1, y = 0;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-')x = -1;ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			y = (y << 1) + (y << 3) + (ch ^ 48);ch = getchar();
		}
		return x * y;
	}
	inline void wi(int s) {
		if (s == 0)return ;
		if (s < 0) {putchar('-');s = -s;}
		wi(s / 10);putchar(s % 10 + 48);
	}
	inline void ww(int s) {
		if (s == 0)putchar(48);else wi(s);putchar(32);
	}
	inline void wln(int s) {
		if (s == 0)putchar(48);else wi(s);putchar(10);
	}
	inline void w(int s) {
		if (s == 0)putchar(48);else wi(s);
	}
}
using namespace IO;
namespace DINO{
	int n, k, a[355555], b[355555], t[999999];
	vector<int>v[355555];
	int dp[999999] , ma[999999];
	stack <int> st1, st2;
	inline void DP(int x) {
		if (v[x].size() == 0 || dp[x]) return;
		for(int j = 0; j < v[x].size(); ++ j){
			DP(v[x][j]);
			dp[x] = max(dp[x], dp[v[x][j]] + 1);
		}
		ma[a[x]] = max(ma[a[x]], dp[x]);
	}
	inline int f(int x) {
		int le = 1, rg = n + k, mid;
		while (le <= rg){
			mid = le + rg >> 1;
			if (t[mid] == x) return mid;
			if (t[mid] < x) le = mid + 1;
			else rg = mid - 1;
		}
		return 0;
	}
	inline void _() {
		n = r(), k = r();
		for (ri i = 1; i <= n; ++ i) a[i] = t[i] = r();
		for (ri i = 1; i <= k; ++ i) b[i] = t[i + n] = r();
		sort (t + 1, t + n + k + 1);
		for (ri i = 1; i <= n; ++ i) a[i] = f(a[i]);
		for (ri i = 1; i <= k; ++ i) b[i] = f(b[i]);
		a[n + 1] = n + k + 2;
		for (ri i = 1; i <= n + 1; ++ i) {
			while (!st1.empty() && a[st1.top()] <= a[i]) st1.pop();
			if (!st1.empty()) v[st1.top()].push_back(i);
			st1.push(i);
		}
		for (ri i = n + 1; i; -- i) {
			while (!st2.empty() && a[st2.top()] <= a[i]) st2.pop();
			if (!st2.empty()) v[st2.top()].push_back(i);
			st2.push(i);
		}
		DP(n + 1);
		for (ri i = 1; i <= n + k + 2; ++ i) ma[i] = max(ma[i], ma[i - 1]);
		int S = dp[1];
		for(ri i = 1; i <= k; ++ i) S += ma[b[i]];
		wln(S);
	}
}
signed main(){
	freopen("bird.in", "r", stdin);
	freopen("bird.out", "w", stdout);
	DINO :: _();
}
```

---

## 作者：LTTXiaochuan (赞：2)

**题目大意**：小鸟从第一棵树开始移动，只能移动到**严格小于**自己所处的树的高度的树上，且中途不能跨越更高的树；小鸟有 $k$ 张瞬移卡，只能依次使用，可以瞬移到高度小于等于瞬移卡权值的任意树上。求小鸟最多的飞行次数（不包括瞬移）。



首先，对于本题，有一项基本事实：**肯定是在飞不了的时候才使用瞬移卡**。因为瞬移卡的使用没有限制，如果还能继续飞，肯定是选择继续飞，再瞬移到想要瞬移的地方。于是，每一次使用瞬移卡，可以看做是一个单独的进程。只要对于每张瞬移卡单独求解即可。

继续思考，我们观察到：数据范围在 $10^5$ 量级，允许使用 $\log_2n$ 的算法。为了快速求解，显然应当预处理出在任意一棵树上，小鸟能飞的步数最多是多少，我们用 $g_i$ 表示。于是又想到：需要先求解出，**在任意一棵树上，小鸟能飞的范围是从哪里到哪里**，我们用 $lpos_i$ 和 $rpos_i$ 表示。

对于这个问题，显然等价于“奶牛挡奶牛”模型，只需用两次单调栈求解即可，复杂度为 $O(n)$。不清楚该问题的同志可以参考此题：[P2947 [USACO09MAR] Look Up S - 洛谷](https://www.luogu.com.cn/problem/P2947)

处理完以后考虑最低的那些树（严格来讲并不一定是最低的那些树，这只是充分条件，更准确的定义是：能飞的范围只有 $1$ 的树），显然它们的 $g_i=0$。于是我们想到：先处理那些更矮的树的 $g_i$，这样等到处理大的 $g_i$ 时，只需要从更矮的树中选择一个最大的 $g_i$ 再加 $1$ 即可。于是接下来考虑：**如何快速求解一个区间内的最大值**。

求解区间最大值可以使用 ST 表或线段树。笔者这里使用了线段树，主要是因为模拟赛时笔者不记得 ST 表怎么写了。建议读者使用 ST 表，常数更小，编程复杂度更低。

处理完 $g_i$ 以后，还需要考虑：**如何快速查找高度小于某个值的树中，飞行步数最大的树**。这里笔者采用了一种看起来很“笨”的方法：先预处理出小于等于某个高度的树中飞行步数的最大值（当然，此处不能求解 $1$ 到 $10^9$ 中所有的高度，只需要求解数据中的高度即可），再对其二分查找。读者如果有更好的办法，可以自行解决。

到此，我们就完成了对本题的分析。

希望本题解能对您有所帮助。

示例代码（模拟赛时）：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=3e5+10;

typedef pair<int,int> PII;

struct node{
    int h,id;
}a[N];

int n,k;
int h[N],c[N];
int lpos[N],rpos[N];
int g[N]; //某个点最远能飞几步

struct STEP{
    int h,val;
}step[N];
int idx;

stack<PII> st;

bool cmp(node x,node y){ return x.h<y.h; }

//============================================

int tree[N<<2];
int tag[N<<2];

int ls(int p){ return p*2; }
int rs(int p){ return p*2+1; }

void push_up(int p){ tree[p]=max(tree[ls(p)],tree[rs(p)]); }

void addtag(int p,int pl,int pr,int d)
{
    tag[p]+=d;
    tree[p]+=d*(pr-pl+1);
}

void push_down(int p,int pl,int pr)
{
    if(tag[p])
    {
        int mid=(pl+pr)>>1;
        addtag(ls(p),pl,mid,tag[p]);
        addtag(rs(p),mid+1,pr,tag[p]);
        tag[p]=0;
    }
}

void update(int L,int R,int p,int pl,int pr,int d)
{
    if(L<=pl && pr<=R)
    {
        addtag(p,pl,pr,d);
        return;
    }
    push_down(p,pl,pr);
    int mid=(pl+pr)>>1;
    if(L<=mid) update(L,R,ls(p),pl,mid,d);
    if(R>mid) update(L,R,rs(p),mid+1,pr,d);
    push_up(p);
}

int query(int L,int R,int p,int pl,int pr)
{
    if(L<=pl && pr<=R) return tree[p];
    push_down(p,pl,pr);
    int mid=(pl+pr)>>1,res=0;
    if(L<=mid) res=max(res,query(L,R,ls(p),pl,mid));
    if(R>mid) res=max(res,query(L,R,rs(p),mid+1,pr));
    return res;
}

//============================================

void getmax(int id)
{
    g[id]=query(lpos[id]+1,rpos[id]-1,1,1,n)+1;
    update(id,id,1,1,n,g[id]);
}

void pre()
{
    int maxg=0,lasth=a[1].h;
    for(int i=1; i<=n; i++)
    {
        if(a[i].h!=lasth)
        {
            idx++;
            step[idx].h=lasth;
            step[idx].val=maxg;
        }
        maxg=max(maxg,g[a[i].id]);
        lasth=a[i].h;
    }
    idx++;
    step[idx].h=lasth;
    step[idx].val=maxg;
}

int solve(int card)
{
    //二分找牌
    int L=1,R=idx,mid;
    while(L<R)
    {
        mid=(L+R+1)>>1;
        if(step[mid].h>card) R=mid-1;
        else L=mid;
    }
    return step[L].val;
}

signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    cin>>n>>k;
    for(int i=1; i<=n; i++)
    {
        cin>>h[i];
        a[i].h=h[i],a[i].id=i;
    }
    for(int i=1; i<=k; i++) cin>>c[i];
    sort(a+1,a+1+n,cmp);

    //第一步：用单调栈求出每个点的最大飞行范围 O(n)
    
    //左边最远
    for(int i=1; i<=n; i++)
    {
        while(!st.empty() && st.top().first<h[i]) st.pop();
        if(!st.empty()) lpos[i]=st.top().second;
        st.push({h[i],i});
    }

    while(!st.empty()) st.pop(); //清空
    
    //右边最远
    for(int i=n; i>=1; i--)
    {
        while(!st.empty() && st.top().first<h[i]) st.pop();
        if(!st.empty()) rpos[i]=st.top().second;
        else rpos[i]=n+1; //不存在
        st.push({h[i],i});
    }


    //第二步：从小到大对于每个点
    //求出该点飞行范围内的能飞到的拥有最大距离的点
    //即求飞行区间内最大值，用线段树
    for(int i=1; i<=n; i++) getmax(a[i].id);
    for(int i=1; i<=n; i++) g[i]--;


    //第三步：直接处理出小于等于某个编号的最大值
    pre();

    //第四步：查找编号小于牌值的最大值
    int ans=0;
    for(int i=1; i<=k; i++) ans+=solve(c[i]);
    cout<<ans+g[1]<<"\n";

    //测试代码：
    // for(int i=1; i<=n; i++) cout<<g[i]<<" ";
    // cout<<"\n\n";
    // for(int i=1; i<=n; i++) cout<<step[i].h<<" "<<step[i].val<<"\n";

    return 0;
}
/*
11 4
1 3 4 5 1 4 2 6 9 8 3
4 100000 3 8
ANS:12

5 2
6 6 6 6 6
10 15
ANS:0

5 2
5 4 3 2 1
4 3
ANS:9
*/
```

---

## 作者：DrDuck (赞：2)

# 基本思路：笛卡尔树 #
为什么会想到用笛卡尔树？

首先，我们发现鸟一次只能往更低的地方飞，这一点是不是和堆的性质很像？

其次，笛卡尔树满足二叉搜索树的性质，这一点有利于我们去统计答案。

由于鸟只能往低处飞，考虑建立大根堆。我这里为了方便计数，当出现多个相等的最值时，统一选了最右边的作为堆顶。也就是将：

```cpp
while (cnt && a[s[cnt]] < a[i])
```
改为：

```cpp
while (cnt && a[s[cnt]] <= a[i])
```
好了，现在我们树建好了，拿第二个样例来说，大概长这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/wcjh1drn.png) 
其实不难发现，小鸟从一个节点出发，能飞的最大次数其实就是这棵笛卡尔树（去掉堆顶）的深度。可以利用 DFS 求得每个节点的深度。

当然还有考虑些特殊情况，如果往下过程中遇到了高度相同的树怎么办？比如这个样例：

```cpp
8 9
6 0 0 3 7 0 7 8 
7 8 0 0 5 8 2 7 0
```
如果从高度为 $8$ 的树飞到第二个高度为 $7$ 的树，再飞到第一个高度为 $7$ 的树显然是不符合要求的，鸟不能飞到与自身所在树高度相同的节点。所以在 DFS 的过程中遇到高度相同的节点，不要统计这个点的深度。

最后就是查询了。直接瞬移到高度最高的点得到的深度不一定是最优的，我们要在经过排序的树中，在区间 $[1,pos]$ 内选择一个深度最深的子树，其中 $pos$ 是最后一棵能瞬移到的树。典型的区间最值查询问题。可以用 st 表解决。对每棵树进行排序，用 st 表记录区间深度最值，查询是先二分找到最后一个能瞬移到的树的位置（在 st 表中的），查询即可。
# CODE #

```cpp
#include<bits/stdc++.h>
//#define int long long
#define noodles main
using namespace std;
const int maxn = 3e+5 + 5;
int n = 0, k = 0, tot = 0, ans = 0, mx = 0, b = 0, root = 0;
int a[maxn], s[maxn], l[maxn], r[maxn], f[maxn][35];
vector<int> rt;
class tree
{
public:
	int h, dep;
	friend bool operator < (const tree &x, const tree &y)
	{
		return x.h < y.h;
	}
};
tree t[maxn];
inline int read()
{
	register int x=0,f=0;register char c=getchar();
	while(c<'0'||c>'9')f=(c=='-'),c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?-x:x;
}
int dfs(int pos)
{
	if (!l[pos] && !r[pos])
	{
		return 0;
	}
	if (!l[pos])
	{
		int ret = dfs(r[pos]) + 1;
		if (a[pos] == a[r[pos]])
		{
			ret--;
		}
		return t[pos].dep = max(ret, t[pos].dep);
	}
	if (!r[pos])
	{
		int ret = dfs(l[pos]) + 1;
		if (a[pos] == a[l[pos]])
		{
			ret--;
		}
		return t[pos].dep = max(ret, t[pos].dep);
	}
	int reta = dfs(l[pos]) + 1;
	if (a[pos] == a[l[pos]])
	{
		reta--;
	}
	int retb = dfs(r[pos]) + 1;
	if (a[pos] == a[r[pos]])
	{
		retb--;
	}
	return t[pos].dep = max(max(reta, retb), t[pos].dep);;
}
void st()
{
	for (int j = 1; (1 << j) <= n; j++)
	{
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
		{
			f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
	}
}
int query(int x, int y)
{
	int d = log2(y - x + 1);
	return max(f[x][d], f[y - (1 << d) + 1][d]);
}
signed noodles()
{
	n = read();
	k = read();
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
		t[i].h = a[i];
		if (a[i] >= mx)
		{
			mx = a[i];
			root = i;
		}
		int cnt = tot;
		while (cnt && a[s[cnt]] <= a[i])
		{
			cnt--;
		}
		if (cnt)
		{
			r[s[cnt]] = i;
		}
		if (cnt < tot)
		{
			l[i] = s[cnt + 1];
		}
		s[++cnt] = i;
		tot = cnt;
	}
	dfs(root);
	ans = t[1].dep;
	sort(t + 1, t + n + 1);
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = t[i].dep;
	}
	st();
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= k; i++)
	{
		b = read();
		int pos = 0;
		int x = 1;
		int y = n;
		while (x <= y)
		{
			int mid = (x + y) / 2;
			if (a[mid] <= b)
			{
				x = mid + 1;
				pos = mid;
			}
			else
			{
				y = mid - 1;
			}
		}
		ans += query(1, pos);
	}
	printf("%d", ans);
	return 0;
}
```
拒绝抄袭！

---

## 作者：Nygglatho (赞：2)

一个大常数的不用笛卡尔树的做法。

显然，离散化不影响答案，所以先将 $a,b$ 离散化。

先考虑没有瞬移的情况。

令 $l_i$ 表示最小的 $w$，使得 $\forall w\le j<i,a_j<a_i$，$r_i$ 表示最大的 $w$，使得 $\forall i<j
\le w,a_j<a_i$。这可以使用单调栈解决。

令 $f_i$ 表示从 $i$ 开始跳，**不使用瞬移**，最大能飞行的次数。

则由于有往左边飞和往右边飞两种方案，所以 $f_i=\max(\max\limits_{j=l_i}^{i-1}f_j,\max\limits_{j=i+1}^{r_i}f_j)$。

按 $a_i$ 从小到大更新 $f_i$，由于对于 $i$，只能飞到 $i$ 旁边比 $i$ 小的点，所以这样可以保证对于旁边能飞到的点都已经被更新。

使用线段树优化，时间复杂度为 $O(n\log n)$。

对于瞬移，显然可以贪心地瞬移到 $f_i$ 尽量大的点，以保证飞行的次数尽量多。

具体的，对于第 $j$ 次瞬移，需要瞬移到满足 $a_i<b_j$ 且 $f_i$ 尽量大的 $i$ 点。

这个在离散化之后就很好维护了，时间复杂度 $O(n+k)$。

注意答案最后需要加上 $f_1$，因为为了保证最优，需要到不能继续飞之后再使用瞬移。

```cpp
#include "bits/stdc++.h"
#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define F(i,x,y) for (int i = (x); i <= (y); ++ i)
#define D(i,x,y) for (int i = (x); i >= (y); -- i)
#define OPEN freopen ("bird.in", "r", stdin); freopen ("bird.out", "w", stdout);
#define ll long long
#define ul unsigned long long
using namespace std;

const ll mod = 1ll * 1e9 + 7ll;
//const ll mod = 998244353ll;
// bool st;
int a[300010];

int b[300010];

int _mx[300010];

int l[300010], r[300010];

int n, k;

stack<int> s;

struct ropz {
	int id; int a;
	bool operator <(const ropz& zsc) const {
		return a < zsc.a;
	}
}op[300010];

namespace Seg {
	int d[1200012];
	void Update(int l, int r, int x, int p, int v) {
		if (l == r) {d[p] = v; return ;}
		int m = (l + r) >> 1;
		if (x <= m) Update(l, m, x, p << 1, v);
		else Update(m + 1, r, x, p << 1 | 1, v);
		d[p] = max(d[p * 2], d[p * 2 + 1]);
	}
	
	int Query(int l, int r, int s, int t, int p) {
//		cerr << l << ' ' << r << ' ' << s << ' ' << t << ' ' << p << ' ' << d[p] << '\n';
		if (l <= s && t <= r) {
			return d[p];
		}
		int m = (s + t) >> 1;
		int res = 0;
		if (l <= m) res = Query(l, r, s, m, p << 1);
		if (m < r) res = max(res, Query(l, r, m + 1, t, p << 1 | 1));
		return res;
	}
}

namespace Hsh {
	int qwq[600010];
	int cnt;
	unordered_map<int, int> mp;
	void Init() {
		F(i, 1, n) qwq[++ cnt] = a[i];
		F(i, 1, k) qwq[++ cnt] = b[i];
		sort (qwq + 1, qwq + cnt + 1);
		
		F(i, 1, cnt)
			if (! mp[qwq[i]]) mp[qwq[i]] = i;
	}
	
	void Start () {
		F(i, 1, n) a[i] = mp[a[i]];
		F(i, 1, k) b[i] = mp[b[i]];
	}
}

int w[600010];

// bool ed;

using namespace Seg;
int main() {
//	OPEN
	IOS
// 	cerr << (&st - &ed) / 1024.0 / 1024.0 << '\n';
	cin >> n >> k;
	
	F(i, 1, n) cin >> a[i];
	
	F(i, 1, k) cin >> b[i];
	
	Hsh::Init();
	Hsh::Start();
	
//	F(i, 1, n) cerr << a[i] << ' '; cerr << '\n'; F(i, 1, k) cerr << b[i] << ' '; cerr << '\n';
	
	F(i, 1, n) {
		while (!s.empty() && a[s.top()] < a[i]) s.pop();
		if (!s.empty()) l[i] = s.top();
		s.push(i);
	}
	while (!s.empty()) s.pop();
	
	D(i, n, 1) {
		while (!s.empty() && a[s.top()] < a[i]) s.pop();
		if (!s.empty()) r[i] = s.top();
		else r[i] = n + 1;
		s.push(i);
	}
	
	F(i, 1, n) ++ l[i], -- r[i];
//	F(i, 1, n) cerr << l[i] << ' ' << r[i] << '\n';
	F(i, 1, n) op[i] = {i, a[i]};
	
	sort(op + 1, op + n + 1);
//	F(i, 1, n) cerr << op[i].a << ' ' << op[i].id << '\n';
	F(i, 1, n) {
		int now = op[i].id;
		if (l[now] == now && r[now] == now) continue;
		if (l[now] == now) _mx[now] = Query(now + 1, r[now], 1, n, 1) + 1;
		else if (r[now] == now) _mx[now] = Query(l[now], now - 1, 1, n, 1) + 1;
		else _mx[now] = max(Query(l[now], now - 1, 1, n, 1), Query(now + 1, r[now], 1, n, 1)) + 1;
//		cerr << Query(l[now], now - 1, 1, n, 1) << ' ' << Query(now + 1, r[now], 1, n, 1) << '\n';
//		cerr << max(Query(l[now], now - 1, 1, n, 1), Query(now + 1, r[now], 1, n, 1)) << '\n';
		Update(1, n, now, 1, _mx[now]);
	}
	
	ll ans = 0ll;
	
	F(i, 1, n) w[a[i]] = max(_mx[i], w[a[i]]);
	
	F(i, 1, n + k) w[i] = max(w[i], w[i - 1]);
	
//	F(i, 1, n + k) cerr << w[i] << ' '; cerr << '\n';
	ans = _mx[1];
	
	F(i, 1, k) ans += w[b[i]];
	
	cout << ans << '\n';
	
//	F(i, 1, n) cerr << _mx[i] << ' '; cerr << '\n';
}
```

---

