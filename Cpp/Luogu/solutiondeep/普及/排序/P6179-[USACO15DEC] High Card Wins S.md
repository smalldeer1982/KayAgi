# 题目信息

# [USACO15DEC] High Card Wins S

## 题目描述

Bessie 是纸牌游戏的忠实粉丝。对她而言，其他奶牛都算不上对手。更糟糕的是，其他奶牛在打牌时的行为都是完全能预测的。尽管如此，Bessie 知道取胜仍然是个挑战。

Bessie 和她的朋友 Elsie 正在玩一种纸牌游戏。这个游戏里要用到一副 $2N$ 张牌的套牌，编号从 $1$ 到 $2N$。Bessie 和 Elsie 每个人各分得 $N$ 张卡片。接下来进行 $N$ 轮比赛，Bessie 和 Elsie 每轮各出一张牌。每一轮谁的牌编号更大，谁就赢得了本轮的胜利。

Bessie 已经预测了 Elsie 的出牌顺序，请帮助 Bessie 算出她最多能赢多少轮。

## 说明/提示

Bessie 手中拿着 $2,3,5$ 三张牌。

它第一轮出 $2$，第二轮出 $3$，第三轮出 $5$，从而赢得一，三两轮。可以证明不存在更优的方案。

## 样例 #1

### 输入

```
3
1
6
4```

### 输出

```
2```

# AI分析结果

### 综合分析与结论
这些题解主要围绕贪心和二分查找算法解决问题。贪心策略核心在于用刚好大于对方的牌应对，或用小牌消耗对方大牌，保存大牌应对小牌；二分查找用于确定Bessie能赢的最大场数。各题解实现方式不同，包括排序、桶存储、堆优化、使用`set`容器等。

### 所选题解
- **作者：杨誉yy - Solution2（5星）**
    - **关键亮点**：思路清晰，通过桶存储简化操作，时间复杂度接近$O(n)$，代码简洁易读。
    - **核心代码**：
```cpp
#include<cstdio>
int ans,i,j,n,m,tmp,tail,cnt,b;
bool v[100010];
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&b);
        v[b]=true;
    }
    for(i=1;i<=2*n;i++)
    {
        if(!v[i])
        {
            if(cnt>0)
            {
                cnt--;
                ans++;
            }
        }
        else
        {
            cnt++;
        }
    }
    printf("%d",ans);
}
```
    - **核心实现思想**：用`v`数组记录Elsie的手牌，遍历$1$到$2n$，若当前数是Elsie的手牌，`cnt`加1；若是Bessie的手牌且`cnt`大于0，说明能赢，`ans`加1，`cnt`减1。

- **作者：study_nerd（4星）**
    - **关键亮点**：采用二分查找确定Bessie能赢的最大场数，思路巧妙，代码逻辑清晰。
    - **核心代码**：
```cpp
bool cheak(int x)
{
    int tt=n;
    for(int i=x;i>0;--i)
    {
        if(b[tt]<a[i])return 0;
        tt--;
    }
    return 1;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        s[a[i]]=true;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=2*n;++i)if(!s[i])b[++tot]=i;
    int l=0,r=n+1;
    while(l+1<r)
    {
        int mid=l+r>>1;
        if(cheak(mid))l=mid;
        else r=mid;
    }
    cout<<l;
    return 0;
}
```
    - **核心实现思想**：二分查找Bessie能赢的场数`mid`，`cheak`函数检查是否能赢`mid`场，若能则更新左边界，否则更新右边界。

- **作者：MuYC（4星）**
    - **关键亮点**：使用`set`容器结合贪心算法，方便查找和删除元素，代码简洁。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int A[50005],n,book[100005],tail = 0,Ans = 0;
set <int> s;

int main()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i ++)cin >> A[i],book[A[i]] = 1;
    for(int i = 1 ; i <= 2 * n ; i ++)
        if(book[i] == 0) s.insert(i);
    for(int i = 1 ; i <= n ; i ++)
    {
        set<int>::iterator it;
        it = s.upper_bound(A[i]);
        if(*it > A[i])s.erase(*it),Ans ++;
        else s.erase(*s.begin());
    }
    cout << Ans;
    return 0;
}
```
    - **核心实现思想**：用`set`存储Bessie的手牌，遍历Elsie的手牌，用`upper_bound`查找刚好大于当前手牌的牌，若有则删除并`Ans`加1，否则删除最小的牌。

### 最优关键思路或技巧
- **桶存储**：如杨誉yy的Solution2，用桶存储手牌信息，简化操作，使遍历有序，降低时间复杂度。
- **二分查找**：如study_nerd的题解，通过二分查找确定能赢的最大场数，减少不必要的计算。
- **贪心策略**：用刚好大于对方的牌应对，或用小牌消耗对方大牌，保存大牌应对小牌。

### 可拓展之处
同类型题如洛谷上的“P1650 田忌赛马”，都是通过合理安排出牌顺序使自己获胜次数最多。类似算法套路还有区间调度问题，通过贪心策略安排任务顺序以获取最大收益。

### 推荐题目
- P1650 田忌赛马
- P2240 硬币购物（可通过贪心和二分优化）
- P1090 合并果子（贪心算法）

### 个人心得
部分题解提到类似“田忌赛马”的思路，启发我们在解决此类博弈问题时，可从经典策略中寻找灵感，采用贪心思想，合理安排资源以获取最优解。 

---
处理用时：31.95秒