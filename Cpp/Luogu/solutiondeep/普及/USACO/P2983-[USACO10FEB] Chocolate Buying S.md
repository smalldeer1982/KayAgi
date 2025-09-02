# 题目信息

# [USACO10FEB] Chocolate Buying S

## 题目描述

Bessie and the herd love chocolate so Farmer John is buying them some.

The Bovine Chocolate Store features $N (1 \le N \le 100,000)$ kinds of chocolate in essentially unlimited quantities.  Each type i of chocolate has price $P_i (1 \le P_i \le 10^{18})$ per piece and there are $C_i (1 \le C_i \le 10^{18})$ cows that want that type of chocolate.

Farmer John has a budget of $B (1 \le B \le 10^{18})$ that he can spend on chocolates for the cows. What is the maximum number of cows that he can satisfy?  All cows only want one type of chocolate, and will be satisfied only by that type.

Consider an example where FJ has $50$ to spend on $5$ different types of chocolate. A total of eleven cows have various chocolate preferences:

|Chocolate\_Type|Per\_Chocolate\_Cost|Cows\_preferring\_this\_type| 
|:-----------:|:-----------:|:-----------:|
|$1$|$5$|$3$|
|$2$|$1$|$1$|
|$3$|$10$|$4$|
|$4$|$7$|$2$|
|$5$|$60$|$1$|

Obviously, FJ can't purchase chocolate type $5$, since he doesn't have enough money. Even if it cost only $50$, it's a counterproductive purchase since only one cow would be satisfied.

Looking at the chocolates start at the less expensive ones, he can purchase $1$ chocolate of type $2$ for $1 \times 1$ leaving $50-1=49$, then purchase $3$ chocolate of type $1$ for $3 \times 5$ leaving $49-15=34$, then  purchase $2$ chocolate of type $4$ for $2 \times 7$ leaving $34-14=20$, then  purchase $2$ chocolate of type $3$ for $2 \times 10$ leaving $20-20=0$.

He would thus satisfy $1 + 3 + 2 + 2 = 8$ cows. 

## 样例 #1

### 输入

```
5 50 
5 3 
1 1 
10 4 
7 2 
60 1 
```

### 输出

```
8 
```

# AI分析结果



### 综合分析与结论
本题考察贪心算法，核心思路是将巧克力按价格升序排列，优先购买便宜的以满足更多奶牛。所有题解均采用此策略，区别在于数据结构的实现方式及代码优化。需特别注意处理大数时选择合适的数据类型（如unsigned long long）。

---

### 高分题解推荐

#### 1. 作者：K0stlin ⭐⭐⭐⭐
**关键亮点**  
- 结构体排序实现简洁，逻辑清晰  
- 正确使用`unsigned long long`处理大数  
- 循环中直接处理全购/部分购场景，时间复杂度O(n)

**核心代码**  
```cpp
sort(a+1,a+n+1,cmp);
for(int i=1;i<=n;i++){
    if(v>a[i].p*a[i].c){
        v -= a[i].p*a[i].c;
        ans += a[i].c;
    } else {
        ans += v/a[i].p;
        break;
    }
}
```

#### 2. 作者：llzzxx712 ⭐⭐⭐⭐  
**关键亮点**  
- 注释详尽，适合初学者理解  
- 明确解释排序后直接break的合理性  
- 代码变量命名直观（如c[i].p表示价格）

**个人心得引用**  
> "由于剩下的钱不够买这种巧克力了，而下次循环中的巧克力更贵，所以可以直接跳出循环"

#### 3. 作者：wisdom_grass ⭐⭐⭐⭐  
**关键亮点**  
- 使用`vector<pair>`简化数据结构  
- 强调标签误导问题（原题标为DP实为贪心）  
- 代码中直接判断剩余钱能否覆盖当前类型  

**调试教训**  
> "初学dp的我被标签误导，实际是贪心题。一定要自己分析问题本质！"

---

### 关键思路总结
1. **贪心策略**：按价格升序处理巧克力，确保每次选择当前最优解。  
2. **数据类型**：所有涉及金额和数量的变量必须使用`long long`或`unsigned long long`。  
3. **终止条件**：当剩余预算不足以全购当前类型时，`ans += b/p`后直接跳出循环（后续类型价格更高）。  

---

### 拓展与同类题目推荐
**类似题目推荐**  
1. [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)  
   - 同样采用价格排序贪心策略  
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
   - 优先队列实现贪心最优合并  
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995)  
   - 极值交替选择策略的贪心应用  

**思维拓展**  
当问题中出现"在有限资源下最大化/最小化目标"时，优先考虑贪心或动态规划。若数值范围极大（如1e18），通常排除DP，转而寻找贪心或数学规律。

---
处理用时：51.19秒