# [ABC203E] White Pawn

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc203/tasks/abc203_e

$ N $ を正の整数とします。 行と列にそれぞれ $ 0 $ から $ 2N $ までの番号が付いた $ (2N+1)\times\ (2N+1) $ のマス目があり、行 $ i $ かつ列 $ j $ に属するマスを $ (i,j) $ で表します。

白のポーンが $ 1 $ つあり、最初 $ (0,N) $ に置かれています。 黒のポーンは $ M $ 個あり、$ i $ 個目の黒のポーンは $ (X_i,\ Y_i) $ に置かれています。

白のポーンが $ (i,j) $ にあるとき、あなたは以下のいずれかの操作で白のポーンを動かすことができます。

- $ 0\leq\ i\leq\ 2N-1 $, $ 0\ \leq\ j\leq\ 2N $ を満たし、$ (i+1,j) $ に黒のポーンが**無い**ならば、白のポーンを $ (i+1,j) $ に動かす。
- $ 0\leq\ i\leq\ 2N-1 $, $ 0\ \leq\ j\leq\ 2N-1 $ を満たし、$ (i+1,j+1) $ に黒のポーンが**有る**ならば、白のポーンを $ (i+1,j+1) $ に動かす。
- $ 0\leq\ i\leq\ 2N-1 $, $ 1\ \leq\ j\leq\ 2N $ を満たし、$ (i+1,j-1) $ に黒のポーンが**有る**ならば、白のポーンを $ (i+1,j-1) $ に動かす。

黒のポーンは動かすことができません。

この操作を繰り返した結果、$ (2N,Y) $ に白のポーンが置かれている状態にできるような $ Y $ の値としてあり得るものの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^9 $
- $ 0\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ X_i\ \leq\ 2N $
- $ 0\ \leq\ Y_i\ \leq\ 2N $
- $ (X_i,\ Y_i)\ \neq\ (X_j,\ Y_j) $ $ (i\ \neq\ j) $
- 入力は全て整数である。

### Sample Explanation 1

$ (4,0) $, $ (4,1) $, $ (4,2) $ の $ 3 $ つへはそれぞれ次のように動かせます: - $ (0,2)\to\ (1,1)\to\ (2,1)\to\ (3,1)\to\ (4,2) $ - $ (0,2)\to\ (1,1)\to\ (2,1)\to\ (3,1)\to\ (4,1) $ - $ (0,2)\to\ (1,1)\to\ (2,0)\to\ (3,0)\to\ (4,0) $ 一方、 $ (4,3) $ と $ (4,4) $ へは動かすことができません。 よって、 $ 3 $ を出力します。

### Sample Explanation 2

白のポーンを $ (0,1) $ から動かすことはできません。

## 样例 #1

### 输入

```
2 4
1 1
1 2
2 0
4 2```

### 输出

```
3```

## 样例 #2

### 输入

```
1 1
1 1```

### 输出

```
0```

# 题解

## 作者：jokersen (赞：7)

## 主要思路是离散化。

观察可知，只有该行有黑棋时才会使答案变化，所以空白的行都是无意义的，可以舍去。

### 输入：

```
scanf("%d%d",&n,&m);
for(int i=1;i<=m;i++) scanf("%d%d",&arr[i].first,&arr[i].second);//使用结构体,方便排序
```

### 排序：

```
bool cmp(pair<int,int>x,pair<int,int>y){return x.first!=y.first?x.first<y.first:x.second<y.second;}
sort(arr+1,arr+m+1,cmp);//按行从小到大排,若行相同则按列从小到大排
```

### 离散化：

```
//vis1表示该行在离散化后是第几行
for(int i=1;i<=m;i++){
	int t=arr[i].first,s=arr[i].second;
	if(vis1[t]) b[vis1[t]].push_back(s);//若记录过该行则存入记录的位置
	else vis1[t]=++cnt,b[cnt].push_back(s);//否则新开一位,存入
}
```

统计答案时只需用 map 记录哪些可以到达，以及 $ans$（初始值为 $1$）记录数量即可。

注意改变可到达的在下一行才生效，需要开个待操作序列，统计好该行后再操作。

### 统计答案：

```
vis2[n]=true;//开始时n可到达
for(int i=1;i<=cnt;i++){
	wait.clear();//清理待操作序列
	for(auto v:b[i]){//遍历该行的黑棋
		bool t=false;//默认该列不可到达
		if(vis2[v]) wait.push_back({v,false}),ans--;//挡住白棋下移,改为不可到达,数量-1
		if(v>0) t|=vis2[v-1];//若左边没超边界
		if(v<n*2) t|=vis2[v+1];//若右边没超边界
		if(t) wait.push_back({v,true}),ans++;//可以从左右过来,改为可以到达,数量+1
	}
	for(auto p:wait) vis2[p.first]=p.second;//执行待操作序列中的操作
}
```

## Code：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,ans=1;
vector<int>b[200005];
vector<pair<int,bool> >wait;
map<int,int>vis1;
map<int,bool>vis2;
pair<int,int>arr[200005];
bool cmp(pair<int,int>x,pair<int,int>y){return x.first!=y.first?x.first<y.first:x.second<y.second;}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&arr[i].first,&arr[i].second);
	sort(arr+1,arr+m+1,cmp);
	for(int i=1;i<=m;i++){
		int t=arr[i].first,s=arr[i].second;
		if(vis1[t]) b[vis1[t]].push_back(s);
		else vis1[t]=++cnt,b[cnt].push_back(s);
	}
	vis2[n]=true;
	for(int i=1;i<=cnt;i++){
		wait.clear();
		for(auto v:b[i]){
			bool t=false;
			if(vis2[v]) wait.push_back({v,false}),ans--;
			if(v>0) t|=vis2[v-1];
			if(v<n*2) t|=vis2[v+1];
			if(t) wait.push_back({v,true}),ans++;
		}
		for(auto p:wait) vis2[p.first]=p.second;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Louis_lxy (赞：5)

## 前言

其实个人觉得这题根本没有绿题的难度，就是一堆技巧优化模拟而已啊。

## 思路

用个 map 储存各层的黑子，然后用个 set 储存当前层能到达的位置，然后直接暴力转移到下一层即可，记得不能立马处理删除和添加，要到处理完整层再处理。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, m;
	map<int, vector<int>> a;
	scanf("%d %d", &n, &m);
	for (int i = 1, x, y; i <= m; ++i)
	{
		scanf("%d %d", &x, &y);
		a[x].push_back(y);
	}
	set<int> can;
	can.insert(n);
	for (auto i : a)
	{
		vector<int> pop, push;
		for (int j : i.second)
			if (can.count(j))
				pop.push_back(j);
		for (int j : i.second)
			if (can.count(j - 1) || can.count(j + 1))
				push.push_back(j);
		for (int j : pop) can.erase(j);
		for (int j : push) can.insert(j);
	}
	printf("%d", can.size());
	return 0;
}
```

---

## 作者：kanglr1013 (赞：3)

随机跳题跳到的。  
## 题目大意  
有一个 $(2n + 1) \times (2n + 1)$ 的棋盘，有一个白棋在 $(0, n)$。  
当白棋在 $(i, j)$ 时你可以进行以下操作：  

1. 如果 $(i + 1, j)$ **没有**黑棋，你可以走到那。  
2. 如果 $(i + 1, j - 1)$ **有**黑棋，你可以走到那。  
2. 如果 $(i + 1, j + 1)$ **有**黑棋，你可以走到那。  

求到 $(2n + 1)$ 行时能够到达多少个点。  

$1 \le n \le 10^9,0 \le m \le 2 \times 10^5$ 
## 思路  
观察到 $1 \le n \le 10^9$，直接模拟肯定是不行的。  

根据题目，白棋所能够到达的位置只与黑棋有关联。  
如果一行没有任何一个黑棋，那么它的状态只能由上一行继承过来，即只能进行操作 1。  

黑棋至多有 $2 \times 10^5$ 个，故可以考虑只枚举每一个黑棋的位置。  
具体地，我们从小到大枚举每一行每一个黑棋的位置，然后按照题目中给定的操作进行分类讨论即可。  

在实现上，可以离散化或者使用 `map` 套 `vector` 存储每一行黑棋的位置，用 `set` 统计答案即可。  
最后 `set` 的大小即为答案，时间复杂度 $\mathcal{O}(m \log m)$。  

## 代码  
[My Submission](https://atcoder.jp/contests/abc203/submissions/61349975)

---

## 作者：Pyrf_uqcat (赞：2)

题意：题意简洁明了，不多说了。

注意 $n\le10^9$，不可直接模拟。但是黑棋却不超过 $2\times10^5$ 个，因为 $x$ 和 $y$ 较大，所以用 map 存储黑棋信息。注意每层都有很多黑棋，用 set 套 vector 存储。

再用 set 存每层能到达哪些格子，暴力转移即可。


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include <bits/stdc++.h>
#define int long long 

using namespace std;

int n,m;

map<int,vector<int>> mp;

set<int> s;

signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y;cin>>x>>y;
		mp[x].push_back(y);
	}
	s.insert(n);
	for(auto i:mp)
	{
		vector<int> era,ins;
		for(int j:i.second)
		{
			if(s.count(j)) era.push_back(j);
			if(s.count(j-1)||s.count(j+1)) ins.push_back(j);
		}
		for(int j:era) s.erase(j);
		for(int j:ins) s.insert(j);
	}
	int ans=s.size();
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：theb0t (赞：2)

由于 $m \le 2 \times 10^{5}$，所以可以把有黑格子的行扔到一个 map 里面，然后再用一个 set 存储当前能走到哪些格子。按照题意暴力转移，开两个 vector in 和 out，分别存储哪些格子要删掉，哪些格子要加入。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	map<int,vector<int>> Map;
	set<int> Set;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Map[x].push_back(y);
	}
	Set.insert(n);
	for(auto i:Map)
	{
		vector<int> in,out;
		for(int j:i.second)
		{
			if(Set.count(j)) out.push_back(j);
			if(Set.count(j-1)||Set.count(j+1)) in.push_back(j);
		}
		for(int j:out) Set.erase(j);
		for(int j:in) Set.insert(j);
	}
	printf("%d",Set.size());
	return 0;
}
```

---

## 作者：Kawaii_qiuw (赞：1)

### 题意
有一个 $(2N+1)\times(2N+1)$ 的正方形棋盘，行数、列数下标都依次从 $0$ 到 $2N$。我们用 $(i,j)$ 表示棋盘上 $i$ 行 $j$ 列的位置。

我们有一颗棋子，初始位置在 $(0,N)$。棋盘上有 $M$ 个黑方格，第 $i$ 个的位置在 $(X_i,Y_i)$，其余都是白方格。

当棋子在 $(i,j)$ 时，你可以执行任意下列操作，但不能移出棋盘：

- $(i+1,j)$ 是白色时，移到 $(i+1,j)$；
- $(i+1,j-1)$ 是黑色时，移到 $(i+1,j-1)$。
- $(i+1,j+1)$ 是黑色时，移到 $(i+1,j+1)$。

棋盘上的方格不能移动。求棋盘的最后一行的能到达的列的个数。

### 思路

我们发现，当 $N$ 较大时，大多数行多是空着的，所以我们从每个 $X_i$ 开始考虑。对于白色的位置 $(i,j)$，如果不能到达 $(i-1,j)$，则不能到达 $(i,j)$。相反，对于黑色的 $(i,j)$，如果能到达 $(i-1,j-1)$ 或 $(i-1,j+1)$，则能到达 $(i,j)$。

因此，我们先排序每个 $(X_i,Y_i)$，再对于每个有黑色的行，用 ```set``` 维护能到达的列数，再按上述方法判断即可。

### 代码


```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<pair<int, int> > black;
	black.reserve(m);
	while (m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		black.emplace_back(x, y);
	}
	m = black.size();
	sort(black.begin(), black.end());
	set<int> cols;
	cols.insert(n);
	for (int l=0, r=0; l<m; l=r) {
		while (r < m && black[r].first == black[l].first) r ++;
		vector<int> rem, add;
		for (int i=l; i<r; i++) {
			int y = black[i].second;
			bool ok = cols.count(y - 1) || cols.count(y + 1);
			if (cols.count(y)) {
				if (!ok)
					rem.push_back(y);
			}
			else if (ok)
				add.push_back(y);
		}
		for (int y: rem) cols.erase(y);
		for (int y: add) cols.insert(y);
	}
	printf("%llu\n", cols.size());
	return 0;
}
```

完结撒花。

---

## 作者：ICE__LX (赞：1)

### 具体思路
如果直接模拟肯定会炸，因为 $N$ 的范围很大，因此还需进行离散化。在此并不推荐用 map，因为它的常数较大，而且本题以查询为主，因此更加推荐使用去重二分或哈希表。  
思路与其他题解差不多，枚举每行的黑子，统计该行同列的黑子和左上或左下的黑子后再统一进行转移。如果在统计过程中就进行转移会影响后续的统计，因此需全部统计完后再进行状态转移，也就是完成该行的删添。  
### 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define deap(i,a,b) for(int i=a;i>=b;i--)
#define in(a) a=read()
const int N = 2e5+5;
const int inf = INT_MAX;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
void fast() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int n,m;
int a[N],b[N],c[N],top1,top2;
vector<int>sum[N];
set<int>s;//还是被迫用了红黑树           
signed main() {
	//fast();
	in(n),in(m);
	rep(i,1,m)in(a[i]),in(b[i]); 
	rep(i,1,m)c[i]=a[i];
	sort(c+1,c+m+1);
	int tot=unique(c+1,c+m+1)-c;//离散化   
	tot--;
	rep(i,1,m)sum[lower_bound(c+1,c+tot+1,a[i])-c].push_back(b[i]);//处理数据 
	s.insert(n);//初始化 
	rep(i,1,tot) {//枚举每行的黑子 
		top1=top2=0;//清空统计数组 
		for(auto v:sum[i]) {//记录同列的黑子和左上或左下的黑子 
			if(s.find(v)!=s.end())a[++top1]=v;//不浪费一点空间！ 
			if(s.find(v+1)!=s.end()||s.find(v-1)!=s.end())b[++top2]=v;
		}  
		rep(j,1,top1)s.erase(a[j]);//删添 
		rep(j,1,top2)s.insert(b[j]);
	}
	cout<<s.size();
	return 0;
}
```

---

## 作者：gdz0214_and_zxb0214 (赞：0)

## 分析
### 输入与存坐标
发现 $n$ 的范围极大，而 $m$ 则有说法。

由于 $m$ 与黑棋相关，容易想到存黑棋棋子坐标，虽然样例中 $x$ 有序，但题目中并没有规定这点，所以可以用映射表与动态数组来存黑棋棋子的坐标,以下为输入部分的代码。
```cpp
int n,m,x,y;
map<int,vector<int> > s; 
scanf("%d%d",&n,&m);
for(int i=1;i<=m;i++){
  scanf("%d%d",&x,&y);
  s[x].push_back(y);
}
```
### 处理
研究一下样例，发现样例中没有黑棋棋子的第三行能到达的点与第二行相等，推敲一下得出若一行没有黑棋棋子则继承上一行，否则我们可以用一个集合来存储上一行能到达的点，随后遍历当前行的黑棋棋子，判断每个黑棋棋子的上方是否有白棋棋子，若有，则删除此点，再判断每个黑棋棋子左上和右上方是否有白点，若有，则保留此点。以下为代码。
```cpp
set<int> now;
now.insert(n);
for(auto i:s){//i当前为pair<int,vector<int> > 
  vector<int> erase,insert;
  for(auto j:i.second){//j当前为 vector<int> 中的 int,为第 i.first 行中黑点的 y 坐标 
    if(now.count(j)){
      erase.push_back(j);
    }
    if(now.count(j-1)||now.count(j+1)){
      insert.push_back(j);
    }
  }
  for(auto j:erase){
    now.erase(j);
  }
  for(auto j:insert){
    now.insert(j);
  }
}
```
### 输出部分代码
```cpp
printf("%d",now.size());
```
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,x,y;
	map<int,vector<int> > s; 
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		s[x].push_back(y);
	}
	set<int> now;
	now.insert(n);
	for(auto i:s){//i当前为pair<int,vector<int> > 
		vector<int> erase,insert;
		for(auto j:i.second){//j当前为 vector<int> 中的 int,为第 i.first 行中黑点的 y 坐标 
			if(now.count(j)){
				erase.push_back(j);
			}
			if(now.count(j-1)||now.count(j+1)){
				insert.push_back(j);
			}
		}
		for(auto j:erase){
			now.erase(j);
		}
		for(auto j:insert){
			now.insert(j);
		}
	}
	printf("%d",now.size());
	return 0;
}
```
[提交记录](https://www.luogu.com.cn/record/206868632)

---

## 作者：Empty_Dream (赞：0)

## ABC203E 解题报告

### 分析

比较简单的一题。

对于暴力，很明显对于每一行每一个点判断是否能往下面转移，但是复杂度会炸。

但是我们发现黑点很少，而且白点的转移与黑点相关，我们就可以考虑只遍历每一个黑点，分两种情况讨论：

- 如果这个黑点的正上方有白点能到，那么上面那个白点会被阻拦。
- 如果左上或者右上有白点能到，那么就能转移到这个黑点上。

之后拿 `map` 套 `vector` 维护每一行黑点信息，`set` 表示初始点能到达的点的横坐标，然后对于每一行都进行上面的操作，最后答案就是 `set` 的大小。

注意：记得先记录下来两种情况的对应黑点的横坐标，再转移。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

int n, m;
int x[N], y[N];
map<int, vector<int>> mp;
set<int> st;

signed main(){
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> x[i] >> y[i], mp[x[i]].push_back(y[i]);//维护每一行的信息
	st.insert(n);//第一个点肯定能到
	for (auto it : mp){
		vector<int> v1, v2;
		for (int i = 0; i < it.second.size(); i++){
			if (st.count(it.second[i])) v1.push_back(it.second[i]);//会被阻拦的
		}
		for (int i = 0; i < it.second.size(); i++){
			if (st.count(it.second[i] - 1) || st.count(it.second[i] + 1)) v2.push_back(it.second[i]);//能转移过来的
		}
		for (int i = 0; i < v1.size(); i++) st.erase(v1[i]);
		for (int i = 0; i < v2.size(); i++) st.insert(v2[i]);//更新set
	}
	cout << st.size();
	return 0;
}
```

---

## 作者：panyanppyy (赞：0)

校内 VP，赛时没看题，赛后发现是 EZ 题。

## Problem

一个 $(2n+1)\times(2n+1)$ 的棋盘上有 $m$ 个黑棋，你有一个白棋在 $(0,n)$。白棋在 $(i,j)$，每次可以对白棋进行一下操作：

1. 如果 $(i+1,j)$ **没有**黑棋，可以走到那。

2. 如果 $(i+1,j-1)$ **有**黑棋，可以走到那。
3. 如果 $(i+1,j+1)$ **有**黑棋，可以走到那。

问到 $2n+1$ 行时能走到多少个点。

$1\le n \le 10^9,0\le m\le 2\times10^5,0\le X_i,Y_i\le 2n$
## Solution

发现最后的答案对多只有 $n$。只有有黑色点的行有用，所以只要对每一个有用的行转移。可以直接用一个可以删数和加数的数据结构。

可以用 `set` 做到 $\mathcal O(m\log m)$ 的时间复杂度。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
#define se second
using namespace std;
template<typename T_>void operator+=(vector<T_>&x,const T_&y){x.push_back(y);}
template<typename T_>void operator+=(set<T_>&x,const T_&y){x.insert(y);}
template<typename T_>void operator-=(set<T_>&x,const T_&y){x.erase(y);}
map<int,vector<int>>a;
set<int>s;
int n,m;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++)cin>>x>>y,a[x]+=y;
	s+=n;
	for(auto&i:a){
		vector<int>A,B;
		for(int j:i.se)
			if(s.count(j))A+=j;
		for(int j:i.se)
			if(s.count(j-1)||s.count(j+1))B+=j;
		for(int j:A)s-=j;
		for(int j:B)s+=j;
	}
	cout<<s.size()<<'\n';
	return 0;
}

```

---

