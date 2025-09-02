# 题目信息

# Food Buying

## 题目描述

Mishka wants to buy some food in the nearby shop. Initially, he has $ s $ burles on his card.

Mishka can perform the following operation any number of times (possibly, zero): choose some positive integer number $ 1 \le x \le s $ , buy food that costs exactly $ x $ burles and obtain $ \lfloor\frac{x}{10}\rfloor $ burles as a cashback (in other words, Mishka spends $ x $ burles and obtains $ \lfloor\frac{x}{10}\rfloor $ back). The operation $ \lfloor\frac{a}{b}\rfloor $ means $ a $ divided by $ b $ rounded down.

It is guaranteed that you can always buy some food that costs $ x $ for any possible value of $ x $ .

Your task is to say the maximum number of burles Mishka can spend if he buys food optimally.

For example, if Mishka has $ s=19 $ burles then the maximum number of burles he can spend is $ 21 $ . Firstly, he can spend $ x=10 $ burles, obtain $ 1 $ burle as a cashback. Now he has $ s=10 $ burles, so can spend $ x=10 $ burles, obtain $ 1 $ burle as a cashback and spend it too.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
1
10
19
9876
12345
1000000000```

### 输出

```
1
11
21
10973
13716
1111111111```

# AI分析结果

### 题目内容
# 购买食物

## 题目描述
米什卡想在附近的商店买些食物。最初，他的卡上有 $s$ 卢布。

米什卡可以进行以下操作任意次（可能为零次）：选择一个正整数 $1 \leq x \leq s$，购买价值恰好为 $x$ 卢布的食物，并获得 $\lfloor\frac{x}{10}\rfloor$ 卢布的现金返还（换句话说，米什卡花费 $x$ 卢布并获得 $\lfloor\frac{x}{10}\rfloor$ 卢布返还）。操作 $\lfloor\frac{a}{b}\rfloor$ 表示 $a$ 除以 $b$ 向下取整。

保证对于任何可能的 $x$ 值，你都能买到价值为 $x$ 的食物。

你的任务是说出如果米什卡以最优方式购买食物，他最多可以花费多少卢布。

例如，如果米什卡有 $s = 19$ 卢布，那么他最多可以花费 $21$ 卢布。首先，他可以花费 $x = 10$ 卢布，获得 $1$ 卢布现金返还。现在他有 $s = 10$ 卢布，所以可以再花费 $x = 10$ 卢布，获得 $1$ 卢布现金返还并也花掉它。

你必须回答 $t$ 个独立的测试用例。

## 样例 #1
### 输入
```
6
1
10
19
9876
12345
1000000000
```
### 输出
```
1
11
21
10973
13716
1111111111
```
### 算法分类
数学

### 题解综合分析与结论
1. **幻之陨梦**：思路是将花 $x$ 元得 $\lfloor\frac{x}{10}\rfloor$ 元现金返还理解为花 $9$ 份钱能买 $10$ 份东西，得出公式 $ans = (int)(s / 0.9)$ 。代码简洁，直接运用公式计算输出。
2. **123456zmy**：与幻之陨梦思路一致，也是认为每次返还 $10\%$，直接将 $s$ 除 $0.9$ 向下取整输出。
3. **Aehnuwx**：贪心策略，每次花费 $10$ 可使花费钱数最大化，得出分段函数 $\mathbf{ans}= \begin{cases} \lfloor \dfrac{s}{9} \rfloor \times 10 +s\bmod 9-1,9|s \\ \lfloor \dfrac{s}{9} \rfloor \times 10 +s\bmod 9, \rm Otherwise \end{cases}$ ，并指出可以用 $s+\lfloor \dfrac{s-1}{9} \rfloor$ 或 $\lfloor \dfrac{10s}{9} \rfloor$ 替代。
4. **Cult_style**：通过模拟每次操作，当 $a\geq10$ 时，不断计算每次操作花费和获得现金返还后的剩余金额，最后输出总花费。但代码相对复杂，效率不如前几种方法。

综合来看，幻之陨梦和123456zmy的方法简洁高效，直接利用数学关系得出结果；Aehnuwx虽然思路复杂些，但也给出了不同角度的数学推导；Cult_style的模拟方法代码复杂且效率低。

### 所选4星及以上题解
- **幻之陨梦（5星）**
  - **关键亮点**：思路清晰，将复杂的现金返还规则转化为简单的数学公式，代码简洁明了，直接运用公式计算并输出结果。
  - **重点代码**：
```cpp
#include<cstdio>
using namespace std;
int T,s,ans;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&s);
        ans=(int)(s/0.9);
        printf("%d\n",ans);
    }
    return 0;
}
```
  - **核心实现思想**：通过将题目中的现金返还规则理解为花9份钱能买10份东西，得出 $ans = (int)(s / 0.9)$ 的公式，输入 $T$ 和 $s$ 后，直接按公式计算并输出结果。
- **123456zmy（5星）**
  - **关键亮点**：与幻之陨梦思路相同，但使用了 `bits/stdc++.h` 万能头文件，代码同样简洁，直接实现核心思路。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,s;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&s);
		printf("%d\n",(int)(s/0.9));
	}
	return 0;
}
```
  - **核心实现思想**：认为每次返还 $10\%$，直接将输入的 $s$ 除 $0.9$ 向下取整并输出结果。

### 最优关键思路或技巧
将题目中花费与现金返还的复杂规则转化为简单的数学关系，即花9份钱能买10份东西，从而直接通过 $s/0.9$ 向下取整得到结果，极大简化计算过程。

### 可拓展思路
此类题目属于数学计算优化类，类似套路是将复杂的操作规则转化为简单数学公式。例如在一些购物满减、折扣返现等场景题目中，可通过分析规则找到类似的数学关系快速求解。

### 洛谷相似题目推荐
1. [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析时间分配规则，利用简单数学计算得出结果。
2. [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同包装铅笔价格和所需铅笔数量，通过数学计算选择最优购买方案。
3. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：利用等差数列求和公式等数学知识解决连续自然数和的问题。 

---
处理用时：58.05秒