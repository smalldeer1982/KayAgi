# [APC001] D - Array Again

## 题目描述

你需要维护一个数列，支持 $4$ 种操作：

1. `1 x y`：连续向数列中插入 $y$ 个数 $x$。
2. `2 x y`：连续在数列中删除 $y$ 次 $x$。如果在某一次删除中 $x$ 已经不存在于数列中，则忽略此操作。
3. `3`：对数列进行去重，即，对于每个在数列中出现过的不同的正整数 $x$，如果它在数列中出现了大于 $1$ 次，则只在数列中保留一个 $x$，其余全部删除。
4. `4 x`：查询数列中 $x$ 的出现次数。

对于每个操作 $4$，请求出其答案。

## 说明/提示

### 样例解释 $1$

第 $1$ 次操作：插入 $10$ 个 $2$。

第 $2$ 次操作：删除 $5$ 个 $2$。此后数列中只包含 $5$ 个 $2$。

第 $3$ 次操作：查询 $2$ 的出现次数，共 $5$ 次。

第 $4$ 次操作：对数列进行去重。此后数列中只包含一个 $2$。

第 $5$ 次操作：查询 $2$ 的出现次数，共 $1$ 次。

### 样例解释 $2$

请注意答案可能会超过 `int` 的范围。

### 数据范围

对于 $100\%$ 的数据，$1\le q\le 10^5$，$1\le x,y\le 10^9$。

请注意：由于本题所在比赛没有部分分，故只有通过所有的测试点才可以获得满分，否则会获得 $0$ 分。

## 样例 #1

### 输入

```
5
1 2 10
2 2 5
4 2
3
4 2```

### 输出

```
5
1```

## 样例 #2

### 输入

```
4
1 1000000000 1000000000
1 1000000000 1000000000
1 1000000000 1000000000
4 1000000000```

### 输出

```
3000000000```

## 样例 #3

### 输入

```
20
4 95002957
2 384405322 255642125
2 384405322 174926753
2 384405322 51265222
1 384405322 311383201
4 384405322
1 384405322 5464229
4 22438767
4 17075617
1 384405322 153189933
1 230228188 148299369
1 7168162 387115701
1 384405322 154480360
1 384405322 438458686
3
1 7961090 98996809
4 153074129
1 975025351 171484003
1 384405322 650527951
4 384405322```

### 输出

```
0
311383201
0
0
0
650527952```

# 题解

## 作者：tjtdrxxz (赞：8)

题目要求我们写一个能加入，删除，去重，单点查询的数据结构，很容易能想到线段树。

但，数据范围让这道题变得有点坑，直接开 $ 10 ^ 9 $ 的数组肯定是要寄的，所以我们可以考虑动态开点。

类似于主席树，我们每次查询一个点的时候，如果该点存在，就不管，不然我们就新建一个点。

加入操作很简单，直接把 $ x $ 所在的点加上 $ y $ 就好了，删除操作和加入操作一样，但注意是减去 $ y $，去重操作其实也不难想，只用在根节点修改他的 lazy_tag，每次下传就好了，查询操作也很简单，单点查询板板。

~~因为我懒~~，所以我用的指针。

code：
```cpp
# include "bits/stdc++.h"
# define int long long
using namespace std;
struct node
{
	int l; int r;
	node *ll, *rr;
	int sum, tag;
	node ()
	{
		l = 0, r = 0;
		ll = rr = NULL;
		tag = sum = 0;
	}
};
node *root;
node *push_up (node *ind)
{
	ind -> sum = 0;
	if (ind -> ll)
	{
		ind -> sum += ind -> ll -> sum;
	}
	if (ind -> rr)
	{
		ind -> sum += ind -> rr -> sum;
	}
	return ind;
}
node *push_down (node *ind)
{
	if (ind -> tag)
	{
		if (ind -> ll)
		{
			if (ind -> ll -> sum)
			{
				ind -> ll -> sum = ind -> ll -> r - ind -> ll -> l + 1;
				ind -> ll -> tag = ind -> tag;
			}
		}
		if (ind -> rr)
		{
			if (ind -> rr -> sum)
			{
				ind -> rr -> sum = ind -> rr -> r - ind -> rr -> l + 1;
				ind -> rr -> tag = ind -> tag;
			}
		}
		ind -> tag = 0;
	}
	return ind;
}
node *amend (int dis, node *ind, int l, int r, int x)
{
	if (!ind) ind = (new node ());
	ind -> l = l;
	ind -> r = r;
	if (l == r)
	{
		ind -> sum += x;
		if (ind -> sum < 0) ind -> sum = 0;
		return ind;
	}
	ind = push_down (ind);
	int m1 = l + r >> 1; if (m1 >= dis) ind -> ll = amend (dis, ind -> ll, l, m1, x);
	int m2 = m1 * 1 + 1; if (m2 <= dis) ind -> rr = amend (dis, ind -> rr, m2, r, x);
	push_up (ind);
	return ind;
}
int sum (int dis, node *ind, int l, int r)
{
	if (!ind) return 0;
	if (l == r)
	{
		return ind -> sum;
	}
	ind = push_down (ind);
	int m1 = l + r >> 1; if (m1 >= dis) return sum (dis, ind -> ll, l, m1);
	int m2 = m1 * 1 + 1; if (m2 <= dis) return sum (dis, ind -> rr, m2, r);
	return 0;
}
node *change (node *ind)
{
	ind -> tag = 1;
	ind -> sum = ind -> r - ind -> l + 1;
	return ind;
}
int m;
# define stdi stdin
# define stdo stdout
signed main ()
{
	setvbuf (stdi, (char*) calloc (1 << 20, sizeof (char)), _IOFBF, 1 << 20);
	setvbuf (stdo, (char*) calloc (1 << 20, sizeof (char)), _IOFBF, 1 << 20);
	scanf ("%lld", &m);
	do
	{
		int op, x, y;
		scanf ("%lld", &op);
		if (op == 1) scanf ("%lld %lld", &x, &y), root = amend (x, root, 1, 1000000000, y);
		if (op == 2) scanf ("%lld %lld", &x, &y), root = amend (x, root, 1, 1000000000, -y);
		if (op == 3) root = change (root);
		if (op == 4) scanf ("%lld", &x), printf ("%lld\n", sum (x, root, 1, 1000000000));
	} while (-- m);
}
```

---

## 作者：Zskioaert1106 (赞：7)

题目传送门：[P11139 [APC001] D - Array Again](https://www.luogu.com.cn/problem/P11139)

一个很方便用 STL 的模拟。

### 题意简述

省流：你要实现一个支持批量加入、批量删除、去重、查询的数据结构。

### 前置知识

> STL 是 Standard Template Library 的简称，中文名标准模板库。
>
> 在实际的开发过程中，数据结构本身的重要性不会逊于操作于数据结构的算法的重要性，当程序中存在着对时间要求很高的部分时，数据结构的选择就显得更加重要。

map 是一种高效方便的数据结构，它有点类似“字典”，又键值对组成。它与数组的区别在于只有声明一个键才会占用这份空间，具有极大的空间流动性。同时键和值都可以是各种数据类型。

map 的定义方法是：`map<type,type>p`，第一个类型是键的类型，第二个是值的类型。

使用 map 要引用 C++ 的 `map` 库。

### 题目分析

注意到题目中的操作都是针对某个特定的数的，所以很适合用 map。

我们定义 `map<long long,long long>p` ，将 `p[x]` 表示数 $x$ 在数列中的出现次数。则对于第一种操作，直接将 `p[x]` 的值加上 $y$ 即可。

对于第二种操作，将 $p_x$ 的值设为 $\max(p_x,0)$，可以满足题目要求。

对于第三种操作，我们可以学习 map 的遍历方法，~~但是有些麻烦~~，于是我们可以用一个队列来存储所有在数列中出现过且没有重置过的 $x$，每次进行操作 3 时就将队列中的所有元素在 map 中的映射依次变为 $1$。

对于操作 4，则直接输出 `p[x]` 即可。

- map 的特性之一：如果你未定义 map 中某个键，它不会占用空间，但查询时会返回 $0$。查询之后这个键就要占据空间了。

### 代码编写

初始化：

```cpp
#include<iostream>
#include<map>
#include<queue>
```

```cpp
map<long long ,long long>p;
queue<long long>q;
int Q;
int main(){
    cin>>Q;
    while(Q--){
```

定义一个变量 $opt$ 表示操作种类，操作 1：

```cpp
    	short opt;
    	cin>>opt;
    	if(opt==1){
    		long long x,y;
    		cin>>x>>y;
    		p[x]=p[x]+y;
    		q.push(x);
		}
```

上面的 `q.push(x)` 表示将这个值加入待会重置的队列了。

操作 2：

```cpp
		else if(opt==2){
			long long x,y;
    		cin>>x>>y;
    		p[x]=max(p[x]-y,0ll);
		}
```

在操作 3 中，我们可以重复将 $q$ 的内容出队，并将 map 中的该值去重：

```cpp
		else if(opt==3){
			while(!q.empty()){
				if(p[q.front()]>1)p[q.front()]=1ll;
				q.pop();
			}
		}
```

在上面的重置中，我们注意到将 $p_{q_i}$ 重置后并未将出队的 $q_i$ 放回队列，因为如果之后 $p_{q_i}$ 还会改变，那么它还会在操作 1 入队，否则它一定一直是 $1$。

操作 4：

```cpp
		else if(opt==4){
			long long x;
			cin>>x;
			cout<<p[x]<<'\n';
		}
```

如此就完成了主要部分。这样的模拟题还是比较简单的。

### 完整代码

```cpp
#include<iostream>
#include<map>
#include<queue>
using namespace std;
map<long long ,long long>p;
queue<long long>q;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int Q;
    cin>>Q;
    while(Q--){
    	short opt;
    	cin>>opt;
    	if(opt==1){
    		long long x,y;
    		cin>>x>>y;
    		p[x]=p[x]+y;
    		q.push(x);
		}
		else if(opt==2){
			long long x,y;
    		cin>>x>>y;
    		p[x]=max(p[x]-y,0ll);
		}
		else if(opt==3){
			while(!q.empty()){
				if(p[q.front()]>1)p[q.front()]=1ll;
				q.pop();
			}
		}
		else if(opt==4){
			long long x;
			cin>>x;
			cout<<p[x]<<'\n';
		}
	}
    return 0;
}
```

[赛时 AC 记录](https://www.luogu.com.cn/record/179316377)，可放心食用。

---

## 作者：ARIS2_0 (赞：3)

我们发现，对于操作 1、2、4，我们只需要用最朴素的 Hash 表就可以解决。可对于操作 3，如果暴力修改，时间复杂度为操作 3 的次数乘上 Hash 表中的元素个数，很容易 TLE。

我们考虑降低操作 3 的时间复杂度。假设我们的 Hash 表使用 `vector` 实现，基本操作如下：


```cpp
const int mod=1e3+7;
struct node{
	int id,num;
};
vector<node>v[mod];
void add(int id,int num){
	int x=id%mod;bool find=0;
	for(int i=0;i<v[x].size();i++){
		if(v[x][i].id==id){
			v[x][i].num+=num;
			find=1;break;
		}
	}
	if(!find){
		v[x].push_back(node{id,num});
	}
	return;
}
void erase(int id,int num){
	int x=id%mod;
	for(int i=0;i<v[x].size();i++){
		if(v[x][i].id==id){
			v[x][i].num-=num;
			if(v[x][i].num<0)v[x][i].num=0;
			break;
		}
	}
	return;
}
int check(int id){
	int x=id%mod;
	for(int i=0;i<v[x].size();i++){
		if(v[x][i].id==id)return v[x][i].num;
	}return 0;
}
```

深入思考，发现对于每次操作 3，我们没有必要把每个元素的 $num$ 设成 $1$ 或 $0$，只需要使用 $b_i$ 表示 $v_i$ 中的所有元素需不需要执行操作 3（去重），然后对于每次 `add` `erase` `check` 操作，定位到 $v_x$ 后，先检查 $b_x$ 是否为真，若为真，将 $v_x$ 中所有元素的 $num$ 重置为 $1$ 或 $0$（因为可能有 $num$ 为 $0$ 的元素），然后使 $b_x=false$ 即可。注意，这里 Hash 表的 $mod$ 不能开太大，因为操作 3 的时间复杂度是 $O(mod)$ 的。本人亲身实践，开到 $10^6+7$ 一堆 TLE。完整代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e3+7;
bool b[mod];
struct node{
	int id,num;
};
vector<node>v[mod];
void add(int id,int num){
	int x=id%mod;bool find=0;
	if(b[x]){
		for(int i=0;i<v[x].size();i++){
			v[x][i].num=min(v[x][i].num,1ll);
		}
		b[x]=0;
	}
	for(int i=0;i<v[x].size();i++){
		if(v[x][i].id==id){
			v[x][i].num+=num;
			find=1;break;
		}
	}
	if(!find){
		v[x].push_back(node{id,num});
	}
	return;
}
void erase(int id,int num){
	int x=id%mod;
	if(b[x]){
		for(int i=0;i<v[x].size();i++){
			v[x][i].num=min(v[x][i].num,1ll);
		}
		b[x]=0;
	}
	for(int i=0;i<v[x].size();i++){
		if(v[x][i].id==id){
			v[x][i].num-=num;
			if(v[x][i].num<0)v[x][i].num=0;
			break;
		}
	}
	return;
}
void my_unique(){
	for(int i=0;i<mod;i++)b[i]=1;
}
int check(int id){
	int x=id%mod;
	if(b[x]){
		for(int i=0;i<v[x].size();i++){
			v[x][i].num=min(v[x][i].num,1ll);
		}
		b[x]=0;
	}
	for(int i=0;i<v[x].size();i++){
		if(v[x][i].id==id)return v[x][i].num;
	}return 0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
	int n;cin>>n;
	while(n--){
		int op,x,y;cin>>op;
		switch(op){
			case 1:{cin>>x>>y;
				add(x,y);
				break;
			}
			case 2:{cin>>x>>y;
				erase(x,y);
				break;
			}
			case 3:{
				my_unique();
				break;
			}
			case 4:{cin>>x;
				cout<<check(x)<<"\n";
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：__Allen_123__ (赞：3)

不需要数据结构，但需要 STL。当然如果你想写动态开点线段树之类的也没问题。

我们显然有一个朴素 $O(nq)$ 做法：记录每个数的个数，在去重时把所有数的数量都改变成 $1$，但复杂度过高，无法接受。

可见对于其他操作都可以 $O(1)$ 完成，优化瓶颈在去重操作上。

我们考虑离线修改。对于操作 $1,2,4$，在原本的操作之前先判断上一次它的修改是否在上一次去重之前。如果是，则之前这些数的数量已经变为 $1$，使用一个 `map` 维护上一次操作编号以及数量即可。

```cpp
#include <bits/stdc++.h>
//#define int long long
#define pii pair<int, int>
#define rep(x, y, z) for(int x = (y);x <= (int)(z);x++)
#define per(x, y, z) for(int x = (y);x >= (int)(z);x--)
#define ask(x) while(x--)
#define ask1(x) for(scanf("%d", &x);x--;)
#define fvec(x, y) for(auto x : y)
#define all(x) x.begin(), x.end()
#define pb push_back
#define fi first
#define se second
typedef long long ll;
using namespace std;
void gmax(auto &x, auto y){
	x = max(x, y);
}
void gmin(auto &x, auto y){
	x = min(x, y);
}
const int inf = 0x3f3f3f3f, p = 1e9 + 7;
void add(auto &x, auto y){
	x = (x + y % p) % p;
}
int q, op, x, y, lst = -1;
map<int, pair<ll, int>> mp;
signed main(){
	scanf("%d", &q);
	rep(i, 1, q){
		scanf("%d", &op);
		if(op == 1){
			scanf("%d%d", &x, &y);
			if(mp[x].se <= lst && mp[x].se){
				mp[x].fi = 1;
			}
			mp[x].fi += y;
			mp[x].se = i;
		}
		else if(op == 2){
			scanf("%d%d", &x, &y);
			if(mp[x].se <= lst && mp[x].se){
				mp[x].fi = 1;
			}
			mp[x].fi = max(mp[x].fi - y, 0ll);
			mp[x].se = i;
			if(!mp[x].fi){
				mp.erase(x);
			}
		}
		else if(op == 3){
			lst = i;
		}
		else{
			scanf("%d", &x);
			if(!mp.count(x)){
				printf("0\n");
			}
			else if(mp[x].se <= lst && mp[x].se){
				printf("1\n");
			}
			else{
				printf("%lld\n", mp[x].fi);
			}
		}
	}
	return 0;
}
```

#### Bonus

验题人的更为简便的做法。

使用一个 set 维护所有出现次数超过 $1$ 的数，每次操作 $3$ 时遍历 set 赋值为 $1$ 即可。

验题人代码：

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
int q;
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> q;
  map<int, int> mp;
  set<int> t;
  while (q--){
    int op, x, y;
    cin >> op;
    if (op == 1){
      cin >> x >> y;
      if (mp[x] <= 1){
        t.erase(x);
      }
      mp[x] += y;
      if (mp[x] > 1){
        t.insert(x);
      }
    }else if (op == 2){
      cin >> x >> y;
      if (mp[x] <= 1){
        t.erase(x);
      }
      mp[x] = max(0ll, mp[x] - y);
      if (mp[x] > 1){
        t.insert(x);
      }
      if (mp[x] == 0){
        mp.erase(x);
        t.erase(x);
      }
    }else if (op == 3){
      for (auto v : t){
        mp[v] = 1;
      }
      set<int> ().swap(t);
    }else {
      cin >> x;
      cout << mp[x] << '\n';
    }
  }
  return 0;
}
```

---

## 作者：__Luna__ (赞：2)

首先，STL 有一个东西叫做 map，它可是棵优秀的红黑树……   
用 map 记录每个数出现的次数，可以在 $O(1)$ 复杂度内实现操作 1，2 和 4。   
操作 3 直接暴力去重的单次复杂度为 $O(n)$，似乎压力有点大，没事让我们祈祷数据很弱……  
[提交记录](https://www.luogu.com.cn/record/179369773)，嗯，非常释怀地 TLE 了。   
怎么优化？我们可以借鉴一下懒标记的思路，在执行操作 3 时打一个标记，遇到操作 1，2 时再一起处理。   
我们不能让操作 3 修改每个数的标记，因为这样也会有 $O(n)$ 的复杂度；但我们也希望每个数都有一个标记，因为标记在各个数上停留的时间不同。   
一种解决方法是，记录一个公共标记，为去重操作的次数，修改复杂度为 $O(1)$；每个数有一个标记，表示最后一次下放标记处理的是第几次去重。   
当遇到操作 1，2 且对应数的标记小于公共标记时，就需要下放标记，即执行去重操作，同时将当前数的标记更新为公共标记。   
操作 4 不需要下放标记，只要在标记小于公共标记时输出 1 即可。不过即使此时将标记下放，也不会因此影响程序复杂度。   
通过代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,long long>m,m2;
int c;
int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		int i,j,k;
		cin>>i;
		if(i==1)
		{
			cin>>j>>k;
			if(m[j]==0)m2[j]=c;
			if(m2[j]<c)m[j]=k+1,m2[j]=c;
			else m[j]+=k;
		}
		if(i==2)
		{
			cin>>j>>k;
			if(m[j]==0)m2[j]=c;
			if(m2[j]<c)m[j]=0,m2[j]=c;
			else if(m[j]>k)m[j]-=k;
			else m[j]=0;
		}
		if(i==3)
		{
			c++;
		}
		if(i==4)
		{
			cin>>j;
			if(m[j]==0)m2[j]=c;
			if(m2[j]<c)cout<<1<<endl;
			else cout<<m[j]<<endl;
		}
	}
}
```

---

## 作者：__zyq_666_kpzc__ (赞：2)

### 思路分析
这题我们可以用一个有序键值对 $mp$ 解决。
- 操作一：$mp_x$ 的数量增加 $y$。
- 操作二：$mp_x$ 的数量减少 $y$。
- 操作三：再来一个有序键值对 $mp2$，$mp2_i$ 表示第 $i$ 个数是否去重，跟线段树中的懒标记差不多。之后若进行到操作 $1$，操作 $2$ 和操作 $4$ 时，再将对应要询问的值去重。
- 操作四：输出 $mp_x$ 即可。

---

## 作者：a18981826590 (赞：1)

# [P11139 [APC001] D - Array Again](https://www.luogu.com.cn/problem/P11139)
## 题意简述
对一些数进行插入、删除、去重操作，在线查询数的个数。
## 赛时做法
看到数据范围 $1 \le x \le 10^{9}$，想到用 `unordered_map`，但操作 $3$ 的复杂度达到了 $O(n)$，你会因[ `TLE` 一个测试点而失去 $400$ 分](https://www.luogu.com.cn/record/179356721)。
## 暴力碾压标算
用两个数组，一个记录值，另一个记录个数，每次操作都遍历一遍进行数值匹配，按照题意模拟即可。
## [AC](https://www.luogu.com.cn/record/179432764) 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],c,d,q,x,y;
long long int b[100010];
int main(){
	ios::sync_with_stdio(0);
	cin>>q;
	while(q--){
		cin>>x;
		if(x==1){
			cin>>x>>y;
			d=0;
			while(d<c){
				if(a[d]==x){
					b[d]+=y;
					break;
				}
				d++;
			}
			if(d==c){
				a[c]=x;
				b[c]=y;
				c++;
			}
		}
		else if(x==2){
			cin>>x>>y;
			d=0;			
			while(d<c){
				if(a[d]==x){
					if(b[d]<=y) b[d]=0;
					else b[d]-=y;
					break;
				}
				d++;
			}
		}
		else if(x==3){
			d=0;
			while(d<c){
				b[d]=bool(b[d]);
				d++;
			}
		}
		else{
			cin>>x;
			d=0;
			while(d<c){
				if(a[d]==x){
					cout<<b[d]<<'\n';
					break;
				}
				d++;
			}
			if(d==c) cout<<"0\n";
		}
	}
	return 0;
}
```

---

## 作者：Zhl2010 (赞：0)

## 思路

首先看到题目，直接打了个 `map` 上去，但是却 `TLE` 了。

这是记录：[记录](https://www.luogu.com.cn/record/179310549)。

### 错误代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000010],cnt=0;
map<int,int>mp;
signed main(){
	int q;
	cin>>q;
	while(q--){
		int t;
		cin>>t;
		int x,y;
		if(t==1){
			scanf("%d%d",&x,&y);
			if(!mp[x])a[++cnt]=x;
			mp[x]+=y;
		}if(t==2){
			scanf("%d%d",&x,&y);
			mp[x]=max(mp[x]-y,0ll);
		}if(t==3){
			for(int i=1;i<=cnt;i++){
				if(mp[a[i]])mp[a[i]]=1;
			}
		}if(t==4){
			scanf("%d",&x);
			cout<<mp[x]<<endl;
		}
	}
	return 0;
}
```

这种方法只有一个操作是要循环 $n$ 次的，为什么不对？

后来想了想，`map` 每次访问要用的时间比数组多，所以理所当然 `TLE`。

所以千万不要在这种题上用 `map`，血的教训！！！

所以正解是什么？

不是高深的算法，而是暴力。定义一个 $b$ 数组，存每一个出现过的数，而 $a$ 数组表示 $b$ 数组对应的数的个数，也就是 $b_i$ 表示第 $i$ 个数是 $b_i$，有 $a_i$ 个。

然后根据题意，暴力修改数组和查询答案。

这样，我们就水掉了黄题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000010],cnt=0;
int b[1000010];
signed main(){
	int q;
	cin>>q;
	while(q--){
		int t;
		cin>>t;
		int x,y;
		if(t==1){
			scanf("%d%d",&x,&y);
			int pd=0;
			for(int i=1;i<=cnt;i++){
				if(b[i]==x){
					a[i]+=y;
					pd=1;
					break;
				}
			}
			if(!pd){
				b[++cnt]=x;
				a[cnt]=y; 
			} 
		}if(t==2){
			scanf("%d%d",&x,&y);
			for(int i=1;i<=cnt;i++){
				if(b[i]==x){
					a[i]=max(a[i]-y,0ll);
					break;
				}
			}
		}if(t==3){
			for(int i=1;i<=cnt;i++){
				a[i]=min(1ll,a[i]);
			}
		}if(t==4){
			scanf("%d",&x);
			int pd=0;
			for(int i=1;i<=cnt;i++){
				if(b[i]==x){
					pd=1;
					cout<<a[i]<<endl;
					break;
				}
			}
			if(!pd)cout<<0<<endl;
		}
	}
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

注意到比较棘手的是去重操作。如果没有去重，我们完全可以直接用映射表解决。既然有这个操作，考虑用线段树。

（虽然线段树有点大材小用了，毕竟大多数是单点操作。）

此处其实只需要用到单点的信息，因此线段树存储区间的什么信息都可以。这里我存储了区间最大值。

首先将操作离线，把所有的 $x$ 都离散化，方便值域操作。

对于操作 $1$，即将 $x$ 单点加 $y$。

对于操作 $2$，即将 $x$ 单点减 $y$，与 $0$ 取最大值。

对于操作 $3$，开一个标记数组，将代表整个序列的节点标记设为 $1$。传标记时，把传到的区间信息变为 $0$ 与标记取最小值，然后清空上一层标记。

对于操作 $4$，即输出 $x$ 单点的信息。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,op[1000005],x[1000005],y[1000005];
map<int,int> ma;
int f[4000005],flag[4000005];
void pushdown(int root){
	if(!flag[root]) return;
	f[root<<1]=min(f[root<<1],flag[root]),flag[root<<1]=flag[root];
	f[root<<1|1]=min(f[root<<1|1],flag[root]),flag[root<<1|1]=flag[root];
	flag[root]=0;
}
void update(int root,int l,int r,int k,int x){
	if(l==r){ f[root]=max(0ll,f[root]+x);return; }
	int mid=(l+r)>>1;
	pushdown(root);
	if(k<=mid) update(root<<1,l,mid,k,x);
	else update(root<<1|1,mid+1,r,k,x);
	f[root]=max(f[root<<1],f[root<<1|1]);
}
int Find(int root,int l,int r,int k){
	if(l==r) return f[root];
	int mid=(l+r)>>1;
	pushdown(root);
	if(k<=mid) return Find(root<<1,l,mid,k);
	else return Find(root<<1|1,mid+1,r,k);
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&op[i]);
		if(op[i]==1) scanf("%lld %lld",&x[i],&y[i]);
		if(op[i]==2) scanf("%lld %lld",&x[i],&y[i]);
		if(op[i]==4) scanf("%lld",&x[i]);
	}
	for(int i=1;i<=n;i++) if(x[i]) ma[x[i]]=1;
	int j=0;
	for(map<int,int>::iterator i=ma.begin();i!=ma.end();i++)
		ma[i->first]=++j;
	for(int i=1;i<=n;i++) x[i]=ma[x[i]];
	for(int i=1;i<=n;i++){
		if(op[i]==1) update(1,1,n,x[i],y[i]);
		if(op[i]==2) update(1,1,n,x[i],-y[i]);
		if(op[i]==3) flag[1]=1;
		if(op[i]==4) printf("%lld\n",Find(1,1,n,x[i]));
	}
	return 0;
}
```

---

## 作者：xiaoyang111 (赞：0)

### 思路

考虑记录每一次覆盖的时间，然后在每一个操作前更新一下再回答。

操作一就是先更新一下，然后加一下。

操作二也先更新，然后减一下，如果没有就不用管，要考虑减完的情况，和零取个最大值就可以了。

操作三就把覆盖的时间改一下。

操作四就是先更新，再回答一下。

更新还算简单吧，再记一下这个数上次啥时候更新的，如果更新的时间比覆盖的时间晚，就不用管。这个数原来就没有也不管。否则就要管，变成一就行了。

### 实现

除去 STL 的巨大常数，时间复杂度 $O(q)$。

```cpp
#include <iostream>
#include <unordered_map>
#define int long long
using namespace std;
const int N=1e5+5;
unordered_map<int,int> m;//这个数对应的编号
int t[N],c[N],g=-1,x,y;
void upd(int x,int i){//更新关于去重
	if (!m.count(x)) return;
	int u=m[x];
	if (c[u]==0){t[u]=i;return;}//已经被删完了
	if (t[u]>g) return;//已经是最新的
	if (t[u]!=-1) c[u]=1;
	t[u]=i;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int q;
	cin >> q;  
	for (int i=0;i<N;++i) t[i]=-1;
	for (int i=0,op,cnt=0;i<q;++i){
		cin >> op;
		if (op==1){
			cin >> x >> y;
			if (!m.count(x)) m[x]=++cnt;//新建
			upd(x,i);
			c[m[x]]+=y;
		}else if (op==2){
			cin >> x >> y;
			if (!m.count(x)) continue;
			upd(x,i);
			c[m[x]]=max(c[m[x]]-y,0ll);
		}else if (op==3){
			g=i;
		}else{
			cin >> x;
			if (!m.count(x)){
				cout<<0<<"\n";
				continue;
			}
			upd(x,i);
			cout<<c[m[x]]<<"\n";
		}
	}
	cout.flush();
	return 0;
}
```

---

## 作者：2022linzhiyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11139)

~~又是学数据结构学傻的一天。~~

由于习惯，后面的 $q$ 均用 $n$ 代替。

这题要求四个操作，分别是：单点插入、单点删除、全体去重、单点查询。

首先，因为 $1 \le x,y \le 10^9$，所以我们可以利用 map 进行离散化。因此对于操作一、二、四我们都可以 $O(1)$ 维护，但是操作三就不行了，因此想到线段树，只需要在根节点放一个懒标记，查询和修改的时候下传即可。

这样操作一、二、四的复杂度变为 $O(\log{n})$，操作三的复杂度变为 $O(1)$，总时间复杂度为 $O(n\log^2{n})$，可以通过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node {
	int l,r;
	long long cnt;
	bool tag;
}tr[N<<2];
int q,cnt;
map<int,int> mp;
void f(int u) {
	tr[u].cnt=min(tr[u].cnt,1ll);
	tr[u].tag=1;
}
void pushdown(int u) {
	if (tr[u].tag) {
		f(u<<1), f(u<<1|1);
		tr[u].tag=0;
	}
}
void build(int u,int l,int r) {
	tr[u]={l,r,0,0};
	if (l == r) return;
	int mid=l+r>>1;
	build(u<<1,l,mid), build(u<<1|1,mid+1,r);
}
void modify(int u,int x,int k) {
	if (tr[u].l == tr[u].r) {
		tr[u].cnt += (long long)k;
		if (tr[u].cnt < 0) tr[u].cnt=0;
	} else {
		pushdown(u);
		if (tr[u<<1].r >= x) modify(u<<1,x,k);
		if (tr[u<<1|1].l <= x) modify(u<<1|1,x,k);
	}
}
long long query(int u,int x) {
	if (tr[u].l == tr[u].r) return tr[u].cnt;
	pushdown(u);
	if (tr[u<<1].r >= x) return query(u<<1,x);
	return query(u<<1|1,x);
}
int get(int x) {
	if (!mp[x]) mp[x]=++cnt;
	return mp[x];
}
signed main()
{
	cin >> q;
	build(1,1,q);
	while (q --) {
		int opt,x,y;
		cin >> opt;
		if (opt == 1) cin >> x >> y, x=get(x), modify(1,x,y);
		if (opt == 2) cin >> x >> y, x=get(x), modify(1,x,-y);
		if (opt == 3) pushdown(1), tr[1].tag=1;
		if (opt == 4) cin >> x, x=get(x), cout << query(1,x) << endl;
	}
	return 0;
}

```

---

## 作者：OrzSceamyn (赞：0)

### [APC001] D - Array Again 题解

#### 思路

**STL 大法好。**


看到要查询次数，值域在 $10^9$，显然先考虑 `map`，如果没有 $3$ 操作就非常好做了。

那么考虑 $3$ 操作怎么做，因为 $q$ 只有 $10^5$，所以 `map` 里存的数字最多只有 $10^5$ 个，只需要在 $1$ 操作加数字的时候用一个 `vector` 存当前数列中有的数字，对于每次 $3$ 操作，直接暴力遍历整个 `vector`，将所有数字的次数都变为 $1$，然后把 `vector` 清空，设操作 $1$ 的数量为 $x$ 个，这样做的时间复杂度 $q$ 次询问一共是 $O(x)$ 的。

代码就非常好写了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T=1;
map<int,int> mp;
int q;
vector<int> ve;
void solve(){
	cin>>q;
	while(q--){
		int op,x,y;
		cin>>op;
		if(op==1){
			cin>>x>>y;
			mp[x]+=y;
			if(mp[x]>0) ve.push_back(x);
		}
		if(op==2){
			cin>>x>>y;
			if(mp[x]>=y) mp[x]-=y;
			else mp[x]=0;
		}
		if(op==3){
			for(int a:ve){
				if(mp[a]>0){
					mp[a]=1;
				}
			}
		}
		if(op==4){
			cin>>x;
			cout<<mp[x]<<'\n';
		}
	}
}

int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
//	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}

```

---

## 作者：Redshift_Shine (赞：0)

这道题的套路在 AtCoder 出现过。

首先，除操作 $3$ 之外的操作都可以十分简单地使用 `map` 进行维护。考虑如何处理操作 $3$。

若使用 `map` 直接进行操作 $3$，时间复杂度将会为 $O(|\text{set}(a)|)$。这显然是不可接受的，考虑优化。

类似于线段树的懒标记，我们可以在这个数组上同样维护一个懒标记。具体的，设置一个初始为 $0$ 的时间戳，以及另一个 `map`，维护每种元素最后一次非 $3$ 操作时所在的时间戳。

若进行操作 $3$，则使时间戳加 $1$；否则，检查该元素的时间戳是否与目前时间戳对应，若不是，则进行去重操作。

时间复杂度视使用容器为 $O(q)$ 或 $O(q\log q)$。

```c++
#include <cstdio>
#include <map>
using namespace std;
const int N = 1e5 + 10;
using ll = long long;
map<int, ll> mp, mpcl;
int n, idx;
int main()
{
	scanf("%d", &n);
	for (int i = 1, x, y, z; i <= n; i++)
	{
		scanf("%d", &x);
		if (x == 3)
		{
			idx++;
			continue;
		}
		scanf("%d", &y);
		if (mpcl[y] != idx)
		{
			mp[y] = min(1ll, mp[y]);
			mpcl[y] = idx;
		}
		if (x == 4)
		{
			printf("%lld\n", mp[y]);
			continue;
		}
		scanf("%d", &z);
		if (x == 1)
		{
			mp[y] += z;
			continue;
		}
		mp[y] = max(mp[y] - z, 0ll);
	}
}
```

---

