# Flow Control

## 题目描述

You have to handle a very complex water distribution system. The system consists of $ n $ junctions and $ m $ pipes, $ i $ -th pipe connects junctions $ x_i $ and $ y_i $ .

The only thing you can do is adjusting the pipes. You have to choose $ m $ integer numbers $ f_1 $ , $ f_2 $ , ..., $ f_m $ and use them as pipe settings. $ i $ -th pipe will distribute $ f_i $ units of water per second from junction $ x_i $ to junction $ y_i $ (if $ f_i $ is negative, then the pipe will distribute $ |f_i| $ units of water per second from junction $ y_i $ to junction $ x_i $ ). It is allowed to set $ f_i $ to any integer from $ -2 \cdot 10^9 $ to $ 2 \cdot 10^9 $ .

In order for the system to work properly, there are some constraints: for every $ i \in [1, n] $ , $ i $ -th junction has a number $ s_i $ associated with it meaning that the difference between incoming and outcoming flow for $ i $ -th junction must be exactly $ s_i $ (if $ s_i $ is not negative, then $ i $ -th junction must receive $ s_i $ units of water per second; if it is negative, then $ i $ -th junction must transfer $ |s_i| $ units of water per second to other junctions).

Can you choose the integers $ f_1 $ , $ f_2 $ , ..., $ f_m $ in such a way that all requirements on incoming and outcoming flows are satisfied?

## 样例 #1

### 输入

```
4
3 -10 6 1
5
1 2
3 2
2 4
3 4
3 1
```

### 输出

```
Possible
4
-6
8
-7
7
```

## 样例 #2

### 输入

```
4
3 -10 6 4
5
1 2
3 2
2 4
3 4
3 1
```

### 输出

```
Impossible
```

# 题解

## 作者：Porsche (赞：5)

看到还没有人发题解，不如我来一篇？

其实做这道题纯粹是因为这是一道双倍经验题，这道题与JZOJ 5916. 【NOIP2018 模拟 10.20】flow 体面意思是一样的，大家可以把它看成一个中文翻译，下面奉上这道题的中文翻译（~~代码形式插入~~）

```
5916. 【NOIP2018 模拟 10.20】flow  (File IO): input:flow.in output:flow.out 
Time Limits: 1000 ms  Memory Limits: 262144 KB  Detailed Limits    Special Judge 
Description 
       你是申国的一个地方长官，你手下有 n 个城市。        为了加强基础设施建设，在 2020 全面建成小康社会，统筹推进经济建设、政治建设、文化建设、 社会建设、生态文明建设，坚定实施科教兴国战略、人才强国战略、创新驱动发展战略、乡村振兴战 略、区域协调发展战略、可持续发展战略、军民融合发展战略，突出抓重点、补短板、强弱项，特别是 要坚决打好防范化解重大风险、精准脱贫、污染防治的攻坚战，使全面建成小康社会得到人民认可、经 得起历史检验。你认为本省的水利调配非常有问题，这导致部分地区出现严重的缺水，而部分地区却全 年洪灾泛滥。        于是你打算将原有的但是已经废弃了的 m 条水管重新使用。第 i 条水管连接城市 xi 和 yi。这些水管 联通了所有城市。每座城市对水的需求不同设为 ai，部分城市处于缺水状态，ai 为正，缺水量刚好为 ai mol。部分城市因为有水库，ai 为负，它需要向外输送-ai mol 的水才能不形成洪灾。对于每条水管，你需 要决定它的输送量 fi，若 fi 为正则表示从 xi 向 yi 输送 fi mol 的水，fi 为负则表示从 yi 向 xi 输送-fi mol 的 水。        你需要做到每个城市都刚好满足它的需求，即缺 ai mol 水的城市需要刚好输入 ai 的水，而多出-ai mol 水的城市需要刚好输出-ai mol 水。        你需要判断能否满足要求，若满足，你还需要输出所有的 f。 
Input 
第一行一个整数 n。 第二行 n 个整数 ai。 第三行一个整数 m。 接下来 m 行每行两个整数，xi,yi。 意义如题中所述。 
Output 
如果不能满足要求，输出”Impossible”。 否则第一行输出”Possible”，接下来 m 行，第 i+1 行输出 fi。 若有多组解，随意输出一组即可。 
Sample Input 
4 
3 -10 6 1 
5 
1 2 
3 2 
2 4 
3 4 
3 1 
Sample Output 
Possible 
4 
-6 
8 
-7 
7 
Data Constraint 
对于 10%：n<=5，|ai|<=20 对于 20%：n<=10，|ai|<=20 对于另 30%：n<=1000，m=n，|ai|<=20 对于 100%：n<=200000，m<=300000，你使用 longint(pascal)/int(c++)就能够存储 ai。 数据纯随机。 
Hint 
Tips 
mol 是一种单位。 
```
下面是思路：

首先，我们需要判断是否合法，这很简单，只需要记录一下a数组里面的数的总和为0及合法，不为0则不合法，直接输出"Impossible"之后return 0即可。

之后讨论合法情况：

现在考虑如何构造出一种合法解。
一种很简单的方法就是先构造一棵生成树，
强制只用树上面的边，这样就可以轻松求出一组合法解。

还是看不懂的小朋友们还是直接看下面的代码吧

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a[200001],fa[200001],p[200001],ans[200001];
int cnt;
struct rec
{
    int nxt;
    int lst;
    int to;
    int id;
}e[400001];//个人习惯用数组存邻接表
int getfa(int x)
{
    return fa[x]=fa[x]==x?x:getfa(fa[x]);//并查集
}
void add(int x,int y,int flag)//建立邻接表
{
    e[++cnt].nxt=e[x].lst;
    e[cnt].to=y;
    e[cnt].id=flag;
    e[x].lst=cnt;
}
void dfs(int x,int f)//DFS搜索
{
    p[x]=a[x];
    for(int i=e[x].lst;i;i=e[i].nxt)
        if(e[i].to!=f)
        {
            dfs(e[i].to,x);
            p[x]+=p[e[i].to];
            if(i%2)ans[e[i].id]=p[e[i].to];
            else ans[e[i].id]=-p[e[i].to];
        }
}
int main()
{
    int n,m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        fa[i]=i;
        cnt+=a[i];//cnt此时用来记录a数组是否合法
    }
    if(cnt)//判断是否合法
    {
        cout<<"Impossible"<<endl;
        return 0;
    }
    cout<<"Possible"<<endl;
    cnt=0;
    scanf("%d",&m);
    for(int i=1;i<=m;i++)//如上面解释所说
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(getfa(x)!=getfa(y))
        {
            add(x,y,i);
            add(y,x,i);
            fa[getfa(x)]=getfa(y);
        }
    }
    dfs(1,0);
    for(int i=1;i<=m;i++)//输出
        cout<<ans[i]<<endl;
    return 0;
}
```
~~恶搞环节：~~

好学生自动忽略即可

~~教大家一种新的定义方式，可以让抄你题解的人一脸懵逼。~~

~~以下划线长度不同定义不同的变量~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int _[200001],__[200001],___[200001],____[200001];
int _____;
struct ________________
{
    int _______;
    int ________;
    int _________;
    int __________;
}______[400001];
int _________________(int ___________)
{
    return __[___________]=__[___________]==___________?___________:_________________(__[___________]);
}
void __________________(int ___________,int ____________,int _______________)
{
    ______[++_____]._______=______[___________].________;
    ______[_____]._________=____________;
    ______[_____].__________=_______________;
    ______[___________].________=_____;
}
void ___________________(int ___________,int _______________)
{
    ___[___________]=_[___________];
    for(int _____________=______[___________].________;_____________;_____________=______[_____________]._______)
        if(______[_____________]._________!=_______________)
        {
            ___________________(______[_____________]._________,___________);
            ___[___________]+=___[______[_____________]._________];
            if(_____________%2)____[______[_____________].__________]=___[______[_____________]._________];
            else ____[______[_____________].__________]=-___[______[_____________]._________];
        }
}
int main()
{
    int ______________,_______________;
    scanf("%d",&______________);
    for(int _____________=1;_____________<=______________;_____________++)
    {
        scanf("%d",&_[_____________]);
        __[_____________]=_____________;
        _____+=_[_____________];
    }
    if(_____)
    {
        cout<<"Impossible"<<endl;
        return 0;
    }
    cout<<"Possible"<<endl;
    _____=0;
    scanf("%d",&_______________);
    for(int _____________=1;_____________<=_______________;_____________++)
    {
        int ___________,____________;
        scanf("%d%d",&___________,&____________);
        if(_________________(___________)!=_________________(____________))
        {
            __________________(___________,____________,_____________);
            __________________(____________,___________,_____________);
            __[_________________(___________)]=_________________(____________);
        }
    }
    ___________________(1,0);
    for(int _____________=1;_____________<=_______________;_____________++)
        cout<<____[_____________]<<endl;
    return 0;
}
```
~~不要以为上面的是代码补全，上面的科室AC代码哦~~~

---

## 作者：OIer_ACMer (赞：2)

# 题目解析：

本题作者认为是一道构造题，读完题，光从题面上跟着题目的思路走我们发现陷入了死胡同，这时，我们需要正难则反。

首先，我们将需求变成要求，如果一个点的流量为 $x$，则从他的父节点调配 $x$ 的流量给他，同时，加大父亲节点的需求，毕竟要养活一个子节点，之后，以此类推。

你问我为什么在一个图上会有父亲节点与儿子节点，我的回答是：你可以把图变成一棵树来计算。

# 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
    int to, next, id;
} edge[1000009];
int cnt, head[1000009];
void add(int u, int v, int id)
{
    edge[++cnt].to = v;
    edge[cnt].id = id;
    edge[cnt].next = head[u];
    head[u] = cnt;
}
int s[1000009]; 
int f[1000009];
bool vis[1000009];
void dfs(int x, int fa, int id)
{
    vis[x] = 1;
    for (int i = head[x]; i; i = edge[i].next)
    {
        int y = edge[i].to, id = edge[i].id;
        if (!vis[y])
        {
            dfs(y, x, id);
        }
    }
    // cout << "x=" << x << endl;
    if (s[x] != 0)
    {
        if (id < 0)
        {
            f[-id] -= s[x];
        }
        else
        {
            f[id] += s[x];
        }
        s[fa] += s[x];
        s[x] = 0;
    }
}
int n;
int main()
{
    int tot = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        tot += s[i];
    }
    if (tot != 0)
    {
        cout << "Impossible";
        return 0;
    }
    cout << "Possible\n";
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        add(u, v, i);
        add(v, u, -i);
    }
    dfs(1, 0, 0);
    for (int i = 1; i <= m; i++)
    {
        cout << f[i] << '\n';
    }
    return 0;
}
```

---

## 作者：yuzhechuan (赞：2)

### 题意：

给你一个n个点m条边的无向图，你可以任意设置每条边的流量，现在要求每个点都得到$s_i$的流量，问方案?

---

### 题解：

首先注意到流量总量是守恒的，即有一定量的进就又有等量的出，所以对于合法的情况$\sum s=0$，否则就是不合法的

其次还要发现一条性质：即对于合法的情况，只要图是联通的就一定有可行的方案

自己口胡一下应该很容易想明白

根据这一条性质，我们完全将给出的图当成一棵树来做，从上到下遍历，从下往上更新，每次操作由于转移都是1对1的，所以可以直接贪心做，将一条边的流量设置为下层点所需要的流量，同时用上层点“支付”这一部分流量。至于流量的“方向”只要特判一下边是否是给出的那条就行了

---

### 题解：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return  x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}
template<class t> inline void writeln(t x){write(x);puts("");}

const int N=2e5+5,M=N;
int en=1,h[N],n,m,ans[M],a[N],sum;
bool v[N];

struct edge{
	int n,v;
}e[M<<1];

void add(int x,int y){
	e[++en]=(edge){h[x],y};
	h[x]=en;
}

void dfs(int x){
	v[x]=1; //标记该点已访问过
	for(int i=h[x];i;i=e[i].n){
		int y=e[i].v;
		if(v[y]) continue; //访问过就不要再去了
		dfs(y);
		ans[i>>1]=(i&1?-1:1)*a[y]; //偶数编号边是题目给出的，用正的，否则是反向边用负数
		a[x]+=a[y]; //用上层点支付流量
	}
} 

signed main(){
	read(n);
	for(int i=1;i<=n;i++) sum+=read(a[i]);
	if(sum){ //先判掉无解的情况
		puts("Impossible");
		return 0;
	}
	read(m);
	for(int i=1,x,y;i<=m;i++){
		read(x);read(y);
		add(x,y);add(y,x);
	}
	dfs(1);
	puts("Possible");
	for(int i=1;i<=m;i++) writeln(ans[i]);
}
```

---

## 作者：ifffer_2137 (赞：1)

### 题意
给一个图，每个点给定总流经量，给每条边定向定流量，或报告无解。
### 分析
~~*2400 大概是历史遗留问题。~~

你发现每条边的总贡献为 $0$，所以总流经量之和如果不为 $0$ 则无解。

然后你发现任意提取出一棵生成树就可以直接递推构造了，从叶子一点一点往上填每一条边都是确定的，剩下的非树边不流即可。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
#define mkpr make_pair
#define x first
#define y second
#define popcnt __builtin_popcountll
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w?x:-x;
}
template<class T1,class T2>inline bool Cmn(T1 &x,T2 y){return y<x?x=y,1:0;}
template<class T1,class T2>inline bool Cmx(T1 &x,T2 y){return y>x?x=y,1:0;}
template<class T>inline void Dbg(T *a,int l,int r){for(int i=l;i<=r;i++)cout<<a[i]<<' ';cout<<'\n';}
mt19937 rnd(time(NULL));
constexpr int inf=0x3f3f3f3f;
constexpr int maxn=2e5+5;
constexpr int maxm=5e3+5;
constexpr int mod=998244353;
constexpr int base=2137;
constexpr int V=1e9;
constexpr int H=18;
constexpr int W=64;
constexpr int Z=26;
constexpr double eps=1e-9;
inline int Redu(int x){return x-(x>=mod)*mod;}
inline void Add(int &x,int y){x=x+y-(x+y>=mod)*mod;}
inline void _Add(int &x,ll y){x=(x+y)%mod;}
inline void Del(int &x,int y){x=x-y+(x-y<0)*mod;}
inline void _Del(int &x,ll y){x=(x-y)%mod;x+=(x<0)*mod;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int Pow(int a,int x){int s=1;for(;x;x>>=1,a=1ll*a*a%mod)if(x&1)s=1ll*s*a%mod;return s;}
bool Mem1;
int n,m,s;
int a[maxn];
vector<pii> G[maxn];
int vis[maxn];
int ans[maxn];
void dfs(int u){
	vis[u]=1;
	for(pii e:G[u]){
		int v=e.x,id=e.y;
		if(vis[v]) continue;
		dfs(v);
		if(id>0) ans[id]=a[v],a[u]+=a[v];
		else ans[-id]=-a[v],a[u]+=a[v];
	}
}
void Init(){}
void Clear(){}
void Mymain(){
	Clear();
	n=read();
	for(int i=1;i<=n;i++) s+=(a[i]=read());
	m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		G[u].push_back(mkpr(v,i)),G[v].push_back(mkpr(u,-i));
	}
	if(s) return cout<<"Impossible\n",void(); 
	dfs(1);
	cout<<"Possible\n";
	for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
}
bool Mem2;
signed main(){
	#ifdef LOCAL
	assert(freopen("data.in","r",stdin));
	assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	Init();int _=1;
	while(_--) Mymain();
	cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms\n";
	cerr<<"Memory: "<<(&Mem1-&Mem2)/1024.0/1024.0<<" MB\n";
	return 0;
}
```

---

## 作者：肖翔 (赞：1)

首先，这是一个无向图。

相当于给出若干联通块，每个点有点权，表示出边与入边边权和之差。

也可以视作流量。

这个流量可以任意传递，所以只要每个联通块里的点权和为 $0$，那么它就合法。

然后考虑构造一个合法方案。

对于每个联通块，在保证联通的前提下，去掉一些无用的边。

发现最后会变成一棵树。

我们只需要从叶子开始，把它的流量传给父亲。

一次 dfs 就做完了。

（有点像拓扑排序。）

（其实最后根节点处的流量就是块内点权和，做完 dfs 再判断一下即可。）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int fa[maxn];
int s[maxn];
int x[maxn],y[maxn];
inline int rd(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
inline int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
	x=find(x),y=find(y);
	if(x!=y)fa[x]=y;
	return;
}
struct edge{
	int y,nxt;
}e[maxn<<1];
int h[maxn],tot;
inline  void add(int x,int y){
	e[++tot].y=y;
	e[tot].nxt=h[x];
	h[x]=tot;
}
int sum[maxn];
bool vis[maxn];
map<pair<int,int>,int> ans;
inline void dfs(int x){
	vis[x]=1;sum[x]=s[x];
	for(int i=h[x];i;i=e[i].nxt){
		int y=e[i].y;
		if(vis[y])continue;
		dfs(y);
		ans[{y,x}]=sum[y];
		sum[x]+=sum[y];
	}
	return;
}
int main(){
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)s[i]=-rd();	
	for(int i=1;i<=n;i++)fa[i]=i;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		x[i]=rd();y[i]=rd();
		merge(x[i],y[i]);
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		if(find(x[i])!=find(y[i])){
			add(x[i],y[i]);
			add(y[i],x[i]);
			merge(x[i],y[i]);
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			dfs(i);
			if(sum[i]){
				puts("Impossible");
				return 0;
			}
		}
	}
	puts("Possible");
	for(int i=1;i<=m;i++){
		if(ans[{x[i],y[i]}]){
			printf("%d\n",ans[{x[i],y[i]}]);
		}
		else if(ans[{y[i],x[i]}]){
			printf("%d\n",-ans[{y[i],x[i]}]);
		}
		else puts("0");
	}
}
```


---

## 作者：UncleSam_Died (赞：1)

### 解题思路

一个很显然的结论：

- 当且仅当所有点的流量之和为 $0$ 时，存在解。

在得出这个结论后，我们可以先计算出 $\displaystyle \sum_{i=1}^n s_i$ 的值，然后判断一下是否为 $0$，如果不为 $0$，那么直接输出 `Impossible` 即可。

接下来讨论为 $0$ 的情况。根据上面的结论我们可以知道，如果图联通，那么一定满足这个结论，反之亦然。由此可得，我们可以删除若干条边，只要剩下的边可以构成一个联通图就可以了。这里考虑最简单的情况，即只保留 $n-1$ 条边，剩下的边构成一棵无根树，我们默认 $1$ 号节点为它的根节点。从根开始搜索，直到找到叶子节点，然后我们根据叶子节点的约束条件，计算它的父节点还需要流入或流出的水量，然后一层层往上更新即可，每次更新的时候同时处理出当前节点和它的父亲节点连边的流量。因为一条边的水量的正负由边的方向决定，所以我们还需要记录每一条边，可以用 map 来存储两个点之间的边的编号，按照输入中给的方向的边，编号为正，否则编号为负，这样在更新的时候就可以根据边的编号的正负来判断水流的方向，从而确定 $f_i$ 的正负。

时间复杂度 $O(n\log n)$。

### AC 代码

```cpp
#include<iostream>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include <map>
#define ll long long

inline void FileOpen(const char *infile,const char *outfile){
    char *fileread=new char[1];
    char *filewrite=new char[1];
    fileread[0]=114,filewrite[0]=119;
    freopen(infile,fileread,stdin);
    freopen(outfile,filewrite,stdout);
}
inline void FileClose(){
    char *fileread=new char[1];
    char *filewrite=new char[1];
    char *CONwrite=new char[3];
    fileread[0]=114,filewrite[0]=119;
    CONwrite[0]=67,CONwrite[1]=79,CONwrite[2]=78;
    fclose(stdin);
    fclose(stdout);
    std::cin.clear();
    std::cout.clear();
    freopen(CONwrite,fileread,stdin);
    freopen(CONwrite,filewrite,stdout);
}
#define N 200005
#define pii std::pair<int,int>
int n,m,s[N],f[N];
int fl[N],vis[N];
std::vector<int> edge[N];
std::map<pii,int> pos;
inline void dfs(int u,int fa){
    fl[u]=s[u];vis[u]=1;
    for(auto v:edge[u]){
        if(v==fa) continue;
        if(vis[v]) continue; 
        dfs(v,u);fl[u]+=fl[v];
    }if(fl[u]==0) return;
    int np=pos[{u,fa}];
    if(np<0)
        f[-np]=fl[u];
    else f[np]=-fl[u];
}
inline void work(){
    scanf("%d",&n);int sum=0;
    for(register int i=1;i<=n;++i)
        scanf("%d",&s[i]),sum+=s[i];
    if(sum!=0){puts("Impossible");return;}
    scanf("%d",&m);int u,v;
    for(register int i=1;i<=m;++i){
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
        pos[{u,v}]=i;
        pos[{v,u}]=-i;
    }dfs(1,0);puts("Possible");
    for(register int i=1;i<=m;++i)
        printf("%d\n",f[i]);
}signed main(){
    srand(114514);
    srand(rand());
    srand(time(0));
    
    work();system("pause");
}
```





---

## 作者：Warriors_Cat (赞：0)

大概是一道比较轻松的思维题？

### $Solution:$

首先这张图有很多连通块，我们只考虑一个连通块。

很显然在传递的过程中，总数肯定是不变的，所以这几个节点的 $f_i$ 和为 $0$。我们先把不符合的给特判掉。

如果 $f_i$ 和为 $0$，那么一定是可以构造的。具体做法就是跑一棵生成树，然后从叶节点一直传递到父节点即可。

于是这道题就没了……

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int N = 400010;
struct edge{
	int v, w, nxt;
}e[N << 1];
struct node{
	int u, v;
}g[N << 1];
int head[N << 1], cnt, n, m, a[N], f[N], ans[N << 1], S;
bool vis[N], Vis[N << 1];
inline void add(int u, int v, int w){
	e[++cnt].v = v;
	e[cnt].w = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
inline void dfs(int u){
	vis[u] = 1; S += a[u];
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].v; if(vis[v]) continue;
		dfs(v);
	}
	return;
}
inline int anc(int x){ return x == f[x] ? x : f[x] = anc(f[x]); }
inline void Dfs(int u){
	vis[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].v, w = e[i].w;
		if(vis[v]) continue;
		Dfs(v);
		if(g[w].u == u) ans[w] = a[v];
		else ans[w] = -a[v];
		a[u] += a[v];
	}
}
signed main(){
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read(), f[i] = i;
	m = read();
	for(int i = 1; i <= m; ++i) g[i].u = read(), g[i].v = read(), add(g[i].u, g[i].v, 0), add(g[i].v, g[i].u, 0);
	for(int i = 1; i <= n; ++i) if(!vis[i]){
		S = 0; dfs(i); if(S != 0) return printf("Impossible") & 0;
	}
	puts("Possible");
	memset(head, cnt = 0, sizeof(head));
	for(int i = 1; i <= m; ++i){
		int u = g[i].u, v = g[i].v;
		if(anc(u) != anc(v)){
			add(u, v, i); add(v, u, i);
			f[f[u]] = f[v];
			Vis[i] = 1;
		}
	}
	for(int i = 1; i <= m; ++i) if(!Vis[i]) ans[i] = 0;
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; ++i) if(!vis[i]) Dfs(i);
	for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	return 0;
}
```


---

