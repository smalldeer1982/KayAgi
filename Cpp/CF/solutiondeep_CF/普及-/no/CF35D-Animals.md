# 题目信息

# Animals

## 题目描述

Once upon a time DravDe, an outstanding person famous for his professional achievements (as you must remember, he works in a warehouse storing Ogudar-Olok, a magical but non-alcoholic drink) came home after a hard day. That day he had to drink 9875 boxes of the drink and, having come home, he went to bed at once.

DravDe dreamt about managing a successful farm. He dreamt that every day one animal came to him and asked him to let it settle there. However, DravDe, being unimaginably kind, could send the animal away and it went, rejected. There were exactly $ n $ days in DravDe’s dream and the animal that came on the $ i $ -th day, ate exactly $ c_{i} $ tons of food daily starting from day $ i $ . But if one day the animal could not get the food it needed, it got really sad. At the very beginning of the dream there were exactly $ X $ tons of food on the farm.

DravDe woke up terrified...

When he retold the dream to you, he couldn’t remember how many animals were on the farm by the end of the $ n $ -th day any more, but he did remember that nobody got sad (as it was a happy farm) and that there was the maximum possible amount of the animals. That’s the number he wants you to find out.

It should be noticed that the animals arrived in the morning and DravDe only started to feed them in the afternoon, so that if an animal willing to join them is rejected, it can’t eat any farm food. But if the animal does join the farm, it eats daily from that day to the $ n $ -th.

## 说明/提示

Note to the first example: DravDe leaves the second and the third animal on the farm. The second animal will eat one ton of food on the second day and one ton on the third day. The third animal will eat one ton of food on the third day.

## 样例 #1

### 输入

```
3 4
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 6
1 1 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# 动物

## 题目描述
很久很久以前，德拉夫德（DravDe），一位因专业成就而闻名的杰出人士（你们肯定记得，他在一个储存奥古达尔 - 奥洛克（Ogudar - Olok）的仓库工作，这是一种神奇的无酒精饮料），在辛苦工作一天后回到家。那天他不得不喝掉9875箱这种饮料，回到家后，他立刻上床睡觉了。

德拉夫德梦到自己经营着一个成功的农场。他梦到每天都有一只动物来找他，请求在农场定居。然而，无比善良的德拉夫德可能会把动物送走，然后动物就会失望地离开。在德拉夫德的梦里正好有 $n$ 天，第 $i$ 天来的动物从第 $i$ 天开始每天确切地吃 $c_{i}$ 吨食物。但是如果有一天动物得不到它所需的食物，它就会非常难过。在梦的一开始，农场里正好有 $X$ 吨食物。

德拉夫德惊恐地醒来...

当他向你复述这个梦时，他已经不记得到第 $n$ 天结束时农场里有多少只动物了，但他记得没有动物难过（因为这是一个快乐的农场），并且动物的数量是尽可能多的。这就是他希望你找出的数字。

需要注意的是，动物在早上到达，德拉夫德只在下午开始喂它们，所以如果一只想加入的动物被拒绝，它就吃不到农场的任何食物。但是如果动物加入了农场，它从当天到第 $n$ 天每天都会进食。

## 说明/提示
第一个示例的说明：德拉夫德留下了第二只和第三只动物在农场。第二只动物将在第二天吃一吨食物，第三天吃一吨食物。第三只动物将在第三天吃一吨食物。

## 样例 #1
### 输入
```
3 4
1 1 1
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3 6
1 1 1
```
### 输出
```
3
```

### 算法分类
贪心、动态规划

### 综合分析与结论
这些题解主要围绕贪心和动态规划两种算法思路。核心难点在于理解题意，将动物每天的食量转化为从到来日到第n天的总食量。
 - **贪心思路要点**：先预处理出每只动物从到来日到第n天的总食量，对这些总食量进行排序，从小到大依次选择，只要剩余食物足够就选择该动物，直到食物不足。
 - **动态规划思路要点**：同样先预处理每只动物总食量，设dp[x]为剩余粮食为x时所能容纳的最大动物数，通过状态转移方程dp[x]=max(dp[x],dp[x - ani[i]] + 1)求解，类似01背包问题。

### 所选的题解
 - **作者：WCG2025 (5星)**
    - **关键亮点**：清晰阐述两种解法思路，代码实现完整且注释详细，对01背包和贪心的实现方式有明确说明。
    - **个人心得**：提到CF题目有加文件输入输出的要求。
    - **重点代码 - 贪心**：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch=getchar();
    int x=0,f=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int n;
int k;
int a[1000000];
int cnt=1;
int ans;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    n=read();
    k=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        a[i]=a[i]*(n-i+1);
    }
    sort(a+1,a+n+1);
    while(k-a[cnt]>=0&&cnt<=n)
    {
        ans++;
        k-=a[cnt++];
    }
    printf("%d",ans);
    return 0;
} 
```
核心实现思想：先读入数据并处理每只动物总食量，排序后通过循环判断剩余食物是否够，够则选择该动物并更新剩余食物量。
    - **重点代码 - 动态规划**：
```cpp
#include<iostream>
#include<cstdio>
#include<fstream>
using namespace std;

int ani[1005];
int dp[100005];
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,x;
    cin>>n>>x;
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&ani[i]);
        ani[i]*=(n-i+1);
    }
    for(int i=1;i<=n;i++)
        for(int j=x;j>=ani[i];j--)
            dp[j]=max(dp[j],dp[j-ani[i]]+1);
    cout<<dp[x]<<endl;
    return 0;
}
```
核心实现思想：读入数据并处理总食量后，利用两层循环，外层遍历动物，内层从大到小遍历剩余食物量，通过状态转移方程更新dp数组。
 - **作者：BigJoker (4星)**
    - **关键亮点**：先对题目进行分析，明确两种解法都需先算出每件物品成本，贪心代码简洁明了。
    - **重点代码 - 贪心**：
```cpp
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define dep(i,r,l) for(int i=r;i>=l;i--)
using namespace std;
const int N=1e2+5;
int n,x,ans,c[N];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d %d",&n,&x);
    rep(i,1,n){
        scanf("%d",&c[i]);
        c[i]=c[i]*(n-i+1);
    }
    sort(c+1,c+1+n);
    rep(i,1,n)
        if(x>=c[i]) ans++,x-=c[i];
        else break;
    printf("%d",ans);
    return 0;
}
```
核心实现思想：读入数据并处理每只动物总食量，排序后循环判断剩余食物量，够则选择动物并更新剩余量。

### 最优关键思路或技巧
贪心算法在此题中更为简洁高效，关键在于巧妙地将动物每天食量转化为总食量，通过排序和简单循环选择动物，避免了动态规划相对复杂的状态转移过程。

### 同类型题或类似算法套路
此类题目通常涉及资源分配，可通过分析每个元素的固定消耗，利用贪心思想从消耗小的元素开始选择，以达到资源利用最大化。

### 洛谷题目推荐
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
 - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录与总结
多位作者提到CF该题需加文件输入输出操作，否则会RE或WA，提醒做题时注意题目特殊要求。 

---
处理用时：66.90秒