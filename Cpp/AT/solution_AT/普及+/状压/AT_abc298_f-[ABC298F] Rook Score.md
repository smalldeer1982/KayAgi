# [ABC298F] Rook Score

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc298/tasks/abc298_f

縦 $ 10^9 $ マス、横 $ 10^9 $ マスのマス目があります。上から $ i $ 番目、左から $ j $ 番目のマスを $ (i,j) $ と表記します。

$ i=1,2,\ldots,N $ に対し $ (r_i,c_i) $ には正整数 $ x_i $ が、他の $ 10^{18}-N $ 個のマスには $ 0 $ が書かれています。

あなたはあるマス $ (R,C) $ を選び、 $ (R,C) $ と行または列が同じ $ 2\ \times\ 10^9\ -\ 1 $ 個のマスに書かれた整数の総和 $ S $ を求めました。

$ S $ として考えられる最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ r_i,c_i,x_i\ \leq\ 10^9 $
- $ i\ \neq\ j $ ならば $ (r_i,c_i)\ \neq\ (r_j,c_j) $
- 入力はすべて整数

### Sample Explanation 1

$ (R,C) $ として $ (2,2) $ を選ぶと $ S $ が $ 20 $ となります。これが最大値です。

## 样例 #1

### 输入

```
4
1 1 2
1 2 9
2 1 8
3 2 3```

### 输出

```
20```

## 样例 #2

### 输入

```
1
1 1000000000 1```

### 输出

```
1```

## 样例 #3

### 输入

```
15
158260522 877914575 602436426
24979445 861648772 623690081
433933447 476190629 262703497
211047202 971407775 628894325
731963982 822804784 450968417
430302156 982631932 161735902
880895728 923078537 707723857
189330739 910286918 802329211
404539679 303238506 317063340
492686568 773361868 125660016
650287940 839296263 462224593
492601449 384836991 191890310
576823355 782177068 404011431
818008580 954291757 160449218
155374934 840594328 164163676```

### 输出

```
1510053068```

# 题解

## 作者：2huk (赞：7)

## 题目描述

有一个 $10^9 \times 10^9$ 的网格。$(r_i, c_i)$ 的位置上写着 $x_i$，其余位置为 $0$。

找到一个点 $(x, y)$，使得 $x$ 行的数字与 $y$ 行的数字之和最大（重复计算的要只算一次）。求出最大值。

## 样例输入输出

```input1
4
1 1 2
1 2 9
2 1 8
3 2 3
```

```output1
20
```

![p9k1t4f.png](https://s1.ax1x.com/2023/04/20/p9k1t4f.png)

## 数据范围

$1 \le N \le 2 \times 10^5,\ 1 \le r_i,c_i,x_i \le 10^9$

## 前置 - [STL](https://oi-wiki.org/lang/csl/container/)

[`pair<int, int>`](https://oi-wiki.org/lang/csl/pair/) : 将两个变量关联在一起，组成一个对，这两个变量的类型都是 `int`。由于 `pair<int, int>` 过长，我们通常用加上一条语句`typedef pair<int, int> PII;` 用 `PII` 代替掉上面的 `pair<int, int>`。

[`map<PII, int>`](https://oi-wiki.org/lang/csl/associative-container/#map) : 有序键值对容器，它的元素的键是唯一的。前面的 `PII` 是我们规定的键类型，后面的 `int` 是我们规定的值类型。

[`unordered_map<int, int>`](https://oi-wiki.org/lang/csl/unordered-container/) : 与 `map` 类似，无序键值对容器，它的元素的键是唯一的。前面的 `int` 是我们规定的键类型，后面的 `int` 是我们规定的值类型。

[`vector<PII>`](https://oi-wiki.org/lang/csl/sequence-container/#vector) : ​内存连续的、可变长度数组，数组中的元素类型为 `int`。

## 分析

介绍完本题需要用到的 `STL` 容器后，我们开始分析这道题目。

本题的值域巨大，但元素数量不多，因此我们要想一种方法把数据存储起来，

完成后，就要考虑贪心策略，寻找最优解。

以下分为两个部分叙述。

## 存储数据

看到这个数据范围，我们可以将数据离散化。但那样略显复杂，这里使用 `STL` 容器进行处理数据。

`unordered_map` 的内部原理是使用哈希表存储数据，因此它可以存储几乎所有数据类型（几乎的原因下面有提到）。题目中要求每一行或每一列的数字和，所以可以用 `unordered_map` 存储每一行和每一列的权值和。

我们还需要存储下每一个点的权值，但是如果开二维数组肯定是不可以的，因此考虑使用容器 `map`。

为什么不能使用 `unordered_map` 呢？因为我们相当于是有 $3$ 个变量要存储，分别是横坐标，纵坐标和权值。而 `unordered_map` 不允许使用 `pair`，所以也就不能存储 $3$ 个变量，而 `map` 是可以的。

以上的存储都可以在输入时完成：

```cpp
unordered_map<int, int> R, C;
vector<PII> r, c; 
map<PII, int> mp;

cin >> n;

for (int i = 1; i <= n; i ++ )
{
	cin >> x >> y >> z;
	mp[{x, y}] = z;
	R[x] += z;
	C[y] += z;
}
```

由于要找最大值，我们会有一个意识就是需要把数据排序。但 `unordered_map` 是无法支持排序的，因此这里就用到了 `vector`。

我们可以把 `unordered_map` 中的所有数据再次存入 `vector` 中。由于 `unordered_map` 中的每一个值都有 `Key` 和 `T` 属性，也就是 `first` 和 `second`，所以 `vector` 的数据类型为 `pair<int, int>`，其中第一个值存储的是当前行的权值和，第二个值存储的是这一行的行数。

将元素搬到 `vector` 中后，就可以对其进行排序了。`pair<int, int>` 类型的 `sort` 排序是按照第一个值从小到大排序，所以排完序后还需要把数组翻转过来。

```cpp
for (auto e : R) r.push_back({e.second, e.first});
for (auto e : C) c.push_back({e.second, e.first});

sort(r.begin(), r.end());
sort(c.begin(), c.end());
reverse(r.begin(), r.end());
reverse(c.begin(), c.end());
```

## 贪心寻找最优解

上面的排序都是为了这一步的贪心做准备。

如果只找最大行和最大列，并把它们相加的话，是肯定不行的。例如下面这个例子。

![p9kNVMT.png](https://s1.ax1x.com/2023/04/20/p9kNVMT.png)

最大行是第 $2$ 行，最大列是第 $2$ 列，但是它们的和是 $11$，不如选 $(2, 1)$ 点的 $12$ 要优。所以这样的贪心策略是不行的。

由于求行和列的和的时候，需要减掉重复部分的数值，所以这个减掉的数值肯定是越小越好。

最小是多少呢？明显为 $0$，也就是不在这个格子上面写数字。所以我们又有了另一种贪心策略：先把行和列按数字和从大到小排序，如果令当前行为 $r$，当前列为 $c$，那么如果 $(r, c)$ 的值为 $0$，就可以直接更新答案并跳出循环，否则继续更新最大值。

贪心证明：

如果当前枚举的行为 $r$，当前列为 $c$，那么由于我们已经排过序，所以以后枚举的行 $r'$ 和列 $c'$ 的和一定是分别小于等于当前列的。也就是 $s_{r'} \le  s_r,\ s_{c'} \le s_c$。又由于 $(r, c)$ 的值为 $0$，所以本行和本列的总和为 $s_r + s_c$。而 $(r', c')$ 的值不一定为 $0$，若记这个数为 $x$，那么一定有 $x \ge 0$，所以 $r'$ 行和 $c'$ 列的总和为 $s_{r'} + s_{c'} - x$。很显然的是，$s_r + s_c \ge s_{r'} + s_{c'} - x$，所以可以停止枚举直接输出答案。

```cpp
for (auto _r : r)
	for (auto _c : c)
		if (mp.find({_r.second, _c.second}) == mp.end())
		{
			ans = max(ans, _r.first + _c.first);
			break;
		}
		else ans = max(ans, _r.first + _c.first - mp[{_r.second, _c.second}]);
```

## 完整代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;

#define int long long

typedef pair<int, int> PII;

int n, x, y, z, ans;

unordered_map<int, int> R, C;
vector<PII> r, c; 
map<PII, int> mp;

signed main()
{
	// 读入 
	cin >> n;
	
	for (int i = 1; i <= n; i ++ )
	{
		cin >> x >> y >> z;	
		mp[{x, y}] = z;		// map 存储 (x, y) 上的值 
		R[x] += z;			// R 存储当前行上的数字和 
		C[y] += z;			// C 存储当前列上的数字和 
	}
	
	// 将 unordered_map 中的元素搬到 vector 中，便于排序 
	for (auto e : R) r.push_back({e.second, e.first});
	for (auto e : C) c.push_back({e.second, e.first});
	
	// 从大到小排序 
	sort(r.begin(), r.end());
	sort(c.begin(), c.end());
	reverse(r.begin(), r.end());
	reverse(c.begin(), c.end());
	
	// 贪心 
	for (auto _r : r)		// 枚举行 
		for (auto _c : c)	// 枚举列 
			if (mp.find({_r.second, _c.second}) == mp.end())		// 如果 (_r, _c) 的值为 0，更新答案后直接跳出循环 
			{
				ans = max(ans, _r.first + _c.first);
				break;
			}
			else ans = max(ans, _r.first + _c.first - mp[{_r.second, _c.second}]);		// 否则更新答案 
	 
	cout << ans;		// 输出答案 
	
	return 0;
}
```


---

## 作者：ダ月 (赞：3)

### 题意概要：

在 $10^9\times10^9$ 平面上有 $n$ 个点有大于零的值，其余的点均为 $0$。现在你选择一个点，使得所在列的所有值的和，加上所在的行的所有值的和，减去当前点的值最大。求这个最大值。

### 题目分析：

我们先以每个有大于零的点的值为中心点，更新一遍答案。只有这一步显然是错的，连样例一都过不掉。

我们考虑一个值为 $0$ 的点，要求所在列的值的和不为零，并且若当前这一行所有的点所在的列不能算入答案。然后用所有满足以上条件的列的和的最大值加上这一行的所有值，去更新答案。

显然，我们需要一个数据结构，能够统计不重复的值，能够支持删除，插入，查询最大值的操作。stl 的库提供了 `multiset` 容器可以完成这些操作。当然，平衡树，值域线段树应该也能完成这些操作。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
#define pd(x) push_back(x)
#define First(x) (*x.begin())
#define Avail(x,y) (x.find(y)==x.end())
//===
//部分缺省源
//===
int n;
struct node{ll x,y,z;}a[N];
map<ll,ll> mp[2];
map<ll,vector<ll> >v;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].z;
		mp[0][a[i].x]+=a[i].z;
		mp[1][a[i].y]+=a[i].z;
		v[a[i].x].pd(a[i].y);
	}ll ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,mp[0][a[i].x]+mp[1][a[i].y]-a[i].z);
	multiset<ll,greater<ll> > st;
	for(auto x:mp[1])st.insert(x.second);
	st.insert(0);
	for(auto x:mp[0]){
		ll p=x.first;
		for(auto y:v[p])st.erase(st.find(mp[1][y]));
		ans=max(ans,First(st)+x.second);
		for(auto y:v[p])st.insert(mp[1][y]);
	}
	printf("%lld\n",ans);
	return 0;
}






```


---

## 作者：jijidawang (赞：3)

显然对于一个选择方案 $(R,C)$ 来说，贡献就是：
$$v((R,C))=rsum(R)+csum(C)-w_{R,C}$$
其中 $rsum(x),csum(x)$ 分别表示行 $x$，列 $x$ 的权值和，$w_{x,y}$ 表示 $(x,y)$ 的权值。

无非就是 $w_{R,C}=0$ 和 $w_{R,C}=1$ 两种情况，而 $w_{R,C}=1$ 的情况只需要扫一遍即可，涉及到的内容可以使用 umap 维护。

对于 $w_{R,C}=0$ 的情况，枚举每个出现过的行 $r$，按 $csum$ 从大到小枚举每个出现过的列 $c$，当 $w_{r,c}=0$ 时，后面的的 $(r,\cdots)$ 决策一定更劣，于是直接跳出循环即可。

不难发现时间复杂度为 $\Theta(n)$。

---

## 作者：heaksicn (赞：2)

## 1 description

在 $10^9\times 10^9$ 的网格图中有 $n$ 个点 $(r_i,c_i)$，权值为 $x_i$。

要求选择一个点 $(R,C)$，使得第 $R$ 行和第 $C$ 列上所有点的权值和最大。

## 2 solution

考虑选择一个点时答案的构成。

假设 $sum_{i,0/1}$ 表示第 $i$ 行或列的权值和。

如果我们选择了一个点 $(R,C)$，那么此时的答案应为 $sum_{R,0}+sum_{C,1}-val_{R,C}$。

那么，如果我们钦定必须选择第 $R$ 行，那么为了保证答案最大，我们就应该选择去除这行的点后权值和最大的一列。

离散化后用线段树维护即可。

由于每个点只会被去除 $1$ 次，所以总共的更新次数为 $O(n)$ 次。

时间复杂度 $O(n\log n)$。

## 3 code

```
//Man always remember love because of romance only!
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pa pair<int,int>
#define mp make_pair
#define fi first
#define se second
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int r[200001],c[200001],x[200001];
int a[200001];
vector<pa> v[200001]; 
int sum[200001];
int tr[800001];
inline int maxx(int x,int y){
	return x>y?x:y;
}
inline void pushup(int x){
	tr[x]=maxx(tr[x<<1],tr[x<<1|1]);
}
inline void build(int x,int l,int r){
	if(l==r){
		tr[x]=sum[l];
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
inline void update(int x,int k,int l,int r,int id){
	if(l==id&&r==id){
		tr[x]+=k;
		return;
	}
	int mid=(l+r)/2;
	if(mid>=id) update(x<<1,k,l,mid,id);
	else update(x<<1|1,k,mid+1,r,id);
	pushup(x);
}
int sum2[200001];
map<int,int> sb;
signed main(){
	int n=read();
	for(int i=1;i<=n;i++){
		r[i]=read(),c[i]=read(),x[i]=read();
		a[i]=c[i];
	}
	sort(a+1,a+n+1);
	int tp=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=tp;i++) sb[a[i]]=i;
	for(int i=1;i<=n;i++) c[i]=sb[c[i]];
	for(int i=1;i<=n;i++) a[i]=r[i];
	sort(a+1,a+n+1);
	tp=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=tp;i++) sb[a[i]]=i;
	for(int i=1;i<=n;i++) r[i]=sb[r[i]];
	for(int i=1;i<=n;i++){
		v[r[i]].push_back(mp(c[i],x[i]));
		sum[c[i]]+=x[i];
		sum2[r[i]]+=x[i];
	}
	build(1,1,n);
	int ans=0;
	for(int i=1;i<=tp;i++){
		for(int j=0;j<v[i].size();j++) update(1,-v[i][j].se,1,n,v[i][j].fi);//去除该行的所有点
		ans=maxx(ans,sum2[i]+tr[1]);//该行的权值+权值最大的一列
		for(int j=0;j<v[i].size();j++) update(1,v[i][j].se,1,n,v[i][j].fi);//加回去
	}
	write(ans);
	return 0;
}
```


---

## 作者：RedStoneShark (赞：1)

### 思路：
考虑枚举：

记录每一行，每一列的总值，升序排序。然后枚举行，列坐标。遇见 $\left(x,y\right)=0$ 直接 break 就好，因为它肯定是最大的或者是之前就已经遇见过最大的了。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
unordered_map<int,int> mpl,mpc;
map<pair<int,int>,int> mp;
vector<pair<int,int> > vel,vec;
signed main(){
	cin>>n;
	for(int r,c,x,i=1;i<=n;i++){
		cin>>r>>c>>x;
		mpl[r]+=x,mpc[c]+=x;
		mp[{r,c}]+=x;
	}
	for(auto [x,y]:mpl) vel.push_back({y,x});
	for(auto [x,y]:mpc) vec.push_back({y,x});
  //存入
	sort(vel.begin(),vel.end());
	sort(vec.begin(),vec.end());
	reverse(vel.begin(),vel.end());
	reverse(vec.begin(),vec.end());
  //升序排列
	int ans=-1;
	for(auto [x,y]:vel){
		for(auto [xx,yy]:vec){
			if(mp.find({y,yy})==mp.end()){ans=max(ans,x+xx);break;}
			else ans=max(ans,x+xx-mp[{y,yy}]);
		}
	}
  //暴力枚举
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：csh0908 (赞：0)

### 题意
[题意](https://www.luogu.com.cn/problem/AT_abc298_f)
已经非常明确，不多赘述。

### 思路
不难想到一种朴素且暴力的做法，就是枚举行和列，$n^{2}$ 暴力。显然会超时，于是想到优化这个暴力。能否排序每行的和以及每列的和，直接找出和最大的行以及和最大的列直接相加减去当前点呢，显然是不行的，因为当前点可能很大，那么则不是最优的，模拟样例 $1$ 也可以知道。但如果当前点为 $0$，则肯定是最大的。那我们只需要思考当前点不为 $0$ 时，应该怎么办。我们可以先用 $ans$ 暂时统计着当前的值，取最大，直到找到下一个行和列都最大的，且当前点为 $0$，再用 $ans$ 去更新，取最大，此时的值即为最大值，直接输出即可。

---

## 作者：__ZengJunjie__ (赞：0)

[题目链接](https://atcoder.jp/contests/abc298/tasks/abc298_f)  
## 题目解析：  
题目大意已经非常明白了，就是在一个 $10^9 \times 10^9$ 的二维平面上有 $n$ 个带权值的点，求对于平面中的每个点其所在行和列的权值和再减去这个点的权值的最大值。第一眼看上去 $10^9$ 非常大，而 $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $ 所以我们先考虑将每个点的坐标离散化，这样就转化成了 $(2 \times 10^5) \times (2 \times 10^5)$ 的平面，再求出离散化后每行的权值 $h_i$ 和和每列的权值和 $l_i$。那么问题来了，怎样快速求出答案呢？考虑对于每个点 $(i,j)$，分两种情况考虑：
1. $v(i,j)>0$，那么这个点对答案的贡献就等于其所在行和列的权值和再减去这个点的权值。
2. $v(i,j)=0$，这种情况有点复杂，对于每个列 $i$ 只能选择一个 $v(i,j)=0$ 的 $j$，显然不能暴力枚举，考虑从有权值的 $n$ 个点中计算。将 $n$ 个点按照行的坐标升序排序，行坐标相同按列坐标升序排序，对于一个点 $i$ $(1 \leq i \leq n)$，它的 $r_i$ 能够相匹配的列坐标就是 $n$ 个列中去除每个行坐标为 $r_i$ 的点的列坐标，因此我们把每个列坐标加上 $0$, $n+1$ 当作隔板，求出相邻两个隔板之中求对应列的每个 $l_i$ 的最大值，用线段树维护。

(注：上面的 $v(i,j)$ 指的是点 $(i,j)$ 的权值)  
最后，求这两种情况的最大值即是答案。  
## 代码部分：  

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,v[200010],x[200010],y[200010],idx1,idx2;
long long h[200010],l[200010],ans1,ans2,tree[800010],maxx[200010];
struct node{
	long long id,a;
}r[200010],c[200010];
struct edge{
	long long R,C;
}D[200010];
bool cmp1(node A,node B){
	if(A.a!=B.a)return A.a<B.a;
	else return A.id<B.id;
}
bool cmp2(edge A,edge B){
	if(A.R!=B.R)return A.R<B.R;
	else return A.C<B.C;
}
void build(long long p,long long L,long long R){
	if(L==R){
		tree[p]=l[L];
		return ;
	}
	long long mid=(L+R)/2;
	build(p*2,L,mid);
	build(p*2+1,mid+1,R);
	tree[p]=max(tree[p*2],tree[p*2+1]);
}
long long query(long long p,long long L,long long R,long long x,long long y){
	if(x<=L&&R<=y)return tree[p];
	if(y<L||R<x)return -1e9;
	long long mid=(L+R)/2,res=0;
	res=max(query(p*2,L,mid,x,y),query(p*2+1,mid+1,R,x,y));
	return res;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&r[i].a,&c[i].a,&v[i]);
		r[i].id=i,c[i].id=i;
	}
	sort(r+1,r+n+1,cmp1);
	sort(c+1,c+n+1,cmp1);
	for(int i=1;i<=n;i++){
		if(r[i].a!=r[i-1].a)x[r[i].id]=++idx1;
		else x[r[i].id]=x[r[i-1].id];
		if(c[i].a!=c[i-1].a)y[c[i].id]=++idx2;
		else y[c[i].id]=y[c[i-1].id];
	}
	for(int i=1;i<=n;i++)D[i].R=x[i],D[i].C=y[i];
	sort(D+1,D+n+1,cmp2);
	for(int i=1;i<=n;i++)h[x[i]]+=v[i],l[y[i]]+=v[i];
	build(1,1,n);
	for(int i=1;i<=n;i++){
		ans1=max(ans1,h[x[i]]+l[y[i]]-v[i]);
	}
	for(int i=1;i<=n;i++){
		if(D[i].R!=D[i-1].R){
			if(D[i].C!=1)maxx[D[i].R]=max(maxx[D[i].R],query(1,1,n,1,D[i].C-1));
			if(i!=1&&D[i-1].C!=n)maxx[D[i-1].R]=max(maxx[D[i-1].R],query(1,1,n,D[i-1].C+1,n));
		}
		else {
			if(D[i].C-D[i-1].C>1)maxx[D[i].R]=max(maxx[D[i].R],query(1,1,n,D[i-1].C+1,D[i].C-1));
		}
	}
	for(int i=1;i<=n;i++)ans2=max(ans2,h[i]+maxx[i]);
	printf("%lld",max(ans1,ans2));
	return 0;
}
```

---

## 作者：yuhong056 (赞：0)

# 题解：AT_abc298_f [ABC298F] Rook Score
其实这道题只需要暴力。
## 思路
直接枚举选哪一行，再找和最大的列即可。
## 小细节
如果直接枚举，可能会有重叠部分，选和最大的列不一定最优，举个例子（摘自楼下）：

![](https://cdn.luogu.com.cn/upload/image_hosting/iwwd9ohe.png)

此时，我们会选择最大的第 $2$ 列，最终得到答案为：$1 + 9 + 1 + 0 = 11$。

但是，实际上，正确答案却是第 $1$ 列，第 $2$ 行，答案为：$2 + 0 + 1 + 9 = 12$。

那怎么办呢？

其实非常简单，我们将所有与本行有重叠部分的列全部减去重叠部分，再去找最大值即可。

但是，这里即需要改变元素大小，又要找最大值，因此需要一个堆来维护。

这里可以直接使用 STL 中的 [`multiset`](https://oi.wiki/lang/csl/associative-container/)。

**记得开 `long long`！**
## Code
```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 35;

map<int, ll>hsum, lsum; // 存储每一行、列的和
multiset<ll>Lsum; // 存储所有列的和
map<int, vector<pair<int, ll> > >h; // 存储每行有哪些列相交，相交点值为多少
ll ans;
int n;

int main(){
	cin >> n;
	for(int i = 1, r, c, x; i <= n; i++) {
		cin >> r >> c >> x;
		hsum[r] += x, lsum[c] += x;
		h[r].push_back({c, x});
	}
	for(auto [x, sum] : lsum) {
		Lsum.insert(sum);
	}
	for(auto [x, sum] : hsum) {
		for(auto [y, s] : h[x]) { // 将所有与本行有重叠部分的列全部减去重叠部分
			Lsum.erase(Lsum.find(lsum[y]));
			Lsum.insert(lsum[y] - s);
		}
		ans = max(ans, sum + *Lsum.rbegin()); // 找最大值
		for(auto [y, s] : h[x]) { // 将重叠部分全部加回来，避免影响后续计算
			Lsum.erase(Lsum.find(lsum[y] - s));
			Lsum.insert(lsum[y]);
		}
	}
	cout << ans;
	return 0;
}

```

---

## 作者：yegengghost (赞：0)

对于该题有一个通式，就是用两个数组分别记录当前行列的数字之和。为了找最大值，我们就将所得值升序排序，接着倒序枚举。若发现此时当前格子的值为零，对该数计算完后则无需继续往下考虑。因为之后的答案注定要比该值小。

若发现数值大于零，就按照题面计算即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1;
const int mod=1;
int ksm(int x,int k)
{
	int ans=1,base=x;
	while(k)
	{
		if(k&1) ans=1ll*ans*base%mod;
		base=1ll*base*base%mod; k>>=1;
	}
	return ans;
}
int read()
{
	int f=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}
int n;
int x,y,val;
int ans;
vector<pair<int,int> >r,c;
map<pair<int,int>,int>mp;
unordered_map<int,int>row,colomn;
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		x=read();
		y=read();
		val=read();
		mp[{x,y}]=val;//不仅要记录下这一个格子的值
		row[x]+=val;
		colomn[y]+=val;
		//还要把剩下来对应行列给累加进去。
	}
	//准备排序。
	for(auto i:row)
		r.push_back({i.second,i.first});
	for(auto i:colomn)
		c.push_back({i.second,i.first});
	sort(r.begin(),r.end());
	sort(c.begin(),c.end());
	reverse(r.begin(),r.end());
	reverse(c.begin(),c.end());//为了找到最优解，还是得先从最大的数开始找，所以有这一步。
	for(auto i:r)
		for(auto j:c)
		{
			if(mp.find({i.second,j.second})==mp.end())//若该格子的数字为0，那么说明后面再找也都是0且wyy
			{
				ans=max(ans,i.first+j.first);
				break;
			}
			else
				ans=max(ans,i.first+j.first-mp[{i.second,j.second}]);//反之就把我们当前的数字给减掉。
		}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Meickol (赞：0)

根据题意容易写出暴力做法：

```c++
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int N=2e5+5;
int n;
map<int,int> mpx,mpy;
map<int,LL> sumx,sumy;
map<int,int> p[N];
int cntx,cnty;
int getx(int x){
	if(!mpx[x]) mpx[x]=++cntx;
	return mpx[x];
}
int gety(int y){
	if(!mpy[y]) mpy[y]=++cnty;
	return mpy[y];
}
void solve(){
	cin>>n;
	rep(i,1,n){
		int x,y,w;
		cin>>x>>y>>w;
		sumx[getx(x)]+=w;
		sumy[gety(y)]+=w;
		p[getx(x)][gety(y)]=w;
	}
	LL ans=0;
	rep(i,1,cntx){
		rep(j,1,cnty){
			LL t=sumx[i]+sumy[j]-p[i][j];
			ans=max(ans,t);
		}
	}
	cout<<ans;
}
```



但这显然会 `TLE`。

如何优化呢？观察上面代码种的计算式 $\large sumx_{i}+sumy_{j}-p_{i,j}$，容易想到，要让答案越大，必然是让 $\large sumx_{i}+sumy_{j}$ 越大，且 $\large p_{i,j}$ 越小。

于是可以想到将 $sumx$ 和 $sumy$ 先降序排序。

经过降序排序后，就能保证每次先枚举到的 $sumx$ 以及 $sumy$ 更大。

而当点数很多且稀疏分布时 $\large p_{i,j}$ 会有最小值 $0$，否则为题目给定的点值。

当 $sumx$ 已经确定，我们考虑 $sumy$ 时，显然当 $\large p_{i,j}$ 取 $0$ 时更优。但这并不一定是最终答案，这只能保证在当前确定的 $sumx$ 下继续枚举 $sumy$ 时不会出现更优答案，并不意味着在下一轮 $sumx$ 中不会出现比当前选择更优的答案，所以当 $\large p_{i,j}$ 为 $0$ 时我们结束本轮 $sumy$ 的枚举，直接继续下一轮 $sumx$ 的枚举。

**最终代码**

```c++
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
typedef pair<LL,int> PLI;
const int N=2e5+5,MOD=1e6+7;
int n;
map<int,int> mpx,mpy;
map<int,LL> sumx,sumy;
map<int,int> p[N];
int cntx,cnty;
vector<PLI> vecx,vecy;
int getx(int x){
	if(!mpx[x]) mpx[x]=++cntx;
	return mpx[x];
}
int gety(int y){
	if(!mpy[y]) mpy[y]=++cnty;
	return mpy[y];
}
void solve(){
	cin>>n;
	rep(i,1,n){
		int x,y,w;
		cin>>x>>y>>w;
		sumx[getx(x)]+=w;
		sumy[gety(y)]+=w;
		p[getx(x)][gety(y)]=w;
	}
	for(auto x:sumx){
		vecx.push_back({x.second,x.first});
	}
	for(auto y:sumy){
		vecy.push_back({y.second,y.first});
	}
	sort(vecx.begin(),vecx.end(),greater<PLI>());
	sort(vecy.begin(),vecy.end(),greater<PLI>());
	LL ans=0;
	for(auto x:vecx){
		for(auto y:vecy){
			LL t=x.first+y.first-p[x.second][y.second];
			ans=max(ans,t);
			if(!p[x.second][y.second]) break; //必要的优化
		}
	}
	cout<<ans;
}
```

---

