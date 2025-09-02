# 题目信息

# Jamie and Binary Sequence (changed after round)

## 题目描述

Jamie is preparing a Codeforces round. He has got an idea for a problem, but does not know how to solve it. Help him write a solution to the following problem:

Find $ k $ integers such that the sum of two to the power of each number equals to the number $ n $ and the largest integer in the answer is as small as possible. As there may be multiple answers, you are asked to output the lexicographically largest one.

To be more clear, consider all integer sequence with length $ k $ $ (a_{1},a_{2},...,a_{k}) $ with ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/804a330680fa0a689680c55396d7d651c977b163.png). Give a value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/3a6d52e5a86468620a5b59c3452f1e46ca1a5ee4.png) to each sequence. Among all sequence(s) that have the minimum $ y $ value, output the one that is the lexicographically largest.

For definitions of powers and lexicographical order see notes.


## 说明/提示

Sample 1:

 $ 2^{3}+2^{3}+2^{2}+2^{1}+2^{0}=8+8+4+2+1=23 $

Answers like $ (3,3,2,0,1) $ or $ (0,1,2,3,3) $ are not lexicographically largest.

Answers like $ (4,1,1,1,0) $ do not have the minimum $ y $ value.

Sample 2:

It can be shown there does not exist a sequence with length 2.

Sample 3:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/32c976228a27c0f708bbb18d0f890775f96c4e59.png)

Powers of 2:

If $ x>0 $ , then $ 2^{x}=2·2·2·...·2 $ ( $ x $ times).

If $ x=0 $ , then $ 2^{x}=1 $ .

If $ x<0 $ , then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/6fdb1f744a78ad201a27505654584044743d34f7.png).

Lexicographical order:

Given two different sequences of the same length, $ (a_{1},a_{2},...\ ,a_{k}) $ and $ (b_{1},b_{2},...\ ,b_{k}) $ , the first one is smaller than the second one for the lexicographical order, if and only if $ a_{i}<b_{i} $ , for the first $ i $ where $ a_{i} $ and $ b_{i} $ differ.

## 样例 #1

### 输入

```
23 5
```

### 输出

```
Yes
3 3 2 1 0 
```

## 样例 #2

### 输入

```
13 2
```

### 输出

```
No
```

## 样例 #3

### 输入

```
1 2
```

### 输出

```
Yes
-1 -1 
```

# AI分析结果



---

### **算法分类**
贪心与构造

---

### **题解思路与核心难点**

**题目核心**：将n拆分为k个2的幂次项之和，使得最大幂次尽可能小，同时字典序最大。

**关键步骤与难点**：
1. **确定最小最大幂次y**：  
   - 所有高于y的幂次项必须拆分为多个y的项。例如，2^4需拆为2^3+2^3，再继续拆到y的层级。
   - 枚举可能的y值（含负数），检查拆分后总项数是否≤k。
   - **难点**：正确处理负数拆分的溢出问题（如拆2^0为两个2^-1时，需计算2^(j-y)是否超出k的限制）。

2. **填充至k项并保证字典序最大**：  
   - 拆分后的项数可能不足k，此时需从最小的项开始拆（如末尾项），每次拆为两个更小的项，确保前面的项尽可能大，维护字典序。

---

### **最优题解评分与亮点**

1. **CarroT1212（5星）**  
   - **思路清晰**：枚举可能的y，直接构造答案数组。
   - **代码简洁**：用vector动态调整项数，拆分末尾项。
   - **边界处理**：正确处理负数拆分，如样例3的-1项。
   - **关键代码**：
     ```cpp
     while (ans.size() < k) {
         ll x = ans.back();
         ans.pop_back();
         ans.pb(x-1); ans.pb(x-1);
     }
     ```

2. **Liuhy2996（4星）**  
   - **双优先队列**：先用优先队列确定最小y，再处理字典序。
   - **动态调整**：优先队列维护最大项，拆分时转向最小项。
   - **亮点**：通过两次队列操作分离最大值与字典序处理。

3. **JimmyLee（4星）**  
   - **Set维护顺序**：利用有序集合确保拆分时的字典序。
   - **直接构造**：先拆最大项到最小y，再处理剩余项。

---

### **核心算法流程可视化**

**动画设计**：  
1. **初始分解**：将n的二进制位映射为初始项（如23→[3,2,1,0]）。  
2. **拆分高位**：将高位项（如3）拆为多个目标y项（如3→两个3）。  
3. **填充末尾**：若项数不足k，持续拆分末尾项（如0→-1,-1）。  
4. **颜色标记**：  
   - **红色**：当前正在拆分的项。  
   - **绿色**：已确定的最大y项。  
   - **蓝色**：正在调整的末尾项。  

**复古像素风格**：  
- **8位网格**：每个项显示为方块，高度表示幂次大小。  
- **音效**：拆分时播放“分解”音效，完成时播放胜利音效。  
- **自动演示**：按步长自动拆分，用户可暂停观察。

---

### **代码实现（关键片段）**

```cpp
// CarroT1212的题解核心代码
vector<ll> nn;
for (ll i=61; ~i; i--) 
    if (n >> i & 1) nn.pb(i);  // 二进制分解

for (ll y=-61; y<=61; y++) {
    vector<ll> ans;
    for (ll j : nn) {
        if (j > y) {
            // 拆分高位项为多个y项
            ll cnt = 1LL << (j - y);
            ans.insert(ans.end(), cnt, y);
        } else ans.pb(j);
    }
    // 填充至k项
    while (ans.size() < k) {
        ll x = ans.back();
        ans.pop_back();
        ans.pb(x-1); ans.pb(x-1);
    }
    if (ans.size() == k) {
        printf("Yes\n");
        for (ll i : ans) printf("%lld ", i);
        return 0;
    }
}
```

---

### **同类型题目推荐**
1. **P2325 [SCOI2005] 王室联邦**（树分块构造）  
2. **P2114 [NOI2014] 起床困难综合症**（位运算贪心）  
3. **P5655 基础数据结构练习题**（构造与贪心结合）

---

### **个人心得**
- **负指数处理**：拆解时需注意2^x的定义，如2^-1=1/2，但构造时只需保持总和不变。  
- **字典序陷阱**：若先拆分高位项，可能导致字典序变小，必须从末尾拆分。

---
处理用时：111.85秒