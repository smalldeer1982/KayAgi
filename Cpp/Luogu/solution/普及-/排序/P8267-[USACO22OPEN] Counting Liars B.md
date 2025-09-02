# [USACO22OPEN] Counting Liars B

## 题目描述

奶牛 Bessie 躲在数轴上的某处。Farmer John 的 $N$ 头奶牛（$1\le N\le 1000$）中的每头奶牛都有一条信息要分享：第 $i$ 头奶牛说 Bessie 躲在小于或等于 $p_i$ 的某个位置，或者说 Bessie 躲在大于或等于 $p_i$ 的某个位置（$0\le p_i\le 10^9$）。

不幸的是，可能不存在躲藏位置与所有奶牛的回答均一致，这意味着并非所有奶牛都在说真话。计算在撒谎的奶牛的最小数量。

## 说明/提示

【样例解释 1】

有可能没有奶牛在撒谎。

【样例解释 2】

至少一头奶牛在撒谎。

## 样例 #1

### 输入

```
2
G 3
L 5```

### 输出

```
0```

## 样例 #2

### 输入

```
2
G 3
L 2```

### 输出

```
1```

# 题解

## 作者：Ginger_he (赞：9)

# 前置知识

1. 若 $a\leqslant b,x\leqslant a$，则 $x\leqslant b$
2. 若 $a\geqslant b,x\geqslant a$，则 $x\geqslant b$
3. 若 $a>b,x\geqslant a,x\leqslant b$，则 $x$ 无解

# 题解

首先，我们将字符为 `L` 和 `G` 分别加入数组 $a$ 和 $b$ 中，并进行排序。然后我们 $O(n^2)$ 枚举，不妨假设枚举到 $a_i$ 和 $b_j$，数组 $a,b$ 的大小分别为 $x,y$。  

由前置知识，我们可以得到：  

1. $a_{i},a_{i+1},\cdots,a_x$ 都是满足条件的
2. $b_1,b_2,\cdots,b_{j}$ 都是满足条件的
3. 如果 $a_i<b_j$ 则无解。  

因此，我们先判断一下 $a_i$ 和 $b_j$ 的大小关系，如果符合条件，$ans=\min\{ans,i-1+y-j\}$，这样就得出答案了。

## 优化

[数据加强版](https://www.luogu.com.cn/problem/U208878)  

其实这道题是可以 $O(n\log n)$ 的。注意到枚举每一个 $a_i$ 时，$i-1$ 是固定的，我们要让 $y-j$ 尽量小，就是让 $j$ 尽量大。简单来说，就是要求 $b$ 数组中小于等于 $a_i$ 的最大值，在 $b$ 数组中二分即可，下面的代码还是 $O(n^2)$ 的。

## 注意

- 最坏情况下有 $1$ 只奶牛猜的是对的，所以 $ans$ 要初始化为 $n-1$。

- 有可能说 `L` 或说 `G` 的奶牛全都是错的，注意细节。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1005
int n,t,x,y,a[N],b[N],ans;
char c;
int main()
{
	scanf("%d",&n);
	b[++y]=-1;
	for(int i=1;i<=n;i++)
	{
		scanf("\n%c%d",&c,&t);
		if(c=='L') a[++x]=t;
		else b[++y]=t;
	}
	sort(a+1,a+x+1);
	sort(b+1,b+y+1);
	a[++x]=1e9+1,ans=n-1;
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			if(a[i]>=b[j]) ans=min(ans,i-1+y-j);
			else break;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：LKY928261 (赞：5)

## 题目分析

简化题意：数轴上有一动点 $P$，有 $N$ 句话，其中 ``L x`` 表示 $P \leq x$，``G x`` 表示 $P \geq x$，求最少的假话个数。

大致思路：首先将每句话按 $p_i$ 升序排列，再依次进行计算。

每次的计算方法如下：

设 `L` 的序列为 $a$，长度为 $la$， `G` 的序列为 $b$，长度为 $lb$，当前位置的点 $P$ 满足 $a_i \leq P \leq a_{i+1},b_j \leq P \leq b_{j+1}$，则当前的假话数为 $i+lb-j$。

一边枚举一边求最小值即可。

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,x,y,z,a[1005],b[1005],i,j;char c;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=0;i<n;i++){cin>>c>>z;if(c=='L')a[x++]=z;else b[y++]=z;}
	//这里我开了两个数组，只开一个也能做，但两个数组更方便
	sort(a,a+x);sort(b,b+y);
	for(z=min(x,y),i=j=0;i<x&&j<y;){
		if(a[i]<b[j])i++;else j++;
		z=min(z,i+y-j);
	}
	cout<<z<<"\n";
}
```

---

## 作者：苏联小渣 (赞：4)

### Upd：2023.1.30 修改了代码。原代码错在忽略了说 `L` 的和说 `R` 的人可以全错。

引理 $1$：在小于等于 $x$ 的位置**包含**了在小于等于 $y(y>x)$ 的位置的情况。

引理 $2$：在大于等于 $x$ 的位置**包含**了在大于等于 $y(y<x)$ 的位置的情况。

---

利用上述两个引理，我们把所有 `L`，`G` 的坐标**分别**排序。然后两重循环枚举 `L`，`G` 对应的坐标（假设存储两者的坐标数组分别为 $l,g$，元素个数分别为 $p,q$）。假设我们枚举到了 $l_i=x,g_j=y$，其中 $x$ 表示位置需满足 $\le x$，$y$ 表示位置需满足 $\ge y$。这个范围需要是合法的，所以需满足 $y \le x$。由于 $l,g$ 都是有序的，故 $\le x$ 也就相当于要舍去**小于 $x$** 的情况，也就是 $i-1$；$\ge y$ 也就相当于要舍去**大于 $y$** 的情况，也就是 $q-j$。然后把两者加起来，就是要删去的元素个数了。取最小值即可。

举个例子理解一下：

假设 $l= \{1,4,5,7,8\},g=\{1,2,3,4,5\}$。目前枚举到 $l_3=5,g_2=2$。也就是说，位置 $p$ 需满足 $2 \le p \le 5$。根据引理，$\le 5$ 的情况包含了 $\le 7, \le 8$ 的情况，所以无需删去；但不包含 $\le 1,\le 4$ 的情况。也就是说 $\le 5$ 不一定代表 $\le 1,\le 4$，所以需要删去。大于等于也同理。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, s, t, p, q, a[1007], b[1007];
int main(){
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){
		char x;
		cin >> x; scanf ("%d", &t);
		if (x == 'L') a[++p] = t;
		else b[++q] = t;
	}
	s = n - 1;
	a[++p] = 1e9+7, b[++q] = -1e9;
	sort (a+1, a+p+1);
	sort (b+1, b+q+1);
	for (int i=1; i<=p; i++){
		for (int j=1; j<=q; j++){
			if (b[j] <= a[i]) s = min(s, q - j + i - 1);
		}
	}
	printf ("%d\n", s);
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：3)

## 思路

首先肯定暴力枚举 $0$ 到 $10^9$ 中的位置，然后就是时间爆炸。

我们考虑，假如有一头奶牛说 Bessie 躲在大于等于 $x$ 的位置上，那么无论 Bessie 在 $x + 1$ 或是 $x + 2$ 都是合法的，如果又有一头奶牛说 Bessie 躲在小于等于 $y$ 的位置上（保证 $x < y$），那么 Bessie 躲在 $[x, y]$ 这个区间里的任意一个位置都是合法且**等价**的。

那么我们不必去枚举每一个位置，只需枚举一段区间里的任意一个数都行，由于包括等于，这里就可以用本身的位置枚举。

具体实现：

1. 枚举两头奶牛所说的话。

2. 判断当前是否有撒谎的奶牛。

3. 对于每一次枚举的奶牛，进行取最小值。

## 代码

代码应该就很好实现了：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int n, mini = 1e9;

struct Node{
  char c;
  int x;
}a[N];

void Solve(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i].c >> a[i].x;
  }
  for(int i = 1; i <= n; i++){    //枚举奶牛
    int ans = 0;
    for(int j = 1; j <= n; j++){
      if(a[j].c == 'G'){
        if(a[j].x > a[i].x){ //判断是否合法
          ans++;
        }
      }
      else if(a[j].c == 'L'){
        if(a[j].x < a[i].x){
          ans++;
        }
      }
    }
    mini = min(mini, ans);   //取最小值
  }
  cout << (mini == 1e9 ? 0 : mini);
}

int main(){
  Solve();
  return 0;
}
```

---

## 作者：Galex (赞：2)

这个题可以把题意转化一下：将小于等于 $p_i$ 改为 $[0,p_i]$，将大于等于 $p_i$ 改为 $[p_i,10^9]$，问题转化为：至多有多少个区间存在交集？

相信大家的第一想法应该是枚举所有的位置，判断它被多少个区间包含。

**但是！**

$p_i \le 10^9$，也就是说，需要枚举 $10^9$ 个位置。

很明显，我们需要优化一下。

首先，其实我们并不关心每个区间的具体位置，只关心他们是否存在交集。

那么做法就很明显了：**就是离散化！**

这样我们就只用枚举 $2 \times n$ 个位置，复杂度 $O(n^2)$。

代码：

```cpp
#include <cstdio>
#include <algorithm>

int read(){
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

char readc(){
	char ch = getchar();
	while (ch != 'G' && ch != 'L')
		ch = getchar();
	return ch;
} 

int n, k;
struct node{
	int l, r;
}a[1005];
int b[2005];
int ans, cnt, res;

int main(){
	n = read();
	for (int i = 1; i <= n; i++){
		char op = readc();
		int p = read();
		if (op == 'L')
			a[i].l = 0, a[i].r = p;
		else
			a[i].l = p, a[i].r = 1e9;
		b[2 * i - 1] = a[i].l, b[2 * i] = a[i].r;
	}
	std::sort(b + 1, b + 2 * n + 1);
	int tot = std::unique(b + 1, b + 2 * n + 1) - b - 1;
	for (int i = 1; i <= n; i++)
		a[i].l = std::lower_bound(b + 1, b + tot + 1, a[i].l) - b - 1, a[i].r = std::lower_bound(b + 1, b + tot + 1, a[i].r) - b - 1;
	int ans = 0;
	for (int i = 1; i <= tot; i++){
		int cnt = 0;
		for (int j = 1; j <= n; j++)
			if (a[j].l <= i && i <= a[j].r)
				cnt++;
		ans = std::max(ans, cnt); 
	}
	printf("%d", n - ans);
	return 0;
}
```


---

## 作者：ImposterAnYu (赞：1)

~~我又来水题解了。~~

看这数据范围，妥妥的 $O(n^2)$ 暴力。

# 简化题意
给定 $n(1 \leq n \leq 1000)$ 个关于 $x$ 的不等式，格式为 `ch a`（其中，$ch$ 是一个为 `L` 或 `G` 的字符，$a$ 为一个不小于 $10^9$ 的非负整数）。当 $ch$ 为 `L` 时，表示 $x \leq a$；当 $ch$ 为 `G` 时，表示 $x \ge a$。

问：至少要删去几个不等式，才能使得符合条件的 $x$ 存在？

# 解析
## 1. 什么情况下会有奶牛说谎？
很明显，当存在一对不等式组 $(i,j)$，满足这些条件时，会有奶牛说谎。

1. 第 $i$ 个不等式为 $x \leq a_i$；

2. 第 $j$ 个不等式为 $x \geq a_j$；

3. $a_i < a_j$。

[因为原理比较简单，所以在此就不讲了，不懂得就自己去看吧（（（](https://anyu-yyds.blog.luogu.org/fou-deng-shi-zu)

## 2. 怎样找出最小的答案？
开头已经说了，这是个 $O(n^2)$ 的暴力。~~当然，可能存在复杂度更优的解法。~~

正常情况下，我们枚举的是 $x(0 \leq x \leq 10^9)$，但是这样会慢到飞起，所以我们可以优化一下策略，变成枚举 $i(1 \leq i \leq n)$，然后让 $x = a_i$，看这时候有多少头说谎的奶牛。最后，我们只需要求出这些说谎的奶牛的头数中的最小值就好了~

没听懂？看代码就完事了~

# AC code
```c++
#include<bits/stdc++.h>
#define int1 long long 
using namespace std;                   
int1 n,a,i,j,l[1005],g[1005],minn = 114514,s,t,p;
char ch;
int1 read(){//熟悉的快读。 
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//熟悉的快写。 
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
/*
string str(){
    char ch = getchar();
    string w = "";
    while(!isalpha(ch)){
        ch = getchar();
    }
    while(isalpha(ch)){
        w += ch;
        ch = getchar();
    }
    return w;
}
这里是快速读入字符串，因为没用就注释掉了（doge）。 
*/
int main(){   
	n = read();
	for(i = 1; i <= n; i++){
		ch = getchar();
		while(ch != 'L' && ch != 'G'){//快速读入字符（误）。 
			ch = getchar();
		}
		a = read();
		if(ch == 'L'){//将信息分开处理。 
			l[++s] = a;
		}else{
			g[++t] = a;
		}
	}
	for(i = 1; i <= s; i++){//分开枚举。 
		p = 0;
		for(j = 1; j <= s; j++){//统计 x = a_i 时，撒谎的奶牛头数。 
			p += (l[i] > l[j]);
		}
		for(j = 1; j <= t; j++){//将 n 头统计完。 
			p += (l[i] < g[j]);
		}
		minn = min(minn,p);//取最小值。 
	}
	for(i = 1; i <= t; i++){//同上。 
		p = 0;
		for(j = 1; j <= s; j++){
			p += (g[i] > l[j]);
		}
		for(j = 1; j <= t; j++){
			p += (g[i] < g[j]);
		}
		minn = min(minn,p);
	}
	print(minn);
  	return 0;
}
```

---

## 作者：_lfxxx_ (赞：1)

## Problem：
有 $n$ 个形如 $x\le p_i$ 或 $x\ge p_i$ 的条件，问最少多少个条件不成立。
## Solution：
显然有一种最优的情况满足 $x\in p$。

于是我们可以花 $O(n)$ 的时间枚举 $p$，再花 $O(n)$ 时间判合法，于是复杂度 $O(n^2)$，本题 $n\le10^3$，可以通过。

（代码放最后）

但其实还可以更优，上面代码主要慢在判合法，我们针对这个进行优化。

我们发现可以将每个条件转化为 $[l_i,r_i]$ 都加 $1$（不合法的贡献加 $1$） 的形式，而我们就是求哪个值最小。`L` 就是 $[p_i+1,+\infty]$ 加 $1$，`G` 就是 $[0,p_i-1]$ 加 $1$。这东西差分一下就行了。

由于 $0\le p_i\le10^9$，所以要离散化。

时间复杂度 $O(n\log n)$，瓶颈离散化。
## Code:
```cpp
//O(n^2)
namespace solution{
constexpr int N=1e3+5;
struct cow{
	char op;
	int p;
}a[N];
void main(){
#ifdef IAKIOI
	freopen("in.txt","r",stdin);
#endif
	int n,s,ans(N);
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i].op>>a[i].p;
	for(int i=1;i<=n;++i){
		s=0;
		for(int j=1;j<=n;++j)
			s+=a[j].op=='L'&&a[j].p<a[i].p||a[j].op=='G'&&a[j].p>a[i].p;
		ans=min(ans,s);
	}
	cout<<ans<<endl;
}
}
```

```cpp
//O(nlogn)
namespace solution{
constexpr int N=1e3+5;
struct cow{
	char op;
	int p;
}a[N];
int tmp[N],b[N];
void main(){
#ifdef IAKIOI
	freopen("in.txt","r",stdin);
#endif
	int n,ans(N),cnt;
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i].op>>a[i].p,tmp[i]=a[i].p;
	sort(tmp+1,tmp+1+n),cnt=unique(tmp+1,tmp+1+n)-tmp-1;
	for(int i=1;i<=n;++i)
		if(a[i].op=='L')
			++b[lower_bound(tmp+1,tmp+1+cnt,a[i].p)-tmp+1];
		else
			++b[0],--b[lower_bound(tmp+1,tmp+1+cnt,a[i].p)-tmp];
	for(int i=1;i<=cnt;++i)
		ans=min(ans,b[i]+=b[i-1]);
	cout<<ans<<endl;
}
}
```

---

## 作者：SSER_ZRQ (赞：1)

# Counting Liars B题解




题目大意：有若干的数量关系（解集），找出一个数 $x$，使尽量多的数量关系成立。



## 做法

将每一个数量关系按照坐标排好序。即将这些解集画在坐标轴上。

就像这样

![](https://cdn.luogu.com.cn/upload/image_hosting/mw7yxwgz.png)


然后，我们再枚举区间，即 $a-b,b-c,c-d,......$，耗时 $O(n)$

对于每一个区间，用 $O(n)$ 时间查询满足多少条件。

用一个变量记录所有区间答案的最大值。

总耗时： $O(n^2)$

#### 注意！！有一个细节！！

即枚举 $a-b$ 区间的时候，最小取 $a$, 最大取 $b$。而有一些关系（解集）是只能在取 $a$ 或取 $b$ 时成立，例如：`L a` 和 `G b`。此时统计取 $a$ 和 $b$ 哪一个能满足的条件多，就选哪一个。

## 附上代码

[代码](https://www.luogu.com.cn/paste/1u7vcxsr)

---

## 作者：lsj2009 (赞：1)

## 题目大意
<https://www.luogu.com.cn/problem/P8267>。
## 思路
约定的数据分别为 $opt_i,p_i$。


设 $f_{0,x}$ 为 $opt_i=\texttt{L}$ 且 $x\le p_i$ 的 $i$ 的数量。

设 $f_{1,x}$ 为 $opt_i=\texttt{G}$ 且 $x\ge p_i$ 的 $i$ 的数量。

容易发现，将奶牛放在 $x$ 号点的说真话的奶牛数量为 $f_{0,x}+f_{1,x}$，则说谎话的奶牛个数为 $n-(f_{0,x}+f_{1,x})$。

用 $a_{0,x}$ 表示 $opt_i=\texttt{L}$ 且 $p_i=x$ 的 $i$ 的数量。

用 $a_{1,x}$ 表示 $opt_i=\texttt{G}$ 且 $p_i=x$ 的 $i$ 的数量。

则 $f_{0,x}=\sum\limits_{i=x}^{\max\limits_{k=1}^n\{p_k\}}a_{0,x}$，$f_{1,x}=\sum\limits_{i=0}^{x}a_{1,x}$。

上述二式可以使用前缀和（后缀和）求之。

不过，值的注意的一点是 $p_i\le10^9$，这样子数组是肯定存不下的，不过，我们可以使用离散化这一技巧将所有 $p_i$ 的值都转换到 $1$ 至 $n$ 之间。这里不作过多介绍。
## Code:
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define pb pop_back
#define mk make_pair
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
template <typename T> inline void read(T& x) {
	x=0; T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch&15); ch=getchar(); }
	x=x*f;
	return;
}
template <typename T,typename ...Arg> inline void read(T& x,Arg& ...arg){
	read(x); read(arg...);
}
int power(int a,int b) {
	int ans=1;
	do {
		if(b&1) ans*=a; a*=a;
	} while(b>>=1);
	return ans;
}
const int N=1e3+5;
int a[N],t[N],sum0[N],sum1[N],n,ans,len;
char opt[N];
signed main() {
	read(n);
	_for(i,1,n)
		cin>>opt[i],read(a[i]),t[i]=a[i];
	sort(t+1,t+n+1);
	len=unique(t+1,t+n+1)-(t+1);
	_for(i,1,n) {
		int x=lower_bound(t+1,t+len+1,a[i])-t;
		if(opt[i]=='L')
			++sum0[x];
		else
			++sum1[x];
	}
	_for(i,1,len) sum1[i]+=sum1[i-1];
	_rep(i,len,1) sum0[i]+=sum0[i+1];
	_for(i,1,len)
		ans=max(ans,sum0[i]+sum1[i]);
	printf("%d",n-ans);
	return 1;
}

```
时间复杂度 $\Theta(n\log{n})$，瓶颈在于排序。

当然，也可以使用哈希，平均时间复杂度 $\Theta(n)$。

---

