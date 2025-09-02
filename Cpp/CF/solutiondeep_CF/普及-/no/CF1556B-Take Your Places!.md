# 题目信息

# Take Your Places!

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556B/1e01fe272756235c22745e77349edf5747f912ab.png)William has an array of $ n $ integers $ a_1, a_2, \dots, a_n $ . In one move he can swap two neighboring items. Two items $ a_i $ and $ a_j $ are considered neighboring if the condition $ |i - j| = 1 $ is satisfied.

William wants you to calculate the minimal number of swaps he would need to perform to make it so that the array does not contain two neighboring items with the same parity.

## 说明/提示

In the first test case the following sequence of operations would satisfy the requirements:

1. swap(2, 3). Array after performing the operation: $ [6, 1, 6] $

In the second test case the array initially does not contain two neighboring items of the same parity.

In the third test case the following sequence of operations would satisfy the requirements:

1. swap(3, 4). Array after performing the operation: $ [1, 1, 2, 1, 2, 2] $
2. swap(2, 3). Array after performing the operation: $ [1, 2, 1, 1, 2, 2] $
3. swap(4, 5). Array after performing the operation: $ [1, 2, 1, 2, 1, 2] $

In the fourth test case it is impossible to satisfy the requirements.

In the fifth test case the following sequence of operations would satisfy the requirements:

1. swap(2, 3). Array after performing the operation: $ [6, 3, 2, 4, 5, 1] $
2. swap(4, 5). Array after performing the operation: $ [6, 3, 2, 5, 4, 1] $

## 样例 #1

### 输入

```
5
3
6 6 1
1
9
6
1 1 1 2 2 2
2
8 6
6
6 2 3 4 5 1```

### 输出

```
1
0
3
-1
2```

# AI分析结果

### 题目内容
# 各就各位！

## 题目描述
威廉有一个包含 \(n\) 个整数 \(a_1, a_2, \dots, a_n\) 的数组。在一次操作中，他可以交换两个相邻的元素。如果满足条件 \( |i - j| = 1\)，则元素 \(a_i\) 和 \(a_j\) 被视为相邻。

威廉希望你计算出，为了使数组中不存在两个相邻元素具有相同的奇偶性，他最少需要执行多少次交换操作。

## 说明/提示
在第一个测试用例中，以下操作序列可以满足要求：
1. 交换(2, 3)。执行操作后的数组：\([6, 1, 6]\)

在第二个测试用例中，数组最初就不存在两个相邻元素具有相同的奇偶性。

在第三个测试用例中，以下操作序列可以满足要求：
1. 交换(3, 4)。执行操作后的数组：\([1, 1, 2, 1, 2, 2]\)
2. 交换(2, 3)。执行操作后的数组：\([1, 2, 1, 1, 2, 2]\)
3. 交换(4, 5)。执行操作后的数组：\([1, 2, 1, 2, 1, 2]\)

在第四个测试用例中，无法满足要求。

在第五个测试用例中，以下操作序列可以满足要求：
1. 交换(2, 3)。执行操作后的数组：\([6, 3, 2, 4, 5, 1]\)
2. 交换(4, 5)。执行操作后的数组：\([6, 3, 2, 5, 4, 1]\)

## 样例 #1
### 输入
```
5
3
6 6 1
1
9
6
1 1 1 2 2 2
2
8 6
6
6 2 3 4 5 1
```
### 输出
```
1
0
3
-1
2
```

### 算法分类
贪心

### 综合分析与结论
所有题解都先判断无解情况，即奇数个数与偶数个数之差的绝对值超过1时无解。对于有解情况，根据数组长度 \(n\) 的奇偶性分类讨论。当 \(n\) 为奇数时，若奇数与偶数个数差为1，将个数多的数填到奇数位置，计算其与目标位置的距离和；当 \(n\) 为偶数时，若奇数与偶数个数相同，分别计算奇数放奇数位置和奇数放偶数位置的操作次数，取最小值。不同之处在于部分题解使用树状数组优化计算距离和的过程，部分直接暴力计算。

### 所选的题解
- **youyou2007题解**：★★★★
    - **关键亮点**：思路清晰，代码简洁，直接根据 \(n\) 的奇偶性和奇偶数个数进行分类，计算移动距离和。
    - **重点代码**：
```cpp
if(abs(t1-t2)>1){//判断无解
    puts("-1");
    continue;
}
int ans=0;
if(n & 1){//n是奇数的情况
    int s=0;
    if(t1 > t2){
        rep(i,1,t1){
            s+=abs(e[i]-(i*2-1));//
        }
        ans=s;
    }
    else{
        rep(i,1,t2){
            s+=abs(o[i]-(i*2-1));
        }
        ans = s;
    }
}
else{//n是偶数的情况，放到奇数位置和偶数位置都要算一遍
    int s=0;
    rep(i,1,t1){
        s+=abs(e[i]-(i*2-1));
    }
    ans=s;
    s=0;
    rep(i,1,t1){
        s+=abs(e[i]-(i*2));
    }
    ans=min(s,ans);
}
```
核心实现思想：先记录奇数和偶数的位置，根据 \(n\) 奇偶性和奇偶数个数，计算对应位置的距离和，奇数多则奇数放奇数位置，偶数多则偶数放奇数位置，偶数个数相等则两种情况都计算取最小值。
- **felixshu题解**：★★★★
    - **关键亮点**：代码逻辑清晰，按照 \(n\) 的奇偶性分别处理，代码结构明了。
    - **重点代码**：
```cpp
if(n%2==0){
    if(k1==k2){ 
        long long m1=0,m2=0;
        for(int i = 1; i <= k2; i++){
            int l=((i-1)<<1)+1;
            m1+=abs(a2[i]-l);
        }
        for(int i=1;i<=k1; i++){
            int l=((i-1)<<1)+1;
            m2+=abs(a1[i]-l);
        }
        ans = min(m1, m2);
        cout<<ans<<endl;
        continue;
    }
    else{
        cout<<"-1"<<endl;
        continue;
    }
}
else{
    if(abs(k1- k2)!= 1) {
        cout<<"-1"<<endl;
        continue;
    }
    if(k2 > k1){
        long long m1 = 0;
        for(int i = 1; i <= k2; i++){
            int l=((i-1)<<1)+1;
            m1 += abs(a2[i] - l);
        }
        cout<<m1<<endl;
    }
    else{
        long long m1 = 0;
        for(int i = 1; i <= k1; i++){
            int l=((i-1)<<1)+1;
            m1 +=abs(a1[i] - l);
        }
        cout<<m1<<endl;
    }
}
```
核心实现思想：同样先判断无解情况，对于 \(n\) 为偶数且奇数偶数个数相同，分别计算奇数放奇数位和偶数放奇数位的距离和取最小值；\(n\) 为奇数且奇偶数个数差为1，将个数多的放奇数位置计算距离和。
- **NXYorz题解**：★★★★
    - **关键亮点**：代码简洁，注释清晰，逻辑完整，按照分析思路逐步实现。
    - **重点代码**：
```cpp
if(n & 1){
    if(abs(eve[0] - odd[0])!= 1) {printf("-1\n"); return;}
    if(eve[0] > odd[0]){
        long long tot = 0;
        for(int i = 1; i <= eve[0]; i++){
            int loc = ((i - 1) << 1) + 1;
            tot += abs(eve[i] - loc);
        }
        ans = min(ans, tot);
    }
    else{
        long long tot = 0;
        for(int i = 1; i <= odd[0]; i++){
            int loc = ((i - 1) << 1) + 1;
            tot += abs(odd[i] - loc);
        }
        ans = min(ans, tot);
    }
}
else{
    if(eve[0]!= odd[0]) {printf("-1\n"); return;}
    long long tot = 0;
    for(int i = 1; i <= eve[0]; i++){
        int loc = ((i - 1) << 1) + 1;
        tot += abs(eve[i] - loc);
    }
    ans = min(ans, tot); tot = 0;
    for(int i = 1; i <= odd[0]; i++){
        int loc = ((i - 1) << 1) + 1;
        tot += abs(odd[i] - loc);
    }
    ans = min(ans, tot); tot = 0;
}
```
核心实现思想：先判断无解，再依据 \(n\) 奇偶性，奇数时将个数多的放奇数位置算距离和，偶数时分别计算奇数放奇数位和奇数放偶数位的距离和取最小值。

### 最优关键思路或技巧
通过分析数组长度 \(n\) 的奇偶性以及奇数和偶数个数的关系，利用贪心策略，将某一种数（个数多的或其中一种）放置到特定位置（奇数位置），计算其与目标位置的距离和，避免了复杂的交换模拟过程，直接得到最小交换次数。

### 可拓展之处
同类型题可考察类似的奇偶性分析与贪心策略结合，比如对序列元素有其他性质要求（如大小关系、整除关系等），通过交换相邻元素达到特定排列要求，同样可先分析无解情况，再依据条件分类讨论。

### 推荐洛谷题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：涉及贪心策略，根据元素的两个属性进行排序和计算。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：通过分析任务在不同机器上的加工时间，利用贪心思想安排任务顺序。
- [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)：需要对区间进行处理，运用贪心策略解决资源分配问题。 

---
处理用时：64.91秒