# 题目信息

# Balanced Substring

## 题目描述

You are given a string $ s $ consisting only of characters 0 and 1. A substring $ [l,r] $ of $ s $ is a string $ s_{l}s_{l+1}s_{l+2}...\ s_{r} $ , and its length equals to $ r-l+1 $ . A substring is called balanced if the number of zeroes (0) equals to the number of ones in this substring.

You have to determine the length of the longest balanced substring of $ s $ .

## 说明/提示

In the first example you can choose the substring $ [3,6] $ . It is balanced, and its length is $ 4 $ . Choosing the substring $ [2,5] $ is also possible.

In the second example it's impossible to find a non-empty balanced substring.

## 样例 #1

### 输入

```
8
11010111
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
111
```

### 输出

```
0
```

# AI分析结果


### 💡 Kay的C++算法解析：Balanced Substring 深入学习指南 💡

#### 题目解读与核心算法识别
✨ **本题主要考察**：`前缀和与桶技巧`  
🗣️ **初步分析**：  
> 将"0"视为-1、"1"视为+1后，问题转化为寻找和为零的最长子串。就像在游戏中收集等量金币和钻石的关卡，我们需要快速定位价值平衡点。  
> - **核心技巧**：用桶数组记录前缀和首次出现位置（偏移n处理负数），当相同前缀和再现时更新最大长度  
> - **可视化设计**：复古像素进度条显示前缀和变化，当相同值再现时触发"平衡闪光"动画（金色闪光+8-bit音效）  
> - **游戏化元素**：每找到平衡子串增加金币计数，通关后根据最大长度解锁像素奖杯  

---

#### 精选优质题解参考
**题解一 (来源：zhengrunzhe)**  
* **点评**：思路直击本质，将0/1映射为±1的转换极为巧妙。桶数组替代map实现O(1)查询，用sum[i-1]更新桶的设计避免自我覆盖，边界处理严谨（+n偏移）。代码变量命名简洁但含义明确，空间复杂度O(n)堪称典范解法。

**题解二 (来源：曼恩薄荷)**  
* **点评**：采用map实现更通用的负数处理，虽然增加O(log n)开销但提升了代码可读性。特别亮点是单独处理sum[i]=0的情况，避免漏解。输入用`%1d`直接读数字简化处理，适合初学者理解核心思路。

**题解三 (来源：AC_Automation)**  
* **点评**：桶偏移处理与题解一异曲同工，亮点在于显式处理sum=0的初始状态。代码逻辑闭环性强（book数组初始化为0），用`sum+100000`确保下标非负，防御性编程思维值得学习。

---

#### 核心难点辨析与解题策略
1. **难点：负数下标处理**  
   * **分析**：前缀和范围[-n,n]，需偏移n转非负。桶数组大小应为2n+1（如题解三的200005）
   * 💡 学习笔记：偏移量=最大负值绝对值，通用公式：index = sum + n

2. **难点：初始状态定义**  
   * **分析**：空子串(sum[0]=0)必须初始化（题解五疏漏此点）。桶对sum[0]应设位置0
   * 💡 学习笔记：前缀和问题永远从index=0开始思考

3. **难点：桶更新时机**  
   * **分析**：先检查再更新避免覆盖当前值（如题解一先判断first[sum[i]+n]存在性再更新）
   * 💡 学习笔记：桶记录历史值，当前值仅用于查询

✨ **解题技巧总结**  
- **问题转化**：将计数平衡转为数学求和为零（±1映射）  
- **空间换时间**：桶数组替代双重循环实现O(n)优化  
- **防御编程**：显式处理边界(sum=0)和初始化  
- **偏移技巧**：负数下标转正数保证索引有效性  

---

#### C++核心代码实现赏析
**通用核心实现参考**  
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 10; // 两倍空间防越界
int n, sum[N], first[N], ans; // first需初始化为-1

int main() {
    scanf("%d", &n);
    fill(first, first+N, -1); // 初始化为-1
    first[n] = 0; // sum[0]=0的位置是0
    
    char s[N];
    scanf("%s", s+1);
    for(int i=1; i<=n; ++i) {
        sum[i] = sum[i-1] + (s[i]=='1' ? 1 : -1);
        int idx = sum[i] + n; // 偏移处理
        
        if(first[idx] != -1) 
            ans = max(ans, i - first[idx]);
        else 
            first[idx] = i; // 记录首次出现
    }
    printf("%d", ans);
}
```

**题解一核心片段**  
```cpp
if (first[sum[i]+n]) // 检查历史值存在性
    ans=max(ans,i-first[sum[i]+n]+1);
if (!first[sum[i-1]+n]) // 更新桶用前一个值
    first[sum[i-1]+n]=i;
```
* **解读**：`first`数组记录各前缀和首次位置。查询当前值`sum[i]`时，若桶中存在相同值，则区间`[首次位置+1, i]`必平衡。更新桶用`sum[i-1]`确保下次查询可用
* 💡 学习笔记：桶更新滞后一单位避免自锁

**题解三核心片段**  
```cpp
if(sum==0) ans=max(ans,i); // 显式处理零和
if(!book[sum+100000]) book[sum+100000]=i;
else ans=max(ans,i-book[sum+100000]);
```
* **解读**：`book`数组功能同`first`，但单独处理sum=0情况。偏移量100000覆盖极端情况
* 💡 学习笔记：零和子串必然从首字符开始

---

#### 算法可视化：像素动画演示
🎮 **主题**：8-bit风格"平衡猎人"闯关  
🖌️ **设计思路**：  
- **像素网格**：每个字符转为像素块（0=蓝色，1=红色）  
- **动态进度条**：底部进度条显示当前前缀和（左红右蓝）  
- **关键帧触发**：  
  - 黄光闪烁：相同前缀和再现时触发平衡动画  
  - 音效设计：平衡时播放FC游戏金币音效，破纪录时播放通关音乐  
- **控制面板**：  
  - 速度滑块：调节单步/自动演示速度  
  - 复位键：像素块爆炸重组成初始状态  
- **数据跟踪**：  
  ```js
  // 伪代码核心逻辑
  function drawFrame() {
      drawPixelBlocks(); // 绘制当前字符串
      drawProgressBar(currentSum); // 绘制前缀和进度条
      if(bucket.has(sum)) { 
          flashGoldenEffect(); // 触发金色闪光
          updateMaxLength();  // 更新最长平衡记录
      }
      updateBucket(prevSum); // 更新桶（用前一状态）
  }
  ```

---

#### 拓展练习与相似问题思考
🔗 **技巧迁移**：  
1. 寻找和特定k的子数组（LeetCode 560）  
2. 包含等量字母的最长子串（LeetCode 1371）  
3. 连续数组最大乘积（正负计数变形）  

📚 **洛谷推荐**：  
1. **P1115** 最大子段和（基础前缀和应用）  
2. **P3131** Subsequences Summing to Sevens（同余桶技巧）  
3. **P3406** 海底高铁（差分数组进阶）  

---

#### 学习心得与经验分享
> **经验摘录 (zhengrunzhe)**："桶开成数组，+n就好了"  
> **Kay点评**：此经验揭示算法竞赛核心思维——将问题转化为可索引的数学模型。偏移量处理是负数下标的通用解决方案，适用于任何有界范围问题。

---

通过本次分析，我们掌握了前缀和桶技巧的核心：**问题转化**、**桶索引设计**和**边界处理**。记住：好算法如同精妙游戏关卡设计，每个元素都该在正确位置发挥价值！🎮🚀

---
处理用时：88.32秒