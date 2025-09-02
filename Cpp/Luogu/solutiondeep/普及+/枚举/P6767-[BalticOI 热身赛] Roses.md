# 题目信息

# [BalticOI 热身赛] Roses

## 题目背景

因为特殊原因，本题目另外 $24$ 组数据请在 [这里](https://www.luogu.com.cn/problem/U127462) 提交。

Valentine 是人赢。

## 题目描述

现在 Valentine 要给他的 $N$ 个妹子买玫瑰花，现在 Valentine 面前有两家店，每一家店有无数朵玫瑰花，但是他们按束卖。第一家店一束花里有 $A$ 朵，每一束花要用 $B$ 块钱。第二家店一束花里有 $C$ 朵，每一束花要用 $D$ 块钱。

求 Valentine 至少买 $N$ 朵花最少需要花多少钱。

至少可以这么理解，假如 $M>N$，但是买 $M$ 朵花的钱比买 $N$ 朵花的少，Valentine 就会买 $M$ 朵花，并把多出来的花给其他妹子，没错，Valentine 很花心。

## 说明/提示

#### 样例说明

对于样例 $1$，Valentine 可以选择在第二家店买 $2$ 束花。

对于样例 $2$，Valentine 可以选择在第一家店买 $1$ 束花，在第二家店买 $2$ 束花。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$N,A,B,C,D \le 1000$。
- Subtask 2（80 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N \le 10^{15}$，$1 \le A,B,C,D \le 10^5$，保证答案不超过 $10^{18}$。

#### 说明

翻译自 [BalticOI 2020 Day0 B Roses](http://www.boi2020.lv/data/tasks/en/day0/roses.pdf)。

与 BalticOI 2012 Day0 A 内容一致。

## 样例 #1

### 输入

```
5 1 4 3 6```

### 输出

```
12```

## 样例 #2

### 输入

```
22 2 3 10 14```

### 输出

```
31```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何计算购买至少 $N$ 朵花的最小花费展开。核心思路是先比较两种花束的性价比，优先选择性价比高的花束购买，再通过枚举另一种花束的购买数量来找到最小花费。不同题解的差异主要在于枚举的范围和优化方式。部分题解通过限制枚举次数、利用最大公约数等方法优化了时间复杂度，避免了超时。

### 所选题解
- **sysong（4星）**
  - **关键亮点**：思路清晰，先尝试简单枚举，在遇到超时问题后逐步分析并优化，最终通过限制循环次数解决问题。
  - **个人心得**：在提交代码时先取得了 TLE 的成绩，还有一个点过不了。之后发现把多买的部分替换掉后价格会增加，设置 flag 优化却得到 WA 结果。最后发现拿掉和新买部分可能多买，结合 $A,C \le 10^{5}$ 的条件，最多循环 $10^{5}$ 次就能计算可能最优的情况。
- **zjh111111（4星）**
  - **关键亮点**：通过数学推导得出枚举性价比低的个数即可，复杂度为 $\mathcal{O}(a)$，优化了枚举范围。
- **快斗游鹿（4星）**
  - **关键亮点**：先确定先买性价比高的花最优，再通过数学分析找到枚举的上界为 $\dfrac{a}{\gcd(a,c)}$，减少了不必要的枚举。

### 重点代码及核心实现思想
#### sysong
```c++
#include <bits/stdc++.h>
#define R register
#define gc() getchar()
#define ll long long
#define ld long double
using namespace std;

inline ll rd(){
    R ll x=0;R char c=gc();
    while(c>'9'||c<'0')c=gc();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
    return x;
}

int main(){
    ll n=rd(),a=rd(),b=rd(),c=rd(),d=rd(),ans=1e18;
    ld x=b*1.0/a,y=d*1.0/c;
    if(x>y)swap(a,c),swap(b,d);
    ll s=(n+a-1)/a;
    for(R ll i=s,k,f=100000;i>=0&&f;i--,f--) {
        k=i*b+max((ll)0,n-i*a+c-1)/c*d;
        if(k<ans)ans=k;
    }
    printf("%lld\n",ans);
    return 0;
}
```
**核心实现思想**：先比较两种花束的单价，将单价低的花束作为主要购买对象，计算至少需要购买的束数 $s$。然后从 $s$ 开始枚举，每次计算总花费 $k$，更新最小花费 $ans$。为了避免超时，限制循环次数为 $10^{5}$。

#### zjh111111
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
template <typename T>
inline void read(T &x) {
    char c = getchar(); int w = 1; x = 0;
    while (!isdigit(c))
        (c == '-') && (w = -w), c = getchar();
    while (isdigit(c))
        x = (x << 1) + (x << 3) + (c ^ '0'), c = getchar();
    x *= w;
}

int n, a, b, c, d, ans = 1e18;
inline int gcd(int x, int y) {
    return (!y) ? x : gcd(y, x % y);
}
signed main() {
    read(n); read(a); read(b); read(c); read(d);
    if (a*d < b*c) swap(a, c), swap(b, d);
    for (register int i=0; i<=a/gcd(a, c); ++i) {
        int x = n-c*i, res = i*d;
        if (x > 0) res += ((x-1)/a+1)*b;
        ans = min(ans, res);
    }
    cout << ans;
    return 0;
}
```
**核心实现思想**：通过数学推导得出枚举性价比低的个数即可，枚举范围为 $0$ 到 $\dfrac{a}{\gcd(a, c)}$。对于每个枚举的 $i$，计算购买 $i$ 束性价比低的花束后，还需要购买的性价比高的花束数量，从而计算总花费 $res$，更新最小花费 $ans$。

#### 快斗游鹿
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b,c,d,ans=1145141919810000;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int getcost(int sum,int flo,int cost){
    if(sum<=0)return 0;
    if(sum%flo==0)return sum/flo*cost;
    else return (sum/flo+1)*cost;
}
signed main(){
    n=read();a=read();b=read();c=read();d=read();
    if(a*d<b*c){
        swap(a,c);
        swap(b,d);
    }
    int k=a/__gcd(a,c);
    ans=getcost(n,a,b);
    for(int i=1;i<=k;i++){
        ans=min(ans,i*d+getcost(n-i*c,a,b));
    } 
    cout<<ans;
    return 0;
}
```
**核心实现思想**：先比较两种花束的性价比，将性价比高的花束作为主要购买对象，计算只买该花束的花费作为初始最小花费 $ans$。然后从 $1$ 到 $\dfrac{a}{\gcd(a, c)}$ 枚举购买性价比低的花束的数量 $i$，每次计算总花费并更新最小花费 $ans$。

### 最优关键思路或技巧
- **性价比比较**：先比较两种花束的单价，优先选择性价比高的花束购买。
- **枚举优化**：通过数学分析找到枚举的上界，如 $\dfrac{a}{\gcd(a, c)}$ 或 $10^{5}$，减少不必要的枚举，避免超时。

### 可拓展之处
同类型题可能会有更多种类的花束可供选择，或者有其他限制条件，如每种花束的数量有限等。类似算法套路可以是先比较各种方案的性价比，再通过枚举或其他优化方法找到最优解。

### 推荐题目
- P1007 独木桥
- P1012 拼数
- P1020 导弹拦截

### 个人心得总结
部分题解作者在调试过程中遇到了超时（TLE）和答案错误（WA）的问题。通过不断分析和尝试，发现了多买、替换部分可能导致的问题，以及利用题目给定的数据范围和数学性质（如最大公约数）来优化枚举范围，最终解决了问题。这提醒我们在解题时要注意边界情况和优化算法，遇到问题要逐步分析，尝试不同的方法。 

---
处理用时：58.08秒