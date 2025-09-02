# [ABC206F] Interval Game 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc206/tasks/abc206_f

$ T $ 個のテストケースについて、以下の問題を解いてください。

$ N $ 個の半開区間 $ [L_i,R_i) $ ($ 1\ \le\ i\ \le\ N $) があり、 Alice と Bob がこの区間を使って次のようなゲームをします。

- Alice から始めて、以下の操作を交互に行う。
  - $ N $ 個の区間の中から、既に選ばれているどの区間とも共有点をもたない区間を $ 1 $ つ選ぶ。

先に操作を行えなくなった方が負けで、もう片方のプレイヤーが勝ちます。  
 双方のプレイヤーが勝利に対して最善を尽くした場合、どちらが勝つことになりますか？

 半開区間とは？半開区間 $ [X,Y) $ とは、 $ X $ 以上 $ Y $ 未満のすべての実数からなる区間です。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ T\ \le\ 20 $
- $ 1\ \le\ N\ \le\ 100 $
- $ 1\ \le\ L_i\ <\ R_i\ \le\ 100 $

### Sample Explanation 1

この入力には、 $ 5 $ つのテストケースが含まれます。 $ 1 $ つ目のテストケースについて、例えば以下のようにゲームが進行します。 - Alice が区間 $ [12,53) $ を選択する。 - Bob が区間 $ [53,98) $ を選択する。 ゲームに用いる区間は半開区間なので、 $ [12,53),[53,98) $ は共有点を持たない。 - Alice はこれ以上操作を行えず、負ける。 Bob はゲームに勝つ。 このテストケースについて、上記の手順が必ずしも両者にとって最善とは限りませんが、両者が最善を尽くした場合勝利するのは Bob であることが示せます。 $ 2 $ つ目のテストケースのように、ひとつのテストケースに同じ区間が複数含まれる場合もあります。

## 样例 #1

### 输入

```
5
3
53 98
8 43
12 53
10
4 7
5 7
3 7
4 5
5 8
6 9
4 8
5 10
1 9
5 10
2
58 98
11 29
6
79 83
44 83
38 74
49 88
18 45
64 99
1
5 9```

### 输出

```
Bob
Alice
Bob
Alice
Alice```

# 题解

## 作者：DengDuck (赞：2)

这道题目是一道典型的公平博弈游戏，考虑求 SG 函数。

我们设 $SG_{i,j}$ 表示一个 $[i,j)$ 的左闭右开的区间的 SG 函数，我们找一个线段 $[l,r)$。

根据定理，我们用线段将区间分开后，所产生的 SG 函数值就是分开的两个区间的 SG 函数值的异或和。

对于每个区间的 SG 函数，统计求一个 mex 即可。 

因此我们求出所有区间的 SG 函数即可。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
struct node {
    LL l, r;
} a[105];
bool cmp(node x, node y) { return x.l < y.l; }
LL T, n, cnt, N, b[205], sg[105][105], vis[1005];
map<LL, LL> ma;
int main() {
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld", &n);
        ma.clear();
        memset(sg, 0, sizeof(sg));
        N = 0, cnt = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lld%lld", &a[i].l, &a[i].r);
            b[++cnt] = a[i].l;
            b[++cnt] = a[i].r;
        }
        sort(b + 1, b + cnt + 1);
        for (int i = 1; i <= cnt; i++) {
            if (b[i] != b[i - 1])
                ma[b[i]] = ++N;
        }
        for (int i = 1; i <= n; i++) {
            a[i].l = ma[a[i].l];
            a[i].r = ma[a[i].r];
        }
        sort(a + 1, a + n + 1, cmp);
        for (int L = 1; L <= N; L++) {
            for (int i = 1; i + L - 1 <= N; i++) {
                memset(vis, 0, sizeof(vis));
                int j = i + L - 1;
                for (int k = 1; k <= n; k++) {
                    if (j < a[k].l)
                        break;
                    if (i <= a[k].l && a[k].r <= j) {
                        vis[sg[i][a[k].l] ^ sg[a[k].r][j]] = 1;
                    }
                }
                for (int k = 0; k <= 100; k++) {
                    if (vis[k] == 0) {
                        sg[i][j] = k;
                        break;
                    }
                }
            }
        }
        if (sg[1][N] == 0) {
            puts("Bob");
        } else {
            puts("Alice");
        }
    }
}
```

---

## 作者：vicky2048_2 (赞：0)

### $\text{Somethig Useless}$

~~ORZ 楼上 Deng_Duck 老师，您吊打集训队。%%%~~

------------

## $\text{Analysis}$

SG 板题。

我们每从区间 $[l,r)$ 中取走一个区间 $[L_i,R_i)$，区间 $[l,r)$ 便会被分成三部分：

- 未被取走的区间 $[l,L_i)$ 和 $[R_i,r)$。

- 已被取走的区间 $[L_i,R_i)$。

于是我们不难想到用 $\operatorname{SG}_{i,j}$ 表示**左闭右开区间** $[i,j)$ 的 SG 值。

这个时候思路就很明确了，我们直接枚举每一段区间 $[L_i,R_i)$，用 $\operatorname{mex}$ 求每个 $\operatorname{SG}_{i,j}$：

$$\operatorname{SG}_{i,j}=\operatorname{mex}\{ \operatorname{SG}_{i,L_k}\text{ xor }\operatorname{SG}_{R_k,j}\}[1\leq k\leq N]$$

最后答案输出 $\operatorname{SG}_{1,\max(R_i)}$ 即可。

## $\text{Code}$

代码实现的时候要注意 $\operatorname{SG}_{i,j}$ 表示的是**左闭右开区间** $[i,j)$ 的 SG 值，**而不是左闭右闭区间**。

```cpp
#include<bits/stdc++.h>
#define N 105
using namespace std;
struct node{
    int l,r;
}no[N];
int sg[N][N];
bool xyl(node a,node b){
    if(a.l!=b.l) return a.l<b.l;
    return a.r<b.r;
}
bool vis[N];
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n,ma=-1;scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&no[i].l,&no[i].r),ma=max(ma,no[i].r);
        sort(no+1,no+1+n,xyl);
        for(int i=1;i<=100;i++)
            for(int j=1;j<=100;j++) sg[i][j]=0;
        for(int len=1;len<=ma;len++){
            for(int st=1;st+len<=ma;st++){
                int en=st+len;
                memset(vis,0,sizeof(vis));
                for(int k=1;k<=n&&no[k].l<ma;k++)
                    if(no[k].l>=st&&no[k].r<=en)
                        vis[sg[st][no[k].l]^sg[no[k].r][en]]=1;
                for(int k=0;;k++)
                    if(!vis[k]){ sg[st][en]=k; break;}
            }
        }
        printf("%s\n",sg[1][ma]?"Alice":"Bob");
    }
    return 0;
}
```


---

