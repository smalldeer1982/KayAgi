# 题目信息

# [ABC196E] Filters

## 题目描述

给出整数数列 $A=(a_1,a_2,...,a_n)$，$T=(t_1,t_2,...,t_n)$，$X=(x_1,x_2,...,x_q)$。

定义 $n$ 个函数 $f_1(x),f_2(x),...,f_n(x)$：
$$
f_i(x)=\begin{cases}
x+a_i& t_i=1\\
\max(x,a_i)& t_i=2\\
\min(x,a_i)& t_i=3\\
\end{cases}
$$
对于 $i=1,2,...,q$，求出 $f_n(...f_2(f_1(x_i))...)$ 的值。

## 说明/提示

对于 $100\%$ 的数据所有输入的值均为整数，$1 \leqslant n,q \leqslant 2 \times 10^5$，$1 \leqslant t_i \leqslant 3$，$|a_i|,|x_i| \leqslant 10^9$。

## 样例 #1

### 输入

```
3

-10 2

10 1

10 3

5

-15 -10 -5 0 5```

### 输出

```
0

0

5

10

10```

# AI分析结果

### 题目内容重写

#### 题目描述

给出整数数列 $A=(a_1,a_2,...,a_n)$，$T=(t_1,t_2,...,t_n)$，$X=(x_1,x_2,...,x_q)$。

定义 $n$ 个函数 $f_1(x),f_2(x),...,f_n(x)$：
$$
f_i(x)=\begin{cases}
x+a_i& t_i=1\\
\max(x,a_i)& t_i=2\\
\min(x,a_i)& t_i=3\\
\end{cases}
$$
对于 $i=1,2,...,q$，求出 $f_n(...f_2(f_1(x_i))...)$ 的值。

#### 说明/提示

对于 $100\%$ 的数据所有输入的值均为整数，$1 \leqslant n,q \leqslant 2 \times 10^5$，$1 \leqslant t_i \leqslant 3$，$|a_i|,|x_i| \leqslant 10^9$。

#### 样例 #1

##### 输入

```
3

-10 2

10 1

10 3

5

-15 -10 -5 0 5```

##### 输出

```
0

0

5

10

10```

### 算法分类
模拟

### 题解分析与结论

本题的核心在于如何高效处理多个函数操作的组合，特别是对于大量查询的处理。题解中主要采用了维护一个区间 $[\text{L}, \text{R}]$ 的方法，通过不断更新这个区间来反映所有操作对 $x$ 的影响。最终，对于每个查询 $x_i$，只需将其与区间边界进行比较，并加上所有偏移量即可得到结果。

### 所选高星题解

#### 题解1：作者：liangbowen (赞：9)
- **星级**：5星
- **关键亮点**：通过维护区间 $[\text{L}, \text{R}]$ 来简化操作，思路清晰，代码简洁高效。
- **个人心得**：作者提到正确的思考方向是将 $x$ 视为未知数，维护一个区间，这种思维方式值得借鉴。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long min(long long x, int y) {return x < y ? x : y;}
long long max(long long x, int y) {return x > y ? x : y;}
int main()
{
	int n, q; long long minx = -1e18, maxx = 1e18, add = 0;
	scanf("%d", &n);
	while (n--)
	{
		int x, op;
		scanf("%d%d", &x, &op);
		if (op == 1) minx += x, maxx += x, add += x;
		else if (op == 2) minx = max(minx, x), maxx = max(maxx, x);
		else if (op == 3) minx = min(minx, x), maxx = min(maxx, x);
	}
	scanf("%d", &q);
	while (q--)
	{
		int x; scanf("%d", &x);
		printf("%lld\n", max(minx, min(maxx, x + add)));
	}
	return 0;
}
```

#### 题解2：作者：_GW_ (赞：0)
- **星级**：4星
- **关键亮点**：将操作一分离出来，单独处理，简化了问题，思路清晰。
- **个人心得**：作者提到将操作一的偏移量单独处理，这种分离思想在处理复杂操作时非常有效。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int a[N],res[N],t[N],n,m,k,x,y,z,sum,Mi=-1e18,Ma=1e18;
signed main()
{
  cin>>n;
  for(int i=1;i<=n;i++) 
  {
    cin>>a[i]>>t[i];
    if(t[i]==1) 
    {
      sum+=a[i];
    }
    else if(t[i]==2)
    {
      Ma=max(Ma,a[i]-sum);
      Mi=max(Mi,a[i]-sum);
    }
    else
    {
      Mi=min(Mi,a[i]-sum);
      Ma=min(Ma,a[i]-sum);
    }
  }
  cin>>m;
  for(int i=1;i<=m;i++)
  {
    cin>>x;
    cout<<max(Mi,min(Ma,x))+sum<<'\n';
  }
  return 0;
 } 
```

#### 题解3：作者：Ryan_Adam (赞：0)
- **星级**：4星
- **关键亮点**：预处理操作序列，提前计算合法区间，思路清晰，代码简洁。
- **个人心得**：作者提到预处理操作序列，提前计算合法区间，这种预处理思想在处理大量查询时非常有效。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int INF=0x7fffffff;
int t[N],a[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    int l=-INF,r=INF;
    int sumt=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i]>>t[i];
        if(t[i]==1)l+=a[i],r+=a[i],sumt+=a[i];
        else if(t[i]==2)l=max(l,a[i]),r=max(r,a[i]);
        else if(t[i]==3)r=min(r,a[i]),l=min(l,a[i]);
    }
    int q;
    cin>>q;
    while(q--)
    {
        int x;
        cin>>x;
        x+=sumt;
        cout<<max(l,min(r,x))<<endl;
    }
    return 0;
}
```

### 最优关键思路或技巧
维护一个区间 $[\text{L}, \text{R}]$ 来反映所有操作对 $x$ 的影响，最终通过比较 $x_i$ 与区间边界并加上偏移量得到结果。这种思路在处理大量查询时非常高效。

### 可拓展之处
类似的问题可以通过维护区间或预处理操作序列来简化处理，特别是在处理大量查询时，这种思路非常有效。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)

---
处理用时：47.56秒