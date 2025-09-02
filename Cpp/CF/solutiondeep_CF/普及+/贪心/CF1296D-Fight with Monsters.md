# 题目信息

# Fight with Monsters

## 题目描述

There are $ n $ monsters standing in a row numbered from $ 1 $ to $ n $ . The $ i $ -th monster has $ h_i $ health points (hp). You have your attack power equal to $ a $ hp and your opponent has his attack power equal to $ b $ hp.

You and your opponent are fighting these monsters. Firstly, you and your opponent go to the first monster and fight it till his death, then you and your opponent go the second monster and fight it till his death, and so on. A monster is considered dead if its hp is less than or equal to $ 0 $ .

The fight with a monster happens in turns.

1. You hit the monster by $ a $ hp. If it is dead after your hit, you gain one point and you both proceed to the next monster.
2. Your opponent hits the monster by $ b $ hp. If it is dead after his hit, nobody gains a point and you both proceed to the next monster.

You have some secret technique to force your opponent to skip his turn. You can use this technique at most $ k $ times in total (for example, if there are two monsters and $ k=4 $ , then you can use the technique $ 2 $ times on the first monster and $ 1 $ time on the second monster, but not $ 2 $ times on the first monster and $ 3 $ times on the second monster).

Your task is to determine the maximum number of points you can gain if you use the secret technique optimally.

## 样例 #1

### 输入

```
6 2 3 3
7 10 50 12 1 8```

### 输出

```
5```

## 样例 #2

### 输入

```
1 1 100 99
100```

### 输出

```
1```

## 样例 #3

### 输入

```
7 4 2 1
1 3 5 4 2 7 6```

### 输出

```
6```

# AI分析结果



# Fight with Monsters（与怪物战斗）

## 题目描述

有 $n$ 个怪物排成一行，编号从 $1$ 到 $n$。第 $i$ 个怪物有 $h_i$ 点生命值（hp）。你的攻击力为 $a$ hp，对手的攻击力为 $b$ hp。

你与对手轮流攻击这些怪物。首先你们攻击第一个怪物直到其死亡，接着攻击第二个怪物，依此类推。若你的攻击使怪物血量 $\leq 0$，则你获得一分；若对手的攻击使其死亡，则无人得分。

你拥有最多 $k$ 次特殊能力，可让对手跳过他的回合。求最大化能获得的分数。

---

## 题解综合分析

### 算法核心思路
所有题解均采用 **贪心+模运算** 的核心逻辑：
1. **模运算处理**：将怪物血量 $h_i$ 对 $(a+b)$ 取模，得到最后一轮的血量 $m$
2. **关键判断**：
   - 若 $m \leq a$：无需使用特殊能力即可得分
   - 若 $m > a$：需要 $\lceil \frac{m-a}{a} \rceil$ 次特殊能力
3. **贪心选择**：按所需次数排序，优先选择消耗次数少的怪物

### 难点处理对比
| 处理方式               | 代表题解          | 核心技巧                                                                 |
|------------------------|-------------------|--------------------------------------------------------------------------|
| 将 $h_i$ 减1后取模     | 幻之陨梦、Elairin176 | 避免余数为0的特殊情况，简化计算式 $h_i = (x-1)\%(a+b)+1$                |
| 余数0时设为 $a+b$      | _6_awa、Priori_Incantatem | 直接处理余数为0的情况为完整轮次 $h_i = (h_i\%(a+b)) \text{ or } (a+b)$ |
| 浮点数ceil运算         | _6_awa、jscblack   | 使用 `ceil((p - a)/a)` 明确向上取整                                      |
| 整数运算避免浮点       | Yizhixiaoyun、123456zmy | 通过 `(x + a - 1)/a` 实现等价效果                                        |

---

## 优质题解推荐

### 1. 作者：_6_awa（⭐⭐⭐⭐⭐）
**亮点**：逻辑清晰，处理余数为0的情况简洁，代码可读性极佳  
```cpp
int p = c[i] % (a + b);
if(p == 0) p = a + b;  // 处理余数为0的情况
if(p <= a) d[i] = 0;
else d[i] = ceil((p - a) / (double)a);
sort(d + 1, d + n + 1);  // 贪心排序
```

### 2. 作者：Yizhixiaoyun（⭐⭐⭐⭐）
**亮点**：通过整数运算避免浮点误差，代码高效  
```cpp
h[i] = (read() - 1) % (a + b);  // 减1处理余数
h[i] /= a;  // 等价于计算所需次数
sort(h + 1, h + n + 1);
```

### 3. 作者：幻之陨梦（⭐⭐⭐⭐）
**亮点**：独创减1取模法统一处理边界，代码简洁  
```cpp
x = (x-1) % (a+b);  // 关键处理
cost[i] = x/a;      // 直接整数除法
sort(cost, cost+n);
```

---

## 最优技巧总结
1. **模运算统一处理**：通过 $(a+b)$ 取模将问题简化为最后一轮的血量计算
2. **整数运算优化**：使用 `(x + a - 1)/a` 替代浮点运算避免精度问题
3. **边界处理技巧**：对余数为0的情况统一转换为 $a+b$ 或通过减1取模避免特判

---

## 相似题目推荐
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080) - 贪心排序经典问题
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 时间调度中的贪心策略
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 优先队列实现贪心

---

## 个人心得摘录
> **幻之陨梦**：  
> _"发现当余数为0时，将血量减1再取模可以统一处理，避免了复杂的条件判断"_  
> **Elairin176**：  
> _"调试中发现直接计算最后一轮剩余血量时，边界条件容易出错，最终通过减1取模法解决"_  
> **jscblack**：  
> _"最初误以为需要模拟整个攻击过程，后来意识到只需关注最后一轮的关键攻击机会"_

---
处理用时：53.48秒