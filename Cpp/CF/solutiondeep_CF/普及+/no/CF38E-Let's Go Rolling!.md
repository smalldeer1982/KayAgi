# 题目信息

# Let's Go Rolling!

## 题目描述

On a number axis directed from the left rightwards, $ n $ marbles with coordinates $ x_{1},x_{2},...,x_{n} $ are situated. Let's assume that the sizes of the marbles are infinitely small, that is in this task each of them is assumed to be a material point. You can stick pins in some of them and the cost of sticking in the marble number $ i $ is equal to $ c_{i} $ , number $ c_{i} $ may be negative. After you choose and stick the pins you need, the marbles will start to roll left according to the rule: if a marble has a pin stuck in it, then the marble doesn't move, otherwise the marble rolls all the way up to the next marble which has a pin stuck in it and stops moving there. If there is no pinned marble on the left to the given unpinned one, it is concluded that the marble rolls to the left to infinity and you will pay an infinitely large fine for it. If no marble rolled infinitely to the left, then the fine will consist of two summands:

- the sum of the costs of stuck pins;
- the sum of the lengths of the paths of each of the marbles, that is the sum of absolute values of differences between their initial and final positions.

Your task is to choose and pin some marbles in the way that will make the fine for you to pay as little as possible.

## 样例 #1

### 输入

```
3
2 3
3 4
1 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4
1 7
3 1
5 10
6 1
```

### 输出

```
11
```

# AI分析结果

### 题目内容
# 让我们滚动吧！

## 题目描述
在一条从左向右的数轴上，有\(n\)个弹珠，其坐标分别为\(x_{1},x_{2},...,x_{n}\)。假设弹珠的大小无限小，即在此任务中每个弹珠都被视为一个质点。你可以在其中一些弹珠上插针，在弹珠\(i\)上插针的成本等于\(c_{i}\)，\(c_{i}\)可能为负数。在选择并插好所需的针后，弹珠将开始向左滚动，规则如下：如果一个弹珠插有针，那么该弹珠不会移动，否则弹珠会一直向左滚动，直到碰到下一个插有针的弹珠并在那里停止移动。如果给定的未插针弹珠左边没有插针的弹珠，那么该弹珠将向左滚向无穷远，你将为此支付无限大的罚款。如果没有弹珠向左滚向无穷远，那么罚款将由两个部分组成：
- 插针的成本总和；
- 每个弹珠滚动路径的长度总和，即它们初始位置和最终位置之差的绝对值之和。

你的任务是选择并插针一些弹珠，以使你支付的罚款尽可能少。

## 样例 #1
### 输入
```
3
2 3
3 4
1 2
```
### 输出
```
5
```

## 样例 #2
### 输入
```
4
1 7
3 1
5 10
6 1
```
### 输出
```
11
```

### 算法分类
动态规划

### 题解综合分析与结论
这几道题解都采用动态规划算法来解决问题，核心思路都是先对弹珠按坐标排序，再通过定义不同的状态和状态转移方程来求解最小花费。区别在于状态的定义和转移方程的推导方式。部分题解通过维护前缀和来优化计算弹珠滚动距离的过程，从而降低时间复杂度。

### 所选的题解
- **作者：基地A_I (4星)**
    - **关键亮点**：思路清晰，详细阐述了状态转移方程的推导过程。状态定义直观，以\(f_{i,j}\)表示前\(i\)个弹珠且最后一个固定弹珠为\(j\)时的最小花费，转移方程根据\(i\)是否等于\(j\)分情况讨论。
    - **重点代码**：
```cpp
// int下INF=0x3f3f3f3f
// long long 下 INF=1e19 
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#define int long long
#define INF 1e19
using namespace std;
inline int read() {
    int x=0,f=1; char ch=getchar();
    while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+(ch^48); ch=getchar(); }
    return x * f;
}
const int N = 3007;
int n;
int f[N][N];
struct Marbles {    //弹珠 
    int x,c;
}a[N];
bool cmp(Marbles x,Marbles y) {
    return x.x < y.x;
}
signed main()
{
    n = read();
    for(int i=1;i<=n;++i)
        a[i].x = read(), a[i].c = read();
    sort(a+1, a+1+n, cmp);
    int minn;
    f[1][1] = a[1].c;
    for(int i=2;i<=n;++i) {
        minn = INF;
        for(int j=1;j<i;++j) {
            f[i][j] = f[i-1][j] + a[i].x - a[j].x;
            minn = min(minn, f[i-1][j]);
        }
        f[i][i] = minn + a[i].c;
    }
    int ans = INF;
    for(int i=1;i<=n;++i)
        ans = min(ans, f[n][i]);
    cout<<ans<<endl;
    return 0;
}
```
    - **核心实现思想**：先读入弹珠数据并按坐标排序，初始化\(f[1][1]\)。通过两层循环，外层遍历弹珠数量，内层确定最后固定弹珠，分情况更新\(f[i][j]\)，最后在\(f[n][i]\)中找最小值作为答案。

- **作者：harmis_yz (4星)**
    - **关键亮点**：状态定义简洁，仅用一维数组\(f_i\)表示在第\(i\)个小球位置插针的最小花费，通过前缀和优化转移方程，将原本\(O(n^3)\)的时间复杂度优化到\(O(n^2)\)。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
    il int read(){
        int x=0,f=1;char ch=gc;
        while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
        while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
        return x*f;
    }
    il int qmi(int a,int b,int p){
        int ans=1;
        while(b){
            if(b&1) ans=ans*a%p;
            a=a*a%p,b>>=1;
        }
        return ans;
    }
    il auto max(auto a,auto b){return (a>b?a:b);}
    il auto min(auto a,auto b){return (a<b?a:b);}
    il int gcd(int a,int b){
        if(!b) return a;
        return gcd(b,a%b);
    }
    il int lcm(int a,int b){
        return a/gcd(a,b)*b;
    }
    il void exgcd(int a,int b,int &x,int &y){
        if(!b) return x=1,y=0,void(0);
        exgcd(b,a%b,x,y);
        int t=x;
        x=y,y=t-a/b*x;
        return ;
    }
    mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=3005;
int n;
struct node{
    int x,c,s;
}a[N];
int f[N],s[N];

il bool cmp(node a,node b){
    return a.x<b.x;
}
il int getsum(int l,int r){
    return s[r]-s[l]-(r-l)*a[l].s;
}
il void solve(){
    n=rd;
    for(re int i=1;i<=n;++i) a[i]={rd,rd};
    sort(a+1,a+n+1,cmp);
    for(re int i=1;i<=n;++i) a[i].s=a[i].x-a[1].x,s[i]=a[i].s+s[i-1];
    memset(f,0x3f,sizeof(f));
    f[n+1]=0;
    for(re int i=n;i>=1;--i){
        for(re int lst=i+1;lst<=n+1;++lst){
            f[i]=min(f[i],f[lst]+getsum(i,lst-1)+a[i].c);
        }
    }
    printf("%lld\n",f[1]);
    return ;
}

signed main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
    int t=1;while(t--)
    solve();
    return 0;
}
```
    - **核心实现思想**：读入数据排序后，计算前缀和数组\(s\)。初始化\(f\)数组，通过两层循环，外层倒序遍历弹珠，内层枚举右边第一个插针位置，利用前缀和计算滚动距离并更新\(f[i]\)，最终\(f[1]\)为答案。

### 最优关键思路或技巧
1. **状态定义优化**：如harmis_yz的题解，用一维数组定义状态，简化了状态表示，减少空间复杂度，同时更清晰地反映问题本质。
2. **前缀和优化**：多个题解利用前缀和优化计算弹珠滚动距离的过程，将原本需要多次重复计算的部分转化为一次计算，从而降低时间复杂度。

### 可拓展之处
此类题目属于动态规划在数轴上物体移动场景的应用。类似题目可能会改变移动规则、费用计算方式或者增加限制条件等。例如，改变弹珠滚动方向，或者让弹珠滚动到特定位置有额外奖励等。

### 洛谷相似题目推荐
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：经典的动态规划题目，涉及最长不上升子序列和最长上升子序列的求解，与本题类似，都需要合理定义状态和状态转移方程。
2. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)：区间动态规划问题，通过合并石子的操作来求最小或最大得分，与本题同样需要考虑不同状态间的转移关系。
3. [P3951 [NOIP2017 提高组] 小凯的疑惑](https://www.luogu.com.cn/problem/P3951)：虽然看似数论问题，但也可以通过动态规划的思想解决，与本题一样，需要找到合适的状态和转移方式来求解。

### 个人心得摘录与总结
无。 

---
处理用时：84.88秒