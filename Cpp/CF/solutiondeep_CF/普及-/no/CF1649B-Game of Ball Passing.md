# 题目信息

# Game of Ball Passing

## 题目描述

Daniel is watching a football team playing a game during their training session. They want to improve their passing skills during that session.

The game involves $ n $ players, making multiple passes towards each other. Unfortunately, since the balls were moving too fast, after the session Daniel is unable to know how many balls were involved during the game. The only thing he knows is the number of passes delivered by each player during all the session.

Find the minimum possible amount of balls that were involved in the game.

## 说明/提示

In the first test case, with the only ball, the game can go like this:

 $ 2 \rightarrow 1 \rightarrow 3 \rightarrow 4 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 2 \rightarrow 3 \rightarrow 2 $ .

In the second test case, there is no possible way to play the game with only one ball. One possible way to play with two balls:

 $ 2 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 1 $ .

 $ 2 \rightarrow 3 \rightarrow 2 \rightarrow 1 $

In the third example, there were no passes, so $ 0 $ balls are possible.

## 样例 #1

### 输入

```
4
4
2 3 3 2
3
1 5 2
2
0 0
4
1000000000 1000000000 1000000000 1000000000```

### 输出

```
1
2
0
1```

# AI分析结果

### 题目内容
# 传球游戏

## 题目描述
丹尼尔正在观看一支足球队在训练期间进行的一场比赛。在那期间，他们想提高传球技巧。

这个游戏涉及$n$名球员，他们相互之间进行多次传球。不幸的是，由于球移动得太快，训练结束后丹尼尔无法知道比赛中涉及了多少个球。他唯一知道的是每个球员在整个训练期间的传球次数。

求比赛中可能涉及的最小球数。

## 说明/提示
在第一个测试用例中，仅用一个球，比赛可以这样进行：
$2 \rightarrow 1 \rightarrow 3 \rightarrow 4 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 2 \rightarrow 3 \rightarrow 2$。

在第二个测试用例中，仅用一个球不可能完成比赛。用两个球的一种可能方式：
$2 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 1$。
$2 \rightarrow 3 \rightarrow 2 \rightarrow 1$

在第三个示例中，没有传球，所以$0$个球是可能的。

## 样例 #1
### 输入
```
4
4
2 3 3 2
3
1 5 2
2
0 0
4
1000000000 1000000000 1000000000 1000000000
```
### 输出
```
1
2
0
1
```
### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过比较传球次数最多的球员的传球次数与其他球员传球次数总和的关系来确定最少球数。难点在于理解如何通过这种比较得出球数，以及证明一些特殊情况（如总和大于最大传球次数时为何只需一个球）。各题解思路基本一致，只是在表述和推导过程略有差异。

### 所选的题解
- **作者：Lyr_ids (5星)**
    - **关键亮点**：思路清晰，先将问题简化，把踢球数最多的球员单拎出来分析，分情况讨论并给出详细证明，代码简洁明了。
    - **个人心得**：无
    ```cpp
    read(n);
    sum=0;
    int tmp=0;
    for(int i=0;i<n;++i)
    {
        read(a[i]);
        sum+=a[i];
        tmp=max(tmp,a[i]);
    }
    sum-=tmp;
    if(tmp==0)
    {
        puts("0");
        continue;
    }
    if(sum>=tmp)
        puts("1");
    else
        printf("%d\n",(int)tmp-(int)sum);
    ```
    - **核心代码简述**：先读入人数和每个人传球次数，求出总和与最大值，减去最大值后判断剩余总和与最大值关系得出球数。
- **作者：0xFF (5星)**
    - **关键亮点**：通过观察总结出规律，从传球总数和最大传球数的关系入手分析，逻辑严谨，代码实现完整规范。
    - **个人心得**：无
    ```cpp
    #include<iostream>
    using namespace std;
    int t,n;
    int main(){
        cin>>t;
        for(int i=1;i<=t;i++){
            cin>>n;
            long long sum=0;
            int a;
            int maxn=0;
            for(int i=1;i<=n;i++){
                cin>>a;
                sum+=a;
                maxn=max(maxn,a);
            }
            if(sum==0){
                cout<<0;
            }
            else if(maxn*2<=sum){
                cout<<1;
            }
            else{
                cout<<2*maxn-sum;
            }
            cout<<endl;
        }
        return 0;
    }
    ```
    - **核心代码简述**：读入测试组数和人数、传球次数，计算总和与最大值，根据总和与最大传球数两倍的关系输出球数。
- **作者：Aya_tt (4星)**
    - **关键亮点**：直接点明解题突破口在于把球传给传球次数最多的人，简洁地概括了解题关键思路。
    - **个人心得**：无
    - **核心代码简述**：无代码，但思路为统计总和与最大传球数，根据两者关系及传球次数为0的特判得出球数。

### 最优关键思路或技巧
将传球次数最多的球员单独考虑，与其他球员传球次数总和进行比较。利用贪心思想，让球尽可能在球员间高效传递，优先满足传球次数多的球员，通过这种方式确定最少球数。

### 同类型题或类似算法套路
此类题目通常是通过对数据特征（如最大、最小、总和等）的分析，利用贪心策略解决问题。类似套路是找到关键数据（如本题的最大传球次数），与其他相关数据（如传球次数总和）对比，根据不同情况得出结果。

### 洛谷推荐题目
- **P1090 [NOIP2004 提高组] 合并果子**：通过贪心策略选择最小的两堆果子合并，与本题通过比较关键数据确定结果思路类似。
- **P1223 排队接水**：根据接水时间贪心排序，确定最优排队顺序，同样是利用贪心解决实际问题。
- **P1080 [NOIP2012 提高组] 国王游戏**：通过对数据的分析，利用贪心策略确定最优排列顺序，与本题分析关键数据关系解题类似。 

---
处理用时：37.42秒