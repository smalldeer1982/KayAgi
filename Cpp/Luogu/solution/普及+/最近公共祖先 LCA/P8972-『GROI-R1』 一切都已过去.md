# 『GROI-R1』 一切都已过去

## 题目背景

悦关上窗，拉上帘布。

果然还是想不起来啊。

隐约记得曾和什么人一起做过这样的事。

仰面躺下，手执一只木笺。

「究竟如何，才能拥有“过去”啊……」

她闭上双眼。

「6 岁前的记忆……究竟如何才能寻回？」

## 题目描述

悦正在寻找她的记忆。忽然，她来到了有 $n$ 个节点的一棵树上。树上每一条边都有各自边权，每一个点都有各自的点权。

「把经历都聚拢起来，能完整地复原吗……」

悦从树上的一个点，慢慢地走到了另一个点，可是她什么也没找到。但是，她不知道，玘一直在远处望着她走过的道路。

玘发现，悦全程****没有走回头路****。他想把悦****走过的每一条边的边权乘起来****，可惜他发现他遇到了一个这一生未曾见到过的数字。

「为什么会这样呢？」

玘想到悦是突然出现在树上的，最初的点一定有蹊跷！他****把最初那个点的点权乘上****……

突然，一束彼岸花的红光亮起！世界重新安静了下来。

悦看到了玘留下的字样，可惜她不能从中看出任何过去的记忆。现在，你要帮她判断：把经历都聚拢起来，****能完整地复原过去吗****？我们称悦的一条路径能“复原过去”，当且仅当玘****留下的乘积是一个整数****。

**形式化题面**

给定一棵 $n$ 个节点的树和 $q$ 次询问。每次询问给出两个整数 $x,y$，表示询问树上以 $x$ 和 $y$ 为端点的简单路径上边权乘积与点 $x$ 的点权相乘是否为整数。

## 说明/提示

**样例解释**

根据输入可以得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3e4jqu6f.png)

对于第一个询问 $(1,5)$ 可以发现悦经过的边的边权分别是 $0.1$ 和 $0.99$，她出发的 $1$ 号点的点权为 $1$。$1\times0.1\times0.99=0.099$ 不是整数。所以输出 `No`。

对于后面两次询问同理。

**数据范围**

**本题采用捆绑测试。**

| 子任务编号 | 数据范围 | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $\text{Subtask1}$ | $n,q\le3\times 10^3$ |  | $15$ |
| $\text{Subtask2}$ | $n\le500$，$q\le10^5$ |  | $10$ |
| $\text{Subtask3}$ | $n,q\le10^5$ | $\text{BE}$ | $10$ |
| $\text{Subtask4}$ | $n,q\le10^5$ | $\text{A}$ | $5$ |
| $\text{Subtask5}$ | $n,q\le10^5$ | $\text{B}$ | $10$ |
| $\text{Subtask6}$ | $n,q\le10^5$ | $\text{C}$ | $5$ |
| $\text{Subtask7}$ | $n,q\le10^5$ | $\text{D}$ | $10$ |
| $\text{Subtask8}$ | $n,q\le2×10^5$ |  | $35$ |

特殊性质 $\text{A}$：保证树退化成一条链。

特殊性质 $\text{B}$：保证树随机生成（即对于每一个节点随机选择它的父亲节点）。

特殊性质 $\text{C}$：保证 $w\in\{0.1,0.3,0.5,0.7,0.9\}$。

特殊性质 $\text{D}$：保证 $w\in\{0.1,0.2,0.3,0.4,0.6,0.7,0.8,0.9\}$。

特殊性质 $\text{E}$：保证 $w\le2$ 且 $w$ 小数位数不超过 $1$ 位。

对于 $100\%$ 的数据满足 $1\le n,q\le2\times10^5$，$0\le a_i\le10^9$，$0\le w\le10^4$，$1\le u,v,x,y\le n$，$x\ne y$，$w$ 小数位数不超过 $4$ 位。

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
1 2 0.1
2 3 0.20
3 4 0.5
2 5 0.99
1 5
1 4
4 3```

### 输出

```
No
No
Yes```

# 题解

## 作者：迟暮天复明 (赞：24)

显然，每次询问的乘积可以表示成 $\dfrac{p}{q}$ 的形式。由于每一条边的边权都不超过 $4$ 位小数，所以一定可以表示成 $\dfrac{k}{10^x}$ 的形式，其中 $x$ 是小数位数。所以，如果我们想要乘积是一个整数，就必须要分子把和分母中所有的 $10$ 都约分了。

我们发现 $10=2\times5$，所以只需要分子中因数 $2$ 的个数与因数 $5$ 的个数分别大于或等于分母中因数 $2$ 和因数 $5$ 的个数即可。

我们知道每一个边权和点权都可以表示成 $2^p\times 5^q \times k$ 的形式。根据上文所说，$k$ 对解题无关紧要。所以我们可以对于每一条边和每一个点，计算出各自的 $p$ 与 $q$ 的值。那这样，我们就把问题转化为：对于每一次询问，是否对于所有要乘起来的数存在 $\sum p\ge 0$ 且 $\sum q\ge 0$。

上面的式子，我们可以分成两部分计算。一是边权的乘积，二是起始点点权。两者可以分开计算。对于起始点的点权，显然能够计算了。因此我们只需要考虑如何计算树上一条链的答案即可。

怎么计算一条链上的 $\sum p$ 和 $\sum q$ 呢？我们可以记 $f_i$ 为从树的根节点到节点 $i$ 的 $\sum p$，记 $g_i$ 为从树的根节点到节点 $i$ 的 $\sum q$。这样，就得到 $\sum p=f_u+f_v-2f_{\operatorname{lca}(u,v)},\sum q=g_u+g_v-2g_{\operatorname{lca}(u,v)}$。为了得到 $f$ 数组和 $g$ 数组的值，我们可以在计算完每一条边各自的 $p$ 和 $q$ 之后对这棵树进行一次深度优先遍历。

那么这道题就做完了。注意判断点权为 $0$ 以及边权为 $0$ 的情况。我们只要在处理的时候将 $0$ 看做 $2^{\mathrm{inf}}\times 5^{\mathrm{inf}}$ 即可。

---

## 作者：Stars_visitor_tyw (赞：23)

## P8972 『GROI-R1』 一切都已过去 题解
### 分析
从数据范围很容易发现，如果我们把边权累乘再判整数，炸掉是必然的，这时候，我们来发现一个性质：只有小数部分有 $2$ 和 $5$ 相乘的时候，才可能变成整数。当然，这并不是绝对的，例如 $2.02 \times 5$ 就不是整数。从上面举的例子很容易发现一个性质：两个实数的乘积是否为整数与小数点数位也有关系。一对 $2$ 和 $5$ 可以抵消掉一个小数点数位（$2$ 和 $5$ 可以在任意且不同数位上，并且 $2$ 和 $5$ 的倍数也有用）。这时，我们可以将边权通过不断 $\times 10$ 变成整数，并分解质因数分别求因数中 $2$ 和 $5$ 的个数（点权也要处理）。$2$ 和 $5$ 的个数求出来了，小数点数位也很好处理。最终的小数点位数应该是所有路径上的边权小数点位数之和，所以我们在将边权化整数时再维护一个变量统计小数点位数并记录到邻接矩阵里。若路径 $x$ 到 $y$ 的总边权乘上 $x$ 的点权得到的结果中 $2$ 的个数和 $5$ 的个数大于或等于总小数点位数，则其为整数。分别维护即可。

注意：若边权或点权为 $0$ 则对应维护的当前点权或点权的 $2$ 和 $5$ 赋予极大值。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
const int inf=1e16;
struct node
{
    int y, w, dlp;//dlp表示小数点位数，Decimal Places
};
int n, m, s, dep[N], dp[N][21], dis[N], cnt2[N], cnt5[N], a[N];
vector<node> nbr[N];
int count_two(int x)
{
    if(x==0)
    {
        return inf;
    }
    int cnt=0;
    while(x!=0&&x%2==0)
    {
        cnt++;
        x/=2;
    }
    return cnt;
}
int count_five(int x)
{
    if(x==0)
    {
        return inf;
    }
    int cnt=0;
    while(x!=0&&x%5==0)
    {
        cnt++;
        x/=5;
    }
    return cnt;
}
void pre_lca(int cur, int fa)
{
	dp[cur][0]=fa;
	dep[cur]=dep[fa]+1;
	for(int i=1;(1<<i)<=dep[cur];i++)
	{
		dp[cur][i]=dp[dp[cur][i-1]][i-1];
	}
	for(auto i:nbr[cur])
	{
	    int nxt=i.y;
		if(nxt!=fa)
		{
			dis[nxt]=dis[cur]+i.dlp,cnt2[nxt]=cnt2[cur]+count_two(i.w),cnt5[nxt]=cnt5[cur]+count_five(i.w);
			pre_lca(nxt,cur);
		}
	}
}
int lca(int x, int y)
{
	if(dep[x]>dep[y])
	{
		swap(x,y);
	}
	for(int i=20;i>=0;i--)
	{
		if(dep[x]<=dep[dp[y][i]])
		{
			y=dp[y][i];
		}
	}
	if(x==y)
	{
		return x;
	}
	for(int i=20;i>=0;i--)
	{
		if(dp[x][i]!=dp[y][i])
		{
			x=dp[x][i];
			y=dp[y][i];
		}
	}
	return dp[x][0];
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
	    cin>>a[i];
	}
	for(int i=1;i<n;i++)
    {
        int x, y;
        double v;
        cin>>x>>y>>v;
        int dlp=0;
        while(v!=floor(v))
        {
            v*=10.0;
            dlp++;
        }
        nbr[x].push_back((node){y,floor(v),dlp});
        nbr[y].push_back((node){x,floor(v),dlp});
    }
    pre_lca(1,0);
    for(;m;m--)
    {
        int x, y;
        cin>>x>>y;
        int tmp=lca(x,y);
        if(min(cnt2[x]+cnt2[y]-2*cnt2[tmp]+count_two(a[x]),cnt5[x]+cnt5[y]-2*cnt5[tmp]+count_five(a[x]))>=dis[x]+dis[y]-2*dis[tmp])
        {
            cout<<"Yes\n";
        }
        else
        {
            cout<<"No\n";
        }
    }
}
```

---

## 作者：masonpop (赞：11)

个人认为做法比较好想。但是蒟蒻赛时没有考虑 特殊情况，结果直接保龄。赛后改了改过了。感谢出题人 lsj 大佬的提示。~~数据真tm毒瘤。~~
* 言归正传。回想一下我们~~小学二年级~~计算小数乘法的方法，就是先不考虑小数点，将所有数乘在一起最后移位。对于这题，我们先将浮点数通过平移小数点的方法转成整数。对于每条边用变量 $cnt$ 表示这条边边权原本的小数点数量。那么，求 $(x,y)$ 之间路径上小数点数量就可以通过 $\text{LCA}$ 简单统计。
* 那么，我们只需要统计这一车整数乘积末尾 $0$ 的个数，与小数点位数比较即可。如何统计呢?只需要看边权 $2$ 的幂次总和和 $5$ 的幂次总和的较小者即可。维护两点间路径中 $2$ 和 $5$ 的幂次总和，又可以直接用 $\text{LCA}$ 统计没错吧。
* 但是，事情还远远没有结束。如果怀着这么 naive 的想法做这么一道毒瘤题目的话，就会像我这样。
![](https://cdn.luogu.com.cn/upload/image_hosting/bh67twci.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)
* 为什么会这样呢。说说几个主要的坑点吧。

$(1)$ 统计幂次函数出错。
* 可以看到，前面提交的时候 $\color{darkblue}\text{T}$ 了几发，原因是没有在数达到 $0$ 的时候 ```return``` 结果死循环了。~~我不是在卡评测姬别举报我~~

$(2)$ 没有特判权值为 $0$ 的情况
* 快乐的修改，提交，结果黑色变成了红色。这又是怎么回事呢？开始不停的魔改代码结果到结束也没有改出来。其实，如果仔细看题的话就会发现，边权和点权是会取到 $0$ 的，此时我们的代码会出锅。我们可以再开一个数组记录路径上边权为 $0$ 的个数，如果 $>0$ 就直接输出 ```Yes.``` 再特判起点权值就行了。当然定义 $0$ 中 $2$ 和 $5$ 的幂次是无穷大也是可以的。
* 代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=400010;
const int inf=10000000;
const int maxm=500010;
int n,m,x,y,tot=0;
int a[maxn],head[maxn],to[maxm],nxt[maxm];
int dep[maxn],fa[maxn][25],lg[maxn],cnt[maxn],ver[maxn];
int zero[maxn];
double z;
inline int calc2(int x)//2的幂次
{
	int cal=0;
	while(x && x%2==0)cal++,x/=2;
	return cal;	
} 
inline int calc5(int x)//5的幂次
{
	int cal=0;
	while(x && x%5==0)cal++,x/=5;
	return cal;	
} 
int sum[maxn],two[maxn],five[maxn];//sum:总小数点位数，two,five:末尾0的个数 
inline void add(int x,int y,int z,int p)//p:小数点位数 
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;//模板 
	ver[tot]=z;
	cnt[tot]=p;
}
inline void dfs(int x,int f)
{
	dep[x]=dep[f]+1;
	fa[x][0]=f;
	for(int i=1;(1<<i)<=dep[x];i++)
	{
		fa[x][i]=fa[fa[x][i-1]][i-1];
	}
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==f)continue;
		sum[y]=sum[x]+cnt[i];
		two[y]=two[x]+calc2(ver[i]);
		five[y]=five[x]+calc5(ver[i]);
		zero[y]=zero[x]+(ver[i]==0);
		dfs(y,x);
	}
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y])x=fa[x][lg[dep[x]-dep[y]]-1];
	if(x==y)return x;
	for(int i=lg[dep[x]];i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
signed main()
{
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	memset(zero,1,sizeof(zero));
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<n;i++)
    {
    	scanf("%lld%lld%lf",&x,&y,&z);
    	int p=0;
    	while(z!=floor(z))z*=10,p++;//小数点位数 
    	add(x,y,(int)z,p);
		add(y,x,(int)z,p);
	}
	dfs(1,0);
	for(int i=1;i<=n;++i)
	{
		lg[i]=lg[i-1]+(1<<lg[i-1]==i);//预处理log 
	} 
	while(m--)
	{
		scanf("%lld%lld",&x,&y);
		int flo=sum[x]+sum[y]-2*sum[LCA(x,y)];
		int twos=two[x]+two[y]-2*two[LCA(x,y)]+calc2(a[x]);
		int fives=five[x]+five[y]-2*five[LCA(x,y)]+calc5(a[x]);
		int ten=min(twos,fives);
		if(ten>=flo || a[x]==0 || (zero[x]+zero[y]-2*zero[LCA(x,y)])>0)printf("Yes\n");
		else printf("No\n");
	}
    return 0;
}
```


---

## 作者：User_leo (赞：8)

## 0.前言：
在找 LCA 的题时，偶然发现了这道 GROI-R1 的题。

愉快地调了 $13$ day ......

发篇题解作纪念。
## 1.题意
给定一棵 $n$ 个节点的树和 $q$ 次询问。每次询问给出两个整数 $x,y$，表示询问树上以 $x$ 和 $y$ 为端点的简单路径上边权乘积与点 $x$ 的点权相乘是否为整数。
## 2.思路
一开始我认为只要把边权转化成整数后，再把它们与起点点权乘起来，判断它是不是整数（后四位为零）即可。

但是数据范围给了我致命一击。
#### $0\le a_i\le10^9$，$0\le w\le10^4$
long long 会爆，高精会 T。

看来这种思路并不可取。

我们需要换一种思路来切这道题。

众所周知，可以通过数字里因数 $2$ 和因数 $5$ 的数量来判断这个数字有几个后缀零。

那么浮点数呢？
#### 同理
我们照样可以统计因数 $2$ 和因数 $5$ 的数量来判断这个数字有几位小数。

而两个浮点数相乘所产生的小数位数为这两个浮点数的小数位数的和。

可以先在输入时将点权和边权先转整数，再把里面因数 $2$ 和因数 $5$ 的数量存下来（注：存储时要 $-4$ ，因为题目中 $w$ 小数位数不超过 $4$ 位，转整数时要 $\times10000$，需要统计原数字小数位数，而边权中因数 $2$ 和因数 $5$ 的数量可以和小数位数抵消，为负数代表此数无法贡献因数 $2$ 和因数 $5$ 的同时，还会产生小数位数），然后在建树时建立从根节点到目前节点因数 $2$ 和因数 $5$ 的数量之和，接着在询问时求起点和终点的 LCA，算出路径上边权相乘会产生几位小数位数，最后将结果加上点权所贡献的因数 $2$ 和因数 $5$，判断因数 $2$ 和因数 $5$ 的数量是否 $\ge0$ （若成立，代表结果没有小数位数（为整数），若不成立，代表结果存在小数位数（为小数）），输出即可。
## 3.特判
数据中可能会出现 $0$，如果直接分解会导致死循环。
注意要将其因数 $2$ 和因数 $5$ 的数量设为极大值。
## 4.献上我丑陋的代码(感谢 @Cfz大佬的帮助)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,inf=0x3f3f3f3f,L=20;
int cnt,h[N];//邻接表
int ct[N],cf[N],num[N][2];//统计因数2和因数5的数量 
int f[N][L],dep[N],lg[N];//LCA
int n,q;
struct node{
    int to,nxt,cnt2,cnt5;
}e[N<<1];
void add_edge(int x,int y,int w){
    e[++cnt]={y,h[x],-4,-4};//注意要初始化成-4（转整数时乘了10000，这里是原有的小数位数）
    h[x]=cnt;
    if(w==0){//别忘记特判
        e[cnt].cnt2=e[cnt].cnt5=inf;
    }else{
        while(w%2){
            e[cnt].cnt2++;
            w/=2;
        }
        while(w%5){
            e[cnt].cnt5++;
            w/=5;
        }
    }
    return ;
}
void dfs(int x){
    for(int i=h[x];i;i=e[i].nxt){
        int go=e[i].to;
        if(!dep[go]){
            ct[go]=ct[x]+e[i].cnt2;
            cf[go]=cf[x]+e[i].cnt5;
            dep[go]=dep[x]+1;
            dfs(go);
        }
    }
}
int LCA(int x,int y){
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    while(dep[x]>dep[y]){
        x=f[x][lg[dep[x]-dep[y]]];
    }
    if(x==y){
        return x;
    }
    for(int i=L-1;i>=0;i--){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
signed main(){
    cin>>n>>q;
    lg[0]=-1;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(x==0){//只要出现分解因数就要特判 
            num[i][0]=num[i][1]=inf;
        }else{
            while(x%2){
                num[i][0]++;
                x/=2;
            }
            while(x%5){
                num[i][1]++;
                x/=5;
            }
        }
        lg[i]=lg[i>>1]+1;
    }
    for(int i=1;i<n;i++){
        int a,b;
        double w;
        cin>>a>>b>>w;
        add_edge(a,b,w*10000);//*10000转整数（题目中w小数位数不超过4位。） 
        add_edge(b,a,w*10000);
    }
    dep[1]=1;
    dfs(1);
    for(int i=1;i<=L;i++){
        for(int j=1;j<=n;j++){
            f[j][i]=f[f[j][i-1]][i-1];
        }
    }
    while(q--){
        int x,y,z,ans,a,b;
        cin>>x>>y;
        z=LCA(x,y);
        a=num[x][0]+ct[x]+ct[y]-ct[z]*2;//路径上因数2的个数 
        b=num[x][1]+cf[x]+cf[y]-cf[z]*2;//路径上因数5的个数
        if(a>=0&&b>=0){//如果乘起来是整数 
            cout<<"Yes\n";
        }else{
            cout<<"No\n";
        }
    }
    return 0;
}
```
~~您觉得直接抄能过吗~~

---

## 作者：TernaryTree (赞：7)

套路类似的题：[AT_agc047_a](https://www.luogu.com.cn/problem/AT_agc047_a)。

浮点数容易出现误差，不好处理。发现小数点后位数不超过 $4$ 位，于是将边权乘 $10^4$。

发现这样边权乘积过大，仍不好处理。不妨将边权分为 $2$ 因子次数与 $5$ 因子次数。对于点权也同样处理。然后跑树上差分，比较大小即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 2e5 + 1;
const int mul = 1e4;
const int eps = 1e-5;
const int maxd = 20;
const int inf = 1e9;

typedef pair<int, int> pii;

struct edge {
    int to, next;
    pii w;
};

int n, q;
pii a[maxn];
int head[maxn];
edge e[maxn << 1];
int cnt;

void add_edge(int u, int v, int c2, int c5) {
    e[++cnt].to = v;
    e[cnt].w = make_pair(c2, c5);
    e[cnt].next = head[u];
    head[u] = cnt;
}

int fa[maxn][maxd];
int dep[maxn];

void get_dep(int u, int depth, int fat) {
    dep[u] = depth;
    for (int i = head[u]; i; i = e[i].next) {
        if (e[i].to != fat) {
        	get_dep(e[i].to, depth + 1, u);
		}
    }
} 

void get_fa(int cur, int fat) {
    fa[cur][0] = fat;
    for (int i = 1; i <= log2(dep[cur]) + 1; i++) {
        fa[cur][i] = fa[fa[cur][i - 1]][i - 1];
    }
    for (int i = head[cur]; i; i = e[i].next) {
        if (e[i].to != fat) {
        	get_fa(e[i].to, cur);
		}
    }
}

pii val[maxn];

void dfs(int u, int fat, int c2, int c5) {
    val[u] = make_pair(c2, c5);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        pii w = e[i].w;
        if (v == fat) continue;
        dfs(v, u, c2 + w.first, c5 + w.second);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    while (dep[u] > dep[v]) {
        u = fa[u][(int) log2(dep[u] - dep[v])];
    }
    if (u == v) return u;
    for (int i = log2(dep[u]); i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> q;
    int u, v;
    double w;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        int c2 = 0, c5 = 0;
        if (!x) c2 = c5 = inf;
        else {
            while (x % 2 == 0) x /= 2, ++c2;
            while (x % 5 == 0) x /= 5, ++c5;
        }
        a[i] = make_pair(c2, c5);
    }
    for (int i = 1; i <= n - 1; i++) {
        cin >> u >> v >> w;
        int nw = w * mul + eps;
        int c2 = 0, c5 = 0;
        if (!nw) c2 = c5 = inf;
        else {
            while (nw % 2 == 0) nw /= 2, ++c2;
            while (nw % 5 == 0) nw /= 5, ++c5;
        }
        add_edge(u, v, c2, c5);
        add_edge(v, u, c2, c5);
    }
    get_dep(1, 0, 0);
    get_fa(1, 0);
    dfs(1, 0, 0, 0);
    while (q--) {
        int x, y, z;
        cin >> x >> y;
        z = lca(x, y);
        int dis = dep[x] + dep[y] - 2 * dep[z];
        int c2 = val[x].first + val[y].first - 2 * val[z].first + a[x].first;
        int c5 = val[x].second + val[y].second - 2 * val[z].second + a[x].second;
        cout << (c2 >= dis * 4 && c5 >= dis * 4 ? "Yes" : "No") << endl;
    }
    return 0;
}
```

---

## 作者：wwwwwza (赞：5)

## [题目传送门](https://www.luogu.com.cn/problem/P8972)

既然都没人用树链剖分写题解，那我就写一篇。  
这道题细节有亿点点多……

## 步骤
### 一、输入
1. 在输入边权值的时候，由于其最多是四位小数，所以将其乘上 $10^4$。
2. 因为边权值无法单独方便的存储，所以将其存在儿子节点上。

### 二、树链剖分
1. 与模板相同，这里不过多赘述。
2. [模板题](https://www.luogu.com.cn/problem/P3384)。

### 三、线段树
1. 线段树存储四个值：小数数位长度、因数 $2$ 的个数、因数 $5$ 的个数、$0$ 的个数。
2. 由于开头边权值乘了 $10^4$，所以默认概数的小数数位为 $4$。两小数相乘后其数的小数数位长度为原两数小数数位长度相加。
3. 因数个数也是同理，相加即可。
4. $0$ 的个数在后面有妙用。

### 四、最近公共祖先
1. 树链剖分模板。
2. 由于边权值是存储在该边的儿子节点上，所以会发现加多了一个 $lca$，减去即可。
3. 别忘了乘初始点的点权。
4. 由于 $2 \times 5=10$，可以使小数数位长度减一，看有几个 $2 \times 5$ 即可。
5. 任何一个数乘 $0$，都得 $0$，为整数，满足条件。

### 五、输出
1. 按判断结果输出答案。


## 代码
```cpp
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
const int N=2e5+10;
int n,q,w[N],val[N],x,y;
double z;
int dfn[N],size[N],dep[N],son[N],fat[N],top[N],cnt=0;
struct node{
	int v,w;
};
vector<node>g[N];
struct T{
	int num,two,five,zero;
}tree[N<<2];
T operator + (const T a,const T b){//辅助线段树
	T c;
	c.num=a.num+b.num;
	c.two=a.two+b.two;
	c.five=a.five+b.five;
	c.zero=a.zero+b.zero;
	return c;
}
T operator - (const T a,const T b){
	T c;
	c.num=a.num-b.num;
	c.two=a.two-b.two;
	c.five=a.five-b.five;
	c.zero=a.zero-b.zero;
	return c;
}
void dfs1(int u,int fa){
	size[u]=1;
	fat[u]=fa;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].v;
		if(v==fa)continue;
		val[v]=g[u][i].w;
		dep[v]=dep[u]+1;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int topx){
	dfn[u]=++cnt;
	top[u]=topx;
	if(son[u]){
		dfs2(son[u],topx);
	}
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].v;
		if(v==fat[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int cal2(int x){//求一个数中有几个因数2 
	int sum=0;
	while(x%2==0&&x>=1){
		sum++;
		x/=2;
	}
	return sum;
}
int cal5(int x){//求一个数中有几个因数5 
	int sum=0;
	while(x%5==0&&x>=1){
		sum++;
		x/=5;
	}
	return sum;
}
void update(int rt,int l,int r,int x,int d){//修改 
	if(l==r){
		tree[rt]={4,cal2(d),cal5(d),(d==0)?1:0};
		return;
	}
	int mid=l+r>>1;
	if(mid>=x)update(rt*2,l,mid,x,d);
	else update(rt*2+1,mid+1,r,x,d);
	tree[rt]=tree[rt*2]+tree[rt*2+1];
}
T query(int rt,int l,int r,int x,int y){//查找 
	if(x<=l&&r<=y){
		return tree[rt];
	}
	int mid=l+r>>1;
	T sum={0,0,0,0};
	if(mid>=x)sum=sum+query(rt*2,l,mid,x,y);
	if(mid<y)sum=sum+query(rt*2+1,mid+1,r,x,y);
	return sum; 
}
void pre_find(int x,int y){//回答 
	T ans={0,cal2(w[x]),cal5(w[x]),(w[x]==0)?1:0};
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=ans+query(1,1,n,dfn[top[x]],dfn[x]);
		x=fat[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans=ans+query(1,1,n,dfn[x],dfn[y]);
	ans=ans-query(1,1,n,dfn[x],dfn[x]);
	if(min(ans.two,ans.five)>=ans.num||ans.zero>=1){
		printf("Yes\n");
	}else{
		printf("No\n");
	}
}
int main(){
	scanf("%d%d",&n,&q);//输入 
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
	}
	for(int i=1;i<n;i++){
		scanf("%d%d%lf",&x,&y,&z);
		z*=10000;//变成整数 
		int k=z;
		g[x].push_back({y,k});
		g[y].push_back({x,k});
	}
	val[1]=10000;//边权值 
	dfs1(1,0);dfs2(1,1);//树链剖分 
	for(int i=1;i<=n;i++){
		update(1,1,n,dfn[i],val[i]);//线段树 
	}
	while(q--){
		scanf("%d%d",&x,&y);
		pre_find(x,y);
	}
	return 0;
}

```

---

## 作者：Fislett (赞：4)

# 题意

给你一颗 $n$ 个结点的树，每个结点有一个点权，每条边有一条边权。给你 $q$ 次询问，每次询问给定两个整数 $x,y$，询问 $x$ 到 $y$ 路径上的所有边权之积与 $x$ 的点权之积是否为整数。

# 解法

边权的小数点位数不超过 $4$ 位，我们先把所有的边权乘上 $10^4$ 把他变为整数。那现在的问题就变成了要看乘积末尾的零是否大于等于我们乘进去的零。这个问题经过我们的小学数学转化一下就可以变成乘积分解质因数之后 $2$ 的个数和 $5$ 的个数是否大于乘进去的零的个数。

切记，数据中会出现很多有 $0$ 的情况，这时，把 $2$ 的因数的个数和 $5$ 的因数的个数赋为极大值即可。

不开 ```long long``` 见祖宗。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct edge
{
	int to, cnt2, cnt5, next;
} e[500005];
int n, q, five[200005], two[200005], toto, head[200005], d[200005], fa[200005][19], a[200005];
pair<int, int> val[200005];
pair<int, int> f(int x)
{
	int r = -4, p = -4;
	while (x % 2 == 0)
	{
		r ++;
		x /= 2;
	}
	while (x % 5 == 0)
	{
		p ++;
		x /= 5;
	}
	return make_pair(r, p);
}
void add(int x, int y, int u, int v)
{
	e[++ toto].to = y;
	e[toto].cnt2 = u;
	e[toto].cnt5 = v;
	e[toto].next = head[x];
	head[x] = toto;
}
bool vis[200005];
void dfs(int root, int def)
{
	vis[root] = true;
	d[root] = def;
	for (int i = head[root]; i; i = e[i].next)
	{
		if (vis[e[i].to]) continue;
		fa[e[i].to][0] = root;
		val[e[i].to].first = val[root].first + e[i].cnt2;
		val[e[i].to].second = val[root].second + e[i].cnt5;
		dfs(e[i].to, def + 1);
	}
}
int lca(int x, int y)
{
	if (d[x] > d[y]) swap(x, y);
	for (int i = 18; i >= 0; i --) if (d[fa[y][i]] >= d[x]) y = fa[y][i];
	if (x == y) return x;
	for (int i = 18; i >= 0; i --)
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	return fa[x][0];
}
signed main()
{
	ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i ++)
	{
		cin >> a[i];
		if (!a[i]) five[i] = two[i] = 2e9;
		else
		{
			pair<int, int> p = f(a[i]);
			five[i] = p.second + 4, two[i] = p.first + 4;
		}
	}
	for (int i = 1; i < n; i ++)
	{
		int x, y;
		double z;
		cin >> x >> y >> z;
		if (z != 0)
		{
			pair<int, int> p = f(z * 10000);
			add(x, y, p.first, p.second);
			add(y, x, p.first, p.second);
		}
		else
		{
			add(x, y, 2e9, 2e9);
			add(y, x, 2e9, 2e9);
		}
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i ++)
		for (int j = 1; (1 << (j - 1)) <= d[i]; j ++)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	while (q --)
	{
		int x, y;
		cin >> x >> y;
		int z = lca(x, y);
		int cnt2 = val[x].first + val[y].first - val[z].first * 2 + two[x];
		int cnt5 = val[y].second + val[x].second - val[z].second * 2 + five[x];
		if (cnt2 >= 0 && cnt5 >= 0) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```


---

## 作者：xuchuhan (赞：4)

## Description

给你 $n,q$，表示有一棵 $n$ 个结点的树以及 $q$ 次询问。再给你一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，其中 $a_i$ 为树上结点 $i$ 的点权。每次询问给定 $x,y$，询问结点 $x$ 至结点 $y$ 的路径上所有边的边权之积乘上 $a_x$ 是否为整数。

## Solution

因为边权均为小数，且点权均为整数，所以最后的乘积 $S$ 一定可以表示为 $\dfrac{x}{10^k}=\dfrac{x}{2^k\times5^k}$。想要乘积为整数，那么 $x$ 所包含的质因数 $2,5$ 的个数都要大于等于 $k$。所以我们可以统计路径上乘积质因数 $2,5$ 的数量，再判断这些 $2,5$ 是否大于等于 $k$。$k$ 自然就是总的小数点位数。

当然，若直接搜索找出路径时间复杂度太高，我们可以使用 LCA 优化，设 $dis2_i$ 表示从根节点到 $i$ 的路径总乘积所包含质因数 $2$ 的个数，则求结点 $x$ 至结点 $y$ 的路径总乘积所包含质因数 $2$ 的个数有如下代码：

```
int num2=dis2[x]+dis2[y]-2*dis2[LCA(x,y)];
```

其中 `LCA(x,y)` 表示结点 $x$ 和结点 $y$ 的最近公共祖先。

还需要注意几点细节：

- 浮点数不好计算，所以我们可以把它化为整数再计算。因为题目保证了 $w$ 小数位数不超过 $4$ 位，所以我们可以将所有权值先乘上 $10^4$，计算质因数 $2,5$ 的个数时再减去 $4$。最后判断时判断质因数 $2,5$ 的个数是否大于等于 $0$ 即可。

- 别忘了最后 $2,5$ 的总个数需要加上 $a_x$ 所包含的质因数 $2,5$ 的个数。

- 若边权为 $0$，则乘积永远是整数，将 $2,5$ 的个数设为无穷大。

## Code

代码实现难度还是不小的，细节也超级多。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,q;
int a[N],dep[N],dis2[N],dis5[N];
int dp[N][30];
struct node{
	int y,z;
};
vector<node>v[N];
int Cal(int x,int num){//计算x包含因数num的个数
	int cnt=0;
	while(x&&x%num==0){
		x/=num;
		cnt++;
	}
	return cnt;
}
void DFS(int x,int fa){//LCA预处理
	dep[x]=dep[fa]+1;
	dp[x][0]=fa;
	for(int i=1;(1<<i)<=dep[x];i++)
		dp[x][i]=dp[dp[x][i-1]][i-1];
	for(int i=0;i<v[x].size();i++){
		int to=v[x][i].y,w=v[x][i].z;
		if(to==fa)
			continue;
		if(w==0)
			dis2[to]=dis2[x]+1e9,dis5[to]=dis5[x]+1e9;//边权为0
		else
			dis2[to]=dis2[x]+Cal(w,2)-4,dis5[to]=dis5[x]+Cal(w,5)-4;//减4
		DFS(to,x);
	}
	return;
}
int LCA(int x,int y){//求x和y的LCA
	if(dep[x]>dep[y])
		swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[x]<=dep[dp[y][i]])
			y=dp[y][i];
	if(x==y)
		return x;
	for(int i=20;i>=0;i--)
		if(dp[x][i]!=dp[y][i])
			x=dp[x][i],y=dp[y][i];
	return dp[x][0];
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    //加读入优化,不加可能会TLE
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++){
		int x,y;
		double z;
		cin>>x>>y>>z;
		z*=10000;//先乘上10^4
		v[x].push_back({y,(long long)z});
		v[y].push_back({x,(long long)z});
	}
	DFS(1,0);
	while(q--){
		int x,y;
		cin>>x>>y;
		int num2=dis2[x]+dis2[y]-2*dis2[LCA(x,y)]+Cal(a[x],2);//x->y路径上的因子2个数，别忘了加上a[x]因子2的个数
		int num5=dis5[x]+dis5[y]-2*dis5[LCA(x,y)]+Cal(a[x],5);//同理
		if((num2>=0&&num5>=0)||!a[x])//若a[x]的值为0积同样为整数
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：MichaelWong (赞：3)

和其他几位 dalao 的做法有一点点小不同，写一下。

# [原题链接](https://www.luogu.com.cn/problem/P8972)


------------


形式化题面给的很清楚，

给定 $n$ 个节点的树和 $q$ 次询问，每次给出 $x,y$，表示询问树上以 $x$ 和 $y$ 为端点的简单路径上边权乘积与点 $x$ 的点权相乘是否为整数。

- 所以，我们肯定是需要 LCA 的，最熟悉的做法就是使用倍增思想。

需要解决的问题：如何计算边权积。

- 我们考虑同样使用倍增思想，使用 $wt(u,i)$ 表示节点 $u$ 到第 $2^i$ 个祖先的路径的边权积。

需要解决的问题：即使是 `long double` 精度也是不够的。

- 考虑到如果 $i$ 位小数和 $j$ 位小数相乘，结果位数 $i+j$ 小，则证明他们相乘结尾出现了 $0$，只有可能是 $2 \times 5$。

所以，我们使用 $cnt2$ 和 $cnt5$ 记录去掉小数点后的数字的因数中有几个 $2$ 和几个 $5$，再用 $cntd$ 记录考虑结尾 $0$ 时理论上有几位小数。如果 $\min (cnt2,cnt5) \geq cntd$ 则结果为整数。 

- 因为规定边权小数位数不超过 $4$ 位，所以我们可以在最初 $w \times 10000,cntd \gets 4$，然后计算 $cnt2$ 和 $cnt5$ 即可。

## AC CODE

```cpp
#include<bits/stdc++.h>
const int N=2e5+5;
int fa[N][25],dep[N];
int n,q,a[N];
struct number{//结构体记录边权，因为位数只与2,5有关，其他的就不记录了
	int cnt2,cnt5,cntd;
	bool is_zero;//任何数乘0都得0，所以只要出现0就是整数，特判
	number operator * (number x){//重载number型变量乘法
		if(is_zero || x.is_zero)	return {0,0,0,1};
		number ans {cnt2,cnt5,cntd,is_zero};
		ans.cnt2+=x.cnt2;
		ans.cnt5+=x.cnt5;
		ans.cntd+=x.cntd;
		return ans;
	}
	number operator * (int x){//重载number型与int型乘法
		if(is_zero || x==0)	return {0,0,0,1};
		number ans {cnt2,cnt5,cntd,is_zero};
		while(x && (x%2)==0)	{ans.cnt2++;	x/=2;}
		while(x && (x%5)==0)	{ans.cnt5++;	x/=5;}
		return ans;
	}
}wt[N][25];
const number num1 {0,0,0,0};
struct edge {int to; number w;};//结构体存边
std::vector <edge> E[N];
number make_number(double x){//将int型变量转换为number型
	if(x==0)	return {0,0,0,1};
	number ans {0,0,0,0};
	x*=10000;	ans.cntd+=4;
	int xx=x;
	while(xx&&(xx%2)==0)	{ans.cnt2++;	xx/=2;}
	while(xx&&(xx%5)==0)	{ans.cnt5++;	xx/=5;}
	return ans;
}
bool is_int(number x){//判断是否整数
	if(x.is_zero || std::min(x.cnt2,x.cnt5)>=x.cntd)	return 1;
	return 0;
}
void init(int u){//dfs与倍增初始化
	for(int i=1;i<=21;++i)	{fa[u][i]=fa[fa[u][i-1]][i-1];	wt[u][i]=wt[u][i-1]*wt[fa[u][i-1]][i-1];}//初始化倍增
	for(auto v:E[u])	if(v.to!=fa[u][0])	{fa[v.to][0]=u;	wt[v.to][0]=v.w;	dep[v.to]=dep[u]+1;	init(v.to);}//继续dfs
}
number LCA(int u,int v){//寻找LCA并计算边权和
	number ans=num1;
	if(dep[u]<dep[v])	std::swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=21;i>=0;--i)	if(d&(1<<i))	ans=ans*wt[u][i],u=fa[u][i],d-=1<<i;
	if(u==v)	return ans;
	for(int i=21;i>=0;--i)	if(fa[u][i]!=fa[v][i])	ans=ans*wt[u][i]*wt[v][i],u=fa[u][i],v=fa[v][i];
	ans=ans*wt[u][0]*wt[v][0];
	return ans;
}
int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);std::cout.tie(0);
	std::cin>>n>>q;
	for(int i=1;i<=n;++i)
		std::cin>>a[i];
	for(int i=1;i<n;++i){
		int u,v;	double w;
		std::cin>>u>>v>>w;
		E[u].push_back({v,make_number(w)});	E[v].push_back({u,make_number(w)});
	}
	dep[1]=1,init(1);
	for(int i=1;i<=q;++i){
		int x,y;
		std::cin>>x>>y;
		if(is_int(LCA(x,y)*a[x]))	std::puts("Yes");
		else std::puts("No");
	}
	return 0;
}
```

本题解毕。

---

## 作者：Rain_rhythm (赞：2)

### Solution

对于所有路径的贡献，必然可以表示成 $\dfrac{x}{10^k}$ 的形式。

那么考虑从因子 $2$ 和 $5$ 入手。维护 $f_i,dp_{0,i},dp_{1,i}$ 分别表示从根开始到节点 $i$ 路径上的小数点后数位个数之和（即所有的 $k$ 之和）、包含因子 $2$ 的个数之和、包含因子 $5$ 的个数之和。

对于一条 $u$ 到 $v$ 的路径，设节点 $p$ 为 $u$ 和 $v$ 的 LCA，$a_u$ 的因子 $2$ 的个数之和为 $t_0$，因子 $5$ 的个数之和为 $t_1$。那么:

- 小数点后数位个数之和为 $f_u+f_v-2 f_p$

- 因子 $2$ 的个数之和为 $dp_{0,u}+dp_{0,v}-2 dp_{0,p}+t_0$

- 因子 $5$ 的个数之和为 $dp_{1,u}+dp_{1,v}-2 dp_{1,p}+t_1$

预处理出 LCA，在询问时判断路径上因子 $2$ 的个数之和以及因子 $5$ 的个数之和是否都大于等于路径上的小数点后数位个数之和即可。

### Code


```cpp
/* ChongYun */
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,q,a[200005];
struct node{
	int to,nxt,val,cnt;
}w[400005];
int hd[400005],ecnt=0;
void Link(int x,int y,int val,int cnt){
	++ecnt;
	w[ecnt].to=y;
	w[ecnt].nxt=hd[x];
    w[ecnt].val=val;
    w[ecnt].cnt=cnt;
	hd[x]=ecnt;
	return ;
} 
int getcnt(int p,int x){
    if(!x) return 1e12;
    int qans=0;
    while(x%p==0) x/=p,++qans;
    return qans;
}
int f[200005],dp2[200005],dp5[200005];
int dp[200005][25],dep[200005];
void initdfs(int x,int fa){
	dep[x]=dep[fa]+1; dp[x][0]=fa;
	for(int i=1;(1<<i)<=dep[x];i++) dp[x][i]=dp[dp[x][i-1]][i-1];
	for(int i=hd[x];i!=0;i=w[i].nxt){
		int y=w[i].to;
		if(y==fa) continue;
        f[y]=f[x]+w[i].cnt;
        dp2[y]=dp2[x]+getcnt(2,w[i].val);
        dp5[y]=dp5[x]+getcnt(5,w[i].val);
		initdfs(y,x);
	}
	return ;
} 
int LCA(int x,int y){
	if(dep[y]<dep[x]) swap(x,y);
	for(int i=20;i>=0;i--){
		if(dep[dp[y][i]]>=dep[x]) y=dp[y][i];
	}
	if(x==y) return x;
	for(int i=20;i>=0;i--){
		if(dp[x][i]!=dp[y][i]){
			x=dp[x][i];
			y=dp[y][i];
		}
	}
	return dp[x][0];
}
signed main(){
	n=read(); q=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++){
        int u,v,qcnt=0;
        double val;
        u=read(); v=read();
        scanf("%lf",&val);
        while(val!=floor(val)) val*=10,qcnt++;
        Link(u,v,val,qcnt);
        Link(v,u,val,qcnt);
    }
    initdfs(1,0);
    while(q--){
        int u=read(),v=read();
        int fa=LCA(u,v),d=f[u]+f[v]-2*f[fa];
        int qwq=dp2[u]+dp2[v]-2*dp2[fa]+getcnt(2,a[u]);
        int qaq=dp5[u]+dp5[v]-2*dp5[fa]+getcnt(5,a[u]);
        printf(min(qwq,qaq)>=d?"Yes\n":"No\n");
    }
	return 0; 
} 
```

---

## 作者：Weekoder (赞：1)

### 思路

首先想到 LCA，但观察到数据范围，发现直接乘会爆炸。

如何优化？我们知道，只有小数部分有 $2$ 和 $5$ 相乘，才可能变成整数，一对 $2$ 和 $5$ 可以抵消掉 $1$ 个小数点位。设 $dis_i$ 为从根结点到点 $i$ 的路径上的总的小数点数位，$dis2_i$ 为从根结点到点 $i$ 的路径上的质因数 $2$ 的个数，$dis5_i$ 同理，则一条路径上的 $cnt1,cnt2,cnt5$ 分别用 LCA 求解即可。若 $\min(cnt2,cnt5)\ge cnt1$，则路径乘积为整数。分别维护 $dis,dis2,dis5$。

如果出现了 $0$，则路径乘积一定为整数，$2$ 和 $5$ 的个数设为极大值。

代码如下：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 5;

struct Edge {
	int to, w, cnt;
};

int n, Q, a[N], deep[N], dp[N][30], dis[N], dis2[N], dis5[N];

vector<Edge> nbr[N];

int cnt2(int x) {
	if (!x)
		return 1e18;
	int sum = 0;
	while (x && x % 2 == 0)
		sum++, x >>= 1;
	return sum;
}

int cnt5(int x) {
	if (!x)
		return 1e18;
	int sum = 0;
	while (x && x % 5 == 0)
		sum++, x /= 5;
	return sum;
}

void pre_lca(int cur, int fa) {
	deep[cur] = deep[fa] + 1;
	dp[cur][0] = fa;
	for (int j = 1; (1 << j) <= deep[cur]; j++)
		dp[cur][j] = dp[dp[cur][j - 1]][j - 1];
	for (auto nxt : nbr[cur])
		if (nxt.to != fa)
			dis[nxt.to] = dis[cur] + nxt.cnt, dis2[nxt.to] = dis2[cur] + cnt2(nxt.w), dis5[nxt.to] = dis5[cur] + cnt5(nxt.w), pre_lca(nxt.to, cur);
}

int lca(int x, int y) {
	if (deep[x] > deep[y])
		swap(x, y);
	for (int i = 20; i >= 0; i--)
		if (deep[dp[y][i]] >= deep[x])
			y = dp[y][i];
	if (x == y)
		return x;
	for (int i = 20; i >= 0; i--)
		if (dp[x][i] != dp[y][i])
			x = dp[x][i], y = dp[y][i];
	return dp[x][0];
}

double dist(int x, int y) {
	return dis[x] * dis[y] / dis[lca(x, y)] / dis[lca(x, y)];
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> Q;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1, u, v; i < n; i++) {
		double w;
		cin >> u >> v >> w;
		int p = 0;
		while (w != floor(w))
			w *= 10, p++;
		nbr[u].emplace_back((Edge){v, (int)w, p});
		nbr[v].emplace_back((Edge){u, (int)w, p});
	}
	pre_lca(1, 0);	
	while (Q --) {
		int x, y;
		cin >> x >> y;
		int LCA = lca(x, y);
		int cnt = min(dis2[x] + dis2[y] - 2 * dis2[LCA] + cnt2(a[x]), dis5[x] + dis5[y] - 2 * dis5[LCA] + cnt5(a[x])), tmp = dis[x] + dis[y] - 2 * dis[LCA];
		cout << (cnt >= tmp ? "Yes\n" : "No\n");
	}
	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

首先小数精度很恶心，考虑维护成分数。

注意到分母一定是 $10^x$，考虑维护 $2,5$ 在数里面出现了多少次。

显然这是乘积，分子里面的其他内容不需要维护。

即使使用除法，最后也肯定对答案没有贡献。

剩下的求 LCA 然后树上前缀积即可。

但是有一个问题，显然 $2,0,3,4$ 这样前缀积是 $2,0,0,0$，这时候求 $[3,4]$ 的前缀积不能用 $0\div 0$ 来求。

注意到有个性质：任何数乘 $0$ 都是 $0$。

考虑把 $0$ 当做 $10^{+\inf}$ 处理即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define Number sdhfiasuhdfishfis
using namespace std;
constexpr int N=2e5+1;
int n,q,son[N],fa[N],siz[N],top[N],dep[N];
struct Number{
    int cnt2,cnt5;
    Number(){}
    Number(string s){
        if(s=="0"){
            cnt2=cnt5=10000000;
        }
        else{
            int cnt=0,fl=0,val=0;
            for(auto p:s){
                cnt+=fl;
                if(p=='.')
                    fl=1;
                if(p!='.')
                    val=val*10+(p-48);
            }
            cnt2=cnt5=-cnt;
            while(val%2==0)
                cnt2++,val/=2;
            while(val%5==0)
                cnt5++,val/=5;
        }
    }
    friend Number operator*(Number a,Number b){
        a.cnt2+=b.cnt2,a.cnt5+=b.cnt5;
        return a;
    }
    friend Number operator/(Number a,Number b){
        a.cnt2-=b.cnt2,a.cnt5-=b.cnt5;
        return a;
    }
}a[N],val[N];
string s;
vector<pair<int,Number> >e[N];
int dfs_siz(int u,int fath){
    int maxs=-1;
    siz[u]=1,fa[u]=fath,dep[u]=dep[fath]+1;
    for(auto[v,w]:e[u]){
        if(v==fa[u])
            continue;
        val[v]=val[u]*w;
        siz[u]+=dfs_siz(v,u);
        if(maxs<siz[v])
            maxs=siz[v],son[u]=v;
    }
    return siz[u];
}
void dfs_chain(int u,int tp){
    top[u]=tp;
    if(son[u])
        dfs_chain(son[u],tp);
    for(auto[v,w]:e[u]){
        if(v==fa[u]||v==son[u])
            continue;
        dfs_chain(v,v);
    }
    return;
}
int get_lca(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])
            swap(u,v);
        u=fa[top[u]];
    }
    return dep[u]<dep[v]?u:v;
}
void debug(Number x){
    cout<<x.cnt2<<' '<<x.cnt5<<'\n';
    return;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>s;
        a[i]=Number(s);
    }
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v>>s;
        e[u].push_back({v,Number(s)}),
        e[v].push_back({u,Number(s)});
    }
    val[1]=Number("1");
    dfs_siz(1,0),dfs_chain(1,1);
    for(int u,v,lca;q;--q){
        cin>>u>>v;
        lca=get_lca(u,v);
        Number ans=(val[u]/val[lca])*(val[v]/val[lca])*a[u];
        if(ans.cnt2>=0&&ans.cnt5>=0)
            cout<<"Yes\n";
        else
            cout<<"No\n";
//        debug(val[u]),debug(val[v]),debug(val[lca]);
    }
    return 0;
}
```

---

## 作者：lcfollower (赞：0)

咕咕咕还能写题解。

首先考虑暴力解法，先计算出每次询问 $u$，$v$ 的深度以及父亲节点（以下默认 $u$ 的深度大于等于 $v$ 的深度），还有从根到节点的路径的边权积 $dis_i$。

先求最近公共祖先 $l$，则 $u$，$v$ 之间的简单路径之积乘上 $u$ 的点权为 $\frac{dis_u\times dis_v}{dis_{l}^2}\times val_u\to mul$，其中 $val_i$ 表示节点 $i$ 的点权，然后判断 $\lfloor mul \rfloor$ 是否等于 $mul$ 即可。由于 $1\le n\le 10^5$，所以考虑**倍增**优化。如果还不会倍增求最近公共祖先，请[出门左转](https://www.luogu.com.cn/problem/P3379)。

但是由于精度问题或小数点位数过多，很有可能导致答案错误。

思考一下，$10 = 2\times 5$，所以小数部分只有 $2\times 5$ 的乘法可以消除小数点的一位。

因此考虑计算每个边权（点权）含有的 $2$ 和 $5$ 的数量，现将其化为整数，然后计算数量即可。注意还要计算这个数乘以多少个 $10$ 才变为整数。

然后通过公式计算出 $u$，$v$ 之间的简单路径乘以 $u$ 的点权的三个元素：含有因子 $2$ 的数量、含有因子 $5$ 的数量、小数点总共的位数。

那么一共能消除的小数点位数为 $\min\{num2 , num5\}$。如果这个数大于等于小数点总共位数，则为整数；反之，则不为整数。

- 注意事项：有可能边权（点权）为 $0$。

- 解决方案：特判或者将 $0$ 含有 $2$，$5$ 的因子个数设为 $+\infty$ 来保证因子 $2$，$5$ 个数的最小值大于等于小数点后的位数。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define inf 1e13
//注意这个 inf 不要定义太大，为了防止树是一条链，所以需要再类型范围内的 1/(100000 - 1)。
#define infi 1e18

const int N = 2e5 + 10 ,M = N;
int n ,Q ,val[N] ,in[N];
int fa[N][21] ,dep[N] ,lg[N] ,two[N] ,five[N] ,digit[N];
vector <tuple <int ,int ,int> > edge[M << 1];

inline int get(int x ,int k){
  if(!x) return inf;
  int tot = 0;
  while(x && (x % k == 0)) ++ tot , x /= k;
  return tot;
} inline void dfs(int u ,int fath){//预处理 fa 数组、含有因子 2,5 的个数以及乘积小数点的位数。
  fa[u][0] = fath ,dep[u] =  dep[fath] + 1;
  for(int i = 1; i <= lg[dep[u]];i ++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
  for(auto [v ,w ,dig] : edge[u])
    if(v != fath){
      two[v] = two[u] + get(w ,2) ,five[v] = five[u] + get(w ,5) ,digit[v] = digit[u] + dig;//两个小数相乘最多的位数是相加，而非相乘。比如 1.2 * 1.2 = 1.44。
      dfs(v ,u);
    }
} inline int LCA(int u ,int v){//求 LCA。
  if(dep[u] < dep[v]) swap(u ,v);
  while(dep[u] > dep[v]) u = fa[u][lg[dep[u] - dep[v]]];
  if(u == v) return u;
  for(int i = 20;i >= 0;i --)
    if(fa[u][i] != fa[v][i]) u = fa[u][i] ,v = fa[v][i];
  return fa[u][0];
} signed main(){
  scanf("%lld %lld" ,&n , &Q);
  int root = 1;
  for(int i = 1;i <= n;i ++) scanf("%lld" ,val + i);
  lg[0] = -1;
  for(int i = 1;i <= n;i ++) lg[i] = lg[i >> 1ll] + 1;//预处理 log2(x)。
  for(int i = 1;i < n;i ++){
    int u , v ,tot = 0;
    double w;
    scanf("%lld %lld %lf",&u ,&v ,&w);
    while((int)w != w){++ tot ,w *= 10.0;}//tot 为小数点后的位数。
    edge[u].emplace_back(v ,w ,tot);
    edge[v].emplace_back(u ,w ,tot);
    in[u] ++ ,in[v] ++;
  }
  for(int i = 1;i <= n;i ++) if(in[i] == 1){root = i;break;}//求根。
  dfs(root ,0);
  while(Q --){
    int u , v;
    scanf("%lld %lld" ,&u ,&v);
    int lca = LCA(u ,v);
    int num2 = two[u] + two[v] - 2 * two[lca] + get(val[u] ,2) ,num5 = five[u] + five[v] - 2 * five[lca] + get(val[u] ,5) ,dig = digit[u] + digit[v] - 2 * digit[lca];
    if(min(num2 ,num5) >= dig) puts("Yes");
    else puts("No");
  }
  return 0;
}
```

---

## 作者：2huk (赞：0)

- 给定一颗 $n$ 个节点的树，边权为**实数**，点权为**整数**。$q$ 给定两个整数 $x, y$，表示询问树上以 $x$ 和 $y$ 为端点的简单路径上边权乘积与点 $x$ 的点权相乘是否为整数。
- $n, q \le 2 \times 10^5$，$a_i \le 10^9$，$w \le 10^4$，$w$ 小数位数不超过 $4$ 位。

若干个数的乘积为整数，可以类似小学乘法。如果这些数的小数位数的和共 $a$ 位，且将它们的小数点忽略后，乘积末尾有 $b$ 个 $0$，那么原数乘积是否为整数等价于是否 $a \le b$。

其中求末尾 $0$ 的个数等价于质因数分解后 $2, 5$ 中出现次数的较小值。所以我们需要求的是：

- $x \sim y$ 路径上所有边权小数位数和；
- $x \sim y$ 路径上所有边权质因数分解后 $2,5$ 的出现次数；
- $x$ 质因数分解后 $2, 5$ 的出现次数。

3rd 极易。如果令 $f_{0, i}$ 表示根到 $i$ 节点边权的小数位数的和，$f_{2,i}$ 表示根到 $i$ 节点边权的质因数分解后 $2$ 的出现次数，$f_{5,i}$ 表示根到 $i$ 节点边权的质因数分解后 $5$ 的出现次数。那么 1th 和 2nd 的答案为是 $f_{0/2/5, x} + f_{0/2/5, y} - 2f_{0/2/5, \operatorname{lca(x, y)}}$。

注意我们将 $0$ 看作其中包含 $\infty$ 个 $2, 5$。

```cpp
int n, q, a[N];
int h[N], e[M], ne[M], idx;
double w[M];

void add(int a, int b, double c) {
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++ ;
}

int f[6][N];
int dep[N];
int fa[N][20];

int calc(double w, int op = 0) {
	int res = 0;
	while (w != (int)w) {
		++ res;
		w *= 10;
	}
	if (!op) return res;
	res = 0; int v = w;
	if (!v) return 1e12;
	while (v % op == 0) {
		++ res;
		v /= op;
	}
	return res;
}

void dfs(int u, int F) {
	dep[u] = dep[F] + 1;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == F) continue;
		fa[v][0] = u;
		for (int j = 1; j < 20; ++ j )
			fa[v][j] = fa[fa[v][j - 1]][j - 1];
		f[0][v] = f[0][u] + calc(w[i]);
		f[2][v] = f[2][u] + calc(w[i], 2);
		f[5][v] = f[5][u] + calc(w[i], 5);
		dfs(v, u);
	}
	return;
}

int lca(int a, int b) {
	if (dep[a] < dep[b]) swap(a, b);
	for (int i = 19; ~i; -- i )
		if (dep[fa[a][i]] >= dep[b])
			a = fa[a][i];
	if (a == b) return a;
	for (int i = 19; ~i; -- i )
		if (fa[a][i] != fa[b][i])
			a = fa[a][i], b = fa[b][i];
	return fa[a][0];
}

void Luogu_UID_748509() {
	memset(h, -1, sizeof h);
	fin >> n >> q;
	for (int i = 1; i <= n; ++ i ) fin >> a[i];
	for (int i = 1; i < n; ++ i ) {
		int x, y; double z;
		scanf("%lld%lld%lf", &x, &y, &z);
		add(x, y, z), add(y, x, z);
	} 
	dfs(1, 0);
	while (q -- ) {
		int x, y; fin >> x >> y;
		int p = lca(x, y);
		int ten = min(f[2][x] + f[2][y] - 2 * f[2][p] + calc(a[x], 2), f[5][x] + f[5][y] - 2 * f[5][p] + calc(a[x], 5));
		int dot = f[0][x] + f[0][y] - 2 * f[0][p];
		puts(ten >= dot ? "Yes" : "No");
	}
}
```

---

