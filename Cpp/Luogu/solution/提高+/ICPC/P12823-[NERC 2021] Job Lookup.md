# [NERC 2021] Job Lookup

## 题目描述

Julia 的 $n$ 个朋友想要在他们新搬去的国家创办一家初创公司。他们根据各自的工作内容（从前端到后端）给自己分配了编号 $1$ 到 $n$。他们还估计了一个矩阵 $c$，其中 $c_{ij} = c_{ji}$ 表示从事工作 $i$ 和 $j$ 的人之间每月的平均消息数量。

现在他们想要建立一棵**层级树**。这棵树将是一棵**二叉树**，每个节点包含团队中的一名成员。某位成员将被选为团队领导，并位于根节点。为了确保领导能够轻松联系到任何下属，对于树中的每个节点 $v$，必须满足以下条件：其左子树中的所有成员编号必须小于 $v$，而其右子树中的所有成员编号必须大于 $v$。

当层级树确定后，从事工作 $i$ 和 $j$ 的成员将通过他们在树中节点之间的最短路径进行通信。设该路径长度为 $d_{ij}$，则他们的通信成本为 $c_{ij} \cdot d_{ij}$。

你的任务是找到一棵层级树，使得所有成员对的通信总成本最小化：$\sum_{1 \le i < j \le n} c_{ij} \cdot d_{ij}$。


## 说明/提示

最小的可能总成本为 $566 \cdot 1 + 239 \cdot 1 + 30 \cdot 1 + 1 \cdot 2 + 1 \cdot 2 = 839$：

![](https://cdn.luogu.com.cn/upload/image_hosting/isxizhg5.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
0 566 1 0
566 0 239 30
1 239 0 1
0 30 1 0```

### 输出

```
2 4 2 0```

# 题解

## 作者：FS_NEO (赞：6)

区间 DP 板题。
***

题目要求建立一颗二叉搜索树，很容易想到以编号为下标，进行区间 DP。

设 $cost_{i,j}$ 表示编号在 $[i,j]$ 区间内所有节点，与区间外所有节点的消息数量和；$f_{i,j}$ 表示将 $[i,j]$ 区间内的点建树花费的最小代价，容易得到转移：

$$
f[i][j]=\min_{\;k\in[i,j]\;}\Bigl(\,
      f[i][k-1]+f[k+1][j]+\text{cost}[i][k-1]+\text{cost}[k+1][j]\Bigr)
$$

记录转移路径即可，时间复杂度 $O(n^3)$，细节处理见代码：

```cpp
/*

  2025.6.23

 * Happy Zenith Noises *

*/
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef pair<int,int>P;
typedef long long ll;
const int MAXN=205,mod=1e9+7,inf=1e17;
int n,a[MAXN][MAXN],cst[MAXN][MAXN];
int f[MAXN][MAXN],ffa[MAXN],g[MAXN][MAXN];
void solve(int l,int r,int fa){
	if(l>r)return ;
	ffa[g[l][r]]=fa;
	if(l==r)return ;
	solve(l,g[l][r]-1,g[l][r]);
	solve(g[l][r]+1,r,g[l][r]);
}
signed main(){
	memset(f,0x3f,sizeof(f));
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>a[i][j];
	for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)for(int t=i;t<=j;t++)for(int k=1;k<=n;k++)if(k<i||k>j)cst[i][j]+=a[t][k];
	for(int i=1;i<=n;i++)f[i][i]=0,g[i][i]=i;
	for(int l=2;l<=n;l++){
		for(int i=1;i+l-1<=n;i++){
			int j=i+l-1;
			if(f[i+1][j]+cst[i+1][j]<=f[i][j])f[i][j]=f[i+1][j]+cst[i+1][j],g[i][j]=i;
			if(f[i][j-1]+cst[i][j-1]<=f[i][j])f[i][j]=f[i][j-1]+cst[i][j-1],g[i][j]=j;
			for(int k=i+1;k<j;k++){
				if(f[i][k-1]+cst[i][k-1]+f[k+1][j]+cst[k+1][j]<=f[i][j]){
					f[i][j]=f[i][k-1]+cst[i][k-1]+f[k+1][j]+cst[k+1][j];
					g[i][j]=k;
				}
			}
		}
	}
	solve(1,n,0);
	for(int i=1;i<=n;i++)cout<<ffa[i]<<" ";
	return 0;
}
```

---

## 作者：Null_h (赞：1)

## 前言

一道挺难调的 dp。

## 思路

发现要求构造一棵二叉搜索树，结合数据范围，不难想到使用区间 dp。

那么肯定是令 $f_{l,r}$表示区间 $[l,r]$ 内的数构成一个树的最小贡献，然后枚举根节点转移，大致可以实现 $O(n^3)$ 的算法。

但是如果记录每个子树内部的贡献，那么转移时仍然会产生额外的贡献，而且是与子树具体的形态有关的，难以转移。所以考虑更换状态定义，我们发现对于每一条边，如果知道它的子树内节点情况，可以直接计算出它最后的贡献，所以做出如下定义：

记 $f_{l,r}$ 为区间 $[l,r]$ 内的数构成一棵子树时，子树内的所有边对最终答案造成的贡献，可以算是一种**费用提前计算**。

转移方程为：

$$f_{l,r}=\min_{x\in[l,r]}\{f_{l,x-1}+f_{x+1,r}+w_{l,r,x}\}$$

其中 $w_{l,r,x}$ 表示 $[l,r]$ 构成一棵子树时，如果以 $x$ 为根节点，连向左右子树的两条或一条边造成的贡献，对于其中一条边来说，这个值就是它连向子树内的所有点和子树外的两两造成的贡献，使用二维前缀和不难维护。

最后 dfs 求答案是简单的。

特别注意 $x$ 取 $l$ 和 $r$ 时的边界判断，同时搞清楚二维前缀和查询时的访问坐标。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=210;
int c[N][N],f[N][N],s[N][N],n,ans[N];
int calc(int x1,int y11,int x2,int y2){
	if(x1>x2||y11>y2)return 0;
	return s[x2][y2]+s[x1-1][y11-1]-s[x2][y11-1]-s[x1-1][y2];
}
int val(int l,int r){
	if(l>r)return 0;
	return calc(1,l,l-1,r)+calc(r+1,l,n,r);
}
int w(int l,int r,int x){
	return f[l][x-1]+f[x+1][r]+val(l,x-1)+val(x+1,r);
}
void dfs(int l,int r,int fa){
	if(l==r){
		ans[l]=fa;
		return;
	}
	if(l>r)return;
	for(int x=l;x<=r;x++){
		if(f[l][r]==w(l,r,x)){
			ans[x]=fa;
			dfs(l,x-1,x);
			dfs(x+1,r,x);
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>c[i][j];
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+c[i][j];
			f[i][j]=-1;
		}
		f[i][i]=0;
		f[i+1][i]=0;
		f[i][i-1]=0;
	}
	
	for(int len=2;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			for(int x=l;x<=r;x++){
				if(f[l][r]==-1)f[l][r]=w(l,r,x);
				else f[l][r]=min(f[l][r],w(l,r,x));
			}
		}
	}
	dfs(1,n,0);
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<' ';
	}
	return 0;
}
```

---

