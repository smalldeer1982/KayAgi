# Fractal Detector

## 题目描述

Vasya是个喜欢分型的男孩

他会先画出一个2$\times$2的白色格子,然后在上面任意的涂色。这是他的第一次操作。

接下来的若干次操作，他把原先黑色的格子变为2$\times$2的黑格子，原先白色的格子变成刚开始涂好色的颜色。

比如Vasya刚开始把2$\times$2的右上角的格子涂黑，他能得到以下图形

![](https://cdn.luogu.org/upload/vjudge_pic/CF228C/e8422806af6330609da67545ef59f385e8f81169.png)

图中,Vasya一共做了三次操作

一天Vasya累了，他不想画分形图形了，于是他随手画了一个图，想要知道里面有多少个至少经过两次操作的分形图形

## 说明/提示

对于第一个样例，如下图红色、蓝色、绿色所示所示

![](https://cdn.luogu.org/upload/vjudge_pic/CF228C/0e3ee6f0bc356a0362f898d820ceb6d14269c83c.png)

对于第二个样例，并没有合法的分形图形

![](https://cdn.luogu.org/upload/vjudge_pic/CF228C/52949284a400689262d98e354fadec0c60f26f1b.png)

## 样例 #1

### 输入

```
6 11
......*.***
*.*.*....**
.***....*.*
..***.*....
.*.*.....**
......*.*..
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 4
..**
..**
....
....
```

### 输出

```
0
```

# 题解

## 作者：ygsldr (赞：2)

没好好读题被坑了QAQ

题中说“A part of them is painted black according to the fractal pattern.”，也就是一部分会被涂成黑色（嗯就是我顺口翻的“任意的涂色”）

所以不止图中那一种情况，全白到全黑都是可以的

做题的时候看样例一以为可以旋转emmm...，但题中没有任何有关旋转的说法，因为本身不是旋转而是本身就可以得到，如下图：

![](https://cdn.luogu.com.cn/upload/pic/55631.png)

那个4$\times$4就是图中蓝色的

好嘛，没被坑到的人肯定说我在废话了

那谈谈接下来怎么做

假设我们用4个布尔变量来记录最初的分形 b[2][2]

再假设我们用一个二维字符数组来记录了第i次的分形图形，那么，我们考虑把第i+1次的图形分为左上、左下、右上、右下，4块，分两种情况

>这个位置最初为黑

>这个位置最初为白

那么，假如这个位置最初为黑，它依旧为黑，假如为白，它应该填充第i次的分形图形

还是看图吧QAQ

![](https://cdn.luogu.com.cn/upload/pic/55638.png)

那我们可以开始构思，我们首先枚举初始的状态，然后我们开一个数组记录当前操作次数下哪些符合分形图形，递推就好了

代码复杂度O($2^4\times log_2{min(n,m)} \times n \times m \times 4$)

//CF神机又是4s题能过的

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char mp[512][512];
int s[512][512];
bool dp[12][512][512];
int n, m;
int sum(int l2, int r2, int l1, int r1){
    return s[l2][r2] - s[l1-1][r2] - s[l2][r1-1] + s[l1-1][r1-1];
}//前缀和
int dx[4]={0, 0, 1, 1}, dy[4] = {0, 1, 0, 1};
int CountOne(int T){
    memset(dp, 0, sizeof(dp));
    memset(s, 0, sizeof(s));
    for(int i(1); i <= n; ++i){
        for(int j(1); j <= m; ++j){
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + mp[i][j];
            dp[0][i][j] = !mp[i][j];	
        }
    }//每次操作初始化
    for(int i(1); i <= 10; ++i){
        for(int j(1); j <= n - (1<<(i-1)); ++j){
            for(int k(1); k <= m - (1<<i-1); ++k){
                bool OK = true;
                for(int t(0); t < 4 && OK; ++t){
                    if(T&(1<<t)){
                        OK &= sum(j+(1<<i-1)-1+dx[t]*(1<<i-1), k+(1<<i-1)*dy[t], j+dx[t]*(1<<i-1), k+1+(dy[t]-1)*(1<<i-1)) == (1 << 2*(i-1));
                    }// Sum = Black
                    else{
                        OK &= dp[i-1][j+(1<<i-1)*dx[t]][k+(1<<i-1)*dy[t]];
                    }// dp Ok
                }//枚举状态每一位
                if(OK) dp[i][j][k+(1<<i-1)] = true;//往下递推
            }
        }
    }
    int ans(0);
    for(int i(2); i <= 10; ++i){
        for(int j(1); j <= n; ++j){
            for(int k(1); k <= m; ++k) ans += dp[i][j][k];
        }
    }	
    return ans;
}
int main(){
    scanf("%d%d", &n, &m);
    for(int i(1); i <= n; ++i) scanf("%s", mp[i] + 1);
    for(int i(1); i <= n; ++i){
        for(int j(1); j <= m; ++j){
            mp[i][j] = (mp[i][j] == '*');
        }
    }
    long long ans(0);
    for(int i(0); i <= 15; ++i)
        ans += CountOne(i);//状压枚举状态
    printf("%lld\n", ans);
    return 0;
}
```
dp[i][j][k]表示第i(i-1?)次操作以(j,k)为右上角是不是分形图形

我的代码是以右上角为记录的点（因为直接从刚开始错的改过来），所以可能会引起不适，建议以记录左上角所在合不合法QwQ

---

## 作者：02Ljh (赞：1)

码量题。~~谴责CF出题人卡哈希~~

### 前置知识：二维哈希 [板子](https://www.luogu.com.cn/problem/UVA11019)

对于一个矩阵，首先对于每行哈希，然后对每行的哈希值取不同的 base 哈希。而从大矩阵里提出一个小矩阵可以 $O(1)$ 做，这里直接给公式，证明看板子题题解。

$i$ 处哈希 $a_{i,j}$，行哈希基数 $b1$，列 $b2$，要求右端点 $n,m$，左端点 $x,y$ 的小矩阵，公式为：

$a_{n,m}-a_{n,y-1}\times b1^{m-y+1}-a_{x-1,m}\times b2^{n-x+1}+a_{x-1,y-1}\times b1^{m-y+1}\times b2^{n-x+1}$

首先考虑最后合法正方形数是有限的，每种合法正方形一定是 $2$ 的倍数长度，一共有 $(2^4\times nm \log\min(n,m))$ 种

然后对于每种初始情况扩展出所有边长 $\leq \min(n,m)$ 的情况，对其进行哈希，然后存到 map 里。

然后把大矩阵哈希一下，$nm\log\min(n,m)$ 枚举起点和长度，然后判断每个小正方形的哈希值是否在 map 里出现过，统计答案。

**要写双哈希，注意随时取模**

[AC](https://codeforces.com/contest/228/submission/243887246)

---

