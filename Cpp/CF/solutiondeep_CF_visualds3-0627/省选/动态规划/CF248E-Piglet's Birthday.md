# 题目信息

# Piglet's Birthday

## 题目描述

Piglet has got a birthday today. His friend Winnie the Pooh wants to make the best present for him — a honey pot. Of course Winnie realizes that he won't manage to get the full pot to Piglet. In fact, he is likely to eat all the honey from the pot. And as soon as Winnie planned a snack on is way, the pot should initially have as much honey as possible.

The day before Winnie the Pooh replenished his honey stocks. Winnie-the-Pooh has $ n $ shelves at home, each shelf contains some, perhaps zero number of honey pots. During the day Winnie came to the honey shelves $ q $ times; on the $ i $ -th time he came to some shelf $ u_{i} $ , took from it some pots $ k_{i} $ , tasted the honey from each pot and put all those pots on some shelf $ v_{i} $ . As Winnie chose the pots, he followed his intuition. And that means that among all sets of $ k_{i} $ pots on shelf $ u_{i} $ , he equiprobably chooses one.

Now Winnie remembers all actions he performed with the honey pots. He wants to take to the party the pot he didn't try the day before. For that he must know the mathematical expectation of the number $ m $ of shelves that don't have a single untasted pot. To evaluate his chances better, Winnie-the-Pooh wants to know the value $ m $ after each action he performs.

Your task is to write a program that will find those values for him.

## 样例 #1

### 输入

```
3
2 2 3
5
1 2 1
2 1 2
1 2 2
3 1 1
3 2 2
```

### 输出

```
0.000000000000
0.333333333333
1.000000000000
1.000000000000
2.000000000000
```

# AI分析结果



0. **题目翻译**

---

# 小猪的生日

## 题目描述

今天是小猪的生日。他的朋友维尼熊想送他最好的礼物——蜜罐。但维尼知道，自己可能无法将整个蜜罐完整地送给小猪。事实上，他可能在路上就把所有蜂蜜吃光了。为了尽可能保持蜜罐的完整，维尼需要精确计算蜂蜜的分配情况。

维尼家中有 $n$ 个货架，每个货架初始存放若干（可能为零）蜜罐。一天中维尼进行了 $q$ 次操作：在第 $i$ 次操作中，他从货架 $u_i$ 取出 $k_i$ 个蜜罐，品尝所有罐子后转移到货架 $v_i$。维尼的选取遵循均匀随机原则——在所有可能的 $k_i$ 罐子组合中，每个组合被选中的概率相等。

现在维尼想知道，每次操作后数学期望值 $m$（即所有蜜罐都被品尝过的货架数量）是多少。请编写程序帮助他计算每次操作后的期望值。

## 样例 #1

### 输入
```
3
2 2 3
5
1 2 1
2 1 2
1 2 2
3 1 1
3 2 2
```

### 输出
```
0.000000000000
0.333333333333
1.000000000000
1.000000000000
2.000000000000
```

---

1. **唯一算法分类**  
线性DP

---

2. **综合分析与结论**

### 核心思路
- **状态设计**：$f[i][j]$ 表示货架 $i$ 剩余 $j$ 个未被品尝蜜罐的概率
- **组合数优化**：预处理 $C_{5 \times 10^5}^5$ 的组合数，解决大数计算精度问题
- **转移方程**：
  $$f[u][j] = \frac{\sum_{k=j}^{\min(j+w,now_u)} f[u][k] \cdot C_k^{k-j} \cdot C_{now_u-k}^{w-(k-j)}}{C_{now_u}^w}$$
  
### 可视化设计
1. **网格动画**：Canvas绘制货架状态矩阵，每个单元格表示$f[i][j]$值
2. **高亮机制**：
   - 红色闪烁：当前操作的货架$u$
   - 绿色渐变：概率变化的$j$值区间
3. **音效系统**：
   - 清脆"叮"声：完成组合数计算
   - 流水声：状态转移过程
4. **复古风格**：
   - 8-bit像素字体显示概率值
   - 16色调色板（棕黄渐变模拟蜂蜜）

---

3. **题解清单 (≥4星)**

| 题解作者       | 星级 | 核心亮点                                                                 |
|----------------|------|--------------------------------------------------------------------------|
| xtx1092515503 | ★★★★☆ | 精确处理大范围组合数，避免精度爆炸；使用滚动数组优化空间                 |
| Alex_Wei      | ★★★★  | 逆向思维（维护未吃蜜罐），给出组合数动态计算方法                         |
| Graphcity     | ★★★★  | 利用$a_i \leq 100$的特性，设计$O(nVk)$的高效算法                          |

---

4. **最优代码片段**

```cpp
// 组合数预处理（解决大数精度问题）
for(int i=0;i<=MAXN;i++) C[i][0]=1;
for(int i=1;i<=MAXN;i++)
    for(int j=1;j<=min(i,5);j++)
        C[i][j] = C[i-1][j-1] + C[i-1][j];

// 关键转移逻辑
res -= f[u][0];
for(int j=0;j<=num[u];j++){
    double ans = 0;
    for(int k=j; k<=min(j+w,now[u]); k++)
        ans += f[u][k] * C[k][k-j] * C[now[u]-k][w-(k-j)];
    f[u][j] = ans / C[now[u]][w];
}
res += f[u][0];
```

---

5. **同类题目推荐**
1. CF518D - Ilya and Escalator（概率DP）
2. P1850 换教室（期望DP）
3. CF16E - Fish（状态压缩概率转移）

---

6. **可视化实现方案**

```javascript
// 伪代码示例
class HoneyGrid {
    constructor(n) {
        this.canvas = document.createElement('canvas');
        this.ctx = this.canvas.getContext('2d');
        this.grid = new Array(n).fill(0).map(() => new Array(101));
        this.playSound('startup'); // 8-bit启动音效
    }

    update(u, k) {
        this.highlight(u); // 红色边框闪烁
        for(let j=0; j<=100; j++) {
            this.cell(u,j).alpha = f[u][j]; // 透明度映射概率
            this.playSound('drop', 0.2*j); // 概率越大音调越高
        }
    }
}
```

---

7. **思维跃迁**
- **降维打击**：将看似复杂的概率问题转化为线性DP状态转移
- **组合数预计算**：通过观察操作参数范围（$k \leq 5$）大幅降低计算量
- **逆向维护**：维护未被品尝的状态比维护已品尝状态更易处理转移

---

8. **灵魂拷问**
如果货架容量达到$10^9$级别，上述算法将如何优化？  
→ 离散化概率分布，仅维护非零概率区间

---
处理用时：61.29秒