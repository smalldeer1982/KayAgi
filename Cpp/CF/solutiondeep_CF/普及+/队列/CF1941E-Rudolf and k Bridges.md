# 题目信息

# Rudolf and k Bridges

## 题目描述

Bernard loves visiting Rudolf, but he is always running late. The problem is that Bernard has to cross the river on a ferry. Rudolf decided to help his friend solve this problem.

The river is a grid of $ n $ rows and $ m $ columns. The intersection of the $ i $ -th row and the $ j $ -th column contains the number $ a_{i,j} $ — the depth in the corresponding cell. All cells in the first and last columns correspond to the river banks, so the depth for them is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/2420e4ab48e7eae57737cc3a1dbfde24de284901.png) The river may look like this.Rudolf can choose the row $ (i,1), (i,2), \ldots, (i,m) $ and build a bridge over it. In each cell of the row, he can install a support for the bridge. The cost of installing a support in the cell $ (i,j) $ is $ a_{i,j}+1 $ . Supports must be installed so that the following conditions are met:

1. A support must be installed in cell $ (i,1) $ ;
2. A support must be installed in cell $ (i,m) $ ;
3. The distance between any pair of adjacent supports must be no more than $ d $ . The distance between supports $ (i, j_1) $ and $ (i, j_2) $ is $ |j_1 - j_2| - 1 $ .

Building just one bridge is boring. Therefore, Rudolf decided to build $ k $ bridges on consecutive rows of the river, that is, to choose some $ i $ ( $ 1 \le i \le n - k + 1 $ ) and independently build a bridge on each of the rows $ i, i + 1, \ldots, i + k - 1 $ . Help Rudolf minimize the total cost of installing supports.

## 说明/提示

In the first test case, it is most profitable to build a bridge on the second row.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/7ad474029f5a4a6573b004238d770f23ae9fe42a.png) It is not a top view, but side view: gray cells — bridge itself, white cells are empty, black cells — supports, blue cells — water, brown cells — river bottom.In the second test case, it is most profitable to build bridges on the second and third rows. The supports will be placed in cells $ (2, 3) $ , $ (3, 2) $ , and on the river banks.

In the third test case the supports can be placed along the river banks.

## 样例 #1

### 输入

```
5
3 11 1 4
0 1 2 3 4 5 4 3 2 1 0
0 1 2 3 2 1 2 3 3 2 0
0 1 2 3 5 5 5 5 5 2 0
4 4 2 1
0 3 3 0
0 2 1 0
0 1 2 0
0 3 3 0
4 5 2 5
0 1 1 1 0
0 2 2 2 0
0 2 1 1 0
0 3 2 1 0
1 8 1 1
0 10 4 8 4 4 2 0
4 5 3 2
0 8 4 4 0
0 3 4 8 0
0 8 1 10 0
0 10 1 5 0```

### 输出

```
4
8
4
15
14```

# AI分析结果

### 题目重写
# Rudolf和k座桥

## 题目描述
Bernard喜欢拜访Rudolf，但他总是迟到。问题在于Bernard必须乘坐渡轮过河。Rudolf决定帮助他的朋友解决这个问题。

这条河是一个$n$行$m$列的网格。第$i$行和第$j$列的交叉点包含数字$a_{i,j}$，即相应单元格的深度。第一列和最后一列的所有单元格都对应河岸，因此它们的深度为$0$。

Rudolf可以选择一行$(i,1),(i,2),\ldots,(i,m)$并在上面建一座桥。在该行的每个单元格中，他可以安装一个桥的支撑。在单元格$(i,j)$中安装支撑的成本是$a_{i,j}+1$。支撑的安装必须满足以下条件：
1. 必须在单元格$(i,1)$中安装一个支撑；
2. 必须在单元格$(i,m)$中安装一个支撑；
3. 任意两个相邻支撑之间的距离不得超过$d$。支撑$(i,j_1)$和$(i,j_2)$之间的距离是$|j_1 - j_2| - 1$。

只建一座桥很无聊。因此，Rudolf决定在连续的$k$行河面上建桥，即选择某个$i$（$1 \leq i \leq n - k + 1$），并在第$i,i + 1,\ldots,i + k - 1$行上分别独立建桥。帮助Rudolf最小化安装支撑的总成本。

## 说明/提示
在第一个测试用例中，在第二行建桥是最划算的。

在第二个测试用例中，在第二行和第三行建桥是最划算的。支撑将放置在单元格$(2, 3)$，$(3, 2)$以及河岸上。

在第三个测试用例中，支撑可以沿着河岸放置。

## 样例 #1
### 输入
```
5
3 11 1 4
0 1 2 3 4 5 4 3 2 1 0
0 1 2 3 2 1 2 3 3 2 0
0 1 2 3 5 5 5 5 5 2 0
4 4 2 1
0 3 3 0
0 2 1 0
0 1 2 0
0 3 3 0
4 5 2 5
0 1 1 1 0
0 2 2 2 0
0 2 1 1 0
0 3 2 1 0
1 8 1 1
0 10 4 8 4 4 2 0
4 5 3 2
0 8 4 4 0
0 3 4 8 0
0 8 1 10 0
0 10 1 5 0
```
### 输出
```
4
8
4
15
14
```

### 题解综合分析与结论
所有题解思路基本一致，都认识到每行建桥成本独立，先求每行最小建桥成本，再用前缀和求连续$k$行的最小总成本。
1. **思路**：对于每行，通过动态规划求最小建桥成本，状态转移方程为$f[i]=\min(f[j]) + a[i]+1$（$i - d - 1 \leq j \lt i$），其中$f[i]$表示在第$i$个位置建桥的最小成本，$a[i]$是该位置水深。
2. **算法要点**：
    - **动态规划**：确定状态和转移方程，计算每行最小建桥成本。
    - **数据结构优化**：为避免$O(nmd)$的时间复杂度，使用单调队列或线段树优化。单调队列可将时间复杂度降为$O(nm)$，线段树可优化到$O(nm\log m)$。
    - **前缀和**：计算每行最小成本后，利用前缀和快速求出连续$k$行的最小总成本。
3. **解决难点**：主要难点是优化动态规划的时间复杂度。通过单调队列或线段树维护区间最小值，减少计算量，避免超时。

### 所选的题解
- **作者：luobotianle (赞：10)  星级：5星**
    - **关键亮点**：思路清晰，代码简洁高效，详细注释，采用单调队列优化动态规划，复杂度低。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,m,k,T,d;
int a[105][N];
ll f[N];
ll ans[N],anss;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>k>>d;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
			}
		}
		for(int j=1;j<=n;j++){
			deque<ll> q;
			q.clear();
			f[1]=a[j][1]+1;
			q.push_back(1);
			for(register int i=2;i<=m;i++){
				if(!q.empty()&&i-q.front()>d+1)q.pop_front();
				f[i]=f[q.front()]+a[j][i]+1;
				while(!q.empty()&&f[q.back()]>f[i])q.pop_back();
				q.push_back(i);
			}
			ans[j]=ans[j-1]+f[m];
		}
		ll anss=ans[k];
		for(int i=k+1;i<=n;i++){
			anss=min(anss,ans[i]-ans[i-k]);
		}
		cout<<anss<<endl;
	}
	return 0;
}
```
核心实现思想：利用单调队列维护$f$数组的最小值，在遍历每行时，根据距离条件更新队列，计算$f[i]$，最后通过前缀和与滑动窗口思想求出最小总成本。

- **作者：2huk (赞：8)  星级：4星**
    - **关键亮点**：清晰阐述思路，提到用线段树或单调队列优化，给出线段树实现的代码链接。
    - **个人心得**：无
    - **核心代码**：无（给出链接<https://codeforces.com/contest/1941/submission/251199109>）

- **作者：wsx248 (赞：7)  星级：4星**
    - **关键亮点**：分步骤详细讲解，先给出朴素$dp$转移方程，再说明单调队列优化，最后提及前缀和优化区间和求取。
    - **个人心得**：无
    - **核心代码**：
```cpp
void solve(long long a[], long long dp[])
{
	dp[1] = 1;
	deque<int> q;
	q.push_back(1);
	for(int i=2;i<=m;i++)
	{
		if(q.size() && q.front()<i-d-1)
			q.pop_front();
		dp[i] = dp[q.front()] + a[i] + 1;
		while(q.size() && dp[q.back()]>=dp[i])
			q.pop_back();
		q.push_back(i);
	}
}
```
核心实现思想：与luobotianle类似，通过单调队列维护$dp$数组最小值，更新$dp[i]$。

### 最优关键思路或技巧
1. **动态规划状态设计**：将每行建桥问题转化为动态规划，通过合理定义状态$f[i]$，找到简洁的状态转移方程。
2. **单调队列优化**：利用单调队列维护滑动窗口内的最小值，避免暴力枚举，降低时间复杂度。
3. **前缀和优化**：计算每行最小成本后，用前缀和快速计算连续$k$行的总成本，减少计算量。

### 可拓展之处
1. **同类型题**：此类题目通常涉及动态规划与数据结构优化结合，如在网格上按特定规则移动求最小成本等。
2. **类似算法套路**：遇到动态规划转移方程中需频繁求区间最值的问题，可考虑用单调队列或线段树优化。

### 洛谷相似题目
1. **P1725 [NOI2016] 排队布局**：涉及动态规划和单调队列优化，与本题优化思路相似。
2. **P2893 [USACO08FEB] Making the Grade G**：通过动态规划和单调队列解决序列调整问题，锻炼动态规划思维。
3. **P3398 仓鼠找sugar**：需要运用动态规划和数据结构优化，与本题结合动态规划与数据结构的思路相符。 

---
处理用时：41.00秒