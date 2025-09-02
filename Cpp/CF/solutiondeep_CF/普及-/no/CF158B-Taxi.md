# 题目信息

# Taxi

## 题目描述

After the lessons $ n $ groups of schoolchildren went outside and decided to visit Polycarpus to celebrate his birthday. We know that the $ i $ -th group consists of $ s_{i} $ friends ( $ 1<=s_{i}<=4 $ ), and they want to go to Polycarpus together. They decided to get there by taxi. Each car can carry at most four passengers. What minimum number of cars will the children need if all members of each group should ride in the same taxi (but one taxi can take more than one group)?

## 说明/提示

In the first test we can sort the children into four cars like this:

- the third group (consisting of four children),
- the fourth group (consisting of three children),
- the fifth group (consisting of three children),
- the first and the second group (consisting of one and two children, correspondingly).

There are other ways to sort the groups into four cars.

## 样例 #1

### 输入

```
5
1 2 4 3 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8
2 3 4 4 2 1 3 1
```

### 输出

```
5
```

# AI分析结果

### 题目内容
#### Taxi
1. **题目描述**：在课程结束后，$n$组学童外出，决定去Polycarpus家庆祝他的生日。已知第$i$组有$s_{i}$个朋友（$1\leq s_{i}\leq4$），他们想一起去Polycarpus家。他们决定乘坐出租车前往，每辆出租车最多可搭载四名乘客。如果每组的所有成员都必须乘坐同一辆出租车（但一辆出租车可以搭载多个组），那么孩子们最少需要多少辆出租车？
2. **说明/提示**：在第一个测试中，我们可以这样将孩子们分配到四辆出租车中：
    - 第三组（由四个孩子组成）；
    - 第四组（由三个孩子组成）；
    - 第五组（由三个孩子组成）；
    - 第一组和第二组（分别由一个和两个孩子组成）。
    - 还有其他将这些组分配到四辆出租车的方法。
3. **样例 #1**
    - **输入**：
```
5
1 2 4 3 3
```
    - **输出**：
```
4
```
4. **样例 #2**
    - **输入**：
```
8
2 3 4 4 2 1 3 1
```
    - **输出**：
```
5
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，尽量让每辆出租车搭载尽可能多的人，以达到使用最少出租车的目的。各题解主要围绕如何将不同人数的小组（1 - 4人）进行组合展开。解决难点在于如何合理搭配剩余小组，保证出租车数量最少。

### 所选的题解
1. **作者：FL_sleake (赞：4)**
    - **星级**：4星
    - **关键亮点**：代码简洁，通过巧妙的计算，避免了复杂的if - else语句。先将3人组和1人组尽量组合，然后利用总人数除以4上取整的方式处理剩余的2人组和1人组，减少了代码量。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int cnt[5];
signed main(){
    int n;
    cin>>n;
    for(int i = 1,x; i <= n; i++) cin>>x,cnt[x]++;
    int t = min(cnt[3],cnt[1]);
    cnt[4]+=t;
    cnt[3]-=t;
    cnt[1]-=t;
    cout<<cnt[4]+cnt[3]+(cnt[2]*2+cnt[1]*1+4 - 1)/4<<endl;
    return 0;
}
```
    - **核心实现思想**：先统计每组人数对应的组数，将3人组和1人组能匹配的部分匹配，更新剩余组数，最后通过计算总人数（2人组人数 + 1人组人数）除以4上取整，加上已确定的4人组和剩余3人组数量得到总出租车数。

2. **作者：ZolaWatle (赞：5)**
    - **星级**：4星
    - **关键亮点**：思路清晰，按照不同人数小组的组合方式逐步分析，代码逻辑明确，易于理解。对各种情况的讨论详细，如对剩余2人组、1人组和3人组的处理，逐步得出最少出租车数量。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
#define re register int
using namespace std;

int n,ans,sum[5];

int main()
{
    std::scanf("%d",&n);
    for(re i = 1; i <= n; i++)
    {
        re temp;
        std::scanf("%d",&temp);
        sum[temp]++;
    }

    ans+=sum[4];
    ans+=sum[2]/2;
    if(sum[2]%2!=0)
    {
        ans++;
        if(sum[1]>=2)
            sum[1]-=2;
        else if(sum[1]>=1)
            sum[1]--;
    }


    if(sum[1]==sum[3])
        ans+=sum[1];
    else if(sum[1]>sum[3])
    {
        ans+=sum[3];
        sum[1]-=sum[3];
        ans+=sum[1]/4;
        if(sum[1]%4!=0)
            ans++;
    }
    else if(sum[1]<sum[3])
        ans+=sum[3];

    std::printf("%d",ans);
    return 0;
}
```
    - **核心实现思想**：先统计各人数小组的组数，4人组直接算入出租车数，2人组两两配对算入出租车数，处理剩余2人组，再将1人组和3人组按不同情况组合计算出租车数。

### 最优关键思路或技巧
1. **贪心策略**：优先考虑能凑满4人的组合方式，如4人组单独一车，3人组和1人组拼车，2人组两两拼车等，以达到出租车使用数量最少。
2. **代码实现技巧**：像FL_sleake的题解，通过巧妙的计算避免复杂的条件判断，减少代码量，提高代码简洁性和可读性。

### 可拓展之处
同类型题通常围绕资源分配、组合优化等场景，如将不同重量的物品装入容量固定的背包，要求尽量装满背包，这类题目都可以尝试使用贪心策略解决。类似算法套路是先确定局部最优的组合方式，再逐步处理剩余部分，以达到整体最优。

### 洛谷相似题目推荐
1. **P1094 [NOIP2007 普及组] 纪念品分组**：同样是将不同重量的物品分组放入容量固定的容器，求最少容器数，考察贪心策略。
2. **P1199 [NOIP2010 普及组] 三国游戏**：涉及武将武力值的配对问题，类似小组组合以达到最优结果，运用贪心思想。
3. **P1223 排队接水**：根据接水时间对人进行排序，用贪心策略使总等待时间最少，与本题合理分配资源思路相似。 

---
处理用时：45.29秒