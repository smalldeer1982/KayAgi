# Job Lookup

## 题目描述

Julia's $ n $ friends want to organize a startup in a new country they moved to. They assigned each other numbers from 1 to $ n $ according to the jobs they have, from the most front-end tasks to the most back-end ones. They also estimated a matrix $ c $ , where $ c_{ij} = c_{ji} $ is the average number of messages per month between people doing jobs $ i $ and $ j $ .

Now they want to make a hierarchy tree. It will be a binary tree with each node containing one member of the team. Some member will be selected as a leader of the team and will be contained in the root node. In order for the leader to be able to easily reach any subordinate, for each node $ v $ of the tree, the following should apply: all members in its left subtree must have smaller numbers than $ v $ , and all members in its right subtree must have larger numbers than $ v $ .

After the hierarchy tree is settled, people doing jobs $ i $ and $ j $ will be communicating via the shortest path in the tree between their nodes. Let's denote the length of this path as $ d_{ij} $ . Thus, the cost of their communication is $ c_{ij} \cdot d_{ij} $ .

Your task is to find a hierarchy tree that minimizes the total cost of communication over all pairs: $ \sum_{1 \le i < j \le n} c_{ij} \cdot d_{ij} $ .

## 说明/提示

The minimal possible total cost is $ 566 \cdot 1+239 \cdot 1+30 \cdot 1+1 \cdot 2+1 \cdot 2=839 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666J/7d043f0dc31fa1bc60f31358d0ccffe9104138cc.png)

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

## 作者：DaiRuiChen007 (赞：5)

# CF1666J 题解



## 思路分析

记 $dp_{l,r}$ 表示区间 $[l,r]$ 中所有点**贡献**之和的最小值，我们枚举 $dp_{l,r}$ 中的根 $k$，则 $[l,k)$ 为 $k$ 的左子树，$(k,r]$ 为 $k$ 的右子树。

一个显然的想法是把 $d_{i,j}$ 拆分到每条边上统计，每条边对答案产生多少贡献那么每次合并两棵子树的时候产生的新贡献为：左子树内每个点到左子树外每个点的通话数加上右子树内每个点到右子树外每个点的通话数。

假设我们记 $C_{\mathbf {I_1},\mathbf {I_2}}$ 为 $x\in \mathbf {I_1},y\in\mathbf{I_2}$ 的 $c_{x,y}$ 的和，其中 $\mathbf{I_1},\mathbf{I_2}$ 为两个区间，可以通过二维前缀和快速查询，那么状态转移方程如下：
$$
dp_{l,r}=\max_{k=l}^r\{dp_{l,k-1}+dp_{k+1,r}+(C_{[l,k),[1,l)}+C_{[l,k),[k,n]})+(C_{(k,r],[1,k]}+C_{(k,r],(r,n]})\}
$$
构造方案时记录每个 $[l,r]$ 转移时最优的 $k$，递归计算 $[l,k)$ 和 $(k,r]$ 子树的形态即可。

时间复杂度 $\Theta(n^3)$。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
const int MAXN=201,INF=1e17;
int dp[MAXN][MAXN],rt[MAXN][MAXN],c[MAXN][MAXN],sum[MAXN][MAXN],fa[MAXN];
inline void dfs(int l,int r,int f) {
	if(l>r) return ;
	int k=rt[l][r];
	fa[k]=f;
	dfs(l,k-1,k),dfs(k+1,r,k);
}
inline int cnt(int r1,int r2,int c1,int c2) {
	if(r1>r2||c1>c2) return 0;
	return sum[r2][c2]-sum[r2][c1-1]-sum[r1-1][c2]+sum[r1-1][c1-1];
}
signed main() {
	int n;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			scanf("%lld",&c[i][j]);
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+c[i][j];
		}
	}
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) dp[i][j]=INF;
	for(int i=1;i<=n;++i) dp[i][i]=0,rt[i][i]=i;
	for(int len=1;len<n;++len) {
		for(int l=1,r=l+len;r<=n;++l,++r) {
			for(int k=l;k<=r;++k) {
				int val=cnt(l,k-1,1,l-1)+cnt(l,k-1,k,n)+
						cnt(k+1,r,1,k)+cnt(k+1,r,r+1,n)+
						(k==l?0:dp[l][k-1])+(k==r?0:dp[k+1][r]);
				if(val<dp[l][r]) rt[l][r]=k,dp[l][r]=val;
			}
		}
	}
	dfs(1,n,0);
	for(int i=1;i<=n;++i) printf("%lld ",fa[i]);
	puts("");
	return 0;
}
```



---

## 作者：hyman00 (赞：4)

# CF1666J

树形+区间dp

设 $dp_{l,r}$ 为 l 到 r 的区间最小代价。

那么枚举这一段的根 k，于是
$$
dp_{l,r}=\min_{k=l}^r{dp_{l,k-1}+dp_{k+1,r}+\sum_{i\in[l,k-1]}(\sum_{j\in[0,l-1]}a_{i,j}+\sum_{j\in[k,n-1]}a_{i,j})+\sum_{i\in[k+1,r]}(\sum_{j\in[0,k]}a_{i,j}+\sum_{j\in[r+1,n-1]}a_{i,j})}
$$

后面的可以用二维前缀和做。

```c++
int calc(int l1,int r1,int l2,int r2){
	re sum[r1][r2]-sum[l1-1][r2]-sum[r1][l2-1]+sum[l1-1][l2-1];
}
```
完整代码：
```c++
int a[202][202];
pii dp[202][202];
int sum[202][202];
int calc(int l1,int r1,int l2,int r2){
	re sum[r1][r2]-sum[l1-1][r2]-sum[r1][l2-1]+sum[l1-1][l2-1];
}
int ans[202];
void getans(int l,int r,int p){
	if(r<l)re;//cout<<l<<" "<<r<<" "<<p<<"\n";
	ans[dp[l][r].S]=p;
	getans(l,dp[l][r].S-1,dp[l][r].S);
	getans(dp[l][r].S+1,r,dp[l][r].S);
}
void run(){
	int n;
	cin>>n;
	rept(i,1,n+1)rept(j,1,n+1){
		cin>>a[i][j];
		sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
	}
	rept(i,1,n+1)rept(j,1,n+1)dp[i][j]={0,i};
	rept(i,1,n+1)dp[i][i]={0,i};
	rept(d,1,n){
		for(int l=1,r=d+1;r<=n;l++,r++){
			dp[l][r]={INF,INF};
			rept(k,l,r+1){
				int cc=dp[l][k-1].F+dp[k+1][r].F;
				cc+=calc(l,k-1,1,l-1);
				cc+=calc(l,k-1,k,n);
				cc+=calc(k+1,r,1,k);
				cc+=calc(k+1,r,r+1,n);
				Mi(dp[l][r],{cc,k});
			}
		}
	}
	getans(1,n,0);
	rept(i,1,n+1)cout<<ans[i]<<" ";
	cout<<"\n";
}
```
注意记录路径。


---

## 作者：Redamancy_Lydic (赞：0)

被迫来写篇题解。

首先，第一个要求我们只需要在递归构造的时候保证子树对应区间连续即可，现在考虑第二个要求。

就题目中的二叉树而言，想要确定其结构，我们只需要关注这段区间，即这棵子树根节点的编号，又因为子树区间连续，所以我们不难想到区间动态规划。

设 $dp_{l,r}$ 表示 $l\sim r$ 这段区间的答案，结合上文所说，我们可以枚举区间断点 $k$ 表示这段区间的根节点，这样 $dp_{l,r}$ 可以由 $dp_{l,k-1}$ 和 $dp_{k+1,r}$ 合并过来。

具体的，我们可以把 $d_{i,j}$ 拆分开来，以左子树为例，其中的每一条边都会和子树外的每一条边产生贡献，即 $\sum_{i=l}^{k-1}(\sum_{j=1}^{l-1}c_{i,j}+\sum_{j=k}^{n}c_{i,j})$，右子树同理。

输出的话我们可以记录最优状态下的根节点，记录一下，递归构建树。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=3e3+100;
const int inf=3e17+7;
int n,c[300][300];
int dp[300][300],ans[300][300];
int sum[300][300],fa[300];
inline int ask(int l1,int r1,int l2,int r2)
{if(l1>r1||l2>r2)return 0;return sum[r1][r2]-sum[l1-1][r2]-sum[r1][l2-1]+sum[l1-1][l2-1];}
void dfs(int l,int r,int rt)
{
    if(l>r)return ;
    int k=ans[l][r];
    fa[k]=rt;
    dfs(l,k-1,k);
    dfs(k+1,r,k);
}
signed main()
{
#ifdef Lydic
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);

//  #else
//   	freopen("Stone.in","r",stdin);
//   	freopen("Stone.out","w",stdout);
#endif
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            c[i][j]=read();
            sum[i][j]=c[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
        }
    for(int i=1;i<n;i++)
        for(int j=i+1;j<=n;j++)
            dp[i][j]=inf;
    for(int i=1;i<=n;i++)
        ans[i][i]=i;
    for(int len=1;len<n;len++)
    {
        for(int l=1;l<=n-len;l++)
        {
            int r=l+len;
            for(int k=l;k<=r;k++)
            {
                int res=ask(l,k-1,1,l-1)+ask(l,k-1,k,n)+ask(k+1,r,1,k)+ask(k+1,r,r+1,n)+dp[l][k-1]+dp[k+1][r];
                if(res<dp[l][r])
                {
                    dp[l][r]=res;
                    ans[l][r]=k;
                }
            }
        }
    }
    dfs(1,n,0);
    for(int i=1;i<=n;i++)printf("%lld ",fa[i]);
	return 0;
}
```

---

## 作者：OIerBoy (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1666J) 
## 前言
显然，由题易知每棵子树的节点编号是一段连续的区间，所以可以我们可以用区间 DP 做这道题。
## 思路
我们知道树上两点之间只有一条边，所以我们没有必要去求两点之间的路径，我们要将 $c_{i,j},d_{i,j}$ 转换为 $c_{i,j}$，$\left(\begin{matrix}\underbrace{1+1+\dots+1}\\d_{i,j}\end{matrix}\right)$ 其中的 $1$ 则是代表每一条边，把费用分配到每一条边。

怎么判断两个点要不要经过一条边呢，只需要看一颗子树之中，在子树里面的点与在子树外面的点是必然经过子树根节点的，所以我们每次计算所有子树里面与外面的点经过子树根节点的总和就可以了。

设 $f_{l,r}$ 表示 $l$ 到 $r$ 区间的最小花费。


转移时枚举这一段区间的根节点 $k$：

$f_{l,r}=\min(f_{l,r},f_{l,k-1}+f_{k+1,r}+\sum_{i=l}^{k-1}\left(\sum_{j=1}^{l-1}c_{i,j}+\sum_{j=k}^nc_{i,j}\right)+\sum_{i=k+1}^r\left(\sum_{j=1}^kc_{i,j}+\sum_{j=r+1}^nc_{i,j}\right)$


而后面的 $\sum_{i=l}^{k-1}\left(\sum_{j=1}^{l-1}c_{i,j}+\sum_{j=k}^nc_{i,j}\right)+\sum_{i=k+1}^r\left(\sum_{j=1}^kc_{i,j}+\sum_{j=r+1}^nc_{i,j}\right)$ 就完全可以用二维前缀和来做。

这样我们就可以得到一个 $O\left(n^3\right)$ 时间复杂度的算法了。
## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000][1000],pre[1000][1000],f[1000][1000],y[1000][1000],fa[1000];
void find(int now,int l,int r){//查找每一个点的父节点
	if(l==r)return;
	fa[y[l][now-1]]=now;
	fa[y[now+1][r]]=now;
	if(now>1)find(y[l][now-1],l,now-1);
	if(now<n)find(y[now+1][r],now+1,r);
}
int main(){
	memset(f,0x3f,sizeof(f));
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)//二位前缀和
		for(int j=1;j<=n;j++)
			pre[i][j]=a[i][j]+pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1];
	for(int i=1;i<=n;i++)f[i][i]=0,y[i][i]=i;//对l=r的进行初始化
	for(int k=2;k<=n;k++){//枚举长度，保证算法的可行性
		for(int l=1;l<=n-k+1;l++){//枚举左节点
			long long r=l+k-1;//计算右节点
			for(int m=l;m<=r;m++){//枚举子树根节点
				long long ls=pre[m-1][n]-pre[l-1][n]-(pre[m-1][m-1]-pre[l-1][m-1]-pre[m-1][l-1]+pre[l-1][l-1]);
				long long rs=pre[r][n]-pre[m][n]-(pre[r][r]-pre[m][r]-pre[r][m]+pre[m][m]);//二位前缀和求值
				long long ll=f[l][m-1],rr=f[m+1][r];
				if(m==l)ll=0,ls=0;if(m==r)rr=0,rs=0;//特判边界情况
				if(f[l][r]>=ll+rr+ls+rs){
					f[l][r]=ll+rr+ls+rs;
					y[l][r]=m;//记录下此子树的根节点
				}
			}
		}
	}
	find(y[1][n],1,n);
	for(int i=1;i<=n;i++)cout<<fa[i]<<" ";
	return 0;//完结撒花
}
```

---

