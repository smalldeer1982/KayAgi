# [ABC348C] Colorful Beans

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc348/tasks/abc348_c

$ N $ 種類のビーンズが $ 1 $ 粒ずつあります。 $ i $ 種類目のビーンズはおいしさが $ A_i $ で色が $ C_i $ です。ビーンズは混ぜられており、色でしか区別することができません。

あなたはビーンズの色を $ 1 $ つ選び、その色のビーンズをどれか $ 1 $ 粒食べます。ビーンズの色をうまく選ぶことで、食べる可能性のあるビーンズのおいしさの最小値を最大化してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ A_i\ \leq\ 10^{9} $
- $ 1\ \leq\ C_i\ \leq\ 10^{9} $
- 入力は全て整数である。
 
### Sample Explanation 1

同じ色のビーンズは互いに区別がつかないことに注意してください。 選ぶことができる色は 色 $ 1 $ と 色 $ 5 $ です。 - 色 $ 1 $ のビーンズは $ 2 $ 種類あり、美味しさはそれぞれ $ 100,\ 40 $ です。よって、色 $ 1 $ を選んだときのおいしさの最小値は $ 40 $ です。 - 色 $ 5 $ のビーンズは $ 2 $ 種類あり、美味しさはそれぞれ $ 20,\ 30 $ です。よって、色 $ 5 $ を選んだときのおいしさの最小値は $ 20 $ です。 おいしさの最小値を最大化するには 色 $ 1 $ を選べばよいため、そのときの最小値である $ 40 $ を出力します。

## 样例 #1

### 输入

```
4
100 1
20 5
30 5
40 1```

### 输出

```
40```

## 样例 #2

### 输入

```
10
68 3
17 2
99 2
92 4
82 4
10 3
100 2
78 1
3 1
35 4```

### 输出

```
35```

# 题解

## 作者：Little_x_starTYJ (赞：9)

### 解题思路
对于每种颜色的豆子，我们先找到美味度最小的那个，最后找出这些不同种类的豆子中美味度最大的即可。

那我们怎么找到第 $i$ 种豆子中美味度最小的那个呢？这里给出两种思路：

1. 使用桶的思想标记。
2. 对于每一种的豆子按照美味度从大到小排序。

**注意：** 如果你使用的是思路一，那么你不能使用数组进行标记，因为数据范围很大，因此我们可以使用 `map` 进行标记。

第一种思路的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node {
	int a, c;
}b[200010];
map<int, int> m;
signed main() {
ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> b[i].a >> b[i].c;
		if (m[b[i].c] == 0)
			m[b[i].c] = b[i].a;
		else 
		m[b[i].c] = min(m[b[i].c], b[i].a);
	}
	int ans = -1e9;
	for (int i = 1; i <= n ;i ++){
		ans = max(m[b[i].c], ans);
	}
	cout << ans;
  	return 0;
} 
```
第二种思路的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node {
	int a, c;
}b[200010];
map<int, int> m;
bool cmp(node a, node b){
	if (a.c != b.c)
		return a.c < b.c;
	return a.a < b.a;
}
signed main() {
ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> b[i].a >> b[i].c;
	sort(b + 1, b + 1 + n, cmp);
	int ans = -1e9;
	for (int i = 1; i <= n; i++)
		if (b[i].c != b[i - 1].c)
			ans = max(ans, b[i].a);
	cout << ans;
	return 0;
}
```
### 总结
这道题目还是很水，主要考察的是桶或者结构体排序，如果需要程序运行速度更快，建议大家使用第二种方法完成这道题目，因为本题使用第二种方法比第一种方法快两倍，如果需要以最快的速度完成这道题，那么建议使用第一种方法，因为代码要短 $50$ 个字符。

---

## 作者：MinimumSpanningTree (赞：9)

[原题链接](https://www.luogu.com.cn/problem/solution/AT_abc348_c)

先开一个数组标记每一种颜色最小的美味值，再遍历找出这些最小美味值的最大值即可。

考虑到颜色最大可以到 $10^9$，数组无法开到这么大，所以可以使用 `map` 来存储。

```cpp
#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<algorithm>
#include<cmath>
using namespace std;
unordered_map<int,int> um;
int n,a,b,ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		if(!um.count(b)) um[b]=a;
		else um[b]=min(um[b],a);
	}
	for(unordered_map<int,int>::iterator it=um.begin();it!=um.end();it++) ans=max(ans,it->second);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：hz_rft (赞：8)

### 题目翻译：

你有 $N$ 个糖果，并且每一个糖果都有美味度 $A_i$ 和他的种类 $C_i$，求每种糖果中美味度 $A_i$ 的最小值的最大值。换句话说，就是将每种糖果的美味度 $A_i$ 的最小值保存出来，在从中找到最大值并输出。

### 思路：

看到每种糖果都有两个属性：美味度 $A_i$ 以及种类 $C_i$，还要找每一种糖果的最小值，便考虑用结构体实现。

### 具体做法：

先循环输入美味度 $A_i$ 以及种类 $C_i$，然后排序，最后再按题目描述来找每种糖果中美味度 $A_i$ 的最小值的最大值。输出即可。

### 代码：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
struct d{
	int a,c;
}b[200001];//结构体
int cmp(d x,d y){
	if(x.c==y.c)return x.a<y.a;
	else return x.c<y.c;//优先看种类是否相同，相同就按美味度排序，否则按种类大小排序
}
int n,i,s;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)cin>>b[i].a>>b[i].c;//输入美味度与种类
	sort(b+1,b+n+1,cmp);//排序
	for(i=1;i<=n;i++)
	{
		if(b[i].c!=b[i-1].c)s=max(s,b[i].a);//判断是否为种类的最小值，以及存其中的最大值
	}
	cout<<s;//输出
	return 0;//完结撒花！！！
}
```

[AC 记录](https://atcoder.jp/contests/abc348/submissions/52135838)

### 总结：

这道题目算一道结构体与排序的练习题目，作者在赛时 14 分 55 秒时就 A 了，建议可当结构体的经典习题练手。

---

## 作者：__ATRI__ (赞：7)

## 题目大意

有 $N$ 种豆子。其中第 $i$ 种豆子的美味度为 $A_i$，颜色为 $C_i$。豆子被混在一起，只能通过颜色来区分。

你要选择一种颜色的豆子，然后吃一种这种颜色的豆子。通过选择最佳颜色，使所吃豆子的美味度的最小可能值最大。

## 解法

看到 $1\le C_i\le10^9$，也就是说颜色值可能很大。

但是 $1\le N\le2\times10^5$，也就是说一共最多只有 $2\times10^5$ 种颜色。

考虑使用 map 对颜色进行重新编码，将 $N$ 种颜色改为 $1$ 到 $N$ 的值。

编码之后对于每一种颜色进行分类，用优先队列找出每一种颜色的最小美味度，取最大值，然后输出。

代码：
```cpp
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

using ll=long long;

int n,a[200005],c[200005],cnt,ans;//cnt 是颜色数量，ans 是统计的答案
map<int,int>mp;//使用 map 对颜色进行重新编码
priority_queue<int,vector<int>,greater<int> >st[200005];//用优先队列取每一种颜色的最小美味度

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for(int i=1;i<=n;++i){
		cin >> a[i] >> c[i];
		if(!mp.count(c[i]))mp[c[i]]=++cnt;//若当前颜色没有被编码，就进行编码
		c[i]=mp[c[i]];//用编码后的颜色替换原来的颜色
		st[c[i]].push(a[i]);//将美味度放进当前颜色的优先队列
	}
	for(int i=1;i<=cnt;++i)ans=max(ans,st[i].top());//统计答案
	cout << ans << endl;
	return 0;
}
```

---

## 作者：CQBZ_ZJYjoe (赞：5)

[题目链接](https://atcoder.jp/contests/abc348/tasks/abc348_c)

## 初步思路
初见题目，一看直接吓一跳
-   $1\leq N\leq 2\times 10^5$
-   $1\leq A_i \leq 10^9$
-   $1\leq C_i \leq 10^9$

停，我们仔细看一看描述，发现只用将输入中每种豆子的最小美味值记录下来，再取其中的最大值即可，~~此题结束~~不可能的，由于 $1\leq A_i \leq 10^9$ 且 $1\leq C_i \leq 10^9$ 不仅会爆 int 而且会获得 MLE 或 CE 的好成绩。又由于 $1\leq N\leq 2\times 10^5$，于是想到可以用 map 记录出现次数，时间复杂度为 $O(N \log N)$，接下来请看代码。

## 代码实现
```cpp
#include<bits/stdc++.h>
#define fast_io ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define lowbit(x) x&-x
#define endl '\n'
#define ve vector
#define pq priority_queue
#define dq deque
#define mk make_pair
using namespace std;
using ll=long long;using db=double;using ull=unsigned long long;using ldb=long double;using fl=float;using bo=bool;using i128=__int128_t;using uint128=__uint128_t;
int n,a[200005],ans;
map<int,int> mp;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	fast_io;
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		int x;
		cin>>x>>a[i];
		if (mp.find(a[i])==mp.end())
			mp[a[i]]=0x7f7f7f7f;//初始化为极大值
		mp[a[i]]=min(mp[a[i]],x);//更新每种豆子的美味值
	}
	for (int i=1;i<=n;i++)
		ans=max(ans,mp[a[i]]);//查找每种豆子美味程度的最大值
	cout<<ans;
	return 0;
}
```

---

## 作者：Tracy_Loght (赞：4)

## 题目描述：

答案是**每一种颜色**豆子带来效益的**最小值中**，**取最大值**。

## 思路：

前置知识：struct 的排序。

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ A_i\ \leq\ 10^{9} $
- $ 1\ \leq\ C_i\ \leq\ 10^{9} $

数组是**不可能存下**的，考虑用 map 或 struct，map 简单一点，但 map 前一位已经讲了，那我讲一下 struct 的。

------------
1. 定义 struct：
```
struct op{
	int x,y;//分别表示收益和颜色
};
```

2. 以颜色排序：因为求的是每一种颜色的最小值，而直接一个个去找铁定**超时**，且答案**与顺序无关**，所以先排序，**以颜色排序**，可以帮助我们找**每一个**颜色豆子**收益的最小值**。

**注：**（先**定义排序方式**，再排序，普通的 sort 不支持 struct 排序）

```
bool cmp(const op a,const op b)//以颜色排序
{
	return a.y<b.y;
}
sort(o+1,o+n+1,cmp);//排序范围
```

3. 找所有颜色的**最小值**：
```
int jl=1;
for(int i=1;i<=n;i++){//在排序后的颜色内找每个颜色的最小
	small[jl]=min(o[i].x,small[jl])
	if(o[i].y!=o[i+1].y){
     jl++;
     small[jl]=0x7fffffff;
	} 
}
```

4. 找所有颜色的**最小值中的最大值**：

```
int big=0xc0c0c0c0; //将比较的设为最小
for(int i=1;i<=jl;i++)//找最大
	big=max(big,k[i]);
cout<<big;//输出答案
return 0;
```
完结撒花！

---

## 作者：39xiemy (赞：3)

## 题目大意

有 $n$ 颗豆子，每颗豆子有 $a_i$ 点美味度，其颜色为 $c_i$，现在定义第 $d_i$ 颗豆子为第 $c_i$ 种颜色的豆子中美味度最小的豆子，最大化第 $d_i$ 颗豆子的美味度。

## 分析

首先想到对于第 $c_i$ 种颜色的豆子，直接开数组 $b_{c_i}$ 存第 $c_i$ 种颜色的豆子的最小美味度，但看到 $1 \le c_i \le 10^9$ 的取值范围，是不能直接存的。

那就需要对颜色进行离散化，但我~~懒得写~~不会写离散化，后来我又想到了另一种方法。先开结构体存储 $a_i$ 和 $c_i$，再用 `sort` 来排序：在 `cmp` 函数中，以 $c_i$ 作为第一关键字，从小到大排序；若 $c_i$ 的值相同，则以 $a_i$ 作为第二关键字，从小到大排序。

排好序后，只需要遍历一次数组，如果第 $i - 1$ 颗豆子的颜色与第 $i$ 颗豆子的颜色不一样，就说明第 $i$ 颗豆子是当前颜色的豆子中，美味度最小的豆子，用一个变量求出这些豆子的最大值即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,mx=-1;   //mx是用来存储答案，即最大化最小美味度的值。 
struct node{
	int b,col;        //b是美味度，c是颜色
}bean[200001];
inline bool cmp(node x,node y)
{
	return (x.col==y.col?x.b<y.b:x.col<y.col); //这里用的三目运算符，用if判断也可以 
}
int main()
{
	cin>>a;
	for(int i=1;i<=a;i++)
	{
		scanf("%d%d",&bean[i].b,&bean[i].col);
	}
	sort(1+bean,1+bean+a,cmp);      //排序，记得要加1 
	for(int i=1;i<=a;i++)
	{
		if(bean[i].col!=bean[i-1].col)  
		{
			mx=max(mx,bean[i].b);     //如果颜色不一样，就用mx记录下这颗豆子的美味度 
		}
	}
	printf("%d",mx);
	return 0;
}
```

---

## 作者：xxboyxx (赞：3)

### 翻译

有 $N$ 颗豆子，其中第 $i$ 颗豆子的美味度为 $A_i$，颜色为 $C_i$。需要选择一种颜色的豆子，然后使这种颜色的豆子中美味度最小的最大。

### 思路

颜色值是很大的，而且可能不连续，这里要先用**离散化**，将每种颜色离散为 $1 \sim T$，此处 $T$ 为颜色的种数，再分别求出每一种颜色的最小值，再把这些最小值求最大值即可。

### 注意

当某种颜色第一次出现时，这种颜色的最小值就是它。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t=0,maxx=0;
int a[1000005];
int b[1000005];
map<int,int> mp;
int c[1000005];
signed main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		if (mp[b[i]]==0)
		{
			c[++t]=a[i];
			mp[b[i]]=t;//离散化 
		}
		else
			c[mp[b[i]]]=min(c[mp[b[i]]],a[i]);//计算最小 
	}
	for (int i=1;i<=t;i++)//计算最大 
		if (c[i]>maxx)
			maxx=c[i];
	cout<<maxx;
	return 0;
}
```

---

## 作者：Matrix__ (赞：3)

[传送门](https://www.luogu.com.cn/problem/AT_abc348_c)

### 由于作者太菜了，结构体，排序什么的，都不会，本蒟蒻只会 `vector` 加离散化。

这个题其实很水的啦~~

首先呢，一目了然，可以打一个两重循环的暴力。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;
typedef __int128 III;
const db eqs=1e-6;
const int inf=1e9;
void cmax(int &a,int b){a=max(a,b);}
void cmin(int &a,int b){a=min(a,b);}
bool db_eq(db a,db b){return fabs(a-b)<eqs;}

int n;
vector<pair<int,int> >a;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	int aa,c;
	for(int i=1;i<=n;i++)
	{
		cin>>aa>>c;
		bool flag=1;
		for(int j=0;j<(int)a.size();j++)
		{
			if(a[j].first==c)
			{
				cmin(a[j].second,aa);
				flag=0;
				break;
			}
		} 
		if(flag)
		{
			a.push_back({c,aa});
		}
	}
	int sum=-1e9;
	for(int j=0;j<(int)a.size();j++)
	{
		cmax(sum,a[j].second);
	}
	cout<<sum<<endl;
	return 0;
}

```

但是呢：

![](https://cdn.luogu.com.cn/upload/image_hosting/noh7wxnq.png)

所以我们想优化：

可以想到建立数组 $a$，维护一个 $a_i$ 为颜色为 $i$ 的最小的 $A_i$。

但是呢，颜色 $C_i \le 10^9$，开 `a[1000000005]` 会炸空间。

那又该怎么做呢？

又看到 $N \le 10^5$，就想到可以用**离散化**。

我的离散化就是先将 $C_i$ 单独存储，将他排序（要离散化就必须排序！！！），再去个重。用二分找那个数，再返回其下标，这个数就是他离散化后的数。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
typedef double db;
typedef __int128 III;
const db eqs=1e-6;
const int inf=1e9;
void cmax(int &a,int b){a=max(a,b);}
void cmin(int &a,int b){a=min(a,b);}
bool db_eq(db a,db b){return fabs(a-b)<eqs;}

int n;
vector<pair<int,int> >a;
vector<int>b;

int find(int x)
{
    int l=0,r=b.size()-1;
    while(l<r)
    {
        int mid=l+r>>1;
        if(b[mid]>=x) r=mid;
        else l=mid+1;
    }
    return r+1;
}

int x[1000000+5];

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	int aa,c;
	for(int i=1;i<=n;i++)
	{
		cin>>aa>>c;
		a.push_back({aa,c});
		b.push_back(c);
	}
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());
	for(int i=0;i<n;i++)
	{
		x[find(a[i].second)]=1e18;
	}
	for(int i=0;i<n;i++)
	{
//		cout<<a[i].second<<" "<<a[i].first<<" "<<find(a[i].second)<<endl;
		cmin(x[find(a[i].second)],a[i].first);
	}
	int ans=-1e18;
	for(int i=0;i<n;i++)
	{
//		cout<<x[find(a[i].second)]<<endl;
		cmax(ans,x[find(a[i].second)]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：tXX_F (赞：2)

# [ABC348C] Colorful Beans

## 简要题意

给出豆子的美味度 $A_i$ 和颜色 $C_i$，让你选择一种颜色的豆子，使得豆子的美味度的最小值最大。

## 解题思路

用结构体存下豆子的信息，以颜色编号 $C_i$ 从小到大排序。再用一重循环遍历结构体，记录当前美味度的最小值，若当前豆子的颜色与后一颗不同，则更新答案为美味度最小值的最大值即可。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn = 2e5 + 5;
struct Project_Beans {
	int a, c;
} Beans[Maxn];
int n;
int Answer = INT_MIN;
inline bool Compar(Project_Beans A, Project_Beans B) {
	return A.c < B.c;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0), cin >> n;
	for (register int i = 1; i <= n; ++i) cin >> Beans[i].a >> Beans[i].c;
	sort(Beans + 1, Beans + n + 1, Compar);
	for (register int i = 1, max_min = INT_MAX; i <= n; ++i) {
		max_min = min(max_min, Beans[i].a);
		if (Beans[i].c != Beans[i + 1].c) {
			Answer = max(Answer, max_min);
			max_min = INT_MAX;
		}
	}
	cout << Answer << endl;
	return 0;
}
```

---

## 作者：lunjiahao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc348_c)
### 题目大意：
给定 $n$ 个豆子，每个豆子有美味度 $a_i$ 和颜色 $c_i$，选择 $1$ 种颜色的豆子吃 $1$ 粒美味度最小的豆子，求所吃豆子美味度的最大值。

数据范围：$1 \leq n \leq 2 \times 10^5,1 \leq a_i,c_i \leq 10^9$。
### 题目分析：
对于求同种颜色豆子美味度的最小值，考虑开一个 `map` 或 `unordered_map` 等存储，记录所出现的颜色，再遍历每种颜色豆子美味度求最大值即可。

时间复杂度：$O(n)$，含有较大常数。
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,c[N],ans;
unordered_map <int,int> mp;//习惯打unordered_map减少一下常数
signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int a;
		scanf("%d%d",&a,&c[i]);
		if(!mp[c[i]]) mp[c[i]]=a;//这里map初始为空，所以直赋值
		else mp[c[i]]=min(mp[c[i]],a);//否则取最小值
	}
	for(int i=1;i<=n;i++)
		ans=max(ans,mp[c[i]]);//遍历每种颜色的豆子的美味度
	printf("%d",ans);
	return 0;
}
```

---

## 作者：梦应归于何处 (赞：2)

### 题目大意

现在有 $N$ 种豆子，每种豆子有一个美味度和颜色，相同颜色的豆子分辨不清，不同颜色的豆子可以分辨。

现在让你求你最差情况下你能吃到的豆子的美味度的最大值是多少。

### 思路

最差情况下同颜色的豆子只能吃到美味度最小的。而不同颜色的豆子我们肯定吃他们当中美味度最大的，因为我们能分辨不同颜色的豆子。

### 代码

~~~cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp make_pair
#define pll pair<ll,ll>
#define prq priority_queue
using namespace std;
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') {
			f = -1;
		}
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
map<ll, ll> mp;
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n = read();
	while (n--) {
		ll a = read(), b = read();
		if (mp[b] == 0) {
			mp[b] = a;
		} else {
			mp[b] = min(mp[b], a);
		}
	}
	ll ans = 0;
	for (auto i : mp) {
		ans = max(ans, i.second);
	}
	cout<<ans;
	return 0;
}
~~~

---

## 作者：OIer_Tan (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc348_c)

说句闲话，ABC 的 C 题为什么老是 `map` 板题。

## 题意

豆子有 $N$ 种。其中第 $i$ 种豆子的美味度为 $A_i$，颜色为 $C_i$。豆子是混合的，只能通过颜色来区分。

您将选择一种颜色的豆子，并吃下这种颜色的豆子。通过选择最佳颜色，最大限度地增加所吃豆子的最低美味度。

## 思路

显然暴力开数组存是会炸空间的，所以容易想到 `map` 或 `unordered_map`，每次更新当前颜色对应的最小值即可。

这里要注意一点，`map` 或 `unordered_map` 值的初始值都为 $0$，所以更新的时候要注意一下初始值的问题。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std ;

typedef long long ll ;

const ll N = 2e5 + 5 ;

ll n ;

pair <ll,ll> bean [N] ;

unordered_map <ll,ll> cnt ;

int main() 
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> bean [i].first >> bean [i].second ;
//		cnt [bean [i].second] += bean [i].first ;
		if ( cnt [bean [i].second] )
		{
			cnt [bean [i].second] = min ( cnt [bean [i].second] , bean [i].first ) ;
		}
		else
		{
			cnt [bean [i].second] = bean [i].first ;
		}
	}
	ll maxans = 0 ;
	for ( auto it = cnt.begin () ; it != cnt.end () ; it ++ )
	{
//		cout << it -> first << " " << it -> second << endl ;
		if ( maxans < it -> second )
		{
			maxans = it -> second ;
		}
	}
	cout << maxans << endl ;
	return 0;
}

```

---

## 作者：I_Love_DS (赞：1)

## 前置闲话

这场 ABC348 我只做出了前 $3$ 题。~~我太蒻了~~

但本题还是蛮简单的。

## 思路

记录一样颜色的豆子的最小美味度，再求最大美味度，这种做法一定会超时，爆空间。实际上，我们可以把这 $N$ 个豆子进行排序。

### 排序方法：

1. 把一样颜色的豆子放在一起。
2. 如果豆子颜色一样，就把美味度小的放前面。

### 这样，本题就简单多了：

枚举一遍所有的豆子，如果 $C_{i - 1} \ne C_i$，那么更新最大美味值。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 50;//n的最大值
int n,ans = 0;//分别表示豆子个数和答案
struct node {
	int w,c;//w是美味度，c是颜色
} a[maxn];
bool cmp(const node &x,const node &y){//比较函数
	if (x.c == y.c) return x.w < y.w;
	else return x.c < y.c;//大于或小于都行
}
int main(){
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%d%d",&a[i].w,&a[i].c);//输入
	sort(a + 1,a + n + 1,cmp);//排序
	for (int i = 1; i <= n; i++) 
		if (a[i].c != a[i - 1].c) //其实这里并不需要特判i是否等于1
			ans = max(ans,a[i].w);//更新答案
	printf("%d",ans);//输出
	return 0;
}
```

谢谢观看。如果有疑问请在评论区留言，我会尽量看的！

---

## 作者：xiao_dong_xi (赞：1)

### 解题思路
题目不难理解，求出每种颜色糖果的美味度最小值的最大值。

于是我想到用结构体排序解决这题。

主要思路就是把颜色和美味度按颜色从小到大排序一遍，然后用一个用于判断颜色变化的标记变量。排序后把标记变量设为颜色最小值，每次统计每种颜色糖果美味度最小值，颜色变化了一次，就统计一次每种颜色糖果的美味度最小值的最大值。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int minmy=2147483647;//每种颜色糖果美味度最小值 
int max_minmy=-2147483647;//每种颜色糖果的美味度最小值的最大值 
int flag;//标记变量 
struct node{int a,c;}f[200002];
int cmp(node x,node y){return x.c<y.c;}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>f[i].a>>f[i].c;
	sort(f+1,f+n+1,cmp);//结构体排序 
	flag=f[1].c;//将标记变量设为颜色最小值 
	for(int i=1;i<=n;i++){
		if(f[i].c!=flag){
			if(minmy>max_minmy)max_minmy=minmy;//判断 每种颜色糖果的美味度最小值的最大值 
			minmy=2147483647;//记得每次赋值 
			flag=f[i].c;
		}
		if(f[i].a<minmy)minmy=f[i].a;//判断每种颜色糖果美味度最小值  
	}
	if(minmy>max_minmy)max_minmy=minmy;//最后还要再判断一次 
	cout<<max_minmy;
    return 0;
}
```

---

## 作者：qw1234321 (赞：1)

题意简单来说就是让你求每种颜色的豆子的最小美味值中的最大值。

理解完题意后就是模拟了，颜色值域比较大，可以用 STL 里的 map 来存。

[code.](https://atcoder.jp/contests/abc348/submissions/52077424)

~~我写过最短的一篇题解。~~

---

## 作者：__Cby___ (赞：1)

# 解题思路
我们使用 `map` 记录每种颜色的最小值，最后遍历 `map` 在这些最小值中取最大值就行了。   
# 代码
```cpp
#include <iostream>
#include <map>
using namespace std;
map<long long int, long long int> mp;
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		long long int a, b;
		cin >> a >> b;
		if (!mp.count(b))mp[b] = a;
		else mp[b] = min(mp[b], a);
	}
	long long int md = -212345678987654;
	for (auto v : mp) {
		md = max(md, v.second);;
	}
	cout << md << endl;
	return 0;
}
```

---

## 作者：lucasincyber (赞：1)

## 思路
思路不难想到。可以用一个 map 维护每一种不同颜色的豆子的最小值，再在这些所有值中取最大值（因为只用选一种颜色的豆子，且需要尽可能大）。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
map<int, int> bd;

int main()
{
	cin >> n;
	for (int i = 1, d, c; i <= n; i++)
	{
		cin >> d >> c;
		if (bd.find(c) == bd.end()) bd[c] = d;
		else bd[c] = min(bd[c], d);
	}
	int ans = 0;
	for (auto i : bd)
		ans = max(ans, i.second);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：Harrylzh (赞：1)

考虑求出每种颜色的美味度的最小值，再在各种颜色的最小值中取最大的。因为 $C_i \le 10^9$，数组开不下，可以使用 map 来处理映射关系。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long a[1000000+5];
long long c[1000000+5];
long long maxn=-2e9;
map<long long,long long> mp;
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i],&c[i]);
        if(!mp.count(c[i])) mp[c[i]]=a[i];
		else mp[c[i]]=min(mp[c[i]],a[i]);
	}
	for(long long i=1;i<=n;i++)
	{
		maxn=max(maxn,mp[c[i]]);
	}
	printf("%lld\n",maxn);
	return 0;
}
```

---

## 作者：_colin1112_ (赞：1)

## 思路

一开始看到这道题，就直接想着开一个二维数组 $a_{i,j}$，$a_{c_i}$ 表示一个颜色的所有美味度。然后用 `set` 维护颜色，最后按照 `set` 中的颜色值对二维数组进行依次排序，最后统计最大值即可。

Code:

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E = 1e6 + 5;
ll n, max1;
vector<ll> a[E];
set<ll> id;
int main()
{
    cin >> n;
    for (int i = 1, x, y; i <= n; i++)
    {
        cin >> x >> y;
        a[y].push_back(x);
        id.insert(y);
    }
    for (auto v : id)
        sort(a[v].begin(), a[v].end());//排序
    for (auto v : id)
        max1 = max(max1, a[v][0]);//统计最大值
    cout << max1;
    return 0;
}
```

好，RE。

注意到颜色 $c_i$ 的数据范围是 $1\leq c_i \leq 10^9$，直接用数组记录颜色是肯定不行的。于是，对 $c$ 数组进行离散化即可。

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E = 1e6 + 5;
ll n, max1;
ll x[E], y[E], t[E];
vector<ll> a[E];
set<ll> id;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    ll cnt = 0;
  //------------------------------离散化
    for (int i = 1; i <= n; i++)
        t[++cnt] = y[i];
    sort(t + 1, t + 1 + cnt);
    ll m = unique(t + 1, t + 1 + cnt) - t - 1;
    for (int i = 1; i <= n; i++)
        y[i] = lower_bound(t + 1, t + 1 + m, y[i]) - t - 1;
  //-------------------------------
    for (int i = 1; i <= n; i++)
    {
        a[y[i]].push_back(x[i]);
        id.insert(y[i]);
    }
    for (auto v : id)
        sort(a[v].begin(), a[v].end());//排序
    for (auto v : id)
        max1 = max(max1, a[v][0]);//统计最大值
    cout << max1;
    return 0;
}
```

---

## 作者：Ryzen_9_7950X (赞：1)

# 题意
你有若干颗豆子，你希望选一种颜色的豆子，使得可能吃到的美味程度最小的豆子的美味程度最大（只能通过颜色区分豆子）。
# 方法
我们可以新建一个 map 容器，将颜色设置为键，将对应颜色可能出现的美味值最小的豆子的美味值设置成值。\
如果你们还不知道什么是 map 容器，请跳转[对 map 容器的介绍](https://c.biancheng.net/view/7173.html)。
# 示例
## 样例 1
举个例子：
```
4
100 1
20 5
30 5
40 1
```
第一颗豆子被输入时， map 容器中尚不存在颜色 $1$ 。\
因此，我们在容器中新建颜色 $1$ ，并将对应的「最小美味值」设置成 $100$ 。\
第二颗豆子被输入时，容器中尚不存在颜色 $5$ 。\
因此，我们在容器中新建颜色 $5$ ，并将对应的「最小美味值」设置成 $20$ 。\
第三颗豆子被输入时，容器中已经存在颜色 $5$ 。\
由于这颗豆子的美味值超过对应的「最小美味值」，因此不做任何改动。\
第四颗豆子被输入时，容器中已经存在颜色 $1$ 。\
由于这颗豆子的美味值小于对应的「最小美味值」，所以我们将对应的「最小美味值」设置成 $40$。\
代码执行完毕后，容器的内容如下：
$$
\begin{bmatrix}
1 & 40 \\
5 & 20 \\
\end{bmatrix}
$$
如上所示，容器中所有值的最大值是 $40$ ，因此输出答案 $40$。
## 样例 2
再举个例子：
```
10
68 3
17 2
99 2
92 4
82 4
10 3
100 2
78 1
3 1
35 4
```
我们用同样的思路，代码执行完毕后， map 容器的内容如下：
$$
\begin{bmatrix}
3 & 10 \\
2 & 17 \\
4 & 35 \\
1 & 3 \\
\end{bmatrix}
$$
如上所示，容器中所有值的最大值是 $35$ ，因此输出答案 $35$。
# 代码
我们可以通过上面的思路，得到下面的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct bean
{
    int color,dls;
};
int main()
{
    int a;
    cin >> a;
    bean x;
    map<int,int> x_;
    vector<int> c;
    for(int i = 1;i <= a;i++)
    {
        cin >> x.dls >> x.color;
        if(x_.find(x.color) != x_.end()) x_[x.color] = min(x_[x.color],x.dls);
        else
        {
            x_[x.color] = x.dls;
            c.push_back(x.color);
        }
    }
    int ans = 0;
    for(int i = 0;i < c.size();i++)
    {
        ans = max(x_[c[i]],ans);
        //cout << c[i] << " " << ans << endl;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：__HHX__ (赞：1)

# 思路
# 法一（离散化思路）
容易观察得：所有 $C_i$ 不等的数量小于等于 $N$。

构造函数 $f(x) = k$ 我们要使得 $k \leq N$ 即可。

开个桶，每次 $cnt_{f(C_i)}$ 更新为 $\min\{cnt_{f(C_i)},A_i\}$。

用 map 或二分构造 $f(x)$ 可以做到 $O(N \log N)$。

代码如下：
```cpp
#include <iostream>
#include <map>

using namespace std;

int n, ma;

map<int, int> cnt;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int a, c;
    cin >> a >> c;
    if (!cnt[c]) cnt[c] = 2e9;
    cnt[c] = min(cnt[c], a);
  }
  for (auto a : cnt) {
    ma = max(ma, a.second);
  }
  cout << ma;
  return 0;
}
```
# 法二（结构体排序）
当然上面的做法对萌新十分不友好，十分容易让萌新大脑短路。

但是，对于这个题，我们仅需进行结构体排序。

$C_i$ 为**第一关键字**，$A_i$ 为**第二关键句**。

$C_i$ 排序可**从小到大**或**从大到小**，我们这样操作仅仅只是让 $C_i$ 相同的相靠。

$A_i$ 排序**从小到大**，我们这样操作仅仅只是最小的 $A_i$ 向前靠。

我们从前到后搜，因为相同的 $C_i$ 下第一个出现的 $A_i$ 最小。

因为这个方法是是我打完后才想出来的，所以没有代码。

伪代码如下：
```
a <- (C, A)(1 ~ n);
sort(a);
for i -> 1 ~ n
  if a[i].C !=a[i - 1].C
    ans = max(ans, a[i].A);
```

---

## 作者：SkyLines (赞：1)

## Translate

有 $N$ 种豆子，每种豆子各有一颗。第 $i$ 种豆子的美味度为 $A_i$，颜色为 $C_i$，豆子是混合的，只能通过颜色区分。你将选择一种颜色的豆子，并吃下所有这种颜色的豆子，选择最佳颜色，使所吃豆子的美味度最小。

## Solution

因为吃下的是一种颜色的豆子，所以可以按 $C_i$ 从小到大排序。然后就可以遍历所有豆子，遍历到第 $i$ 个，如果 $C_{i-1}=C_i$，则更新最小值（取最小值），否则更新答案（取最大值）。

时间复杂度：$O(N \log N)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
int pow_(int aa, int bb, int cc){
	int ans = 1;
	while(bb){
		if(bb & 1) ans = ans * aa % cc;
		aa = aa * aa % cc;
		bb >>= 1;
	}
	return ans;
}
const int N = 2e5 + 5;
int n, minn, ans;
struct node{
	int a, c;
} edge[N];
bool cmp(node xx, node yy){
	return xx.c < yy.c;
}
int main(){
	minn = 1e9 + 5;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &edge[i].a, &edge[i].c);
	}
	sort(edge + 1, edge + n + 1, cmp);
	minn = edge[1].a;
	for(int i = 2; i <= n; i++){
		if(edge[i].c == edge[i - 1].c){
			minn = min_(minn, edge[i].a);
		}
		else{
			ans = max_(ans, minn);
			minn = edge[i].a;
		}
	}
	ans = max_(ans, minn);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：1)

# AT_abc348_c 题解

## 题目大意

给定 $N$ 个豆子，其中第 $i$ 个豆子的美味度是 $A_i$，颜色是 $C_i$，将每一种颜色中美味度最低的豆子组成一个序列，求该序列中的最大值。

## 题目思路

由于颜色 $C_i$ 在 $1$ 和 $10^9$ 之间，直接开数组会爆空间，所以可以选用 STL 中的 `unordered_map`，当然，`map` 也是可以的，用 `unordered_map` 记录每种颜色的最小值，最后枚举 `unordered_map`，找出最大值并输出即可，时间复杂度：$O(N)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=200005;

int n;
int a[N],c[N];
unordered_map<int,int> s;
int maxx;

int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;++i) {
        scanf("%d %d",&a[i],&c[i]);
        if (s.find(c[i])==s.end()) {
            s.insert({c[i],a[i]});
        } else {
            if (a[i]<s[c[i]]) {
                s[c[i]]=a[i];
            }
        }
    }
    for (auto it=s.begin();it!=s.end();++it) {
        maxx=max(maxx,it->second);
    }
    printf("%d",maxx);
    return 0;
}
```

---

## 作者：Igallta (赞：1)

这道题我们看颜色的范围（$10^9$）很明显是一个离散化。

> 你的范围有点松弛，但是你的 $N$ 又弥补了这一部分，如果直接开颜色桶数组的话，可能会出现 MLE、RE 的情况，这边建议数组丢掉的同时做一个离散化。

我是选用了 `map` 和 `set`。

先用 `set` 来存储颜色方便遍历，`map` 记录最小值。

在修改 `map` 的时候，不能直接记录，不然会返回 `0`。

如果当前这个颜色最小值是 `0`，也就是还没有最小值，讲这个值改为最小值。

否则就直接跟当前已经储存的最小值比较就行了。

```cpp
/****************************************
作者:
版权:
日期:
*****************************************/
#include<bits/stdc++.h>
#define LL k<<1
#define RR k<<1|1
#define int long long

using namespace std;
set<int>st;//存储颜色
map<int,int>mp;//存储最小值 
int n;
struct Node{
	int va,cl;
}a[200001]; 
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].va>>a[i].cl;
		mp[a[i].cl]=min(mp[a[i].cl],a[i].va);
		if(mp[a[i].cl]==0)mp[a[i].cl]=a[i].va;
		st.insert(a[i].cl);
	}
	int maxn=0;
	for(auto v:st){
//		cout<<v<<' ';
		maxn=max(mp[v],maxn);
	}
	cout<<maxn;
	return 0;
}
```

---

## 作者：DFs_YYDS (赞：1)

大佬的题解都好厉害，看不懂，就让本蒟蒻来写一篇结构体  `sort` 的题解吧。
# 题目大意
有 $n$ 颗糖果，第 $i$ 颗糖果的味道是 $A_i$，颜色是 $C_i$。问每种颜色味道的最小值最大是多少。  
感觉还是有点难理解，举个具体的例子吧：
```
3
10 2
20 1
15 1
```
有 $3$ 颗糖果，第一颗糖果的颜色为 $2$，味道为 $10$；第二颗糖果的颜色为 $1$，味道为 $20$；第二颗糖果的颜色为 $1$，味道为 $15$。颜色为 $2$ 的糖果味道最小值是 $10$，颜色为 $1$ 的糖果味道最小值是 $15$，取最大值，所以答案是 $15$。

# 具体思路
读入 $n$ 颗糖果的数据后，以颜色为第一关键字，以味道为第二关键字，从小到大排序。这样颜色一样的糖果就在一起，并且相同颜色的第一颗糖果就是当前颜色的最小值。最后只需要对每种颜色糖果的最小值打擂台求味道最大的就行了。

# 完整代码
```cpp
#include<bits/stdc++.h>//万能头。 
using namespace std;
struct candy{//糖果结构体。 
	int c,v;//颜色c和味道v。 
}a[200005];//a数组，开到2*1e5，不然会RE。 
bool cmp(candy x,candy y){//排序的比较函数。 
	if(x.c!=y.c)return x.c<y.c;//第一关键字颜色，如果颜色不一样就把颜色小的排在前面。 
	return x.v<y.v;//第二关键字味道，把颜味道小的排在前面。 
}
int main(){//主函数。 
	int n,Max=0,j;//n颗糖果，最大值Max，j到用到的时候再讲。 
	cin>>n;//读入n。 
	for(int i=0;i<n;i++)cin>>a[i].v>>a[i].c;//先读入颜色再读入味道。 
	sort(a,a+n,cmp);//排序。 
	for(int i=0;i<n;i=j){//注意是i=j。 
		Max=max(Max,a[i].v);//a[i].v一定是当前颜色中味道最小的一个，打擂台。 
		for(j=i+1;j<n&&a[i].c==a[j].c;j++);//寻找下一个不同的颜色，可以用二分优化。 
	}
	cout<<Max;//输出。 
	return 0;//华丽结束。 
}
```

---

## 作者：Spark_King (赞：1)

# ABC_348_C 题解

## 题意翻译

有 $N$ 种豆子，每一种豆子都有自己的美味程度 $A_i$ 和颜色 $C_i$，要求从中选出一种颜色的豆子并吃掉。通过选择最佳颜色，**最大限度**地提高所吃的该种颜色的豆子的**最小美味值**。

## 题目分析

乍一看题目很拗口，不过仔细观察就可以理解题目意思。题目要求我们在所有**同种颜色**里**美味值的最小值**中取**最大值**。

还不明白？那就看样例：

```
输入：
4
100 1
20 5
30 5
40 1

输出：
40
```

样例中，一共有两种颜色，分别为 $1$ 和 $5$。其中，颜色 $1$ 对应了两个美味值分别为 $100$ 和 $40$，**最小值是 $40$**；同理，颜色 $5$ 中，**最小值为 $20$**。
两者中较大的是 $40$，因此答案为 $40$。

清楚了题意，我们来思考做法。

我们可以运用 map 来记录**该种颜色中美味值的最小值**，然后从中遍历得到答案。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
ll a[200010],c[200010];
map<ll,ll> m;
ll ans;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++)
	{
		cin>>a[i]>>c[i];
		if(m.count(c[i])) m[c[i]]=min(m[c[i]],a[i]);
		else m[c[i]]=a[i];//保存每一种颜色中美味值的最小值
	}
	sort(c+1,c+1+n);
	ll cnt=unique(c+1,c+1+n)-(c+1);//排序去重（其实可以不要）
	for(ll i=1;i<=cnt;i++) ans=max(ans,m[c[i]]);//遍历答案
	cout<<ans;
	return 0;
}
```


个人认为本题主要还是在于**读懂题意**，代码什么的其实不难。

---

## 作者：Bc2_ChickenDreamer (赞：1)

## ABC348C

### Sol

主要考察 map 的用法。

一看到 $1 \le C_i \le 10^9$，急速想到用 map。我们先创建两个 map，一个用来记录颜色 $C_i$ 有没有出现过，一个用来记录每个颜色的最小值。

我们遍历一遍 $A_i, C_i$，如果颜色 $C_i$ 没有出现过，那么标记出现，并把另一个 map 中颜色 $C_i$ 最小值初始化为一个极大数（我这里初始化为 $2^{31} - 1$）。然后对于每个 $1 \le i \le n$，都要把颜色 $C_i$ 最小值更新。

这里为了方便，我们加一个数组 $B_i$，用来存储对于每个 $1 \le i \le n$ 出现的颜色。最后我们遍历 $B_i$，取每个颜色最小值的最大值即可。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>

using namespace std;

using ll = long long;

const int kMaxN = 2e5 + 50, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18;

int n, a[kMaxN], c[kMaxN], b[kMaxN], mx = -kInf;
map<int, int> mp, mp2;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++ i) {
    cin >> a[i] >> c[i]; // 输入
  }
  for (int i = 1; i <= n; ++ i) {
    if (!mp2[c[i]]) { // 如果 ci 没出现过
      mp[c[i]] = kInf; // 初始化 2^31  - 1
      mp2[c[i]] = 1; // 标记出现
    }
    mp[c[i]] = min(mp[c[i]], a[i]); // 取最小值
    b[i] = c[i]; // 表示每个 ci
  }
  for (int i = 1; i <= n; ++ i) {
    mx = max(mx, mp[b[i]]); // 取最大值
  }
  cout << mx << '\n';
  return 0;
}
```

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc348_c)

使用 map 记录所有出现过的 $c_i$ 对应的所有 $a_i$ 的最小值，记为 $mp_{c_i}$。然后求 $mp$ 当中所有元素的最大值就行，实现的话就只要枚举每个 $c_i$，然后求最大值。

笔者表述能力较差，具体的求 $mp$ 当中所有元素的最大值的方式直接看代码。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
int a[200010],c[200010];
map<int,int> mp;
int ans=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>c[i];
		if(!mp[c[i]]) mp[c[i]]=a[i];
		else mp[c[i]]=min(mp[c[i]],a[i]);
	}
	for(int i=1;i<=n;i++)
		ans=max(ans,mp[c[i]]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：kkxacj (赞：1)

#### 思路：

题面有点绕，但其实就是说找到一种颜色，使得所有是这种颜色的最小值最大，考虑 `map` 存一下每种颜色的最小值，最后取个最大值就可以了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],b[200010],ma;
map<int,int>mp;
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) 
	{
		scanf("%d%d",&b[i],&a[i]);
		if(!mp[a[i]]) mp[a[i]] = b[i];
		else mp[a[i]] = min(mp[a[i]],b[i]);
	}
	for(int i = 1;i <= n;i++) ma = max(ma,mp[a[i]]);
	cout<<ma<<endl;
        return 0;
}

```

---

## 作者：Ray0Regina (赞：1)

[原题传送门](https://atcoder.jp/contests/abc348/tasks/abc348_c)

看到题首先想到数组存下每个色的最小值，再找出最大。查看一下数据范围，显然数组会爆存不下，且会超时，自然不行。仔细看一下 $n$ 的范围，发现 $n$ 在 $1$ 和 $200000$ 之间，可以用 map，但是记得要判零，复杂度为 $O( n\log n)$，故代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,c,madd=-1;
map<int,int>mad;
bool cmp(int a,int b){
	return a>b;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a>>c;
		if(mad[c])
			mad[c]=min(a,mad[c]);
		else
			mad[c]=a;
	}
	for(auto i:mad)
	madd=max(madd,i.second);
	cout<<madd;
	return 0;
}

```
(第一次发题解好激动啊！特别感谢@Elysian_Realme 大佬的指点！）

---

## 作者：unordered_yao (赞：1)

## 题意

给定 $N$ 种豆子，第 $i$ 种豆子的美味度为 $A_i$，颜色为 $C_i$。而且这些豆子混在一起了，只能通过颜色来区分。你要选择最佳颜色，最大限度地减少所吃豆子的美味度。

## 思路
因为 $C_i$ 范围很大，开数组这条路走不通。我们可以用 map 记录一下当前颜色豆子的美味度的最小值，令这个数组为 $S$。然后我们遍历一下 $S$，找到 $S$ 中数字的最大值即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n;
map<int,int> mp;
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        int x,y;
        cin >> x >> y;
        if(!mp.count(y)) mp[y] = x;
        else mp[y] = min(mp[y],x);
    }
    int ans = 0;
    for(auto& t:mp){
        ans = max(t.second,ans);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：oceanfish (赞：1)

## 问题陈述

豆子有 $N$ 种。其中第 $i$ 种豆子的美味度为 $A_i$，颜色为 $C_i$。豆子是混合的，只能通过颜色来区分，某一颜色的种子可能有多个。

您将要找出每种颜色的豆子的最小美味值中的最大值。并输出这个值。

## 解法

考虑到数据范围很大，所以排除暴力做法，思考其他做法。

我们发现我们要存储每种颜色的豆子的最小美味值，所以我们使用 `map` 存储。对于求最大值，我们可以预先存下每一种颜色，再在其中取最大值即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a, c;
map<int, int>mp;
int t[500005], o;

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a >> c;
		if (!mp[c])
			mp[c] = a, t[++o] = c;
		else
			mp[c] = min(mp[c], a);
	}
	int ans = 0;
	for (int i = 1; i <= o; i++)
		ans = max(ans, mp[t[i]]);
	cout << ans;
	return 0;
}
```

---

## 作者：ma_niu_bi (赞：1)

### 题意

给出 $n$ 个豆子，每种豆子的颜色为 $C_i$ ，美味度为 $A_i$。求每种颜色的豆子的美味度的最小值的最大值。

### 思路

使用 ```map``` 维护每种颜色的美味度的最小值，最后枚举每种颜色，统计答案即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ans, a[200005], c[200005];
map <int, int> mp;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> a[i] >> c[i];
    for (int i = 1; i <= n; i ++) {
        if (mp.find(c[i]) == mp.end()) mp[c[i]] = a[i];
        mp[c[i]] = min(mp[c[i]], a[i]);
    }
    for (int i = 1; i <= n; i ++) 
        ans = max(ans, mp[c[i]]);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：CEFqwq (赞：1)

考虑开两个 `map` 离散化，一个维护当前颜色是否第一次出现，另一个维护每种颜色豆子美味程度最小值，然后扫一遍统计。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[200005], c[200005];
map<int, bool> mp1;//维护是否第一次出现
map<int, int> mp2;//维护美味程度最小值
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i] >> c[i];
		if (!mp1[c[i]]){
			mp1[c[i]] = 1;
			mp2[c[i]] = a[i];
		}else
			mp2[c[i]] = min(mp2[c[i]], a[i]);
	}
	int mx = 0;
	for (int i = 1; i <= n; i++)
		mx = max(mp2[c[i]], mx);//统计答案
	cout << mx;
}
```

---

## 作者：Elysian_Realme (赞：1)

# AT_abc348_c

## 解题思路

初看到这题，想到可以开一个桶记录每种颜色的最小值，看到数据范围 $10^9$。

注意到这里 $n$ 只有 $2\times 10^5$，即使每种豆子颜色各不相同最多也只会出现 $2\times 10^5$ 种颜色。

于是想到离散化。~~赛时懒得打离散化就用了 map。~~

这里，如果要用 map 记得特判初始值为 $0$ 的情况。

复杂度：离散化和 map 都是 $O(n\log n)$。

[code](https://atcoder.jp/contests/abc348/submissions/52143908)

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc348_c)

## 思路

考虑用一个桶统计 $A_i$ **最小值**，又看到 $1\le C_i\le 10^9$，于是想到考虑记录对于每个 $C_i$，记录 $A_i$ **最小值**的 `map`。

读入数据后记录是否记录过这个种类的食物，如果有就判断**最小值**，否则记录这个值。

最后迭代循环，找到**最大值**，输出。

- 可选优化：把 `map` 替换为 `unordered_map`。

## AC 部分代码

```cpp
const int N=2e5+10;
unordered_map<int,int>mp,vis;
int tom[N],n,ans=-1e9;
pii a[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i].fi>>a[i].se;
		if(!vis[a[i].se])vis[a[i].se]=1,mp[a[i].se]=a[i].fi;//没有就记录。
		else mp[a[i].se]=min(mp[a[i].se],a[i].fi);//有了就判断最小值。
	}
	for(auto it:mp)ans=max(it.se,ans);
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/154768074)

---

## 作者：Pink_Cut_Tree (赞：1)

# AT_abc348_c [ABC348C] Colorful Beans 题解

### 翻译

给出 $n$ 个豆子以及其美味度 $a_i$，颜色 $b_i$，问对于每一种颜色的豆子的美味度的最小值中的最大值是多少。

### 解析

考虑用数组记录每种颜色豆子美味度的最小值，最后打擂求出最大值即可。

观察到 $a_i,c_i\leq 10^9$，于是我们用 `map` 来实现。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a,b,ans;
map<int,int>ds;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	while(n--){
		cin>>a>>b;
		if(ds[b]){
			ds[b]=min(ds[b],a);
		}
		else{
			ds[b]=a;
		}
	}
	for(auto it=ds.begin();it!=ds.end();it++){
		if((*it).second>ans){
			ans=(*it).second;
		}
	}
	cout<<ans;
return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
$f_{j}$ 表示对于所有 $c_i=j$，其中最小的 $a_i$。然后这题就变成了 $\max f_i$。因为 $c_i$ 大，所以可以用 map 存哦！
# 代码
```cpp
# include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair <int, int> pii;

int n, x, y, maxx;
map <int, int> f;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i) {
		cin >> x >> y;
		if (! f[y] || x < f[y])
			f[y] = x;
	}
	for (auto i = f.begin (); i != f.end (); ++ i) //map 独特的遍历方式，其中 auto 可以替换为 map <int, int> :: iterator，i->first 表示第一位（下标），i->second 表示第二维（数值）
		maxx = max (maxx, i->second);
	cout << maxx;
	return 0;
}
```

---

## 作者：ZBH_123 (赞：1)

## 题目分析

这是一道暴力题。我们维护每种颜色的豆子中最小美味程度，再在这些值中寻找最大值就行了。但是因为 $C_i$ 最多可以到 $10^9$，所以我们要离散化。

综上所述，这么做的时间复杂度为 $\Theta(N \log N)$，足以通过本题。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=2e5;
int n,a[maxn+5],b[maxn+5],c[maxn+5],Min[maxn+5];

void init(){
	memset(Min,0x3f,sizeof Min);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&a[i],&c[i]);
		b[i]=c[i];
	}
}

void solve(){
	sort(b+1,b+n+1);
	int cnt=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		c[i]=lower_bound(b+1,b+cnt+1,c[i])-b;
		Min[c[i]]=min(Min[c[i]],a[i]);
	}
	
	int ans=0;
	for(int i=1;i<=cnt;i++){
		ans=max(ans,Min[i]);
	}
	printf("%d",ans);
}

int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 题意：

给定一些豆子，第 $i$ 个豆子颜色为  $C_i$，美味度为 $A_i$；

需要选择一个最佳的颜色，最大限度地减少所吃豆子的美味度。

### 思路：

就是求所有颜色集合中美味度最小的最大值。

考虑用 `map` 维护 $Min_x$ 表示当前 $x$ 颜色集合的最小值，每次加入一个豆子时，将 $Min_{C_i} \to \min(Min_{C_i},A_i)$；注意，初始要赋值为无穷大。

最后遍历一遍出现过的颜色，求出 $Min$ 中的最大值即可。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200200;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,x,y,ans;
ll c[N];
map<ll,ll> Min;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		x=read(),y=read();
		c[i]=y;
		if(!Min[y])
		  Min[y]=x;
		else
		  Min[y]=min(Min[y],x);
	}
	for(int i=1;i<=n;i++)
	  ans=max(ans,Min[c[i]]);
	write(ans);
	return 0;
}
```

---

## 作者：xu_zhihao (赞：0)

### 题目理解：
   - 我写的方案是用 map 统计每种豆子的最小美丽值，再用 把整个 map 塞进 pair 类型的 vector 里，再给 vector 排序，最后输出最大魅力值即可。思路还是非常简洁的。
   
### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>mp;
int a[210010];
int c[210010];
bool cmp(pair<int,int> a,pair<int,int> b)
{
	return a.second>b.second;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>c[i];
		int p=mp[c[i]];
		if(!p)mp[c[i]]=a[i];
		else mp[c[i]]=min(p,a[i]); 
	}
	vector<pair<int,int>>v(mp.begin(),mp.end());
	sort(v.begin(),v.end(),cmp);
	cout<<(v.begin())->second;
}
```

[AC 记录](https://atcoder.jp/contests/abc348/submissions/52092244)

---

## 作者：Hughpig (赞：0)

一个显然的想法是把记录每个颜色为 $C_i$ 的 $A_i$ 的最小值，最后扫一遍所有的 $A_i$ 最小值找最大的。可惜 $1\le A_i,C_i\le 10^9$，数组开不下。

但是我们可以对 $C_i$ 进行离散化，把所有 $C_i$ 映射到 $[1,N]$ 内。然后就可以直接记录 $A_i$ 最小值啦。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=200007;
int n,color[N],Min[N],prea[N],ans;

struct node{
	int a,c;
	friend bool operator <(node a,node b){
		if(a.c==b.c)return a.a<b.a;
		return a.c<b.c;
	}
	friend bool operator ==(node a,node b){
		return a.a==b.a&&a.c==b.c;
	}
}bean[N];

int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)Min[i]=INT_MAX;
	for(int i=1;i<=n;++i)cin>>bean[i].a>>bean[i].c,color[i]=bean[i].c,prea[i]=bean[i].a;
  	//离散化，把 C_i 映射到 1~N 之间。
	sort(bean+1,bean+n+1);
	n=unique(bean+1,bean+n+1)-bean-1;
	for(int i=1;i<=n;++i){
		color[i]=lower_bound(bean+1,bean+n+1,node{0,color[i]})-bean;
	}
	for(int i=1;i<=n;++i)bean[i].c=color[i],bean[i].a=prea[i];
	for(int i=1;i<=n;++i){
		Min[bean[i].c]=min(Min[bean[i].c],bean[i].a);//找到颜色为 C_i 的 A_i 最小值。
	}
	for(int i=1;i<=n;++i)ans=max(ans,Min[bean[i].c]);
	cout<<ans;
	return 0;
}
```

---

## 作者：hsr_ray_kkksc03 (赞：0)

# [ABC348C] Colorful Beans 题解
## 思路

考虑用数组存储每种颜色的豆子美味程度的最小值，再求整个数组美味程度的最大值。

但是注意到数据量，直接开数组会 MLE，所以用 map 动态存储。

## code

```cpp
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
int n;
map<int,int> mp;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int a,c;
		scanf("%d%d",&c,&a);
		if(mp[a]==0) mp[a]=0x7fffffff;
		mp[a]=min(mp[a],c);
	}
	int ans=-0x7fffffff;
	for(map<int,int>::iterator it=mp.begin();it!=mp.end();it++){
		ans=max(ans,it->second);
	}
	printf("%d",ans);

	return 0;
}
```

---

## 作者：int_stl (赞：0)

### 形式化题意
先分别求不同颜色的豆子美味度最小值，然后取最大值即可。

### 代码实现

```cpp
#include <iostream>
#include <map>
#define int long long
using namespace std;
int n;
map <int, int> mp;
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int a, c;
		cin >> a >> c;
		if (!mp[c]) mp[c] = 1e10;
		mp[c] = min(mp[c], a);
	}
	int maxn = -1;
	for (pair <int, int> a : mp) {
		maxn = max(maxn, a.second);
	}
	cout << maxn;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

发现 $n \leq 200000$，也就是最多只有 $200000$ 种颜色的扁豆。

然后，开一个 map 存储每种颜色在颜色数组中映射到的编号。

每次记录时，若在 map 中没有记录，则将颜色总数 $cnt$ 加上 $1$，在 map 中进行记录，然后把对应映射编号上的值设为当前扁豆的美味值。

若在 map 中有记录，则直接把对应映射编号上的值与当前扁豆美味值取最小值即可。

代码很短。

```cpp
#include <iostream>
#include <map>
using namespace std;

int n, a[200005], b[200005], cnt;
map <int, int> mp;

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) b[i] = 1000000000;
	for(int i = 1; i <= n; i++) {
		int x;
		cin >> a[i] >> x;
		if(!mp[x]) mp[x] = ++cnt;
		b[mp[x]] = min(b[mp[x]], a[i]);
	}
	int maxn = 0;
	for(int i = 1; i <= cnt; i++) {
		maxn = max(maxn, b[i]);
	}
	cout << maxn;
}
```

---

## 作者：jess1ca1o0g3 (赞：0)

[Portal(AT)](https://atcoder.jp/contests/abc348/tasks/abc348_c)

[Portal(Luogu)](https://www.luogu.com.cn/problem/AT_abc348_c)

~~数据好吓人（~~

翻译说最小美味度最大，以为是个二分答案。

仔细分析，定义豆子结构体，分别存颜色和美味度。

要得到每一种豆子的最小美味度，给结构体按照颜色为第一顺序，每味度为第二顺序排序。

这样可以把每种颜色的豆子分出来，大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/m23a0opz.png)

这样就可以得到每种豆子美味度最小值，再求它们当中的最大值即可。

[代码](https://paste.ubuntu.com/p/v5nMs8KNBq/)。

---

## 作者：___nyLittleT___ (赞：0)

# 思路
按颜色分类，求出每一个颜色的最小值，最后再求最小值。  
首先想到 `map` 来存储，只不过要求最小值，`map` 该怎么初始化呢？  
直接舍弃这个想法，接下来我想到用排序按颜色排序，颜色相同的以美味度排序，那么在每一个分界点，也就是 $c_i≠c_{i-1}$ 时，用数组记录每个颜色的首个美味度（因为排过序，所以首个就是最小值），最后再求出最小值。  

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;

struct col{
	int a;
	int c;
}b[200005];
bool cmp(col oO,col Oo){
	if(oO.c!=Oo.c) return oO.c<Oo.c;
	return oO.a<Oo.a;
}

map<int,int>mina;
int idx;

int find(int sta,int key){//跳到下一个分界点
	for(int i=sta;i<=n;i++)
		if(b[i].c>key) return i;
	return -1;//没有分界点了，代表结束
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&b[i].a,&b[i].c);
	sort(b+1,b+1+n,cmp);//排序
	int las=-1;//记录上一个颜色
	for(int i=1;i<=n;){
		if(b[i].c!=las){
			//分段
			mina[++idx]=b[i].a;
			las=b[i].c;
			int pos=find(i,las);
			if(pos==-1) break;//跳出
			i=pos;//否则直接跳过中间的
		}
	}
	int maxx=-0x7f7f7f7f;
	for(int i=1;i<=idx;i++) maxx=max(maxx,mina[i]);
	printf("%d",maxx);
	return 0;
}
```

---

## 作者：_KHIN (赞：0)

## 思路
一看题：

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ A_i\ \leq\ 10^{9} $
- $ 1\ \leq\ C_i\ \leq\ 10^{9} $

~~有点吓人~~

别慌，我们认真看一眼题目描述，发现只要求出每种豆子的最小美味值，然后在他们里取最大值即可。

啥？就这？显然不是的。由于 $ 1\ \leq\ C_i\ \leq\ 10^{9} $，如果我们暴力记录所有颜色，肯定会炸。

显然，最多会出现 $2\times10^{5}$ 种颜色，那么我们可以使用 map 来代替数组，这样就能 AC 了。

## code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005],c[200005],ans=-10000000;
map<int,int> minn;//用map
signed main()
{
 	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>c[i];
		minn[c[i]]=1e9;//由于是取min，所以初始值要赋成一个巨大的数
	}
	for(int i=1;i<=n;i++)
	{
		minn[c[i]]=min(minn[c[i]],a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,minn[c[i]]);
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：2011FYCCCTA (赞：0)

[原题](https://www.luogu.com.cn/problem/AT_abc348_c)

---
### 思路

数据范围很吓人，但也只是吓吓人而已。

记录一下每种颜色的最小值，但由于 $1 \le C_i \le 10^9$ 的数据范围需要用到 `map` 记录，最后遍历一下求最大值即可。

---
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , a[200005] , c[200005],ans;
map<int , int> mc;
int main()
{
    cin >> n;
    for (int i = 1 ; i <= n ; i++)
    {cin >>a[i]>>c[i]; mc[c[i]] = (mc[c[i]] ==0?a[i]:min(mc[c[i]] , a[i]));}

    for (auto i : mc) ans = max(ans , i.second);
    cout<<ans;
    return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

不难得到答案就是**每种**颜色的豆的**最小值**的**最大值**，但是 $1\le a_i , c_i\le 10^9$，如果直接用数组保证你会 $\texttt{MLE}$。

因此考虑使用 $\texttt{map}$。

用 $mp_i$ 表示颜色为 $i$ 的豆子的最小值，如果 $mp_i = 0$，直接赋值；否则比较最小值。

最后再从所有豆子的颜色中找最大值即可。

[Code。](https://atcoder.jp/contests/abc348/submissions/52138813)

---

## 作者：coderJerry (赞：0)

### 题目描述：[传送门](https://www.luogu.com.cn/problem/AT_abc348_c)
### 题目分析
别被题目的最大最小值骗了！不是二分。就是个简单的 ```map```，输入的时候就处理出一种颜色最小的是哪一个丢进 ```map``` 里，最后再扫一遍整个 ```map``` 找出最大值输出即可。
### AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
map<int,int> mp;
int n,a,c[200010],ans=-1;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a>>c[i];
        if(!mp.count(c[i])) mp[c[i]]=a;
        else mp[c[i]]=min(mp[c[i]],a);
    }
    for(auto it:mp) ans=max(ans,it.second);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：dwr_2011 (赞：0)

这道题呢思路很简单，就是说代码能力需要高一些。
# 思路
首先呢我们把颜色排一遍序，这样颜色相同的糖就挨一起了，然后枚举每个糖果，相同颜色的取最小，与前面不同时取哪种糖果的最小美味值最大就行了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	long long a,b;
}a[200010];
bool cmp(node a,node b)
{
	return a.b<b.b;
 } 
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].a>>a[i].b;
	}
	sort(a+1,a+n+1,cmp);
	long long maxn=0,ans=0;
	for(int i=1;i<=n+1;i++)
	{
		if(a[i].b!=a[i-1].b)
		{
			maxn=max(maxn,ans);//不相同的取最大，计算答案。
			ans=a[i].a;
		}
		else
		{
			ans=min(ans,a[i].a);//相同糖果取最大。
		}
	}
	cout<<maxn;
	return 0;//华丽结束
}

```

---

