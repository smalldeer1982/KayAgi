# 题目信息

# Game of Life

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523A/010268700b5eefe6d637a339a161b9e30121cb66.png)William really likes the cellular automaton called "Game of Life" so he decided to make his own version. For simplicity, William decided to define his cellular automaton on an array containing $ n $ cells, with each cell either being alive or dead.

Evolution of the array in William's cellular automaton occurs iteratively in the following way:

- If the element is dead and it has exactly $ 1 $ alive neighbor in the current state of the array, then on the next iteration it will become alive. For an element at index $ i $ the neighbors would be elements with indices $ i - 1 $ and $ i + 1 $ . If there is no element at that index, it is considered to be a dead neighbor.
- William is a humane person so all alive elements stay alive.

Check the note section for examples of the evolution.

You are given some initial state of all elements and you need to help William find the state of the array after $ m $ iterations of evolution.

## 说明/提示

Sequence of iterations of evolution for the first test case

- 01000000001 — initial state
- 11100000011 — first iteration of evolution
- 11110000111 — second iteration of evolution
- 11111001111 — third iteration of evolution

Sequence of iterations of evolution for the second test case

- 0110100101 — initial state
- 1110111101 — first iteration of evolution
- 1110111101 — second iteration of evolution

## 样例 #1

### 输入

```
4
11 3
01000000001
10 2
0110100101
5 2
10101
3 100
000```

### 输出

```
11111001111
1110111101
10101
000```

# AI分析结果

### 题目内容
# 生命游戏

## 题目描述
威廉非常喜欢名为“生命游戏”的元胞自动机，所以他决定制作自己的版本。为简单起见，威廉决定在一个包含 $n$ 个单元格的数组上定义他的元胞自动机，每个单元格要么是活的，要么是死的。

威廉的元胞自动机中数组的演变以迭代方式进行，如下所示：
 - 如果一个元素是死的，并且在数组的当前状态下它恰好有一个活的邻居，那么在下一次迭代中它将变为活的。对于索引为 $i$ 的元素，其邻居是索引为 $i - 1$ 和 $i + 1$ 的元素。如果该索引处没有元素，则视为死邻居。
 - 威廉是个仁慈的人，所以所有活的元素都会保持存活。

查看注释部分以获取演变示例。

给定所有元素的初始状态，你需要帮助威廉找到经过 $m$ 次演变迭代后数组的状态。

## 说明/提示
第一个测试用例的演变迭代序列：
 - 01000000001 — 初始状态
 - 11100000011 — 第一次演变迭代
 - 11110000111 — 第二次演变迭代
 - 11111001111 — 第三次演变迭代

第二个测试用例的演变迭代序列：
 - 0110100101 — 初始状态
 - 1110111101 — 第一次演变迭代
 - 1110111101 — 第二次演变迭代

## 样例 #1
### 输入
```
4
11 3
01000000001
10 2
0110100101
5 2
10101
3 100
000
```
### 输出
```
11111001111
1110111101
10101
000
```

### 算法分类
模拟

### 题解综合分析与结论
这些题解主要分为两种思路，一种是直接模拟，另一种是通过预处理优化。直接模拟的思路简单，但时间复杂度较高，在本题数据规模下可能会超时，如作者Chenyichen0420、SH___int、a1a2a3a4a5的题解。优化思路则是通过记录每个位置与前后最近的1的距离，避免对每一轮进行重复计算，从而降低时间复杂度，如作者Hamer_sans、cmll02、dks0311、xwh_hh、_Evergarden_、Noby_Glds的题解。

### 所选的题解
 - **作者Hamer_sans（5星）**
    - **关键亮点**：通过类似前缀和的思路，用两个数组分别记录每个0距前一个1和后一个1的位置，然后根据不同情况分类讨论，优化掉了对m次迭代的直接模拟，时间复杂度低。同时对边界情况处理详细。
    - **个人心得**：最初写了时间复杂度为 $O(tnm)$ 的模拟代码导致TLE，后思考优化m的方法，还注意到首尾边界处理不当会出错。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int t,n,m;
int b[N],p[N];
int inf=0x3f3f3f3f;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        string a;
        cin>>a;
        b[0]=-inf;
        p[n+1]=inf;
        string x="0";
        x+=a;
        for(register int i=1;i<=n;++i){
            if(x[i]=='1') b[i]=i;
            else b[i]=b[i-1];
        }
        for(register int i=n;i>=1;--i){
            if(x[i]=='1') p[i]=i;
            else p[i]=p[i+1];
        }
        for(register int i=1;i<=n;++i){
            if(x[i]=='1') cout<<x[i];
            else{
                int l=i-b[i],r=p[i]-i;
                if(l==r) printf("%d",0);
                else if(l<=m or r<=m) printf("%d",1);
                else printf("%d",0);
            }
        }
        printf("\n");
    }
    return 0;
}
```
核心实现思想：先对输入字符串预处理，添加前缀0方便处理边界。通过两次遍历分别填充记录前后1位置的数组b和p，最后根据当前位置字符及与前后1的距离判断输出结果。
 - **作者cmll02（5星）**
    - **关键亮点**：同样采用记录每个点最近的前后两个1的位置，以此判断每个位置最终状态，代码简洁高效，时间复杂度为 $O(n)$ 。
    - **核心代码**：
```cpp
// Problem: A. Game of Life
// Contest: Codeforces - Deltix Round, Spring 2021 (open for everyone, rated, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1523/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <stdio.h>
#include <string.h> 
#include <algorithm>
#include <queue>
#define od(x) printf("%d",x)
#define odb(x) printf("%d ",x)
#define odl(x) printf("%d\n",x)
#define odp(x,y) printf("%d %d\n",x,y)
#define ol(x) puts("")
#define old(x) printf("%lld",x)
#define oldb(x) printf("%lld ",x)
#define oldl(x) printf("%lld\n",x)
#define oldp(x,y) printf("%lld %lld\n",x,y)
//#define int long long
inline int read()
{
    int num=0,f=1;char c=getchar();
    while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
    while(c>47&&c<58)num=num*10+(c^48),c=getchar();
    return num*f;
}
inline int re1d()
{
    char c=getchar();
    while(c<48||c>49)c=getchar();
    return c&1;
}
inline int min(int a,int b){return a>b?b:a;}
inline int max(int a,int b){return a<b?b:a;}
int a[10005],pre[10005],suf[10005];
signed main()
{
    int T=read();
    pre[0]=-2000000000;
    while(T--)
    {
        int n=read(),m=read();
        for(int i=1;i<=n;i++)a[i]=re1d();
        for(int i=1;i<=n;i++)
        {
            if(a[i])
            {
                pre[i]=i;
            }
            else pre[i]=pre[i-1];
        }
        suf[n+1]=2000000000;
        for(int i=n;i>=1;i--)
        {
            if(a[i])suf[i]=i;else suf[i]=suf[i+1];
        }
        for(int i=1;i<=n;i++)if(a[i])putchar(49);
        else
        {
            int x=i-pre[i],y=suf[i]-i;
            if(x==y)putchar(48);
            else if(x<=m||y<=m)putchar(49);
            else putchar(48);
        }
        puts("");
    }
    return 0;
}
```
核心实现思想：通过两次遍历分别确定每个位置前一个1和后一个1的位置并存于pre和suf数组，最后根据当前位置字符及与前后1的距离判断输出结果。
 - **作者dks0311（4星）**
    - **关键亮点**：思路清晰，先分析暴力枚举m次操作会TLE，进而提出预处理每个0与前后1的距离，通过分类讨论得出结果，代码中使用快读优化输入。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
const int INF = 0x3f3f3f3f;
int t;
int d1[N], d2[N], a[N];
inline int read(){
    int s = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
    return s * f;
}	//快读 
int main(){
    t = read();
    while(t--){
        int n = read(), m = read();
        for(register int i = 1; i <= n; ++i)
            a[i] = getchar() - '0';	//输入 
        int pos = 0;
        for(register int i = 1; i <= n; ++i){
            if(a[i] == 1) pos = i;
            else{
                if(pos == 0) d1[i] = INF;
                else d1[i] = i - pos;
            }
        }	//和前一个1的距离 
        pos = 0;
        for(register int i = n; i >= 1; --i){
            if(a[i] == 1) pos = i;
            else{
                if(pos == 0) d2[i] = INF;
                else d2[i] = pos - i;
            }
        }	//和后一个1的距离 
        for(register int i = 1; i <= n; ++i){
            if(a[i] == 0 && d1[i]!= d2[i] && (d1[i] <= m || d2[i] <= m)) a[i] = 1;
        }
        for(register int i = 1; i <= n; ++i)
            printf("%d", a[i]);
        puts("");
    }
    return 0;
}
```
核心实现思想：先通过快读输入数据，再两次遍历分别计算每个位置与前一个1和后一个1的距离存于d1和d2数组，最后根据当前位置字符及与前后1的距离判断是否将0变为1并输出结果。

### 最优关键思路或技巧
通过预处理每个0与前后最近1的距离，利用这两个距离信息直接判断经过m次迭代后每个位置的状态，避免对每次迭代进行重复模拟，从而优化时间复杂度。

### 可拓展之处
此类题目属于状态演变模拟类型，类似的题目通常需要找到状态变化的规律，然后通过合适的数据结构和算法优化来减少计算量。常见的优化方式包括预处理、剪枝等。

### 推荐洛谷题目
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举和剪枝解决组合问题，与本题都涉及对多种情况的判断处理。
 - [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：对开关状态的模拟，和本题状态演变有相似之处，可锻炼模拟题的思维。
 - [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合数学知识与递推思想，与本题优化思路类似，都需要挖掘题目内在规律进行计算。

### 个人心得摘录与总结
 - **作者Hamer_sans**：最初写暴力模拟代码因时间复杂度高而TLE，后思考优化m的计算，采用类似前缀和思路记录距离，还发现首尾边界处理不当会导致错误。总结出做此类题要注意数据范围对复杂度的影响，以及边界情况的处理。 

---
处理用时：83.07秒