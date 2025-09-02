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

这些题解的核心思路都是**贪心算法**，通过将巧克力按价格从小到大排序，优先购买价格较低的巧克力，以最大化满足的奶牛数量。所有题解都强调了**数据范围**的问题，建议使用 `unsigned long long` 或 `long long` 类型来避免溢出。

尽管题解思路相似，但在代码实现、注释清晰度、以及细节处理上存在差异。部分题解提供了详细的注释和调试经验，有助于初学者理解。

### 所选高质量题解

#### 1. 作者：K0stlin (赞：21)  
**星级：★★★★★**  
**关键亮点：**  
- 代码简洁，结构清晰，使用 `unsigned long long` 处理大数。
- 提供了结构体排序的必要性说明，适合初学者理解。
- 通过简单的 `if-else` 逻辑实现了贪心策略，代码可读性强。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    if(v>a[i].p*a[i].c){v=v-a[i].p*a[i].c;ans+=a[i].c;}
    else{ans+=v/a[i].p;break;}
}
```
**实现思想：**  
优先购买价格较低的巧克力，若预算充足则全部购买，否则尽可能多地购买。

#### 2. 作者：llzzxx712 (赞：9)  
**星级：★★★★☆**  
**关键亮点：**  
- 注释详细，解释了每一步的逻辑，适合初学者。
- 使用了 `unsigned long long` 处理大数，并强调了数据范围的重要性。
- 通过 `continue` 和 `break` 优化了循环逻辑。

**核心代码：**
```cpp
if(b>c[i].c*c[i].p){
    ans+=c[i].c;
    b-=c[i].c*c[i].p;
    continue;
}
else{
    ans+=b/c[i].p;
    break;
}
```
**实现思想：**  
优先购买价格较低的巧克力，若预算充足则全部购买，否则尽可能多地购买。

#### 3. 作者：wisdom_grass (赞：5)  
**星级：★★★★☆**  
**关键亮点：**  
- 使用 `vector` 和 `pair` 简化了数据结构，代码更具现代感。
- 提供了对贪心算法的详细解释，帮助理解其正确性。
- 强调了数据范围的重要性，并提供了调试经验。

**核心代码：**
```cpp
if(b / a[i].first < a[i].second) {
    ans += b / a[i].first;
    break;
}
ans += a[i].second;
b -= a[i].first * a[i].second;
```
**实现思想：**  
优先购买价格较低的巧克力，若预算充足则全部购买，否则尽可能多地购买。

### 最优关键思路与技巧

1. **贪心策略**：优先购买价格较低的巧克力，以最大化满足的奶牛数量。
2. **数据范围处理**：使用 `unsigned long long` 或 `long long` 避免溢出。
3. **排序优化**：通过结构体或 `pair` 对巧克力按价格排序，简化贪心实现。

### 拓展思路与类似题目

1. **类似题目**：
   - [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)
   - [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)
   - [P2240 [NOIP2014 提高组] 飞扬的小鸟](https://www.luogu.com.cn/problem/P2240)

2. **拓展思路**：
   - 类似贪心问题可以扩展到其他资源分配场景，如任务调度、背包问题等。
   - 对于大数据范围问题，始终要注意数据类型的选取，避免溢出。

### 个人心得总结

- **调试经验**：多位作者提到因未使用 `long long` 而导致的溢出问题，强调了数据范围的重要性。
- **标签误导**：部分作者提到标签误导为动态规划，实际为贪心问题，提醒不要盲目相信标签。
- **代码优化**：通过 `continue` 和 `break` 优化循环逻辑，减少不必要的计算。

---
处理用时：35.75秒