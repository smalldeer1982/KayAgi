# [USACO11FEB] Generic Cow Protests G

## 题目描述

Farmer John 的 $N$ 头奶牛（$1 \leq N \leq 10^5$）排成一列，正在进行一场抗议活动。第 $i$ 头奶牛的理智度为 $a_i$（$-10^4 \leq a_i \leq 10^4$）。

FJ 希望奶牛在抗议时保持理性，为此，他打算将所有的奶牛隔离成若干个小组，每个小组内的奶牛的理智度总和都要不小于零。

由于奶牛是按直线排列的，所以一个小组内的奶牛位置必须是连续的。请帮助 FJ 计算一下，满足条件的分组方案有多少种。

## 说明/提示

所有合法分组方案如下：

- $\texttt{(2 3 -3 1)}$
- $\texttt{(2 3 -3) (1)}$
- $\texttt{(2) (3 -3 1)}$
- $\texttt{(2) (3 -3) (1)}$

## 样例 #1

### 输入

```
4
2
3
-3
1```

### 输出

```
4```

# 题解

## 作者：MZ_CXQ (赞：27)

### [欢迎踩踩我的博客](https://www.cnblogs.com/mzg1805/p/11387673.html)

[${\color{cyan}{>>Question}}$](https://www.luogu.org/problem/P2344)

二维偏序$dp$

方程很简单

令$f[i]$表示到$i$的方案数

有
$$f[i] = \sum f[j],\sum_{k = j+1}^i a[k] \geq 0$$

写成前缀和的形式便是
$$f[i] = \sum f[j],sum[i]-sum[j]\geq 0$$

暴力是$O(n^2)$(~~话说居然有70pts~~),考虑优化

观察可知$i$由$j$转移来有两个条件

$1.$ $j < i$

$2.$ $sum[j] <= sum[i]$

那可把$i$看成$(i,sum[i])$的点,就成了一个二维偏序问题

不了解二维偏序的可以康康[这篇博客](https://blog.csdn.net/u012972031/article/details/91049130)(其实逆序对就是最经典的二维偏序(动态逆序对就是三维偏序)
)

可以离散化,也可以不离散化

离散化就离散$sum[i]$,$i$天然有序

不离散化就以$sum[i]$为第一关键字,$i$为第二关键字排序

外面都套个树状数组即可

但我太菜了,第一次处理树状数组$0$基准的情况($f[0] = 1$),犯了很多错才调出来,具体看代码吧


离散化版

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
using namespace std; 

template <typename T> void in(T &x) {
    x = 0; T f = 1; char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch)) {x = 10 * x + ch - 48; ch = getchar();}
    x *= f;
}

template <typename T> void out(T x) {
    if(x < 0) x = -x , putchar('-');
    if(x > 9) out(x/10);
    putchar(x%10 + 48);
}
//-------------------------------------------------------

const int N = 1e5+7,mod = 1e9+9;
int n;
ll b[N],ans;

struct node {
	int pos;ll sum;
}p[N];

struct map {
	int pos;ll sum;
	bool operator < (const map &x) const {
		return sum == x.sum ? pos < x.pos : sum < x.sum;//sum < x.sum;
	}
}a[N];

void A(int pos,ll k) {
	for(int i = pos;i <= n;i += i&-i) b[i] = (b[i]+k)%mod;
}

ll Q(int pos) {
	ll res = 0;
	for(int i = pos;i;i -= i&-i) res = (res + b[i])%mod;
	return res;
}

int main() {
	//freopen("0.in","r",stdin);
	//freopen("my.out","w",stdout);
	int i; ll x;
	in(n);
	a[0].pos = a[0].sum = 0;
	for(i = 1;i <= n; ++i) p[i].pos = i,in(x),p[i].sum = p[i-1].sum + x,a[i].pos = i,a[i].sum = p[i].sum;
	sort(a,a+n+1);//debug a[0]
	p[a[0].pos].sum = 1; int _id = 1;
	for(i = 1;i <= n; ++i) {
		if(a[i].sum != a[i-1].sum) ++_id;//debug i-1越界 
		p[a[i].pos].sum = _id;
	}
	//for(i = 1;i <= n; ++i) cout << p[i].sum << endl;
	A(p[0].sum,1);
	for(i = 1;i <= n; ++i) {
		ans = Q(p[i].sum);
		A(p[i].sum,ans);
		if(i == n) out(ans);
		//out(ans),putchar('\n');
	}
	//out(ans);
	return 0;
}
```

不离散化版
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
using namespace std; 

template <typename T> void in(T &x) {
    x = 0; T f = 1; char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch)) {x = 10 * x + ch - 48; ch = getchar();}
    x *= f;
}

template <typename T> void out(T x) {
    if(x < 0) x = -x , putchar('-');
    if(x > 9) out(x/10);
    putchar(x%10 + 48);
}
//-------------------------------------------------------

const int N = 1e5+7,mod = 1e9+9;
int n;
ll b[N],ans;
ll f[N];

struct node {
	int pos;ll sum;
	bool operator < (const node &x) const {
		return sum == x.sum ? pos < x.pos : sum < x.sum;
	}
}p[N];

void A(int pos,ll k) {
	for(int i = pos;i <= n+1;i += i&-i) b[i] = (b[i]+k)%mod;//debug n+1 -> n
}

ll Q(int pos) {
	ll res = 0;
	for(int i = pos;i;i -= i&-i) res = (res + b[i])%mod;
	return res;
}

int main() {
	//freopen("0.in","r",stdin);
	int i; ll x;
	in(n);
	p[0].pos = 1,p[0].sum = 0;
	for(i = 1;i <= n; ++i) p[i].pos = i+1,in(x),p[i].sum = p[i-1].sum + x;
	sort(p,p+n+1);
	for(i = 0;i <= n; ++i) {
		if(p[i].pos == 1) A(p[i].pos,1);
		f[p[i].pos-1] = Q(p[i].pos);
		ll x = f[p[i].pos-1];
		//if(p[i].pos == 1) A(p[i].pos,1);//debug//debug 
		if(p[i].pos == 1) continue;
		A(p[i].pos,x);
	}
	out(f[n]);
	//for(i = 1;i <= n; ++i) cout << f[i] << endl;
	return 0;
}
```

谢谢各位看官老爷支持,如果觉得还看得下去的话,不妨点个赞,
~~投个币~~（づ￣3￣）づ╭❤～

另外有意愿的大佬们可以去切一下[这道题](https://www.luogu.org/problem/P3431),一样的思路

---

## 作者：NTG_Adiord (赞：20)

~~今天考试考了,我选择BFS~~

代码解释

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,lie[100001],zt[100001];//zt存当前长度有多少种了
bool ale[100001];//确认一下当前长度在不在队列里
long long ans;
priority_queue<int,vector<int>,greater<int> > e;
void bfs(int now){
	long long k=0;
	for(int i=now+1;i<=n;i++){
		k+=lie[i];//从哪来的加那个
		if(k>=0){
			zt[i]+=zt[now];
			zt[i]%=1000000009;
			if(!ale[i]){
				e.push(i);
				ale[i]=1;//在队列里就不用再加了
			}
		}
	}
}
int main(){
	zt[0]=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&lie[i]);
	}
	e.push(0);//从0开始搜索
	while(!e.empty()){
		bfs(e.top());e.pop();//如果队列里有就搜,以短的优先
	}
	cout<<zt[n];
}

```



---

## 作者：Sundial (赞：13)

[[题目传送门](https://www.luogu.org/problem/P2344)]

这道题本蒟蒻感觉不太好想，于是乎就发篇博客加深一下记忆，也方便以后查看

首先因为题目中说必须是连续的一段，很容易想到要用前缀和，并且看过数据范围后要离散化一下

然后会有一个dp的思想

具体讲一下
```cpp
add(s[0], 1);//因为 s[0] 此时记录的是相对大小，即表示理智度刚好为0时，方案数为1，先加入树状数组 
for (int i = 1; i <= n; i++) {
	ans = query(s[i]);//查询前面比自己小的前缀和
	add(s[i], ans);//累加上方案数 
}
```
很多人可能会有疑问，为什么这里只查询比自己小的就行了？难道不会有负值的情况吗？

请看这一句：
```cpp
add(s[0], 1);
```
因为你离散化之后 s[0] 就变成了相对大小，即记录下了理智度为0时的相对大小，此时方案数为1。在此后如果你加入比它小的值，也就是理智度小于0的一段时，其方案数依然为0，并不会影响上面的值。所以循环碰到 s[i] < 0 时，ans = 0,在加入时增加依然为0。

好我们来解决为什么加 比自己小的值 的问题

就是说，因为要dp将前面分成好几段来累加，所以当前一个值大于自己时，代表这之间一定出现了负值，再进行累加就不正确了，所以加比自己小的值。

另外因为是dp所以将当前方案数加到当前值上，然后加入树状数组

好了好了，看看代码就清楚了

~~其实自己讲的啥都不是qwq~~

**code:**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int p = 1000000009;
int n, ans;
int c[100021], a[100021], s[100021];
void add(int x, int v) {//树状数组用来维护方案数 
	for (int i = x; i <= n + 1; i += i & -i) {
		c[i] += v;
		c[i] %= p;
	}
}
int query(int x) {
	int re = 0;
	for (int i = x; i > 0; i -= i & -i) {
		re += c[i];
		re %= p;
	}
	return re;
}
int main () {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &s[i]);
		s[i] += s[i - 1];//记录前缀和 
		a[i] = s[i];//另开一个数组用于离散化 
	}
	sort(a, a + 1 + n);//排序 
	for (int i = 0; i <= n; i++) {//离散化 
		s[i] = lower_bound(a, a + 1 + n, s[i]) - a + 1;
	}
	add(s[0], 1);//因为 s[0] 此时记录的是相对大小，即表示理智度刚好为0时，方案数为1，先加入树状数组 
	for (int i = 1; i <= n; i++) {
		ans = query(s[i]);//查询前面比自己小的前缀和
		add(s[i], ans);//累加上方案数 
	}
	printf("%d\n", ans % p);
	return 0;
}
```


---

## 作者：程就未来 (赞：9)

### 大家好，我喜欢枚举，我用n^2暴力（水）过了此题.
[评测记录](https://www.luogu.org/recordnew/show/20679692)

这是一道dp，f[i]表示前i头奶牛分组的方案数

显然f[i] = sum f[j] (s[j] < s[i])(s是前缀和)

下面说正解

我们发现可以用权值线段树每次统计小于s[i]的f[j]的和。

可以用树状数组实现（别忘了离散化）

## code
### 暴力：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define R register int
#define For(i , x , y) for(i = x ; i <= y ; ++ i)
const int N = 1e5 + 5 , P = 1000000009;
inline ll read() {
    ll s = 0 , w = 1; char ch = getchar();
    while(ch < 48 || ch > 57) {if(ch == '-') w = -1; ch = getchar();}
    while(ch >= 48 && ch <= 57) s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar();
    return s * w;
}
ll n , f[N] , a[N] , s[N] , c[N];
int main() {
    R i , j ;
    n = read();
    For(i , 1 , n) a[i] = read() , s[i] = s[i - 1] + a[i];
    f[0] = 1;
    For(i , 1 , n)
        if(s[i] >= 0) 
            For(j , 0 , i - 1)
                if(s[j] >= 0 && s[i] - s[j] >= 0) (f[i] += f[j])%=P;
    cout << f[n] << endl;
    return 0;
}
```

### 正解：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define R register int
#define For(i , x , y) for(i = x ; i <= y ; ++ i)
#define lowbit(x) x & -x
const int N = 2e5 + 5 , P = 1000000009 ;
inline ll read() {
    ll s = 0 , w = 1; char ch = getchar();
    while(ch < 48 || ch > 57) {if(ch == '-') w = -1; ch = getchar();}
    while(ch >= 48 && ch <= 57) s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar();
    return s * w;
}
ll n , f[N] , a[N] , b[N] , s[N] , c[N];
inline void update(ll x , ll val) {
    while(x <= n) (c[x] += val)%=P , x += lowbit(x);
}
inline ll query(ll x) {
    ll ans = 0;
    while(x) (ans += c[x])%=P , x -=lowbit(x);
    return ans%P;
}

int main() {
    R i , j ;
    n = read();
    For(i , 1 , n) b[i] = s[i] = s[i - 1] + read();
    sort(b + 1 , b + n + 1);
    ll cnt = unique(b + 1 , b + n + 1) - b - 1;
    For(i , 1 , n) a[i] = lower_bound(b + 1 , b + cnt + 1 , s[i]) - b; 
    f[0] = 1;
    For(i , 1 , n) 
        if(s[i] >= 0){
            f[i] = 1; update(a[i] , f[i]);++ i;break;
        }
    
    while(i <= n) {
        if(s[i] >= 0) {
            f[i] = (query(a[i]) + 1)%P;
             update(a[i] , f[i]);
        }
        ++ i;
    }
    cout << f[n] << endl;
    return 0;
}

```


---

## 作者：天命之路 (赞：8)

这道题目，是一道有点刺激的数据结构优化 $dp$ 题。

#### 如何想到 $dp$:

我们看到，这道题是一个求方案数量的题目，那么只有递推（也就是简单 $dp$）和搜索这两种方式，而我不喜欢打搜索，就用 $dp$ 了。

#### 如何设计 $dp$:

我们知道，题目中要求对序列进行分组，那么就是一道有关子序列的问题，我们就可以想到，一段子序列是两个子序列的差集，即$[l,r]$ 是 $[1,r]$ 和 $[1,l]$ 的差集，所以可以设计关于前缀的 $dp$ （这段话适用于大多数子序列的题目）

所以，设 $f[i]$表示将$a_{1 \dots i}$ 分组的方案数。

那么，我们只要找到一个$[1,i]$的后缀$[k+1,i]$，满足其中所有数之和不小于0，那么在合法的分组方案中，一定有这一段被作为最后一组的情况。

那一共有多少这种方案呢？

在这种方案下，我们要让$[1,k]$ 也符合要求，因为在这里后缀是固定的，所以情况数就是让$[1,k]$符合要求的方案数。

就是$f[k]$

所以，我们的状态转移方程就写出来了。

$$f[i]=\sum\limits_{a_{k+1}+a_{k+2}+\dots+a_i\ge 0,k \le i}f[k]$$

（其实上面啰嗦一大堆，是为了让各位看官获得一个普适化的思维方式）

简化一下状态转移方程，令 $sum[i]=\sum\limits_{j=1}^i a[j]$，则状态转移方程可以写成：
$$f[0]=1,f[i]=\sum\limits_{sum[i] \ge sum[k],k \le i}f[k]$$

暴力枚举 $i,k$ 的话，时间复杂度为 $\Theta(n^2)$

然而，要是 $n$ 再小点就好了.......

$n \le 2\times 10^5$

看到这个范围，你才知道这为什么是蓝题。


---

#### 如何优化时间：

我们可以新建一个序列$q$ 其中$q[sum[i]]=f[i],i\in[0,n]$

我们维护一个下标$i$,从左到右扫描。（这样就天然满足了方程中$k \le i$这一条件）

那么对于$f[i]$而言，我们只要求$\sum\limits_{j=\min\{sum[k]\}}^{sum[i]}q[j]$,求完之后再让$q[sum[i]]\leftarrow f[i]$.(其中$\min\{sum[k]\}$是指所有$sum$中的最小值）

那么，这就是个单点修改，询问前缀和的题目，可以用树状数组求解.

但是，我们发现，$-10^9\le sum[i]\le 10^9,i \in[1,n]$，是完全没法用普通数组做的。

我们可以用一个数的排名代替这个数（排名定义为比它小的个数加1）

我们知道，这样子的话，在某个数前面的数还是在某个数前面，结果不会有改变。

其实这个过程就是离散化（将无限空间里的有限个体映射到有限空间中）

这种代替方式最为常用，也好写。

但是，我们映射的时候要加上0号结点，因为有一点:$f[0]=1$

如何求一个数的排名？

排序之后看它的下标，可以用二分查找，这里不再赘述。

---
#### 代码：

各位看官，随我来！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],sum[N],vals[N],n,b[N],mod=1e9+9;
/*
	a为原序列
    sum 为前缀和
    vals为一个附加空间，用来存排序之后的sum
    b 为离散化后的序列
*/
int f[N];
#define lowbit(x) (x&(-x))
int tr[N];
//
inline void update(int pos,int num)   //树状数组单点修改
{
	int x=pos;
	while(x<=n)
	{
		tr[x]+=num;
		tr[x]%=mod;
		x+=lowbit(x);
	}
}
inline int _sum(int pos)   //树状数组求前缀和
{
	int res=0,x=pos;
	while(x)
	{
		(res+=tr[x])%=mod;
		x-=lowbit(x);
	}
	return res;
}
int tot=0;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
//------------------读入，预处理--------------------
	for(int i=0;i<=n;i++)  //记得加上0
	vals[++tot]=sum[i];     
	sort(vals+1,vals+tot+1);  //排序
	tot=unique(vals+1,vals+tot+1)-vals-1;  //去重，否则相同的数排名不同
	for(int i=0;i<=n;i++)
	b[i]=lower_bound(vals+1,vals+tot+1,sum[i])-vals;  //二分查找
//------------------离散化----------------------------
	update(b[0],f[0]=1);   //加入0号结点
	for(int i=1;i<=n;i++)
	{
		f[i]=_sum(b[i]);   //求出 q 序列中的前缀和
		update(b[i],f[i]);   //令q[b[i]]=f[i]
	}
	cout<<f[n]<<endl;   //输出答案
    return 2147483647;
}
```

有问题请评论，不喜勿喷。

---

## 作者：XG_Zepto (赞：6)

### 思路

我们令$f[i]$表示考虑到第$i$个奶牛的方案数，$s[i]$表示前缀和，显然有

$f[i]=\sum_{1\le j \le i ,s[j] < s[i] }  f[j]$ 。

我们发现，这个问题演变成类顺序对的问题，我们使用树状数组解决。

细节不再赘述，因为和逆序对是相似的，具体可以参照https://www.cnblogs.com/xiongmao-cpp/p/5043340.html

### 评测记录

用时: 52ms / 内存: 2914KB

### 代码实现

```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int n,sum[100001],tree[100001],a[100001];
    int MOD=1e9+9;
    //以下树状数组
    void Add(int i,int j)
    {for(;i<=n+5;i+=(i&-i))tree[i]+=j,tree[i]%=MOD;}
    int Sum(int i)
    {int res=0;for(;i;i-=(i&-i))res+=tree[i],res%=MOD;return res;}
    int main() {
        scanf("%d",&n);
        for (int i=1;i<=n;i++) 
        {scanf("%d",&sum[i]);sum[i]+=sum[i-1];a[i]=sum[i];}
        sort(a,a+n+1);
        for (int i=0;i<=n;i++) 
        sum[i]=lower_bound(a,a+n+1,sum[i])-a+2;//离散化
        Add(sum[0],1);int ans=0;
        for(int i=1;i<=n;i++) {ans=Sum(sum[i]);Add(sum[i],ans);}
        //树状数组求顺序对
        printf("%d\n",ans);
        return 0;
}
```

---

## 作者：Santiego (赞：4)

~~USACO的题太猛了~~

~~让本蒟蒻把树状数组做法再讲详细一点吧~~

首先容易想到$DP$，设$f[i]$表示为在第$i$位时方案数，转移方程：
$$
f[i]=\sum f[j]\;(j< i,sum[i]-sum[j]\ge0)
$$
$O(n^2)$过不了，考虑优化

移项得：
$$
f[i]=\sum f[j]\;(j< i,sum[i]\ge sum[j])
$$
这时候我们发现相当于求在$i$前面并且前缀和小于$sum[i]$的所有$f[i]$和，这就可以用一个树状数组优化了，在树状数组维护下标为$sum[i]$，$f[i]$的前缀和。对于每个$f[i]$即为树状数组上$sum[i]$的前缀和。

这里需要注意的是前缀和可能为负，而树状数组下标不能为负，所以我们要离散化一下。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 100010
#define lowbit(x) ((x)&(-(x)))
#define MOD 1000000009
int n,sum[MAXN],s;
int sum_sort[MAXN+1];
int tre[MAXN+1];
inline void add(int x, int val){
    while(x<=s){
        tre[x]=(tre[x]+val)%MOD;
        x+=lowbit(x);
    }
}
inline int get_sum(int x){
    int res=0;
    while(x>0){
        res=(res+tre[x])%MOD;
        x-=lowbit(x);
    }
    return res;
}
int main(){
    scanf("%d", &n);
    for(int i=1;i<=n;++i)
        scanf("%d", &sum[i]),sum[i]+=sum[i-1];
    for(int i=1;i<=n;++i) sum_sort[i]=sum[i];
    sort(sum_sort, sum_sort+1+n);
    s=unique(sum_sort, sum_sort+1+n)-sum_sort;
    for(int i=0;i<=n;++i) sum[i]=lower_bound(sum_sort, sum_sort+s, sum[i])-sum_sort+1;
    add(sum[0], 1); // f[0]=1 计数dp初始化
    int ans=0;
    for(int i=1;i<=n;++i){
        ans=get_sum(sum[i]); // 获得f[i]
        add(sum[i], ans); // 维护树状数组
    }
    printf("%d\n", ans);
    return 0;
}
```






---

## 作者：杰森的伯恩 (赞：4)

记录前缀理智和si。l,l+1,l+2,…,r-1,r能够分成一组，iff s[r]>=s[l-1]

令dp[i]表示以i作为某一段的结尾的分组方式。dp[n]就是要求的答案

dp[i]=∑dp[j] ……j<i且s[j]<=s[i]

<=s[i]的dp[j]的和可以使用树状数组维护。

因此，先以s[i]离散化，每次动态查询，动态修改

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define f(i,l,r) for(i=(l);i<=(r);i++)
using namespace std;
const int MAXN=100005,MOD=1000000009;
struct Node{
    int v,id,Hash;
    bool operator < (const Node& x)const{
        return v<x.v;
    }
}sum[MAXN];
int n,a[MAXN],Tree[MAXN],Hash[MAXN],sz;
bool cmp(Node a,Node b)
{
    return a.id<b.id;
}
void Add(int x,int d)
{
    while(x<=sz){
        Tree[x]=(Tree[x]+d)%MOD;
        x+=x&(-x);
    }
}
int Query(int x)
{
    int res=0;
    while(x>0){
        res=(res+Tree[x])%MOD;
        x-=x&(-x);
    }
    return res;
}
int main()
{
    int i,j=1,tot=0,pos,ans;
    scanf("%d",&n);
    sum[0].v=sum[0].id=0;          //dp边界为dp[0]=1,因此要插入一个0
    f(i,1,n){
        scanf("%d",&a[i]);
        sum[i].v=sum[i-1].v+a[i];
        sum[i].id=i;
    }
    sort(sum,sum+1+n);
    sum[0].Hash=1;
    f(i,1,n){                                   //去重+离散化
        if(sum[i].v!=sum[i-1].v){
            sum[i].Hash=++j;
        }
        else sum[i].Hash=j;
    }
    sz=j;
    sort(sum,sum+1+n,cmp);
    Add(sum[0].Hash,1);                       //dp边界
    f(i,1,n){
        ans=Query(sum[i].Hash);
        Add(sum[i].Hash,ans);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：wmjlzw1314 (赞：3)

```cpp
**补一发树状数组的题解**
**~~摘自机房十级爷~~**
//类似于dp思想  ，sum[i]表示以i结尾的话 ，当前ans的方案数 
/*我们考虑一下这个问题 ，由于题目中说了 ， 只能是连续的一段 ， 所以我们很自然的想到了 
前缀和的形式 ，由于数据太大 ，所以采用离散化 ， 对于每一种分法 ， 也就是sum[i]有两种可能 ，
为正或为负 ， 由于我们离散化了， 所以为负的点 在sum【0】的左边 ， 为正的点在sum【0】右边 。
所以在右边的 ， 可以对答案做出贡献 ， 所以把 sum【0】 初始化为 1 ；
//sum[0] 左边 ， 为负 ， 前缀和为零 ， 所以他的ans每次都为零 ， 如果这个序列最后相加小于零 （sum[n])小于
零的话 ， 答案就是零 ， 如果最后为正 ，那么对于以后的也没有什么影响...（因为前缀和相加0） 
在sum【0】右边 ，那么就为正 ，每次加上前缀和，为什么是前缀和 
就比如下面 
sum[1] = 1  ans = 1; 
sum[2] = 0  ans = 0;
sum[3] = 5  ans = 2;
因为在sum[3]的时候 2 + ３也是可以构成单独的一组，所以方案数需要累加 

 
```
```cpp
#include<bits/stdc++.h>
using namespace s td;
int a[100020] , sum[100020];
const int p = 1000000009;
int n ;
int c[100020];
void add(int x ,int y){
	for(int i = x; i <= n + 1; i += (i & (-i))){
		c[i] += y;
		c[i] %= p;
	}
}
int Sum(int x){
	int re = 0;
	for(int i = x ; i > 0 ; i -= (i & (-i))){
		re =(re + c[i]) % p;
	}
	return re % p;
}
long long  ans;
int main () {
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++){
	   scanf("%d",&sum[i]);
	   sum[i] += sum[i - 1];
 	   a[i] = sum[i];
	}
     int m = n;
	 sort(a  , a + 1 + m);
	 m = unique(a , a + m + 1 )  - a; 
	 for(int i = 0 ;i <= n;i++){
	 	sum[i] = lower_bound(a , a + m+1 , sum[i]) -  a + 1;
	 }	
	 add(sum[0] , 1);
	 for(int i = 1 ; i <= n ; i++){
	 	ans = Sum(sum[i]);
	 	add(sum[i] , ans);
	 }
	 cout << ans % p << endl;
}
```


---

## 作者：Paranoid丶离殇 (赞：2)

## 【题目背景】

Generic Cow Protests, 2011 Feb

## 【题目描述】

约翰家的N 头奶牛正在排队游行抗议。一些奶牛情绪激动，约翰测算下来，排在第i 位的奶牛的理智度为Ai，数字可正可负。

约翰希望奶牛在抗议时保持理性，为此，他打算将这条队伍分割成几个小组，每个抗议小组的理智度之和必须大于或等于零。奶牛的队伍已经固定了前后顺序，所以不能交换它们的位置，所以分在一个小组里的奶牛必须是连续位置的。除此之外，分组多少组，每组分多少奶牛，都没有限制。

约翰想知道有多少种分组的方案，由于答案可能很大，只要输出答案除以1000000009

 的余数即可。

**【输入格式】**

• 第一行：单个整数N，1≤*N*≤100000



• 第二行到第N + 1 行：第i + 1 行有一个整数Ai，−105≤*A**i*≤105



**【输出格式】**

单个整数：表示分组方案数模1000000009

 的余数

**【输入样例】**

```
4
2
3
-3
1
```

**【输出样例】** 

```
4  
```

## 说明：

解释:如果分两组，可以把前三头分在一组，或把后三头分在一组；如果分三组，可以把中间两头分在一组，第一和最后一头奶牛自成一组；最后一种分法是把四头奶牛分在同一组里。

**题解：**

记录前缀理智和sum[i]，l ~ r 可分成一组 当且仅当sum[r] >= sum[l-1]；

令dp[i]表示以i作为某一段的结尾的分组方式。dp[n]就是要求的答案

dp[i]=∑dp[j] ……j<i且sum[j]<=sum[i]；

<=sum[i]的dp[j]的和可以使用树状数组维护。

因此，先以sum[i]离散化，每次动态查询，动态修改

特别的 ： dp[0] = 1,优先插入；

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5e5 + 5, mod = 1e9 + 9;
typedef long long LL;
int n, k = -1, sum[N], b[N], c[N];
int lowbit(int x) { return x & -x; }
void add(int x, int k) {
    for( ;x <= n + 5; x += lowbit(x)) (c[x] += k) %= mod;
}
int getsum(int x) {
    int res = 0;
    for( ; x ;x -= lowbit(x)) (res += c[x]) %= mod;
    return res;
}
int main () {
    cin >> n;
    for(int i = 1;i <= n;i ++) 
        cin >> sum[i], sum[i] += sum[i-1], b[i] = sum[i];
    sort(b + 1, b + n + 1);
    for(int i = 0;i <= n;i ++) 
        sum[i] = lower_bound(b+1, b+n+1, sum[i]) - b + 2; 
    LL ans = 0;
    add(sum[0], 1);
    for(int i = 1;i <= n;i ++) {
        ans = getsum(sum[i]);
        add(sum[i], ans);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2344)
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;要写$DP$的话，很容易看出来：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(i)$：前$i$头牛的分组方案。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$S(i)=\sum_{j=1}^ia_j$，则状态转移方程可描述如下：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle DP(i)=\sum_{j=0}^{i-1}[S_i-S_j\ge0]\times DP(j)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其中方括号的值由命题的真伪决定（模拟$if$语句）。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后你把暴力程序交上去，你就可以得到——惊人的$90$分！  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~所以数据这么水，如果你考试的时候遇到了干嘛还想优化呢？直接去切下一题吧！~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;再弄一下显而易见的移项——  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle DP(i)=\sum_{j=0}^{i-1}[S_i\ge S_j]\times DP(j)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于我太蒟了，所以看到这个东西认不得它是二维偏序。不过我们可以发现如果把$j$用时间这一维来代替的话，这个实际上是在一个决策点集合中进行二分，所有$S_j$比$S_i$小的$j$都会被加到$DP(i)$里面。然后我们就想到了——  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;树状数组，~~权值线段树，01Trie~~，平衡树。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于这个$S$最多可以降到$N\times \min\{a\}$，也就是$-10^{10}$，所以直接套树状数组是不太现实的（或者，因为我实在是太蒟了），所以我写了一棵平衡树$Splay$，常数大到起飞，但是确实可以过。~~你可以在rank榜的末尾看见我~~  
# 代码
```cpp
#include <cstdio>

const int mod = 1000000009;
const int MAXN = 100005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ){ f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ), x = -x; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

int ch[MAXN][2], par[MAXN], key[MAXN], val[MAXN], s[MAXN];
int DP[MAXN];
int S[MAXN];
int N, rt, len;

bool chk( const int x )
{
	return ch[par[x]][1] == x;
}

void pushup( const int x )
{
	s[x] = ( ( s[ch[x][0]] + s[ch[x][1]] ) % mod + val[x] ) % mod;
}

void rotate( const int x )
{
	if( ! x ) return;
	int y = par[x], z = par[y], sx = chk( x ), sy = chk( y ), son = ch[x][! sx];
	if( z ) ch[z][sy] = x;
	if( y ) par[y] = x, ch[y][sx] = son;
	ch[x][! sx] = y, par[x] = z;
	if( son ) par[son] = y;
	pushup( y ), pushup( x ), pushup( z );
}

void splay( const int x, const int tar = 0 )
{
	int y, z;
	while( ( y = par[x] ) ^ tar )
	{
		z = par[y];
		if( z ^ tar )
		{
			if( chk( y ) == chk( x ) ) rotate( y );
			else rotate( x );
		}
		rotate( x );
	}
	if( ! tar ) rt = x;
}

void insert( const int nKey, const int nVal )
{
	int p = rt, fa = 0;
	while( p && nKey ^ key[p] ) fa = p, p = ch[p][nKey > key[p]];
	if( p ) val[p] = ( val[p] + nVal ) % mod;
	else
	{
		p = ++len;
		if( len == 1 ) rt = p;
		if( fa ) par[p] = fa, ch[fa][nKey > key[fa]] = p;
		val[p] = nVal, key[p] = nKey, ch[p][0] = ch[p][1] = 0;
	}
	pushup( p );
	splay( p );
}

void find( const int nKey )
{
	if( ! rt ) return;
	int p = rt;
	while( ch[p][nKey > key[p]] && key[p] ^ nKey ) p = ch[p][nKey > key[p]];
	splay( p );
}

int succ( const int nKey )
{
	find( nKey );
	if( key[rt] > nKey ) return rt;
	int p = ch[rt][1];
	while( ch[p][0] ) p = ch[p][0];
	return p;
}

int main()
{
	read( N );
	for( int i = 1 ; i <= N ; i ++ ) read( S[i] ), S[i] += S[i - 1];
	insert( -0x3f3f3f3f, 0 );
	insert( 0x3f3f3f3f, 0 );
	insert( S[0], 1 );
	for( int i = 1 ; i <= N ; i ++ )
	{
		int p = succ( S[i] );
		splay( p );
		DP[i] = s[ch[rt][0]] % mod;
		insert( S[i], DP[i] );
	}
	write( DP[N] ), putchar( '\n' );
	return 0;
}
```

---

## 作者：hahalidaxin2 (赞：1)

【思路】

线性DP+BIT加速+离散化。

设d[i]表示前i头奶牛的分法，则有转移方程式如下：

     d[i]=sigma{ d[j]( j<i && S(j+1,i)>=0 ) }

其中sigma表示求和、S代表区间和。

如果令sum[]表示前缀和，则可以进一步得出转移条件：存在j<i且sum[j]<=sum[i]

BIT加速：如果DP枚举到i，令C[x]表示i之前sum==x的所有d之和，则d[i]为小于sum[i]的所有d之和，可以用BIT求出小于sum[i]的区间和。

离散化：sum的情况最多有n+1种而其范围可能很大，所以考虑对sum进行离散化。

  
另外有0的情况可以考虑将BIT下标进行偏移或hash到其他范围。

【代码】

```cpp

#include<cstdio>
#include<iostream>
#include<algorithm>
#define FOR(a,b,c) for(int a=(b);a<=(c);a++)
using namespace std;

const int maxn = 100000+10;
const int MOD=1000000009;

int sum[maxn],a[maxn];
int hash[maxn],cnt;
int n;

int C[maxn],Max;
int lowbit(int x) { return x&(-x); }
int Sum(int x) {
    x++;
    int res=0;
    while(x>0) {
        res = (res+C[x])%MOD;
        x-=lowbit(x);
    }
    return res;
}
void Add(int x,int v) {
    x++;
    while(x<=Max+1) {
        C[x] = (C[x]+v)%MOD;
        x+=lowbit(x);
    }
}

int find(int x) {
    return lower_bound(hash,hash+cnt+1,x)-hash;
}

int main() {
    scanf("%d",&n);
    FOR(i,1,n) {
        scanf("%d",&a[i]);
        sum[i]=sum[i-1]+a[i];
        Max=max(Max,sum[i]);
    }
    sort(sum,sum+n+1);         //将0计入 
    hash[0]=sum[0];
    FOR(i,1,n) if(sum[i]!=sum[i-1]) {
        hash[++cnt]=sum[i];
    }
    Add(find(0),1);
    int tot=0,ans=0;
    FOR(i,1,n) {
        tot += a[i];
        ans = Sum(find(tot))%MOD;
        Add(find(tot),ans);
    }
    printf("%d\n",ans);
    return 0;
}

```

---

