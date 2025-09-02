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
各题解均围绕数学推导展开，核心结论为：满足条件的数对必为 2:3 的比例。最优解法通过排序后枚举起始点，利用 map 或二分查找构建等比数列链。关键优化在于快速判断数是否存在及统计出现次数。

### 高星题解推荐
---

#### 1. 作者：Alex_Wei（★★★★★）
**关键亮点**  
- 从数论角度完整推导比例关系，证明严谨  
- 使用 map 实现 O(n log n) 的高效统计  
- 代码简洁，包含重复元素的智能处理  
**核心代码**  
```cpp
map<int,int> mp;
sort(a+1,a+n+1);
for(int i=1;i<=n;i++){
    ll tmp=a[i],cnt=0;
    while(mp[tmp]){
        cnt += tmp*mp[tmp];
        mp[tmp]=0; // 标记已使用
        tmp = (tmp%2==0) ? tmp/2*3 : break;
    }
    ans = max(ans, cnt);
}
```

---

#### 2. 作者：Konnyaku_LXZ（★★★★☆）  
**关键亮点**  
- 分步拆解 gcd/lcm 关系，推导直观  
- 使用排序+二分实现 O(n log n) 的 DP  
- 离散化处理提升效率  
**核心实现**  
```cpp
sort(a+1,a+n+1);
// 离散化去重并统计出现次数
for(int i=1;i<=cnt;i++){
    if(x[i]%3==0){
        int pos = lower_bound(x+1,x+i,x[i]/3*2) - x;
        if(x[pos]==x[i]/3*2) f[i] += f[pos];
    }
    ans = max(ans, f[i]);
}
```

---

### 最优技巧总结
1. **数学推导优先**：将复杂条件转化为比例关系（2:3），大幅简化问题。  
2. **链式结构处理**：通过当前数生成下一项（tmp = tmp/2*3），构建等比链。  
3. **高效存在性判断**：使用排序+二分或 map 实现 O(1) 存在性查询。  

### 拓展与举一反三
- **同类题型**：涉及数论条件转化（如特定比例、余数关系）的极值问题  
- **算法套路**：  
  - 数学建模 → 结构发现 → 贪心/DP 求最优链  
  - 出现次数统计的 map/离散化处理  

### 推荐练习题
1. [P1072 Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)（gcd/lcm 性质应用）  
2. [P2444 病毒](https://www.luogu.com.cn/problem/P2444)（字符串循环节与数论结合）  
3. [CF1349A Orac and LCM](https://codeforces.com/problemset/problem/1349/A)（极值计算与数论推导）  

### 题解中的调试经验
- **lndjy**：通过暴力枚举小数据发现 2:3 规律，强调打表在数论题中的作用。  
- **Rubidium_Chloride**：尝试拓扑排序后发现链式结构特性，提示复杂方法未必最优。  
- **wuyonghuming**：强调边界条件验证（如 tmp%2==0 的判断），避免无限循环。

---
处理用时：73.54秒