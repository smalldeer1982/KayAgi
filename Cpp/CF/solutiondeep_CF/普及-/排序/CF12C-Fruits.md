# 题目信息

# Fruits

## 题目描述

The spring is coming and it means that a lot of fruits appear on the counters. One sunny day little boy Valera decided to go shopping. He made a list of $ m $ fruits he wanted to buy. If Valera want to buy more than one fruit of some kind, he includes it into the list several times.

When he came to the fruit stall of Ashot, he saw that the seller hadn't distributed price tags to the goods, but put all price tags on the counter. Later Ashot will attach every price tag to some kind of fruits, and Valera will be able to count the total price of all fruits from his list. But Valera wants to know now what can be the smallest total price (in case of the most «lucky» for him distribution of price tags) and the largest total price (in case of the most «unlucky» for him distribution of price tags).

## 样例 #1

### 输入

```
5 3
4 2 1 10 5
apple
orange
mango
```

### 输出

```
7 19
```

## 样例 #2

### 输入

```
6 5
3 5 1 6 8 1
peach
grapefruit
banana
orange
orange
```

### 输出

```
11 30
```

# AI分析结果

### 题目中文重写
# 水果

## 题目描述
春天来了，这意味着柜台上出现了很多水果。一个阳光明媚的日子，小男孩瓦莱拉决定去购物。他列了一个清单，上面有 $m$ 种他想买的水果。如果瓦莱拉想买某种水果超过一个，他会把这种水果在清单上列多次。

当他来到阿肖特的水果摊时，他看到卖家没有给商品贴上价格标签，而是把所有价格标签都放在了柜台上。之后，阿肖特会把每个价格标签贴在某种水果上，瓦莱拉就能算出他清单上所有水果的总价。但瓦莱拉现在就想知道，在最“幸运”（对他来说）的价格标签分配情况下，总价最小能是多少；在最“不幸”的价格标签分配情况下，总价最大能是多少。

## 样例 #1
### 输入
```
5 3
4 2 1 10 5
apple
orange
mango
```
### 输出
```
7 19
```

## 样例 #2
### 输入
```
6 5
3 5 1 6 8 1
peach
grapefruit
banana
orange
orange
```
### 输出
```
11 30
```

### 题解综合分析与结论
- **思路对比**：三位作者思路一致，都是先统计每种水果的数量，对价格和水果数量排序，再根据贪心策略计算最小和最大总价。最小总价是将低价分配给数量多的水果，最大总价是将高价分配给数量多的水果。
- **算法要点**：
    - Fido_Puppy 使用 `map` 统计水果数量，再将其存入数组排序。
    - _Qer 定义 `fruit` 结构体存储水果信息，手动遍历判断新水果并统计数量。
    - fls233666 用数组存储去重后的水果和数量，手动遍历判断重复并统计。
- **解决难点**：核心难点是统计每种水果的数量，三位作者分别用 `map`、结构体和数组解决。

### 题解评分与选择
- **Fido_Puppy**：4星。思路清晰，使用 `map` 简化水果数量统计，代码简洁易懂。
- **_Qer**：3星。思路详细，但代码较长，手动判断新水果较繁琐。
- **fls233666**：3星。思路明确，手动遍历去重和统计数量，代码可读性一般。

### 最优题解
- **Fido_Puppy（4星）**：
    - **关键亮点**：使用 `map` 统计水果数量，简化操作，代码简洁。
    - **核心代码**：
```cpp
#include<iostream>
#include<algorithm>
#include<map>
#include<cstring>
using namespace std;
int n, m, a[100001], c[100001], len = 0, Min=0, Max=0;
map <string, int> b;
string s[100001];
int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) {
        cin >> s[i];
        b[s[i]]++;
    }
    sort(a + 1, a + n + 1, less<int>());
    for(int i = 1; i <= m; i++) {
        if (b[s[i]]!= 0) c[++len] = b[s[i]];
        b[s[i]] = 0;
    }
    sort(c + 1, c + len + 1, greater<int>());
    for(int i = 1; i <= len; i++) {
        Min += c[i] * a[i];
        Max += c[i] * a[n - i + 1];
    }
    cout << Min << " " << Max;
    return 0;
}
```
**核心实现思想**：用 `map` 统计每种水果的数量，将水果数量存入数组排序，对价格数组排序，根据贪心策略计算最小和最大总价。

### 关键思路或技巧
- 使用 `map` 统计字符串数量，利用其键值对特性简化操作。
- 贪心策略：最小总价将低价给数量多的水果，最大总价将高价给数量多的水果。

### 拓展思路
同类型题可拓展到资源分配问题，如不同任务分配不同成本，求总成本最小或最大。类似算法套路是先统计各元素数量，排序后根据贪心策略分配资源。

### 洛谷相似题目推荐
- P1094 [NOIP2007 普及组] 纪念品分组
- P1223 排队接水
- P1803 凌乱的yyy / 线段覆盖

### 个人心得摘录与总结
- Fido_Puppy：指出在 `C++` 的 `STL` 面前，字典树、二分等方法处理字符串计数太复杂，可使用 `map` 简化操作。总结是合理利用 `STL` 能降低代码复杂度。 

---
处理用时：33.49秒