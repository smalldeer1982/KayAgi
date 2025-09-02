# 天下一美術館

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2015-quala/tasks/tenka1_2015_qualA_c

天下一美術館のセト館長は、新コーナーの白黒のモザイクアートコーナーのレイアウトを決めることになりました。

見栄えを良くするためには、隣同士に並ぶ各アートは似ているものにしたいと考えています。

そこでセト館長の２つのアート同士の相違度を定義することにしました。

モザイクアートは白か黒に塗られた $ M\ \times\ N $ のマス目です。

一方のモザイクアートを他方のモザイクアートに変換する操作を考え、その操作に必要な最小のコストを相違度とします。

操作は、黒マスから白マスへの変換、白マスから黒マスへの変換、上下左右の4方向に隣り合ったマス目の交換の3種類あり、どれもコストが$ 1 $かかります。

セト館長のために与えられた2つのモザイクアートの相違度を求めるプログラムを作成してください。

## 说明/提示

### 配点

この問題には部分点が設定されている。

- $ N,\ M\ \leq{}\ 10 $を満たすテストケース全てに正解した場合は、$ 40 $ 点が与えられる。
- 全てのテストケースに正解した場合は、上記とは別に $ 50 $ 点が与えられる。

### Sample Explanation 1

下の行に対してマス目の交換を行うことにより、コスト1で変換が可能です。

### Sample Explanation 2

白から黒への変換を1回、マス目の交換を3回行うことでコスト4で変換が可能です。

### Sample Explanation 3

白から黒への変換を2回、マス目の交換を1回行うことでコスト3で変換が可能です。

## 样例 #1

### 输入

```
2 2
0 0
1 0
0 0
0 1```

### 输出

```
1```

## 样例 #2

### 输入

```
3 3
0 0 0
0 1 0
1 0 1
0 1 0
1 0 1
0 1 0```

### 输出

```
4```

## 样例 #3

### 输入

```
3 4
0 0 0 0
1 1 0 0
0 0 0 0
1 1 1 0
0 1 0 0
0 0 0 0```

### 输出

```
3```

# 题解

## 作者：缪凌锴_Mathew (赞：3)

### 思路

先假定全部都是用修改操作。

交换操作更优当且仅当两个相邻的点从 `01` 变为 `10`，直接交换比改两次更优。

于是我们把相邻的，交换更优的，要操作的点建边，跑二分图最大匹配。

![](https://s3.bmp.ovh/imgs/2023/11/01/6a13dddff9af9cc2.png)

![](https://s3.bmp.ovh/imgs/2023/11/01/ed118147c7d3c2b0.png)

我用的是 [匈牙利算法(P3386)](https://www.luogu.com.cn/problem/P3386)，建出来的图点数和边数是 $O(nm)$ 级别的，时间复杂度 $O(n^2 m^2)$，空间复杂度 $O(nm)$。

### 实现

```cpp
#include<map>
#include<set>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<string>
#include<bitset>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=70+10;
const int MAXM=5e3+10;
const int INF=0x3f3f3f3f;
const long long LINF=0x3f3f3f3f3f3f3f3f;
int n,m,cnt=0,ans=0;
int a[MAXN][MAXN],b[MAXN][MAXN];
int X[MAXM],Y[MAXM];
int idx[MAXN][MAXN];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
vector <int> gr[MAXM];
void add_edge(int x,int y){
    gr[x].push_back(y);
}
bool vis[MAXM];
int match[MAXM];
bool dfs(int x){//匈牙利算法
    vis[x]=true;
    for(int i=0;i<gr[x].size();i++)
    {
        int to=gr[x][i];
        if((!match[to])||(!vis[match[to]]&&dfs(match[to]))){
            match[to]=x;
            return true;
        }
    }
    return false;
}
signed main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&b[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(a[i][j]!=b[i][j]){//假定直接修改
                cnt++;
                idx[i][j]=cnt;
                X[cnt]=i;
                Y[cnt]=j;
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(idx[i][j]&&a[i][j]){
                for(int d=0;d<4;d++)
                {
                    int tox=i+dx[d],toy=j+dy[d];
                    if(idx[tox][toy]&&(!a[tox][toy])){//相邻的异色修改建边
                        add_edge(idx[i][j],idx[tox][toy]);
                    }
                }
            }
        }
    }
    for(int i=1;i<=cnt;i++)
    {
        if(a[X[i]][Y[i]]){
            memset(vis,false,sizeof(vis));
            ans+=dfs(i);
        }
    }
    printf("%d\n",cnt-ans);
    return 0;
}
```

---

## 作者：AC_love (赞：0)

注意到：当且仅当相邻两个都不满足条件的数交换后都满足条件时才会进行交换操作，否则一定不优。

找到所有可以交换的点对，我们一定希望交换的次数尽可能多。

考虑最大流。先将图黑白染色，能匹配的点对从黑点向白点连边，跑一遍最大流，这就是最多交换次数。

交换两个点比直接让两个点分别 reverse 颜色要优一步，所以答案就是所有点都 reverse 时的答案减去最大流。

[code](https://atcoder.jp/contests/tenka1-2015-quala/submissions/59072389)

---

