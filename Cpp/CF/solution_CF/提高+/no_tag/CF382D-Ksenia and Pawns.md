# Ksenia and Pawns

## 题目描述

Ksenia has a chessboard of size $ n×m $ . Each cell of the chessboard contains one of the characters: "<", ">", "^", "v", "\#". The cells that contain character "\#" are blocked. We know that all chessboard cells that touch the border are blocked.

Ksenia is playing with two pawns on this chessboard. Initially, she puts the pawns on the chessboard. One cell of the chessboard can contain two pawns if and only if the cell is blocked. In other cases two pawns can not stand in one cell. The game begins when Ksenia put pawns on the board. In one move, Ksenia moves each pawn to a side adjacent cell in the direction of arrows painted on the cell on which the corresponding pawn sits (if the pawn sits on "\#", it does not move). Assume that Ksenia moves pawns simultaneously (see the second test case).

Of course, Ksenia plays for points. How can one calculate the points per game? Very simply! Let's count how many movements the first pawn made and how many movements the second pawn made, sum these two numbers — it will be the resulting score of the game.

Ksenia wonders: what is the maximum number of points she can earn (for that, she should place the pawns optimally well early in the game). Help her and find that number.

## 样例 #1

### 输入

```
1 1
#
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 4
####
#&gt;^{}#
####
```

### 输出

```
3```

## 样例 #3

### 输入

```
3 4
####
#&gt;&lt;#
####
```

### 输出

```
-1```

## 样例 #4

### 输入

```
7 5
#####
##v##
##v##
#####
##^{}##
##^{}##
#####
```

### 输出

```
4```

## 样例 #5

### 输入

```
7 5
#####
##v##
##v##
##&lt;##
##^{}##
##^{}##
#####```

### 输出

```
5```

# 题解

## 作者：Hoks (赞：1)

## 前言
duel 到的，瞪出来了，但是代码码了 $15$ min。

样例只能说蓝盆，不如去 CF 上看。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
首先这个题目就很容易想到图论建模。

走的方向都是固定的，就相当于是点与点之间连边。

考虑直接把点 $x,y$ 压为一个状态 $(x-1)m+y$。

发现题目中可能存在 $-1$ 的情况，优先考虑这个情况。

其实就是存在环，有环自然可以无限走了。

考虑判环，很自然的想到拓扑排序。

那么就先拓扑一遍，如果没能走到所有的点说明存在环，输出 $-1$。

考虑什么是答案。

答案其实就是选取两段路径使得长度之和最大。

那么求出了最长 $mx$ 和次长 $mxx$，答案即为 $\max(2\times mx-1,mx+mxx)$。

那如何求出所有的路径长度呢？

如果枚举起点，那么只能求出最长的路径而无法求出所有不同的可能路径长度。

所以考虑枚举终点，倒着往回走。

记忆化一下，碰到没走过的点就加入新答案，最后如上输出即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2010,mod=1e9+7,V=1e9,INF=0x3f3f3f3f3f3f3f3f;
int n,m,cnt,res,in[N*N],mp[N][N];char s[N][N];vector<int>e[N*N],ans;
int dxy[5][2]={{1,0},{0,1},{-1,0},{0,-1}};queue<int>q;
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
    inline bool chk(char c) { return !(c=='<'||c=='>'||c=='#'||c=='^'||c=='v'); }
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
inline int op(char c)
{
    if(c=='v') return 0;if(c=='>') return 1;
    if(c=='^') return 2;if(c=='<') return 3;
    return 4;
}
inline void bfs(int x,int y)
{
    queue<pair<int,pair<int,int>>> q;q.push({0,{x,y}});
    while(!q.empty())
    {
        int u=q.front().first+1,x=q.front().second.first,y=q.front().second.second;q.pop();
        if(mp[x][y]){put("-1");flush();exit(0);}mp[x][y]=1;
        if(s[x-1][y]=='v') q.push({u,{x-1,y}});
        if(s[x+1][y]=='^')  q.push({u,{x+1,y}});
        if(s[x][y-1]=='>') q.push({u,{x,y-1}});
        if(s[x][y+1]=='<') q.push({u,{x,y+1}});
        if(q.empty()) ans.emplace_back(u);
    }
}
signed main()
{
    n=read(),m=read();for(int i=1,l=0;i<=n;i++) rd(s[i],l),l=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            int opt=op(s[i][j]),dx=i+dxy[opt][0],dy=j+dxy[opt][1];
            if(opt==4) continue;e[(dx-1)*m+dy].emplace_back((i-1)*m+j);in[(i-1)*m+j]++;
        }
    for(int i=1;i<=n*m;i++) if(in[i]==0) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();cnt++;
        for(auto v:e[u]) if(!--in[v]) q.push(v);
    }
    if(cnt!=n*m){put("-1");goto genshin;}
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
        if(s[i][j]=='#')
        {
            if(s[i-1][j]=='v') bfs(i-1,j);
            if(s[i+1][j]=='^') bfs(i+1,j);
            if(s[i][j-1]=='>') bfs(i,j-1);
            if(s[i][j+1]=='<') bfs(i,j+1);
        }
    sort(ans.begin(),ans.end());reverse(ans.begin(),ans.end());
    if(ans.size()>1) res=ans[0]+ans[1];
    if(!ans.empty()) res=max(res,ans[0]*2-1);
    print(res);
    genshin:;flush();return 0;
}
```

---

## 作者：Starrykiller (赞：1)

建出对应的有向图，如果有环答案显然为 $-1$。

否则，答案只能有两种情况：

- 一条链上的两个点；
- 两条链上的两个点。

这启示我们求出 $f(i,j,0/1)$ 表示以 $(i,j)$ 结尾的最长/次长路径。将所有 $\texttt{\#}$ 的 $f(i,j,0/1)$ 排个序，对两种情况取 $\max$ 即可。

[My submission](https://codeforces.com/contest/382/submission/262707139)。/bx Hoks。

---

