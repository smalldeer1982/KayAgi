# 题目信息

# [CCC 2023 S2] Symmetric Mountains

## 题目描述

Rebecca is a tour guide and is trying to market the Rocky Mountains for her magazine. She recently took a beautiful picture consisting of $N$ mountains where the $i\text{-th}$ mountain from the left has a height $h_i$. She will crop this picture for her magazine, by possibly removing some mountains from the left side of the picture and possibly removing some mountains from the right side of the picture. That is, a crop consists of consecutive mountains starting from the $l\text{-th}$ to the $r\text{-th}$ mountain where $l \leq r$. To please her magazine readers, Rebecca will try to find the most symmetric crop.

We will measure the $asymmetric\ value$ of a crop as the sum of the absolute difference for every pair of mountains equidistant from the midpoint of the crop. To help understand that definition, note that the absolute value of $a$ number $v$, written as $|v|$, is the non-negative value of v: for example $\lvert -6 \rvert = 6$ and $|14| = 14$. The asymmetric value of a crop is the sum of all $|h_{l+i} - h_{r-i}|$ for $0 \leq i \leq \frac{r-l}{2}$. To put that formula in a different way, we pair up the mountains working from the outside in toward the centre, calculate the absolute difference in height of each of these pairs, and sum them up.

Because Rebecca does not know how wide the picture needs to be, for all possible crop lengths, find the asymmetric value of the most symmetric crop (the crop with the minimum asymmetric value).

## 说明/提示

Explanation of Output for Sample Input $1$:

We will show why the fifth value from the left is $2$.Let us try to compute all the asymmetric values of crops with length $5$.

The height of the mountains in the first crop is $[3, 1, 4, 1, 5]$. The asymmetric value of this crop is $|3 - 5| + |1 - 1| + |4 - 4| = 2$.

The height of the mountains in the second crop is $[1, 4, 1, 5, 9]$. The asymmetric value of this crop is $|1 - 9| + |4 - 5| + |1 - 1| = 9$.

The height of the mountains in the last crop is $[4, 1, 5, 9, 2]$. The asymmetric value of this crop is $|4 - 2| + |1 - 9| + |5 - 5| = 10$.

Hence, the most symmetric crop of length $5$ is $2$.

Explanation of Output for Sample Input $2$:

This sample satisfies the second subtask. Note that the only crop of length $4$ is $[1, 3, 5, 6]$ which has asymmetric value of $|1 - 6| + |3 - 5| = 7$.

**本题采用捆绑测试**：

- Subtask 1（5 points）：$1\leq N \leq 300$，$0\leq h_i \leq 10^5$。

- Subtask 2（5 points）：$1 \leq N \leq 5000$，$0 \leq h_i \leq 10^5$，保证山的高度从左到右单调不减。

- Subtask 3（5 points）：$1\leq N\leq 5000$，$0 \leq h_i \leq 10^5$。

## 样例 #1

### 输入

```
7
3 1 4 1 5 9 2```

### 输出

```
0 2 0 5 2 10 10```

## 样例 #2

### 输入

```
4
1 3 5 6```

### 输出

```
0 1 3 7```

# AI分析结果

• **综合分析与结论**：这些题解主要围绕如何优化暴力解法以降低时间复杂度。暴力解法通常是先枚举长度，再枚举左右端点，最后计算差值，时间复杂度为 \(O(n^3)\) 会超时。优化思路主要有以下几种：
    - **记忆化搜索**：记录已经计算过的区间不对称值，避免重复计算，如通过二维数组记录 \(d(l,r)\) 的值，时间复杂度优化到 \(O(n^2)\)。
    - **区间DP**：通过状态转移方程 \(dp_{i,j}=dp_{i + 1,j - 1}+|h_i - h_j|\) 来计算区间不对称值，同样时间复杂度为 \(O(n^2)\)。
    - **中心扩展**：枚举对称点然后向左右两边扩展，计算不对称值，时间复杂度 \(O(n^2)\)，但实际运行速度较快。

从思路清晰度、代码可读性、优化程度综合来看，以下题解质量较高：
  - **作者：ZepX_D (赞：11)**
    - **星级**：4星
    - **关键亮点**：思路简洁清晰，通过枚举对称点向两边扩展计算不对称值，代码实现简单，实际运行速度快。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

int h[5010],ans[5010],l,r,s;

int main()
{
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int n;cin >> n;
	memset(ans,0x3f,sizeof(ans));
	for (int i = 1;i <= n;i++) cin >> h[i];
	for (int i = 1;i <= n;i++)
	{
		s = 0,l = r = i;
		while(l && r <= n)
		{
			ans[r - l + 1] = min(ans[r - l + 1],s);
			l--,r++,s += abs(h[r]-h[l]);
		}

		s = abs(h[i + 1]-h[i]),l = i,r = i + 1;
		while(l && r <= n)
		{
			ans[r - l + 1] = min(ans[r - l + 1],s);
			l--,r++,s += abs(h[r]-h[l]);	
		}
	}
	for (int i = 1;i <= n;i++) cout << ans[i] << ' ';
	return 0;
}
```
    - **核心思想**：先对所有长度的最小不对称值初始化为极大值，然后分别枚举奇数长度和偶数长度的对称中心，向两边扩展，在扩展过程中更新对应长度的最小不对称值。
  - **作者：玄学OIER荷蒻 (赞：9)**
    - **星级**：4星
    - **关键亮点**：采用区间DP方法，通过预处理长度 \(0\) 和 \(1\) 的区间，利用状态转移方程 \(dp_{i,j}=dp_{i + 1,j - 1}+|h_i - h_j|\) 计算区间不对称值，代码简短。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include <bits/stdc++.h>

#define magic ios::sync_with_stdio(false);cin.tie(0);cout.tie(0); 

using namespace std;

int dp[5010][5010],h[5010],minn[5010],n;

int main()
{
    magic
    cin>>n;
    for (register int i = 1;i <= n;i++) cin>>h[i];
    for (register int j = 2;j <= n;j++){
        minn[j]=250000000;
        for (register int i = 1;i <= n - j + 1;i++){
            dp[i][i + j - 1]=dp[i + 1][i + j - 2]+abs(h[i]-h[i + j - 1]);
            minn[j]=min(minn[j],dp[i][i + j - 1]);
        }
    }
    for (register int i = 1;i <= n;i++) cout<<minn[i]<<' ';
    return 0;
}
```
    - **核心思想**：通过两层循环枚举区间长度和区间起点，利用状态转移方程计算每个区间的不对称值，并记录每个长度下的最小不对称值。
  - **作者：Loser_Syx (赞：27)**
    - **星级**：4星
    - **关键亮点**：先给出暴力解法，再通过举例说明优化思路，利用数组记录之前算过的差值，使每次计算不对称值为 \(O(1)\) 复杂度，根据奇偶性分开记录差值。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include <iostream>

using namespace std;
typedef long long ll;

ll h[10101];
ll a[10101], b[10101];

int main(){
    int n;
    scanf("%lld", &n);
    for(int i = 1; i <= n; ++i) scanf("%lld", &h[i]);
    printf("0 ");
    for(int i = 2; i <= n; ++i){
        if(i % 2 == 1){
            int l = n - i + 1, r = n;
            ll cz = 1e15;
            while(r >= i){
                a[r]=a[r - 1]+abs(h[r]-h[l]);
                cz = min(cz, a[r]);
                --l;--r;
            }
            printf("%lld ", cz);
        }else{
            int l = n - i + 1, r = n;
            ll cz = 1e15;
            while(r >= i){
                b[r]=b[r - 1]+abs(h[r]-h[l]);
                cz = min(cz, b[r]);
                --l;--r;
            }
            printf("%lld ", cz);
        }
    }
    return 0;
}
```
    - **核心思想**：根据区间长度的奇偶性，分别从右往左枚举区间，利用数组记录不对称值的累加和，从而快速得到每个长度下的最小不对称值。

• **最优关键思路或技巧**：通过记忆化或动态规划的方式避免重复计算区间不对称值，将时间复杂度从 \(O(n^3)\) 优化到 \(O(n^2)\)。如区间DP利用状态转移方程 \(dp_{i,j}=dp_{i + 1,j - 1}+|h_i - h_j|\)，中心扩展法通过枚举对称中心向两边扩展并记录最小不对称值。

• **可拓展思路**：此类题目属于区间相关的最值问题，常见套路是通过动态规划或记忆化搜索来优化暴力枚举。类似题目通常涉及对区间的某种度量计算，并求满足特定条件的区间最值。

• **相似知识点洛谷题目**：
    - [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
    - [P3146 [USACO16OPEN]248 G](https://www.luogu.com.cn/problem/P3146)
    - [P1063 [NOIP2006 提高组] 能量项链](https://www.luogu.com.cn/problem/P1063)

• **个人心得摘录与总结**：部分题解提到在递归计算时要注意记录是否计算过，避免重复计算导致TLE，如定义 `vis` 数组标记已经计算过的区间不对称值。这表明在解决这类问题时，对已经计算的结果进行有效的管理和复用是优化算法的重要手段。 

---
处理用时：37.07秒