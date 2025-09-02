# Bank Hacking

## 题目描述

Although Inzane successfully found his beloved bone, Zane, his owner, has yet to return. To search for Zane, he would need a lot of money, of which he sadly has none. To deal with the problem, he has decided to hack the banks.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796C/2dce5999c2db79450d45fe87441c705c32509051.png)There are $ n $ banks, numbered from $ 1 $ to $ n $ . There are also $ n-1 $ wires connecting the banks. All banks are initially online. Each bank also has its initial strength: bank $ i $ has initial strength $ a_{i} $ .

Let us define some keywords before we proceed. Bank $ i $ and bank $ j $ are neighboring if and only if there exists a wire directly connecting them. Bank $ i $ and bank $ j $ are semi-neighboring if and only if there exists an online bank $ k $ such that bank $ i $ and bank $ k $ are neighboring and bank $ k $ and bank $ j $ are neighboring.

When a bank is hacked, it becomes offline (and no longer online), and other banks that are neighboring or semi-neighboring to it have their strengths increased by $ 1 $ .

To start his plan, Inzane will choose a bank to hack first. Indeed, the strength of such bank must not exceed the strength of his computer. After this, he will repeatedly choose some bank to hack next until all the banks are hacked, but he can continue to hack bank $ x $ if and only if all these conditions are met:

1. Bank $ x $ is online. That is, bank $ x $ is not hacked yet.
2. Bank $ x $ is neighboring to some offline bank.
3. The strength of bank $ x $ is less than or equal to the strength of Inzane's computer.

Determine the minimum strength of the computer Inzane needs to hack all the banks.

## 说明/提示

In the first sample, Inzane can hack all banks using a computer with strength $ 5 $ . Here is how:

- Initially, strengths of the banks are $ [1,2,3,4,5] $ .
- He hacks bank $ 5 $ , then strengths of the banks become $ [1,2,4,5,-] $ .
- He hacks bank $ 4 $ , then strengths of the banks become $ [1,3,5,-,-] $ .
- He hacks bank $ 3 $ , then strengths of the banks become $ [2,4,-,-,-] $ .
- He hacks bank $ 2 $ , then strengths of the banks become $ [3,-,-,-,-] $ .
- He completes his goal by hacking bank $ 1 $ .

In the second sample, Inzane can hack banks $ 4 $ , $ 2 $ , $ 3 $ , $ 1 $ , $ 5 $ , $ 7 $ , and $ 6 $ , in this order. This way, he can hack all banks using a computer with strength $ 93 $ .

## 样例 #1

### 输入

```
5
1 2 3 4 5
1 2
2 3
3 4
4 5
```

### 输出

```
5```

## 样例 #2

### 输入

```
7
38 -29 87 93 39 28 -55
1 2
2 5
3 2
2 4
1 7
7 6
```

### 输出

```
93```

## 样例 #3

### 输入

```
5
1 2 7 6 7
1 5
5 3
3 4
2 4
```

### 输出

```
8```

# 题解

## 作者：Zq_water (赞：2)

智商不够，暴力来凑。

正难则反，我们发现原题操作一次影响到的节点很多，可以反过来想，我们先给原树中的每一个权值 +2，这样原操作就转化为了，对根节点权值 -2，其儿子节点 -1，因为每个节点所直接连接的节点个数为线性级的，所以将每次操作放入线段树中暴力维护即可，时间复杂度 $O(n\log n)$。

Code:

```cpp
#include<bits/stdc++.h>
#define INF 2e18
#define endl '\n'
#define PI acos(-1)
#define pb push_back
#define fi first
#define se second
#define int long long
#define mem(x,v) memset(x,v,sizeof x)
using namespace std;
const int N = 3e5+5;

int n,ans,a[N];
struct Tree{int l,r,maxx;}t[N<<2];
vector <int> g[N];

#define ls (u<<1)
#define rs (u<<1|1) 
void pushup(int u){t[u].maxx=max(t[ls].maxx,t[rs].maxx);}
void build(int u,int l,int r){
	t[u].l=l,t[u].r=r;
	if(l==r){t[u].maxx=a[l];return;}
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(u);
}
void modify(int u,int pos,int k){
	if(t[u].l==t[u].r){
		t[u].maxx+=k;
		return;
	}
	int mid=t[u].l+t[u].r>>1;
	if(pos<=mid)modify(ls,pos,k);
	else modify(rs,pos,k);
	pushup(u);
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,ans=INF;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]+=2;
	build(1,1,n);
	for(int i=1,u,v;i<n;i++)cin>>u>>v,g[u].pb(v),g[v].pb(u);
	for(int i=1;i<=n;i++){
		modify(1,i,-2);
		for(int v:g[i])modify(1,v,-1);
		ans=min(ans,t[1].maxx);
		for(int v:g[i])modify(1,v,1);
		modify(1,i,2);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：2)

## 分析
我们把所有电脑中最高的强度定为first，把first-1定为second

把强度为first的电脑的个数定为fcnt，把强度为second的电脑的个数定为scnt

我们分析一下，不难发现有一下三种情况

1、答案为first

一、fcnt=1并且scnt=0

二、fcnt=1并且scnt不为0但是所有强度为second的电脑都与唯一强度为first的电脑直接相连

2、答案为first+1

一、fcnt=1并且scnt不为0并且所有强度为second的电脑不能与唯一强度为first的电脑直接相连

二、fcnt>1并且所有强度为first的电脑都与某一台电脑直接相连

3、答案为first+2

fcnt>1并且所有强度为first的电脑不都与某一台电脑直接相连

## 代码

``` cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int maxn=6e5+5;
ll a[maxn],head[maxn],tot=1;
struct asd{
	ll to,next;
}b[maxn];
void ad(ll aa,ll bb){
	b[tot].to=bb;
	b[tot].next=head[aa];
	head[aa]=tot++;
}
int main(){
	memset(head,-1,sizeof(head));
	ll n;
	scanf("%lld",&n);
	ll fir=-0x3f3f3f3f3f3f3f3f,sec;
	for(ll i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		fir=max(fir,a[i]);
	}
	for(ll i=1;i<n;i++){
		ll aa,bb;
		scanf("%lld%lld",&aa,&bb);
		ad(aa,bb);
		ad(bb,aa);
	}
	ll fcnt=0,scnt=0;
	for(ll i=1;i<=n;i++){
		if(fir-a[i]==1) scnt++;
		if(fir==a[i]) fcnt++;
	}
	sec=fir-1;
	ll jl=0;
	if(scnt){
		for(ll i=1;i<=n;i++){
			if(a[i]==fir){
				jl=i;
				break;
			}
		}
		for(ll i=head[jl];i!=-1;i=b[i].next){
			ll u=b[i].to;
			if(a[u]==sec){
				scnt--;
			}
		}
	}
	if(scnt==0 && fcnt==1){
		printf("%lld\n",fir);
		return 0;
	}
	else if(scnt!=0 && fcnt==1){
		printf("%lld\n",fir+1);
		return 0;
	}
	for(jl=1;jl<=n;jl++){
		ll js=0;
		if(a[jl]==fir) js++;
		for(ll i=head[jl];i!=-1;i=b[i].next){
			ll u=b[i].to;
			if(a[u]==fir){
				js++;
			}
		}
		if(fcnt==js){
			printf("%lld\n",fir+1);	
			return 0;
		}
	}
	printf("%lld\n",fir+2);	
	return 0;
}
```



---

## 作者：littleseven (赞：1)

## 题解：

**思维**

很卡人的思维题………………

首先根据题意，画画图，我们会发现答案仅有三种情况：

- $ans~=~val_{max}$
- $ans~=~val_{max} + 1$
- $ans~=~val_{max} + 2$

所以考虑一下下面的这些情况：

**NO.1**

![](https://i.loli.net/2019/10/21/eRE2NtgVx18qXBc.png)

**NO.2**

![](https://i.loli.net/2019/10/21/jOAGHx3I4X2mD9c.png)

**NO.3**

![](https://i.loli.net/2019/10/21/XrwD9vtu4bFQYp1.png)

我们会发现，对于这几种情况，他们共同的特点是：

- $val~=~val_{max}$的点只有一个

之后我们会找出在这种情况下的几种答案：

- 当不存在$val~=~val_{max}-1$的点的时候，答案一定是$ans~=~val_{max}$
- 当存在$val=val_{max}-1$的点时，如果所有$val~=~val_{max}-1$的点都是$val~=~val_{max}$的点的子节点，答案是$ans~=~val_{max}$，否则$ans~=~val_{max} + 1$

**NO.4**

![](https://i.loli.net/2019/10/21/Xn2OS5r98eYAwiQ.png)

**NO.5**

![](https://i.loli.net/2019/10/21/tFUm9rnGuC2xwDd.png)

再看这两种情况，我们会发现：

- 这时$val~=~val_{max}$的点不只有一个（$\ge2$）

之后我们可以得出在这种情况下的答案：

- 如果所有$val~=~val_{max}$的点都连在一个其他点上或者连在一个$val~=~val{max}$的点上，答案为$ans~=~val_{max}+1$
- 否则答案为$ans~=~val_{max}+ 2$

-----

那么我们最终整理一下这些情况：

- 当$val~=~val_{max}$的点只有一个的时候：
  1. 如果$val~=~val_{max}-1$的点不存在，$ans~=~val_{max}$
  2. 如果$val~=~val_{max}-1$的点存在，且这个点是$val~=~val_{max}$的那个点的子节点，$ans~=~val_{max}$
  3. 如果$val~=~val_{max}-1$的点存在，且这个点不是$val~=~val_{max}$的点的子节点，$ans~=~val_{max}+1$
- 当$val=val_{max}$的点有多个的时候：
  1. 如果所有$val~=~val_{max}$的点都是一个点的子节点，$ans~=~val_{max}+1$
  2. 如果一个$val~=~val_{max}$的点的子节点中包含所有其他$val~=~val_{max}$的点， $ans~=~val_{max}+1$
  3. 如果不满足以上两种情况，$ans~=~val_{max}+2$

最终按照这个模拟即可。注意细节和数据范围。

## AC代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define setI(x) freopen(x".in", "r", stdin);

#define setO(x) freopen(x".out", "w", stdout);

#define setIO(x) setI(x) setO(x)

typedef long long ll;

const int N = 300010;

const int inf = 0x3f3f3f3f;

int n;

ll val[N], mx;

int totmx, totse, tmp;

int tot, head[N], nxt[N << 1], to[N << 1];

void add(int x, int y) {
	to[ ++ tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
}

int main() {
	// setIO("tree");
	scanf("%d", &n);
	mx = -inf;
	for (int i = 1; i <= n; i ++ ) {
		scanf("%I64d", &val[i]);
		if (val[i] > mx) {
			mx = val[i];
			tmp = i;
		}
	}
	for (int i = 1; i <= n; i ++ ) {
		if (val[i] == mx) {
			totmx ++ ;
		}
		if (val[i] == mx - 1) {
			totse ++ ;
		}
	}
	for (int i = 1; i < n; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	if (totmx == 1) {
		if (totse == 0) {
			cout << mx << endl;
			return 0;
		}
		else {
			int now = 0;
			for (int i = head[tmp]; i; i = nxt[i]) {
				if (val[to[i]] == mx - 1) {
					now ++ ;
				}
			}
			if (now == totse) {
				cout << mx << endl;
				return 0;
			}
			else {
				cout << mx + 1 << endl;
				return 0;
			}
		}
	}
	if (totmx >= 2) {
		for (int i = 1; i <= n; i ++ ) {
			int cnt = 0;
			for (int j = head[i]; j; j = nxt[j]) {
				int now = to[j];
				if (val[now] == mx) {
					cnt ++ ;
				}
			}
			if (val[i] != mx && cnt == totmx) {
				cout << mx + 1 << endl;
				return 0;
			}
			if (val[i] == mx && cnt == totmx - 1) {
				cout << mx + 1 << endl;
				return 0;
			}
		}
	}
	cout << mx + 2 << endl;
	return 0;
}
```



---

## 作者：泠小毒 (赞：0)

# Bank Hacking
给定一棵带点权树，选出一个最佳的根节点，使得根节点的点权不变，它的儿子点权加1，其余点点权加2，并使最大点权最小，输出这个最小的最大点权
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190516/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190516.html)
## 解法
暴力的对每一个点扫它所有的儿子，然后check，设ans为原来的最大值，答案只可能是ans,ans+1,ans+2，复杂度是n+m
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int to,next;}e[600010];
int n,cnt=0,res,ans=-0x3f3f3f3f,flg,x,y,a[300010],head[300010];
map<int,int>mp;
void add(){e[++cnt]={y,head[x]},head[x]=cnt,e[++cnt]={x,head[y]},head[y]=cnt;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),mp[a[i]]++,ans=max(ans,a[i]);
	res=ans+2;
	for(int i=1;i<n;i++)scanf("%d%d",&x,&y),add();
	for(int i=1;i<=n;i++)
	{
		flg=0;
		for(int j=head[i];j;j=e[j].next){mp[a[e[j].to]]--;if(a[e[j].to]==ans)flg=1;}
		if(!mp[ans])res=ans+1;
		if(ans==a[i]&&mp[ans]==1)
		{
			if(mp[ans-1])res=ans+1;
			else if(flg)res=ans+1;
			else{res=ans;break;}
		}
		for(int j=head[i];j;j=e[j].next)mp[a[e[j].to]]++;
	}
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

~~这不是直接暴力就行了~~
### 题意
给定一棵带点权树，选出一个最佳的根节点，使得根节点的点权不变，它的儿子点权加1，其余点点权加2，并使最大点权最小，输出这个最小的最大点权
### 分析
考虑直接维护一棵单点加区间 $\max$ 的 sgt ，最开始将每个点权值 $+2$ 建树。

然后枚举根，只需将与根相连的所有点权值 $-1$ ，将根节点权值 $-2$ ，然后将答案与全局 $\max$ 取 $\min$ ，就做完了，求完当前答案记得撤回。

因为每条边只被遍历两次，树只有 $n-1$ 条边，所以复杂度 $O(n\log n)$ 可以过。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=3e5+5;
int n,ans=inf;
int a[maxn];
vector<int> tr[maxn];
inline int max(int x,int y){
	return x>y?x:y;
}
inline int min(int x,int y){
	return x<y?x:y;
}
struct Segment_Tree{//线段树 
	int maxv[maxn*4];
	inline void pushup(int o){
		maxv[o]=max(maxv[o*2],maxv[o*2+1]);
	}
	void build(int o,int l,int r){
		if(l==r){
			maxv[o]=a[l];
			return;
		}
		int m=(l+r)>>1;
		build(o*2,l,m);
		build(o*2+1,m+1,r);
		pushup(o);
	}
	inline void update(int o,int l,int r,int x,int k){
		if(l==r){
			maxv[o]+=k;
			return;
		}
		int m=(l+r)>>1;
		if(x<=m) update(o*2,l,m,x,k);
		else update(o*2+1,m+1,r,x,k);
		pushup(o);
	}
}seg;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read()+2;
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	seg.build(1,1,n);
	for(int i=1;i<=n;i++){
		for(int j=0;j<tr[i].size();j++){
			int v=tr[i][j];
			seg.update(1,1,n,v,-1);
		}
		seg.update(1,1,n,i,-2);
		ans=min(ans,seg.maxv[1]);
		for(int j=0;j<tr[i].size();j++){
			int v=tr[i][j];
			seg.update(1,1,n,v,1);
		}
		seg.update(1,1,n,i,2);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

