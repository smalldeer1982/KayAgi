# Dining Hall

## 题目描述

在一个庞大的王国中，有一个无限大的餐厅。

该餐厅可以表示为由单元格 $(x, y)$ 构成的集合，其中 $x, y$ 是自然数。餐厅内还有无数张桌子。每张桌子由四个单元格定义：$(3x + 1, 3y + 1)$、$(3x + 1, 3y + 2)$、$(3x + 2, 3y + 1)$、$(3x + 2, 3y + 2)$，其中 $x, y$ 是非负整数。所有不属于任何桌子的单元格被视为走廊。

客人只能在走廊中移动，且每次只能通过相邻的边移动到相邻的单元格，每次移动耗时相同。注意：客人只能在最后一次移动时坐在桌子上，且必须坐在桌子上。

在王国的一场晚宴中，共有 $n$ 位客人到来，每位客人有一个特征值 $t_i$（取值为 $0$ 或 $1$）。他们按顺序进入大厅，从单元格 $(0, 0)$ 出发走向某张桌子。若第 $i$ 位客人的 $t_i = 1$，则他会选择距离最近的仍有空位的桌子；若 $t_i = 0$，则他会选择距离最近的未被占用的桌子（即使后续可能有其他客人加入）。若存在多张桌子距离相同，则选择 $x$ 坐标最小的单元格；若仍有多个选项，则选择其中 $y$ 坐标最小的单元格。

从单元格到桌子的距离定义为到该桌子上最近的未被占用的单元格的距离。两单元格之间的距离按移动到相邻单元格的次数计算。注意：移动过程中不允许穿过属于桌子的单元格，除非是最后一步（该步骤会将你放置在桌子的最终单元格上）。

为更好理解条件，可参考说明中的图示。

你无需亲自计算所有客人的入座情况，请直接输出每位客人最终入座的单元格。

## 说明/提示

第一位客人到单元格 $(1, 1)$ 的距离为 2，因此选择该位置。

第二位客人到单元格 $(1, 2)$ 和 $(2, 1)$ 的距离均为 3，但由于 $1 < 2$，因此选择 $(1, 2)$。无额外约束。

第三位客人到单元格 $(2, 1)$ 的距离为 3，因此选择该位置。

第四位客人到单元格 $(1, 4)$ 的距离为 5，因此选择该位置。

第五位客人到单元格 $(4, 1)$ 的距离为 5。

第六位客人到单元格 $(1, 5)$ 和 $(2, 2)$ 的距离均为 6，但由于 $x$ 坐标更小，因此选择 $(1, 5)$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2090C/14307747f44bf893a0cb5c3731d43642a649f3b9.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
6
0 1 1 0 0 1
5
1 0 0 1 1```

### 输出

```
1 1
1 2
2 1
1 4
4 1
1 5
1 1
1 4
4 1
1 2
2 1```

# 题解

## 作者：AstaVenti_ (赞：10)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{54}$ 篇题解。

# $\mathbf{0x01}$ 承

大厅有无限个 $2\times 2$ 的桌子，每两个桌子之间都有一条宽度为 $1$ 的走廊，对于在 $(0,0)$ 的每一个人 $a_i$：

- 如果 $a_i=0$，则找到最近的空桌子（四个位置每个都没人）坐下；
- 如果 $a_i=1$，则找到最近的空位置（可能是空桌子，可能有人）坐下。

求出每个人的位置。

# $\mathbf{0x02}$ 转

下图表示到达大厅中的所有桌子（灰色部分）所需的最小步数：

![](https://cdn.luogu.com.cn/upload/image_hosting/y6oqkedk.png)

可以发现相同步数的位置呈斜向排列，即对于一个桌子上的一个位置 $(x,y)$，则另外一个桌子上的位置 $(x+3,y-3)$ 需要相同的步数。

为了找到当前距离最小的点，可以用优先队列维护。

其它内容详见代码注释。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<ll,ll,ll> tp;//分别表示步数、x 和 y
ll T,n;
int main(){
	cin>>T;
	while(T--){
		priority_queue<tp,vector<tp>,greater<tp>>pq;
		ll x=1,y=1,dis=2;//位置和步数
		cin>>n;
		vector<pair<ll,ll>>ans(n+1);
		for(ll i=1,xx;i<=n;i++){
			cin>>xx;
			if(xx&&pq.size()&&get<0>(pq.top())<dis){
				//需要空位置，堆不为空，距离小于 dis
				auto p=pq.top();
				pq.pop();
				ans[i]={get<1>(p),get<2>(p)};
			}else{
				ans[i]={x,y};
				pq.push({x+y+1,x+1,y});
				pq.push({x+y+1,x,y+1});
				pq.push({x+y+4,x+1,y+1});
				//把这个桌子其他三个位置放入堆
				(y-1)?(x+=3,y-=3):(swap(x,y),y+=3);
				//这里如果 y=1 需要特判
				dis=x+y;
			}
		}
		for(ll i=1;i<=n;i++){
			cout<<ans[i].first<<" "<<ans[i].second<<endl;
		}
	}
}

```

---

## 作者：BLuemoon_ (赞：2)

[link](https://www.luogu.com.cn/problem/CF2090C)

## 思路

考虑最坏的情况，即每个人都要一个单独的桌子：

![](https://cdn.luogu.com.cn/upload/image_hosting/mejftbd0.png)

可以发现这是阶梯状分布的，于是我们用到的桌子最多 $\sqrt{2n}$ 行 $\sqrt{2n}$ 列的。

我们可以用一个 `dis` 函数计算每个格子距离原点的距离，注意每个桌子右上角的距离要 $+2$。使用两个 `set` 分别存下这些可能的被坐的桌子的每个点，一个 `set` 存所有能坐的位置，另一个存没被坐过的桌子。这样就可以根据不同的需求快速找答案了。

在有人坐进来时，删掉两个 `set` 中不能再被坐的点，注意判断这个点是否已经被删掉，否则会 RE。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using DB = double;

const int kMaxN = 5e4 + 5;

LL T = 1, n, a[kMaxN], ans;
string s;

void pr(bool pr) { cout << (pr ? "YES" : "NO") << '\n'; }
int dis(int x, int y) {
  if (x % 3 == 2 && y % 3 == 2) {
    return x + y + 2;
  } else {
    return x + y;
  }
}

struct P {
  int x, y;
  bool operator<(const P &o) const {
    return dis(x, y) != dis(o.x, o.y) ? dis(x, y) < dis(o.x, o.y) : (x != o.x ? x < o.x : y < o.y);
  }
};

set<P> f, g;

void del(int x, int y) {
  f.count({x, y}) && (f.erase({x, y}));
  x % 3 == 2 && (x--), y % 3 == 2 && (y--);
  g.count({x, y}) && (g.erase({x, y}));
  g.count({x, y + 1}) && (g.erase({x, y + 1}));
  g.count({x + 1, y}) && (g.erase({x + 1, y}));
  g.count({x + 1, y + 1}) && (g.erase({x + 1, y + 1}));
} 

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> T; T; T--, ans = 0, f.clear(), g.clear()) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 0; i * i <= n << 1; i++) {
      for (int j = 0; j * j <= n << 1; j++) {
        f.insert({3 * i + 1, 3 * j + 1}), f.insert({3 * i + 1, 3 * j + 2}), f.insert({3 * i + 2, 3 * j + 1}), f.insert({3 * i + 2, 3 * j + 2});
        g.insert({3 * i + 1, 3 * j + 1}), g.insert({3 * i + 1, 3 * j + 2}), g.insert({3 * i + 2, 3 * j + 1}), g.insert({3 * i + 2, 3 * j + 2});
      }
    }
    for (int i = 1; i <= n; i++) {
      if (a[i]) {
        cout << (*f.begin()).x << ' ' << (*f.begin()).y << '\n';
        del((*f.begin()).x, (*f.begin()).y);
      } else {
        cout << (*g.begin()).x << ' ' << (*g.begin()).y << '\n';
        del((*g.begin()).x, (*g.begin()).y);
      }
    }
  }
  return 0;
}
```

---

## 作者：postpone (赞：1)

无论是哪种宾客，他们选座位的优先级都是：从走廊走过去的距离最近，然后是 $x$ 坐标最小。

我们考虑一种由距离到一个有序集合的映射，这个有序集合存放坐标，以 $x$ 从小到大排序。对于每一个宾客，我们先找到距离最近的集合，然后从集合中取走第一个元素即可。

再来分析两种宾客的要求，一个是随便，一个是只能选目前没人坐的桌子。又因为优先坐近的，两者面对没人坐的桌子时都会选左下角。因此对于后者，不存在“有桌子的左下角空出来，但是我不能坐”的情况。

那么我们用 $\texttt{std::map}$ 来实现上述的映射，一个存放所有座位，一个只存所有桌子的左下角，依照顺序根据宾客类型来拿座位即可。

[完整代码](https://codeforces.com/contest/2090/submission/312202682)

---

