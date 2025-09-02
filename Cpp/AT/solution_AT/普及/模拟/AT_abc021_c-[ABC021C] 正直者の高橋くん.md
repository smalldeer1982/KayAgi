# [ABC021C] 正直者の高橋くん

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc021/tasks/abc021_c

あなたと高橋君は、AtCoder 王国に住んでいます。AtCoder 王国には、$ N $ 個の町と、町どうしを結ぶ $ M $ 本の道路が存在し、それらは双方向に移動可能です。 $ N $ 個の町はそれぞれ 町 $ 1 $,町 $ 2 $,…,町 $ N $ と呼ばれています。 また、$ M $ 個の道路はそれぞれ 道路 $ 1 $,道路 $ 2 $,…,道路 $ M $ と呼ばれています。

高橋君はあなたの家に遊びに行くことにしました。そして、高橋君は町 $ a $ から出発して、AtCoder 王国のいくつかの町（$ 0 $ 個でも良い）を経由して町 $ b $ にあるあなたの家に到着しました。

高橋君は最短経路を辿ってきたと主張しています。 高橋君は正直なので、絶対に嘘をつきません。

そこで、あなたは町 $ a $ から町 $ b $ への最短経路が何通りあるかを数えることにしました。答えは非常に大きくなる可能性があるので、実際の答えを $ 1,000,000,007(=10^9+7) $ で割った余りを出力してください。

町 $ a $ から町 $ b $ への最短経路とは、町 $ a $ から町 $ b $ への移動経路において道路を通る回数が最小となるような経路のことを言います。

## 说明/提示

### Sample Explanation 1

この入力例に対する図は以下の通りで、最短経路として次の $ 4 $ 通りが考えられます。 - $ 1→2→4→5→7 $ - $ 1→3→4→5→7 $ - $ 1→2→4→6→7 $ - $ 1→3→4→6→7 $ !\[\](http://abc021.contest.atcoder.jp/img/abc/021/enJQfEfKt-baQEUDjCrVFLSw/C\_sample1.png)

### Sample Explanation 2

この入力例に対する図は以下の通りです。 !\[\](http://abc021.contest.atcoder.jp/img/abc/021/enJQfEfKt-baQEUDjCrVFLSw/C\_sample2.png)

## 样例 #1

### 输入

```
7
1 7
8
1 2
1 3
4 2
4 3
4 5
4 6
7 5
7 6```

### 输出

```
4```

## 样例 #2

### 输入

```
7
1 7
9
1 2
1 3
4 2
4 3
4 5
4 6
7 5
7 6
4 7```

### 输出

```
2```

# 题解

## 作者：FFTotoro (赞：5)

广搜即可。

设数组 $c$ 为起点到每个点最短路的数量，$v$ 为是否经过某个点的标记。然后一圈一圈往外搜，如果搜到了就更新答案。

放代码：

```cpp
#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>
#define int long long // 本题坑点
using namespace std;
vector<int> g[1000001];
int a[1000001],c[1000001];
bool v[1000001];
signed main(){
    int n,s,b,m; cin>>n>>s>>b>>m;
    for(int i=1;i<=m;i++){
        int x,y; cin>>x>>y;
        g[x].push_back(y); g[y].push_back(x);
    } // 用 vector 存图
    queue<int> q; q.push(s); v[s]=c[s]=1;
    while(!q.empty()){ // 广搜过程
        int x=q.front(); q.pop();
        for(int i=0;i<g[x].size();i++){
            int h=g[x][i];
            if(!v[h]){v[h]=1; a[h]=a[x]+1; q.push(h);}
            if(a[h]==a[x]+1)c[h]=(c[h]+c[x])%1000000007; // 更新答案
        }
    }
    cout<<c[b]<<endl; // 输出答案
    return 0;
}

---

