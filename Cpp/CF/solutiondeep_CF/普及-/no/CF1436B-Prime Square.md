# 题目信息

# Prime Square

## 题目描述

Sasha likes investigating different math objects, for example, magic squares. But Sasha understands that magic squares have already been studied by hundreds of people, so he sees no sense of studying them further. Instead, he invented his own type of square — a prime square.

A square of size $ n \times n $ is called prime if the following three conditions are held simultaneously:

- all numbers on the square are non-negative integers not exceeding $ 10^5 $ ;
- there are no prime numbers in the square;
- sums of integers in each row and each column are prime numbers.

Sasha has an integer $ n $ . He asks you to find any prime square of size $ n \times n $ . Sasha is absolutely sure such squares exist, so just help him!

## 样例 #1

### 输入

```
2
4
2```

### 输出

```
4 6 8 1
4 9 9 9
4 10 10 65
1 4 4 4
1 1
1 1```

# AI分析结果

### 题目内容
# 质数方阵

## 题目描述
萨沙喜欢研究不同的数学对象，例如幻方。但萨沙明白幻方已经被成百上千的人研究过了，所以他觉得没有必要再进一步研究它们。相反，他发明了自己的一种方阵——质数方阵。

一个 $n \times n$ 的方阵被称为质数方阵，如果同时满足以下三个条件：
- 方阵中的所有数都是不超过 $10^5$ 的非负整数；
- 方阵中不存在质数；
- 每行和每列的整数之和都是质数。

萨沙有一个整数 $n$ 。他请你找出任意一个大小为 $n \times n$ 的质数方阵。萨沙非常确定这样的方阵是存在的，所以帮帮他吧！

## 样例 #1
### 输入
```
2
4
2
```
### 输出
```
4 6 8 1
4 9 9 9
4 10 10 65
1 4 4 4
1 1
1 1
```

### 算法分类
构造

### 题解综合分析与结论
这些题解的共同目标是构造满足特定条件的 $n \times n$ 方阵。主要思路围绕使用非质数（如0和1）来构建方阵，使每行每列和为质数。
- **思路方面**：多数题解利用0和1的特性构造方阵。部分题解针对 $n$ 的奇偶性分别处理；有的通过固定每行每列1的数量来保证和为质数；还有通过移动一行数字构造整个方阵。
- **算法要点**：利用非质数0和1构造，关注每行每列和的质数性质。部分题解需筛出质数表，或通过特定规则修改方阵元素使和为质数。
- **解决难点**：难点在于如何巧妙利用非质数构造出满足行列和为质数的方阵。不同题解从不同角度突破，如利用0和1组合、按 $n$ 奇偶性构造、移动行元素等。

### 所选的题解
- **作者：45dinо (5星)**
    - **关键亮点**：思路简洁清晰，直接利用0和1构造，通过特定规则使每行每列恰有两个1，保证和为2（质数），代码实现简单高效。
    - **重点代码核心实现思想**：通过两层循环遍历方阵位置，根据条件判断输出0或1 。
    ```cpp
    for(int i=1;i<=n;i++)
    {
        for(int l=1;l<=n;l++)
            if(l==i||l==i%n+1)
                cout<<1<<" ";
            else
                cout<<0<<" ";
        cout<<endl;
    }
    ```
- **作者：tuzhewen (4星)**
    - **关键亮点**：先将方阵全填1 ，根据 $n$ 是否为质数进行不同处理，通过找大于 $n$ 的质数作为行和并调整元素值，逻辑清晰，方法巧妙。
    - **重点代码核心实现思想**：先筛出质数表，然后循环找合适的行和 $sum$ ，并调整对角线元素使每行每列和为 $sum$ 。
    ```cpp
    do{
        int pos=upper_bound(prime+1,prime+1+cnt,sum)-prime;
        sum=prime[pos];
    }while(isp[sum-n+1]);
    F(i,1,n) a[i][i]=sum-n+1;
    ```
- **作者：Werner_Yin (4星)**
    - **关键亮点**：通过观察发现一种简单固定的01排列方式构造方阵，满足行列和为质数条件，思路直接，实现容易。
    - **重点代码核心实现思想**：通过两层循环遍历方阵位置，按特定条件输出0或1 。
    ```cpp
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++)
            if(j == i+1||j == i||(j == 1&&i==n)) printf("1 ");
            else printf("0 ");
        puts("");
    }
    ```

### 最优关键思路或技巧
利用非质数0和1的特性来构造方阵是关键技巧。通过巧妙设计0和1的分布，如固定每行每列1的数量、按特定规则在对角线上放置1等，使每行每列和满足质数要求。同时，对于 $n$ 的不同情况（奇偶性或是否为质数）进行分类讨论处理，能更有条理地解决问题。

### 同类型题或类似算法套路拓展
此类题目属于构造类问题，常见套路是先观察题目条件，寻找特殊数字或规律，利用这些特殊性质来构建满足要求的结构。例如在构造矩阵、序列等问题中，从简单情况入手，分析数字特性（如奇偶性、质数合数性质等），通过分类讨论、逐步调整来完成构造。

### 洛谷相似知识点题目推荐
- [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)：涉及构造与搜索相关知识，通过构造01迷宫探索路径。
- [P1421 小玉买文具](https://www.luogu.com.cn/problem/P1421)：可看作简单构造问题，根据给定条件构造计算逻辑。
- [P2670 扫雷游戏](https://www.luogu.com.cn/problem/P2670)：通过构造扫雷矩阵，依据规则进行计算和判断。 

---
处理用时：45.75秒