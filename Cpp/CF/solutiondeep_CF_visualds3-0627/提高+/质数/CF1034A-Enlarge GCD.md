# 题目信息

# Enlarge GCD

## 题目描述

Mr. F has $ n $ positive integers, $ a_1, a_2, \ldots, a_n $ .

He thinks the greatest common divisor of these integers is too small. So he wants to enlarge it by removing some of the integers.

But this problem is too simple for him, so he does not want to do it by himself. If you help him, he will give you some scores in reward.

Your task is to calculate the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

## 说明/提示

In the first example, the greatest common divisor is $ 1 $ in the beginning. You can remove $ 1 $ so that the greatest common divisor is enlarged to $ 2 $ . The answer is $ 1 $ .

In the second example, the greatest common divisor is $ 3 $ in the beginning. You can remove $ 6 $ and $ 9 $ so that the greatest common divisor is enlarged to $ 15 $ . There is no solution which removes only one integer. So the answer is $ 2 $ .

In the third example, there is no solution to enlarge the greatest common divisor. So the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
1 2 4
```

### 输出

```
1```

## 样例 #2

### 输入

```
4
6 9 15 30
```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
-1```

# AI分析结果



---

## **唯一算法分类**  
数论（筛法与GCD优化）

---

## **综合分析与结论**  
**核心思路**：  
1. **预处理原数组的GCD**：将所有数除以原GCD，转化为求新数组的GCD大于1的问题。  
2. **枚举质数统计倍数**：利用筛法高效统计质数的倍数出现次数，次数最多的质数对应删除最少元素。  
3. **时间复杂度优化**：通过埃氏筛或线性筛预处理质数，将复杂度优化至线性或近似线性。  

**算法难点**：  
- 处理大范围质数统计（如1.5e7）时，需避免暴力分解质因数的高时间复杂度。  
- 正确统计质数倍数次数，注意重复质因子仅统计一次（如分解时去重）。  

**可视化设计**：  
- **动画方案**：  
  - 用Canvas绘制数值网格，高亮当前质数及其倍数。  
  - 步进显示筛法过程，颜色标记质数（红色）、已筛数（灰色）、当前统计的倍数（绿色）。  
- **复古像素风格**：  
  - 质数用8位像素方块表示，背景音乐为8-bit循环音效。  
  - 找到最大次数质数时播放胜利音效，无解时播放失败音效。  
- **AI自动模式**：模拟筛法过程，自动选择下一个质数并统计倍数。  

---

## **题解清单 (≥4星)**  
1. **Siyuan的优化思路（5星）**  
   - **亮点**：代码简洁，利用筛法统计质数倍数，复杂度严格证明为O(m log log m)。  
   - **关键代码**：  
     ```cpp  
     for(int j=x;j<=mx;j+=x) num+=cnt[j];  
     ans = min(ans, n - num);  
     ```  
2. **Acc_Robin的题解（4星）**  
   - **亮点**：补充复杂度分析，代码中通过`std::__gcd`快速计算原GCD。  
   - **引用心得**：“枚举每一个素数，一个素数的倍数的个数就是我们需要留下的元素。”  
3. **kimi0705的题解（4星）**  
   - **亮点**：代码极简，直接嵌入筛法和统计逻辑，适合快速实现。  

---

## **最优思路提炼**  
**关键技巧**：  
1. **消除原GCD影响**：将问题转化为求新数组的GCD>1，避免原GCD的干扰。  
2. **质数倍数统计**：所有可能的更大GCD必为质数，只需统计各质数的倍数出现次数。  
3. **筛法优化统计**：利用埃氏筛的标记过程，在筛质数的同时统计倍数，避免重复计算。  

**代码片段（Siyuan优化思路）**：  
```cpp  
// 筛法预处理质数  
void sieve(int n) {  
    for(int i=2; i<=n; ++i) {  
        if(!flg[i]) p[++tot]=i;  
        for(int j=1; j<=tot && i*p[j]<=n; ++j) {  
            flg[i*p[j]] = true;  
            if(i%p[j] == 0) break;  
        }  
    }  
}  

// 统计质数倍数  
for(int i=1; i<=tot; ++i) {  
    int x = p[i], num = 0;  
    for(int j=x; j<=mx; j+=x) num += cnt[j];  
    ans = min(ans, n - num);  
}  
```  

---

## **同类型题与算法套路**  
1. **质数统计问题**：如统计区间内质数个数（洛谷P3912）。  
2. **GCD变形问题**：如求数组中所有子序列的GCD最大值（需结合筛法优化）。  
3. **质因数分解优化**：通过预处理最小质因子快速分解大数（如leetcode 650）。  

---

## **推荐题目**  
1. [洛谷P1072 Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)  
   - **考点**：GCD与LCM的质因数分解联合应用。  
2. [洛谷P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)  
   - **考点**：GCD与LCM的关系及质数对统计。  
3. [Codeforces 1047C Enlarge GCD](https://codeforces.com/problemset/problem/1047/C)  
   - **考点**：本题的扩展版本，需结合更高效的筛法优化。  

---

## **个人心得摘录**  
- **调试教训**（来自cppcppcpp3）：  
  > “分解质因数时需注意重复质因子仅统计一次，否则会错误计算倍数次数。”  
- **优化顿悟**（来自Acc_Robin）：  
  > “意识到最终的GCD必为质数，直接枚举质数而非合数，极大减少计算量。”  

---

## **可视化与算法演示**  
**核心逻辑动画**：  
1. **初始状态**：显示原数组数值，红色标记原GCD。  
2. **除以GCD**：所有数值缩小，出现多个1（若原GCD较大）。  
3. **筛法过程**：  
   - 高亮当前质数p，绿色标记其倍数。  
   - 右侧计数器显示p的倍数个数，动态更新最小删除数。  
4. **结果展示**：最终选中最大倍数质数，红色框标记答案。  

**复古像素实现**：  
```javascript  
// 伪代码示例：Canvas绘制筛法过程  
function drawPixel(x, y, color) {  
    ctx.fillStyle = color;  
    ctx.fillRect(x*10, y*10, 8, 8); // 8x8像素方块  
}  

// 筛法动画步骤  
let currentPrime = 2;  
function animateSieve() {  
    if(currentPrime > maxNumber) return;  
    // 标记当前质数为红色  
    drawPixel(currentPrime, 0, '#FF0000');  
    // 标记其倍数为绿色  
    for(let j=currentPrime; j<=maxNumber; j+=currentPrime) {  
        drawPixel(j, 1, '#00FF00');  
    }  
    currentPrime = getNextPrime();  
    requestAnimationFrame(animateSieve);  
}  
```  

**音效设计**：  
- **质数发现**：短促“哔”声（Web Audio合成方波）。  
- **统计完成**：播放8-bit鼓点音效。  
- **无解提示**：低沉“嗡”声持续0.5秒。  

--- 

通过上述分析，可系统掌握本题的筛法优化思路，并举一反三解决同类数论问题。

---
处理用时：86.27秒