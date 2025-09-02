# [POI 2017] Sabotaż

## 题目描述

某个公司有 $n$ 个人，上下级关系构成了一个有根树。其中有个人是叛徒（这个人不知道是谁）。

对于一个人，如果他下属（直接或者间接，不包括他自己）中叛徒占的比例超过 $x$，那么这个人也会变成叛徒，并且他的所有下属都会变成叛徒。你要求出一个最小的 $x$，使得最坏情况下，叛徒的个数不会超过 $k$。

## 说明/提示

#### 样例解释
答案中的 $x$ 实际上是一个无限趋近于 $\frac{2}{3}$ 但是大于 $\frac{2}{3}$ 的数。 

因为当 $x$ 取 $\frac{2}{3}$ 时，最坏情况下 $3,7,8,9$ 都是叛徒，超过了 $k=3$。
#### 数据范围
对于 $100\%$ 的数据，$1\le k\le n\le 500000$，$1\le p_{i+1}\le i$。

## 样例 #1

### 输入

```
9 3
1
1
2
2
2
3
7
3```

### 输出

```
0.6666666667```

# 题解

## 作者：_LPF_ (赞：18)

**本题解已经通过了，这次是勘误，去掉了反作弊，望管理员通过。**

**感谢 @void_basic_learner dalao 指出的错误。**
# 树形DP入门题

## 题意描述
在一棵以1号节点为根节点的树上，有很多~~纯洁的~~白点，

BUT，突然有一个黑点出现（可能在任意位置）

它要染黑尽可能多的节点，而在一棵子树中，

只有当黑点的比例$>x$才可以染黑根节点（即整棵子树）

求x的最小值，使得整棵树中被染黑的节点数不超过$k$个

如果你看不懂请走[传送门](https://www.luogu.com.cn/problem/P5958)

## 算法分析
一道很裸的树形DP，但思路很巧

显然本题有以下性质：
 1. **最坏情况下，最开始的叛徒是叶子结点**
 2. **因为一个节点被染黑了，一起为根节点的子树将全黑，所以最终被染黑的一定是一颗子树**

先设计状态：**$f(i)$表示使得$i$不变黑的最小$x$**

易得：**$f(i)$也是使得$i$变黑的最大$x$**

可知$f(i)$仅与$f(son{i})$以及$soni$的大小有关（这里的$soni$表示$i$的子节点）

那么我们用$sum(i)$表示**以$i$为根节点的子树的大小**,$sum(i)$是需要提前用dfs预处理的

显然$i$被染黑仅必须满足以下两种情况：

 1. **$f(soni) > x$,即$i$的某棵子树被染黑**
 2. **$sum(soni)/(sum(i)-1) > x$,即$soni$的被染黑足以导致$i$的被染黑**
 
根据以上规律可以推出如下方程：

$f(i)=max(f(i),min(f(soni),sum(soni)/(sum(i)-1)))$~~(不会用LaTeX写公式的蒟蒻瑟瑟发抖)~~

取$min$是因为需要同时满足条件1和条件2，
取$max$是因为需要答案最优

~~（貌似貌似到这里就结束了呢）~~

其实还有以下三点细节需要注意：

1. **对于叶子结点$a$，显然有$f(a)=1$**
2. **对于$ans$当$sum(a)<k$时是不需要考虑的，因为它合法，所以即使它被染黑也无所谓**
3. **针对上一条结论，易得$ans=max(ans,f(a))$,其中$sum(a)>=k$**

然后就去快乐$AC$吧......

## 代码实现

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#define maxn 500050
using namespace std;

int n,k,sum[maxn];
double f[maxn],ans;
vector<int>v[maxn];//用vector存图笑哈哈

void dfs(int now,int fa){
    sum[now]=1;
    for(int i=0;i<v[now].size();i++){
        int to=v[now][i];
        dfs(to,now);
        sum[now]+=sum[to];
    }//dfs预处理sum[]
    if(sum[now]==1){f[now]=1.0;return;}//叶子结点的处理
    for(int i=0;i<v[now].size();i++){
        int to=v[now][i];
        f[now]=max(f[now],min(f[to],(double)sum[to]/(sum[now]-1)));
    }//dp
    if(sum[now]>k) ans=max(ans,f[now]);//统计答案，注意if
    return;
}

int main(){
    scanf("%d %d",&n,&k);
    int x;
    for(int i=2;i<=n;i++){
        scanf("%d",&x);
        v[x].push_back(i);
    }
    dfs(1,0);
    printf("%.8lf",ans);//注意精度问题
    return 0;
}
```

## 结语
安利[my blog](https://www.cnblogs.com/lpf-666/)
（光速逃...

---

## 作者：漠寒 (赞：5)

### 题意分析

最坏情况一定是这个叛徒是叶子结点，这样他才有更大的概率来影响他的上级，比如你使一个子树都变为叛徒，肯定比仅有这个子树的根节点是叛徒影响力更大。

叛徒集体一定是一棵子树，因此我们选用深搜，递归来树形 $DP$ ，以此维护相关信息。

$f_i$ 表示 $i$ 不是叛徒的最小 $x$ ， $s_i$ 表示子树的大小。

对于叶子结点，它的 $f$ 显而易见应为1，因此可以初始化所有的 $f$ 为1。

对于每个节点，枚举它的子节点，若要满足以该节点为根的子树不整体受影响，它需要同时满足以下任一条件，满足儿子不受影响，满足儿子为根的子树大小占比不对自己产生影响。

转移式。

```cpp
f[u]=max(f[u],min(f[v],(double)s[v]/(s[u]-1)));
```

处理完每个节点后，如果它的子树大小大于限制的 $k$ ，我们就需要将它的 $f$ 纳入考虑范围之内，以它更新 $ans$。

最后输出即可，考虑精度，输出八位小数。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int s[500005],n,k,head[500005],tot;
double f[500005],ans;
struct node{
	int to,next;
}a[500005];
void dfs(int u,int fr){
	s[u]=1;
	for(int i=head[u];i;i=a[i].next){
		int v=a[i].to;
		if(v==fr)continue;
		dfs(v,u);
		s[u]+=s[v];
	}
	for(int i=head[u];i;i=a[i].next){
		int v=a[i].to;
		if(v==fr)continue;
		f[u]=max(f[u],min(f[v],(double)s[v]/(s[u]-1)));
		if(f[u]==1)f[u]=min(f[v],(double)s[v]/(s[u]-1));//特判，否则答案恒为1 
	}
	if(s[u]>k)ans=max(ans,f[u]);//更新 
} 
int main()
{
	cin>>n>>k;
	for(int i=2;i<=n;i++){
		int x;
		cin>>x;
		a[++tot].to=i;
		a[tot].next=head[x];
		head[x]=tot;
	}
	for(int i=1;i<=n;i++)f[i]=1;
	dfs(1,0);
	printf("%.8lf",ans);
}

```


---

## 作者：字如其人 (赞：3)

很好的树形 $dp$ 入门题。

令 $f[i]$ 为在最坏情况下，使得节点 $i$ 作为一个子树的根能被更新成叛徒（$fa[i]$ 此时未被更新）所需得最大 $x$（注意，这里的     $x<=f[i]$ ,可以取等） ，既最大的 $f[i]$ 。（所以在更新 $f[i]$ 时，应该取 $max$ ）

显然，当 $f[i]$ 被更新后，当 $x<=f[i]$ 时，$i$ 为根的子树都成了叛徒 ,此时如果 $size[i]>k$ ，那么意味着 $x<=f[i]$ 时存在一种情况使叛徒个数超过 $k$ 。更新 $ans$ 。
```cpp
if(siz[x]>k)ans=max(ans,f[x]);
```

现在的问题是如何更新 $f[i]$ 。

考虑对于当前节点 $x$ ,有一个儿子 $y$ ,那么通过 $y$ 为根的子树将叛徒传给 $x$ 需要满足两个条件。

1、最坏情况下， $y$ 能被更新。

2、$x$ 能被 $y$ 更新。

对应的是：

1、$x<=f[y]$  

2、$x<=size[y]/(size[x]-1)$ 

既 $x<=min(f[y],size[y]/(size[x]-1))$

对于 $x$ 的每一个子节点 $y$ ，我们要找到最坏的情况，所以要整体取 $max$ 。（开头有说）。
```cpp
f[x]=max(f[x],min((double)siz[y]/(siz[x]-1),f[y]));
```
这就把求 $f[x]$ 变成了求 $f[y]$，那么递归到叶子节点时,$f$[叶子节点]=1。

原因:叶子节点的子树只有一个节点，只能最开始是叛徒才能作为根节点被更新，所以只有$x>=1$ 时成立。

那么这道题就解决了。

核心代码：
```cpp
void dfs(int x){
	siz[x]=1;
	if(!son[x].size()){f[x]=1;return;}
	for(int i=0;i<son[x].size();i++){
		int y=son[x][i];
		dfs(y);
		siz[x]+=siz[y];
	}
	for(int i=0;i<son[x].size();i++){
		int y=son[x][i];
		f[x]=max(f[x],min((double)siz[y]/(siz[x]-1),f[y]));
	} 
	if(siz[x]>k)ans=max(ans,f[x]);
}
```


---

## 作者：NXYorz (赞：3)

# 首先本蒟蒻要表达深深的歉意

因为本蒟蒻，这道题的AC率不再是百分之百。

# 现在进入正题

这道题可以**DP**来做，我们考虑一个数组f[ i ]表示**使这个节点叛变的最大值，同时也是使这个节点不叛变的最小值。**
也就是说如果我们的x大于了这个值，那么这个节点就不叛变，反之，就叛变。

然后我们可以得到状态转移方程：

**f[ i ] = max ( f[ i ], min ( f[ j ], size[ j ] / size[ i ] ) );**

这里先解释一下变量和数组的关系： **i** 是当前我们正在遍历的节点，**j** 是它的子节点。

**这个方程是怎么得到的呢**

首先我们来看 ```min ( f[ j ], size[ j ] / size[ i ] )``` 这里，我们知道，如果要计算这个节点在父节点中的比列时我们一定是默认它已经叛变了，否则就没有任何意义。因此要是二者都满足我们就要取小的。

然后我们与当前的最优值比较，如果可以更新最大值，我们就更新一下。

但是我们紧紧是维护了一颗树，并没有得到最终的答案。因此在我们每往回递归的时候，我们就判断一下，是否**当前节点的大小**已经大于了K，如果是的话，我们就要比较一下**当前答案**与我们**所维护的这个节点**的**最大值**。因为如果大于了K，这个节点就一定不能叛变，所以我们就希望最终答案要大于所有**节点大小**大于k的**节点**所维护的f [ ]。

【code】
```
#include<iostream>
#include<cstdio>
#include<vector>
#define N 500001
using namespace std;
int n,k;
int size[N];
double ans,f[N];
vector<int> son[N];
int dfs(int x)
{
	for(int i=0;i<son[x].size();i++)
		size[x]+=dfs(son[x][i]);
	if(size[x]==0) {size[x]+=1;f[x]=1;return 1;}
	for(int i=0;i<son[x].size();i++)
		f[x]=max(f[x],min(f[son[x][i]],(double)size[son[x][i]]/size[x]));
	size[x]+=1;
	if(size[x]>k) ans=max(ans,f[x]);
	return size[x];
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int fa;scanf("%d",&fa);
		son[fa].push_back(i+1);
	}
	dfs(1);
	printf("%.10lf",ans);return 0;
}
```

---

## 作者：Vanilla_0 (赞：2)

这是一道经典的树形DP，很适合用来锻炼思路。
# 思路
首先是构造数组，设 $f[i]$ 表示 $i$ 不是叛徒能取到的最小 $x$ （或者 $i$ 是叛徒能取到的最大 $x$ ）,设 $sz[i]$ 表示子树的大小。
### 推论
1. 一个节点是叛徒，当且仅当它的所有子树都变成了叛徒。
2. 当一个节点被更新为叛徒时，满足 $x<=f[i]$ ，而如果满足 $sz[i]>k$ ,说明此时的 $x$ 偏小，更新 $x$。
3. 最坏情况考虑那个人是叶子节点。
### 方程推导
要使一个节点 $p$ 被更新，那么就要满足它的一个儿子 $t$ 能被更新且它能被它的这个儿子所更新，即满足：
1. $x<=f[t]$
2. $x<=sz[p]/(sz[t]-1)$

因此只需要比它们之中最小的还要小就行了。

因为我们要找到满足条件的最大 $f[p]$ ，所以要取 $max$ 。
### 注意事项
1. 初始化时要设叶子节点的 $f$ 为1，表示只有 $x>1$ 时才满足不让它的父亲变为叛徒。
2. 也可以用 $STL$ ,码量会少一点。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,k;
struct node{
	int to,next;
} a[N<<2];
int head[N],tot=0,sz[N];
double ans,f[N];
void add(int x,int y)
{
	a[++tot].to=y;
	a[tot].next=head[x];
	head[x]=tot;
}
void dfs(int rt)
{
	sz[rt]=1;//初始化 
	for(int i=head[rt];i;i=a[i].next)
	{
		int v=a[i].to;
		dfs(v);//递归处理，统计子树大小 
		sz[rt]+=sz[v];
	}
	if(sz[rt]==1){f[rt]=1;return;}//对叶子节点的特殊处理 
	for(int i=head[rt];i;i=a[i].next)
	{
		int v=a[i].to;
		f[rt]=max(f[rt],min((double)sz[v]/(sz[rt]-1),f[v])); 
	}
	if(sz[rt]>k) ans=max(ans,f[rt]);//统计答案 
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=2,p;i<=n;i++)
	{
		scanf("%d",&p);
		add(p,i);//注意存边的方向 
	}
	dfs(1);//从根开始递归 
	printf("%.8lf",ans);
	return 0;
} 
```


---

## 作者：CYZZ (赞：1)

# [P5958 Sabotaż](https://www.luogu.com.cn/problem/P5958)
这是一道很好的入门**树形 DP**。
# 题意简明
给你一颗节点数为 $n$ 的有根树，有一个节点已经被染黑（不知道是哪一个）。若以节点 $i$ 为根的子树中黑色点的比例超过 $x$，则 $i$ 会被染黑，以 $i$ 为根的整棵子树也会被染黑（起始点除外）。求最坏情况下 $x$ 的最小值。
# 思路分析
先给几个简单结论（可以自行证明）：

- 最终染黑的叛徒集体一定是**一整颗子树**。
- **最坏情况**叛徒一定处于**叶子节点**。
- 使一个节点叛变的最大值，也是使这个节点**不叛变**的**最小值**。

然后就可以开始愉快地推状态转移方程了：

设 $dp_i$ 表示使节点 $i$ 叛变的 $x$ 的最小值，且 $dp_i$ 仅与以 $i$ 为根的子树有关。即 $i$ 被染黑时，当且仅当以 **$i$ 的子孙 $j$ 为根的子树已被染黑**且**足以导致 $i$ 被染黑**。分别对应两个条件：

- $dp_i \le dp_j$
- $dp_i \le size_i/(size_j-1)$

因为两个条件都要满足，所以要取 $\max$。

这样我们就得出了方程：
$$dp_i=\max(dp_i,\min(size_i/(size_j-1)))$$

最后在预处理时注意两点即可：

- $size$ 数组在转移之前先预处理好。
- 对于叶子节点 $i$，显然有 $dp_i=1$。
- 取 $size$ 值大于 $k$ 的 $dp_i$ 更新答案，因为大小小于 $k$ 的子树染不染黑都无所谓。

# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,head[500005],tot,siz[500005];
double ans,dp[500005];
struct edge
{
	int next,to;
}e[1000005];
void add_edge(int u,int v)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	head[u]=tot;
}
void dfs(int u,int fa)
{
	siz[u]=1;
	for(int i=head[u];i;i=e[i].next)
	{
		dfs(e[i].to,u);
		siz[u]+=siz[e[i].to];
	}//预处理size
	if(siz[u]==1)
	{
		dp[u]=1;
		return ;
	}//初始值 
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		dp[u]=max(dp[u],min(dp[v],1.0*siz[v]/(siz[u]-1)));//重点 
	}
	if(siz[u]>k)
		ans=max(ans,dp[u]);//更新答案 
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=2;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add_edge(x,i);
	}
	dfs(1,0);
	printf("%.10lf",ans);
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：神眷之樱花 (赞：1)

# 题意
在一棵树上，最开始只有一个叛徒，而当某棵子树中叛徒的比例（计算比例时，分母不包括这颗子树的根节点）超过 $x$ 时，这棵子树中所有的点都会变成叛徒，求一个最小的 $x$，使最终这颗树上叛徒的个数不超过 $k$。
# 解析
了解过树形DP的同学应该读完题就能想到用树形DP吧。但是做的时候对于我这种蒟蒻也并不容易。


------------
### 定义
我们设 $dp[i]$ 表示节点 $i$ 不为叛徒时的最小$x$，$siz[i]$ 表示以节点 $i$为根的子树大小。
### 引理
* 最坏的时候，叛徒一定为叶子节点。
* 一个本不是叛徒的节点变成了叛徒，那么以它为根的子树一定都变成了叛徒。
* 叛徒集体一定是**一棵**子树。
### 初始化
当 $i$ 是叶子节点时，因为每个叶子节点都有可能是叛徒，所以 $dp[i]$ 应该是1，表示只有叛徒比例超过 $1$ 时才行。
### 状态转移方程
```cpp
for(int i = 0; i < son[now].size(); i++)
	dp[now] = max(dp[now],min(dp[son[now][i]],1.0 * siz[son[now][i]] / (siz[now] - 1)));
```
根据引理二和引理三
我们可以得到以当前节点为根的子树中叛徒的比例：
```cpp
1.0 * siz[son[now][i]] / (siz[now] - 1)
```
取 $min$ 是为了满足 $x$ 最小的条件。因为在两者中我们只需要满足最小的那个即可。

取 $max$ 是因为了满足我们 $dp[i]$ 的定义，也就是说转移之后，当前节点是不能变为叛徒的，所以要取二者之中的最大值。
# 代码
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

const int N = 5e5 + 5;
int n,k,siz[N];
double dp[N],ans = 0;
vector<int> son[N];
void dfs(int now){
	siz[now] = 1;
	for(int i = 0; i < son[now].size(); i++) {
		dfs(son[now][i]);
		siz[now] += siz[son[now][i]];
	}
	if(siz[now] == 1) {
		dp[now] = 1.0;
		return;
	}
	for(int i = 0; i < son[now].size(); i++)
		dp[now] = max(dp[now],min(dp[son[now][i]],1.0 * siz[son[now][i]] / (siz[now] - 1)));
	if(siz[now] > k) ans = max(ans,dp[now]);
}
int main() {
	scanf("%d%d",&n,&k);
	for(int i = 2,u; i <= n; i++) {
		scanf("%d",&u);
		son[u].push_back(i);
	}
	dfs(1);
	printf("%.8lf",ans);
	return 0;
}
```


---

## 作者：Planetary_system (赞：0)

## 题面解释：
如果一颗子树（不计根节点）中黑点比例超过 $x$，整颗子树变成黑的。求出使黑点不超过 $k$ 个时 $x$ 的最小值。

## 思路分析：
先找黑色传递的性质。首先，黑色只能从下往上传。若非叶子节点为初始黑点时能使子树变黑，那么为叶子节点一定也可以。因为同样有 $1$ 个黑点，在更小的子树中占比只会更大。同时，如果一颗黑的子树能使一颗祖先子树全部变黑，那么他一定可以使更小的祖先子树变黑。也就是说，如果当前子树已经无法被变黑，此子树的祖先子树一定不会变黑。故而黑色只需一层一层往上传即可。

根据性质套路性地考虑`树形dp`。

依据题面设计状态为 $dp_i$ 表示能使以 $i$ 为根的子树全黑的 $x$ 的最大值(需超过 $x$ 所以取不到)，同时就是使以 $i$ 为根的子树不变黑的最小 $x$（可取到）。那么当 $k<sz_i$ ( $sz_i$ 以 $i$ 为根的子树的大小) 时，需满足 $dp_i\le x$。即为最终的答案是所有大小超过 $k$ 的子树根节点 $dp$ 值中的最大值。

然后思考转移。根据上文，以 $j$ 为根的子树使以 $i$ 为根的子树变黑首先以 $j$ 为根的子树是全黑的，故而此时 $x<dp_j$。同时，需要以 $j$ 为根的子树的大小（包括 $j$）在以 $i$ 为根的子树大小（不包括 $i$）中占比 $>x$。那么需要在这两者中取更小值，即为 $j$ 往上传递的情况下 $dp_i$ 的上界。然后所有子树中取最大的一个，那么就可以保证无论如何都当前子树不变黑。
## AC Code:
码量很小，不知道为何会有什么奇奇怪怪的错误。还有问题的话直接看代码也很好理解。

说细节的话就是超过不超过对应不等式能否取等，上述文章和代码中都有清晰体现这一点。

防止直接`copy`刷通过数只放核心部分。
```cpp
void dfs(int u){
	dp[u]=g[u].empty();
	for(int v:g[u])dfs(v),sz[u]+=sz[v];
	for(int v:g[u])dp[u]=max(dp[u],min(sz[v]*1.0/sz[u],dp[v]));
	if(++sz[u]>k)ans=max(ans,dp[u]);
	return;
}
```
完结撒花！！！

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

一眼题。

我们不难注意到一个性质：一个上司叛变了一定不如一个叶子节点叛变了。

为什么呢？首先，如果一个非叶子节点，他确实有可能通过足够小的 $x$ 一步步晋级到上面。但是，对比其子树内的一个叶子节点，这个非叶子节点的所有子节点都是空白的，而这个叶子节点因为拥有恒比非叶子节点更小比例的空白节点，因此对于同样的 $x$，非叶子节点能做到的，叶子节点也一定能过做到。

第一个性质出来了，题就已经不难了。再看第二个性质：叛变的部分在最优的情况下，一定是一个子树内的所有节点。

这点不难证，说白了就是不可能跨级叛变，证明和上面基本一样。

那么，你要干的就是统计以每一个节点为根的子树全部叛变所需要的最小 $x$，然后只统计字数大小大于 $k$ 的子树的 $x_{\max}$。

转移的时候，对于一个节点 $p$ 和它的子节点 $sp$，最小 $x$ 就是 $\min(sz_{sp}/sz_p-1,x_{sp})$，同一节点取子树中的 $x$ 的 $\max$。其中 $sz_p$ 表示以 $p$ 为根节点的子树的大小。

因为这一题要求 $x$ 误差不超过 $10^{-6}$，于是我们直接输出统计出来的答案，误差一定不超过 $10^{-6}$。大喜！

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif
inline int read() {
	int r = 0; char c = getchar_unlocked();
	while (c < '0' || c>'9') c = getchar_unlocked();
	while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = getchar_unlocked();
	return r;
}
inline void write(long long x) {
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 ^ 48);
}
inline void writi(long long args) {
	write(args); putchar_unlocked(10);
}
using ld = long double;
constexpr bool online = 0;
int n, m, f[500005], sz[500005];
ld nd[500005], ans;
vector<int>son[500005];
inline void dsz(int p) {
	sz[p] = 1;
	for (int sp : son[p])
		dsz(sp), sz[p] += sz[sp];
}
inline void dnd(int p) {
	if (!son[p].size()) {
		nd[p] = 1; return;
	}
	for (int sp : son[p]) {
		dnd(sp);
		ld val = (ld)sz[sp] / (sz[p] - 1);
		ld acn = min(val, nd[sp]);
		nd[p] = max(nd[p], acn);
	}
	if (sz[p] > m) ans = max(ans, nd[p]);
}
signed main() {
	if (online)
		freopen("Sabota.in", "r", stdin),
		freopen("Sabota.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 2;i <= n;++i)
		cin >> f[i], son[f[i]].emplace_back(i);
	dsz(1); dnd(1);
	printf("%.10Lf", ans);
	return 0;
}
//私は猫です
//9:45 passed big exam
```

---

## 作者：MoonCake2011 (赞：0)

~~话说所有人是叛徒那不就都不是叛徒了吗？~~

这边难度虚高。

这边发现答案具有单调性，直接二分答案 $x$。

接着尝试树形 dp 统计。

设 $dp_i$ 为节点 $i$ 子树内叛徒最多的情况。

初值为 $dp_i=1$，表示自已为叛徒。

接着枚举子树，如果儿子 $j$ 的 $\dfrac{dp_j}{siz_i-1} > x$，我们可以将 $dp_i$ 赋值为 $siz_i$。

否则，更新 $dp_i=\max dp_j$。

那就推上去就完了。

代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
// #define double long double
#define eps 1e-7
int n,k;
int head[500010],to[500010],nxt[500010],tot;
inline void add(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot; 
}
int dp[500010],siz[500010];
void dfs(int x,double p){
	siz[x]=dp[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		dfs(to[i],p);
		siz[x]+=siz[to[i]];
	}
	for(int i=head[x];i;i=nxt[i]){
		if((double)(dp[to[i]])/(siz[x]-1)>p) dp[x]=siz[x];else dp[x]=max(dp[x],dp[to[i]]);
	}
}
inline bool check(double x){
	dfs(1,x);
	return dp[1]<=k;
}
signed main() {
//	freopen("Sabota.in","r",stdin);
//	freopen("Sabota.out","w",stdout);
	cin>>n>>k;
	for(int i=2;i<=n;i++){
		int f;
		cin>>f;
		add(f,i);
	}
	double l=0,r=1,mid=0;
	while(r-l>eps)
		if(check(mid=(l+r)/2)) r=mid;
		else l=mid;
	printf("%.7f",l);
	return 0;
}
```

---

## 作者：EllinY (赞：0)

# 题意
公司里有一个叛徒，任何人都可能是那个叛徒。叛徒具有传染性，如果一个人的直接下属和间接下属中叛徒的比例大于等于 $x$，那么这个人和他所有的下属都会变成叛徒。在保证叛徒总数不超过 $k$ 的同时，求 $x$ 的最小值。
# 思路
$x$ 越大，传染的难度越高，叛徒也就越少；相应地，$x$ 越小，叛徒越多。所以当某个 $x$ 只会使得小于等于 $k$ 个人成为叛徒，而 $x-0.00000\dots01$ 会使超过 $k$ 个人变成叛徒，此时就找到了最小的 $x$。那么我们可以寻找最大的 $x$ 使得超过 $k$ 个人变成叛徒，最后的答案就是 $x+0.0000\dots01$。$\\$ 先对传染的方式进行分析。首先，一开始只有一个叛徒。其次，在任何状态下，被传染的一定是某个子树中所有的节点。因为如果某个节点被传染了，那么它子树中的所有点都会被传染。其实还有一个隐藏前提，感染源可以默认一定在叶子节点，如果是从某个非叶子开始传递，不能感染它的下属，这样使得感染人数减少，无法对答案产生贡献（要找到感染人数超过 $k$ 的 $x$ 上限，这里找到的 $x$ 会比叶子节点作为感染源的 $x$ 小）。$\\$ 可以设计 dp，$dp_{i}$ 表示使 $i$ 为根的子树中所有点都被感染的最大的 $x$（再大就无法全部感染）。转移方程：$dp_i=\max\{\min(dp_j,\frac{sz_j}{sz_i-1})\}(j\in son_i)$，其中 $sz_i$ 表示以 $i$ 为根的子树的大小。首先 $x$ 得要能让 $j$ 为根的子树全部感染，然后 $x$ 得不超过 $\frac{sz_j}{sz_i-1}$，使 $j$ 为根的子树中的节点数足够（占比够高）感染以 $i$ 为根的子树，减 $1$ 是因为 $i$ 的下属不包括 $i$ 节点本身。外面取 $\max$ 是因为只要有一个儿子在某个 $x$ 的情况下可以把 $i$ 为根的子树感染，这个 $x$ 就成立，而且 dp 也是要求最大值。因为只有一个感染源，所以不可能出现某个节点的两个儿子所在的子树都已被感染而这个节点还没被感染的情况。$\\$ 初始状态是这个节点（叶子节点）是感染源，无论 $x$ 多高都不影响它被感染，所以 $dp_i=1$。最后的答案就是 $\max{dp_i}+0.0000000001$（$i$ 是一个 $sz_i>k$ 的节点；真实的答案是一个 $>\max{dp_i}$ 但无限接近这个数的，精度要求是 $10^{-6}$ 所以加上 $10^{-10}$ 完全可以）。
# 代码
这里的精度要用`printf("%.10lf\n",ans);`，否则会自动输出 $6$ 位小数并四舍五入。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,p;
vector<int> go[500005];
double dp[500005],ans,sz[500005];
void dfs(int ps){
	sz[ps]=1;
	for(auto g:go[ps]){
		dfs(g);
		sz[ps]=sz[ps]+sz[g];
	}
}
void dynamic(int ps){
	if(go[ps].size()==0) dp[ps]=1;
	for(auto g:go[ps]){
		dynamic(g);
		dp[ps]=max(dp[ps],min(dp[g],(double)sz[g]/(sz[ps]-1)));
//		cout<<ps<<' '<<g<<':'<<dp[ps]<<endl;
	}
}
int main(){
	cin>>n>>k;
	for(int i=2;i<=n;i++){
		cin>>p;
		go[p].push_back(i);
	}
	dfs(1);
	dynamic(1);
	for(int i=1;i<=n;i++)
		if(sz[i]>k)
			ans=max(ans,dp[i]);
	ans+=0.0000000001;
	printf("%.10lf\n",ans);
	return 0;
}
```
Thanks for reading.

---

## 作者：run_away (赞：0)

## 题意

给定一棵大小为 $n$ 的树，树上有一个未知节点被染色。对于任意一个节点，若它的子树中被染色的比例超过实数 $x$，则它也被染色。给定整数 $k$，求出最小的 $x$，使得被染色节点最多不超过 $k$ 个。

## 分析

比较明显的树形 DP，可以在 DFS 里面求出每个节点的子树大小 $siz$。

设 $f_i$ 表示第 $i$ 个节点的子树内最小的 $x$。

所以第 $u$ 个节点被染色，当且仅当存在被染色的孩子节点 $v$，使得 $f_v>f_u$（当前节点的 $x$ 小于孩子节点）；或 $siz_v\div(siz_u-1)>f_u$（孩子结点的子树大小已经可以让当前节点染色）。

可得状态转移方程为 $f_u=\max(f_u,\min(f_v,siz_v\div(siz_u-1)))$。

整个过程在 DFS 里实现，每个节点最多被遍历到一次，总时间复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll maxn=5e5+5;
ll n,k,siz[maxn];
vector<ll>son[maxn];
double ans,f[maxn];
inline void dfs(ll u,ll pre){
    siz[u]=1;
    for(auto v:son[u]){
        if(v==pre)continue;
        dfs(v,u);
        siz[u]+=siz[v];
    }
    if(siz[u]==1){f[u]=1;return;}
    for(auto v:son[u]){
        if(v==pre)continue;
        f[u]=max(f[u],min(f[v],siz[v]*1.0/(siz[u]-1)));
    }
    if(siz[u]>k)ans=max(ans,f[u]);
}
signed main(){
    n=read(),k=read();
    for(ll i=2;i<=n;++i){
        ll u=read();
        son[u].push_back(i);
    }
    dfs(1,0);
    printf("%.8lf",ans);
    return 0;
}
```

---

## 作者：Cloxier (赞：0)

观察题面，其实我们很容易就能得到以下结论：

既然以某个节点为根的子树中的所有节点都为下属，那么显然，最坏情况下，第一个叛徒一定是叶子，最终叛徒一定是一棵子树。

知道了这点，我们就可以开始树形 DP：

令 $f(x)$ 表示使节点 $x$ 不变为叛徒的最小$v$，那么 $f(x)$ 自然也是使节点 $x$ 变为叛徒的最大 $v$ ；同时我们枚举节点 $x$ 的所有**叛变子树**，并用 $size_x$ 表示 $x$ 的子树大小。

让一个父节点连同所有儿子节点叛变，需要满足子树中叛徒的占比大于 $v$，且子树大小在父节点大小中占比超过 $v$ ，既然我们想找到让父节点叛变最小的 $v$，取最小值即可。同时我们需要寻找最坏情况，那么就需要在集合 $son_x$ 中枚举 $y$ ，遍历集合找到最大值。那么状态转移方程如下：

$f(x) = {max}(y∈son_x(min(f(y), \frac{size_y}{size_x - 1})))$

我们已经解决了最关键的问题，接下来我们只需要从根节点开始进行递归搜索完成树形 DP 的全过程即可。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int n, k;

struct Edge
{
    int to, nxt;
}edge[N];
int head[N], cnt;
int siz[N];
double f[N];
double ans = 0;//需要注意，这里不能赋值为负数，否则无法通过答案为0的情况

void addEdge(int u, int v)
{
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
    return;
}

void dfs(int x, int fa)
{
    siz[x] = 1;
    for(int i = head[x]; i; i = edge[i].nxt)
    {
        if(edge[i].to == fa)
        {
            return;
        }
        dfs(edge[i].to, x);
        siz[x] += siz[edge[i].to];
    }
    //遍历子树
    if(siz[x] == 1)
    {
        f[x] = 1.0;
        return;
        //叶子节点直接赋值1
    }
    for(int i = head[x]; i; i = edge[i].nxt)
    {
        f[x] = max(f[x], min(f[edge[i].to], (double)siz[edge[i].to] / (siz[x] - 1)));
    }
    if(siz[x] > k)
    {
        ans = max(ans, f[x]);
    }
    //进行转移与答案更新
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    int tmp;
    for(int i = 2; i <= n; i++)
    {
        cin >> tmp;
        addEdge(tmp, i);
    }
    //注意1为树根，建边要从2开始
    dfs(1, 0);
    cout << fixed << setprecision(7) << ans;
    return 0;
}
```


---

## 作者：Computer1828 (赞：0)

#### 本题正解算法：树形DP


------------

### 思路1

看到这道题的时候，我的第一反应是二分答案。

设左端点 $l = 0$ ，右端点 $r = 1$ 。

定义一个函数 $check(x)$ ，判断答案为 $x$ 的时候，在最坏情况下，叛变的人数是否超过 $k$ 。

找规律得：在最坏情况下，题目中规定的已经叛变的人应该是在叶子结点上。

所以我们在check的时候遍历每个叶子结点，假设它已经叛变，然后判断它上一级祖先会不会叛变，如果会，加上子树大小并继续向上dfs；否则判断是否大于k

如果 $check(mid) == true$ 的时候，则 $l = mid+1^{-7}$ 。

否则 $r = mid$ 。

考虑时间复杂度，二分的时间是个常数，check的时候复杂度大概是 $n*logn$ ，极容易TLE。~~我懒得去试 读者自行尝试~~

### 思路2

我看到这是一棵树，所以就想到树形DP。

我们设 $si[i]$ 表示节点 $i$ 的子树大小。

我们设 $f[i]$ 表示节点 $i$ 不叛变的最小 $x$ 。

找规律得 $f[i]$ 也表示节点 $i$ 叛变的最大 $x$ 。

![](https://cdn.luogu.com.cn/upload/image_hosting/7dq3q45a.png)

为了使节点 $i$ 能叛变，我们必须得满足两个条件：

1. 它有至少一棵子树叛变，即 $f[j] \leq x$ 。
2. $\frac {si[j]} {si[i]-1} \leq x$ ，其中 $si[j]$ 表示 $i$ 的子节点 $j$ 的子树大小。

再由于我们要的是在最坏情况下的答案，所以我们要对 $f[i]$ 取 $max$ 。

综上所述，可得DP方程：

$f[i] = max(f[i],min(f[j],\frac {si[j]} {si[i]-1}))$

边界条件，即叶子结点 $f[i] = 1$ 。

当且仅当 $si[i] > k$ 的时候我们才更新答案。

```cpp
#include<stdio.h>
using namespace std;
int n,k;
struct edge{
	int to,nxt;
}e[500005];

int hed[500005],cnt;
inline void add(int u,int v){
	e[++cnt].to = v;
	e[cnt].nxt = hed[u];
	hed[u] = cnt;
}

inline double max(double x,double y){
	return x>y?x:y;
}

inline double min(double x,double y){
	return x<y?x:y;
}

int si[500005];
inline void dfs(int u){
	si[u] = 1;
	for(int i = hed[u];i;i = e[i].nxt){
		int v = e[i].to;
		dfs(v);
		si[u] += si[v];
	}
}

double f[500005];

inline void dfs2(int u){
	for(int i = hed[u];i;i = e[i].nxt){
		int v = e[i].to;
		dfs2(v);
		f[u] = max(f[u],min(f[v],si[v]*1.0/(si[u]-1)));
	}
}

double ans;
int main(){
	scanf("%d%d",&n,&k);
	int x;
	for(int i = 2;i<=n;++i){
		scanf("%d",&x);
		add(x,i);
	}
	
	dfs(1);
	
	for(int i = 1;i<=n;++i){
		if(si[i] == 1) f[i] = 1;
	}
	
	dfs2(1);
	
	for(int i = 1;i<=n;++i){
		if(si[i] > k) ans = max(ans,f[i]);
	}
	printf("%.8lf",ans);
	return 0;
}
```

---

