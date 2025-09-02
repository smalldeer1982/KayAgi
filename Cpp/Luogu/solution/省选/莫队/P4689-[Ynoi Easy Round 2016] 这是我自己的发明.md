# [Ynoi Easy Round 2016] 这是我自己的发明

## 题目背景

一切伟大的世界历史事件与人物，可以说都会出现两次

第一次是作为悲剧出现

第二次，则是作为笑剧出现

——《路易.波拿巴的雾月十八日》

感动、

痛苦、

以及快乐、

都只是遥不可及的宝石

即便如此，人们啊，

获得幸福吧！

![](https://cdn.luogu.com.cn/upload/pic/21098.png)

世界将在7月20日终结

世界回归天空的日子

万物被天空侵染的日子

回归天空的日子

世界必须回归

世界的极限

世界的尽头

世界的终结

![](https://cdn.luogu.com.cn/upload/pic/21099.png)

你看…那就是极限…最尽头的天空

如今，已无应该之事了如今，已无忘却之物了

不需要的话语

![](https://cdn.luogu.com.cn/upload/pic/21100.png)

告别了永不相交的平行，我被吸进了…

垂直下落的世界

![](https://cdn.luogu.com.cn/upload/pic/21101.png)

虽哭亦喜

虽悲亦喜

各种感情混在一起...

比起其他所有，想必还是高兴占多吧

她高兴地抱着我

紧紧地抱着

再也不会松开了...

想永远这样...

她的思绪，以比语言更快的速度，传达给了我

有些东西，比语言更快

她的思绪，以比语言更快的速度，传达给了我

有些东西，比语音更准确

世界上无论多么短暂的瞬间，都有意义

有意义

块临近终结了

最后的瞬间

啊啊...

远方的警笛声

黑色的天空

月正笑

地正润潮

星正舞

风正凉

在我怀中，温暖的，

橘希实香

![](https://cdn.luogu.com.cn/upload/pic/21103.png)

她在我的怀中...静静地合上了双眼

然后我也...

静静地合上了双眼

## 题目描述

您正在打 galgame，然后突然家长进来了，于是您假装在写数据结构题：

给一个树，$n$ 个点，有点权，初始根是 1。

$m$ 个操作，种类如下：

`1 x` 将树根换为 $x$。

`2 x y` 给出两个点 $x,y$，从 $x$ 的子树中选每一个点，$y$ 的子树中选每一个点，求点权相等的情况数。


## 说明/提示

Idea：nzhtl1477，Solution：nzhtl1477，Code：nzhtl1477，Data：nzhtl1477

【数据范围】   
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1 \le m \le 5\times 10^5$ , $1 \le a_i \le 10^9$。

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
1 2
1 3
3 4
3 5
2 4 5
2 1 5
2 3 5
1 5
2 4 5```

### 输出

```
0
1
1
1```

# 题解

## 作者：shadowice1984 (赞：21)

~~丢人根号分治，打不过拆一堆询问的莫队~~

这里介绍一种规避莫队的做法

_____________________


# 本题题解

给定一颗树，树上每个点有点权，询问x和y的子树当中有多少对点的颜色相等，支持换根

不过我们很快发现换根是假的……，我们用dfs序把这颗树拍平成一个序列

之后我们会发现无论根在哪里，一个点的子树只对应着两种联通块，一种是根为1时的子树，另一个是所有点刨去这个点的一个孩子的子树，这个自行画图理解一下即可，应该不难

那么我们就可以集中精力解决没有换根操作时的问题了

那么我们发现一个非常重要的性质，在这颗树上出现次数大于$\sqrt{N}$的颜色数目不会超过$\sqrt{N}$种

那么意味着我们可以将两种暴力拼在一起，一种是$O(cntm)$的暴力，其中$cnt$是颜色数目，另一种是$O(\sum_{i}cnt(i)^2+m\sqrt{n})$的暴力，其中$cnt(i)$是每一种颜色出现的次数。

那么如果我们对所有出现次数大于$\sqrt{N}$的颜色跑第一种暴力而对所有出现次数小于$\sqrt{N}$的颜色跑第二种暴力的话，我们就可以得到一个复杂度为$O(m\sqrt{n})$优秀做法


所以接下来我们分别介绍两种暴力

## case1：当颜色出现次数大于根号n时

~~恭喜你发现了一道思博题~~

枚举每个颜色对答案的贡献，令$siz(i)$表示$i$这个子树里有多少个点的颜色是我们枚举的颜色，那么这个颜色对一个询问$(x,y)$的贡献就是$siz(x)siz(y)$

然后我们枚举每一个大于$\sqrt{n}$的颜色跑一遍刚才的暴力就行了，复杂度$O((n+m)\sqrt{n})$

## case 2:当颜色的出现次数小于根号n时

~~恭喜你发现了另一道思博题~~

此时我们只需要想一个$O(\sum_{i}cnt(i)^2)$的暴力就行了，那么我们可以把所有同色的点对$(x,y)$拉出来

接下来我们观察一下询问，询问的限制是子树，一个子树在dfs序上被映射为了一段区间，那么转化一下询问的要求就是第一个点在一段区间$(l1,r1)$第二个点在另一段区间$(l2,r2)$

这东西似乎是一个矩形询问?

那么这似乎是一个二维数点裸题，询问一个矩形里有多少点……

如果直接拖二维数点的板子离线后跑扫描线的话我们会得到一个丢人的$O(n\sqrt{n}logn+m\sqrt{n})$做法

如果我们调整一下根号分治的上下界的话我们会得到一个$O((n+m)\sqrt{nlogn})$的丢人做法

所以显然不能直接粘二维数点板子，观察到询问只有$O(m)$次，但是修改却有$O(n\sqrt{n})$次，那么这启示我们将树状数组替换为分块，此时我们的复杂度就是$O((n+m)\sqrt{n})$了

实际写的时候你会发现这个数点十分恶心，需要手动拆扫描线才能保证我们询问的次数不是很多……

然后我们就做完这道题~十分好写也不需要卡什么常数就过去了

上代码~

```C
// luogu-judger-enable-o2
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;const int N=1e5+10;const int BC=230;typedef long long ll;
namespace INPUT_SPACE{
    const int BS=(1<<24)+5;char Buffer[BS],*HD,*TL;
    char gc() { if(HD==TL) TL=(HD=Buffer)+fread(Buffer,1,BS,stdin);return (HD==TL)?EOF:*HD++; }
    inline void read(int& t)
    {
        int x,ch,sgn=1;while(((ch=gc())<'0'||ch>'9')&&ch!='-');
        if(ch=='-') sgn=-1,x=0;else x=ch^'0';
        while((ch=gc())>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^'0');
        t=x*sgn;
    }
}using INPUT_SPACE::read;
const int HB=1<<25;const int TB=(1<<25)-1;
template <typename T>
inline void gm(T* &bas,int siz,T* & op){op=bas;bas=bas+siz+1;}
int dfn[N];int nfd[N];int siz[N];int df;int dg[N];int col[N];int nrt;
struct qry{int u;int v;ll ans;}qr[N*5];int n;int m;int ccnt[N];int bel[N];
inline int isson(int u,int rt){return (nfd[u]<=nfd[rt])&&(nfd[rt]<nfd[u]+siz[u]);}
namespace lsh
{
    map <int,int> mp;
    inline void pre()
    {
        for(int i=1;i<=n;i++)mp[col[i]]=1;map <int,int> :: iterator it,it1;
        for(it=mp.begin(),it1=it,it1++;it1!=mp.end();++it,++it1)it1->second+=it->second;
        for(int i=1;i<=n;i++)col[i]=mp[col[i]];for(int i=1;i<=n;i++)ccnt[col[i]]++;
    }
}
namespace brusolve1
{
    int* v[N];int Eg_bas[N<<2];int* A_t;int csiz[N];int afn[N];int af;
    inline void ih(){A_t=Eg_bas;for(int i=1;i<=n;i++)gm(A_t,dg[i]-(i!=1),v[i]),dg[i]=0;}
    inline void ins(int u,int V){v[u][++dg[u]]=V;}
    inline void pb(int u){afn[++af]=u;}
    inline void calc(int cc)
    {
        for(int i=1;i<=n;i++)csiz[i]=(col[i]==cc);
        for(int i=1;i<=n;i++)
        {int u=afn[i];for(int j=1;j<=dg[u];j++)csiz[u]+=csiz[v[u][j]];}
        for(int i=1,tot=csiz[1];i<=m;i++)
        {
            qry& p=qr[i];
            int c1=(p.u&HB)?tot-csiz[p.u&TB]:csiz[p.u&TB];
            int c2=(p.v&HB)?tot-csiz[p.v&TB]:csiz[p.v&TB];p.ans+=(ll)c1*c2;
        }
    }inline void solve(){for(int i=1;i<=n;i++)if(ccnt[i]>BC)calc(i);}
}
namespace brusolve2
{
    const int B=270;
    struct sqry{int l;int r;int id;};vector <sqry> ve[N];vector <sqry> ed; 
    int* vc[N];int V_bas[N<<2];int* A_t;int a1[N];int sub[N];int bi[N];
    inline int cqry(int l,int r)
    {
        if(bi[l]==bi[r]){int ret=0;for(int i=l;i<=r;i++)ret+=a1[i];return ret;}
        int ret=0;for(int i=l;bi[i]==bi[l];i++)ret+=a1[i];
        for(int i=r;bi[i]==bi[r];i--)ret+=a1[i];
        for(int i=bi[l]+1;i<bi[r];i++)ret+=sub[i];return ret;
    }
    inline void pre()
    {
        A_t=V_bas;for(int i=1;i<=n;i++)
            if(ccnt[i]<=BC){gm(A_t,ccnt[i],vc[i]),ccnt[i]=0;}
        for(int i=1;i<=n;i++)
            {int nc=col[i];if(ccnt[nc]<=BC)vc[nc][++ccnt[nc]]=nfd[i];}
        for(int i=1;i<=n;i++)bi[i]=(i-1)/B+1;
        for(int i=1;i<=m;i++)
        {
            qry& t=qr[i];int tp=(((t.u&HB)>>25)<<1)|((t.v&HB)>>25);
            int u=t.u&TB;int v=t.v&TB;sqry nw=(sqry){nfd[v],nfd[v]+siz[v]-1,0};
            vector <sqry>& q1=ve[nfd[u]-1];vector <sqry>& q2=ve[nfd[u]+siz[u]-1];
            switch(tp)
            {
                case 0:{nw.id=i<<2|1;q1.push_back(nw);nw.id=i<<2|0;q2.push_back(nw);break;}
                case 1:{nw.id=i<<2|3;q1.push_back(nw);nw.id=i<<2|2;q2.push_back(nw);break;}
                case 2:
                {
                    nw.id=i<<2|0;q1.push_back(nw);nw.id=i<<2|1;q2.push_back(nw);
                    ed.push_back((sqry){nfd[v],nfd[v]+siz[v]-1,i<<2|0});break;
                }
                case 3:
                {
                    nw.id=i<<2|2;q1.push_back(nw);nw.id=i<<2|3;q2.push_back(nw);
                    ed.push_back((sqry){nfd[v],nfd[v]+siz[v]-1,i<<2|2});break;
                }
            }
        }
    }
    inline void solve()
    {
        pre();ll tot=0;
        for(int i=1;i<=n;i++)
        {
            int nc=col[dfn[i]];
            if(ccnt[nc]<=BC)for(int j=1;j<=ccnt[nc];j++)
                    a1[vc[nc][j]]++,sub[bi[vc[nc][j]]]++,tot++;
            for(vector <sqry>:: iterator it=ve[i].begin();it!=ve[i].end();++it)
            {
                int ans=cqry(it->l,it->r);ll& tar=qr[it->id>>2].ans;
                switch(it->id&3)
                {
                    case 0:{tar+=ans;break;}case 1:{tar-=ans;break;}
                    case 2:{tar+=tot-ans;break;}case 3:{tar-=tot-ans;break;}
                }
            }
        }for(int i=1;i<=n;i++)a1[i]+=a1[i-1];
        for(vector <sqry>:: iterator it=ed.begin();it!=ed.end();++it)
        {
            int ans=a1[it->r]-a1[it->l-1];ll& tar=qr[it->id>>2].ans;
            if((it->id&3)==0)tar+=ans;else tar+=tot-ans;
        }
    }
}
namespace oldtree
{
    int v[N<<1];int x[N<<1];int ct;int al[N];int fa[N][22];int dep[N];
    inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;dg[u]++;dg[V]++;}
    inline int dfs(int u,int f)
    {
        for(int i=0;fa[u][i];i++)fa[u][i+1]=fa[fa[u][i]][i];
        dfn[++df]=u;nfd[u]=df;
        for(int i=al[u];i;i=x[i])
            if(v[i]!=f)fa[v[i]][0]=u,dep[v[i]]=dep[u]+1,brusolve1::ins(u,v[i]),siz[u]+=dfs(v[i],u);
        brusolve1::pb(u);return ++siz[u];
    }
    inline int cbt(int u,int v)
    {
        int del=dep[v]-dep[u];del--;
        for(int i=0;del;del>>=1,i++)if(del&1)v=fa[v][i];return v;
    }
    inline void build(){brusolve1::ih();dfs(1,0);}
}
int main()
{
    read(n);read(m);
    for(int i=1;i<=n;i++)read(col[i]);lsh::pre();
    for(int i=1,u,v;i<n;i++)read(u),read(v),oldtree::add(u,v),oldtree::add(v,u);nrt=1;
    oldtree::build();
    for(int i=1,tp,u,v;i<=m;i++)
    {
        read(tp);if(tp==1){read(nrt);m--,i--;continue;}
        read(u);read(v);
        if(u==nrt)u=1;else if(isson(u,nrt))u=oldtree::cbt(u,nrt)|(1<<25);
        if(v==nrt)v=1;else if(isson(v,nrt))v=oldtree::cbt(v,nrt)|(1<<25);
        qr[i]=(qry){u,v,0};
    }brusolve1::solve();brusolve2::solve();
    for(int i=1;i<=m;i++)printf("%lld\n",qr[i].ans);return 0;
}
```







---

## 作者：yuzhechuan (赞：16)

[P5268 [SNOI2017]一个简单的询问](https://www.luogu.com.cn/problem/P5268)的树上加强版，难度得到了一定的提高

---

### 题解：

首先不考虑换根操作的话，询问可以用dfs序转为两个区间，分别对应两棵子树，于是问题就转化为了P5268

然后考虑换根操作，延续不换根的做法，我们现在也要搞出$x,y$在的dfs序上的对应区间

设$rt$为当前根，很容易发现只有当$rt$在$x$(或$y$)的子树内的时候才会有异于不换根做法的情况出现

画出这种情况：

![](https://s1.ax1x.com/2020/06/02/tYeQzj.png)

稍加观察就能发现以rt为根时，$x$的子树是整棵树扣掉$1$的子树，而$1$是$rt$的祖先中最接近$x$的一个

![](https://s1.ax1x.com/2020/06/02/tYe1Qs.png)

然后类比，所有的这种"1"都可以用树上k级祖先$O(1)-O(log n)$解决，于是$x$的对应区间就是整棵树扣掉"1"的子树区间

搞出每个询问对应的实际区间后就可以仿照P5268的做法拆询问搞莫队啦qwq

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define getchar gc
inline char gc(){
	static char buf[1<<16],*p1=buf,*p2=buf;
	if(p1==p2){
		p2=(p1=buf)+fread(buf,1,1<<16,stdin);
		if(p2==p1) return EOF;
	}
	return *p1++;
}
#endif
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

#define pii pair<int,int>
#define l first
#define r second

const int N=5e5+5,M=1e6+5; //理性开大，没啥坏处（雾）
int dfn[N],cnt,sz[N],d[N],f[N][18],qn,ans[M],t,rt,bl[N],n,m,num[N],un,a[N],col[N],cntl[N],cntr[N];
vector<int> g[N];

struct que{
	int l,r,i;
	inline bool operator < (const que &nt) const {
		return bl[l]^bl[nt.l]?bl[l]<bl[nt.l]:bl[l]&1?r<nt.r:r>nt.r;
	}
}q[M<<2];

void dfs(int x,int fa){ //预处理
	dfn[x]=++cnt;sz[x]=1;d[x]=d[fa]+1;
	f[x][0]=fa;
	for(int i=1;f[f[x][i-1]][i-1];i++) f[x][i]=f[f[x][i-1]][i-1];
	for(int y:g[x]) if(y^fa) dfs(y,x),sz[x]+=sz[y];
}

void add(int l,int r,int ll,int rr,int i){ //拆询问，类比P5268
	q[++qn]=(que){r,rr,i};
	q[++qn]=(que){l-1,rr,-i}; 
	q[++qn]=(que){ll-1,r,-i};
	q[++qn]=(que){l-1,ll-1,i};
}

int getk(int x,int k){ //logn找k祖先
	for(int i=17;~i;i--) if(k>=(1<<i)) k-=1<<i,x=f[x][i];
	return x;
}

vector<pii> calc(int x){
	vector<pii> res;
	if(x==rt) res.push_back(pii(1,n)); //是根就是[1,n]
	else if(dfn[x]<=dfn[rt]&&dfn[rt]<=dfn[x]+sz[x]-1){ //rt在x子树内就找出要被扣掉的那棵树的根节点son
		int son=getk(rt,d[rt]-d[x]-1);
		if(1<=dfn[son]-1) res.push_back(pii(1,dfn[son]-1));
		if(dfn[son]+sz[son]<=n) res.push_back(pii(dfn[son]+sz[son],n));
	}
	else res.push_back(pii(dfn[x],dfn[x]+sz[x]-1)); //否则就直接返回x子树的dfs序区间
	return res;
}

signed main(){
    srand(time(NULL));
	read(n);read(m);rt=1;
	for(int i=1;i<=n;i++) num[i]=read(a[i]);
	sort(num+1,num+1+n);
	un=unique(num+1,num+1+n)-num-1;
	for(int i=1,x,y;i<n;i++){
		read(x);read(y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(rand()%n+1,0); //小优化，随机为根让毒瘤出题人很难来卡你
	for(int i=1;i<=n;i++) col[dfn[i]]=lower_bound(num+1,num+1+un,a[i])-num; //将原数列点权转为对应dfs序列的点权，并顺便离散化
	while(m--){
		int op;
		read(op);
		if(op==1) read(rt);
		else{
			int x,y;
			vector<pii> px,py; //分别对应两个询问点的对应ds区间
			t++;
			read(x);read(y);
			px=calc(x);
			py=calc(y);
			for(auto x:px) for(auto y:py) add(x.l,x.r,y.l,y.r,t); //分别枚举，进行拆分询问
		}
	}
    //下面就与P5268相同了
	int len=n/sqrt(t);
	for(int i=1;i<=n;i++) bl[i]=(i-1)/len+1;
	for(int i=1;i<=qn;i++) if(q[i].l>q[i].r) swap(q[i].l,q[i].r);
	sort(q+1,q+1+qn);
	for(int i=1,l=1,r=1,cur=0;i<=qn;i++){
		while(l<q[i].l) cur+=cntr[col[++l]],cntl[col[l]]++;
		while(l>q[i].l) cur-=cntr[col[l]],cntl[col[l--]]--;
		while(r<q[i].r) cur+=cntl[col[++r]],cntr[col[r]]++;
		while(r>q[i].r) cur-=cntl[col[r]],cntr[col[r--]]--;
		ans[abs(q[i].i)]+=cur*(q[i].i/abs(q[i].i));
	}
	for(int i=1;i<=t;i++) write(ans[i]),puts("");
}
```

---

## 作者：Limit (赞：13)

# 题目大意

给出一棵树,每个节点有一个权值,这个数的根节点会改变,每次查询两颗子树中各取一个节点的值相同的方案数.

# 分析

先转换一下问题,取出的节点的值相同的方案数 $=\sum_{i=1}^n(count(i,x)\times count(i,y))$(其中 $count(a,b)$ 表示在 $b$ 的子树中值 $a$ 出现的次数).

然后就变成了一个和 [P5268](https://www.luogu.com.cn/problem/P5268) 差不多的一个问题.

在 DFS 序中查询的子树必定为其中的一段区间或者两段区间(其中一段的一端为头,另一段的一端为尾).

对于拆成最多 $16$ 个区间的做法这里就不多说了,这里就分享一个只需要拆成 $4$ 个区间的大常数做法以及一个可能有点用的卡常方法.

对于拆出来的两个区间都是从数列的边上开始,那么这个东西看起来就像是一个环,那么就可以用处理环的方法处理这个东西,对于 $[1,a]$ 和 $[b,n]$($a<b$) 这样两段区间可以先将原序列变成两个相连的原序列,那么这两个区间就变成了 $[b,n+a]$,变成了一个区间就比较好处理了(但是这里的 $n$ 相当于乘了 $2$ 所以常数巨大实测基本会 TLE).

考虑 lxl 是毒瘤,所以数据也会很毒瘤,对于最多拆 $16$ 个区间的方法可能会卡满,那么考虑最开始建树的时候**随机**一个节点为 $root$ 建树,对于运气好的时候可以跑飞快.

利用上面两个方法确实是可以通过这道题的(但不能做到次次过).

代码太丑了,想要看的点[这里](https://www.luogu.com.cn/record/34067785)吧(~~我觉得 $60$ 分还是挺容易做到的~~).

---

## 作者：Sol1 (赞：12)

貌似是第一次完全脱离题解切掉一个黑题呢？

进入正题。

首先如果你的做题量够多的话一眼就会发现这个询问就是 [P5268 [SNOI2017]一个简单的询问](https://www.luogu.com.cn/problem/P5268) 搬到了子树上面。

然后子树转序列有一个很套路的方式就是用 dfs 序。

但是换根怎么搞呢？

其实你只需要稍微想一下就会知道换根是假的，对于任意一个节点 $u$，定义此时 $u$ 的子树是按以 $1$ 为根计算的，那么我们分情况讨论：

1. 如果此时的根是不在 $u$ 的子树内的，那么显然以此时的根计算的子树与以 $1$ 为根计算的子树是一样的。
2. 如果此时的根是 $u$，那么显然子树就是整棵树。
3. 如果此时的根在 $u$ 的一个孩子 $v$ 的子树里面，那么显然此时 $u$ 的子树就是整棵树去掉 $v$ 的子树。

显然上面三种情况都可以在 dfs 序上面找到对应的 $1\sim 2$ 段连续区间。

所以换根是假的~

这时你可能会想到直接在 dfs 序上面做 P5268。

下面为了方便说明，我们记 $f(a, b, c, d)$ 为 $[a,b]$ 区间和 $[c,d]$ 区间之间的查询结果，$g(x,y)=f(1,x,1,y)$。

我们在计算 $f(l_1,r_1,l_2,r_2)$ 的时候是拆了 $4$ 个询问，变成 $g(r_1,r_2)-g(l_1-1,r_2)-g(r_1,l_2-1)+g(l_1-1,l_2-1)$。

然后如果根同时出现在 $u$ 和 $v$ 的子树里面，我们要算的是 $f(1,l_1,1,l_2)+f(1,l_1,r_2,n)+f(r_1,n,r_2,n)+f(r_1,n,1,l_2)$。

直接拆得到 $4\times 4=16$ 个询问然后做莫队！

~~抱歉你这样是过不掉的~~

然后你发现可以倍长 dfs 序列，然后就不用拆区间了，就只剩 $4$ 倍的询问了！

~~抱歉莫队的复杂度是 $\sout {O(n\sqrt m)}$ 的，你把 $\sout n$ 乘 $\sout 2$ 和把 $\sout m$ 乘 $\sout 4$ 木有区别~~

~~mmp~~

所以只能去挖掘一下这个 $f$ 的性质，发现有如下两个性质：

- $f(a,b,c,d)=f(c,d,a,b)$
- $f(a,b,c,d)=f(a,b,1,d)-f(a,b,1,c-1)$

前者显然，后者可以这样理解为如果要在 $[1,d]$ 区间内选一个数，那么要么在 $[c,d]$ 里面要么在 $[1,c-1]$ 里面，而且两者的方案是可以加减的。

于是我们就可以转化这个式子。

首先考虑 $u$ 是一段连续区间，$v$ 是两段连续区间的情况。

这时要计算的是 $f(l_1,r_1,1,l_2)+f(l_1,r_1,r_2,n)$。

利用上面的等式可以算出：

$$f(l_1,r_1,1,l_2)+f(l_1,r_1,r_2,n)=g(r_1,l_2)-g(l_1-1,l_2)+g(r_1,n)-g(l_1-1,n)-g(r_1,r_2-1)+g(l_1-1,r_2-1)$$

发现可以预处理 $g(i,n)$，所以实际上这里需要拆的询问只有 $4$ 个。

记 $h(i)=g(i,n)$。

然后考虑都是两段询问的情况。

此时要计算：

$$f(1,l_1,1,l_2)+f(1,l_1,r_2,n)+f(r_1,n,1,l_2)+f(r_1,n,r_2,n)$$

化为下式：

$$g(l_1,l_2)+h(l_1)-g(l_1,r_2-1)+h(l_2)-g(l_2,r_1-1)+h(n)-h(r_1-1)-h(r_2-1)+g(r_1-1,r_2-1)$$

发现依然只需要拆 $4$ 个询问。

所以所有询问都可以只拆 $4$ 个，也就是说算法只带 $2$ 倍时间常数和 $4$ 倍空间常数，那么这道题就做完了~

最终时间 $O(n\sqrt m)$，空间 $O(n+m)$。

然后就是注意莫队块长需要取 $\dfrac{n}{\sqrt m}$ 来达到最优复杂度，直接取 $\sqrt n$ 会导致复杂度升高到 $O((n+m)\sqrt n)$，以及注意查询节点是根的时候的一些细节。

上代码~

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

const int N = 100005, M = 500005;

struct Edge {
	int to, nxt;
	Edge() {
		nxt = -1;
	}
};
Edge e[N << 1];
int n, hd[N], pnt, m, pos[N], qcnt, dfn[N], dep[N], post[N], a[N], b[N], S, fa[N][25], _time, cnt1[N], cnt2[N], atmp[N];
bool isquery[M];
long long ans[M], pref[N], curval; // pref[i] = f(1, i, 1, n)
struct Query {
	int l, r, id;
	Query(int l = 0, int r = 0, int id = 0) : l(l), r(r), id(id) {}
	bool operator < (const Query& b) const {
		return (pos[l] ^ pos[b.l] ? pos[l] < pos[b.l] : (pos[l] & 1 ? r < b.r : r > b.r));
	}
};
Query qry[M << 2];

inline void AddEdge(int u, int v) {
	e[++pnt].to = v;
	e[pnt].nxt = hd[u];
	hd[u] = pnt;
}

inline void Read() {
	n = qread(); m = qread();
	for (register int i = 1;i <= n;i++) b[i] = a[i] = qread();
	for (register int i = 1;i < n;i++) {
		register int u = qread(), v = qread();
		AddEdge(u, v);
		AddEdge(v, u);
	}
}

inline void Dfs(int u) {
	dfn[u] = ++_time;
	atmp[_time] = a[u];
	for (register int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa[u][0]) {
			fa[e[i].to][0] = u;
			dep[e[i].to] = dep[u] + 1;
			Dfs(e[i].to);
		}
	}
	post[u] = _time;
}

inline int Up(int u, int k) {
	for (register int j = 20;j >= 0;j--) {
		if ((k >> j) & 1) u = fa[u][j];
	}
	return u;
}

inline void AddQuery(int l, int r, int i) {
	if (l < 1 || l > n) return;
	if (r < 1 || r > n) return;
	if (l > r) swap(l, r);
	qry[++qcnt] = Query(l, r, i);
}

inline void Prefix() {
	sort(b + 1, b + n + 1);
	register int vtop = unique(b + 1, b + n + 1) - b - 1;
	for (register int i = 1;i <= n;i++) a[i] = lower_bound(b + 1, b + vtop + 1, a[i]) - b;
	for (register int j = 1;j <= 20;j++) {
		for (register int i = 1;i <= n;i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
	}
	for (register int i = 1;i <= n;i++) cnt1[a[i]]++;
	for (register int i = 1;i <= n;i++) pref[i] = pref[i - 1] + cnt1[a[i]];
	register int rt = 1;
	for (register int i = 1;i <= m;i++) {
		register int opt = qread();
		if (opt == 1) rt = qread();
		else {
			isquery[i] = 1;
			register int u = qread(), v = qread(), type = 0;
			if (dfn[u] <= dfn[rt] && dfn[rt] <= post[u]) type |= 2;
			if (dfn[v] <= dfn[rt] && dfn[rt] <= post[v]) type |= 1;
			//printf("T=%d\n", type);
			if (type == 0) {
				register int l1 = dfn[u], r1 = post[u], l2 = dfn[v], r2 = post[v];
				//printf("l1=%d r1=%d l2=%d r2=%d\n", l1, r1, l2, r2);
				AddQuery(r1, r2, i);
				AddQuery(l1 - 1, r2, -i);
				AddQuery(r1, l2 - 1, -i);
				AddQuery(l1 - 1, l2 - 1, i);
			} else if (type == 1) {
				register int l1, r1, l2, r2;
				l1 = dfn[u]; r1 = post[u];
				if (v != rt) {
					register int sv = Up(rt, dep[rt] - dep[v] - 1);
					l2 = dfn[sv] - 1; r2 = post[sv] + 1;
				} else {
					l2 = 0;
					r2 = 1;
				}
				/*
				  f(l1, r1, 1, l2) + f(l1, r1, r2, n)
				= f(1, r1, 1, l2) - f(1, l1 - 1, 1, l2) + f(l1, r1, 1, n) - f(l1, r1, 1, r2 - 1)
				= f(1, r1, 1, l2) - f(1, l1 - 1, 1, l2) + fpre(r1) - fpre(l1 - 1) - f(1, r1, 1, r2 - 1) + f(1, l1 - 1, 1, r2 - 1)
				*/
				ans[i] += pref[r1] - pref[l1 - 1];
				AddQuery(r1, l2, i);
				AddQuery(l1 - 1, l2, -i);
				AddQuery(r1, r2 - 1, -i);
				AddQuery(l1 - 1, r2 - 1, i);
			} else if (type == 2) {
				swap(u, v);
				register int l1, r1, l2, r2;
				l1 = dfn[u]; r1 = post[u];
				if (v != rt) {
					register int sv = Up(rt, dep[rt] - dep[v] - 1);
					l2 = dfn[sv] - 1; r2 = post[sv] + 1;
				} else {
					l2 = 0;
					r2 = 1;
				}
				/*
				  f(l1, r1, 1, l2) + f(l1, r1, r2, n)
				= f(1, r1, 1, l2) - f(1, l1 - 1, 1, l2) + f(l1, r1, 1, n) - f(l1, r1, 1, r2 - 1)
				= f(1, r1, 1, l2) - f(1, l1 - 1, 1, l2) + fpre(r1) - fpre(l1 - 1) - f(1, r1, 1, r2 - 1) + f(1, l1 - 1, 1, r2 - 1)
				*/
				ans[i] += pref[r1] - pref[l1 - 1];
				AddQuery(r1, l2, i);
				AddQuery(l1 - 1, l2, -i);
				AddQuery(r1, r2 - 1, -i);
				AddQuery(l1 - 1, r2 - 1, i);
			} else if (type == 3) {
				register int l1, r1, l2, r2;
				if (u != rt) {
					register int su = Up(rt, dep[rt] - dep[u] - 1);
					l1 = dfn[su] - 1; r1 = post[su] + 1;
				} else {
					l1 = 0;
					r1 = 1;
				}
				if (v != rt) {
					register int sv = Up(rt, dep[rt] - dep[v] - 1);
					l2 = dfn[sv] - 1; r2 = post[sv] + 1;
				} else {
					l2 = 0;
					r2 = 1;
				}
				ans[i] += pref[l1] + pref[l2] + pref[n] - pref[r1 - 1] - pref[r2 - 1];
				AddQuery(l1, r2 - 1, -i);
				AddQuery(l1, l2, i);
				AddQuery(l2, r1 - 1, -i);
				AddQuery(r1 - 1, r2 - 1, i);
			}
		}
	}
}

inline void Addl(int x) {curval += cnt2[x]; cnt1[x]++;}
inline void Dell(int x) {curval -= cnt2[x]; cnt1[x]--;}
inline void Addr(int x) {curval += cnt1[x]; cnt2[x]++;}
inline void Delr(int x) {curval -= cnt1[x]; cnt2[x]--;}

inline void Solve() {
	//for (register int i = 1;i <= n;i++) printf("%d ", a[i]);
	//puts("");
	S = (int)(1.0 * n / sqrt(qcnt));
	for (register int i = 1;i <= n;i++) pos[i] = (i - 1) / S + 1;
	sort(qry, qry + qcnt + 1);
	memset(cnt1, 0, sizeof(cnt1));
	memset(cnt2, 0, sizeof(cnt2));
	register int lp = 0, rp = 0;
	for (register int i = 1;i <= qcnt;i++) {
		//printf("%d %d %d\n", qry[i].l, qry[i].r, qry[i].id);
		while (lp < qry[i].l) Addl(a[++lp]);
		while (rp < qry[i].r) Addr(a[++rp]);
		while (lp > qry[i].l) Dell(a[lp--]);
		while (rp > qry[i].r) Delr(a[rp--]);
		if (qry[i].id > 0) ans[qry[i].id] += curval;
		else ans[-qry[i].id] -= curval;
	}
	for (register int i = 1;i <= m;i++) {
		if (isquery[i]) printf("%lld\n", ans[i]);
	}
}

int main() {
	memset(hd, -1, sizeof(hd));
	Read();
	dep[1] = 1; Dfs(1); memcpy(a, atmp, sizeof(a));
	Prefix();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：FlashHu (赞：11)

具体思路看别的题解吧。这里只提两个可能对常数和代码长度有优化的处理方法。

### I

把一个询问拆成$9$个甚至$16$个莫队询问实在是有点珂怕。

发现询问的一边要么是一个区间，要么是$[1,n]$挖去一个区间。

记$pre_i=f_{[1,i],[1,n]}$，这个可以一遍预处理求出来。

简单容斥一下：

$$f_{[l,r],[1,L)\cup(R,n]}=f_{[l,r],[1,n]}-f_{[l,r],[L,R]}=pre_r-pre_{l-1}-f_{[l,r],[L,R]}$$

$$f_{[1,l)\cup(r,n],[1,L)\cup(R,n]}=f_{[1,n],[1,n]}-f_{[l,r],[1,n]}-f_{[1,n],[L,R]}+f_{[l,r],[L,R]}=...$$

于是对于每个询问，我们拆成$4$个莫队询问就够了，因为只差求$f_{[l,r],[L,R]}$。

### II

如何求某一个点往新根方向上的儿子？树剖倍增什么的都太呆了。

预处理树的dfn序，每个点开一个map按dfn序挂上它所有的儿子，查询时拿着新根的dfn序直接lower_bound即可。

然后就可以2kb写完这道不算太毒瘤的由乃题了。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define RG register
#define R RG int
#define G if(++ip==ie)if(fread(ip=buf,1,SZ,stdin))
using namespace std;
const int SZ=1<<19,N=1e5+9,M=5e5+9;
char buf[SZ],*ie=buf+SZ,*ip=ie-1;
inline int in(){
    G;while(*ip<'-')G;
    R x=*ip&15;G;
    while(*ip>'-'){x*=10;x+=*ip&15;G;}
    return x;
}
struct Qry{
    int x,y,b,id;
    inline bool operator<(const Qry&t)const{
        return b!=t.b?b<t.b:(1&b)?y>t.y:y<t.y;
    }
}t[4*M];
int dfn,a[N],b[N],c1[N],c2[N],l[N],r[N],he[N],ne[2*N],to[2*N];
LL pre[N],ans[M];
map<int,int>ch[N];
void dfs(R x,R f){//预处理dfn序
    l[x]=++dfn;
    for(R y,i=he[x];i;i=ne[i])
        if((y=to[i])!=f)dfs(y,x),ch[x][r[y]]=y;
    r[x]=dfn;
}
int main(){
    R n=in(),m=in(),q=0,B=sqrt(n);
    for(R i=1;i<=n;++i)
        a[i]=b[i]=in();
    for(R i=1,p=0;i<n;++i){
        R x=in(),y=in();
        ne[++p]=he[x];to[he[x]=p]=y;
        ne[++p]=he[y];to[he[y]=p]=x;
    }
    dfs(1,0);
    sort(a+1,a+n+1);
    for(R i=1;i<=n;++i)b[i]=lower_bound(a+1,a+n+1,b[i])-a;
    for(R i=1;i<=n;++i)++c1[a[l[i]]=b[i]];//预处理pre
    for(R i=1;i<=n;++i)pre[i]=pre[i-1]+c1[a[i]];
    for(R i=1,rt=1;i<=m;++i){
        if(in()&1){rt=in();--i;--m;continue;}
        R x=in(),y=in();
        R tx=l[x]<=l[rt]&&r[rt]<=r[x];if(x==rt)x=1,tx=0;
        R ty=l[y]<=l[rt]&&r[rt]<=r[y];if(y==rt)y=1,ty=0;
        if(tx)x=ch[x].lower_bound(l[rt])->second;//map找儿子
        if(ty)y=ch[y].lower_bound(l[rt])->second;
        R lx=l[x]-1,ly=l[y]-1,rx=r[x],ry=r[y];
        if(tx&&ty)ans[i]=pre[n];
        if(tx)ans[i]+=(pre[ry]-pre[ly])*(tx==ty?-1:1);
        if(ty)ans[i]+=(pre[rx]-pre[lx])*(tx==ty?-1:1);
        t[++q]=(Qry){rx,ry,rx/B,tx==ty?i:-i};//四个莫队询问，带上容斥系数
        t[++q]=(Qry){rx,ly,rx/B,tx==ty?-i:i};
        t[++q]=(Qry){lx,ry,lx/B,tx==ty?-i:i};
        t[++q]=(Qry){lx,ly,lx/B,tx==ty?i:-i};
    }
    sort(t+1,t+q+1);
    LL now=0;memset(c1+1,0,4*n);
    for(R i=1,x=0,y=0;i<=q;++i){//莫队
        while(x<t[i].x)++c1[a[++x]],now+=c2[a[x  ]];
        while(x>t[i].x)--c1[a[  x]],now-=c2[a[x--]];
        while(y<t[i].y)++c2[a[++y]],now+=c1[a[y  ]];
        while(y>t[i].y)--c2[a[  y]],now-=c1[a[y--]];
        R j=t[i].id;j>0?ans[j]+=now:ans[-j]-=now;
    }
    for(R i=1;i<=m;++i)
        printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：诗乃 (赞：9)

不难发现换根是假的。以1为根将树拍成dfs序，则：

>1、若x为当前根，则x的子树对应区间为整个dfs序列。

>2、若x在当前根的子树中，则x的子树对应区间为一段连续的区间。

>3、若当前根在x的子树中，则x的子树对应区间为整个序列挖去一段区间。

至此，可以将子树问题转化为序列上的区间问题。

设$ans(l1,r1,l2,r2)$为区间$[l1,r1]$与$[l2,r2]$的答案。
则有：

$$ans(l1,r1,l2,r2)=ans(1,r1,1,r2)+ans(1,l1-1,1,l2-1)-ans(1,r1,1,l1-1)-ans(1,r2,1,l2-1)$$

莫队处理即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 500050;
void read(int &x) {
	char ch; while(ch = getchar(), ch < '!'); x = ch - 48;
	while(ch = getchar(), ch > '!') x = (x << 3) + (x << 1) + ch - 48;
}
void write(lint x) {if(x > 9) write(x/10); putchar(x%10+48);}
struct Edge {int to, next;} e[MAXN];
struct Qry {int l, r, id, f;} q[8000050];
int Q, m, in[MAXN], out[MAXN], idx, _dfn, st[MAXN][21], dfn[MAXN], dep[MAXN], fa[MAXN], h[MAXN], en, rt, cnt[MAXN][2];
int is_q[MAXN], top[MAXN], son[MAXN], siz[MAXN], tl[MAXN], tr[MAXN], o[MAXN], c[MAXN], a[MAXN], n, lg2[MAXN]; lint ans[MAXN], ima, _c, SIZ;
void addedge(int u, int v) {e[en] = (Edge) {v, h[u]}; h[u] = en++;}
bool cmp(Qry a, Qry b) {return a.l/SIZ == b.l/SIZ ? a.r < b.r : a.l < b.l;}
void dfs1(int u, int p) {
	st[++idx][0] = u; in[u] = ++_dfn; dfn[u] = idx; c[_dfn] = a[u];
	dep[u] = dep[p] + 1; fa[u] = p; siz[u] = 1;
	for(int v, i = h[u]; ~i; i = e[i].next)
		if((v = e[i].to) != p) {
			dfs1(v, u); st[++idx][0] = u; siz[u] += siz[v];
			if(siz[v] > siz[son[u]]) son[u] = v;
		}
	out[u] = _dfn;
}
void dfs2(int u, int f) {
	top[u] = f; if(son[u]) dfs2(son[u], f);
	for(int v, i = h[u]; ~i; i = e[i].next)
		if((v = e[i].to) != fa[u] && v != son[u]) dfs2(v, v);
}
int find(int y, int x) {//找x在y的哪个子树内
	int u; for(; top[x] != top[y]; u = top[x], x = fa[u]);
	return x == y ? u : son[y]; 
}
void init() {
	dep[1] = 1; dfs1(1, 1); dfs2(1, 1);
	for(int i = 2; i <= (n << 1); ++i) lg2[i] = lg2[i>>1] + 1;
	for(int j = 1; j <= 21; ++j)
		for(int i = 1; i + (1 << j) - 1 <= (n << 1); ++i)
			st[i][j] = dep[st[i][j-1]] < dep[st[i+(1<<(j-1))][j-1]] ? st[i][j-1] : st[i+(1<<(j-1))][j-1];
}
int LCA(int u, int v) {
	int x = dfn[u], y = dfn[v];
	if(x > y) swap(x, y);
	int k = lg2[y-x+1];
	return dep[st[x][k]] < dep[st[y-(1<<k)+1][k]] ? st[x][k] : st[y-(1<<k)+1][k];
}
void RC(int l1, int r1, int l2, int r2, int id) {//将区间询问转化为几个子问题的容斥
	q[++m] = (Qry) {r1, r2, id, 1}; q[++m] = (Qry) {l1-1, l2-1, id, 1};
	q[++m] = (Qry) {r1, l2-1, id, -1}; q[++m] = (Qry) {l1-1, r2, id, -1};
}
void devide(int x) { //处理x的子树对应的区间
	if(x == rt) tl[++_c] = 1, tr[_c] = n;
	else {
		int z = LCA(x, rt);
		if(z != x) tl[++_c] = in[x], tr[_c] = out[x];
		else {
			int y = find(x, rt);
			if(1 <= in[y]-1) tl[++_c] = 1; tr[_c] = in[y]-1;
			if(out[y]+1 <= n) tl[++_c] = out[y]+1, tr[_c] = n;
		}
	}
}
void build(int x, int y, int id) {//将两个子树问题转化为区间问题
	_c = 0; devide(x); int mid = _c; devide(y);
	for(int i = 1; i <= mid; ++i)
		for(int j = mid+1; j <= _c; ++j)
			RC(tl[i], tr[i], tl[j], tr[j], id);
}
void add(int x, int p) {ima += cnt[c[x]][p^1]; ++cnt[c[x]][p];}
void del(int x, int p) {ima -= cnt[c[x]][p^1]; --cnt[c[x]][p];}
int main() {
	read(n); read(Q); SIZ = sqrt(n); memset(h, -1, sizeof h);
	for(int i = 1; i <= n; ++i) read(a[i]), o[i] = a[i];
	sort(o+1, o+n+1); int _n = unique(o+1, o+n+1)-o-1;
	for(int i = 1; i <= n; ++i) a[i] = lower_bound(o+1, o+_n+1, a[i])-o;
	for(int u, v, i = 1; i < n; ++i) read(u), read(v), addedge(u, v), addedge(v, u);
	init(); rt = 1;
	for(int opt, x, y, i = 1; i <= Q; ++i) {
		read(opt); read(x);
		if(opt == 1) rt = x;
		else is_q[i] = 1, read(y), build(x, y, i);
	}
	for(int i = 1; i <= m; ++i) if(q[i].l > q[i].r) swap(q[i].l, q[i].r);
	sort(q+1, q+m+1, cmp);
	for(int L = 0, R = 0, i = 1; i <= m; ++i) {
		int l = q[i].l, r = q[i].r;
		while(L < l) add(++L, 0); while(L > l) del(L--, 0); 
		while(R < r) add(++R, 1); while(R > r) del(R--, 1);
		ans[q[i].id] += ima * q[i].f;
	}
	for(int i = 1; i <= Q; ++i) if(is_q[i]) write(ans[i]), putchar('\n');
}

```

---

## 作者：ENESAMA (赞：6)

这可能是我见过的最水的黑题了~~（不过蒟蒻我也没做过几道）~~

这道题的思路灰常简单啊

做过bzoj3083和bzoj5016就能熟练拍板子了~~（蓝而我还是没做过）~~

就是对于一个查询的点来说 

如果它是root 那么子树就是整棵树

如果它和root的lca是它本身 

那么去掉它与root的路径上它的那个叶结点的子树

剩下的就是要找的区间 ，而这段区间必定是连续的，所以就是两段区间
 
而其他情况下 要查找的就是它现在的子树

这里有一个dalao的图，虽然丑了点，但是十分形象

https://blog.csdn.net/lcomyn/article/details/45718295

然后可以看出另一个有用的性质

对于dfs序的序列上一个区间[l1,r1]  和[l2,r2]的查询

可以拆分为四个查询来进行

也就是**[1，r1]和[1,r2] + [1,l1-1]和[1,l2-1]- [1,l1-1]和[1,r2]- [1,l2-1]和[1,r1]**

既然已经到了这种地步

发现每个询问可以拆成最多16个由dfs序列的左端点作为左端点的区间

是不是震惊的发现 ：**似乎可以用莫队算法处理！**

然后就变成了一个裸的莫队模版

对了记得要写的好看一点

**这道题超级卡常的！！！**

接下来就是代码了

顺手附赠一组小样例
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int in[100005],out[100005],all,dp[100005][20],dfs_num,l[10],r[10];
int di[100005],pos1,pos2,b[100005],now,to[200005],next[200005];
int head[100005],tot,depth[100005],root,n,tong[100005][2];
int m,shu1,shu2,a[100005],shu,c[100005];
long long ans[500005],ans_here;
bool pd[500005];
struct node
{
    int id,l,r;
    bool judge;
}ask[8000005];
void add(int x,int y)
{
    to[++tot]=y;
    next[tot]=head[x];
    head[x]=tot;
}
void dfs(int x,int fa)
{
    in[x]=++dfs_num;
    c[dfs_num]=a[x];
    dp[x][0]=fa;
    for(int i=1;i<=17;i++)
    {
        dp[x][i]=dp[dp[x][i-1]][i-1];
    }
    for(int i=head[x];i;i=next[i])
    {
        int y=to[i];
        if(y==fa) continue;
        depth[y]=depth[x]+1;
        dfs(y,x);
    }
    out[x]=dfs_num;
}
int lca(int x,int y)
{
    if(depth[x]<depth[y])
    swap(x,y);
    int delta=depth[x]-depth[y];
    for(int i=0;i<=17;i++)
    if(delta&(1<<i))
    {
        x=dp[x][i];
    }
    if(x==y) return x;
    for(int i=17;i>=0;i--)
    if(dp[x][i]!=dp[y][i])
    {
        x=dp[x][i];
        y=dp[y][i];
    }
    return dp[x][0];
}
int find(int x,int y)
{
    if(depth[x]<depth[y])
    swap(x,y);
    int delta=depth[x]-depth[y]-1;
    for(int i=0;i<=17;i++)
    if(delta&(1<<i))
    {
        x=dp[x][i];
    }
    return x;
}
void add_query(int x,int y,int id)
{
    int cnt=0;
    if(x==root) l[++cnt]=1,r[cnt]=n;
    else
    {
        int temp=lca(x,root);
        if(temp!=x) l[++cnt]=in[x],r[cnt]=out[x];
        else 
        {
            int now=find(x,root);
            l[++cnt]=1,r[cnt]=in[now]-1;
            if(l[cnt]>r[cnt]) cnt--;
            l[++cnt]=out[now]+1,r[cnt]=n;
            if(l[cnt]>r[cnt]) cnt--;
        }
    }
    int mid=cnt;
    if(y==root) l[++cnt]=1,r[cnt]=n;
    else
    {
        int temp=lca(y,root);
        if(temp!=y) l[++cnt]=in[y],r[cnt]=out[y];
        else 
        {
            int now=find(y,root);
            l[++cnt]=1,r[cnt]=in[now]-1;
            if(l[cnt]>r[cnt]) cnt--;
            l[++cnt]=out[now]+1,r[cnt]=n;
            if(l[cnt]>r[cnt]) cnt--;
        }
    }
    for(int i=1;i<=mid;i++)
    {
        for(int j=mid+1;j<=cnt;j++)
        {//尽量不要用构造函数，一位机房的同学因此TLE了三个点
            ask[++all].l=r[i],ask[all].id=id,ask[all].r=r[j],ask[all].judge=true;
            ask[++all].l=l[i]-1,ask[all].id=id,ask[all].r=l[j]-1,ask[all].judge=true;
            ask[++all].l=r[i],ask[all].id=id,ask[all].r=l[j]-1,ask[all].judge=false;
            ask[++all].l=l[i]-1,ask[all].id=id,ask[all].r=r[j],ask[all].judge=false;
        }
    }
}
bool cmp(const node &a,const node &b)
{
    if(di[a.l]!=di[b.l])
    return di[a.l]<di[b.l];
    return a.r<b.r;
}
void ad(int x,int kind)
{
    int y=c[x];
    ans_here+=tong[y][kind^1];
    tong[y][kind]++;
}
void de(int x,int kind)
{
    int y=c[x];
    ans_here-=tong[y][kind^1];
    tong[y][kind]--;
}
int read()
{
    char c;
    int x;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    x=c-'0';
    for(c=getchar();c>='0'&&c<='9';c=getchar())
    x=x*10+c-'0';
    return x;
}
int main()
{
    cin>>n>>m;
    int piece=sqrt(n);
    for(int i=1;i<=n;i++)
    {
        di[i]=(i-1)/piece+1;
    }
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        b[i]=a[i];
    }
    for(int i=1;i<=n-1;i++)
    {
        shu1=read();
        shu2=read();
        add(shu1,shu2);
        add(shu2,shu1);
    }
    depth[1]=1;
    root=1;
    sort(b+1,b+n+1);
    now=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)
    a[i]=lower_bound(b+1,b+n+1,a[i])-b; //预先处理出离散化后的数组
    dfs(1,1);
    for(int i=1;i<=m;i++)
    {
        shu=read();
        if(shu==1)
        {
            shu1=read();
            root=shu1;
        }
        else 
        {
            shu1=read();
            shu2=read();
            add_query(shu1,shu2,i);
            pd[i]=true;
        }
    }
    for(int i=1;i<=all;i++)
    {
        if(ask[i].l>ask[i].r) swap(ask[i].l,ask[i].r);
    }
    sort(ask+1,ask+all+1,cmp);
    pos1=0;
    pos2=0;
    for(int i=1;i<=all;i++)
    {
        while(pos1<ask[i].l) ad(++pos1,0);
        while(pos1>ask[i].l) de(pos1--,0);
        while(pos2<ask[i].r) ad(++pos2,1);
        while(pos2>ask[i].r) de(pos2--,1);
        if(ask[i].judge)
        ans[ask[i].id]+=ans_here;
        else ans[ask[i].id]-=ans_here;
    }
    for(int i=1;i<=m;i++)
    if(pd[i])
    {
        printf("%lld\n",ans[i]);
    }
    return 0;
} 
/*
10 10
36088 87629 24511 26212 51285 80251 18887 5484 17567 41736 
1 10
1 4
10 3
10 6
3 2
6 7
4 8
2 5
2 9
2 4 9
2 7 2
2 8 10
1  2
1  6
1  8
1  7
2 3 4
2 10 6
1  10
*/
```

---

## 作者：徐致远 (赞：4)

### 广告  

[本蒟蒻的Blog](https://www.chnxuzhiyuan.cn/2019/03/06/%E3%80%8CYNOI2016%E3%80%8D%E8%BF%99%E6%98%AF%E6%88%91%E8%87%AA%E5%B7%B1%E7%9A%84%E5%8F%91%E6%98%8E-Solution/)

### 题解

又是一道由乃OI的毒瘤题QwQ。

前置技能，这题的简化版：[SNOI2017 一个简单的询问](https://www.chnxuzhiyuan.cn/2019/03/04/%E3%80%8CSNOI2017%E3%80%8D%E4%B8%80%E4%B8%AA%E7%AE%80%E5%8D%95%E7%9A%84%E8%AF%A2%E9%97%AE-Solution/)。

做完上面一题，不难发现，只要爬到树上做这题就行了。

先~~一巴掌把树拍扁~~按照DFS序将树化成一个序列，这样每一颗子树对应着序列上的一段区间，然后就和之前那一题没什么区别了。

但是！！！竟然有换根这种操作。

不过不难发现，其实换根的操作就是假的。

先设当前的根为$rt$，询问子树的节点为$x$，不管怎样，我们就认为根始终是节点$1$。

然后又这么几种情况：

- $x=rt$

此时询问的就是整棵树。

![1.png](https://www.chnxuzhiyuan.cn/images/%E3%80%8CYNOI2016%E3%80%8D%E8%BF%99%E6%98%AF%E6%88%91%E8%87%AA%E5%B7%B1%E7%9A%84%E5%8F%91%E6%98%8E-1.png)

- $LCA(x,rt)\neq x$

此时查询的就是当$1$为根时$x$的子树。

![2.png](https://www.chnxuzhiyuan.cn/images/%E3%80%8CYNOI2016%E3%80%8D%E8%BF%99%E6%98%AF%E6%88%91%E8%87%AA%E5%B7%B1%E7%9A%84%E5%8F%91%E6%98%8E-2.png)

- $LCA(x,rt)=x$

![3.png](https://www.chnxuzhiyuan.cn/images/%E3%80%8CYNOI2016%E3%80%8D%E8%BF%99%E6%98%AF%E6%88%91%E8%87%AA%E5%B7%B1%E7%9A%84%E5%8F%91%E6%98%8E-3.png)

此时查询整棵树除去rt到x路径上离x最近的一个节点（就是图中好几个箭头指的那个点）的子树。可以拆成两个序列解决。那个节点可以通过倍增找到。

拆分成若干个序列之后，直接莫队即可。

还有记得要离散，权值是比较大的。~~我就因为没看数据范围，忘记离散，结果崩掉1个点QwQ~~

### 代码

```cpp
#include<map>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100005,maxm=500005;
int n,m,q,rt,idx,tot,lnk[maxn],son[maxn*2],nxt[maxn*2],St[maxn],En[maxn],father[maxn][20],dep[maxn],A[maxn],B[maxn],S,Area[maxn],num,cnt1[maxn],cnt2[maxn],p1,p2;LL ans[maxm],now;   //要开的东西实在太多，写的好丑QwQ
map<int,int> hsh;
inline int read()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
inline void add_e(int x,int y){tot++;son[tot]=y;nxt[tot]=lnk[x];lnk[x]=tot;}
void Build(int now,int fa)        //以节点1作为根节点初始化
{
	father[now][0]=fa;dep[now]=dep[fa]+1;idx++;A[idx]=B[now];St[now]=idx;
	for(int i=1;i<=16;i++) father[now][i]=father[father[now][i-1]][i-1];
	for(int i=lnk[now];i;i=nxt[i])
		if(son[i]!=fa)
			Build(son[i],now);
	En[now]=idx;
}
int LCA(int u,int v)              //倍增LCA
{
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=16;i>=0;i--) if(dep[father[u][i]]>=dep[v]) u=father[u][i];
	for(int i=16;i>=0;i--) if(father[u][i]!=father[v][i]){u=father[u][i];v=father[v][i];}
	if(u!=v) return father[u][0];
	return u;
}
int GetSon(int u,int v)
{
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=16;i>=0;i--) if(dep[father[u][i]]>dep[v]) u=father[u][i];
	return u;
}
struct Interval
{
	int R1,R2,f,id;
	void Init(){if(R1>R2)swap(R1,R2);}
	bool operator < (const Interval& b)const{return Area[R1]<Area[b.R1]||(Area[R1]==Area[b.R1]&&((Area[R1]&1)?R2<b.R2:R2>b.R2));}
}Q[maxm*16];            //注意一个询问最左可以拆成16个区间
inline void Add(int L1,int R1,int L2,int R2,int id)
{
	num++;Q[num].R1=R1;Q[num].R2=R2;Q[num].f=1;Q[num].Init();Q[num].id=id;
	if(L1>1){num++;Q[num].R1=L1-1;Q[num].R2=R2;Q[num].f=-1;Q[num].Init();Q[num].id=id;}
	if(L2>1){num++;Q[num].R1=R1;Q[num].R2=L2-1;Q[num].f=-1;Q[num].Init();Q[num].id=id;}
	if(L1>1&&L2>1){num++;Q[num].R1=L1-1;Q[num].R2=L2-1;Q[num].f=1;Q[num].Init();Q[num].id=id;}
}
int main()
{
	n=read();m=read();S=sqrt(n)+1e-10;rt=1;
	for(int i=1;i<=n;i++) A[i]=B[i]=read();
	sort(B+1,B+1+n);int tep=0;
	for(int i=1;i<=n;i++) if(!hsh[B[i]]) hsh[B[i]]=++tep;
	for(int i=1;i<=n;i++) B[i]=hsh[A[i]];                //离散
	for(int i=1;i<=n;i++) Area[i]=(i-1)/S+1;
	for(int i=1;i<n;i++)
	{
		int a=read(),b=read();
		add_e(a,b);add_e(b,a);
	}
	Build(1,0);
	for(int i=1;i<=m;i++)
	{
		if(read()==1) rt=read();
		else
		{
			int x=read(),y=read();q++;
			int len1=0,L1[3],R1[3],len2=0,L2[3],R2[3];
			if(x==rt){len1++;L1[len1]=1;R1[len1]=n;}
			else if(LCA(x,rt)!=x){len1++;L1[len1]=St[x];R1[len1]=En[x];}
			else{int v=GetSon(rt,x);len1++;L1[len1]=1;R1[len1]=St[v]-1;if(En[v]<n){len1++;L1[len1]=En[v]+1;R1[len1]=n;}}
			if(y==rt){len2++;L2[len2]=1;R2[len2]=n;}
			else if(LCA(y,rt)!=y){len2++;L2[len2]=St[y];R2[len2]=En[y];}
			else{int v=GetSon(rt,y);len2++;L2[len2]=1;R2[len2]=St[v]-1;if(En[v]<n){len2++;L2[len2]=En[v]+1;R2[len2]=n;}}
			for(int j=1;j<=len1;j++)	
				for(int k=1;k<=len2;k++)
					Add(L1[j],R1[j],L2[k],R2[k],q);          //拆成区间上莫队
		}
	}
	sort(Q+1,Q+1+num);                //莫队
	for(int i=1;i<=num;i++)
	{
		while(p2<Q[i].R2){p2++;cnt2[A[p2]]++;now+=cnt1[A[p2]];}
		while(p1>Q[i].R1){cnt1[A[p1]]--;now-=cnt2[A[p1]];p1--;}
		while(p2>Q[i].R2){cnt2[A[p2]]--;now-=cnt1[A[p2]];p2--;}
		while(p1<Q[i].R1){p1++;cnt1[A[p1]]++;now+=cnt2[A[p1]];}
		ans[Q[i].id]+=now*Q[i].f;
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```



---

## 作者：Taduro (赞：3)

一句话题意：求区间相同颜色的数对数，上树做，要求支持换根。

在做这题之前我见过[[Snoi2017]一个简单的询问](https://www.lydsy.com/JudgeOnline/problem.php?id=5016)，所以如果这是一个序列上的问题的话：

$f(l1,r1,l2,r2)$表示询问l1,r1,l2,r2的答案，显然四个关键字不能莫队，但是我们可以容斥。
$$
f(l1,r1,l2,r2)=f(1,r1,1,r2)-f(1,l1-1,l2,r2)-f(l1,r1,l2-1,r2)+f(1,l1-1,1,l2-1)
$$
很多问你两个区间满足什么条件的数对数都可以容斥成这样，比如[[HAOI2011 Problem b]](https://www.luogu.org/problemnew/show/P2522)。

这样一个询问就只有两个关键字了。

在树上的做法：

因为有换根的操作，所以可能会是一个区间对多个区间甚至多个区间对多个区间。

例如：三个区间[l1,r1],[l2,r2],[l3,r3]和三个个区间[l1‘,r1’],[l2',r2'],[l3',r3']中的答案数。

把两边区间每一对都对应即可，就是3*3=9个询问。

换根的话分类讨论，如果新根不在x的子树内相安无事，否则x子树的区间就是除了**x向新根那个方向的**儿子的子树，以外的所有点，dfs序搞一搞就好了。

```c++
#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
#ifdef ONLINE_JUDGE
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){if(A==B){B=(A=ss)+fread(ss,1,1<<17,stdin);if(A==B)return EOF;}return*A++;}
template<class T>inline void read(T&x){
    static char c;static int y;
    for(c=gc(),x=0,y=1;c<48||57<c;c=gc())if(c=='-')y=-1;
    for(;48<=c&&c<=57;c=gc())x=((x+(x<<2))<<1)+(c^'0');
    x*=y;
}
#else
void read(int&x){scanf("%d",&x);}
#endif
struct node{
	int next,to;
}w[400001];
struct ques{
	int h,l,r,f;
}q[8000011];
struct ls{
	int h,z;
}a[100001];
int rt,now,num,hs[100001],head[100001],idx[100001],size[100001];
int r,lx[201],n,b[100001],dfn[100001],fa[100001],bl[100001],cnt;
int m,l,ly[201],o[100001][2],que,fx[201],fy[201],blo,top[100001];
ll ans[500001],sum;
inline bool cmp2(ls c,ls d){return c.z<d.z;}
inline bool cmp(ques c,ques d){
	if (bl[c.l]!=bl[d.l]) return c.l<d.l;
	if (bl[c.l]&1) return c.r<d.r;
	else return c.r>d.r;
	// return (c.r<d.r)^(bl[c.l]&1)^1;
}
inline void add_edge(int x,int y){
	w[++cnt].next=head[x];
	w[cnt].to=y; head[x]=cnt;
}
void dfs1(int x,int da){
	dfn[++num]=b[x]; idx[x]=num; size[x]=1;
	for (int i=head[x]; i; i=w[i].next){
		if (w[i].to!=da){
			fa[w[i].to]=x;
			dfs1(w[i].to,x);
			size[x]+=size[w[i].to];
			if (size[w[i].to]>size[hs[x]]) hs[x]=w[i].to;
		}
	}
}
void dfs2(int x,int tp){
	top[x]=tp;
	if (hs[x]) dfs2(hs[x],tp);
	// top[x]=x;
	for (int i=head[x]; i; i=w[i].next)
		if (w[i].to!=hs[x]&&w[i].to!=fa[x])
			dfs2(w[i].to,w[i].to);
}
inline int find(int y,int x){
	int u;
	while (top[x]!=top[y]) u=top[x],x=fa[u];
	if (x==y) return u; return hs[y];
}
inline void build(int x,int y){
	int nx=0,ny=0;
	int l1=idx[x],r1=idx[x]+size[x]-1;
	int l2=idx[y],r2=idx[y]+size[y]-1;
	if (x==rt) lx[++nx]=n,fx[nx]=1;
	else
		if (idx[x]<=idx[rt]&&idx[rt]<=idx[x]+size[x]-1){
			int z=find(x,rt);
			lx[++nx]=idx[z]-1; fx[nx]=1;
			lx[++nx]=idx[z]+size[z]-1; fx[nx]=-1;
			lx[++nx]=n; fx[nx]=1;
		}
		else{
			lx[++nx]=r1; fx[nx]=1;
			lx[++nx]=l1-1; fx[nx]=-1;
		}
	if (y==rt) ly[++ny]=n,fy[ny]=1;
	else
		if (idx[y]<=idx[rt]&&idx[rt]<=idx[y]+size[y]-1){
			int z=find(y,rt);
			ly[++ny]=idx[z]-1; fy[ny]=1;
			ly[++ny]=idx[z]+size[z]-1; fy[ny]=-1;
			ly[++ny]=n; fy[ny]=1;
		}
		else{
			ly[++ny]=r2; fy[ny]=1;
			ly[++ny]=l2-1; fy[ny]=-1;
		}
	for (int i=1; i<=nx; i++)
		for (int j=1; j<=ny; j++)
			if (lx[i]&&ly[j])
				q[++que].h=now,q[que].l=lx[i],q[que].r=ly[j],q[que].f=fx[i]*fy[j];
}
inline void add(int x,int y){o[dfn[x]][y]++; sum+=o[dfn[x]][y^1];}
inline void del(int x,int y){o[dfn[x]][y]--; sum-=o[dfn[x]][y^1];}
int main(){
	int x,y,opt;
	read(n),read(m);
	for (int i=1; i<=n; i++) read(a[i].z),a[i].h=i;
	sort(a+1,a+n+1,cmp2);
	for (int i=1; i<=n; i++){
		b[a[i].h]=b[a[i-1].h]; if (a[i].z!=a[i-1].z) b[a[i].h]++;
	}

	// puts("dllxl");
	for (int i=1; i<n; i++){
		read(x),read(y);
		add_edge(x,y); add_edge(y,x);
	}
	dfs1(1,0); dfs2(1,1); rt=1;
	for (int i=1; i<=m; i++){
		read(opt);
		if (opt==1) read(rt);
		else{
			read(x),read(y);
			now++; build(x,y);
		}
	}
	blo=sqrt(n);
	for (int i=1; i<=n; i++) bl[i]=(i-1)/blo+1;
	sort(q+1,q+que+1,cmp);//	return 0;
	for (int i=1; i<=que; i++){
		while (l<q[i].l) l++,add(l,0);
		while (l>q[i].l) del(l,0),l--;
		while (r<q[i].r) r++,add(r,1);
		while (r>q[i].r) del(r,1),r--;
		ans[q[i].h]+=sum*q[i].f;
	}
	for (int i=1; i<=now; i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Owen_codeisking (赞：2)

# [更好的阅读体验戳这里](https://www.cnblogs.com/owencodeisking/p/10003463.html)

话说这道题数据是不是都是链啊，我不手动扩栈就全 $RE$...

不过 $A$ 了这题还是很爽的，通过昨晚到今天早上的奋斗，终于肝出了这题

其实楼上说的也差不多了，就是把区间拆掉然后莫队瞎搞

弱化版：[bzoj [SNOI2017]一个简单的询问](https://www.lydsy.com/JudgeOnline/problem.php?id=5016)

那我先讲弱化版吧

可以发现 
$$\sum_{x=0}^{inf}get(l_1,r_1,x)\times get(l_2,r_2,x)=\sum_{x=0}^{inf}get(0,r_1,x)\times get(0,r_2,x)-\sum_{x=0}^{inf}get(0,l_1-1,x)\times get(0,r_2,x)$$
$$-\sum_{x=0}^{inf}get(0,r_1,x)\times get(0,l_2-1,x)+\sum_{x=0}^{inf}get(0,l_1-1,x)\times get(0,l_2-1,x)$$

我们对上面的式子直接上莫队，开两个数组统计即可

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=100000+10;
int n,m,a[maxn],b[maxn],c[maxn],tot,blo;ll ans[maxn],now;

struct Query{
	int l,r,id,v;
}q[maxn<<2];

bool cmp(Query a,Query b){
	if((a.l-1)/blo!=(b.l-1)/blo)
		return (a.l-1)/blo<(b.l-1)/blo;
	return a.r<b.r;
}

inline int read(){
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

inline void addb(int x){now+=(ll)c[a[x]];b[a[x]]++;}
inline void delb(int x){now-=(ll)c[a[x]];b[a[x]]--;}
inline void addc(int x){now+=(ll)b[a[x]];c[a[x]]++;}
inline void delc(int x){now-=(ll)b[a[x]];c[a[x]]--;}

int main()
{
	n=read();blo=sqrt(n);
	for(int i=1;i<=n;i++) a[i]=read();
	m=read();
	int l1,r1,l2,r2;
	for(int i=1;i<=m;i++){
		l1=read(),r1=read(),l2=read(),r2=read();
		q[++tot]=(Query){r1,r2,i,1};
		if(l1>1) q[++tot]=(Query){l1-1,r2,i,-1};
		if(l2>1) q[++tot]=(Query){l2-1,r1,i,-1};
		if(l1>1&&l2>1) q[++tot]=(Query){l1-1,l2-1,i,1};	
	}
	sort(q+1,q+tot+1,cmp);
	int L=0,R=0;
	for(int i=1;i<=tot;i++){
		while(L<q[i].l) addb(++L);
		while(L>q[i].l) delb(L--);
		while(R<q[i].r) addc(++R);
		while(R>q[i].r) delc(R--);
		ans[q[i].id]+=(ll)q[i].v*now;
	}
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```

然后写完弱化版就来做这题了……我的代码洛谷 $AC$，$bzoj\ AC$，$loj\ TLE$，强行上 $fread\ fwrite$ 才卡过去

其实这道题差不多，转化为 $dfs$ 序，然后类似树剖换根的思想分类讨论：

1、$x=rt$ 

2、$rt$ 在以 $1$ 为根时 $x$ 的子树中

3、$rt$ 不在以 $1$ 为根时 $x$ 的子树中

然后第一种和第三种情况比较简单，第二种情况要找 $rt$ 在哪里，我用的树剖，其实还可以用倍增，转化为两段区间，然后合并 $x$ 的区间和 $y$ 的区间

那么就要分九种情况讨论了 ~~怪不得lxl的题目那么毒瘤~~

严重压行后 $91$ 行，还是比较清爽的

$Code\ Below:$

```cpp
#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=100000+10;
int n,m,rt=1,a[maxn],mp[maxn],b[maxn],c[maxn],cnt,blo,t;ll ans[maxn*5],now;
int top[maxn],siz[maxn],son[maxn],fa[maxn],id[maxn],head[maxn],to[maxn<<1],nxt[maxn<<1],tot,tim;
struct Query{int l,r,id,v;}q[maxn*80];
bool cmp(Query a,Query b){return ((a.l-1)/blo!=(b.l-1)/blo)?((a.l-1)/blo<(b.l-1)/blo):(a.r<b.r);}
inline int read(){
    register int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return (f==1)?x:-x;
}
inline void add(int x,int y){to[++tot]=y;nxt[tot]=head[x];head[x]=tot;}
void dfs1(int x,int f){
    siz[x]=1;fa[x]=f;int maxson=-1;
    for(int i=head[x];i;i=nxt[i])
        if(to[i]!=f){
            dfs1(to[i],x);siz[x]+=siz[to[i]];
            if(maxson<siz[to[i]]) maxson=siz[to[i]],son[x]=to[i];
        }
}
void dfs2(int x,int topf){
    id[x]=++tim;mp[tim]=a[x];top[x]=topf;
    if(son[x]) dfs2(son[x],topf);
    for(int i=head[x];i;i=nxt[i])
        if(to[i]!=fa[x]&&to[i]!=son[x]) dfs2(to[i],to[i]);
}
inline int getson(int x,int y){
    while(top[x]!=top[y]){x=top[x];if(fa[x]==y) return x;x=fa[x];}
    return son[y];
}
inline void addb(int x){now+=(ll)c[mp[x]];b[mp[x]]++;}
inline void delb(int x){now-=(ll)c[mp[x]];b[mp[x]]--;}
inline void addc(int x){now+=(ll)b[mp[x]];c[mp[x]]++;}
inline void delc(int x){now-=(ll)b[mp[x]];c[mp[x]]--;}
inline void Add(int l1,int r1,int l2,int r2,int id){
    if(l1<1||l2<1||r1>n||r2>n||l1>r1||l2>r2) return ;
    q[++cnt]=(Query){r1,r2,id,1};
    if(l1>1) q[++cnt]=(Query){l1-1,r2,id,-1};
    if(l2>1) q[++cnt]=(Query){l2-1,r1,id,-1};
    if(l1>1&&l2>1) q[++cnt]=(Query){l1-1,l2-1,id,1};	
}
int main()
{
    n=read(),m=read();blo=sqrt(n);
    int i,opt,x,y,z,l1,r1,j=0,L=0,R=0;
    for(i=1;i<=n;i++) mp[i]=a[i]=read();
    sort(mp+1,mp+n+1);t=unique(mp+1,mp+n+1)-mp-1;
    for(i=1;i<=n;i++) a[i]=lower_bound(mp+1,mp+t+1,a[i])-mp;
    for(i=1;i<n;i++){x=read(),y=read();add(x,y);add(y,x);}
    dfs1(rt,0);dfs2(rt,rt);
    for(i=1;i<=m;i++){
        opt=read();
        if(opt==1) rt=read();
        if(opt==2){
            j++;x=read(),y=read();
            if(x==rt){
                if(y==rt) Add(1,n,1,n,j);
                else if(id[y]<id[rt]&&id[rt]+siz[rt]<=id[y]+siz[y]) 
                    z=getson(rt,y),Add(1,n,1,id[z]-1,j),Add(1,n,id[z]+siz[z],n,j);
                else Add(1,n,id[y],id[y]+siz[y]-1,j);
            }
            else if(id[x]<id[rt]&&id[rt]+siz[rt]<=id[x]+siz[x]){
                z=getson(rt,x);l1=id[z];r1=id[z]+siz[z]-1;
                if(y==rt) Add(1,l1-1,1,n,j),Add(r1+1,n,1,n,j);
                else if(id[y]<id[rt]&&id[rt]+siz[rt]<=id[y]+siz[y])
                    z=getson(rt,y),Add(1,l1-1,1,id[z]-1,j),Add(1,l1-1,id[z]+siz[z],n,j),Add(r1+1,n,1,id[z]-1,j),Add(r1+1,n,id[z]+siz[z],n,j);
                else Add(1,l1-1,id[y],id[y]+siz[y]-1,j),Add(r1+1,n,id[y],id[y]+siz[y]-1,j);
            }
            else {
                if(y==rt) Add(id[x],id[x]+siz[x]-1,1,n,j);
                else if(id[y]<id[rt]&&id[rt]+siz[rt]<=id[y]+siz[y])
                    z=getson(rt,y),Add(id[x],id[x]+siz[x]-1,1,id[z]-1,j),Add(id[x],id[x]+siz[x]-1,id[z]+siz[z],n,j);
                else Add(id[x],id[x]+siz[x]-1,id[y],id[y]+siz[y]-1,j);
            }
        }
    }
    sort(q+1,q+cnt+1,cmp);
    for(i=1;i<=cnt;i++){
        while(L<q[i].l) addb(++L);
        while(L>q[i].l) delb(L--);
        while(R<q[i].r) addc(++R);
        while(R>q[i].r) delc(R--);
        ans[q[i].id]+=(ll)q[i].v*now;
    }
    for(i=1;i<=j;i++) printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：juju527 (赞：1)

### [[Ynoi2016]这是我自己的发明](https://www.luogu.com.cn/problem/P4689)

先看弱化版[[Snoi2017]一个简单的询问](http://www.lydsy.com/JudgeOnline/problem.php?id=5016)

我们设$f(l_1,r_1,l_2,r_2)$为区间$[l_1,r_1]$和$[l_2,r_2]$中各取一个的权值相同情况总数

但4元我们不好处理

容斥

$f(l_1,r_1,l_2,r_2)=f(1,r_1,1,r_2)-f(1,l_2-1,1,r_1)-f(1,l_1-1,1,r_2)+f(1,l_1-1,1,l_2-1)$

这样的话每一个f就只有两元了

我们用图来形象的看一看这个容斥

![](https://s1.ax1x.com/2020/04/02/GtVQRH.png)

我们首先计算了两个紫色区间的f

那么，棕色区间([1,l2-1])和绿色区间([1,r1])的f是我们不应该计算的

同理[1,l1-1]和[1,r2]是我们不该计算的

两个均减去的话，把[1,l1-1]和[1,l2-1]的f减了两遍，加回来即可

然后对于区间1统计某数字个数的问题我们用普通莫队解决

我们发现我们需要计算的都是f(1,x,1,y)这个形式

不妨设x小于y

对于一个数字k，它对答案的贡献即[1,x]内k数量乘以[1,y]内k数量

设s1=[1,x]内k数量,s2=[1,y]内k数量

在莫队l指针向左时，某个k的s1应该减少1，所有s2不变，对答案贡献-s2

l指针向右，某个k的s1应该增加1，所有s2不变，对答案贡献s2

在莫队r指针向左时，某个k的s2应该减少1，所有s1不变，对答案贡献-s1

r指针向右，某个k的s2应该增加1，所有s1不变，对答案贡献s1

我们拿两个数组记录数量就好了

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=50005,maxm=50005;
int block;
struct Query{
	int id,x,y;
	bool operator <(Query i)const{
		return ((x-1)/block==(i.x-1)/block)?y<i.y:x<i.x;
	}
}q[4*maxm];
int a[maxn];
long long ans=0;
int cnt1[maxn],cnt2[maxn];
long long ANS[maxm];
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
void ins1(int x){
	ans+=cnt2[a[x]];
	cnt1[a[x]]++;
	return ;
}
void ins2(int x){
	ans+=cnt1[a[x]];
	cnt2[a[x]]++;
	return ;
}
void del1(int x){
	ans-=cnt2[a[x]];
	cnt1[a[x]]--;
	return ;
}
void del2(int x){
	ans-=cnt1[a[x]];
	cnt2[a[x]]--;
	return ;
}
int main(){
	int n,m,Q=0;
	n=read();
	block=sqrt(n);
	for(int i=1;i<=n;i++)a[i]=read();
	m=read();
	for(int i=1;i<=m;i++){
		int l1,r1,l2,r2;
		l1=read();r1=read();l2=read();r2=read();
		Q++;q[Q].id=i;q[Q].x=r1;q[Q].y=r2;
		if(q[Q].x>q[Q].y)swap(q[Q].x,q[Q].y);
		Q++;q[Q].id=-i;q[Q].x=l2-1;q[Q].y=r1;
		if(q[Q].x>q[Q].y)swap(q[Q].x,q[Q].y);
		Q++;q[Q].id=-i;q[Q].x=l1-1;q[Q].y=r2;
		if(q[Q].x>q[Q].y)swap(q[Q].x,q[Q].y);
		Q++;q[Q].id=i;q[Q].x=l1-1;q[Q].y=l2-1;
		if(q[Q].x>q[Q].y)swap(q[Q].x,q[Q].y);
	}
	sort(q+1,q+Q+1);
	int l=0,r=0;
	for(int i=1;i<=Q;i++){
		int id=q[i].id,x=q[i].x,y=q[i].y;
		while(l<x)ins2(++l);
		while(l>x)del2(l--);
		while(r<y)ins1(++r);
		while(r>y)del1(r--);
		ANS[abs(id)]+=(id<0?-ans:ans);
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ANS[i]);
	return 0;
}

```

我们看到这一题

需要两种操作

换根和询问两颗子树内点权相等情况总数

我们考虑用一个dfs求出dfs序

我们知道一棵子树x的所有点在dfs序上的位置是[dfn[x],dfn[x]+son[x]-1]

dfn[x]是x的dfs序，son[x]是x的子树大小

而换根对于一个x只有两种情况

即根在x的子树里（指根为1时树的形态中）和不在

在时，不难发现，x的子树会变成所有节点除去x的某个儿子的子树

这个儿子是根往x走的最后一个节点

不在x子树里就什么也不会发生，x的子树还是x的子树

由于区间要么是某棵子树，要么是全部节点去掉某棵子树

我们把dfs序复制一遍粘后面

暴政一定能变成一个区间

然后就按弱化版的方法搞即可

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005,maxm=500005;
int block;
struct Query{
	int id,x,y;
	bool operator <(Query i)const{
		return ((x-1)/block==(i.x-1)/block)?y<i.y:x<i.x;
	}
}q[4*maxm];
struct node{
	int id,val;
	bool operator <(node i)const{
		return val<i.val;
	}
}b[maxn];
struct Edge{
	int to;
	int nxt;
}e[2*maxn];
int cnt;
int head[maxn];
int dfsnum;
int a[maxn];
int c[2*maxn],dfn[maxn],son[maxn];
int dep[maxn],f[maxn][21];
long long ans=0;
int cnt1[maxn],cnt2[maxn];
long long ANS[maxm];
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
void add(int u,int v){
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt++;
	return ;
}
void dfs(int x,int fa){
	dfn[x]=++dfsnum;
	c[dfsnum]=x;
	son[x]=1;
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	for(int i=1;i<=20;i++)f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i!=-1;i=e[i].nxt){
		int tmp=e[i].to;
		if(tmp==fa)continue;
		dfs(tmp,x);
		son[x]+=son[tmp];
	}
	return ;
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if(x==y)return x;
	for(int i=20;i>=0;i--)
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	return f[x][0];
}
int get(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[f[x][i]]>dep[y])
			x=f[x][i];
	return x;
}
void ins1(int x){
	ans+=cnt2[a[c[x]]];
	cnt1[a[c[x]]]++;
	return ;
}
void ins2(int x){
	ans+=cnt1[a[c[x]]];
	cnt2[a[c[x]]]++;
	return ;
}
void del1(int x){
	ans-=cnt2[a[c[x]]];
	cnt1[a[c[x]]]--;
	return ;
}
void del2(int x){
	ans-=cnt1[a[c[x]]];
	cnt2[a[c[x]]]--;
	return ;
}
int main(){
	int n,m,Q=0;
	n=read();m=read();
	block=sqrt(2*n);
	memset(head,-1,sizeof(head));
	for(int i=1;i<=n;i++){b[i].id=i;b[i].val=read();}
	sort(b+1,b+n+1);
	int w=0;
	b[0].val=0;
	for(int i=1;i<=n;i++){
		if(b[i].val>b[i-1].val)w++;
		a[b[i].id]=w;
	}
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=n+1;i<=2*n;i++)c[i]=c[i-n];
	int rt=1;
	for(int i=1;i<=m;i++){
		int opt,x,y;
		int l1,r1,l2,r2,u;
		opt=read();x=read();
		if(opt==1){rt=x;ANS[i]=-1;}
		else{
			y=read();
			if(rt==x)l1=1,r1=n;
			else if(lca(rt,x)!=x)l1=dfn[x],r1=dfn[x]+son[x]-1;
			else{
				u=get(rt,x);
				l1=dfn[u]+son[u];r1=n+dfn[u]-1;
			}
			if(rt==y)l2=1,r2=n;
			else if(lca(rt,y)!=y)l2=dfn[y],r2=dfn[y]+son[y]-1;
			else{
				u=get(rt,y);
				l2=dfn[u]+son[u];r2=n+dfn[u]-1;
			}
			Q++;q[Q].id=i;q[Q].x=r1;q[Q].y=r2;
			if(q[Q].x>q[Q].y)swap(q[Q].x,q[Q].y);
			Q++;q[Q].id=-i;q[Q].x=l2-1;q[Q].y=r1;
			if(q[Q].x>q[Q].y)swap(q[Q].x,q[Q].y);
			Q++;q[Q].id=-i;q[Q].x=l1-1;q[Q].y=r2;
			if(q[Q].x>q[Q].y)swap(q[Q].x,q[Q].y);
			Q++;q[Q].id=i;q[Q].x=l1-1;q[Q].y=l2-1;
			if(q[Q].x>q[Q].y)swap(q[Q].x,q[Q].y);
		}
	}
	sort(q+1,q+Q+1);
	int l=0,r=0;
	for(int i=1;i<=Q;i++){
		int id=q[i].id,x=q[i].x,y=q[i].y;
		while(l<x)ins2(++l);
		while(l>x)del2(l--);
		while(r<y)ins1(++r);
		while(r>y)del1(r--);
		ANS[abs(id)]+=(id<0?-ans:ans);
	}
	for(int i=1;i<=m;i++)
		if(ANS[i]>-1)
			printf("%lld\n",ANS[i]);
	return 0;
}

```

---

