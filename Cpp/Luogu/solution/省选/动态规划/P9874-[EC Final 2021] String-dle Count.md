# [EC Final 2021] String-dle Count

## 题目描述

当大多数人都沉迷于玩 Wordle 的时候，庞教授却已经沉迷于玩 String-dle 了。

String-dle 是一个有趣的猜字符串的游戏，玩家在玩的时候要通过几轮尝试，猜出一个长度为 $k$ 的字符串。并且在每轮尝试中，玩家要提交一个长度为 $k$ 的字符串来作为他的猜测，而系统通过以下伪代码来为提交的猜测评级：
```
def grading(answer, guess):
  let count be a hash map
  for i = 1 to k:
    if answer[i] not in count:
      count[answer[i]] = 1
    else:
      count[answer[i]] = count[answer[i]] + 1
  let grade be an array of length k
  for i = 1 to k:
    if answer[i] == guess[i]:
      grade[i] = 'O'
      count[guess[i]] = count[guess[i]] - 1
  for i = 1 to k:
    if answer[i] != guess[i]:
      if count[guess[i]] > 0:
        grade[i] = '-'
        count[guess[i]] = count[guess[i]] - 1
      else:
        grade[i] = 'x'
  return grade
```
返回的评级包括 $\tt{O}$（大写字母 O）、$\tt{-}$（破折号）和 $\tt{x}$（小写字母 x），且玩家可以基于先前的评级进行下一次猜测。下面是庞教授玩的一局游戏示例：
```
G: CRANE
A: xx--x
G: UTTER
A: xxOxx
G: NASAL
A: OOxOO
G: NATAL
A: OOOOO
```
在字符串 $\tt{G}$ 后面的是庞教授的猜测，以及在字符串 $\tt{A}$ 后面的是该次猜测的评级。

庞教授非常喜欢这个游戏。他确信他已经知道了这个游戏的完美策略。然而，今天他很生气，因为他认为评级系统出了问题！他想让人写一个分析程序，根据他的猜测与评级找出所有可能的可以作为答案的字符串。

由于评级系统可能出了问题，所以它可能不再符合上面给出的伪代码。具体来说，你需要找到所有符合输入的字符串。一个符合输入的字符串是指，对于输入中任意一个猜测  $g$ 和它的正确评级 $d$，都符合  `grading(s, g)=d`。

当然，你接受了这个任务。

## 说明/提示

对于第二个样例:

如果答案是 $\tt{ACDEF}$，则 $\tt{BBBAA}$ 的评级为 $\tt{xxx-x}$.

## 样例 #1

### 输入

```
2 5
CRANE
xx--x
NASAL
OOxOO```

### 输出

```
21```

## 样例 #2

### 输入

```
1 5
BBBAA
xxxx-```

### 输出

```
0```

## 样例 #3

### 输入

```
2 5
ABCDE
-xxxx
ABCDE
xxxxx```

### 输出

```
0```

## 样例 #4

### 输入

```
1 3
ABC
---```

### 输出

```
2```

## 样例 #5

### 输入

```
1 15
AAAAAAAAAAAAAAB
-xxxxxxxxxxxxxx```

### 输出

```
918547951```

## 样例 #6

### 输入

```
1 15
AAAAAAAAAAAAAAA
-xxxxxxxxxxxxxx```

### 输出

```
0```

## 样例 #7

### 输入

```
1 1
K
x```

### 输出

```
25```

# 题解

## 作者：mskqwq (赞：1)

从题目给的条件可以得到以下信息：

- 每种字符的出现次数的上下界：对于一种字符，它在一条信息中一定是前面一段横杠，后面一段 X，中间可能有一些 O，否则无解。那么它的出现次数的下界就是横杠的数量加上 O 的数量，如果存在 X 的话上界也是这个数。
- 每个位置不能填/必须填某个字符。

设字符 $c$ 的出现次数上下界分别为 $r_c$ 和 $l_c$，那么 $\sum l_i > k$ 或 $l_c>r_c$ 则无解。然后考虑 dp，设 $f_{S}$ 目前填的字符构成的可重集为 $S$ 的方案数。

这个集合 $S$ 是可以用一个长度为 $k$ 的二进制数 $s$ 表示的，将 $s$ 二进制下按位分成 $27$ 组，长度分别为 $l_A \dots l_{Z}$ 和 $k-\sum l_i$。对于 $i \le 26$，第 $i$ 组的 $1$ 的个数表示填了多少个第 $i$ 个字符。然后还要考虑填的个数超过 $l_i$ 的情况，把这些字符丢到第 $27$ 组里表示就行。

时间复杂度为 $O(|\sum|2^k)$。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define mems(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char c=getchar();int f=1,x=0;
    for(;c<48||c>57;c=getchar())if(c=='-') f=-1;
    for(;47<c&&c<58;c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x*f;
}
const int N=21,mod=1e9+7;
int f[1<<N],n,k,L[30],R[30],p[N],vis[N][30],sum[30];
char s[N],t[N];vector<int> vt;
int lowbit(int x){return x&-x;}
int get(int s,int c){
    return s|(lowbit(~(s>>sum[c]))<<sum[c]);
}
void add(int &x,int y){((x+=y)>=mod)&&(x-=mod);}
bool ck(int s,int c){
    int p=c==26?k-sum[c]:L[c],k=(s>>sum[c])&((1<<p)-1);
    return k!=(1<<p)-1;
}
void work(int s,int i){
    if(ck(s,i)) add(f[get(s,i)],f[s]);
    else if(R[i]==1270&&sum[26]!=k&&ck(s,26)) add(f[get(s,26)],f[s]);
}
void misaka(){
    n=read(),k=read();
    rep(i,0,25) R[i]=1270;
    rep(i,1,k) p[i]=-1;
    rep(__,1,n){
        scanf("%s%s",s+1,t+1);
        rep(c,0,25){
            int cnt=0,flag=0;
            rep(i,1,k)if(s[i]-'A'==c){
                if(t[i]=='O'){
                    if(vis[i][c]) puts("0"),exit(0);
                    rep(j,0,25)if(j^c) vis[i][j]=1;
                    p[i]=c,cnt++;
                }
                if(t[i]=='-'){
                    if(flag||p[i]==c) puts("0"),exit(0);
                    vis[i][c]=1,cnt++;
                }
                if(t[i]=='x'){
                    if(p[i]==c) puts("0"),exit(0);
                    flag=1,vis[i][c]=1;
                }
            }
            L[c]=max(L[c],cnt);
            if(flag) R[c]=min(R[c],cnt);
        }
    }
    rep(c,0,25)if(L[c]>R[c]) puts("0"),exit(0);
    rep(i,1,k)if((~p[i])&&vis[i][p[i]]) puts("0"),exit(0);
    f[0]=1;
    rep(i,1,26) sum[i]=sum[i-1]+L[i-1];
    if(sum[26]>k) puts("0"),exit(0);
    rep(s,0,(1<<k)-2)if(f[s]){
        int x=pc(s)+1;
        if(~p[x]) work(s,p[x]);
        else rep(i,0,25)if(!vis[x][i]) work(s,i);
    }
    printf("%d",f[(1<<k)-1]);
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=1;
    while(T--) misaka();
    return 0;
}
```

---

## 作者：zheng_zx (赞：1)

## P9874 [EC Final 2021] String-dle Count

[题目传送门](https://www.luogu.com.cn/problem/P9874)

### 分析

---

其实，最后每一种字符只有两种状态：

1. 出现了 $x$，此时就已经知道该字符有多少个了。

2. 没有出现 $x$，那么相当于知道了这个字符至少有多少个记为 $L_i$。

同时，我们可以维护出每一个位置不可以填某个字符。

考虑从左往右填，记录一个状态为填了前 $i$ 个字符；

由于有下界的限制，因此还需要每种字符已经出现了多少次。

由于 $\sum L_i \le k$，因此可以简单地压成一个二进制数。

至于具体出现了多少次的字符，只需要保证再出现够 $L_i$ 个字符后不再转移即可。

---

## 作者：Sampson_YW (赞：1)

对于一条限制，如果出现了 `O`，那么就表示这个位置上必须填某个字符。如果出现了 `-`，那么就可以知道某个字符**至少**出现了几次，记为 $L_i$。如果出现了 `x`，那么就可以知道某个字符**恰好**出现了几次，记为 $R_i$。并且如果某个位置是 `-` 或 `x`，那么就表示这个位置上不能填某个字符。

如果有 $L_i>R_i$ 或者 $\sum L_i>k$，那么无解。否则 $\sum L_i\leq k$，可以将这些字符状压成一个长度为 $\sum L_i$ 的二进制位，代表填没填过。每次转移就枚举一个字符，判断一下这个字符能不能填到这个位置上，并且填上之后有是不是仍然满足出现次数的限制，如果两个条件都满足就可以转移。

转移分为：填出现次数小于 $L_i$ 的字符，填出现次数大于等于 $L_i$ 的字符两种。前一种每次转移的枚举次数是 $O(k)$ 的，后一种每次转移的枚举次数是 $O(|\Sigma|)$ 的。

所以直接暴力转移的复杂度是 $O\left((|\Sigma|+k)k2^k\right)$ 的，我没跑过去。对于第二种转移预处理：只考虑出现次数的限制时，能填的字符是哪些。复杂度 $O(k^22^k)$。

[code](https://www.luogu.com.cn/paste/ic6fb9mv)

---

