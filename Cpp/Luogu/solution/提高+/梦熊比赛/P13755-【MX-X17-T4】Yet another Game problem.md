# 【MX-X17-T4】Yet another Game problem

## 题目描述

Alice 和 Bob 又在玩游戏。有一个序列 $a_1,a_2,\ldots,a_n$ 和一个区间 $[l,r]$ 初始为 $[1,n]$。双方都知道所有的信息，Alice 和 Bob 将轮流对这个区间进行操作，Alice 先手。

- 若轮到 Alice 操作，她可以选择一个 $i$（$l<i\le r$），并把区间变为 $[i,r]$。
- 若轮到 Bob 操作，他可以选择一个 $i$（$l\le i< r$），并把区间变为 $[l,i]$。

当 $l=r$ 时，游戏结束。最终得分即为 $a_l$。

Alice 希望这个最终得分尽可能大，Bob 则希望最终得分尽可能小。假设双方都采用最优策略，请问最终得分会是多少？有时为了防止你蒙混过关，Alice 还要你告诉她第一步应该如何操作。

## 说明/提示

**【样例解释 #1】**

Alice 可以直接把区间 $[1,5]$ 变成 $[5,5]$，最终得分为 5。显然没有比这更优的操作了。

**【样例解释 #2】**

Alice 先把区间 $[1,5]$ 变成区间 $[4,5]$，随后 Bob 把区间 $[4,5]$ 变成区间 $[4,4]$，最终得分为 4。可以证明这是唯一可能的操作过程。

**【数据范围】**

|测试点编号|$n$|$\mathit{op}$|
|:-:|:-:|:-:|
|$1\sim 4$|$\le 100$|$=0$|
|$5\sim 10$|$\le 3000$|$=0$|
|$11\sim 18$|$\le 10^6$|$=0$|
|$19\sim 20$|$\le 10^6$|$=1$|

对于 $100\%$ 的数据，$2\le n\le 10^6$，$\mathit{op} \in\{0,1\}$，$1 \le a_i \le 10^9$。

## 样例 #1

### 输入

```
5 0
1 2 3 4 5```

### 输出

```
5```

## 样例 #2

### 输入

```
5 1
2 5 1 4 3```

### 输出

```
4
1
4```

# 题解

## 作者：P2441M (赞：2)

## 题意

给定一个长度为 $n$ 的序列 $a$。Alice 和 Bob 对一个初始为 $[1,n]$ 的区间轮流操作，Alice 先手。

- Alice 操作时需要选择一个 $i(l<i\leq r)$，把区间变成 $[i,r]$。
- Bob 操作时需要选择一个 $i(l\leq i<r)$，把区间变成 $[l,i]$。

当 $l=r$ 时游戏结束，得分为 $a_l$。Alice 希望最大化得分，Bob 希望最小化得分。求两人都采用最优策略时最终的得分。部分测试点还要求给出 Alice 所有可能的第一步的操作方案。$2\leq n\leq 10^6$，$1\leq a_i\leq 10^9$。

## 题解

没做出来真是唐完了。

二分答案 $x$，转化为判定最终得分是否能 $\geq x$。套路地把 $a$ 中 $\geq x$ 的位置变为 $1$，$<x$ 的位置变为 $-1$，那么就需要判定是否能使最终得分为 $1$。

直接给出结论：先手必胜的充要条件为 $a$ 中存在一个**非空真后缀**的和 $\geq 0$。

:::info[证明]{open}
使用数学归纳法。$n=2$ 时命题显然成立。

设后缀和 $suf_i=\sum\limits_{j=i}^n a_i$。

先证充分性。我们证明其逆否命题：若 $a$ 中**不**存在一个非空真后缀的和 $\geq 0$，则后手必胜。首先先手显然不能一步得胜，其次，先手操作完后，设当前区间为 $[p,n]$，那么考察 $suf[p+1,n]$ 中最靠前的最大值的位置 $pos$，后手只需将区间操作为 $[p,pos-1]$ 即可保证依然不存在非空真后缀的和 $\geq 0$，因为此时对于 $\forall p\leq i<pos$，必然有 $suf_i<suf_{pos}$。

再证必要性。先手必胜，实际上意味着当他把区间操作成 $[p,n]$ 后，无论后手怎么选择 $q(p\leq q<n)$，$a[p,q]$ 中都存在一个非空真后缀的和 $\geq 0$，也就是说必然有 $\max\limits_{i=p+1}^q suf_i\geq suf_{q+1}$，即 $suf_{p+1}$ 为 $suf[p+1,n]$ 中的**非严格最大值**。同时我们不能让后手一步取胜，所以还要有 $suf_p\geq suf_{p+1}$。我们可以发现，这两个条件等价于 $suf_p$ 是 $suf[p,n]$ 中的**严格最大值**。于是取 $p$ 为 $suf$ 中最靠后的最大值的位置即可。

$\Box$
:::

这样我们就能 $\mathcal{O}(n)$ check 了。

上述证明实际上也给出了 Alice 第一步的操作方案：取所有 $p$ 使得 $suf_p$ 为 $suf[p,n]$ 的严格最大值即可。

时间复杂度 $\mathcal{O}(n\log{V})$，其中 $V$ 表示 $a$ 的值域。

## 代码

```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e6 + 5;

int n, op, v, a[N];
int sz, ans[N];

bool check(int x) {
	int s = 0;
	for (int i = n; i > 1; --i) if ((s += (a[i] >= x ? 1 : -1)) >= 0) return 1;
	return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> op;
    for (int i = 1; i <= n; ++i) cin >> a[i], chk_max(v, a[i]);
    int l = 0, r = v;
    while (l < r) {
    	int mid = l + r + 1 >> 1;
    	if (check(mid)) l = mid;
    	else r = mid - 1;
    }
    cout << l << '\n';
    if (!op) return 0;
    for (int i = 1; i <= n; ++i) a[i] = a[i] >= l ? 1 : -1;
    int s = 0, mx = -1;
    for (int i = n; i > 1; --i) if ((s += a[i]) > mx) mx = s, ans[++sz] = i;
    cout << sz << '\n';
    for (int i = sz; i; --i) cout << ans[i] << ' ';
    return 0;
}
```

---

## 作者：Hoks (赞：1)

## 前言
复健来了。

第一眼感觉是很像[这个](https://www.luogu.com.cn/problem/CF1710E)题，结果还真挺像就是。
## 思路分析
看到题肯定想法很多，第一眼的感觉就是区间 dp。

我们定义 $f_{l,r,0/1}$ 为 $[l,r]$ 这个区间，Alice/Bob 最优选择能得到的最大/最小分数。

边界条件就是 $l=r$ 的时候，简单 dp 转移一下可以拿到 $50$ pts。

然后就在这个 dp 的优化上卡死了，因为状态数是 $O(n^2)$ 的，除非去除无用状态才能优化复杂度。

但貌似没有很大的说法，所以我们考虑来换做法。

不难发现我们存在一个比较大的问题就是不知道答案是多少，所以无法判断 Alice 如果移动到当前点是否优秀。

所以考虑二分出答案 $ans$。

那么序列中的所有数就可以被我们划分为**胜点**与**败点**（对于 Alice 而言）。

然后我们基于这个**胜点败点**来考虑双方的决策。

首先这个序列肯定是变成了一串胜点一串败点交替的样子，很容易发现在 Alice 操作后 $l$ 肯定在胜点上，对 Bob 也同理。

进一步拓展的，我们可以注意到，如果胜负还未定，那么 Alice 移动完 $l$ 所在的一段连续**胜点**数一定比下一段连续**败点**数多。

这个比较容易理解，如果数量少了的话 Bob 直接把 $r$ 移到下一段败点末尾 Alice 就必败了。

透过这个性质我们其实就可以推出正解了。

结论：若令胜点权值为 $1$，败点权值为 $0$，那么必胜当且仅当存在非空后缀和 $\ge0$，且 Alice 选择的点必然满足为后缀和最大值（即选了点 $x$，后缀和为 $s$ 满足 $s_x>\max\limits_{i=x+1}^n s_i$）。

我们尝试来证明这个结论。

当 Alice 选择后缀和最大值这些点时，显然是一定满足我们前面所说的所有结论的，此时我们来考虑 Bob 的策略。

Bob 的选择大致有如下两种：
  
1. 被迫移动一步。
2. 主动移动一大块并且满足其中 $1$ 比 $0$ 多。

因为 $1,0$ 的差值就是后缀和，所以 Bob 移动一个区间 $[x,y]$ 变动的 $1,0$ 差值就是 $s_x-s_{y+1}$。

为了方便解释我们引入经典概念折线图，直接数形结合将 $s$ 的图像画出来，这里为了方便直接轴对称距离。

![](https://cdn.luogu.com.cn/upload/image_hosting/ctiakwqy.png)

这里假设 Alice 最开始在最右端的点，那么 Bob 不管怎么移都**一定**会在 Alice **下方**，也就是这里还满足 $1$ 的数量比 $0$ 多。

那么这样拖下去到最后结束还是 $1$ 比 $0$ 多，也就是 Alice 获胜。

同时这里仍然满足我们前面所提出的那个结论，因此充分性成立。

然后就是必要性的问题，我们不妨考虑 Alice 到达上图中比第一个山峰低的一个位置。

此时 Bob 即可将 $r$ 拉到峰顶位置，不妨截取出这段发现会是 $11100000$ 这种类似，必然会存在 $0$ 比 $1$ 多的情况。

那么此时 Bob 只要套用 Alice 的必胜策略即可必胜，因此 Alice 的每一步必然是**后缀最大值**。

然后代码也就非常好实现了喵。
## 代码
```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=1e6+10,M=5e3+10,V=1e6,mod=1e9+7;
int n,m,a[N],b[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(long long x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c=='('||c==')'||c==':'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline bool check(int x)
{
    for(int i=1;i<=n;i++) b[i]=(a[i]>=x);
    for(int i=n,s=0;i>=2;i--)
    {
        s+=b[i]?1:-1;
        if(s>=0) return true;
    }return false;
}
inline void solve()
{
    n=read();m=read();for(int i=1;i<=n;i++) a[i]=read();int l=1,r=1e9,res=0;
    while(l<=r) if(check(mid)) res=mid,l=mid+1;else r=mid-1;print(res);put('\n');
    for(int i=1;i<=n;i++) b[i]=(a[i]>=res);int mx=-1;vector<int>c;
    for(int i=n,s=0;i>=1;i--) s+=b[i]?1:-1;if(!m) return;
    for(int i=n,s=0;i>=1;i--)
    {
        s+=b[i]?1:-1;if(i==1) break;
        if(s>mx) c.emplace_back(i);mx=max(mx,s);
    }sort(c.begin(),c.end());
    print(c.size());put('\n');for(auto x:c) print(x),put(' ');
}
signed main()
{
    int T=1;
    // T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Fzrcy (赞：0)

首先我们二分答案 $val$，设 $b_i=[a_i\ge val]$，Alice 的目标是使答案为 $1$，Bob 的目标是使答案为 $0$。

先考虑特殊情况：若 $b_n=1$，则 Alice 必胜；若 $b_{n-1}=1$ 且 $n>2$，则 Alice 必胜。

然后再考虑一般情况：若 Alice 选择 $i$，则 $i$ 必须满足 $b_{i}=b_{i+1}=1$，否则 Bob 可以选择 $i$ 或 $i+1$ 使 Alice 必败。同理，若 Bob 选择 $i$，则 $i$ 必须满足 $b_{i}=b_{i-1}=0$，否则 Bob 必败。

证明：若 Alice 选择的 $i$ 满足 $b_i=0$，则 Bob 接下来只需选择 $i$ 即可。若 Alice 选择的 $i$ 满足 $b_{i+1}=0$，则 Bob 只需选择 $i+1$，接下来 Alice 只能选择 $i+1$，此时 Alice 必败。Bob 的情况类似。


然后我们将所有 Alice 可能选择的 $i$ 视为左括号，Bob 可能选择的 $i$ 视为右括号，再对形成的括号序列进行匹配。

结论：Alice 必胜当且仅当存在未匹配的左括号。

证明：若 Alice 一开始选择一个匹配成功的左括号，则 Bob 只需选择与之匹配的右括号。接下来 Alice 每选择一个左括号，Bob 只需选择与之匹配的右括号即可（这个右括号一定存在），直到 Alice 没有左括号可以选，此时 Alice 必败。

若 Alice 一开始选择一个没有匹配成功的左括号，则 Bob 选择的右括号一定无法与之匹配，接下来 Alice 只需要不断选择与 Bob 选择的右括号匹配的左括号即可，最终 Bob 没有右括号可以选，此时 Alice 必胜。

因此操作第一步的方法就是选择一个未匹配的左括号和特殊情况。

总复杂度为 $O(n\log V)$。

```cpp
int n,a[N],b[N],stk[N],top;
inline bool judge(int val){
    for(int i=1;i<=n;i++)b[i]=(a[i]>=val);
    top=0;
    for(int i=2;i<n-1;i++){
        if(b[i]&&b[i+1])stk[++top]=i;
        if(b[i]==0&&b[i+1]==0&&top)top--;
    }
    if(n>2&&b[n-1])stk[++top]=n-1;
    if(b[n])stk[++top]=n;
    return top>0;
}
int main(){
    int L=1,R=1e9+1,ans=0,op; cin>>n>>op;
    for(int i=1;i<=n;i++)cin>>a[i];
    while(L<=R){
        int mid=L+R>>1;
        if(judge(mid))ans=mid,L=mid+1;
        else R=mid-1;
    }
    cout<<ans<<endl;
    if(op){
        judge(ans);
        cout<<top<<endl;
        for(int i=1;i<=top;i++)cout<<stk[i]<<' ';
    }
    return 0;
}
```

---

