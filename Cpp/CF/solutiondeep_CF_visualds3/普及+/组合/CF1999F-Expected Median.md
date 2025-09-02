# 题目信息

# Expected Median

## 题目描述

Arul has a binary array $ ^{\text{∗}} $ $ a $ of length $ n $ .

He will take all subsequences $ ^{\text{†}} $ of length $ k $ ( $ k $ is odd) of this array and find their median. $ ^{\text{‡}} $

What is the sum of all these values?

As this sum can be very large, output it modulo $ 10^9 + 7 $ . In other words, print the remainder of this sum when divided by $ 10^9 + 7 $ .

 $ ^{\text{∗}} $ A binary array is an array consisting only of zeros and ones.

 $ ^{\text{†}} $ An array $ b $ is a subsequence of an array $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements. Subsequences don't have to be contiguous.

 $ ^{\text{‡}} $ The median of an array of odd length $ k $ is the $ \frac{k+1}{2} $ -th element when sorted.

## 说明/提示

In the first test case, there are four subsequences of $ [1,0,0,1] $ with length $ k=3 $ :

- $ [1,0,0] $ : median $ = 0 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [0,0,1] $ : median $ = 0 $ .

 The sum of the results is $ 0+1+1+0=2 $ .In the second test case, all subsequences of length $ 1 $ have median $ 1 $ , so the answer is $ 5 $ .

## 样例 #1

### 输入

```
8
4 3
1 0 0 1
5 1
1 1 1 1 1
5 5
0 1 0 1 0
6 3
1 0 1 0 1 1
4 3
1 0 1 1
5 3
1 0 1 1 0
2 1
0 0
34 17
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
2
5
0
16
4
7
0
333606206```

# AI分析结果


### 💡 Kay的C++算法解析：Expected Median 深入学习指南 💡

**题目解读与核心算法识别**  
✨ **本题主要考察**：组合数学应用（Combinatorics）  
🗣️ **初步分析**：  
> 解决"Expected Median"的关键在于运用组合数学技巧。想象你在一个装满0/1糖果的罐子里挑选k颗糖，中位数是1的条件是：至少有m=(k+1)/2颗1糖果（因为k是奇数）。组合数学就像计算不同口味搭配方案的方法——统计所有满足条件的选糖方案数量。  
> - 所有题解都采用同一核心思路：枚举1的个数i（从m到k），计算方案数C(cnt1,i)*C(cnt0,k-i)并求和  
> - 核心难点在于高效计算组合数（需预处理阶乘和逆元）及正确设定枚举边界  
> - 可视化设计将采用"组合数计算器"像素游戏：左侧动态展示阶乘计算过程（像素方块堆叠），右侧显示组合数乘积累加。关键变量cnt0/cnt1用不同颜色像素块表示，枚举进度以进度条展示，每步伴随8-bit音效（阶乘计算"嘀"，组合数相乘"叮"，累加"咔"）

---

### 2. 精选优质题解参考

**题解一：aeiouaoeiu (5星)**  
* **点评**：  
  思路直击本质——将"至少m个1"转化为枚举"恰好i个1"，逻辑推导清晰完整。代码规范：①预处理阶乘和逆元数组，实现O(1)组合数查询；②边界处理严谨（C函数中判断a<b）；③变量名cnt/frac/inv含义明确。亮点在于空间优化（逆元数组倒推计算）和高效性（O(n+k)）。调试建议：maxn=200000需开足够大数组，避免RE。

**题解二：Pink_Cut_Tree (5星)**  
* **点评**：  
  教学价值突出：解析部分用自然语言解释数学原理（"从c个1选i个，n-c个0选k-i个"），降低理解门槛。代码亮点：①模块化设计（ksm快速幂独立函数）；②防御性编程（C函数中n<m的判断）；③详细注释说明逆元原理。可改进点：每次调用C函数都计算逆元稍慢，预处理逆元数组更优。

**题解三：Gapple (4星)**  
* **点评**：  
  提供独特视角——枚举0的个数（0到⌊k/2⌋），等价但不同的组合解释。代码亮点：①自定义add/mul取模函数增强可读性；②对称处理cnt[0]/cnt[1]；③逆元预处理方法高效。思考启发：同一问题可多角度转化，枚举对象的选择影响代码简洁性。

---

### 3. 核心难点辨析与解题策略

1. **难点1：组合问题转化**  
   * **分析**： 中位数为1的条件隐含"1的数量≥0的数量"，需转化为可计算的组合模型（∑[i=m→k]C(cnt1,i)C(cnt0,k-i)）。优质题解均通过变量cnt1/cnt0剥离无效信息。  
   * 💡 **学习笔记**： 复杂条件 → 数学量化 → 组合模型

2. **难点2：组合数高效计算**  
   * **分析**： 直接计算阶乘会溢出，需预处理阶乘+逆元。逆元计算利用费马小定理（a^{mod-2}），逆元数组可通过倒推优化（inv[i]=inv[i+1]*(i+1)%mod）。  
   * 💡 **学习笔记**： 模质数组合数 = 阶乘 × 逆元乘积

3. **难点3：枚举边界确定**  
   * **分析**： 枚举i时需同时满足：i∈[m, min(k,cnt1)] 且 k-i≤cnt0。Super_Cube的优化：i从max(m, k-cnt0)开始，避免无效计算。  
   * 💡 **学习笔记**： 组合枚举先验范围分析可提速

#### ✨ 解题技巧总结
- **技巧1：问题降维** - 忽略原序列顺序，聚焦0/1计数  
- **技巧2：预处理为王** - 阶乘/逆元数组预计算，O(1)响应查询  
- **技巧3：防御性组合函数** - C(n,m)中先判n≥m, 避免非法访问  

---

### 4. C++核心代码实现赏析

**本题通用核心实现参考**  
```cpp
#include <iostream>
using namespace std;
typedef long long LL;
const int MOD = 1e9+7, N = 200005;

LL fact[N], invFact[N];

LL qpow(LL base, LL exp, LL mod) {
    LL res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) 
        fact[i] = fact[i-1] * i % MOD;
    invFact[N-1] = qpow(fact[N-1], MOD-2, MOD);
    for (int i = N-2; i >= 0; i--) 
        invFact[i] = invFact[i+1] * (i+1) % MOD;
}

LL C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n-k] % MOD;
}

int main() {
    precompute();
    int T; cin >> T;
    while (T--) {
        int n, k, cnt1 = 0; 
        cin >> n >> k;
        for (int i = 0, x; i < n; i++) {
            cin >> x;
            cnt1 += x;
        }
        int cnt0 = n - cnt1, m = (k+1)/2;
        LL ans = 0;
        for (int i = m; i <= k; i++) 
            if (k-i <= cnt0 && i <= cnt1)
                ans = (ans + C(cnt1,i) * C(cnt0,k-i)) % MOD;
        cout << ans << endl;
    }
    return 0;
}
```
**代码解读概要**：  
① 预处理fact/invFact数组实现O(1)组合数查询  
② qpow快速幂计算模逆元（MOD为质数）  
③ 主逻辑：统计cnt1/cnt0 → 枚举i → 累加合法组合数乘积  

---

**题解一（aeiouaoeiu）片段赏析**  
* **亮点**：逆元数组倒推计算，空间效率优化  
* **核心代码**：
  ```cpp
  inv[maxn-1] = qpow(frac[maxn-1], p-2);
  for(int i=maxn-1;i>=1;i--) 
      inv[i-1]=inv[i]*i%p;  // 逆元递推关键！
  ```
* **代码解读**：为什么从高位倒推？因 `(i!)^-1 = ( (i+1)! )^-1 * (i+1)`。计算inv[i-1]时只需乘(i+1)，比独立求每个逆元高效。

**题解二（Pink_Cut_Tree）片段赏析**  
* **亮点**：自解释型组合数函数  
* **核心代码**：
  ```cpp
  int C(int n,int m){
      if(n<m) return 0;  // 边界守卫
      return f[n] * ksm(f[m],mod-2) % mod * ksm(f[n-m],mod-2) % mod;
  }  
  ```
* **代码解读**：每次调用都单独计算逆元，虽比预处理慢但代码更易理解。注意`ksm(f[m],mod-2)`即f[m]的逆元——费马小定理应用。

**题解三（Gapple）片段赏析**  
* **亮点**：枚举0的个数的等价实现  
* **核心代码**：
  ```cpp
  for (int i = 0; i <= k >> 1; ++i)  // 枚举0的个数
      ans = add(ans, mul(C(cnt0, i), C(cnt1, k-i)));
  ```
* **代码解读**：`k>>1`即⌊k/2⌋。当0的个数≤k/2时，1的个数必然≥k/2+1（因k奇），满足中位数=1条件。与主流解法殊途同归！

---

### 5. 算法可视化：像素动画演示

**主题**：8-bit风格"组合数计算器"  
**核心演示流程**：  
```plaintext
  [初始化] 像素网格划分三区：
    ├─ 阶乘区：动态构建fact数组（像素块堆叠动画）
    ├─ 逆元区：红色像素块从右向左递推（伴随"嘟"声）
    └─ 组合区：cnt1(蓝色)/cnt0(黄色)像素块碰撞→迸发组合数结果

  [关键动画] 
  1. 枚举i时：进度条从m移动到k，当前i值高亮闪烁
  2. 计算C(cnt1,i)：蓝色块飞入组合公式，显示计算结果
  3. 累加时：黄色进度条增长，播放"咔咔"计数音效

  [游戏化设计]
  - 控制面板：步进执行/自动播放（调速滑块）
  - 音效系统：阶乘计算→"嘀"，逆元→"嘟"，组合数→"叮"，错误→爆破音
  - 关卡成就：每完成一个i值计算得1星，满k-m+1星通关
```

---

### 6. 拓展练习与相似问题思考

**通用套路迁移**：  
组合计数用于解决"满足条件的子集数量"问题，适用于：  
1. 限定元素数量的选择方案（如安全系统）  
2. 二进制子序列约束问题（如本题）  
3. 图论中路径计数（如网格图路径）  

**推荐练习**：  
1. [洛谷 P2638 安全系统](https://www.luogu.com.cn/problem/P2638)  
   → **巩固组合数应用**：两种物品在多个容器中的分配问题  
2. [洛谷 P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)  
   → **进阶预处理技巧**：组合数取模前缀和  
3. [洛谷 P3414 二进制](https://www.luogu.com.cn/problem/P3414)  
   → **变形挑战**：统计二进制子序列满足特殊条件的数量  

---

### 7. 学习心得与经验分享

> **参考经验（来自 aeiouaoeiu）**：  
> "将'至少m个'转化为'恰好i个'求和，是组合计数的经典技巧"  
> **参考经验（来自 Gapple）**：  
> "枚举0的个数和枚举1的个数本质相通，但提供不同视角"  

**Kay的总结**：  
1. 组合问题常有多解，选择最直观的转化路径  
2. 调试时验证小数据（如n=3,k=2）比大样本更有效  
3. 预处理数组大小要预留余量（≥200000）  

---

本次解析就到这里！用组合数学将复杂问题化繁为简，就像用乐高积木组装模型——掌握基础模块，就能构建精彩解法。下次再见！🚀

---
处理用时：217.31秒