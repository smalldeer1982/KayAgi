# X Aura

## 题目描述

Mount ICPC 可以被表示为一个网格，共有 $R$ 行（编号从 $1$ 到 $R$）和 $C$ 列（编号从 $1$ 到 $C$）。位于第 $r$ 行和第 $c$ 列的单元格被表示为 $(r, c)$，其高度为 $H_{r, c}$。两个单元格是相邻的，如果它们共享一条边。正式来说，$(r, c)$ 相邻于 $(r-1, c)$、$(r+1, c)$、$(r, c-1)$ 和 $(r, c+1)$，如果这些单元格存在。

你只能在相邻的单元格之间移动，每次移动都会产生一个惩罚。具有一个奇数正整数 $X$ 的气场，从高度为 $h_1$ 的单元格移动到高度为 $h_2$ 的单元格会产生 $(h_1 - h_2)^X$ 的惩罚。注意，惩罚可以是负数。

你想回答 $Q$ 个独立的场景。在每个场景中，你从起始单元格 $(R_s, C_s)$ 开始，想要移动到目标单元格 $(R_f, C_f)$，以最小的总惩罚。有些场景可能会使总惩罚变得任意小，这样的场景被称为无效的。找到从起始单元格到目标单元格的最小总惩罚，或者确定场景是否无效。

## 样例 #1

### 输入

```
3 4 1
3359
4294
3681
5
1 1 3 4
3 3 2 1
2 2 1 4
1 3 3 2
1 1 1 1```

### 输出

```
2
4
-7
-1
0```

## 样例 #2

### 输入

```
2 4 5
1908
2023
2
1 1 2 4
1 1 1 1```

### 输出

```
INVALID
INVALID```

## 样例 #3

### 输入

```
3 3 9
135
357
579
2
3 3 1 1
2 2 2 2```

### 输出

```
2048
0```

# 题解

## 作者：block_in_mc (赞：3)

显然，如果图中存在负环，从任何位置出发均能走到负环，所有询问答案均为 `INVALID`。由于 $X$ 是奇数，有 $(h_1-h_2)^X=-(h_2-h_1)^X$，即对于一个权值和为 $v$ 的环，反着走的权值为 $-v$。因此，图上所有环的权值和都为 $0$，否则这个环和其反向环中一定会有负环。

考虑如何判断图中是否有负环。不难发现，图中没有负环当且仅当 $(i,j),(i,j+1),(i+1,j+1),(i+1,j)$ 四个点组成的环（称其为方格）权值和均为 $0$。这样任意一个环都可以由若干个方格组合而来，其中的重叠部分正反经过次数相同，可以抵消。

这个图还有一个巧妙的性质，任意两个点间所有路径距离相同。考虑 $a$ 到 $b$ 的两条路径 $A,B$ 和 $b$ 到 $a$ 的一条路径 $C$，则有 $A+C=B+C=0$，即 $A=B$。同理可以得到 $a$ 到 $c$ 的距离等于 $a$ 到 $b$ 的距离加上 $b$ 到 $c$ 的距离。

因此，从 $O(1,1)$ 出发，计算到所有点的距离，$P_1$ 到 $P_2$ 的距离即为 $O$ 到 $P_2$ 的距离减去 $O$ 到 $P_1$ 的距离。

[提交记录](https://codeforces.com/contest/2045/submission/306998432)。

---

## 作者：lfxxx (赞：1)

注意到存在负环，一直走答案为负无穷，存在正环倒着走就变成负环了。

没有正环也没有负环？那这个图上不就等于没有环（保留任意一个树形结构后加入任意非树边不会改变任何两点间的距离），保留任意一个有树形结构并对于每个点计算出从其出发抵达根的路径权值之和即可做到 $O(R \times C + Q)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e3+114;
int dep[maxn][maxn];
char c[maxn][maxn];
int a[maxn][maxn];
int n,m,x;
bool flag=false;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res;
    if(b%2==1) res=res*a;
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>x;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>c[i][j],a[i][j]=c[i][j]-'0';
    }
    for(int i=2;i<=n;i++) dep[i][1]=dep[i-1][1]+qpow((a[i][1]-a[i-1][1]),x);
    for(int i=1;i<=n;i++){
        for(int j=2;j<=m;j++) dep[i][j]=dep[i][j-1]+qpow((a[i][j]-a[i][j-1]),x);
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            if(dep[i][j]-dep[i+1][j]+qpow((a[i+1][j]-a[i][j]),x)!=0) flag=true;
        }
    }
    int q;
    cin>>q;
    while(q--){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        if(flag==true) cout<<"INVALID\n";
        else cout<<dep[x1][y1]-dep[x2][y2]<<'\n';
    }
    return 0;
}
```

---

## 作者：Aurie (赞：0)

注意到，因为该图是连通图，所以全局有一个负环，则所有询问无解。在图中方向相反的边互为相反数，所以正环反过来走就是负环。因此若想有解，则所有环的长度必须为 $0$。此时只需判断四条边构成的小环，若所有小环长度都为 $0$，则全局所有环长度均为 $0$。

> 证明：  
> ![](https://cdn.luogu.com.cn/upload/image_hosting/52jwc3ii.png)  
> 若 $a+b+g+f=0,a+d+e-g=0$ 则带入消元消除 $g$ 可推出 $a+b+c+d+e+f=0$。  
> 更长的环同理可得。  

若全局的环长均为 $0$，则从 $a$ 到 $b$ 任意一条路径的长度都应相同，若不同，则可利用两条路径构造出一个非 $0$ 环。所以应先判无解，再任意走一条路即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void read(T &x){x=0;int f = 1;char ch = getchar();while(!isdigit(ch)){if(ch=='-'){f=-1;}ch=getchar();}while(isdigit(ch)){x = (x<<3)+(x<<1)+(ch^0x30);ch=getchar();}x*=f;}
template<typename T>
void print(const T &x){if(x>9)print(x/10);putchar(x%10|0x30);}
template<typename T>
void println(T x){if(x<0){putchar('-');x=-x;}print(x);putchar('\n');}
template<typename T>
void printcs(T x){if(x<0){putchar('-');x=-x;}print(x);putchar(' ');}

const int N = 1e3 + 10;

int n, m, q, x;

char h[N][N];

typedef long long ll;

int po(int x, int n) {
    int r = 1;
    while (n) {
        if (n & 1) r *= x;
        x *= x;
        n >>= 1;
    }
    return r;
}

ll dis[N][N];

int main(){
    read(n), read(m), read(x);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> h[i][j];
            h[i][j] ^= 0x30;
        }
    }
    // cout<<(int)h[1][1]<<endl;
    bool flag = false;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            // auto tmp = (po(h[i][j] - h[i + 1][j], x) +
            // po(h[i + 1][j] - h[i + 1][j + 1], x) +
            // po(h[i + 1][j + 1] - h[i][j + 1], x) + 
            // po(h[i][j + 1] - h[i][j], x)
            // );
            if (po(h[i][j] - h[i + 1][j], x) +
                po(h[i + 1][j] - h[i + 1][j + 1], x) +
                po(h[i + 1][j + 1] - h[i][j + 1], x) + 
                po(h[i][j + 1] - h[i][j], x) != 0
                ) {
                    flag = true;
                    // cout<<i<<'!'<<j<<' '<<tmp<<endl;
                }
        }
    }
    if (!flag) {
        dis[1][1] = 0;
        for (int i = 2; i <= n; i++) {
            dis[i][1] = dis[i - 1][1] + po(h[i - 1][1] - h[i][1], x);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 2; j <= m; j++) {
                dis[i][j] = dis[i][j - 1] + po(h[i][j - 1] - h[i][j], x);
            }
        }
    }
    read(q);
    int x, y, xx, yy;
    while (q--) {
        read(x), read(y), read(xx), read(yy);
        if (flag) {
            puts("INVALID");
            continue;
        }
        
        println(dis[xx][yy] - dis[x][y]);
    }
    return 0;
}
```

---

