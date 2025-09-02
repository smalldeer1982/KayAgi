# 题目信息

# Cheese Board

## 题目描述

Not to be confused with [chessboard](https://en.wikipedia.org/wiki/Chessboard).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF952E/d088bd192ec24adc1aa0fd2afc4c2fb2b7ee4531.png)

## 样例 #1

### 输入

```
9
brie soft
camembert soft
feta soft
goat soft
muenster soft
asiago hard
cheddar hard
gouda hard
swiss hard
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6
parmesan hard
emmental hard
edam hard
colby hard
gruyere hard
asiago hard
```

### 输出

```
4
```

# AI分析结果

### 题目内容
# 奶酪板

## 题目描述
不要与[棋盘](https://en.wikipedia.org/wiki/Chessboard)混淆。
![奶酪板示意图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF952E/d088bd192ec24adc1aa0fd2afc4c2fb2b7ee4531.png)

## 样例 #1
### 输入
```
9
brie soft
camembert soft
feta soft
goat soft
muenster soft
asiago hard
cheddar hard
gouda hard
swiss hard
```
### 输出
```
3
```

## 样例 #2
### 输入
```
6
parmesan hard
emmental hard
edam hard
colby hard
gruyere hard
asiago hard
```
### 输出
```
4
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是先统计软、硬奶酪的数量，找出数量较多的那种奶酪，然后从小到大枚举棋盘边长，判断该边长的棋盘是否能满足放置所有奶酪且相同类型奶酪不相邻的条件。判断条件主要有两个：一是棋盘面积要大于等于奶酪总数；二是棋盘上可放置不相邻格子的数量（边长为偶数时是棋盘面积的一半，边长为奇数时是（棋盘面积 + 1）的一半）要大于等于数量较多的那种奶酪的个数。

不同题解在代码实现细节上有所差异，如输入方式、变量命名、判断条件的写法等，但整体思路基本一致。

### 所选的题解
- **作者：郑朝曦zzx (5星)**
    - **关键亮点**：思路清晰，先明确解题的两个步骤，对判断是否有解的条件阐述详细，代码简洁明了。
    - **重点代码核心实现思想**：先通过循环统计软、硬奶酪个数并找出较多的数量，再通过循环枚举边长，根据上述两个判断条件确定满足要求的最小边长。
    ```cpp
    for (int i = 1; i <= n; ++i)
    {
        cin >> s1 >> s2;
        if (s2 == "soft") ++s;
        else ++h;
    }
    if (s > h) mx = s;
    else mx = h;
    for (int i = 1; i <= n; ++i)
    {
        int k = (i * i + 1) >> 1;
        if (i * i >= n && k >= mx)
        {
            printf("%d\n", i);
            return 0;
        }
    }
    ```
- **作者：Tan_Wei_Ye (4星)**
    - **关键亮点**：代码简短精炼，直接抓住核心思路，简洁地实现了从小到大枚举棋盘大小并判断是否合法。
    - **重点代码核心实现思想**：与上述类似，先统计软、硬奶酪数量并找出较大值，然后通过循环枚举边长，根据条件判断找到符合要求的边长。
    ```cpp
    for(int i=1;(i*i+1)/2<x || i*i<soft+hard;i++) ;
    cout<<i<<endl;
    ```
- **作者：ivyjiao (4星)**
    - **关键亮点**：解题步骤清晰，对每一步的思路和实现都有详细说明，代码结构清晰易懂。
    - **重点代码核心实现思想**：先统计软、硬奶酪数量并找出较大值，再通过循环枚举边长，依据两个判断条件确定最小边长。
    ```cpp
    for(int i=1;i<=n;i++){
        int k=(i*i+1)/2;
        if(i*i>=n&&k>=maxn){
            cout<<i<<endl;
            return 0;
        }
    }
    ```

### 最优关键思路或技巧
通过分析棋盘放置奶酪的特性，得出判断棋盘是否满足放置条件的两个关键数学条件，然后利用枚举的方法，从小到大尝试棋盘边长，这种结合数学分析与枚举的方式高效解决了问题。

### 可拓展之处
同类型题通常围绕在给定条件下寻找最小或最优的某种容器或布局，类似算法套路是先通过分析问题得出关键的判断条件，再利用枚举等方法去尝试不同的可能值。

### 洛谷相似题目推荐
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：通过枚举菜品组合判断是否满足预算，与本题枚举棋盘边长判断是否满足放置奶酪条件类似。
- [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：通过枚举天数判断是否达到目标距离，与本题枚举棋盘边长判断是否满足条件思路相近。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过枚举不同包装铅笔的购买数量组合，判断是否满足需求且花费最小，与本题枚举思路类似。 

---
处理用时：41.01秒