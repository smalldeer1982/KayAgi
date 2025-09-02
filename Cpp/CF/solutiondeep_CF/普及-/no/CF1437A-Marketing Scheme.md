# 题目信息

# Marketing Scheme

## 题目描述

You got a job as a marketer in a pet shop, and your current task is to boost sales of cat food. One of the strategies is to sell cans of food in packs with discounts.

Suppose you decided to sell packs with $ a $ cans in a pack with a discount and some customer wants to buy $ x $ cans of cat food. Then he follows a greedy strategy:

- he buys $ \left\lfloor \frac{x}{a} \right\rfloor $ packs with a discount;
- then he wants to buy the remaining $ (x \bmod a) $ cans one by one.

 $ \left\lfloor \frac{x}{a} \right\rfloor $ is $ x $ divided by $ a $ rounded down, $ x \bmod a $ is the remainer of $ x $ divided by $ a $ .

But customers are greedy in general, so if the customer wants to buy $ (x \bmod a) $ cans one by one and it happens that $ (x \bmod a) \ge \frac{a}{2} $ he decides to buy the whole pack of $ a $ cans (instead of buying $ (x \bmod a) $ cans). It makes you, as a marketer, happy since the customer bought more than he wanted initially.

You know that each of the customers that come to your shop can buy any number of cans from $ l $ to $ r $ inclusive. Can you choose such size of pack $ a $ that each customer buys more cans than they wanted initially?

## 说明/提示

In the first test case, you can take, for example, $ a = 5 $ as the size of the pack. Then if a customer wants to buy $ 3 $ cans, he'll buy $ 5 $ instead ( $ 3 \bmod 5 = 3 $ , $ \frac{5}{2} = 2.5 $ ). The one who wants $ 4 $ cans will also buy $ 5 $ cans.

In the second test case, there is no way to choose $ a $ .

In the third test case, you can take, for example, $ a = 80 $ .

## 样例 #1

### 输入

```
3
3 4
1 2
120 150```

### 输出

```
YES
NO
YES```

# AI分析结果

### 题目内容
# 营销方案

## 题目描述
你在一家宠物店找到了一份营销工作，你当前的任务是促进猫粮的销售。其中一个策略是打折销售猫粮罐头包。

假设你决定以折扣价销售每包含 $a$ 罐的猫粮包，而有顾客想要购买 $x$ 罐猫粮。那么他会遵循一种贪心策略：
 - 他会购买 $\left\lfloor \frac{x}{a} \right\rfloor$ 个折扣包；
 - 然后他想逐个购买剩余的 $(x \bmod a)$ 罐。

 $\left\lfloor \frac{x}{a} \right\rfloor$ 是 $x$ 除以 $a$ 向下取整的结果，$x \bmod a$ 是 $x$ 除以 $a$ 的余数。

但一般来说顾客都很贪心，所以如果顾客想逐个购买 $(x \bmod a)$ 罐，而恰好 $(x \bmod a) \geq \frac{a}{2}$，他就会决定购买一整包 $a$ 罐（而不是购买 $(x \bmod a)$ 罐）。这会让身为营销人员的你很高兴，因为顾客购买的比他最初想要的更多。

你知道每个来你店里的顾客可以购买从 $l$ 到 $r$（包含两端）罐的任意数量的猫粮。你能选择这样一个包的大小 $a$，使得每个顾客购买的猫粮罐数都比他们最初想要的多吗？

## 说明/提示
在第一个测试用例中，例如，你可以取 $a = 5$ 作为包的大小。那么如果一个顾客想要买 $3$ 罐，他会买 $5$ 罐（$3 \bmod 5 = 3$，$\frac{5}{2} = 2.5$）。想要买 $4$ 罐的顾客也会买 $5$ 罐。

在第二个测试用例中，没有办法选择 $a$。

在第三个测试用例中，例如，你可以取 $a = 80$。

## 样例 #1
### 输入
```
3
3 4
1 2
120 150
```
### 输出
```
YES
NO
YES
```
### 算法分类
数学

### 题解综合分析与结论
所有题解核心思路一致，都是判断是否存在一个数 $a$，使得对于区间 $[l, r]$ 内的任意数 $x$ 都满足 $x \bmod a \geq \frac{a}{2}$，最终结论均为当 $l \times 2 > r$ 时输出 “YES”，否则输出 “NO” 。不同题解的分析角度略有差异，部分通过找规律得出结论，部分从理论推导出发。

### 所选的题解
- **作者：Eason_AC（5星）**
  - **关键亮点**：思路清晰简洁，直接从使 $x \bmod a \geq \frac{a}{2}$ 的角度出发，考虑让 $a = 2x$ 这种特殊情况，进而推导出判断条件 $l \times 2 \leq r$ 不成立时才有解，逻辑连贯。
  - **重点代码**：
```cpp
int t, l, r;
int main() {
    getint(t);
    while(t--) {
        getint(l), getint(r);
        if(l * 2 <= r) puts("NO"); else puts("YES");
    }
    return 0;
}
```
  - **核心实现思想**：读入每组询问的 $l$ 和 $r$，根据推导的条件 $l \times 2 \leq r$ 判断并输出结果。
- **作者：_ajthreac_（4星）**
  - **关键亮点**：从 $a$ 与区间端点 $l$、$r$ 的关系入手进行分析，对于 $l$ 需满足 $l \geq \frac{a}{2}$，对于 $r$ 需满足 $r < a$，通过这种方式得出最终判断条件，分析角度较为新颖。
  - **重点代码**：
```cpp
int n,l,r;
int main(){
    Read(n);
    while(n--){
        Read(l),Read(r);
        if(l*2>r)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
```
  - **核心实现思想**：读入询问组数及每组的 $l$ 和 $r$，依据分析得出的 $l \times 2 > r$ 这个条件进行判断并输出结果。
- **作者：itisover（4星）**
  - **关键亮点**：通过分类讨论全面地证明了结论。分别讨论了 $a > l$、$a = l$、$l < a < r$ 且 $r \geq 2l$ 这几种情况，逻辑严谨，证明过程详细。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int T,l,r;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&l,&r);
        if(r<(l<<1)) printf("%s\n","YES");
        else printf("%s\n","NO");
    }
    return 0;
}
```
  - **核心实现思想**：读入测试用例数量 $T$，对每组的 $l$ 和 $r$，根据分类讨论得出的 $r < 2l$ 这个条件判断并输出结果。

### 最优关键思路或技巧
从特殊情况入手分析，如令 $a = 2x$ 满足 $x \bmod a \geq \frac{a}{2}$，进而推导出一般的判断条件。或者从 $a$ 与区间端点关系出发，通过严谨的分类讨论得出结论。

### 可拓展思路
此类题目属于基于数学关系判断存在性的问题，类似套路为从特殊情况找规律，或者从边界条件、不同情况分类讨论来推导通用结论。

### 相似知识点洛谷题目
 - [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)：涉及数学中的质数及分解相关知识。
 - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：需要通过数学推导找出满足条件的连续自然数序列，与本题从数学关系推导结论类似。
 - [P2669 金币](https://www.luogu.com.cn/problem/P2669)：通过分析数学规律来解决问题，和本题找规律或推导判断条件思路相符。

### 个人心得摘录与总结
无。 

---
处理用时：57.55秒