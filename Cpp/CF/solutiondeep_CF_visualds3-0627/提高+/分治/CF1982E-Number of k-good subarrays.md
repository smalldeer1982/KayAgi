# 题目信息

# Number of k-good subarrays

## 题目描述

Let $ bit(x) $ denote the number of ones in the binary representation of a non-negative integer $ x $ .

A subarray of an array is called  $ k $ -good if it consists only of numbers with no more than $ k $ ones in their binary representation, i.e., a subarray $ (l, r) $ of array $ a $ is good if for any $ i $ such that $ l \le i \le r $ condition $ bit(a_{i}) \le k $ is satisfied.

You are given an array $ a $ of length $ n $ , consisting of consecutive non-negative integers starting from $ 0 $ , i.e., $ a_{i} = i $ for $ 0 \le i \le n - 1 $ (in $ 0 $ -based indexing). You need to count the number of  $ k $ -good subarrays in this array.

As the answer can be very large, output it modulo $ 10^{9} + 7 $ .

## 说明/提示

For the first test case $ a = [0, 1, 2, 3, 4, 5] $ , $ k = 1 $ .

To find the answer, let's write all the numbers in binary representation:

 $ $$$a = [\color{green}{000}, \color{green}{001}, \color{green}{010}, \color{red}{011}, \color{green}{100}, \color{red}{101}] $ $ </p><p>From this, it can be seen that the numbers  $ 3 $  and  $ 5 $  have  $ 2 \\ge (k = 1) $  ones in their binary representation, so the answer should include all subarrays that do not contain either  $ 3 $  or  $ 5 $ , which are the subarrays (in  $ 0 $ -based indexing): ( $ 0 $ ,  $ 0 $ ), ( $ 0 $ ,  $ 1 $ ), ( $ 0 $ ,  $ 2 $ ), ( $ 1 $ ,  $ 1 $ ), ( $ 1 $ ,  $ 2 $ ), ( $ 2 $ ,  $ 2 $ ), ( $ 4 $ ,  $ 4$$$).

## 样例 #1

### 输入

```
10
6 1
16 2
1 1
3 1
31 3
14 1
1337 5
100000 20
795569939321040850 56
576460752303423268 59```

### 输出

```
7
35
1
6
155
8
7323
49965
741136395
66679884```

# AI分析结果



**唯一算法分类**：分治递归与二进制分解

---

**综合分析与结论**  
本题核心在于如何高效统计满足条件的连续子数组数目。由于n极大（1e18），必须采用分治策略，结合二进制数的特性分解问题。关键思路是将数组分为最大2的幂部分和剩余部分，递归处理左右子问题，并计算跨区间的贡献。

**核心算法流程**：  
1. 找到最大2的幂mx=2^c，将数组分为0~mx-1（左）和mx~n-1（右）。  
2. 左部分递归求解sol(mx, k)，右部分转化为sol(n-mx, k-1)（因最高位为1，剩余位数需满足bit<=k-1）。  
3. 若c<=k，左部分所有数均有效，右部分有效数为s=min(2^k-1, n-mx)，贡献为mx*s。  
4. 递归终止条件：k=0时只能有单个0元素，n=1时返回1。  

**可视化设计要点**：  
- **动画演示**：用树状结构展示递归分解，每次分裂显示mx值和k的变化。  
- **颜色标记**：左部分标绿色（有效），右部分标橙色（需递归处理），贡献部分用黄色高亮。  
- **步进控制**：允许单步查看分解过程，展示当前递归层的mx、k、贡献计算。  

---

**题解清单 (≥4星)**  
1. **SFlyer（5星）**  
   - 思路清晰，代码简洁，记忆化优化避免重复计算。  
   - 关键点：递归分解与中间贡献的精妙处理。  
   ```cpp
   ll sol(ll n,ll k){
       if (k==0 || n==1) return 1;
       ll c=0; while ((1ll<<c+1)<n) c++;
       ll mx=1ll<<c, l=sol(mx,k), r=sol(n-mx,k-1);
       ll ans = (l + r) % mod;
       if (c <=k) ans = (ans + (min((1ll<<k)-1,n-mx) % mod) * (mx % mod)) % mod;
       return ans;
   }
   ```

2. **yshpdyt（4星）**  
   - 预处理动态规划表加速计算，结构体合并区间信息。  
   - 维护极长前缀/后缀，合并时计算跨区贡献。  
   ```cpp
   struct node{ ll l,r,ans,len; };
   node operator+(const node &a, const node &b){
       node c = {a.l, b.r, (a.ans + b.ans + a.r*b.l) % mod, a.len + b.len};
       if (a.l == a.len) c.l += b.l;
       if (b.r == b.len) c.r += a.r;
       return c;
   }
   ```

3. **KingPowers（4星）**  
   - 预处理f数组处理2的幂情况，代码结构清晰。  
   - 合并时计算前缀后缀贡献，类似线段树合并。  
   ```cpp
   struct node{ mint len,pre,suf,ans; };
   node operator+(const node &a, const node &b){
       node res; res.len = a.len + b.len;
       res.ans = a.ans + b.ans + a.suf*b.pre;
       // ... 前缀后缀处理
   }
   ```

---

**最优思路提炼**  
1. **二进制分解**：利用最高位将问题分解为左右子问题。  
2. **递归合并**：左部分全有效时，跨区贡献为左长度×右有效数。  
3. **预处理优化**：对2的幂情况预处理，加速递归过程。  

**同类型题套路**  
- 分治处理二进制特性问题（如求区间异或和）。  
- 动态规划预处理固定结构，加速递归。  

**推荐题目**  
1. P6104 [数位DP练习]  
2. P2651 [添加括号（分治）]  
3. P7078 [子序列计数（滑动窗口变种）]  

---

**个人心得摘录**  
- 调试时发现c的计算需精确到mx是最大的小于n的2次幂。  
- 中间贡献的s需要与n-mx取最小，避免右侧超限。  

---

**可视化算法演示**  
```javascript
// 示例：递归分解动画（伪代码）
function drawRecursion(n, k, depth) {
    let mx = 最大2的幂;
    绘制当前层分解为 [0, mx) 和 [mx, n);
    高亮左侧绿色，右侧橙色;
    if (c <=k) 绘制黄色贡献区域 mx*s;
    // 递归绘制左右子层
    drawRecursion(mx, k, depth+1);
    drawRecursion(n-mx, k-1, depth+1);
}
// 控制面板实现步进、速度调节
```

**复古像素风格设计**  
- **调色板**：8位绿色（左）、橙色（右）、黄色（贡献）。  
- **音效**：分解时播放8位"blip"，递归终止时播放胜利音效。  
- **Canvas动画**：网格显示当前n的二进制分解，动态绘制递归树。

---
处理用时：110.87秒