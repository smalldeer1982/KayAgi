# Oier们的镜子(mirror)

## 题目背景

原创By：[b2019dy](https://www.luogu.org/space/show?uid=78488) 、[disangan233](https://www.luogu.org/space/show?uid=72679)   

$gcd$是一个很臭美的OIer，他有一些神奇的镜子。

## 题目描述



$gcd$手里一共有$n$个物体，它们的编号为$A_1,A_2,A_3\cdots A_n$。这些物体中有元素板也有镜子，元素板上带有元素，镜子一开始不带元素。

一个元素板可以与**至多**一面镜子相对应，那样的话那面镜子将会带上元素板上的元素。

一面镜子无法对应其他镜子。

现在告诉你物体总数$n$和每个物体**对应后**所带的元素个数，请问一共有多少种对应情况。


## 说明/提示


对于$20\%$的数据，$n\leq 5$。  

对于$50\%$的数据，$n\leq 10$。 

对于$100\%$的数据，$n\leq 15$。 


## 样例解释  

因为出题人太懒现将解释中的"(其余)全是元素板"缩写为"suki"！"对应"缩写为$\to$

### 样例1   
* suki。
* $A1,A2\to A3$。 
   
#### 答案为：$2$。


### 样例2  
* suki。
* $A2,A3\to A4$，suki。    
* $A1,A4\to A5$，suki。  
* $A1,A2,A3\to A5$，suki。    
* $A2\to A3$，suki。  
* $A2\to A3$，$A1,A4$->$A5$。  
* $A3\to A2$，suki。  
* $A3\to A2$，$A1,A4$->$A5$。  

### 答案为：$8$。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5
1 2 2 4 5```

### 输出

```
8```

# 题解

## 作者：nosta (赞：4)

【题意】定义有根树上一个结点的权值等于整个子树内的节点权值和，现给出$n(n\le15)$个节点的权值$\{w_n\}$，限制每棵树高度不超过$2$，求满足要求的带权森林个数。 

【做法】考虑状压dp，设$f[i,j]$为按$w$排序小大排序后前$i$个节点所构成的森林中，高度为$1$的树集合为$j$的方案数，转移有
$$
f[i,j]\to f[i+1,j+\{i+1\}]$$  
$$f[i,j]\to f[i+1,j-k] \; (k\subseteq j,k\not=\varnothing,w_{i+1}=\sum_{e\in k}w_e)
$$
即考虑让$i+1$作为高度为$1$或$2$的树的树根。注意到当$|k|=1$时，存在让$i+1$作为$k$中唯一点$e_0$的儿子的方案。显然仅当$w_i$单调不降时能取到所有决策。

【复杂度的推导】
$$
\sum_{i=0}^{2^n-1}2^{\mathbb{popcount}_i}
=\sum_{i=0}^n(n,i)2^i=\sum_{i=0}^n(n,i)1^{n-i}2^i=(1+2)^n=3^n
$$

总时间复杂度为$O(n3^n)$，需要剪枝。  

```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod=1e9+7;

int n,w[15],sum[1<<15];
int lmt,f[16][1<<15];

inline int lbt(int x) {return x&-x;}
inline void add(int&x,int y) {if((x+=y)>=mod) x-=mod;}

int main() {
	scanf("%d",&n);
	for(int i=0; i<n; ++i) scanf("%d",w+i); sort(w,w+n);
	for(int i=0; i<n; ++i) sum[1<<i]=w[i]; lmt=1<<n;
	for(int i=0; i<lmt; ++i) {
		if(i!=lbt(i)) sum[i]=sum[i-lbt(i)]+sum[lbt(i)];
	}
	f[0][0]=1;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<lmt; ++j) if(f[i][j]) {
			add(f[i+1][j|(1<<i)],f[i][j]);
			for(int k=j; k; k=(k-1)&j) if(w[i]==sum[k]) {
				add(f[i+1][j^k],f[i][j]);
				if(k==lbt(k)) add(f[i+1][j^k],f[i][j]);
			}
		}
	}
	int ans=0;
	for(int i=0; i<lmt; ++i) {
		add(ans,f[n][i]);
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Nuyoah_awa (赞：3)

### 题目大意

这道题的题面就挺绕的，大概就是有一些点，这些点可以指向一些有权值的点，这时自己没有权值，或者自己有权值。

抽象来讲就是连成多个菊花图，根节点没有点权，叶子结点有点权。（其实是个森林）要求根节点的权值为所有叶子的点权和，已给出所有点的最终点权，求多少种连边情况。

### 题目分析

#### 暴力

理解完题意后暴力就很好想了，dfs 出哪些点作为根节点，然后再深搜出每个根节点连接那些点。

时间复杂度为 $\mathcal O(2 ^ n \times 2 ^ {n ^ 2})$，可以过 20pts。

#### 正解

我们发现 $n$ 很小，直接想到状压。

#### 状态

按照正常的状压 dp，应该是一维定义压缩后的状态，一维定义枚举到第几个数。

然后我们来考虑怎么压缩好转移，我们转移肯定要知道哪些点要连到枚举的这个点上，于是我们可以定义状态 $s$ 表示所有有权且未连边的叶子结点的集合。

#### 转移

被动转移和主动转移均可，我在这只讲主动转移的情况。

我们分成两种情况转移。

1. 当前点是根节点节点

也就是说当前点最初为 $0$，对于其他点无影响，转移方程为：

$$f_{s,i} \to f_{s + \{i\}, i+1}$$

2. 当前节点是叶子结点

这时我们需要枚举连接到这个点上的点的子集 $t$。很显然这些点需要从我们未连边且有权的点中选，也就是当前状态 $s$ 的子集。（这就是状态定义的主要原因）

但转移并非转移到状态 $t$ 上，因为状态是所有未连边且有点权的点，我们选出的这些点都将连边，所以之后的状态是 $s - t$。

转移方程：

$$f_{s,i} \to f_{s-t,i+1}$$

注：上述转移只能在选出点的点权和等于该点的点权是转移，即 $a_{i+1} = \sum\limits_{j \in t}a_j$

特别的，如果两点 $x,y$ 最终点权相同，我们只计算了 $x \to y$ 的情况，没有计算 $y \to x$ 的情况，所以我们需要特判一下， 如果这个点仅有一个子节点，我们需要再次计算这个状态的贡献，即 $y \to x$ 的情况。

#### 补充

其实这个算法到此为止并不是正确的，因为计算每个点为根时，我们只会计算已经计算过的点连向他的情况，简单来讲就是只会计算它左边的数，没有计算它右边的数。

不过这个 bug 也好解决，我们只需将目标排个序，就行了，因为如果这个点右边的数都比他大，右边的数就不可能作为叶子结点连向他了。

#### 优化

上述算法需要枚举每个点、每个状态、转移后的状态，还要判断连接的数的权值和加起来是否等于当前数，时间复杂度是 $\mathcal O(n \times 2 ^ n \times 2 ^ n \times n)$ 的，只能拿 50pts。

首先，我们可以优化掉最后一层 $n$，也就是判断枚举的数之和是否等于当前点权，我们可以预处理出每种情况的点权和，也可以用递推来得出：

定义 $g_s$ 表示集合 $s$ 中所有点的点权和，我们顺序枚举 $s$，则 $g_s = g_{s - 2^j} + a_j$。$j$ 表示 $s$ 中最靠后的一个点。$g$ 数组的初始化为 $g_{2^i} = a_i$。

然后我们发现转移后的状态只需枚举 $s$ 的子集，于是时间复杂度就优化到了 $\mathcal O(n \times 3^n)$ 大概就能过了，然后再加一些剪枝：

1. 当当前状态 $f_{s, i}$ 为 $0$ 时，我们直接跳过，因为这个状态转移给任何一个状态都是无效的。
2. 当预处理出的 $g_s \neq a_i$ 时，直接跳过。

然后就很玄学的过了。

Q.E.D.

#### 细节

- 记得取模。
- 取模不开 `long long` $\approx$ 没取模。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <math.h>
#include <cstring>
#include <algorithm>
#define int long long

using namespace std;

const int N = 20, MOD = 1e9 + 7;
int n, a[N], g[(1 << 16)], f[(1 << 16)][N], ans;

int lowbit(int x)
{
	return x & -x;
}

signed main()
{
	scanf("%lld", &n);
	for(int i = 1;i <= n;i++)
		scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	for(int i = 1;i <= n;i++)
		g[(1 << (i - 1))] = a[i];
	for(int s = 0;s < (1 << n);s++)
		g[s] = g[s - lowbit(s)] + g[lowbit(s)];
	f[0][1] = 1;
	for(int i = 1;i <= n;i++)
	{
		for(int s = 0;s < (1 << n);s++)
		{
			if(f[s][i] == 0)
				continue;
			(f[s | (1 << (i - 1))][i + 1] += f[s][i]) %= MOD;
			for(int t = s;t != 0;t = (t - 1) & s)
			{
				if(a[i] != g[t])
					continue;
				(f[s - t][i + 1] += f[s][i]) %= MOD;
				if(t == lowbit(t))
					(f[s - t][i + 1] += f[s][i]) %= MOD;
			}
		}
	}
	for(int s = 0;s < (1 << n);s++)
		(ans += f[s][n+1]) %= MOD;
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Jiang_zi_chuan (赞：1)

我们可以比较暴力的做

每次枚举一个数，然后枚举子集可以用哪些东西构成

记录一下用了几组，最后除掉就行了

$7*3^n$并不能过

然后可以用fwt优化

代码：

```cpp
//2018.12.31 18:00
/*
   Name: Jiang_zi_chuan
   Copyright: Jiang_zi_chuan
   Author: Jiang_zi_chuan
   Date: 31/12/18 18:00
   Description: 算法类型
*/
// luogu-judger-enable-o2
//#define LOCAL
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

#define INF 0x3f
#define ull unsigned long long
#define ll long long
#define FOR(a, b, n) for(register int a = b; b >= n ? a >= n : a <= n; b >= n ? a-- : a++)
#define M(a, n) memset(a, n, sizeof(a));
#define S(n) scanf("%d", &n)
#define P(n) printf("%d", n)
#define G(n) getline(cin, n)
#define PI acos(-1.0)
#define QAQ(n) 0
#define chen_zhe 0x3f

using namespace std;

const int NR = 1000;
#define lowbit(x) (x & ( -x ))
const int N = 16;
const int N2 = 1 << 15;
int n, a[N], b[N2], sum[N2], f[N][N2];
const int mo = 1e9 + 7;
void ps(int &x, int y)
{
  x += y;
  x %= mo;
}
int main()
{
  S(n);
  FOR(i, 1, n) 
    S(a[i]);
  sort(a + 1, a + n + 1);
  FOR(i, 1, n) 
    b[1 << (i - 1)] = a[i];
  int l = (1 << n) - 1;
  f[0][0] = 1;
  FOR(i, 1, l) 
    sum[i] = sum[i - lowbit(i)] + b[lowbit(i)];
  FOR(i, 1, n) 
  {
    FOR(j, 0, l) 
      if (f[i - 1][j])
      {
        ps(f[i][j | (1 << (i - 1))], f[i - 1][j]);
        for(register int k = j; k; k = (k - 1) & j)
          if (sum[k] == a[i])
          {
            ps(f[i][j ^ k], f[i - 1][j]);
            if (!(k - lowbit(k))) 
              ps(f[i][j ^ k], f[i - 1][j]);
          }
      }
  }
  int ans = 0;
  FOR(i, 0, l) 
    ps(ans, f[n][i]);
  P(ans);
  return 0; 
}
```

---

