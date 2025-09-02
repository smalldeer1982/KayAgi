# 题目信息

# [USACO07MAR] Face The Right Way G

## 题目描述

Farmer John has arranged his N (1 ≤ N ≤ 5,000) cows in a row and many of them are facing forward, like good cows. Some of them are facing backward, though, and he needs them all to face forward to make his life perfect.

Fortunately, FJ recently bought an automatic cow turning machine. Since he purchased the discount model, it must be irrevocably preset to turn K (1 ≤ K ≤ N) cows at once, and it can only turn cows that are all standing next to each other in line. Each time the machine is used, it reverses the facing direction of a contiguous group of K cows in the line (one cannot use it on fewer than K cows, e.g., at the either end of the line of cows). Each cow remains in the same \*location\* as before, but ends up facing the \*opposite direction\*. A cow that starts out facing forward will be turned backward by the machine and vice-versa.

Because FJ must pick a single, never-changing value of K, please help him determine the minimum value of K that minimizes the number of operations required by the machine to make all the cows face forward. Also determine M, the minimum number of machine operations required to get all the cows facing forward using that value of K.

$N$ 头牛排成一列 $1 \le N \le 5000$。每头牛或者向前或者向后。为了让所有牛都面向前方，农夫每次可以将 $K$ 头连续的牛转向 $1 \le K \le N$，求使操作次数最小的相应 $K$ 和最小的操作次数 $M$。$F$ 为朝前，$B$ 为朝后。

请在一行输出两个数字 $K$ 和 $M$，用空格分开。

## 说明/提示

For K = 3, the machine must be operated three times: turn cows (1,2,3), (3,4,5), and finally (5,6,7)


## 样例 #1

### 输入

```
7
B
B
F
B
F
B
B```

### 输出

```
3 3```

# AI分析结果



### 综合分析与结论  
该题核心在于通过贪心策略确定最小翻转次数，并利用差分优化将复杂度从 O(n³) 降为 O(n²)。所有题解均基于以下两点：  
1. **贪心策略**：从左到右遍历，遇到反向牛立即翻转后续区间。  
2. **差分优化**：用标记或差分数组记录翻转状态，避免暴力修改区间。  

最优解法需枚举 K (1≤K≤N)，对每个 K 使用差分模拟翻转过程，记录合法 K 对应的最小操作次数。  

---

### 高星题解推荐 (≥4星)  

#### 1. 作者：Delva (⭐️⭐️⭐️⭐️⭐️)  
**关键亮点**：  
- 使用差分数组 `B[]` 记录翻转区间端点，结合异或操作高效维护当前状态。  
- 代码简洁，逻辑清晰，通过 `b ^= B[i]` 动态更新翻转状态。  
- 明确处理边界条件（翻转区间超出末尾则跳过）。  

**核心代码**：  
```cpp  
for(int i=1;i<=n;++i){
    b ^= B[i]; // 动态更新当前翻转状态
    if(!(A[i]^b)){ // 当前牛需要翻转
        if(i+len-1>n) break;
        b ^= 1, B[i+len]^=1; // 差分标记
        ++cnt;
    }
}  
```  

---

#### 2. 作者：llzzxx712 (⭐️⭐️⭐️⭐️)  
**关键亮点**：  
- 引入 `now` 变量表示当前是否处于翻转状态，结合差分数组 `cha[]` 快速判断。  
- 详细注释说明每一步逻辑，代码可读性极强。  
- 正确处理末尾检查，确保剩余牛全部朝前。  

**核心代码**：  
```cpp  
for(int i=1;i<=n;i++){
    now ^= cha[i]; // 当前翻转状态
    if(a[i]^now == 0){ // 需要翻转
        if(i+k-1>n) return INF;
        now ^= 1, cha[i+k]^=1; // 差分标记
        cnt++;
    }
}  
```  

---

#### 3. 作者：Jerrycyx (⭐️⭐️⭐️⭐️)  
**关键亮点**：  
- 使用队列维护有效翻转起点，避免重复计算。  
- 结合 `bitset` 快速处理序列，代码简洁高效。  
- 动态弹出无效起点，确保队列仅覆盖当前点。  

**核心代码**：  
```cpp  
queue<int> q;
for(int i=1;i<=n;i++){
    while(!q.empty() && q.front()<i-k+1) q.pop();
    if(q.size()&1) t.flip(i); // 奇数次翻转则取反
    if(t[i] && i+k-1<=n){
        q.push(i); // 记录新翻转起点
        t.flip(i); // 调整当前状态
        m++;
    }
}  
```  

---

### 最优关键思路与技巧  
1. **差分数组标记法**：  
   - 用差分数组记录翻转区间的起点和终点，通过异或操作动态维护当前状态。  
   - 每次翻转只需修改区间两端点，复杂度 O(1)。  
2. **贪心策略的正确性**：  
   - 每个反向牛必须且仅需翻转一次，后续操作不影响已处理部分。  

---

### 类似题目推荐  
1. **P1965 [NOIP2013 提高组] 转圈游戏**（枚举与模运算优化）  
2. **P1982 [NOIP2013 普及组] 小朋友的数字**（贪心与动态规划）  
3. **P3406 海底高铁**（差分数组应用与路径优化）  

---

### 个人心得摘录  
1. **边界条件处理**（FallR）：  
   > "因为末尾不足 K 的检查遗漏导致 90 分，调试一小时后发现需严格判断 `i+k-1 ≤n`。"  
   **总结**：翻转区间终点必须明确限制，否则会漏判无解情况。  

2. **输出顺序注意**（pikabi）：  
   > "样例输出 3 3 易误导，实际应先输出 K 再输出 M。"  
   **总结**：仔细验证输出格式，避免低级错误。  

3. **调试技巧**（MrMorning）：  
   > "使用 `memcpy` 复制原数组进行模拟，避免直接修改影响后续枚举。"  
   **总结**：临时副本操作是处理多组枚举的有效手段。

---
处理用时：69.91秒