# 题目信息

# Let's Go Hiking

## 题目描述

On a weekend, Qingshan suggests that she and her friend Daniel go hiking. Unfortunately, they are busy high school students, so they can only go hiking on scratch paper.

A permutation $ p $ is written from left to right on the paper. First Qingshan chooses an integer index $ x $ ( $ 1\le x\le n $ ) and tells it to Daniel. After that, Daniel chooses another integer index $ y $ ( $ 1\le y\le n $ , $ y \ne x $ ).

The game progresses turn by turn and as usual, Qingshan moves first. The rules follow:

- If it is Qingshan's turn, Qingshan must change $ x $ to such an index $ x' $ that $ 1\le x'\le n $ , $ |x'-x|=1 $ , $ x'\ne y $ , and $ p_{x'}<p_x $ at the same time.
- If it is Daniel's turn, Daniel must change $ y $ to such an index $ y' $ that $ 1\le y'\le n $ , $ |y'-y|=1 $ , $ y'\ne x $ , and $ p_{y'}>p_y $ at the same time.

The person who can't make her or his move loses, and the other wins. You, as Qingshan's fan, are asked to calculate the number of possible $ x $ to make Qingshan win in the case both players play optimally.

## 说明/提示

In the first test case, Qingshan can only choose $ x=3 $ to win, so the answer is $ 1 $ .

In the second test case, if Qingshan will choose $ x=4 $ , Daniel can choose $ y=1 $ . In the first turn (Qingshan's) Qingshan chooses $ x'=3 $ and changes $ x $ to $ 3 $ . In the second turn (Daniel's) Daniel chooses $ y'=2 $ and changes $ y $ to $ 2 $ . Qingshan can't choose $ x'=2 $ because $ y=2 $ at this time. Then Qingshan loses.

## 样例 #1

### 输入

```
5
1 2 5 4 3```

### 输出

```
1```

## 样例 #2

### 输入

```
7
1 2 4 6 5 3 7```

### 输出

```
0```

# AI分析结果

### 题目翻译
在一个周末，青山建议她和她的朋友丹尼尔去徒步旅行。不幸的是，他们都是忙碌的高中生，所以他们只能在草稿纸上进行徒步旅行。

在纸上从左到右写着一个排列 $ p $。首先，青山选择一个整数索引 $ x $（$ 1\le x\le n $）并告诉丹尼尔。之后，丹尼尔选择另一个整数索引 $ y $（$ 1\le y\le n $，$ y \ne x $）。

游戏轮流进行，和往常一样，青山先行动。规则如下：
- 如果轮到青山行动，青山必须将 $ x $ 更改为一个索引 $ x' $，使得 $ 1\le x'\le n $，$ |x'-x|=1 $，$ x'\ne y $，并且同时满足 $ p_{x'}<p_x $。
- 如果轮到丹尼尔行动，丹尼尔必须将 $ y $ 更改为一个索引 $ y' $，使得 $ 1\le y'\le n $，$ |y'-y|=1 $，$ y'\ne x $，并且同时满足 $ p_{y'}>p_y $。

无法行动的人输掉游戏，另一个人获胜。作为青山的粉丝，你被要求计算在双方都采取最优策略的情况下，能让青山获胜的可能的 $ x $ 的数量。

### 算法分类
无算法分类

### 综合分析与结论
这些题解大多围绕分类讨论展开，核心是分析先手（青山）在不同位置选择下的胜负情况。各题解普遍先确定先手的可选位置范围（通常是山峰位置），再根据山峰两边坡长的关系（是否相等、奇偶性等）以及最长坡长的数量等条件来判断先手是否能获胜。

### 所选题解
- **作者：miao5 (赞：10)，4星**
    - **关键亮点**：思路清晰，通过大量配图详细分析了各种可能的情况，最后得出有且只有两条最长的边，刚好连在一起，长度又恰好是奇数时先手能赢的结论。代码实现简洁明了。
- **作者：oisdoaiu (赞：5)，4星**
    - **关键亮点**：采用枚举每个初始位置并判断可行性的方法，对后手的选择进行了细致分类（和先手比长度、堵路），并通过预处理降低了时间复杂度。
- **作者：fuxuantong123 (赞：3)，4星**
    - **关键亮点**：先证明答案一定是 $0$ 或 $1$，然后分类讨论不同情况下先手的胜负，逻辑严谨，代码实现简洁。

### 重点代码
#### miao5 的代码
```cpp
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=100010;
int n,a[maxn],len_up,len_down;
int dp1[maxn],dp2[maxn],len_max;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]>a[i-1]) dp1[i]=dp1[i-1]+1;
        else dp1[i]=1;
        if(a[i]<a[i-1]) dp2[i]=dp2[i-1]+1;
        else dp2[i]=1; // 记录坡的连续长度 
        len_up=max(len_up,dp1[i]);
        len_down=max(len_up,dp2[i]); // 记录最长的坡 
    }
    len_max=max(len_up,len_down); // 最最长的坡 
    bool f_up=false,f_down=false;
    int p_up,p_down;
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(dp1[i]==len_max){
            f_up=true;
            cnt++;
            p_up=i;
        }
        if(dp2[i]==len_max){
            f_down=true;
            cnt++;
            p_down=i;
        } // 记录最长的上坡和最长的下坡的位置 
    }
    if(f_up&&f_down&&cnt==2&&p_up==p_down-len_max+1&&len_max%2) cout<<1<<endl; 
    else cout<<0<<endl;	
    // 判断，输出答案。 
    return 0;
}
```
**核心实现思想**：先通过动态规划记录每个位置的上坡和下坡长度，找出最长坡长，再统计最长上坡和最长下坡的数量和位置，最后根据条件判断是否满足先手获胜的情况。

#### oisdoaiu 的代码
```cpp
for(register int i=1, lst=1; i<=n; i++)    
    if(a[i]>a[i+1] or i==n){
        for(register int j=lst; j<=i; j++) up[1][j] = i, down[0][j] = lst;
        lst = i+1;
    }
for(register int i=n, lst=n; i; i--)
    if(a[i]>a[i-1] or i==1){
        for(register int j=lst; j>=i; j--) up[0][j] = i, down[1][j] = lst;
        lst = i-1;
    }
for(register int i=1; i<=n; i++) pre[i] = max(pre[i-1],max(i-up[0][i]+1,up[1][i]-i+1));
for(register int i=n; i>=1; i--) suf[i] = max(suf[i+1],max(i-up[0][i]+1,up[1][i]-i+1));
for(register int i=1; i<=n; i++) if(down[0][i]!=i and down[1][i]!=i){
    int len1 = i-down[0][i]+1, len2 = down[1][i]-i+1;
    int l = down[0][i], r = down[1][i];
    if(max(max(pre[l-1],l-up[0][l]+1),max(suf[r+1],up[1][r]-r+1))>=max(len1,len2)) continue;
    if(((len1>>1)<<1)>=len2) continue;
    if(((len2>>1)<<1)>=len1) continue;
    ans++;
}
```
**核心实现思想**：先预处理出每个位置能走到的最左和最右位置，再预处理出前缀和后缀中能走的最远长度，最后枚举每个位置，根据条件判断该位置是否能让先手获胜。

#### fuxuantong123 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100010];
int s[100010];
int j[100010];
int main(){
    int n;
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=2;i<=n;i++){
        if(a[i]>a[i-1]){
            s[i]=s[i-1]+1;
        }
    }
    for(int i=n-1;i>=1;i--){
        if(a[i]>a[i+1]){
            j[i]=j[i+1]+1;
        }
    }
    int mxs=0;
    int mxj=0;
    for(int i=1;i<=n;i++){
        mxs=max(mxs,s[i]);
        mxj=max(mxj,j[i]);
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(mxs==mxj && s[i]==mxs){
            cnt++;
        }
        if(mxs==mxj && j[i]==mxs){
            cnt++;
        }
    }
    if(cnt>=3){
        printf("0");
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(s[i]==j[i] && s[i]%2==0 && s[i]==mxs && j[i]==mxj && s[i]!=0){
            printf("1");
            return 0;
        }
    }
    printf("0");
return 0;
}
```
**核心实现思想**：先计算每个位置的上升和下降长度，找出最大上升和下降长度，统计最大长度的数量，最后根据条件判断是否存在先手必胜的位置。

### 最优关键思路或技巧
- **分类讨论**：将各种可能的情况进行细致分类，逐一分析每种情况下先手的胜负，从而得出结论。
- **预处理**：通过预处理每个位置的相关信息（如上坡、下坡长度，前缀、后缀中能走的最远长度等），降低后续判断的时间复杂度。

### 拓展思路
同类型题可能会改变游戏规则，如移动的条件、获胜的条件等，但解题的核心思路仍然是分类讨论和分析各种情况。类似的算法套路包括对博弈问题进行深入分析，找出必胜或必败的条件。

### 推荐题目
- [P1290 欧几里德的游戏](https://www.luogu.com.cn/problem/P1290)
- [P2197 【模板】nim 游戏](https://www.luogu.com.cn/problem/P2197)
- [P2964 [USACO09NOV]A Coin Game S](https://www.luogu.com.cn/problem/P2964)

### 个人心得摘录与总结
- **Cry_For_theMoon**：赛场被其他题卡了时间，导致没时间思考本题，结果成绩不理想。总结：合理分配比赛时间很重要。
- **vectorwyx**：赛时因为读错题而调了一个小时。总结：读题要仔细，避免因理解错误浪费时间。

---
处理用时：73.72秒