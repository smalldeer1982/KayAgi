# 题目信息

# [USACO06OPEN] County Fair Events S

## 题目背景

题目是经过简写保证不改变原有题意的题目。

## 题目描述

FJ 参加活动。 

他想参加尽可能多的 $N$ 个活动，参加完某个之后可以立刻参加下一个。 

给定 FJ 可参加的活动列表、其开始时间 $T$ 和持续时间 $L$ ，求 FJ 可以参加的最大活动数。 

FJ 每个活动都不会提早离开。

## 说明/提示

$1\le T,L\le 10^5$

$1\le N\le 10^4$

## 样例 #1

### 输入

```
7
1 6
8 6
14 5
19 2
1 8
18 3
10 6```

### 输出

```
4```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
本题的核心问题是如何在时间不冲突的情况下，选择尽可能多的活动。所有题解都采用了贪心算法，通过按活动结束时间排序，并依次选择最早结束且不与已选活动冲突的活动。这种策略能够保证每次选择都为后续活动留下尽可能多的时间，从而最大化活动数量。

### 所选高星题解
#### 1. 作者：HsKr (赞：8)
- **星级**: 5星
- **关键亮点**: 代码简洁明了，思路清晰，直接按结束时间排序并贪心选择，逻辑严谨。
- **个人心得**: 无

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
    int t,l;
}a[10010];
bool cmp(node a,node b){
    return a.t+a.l<b.t+b.l;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].t>>a[i].l;
    }
    sort(a+1,a+n+1,cmp);
    int end=a[1].t+a[1].l,ans=1;
    for(int i=2;i<=n;i++){
        if(a[i].t>=end){
            ans++;
            end=a[i].l+a[i].t;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

#### 2. 作者：Diamiko (赞：6)
- **星级**: 4星
- **关键亮点**: 详细解释了贪心策略的正确性，并提供了反例证明其他贪心策略的错误。
- **个人心得**: 无

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct Activity{
    int Start, Last, End;
    friend bool operator<(Activity x,Activity y){
        return x.End==y.End ? x.Start<y.Start : x.End<y.End;
    }
}ac[10005];
int n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&ac[i].Start,&ac[i].Last);
        ac[i].End=ac[i].Start+ac[i].Last;
    }
    sort(ac+1,ac+n+1);
    int ans=1,r=ac[1].End;
    for(int i=2;i<=n;i++){
        if(r<=ac[i].Start){
            r=ac[i].End;
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

#### 3. 作者：Dovuq (赞：3)
- **星级**: 4星
- **关键亮点**: 提供了多种贪心策略的对比，并详细解释了为什么选择结束时间最早的策略是正确的。
- **个人心得**: 无

```cpp
#include <bits/stdc++.h>
using namespace std;
struct event{
    int start,end;
    void read(){
        int a;
        scanf("%d%d",&start,&a);
        end=start+a;
    }
};
event t[10005];
bool operator<(event a,event b){
    return a.end<b.end;
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        t[i].read();
    sort(t,t+n);
    int now=0,ans=0;
    for(int i=0;i<n;i++){
        if(t[i].start>=now){
            now=t[i].end;
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
```

### 最优关键思路或技巧
- **按结束时间排序**: 通过按活动结束时间排序，确保每次选择的活动为后续活动留下最多的时间。
- **贪心选择**: 依次选择最早结束且不与已选活动冲突的活动，保证每次选择都是当前最优解。

### 可拓展之处
- **类似问题**: 其他需要最大化选择不相交区间的问题，如任务调度、会议室安排等。
- **算法套路**: 贪心算法在处理区间选择问题时，通常需要按某一维度排序，并依次选择符合条件的最优解。

### 推荐相似题目
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
2. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：31.09秒