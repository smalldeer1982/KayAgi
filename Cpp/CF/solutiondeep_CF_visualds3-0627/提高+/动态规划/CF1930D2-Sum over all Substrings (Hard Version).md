# 题目信息

# Sum over all Substrings (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ t $ and $ n $ . You can make hacks only if both versions of the problem are solved.

For a binary $ ^\dagger $ pattern $ p $ and a binary string $ q $ , both of length $ m $ , $ q $ is called $ p $ -good if for every $ i $ ( $ 1 \leq i \leq m $ ), there exist indices $ l $ and $ r $ such that:

- $ 1 \leq l \leq i \leq r \leq m $ , and
- $ p_i $ is a mode $ ^\ddagger $ of the string $ q_l q_{l+1} \ldots q_{r} $ .

For a pattern $ p $ , let $ f(p) $ be the minimum possible number of $ \mathtt{1} $ s in a $ p $ -good binary string (of the same length as the pattern).

You are given a binary string $ s $ of size $ n $ . Find $ $$$\sum_{i=1}^{n} \sum_{j=i}^{n} f(s_i s_{i+1} \ldots s_j). $ $  In other words, you need to sum the values of  $ f $  over all  $ \\frac{n(n+1)}{2} $  substrings of  $ s $ .</p><p> $ ^\\dagger $  A binary <span class="tex-font-style-it">pattern</span> is a string that only consists of characters  $ \\mathtt{0} $  and  $ \\mathtt{1} $ .</p><p> $ ^\\ddagger $  Character  $ c $  is a mode of string  $ t $  of length  $ m $  if the number of occurrences of  $ c $  in  $ t $  is at least  $ \\lceil \\frac{m}{2} \\rceil $ . For example,  $ \\mathtt{0} $  is a mode of  $ \\mathtt{010} $ ,  $ \\mathtt{1} $  is not a mode of  $ \\mathtt{010} $ , and both  $ \\mathtt{0} $  and  $ \\mathtt{1} $  are modes of  $ \\mathtt{011010}$$$.

## 说明/提示

In the first test case, the only $ \mathtt{1} $ -good string is $ \mathtt{1} $ . Thus, $ f(\mathtt{1})=1 $ .

In the second test case, $ f(\mathtt{10})=1 $ because $ \mathtt{01} $ is $ \mathtt{10} $ -good, and $ \mathtt{00} $ is not $ \mathtt{10} $ -good. Thus, the answer is $ f(\mathtt{1})+f(\mathtt{10})+f(\mathtt{0}) = 1 + 1 + 0 = 2 $ .

In the third test case, $ f $ equals to $ 0 $ for all $ 1 \leq i \leq j \leq 5 $ . Thus, the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
1
1
2
10
5
00000
20
11110110000000111111```

### 输出

```
1
2
0
346```

# AI分析结果



---

## 题目重写

### 题目描述

这是该问题的困难版本。两个版本之间的唯一区别在于对 $t$ 和 $n$ 的约束。只有当两个版本的问题都解决时，才能进行 hack。

对于长度为 $m$ 的二进制模式 $p$ 和二进制字符串 $q$，若对于每个 $i$（$1 \leq i \leq m$），存在满足以下条件的下标 $l$ 和 $r$：
- $1 \leq l \leq i \leq r \leq m$，且
- $p_i$ 是子串 $q_l q_{l+1} \ldots q_r$ 的众数$^\ddagger$，

则称 $q$ 是 $p$-good 的。定义 $f(p)$ 为所有与 $p$ 等长的 $p$-good 字符串中 $1$ 的最小数量。

给定长度为 $n$ 的二进制字符串 $s$，计算：
$$ \sum_{i=1}^{n} \sum_{j=i}^{n} f(s_i s_{i+1} \ldots s_j) $$
即对 $s$ 的所有 $\frac{n(n+1)}{2}$ 个子串的 $f$ 值求和。

$^\dagger$ 二进制模式指仅包含字符 $0$ 和 $1$ 的字符串。  
$^\ddagger$ 若字符 $c$ 在字符串 $t$ 中的出现次数至少为 $\lceil \frac{|t|}{2} \rceil$，则称 $c$ 是 $t$ 的众数。

---

## 算法分类：线性DP

---

## 题解分析与结论

### 核心思路与难点
所有题解均基于以下关键观察：  
**每个 $q$ 中的 $1$ 可以覆盖 $p$ 中连续的三个位置**。例如，若在 $q_j$ 放置 $1$，则 $p$ 的 $j-1,j,j+1$ 位置的约束均可被满足。

#### 动态规划设计
1. **状态定义**：  
   - `f[i]` 表示以 `i` 结尾的所有子串的贡献总和（如 selcouth 解法）
   - 或维护距离最近 $1$ 的四种状态（如 IGA_Indigo 解法）

2. **状态转移**：  
   - **字符为 1**：`f[i] = f[max(i-3, 0)] + i`（覆盖三个位置）
   - **字符为 0**：`f[i] = f[i-1]`（无需新增 $1$）

#### 优化手段
- **空间压缩**：通过滚动数组将空间复杂度优化至 $O(1)$
- **状态合并**：仅维护四种距离状态（0,1,2,≥3）及其贡献

---

## 题解评分（≥4星）

1. **selcouth 的解法（⭐⭐⭐⭐⭐）**  
   - **亮点**：  
     - 直击问题本质，直接推导出线性 DP 状态转移方程  
     - 代码简洁，时间复杂度 $O(n)$，空间复杂度可优化至 $O(1)$  
   - **代码片段**：
     ```cpp
     for(int i = 1; i<=n; i++) {
         if(s[i] == '1') 
             f[i] = f[max(i-3, 0ll)] + i;
         else 
             f[i] = f[i-1];
     }
     ```

2. **IGA_Indigo 的解法（⭐⭐⭐⭐）**  
   - **亮点**：  
     - 通过维护四个状态实现空间优化  
     - 巧妙处理距离最近 $1$ 的覆盖范围  
   - **代码片段**：
     ```cpp
     for(int i=1;i<=n;i++) {
         gs[0] += gs[1]; gs[1]=gs[2]; gs[2]=gs[3]; gs[3]=0;
         gx[0] += gx[1]; gx[1]=gx[2]; gx[2]=gx[3]; gx[3]=0;
         if(s[i]=='1') {
             gs[3] = gs[0]; gx[3] = gx[0] + gs[0];
             gs[0] = gx[0] = 0;
         }
         ans += gx[0]+gx[1]+gx[2]+gx[3];
     }
     ```

3. **phigy 的解法（⭐⭐⭐⭐）**  
   - **亮点**：  
     - 类似状态压缩，代码实现简洁  
     - 通过维护 `lst` 和 `num` 数组实现高效贡献计算  

---

## 最优思路提炼

### 关键技巧
1. **覆盖窗口跳跃**：每个 $1$ 覆盖三个位置，跳过已覆盖区域  
2. **贡献累加**：以当前下标为右端点的所有子串贡献自然累加  
3. **状态压缩**：仅维护有限状态（如距离最近 $1$ 的四种情况）

---

## 同类型题推荐
1. [LeetCode 198. 打家劫舍](https://leetcode.com/problems/house-robber/)  
   （状态转移：是否选择当前房屋）  
2. [CF 1930D1 Sum over all Substrings (Easy Version)](https://www.luogu.com.cn/problem/CF1930D1)  
   （相同问题的小规模版本）  
3. [LeetCode 413. 等差数列划分](https://leetcode.com/problems/arithmetic-slices/)  
   （利用滑动窗口统计子数组贡献）

---

## 可视化与算法演示

### 动态规划动画方案
1. **网格展示**：  
   - 绘制横向网格表示字符串位置，纵向网格表示 DP 状态  
   - 使用不同颜色标记状态转移路径（如绿色表示新增 $1$，红色表示继承）

2. **高亮机制**：  
   - 当前字符高亮闪烁  
   - 覆盖范围（三个位置）用半透明色块标注  
   - 状态转移时显示箭头动画

3. **复古像素风格**：  
   - **颜色方案**：  
     - 状态 0-3 用黄/蓝/绿/红表示  
     - 音效：8-bit 风格音效（如放置 $1$ 时播放 "coin" 音效）
   - **Canvas 动画**：  
     - 每个状态用 16x16 像素块表示  
     - 自动模式以 2 FPS 步进，手动模式支持暂停/单步

### 示例动画流程
```
初始状态：[0,0,0,0]
处理字符1（位置3）：
  覆盖范围 [1-3]，状态转移 → [0,0,0,1]
贡献增加 3（对应所有以3结尾的子串）
```

---

## 个人心得摘录
> "当发现每个 $1$ 可以覆盖三个位置时，问题豁然开朗。调试时通过打印状态转移表，才理解为何需要维护四个状态。" —— IGA_Indigo  
> "将问题转换为贡献累加而非逐个计算子串，是突破时间复杂度的关键。" —— selcouth

---

## 核心代码实现

### 线性DP解法（selcouth）
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+10;
int t, n, f[maxn];
string s;

signed main() {
    cin >> t;
    while(t--) {
        cin >> n >> s;
        int ans = 0;
        s = ' ' + s;
        f[0] = 0;
        for(int i = 1; i<=n; i++) {
            if(s[i] == '1')
                f[i] = f[max(i-3, 0ll)] + i;
            else 
                f[i] = f[i-1];
            ans += f[i];
        }
        cout << ans << '\n';
    }
}
```

---

通过结合状态压缩和贡献累加的思想，该问题在线性时间复杂度内得到高效解决。

---
处理用时：99.34秒