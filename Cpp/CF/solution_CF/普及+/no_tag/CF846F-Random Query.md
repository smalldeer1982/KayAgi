# Random Query

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers. You pick two integer numbers $ l $ and $ r $ from $ 1 $ to $ n $ , inclusive (numbers are picked randomly, equiprobably and independently). If $ l&gt;r $ , then you swap values of $ l $ and $ r $ . You have to calculate the expected value of the number of unique elements in segment of the array from index $ l $ to index $ r $ , inclusive ( $ 1 $ -indexed).

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
1.500000
```

## 样例 #2

### 输入

```
2
2 2
```

### 输出

```
1.000000
```

# 题解

## 作者：Stream月 (赞：7)

刚开始学期望，什么都不会

还是用到期望的重要性质：**期望的和 $=$ 和的期望**

如何转化问题呢？

数列$B$的期望长度 实际上 就是每个数被保留下来的期望值的和

问题转化为计算每个数被保留下来的期望

进一步考虑这个数在那些区间中会被保留，这里我们不妨只保留一个区间中第一次出现的数， 那么可以处理出$pre[i]$ 表示数 $i$出现的前一个位置，那么对于一个数$a[i]$, 那么会保留$a[i]$ 的左端点位于$[pre[a[i]] + 1, i] $ ， 右端点位于$[i, n]$, 保留$a[i]$区间的个数为
$$
(i - pre[a[i]])*(n - i + 1)
$$
将该值除$n^2$,就是$a[i]$被保留的期望，最后求个和就好了

注意一点，题中的$l, r$是可以任意取的，
$l \neq r$ 时答案应计算两次， $l = r$时则是一次，细节按照自己习惯的方式处理就好了。

下面是喜闻乐见的代码实现(~~写快读写惯了qwq~~)：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;

using namespace std;
#define $(i,a,n) for(int i = a; i <= n; ++i)

inline ll read() {
	   ll ans = 0;
	   char last = ' ',ch = getchar();
	   while(ch < '0' || ch > '9') last = ch, ch = getchar();
	   while(ch >= '0' && ch <= '9') ans = (ans << 3) + (ans << 1) + ch - '0', ch = getchar();
	   if(last == '-') ans = -ans;
	   return ans;
}

const int INF = 0x3f3f3f3f;
const int N = 1e6 + 5;

ll a[N], n, pre[N];
ll ans = 0;
int main(){
	//freopen("testdata.in", "r", stdin);
	//freopen("ans.out", "w", stdout);
	n = read();
	$(i, 1, n) a[i] = read();
	for(int i = 1; i <= n; ++i) {
		ans += (i - pre[a[i]]) * (n - i + 1) * 2 ;
		pre[a[i]] = i;
	}
	ans -= n;
	printf("%.6lf", (double)ans/(double)(n * n));
	return 0;
}

```

最后祝大家CSP 2019 rp++



---

## 作者：wwlw (赞：5)

[Link](https://www.luogu.com.cn/problem/CF846F)
---------------

### Description
给定长为 $n$ 的数列 $a_i$，随机地选取两个数 $l,r\in [1,n]$，如果 $l>r$，则交换 $l,r$。求区间 $[l,r]$ 中不同数字个数的期望。

### Solution

我们只需要求出所有区间内的不同数字个数和再除以区间个数就可以了。实际上对特定区间统计不同数的个数并不太好处理，不管怎么优化复杂度都不优于 $O(n^2)$，因为逃不掉枚举区间。那如果不枚举区间呢？考虑到不同数值的数相互间是独立的，所以想到可以枚举数值，转而快速统计合法的区间个数。一个特定的数 $x$ 会对一个区间做出贡献，当且仅当 $x$ 在该区间出现过，而且不管出现多少次都只会做出 $1$ 的贡献。那么问题就转化成求有多少区间包含数 $x$。考虑补集转换，求总区间个数减去不包含 $x$ 的区间个数。如果新开一个数组 $b$，$b_i$ 为 $1$ 当且仅当 $a_i=x$ 成立。那么不包含 $x$ 的区间就是一个由 $0$ 组成的段，个数就是该 $0$ 段长度的平方，最后再把所有 $0$ 段的贡献求和。这一步显然可以用线段树来维护，类似于最大子段和的思路，一个节点维护线段树上区间前缀 $0$ 和后缀 $0$ 的个数，以及该区间包含的所求区间个数。复杂度 $O(|V|\log n)$，$|V|$ 是值域。

```cpp
#include<stdio.h>
#include<vector>
using namespace std;
#define N 1000007
#define ll long long
#define lid id<<1
#define rid id<<1|1

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='0') flag=0; c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

struct Node{
    ll ls,rs,sum;
}t[N<<2];

int n;
vector<int> V[N];
bool a[N];

inline void update(int id,int lf,int rf){
    int mid=(lf+rf)>>1;
    if(t[lid].ls==mid-lf+1) t[id].ls=t[lid].ls+t[rid].ls;
    else t[id].ls=t[lid].ls;
    if(t[rid].rs==rf-mid) t[id].rs=t[rid].rs+t[lid].rs;
    else t[id].rs=t[rid].rs;
    ll x=t[lid].rs,y=t[rid].ls,z=t[lid].rs+t[rid].ls;
    t[id].sum=t[lid].sum-x*x+t[rid].sum-y*y+z*z;
}

int pos;
void modify(int id,int lf,int rf){
    if(lf==rf){
        a[pos]^=1;
        if(!a[pos]) t[id].ls=t[id].rs=t[id].sum=1;
        else t[id].ls=t[id].rs=t[id].sum=0;
    }else{
        int mid=(lf+rf)>>1;
        if(pos<=mid) modify(lid,lf,mid);
        else modify(rid,mid+1,rf);
        update(id,lf,rf);
    }
}

void build(int id,int lf,int rf){
    if(lf==rf)
        t[id].ls=t[id].rs=t[id].sum=1;
    else{
        int mid=(lf+rf)>>1;
        build(lid,lf,mid);
        build(rid,mid+1,rf);
        update(id,lf,rf);
    }
}

int main(){
    n=read();
    for(int i=1;i<=n;i++)
        V[read()].push_back(i);
    ll ans=0;
    build(1,1,n);
    for(int i=1;i<N;i++){
        if(!V[i].size()) continue;
        for(int j=0;j<V[i].size();j++)
            pos=V[i][j],modify(1,1,n);
        ans+=1ll*n*n-t[1].sum;
        for(int j=0;j<V[i].size();j++)
            pos=V[i][j],modify(1,1,n);
    }
    printf("%.6lf",1.0*ans/(1ll*n*n));
}
```

---

## 作者：Smallbasic (赞：4)

期望其实是个幌子，我们实际上要求的是每个区间不同的数字个数和，最后除以总区间数就是答案。

考虑怎么求区间 $[l,r]$ 的不同的数字个数，我们假定每个数只有它在区间中最后一次出现的位置对答案有贡献。记 $nxt[i]$ 为在 $i$ 位置上的数$a_i$在数组中下一次出现的位置。如果 $a_i$ 就是最后一次出现，那 $nxt_i=n+1$。我们发现，对于 $i\in[l,r]$，只有 $nxt_i>r$ 时，这个位置才会对答案有贡献(否则下一次出现还是在区间内，这个位置就不是这个数在区间中最后一次出现的位置)。那么区间 $[l,r]$ 中不同的数字个数即为：

$$\sum_{i=l}^r[nxt_i>r]$$

而我们要求的每个区间不同的数字个数和,就是：

$$\sum_{l=1}^n \sum_{r=l}^n \sum_{i=l}^r [nxt_i>r]$$

考虑把先枚举 $i$:

$$\sum_{i=1}^n \sum_{l=1}^i \sum_{r=i}^n  [nxt_i>r]$$

我们发现 $l$ 对最后一层的统计没有影响，可以直接写成：

$$\sum_{i=1}^n i\cdot \sum_{r=i}^n  [nxt_i>r]$$

$$=\sum_{i=1}^n i\cdot (nxt_i-i)$$

显然可以 $O(n)$ 计算。

有坑点：这题随机 $l$ 和 $r$ 的时候，如果 $l>r$，那么会交换 $l$ 和 $r$，此时这个区间对答案的分子分母都贡献了两次，是不用考虑的。但是还有 $l=r$ 的情况，此时 $l$ 和 $r$ 怎么交换都是一种情况。因此分子分母都要减去 $n$。所以设我们之前求出的每个区间不同的数字个数和为 $ans$,则输出的答案为：

$$ans\times 2 - n \over n\times(n+1)-n$$

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

int a[N], nxt[N], n, lst[N];
ll ans = 0;

inline int read() {
	int s = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) s = (s << 1) + (s << 3) + (ch & 15), ch = getchar();
	return s;
}

int main() {
	n = read(); memset(lst, -1, sizeof lst);
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = n; i; --i) {
		if (lst[a[i]] == -1) lst[a[i]] = n + 1;
		nxt[i] = lst[a[i]]; lst[a[i]] = i;
	}
	for (int i = 1; i <= n; ++i)
		ans = ans + 1ll * i * (nxt[i] - i);
	ans = ans * 2ll - n;
	ll all = 1ll * n * (n + 1) - n;
	printf("%.6lf", 1.0 * ans / all);
	return 0;
}
```


---

## 作者：ChthollyTree (赞：1)


其实，我们就是要求一个序列的所有子区间的数的种类数之和

我们考虑，假设从左到右第一次出现的数产生贡献

那么，对于一个数$a_i$，它产生贡献的区间

l 需要在 相同数的上一次出现的位置 + 1 ~ i

r 需要在 i~n

对于生成的l,r 有 $n^2$种情况

其中l ≠ r 时都有两种可能(l> r 和 l < r)
 
l = r时候只有一种情况

所以要特殊处理 l = r

```
#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define MAXN 1000005

LL n,m;
LL a[MAXN],c[MAXN];
LL ans;

void rd()
{
	cin >> n;
	for(int i = 1; i <= n; i ++)
		cin >> a[i];
}

int main()
{
	rd();
	for(int i = 1; i <= n; i ++) {
		ans += (i - c[a[i]]) * (n - i+1) * 2 - 2;
		c[a[i]] = i;
	}
	ans += n;
	printf("%.6lf",(double)ans/(double)(n*n));
	return 0;
 } 
```

---

## 作者：TTpandaS (赞：0)

这是一个古典实验，所以答案为每个数字在区间出现次数的期望。对于每个区间，随机变量为 $1/0$，所以答案为每个数字在区间出现概率。

区间数量为 $n^2-n$ 个，因为 $l,r$ 无大小限制，但是 $l=r$ 的情况会在 $n^2$ 中计算两次。

数字只会在第一次出现时对次数产生贡献，所以我们在处理 $a_i$ 时我们认为 $a_i$ 是第一个在区间中大小为 $a_i$ 的数。所以区间的起点至少为上一个大小为 $a_I$ 出现的位置 $+1$，最多为 $i$，终点至少为 $i$，最多为 $n$，所以预处理每个数字上一次出现的位置 $pre_i$，每个数字在区间出现次数的总数为

$$ \sum_{i=1}^{n}2(i-pre_{a_i})(n-i+1) $$

这个算式同样会把 $l=r$ 的情况计算两次，答案 $-n$ 即可。

---

## 作者：泠小毒 (赞：0)

# Random Query
给定一个数列A,随机选取两个值l,r(等概率,可以相等),进行以下操作：

1.if(l>r):swap(l,r) 2.对数列A中l,r区间内的数去重得到数列B

求数列B的期望大小。
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190514/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190514.html)
## 解法
答案可以转化为总长度/序列总数

然后手推一下原始总长度的公式，n+2(2(n-1)+3(n-2)+...+n(n-(n-1)))

序列总数就是n方，之后看去重后的贡献，对于a[i]和a[j] (i<j)，只有当它们相等时才有贡献

我们设定一个区间中去重时只留下最后一次出现的数，所以a[i]会删去，a[j]会留下，而贡献是i*(n-j+1)，即左端点取在i左边，右端点取在j右边，此时i点已经不会对后面再出现的该数产生影响，所以只需要对最近的相等的数作处理即可
## ac代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,a[1000010],last[1000010];
double ans,res;
int main()
{
	memset(last,0,sizeof(last)),scanf("%d",&n),ans=double(n),res=double(n)*double(n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),ans+=double(n-i)*double(i+1)*2.0;
	for(int i=1;i<=n;i++)
		{if(last[a[i]])ans-=double(last[a[i]])*double(n-i+1)*2.0;last[a[i]]=i;}
	printf("%.6f",ans/res);
	return 0;
}
```

---

