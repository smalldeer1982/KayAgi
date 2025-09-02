# 题目信息

# TV Shows

## 题目描述

There are $ n $ TV shows you want to watch. Suppose the whole time is split into equal parts called "minutes". The $ i $ -th of the shows is going from $ l_i $ -th to $ r_i $ -th minute, both ends inclusive.

You need a TV to watch a TV show and you can't watch two TV shows which air at the same time on the same TV, so it is possible you will need multiple TVs in some minutes. For example, if segments $ [l_i, r_i] $ and $ [l_j, r_j] $ intersect, then shows $ i $ and $ j $ can't be watched simultaneously on one TV.

Once you start watching a show on some TV it is not possible to "move" it to another TV (since it would be too distracting), or to watch another show on the same TV until this show ends.

There is a TV Rental shop near you. It rents a TV for $ x $ rupees, and charges $ y $ ( $ y < x $ ) rupees for every extra minute you keep the TV. So in order to rent a TV for minutes $ [a; b] $ you will need to pay $ x + y \cdot (b - a) $ .

You can assume, that taking and returning of the TV doesn't take any time and doesn't distract from watching other TV shows. Find the minimum possible cost to view all shows. Since this value could be too large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, the optimal strategy would be to rent $ 3 $ TVs to watch:

- Show $ [1, 2] $ on the first TV,
- Show $ [4, 10] $ on the second TV,
- Shows $ [2, 4], [5, 9], [10, 11] $ on the third TV.

This way the cost for the first TV is $ 4 + 3 \cdot (2 - 1) = 7 $ , for the second is $ 4 + 3 \cdot (10 - 4) = 22 $ and for the third is $ 4 + 3 \cdot (11 - 2) = 31 $ , which gives $ 60 $ int total.

In the second example, it is optimal watch each show on a new TV.

In third example, it is optimal to watch both shows on a new TV. Note that the answer is to be printed modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
5 4 3
1 2
4 10
2 4
10 11
5 9
```

### 输出

```
60```

## 样例 #2

### 输入

```
6 3 2
8 20
6 22
4 15
20 28
17 25
20 27
```

### 输出

```
142```

## 样例 #3

### 输入

```
2 1000000000 2
1 2
2 3
```

### 输出

```
999999997```

# AI分析结果

### 题目内容
# 电视节目

## 题目描述
有 $n$ 个你想看的电视节目。假设整个时间被划分为相等的部分，称为“分钟”。第 $i$ 个节目从第 $l_i$ 分钟播放到第 $r_i$ 分钟，包括两端。

你需要一台电视来看一个节目，并且你不能在同一台电视上同时观看两个同时播放的节目，所以在某些分钟你可能需要多台电视。例如，如果区间 $[l_i, r_i]$ 和 $[l_j, r_j]$ 相交，那么节目 $i$ 和节目 $j$ 不能在同一台电视上同时观看。

一旦你在某台电视上开始观看一个节目，就不可能将它“转移”到另一台电视上（因为这会太分散注意力），或者在这个节目结束之前在同一台电视上观看另一个节目。

你附近有一家电视租赁店。它出租一台电视收费 $x$ 卢比，并且对于你多保留电视的每一分钟额外收取 $y$（$y < x$）卢比。所以为了在 $[a; b]$ 分钟内租用一台电视，你需要支付 $x + y \cdot (b - a)$。

你可以假设，取电视和还电视不需要任何时间，也不会分散你观看其他电视节目的注意力。找到观看所有节目可能的最小成本。由于这个值可能太大，将其对 $10^9 + 7$ 取模后输出。

## 说明/提示
在第一个例子中，最优策略是租 $3$ 台电视来观看：
 - 在第一台电视上观看节目 $[1, 2]$，
 - 在第二台电视上观看节目 $[4, 10]$，
 - 在第三台电视上观看节目 $[2, 4], [5, 9], [10, 11]$。

这样，第一台电视的成本是 $4 + 3 \cdot (2 - 1) = 7$，第二台是 $4 + 3 \cdot (10 - 4) = 22$，第三台是 $4 + 3 \cdot (11 - 2) = 31$，总计 $60$。

在第二个例子中，最优的方法是在每台新电视上观看每个节目。

在第三个例子中，最优的方法是在一台新电视上观看两个节目。注意答案要对 $10^9 + 7$ 取模后输出。

## 样例 #1
### 输入
```
5 4 3
1 2
4 10
2 4
10 11
5 9
```
### 输出
```
60```

## 样例 #2
### 输入
```
6 3 2
8 20
6 22
4 15
20 28
17 25
20 27
```
### 输出
```
142```

## 样例 #3
### 输入
```
2 1000000000 2
1 2
2 3
```
### 输出
```
999999997```

### 算法分类
贪心

### 题解综合分析与结论
这几道题解都采用贪心策略解决问题，核心思路都是在选用原有电视和借新电视之间进行权衡，以达到最小花费。不同题解在具体实现上略有差异，有的通过对区间端点进行排序后扫描，利用栈来维护可用电视；有的通过对区间按左端点排序，使用multiset 来寻找合适的合并区间。

### 所选的题解
 - **作者：p_b_p_b (5星)**
    - **关键亮点**：思路清晰简洁，代码实现直接明了。将节目开始和结束时间存入数组并标记，按时间和开始/结束顺序排序后扫描，利用栈来贪心选择使用旧电视还是租新电视，很好地实现了贪心策略。
    - **个人心得**：提到题目难度被评高，认为思维和代码实现难度不大。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define sz 200020
#define mod (int)(1e9+7)
using namespace std;
typedef long long ll;
struct hh{ll t,id;bool d;}s[sz];
inline bool cmp(const hh &x,const hh &y){return x.t==y.t?x.d<y.d:x.t<y.t;}
struct hhh{ll l,r;}a[sz];
int n;
ll X,Y;
int main()
{
    ll i,x,y;
    cin>>n>>X>>Y;
    for (i=1;i<=n;i++) cin>>x>>y,a[i]=(hhh){x,y},s[i*2-1]=(hh){x,i,0},s[i*2]=(hh){y,i,1};
    stack<int>st;
    ll ans=0;
    sort(s+1,s+n+n+1,cmp);
    for (i=1;i<=n+n;i++)
    {
        if (s[i].d) st.push(s[i].t);
        else
        {
            y=a[s[i].id].r;
            if (st.empty()) (ans+=(X+Y*(y-s[i].t)%mod)%mod)%=mod;
            else
            {
                x=st.top();
                if (Y*(y-x)<X+Y*(y-s[i].t)) (ans+=Y*(y-x)%mod)%=mod,st.pop();
                else (ans+=(X+Y*(y-s[i].t)%mod)%mod)%=mod;
            }
        }
    }
    cout<<ans;
}
```
    - **核心实现思想**：先将每个节目起止时间转化为带有开始/结束标记的结构体数组，排序后遍历。遇到节目开始，若栈为空则租新电视；若栈不为空，比较使用栈顶电视（最近结束的电视）和租新电视的花费，选择花费小的方式并更新答案。遇到节目结束，将结束时间压入栈。
 - **作者：一扶苏一 (4星)**
    - **关键亮点**：对贪心策略的两个结论给出了详细的感性理解和证明，使得贪心思路更具说服力。代码实现上通过结构体和重载运算符进行排序等操作，逻辑清晰。
    - **核心代码片段**：
```cpp
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
    const int L = 1000000;
    char buf[L], *front=buf, *end=buf;
    char GetChar() {
        if (front == end) {
            end = buf + fread(front = buf, 1, L, stdin);
            if (front == end) return -1;
        }
        return *(front++);
    }
}

template <typename T>
inline void qr(T &x) {
    rg char ch = IPT::GetChar(), lst = ' ';
    while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
    while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
    if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
    rg char ch = IPT::GetChar(), lst = ' ';
    while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
    while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
    if (ch == '.') {
        ch = IPT::GetChar();
        double base = 1;
        while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
    }
    if (lst == '-') x = -x;
}

namespace OPT {
    char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
    if (x < 0) {x = -x, putchar('-');}
    rg int top=0;
    do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
    while (top) putchar(OPT::buf[top--]);
    if (pt) putchar(aft);
}

const int maxn = 100010;
const int maxm = 200010;
const int MOD = 1000000007;

struct M {
    int l, r;
    inline bool operator<(const M &_others) const {
        return this->r < _others.r;
    }
};
M MU[maxn];

struct Zay {
    int id, pos;
    bool Is_Begin;
    inline bool operator<(const Zay &_others) const {
        if (this->pos!= _others.pos) return this->pos < _others.pos;
        else if (this->Is_Begin ^ _others.Is_Begin) return this->Is_Begin;
        else return this->id < _others.id;
    }
};
Zay CU[maxm];

int n, x, y, cnt, scnt, ans;
int stack[maxm];

int main() {
    freopen("1.in", "r", stdin);
    qr(n); qr(x); qr(y);
    for (rg int i = 1; i <= n; ++i) {
        qr(MU[i].l); qr(MU[i].r);
        Zay &_temp = CU[++cnt];
        _temp.id = i; _temp.pos = MU[i].l; _temp.Is_Begin = true;
        Zay &_tp = CU[++cnt];
        _tp.id = i; _tp.pos = MU[i].r;
    }
    std::sort(CU + 1, CU + 1 + cnt);
    for (rg int i = 1; i <= cnt; ++i) {
        if (CU[i].Is_Begin) {
            ll payd = x + 1ll * (MU[CU[i].id].r - MU[CU[i].id].l) * y;
            if (scnt) {
                if ((1ll * (MU[CU[i].id].r - stack[scnt]) * y) < payd) {
                    payd = 1ll * (MU[CU[i].id].r - stack[scnt]) * y;
                    --scnt;
                }
            }
            ans = (ans + payd) % MOD;
        } else {
            stack[++scnt] = CU[i].pos;
        }
    }
    qw(ans, '\n', true);
    return 0;
}
```
    - **核心实现思想**：与上一题解类似，先将节目起止时间转化为特定结构体数组并排序。遍历过程中，节目开始时计算租新电视花费，若有可用旧电视（栈不为空），比较使用旧电视和租新电视花费，选择花费小的更新答案；节目结束时将结束时间存入栈。
 - **作者：_edge_ (4星)**
    - **关键亮点**：先计算所有区间单独播放的花费，再通过左端点排序，利用multiset 寻找合适的区间合并，优化了计算过程，代码简洁高效。
    - **核心代码片段**：
```cpp
#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#define int long long 
using namespace std;
const int Mod=1e9+7;
const int INF=1e5+5;
struct _node_data{
    int l,r;
}aa[INF];
int n,x,y,l[INF],r[INF],ans; 
multiset <int> s;
bool cmp(_node_data xx,_node_data yy) {
    return xx.l<yy.l;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n>>x>>y;
    for (int i=1;i<=n;i++)
        cin>>l[i]>>r[i],ans+=x,ans+=y*(r[i]-l[i])%Mod,ans%=Mod,aa[i].l=l[i],aa[i].r=r[i];
    sort(aa+1,aa+1+n,cmp);
    for (int i=1;i<=n;i++)
        l[i]=aa[i].l,r[i]=aa[i].r;
    for (int i=1;i<=n;i++) {
        multiset<int>::iterator it=s.lower_bound(l[i]);
        if (s.begin()==it) { 
            s.insert(r[i]);
            continue;
        }
        it--;
        if ((l[i]-(*it))*y<x) {
            ans+=(l[i]-(*it))*y%Mod-x%Mod;ans%=Mod;
            ans+=Mod;ans%=Mod;
            s.erase(s.find(*it));
        }    
        s.insert(r[i]);
    }
    ans%=Mod;
    ans+=Mod;ans%=Mod;
    cout<<ans<<"\n";
    return 0;
}
```
    - **核心实现思想**：先假设每个节目单独用一台电视，计算总花费。对节目按左端点排序后遍历，对于每个节目，在multiset 中寻找最接近其左端点的右端点，若合并这两个节目区间能减少花费，则更新答案并从multiset 中移除该右端点，最后将当前节目右端点插入multiset。

### 最优关键思路或技巧
1. **贪心策略**：在选用原有电视和租新电视之间进行贪心选择，优先使用最近结束的旧电视，以减少空闲时间带来的额外花费。
2. **数据结构运用**：利用栈或multiset 来高效维护可用电视或可合并区间的信息，便于快速做出贪心决策。

### 可拓展思路
此类题目属于区间贪心问题，类似套路包括对区间端点进行排序后扫描，根据题目条件在不同选择中进行贪心决策。例如在安排会议、活动等资源分配场景下，通过合理贪心策略优化资源使用成本。

### 洛谷相似题目推荐
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
2. [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
3. [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)

### 个人心得摘录与总结
p_b_p_b 认为本题思维和代码实现难度不大，却被评成紫题，强调题目难度评估与实际感受的差异。这提醒我们在做题时不能仅依据题目难度评级来判断，需亲自实践体会题目实际难度，同时也反映出不同人对题目难度感知的主观性。 

---
处理用时：113.47秒