# loidc，想想看

## 题目背景

话说 loidc 现在正在家闲的无聊，这天 loidc 正在观看比赛，他突然很有兴趣想了解一段时间内中国队获得金牌的情况。

## 题目描述

还有一点，loidc 有特殊能力，可以预知未来，他可以准确的猜到中国队在某一个单位时间内获得的金牌数。但是，还有但是！由于工作量太大，再加上猜金牌要费很多的体力，所以他无法准确的计算出一段时间内获得的金牌数最大的单位时间是哪个，就因为这样 loidc 很郁闷。他思索来思索去就想到了你，因为他知道你是个 OIer，所以他对你呵呵一笑就把问题交给你了，loidc 希望你能在 1 s 内得出答案。


## 说明/提示

$30\%$：$n \le 1000$，$m \le 1000$。

$100\%$：$n \le {10}^5$，$m \le {10}^5$。

其他有关输入输出均小于 `maxlongint`。

数据保证 $a_i$ 没有相同的。

## 样例 #1

### 输入

```
5
2 3 4 5 6
5
1 1
1 2
2 3
3 4
4 5
```

### 输出

```
1
2
3
4
5
```

# 题解

## 作者：FQR_ (赞：14)

看到题解区的大佬们有用线段树的，有用单调队列的，只会暴力的本蒟蒻大受震撼。

___

### 题目简化：

给定长度为 $n$ 的数组 $a$ ，求 $a_x$ 和 $a_y$ 之间最大的数的位置。

___

### 思路：

首先，读入，不必多说。

然后，我们用`maxn`表示最大数的值，用 `ans` 表示最大数的位置。遍历 $a_x$ 和 $a_y$ 之间的所有数。如果 $a_i$ 比`maxn`大，就把`maxn`替换为 $a_i$ ，把`ans`替换为 `i`。 

最后，输出`ans`，就得到答案了。

___

### AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,a[100005],x,y;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>m;
	while(m--)//循环m次
	{
		cin>>x>>y;
		int maxn=-1,ans=0;//maxn为最大数的值，ans为最大数的位置
		for(int i=x;i<=y;i++)//从x遍历到y
		{
			if(a[i]>maxn)
			{
				maxn=a[i];ans=i;
			}//如果a[i]大于当前最大数的值，就把最大值替换为a[i]，位置替换成i
		}
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：LOI_imcy (赞：4)

可以放弃思考，直接上线段树

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int num[1010010];
int t[1011000];
struct xd_tree
{
    int l,r,p;
    int add,max;
}tree[1010010*4];
void build(int p,int l,int r)
{
    tree[p].l = l , tree[p].r = r;
    if(l == r)
    {
        tree[p].max = num[l];
        return ;
    }
    int mid = ( l + r ) >> 1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    tree[p].max = max(tree[p*2].max,tree[p*2+1].max);
}
int ask(int p,int l,int r)
{
    if(tree[p].l >= l && tree[p].r <= r)
        return tree[p].max;
    int ans = 0;
    int mid = (tree[p].l + tree[p].r) >> 1;
    if(l <= mid)
        ans = max(ans,ask(p*2,l,r));
    if(r > mid)
        ans = max(ans,ask(p*2+1,l,r));
    return ans;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i ++)
        scanf("%d",&num[i]) , t[num[i]] = i;
    build(1,1,n);
    int q;
    scanf("%d",&q);
    for(int i = 1 ; i <= q ; i ++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        cout<<t[ask(1,l,r)]<<endl;
    }
    return 0;
}
```

---

## 作者：Exber (赞：2)

## 做法
暴力……

对于每个询问，可以直接暴力求出区间最大值。

因为题目上说的 $x_i\ge x_{i-1},y_i\ge y_{i-1}$，所以每个时间段实际上只会被访问一次，时间复杂度并不是 $O(nm)$ 而是 $O(n)$。

## AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

int n,m;
ll a[100005];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		int mj=l; // 最大值的下标
		for(int j=l;j<=r;j++)
		{
			mj=a[j]>a[mj]?j:mj; // 暴力求解 
		}
		printf("%d\n",mj);
	}
	return 0;
}
```


---

## 作者：Limerick (赞：2)

同样,感谢yg大神对我的指导.

本来本蒟蒻是想来练一练RMQ的,没先到用树状数组过了....

本蒟蒻对这题数据也是无语的,树状数组和线段树居然不爆空间......

好了,看楼下两位大神分别用了RMQ和线段树,于是本蒟蒻决定发一波树状数组,其实树状数组应该跑的最快,线段树常数太大......

树状数组求区间最大值,应该算得上是模板题了吧,

在来看维护区间最大值的算法，我们先看一整段区间[1，n]都需要初始化的情况。（即 h[] 数组都为0，现在需要用 a[] 数组更新 h[] 数组）

```cpp
    void updata(int i, int val)  
    {  
        while (i <= n)  
        {  
            h[i] = max(h[i], val);  
            i += lowbit(i);  
        }  
    }  
```
这样是也可行的，于是我们就有了一个O（n\*logn）的维护方法，即当要更新一个数的时候，把 h[] 数组清零， 然后用数组 a[] 去更新 h[] 数组
但这个复杂度显然太高了。

但是,我们不难发现：对于x，可以转移到x的只有，x-2^0，x-2^1，x-2^2，.......，x-2^k （k满足2^k < lowbit(x)且2^(k+1)>=lowbit(x)）

举例:

若 x = 1010000= 1001000 + lowbit(1001000) = 1001000 + 1000 = 1001000 + 2^3= 1001100 + lowbit(1001100) = 1001100 + 100

= 1001100 + 2^2= 1001110 + lowbit(1001110) = 1001110 + 10 = 1001110 + 2^1= 1001111 + lowbit(1001111) = 1001111 + 1

= 1001111 + 2^0

所以对于每一个h[i]，在保证h[1...i-1]都正确的前提下，要重新计算h[i]值的时间复杂度是O（logn），具体方法如下：

```cpp
    h[x] = a[x];  
    lx = lowbit(x);  
    for (i=1; i<lx; i<<=1)  
    h[x] = max(h[x], h[x-i]);  
    x += lowbit(x);  
```
这样，我们就可以得到一个和树状数组维护区间合算法很像的算法
```cpp
    void updata(int x)  
    {  
        int lx, i;  
        while (x <= n)  
        {  
            h[x] = a[x];  
            lx = lowbit(x);  
            for (i=1; i<lx; i<<=1)  
                h[x] = max(h[x], h[x-i]);  
            x += lowbit(x);  
        }         
    }  
```
这个算法的时间复杂度是O((logn)^2)，所以现在就可以在O（(logn)^2）的时间内完成最值的区间维护了。
本段文字引用:http://blog.csdn.net/u010598215/article/details/48206959

接着就很好办了,把输入的数据按序编号,然后输出找到的最大值的编号即可.

好了,闲话少叙,贴上代码:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
```
/\*
P2311 loidc,想想看 题解

\*/
const int N=1011000;//居然没有爆空间,数据太弱

long long n,m,i,a[N],t[N\*4],k1,k2,j,f[N];//注意:此处树状数组要开到N\*4

/\*
接下来是树状数组求区间最大值模板,详情见上面的分析

\*/
```cpp
long long lowbit(long long x){
    return x&(-x);
}
void tree(long long x){
    long long l;
    while(x<=n){
        t[x]=a[x];
        l=lowbit(x);
        for(long long h=1;h<l;h<<=1){
            t[x]=max(t[x],t[x-h]);
        }
        x+=lowbit(x);
    }
    return;
}
long long sum(long long l,long long r){
    long long ans=0;
    while(r>=l){
        ans=max(ans,a[r]);
        r--;
        for(;(r-lowbit(r))>=l;r-=lowbit(r)){
            ans=max(ans,t[r]);
        }
    }
    return ans;
}
//模板结束
int main(){
    scanf("%lld",&n);
    for(i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        f[a[i]]=i;//将输入数据编号
        tree(i);//初始化
    }
    scanf("%lld",&m);
    for(i=1;i<=m;i++){
        scanf("%lld%lld",&k1,&k2);
        printf("%lld\n",f[sum(k1,k2)]);//将找到的最大值的编号输出
    }
    system("pause");
    exit(0);
}
```
接下来,我们来聊一聊RMQ的做法,
首先普及一下,什么是RMQ:

RMQ的主要运用是Sparse\_Table算法（简称ST算法）,它可以在O(nlogn)的预处理以后实现O(1)的查询效率，即整体时间复杂度为O(nlogn)-O(1)。

RMQ的主要原理就是dp,用 a[1..n]表示一组数，F[i,j]表示从a[i]到a[i+2^j-1]这个范围内的最大值，也就是以a[i]为起点连续2^j个数的最大值，由于元素个数为2^j个，所以从中间平均分成两部分，每一部分的元素个数刚好为2^(j-1)个.

很明显，整个区间的最大值一定是左右两部分最大值中的较大值，满足动态规划的最优性原理：

状态转移方程：F[i,j]=max(F[i,j-1],F[i+2^(j-1),j-1])

边界条件为：F[i,0]=a[i]

我们可以采用自底向上的算法递推出所有符合条件的f[i,j]的值，就可以在O(nlogn)的时间复杂度内预处理F数组。

例如：f[2,3]保存的是a[2],a[3],a[4],……,a[9]中的最小值，而f[2,3]=

min(f[2,2],f[6,2])=min((a[2],a[3],a[4],a[5]),(a[6],a[7],a[8],a[9]))

预处理F数组代码：

```cpp
    for(i=1;i<=n;i++)f[i][0]=a[i];   //初始化
    for(j=1;j<=int(log(n)/log(2));j++) //递推
           for(i=1;i+(1<<j)-1<=n;i++) 
                      f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]); 
```
对于询问[L,R],求出最大的x,满足2^x<=R-L+1,即x=int(log(R-L+1)/log(2))
[L,R]=[L,L+2^x-1] ∪[R+1-2^x,R]，两个子区间元素个数都是2^x个，所以RMQ(L,R)=max(F[L,x],F[R+1-2^x,x])

询问操作代码：

```cpp
     int Ask(int L,int R)
     {   int k;
          k=int(log(R-L+1)/log(2));
          return max(f[L][k],f[R+1-(1<<k)][k]);
     }
```
该算法总时间复杂度为O(NlogN+M)
本段文字引用https://wenku.baidu.com/view/4e0e4778f111f18582d05a03.html?from=search

好了,后面的就好办了,跟树状数组一样,输出找到最大值的编号,

这又怎么做呢？其实很简单:

只需要将状态转移方程嵌在a数组利用即可:

f[i][j]=(a[f[i][j-1]]>a[f[i+(1<<(j-1))][j-1]])?f[i][j-1]:f[i+(1<<(j-1))][j-1]

询问时也一样:return a[f[l][k]]>a[f[r+1-(1<<k)][k]]?f[l][k]:f[r+1-(1<<k)][k]

是不是很简单呢?


---

## 作者：I_have_been_here (赞：1)

提供一种线段树的新做法

# 题目分析

读完题面，概括一下就是给出 $m$ 个询问，每一次询问有 $x$, $y$ 两个整数，表示一个区间，现在要求对于每一次询问求出这个区间内最大值在这个长度为 $n$ 的序列的位置，考虑直接使用线段树结构体维护即可。

# 思路解析

对于线段树的处理，如果这道题仅仅是求最大值，那么就是板子，这里我们考虑将这个最大值换成维护一个结构体变量，即同时维护最大值和这个最大值的位置，那么在每一次递归中通过比较最大值，来同时更新每一层返回答案的结构体变量即可，其他和板子没什么区别。

注意，每一次询问中，返回的都应该是一个结构体类型的变量，这样，我们根据每一次递归中左右子树相对目标区间的位置，继续往下递归，因为我们比较大小是结构体里的一个参数，对于原变量不能直接取最大，所以说我们这里需要直接求出向下递归的值再进行比较，否则会超时。

详细看代码吧。

# AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
struct K {
	int id, M;
}; // 维护的树中的结构体
struct node {
	int l, r;
	K p; // 维护
} t[maxn << 2];
int n, q, a[maxn];
void build(int i, int l, int r) {
	t[i].l = l, t[i].r = r;
	if (l == r) {
		t[i].p.id = l; // 建树，区间内一个数就是它自己
		t[i].p.M = a[l]; // 同上
		return;
	}
	int mid = l + r >> 1;
	build(i << 1, l, mid);
	build(i << 1 | 1, mid + 1, r);
	t[i].p.id = t[i << 1].p.M > t[i << 1 | 1].p.M ? t[i << 1].p.id : t[i << 1 | 1].p.id;
	t[i].p.M = max(t[i << 1].p.M, t[i << 1 | 1].p.M); // 分别向上传递，比较大小
}
K query(int i, int l, int r) {
	if (l <= t[i].l && t[i].r <= r) {
		return t[i].p;
	}
	K ans; // 使用结构体变量传递
	ans.M = -0x3f3f3f3f;
	if (t[i << 1].r >= l) {
		K ret = query(i << 1, l, r); // 这里需要优化常数
		ans = ret.M > ans.M ? ret : ans; // 比较大小
	}
	if (t[i << 1 | 1].l <= r) {
		K ret = query(i << 1 | 1, l, r);
		ans = ret.M > ans.M ? ret : ans;
	} // 同上
	return ans;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	build(1, 1, n);
//	for (int i = 1; i <= n * 2; i++)
//		printf("%d %d %d %d %d\n", t[i].l, t[i].r, t[i].p.M, t[i].p.id, i);
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		K f = query(1, x, y);
		cout << f.id << endl;
	}
}

```


---

## 作者：TheSky233 (赞：1)

## Description

给定数组 $\{a\}$，有 $m$ 组询问，每组询问要求回答区间 $\left[l,r\right]$ 内最大值的下标。

## Solution

做法：[ST 表](https://www.luogu.com.cn/problem/P3865)。

ST 表是一种回答区间 RMQ 的数据结构，可以做到 $\mathcal O(n \log_2 n)$ 预处理，$\mathcal O(1)$ 查询。具体地说，$f_{i,j}$ 中存储的是原来数组中从 $i$ 开始 $2^j$ 个数的最大值。查询时，求出询问区间的最大值即可。

因为数据保证 $a_i$ 没有相同的，所以我们可以建立一个映射数组存储 $\{a_i,i\}$ 的对应关系。

时间复杂度：$\mathcal O(n \log_2 n + m)$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T> inline void read(T& x) {
	x=0;T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=x*f;
	return;
}
template <typename T,typename ...Arg>void read(T& x,Arg& ...arg){
	read(x);
	read(arg...);
}
template <typename T>void write(T x) {
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
template <typename T,typename ...Arg>void write(T& x,Arg& ...arg){
	write(x);
	putchar(' ');
	write(arg...);
}

const int N=1e6+5;

int n,m,l,r;
int ST[N][21],t[N];

int query(int l,int r){
	int k=__lg(r-l+1);
	return max(ST[l][k],ST[r-(1<<k)+1][k]);
}


int main(){
	read(n);
	for(int i=1;i<=n;i++) read(ST[i][0]),t[ST[i][0]]=i;
	for(int j=1;j<=21;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			ST[i][j]=max(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
		}
	}
	read(m);
	for(int i=1;i<=m;i++){
		read(l,r);
		write(t[query(l,r)]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：YuntianZhao (赞：1)

# P2311

这篇是一个指针版线段树的题解。

其实指针版线段树个人认为非常好理解。

对于每一个节点，d 表示区间的最大值，l 表示区间的左端点，r 表示区间右端点。ls (left son) 指向左儿子，rs (right son) 指向右儿子。

```c++
struct Node {
  int d;
  int l, r;
  Node *ls, *rs;
  Node(int l = 0, int r = 0):
      l(l), r(r), d(0), ls(NULL), rs(NULL) {};
};
```

指针版线段树有一个比较好的特点就是可以动态的 new 出内存空间。

```c++
Node *build(int l, int r) {
  Node *p = new Node(l, r);
  if (l == r) {
    p->d = a[l];
    return p;
  }
  int mid = (l + r) / 2;
  p->ls = build(l, mid);
  p->rs = build(mid + 1, r);
  p->d = max(p->ls->d, p->rs->d);
}
```

询问的话其实就是一个分类讨论，分四种情况：

- 询问区间就是当前节点覆盖的区间

- 询问区间包含在当前节点左儿子覆盖的区间

- 询问区间包含在当前节点右儿子覆盖的区间

- 询问区间包含在当前节点左儿子和右儿子覆盖的区间

```c++
int query(Node *p, int l, int r) {
  if (p->l == l && p->r == r) {
    return p->d;
  }
  if (p->ls->r >= r) {
    return query(p->ls, l, r);
  } else if (p->rs->l <= l) {
    return query(p->rs, l, r);
  } else {
    return max(query(p->ls, l, p->ls->r), query(p->rs, p->rs->l, r));
  }
}
```

然后题目要求求出最大的位置，就用 map 记录一下就好了。

完整代码如下（前面有些定义的没有用到的常量请忽略）：

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const double eps = 1e-6;

int n, m, k;

int a[maxn];
map<int, int> t;

struct Node {
  int d;
  int l, r;
  Node *ls, *rs;
  Node(int l = 0, int r = 0):
      l(l), r(r), d(0), ls(NULL), rs(NULL) {};
};

Node *root;

Node *build(int l, int r) {
  Node *p = new Node(l, r);
  if (l == r) {
    p->d = a[l];
    return p;
  }
  int mid = (l + r) / 2;
  p->ls = build(l, mid);
  p->rs = build(mid + 1, r);
  p->d = max(p->ls->d, p->rs->d);
}

int query(Node *p, int l, int r) {
  if (p->l == l && p->r == r) {
    return p->d;
  }
  if (p->ls->r >= r) {
    return query(p->ls, l, r);
  } else if (p->rs->l <= l) {
    return query(p->rs, l, r);
  } else {
    return max(query(p->ls, l, p->ls->r), query(p->rs, p->rs->l, r));
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    t[a[i]] = i;
  }
  root = build(1, n);
  scanf("%d", &m);
  int l, r;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &l, &r);
    k = query(root, l, r);
    printf("%d\n", t[k]);
  }
  return 0;
}
```

---

## 作者：cabasky (赞：1)

注意这句话

**注意对于第i个提问和第i+1个提问严格的有xi<=xi+1，yi<=yi+1。**

这不就是明显的单调队列吗

为什么都写线段树呢

贴上AC代码 期望复杂度o(n)

注意这一次的左端点可能大于上一次的右端点 所以每一次入队的指针 j=max(yest+1,x) 就是因为这个WA了一次

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
long long a[100010];
int line[100010],head,tail,yest,n,m;
void add(int p){
    while(head<=tail&&a[p]>a[line[tail]]) tail--;
    tail++;
    line[tail]=p;
}
int main(){
    int x,y,j;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    head=1;
    tail=0;
    yest=0;
    for(int i=1;i<=m;i++){
        scanf("%d %d",&x,&y);
        while(head<=tail&&line[head]<x) head++;
        j=yest+1;
        if(x>j) j=x;
        for(;j<=y;j++) add(j);
        yest=y;
        printf("%d\n",line[head]);
    }
    return 0;
}
```

---

## 作者：newbeeglass (赞：0)

线段树裸题。

主要是输出序号有一点点烦，线段树结构体里用来维护最大值的 ```pre``` 变量需要用另一个结构体来定义，```pre``` 不仅维护最大值，也维护了这个最大值的序号，最后查询的时候直接返回整个 ```pre```，输出它所对应的序号就好了，解释在代码里。

### AC code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000005],m;
struct node{
	int num,sum;
}; //num 表示序号，sum表示最大值 
struct tree{
	int l,r;
	node pre;
}t[4000005];
node maxx(node x,node y){ //定义一个取最大值的函数 
	if(x.sum>y.sum){
		return x;
	}
	return y;
}
void pushup(int p){ //pushup 有点烦，单独写 
	if(t[p*2].pre.sum>t[p*2+1].pre.sum){
		t[p].pre.sum=t[p*2].pre.sum;
		t[p].pre.num=t[p*2].pre.num;
	}
	else{
		t[p].pre.sum=t[p*2+1].pre.sum;
		t[p].pre.num=t[p*2+1].pre.num;
	}
}
void build(int p,int x,int y){ //建树 
	t[p].l=x;
	t[p].r=y;
	if(x==y){
		t[p].pre.sum=a[x];
		t[p].pre.num=x; //别忘了存序号 
		return;
	} 
	int mid=x+y>>1;
	build(p*2,x,mid);
	build(p*2+1,mid+1,y);
	pushup(p);
}
node ask(int p,int x,int y){ //查询函数直接用 node，更方便 
	if(x<=t[p].l && y>=t[p].r){
		return t[p].pre;
	}
	int mid=t[p].l+t[p].r>>1;
	if(x<=mid && y>mid){
		return maxx(ask(p*2,x,y),ask(p*2+1,x,y));
	}
	if(x<=mid){
		return ask(p*2,x,y);
	}
	if(y>mid){
		return ask(p*2+1,x,y);
	}
}
main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	cin>>m;
	while(m--){
		int x,y;
		cin>>x>>y;
		node ans=ask(1,x,y);
		cout<<ans.num<<endl; //输出序号 
	}
}

```


---

## 作者：huangwenlong (赞：0)

全裸的RMQ，Sparse Table 算法直接过

设f(i,j)表示从第i个数起连续2^j个数中的最值，状转方程f(i,j)=max{f(i,j-1), f(i+2^(j-1), j-1)}

区间[l,r]的最值Q(x,y)=max{f(x,k), f(y-2^k+1,k)}，其中k=log2(y-x+1)向下取整

写代码的时候注意加减运算符高级于<<运算符，还有就是哪里有-1哪里没有这类的细节问题


    
    
    
        
            
```cpp
#include <iostream>
#include <cmath>
#define maxn 100005
using namespace std;
int n,m;
int rmq[maxn][20];
int a[maxn];
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];    
    //init
    for(int i=1;i<=n;++i)
        rmq[i][0]=i;
    int limit=log(n)/log(2)+1;
    for(int j=1;j<=limit;++j)
    {
        for(int i=1;i<=n;++i)
        {
            if(i+(1<<j-1)-1<=n)
            {
                if(a[rmq[i][j-1]] > a[rmq[i+(1<<(j-1))][j-1]])
                    rmq[i][j]=rmq[i][j-1];
                else
                    rmq[i][j]=rmq[i+(1<<(j-1))][j-1];
            }
        }
    }
    cin>>m;
    //query
    for(int i=0;i<m;++i)
    {
        int x,y;
        cin>>x>>y;
        int ans;
        int k=log(y-x+1)/log(2);
        if(a[rmq[x][k]] > a[rmq[y-(1<<k)+1][k]])
            ans=rmq[x][k];
        else
            ans=rmq[y-(1<<k)+1][k];
        cout<<ans<<endl;
    }
    return 0;
}
```

---

