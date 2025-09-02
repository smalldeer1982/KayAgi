# 题目信息

# [ARC154C] Roller

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc154/tasks/arc154_c

長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N),B=(B_1,B_2,\dots,B_N) $ が与えられます。

あなたは以下の操作を好きな回数（$ 0 $ 回でもよい）繰り返すことができます。

- $ 1\ \le\ i\ \le\ N $ を満たす整数 $ i $ を選び、$ A_i $ を $ A_{i+1} $ で置き換える。
 
ただし、$ A_{N+1} $ とは $ A_1 $ のこととします。

$ A $ を $ B $ に一致させることが出来るか判定してください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 5000 $
- $ 1\ \le\ N\ \le\ 5000 $
- $ 1\ \le\ A_i,B_i\ \le\ N $
- $ 1 $ 個の入力に含まれるテストケースについて、それらの $ N $ の総和は $ 5000 $ を超えない。
 
### Sample Explanation 1

$ 1 $ 個目のテストケースでは、以下のように操作することにより $ A $ を $ B $ と一致させることが出来ます。 - $ i=1 $ を選ぶ。$ A_1 $ を $ A_2 $ で置き換える。$ A=(2,2) $ となる。 $ 2 $ 個目のテストケースでは、以下のように操作することにより $ A $ を $ B $ と一致させることが出来ます。 - $ i=4 $ を選ぶ。$ A_4 $ を $ A_1 $ で置き換える。$ A=(2,3,1,2) $ となる。 - $ i=2 $ を選ぶ。$ A_2 $ を $ A_3 $ で置き換える。$ A=(2,1,1,2) $ となる。 $ 3 $ 個目のテストケースでは、どのように操作しても $ A $ を $ B $ と一致させることは出来ません。

## 样例 #1

### 输入

```
3

2

1 2

2 2

4

2 3 1 1

2 1 1 2

2

1 1

2 2```

### 输出

```
Yes

Yes

No```

# AI分析结果

### 题目翻译
给定两个长度为 $N$ 的序列 $A=(A_1,A_2,\dots,A_N)$ 和 $B=(B_1,B_2,\dots,B_N)$。你可以执行以下操作（包括 $0$ 次）：选择一个整数 $i(1\le i\le n)$，然后令 $A_i=A_{i+1}$，特别的，令 $A_{n+1}=A_1$。请问是否可以将 $A$ 序列变成 $B$ 序列。

### 题解分析与结论

#### 综合分析与结论
本题的核心在于通过操作将序列 $A$ 转换为序列 $B$。操作的本质是将 $A_i$ 替换为 $A_{i+1}$，且序列是环形的。因此，关键在于如何通过这种操作调整 $A$ 的结构，使其与 $B$ 一致。

各题解的思路主要集中在以下几点：
1. **压缩序列**：将相邻的相同元素合并，形成“块”，简化问题。
2. **子序列匹配**：判断 $B$ 的压缩序列是否是 $A$ 的压缩序列的某个旋转后的子序列。
3. **特殊情况处理**：当 $A$ 和 $B$ 的压缩序列长度均为 $N$ 时，直接比较是否完全相同。

#### 所选高星题解

##### 题解1：Daidly (4星)
**关键亮点**：
- 将序列压缩成块，简化问题。
- 通过枚举起点，判断 $B$ 的压缩序列是否是 $A$ 的压缩序列的某个旋转后的子序列。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
bool solve(){
    n=read(),na=nb=0;
    for(int i=1;i<=n;++i)a[i]=a[i+n]=read();
    for(int i=1;i<=n;++i)b[i]=read();
    for(int i=1;i<=n;++i)if(a[i]!=a[i%n+1])ta[++na]=a[i];
    for(int i=1;i<=n;++i)if(b[i]!=b[i%n+1])tb[++nb]=b[i];
    if(!na)ta[++na]=a[1];
    if(!nb)tb[++nb]=b[1];
    if(na==n&&nb==n){
        for(int i=1;i<=n;++i)if(a[i]!=b[i])return 0;
        return 1;
    }
    for(int i=1;i<=na;++i){
        int pos=1;
        for(int j=0;j<na;++j)if(ta[(i+j)%na?(i+j)%na:na]==tb[pos])pos++;
        if(pos>nb)return 1;
    }
    return 0;
}
```

##### 题解2：Erica_N_Contina (4星)
**关键亮点**：
- 从序列中数字的种类和相对位置入手，分析是否可以通过操作调整 $A$ 的结构。
- 详细讨论了不同情况下的处理方式，逻辑严谨。
- 代码实现清晰，注释详细。

**核心代码**：
```cpp
bool judge(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i+n]=a[i];
    for(int i=1;i<=n;i++)scanf("%d",&b[i]);
    int na=0,nb=0;
    for(int i=1;i<=n;i++)if(a[i]!=a[i%n+1])ta[++na]=a[i];
    for(int i=1;i<=n;i++)if(b[i]!=b[i%n+1])tb[++nb]=b[i];
    if(!na)ta[++na]=a[1];
    if(!nb)tb[++nb]=b[1];
    if(na==n&&nb==n){
        for(int i=1;i<=n;i++)
            if(a[i]!=b[i])return 0;
        return 1;
    }
    for(int i=1;i<=na;i++){
        int idb=1;
        for(int j=0;j<na;j++){
            int ida;
            if((i+j)%na)ida=(i+j)%na;
            else ida=na;    
            if(ta[ida]==tb[idb])idb++;
        }
        if(idb>nb)return 1;
    }
    return 0;
}
```

##### 题解3：e4fsrc2e4fsrc2 (4星)
**关键亮点**：
- 将序列压缩成块，简化问题。
- 通过枚举起点，判断 $B$ 的压缩序列是否是 $A$ 的压缩序列的某个旋转后的子序列。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
bool judge(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i+n]=a[i];
    for(int i=1;i<=n;i++)scanf("%d",&b[i]);
    int na=0,nb=0;
    for(int i=1;i<=n;i++)if(a[i]!=a[i%n+1])ta[++na]=a[i];
    for(int i=1;i<=n;i++)if(b[i]!=b[i%n+1])tb[++nb]=b[i];
    if(!na)ta[++na]=a[1];
    if(!nb)tb[++nb]=b[1];
    if(na==n&&nb==n){
        for(int i=1;i<=n;i++)
            if(a[i]!=b[i])return 0;
        return 1;
    }
    for(int i=1;i<=na;i++){
        int idb=1;
        for(int j=0;j<na;j++){
            int ida;
            if((i+j)%na)ida=(i+j)%na;
            else ida=na;    
            if(ta[ida]==tb[idb])idb++;
        }
        if(idb>nb)return 1;
    }
    return 0;
}
```

### 最优关键思路与技巧
1. **压缩序列**：将相邻的相同元素合并成块，简化问题。
2. **子序列匹配**：通过枚举起点，判断 $B$ 的压缩序列是否是 $A$ 的压缩序列的某个旋转后的子序列。
3. **特殊情况处理**：当 $A$ 和 $B$ 的压缩序列长度均为 $N$ 时，直接比较是否完全相同。

### 可拓展之处
- **类似问题**：可以扩展到其他需要通过操作调整序列结构的问题，如通过交换、替换等操作将序列转换为目标序列。
- **算法套路**：压缩序列、子序列匹配、枚举起点等技巧在其他序列问题中也有广泛应用。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：56.72秒