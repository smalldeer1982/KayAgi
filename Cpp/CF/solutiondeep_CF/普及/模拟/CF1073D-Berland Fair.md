# 题目信息

# Berland Fair

## 题目描述

XXI Berland Annual Fair is coming really soon! Traditionally fair consists of $ n $ booths, arranged in a circle. The booths are numbered $ 1 $ through $ n $ clockwise with $ n $ being adjacent to $ 1 $ . The $ i $ -th booths sells some candies for the price of $ a_i $ burles per item. Each booth has an unlimited supply of candies.

Polycarp has decided to spend at most $ T $ burles at the fair. However, he has some plan in mind for his path across the booths:

- at first, he visits booth number $ 1 $ ;
- if he has enough burles to buy exactly one candy from the current booth, then he buys it immediately;
- then he proceeds to the next booth in the clockwise order (regardless of if he bought a candy or not).

Polycarp's money is finite, thus the process will end once he can no longer buy candy at any booth.

Calculate the number of candies Polycarp will buy.

## 说明/提示

Let's consider the first example. Here are Polycarp's moves until he runs out of money:

1. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 33 $ ;
2. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 31 $ ;
3. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 26 $ ;
4. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 21 $ ;
5. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 19 $ ;
6. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 14 $ ;
7. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 9 $ ;
8. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 7 $ ;
9. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 2 $ ;
10. Booth $ 1 $ , buys no candy, not enough money;
11. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 0 $ .

No candy can be bought later. The total number of candies bought is $ 10 $ .

In the second example he has $ 1 $ burle left at the end of his path, no candy can be bought with this amount.

## 样例 #1

### 输入

```
3 38
5 2 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 21
2 4 100 2 6
```

### 输出

```
6
```

# AI分析结果

### 题目中文重写
# 伯兰集市

## 题目描述
第21届伯兰年度集市马上就要到啦！传统上，集市由 $n$ 个摊位围成一个圆圈。摊位按顺时针方向从 $1$ 到 $n$ 编号，其中 $n$ 号摊位与 $1$ 号摊位相邻。第 $i$ 个摊位以 $a_i$ 伯尔（货币单位）的单价出售糖果，且每个摊位的糖果供应无限。

波利亚尔决定在集市上最多花费 $T$ 伯尔。不过，他对于逛摊位有如下计划：
- 首先，他前往 $1$ 号摊位；
- 如果他有足够的钱恰好从当前摊位购买一颗糖果，他会立即购买；
- 然后，他按顺时针方向前往下一个摊位（无论是否购买了糖果）。

由于波利亚尔的钱是有限的，一旦他在任何摊位都无法购买糖果时，这个过程就会结束。

请计算波利亚尔会购买的糖果数量。

## 说明/提示
让我们考虑第一个样例。以下是波利亚尔在钱花完之前的行动过程：
1. 在 $1$ 号摊位，花费 $5$ 伯尔购买糖果，此时 $T = 33$；
2. 在 $2$ 号摊位，花费 $2$ 伯尔购买糖果，此时 $T = 31$；
3. 在 $3$ 号摊位，花费 $5$ 伯尔购买糖果，此时 $T = 26$；
4. 在 $1$ 号摊位，花费 $5$ 伯尔购买糖果，此时 $T = 21$；
5. 在 $2$ 号摊位，花费 $2$ 伯尔购买糖果，此时 $T = 19$；
6. 在 $3$ 号摊位，花费 $5$ 伯尔购买糖果，此时 $T = 14$；
7. 在 $1$ 号摊位，花费 $5$ 伯尔购买糖果，此时 $T = 9$；
8. 在 $2$ 号摊位，花费 $2$ 伯尔购买糖果，此时 $T = 7$；
9. 在 $3$ 号摊位，花费 $5$ 伯尔购买糖果，此时 $T = 2$；
10. 在 $1$ 号摊位，因钱不够未购买糖果；
11. 在 $2$ 号摊位，花费 $2$ 伯尔购买糖果，此时 $T = 0$。

之后就无法再购买糖果了。总共购买的糖果数量是 $10$ 颗。

在第二个样例中，他在逛完摊位后还剩下 $1$ 伯尔，但这点钱无法再购买任何糖果。

## 样例 #1
### 输入
```
3 38
5 2 5
```
### 输出
```
10
```

## 样例 #2
### 输入
```
5 21
2 4 100 2 6
```
### 输出
```
6
```

### 综合分析与结论
这些题解的核心思路都是先计算整圈购买的情况，再处理剩余钱数不足以整圈购买的情况。在处理过程中，不同题解采用了不同的优化策略。
- **思路对比**：大部分题解通过计算每圈能购买的糖果数和花费，用总钱数取模来减少不必要的模拟。部分题解在此基础上，还考虑了剔除无法购买糖果的摊位，进一步优化计算。
- **算法要点**：主要算法要点包括计算每圈花费和购买数量、取模操作减少计算量、标记或删除无法购买的摊位。
- **解决难点**：难点在于处理钱数的变化和摊位的剔除，避免不必要的重复计算。通过取模操作和标记摊位，不同题解都有效地解决了这些问题。

### 高评分题解
- **作者：Ynoi（5星）**
    - **关键亮点**：思路清晰，代码简洁，通过取模操作将时间复杂度控制在 $n\log m$，能有效解决问题。
    - **核心代码**：
```cpp
while(s > 0)
{
    s = 0;rs = 0;
    for(int i = 1; i <= n; i ++)
        if(s+a[i] <= m)
        {
            s += a[i]; 
            rs ++;
        }
    if(s == 0) break;
    ans += m / s * rs;
    m %= s;
}
```
核心实现思想：每次计算一圈能购买的糖果数 `rs` 和花费 `s`，若 `s` 不为 0，则用总钱数 `m` 除以 `s` 得到能转的圈数，乘以 `rs` 累加到答案 `ans` 中，再对 `m` 取模。

- **作者：信息向阳花木（4星）**
    - **关键亮点**：详细解释了避免重复模拟的思路，代码可读性高，通过记录每圈信息优化计算。
    - **核心代码**：
```cpp
while (sum > 0 && t > 0)
{
    res += t / sum * cnt;
    t %= sum;
    sum = 0; cnt = 0;
    for (int i = 1; i <= n; i ++ )
    {
        if(t - sum >= a[i])
        {
            sum += a[i];
            cnt ++;
        }
    }
}
```
核心实现思想：在 `sum` 和 `t` 都大于 0 时，用 `t` 除以 `sum` 得到能转的圈数，乘以 `cnt` 累加到答案 `res` 中，对 `t` 取模，然后重新计算一圈的花费 `sum` 和购买数量 `cnt`。

- **作者：傅思维666（4星）**
    - **关键亮点**：分享了思路优化的过程，从暴力枚举到逐步优化，最终通过标记无法购买的摊位提高效率。
    - **核心代码**：
```cpp
while(1)
{
    ans+=tot*(k/sum);
    k%=sum;
    int flag=0;
    for(int i=1;i<=n;i++)
    {
        if(v[i])
            continue;
        if(k>=a[i])
        {
            ans++;
            k-=a[i];
            flag=1;
        }
        else
        {
            v[i]=1;
            sum-=a[i];
            tot--;
        }
    }
    if(flag==0)
        break;
}
```
核心实现思想：使用死循环，每次用 `k` 除以 `sum` 得到能转的圈数，乘以 `tot` 累加到答案 `ans` 中，对 `k` 取模。遍历摊位，若能购买则更新 `ans` 和 `k`，若不能购买则标记摊位并更新 `sum` 和 `tot`。当 `flag` 为 0 时，说明无法再购买，退出循环。

### 最优关键思路或技巧
- **取模优化**：通过计算每圈的花费，用总钱数对其取模，减少不必要的模拟，将时间复杂度降低。
- **标记或删除无法购买的摊位**：避免对无法购买糖果的摊位进行重复判断，提高计算效率。

### 拓展思路
同类型题目可能会有不同的场景，如摊位有不同的营业时间、商品有不同的限购数量等。解题思路仍然可以围绕计算每轮的花费和收益，通过取模和标记等方法优化计算。

### 洛谷相似题目推荐
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)：模拟比赛过程，根据规则计算得分。
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)：根据多项式的系数和次数，按规则输出多项式。
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)：根据给定规则对字符串进行展开操作。

### 个人心得摘录与总结
- **傅思维666**：最初的暴力枚举代码在数据较水时能通过，但提交到原题会超时。后来对代码进行优化，包括不用前缀和数组、用乘法算式代替循环减法、用标记数组跳过无法购买的摊位等。总结是要不断优化算法，避免因数据水而掩盖代码的复杂度问题。
- **Hanx16Kira**：提到自己的解法可能不是最优，但因为计时方式改变耗时较低。通过优先队列维护权值最大的点，利用取模和剔除无用点优化计算，说明优先队列可舍去无用状态，降低常数。 

---
处理用时：47.54秒