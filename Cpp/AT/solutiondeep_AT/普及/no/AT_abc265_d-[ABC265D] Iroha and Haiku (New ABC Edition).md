# 题目信息

# [ABC265D] Iroha and Haiku (New ABC Edition)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc265/tasks/abc265_d

長さ $ N $ の数列 $ A=(A_0,\ldots,A_{N-1}) $ があります。  
次の条件を全て満たす整数の組 $ (x,y,z,w) $ が存在するか判定してください。

- $ 0\ \leq\ x\ <\ y\ <\ z\ <\ w\ \leq\ N $
- $ A_x\ +\ A_{x+1}\ +\ \ldots\ +\ A_{y-1}\ =\ P $
- $ A_y\ +\ A_{y+1}\ +\ \ldots\ +\ A_{z-1}\ =\ Q $
- $ A_z\ +\ A_{z+1}\ +\ \ldots\ +\ A_{w-1}\ =\ R $

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ P,Q,R\ \leq\ 10^{15} $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ (x,y,z,w)=(1,3,6,8) $ が条件を満たします。

## 样例 #1

### 输入

```
10 5 7 5
1 3 2 2 2 3 1 4 3 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
9 100 101 100
31 41 59 26 53 58 97 93 23```

### 输出

```
No```

## 样例 #3

### 输入

```
7 1 1 1
1 1 1 1 1 1 1```

### 输出

```
Yes```

# AI分析结果



# [ABC265D] Iroha and Haiku (新ABC版)

## 题目描述

给定长度为 $N$ 的数列 $A=(A_0,\ldots,A_{N-1})$，判断是否存在满足以下条件的整数四元组 $(x,y,z,w)$：

- $0 \leq x < y < z < w \leq N$
- $\sum_{i=x}^{y-1} A_i = P$
- $\sum_{i=y}^{z-1} A_i = Q$
- $\sum_{i=z}^{w-1} A_i = R$

**算法分类**: 前缀和 + 二分/集合

---

## 精选题解分析

### 题解1（Tooler_Yang） ★★★★☆
**亮点**:  
1. 利用前缀和与集合的O(1)查询特性
2. 将问题转化为前缀和的数学关系式
3. 代码简洁易读，时间复杂度O(nlogn)

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200001], sum;
set<long long> st({0});
int main(){
    long long n,p,q,r;
    cin>>n>>p>>q>>r;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum += a[i];
        st.insert(sum);
    }
    for(auto x:st){
        if(st.find(x+p)!=st.end() 
        && st.find(x+p+q)!=st.end() 
        && st.find(x+p+q+r)!=st.end()){
            cout<<"Yes";
            return 0;
        }
    }
    cout<<"No";
    return 0;
}
```

### 题解2（lsz_） ★★★★
**亮点**:  
1. 强调数据范围需要long long
2. 数学推导清晰，转化为前缀和的三段式验证
3. 代码风格简洁，使用auto遍历集合

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,p,q,r,sum;
set<LL> st;
int main(){
    st.insert(0);
    cin>>n>>p>>q>>r;
    for(int i=1;i<=n;i++){
        LL x; cin>>x;
        sum += x;
        st.insert(sum);
    }
    for(auto a:st){
        if(st.find(a+p)!=st.end() 
        && st.find(a+p+q)!=st.end() 
        && st.find(a+p+q+r)!=st.end()){
            cout<<"Yes"; return 0;
        }
    }
    cout<<"No";
    return 0;
}
```

### 题解3（Exp10re） ★★★★
**亮点**:  
1. 尺取法实现O(n)时间复杂度
2. 分三次预处理每个位置的可行区间
3. 严格数学证明指针移动的正确性

```cpp
void ruler(long long t){ // 尺取法预处理
    long long l=0,r=0,cnt=0;
    for(;l<n;cnt-=a[l++]){
        while(r<=n && cnt<num[t]) cnt+=a[r++];
        if(cnt==num[t]) p[t][l]=r;
        else p[t][l]=-1;
    }
}
// 主函数分三次调用ruler处理PQR
```

---

## 最优思路总结
1. **前缀和核心思想**：将区间和转化为前缀和差值，即 $sum[y]-sum[x]=P$ 的数学关系
2. **集合优化查询**：利用set的O(logn)查询特性，快速验证目标前缀和是否存在
3. **数学关系转换**：验证 $sum_x + P$, $sum_x+P+Q$, $sum_x+P+Q+R$ 是否同时存在
4. **单调性利用**：当数组元素全为正数时，前缀和严格递增，可用二分代替集合查询

---

## 拓展训练
1. **相似类型题**：
   - P1147 连续自然数和（前缀和+数学）
   - P3406 海底高铁（前缀和+差分）
   - P3662 [USACO17FEB]Why Did the Cow Cross the Road II S（滑动窗口）

2. **关键调试经验**：
   - 必须使用long long类型存储前缀和
   - 初始集合要插入sum=0处理左边界
   - 验证顺序要保证x < y < z < w的严格递增关系

3. **算法变式**：
   - 当存在负数元素时，需改用哈希表存储前缀和
   - 若要求输出具体区间而非存在性，可结合二分查找记录坐标
   - 若需求多段区间（超过三段），可扩展为动态规划形式

---
处理用时：54.51秒