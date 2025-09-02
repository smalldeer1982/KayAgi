# 题目信息

# [USACO2.1] 三值的排序 Sorting a Three-Valued Sequence

## 题目描述

排序是一种很频繁的计算任务。现在考虑最多只有三值的排序问题。一个实际的例子是，当我们给某项竞赛的优胜者按金银铜牌排序的时候。在这个任务中可能的值只有三种 $1,2,3$。我们用交换的方法把他排成升序的。

写一个程序计算出，给定的一个 $1,2,3$ 组成的数字序列，排成升序所需的最少交换次数


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 1000$。

USACO 2.1

翻译来自NOCOW


## 样例 #1

### 输入

```
9
2
2
1
3
3
3
2
3
1```

### 输出

```
4
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何用最少交换次数将由 1、2、3 组成的序列排成升序展开，大多采用贪心算法。算法要点在于先统计 1、2、3 的个数，划分出排序后的三个区间，优先交换能让两个数字同时归位的数对，再处理需两次交换让三个数字归位的情况。难点在于准确找出可一次交换归位的数对，以及处理剩余需两次交换的情况。

### 所选题解
- **作者：ABCDXYZ（5 星）**
    - **关键亮点**：思路清晰，先统计 1、2、3 出现的次数，标记出排序后各位置应有的数字，通过比较原序列和目标序列，利用容斥原理求出可节省的交换次数，代码结构清晰，可读性强。
    - **核心代码**：
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int a[1010],flag[1010];
int times_1,times_2,times_3,ans=0,n;
void draw( ){
    for(int i=1;i<=times_1;i++)
        flag[i]=1;
    for(int i=times_1+1;i<=times_2+times_1;i++)
        flag[i]=2;
    for(int i=times_2+times_1+1;i<=n;i++)
        flag[i]=3;
}
void Find( ){
    for(int i=1;i<=n;i++){
        if(a[i]==1)times_1++;
        else if(a[i]==2)times_2++;
        else if(a[i]==3)times_3++;
    }
    draw();
    return;
}
int main( ){
    int m,j,k,i;
    int swap1=0,swap2=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);    
    Find();
    for(i=1;i<=n;i++){
        if(flag[i]==1 && a[i]!=1)
            ans++;
        if(flag[i]==2 && a[i]!=2)
            ans++;
        if(flag[i]==1 && a[i]==2)
            swap1++;
        if(flag[i]==2 && a[i]==1)
            swap2++;
    }
    ans-=min(swap1,swap2);
    printf("%d",ans);
    return 0;
}
```
- **作者：楯山文乃（4 星）**
    - **关键亮点**：先找出可一次交换让两个数字归位的情况，再处理剩余需两次交换让三个数字归位的情况，思路简洁明了，代码实现较为直观。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
using namespace std;
int n,i,ans,sum=0;
int a[2000],b[2000],f[10][10];
int main(){
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1); 
    for(i=1;i<=n;i++) f[b[i]][a[i]]++;
    ans=min(f[1][2],f[2][1]);
    f[1][2]-=ans; f[2][1]-=ans;
    sum+=ans;
    ans=min(f[1][3],f[3][1]);
    f[1][3]-=ans; f[3][1]-=ans;
    sum+=ans;
    ans=min(f[2][3],f[3][2]);
    f[2][3]-=ans; f[3][2]-=ans;
    sum+=ans;
    sum+=max(f[1][2],f[2][1])*2;
    printf("%d\n",sum);
    return 0;
}
```
- **作者：泠小毒（4 星）**
    - **关键亮点**：先考虑最优解，优先交换一次能使 2 个数字到位的情况，再处理需两次交换使 3 个数字到位的情况，代码逻辑清晰，易于理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1010],sum[10],ans;
int main()
{
    cin >> n;
    for(int i=1;i<=n;i++)
        cin >> a[i],sum[a[i]]++;
    for(int i=1;i<=sum[1];i++)
        for(int j=sum[1]+1;j<=sum[1]+sum[2];j++)
            if(a[i]==2&&a[j]==1)
                swap(a[i],a[j]),ans++;
    for(int i=1;i<=sum[1];i++)
        for(int j=sum[1]+sum[2]+1;j<=n;j++)
            if(a[i]==3&&a[j]==1)
                swap(a[i],a[j]),ans++;
    for(int i=sum[1]+1;i<=sum[1]+sum[2];i++)
        for(int j=sum[1]+sum[2]+1;j<=n;j++)
            if(a[i]==3&&a[j]==2)
                swap(a[i],a[j]),ans++;
    for(int i=1;i<=sum[1];i++)
        if(a[i]!=1)
            ans+=2;
    cout << ans << endl;
    return 0;
}
```

### 最优关键思路与技巧
- **贪心策略**：优先进行一次交换能让两个数字归位的操作，再处理需两次交换让三个数字归位的情况。
- **统计与区间划分**：统计 1、2、3 的个数，划分出排序后的三个区间，便于确定数字应处的正确位置。
- **容斥原理**：通过统计不同区间数字错位的情况，利用容斥原理计算可节省的交换次数。

### 可拓展之处
同类型题可拓展到更多值的排序问题，或在交换规则上进行变化。类似算法套路可用于其他需要贪心策略解决的排序或交换问题，如部分图论中的节点交换问题。

### 推荐题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得摘录与总结
- **作者：Pisces**：第一次发题解，认为自己的时间复杂度较低，但代码在洛谷上过不了，不过数据答案正确，在其他 OJ 能过。总结：代码在不同 OJ 上可能存在兼容性问题，需注意。
- **作者：zhouwc**：看到众多大神写题解，心血来潮写了自己的算法，若有错误希望被指出。总结：勇于分享自己的思路，同时保持谦逊，接受他人的指正。 

---
处理用时：42.30秒