# 题目信息

# Make it Divisible by 25

## 题目描述

给定一个**正整数** $n$，你可以对它进行操作。

对于每一次操作，你可以将这个正整数其中的**任意**一个数位删去，之后这个数剩下的左右两边会相接。

特别地：

- 如果一个数仅剩下一个数位，则不能再对它进行操作；
- 如果一个操作之后的数包含前导零，则这些前导零会被一并删除。

例如：

- 将 $32925$ 的第 $3$ 位删除后，它会变成 $3225$；
- 将 $20099050$ 的第 $1$ 位删除后，它会变成 $99050$（两个前导零被一并删除了）。

请你求出，最少经过多少次操作之后，可以得到一个能被 $25$ 整除的**正整数**。

## 说明/提示

- $1 \le t \le 10^4$；
- $25 \le n \le 10^{18}$。

Translated by @BurningEnderDragon, 2021.10.14

## 样例 #1

### 输入

```
5
100
71345
3259
50555
2050047```

### 输出

```
0
3
1
3
2```

# AI分析结果



# 算法分类：数论

## 题解思路与解决难点
### 核心数学逻辑
所有题解均基于**25的倍数特性**：末两位只能是00、25、50、75。通过反向匹配这四种情况，计算最少删除次数。

### 关键公式推导
设数字长度为n，寻找模式`XY`（XY∈{00,25,50,75}）：
1. 从右向左定位`Y`字符
2. 继续向左定位`X`字符
3. 所需删除次数 = (总长度 - 末位Y的位置 - 1) + (末位Y的位置 - 十位X的位置 - 1)

### 难点对比
| 题解方案 | 实现方式 | 前导零处理 | 时间复杂度 |
|---------|---------|------------|-----------|
| 模式枚举法 | 预存四种模式反向匹配 | 自动忽略前导零 | O(4n) |
| 分情况讨论法 | 分末尾0/5两种情况处理 | 显式检查前导零 | O(2n) |
| 暴力枚举法 | 单独处理每种模式 | 每次匹配独立处理 | O(4n) |

## 题解评分（≥4星）
1. **Coros_Trusds（5星）**  
   - 思路清晰，系统化处理四种情况
   - 代码结构简明，使用字符串逆序匹配
   - 时间复杂度最优，易扩展

2. **ttq012（4星）**  
   - 分两类情况减少重复计算
   - 代码注释详尽，逻辑分层明确
   - 处理前导零的方式稍显隐晦

3. **sycqwq（4星）**  
   - 显式枚举四种情况
   - 代码结构直观，变量命名清晰
   - 存在部分代码冗余

## 最优思路提炼
**反向贪心匹配法**：
1. 预定义四种合法结尾模式
2. 对每个模式从右向左进行两次字符匹配
3. 计算匹配成功时的最小删除次数
4. 取所有可行方案的最小值

**数学优化点**：  
通过反向匹配避免无效的前缀操作，确保每次计算的最优子结构性质。

## 同类型题套路
**数位操作类问题通用解法**：
1. 根据数论特性确定必要条件（如末尾数字组合）
2. 反向/正向扫描定位关键数位
3. 计算中间数位的删除/保留策略

## 推荐练习题
1. [CF 1515B](https://www.luogu.com.cn/problem/CF1515B)（方块切割的数学特性）
2. [P1217](https://www.luogu.com.cn/problem/P1217)（回文质数的数位处理）
3. [CF 1594B](https://www.luogu.com.cn/problem/CF1594B)（特殊进制表示问题）

## 关键代码实现
```cpp
// Coros_Trusds 核心代码
inline void solve(string str) {
    int ans = str.size();
    for (int i = 0; i <= 3; i++) {  // 枚举四种模式
        int idx = 1;  // 模式字符指针（从后往前）
        for (int j = str.size()-1; j >= 0; j--) {
            if (tmp[i][idx] == str[j]) idx--;
            if (idx == -1) {  // 完整匹配模式
                ans = min(ans, (int)str.size()-j-2);
                break;
            }
        }
    }
    cout << ans << '\n';
}
```

## 可视化设计
**像素化算法演示**：
```html
<canvas id="demo" width="640" height="200"></canvas>
<script>
const patterns = ["00", "25", "50", "75"];
let step = 0, currentPattern = 0;

function drawStep(ctx, str, pos) {
    ctx.clearRect(0, 0, 640, 200);
    // 绘制数字序列
    str.split('').forEach((c, i) => {
        ctx.fillStyle = i === pos ? "#FF0000" : "#FFFFFF";
        ctx.fillRect(50 + i*30, 80, 25, 25);
        ctx.fillStyle = "#000000";
        ctx.fillText(c, 58 + i*30, 98);
    });
    // 绘制当前匹配模式
    ctx.fillText("Target: " + patterns[currentPattern], 50, 150);
}

function simulate(str) {
    const ctx = document.getElementById('demo').getContext('2d');
    let patternIndex = 0, matchPos = 1;
    for(let p = 0; p < 4; p++) {
        currentPattern = p;
        let idx = 1;
        for(let j = str.length-1; j >=0; j--) {
            setTimeout(() => {
                drawStep(ctx, str, j);
                if(str[j] === patterns[p][idx]) idx--;
                if(idx === -1) {
                    ctx.fillText(`Found! Delete ${str.length-j-2}`, 50, 180);
                }
            }, step++ * 1000);
        }
    }
}
simulate("2050047"); // 样例输入
</script>
```

**交互特性**：
- 红色方块高亮当前检测数位
- 每步间隔1秒自动播放
- 成功匹配时显示删除次数
- 8-bit风格像素块显示数字序列

## 个人心得摘录
"处理数位问题时，反向匹配往往比正向更高效——因为目标特征通常出现在尾部。在调试时，要特别注意前导零和单数字边界情况。" —— Coros_Trusds

"将四种情况独立处理虽然代码略长，但能避免复杂的条件嵌套，实际运行效率反而更高。" —— sycqwq

---
处理用时：68.32秒