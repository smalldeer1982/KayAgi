# 题目信息

# 「SWTR-6」GCDs & LCMs

## 题目描述

小 A 有一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$。

他想从这些数中选出一些数 $b_1,b_2,\cdots,b_k$ 满足：对于所有 $i\ (1\leq i\leq k)$，$b_i$ 要么是序列 $b$ 中的最大值，要么存在一个位置 $j$ 使得 $b_j>b_i$ 且 $b_i+b_j+\gcd(b_i,b_j)=\mathrm{lcm}(b_i,b_j)$。

- 如果你不知道 $\gcd$ 和 $\mathrm{lcm}$ 是什么，可以点击最底部的「帮助/提示」部分的链接。

小 A 想让选出的数之和尽量大。请求出这个最大值。

## 说明/提示

**「样例 1 说明」**

可以选择 $b=\{2,3\}$，因为 $2+3+\gcd(2,3)=\mathrm{lcm}(2,3)$。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask 1（5 points）：$n\leq2$；
- Subtask 2（20 points）：$n\leq 17$；
- Subtask 3（15 points）：$a_i\leq 2\times 10^3$；
- Subtask 4（15 points）：$n\leq 2\times 10^3$；
- Subtask 5（10 points）：$n\leq 5\times 10^4$；
- Subtask 6（10 points）：$a_i\leq 10^7$；
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^5$，$1\leq a_i\leq 10^9$。

**「帮助/提示」**

$\gcd$ 表示[最大公约数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fr=aladdin)，$\mathrm{lcm}$ 表示[最小公倍数](https://baike.baidu.com/item/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B0/6192375?fr=aladdin)。

**「来源」**

[【LGR-075】洛谷 8 月月赛 II Div.2 & SWTR-06 & EZEC Round 3](https://www.luogu.com.cn/contest/33190)。

idea & solution & data by [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
4
4 3 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
10
6 7 18 4 17 10 9 1 3 8```

### 输出

```
19```

## 样例 #3

### 输入

```
3
123456789 234567890 123456789```

### 输出

```
246913578```

# AI分析结果



### 综合分析与结论
该题核心在于通过数学推导得出等比数列关系，将问题转化为寻找最大权重的等比链。各题解均围绕以下关键点展开：
1. **数学推导**：通过设定gcd/lcm关系，推导出合法数对满足2:3比例
2. **结构建模**：将合法序列建模为公比3/2的等比数列
3. **实现优化**：通过排序+二分/map统计出现次数，避免暴力枚举

### 高星题解精选（评分≥4★）

#### 1. Alex_Wei（5★）
**核心亮点**：
- 官方题解，推导过程最严谨
- 提供多子任务解法思路
- 代码简洁高效（map统计+链式跳跃）
**关键代码**：
```cpp
for(int i=1;i<=n;i++){
    ll tmp=a[i],cnt=0;
    while(mp[tmp]){ // 链式跳跃统计
        cnt += tmp*mp[tmp];
        mp[tmp]=0; // 标记已访问
        tmp = (tmp%2==0) ? tmp/2*3 : -1;
    }
    ans=max(ans,cnt);
}
```
**实现思想**：将数组排序后，从每个元素出发沿2:3链累加值，同时清空已访问元素避免重复计算

#### 2. Konnyaku_LXZ（4.5★）
**核心亮点**：
- 独立推导过程清晰易懂
- 使用结构体存储离散化后的数值和出现次数
- 二分查找实现高效递推
**关键代码**：
```cpp
for(int i=1; i<=cnt; i++){
    if(x[i]%3 != 0) continue;
    int val = x[i]/3*2;
    int pos = lower_bound(x+1, x+cnt+1, val) - x;
    if(x[pos] == val) f[i] += f[pos];
}
```
**实现思想**：离散化后建立DP数组，通过二分查找前驱节点进行状态转移

#### 3. Rubidium_Chloride（4★）
**核心亮点**：
- 提供数学推导的完整代数过程
- 引入拓扑排序思路处理依赖关系
- 使用并查集维护连通块
**个人心得**：
> "考时口胡，考后证明" 体现了竞赛中先猜想后验证的实用策略  
> "注意处理重复元素需合并统计" 强调离散化的重要性

### 关键思路总结
1. **数学建模**：将数论条件转化为等比数列关系
2. **离散化优化**：通过排序+二分/map处理大数据范围
3. **链式处理**：沿比例链跳跃统计，时间复杂度O(n log a)
4. **状态复用**：标记已访问元素避免重复计算

### 拓展练习
1. [P1895 数字序列](https://www.luogu.com.cn/problem/P1895) - 数列构造与数学规律
2. [P2447 外星千足虫](https://www.luogu.com.cn/problem/P2447) - 异或方程组与位运算
3. [P2921  Trick or Treat on the Farm](https://www.luogu.com.cn/problem/P2921) - 图论中的环处理与记忆化

### 核心代码片段
Alex_Wei的map实现（完整核心逻辑）：
```cpp
#include <bits/stdc++.h>
using namespace std;

map<int,int> mp;
int n, a[300005];
long long ans;

int main() {
    cin >> n;
    for(int i=1; i<=n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    sort(a+1, a+n+1);
    
    for(int i=1; i<=n; i++) {
        long long sum = 0;
        int val = a[i];
        while(mp.count(val) && mp[val] > 0) {
            sum += 1LL * val * mp[val];
            mp.erase(val); // 防止重复访问
            if(val % 2 == 0) 
                val = val / 2 * 3;
            else 
                break;
        }
        ans = max(ans, sum);
    }
    cout << ans;
    return 0;
}
```

---
处理用时：57.90秒