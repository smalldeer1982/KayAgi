# [AGC023B] Find Symmetries

## 题目描述

Snuke 有两块板子。每块板都是一个 $n$ 行 $n$ 列的网格。对于这两块板子，记第 $i$ 行 $j$ 列的格子为 $(i,j)$。

第一块板子的每个格子上都写着一个小写字母：格子 $(i,j)$ 上的字母为 $S_{i,j}$。第二块板子上没有写任何东西。

Snuke 将以以下方法在第二块板子上写下字母：

首先，选择两个整数 $A$，$B$；然后在第二块板子的每个格子上写下一个字母。具体的说，第二块板子的格子 $(i+A,j+B)$ 将写上 $S_{i,j}$。这里第 $n+k$ 行即第 $k$ 行，第 $n+k$ 列即为第 $k$ 列。

此操作后，若对任意的 $i,j$，第二块板的格子 $(j,i)$ 上的字母和格子 $(i,j)$ 上的字母相同，则称第二块板为“好板”。

请你求出有多少 $A,B$ 满足 $0\le A,B<n$，且经过上述操作后第二块板为“好板”。

## 说明/提示

- $1\le n\le 300$。
- $S_{i,j}$ 都是小写字母。

#### 样例解释：

对于样例 1：对于所有可能的 $A$ 和 $B$，二号板上的字母如下所示：

![](https://img.atcoder.jp/agc023/2414e26dc3abb6dd7bfa0c800bb4af0c.png)

当且仅当 $(A,B)=(0,1)$ 或 $(A,B)=(1,0)$ 时满足第二块板是“好板”，因此答案是 $22$。

对于样例 2，所有被选中的 $A$ 和 $B$ 都会使第二块板成为“好板”。

对于样例 3，没有 $A$ 和 $B$ 可以使第二块板成为“好板”。

## 样例 #1

### 输入

```
2
ab
ca```

### 输出

```
2```

## 样例 #2

### 输入

```
4
aaaa
aaaa
aaaa
aaaa```

### 输出

```
16```

## 样例 #3

### 输入

```
5
abcde
fghij
klmno
pqrst
uvwxy```

### 输出

```
0```

# 题解

## 作者：myee (赞：6)

### 前言

大常数 $O(n^2)$ 跑不过小常数 $O(n^3)$ 实锤了。

### 思路

考虑二维哈希判定矩阵相同。

我们把原矩阵和转置后矩阵均向外延拓至 $2n\times2n$，则每个 $(A,B)$ 对对应的矩阵都是其的一个子矩阵。

同时对两个矩阵上二维哈希就好了。

一个矩阵的二维哈希值为 $\sum_{i=0}^{n-1}\sum_{j=0}^{m-1}v_{i,j}b_1^ib_2^j$，显然可以二维前缀和。

我们先对每个字符做一个到 $[0,998244353)$ 的随机映射，在模 $998244353$ 意义下嗯做就好了。

总复杂度 $O(n^2)$。常数很大。

### Code

使用 `mt19937_64` 的构造函数来进行随机映射。

```cpp
const ullt Mod=998244353,g1=3,g2=114514;
typedef ConstMod::mod_ullt<Mod>modint;
typedef std::vector<modint>modvec;
modint V[605][605],VT[605][605];
modint Pow1[605],Pow2[605];
modint Sum1[605][605],Sum2[605][605];
chr C[305];
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    uint n;scanf("%u",&n);
    for(uint i=0;i<n;i++){
        scanf("%s",C);
        for(uint j=0;j<n;j++)
            VT[j+n][i+n]=VT[j+n][i]=VT[j][i+n]=VT[j][i]=V[i+n][j+n]
                =V[i+n][j]=V[i][j+n]=V[i][j]=std::mt19937_64(C[j])();
    }
    Pow1[0]=1;for(uint i=1;i<=n*2;i++)Pow1[i]=Pow1[i-1]*g1;
    Pow2[0]=1;for(uint i=1;i<=n*2;i++)Pow2[i]=Pow2[i-1]*g2;
    for(uint i=0;i<n*2;i++)for(uint j=0;j<n*2;j++)
        Sum1[i+1][j+1]=V[i][j]*Pow1[i]*Pow2[j],Sum2[i+1][j+1]=VT[i][j]*Pow1[i]*Pow2[j];
    for(uint i=0;i<=n*2;i++)for(uint j=0;j<n*2;j++)
        Sum1[i][j+1]+=Sum1[i][j],Sum2[i][j+1]+=Sum2[i][j];
    for(uint i=0;i<n*2;i++)for(uint j=0;j<=n*2;j++)
        Sum1[i+1][j]+=Sum1[i][j],Sum2[i+1][j]+=Sum2[i][j];
    uint ans=0;
    for(uint a=0;a<n;a++)for(uint b=0;b<n;b++)
        if((Sum1[a+n][b+n]+Sum1[a][b]-Sum1[a][b+n]-Sum1[a+n][b])*Pow1[b]*Pow2[a]
                ==(Sum2[b+n][a+n]+Sum2[b][a]-Sum2[b][a+n]-Sum2[b+n][a])*Pow1[a]*Pow2[b])
            ans++;
    printf("%u\n",ans);
    return 0;
}
```


---

## 作者：zmza (赞：2)

# 题意简述

给定一个 $n \times n$ 的矩阵 $S$ ，求出有多少个 $0 \leq a,b <n$ ，将最下面 $a$ 行移到最上面，将最右边 $b$ 列移到最左边，满足 $S(i,j)=S(j,i)$ 。

# 解析

首先，我们可以发现，如果 $a,b$ 满足题目要求，那么 $a+x,b+x$ 也一定会满足。为什么呢？因为它们移动的数量一样，所以左下角的正方形移到右上角，最下面的 $x$ 行移到最上面，最右边的列移到最左边。因为 $a,b$ 满足要求，所以左下角的正方形对称，最下面的 $x$ 行和最右边的 $x$ 列对称，所以还是相等的。

所以我们可以枚举 $a$ ，将最下面的 $a$ 行移到最上面，判断是否可行。如果可以，那么计数器就加 $n$ 。因为 $a$ 从 $a$ 到 $n-1$ 再到 $a-1$ ， $b$ 从 $0$ 到 $n-1$ 这 $n$ 种方案都是可行的。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int read()
{
	int sum = 0, ne = 1;
	char ch = getchar();
	for (; (ch < '0' || ch > '9') && ch != '-'; ch = getchar());
	if (ch == '-')
		ne = -1, ch = getchar();
	for (; ch >= '0' && ch <= '9'; ch = getchar())
		sum = (sum << 3) + (sum << 1) + (ch - '0');
	return sum * ne;
}
char mp[305][305], tmp[305][305];
signed main()
{
	int n = read();
	for (int i = 1; i <= n; i++)
		scanf("%s", mp[i] + 1);
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
			{
				if (i + j == n)
					tmp[n][k] = mp[j][k];
				else if (i + j > n)
					tmp[i + j - n][k] = mp[j][k];
				else tmp[i + j][k] = mp[j][k];
			}
		bool flag = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
				if (tmp[i][j] != tmp[j][i])
				{
					flag = 1;
					break;
				}
			if (flag)
				break;
		}
		if (!flag)
				ans += n; 
	}
	printf("%d", ans);
	return 0;
}

```



---

## 作者：火车司机 (赞：1)

## 简要分析

$n^4$ 暴力应该都不难想，$n^2$ 枚举左上角，$n^2$ 判断是否满足要求，但是这样显然会超时

考虑怎么优化

显然 $n^2$ 判断应该是不能再优化的了，因此我们需要减少枚举数量

通过题目的要求我们可以发现，一个正方形满足条件，那么它一定是关于它的主对角线轴对称的

当我们继续以这个正方形的主对角线上的点为左上角时，所形成的新的正方形也一定是满足条件的

因为新的正方形无非就是将原正方形的上方若干行和左边若干列分别顺序不变地移到了最下方和最右边，不影响关于主对角线对称的性质

如果对这一段不懂可以画个图手模一下

有了这个性质我们就只需要枚举 $n$ 条不同的主对角线了，复杂度降为了 $O(n^3)$

## 完整代码

```cpp
#include <bits/stdc++.h>
#define ri register int
#define N 605
using namespace std;
int n, ans;
char s[N][N];
signed main()
{
	scanf("%d", &n);
	for (ri i = 1; i <= n; ++i)
	{
		scanf("%s", s[i] + 1);
		for (ri j = 1; j <= n; ++j)
			s[i][j + n] = s[i][j];
	}
	for (ri i = 1; i <= n; ++i)
		for (ri j = 1; j <= n; ++j)
			s[i + n][j] = s[i + n][j + n] = s[i][j];
	for (ri i = 0; i < n; ++i)
	{
		ri f = 1;
		for (ri x = 2; x <= n && f; ++x)
			for (ri y = 1; y < x && f; ++y)
				if (s[x + i][y] != s[y + i][x])
					f = 0;
		if (f)
			ans += n;
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：cosf (赞：0)

题目要在板一上 $(i + a, j + b) = (j + a, i + b)$。可以发现，$a - b$ 的值相同，则条件相同。

具体的，比如我们令 $a = b + d$，则条件为 $(i + b + d, j + b) = (j + b + d, i + b)$，然后把该条件视为对 $(i + b, j + b)$ 的条件，那么，此时的条件相当于把板一往左上轮换了 $b$ 次之后再根据 $(d, 0)$ 转写到板二的条件。

把板一往左上轮换显然不会影响条件的本质（所有点与对称轴的相对位置不变），因此，在本题中，我们只需要判断形如 $(a, 0)$ 的转写方式有几个满足要求，数出来后乘以 $n$ 即可。

复杂度 $O(n^3)$。

```cpp
#include <iostream>
using namespace std;

#define MAXN 305

string mp[MAXN];

int n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> mp[i];
        mp[i] = " " + mp[i] + mp[i];
    }
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        bool e = 0;
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                if (mp[j][k + i] != mp[k][j + i])
                {
                    e = 1;
                    break;
                }
            }
            if (e)
            {
                break;
            }
        }
        res += !e;
    }
    cout << res * n << endl;
    return 0;
}

```

---

