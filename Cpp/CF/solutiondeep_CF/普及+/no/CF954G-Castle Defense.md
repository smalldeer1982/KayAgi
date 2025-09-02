# 题目信息

# Castle Defense

## 题目描述

Today you are going to lead a group of elven archers to defend the castle that is attacked by an army of angry orcs. Three sides of the castle are protected by impassable mountains and the remaining side is occupied by a long wall that is split into $ n $ sections. At this moment there are exactly $ a_{i} $ archers located at the $ i $ -th section of this wall. You know that archer who stands at section $ i $ can shoot orcs that attack section located at distance not exceeding $ r $ , that is all such sections $ j $ that $ |i-j|<=r $ . In particular, $ r=0 $ means that archers are only capable of shooting at orcs who attack section $ i $ .

Denote as defense level of section $ i $ the total number of archers who can shoot at the orcs attacking this section. Reliability of the defense plan is the minimum value of defense level of individual wall section.

There is a little time left till the attack so you can't redistribute archers that are already located at the wall. However, there is a reserve of $ k $ archers that you can distribute among wall sections in arbitrary way. You would like to achieve maximum possible reliability of the defence plan.

## 样例 #1

### 输入

```
5 0 6
5 4 3 4 9
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4 2 0
1 2 3 4
```

### 输出

```
6
```

## 样例 #3

### 输入

```
5 1 1
2 1 2 1 2
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# 城堡防御

## 题目描述
今天你将带领一群精灵弓箭手保卫一座被愤怒的兽人军队攻击的城堡。城堡的三面被无法逾越的山脉保护，剩下的一面是一堵长长的城墙，城墙被分成了$n$个部分。此刻，第$i$部分城墙恰好有$a_{i}$个弓箭手。你知道站在第$i$部分的弓箭手可以射击距离不超过$r$的兽人，即所有满足$|i - j| \leq r$的$j$部分。特别地，$r = 0$意味着弓箭手只能射击攻击第$i$部分的兽人。

将第$i$部分城墙的防御等级定义为能够射击攻击该部分兽人的弓箭手总数。防御计划的可靠性是单个城墙部分防御等级的最小值。

距离攻击只剩下一点时间了，所以你不能重新分配已经在城墙上的弓箭手。然而，有$k$个弓箭手预备队，你可以以任意方式分配到城墙各部分。你希望实现防御计划的最大可靠性。

## 样例 #1
### 输入
```
5 0 6
5 4 3 4 9
```
### 输出
```
5
```

## 样例 #2
### 输入
```
4 2 0
1 2 3 4
```
### 输出
```
6
```

## 样例 #3
### 输入
```
5 1 1
2 1 2 1 2
```
### 输出
```
3
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路都是利用二分答案来解决“最大化最小值”问题。先确定二分的范围，左边界通常为0，右边界为所有弓箭手总和加上预备队数量。对于每个二分的中间值，通过贪心策略和特定的数据结构（如差分、队列等）来验证是否能满足防御可靠性要求。

难点在于如何高效地验证二分的中间值。不同题解采用了不同方法，多数题解利用差分与前缀和来维护区间加值操作，以优化时间复杂度。部分题解还提到线段树虽能解决但复杂度较高。

### 所选的题解
- **作者：linxiaoyu四 (赞：4)  星级：4星**
    - **关键亮点**：思路清晰，详细阐述二分答案的过程及验证中间值的方法，利用差分与前缀和优化区间加值操作。
    - **重点代码**：
```cpp
void add(int l,int r,int x)
{
    b[l]+=x;b[r+1]-=x;//区间加值
}
bool che(int x)
{
    int sum=0;
    for(int i=1;i<=n;i++) b[i]=c[i];
    for(int i=1;i<=n;i++)
    {
        b[i]+=b[i-1];//用前缀和查询
        if(b[i]<x)
        {
            sum+=x-b[i],add(i,i+2*r,x-b[i]);if(sum>k)return 0;
        }
    }
    return 1;
}
```
核心实现思想：`add`函数实现差分区间加值。`che`函数用于验证二分的中间值`x`，通过前缀和查询当前位置的值，若小于`x`，则计算需要增加的值并更新区间，同时判断增加的值是否超过预备队数量`k`。
- **作者：Adolfo_North (赞：1)  星级：4星**
    - **关键亮点**：简洁明了地阐述二分答案思路，通过差分数组维护区间加值，代码实现简洁。
    - **重点代码**：
```cpp
bool check(int k2){
    int sum=0;
    for(int i=1;i<=n;i++) c[i]=b[i];
    for(int i=1;i<=n;i++){
        c[i]+=c[i-1];
        if(c[i]<k2){
            int x=k2-c[i];
            sum+=x;
            c[i]+=x;
            c[i+2*r+1]-=x;
            if(sum>k) return 0;
        }
    }
    return 1;
}
```
核心实现思想：`check`函数验证中间值`k2`，通过前缀和还原当前位置的值，若小于`k2`，计算差值并更新区间，同时判断增加的值是否超过`k`。
- **作者：Dino_chx (赞：1)  星级：4星**
    - **关键亮点**：思路讲解细致，将二分答案的过程分步骤阐述，对边界处理进行说明，代码注释详细。
    - **重点代码**：
```cpp
bool check(int x)
{
    for(int i=1;i<=n;i++)     //copy过来，给它覆盖了 
    {
        d2[i]=d1[i];
    }
    int res=0;
    for(int i=1;i<=n;i++)
    {
        d2[i]+=d2[i-1];        //渐渐还原回去 
        if(d2[i]<x)       
        {
            res+=x-d2[i];
            update2(i,min(n,i+r+r),x-d2[i]);  //加上，但是不是i+2*r-1，因为守卫当前城堡不消耗距离的 
            if(res>k)
                return false;
        }
    }
    return res<=k;
} 
```
核心实现思想：`check`函数验证中间值`x`，先复制初始差分数组，通过前缀和还原当前值，若小于`x`，计算差值并更新区间，同时判断增加的值是否超过`k`。

### 最优关键思路或技巧
利用二分答案解决“最大化最小值”问题，通过差分与前缀和优化区间加值操作，以降低时间复杂度。贪心策略体现在当某位置防御等级不足时，将增加的弓箭手尽可能分配到右侧区间，以覆盖更多位置。

### 可拓展之处
同类型题常涉及最大化最小值或最小化最大值的场景，如资源分配、最优策略选择等。类似算法套路是遇到此类问题优先考虑二分答案，再结合贪心策略与合适的数据结构（如差分、前缀和等）验证二分的中间值。

### 推荐洛谷题目
1. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
2. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
3. [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得摘录与总结
部分作者提到二分右边界设置问题，如初始设为1e18导致WA，应设为所有弓箭手总和加上预备队数量，强调了边界设置的重要性。还有作者尝试线段树但因复杂度问题放弃，表明在选择数据结构时需综合考虑复杂度。 

---
处理用时：52.54秒