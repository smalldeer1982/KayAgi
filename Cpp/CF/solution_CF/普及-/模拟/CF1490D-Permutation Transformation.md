# Permutation Transformation

## 题目描述

A permutation — is a sequence of length $ n $ integers from $ 1 $ to $ n $ , in which all the numbers occur exactly once. For example, $ [1] $ , $ [3, 5, 2, 1, 4] $ , $ [1, 3, 2] $ — permutations, and $ [2, 3, 2] $ , $ [4, 3, 1] $ , $ [0] $ — no.

Polycarp was recently gifted a permutation $ a[1 \dots n] $ of length $ n $ . Polycarp likes trees more than permutations, so he wants to transform permutation $ a $ into a rooted binary tree. He transforms an array of different integers into a tree as follows:

- the maximum element of the array becomes the root of the tree;
- all elements to the left of the maximum — form a left subtree (which is built according to the same rules but applied to the left part of the array), but if there are no elements to the left of the maximum, then the root has no left child;
- all elements to the right of the maximum — form a right subtree (which is built according to the same rules but applied to the right side of the array), but if there are no elements to the right of the maximum, then the root has no right child.

For example, if he builds a tree by permutation $ a=[3, 5, 2, 1, 4] $ , then the root will be the element $ a_2=5 $ , and the left subtree will be the tree that will be built for the subarray $ a[1 \dots 1] = [3] $ , and the right one — for the subarray $ a[3 \dots 5] = [2, 1, 4] $ . As a result, the following tree will be built:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1490D/0aafe2e3bc6081fb6190b15e93678e9e1d0a0393.png)The tree corresponding to the permutation $ a=[3, 5, 2, 1, 4] $ .Another example: let the permutation be $ a=[1, 3, 2, 7, 5, 6, 4] $ . In this case, the tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1490D/5e7d3506add8fba00a43e087fca1d5c43d5b6f50.png)The tree corresponding to the permutation $ a=[1, 3, 2, 7, 5, 6, 4] $ .Let us denote by $ d_v $ the depth of the vertex $ a_v $ , that is, the number of edges on the path from the root to the vertex numbered $ a_v $ . Note that the root depth is zero. Given the permutation $ a $ , for each vertex, find the value of $ d_v $ .

## 样例 #1

### 输入

```
3
5
3 5 2 1 4
1
1
4
4 3 1 2```

### 输出

```
1 0 2 3 1 
0 
0 1 3 2```

# 题解

## 作者：冰糖鸽子 (赞：2)

第一眼：哇塞，看上去很难的样子   
第二眼：等一下，这个数据范围。。。水题切了！

----

题目说的清清楚楚，先转换后 $\operatorname{dfs}$ 即可。

转换的时候类似线段树的递归建树，若 $l>r$ 了返回即可。

还有，因为是树，所以我直接为每个点记录了父亲，这也导致了 $\operatorname{dfs}$ 的复杂度高达 $n^2$ ，但是毕竟是 $100$ 嘛，你就算 $n^3$ 又怎么样呢。

$\operatorname{dfs}$ 就普通的 $\operatorname{dfs}$ ，只不过往下走的时候要遍历所有点，遇到父亲是自己的就往下走。

代码（ `Re()` 本来是用来多测清空的，无奈根本没有需要清空的）：

```cpp

// Problem: D. Permutation Transformation
// Contest: Codeforces - Codeforces Round #702 (Div. 3)
// URL: https://codeforces.ml/contest/1490/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
#define M 110
int T,n,a[M],FA[M],d[M];
void Re()
{
	
}
void build(int l,int r,int fa)
{
	if(l>r) return;
	int MAXN=0,MAXI;
	for(int i=l;i<=r;i++)//第一处乱搞/ll
	{
		if(a[i]>MAXN)
		{
			MAXN=a[i];
			MAXI=i;
		}
	}
	FA[MAXN]=fa;
	build(l,MAXI-1,MAXN);
	build(MAXI+1,r,MAXN);
}
void dfs(int x,int D)
{
	d[x]=D;
	for(int i=1;i<=n;i++)//第二次乱搞
	{
		if(FA[i]==x)
		{
			dfs(i,D+1);
		}
	}
}
int main()
{
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		Re();
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		build(1,n,0);
		dfs(0,-1);
		for(int i=1;i<=n;i++)
		{
			cout<<d[a[i]]<<' ';//不是d[i]
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Fa1thful (赞：0)

### 题意：
建一棵树，问树上一个节点的深度。
### 分析：
这道题没有什么思维相关的东西，因为数据范围$1\le n \le 100$，完全支持我们自己建一棵树然后直接模拟。所以思路就是模拟，ps：学校测试考这题的时候有人说是并查集，当然有点像，但是没必要啊，直接记录一个 $father$ 然后连续找祖宗就行了，用不到并查集。
### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
int a[100000];//节点 
int fa[100000];//每个节点的父亲 
void build(int l, int r, int fat) //l左子树，r右子树，fat最大节点的编号 
{
	if (l > r) return;   //依题意 
	if (l == r) 
	{
		fa[l] = fat;
		return;
	}
	int root = 0, mid;
	for (int i = l; i <= r; i++)
	{
		if (a[i] > root) root = a[i], mid = i;  //更新最大数 
	}
	fa[mid] = fat;    //记录爸爸 
	build(l, mid - 1, mid);   
	build(mid + 1, r, mid);
}
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		memset(fa, 0, sizeof(fa));  //初始化 
		int n;
		int root = 0;   //树的根 
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
		}
		build(1, n, -1); //依题意建树 
		for (int i = 1; i <= n; i++)
		{
			int cnt = 0, cur = i;
			while (cur != -1)  //有爸爸 
			{
				cur = fa[cur];   //他变成爸爸 
				cnt++;//继续找爸爸有没有爸爸 
			}
			cout << cnt - 1 << " ";  //没有就找到祖宗了 
		}
		cout << endl;
	}
	return 0;
}
```


---

## 作者：_caiji_ (赞：0)

 _upd on 2021/3/20 修改了图片的 $\LaTeX$_ 

首先我们观察到 $1\leq T\leq 100$，$1\leq n\leq 100$，发现这道题可以使用 dfs 暴力建树记录。

我们来算一下 dfs 的复杂度。对于每一层递归，都要在 $[l,r]$ 区间内找最大值，然后把 $[l,r]$ 分成两部分 $[l,\max i-1]$ 和 $[\max i+1,r]$。我们画个图：

$$
\def{\k}{\quad\quad}
\def{\kk}{\,\,\,}
\def{\kkk}{\underbrace}
\def{\hid}{\color{white}}
\def{\unhid}{\color{black}}
\def{\maxx}{\color{red}}
\def{\udl}{\underline}
\begin{aligned}
\kkk{4 \k 1 \k 2 \k 6\k 3}\k \maxx 8\unhid \k \kkk{7 \k 5}\\
\kkk{4\k1\k2}\k\maxx 6\unhid\k\udl{3}\k\hid 8\unhid\k\maxx 7\unhid \k\udl{5}\\
\maxx4\unhid\k\kkk{1\k2}\k\hid 6\k\maxx3\hid\k8\k7\k\maxx5\\
\hid4\unhid\k\udl{1}\k\maxx2\unhid\hid\k6\k3\k8\k7\k5\\
\hid4\k\maxx1\hid\k2\k6\k3\k8\k7\k5
\end{aligned}
$$

随便估算一下上下界，这样建树的复杂度最小 $O(n\log n)$，最大 $O(n^2)$，足以通过。（如果这个结论错了请指正。）

代码：
```cpp
void dfs(int l,int r,int dep){
    if(l>r) return ;
    int maxn=0,maxi;
    for(int i=l;i<=r;i++){
        if(a[i]>maxn) maxn=a[i],maxi=i;
    }
    ans[maxi]=dep;//记得记录深度
    dfs(l,maxi-1,dep+1);
    dfs(maxi+1,r,dep+1);
}
int mian(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    dfs(1,n,0);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个**排列** $a$，按照以下方法构造一棵树：
- 选择当前排列中的最大数作为根的编号。
- 最大数左边的所有数按照上述方法建左子树，若没有数则该节点没有左儿子。
- 最大数右边的所有数按照上述方法建右子树，若没有数则该节点没有右儿子。
求每个结点的深度（**根节点深度为 $0$**）。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 100$，$1\leqslant n\leqslant 100$。**
## Solution
看到这个题目第一眼以为是什么神仙构造题，结果一看数据范围……直接上 dfs 就过了。

具体地，我们先从 $1$ 到 $n$ 进行遍历找到最大数，再将最大数左边的数和右边的数分别继续 dfs，直到左边界大于右边界为止，dfs 时再将每个节点的深度赋值，每递归一层，就相比于上一层 $+1$ 即可。

如果没听懂就看代码吧。
## Code
```cpp
int a[107], d[107];

iv dfs(int l, int r, int cur) {
	if(l > r) return;
	int pl = l;
	F(i, l, r) if(a[pl] < a[i]) pl = i;
	d[pl] = cur;
	dfs(l, pl - 1, cur + 1), dfs(pl + 1, r, cur + 1);
}

int main() {
	MT {
		F(i, 1, 100) d[i] = 0;
		int n = Rint;
		F(i, 1, n) a[i] = Rint;
		dfs(1, n, 0);
		F(i, 1, n) write(a[i]), putchar((i == n) ? ' ' : '\n');
	}
	return 0;
}
``` 

---

## 作者：Wuyanru (赞：0)

题目链接：[CF1490D Permutation Transformation](https://www.luogu.com.cn/problem/CF1490D)

这道题是一道看起来有关树的题，但是在做题时和树没有太大关系。

本题解使用的做法是模拟，就是将题目中描述的方法模拟了一遍。

接下来让我们看一下模拟的过程。

首先我们可以定义一个函数 $ run $ ,用于计算从左数第 $ l $ 个节点与第 $ r $ 个节点之间所有节点的深度，这样子就可以顺利的进行递归了。

1.  令 $ l=1 $,$ r=1 $。
2.  运行函数，找出区间中最大值，计算深度。
3.  如果 $ l=r $,结束函数。
4.  计算最大数左边所有节点的深度，回到步骤二。
5.  计算最大数右边所有节点的深度，回到步骤二。

所以到最后的函数长这个样子。

```
int max(int l,int r)//寻找区间中最大值 
{
    int maxn=0;
    int maxi;
    for(int i=l;i<=r;i++)
    {
        maxi=(maxn>a[i])?maxi:i;
        maxn=(maxn>a[i])?maxn:a[i];
    }
    return maxi;
}
void run(int l,int r,int fa)
{
    if(l==r)
    {
        ans[l]=ans[fa]+1;
        return ;
    }
    int num=max(l,r);
    ans[num]=ans[fa]+1;
    if(num>l) //判断一定要加上，不加会RE
        run(l,num-1,num);
    if(num<r)
        run(num+1,r,num);
}
```
注意！如果在函数中不加入上方的两个判断语句，会进入死循环！

最后，将主函数写完就算是大功告成了。

AC代码：

```
#include<cstring>
#include<cstdio>
using namespace std;
int ans[101];
int a[101];
int max(int l,int r)//寻找区间中最大值 
{
    int maxn=0;
    int maxi;
    for(int i=l;i<=r;i++)
    {
        maxi=(maxn>a[i])?maxi:i;
        maxn=(maxn>a[i])?maxn:a[i];
    }
    return maxi;
}
void run(int l,int r,int fa)
{
    if(l==r)
    {
        ans[l]=ans[fa]+1;
        return ;
    }
    int num=max(l,r);
    ans[num]=ans[fa]+1;
    if(num>l)
        run(l,num-1,num);
    if(num<r)
        run(num+1,r,num);
}
int main()
{
    int t;
    scanf("%d",&t);
    for(int k=1;k<=t;k++)
    {
        memset(ans,0,sizeof(ans));
        memset(a,0,sizeof(a));
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",a+i);
        int num=max(1,n);
        ans[num]=0;
        if(num>1)
            run(1,num-1,num);
        if(num<n)
            run(num+1,n,num);
        for(int i=1;i<=n;i++)
            printf("%d ",ans[i]);
        printf("\n");
    }
}
```
完结撒花！

---

## 作者：StupidSeven (赞：0)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/CF1490D)

## Analysis
首先我们看到这个n很小，只有100，考虑分治，暴力模拟建树的过程，然后每次记录一下深度就好了。细节见代码

## Code
```cpp
#include<cmath>
#include<queue>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
#define M 110
inline int Readint(void){
	int s=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){s=s*10+c-48;c=getchar();}
	return s*f;	
}
int T,n,value[M],dep[M];
void Dfs(int lson,int rson,int depth){
	int Max=0,idx=0;
	for(int i=lson;i<=rson;i++)
		if(value[i]>Max){
			Max=value[i];
			idx=i;
		}
	dep[idx]=depth;
	if(lson<idx) 
		Dfs(lson,idx-1,depth+1);
	if(rson>idx) 
		Dfs(idx+1,rson,depth+1);
	return;
}
signed main(void){
	T=Readint();
	while(T--){
		n=Readint();
		for(int i=1;i<=n;i++)
			value[i]=Readint();
		Dfs(1,n,0);
		for(int i=1;i<=n;i++)
			printf("%lld ",dep[i]);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：meyi (赞：0)

考场上一眼认出是笛卡尔树，心想 div.3 怎么会考这种东西，然而继续往下看到数据范围：$t\leq100$，$n\leq100$。

于是就可以 $O(n^2)$ 直接按照题意模拟了，找到当前区间最大值，并对当前区间每个节点的深度 `+1`，再递归到左右子区间，要注意深度从 `0` 开始，因此深度数组需要赋 `-1` 的初值。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=110;
int a[maxn],d[maxn],n,t;
void dfs(int l,int r){
	if(l>r)return;
	int m=0,p;
	for(ri i=l;i<=r;++i){
		++d[i];
		if(a[i]>m)m=a[i],p=i;
	}
	dfs(l,p-1),dfs(p+1,r);
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(ri i=1;i<=n;++i)scanf("%d",a+i);
		memset(d,-1,sizeof d);
		dfs(1,n);
		for(ri i=1;i<=n;++i)printf("%d ",d[i]);
		printf("\n");
	}
}
```


---

## 作者：清烛 (赞：0)

挂一下 [My Blog](https://imyangty.com/oi/1309)
## 题意
将一个 $1 - n$ 的排列按照如下规则建成一棵二叉树。

- 找到最大元素，定为树根
- 递归构建左子树
- 递归构建右子树

并输出每个节点的深度（根的深度为 $0$）

## 题解
数据范围 $1\le n\le 100$，所以根本不虚，直接大力按照题意模拟就可以了，构建 $[l,r]$ 的时候找到最大值所在位置 $k$，更新 $k$ 的深度，然后继续建 $[l, k - 1]$ 和 $[k + 1, r]$ 即可，详见代码中提示。

```cpp
void build(int i, int j, int d)
{
    if (i > j) return;//注意边界
    int maxa = -1, pos;
    FOR(k, i, j)
        if (a[k] > maxa)
            maxa = a[k], pos = k;//找到最大的元素在哪里
    dep[pos] = d;//更新深度
    build(i, pos - 1, d + 1);//递归建左子树
    build(pos + 1, j, d + 1);//递归建右子树
    return;
}

int main()
{
    int T = read();
    while (T--)
    {
        int n = read();
        FOR(i, 1, n)
            a[i] = read(), dep[i] = 0;
        build(1, n, 0);//注意根的深度为 0
        FOR(i, 1, n) printf("%d ", dep[i]);
        puts("");
    }
    return 0;
}
```

---

## 作者：registerGen (赞：0)

[宣传一下这次 div3 的题解](https://registergen.github.io/post/solution-codeforces-round-702-div-3/)

直接暴力分治即可。先找出根，然后处理左右子树。

```cpp
int n,a[N+10],anss[N+10];
 
void work(int l,int r){
	if(l>r)return;
	if(l==r)return;
	int maxx=ninf,tmp=-1;
	for(int i=l;i<=r;i++)
		if(a[i]>maxx)maxx=a[i],tmp=i;
	for(int i=l;i<=r;i++)
		if(a[i]!=maxx)anss[i]++; // 如果不是子树的根，则深度 +1
	work(l,tmp-1); // 处理左子树
	work(tmp+1,r); // 处理右子树
}
 
void solve(){
	scanf("%d",&n);
	rep(i,1,n)a[i]=ri();
	memset(anss,0,sizeof(anss));
	work(1,n);
	rep(i,1,n)printf("%d ",anss[i]);
	puts("");
}
```

---

## 作者：henrytb (赞：0)

题目给了一棵二叉树的中序遍历，让我们求出所有节点的深度。

这不大水题吗？？考虑分治，每次找到范围内最大的数拎成根，更新答案，然后从这里劈两半继续往下处理即可。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n;
int a[105],ans[105];
void solve(int l,int r,int dep) {
    if(l==r) {ans[l]=dep;return;}
    if(l>r) return;
    int mx=0,id;
    rep(i,l,r) {
        if(a[i]>mx) mx=a[i],id=i;
    }
    ans[id]=dep;
    solve(l,id-1,dep+1);
    solve(id+1,r,dep+1);
}
int main() {
    for(scanf("%d",&_);_;--_) {
        scanf("%d",&n);
        rep(i,1,n) {
            scanf("%d",&a[i]);
        }
        solve(1,n,0);
        rep(i,1,n) printf("%d ",ans[i]);
        puts("");
    }
    return 0;
}
```

---

