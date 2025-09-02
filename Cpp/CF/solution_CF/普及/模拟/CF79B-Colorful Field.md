# Colorful Field

## 题目描述

## 题意简述

给出一个 $n \times m$ 的矩阵，当中有 $k$ 个点是坏的。然后按照 **从上往下，从左往右** 的顺序依次填入胡萝卜、奇异果和葡萄（英文分别为 $\mathtt{Carrots}$、$\mathtt{Kiwis}$ 和 $\mathtt{Grapes}$ ）。当然，坏掉的点无法填入东西，也不参与填入矩阵的次序。

现给你 $t$ 次询问，每次给出一对数 $i$ 和 $j$，请输出矩阵第 $i$ 行第 $j$ 列所填的物品。（ **如果这一个点是坏的点，则输出**$\mathtt{Waste}$）

## 说明/提示

$1 \le n,m \le 4\cdot10^4$，$1 \le k,t \le 10^3$

## 样例 #1

### 输入

```
4 5 5 6
4 3
1 3
3 3
2 5
3 2
1 3
1 4
2 3
2 4
1 1
1 1
```

### 输出

```
Waste
Grapes
Carrots
Kiwis
Carrots
Carrots
```

# 题解

## 作者：Ninelife_Cat (赞：1)

因为 $n$，$m$ 最大为 $4\times10^4$，所以不能直接开二维数组存。

考虑把二维的矩阵拆成一条线来做，即把矩阵的每一行接到前一行的末尾去。

当输入一个坐标时，我们先把它转成一维的点。如果这个点就是“坏掉的点”，那么直接输出，否则就统计它的前面有几个“坏掉的点”并除去。

因为“胡萝卜”、“奇异果”和“葡萄”放入的顺序是固定的，所以我们将最终得到的位置对 $3$ 取模就能判断这个位置上是什么水果了。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ri register
#define int long long
#define inf 2147483647
#define mp(x,y) make_pair((x),(y))
#define reset(x,y) memset((x),(y),sizeof((x)))
using namespace std;
inline int read()
{
	int x=0;bool f=false;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=true;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return f?-x:x;
}
inline void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
const int N=5e4+10;
int n,m,k,t,x,y,cnt,a[N];
//a数组存放"坏掉的点"的位置
signed main()
{
	n=read();m=read();k=read();t=read();
	for(ri int i=1;i<=k;++i)
		x=read(),y=read(),a[++cnt]=(x-1)*m+y;//二维转一维
	sort(a+1,a+cnt+1);//排序,便于统计
	for(ri int i=1;i<=t;++i)
	{
		x=read();y=read();
		ri int res=(x-1)*m+y,tot=0,f=0;
      		//tot记录这个点前面有几个"坏掉的点"
            	//f记录这个点是否为"坏掉的点"
		for(ri int j=1;j<=cnt;++j)
			if(a[j]<res) ++tot;
				else if(a[j]==res) {f=1;break;}
					else break;//小优化
		if(f) {cout<<"Waste\n";continue;}
		ri int p=(res-tot)%3;//该点的最终位置
		cout<<(!p?"Grapes\n":p==1?"Carrots\n":"Kiwis\n");
	}
	return 0;
}

---

## 作者：Xjin (赞：1)

# 题目描述
再一个二维平面上的 $k$ 个点坏掉了，需要再其他点上放上 Grapes，Carrots 和 Kiwis。并且询问 $t$ 次，问第 $i$ 行，第 $j$ 列上的是什么?三种水果的放置顺序是从左往右，从上往下。
# Solution
一开始是想到直接建一个二维的数组暴力模拟得出结果，但是一看数据发现存不下。后来又想到因为放水果是有一定的顺序的，所以只需要知道再这个点之前有多少个坏掉了的点，然后将未坏掉的点对 $3$ 取余数即可。为了方便操作，可以将二维的转成一维的。查找坏掉了的格子的数量时可以用一个 $b_i$ 数组记录第 $i$ 个坏掉了的格子再一维上的位置，然后排序，用二分的方式求出再 $i,j$ 点之前有多少个坏掉了的格子。就可以得出答案了。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,t;
int b[1005];
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
signed main(){
	n=read();m=read();k=read();t=read();
	for(int i=1;i<=k;i++){
		int x=read(),y=read();
		b[i]=(x-1)*m+y;	//转一维
	}
	sort(b+1,b+n+1);
	while(t--){
		int x=read(),y=read();
		int l=1,r=k;
		while(l<r){
			int mid=(l+r)>>1;
			if(b[mid]>=(x-1)*m+y)r=mid;
			else l=mid+1;
		}//进行二分答案
		int tot=(x-1)*m+y;
		if(tot==b[r]){printf("Waste\n");continue;}
		tot=tot-r+1;
		if(tot%3==0)printf("Grapes\n");
		else if(tot%3==1)printf("Carrots\n");
		else if(tot%3==2)printf("Kiwis\n");
	}
	return 0;
}
```


---

## 作者：Chenyichen0420 (赞：0)

# 简要题意：

给你一个 $n$ 行 $m$ 列的矩阵，让你按照先从左到右，再从上到下的顺序以 $\mathtt{Carrots},\mathtt{Kiwis},\mathtt{Grapes}$ 的循环进行填充。遇到“坏掉”的格子就跳到下一格。问你 $(i,j)$ 位置的格子是什么。

# 思路分析：

首先，如果不考虑坏掉的格子应该都会做吧？$(i-1)\times m+j$ 就是这个格子再填充顺序中的个数（从 $1$ 开始）。

那么，我们只要能求出这个格子前有多少个坏掉的格子就行了。

观察数据范围，$n,m\le4\times10^4$，不能直接预处理到具体的每一个格子，但是 $k,t\le10^3$，这也就意味着我们每一次都暴力枚举这个格子前面有多少个坏掉的格子是可行的。在他前面的格子就是 $i_0<i$ 或者 $i_0=i$ 且 $j_0<j$ 的。本身是不是坏掉的顺便就判了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define make_pair(a,b) a*(n+m)+b
int n,m,k,t,x,y,a[1005],b[1005];
inline void rk(int v){
	if(v==1) puts("Carrots");
	else if(v==2) puts("Kiwis");
	else if(v==0) puts("Grapes");
	else puts("Waste");
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>k>>t;
	for(int i=1;i<=k;++i)cin>>a[i]>>b[i];
	for(int i=1;i<=t;++i){
		cin>>x>>y; int cnt=x*m-m+y; bool ok=1;
		for(int j=1;j<=k;++j){
			if(a[j]<x||a[j]==x&&b[j]<y) cnt--;
			else if(a[j]==x&&b[j]==y) ok=0;
		}
		if(ok) rk(cnt%3);
		else rk(3);
	}
	return 0;
} 
```

---

## 作者：Mioko_Sakurauchi (赞：0)

# Colorful Field
## 题意再述
给出一个 $n \times m$ 的矩阵，当中有 $k$ 个点是坏的。然后按照 **从上往下，从左往右** 的顺序依次填入胡萝卜，奇异果和葡萄（英文分别为 $\mathtt{Carrots}$、$\mathtt{Kiwis}$ 和 $\mathtt{Grapes}$ ）。当然，坏掉的点无法填入东西，也不参与填入矩阵的次序。

现给你 $t$ 次询问，每次给出一对数 $i$ 和 $j$，请输出矩阵第 $i$ 行第 $j$ 列所填的物品。**如果这一个点是坏的点，则输出** $\mathtt{Waste}$。


------------

## 思路：

看到这题的第一眼：~~暴力启动！~~

后来想了想：不对，有问题！数据范围  $1≤n,m≤4 ⋅ 10^4 $，如果暴力，不管是时间还是空间，都会爆炸，怎么办？

其实思路并不难想，我们只需要把 $\mathtt{Waste}$ 都给用一维数组标记出来，然后当询问的时候进行二分查找判断是否是坏的即可，果蔬的种类直接使用当前编号减去坏点编号再取模就可以知道当前的编号。


------------

## 代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#define ll long long
using namespace std;
const int  maxn = 1e5;
ll a[maxn];
ll n, m,k,t;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') if(c=='-') {f=-1;c=getchar();	}
	while(c>='0' and  c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
int  main()
{
	n=read();
	m=read();
	k=read();
	t=read();
	for(int i=1;i<=k;i++)
	{
		ll x,y;
		x=read();
		y=read();
		a[i]=(x-1)*m+y;
	}
		sort(a+1,a+k+1);
	while(t--)
	{
		int x, y, id, l, r, cnt;
		bool waste=false;
		x=read();
		y=read();
		id=(x-1)*m+y;
		l=0, r=k;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if (a[mid]==id)
			{
				waste = true;
				break;
			}
			if (a[mid]>id) 
			{
				r=mid-1;
			}
			else
			{
				l=mid+1;
				cnt=mid;
			}
		}
		id-=cnt;
		if (waste) cout<<"Waste"<<endl;
		else if (id%3==0) cout<<"Grapes"<<endl;
		else if (id%3==1) cout<<"Carrots"<<endl;
		else cout<<"Kiwis"<<endl;
	}
}

```


---

## 作者：block_in_mc (赞：0)

## 题意简述

在一张 $n\times m$ 的图上有 $k$ 个点坏掉了。除去坏掉的点，按从上到下，从左到右的顺序填入 `Carrots`，`Kiwis`，`Grapes`。进行 $t$ 次询问 $x,\ y$，输出 $(x,\ y)$ 处的水果。如果是坏掉的点，输出 `Waste`。

## 思路

首先考虑暴力枚举出每一个位置上的水果是什么。时间复杂度 $O(nm+t)$，空间复杂度 $O(nm)$，很明显过不了 $4\times10^4$。

因为放水果具有一定的顺序，我们可以看这个点前有几个没有坏掉的点，对 $3$ 取模，根据不同的结果输出答案。

空间上，我们可以存储坏掉的点的位置。这里使用 $(x-1)m+y$ 把点 $(x, y)$ 转化为一个数。你也可以使用结构体存储。

如果直接枚举，时间复杂度为 $O(tk)$。**这样就可以过了**。（不知道为什么其他题解都说要二分）

还可以继续优化，考虑二分。由于输入顺序的不确定性，我们需要先排序。在每次查询时，通过所有坏掉的点的坐标二分求出当前点前面的坏掉的点的数量。注意如果二分时发现当前点是坏掉的点，直接输出 `Waste` 即可。时间复杂度 $O(t\log k)$。

## 代码

先给出 $O(tk)$ 的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k, t, x, y, b[1001];
int main() {
	scanf("%d%d%d%d", &n, &m, &k, &t);
	for (int i = 1; i <= k && scanf("%d%d", &x, &y); i++) b[i] = (x-1) * m + y;
	sort(b + 1, b + k + 1);
	for (int i = 1; i <= t; i++) {
        scanf("%d%d", &x, &y);
		bool done = false;
		int idx, cnt=0;
        idx = (x - 1) * m + y;
        for (int j = 1; j <= k; j++) {
            if (b[j] < idx) cnt = j;
            else if (b[j] == idx) done = true;
            else break;
        }
        idx -= cnt;
		if (done) printf("Waste\n");
		else if (idx % 3 == 0) printf("Grapes\n");
		else if (idx % 3 == 1) printf("Carrots\n");
		else if (idx % 3 == 2) printf("Kiwis\n");
	}
}
```

改成 $O(t\log k)$ 也很简单：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k, t, x, y, b[1001];
int main() {
	scanf("%d%d%d%d", &n, &m, &k, &t);
	for (int i = 1; i <= k && scanf("%d%d", &x, &y); i++) b[i] = (x-1) * m + y;
	sort(b + 1, b + k + 1);
	for (int i = 1; i <= t; i++) {
        scanf("%d%d", &x, &y);
		bool done = false;
		int l = 0, r = k, mid, idx, cnt;
        idx = (x - 1) * m + y;
		while (l <= r) {
			mid = (l + r) / 2;
			if (b[mid] == idx) { done = true; break; }
			if (b[mid] > idx) r = mid - 1;
			else l = mid + 1, cnt = mid;
		}
        idx -= cnt;
		if (done) printf("Waste\n");
		else if (idx % 3 == 0) printf("Grapes\n");
		else if (idx % 3 == 1) printf("Carrots\n");
		else if (idx % 3 == 2) printf("Kiwis\n");
	}
}
```

---

## 作者：ask_silently (赞：0)

## 题目简述
有一张 $n \times m$ 的图，其中有 $k$ 个点坏了,让我们在图上按照顺序放入三种水果，然后询问 $t$ 次位置，输出当前位置放入的水果。

## 思路
- 万事万物先暴力。看一眼数据范围，肯定会超时和超空间，所以我们不能开枚举位置的数组，只能开一个记录坏掉的点的位置的数组。于是我们想到要把数组变成一维，就是把下面的横向图拼到上面去，这样就不会超空间了。

- 那超时该怎么解决呢。题目上说了，三种水果是顺序排放，所以我们可以先求出离当前位置最近的一个坏掉的点的一维编号，然后用当前编号减去坏点编号再取模 $3$ 就可以知道当前的水果了。如果当前这个坏点就是自己的话，那就输出 `Waste` 。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,t;
int a[1010];
int main(){
	scanf("%d%d%d%d",&n,&m,&k,&t);
	for(int i=1;i<=k;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		a[i]=(x-1)*m+y;//变成一维数组 
	}
	sort(a+1,a+1+n);//二分的前提是要有序 
	while(t--){
		int x,y;
		scanf("%d%d",&x,&y);
		bool flag=false;
		int l=1,r=k,mid,z=(x-1)*m+y;
		while(l<r){
			mid=(l+r)/2;
			if(a[mid]>=z) r=mid;
			else l=mid+1;
		}//二分求出离自己最近的一个坏点编号 
		if(a[l]==z){
			printf("Waste\n");
			continue;
		}//是自己输出 
		if((z-l+1)%3==0) printf("Grapes\n");
		else if((z-l+1)%3==1) printf("Carrots\n");
		else printf("Kiwis\n");
		//否则取模3 
	}
	return 0;
}

```


---

## 作者：Fislett (赞：0)

[无耻地宣扬一下我的博客](https://tongyuxin.blog.luogu.org/)
# 1. 题意
有一个 $n \times m$ 的矩阵，有 $k$ 个点坏掉了不能种东西，其余的点按照从上往下，从左往右的顺序依次填入胡萝卜、奇异果和葡萄。有 $t$ 次询问，每次询问输入一个坐标，输出这个坐标上种的是什么。
# 2.思路
我们可以把二维的矩阵拆成一维的一条线，同时将坏掉了的点按照它在这条线中的坐标排序，询问时通过二分查找这个点前面离它最近的坏掉了的点，而这个点在坏节点中的编号就是询问的点前面坏接点的数量。知道了前面有几个坏节点，其余的就可以用周期问题的思想愉快的解决了！
# 3.代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k, t, bad[1001];
int main()
{
	scanf("%d%d%d%d", &n, &m, &k, &t);
	for (int i = 1; i <= k; i ++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		bad[i] = (x - 1) * m + y;
	}
	sort(bad + 1, bad + k + 1);
	while (t --)
	{
		int x, y, id, l, r, cnt;
		bool waste = false;
		scanf("%d%d", &x, &y);
		id = (x - 1) * m + y;
		l = 0, r = k;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (bad[mid] == id)
			{
				waste = true;
				break;
			}
			if (bad[mid] > id) r = mid - 1;
			else
			{
				l = mid + 1;
				cnt = mid;
			}
		}
		id -= cnt;
		if (waste) printf("Waste\n");
		else if (id % 3 == 0) printf("Grapes\n");
		else if (id % 3 == 1) printf("Carrots\n");
		else printf("Kiwis\n"); 
	}
}
```

---

## 作者：LaDeX (赞：0)

## 题意 

一个 $n \times m$ 的矩阵，其中 $k$ 个点是坏的。按 **从上到下，从左到右** 的顺序填入字符串，为 $\mathtt{Carrots}$，$\mathtt{Kiwis}$ 和 $\mathtt{Grapes}$ 循环，填入时如果遇到坏的点就跳过。

$T$ 个询问，输入 $x,y$，输出矩阵中第 $x$ 行，第 $y$ 列的字符串。

## 解法

一看题都能想到开一个二维数组，但是 $1 \leq n, m \leq 4\times10^4$，时间复杂度 $O(nm)$，空间复杂度 $O(nm)$ 开不下，所以要优化。

由于是 $3$ 个字符串循环，所以 很容易想到计算出 这个点 是填入时的 第几个点，再模 $3$，输出余数对应的字符串即可，如果该点是坏的，就输出 $\mathtt{Waste}$。

本人先求出每一行有几个 **非坏的** 点，再前缀和，求出从第一行到这一行有几个 **非坏的** 点，再是用 二维 `vector` 存每一行的 **坏** 的点 的位置，再每一行排序。

对于每一次查询，只要算出该点是该行的第几个 **非坏的** 点，再加上从第一行到上一行一共有几个 **非坏的** 点即可。利用 **二分** 求出这一行的 **坏点** 中，$y$ 小于 该点 且最大的点的下标 加一就是该点是该行的第几个 **非坏的** 点 （**`vector` 下标从 $0$ 开始**），要特判一下该点是不是 **坏点**。

时间复杂度 $O(nlog_2n+Tlog_2k)$，空间复杂度 $O(n+k)$。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Fcin\
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
const LL N = 4e4 + 10;
LL pre[N], n, m, k, T;
vector<LL> bad[N];
string S[4] = {"Grapes", "Carrots", "Kiwis", "Waste"};

string solve(){
	LL x, y, res = 0;
	cin >> x >> y;
	res += pre[x - 1];
	LL l = 1, r = bad[x].size();
	while (l + 1 < r){
		LL mid = (l + r) >> 1;
		if (bad[x][mid - 1] >= y)
			r = mid;
		else
			l = mid;
	}
	LL X;
	if (l == 0 || r == 0){
		res += y;
		return S[res % 3];
	}
	if (bad[x][r - 1] <= y)
		X = r;
	else if (bad[x][l - 1] <= y)
		X = l;
	else{
		res += y;
		return S[res % 3];
	}
	if (bad[x][X - 1] == y)
		return S[3];
	res += y - X;
	return S[res % 3];
}

int main(){
//    Fcin;
    LL x, y;
    cin >> n >> m >> k >> T;
    for (LL i = 1; i <= n; i ++)
    	pre[i] = m;
    for (LL i = 1; i <= k; i ++){
    	cin >> x >> y;
    	pre[x] --;
    	bad[x].emplace_back(y);
	}
	for (LL i = 1; i <= n; i ++){
		pre[i] += pre[i - 1];
		sort(bad[i].begin(), bad[i].end());
	}
	while (T --){
		cout << solve() << "\n";
	}
	return 0;
}
```


---

## 作者：小杨小小杨 (赞：0)

## 题意
简洁明了，这里就不多做赘述。
## 思路
首先结构体排序，然后用二分查找距离当前的点最近的那个坏掉的格子的序号，这样就能求出有多少个格子坏掉了。    
最后用周期问题就可以愉快滴解决啦！
## Code
```cpp
#include<iostream>
#include<cstdio>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<deque>
#include<vector>
#include<queue>
#include<string>
#include<cstring>
#include<map>
#include<stack>
#include<set>
using namespace std;
int n,m,k,T,i,bao,t,w,a,b,h;
struct Node{
	int x,y;
}x[40010];
bool cmp(Node x,Node y){return x.x<y.x||x.x==y.x&&x.y<y.y;}
int main(){
	scanf("%d%d%d%d",&n,&m,&k,&T);
	for (i=1;i<=k;i++) scanf("%d%d",&x[i].x,&x[i].y);
	sort(x+1,x+k+1,cmp);
	while (T--){
		scanf("%d%d",&a,&b);
		t=1;w=k;bao=0;
		while (t<=w){
			int mid=(t+w)>>1;
			if (x[mid].x<a||x[mid].x==a&&x[mid].y<=b) bao=mid,t=mid+1;
			else w=mid-1;
		}
		if (x[bao].x==a&&x[bao].y==b) printf("Waste\n");
		else{
			h=((a-1)*m+b-bao-1)%3+1;
			if (h==1) printf("Carrots\n");
			else if (h==2) printf("Kiwis\n");
			else printf("Grapes\n");
		}
	}
	return 0;
}

```


---

