# One-Dimensional Battle Ships

## 题目描述

Alice和Bob喜欢在$1\times n$的表格中玩战舰游戏。游戏开始时，Alice有$k$艘战舰，每艘战舰长度为$a$，她需要把这些战舰不重叠且不相邻地放在格子中（不允许有两艘战舰的格子存在公共边）。但她并不会告诉Bob她放的位置。

接下来，Bob会用$m$颗炮弹尝试打中Alice的战舰，每颗炮弹会选择一个格子打击。但由于Alice喜欢作弊，所以她不会告诉Bob什么时候击中了战舰。请你帮助Bob判断，在第几次发射炮弹后，Alice一定会有一艘战舰被击中。

## 说明/提示

$1 \leq n,k,a \leq 2 \cdot 10^5$

$m,x_i \leq n$

## 样例 #1

### 输入

```
11 3 3
5
4 8 6 1 11
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 1 3
2
1 5
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 1 3
1
3
```

### 输出

```
1
```

# 题解

## 作者：Lynkcat (赞：8)

看到题解没人写 $multiset$ 于是来写一发题解。

首先考虑每个炮弹会把怎样一个区间拆开，假设现在炮弹射向 $x$ ，显然我们维护所有的无法放置的点，在这个集合中找 $x$ 的前驱和后继记为 $l,r$ 。那么我们相当于把原来一个 $r-l-1$ 长度的区间拆成了长度分别为 $x-l-1,r-x-1$ 的两个区间。我们再考虑每个区间对答案的贡献，一个长度为 $y$ 的区间，能放下 $(y+1)/a$ 个小区间（这应该很显然）。那么我们直接考虑对于每次操作时减去大区间的贡献再加上两个小区间的贡献即可。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
int n,k,a,m,x,p,p1,ans;
multiset<int>S;
signed main()
{
	n=read(),k=read(),a=read();
	m=read();
	S.insert(0);
	S.insert(n+1);
	ans+=n/(a+1)+(n%(a+1)==a);
	for (int i=1;i<=m;i++)
	{
		x=read();
		p=*(S.lower_bound(x));
		p1=*(--S.lower_bound(x));
		ans-=(p-p1)/(a+1);
		ans+=(p-x)/(a+1);
		ans+=(x-p1)/(a+1);
		if (ans<k)
		{
			writeln(i);
			return 0;
		}
		S.insert(x);
	}
	writeln(-1);
}
/*

*/


---

## 作者：Poncirus (赞：6)

### 前言

**upd on 220809：代码粘错了，我自裁……**

这是题解区中第一个理论最劣 $\mathcal O(n)$ 的解法。

### 思路

因为「某一时刻是否一定被击中过」具有单调性，应用一种经典的思想：先提前发射所有炮弹，倒序枚举炮弹，不断「撤销」当前最后一发炮弹的发射，如果在「撤销」这发炮弹后，存在任意一种放下 $k$ 艘完整的战舰的方案，说明在发射这一发炮弹之后绝对能够击中。

如果发射所有炮弹后，依然存在一种放下 $k$ 艘完整的战舰的方案，则无解。

具体实现可以使用并查集维护连通块大小，每「撤销」一发炮弹的发射相当于合并三个连通块：炮弹的落点、落点的前一个元素（若不存在或已被炮弹摧毁则忽略）、落点的后一个元素（若不存在或已被炮弹摧毁则忽略）。

设某连通块大小为 $x$，可容纳战舰数为 $res$，显然有 $res = \lfloor (x + 1) \div (p + 1) \rfloor$。

记统计当前可容纳战舰的数量为 $ans$，在并查集合并时，$ans$ 分别减去两个待合并连通块的可容纳战舰的数量，再加上新连通块可容纳战舰的数量。最靠后的 $ans\ge k$ 的时刻即为所求。

### 代码

同时使用路径压缩和按秩合并，时空复杂度均为 $\mathcal O(n)$。

总用时完爆非完隐榜二。

```cpp
namespace XSC062 {
using namespace fastIO;const int maxn = 2e5 + 15;
bool vis[maxn];
int n, k, p, m, x, ans;
int a[maxn], f[maxn], siz[maxn];
inline void swap(int &x, int &y){
    x ^= y ^= x ^= y;
    return;
}
inline int calc(int x) {
    return (x + 1) / (p + 1);
}
inline void Init(int n) {
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        siz[i] = 1;
    }
    return;
}
int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}
inline void merge(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx == fy)
        return;
    ans -= calc(siz[fx]);
    ans -= calc(siz[fy]);
    if (siz[fy] < siz[fx])
        swap(fx, fy);
	siz[fy] += siz[fx];
    ans += calc(siz[fy]);
    f[fx] = fy;
    return;
}
int main() {
	read(n);
	read(k);
	read(p);
	read(m);
	Init(n + 5);
	ans = (n - m) * (2 / (p + 1));
	for (int i = 1; i <= m; ++i) {
		read(a[i]);
		vis[a[i]] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		if (vis[i] || vis[i - 1])
			continue;
		merge(i, i - 1);
	} 
	if (ans >= k) {
		puts("-1");
		return 0;
	}
	for (int i = m; i; --i) {
		vis[a[i]] = 0;
		ans += 2 / (p + 1);
		if (a[i] - 1 && !vis[a[i] - 1])
			merge(a[i], a[i] - 1);
		if (a[i] + 1 <= n && !vis[a[i] + 1])
			merge(a[i], a[i] + 1);
		if (ans >= k) {
			printf("%d", i);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
} // namespace XSC062
```

---

## 作者：zac2010 (赞：3)

思路 $1$：一眼 `set` 维护区间的模板。每次打击一个位置就把区间分裂，重新统计贡献—— $[l,r]$ 这个闭区间最多能放的战舰数为 $\lfloor\frac{(r-l+1)+1}{a+1}\rfloor$（$a+1$ 是因为战舰之间有空格）。

思路 $2$：二分答案。其中判断答案是否合法就只需要拿出所有未被打击格子组成的极大闭区间，按照上述方式统计是否放得下 $k$ 艘战舰即可。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e5 + 10;
int n, k, a, m, cnt, now, x[N], b[N];
int check(int mid){
	fill(b + 1, b + n + 1, 0), cnt = now = 0;
	FL(i, 1, mid) b[x[i]] = 1;
	FL(i, 1, n){
		if(b[i]) cnt += (now + 1) / (a + 1), now = 0;
		else now++;
	}
	return (cnt += (now + 1) / (a + 1)) < k;
}
int main(){
	scanf("%d%d%d%d", &n, &k, &a, &m);
	FL(i, 1, m) scanf("%d", &x[i]);
	int l = 1, r = m, ans = -1;
	while(l <= r){
		int mid = l + r >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：zplqwq (赞：1)

这道题可以考虑用 `multiset` 存储。

`multiset` 里面维护的是所有无法放置的点。

因此每次操作的时候，我们考虑炮弹射中了点 $t$ 。 则这个点在这个 `multiset` 里面的前驱和后继我们记为 $l$ 和 $r$ 。那么原来那个长度为 `r-l-1` 的区间自然就可以拆成长度为 `t-l-1` 和 `r-x-1` 的两个区间。自然这个区间长度为 $x$ 对于答案的贡献是 $\frac{y+1}{a}$ 。则最终的贡献为原来的贡献减去大区间的贡献加上被分出来的两个区间的贡献。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
int n,k;
int a,m;
int x;
int tmp,tmp2;
int flag=0;
int ans=0;
multiset<int> s;
int main()
{
	n=read();
	k=read();
	a=read();
	m=read();
	s.insert(0);
	s.insert(n+1);
	ans+=(n/(a+1)+(n%(a+1)==a));
	for(int i=1;i<=m;i++)
	{
		x=read();
		tmp=*(s.lower_bound(x));
		tmp2=*(--s.lower_bound(x));
		ans-=(tmp-tmp2)/(a+1);
		ans+=(tmp-x)/(a+1);
		ans+=(x-tmp2)/(a+1);
		if(ans<k)
		{
			flag=1;
			printf("%d",i);;
			break;
		}
		s.insert(x);
	}
	if(flag==0) puts("-1");
	return 0;
}
```

---

## 作者：ModestCoder_ (赞：1)

[原题传送门](http://codeforces.com/problemset/problem/567/D)

直接模拟的话比较麻烦，可能需要用上一些数据结构之类的

但是这道题目不需要数据结构，直接二分即可

先把坐标排序，二分答案，$check$里面计算可以放多少船

$id$小于$mid$的断点是合理的

对于一段区间$[l,r]$，可以放$[\frac{r-l+1}{a+1}]$条船

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 200010
using namespace std;
struct data{
	int x, id;
}x[maxn];
int n, k, a, m;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

bool cmp(data x, data y){ return x.x < y.x; }

bool check(int mid){
	int cnt = 0, l = 0;
	for (int i = 1; i <= m; ++i)
		if (x[i].id <= mid) cnt += (x[i].x - l) / (a + 1), l = x[i].x;
	cnt += (n - l + 1) / (a + 1);
	return cnt < k;
}

int main(){
	n = read(), k = read(), a = read(), m = read();
	for (int i = 1; i <= m; ++i) x[i] = (data){read(), i};
	sort(x + 1, x + 1 + m, cmp);	
	int l = 1, r = m, ans = -1;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (check(mid)) ans = mid, r = mid - 1; else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：Error_Eric (赞：0)

### 前言

哇蓝题

### 正文

题目翻译成人话就是：

Bob 有 $m$ 次操作，每一次操作有一个位置 $x$。这个操作会将 $x$ 原来的区间 $[L,R]$($L< x< R$)分割成 $[L,x-1],[x+1,R]$，要求求出在第几次操作完成后不存在 $k$ 个只互相不重叠，没有共顶点的线段，满足所有线段只存在于一个区间内，长度为 $a$。

思路：

显然对于一个已经分好的区间 $[l,r]$,有 $l-r-1$ 的长度。其中我们可以认为第一个战舰的长度是 $a$,后面的长度都是 $a+1$ （这时它们首尾相连），显然最多有 $\lfloor\dfrac{(l-r-1)-a}{a+1}\rfloor+1=\lfloor\dfrac{l-r}{a+1}\rfloor$ 个战舰。注意，第一个区间是 $[0,x_1]$ 最后一个区间是 $[x_m,n+1]$

如果 $p$ 个炸弹没法成功，那么 $p-1$ 个也不可以，符合函数单调性，可以二分。

数据范围提示着我们就是二分（枚举炸弹数目）。

### code

```cpp
#include<iostream> 
#include<algorithm>
#include<stdio.h>
using namespace std;
const int maxn=200000+50;
struct op{int xi,id;}u[maxn];//Bob 的操作
int n,k,a,m;                 //如题目所说
bool cmp(op x,op y){return x.xi<y.xi;}//把操作按位置排序
bool check(int fx){//二分的check函数
	int cnt=0,p=0;//cnt战舰数量p上一个炸弹的位置
	for(int i=1;i<=m;i++)//枚举炸弹
		if(u[i].id<=fx)//如果这个炸弹已经爆炸
        cnt+=(u[i].xi-p)/(a+1),p=u[i].xi;
        //统计这个炸弹和上一个炸弹之间最多有多少战舰
        //现在的炸弹成为了下一个炸弹的“上一个炸弹”
	return cnt+(n-p+1)/(a+1)<k;//当然最后的那个区间不要忘记。
}
int main(){
	scanf("%d%d%d%d",&n,&k,&a,&m);//输入
	for(int i=1;i<=m;++i)scanf("%d",&u[i].xi),u[i].id=i;//输入
	sort(u+1,u+1+m,cmp);//把炸弹按爆炸的位置排序
	int l=0,r=m+1;//准备二分
	while(l<r){//左闭右开
		int mid=l+((r-l)/2);//防爆int
		if(check(mid))r=mid;
		else l=mid+1;
	}
	printf("%d\n",(l==m+1)?(-1):(l));//如果m次都解决不了,那么输出-1，不然输出l;
	return 0;
}
```

二分的时间复杂度 $O(\log m)$ 。

``check()`` 的时间复杂度 $O(m)$ 。

总时间复杂度： $O(m \log m)$ 。

---

## 作者：叶ID (赞：0)

题目：[CF567D One-Dimensional Battle Ships](https://www.luogu.org/problem/CF567D)

****

### 题意翻译的修正

> 接下来，Bob会用$m$颗炮弹尝试打中Alice的战舰，每颗炮弹会选择一个格子打击。但由于Alice喜欢作弊，所以她不会告诉Bob什么时候击中了战舰。请你帮助Bob判断，在第几次发射炮弹后，Alice一定会有一艘战舰被击中。

应该理解成

接下来，Bob会用$m$颗炮弹尝试打中Alice的战舰，每颗炮弹会选择一个格子打击。但由于Alice喜欢作弊，所以她不会告诉Bob什么时候击中了战舰。请你帮助Bob判断，在第几次发射炮弹后，他就能判定Alice一定在作弊（并拆穿她）。

并且，此题中Alice实际上是一直在用“未击中”回应Bob发射炮弹的操作。

****

### 解题思路

一开始，我们可以将地图看做一个连续区间。我们认为这个区间被染成了颜色$1$。~~利用小学数学功底，~~ 很容易发现，对于一个长度为$sz$的区间，最多可以放置$floor(\frac{sz+1}{len+1})$个战舰（题目要求战舰不能互相连接，也不能重叠）。

显然，Bob每扔出一颗炮弹，都会将炮弹打中的区间分成两块（此处我们允许其中一块或者两块长度是$0$）。

按照朴素的思路，我们可以在每次打击之后对于每个区间计算出能放置的战舰数量，最后相加。如果发现，这些区间已经不能容纳题目中的$k$艘战舰，那么显然Alice就作弊了。（显然也没有别的情况了）

### 实现细节

我们用一个`树状数组2`（区间修改，单点查询）维护每个点所属的区间（后称颜色），并维护每种颜色的左右端点。

一开始，我们将树状数组的值全部赋值为$1$，并将$1$的范围设定为$[1,n]$
，代表整个连续的区间。

随后，如果一颗子弹落在$pos$位置，范围为$[l,r]$的区间上，那么区间被拆成两个，分别是$[l,pos-1]$和$[pos+1,r]$（此处无需考虑边界，因为如果某区间的大小变成了$0$，这个区间在以后就没有存在感了，因为她不会再被打中）。我们将区间$[l,pos-1]$保持原有的颜色，然后将区间$[pos,pos]$颜色变成$-1$，最后将$[pos+1,r]$变成一个新的颜色（由于这个区间原本就是清一色的，再染成一种颜色可以通过树状数组2完成）。

至于统计，将变量$cnt$初始化为原来整个区间的容纳量。每次区间拆分时，先减去原有区间的容量，在加上得到的两个区间的容量，就可以了。

****

### 代码与评测记录


```cpp
// status: [Accepted]
// oj:     [luogu]

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 300001;
int n,m,len;
int ct = 0;
int lcolor[MAXN];
int rcolor[MAXN];
int cnt = 0;

//树状数组（区间修改，单点查询）
template<class T,int len>
struct CycOkIai{
    //数据表（无必要时请勿从外部访问）
    int data[len+1];

    //清空树状数组（初始化时无需调用）
    void clear() {
        for(int i=1;i<=len;i++) {
            data[i]=0;
        }
    }

    //返回正整数删除所有非最后一个1的结果
    int lowbit(int x) {return x&(-x);}

    //更新数据，将idx-n加上一个数
    void delta(int idx,int val=0) {
        while(idx<=n) {
            data[idx]+=val;
            idx+=lowbit(idx);
        }
    }

    //更新数据，将l-r加上一个数
    void update(int l,int r,int val=0) {
        delta(l,val);
        delta(r+1,-val);
    }

    //查询位于idx的数据
    int at(int idx) {
        int ret=0;
        while(idx) {
            ret+=data[idx];
            idx-=lowbit(idx);
        }
        return ret;
    }
};

CycOkIai<int,MAXN> col;

inline int capacity(int id) {
    int sz = rcolor[id] - lcolor[id] + 1;
    return (sz+1)/(len+1);
}

int main() {
    ios::sync_with_stdio(false);
    cin>>n>>m>>len;
    ++ct;
    col.update(1,n,ct);
    lcolor[ct] = 1;
    rcolor[ct] = n;

    cnt = capacity(1);

    if(cnt < m) {cout<<"0"<<endl;return 0;}

    int T;
    cin>>T;
    for(int t=1;t<=T;t++) {
        int pos;
        cin>>pos;
        if(col.at(pos)==-1) continue;
        int cc = col.at(pos);
        cnt -= capacity(cc);
        ++ct;
        rcolor[ct] = rcolor[cc];
        rcolor[cc] = pos - 1;
        lcolor[ct] = pos + 1;
        col.update(lcolor[ct],rcolor[ct],ct-cc);
        col.update(pos,pos,-1-cc);
        cnt += capacity(cc) + capacity(ct);
        if(cnt < m) {cout<<t<<endl;return 0;}
    }

    cout<<-1<<endl;
}
```

评测记录：[rid24052403 / 139ms / 2.75s / 3.45MB](https://www.luogu.org/record/24052403)


---

