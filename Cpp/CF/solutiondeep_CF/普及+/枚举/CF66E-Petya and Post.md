# 题目信息

# Petya and Post

## 题目描述

### 题意翻译

有 $n$ 个邮局，在每个邮局都有一个加油站。（邮局编号从 $1$ 开始）

对于第 $i$ 个邮局，$a_i$ 表示位于这个邮局加油站最多能加多少油，$b_i$ 表示它到第 $i+1$ 个邮局会耗费多少油。特殊的，对于第 $n$ 个邮局，$b_n$ 表示它到第 $1$ 个邮局会耗费多少油。

现在可以任意选择一个邮局出发，开始的油量为 $0$。可以选择顺时针或者逆时针走动，一旦决定方向就不可以回头。 要求路途上任一时刻油量$\ge 0$。

## 样例 #1

### 输入

```
4
1 7 2 3
8 1 1 3
```

### 输出

```
2
2 4
```

## 样例 #2

### 输入

```
8
1 2 1 2 1 2 1 2
2 1 2 1 2 1 2 1
```

### 输出

```
8
1 2 3 4 5 6 7 8
```

# AI分析结果

### 题目内容
# Petya和邮局

## 题目描述

### 题意翻译
有 $n$ 个邮局，每个邮局都设有一个加油站。（邮局编号从 $1$ 开始）
对于第 $i$ 个邮局，$a_i$ 表示该邮局加油站的最大加油量，$b_i$ 表示从它到第 $i + 1$ 个邮局的耗油量。特别地，对于第 $n$ 个邮局，$b_n$ 表示从它到第 $1$ 个邮局的耗油量。
现在可任选一个邮局出发，初始油量为 $0$ 。可以选择顺时针或逆时针方向行进，一旦确定方向就不可回头。要求在行进过程中，任一时刻的油量都 $\geq 0$ 。

## 样例 #1
### 输入
```
4
1 7 2 3
8 1 1 3
```
### 输出
```
2
2 4
```

## 样例 #2
### 输入
```
8
1 2 1 2 1 2 1 2
2 1 2 1 2 1 2 1
```
### 输出
```
8
1 2 3 4 5 6 7 8
```

### 综合分析与结论
各题解的核心思路都是围绕在环上判断从每个点出发能否按顺时针或逆时针方向回到起点，主要区别在于优化方式和具体实现的数据结构。
1. **思路**：多数题解先分析暴力做法，再通过挖掘题目性质进行优化。如通过观察发现从不同点出发时油量变化的规律，将问题转化为维护前缀和最小值等问题。
2. **算法要点**：有利用前缀和简化计算，使用线段树、单调队列等数据结构维护前缀和最小值以优化时间复杂度。
3. **解决难点**：难点在于如何优化暴力算法的时间复杂度，以及处理环结构时的细节，如破环成链、顺时针与逆时针方向计算的差异。

### 所选的题解
#### 作者：Fireworks_Rise (5星)
- **关键亮点**：思路清晰，通过开两倍数列破环成链，利用单调队列高效维护前缀和最小值，代码简洁明了，整体实现高效且易懂。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int n,p[N],d[N],s[N];
int q[N],head,tail=-1;
bool flag[N];
signed main() {
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&p[i]);
    for(int i=1;i<=n;i++) {
    	scanf("%lld",&d[i]);
        s[i]=s[i+n]=p[i]-d[i];
    }
    for(int i=1;i<=n*2;i++) s[i]+=s[i-1];
    q[++tail]=n*2+1;
    for(int i=n*2;i>=0;i--) {
        if(q[head]>i+n) head++;
        if(i<n&&s[i]<=s[q[head]])
			flag[i+1]=1;
        while(head<=tail&&s[q[tail]]>=s[i]) tail--;
        q[++tail]=i;
    }
    d[0]=d[n];
    for(int i=1;i<=n;i++) s[i]=s[i+n]=p[i]-d[i-1];
    for(int i=1;i<=n*2;i++) s[i]+=s[i-1];
    head=0,tail=-1;
    q[++tail]=0;
    for(int i=1;i<=n*2;i++) {
        if(q[head]<i-n) head++;
        if(i>n&&s[i]>=s[q[head]])
    		flag[i-n]=1;
        while(head<=tail&&s[q[tail]]<=s[i]) tail--;
        q[++tail]=i;
    }
    int res=0;
    for(int i=1;i<=n;i++)
        if(flag[i]) res++;
    printf("%lld\n",res);
    for(int i=1;i<=n;i++) {
    	if(flag[i])
    		printf("%lld ",i);
	}
	printf("\n");
    return 0;
}
```
核心实现思想：先预处理出顺时针和逆时针方向的前缀和数组 `s`，通过单调队列 `q` 维护前缀和的最小值，根据最小值判断每个点是否满足条件。

#### 作者：xkcdjerry (4星)
- **关键亮点**：从暴力做法逐步优化，详细分析每一步优化的思路，最终得到不用单调队列，仅用前后缀和的 $O(n)$ 做法，对理解优化过程很有帮助。
核心实现思想：通过分析从不同点出发时油量变化规律，将问题转化为前缀加、后缀加、单点赋值、全局查最小值的操作，通过维护前缀最小值和后缀最小值优化实现。

#### 作者：_edge_ (4星)
- **关键亮点**：先给出暴力解法，再详细分析优化思路，将问题转化为维护特定区间前缀和最小值的问题，并给出使用单调队列优化的代码实现，有助于理解从暴力到优化的过程。
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=5e5+5; 
int n,a[INF],b[INF],ans[INF],sum1[INF],q1[INF],l1,r1,sum2[INF];
int q2[INF],l2,r2;
bool check1(int x) {
	int sum=-sum1[x-1];
	// 1 ~ n
	// 2 ~ n+1
	
	while (l1<=r1 && q1[l1]<x) l1++;
	while (l1<=r1 && sum1[q1[r1]]>=sum1[n+x-1]) r1--;
	q1[++r1]=n+x-1;
	
//	for (int i=x;i<n+x;i++) {
//		int kk=sum+sum1[i];
//		if (kk<0) return false;
//	}
	
	if (sum+sum1[q1[l1]]<0) return false;
	
	//... a[x]-b[x]
	//... a[x]-b[x]+a[x+1]-b[x+1]
	// 
	return true;
}

bool check2(int x) {
	int sum=sum2[x+n];
	// 1~n
	// 2~n+1
	
	while (l2<=r2 && q2[l2]<x) l2++;
	while (l2<=r2 && sum2[q2[r2]]<=sum2[n+x-1]) r2--;
	q2[++r2]=n+x-1;
	
//	for (int i=x+n;i>=x+1;i--) {
//		int kk=sum-sum2[i-1];
//		if (kk<0) return false;
//	}
	int kk=sum-sum2[q2[l2]];
	if (kk<0) return false;
	return true;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++) cin>>b[i];
	
	for (int i=n+1;i<=n*2;i++) a[i]=a[i-n];
	for (int i=n+1;i<=n*2;i++) b[i]=b[i-n];
	
	for (int i=1;i<=n*2;i++) sum1[i]=sum1[i-1]+a[i]-b[i];l1=1;
	for (int i=1;i<=n*2;i++) sum2[i]=sum2[i-1]+a[i]-b[i-1];l2=1;
	
	
	for (int i=1;i<n;i++) {
		while (l1<=r1 && sum1[q1[r1]]>=sum1[i]) r1--;
		q1[++r1]=i;
	}
	
	for (int i=1;i<n;i++) {
		while (l2<=r2 && sum2[q2[r2]]<=sum2[i]) r2--;
		q2[++r2]=i;
	}
	
	for (int i=1;i<=n;i++) {
		int l=check1(i);
		int k=check2(i);
		if (l || k) ans[++ans[0]]=i;
	}
	cout<<ans[0]<<"\n";
	for (int i=1;i<=ans[0];i++)
		cout<<ans[i]<<" ";
	return 0;
}
```
核心实现思想：断环为链，分别计算顺时针和逆时针方向的前缀和 `sum1`、`sum2`，利用单调队列 `q1`、`q2` 维护特定区间前缀和最小值，判断每个点是否符合条件。

### 最优关键思路或技巧
1. **破环成链**：通过复制数列将环结构转化为线性结构，便于处理和计算。
2. **前缀和优化**：利用前缀和快速计算从起点到各点的油量变化，简化计算过程。
3. **数据结构维护**：使用单调队列高效维护前缀和的最小值，从而快速判断从每个点出发是否满足条件，将时间复杂度从暴力的 $O(n^2)$ 优化到 $O(n)$。

### 可拓展之处
同类型题通常围绕环形路径上的资源分配、路径可行性判断等场景。类似算法套路包括将环问题转化为线性问题处理，利用前缀和简化计算，根据题目特性选择合适的数据结构（如线段树、单调队列等）优化时间复杂度。

### 相似知识点洛谷题目
1. **P1886 [USACO09NOV]灯Lights**：涉及环形状态变化和可行性判断，可通过类似思路分析。
2. **P2893 [USACO08FEB]Meteor Shower S**：在平面上的路径规划问题，与本题判断路径可行性有相似之处。
3. **P1195 口袋的天空**：虽然是图论相关，但在处理连通性和最优解判断上，与本题通过分析条件优化解法的思路类似。 

---
处理用时：41.50秒