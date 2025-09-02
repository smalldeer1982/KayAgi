# [ABC017C] ハイスコア

## 题目描述

### 题意 

高桥君非常喜欢打电动。

现在他在玩的这个游戏中有 $N$ 个遗迹，你可以按照你喜欢的顺序去探索这些遗迹（不一定都要探索）。在探索遗迹的过程中会获得宝石，游戏中一共有 $M$ 种宝石。

当你探索过第 $i(1\le i \le N)$ 个遗迹后，你的得分将增加 $s_i$，同时，你将得到所有种类编号在 $l_i$ 到 $r_i$ 之间的宝石各一个，但是再一次探索同一个遗迹的话，你将什么都无法得到。

获得的宝石无法被丢弃，当所有种类的宝石都获得之后，会复活魔王导致得分清零且不再能得分。

高桥君想要得到尽可能高的分数，请求出在不复活魔王的情况下，可以得到的分数最高能是多少。

## 说明/提示

- $1\le N \le 10^5$
- $1\le M \le 10^5$
- $1\le l_i,r_i \le M$
- $1\le s_i \le 5\times 10^3$
- 所有读入的数值都是整数。

---

## 样例 #1

### 输入

```
4 6
1 3 30
2 3 40
3 6 25
6 6 10```

### 输出

```
80```

## 样例 #2

### 输入

```
2 7
1 3 90
5 7 90```

### 输出

```
180```

## 样例 #3

### 输入

```
1 4
1 4 70```

### 输出

```
0```

# 题解

## 作者：Walter_Fang (赞：5)

### 大致题意

有 $n$ 个遗迹，可以按照任意顺序探索这些遗迹，允许不探索全部。

探索时会获得宝石，一共有 $m$ 种宝石。

探索过第i个遗迹后，得分将增加 $s_i$，同时，将得到所有种类编号在 $l_i$ 到 $r_i$ 之间的宝石各一个，但是重复探索同一遗迹，将什么都得不到。

获得的宝石无法丢弃，当获得所有种类的宝石后，会清空得分且不能再得分。

求出在不清空得分的情况下，可得到的最高分数。

### 解析/思路

注意到 $1\le s_i \le 5\times 10^3$，即得分均为正，因此贪心，令探索到的遗迹数量尽可能多，且得到的宝石种类尽可能少。

继续思考，得到的宝石种类要尽可能少，那在最优情况下我们肯定要得到 $m-1$ 种宝石。设这个不希望得到的宝石为第 $i$ 种，则我们不应该探索可以得到宝石 $i$ 的遗迹，即在去探索所有遗迹的得分中减去所有会得到第 $i$ 种宝石的遗迹的得分，得出的数即为答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,i,mi=INT_MAX,s,tmp,a[N],x[N],y[N],f[N];
int main(){
	cin>>n>>m;
	for(i=1;i<=n;i++)cin>>x[i]>>y[i]>>f[i];
	for(i=1;i<=n;i++)a[x[i]]+=f[i],a[y[i]+1]-=f[i],s+=f[i];
	for(i=1;i<=m;i++)tmp+=a[i],mi=min(mi,tmp);
	cout<<s-mi<<'\n';
}
```

---

## 作者：fengenrong (赞：2)

### 题意
有 $N$ 个遗迹，$M$ 个宝石。当探索到第 $i$ 个遗迹，可以获得 $l_i$ 到 $r_i$ 的所有宝石，加上 $s_i$ 的得分。但当 $M$ 个宝石都被探索后，得分将会清零。

### 思路

考虑贪心，我们只用留下任意一个宝石即可。

其实，我们第 $i$ 次只用将区间 $[1,l_{i}-1]$ 的宝石加上 $s_i$ 的得分，和将区间 $[r_{i}+1,M]$ 的宝石也加上 $s_i$ 的得分。但是，这样会超时。

所以，我们可以使用差分数组来优化（线段树也可以）。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m;
int cf[100005],QZ;
int ans;
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1,l,r,s;i<=n;i++){
        scanf("%lld%lld%lld",&l,&r,&s);
        cf[1]+=s,cf[l]-=s,cf[r+1]+=s;//差分
    }
    for(int i=1;i<=m;i++){
        QZ+=cf[i];//第i个宝石保留所获得的得分
        ans=max(ans,QZ);//求最大值
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：coding_goat (赞：2)

# 原题链接

还能交得上去，来一发。

[洛谷](https://www.luogu.com.cn/problem/AT_abc017_3)

[AT](https://atcoder.jp/contests/abc017/tasks/abc017_3)

# 1.思路

看到所有的分数为正，立马想到贪心。只要枚举每一个宝石，计算少了这颗宝石后会亏多少，亏的最少的就是我们选择的宝石。拿总分数减去最少亏的分数就可以得到答案啦。

为了统计每个点有多少的分数加成，可以立马想到区间修改，单点查询。毕竟这里只查一次，故用差分即可。（当然用树状数组也不是不可以。）

# 2.代码

差分解法：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
template <typename T>inline void read(T &xx){
	xx=0;int f=1;
    char c = getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        xx = (xx<<1)+(xx<<3)+(c^48);
        c = getchar();
    }
    xx*=f;
}
#define maxn 100010
int n,m,cost[maxn],tot,l,r,s,minn=1e9;
int main(){
	read(n),read(m);
	for(int i=1;i<=n;i++){
		read(l),read(r),read(s);
		cost[l]+=s,cost[r+1]-=s;
		tot+=s;
	}
	for(int i=1;i<=m;i++) cost[i]+=cost[i-1];
	for(int i=1;i<=m;i++) minn=min(minn,cost[i]);
	cout<<tot-minn<<'\n';
	return 0;
}
```

树状数组解法（推销一下：[我的树状数组学习笔记](https://www.luogu.com.cn/blog/codingfatguyHZH233/Study-Note-Binary-Index-Tree)）

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
template <typename T>inline void read(T &xx){
	xx=0;int f=1;
    char c = getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        xx = (xx<<1)+(xx<<3)+(c^48);
        c = getchar();
    }
    xx*=f;
}
#define maxn 100010
#define int ll
int n,m,tree1[maxn],tree2[maxn],tot,l,r,s,minn=1e18;
int lowbit(int x){
    return x&(-x);
}
int getans(int tree[],int x){
    int res=0;
    while(x>0){
        res+=tree[x];
        x-=lowbit(x);
    }
    return res;
}
void update(int tree[],int x,int k){
    while(x<maxn){
        tree[x]+=k;
        x+=lowbit(x);
    }
}
void add(int l,int r,int k){
    update(tree1,l,k),update(tree1,r+1,-k);
    update(tree2,l,(l*k)),update(tree2,r+1,(r+1)*(-k));
}
int query(int l,int r){
    return (r+1)*getans(tree1,r)-l*getans(tree1,l-1)-(getans(tree2,r)-getans(tree2,l-1));
}
signed main(){
	read(n),read(m);
	for(int i=1;i<=n;i++){
		read(l),read(r),read(s);
		add(l,r,s);
		tot+=s;
	}
	for(int i=1;i<=m;i++) minn=min(minn,query(i,i));
	cout<<tot-minn<<'\n';
	return 0;
}
```

---

## 作者：scp020 (赞：2)

# [ABC017C] ハイスコア 题解

大水题，不评价。

前置芝士：差分，前缀和，不会的小朋友可以去学习。

## 解法

### 部分分解法（$30$ 个测试点）

考虑枚举 $n$ 个遗迹是否选取，判断这些遗迹是否覆盖了所有宝石，如果没有则最大化答案。

时间复杂度 $\mathcal{O}(n \times m \times 2^n)$。

### 部分分解法（$100$ 个测试点）

考虑优化枚举方法。

因为题中要求至少一个宝石不被选取，所以考虑固定这个不被选取的宝石（不管别的宝石是否被选取）。如果一个遗迹选了这个被固定的宝石则不选，否则选（要最大化答案）。

时间复杂度 $\mathcal{O}(n \times m)$。

### 满分解法

考虑继续优化上一个方法。

上一个解法的特点是不去考虑我们选的遗迹的贡献，而是总贡献减去没有被选的贡献。所以我们需要一种数据结构可以完成下面两种操作：

+ 区间加和。

+ 单点查询。

当然，可以完成这两种操作的数据结构有很多，比如线段树，树状数组，但是这道题中没有修改，所以我们可以选择差分和前缀和来完成这两种操作。

对于 $n$ 个遗迹，每个遗迹对应的宝石为 $l_i$ 和 $r_i$，我们将 $pre_{l_i}$ 加上 $s_i$，将 $pre_{r_i+1}$ 减去 $s_i$，最后算一遍前缀和，就可以达到将 $l_i$ 和 $r_i$ 之间所有数都加上 $s_i$ 的效果。最后枚举一遍不选取的宝石用总贡献减去选这个宝石的贡献然后取最大值即可。

时间复杂度 $\mathcal{O}(n + m)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Getchar() p1==p2 and (p2=(p1=Inf)+fread(Inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
char Inf[1<<21],*p1,*p2;
inline void read(int &x,char c=Getchar())
{
	bool f=c!='-';
	x=0;
	while(c<48 or c>57) c=Getchar(),f&=c!='-';
	while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
	x=f?x:-x;
}
int n,m,pre[100010],sum,mini=0x3f3f3f3f;
int main()
{
	read(n),read(m);
	for(int i=1,L,R,s;i<=n;i++) read(L),read(R),read(s),pre[L]+=s,pre[R+1]-=s,sum+=s;
	for(int i=1;i<=m;i++) pre[i]+=pre[i-1],mini=min(mini,pre[i]);
	cout<<sum-mini<<endl;// 千万别忘输出行末换行
	return 0;
}
```

---

## 作者：Trump__Biden (赞：2)

 Update on 2023.1.28：代码因复制疏忽，被好心人[@zhouchenqiao1](https://www.luogu.com.cn/user/705012)发现，现已改正，感谢！！！

### [传送门](https://www.luogu.com.cn/problem/AT_abc017_3)

~~这是一道十分简单的题。~~

我们只需要用一个数组将每次输入的左端点的值加上可以增加分数，右端点的右边一个点的值减去分数，再用一个变量存储如果将每个山洞都探一遍总共可以加多少分。

最后用一个数组，数组的值是该数组的前一个的值加上它这个点所对应的分数，最后求这里面这个数组中最小的值，它的贡献是最小的。运用贪心的思想，减去它之后所得的答案即是最优解。


#### 代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
int n,m,i,sum,minn,l[100010],r[100010],s[100010];
int dis[100010],minx[100010];
void input(){
	using namespace std;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i){
		scanf("%d%d%d",&l[i],&r[i],&s[i]);
	}
}
void out(){
	using namespace std;
	printf("%d\n",sum-minn);
}
void M(){
	using namespace std;
	input();
	for(i=1;i<=n;++i){
		dis[l[i]]+=s[i];
		dis[r[i]+1]-=s[i];
		sum+=s[i];
	}
	for(i=1;i<=m;++i){
		minx[i]=minx[i-1]+dis[i];
	}
	for(i=1;i<=m;++i){
		minn=min(minx[i],minn);
	}
	out();
}
int main(){
	using namespace std;
	minn=0x3f3f3f3f;
	M();
	return 0;
}
```


不要忘记换行，~~因为这个卡了我 5 min。~~

---

## 作者：RyanLeander (赞：1)

**回到原题の传送门：**[我是原题](https://www.luogu.com.cn/problem/AT_abc017_3)
------------
# **贪心 + 差分**

仔细思考一下，会发现如果我们要让得分最高，探索的洞穴要尽可能得多，因此，最优获得 $m-1$ 个宝石。

**Q**：那么剩下一颗不要了的宝石咋求？

**A**：差分前缀和！

因为最后才输出，我们可以开开心心地打个差分（线段树也可以，但常数时间修改区间岂不更香？），差分用来记录不取某个宝石的损失。我们记它的损失为，可以取到它的所有遗迹的 $s$ 值之和。

总而言之，我们每输入一个遗迹，就将区间 $[l_i, r_i]$ 的值增加 $s_i$ ，之后将计损失的数组遍历一遍，找到最小损失，计最小损失为 $w$ ，则输出便是 $\sum^{n}_{i=1}s_i-w$。

# 上！代！码！
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int d[N],n,m,tot,ans=114514191;
int main(){
    scanf("%d%d",&n,&m);
    while(n--){
        int l,r,s;
        scanf("%d%d%d",&l,&r,&s);
        tot+=s;
        d[l]+=s,d[r+1]-=s;
    }
    for(int i=1;i<=m;i++){
        d[i]+=d[i-1];
        ans=min(ans,d[i]);
    }
    printf("%d\n",tot-ans);
    return 0;
}
```


---

## 作者：QCurium (赞：1)

[原题链接](https://www.luogu.com.cn/problem/AT_abc017_3)

[视频讲解（顺便点个赞吧](https://www.bilibili.com/video/BV1ym4y1G72W/?vd_source=a8f2ca9bd086cb49d933fb93cb7409c0)

## 题意

给你一个长度为 $m$ 的区间，再给你 $n$ 个长度小于等于 $m$ 的区间，第 $i$ 个区间价值为 $s_i$，求不完全覆盖长度为 $m$ 的区间，最大价值是多少？

## 题目分析

我们想要价值最大，肯定是当覆盖的区间长度为 $m-1$ 时，价值最大，所以我们枚举每一个不选的区间，用总价值减去**最小的包含这个不选区间的区间价值**就是答案了。

根据我们翻译的题意，我们可以马上想到**线段树**，所以我就用线段树实现了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,sm=0,mn=1e12;
struct node{
	int l,r;
	int sum,tag;
}a[N<<2];
void push_down(int aa){
	if(a[aa].tag){
		a[aa*2].sum+=(a[aa*2].r-a[aa*2].l+1)*a[aa].tag;
		a[aa*2+1].sum+=(a[aa*2+1].r-a[aa*2+1].l+1)*a[aa].tag;
		a[aa*2].tag+=a[aa].tag;
		a[aa*2+1].tag+=a[aa].tag;
		a[aa].tag=0;
	}
	return ;
}
void build(int aa,int l,int r){
	a[aa].l=l;
	a[aa].r=r;
	a[aa].tag=a[aa].sum=0;
	if(l==r)
		return ;
	int mid=(l+r)>>1;
	build(aa*2,l,mid);
	build(aa*2+1,mid+1,r);
	return ;
}
void modify(int aa,int l,int r,int z){
	if(a[aa].l>=l&&a[aa].r<=r){
		a[aa].sum+=(a[aa].r-a[aa].l+1)*z;
		a[aa].tag+=z;
		return ;
	}
	push_down(aa);
	int mid=(a[aa].l+a[aa].r)>>1;
	if(l<=mid)
		modify(aa*2,l,r,z);
	if(r>mid)
		modify(aa*2+1,l,r,z);
}
int query(int aa,int lr){
	if(a[aa].l==a[aa].r&&a[aa].l==lr)
		return a[aa].sum;
	push_down(aa);
	int mid=(a[aa].l+a[aa].r)>>1;
	if(lr<=mid)
		return query(aa*2,lr);
	else
		return query(aa*2+1,lr);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>n>>m;
	build(1,1,m);
	for(int i=1;i<=n;i++){
		int ll,rr,ss;
		cin>>ll>>rr>>ss;
		sm+=ss;
		modify(1,ll,rr,ss);
	} 
	for(int i=1;i<=m;i++)
		mn=min(mn,query(1,i));
	cout<<sm-mn<<'\n';
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/126152142)

---

## 作者：Buried_Dream (赞：1)

值域很小只有 $10^5$。

如果想让至少一个地方没有被线段覆盖，不选这个地方就行了。

那该选哪个位置没有被覆盖，当然是贡献最小的了。

所以做法很明显了：

先差分一下，然后做一遍前缀和，从前往后扫一遍，找一个值最小的位置。

最后的答案就是总和减去最小值。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;

#define int ll
typedef long long ll;
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;

inline int read() {
    int res = 0, f = 0; char ch = getchar();
    for(; !isdigit(ch); ch = getchar()) f |= (ch == '-');
    for(; isdigit(ch); ch = getchar()) res = (res << 1) + (res << 3) + (ch - '0');
    return f ? - res : res;
}

ll diff[N], qzh[N], Sum;

signed main() {
	int n = read(), M = read();	
	for(int i = 1; i <= n; i++) {
		int l = read(), r = read(), val = read();
		diff[l] += val, diff[r + 1] -= val;
		Sum += val;
	}
	ll Min = LONG_LONG_MAX;
	for(int i = 1; i <= M; i++) qzh[i] = qzh[i - 1] + diff[i];
	for(int i = 1; i <= M; i++) {
		Min = std::min(Min, qzh[i]);
	}
	cout << Sum - Min << "\n";
	return 0;
}


---

## 作者：_AyachiNene (赞：0)

# 思路：
我们把一段宝石区间看做一条线段，我们想在不完全覆盖区间的情况下拿到最大的价值，那么肯定是不选一段价值最小的区间其他的全拿是最优的。我们可以用线段树或树状数组等数据结构来维护每一段区间的价值和。
# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls root*2
#define rs root*2+1
int n,m,ans=INT_MAX,sum;
struct node
{
	int l,r,val,f; 
}t[114514*4];
//以下为线段树
void bld(int l,int r,int root)
{
    t[root].l=l;
    t[root].r=r;
    if(l==r)
        return;
    int mid=(l+r)/2;
    bld(l,mid,root*2);
    bld(mid+1,r,root*2+1);
    t[root].val=t[ls].val+t[rs].val;
}
void down(int root)
{
    t[ls].f+=t[root].f;
    t[rs].f+=t[root].f;
    t[ls].val=t[ls].val+(t[ls].r-t[ls].l+1)*t[root].f;
    t[rs].val=t[rs].val+(t[rs].r-t[rs].l+1)*t[root].f;
    t[root].f=0;
}
void add(int x,int y,int root,int k)
{
	if(x<=t[root].l&&y>=t[root].r)
	{
		t[root].val+=(t[root].r-t[root].l+1)*k;
		t[root].f+=k;
		return;
	}
	if(t[root].f)
		down(root);
    int mid=(t[root].l+t[root].r)/2;
	if(x<=mid)
		add(x,y,ls,k);
	if(y>mid)
		add(x,y,rs,k);
	t[root].val=t[ls].val+t[rs].val;
}
int query(int x,int y,int root)
{
    int ret=0;
    if(t[root].l>=x&&t[root].r<=y)
        return t[root].val;
    if(t[root].f)
        down(root);
    int mid=(t[root].l+t[root].r)/2;
    if(x<=mid)
        ret=ret+query(x,y,ls);
    if(y>mid)
        ret=ret+query(x,y,rs);
    return ret;
}
//以上为线段树
int main()
{
	cin>>n>>m;
	bld(1,m,1);     //按种类建树
	for(int i=1;i<=n;i++)
	{
		int l,r,s;
		cin>>l>>r>>s;
		sum+=s;
		add(l,r,1,s);      //维护价值
	}
	for(int i=1;i<=m;i++)
		ans=min(ans,query(i,i,1));   //找最小的一段
	cout<<sum-ans<<endl;
	return 0;
}
```


---

## 作者：未来姚班zyl (赞：0)

## 题目大意

有 $M$ 种宝石（编号 $1\sim M$）与 $N$ 个遗迹，每选择一个遗迹 $i$ 会获得一段区间 $[l_{i},r_{i}]$ 的宝石，并获得指定的得分 $s_{i}$（只能一次），最大化不集齐所有宝石的情况下的得分。

## 题目分析
这道题题解区里已经有很多的差分和前缀和做法了，这里假设我不会差分和前缀和（或者没想到），这道题还有别的做法吗？当然是有的。

先给出一个比较明了的思路。把所有宝石抽象成一个线段，宝石是线段上的点，那么遗迹其实就是区间覆盖了。假如我已经选好了若干个遗迹，最后总会剩下一些点不会被覆盖。

那么假定我已经选定了一个没被覆盖的点（为什么不选多个？因为选一个已经满足答案要求了，再多选就显得多余，而且多了限制），那么我肯定会把不包含这个点的区间全部选上，它们的权值之和就是答案。反过来，对于一段区间，只要我选的点不在这段区间上，那这个区间就一定能造成对应贡献。

这样的问题就可以用线段树解决了（~~不会差分怎么会线段树啊~~），对于一个遗迹 $i$，将它没有覆盖的区间加上 $s_{i}$，表示它能够造成贡献时被选择的点的范围，然后求单点最大值，即为答案。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r 
using namespace std;
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void write(ll x){if(x<0) putchar('-'),x=-x;if(x>9) write(x/10);putchar(x%10+48);}
const int N=1e5+5;
struct node{
	int w,laz;
}xd[N*4];
void getup(int x){
	xd[x].w=max(xd[L].w,xd[R].w);
} 
void pushdown(int x){
	int laz=xd[x].laz;
	xd[L].w+=laz,xd[R].w+=laz,xd[L].laz+=laz,xd[R].laz+=laz;
	xd[x].laz=0;
}
void modify(int x,int l,int r,int Ll,int Rr,int k){
	if(l>=Ll&&r<=Rr){xd[x].w+=k,xd[x].laz+=k;return;}
	pushdown(x);
	if(Rr<=mid)modify(lc,Ll,Rr,k);
	else if(Ll>mid)modify(rc,Ll,Rr,k);
	else modify(lc,Ll,Rr,k),modify(rc,Ll,Rr,k);
	getup(x);
}
int n,m;
int main(){
	n=read(),m=read();
	for(int i=1,l,r,k;i<=n;i++){
		l=read(),r=read(),k=read();
		if(l>1)modify(1,1,m,1,l-1,k);
		if(r<m)modify(1,1,m,r+1,m,k);
	}
	cout <<xd[1].w<<endl;
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

一个比较暴力的做法。

发现答案是包含其中一个点的不选，其他都选。于是可以维护一个点前缀和后缀能选的线段，最后求和。

稍微慢一点，时间复杂度 $O(n\log n)$，瓶颈在排序。

code：

```cpp
int n,m;
ll s[N],t[N];
struct node{
	int l,r,val;
}e[N];
inline bool cmp1(node x,node y){
	return x.r<y.r;
}
inline bool cmp2(node x,node y){
	return x.l<y.l;
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&e[i].l,&e[i].r,&e[i].val);
	}
	sort(e+1,e+n+1,cmp1);
	for(int i=1,j=0;i<=m;i++){
		s[i]=s[i-1];
		while(j<n&&e[j+1].r<i){
			s[i]+=e[++j].val;
		}
	}
	sort(e+1,e+n+1,cmp2);
	for(int i=m,j=n+1;i>=1;i--){
		t[i]=t[i+1];
		while(j>1&&e[j-1].l>i){
			t[i]+=e[--j].val;
		}
	}
	ll ans=0;
	for(int i=1;i<=m;i++){
		ans=max(ans,s[i]+t[i]);
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：TankYu (赞：0)

注意到得分都是正的，于是根据贪心，我们肯定要探索尽量多的遗迹。而题目中说不能集齐 $M$ 种宝石，那么可以想到应该尽可能减少 **未获得宝石的种类**。

因为只要不集齐就行，所以我们理论上最优就是只不获得 **某一种** 宝石。

那么如果想不获得某一种宝石，我们就应该不探索所有含这种宝石的遗迹。设不拿第 $i$ 种宝石的代价为 $d_i$，那么第 $k$ 个遗迹应该贡献 $\forall i \in[l_k,r_k],d_i \gets d_i + s_i$。

这个东西可以差分维护，然后我们初始假定全都能探索，则总分数为 $\sum\limits_{i = 1}^{n} s_i$。然后输出总分数减去最小的 $d$ 即可。

**注意输出一个换行**。

```cpp
#include <iostream>
using namespace std;

int d[100010];

int main()
{
	int n, m;
	cin >> n >> m;
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int l, r, s;
		cin >> l >> r >> s;
		ans += s;
		d[l] += s;
		d[r + 1] -= s;
	}
	int minn = ans;
	for (int i = 1; i <= m; i++)
	{
		d[i] += d[i - 1];
		minn = min(minn, d[i]);
	}
	cout << ans - minn << '\n';
	return 0;
}

```

---

## 作者：wdgm4 (赞：0)

本题运用的算法是差分和前缀和。

首先，我们需要求出如果每个遗迹都去了，每个宝石如果得到该宝石最多得到的分数，用暴力会超时，所以我们可以用差分，之后前缀和一下就可以求出来了。

我用表格画了个图，对应的是样例一的数据。

![](https://cdn.luogu.com.cn/upload/image_hosting/73gs9bgq.png?x-oss-process=image/resize,m_lfit,h_250,w_700)

之后需要用贪心思想，由于不能获得全部的宝石，那么我们可以去掉得分最少的宝石，即在总得分（去了所有遗迹的得分）中减去所有会得到该宝石的遗迹的得分，得出的数就是答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define XD 114514

using namespace std;
int n,m,a[100010],num=0x3f3f3f3f,sum;//记得num初始化成一个超大的数 
int l[100010],r[100010],s[100010];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&l[i],&r[i],&s[i]);
	}
	for(int i=1;i<=n;i++){//差分 
		a[l[i]]+=s[i];
		a[r[i]+1]-=s[i];
		sum+=s[i];//求出如果每个遗迹都去了的得分数 
	}
	int nem=0;
	for(int i=1;i<=m;i++){
		nem+=a[i];//前缀和 
		num=min(num,nem);//求出最小的 
	}
	cout<<sum-num<<endl;//AtCoder上的题记得最后换行 
	return 0;
}


```


---

