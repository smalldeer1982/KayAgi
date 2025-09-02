# 题目信息

# Potions (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ n \leq 200000 $ . You can make hacks only if both versions of the problem are solved.

There are $ n $ potions in a line, with potion $ 1 $ on the far left and potion $ n $ on the far right. Each potion will increase your health by $ a_i $ when drunk. $ a_i $ can be negative, meaning that potion will decrease will health.

You start with $ 0 $ health and you will walk from left to right, from first potion to the last one. At each potion, you may choose to drink it or ignore it. You must ensure that your health is always non-negative.

What is the largest number of potions you can drink?

## 说明/提示

For the sample, you can drink $ 5 $ potions by taking potions $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ and $ 6 $ . It is not possible to drink all $ 6 $ potions because your health will go negative at some point

## 样例 #1

### 输入

```
6
4 -4 1 -3 1 -3```

### 输出

```
5```

# AI分析结果

### 题目内容（中文重写）
# 药剂（困难版本）

## 题目描述
这是该问题的困难版本。唯一的区别在于，在这个版本中 $ n \leq 200000 $。只有当两个版本的问题都解决后，你才能进行 Hack 操作。

有 $ n $ 瓶药剂排成一排，最左边是第 1 瓶药剂，最右边是第 $ n $ 瓶药剂。每瓶药剂在喝下后会使你的生命值增加 $ a_i $，$ a_i $ 可能为负数，这意味着该药剂会减少你的生命值。

你初始生命值为 0，并且会从左到右，从第 1 瓶药剂走到第 $ n $ 瓶药剂。在每瓶药剂前，你可以选择喝下它或忽略它。你必须确保自己的生命值始终非负。

你最多可以喝下多少瓶药剂？

## 说明/提示
对于样例，你可以喝下 5 瓶药剂，选择第 1、3、4、5 和 6 瓶药剂。不可能喝下所有 6 瓶药剂，因为在某些时刻你的生命值会变为负数。

## 样例 #1
### 输入
```
6
4 -4 1 -3 1 -3
```
### 输出
```
5
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，目标是尽可能多地喝药剂且保证生命值非负。大部分题解借助优先队列（堆）来维护已喝药剂中的关键信息（如最大负数绝对值或最小负数），以便在生命值为负时做出最优调整。

各题解的差异主要体现在实现细节和优先队列的使用方式上。部分题解直接使用大根堆存储负数的绝对值，部分使用小根堆存储负数本身。还有题解使用线段树来维护区间信息，但相对复杂。

### 所选题解
- **作者：2021sunzishan（4星）**
  - **关键亮点**：思路清晰，代码简洁易懂，使用大根堆存储负数的绝对值，便于在生命值为负时快速找到对生命值影响最大的药剂并舍弃。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
priority_queue<long long,vector<long long>,less<long long> >q; //大根堆
int main() {
    cin>>n;
    long long ans=0,s=0;//ans：药剂瓶数 s:当前体力和
    for (int i=1; i<=n; i++) {
        long long x;
        cin>>x;
        if (x<0)
            q.push(-x); //如果为负数，绝对值入堆
        s+=x; //当前体力和加x
        ans++; //药剂瓶数加1
        if(s<0) {  //如果体力值不满足条件了
            long long k=q.top(); //取出堆中最大的绝对值，就是最小的负数
            s+=k; //体力和恢复k
            ans--; //药剂瓶数减1，因为丢弃了一瓶药剂
            q.pop(); 
        }
    }
    cout<<ans;
    return 0;
}
```
核心实现思想：遍历药剂，遇到正数直接喝，遇到负数先喝并将其绝对值存入大根堆。若生命值为负，从堆中取出最大绝对值的药剂（即对生命值影响最大的负数药剂）舍弃，更新生命值和喝药数量。

- **作者：Hilte（4星）**
  - **关键亮点**：明确对比了 DP 和贪心算法的时间复杂度，突出了贪心算法的优势，使用小根堆存储已喝药剂，在生命值为负时弹出最小的药剂。
  - **核心代码**：
```cpp
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
priority_queue<ll,vector<ll>,greater<ll> > q;//从小到大
ll a[200001];

int main()
{
    ll n,cur=1,ans=0,tot=0;
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    ans=n;//答案
    while(cur<=n)//没有喝到n瓶药
    {
        tot+=a[cur];//将血量增加a[i]
        q.push(a[cur]);//压入Q
        if(tot<0)//如果凉了
        {
            tot-=q.top();//反（后）悔一次，不喝这瓶药
            q.pop();
            ans--;//少喝一瓶药
        }
        cur++;
    }
    printf("%lld\n",ans);
    return 0;
}
```
核心实现思想：遍历药剂，每喝一瓶就将其加入小根堆。若生命值为负，从堆中弹出最小的药剂，更新生命值和喝药数量。

- **作者：_Winham_（4星）**
  - **关键亮点**：思路简洁明了，使用小根堆存储已喝药剂，代码实现较为清晰。
  - **核心代码**：
```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
#include<queue>
using namespace std;
#define int long long
const int N = 2e5+10;
const int INF = 0x3f3f3f3f;
int n,a[N]; 
priority_queue<int,vector<int>,greater<int>>q;//从小到大优先队列 
signed main(){
    cin>>n;
    int cnt=0,sum=0;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        cnt+=x;
        q.push(x);
        if(cnt<0){
            cnt-=q.top(),sum--;//我们要把背包里最没用的东西丢掉 
            q.pop();
        }
        sum++;
    }
    cout<<sum<<endl;
    return 0;
}
```
核心实现思想：遍历药剂，每喝一瓶就将其加入小根堆。若生命值为负，从堆中弹出最小的药剂，更新生命值和喝药数量。

### 最优关键思路或技巧
使用优先队列（堆）来维护已喝药剂中的关键信息，在生命值为负时能快速找到需要舍弃的药剂，时间复杂度为 $O(n\log n)$，避免了暴力枚举的 $O(n^2)$ 复杂度。

### 拓展思路
同类型题通常涉及在满足一定条件下的最优选择问题，可使用贪心算法结合优先队列解决。类似算法套路包括在动态选择过程中，利用优先队列维护关键信息，以便在不满足条件时进行最优调整。

### 推荐洛谷题目
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
2. [P2240 【深基12.例1】部分背包问题](https://www.luogu.com.cn/problem/P2240)
3. [P1090 [NOIP2004 提高组] 合并果子 / [USACO06NOV] Fence Repair G](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录与总结
- **作者：Fa1thful**：做题不要不屑于打暴力，正解可能隐含在暴力中。积极打暴力，不仅能在考场上拿部分分数，还可能通过 `STL` 优化得到满分。同时要多学多用 `STL`，关键时刻能帮助优化暴力算法。 

---
处理用时：56.79秒