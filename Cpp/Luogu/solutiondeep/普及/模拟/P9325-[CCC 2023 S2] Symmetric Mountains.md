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

### 综合分析与结论
本题要求对于所有可能的作物长度，找出最对称作物（不对称值最小的作物）的不对称值。各题解主要围绕暴力枚举和优化展开，优化思路多为利用区间之间的关系减少重复计算，常见方法有记忆化搜索、区间 DP 等。

### 所选题解
- **作者：ZepX_D（5星）**
    - **关键亮点**：思路清晰，通过枚举中间对称点向两边扩展，避免了复杂的状态转移方程，代码简洁易懂，时间复杂度为 $O(n^2)$ 且实际运行效率高。
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
            ans[r-l+1] = min(ans[r-l+1],s);
            l--,r++,s += abs(h[r]-h[l]);
        }

        s = abs(h[i+1]-h[i]),l = i,r = i+1;
        while(l && r <= n)
        {
            ans[r-l+1] = min(ans[r-l+1],s);
            l--,r++,s += abs(h[r]-h[l]);	
        }
    }
    for (int i = 1;i <= n;i++) cout << ans[i] << ' ';
    return 0;
}
```
    - **核心实现思想**：枚举中间对称点 $i$，分长度为奇数和偶数两种情况向两边扩展，计算当前不对称性 $s$，并更新对应长度的最小不对称性 $ans_{r - l + 1}$。

- **作者：玄学OIER荷蒻（4星）**
    - **关键亮点**：明确指出是区间 DP 问题，状态转移方程推导清晰，代码简洁规范，去除注释和优化后代码长度较短。
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
    for (register int i=1;i<=n;i++) cin>>h[i];
    for (register int j=2;j<=n;j++){
        minn[j]=250000000;
        for (register int i=1;i<=n-j+1;i++){
            dp[i][i+j-1]=dp[i+1][i+j-2]+abs(h[i]-h[i+j-1]);
            minn[j]=min(minn[j],dp[i][i+j-1]);
        }
    }
    for (register int i=1;i<=n;i++) cout<<minn[i]<<' ';
    return 0;
}
```
    - **核心实现思想**：设 $dp_{i,j}$ 表示区间 $[i,j]$ 的不对称值，状态转移方程为 $dp_{i,j}=dp_{i + 1,j - 1}+|h_i - h_j|$，枚举区间长度和起点，更新对应长度的最小不对称性 $minn_j$。

- **作者：Loser_Syx（4星）**
    - **关键亮点**：从暴力枚举出发，详细阐述优化思路，通过记录之前算过的差值，将每次计算复杂度降为 $O(1)$，代码实现逻辑清晰。
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
            int l = n-i+1, r = n;
            ll cz = 1e15;
            while(r >= i){
                a[r] = a[r-1] + abs(h[r] - h[l]);
                cz = min(cz, a[r]);
                --l;--r;
            }
            printf("%lld ", cz);
        }else{
            int l = n-i+1, r = n;
            ll cz = 1e15;
            while(r >= i){
                b[r] = b[r-1] + abs(h[r] - h[l]);
                cz = min(cz, b[r]);
                --l;--r;
            }
            printf("%lld ", cz);
        }
    }
    return 0;
}
```
    - **核心实现思想**：分奇偶长度记录之前算过的差值，避免重复计算，枚举长度，更新对应长度的最小不对称性。

### 最优关键思路或技巧
- **记忆化搜索/区间 DP**：利用区间之间的关系，通过状态转移方程减少重复计算，如 $dp_{i,j}=dp_{i + 1,j - 1}+|h_i - h_j|$。
- **枚举中间对称点扩展**：枚举中间对称点向两边扩展，避免枚举所有区间，降低复杂度。

### 可拓展之处
同类型题或类似算法套路：其他区间最值问题，如求区间最大/最小和、区间最长/最短子序列等，可采用类似的区间 DP 或记忆化搜索思路。

### 推荐题目
- [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
- [P3205 [HNOI2010]合唱队](https://www.luogu.com.cn/problem/P3205)
- [P1040 [NOIP2003 提高组] 加分二叉树](https://www.luogu.com.cn/problem/P1040)

### 个人心得摘录与总结
- **作者：0x282e202e2029**：递归计算时需定义 `vis` 数组记录是否计算过，避免重复计算导致 TLE，同时要注意函数越界判断。
- **作者：leiaxiwo**：重新开 `bool` 二维数组 `vis` 判断是否已经计算过，若已计算则直接返回答案，否则递归计算并标记。 

---
处理用时：42.52秒