# 题目信息

# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1
```

### 输出

```
9
```

# AI分析结果

### 题目内容中文重写
## 曲折的移动

### 题目描述
龙象征着智慧、力量和财富。在农历新年那天，人们用竹条和布料制作龙的模型，用杆子撑起它们，并高低起伏地舞动杆子，以模拟一条飞舞的龙。

手持低杆的表演者用数字 $1$ 表示，而手持高杆的表演者用数字 $2$ 表示。因此，表演者的队伍可以用一个序列 $a_{1},a_{2},\cdots,a_{n}$ 来表示。

小汤米也在其中。他想选择一个区间 $[l,r]$（$1\leq l\leq r\leq n$），然后将 $a_{l},a_{l + 1},\cdots,a_{r}$ 反转，使得新序列的最长非递减子序列的长度最大。

非递减子序列是一个索引序列 $p_{1},p_{2},\cdots,p_{k}$，满足 $p_{1}<p_{2}<\cdots<p_{k}$ 且 $a_{p1}\leq a_{p2}\leq\cdots\leq a_{pk}$。该子序列的长度为 $k$。

### 说明/提示
在第一个样例中，反转区间 $[2,3]$ 后，数组将变为 $[1,1,2,2]$，其中最长非递减子序列的长度为 $4$。

在第二个样例中，反转区间 $[3,7]$ 后，数组将变为 $[1,1,1,1,2,2,2,2,2,1]$，其中最长非递减子序列的长度为 $9$。

### 样例 #1
#### 输入
```
4
1 2 1 2
```
#### 输出
```
4
```

### 样例 #2
#### 输入
```
10
1 1 2 2 2 1 1 2 2 1
```
#### 输出
```
9
```

### 综合分析与结论
这些题解主要围绕如何解决给定仅含 1 和 2 的序列，通过翻转一个区间来得到最长非递减子序列长度的问题。思路上大多先分析出最终序列可拆分为 $[1,1,\cdots][2,2,\cdots][1,1,\cdots][2,2,\cdots]$ 四段，通过翻转中间两段来优化结果。

算法要点方面，有两种主流方法：一是利用前缀和、后缀和结合线段树维护 $ct1[i - 1]+ct2[i]$ 来枚举断点求解，时间复杂度为 $O(n\log n)$；二是使用动态规划，定义状态表示前 $i$ 个数中前 $j$ 段的答案，通过状态转移方程递推，时间复杂度为 $O(n)$。

解决的难点在于如何想到将序列拆分为四段的思路，以及如何正确构建状态转移方程。

### 高评分题解
- **浅色调（5星）**
    - **关键亮点**：提供了两种解法，思路清晰，代码注释详细，对两种方法的复杂度分析准确。
    - **个人心得**：无
    - **核心代码（解法二）**：
```cpp
#include<bits/stdc++.h>
#define RE register
#define For(i,a,b) for(RE int (i)=(a);(i)<=(b);(i)++)
using namespace std;
int n,x,f[5];

int main(){
    scanf("%d",&n);
    For(i,1,n) 
        scanf("%d",&x),
        f[1]+=(x==1),
        f[2]=max(f[1],f[2]+(x==2)),
        f[3]=max(f[2],f[3]+(x==1)),
        f[4]=max(f[3],f[4]+(x==2));
    cout<<f[4];
    return 0;
}
```
    - **核心实现思想**：定义 $f[i]$ 表示前 $i$ 个数中前 $j$ 段的答案，通过状态转移方程 $f[1]+=(x==1);f[2]=max(f[1],f[2]+(x==2));f[3]=max(f[2],f[3]+(x==1));f[4]=max(f[3],f[4]+(x==2));$ 递推得到最终结果。

- **蒟蒻丁（4星）**
    - **关键亮点**：思路清晰，对状态转移方程的理解提供了形象的解释，代码简洁。
    - **个人心得**：“这题又开阔了我的眼界”，表示本题让其有了新的收获。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
ll n,m,f[10],ans;

int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		ll a1;
		scanf("%lld",&a1);
		f[1]+=(a1==1);
		f[2]=max(f[1],f[2]+(a1==2));
		f[3]=max(f[2],f[3]+(a1==1));
		f[4]=max(f[3],f[4]+(a1==2));
	}
	cout<<f[4];
}
```
    - **核心实现思想**：与浅色调的解法二类似，通过状态转移方程更新 $f$ 数组，最终得到最长非递减子序列的长度。

- **Karry5307（4星）**
    - **关键亮点**：思路独特，通过分别定义 $f_{i,j}$ 和 $g_{i,j}$ 表示前后两段的最长不降子序列长度，再枚举分界线求解。
    - **个人心得**：“做完之后看了看题解区发现没人思路跟我一样，所以来写一下”，体现了其独特的思考方式。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=2e5+51; 
ll n,res;
ll x[MAXN],f[MAXN][3],g[MAXN][3];
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		x[i]=read();
	}
	for(register int i=1;i<=n;i++)
	{
		f[i][1]=f[i-1][1],f[i][2]=f[i-1][2];
		x[i]==1?f[i][1]++:f[i][2]=max(f[i][1],f[i][2])+1;
	}
	for(register int i=n;i;i--)
	{
		g[i][1]=g[i+1][1],g[i][2]=g[i+1][2];
		x[i]==2?g[i][2]++:g[i][1]=max(g[i][1],g[i][2])+1;
	}
	for(register int i=0;i<=n;i++)
	{
		res=max(res,f[i][2]+g[i+1][1]);
	}
	printf("%d\n",res);
}
```
    - **核心实现思想**：先正向递推 $f_{i,j}$ 表示 $1\sim i$ 中最后一段选 $j$ 的最长不降子序列长度，再反向递推 $g_{i,j}$ 表示 $i\sim n$ 中最后一段选 $j$ 的最长不降子序列长度，最后枚举分界线 $i$，取 $f_{i,2}+g_{i + 1,1}$ 的最大值作为答案。

### 最优关键思路或技巧
- **思维方式**：将最终序列拆分为四段的思路是解决本题的关键，通过这种方式将问题转化为可处理的子问题。
- **算法优化**：使用动态规划可以将时间复杂度优化到 $O(n)$，避免了暴力枚举的高复杂度。
- **代码实现技巧**：可以通过压维的方式减少空间复杂度，如在动态规划中只使用一维数组来存储状态。

### 拓展思路
同类型题可以考虑序列元素种类增加，或者翻转操作次数增加的情况。类似算法套路可以用于解决其他需要通过区间操作来优化序列性质的问题，如区间修改求最大连续和等。

### 推荐题目
- [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：考察最长不下降子序列和最长下降子序列的求解。
- [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)：区间动态规划的经典题目。
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：求解序列的最大连续子段和。

### 个人心得总结
- 蒟蒻丁表示本题开阔了眼界，说明做此类题目有助于拓展思维。
- Karry5307提到自己思路独特，鼓励我们在解题时要有独立思考的能力，尝试不同的方法。

---
处理用时：44.89秒