# 题目信息

# Beauty of the mountains

## 题目描述

Nikita loves mountains and has finally decided to visit the Berlyand mountain range! The range was so beautiful that Nikita decided to capture it on a map. The map is a table of $ n $ rows and $ m $ columns, with each cell containing a non-negative integer representing the height of the mountain.

He also noticed that mountains come in two types:

- With snowy caps.
- Without snowy caps.

Nikita is a very pragmatic person. He wants the sum of the heights of the mountains with snowy caps to be equal to the sum of the heights of the mountains without them. He has arranged with the mayor of Berlyand, Polikarp Polikarpovich, to allow him to transform the landscape.

Nikita can perform transformations on submatrices of size $ k \times k $ as follows: he can add an integer constant $ c $ to the heights of the mountains within this area, but the type of the mountain remains unchanged. Nikita can choose the constant $ c $ independently for each transformation. Note that $ c $ can be negative.

Before making the transformations, Nikita asks you to find out if it is possible to achieve equality of the sums, or if it is impossible. It doesn't matter at what cost, even if the mountains turn into canyons and have negative heights.

If only one type of mountain is represented on the map, then the sum of the heights of the other type of mountain is considered to be zero.

## 说明/提示

The mountain array from the first test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/c2cad4d039daa4458ac8328be539df0f39115b35.png)Initially, the sum of the heights of the mountains with snowy caps is $ 11 + 3 + 4 + 3 + 0 + 1 + 15 = 37 $ , and without them is $ 7 + 2 = 9 $ .

To equalize these sums, we can perform two transformations:

First transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/26401332927c782774104130bd94cec3d8dea8ef.png)Note that the constant $ c $ can be negative.

After the first transformation, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/8985a2e394a22468e2807bb57386a8c62bc3f888.png)Second transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/83de4303ed287bb4d20cf33c8ab2494ed765c011.png)As a result, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/1dfddde2b777b3b24d753c3d41d8fe42319ee24e.png)The sum of the heights of the mountains with snowy caps is $ 17 + 9 + 9 - 16 - 20 - 19 + 15 = -5 $ , and without them is $ 7 - 12 = -5 $ , thus the answer is YES.

## 样例 #1

### 输入

```
8
3 3 2
7 11 3
4 2 3
0 1 15
100
010
000
4 4 3
123 413 24 233
123 42 0 216
22 1 1 53
427 763 22 6
0101
1111
1010
0101
3 3 2
2 1 1
1 1 2
1 5 4
010
101
010
3 3 2
2 1 1
1 1 2
1 5 3
010
101
010
3 4 3
46 49 50 1
19 30 23 12
30 25 1 46
1000
0100
0010
5 4 4
39 30 0 17
22 42 30 13
10 44 46 35
12 19 9 39
21 0 45 40
1000
1111
0011
0111
1100
2 2 2
3 4
6 7
00
00
2 2 2
0 0
2 0
01
00```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
YES```

# AI分析结果



## 算法分类  
**数学（裴蜀定理）+二维前缀和**

---

## 综合分析与结论  
### 核心思路  
1. **差值转化**：将有雪与无雪总高度的差值转化为线性方程问题。  
2. **操作影响模型**：每个k×k操作对应系数a_i，求解Σ(a_i * c_i) = -初始差。  
3. **裴蜀定理**：判断方程是否有整数解的条件为差值是所有系数最大公约数的倍数。  

### 解决难点  
- **快速统计子矩阵属性**：通过二维前缀和预处理，O(1)查询每个k×k子矩阵的无雪格子数。  
- **边界处理**：遍历所有合法子矩阵左上角，避免越界。  
- **系数计算**：将每个子矩阵的影响转化为系数a_i = k² - 2*s1，其中s1为无雪数。  

### 可视化设计  
- **动画效果**：Canvas绘制网格，高亮当前遍历的子矩阵，动态显示a_i计算过程。  
- **音效触发**：每计算完一个子矩阵的系数播放短促音效，求解成功时播放胜利音效。  
- **复古风格**：采用8位像素风，差值与gcd数值以像素字体展示，背景音乐循环播放。  

---

## 题解清单（≥4星）  
1. **SnapYust（5星）**  
   - 思路清晰，代码结构简洁，预处理前缀和与系数计算分离，可读性强。  
   - 核心亮点：显式处理所有子矩阵，正确计算gcd并处理全零特例。  

2. **xhhhh36（4星）**  
   - 简化变量命名，直接计算每个子矩阵的绝对值差，减少冗余步骤。  
   - 个人心得：在注释中强调gcd的初始值处理，避免逻辑错误。  

3. **Targanzqq（4星）**  
   - 使用三维数组存储前缀和，代码略显复杂但逻辑严谨。  
   - 调试注释保留，方便理解矩阵属性统计过程。  

---

## 核心代码实现  
```cpp
// 二维前缀和预处理
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        sum[i][j] = c[i][j-1]-'0' + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        if(c[i][j-1] == '1') sum1 += a[i][j];
        else sum2 += a[i][j];
    }
}

// 遍历所有子矩阵，计算系数
long long gcd_val = 0;
for(int i=1; i<=n-k+1; i++){
    for(int j=1; j<=m-k+1; j++){
        int s1 = sum[i+k-1][j+k-1] - sum[i-1][j+k-1] - sum[i+k-1][j-1] + sum[i-1][j-1];
        int ai = k*k - 2*s1; // 计算a_i
        gcd_val = gcd(gcd_val, abs(ai));
    }
}

// 判断解的存在性
if(gcd_val == 0 ? (delta == 0) : (delta % gcd_val == 0)){
    cout << "YES\n";
} else {
    cout << "NO\n";
}
```

---

## 同类型题推荐  
1. **P4549 裴蜀定理**：基础数论题，直接应用定理。  
2. **P2280 激光炸弹**：二维前缀和经典问题，统计子矩阵和。  
3. **CF510D Fox And Jumping**：数论+动态规划，利用gcd性质求解最优方案。  

---

## 个人心得摘录  
- **调试教训**：初始差未取绝对值导致符号错误，后通过输出中间变量排查。  
- **优化技巧**：二维前缀和下标从1开始，避免边界特判。  

---

## 可视化方案（复古像素风）  
1. **Canvas绘制**：  
   - 网格用16x16像素块表示，雪盖格子用蓝色，非雪用绿色。  
   - 当前遍历的子矩阵边框闪烁黄色，内部填充半透明红色。  

2. **音效设计**：  
   - 每次计算完一个子矩阵，播放“哔”声（Web Audio模拟8bit音效）。  
   - 成功/失败时播放经典FC游戏胜利/失败音乐片段。  

3. **自动演示模式**：  
   - 按行优先顺序遍历子矩阵，显示系数计算过程。  
   - 最终gcd与差值判断结果以弹窗形式像素动画展示。  

4. **交互控制**：  
   - 速度滑块调节遍历速度，暂停/继续按钮控制流程。  
   - 支持鼠标悬停查看子矩阵的s1和a_i数值。  

```javascript
// 示例：音效触发（伪代码）
function playBeep() {
    const osc = audioCtx.createOscillator();
    osc.frequency.setValueAtTime(800, audioCtx.currentTime);
    osc.connect(audioCtx.destination);
    osc.start();
    osc.stop(audioCtx.currentTime + 0.1);
}
```

---
处理用时：82.28秒