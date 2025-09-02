# 题目信息

# Arranging The Sheep

## 题目描述

You are playing the game "Arranging The Sheep". The goal of this game is to make the sheep line up. The level in the game is described by a string of length $ n $ , consisting of the characters '.' (empty space) and '\*' (sheep). In one move, you can move any sheep one square to the left or one square to the right, if the corresponding square exists and is empty. The game ends as soon as the sheep are lined up, that is, there should be no empty cells between any sheep.

For example, if $ n=6 $ and the level is described by the string "\*\*.\*..", then the following game scenario is possible:

- the sheep at the $ 4 $ position moves to the right, the state of the level: "\*\*..\*.";
- the sheep at the $ 2 $ position moves to the right, the state of the level: "\*.\*.\*.";
- the sheep at the $ 1 $ position moves to the right, the state of the level: ".\*\*.\*.";
- the sheep at the $ 3 $ position moves to the right, the state of the level: ".\*.\*\*.";
- the sheep at the $ 2 $ position moves to the right, the state of the level: "..\*\*\*.";
- the sheep are lined up and the game ends.

For a given level, determine the minimum number of moves you need to make to complete the level.

## 样例 #1

### 输入

```
5
6
**.*..
5
*****
3
.*.
3
...
10
*.*...*.**```

### 输出

```
1
0
0
0
9```

# AI分析结果

### 题目内容
# 排列绵羊

## 题目描述
你正在玩“排列绵羊”游戏。该游戏的目标是让绵羊排成一排。游戏中的关卡由一个长度为 $n$ 的字符串描述，字符串由字符 '.'（空格）和 '*'（绵羊）组成。在一次移动中，如果相应的方格存在且为空，你可以将任意一只绵羊向左或向右移动一格。一旦绵羊排成一排，即任意两只绵羊之间没有空格，游戏结束。

例如，如果 $n = 6$ 且关卡由字符串“**.*..”描述，那么可能的游戏场景如下：
- 位置4的绵羊向右移动，关卡状态：“**..*.”；
- 位置2的绵羊向右移动，关卡状态：“*.*.*.”；
- 位置1的绵羊向右移动，关卡状态：“.*.*.*.”；
- 位置3的绵羊向右移动，关卡状态：“.*.**. ”；
- 位置2的绵羊向右移动，关卡状态：“..***.”；
- 绵羊排成一排，游戏结束。

对于给定的关卡，确定完成该关卡所需的最小移动次数。

## 样例 #1
### 输入
```
5
6
**.*..
5
*****
3
.*.
3
...
10
*.*...*.**
```
### 输出
```
1
0
0
0
9
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解主要围绕如何以最少移动次数让绵羊（即'*'字符）排成一排展开。思路上可分为两类，一类是向中间的'*'靠拢（Waaifu_D、LinkZelda、qwq___qaq），另一类是考虑将'.'移到两边（云浅知处、oimaster）。解决难点在于找到最优的移动策略，不同题解从不同角度给出了方法。

### 所选的题解
- **作者：Waaifu_D（5星）**
  - **关键亮点**：思路清晰，直接点明贪心策略为向中间的'*'靠拢，代码实现简洁明了，对特殊情况有清晰的特判。
  - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
string s;
long long n,m[1000005],pop=0,flag=0,ans=0;
long long t;
int main()
{
    cin>>t;
    while(t--)
    {
        pop=0,flag=0,ans=0;
        cin>>n;
        cin>>s;
        for(int i=0; i<n;i++)
        {
            if(s[i]=='*')
            {
                m[++pop]=i+1;
            }
            if(s[i]=='.') flag=1;
        }
        if(pop==0||pop==1||flag==0) {cout<<0<<endl;continue;}
        int mid=pop/2+1;
        for(int i=1; i<=pop;i++)
        {
            ans+=abs(m[mid]-m[i])-abs(mid-i);
        }
        cout<<ans<<endl;
    }
}
```
  - **核心实现思想**：先记录'*'的位置，判断特殊情况。确定中间'*'的位置后，通过计算每个'*'到中间'*'位置的距离差累加得到最小移动次数。
- **作者：LinkZelda（4星）**
  - **关键亮点**：简洁地阐述了向中间'*'靠拢的贪心思路，明确指出和中位数有关，点明时间复杂度。
  - **重点代码（链接形式）**：[代码](https://www.luogu.com.cn/paste/tnzbyfet)
  - **核心实现思想**：扫描字符串记录'*'位置，确定中间位置后计算其他'*'到中间位置的距离之和。
- **作者：云浅知处（4星）**
  - **关键亮点**：转换思路，从移动'.'的角度出发，通过计算每个'.'向左、向右移动的步数，利用前缀和与后缀和来求解最小移动次数。
  - **重点代码**：
```cpp
#include<cstdlib>
#include<iostream>
#include<cstring>

#define int long long
#define MAXN 1000005

using namespace std;

int l[MAXN],r[MAXN],suf[MAXN],pre[MAXN],n,t,a[MAXN];
string s;

signed main(void){

    cin>>t;
    while(t--){
        
        for(int i=1;i<=n;i++)l[i]=r[i]=suf[i]=pre[i]=a[i]=0;
        
        cin>>n;
        cin>>s;

        int cnt=0;
        l[n]=r[n]=suf[n]=pre[n]=0;
        for(int i=0;i<n;i++){
            l[i]=r[i]=suf[i]=pre[i]=0;
            if(s[i]=='.')a[++cnt]=i+1;
        }
        if(cnt==0){
            puts("0");
            continue;
        }
        
        for(int i=1;i<=cnt;i++)l[i]=a[i]-i,r[i]=n-cnt+i-a[i];
        int ans=1919810114514;
        for(int i=1;i<=cnt;i++)pre[i]=pre[i-1]+l[i];
        for(int i=cnt;i>=1;i--)suf[i]=suf[i+1]+r[i];
        for(int i=0;i<=cnt;i++)ans=min(ans,pre[i]+suf[i+1]);
        cout<<ans<<endl;
    }

    return 0;
}
```
  - **核心实现思想**：先记录'.'的位置，计算每个'.'向左、向右移动步数，分别求前缀和与后缀和，枚举不同位置求最小的前后缀和之和得到最小移动次数。

### 最优关键思路或技巧
向中间的'*'靠拢这一贪心策略较为直观且易于实现。在实现时，通过记录'*'的位置并利用中位数相关计算来快速得出最小移动次数。另一种将'.'移到两边的思路，通过巧妙地计算'.'的移动步数并结合前缀和与后缀和求解，也是一种不错的优化方向。

### 拓展
同类型题可考虑一些涉及元素位置调整求最小代价的问题，通常可以从贪心的角度去思考元素的移动方向。类似算法套路是先观察元素移动的规律，确定一个最优的目标位置（如中位数位置）或者移动方向，再通过计算距离或代价来求解。

### 洛谷题目推荐
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过合并果子求最小代价，考察贪心策略。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及双方策略选择，可通过贪心思想求解。
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：在字符串中找重复模式，部分测试点可利用贪心优化。 

---
处理用时：44.42秒