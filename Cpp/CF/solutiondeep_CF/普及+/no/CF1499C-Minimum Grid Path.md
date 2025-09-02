# 题目信息

# Minimum Grid Path

## 题目描述

Let's say you are standing on the $ XY $ -plane at point $ (0, 0) $ and you want to reach point $ (n, n) $ .

You can move only in two directions:

- to the right, i. e. horizontally and in the direction that increase your $ x $ coordinate,
- or up, i. e. vertically and in the direction that increase your $ y $ coordinate.

In other words, your path will have the following structure:

- initially, you choose to go to the right or up;
- then you go some positive integer distance in the chosen direction (distances can be chosen independently);
- after that you change your direction (from right to up, or from up to right) and repeat the process.

You don't like to change your direction too much, so you will make no more than $ n - 1 $ direction changes.

As a result, your path will be a polygonal chain from $ (0, 0) $ to $ (n, n) $ , consisting of at most $ n $ line segments where each segment has positive integer length and vertical and horizontal segments alternate.

Not all paths are equal. You have $ n $ integers $ c_1, c_2, \dots, c_n $ where $ c_i $ is the cost of the $ i $ -th segment.

Using these costs we can define the cost of the path as the sum of lengths of the segments of this path multiplied by their cost, i. e. if the path consists of $ k $ segments ( $ k \le n $ ), then the cost of the path is equal to $ \sum\limits_{i=1}^{k}{c_i \cdot length_i} $ (segments are numbered from $ 1 $ to $ k $ in the order they are in the path).

Find the path of the minimum cost and print its cost.

## 说明/提示

In the first test case, to reach $ (2, 2) $ you need to make at least one turn, so your path will consist of exactly $ 2 $ segments: one horizontal of length $ 2 $ and one vertical of length $ 2 $ . The cost of the path will be equal to $ 2 \cdot c_1 + 2 \cdot c_2 = 26 + 176 = 202 $ .

In the second test case, one of the optimal paths consists of $ 3 $ segments: the first segment of length $ 1 $ , the second segment of length $ 3 $ and the third segment of length $ 2 $ .

The cost of the path is $ 1 \cdot 2 + 3 \cdot 3 + 2 \cdot 1 = 13 $ .

In the third test case, one of the optimal paths consists of $ 4 $ segments: the first segment of length $ 1 $ , the second one — $ 1 $ , the third one — $ 4 $ , the fourth one — $ 4 $ . The cost of the path is $ 1 \cdot 4 + 1 \cdot 3 + 4 \cdot 2 + 4 \cdot 1 = 19 $ .

## 样例 #1

### 输入

```
3
2
13 88
3
2 3 1
5
4 3 2 1 4```

### 输出

```
202
13
19```

# AI分析结果

### 题目翻译
# 最小网格路径

## 题目描述
假设你站在 $XY$ 平面的点 $(0, 0)$ 处，想要到达点 $(n, n)$。

你只能朝两个方向移动：
- 向右，即水平且朝着增加 $x$ 坐标的方向移动；
- 向上，即垂直且朝着增加 $y$ 坐标的方向移动。

换句话说，你的路径将具有以下结构：
- 最初，你选择向右或向上移动；
- 然后沿着所选方向移动一段正整数距离（距离可以独立选择）；
- 之后改变移动方向（从右到上，或从下到右）并重复上述过程。

你不喜欢频繁改变方向，因此方向改变次数最多为 $n - 1$ 次。

最终，你的路径将是一条从 $(0, 0)$ 到 $(n, n)$ 的折线，由最多 $n$ 条线段组成，且每条线段的长度为正整数，垂直和水平线段交替出现。

并非所有路径都是等价的。给定 $n$ 个整数 $c_1, c_2, \dots, c_n$，其中 $c_i$ 是第 $i$ 条线段的代价。

利用这些代价，我们可以定义路径的代价为路径中各线段长度乘以其代价的总和，即如果路径由 $k$ 条线段组成（$k \leq n$），则路径的代价为 $\sum\limits_{i=1}^{k}{c_i \cdot length_i}$（线段按在路径中的顺序从 1 到 $k$ 编号）。

请找出代价最小的路径并输出其代价。

## 说明/提示
在第一个测试用例中，要到达 $(2, 2)$ 至少需要转弯一次，因此路径恰好由 2 条线段组成：一条水平线段长度为 2，一条垂直线段长度为 2。路径的代价为 $2 \cdot c_1 + 2 \cdot c_2 = 26 + 176 = 202$。

在第二个测试用例中，一条最优路径由 3 条线段组成：第一条线段长度为 1，第二条线段长度为 3，第三条线段长度为 2。

该路径的代价为 $1 \cdot 2 + 3 \cdot 3 + 2 \cdot 1 = 13$。

在第三个测试用例中，一条最优路径由 4 条线段组成：第一条线段长度为 1，第二条为 1，第三条为 4，第四条为 4。该路径的代价为 $1 \cdot 4 + 1 \cdot 3 + 4 \cdot 2 + 4 \cdot 1 = 19$。

## 样例 #1
### 输入
```
3
2
13 88
3
2 3 1
5
4 3 2 1 4
```

### 输出
```
202
13
19
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，即让代价最小的线段尽可能长，其余线段长度为 1。不同题解在实现细节上有所差异，如前缀和的计算、最小值的更新方式等，但整体的贪心策略是一致的。

### 所选题解
- **作者：snnu_lgw (赞：3)，4星**
    - **关键亮点**：思路清晰，代码简洁，对贪心策略的解释较为详细，同时提醒了数据范围需要使用 long long 类型。
    - **个人心得**：原本以为是动态规划做法，思考后发现是贪心算法，提醒我们在解题时要灵活思考。
- **作者：moqizhu2005 (赞：2)，4星**
    - **关键亮点**：通过预处理最大值和前缀和，将时间复杂度优化到 $O(n)$，代码逻辑清晰。
- **作者：fanfansann (赞：1)，4星**
    - **关键亮点**：对贪心思路的解释直观易懂，代码实现简洁明了，直接奇偶交替行走进行贪心。

### 重点代码
#### 作者：snnu_lgw
```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll c[100000+10]; // cost

int main()
{
	int t; cin>>t;
	while(t--)
	{
		int n; cin>>n;
		for(int i=1;i<=n;i++)
			scanf("%lld",&c[i]);
		
		ll a_sum = c[1], b_sum = c[2]; //前缀和 
		ll a_min = c[1], b_min = c[2]; //当前最小值 

		ll ans = a_min*n+b_min*n;
		for(int i=2;i<=n-1;i++)
		{//在枚举的过程中直接修改ans
			if(i%2==0){
				a_sum += c[i+1];
				a_min = min(a_min,c[i+1]);
				b_min = min(b_min,c[i]);
				ans = min(ans,a_min*(n-(i+1)/2)+a_sum-a_min+b_min*(n-i/2+1)+b_sum-b_min); 
			}
			else {
				a_min = min(a_min,c[i]);
				b_sum += c[i+1];
				b_min = min(b_min,c[i+1]);
				ans = min(ans,a_min*(n-i/2)+a_sum-a_min+b_min*(n-(i+1)/2+1)+b_sum-b_min);
			}			
		}
		cout<<ans<<endl;
	} 
	return 0;
}
```
**核心实现思想**：通过枚举每一个线段的代价，分别计算向右和向上的前缀和与最小值，根据贪心策略更新最小代价。

#### 作者：moqizhu2005
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll maxn=100005,inf=(1ll<<60);
ll t,n,c[maxn],f[maxn],g[maxn],s[maxn],d[maxn];
int main(){
    scanf("%lld",&t);
    while(t--){
    	scanf("%lld",&n);
    	f[0]=g[0]=inf;
    	for(int i=1;i<=n;i++){
    		scanf("%lld",&c[i]);
    		f[i]=g[i]=inf;
		}
		for(int i=1;i<=n;i++){
			if(i%2==0){
				s[i]=s[i-1]+c[i];
				d[i]=d[i-1];
				f[i]=min(f[i-1],c[i]);
				g[i]=g[i-1];
			}
			else{
				d[i]=d[i-1]+c[i];
				s[i]=s[i-1];
				g[i]=min(g[i-1],c[i]);
				f[i]=f[i-1];
			}
		}
		ll ans=inf;
    	for(int i=2;i<=n;i++){
    		ll x=i/2,y=(i+1)/2;
    		ans=min(ans,f[i]*(n-x+1)+s[i]-f[i]+g[i]*(n-y+1)+d[i]-g[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
**核心实现思想**：预处理奇数位置和偶数位置的前缀和与最小值，然后枚举总共分割的线段数，根据贪心策略计算最小代价。

#### 作者：fanfansann
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 500007, INF = 2e9;

int t, n, m;
int a[N];

void solve()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; ++ i) 
		scanf("%lld", &a[i]);
	
	int even = INF, odd = INF, cnt_even = 0, cnt_odd = 0;
	int ans_even = 0, ans_odd = 0;
	int ans = (a[1] + a[2]) * n;
	for(int i = 1; i <= n; ++ i) {
		if(i & 1) {
			ans_odd += a[i];
			cnt_odd ++ ;
			odd = min(odd, a[i]);
		}
		else {
			ans_even += a[i];
			cnt_even ++ ;
			even = min(even, a[i]);
		}
		ans = min(ans, ans_even + even * (n - cnt_even) + ans_odd + odd * (n - cnt_odd));
	}
	printf("%lld\n", ans);
}

signed main()
{
	scanf("%lld", &t);
	while(t -- ) {
		solve();
	}
	return 0;
}
```
**核心实现思想**：奇偶交替遍历线段代价，分别记录奇数位置和偶数位置的和、最小值以及线段数量，根据贪心策略更新最小代价。

### 关键思路或技巧
- 贪心策略：让代价最小的线段尽可能长，其余线段长度为 1。
- 奇偶交替处理：由于只能交替改变方向，所以可以通过奇偶性来区分水平和垂直方向的线段。
- 前缀和与最小值的维护：通过前缀和和最小值的更新，可以快速计算当前状态下的路径代价。

### 拓展思路
同类型题或类似算法套路：
- 其他网格路径问题，如带障碍物、不同移动规则等，可能需要结合搜索、动态规划等算法。
- 其他贪心问题，如区间调度、任务分配等，关键在于找到合适的贪心策略。

### 推荐洛谷题目
- P1090 [NOIP2004 提高组] 合并果子
- P1223 排队接水
- P2240 【深基12.例1】部分背包问题

---
处理用时：66.60秒