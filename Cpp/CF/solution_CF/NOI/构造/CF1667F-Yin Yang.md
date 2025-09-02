# Yin Yang

## 题目描述

给定一个有 $n$ 行 $m$ 列的矩形网格，$n$ 和 $m$ 都能被 $4$ 整除。部分格子已经被染成黑色或白色。保证没有两个已染色的格子共享边或角。

请你给剩下的格子染色，使得所有黑色格子和所有白色格子分别都能通过正交方向（上下左右）连通，或者判断无解。

具体来说，把所有黑色格子看作图中的节点，如果两个格子共享一条边，则它们之间有一条边。如果这个图是连通的，则称黑色格子是正交连通的。白色格子同理。

## 说明/提示

第一个测试用例的解如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1667F/3dc9d1049e5e9d683890dfa8ead1eafd76cdf4e9.png)

第二个测试用例：可以发现黑色和白色部分无法同时连通，因此答案为 "NO"。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
8 8
.W.W....
.....B.W
.W.W....
.....W.W
B.B.....
....B.B.
B.W.....
....B.B.
8 8
B.W..B.W
........
W.B..W.B
........
........
B.W..B.W
........
W.B..W.B
8 12
W.B.........
....B...B.W.
B.B.........
....B...B.B.
.B..........
........B...
.W..B.B...W.
............
16 16
.W............W.
...W..W..W.W....
.B...........B.W
....W....W......
W......B....W.W.
..W.......B.....
....W...W....B.W
.W....W....W....
...B...........W
W.....W...W..B..
..W.W...W......B
............W...
.W.B...B.B....B.
.....W.....W....
..W......W...W..
W...W..W...W...W```

### 输出

```
YES
BWWWWWWW
BWBBBBBW
BWBWWWBW
BWBWBWBW
BWBWBWBW
BWBBBWBW
BWWWWWBW
BBBBBBBW
NO
YES
WWBBBBBBBBBB
BWWWBBBBBBWB
BBBWBBBWWWWB
BBBWBBBWBBBB
BBBWBBBWBBBB
BBBWWWWWBBBB
BWWWBBBWWWWB
BBBBBBBBBBBB
YES
WWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWW
WBBBBBBBBBBBBBWW
WBBBWBWWWWBWWBWW
WBBWWBBBWWBWWBWW
WBWWWBWWWWBWWBWW
WBBWWBBBWWBWWBWW
WWBWWWWWWWWWWWWW
WWBBBBBBBBBBBBWW
WBBBWWWBWWWBWBWW
WWWBWBBBWBBBWBBB
WWWBWBWWWWWBWWBW
WWWBWBBBWBBBWWBW
WWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWW```

# 题解

## 作者：_Arahc_ (赞：6)

3500 的构造题，自行体会……

## 题目描述

给定一个 $4n\times 4m$ 的方格图，每个格子都是黑色或白色。有些格子已经被涂色了，你要给剩下的格子涂色，使得黑色格子和白色格子分别组成连通块。构造一种方案或判断无解。

**保证已经被涂色的格子没有公共点或公共边。**

$4\leq 4n,4m\leq 500$，多组数据，数据组数 $\leq4000$，保证 $\sum nm \leq 250000$。

## 题解

注：题解配图中为了区分未染色格子和已染色格子，将黑白染色改为红蓝染色。

先来考虑一个简单的问题，如果四个边界上没有格子被染色，如何构造？

联想 [AGC004C And Gird](https://www.luogu.com.cn/problem/AT2043)，考虑构造“梳子”状的图案，如图 1：

![图 1](https://pic.imgdb.cn/item/62b6be7c094754312933b98b.png)

考虑到任意两个限制颜色的格子不八联通，这种方案一定是可行的。

然后考虑如果边界上有限制颜色的格子怎么做。首先如果边界上存在形如 `BWBW` 的序列，是一定无解的，如图 2（格子上有“限制”二字表示这个格子颜色固定）：

![图 2](https://pic.imgdb.cn/item/62b6bfc509475431293599be.png)

对于不存在形如 `BWBW` 序列的情况，不难发现，我们一定可以找到完整的一个边界（上/下/左/右），这条边上可以全部赋成同一个颜色，而且它对面那条边界上至少有一个点是不同的颜色。不妨把这个完整的边界上的颜色当成蓝色，参考图 1 “梳子”型构造的蓝色部分，给它安排好。

这样至少可以保证蓝色的格子相互之间可以连通了。现在处理红色格子，可以列举出如下三个不合法的情况，我们一一解决：

1. 边框被蓝色包围了，部分边框上的红色与梳子的条纹不联通。
2. 接近边框位置（第 $2$ 和第 $n-1$ 行）的格子不联通。
3. 红色梳子条纹不联通。

图 3 的三个例子分别对应了上面的三种不合法情况：

![图 3](https://pic.imgdb.cn/item/62b6c4de09475431293df46c.png)

~~你问我这些例子都是怎么来的？WA on test 1,2,3,17。~~

实际上这三种情况都可以通过简单的调整实现：

1. 你把下面也变成蓝色不行吗？
2. 因为上/下部分的蓝色是连通的，直接把道路打通就可以了。
3. 显然把蓝色都连起来之后，打穿一个蓝色条纹就可以连接起来。

注意这三种调整的顺序。

（请时刻注意 `BWBW` 的情况早就被判掉了，在这里是不存在的。）

主要的问题是这三个，其实还有很多琐碎的细节需要考虑。个人感觉就只凭这个细节难度都能值这个 3500 了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool Begin;
const int max_n=502;
inline int read(){
    int x=0;bool w=0;char c=getchar();
    while(c<'0' || c>'9') w|=c=='-',c=getchar();
    while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void write(int x){
    putchar(x==2?'B':'W');
}
inline int reads(){
    char c=getchar();
    while(c!='B' && c!='W' && c!='.') c=getchar();
    if(c=='B') return 2;
    if(c=='W') return 3;
    return 0;
}

int n,m,cntr;
int a[max_n][max_n],ans[max_n][max_n];

int Tmp[max_n][max_n];
inline void rotate(){
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=m;++j)
            Tmp[i][j]=a[i][j];
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=m;++j)
            a[j][n-i+1]=Tmp[i][j];
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=m;++j)
            Tmp[i][j]=ans[i][j];
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=m;++j)
            ans[j][n-i+1]=Tmp[i][j];
    swap(n,m),++cntr;
}
inline void clear(){
    cntr=0;
    for(register int i=0;i<=n;++i)
        for(register int j=0;j<=m;++j)
            a[i][j]=ans[i][j]=a[j][i]=ans[j][i]=0;
}

inline int calc(){
    int res=0;
    for(register int p=1;p<=2;++p){
        for(register int i=2;i<=m;++i)
            if(!ans[1][i])
                ans[1][i]=ans[1][i-1];
        for(register int i=2;i<=n;++i)
            if(!ans[i][m])
                ans[i][m]=ans[i-1][m];
        for(register int i=m-1;i;--i)
            if(!ans[n][i])
                ans[n][i]=ans[n][i+1];
        for(register int i=n-1;i;--i)
            if(!ans[i][1])
                ans[i][1]=ans[i+1][1];
        if(!ans[1][1])
            ans[1][1]=2;
    }
    for(register int i=2;i<=m;++i)
        if(ans[1][i]!=ans[1][i-1])
            ++res;
    for(register int i=2;i<=n;++i)
        if(ans[i][m]!=ans[i-1][m])
            ++res;
    for(register int i=m-1;i;--i)
        if(ans[n][i]!=ans[n][i+1])
            ++res;
    for(register int i=n-1;i;--i)
        if(ans[i][1]!=ans[i+1][1])
            ++res;
    return res;
}

inline bool Nice(){
    bool ok=0;
    for(register int i=1;i<=n;++i){
        if(ans[i][1]!=ans[1][1])
            return 0;
        if(i>1 && i<n && ans[i][m]!=ans[1][1])
            ok=1;
    }
    return ok;
}

int Red,Blue;

inline void findroad(int x,int y){
    if(ans[x-1][y]==Red || ans[x+1][y]==Red || ans[x][y+1]==Red) return;
    int X1=(x==2?1:n);
    if(y<=m-2 && ans[X1][y+2]==Red){
        ans[X1][y]=ans[X1][y+1]=Red;
        return;
    }
    int X2=(x==2?2:n-1);
    if(y<=m-2 && ans[X2][y+2]==Red){
        ans[X2][y+1]=Red;
        return;
    }
    int X3=(x==2?3:n-2),X4=(x==2?4:n-3);
    if(a[X4][y]!=Blue){
        ans[X3][y]=Red;
        return;
    }
    int Y=(y<=m-2?y+1:y-1);
    ans[X2][Y]=ans[X3][Y]=Red;
}

inline void bigroad(int x){
    for(register int j=2;j<=4;++j){
        bool ok=1;
        for(register int i=x-1;i<=x+2;++i)
            if(a[i][j]==Blue){
                ok=0;
                break;
            }
        if(ok){
            ans[x][j]=ans[x+1][j]=Red;
            return;
        }
    }
    for(register int i=x-1;i<=x+2;++i)
        if(!a[i][3])
            ans[i][3]=Red;
    if(a[x-1][3]){
        ans[x-1][2]=Blue,
        ans[x][4]=Red;
    }
    if(a[x+2][3]){
        ans[x+2][2]=Blue,
        ans[x+1][4]=Red;
    }
    if(a[x][3] || a[x+1][3]){
        ans[x][2]=ans[x+1][2]=Red;
    }
}

inline void buildroad(){
    int fr=0,ls=0;
    for(register int i=1;i<=n;++i)
        if(ans[i][m]==Red){
            if(!fr) fr=i;
            ls=i;
        }
    if(!fr || (ls>3 && fr<n-2)) return;
    if(ls<=3 && a[4][m-1]==Blue){
        ans[3][m]=ans[4][m]=ans[5][m]=Red;
        return;
    }
    if(fr>=n-2 && a[n-3][m-1]==Blue){
        ans[n-4][m]=ans[n-3][m]=ans[n-2][m]=Red;
        return;
    }
    int x=(ls<=3?2:n-2);
    for(register int i=x;i<=x+1;++i)
        for(register int j=m-1;j<=m;++j)
            if(!a[i][j])
                ans[i][j]=Red;
}

bool End;
#define File ""
signed main(){
    // #ifndef ONLINE_JUDGE
    // freopen(File ".in","r",stdin);
    // freopen(File ".out","w",stdout);
    // #endif
    for(register int T=read();T;--T,clear()){
        n=read(),m=read();
        for(register int i=1;i<=n;++i)
            for(register int j=1;j<=m;++j)
                a[i][j]=ans[i][j]=reads();
        int tmp=calc();
        if(tmp>=4){
            puts("NO");
            continue;
        }
        if(tmp>0) while(!Nice()) rotate();
        Blue=ans[1][1],Red=Blue^1;
        for(register int i=2;i<n;++i)
            for(register int j=2;j<m;++j)
                if(!a[i][j])
                    ans[i][j]=(i%4>1?Blue:Red);
        for(register int i=1;i<n;++i)
            if(ans[i][m-1]==ans[i+1][m] && ans[i+1][m-1]==ans[i][m] && ans[i][m]!=ans[i+1][m]){
                if(!a[i][m]) ans[i][m]^=1;
                else ans[i+1][m]^=1;
            }
        buildroad();
        for(register int i=2;i<m;++i){
            if(a[2][i]==Red) findroad(2,i);
            if(a[n-1][i]==Red) findroad(n-1,i);
        }
        for(register int i=6;i<=n-6;i+=4)
            if(ans[i][m]==Blue || ans[i+1][m]==Blue)
                bigroad(i);
        while(cntr%4!=0) rotate();
        puts("YES");
        for(register int i=1;i<=n;++i){
            for(register int j=1;j<=m;++j)
                write(ans[i][j]);
            putchar('\n');
        }
    }
    return 0;
}
```

---

## 作者：sunkuangzheng (赞：2)

$\textbf{CF1667F *3500}$

> - 给定 $n \times m$ 的网格图，$n,m$ 是 $4$ 的倍数。有一些格子已经染上了红色、蓝色中的一种，有的格子还是空白。**保证一个已经染色的格子周围八个格子没有别的已经染色的格子**。

> - 给空白格子染色，使得所有蓝色格子四连通，所有红色格子四连通，或报告无解。

> - $8 \le n,m \le 500, \sum nm \le 2.5 \times 10^5$。

CF 上这题的 tag 只有 $\text{implementation}$。

## 0. 前言和约定

本题的另一篇题解存在一些小错误，且没有涉及太多细节。

这篇题解将详细的说明本题的各种细节。

所有图片中带 $\texttt{\#}$ 的格子表示题目已经限定颜色，$\texttt{x}$ 表示修改的位置。

## 1. 从边界空白出发

考虑本题的简单情况：保证边界格子都没有涂色。

这种情况下我们采用如下构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/1yutwms5.png)

即，第一行涂红，最后一行涂蓝，对于行 $i \in [2,n-1]$ 上的非 $\texttt{\#}$ 格子，如果列 $j \bmod 4 \le 1$ 涂蓝，否则涂红。以下我们称连续两个相同颜色的列为一个**条纹**，称第一行和最后一行为**边线**。

注意到 **$\texttt{\#}$ 格子不可能割断一个条纹**，而条纹一定与边线连通，所以对于一个格子，它只要与条纹连通就一定在大连通块里。容易发现上述构造中，所有红色格子周围都有红色条纹，蓝色格子同理，那么上述构造合法。

## 2. 有解条件？

寻找一个合法的**必要**条件：边界上不能顺时针出现 $\texttt{BWBW}$ 的子序列。这种情况下两个 $\texttt{B}$ 连通后一定会割断两个 $\texttt{W}$
 使其无法连通，故无解。
 
我们~~合理~~猜测这个条件也**充分**。下面直接给出构造。

下面请时刻记住，$\texttt{BWBW}$ 的子序列已经**不可能**出现。

## 3. 给边界染色

对于边界上每一个 $\texttt{\#}$，顺时针把前面的每一个格子涂成相同的颜色，直到遇到下一个 $\texttt{\#}$，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/7g6aprge.png)

（如果不存在 $\texttt{\#}$ 则强行染红 $(1,1)$）

显然只会有不超过两个边界上会有两种颜色，我们一定能找到一个颜色全都相同的边界，且颜色不同的边界在对面。把这个边界放在最上面，后面可以省去一些讨论。

## 4. 让红色格子连通

我们不能完全按照 $1$ 中方法涂色，但是大部分各自仍然可以这样涂。上面的边线我们可以全部涂红，红色条纹可以涂红，这样涂完红色格子都会连通，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/mhkyc8ds.png)

此后，蓝色格子会出现三种不连通情况。

## 5. 处理下方边线

这种情况下会出现较多情况，第一种即上图，格子 $(8,3),(8,4),(7,3),(7,4)$ 形成一个 X 形让蓝色区域不连通。此时我们直接修改底边那个不是 $\texttt{\#}$ 的格子，例如上图就翻转 $(8,4)$ 将其变成蓝色。

另外两种情况及处理方式如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/e7dfutld.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/z77jrzu6.png)

注意右边可能会出现类似情况，处理方式大体相同。请注意左右不会同时出现这种情况，否则就会出现 $\texttt{BWBW}$。

这一段代码如下：

```cpp
    //a 是正在涂色的数组，lim 是原来的网格。
    int fi = 1e9,lt = 0;
    for(int i = 1;i <= m;i ++) if(a[n][i] == Y) fi = min(fi,i),lt = i;
    if(fi == 1e9 || fi < m-2 && lt > 3);
    else if(lt <= 3 && a[n-1][4] == X) a[n][3] = a[n][4] = a[n][5] = Y;
    else if(fi >= m - 2 && a[n-1][m-3] == X) a[n][m-2] = a[n][m-3] = a[n][m-4] = Y;
    else{
        int p = (lt <= 3 ? 2 : m - 2); 
        for(int i = p;i <= p + 1;i ++) for(int j = n - 1;j <= n;j ++)
            if(!lim[j][i]) a[j][i] = Y;
    }
```

这样两边的蓝条纹就会和蓝边线连通。

## 6. 处理孤立蓝色

因为最后一列和第一列没有完全填蓝，所以第 $2,m-2$ 列会出现孤立蓝色，大概有这四种情况。基本思路是打穿红色块，和中间蓝色条纹连通。**注意保持红色连通**。

![](https://cdn.luogu.com.cn/upload/image_hosting/svtsws0h.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/wye1wjvj.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/jz9dqe9d.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/1qz3slux.png)

这样以后蓝色孤立点消失，这一部分代码如下。

```cpp
    for(int i = 2;i < n;i ++) if(a[i][2] == Y  && a[i-1][2] == X && a[i+1][2] == X && a[i][1] == X && a[i][3] == X) 
        if(i != n - 1 && a[i+2][1] == Y) a[i][1] = a[i+1][1] = Y;
        else if(a[i-2][2] == Y) a[i-1][2] = Y; 
        else if(a[i][4] != X && lim[i][3] != X) a[i][3] = Y;
        else if(i != 2 && a[i-1][4] != X) a[i-1][2] = a[i-1][3] = Y;
        else a[i+1][2] = a[i+1][3] = Y;
    for(int i = 2;i < n;i ++) if(a[i][m-1] == Y && a[i-1][m-1] == X && a[i+1][m-1] == X&& a[i][m] == X && a[i][m-2] == X) 
        if(i != n - 1 && a[i+2][m] == Y) a[i][m] = a[i+1][m] = Y;
        else if(a[i-2][m-1] == Y) a[i-1][m-1] = Y; 
        else if(a[i][m-3] != X && lim[i][m-2] != X) a[i][m-2] = Y;
        else if(i != 2 && a[i-1][m-3] != X) a[i-1][m-1] = a[i-1][m-2] = Y;
        else a[i+1][m-1] = a[i+1][m-2] = Y; 
```

## 7. 连接蓝色条纹

多个蓝色条纹之间可能不连通。

![](https://cdn.luogu.com.cn/upload/image_hosting/w92cll1t.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/4nokyur9.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/9d6zn0r8.png)

请注意情况二中，一定要红色补在上面，蓝色涂在下面，因为 $(5,5)$ 格子如果是蓝色障碍，填反了红色会不连通。（WA on test 17 可能是因为这个）

这一部分代码如下。


```cpp
    auto con = [&](int x){
        for(int i = 2;i <= 4;i ++)
            if(lim[i][x-1] != X && lim[i][x] != X && lim[i][x+1] != X && lim[i][x+2] != X)
                return a[i][x] = a[i][x + 1] = Y,void();
        for(int i = x - 1;i <= x + 2;i ++) if(lim[3][i] != X) a[3][i] = Y;
        if(lim[3][x - 1] == X) a[4][x] = Y,a[2][x - 1] = X;
        if(lim[3][x + 2] == X) a[4][x + 1] = Y,a[2][x + 2] = X;
        if(lim[3][x] == X || lim[3][x + 1] == X) a[2][x] = a[2][x + 1] = Y;
    };
    for(int i = 6;i <= m - 6;i += 4) if(a[n][i] == X || a[n][i + 1] == X) con(i);
```

## 8. 完整代码


```cpp
/**
 *    author: sunkuangzheng
 *    created: 26.02.2024 14:32:14
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 2e3+5;
using namespace std;
int T,n,m,a[N][N],b[N][N],rott,lim[N][N],c[N][N],tc,fkfg; string s[N];
void los(){
    cin >> n >> m;
    for(int i = 1;i <= n;i ++) cin >> s[i],s[i] = " " + s[i];
    for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++)
        a[i][j] = (s[i][j] == 'W' ? 1 : (s[i][j] == 'B' ? 2 : 0)),lim[i][j] = a[i][j];
    auto around = [&]{
        vector<int> fk; int cnt = 0;
        for(int _ = 1;_ <= 2;_ ++){
            for(int i = 2;i <= m;i ++) if(!a[1][i]) a[1][i] = a[1][i-1];
            for(int i = 2;i <= n;i ++) if(!a[i][m]) a[i][m] = a[i-1][m];
            for(int i = m - 1;i >= 1;i --) if(!a[n][i]) a[n][i] = a[n][i+1];
            for(int i = n - 1;i >= 1;i --) if(!a[i][1]) a[i][1] = a[i+1][1];
            if(!a[1][1]) a[1][1] = 1;
        }for(int i = 1;i <= m;i ++) fk.push_back(a[1][i]);
        for(int i = 1;i <= n;i ++) fk.push_back(a[i][m]);
        for(int i = m;i >= 1;i --) fk.push_back(a[n][i]);
        for(int i = n;i >= 1;i --) fk.push_back(a[i][1]);
        for(int i = 1;i < fk.size();i ++) cnt += (fk[i] != fk[i - 1]);
        return cnt;
    };auto rot = [&](){
        for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) b[i][j] = a[i][j],c[i][j] = lim[i][j];
        for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) a[j][n - i + 1] = b[i][j],lim[j][n - i + 1] = c[i][j];
        ++ rott,swap(n,m);
    };auto ck = [&](){
        int fg = 0;
        for(int i = 1;i <= m;i ++){
            if(a[1][i] != a[1][1]) return 0;
            fg |= (i > 1 && i < m && a[1][i] != a[n][i]);
        }return fg;
    }; int ti = around();
    if(ti >= 3) return cout << "NO\n",void();
    cout << "YES\n";
    if(ti) while(!ck()) rot();
    int X = a[1][1],Y = 3 - a[1][1];
    for(int i = 2;i < n;i ++) for(int j = 2;j < m;j ++)
        if(!lim[i][j]) a[i][j] = (j % 4 > 1 ? X : Y);
    for(int i = 1;i < m;i ++)
        if(a[n][i] == a[n-1][i+1] && a[n-1][i] == a[n][i+1] && a[n][i] != a[n][i+1])
            if(!lim[n][i]) a[n][i] = 3 - a[n][i]; else a[n][i+1] = 3 - a[n][i+1];
    int fi = 1e9,lt = 0;
    for(int i = 1;i <= m;i ++) if(a[n][i] == Y) fi = min(fi,i),lt = i;
    if(fi == 1e9 || fi < m-2 && lt > 3);
    else if(lt <= 3 && a[n-1][4] == X) a[n][3] = a[n][4] = a[n][5] = Y;
    else if(fi >= m - 2 && a[n-1][m-3] == X) a[n][m-2] = a[n][m-3] = a[n][m-4] = Y;
    else{
        int p = (lt <= 3 ? 2 : m - 2); 
        for(int i = p;i <= p + 1;i ++) for(int j = n - 1;j <= n;j ++)
            if(!lim[j][i]) a[j][i] = Y;
    }for(int i = 2;i < n;i ++) if(a[i][2] == Y  && a[i-1][2] == X && a[i+1][2] == X && a[i][1] == X && a[i][3] == X) 
        if(i != n - 1 && a[i+2][1] == Y) a[i][1] = a[i+1][1] = Y;
        else if(a[i-2][2] == Y) a[i-1][2] = Y; 
        else if(a[i][4] != X && lim[i][3] != X) a[i][3] = Y;
        else if(i != 2 && a[i-1][4] != X) a[i-1][2] = a[i-1][3] = Y;
        else a[i+1][2] = a[i+1][3] = Y;
    for(int i = 2;i < n;i ++) if(a[i][m-1] == Y && a[i-1][m-1] == X && a[i+1][m-1] == X&& a[i][m] == X && a[i][m-2] == X) 
        if(i != n - 1 && a[i+2][m] == Y) a[i][m] = a[i+1][m] = Y;
        else if(a[i-2][m-1] == Y) a[i-1][m-1] = Y; 
        else if(a[i][m-3] != X && lim[i][m-2] != X) a[i][m-2] = Y;
        else if(i != 2 && a[i-1][m-3] != X) a[i-1][m-1] = a[i-1][m-2] = Y;
        else a[i+1][m-1] = a[i+1][m-2] = Y; 
    auto con = [&](int x){
        for(int i = 2;i <= 4;i ++)
            if(lim[i][x-1] != X && lim[i][x] != X && lim[i][x+1] != X && lim[i][x+2] != X)
                return a[i][x] = a[i][x + 1] = Y,void();
        for(int i = x - 1;i <= x + 2;i ++) if(lim[3][i] != X) a[3][i] = Y;
        if(lim[3][x - 1] == X) a[4][x] = Y,a[2][x - 1] = X;
        if(lim[3][x + 2] == X) a[4][x + 1] = Y,a[2][x + 2] = X;
        if(lim[3][x] == X || lim[3][x + 1] == X) a[2][x] = a[2][x + 1] = Y;
    };
    for(int i = 6;i <= m - 6;i += 4) if(a[n][i] == X || a[n][i + 1] == X) con(i);
    while(rott % 4) rot(); rott = 0;
    for(int i = 1;i <= n;i ++,cout << "\n") for(int j = 1;j <= m;j ++)
        cout << (a[i][j] == 1 ? 'W' : 'B');
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

## 9. 一些数据

都是我 WA 过的，如果上面哪个情况讨论漏了，这些数据可能能帮你查出来。

```
8
8 8
.....B.B
B.W.....
.....W..
.W.W...B
........
.B....W.
...B....
.W...B.B
8 8
.W.W....
.....B.W
.W.W....
.....W.W
B.B.....
....B.B.
B.W.....
....B.B.
8 8
....B.W.
B.W.....
....B..W
..B.....
B...B.W.
........
.B.W.W.W
........
8 8
....B..B
.W......
...W.W..
.......B
W..W.W..
.......W
.B.B.B..
.......W
8 8
...W.W..
.W.....W
....W...
B.W....B
....B...
.W......
...W.W.B
.B......
8 8
.......W
.B.W.B..
........
W.B..B.W
........
B.B.B.W.
........
.B..B.W.
8 12
.B.B........
......W..W.B
B...W.......
..W.....W.B.
B....W......
...B...B....
.W........W.
....B.W.W...
8 12
B.W.........
......B.W...
W..B......B.
........W...
...W.W....W.
.W.....W....
...B.W....W.
............
```

上面的数据全都有解。

其实把各种情况讨论清楚后，本题也并不是特别难写啦！

~~我就调了一个下午一个晚上和半个上午就过了！！！111~~

---

