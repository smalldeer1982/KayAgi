# 题目信息

# ロシアの旗 (Russian Flag)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2016yo/tasks/joi2016yo_c

K 理事長はロシアで開催される IOI 2016 に合わせて旗を作ることにした．K 理事長はまず倉庫から古い旗を取り出してきた．この旗は $ N $ 行 $ M $ 列のマス目に分けられていて，それぞれのマスには白・青・赤のいずれかの色が塗られている．

K 理事長はこの旗のいくつかのマスを塗り替えてロシアの旗にしようとしている．ただし，この問題でいうロシアの旗とは以下のようなものである．

- 上から何行か（$ 1 $ 行以上）のマスが全て白で塗られている．
- 続く何行か（$ 1 $ 行以上）のマスが全て青で塗られている．
- それ以外の行（$ 1 $ 行以上）のマスが全て赤で塗られている．

K 理事長が古い旗をロシアの旗にするために塗り替える必要のあるマスの個数の最小値を求めよ．

- - - - - -

## 说明/提示

### Sample Explanation 1

入出力例 $ 1 $ において，古い旗には下図のように色が塗られている． !\[2016-yo-t3-fig01.png\](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig01.png) 下図において，`X` の書かれた $ 11 $ 個のマスを塗り替える． !\[2016-yo-t3-fig02.png\](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig02.png) これにより下図のようなロシアの旗にすることができる． !\[2016-yo-t3-fig03.png\](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig03.png) $ 11 $ 個未満のマスを塗り替えることではロシアの旗にすることはできないため，$ 11 $ を出力する． - - - - - -

### Sample Explanation 2

入出力例 $ 2 $ においては，古い旗には下図のように色が塗られている． !\[2016-yo-t3-fig04.png\](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig04.png)

## 样例 #1

### 输入

```
4 5
WRWRW
BWRWB
WRWRW
RWBWR```

### 输出

```
11```

## 样例 #2

### 输入

```
6 14
WWWWWWWWWWWWWW
WBBBWWRRWWBBBW
WWBWWRRRRWWBWW
BWBWWRRRRWWBWW
WBBWWWRRWWBBBW
WWWWWWWWWWWWWW```

### 输出

```
44```

# AI分析结果

### 题目翻译
# 俄罗斯国旗 (Russian Flag)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2016yo/tasks/joi2016yo_c

K 理事长为了配合在俄罗斯举办的 IOI 2016，决定制作一面旗帜。K 理事长首先从仓库里取出了一面旧旗帜。这面旗帜被分成了 $N$ 行 $M$ 列的格子，每个格子都涂有白色、蓝色、红色中的一种颜色。

K 理事长打算将这面旗帜的一些格子重新涂色，使其变成俄罗斯国旗。在这个问题中，俄罗斯国旗的定义如下：
- 从上往下若干行（至少 1 行）的格子全部涂成白色。
- 接着的若干行（至少 1 行）的格子全部涂成蓝色。
- 剩下的行（至少 1 行）的格子全部涂成红色。

请计算 K 理事长将旧旗帜变成俄罗斯国旗所需重新涂色的格子的最少数量。

### 说明/提示

#### 样例解释 1
在样例输入输出 1 中，旧旗帜的颜色分布如下图所示。![2016-yo-t3-fig01.png](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig01.png) 在下图中，标记为 `X` 的 11 个格子需要重新涂色。![2016-yo-t3-fig02.png](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig02.png) 这样就可以将旗帜变成如下图所示的俄罗斯国旗。![2016-yo-t3-fig03.png](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig03.png) 由于少于 11 个格子无法将旗帜变成俄罗斯国旗，因此输出 11。

#### 样例解释 2
在样例输入输出 2 中，旧旗帜的颜色分布如下图所示。![2016-yo-t3-fig04.png](https://img.atcoder.jp/joi2016yo/2016-yo-t3-fig04.png)

## 样例 #1

### 输入
```
4 5
WRWRW
BWRWB
WRWRW
RWBWR
```

### 输出
```
11
```

## 样例 #2

### 输入
```
6 14
WWWWWWWWWWWWWW
WBBBWWRRWWBBBW
WWBWWRRRRWWBWW
BWBWWRRRRWWBWW
WBBWWWRRWWBBBW
WWWWWWWWWWWWWW
```

### 输出
```
44
```

### 综合分析与结论
这些题解的核心思路都是基于数据范围较小，采用暴力枚举的方法来解决问题。具体做法是通过两重循环枚举白色与蓝色、蓝色与红色的分界行，然后计算在这种划分下需要重新涂色的格子数量，最后取最小值。

部分题解使用了计数数组（桶）来记录每行中三种颜色的格子数量，这样可以减少后续计算的复杂度。

### 所选题解
- **作者：huyangmu (赞：4)，4星**
  - 关键亮点：思路清晰，代码简洁，使用计数数组优化计算。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=55; 
int n,m,cnt1[NR],cnt2[NR],cnt3[NR],ans=0x3f3f3f3f;
char c[NR][NR];
int main (){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;++i){
        for (int j=1;j<=m;++j){
            cin>>c[i][j];
            if (c[i][j]=='W') ++cnt1[i];
            else if (c[i][j]=='B') ++cnt2[i];
            else ++cnt3[i];
        }
    }
    for (int x=1;x<n-1;++x){
        for (int y=x+1;y<n;++y){
            int tmp=0,sum=0;
            for (int i=1;i<=x;++i) tmp+=cnt1[i];
            sum+=x*m-tmp;
            tmp=0;
            for (int i=x+1;i<=y;++i) tmp+=cnt2[i];
            sum+=(y-x)*m-tmp;
            tmp=0;
            for (int i=y+1;i<=n;++i) tmp+=cnt3[i];
            sum+=(n-y)*m-tmp;
            ans=min(ans,sum);
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```
核心实现思想：先通过两层循环输入旗帜信息，并统计每行中三种颜色的格子数量。然后通过两层循环枚举白色和蓝色的分界行 $x$ 以及蓝色和红色的分界行 $y$，对于每一种划分，计算需要重新涂色的格子数量，最后取最小值。

- **作者：Sammy_prime (赞：3)，4星**
  - 关键亮点：思路直接，代码简单易懂，直接枚举分界行并统计需要重新涂色的格子数量。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,minn=1<<30; char a[55][55];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) cin>>a[i][j];
    for(int i=1;i<=n-2;i++)
        for(int j=i+1;j<=n-1;j++){
            int cnt=0;
            for(int k=1;k<=i;k++)
                for(int l=1;l<=m;l++) if(a[k][l]!='W') cnt++;
            for(int k=i+1;k<=j;k++)
                for(int l=1;l<=m;l++) if(a[k][l]!='B') cnt++;
            for(int k=j+1;k<=n;k++)
                for(int l=1;l<=m;l++) if(a[k][l]!='R') cnt++;
            minn=min(minn,cnt);
        }
    printf("%d\n",minn);
    return 0;
}
```
核心实现思想：通过两层循环输入旗帜信息，然后通过两层循环枚举白色和蓝色的分界行 $i$ 以及蓝色和红色的分界行 $j$，对于每一种划分，使用两层循环遍历每个格子，统计需要重新涂色的格子数量，最后取最小值。

- **作者：xhhhh36 (赞：3)，4星**
  - 关键亮点：使用计数数组，逻辑清晰，代码规范。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,r[55],w[55],b[55];
char a[55][55];
signed main()
{
    cin>>n>>m;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            if (a[i][j]=='W') w[i]++;
            else if (a[i][j]=='R') r[i]++;
            else b[i]++;
        }
    }
    int ans,mn=INT_MAX;
    for (int x=1;x<n-1;x++)
    {
        for (int y=x+1;y<n;y++)
        {
            ans=0;
            for (int i=1;i<=x;i++)
            {
                ans+=m-w[i];
            }
            for (int i=x+1;i<=y;i++)
            {
                ans+=m-b[i];
            }
            for (int i=y+1;i<=n;i++)
            {
                ans+=m-r[i];
            }
            mn=min(mn,ans);
        }
    }
    cout<<mn<<endl;
    return 0;
}
```
核心实现思想：先通过两层循环输入旗帜信息，并统计每行中三种颜色的格子数量。然后通过两层循环枚举白色和蓝色的分界行 $x$ 以及蓝色和红色的分界行 $y$，对于每一种划分，计算需要重新涂色的格子数量，最后取最小值。

### 最优关键思路或技巧
- **暴力枚举**：由于数据范围较小，直接枚举所有可能的分界行，计算每种情况下需要重新涂色的格子数量，取最小值。
- **计数数组（桶）**：使用计数数组记录每行中三种颜色的格子数量，避免在后续计算中重复遍历每行的格子，减少时间复杂度。

### 拓展思路
同类型题目通常会有数据范围较小，且可以通过枚举所有可能情况来求解的特点。类似的算法套路包括枚举排列组合、枚举区间等，然后根据题目要求计算相应的结果并取最优值。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合来求解问题。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：可以通过枚举区间来解决。
- [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)：需要枚举各种排列情况并计算结果。

### 个人心得摘录与总结
- **hexuchen**：提到要注意输出答案末尾要加换行，这是一个容易忽略的细节，在竞赛中可能会导致错误，提醒我们要仔细检查输出格式。

---
处理用时：54.98秒