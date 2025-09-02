# Recovering BST

## 题目描述

Dima the hamster enjoys nibbling different things: cages, sticks, bad problemsetters and even trees!

Recently he found a binary search tree and instinctively nibbled all of its edges, hence messing up the vertices. Dima knows that if Andrew, who has been thoroughly assembling the tree for a long time, comes home and sees his creation demolished, he'll get extremely upset.

To not let that happen, Dima has to recover the binary search tree. Luckily, he noticed that any two vertices connected by a direct edge had their greatest common divisor value exceed $ 1 $ .

Help Dima construct such a binary search tree or determine that it's impossible. The definition and properties of a binary search tree can be found [here.](https://en.wikipedia.org/wiki/Binary_search_tree)

## 说明/提示

The picture below illustrates one of the possible trees for the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025D/a6281ebfc3addc046e3a216e978640a7d00d938f.png)The picture below illustrates one of the possible trees for the third example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025D/422d22e6560dde35033dafdd73125c60e4d294d8.png)

## 样例 #1

### 输入

```
6
3 6 9 18 36 108
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2
7 17
```

### 输出

```
No
```

## 样例 #3

### 输入

```
9
4 8 10 12 15 18 33 44 81
```

### 输出

```
Yes
```

# 题解

## 作者：C_末_Dragon (赞：13)

看dalao们都是用 $f(l,r,0)$ 保存以 $l-1$ 为父亲节点，区间 $[l,r]$ 是否有合法的构造，$f(l,r,1)$ 保存以 $r+1$ 为父亲节点，区间 $[l,r]$ 是否有合法的构造。juruo我对于边界问题傻傻搞不清，所以我就稍稍改了一下。

$f(l,r,0)$ 保存以 $l$ 为父亲节点，区间 $[l,r]$ 是否有合法的构造，$f(l,r,1)$ 保存以 $r$ 为父亲节点，区间 $[l,r]$ 是否有合法的构造。

初始化时，我们对于每一个 $i$ 都将 $f(i,i,0)$ 和 $f(i,i,1)$ 都保存为 $1$，因为以单个节点的空树是一定存在的。

区间DP时我们进行的是一个合并操作：

当 $f(i,k,0)=1$ 且 $f(k+1,j,0)=1$ 时，我们就有两棵树。假设如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/8vohkan4.png)

当 $k$ 能与 $j$ 相连时，我们能构成一颗新树，如下左图，即 $f(i,j,0)=1$；当 $i$ 能与 $k+1$ 相连时，我们也能构成一颗新树，如下右图，即 $f(i,j,1)=1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ruj3mhpw.png)

最后我们只要检查对于每个 $i$，$f(1,i,1)$ 与 $f(i,n,0)$ 是否均为1，一旦有就输出 $Yes$，若没有，就输出 $No$。

## Code
```cpp
#include<cstdio>
#include<iostream>
using namespace std;

inline int read() {
	int x=0;
	char ch=getchar();
	for(; ch<'0'||ch>'9'; ch=getchar());
	for(; ch>='0'&&ch<='9'; x=(x<<1)+(x<<3)+(ch^48),ch=getchar());
	return x;
}

const int N=7e2+10;
int a[N];
bool f[N][N][2],b[N][N];

int gcd(int a,int b) {
	return b?gcd(b,a%b):a;
}

int main() {
	int n=read();
	for(register int i=1; i<=n; ++i) {
		a[i]=read();
	}//读入
	for(register int i=1; i<=n; ++i) {
		f[i][i][0]=f[i][i][1]=1;
	}//初始化
	for(register int i=2; i<=n; ++i) {
		for(register int j=1; j<i; ++j) {
			b[i][j]=gcd(a[i],a[j])>1;
		}
	}//预处理两个点是否能相连，注意i>j
	for(register int l=1; l<n; ++l) {
		for(register int i=1; i<=n-l; ++i) {
			int j=i+l;
			for(register int k=i; k<j; ++k) {
				if(f[i][k][0]&&f[k+1][j][1]) {
					f[i][j][0]|=b[j][k];
					f[i][j][1]|=b[k+1][i];
				}
			}
		}
	}//DP
	bool flag=0;
	for(register int i=1; i<=n; ++i) {
		flag|=f[1][i][1]&f[i][n][0];
	}
	if(flag) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	return 0;
}
```


------------

p.s.图画的有点丑，dalao们见笑了。

---

## 作者：ysner (赞：7)

### 题面

给出一些数，若要求两数$gcd>1$才能连边，询问他们是否能构成一棵**二叉搜索树**。

 - $n\leq700$
 
### 解析
如果没注意到**二叉搜索树**这一条件，这题绝对做不出来。。。

二叉搜索树的定义是，对同一节点，左儿子权值比它小，右儿子权值比它大。
于是有一个很重要的性质，**中序遍历上点权从小到大**。

可以得出推论：

 - 一棵子树（在中序遍历上可视为一段区间$[l,r]$），把它作为左儿子，根结点的父亲一定为$r+1$；把它作为右儿子，根节点父亲一定为$l-1$。

然而注意到，如果暴力设$f[i][j][k][0/1]$表示以$k$为根，$[i,j]$作为其左/右儿子是否合法是会$MLE$，而且有许多无效状态。

于是需应用上面推论，设两个判合法性的数组：

 - $L[i][j]$表示区间$[i,j-1]$作为$j$的左儿子是否合法
 - $R[i][j]$表示区间$[i+1,j]$作为$j$的右儿子是否合法

转移：

设$k$为区间$[i,j]$的根，

如果$L[i][k]=1$且$r[k][j]=1$，则该状态合法，可以转移；

没地方转移了就$puts("Yes")$。

如果$k$可以与$l-1$相连，说明以$l-1$为根，$[l,r]$为右儿子的状态合法。

如果$k$可以与$r+1$相连，说明以$r+1$为根，$[l,r]$为左儿子的状态合法。
```
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define re register
#define il inline
#define fp(i,a,b) for(re int i=a;i<=b;i++)
#define fq(i,a,b) for(re int i=a;i>=b;i--)
using namespace std;
il ll gi()
{
  re ll x=0,p=1;
  re char ch=getchar();
  while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
  if(ch=='-') p=-1,ch=getchar();
  while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
  return p*x;
}
const int N=710;
int n,a[N],f[N][N],L[N][N],R[N][N];
int main()
{
  ios::sync_with_stdio(false);
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i],L[i][i]=R[i][i]=1;
  fp(i,1,n) fp(j,i,n) if(__gcd(a[i],a[j])>1) f[i][j]=f[j][i]=1;
  fq(l,n,1)
    fp(r,l,n)
    fp(k,l,r)
    if(L[l][k]&&R[k][r])
      {
	if(l==1&&r==n) {puts("Yes");return 0;}
	if(f[l-1][k]) R[l-1][r]=1;
	if(f[k][r+1]) L[l][r+1]=1;
      }
  puts("No");
  return 0;
}
```
安利[蒟蒻博客](https://www.cnblogs.com/yanshannan/p/9505936.html)

---

## 作者：Strelitzia (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF1025D)

---

首先这道题容易想到 $O(n ^ 4)$ 的 $dp$。

定义 $dp_{i,j,k}$ 意为在 $[l,r]$ 这个区间，以 $k$ 为根节点，枚举子树的根节点，判断是否不互质。

但这样，即会超时，又会超空间，肯定是不行的。

再从题目里面找条件，这是个二叉搜索树，给出的序列是中序遍历。

二叉搜索树的性质有什么，左子树上所有结点的值均小于它的根结点的值，

右子树上所有结点的值均大于它的根结点的值。

所以我们可以先假定一个区间 $[l,r]$ 可以合法的构造，那么这棵子树的父亲节点，

一定是编号为 $l-1$ 或 $r + 1$ 的节点，这是我们优化 $dp$ 的重点。

我们定义 $dp_{i,j,0/1}$，$i,j$ 是这个区间，0/1 如果是 0，

说明$[i + 1,j]$ 的父节点是 $i$，如果是 1，说明$[i,j - 1]$ 的父节点是 $j$。

然后就根据定义 $dp$ 一下，这个题的难点是想到区间的父节点是什么，其他都还好。


```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
template<typename T>void read(T &x) {
	T f = 1;x = 0;char s = getchar();
	while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int maxn = 705;
int n,a[maxn];
int dp[maxn][maxn][2],gcdd[maxn][maxn];
int gcd(int x,int y) {
	return y == 0 ? x : gcd(y,x % y);
}
int main () {
	read(n);
	for (int i = 1 ; i <= n ; ++ i) read(a[i]);
	for (int i = 1 ; i <= n ; ++ i)
		for (int j = 1 ; j <= n ; ++ j)
			gcdd[i][j] = gcd(a[i],a[j]);
	for (int i = 1 ; i <= n ; ++ i) dp[i][i][0] = dp[i][i][1] = 1;
	for (int len = 1 ; len <= n ; ++ len) {
		for (int i = 1 ; i + len - 1 <= n ; ++ i) {
			int ed = len + i - 1;
			for (int j = i ; j <= ed ; ++ j) {
				if(dp[i][j][0] && dp[j][ed][1]) {
					if(i == 1 && ed == n) {
						puts("Yes");
						return 0;	
					}
					if(gcdd[i - 1][j] != 1) dp[i - 1][ed][1] = 1;
					if(gcdd[ed + 1][j] != 1) dp[i][ed + 1][0] = 1;
				}
			}
		}
	}
	puts("No");
	return 0;
}
```

---

## 作者：pomelo_nene (赞：4)

这是一个可行性问题。考虑 $\operatorname{BST}$ 的性质，左子树所有节点的权值小于根节点，右子树所有节点的权值大于根节点。又考虑到序列给出的特殊性，我们不难想到将数列抽象为区间，判断可行性。

不难想到 $O(n^4)$ 的算法，枚举可能的根，在左区间和右区间枚举左右子树节点进行判断。

考虑优化这个区间 dp 的判断，显然我们需要推出一些性质。这道题的关键就在于，区间 $[l,r]$ 要么是 $[1,n]$，要么是作为 $l-1$ 的右子树，要么是作为 $r+1$ 的左子树。

重新定义 $dp_{i,j,0}$ 为区间 $[i,j-1]$ 内所有节点能否作为 $j$ 的左子树，$dp_{i,j,1}$ 为区间 $[i+1,j]$ 内所有节点能否作为 $i$ 的右子树。

返回去看一下是否能够判断。我们发现区间 $[i,j]$ 能够转移，当且仅当存在一个 $k \in [i,j]$，使得 $dp_{i,k,0} ∧ dp_{k,j,1}$（意为 $k$ 为根，左右子树合法）。

接下来我们需要拓展的区间就是 $[i-1,j]$ 和 $[i,j+1]$。

- 对于第一个区间，能够转移的条件是 $\gcd(a_{i-1},a_k) \neq 1$；   
- 对于第二个区间，能够转移的条件是 $\gcd(a_k,a_{k+1}) \neq 1$。

根据题目要求可以得到。

这样我们就少了一个判断的 $O(n)$，总时间复杂度 $O(n^3)$。

---

## 作者：ezoixx130 (赞：4)

看来大家写的都是正解啊。。

只有我一个场上写了时间和空间复杂度都不对然而过掉的乱搞的吗？？？

我的做法是这样的：设计一个check(l,r,root)表示当前子树的根为root时，是否能用l~r之间的数构造出一个满足题意的子树。

实现很简单，就是暴力枚举l~r之间那一个数作儿子，再递归判断即可。

然而这样太暴力了，随随便便都能卡到TLE。

但是我们发现，实际上我们在搜索的过程中有大量重复搜索的地方，于是我们加上一个记忆化。

然后我们发现开700的三维数组会MLE。

由于这个数组只用存储bool值，那我们就把它开成bitset。

接着这个做法就过了。

代码：
```
#include<bits/stdc++.h>
using namespace std;

int n,a[701];
bitset<701> vis2[701][701],ans[701][701];
bool ok[701][701];

int check(int l,int r,int root)
{
    if(r<l)return true;
    if(l==r)return ok[l][root];
    if(vis2[l][r][root])return ans[l][r][root];
    for(int i=l;i<=r;++i)
        if(ok[i][root] &&check(l,i-1,i) && check(i+1,r,i))
        {
            vis2[l][r][root]=1;
            ans[l][r][root]=1;
            return true;
        }
    vis2[l][r][root]=2;
    return false;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",a+i);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
            ok[i][j]=__gcd(a[i],a[j])!=1;
        ok[0][i]=true;
        ok[i][0]=true;
    }
    if(check(1,n,0))puts("Yes");else puts("No");
}
```

---

## 作者：zimujun (赞：3)

这题可以出到 $1.5 \times 10^3$ 的，怎么没人写 $O(n^3/\omega)$ 的题解啊。

传统的做法是注意到有一个显然的 $O(n^3)$ 状态 $O(n)$ 转移的区间 dp，随后发现其中有一维状态不是必要记的，于是就优化到了 $O(n^2)$ 状态。但是到了这一步还是有优化空间，因为这时候状态都是一个 `bool` 变量，可以尝试压位做到 $O(n/\omega)$ 转移。

具体的，预处理与每个数不互质的下标集合，然后再在 dp 的过程中动态维护当位置 $i$ 作为左/右端点时，可以作为对应的右/左端点的位置的集合，[码](https://codeforces.com/contest/1025/submission/151374042)。

---

## 作者：Azazеl (赞：2)

### CF1025D Recovering BST 题解  

[或许好一点的阅读体验](https://www.cnblogs.com/Azazel/p/13479793.html)

------
#### 题意  

>$\ \ \ \ \ \ $给定一个长度为 $n$ （ $2\le n\le 700$ ）的升序排列。问是否有办法用这几个数作为点权构成一棵 BST 使得这棵 BST 所有边连接的两点的点权互质。  

---

#### 题解 

$~~~~$  我们知道 BST 的中序遍历一定是升序排列的，因此这个序列就是一棵二叉树的中序遍历。而当我们钦定一个升序区间中某一个节点为该区间子树的根节点时，这个子树根节点的左右子树就确定了。而把这个操作逆向过来，就是一个区间 DP 的过程。

$~~~~$ 本题有一些不一样，看到 $n$ 很小，可以往 $\mathcal{O(n^3)}$ 的算法去想。  

$~~~~$ 如果一开始没有想到，可以考虑用暴力一点的算法优化上来。不难想到一个 $n^4$ 的 DP ，设： $dp_{i,j,k}$ 表示区间 $[l,r]$ 以整个序列的第 $k$ 个元素为根时该区间的合法性。  

$~~~~$ 很容易想到如何转移，用 $n^2$ 枚举区间，$n$ 枚举当前区间子树的根节点，$n$ 枚举左右区间是否有满足条件的根节点即可。  

$~~~~$ 那我们怎么优化这个过程呢？由于 $n^2$ 的枚举区间肯定优化不动，就只能往另外的两个过程想。  

$~~~~$ 发现一个区间 $[l,r]$ 其父节点只可能是 $l-1$ 或 $r+1$ 。可以利用这个性质进行 DP。  

$~~~~$ **正解部分：** 定义： $dp_{i,j,k}$ ，当 $k=0$ 时表示 $[l,r-1]$ 的父节点是 $r$ 的合法性，当 $k=1$ 时表示 $[l+1,r]$ 的父节点是 $l$。考虑一个已知的状态 $dp_{l,r,k}$ 能扩展出的状态，可以得到转移方程。  
$$
dp_{l-1,r,1}=dp_{l,k,0} ~ \& ~ dp_{k,r,1} ~ \& ~ (a_{l-1},a_{k}) \not= 1
$$

$$
dp_{l,r+1,0}=dp_{l,k,0} ~ \& ~ dp_{k,r,1} ~ \& ~ (a_{r+1},a_{k}) \not =1
$$

$~~~~$ 初值：$dp_{i,i,0},dp_{i,i,1} (1 \le i \le n)$ 均为 $1$。答案：当某次转移到区间 $[1,n]$ 时满足上面两个转移方程的前两个条件即可。

$~~~~$ 然后大力转移就可以了，时间复杂度 $\mathcal{O(n^3)}$。另外还要注意一些细节，具体见代码。    

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int gcd(int a,int b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}
int arr[705];
bool f[705][705],dp[705][705][2];//dp[l][r][k]:区间 [l,r] 在父节点为 r(k=0)时的合法性与在父节点为 l(k=1)时的合法性 
int main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&arr[i]),dp[i][i][0]=dp[i][i][1]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(gcd(arr[i],arr[j])!=1) f[i][j]=f[j][i]=true;// n^2预处理一下，不然每次都有 log 也受不起。 
		}
	}
	for(int l=n;l>=1;l--)
	{
		for(int r=l;r<=n;r++)
		{
			for(int k=l;k<=r;k++)
			{
				if(dp[l][k][0]&&dp[k][r][1])
				{
					if(l==1&&r==n)
					{
						puts("Yes");
						return 0;	
					}
					if(f[l-1][k]) dp[l-1][r][1]=true;
					if(f[r+1][k]) dp[l][r+1][0]=true;
				}
			}
		}
	}
	puts("No");
	return 0;
}
```



---

## 作者：SunnyYuan (赞：1)

## 思路

这里讲一个通俗易懂的版本。

设 $f_{i, j, 0/1}$ 表示在 $[i, j]$ 这一段区间以 $i$ 或者 $j$ 为根是否可以建成二叉搜索树。如果 $f_{i, j, 0} = true$ 表示以 $i$ 为根建立一棵二叉搜索树可行，$f_{i, j, 1} = true$ 表示以 $j$ 为根建立一棵平衡树可行。

那我们想让 $i$ 为根，首先要让 $[i + 1, j]$ 成为其右子树，那我们要选出来一个根 $k$ 满足 $i + 1 \le k \le j$，那么我们要让 $k$ 成为 $[i + 1, j]$ 这个区间的根，就要让 $f_{i + 1, k, 1}$ 和 $f_{k, j, 0}$ 都是 $true$，保证两棵子树都能接在 $k$ 上，然后我们再让 $i, k$ 相连，那么就需要满足 $\gcd(a_i, a_k) > 1$ 才行，如果以上条件都满足，那么 $f_{i, j, 0}$ 为 $true$，可以以 $i$ 为根。

同样的，我们想让 $j$ 为根，首先要让 $[i, j - 1]$ 成为左子树，然后找出一个根 $k$ 保证左右子树可以和谐相处，还要保证 $\gcd(a_j, a_k) > 1$，如果以上条件都满足，那么 $f_{i, j, 1}$ 为 $true$。

最后答案 $f_{1, n, 0}$ 或 $f_{1, n, 1}$ 为真。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: Recovering BST
| Contest: Luogu
| URL:     https://www.luogu.com.cn/problem/CF1025D
| When:    2023-10-05 16:16:26
| 
| Memory:  250 MB
| Time:    1000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 710;

bool f[N][N][2], c[N][N];
int n, a[N];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            c[i][j] = gcd(a[i], a[j]) > 1;

    for (int len = 1; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            if (len == 1) f[i][i][0] = f[i][i][1] = 1;
            else {
                for (int k = i + 1; k <= j; k++) if (f[i + 1][k][1] && f[k][j][0] && c[i][k]) f[i][j][0] = true;
                for (int k = i; k <= j - 1; k++) if (f[i][k][1] && f[k][j - 1][0] && c[k][j]) f[i][j][1] = true;
            }
        }
    }
    if (f[1][n][1] || f[1][n][0]) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}
```

---

## 作者：2huk (赞：0)

**题目保证了输入 $a_i$ 递增。**

因为是二叉排序树，所以**树上每颗子树都能对应序列上一个区间**。或者说，这棵树的中序遍历就是给定的序列。

有个性质：$[l, r]$ 对应的子树里，$l$ 是最小值，$r$ 是最大值；且从根开始一直向左走最后到达的点是 $l$，一直向右走最后到达的点是 $r$。如果你学过笛卡尔树理解这些是容易的。

考虑区间 DP。设 $f(l, r, k)$ 表示能否将 $[l, r]$ 内的值构造一棵合法的二叉排序树，且其根为 $k$。转移考虑枚举 $[l, k - 1]$ 的根节点和 $[k + 1, r]$ 的根节点。对于答案，判断是否存在 $k$ 使得 $f(1, n, k)$ 为真即可。

时间复杂度 $\mathcal O(n^4)$，过不了。

注意到 $f(l, r, k) = f(l, k, k) \land f(k,r,k)$。所以你可以只记录 $f(l, r, 0/1)$ 表示 $k$ 是左端点还是右端点。状态数做到 $\mathcal O(n^2)$。

考虑转移。我们以 $f(l, r, 0)$，即以 $l$ 作为根为例。

考虑枚举 $r$ 的父亲 $k$。这里需要满足 $\gcd(a_r, a_k) \ne 1$。

根据性质，你从 $l$ 出发，一直往右走，最后到达的点一定需要是 $r$。所以 $r$ 的父亲是 $k$ 就意味着 $r$ 是 $k$ 的**右儿子**。

因为你走到头了，所以 $r$ 必须没有右子树。这时你想到了 $f(?,r,1)$ 的定义。但是这个 $?$ 应该是什么呢？

再根据性质，$?$ 是从根（$r$）出发，一直向左走最后到达的点。这个点是否确定？

确定。从 $k$ 开始，先向右走（到达 $r$），再一直向左走直到走不动，此时所在的点是 $k$ 的后继。而 $k$ 的后继是 $k + 1$。所以这个 $?$ 是 $k + 1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/wkancudd.png)

而除去 $r$ 的子树外，剩下的子树对应区间 $[l, k]$，且以 $l$ 为根。所以 $k$ 合法当且仅当：

$$
f(l,k,0) \land f(k+1,r,1)
$$

总转移是（懒得打 $\LaTeX$ 了，看代码吧）：

```cpp
for (int k = l; k < r; ++ k )
	if (f[l][k][0] && f[k + 1][r][1]) {
		if（gcd(a[k], a[r]) > 1) f[l][r][0] = true;
		if (gcd(a[k + 1], a[l]) > 1) f[l][r][1] = true;
	}
```

判断答案从原来的 $f(1, n, k)$ 变成了 $f(1, k, 1) \land f(k, r, 0)$。

完整 AC 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 710 + 10;

int n, a[N];
bool f[N][N][2];
int g[N][N];

signed main() {
	cin >> n;
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i];
		f[i][i][0] = f[i][i][1] = true;
	}
	
	for (int i = 1; i <= n; ++ i )
		for (int j = 1; j <= n; ++ j )
			g[i][j] = __gcd(a[i], a[j]);
	
	for (int len = 2; len <= n; ++ len )
		for (int l = 1, r = len; r <= n; ++ l, ++ r )
			for (int k = l; k < r; ++ k )
				if (f[l][k][0] && f[k + 1][r][1]) {
					if (g[k][r] > 1) f[l][r][0] = true;
					if (g[k + 1][l] > 1) f[l][r][1] = true;
				}
	
	for (int i = 1; i <= n; ++ i )
		if (f[1][i][1] && f[i][n][0]) {
			puts("Yes");
			return 0;
		}
	
	puts("No");
	return 0;
}
```

这个题卡了求 $\gcd$ 的 $\log$，所以我们用 $\mathcal O(n^2 \log V)$ 预处理每个对的 $\gcd$。总复杂度是 $\mathcal O(n^3)$ 的。

---

## 作者：Emily666 (赞：0)

### 题目大意
给定 $n$ 个节点对应的权值，要求构造二叉搜索树，且相邻节点的权值不互质，问能否成功构造满足要求的二叉搜索树。


------------
### 思路分析
首先，对于二叉搜索树的每一个非叶子节点，它的的左儿子都小于它，右儿子都大于它~~废话~~，所以二叉搜索树的中序遍历，就是一个从小到大“排好序”的序列。也就是说，题目中输入的数列 $a_i$，就是**原二叉搜索树（如果有的话）的中序遍历**。

然后，每次枚举（子树）可能的根，我们就可以写出一个记忆化搜索了：
```cpp
bool dfs(int l,int r,int fa){
	if(l>r) return 1;//即该子树没有节点
	if(vis[l][r][fa]) return f[l][r][fa];//记过了就返回
	vis[l][r][fa]=1;//标记
	for(int i=l;i<=r;i++){//枚举该子树的根
		if(t[i][fa]&&dfs(l,i-1,i)&&dfs(i+1,r,i)){//此处的t是预处理数组，t[i][j]=0表示a[i]和a[j]互质，反之亦然。后面的dfs(l,i-1,i)和dfs(i+1,r,i)分别表示以i为根时的左右子树。
			f[l][r][fa]=1;//记忆化
			return 1;
		}
	}
	return 0;
}
```
然而，这种解法的空间复杂度太高，要进行优化。

在一个中序遍历里，根节点的位置是在中间（相对于先序和后序而言），画个图长这样：![](https://cdn.luogu.com.cn/upload/image_hosting/3ivjarrp.png)
我们会发现，对于每一棵子树，**其根的父节点在中序遍历中肯定与它本身对应的序列相邻**。根据这一点，我们可以把 `fa=l-1` 的情况记为 $0$，把 `fa=r+1` 的情况记为 $1$，然后就能愉快地对代码进行优化啦~
```cpp
bool dfs(int l,int r,int fa){//因为是数组下标，所以fa还是开int
	if(l>r) return 1;
	if(vis[l][r][fa]) return f[l][r][fa];
	vis[l][r][fa]=1;
	for(int i=l;i<=r;i++){
		if(t[i][fa?r+1:l-1]&&dfs(l,i-1,1)/*根节点在左子树的右边*/&&dfs(i+1,r,0)/*根节点在右子树的左边*/){
			f[l][r][fa]=1;
			return 1;
		}
	}
	return 0;
}
```


------------
### 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[705];
bool t[705][705],vis[705][705][2],f[705][705][2];
bool dfs(int l,int r,int fa){//注释见思路分析部分
	if(l>r) return 1;
	if(vis[l][r][fa]) return f[l][r][fa];
	vis[l][r][fa]=1;
	for(int i=l;i<=r;i++){
		if(t[i][fa?r+1:l-1]&&dfs(l,i-1,1)&&dfs(i+1,r,0)){
			f[l][r][fa]=1;
			return 1;
		}
	}
	return 0;
}
int main(){
	cin>>n;
	int gcd=0;
	for(int i=0;i<n;i++){
		cin>>a[i];
		gcd=__gcd(gcd,a[i]);
	}
	if(gcd>1){//特判，如果所有数都有一个共同的因数就直接输出"Yes"。
		cout<<"Yes\n";
		return 0;
	}
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(__gcd(a[i],a[j])>1) t[i][j]=t[j][i]=1;//预处理
		}
	}
	for(int i=0;i<n;i++){//枚举整棵树的根
		if(dfs(0,i-1,1)&&dfs(i+1,n-1,0)){//递归左右子树
			cout<<"Yes\n";//只要有一种可行方案就直接输出
			return 0;
		}
	}
	cout<<"No\n";
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# Part 1 - 题目翻译

给定 $n$ 个节点对应的权值 $a_1,a_2,\dots,a_n$，判断是否可以构造二叉排序树，即左儿子节点权值小于父亲节点，右儿子节点权值大于父亲节点，要求相邻节点的权值不互质。

# Part 2 - 算法思路

第一次自己做出紫题！但是觉得这道题达不到紫色。

很容易想到区间 dp。定义 $dp_{i,j,k}$ 为根为 $i$，区间为 $[j,k]$ 是否可以构造出二叉排序树。

考虑记忆化搜索，对于当前的搜索，$[l,r]$ 是当前区间，$fa$ 是根：

- 若 $l>r$，直接返回 $1$。
- 若 $l=r$，判断这个节点与根的权值是否互质，即 $\gcd(a_l,a_{fa})$ 是否等于 $1$。
- 若 $l<r$，枚举区间内的节点 $i$ 作为根，易得转移方程式：$dp_{fa,l,r}=dp_{i,l,i-1} \land dp_{i,i+1,r}$。

如果直接 dp 数组显然会爆空间，可以使用 map 卡空间。

# Part 3 - 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll int

ll tc, n, a[710];
map<pair<ll, ll>, bool> dp[710];

bool dfs(ll l, ll r, ll rt) {
	if (dp[rt].find({l, r}) != dp[rt].end()) {
		return dp[rt][{l, r}];
	}
	if (l == r) {
		return (__gcd(a[l], a[rt]) > 1);
	}
	if (l > r) {
		return 1;
	}
	bool res = 0;
	for (ll i = l; i <= r; i++) {
		if (__gcd(a[i], a[rt]) > 1) {
			res |= (dfs(l, i - 1, i) && dfs(i + 1, r, i));
			if (res) {
				return dp[rt][{l, r}] = res;
			}
		}
	}
	return dp[rt][{l, r}] = res;
}

int main() {

	scanf("%d", &n);
	for (ll i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	bool ans = dfs(1, n, 0);
	if (ans) {
		puts("Yes");
	} else {
		puts("No");
	}

	return 0;
}

```

---

## 作者：fengqiao17 (赞：0)

## 题目大意

给定一个序列 $a_i$，要求构造出满足以下条件的一棵树：

1. 该树是一棵**二叉搜索树**；
2. 两个直接相连的点之间的权值不互质，即最大公约数不为 1。

求是否可以构造出来。

## 思路分析

呃……由于其他巨佬已经把主要部分讲完了，所以我主要说一些细节。

#### 第一，为什么我们使用区间 DP？

我们一开始可以思考这是不是一棵平衡树，然后~~太菜了不会~~发现做不出来。

如果这题要用 DP 的话，那么我们发现无论是从左到右枚举还是从右到左枚举都无法做出，于是我们只能枚举长度。这就是区间 DP 的由来。

#### 第二，那个状态里面的第三维是怎么来的？

作为一名区间 DP 的小白，我们很有可能会定义以下的状态：$dp_{i,j}$ 表示将区间 $i$ 到 $j$ 的数字能否合并为一棵树，它的子问题是它的两棵子树。

这里就有一个问题：由于这里有一个情况我们没有注意到，那就是两棵子树在拼接时我们没有关注它们的顺序，右子树的根节点既可以当做整棵树的根节点，也可以接在左子树的下面使得左子树的根节点当做整棵树的根节点。

那么对于状态定义的改正方案也就呼之欲出了：$dp_{i,j,k}$ 将区间 $i$ 到 $j$ 的数字，且 $i$ 或者 $j$ 作为根节点能否合并为一棵树，$k$ 为 1 表示以 $i$ 为根节点，反之表示以 $j$ 为根节点。

状态转移方程可以看具体代码，这里就不说了。

#### 第三，为什么我要预处理一个数组？

预处理出一个数组 $f_{i,j}$ 是为了标记 $a_i$ 和 $a_j$ 是否互质，这个预处理是为了在后面的 DP 中不要重复处理，浪费时间。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 7e2 + 5;
int a[N];
bool f[N][N];
bool dp[N][N][2];
int gcd(int a , int b){//常规gcd最大公因数
	if(a % b == 0){
		return b;
	}
	return gcd(b , a % b);
}
int main(){
	int n;
	cin>>n;
	for(int i = 1 ; i <= n ; i++){
		cin>>a[i];
	}
	for(int i = 1 ; i <= n ; i++){
		dp[i][i][0] = dp[i][i][1] = 1;
	}
	for(int i = 2 ; i <= n ; i++){
		for(int j = 1 ; j < i ; j++){
			f[i][j] = gcd(a[i] , a[j]) > 1;//预处理a[i]、a[j]互不互质
		}
	}
	for(int len = 2 ; len <= n ; len++){//区间DP
		for(int i = 1 ; i + len - 1 <= n ; i++){
			int j = i + len - 1;
			for(int k = i ; k < j ; k++){
				if(dp[i][k][0] == 1 && dp[k + 1][j][1] == 1){
					dp[i][j][0] |= f[j][k];//以j开头
					dp[i][j][1] |= f[k + 1][i];//以i开头
				}//注意前面预处理是i<j，所以后面也要一样
			}
		}
	}
	for(int i = 1 ; i <= n ; i++){
		if(dp[1][i][1] == 1 && dp[i][n][0] == 1){//如果两种情况都可以，那么就可以把它们合并为一棵树
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";
	return 0;
}
```

## 七嘴八舌

这份题解写了我两天半（真的是两天半，不是什么奇奇怪怪的数字），不喜轻喷！

---

## 作者：cirnovsky (赞：0)

根据 BST 的性质可知对于一棵以 $u$ 为根的子树 $\text{subtree}(u)$ 对应原序列中的一段区间，于是对于一个区间 $[l,r]$，如果我们选取 $k$ 作为根，那么 $\text{subtree}(u)$ 的形态就固定下来了。

设 $f(i,j,k)$ 为区间 $[i,j]$ 中以 $k$ 为根是否能够构成一棵 BST。这不好，这很差，考虑怎么优化。

观察发现 $[l,r]$ 的父亲结点一定是 $l-1$ 或 $r+1$，于是重新设 $f(i,j,0\text{ or }1)$ 表示区间 $[i,j-1]$ 的父结点为 $j$ 是否合法 / 区间 $[i+1,j]$ 的父结点为 $i$ 是否合法。转移即：

$$
f(i-1,j,1)=f(i-1,j,1)\vee f(i,k,0)\wedge f(k,j,1)\wedge(\gcd(a_{i-1},a_{k})\neq1) \\
f(i,j+1,0)=f(i,j+1,0)\vee f(i,k,0)\wedge f(k,j,1)\wedge(\gcd(a_{j+1},a_{k})\neq1)
$$

$k$ 是区间 DP 的中间点。于是就可以做了，边界与答案显然。

```cpp
#include<bits/stdc++.h>
#define f(i,j,k) (f[i][j][k])
int n,a[710];
bool f[710][710][2],flag[710][710];
int GCD(int one,int ano)
{
	if(ano==0)	return one;
	else	return GCD(ano,one%ano);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)	f(i,i,1)=f(i,i,0)=1;
	for(int i=1;i<=n;++i)
	{
		flag[i][0]=1;
		for(int j=i;j<=n;++j)
		{
			flag[i][j]=flag[j][i]=(GCD(a[i],a[j])!=1);
			flag[0][j]=1;
		}
	}
	for(int i=n;i;--i)
	{
		for(int j=i;j<=n;++j)
		{
			for(int k=i;k<=j;++k)
			{
				f(i-1,j,1)|=(f(i,k,0)&f(k,j,1)&flag[i-1][k]);
				f(i,j+1,0)|=(f(i,k,0)&f(k,j,1)&flag[j+1][k]);
			}
		}
	}
	printf((f(1,n,0)|f(1,n,1))?"Yes\n":"No\n");
	return 0;
}
```

---

## 作者：Tony102 (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1025D)

[Blog阅读效果更佳](https://tony102.xyz/index.php/2021/02/19/cf1025d-recovering-bst/)


### Sol

注意到这是一个二叉树，而且是一棵二叉排序树

一棵二叉树，也就是说对于一个点它只有左右两个儿子。我们可以在一个区间内dp来选择它的左右儿子。我们设$f[i][j][k]$表示在区间$[i,j]$内以是否能以$k$为根并且满足任意两个直接相连的点之间的权值最大公约数不是$1$的条件。$O(n^2)$ 地枚举区间，$O(n)$ 地枚举根，$O(n)$ 地枚举儿子节点。时间复杂度为 $O(n ^4)$ 

因为这是一棵BST，它的中序遍历的话权值就是从小到大的。构造合法的树也会满足这样的条件。也就是说，区间$[i,j]$组成子树的父节点一定是$i-1$或$j+1$

设$opt[i][j]$表示$a[i]$和$a[j]$的公因数是否**不为1**。设$f[i][j][0/1]$ 表示区间$[i,j]$以$0: i-1$ 或 $1: j +1$ 为父节点时是否可行。若该区间本身可行，当前枚举的根为$k$， 若$opt[i-1][k] = 1$ ，则$f[i][k][0] = 1$。 以$j+1$为父节点的情况同理

这样以来省去一维状态，时间复杂度降至$O(n^3)$，可以通过本题。具体实现的时候可以预处理两个数的最大公因数是否为$1$来转移。当区间$[1,n]$出现一种合法状态的时候，即可输出`Yes`，否则无解。


**[Code戳这里](https://tony102.xyz/index.php/2021/02/19/cf1025d-recovering-bst/)**



---

## 作者：Ouaoan (赞：0)

题目：[Recovering BST](http://codeforces.com/contest/1025/problem/D)

题意：
给出n个升序排列的数，求是否能用这n个数组成一颗二叉排序树。

思路：

考场上——看标题，BST！看了题面后，我zz的想，这不就是裸的图论题么…然后就一顿敲，交上去一遍AC，心里美滋滋。结果正式测评就在51个点WA了。
其实正解是dp。

令L[i][j]表示以i为根，i的左子树可到j 这样的bst是否存在。
同理R[i][j]表示以i为根，i的右子树可到j 这样的bst是否存在。

然后枚举一个中间变量进行转移。
比如说L的转移：其中g[i][p]为true是为了判断p可与i相连，而L[p][k]即是指p的左儿子可扩展到k。由于是BST，所以i+1一定是i的祖先或在i的右子树中。R[i+1][p]为true指i+1可扩展到p，也就是指i+1是i的祖先。 所以可以看出，p是i的父亲，i+1为i的祖先时，i只有左子树，所以可以利用p的左子树进行转移。

最后，如果存在一个i使得L[i][n]==R[1][i]==1，则说明存在一颗以i为根的bst，否则不存在。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define maxn 700
#define rep(i,x,y) for(int i=x;i<=y;i++)

int n;
int a[maxn+5];
int g[maxn+5][maxn+5];
bool L[maxn+5][maxn+5],R[maxn+5][maxn+5];

int GCD(int x,int y) {
	if(y==0) return x;
	return GCD(y,x%y);
}

int main() {
	scanf("%d",&n);
	rep(i,1,n) {
		scanf("%d",&a[i]);
	}
	rep(i,1,n) {
		rep(j,1,n) {
			g[i][j]=GCD(a[i],a[j]);
			if(g[i][j]==1) g[i][j]=0;
			else g[i][j]=1;
		}
	}
	rep(i,1,n) L[i][i]=R[i][i]=1;
	rep(j,1,n-1) rep(i,1,n-j) {
		int k=i+j;
		rep(p,i+1,k) L[i][k]|=(g[i][p]&L[p][k]&R[i+1][p]);
		rep(p,i,k-1) R[i][k]|=(g[p][k]&L[p][k-1]&R[i][p]);
	}
	rep(i,1,n) {
		if(L[i][n]&&R[1][i]) {
			printf("Yes");
			return 0;
		}
	}
	printf("No");
	return 0;
}
```

---

## 作者：Mickey_snow (赞：0)

[CF1025D](http://codeforces.com/problemset/problem/1025/D) _Recovering BST_ : 区间DP.

题目大意：给定一颗二叉搜索树的中序遍历，已知此二叉搜索树所有有连边的两个节点最大公约数都大于 $1$ ,问能否构造出一颗满足条件的二叉搜索树。

开两个二维数组 $lft_{i,j}$ 代表区间 $[i,j]$ 能否构造出以 $j$ 为根的搜索树。类似地，二维数组 $rgt_{i,j}$ 代表区间 $[i,j]$ 能否构造出以 $i$ 为根的搜索树。

由于题目中给定的是中序遍历，所以原搜索树中任何一个子树都是给定数组 $a$ 的一段连续区间，而且无论是 $lft$ 还是 $rgt$ 代表的都是能否构造出一个根只有一个儿子的子树。可见，如果存在一个节点 $k$ 同时满足 $lft_{i,k}$ 和 $rgt_{k,j}$ 那么就是说可以构造出来一颗以 $k$ 为根而且有两个儿子的搜索树，我们可以用这个来转移。如果 $k$ 能够成为子树的根，那么我们再来判断一下 $k$ 能否与 $i-1, j+1$ 连边，推导出 $k$ 可能的父节点，也就是 $lft_{i-1,l}$ 和 $rgt_{i,l+1}$.由于题目没有要求将构造的搜索树输出，所以转移完之后 $k$ 就不重要了，下一步要考虑的根应该是 $i-1$ 和 $l+1$.

如果在某一时刻发现可以以 $k$ 为根，构造出区间  $[1,n]$ 的搜索树。也就是 $i=1,j=n$ ，那么要求的答案就是 Yes,如果执行完了全部循环，说明找不到符合条件的搜索树，答案为 No.

```c#
using System;

namespace CF1025D 
{
	class Program 
	{
		static void Main(string[] args) {
			int totNodes = Convert.ToInt32(Console.ReadLine());
			string[] inp = Console.ReadLine().Split(' ');
			int[] num = new int[totNodes];
			bool[,] lft = new bool[totNodes, totNodes], rgt = new bool[totNodes, totNodes];

			for(int i = 0;i < totNodes;i++) {
				num[i] = Convert.ToInt32(inp[i]);
				lft[i, i] = true;rgt[i, i] = true;
			}

			for(int fr = totNodes - 1;fr >= 0;fr--)
				for(int to = fr;to < totNodes;to++) 
					for(int root = fr;root <= to;root++)
						if(lft[fr, root] && rgt[root, to]) {
							if(fr == 0 && to == totNodes - 1) {
								Console.WriteLine("Yes");return;
							}

							if(fr > 0 && gcd(num[root], num[fr - 1]) > 1) rgt[fr - 1, to] = true;
							if(to < totNodes - 1 && gcd(num[root], num[to + 1]) > 1) lft[fr, to + 1] = true;
						}

			Console.WriteLine("No");
		}

		static int gcd(int a,int b) {
			return b == 0 ? a : gcd(b, a % b);
		}
	}
}
```

---

## 作者：UperFicial (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1025D)

同步发表于我的 [$\text{cnblogs}$](https://www.cnblogs.com/UperFicial/p/16659415.html)。

肉眼观察题。

设 $f_{i,j,k}$ 表示区间 $[i,j]$ 的根为 $k$ 时能否还原。这样枚举一个根 $k$，分别枚举两个儿子在两个区间的位置转移就好了，由于两个儿子是独立的，所以复杂度 $\Theta(n^4)$，无法通过。

考虑二叉搜索树的性质，区间 $[i,j]$ 组成的二叉搜索树的根一定是 $(i-1)$ 或 $(j+1)$。要不然有一段放不上去。

既然根的父亲只有两种方式，状态的设计就可以大大的简化了。

我们设 $f_{i,j,0}$ 表示区间 $[i,j)$ 组成的二叉搜索树的根的父亲是 $j$ 能否还原，$f_{i,j,1}$ 表示区间 $(i,j]$ 组成的二叉搜索树的根的父亲是 $i$ 能否还原。

转移采用刷表法，用 $f_{i,j,0/1}$ 来更新区间 $f_{i-1,j,0/1}$ 和 $f_{i,j+1,0/1}$ 即可。

[代码](https://codeforc.es/contest/1025/submission/170941979)。

---

