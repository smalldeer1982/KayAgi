# 题目信息

# Paint the Digits

## 题目描述

You are given a sequence of $ n $ digits $ d_1d_2 \dots d_{n} $ . You need to paint all the digits in two colors so that:

- each digit is painted either in the color $ 1 $ or in the color $ 2 $ ;
- if you write in a row from left to right all the digits painted in the color $ 1 $ , and then after them all the digits painted in the color $ 2 $ , then the resulting sequence of $ n $ digits will be non-decreasing (that is, each next digit will be greater than or equal to the previous digit).

For example, for the sequence $ d=914 $ the only valid coloring is $ 211 $ (paint in the color $ 1 $ two last digits, paint in the color $ 2 $ the first digit). But $ 122 $ is not a valid coloring ( $ 9 $ concatenated with $ 14 $ is not a non-decreasing sequence).

It is allowed that either of the two colors is not used at all. Digits painted in the same color are not required to have consecutive positions.

Find any of the valid ways to paint the given sequence of digits or determine that it is impossible to do.

## 说明/提示

In the first test case, $ d=040425524644 $ . The output $ t=121212211211 $ is correct because $ 0022444 $ (painted in $ 1 $ ) concatenated with $ 44556 $ (painted in $ 2 $ ) is $ 002244444556 $ which is a sorted sequence of $ n $ given digits.

## 样例 #1

### 输入

```
5
12
040425524644
1
0
9
123456789
2
98
3
987
```

### 输出

```
121212211211
1
222222222
21
-
```

# AI分析结果

### 题目内容翻译
#### 题目描述
给定一个由 $n$ 个数字组成的序列 $d_1d_2 \dots d_{n}$。你需要将所有数字用两种颜色进行染色，使得：
- 每个数字要么染成颜色 $1$，要么染成颜色 $2$；
- 如果你将所有染成颜色 $1$ 的数字从左到右依次排列，然后接着排列所有染成颜色 $2$ 的数字，那么得到的长度为 $n$ 的数字序列是非递减的（即每个后续数字都大于或等于前一个数字）。

例如，对于序列 $d = 914$，唯一有效的染色方案是 $211$（将最后两个数字染成颜色 $1$，将第一个数字染成颜色 $2$）。但 $122$ 不是有效的染色方案（$9$ 与 $14$ 连接起来不是非递减序列）。

允许两种颜色中的某一种完全不使用。染成相同颜色的数字不要求位置连续。

找出任意一种有效的染色方案来对给定的数字序列进行染色，或者判断无法进行染色。

#### 说明/提示
在第一个测试用例中，$d = 040425524644$。输出 $t = 121212211211$ 是正确的，因为染成颜色 $1$ 的数字 $0022444$ 与染成颜色 $2$ 的数字 $44556$ 连接起来得到 $002244444556$，这是一个由 $n$ 个给定数字组成的有序序列。

#### 样例 #1
##### 输入
```
5
12
040425524644
1
0
9
123456789
2
98
3
987
```
##### 输出
```
121212211211
1
222222222
21
-
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心都是将原序列分成两个子序列，使得它们连接后是非递减序列。各题解的思路和实现方法有所不同：
- **jiangXxin**：通过排序原序列并与原序列比较，相同的分入第一组，不同的分入第二组，最后检查结果是否满足非递减条件。
- **wuyixiang**：采用排序 + 贪心策略，枚举第一个子序列最后面的下标，根据字符能否接上决定子序列的选择。
- **叶ID**：枚举序列 $1$ 和序列 $2$ 的分界值 $t$，从后往前扫描确定子序列 $1$，剩下的为子序列 $2$，再判断子序列 $2$ 是否非递减。
- **皎月半洒花**：观察性质，根据位置和数字大小关系划分两个子序列，最后检查结果。
- **E1_de5truct0r**：先排序原序列，用双指针按副本顺序选 $1$，剩下的为 $2$，判断 $2$ 是否按顺序排列；还提出了 $O(n)$ 的做法，预处理 $minn$ 数组并特判。

### 所选题解
- **jiangXxin（4星）**：
    - **关键亮点**：思路清晰，代码结构完整，通过排序和比较的方式简单直接地实现了子序列的划分，最后进行结果检查。
    - **个人心得**：作者提到这道题当时差点没做出来，说明题目有一定难度。
- **叶ID（4星）**：
    - **关键亮点**：通过枚举分界值 $t$ 来确定两个子序列，从后往前扫描的方式巧妙地处理了子序列的划分，逻辑严谨。
- **E1_de5truct0r（4星）**：
    - **关键亮点**：双指针的应用简洁高效，还提出了 $O(n)$ 的优化思路，虽然对其正确性存疑，但提供了新的思考方向。

### 重点代码
#### jiangXxin
```cpp
REP(1,n,i){
    if(a[i]==b[pos]){
        pos++;
        ans[i]=1;
    }
    else ans[i]=2;
}
// 获得一个答案序列
int tim=0;
REP(1,n,i){
    if(ans[i]==1)c[++tim]=a[i];
}
REP(1,n,i){
    if(ans[i]==2)c[++tim]=a[i];
}
// 无解的判断
int flag=0;
REP(1,n-1,i){
    if(c[i]>c[i+1]){
        flag=1;
        break;
    }
}
```
**核心实现思想**：先将原序列和排序后的序列比较，划分出两个子序列，再将子序列组合成一个序列，最后检查该序列是否非递减。

#### 叶ID
```cpp
for(int t=0;t<10;t++) {
    int m1 = 10;
    int m2 = 10;
    bool ok = 1;
    for(int i=1;i<=n;i++) col[i]=-1;
    for(int i=n;i>=1;i--) {
        if(arr[i]<=t) {
            if(arr[i]<=m1) col[i] = 1;
            if(arr[i]>m1 && arr[i]!=t) {ok=0;break;}
            if(arr[i]<=m1) m1=arr[i];
        }
    }
    for(int i=n;i>=1;i--) {
        if(arr[i]>=t && col[i]!=1) {
            col[i] = 2;
            if(arr[i]>m2) {ok=0;break;}
            m2=arr[i];
        }
    }
    if(ok) {
        for(int j=1;j<=n;j++) {
            cout<<col[j];
        }
        cout<<'\n';
        solved = 1;
        break;
    }
}
```
**核心实现思想**：枚举分界值 $t$，从后往前扫描确定子序列 $1$，再确定子序列 $2$，最后判断是否满足条件。

#### E1_de5truct0r
```cpp
for(int i=1;i<=n;i++)
    if(a[i]==b[j]) j++,col[i]=1;
    else col[i]=2,F.push_back(a[i]);
bool flag=1;
for(int i=1;i<F.size();i++)
    if(F[i]<F[i-1]) {
        flag=0;
        break;
    }
```
**核心实现思想**：用双指针按排序后的副本顺序选 $1$，剩下的为 $2$，判断 $2$ 是否按顺序排列。

### 最优关键思路或技巧
- 排序是解决本题的基础，通过排序后的序列与原序列比较可以方便地划分两个子序列。
- 枚举分界值 $t$ 是一种巧妙的思路，能够有效地确定两个子序列的范围。
- 双指针的应用可以在 $O(n)$ 时间内完成子序列的划分。

### 可拓展之处
同类型题可能会有更多的限制条件，如颜色数量增加、子序列数量增加等。类似算法套路可以是先对序列进行排序，再根据一定的规则划分序列，最后检查结果是否满足条件。

### 推荐洛谷题目
- [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)
- [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
- [P1271 【深基9.例1】选举学生会](https://www.luogu.com.cn/problem/P1271)

### 个人心得摘录与总结
- **jiangXxin**：作者提到这道题当时差点没做出来，说明题目有一定难度，需要仔细思考和尝试不同的方法。
- **E1_de5truct0r**：作者提出了 $O(n)$ 的优化思路，但对其正确性存疑，这提醒我们在优化算法时要注意证明其正确性。

---
处理用时：54.31秒