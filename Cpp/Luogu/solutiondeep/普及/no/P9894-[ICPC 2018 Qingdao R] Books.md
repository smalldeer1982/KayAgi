# 题目信息

# [ICPC 2018 Qingdao R] Books

## 题目描述

DreamGrid went to the bookshop yesterday. There are $n$ books in the bookshop in total. Because DreamGrid is very rich, he bought the books according to the strategy below:

- Check the $n$ books from the 1st one to the $n$-th one **in order**.
- For each book being checked now, if DreamGrid has enough money (not less than the book price), he'll buy the book and his money will be reduced by the price of the book.
- In case that his money is less than the price of the book being checked now, he will skip that book.


BaoBao is curious about how rich DreamGrid is. You are asked to tell him the maximum possible amount of money DreamGrid took before buying the books, which is a non-negative integer. All he knows are the prices of the $n$ books and the number of books DreamGrid bought in total,  indicated  by $m$. 


## 样例 #1

### 输入

```
4
4 2
1 2 4 8
4 0
100 99 98 97
2 2
10000 10000
5 3
0 0 0 0 1```

### 输出

```
6
96
Richman
Impossible```

# AI分析结果



**算法分类**：贪心

---

### **综合分析**
本题的关键在于贪心策略的选择及边界条件的处理。所有题解核心思路一致：先处理免费书，保证购买数量合法后，前 $m$ 本非零书的总和加上剩余书中最便宜价格减一即为答案。难点在于正确处理 $0$ 元书及边界条件（如 `Impossible` 和 `Richman` 的判断）。

---

### **精选题解**

#### 1. 题解作者：zheng_zx  
**⭐️⭐️⭐️⭐️⭐️**  
**关键亮点**：  
- 代码简洁，利用 `accumulate` 和 `min_element` 简化求和与最小值计算。  
- 边界条件处理清晰（如 `Impossible` 和 `Richman`）。  
**核心代码**：  
```cpp
long long ans = accumulate(a, a + m, 0ll) + *min_element(a + m, a + n) - 1;
```
**代码思想**：移除所有 $0$ 元书后，前 $m$ 本书的总和加上剩余书的最小值减一。

---

#### 2. 题解作者：lidagua1004  
**⭐️⭐️⭐️⭐️**  
**关键亮点**：  
- 显式处理输入中的 $0$ 元书，调整 $n$ 和 $m$ 的值。  
- 逻辑分层明确，注释清晰。  
**核心代码**：  
```cpp
for(int i=1;i<=n;i++){
    cin>>a[i];
    if(!a[i]) i--,n--,m--; // 移除0元书
}
if(m>n||m<0) cout<<"Impossible\n";
else if(n==m) cout<<"Richman\n";
else {
    for(int i=1;i<=m;i++) ans+=a[i]; 
    for(int i=m+1;i<=n;i++) d=min(d,a[i]); 
    cout<<ans+d-1<<"\n";
}
```

---

#### 3. 题解作者：juruo_zhanshen  
**⭐️⭐️⭐️⭐️**  
**关键亮点**：  
- 详细注释解释思路，适合新手理解。  
- 显式遍历剩余书求最小值，避免库函数依赖。  
**个人心得**：  
> 不开 `long long` 见祖宗 —— 强调数据范围的重要性。

---

### **关键思路总结**  
1. **贪心策略**：必须购买所有 $0$ 元书，再按顺序购买足够数量的非零书。  
2. **最大值构造**：总金额为前 $m$ 本非零书总和，加上剩余书中最小价格减一。  
3. **边界处理**：  
   - $0$ 元书数量超过 $m$ → `Impossible`；  
   - 总书数等于 $m$ → `Richman`。  

---

### **拓展与相似题目**  
1. **P1209 [USACO1.3] 修理牛棚 Barn Repair**（贪心选择间隔最大的位置断开）。  
2. **P1090 [NOIP2004 提高组] 合并果子**（贪心选择最小堆合并）。  
3. **P4995 跳跳！**（贪心交替选择最大最小值）。

---
处理用时：49.10秒