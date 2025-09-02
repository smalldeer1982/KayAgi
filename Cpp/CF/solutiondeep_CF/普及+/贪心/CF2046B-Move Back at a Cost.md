# 题目信息

# Move Back at a Cost

## 题目描述

You are given an array of integers $ a $ of length $ n $ . You can perform the following operation zero or more times:

- In one operation choose an index $ i $ ( $ 1 \le i \le n $ ), assign $ a_i := a_i + 1 $ , and then move $ a_i $ to the back of the array (to the rightmost position). For example, if $ a = [3, 5, 1, 9] $ , and you choose $ i = 2 $ , the array becomes $ [3, 1, 9, 6] $ .

Find the lexicographically smallest $ ^{\text{∗}} $ array you can get by performing these operations.

 $ ^{\text{∗}} $ An array $ c $ is lexicographically smaller than an array $ d $ if and only if one of the following holds:

- $ c $ is a prefix of $ d $ , but $ c \ne d $ ; or
- in the first position where $ c $ and $ d $ differ, the array $ c $ has a smaller element than the corresponding element in $ d $ .

## 样例 #1

### 输入

```
3
3
2 1 3
5
1 2 2 1 4
6
1 2 3 6 5 4```

### 输出

```
1 3 3 
1 1 3 3 5 
1 2 3 4 6 7```

# AI分析结果



# Move Back at a Cost

## 题目描述

给定一个长度为 $n$ 的整数数组 $a$，你可以执行以下操作零次或多次：

- 选择一个下标 $i$（$1 \le i \le n$），将 $a_i$ 的值增加 $1$，然后将 $a_i$ 移动到数组的末尾（最右侧）。例如，若 $a = [3, 5, 1, 9]$ 且选择 $i = 2$，数组将变为 $[3, 1, 9, 6]$。

要求通过执行这些操作，得到字典序最小的数组。

**字典序定义**：数组 $c$ 字典序小于数组 $d$ 当且仅当满足以下任一条件：
1. $c$ 是 $d$ 的前缀且 $c \ne d$；
2. 在第一个不同的位置，$c$ 的元素小于 $d$ 的对应元素。

---

## 题解分析与结论

### 题解关键思路总结
1. **操作特性分析**：每个元素最多被操作一次（操作后移至末尾，无法再次影响前段）
2. **A数判定原则**：若元素后方存在更小值则必须操作（称为A数或特征数）
3. **分阶段处理**：
   - 第一轮处理所有原始数组中需要操作的数
   - 第二轮处理因第一轮操作产生的新候选数
4. **排序优化**：所有被操作的数最终需按升序排列在数组末尾
5. **后缀最小值维护**：通过反向遍历快速判定需要操作的元素

### 最优解法核心技巧
1. **两轮扫描法**：
   - 第一轮逆向扫描标记所有后面有更小值的元素
   - 第二轮基于第一轮结果的最小值再次筛选
2. **标记分离+排序**：将操作数与非操作数分离处理，最终合并排序
3. **空间换时间**：使用辅助数组标记操作状态，避免实际移动元素

### 推荐题解

#### 1. hgcnxn（⭐⭐⭐⭐⭐）
**关键亮点**：
- 清晰的两轮扫描策略
- 使用标记数组分离处理逻辑
- O(n) 预处理 + O(n) 后处理的线性复杂度
```cpp
for(int i=n-1;i>=0;i--){
    if(mn>a[i]) mn=a[i];
    if(a[i]>mn) { // 第一轮标记
        a[i]++;
        f[i]=1;
        mnn=min(mnn,a[i]);
    }
}
for(int i=n-1;i>=0;i--) // 第二轮处理
    if(f[i]==0 && a[i]>mnn) a[i]++;
sort(a,a+n); // 最终排序
```

#### 2. OrinLoong（⭐⭐⭐⭐）
**创新点**：
- 递归式分段处理思想
- 优先队列维护操作数集合
- 后缀最小值数组优化判断
```cpp
smn[N] = N; // 预处理后缀最小值下标
for(int i=N-1;i>=1;i--)
    smn[i] = (a[i]<=a[smn[i+1]] ? i : smn[i+1]);
while(l<=N){
    p=smn[l]; // 当前段最小值位置
    for(int i=l;i<p;i++) pq.push(a[i]+1); // 前段元素入队
    if(!pq.empty() && pq.top()<a[p]) pq.push(a[p]+1);
    else q.push(a[p]); // 保留最小值
    l=p+1;
}
```

#### 3. 201012280925LSY（⭐⭐⭐⭐）
**独特思路**：
- 双优先队列动态维护候选集
- 实时比较未操作段最小值与已操作数
- 渐进式构建最终序列
```cpp
while(!dq.empty() || l<=n){
    if(dq.empty() || back_min[l] <= dq.top().s){
        cout << back_min[l] << " ";
        for(int j=l;j<min_pos;j++) dq.push(a[j]+1);
        l = min_pos + 1;
    } else {
        cout << dq.top().s << " ";
        dq.pop();
    }
}
```

---

## 拓展应用

### 类似题目套路
1. **后缀极值应用**：常用于需要后方元素信息决策的场景
2. **动态候选集维护**：优先队列处理不断变化的候选元素
3. **分段处理策略**：将数组划分为多个决策段分别处理

### 推荐练习题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)  
   （贪心策略与字典序维护）
2. [P2870 [USACO07DEC] Best Cow Line G](https://www.luogu.com.cn/problem/P2870)  
   （双向指针+字典序决策）
3. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)  
   （优先队列维护操作候选集）

---

## 调试心得摘录
1. **边界处理**：多位题解作者强调要特别注意数组末尾和空队列的特殊情况
2. **操作顺序陷阱**：实际无需关心具体操作顺序，只需保证最终操作数排序正确
3. **数值更新时机**：在逆向遍历时及时更新最小值，避免使用过时数据判断
4. **空间优化**：通过标记数组而非实际移动元素，大幅降低实现复杂度

---
处理用时：63.01秒