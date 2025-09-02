# 题目信息

# 「HGOI-1」Number

## 题目背景

$\text{bh1234666}$ 正在学习乘法！

## 题目描述

$\text{bh1234666}$ 有一定数量的数字 $0 \sim 9$，现在他想让你寻找一种分配方案，将它们分成两个整数，使得他们的乘积 $p$ 最大。
 
由于 $\text{bh1234666}$ 不喜欢太大的数，所以你只需要输出**两个非负整数**，使它们的乘积**等于**最大乘积 $p$，但是这两个整数 $0 \sim 9$ 的数量不能等于给定的数量（任意一个数字数量不相等即可，**不考虑前导零**）。

$\text{bh1234666}$ 是很善良的，如果 $0 \sim 9$ 的数量等于给定的数量了，你依旧可以得到的一半的分。

## 说明/提示

#### 样例解释
最大可能乘积为 $97643210 \times 88653221=13949030 \times 620572547=8656385075279410$。

若输出 $97643210 \times 88653221$ 则只能得到一半的分，因为 $0\sim 9$ 出现的次数与给定的相同。

#### 数据范围及约定
本题采用**捆绑测试**，共有 $5$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & \sum c_i\le \cr\hline
1 & 10 & 20 \cr\hline
2 & 20 & 100 \cr\hline
3 & 20 & 5000 \cr\hline
4 & 20 & 10^6 \cr\hline
5 & 30 & 10^7 \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，保证 $1 \le c_i$，$\sum c_i \le 10^7$。

#### 说明

本题有 $\text{spj}$，两数乘积正确得一半的分，数量与给出的不同且乘积正确得全部分数。故每一 $\text{subtask}$ 的得分为其中所有数据点得分的**最小值**。


## 样例 #1

### 输入

```
1 2 3 2 1 1 2 1 2 1```

### 输出

```
13949030
620572547```

# AI分析结果



### 综合分析与结论

#### 核心算法要点
1. **贪心策略**：从高位到低位分配最大可用数字，保持两数长度差≤1，优先保证两数差值最小化。
2. **数学基础**：和一定时，差越小积越大（$\frac{X^2-Y^2}{4}$ 最大化的推导）。
3. **调整技巧**：利用必然存在末尾0的特性，通过乘2/除2操作改变数字数量分布。

#### 解决难点对比
| 题解方案 | 贪心分配策略 | 调整方法 | 高精度处理 |
|----------|--------------|----------|------------|
| bh1234666 | 交替分配+动态平衡差值 | 末尾0处理（乘2/除2） | 字符数组直接操作 |
| linyuhao | 交替分配+优先补小数 | 末尾0拆解（乘2/乘5） | 高精乘低精模板 |
| VIOLET   | 先补齐位数后平均分配 | 末尾0拆分乘2/5 | 字符串操作 |
| Full_Speed | 长度平衡+奇偶处理 | 末尾0直接调整 | 字符串模拟高精 |

#### 可视化设计要点
1. **贪心分配动画**：
   - 用**双色像素块**表示两个数的构建过程
   - 高亮当前分配的数字（红色块表示当前最大可用数字）
   - 动态显示两数差值曲线图（右上角小面板）
   
2. **调整操作演示**：
   ```javascript
   // 伪代码示例：末尾0处理动画
   function animateAdjust(){
     highlightEndZero(); // 高亮末尾0
     playSound('select'); 
     splitZeroTo2x5();   // 展示0拆分为2*5
     multiplyNumber(2);  // 左侧数字像素块膨胀动画
     divideNumber(2);     // 右侧数字像素块压缩动画
   }
   ```

3. **复古风格交互**：
   - **8位音效**：分配数字时播放NES风格"哔"声，调整操作时播放马里奥金币音
   - **积分系统**：正确分配一个数字+10分，最优选择额外+5分
   - **自动演示模式**：AI自动执行贪心策略，按空格可暂停干预

---

### 题解评分（≥4★）

#### 1. bh1234666 题解（★★★★☆）
- **亮点**：严格数学推导贪心正确性，末尾调整方法巧妙
- **代码**：直接操作字符数组，内存效率高
- **不足**：变量命名简短（s1/s2）影响可读性

#### 2. linyuhao 题解（★★★★★）
- **亮点**：清晰分步说明，附带高精度乘模板
- **代码**：模块化函数设计（sh()处理高精乘）
- **技巧**：使用pd标志处理前导零

#### 3. Full_Speed 题解（★★★★☆）
- **亮点**：详细注释+分步调试思路
- **可视化友好**：字符串直接操作便于动画演示
- **局限**：高精乘实现未倒序存储

---

### 关键代码实现

#### 贪心分配核心逻辑
```cpp
// bh1234666 题解片段
bool flag = 0;
for (int i = 9; i >= 0; i--) {
    while (c[i]--) {
        if (!flag) s1[l1++] = i + '0';
        else s2[l2++] = i + '0';
        flag = !flag;
        // 动态平衡长度差
        if (flag && s1[l1-1] > s2[l2-1]) break;
    }
}
```

#### 调整操作实现
```cpp
// linyuhao 题解的高精乘模板
void sh(string x, int y) {
    memset(c, 0, sizeof(c));
    for (int i = 0; i < x.length(); i++) 
        a[i] = x[x.length()-i-1] - '0';
    
    for (int i = 0; i < x.length(); i++) 
        c[i] = a[i] * y;
    
    // 处理进位
    for (int i = 0; i <= x.length(); i++) {
        c[i+1] += c[i] / 10;
        c[i] %= 10;
    }
}
```

---

### 同类型题目推荐

1. **P1090 [NOIP2004 提高组] 合并果子**  
   - 贪心选择最小代价合并，优先队列应用

2. **P1223 排队接水**  
   - 时间规划类贪心，通过排序优化平均等待时间

3. **P5653 基础最优化练习题**  
   - 带限制条件的极值问题，考验贪心策略的灵活性

---

### 可视化代码片段（Canvas+音效）

```javascript
// 贪心分配动画核心逻辑
class GreedyAnimator {
  constructor(canvas) {
    this.numbers = [9,8,7,6,5,4,3,2,1,0];
    this.bins = [new NumberBuilder(), new NumberBuilder()];
    this.ctx = canvas.getContext('2d');
    this.playSound('bgm', true); // 循环背景音乐
  }

  async allocateNext() {
    const num = this.getMaxAvailable();
    const target = this.selectTargetBin();
    
    // 高亮动画
    this.highlightNumber(num); 
    await this.moveToBin(num, target);
    
    // 更新状态
    target.add(num);
    this.updateDifferenceChart();
  }

  selectTargetBin() {
    // 实现bh1234666的平衡策略
    if (Math.abs(this.bins[0].length - this.bins[1].length) > 1)
      return /* 补齐短的那个 */;
    return this.bins[0].value < this.bins[1].value ? 0 : 1;
  }
}
```

---
处理用时：65.58秒