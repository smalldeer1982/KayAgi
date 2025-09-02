# 题目信息

# [ABC173D] Chat in a Circle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc173/tasks/abc173_d

あなたはオンラインゲーム「ATChat」のチュートリアルを終え、その場に居合わせたプレイヤー $ N $ 人で早速とある場所を訪ねることにしました。この $ N $ 人には $ 1 $ から $ N $ の番号が振られており、人 $ i\ (1\ \leq\ i\ \leq\ N) $ の **フレンドリーさ** は $ A_i $ です。

訪ねる際、$ N $ 人は好きな順番で $ 1 $ 人ずつ到着します。あなたたちは迷子にならないために、既に到着した人たちで環状に並び、新たに到着した人は好きな位置に割り込んで加わるというルールを決めました。

最初に到着した人以外の各人は、割り込んだ位置から到着した時点で「時計回りで最も近い人」と「反時計回りで最も近い人」のフレンドリーさのうち小さい方に等しい **心地よさ** を感じます。最初に到着した人の心地よさは $ 0 $ です。

$ N $ 人が到着する順番や割り込む位置を適切に決めたとき、$ N $ 人の心地よさの合計の最大値はいくらになるでしょう？

## 说明/提示

### 制約

- 入力はすべて整数
- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

人 $ 4,\ 2,\ 1,\ 3 $ がこの順に到着し、図のように輪に割り込むことで、心地よさの合計は $ 7 $ になります。 !\[図\](https://img.atcoder.jp/ghi/766a260a0019ea93e86e0588cc4db868.png) 心地よさの合計を $ 7 $ より大きくすることはできないので、$ 7 $ が答えになります。

## 样例 #1

### 输入

```
4

2 2 1 3```

### 输出

```
7```

## 样例 #2

### 输入

```
7

1 1 1 1 1 1 1```

### 输出

```
6```

# AI分析结果



# [ABC173D] Chat in a Circle

## 题目描述

你结束了在线游戏“ATChat”的教程，与在场的N名玩家决定立即访问某个地方。这N人编号为1到N，第i人的友好度为A_i。

访问时，N人以任意顺序依次到达。为了不走散，已到达的人围成环状排列，新到达的人可插入任意位置。

除第一个到达的人外，每个人插入时，其“顺时针最近的人”与“逆时针最近的人”中较小的友好度即为该人的舒适度。第一个人的舒适度为0。

求通过合理安排到达顺序与插入位置，N人舒适度总和的最大值。

## 算法分类
贪心

## 题目分析与题解对比

各题解均采用贪心策略，核心思路为将数组降序排列后，用优先队列维护当前可用最大值。每次取出最大值累加后，将当前元素插入队列两次，确保后续能重复利用次大值。难点在于理解每个元素（除最大外）可贡献两次，通过优先队列动态维护可用间隙的最大值。

### 精选题解

#### 1. DengDuck（4星）
**关键亮点**：代码简洁，正确使用升序排序与优先队列，通过倒序处理元素确保逻辑正确。
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
priority_queue<LL,vector<LL>,less<LL> >p; 
LL n,a[N],ans;
int main() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]; 
    sort(a+1,a+n+1); // 升序排序
    p.push(a[n]);    // 最大值入队
    for(int i=n-1;i>=1;i--) {
        ans+=p.top();
        p.pop();
        p.push(a[i]); // 插入两次当前元素
        p.push(a[i]);
    }
    printf("%lld",ans);
}
```

#### 2. Lyw_and_Segment_Tree（4星）
**关键亮点**：逻辑清晰，代码结构紧凑，直接通过优先队列维护当前最大值。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[200010],ans=0;
int main(){
    priority_queue<ll> q;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);      // 升序排序
    q.push(a[n]);         // 最大值入队
    for(int i=n-1;i>=1;i--){
        ans+=q.top();
        q.pop();
        q.push(a[i]);     // 插入两次当前元素
        q.push(a[i]);
    }
    cout<<ans<<endl;
}
```

#### 3. huhexuan（4星）
**关键亮点**：降序排序处理，直观体现贪心选择最大值的思路。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005];
bool cmp(int a,int b){return a>b;}
priority_queue<int>q;
signed main() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1,cmp); // 降序排序
    q.push(a[1]);         // 最大值入队
    int ans=0;
    for(int i=2;i<=n;i++) {
        ans+=q.top(); 
        q.pop();
        q.push(a[i]);     // 插入两次当前元素
        q.push(a[i]);
    }
    cout<<ans;
}
```

## 最优思路总结
将数组排序后，利用优先队列动态维护当前可用的最大间隙值。每次插入新元素时，取出最大值累加，并将该元素插入两次以生成新间隙。时间复杂度O(N log N)，空间复杂度O(N)。

## 相似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
2. [P6033 合并果子（加强版）](https://www.luogu.com.cn/problem/P6033)  
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

---
处理用时：191.64秒