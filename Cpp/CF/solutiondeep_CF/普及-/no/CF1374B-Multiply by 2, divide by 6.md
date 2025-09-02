# 题目信息

# Multiply by 2, divide by 6

## 题目描述

You are given an integer $ n $ . In one move, you can either multiply $ n $ by two or divide $ n $ by $ 6 $ (if it is divisible by $ 6 $ without the remainder).

Your task is to find the minimum number of moves needed to obtain $ 1 $ from $ n $ or determine if it's impossible to do that.

You have to answer $ t $ independent test cases.

## 说明/提示

Consider the sixth test case of the example. The answer can be obtained by the following sequence of moves from the given integer $ 15116544 $ :

1. Divide by $ 6 $ and get $ 2519424 $ ;
2. divide by $ 6 $ and get $ 419904 $ ;
3. divide by $ 6 $ and get $ 69984 $ ;
4. divide by $ 6 $ and get $ 11664 $ ;
5. multiply by $ 2 $ and get $ 23328 $ ;
6. divide by $ 6 $ and get $ 3888 $ ;
7. divide by $ 6 $ and get $ 648 $ ;
8. divide by $ 6 $ and get $ 108 $ ;
9. multiply by $ 2 $ and get $ 216 $ ;
10. divide by $ 6 $ and get $ 36 $ ;
11. divide by $ 6 $ and get $ 6 $ ;
12. divide by $ 6 $ and get $ 1 $ .

## 样例 #1

### 输入

```
7
1
2
3
12
12345
15116544
387420489```

### 输出

```
0
-1
2
-1
-1
12
36```

# AI分析结果

### 题目内容
# 乘2，除以6

## 题目描述
给定一个整数 $n$ 。在一次操作中，你可以将 $n$ 乘以2，或者将 $n$ 除以6（前提是 $n$ 能被6整除且没有余数）。

你的任务是找出从 $n$ 得到1所需的最小操作次数，或者确定这是不可能的。

你必须回答 $t$ 个独立的测试用例。

## 说明/提示
考虑示例中的第六个测试用例。从给定的整数15116544可以通过以下操作序列得到答案：
1. 除以6得到2519424；
2. 除以6得到419904；
3. 除以6得到69984；
4. 除以6得到11664；
5. 乘以2得到23328；
6. 除以6得到3888；
7. 除以6得到648；
8. 除以6得到108；
9. 乘以2得到216；
10. 除以6得到36；
11. 除以6得到6；
12. 除以6得到1。

## 样例 #1
### 输入
```
7
1
2
3
12
12345
15116544
387420489
```
### 输出
```
0
-1
2
-1
-1
12
36
```
### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是围绕数字 $n$ 的质因子展开。因为操作涉及乘以2和除以6（$6 = 2×3$），所以关键在于分析 $n$ 中2和3的质因子个数情况。若 $n$ 存在除2和3以外的质因子，或者2的质因子个数多于3的质因子个数，那么无法通过给定操作得到1。若2的质因子个数少于或等于3的质因子个数，则可以计算出最少操作次数。各题解的主要区别在于具体实现方式和对逻辑的表达。

### 所选的题解
- **作者：江户川·萝卜 (6赞)  星级：4星**
    - **关键亮点**：思路清晰，直接从操作对数字的影响出发，通过循环判断 $n$ 是否能被3整除，再根据能否被2整除来决定操作及操作次数的累加，代码简洁明了。
    - **重点代码及核心实现思想**：
```cpp
while(n%3==0){
    if(n%2==0) step++,n/=6;
    else step+=2,n/=3;
}
if(n>1) printf("-1\n");
else printf("%d\n",step);
```
核心思想是不断对 $n$ 进行操作，能直接除以6时操作次数加1并更新 $n$，不能直接除以6时通过乘2再除以6（操作次数加2）的方式更新 $n$，最后判断 $n$ 是否为1来决定输出结果。
- **作者：_cmh (5赞)  星级：4星**
    - **关键亮点**：代码简洁高效，先分别处理能直接除以6和能除以3的情况，最后判断 $n$ 是否为1输出结果，逻辑清晰。
    - **重点代码及核心实现思想**：
```cpp
while(n%6==0) ans++,n/=6;
while(n%3==0) ans+=2,n/=3;
if(n==1) cout<<ans<<endl;
else cout<<"-1\n";
```
先尽可能地将 $n$ 除以6，再处理只能除以3的情况，根据最终 $n$ 是否为1输出答案。
- **作者：xixike (2赞)  星级：4星**
    - **关键亮点**：通过函数分别计算2和3的质因子个数，根据质因子个数关系直接得出结果，逻辑严谨。
    - **重点代码及核心实现思想**：
```cpp
int get_yinzi(int p){
    int res=0;
    while(tmp%p==0){
        res++;
        tmp/=p;
    }
    return res;
}
//...
int x2=get_yinzi(2);
int x3=get_yinzi(3);
if(x2>x3||tmp!=1){
    printf("-1\n");
    continue;
}
printf("%d\n",x2+2*(x3-x2));
```
通过 `get_yinzi` 函数获取2和3的质因子个数，根据质因子个数关系判断能否得到1并计算操作次数。

### 最优关键思路或技巧
核心思路是分析数字 $n$ 的质因子情况，利用 $6 = 2×3$ 的特性，通过判断2和3的质因子个数关系来确定能否得到1以及计算最少操作次数。这种基于数论中质因子分析的思维方式是解决此类问题的关键。

### 可拓展之处
同类型题通常围绕数字的特定操作和性质展开，类似算法套路是对给定操作涉及的数字进行质因数分解，分析质因子之间的关系来解决问题。例如，给定其他特定的乘除操作，分析操作数的质因子，判断能否通过操作达到目标值并计算最少操作次数。

### 洛谷相似题目
- [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)：通过对数字进行质因数分解来解决问题，与本题分析质因子思路类似。
- [P1572 计算分数](https://www.luogu.com.cn/problem/P1572)：涉及分数的化简等操作，需要对分子分母进行质因数相关分析，和本题利用数论知识解决问题的思路相符。
- [P2681 求和](https://www.luogu.com.cn/problem/P2681)：通过对数字的整除性质和质因子等数论知识进行分析求解。 

---
处理用时：43.79秒