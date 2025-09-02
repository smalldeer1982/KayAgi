# 题目信息

# [USACO18FEB] Rest Stops S

## 题目描述

Farmer John 和他的私人教练 Bessie 正在攀登温哥华山。为了他们的目的（以及你的目的），这座山可以表示为一条长度为 $L$ 米的长直步道（$1 \leq L \leq 10^6$）。Farmer John 将以每米 $r_F$ 秒的恒定速度徒步（$1 \leq r_F \leq 10^6$）。由于他正在锻炼耐力，他不会在途中休息。

然而，Bessie 被允许在休息站休息，她可能会在那里找到一些美味的草。当然，她不能随便停下来！步道上有 $N$ 个休息站（$1 \leq N \leq 10^5$）；第 $i$ 个休息站距离步道起点 $x_i$ 米（$0 < x_i < L$），并且有一个美味值 $c_i$（$1 \leq c_i \leq 10^6$）。如果 Bessie 在第 $i$ 个休息站休息 $t$ 秒，她会获得 $c_i \cdot t$ 的美味单位。

当不在休息站时，Bessie 将以每米 $r_B$ 秒的固定速度徒步（$1 \leq r_B \leq 10^6$）。由于 Bessie 年轻且健康，$r_B$ 严格小于 $r_F$。

Bessie 希望最大化她摄入的美味草量。但她担心 Farmer John；她认为如果在徒步的任何时刻她在步道上落后于 Farmer John，他可能会失去继续前进的动力！

请帮助 Bessie 找到在确保 Farmer John 完成徒步的情况下，她能获得的最大总美味单位。

## 说明/提示

在这个例子中，Bessie 最优的策略是在 $x=7$ 的休息站休息 $7$ 秒（获得 $14$ 个美味单位），然后在 $x=8$ 的休息站再休息 $1$ 秒（获得 $1$ 个美味单位，总共 $15$ 个美味单位）。

## 样例 #1

### 输入

```
10 2 4 3
7 2
8 1```

### 输出

```
15```

# AI分析结果

### 综合分析与结论
这些题解主要围绕贪心算法解决问题，不同题解在实现细节和复杂度上有所差异。多数题解先对休息站按美味值排序，再遍历计算最大美味值；部分题解通过后缀最大值、单调队列等方法避免排序，优化复杂度至 $O(n)$。

### 所选题解
- **作者：pzc2004（5星）**
    - **关键亮点**：思路清晰，代码简洁，注释详细，明确提醒开 `long long` 避免数据溢出。
    - **个人心得**：提到“要开 long long！！！~~别问我是怎么知道的~~”，暗示因未开 `long long` 踩过坑。
```cpp
#include <bits/stdc++.h>
using namespace std;
long long l,n,v1,v2,ans,a2;
struct sb {
    long long a,b;
}a[100001];
bool cmp(const sb &sb1,const sb &sb2) {
    return sb1.b>sb2.b;
}
int main() {
    scanf("%lld%lld%lld%lld",&l,&n,&v1,&v2);
    for(long long i=1;i<=n;i++) scanf("%lld%lld",&a[i].a,&a[i].b);
    sort(a+1,a+n+1,cmp);
    for(long long i=1;i<=n;i++) {
        if(a[i].a*v2+a2<=a[i].a*v1) {
            ans+=(a[i].a*v1-a[i].a*v2-a2)*a[i].b;
            a2=a[i].a*v1-a[i].a*v2;
        }
    }
    printf("%lld",ans);
}
```
核心思想：先按美味值对休息站排序，再遍历，若 Bessie 到当前休息站的时间加上已吃草时间小于等于 Farmer John 到该站的时间，就尽可能多地吃草并更新吃草时间。

- **作者：Lolierl（4星）**
    - **关键亮点**：无需排序，通过后缀最大值的方法，将时间复杂度优化到严格线性 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
using namespace std; 
const int N = 1e6 + 5; 
int l, n, rf, rb, s[N], t[N]; 
int main() {
    scanf("%d%d%d%d", &l, &n, &rf, &rb); 
    for(int i = 1; i <= n; i++) {
        int x, c; 
        scanf("%d%d", &x, &c); 
        t[x] = max(t[x], c); 
    }
    for(int i = l - 1; i >= 1; i--)
        s[i] = (t[s[i + 1]] > t[i])? s[i + 1] : i; 
    int x = 0; 
    long long ans = 0; 
    while(s[x + 1]) {
        ans += 1ll * (rf - rb) * (s[x + 1] - x) * t[s[x + 1]]; 
        x = s[x + 1]; 
    }
    printf("%lld", ans); 
    return 0; 
}
```
核心思想：先记录每个位置的最大美味值，再逆序遍历求出每个位置到终点的最大美味值所在位置，最后依次计算在这些位置能获得的美味值。

- **作者：封禁用户（4星）**
    - **关键亮点**：同样避免排序，通过逆序扫描找出每个阶段的最优解，将复杂度优化到 $O(n)$，且代码有详细的输入输出优化。
```cpp
#include <cstdio>
#include <iostream>
#include <cctype>
#include <cstring>
#include <map>
#include <stack>
#include <utility>
#include <string>
#include <algorithm>
#define gc() getchar()
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define dec(i,a,b) for(int i=(a);i>=(b);--i)
#define endll putchar('\n');
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int  MAXOUT=10000;
const int MAXBUF=10000;
char buf[MAXBUF],*ps=buf,*pe=buf+1;
// 此处省略输入输出优化函数
const int maxn=101101;
ll l,n,rf,rb;
struct kusa{
    ll dis,val;
    kusa(){}
    kusa(ll _dis,ll _val){dis=_dis;val=_val;}
}k[maxn];
bool operator <(const kusa &a,const kusa &b){
    if(a.val==b.val) return a.dis>b.dis;
    return a.val>b.val;
}
ll ans;
ll tmp_max;
bool decmax[maxn];
int tmp_dis=0;
int main(){
    in(l),in(n),in(rf),in(rb);
    rep(i,1,n) in(k[i].dis),in(k[i].val);
    dec(i,n,1)
        if(k[i].val>tmp_max) decmax[i]=true,tmp_max=k[i].val;
    rep(i,1,n)
        if(decmax[i]==true){
            ans+=k[i].val*(rf-rb)*(k[i].dis-tmp_dis);
            tmp_dis=k[i].dis;
        }
    out_int_ln(ans);
    write();
    return 0;
}
```
核心思想：逆序扫描休息站，标记每个阶段的最优解，再正序遍历计算最大美味值。

### 最优关键思路或技巧
- 避免排序：通过后缀最大值、逆序扫描等方法，将时间复杂度从 $O(n\log n)$ 优化到 $O(n)$。
- 贪心策略：优先选择美味值大的休息站，确保在不落后 Farmer John 的前提下获得最大美味值。

### 可拓展之处
同类型题可拓展到其他资源分配问题，如在一定时间或距离限制下，选择价值最高的物品。类似算法套路可用于解决具有最优子结构的问题，通过贪心策略逐步构建最优解。

### 推荐题目
- P1094 [NOIP2007 普及组] 纪念品分组
- P1223 排队接水
- P2240 【深基12.例1】部分背包问题

---
处理用时：46.44秒