# 题目信息

# Levko and Table

## 题目描述

Levko loves tables that consist of $ n $ rows and $ n $ columns very much. He especially loves beautiful tables. A table is beautiful to Levko if the sum of elements in each row and column of the table equals $ k $ .

Unfortunately, he doesn't know any such table. Your task is to help him to find at least one of them.

## 说明/提示

In the first sample the sum in the first row is $ 1+3=4 $ , in the second row — $ 3+1=4 $ , in the first column — $ 1+3=4 $ and in the second column — $ 3+1=4 $ . There are other beautiful tables for this sample.

In the second sample the sum of elements in each row and each column equals $ 7 $ . Besides, there are other tables that meet the statement requirements.

## 样例 #1

### 输入

```
2 4
```

### 输出

```
1 3
3 1
```

## 样例 #2

### 输入

```
4 7
```

### 输出

```
2 1 0 4
4 0 2 1
1 3 3 0
0 3 2 2
```

# AI分析结果

### 题目内容
# Levko和表格
## 题目描述
Levko非常喜欢由$n$行和$n$列组成的表格。他尤其喜欢漂亮的表格。对于Levko来说，如果表格中每行和每列的元素之和都等于$k$，那么这个表格就是漂亮的。
不幸的是，他不知道任何这样的表格。你的任务是帮助他至少找到一个这样的表格。
## 说明/提示
在第一个样例中，第一行的和是$1 + 3 = 4$，第二行是$3 + 1 = 4$，第一列是$1 + 3 = 4$，第二列是$3 + 1 = 4$。对于这个样例还有其他漂亮的表格。
在第二个样例中，每行和每列的元素之和都等于$7$。此外，还有其他满足题目要求的表格。
## 样例 #1
### 输入
```
2 4
```
### 输出
```
1 3
3 1
```
## 样例 #2
### 输入
```
4 7
```
### 输出
```
2 1 0 4
4 0 2 1
1 3 3 0
0 3 2 2
```
### 算法分类
构造
### 综合分析与结论
这些题解的核心思路基本一致，都是通过构造一个特殊的矩阵来满足每行每列和为$k$的要求。大多数题解选择在矩阵的对角线上放置$k$，其余位置为$0$，这种构造方式简单直接，容易理解和实现。少部分题解如“ttq012”通过随机打乱位置来尝试构造满足条件的矩阵，但相对复杂且没有必要。整体来看，各题解思路清晰，主要差异在于代码风格和细节处理。
### 所选的题解
- **作者：zhang_kevin（5星）**
    - **关键亮点**：思路阐述清晰，先简述题意，再详细说明解题思路，通过对矩阵的观察得出简洁构造方法，代码简洁明了。
    - **重点代码**：
```cpp
#include<cstdio>
int main(){
    int n, k;
    scanf("%d %d", &n, k);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i == j){
                printf("%d ", k);
            }else{
                printf("0 ");
            }
        }
        printf("\n");
    }
    return 0;
}
```
核心实现思想：通过两层循环遍历矩阵的每一个位置，当行号等于列号时输出$k$，否则输出$0$，从而构造出满足条件的矩阵。
- **作者：REAL_曼巴（4星）**
    - **关键亮点**：以模拟题角度出发，语言通俗易懂，结合图片辅助理解，代码简洁且注释详细。
    - **重点代码**：
```cpp
#include <iostream>
using namespace std;
int n,k;
int main (){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)
                cout<<k<<' ';
            else
                cout<<'0'<<' ';
        }
        cout<<endl;
    }
    return 0;
}
```
核心实现思想：与上一题解类似，利用循环嵌套遍历矩阵位置，根据行列号是否相等决定输出$k$还是$0$。
- **作者：zbk233（4星）**
    - **关键亮点**：解题思路简洁清晰，先将矩阵初始化为$0$，再把对角线元素设为$k$，代码简洁高效。
    - **重点代码**：
```cpp
#include<iostream>
using namespace std;
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++,putchar('\n'))
        for(int j=1;j<=n;j++)
            cout<<(i==j?k:0)<<' ';
    return 0;
}
```
核心实现思想：通过循环嵌套遍历矩阵，利用三元运算符简洁地判断并输出对应位置的值，当行列号相等时输出$k$，否则输出$0$。
### 最优关键思路或技巧
构造特殊矩阵时，利用对角线元素的行列号相等这一特性，将$k$放置在对角线上，其余位置设为$0$，这种简单直接的构造方法能高效满足题目要求，大大简化了问题的解决过程。
### 可拓展之处
此类题目属于构造类问题，常见的类似套路是根据题目给定的条件，寻找一种简单且符合要求的规律来构造数据结构。同类型题可能会改变矩阵的限制条件，如要求构造一个每行和为$k$，每列和为$m$（$k\neq m$）的矩阵，或者对矩阵元素有其他限制等。
### 洛谷推荐题目
- [P1163 银行贷款](https://www.luogu.com.cn/problem/P1163)：通过构造合适的还款计划来满足题目条件，涉及简单的数学构造。
- [P1422 小玉家的电费](https://www.luogu.com.cn/problem/P1422)：根据不同电量区间的收费标准构造计算电费的方法。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过分析不同包装铅笔的价格和所需数量，构造出最省钱的购买方案。 

---
处理用时：49.17秒