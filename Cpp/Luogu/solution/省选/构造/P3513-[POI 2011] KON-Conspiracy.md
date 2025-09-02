# [POI 2011] KON-Conspiracy

## 题目描述

敌对的 Bitotia 发动了一次对 Byteotia 的突袭，并占领了其大部分领土。

Byteotia 的国王 Byteasar 打算在被占领地区组织抵抗运动。

Byteasar 自然地从选择将组成运动骨干的人开始。

他们将被分为两组：

阴谋者将在被占领的领土上直接行动，而支援小组将在自由的 Byteotia 内部运作。

然而，有一个问题——分组必须满足以下条件：

支援小组中的每一对人必须彼此认识——这将使整个小组合作高效。

阴谋者之间不能相互认识。

没有一个小组可以为空，即必须至少有一个阴谋者和至少一个支援小组成员。

Byteasar 想知道有多少种方法可以将选定的人分成这两组。

最重要的是，这样的分组是否可能。

由于他完全不知道如何解决这个问题，他向你求助。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
2 2 3
2 1 3
3 1 2 4
1 3```

### 输出

```
3```

# 题解

## 作者：w4p3r (赞：43)

提供一种不用 2-SAT 的思路。

我们考虑选出的 后勤组织 的集合为 $A$ ，集合 $A$ 的大小为 $m$ 。

假设图中总边数为 $S$ ，那么 $A$ 中所有点的总 **度数** $sum$ 应该等于 $S+\binom{m}{2}$。 

显然，$sum \le S+ \binom{m}{2}$。所以在固定 $m$ 之后，我们只用判断度数最大的 $m$ 个点是否合法即可。

如果合法，可以考虑把度数最小的点换成其他度数相等的点，假设前  $m$ 个点选了 $a$ 个最小度数的点，总共有 $b$ 个最小度数的点，则贡献上 $\binom{b}{a}$ 即可。

可以做到 $O(n \log n )$ ，但因为读入都是 $O(n^2)$ 的，所以本文只实现了 $O(n^2)$。

~~（主要是我太懒了）~~

代码中取模是因为我感觉求个 $5000!$ 不取模太鬼畜了，可以证明答案是 $O(n)$ 的，所以取模也不会影响答案。

**注意特判整个图是完全图的情况**


```cpp
//W4P3R
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register int
#define fr first
#define sd second
#define pa pair<int,int>
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define MEM(a) memset(a,0,sizeof(a))
#define N 5010
const int mod=998244353;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline int lowbit(int x){return x&(-x);}
int n,deg[N],x;
int S,fac[N],inv[N];
inline int C(int n,int m){return 1LL*fac[n]*inv[m]%mod*inv[n-m]%mod;}
inline int Z(int x){return (x>=mod?x-mod:x);}
int main()
{
	//ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();FOR(i,1,n){deg[i]=read();int t=deg[i];while(t--){x=read();}S+=deg[i];}//没错这种做法边都不需要读入 
	S/=2;sort(deg+1,deg+n+1);reverse(deg+1,deg+n+1);
	fac[0]=1;
	FOR(i,1,n)fac[i]=1LL*fac[i-1]*i%mod;
	inv[0]=inv[1]=1;
	FOR(i,2,n)inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod;
	FOR(i,2,n)inv[i]=1LL*inv[i-1]*inv[i]%mod;
	int sum=0,ans=0;
	FOR(i,1,n)
	{
		sum+=deg[i];
		if(sum==S+i*(i-1)/2)
		{
			int a=0,b=0,pos=i;
			while(pos>=1&&deg[pos]==deg[i])a++,b++,pos--;
			pos=i+1;
			while(pos<=n&&deg[pos]==deg[i])b++,pos++;
			ans=Z(ans+C(b,a));
		}
	}
	if(deg[n]==n-1)ans=Z(ans+mod-1);//完全图 
	cout<<ans<<'\n';
	return 0;
}
//gl

```


**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**


---

## 作者：wyd_forever (赞：34)

### 思维挺高一题，挺好的  
$ps$:首先声明，思路来源于[这篇博客](https://www.cnblogs.com/chenyushuo/p/5128665.html)  
## $first$  
作为一道$2-SAT$的类模板题，那当然要有$2-SAT$的常规操作了。设$0$为后勤，$1$为同谋者，则显然当$x$与$y$是熟人且$x_1$时，肯定会造成$y_0$；同理，当$x,y$不是熟人且$x_0$时，肯定会造成$y_1$.  
  
按上述方法连边，然后跑一遍$2-SAT$基础操作就差不多完成了（如果还不知道$2-SAT$的话请[左转](https://www.luogu.org/problem/P4782)）。  
  
## $second$  
首先，通过每个数$2-SAT$缩点后的$belong$值，即在缩点后的点所在强连通分量的逆拓扑序。  
  
为了得到一组可行的解，只需要当$x_0$所在的强连通分量的拓扑序在$x_1$所在的强连通分量的拓扑序之后取为真(即后勤)就可以了，又由于是逆拓扑序，故将$belong_{x_0}<belong_{x_1}$的所有$x$加入后勤，其余加入同谋者，这样的解一定是一组可行解。  
  
注意：$belong$间的小于号不能改变，否则会使后续操作出锅（~~别问我是怎么知道的~~）  
  
## $third$  
最后最难的一步，也正是本题的重点：计算方案数。  
  
这里为了方便得出答案，定义一个非常重要的量——冲突点。关于冲突点我们进行如下定义：当点$x$在后勤时，其熟人$y$在同谋的话，$y$为$x$的冲突点；或者，当$x$在同谋时，其陌生人$y$在后勤的话，$y$同样为$x$的冲突点。  
  
另外我们还需要想到一个特殊的性质，在一个正解的基础上，若要得到一个新的方案最多只能将一个人替换阵营或将两个不同阵营的人替换位置。  
  
这个还算显然吧，因为后勤任两人互相认识，所以不能换两个到同谋，同理同谋也不能同时换两个到后勤。  
  
冲突点就是为了方便枚举替换方案数的。  
  
## $forth$
  
重温一下定义就知道，冲突点是可能可以替换的点。  
  
若我们在给定一个数组$contradition_i$来保存$i$的冲突点个数，易得有且仅有当$contradition_i<=1$时**可能**可以进行将$i$移动至对方阵营的新解拓展。  
  
注意，是**可能**。 
  
下面分情况讨论：
  
当$contradition_i=1$时，当且仅当其冲突点$j$满足$contradition_j=0$时可让$i$与$j$互换，否则$i$绝无可能到达对方阵营。这个的正确性也是显然。  
  
当$contradition_i=0$时，可以直接放到对方阵营(前提条件是该阵营人数大于等于二，即有放人的富余)，也可以与对方阵营中任意个同样无冲突点的点互换(这个直接用一个$tmp_1$和$tmp_2$统计一下两边阵营的无冲突点数，最后乘一下就好了)，至于仅以$i$为冲突点的情况已在上一种情况中考虑过了，不需要重复算，可以证明，其他点无法与之交换。  
  
~~于是这题被秒了~~  
  
## $fifth$  
  
**一些细节**：注意当最开始的解满足条件时加上最开始的解，当$2-SAT$跑完后$belong$冲突时直接输出$0$.  
  
另外的……应该没什么了吧……  
  
时间复杂度$O(n^2)$，都花在后面的计算了。  
  
## $sixth$  
  
贴代码(~~有略注~~)：  
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define in read()
#define re register
#define fur(i,a,b) for(re int i=a;i<=b;++i)
#define fdr(i,a,b) for(re int i=a;i>=b;--i)
#define cl(a,b) memset(a,b,sizeof(a))
#define jinitaimei signed
inline int read() //读优
{
	int x=0;
	char ch=getchar();
	for(;!isalnum(ch);ch=getchar());
	for(;isalnum(ch);ch=getchar()) x=x*10+ch-'0';
	return x;
}
const int xx=1e4+101,yy=5e3+10;
bool know[yy][yy];    //是否认识
int bel[xx],all=0;    //缩点必备
int sta[xx],top=0;
int id[xx],low[xx],num=0;
bool vis[xx],con[yy];  //con[]存储是否为同谋成员
int logis[yy],cnt_log=0;//logistics 存储后勤成员与数量
int consp[yy],cnt_con=0;//conspirator 存储同谋成员与数量
struct edge{int to,nxt;}e[yy*yy];  //邻接表
int contradition[yy],match[yy];   //前者为冲突点数量，后面是冲突点编号
int head[xx],cnt_edge=0;
inline void add(int x,int y)  //连边
{
	e[++cnt_edge]=(edge){y,head[x]};
	head[x]=cnt_edge;
}
inline void Tarjan(int g)  //缩点
{
	low[g]=id[g]=++num;
	vis[g]=true;
	sta[++top]=g;
	for(int i=head[g];i;i=e[i].nxt)
	{
		int j=e[i].to;
		if(!id[j])
		{
			Tarjan(j);
			low[g]=min(low[g],low[j]);
		}
		else if(vis[j]) low[g]=min(low[g],id[j]);
	}
	if(id[g]!=low[g]) return;
	++all;
	do
	{
		int tp=sta[top];
		bel[tp]=all;
		vis[tp]=false;
	}
	while(sta[top--]!=g);
}
jinitaimei main()
{
	int n=in;
	fur(i,1,n)
	{
		int k=in,x;
		while(k--) x=in,know[i][x]=true;
	}
	fur(i,1,n) fur(j,1,n) if(i!=j)
	{
		if(know[i][j]) add(i+n,j);
		else add(i,j+n);
	}
	fur(i,1,2*n) if(!id[i]) Tarjan(i);
	fur(i,1,n)     //分阵营
	{
		if(bel[i]==bel[i+n]) puts("0"),exit(0);
		if(bel[i]<bel[i+n]) logis[++cnt_log]=i;
		else consp[++cnt_con]=i,con[i]=true;
	}
	int ans=(cnt_log&&cnt_con),tmp1=0,tmp2=0;//若两阵营人数不为零，加上初始解
	fur(i,1,cnt_log) fur(j,1,cnt_con) if(know[logis[i]][consp[j]]) ++contradition[logis[i]],match[logis[i]]=consp[j];
	fur(i,1,cnt_con) fur(j,1,cnt_log) if(!know[consp[i]][logis[j]]) ++contradition[consp[i]],match[consp[i]]=logis[j];//冲突点初始化
	fur(i,1,n) if(contradition[i]==1) if(!contradition[match[i]]) ++ans;//当冲突点唯一，且对方无冲突点，则可交换二者，答案加一
	fur(i,1,n) if(!contradition[i])//无冲突点时
	{
		if((con[i]&&cnt_con>1)||(!con[i]&&cnt_log>1)) ++ans;//若己方阵营人数大于一，可将该点放入对方阵营，答案加一
		if(con[i]) ++tmp2; //统计同谋者无冲突点的点数
		else ++tmp1; //统计后勤无冲突点的点数
	}
	ans+=tmp1*tmp2; //统计两阵营无冲突点可直接交换的方案数
	printf("%d\n",ans);//额……输出答案
	return 0;
}
```
完结撒花，$QwQ$.

---

## 作者：双管荧光灯 (赞：21)

神仙都会2-SAT，但对于我这种什么都不会的蒟蒻来说怎么办呢（

这里提供一种简单做法

我们观察一下合法图的性质，可以得到一个显然又有用的性质：对于所有团中的点度数都大于等于独立集中的点

所以这题构造方案就非常好做啦，按度数排序，能加进团就加，不能加就停止，再判断一下方案是否合法就行啦

考虑方案数，对于每一个方案，因为我们能加就加，所以团的点数已经达到最大值，我们只有两种方案，一种是踢掉一个团内度数等于团点数-1的点，一种是将一个不再团内的度数等于团点数-1的点与一个团内度数等于团点数-1的点交换，这两种操作都只要比较度数就行

Code：（比2-SAT好写多了，因为常数小在LOJ上跑了rank1

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,d[5005],i,x[5005],aa,ab,j,a,ans;
bitset<5005> g[5005],tmp;
bool cmp(int a,int b)
{
	return d[a]>d[b];
}
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    char ch=nc();int sum=0;
    while(!(ch>='0'&&ch<='9'))ch=nc();
    while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=nc();
    return sum;
}
int main()
{
	n=read();
	for(i=1;i<=n;++i)
	{
		x[i]=i;
		d[i]=read();
		for(j=1;j<=d[i];++j)
		{
			a=read();
			g[i][a]=1;
		}
	}
	sort(x+1,x+1+n,cmp);
	for(i=1;i<=n;++i)
		if((g[x[i]]&tmp).count()==tmp.count())
			tmp[x[i]]=1;
		else
			break;
	int num=i-1;
	for(i=num+1;i<=n;++i)
		for(j=i+1;j<=n;++j)
			if(g[x[i]][x[j]])
			{
				puts("0");
				return 0;
			}
	ans=1;
	if(num==n)
		--ans;
	if(num!=1)
		for(i=1;i<=num;++i)
			if(d[x[i]]==num-1)
				++ans;
	for(i=num+1;i<=n;++i)
		if(d[x[i]]==num-1)
		{
			for(j=1;j<=num;++j)
				if(!g[x[i]][x[j]])
					break;
			if(d[x[j]]==num-1)
				++ans;
		}
	cout<<ans<<endl;
}

```


---

## 作者：ycyaw (赞：12)

题目大意就是，给出$n$个点，分成一个团和一个独立集的方案数。

刚看到题没什么思路，稍微想一想，我们可以得到一个初步的结论。

我们发现，如果我们找到了一组合法的方案，那么我们从团中移出两个点到独立集中是不可行的，因为这两个点必定有边。同理，从独立集移两个点到团中也是不可行的，因为这两个点之间必定没有边。

由此我们发现，对于一个合法的方案，所以如果有另外合法的方案，必定只能在这个方案的基础上改变一个点$($把一个点从独立集移到团中,或把一个点从团移到独立集中，或交换独立集和团中的各一个点$)$。

那么我们考虑怎么找合法的方案？

显然的$2-SAT$问题，每个点拆两个点,表示分到团里还是团外，$i($编号是$i\times 2-1)$表示团里，$i'($编号是$i\times 2)$表示团外。

若$i,j$有边，$i'->j,j'->i$；若没边，$i->j',j->i'$。$($箭头表示连边$)$。

然后我们利用拓扑序就能找到一组合法解。$($不清楚的话可参考$2-SAT$模板$)$

剩下就是求之前所说的改变一个点可以到达的方案。$n^2$统计一下即可。~~只是一个小模拟~~ 还有，$yy$一下发现$2$要特判。

$Code\ Below:$
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
#define pc putchar
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
const int N=5005;
int n,dfn[N<<1],low[N<<1],st[N<<1],top,ans;
int col[N<<1],dep,vis[N<<1],p[N],col_cnt,nei[N],c1,wai[N],c2,a[N],b[N];
bool f[N][N];
vector<int> g[N<<1];
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-ff;ch=getchar();}
    while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+ch-'0';ch=getchar();}
    return ret*ff;
}
void write(int x){
    if(x<0){x=-x;putchar('-');}
    if(x>9) write(x/10);
    putchar(x%10+48);
}
void writeln(int x){write(x),hh;}

void add(int x,int y){
    g[x].push_back(y);
}
void tarjan(int now){
    dfn[now]=low[now]=++dep;
    st[++top]=now;
    vis[now]=1;
    for(int i=0;i<(int)g[now].size();i++){
        int v=g[now][i];
        if(!dfn[v]){
            tarjan(v);
            low[now]=min(low[now],low[v]);
        }
        else if(vis[v]) low[now]=min(low[now],low[v]);
    }
    if(dfn[now]==low[now]){
        col_cnt++;
        int t;
        do{
            t=st[top];
            top--;
            vis[t]=0;
            col[t]=col_cnt;
        }while(t!=now);
    }
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++){
        int x=read();
        while(x--){
            int t=read();
            f[i][t]=1;
        }
        for(int j=1;j<=n;j++){
            if(i^j){
                if(f[i][j]) add(i*2,j*2-1);
                else add(i*2-1,j*2);
            }
        }
    }
    if(n==2){
        write(2);
        return 0;
    }
    for(int i=1;i<=2*n;i++)
        if(!dfn[i])
            tarjan(i);
    for(int i=1;i<=n;i++){
        if(col[i*2-1]==col[i*2]){
            write(0);
            return 0;
        }
    }
    for(int i=1;i<=n;i++) p[i]=col[i*2-1]>col[i*2];
    //col[i]>col[j]说明i拓扑序小于j,则取j 
    //所以p[i]=0则在团内 
//    for(int i=1;i<=n;i++) write(p[i]),pc(' ');
    for(int i=1;i<=n;i++){
        if(!p[i]) nei[++c1]=i;
        else wai[++c2]=i;
    }
    int ans=1;
    for(int i=1;i<=c1;i++){
        int x=nei[i],cnt=0;
        for(int j=1;j<=c2;j++){
            int y=wai[j];
            if(f[x][y]){
                if(cnt==1){
                    a[i]=1e9;//不能动
                    break;
                }
                cnt++;
                a[i]=y;
            }
        }
    }
    for(int i=1;i<=c2;i++){
        int x=wai[i],cnt=0;
        for(int j=1;j<=c1;j++){
            int y=nei[j];
            if(!f[x][y]){
                if(cnt==1){
                    b[i]=1e9;
                    break;
                }
                cnt++;
                b[i]=y;
            }
        }
    }
    if(c1!=1){
        for(int i=1;i<=c1;i++)
        if(!a[i])
            ans++;//把i换出去
    }
    if(c2!=1){
        for(int i=1;i<=c2;i++)
        if(!b[i])
            ans++;//把i换进来 
    }
    for(int i=1;i<=c1;i++)
        for(int j=1;j<=c2;j++)
            if((a[i]==wai[j]||!a[i])&&((b[j]==nei[i]||!b[j])))
                ans++;
    write(ans);
    return 0;
}
```


---

## 作者：bits47 (赞：6)

思路来源于 wyd_forever 的题解，并对答案统计做出简化，删去不必要的讨论。

# 2-SAT计数 [P3513 [POI2011] KON-Conspiracy](https://www.luogu.com.cn/problem/P3513)
构造一个新的方案可以从一个可行解中**替换一个人的阵营**或**对调两个不同阵营的人**。

定义**冲突点对**为若把 $x$ 放到 $y$ 点所在部分去后会矛盾的点（$x,y$ 属于两部分）。

先根据前线互不认识和后勤互相认识建图跑 2-SAT ，把原图按反拓扑序先后划分为前线和后勤两部分（常规处理出一个正解，不会左转 [P4782 【模板】2-SAT 问题](https://www.luogu.com.cn/problem/P4782)），再处理出每个点的**冲突点对数**和其中**一个冲突点**。

一种新的方案只能通过以下两种操作之一构造：

- 替换一个人的阵营：冲突点对数为 $0$ 且原阵营人数大于 $1$。
- 对调两个不同阵营的人：冲突点对数为 $1$ 且对应的冲突点的冲突点对数为 $0$。

理由：

1. 后勤任意两人互相认识，所以不能换两个到前线，同理前线也不能同时换两个到后勤。所以每个阵营最多改变一个（可互换、可增减）。
2. 若存在冲突点对数为 $0$ 的点，这些点一定都在同一个阵营里(想想看，如果一个后勤和所有前线都不认识，起冲突点对数为 $0$，但必然不存在一个前线和所有后勤都认识，反之亦然)。所以不存在两个 $0$ 互换，只能把冲突点对数为 $0$ 扔到另一边，或对调冲突点对数为 $1$ 且对应的冲突点的冲突点对数为 $0$ 的两点。

```cpp
void tarjan(int u){
	dfn[u]=low[u]=++tot,vis[u]=1,st.push(u);
	int len=vec[u].size(),v;
	for(int i=len-1;i>=0;--i){
		v=vec[u][i];
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		++sum;
		do{
			v=st.top(),st.pop();
			co[v]=sum,vis[v]=0;
		}while(v!=u);
	}
}
int main() {
	n=read();//x前线，x+n后勤
	for(int i=1;i<=n;++i){
		k=read();
		for(int j=1;j<=k;++j) x=read(),b[i][x]=1;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			if(b[i][j]) vec[i].push_back(j+n);//b--是否为熟人
			else if(i!=j) vec[i+n].push_back(j);
		}
	for(int i=n+n;i>=1;--i) if(!dfn[i]) tarjan(i);
	//bel--属于前线(0)/后勤(1)
	for(int i=1;i<=n;++i){//按反拓扑序分类
		if(co[i]==co[i+n]){printf("0");return 0;}
		if(co[i]<co[i+n]) q[0][++num[0]]=i;
		else q[1][++num[1]]=i,bel[i]=1;
	}
	if(num[0]&&num[1]) ans=1;
	for(int i=1;i<=num[0];++i){
		for(int j=1;j<=num[1];++j){//处理冲突点 
			if(!b[q[0][i]][q[1][j]]) ++cnt[q[0][i]],id[q[0][i]]=q[1][j];
			if(b[q[0][i]][q[1][j]]) ++cnt[q[1][j]],id[q[1][j]]=q[0][i];
		}
	}
	for(int i=1;i<=n;++i){
		if(!cnt[i]){
			++c0[bel[i]];//统计冲突点数为0的点
			if(num[bel[i]]>1) ++ans;//冲突点对数为0且原阵营人数大于1，可替换这个人的阵营
		}
		if(cnt[i]==1&&!cnt[id[i]]) ++ans; //冲突点对数为1，且对应的冲突点的冲突点对数为0，可对调这两个人
	}
	printf("%d",ans);
    return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

一眼 2-SAT。

考虑后勤者是 $0$，同谋者是 $1$。

如果不同的人 $u$ 和 $v$ 互相认识，那么 $u$ 是 $1$ 可以推出 $v$ 是 $0$。如果他们不认识，那么 $u$ 是 $0$ 可以推出 $v$ 是 $1$。

构造出一组解是 2-SAT 的经典问题。然而“2-SAT”问题的解数可能就没有那么典了。

在这道题里面，考虑我们现在构造出了一组解，后勤者的集合是 $S_1$，同谋者的集合是 $S_2$。

显然，另外一种情况，不可能有两个原来在 $S_1$ 中的人现在都不在 $S_1$ 中。因为他们必定互相认识。另一方向同理。

所以最后，$S_1$ 和 $S_2$ 分别最多各出去一个人。于是，我们可以直接枚举，然后快速判定是否合法。复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5000+10,MAXM=1e4+10;
int n,dfn[MAXM],low[MAXM],in[MAXM],col[MAXM],tot,colid;
stack<int> st;
bitset<MAXN> flg[MAXN];
void tarjan(int u) {
	dfn[u]=low[u]=++tot,in[u]=1,st.push(u);	
	int pos=u; if(pos>n) pos-=n;
	ffor(i,1,n) if(i!=pos) {
		int v=-1;
		if(flg[pos][i]&&u>n) v=i;
		if(!flg[pos][i]&&u<=n) v=i+n;
		if(v!=-1) {
			if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
			else if(in[v]) low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]) {
		++colid;
		while(st.top()!=u) col[st.top()]=colid,in[st.top()]=0,st.pop();
		col[u]=colid,in[u]=0,st.pop();
	}
	return ;
}
vector<int> S1,S2;
int deg[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) {
		int cnt; cin>>cnt;
		ffor(j,1,cnt) {
			int nxt; cin>>nxt;
			flg[i][nxt]=1;
		}
	}
	ffor(i,1,n+n) if(dfn[i]==0) tarjan(i);
	S1.push_back(0),S2.push_back(0);
	ffor(i,1,n) if(col[i]==col[i+n]) return cout<<0,0;
	ffor(i,1,n) if(col[i]<col[i+n]) S1.push_back(i); else S2.push_back(i);
	int ans=0,cnt0=S1.size()-1,cnt1=S2.size()-1;
	for(auto id0:S1) if(id0) for(auto id1:S2) if(id1) deg[id0]+=flg[id0][id1];	
	for(auto id1:S2) if(id1) for(auto id0:S1) if(id0) deg[id1]+=!flg[id0][id1];
	for(auto id0:S1) for(auto id1:S2) {
		int Cnt0=cnt0-!!id0+!!id1,Cnt1=cnt1-!!id1+!!id0;
		if(!Cnt0||!Cnt1) continue ;
		int v1=0,v2=0;
		if(id0) v1=deg[id0];
		if(id1) v2=deg[id1];
		if(id0&&id1) v1-=flg[id0][id1],v2-=!flg[id0][id1];
		if(!v1&&!v2) ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：3)

[P3513](https://www.luogu.com.cn/problem/P3513)。

同谋者和后勤者两个状态，有一些关系（熟人不能都是同谋者，不是熟人不能都是后勤组），2-SAT 显然，这里就不讲了，不会的去[模板](https://www.luogu.com.cn/problem/P4782)。

感觉本题 2-SAT 好想，重点是统计方案。

接下来的重点是统计方案数，因为 2-SAT 已经帮助我们构造了一个方案，考虑调整这个方案。

下文中我用 `认识` 代表两个人为熟人，这里，`认识` 是双向的。

发现这个方案好像很难调，难道这题不可做？

观察条件：

- 后勤组任意两人都是熟人。

- 同谋者任意两人都不是熟人。

那么，后勤组里的两个人，由于必然认识，所以不能同时调到同谋者；同理，同谋者里的两个人，不能同时调到后勤者。

所以，调人只有下面两个状态：

1. 改变他的组别。

2. 将两个组别的人调换位置。

正如其他题解指出的，我们可以定义一个矛盾对数 $tag_i$，用来表示第 $i$ 个点调到另一个职位矛盾的人数。

比如说，对于一个同谋者来说，在后勤组里与他认识的人的数量就是矛盾对数。

统计两个组别的人数，如果人数满足要求，可以直接让答案 $sum$ 增加。

现在看一下第一个方案满足的条件：

- 该组别的 $s$ 需要大于 $1$，为了保证每一个组都有人。

- 该人的矛盾对数为 $0$，因为只有他调过去。

看一下第二个方案满足的条件：

- 两个人不在同一组别，不然换了没效果。

- 一个 $tag$ 为 $1$，另一个为 $0$（由于在我的程序中正反都会枚举到，所以就只判断了一个）。

解释一下上面的第二条。

$tag\le1$ 应该都好理解，应为需要改变之后没有矛盾，显然矛盾对数不能超过 $1$，否则改不了。

不妨两个人为 $i,j$，$i$ 为同谋组，$j$ 为后勤组，其余情况其实是差不多的。

如果 $i$ 认识 $j$，那么 $tag_i$ 会因为 $j$ 增加 $1$，$tag_j$ 不会因为 $i$ 增加 $1$；如果 $i$ 不认识 $j$ 同理。

因为必然 $i$ 认识 $j$，或者 $i$ 不认识 $j$，所以两个 $tag$ 不会同时为 $1$ 或者 $0$。

当 $tag_i=1,tag_j=0$ 的时候，下面说明必然可行。

$tag_j=0$ 说明了 $i$ 不认识 $j$，而且 $j$ 不认识同谋组里所有人。

因为 $i$ 不认识 $j$，所以 $tag_i\ge1$，而因为 $tag_i=1$，所以 $i$ 认识后勤组里除了 $j$ 以外的所有人。

故可交换 $i,j$。

证毕。

代码就很好写了。

如果被卡空间了，可以把邻接表换成邻接矩阵，然后用 bool 存储，这样 $280$ 多 MB 直接变成 $48$ MB（不含栈空间）。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5005;
bool f1;
int n, m, x, cnt, idx, dfn[N << 1], low[N << 1], q[N << 1], t, to[N << 1], tem, ans[N], ccnt, tag[N], s[2];
long long sum;
bool vis[N << 1], a[N][N], b[N][N];
bool f2;
vector<int>S[N << 1];
inline void IM(){
	printf("0\n");
	exit(0);
}
inline void add(int x, int y){
	b[x][y] = 1;
}
inline void tarjan(int x){
	low[x] = dfn[x] = ++idx;
	q[++t] = x;
	vis[x] = 1;
	int val = x > n ? 0 : n;
	for(int i = 1 + val; i <= n + val; i++){
		if(!b[x][i]) continue ;
		if(!dfn[i]){
			tarjan(i);
			low[x] = min(low[x], low[i]);
		}
		else if(vis[i]) low[x] = min(low[x], dfn[i]);
	}
	if(dfn[x] == low[x]){
		cnt++;
		while(vis[x]){
			to[q[t]] = cnt;
			vis[q[t]] = 0;
			tem = q[t];
			if(tem > n) tem -= n;
			if(to[tem] == to[tem + n]) IM();
			S[cnt].push_back(q[t--]);
		}
	}
}
inline bool check(int id){
	for(auto x : S[id]){
		tem = x;
		if(tem > n) tem -= n;
		if(~ans[tem]) return 0;
	}
	return 1;
}
inline void go(int id){
	for(auto x : S[id]){
		if(x > n) ans[x - n] = 1;
		else ans[x] = 0;
		ccnt++;
	}
}
int main(){
//	printf("%.2lfMB\n", (&f2 - &f1) / 1024.0 / 1024.0);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &m);
		for(int j = 1; j <= m; j++){
			scanf("%d", &x);
			a[i][x] = 1;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			if(a[i][j]){
				add(i + n, j);
				add(j + n, i);
			}
			else{
				add(i, j + n);
				add(j, i + n);
			}
		}
	}
//	for(int i = 1; i <= n << 1; i++, putchar('\n')) for(int j = 1; j <= n << 1; j++) printf("%d ", b[i][j]);
	for(int i = 1; i <= n << 1; i++){
		if(!dfn[i]) tarjan(i);
	}
	memset(ans, 0xff, sizeof(ans));
	for(int i = 1; i <= cnt; i++){
		if(check(i)) go(i);
	}
	if(ccnt < n) IM();
	for(int i = 1; i <= n; i++){
		s[ans[i]]++;
		for(int j = i; j <= n; j++){
			if(ans[i] == ans[j]) continue ;
			if(ans[i]){
				if(a[i][j]) tag[j]++;
				else tag[i]++;
			}
			else{
				if(a[i][j]) tag[i]++;
				else tag[j]++;
			}
		}
	}
	if(s[0] && s[1]) sum++;
	for(int i = 1; i <= n; i++){
		if(s[ans[i]] == 1) ;
		else if(tag[i] == 0) sum++;
		for(int j = 1; j <= n; j++){
			if(ans[i] == ans[j]) continue ;
			if(tag[i] == 1 && tag[j] == 0) sum++;
		}
	}
	printf("%lld\n", sum);
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 前言
这是一道神仙题，思路挺巧妙的。
# 思路
我们首先可以发现这是一个 2-SAT，那么我们先想如何建模，首先如果两个人是好友关系（后面用 $i$ 和 $j$ 表示），那么如果第 $i$ 个人进了同谋者则 $j$ 必须进后勤组，如果两人不是好友关系则第 $i$ 个人进后勤组第 $j$ 个人必须进同谋组，然后就跑一遍 2-SAT 模板即可，然后就可以判无解了。

但是，这道题要求求出方案数，所以我们先要得出一个结论，对于一种可行解一定不能将同一组的两个及以上的人拿到另一组去（这个应该一看就懂，就不证明了）。

那么我们就能得到 $3$ 种转换方式分别是：从两组中任选一组拿一人到另外一组以及从两组中分别选一人进行交换。

然后我们就可以先预处理出 $id_i$ 以及 $cnt_i$ 分别表示当 $i$ 拿到另一组后会与 $i$ 出现矛盾的点的下标和 $i$ 到另一组后会出现矛盾的点的数量，然后我们再对三种情况进行讨论。

- 如果是将 $i$ 单独拿到另一组，那么我们首先要满足 $i$ 拿过去后不会出现矛盾即 $cnt_i$ 等于 $0$，这里需要判断拿过去后当前组是否还有人。

- 当要将 $i$ 与某个点交换时且 $cnt_i$ 等于 $0$，那么我们就只能交换那些换过去也不会出现矛盾的点（即 $cnt_j$ 也等于 $0$）。

- 当要将 $i$ 与某个点交换时且 $cnt_i$ 等于 $1$，那么我们就可以拿出与 $i$ 矛盾的那一个点，如果 $cnt_{id_i}$ 等于 $0$ 时才可以交换。

- 当要将 $i$ 与某个点交换时且 $cnt_i>1$ 时我们无法进行任何交换因为交换一下只能抵消掉一对矛盾，所以无论如何交换都会剩有矛盾。

这里我们还需判断一开始求出的那组的两个组别的人数是否都大于 $1$，如果满足则答案初始化为 $1$ 否则为 $0$。

注意这道题的空间给得有点小。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%d",&x)
#define lcm(x,y) x*y/__gcd(x,y) 
#define il inline
#define pb push_back
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
const int N=5010;
int mp[N][N];
vector<int>v[N<<1];
int dfn[N<<1],low[N<<1],idx;
int is[N<<1],co[N<<1],cnt,n;
int id[N],_cnt[N];
stack<int>s;
il void dfs(int x) {//模板 
	dfn[x]=low[x]=++idx;
	s.push(x);
	is[x]=1;
	for(auto to:v[x]) {
		if(!dfn[to]) dfs(to),low[x]=min(low[x],low[to]);
		else if(is[to]) low[x]=min(low[x],dfn[to]);
	}
	if(low[x]==dfn[x]) {
		int p;
		cnt++;
		do{
			p=s.top();
			s.pop();
			is[p]=false;
			co[p]=cnt;
		}while(p!=x);
	}
}
/*
1~n 合作
n+1~2*n 不认识 
*/
int res;
vector<int>a,b;
fire main() {
	in(n);
	rep(i,1,n) {
		int w;
		in(w);
		rep(j,1,w) {
			int x;
			in(x);
			mp[i][x]=1;
			v[i+n].pb(x);//连边 
		}
		rep(j,i+1,n) if(!mp[i][j]) v[i].pb(j+n),v[j].pb(i+n);//连边 
	}
	rep(i,1,2*n) if(!dfn[i]) dfs(i);
	rep(i,1,n) {
		if(co[i]==co[i+n]) {
			cout<<"0";//无解 
			return false;
		}
		if(co[i]<co[i+n]) a.pb(i);//找出这一组中两组成员 
		else b.pb(i);
	}
	if(a.size()&&b.size()) res=1;
	for(auto x:a) {
		for(auto y:b) {
			if(mp[x][y]) id[x]=y,_cnt[x]++;//预处理矛盾 
			else id[y]=x,_cnt[y]++;
		}
	}
	int tot=false,_tot=false;
	for(auto y:b) if(!_cnt[y]) tot++; //预处理 
	for(auto x:a) if(!_cnt[x]) _tot++;
	for(auto x:a) {
		if(!_cnt[x]) res+=(a.size()>1?1:0)+tot;//分类讨论 
		else if(_cnt[x]==1){
			int y=id[x];
			if(!_cnt[y]) res++;
		}
	}
	for(auto y:b) {
		if(!_cnt[y]) res+=(b.size()>1?1:0)+_tot;
		else if(_cnt[y]==1){
			int x=id[y];
			if(!_cnt[x]) res++;
		}
	}
	printf("%d\n",res);
	return false;
}
```

---

## 作者：_anll_ (赞：1)

个人认为是很有思维含量的一道~~毕竟[交了16发左右](https://www.luogu.com.cn/record/list?pid=P3513&user=Aaa_liang&page=1)~~
## 题目大意
给你 $n$ 个人和 $m$ 个熟人关系，你要把这 $n$ 个人分为两组，$A$ 组内任意二人都不能相互熟悉，$B$ 组内任意两人都必须相互熟悉，求合理分组的方案数。

## 大体思路
前置芝士：[P4782 【模板】2-SAT](https://www.luogu.com.cn/problem/P4782)，也可以查看这篇蒟蒻写的[学习笔记](https://www.luogu.com.cn/blog/is-saliang-awa/post-2-sat)。

我们约定，对于一个点加入同谋会的编号为 $i$，加入后勤则为 $i+n$。

看到 `两人` 和 `必须` 这种话术就可以联想到 2-sat，而恰恰这个题建图也是很裸的 2-sat。如果 $i$ 和 $j$ 为熟人，则 $i$ 向 $j+n$ 连边；否则 $j$ 向 $i+n$ 连边。

建边很容易，难的是如何统计方案数。没有思路的话不妨先把第一个方案求出来，再慢慢探索。我们发现，如果要把一个人从同谋调到后勤，要么后勤中全是熟人可以直接转过去，要么后勤中只有一个人不熟，存在冲突，这样就可以对调。同理，如果你要从后勤调到同谋，同谋中也最多只能有一个人不认识。我们可以拿一个数组 $pl$ 存冲突的人，即如果 $i$ 与 $j$ 存在冲突，那我们就把 $pl_i=j$。而我们可不可以同时把两个人从同谋调到后勤呢？我们知道，在同谋中的任何两个人都不认识，如果一起调的话就会让后勤里存在至少两个不认识的人。反之也是一样。**这就意味着每次最多对调/单调一个人。**

大体思路想好了，我们再来扣扣细节。不妨分类讨论对调与单调的情况：

如果我们要把 $i$ 和 $j$ 对调，那只能存在一个人有冲突，即 $pl_i=j$，而 $pl_j=0$。这里个人认为有点难理解，我的理解大概是这样的：因为关系是双向的，如果你 $i$ 在同谋，$j$ 在后勤，那对于 $i$ 来说他和 $j$ 不熟，存在冲突；而 $j$ 和 $i$ 不熟，正好，没有冲突。

而如果我们只是把 $i$ 单调，那就要求 $i$ 属于的组别至少存在两个人，不然 $i$ 一走那个组别就没人了。

思路大概就是这样，下面来一些注意事项：

1. 如果在建立第一个方案时发现根本建立不出来，直接输出 $0$ 就好了。

1. 如果在建立第一个方案时发现有组别没人，那 $ans$ 初始化就为 $0$，否则为 $1$。

1. 如果习惯写 `define int long long` 邪教，起码在这道题，请改掉。

## 代码演示
大体思路就是这样，如果有不清楚/不清晰的地方，还请结合代码和注释理解。
```cpp
#include<iostream>
#include<cstring>
using namespace std;
struct Edge{
    int l,nxt;
}edges[25000005];
int n,tt=1,head[10005];
int tot,dfn[10005],low[10005];
int top,instk[10005],stk[10005];
int cnt,scc[10005],pl[10005],ml[2];
bool vu[5005][5005],mp[10005];
void add_edge(int f,int l){
    tt+=1;
    edges[tt]={l,head[f]};
    head[f]=tt;
}
void tarjian(int x){
    tot+=1,top+=1;
    dfn[x]=low[x]=tot;
    instk[x]=1,stk[top]=x;
    for(int i=head[x];i;i=edges[i].nxt){
        int l=edges[i].l;
        if(!low[l]){
            tarjian(l);
            low[x]=min(low[x],low[l]);
        }
        else if(instk[l]) low[x]=min(low[x],dfn[l]);
    }
    if(dfn[x]==low[x]){
        int y;cnt+=1;
        do{
            y=stk[top],top-=1,instk[y]=0;
            scc[y]=cnt;
        }while(y!=x);
    }
}
signed main(){
    int op,l;
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>op;
        for(int j=1;j<=op;j++){
            cin>>l;
            vu[i][l]=1;//为熟人
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            if(vu[i][j]){add_edge(i,j+n);}
            else{add_edge(i+n,j);}
        }
    }
    for(int i=1;i<=2*n;i++) if(!low[i]) tarjian(i);
    for(int i=1;i<=n;i++){
        if(scc[i]==scc[i+n]){
            cout<<0;
            return 0;
        }
        //打组别标记+存每个组别的人数
        if(scc[i]<scc[i+n]) mp[i]=1,ml[1]+=1;
        else ml[0]+=1;
    }
    int ans=(ml[0]&&ml[1]);//初始化ans
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(mp[i]==mp[j]) continue;
            if(mp[i]!=vu[i][j]){//存在冲突
                if(pl[i]){
                    pl[i]=-1;//冲突>=2
                    break;
                }
                pl[i]=j;//冲突=1就存下让i产生冲突的人
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(pl[i]==-1) continue;
        if(!pl[i]){if(ml[mp[i]]>=2) ans+=1;}//不存在冲突 一定一定要注意if对应关系！（血的教训）
        else if(!pl[pl[i]]) ans+=1;//存在冲突
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：Z1qqurat (赞：0)

可以说是特殊情况下的 2-SAT 方案数统计，我并不认为别的情况也能这样求方案数。

首先我们将后勤视作 $0$，同谋视作 $1$，如果 $u$ 认识 $v$，那么如果 $u=1$ 的话 $v\ne 1$，即 $u=1\to v=0$；如果 $u$ 不认识 $v$，那么如果 $u=0$ 的话 $v\ne 0$，即 $u=0\to v=1$，注意这里 $u\ne v$。

然后我们试图通过先随便构造一组可行解，来得出其他的解。容易发现，如果在目前这组可行解 $S_0,S_1$ 中，$u,v$ 都在 $S_0$ 中，那么 $u,v$ 不可能同时移到 $S_1$ 中，因为 $u,v$ 互相认识。所以我们每次调整一组方案，至多从 $S_0,S_1$ 中各选出 $0/1$ 个节点挪到对面集合中，这样的调整至多 $n^2$ 种。

考虑如何快速判断一种调整是否可行。记录对于目前的任意解，$cnt_u$ 表示 $u$ 在对面集合中有多少熟人，通过选出来交换的两数 $u,v$ 之间的熟人关系以及预处理好的 $cnt_u,cnt_v$ 便可以 $\mathcal{O}(1)$ 判断某种调整是否可行。注意 $|S_0|,|S_1|$ 都要 $>0$ 的限制，有一些小细节。

```cpp
#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)
#define All(v, l, r) &v[l], &v[(r) + 1]
#define NOSOL return cout << "0\n", 0
using i64 = int64_t;
using db = double;
using std::cin;
using std::cout;
constexpr int N = 5005, M = 1e4 + 5;

int n;
std::array<std::array<bool, N>, N> a;
std::array<int, N> cnt;

std::array<std::vector<int>, M> G;
int tot, id;
std::array<bool, M> ons;
std::array<int, M> dfn, low, scc;
std::stack<int> stk;

auto tarjan(int u) -> void {
   dfn[u] = low[u] = ++tot;
   stk.emplace(u), ons[u] = 1;
   for (auto v : G[u]) {
      if (!dfn[v]) tarjan(v), low[u] = std::min(low[u], low[v]);
      else if (ons[v]) low[u] = std::min(low[u], dfn[v]);
   }

   if (low[u] == dfn[u]) {
      id++;
      while (!stk.empty()) {
         auto v = stk.top(); stk.pop();
         ons[v] = 0, scc[v] = id;
         if (v == u) break;
      }
   }
   return ;
}

std::array<std::vector<int>, 2> s;

auto main() -> int {
   std::ios::sync_with_stdio(false);
   cin.tie(nullptr), cout.tie(nullptr);

   cin >> n;
   for (auto i = 1, k = 0, x = 0; i <= n; ++i) {
      cin >> k;
      while (k--) cin >> x, a[i][x] = 1;
      for (auto j = 1; j <= n; ++j) {
      	if (i == j) continue;
         if (a[i][j]) G[i + n].emplace_back(j);
         else G[i].emplace_back(j + n);
      }
   }

   for (auto i = 1; i <= (n << 1); ++i) if (!dfn[i]) tarjan(i);
   for (auto i = 1; i <= n; ++i)
      if (scc[i] == scc[i + n]) NOSOL;
   for (auto i = 1; i <= n; ++i)
      s[scc[i] > scc[i + n]].emplace_back(i);
   for (auto u : s[0])
      for (auto v : s[1]) cnt[u] += a[u][v], cnt[v] += a[v][u];
   
   auto ans = 0;
   if (s[0].size() > 1)
   	for (auto u : s[0]) if (!cnt[u]) ans++;
   if (s[1].size() > 1)
   for (auto v : s[1]) if (cnt[v] == s[0].size()) ans++;
   if (s[0].size() && s[1].size()) {
   	ans++;
   	for (auto u : s[0])
      	for (auto v : s[1])
         	if (cnt[u] - a[u][v] == 0 && cnt[v] - a[u][v] == s[0].size() - 1) ans++;
   }
   cout << ans << "\n";
   return 0;
}
```

---

