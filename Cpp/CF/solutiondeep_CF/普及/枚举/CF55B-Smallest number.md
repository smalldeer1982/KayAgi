# 题目信息

# Smallest number

## 题目描述

Recently, Vladimir got bad mark in algebra again. To avoid such unpleasant events in future he decided to train his arithmetic skills. He wrote four integer numbers $ a $ , $ b $ , $ c $ , $ d $ on the blackboard. During each of the next three minutes he took two numbers from the blackboard (not necessarily adjacent) and replaced them with their sum or their product. In the end he got one number. Unfortunately, due to the awful memory he forgot that number, but he remembers four original numbers, sequence of the operations and his surprise because of the very small result. Help Vladimir remember the forgotten number: find the smallest number that can be obtained from the original numbers by the given sequence of operations.

## 样例 #1

### 输入

```
1 1 1 1
+ + *
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 2 2 2
* * +
```

### 输出

```
8
```

## 样例 #3

### 输入

```
1 2 3 4
* + +
```

### 输出

```
9
```

# AI分析结果

### 题目翻译
# 最小的数

## 题目描述
最近，弗拉基米尔的代数成绩又很差。为了避免未来再发生这种不愉快的事情，他决定训练自己的算术技能。他在黑板上写下了四个整数 $ a $、$ b $、$ c $、$ d $。在接下来的三分钟里，他每次从黑板上选取两个数（不一定相邻），并将它们替换为它们的和或积。最后，他得到了一个数。不幸的是，由于记忆力太差，他忘记了那个数，但他记得最初的四个数、操作的顺序，以及因为结果非常小而感到的惊讶。请帮助弗拉基米尔回忆起那个忘记的数：找出通过给定的操作顺序从原始数字中可以得到的最小数。

## 样例 #1
### 输入
```
1 1 1 1
+ + *
```
### 输出
```
3
```

## 样例 #2
### 输入
```
2 2 2 2
* * +
```
### 输出
```
8
```

## 样例 #3
### 输入
```
1 2 3 4
* + +
```
### 输出
```
9
```

### 综合分析与结论
这些题解的思路主要分为暴力搜索和特殊方法两类。暴力搜索类题解通过深度优先搜索（DFS）枚举所有可能的操作组合，找到最小结果；特殊方法类题解有随机算法和分类讨论法。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|Fido_Puppy|随机抽取两个数进行操作，重复多次取最小结果|使用`srand`和`rand`函数随机选取数字，多次尝试逼近最优解|不能保证一次性AC，依赖大量尝试|2星|
|linyinuo2008|深度优先搜索，枚举两个要操作的数，按顺序操作并回溯|使用`vis`数组记录操作情况，搜索完还原|注意数据类型、初始化、回溯条件|4星|
|爱嘤撕毯|生成4的全排列作为运算顺序，考虑两种计算情况取最小结果|生成全排列，对每个全排列按顺序计算和分成两批计算|考虑遗漏的计算情况|3星|
|YangXiaopei|根据运算符中`*`的个数分类讨论|对不同`*`的个数情况分别推导最小结果的计算方式|复杂情况的分类和推导|3星|
|AuCloud|打表存储4个数字和3个数字的全排列，按顺序计算取最小值|生成全排列表，按表进行计算|打表和按表计算的实现|3星|
|翼德天尊|深度优先搜索，每次选两个数与符号结合并回溯|标记使用过的数，搜索完还原标记和数值|回溯操作和数据类型|4星|
|Siyuan|暴力搜索，枚举两个数，更改数值并递归，到达目标状态更新答案|使用`-1`标记使用过的数字和符号，回溯还原|回溯和标记的处理|4星|
|Suuon_Kanderu|深度优先搜索，枚举两个操作数，将结果覆盖并删除一个数，回溯还原|使用`vector`存储操作数，回溯时还原`vector`|`vector`的操作和回溯|3星|
|傅思维666|暴力搜索，两两枚举、标记、还原现场|将运算结果存到一个数，标记另一个数，回溯还原|还原现场时避免除以0|3星|
|mot1ve|深度优先搜索，枚举运算符用于哪两个数，新数覆盖一个数，标记另一个数为`-1`|用`-1`标记使用过的数，回溯还原|标记和回溯|3星|
|Daidly|暴力搜索，判断加或乘，标记用过的数为`-1`，取最小结果|标记使用过的数，回溯还原|标记和回溯|3星|

### 所选题解
- **linyinuo2008（4星）**
    - 关键亮点：思路清晰，对搜索过程中的注意事项有详细说明，代码注释丰富，可读性强。
    - 个人心得：“好久没写搜索了，一写有点发蒙，写篇题解巩固一下”，强调了写题解对巩固知识的作用。
    - 核心代码：
```cpp
void dfs(int cur)
{
    int i,j;
    if(cur==3)
    {
        for(i=0;i<4;i++)
            if(!vis[i])
                ans=min(ans,a[i]);
        return ;
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(i==j||vis[i]||vis[j])   continue;
            long long p=a[i];
            vis[j]=1;
            if(ope[cur]=='+')
                a[i]+=a[j];
            else if(ope[cur]=='*')
                a[i]*=a[j];
            dfs(cur+1);
            vis[j]=0;
            a[i]=p;
        }
    }
}
```
核心实现思想：通过`dfs`函数进行深度优先搜索，枚举两个未使用过的数，根据当前操作符进行操作，标记使用过的数，递归搜索下一层，搜索完回溯还原标记和数值。

- **翼德天尊（4星）**
    - 关键亮点：对解题步骤进行了详细的分步说明，代码逻辑清晰，对回溯操作有明确解释。
    - 核心代码：
```cpp
void dfs(int d){
    if (d==4){
        int zc=0;
        for (int i=1;i<=4;i++){
            if (!vis[i]) zc=a[i];
        }
        ans=min(ans,zc);
        return;
    }
    for (int i=1;i<=4;i++){
        if (!vis[i]){
            for (int j=i+1;j<=4;j++){
                if (!vis[j]){
                    vis[i]=1;
                    int s=a[j];
                    if (b[d]=='+') a[j]+=a[i];
                    else if (b[d]=='*') a[j]*=a[i];
                    dfs(d+1);
                    a[j]=s;
                    vis[i]=0;
                }
            }
        }
    }
}
```
核心实现思想：`dfs`函数进行深度优先搜索，当搜索到第4次时，找到未标记的数更新答案。枚举两个未标记的数，根据操作符进行操作，标记使用过的数，递归搜索下一层，回溯还原标记和数值。

- **Siyuan（4星）**
    - 关键亮点：思路简洁明了，代码使用`register`关键字优化，对使用过的数字和符号用`-1`标记，回溯处理清晰。
    - 核心代码：
```cpp
inline void dfs(const int &left)
{
    if(left==1)
    {
        register ll s;
        for(register int i=1;i<=4;i++)
            if(a[i]!=-1){s=a[i];break;}
        ans=(ans<s?ans:s);
        return;
    }
    for(register int i=1;i<=4;i++)
        for(register int j=i+1;j<=4;j++)
        {
            register int k=4-left+1;
            if(a[i]==-1||a[j]==-1||p[k]=='-')  continue;
            register ll x=a[i],y=a[j];
            register char t=p[k];
            p[k]='-';  a[j]=-1;
            if(t=='+')  a[i]=x+y;  else  a[i]=x*y;
            dfs(left-1);
            a[i]=x;  a[j]=y;  p[k]=t;
        }
}
```
核心实现思想：`dfs`函数根据剩余数字个数进行深度优先搜索，当剩余1个数时更新答案。枚举两个未使用过的数，根据操作符进行操作，标记使用过的数字和符号，递归搜索下一层，回溯还原标记和数值。

### 最优关键思路或技巧
- **深度优先搜索（DFS）**：通过递归枚举所有可能的操作组合，是解决此类问题的通用方法。
- **回溯**：在搜索过程中，标记使用过的元素，搜索完后还原标记和数值，保证可以尝试所有可能。
- **标记技巧**：使用`vis`数组、`-1`等方式标记使用过的数字和符号，方便回溯和判断。

### 可拓展之处
同类型题：给定多个数字和运算符，按照一定规则进行组合运算，求最大或最小结果。可以使用类似的深度优先搜索和回溯方法解决。

### 洛谷相似题目推荐
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：从n个数中选k个数相加，判断和是否为质数，使用深度优先搜索枚举组合。
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：在电梯中上下移动，每次移动的层数固定，求到达目标楼层的最少移动次数，可使用广度优先搜索或深度优先搜索。
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：在8×8的棋盘上放置8个皇后，使它们互不攻击，使用深度优先搜索枚举所有可能的放置方案。

### 个人心得摘录总结
- linyinuo2008：好久没写搜索，写题解巩固知识，强调了写题解对学习的帮助。
- YangXiaopei：改了一晚上，测了十多次，每次改一点，最终通过，体现了调试的耐心和坚持。
- 傅思维666：第一份代码挂了，原因是搜索思路错误，提醒要选对搜索思路。

---
处理用时：53.05秒