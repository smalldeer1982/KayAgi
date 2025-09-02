# DZY Loves Chemistry

## 题目描述

DZY loves chemistry, and he enjoys mixing chemicals.

DZY has $ n $ chemicals, and $ m $ pairs of them will react. He wants to pour these chemicals into a test tube, and he needs to pour them in one by one, in any order.

Let's consider the danger of a test tube. Danger of an empty test tube is $ 1 $ . And every time when DZY pours a chemical, if there are already one or more chemicals in the test tube that can react with it, the danger of the test tube will be multiplied by $ 2 $ . Otherwise the danger remains as it is.

Find the maximum possible danger after pouring all the chemicals one by one in optimal order.

## 说明/提示

In the first sample, there's only one way to pour, and the danger won't increase.

In the second sample, no matter we pour the $ 1 $ st chemical first, or pour the $ 2 $ nd chemical first, the answer is always $ 2 $ .

In the third sample, there are four ways to achieve the maximum possible danger: 2-1-3, 2-3-1, 1-2-3 and 3-2-1 (that is the numbers of the chemicals in order of pouring).

## 样例 #1

### 输入

```
1 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 1
1 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 2
1 2
2 3
```

### 输出

```
4
```

# 题解

## 作者：GeChang (赞：2)

# CF445B 【DZY Loves Chemistry】
~~说句闲话，dzy一定卒的很惨。~~
## 1.思路
这道题先用并查集理清化学药品中的反应关系，然后再根据关系的多少与数量来计算最大危险值即可。

其中，稍作分析就可以得出，加入药品的顺序并不一定影响危险值。

先以一组数据为例：
```
3 3
1 2
2 3
1 3
```
此时 `1` 能与 `2` 反应， `2` 能与 `3` 反应，而此时 `1` 与 `3` 一定能发生反应，这也就代表最后一组 `1 3` 是重复的，并不能增加危险值，故边合并并查集边更新危险值就可以了。

## 2.代码
注释见代码。
```cpp
#include<bits/stdc++.h> //万能头文件大法好呀
#define ll long long //个人习惯
using namespace std;
ll n,m,wei=1,x,y,p[10010]; //p是并查集数组，wei是危险值
ll getroot(ll k) //并查集“找父亲”函数
{
	if(p[k]==k) return k;
	p[k]=getroot(p[k]); //路径压缩
	return p[k];
}
int main()
{
	cin>>n>>m; //读入
	for(ll i=1;i<=n;i++) p[i]=i; //初始化并查集
	for(ll i=1;i<=m;i++)
	{
		cin>>x>>y; //输入关系
		ll root_x=getroot(x),root_y=getroot(y); //找到父节点
		if(root_x!=root_y)
		{
        		p[root_x]=root_y; //合并
           		wei*=2; //计算危险值
		}
	}
	cout<<wei<<endl; //输出
	return 0; //结束qwq
}
```


# 莫抄袭，没了AC记录，空悲切！
~~话说这题这么水还有谁会看题解？~~

---

## 作者：qifan_maker (赞：1)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/CF445B)

[Codeforces](https://codeforces.com/contest/445/problem/A)
### 题目解法
我们需要用到并查集算法。并查集算法比较简单，这里就不过多介绍了，不了解的朋友可以去 [OI-wiki](https://oi-wiki.org/ds/dsu/) 看看。

---

举个例子：
```
3 3
1 2
2 3
1 3
```
$1$ 和 $2$ 会反应，危险值为 $1\times2=2$；

$2$ 和 $3$ 会反应，危险值为 $2\times2=4$；

$1$ 和 $3$ 会反应，但重复了，危险值不变。

很容易想到这道题可以用并查集，如果两个数会反应，就将它们合并，危险值翻倍，但如果它们的父亲相同，说明这个反应是重复的，危险值不变。
### [AC](https://www.luogu.com.cn/record/108628197) Code
```cpp
/*
题目编号：
B. DZY Loves Chemistry
By：
qifan_maker
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;
ll fa[100];
ll sum=1;
void init(){
	for (int i=1;i<=n;i++){
		fa[i] = i;
	}
}
int find(int i){
    if (fa[i] == i){
        return fa[i];
    }
    fa[i] = find(fa[i]);
    return fa[i];
}
void merge(int a,int b){
    int i=find(a);
    int j=find(b);
    if (i != j){
        fa[i] = j;
    	sum *= 2;
    }
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	init();
	while (m--){
		int x,y;
		cin >> x >> y;
		merge(x,y);
	}
	cout << sum;
	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：1)

图的遍历。

既然 $x_i$ 和 $y_i$ 可以互相反应，那我们可以在 $x_i$ 和 $y_i$ 之间连一条无向边，那么我们就会有 $s$ 个连通块，当一个连通块中的一个点被放入烧杯后，如果这个连通块内没有任何一个点被放入，那么危险值不变，否则危险值乘 $2$，所以答案为 $2^{n-s}$，可以使用图遍历的方式记录连通块，复杂度 $\mathcal{O}{(n+m)}$。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back 
using namespace std;
typedef long long ll;
const int maxn=55;
ll n,m,s,vis[maxn];
vector<ll> edge[maxn];
void dfs(ll u){
	vis[u]=1;
	for(auto v:edge[u]){
		if(!vis[v]) dfs(v);
	}
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	ll T=1;
	//cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n>>m;
		ll u,v;
		for(int i=1;i<=m;i++){
			cin>>u>>v;
			edge[u].pb(v),edge[v].pb(u);
		}
		s=0;
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				s++;
				dfs(i);
			}
		}
		cout<<(1ll<<(n-s))<<"\n";
	}
	return 0;
}
```

---

## 作者：linyinuo2008 (赞：1)

大家好，我又来水题解喽。


~~首先，这道题的名字别有深意（自行分析）。~~

我们一起来看一看。
# 1、题目分析

这道题想法很自然，把所有互为危险混合物的物质放到一个并查集里面，然后每次输入时看这两个物质是否已在一棵树里面。


两个要点：

- 必须开 $long$ $long$ 。

- 放入顺序并不一定影响危险值。

我们以一组数据为例：
```
5 3
2 4 
1 4
2 5
```
这说明`2`和`4`能反生反应，`2`和`5`能发生反应，推出`4`和`5`能反应，但是`5`放入时只需和`2`反应，不再和`4`反应。

所以每次放入前先判断一下这两个物质是不是已在同一棵树中就可以了。

# 2、代码

```cpp
#include <iostream>
using namespace std;
long long father[51],n,m;
long long ans=1;
long long getfa(long long a)
{
	if(father[a]==a)
	{
		return a;
	}
	return father[a]=getfa(father[a]);
}
int main()
{
	long long i,p,q,rp,rq;
	cin>>n>>m;
	for(i=1;i<=n;i++) 
	{
		father[i]=i;//初始化father数组
	}
	for(i=1;i<=m;i++)
	{
		cin>>p>>q;
		rp=getfa(p);
		rq=getfa(q);//找祖先
		if(rp!=rq){//在一棵树里就不必再加危险值了
			father[rp]=rq; 
			ans*=2;
		}
	}
	cout<<ans;
	return 0;
}
```

管理员大大求通过！
## 若有错误，欢迎指出！



---

## 作者：xiaofeng_and_xiaoyu (赞：0)

并查集的裸题，作为刚学完并查集的我，肯定要来~~水题解~~练练手了。

只需要查他们是不是反应过就可以，可以就 $ans \times2$，反应过就下一个。

没有什么大问题，直接给出代码：

```cpp
#include<iostream>
using namespace std;
int l[2002000];//保险导致贡献一发空间最劣解
int find(int x){
	if(l[x]==x)return x;
	return l[x]=find(l[x]);//并查集查找
}
int main(){
	long long int a1,a2,ans=1;
	cin>>a1>>a2;
	for(int i=1;i<=a1;i++){
		l[i]=i;//基本赋值
	}
	for(int i=1;i<=a2;i++){
		int b,c;
		cin>>b>>c;
		if(find(b)!=find(c)){
			l[find(b)]=find(c);
			ans*=2;
		} 	
	}
	cout<<ans<<endl;
	return 0;
}

```
最后吐槽一句，为什么要求最大值啊，明明在现实中要想法缩小危险值啊。

---

## 作者：Wy_x (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF445B)

## Solution:

并查集裸题。

从 $1$ 到 $m$ 枚举，判断编号为 $i$ 两种物质是否反应过（是否在一个并查集里），是则跳过，反之将这两个点所在的集合合并，并更新答案。

注意：

- 要**初始化并查集**。

- $\text{ans}$ **初值**要设为 $1$，以后的 $\times 2$ 操作才会生效。

- 因为 $1 \le n \le 50$，所以**答案最大为** $2^{49}$，**需要开** $\text{long long}$。

## Code:

```cpp
#include<bits/stdc++.h>   //万能头文件  
#define int long long
using namespace std; 

int f[1<<20];

void init(int x) //初始化函数
{
	f[0]=0;
	for(int i=1;i<=x;i++)
	{
		f[i]=i;//一开始，每个节点的爸爸都是它本身
	}
}

int find(int x) //找爸爸函数
{
	if(f[x]==x) return x;
	return f[x]=find(f[x]);//路径压缩
}

void merge(int x,int y) //加点函数
{
	int fx=find(x),fy=find(y);
	if(fx==fy) return;
	f[fx]=fy;
}

int n,m,ans=1;
struct R { int u,v,w; } a[1<<20];

signed main()
{
	cin>>n>>m;
	
	init(n);//初始化，有 n 个点的并查集
	
	for(int i=1;i<=m;i++) cin>>a[i].u>>a[i].v;
		
	for(int i=1;i<=m;i++)
	{
		int fx=find(a[i].u);
		int fy=find(a[i].v);//找这两个点的爸爸
		if(fx!=fy)
		{
			f[fx]=fy;// 合并集合
			ans<<=1; //ans*=2，计算答案
		}
	}
	
	cout<<ans;
	
	return 0;
}
```

---

## 作者：青龍剑 (赞：0)

~~话说我这个小蒟蒻刚刚连蒙带骗过了这道题就恬不知耻地写题解真不要脸~~

简单说一下吧

相信所有来看题解的都是没有思路的⑧

我最开始就没有任何思路，经大佬点拨才明白。

分析第三组数据就可以知道可反应的几对化学药品的放置顺序互不影响，但不可反应的是要有特定顺序的。

我们就可以不用管不能反应的几对，直接利用可以反应的建一个并查集，可以反应就连线。这样，所有线段的数量就是乘以二的次数。

接下来奉上代码

```cpp
#include<bits/stdc++.h> //我不管比赛限制我就喜欢他
using namespace std;
long long n,m,st[1000005],x,y,ans=1;
long long getroot(long long k) //传统美德
{
	if(st[k]==k) return k;
	st[k]=getroot(st[k]); //递归
	return st[k];
}
int main()
{
	cin>>n>>m;
	for(long long i=1;i<=n;i++) st[i]=i; //初始化
	for(long long i=1;i<=m;i++)
	{
		cin>>x>>y;
		long long ax=getroot(x),ay=getroot(y); //找呀找呀找爸爸
		if(ax!=ay)
		{
			st[ax]=ay; //合并并查集
			ans=ans*2; //乘2操作
		}
	}
	cout<<ans;
	return scan; //结束
}
```

代码写完才发现超级短

~~盲猜DZY这个名字有别的含义？？？~~

好吧再见。

OwO

---

## 作者：codeLJH114514 (赞：0)

[Problem](https://www.luogu.com.cn/problem/CF445B)

## $\textbf{Problem}$

DZY 有 $n$ 种物质，其中某些物质与另外的物质会发生反应，如果加入的某个物质至少与已加入的一种物质发生反应，那么危险值乘以 $2$，危险值初始为 $1$。

求所有物质加入完毕后最大的危险值。

## $\textbf{Data}$

$1 \le n \le 50, 0\le n \le \frac{n(n - 1)}{2}$。

## $\textbf{Solution}$

把所有能互相发生反应的物质定成一个连通块，易知一个连通块会让危险值乘以 $2^{k - 1}$（$k$ 是连通块大小）。

使用并查集维护这些连通块即可，对于新加进来的边，如果边的两边已在一个连通块，则这条边没有意义（因为通过之前已经能知道这两个物质能发生反应了），否则危险值 $\times 2$。

算法时间复杂度：$\mathcal{O}(m \log_2 n)$。

注意，本题中 $\max{n} = 50$，如果这五十个物质都在一个连通块内，则答案是 $2^{49}$，显然会 $32$ 位整形变量是存不下的，需用 $64$ 位整型变量（$32$ 位有符号整形最大值为 $2^{31} - 1 < 2^{49}$，$64$ 位有符号整形最大值是 $2^{63} - 1 > 2^{49}$）。

## $\textbf{Code}$

```cpp
#include <iostream>
#define maxn 64
#define int int64_t
int n, m, x, y, A;
int f[maxn], s[maxn];
int Root(int);
void Union(int, int);
signed main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        f[i] = i,
        s[i] = 1;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y;
        int Fx = Root(x), Fy = Root(y);
        if (Fx != Fy) {
            Union(x, y);
            A += 1;
        }
    }
    std::cout << (1LL << A);
    return 0;
}
int Root(int x) {
    if (f[x] == x)
        return x;
    return f[x] = Root(f[x]);
}
void Union(int x, int y) {
    x = Root(x), y = Root(y);
    if (s[x] > s[y]) {
        s[x] += s[y];
        f[y] = x;
    } else {
        s[y] += s[x];
        f[x] = y;
    }
}
```

---

