# ナップサック問題

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2019/tasks/kupc2019_b

$ n $ 個の品物があり、$ 1 $ から $ n $ までの番号が付けられています。

各品物には価値と重さが定められていて、$ i $ 番目の品物の価値は $ v_i $、重さは $ w_i $ です。

あなたはこれらの品物から重さの総和が $ W $ を超えないようにいくつか選び、選んだ品物の価値の総和を最大化したいです。

ただし、$ m $ 個の条件があります。

$ j $ 番目の条件は $ (a_j,\ b_j) $ で表され、それぞれ「 $ a_j $ 番目の品物を選ぶならば $ b_j $ 番目の品物を選ばなければならず、$ b_j $ 番目の品物を選ぶならば $ a_j $ 番目の品物を選ばなければならない」 という意味です。

これらの条件を全て満たした上で、$ n $ 個の品物から重さの総和が $ W $ を超えないようにいくつか品物を選んだときの価値の総和の最大値を求めてください。

## 说明/提示

### 制約

- 入力中の値は全て整数である。
- $ 1\ \leq\ n\ \leq\ 100 $
- $ 0\ \leq\ m\ \leq\ \frac\ {n(n-1)}{2} $
- $ 1\ \leq\ W\ \leq\ 10^4 $
- $ 1\ \leq\ w_i\ \leq\ W $
- $ 1\ \leq\ v_i\ \leq\ 10^7 $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ n $
- $ a_i\ \neq\ b_i $
- $ i\ \neq\ j $ ならば、$ (a_i,\ b_i)\ \neq\ (a_j,\ b_j) $ かつ $ (a_i,\ b_i)\ \neq\ (b_j,\ a_j) $

### Sample Explanation 1

$ 1 $ 番目の品物と $ 2 $ 番目の品物を選ぶことで価値の総和を $ 6 $ にすることができ、これが最適です。 条件から、$ 2 $ 番目の品物と $ 3 $ 番目の品物だけを選ぶことはできないことに注意してください。

### Sample Explanation 2

全ての品物を選ぶことができます。

### Sample Explanation 3

一つも品物を選ぶことができません。

## 样例 #1

### 输入

```
3 1 10
3 2
5 4
3 3
1 2```

### 输出

```
6```

## 样例 #2

### 输入

```
4 0 10
1 1
2 2
3 3
4 4```

### 输出

```
10```

## 样例 #3

### 输入

```
3 3 6
2 5
3 8
3 4
1 2
2 3
3 1```

### 输出

```
0```

## 样例 #4

### 输入

```
1 0 10000
10000 10000000```

### 输出

```
10000000```

# 题解

## 作者：Ag2O2_2010_AC_gu (赞：2)

### 思路

这题可以使用 01 背包+并查集。

因为在条件里物品是相互依赖的，所以我们可以把相互依赖的物品合并成一个物品。

例如下面三样相互依赖的物品（左边是价值，右边是价格）：

```
5 4
3 3
1 2
```

合并之后变成一件物品：

```
9 9
```

如何判断哪些物品相互依赖呢？我们可以很容易地想到并查集。

先把输入的 $u$ 和 $v$ 合并，接着把每一个物品合并到对应的祖先节点，注意合并前要 `if(i!=fa[i])` 判断该物品是不是祖先结点，否则祖先结点的物品会被计算两次。

合并完之后就变成 01 背包啦。

接下来是 01 背包的部分：

我们用 `dp[i][j]` 表示前 $i$ 个物品，背包容量为 $j$ 时的最大价值。

每一项物品有两种情况：选和不选。

如果不选该物品，价值为 `dp[i-1][j]`。

如果选这个物品，就要预留 $c_i$ 的背包容量，从 $j-c_i$ 这个背包容量加上本次选的物品的价值 $d_i$，价值为 `dp[i-c[i]]+d[i]`。

由于题目要求物品的最大价值，得出转移方程为 `dp[i][j]=max(dp[i-1][j],dp[i-1][j-c[i]]+d[i])`。

当然，我们也可以使用滚动数组把 $dp$ 数组降成一维数组。我们可以把第一维去掉。但有个细节，一维数组中 $j$ 的扫描顺序应该从大到小（$w$ 到 $c_i$），否则前一次循环保存下来的值将会被修改，从而造成错误。

最后 01 背包的部分是这样的：

```
for(int i=1; i<=n; i++) {
		if(!c[i]&&!d[i]) continue;//这行其实不写也没关系
		for(int j=w; j>=c[i]; j--) dp[j]=max(dp[j],dp[j-c[i]]+d[i]);
}
```

### AC代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+100;
int n,m,w,c[N],d[N],u,v,fa[N],dp[N];
int find1(int x) {//查询祖先结点
	return fa[x]==x?x:fa[x]=find1(fa[x]);//路径压缩
}
void merge1(int x,int y) {//合并
	int gx=find1(x),gy=find1(y);
	if(gx!=gy) fa[gx]=gy;
}
int main() {
	scanf("%d%d%d",&n,&m,&w);
	for(int i=1; i<=n; i++) fa[i]=i;//别忘了初始化fa数组
	for(int i=1; i<=n; i++) scanf("%d%d",&c[i],&d[i]);
	for(int i=1; i<=m; i++) {
		scanf("%d%d",&u,&v);
		merge1(u,v);//合并互相依赖的两个物品
	}
	for(int i=1; i<=n; i++) {
		if(find1(i)!=i) {//注意合并前要判断该物品是不是祖先结点，否则祖先结点的物品会被计算两次
			c[fa[i]]+=c[i],d[fa[i]]+=d[i];
			c[i]=0,d[i]=0;
		}
	}
	for(int i=1; i<=n; i++) {
		if(!c[i]&&!d[i]) continue;//这行其实不写也没关系
		for(int j=w; j>=c[i]; j--) dp[j]=max(dp[j],dp[j-c[i]]+d[i]);
	}
	printf("%d",dp[w]);
	return 0;
}
```

---

## 作者：Enoch006 (赞：2)

### 简要翻译：
有 $n$ 个物品，每个物品都有价值和重量，给你一个承重为 $W$ 的背包。将一些物品放进背包使总价值最大，并输出最大值。

但是，需要满足一些条件。给出小于 $n$ 的正整数 $a$ 和 $b$，若选择将编号为 $a$ 的物品放入背包，则必须把编号为 $b$ 的物品放入背包；若选择将编号为 $b$ 的物品放入背包，则也必须把编号为 $a$ 的物品放入背包。

### 题目分析：

如果要选择编号为 $a$ 的物品，也要选择编号为 $b$ 的物品。也就是说其实我们可以将 $a$ 和 $b$ “合并”起来，变成另一个大的物品。再进行背包 DP。

这时候，我们想到**并查集**合并物品。一步一步建树，最后**合并的物品的价值和重量**就在每棵树的**根**。

### 题目代码：
```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 10005
using namespace std;
int n,m,cnt,W,x,y,fa[maxm],f[maxm];
struct node{
	int w,v;
}a[maxm],b[maxm];
void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
}
int getfa(int u){
	if(fa[u]==u)return u;
	return fa[u]=getfa(fa[u]);
}
signed main(){
    cin>>n>>m>>W;
    init();//并查集初始化。
    for(int i=1;i<=n;i++){
    	cin>>a[i].w>>a[i].v;
	}
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		if(getfa(x)==getfa(y))continue;//如果已经在同一棵树了就跳过。
		else{
			a[getfa(x)].w+=a[getfa(y)].w;
			a[getfa(x)].v+=a[getfa(y)].v;
			a[getfa(y)].w=a[getfa(y)].v=0;
			fa[getfa(y)]=fa[getfa(x)];//这里千万要注意是一棵树根加到另外一颗树的根！！！我就在这里出错了。。。
		}
			
	}
	for(int i=1;i<=n;i++){
		for(int j=W;j>=a[i].w;j--){
			f[j]=max(f[j],f[j-a[i].w]+a[i].v);
		}
	}//普通 01 背包求解。
	cout<<f[W];
    return 0;
}
```

### 题外话：
题目标签建议放**背包**与**并查集**，难度建议评**黄**。


---

## 作者：XinFengIneverleft (赞：1)

### [原题链接](https://www.luogu.com.cn/problem/AT_kupc2019_b)  
### [双倍经验](https://www.luogu.com.cn/problem/P1455)  
### [三倍经验](https://www.acwing.com/problem/content/1254/)
------------
## 题意简述  
有 $n$ 件商品，商品之间有 $m$ 种捆绑关系，具有捆绑关系的商品只能捆绑销售。求在不超出预算的情况下，可以买到的商品价值的最大值。  
## 题目分析  
本题打眼一看就知道是个 $01$ 背包，但是题目还要求捆绑销售，可以使用并查集轻松维护捆绑关系。  
我们再开一个结构体，存入具有相同捆绑关系的商品，使其组成一整个新商品再进行状态转移。  
## 代码  
代码如下，详见注释。  
```cpp
#include <bits/stdc++.h>
using namespace std;

int v[10005], w[10005];//v[i]表示第i个物品花费的代价 w[i]表示第i个物品的价值
int px[10005], dp[10005];//px数组存储每个节点的父节点 dp数组供状态转移使用

struct node
{
	int v, w;//这里的v和w表示新构造的商品的代价和价值
} no[10005];

int find(int x)//并查集板子
{
	if (px[x] != x)
		px[x] = find(px[x]);
	return px[x];
}

int main()
{
	int n, m, ww;//n件商品 m组捆绑关系 ww为预算
	cin >> n >> m >> ww;
    
	for (int i = 1; i <= n; i++)//并查集初始化！！！
		px[i] = i;//将每个节点的父节点初始化为自己

	for (int i = 1; i <= n; i++)//读入商品代价、价值
		cin >> v[i] >> w[i];
	for (int i = 1; i <= m; i++)//读入捆绑关系，同时进行合并操作
	{
		cin >> x >> y;
		px[find(x)] = find(y);
	}
	for (int i = 1; i <= n; i++)//构造新商品
	{
		no[find(i)].v += v[i];//寻找i的祖宗节点
		no[find(i)].w += w[i];//以祖宗节点为编号构造新商品
	}
	for (int i = 1; i <= n; i++)//01背包状态转移板子
		for (int j = ww; j >= no[i].v; j--)
			dp[j] = max(dp[j], dp[j - no[i].v] + no[i].w);
	cout << dp[ww];
	return 0;
}
```


---

## 作者：Garbage_fish (赞：0)

## 做法

并查集+dp。

由于限制了不同货物之间的捆绑关系，因此可以把捆绑在一起的货物看作一个整体，即将它们的货物重量与价值分别累加起来，最后再做一次选或不选的 dp 即可。

可以在合并的过程中方便的将他们的和累加起来，即直接将子树的权值加到根节点的权值里面去。

```cpp
void un(int x, int y) {
	int fx = gf(x), fy = gf(y);
	if (fx != fy) {
		f[fx] = fy;
		c[fy] += c[fx];
		d[fy] += d[fx];
	}
}
//gf 为并查集求根函数
```

而 dp 的时候，需注意存在多个货物被捆绑到同一个，但是多次被统计的情况，要用一个 $vis$ 数组来记录是否已经取过。

**[AC](https://www.luogu.com.cn/record/135449900) Code:**

```cpp
#include <bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
const int N = 1e4 + 10;
int n, m, w, f[N], c[N], d[N], dp[N], maxx;
bool vis[N];
int gf(int x) {
	int r = x;
	while (r != f[r])
		r = f[r];
	int i = x, j;
	while (f[i] != r) {
		j = f[i];
		f[i] = r;
		i = j;
	}
	return r;
}
void un(int x, int y) {
	int fx = gf(x), fy = gf(y);
	if (fx != fy) {
		f[fx] = fy;
		c[fy] += c[fx];
		d[fy] += d[fx];
	}
}
signed main() {
	IOS;
	cin >> n >> m >> w;
	for (int i = 1; i <= n; i++) {
		cin >> c[i] >> d[i];
		f[i] = i;
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		un(u, v);
	}
	memset(dp, -1, sizeof dp);
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		int fi = gf(i);
		if (vis[fi])
			continue;
		vis[fi] = true;
		for (int j = w; j >= c[fi]; j--) 
			if (dp[j - c[fi]] >= 0) {
				dp[j] = max(dp[j], dp[j - c[fi]] + d[fi]);
				maxx = max(maxx, dp[j]);
			}
	}
	cout << maxx;
	return 0;
}
```

---

## 作者：CleverPenguin (赞：0)

题目大意就是，一个零一背包。  
但是呢，有一些东西是捆绑销售的，也就是说，有两个东西，要么都买，要么都不买。  
由于捆绑的数量不唯一，没法直接加，考虑使用并查集。将有关系的两件物品选择一个父亲，在全部加完后再使用动规。

```cpp
int getfa(int x) {
	if(prt[x]==x)return x;
	return prt[x]=getfa(prt[x]);
}
```
然后再重新统计，使用背包求解：
```cpp
for(int i=1;i<=n-m;i++){
	for(int j=w;j>=w[i];j--){
		dp[j]=max(dp[j],dp[j-c[i]]+d[i]);
	}
}

---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_kupc2019_b)

## 题面

有 $n$ 个物品，编号从 $1$ 到 $n$。  

每件物品都有价值和重量，第$i$件物品的价值为 $v_i$，重量为 $w_i$。
你想从这些物品中挑选一些重量总和不超过 $W$，使所选物品的价值总和最大化。  

但是，有 $m$ 个条件。第 $j$ 的条件用 $(a_j,b_j)$ 表示，分别是“如果选择第 $a_j$ 个物品，就必须选择第 $b_j$ 个物品，如果选择第 $b_j$ 个物品，就必须选择第 $a_j$ 个物品”的意思。

在满足所有这些条件的基础上，从 $n$ 个物品中选择几个物品时的价值总和的最大值，使重量总和不超过 $W$。

## 分析

我们看一下题目的输出要求便可以想到 $01$ 背包。但是我们怎么处理题目中的这个问题呢？

>如果选择第 $a_j$ 个物品，就必须选择第 $b_j$ 个物品，如果选择第 $b_j$ 个物品，就必须选择第 $a_j$ 个物品。

我们便想到了并查集。

我们来说说并查集是什么：就是一种快速查询图中两个点是否联通的算法

我们通过判断两个节点的祖先（这个是自己选定的），如果祖先相同，那么两个点联通。反之亦然。

在这里我使用了路径压缩，如果不会的话可以上网查一下，这里就不过多叙述了。

# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e4+100;
#define int long long
int fa[N],n,m,money,tot[N],cost[N],u,v,dp[N];
int find_fa(int x){
	if(fa[x]==x)return x;
	return fa[x]=find_fa(fa[x]);
}
void add(int x,int y){
	int f_x=find_fa(x),f_y=find_fa(y);
	if(f_x==f_y)return;//如果在一个里面，退出
	fa[f_x]=f_y;
	tot[f_y]+=tot[f_x];
	cost[f_y]+=tot[f_x];
	return;
}
signed main(){
	scanf("%lld %lld %lld",&n,&m,&money);
	for(int i=1;i<=n;i++){
		scanf("%lld %lld",&cost[i],&tot[i]);
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		scanf("%lld %lld",&u,&v);
		add(u,v);
	}
	for(int i=1;i<=n;i++){
  		//判断是否是最上面的定点
		if(fa[i]==i)
		for(int j=money;j>=cost[i];j--){
			dp[j]=max(dp[j],dp[j-cost[i]]+tot[i]);
		}
	}
	printf("%lld",dp[money]);
	return 0;
}
```


---

## 作者：filletoto (赞：0)

## 思路
简单的背包问题。

因为配套购买是双向的，相当于把两个物品“合并”在一起，变成另一个大的物品，所以我们可以用并查集一步一步合并建树，最后合并的物品的价值和重量就在每棵树的根。

最后两重循环进行背包问题求解。

背包部分，我们可以定义一个一维数组 $dp$。

$dp_i$ 表示取到第 $i$ 个物品的最大价值

每次有两种操作，可以选择要不要装这个物品，明白后即可得出转移方程

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
//快速读入
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') 
	{
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
int n,m,w,f[10005],c[10005],d[10005],x,y,find_x,find_y,dp[10005];
inline void init()//初始化
{
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
	}
	return ;
} 
inline int find(int x)//路径压缩找祖先
{
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
int main()
{
	n=read();
	m=read();
	w=read();
	init();
	for(int i=1;i<=n;i++)
	{
		c[i]=read();
		d[i]=read();
	}
	//并查集合并
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		find_x=find(x);
		find_y=find(y);
		f[find_x]=find_y;
	}
	//计算大型云朵的重量和价值
	for(int i=1;i<=n;i++)
	{
		if(f[i]!=i)
		{
			find_x=find(i);
			d[find_x]+=d[i];
			d[i]=0;
			c[find_x]+=c[i];
			c[i]=0;
		}
	}
	//01背包
	for(int i=1;i<=n;i++)
	{
		for(int j=w;j>=c[i];j--)
		{
			dp[j]=max(dp[j],dp[j-c[i]]+d[i]);
		}
	}
	cout << dp[w] << endl;
	
	
	
	return 0;
}
```

---

## 作者：Ferdina_zcjb (赞：0)

题意很简单，在此不赘述。

其实，这道题不难，重点在于 01 背包，其中“给出小于 $n$ 的正整数 $a$ 和 $b$，若选择将编号为 $a$ 的物品放入背包，则必须把编号为 $b$ 的物品放入背包；若选择将编号为 $b$ 的物品放入背包，则也必须把编号为 $a$ 的物品放入背包。”这一要求也很简单，只需要运用并查集**将 $a$ 与 $b$ 并起来成为一个统一物品**即可。

01 背包：

```cpp
void DP(void){
    for(int i=1;i<=n;i++){
		for(int j=W;j>=a[i].w;j--){
			dp[j]=max(dp[j],dp[j-a[i].w]+a[i].v);
		}
	}
}
```

并查集：

```cpp
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void bing(int x,int y){
    a[x].w+=a[y].w;
	a[x].v+=a[y].v;
	a[y].w=a[y].v=0;
	fa[y]=fa[x];
}
for(int i=1;i<=m;i++){
    int q1,q2;
	cin >> q1 >> q2;
    int fx = find(q1),fy = find(q2);
	if(fx==fy){
    	continue;
    }else{
		bing(fx,fy);
	}		
}
```

全部代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
const int MAXM = 10005;
using namespace::std;
int n,m,W,fa[MAXM],dp[MAXM];
struct node{
	int w,v;
}a[MAXM];
void init(){//初始化并查集。
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
}
int find(int x){//并查集。
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void DP(void){//01背包。
    for(int i=1;i<=n;i++){
		for(int j=W;j>=a[i].w;j--){
			dp[j]=max(dp[j],dp[j-a[i].w]+a[i].v);
		}
	}
}
void bing(int x,int y){//合并。
    a[x].w+=a[y].w;
	a[x].v+=a[y].v;
	a[y].w=a[y].v=0;
	fa[y]=fa[x];
}
signed main(){
    cin >> n >> m >> W;
    init();
    for(int i=1;i<=n;i++){
    	cin>>a[i].w>>a[i].v;
	}
	for(int i=1;i<=m;i++){
        int q1,q2;
		cin >> q1 >> q2;
        int fx = find(q1),fy = find(q2);
		if(fx==fy){
            continue;
        }else{//合并成大物体。
			bing(fx,fy);
		}
			
	}
	DP();
	cout << dp[W] << endl;
    return 0;
}
```

题目难度不大，其实“普及/提高-”就行了（个人认为）。

---

## 作者：lovely_hyzhuo (赞：0)

并查集 + 背包好题。

双倍经验 P1455。



------------
## 1.初步分析

初步看题时，以为这是有依赖的背包，结果是 01 背包。

整体思路就是将捆绑的物品一起售卖，只有选和不选两种操作，所以就是 01 背包啦。

对于每一个连通块的根节点，价值放到 $w$ 数组里面，代价放到 $v$ 数组里面。

## 2.定义状态，终点

由于是 $01$ 背包，所以定义 $dp_j$ 表示在 $j$ 的价钱下最大的收益。

那么终点就是 $dp_W$

## 3.完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,W;
int fa[100010],v[100010],w[100010],vis[100010],wis[100010],c[100010],d[100010],dp[100010];
int find(int x)
{
	if(fa[x]!=x)
		return fa[x]=find(fa[x]);
	return x;
}
int main()
{
	cin>>n>>m>>W;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=n;i++)
		cin>>c[i]>>d[i];
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		int fx=find(x),fy=find(y);
		if(fx!=fy)
			fa[fy]=fx;
	}
	for(int i=1;i<=n;i++)
	{
		int t=find(i);
		vis[t]+=c[i];
		wis[t]+=d[i];
	}
	int l=0;
	for(int i=1;i<=n;i++)
	{
		if(vis[i]!=0)
		{
			l++;
			v[l]=vis[i];
			w[l]=wis[i];
		}
	}
	for(int i=1;i<=l;i++)
	{
		for(int j=W;j>=v[i];j--)
		{
			dp[j]=max(dp[j],dp[j-v[i]]+w[i]);
		}
	}
	cout<<dp[W];
	return 0;
}
```


---

## 作者：yzy4090 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_kupc2019_b)  
本题建议评黄（[双倍经验](https://www.luogu.com.cn/problem/P1455)）。  

**思路**  
首先可以得知如果没有配套购买的操作就是一个裸的 01 背包问题。因为配套购买是双向的，相当于把两个物品“绑定”在一起，考虑使用路径压缩并查集维护绑定关系，在并查集合并时更新大物品的重量和价值。  

**代码**  
```cpp
#include<iostream>
#include<cstring>
#include<map>
const int MAXN=1000005;
using namespace std;
int n,m,w,c[MAXN],d[MAXN],fa[MAXN],f[MAXN];
int fafind(int now){
	return fa[now]==now?now:fa[now]=fafind(fa[now]);
}//路径压缩并查集
void unify(int x,int y){
	int fx=fafind(x),fy=fafind(y);
	if(fx!=fy){
		c[fy]+=c[fx];
		d[fy]+=d[fx];
		fa[fx]=fy;//大物品的重量和价值
	}
	return;
}//合并操作
int main(){
	scanf("%d%d%d",&n,&m,&w);
	for(int i=1;i<=n;i++){
		fa[i]=i;
		scanf("%d%d",&c[i],&d[i]);
	}
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		unify(u,v);
	}
	for(int i=1;i<=n;i++)if(fa[i]==i){//是不是大物品
		for(int j=w;j>=c[i];j--)
			f[j]=max(f[j],f[j-c[i]]+d[i]);//01 背包模板
	}
	printf("%d",f[w]);
	return 0;
}
```
时间复杂度为 $\mathcal O(nW)$。

---

## 作者：Loser_Syx (赞：0)

## 思路

这题的重点在于合并，它给你 $x$ 和 $y$ 说他们必须要捆绑在一起买，那么我们就自主的联想到“连通块”与“并查集”，所以每次操作都只需将它们所在的集内合并便可，注意特判是否已经在被合并了。

剩下就都是 01 背包的板子了。

本题使用并查集的正确性是因为两个捆绑的物品关系是相互的，而不是单向的，用并查集便可解决。

## 代码

```cpp
#include <iostream>
using namespace std;
int cost[101001], jz[101001], f[101001];
int rtcost[101001], rtjz[101001];
int dp[101010];
int fd(int x){
    while(x != f[x]) x = f[x] = f[f[x]];
    return x;
}
int max(int a, int b){
    return a > b ? a : b;
}
int main(){
    int n, m, w;
    scanf("%d%d%d", &n, &m, &w);
    for(int i = 1; i <= n; ++i){
        scanf("%d%d", &cost[i], &jz[i]);
        f[i] = i;
    }
    while(m--){
        int x, y;
        scanf("%d%d", &x, &y);
        int _1 = fd(x), _2 = fd(y);
        if(_1 != _2){
            f[_2] = _1;
            cost[_1] += cost[_2];
            jz[_1] += jz[_2];
        }
    }
    int len = 0;
    for(int i = 1; i <= n; ++i){
        if(f[i] == i){
            rtcost[++len] = cost[i];
            rtjz[len] = jz[i];
            //cout << i << '\n';
        }
    }
    int mx = 0;
    for(int i = 1; i <= len; ++i){
        //cout << rtcost[i] << ' ' << rtjz[i] << '\n';
        for(int j = w; j >= 0; --j){
            if(j >= rtcost[i]){
                dp[j] = max(dp[j], dp[j - rtcost[i]] + rtjz[i]);
            }
        }
    }
    cout << dp[w] << '\n';
    return 0;
}
```

---

