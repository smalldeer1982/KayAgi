# 题目信息

# Engineer Artem

## 题目描述

Artem is building a new robot. He has a matrix $ a $ consisting of $ n $ rows and $ m $ columns. The cell located on the $ i $ -th row from the top and the $ j $ -th column from the left has a value $ a_{i,j} $ written in it.

If two adjacent cells contain the same value, the robot will break. A matrix is called good if no two adjacent cells contain the same value, where two cells are called adjacent if they share a side.

Artem wants to increment the values in some cells by one to make $ a $ good.

More formally, find a good matrix $ b $ that satisfies the following condition —

- For all valid ( $ i,j $ ), either $ b_{i,j} = a_{i,j} $ or $ b_{i,j} = a_{i,j}+1 $ .

For the constraints of this problem, it can be shown that such a matrix $ b $ always exists. If there are several such tables, you can output any of them. Please note that you do not have to minimize the number of increments.

## 说明/提示

In all the cases, you can verify that no two adjacent cells have the same value and that $ b $ is the same as $ a $ with some values incremented by one.

## 样例 #1

### 输入

```
3
3 2
1 2
4 5
7 8
2 2
1 1
3 3
2 2
1 3
2 2```

### 输出

```
1 2
5 6
7 8
2 1
4 3
2 4
3 2```

# AI分析结果

### 题目内容重写
Artem正在建造一个新的机器人。他有一个由$n$行$m$列组成的矩阵$a$。矩阵中位于第$i$行第$j$列的单元格中的值为$a_{i,j}$。

如果两个相邻的单元格包含相同的值，机器人就会损坏。一个矩阵被称为“好的”，当且仅当没有任何两个相邻的单元格包含相同的值，其中两个单元格相邻指的是它们共享一条边。

Artem希望通过将某些单元格的值增加1来使矩阵$a$变成“好的”矩阵。

更正式地说，找到一个“好的”矩阵$b$，满足以下条件：
- 对于所有有效的$(i,j)$，要么$b_{i,j} = a_{i,j}$，要么$b_{i,j} = a_{i,j}+1$。

对于这个问题，可以证明这样的矩阵$b$总是存在。如果有多个这样的矩阵，输出任意一个即可。注意，你不需要最小化增加的次数。

### 算法分类
构造

### 题解分析与结论
本题的核心思路是通过改变矩阵中元素的奇偶性，使得相邻元素的奇偶性不同，从而保证它们不相等。由于奇数和偶数不可能相等，因此通过将矩阵中的元素按照棋盘式的奇偶性排列，可以轻松满足题目的要求。大多数题解都采用了这一思路，通过判断每个元素的奇偶性是否与$(i+j)$的奇偶性相同来决定是否对其进行加一操作。

### 评分较高的题解
#### 1. 作者：彭天宇 (赞：14)
**星级：5星**
**关键亮点：** 通过棋盘式的奇偶性排列，确保相邻元素的奇偶性不同，从而保证它们不相等。思路清晰，代码简洁。
**个人心得：** 通过$+1$操作改变元素的奇偶性，确保相邻元素的奇偶性不同，这种方法非常巧妙且易于实现。

**核心代码：**
```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
        s[i][j]=read();
        if((i+j)%2==0&&s[i][j]%2==0)s[i][j]++;
        if((i+j)%2==1&&s[i][j]%2==1)s[i][j]++;
    }
```

#### 2. 作者：XL4453 (赞：1)
**星级：4星**
**关键亮点：** 通过判断每个元素的奇偶性是否与$(i+j)$的奇偶性相同来决定是否对其进行加一操作，代码简洁且高效。
**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        scanf("%d",&x);
        if((i+j)%2==0)x+=(x%2==0);
        else x+=(x%2==1);
        printf("%d ",x);
    }
    printf("\n");
}
```

#### 3. 作者：ZettaByte (赞：0)
**星级：4星**
**关键亮点：** 通过判断$a_{i,j}$的奇偶性是否与$i+j$相同来决定是否增加1，思路清晰，代码简洁。
**核心代码：**
```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        if(a[i][j]%2!=(i+j)%2) a[i][j]++;
```

### 最优关键思路或技巧
通过改变矩阵中元素的奇偶性，使得相邻元素的奇偶性不同，从而保证它们不相等。这种方法简单高效，且易于实现。

### 可拓展之处
类似的问题可以通过改变元素的某些属性（如奇偶性、模数等）来确保相邻元素不相等。例如，可以通过模3、模4等来进一步扩展问题。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：35.20秒