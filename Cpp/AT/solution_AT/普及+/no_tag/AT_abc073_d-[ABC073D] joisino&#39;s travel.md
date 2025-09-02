# [ABC073D] joisino&#39;s travel

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc073/tasks/abc073_d

Atcoder国には $ N $ 個の町があり、$ M $ 本の双方向に移動可能な道で結ばれています。

また、 $ i $ 本目の道は町 $ A_i $ と町 $ B_i $ の間を距離 $ C_i $ で結んでいます。

joisinoお姉ちゃんは、この国の $ R $ 個の町 $ r_1,r_2..r_R $ を訪れることとなりました。

最初に訪れる町までの移動と、最後に訪れる町からの移動は空路で行うが、それ以外は道を使わなければなりません。

町を訪れる順番を、道での移動距離が最小となるように決めた時の移動距離を答えてください。

## 说明/提示

### 制約

- $ 2≦N≦200 $
- $ 1≦M≦N×(N-1)/2 $
- $ 2≦R≦min(8,N) $ ( $ min(8,N) $ は $ 8 $ と $ N $ のうち小さい方)
- $ r_i≠r_j\ (i≠j) $
- $ 1≦A_i,B_i≦N\ ,\ A_i≠B_i $
- $ (A_i,B_i)≠(A_j,B_j),(A_i,B_i)≠(B_j,A_j)\ (i≠j) $
- $ 1≦C_i≦100000 $
- すべての町の間は道のみで移動することができる。
- 入力は全て整数である。

### Sample Explanation 1

例えば、町 $ 1 $ ,町 $ 2 $ ,町 $ 3 $ の順番で訪れると、移動距離が $ 2 $ となり、最小となります。

### Sample Explanation 2

町 $ 1 $ を訪れたあとに町 $ 3 $ を訪れても、町 $ 3 $ を訪れたあとに町 $ 1 $ を訪れても、町 $ 1 $ と町 $ 3 $ の間の最短距離は $ 4 $ であるため、どの順番を選んだとしても答えは $ 4 $ となります。

## 样例 #1

### 输入

```
3 3 3
1 2 3
1 2 1
2 3 1
3 1 4```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3 2
1 3
2 3 2
1 3 6
1 2 2```

### 输出

```
4```

## 样例 #3

### 输入

```
4 6 3
2 3 4
1 2 4
2 3 3
4 3 1
1 4 1
4 2 2
3 1 6```

### 输出

```
3```

# 题解

## 作者：fly20040720 (赞：1)

题意：给一张无向图，给定一些点，求走过全部给定的点的最小代价。

n<=8，直接全排列然后比大小就行了，floyd n^3的复杂度在n!面前显得微不足道。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int n,m,R,dist[300][300],r[10];

int main()
{
    memset(dist,0x3f,sizeof dist);
    int Min,ans;
    cin>>n>>m>>R;
    for(int i=0;i<R;i++)
        cin>>r[i];
    for(int i=0;i<m;i++)
    {
        int x,y,z;
        cin>>x>>y>>z;
        dist[x][y]=dist[y][x]=z;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(dist[i][k]+dist[k][j]<dist[i][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
    sort(r,r+R);
    ans=0x3f3f3f3f;
    do
    {
        Min=0;
        for(int i=0;i<R-1;i++)
            Min+=dist[r[i]][r[i+1]];
        ans=min(Min,ans);
    }while(next_permutation(r,r+R));
    cout<<ans;
}
```

---

