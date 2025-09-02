# 题目信息

# Duff and Meat

## 题目描述

Duff is addicted to meat! Malek wants to keep her happy for $ n $ days. In order to be happy in $ i $ -th day, she needs to eat exactly $ a_{i} $ kilograms of meat.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF588A/e0a1a4af93fd8d07e258d5dc1cd3e48db986dfbc.png)There is a big shop uptown and Malek wants to buy meat for her from there. In $ i $ -th day, they sell meat for $ p_{i} $ dollars per kilogram. Malek knows all numbers $ a_{1},...,a_{n} $ and $ p_{1},...,p_{n} $ . In each day, he can buy arbitrary amount of meat, also he can keep some meat he has for the future.

Malek is a little tired from cooking meat, so he asked for your help. Help him to minimize the total money he spends to keep Duff happy for $ n $ days.

## 说明/提示

In the first sample case: An optimal way would be to buy 1 kg on the first day, 2 kg on the second day and 3 kg on the third day.

In the second sample case: An optimal way would be to buy 1 kg on the first day and 5 kg (needed meat for the second and third day) on the second day.

## 样例 #1

### 输入

```
3
1 3
2 2
3 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3
1 3
2 1
3 2
```

### 输出

```
8
```

# AI分析结果

### 题目翻译
# Duff与肉

## 题目描述
Duff对肉上瘾！Malek想让她开心 $n$ 天。为了在第 $i$ 天开心，她需要准确地吃掉 $a_{i}$ 千克肉。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF588A/e0a1a4af93fd8d07e258d5dc1cd3e48db986dfbc.png) 镇上有一家大商店，Malek想从那里为她买肉。在第 $i$ 天，商店每千克肉售价为 $p_{i}$ 美元。Malek知道所有的数字 $a_{1}, \ldots, a_{n}$ 和 $p_{1}, \ldots, p_{n}$。在每一天，他可以购买任意数量的肉，他也可以把买来的肉留到未来吃。

Malek有点厌倦了做肉，所以他向你寻求帮助。帮助他最小化在 $n$ 天内让Duff开心所花费的总金额。

## 说明/提示
在第一个样例中：一个最优的方法是在第一天买1千克，第二天买2千克，第三天买3千克。

在第二个样例中：一个最优的方法是在第一天买1千克，在第二天买5千克（第二天和第三天需要的肉）。

## 样例 #1
### 输入
```
3
1 3
2 2
3 1
```
### 输出
```
10
```

## 样例 #2
### 输入
```
3
1 3
2 1
3 2
```
### 输出
```
8
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，由于肉可以囤，所以在每一天都选择到当天为止价格最低的肉来购买，就能使总花费最小。各题解的区别主要在于代码语言和实现细节。

### 题解评分
- 灵光一闪：4星。思路清晰，代码简洁易懂，注释明确。
- LucasXu80：3星。思路阐述清晰，但使用的是Python代码，对于本题要求的C++算法分析不太契合。
- LYR_：3星。思路与其他题解类似，提到了内存优化，但整体创新性不足。
- 树下：2星。代码存在小问题，逻辑不够清晰，且没有写`return 0`，代码规范性欠佳。

### 所选题解
- 灵光一闪：4星。关键亮点在于思路清晰，代码简洁，通过边读边判的方式，不断更新最低价并计算总花费。

### 重点代码
```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
int a[100005],b[100005],ans,n,num=2e9,tep;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i]>>b[i];
        if(num>b[i]){//跌出了最低价
            num=b[i];//更新最低价
        }
        ans+=num*a[i];//然后相乘再加进ans里
    }
    cout<<ans;//输出……
    return 0;
}
```

### 核心实现思想
在输入每天需要的肉的数量和当天肉的价格时，不断比较当前价格和之前记录的最低价格，如果当前价格更低，则更新最低价格。然后用最低价格乘以当天需要的肉的数量，并累加到总花费中。

### 扩展思路
同类型题通常涉及资源的分配和选择，通过贪心策略来达到最优解。例如在一些购物、任务安排等问题中，都可以考虑使用贪心算法。关键在于找到一个合适的贪心策略，即每次选择都能使整体结果更优。

### 洛谷相似题目
1. P1223 排队接水（https://www.luogu.com.cn/problem/P1223）
2. P1094 纪念品分组（https://www.luogu.com.cn/problem/P1094）
3. P2240 部分背包问题（https://www.luogu.com.cn/problem/P2240）

### 个人心得
本题解中没有明显的个人心得内容。 

---
处理用时：25.68秒