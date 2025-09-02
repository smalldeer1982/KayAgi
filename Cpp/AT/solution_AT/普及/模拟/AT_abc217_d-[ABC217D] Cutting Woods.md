# [ABC217D] Cutting Woods

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc217/tasks/abc217_d

長さ $ L $ メートルの直線状の木材があります。  
 $ x\ =\ 1,\ 2,\ \dots,\ L\ -\ 1 $ に対して、木材の左端から $ x $ メートルの地点には目印として線 $ x $ が引かれています。

$ Q $ 個のクエリが与えられます。 $ i $ 番目のクエリは数の組 $ (c_i,\ x_i) $ によって表されます。  
 以下の説明に従ってクエリを $ i $ の昇順に処理してください。

- $ c_i\ =\ 1 $ のとき : 線 $ x_i $ がある地点で木材を $ 2 $ つに切る。
- $ c_i\ =\ 2 $ のとき : 線 $ x_i $ を含む木材を選び、その長さを出力する。

ただし $ c_i\ =\ 1,\ 2 $ の両方に対して、線 $ x_i $ はクエリを処理する時点で切られていないことが保証されます。

## 说明/提示

### 制約

- $ 1\ \leq\ L\ \leq\ 10^9 $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ c_i\ =\ 1,\ 2 $ $ (1\ \leq\ i\ \leq\ Q) $
- $ 1\ \leq\ x_i\ \leq\ L\ -\ 1 $ $ (1\ \leq\ i\ \leq\ Q) $
- 全ての $ i $ $ (1\ \leq\ i\ \leq\ Q) $ に対して次が成り立つ: $ 1\ \leq\ j\ \lt\ i $ かつ $ (c_j,x_j)\ =\ (1,\ x_i) $ を満たす $ j $ は存在しない。
- 入力は全て整数である。

### Sample Explanation 1

$ 1 $ 番目のクエリ時点では木材は一度も切られていないので、線 $ 2 $ を含む木材の長さは $ 5 $ メートルです。よって $ 5 $ を出力します。 $ 2 $ 番目のクエリによって、木材は $ 3 $ メートルの木材と $ 2 $ メートルの木材に分割されます。 $ 3 $ 番目のクエリ時点では 線 $ 2 $ を含む木材の長さは $ 3 $ メートルなので、$ 3 $ を出力します。

## 样例 #1

### 输入

```
5 3
2 2
1 3
2 2```

### 输出

```
5
3```

## 样例 #2

### 输入

```
5 3
1 2
1 4
2 3```

### 输出

```
2```

## 样例 #3

### 输入

```
100 10
1 31
2 41
1 59
2 26
1 53
2 58
1 97
2 93
1 23
2 84```

### 输出

```
69
31
6
38
38```

# 题解

## 作者：ZBH_123 (赞：5)

## 题目大意
给定长为 $L$ 的序列，每次操作给定一个 $x$，将 $x$ 所在的区间 $[l,r]$ 分为 $[l,x]$ 和 $[x+1,r]$；或是给定一个 $x$，求出 $x$ 所在的区间的长度。
## 题目分析
可以维护一个 set，set 里面存放当前序列的所有的右端点。每次分裂操作时，序列的右端点就多了一个 $x$，将它放进 set。当询问操作时，在 set 中查找第一个大于等于 $x$ 的右端点，用这个点的位置减去 set 中上一个点的位置就是 $x$ 所在的区间长度。

**AC code:**
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
int s,q,op,x;
set<int>a;
int main(){
	scanf("%d %d",&s,&q);
	a.insert(0);
	a.insert(s);
	while(q--){
		scanf("%d %d",&op,&x);
		if(op==1){
			a.insert(x);
		}
		else{
			set<int>::iterator it=a.lower_bound(x);
			set<int>::iterator it2=it--;
			cout<<(*it2)-(*it)<<endl;
		}
	}
	return 0;
}
```

---

## 作者：WRuperD (赞：3)

提供一种简单易想的思路。

发现对于每个询问 $x$，只需要知道在它之前的修改的断点中比 $x$ 大的最小值和比 $x$ 小的最小值，然后相减即可。

在线做比较复杂，考虑离线。问题就变成了静态区间问题，只用查询区间前驱和后继即可，不用支持修改。

那这个东西就可以用分块解决，参考 https://loj.ac/p/6279

对于每个块内排序，块外暴力即可。

复杂度 $O(q \sqrt q)$

---

## 作者：PeyNiKge (赞：2)

### 题目大意

- 给定一个长度为 $L$ 的区间和 $Q$ 次操作，

- 每次操作需要查询 $x$ 点所在的区间的长度，

- 或是将 $x$ 所在的区间 $[l, r]$ 分成 $[l, x]$ 和 $[x + 1, r]$ 两部分。
 
### 题目分析

考虑使用 [$set$](https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=1&tn=baidu&wd=c%2B%2B%20stl%20set&fenlei=256&oq=c%252B%252Bset&rsv_pq=8756f4db00007437&rsv_t=8044h7CozVjEeeAkYurcJyilBjl%2B5cSABGQUIqcIgIlpMb5XJCDTnKmKuVI&rqlang=cn&rsv_dl=tb&rsv_enter=1&rsv_btype=t&inputT=5267&rsv_sug3=20&rsv_sug1=17&rsv_sug7=100&rsv_sug2=0&rsv_sug4=5456)，用它储存每一个区间的左端点，修改时向 $set$ 中插入 $x$，询问时在 $set$ 中找到第一个大于等于 $x$ 的数 $l$，不难发现 $r$ 即为 $x$ 所在区间的右端点坐标 $+1$，同时不难看出 $x$ 所在区间的左端点等于 $set$ 中 $r$ 的上一个数，所以我们可以计算出 $x$ 所在区间的长度。

注意我们在 $set$ 中寻找第一个大于等于 $x$ 的数时，显然不能 $O(n)$ 查找，可以使用二分，具体实现方法见代码。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
int n, q, c, x;
int l, r;
set<int>::iterator it; //迭代器
set<int>s; //set
int main(){
    scanf("%d%d", &n, &q);
    s.insert(0);
    s.insert(n);//注意这里要先插入0和n，不然有的点会算不出来。
    for(int i = 1; i <= q; i++){
        scanf("%d%d", &c, &x);
        if(c == 1){
            s.insert(x);//插入x。
        }
        else{
            it = s.lower_bound(x);//set自带的二分函数，可以找到第一个大于等于x的数的地址。
            r = *it;//取出迭代器中的值
            l = *(--it);//取出上一个迭代器中的值
            printf("%d\n", r - l);
        }
    }
    return 0;
}
```


---

## 作者：MMXIandCCXXII (赞：1)

## 思路
如果我时间复杂度肯定会超，所以，我们可以换种思路。

我们可以把每个区间的右端点，也就是输入的切割点存起来，每次**二分查找**，找到它所在的区间的右端点和前一个区间的右端点，相减便是这个区间的长度。

但是，二分要求**有序**，每次去对数组进行排序还是会超时，所以我们需要一个 set 来存储，这样就能保证它的有序性。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;

set <int> s;
set <int> ::iterator it;

int main()
{
	int l, n;
	cin >> l >> n;
	s.insert (0);
	s.insert (l);
	for (int i = 1; i <= n; i++)
	{
		int op, x;
		cin >> op >> x;
		if (op == 1)
		{
			s.insert (x);
		}
		else
		{
			it = s.lower_bound (x);
			int y = *it;
			it--;
			int z = *it;
			cout << y - z << endl;
		}
	}
	return 0;
}
```

---

## 作者：RYANGSJ (赞：1)

## 题目大意

有一条线段，每一次进行两种操作之一。

第一种操作：从 $x$ 这个点把 $x$ 所在的线段段成两段。

第二种操作：询问 $x$ 这个点所在线段的长度。

## 做法

使用 set 来维护每一条线段的端点，初始时有一条起点为 $1$ 的线段。当遇到操作一时，就把这条线段断开，也就是再加入一条端点为 $x$ 的线段。当遇到操作二时，查找第一个大于 $x$ 的线段，求出这一条线段与第一个小于这条线段的线段的差，就是查询的答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
using namespace std;
inline int read(){char ch=getchar();int f=1,res=0;while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){res*=10;res+=(ch-'0');ch=getchar();}return res*f;}
inline void write(int x){if(x<0){putchar('-'),x=-x;}if(x<=9){putchar(x+'0');}else{write(x/10);putchar(x%10+'0');}}
int n,q;
set<int>s;
signed main(){
	n=read(),q=read();
	s.insert(0);//注意要插入0和n，不然有的点无法统计答案 
	s.insert(n);
	for(int i=1;i<=q;i++){
		int opt=read();
		if(opt==1){//断开线段 
			int x=read();
			s.insert(x);
		}else{//查询所在线段 
			int x=read();
			set<int>::iterator it;
			it=s.upper_bound(x);
			int now=(*it);
			it--;
			write(now-(*it));
			puts("");
		}
	}
	return 0;
}
```


---

## 作者：_shine_ (赞：0)

看到 $1\le q\le 2\times 10^5$，显然发现查询长度必须要快，不能直接遍历，显然用预处理或内部二分来解决，这里使用二分。

下面来解决存储问题。看到 $1\le l\le 10^9$ 且输入的不保证具有单调性，显然不能使用数组或 ```map``` 存储，思考使用一种时间较低、有序的存储工具来存储，则能想到 ```map,set,priority_queue``` 来存储，但是 ```map``` 在二分寻找长度时很不便，```priority_queue``` 无法快速简便的进行二分，则显然使用 ```set```。

知道了存储问题，就好解决了。不妨在没次查询时二分第一个大于 $x$ 的左节点，这样就能算出到上一个左节点的距离了，这里要注意指针问题。
#### code
注：有些卡常，可优化或快读（```scanf``` 也行）。

[AC Records](https://atcoder.jp/contests/abc217/submissions/46227632)

---

## 作者：zhujiangyuan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc217_d)

## Description
给定一个长度为 $L$ 的序列 $[1,L]$ 和 $q$ 个询问。对于第 $i$ 次询问有一个 $c_i$ 和 $x_i$，如果 $c_i=1$，将 $x$ 点所在的区间 $[l,r]$ 分为 $[l,x]$ 和 $[x+1,r]$；如果 $c_i=2$，输出 $x$ 点所在区间的长度。

## Solution
发现序列总长度最大为 $10^9$，不好存，而且想表示出每个区间，考虑存区间的左端点和右端点。使用 STL 的 set 进行存储，这样还能自动排序+去重。初始化在 set 里插入 $0$ 和 $L$。

支持两种操作：
1. 插入操作，这时把 $x$ 点所在的区间 $[l,r]$ 分为 $[l,x]$ 和 $[x+1,r]$，这时序列中多了一个端点 $x$，所以把 $x$ 插入进 set。时间复杂度 $O(\log n)$。
2. 查询操作。使用 set 自带的 `lower_bound` 查找第一个大于等于 $x$ 的数，即为 $x$ 所在区间的右端点，记为 $a$，$a$ 在 set 中的位置减 $1$ 所对应的数，记为 $b$，$b$ 就是 $x$ 所在区间的左端点减 $1$。所以答案为 $a-b$，时间复杂度 $O(\log n)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,q;
set<int>s;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>l>>q;
	s.insert(0),s.insert(l);//set初始化 插入0和L
	while(q--)
	{
		int c,x;
		cin>>c>>x;
		if(c==1) s.insert(x);//插入端点x
		else
		{
			set<int>::iterator it=s.lower_bound(x);//迭代器it为a的位置
			int a=*it;//*it为位置it所对应的值
			it--;//位置减1
			int b=*it;//同上
			cout<<a-b<<'\n';//输出答案
		}
	}
	return 0;
}
```
总时间复杂度 $O(q\log n)$。

---

## 作者：Luxingguang (赞：0)

~~这是蒟蒻写的第六篇题解~~

[题目传送门](https://www.luogu.com.cn/problem/AT_abc217_d)

## 一、~~人话版~~题意
------------
给定一个长度为 $L$ 的区间与一个二元组 $(c,x)$。若 $c=1$
则从 $x$ 点分割。若 $c=2$ 则查询 $x$ 所在的区间的长度。

## 二、思路分析
------------
当 $c=1$ 时我们可以存储每一个断点，当 $c=2$ 时我们可以用 c++ 自带的二分下界搜索 $x$ 所在的区间。

## 三、代码实现
------------
```cpp
#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
int l,q,c,x;
set<int> s;
signed main(){
	scanf("%d%d",&l,&q);
	s.insert(0),s.insert(l);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&c,&x);
		if(c==1){
			s1.insert(x);
		}else{
			set<int>::iterator it=s.lower_bound(x);
			int o=*it;
			it--;
			int p=*it;
			printf("%d\n",o-p);
		}
	}
	return 0;
}
```


---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc217_d)

## 思路

用 STL 中的 set 来做此题，set 中存每次切断的位置（每段木头的头尾位置）。

首先在 set 中插入 $1$ 和 $L$，保存初始的一段木头。读入 $Q$ 组数据后分类讨论操作的情况。

**对于每次操作 $1$**：在 set 中插入 $x$ 和  $x+1$，表示又切断了一节（增加 $2$ 个端点）。

**对于每次操作 $2$**：用 ``upper_bound`` 函数二分查找当前位置所在的木头段的**右端点**，保存为 $r$，之后向前枚举**一个**端点保存为 $l$（此时的位置就是当前位置所在木头段的**左端点**）。最后输出 $r-l+1$（包含两端点所以 $+1$）。

这里不放代码了，根据上面的思路一步步写即可。

---

## 作者：vicky2048_2 (赞：0)

## $\text{Analysis}$

读完题之后不难想到：

- 对于每一次增加边界的操作，实际上就是在所有的边界点中增加了两个点：$x,x+1$。

- 对于每一次询问，我们只需要分别找点 $x$ 左右两边离它最近的两个分界点即可。

于是题目就可以直接转化成这样一个问题：


1. 给定一个点 $x$，将点 $x$ 和 $x+1$ 分别加入到终点序列和起点序列（下文统称为点序列）中。

2. 给定一个点 $x$，在起点序列中查找小于等于 $x$ 的点中最接近 $x$ 的点，在终点序列中查找大于等于 $x$ 的点中最接近 $x$ 的点，求两点的距离（计算距离时两端点也包含在内）。

不难想到二分。

易证得点序列元素一定互异（边界点不可能重合），于是直接用 $\operatorname{set}$ 的 $\operatorname{lower}\_\operatorname{bound}$ 做二分即可。

时间复杂度 $O(Q\log_2Q)$。

~~这个时间复杂度长得好像 $QoQ$ 阿。QwQ~~

## $\text{Code}$

```
#include<bits/stdc++.h>
using namespace std;
int en,q;
set<int>a;
set<int,greater<int>>aa;
int main(){
    scanf("%d%d",&en,&q);
    aa.insert(1),a.insert(en);
    while(q--){
        int op,b;
        scanf("%d%d",&op,&b);
        if(op<2)
            a.insert(b),aa.insert(b+1);
        else
            printf("%d\n",(*(a.lower_bound(b)))-(*(aa.lower_bound(b)))+1);
    }
    return 0;
}
```


---

## 作者：_Flame_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc217_d)

前置知识：[set](https://oiwiki.com/lang/csl/associative-container/)

## 思路

题意很简单，只需要用一个支持 $O(q\log n)$ 时间复杂度插入，$O(q\log n)$ 时间复杂度查询的数据结构寻找每一个刚好比询问大的断点与刚好比询问小的断点，按照题目所述操作即可实现。

考虑线段树上二分，但是不会，于是考虑 vector 和数组，发现都无法实现，于是想到 set，set 用红黑树实现，支持 $O(\log n)$ 插入与二分查找。这题到这就很好解决了，对于每个 $c_i=1$ 的操作，直接插入断点坐标，对于每个 $c_i=2$ 操作，二分查找第一个比询问的 $x_i$ 大的断点，并取这个断点与这个断点的前一个断点的差，也就是当前区间的长度，输出即可。

## Code


```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

int n,q;
set<int> s;

void solve(){
	n=read(),q=read();
	s.insert(0),s.insert(n);
	set<int>::iterator it;
	while(q--){
		int opt=read(),x=read();
		if(opt==1) s.insert(x);
		else if(opt==2){
			int ans=0;
			it=s.upper_bound(x);
			ans+=(*it),it--,ans-=(*it);
			write(ans);
			puts("");
		}
		else continue;
	}
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}

```



---

## 作者：cppcppcpp3 (赞：0)

提供一个需要离线处理的**线段树**做法。

## 思路：

首先可以考虑最暴力、最直接的做法：

对于每个点 $x$，维护它所在木头段的左端点与右端点，不妨分别记作 $l_x$ 与 $r_x$。显然地，若从点 $x$ 劈开木头，则点 $x$ 的影响范围应为 $[l_x,r_x]$。对于区间 $[l_x,x-1]$ 中的点，这次操作将它们所在木头段的右端点改为 $x$；而对于区间 $[x+1,r_x]$ 中的点，它们所在木头段的左端点变为 $x$。由于题目保证了一个点作为劈开处后不会对其进行查询，故可不做处理。复杂度为 $O(LQ)$。

当然，从上述可知，这样的做法复杂度极高。考虑进行优化。

观察到点数很多（$L$ 很大），但是操作数量却不多于 $2 \times 10^5$，那么被操作过的点最多其实仅仅有 $2 \times 10^5$ 个。

因此，我们**只关注那些进行过操作的点**。

怎么做呢？将所有操作离线，存储下来。将操作过的点丢进 vector，从小到大排序后重新编号。这个时候，进行单次修改操作的复杂度就从 $O(L)$ 降至 $O(Q)$ 了，总的时间复杂度就是 $O(Q^2)$。

然后，我们又发现一点，其实劈开带来的端点修改操作就是**区间赋值**，输出就是**单点查询**，我们喜欢的线段树就发挥了巨大的作用。时间复杂度降为 $O(Q\times \log Q)$，足以通过此题。

不过，由于用了各种 STL，常数较大，代码跑得比较慢。最后的缺点在于码量略大。

## 代码：
```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
#define md ((u+v)>>1)
#define ls (t<<1)
#define rs (t<<1|1)
using namespace std;
const int N=2e5+5;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,m,cnt,l[N],r[N];
int s[N<<2][2],lz[N<<2][2]; //0对应左端点,1对应右端点

struct que{
	int op,x;
}a[N];

map<int,int> mp;
vector<int> v;

il void pushup(int t){
	for(int i=0;i<2;++i) s[t][i]=s[ls][i]+s[rs][i];
}

void build(int u,int v,int t){
	lz[t][0]=-2,lz[t][1]=-2;
	if(u==v){
		s[t][0]=l[u],s[t][1]=r[u];
		return;
	}
	build(u,md,ls),build(md+1,v,rs);
	pushup(t);
} 

il void pushdown(int u,int v,int t){
	for(int o=0;o<2;++o){
		if(lz[t][o]==-2) continue;
		s[ls][o]=lz[t][o]*(md-u+1),s[rs][o]=lz[t][o]*(v-md);
		lz[ls][o]=lz[t][o],lz[rs][o]=lz[t][o];
		lz[t][o]=-2;
	}
}

void update(int u,int v,int t,int x,int y,int k,int o){ //区间赋值
	if(u>y||v<x) return;
	if(u>=x&&v<=y){
		s[t][o]=(v-u+1)*k,lz[t][o]=k;
		return;
	}
	pushdown(u,v,t);
	if(x<=md) update(u,md,ls,x,y,k,o);
	if(y>md) update(md+1,v,rs,x,y,k,o);
	pushup(t);
}

int query(int u,int v,int t,int x,int o){
	if(u==v) return s[t][o];
	pushdown(u,v,t);
	if(x<=md) return query(u,md,ls,x,o);
	else return query(md+1,v,rs,x,o);
}

int ll(int i){
	int p=query(0,cnt-1,1,i,0);
	if(p==-1) return 0;
	return v[p];
}

int rr(int i){
	int p=query(0,cnt-1,1,i,1);
	if(p==cnt) return n;
	return v[p];
}

main(){
	n=wrd(),m=wrd();
	for(int i=1;i<=m;++i){
		int op=wrd(),x=wrd();
		a[i]=que{op,x}; //离线
	}
	
	for(int i=1;i<=m;++i){
		if(mp[a[i].x]) continue;
		v.push_back(a[i].x),mp[a[i].x]=1;
	}
	
	cnt=v.size();
	
	sort(v.begin(),v.end());
	for(int i=0;i<cnt;++i){
		mp[v[i]]=i,l[i]=-1,r[i]=cnt; //特殊情形：l[i]==-1 代表左端点为0处，r[i]==cnt 表示右端点为 L 
	}
	
	build(0,cnt-1,1);
	
	for(int i=1;i<=m;++i){
		int nx=mp[a[i].x];
		
		if(a[i].op<2){
			int p=query(0,cnt-1,1,nx,0),q=query(0,cnt-1,1,nx,1);
			
			if(p<0) update(0,cnt-1,1,0,nx-1,nx,1); //修改[l[x],x-1]
			else update(0,cnt-1,1,p,nx-1,nx,1);
			
			if(q==cnt) update(0,cnt-1,1,nx+1,q-1,nx,0); //修改[x+1,r[x]]
			else update(0,cnt-1,1,nx+1,q,nx,0);

		}else printf("%lld\n",rr(nx)-ll(nx));
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

其它题解都说的很对，给出另一个做法。

对于分裂操作，直接在数组中 $ [l,r] $ 之间的位置插入 $ x $ 即可。

对于查询操作，二分求出 $ x $ 所在线段的右端点，然后右端点减一则一定为做短点的位置，两点间的距离则为答案。

实际上这和其他的做法也类似，不过用 vector 实现了插入和二分过程，喜提最劣解。

关于这个做法的时间效率问题：瓶颈显然在 $ 1 $ 操作，因为我们知道 insert 的复杂度实际上最差是 $ \mathcal{O}(n) $ 的，但是因为常数小而且跑不满所以加上快读也可以通过。

时间复杂度是最差 $ \mathcal{O}(Q^2) $，但根据上述分析可知跑不满，可以通过。

另外官方题解中有介绍，本题用一些高科技可以做到理论优秀于单 $ \log $ 的做法，此处不加详述。

代码：

```cpp
#pragma GCC Ofast
#import <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,q;
vector<int>s;
signed main()
{
	cin>>n>>q;
	s={0,n};
	for(int i=1;i<=q;i++)
	{
		int opt=read();
		if(opt==1)
		{ 
			int x=read();
			s.insert(upper_bound(s.begin(),s.end(),x),x);
		}
		else
		{
            int x=read();
			auto tmp=(upper_bound(s.begin(),s.end(),x));
            cout<<*tmp-*(tmp-1)<<'\n';
		}
	}
}
```


---

