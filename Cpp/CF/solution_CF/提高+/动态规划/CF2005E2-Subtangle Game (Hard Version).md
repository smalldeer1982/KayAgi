# Subtangle Game (Hard Version)

## 题目描述

This is the hard version of the problem. The differences between the two versions are the constraints on all the variables. You can make hacks only if both versions of the problem are solved.

Tsovak and Narek are playing a game. They have an array $ a $ and a matrix $ b $ of integers with $ n $ rows and $ m $ columns, numbered from $ 1 $ . The cell in the $ i $ -th row and the $ j $ -th column is $ (i, j) $ .

They are looking for the elements of $ a $ in turns; Tsovak starts first. Each time a player looks for a cell in the matrix containing the current element of $ a $ (Tsovak looks for the first, then Narek looks for the second, etc.). Let's say a player has chosen the cell $ (r, c) $ . The next player has to choose his cell in the submatrix starting at $ (r + 1, c + 1) $ and ending in $ (n, m) $ (the submatrix can be empty if $ r=n $ or $ c=m $ ). If a player cannot find such a cell (or the remaining submatrix is empty) or the array ends (the previous player has chosen the last element), then he loses.

Your task is to determine the winner if the players play optimally.

Note: since the input is large, you may need to optimize input/output for this problem.

For example, in C++, it is enough to use the following lines at the start of the main() function:

```
<pre class="lstlisting">```
int main() {<br></br>    ios_base::sync_with_stdio(false);<br></br>    cin.tie(NULL); cout.tie(NULL);<br></br>}<br></br>
```
```

## 说明/提示

In the first example, Tsovak starts by looking for $ 1 $ . There is only one occurrence of $ 1 $ at $ (1,1) $ , so he chooses it. Then Narek needs to look for $ 2 $ in the submatrix of $ (2, 2) $ , which consists of just the last two elements: $ 6 $ and $ 2 $ . He chooses $ 2 $ , and then Tsovak loses since the array has ended.

In the second example, Tsovak needs to choose $ 1 $ . There is a $ 1 $ at the cell $ (n,m) $ , so he chooses that cell. Then, since the submatrix of $ (n + 1, m + 1) $ is empty, Narek cannot find $ 2 $ , so he loses.

## 样例 #1

### 输入

```
3
2 2 3
1 2
1 3 6
4 6 2
2 2 4
1 2
1 1 3 2
4 2 5 1
2 4 2
1 2
3 4
5 6
7 8
8 8```

### 输出

```
N
T
N```

# 题解

## 作者：Albert_van (赞：6)

[题](https://www.luogu.com.cn/problem/CF2005E2) [题](https://mirror.codeforces.com/contest/2005/problem/E2)。看不懂官方题解，于是找到物理竞赛女队大佬，没想到他十分钟就给出了极其直观的做法，恐怖如斯。

考虑一个简单 dp：$f_{k,i,j}$ 表示，当前操作者面对 $(i,j)$ 到 $(n,m)$ 的子矩形，需要找到一个 $b_{x,y}=a_k$，是否必胜。有转移：$f_{k,i,j}=1$ 仅当下列至少一种情况发生：

- $b_{i,j}=a_k$ 的前提下，$k=l$ 或 $i=n$ 或 $j=m$ 或 $f_{k+1,i+1,j+1}=0$（选择 $b_{i,j}$，操作一次转化为必败点）；
- $\exists x\ge i,y\ge j:f_{k,x,y}=1$（子矩形中存在满足第一条的 $(i,j)=(x,y)$）。

对于 $f_{k,x,y}=1$，$(x,y)$ 左上方的 $f$ 值（$f_{k,i,j}$ 其中 $i\le x,j\le y$）全为 $1$。那么当 $k$ 确定时，$f_{k,i,j}$ 的取值形如阶梯：

$$
\begin{pmatrix}1&1&1&1&0\\1&1&1&0&0\\1&1&1&0&0\\1&0&0&0&0\end{pmatrix}
$$
从 $n$ 到 $1$ 枚举 $k$，记 $g_{k,i}$ 表示第 $i$ 行中使 $f_{k,i,j}=1$ 的最大的 $j$，$mx_{k,i}$ 为第 $i$ 行中 $b_{i,j}=a_k$ 的最大的 $j$，直接在 $g$ 上转移即可，复杂度是 $\mathcal O(nl)$ 的。

另外，E1 的结论有助于简化本题的实现：如果某个数字在 $a$ 中出现了多次，设第二次出现的位置为 $t$，那么将 $a$ 中 $t$ 及以后的数字全部删去（令 $l\gets t-1$）不影响答案。

>假设当前操作者面对的子矩形中有两个位置 $(x,y),(u,v)$ 满足 $x>u,y>v,b_{x,y}=b_{u,v}=a_k$，因为 $f_{x+1,y+1,k+1}=1\Rightarrow f_{u+1,v+1,k+1}=1$，所以选择 $(x,y)$ 能够最大化对手进必败点的情况数，不劣于选择 $(u,v)$。因此两个人选择的 $(i,j)$ 都满足 $\not\exists x>i,y>j:b_{x,y}=b_{i,j}$，而子矩形在往右下方收缩，在 $a$ 中第二次碰到 $b_{i,j}$ 时必然无法操作从而失败，这等价于序列在此终止。

```cpp
#include <cstdio>
#include <cstring>

void cmx(int &x,int y){if(x<y) x=y;}

void re(int &x){
	x=0;int c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
}

const int N=1531;

int a[N],p[N*N],g[N],mx[N][N];

int main()
{
	int T;re(T);while(T--){
		int l,n,m,x;re(l);re(n);re(m);int ul=l;
		for(int i=1;i<=l;++i){
			re(a[i]);if(p[a[i]]) ul=i-1;
			if(i<=ul) p[a[i]]=i;
		}
		for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) re(x),cmx(mx[p[x]][i],j);
		for(int k=ul;k;--k){
			for(int i=1;i<=n;++i) g[i]=mx[k][i]+1>g[i+1]?mx[k][i]:0;
			for(int i=n-1;i;--i) cmx(g[i],g[i+1]);
		}
		puts(g[1]?"T":"N");
		for(int k=1;k<=ul;++k){
			p[a[k]]=0;for(int i=1;i<=n;++i) mx[k][i]=0;
		}
		memset(g,0,sizeof(g));
	}
}
```

---

## 作者：luckyclover (赞：1)

我看不懂题解，但我会用 bitset！

考虑最简单的 $\mathcal{O(nml)}$ 的算法。设 $f_{i,j,k}$ 表示在 $(i,j)$ 到 $(n,m)$ 的子矩阵中第 $k$ 轮时先手的胜负状态。显然有：
$$
f_{i,j,k}=\left\{
\begin{aligned}
&f_{i+1,j,k}|f_{i,j+1,k}|\neg f_{i+1,j+1,k+1} & & {b_{i,j}=a_k}\\
&f_{i+1,j,k}|f_{i,j+1,k}  & & {\text{otherwise}}\\
\end{aligned}
\right.
$$
直接把 dp 数组的第三维压进 bitset 里。在 $b_{i,j}\neq a_k$ 时转移是简单的；而在 $b_{i,j}=a_k$ 时其实是对所有满足 $a_k=b_{i,j}$ 的 $k$ 进行转移。所以可以对每个不同的 $a_i$ 预处理出所有 $j$ 使得 $a_i=a_j$，压进一个 bitset $g_{a_i}$ 里，转移方程：
$$
f_{i,j}=f_{i+1,j}|f_{i,j+1}|(\neg(f_{i+1,j+1}>>1)\&g_{b_{i,j}})
$$
时间复杂度 $\mathcal{O(\frac{nml}{\omega})}$，跑了不到 $1$ 秒。

卡空间，需要滚动数组。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
const int MAX=1505,MOD=998244353;
int n,m,K;
int a[MAX],b[MAX][MAX];
bitset<MAX> f[2][MAX];
unordered_map<int,bitset<MAX>> bs;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T; cin>>T;
	while(T--){
		cin>>K>>n>>m;
		for(int i=1;i<=m+1;i++){
			f[0][i].reset(); f[1][i].reset();
		}
		bs.clear();
		for(int i=1;i<=K;i++) cin>>a[i];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>b[i][j];
		for(int i=1;i<=K;i++) bs[a[i]][i]=1;
		for(int i=n;i>=1;i--){
			for(int j=m;j>=1;j--){
				f[i&1][j]=f[i&1^1][j]|f[i&1][j+1];
				if(bs.find(b[i][j])!=bs.end())
					f[i&1][j]|=bs[b[i][j]]&(~(f[i&1^1][j+1]>>1));
			}
		}
		if(f[1][1][1]) cout<<"T\n";
		else cout<<"N\n";
	}
	return 0;
}
```

---

## 作者：WeWantToRun (赞：1)

延续 E1 的思路。考虑选第 $i$ 个数会将第 $i-1$ 个数限死在左上角一个阶梯型之外（否则对手就有必胜策略）。比如以下例子：

```
a=[...,5]
b=[5,*,*,*,5
   *,*,*,5,*
   *,*,5,*,*
   *,*,*,*,*
   5,*,*,*,*]
```

那么选第一个数的人只能在右下方的星号里选，否则对手选了第一个人选的数右下方的 $5$，第一个人就输了。

可以开一个 dp 数组维护每一行被对手占领的范围的右端点。转移就是枚举每一个当前数字的位置判断是否能选择，完成后跑一遍后缀最大值。

最终第一个人能胜利，当且仅当他能选择至少一个数，也就是 dp 数组不全为零。

时间复杂度 $O(nm)$。

[Code](https://www.luogu.com.cn/paste/4a5opqj7)

---

