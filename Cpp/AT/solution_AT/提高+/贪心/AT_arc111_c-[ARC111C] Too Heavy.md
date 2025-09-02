# [ARC111C] Too Heavy

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc111/tasks/arc111_c

$ 1 $ から $ N $ の番号がついた $ N $ 人の人間と、同じく $ 1 $ から $ N $ の番号がついた $ N $ 個の荷物があります。 人 $ i $ の体重は $ a_i $, 荷物 $ j $ の重さは $ b_j $ です。 はじめ人 $ i $ は 荷物 $ p_i $ を持っており、以下の操作を $ 0 $ 回以上繰り返すことで全ての人が自分と同じ番号の荷物を持っている状態にしたいです。

- $ i,j\ (i\ \neq\ j) $ を選び、人 $ i $ と人 $ j $ の荷物を交換する。

ただし、人は自分の体重**以上**の重さの荷物を持つと疲れてしまい、その後一切操作には加われません (すなわち、$ i,j $として選べません)。 特に、 $ a_i\ \leq\ b_{p_i} $ なら一度も操作に加われません。

条件を満たす操作列があるか判定し、存在するならばそのうち**操作回数が最小**であるものをひとつ構成してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ a_i,b_i\ \leq\ 10^9 $
- $ p $ は $ 1,\ \ldots\ ,N $ の順列
- 入力される数はすべて整数

### Sample Explanation 1

初期状態で人 $ 1,2,3,4 $ が持っている荷物の重さはそれぞれ $ 1,3,3,5 $ なので、初期状態では誰も疲れていません。 まず人 $ 3 $ と $ 4 $ で操作をします。人 $ 1,2,3,4 $ が持っている荷物の重さはそれぞれ $ 1,3,5,3 $ なので、まだ誰も疲れていません。 次に人 $ 1 $ と $ 3 $ で操作をします。人 $ 1,2,3,4 $ が持っている荷物の重さはそれぞれ $ 5,3,1,3 $ なので、人 $ 1 $ が疲れます。 最後に人 $ 4 $ と $ 2 $ で操作をします。人 $ 1,2,3,4 $ が持っている荷物の重さはそれぞれ $ 5,3,1,3 $ なので、これで新たに疲れる人はいません。 これによって全員が正しい荷物を持っている状態になり、さらにこれは最小の操作回数なので、正しい出力の一つです。

### Sample Explanation 2

条件を満たすように操作することは出来ません。

### Sample Explanation 3

初期状態で条件を満たしています。

## 样例 #1

### 输入

```
4
3 4 8 6
5 3 1 3
3 4 2 1```

### 输出

```
3
3 4
1 3
4 2```

## 样例 #2

### 输入

```
4
1 2 3 4
4 3 2 1
4 3 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
1
58
998244353
1```

### 输出

```
0```

# 题解

## 作者：蒟酱 (赞：4)

无解的情况：当且仅当一个人手上的物品不是自己的物品，并且这个物品的质量大于自己的体重，这个不是自己的东西就卡手了，换不出去，无解。  
甲手上是乙的物品。乙的手上是丙的物品，丙的手上是丁的物品，丁的手上是甲的物品，那么甲乙丙丁就形成了一个环，置换环。由于每个人手上的物品（即 $p_i$）是个排列，所以原序列肯定可以划分为多个置换环，那么只要思考对于每个置换环怎么做就行了。  
找到环内体重最大的，然后按照环的顺序每次把下一个人和体重最大的交换手中的物品就行了。  
在这个交换过程中会不会出现卡手的情况呢？除去体重最大的那个人，环内的其他人都只交换了一次。如果一次都不能交换已经判定过了。而体重最大的如果会卡手，那这个物品是比环内所有人的体重都大的，而这种情况也判定过了。所以无解的情况只有一种。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define siz(x) int((x).size())
#define all(x) std::begin(x),std::end(x)
using std::cin;using std::cout;
using pii=std::pair<int,int>;
using bsi=std::basic_string<int>;
constexpr int N=200001;
int n,a[N],b[N],p[N];
bool t[N];
bsi r;
std::vector<pii>ans;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)
		if(cin>>p[i],p[i]!=i&&b[p[i]]>=a[i])
			return cout<<"-1",0;
	for(int i=1;i<=n;i++)if(!t[i]){
		r.clear();
		for(int j=i;!t[j];j=p[j])
			t[j]=true,r+=j;
		int k=*max_element(all(r),[](int x,int y){
			return a[x]<a[y];});
		for(int j=k;p[j]!=k;j=p[j])
			ans.emplace_back(k,p[j]);
	}
	cout<<siz(ans)<<'\n';
	for(auto[u,v]:ans)cout<<u<<' '<<v<<'\n';
	return 0;
}
```

---

## 作者：Remilia1023 (赞：4)

显然有一种无解的情况，初始时 $\exists i, i \not= p_i \wedge a_i\le b_{p_i}$，即 $i$ 没有提自己的行李，并且 $i$ 的重量小于等于 $i$ 提的行李的重量，此时 $i$ 无法参与任何交换。

接下来讨论有解的情况，此时满足 $\forall i\in[1,n],a_i> b_{p_i}$ 。将 $i$ 与 $p_i$ 连边，因为 $p$ 是 $1\cdots n$ 的排列，会得到 $C$ 个环，最终的目标是得到 $n$ 个自环，此时 $\forall i\in[1,n],i=p_i$。

可以对于每个环分别考虑，先找到每个环 $a_i$ 最小的人 $x$，以及 $p_y=x$ 的人 $y$，交换 $p_x,p_y$。因为 $a_x$ 是环中最小的，所以 $a_x\le a_y$，在有解的前提下，保证了 $b_{p_x}<a_x$。因此，交换后，原来的 $b_{p_x}<a_y$，$y$ 可以继续参与交换，而 $x=p_x$，$x$ 已经满足条件，会使环的长度减小 $1$。形象地理解，环在 $x$ 处由 $\cdots y\rightarrow x\rightarrow z\cdots$ 变为了 $\cdots y\rightarrow z\cdots ,x\rightarrow x$。

重复此操作，直到环长变为 $1$。

可以发现，这样的策略保证除了最开始提到的情况之外都是有解的。由于每次环的长度减小 $1$，而目标是得到 $n$ 个自环，所以需要 $n-C$ 次操作，这样刚好能取到答案下界，感性理解，最优的操作下每次操作要么使 $1$ 个人，要么使 $2$ 个人满足条件，前者只需操作一步，后者就是一个长度为 $2$ 的环，也只需要操作一步，与上面的策略操作次数相同。

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace IO{
// 这里是一个快读板子，就省去了
}

const int N = 3e5;
int n, top, vis[N], p[N], a[N], b[N], cyc[N], rev[N];
using pii = pair<int, int>;
vector<pii> opt;

bool cmp(int x, int y)
{
  return a[x] < a[y];
}

int main()
{
  qcin >> n;
  for (int i = 1; i <= n; i++) qcin >> a[i];
  for (int i = 1; i <= n; i++) qcin >> b[i];
  for (int i = 1; i <= n; i++) {
    qcin >> p[i];  rev[p[i]] = i;
    if (a[i] <= b[p[i]] && i != p[i])
      return qcout << -1 << endl, 0;  // 判断无解
  }
  for (int i = 1; i <= n; i++)
    if (!vis[i] && i != p[i]) {
      top = 0;
      int u = i;
      while (!vis[u]) {   // 找环
        vis[u] = 1;
        cyc[++top] = u;
        u = p[u];
      }
      sort(cyc + 1, cyc + top + 1, cmp);  // 每次找到最小的 ai
      for (int j = 1; j <= top - 1; j++) {
        u = cyc[j];
        opt.emplace_back(pii{u, rev[u]});
        p[rev[u]] = p[u];
        rev[p[u]] = rev[u];
      }
    }
  qcout << opt.size() << endl;
  for (pii u : opt)
    qcout << u.first << ' ' << u.second << endl;
  return 0;
}
不懂的可以评论区问我哦，如有错误请指出qwq
```

---

## 作者：StarRoam (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc111_c)


 - 我们首先考虑无解的情况，即此时有一对交换不且位置并不匹配。


 - 接着考虑如何构造方案，此时有一个贪心思想：我们只要尽量拿重量小的物品作为交换的中转站即可，每次选择没有匹配的人中物品重量最小的一个，向拥有他所对应的物品的人进行交换，因为这样所交换的物品重量是单调不降的，则两人之间一定可以交换。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5;
int n,p[N];
ll a[N],b[N];
int trk[N];
struct Data{
	ll w;
	int num;
}t[N];
struct ANS{
	int x,y;
}ans[N];
bool cmp(Data px,Data py){
	return px.w<py.w;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	for(int i=1;i<=n;i++)
	{
		cin>>p[i];
		if(b[p[i]]>=a[i]&&i!=p[i]){
			cout<<"-1";
			return 0;
		}
		t[i]=Data{b[p[i]],i};
		trk[p[i]]=i;
	}
	sort(t+1,t+n+1,cmp);
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		int now=t[i].num;
		while(now!=trk[now])
		{
			int x=now,y=trk[now];
			ans[++cnt]=ANS{x,y};
			swap(p[x],p[y]);
			trk[p[x]]=x,trk[p[y]]=y;
		}
	}
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++)
		cout<<ans[i].x<<" "<<ans[i].y<<"\n";
	return 0;
}
```

---

