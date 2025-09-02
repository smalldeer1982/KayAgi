# 题目信息

# [ABC160E] Red and Green Apples

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc160/tasks/abc160_e

あなたは、$ X $ 個の赤色のリンゴと $ Y $ 個の緑色のリンゴを食べようとしています。  
 あなたは $ A $ 個の赤色のリンゴを持っており、美味しさはそれぞれ $ p_1,p_2,\ \dots\ ,p_A $ です。  
 あなたは $ B $ 個の緑色のリンゴを持っており、美味しさはそれぞれ $ q_1,q_2,\ \dots\ ,q_B $ です。  
 あなたは $ C $ 個の無色のリンゴを持っており、美味しさはそれぞれ $ r_1,r_2,\ \dots\ ,r_C $ です。  
 無色のリンゴは食べる前に着色することで、赤色のリンゴもしくは緑色のリンゴと見なすことができます。  
 以上のリンゴの中から、できるだけ美味しさの総和が大きくなるように食べるリンゴを選びます。  
 $ 0 $ 個以上の無色のリンゴに適切に着色したとき、食べる $ X+Y $ 個のリンゴの美味しさの総和が最大でいくつになるか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ X\ \leq\ A\ \leq\ 10^5 $
- $ 1\ \leq\ Y\ \leq\ B\ \leq\ 10^5 $
- $ 1\ \leq\ C\ \leq\ 10^5 $
- $ 1\ \leq\ p_i\ \leq\ 10^9 $
- $ 1\ \leq\ q_i\ \leq\ 10^9 $
- $ 1\ \leq\ r_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

以下のようにすることで、食べるリンゴの美味しさの総和を最大にすることができます。 - $ 2 $ 番目の赤色のリンゴを食べる。 - $ 1 $ 番目の緑色のリンゴを食べる。 - $ 1 $ 番目の無色のリンゴを緑色に着色し、食べる。

## 样例 #1

### 输入

```
1 2 2 2 1

2 4

5 1

3```

### 输出

```
12```

## 样例 #2

### 输入

```
2 2 2 2 2

8 6

9 1

2 1```

### 输出

```
25```

## 样例 #3

### 输入

```
2 2 4 4 4

11 12 13 14

21 22 23 24

1 2 3 4```

### 输出

```
74```

# AI分析结果

### 题目内容重写

**题目描述**

你将要吃 $X$ 个红苹果和 $Y$ 个绿苹果。  
你有 $A$ 个红苹果，它们的美味值分别是 $p_1, p_2, \dots, p_A$。  
你有 $B$ 个绿苹果，它们的美味值分别是 $q_1, q_2, \dots, q_B$。  
你有 $C$ 个无色苹果，它们的美味值分别是 $r_1, r_2, \dots, r_C$。  
在吃无色苹果之前，你可以将它涂成红色或绿色，然后这个苹果会按照红色或绿色苹果计数。  
你要从上面的苹果中选择要吃的，使得吃过的美味值尽可能大。  
找出将零个或更多无色苹果进行最佳着色时所能达到的吃掉苹果美味的最大可能总和。

### 算法分类
贪心

### 综合分析与结论

这道题的核心思想是通过贪心策略选择美味值最大的苹果，同时满足红苹果和绿苹果的数量限制。各题解的主要思路都是通过排序和选择前 $X$ 个红苹果和前 $Y$ 个绿苹果，然后将无色苹果与已选苹果进行比较，替换掉美味值较小的苹果，最终得到最大美味值总和。

### 所选高星题解

#### 题解1：ix35 (5星)
**关键亮点**：
- 简洁明了，直接通过排序和选择前 $X$ 个红苹果和前 $Y$ 个绿苹果，然后将所有苹果合并排序，选择前 $X+Y$ 个苹果。
- 代码实现高效，逻辑清晰。

**核心代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=100010;
int x,y,a,b,c,t,tot;
ll p[MAXN*3],q[MAXN],r[MAXN],ans;
int main () {
    scanf("%d%d%d%d%d",&x,&y,&a,&b,&c);
    for (int i=1;i<=a;i++) {
        scanf("%d",&q[i]);
    }
    sort(q+1,q+a+1);
    for (int i=a;i>=a-x+1;i--) {p[++tot]=q[i];}
    for (int i=1;i<=b;i++) {
        scanf("%d",&r[i]);
    }
    sort(r+1,r+b+1);
    for (int i=b;i>=b-y+1;i--) {p[++tot]=r[i];} 
    for (int i=1;i<=c;i++) {
        scanf("%d",&t);
        p[++tot]=t;
    }
    sort(p+1,p+tot+1);
    for (int i=tot;i>=tot-x-y+1;i--) {
        ans+=p[i];
    }
    printf("%lld\n",ans);
    return 0;
}
```

#### 题解2：oimaster (4星)
**关键亮点**：
- 使用优先队列（大根堆）来维护所有苹果的美味值，逐步选择最大美味值的苹果。
- 通过记录苹果的颜色和剩余数量，确保选择的苹果满足红苹果和绿苹果的数量限制。

**核心代码**：
```cpp
#include<iostream>
#include<queue>
using namespace std;
#define int long long
signed main(){
    int x,y,a,b,c;
    cin>>x>>y>>a>>b>>c;
    priority_queue<pair<int,int> >h;
    while(a--){
        int w;
        cin>>w;
        h.push(make_pair(w,1));
    }
    while(b--){
        int w;
        cin>>w;
        h.push(make_pair(w,2));
    }
    while(c--){
        int w;
        cin>>w;
        h.push(make_pair(w,3));
    }
    int z=x+y;
    int ans=0;
    while(z){
        pair<int,int>f=h.top();
        h.pop();
        if(f.second==3){
            ans+=f.first;
            --z;
        }
        else if(f.second==1&&x){
            ans+=f.first;
            --x;
            --z;
        }
        else if(f.second==2&&y){
            ans+=f.first;
            --y;
            --z;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

#### 题解3：Limury (4星)
**关键亮点**：
- 通过排序和选择前 $X$ 个红苹果和前 $Y$ 个绿苹果，然后将无色苹果与已选苹果进行比较，替换掉美味值较小的苹果。
- 代码实现清晰，逻辑严谨。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1000005;
ll x,y,a,b,c,cnti=1,cnt;
ll lans[maxn],ai[maxn],bi[maxn],ci[maxn];
bool cmp(ll u,ll v){
    return u>v;
}
int main(){
    scanf("%lld%lld%lld%lld%lld",&x,&y,&a,&b,&c);
    for(int i=1;i<=a;i++){
        scanf("%lld",&ai[i]);
    }
    for(int i=1;i<=b;i++){
        scanf("%lld",&bi[i]);
    }
    for (int i=1;i<=c;i++){
        scanf("%lld",&ci[i]);
    }
    sort(ai+1,ai+a+1,cmp);
    sort(bi+1,bi+b+1,cmp);
    sort(ci+1,ci+c+1,cmp);
    for(int i=1;i<=x;i++){
        lans[++cnt]=ai[i];
    }
    for(int i=1;i<=y;i++){
        lans[++cnt]=bi[i];
    }
    sort(lans+1,lans+x+y+1,cmp);
    for(int i=x+y;i>=1;i--){
        if(lans[i]<ci[cnti]){
            lans[i]=ci[cnti];
            cnti++;
        }
        if(cnti>c){
            break;
        }
    }
    ll ans=0;
    for(int i=1;i<=cnt;i++){
        ans+=lans[i];
    }
    printf("%lld\n",ans);
    return 0;
}
```

### 最优关键思路与技巧
1. **排序与选择**：通过排序选择前 $X$ 个红苹果和前 $Y$ 个绿苹果，然后将无色苹果与已选苹果进行比较，替换掉美味值较小的苹果。
2. **优先队列**：使用优先队列（大根堆）来维护所有苹果的美味值，逐步选择最大美味值的苹果，确保满足红苹果和绿苹果的数量限制。

### 可拓展之处
类似的问题可以通过贪心策略和排序来解决，例如在资源分配、任务调度等场景中，选择最优的组合以达到最大效益。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：43.94秒