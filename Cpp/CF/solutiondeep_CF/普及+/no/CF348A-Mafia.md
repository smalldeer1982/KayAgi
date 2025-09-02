# 题目信息

# Mafia

## 题目描述

One day $ n $ friends gathered together to play "Mafia". During each round of the game some player must be the supervisor and other $ n-1 $ people take part in the game. For each person we know in how many rounds he wants to be a player, not the supervisor: the $ i $ -th person wants to play $ a_{i} $ rounds. What is the minimum number of rounds of the "Mafia" game they need to play to let each person play at least as many rounds as they want?

## 说明/提示

You don't need to know the rules of "Mafia" to solve this problem. If you're curious, it's a game Russia got from the Soviet times: http://en.wikipedia.org/wiki/Mafia\_(party\_game).

## 样例 #1

### 输入

```
3
3 2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
2 2 2 2
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# Mafia

## 题目描述
一天，$n$个朋友聚在一起玩“黑手党”游戏。在每一轮游戏中，必须有一名玩家担任监督者，其余$n - 1$人参与游戏。对于每个人，我们知道他想作为玩家而非监督者参与游戏的轮数：第$i$个人想玩$a_{i}$轮。他们最少需要玩多少轮“黑手党”游戏，才能让每个人至少玩到他们想要的轮数？

## 说明/提示
解决这个问题不需要知道“黑手党”游戏的规则。如果你好奇，这是一款俄罗斯从苏联时期传承下来的游戏：http://en.wikipedia.org/wiki/Mafia_(party_game)。

## 样例 #1
### 输入
```
3
3 2 2
```
### 输出
```
4
```

## 样例 #2
### 输入
```
4
2 2 2 2
```
### 输出
```
3
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕如何确定满足每个人游戏轮数需求的最少游戏轮数。部分题解采用二分答案的方法，利用问题的单调性，通过不断缩小范围来找到最小满足条件的轮数；多数题解则基于数学方法，先计算所有人想玩游戏的总轮数，除以每轮可参与游戏的人数$n - 1$，并向上取整得到一个初步结果，再与所有人中想玩游戏轮数的最大值比较，取两者中的较大值作为最终答案。难点在于考虑到简单计算总轮数除以$n - 1$可能出现的结果小于想玩游戏轮数最多的人的情况，需要进行特殊处理。

### 所选的题解
- **作者：LRL65 (5星)**
    - **关键亮点**：思路清晰简洁，直接采用$O(n)$时间复杂度的数学方法，先累加每个人想玩的轮数，除以$n - 1$并处理余数，再与最大值比较得出结果，代码实现简洁明了。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    long long n,a,s=0,maxn=0;//记得开long long
    int main(){
        cin>>n;
        for(int i=1;i<=n;i++) {
            cin>>a;//输入
            s+=a;//累加
            maxn=max(maxn,a);//找最大
        }
        n=n-1;
        if(s%n==0)s/=n;else s=s/n+1;
        if(s<maxn)s=maxn;
        cout<<s<<endl;//输出
    }
    ```
    - **核心实现思想**：先读入人数$n$和每个人想玩的轮数$a$，累加得到总轮数$s$并找出最大值$maxn$。然后计算总轮数除以$n - 1$的结果，若能整除则直接赋值给$s$，否则向上取整。最后比较$s$和$maxn$，取较大值输出。
- **作者：Starlight237 (4星)**
    - **关键亮点**：利用二分答案的思路，明确问题的单调性，通过合理确定二分的取值范围，不断缩小范围找到满足条件的最小轮数，代码逻辑清晰。
    ```cpp
    #include<bits/stdc++.h>
    #define reg register
    using namespace std;
    static int a[100000],n;
    static long long ma,si;
    int main(){
        scanf("%d",&n);
        for(reg int i=0;i<n;++i)
            scanf("%d",a+i),ma=max(int(ma),a[i]),si+=a[i];
        long long ans=0,mid,l=ma,r=si;
        while(l<=r){
            mid=l+r>>1;
            if(mid*(n-1)>=si)ans=mid,r=mid-1;
            else l=mid+1;
        }printf("%d",ans);
        return 0;
    }
    ```
    - **核心实现思想**：读入人数$n$和每个人想玩的轮数，同时记录最大值$ma$和总轮数$si$。在$[ma, si]$范围内进行二分查找，每次计算中间值$mid$，判断$mid$轮游戏能否满足所有人需求，若能则更新答案并缩小右边界，否则增大左边界，最终得到满足条件的最小轮数。
- **作者：tanghairong (4星)**
    - **关键亮点**：思路简洁直接，准确抓住问题核心，通过数学计算得出结果，代码简洁易懂，同时注意到数据类型转换和使用`long long`避免数据溢出。
    ```cpp
    #include<iostream>
    #include<cmath>
    #define int long long
    using namespace std;
    signed main(){
        int n,sum=0,maxn=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            int a;
            cin>>a;
            sum+=a;
            maxn=max(maxn,a);
        }
        cout<<max(maxn,(int)ceil(sum*1.0/(n-1)));
        return 0;
    }
    ```
    - **核心实现思想**：读入人数$n$和每个人想玩的轮数$a$，累加得到总轮数$sum$并找出最大值$maxn$。计算总轮数除以$n - 1$并向上取整的结果，与$maxn$比较，输出较大值。

### 最优关键思路或技巧
对于此类问题，数学方法更为直接高效，先计算总需求轮数与每轮可参与人数的关系得出初步轮数，再与最大需求轮数比较取大值。这种方法避免了二分答案可能带来的相对复杂的边界处理和较高的时间复杂度。

### 可拓展思路
同类型题通常围绕资源分配且存在某种限制条件，可通过分析总量与单次分配量、个体最大需求量之间的关系来解决。类似算法套路是先计算初步结果，再考虑特殊情况（如本题中最大需求量的影响）进行调整。

### 相似知识点洛谷题目
1. [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析每天的活动时间，考虑时间限制来确定满足条件的结果，与本题分析总量和限制关系类似。
2. [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：在给定火柴棒数量限制下，通过枚举和分析等式两边所需火柴棒数量来找出满足条件的等式数量，涉及到对总量和条件的综合考虑。
3. [P1228 地毯填补问题](https://www.luogu.com.cn/problem/P1228)：根据棋盘大小和特殊方格位置，利用分治思想进行地毯铺设，与本题在分析问题、满足条件并确定方案上有相似思维方式。 

---
处理用时：63.64秒