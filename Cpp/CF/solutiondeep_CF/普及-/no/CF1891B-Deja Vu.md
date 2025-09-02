# 题目信息

# Deja Vu

## 题目描述

You are given an array $ a $ of length $ n $ , consisting of positive integers, and an array $ x $ of length $ q $ , also consisting of positive integers.

There are $ q $ modification. On the $ i $ -th modification ( $ 1 \leq i \leq q $ ), for each $ j $ ( $ 1 \leq j \leq n $ ), such that $ a_j $ is divisible by $ 2^{x_i} $ , you add $ 2^{x_i-1} $ to $ a_j $ . Note that $ x_i $ ( $ 1 \leq x_i \leq 30 $ ) is a positive integer not exceeding 30.

After all modification queries, you need to output the final array.

## 说明/提示

In the first test case, the first query will add $ 2 $ to the integers in positions $ 4 $ and $ 5 $ . After this addition, the array would be $ [1, 2, 3, 6, 6] $ . Other operations will not modify the array.

In the second test case, the first modification query does not change the array. The second modification query will add $ 8 $ to the integer in position $ 5 $ , so that the array would look like this: $ [7, 8, 12, 36, 56, 6, 3] $ . The third modification query will add $ 2 $ to the integers in positions $ 2, 3 $ , $ 4 $ and $ 5 $ . The array would then look like this: $ [7, 10, 14, 38, 58, 6, 3] $ .

## 样例 #1

### 输入

```
4
5 3
1 2 3 4 4
2 3 4
7 3
7 8 12 36 48 6 3
10 4 2
5 4
2 2 2 2 2
1 1 1 1
5 5
1 2 4 8 16
5 2 3 4 1```

### 输出

```
1 2 3 6 6 
7 10 14 38 58 6 3 
3 3 3 3 3 
1 3 7 11 19```

# AI分析结果

### 题目翻译
## 似曾相识

### 题目描述
给定一个长度为 $n$ 的数组 $a$，数组元素均为正整数，以及一个长度为 $q$ 的数组 $x$，其元素同样为正整数。

共有 $q$ 次修改操作。在第 $i$ 次修改操作（$1 \leq i \leq q$）中，对于每个 $j$（$1 \leq j \leq n$），若 $a_j$ 能被 $2^{x_i}$ 整除，则将 $2^{x_i - 1}$ 加到 $a_j$ 上。注意，$x_i$（$1 \leq x_i \leq 30$）是一个不超过 30 的正整数。

完成所有修改查询后，需要输出最终的数组。

### 说明/提示
在第一个测试用例中，第一次查询会将 2 加到位置 4 和 5 的整数上。这次加法操作后，数组将变为 $[1, 2, 3, 6, 6]$。其他操作不会修改该数组。

在第二个测试用例中，第一次修改查询不会改变数组。第二次修改查询会将 8 加到位置 5 的整数上，因此数组将变为 $[7, 8, 12, 36, 56, 6, 3]$。第三次修改查询会将 2 加到位置 2、3、4 和 5 的整数上。然后数组将变为 $[7, 10, 14, 38, 58, 6, 3]$。

### 样例 #1
#### 输入
```
4
5 3
1 2 3 4 4
2 3 4
7 3
7 8 12 36 48 6 3
10 4 2
5 4
2 2 2 2 2
1 1 1 1
5 5
1 2 4 8 16
5 2 3 4 1
```

#### 输出
```
1 2 3 6 6 
7 10 14 38 58 6 3 
3 3 3 3 3 
1 3 7 11 19
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用一个关键性质：若一个数是 $2^x$ 的倍数，加上 $2^{x - 1}$ 后就不再是 $2^x$ 及更高次幂的倍数，而只是 $2^{x - 1}$ 的倍数。基于此性质，各题解采用了不同的数据结构和方法来优化模拟过程。

### 所选题解
- **作者：_mi_ka_ (5星)**
    - **关键亮点**：思路清晰，使用队列维护 $2^i$ 的倍数的下标，复杂度分析明确，代码可读性高，有快读快写优化。
    - **核心代码**：
```cpp
queue<int>que[31];//第i个队列存2^i的倍数 
while(T--)
{
    n=re(),q=re();
    for(int i=1;i<=n;i++)
    {
        a[i]=re();
        int l=0;
        for(;l<=30;l++)
            if(a[i]%(1<<l))
                break;
        que[l-1].push(i);
    }
    while(q--)
    {
        int x=re();
        for(int i=30;i>=x;i--)
            while(que[i].size())
            {
                int now=que[i].front();
                que[i].pop();
                a[now]+=(1<<(x-1));
                que[x-1].push(now);
            }
    }
    for(int i=1;i<=n;i++)
        wr(a[i]),putchar(' ');
    putchar('\n');
    for(int i=1;i<=30;i++)
        while(que[i].size())
            que[i].pop();
}
```
    - **核心实现思想**：先将每个数能被整除的最大的 $2^l$ 的 $l - 1$ 对应的队列中加入该数的下标。每次操作时，取出大于等于 $x$ 的队列中的下标，更新数组元素，并将其放入 $x - 1$ 的队列中。
- **作者：qzhwlzy (4星)**
    - **关键亮点**：思路简洁，利用二进制性质优化，代码简洁易懂，复杂度低。
    - **核心代码**：
```cpp
while(T--){
    scanf("%d%d",&n,&q); for(int i=1;i<=n;i++) scanf("%d",&a[i]); las=-1;
    while(q--){
        scanf("%d",&x); if(x<las||las==-1)
            {las=x; for(int i=1;i<=n;i++) if(a[i]%(1<<x)==0) a[i]+=(1<<(x-1));}
    } for(int i=1;i<=n;i++) printf("%d%c",a[i]," \n"[i==n]);
}
```
    - **核心实现思想**：发现真正有用的 $x$ 一定是递减的，只处理递减的 $x$，遍历数组更新满足条件的元素。
- **作者：66xyyd (4星)**
    - **关键亮点**：从二进制角度分析问题，通过存储单调递增的修改序列优化操作，代码简洁。
    - **核心代码**：
```cpp
while(T--){
    q[0]=114;
    cnt=0;
    cin >> n >> qq;
    for (int i=1;i<=n;i++){
        cin>>a[i];
    }
    for (int i=1;i<=qq;i++){
        int x;
        cin>>x;
        if (x<q[cnt]){
            cnt++;
            q[cnt]=x;
        }
    }
    for (int i=1;i<=n;i++){
        for(int j=1;j<=cnt;j++){
            if(a[i]%(1<<q[j])==0){
                a[i]+=(1<<(q[j]-1));
            }
        }
        cout << a[i] << ' ';
    }
    cout << '\n';
}
```
    - **核心实现思想**：存储单调递增的修改序列，对每个存下来的 $x$ 遍历数组更新满足条件的元素。

### 最优关键思路或技巧
- 利用数论性质：若一个数是 $2^x$ 的倍数，加上 $2^{x - 1}$ 后就不再是 $2^x$ 及更高次幂的倍数，从而减少不必要的操作。
- 从二进制角度分析问题，将数的整除问题转化为二进制位的特征，简化判断和操作。
- 存储有效的操作序列（如单调递减的 $x$），避免重复操作。

### 可拓展之处
同类型题可能会改变操作的规则，例如修改为加上其他数或者进行其他运算，但核心思路都是利用数的整除性质和二进制特征进行优化。类似算法套路可以应用到涉及数的倍数、余数、二进制表示等问题中。

### 推荐题目
- [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：简单的模拟题，锻炼基本的编程实现能力。
- [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)：涉及数组的操作和模拟，巩固基础。
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：需要合理的模拟和判断，提升逻辑思维能力。

### 个人心得
题解中无个人心得相关内容。

---
处理用时：46.10秒