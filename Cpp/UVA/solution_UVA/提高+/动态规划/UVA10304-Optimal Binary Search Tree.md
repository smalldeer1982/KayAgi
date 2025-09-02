# Optimal Binary Search Tree

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1245

[PDF](https://uva.onlinejudge.org/external/103/p10304.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10304/8240dddbc7a394a9919bfe12ea1df0e5a38b12ed.png)

## 样例 #1

### 输入

```
1 5
3 10 10 10
3 5 10 20```

### 输出

```
0
20
20```

# 题解

## 作者：HPXXZYY (赞：7)

$\color{blue}{\texttt{[Problem]}}$

最优排序二叉树问题（`OBST`，全称如题）的模板题。

给定 $n$ 个点的点权 $d_{i}(1 \leq i \leq n)$，你需要给它们建一棵排序二叉树，记第 $i$ 个点的深度为 $p_{i}(1 \leq i \leq n)$，要求这棵排序二叉树：

$$\sum\limits_{i=1}^{n} p_i \times d_i$$

的值最小。这个值我们称为最小检索次数。

注意，输入平衡树的高度最小，但是它不一定是最优的（甚至可能不如一条链优）。

保证 $d_{i} \leq d_{i+1}(1 \leq i <n)$。

----------------------------------------

$\color{blue}{\texttt{[Soluntion]}}$

我们可以先确定根，再确定左右子树，因为题目保证有序，所以这样做是肯定对的。

记 $f_{i,j}$ 表示为区间 $(i,j)$ 建一棵排序二叉树的最小检索次数。考虑如何计算它。

假设 $k(i \leq k \leq j)$ 为根，它的深度为 $0$，贡献为 $0 \times d_k=0$。左子树 $(i,k-1)$ 在单独作为一棵树时的最小检索次数为 $f_{i,k-1}$，但是因为现在的根是 $k$ 了，所以它们各自的深度都增加了 $1$，所以总的检索次数要加上：

$$d_{i}+d_{i+1}+d_{i+2}+\cdots +d_{k-1}=\sum\limits_{t=i}^{k-1} d_t$$

右子树类似，记 $c_{i,j}=\sum\limits_{t=i}^{j} d_t$，则我们有如下转移式：

$$\begin{aligned}
f_{i,j}&=\min\{f_{i,k-1}+f_{k+1,j}+c_{i,j}-d_{k}\} \\
&=\min\{f_{i,k-1}+f_{k+1,j}-d_{k}\}+c_{i,j}\\
(&i \leq k \leq j)
\end{aligned}$$

直接转移是 $O(n^3)$ 的，可以用四边形不等式优化到 $O(n^2)$，详见参考代码。

----------------------------------------

$\color{blue}{\texttt{[code]}}$

```cpp
int w[260][260],e[260];
int n,f[260][260],p[260];
inline int cost(int a,int b,int c){
	return p[b]-p[a-1]-e[c];
}
int main(){
//	freopen("t1.in","r",stdin);
	while (~scanf("%d",&n)&&n){
		memset(p,0,sizeof(p));
		memset(w,0,sizeof(w));
		memset(f,127,sizeof(f));
		for(int i=1;i<=n;i++){
			scanf("%d",&e[i]);
			p[i]=p[i-1]+e[i];
		}
		for(int i=1;i<=n;i++)
			f[i][i]=0,w[i][i]=i;
		for(int i=1;i<=n;i++)
			f[i+1][i]=f[i][i-1]=0;
		for(int L=2;L<=n;L++)
			for(int j=L;j<=n;j++){
				register int i=j-L+1;
				for(int k=w[i][j-1];k<=w[i+1][j];k++)
					if (f[i][k-1]+f[k+1][j]+cost(i,j,k)<=f[i][j]){
						f[i][j]=f[i][k-1]+f[k+1][j]+cost(i,j,k);
						w[i][j]=k;//四边形不等式中的记录决策点 
					}
			}
		printf("%d\n",f[1][n]);
	}
	return 0;
}
```

---------------------------------

算法：`dp`；`四边形不等式优化`。

---

## 作者：OIer_ACMer (赞：3)

~~这就是四边形优化的题？！~~

------------
注：本题由于较为模板，所以笔者不会赘述太多的证明和原理，望周知！

------------
## 大致思路：
在开始之前，我们先分析一遍题意：给 $n$ 的数字建立一棵排序二叉树，要求从检索的次数最小。

很快，我们就知道这是一道排序二叉树的模板题。根据排序二叉树的递归定义，**我们可以先选根，然后递归建立左右子树**。

同时，我们也可以知道：排序二叉树的做法大多是 DP。所以我们设 $dp_{i,j}$ 表示从 $i$ 到 $j$ 所建立的排序二叉树的最小检索次数。当选择 $k$ 作为根结点之后，其总检索次数为 $dp_{i,k - 1}$，但在作为 $k$ 的子树后，所有节点的深度都要增加 $1$，因此总检索次数要加上 $sum_{i,j} - a_k$。还有，其实这道题**根本不用四边形不等式优化**，因为 $n$ 最多只有 $250$。

综上，转移方程如下：

$dp_{i,j} = \min(dp_{i,j}, dp_{i,k - 1} + dp_{k + 1,j} - sum_{i,j} - a_k)$。

------------
## 代码如下：

```c+
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int MAXN = 255;
const int INF = 0x3f3f3f3f;
int a[MAXN], sum[MAXN], dp[MAXN][MAXN];
int n;
int main()
{
    while (scanf("%d", &n) != EOF)
    {
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            a[i] = read();
            sum[i] = sum[i - 1] + a[i];
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 2; i <= n; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                dp[j][i] = INF;
                for (int k = j; k <= i; k++)
                {
                    dp[j][i] = min(dp[j][i], dp[j][k - 1] + dp[k + 1][i] + sum[i] - sum[j - 1] - a[k]);
                }
            }
        }
        cout << dp[1][n] << endl;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122751758)

---

## 作者：KKarshilov (赞：2)

题目的意思还是比较明显的，Huffman编码意义下的最优二叉树。

二叉树的权值已经给出，每个节点的访问代价就是深度。

真正的访问代价就是节点权值 * 节点深度

现在考虑二叉树的性质

1.∀ u ∈ leftson(x) val[x] > val[u]

2.∀ u ∈ rightson(x) val[x] < val[u]

题目给出的数列(val)是有序的，结合上述特点，你发现了什么？

假设我们以i为根，1~i-1就是左子树，i+1~n就是右子树

由此得出dp方程：f[i][j]表示从i到j的最优二叉树

枚举一个根k，i <= k <= j。

当k为根时相当于i~k-1整体下移一层，k+1~j也整体下移一层

那么，答案就是f[i][k-1] + f[k+1][j] + sum[i][j] - val[k]

一个n^3的区间dp足以AC，不过这题同样可以用四边形不等式优化

不过我~~写不来~~没写就是了

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300;
const int INF = 0x3f3f3f3f;
int f[MAXN][MAXN], s[MAXN], c[MAXN], n;
void init() {
    s[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", c + i);
        s[i] = s[i - 1] + c[i];
    }
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j++)
            f[i][j] = INF;
    for(int i = 1; i <= n; i++) f[i][i - 1] = f[i + 1][i] = 0;
}
signed main() {
    while(scanf("%d", &n) != EOF) {
        init();
        for(int k = 0; k < n; k++) {
            for(int i = 1; i + k <= n; i++) {
                for(int j = i; j <= i + k; j++) {
                    int res = f[i][j - 1] + f[j + 1][i + k] + s[i + k] - s[i - 1] - c[j];
                    f[i][i + k] = min(f[i][i + k], res);
                }
            }
        }
        printf("%d\n", f[1][n]);
    }
    return 0;
}
```

---

## 作者：Jorisy (赞：0)

不难想到区间 dp。

下面令 $s_{l,r}=\sum\limits_{i=l}^re_i$。

令 $f_{l,r}$ 表示区间 $[l,r]$ 构成 BST 的最小代价。

考虑枚举根节点 $k\in[l,r]$。

对于 $[l,k],[k,r]$ 合并，可以发现合并时两棵子树内的节点深度都加一，对代价的贡献就恰好多了 $s_{l,r}-e_k$。

故状态转移方程为 $f_{l,r}=\min\{f_{l,k-1}+f_{k+1,r}+s_{l,r}-e_k\}$，时间复杂度 $O(n^3)$，足以通过本题。

此外，注意到对于端点 $l\le l'\le r'\le r$，有 $s_{l,r}+s_{l',r'}\ge s_{l',r}+s_{l,r'}$，满足四边形不等式，故可以以此优化 dp。时间复杂度优化为 $O(n^2)$。
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[255],sum[255],f[255][255],des[255][255];

void sol()
{
    memset(f,0x3f,sizeof(f));
    memset(a,0,sizeof(a));
    memset(des,0,sizeof(des));
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
        des[i][i]=i;
    }
    for(int i=1;i<=n+1;i++)
    {
        for(int j=0;j<=i;j++)
        {
            f[i][j]=0;
        }
    }
    for(int len=2;len<=n;len++)
    {
        for(int l=1;l+len-1<=n;l++)
        {
            int r=l+len-1;
            for(int k=des[l][r-1];k<=des[l+1][r];k++)
            {
                if(f[l][r]>f[l][k-1]+f[k+1][r]+sum[r]-sum[l-1]-a[k])
                {
                    f[l][r]=f[l][k-1]+f[k+1][r]+sum[r]-sum[l-1]-a[k];
                    des[l][r]=k;
                }
            }
        }
    }
    cout<<f[1][n]<<endl;
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    while(cin>>n) sol();
    return 0;
}
```

---

## 作者：ybc2025chenyuyang (赞：0)

# UVA10304 Optimal Binary Search Tree题解
## 题面解释
在本题中二叉搜索树的特点是每个节点的值比它的左子树上所有节点的值大，比右子树上所有节点的值要小。二叉搜索树的中序遍历是从小到大排列的。

题面上的第三个样例的最优二叉搜索树的总成本为 $5\times 2+10\times 1=20$。

题目给的元素已经按照从小到大的排列，可以方便的组成一颗二叉搜索树。
## 分析
设 $dp[i][j]$ 是区间 $[i,j]$ 的元素组成的二叉搜索树的最小值。我们可以把区间 $[i,j]$ 分成两部分：$[i,k-1]$ 和 $[k+1,j]$，$k$ 在 $i$ 和 $j$ 之间滑动。

我们在区间 $[i,j]$ 内建立一棵二叉树，$k$ 是根结点。不难发现，这正好就是区间DP的精髓，状态转移方程式如下。

$dp[i][j]=min\left \{ dp[i][k-1]+dp[k+1][j]+w(i,j)-e[k] \right \}$

其中 $w(i,j)$ 为区间和，$w(i,j)=\sum_{k=i}^{j}f(e_{k})$。当我们把左右子树连在根结点上的时候，本身的深度增加 $1$，所以每一个元素都得多计算一次，这样就解决了 $cos(e_{i})$ 的计算。

最后，因为根结点 $k$ 的层数是 $0$，所以减去根结点的值是 $e[k]$。

由于 $w(i,j)$ 符合四边形不等式的优化条件，所以 $dp[i][j]$ 可以用四边形不等式优化，此时算法的时间复杂度是 $O(n^2)$。

---

## 作者：Unnamed114514 (赞：0)

简单的题目。

首先容易想到子树对应的点一定连续，所以可以考虑区间 dp。

定义 $dp_{l,r}$ 表示 $[l,r]$ 所构造的 BST 的答案，最后显然输出 $dp_{1,n}$。

容易想到枚举根节点，其他点的相对深度就会 $+1$，那么可以得到 $dp_{l,r}\gets\min\{dp_{l,k-1}+dp_{k+1,r}+\sum\limits_{i=l}^{k-1}e_i+\sum\limits_{i=k+1}^r e_i\}$，然后里面那一坨直接打前缀和就行了。

说句闲话，时间复杂度是 $O(n^3)$，但是你会发现它~~在四边形不等式的练习题里面~~满足四边形不等式，所以就优化到 $O(n^2)$ 了。

---

