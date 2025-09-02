# 题目信息

# [ABC137D] Summer Vacation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc137/tasks/abc137_d

$ N $ 件の日雇いアルバイトがあり、$ i $ 件目の日雇いアルバイトを請けて働くと、その $ A_i $ 日後に報酬 $ B_i $ が得られます。

あなたは、これらの中から $ 1 $ 日に $ 1 $ 件まで選んで請け、働くことができます。

ただし、請けたことのある日雇いアルバイトは選べません。

今日から $ M $ 日後まで($ M $ 日後を含む)に得られる報酬の合計の最大値を求めてください。

なお、日雇いアルバイトは今日から請けて働くことができます。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^5 $
- $ 1\ \leq\ B_i\ \leq\ 10^4 $

### Sample Explanation 1

以下のように日雇いアルバイトを請けて働くと、報酬の合計は $ 5 $ となり、このときが最大です。 - 今日、$ 1 $ 件目の日雇いアルバイトを請けて働き、今日から $ 4 $ 日後に報酬 $ 3 $ を得ます。 - 明日(今日から $ 1 $ 日後)、$ 3 $ 件目の日雇いアルバイトを請けて働き、今日から $ 1+2\ =\ 3 $ 日後に報酬 $ 2 $ を得ます。

## 样例 #1

### 输入

```
3 4

4 3

4 1

2 2```

### 输出

```
5```

## 样例 #2

### 输入

```
5 3

1 2

1 3

1 4

2 1

2 3```

### 输出

```
10```

## 样例 #3

### 输入

```
1 1

2 1```

### 输出

```
0```

# AI分析结果

### 题目内容重写

#### [ABC137D] Summer Vacation

**题目描述**

有 $N$ 件日雇工作，第 $i$ 件工作完成后，将在 $A_i$ 天后获得报酬 $B_i$。你每天可以选择一件工作来完成，但每件工作只能完成一次。问在 $M$ 天内（包括第 $M$ 天）你能获得的最大报酬是多少？

**说明/提示**

- 所有输入均为整数。
- $1 \leq N \leq 10^5$
- $1 \leq M \leq 10^5$
- $1 \leq A_i \leq 10^5$
- $1 \leq B_i \leq 10^4$

**样例 #1**

输入：
```
3 4
4 3
4 1
2 2
```
输出：
```
5
```

**样例 #2**

输入：
```
5 3
1 2
1 3
1 4
2 1
2 3
```
输出：
```
10
```

**样例 #3**

输入：
```
1 1
2 1
```
输出：
```
0
```

### 算法分类
贪心

### 题解分析与结论

本题的核心在于如何在有限的时间内选择最优的工作顺序以获得最大报酬。所有题解都采用了贪心算法，通过优先队列（大根堆）来维护当前可选工作的最大报酬，确保每天选择报酬最高的工作。

### 所选高分题解

#### 题解1：MiddleRed (5星)
**关键亮点**：
- 使用优先队列维护当前可选工作的最大报酬。
- 通过排序和贪心策略确保每天选择最优工作。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,idx;
struct job{int d,v;}a[100001];
priority_queue<int> q;
bool cmp(job a,job b){return a.d<b.d;}
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)	cin>>a[i].d>>a[i].v;
	sort(a,a+n,cmp);
	for(int i=0;i<m;i++)
	{
		for(;a[idx].d<=i+1 and idx<n;idx++)	q.push(a[idx].v);
		if(!q.empty())	
		{
			ans+=q.top();
			q.pop();
		}
	}
	cout<<ans;
	return 0;
}
```

#### 题解2：Sexy_Foxy (4星)
**关键亮点**：
- 详细解释了贪心策略的实现过程。
- 使用优先队列优化选择过程，确保时间复杂度。
- 代码结构清晰，注释详细。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct node {int a,b;}ab[100010];
priority_queue<int>line;
int n,m;
ll ans;
bool cmn(node x,node y) {return x.a<y.a;}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) ab[i].input();
	sort(ab+1,ab+n+1,cmn);
	int cnt=1;
	for(int i=1;i<=m;i++)
	{
		while(ab[cnt].a<=i&&cnt<=n) line.push(ab[cnt++].b);
		if(!line.empty()) ans+=line.top(), line.pop();
	}
	printf("%lld",ans);
	return 0;
}
```

#### 题解3：WaterSun (4星)
**关键亮点**：
- 通过排序和优先队列结合，确保每天选择最优工作。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码**：
```cpp
#include <bits/stdc++.h>
#define re register
using namespace std;
const int N = 1e5 + 10;
int n,m,idx = 1,ans;
priority_queue<int> q;
struct node{int a,b;}arr[N];
inline int read(){
	int r = 0,w = 1; char c = getchar();
	while (c < '0' || c > '9'){ if (c == '-') w = -1; c = getchar(); }
	while (c >= '0' && c <= '9'){ r = (r << 3) + (r << 1) + (c ^ 48); c = getchar(); }
	return r * w;
}
int main(){
	n = read(); m = read();
	for (re int i = 1;i <= n;i++) arr[i].a = read(), arr[i].b = read();
	sort(arr + 1,arr + 1 + n);
	for (re int i = 1;i <= m;i++){
		while (arr[idx].a <= i && idx <= n) q.push(arr[idx++].b);
		if (!q.empty()) ans += q.top(), q.pop();
	}
	printf("%d",ans);
	return 0;
}
```

### 最优关键思路与技巧
- **贪心策略**：每天选择当前可选工作中报酬最高的，确保全局最优。
- **优先队列**：使用大根堆维护当前可选工作的最大报酬，优化选择过程。
- **排序**：按工作完成时间排序，确保每天选择的工作在时间范围内。

### 可拓展之处
- **类似题目**：可以扩展到其他需要在一定时间内选择最优任务的场景，如任务调度、资源分配等。
- **算法优化**：可以考虑使用其他数据结构（如线段树）来进一步优化选择过程。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：36.27秒