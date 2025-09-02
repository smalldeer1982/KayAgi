# Ezzat and Grid

## 题目描述

Moamen was drawing a grid of $ n $ rows and $ 10^9 $ columns containing only digits $ 0 $ and $ 1 $ . Ezzat noticed what Moamen was drawing and became interested in the minimum number of rows one needs to remove to make the grid beautiful.

A grid is beautiful if and only if for every two consecutive rows there is at least one column containing $ 1 $ in these two rows.

Ezzat will give you the number of rows $ n $ , and $ m $ segments of the grid that contain digits $ 1 $ . Every segment is represented with three integers $ i $ , $ l $ , and $ r $ , where $ i $ represents the row number, and $ l $ and $ r $ represent the first and the last column of the segment in that row.

For example, if $ n = 3 $ , $ m = 6 $ , and the segments are $ (1,1,1) $ , $ (1,7,8) $ , $ (2,7,7) $ , $ (2,15,15) $ , $ (3,1,1) $ , $ (3,15,15) $ , then the grid is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1557D/9e4ccafba8e9c07a0c3a14a574b9d7c53033cfd0.png)Your task is to tell Ezzat the minimum number of rows that should be removed to make the grid beautiful.

## 说明/提示

In the first test case, the grid is the one explained in the problem statement. The grid has the following properties:

1. The $ 1 $ -st row and the $ 2 $ -nd row have a common $ 1 $ in the column $ 7 $ .
2. The $ 2 $ -nd row and the $ 3 $ -rd row have a common $ 1 $ in the column $ 15 $ .

 As a result, this grid is beautiful and we do not need to remove any row.In the second test case, the given grid is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1557D/8652918b2f57efcbbbd2515fe51b146893b7cc96.png)

## 样例 #1

### 输入

```
3 6
1 1 1
1 7 8
2 7 7
2 15 15
3 1 1
3 15 15```

### 输出

```
0```

## 样例 #2

### 输入

```
5 4
1 2 3
2 4 6
3 3 5
5 1 1```

### 输出

```
3
2 4 5```

# 题解

## 作者：Lynkcat (赞：17)

这里是 set 做法。

朴素想法是枚举两行，看看他们是否在同一列都有 $1$ 然后连边后跑最长路。

显然边数会爆炸。

我们考虑优化连边数量，我们考虑将列离散化后，给左右端点打标记，然后从第一列开始往第 $k$ 列扫描，中途维护当前列上为 $1$ 的行。容易发现，这个 set 内相邻两个元素连边才是最优的，于是我们就可以在一行插进去时， set 查询相邻的两行，然后连边即可。边数显然是 $O(m)$ 级别的。可以通过。

这不比线段树好写多了

~~ps：赛时因为一些很傻逼的错误导致本来能很快过这道题结果四发罚时挂飞。~~

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
//#define int ll
#define N 3000005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
vector<int>li,E[N];
struct node
{
	int l,r;
};
vector<node>G[N];
int n,m,ans,dis[N],s[N],ls[N],vis[N];
vector<pa>B[N],C[N];
set<int>S;
void ad(int x,int y)
{
	if (x==y) return;
	E[y].push_back(x);
}
signed main()
{
	n=read(),m=read();
	for (int i=1;i<=m;i++)
	{
		node x;
		int y=read();
		x.l=read(),x.r=read();
		G[y].push_back(x);
		li.push_back(x.l),li.push_back(x.r);
	}
	sort(li.begin(),li.end());
	for (int i=1;i<=n;i++)
		for (auto x:G[i])
		{
			x.l=lower_bound(li.begin(),li.end(),x.l)-li.begin()+1;
			x.r=lower_bound(li.begin(),li.end(),x.r)-li.begin()+1;
			B[x.l].push_back({i,1});
			C[x.r+1].push_back({i,-1});
		}
	m=li.size();
	for (int i=1;i<=m;i++)
	{
		for (auto v:C[i])
		{
			s[v.fi]+=v.se;
			if (s[v.fi]==0)
			{
				S.erase(v.fi);
			}
		}
		for (auto v:B[i])
		{
			s[v.fi]+=v.se;
			if (s[v.fi]==1)
			{
				if (S.size()!=0)
           {
					auto it=S.lower_bound(v.fi);
					if (it!=S.end())
					{
						ad(v.fi,(*it));
					}
					if (it!=S.begin())
					{
						it--;
						ad((*it),v.fi);
					}
           }
				S.insert(v.fi);
			}
		}
	}
	for (int i=1;i<=n;i++)
	{
		dis[i]=1;ls[i]=i;
		for (auto u:E[i])
		{
			if (dis[u]+1>dis[i]) dis[i]=dis[u]+1,ls[i]=u;
		}
		if (dis[ans]<dis[i]) ans=i;
	}
	writeln(n-dis[ans]);
	while (ls[ans]!=ans)
	{
		vis[ans]=1;
		ans=ls[ans];
	}
	vis[ans]=1;
	for (int i=1;i<=n;i++) if (!vis[i]) writesp(i);
	
	
}
/*

*/

---

## 作者：myee (赞：7)

### Update
* 20210811 格式已修。


---
### 前言

听说这是道线段树优化 dp 板子题？比赛时一堆人没搞出来？

那我们就来分析一下这题怎么搞罢。

---
### 题意

给你 $n\times m$ 矩形上一些横向的全 $1$ 线段，然后让你删去最少的行，使得任意相邻两行都存在 $1$ 在同一列。

要求输出方案。

**线段可能重叠。**

---
### 思路

看到不在同一行的线段及可能重叠，想到上**扫描线**。

从左往右扫描，**把当前扫描线上的点放进一个数据结构**中。

对每个新插入的点，**找到其前驱、后继，与之相连**。

然后便可以**直接从前往后进行 dp** 找出留下来的最多点及点集（即 **dp 时记录路径**）了，剩下的点即答案。

正确性显然，大概就是每次插点时原本其前驱、后继相连，现在在中间新加一个点后必然更优，其它情况可以继续与它间接相连，于是正确性得证。（默认第 $0$ 行与第 $n+1$ 行全是 $1$）

什么，你问我这个**支持动态加点、删点、找前驱后继的数据结构**是什么？

**平衡树**啊。

其实可以直接用 `set`，但反正我直接上 `Splay` 了。

当然，如果你写线段树，也是可以的。

---
### Code

调试信息没有删，但意义还是清楚的。

前面的 `Splay` 码头可以仅大致浏览一下。

```cpp
#include <algorithm>
#include <stdio.h>
#include <vector>
typedef long long llt;
typedef unsigned uint;typedef unsigned long long ullt;
typedef bool bol;typedef char chr;typedef void voi;
typedef double dbl;
template<typename T>bol _max(T&a,T b){return(a<b)?a=b,true:false;}
template<typename T>bol _min(T&a,T b){return(b<a)?a=b,true:false;}
template<typename T>T power(T base,T index,T mod){return((index<=1)?(index?base:1):(power(base*base%mod,index>>1,mod)*power(base,index&1,mod)))%mod;}
template<typename T>T lowbit(T n){return n&-n;}
template<typename T>T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T>T lcm(T a,T b){return(a!=0||b!=0)?a/gcd(a,b)*b:(T)0;}
template<typename T,typename len_def>
class Splay
{
    public:
        Splay():rot(NULL){}
        ~Splay(){if(rot!=NULL)delete rot;}
        len_def size(){return(rot==NULL)?0:rot->siz;}
        voi bzr(){if(rot!=NULL)delete rot;rot=NULL;}
        voi insert(T key,len_def cnt=1)
        {
            if(rot==NULL){rot=new node(cnt),rot->key=key;return;}
            node*p=rot,*f=NULL;
            do
            {
                if(p->key==key){p->cnt+=cnt,p->resize();if(f!=NULL)f->resize();splay(p);return;}
                if((f=p,p=p->son[p->key<key])==NULL)
                {
                    p=new node(cnt),p->key=key,p->fath=f,f->son[f->key<key]=p,f->resize(),splay(p);
                    return;
                }
            }
            while(true);
        }
        voi cut(T key,len_def cnt=1)
        {
            node*p=rot,*f=NULL;
            while(p!=NULL)
            {
                if(p->key==key)
                {
                    p->cnt=(cnt<p->cnt)?p->cnt-cnt:0,p->resize();
                    if(f!=NULL)f->resize();
                    splay(p);return;
                }
                f=p,p=p->son[p->key<key];
            }
            splay(f);
        }
        voi make_count(T key,len_def cnt)
        {
            if(cnt==0){erase_all(key);return;}
            if(rot==NULL){rot=new node(cnt),rot->key=key;return;}
            node*p=rot,*f=NULL;
            do
            {
                if(p->key==key){p->cnt=cnt,p->resize();if(f!=NULL)f->resize();splay(p);return;}
                if((f=p,p=p->son[p->key<key])==NULL)
                {
                    p=new node(cnt),p->key=key,p->fath=f,f->son[f->key<key]=p,f->resize(),splay(p);
                    return;
                }
            }
            while(true);
        }
        voi erase(T key,len_def cnt=1)
        {
            if(rot==NULL)return;
            rank(key);node*p=rot;
            if(p->key!=key)return;
            if(cnt<p->cnt){p->cnt-=cnt,p->siz-=cnt;return;}
            if(p->son[0]==NULL&&p->son[1]==NULL){bzr();return;}
            if(p->son[0]==NULL){rot=p->son[1],rot->fath=NULL,kill(p);return;}
            if(p->son[1]==NULL){rot=p->son[0],rot->fath=NULL,kill(p);return;}
            pre(),p->son[1]->fath=rot,rot->son[1]=p->son[1],kill(p),rot->resize();
        }
        voi erase_all(T key)
        {
            if(rot==NULL)return;
            rank(key);node*p=rot;
            if(p->key!=key)return;
            if(p->son[0]==NULL&&p->son[1]==NULL){bzr();return;}
            if(p->son[0]==NULL){rot=p->son[1],rot->fath=NULL,kill(p);return;}
            if(p->son[1]==NULL){rot=p->son[0],rot->fath=NULL,kill(p);return;}
            pre(),p->son[1]->fath=rot,rot->son[1]=p->son[1],kill(p),rot->resize();
        }
        len_def count(T key)
        {
            node*p=rot,*last=NULL;
            do
            {
                if(p==NULL)return splay(last),0;
                if(key==p->key)break;
                p=p->son[p->key<key];
            }
            while(true);
            return splay(p),p->cnt;
        }
        len_def rank(T key)
        {
            len_def ans=0;node*p=rot,*last=NULL;
            while(p!=NULL)
                if(key<p->key)last=p,p=p->son[0];
                else
                {
                    if(p->son[0]!=NULL)ans+=p->son[0]->siz;
                    if(key==p->key)return splay(p),ans;
                    ans+=p->cnt,last=p,p=p->son[1];
                }
            return splay(last),ans;
        }
        T kth(len_def k)
        {
            node*p=rot;
            while(p!=NULL)
                if(p->son[0]!=NULL&&k<p->son[0]->siz)p=p->son[0];
                else
                {
                    if(p->son[0]!=NULL)k-=p->son[0]->siz;
                    if(k<p->cnt)break;
                    k-=p->cnt,p=p->son[1];
                }
            return splay(p),p->key;
        }
        T pre(T key){insert(key),pre();T ans=rot->key;erase(key);return ans;}
        T nxt(T key){insert(key),nxt();T ans=rot->key;erase(key);return ans;}
    private:
        class node
        {
            public:
                T key;len_def cnt,siz;node*son[2],*fath;
                node(len_def cnt=1){siz=this->cnt=cnt,son[0]=son[1]=fath=NULL;}
                ~node(){if(son[0]!=NULL)delete son[0];if(son[1]!=NULL)delete son[1];}
                voi resize()
                {
                    siz=cnt;
                    if(son[0]!=NULL)siz+=son[0]->siz;
                    if(son[1]!=NULL)siz+=son[1]->siz;
                }
                bol howson(){return this==fath->son[1];}
                voi rotate()
                {
                    node*f=fath;
                    if(f==NULL)return;
                    node*ff=f->fath;
                    bol sk=howson();
                    if(ff!=NULL)ff->son[f->howson()]=this;
                    f->son[sk]=son[!sk];
                    if(son[!sk]!=NULL)son[!sk]->fath=f;
                    son[!sk]=f,f->fath=this,fath=ff,f->resize(),resize();
                }
        };
        node*rot;
        voi splay(node*p)
        {
            if(p==NULL)return;
            while(p->fath!=NULL)
            {
                if(p->fath->fath!=NULL)((p->howson()==p->fath->howson())?p->fath:p)->rotate();
                p->rotate();
            }
            rot=p;
        }
        voi kill(node*p){p->son[0]=p->son[1]=NULL;delete p;}
        node*pre()
        {
            node*p=rot->son[0];
            if(p==NULL)return NULL;
            while(p->son[1]!=NULL)p=p->son[1];
            return splay(p),p;
        }
        node*nxt()
        {
            node*p=rot->son[1];
            if(p==NULL)return NULL;
            while(p->son[0]!=NULL)p=p->son[0];
            return splay(p),p;
        }
};
typedef std::pair<ullt,uint>Pair;
int In[300005];
Pair P[1919810];
std::vector<uint>Way[300005];
Splay<int,uint>S;
uint DP[300005],Last[300005];
int main()
{
	uint n,m,u,l,r;scanf("%u%u",&n,&m);
	for(uint i=0;i<m;i++)scanf("%u%u%u",&u,&l,&r),P[i<<1]=Pair((ullt)l*2-1,--u),P[(i<<1)|1]=Pair((ullt)r*2,u);
	std::sort(P,P+(m<<=1));
	S.insert(-1),S.insert(n);
	for(uint i=0;i<m;i++)
	{
		u=P[i].second;
		if(P[i].first&1)
		{
			int p=S.pre(u),q=S.nxt(u);
			if(~p)Way[u].push_back(p);
			if((uint)q<n)Way[q].push_back(u);
			S.insert(u);
			In[u]++;
		}
		else S.erase(u),In[u]--;
	}
	uint ans=0;
	u=-1;
	for(uint i=0;i<n;i++)
	{
		Last[i]=-1;
		// printf("%u:",i+1);
		for(auto p:Way[i])
		{
			if(_max(DP[i],DP[p]))Last[i]=p;
			// printf("%u ",p+1);
		}
		// putchar('\n');
		if(_max(ans,++DP[i]))u=i;
	}
	while(~u)In[u]=true,u=Last[u];
	ans=n-ans;
	printf("%u\n",ans);
	for(uint i=0;i<n;i++)if(!In[i])
		printf("%u%c",i+1,(--ans)?' ':'\n');
	return 0;
}
```


---

## 作者：摸鱼酱 (赞：6)

大致题意：有一张 $n$ 行，无限长的网格，上面覆盖了 $m$ 条线段，每条线段用 $(i,l,r)$ 表示覆盖了第 $i$ 行的区间 $[l,r]$，问最少删除多少行，使得剩余的相邻两行都有至少一个相同位置都被线段覆盖，并输出方案。

$1\leq n,m\leq 3\times 10^5$，$1\leq l\leq r\leq 10^9$。

因为输出方案的步骤只需要稍加修改，所以只考虑如何求最多保留多少行。

首先把 $l,r$ 离散化掉，注意数组大小。

设 $f_i$ 表示以第 $i$ 行结尾，能保留的最大行数，$f_i=\max\{f_j\}+1$，其中 $i$ 和 $j$ 存在一个相同位置都被覆盖。

更进一步地，设 $g_i$ 表示位置 $i$ 上被线段覆盖时的最大的 $f$ 值，那么 $f_i$ 就等于所有第 $i$ 行线段对应区间的 $g$ 值的 $\max$ 再加一，然后把 $f_i$ 贡献到它对应的区间上，这个贡献直观感受是让区间对 $f_i$ 取 $\max$。

但不难发现对于一个 $i$，每次更新时 $g_i$ 是单调递增的，即如果这个位置 $i$ 在 $f_j$ 更新时被涉及，那么有 $f_j>g_i$，所以实际上区间取 $\max$ 的操作改为区间赋值即可。

需要用线段树实现区间赋值，区间查询 $\max$，方案的话把结点记录的信息改为 pair 即可。

[code](https://www.luogu.com.cn/paste/fqkezimv)，时间复杂度 $O(n\log n)$。



---

## 作者：huayucaiji (赞：6)

## 前言

线段树好题一个。

## 解题思路

我们首先先要对数据进行离散化，这是一个常规套路。

正难则反，我们考虑 `dp` 。令 $f_i$ 表示以 $i$ 为结尾，最多可以选择多少行。显然，我们有转移方程：
$$
f_i=\max\limits_{j<i \operatorname{and} g(i,j)} f_j+1
$$
其中 $g(i,j)$ 为一个布尔函数，表示第 $i,j$ 行是否可以相邻。

这显然是一个 $O(n^3)$ 级别的算法，我们考虑优化一下，可以用线段树。

我们假设现在考虑已经求出对于 $j\in [1,i]$ 中的所有 $f_j$，我们线段树维护的是目前，区间所被覆盖的行中 $f_i$ 值最大的那一个，这样我们在求解 $f_{i+1}$​ 时，可以利用线段树上的信息了。

最后答案就是 $n-\max\limits_{i=1}^n f_i$。

求解方案的话，只要记录一下决策点即可。

时间复杂度 $O(n\log n)$。线段树帮助我们省去了枚举 $j$ 和计算 $g$ 函数的时间。 

## 代码 

**注意有几处等于号一定要有，否则会错。**

别问我怎么知道。

~~22次的提交记录告诉我的~~

原因的话，是因为可能因为 `pushup` 操作导致父节点的 $maxx$​ 值已经正确，但是另外一个子节点无法更新到。

这话很抽象，最好在实践中理解。。。。。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=3e5+10; 

int n,m,len,cnt;
struct segment {
	int maxx,lazy;
}s[MAXN<<3];
struct sgm {
	int id,l,r;
}sm[MAXN];
int num[MAXN<<1],f[MAXN],g[MAXN];
bool vis[MAXN];
vector<sgm> vec[MAXN];

void pushdown(int l,int r,int p) {
	if(l==r) {
		return ;
	}
	int mid=(l+r)>>1;
	if(f[s[p].lazy]>=f[s[p<<1].maxx]) {
		s[p<<1].maxx=s[p].lazy;
		s[p<<1].lazy=s[p].lazy;
	}
	if(f[s[p].lazy]>=f[s[p<<1|1].maxx]) {
		s[p<<1|1].maxx=s[p].lazy;
		s[p<<1|1].lazy=s[p].lazy;
	}
	s[p].lazy=0;
}
segment pushup(segment lft,segment rgt) {
	segment ret=s[0];
	if(f[lft.maxx]>f[rgt.maxx]) {
		ret.maxx=lft.maxx;
	}
	else {
		ret.maxx=rgt.maxx;
	}
	return ret;
}

void modify(int l,int r,int p,int x,int y,int val) {
	if(r<x||y<l) {
		return ;
	}
	pushdown(l,r,p);
	if(x<=l&&r<=y) {
		if(f[val]>=f[s[p].maxx]) {
            //here
			s[p].maxx=val;
			s[p].lazy=val;
		}
		return ;
	}
	
	int mid=(l+r)>>1;
	modify(l,mid,p<<1,x,y,val);
	modify(mid+1,r,p<<1|1,x,y,val);
	s[p]=pushup(s[p<<1],s[p<<1|1]);
}
segment query(int l,int r,int p,int x,int y) {
	if(r<x||y<l) {
		return s[0];
	}
	pushdown(l,r,p);
	if(x<=l&&r<=y) {
		return s[p];
	}
	
	int mid=(l+r)>>1;
	return pushup(query(l,mid,p<<1,x,y),query(mid+1,r,p<<1|1,x,y));
}

int get(int x) {
	return lower_bound(num+1,num+len+1,x)-num;
}

signed main() {

	cin>>n>>m;
	for(int i=1;i<=m;i++) {
		sm[i].id=read();num[++cnt]=sm[i].l=read();num[++cnt]=sm[i].r=read();
	}
	sort(num+1,num+cnt+1);
	len=unique(num+1,num+cnt+1)-num-1;
	
	for(int i=1;i<=m;i++) {
		sm[i].l=get(sm[i].l);
		sm[i].r=get(sm[i].r);
		vec[sm[i].id].push_back(sm[i]);
	}
	
	int tp=0,maxx=0;
	for(int i=1;i<=n;i++) {
		if(i==6) {
			int hhh;
			hhh++;
		}
		segment ans=s[0];
		int sz=vec[i].size();
		for(int j=0;j<sz;j++) {
			ans=pushup(ans,query(1,len,1,vec[i][j].l,vec[i][j].r));
		}
		f[i]=f[ans.maxx]+1;
		g[i]=ans.maxx;
		//cout<<f[i]<<" "<<g[i]<<endl;
		if(f[i]>maxx) {
			maxx=f[i];
			tp=i;
		}
		
		for(int j=0;j<sz;j++) {
			modify(1,len,1,vec[i][j].l,vec[i][j].r,i);
		}
	}
	
	int ans=n;
	while(tp) {
		ans--;
		vis[tp]=1;
		tp=g[tp];
	}
	
	cout<<ans<<endl;
	for(int i=1;i<=n;i++) {
		if(!vis[i]) {
			printf("%d ",i);
		}
	}

	return 0;
}
```



---

## 作者：Acc_Robin (赞：3)

## CF1557D Ezzat and Grid 题解

[传送门](https://codeforces.com/problemset/problem/1557/D)

[更高更妙的阅读体验](https://accrobin.github.io/2021/08/11/solver/CF1557D%20Ezzat%20and%20Grid%20%E9%A2%98%E8%A7%A3/)

### 题意

给你一个 $n\times m$ 的 01 串，让你删去最少的行（删去一行之后，上下两行变为相邻）使得任意相邻两行都有至少一个公共的位置上是 1.

$n\le 3\times 10^5,m\le 10^9$，每次给出某一行上一个区间 $[l,r]$ 由 $1$ 组成。

### 题解

首先做一步小转化，从“删去最少”变成“选取最多”。

考虑DP，令 $f_{i}$​ 表示前 $i$​ 行最多选取几行，转移有
$$
f_i=\max_{j<i \land \text{第i行与第j行有公共的1}} f_{j}+1
$$
注意到我们需要处理区间相交的问题，无疑线段树是合适的选择。

我们使用线段树来维护区间最大值：加入第 $i$ 行时，使用线段树求出与第 $i$ 有公共部分的最大值 $f_j,(j<i)$，完成 $f_j$ 到 $f_i$ 的转移之后再将第 $i$ 行有 $1$ 的位置全部更新成 $f_i$。

注意此题还要求输出方案，所以线段树上维护最大值的同时维护一下最大值来自于哪一行。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	using pii=pair<int,int>;
	const int N=3e5+9;
	const pii NUL={0,-1};
	int b[N<<1],L[N<<3],R[N<<3],las[N],f;
	pii v[N<<3],t[N<<3];
	vector<pii>g[N];
	#define lc (o<<1)
	#define rc (o<<1|1)
	void up(pii&x,pii y){if(x<y)x=y;}
	void bd(int o,int l,int r){
		L[o]=l,R[o]=r,v[o]=t[o]=NUL;
		if(l==r)return;
		int md=l+r>>1;
		bd(lc,l,md),bd(rc,md+1,r);
	}
	void pd(int o){
		if(t[o]==NUL)return;
		up(v[lc],t[o]),up(v[rc],t[o]);
		up(t[lc],t[o]),up(t[rc],t[o]),t[o]=NUL;
	}
	pii ask(int o,int l,int r){
		if(l<=L[o] && R[o]<=r)return v[o];
		pd(o);
		int md=L[o]+R[o]>>1;pii z=NUL;
		if(l<=md)up(z,ask(lc,l,r));
		if(r>md)up(z,ask(rc,l,r));
		v[o]=max(v[lc],v[rc]);
		return z;
	}
	void add(int o,int l,int r,pii x){
		if(l<=L[o] && R[o]<=r)return (void)(up(v[o],x),up(t[o],x));
		int md=L[o]+R[o]>>1;pd(o);
		if(l<=md)add(lc,l,r,x);
		if(r>md)add(rc,l,r,x);
		v[o]=max(v[lc],v[rc]);
	}
	void work(){
		int n,m,l=0,x,y,z,i;
		for(cin>>n>>m;m--;)
			cin>>x>>y>>z,g[x].push_back({y,z}),b[l++]=y,b[l++]=z;
		sort(b,b+l),l=unique(b,b+l)-b,bd(1,1,l);
		for(i=1;i<=n;++i)for(auto&[x,y]:g[i])
			x=lower_bound(b,b+l,x)-b+1,y=lower_bound(b,b+l,y)-b+1;
		for(i=1;i<=n;++i){
			pii mx=NUL;
			if(i==5)f=1;
			for(auto[x,y]:g[i])mx=max(mx,ask(1,x,y));
			las[i]=mx.second,mx.second=i,++mx.first;
			for(auto[x,y]:g[i])add(1,x,y,mx);
		}
		pii mx=ask(1,1,l);cout<<n-mx.first<<'\n';
		for(x=mx.second;~x;x=las[x])b[x]=-1;
		for(i=1;i<=n;++i)if(~b[i])cout<<i<<' ';
	}
}
int main(){return Acc::work(),0;}
```

### 小细节

此题的值域较大，需要离散化。

---

## 作者：Cupids_Bow (赞：2)

## 前言
看题解大部分是 DP ，在赛时有另一种想法，想分享一下。~~不过实现起来其实差不多？~~
## 思路
题目大意为要求去除若干行，使得剩余的行中任意相邻的两行都有 $1$ 相连。

假设每一行的所有 $1$ 串都连续，那么将每一行的 $1$ 串看成一张垫子，“相邻两行必须有 $1$ 相连”的条件可以很自然地看成上面的垫子必须叠在下面的垫子之上，如下图（ . 表示 $0$ ）：

```cpp
. 1 1 1 . . . . . .
. . 1 1 1 . . . . .
. . . . 1 1 . . . .
. . . . . . . . 1 1
1 1 . . . . . . . .
. . . 1 1 . . . . .
1 1 . . . . . . . .
. . . . 1 1 1 1 1 .
. 1 1 . . . . . . .
. . . . . . . . 1 .

```
将所有的 $1$ “下落”之后如图：
```cpp
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. 1 1 1 . . . . . .
. . 1 1 1 . . . . .
. . . . 1 1 . . . .
1 1 . 1 1 . . . 1 1
1 1 . . 1 1 1 1 1 .
. 1 1 . . . . . 1 .
```
图中堆叠最高的位置高度为 $6$ ，即最后只需剩下 $6$ 行，需要去掉的行数即为 $n-height=4$ 。

那么加入题目的限制，同一行互不相交的 $1$ 串只需有一段能叠在下面的 $1$ 串上，这一行即可继续堆叠上去。那么我们预处理好每一行的各个 $1$ 串，在加入这一行时查询当前行 $1$ 串所在位置的最大高度，将这一行堆叠上去即可，这一部分可以用线段树维护区间最大值实现（注意段落端点需要离散化）。因为在堆叠的过程中会不断更新最高的部分和位置，在每次堆叠时一定可以保证当前的放置是最优的。（其实这一部分和 DP 的转移已经非常像了）

最后的答案即为 $n-height$ ，考虑输出一种可能的去除方案，可以记录每一行最后叠放的高度，因为每一行要达到当前的高度，必定是有一个高度比他小的前驱，从最高层的任意一行出发，标记到底层的所有行序号，最后输出没有被标记的行即可。
## 代码
~~当时写的比较乱，有些地方有冗余，勿喷QAQ~~
```cpp
#include<bits/stdc++.h>
#define next next_
#define last last_
#define y1 yy
using namespace std;

using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const ll mod=1e9+7,mod2=1e9+9;
const ull base=101;
const double pi=acos(-1.0);
int _;

vector<ll> ans,pos[300010],height[300010];
ll n,m,app[600010],pre[300010],cnt;
bool vis[300010];
struct line{
	ll i;
	ll l;
	ll r;
	bool operator < (line a)const{
		return i<a.i;
	}
}seg[300010];
struct tree{
	ll l;
	ll r;
	ll maxn;
	ll lz;
}t[2400010];

void build(ll i,ll l,ll r){
	t[i].l=l;
	t[i].r=r;
	t[i].lz=-1;
	if(l==r){
		t[i].maxn=0;
		return;
	}
	ll mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	t[i].maxn=max(t[i<<1].maxn,t[i<<1|1].maxn);
	return;
}

void pushdown(ll i){
	if(t[i].lz!=-1){
		t[i<<1].maxn=t[i].lz;
		t[i<<1|1].maxn=t[i].lz;
		t[i<<1].lz=t[i].lz;
		t[i<<1|1].lz=t[i].lz;
		t[i].lz=-1;
	}
	return;
}

void change(ll i,ll l,ll r,ll k){
	if(t[i].l>=l&&t[i].r<=r){
		t[i].maxn=k;
		t[i].lz=k;
		return;
	}
	pushdown(i);
	if(t[i<<1].r>=l) change(i<<1,l,r,k);
	if(t[i<<1|1].l<=r) change(i<<1|1,l,r,k);
	t[i].maxn=max(t[i<<1].maxn,t[i<<1|1].maxn);
	return;
}

ll search(ll i,ll l,ll r){
	if(t[i].l>=l&&t[i].r<=r) return t[i].maxn;
	pushdown(i);
	ll maxn=0;
	if(t[i<<1].r>=l) maxn=max(maxn,search(i<<1,l,r));
	if(t[i<<1|1].l<=r) maxn=max(maxn,search(i<<1|1,l,r));
	return maxn;
}

ll nex(ll pos){//查找在同一行的1串
	while(seg[pos+1].i==seg[pos].i&&pos<m) pos++;
	return pos;
}

bool cross(ll a,ll b){判断两行是否有1相邻
	bool f=false;
	for(auto i:pos[a])
		for(auto j:pos[b]){
			if(seg[i].l>seg[j].r||seg[i].r<seg[j].l);
			else f=true;
		}
	return f;
}

void work(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=m;i++){
		scanf("%lld%lld%lld",&seg[i].i,&seg[i].l,&seg[i].r);
		app[++cnt]=seg[i].l;
		app[++cnt]=seg[i].r;
	}
	sort(app+1,app+1+cnt);
	ll pp=unique(app+1,app+1+cnt)-app-1;
	sort(seg+1,seg+1+m);
	for(ll i=1;i<=m;i++){
		pos[seg[i].i].push_back(i);
		seg[i].l=lower_bound(app+1,app+1+pp,seg[i].l)-app;
		seg[i].r=lower_bound(app+1,app+1+pp,seg[i].r)-app;
	}
	build(1,1,pp);
	for(ll i=1;i<=m;i++){
		ll ne=nex(i);
		ll maxn=0;
		foR(ll j=i;j<=ne;j++) maxn=max(maxn,search(1,seg[j].l,seg[j].r));//查找能叠放的最高高度
		foR(ll j=i;j<=ne;j++) change(1,seg[j].l,seg[j].r,maxn+1);//叠放
		foR(ll j=i;j<=ne;j++) height[maxn+1].push_back(seg[j].i);//记录每一个高度的行序号
		i=ne;
	}
	ll id=height[t[1].maxn][0];
	for(ll i=t[1].maxn;i>=1;i--){//找最高层任意一行的前驱
		for(auto k:height[i-1]){
			if(cross(id,k)){
				pre[id]=k;
				break;
			}
		}
		id=pre[id];
	}
	id=height[t[1].maxn][0];
	while(pre[id]) vis[id]=true,id=pre[id];//标记选中的行
	vis[id]=true;
	for(ll i=1;i<=n;i++) if(!vis[i]) ans.push_back(i);
	printf("%lld\n",n-t[1].maxn);
	for(auto i:ans) printf("%lld ",i);
}

int main(){
//	scanf("%d",&_);
	_=1;
	while(_--){
		work();
	}
	return 0;
}
```

---

## 作者：FjswYuzu (赞：1)

人生中第一次拿一道题的保底分。罚了 19 发。这套题的样例都水的一比不做评价。

将删去一些行变成保留一些行。首先将区间离散化，定义 $dp_{i,j}$ 为，在前 $i$ 行里面删除一些行，使得合法并且离散化后第 $j$ 列为 $1$ 可以保留的最大行数。显然第一维可以滚掉。转移的话可以就是枚举这一行全为 $1$ 的 $k$ 个区间，令 $p=\max_{s=1}^k \{ \max_{t=l_s}^{r_s} dp_{i-1,t} \}$，将整行为 $1$ 的位置置为 $p+1$，其余继承 $dp_i$。

注意到 $p+1$ 一定大于 $p$，因此转移的过程是继承，区间求最大值，区间覆盖。可以直接线段树优化转移。转移的时候存储两个信息，即上一行选的什么和 dp 值，用一个数组存下来这一行的上一行选的什么。最后查询整个区间可以保留多少行，以及最后一行是什么，用个数组存下有没有用到，输出答案就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
#define mp make_pair
vector<pair<int,int>> Col[300005];
int C[300005],L[300005],R[300005],b[600005],pre[300005];
bool vis[300005];
pair<int,int> maxn[10800005],tag[10800005];
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define Mm int mid=(l+r)>>1
pair<int,int> Max(pair<int,int> x,pair<int,int> y)
{
	if(x.first>y.first)	return x;
	return y;
}
void push_down(int now)
{
	tag[lc(now)]=Max(tag[lc(now)],tag[now]);
	tag[rc(now)]=Max(tag[rc(now)],tag[now]);
	maxn[lc(now)]=Max(maxn[lc(now)],tag[now]);
	maxn[rc(now)]=Max(maxn[rc(now)],tag[now]);
	tag[now].first=0;
}
void push_up(int now){maxn[now]=Max(maxn[lc(now)],maxn[rc(now)]);}
void modify(int l,int r,int now,int x,int y,pair<int,int> val)
{
	if(x<=l && r<=y)
	{
		tag[now]=Max(tag[now],val);
		maxn[now]=Max(maxn[now],val);
		return ;
	}
	push_down(now);
	Mm;
	if(x<=mid)	modify(l,mid,lc(now),x,y,val);
	if(mid<y)	modify(mid+1,r,rc(now),x,y,val);
	push_up(now);
}
pair<int,int> query(int l,int r,int now,int x,int y)
{
	if(x<=l && r<=y)	return maxn[now];
	push_down(now);
	Mm;
	pair<int,int> ret;
	ret.first=0;
	if(x<=mid)	ret=max(ret,query(l,mid,lc(now),x,y));
	if(mid<y)	ret=max(ret,query(mid+1,r,rc(now),x,y));
	return ret;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d %d %d",&C[i],&L[i],&R[i]);
		b[i*2-1]=L[i],b[i*2]=R[i];
	}
	sort(b+1,b+1+m+m);
	int len=unique(b+1,b+1+m+m)-b-1;
	for(int i=1;i<=m;++i)
	{
		L[i]=lower_bound(b+1,b+1+len,L[i])-b;
		R[i]=lower_bound(b+1,b+1+len,R[i])-b;
		Col[C[i]].push_back(mp(L[i],R[i]));
	}
	for(int i=1;i<=n;++i)
	{
		int dp=0;
		for(auto st:Col[i])	dp=max(dp,query(1,len,1,st.first,st.second).first);
		for(auto st:Col[i])
		{
			pair<int,int> que=query(1,len,1,st.first,st.second);
			if(que.first==dp)
			{
				pre[i]=que.second;
				break;
			}
		}
		++dp;
		for(auto st:Col[i])	modify(1,len,1,st.first,st.second,mp(dp,i));
	}
	printf("%d\n",n-maxn[1].first);
	int now=maxn[1].second;
	while(now)
	{
		vis[now]=true;
		now=pre[now];
	}
	for(int i=1;i<=n;++i)	if(!vis[i])	printf("%d ",i);
	return 0;
}
```

---

## 作者：water_tomato (赞：1)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf1557d-ezzat-and-grid-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1557D)。

给定 $n$ 行 01 串，其中有 $m$ 个区间为 $1$​。删除若干 01 串使剩余串美丽，若干条 01 串美丽当且仅当任意相邻两个 01 串至少有相同的一位均为 $1$。

$n,m\le 3\times10^5$。

## 解析

考虑记 $f_i$ 为以第 $i$ 串结尾的最长美丽串的长度。发现 $f_i=f_j+1,j\in[1,i)$ 当且仅当第 $i$ 串和 $j$ 串有相同位的 $1$​，发现离散化后串一共就只有 $6\times10^5$ 位，我们考虑将贡献打在 01 串的具体位上。

记 $f_{i,j}$ 为当前遍历到第 $i$ 个串，其中最后一个串的第 $j$ 位上为 $1$ 的最大贡献，容易发现 $i$ 实际没什么用。那么我们考虑对于 $j$ 建一棵线段树，遍历到第 $i$ 个串时，我们在线段树上查询第 $i$ 个串所有 $1$ 位置的答案并取最大值再加一作为以当前串结尾的答案，再用这个答案去更新该串的所有 $1$ 位置即可。

由于要输出方案，线段树改成 pair，分别存答案和产生这个答案的串即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ls x<<1
#define rs x<<1|1
using namespace std;
const int N=3e5+5;
pi tr[N<<3],tag[N<<3];
int n,m,pre[N],b[N<<1],cnt,mx;
int ans,ansp;
vector<pi> vec[N];
inline pi Max(pi x,pi y){
	if(x.fi>y.fi) return x;
	return y;
}
inline void pushdown(int x){
	if(!tag[x].fi) return;
	tr[ls]=tag[x],tr[rs]=tag[x];
	tag[ls]=tag[x],tag[rs]=tag[x];
	tag[x]=mk(0,0);
}
inline void pushup(int x){
	tr[x]=Max(tr[ls],tr[rs]);
}
inline pi query(int x,int l,int r,int L,int R){
	if(l>=L&&r<=R) return tr[x];
	int mid=(l+r)>>1;
	pushdown(x);
	if(L<=mid&&R>mid) return Max(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
	if(L<=mid) return query(ls,l,mid,L,R);
	return query(rs,mid+1,r,L,R);
}
inline void modify(int x,int l,int r,int L,int R,pi k){
	if(l>=L&&r<=R){tr[x]=k;tag[x]=k;return;}
	int mid=(l+r)>>1;
	pushdown(x);
	if(L<=mid) modify(ls,l,mid,L,R,k);
	if(R>mid) modify(rs,mid+1,r,L,R,k);
	pushup(x);
}
bool vis[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,l,r;i<=m;i++){
		scanf("%d%d%d",&x,&l,&r);
		vec[x].push_back(mk(l,r));
		b[++cnt]=l;b[++cnt]=r;
	}
	sort(b+1,b+1+cnt);
	cnt=unique(b+1,b+1+cnt)-b-1;
	for(int i=1;i<=n;i++){
		for(auto &x:vec[i]){
			x.fi=lower_bound(b+1,b+1+cnt,x.fi)-b;
			x.se=lower_bound(b+1,b+1+cnt,x.se)-b;
		}
	}//离散化
	for(int i=1;i<=n;i++){
		mx=-1;
		for(auto x:vec[i]){//求当前串的答案
			pi t=query(1,1,cnt,x.fi,x.se);
			if(t.fi>mx){mx=t.fi;pre[i]=t.se;}
		}
		if(mx+1>ans){//更新全局答案
			ans=mx+1;
			ansp=i;
		}
		for(auto x:vec[i]){//更新对应位置的答案
			pi t=mk(mx+1,i);
			modify(1,1,cnt,x.fi,x.se,t);
		}
	}
	printf("%d\n",n-ans);
	for(int i=ansp;i;i=pre[i]) vis[i]=1;
	for(int i=1;i<=n;i++){
		if(!vis[i]) printf("%d ",i);
	}
	return 0;
}
```

掉大分，哈哈。

---

## 作者：registerGen (赞：0)

[这次比赛的题解](https://www.cnblogs.com/registergen/p/cf_round_737_solution.html)

dp。设 $f_{i,j}$ 表示前 $i$ 行最多能保留几行，且我们考虑了第 $i$ 行第 $j$ 列这个格子是 $1$。

转移的时候考虑所有值为 $1$ 的 $(k,j)$，那么：

$$f_{i,j}=\max_{1\le k\le i-1,grid_{k,j}=1}\{f_{k,j}+1\}$$

这个可以用线段树优化。具体的，对于每个 $j$，我们要维护 $f_{k,j}$ 的最大值。

具体细节见代码（非 C++11 党勿入）：

```cpp
using ll=long long;
using pii=std::pair<int,int>;

// 区间覆盖，区间 max，还要维护方案
struct SegTree{
	struct Node{
		pii mx,ctag;
	};

	std::vector<Node> t;

	SegTree(int n=0){
		t.resize(n*4+5,{{0,-1},{0,-1}});
	}

	std::function<int(int)> ls=[](int x)->int{return x<<1;};
	std::function<int(int)> rs=[](int x)->int{return x<<1|1;};

	std::function<Node(const Node &,const Node &)> pushUp=[](const Node &L,const Node &R)->Node{
		return {std::max(L.mx,R.mx),{0,-1}};
	};

	std::function<void(Node &,const pii &)> pushC=[](Node &now,const pii &ctag)->void{
		now.mx=now.ctag=ctag;
	};

	std::function<void(int)> pushDown=[this](int i)->void{
		if(t[i].ctag!=pii({0,-1})){
			pushC(t[ls(i)],t[i].ctag);
			pushC(t[rs(i)],t[i].ctag);
			t[i].ctag={0,-1};
		}
	};

	std::function<void(int,int,int,int,int,const pii &)> modify=[this](int i,int l,int r,int ql,int qr,const pii &x)->void{
		if(ql<=l&&r<=qr)return pushC(t[i],x),void();
		int mid=(l+r)>>1;
		pushDown(i);
		if(ql<=mid)modify(ls(i),l,mid,ql,qr,x);
		if(qr>mid) modify(rs(i),mid+1,r,ql,qr,x);
		t[i]=pushUp(t[ls(i)],t[rs(i)]);
	};

	std::function<Node(int,int,int,int,int)> query=[this](int i,int l,int r,int ql,int qr)->Node{
		if(ql<=l&&r<=qr)return t[i];
		int mid=(l+r)>>1;
		pushDown(i);
		if(ql>mid) return query(rs(i),mid+1,r,ql,qr);
		if(qr<=mid)return query(ls(i),l,mid,ql,qr);
		return pushUp(query(ls(i),l,mid,ql,qr),query(rs(i),mid+1,r,ql,qr));
	};
};

void mian(){
	int n,m;
	scanf("%d%d",&n,&m);
	std::vector<std::vector<pii>> a(n);
	for(int i=0;i<m;i++){
		int p,l,r;
		scanf("%d%d%d",&p,&l,&r);
		p--;
		a[p].push_back({l,r});
	}
	// 把所有线段离散化
	std::function<void(void)> init=[&]()->void{
		std::vector<int> tmp;
		for(auto i:a)
			for(auto j:i)
				tmp.push_back(j.first),tmp.push_back(j.second);
		std::sort(tmp.begin(),tmp.end());
		auto it=std::unique(tmp.begin(),tmp.end());
		tmp.erase(it,tmp.end());
		for(auto &i:a)
			for(auto &j:i){
				j.first=std::lower_bound(tmp.begin(),tmp.end(),j.first)-tmp.begin()+1;
				j.second=std::lower_bound(tmp.begin(),tmp.end(),j.second)-tmp.begin()+1;
			}
	};
	init();
	std::vector<pii> f(n);
	for(auto &x:f)x.second=-1;
	SegTree t(m*2);
	for(int i=0;i<n;i++){
		for(auto j:a[i]){ // 枚举第 i 行所有的值为 1 的格子
			auto x=t.query(1,1,m*2,j.first,j.second); // max_{k=1..i-1,grid[k][j]}=1} f[j]
			x.mx.first++;
			f[i]=std::max(f[i],x.mx);
		}
		for(auto j:a[i])
			t.modify(1,1,m*2,j.first,j.second,{f[i].first,i}); // 更新 max f[k][j]
	}
	// 输出方案
	int p=0;
	for(int i=0;i<n;i++)
		if(f[i]>f[p])p=i;
	std::set<int> ans;
	for(int i=0;i<n;i++)ans.insert(i);
	for(;p!=-1;p=f[p].second)ans.erase(p);
	printf("%d\n",int(ans.size()));
	for(auto i:ans)printf("%d ",i+1);
	puts("");
}
```

---

