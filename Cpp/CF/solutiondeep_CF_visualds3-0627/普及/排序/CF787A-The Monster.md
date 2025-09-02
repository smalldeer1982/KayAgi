# 题目信息

# The Monster

## 题目描述

A monster is chasing after Rick and Morty on another planet. They're so frightened that sometimes they scream. More accurately, Rick screams at times $ b,b+a,b+2a,b+3a,... $ and Morty screams at times $ d,d+c,d+2c,d+3c,... $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787A/23c11249630f1c4252ef0b9cda8ec1bf9b317b5a.png)The Monster will catch them if at any point they scream at the same time, so it wants to know when it will catch them (the first time they scream at the same time) or that they will never scream at the same time.

## 说明/提示

In the first sample testcase, Rick's $ 5 $ th scream and Morty's $ 8 $ th time are at time $ 82 $ .

In the second sample testcase, all Rick's screams will be at odd times and Morty's will be at even times, so they will never scream at the same time.

## 样例 #1

### 输入

```
20 2
9 19
```

### 输出

```
82
```

## 样例 #2

### 输入

```
2 1
16 12
```

### 输出

```
-1
```

# AI分析结果



# 算法分类  
**数论（扩展欧几里得算法/贝祖定理）**

---

# 题解核心分析与结论  
## 核心难点  
1. **解的存在性判断**：两个等差数列的交集是否存在，需满足 $(d-b) \bmod \gcd(a,c) = 0$  
2. **最小解高效求解**：避免暴力枚举导致超时，需用数论方法推导  

## 解决方案对比  
| 方法类型 | 实现思路 | 时间复杂度 | 适用场景 |  
|---------|----------|-----------|---------|  
| 暴力枚举 | 双重循环枚举 i/j 的值 | $O(n^2)$ | 小数据范围（题目参数 ≤100） |  
| 数论模拟 | 贝祖定理判断解存在后，交替增加时间点 | $O(k)$ | 任意数据范围 |  
| 扩展欧几里得 | 解线性同余方程求最小解 | $O(\log n)$ | 需要数学推导能力 |  

---

# 题解评分（≥4星）  
1. **Alex_Wei（5星）**  
   ✅ 思路清晰：贝祖定理判定解存在性  
   ✅ 代码简洁：交替增加时间点直到相等  
   ✅ 时间复杂度低：线性时间完成  

2. **sodak（4星）**  
   ✅ 实现简洁：与 Alex_Wei 思路相同  
   ❌ 未完整解释数学推导  

3. **肖恩Sean（4星）**  
   ✅ 扩展欧几里得算法实现  
   ❌ 代码复杂度较高，需合并同余方程  

---

# 最优思路与代码实现  
## 核心算法流程  
1. **数学推导**：通过贝祖定理判断解存在性  
   $$\text{解存在的条件：} \quad (d-b) \bmod \gcd(a,c) = 0$$  
2. **交替递增**：维护两个时间点，每次增加较小的一方直到相等  

```cpp  
int a, b, c, d;  
cin >> a >> b >> c >> d;  
int gcd_val = gcd(a, c);  
if ((d - b) % gcd_val != 0) {  
    cout << -1;  
    exit(0);  
}  
while (b != d) {  
    b < d ? b += a : d += c;  
}  
cout << b;  
```  

---

# 同类型题与算法套路  
**线性同余方程**：形如 $ax + by = c$ 的方程解的存在性判断  
**双指针交替递增**：用于寻找两个递增序列的交集  

---

# 推荐练习题  
1. **P1516** 青蛙的约会（扩展欧几里得算法）  
2. **P5656** 二元一次不定方程（exgcd模板题）  
3. **P1082** 同余方程（线性同余方程求解）  

---

# 可视化与算法演示  
## 动画设计  
1. **像素风格时间轴**：  
   - 用两种颜色标记 Rick（红色）和 Morty（蓝色）的当前时间点  
   - 每次递增时播放 "beep" 音效  
   - 相遇时触发 "胜利" 音效并高亮显示时间值  

2. **关键步骤高亮**：  
   - 显示当前 gcd 计算过程和 $(d-b) \bmod \gcd(a,c)$ 的判定  
   - 每次递增时动态更新公式：  
     $$\text{Rick: } b + a \times i \quad \text{Morty: } d + c \times j$$  

3. **交互控制**：  
   - 步进执行：观察每次递增逻辑  
   - 速度调节：快速查看整体流程或逐步分析  

---

# 复古游戏化实现（Web Demo 伪代码）  
```javascript  
// 初始化 Canvas  
const ctx = initCanvas();  
let rickTime = b, mortyTime = d;  

function draw() {  
    // 绘制时间轴与当前时间点  
    drawPixel(rickTime, RED);  
    drawPixel(mortyTime, BLUE);  
    // 播放移动音效  
    if (rickTime !== mortyTime) playSound('move');  
}  

function step() {  
    if (rickTime < mortyTime) rickTime += a;  
    else mortyTime += c;  
    draw();  
    if (rickTime === mortyTime) playSound('win');  
}  
```  

**8位音效设计**：  
- `move.wav`：短促电子音（每次递增时播放）  
- `win.wav`：8-bit 胜利旋律  
- `bgm.mp3`：循环芯片音乐  

--- 

通过数学推导与高效模拟，本解法在趣味性与严谨性间取得平衡，是算法与游戏化结合的经典案例。

---
处理用时：66.45秒