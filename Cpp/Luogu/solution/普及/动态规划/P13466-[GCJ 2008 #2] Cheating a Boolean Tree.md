# [GCJ 2008 #2] Cheating a Boolean Tree

## 题目描述

在本题中，我们将考虑一种称为布尔树的二叉树。在这种树中，除了最后（最深）一层外，每一层都被完全填满，并且最后一层的节点尽可能靠左。此外，树中的每个节点要么有 $0$ 个子节点，要么有 $2$ 个子节点。

布尔树的特殊之处在于，每个节点都与一个布尔值相关联，取 $1$ 或 $0$。此外，每个内部节点都与一个“AND”或“OR”门相关联。一个“AND”门节点的值由其两个子节点的值进行逻辑与运算得到。同理，“OR”门节点的值由其两个子节点的值进行逻辑或运算得到。所有叶子节点的值将作为输入给出，因此可以自底向上计算所有节点的值。

我们特别关注树的根节点。我们希望根节点的值为 $V$，即 $1$ 或 $0$。不幸的是，根节点的实际值可能并非如此。幸运的是，我们可以作弊，将某些节点的门类型进行更改；即可以将 AND 门改为 OR 门，或将 OR 门改为 AND 门。

给定一个布尔树的描述以及哪些门可以更改，求最少需要更改多少个门，才能使根节点的值为 $V$。如果无法实现，则输出 "IMPOSSIBLE"（带引号，仅为清晰起见）。

## 说明/提示

**样例说明**

在第 1 个测试用例中，我们可以将节点 3 的门更改为 OR 门，从而使根节点达到期望的结果。

在第 2 个测试用例中，只有根节点可以更改，但将其改为 OR 门也无法实现目标。

**数据范围**

- $1 < N \leq 20$

**小数据集（5 分，测试点 1 - 可见）**

- $2 < M < 30$

**大数据集（10 分，测试点 2 - 隐藏）**

- $2 < M < 10000$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
9 1
1 0
1 1
1 1
0 0
1
0
1
0
1
5 0
1 1
0 0
1
1
0```

### 输出

```
Case #1: 1
Case #2: IMPOSSIBLE```

# 题解

## 作者：Nostopathy (赞：1)

# Solution

## 1 思路

树形 DP。

定义 $dp_{i,0/1}$ 表示在以 $i$ 为根的子树中，$i$ 的值为 $0/1$ 的最小更改数。

可以发现分为以下情况：

- $i$ 是“AND”门，且不能修改：若要求 $0$，则左子节点取 $0$ 时右子节点取 $0/1$，左子节点取 $1$ 时右子节点取 $0$；若要求 $1$，则左子节点取 $1$ 时右子节点取 $1$；
- $i$ 是“OR”门，且不能修改：若要求 $0$，则左子节点取 $0$ 时右子节点取 $0$；若要求 $1$，则左子节点取 $1$ 时右子节点取 $0/1$，左子节点取 $0$ 时右子节点取 $1$；
- $i$ 是“AND”门，且可以修改：在“$i$ 是“OR”门，且不能修改”的情况上加 $1$；
- $i$ 是“OR”门，且可以修改：在“$i$ 是“AND”门，且不能修改”的情况上加 $1$。

特别地，若 $i$ 为叶子节点，则 $dp_{i,val_i} \leftarrow 0,dp_{i,1-val_i} \leftarrow +\infty$。

答案为 $dp_{1,V}$，若该值为 $+
\infty$，则判定无解。

## 2 实现

梳理了以上的思路，我们就可以愉快地写代码了：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pb push_back
#define rep(a, b, c, d) for(int a=b; a<=c; a+=d)
#define inf (INT_MAX >> 1)
const int N = 1e4 + 5;
int ls(int n) {return n << 1;}
int rs(int n) {return (n << 1) + 1;}
struct node {
	bool is_and, changeable, is_leaf, val;
};
bool Min(int &a, int b) {
	return (b < a ? a = b, 0 : 1);
}
void solve(int casenum) {
	int m, v;
	cin >> m >> v;
	vector<node> arr(m + 1);
	rep(i, 1, (m - 1) / 2, 1) {
		bool g, c;
		cin >> g >> c;
		arr[i].is_and = g;
		arr[i].changeable = c;
		arr[i].is_leaf = 0;
	}
	rep(i, (m - 1) / 2 + 1, m, 1) {
		bool n;
		cin >> n;
		arr[i].val = n;
		arr[i].is_leaf = 1;
	}
	vector<vector<int> > dp(m + 1, vector<int>(2, inf));
	for(int i = m; i >= 1; -- i) {
		if(arr[i].is_leaf) {
			dp[i][arr[i].val] = 0;
			dp[i][!arr[i].val] = inf;
		}
		else {
			int ls = (i << 1), rs = (i << 1) + 1;
			rep(tar, 0, 1, 1) {
				int res = inf;
				if(arr[i].is_and) {
					if(tar == 1) {
						if(dp[ls][1] != inf && dp[rs][1] != inf)
							Min(res, dp[ls][1] + dp[rs][1]); 
					}
					else {
						int a = inf, b = inf;
						if(dp[ls][0] != inf)
							a = dp[ls][0] + min(dp[rs][0], dp[rs][1]);
						if(dp[ls][1] != inf && dp[rs][0] != inf)
							b = dp[ls][1] + dp[rs][0];
						Min(res, min(a, b));
					}
				}
				else {
					if(tar == 0) {
						if(dp[ls][0] != inf && dp[rs][0] != inf)
							Min(res, dp[ls][0] + dp[rs][0]);
					}
					else {
						int a = inf, b = inf;
						if(dp[ls][1] != inf)
							a = dp[ls][1] + min(dp[rs][0], dp[rs][1]);
						if(dp[ls][0] != inf && dp[rs][1] != inf)
							b = dp[ls][0] + dp[rs][1];
						Min(res, min(a, b));
					}
				}
				if(arr[i].changeable) {
					if(!arr[i].is_and) {
						if(tar == 1) {
							if(dp[ls][1] != inf && dp[rs][1] != inf)
								Min(res, dp[ls][1] + dp[rs][1] + 1); 
						}
						else {
							int a = inf, b = inf;
							if(dp[ls][0] != inf)
								a = dp[ls][0] + min(dp[rs][0], dp[rs][1]) + 1;
							if(dp[ls][1] != inf && dp[rs][0] != inf)
								b = dp[ls][1] + dp[rs][0] + 1;
							Min(res, min(a, b));
						}
					}
					else {
						if(tar == 0) {
							if(dp[ls][0] != inf && dp[rs][0] != inf)
								Min(res, dp[ls][0] + dp[rs][0] + 1);
						}
						else {
							int a = inf, b = inf;
							if(dp[ls][1] != inf)
								a = dp[ls][1] + min(dp[rs][0], dp[rs][1]) + 1;
							if(dp[ls][0] != inf && dp[rs][1] != inf)
								b = dp[ls][0] + dp[rs][1] + 1;
							Min(res, min(a, b));
						}
					}
				}
				dp[i][tar] = res;
			}
		}
	}
	cout << "Case #" << casenum << ": ";
	if(dp[1][v] != inf)
		cout << dp[1][v] << "\n";
	else
		cout << "IMPOSSIBLE\n";
}
signed main () {
	int n;
	cin >> n;
	rep(i, 1, n, 1)
		solve(i);
	return 0;
}
```

## 3 小结

本题作为一道 DP 有一定难度，需要具备分类讨论推导的能力。感谢您能看到这里，也欢迎评论区留言讨论。

也以此纪念我写过最长的代码（$2.68\text{KB}$）。

~~没有求关的题解不是好题解。~~

---

## 作者：4041nofoundGeoge (赞：1)

:::align{center}
## 思路
:::

经典树形 DP 问题。

题目大意是：通过修改与/或阀，使得最后结果为 $V$ 的最小操作次数，**仅能修改可修改的结点。**，下文中的假设均在此结点可以修改的前提下，若无法更改，此值为 $\infty$。

设 $f_{\text{node},\text{val}}$，表示结点 $\text{node}$ 的值为 $\text{val}$ 的最小操作次数。

很显然，不修改当前的结点，很显然为其左右子树的操作次数的和： $f_{\text{node},p}=\min\{f_{\text{node},\text{p}},f_{\text{left},\text{val left}}+f_{\text{left},\text{val right}}\}$，其中 $\text{left},\text{right}$ 各为 $\text{node}$ 的左右子结点，即 $\text{left}\leftarrow \text{node}\times 2,\text{right}\leftarrow \text{node}\times 2+1$，$\text{val left},\text{val right}$ 表示的是左右结点的状态，各可以为 $0$ 或 $1$，当然，若 $\text{node}$ 左右子树无法更改修改成对应的值，其值为 $\infty$；$p$ 为当前结点的状态，为 $1$ 则为与运算，否则为或运算。

若更改当前与/或阀，即在其左右子树的和**加一**，$p$ 也取反：$f_{\text{node},1-p}=\min\{f_{\text{node},\text{1-p}},f_{\text{left},\text{val left}}+f_{\text{left},\text{val right}}+1\}$。

最后我们只需要从叶子结点往上做动规即可，叶子结点对应的动规数组初始值为 $0$。

:::align{center}
## 代码
:::

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
struct Tree{
    int gate;//原与/或阀的数值
    int flag;//是否能被修改
    int value;//叶子结点的数值
    bool leaf;//是否为叶子结点
};
Tree tree[10005];
int f[10005][3];
void dp(int node){
    if(tree[node].leaf==1){f[node][tree[node].value]=0;return;}
    int left=node*2,right=node*2+1;
    dp(left);//搜索左子树
    dp(right);//搜索右子树
    for(int i=0;i<=1;i++)f[node][i]=INF;
    int gate=tree[node].gate;
    for(int l=0;l<=1;l++){
        for(int r=0;r<=1;r++){
            if(f[left][l]==INF||f[right][r]==INF)continue;//这个点改不成这个数值，跳过
            int ans;
            if(!gate)ans=l||r;
            else ans=l&&r;
            int pay=f[left][l]+f[right][r];
            if(pay<f[node][ans])f[node][ans]=pay;
        }
    }
    if(tree[node].flag){//这个点能改
        int Gate=1-tree[node].gate;
        for(int l=0;l<=1;l++){
            for(int r=0;r<=1;r++){
                if(f[left][l]==INF||f[right][r]==INF)continue;
                int ans;
                if(!Gate)ans=l||r;
                else ans=l&&r;
                int pay=f[left][l]+f[right][r]+1;
                if(pay<f[node][ans])f[node][ans]=pay;
            }
        }
    }
}
int main(){
    int t;
    cin>>t;
    int q=t;
    while(t--){
        int m,v;
        cin>>m>>v;
        memset(tree,0,sizeof tree);
        for(int i=1;i<=m;i++){
            if(i<=(m-1)/2){
                int g,c;
                cin>>g>>c;
                tree[i].gate=g,tree[i].flag=c;
            }
            else{
                int I;
                cin>>I;
                tree[i].leaf=1;
                tree[i].value=I;
            }
        }
        memset(f,INF,sizeof f);
        dp(1);
        cout<<"Case #"<<q-t<<": ";
        if(f[1][v]==INF)cout<<"IMPOSSIBLE";
        else cout<<f[1][v];
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13466)

# 题目分析

一道树上动态规划题，可以分成几部分解决。

第一步是建树。参照线段树，我们不难写出以下代码：

```cpp
inline void build(int x,int n){
	if(x>n){
		return;
	}
	tree[x].clear();
	tree[x].push_back((edge){x,2*x});
	tree[x].push_back((edge){x,2*x+1});
	build(2*x,n);
	build(2*x+1,n);
	return;
}
```
其中 ```tree[]``` 为存储树的邻接表。

第二步是算出每个节点初始时的值。这里用一个深搜可以解决。代码如下：

```cpp
inline void build2(int x){
	if(p[x].kind==2){
		return;
	}
	for(int i=0;i<tree[x].size();i++){
		build2(tree[x][i].v);
		if(p[x].gate==0){
			p[x].num=p[tree[x][0].v].num|p[tree[x][1].v].num;
		}
		else{
			p[x].num=p[tree[x][0].v].num&p[tree[x][1].v].num;
		}
	}
	return;
}
```
其中 ```p``` 是存储每个点信息的结构体。，定义如下：

```cpp
struct points{
	int kind；//是否为叶子节点（1不是，2是）
        int gate;//每个内部节点的门（按照题目中的方式赋值）
        int change;//门是否可以变
        int num;每个节点的值
}p[N];
```

接下来就进入动态规划的环节。

定义状态 $f_{i,j}$ 表示将节点 $i$ 的值变为 $j$ 所需最小变化次数。显然，$f_{i,j}=0$，如果初始时节点 $i$ 的值为 $j$。

下面是一个很重要的结论：左子树的任何变化操作都不会影响右子树中的节点，右子树的任何操作也不会影响左子树。证明：

变化一个节点的门，只会影响其祖先节点的值。而左子树中任意一个节点的祖先不可能在右子树中，右子树中的任意节点的祖先也不可能在左子树中，证毕。

由此，把左子节点 $i_1$ 的值编程 $m$，把右子节点 $i_2$ 的值变成 $n$ 的总操作次数为 $f_{i_1,m}+f_{i_2,n}$。

下面就需要分类讨论了。设节点 $i$ 的左子节点为 $v_1$，右子节点为 $v_2$。

- 若节点 $i$ 为与门且可以变化，则若节点 $i$ 要变成 $1$，有三种变法：将左右子节点的值都变成 $1$，将左子节点的值变为 $1$ 并将门变为或，以及将右子节点变为 $1$ 并将门变为或。因此 $f_{i,1}=\min(f_{v_1,1}+f_{v_2,1},f_{v_1,1}+1,f_{v_2,1}+1)$。将其值变为 $0$ 则较为简单，因为此时不需要考虑将门变成或的情况，所以 $f_{i,0}=\min(f_{v_1,0},f_{v_2,0})$。
- 若节点 $i$ 为与门且不可变化，则将其值变为 $1$ 的方式有且只有一种，就是其左右子节点都为 $1$。此时 $f_{i,1}=f_{v_1,1}+f_{v_2,1}$。而将值变为 $0$ 的情况与前一种情况相同，$f_{i,0}=\min(f_{v_1,0},f_{v_2,0})$。
- 若节点 $i$ 为或门且可以变化，则若将值变为 $1$，与与门中变为 $0$ 类似，不用考虑门的变化，答案为 $f_{i,1}=\min(f_{v_1,1},f_{v_2,1})$。若将值变为 $0$，则有三种变法：将左右子节点的值全变为 $0$，或将其门变为与，然后将左右子节点中的一个变为 $0$。所以答案为 $f_{i,0}=\min(f_{v_1,0}+f_{v_2,0},f_{v_1,0}+1,f_{v_2,0}+1)$。
- 若节点 $i$ 的门为或且不可变化，则若将值变为 $1$，与前一种情况一样，答案为 $f_{i,1}=\min(f_{v_1,1},f_{v_2,1})$。若将值变为 $0$，则有且只有一种变法，即左右子节点都变成 $0$，答案为 $f_{i,0}=f_{v_1,0}+f_{v_2,0}$。

对于叶子节点，由于其值无法改变，所以设其值为 $x$，则有 $f_{i,x}=0$，$f_{i,y}$ 为正无穷，其中 $y$ 为 $0$ 和 $1$ 中的一个且不等于 $x$。由此，$f_{1,k}$ 就是答案。如果该值为正无穷，则无解。

# 完整代码

```cpp
#include<bits/stdc++.h>
#define N 100001
#define INF 100000001
using namespace std;
int plus1(int a,int b){
	if(a!=INF&&b!=INF){
		return a+b;
	}
	return INF;
}
struct edge{
	int u,v;
};
vector<edge>tree[N];
inline void build(int x,int n){
	if(x>n){
		return;
	}
	tree[x].clear();
	tree[x].push_back((edge){x,2*x});
	tree[x].push_back((edge){x,2*x+1});
	build(2*x,n);
	build(2*x+1,n);
	return;
}
struct points{
	int kind,gate,change,num;
}p[N];
int f[N][2];
inline void build2(int x){
	if(p[x].kind==2){
		return;
	}
	for(int i=0;i<tree[x].size();i++){
		build2(tree[x][i].v);
		//cout<<p[tree[x][0].v].num<<' '<<p[tree[x][1].v].num<<endl;
		if(p[x].gate==0){
			p[x].num=p[tree[x][0].v].num|p[tree[x][1].v].num;
		}
		else{
			p[x].num=p[tree[x][0].v].num&p[tree[x][1].v].num;
		}
	}
	return;
}
void dfs(int x){
	if(p[x].kind==2){
		return;
	}
	int v1=tree[x][0].v,v2=tree[x][1].v;
	dfs(v1);
	dfs(v2);
	if(p[x].gate==1){
		if(p[x].num==1){
			//cout<<'@'<<x<<endl;
			f[x][1]=0;
			f[x][0]=min(f[v1][0],f[v2][0]);
		}
		else{
			//cout<<'#'<<x<<endl;
			f[x][0]=0;
			if(p[x].change==1){
				f[x][1]=min(plus1(f[v1][1],f[v2][1]),min(plus1(f[v2][1],1),plus1(f[v1][1],1)));
			}
			else{
				f[x][1]=plus1(f[v1][1],f[v2][1]);
			}
		}
	}
	else{
		if(p[x].num==1){
			f[x][1]=0;
			if(p[x].change==1){
				//cout<<"$"<<x<<endl;
				f[x][0]=min(plus1(f[v1][0],f[v2][0]),min(plus1(f[v1][0],1),plus1(f[v2][0],1)));
			}
			else{
				f[x][0]=plus1(f[v1][0],f[v2][0]);
			}
		}
		else{
			//cout<<'%'<<x<<endl;
			f[x][0]=0;
			f[x][1]=min(f[v1][1],f[v2][1]);
		}
	}
	return;
}
int main(){
	int t;
	cin>>t;
	for(int o=1;o<=t;o++){
		cout<<"Case #"<<o<<": ";
		int n,v;
		cin>>n>>v;
		build(1,n);
		for(int i=1;i<=(n-1)/2;i++){
			int x,y;
			cin>>x>>y;
			p[i].kind=1;
			p[i].gate=x;
			p[i].change=y;
		}
		for(int i=(n-1)/2+1;i<=n;i++){
			int x;
			cin>>x;
			p[i].kind=2;
			p[i].num=x;
			if(x==1){
				f[i][1]=0;
				f[i][0]=INF;
			}
			else{
				f[i][0]=0;
				f[i][1]=INF;
			}
		}
		build2(1);
//		for(int i=1;i<=n;i++){
//			cout<<p[i].num<<' ';
//		}
//		cout<<endl;
		if(p[1].num==v){
			cout<<0<<endl;
			continue;
		}
		dfs(1);
		if(f[1][v]==INF){
			cout<<"IMPOSSIBLE"<<endl;
		}
		else{
			cout<<f[1][v]<<endl;
		}
	}
	return 0;
}
```

---

