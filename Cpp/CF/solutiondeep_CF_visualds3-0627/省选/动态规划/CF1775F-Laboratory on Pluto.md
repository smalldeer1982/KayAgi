# 题目信息

# Laboratory on Pluto

## 题目描述

As you know, Martian scientists are actively engaged in space research. One of the highest priorities is Pluto. In order to study this planet in more detail, it was decided to build a laboratory on Pluto.

It is known that the lab will be built of $ n $ square blocks of equal size. For convenience, we will assume that Pluto's surface is a plane divided by vertical and horizontal lines into unit squares. Each square is either occupied by a lab block or not, and only $ n $ squares are occupied.

Since each block is square, it has four walls. If a wall is adjacent to another block, it is considered inside, otherwise — outside.

Pluto is famous for its extremely cold temperatures, so the outside walls of the lab must be insulated. One unit of insulation per exterior wall would be required. Thus, the greater the total length of the outside walls of the lab (i. e., its perimeter), the more insulation will be needed.

Consider the lab layout in the figure below. It shows that the lab consists of $ n = 33 $ blocks, and all the blocks have a total of $ 24 $ outside walls, i. e. $ 24 $ units of insulation will be needed.

You should build the lab optimally, i. e., minimize the amount of insulation. On the other hand, there may be many optimal options, so scientists may be interested in the number of ways to build the lab using the minimum amount of insulation, modulo a prime number $ m $ .

Two ways are considered the same if they are the same when overlapping without turning. Thus, if a lab plan is rotated by $ 90^{\circ} $ , such a new plan can be considered a separate way.

To help scientists explore Pluto, you need to write a program that solves these difficult problems.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/19a2731aaaa55a0f9a8048f01dd79ff768ce23d2.png)

## 说明/提示

Consider the second example.

If $ n=1 $ , the only way to build a lab is to place a single block. In this case, the perimeter will be equal to four.

When $ n=2 $ , you must place two blocks side by side. This can be done either vertically or horizontally, so there are two ways. It is easy to see that the lab has six outside walls in this case.

For $ n=7 $ , all the $ 22 $ optimal plans are shown in the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/2d61b154960a5ef9890728641d5e6f811e5f6274.png)

## 样例 #1

### 输入

```
3 1
1
2
7```

### 输出

```
1 1
#
1 2
##
2 4
.###
####```

## 样例 #2

### 输入

```
3 2
1000000007
1
2
7```

### 输出

```
4 1
6 2
12 22```

# AI分析结果



0. **题目翻译**

---

# 实验室在冥王星

## 题目描述

众所周知，火星科学家们积极从事太空研究。最高优先级的任务之一是研究冥王星。为了更详细地研究该行星，决定在冥王星表面建造一个实验室。

实验室将由 $n$ 个等大的正方形模块组成。为方便起见，我们认为冥王星表面是一个被垂直和水平线划分为单位正方形的平面。每个正方形要么被实验室模块占据，要么未被占据，且恰好有 $n$ 个被占据的方块。

每个模块有四面墙。若某面墙与另一模块相邻，则视为内部墙，否则为外部墙。

冥王星以极寒著称，因此实验室的外墙必须保温。每单位外部墙需要一单位保温材料。因此，实验室外壁总长度（即周长）越大，所需保温材料越多。

考虑下图实验室布局。该实验室由 $n=33$ 个模块组成，所有模块共有 $24$ 个外部墙，即需要 $24$ 单位保温材料。

你需要以最优方式建造实验室，即最小化保温材料用量。由于可能存在多种最优方案，科学家们想知道使用最小保温材料建造实验室的方案数（对质数 $m$ 取模）。

两种方案视为相同当且仅当不旋转即可完全重合。若方案经 $90^{\circ}$ 旋转后相同，则视为不同方案。

你需要编写程序帮助科学家解决这些问题。

## 样例 #1

### 输入
```
3 1
1
2
7
```

### 输出
```
1 1
#
1 2
##
2 4
.###
####
```

## 样例 #2

### 输入
```
3 2
1000000007
1
2
7
```

### 输出
```
4 1
6 2
12 22
```

---

1. **唯一算法分类**  
   **线性DP**

2. **综合分析与结论**

### 核心思路
- **最小周长构造**：最优形状为近似矩形，通过枚举接近 $\sqrt{n}$ 的长宽组合确定最小周长
- **方案数计算**：将多余部分建模为四角挖洞问题，每个角的方案转化为整数分拆问题，通过四次DP卷积合并结果

### 动态规划核心
- **分拆数DP**：`dp[i][j]` 表示总和为i的j个数分拆方案数，转移方程：
  ```math
  dp[i][j] = dp[i-1][j-1] + dp[i-j][j]
  ```
  对应新增元素或整体+1两种操作
- **四维合并**：预处理单个角的分拆方案数后，通过三次卷积操作合并四个角的贡献

### 可视化设计
- **像素动画**：在Canvas中以网格展示DP矩阵更新，分拆数生成时用不同颜色标记新增元素与整体扩容
- **音效系统**：
  - 状态转移时播放8-bit "滴"声
  - 完成分拆时播放上升音阶
  - 错误操作时播放经典FC错误音效
- **自动演示模式**：按最佳路径自动执行DP更新，右下角显示当前处理的分拆数值

3. **题解清单 (4星及以上)**

| 作者         | 亮点                                                                 | 评分 |
|--------------|--------------------------------------------------------------------|------|
| Mine_King    | 清晰的分步DP推导，完整预处理方案，配图直观                          | ⭐⭐⭐⭐ |
| Hovery       | 精准抓住四角卷积特征，关联经典分拆问题                              | ⭐⭐⭐⭐ |
| zac2010      | 代码结构清晰，卷积操作实现高效                                      | ⭐⭐⭐⭐ |

4. **代码实现**

```cpp
// 分拆数预处理核心代码
int dp[1005][1005], f[1005], g[1005], gg[1005];
void preprocess(int mod) {
    dp[0][0] = 1;
    for (int i = 1; i <= 1000; i++)
        for (int j = i; j <= 1000; j++) {
            if (i == j) dp[i][j] = 1;
            else dp[i][j] = (dp[i-1][j-1] + dp[i][j-i]) % mod;
        }
    
    for (int i = 0; i <= 1000; i++)
        for (int j = 1; j <= i; j++)
            f[i] = (f[i] + dp[j][i]) % mod;
    
    // 三次卷积合并四个角
    for (int i = 0; i <= 1000; i++)
        for (int j = 0; j <= 1000; j++)
            if (i + j <= 1000)
                g[i+j] = (g[i+j] + 1LL * f[i] * f[j]) % mod;
    // ...类似操作合并四次
}
```

5. **同类型题目推荐**
1. P1025 数的划分 - 分拆数DP基础
2. CF1516E - 多重分拆数应用
3. P4389 付公主的背包 - 生成函数与分拆数

6. **可视化代码片段**
```javascript
// Canvas绘制DP矩阵
function drawDPGrid() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for(let i=0; i<=currentMax; i++) {
        for(let j=0; j<=i; j++) {
            ctx.fillStyle = getColor(dp[i][j]); 
            ctx.fillRect(j*30, i*30, 28, 28);
            ctx.fillText(dp[i][j], j*30+5, i*30+20);
        }
    }
}
// 音效触发
function playSound(type) {
    if(type == 'update') beep(440, 50);
    if(type == 'success') beep(880, 200);
}
```

7. **总结**
- **思维突破点**：将三维空间问题降维为二维分拆数问题，通过独立处理四角简化复杂度
- **调试教训**：注意预处理时模数运算的溢出问题，卷积顺序影响最终结果
- **扩展思考**：该模型可推广至三维空间中的最优形状设计问题，需引入立体分拆数概念

---
处理用时：72.40秒