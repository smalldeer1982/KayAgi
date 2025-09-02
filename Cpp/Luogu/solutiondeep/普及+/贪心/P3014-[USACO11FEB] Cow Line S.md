# 题目信息

# [USACO11FEB] Cow Line S

## 题目描述

The N (1 <= N <= 20) cows conveniently numbered 1...N are playing yet another one of their crazy games with Farmer John. The cows will arrange themselves in a line and ask Farmer John what their line number is. In return, Farmer John can give them a line number and the cows must rearrange themselves into that line.

A line number is assigned by numbering all the permutations of the line in lexicographic order.

Consider this example:

Farmer John has 5 cows and gives them the line number of 3.

The permutations of the line in ascending lexicographic order: 1st: 1 2 3 4 5

2nd: 1 2 3 5 4

3rd: 1 2 4 3 5

Therefore, the cows will line themselves in the cow line 1 2 4 3 5.

The cows, in return, line themselves in the configuration '1 2 5 3 4' and ask Farmer John what their line number is.

Continuing with the list:

4th : 1 2 4 5 3

5th : 1 2 5 3 4

Farmer John can see the answer here is 5

Farmer John and the cows would like your help to play their game. They have K (1 <= K <= 10,000) queries that they need help with. Query i has two parts: C\_i will be the command, which is either 'P' or 'Q'.

If C\_i is 'P', then the second part of the query will be one integer A\_i (1 <= A\_i <= N!), which is a line number. This is Farmer John challenging the cows to line up in the correct cow line.

If C\_i is 'Q', then the second part of the query will be N distinct integers B\_ij (1 <= B\_ij <= N). This will denote a cow line. These are the cows challenging Farmer John to find their line number.



## 样例 #1

### 输入

```
5 2 
P 
3 
Q 
1 2 5 3 4 
```

### 输出

```
1 2 4 3 5 
5 
```

# AI分析结果



### 综合分析与结论
本题考察康托展开及其逆运算的应用，所有题解均围绕这一核心展开。各解法差异主要体现在优化手段（树状数组优化未用数字查询）、代码结构设计（阶乘预处理方式）以及实现细节处理（序号偏移量的处理）。最优解法需兼顾时间复杂度优化与代码可读性。

---

### 精选高星题解

#### 1. 作者：YoungNeal（★★★★★）
**关键亮点**：  
- 代码最简洁，双函数分别实现康托展开与逆展开，逻辑清晰  
- 预处理阶乘数组减少重复计算  
- 使用标记数组维护可用数字，实现直观易懂  
**核心代码**：
```cpp
int contor(int x[]){ // 康托展开
    int p=0;
    for(int i=1;i<=n;i++){
        int t=0;
        for(int j=i+1;j<=n;j++) t += (x[i]>x[j]);
        p += t*fac[n-i];
    }
    return p+1; // 注意+1偏移
}

void reverse_contor(int x){ // 逆康托展开
    x--;
    for(int i=1;i<=n;i++){
        int t=x/fac[n-i];
        for(j=1;j<=n && (vis[j] || t);j++) 
            if(!vis[j]) t--;
        vis[j]=1;
        printf("%d ",j);
        x %= fac[n-i];
    }
}
```

#### 2. 作者：Honeta（★★★★☆）
**关键亮点**：  
- 使用树状数组优化康托展开的查询效率，时间复杂度降至O(n log n)  
- 通过add/ask操作动态维护可用数字集合，适合更大规模数据  
**核心优化点**：
```cpp
void add(ll x,ll y){ // 树状数组更新
    for(;x<=n;x+=x&-x)tree[x]+=y;
}
ll ask(ll x){ // 查询前缀和
    ll res=0;
    for(;x;x-=x&-x)res+=tree[x];
    return res;
}

// 康托展开时计算每位贡献
add(t2,-1); // 划掉当前数字
ans += ask(t2)*fact[n-i];
```

#### 3. 作者：Rainybunny（★★★★☆）
**关键亮点**：  
- 提供完整的数学证明，深入剖析康托展开原理  
- 使用vector动态维护可用数字集合，空间利用率高  
**独特技巧**：
```cpp
vector<int> ReCantor(LL k) {
    vector<int> v, ret;
    for(int i=1;i<=n;i++) v.push_back(i);
    for(int i=n;i>=1;i--) {
        LL r = k%FAC[i-1], t = k/FAC[i-1];
        sort(v.begin(),v.end());
        ret.push_back(v[t]); // 直接取第t小元素
        v.erase(v.begin()+t);
        k = r;
    }
    return ret;
}
```

---

### 最优技巧总结
1. **阶乘预处理**：提前计算并存储阶乘值避免重复计算  
2. **动态维护可用数字**：  
   - 标记数组（O(n)遍历）适合n≤20的小规模数据  
   - 树状数组（O(log n)查询）优化时间效率  
   - vector动态删除（O(n)排序）平衡实现难度  
3. **序号偏移处理**：康托展开结果需+1，逆展开前需-1  
4. **逆展开位分解**：通过阶乘除法确定每个位置的数字选择  

---

### 拓展练习推荐
1. **P1088 火星人**（康托展开应用）  
2. **P1379 八数码难题**（康托展开用于状态压缩）  
3. **P2529 [SHOI2001] 击鼓传花**（逆康托展开变形）

---

### 题解中的智慧闪光
- **调试经验**：多位作者强调序号±1的处理（如YoungNeal在contor返回时+1）  
- **优化心得**：Honeta提到树状数组相比暴力遍历的显著效率提升  
- **思维顿悟**：Rainybunny通过数学归纳法证明康托展开的正确性，深化理解  
- **实现技巧**：多题解使用memset初始化标记数组，保证每组查询的独立性

---
处理用时：62.46秒