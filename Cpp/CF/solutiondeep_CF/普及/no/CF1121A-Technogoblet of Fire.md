# 题目信息

# Technogoblet of Fire

## 题目描述

Everybody knows that the $ m $ -coder Tournament will happen soon. $ m $ schools participate in the tournament, and only one student from each school participates.

There are a total of $ n $ students in those schools. Before the tournament, all students put their names and the names of their schools into the Technogoblet of Fire. After that, Technogoblet selects the strongest student from each school to participate.

Arkady is a hacker who wants to have $ k $ Chosen Ones selected by the Technogoblet. Unfortunately, not all of them are the strongest in their schools, but Arkady can make up some new school names and replace some names from Technogoblet with those. You can't use each made-up name more than once. In that case, Technogoblet would select the strongest student in those made-up schools too.

You know the power of each student and schools they study in. Calculate the minimal number of schools Arkady has to make up so that $ k $ Chosen Ones would be selected by the Technogoblet.

## 说明/提示

In the first example there's just a single Chosen One with id $ 3 $ . His power is equal to $ 3 $ , but in the same school $ 1 $ , there's a student with id $ 5 $ and power $ 6 $ , and that means inaction would not lead to the latter being chosen. If we, however, make up a new school (let its id be $ 4 $ ) for the Chosen One, Technogoblet would select students with ids $ 2 $ (strongest in $ 3 $ ), $ 5 $ (strongest in $ 1 $ ), $ 6 $ (strongest in $ 2 $ ) and $ 3 $ (strongest in $ 4 $ ).

In the second example, you can change the school of student $ 3 $ to the made-up $ 5 $ and the school of student $ 4 $ to the made-up $ 6 $ . It will cause the Technogoblet to choose students $ 8 $ , $ 7 $ , $ 6 $ , $ 5 $ , $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
7 3 1
1 5 3 4 6 7 2
1 3 1 2 1 2 3
3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
8 4 4
1 2 3 4 5 6 7 8
4 3 2 1 4 3 2 1
3 4 5 6
```

### 输出

```
2
```

# AI分析结果

### 题目内容重写
# 火焰杯科技

## 题目描述

众所周知，$m$ -coder 锦标赛即将举行。$m$ 所学校参加了这次比赛，每所学校只有一名学生参赛。

这些学校共有 $n$ 名学生。在比赛前，所有学生将他们的名字和学校名字放入火焰杯科技中。之后，火焰杯科技会从每所学校中选出最强的学生参赛。

Arkady 是一名黑客，他希望火焰杯科技能选出 $k$ 名“天选之子”。不幸的是，并非所有天选之子都是他们学校中最强的，但 Arkady 可以编造一些新的学校名字，并替换火焰杯科技中的一些名字。每个编造的学校名字只能使用一次。这样，火焰杯科技也会从这些编造的学校中选出最强的学生。

你知道每个学生的实力和他们所在的学校。计算 Arkady 需要编造的最少学校数量，以便火焰杯科技选出 $k$ 名天选之子。

## 说明/提示

在第一个样例中，只有一个天选之子，编号为 $3$。他的实力为 $3$，但在同一所学校 $1$ 中，有一个编号为 $5$ 的学生，实力为 $6$，这意味着如果不采取行动，后者将被选中。然而，如果我们为天选之子编造一个新的学校（假设其编号为 $4$），火焰杯科技将选出编号为 $2$（学校 $3$ 中最强）、$5$（学校 $1$ 中最强）、$6$（学校 $2$ 中最强）和 $3$（学校 $4$ 中最强）的学生。

在第二个样例中，你可以将学生 $3$ 的学校改为编造的 $5$，将学生 $4$ 的学校改为编造的 $6$。这将导致火焰杯科技选出学生 $8$、$7$、$6$、$5$、$3$ 和 $4$。

## 样例 #1

### 输入

```
7 3 1
1 5 3 4 6 7 2
1 3 1 2 1 2 3
3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
8 4 4
1 2 3 4 5 6 7 8
4 3 2 1 4 3 2 1
3 4 5 6
```

### 输出

```
2
```

### 算法分类
贪心

### 题解分析与结论
所有题解的思路基本一致，都是通过统计每个学校的最强学生，然后判断 $k$ 个天选之子是否已经是其所在学校的最强学生。如果不是，则需要编造新的学校。这种方法的核心在于贪心策略，即尽可能减少编造学校的数量。

### 评分较高的题解
#### 作者：_Violet_Evergarden (赞：5)
- **星级**: 4
- **关键亮点**: 代码简洁，思路清晰，直接通过数组记录每所学校的最强学生，然后进行判断。
- **核心代码**:
```cpp
for(int i=1;i<=n;i++){
    cin>>a[i];
}
for(int i=1;i<=n;i++){
    cin>>b[i];
    da[b[i]]=max(da[b[i]],a[i]);
}
for(int i=1;i<=k;i++){
    cin>>x;
    if(a[x]!=da[b[x]]){
        ans++;
    }
}
cout<<ans;
```

#### 作者：Stars_visitor_tyw (赞：1)
- **星级**: 4
- **关键亮点**: 使用了 `memset` 初始化数组，代码结构清晰，逻辑严谨。
- **核心代码**:
```cpp
memset(maxi,0xcf,sizeof(maxi));
for(int i=1;i<=n;i++){
    cin>>a[i];
}
for(int i=1;i<=n;i++){
    cin>>sch[i];
    maxi[sch[i]]=max(maxi[sch[i]],a[i]);
}
for(int i=1;i<=k;i++){
    int id;
    cin>>id;
    if(a[id]!=maxi[sch[id]]){
        ans++;
    }
}
cout<<ans;
```

#### 作者：Silence_World (赞：1)
- **星级**: 4
- **关键亮点**: 代码简洁，直接通过数组记录每所学校的最强学生，逻辑清晰。
- **核心代码**:
```cpp
for(int i=1;i<=n;i++){
    cin>>a[i];
}
for(int j=1;j<=n;j++){
    cin>>b[j];
    max1[b[j]]=max(max1[b[j]],a[j]);
}
int cnt=0; 
for(int i=1;i<=k;i++){
    int t;
    cin>>t;
    if(a[t]==max1[b[t]])continue;
    cnt++;
}
cout<<cnt<<endl;
```

### 最优关键思路或技巧
1. **贪心策略**: 通过统计每所学校的最强学生，判断天选之子是否已经是其所在学校的最强学生，如果不是，则需要编造新的学校。
2. **数组记录**: 使用数组记录每所学校的最强学生，方便后续判断。

### 可拓展之处
类似的问题可以扩展到其他需要“最优选择”的场景，例如在资源分配、任务调度等问题中，通过贪心策略来最小化资源消耗或最大化效率。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得摘录
- **作者：Withershine**: “这哪里是编程题，简直就是阅读理解。” 强调了题目理解的重要性。
- **作者：skyskyCCC**: “建议看原题自己翻译，这个洛古翻译其实差点事。” 提醒了翻译可能带来的理解偏差。

---
处理用时：40.87秒