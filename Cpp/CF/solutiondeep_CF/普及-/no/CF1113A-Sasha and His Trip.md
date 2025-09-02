# 题目信息

# Sasha and His Trip

## 题目描述

Sasha is a very happy guy, that's why he is always on the move. There are $ n $ cities in the country where Sasha lives. They are all located on one straight line, and for convenience, they are numbered from $ 1 $ to $ n $ in increasing order. The distance between any two adjacent cities is equal to $ 1 $ kilometer. Since all roads in the country are directed, it's possible to reach the city $ y $ from the city $ x $ only if $ x < y $ .

Once Sasha decided to go on a trip around the country and to visit all $ n $ cities. He will move with the help of his car, Cheetah-2677. The tank capacity of this model is $ v $ liters, and it spends exactly $ 1 $ liter of fuel for $ 1 $ kilometer of the way. At the beginning of the journey, the tank is empty. Sasha is located in the city with the number $ 1 $ and wants to get to the city with the number $ n $ . There is a gas station in each city. In the $ i $ -th city, the price of $ 1 $ liter of fuel is $ i $ dollars. It is obvious that at any moment of time, the tank can contain at most $ v $ liters of fuel.

Sasha doesn't like to waste money, that's why he wants to know what is the minimum amount of money is needed to finish the trip if he can buy fuel in any city he wants. Help him to figure it out!

## 说明/提示

In the first example, Sasha can buy $ 2 $ liters for $ 2 $ dollars ( $ 1 $ dollar per liter) in the first city, drive to the second city, spend $ 1 $ liter of fuel on it, then buy $ 1 $ liter for $ 2 $ dollars in the second city and then drive to the $ 4 $ -th city. Therefore, the answer is $ 1+1+2=4 $ .

In the second example, the capacity of the tank allows to fill the tank completely in the first city, and drive to the last city without stops in other cities.

## 样例 #1

### 输入

```
4 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7 6
```

### 输出

```
6
```

# AI分析结果



# Sasha 的旅行

## 题目描述

Sasha 住在一个有 $n$ 个城市组成的一维国家中，城市按升序编号为 $1$ 到 $n$。相邻城市距离为 $1$ 公里。他需要从城市 $1$ 驾车到城市 $n$，油箱容量为 $v$ 升，每公里消耗 $1$ 升油。每个城市 $i$ 的油价为 $i$ 美元/升。求最小花费。

## 算法分类
贪心

## 题解分析与结论

### 题解对比
1. **Velix 的题解（4星）**
   - **关键思路**：将问题拆分为初始加满油与后续等差数列求和。若油量足够全程，直接计算；否则，初始加满后，后续油价构成等差数列。
   - **亮点**：数学公式直接推导，时间复杂度 $O(1)$，代码简洁。
   - **代码**：
     ```cpp
     if(n<=v) cout<<n-1;
     else cout<<v+(n-v+2)*(n-v-1)/2;
     ```

2. **JoseTony 的题解（4星）**
   - **关键思路**：与 Velix 思路一致，强调等差数列的首项与末项推导。
   - **亮点**：清晰说明首项为 2、末项为 $n-v$ 的等差数列。
   - **代码**：
     ```cpp
     cout << v+(2+n-v)*(n-v-1)/2;
     ```

3. **Cult_style 的题解（3星）**
   - **关键思路**：通过遍历城市模拟加油过程，动态维护剩余油量。
   - **亮点**：直观的贪心模拟，适合理解过程。
   - **代码**：
     ```cpp
     for(int i=1;i<=n;i++){
         int t=min(n-i,m);
         ans+=(t-tot)*i;
         tot=t;
         tot--;
     }
     ```

### 最优思路总结
**贪心策略**：在油价递增的条件下，优先在低价城市加满油。若初始油量足够，直接计算；否则，初始加满后，后续油价构成等差数列（首项 2，末项 $n-v$），求和后与初始费用相加。

### 关键代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n,v;
    cin>>n>>v;
    if(n<=v) cout<<n-1;
    else cout<<v+(n-v+2)*(n-v-1)/2;
}
```

### 拓展与心得
- **同类问题**：涉及价格递增条件下的最优购买策略，如[CF1157B]（滑动窗口贪心）。
- **调试心得**：需注意油价递增性与路径不可逆性对贪心策略的影响，数学公式需严格验证边界情况。

## 相似题目推荐
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（贪心）
2. [P1209 [USACO1.3] 修理牛棚 Barn Repair](https://www.luogu.com.cn/problem/P1209)（贪心+区间合并）
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995)（贪心排序）

---
处理用时：449.11秒