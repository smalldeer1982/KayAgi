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

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：组合数学（计数问题）

🗣️ **初步分析**：
> 解决"Expected Median"这道题，关键在于运用**组合数学**技巧。想象你有一袋子红球（1）和蓝球（0），要计算所有取出k个球的组合中，红球过半的取法总数。在本题中：
> - 核心思路：统计所有1的个数≥(k+1)/2的子序列数量
> - 实现方法：设1的总数为c，则答案为Σ[C(c,i)×C(n-c,k-i)]，其中i从m=(k+1)/2到min(c,k)
> - 可视化设计：用像素网格展示数组元素（红/蓝球），动态演示选球过程
> - 复古游戏化：FC风格像素动画，选球时播放"啾"音效，成功时播放"胜利"音效，控制面板支持单步/自动播放

---

#### 2. 精选优质题解参考
**题解一 (来源：aeiouaoeiu)**
* **点评**：
  思路直击本质，将中位数条件转化为组合计数问题（1的个数≥(k+1)/2）。代码结构清晰：
  - 预处理阶乘和逆元（O(n)）
  - 主逻辑简洁（O(k)枚举）
  - 边界处理严谨（C函数处理非法情况）
  亮点：时间复杂度优化到位，变量命名规范（cnt统计1的数量）

**题解二 (来源：Pink_Cut_Tree)**
* **点评**：
  数学推导清晰，用快速幂求逆元实现组合数计算。代码亮点：
  - 独立封装ksm函数（快速幂）
  - 阶乘数组f[]预处理巧妙
  - 循环边界明确（i≤min(k,cnt)）
  实践价值：代码可直接用于竞赛，调试心得（边界测试）值得学习

**题解三 (来源：cjh20090318)**
* **点评**：
  解题框架完整，包含问题扩展思考（非二进制数组解法）。代码亮点：
  - 逆元线性递推优化（O(n)预处理）
  - 组合数函数C()包含安全校验
  - 变量作用域控制严格
  启发性：通过子问题分解展示组合数学的通用解题模式

---

#### 3. 核心难点辨析与解题策略
1. **关键点：条件转化**
   * **分析**：中位数为1等价于子序列中1的个数≥(k+1)/2。优质题解通过数学建模将问题转化为组合计数，避免暴力枚举子序列。
   * 💡 **学习笔记**：复杂条件→简洁数学模型是解题突破口

2. **关键点：组合数计算优化**
   * **分析**：需高效计算C(n,m)=n!/(m!(n-m)!)。题解普遍采用：
     - 预处理阶乘数组fact[0..N]
     - 费马小定理求逆元（模质数）
     - 逆元数组inv[]递推优化
   * 💡 **学习笔记**：预处理是组合计数的核心优化手段

3. **关键点：枚举边界控制**
   * **分析**：枚举变量i时需满足：
     - 下界：i ≥ (k+1)/2
     - 上界：i ≤ min(k, c)（c为1的总数）
     同时保证k-i≤n-c（0的数量充足）
   * 💡 **学习笔记**：仔细处理边界是避免WA的关键

### ✨ 解题技巧总结
- **模型转化**：将中位数条件转化为1的个数统计
- **组合优化**：预处理阶乘+逆元实现O(1)组合查询
- **边界防御**：显式检查组合数参数有效性（n≥m≥0）
- **模块封装**：将组合数计算独立为C(n,m)函数

---

#### 4. C++核心代码实现赏析
```cpp
#include <iostream>
using namespace std;
const int N = 200005, mod = 1e9+7;
typedef long long ll;

ll fact[N], inv[N];

// 快速幂求逆元
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 初始化阶乘和逆元数组
void init() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) 
        fact[i] = fact[i-1] * i % mod;
    inv[N-1] = qpow(fact[N-1], mod-2);
    for (int i = N-2; i >= 0; i--)
        inv[i] = inv[i+1] * (i+1) % mod;
}

// 组合数计算
ll C(ll n, ll m) {
    if (m < 0 || n < m) return 0;
    return fact[n] * inv[m] % mod * inv[n-m] % mod;
}

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        int n, k, cnt = 0;
        cin >> n >> k;
        for (int i = 0, x; i < n; i++) {
            cin >> x;
            cnt += x; // 统计1的个数
        }
        ll ans = 0;
        int m = (k+1)/2;
        for (int i = m; i <= k; i++) {
            if (i > cnt || k-i > n-cnt) continue;
            ans = (ans + C(cnt, i) * C(n-cnt, k-i)) % mod;
        }
        cout << ans << endl;
    }
    return 0;
}
```
**代码解读概要**：
1. 预处理阶乘数组`fact[]`和逆元数组`inv[]`
2. `C(n,m)`函数安全计算组合数（含非法校验）
3. 主逻辑：统计1的个数→枚举i累加组合乘积
4. 边界处理：跳过无效组合（i>cnt或k-i>n-cnt）

---

**题解一 (aeiouaoeiu)**
* **亮点**：简洁高效的组合数预处理
* **核心代码片段**：
  ```cpp
  ll C(ll a,ll b){return (a<b||b<0)?0:frac[a]*inv[b]%p*inv[a-b]%p;}
  for(int i=m;i<=k;i++) 
      ans=(ans+C(cnt,i)*C(n-cnt,k-i)%p)%p;
  ```
* **代码解读**：
  > - `C(a,b)`函数：三目运算符处理非法参数
  > - 主循环：i从m到k枚举，累加组合乘积
  > - 取模优化：每一步加法后立即取模

**题解二 (Pink_Cut_Tree)**
* **亮点**：快速幂独立封装，阶乘预处理完整
* **核心代码片段**：
  ```cpp
  int ksm(int a,int b){
      int ans=1;
      while(b){
          if(b&1) ans=ans*a%mod;
          a=a*a%mod; b>>=1;
      }
      return ans%mod;
  }
  ```
* **代码解读**：
  > - `ksm()`函数：标准快速幂实现
  > - 位运算优化：`b>>=1`代替除法
  > - 防溢出：每一步乘法后取模

**题解三 (cjh20090318)**
* **亮点**：逆元递推优化，变量名自解释
* **核心代码片段**：
  ```cpp
  inv[maxn-1]=qpow(fact[maxn-1],mod-2);
  for(int i=maxn-2;i>=0;i--)
      inv[i]=inv[i+1]*(i+1)%mod;
  ```
* **代码解读**：
  > - 逆元递推：`inv[i] = inv[i+1]*(i+1)%mod`
  > - 从后向前计算：避免重复计算
  > - 时间复杂度：O(n)完成所有逆元预处理

---

#### 5. 算法可视化：像素动画演示
**主题**：`"像素球选择大冒险"`（复古FC风格）

**核心演示**：
> 8-bit像素网格展示二进制数组（1=红色球，0=蓝色球），动态演示组合数计算过程：
> 1. **初始化**：显示数组和1/0计数面板（复古LED字体）
> 2. **枚举过程**：
>    - 高亮当前选择的红球数量i
>    - 粒子动画展示选球操作（红球：啾啾音效，蓝球：滴答音效）
> 3. **组合计算**：
>    - 左侧面板实时显示C(c,i)和C(n-c,k-i)计算过程
>    - 右侧网格动态绘制选球结果（每帧0.5秒）
> 4. **结果展示**：
>    - 成功时：烟花动画+胜利音效
>    - 边界检查失败：闪烁提示+警示音

**交互设计**：
```javascript
// 伪代码核心逻辑
function visualize() {
    drawGrid(a); // 绘制像素网格
    for (i = m; i <= k; i++) {
        highlight(`i = ${i}`);
        playSound('select'); 
        let c1 = calculateCombo(redBalls, i); // 红球组合
        let c0 = calculateCombo(blueBalls, k-i); // 蓝球组合
        showFormula(`C(${cnt},${i}) × C(${n-cnt},${k-i})`);
        ans += c1 * c0;
        updateCounter(ans); // 更新答案显示
    }
    celebrate(); // 胜利动画
}
```

**游戏化元素**：
> - **控制面板**：步进/暂停/重置（8-bit按钮）
> - **音效系统**：
>   - 选球：8-bit电子音
>   - 错误：短促"哔"声
>   - 胜利：经典FC过关音乐
> - **进度反馈**：每完成10%进度点亮一颗星星

---

#### 6. 拓展练习与相似问题思考
**通用技巧迁移**：
> 组合计数常用于：
> 1. 限定条件的方案统计（如本题）
> 2. 概率期望问题
> 3. 容斥原理应用

**洛谷练习推荐**：
1. **P2638 安全系统** 
   > 🗣️ 巩固组合数模型，处理多类型物品放置问题
2. **P2822 组合数问题** 
   > 🗣️ 学习组合数前缀和优化，处理大数据范围
3. **P3807 卢卡斯定理**
   > 🗣️ 进阶组合数取模技巧，掌握大质数处理方法

---

#### 7. 学习心得与经验分享
> **参考经验**（来自多篇题解）：
> - *"组合数计算要特别注意n<m的边界情况"*
> - *"逆元预处理能大幅优化性能"*
> - *"枚举前先计算合法范围避免无效循环"*
>
> **点评**：这些经验直击组合编程的核心痛点：
> 1. 边界检查是避免RE/WA的关键
> 2. 预处理是优化复杂度的有效手段
> 3. 数学建模前先分析数据范围

---

通过本指南，希望大家不仅掌握组合计数的实现技巧，更学会将复杂问题转化为数学模型的思想方法。记住：编程能力的提升源于对基础算法的深刻理解与灵活应用！💪

---
处理用时：130.77秒