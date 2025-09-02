# Broken BST

## 题目描述

Let $ T $ be arbitrary binary tree — tree, every vertex of which has no more than two children. Given tree is rooted, so there exists only one vertex which doesn't have a parent — it's the root of a tree. Every vertex has an integer number written on it. Following algorithm is run on every value from the tree $ T $ :

1. Set pointer to the root of a tree.
2. Return success if the value in the current vertex is equal to the number you are looking for
3. Go to the left child of the vertex if the value in the current vertex is greater than the number you are looking for
4. Go to the right child of the vertex if the value in the current vertex is less than the number you are looking for
5. Return fail if you try to go to the vertex that doesn't exist

Here is the pseudo-code of the described algorithm:

`<br></br>bool find(TreeNode t, int x) {<br></br>    if (t == null)<br></br>        return false;<br></br>    if (t.value == x)<br></br>        return true;<br></br>    if (x < t.value)<br></br>        return find(t.left, x);<br></br>    else<br></br>        return find(t.right, x);<br></br>}<br></br>find(root, x);<br></br>`The described algorithm works correctly if the tree is binary search tree (i.e. for each node the values of left subtree are less than the value in the node, the values of right subtree are greater than the value in the node). But it can return invalid result if tree is not a binary search tree.

Since the given tree is not necessarily a binary search tree, not all numbers can be found this way. Your task is to calculate, how many times the search will fail being running on every value from the tree.

If the tree has multiple vertices with the same values on them then you should run algorithm on every one of them separately.

## 说明/提示

In the example the root of the tree in vertex $ 2 $ . Search of numbers $ 5 $ and $ 15 $ will return fail because on the first step algorithm will choose the subtree which doesn't contain numbers you are looking for.

## 样例 #1

### 输入

```
3
15 -1 -1
10 1 3
5 -1 -1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
6 2 3
3 4 5
12 6 7
1 -1 8
4 -1 -1
5 -1 -1
14 -1 -1
2 -1 -1
```

### 输出

```
1
```

# 题解

## 作者：Coros_Trusds (赞：2)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15760757.html)

顺着树剖的推荐题目点进来的，没想到压根不是树剖，代码还很短 $\verb!qwq!$。

# 题目大意

给定一棵 $\rm BST$，但是不保证这是一棵正确的 $\rm BST$。

请计算有多少节点不会被遍历到。

# 题目分析

在 $\rm BST$ 中，节点 $u$ 一定满足 $val[ls(u)]<val[u],val[rs(u)]>val[u]$，根据这个性质，一个数能够被找到当且仅当 $l<val[u]<r$。

在 $\rm dfs$ 过程中，我们使用 $map$ 来映射每个节点是否被找到，最后查找就很方便。

于是就做完了。

# 代码

注意 `dfs(rt,-1,1e9+1)`，因为 $\rm dfs$ 中我们是 `<` 和 `>`，所以这里应当满足 $l\ge0-1,r\le10^9+1$。

```cpp
//2022/1/3

const int ma=1e5+5;

int a[ma],ls[ma],rs[ma];

bool have_fa[ma];

int n;

map<int,bool>mp;

inline void dfs(int now,int l,int r)
{
	if(now==-1)
	{
		return;
	}
	
	if(a[now]>l && a[now]<r)
	{
		mp[a[now]]=true;
	}
	
	dfs(ls[now],l,min(r,a[now]));
	
	dfs(rs[now],max(l,a[now]),r);
}

int main(void)
{
	n=read();
	
	for(register int i=1;i<=n;i++)
	{
		a[i]=read(),ls[i]=read(),rs[i]=read();
		
		if(ls[i]!=-1)
		{
			have_fa[ls[i]]=true;
		}
		
		if(rs[i]!=-1)
		{
			have_fa[rs[i]]=true;
		}
	}
	
	int rt;
	
	for(register int i=1;i<=n;i++)
	{
		if(have_fa[i]==false)
		{
			rt=i;
			
			break;
		}
	}
	
	dfs(rt,-1,1e9+1);
	
	int ans=0;
	
	for(register int i=1;i<=n;i++)
	{
		if(mp[a[i]]==false)
		{
			ans++;
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：泠小毒 (赞：2)

# Broken BST
给一棵二叉搜索树,但是不保证这是一棵正确的二叉搜索树,那么按照二叉搜索树的搜索算法(小往左,大往右),可能找不到某些节点,你的任务是计算有多少节点将不会被遍历到
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190509/)
## 解法
这道题题意有点难理解。。。如果有相同的数字，只要有一个被遍历到了，其他都会被遍历到emm

如果暴力的去查询每一个节点的话，一条链就被卡成n方了emmm

所以换一种方法，因为二叉搜索树上每一个节点都有一个范围l<x<r，如果满足，这个点就扫得到

由于很坑的题意，用个map存一下，就差不多了
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,rt,a[100010],ls[100010],rs[100010],vis[100010],ans;
map<int,bool>mp;
void f(int nw){if(nw==-1)return;vis[nw]=1;}
void dfs(int nw,int l,int r)
{
    if(nw==-1)return ;
    if(a[nw]>l&&a[nw]<r)mp[a[nw]]=1;
    dfs(ls[nw],l,min(r,a[nw])),dfs(rs[nw],max(l,a[nw]),r);
}
void get_ans(){for(int i=1;i<=n;i++)if(!mp[a[i]])ans++;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i],&ls[i],&rs[i]),f(ls[i]),f(rs[i]);
    for(int i=1;i<=n;i++)if(!vis[i])rt=i;
    dfs(rt,-1,1e9+1),get_ans(),printf("%d\n",ans);
    return 0;
}
```

---

## 作者：momo5440 (赞：1)

遍历这题的题意非常坑人，若有多个点数值相同那么只要一个被遍历到了，其他就算遍历被到了，但假如任何一个带有这个数值的节点都没有被遍历到的话那么所有带有这个数值的节点都会被算在答案里（~~什么鬼~~）

题意大概说清楚了，接下来的问题是该怎么做，考虑这题之前我们先来考虑一个问题——在一棵二叉搜索树中一个点怎么才会被遍历到（~~这不就是这题吗~~）

我们先假定这有一个非叶子节点 a，他的左节点为l，右节点为r，那么能遍历到l的条件就是l.val<a.val（~~废话~~），同理能到r的条件便是r.val>a.val。下面便来考虑一个问题，为了方便便以 r 举例，那么在查询时如何保障对r.val的这个查询能落到a上呢？毕竟查询只有落到a上时才有机会接触到r我们先设r的爷爷节点为fa，假如a是fa的左节点时，那么必须得有r.val<fa.val才行不然就到右子树去了同理假如a是fa右节点时那么必须得有r.val>fa.val。

所以现在能看出来了一个点能被遍历到的条件是这个点的权值比所有的右转节点（下一个走的是右边）的权值要大而比所有左转节点小（同理），所以这个问题用dfs解决就行了，dfs有三个参数，一个是目前的节点号u，一个是一路上右转节点的最大值maxx，一个是所有左转节点的最小值minn，而他能被遍历到的条件是maxx<tree[u].val<minn。

大概就这样了，统计答案时用个map就行了

把代码贴上，绝对绿色无毒

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
vector<int> v;
struct node{
	int val,l,r;
};
node a[maxn];
bool to[maxn];
int rt,n;
map <int,bool> ma;
void dfs(int u,int maxx,int minn){
	if (u==-1) return;
	if (a[u].val>maxx&&a[u].val<minn) {
		ma[a[u].val]=true;
	}
	dfs(a[u].l,maxx,min(a[u].val,minn));
	dfs(a[u].r,max(a[u].val,maxx),minn);
	return;
}
int main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		scanf("%d%d%d",&a[i].val,&a[i].l,&a[i].r);
		if (a[i].l!=-1)to[a[i].l]=true;
		if (a[i].r!=-1)to[a[i].r]=true;
	}
	for (int i=1;i<=n;i++){
		if(to[i]==false) {
			rt=i;
		}
	}
	dfs(rt,-1,1e9+1);
	int ans=0;
	for (int i=1;i<=n;i++){
		if (ma[a[i].val]==false) ans++;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：AK_heaven (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF797D)

给出一颗普通二叉树，请问，如果把这颗二叉树作为二叉搜索树使用，有多少值无法被访问到。

以上是精确的翻译。

考虑二叉搜索树的性质，对于一个节点，左子树所有节点小于自己，右子树所有节点大于自己。也就是要想被搜索到，必须在一个值域内才行，注意，值相同的节点只要一个被访问到，其余的都视为可访问。

代码如下：


```cpp
#include <bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define pii pair<int, int>
#define ll long long
#define vi vector<int>
using namespace std;

const int N = 1e5 + 10;

#define ls tr[p].L
#define rs tr[p].R

struct node {
	int L, R;
	int w;
}tr[N];

map<int, bool> mp;

int n, vis[N], cnt;

void dfs(int p, int l, int r) {
	if(l < tr[p].w && tr[p].w < r) mp[tr[p].w] = 1;
	if(ls != -1) dfs(ls, l, min(tr[p].w, r));
	if(rs != -1) dfs(rs, max(tr[p].w, l), r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	L(i, 1, n) cin >> tr[i].w >> tr[i].L >> tr[i].R;
	L(i, 1, n) {
		if(tr[i].L != -1) vis[tr[i].L] = 1;
		if(tr[i].R != -1) vis[tr[i].R] = 1;
	}
	L(i, 1, n) if(!vis[i]) dfs(i, -1, 1e9+1);
	L(i, 1, n) cnt += mp[tr[i].w];
	cout << n-cnt;
	return 0;
}

```

---

