# 题目信息

# Special Permutation

## 题目描述

A permutation of length $ n $ is an array $ p=[p_1,p_2,\dots,p_n] $ , which contains every integer from $ 1 $ to $ n $ (inclusive) and, moreover, each number appears exactly once. For example, $ p=[3,1,4,2,5] $ is a permutation of length $ 5 $ .

For a given number $ n $ ( $ n \ge 2 $ ), find a permutation $ p $ in which absolute difference (that is, the absolute value of difference) of any two neighboring (adjacent) elements is between $ 2 $ and $ 4 $ , inclusive. Formally, find such permutation $ p $ that $ 2 \le |p_i - p_{i+1}| \le 4 $ for each $ i $ ( $ 1 \le i < n $ ).

Print any such permutation for the given integer $ n $ or determine that it does not exist.

## 样例 #1

### 输入

```
6
10
2
4
6
7
13```

### 输出

```
9 6 10 8 4 7 3 1 5 2 
-1
3 1 4 2 
5 3 6 2 4 1 
5 1 3 6 2 4 7 
13 9 7 11 8 4 1 3 5 2 6 10 12```

# AI分析结果

### 题目翻译
## 特殊排列

### 题目描述
长度为 $n$ 的排列是一个数组 $p=[p_1,p_2,\dots,p_n]$，它包含从 $1$ 到 $n$ 的每个整数（包含 $1$ 和 $n$），并且每个数字恰好出现一次。例如，$p=[3,1,4,2,5]$ 是一个长度为 $5$ 的排列。

对于给定的数字 $n$（$n \ge 2$），找到一个排列 $p$，其中任意两个相邻元素的绝对差（即差值的绝对值）在 $2$ 到 $4$ 之间（包含 $2$ 和 $4$）。形式上，找到这样的排列 $p$，使得对于每个 $i$（$1 \le i < n$），都有 $2 \le |p_i - p_{i+1}| \le 4$。

为给定的整数 $n$ 输出任意一个这样的排列，或者确定不存在这样的排列。

### 样例 #1
#### 输入
```
6
10
2
4
6
7
13
```
#### 输出
```
9 6 10 8 4 7 3 1 5 2 
-1
3 1 4 2 
5 3 6 2 4 1 
5 1 3 6 2 4 7 
13 9 7 11 8 4 1 3 5 2 6 10 12
```

### 综合分析与结论
这些题解主要围绕如何构造满足条件的排列展开，多数题解先对 $n < 4$ 的情况进行特判，因为此时不存在满足条件的排列。对于 $n \geq 4$ 的情况，不同题解采用了不同的构造方法：
- **打表法**：通过手算小数据找到循环节，根据 $n$ 对 $5$ 取模的结果分类讨论，打表输出相应的排列。
- **奇偶分类法**：根据 $n$ 的奇偶性分别构造排列，一般是先处理奇数或偶数，再调整顺序以满足相邻元素差的条件。
- **规律构造法**：通过观察样例或特定排列，找到插入新元素的规律，逐步构造出满足条件的排列。

### 所选题解
- **作者：天南星魔芋（5星）**
    - **关键亮点**：思路清晰，通过手算小数据找到循环节，将问题分类讨论，打表解决，代码实现简洁明了，易于理解。
    - **核心代码**：
```cpp
int base[20]={0,1,3,5,2,4};//表×5 
int base6[20]={0,1,3,5,2,4,6};
int base7[20]={0,1,3,7,5,2,4,6};
int base8[20]={0,1,3,7,5,2,4,6,8};
int base9[20]={0,1,3,5,2,4,7,9,6,8};

void base_print(int x){
    for(int i=1;i<=5;i++){
        printf("%d ",base[i]+x);
    }
}
// 其他打印函数类似

void js(int x){
    if(x<5){
        if(x==1)printf("1");
        if(x==4)printf("3 1 4 2");
        else printf("-1");
    }
    int y=0;
    while(y+10<=x){
        base_print(y);
        y+=5;
    }
    int pd=x-y;
    if(pd==5)base_print(y);
    else if(pd==6)print_6(y);
    else if(pd==7)print_7(y);
    else if(pd==8)print_8(y);
    else if(pd==9)print_9(y);
}
```
核心思想是先处理 $n < 5$ 的特殊情况，然后根据 $n$ 对 $5$ 取模的结果，选择相应的打表函数输出排列。
- **作者：奇米（4星）**
    - **关键亮点**：思路简洁，通过分奇偶讨论，利用奇数和偶数的性质构造排列，代码实现清晰。
    - **核心代码**：
```cpp
if(n&1){
    for ( int j=n;j>=1;j-- ) 
        if(j&1) a[++cnt]=j;
    a[++cnt]=4,a[++cnt]=2;
    if(n>=6)
        for ( int j=6;j<=n;j++ ) 
            if(j%2==0) a[++cnt]=j;
}
else {
    for ( int j=n;j>=1;j-- ) 
        if(j%2==0) a[++cnt]=j;
    a[++cnt]=5,a[++cnt]=1,a[++cnt]=3;
    if(n>=7)
        for ( int j=7;j<=n;j++ ) 
            if(j&1) a[++cnt]=j;	
}
```
核心思想是根据 $n$ 的奇偶性，先处理奇数或偶数，再插入特定的数，最后处理剩余的数。
- **作者：SpeedStar（4星）**
    - **关键亮点**：代码简洁，直接给出构造方法，先降序输出奇数，再输出 $4$ 和 $2$，最后升序输出偶数。
    - **核心代码**：
```cpp
if (n < 4) {
    cout << -1 << '\n';
    continue;
}
for (int i = n; i >= 1; --i) {
    if (i & 1) cout << i << ' ';
}
cout << 4 << ' ' << 2 << ' ';
for (int i = 6; i <= n; i += 2) {
    cout << i << ' ';
}
```
核心思想是先特判 $n < 4$ 的情况，然后按照特定顺序输出奇数、$4$、$2$ 和偶数。

### 最优关键思路或技巧
- **奇偶性分析**：多数题解利用了奇数和偶数的性质，通过分别处理奇数和偶数，构造出满足相邻元素差条件的排列。
- **打表法**：对于一些复杂的情况，通过手算小数据找到规律，打表输出结果，简化了代码实现。

### 可拓展之处
同类型题可能会改变相邻元素差的范围或其他条件，解题思路仍然可以从奇偶性、打表、找规律等方面入手。类似算法套路包括构造排列、组合数学等。

### 推荐题目
- [P1008 三连击](https://www.luogu.com.cn/problem/P1008)：考察排列组合的构造。
- [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)：需要构造满足特定条件的字符串排列。
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：涉及状态的构造和搜索。

### 个人心得摘录与总结
- **天南星魔芋**：表示自己数论不好，通过手算小数据找到循环节的方法解决问题，体现了从简单情况入手找规律的思维方式。
- **b6e0_**：提到对着样例找规律，说明观察样例是解决构造题的一种有效方法。

---
处理用时：36.66秒