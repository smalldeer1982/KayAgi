# [JSOI2015] salesman

## 题目描述

某售货员小 T 要到若干城镇去推销商品,由于该地区是交通不便的山区，任意两个城镇之间都只有唯一的可能经过其它城镇的路线。 小 T 可以准确地估计出在每个城镇停留的净收益。这些净收益可能是负数，即推销商品的利润抵不上花费。由于交通不便，小 T 经过每个城镇都需要停留，在每个城镇的停留次数与在该地的净收益无关，因为很多费用不是计次收取的，而每个城镇对小 T 的商品需求也是相对固定的，停留一次后就饱和了。每个城镇为了强化治安，对外地人的最多停留次数有严格的规定。

请你帮小 T 设计一个收益最大的巡回方案,即从家乡出发，在经过的每个城镇停留，最后回到家乡的旅行方案。你的程序只需输出最大收益，以及最优方案是否唯一。方案并不包括路线的细节，方案相同的标准是选择经过并停留的城镇是否相同。因为取消巡回也是一种方案，因此最大收益不会是负数。小 T 在家乡净收益是零，因为在家乡是本地人，家乡对小 T 当然没有停留次数的限制。

## 说明/提示

#### 样例说明

最佳路线包括城镇 $1,2,4,5,9$。

---

#### 数据范围

对于 $100\%$ 的数据，$5\leq n\leq 10^5$。

## 样例 #1

### 输入

```
9
-3 -4 2 4 -2 3 4 6
4 4 2 2 2 2 2 2
1 2
1 3
1 4
2 5
2 6
3 7
4 8
4 9```

### 输出

```
9
solution is unique```

# 题解

## 作者：hzoi_liuchang (赞：9)

## 分析
题目中的任意两个城镇之间都只有唯一的可能经过其它城镇的路线非常重要，这就说明题目中给出的图一定是一棵树

因此，联系最近学过的内容，我们可以用树形DP求解

题目中给出了停留次数的限制，这其实就是给出了你最多能访问多少子树

注意：在一个节点停留n次说明你可以遍历n-1棵子树，因为你还要从子树返回这一个节点，所以在读入时要w--（为了方便，后文的停留次数都是指--之后的）

那么动态转移方程是什么呢？

其实很简单，就是在停留次数限制内选择价值最大的子树，同时如果一个子树的价值为负，那么我们就不能选
![](https://cdn.luogu.com.cn/upload/image_hosting/cf9jk6qo.png)

比如上面这幅图，如果在父亲节点只能停留1次，则我们要选择价值最大的节点5

如果停留2次，我们要选择价值最大的两个节点5、3

如果停留3次呢，我们是选择5、3、-1吗？显然不是，因为选择-1这个点会拉低价值，所以我们只选5、3两个点就可以

知道了怎么选择节点，我们来看一下什么情况会出现多种选择

1、既然是重复，那么两个节点价值相同的情况一定要考虑一下
![](https://cdn.luogu.com.cn/upload/image_hosting/k1oq68k8.png)

我们看上面这幅图

如果在父亲节点只能停留1次，则我们会有两种情况：选左边的5或者右边的5

如果停留2次，我们只有一种情况：两个5都选

如果停留3次，我们也有两种情况：选上2个5，左边的4和右边的4再任选一个

停留4次呢？又只有一种了

所以，只有当父亲节点剩余的停留次数为1，而且此时最大值有两个及以上儿子节点，那么就会有多种情况

2、子节点的价值为零
这种情况比较特殊，因为无论你选没选到他，价值都是一样，所以会有两种选择

但是前提是价值为0的节点必须前k大的节点之内，因为如果你都遍历不到他，更谈不上决策了

记录子节点的最大值我们用优先队列就可以

代码
把这两种情况搞清之后，我们就可以开始写代码了
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<queue>
using namespace std;
const int maxn=2e5+5;
struct asd{
    int from,to,next;
}b[maxn];
int tot=1,head[maxn];
int da[maxn],cx[maxn];
void ad(int aa,int bb){
    b[tot].from=aa;
    b[tot].to=bb;
    b[tot].next=head[aa];
    head[aa]=tot++;
}//建边
int f[maxn];//记录最大值
int jud;
void dfs(int now,int fa){
    priority_queue<int> q;//默认大根堆
    for(int i=head[now];i!=-1;i=b[i].next){
        int u=b[i].to;
        if(u==fa) continue;
        dfs(u,now);
        q.push(f[u]);//遍历，同时将子节点的值pop进去
    }
    int cnt=0,jl=0x3f3f3f3f;
    if(q.size()>=2){
        int xx=q.top();
        q.pop();
        jl=q.top();
        q.push(xx);
    }
    //cnt记录所选元素的个数，jl记录上一次选的元素
    //这道题数据很水，把jl赋值成0x3f3f3f3f都能过
    //下面是错误写法
    /*
    int cnt=0,jl=0x3f3f3f3f;或者jl=0;jl=任何数
    没有后面的判断
    虽然能过，但是不对
    */
    while(!q.empty()){
        cnt++;
        int xx=q.top();
        if(xx==0 || (cx[now]==cnt && jl==xx)){
            jud=1;
        }//有两种决策的情况
        if(xx<0 || cx[now]+1==cnt) break;//超过停留次数
        f[now]+=xx;
        jl=xx;
        q.pop();//一定要pop
    }
    while(!q.empty()) q.pop();//pop不pop都可以
}
int main(){
    memset(head,-1,sizeof(head));
    int n;
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        scanf("%d",&da[i]);
    }
    for(int i=2;i<=n;i++){
        scanf("%d",&cx[i]);
        cx[i]--;//一定要--
    }
    cx[1]=0x3f3f3f3f;//1号节点可以停留无数次
    for(int i=2;i<=n;i++){
        int aa,bb;
        scanf("%d%d",&aa,&bb);
        ad(aa,bb);
        ad(bb,aa);//建边
    }
    for(int i=1;i<=n;i++){
        f[i]=da[i];//给每一个节点初始化价值
    }
    dfs(1,0);//从根节点开始遍历
    if(jud) printf("%d\nsolution is not unique\n",f[1]);
    //有多种情况也要输出值，不要忘了
    else printf("%d\nsolution is unique\n",f[1]);
    return 0;
}
```

代码的细节在注释里
这道题思维量不小，大家一定要认真思考

---

## 作者：bzzltl (赞：7)

## 题目大意
有 $ n $ 个点所组成的树，其中 $1$ 号点是其根，每个点都有一个权值（可以为负）和规定的经过该点的次数要求，求从 $ 1 $ 号点开始向其他点走，回到 $ 1 $ 点所能获得的最大价值，并求出可以获得收益最大值的方案是否唯一。


## 解决思想

树形dp和贪心

## 题目分析

由“任意两个城镇之间都只有唯一的可能经过其它城镇的路线”可知该图是个树，由此我们才可以进行接下来的分析。

对于停留次数这一限制，其实是限制访问子树的最大个数。

即若点 $i$ 的限制次数记作 $ c_i $ 则 $ i $ 点最多可以访问 $ c_i -1$ 棵子树。

注意，因为点 $ 1 $ 没有限制条件，所以我们在赋 $ c_1 $  的初始值要把它设置为无穷大。

关于取得最大收益的方案是否唯一，有以下三种情况会导致最大值情况不唯一：

1. 某个子树的值为 $ 0 $ ，显然，我们可以选择将其纳入，或者不纳入，对最大值无影响。
2. 最后可以一个选择的子树权值和一个未选择的子树权值一样大。
3. 这个子树的子树有以上几种情况。

我们设 $ f_i  $ 表示第 $ i $ 点所能获得的最大利益，设 bool 数组 $ vis_i  $ 表示第 $ i $ 点是否可以有多种选择。

在递归过程中，贪心地想，我们可以在递归中对于子树的权值排序，然后 如果子树权值大于 $ 1 $ 并且还能选择,那么让 $ f_u\leftarrow f_u+f_v $ 。

选择过程中，如果出现 $ f_v =0$ 的情况，那么让 $ vis_u=1 $ ，并且把这个结果往上传。 

选择完成后，特判结束选择时，有因为次数限制而不能选但是和某个已经选入的子树的利益相同的子树，如果有的话， $ vis_u=1 $ ，结果上传。 



## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long LLM=9223372036854775807;
const int IM=2147483647;
const int N=1000001;
inline int read(){int x=0,y=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}return x*y;}

int n,cnt,w[N],c[N],f[N],head[N],son[N];
bool vis[N];

struct node{
	int v,nex;
}t[N];

bool cmp(int a,int b){return f[a]>f[b];}

void add(int u,int v)
{
	t[++cnt].v=v;
	t[cnt].nex=head[u];
	head[u]=cnt;
}

void dfs(int u,int fath)
{
	f[u]=w[u];
	for(int i=head[u];i;i=t[i].nex)
	{
		if(t[i].v==fath) continue;
		dfs(t[i].v,u);
		if(vis[t[i].v]) vis[u]=true;
	}
	int cnt=0,bj=1,jl;
	for(int i=head[u];i;i=t[i].nex)
	{
		if(t[i].v==fath) continue;
		son[++cnt]=t[i].v;
	}
	sort(son+1,son+cnt+1,cmp);
	for(int i=1;i<=min(c[u]-1,cnt);i++)
	{
		if(f[son[i]]<0)
		{
			bj=0;
			break;
		}
		if(f[son[i]]==0) vis[u]=true;
		f[u]+=f[son[i]];
		jl=i;
	}
	if(bj&&f[son[jl]]==f[son[jl+1]]&&jl<cnt) vis[u]=true;
}

signed main()
{
	n=read();
	for(int i=1;i<n;i++) w[i+1]=read();
	for(int i=1;i<n;i++) c[i+1]=read();
	c[1]=IM;
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	printf("%d\n",f[1]);
	if(vis[1]) puts("solution is not unique");
	else puts("solution is unique");
	return 0;
}

```

---

## 作者：songge888 (赞：3)

### 题意

给你一颗树，根节点是 $1$，每个节点有一个最大访问次数 $num_i$ 和权值 $val_i$（$num_1=INF$），每个点的权值只记录一次，求从根结点出发，最大的权值和。

### 思路

有一棵树，如图：

![graph _8_.png](https://s2.loli.net/2025/03/03/6rfYca3TpN5JvwW.png)

考虑点 $3$，想要让点 $3$ 访问所有的子节点，$3$ 至少要访问 $4$ 次。

$2\to 3$（$1$次）。

$3\to 5,5\to 3$（$2$次）。

$3\to 4,4\to 3$（$3$次）。

$3\to 7,7\to 3$（$4$次）。

显然，从点 $i$ 到 $i$ 所有的子节点需要 $cnt_i+1$ 次访问机会（$cnt_i$ 指 $i$ 的子节点的个数）。

那么如果一个点到不了它所有的子节点，那么就只去收益最大的点。

怎么求受益最大的点呢？

考虑树形 DP。

$dp_u$ 表示 $u$ 点的最大收益，$dp_u=a_u+\sum_{i=1}^{\min({cnt_u},{num_u})} dp_v$。

可以先求出所有的 $dp_v$，再从大到小排序，使用优先队列即可。

题目还要判断路径是否唯一，考虑 $2$ 种情况：

- 如果可以选的点中如果一个点的权值是 $0$，那么对答案就没有影响，答案不唯一。
- 如果选的最小的一个点有 $2$ 个，答案也不唯一。

注意 $dp_i<0$ 的点不能选。

时间复杂度 $O(n \log n)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define bug cout<<"___songge888___"<<'\n';
using namespace std;
int n;
int dp[100010];
int val[100010],num[100010];
vector<int> g[100010],p[100010];
bool cmp(int x,int y){
	return x>y;
}
int flag;
void dfs(int u,int fa){
	dp[u]=val[u];
	priority_queue<pair<int,int>> q;
	for(auto v:g[u]){
		if(v==fa){
			continue;
		}
		dfs(v,u);
		q.push({dp[v],v}); 
	}
	int las=0;
	for(int i=1;i<num[u];i++){
		if(q.empty()){
			break;
		}
		auto [now,j]=q.top();
		q.pop();
		if(now<0){
			break;
		}
		dp[u]+=now;
		las=now;
		if(now==0){
			flag=1;
		}
	} 
	if(!q.empty()&&q.top().first==las){
		flag=1;
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>val[i+1];
	}
	num[1]=100000000000000000000;
	for(int i=1;i<n;i++){
		cin>>num[i+1];
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	cout<<dp[1]<<'\n';
	if(flag){
		cout<<"solution is not unique";
	}
	else{
		cout<<"solution is unique";
	}
	return 0;
}
```

---

## 作者：Su_Zipei (赞：3)

## 分析
这题一眼应该就能看出来是树形DP，题目中都多次暗示了，所以先把定义搞出来，最开始我跳了一个坑就是把状态定义成了$DP[i][j]$，即在$i$号节点停留$j$次的最大收益，然后想啊想，就没有然后了。。。。。

模拟几个样例发现停留次数有一个很特殊的性质，就是最多只能经过该点的儿子停留次数-1次，不然就回不了家了，但好像对我们这个转移没有什么帮助，回去读一遍题，发现点权可能为负？

**负的？**

那第二维状态就没意义了，我要是那个$Salesman$，肯定先去赚钱多的，不去亏本的，所以这好像直接用一个贪心就可以了，证明也比较好证吧，去一个权大的点肯定比去一个权小的点收获大，不去负权点肯定比去收获大，所以每次从大到小取够停留次数减一或把正儿子取完即可，所以转移方程就是$DP[u]=\sum_{i=1}^s{DP[i]}$。

下面考虑第二个问题，多组解，因为这是个树，所以只有两种情况有多组解，一是有一个子树的权值为0，这样不管怎么走都可以，另一个是所选的最后一棵子树与一棵未选的子树权值一样，这样我们完全可以选另外一棵子树。关于选子树的话，我用的是堆，这个判断是不是为空啊什么的比较方便，当然用$sort$也行，然后就是代码实现啦，其实想明白也挺简单。
```
#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
const int N=1e5+10;
struct Edge{
    int to,nxt;
}e[N<<1];
int Head[N],len;
void Ins(int a,int b){
    e[++len].to=b;e[len].nxt=Head[a];Head[a]=len;
}
struct Node{
    int val,idx;
    Node(){val=idx=0;}
    Node(int a,int b){val=a;idx=b;}
    bool operator <(const Node&A)const{
        return val<A.val;
    }
};
int w[N],lim[N],g[N],dp[N];
inline int read(){
    int w=1,x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;ch=getchar();
    }
    while(ch<='9'&&ch>='0'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*w;
}
void dfs(int u,int fa){
    priority_queue<Node > q;
    dp[u]=w[u];
    for(int i=Head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa)continue;
        dfs(v,u);
        q.push(Node(dp[v],g[v]));
    }
    int tot=1,last;
    while(++tot<=lim[u]&&!q.empty()){
        Node now=q.top();q.pop();
        if(now.val<0)break;
        if(now.val==0){g[u]=1;break;}
        dp[u]+=now.val;
        g[u]|=now.idx;
        last=now.val;
    }
    if(!q.empty())if(q.top().val==last)g[u]=1;
}
int main(){
    int n=read();
    lim[1]=N;
    for(int i=2;i<=n;i++)
        w[i]=read();
    for(int i=2;i<=n;i++)
        lim[i]=read();
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        Ins(a,b);Ins(b,a);
    }
    dfs(1,0);
    cout<<dp[1]<<'\n';
    if(g[1])puts("solution is not unique");
    else puts("solution is unique");
    return 0;
}
```

---

## 作者：yanbinmu (赞：2)

## 题意

给定一棵 $n$ 个点的树，每个点都有一个权值（可以为负）以及可以经过该点的最大次数，求从 $1$ 号点开始向其他点走，回到 $1$ 点所能获得的最大价值，并求出获得收益最大值的方案是否唯一。

## 解题思路

树形DP + 贪心

## 分析

因为最后要回到 $1$ 点，所以遍历子树后还会再经过一次自己。

所以对于一个节点 $u$ 来说，他一共可以遍历 $w_{u} - 1$ 颗子树，其中 $w_{u}$ 为最大可经过次数，**要将 $w_{1}$ ，即家乡节点的最大访问次数设置为正无穷。**

那么我们可以考虑贪心，**设 $f_{i}$ 为节点 $i$ 所能获得的最大价值**。

对于每一个节点，将所有的子树的 $f_{i}$ 从大至小排序，从大往小选，就可以获得最大的价值。

若有一颗字数的价值为 $0$ 那么是否选它都不会影响最后的价值，所以选和不选就会成为两种方案，所以方案不唯一。

因此，我们可以设 $vis_{u}$ 为在 $u$ 点是否有多种方案，在转移时直接合并即可。

剩下的看看代码注释吧。

## 代码

```C++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct Edge{
    int to, nxt;
}edge[N << 1];
int head[N], tot = 1;
void add(int u, int v){
    edge[tot].to = v;
    edge[tot].nxt = head[u];
    head[u] = tot ++ ;
}

struct node{
    int vis, v;
    node(int a, int b){
        v = a;
        vis = b;
    }
    friend bool operator <(const node a, const node b){
        return a.v < b.v;
    }
};
int f[N], vis[N];
int v[N], w[N];//v[i]为权值，w[i]为经过次数限制
void dfs(int u, int fa){
    f[u] = v[u];//初始到自己有一个价值
    priority_queue<node> q;
    for(int i = head[u];i;i = edge[i].nxt){
        int v = edge[i].to;
        if(v == fa) continue;
        dfs(v, u);
        q.push((node){f[v], vis[v]});
    }
    int cnt = 1, last;
    while(cnt <= w[u] - 1 && q.size()){//选择 w[i] - 1 颗子树
        auto t = q.top();
        q.pop();
        if(t.v < 0) break;
        if(t.v == 0){//因为排过序，剩下的就都小于零，不会使最终的利润更大，直接 break 即可
            vis[u] = 1;
            break;
        }
        vis[u] |= t.vis;//子树有多种方案，其父亲当然有多种方案
        f[u] += t.v;
        last = t.v;
        cnt ++ ;
    }
    if(q.size() && last == q.top().v) vis[u] = 1;//如果有一个节点的权值与某一个点相同但是没有取，那么可以不取现在所取得，而去取这个，所以有多种方案
    return ;
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 2;i <= n;i ++ ){
        scanf("%d", &v[i]);
    }
    for(int i = 2;i <= n;i ++ ){
        scanf("%d", &w[i]);
    }
    for(int i = 1;i < n;i ++ ){
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }
    w[1] = 0x3f3f3f3f;//家乡不限制访问次数
    dfs(1, 0);
    printf("%d\nsolution is%sunique", f[1], vis[1] ? " not " : " ");
    return 0;
}
```

---

## 作者：XCDRF_ (赞：1)

# P6082 \[JSOI2015] salesman

[原题传送门](https://www.luogu.com.cn/problem/P6082)

[更好的阅读体验](https://www.luogu.com.cn/article/79svjn7h)

## 解题思路

读完题后容易发现，给出的图是一棵树。题目还要求求最大方案，可以想到树形 DP。

将题目限制转化一下，限制一个点的经过次数其实就是限制了能遍历的子树个数。因为最后要回到根节点，所以最多遍历 $c_i-1$ 个子树。注意，此处点 $1$ 没有经过次数限制，要将点 $1$ 赋为正无穷。

设 $f_i$ 为 $i$ 号点能取得的最大收益，则贪心的想，$f_i$ 肯定为它的儿子中 $f_i$ 前 $c_i-1$ 大值的和，此时有几种情况需要特判：

1. 如果前 $c_i-1$ 大值中有负数，则跳过负数，毕竟没有人会做亏本买卖。
2. 如果前 $c_i-1$ 大值中有 $0$，则这个选不选都可以，这样就产生了多种情况，打上标记。
3. 如果第 $c_i-1$ 大值和第 $c_i$ 大值相等，那这两个取哪个都行，又会产生多种情况，打上标记。

最后输出 $f_1$，如果打过标记输出 `solution is not unique`，没打过标记输出 `solution is unique`。

## 参考代码

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,m,tot;
int head[N],a[N],c[N],f[N];
bool flag;
vector<int> v[N];
struct Edge{
	int nxt,to;
}edge[N<<1];
void add(int x,int y){
	edge[++tot]={head[x],y};
	head[x]=tot;
}
void dfs(int x,int fa){
	f[x]+=a[x];
	for(int i=head[x];i;i=edge[i].nxt){
		int xx=edge[i].to;
		if(xx==fa) continue;
		dfs(xx,x);
		v[x].push_back(f[xx]);
	}
	sort(v[x].begin(),v[x].end(),greater<int>());
	for(int i=0;i<min(c[x]-1,(int)v[x].size())&&v[x][i]>=0;i++){
		f[x]+=v[x][i];
		if(v[x][i]==0) flag=1;
	}
	if((int)v[x].size()>=c[x]&&v[x][c[x]-2]==v[x][c[x]-1]) flag=1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++) cin>>a[i];
    for(int i=2;i<=n;i++) cin>>c[i];
    c[1]=0x3f3f3f3f;
    for(int i=1,x,y;i<n;i++){
    	cin>>x>>y;
    	add(x,y);
    	add(y,x);   	
	}
	dfs(1,-1);
	cout<<f[1]<<'\n';
	if(flag) cout<<"solution is not unique";
	else cout<<"solution is unique";
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/205742737)

---

## 作者：Misty_Post (赞：1)

### P6082 [JSOI2015] salesman 题解

根据我的做题历程来带大家仔细分析一下这道题的所有细节。

# 题意：
给出一个图，通过分析不难发现是一棵树。每个点有自己的价值和通过次数，问从一号点出发再回到一号点的最大价值是多少，并且判断是否是只有一种方案可以得到最大答案。

# 分析

由于题目里说了，在每个城镇的停留次数与在该地的净收益无关，所以稍加分析便可发现时一个常见的由下往上的一个树形动态规划套路，尝试用树形动态规划求解。

每个点的停留次数，可以理解为每个点只可以选有限个子树，想清楚这一点就可以写了。

但是，它错了，为什么呢？

首先，我们要注意，一号点可以经过无数次，要特殊处理。

然后，我们留意到我们不一定要用完点的所有可经过次数，当子树为负数时就不要了。

接下来，我们还要处理唯一性的问题。

不难发现，“唯一”就代表没有选择，如果在取子树时出现了选择，那就不唯一。

也就是说，当我们已经取完了所有可取次数，而取到的最小值等于没有取到的最大值时，就是不唯一。

然后，如果有子树的价值等于零，那选不选显然都可以，也不唯一。

接下来就没有问题啦，开写。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll c[1000000],n,p[1000000],pd[1000000];
ll co[1000000];
ll head[1000000],tot;
struct nood{
	ll v,nxt;
}es[1000000];
void adde(ll x,ll y){
	es[++tot].v=y,es[tot].nxt=head[x],head[x]=tot;
}
void dfs(ll x,ll fa){
	//cout<<x<<"*"<<endl;
	priority_queue<pair<ll,ll>> q;
	for(int i=head[x];i;i=es[i].nxt){
		ll v=es[i].v;
		if(v!=fa){
			dfs(v,x);
			q.push({co[v],v});
		}
	}
	ll lsop=0;
	for(int i=1;i<=p[x];i++){
		if(q.empty()){
			break;
		}
		ll v=q.top().second;
		ll coo=q.top().first;
		//cout<<x<<"->"<<v<<" "<<coo<<endl;
		if(coo==0||pd[v]==1){
			pd[x]=1;
		}
		if(coo>0){
			lsop=coo;
			co[x]+=coo;	
		}
		q.pop();
	}
	if(!q.empty()){
		if(q.top().first==lsop){
			pd[x]=1;
		}
	}
	co[x]+=c[x];
}
int main(){
	cin>>n;
	p[1]=1e18;
	for(int i=2;i<=n;i++){
		cin>>c[i];
	}
	for(int i=2;i<=n;i++){
		cin>>p[i];
		p[i]--;
	}
	ll x,y;
	for(int i=1;i<n;i++){
		cin>>x>>y;
		adde(x,y);
		adde(y,x);
	}
	dfs(1,0);
	cout<<co[1]<<"\n";
	if(pd[1]==0){
		cout<<"solution is unique";
	}
	else{
		cout<<"solution is not unique";
	}
}
```

---

## 作者：QianianXY (赞：1)

[传送门](https://www.luogu.com.cn/problem/P6082)

## 题意简述

一棵树，以点 $1$ 为起点。每个点都有向下遍历子树的数量限制。经过每个点获得收益。求收益最大值，且对于此最大值，是否有多种遍历方案。

## 题目分析

树形 dp。模型相似题目还有 [P3574 [POI2014] FAR-FarmCraft](https://www.luogu.com.cn/problem/P3574)。

定义 dp 数组 $f_u$ 表示以点 $u$ 为根的子树收益最大值。

对于每个 $u$，将子节点 $i$ 存进一个数组，按 $f_i$ 的大小降序排序。在**不超过遍历限制**，且 $f_i>0$ 的情况下，依次将 $f_i$ 加入 $f_u$，可保证结果最大。

第二个问题是如何判定 $f_u$ 的解是否唯一。（**下文“解”通指遍历方案**）

**默认 $f_i$ 已经有序**，设按大小顺序最后一个加入 $f_u$ 的点为 $i_1$，若存在 $f_{i_1+1}=f_{i_1}$，则 $i_1+1$ 和 $i_1$ 都是可遍历的点，所以解不唯一。

或者存在 $f_i=0$，则这个点可走可不走，使解不唯一。

又或者加入答案的 $f_i$ 解不唯一，则 $f_u$ 解不唯一。

可以对 $f$ 数组多开一维，``f[u][0]`` 记录答案，``f[u][1]`` 记录解是否唯一。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 200010
using namespace std;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, a[N], f[N][2], head[N], edge_cnt, w[N], que[N], tot;
struct edge {int nxt, v;} e[N << 1];

inline void add_edge(int u, int v) {e[++edge_cnt].nxt = head[u]; head[u] = edge_cnt; e[edge_cnt].v = v;}

inline bool cmp(const int &a, const int &b) {return f[a][0] > f[b][0];}

inline void solve(int u, int fa)
{
	for (rei i = head[u]; i; i = e[i].nxt) {if (e[i].v == fa) continue; solve(e[i].v, u); if (!f[e[i].v][0]) f[u][1] = 1;} tot = 0;
	for (rei i = head[u]; i; i = e[i].nxt) {if (e[i].v == fa) continue; if (f[e[i].v][0] > 0) que[++tot] = e[i].v;}
	sort(que + 1, que + 1 + tot, cmp); rei i = 1;
	for (; i <= min(tot, w[u]); i++) f[u][0] += f[que[i]][0], f[u][1] |= f[que[i]][1];
	if (i <= tot && f[que[i - 1]][0] == f[que[i]][0]) f[u][1] = 1;
	f[u][0] += a[u];
}

int main()
{
	read(n);
	for (rei i = 2; i <= n; i++) read(a[i]);
	for (rei i = 2; i <= n; i++) read(w[i]), w[i]--; w[1] = 1e9;
	for (rei i = 1; i < n; i++) {int u, v; read(u); read(v); add_edge(u, v); add_edge(v, u);}
	solve(1, 0);
	printf("%d\n", f[1][0]);
	if (f[1][1]) printf("solution is not unique");
	else printf("solution is unique");
	return 0;
}
```


---

## 作者：loceaner (赞：1)


## 题意

给定一棵$n$个点的树，有点权，你从$1$号点开始一次旅行，最后回到$1$号点。每到达一个点，你就能获得等于该点点权的收益， 但每个点都有进入该点的次数限制，且每个点的收益只能获得一 次，求最大收益。

## 思路

> 树形$\texttt{DP}$ + 优先队列 

比较容易看出来这是一道树形$\texttt{DP}$题

要注意的是最大停留次数为`输入次数-1`，因为还要从子树返回到这一个节点

然后下面考虑怎么$\texttt{DP}$

我们用$f[i]$表示以从$i$出发，访问以$i$为根的子树，并且最后能回到$i$的最大收益

显然我们要选较大且非负的数，因为去大点权的节点肯定比去小点权的点权更优，去非负点权的节点肯定比去负点权的节点更优，而且因为一个节点可以去多次且只记一次点权，所以肯定能够用完次数，因此我们每次在小于等于停留次数的前提下取完正儿子即可，这样就可以保证最大，所以$f[i]$就等于$i$所有正儿子的点权之和（前提是小于等于最大停留次数），最后的答案就是$f[1]$

下面来考虑解是否唯一的问题，解不唯一有两种情况：

1. $i$的子树中有权值为$0$的点。因为选不选权值都不变，所以可选可不选，因此解就不唯一了
2. 如果$i$在遍历过程中当父亲节点剩余的停留次数为$1$时，可选的最大值有两个及两个以上儿子节点，则解不唯一

所以在过程中判断一下就好了

## 代码

```cpp
/*
Author:loceaner
*/
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int A = 5e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
	char c = getchar(); int x = 0, f = 1;
	for( ; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return x * f;
}

int n, cnt, head[A], ti[A], a[A], f[A], flag[A];
struct node { int to, nxt; } e[A];

inline void add(int from, int to) {
	e[++cnt].to = to;
	e[cnt].nxt = head[from];
	head[from] = cnt;
}

struct Node {
	int val, id;
	Node() { val = id = 0; }
	Node(int a, int b) { val = a; id = b; }
	bool operator < (const Node &A) const {
		return val < A.val;
	}
};

void dfs(int x, int fa) {
	priority_queue <Node> q;
	f[x] = a[x];
	for (int i = head[x]; i; i = e[i].nxt) {
		int to = e[i].to;
		if (to == fa) continue;
		dfs(to, x);
		q.push(Node(f[to], flag[to]));
	}
	int vis = 0, last;
	while (++vis <= ti[x] && !q.empty()) {
		Node tmp = q.top(); q.pop();
		if (tmp.val < 0) break;
		if (tmp.val == 0) { flag[x] = 1; break; }
		f[x] += tmp.val;
		flag[x] |= tmp.id;
		last = tmp.val;
	}
	if (!q.empty()) 
		if (q.top().val == last) flag[x] = 1;
}

int main() {
	n = read();
	ti[1] = inf; //根节点可以访问无限次 
	for (int i = 2; i <= n; i++) a[i] = read();
	for (int i = 2; i <= n; i++) ti[i] = read() - 1;
	//最多遍历ti[i]-1次因为还要从子树回到这个节点 
	for (int i = 1, x, y; i < n; i++) {
		x = read(), y = read();
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	cout << f[1] << '\n';
	if (flag[1]) cout << "solution is not unique\n";
	else cout << "solution is unique\n";
	return 0;
}
```


---

## 作者：DarthVictor (赞：1)

## 题目
[原地址](https://www.luogu.com.cn/problem/P6082)
## 解说
刚看完这道题感觉还是挺乱的，~~可能那时候脑子不太清醒，一度觉得自己又要重拾Tarjan了。~~ 当然最后还是发觉应该用树形DP。

（以下dp[u]代表以u为根的包括自己在内的子树的最大利润，bool g[u]表示u及其子树的方案数是否唯一，唯一则为0，否则为1，t[u]代表u的次数，v[u]代表u的价值）

计算最大利润确实挺简单。有点像之前做过的[空调教室](https://www.luogu.com.cn/blog/DarthVictor/kai-pian-ci-the-start-yi-ji-vjudgehdu2242-kong-diao-jiao-shi)，但是多了次数限制和负数，但这不难处理。计算u的时候因为每个儿子在走完之后必须返回u来回到根节点，因此我们只能对儿子的dp值进行排序，选取前t[u]-1个，并且遇到负数立即停止因为接下来选的负数只能使总价值变小。

那么怎么处理方案是否唯一呢？

我们开一个bool数组g表示u及其子树的方案数是否唯一。显然，只有以下3种情况下方案数不唯一：

某个取得的儿子dp值为0(选不选都可以)

某个取得的儿子g值为1(在这颗子树中有不同的路径)

下个未选的儿子和最后选择的儿子f值相同(可以替换)~~（我写的时候忽略了这一点但是还是A了，大约是数据太弱了）~~

那么就从根开始递归一遍就可以了哦，最后看dp[1]和g[1]就可以了。

（部分实在想不上来的做法参考了DZN大佬的，谢谢啦~）

![](https://img2020.cnblogs.com/blog/1933812/202004/1933812-20200404194836708-426857835.jpg)
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+5,Inf=2147483647;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int n,head[maxn],tot,v[maxn],t[maxn],dp[maxn];
bool g[maxn];
struct node{
    int to,next;
}e[2*maxn];
void Add(int a,int b){
    e[tot].to=b;
    e[tot].next=head[a];
    head[a]=tot;
    tot++;
}
void dfs(int x,int fa){
    priority_queue<pair<int,int> > q;//按照dp值大小排序 
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;
        if(v==fa) continue;
        dfs(v,x);
        q.push(make_pair(dp[v],v));
    }
    int num=0,sum=0,judge=0;
    while(!q.empty()&&num<t[x]-1){
        if(q.top().first<0) break;//出现拖后腿的立即停止 
        if(q.top().first==0){//有0说明方案不为1，
        //且0后面要么是0要么是负的，都无法做贡献，直接退 
            judge=1;
            break;
        }
        sum+=q.top().first;
        if(g[q.top().second]==1) judge=1;
        q.pop();
        num++;
    }
    dp[x]=sum+v[x];
    g[x]=judge;
}
int main(){
    tot=1;
    t[1]=Inf;//注意自己家可以走无数次 
    n=read();
    for(int i=2;i<=n;i++) v[i]=read();
    for(int i=2;i<=n;i++) t[i]=read();
    for(int i=1;i<=n-1;i++){
        int x,y;
        x=read(); y=read();
        Add(x,y);
        Add(y,x);
    }
    dfs(1,0);
    printf("%d\n",dp[1]);
    if(g[1]) printf("solution is not unique");
    else printf("solution is unique");
    return 0;
}
```
幸甚至哉，歌以咏志。

---

## 作者：Great_Influence (赞：1)

容易注意到原图是棵树。

我们设 $w_u$ 表示 在 $u$ 停留的净收益， $d_u$ 表示能够在 $u$ 停留的最大次数， $dp_u$ 表示经过 $u$ 及其子树的最大收益，则

$dp_u=w_u+u$ 的几个儿子中收益最大的且收益非负的前 $d_u-1$ 个的收益之和

我们计算完 $u$ 的所有儿子的答案后将儿子按照收益从大到小排序取前面不超过 $d_u-1$ 个非负的即可。 这样完成了第一问。

第二问的多解情况只有两种可能:

1. 存在一种最优方案使得经过的某个点 $u$ 满足 $dp_u=0$ 。
2. 存在一种最优方案使得经过的某个点 $u$ 存在至少 $d_u$ 个儿子， 且第 $d_u$ 大收益非负的儿子不唯一。

我们只需要在 $dp$ 的过程中顺便记录是否存在这两种情况即可。

瓶颈在给儿子排序， 总时间复杂度 $O(n\log n)$ 。

代码:
```cpp
#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define pb push_back
typedef long long ll;
using namespace std;

const int MAXN = 1e5 + 7;

static int w[MAXN], d[MAXN], n;

vector <int> ed[MAXN];

inline void init()
{
   cin >> n;
	Rep(i, 2, n) cin >> w[i];
	Rep(i, 2, n) cin >> d[i], -- d[i];
	d[1] = n;
	static int u, v;
	Rep(i, 1, n - 1) cin >>u >> v, ed[u].pb(v), ed[v].pb(u);
}

static ll dp[MAXN];

static int nu[MAXN];

static int sn[MAXN];

inline bool cmp(int u, int v) {return dp[u] > dp[v];}

void dfs(int u, int fa)
{
	for(int v : ed[u]) if(v ^ fa) dfs(v, u);
	int e = 0; dp[u] = w[u];
	for(int v : ed[u]) if(v ^ fa) sn[++ e] = v;
	if(!e) return;
	sort(sn + 1, sn + e + 1, cmp);
	Rep(i, 1, min(e, d[u]))
	{
		if(i[sn][dp] > 0) dp[u] += i[sn][dp], nu[u] |= i[sn][nu];
		if(i[sn][dp] == 0) nu[u] = 1;
	}
	if(d[u] < e && u[d][sn][dp] > 0 && (d[u] + 1)[sn][dp] == u[d][sn][dp])
		nu[u] = 1;
}

inline void solve()
{
	dfs(1, 0);
	cout << dp[1] << endl;
	if(nu[1]) cout << "solution is not unique" << endl;
	else cout << "solution is unique" << endl;
}

int main()
{
	init();
	solve();
	return 0;
}
```

---

## 作者：lam_dyr (赞：0)

## 思路

注意到原图是一棵树（即任意两城镇之间有唯一路径），可以固定 $1$ 为根，选出的巡回方案必然对应一个以 $1$ 为根的连通子树。

对于除家乡外的每个城镇 $u$（利润为 $p_u$，允许停留次数为 $l_u$），如果被选中，则在最终巡回方案中，其停留次数恰好为该城镇在选中子树中的度数（因为从父亲处进入必定停留一次，而再到每个儿子处也需停留）。因此对与 $u（u≠1）$，其在子树中被用到的儿子个数最多为 $l_u-1$。

考虑树形 dp，令 $dp_u$ 表示强制选择 $u$ 时，从 $u$ 及其子树中能获得的最大收益（不重复计算），注意根节点 $1$ 的收益固定为 $0$。

对于 $u$ 的每个儿子 $v$，有两种选择：不选 $v$（收益为 $0$，决策唯一）或者选 $v$（收益为 $dp_v$，但仅当 $dp_v>0$ 时才会提高收益；同时若 $dp_v=0$，那么选或不选均可，决策不唯一）。

因为父节点 $u$ 对于选取儿子存在个数限制 $lim=$（若 $u≠1$ 则为 $l_u-1$，若 $u=1$ 则无限制），转移时的最佳决策就是从所有儿子 $v$ 中选出贡献为正的 $dp_v$ 的最大者；但如果候选集太多且恰好出现相等情况，或者某个儿子本身的选择不唯一（dp 值为 $0$），那么整个方案就不唯一。

由于树形 dp 是自底而上转移的，所以最后答案就是 $dp_1$（如果 $dp_1<0$，说明巡回取消，收益为 $0$）。同时在过程中判断整个方案是否唯一。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
int n,ans;
int p[N],l[N];
vector<int> g[N];
struct note{
	int val;
	bool unique;
}dp[N];
bool cmp(pair<int,bool> a,pair<int,bool> b){
	return a.first>b.first;
}
void dfs(int u,int fa){
	int x=(u==1 ? 0 : p[u]);
	int y=(u==1 ? 1e9 : l[u]-1);
	dp[u]={x,1};
	vector<pair<int,bool>> ve;
	bool flag=0;
	for(auto v: g[u]){
		if(v==fa) continue;
		dfs(v,u);
		if(dp[v].val>0) ve.push_back({dp[v].val,dp[v].unique});
		else if(dp[v].val==0) flag=1;
	}
	sort(ve.begin(),ve.end(),cmp);
	int sz=ve.size();
	int lim=min(y,sz);
	ll sum=0;
	bool f=1;
	for(int i=0;i<lim;++i){
		sum+=ve[i].first;
		if(!ve[i].second)
			f=0;
	}
	if(lim<sz && lim>0){
		if(ve[lim-1].first==ve[lim].first)
			f=0;
	}
	if(flag) f=0;
	dp[u].val=x+sum;
	dp[u].unique=f;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=2;i<=n;++i)
		cin>>p[i];
	for(int i=2;i<=n;++i)
		cin>>l[i];
	for(int i=1;i<n;++i){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	ans=dp[1].val;
	if(ans<0) ans=0;
	cout<<ans<<"\n";
	cout<<(dp[1].unique ? "solution is unique" : "solution is not unique");
	return 0;
}
```

---

