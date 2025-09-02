# 题目信息

# Anastasia and pebbles

## 题目描述

Anastasia loves going for a walk in Central Uzhlyandian Park. But she became uninterested in simple walking, so she began to collect Uzhlyandian pebbles. At first, she decided to collect all the pebbles she could find in the park.

She has only two pockets. She can put at most $ k $ pebbles in each pocket at the same time. There are $ n $ different pebble types in the park, and there are $ w_{i} $ pebbles of the $ i $ -th type. Anastasia is very responsible, so she never mixes pebbles of different types in same pocket. However, she can put different kinds of pebbles in different pockets at the same time. Unfortunately, she can't spend all her time collecting pebbles, so she can collect pebbles from the park only once a day.

Help her to find the minimum number of days needed to collect all the pebbles of Uzhlyandian Central Park, taking into consideration that Anastasia can't place pebbles of different types in same pocket.

## 说明/提示

In the first sample case, Anastasia can collect all pebbles of the first type on the first day, of second type — on the second day, and of third type — on the third day.

Optimal sequence of actions in the second sample case:

- In the first day Anastasia collects $ 8 $ pebbles of the third type.
- In the second day she collects $ 8 $ pebbles of the fourth type.
- In the third day she collects $ 3 $ pebbles of the first type and $ 1 $ pebble of the fourth type.
- In the fourth day she collects $ 7 $ pebbles of the fifth type.
- In the fifth day she collects $ 1 $ pebble of the second type.

## 样例 #1

### 输入

```
3 2
2 3 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 4
3 1 8 9 7
```

### 输出

```
5
```

# AI分析结果



### 题目中文翻译
**题目名称：Anastasia 和鹅卵石**

**题目描述**  
Anastasia 喜欢在中央公园散步，但她对简单散步失去兴趣，开始收集鹅卵石。她有两个口袋，每个口袋最多同时装 $k$ 个鹅卵石。公园有 $n$ 种不同类型的鹅卵石，第 $i$ 种有 $w_i$ 个。她不能在同一个口袋混合不同类型的鹅卵石，但可以同时在两个口袋装不同种类的鹅卵石。每天只能收集一次。求收集所有鹅卵石所需的最小天数。

**输入输出样例**  
样例1：  
输入：  
3 2  
2 3 4  
输出：  
3  

样例2：  
输入：  
5 4  
3 1 8 9 7  
输出：  
5  

**说明/提示**  
样例1中，每天分别收集每种类型的鹅卵石。样例2的详细策略见原题描述。

---

### 算法分类  
**贪心**

---

### 题解综合分析  
所有题解的核心思路均基于以下两步：  
1. **单口袋转换**：将问题转化为单个口袋的总次数（每个口袋每天可装两次）。  
2. **总次数上取整**：总次数除以2后向上取整，得到最终天数。  
关键优化点在于如何高效计算每个类型的装袋次数，避免浮点运算，例如使用整数运算技巧 `(w + k - 1) / k`。

---

### 精选题解（评分≥4星）  
#### 1. 作者：cxy000（5星）  
**关键亮点**  
- 使用 `(x + k - 1) / k` 技巧避免浮点运算，直接计算每个类型的装袋次数。  
- 最终总次数直接通过 `(ans + 1) / 2` 处理上取整，代码简洁高效。  
**核心代码**  
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,x;
    cin>>n>>m;
    long long ans=0;
    for(int i=1;i<=n;i++){
        cin>>x;
        ans+=(x+m-1)/m; // 整数除法上取整
    }
    cout<<(ans+1)/2;    // 总次数除以2上取整
    return 0;
}
```

#### 2. 作者：MZY666（4星）  
**关键亮点**  
- 逻辑清晰，通过奇偶性判断处理总次数的上取整。  
- 代码注释详细，适合初学者理解。  
**核心代码**  
```cpp
for(i=1;i<=n;i++){
    scanf("%lld",&w);
    ans += w/k;         // 基本次数
    if(w%k!=0) ans++;   // 处理余数
}
printf("%lld\n", (ans + 1) / 2); // 奇偶处理简化版
```

#### 3. 作者：力巴尔（4星）  
**关键亮点**  
- 使用三元运算符简化代码，合并余数处理。  
- 通过位运算 `s & 1` 快速判断奇偶性。  
**核心代码**  
```cpp
for (long long i=1;i<=n;i++) {
    scanf("%lld", &a);
    s += (a % k == 0 ? a/k : a/k + 1); // 直接计算装袋次数
}
printf("%lld", s & 1 ? s/2 + 1 : s/2); // 位运算优化奇偶判断
```

---

### 最优思路总结  
**关键技巧**  
1. **整数运算上取整**：对每个类型的装袋次数，使用 `(w + k - 1) / k` 替代 `ceil(w/k)`，避免浮点误差。  
2. **总次数合并优化**：总天数只需将总次数除以2并上取整，无需关心具体装袋顺序。  
**思维模式**：将两个口袋的问题转换为单个口袋的总次数问题，通过数学合并简化计算。

---

### 拓展建议  
**同类题目推荐**  
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心策略排序问题。  
2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：双指针贪心分配。  
3. [P1209 修理牛棚](https://www.luogu.com.cn/problem/P1209)：贪心选择间隔最大位置。  

**调试心得**  
- 避免浮点运算：如 `cqbztz2` 提到的 `ceil` 精度问题，应优先使用整数运算技巧。  
- 奇偶统一处理：总次数可通过 `(ans + 1) / 2` 直接上取整，无需单独判断奇偶。

---
处理用时：62.78秒