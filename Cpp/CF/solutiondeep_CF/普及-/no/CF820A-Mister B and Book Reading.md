# 题目信息

# Mister B and Book Reading

## 题目描述

Mister B once received a gift: it was a book about aliens, which he started read immediately. This book had $ c $ pages.

At first day Mister B read $ v_{0} $ pages, but after that he started to speed up. Every day, starting from the second, he read $ a $ pages more than on the previous day (at first day he read $ v_{0} $ pages, at second — $ v_{0}+a $ pages, at third — $ v_{0}+2a $ pages, and so on). But Mister B is just a human, so he physically wasn't able to read more than $ v_{1} $ pages per day.

Also, to refresh his memory, every day, starting from the second, Mister B had to reread last $ l $ pages he read on the previous day. Mister B finished the book when he read the last page for the first time.

Help Mister B to calculate how many days he needed to finish the book.

## 说明/提示

In the first sample test the book contains $ 5 $ pages, so Mister B read it right at the first day.

In the second sample test at first day Mister B read pages number $ 1-4 $ , at second day — $ 4-11 $ , at third day — $ 11-12 $ and finished the book.

In third sample test every day Mister B read $ 1 $ page of the book, so he finished in 15 days.

## 样例 #1

### 输入

```
5 5 10 5 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
12 4 12 4 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
15 1 100 0 0
```

### 输出

```
15
```

# AI分析结果

### 题目翻译
# B先生与读书

## 题目描述
B先生曾收到一份礼物：一本关于外星人的书，他立刻开始阅读。这本书共有 $ c $ 页。

第一天，B先生读了 $ v_{0} $ 页，但从那之后他开始加快速度。从第二天起，他每天比前一天多读 $ a $ 页（第一天读 $ v_{0} $ 页，第二天读 $ v_{0}+a $ 页，第三天读 $ v_{0}+2a $ 页，依此类推）。但B先生毕竟只是普通人，所以他每天最多只能读 $ v_{1} $ 页。

此外，为了巩固记忆，从第二天起，B先生每天都要重读前一天读过的最后 $ l $ 页。当B先生第一次读完最后一页时，他就完成了这本书的阅读。

请帮助B先生计算他读完这本书需要多少天。

## 说明/提示
在第一个样例测试中，这本书共有 $ 5 $ 页，所以B先生在第一天就读完了。

在第二个样例测试中，第一天B先生读了第 $ 1 - 4 $ 页，第二天读了第 $ 4 - 11 $ 页，第三天读了第 $ 11 - 12 $ 页并读完了这本书。

在第三个样例测试中，B先生每天读 $ 1 $ 页书，所以他用了 $ 15 $ 天读完。

## 样例 #1
### 输入
```
5 5 10 5 4
```
### 输出
```
1
```

## 样例 #2
### 输入
```
12 4 12 4 1
```
### 输出
```
3
```

## 样例 #3
### 输入
```
15 1 100 0 0
```
### 输出
```
15
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟B先生读书的过程，直到读完这本书。具体步骤包括：先处理第一天的阅读情况，然后从第二天开始，根据规则计算每天的阅读量（考虑阅读量上限和复习页数），不断更新剩余页数和天数，直到剩余页数小于等于0。

各题解的区别主要在于代码实现细节，如输入输出方式、变量命名、循环结构等，但整体思路一致。解决的难点在于正确处理第一天的特殊情况（不用复习）以及阅读量的上限。

### 题解评分
- 一叶知秋。：3星。思路清晰，使用了快读优化，但文件读写部分可能会影响通用性。
- 紊莫：4星。思路清晰，代码简洁，对第一天的特判有明确说明。
- Xx_queue：3星。思路清晰，代码逻辑明确。
- ruruo：3星。思路清晰，代码简洁。
- fengxiaoyi：3星。思路清晰，对数据范围和模拟过程有说明。
- Supor__Shoep：3星。思路清晰，但代码中存在逻辑小错误（`reads-=l` 位置可能有误）。
- user470883：3星。思路清晰，代码简洁。
- wangshi：3星。思路清晰，代码有注释。
- ZepX_D：3星。思路清晰，代码简洁。
- 梦游的小雪球：3星。思路清晰，但代码中存在逻辑小错误（`c+=p` 位置可能有误）。

### 较高评分题解
- 紊莫：4星。关键亮点在于思路清晰，对第一天的特判有明确说明，代码简洁。

### 关键思路或技巧
- 模拟过程中，要注意第一天的特殊情况，即不用复习 $ l $ 页。
- 每天的阅读量要取 $ \min(v_0 + a \times (i - 1), v_1) $，确保不超过阅读量上限。

### 拓展思路
同类型题通常是模拟类问题，需要根据题目给定的规则，逐步模拟过程，直到满足结束条件。类似算法套路包括模拟游戏过程、模拟事件发生顺序等。

### 洛谷相似题目推荐
- P1003 铺地毯
- P1042 乒乓球
- P1067 多项式输出

### 个人心得摘录与总结
- 紊莫：提到第一天需要特判否则会出现负数，提醒我们在模拟过程中要注意特殊情况的处理。
- Supor__Shoep：指出题目似乎少翻译了一个条件，但可通过样例看出来，说明在做题时要仔细分析样例，挖掘隐藏条件。

### 重点代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int c,v0,v1,a,l,ans=0,i=0;
    cin>>c>>v0>>v1>>a>>l;
    c-=min(v0,v1),ans++,i++; // 注意第一天需要特判否则会出现负数
    while(c>0)
    {
        c-=min(v0+a*i,v1)-l;
        ans++,i++;
    }
    cout<<ans;
    return 0;
}
```
核心实现思想：先处理第一天的阅读情况，将总页数减去第一天的阅读量，天数加1。然后进入循环，每天计算阅读量（考虑上限和复习页数），更新剩余页数和天数，直到剩余页数小于等于0。 

---
处理用时：37.95秒