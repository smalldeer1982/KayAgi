# Minibuses on Venus (easy version)

## 题目描述

This is the easy version of the problem. The only difference between the three versions is the constraints on $ n $ and $ k $ . You can make hacks only if all versions of the problem are solved.

Maxim is a minibus driver on Venus.

To ride on Maxim's minibus, you need a ticket. Each ticket has a number consisting of $ n $ digits. However, as we know, the residents of Venus use a numeral system with base $ k $ , rather than the decimal system. Therefore, the ticket number can be considered as a sequence of $ n $ integers from $ 0 $ to $ k-1 $ , inclusive.

The residents of Venus consider a ticket to be lucky if there is a digit on it that is equal to the sum of the remaining digits, modulo $ k $ . For example, if $ k=10 $ , then the ticket $ 7135 $ is lucky because $ 7 + 1 + 5 \equiv 3 \pmod{10} $ . On the other hand, the ticket $ 7136 $ is not lucky because no digit is equal to the sum of the others modulo $ 10 $ .

Once, while on a trip, Maxim wondered: how many lucky tickets exist? At the same time, Maxim understands that this number can be very large, so he is interested only in the answer modulo some prime number $ m $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1808E1/2314a7c75bce1209ddf61a583b83dbea8efe39a0.png)

## 说明/提示

In the first example, there are only four lucky tickets: $ 000 $ , $ 011 $ , $ 101 $ , and $ 110 $ .

## 样例 #1

### 输入

```
3 2 1000000007```

### 输出

```
4```

## 样例 #2

### 输入

```
3 4 1000000007```

### 输出

```
28```

# 题解

## 作者：Engulf (赞：0)

令第 $i$ 位上的数是 $a_i$，数的总和是 $S$，$x$ 满足条件当且仅当

$$\exist i\in[1, n] \ \textrm{s. t.} \\  a_i \equiv a_1 + a_2 + \cdots + a_{i - 1} + a_{i + 1} + \cdots + a_n\pmod k$$

即

$$a_i \equiv S - a_i\pmod k$$

即

$$2a_i \equiv S\pmod k$$

接下来提供两种方法。

## 方法一

容斥 + dp。

题目是存在性，如果直接去 dp 是会算重复的，直接一个容斥，求一下对于任意的 $i$，都满足 $2a_i \neq S(\bmod k)$ 的方案数，再用总方案数 $k^n$ 减去之就是存在的方案数。

考虑枚举 $S$，设 $f_{i, j}$ 为前 $i$ 位，数字和是 $S$ 的方案数。
- 状态转移方程：$f_{i, j + l} = f_{i, j + l} + f_{i - 1, l} (2l \not\equiv S \pmod k)$。
- 边界条件：$f_{0, 0} = 1$。
- 答案：$f_{n, S}$。

当然了，$S$ 以及转移里面的 $j + l$ 也是要对 $k$ 取模的。

$O(nk^3)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 105, K = 35;

int n, k, mod;

int f[N][K];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> mod;

    int ans = qpow(k, n);
    for (int s = 0; s < k; s++) {
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < k; j++)
                f[i][j] = 0;
        f[0][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < k; j++)
                if (2 * j % k != s % k)
                    for (int l = 0; l < k; l++)
                        f[i][(l + j) % k] = (f[i][(l + j) % k] + f[i - 1][l]) % mod;
        ans = (ans - f[n][s % k] + mod) % mod;
    }

    cout << ans << "\n";
    return 0;
}
```

## 方法二

数位 dp。

一样是枚举 $S$，dfs 的时候记一下是否存在了一个 $i$ 使得 $2a_i \equiv S(\bmod k)$，再记录一下数位和 $\textrm{sum}$，若 $\textrm{sum} = S$，并且存在这样的 $i$ 就返回 $1$。其他就是套模板。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 105, K = 35;

int n, k, mod;

int f[N][2][K];

int dfs(int pos, bool exi, int sum, int s) {
    if (!pos) return exi * (sum == s);
    if (~f[pos][exi][sum]) return f[pos][exi][sum];
    int res = 0;
    for (int i = 0; i < k; i++)
        res = (res + dfs(pos - 1, exi || (i * 2 % k == s % k), (sum + i) % k, s)) % mod;
    return f[pos][exi][sum] = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> mod;

    int ans = 0;
    for (int i = 0; i < k; i++) {
        memset(f, -1, sizeof f);
        ans = (ans + dfs(n, 0, 0, i)) % mod;
    }

    cout << ans << "\n";
    return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
dp 还是太烂了，写过的 trick 都得想半天。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
首先发现题目询问的是**存在**方案数，显然不是很好做。

直接经典 trick，容斥一下拿总方案数减去不合法方案数即可。

接着来考虑怎么求**对于任意一位都不满足其他位数之和与这一位同余**。

因为 $n,k$ 很小，考虑直接设计 $f_{i,j}$ 表示前 $i$ 位，总和为 $j$ 的方案数。

但这样的话还是很不好做，因为无法判掉不合法状态。

考虑枚举出了总和 $s$，那么对于一个数 $x$，题目中的式子即可表示为：
$$x\equiv s-x(\bmod k)$$
移项可得：
$$2\times x\equiv s(\bmod k)$$
枚举完 $s$ 后，直接枚举位置 $i$，总和 $j$，第 $i$ 位填 $x$ 判完上面那个条件后转移即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=310,INF=0x3f3f3f3f3f3f3f3f;
int n,k,mod,ans,f[N][35];
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
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
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
inline int ksm(int x,int y,int mod)
{
    int res=1;
    while(y){if(y&1) res=res*x%mod;x=x*x%mod;y>>=1;}
    return res;
}
signed main()
{
    n=read(),k=read(),mod=read();
    for(int s=0;s<k;s++)
    {
        memset(f,0,sizeof f);f[0][0]=1;
        for(int i=1;i<=n;i++)
            for(int j=0;j<k;j++)
                for(int l=0;l<k;l++)
                {
                    if(2*l%k==s) continue;
                    f[i][j]=(f[i][j]+f[i-1][(j-l+k)%k])%mod;
                }
        ans=(ans+f[n][s])%mod;
    }print(((ksm(k,n,mod)-ans)%mod+mod)%mod);
    genshin:;flush();return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目分析】**

只能过 E1 的数位 dp 做法。

分析题目，题目中的条件即至少存在一个 $1 \le i \le n$，使得 $a_i \equiv s - a_i \pmod k$，其中 $s = \sum\limits_{i=1}^n a_i \bmod k$，即各数位之和 。化简后得 $2a_i \equiv s \pmod k$。

我们先考虑 $k \le 10$ 的做法，此时显然可以状态压缩，设 $f_{pos,sta,sum}$ 表示到了第 $pos$ 位，数字的 $2$ 倍模 $k$ 的出现状态是 $sta$，和模 $k$ 的结果是 $sum$ 的方案数。该做法的空间复杂度是 $\mathcal O(2^knk)$。

上面的做法并不会 MLE，但是也不会 AC，因为它 CE 了。我们考虑 $n,k$ 都相对小，我们枚举 $k$ 的值。调整数位 dp 状态设计，设 $f_{pos,sum,ok}$ 表示到了第 $pos$ 位，和模 $k$ 的结果是 $sum$，当前是否出现过 $2a_i \bmod k  = p$，其中 $p$ 是枚举的 $k$ 值。然后就可以转移啦，数字合法的条件是 $ok= 1$ 且 $sum = p$。

以下提供两种写法的代码捏。

**【代码 $1(\text{CE})$】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,mod,k,f[105][1073741824][31];
int dfs(int pos,int sta,int sum){
    if(pos == n + 1) return ((sta >> sum) & 1);
    if(f[pos][sta][sum] != -1) return f[pos][sta][sum];
    int ans = 0;
    for(int i = 0;i < k;i ++) ans = (ans + dfs(pos+1,sta|(1<<(2*i%k)),(sum+i)%k)) % mod;
    return f[pos][sta][sum] = ans;
}
signed main(){
    cin >> n >> k >> mod,memset(f,-1,sizeof(f)),cout << dfs(1,0,0);
}
```

**【代码 $2(\text{AC})$】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,mod,k,f[105][35][2],ans;
int dfs(int pos,int sum,int ok,int p){
    if(pos == n + 1) return (ok && sum == p);
    if(f[pos][sum][ok] != -1) return f[pos][sum][ok];
    int ans = 0;
    for(int i = 0;i < k;i ++) ans = (ans+dfs(pos+1,(sum+i)%k,ok || 2*i%k==p,p)) % mod;
    return f[pos][sum][ok] = ans;
}signed main(){
    cin >> n >> k >> mod;
    for(int i = 0;i < k;i ++) memset(f,-1,sizeof(f)),ans = (ans+dfs(1,0,0,i)) % mod;
    cout << ans;
}
```

---

## 作者：masonpop (赞：0)

这个版本就是朴素 dp。

考虑反面，将存在性变为任意性。设所有数的和是 $S$，则不满足条件的序列等价于任意 $1\le i\le n$，$2a_i \not\equiv S  \pmod k$。

直接考虑枚举总和。设 $f_{i,j}$ 表示考虑到第 $i$ 位，当前总和是 $j$（模 $k$ 意义下）有多少种情况，转移直接用 $f_{i-1,(j-t)\bmod k}$ 来更新 $f_{i,j}$。其中 $t=a_i$，可以枚举所有合法的值实现。这样复杂度是 $O(nk^3)$ 的，可以通过 E1。[代码](https://codeforces.com/contest/1808/submission/220017939)。

---

