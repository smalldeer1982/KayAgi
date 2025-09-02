# [USACO15DEC] High Card Low Card P

## 题目描述

奶牛 Bessie 是卡牌游戏的狂热爱好者，这相当令人惊讶，因为她没有灵活的手指。不幸的是，牛群中的其他奶牛都不是好的对手。事实上，她们的表现非常糟糕，总是以完全可预测的方式出牌！尽管如此，对 Bessie 来说，如何获胜仍然是一个挑战。

Bessie 和她的朋友 Elsie 正在玩一个简单的卡牌游戏。她们拿一副 $2N$ 张牌，方便地编号为 $1 \ldots 2N$，并将其分成 $N$ 张牌给 Bessie 和 $N$ 张牌给 Elsie。然后，两人进行 $N$ 轮游戏，每轮 Bessie 和 Elsie 各打出一张牌。最初，打出更高牌的玩家得一分。然而，在游戏中的某个时刻，Bessie 可以决定改变规则，使得在接下来的游戏中，打出更低牌的玩家得一分。Bessie 可以选择不使用这个选项，让整个游戏保持在“高牌获胜”模式，或者她也可以立即启用这个选项，让整个游戏遵循“低牌获胜”的规则。

已知 Bessie 可以预测 Elsie 出牌的顺序，请确定 Bessie 可以获得的最大分数。

## 说明/提示

在这里，Bessie 手中的牌必须是 2、5、6 和 7，她最多可以利用这些牌赢得 3 分。例如，她可以先击败 1 这张牌，然后将规则切换为“低牌获胜”，之后她可以再赢得两轮。

## 样例 #1

### 输入

```
4
1
8
4
3```

### 输出

```
3```

# 题解

## 作者：yukuai26 (赞：24)

题目：https://www.luogu.org/problemnew/show/P3129

神奇的贪心，令f[i]表示前i个每次都出比对方稍微大一点的牌，最多能赢几次

g[i]表示从i-n中每次出比对方稍微小一点的牌，最多赢几次。

ans=max(f[i]+g[i+1]) 0<=i<=n

但是方案可能会重合。一般看到这儿就会放弃贪心去想别的算法。但是这是可行的

1：因为限制比原题目宽，所以ans>=真实的答案

2：对于重复取的数a，如果集合中有个没取的数<a,那么在用小的赢的时候可以代替a;

如果>a,那么在用大的赢时可以代替a

用set来记录最接近的数（其实可以用线段树2333）

```cpp
`#include<cstdio>  
#include<ctime>  
#include<iostream>  
#include<algorithm>  
#include<cstring>  
#include<set>
#define N 200005
using namespace std;  
set<int>q1,q2;  
int a[N],vis[N],n,ans,f[N],g[N];  
inline int read(){
    char c=getchar();int tot=1;while ((c<'0'|| c>'9')&&c!='-') c=getchar();if (c=='-'){tot=-1;c=getchar();}
    int sum=0;while (c>='0'&&c<='9'){sum=sum*10+c-'0';c=getchar();}return sum*tot;}
int main()
{  
    scanf("%d",&n);
        for (int i=1;i<=n;i++){
            a[i]=read();vis[a[i]]=1;
        }  
        for (int i=1;i<=n*2;i++){
            if (!vis[i]){
                q1.insert(i);
                q2.insert(-i);
            }
        }
    for(int i=1;i<=n;i++){  
        set<int>::iterator it=q1.lower_bound(a[i]);  
        if(it!=q1.end())
                q1.erase(it),f[i]=f[i-1]+1;  
        else f[i]=f[i-1];  
    }  
    for(int i=n;i>=1;i--)
        {  
        set<int>::iterator it=q2.lower_bound(-a[i]);  
        if(it!=q2.end())
                q2.erase(it),g[i]=g[i+1]+1;  
        else g[i]=g[i+1];  
    }
        ans=g[1];  
    for(int i=1;i<=n;i++){  
        ans=max(ans,f[i]+g[i+1]);  
    }  
    printf("%d",ans);  
}  `
```

---

## 作者：functionendless (赞：6)

这题乍一眼看去就会往贪心的方向想,而且很容易想到结论但却不知道它的正确性..

结论:

- 记录pre[]和suf[]分别表示在两种规则下,从前往后和从后往前数最大能赢的局数,这玩意显然贪心一下选离当前对手出牌最接近的能赢的数就可以了

- 然后ans=max(pre[i]+suf[i+1]) (0<=i<=n)


正确性:

- 这个策略的疑惑点就在于如果pre和suf中有一个数出现了两次怎么办

- 假设重复出现的那个数是x,那么一定有一个数y同时没有在两个数组中用到

- 当x > y时,pre[]中x用到的位置可以用y代替

- 当x < y时,显然也是同理的.

- 那么就证完了

下面是丑陋的代码:

```cpp
//by funtion
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<bitset>
#include<stack>
#include<cassert>
#define F first
#define S second
#define mp make_pair
#define pii pair<int,int>
#define pb push_back
#define mem(x,y) memset(x,y,sizeof x)
#define sqr(x) ((x)*(x))
using namespace std;
typedef long long ll;
typedef double db;
const int INF=1e9,N=50010 ;
const db eps=1e-8;
inline void read(int &x)
{
    x=0; int f=1; char ch=getchar();
    while( (ch<'0' || ch>'9') && ch!='-') ch=getchar(); if(ch=='-') {f=-1; ch=getchar();}
    while(ch>='0' && ch <='9') x=x*10+ch-'0',ch=getchar();
    x*=f;
}
inline void read(ll &x)
{
    x=0; int f=1; char ch=getchar();
    while( (ch<'0' || ch>'9') && ch!='-') ch=getchar(); if(ch=='-') {f=-1; ch=getchar();}
    while(ch>='0' && ch <='9') x=x*10+ch-'0',ch=getchar();
    x*=f;
}
//==========================head template==========================
int n,ans;
int tmp[N],b[N],pre[N],suf[N];
vector<int> a;
bool used[N<<1];
main()
{
    read(n); int cnt=0;
    for(int i=1;i<=n;i++) {read(b[i]); used[b[i]]=1;}
    for(int i=1;i<=(n<<1);i++) if(!used[i]) {a.pb(i); tmp[++cnt]=i; used[i]=0;}
    for(int i=1;i<=n;i++)
    {
        int pos=lower_bound(a.begin(),a.end(),b[i])-a.begin();
        if(pos>=a.size()) pre[i]=pre[i-1];
        else
        {
            pre[i]=pre[i-1]+1;
            a.erase(a.begin()+pos);
        }
    }
    while(a.size()) a.pop_back();
    for(int i=1;i<=n;i++) a.pb(tmp[i]);
    if(a.size()>n) while(1);
    for(int i=n;i>=1;i--)
    {
        int pos=upper_bound(a.begin(),a.end(),b[i])-a.begin()-1;
        if(pos<0 || pos>=a.size()) suf[i]=suf[i+1];
        else
        {
            suf[i]=suf[i+1]+1;
            a.erase(a.begin()+pos);
        }
    }
    for(int i=0;i<=n;i++)
        ans=max(ans,pre[i]+suf[i+1]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Avakos (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P3129)

首先前后一起做是困难的，考虑把前后拆开，对于每个前缀和后缀统计最大得分。将前缀答案数组设为 $f$，后缀答案数组设为 $g$。

因为前缀部分的得分需要更大的数而后缀部分的得分需要更小的数，所以把 Bessie 的手牌按编号从大到小排序一定不劣。我们将 Elsie 的手牌数组设为 $a$，Bessie 的手牌数组设为 $b$。显然 $b$ 数组严格单调递减。

然后以前缀为例，如果一个 $f_i$ 的值为 $x$，显然用 $b$ 数组的前 $x$ 个数得分一定最优。这启示我们~~考场人类智慧~~顺序枚举 $a$ 并维护一个数组 $c$。枚举到 $a$ 的第 $i$ 个数时，$c_j=\sum_{k=1}^{i}[a_k \le b_j]$。因为 $b$ 严格单调递减，所以维护 $c$ 相当于前缀加。

然后我们再推导~~人类智慧~~一下，发现 $f_i \ge k$的充要条件是 $\forall j \in [1,k]$，$c_j \ge k-j+1$。充分性是显然的，我们只需对于 $j=1 \sim k$ 都选第 $k-j+1$ 大的且比 $b_j$ 小的数即可得到一组合法方案。反证一下必要性，如果存在 $j$ 使 $c_j<k-j+1$，因为前 $k-j$ 个数已经匹配给后 $j+1 \sim k$个数，所以 $b_j$ 不能匹配，从而推出 $f_i<k$，矛盾。

判断这个条件可以把初始的 $c_i$ 设为 $-(n-i+1)$。这样 $f_i \ge k$ 就等价于枚举到 $i$ 时 $\min(c_1 \sim c_k)+n-k \ge 0$。因为可以匹配的数变多了最大得分不会变小，所以 $f$ 单调递增。这样直接维护一个当前 $f_i$ 的值设为
$now$，$i \gets i+1$ 时不断试图增加 $now$ 即可。用线段树维护 $c$，操作为区间加区间最小值。

计算 $g$ 时倒序枚举并做类似的操作即可。总时间复杂度 $O(n \log n)$。

code：

```
#include<bits/stdc++.h>
#define uint unsigned int
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define DU double
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define nep(i,x,n) for(int i=x;i>=n;i--)
using namespace std;
const int N=1e5+10;
int n,a[N],b[N],f[N],g[N],st[N];
struct segtree{
	int l,r,add,minx;
}tr[N*4];
inline void pushup(segtree &u,segtree l,segtree r){
	u.minx=min(l.minx,r.minx);
}
inline void pushdown(segtree &u,segtree &l,segtree &r){
	if(u.add){
		l.minx+=u.add;
		r.minx+=u.add;
		l.add+=u.add,r.add+=u.add;
		u.add=0;
	}
}
inline void build1(int u,int l,int r){
	tr[u].l=l,tr[u].r=r,tr[u].add=0;
	if(l==r){tr[u].minx=-(n-l+1);return ;}
	int mid=(l+r)>>1;
	build1(u<<1,l,mid),build1(u<<1|1,mid+1,r);
	pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}
//初始化用于处理 f 的数组 c 
inline void build2(int u,int l,int r){
	tr[u].l=l,tr[u].r=r,tr[u].add=0;
	if(l==r){tr[u].minx=-l;return ;}
	int mid=(l+r)>>1;
	build2(u<<1,l,mid),build2(u<<1|1,mid+1,r);
	pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}
//初始化用于处理 g 的数组 c
inline void modify(int u,int l,int r,int v){
	if(l<=tr[u].l&&tr[u].r<=r){
		tr[u].minx+=v;
		tr[u].add+=v;
		return ;
	}
	pushdown(tr[u],tr[u<<1],tr[u<<1|1]);
	int mid=(tr[u].l+tr[u].r)>>1;
	if(l<=mid) modify(u<<1,l,r,v);
	if(r>mid) modify(u<<1|1,l,r,v);
	pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}
inline int query(int u,int l,int r){
	if(l<=tr[u].l&&tr[u].r<=r){
		return tr[u].minx;
	}
	pushdown(tr[u],tr[u<<1],tr[u<<1|1]);
	int mid=(tr[u].l+tr[u].r)>>1,res=1e9;
	if(l<=mid) res=min(res,query(u<<1,l,r));
	if(r>mid) res=min(res,query(u<<1|1,l,r));
	return res;
}
inline int read(){
	int s=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		s=(s<<3)+(s<<1)+(ch^48);
		ch=getchar();
	}
	return s*f;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
inline int Find1(int x){
	int l=1,r=n,res=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(b[mid]>=x) l=mid+1,res=mid;
		else r=mid-1;
	}
	return res;
}
inline int Find2(int x){
	int l=1,r=n,res=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(b[mid]<=x) r=mid-1,res=mid;
		else l=mid+1;
	}
	return res;
}
inline void Solve(){
	n=read();rep(i,1,n) a[i]=read(),st[a[i]]=1;
	int tt=0,now=0;nep(i,n+n,1) if(!st[i]) b[++tt]=i;//获取 b
	build1(1,1,n);now=0;
	rep(i,1,n){
		int y=Find1(a[i]);
		if(~y) modify(1,1,y,1);
		while(now<n&&query(1,1,now+1)+n-now-1>=0) now++;
		f[i]=now;
	}//处理 f
	build2(1,1,n);now=n+1;
	nep(i,n,1){
		int y=Find2(a[i]);
		if(~y) modify(1,y,n,1);
		while(now>1&&query(1,now-1,n)+now-2>=0) now--;
		g[i]=n-now+1;
	}//处理 g
	int res=0;rep(i,0,n) res=max(res,f[i]+g[i+1]);//统计答案
	print(res),puts("");
}
int main(){
	int Tests=1;
	while(Tests--) Solve();
	return 0;
}
```

---

## 作者：cghAndy (赞：2)

这道贪心还真的有点把我6到了。。。

如果按照田忌赛马的逻辑之类的

很容易想到 要大的赢得时候 选一个刚好比他大一点的就好 小的时候同理 选一个刚好小一点的

那么我们用set前后搞一下 front[i]就是大的赢 1到i赢最多的盘数 behind[i]同理 从后往前 n到i 小的赢

答案就max(f[i]+g[i+1])  然而我知道你想问我选重复怎么办？

这里有个证明： 如果有一个数a用了两次 那么假设没用的那个数b<a 那么在较小赢时候可以替换a 反之亦然

刷访问量走起...（捂脸）<http://blog.csdn.net/cgh\_andy/article/details/53011315>


---

## 作者：tang_xu (赞：2)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int cmp(int a,int b){
    return a>b;//快排的cmp降序
}
int main(){
    int n,t=1,m1,m2,j=0;
    cin>>n;
    int a[n+5],b[n+5],c[100005]={0},x=n,y=1,temp=0;
    for(int i=1;i<=n;i++){
            cin>>b[i];
            c[b[i]]=1;
        }
    for(int i=1;i<=2*n;i++){
        if(c[i]==0){
            a[t]=i;
            t++;
        }
```
}//求ta手中拿的牌
for(int tot=0;tot<=n;tot++){//从tot处规则变换    枚举

```cpp
        m1=tot;m2=n-tot;
        int b1[m1+5],b2[m2+5];//对方前后的数组，以tot分隔
        for(int i=1;i<=m1;i++)    b1[i]=b[i];
        for(int i=1;i<=m2;i++)    b2[i]=b[m1+i];//储存数据
        sort(b1+1,b1+m1+1,cmp);
        sort(b2+1,b2+m2+1);//按要求排序
        for(int i=1;i<=m1;i++){
            if(a[x]>b1[i]){
                j++;
                x--; //同下
            }
```
}//有点像指针的排序，对于两个有序数组的一个个比大小
```cpp
        for(int i=1;i<=m2;i++){
            if(a[y]<b2[i]){
                j++;//计数
                y++;
            }
        }
        x=n;y=1;
        for(int now=1;now<=2*n;now++)    c[now]=0;//归零
        if(temp<j)    temp=j;//判断
        j=0; //归0
        if(temp==2*n)    break;
    }
    cout<<temp;
    return 0;
}
```
简单来说
就是暴力


---

## 作者：lichenghan (赞：1)

# P3129 High Card Low Card

[Link](https://www.luogu.com.cn/problem/P3129)

题解区都是神仙们想出来的贪心，这里讲一种考试的时候想出来的线段树解法。

首先，我们考虑只有“大的赢”一条规则，这道题怎么做。

这时有一个显而易见的贪心：对于每一个 Bessie 的牌，找一个最大但比这张牌小的，还没有用过的 Elsie 的牌，与之匹配，得一分。如果此时没有更小的牌，则这张牌不能得分。

这是什么？**括号匹配！**

![图为样例](https://cdn.luogu.com.cn/upload/image_hosting/2m7hndjp.png)

（上图为样例中的1,8,4,3）

如果我们把 Elsie 的牌看成左括号，Bessie 的牌看成右括号，那么原问题就变成了求最多匹配的括号的问题。这个问题可以简单地用线段树实现，具体见代码。

如果考虑“小的赢”的条件，那么可以把 Elsie 的牌看成右括号，Bessie 的看成左括号，和前面是一样的。

而且，假设 Bessie 选择在第 $k$ 轮变换规则，那么显然 Bessie 会把前 $k-1$ 大的牌放在前 $k-1$ 轮。

然后，从前往后扫一遍，每次把 Elsie 当前要出的牌和 Bessie 当前**最大的牌**加进线段树，我们就对于每一个 $i$ 求出了前 $i$ 轮不改变规则的答案。同样，从后往前扫一遍，我们也求出了后 $i$ 轮改变了规则的答案。

然后合并答案即可。

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N=1e5+11;
int n;
int a[N],in[N];
int b[N],cntb;
struct node{
	int el,er,all;
/*  线段树的节点
    el,er是这个区间内未匹配的左/右括号数
    all是区间内已匹配括号的对数   */
};
node t[N<<2];
void psu(int p){
	//上传
	int com=min(t[p<<1].el,t[p<<1|1].er);//左儿子的‘(’和右儿子的‘)’匹配
	t[p].all=t[p<<1].all+t[p<<1|1].all+com;
	t[p].el=t[p<<1].el+t[p<<1|1].el-com;
	t[p].er=t[p<<1].er+t[p<<1|1].er-com;
}
void c(int l,int r,int p,int tt,int typ){
	//上传，表示在区间[l,r]中在tt位置添加一个括号
	//typ: 1=左括号 2=右括号
	if(l==r){
		if(typ==1) t[p]={1,0,0};
		else t[p]={0,1,0};
		return;
	}
	int mid=(l+r)>>1;
	if(tt<=mid){
		c(l,mid,p<<1,tt,typ);
	}else{
		c(mid+1,r,p<<1|1,tt,typ);
	}
	psu(p);
}
int ansl[N],ansr[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		in[a[i]]=1;
	}
	for(int i=n*2;i>=1;i--){
		if(!in[i]) b[++cntb]=i;
        //处理出 Bessie 的牌
	}
	for(int i=1;i<=n;i++){
		c(1,n*2,1,a[i],1); //左括号
		c(1,n*2,1,b[i],2); //右括号
		ansl[i]=t[1].all; //记录左侧的答案
	}
	for(int i=1;i<(N<<2);i++){
		t[i]={0,0,0};
	}
	for(int i=n;i>=1;i--){
		c(1,n*2,1,a[i],2); //右括号
		c(1,n*2,1,b[i],1); //左括号
		ansr[i]=t[1].all; //记录右侧的答案
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		ans=max(ans,ansl[i]+ansr[i+1]);//合并
	}
	cout<<ans;
}
```

---

## 作者：大菜鸡fks (赞：1)

这题还是比较神的，感觉自己还是傻。QAQ
一开始想的是从左往右用set维护，从右往左也用set维护。每次在一个set里删除，一个set里添加。但貌似无法做到O（1）统计答案非常不优美。

看了洛谷题解以后恍然大悟。
这题贪心策略是非常显然的。能用差的就用差的去赢他，不要浪费好的资源。

每次记录f[i]为在规则1下，从左往右到i最多能赢多少，g[i]为在规则2下，从右往左到i最多能赢多少。
答案就是max（f[i]+g[i+1]）

我来简单说一下正确性：你如果两个地方用的同一张牌i，肯定有一张牌没被用，那么分情况讨论。
1.比这张牌大。 那么这张牌可以替换掉在规则1下的牌i
2.比这张牌小。 那么这张牌可以替换掉在规则2下的牌i

这样的做法可以证明方案的正确性

```cpp
#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
set<int >q1,q2;
const int maxn=1e5+5;
int n,a[maxn],b[maxn],tot;
bool flag[maxn<<1];
inline void init(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		flag[a[i]]=1;
	}
	for (int i=1;i<=2*n;i++){
		if (!flag[i]){
			b[++tot]=i;
			q1.insert(i);
			q2.insert(-i);
		}
	}
}
int ans,f[maxn],g[maxn];
inline void solve(){
	for (int i=1;i<=n;i++){
		set<int > ::iterator it=q1.lower_bound(a[i]);
		if (it!=q1.end()){
			q1.erase(it); f[i]=f[i-1]+1;
		}else {
			f[i]=f[i-1];
		}
	}
	for (int i=n;i;i--){
		set<int > ::iterator it=q2.lower_bound(-a[i]);
		if (it!=q2.end()){
			q2.erase(it); g[i]=g[i+1]+1;
		}else{
			g[i]=g[i+1];
		}
	}
	ans=g[1];
	for (int i=1;i<=n;i++){
		ans=max(ans,f[i]+g[i+1]);
	}
	printf("%d\n",ans);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：_Imaginary_ (赞：0)

## Problem

[自己看](https://www.luogu.com.cn/problem/P3129)

## Solution

如果我们希望尽可能的比对方大，就尽量出恰好能压掉对方的最小的牌。

如果希望尽可能出的比对方小，就尽量出恰好能压掉对方的最大的牌。

所以，我们只要处理前 $k$ 轮希望尽可能比对方大，能赢的轮数，还有后 $k$ 轮希望尽可能比对方小，能赢的轮数。

这里 $k$ 取 $1\sim n$。

发现，我们只要找前驱和后继就行，用 `set` 的 `lower_bound` 就行。

（对于前驱，全部取成负数就转化成后继了）

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=50005;
int n,a[N];
bool vis[2*N];
set<int> s1,s2;
int pre[N],suc[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
		vis[a[i]]=1;
	}
	pre[0]=suc[n+1]=0;
	for(int i=1;i<=2*n;i++)
	{
		if(!vis[i])
		{
			s1.insert(i);
			s2.insert(-i);
		}
	}
	for(int i=1;i<=n;i++)
	{
		set<int>::iterator it=s1.lower_bound(a[i]);
		if(it!=s1.end()) 
		{
			s1.erase(it);
			pre[i]=pre[i-1]+1;
		}
		else pre[i]=pre[i-1];
	}
	for(int i=n;i>=1;i--)
	{
		set<int>::iterator it=s2.lower_bound(-a[i]);
		if(it!=s2.end()) 
		{
			s2.erase(it);
			suc[i]=suc[i+1]+1;
		}
		else suc[i]=suc[i+1];
	}
	int ans=0;
	for(int i=0;i<=n;i++) ans=max(ans,pre[i]+suc[i+1]);
	printf("%d",ans);
	return 0;
}

```

---

## 作者：_YyD_ (赞：0)

## 题目

[我相信你不是文盲](https://www.luogu.com.cn/problem/P3129)

## 解法

假设第 $i+1$ 变规则。

我们只要每一轮打出恰好比对手大的最小的牌，如果不存在就打最小的牌，这样一定是最优的。

另一种规则则将大小反过来。

考虑处理出每个前缀的最多胜场和每个后缀的最多胜场。

这两个是类似的，我们以维护前缀为例。

~~输的场给啥都行，我们先不管~~

赢的场，我们把他放大也是没有关系的。

**So**

我们先假设所有牌都可以在左边决策。

这样的话就可以从前往后取恰好大于的得到胜场。

但是对于一个以 $i$ 为分割的决策，我们在前 $i$ 场一定要取最大的 $i$ 个。

此时我们把所有取的小的变成前 $i$ 个即可。

后缀类似。

复杂度 $O(n \log n)$ 。

## Code

```cpp
#include<bits/stdc++.h>

#define int long long

#define pb(x) push_back(x)

#define rep(i,l,r) for(int i=l;i<=r;i++)
#define lep(i,l,r) for(int i=l;i>=r;i--)

#define fan putchar('\n')
#define fak putchar(' ')

// #pragma GCC optimize(2,3,"Ofast","inline")

using namespace std;

inline int read() {
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;
	return ~(X-1);
}
inline void write(int X) {
	if(X<0) {X=~(X-1); putchar('-');}
	if(X>9) write(X/10);
	putchar(X%10+'0');
}

int n;
int a[60000];
int b[60000<<1];
int f[60000];
int g[60000];
int ans;
set<int> A,B;

void solve(){
	n=read();
	rep(i,1,n)a[i]=read(),b[a[i]]=1;
	rep(i,1,n<<1)if(!b[i])A.insert(i),B.insert(-i);
	rep(i,1,n){
		f[i]=f[i-1];
		auto t=A.lower_bound(a[i]);
		if(t!=A.end())A.erase(t),f[i]++;
	}
	lep(i,n,1){
		g[i]=g[i+1];
		auto t=B.lower_bound(-a[i]);
		if(t!=B.end())B.erase(t),g[i]++;
		ans=max(ans,f[i]+g[i+1]);
	}
	cout<<max(ans,g[1]);
}

signed main(){
	solve();
	getchar();
	return 0;
}
```


---

## 作者：Epworth (赞：0)

考虑没有特殊权利，怎样安排才能赢得最多：

每次出比对方的牌大，且最接近的牌(出太大的浪费，出太小的要输)。

如果没有比对方的牌大的牌，就牺牲最小的牌带走对面的牌(反正打不赢，小的换大的，稳赚)。

如果有特殊权力呢?

考虑把对方出牌的顺序分成两个序列，断点为$k$。

我们要在$1-k$中尽可能比对面大，$k+1-n$中尽可能比对面小。

根据贪心策略，我们会在$1-k$尽量出大牌，$k+1-n$尽量出小牌，无法满足牺牲一张最后没用的牌。

我们无法知道最后那些牌被牺牲，

但$1-k$中赢的牌，$k+1-n$中赢的牌，$1-n$中牺牲的牌的并集一定是开始时的手牌。

枚举断点分别计算的时间复杂度是$O(过不了)$，考虑优化。

定义$win[i]$表示以$i$为断点，$1-i$最多赢(点数大)多少局。

定义$lose[i]$表示以$i$为断点，$i+1-n$最多“输”(点数小)多少局。

可以用$set$在线性复杂度内处理出两个数组。

为啥用$set$？无重有序集还自带$lower\_bound$查后继。

当然$dalao$们想敲平衡树也可以$ORZ$。

断点为$i$时，最多获胜局数为$win[i]+lose[i+1]\ \ \ i\in [1,n]$

循环统计答案即可。
```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
inline int read(){
	char ch=getchar();int s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-48;ch=getchar();}
	return s*w;
}
int n;
int a[maxn];
int card[maxn];
int win[maxn];
int lose[maxn];
set<int> s;
int main(){
	//freopen("card.in","r",stdin);
	//freopen("card.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		card[a[i]]=1;
	}
	for(int i=1;i<=2*n;i++){
		if(!card[i]) s.insert(i);
	} 
	for(int i=1;i<=n;i++){
		set<int>::iterator it;
		it=s.upper_bound(a[i]);
		if(it==s.end()) win[i]=win[i-1];
		else{
			win[i]=win[i-1]+1;	
			s.erase(it);
		}
	}
	for(int i=1;i<=2*n;i++){
		if(!card[i]) s.insert(i);
	} 
	for(int i=n;i>=1;i--){
		set<int>::iterator it;
		it=--s.upper_bound(a[i]);
		if(it==s.end()) lose[i]=lose[i+1];
		else{
			lose[i]=lose[i+1]+1;
			s.erase(it);	
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		ans=max(ans,win[i]+lose[i+1]);
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：AcerMo (赞：0)

思路和楼下都一样，set维护就好，但是存入第二个set的时候，我没有存负值，只是在查询的时候it--，因为如果不--，那么查到的是大于的第一个，--后就是小于它的最大值了（我神奇的码风2333逃）
```cpp
#include<set>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int M=100500;
set<int>s,t;
set<int>::iterator it;
int n,ans=0;
int a[M],b[M],f[M],g[M];
bool judf(int i)
{
	it=s.lower_bound(a[i]);
	return (it!=s.end());
}
bool judg(int i)
{
	it=t.lower_bound(a[i]);
	it--;
	return (it!=t.end()); 
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]),b[a[i]]=1;
	for (int i=1;i<=2*n;i++)
		if (!b[i]) s.insert(i),t.insert(i);
	for (int i=1;i<=n;i++)
		if (judf(i)) s.erase(it),f[i]=f[i-1]+1;
			else f[i]=f[i-1];
	for (int i=n;i>=1;i--)
		if (judg(i)) t.erase(it),g[i]=g[i+1]+1;
			else g[i]=g[i+1];
	for (int i=0;i<=n;i++) ans=max(ans,f[i]+g[i+1]);
	cout<<ans;
	return 0;
}
```

---

## 作者：i207M (赞：0)

## 题目总结

贝西和她的朋友艾尔西正在玩这个简单的纸牌游戏。游戏有2N张牌，牌上的数字是1到2N。把这些牌分成两份，贝西有N张，艾尔西有另外N张。接下来她们进行N轮出牌，每次各出一张牌。一开始，谁出的牌上的数字大，谁就获得这一轮的胜利。贝西有一个特殊权利，她可以在任意一个时刻把原本数字大的获胜的规则改成数字小的获胜，这个改变将会一直持续到游戏结束。特别的，贝西可以从第一轮开始就使用小牌获胜的规则，也可以直到最后一轮都还杂使用大牌获胜的规则。

现在，贝西已经知道了艾尔西出牌的顺序，她想知道她最多能够赢多少轮。

## 数据范围

N<=50000

## 解题思路

贪心，能出牌就出牌，ans为前缀和后缀的最大值；

为什么前边不影响后边？

前边出最大的，后边出最小的，加起来是整个的；

## 易错误区

1. 不要瞎用pushback，vector下标从0开始；

2. 是$f[i]+g[i+1]$，不是$f[i]+g[i]$；

3. 求ans时从0循环到n；

## 代码展示

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
il char gc() {
    static const int BS = 1 << 22;
    static unsigned char buf[BS], *st, *ed;
    if (st == ed) ed = buf + fread(st = buf, 1, BS, stdin);
    return st == ed ? EOF : *st++;
}
#define gc getchar
template<class T>void in(T &x)
{
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while ('0' <= c && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
void out(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) out(x / 10);
    putchar(x % 10 + '0');
}
#define N 50010
vector<int>e;
set<int>b, c;
set<int>::iterator it;
int f[N], g[N];
int n, ans;
signed main() {
    in(n);
    e.push_back(0);
    for (ri i = 1; i <= (n << 1); ++i) b.insert(i);
    for (ri i = 1, t; i <= n; ++i) {
        in(t);
        e.push_back(t);
        b.erase(t);
    }
    c = b;
    for (ri i = 1; i <= n; ++i) {
        f[i] = f[i - 1];
        if ((it = b.upper_bound(e[i])) != b.end()) {
            f[i]++;
            b.erase(it);
        }
    }
    for (ri i = n; i >= 1; --i) {
        g[i] = g[i + 1];
        if ((it = c.lower_bound(e[i])) != c.begin()) {
            g[i]++;
            c.erase(--it);
        }
    }
    for (ri i = n; i >= 0; --i) {
        ans = max(ans, f[i] + g[i + 1]);
    }
    printf("%d", ans);
    return 0;
}
/*
int f[N];
int find(int x){
    return x==f[x]?x:f[x]=find(f[x]);
}
bool cmpy(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx==fy) return 0;
    if(fy>fx) f[fy]=fx;
    else f[fx]=fy;
    return 1;
}
*/
/*
int v[M], u[M], w[M], nx[M];
int cnt, head[N];
il void add(int uu, int vv, int ww) {
    u[++cnt] = uu, v[cnt] = vv, w[cnt] = ww, nx[cnt] = head[uu];
    head[uu] = cnt;
}
*/
/*
struct Edge {
    int u,v,w,nx;
    Edge() {}
    Edge(int uu,int vv,int ww,int nxt) {
        u=uu,v=vv,w=ww,nx=nxt;
    }
    friend bool operator<(const Edge& a,const Edge& b) {
        return a.w<b.w;
    }
} edge[M];
int cnt,head[M];
il void add(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
}
*/
```

---

## 作者：happybob (赞：0)

## 做法

较为简单的贪心。

先考虑不存在特殊权力，即每次都是大牌获胜。假设这次对方出的是 $a_i$。分情况讨论：

- 若 $a_i$ 是还没有打出的牌中的最大值，显然我方无论如何都无法得到这局的分，因此打出最小的牌。

- 若 $a_i$ 不是最大值，则一定可以出一张牌赢得这一局，显然最优方案是出大于 $a_i$ 的最小值，也就是 `upper_bound`。

而使用特殊权力，即每次都是小牌获胜，把情况反转即可。

可以考虑枚举中点，即使用权力的点 $i$，然后对于每一种情况计算答案，使用 `set` 的复杂度是 $O(n^2 \log n)$。显然超时。

设两个序列 $c1, c2$，$c1_i$ 表示前 $i$ 张牌不使用权力，即大牌获胜时最多赢的轮数，$c2_i$ 表示从第 $i$ 张牌到第 $n$ 张牌使用权力，即小牌获胜最多赢的轮数。特殊地，$c1_0 = 0$，$c2_{n+1} = 0$。

可得答案为 $\max_{i=0}^n c1_i + c2_{i+1}$，时间复杂度 $O(n \log n)$，足以通过。

---

