# [ABC309F] Box in Box

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc309/tasks/abc309_f

$ N $ 個の箱があります。 $ i $ 番目の箱は高さ・幅・奥行きがそれぞれ $ h_i,w_i,d_i $ の直方体の形をしています。

二つの箱であって、必要ならば回転させることで片方の高さ・幅・奥行きがもう片方の高さ・幅・奥行きをそれぞれ上回るようなものが存在するかを判定してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ h_i,w_i,d_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

$ 2 $ 番目の箱を回転させて高さと奥行きを入れ替えると、$ 3 $ 番目の箱が高さ・幅・奥行きをそれぞれ上回ります。

## 样例 #1

### 输入

```
3
19 8 22
10 24 12
15 25 11```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
19 8 22
10 25 12
15 24 11```

### 输出

```
No```

## 样例 #3

### 输入

```
2
1 1 2
1 2 2```

### 输出

```
No```

# 题解

## 作者：DengDuck (赞：9)

考场上的我：一眼三维偏序，我不会，再见。

但是呢，这道题只判断存在性，而且是要求严格覆盖，所以有更简单的做法。

首先我们将三项排序，因为盒子是可以随意旋转的，接下来，我们将其记作 $(a,b,c)$。

我们可以利用树状数组，比较好写。

首先我们排序 $a$ 删掉一项，接下来对 $b$ 进行离散化利于操作。

通常我们用树状数组求解二维偏序的方法在于把树状数组当成桶，但是在这里我们不需要问有多少，只需要问有没有，所以我们只需要记录最小的那一项与当前项比较。

所以我们将 $b$ 当做下标，将 $c$ 当做值，看区间 $[1,b-1]$ 中的最小值是否小于当前项即可。

时间复杂度是 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e6+5;
struct node
{
	LL a,b,c;
}a[N];
LL n,cnt,t[N];
LL lowbit(LL x)
{
	return x&-x;
}
LL query(LL x)
{
	LL mn=t[0];
	while(x)
	{
		mn=min(mn,t[x]);
		x-=lowbit(x);
	}
	return mn;
}
void upd(LL x,LL k)
{
	while(x<=cnt)
	{
		t[x]=min(t[x],k);
		x+=lowbit(x);
	}
}
map<LL,LL>ma;
bool cmp(node x,node y)
{
	return x.b<y.b;
}
bool cmp2(node x,node y)
{
	return x.a<y.a;
}
int main()
{
	memset(t,127,sizeof(t));
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&a[i].a,&a[i].b,&a[i].c);
		if(a[i].a>a[i].b)swap(a[i].a,a[i].b);
		if(a[i].b>a[i].c)swap(a[i].c,a[i].b);
		if(a[i].a>a[i].b)swap(a[i].a,a[i].b);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(a[i].b!=a[i-1].b)ma[a[i].b]=++cnt;
	}
	for(int i=1;i<=n;i++)
	{
		a[i].b=ma[a[i].b];
	}
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++)
	{
		LL l=i,r=i;
		while(a[r+1].a==a[l].a)r++;
		for(int j=l;j<=r;j++)
		{
			if(query(a[j].b-1)<a[j].c)
			{
				puts("Yes");
				return 0;
			}
		}
		for(int j=l;j<=r;j++)
		{
			upd(a[j].b,a[j].c);
		}
		i=r;
	}
	puts("No");
	return 0;
}
```

---

## 作者：Pengzt (赞：6)

[ABC309F](https://www.luogu.com.cn/problem/AT_abc309_f)

首先它说可以旋转啊，显然我让小的相比较是更优的。

然后就变为了三维偏序的存在性问题。

然后直接排序后树套树即可，然后发现这里只需要 $b\in [l,r]$ 时是否存在 $c$ 小于 $qc$，可以直接维护 $b\in[l,r]$ 时 $c$ 的最小值，因为是前缀最小值，树状数组即可维护。

但我考试写的是线段树 + set，自带大常数，需要 ios。

[评测记录](https://atcoder.jp/contests/abc309/submissions/43379033)

---

## 作者：qzhwlzy (赞：3)

## 题目大意

有 $n$ 个箱子，第 $i$ 个箱子的长宽高分别为 $a_i,b_i,c_i$。在允许翻转的情况下，问是否存在两个盒子，一个盒子的长宽高都分别**严格**小于另一个的长宽高。

## 思路

不难想到，可以将长宽高排序后比较。不妨设 $a_i\le b_i\le c_i$，这样两个箱子比较只需要将 $a,b,c$ 分别比较即可。

现在问题变成了一个三维偏序，可以采用 CDQ 分治解决（~~但是不会~~）。所以我们考虑其它做法。不妨先按照 $a$ 排序，这样我们就消掉了一维的干扰。对于剩下的两维，只需要依次枚举 $b_i$，在查找是否存在满足 $j<i,b_j<b_i,c_j<c_i$ 的 $j$ 即可，我们可以用树状数组维护，将 $b$ 离散化后作为下标，$c$ 作为维护的值。这样只需要查找 $[1,b_i)$ 内 $c$ 的最小值，判断其是否小于当前的 $c_i$ 即可。

需要注意本题需要严格小于，于是我们要在 $a$ 相同的一段处理完之后统一更新树状数组。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 200005
using namespace std;
int n,a,b,c,uni[maxn],len,pos=1; struct node{int a,b,c; bool operator<(node x)const{return a<x.a;}}f[maxn];
int tr[maxn]; int lowbit(int x){return x&(-x);} void modify(int p,int v){for(;p<=len;p+=lowbit(p)) tr[p]=min(tr[p],v);}
int query(int p){int res=2000000000; for(;p>=1;p-=lowbit(p)) res=min(tr[p],res); return res;}
int main(){
	scanf("%d",&n); for(int i=1;i<=n;i++){
		scanf("%d%d%d",&a,&b,&c); f[i].a=min(min(a,b),c); f[i].c=max(max(a,b),c);
		f[i].b=a+b+c-f[i].a-f[i].c; uni[i]=f[i].b; tr[i]=2000000000;
	} sort(f+1,f+1+n); sort(uni,uni+1+n); len=unique(uni+1,uni+1+n)-uni-1;
	for(int i=1;i<=n;i++) f[i].b=lower_bound(uni,uni+1+len,f[i].b)-uni;
	for(int i=1;i<=n;i++){
		if(f[i].a>f[i-1].a) while(pos<i){modify(f[pos].b,f[pos].c); pos++;}
		if(query(f[i].b-1)<f[i].c){printf("Yes"); return 0;}
	}
	printf("No"); return 0;
}

```

---

## 作者：Unnamed114514 (赞：3)

[Problem Link](https://atcoder.jp/contests/abc309/tasks/abc309_f)

笑死，线段树端点写反了。

前置知识：[三维偏序，但是非严格](https://www.luogu.com.cn/problem/P3810)

容易发现这是一道三维偏序的题，但是从不严格变成了严格，我们来考虑对代码作出哪些变化：

- 对于 `c` 这一维，在查询时区间从 $[1,c]$ 变成 $[1,c-1]$ 即可。

- 对于 `b` 这一维，在移动指针 $t$ 时，把  $\le$ 改为 $<$ 即可。

这里有个非常 naive 的想法：因为第一维不会影响查询的区间，所以我们不管它。

但是，这样会 WA $3$ 个点。

所以，我们要考虑 `a` 这一维的贡献有什么影响：

注意到我们对 `a` 的处理是升序排序，但是此时我们在求解 `b` 和 `c` 两维时是默认了左边的 `a` 会对右边的 `a` 产生贡献的。但是，实际上，左边的 `a`是可以等于右边的 `a` 的，此时并没有产生贡献，所以我们还需要判断左边在 $[1,c-1]$ 内是否存在产生贡献的点。

本题只需要问我们是否存在，那么我们可以考虑维护对于 `c` 的 `a` 的最小值，这样如果这个最小值都比 `a` 大那么就是不存在的，反之，就是存在的。

最后还需要注意，对 `c` 进行一下离散化。

时间复杂度 $O(n\log^2n)$，空间复杂度 $O(n)$。

---

## 作者：Miss_SGT (赞：2)

#### 思路：
观察题目，所说“旋转”，其实是可以将长方体 $i$ 的 $a_{i}$，$b_{i}$，$c_{i}$ 任意排列，为了好比较，当然将三个值从小到大（倒着一样）排列；

然后很类似于三维偏序，但是要求 $i$ 三个值严格大于 $j$ 的三个值，这点 CDQ 分治是无法满足的。但是我们能知道 $a_{i} \ge a_{j}$，$b_{i} > b_{j}$，$c_{i} > c_{j}$ 的对数。再单独用树状数组维护 $a_{i} = a_{j}$，$b_{i} > b_{j}$，$c_{i} > c_{j}$ 的对数。最后一减就完了。

（思路很复杂，但也是一种解法）
#### 代码：
因为代码又长又臭，所以只展示 CDQ 分治和去重过程罢。

```cpp
void merge(int l,int r,long long &ans){
	if(l==r) return;
	int mid=(l+r)>>1;
	merge(l,mid,ans);merge(mid+1,r,ans);
	sort(a+l,a+mid+1,cmp1);
	sort(a+mid+1,a+r+1,cmp1);
	int l1=l,l2=mid+1;
	while(l1<=mid||l2<=r){
		if(l1<=mid&&(l2==r+1||a[l1].b<a[l2].b)){
			add(a[l1].c,1);
			l1++;
		}else{
			ans+=get(a[l2].c-1);
			l2++;
		}
	}for(int i=l;i<=mid;i++) add(a[i].c,-1);
}
```


```cpp
int lt=1;
sort(a+1,a+n+1,cmp);//按a排序 
a[n+1].a=2e9;
for(int i=1;i<=n;i++){
	if(a[i+1].a>a[i].a){//找到a相同的一段 
		int ls=lt;
		for(int j=lt;j<=i;j++){
			anst+=get(a[j].c-1);
			if(a[j+1].b!=a[j].b||j==i){//找到b相同的一段 
				for(int k=ls;k<=j;k++) 
					add(a[k].c,1);
				ls=j+1;
		}
			}for(int j=lt;j<=i;j++) add(a[j].c,-1);
		lt=i+1;
	}
}
```
#### 最后：

```cpp
puts(ans>anst？"Yes":"No");
```



---

## 作者：rzh01014 (赞：1)

# [abc309_f](https://www.luogu.com.cn/problem/AT_abc309_f)
### 题目描述
给出 $n$ 个盒子，每个盒子都有一个长宽高，盒子可以进行翻转，问是否存在两个盒子，使得一个盒子长宽高严格大于另一个盒子。
### 做法
首先将每个盒子的长宽高进行内部排序，再将盒子按长的大小从小到大排序。    
此时，盒子已经按长排完序，但宽和高不一定有序。此时我们可以开一个值域树状数组，维护小于宽度 $i$ 的最小高，由于值域比较大，因此需要离散化。    
对于答案，我们只需要查询当前宽度的最小已有高度是否比当前高度小即可。      
时间复杂度 $O(n\log n)$。
### code
``` cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,inf=1e18;
int n,tr[N<<1];
struct node{
	int h[5];
} a[N];
inline int lowbit(int x){
	return x&-x;
}
void add(int x,int va){
	for(;x<=n;x+=lowbit(x)) tr[x]=min(tr[x],va);
}
int query(int x){
	if(x<0) return inf;
	int ret=inf;
	for(;x;x-=lowbit(x)) ret=min(ret,tr[x]);
	return ret;
}
int ve[N],cnt=0;
bool cmp(node a,node b){
	return a.h[1]<b.h[1];
}
queue<pair<int,int>>q;
int noww;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	memset(tr,0x3f3f3f3f3f,sizeof tr);
	for(int i=1;i<=n;i++){
		cin>>a[i].h[1]>>a[i].h[2]>>a[i].h[3];
		sort(a[i].h+1,a[i].h+1+3,greater<int>());
		ve[++cnt]=a[i].h[2];
	}
	sort(a+1,a+1+n,cmp);
	sort(ve+1,ve+1+n);
	for(int i=1;i<=n;i++){
		int x=lower_bound(ve+1,ve+1+n,a[i].h[2])-ve;
		if(i!=1&&a[i].h[1]!=a[i-1].h[1]){
			while(!q.empty()){
				add(q.front().first,q.front().second);
				q.pop();
			}
		}
		q.push({x,a[i].h[3]});
		if(i!=1&&query(x-1)<a[i].h[3]){
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";
	return 0;
}


```

---

## 作者：Charlie_ljk (赞：1)

三维偏序板子，可以用 CDQ 解决。

这个 $h_i,w_i,d_i$ 是可以互换的，贪心的角度，类似与田忌赛马的思路，不过我们这次是要让齐王赢，所以大的匹配大的，小的匹配小的，故将三者排好序再赋给 $h_i,w_i,d_i$。

与 [P3810 陌上花开](https://www.luogu.com.cn/problem/P3810) 不同的是，这里的偏序要求严格小于，这不好处理，因为 CDQ 的思想只保证左半区间的第一维 $\le$ 右半区间的第一维，剩下两维改成严格小于即可，考虑这个第一维。

又发现这道题只要求判断是否存在，不需要求个数，考虑用树状数组维护前缀最小值，查询 $[1,c-1]$ 区间内最小值是否严格小于 $a$ 即可。

复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=2e5+10;
template<typename Tp> inline void read(Tp&x)
{
	x=0;register bool z=true;
	register char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
	for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(z?x:~x+1);
}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y){read(x);read(y...);}
template<typename Tp> inline void wt(Tp x)
{if(x>9)wt(x/10);putchar((x%10)+'0');}
template<typename Tp> inline void write(Tp x)
{if(x<0)putchar('-'),x=~x+1;wt(x);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x);putchar(' ');write(y...);}
int n,b[N],c[N];
struct aa {int a,b,c;}e[N],tmp[N];
bool cmp(aa a,aa b) {return a.a<b.a;}
int lowbit(int x) {return x&-x;}
void add(int x,int d) {for(;x<=n;x+=lowbit(x)) c[x]=min(c[x],d);}
void del(int x) {for(;x<=n;x+=lowbit(x)) c[x]=0x3f3f3f3f;} 
int ask(int x)
{
	int ans=0x3f3f3f3f;
	for(;x;x-=lowbit(x)) ans=min(ans,c[x]);
	return ans;
}
void cdq(int l,int r)
{
	if(l==r) return ;
	int mid=(l+r)>>1,x=l,y=mid+1,tot=l;
	cdq(l,mid),cdq(mid+1,r);
	for(;y<=r;y++)
	{
		for(;e[x].b<e[y].b&&x<=mid;x++)
		{
			add(e[x].c,e[x].a);
			tmp[tot++]=e[x];
		}
		if(ask(e[y].c-1)<e[y].a) 
		{
			puts("Yes");
			exit(0);
		}
		tmp[tot++]=e[y];
	}
	for(int i=l;i<=x-1;i++) del(e[i].c);
	for(;x<=mid;x++) tmp[tot++]=e[x];
	for(int i=l;i<=r;i++) e[i]=tmp[i];
}
signed main()
{
	read(n);
	int x[4];
	for(int i=1;i<=n;i++)
	{
		read(x[1],x[2],x[3]);
		sort(x+1,x+1+3);
		e[i]={x[1],x[2],x[3]};
		b[i]=x[3];
	}
	sort(b+1,b+1+n);
	b[0]=unique(b+1,b+1+n)-(b+1);
	for(int i=1;i<=n;i++) 
		e[i].c=lower_bound(b+1,b+1+b[0],e[i].c)-b;
	sort(e+1,e+1+n,cmp);
	memset(c,0x3f,sizeof(c));
	cdq(1,n);
	puts("No");
}
```

---

## 作者：d95a_4c1d (赞：1)

题目翻译已经很短就不给简化题面了。

把每个箱子的六种朝向都当成是不能转的箱子就能避免处理旋转，可以用三维偏序以 $\Theta(n\log^2n)$ 的复杂度通过。

但是我们在生活中遇到类似问题时肯定不会做这样麻烦的比较。习惯的做法是先比较短的边，再比较长的边。把边长排序就只用处理一种状态，从而把常数干到原来的六分之一。

然后这是绿题，用三维偏序有点大炮轰蚊子。如果把第三维长度当作元素的权值，那么元素之间影响关系就只有两维，把影响从加法变成取最小值就能转化为二维偏序。

CDQ 分治加个快读就能抢到[洛谷的最优解](https://www.luogu.com.cn/record/148926303)。（注意考虑如何处理严格小于关系）



```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

namespace FR
{
    const int SIZE = 1<< 20;
    char buf[SIZE], *p1 = buf, *p2 = buf;
    #define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2)?EOF:*p1++)
    int rd(void)
    {
        int x = 0, ch = gc();
        while (!isdigit(ch)) ch = gc();
        while (isdigit(ch)) x = 10 * x + ch - '0', ch = gc();
        return x;
    }
} using FR::rd;

struct vec
{
    int x, y, z, w;
    bool operator < (const vec &a) const
    {
        if (x != a.x) return x < a.x;
        if (y != a.y) return y > a.y;
        return z > a.z;
    }
} *tmp;

void cdq(vec *begin, vec *end)
{
    int len = end - begin;
    if (len < 2) return;
    vec *mid = begin + len / 2;
    cdq(begin, mid), cdq(mid, end);
    vec *l = begin, *r = mid, *p = tmp;
    int minn = 0x3f3f3f3f;
    while (l < mid && r < end)
    {
        if (l->y < r->y) minn = min(minn, l->z), *p++ = *l++;
        else r->w = min(r->w, minn), *p++ = *r++;
    }
    while (l < mid) *p++ = *l++;
    while (r < end) r->w = min(r->w, minn), *p++ = *r++;
    copy(tmp, p, begin);
}

int main(void)
{
    int n = rd(), l[3];
    vec *a;
    a = new vec[n], tmp = new vec[n];
    for (vec *p = a; p < a + n; ++p)
        l[0] = rd(), l[1] = rd(), l[2] = rd(),
        sort(l, l + 3), *p = {l[0], l[1], l[2], l[2]};
    sort(a, a + n), cdq(a, a + n);
    for (vec *p = a; p < a + n; ++p)
        if (p->w < p->z) return delete[] a, delete[] tmp, puts("Yes"), 0;
    return delete[] a, delete[] tmp, puts("No"), 0;
}
```

---

## 作者：BINYU (赞：1)

## 题意

给定 $n$ 个三元组 $(a,b,c)$（$a \le b \le c$），求是否有 $i$，$j$ 同时满足 $a_i<a_j$，$b_i<b_j$，$c_i<c_j$ 的 $i$，$j$。

## 思路

一眼三维偏序，~~然后就把一年半前写的 [CDQ 板子](https://www.luogu.com.cn/problem/P3810)直接粘上来了~~，然后才发现本题要求的是三维均严格小于，而 CDQ 板子并不能处理这种情况，考虑对输入的数据做一些前期的处理，能让数据中相等的情况在不影响答案的前提下全部消失。

因为本题只要求输出有无方案，所以可以先去重。

发现在 $a$ 升序作为第一关键字，$b$ 降序作为第二关键字，$c$ 降序作为第二关键字后，在 CDQ 中因为 $a$ 相等而被多算的方案只可能是前面的大于后面的（三维均相等的情况已经去掉了），所以，我们让排序后的 $a_i = i$，这样多算的就不可能成立了，而原先不相等的 $a$ 之间的大小关系不会被改变。

同理，$b$、$c$ 两维我们也可以进行类似的处理，处理完后就是一个裸的 CDQ 板子了。

---

## 作者：TORz3 (赞：1)

## 思路

前置知识：[三维偏序模板](https://www.luogu.com.cn/problem/P3810)

分析题意后，不难发现是可以交换三元组内顺序的三维偏序题。

相对于模板题，这题要求严格小于，我们一维一维来考虑。

第二维，在归并排序的过程中，注意先把小于的部分，即可能有贡献的部分处理进去。

第三维，若有数据结构来维护，查询时，查区间减一即可。但后面发现，其实只需要把合法的部分的最小值直接处理出来就行。

最后是第一维，为了满足 cdq 分治左边都对右边可能有贡献的性质。

我们考虑预处理出每一段相同的数的最左端和最右端 $pl$ 与 $pr$。

在取 $mid$ 时，我们就找这样的分段点，这样左边的第一维都严格小于右边的第一维。

这样取的时候，会有边界问题，超出查询区间的左边界或右边界，在开始时要处理下这些情况。

## 代码

```cpp
#include <bits/stdc++.h>

#define fi first
#define se second
#define mkp(x, y) make_pair((x), (y))
#define all(x) (x).begin(), (x).end()

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

struct Node {
    int a, b, c;
};

const int N = 2e5+10, INF = 2e9;

int n, nn, k;
Node p[N], np[N], tmp[N];
map<int, int> pl, pr;

bool cmp1(const Node &a, const Node &b) {
    if(a.a == b.a) {
        if(a.b == b.b) {
            return a.c < b.c;
        }
        return a.b < b.b;
    }
    return a.a < b.a;
}
bool cdq(Node np[], int l, int r) {
    if(l >= r) return false;
    int mid = pl[np[l+r >> 1].a] - 1;
    if(mid < l) {
        mid = pr[np[l+r >> 1].a];
    }
    if(mid >= r) return false;
    if(cdq(np, l, mid) || cdq(np, mid+1, r)) {
        return true;
    }
    int i = l, j = mid+1, k = l;
    int t = INF;
    while(i <= mid && j <= r) {
        if(np[i].b < np[j].b) {
            t = min(t, np[i].c);
            tmp[k++] = np[i++];
        }
        else {
            if(t < np[j].c) {
                return true;
            }
            tmp[k++] = np[j++];
        }
    }
    while(j <= r) {
        if(t < np[j].c) {
            return true;
        }
        tmp[k++] = np[j++];
    }
    while(i <= mid) {
        tmp[k++] = np[i++];
    }
    for(int i = l; i <= r; i ++) {
        np[i] = tmp[i];
    }
    return false;
}
void solve() {
    cin >> n;
    for(int i = 0; i < n; i ++) {
        auto &[a, b, c] = p[i];
        cin >> a >> b >> c;
        if(a > b) swap(a, b);
        if(b > c) swap(b, c);
        if(a > b) swap(a, b);
    }
    sort(p, p+n, cmp1);
    for(int i = n-1; i >= 0; i --) {
        pl[p[i].a] = i;
    }
    for(int i = 0; i < n; i ++) {
        pr[p[i].a] = i;
    }
    bool ok = cdq(p, 0, n-1);
    if(ok) {
        cout << "Yes\n";
    }
    else {
        cout << "No\n";
    }
}
```



---

## 作者：_zexal_ (赞：1)

考试时候没有注意到**严格**，被坑了。
#### 思路
注意到一个盒子可以**任意**旋转方向，又因为只用找到一个，所以其实这道题盒子的三个属性都无所谓了。我们将每一个的盒子的三个属性都从小到大排序，问题转换为类似三维偏序的问题。这个简单，直接分治即可。按照三维偏序的标准做法就可以了，只需要把原来的 $b_i \leq b_j$ 改为 $b_i \lt b_j$ 即可，然后在树状数组里面查询 $c$ 的时候改为 $c-1$ 不把他自己放上去即可。这时还存在一个坑点，也是赛事搞死我的地方，我们第一维 $a$ **排序时也要处理严格**！

当然，还有一种奇技淫巧的方法，我们直接还是逆序对，不过统计不满足条件的，如果最后的逆序对数量不是长度为 $n$ 的最大逆序对数量，则说明是存在满足条件的数的。

---

## 作者：Soul_Wanderer (赞：0)

# 题解

## [题目](https://www.luogu.com.cn/problem/AT_abc309_f)  

## 题目大意

给你 $n$ 个箱子，第 $i$ 个箱子有长宽高 $h_i$，$w_i$，$d_i$，可以对箱子进行翻转，也就是长宽高随意调换位置，问是否存在两个箱子 $A$ 和 $B$，$h_B > h_A$，$w_B > w_A$，$d_b > d_A$。

## 思路

我们先小小的贪心一下，如果是存在箱子 $A$ 和 $B$ 满足条件，则必定是 $B$ 的长宽高的最大值大于 $A$ 的长宽高的最大值；$B$ 的长宽高的最小值大于 $A$ 的长宽高的最小值；$B$ 的长宽高的中间值大于 $A$ 的长宽高的中间值。所以我们在存入时可以让 $h$ 存最小值，$w$ 存中间值，$d$ 存最大值。

我们再按照 $h$ 从小到大排序，后面会循环一遍，可以保证 $h$ 满足条件，这里有个小细节等会儿再说。

建一个线段树，维护区间最小值 $dmin$，$dmin$ 初始值设为无穷大。按照 $h$ 从小到大循环，对于每个箱子，将离散化后的 $w_i$ 作为下标，将 $d_i$ 当做值存入。然后查询区间 $[1,w_i-1]$ 的最小值是否**严格**小于 $d_i$，若小于，则一定存在一个箱子比当前箱子的所有值都小。

## 细节

在枚举 $h$ 时有可能不是**严格**大于，需要一些调整，具体请见代码。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n; 
struct n1{
	int h,w,d;
}a[N];
int b[N];
bool cmp(n1 a,n1 b){
	return a.h<b.h;
}
struct n2{
	int l,r;
	int dmin=1452137514749403ll;
}t[N<<2];
void pushup(int p){
	t[p].dmin=min(t[p<<1].dmin,t[p<<1|1].dmin);
}
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r) return ;
	int mid=l+r>>1;
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);
}
void chenge(int p,int L,int R,int x){
	if(L<=t[p].l&&t[p].r<=R){
		t[p].dmin=min(t[p].dmin,x);
		return ;
	}
	int mid=t[p].l+t[p].r>>1;
	if(L<=mid) chenge(p<<1,L,R,x);
	if(mid<R) chenge(p<<1|1,L,R,x);
	pushup(p);
}
int query(int p,int L,int R){
	if(L<=t[p].l&&t[p].r<=R){
		return t[p].dmin;
	}
	int mid=t[p].l+t[p].r>>1;
	int ret=1452137516749403ll;
	if(L<=mid) ret=min(query(p<<1,L,R),ret);
	if(mid<R) ret=min(query(p<<1|1,L,R),ret);
	return ret;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		int aa,bb,cc;cin>>aa>>bb>>cc;
		int sum=aa+bb+cc;
		int maxx=max(aa,max(bb,cc));
		int minn=min(aa,min(bb,cc));
		a[i]={minn,sum-minn-maxx,maxx};
		b[i]=sum-minn-maxx;
	}
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+n+1);
	int cnt=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i].w=lower_bound(b+1,b+cnt+1,a[i].w)-b;
	}
	int id=1;
	build(1,1,n);
	for(int i=1;i<=n;i++){
		if(a[i-1].h<a[i].h){
			while(id<i){
				chenge(1,a[id].w,a[id].w,a[id].d);
				id++;
			}
		}
		if(query(1,1,a[i].w-1)<a[i].d){
			printf("Yes\n");
			return 0;
		}
	}
	printf("No\n");
	return 0;
}
```

---

## 作者：Ups_and_downs (赞：0)

# [ABC309F] Box in Box

题目中给出了 $N$ 个箱子的三维数据 $h$，$w$，$d$，询问是否存在两个箱子 $A$，$B$，可以旋转箱子，使得 $B$ 的三维数据均大于 $A$。

那么首先考虑旋转的情况，如 $B$ 的三维数据均比 $A$ 的要大，那么选择贪心算法，给 $A$ 的最小三维数据匹配 $B$ 最小的，给 $A$ 的最大三维数据匹配 $B$ 最大的，即可完成指定任务。

那么首先应该对三维数据进行一个排序，从小到大记作 $h$，$w$，$d$。

继而对所有箱子按 $h$ 进行排序，这样做的好处在于之后遍历所有箱子，可以不用再考虑 $h$。

然后对于每一个 $(w,d)$，若存在对应的 $A$，$B$ 满足要求，只需要保证对于前面所有前面的 $w_i$ 小于 $w$ 的箱子存在一个 $d_i$ 小于 $d$ 即可。

那么可以转化为 $w_i$ 的值在区间 $[0,w-1]$ 之间的所有箱子的 $d_i$ 的最小值小于 $d$ 即可，运用线段树就可以解决这个问题。

（注意数据范围：由于 $w_i$ 和 $d_i$ 的范围都比较大，应该进行离散化的预处理）

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

给出 $n$ 个长方体的长宽高，问是否存在两个不同的长方体，能够通过旋转它们使得其中一个长方体的长宽高分别严格大于另外一个长方体的长宽高。

## 题目分析

显然的一个贪心就是我们把每个长方体的三个值从大到小设为 $A_i,B_i,C_i$。问题变成了三维偏序，只不过要严格大于，需要特殊处理。但赛时写 cdq 居然 TLE 了。不过同学讲了一个很简单的做法。

注意到本题只需判断存在性，我们就可以将长方体先按 $A_i$ 排序，然后离散化 $B_i$，从左往右遍历，$A_i$ 相同的处理完后，将 $C_i$ 的值插入树状数组内，位置就是离散化的 $B_i$，然后只需要查一下前缀 $B_i-1$ 的最小值是否小于 $C_i$ 就行了，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mid (l+r>>1)
#define L x<<1
#define R x<<1|1
#define lc L,l,mid
#define rc R,mid+1,r
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define e(x) for(int i=h[x];i;i=nxt[i])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=1e5+5,inf=2147000000;
const ll mod=1e9+7;
using namespace std;
struct node{
	int a,b,c;
}a[N];
int m,t[N];
inline bool cmp(node a,node b){
	return a.a<b.a;
}
inline int lowbit(int x){
	return x&-x;
}
inline void add(int x,int k){
	while(x<=m)t[x]=min(t[x],k),x+=lowbit(x); 
}
inline int query(int x){
	int ans=inf;
	while(x)ans=min(ans,t[x]),x-=lowbit(x);
	return ans;
}
int lsh[N],b[N],l;
int main(){
	int n=read();
	rep(i,1,n){
		ll x=read(),y=read(),z=read();
		a[i].a=max(max(x,y),z),a[i].c=min(min(x,y),z),lsh[i]=a[i].b=x+y+z-a[i].a-a[i].c;
	}
	sort(a+1,a+n+1,cmp),sort(lsh+1,lsh+n+1);
	rep(i,2,n+1)if(lsh[i]^lsh[i-1])b[++m]=lsh[i-1];
	memset(t,0x3f,sizeof(t));
	l=1;
	rep(i,1,n){
		if(a[i].a^a[i-1].a){
			rep(j,l,i-1)add(a[j].b,a[j].c);
			l=i;
		}
		a[i].b=lower_bound(b+1,b+m+1,a[i].b)-b;
		if(query(a[i].b-1)<a[i].c){
			cout <<"Yes";
			return 0;
		}
	}
	cout <<"No";
	return 0;
}
```


---

## 作者：Kidding_Ma (赞：0)

交换 $h_i,w_i,d_i$ 的顺序使得 $h_i\le w_i\le d_i$，记 $a_i=(h_i,w_i,d_i)$，对 $a_i$ 排序。

那么我们升序遍历 $a$，对于 $a_j$ 查询满足 $h_i<h_j(i<j)$ 的 $a_i$ 中所有满足 $w_i<w_j$ 的 $w_i$ 对应的最小 $d$ 是否小于 $d_j$，并更新当前 $w_j$ 对于的最小 $d$。

这里可以使用支持单点更新，区间求 $\min$ 的线段树维护，要离散化 $w_i$，$O(n\log n)$。

Code


```cpp
#include "bits/stdc++.h"

using namespace std;
using i64 = long long;

template<class Info,
        class Merge = plus<Info>>
struct SegmentTree {
    const int n;
    const Merge merge;
    vector<Info> info;
    int N;
    SegmentTree(int n) : n(n), merge(Merge()) {
        N = 1;
        while (N < n) {
            N <<= 1;
        }
        info.assign(2 * N, Info());
    }
    SegmentTree(vector<Info> &init) : SegmentTree(init.size()) {
        for (int i = 0; i < n; i++) {
            info[N + i] = init[i];
        }
        for (int i = N - 1; i; i--) {
            pull(i);
        }
    }
    void pull(int p) {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void modify(int p, const Info &v) {
        p += N;
        info[p] = v;
        for (int i = 1; (1 << i) <= N; i++) {
            pull(p >> i);
        }
    }
    Info get(int i) {
        return info[N + i];
    }
    Info rangeQuery(int l, int r) {
        Info res = Info();
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = merge(res, info[l++]);
            if (r & 1) res = merge(info[--r], res);
        }
        return res;
    }
};

constexpr int inf = 1E9;

struct Min {
    int x;
    Min(const int &x = inf) : x(x) {}
};
 
Min operator+(const Min &a, const Min &b) {
    return min(a.x, b.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    vector<array<int, 3>> a(n);
    for (int i = 0; i < n; i++) {
        auto &[h, w, d] = a[i];
		cin >> h >> w >> d;
        sort(a[i].begin(), a[i].end());
    }
    sort(a.begin(), a.end());

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = a[i][1];
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    const int N = v.size();
    SegmentTree<Min> seg(N); 
    for (int l = 0, r = 0; l < n; l = r) {
        while (r < n && a[r][0] == a[l][0]) {
            r += 1;
        }
        for (int i = l; i < r; i++) {
            auto &[h, w, d] = a[i];
            w = lower_bound(v.begin(), v.end(), w) - v.begin();
            if (seg.rangeQuery(0, w).x < d) {
                cout << "Yes\n";
                return 0;
            }
        }
        for (int i = l; i < r; i++) {
            auto &[h, w, d] = a[i];
            seg.modify(w, min(seg.get(w).x, d));
        }
    }
    cout << "No\n";

    return 0;
}
```

---

## 作者：caibet (赞：0)

[:]:SolutionOfAT_abc309_f

**题意**：

给定 $n$ 个盒子，长宽高分别为 $w_i,d_i,h_i$。问是否存在两个盒子经过旋转可以使得 $w_i<w_j,d_i<d_j$ 且 $h_i<h_j$（即存在一个盒子可以放在另一个盒子中且留下缝隙）。

$2\le n\le 2\times10^5,1\le w_i,d_i,h_i\le 10^9$。

**做法**：

（本题解讲述的是三维偏序一般做法以外的做法，此做法只能求出是否存在符合题意的选择方法，若需要学习三维偏序的一般做法及求出选择方法数量的做法，请移步其他题解。）

一个盒子的旋转可以使其长宽高任意交换。因此我们只需将三边大小排序（升降序皆可），依次比较每条边的大小，就可以确定两个盒子是否满足题意。此处证明暂不详细展开。

然而如果逐个比较，复杂度将为 $\mathcal O(n^2)$，如何降低复杂度呢？

由于数列毫无规律，令排序后盒子的三边为 $a_i,b_i$ 和 $c_i$，考虑将盒子以 $a_i$ 为关键字升序排列。此时对于一个盒子 $i$，能放在其中的盒子的编号只可能比 $i$ 小。此时问题转化为求是否存在 $j<i$ 使 $a_j\neq a_i,b_j<b_i$ 且 $c_j<c_i$。

先考虑 $a_i$ 互不相等的情况：求是否存在 $j<i$ 使 $b_j<b_i$ 且 $c_j<c_i$。此处不能使用二维树状数组求解，否则空间不够。

我们可以发现，对于一个固定的 $b_i$，只需记录最小的 $c_i$ 即可，因为同一个 $b_i$ 如果最小的 $c_i$ 都不能放入后面的某一盒子中，那么所有第二边为 $b_i$ 的盒子都不能。对于一个 $b_i$，如果前面的盒子第二边为 $1\sim b_i-1$ 时，最小的第三边 $c_{\min}<c_i$，那么 $c_{\min}$ 对应的盒子就可以放入第 $i$ 个盒子中，成为答案。因为前面的盒子的更新需要进行**单点最小值覆盖**，查询时需要求 $[1,b_i-1]$ 的**区间最小值**，所以可以用树状数组（最小值变体）维护。

举一个例子：

```
3
1 1 4
3 3 2
4 4 4
```

- 上述一系列排序后，三个盒子的顺序为 $[(1,1,4),(2,3,3),(4,4,4)]$。
- 对于第一个盒子，查询第二边为 $1\sim b_1-1(1\sim0)$ 时 $c_i$ 的最小值。答案为 $+\infty$，不能塞入第一个盒子中。随后设置第二边为 $b_1=1$ 时 $c_i$ 的最小值为 $c_1=4$。
- 对于第二个盒子，查询第二边为 $1\sim b_2-1(1\sim2)$ 时 $c_i$ 的最小值。答案为 $4$。$4>c_2=3$，不能塞入第二个盒子中。随后设置第二边为 $b_2=3$ 时 $c_i$ 的最小值为 $c_2=3$。
- 对于第三个盒子，查询第二边为 $1\sim b_3-1(1\sim3)$ 时 $c_i$ 的最小值。答案为 $3$。查询到的盒子 $c_i$ 比当前的小，$b_i$ 也在 $1\sim b_3-1$ 的范围内，$a_i$ 经过排序也在 $a_3$ 之前，因此可以塞进第三个盒子中，输出 `Yes`。

算法复杂度为 $\mathcal O(n\log n)$。

------------


如果存在相同的 $a_i$ 呢？经过排序，这些相同的数字一定相邻，为了不让相同的 $a_i$ 互相影响，我们可以在接下来存在相同的 $a_i$ 时，将本次操作先储存起来，不执行到树状数组上；等到下一个 $a_i$ 不相等时，再将储存起来的操作一并执行，为下一次查询做好准备。操作的储存最多 $n$ 次，释放一次操作复杂度为 $\mathcal O(\log n)$，总复杂度仍为 $\mathcal O(n\log n)$，非常高效。

以下是实现的代码。注意由于题目的值域很大，使用 $w_i,d_i,h_i$ 前需要离散化。

```cpp
namespace{
	const int N=2e5+3;
	int n;
	struct node{
		int a,b,c;
	} a[N];// 存储盒子
	vector<int> v;// 用于离散化
	struct update{
		int x,y;
	};
	vector<update> save;// 存储相同 ai 时的修改
	
	// 最小值树状数组
	int c[N*3];
	void write(int x,int k){
		for(;x<=n*3;x+=x&-x) c[x]=min(c[x],k);
	}
	int query(int x,int res=inf){
		for(;x;x-=x&-x) res=min(res,c[x]);
		return res;
	}
	void work(){
		n=read();
		F(i,1,<=n){
			a[i].a=read();a[i].b=read();
			a[i].c=read();
			// 小范围的冒泡排序（此处为升序）
			if(a[i].b>a[i].c) swap(a[i].b,a[i].c);
			if(a[i].a>a[i].b) swap(a[i].a,a[i].b);
			if(a[i].b>a[i].c) swap(a[i].b,a[i].c);
			
			v.pb(a[i].a);
			v.pb(a[i].b);
			v.pb(a[i].c);
		}
		// 下面为离散化操作
		sort(v.begin(),v.end());
		int k=unique(v.begin(),v.end())-v.begin();
		F(i,1,<=n){
			a[i].a=lower_bound(v.begin(),v.begin()+k,a[i].a)-v.begin()+1;
			a[i].b=lower_bound(v.begin(),v.begin()+k,a[i].b)-v.begin()+1;
			a[i].c=lower_bound(v.begin(),v.begin()+k,a[i].c)-v.begin()+1;
		}
		
		// 按第一边排序
		sort(a+1,a+n+1,[](const node&x,const node&y){
			return x.a<y.a;
		});
		
		memset(c,0x3f,sizeof c);
		
		F(i,1,<=n){
			if(a[i+1].a!=a[i].a){
				// 查询 ai,bi 比自己小的盒子中 ci 的最小值
				if(query(a[i].b-1)<a[i].c){
					puts("Yes");
					return;
				}
				// 释放储存的操作
				F(i,0,<save.size()) write(save[i].x,save[i].y);
				save.clear();
				// 记录当前盒子的信息
				write(a[i].b,a[i].c);
			}else{
				if(query(a[i].b-1)<a[i].c){
					puts("Yes");
					return;
				}
				// 储存操作
				save.pb({a[i].b,a[i].c});
			}
		}
		puts("No");
	}
}
```

---

