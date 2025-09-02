# 题目信息

# Subsequences

## 题目描述

For the given sequence with $ n $ different elements find the number of increasing subsequences with $ k+1 $ elements. It is guaranteed that the answer is not greater than $ 8·10^{18} $ .

## 样例 #1

### 输入

```
5 2
1
2
3
5
4
```

### 输出

```
7
```

# AI分析结果

### 题目内容
# 子序列

## 题目描述
对于给定的包含 $n$ 个不同元素的序列，找出长度为 $k + 1$ 的递增子序列的数量。保证答案不超过 $8·10^{18}$ 。

## 样例 #1
### 输入
```
5 2
1
2
3
5
4
```
### 输出
```
7
```

### 算法分类
动态规划结合树状数组优化

### 综合分析与结论
这些题解的核心思路都是通过动态规划来解决问题，定义状态 $dp[i][j]$ 表示以第 $i$ 个元素结尾，长度为 $j$ 的严格上升子序列的个数，转移方程为 $dp[i][j]=\sum_{a[k]<a[i]} dp[k][j - 1]$ 。原始的动态规划时间复杂度为 $O(n^2m)$，会超时，因此需要优化。大多题解采用树状数组优化，通过建立 $m$ 个树状数组，分别维护长度从 $1$ 到 $m$ 的最长子序列个数，将时间复杂度优化到 $O(nm\log n)$ 。部分题解还提到了线段树优化，但因线段树码量大、常数大，不如树状数组高效。

### 所选的题解
- **作者：Emp7iness (5星)**
    - **关键亮点**：思路清晰，不仅给出树状数组优化动态规划的核心思路，还说明了不用线段树的原因，同时提到可以压掉一维空间复杂度优化到 $O(n)$。
    - **重点代码**：
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define int long long
const int N=1e5+5;
int n,k,ans,a[N],t[N],f[N];
int lowbit(int k)
{
	return k&-k;
}
void add(int x,int k)
{
	while(x<=n)
	{
		t[x]+=k;
		x+=lowbit(x);
	}
}
int sum(int x)
{
	int s=0;
	while(x!=0)
	{
		s+=t[x];
		x-=lowbit(x);
	}
	return s;
}
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		f[i]=1;
	}
	for(int i=1;i<=k;i++)
	{
		memset(t,0,sizeof(t));
		for(int j=1;j<=n;j++)
		{
			add(a[j],f[j]);
			f[j]=sum(a[j]-1);
		}
	}
	for(int i=1;i<=n;i++)	ans+=f[i];
	cout<<ans;
	return 0;
}
```
核心实现思想：通过树状数组维护前缀和，每次循环更新树状数组并从树状数组获取转移值，最后累加得到最终答案。
- **作者：king_xbz (4星)**
    - **关键亮点**：先给出朴素的 $O(n^2)$ 动态规划思路，再引出树状数组优化的方法，逻辑连贯，代码实现清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define fint register int
#define H 5001
#define N 105904
#define int long long
using namespace std;
int n,k;
int a[N],f[N][15],t[N][15];
inline int lowbit(int x);
inline int query(int x,int j);
inline void adds(int x,int y,int j);
signed main()
{
	cin>>n>>k;
	for(fint i=1;i<=n;i++)
	cin>>a[i];
	for(fint i=1;i<=n;i++)
	{
		adds(a[i],1,1);
		for(fint j=2;j<=k+1;j++)
		f[i][j]=query(a[i]-1,j-1),adds(a[i],f[i][j],j);
	} 
	int ans=0;
	for(fint i=1;i<=n;i++)
	ans+=f[i][k+1];
	if(k==0)
	ans++;
	cout<<ans;
	return 0;
}

inline void adds(int x,int y,int j)
{
	for(fint i=x;i<=n;i+=lowbit(i))
	t[i][j]+=y;
	return ;
}

inline int query(int x,int j)
{
	int tot=0;
	for(fint i=x;i;i-=lowbit(i))
	tot+=t[i][j];
	return tot;
}

inline int lowbit(int x)
{
	return x&(-x);
}
```
核心实现思想：与上一题解类似，借助树状数组的查询和修改操作实现动态规划的转移，统计最终答案时考虑了 $k = 0$ 的特殊情况。
- **作者：registerGen (4星)**
    - **关键亮点**：简洁明了地给出状态转移方程和树状数组优化的做法，代码简洁，结构清晰。
    - **重点代码**：
```cpp
// f[i][j] = [a_k < a_i] * f[k][j-1] k = 1 to i - 1

#include<cstdio>
#include<algorithm>

typedef long long ll;

const int N=1e5;

int n,k,a[N+10];
ll ans,f[N+10][15];

struct BIT // 树状数组
{
	ll c[N+10];

#define lowbit(x) (x&(-x))

	inline void modify(int i,ll x)
	{
		for(;i<=n;i+=lowbit(i))c[i]+=x;
	}

	inline ll query(int i)
	{
		ll res=0;
		for(;i;i-=lowbit(i))res+=c[i];
		return res;
	}

#undef lowbit
}t[15];

int main()
{
	scanf("%d%d",&n,&k);k++;
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	if(k==1)return printf("%d\n",n),0; // 特判
	for(int i=1;i<=n;i++)
	{
		t[1].modify(a[i],1); // f[i][1] = 1
		for(int j=2;j<=k;j++)
		{
			// 经典的写法
			f[i][j]=t[j-1].query(a[i]-1);
			t[j].modify(a[i],f[i][j]);
		}
		ans+=f[i][k]; // 统计答案
	}
	printf("%lld\n",ans);
	return 0;
}
```
核心实现思想：利用树状数组结构体数组，在循环中通过树状数组的修改和查询操作完成动态规划状态转移，并统计最终答案，同样考虑了 $k = 1$ 的特殊情况。

### 最优关键思路或技巧
利用树状数组优化动态规划，通过树状数组快速查询前缀和，避免了暴力枚举的 $O(n)$ 时间复杂度，将整体时间复杂度从 $O(n^2m)$ 优化到 $O(nm\log n)$ 。同时，部分题解通过压缩状态空间，进一步优化了空间复杂度。

### 可拓展之处
同类型题通常围绕动态规划结合数据结构优化展开，类似算法套路是先确定动态规划的状态和转移方程，若原始动态规划复杂度较高，考虑用树状数组、线段树等数据结构优化转移过程。例如在一些求满足特定条件子序列数量、子数组和等问题中都可能用到类似方法。

### 推荐洛谷题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：利用树状数组统计逆序对数量，与本题利用树状数组优化动态规划过程类似，锻炼对树状数组的应用能力。
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：基础的树状数组模板题，用于巩固树状数组的基本操作，为解决复杂问题打基础。
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：经典的动态规划题目，可通过动态规划结合前缀和思想解决，与本题动态规划思路有相似之处，帮助加深对动态规划的理解。

### 个人心得摘录与总结
无。 

---
处理用时：73.83秒