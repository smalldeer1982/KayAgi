# 题目信息

# Ivan and Powers of Two

## 题目描述

Ivan has got an array of $ n $ non-negative integers $ a_{1},a_{2},...,a_{n} $ . Ivan knows that the array is sorted in the non-decreasing order.

Ivan wrote out integers $ 2^{a_{1}},2^{a_{2}},...,2^{a_{n}} $ on a piece of paper. Now he wonders, what minimum number of integers of form $ 2^{b} $ $ (b>=0) $ need to be added to the piece of paper so that the sum of all integers written on the paper equalled $ 2^{v}-1 $ for some integer $ v $ $ (v>=0) $ .

Help Ivan, find the required quantity of numbers.

## 说明/提示

In the first sample you do not need to add anything, the sum of numbers already equals $ 2^{3}-1=7 $ .

In the second sample you need to add numbers $ 2^{0},2^{1},2^{2} $ .

## 样例 #1

### 输入

```
4
0 1 1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
1
3
```

### 输出

```
3
```

# AI分析结果



# Ivan and Powers of Two

## 题目描述

Ivan 有一个包含 $n$ 个非负整数 $a_1,a_2,...,a_n$ 的数组，且数组按非递减顺序排列。

Ivan 在纸上写下了 $2^{a_1},2^{a_2},...,2^{a_n}$。现在他想知道，至少需要添加多少个形如 $2^b$（$b \geq 0$）的整数，才能使纸上所有数的总和等于 $2^v - 1$（其中 $v \geq 0$）。

帮助 Ivan 求出需要添加的最小数量。

## 说明/提示

- 第一个样例无需添加，总和已经是 $2^3 - 1 = 7$。
- 第二个样例需添加 $2^0,2^1,2^2$。

## 样例 #1

### 输入
```
4
0 1 1 1
```

### 输出
```
0
```

## 样例 #2

### 输入
```
1
3
```

### 输出
```
3
```

---

**算法分类**：贪心

---

## 题解分析

### 核心思路
将输入的 $a_i$ 合并为更高次幂（利用 $2^x + 2^x = 2^{x+1}$），最终得到一个无重复次幂的集合。目标要求总和为 $2^v - 1$，即需要所有 $0$ 到 $v-1$ 次幂都存在。答案即为最大次幂 $+1$ 减去当前集合大小。

### 关键思路
1. **合并重复次幂**：使用集合或优先队列动态维护当前存在的次幂，合并相同项直到唯一。
2. **计算空缺数量**：最大次幂 $max$ 确定目标 $v = max + 1$，所需补全数量为 $v - \text{集合大小}$。

---

## 精选题解

### 题解1：luojien（4星）
**亮点**：利用 `set` 高效维护合并后的次幂，代码简洁。
```cpp
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
set<int> s;
void uniquee(int& x) {
    while (s.count(x)) {
        s.erase(x);
        x++;
    } 
    s.insert(x);
}
int main() {
    int n;
    cin >> n;
    int mx = -1e9;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        uniquee(x);
        mx = max(mx, x);
    }
    cout << mx + 1 - s.size() << endl;
    return 0;
}
```

### 题解2：111101q（4星）
**亮点**：代码极简，逻辑清晰，适合快速理解核心逻辑。
```cpp
#include<iostream>
#include<set>
using namespace std;
int n,x,maxn;
set<int>s;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x;
        while(s.count(x)) s.erase(x++);
        s.insert(x);
        maxn=max(maxn,x);
    }
    cout<<maxn+1-s.size();
    return 0;
}
```

### 题解3：lanretE（4星）
**亮点**：详细解释二进制特性，使用 `map` 实现合并过程。
```cpp
#include<iostream>
#include<map>
using namespace std;
int n,v;
map<int,int> sum;
int main(){
    cin>>n; 
    for(int i=1;i<=n;++i){
        int x; cin>>x;
        while(sum.count(x)) sum.erase(x++);
        sum[x]++;
        v = max(v,x);
    }
    cout << v + 1 - sum.size() << endl;
    return 0;
}
```

---

## 关键技巧总结
1. **数据结构选择**：`set` 或 `map` 用于动态维护唯一次幂，优先队列也可用于合并但需注意输出格式。
2. **数学性质应用**：利用二进制幂次合并特性（$2^x + 2^x = 2^{x+1}$）简化问题。
3. **边界处理**：最大次幂 $max$ 决定 $v$，最终空缺数计算为 $v - \text{元素数量}$。

---

## 同类题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心+优先队列
2. [P7072 直播获奖](https://www.luogu.com.cn/problem/P7072) - 动态维护有序集合
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 贪心策略选择

---
处理用时：200.84秒