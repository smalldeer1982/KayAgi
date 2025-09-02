# 题目信息

# Benches

## 题目描述

The city park of IT City contains $ n $ east to west paths and $ n $ north to south paths. Each east to west path crosses each north to south path, so there are $ n^{2} $ intersections.

The city funded purchase of five benches. To make it seems that there are many benches it was decided to place them on as many paths as possible. Obviously this requirement is satisfied by the following scheme: each bench is placed on a cross of paths and each path contains not more than one bench.

Help the park administration count the number of ways to place the benches.

## 样例 #1

### 输入

```
5
```

### 输出

```
120```

# AI分析结果

### 题目内容
#### Benches
#### 题目描述
IT市的城市公园有$n$条东西向的道路和$n$条南北向的道路。每条东西向道路与每条南北向道路交叉，所以共有$n^{2}$个交叉点。

市政府出资购买了五个长椅。为了让长椅看起来数量众多，决定将它们放置在尽可能多的道路上。显然，以下方案满足这一要求：每个长椅放置在道路交叉点上，并且每条道路上不超过一个长椅。

请帮助公园管理部门计算放置长椅的方法数量。
#### 样例 #1
##### 输入
```
5
```
##### 输出
```
120
```

### 算法分类
组合数学

### 题解综合分析与结论
所有题解的核心思路一致，均是先从$n$行中选$5$行（组合数$C_n^5$），然后在选定的$5$行中按行依次放置长椅，每行放置的列数选择依次递减（$n, n - 1, n - 2, n - 3, n - 4$），利用乘法原理得到总放置方法数。难点在于避免计算大数，各题解都通过对组合数公式$\frac{n!}{5!(n - 5)!}$进行约分，化简为$\frac{n(n - 1)(n - 2)(n - 3)(n - 4)}{5!}$来解决。

### 所选的题解
- **作者：超级玛丽王子 (5星)**
    - **关键亮点**：思路清晰，先简化模型为$5\times n$的网格图分析每行放置长椅的方法数，再引入从$n$行中选$5$行的组合数概念，逐步推导得出最终公式，逻辑连贯。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main(){
    cin>>n;
    cout<<n*(n-1)*(n-2)*(n-3)*(n-4)/120*n*(n-1)*(n-2)*(n-3)*(n-4);
}
```
    - **核心实现思想**：直接根据推导出的公式`(n(n - 1)(n - 2)(n - 3)(n - 4))^2 / 5!`进行计算，先做除法避免中间结果爆`long long`。
- **作者：int32 (4星)**
    - **关键亮点**：简洁明了地阐述先选$5$行的组合数，再分析每行放置长椅的方法，快速得出答案公式，同时提醒注意数据范围会爆`long long`。
    - **重点代码**：无（未给出具体代码实现）
    - **核心实现思想**：理论推导得出公式$\frac{n!^2}{120(n - 5)!^2}$，化简后同其他题解，实现时应注意数据类型范围。
- **作者：CZQ_King (4星)**
    - **关键亮点**：不仅给出公式计算的代码，还提供了打表的思路及代码，对于数据范围小且计算复杂的题目，打表是一种有效的解题方式。
    - **重点代码（公式）**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main(){
    cin>>n;
    cout<<n*(n-1)*(n-2)*(n-3)*(n-4)/120*n*(n-1)*(n-2)*(n-3)*(n-4);
}
```
    - **核心实现思想（公式）**：与其他题解一致，按推导公式计算。
    - **重点代码（打表）**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f(long long w){
    return w*(w-1)*(w-2)*(w-3)*(w-4)/120*w*(w-1)*(w-2)*(w-3)*(w-4);
}
int main(){
    freopen("2.txt","w",stdout);
    for(long long i=5;i<=100;i++){
        cout<<f(i)<<",";
    }
}
```
    - **核心实现思想（打表）**：通过函数`f`计算每个$n$对应的结果并输出到文件，后续直接读取表中的值。

### 最优关键思路或技巧
1. **组合数的应用**：通过组合数$C_n^5$来确定选择放置长椅的行，再结合每行放置长椅的列的选择方式，利用乘法原理计算总方案数。
2. **公式化简**：为避免计算大数，对组合数公式进行约分，将$n!$和$(n - 5)!$约掉部分项，简化计算。
3. **打表技巧**：对于数据范围较小且计算复杂的情况，提前计算并存储结果，在实际解题时直接查询，可提高效率。

### 可拓展之处
同类型题通常围绕组合数学中的排列组合概念，可能会改变物品数量、限制条件或场景。类似算法套路是先确定选择的组合方式，再分析每种选择下的排列方式，最后利用乘法原理得出结果。在计算时要注意数据范围，合理化简公式或采用其他方式避免大数运算。

### 洛谷相似题目推荐
1. [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：考查二项式定理和组合数的应用。
2. [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)：涉及组合数取模运算，可加深对组合数计算和性质的理解。
3. [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)：进一步拓展组合数在大模数下的计算，考查卢卡斯定理。

### 个人心得摘录与总结
无。 

---
处理用时：52.39秒