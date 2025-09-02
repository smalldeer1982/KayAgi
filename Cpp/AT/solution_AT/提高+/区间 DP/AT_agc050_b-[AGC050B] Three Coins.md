# [AGC050B] Three Coins

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc050/tasks/agc050_b

$ N $ 個のマスが一列に並んでおり、左から右に $ 1 $ から $ N $ までの番号が振られています。

はじめ、すべてのマスは空です。 あなたは、以下の $ 2 $ 種類の操作を任意の順に何度でも行うことができます。

- **連続する** $ 3 $ マスであってコインが置かれていないものを選び、それぞれにコインを置く。
- **連続する** $ 3 $ マスであっていずれにもコインが置かれているものを選び、それぞれからコインを取り除く。

操作を済ませた後、左から $ i $ マス目にコインが置かれているなら、$ a_i $ 点が得られます。 コインがあるマス全てから得られる点数の合計が、あなたの得点です。

得られる最高得点を求めてください。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 500 $
- $ -100\ \leq\ a_i\ \leq\ 100 $
- 入力中の全ての値は整数である。

### Sample Explanation 1

コインが置かれたマスを `o` で、置かれていないマスを `.` で表します。 最適な手順の $ 1 $ つは次の通りです。 `....` $ \rightarrow $ `.ooo` このようにすれば、$ 2\ +\ 3\ +\ 4\ =\ 9 $ 点を得られます。

### Sample Explanation 2

最適な手順の $ 1 $ つは次の通りです。 `......` $ \rightarrow $ `ooo...` $ \rightarrow $ `oooooo` $ \rightarrow $ `o...oo` このようにすれば、$ 3\ +\ (-1)\ +\ 4\ =\ 6 $ 点を得られます。

## 样例 #1

### 输入

```
4
1
2
3
4```

### 输出

```
9```

## 样例 #2

### 输入

```
6
3
-2
-1
0
-1
4```

### 输出

```
6```

## 样例 #3

### 输入

```
10
-84
-60
-41
-100
8
-8
-52
-62
-61
-76```

### 输出

```
0```

# 题解

## 作者：joke3579 (赞：2)

## $\text{statement}$

有 $n$ 个盒子排成一列，从左到右分别编号为 $1\sim n$。

最开始，每个盒子都是空的。你可以以任何顺序进行如下两种操作任意次：
- 选择三个**连续**的空盒子，向其中分别放入一枚硬币。
- 选择三个**连续**的放有硬币的盒子，取出其中的硬币。

操作完后，假设第 $i$ 个盒子中装有硬币，你会获得 $a_i$ 分。最终分数是你从各个盒子处获得的分数的和。

请输出最终分数的最大值。

$3\le n\le 500, \ -100\le a_i \le 100$。

## $\text{solution}$

给定一系列位置 $x_i$，我们能否知道是否可以通过一系列操作使得只有这些位置的盒子内装有硬币？答案是肯定的。

首先我们发现，我们只需要关注 $x_i\bmod 3$ 的值。这是因为我们可以通过进行如下的操作使得 $x_i$ 左右平移三个位置：

`...o`  $\to$  `oooo`  $\to$  `o...`

然后有了转化后的题意：   
给定一个初始为空的串和目标串。你可以以任何顺序进行如下两种操作任意次：
- 在串的任意位置加入 `012`、`120`、`201` 中的一种。
- 在串的任意位置移除形如 `012`、`120`、`201` 的子串。

询问是否能够构造出目标串。

可以证明一定不需要移除操作。   
如果移除操作和上一次加入操作的操作范围有交集，则这两次操作互相抵消。反之我们一定可以通过不断交换移除操作和上一次加入操作的顺序，从而最终转化到前一种情况。容易证明不存在其他情况。

因此我们只需要着眼于加入子串能构造出的所有串。我们可以递归地定义可以构造出的串：
- 空串是可以构造出的。
- 设串长度为 $n$。如果存在三个位置 $x_i < x_j < x_k$，满足 $x_j\equiv x_i + 1\pmod 3$、$x_k\equiv x_j + 1\pmod 3$，且子串 $[1,i)$、$(i,j)$、$(j,k),(k,n]$ 都是可以构造出的串，则该串是可以构造出的。

这给出了一种区间 dp 的方法。总时间复杂度 $O(n^3)$。

$\text{code : }$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
const int N = 500 + 10;
int n, a[N], sum[N], f[N][N];

signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n; rep(i,1,n) cin >> a[i], sum[i] = sum[i - 1] + a[i], f[i][i] = 0;
	rep(i,1,n) rep(j,i+1,n) f[i][j] = -0x3f3f3f3f;
	rep(len,2,n) {
		if (len % 3) {
			for (int l = 1, r = l + len - 1; r <= n; ++ l, ++ r) {
				rep(k,l,r - 1) f[l][r] = max(f[l][r], f[l][k] + f[k + 1][r]);
			}
		} else {
			for (int l = 1, r = l + len - 1; r <= n; ++ l, ++ r) {
				rep(k,l,r - 1) f[l][r] = max(f[l][r], f[l][k] + f[k + 1][r]);
				f[l][r] = max(f[l][r], sum[r] - sum[l - 1]);
				for (int k = l + 1; k <= r - 1; k += 3) 
					f[l][r] = max(f[l][r], f[l + 1][k - 1] + f[k + 1][r - 1] + a[l] + a[k] + a[r]);
			}
		}
	} cout << f[1][n] << '\n';
}
```

---

## 作者：封禁用户 (赞：1)

考虑如下两种操作：

`ooo...` $\to$ `oooooo` $\to$ `oo...o`。

`ooo...` $\to$ `oooooo` $\to$ `o...oo`。

发现这两种操作的本质是将三元组中的部分元素向右移动了 $3$ 格。

容易想到我们还可以通过这种方法移动任何能被 $3$ 整除的数格。

 于是我们可以创造一个移动操作：将一个三元组的第一个元素向左移动 $3k$ 格或最后一个元素向右移动 $3k$ 格。

（也就是说，一个三元组可能被拆分成了类似 `o...o...o` 的形式。）

并且如果仅使用移动和放入操作，和仅使用放入和删除是等价的。

因为由于移动操作的本质是放入+删除操作，同理我们也可以通过放入+移动的操作来抵消删除操作。

考虑设计一个区间 dp，$f_{l,r}$ 为仅考虑区间 $[l,r]$ 的情况。

此时分为两种情况：

* $l$ 和 $r$ 可作为一个三元组的开头和结尾，即满足区间长度为 $3k$。此时考虑枚举三元组的中间元素 $mid$，对答案的贡献为 $a_l+a_r+a_{mid}+f_{l+1,mid-1}+f_{mid+1,r-1}$。

注意中间点需要满足的条件为 $[l+1,mid-1]$ 与 $[mid+1,r-1]$ 这两段区间的长度都为 $3$ 的倍数。

* $l$ 和 $r$ 不可作为一个三元组的开头和结尾，考虑枚举中间点 $mid\in [l+1,r]$ 直接转移，贡献为 $f_{l,mid-1}+f_{mid,r}$。

最终答案为 $f_{1,n}$。

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define inf 0x3f3f3f3f
#define linf 1e18
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define umap(x,y) sd unordered_map<x,y>
#define pque(x) sd priority_queue<x>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=510;
int n;
int a[N];
int f[N][N];
il void solve()
{
	n=read();
	F(i,1,n) a[i]=read();
	F(len,1,n)
	{
		F(l,1,n-len+1)
		{
			int r=l+len-1;
			if((r-l+1)%3==0)//区间长度为3倍数
			{
				F(mid,l+1,r-1)//枚举中间元素
				{
					if((mid-l+1)%3!=2||(r-mid+1)%3!=2) continue;
					f[l][r]=MAX(f[l][r],a[l]+a[r]+a[mid]+f[l+1][mid-1]+f[mid+1][r-1]);
				}
			}
			F(mid,l+1,r) f[l][r]=MAX(f[l][r],f[l][mid-1]+f[mid][r]);
		}
	}
	put(f[1][n]);
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：Take_A_Single_6 (赞：0)

小巧精致的区间 dp。  
首先观察数据范围 $3\le n \le 500$，发现很适合常规的区间 dp，可以直接敲出来：  
```cpp
for(int l=2;l<=n;l++)
{
    for(int i=1,j;i<=n-l+1;i++)
    {
        j=i+l-1;
        for(int k=i;k<j;k++)
            dp[i][j]=max(dp[i][j],dp[i][k]+dp[k][j]);
    }
}
```
那么然后呢？  
我们要考察本题贡献的方式，连续加入三个或者连续去掉三个，显然只是这样过于局限，我们需要更大的性质。  
手玩一下：  
- `.o....` $\to$ `.oooo.` $\to$ `....o.`  
- `....o.` $\to$ `.oooo.` $\to$ `.o....`  

我们发现，一个圈可以任意左移或者右移 $3$ 的倍数个格子，并且由于只能对三个格子操作，所以每次一定是三个三个加贡献，加贡献的块长也一定是 $3$ 的倍数。  
那么在块长为 $3$ 的倍数时，要额外算一下：
$$ dp_{i,j}=max(dp_{i,j},a_i+a_j+a_j+dp_{i+1,k-1}+dp_{k+1,j-1}) $$  
**注意 $k-i-1$ 与 $j-k-1$ 也必须为 $3$ 的倍数！**  
完整代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 1000000007
#define fir first
#define sec second
#define pr pair<int,int>
#define pb push_back
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX%10+'0');
}
int T,n,a[maxn],dp[505][505];
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int l=3;l<=n;l++)
	{
		for(int i=1,j;i<=n-l+1;i++)
		{
			j=i+l-1;
			if(l%3==0)
				for(int k=i+1;k<j;k++)
					if((k-i-1)%3==0&&(j-k-1)%3==0)dp[i][j]=max(dp[i][j],a[i]+a[j]+a[k]+dp[i+1][k-1]+dp[k+1][j-1]);
			for(int k=i;k<j;k++)dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
		}
	}
	write(dp[1][n]);
	return 0;
}
```

---

