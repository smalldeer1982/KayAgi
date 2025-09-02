# [蓝桥杯 2025 省 Python A/Java A/研究生组] 原料采购

## 题目描述

小蓝负责一家工厂的原料采购。

工厂有一辆运货卡车，其容量为 $m$。

工厂附近的采购点都在同一条路的同一方向上，一共有 $n$ 个，每个采购点和工厂的距离各不相同。其中，第 $i$ 个采购点的价格为 $a_i$, 库存为 $b_i$, 距离为 $c_i$。

卡车每行驶一单位长度的路径就需要额外花费 $o$。（返程没有花费，你也可以认为 $o$ 实际是行驶两单位长度的花费）

请计算将卡车装满最少需要花费多少钱，如果没有任何方案可以装满请输出 $-1$。

## 说明/提示

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$n \leq 5000$, $m \leq 50000$;
- 对于 $60\%$ 的评测用例，$m \leq 10^5$;
- 对于所有评测用例，$1 \leq n \leq 10^5$, $1 \leq m, o \leq 10^9$, $1 \leq a_i, b_i, c_i \leq 10^9$, 保证对于 $i > 1$, 一定有 $c_{i-1} < c_i$。

## 样例 #1

### 输入

```
3 5 1
99 9 1
3 4 99
1 2 190```

### 输出

```
201```

# 题解

## 作者：蒋淋雨 (赞：3)

# P12187 [蓝桥杯 2025 省 Python A/Java A/研究生组] 原料采购

## 题意
路上有 $n$ 个站点，第 $i$ 个站点有 $b_i$ 个货物，每个货物 $a_i$ 元，距离为 $c_i$ ，单位距离运费为 $o$ ，需要装满容量为 $m$ 的卡车，问最小代价。

## 思路
妖零圈（省选计划老师）下午在群里说蓝桥杯的题过于经典，过于板子了，所以说质量不高，但是练习 $trick$ 还是好的。

~愣着干什么，报班啊！~

 回到正题。

 答案为 $-1$ 的情况很简单，就是$\sum_{i=1}^{n} b_i < m$ 。
 
做题的时候也很容易想到，如果当前选的更优，那么很显然直接替换掉之前选过的不优的即可。没接触过这个技巧的同学可能会无从下手，或者硬暴力看之前哪个选过的可以被替换。

我们可以用一个叫做翻回贪心的 $trick$ 来解决这道题。就是用一个大根堆（优先队列）来存单位价值和数量。

每次弹出不优的，放入更优的即可。

这个时候还差一个关键点，**距离**。

那我弹出不优的，是不是还要减去他们的距离带来的运费呢?这个时候岂不是很麻烦。（比如当前弹掉了不优秀的，我不优秀的之前的距离是什么？再比如我当前虽然单价更优更便宜，但是加上运费就贵了，那我岂不是白弹了？）

**想复杂了**

我们发现，物品都是一样的，也就是说我卡车装一个 $1$ 号站点的物品和装一个 $2$ 号站点的物品，除了价钱不一样，剩下都一样。

那么我们可以在更新优先队列结束后去统计价钱。

先给出部分代码。

```cpp
while(sz(q)){
      pii it=q.top();
      if(it.fi>a[i]){
          q.pop();
          if(b[i]>Used+it.se){
              v-=it.fi*it.se;
              Used+=it.se;
            }else{
                v-=it.fi*(b[i]-Used);
                it.se-=(b[i]-Used);
                Used=b[i];
                if(it.se)q.push(it);break;
              }
        }else break;
    }
  if(Used){
      q.push({a[i],Used});
      v+=a[i]*Used;
  }
    ans=min(ans,v+c[i]*o);
```

比如说有三次，第一次放入很贵的物品，此时装满。第二次放入很便宜的物品但是运费很贵导致还不如第一次优。第三次放入运费和商品价格都很便宜的物品。

我们直接看最后对 $ans$ 的更新，就是说即便第二次你队列里物品已经从第一次的被换成第二次的了，$ans$ 不优也不会改变，本质上物品是没有被换的。

而接下来假设要被真正替换的话。表面上是第三次的物品替换了第二次的（因为此时由于单价，队列里存的商品实际上是第二次单价低但是运费贵而没被替换的），实际上和第三次的物品替换了第一次没有区别。

然后就可以愉快地切了这道题了。
哦，由于值域范围，初始答案记得设大一些，像我设置成 $10^{16}$ 就第一发喜提了 $95pts$ 。

## 完整代码
```cpp
#define rep(i, a, b) for(int i=a;i<=b;i++)
#define sz(x) (int)(x).size()
int m,o,a[100005],b[100005],c[100005],n;
void solve() {
    cin >> n >> m >> o;
    int ss = 0;
    rep(i, 1, n)cin >> a[i] >> b[i] >> c[i], ss += b[i];
    if (ss < m) {
        cout << -1;
        return;
    }
    priority_queue<pii > q;
    int now = 0, ans = 4e18, v = 0;
    rep(i, 1, n) {
        if (now + b[i] <= m) {
            now += b[i];
            q.push({a[i], b[i]});
            v += a[i] * b[i];
            continue;
        } else {
            if (now < m) {
                q.push({a[i], m - now});
                v += a[i] * (m - now);
                b[i] -= (m - now);
                now = m;
            }
            int Used = 0;
            while (sz(q)) {
                pii it = q.top();
                if (it.fi > a[i]) {
                    q.pop();
                    if (b[i] > Used + it.se) {
                        v -= it.fi * it.se;
                        Used += it.se;
                    } else {
                        v -= it.fi * (b[i] - Used);
                        it.se -= (b[i] - Used);
                        Used = b[i];
                        if (it.se)q.push(it);
                        break;
                    }
                } else break;
            }
            if (Used) {
                q.push({a[i], Used});
                v += a[i] * Used;
            }
            ans = min(ans, v + c[i] * o);
        }
    }
    cout << ans;
}
```

---

## 作者：Aliadgnus (赞：1)

## 前置知识
[反悔贪心](https://oi-wiki.org/basic/greedy/)

## 题目大意
每一个采购点有价格、库存和距离。需要我们计算装满卡车所需的最少费用，考虑装货费用和运输路程费用。如果无法装满，输出 $-1$。
## 思路
我们考虑贪心，先把选出来的原料放进优先队列里由高到低降序排列，我们在从前面到后面一一去遍历原料，每当我们的原料满了的时候，将当前原料的价格与已选原料中最高的价格进行比较，如果当前价格低于已选原料，我们就反悔一次，进行替换。这实质上是一个反悔贪心。

总费用是当前的原料费用与路费相加，取最小值即可。

**细节**：本题存在原料不足的情况，需要特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxa 1005
#define int long long 
#define inf 3e18
#define repr(i,a,b) for(int i = a;i <= b;i++)
int n,m,o;
int a[maxn],b[maxn],c[maxn];
int cost,use,sum;
int ans = inf;
struct node{
    int price,wei;
    bool operator<(const node &x)const{
        return price < x.price;//排序
    }
};
priority_queue<node> q;
signed main() {
    cin.tie(0)->ios::sync_with_stdio(false);
    cout.tie(0);
    cin>>n>>m>>o;
    repr(i,1,n){
        cin>>a[i]>>b[i]>>c[i];
        use+=b[i];
    }
    if(use<m){
        cout<<-1<<endl;
        return 0;
    }//特判原料不足
    repr(i,1,n){
        if(cost+b[i]<=m){
            q.push({a[i],b[i]});
            cost += b[i];
            sum += (a[i]*b[i]);
        }
        else{
            if(cost<m){
                q.push({a[i],m-cost});
                b[i] -= m-cost;
                sum += a[i]*(m-cost);
                cost = m;
            }
            while(!q.empty()&&b[i]){//替换
                node u = q.top();
                if(u.price<=a[i]) break;
                q.pop();
                if(b[i]>=u.wei){
                    q.push({a[i],u.wei});
                    b[i] -= u.wei;
                    sum -= (u.price-a[i])*u.wei;
                }
                else{
                    q.push({a[i],b[i]});
                    q.push({u.price,u.wei-b[i]});
                    sum -= ((u.price-a[i])*b[i]);
                    b[i] = 0;
                }
            }
            ans = min(ans,sum+c[i]*o);
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P12187 题解

## 思路

带反悔的贪心，对于每一个 $i$，求出走到第 $i$ 个采购点所能买到的方案中取最小值，即前 $m$ 便宜的 $a_i$。

于是可以开一个优先队列，存储取的所有货物的单价和数量，每走到一个地方，将这个地方的所有货全都丢到优先队列里，然后按价格从大到小取出货物扔掉，直到取的货物刚好为 $m$ 个。

每一次处理完，如果满 $m$ 个则取一次 $ans$，最后判断是否有解输出即可。

## 代码

```cpp
const int N=100005;
const int inf=1e18;

int n,m,o,cur,pos,cnt,ans=inf;
priority_queue<pii> q;

struct node {
    int a,b,c;
} arr[N];

i32 main() {
    read(n),read(m),read(o);
    _rep(i,1,n) {
        int a,b,c;
        read(a),read(b),read(c);
        arr[i]={a,b,c};
    }
    _rep(i,1,n) {
        cur+=(arr[i].c-pos)*o,pos=arr[i].c;
        cnt+=arr[i].b,cur+=arr[i].a*arr[i].b;
        q.emplace(pii{arr[i].a,arr[i].b});
        while (cnt>m && !q.empty()) {
            auto u=q.top(); q.pop();
            if (cnt-u.second>=m) cnt-=u.second,cur-=u.second*u.first;
            else {
                int k=cnt-m;
                u.second-=k,cnt-=k,cur-=k*u.first;
                q.emplace(u);
            }
        }
        if (cnt==m) ans=min(ans,cur);
    }
    if (cnt<m) puts("-1");
    else write(ans);
    return 0;
}
```

---

