# 题目信息

# Binary Search

## 题目描述

Anton got bored during the hike and wanted to solve something. He asked Kirill if he had any new problems, and of course, Kirill had one.

You are given a permutation $ p $ of size $ n $ , and a number $ x $ that needs to be found. A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

You decided that you are a cool programmer, so you will use an advanced algorithm for the search — binary search. However, you forgot that for binary search, the array must be sorted.

You did not give up and decided to apply this algorithm anyway, and in order to get the correct answer, you can perform the following operation no more than $ 2 $ times before running the algorithm: choose the indices $ i $ , $ j $ ( $ 1\le i, j \le n $ ) and swap the elements at positions $ i $ and $ j $ .

After that, the binary search is performed. At the beginning of the algorithm, two variables $ l = 1 $ and $ r = n + 1 $ are declared. Then the following loop is executed:

1. If $ r - l = 1 $ , end the loop
2. $ m = \lfloor \frac{r + l}{2} \rfloor $
3. If $ p_m \le x $ , assign $ l = m $ , otherwise $ r = m $ .

The goal is to rearrange the numbers in the permutation before the algorithm so that after the algorithm is executed, $ p_l $ is equal to $ x $ . It can be shown that $ 2 $ operations are always sufficient.

## 样例 #1

### 输入

```
5
6 3
1 2 3 4 5 6
6 5
3 1 6 5 2 4
5 1
3 5 4 2 1
6 3
4 3 1 5 2 6
3 2
3 2 1```

### 输出

```
0
1
3 4
2
2 4
1 5
2
4 5
2 4
1
1 3```

# AI分析结果

### 题目翻译
# 二分查找

## 题目描述
安东在徒步旅行时感到无聊，想解决点问题。他问基里尔有没有新问题，基里尔当然有一个。

给定一个长度为 $n$ 的排列 $p$，以及一个需要查找的数字 $x$。长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（数字 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（$n = 3$，但数组中出现了 $4$）。

你觉得自己是个厉害的程序员，所以打算使用高级算法——二分查找。然而，你忘了二分查找要求数组是有序的。

你没有放弃，决定还是应用这个算法。为了得到正确的答案，你可以在运行算法之前最多执行 $2$ 次以下操作：选择索引 $i$、$j$（$1 \leq i, j \leq n$），并交换位置 $i$ 和 $j$ 上的元素。

之后进行二分查找。算法开始时，声明两个变量 $l = 1$ 和 $r = n + 1$。然后执行以下循环：
1. 如果 $r - l = 1$，结束循环。
2. $m = \lfloor \frac{r + l}{2} \rfloor$。
3. 如果 $p_m \leq x$，则令 $l = m$，否则令 $r = m$。

目标是在算法执行前重新排列排列中的数字，使得算法执行后，$p_l$ 等于 $x$。可以证明，$2$ 次操作总是足够的。

## 样例 #1
### 输入
```
5
6 3
1 2 3 4 5 6
6 5
3 1 6 5 2 4
5 1
3 5 4 2 1
6 3
4 3 1 5 2 6
3 2
3 2 1
```

### 输出
```
0
1
3 4
2
2 4
1 5
2
4 5
2 4
1
1 3
```

### 综合分析与结论
这些题解的核心思路都是围绕二分查找的结果和目标值 $x$ 的关系进行处理。多数题解发现将 $x$ 所在位置与二分查找最终得到的 $l$ 位置交换，通常能满足要求，且最多只需一次交换。

- **思路对比**：大部分题解直接考虑交换 $x$ 和 $l$ 的位置，如 Sternenlicht、JOE_ZengYuQiao_0928 等；而 spfa_ 考虑了 $x$ 是否在判定点上的情况，较为复杂；Exp10re 则是在二分过程中碰到 $x$ 就交换 $(1, x)$，最后再交换 $(p, x)$。
- **算法要点**：先进行二分查找得到最终的 $l$ 值，记录 $x$ 的位置，然后根据 $p_l$ 与 $x$ 的关系决定是否交换以及如何交换。
- **解决难点**：主要难点在于证明交换 $x$ 和 $p_l$ 不会影响二分查找的过程。多数题解通过分类讨论 $p_l$ 与 $x$ 的大小关系以及 $x$ 是否在二分过程中作为 $p_m$ 进行比较来解决。

### 高评分题解
- **Sternenlicht（5星）**
    - **关键亮点**：思路清晰，分类讨论详细，对交换操作不影响二分过程的证明严谨，代码实现简洁高效，有快速输入输出优化。
    - **核心代码**：
```cpp
while (T --) {
    int n, x, ans; read(n, x);
    for (int i = 1; i <= n; i ++) {
        read(a[i]);
        if (a[i] == x) ans = i;
    }
    int l = 1, r = n + 1;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (a[mid] <= x) l = mid;
        else r = mid;
    }
    if (a[l] == x) puts("0");
    else puts("1"), write(l, ' '), write(ans);
}
```
核心实现思想：先读入数据，记录 $x$ 的位置，进行二分查找得到 $l$，若 $p_l$ 等于 $x$ 则无需交换，否则交换 $x$ 和 $p_l$ 的位置。

- **JOE_ZengYuQiao_0928（4星）**
    - **关键亮点**：推理简洁明了，代码结构清晰，注释丰富，适合初学者理解。
    - **核心代码**：
```cpp
void w(){
    ans=0;
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]==x)ans=i;
    }
    int l=1,r=n+1; 
    while(l+1<r){
        int mid=(l+r)/2;
        if(a[mid]<=x)l=mid;
        else r=mid;
    }
    if(a[l]==x)cout<<"0\n";
    else cout<<"1\n"<<l<<" "<<ans<<"\n";
}
```
核心实现思想：在 `w` 函数中完成数据读入、二分查找和结果判断，若 $p_l$ 不等于 $x$ 则交换 $x$ 和 $p_l$ 的位置。

- **__Floze3__（4星）**
    - **关键亮点**：对不同情况的证明详细，思路严谨，代码简洁规范。
    - **核心代码**：
```cpp
while (T--) {
    read >> n >> x;
    for (int i = 1; i <= n; i++) {
        read >> a[i];
        if (a[i] == x) pos = i;
    }
    int l = 1, r = n + 1;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (a[mid] <= x) l = mid;
        else r = mid;
    }
    if (a[l] == x) write << "0\n";
    else write << "1\n" << l << ' ' << pos << '\n';
}
```
核心实现思想：循环处理每组数据，读入数据并记录 $x$ 的位置，二分查找得到 $l$，根据 $p_l$ 与 $x$ 的关系输出结果。

### 最优关键思路或技巧
- **思维方式**：通过分析二分查找的过程和条件，发现交换 $x$ 和 $p_l$ 不会影响二分结果，从而简化问题。
- **代码实现**：在二分查找前记录 $x$ 的位置，避免后续再次查找。

### 拓展思路
同类型题可能会改变排列的条件或二分查找的规则，如数组不是排列而是普通数组，或者二分查找的判断条件发生变化。类似算法套路可以先模拟原算法过程，分析结果与目标的关系，再通过少量操作调整数组以满足要求。

### 洛谷相似题目推荐
1. [P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
3. [P1678 烦恼的高考志愿](https://www.luogu.com.cn/problem/P1678)

### 个人心得摘录与总结
JOE_ZengYuQiao_0928 提到“经过我两分半时间的推理，得出一条结论”，总结为通过快速思考和推理找到解题关键结论，体现了在解题时积极思考、大胆推理的重要性。 

---
处理用时：38.41秒