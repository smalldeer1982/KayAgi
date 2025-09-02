# Yet Another Array Queries Problem

## 题目描述

You are given an array $ a $ of size $ n $ , and $ q $ queries to it. There are queries of two types:

- $ 1 $ $ l_{i} $ $ r_{i} $ — perform a cyclic shift of the segment $ [l_{i},r_{i}] $ to the right. That is, for every $ x $ such that $ l_{i}<=x<r_{i} $ new value of $ a_{x+1} $ becomes equal to old value of $ a_{x} $ , and new value of $ a_{li} $ becomes equal to old value of $ a_{ri} $ ;
- $ 2 $ $ l_{i} $ $ r_{i} $ — reverse the segment $ [l_{i},r_{i}] $ .

There are $ m $ important indices in the array $ b_{1} $ , $ b_{2} $ , ..., $ b_{m} $ . For each $ i $ such that $ 1<=i<=m $ you have to output the number that will have index $ b_{i} $ in the array after all queries are performed.

## 样例 #1

### 输入

```
6 3 5
1 2 3 4 5 6
2 1 3
2 3 6
1 1 6
2 2 1 5 3
```

### 输出

```
3 3 1 5 2 
```

# 题解

## 作者：yuzhechuan (赞：5)

提供一个不考虑特殊性质，但代码好写易理解的fhq文艺平衡树做法（好写是基于你有板子）

---

### 题解：

众所周知文艺平衡树可以解决一些区间颠来倒去的问题

对于操作1：把原序列拆开成$a-b-c-d$四段，其中$a=[1,l-1],b=[l,r-1],c=[r,r],d=[r+1,n]$，然后重新合并成$a-c-b-d$就行了

对于操作2：这是文艺平衡树的经典操作，直接拆开后在中间打个翻转标记即可

最后再遍历一遍平衡树就可以得到每个位置上的数了

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define getchar gc
inline char gc(){
	static char buf[1<<16],*p1=buf,*p2=buf;
	if(p1==p2){
		p2=(p1=buf)+fread(buf,1,1<<16,stdin);
		if(p2==p1) return EOF;
	}
	return *p1++;
}
#endif
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

#define new NEW

const int N=2e5+5;
int n,rt,m,q,cnt,ansn,ans[N];
bool tag[N];

struct node{
	int lc,rc,rnd,val,sz;
}a[N];

void up(int x){
	a[x].sz=a[a[x].lc].sz+a[a[x].rc].sz+1;
	return ;
}

int new(int x){
	a[++cnt]=(node){0,0,rand(),x,1};
	return cnt;
}

void pushdown(int x){
	if(!tag[x]) return ;
	swap(a[x].lc,a[x].rc);
	if(a[x].lc) tag[a[x].lc]^=1;
	if(a[x].rc) tag[a[x].rc]^=1;
	tag[x]=0;
}

int merge(int x,int y){
	if(!x||!y) return x|y;
	if(a[x].rnd<a[y].rnd){
		pushdown(x);
		a[x].rc=merge(a[x].rc,y);
		up(x);
		return x;
	}
	else{
		pushdown(y);
		a[y].lc=merge(x,a[y].lc);
		up(y);
		return y;
	}
}

void split(int now,int k,int &x,int &y){
	if(!now){
		x=y=0;
		return ;
	}
	pushdown(now);
	if(a[a[now].lc].sz+1<=k){
		x=now;
		split(a[now].rc,k-(a[a[now].lc].sz+1),a[now].rc,y);
	}
	else{
		y=now;
		split(a[now].lc,k,x,a[now].lc);
	}
	up(now);
}
//上面是模板
void doit(){
	int op,l,r;
	read(op);read(l);read(r);
	if(op==1){
		int a,b,c,d;
		split(rt,l-1,a,b); //拆成四段
		split(b,r-l,b,c);
		split(c,1,c,d);
		rt=merge(a,merge(c,merge(b,d)));
	}
	else{
		int x,y,z;
		split(rt,l-1,x,y);
		split(y,r-l+1,y,z);
		tag[y]^=1; //中间打上翻转标记
		rt=merge(x,merge(y,z));
	}
}

void print(int x){ //最后遍历一遍平衡树，得到答案
	if(!x) return ;
	pushdown(x);
	print(a[x].lc);
	ans[++ansn]=a[x].val;
	print(a[x].rc);
}

signed main(){
	srand(time(NULL));
	read(n);read(m);read(q);
	for(int i=1,x;i<=n;i++) rt=merge(rt,new(read(x)));
	while(m--) doit();
	print(rt);
	while(q--){
		int x;
		read(x);
		write(ans[x]);putchar(' '); //O1查询
	}
}
```

---

## 作者：yuheng_wang080904 (赞：3)

## 题意

给你一个数列 $a$ 和 $q$ 次操作，$m$ 次询问：求出操作完的数列的第 $m_i$ 个数字是多少。

操作分两种：给定 $t,l,r$。若 $t=1$，将每个 $x \in [l,r-1]$ 向右移一位，将 $a[r]$ 移动到 $a[l]$ 的位置。若 $t=2$，翻转区间 $[l,r]$。

## 思路

我在此介绍一个比较朴素的做法——倒推。对于每次询问可以 $O(q)$ 解决，因此不会超时。

我们倒着模拟，设最终下标为 $x$，我们可以这样来求初始下标：从最后一次操作开始，依次向前推出每次操作前的下标。

对于每次操作，如果 $t=1$，分类讨论如下：若 $x<l$ 或 $x>r$，那么 $x$ 不变。若 $x \in [l+1,r]$，那么 $x=x-1$，若 $x=l$，那么 $x=r$。

如果 $t=2$，分类讨论如下：若 $x<l$ 或 $x>r$，那么 $x$ 不变。若 $x \in [l,r]$，那么 $x=l+r-x$。因为这里反转前后对应下标之和为 $l+r$。

注意得出初始下标后要输出的是 $a_x$ 这一数值，而并非 $x$ 这一下标！

## 代码

根据思路，我们就可以写出以下精简的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,m,a[200005],c[200005][5];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>q>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=q;i++)cin>>c[i][1]>>c[i][2]>>c[i][3];
    while(m--){
	int x;
	cin>>x;
	for(int i=q;i>=1;i--){
	    if(x<c[i][2]||x>c[i][3])continue;
            if(c[i][1]==1){
		if(x==c[i][2])x=c[i][3];
		else x--;
	    }
            else x=c[i][2]+c[i][3]-x;
	}
	cout<<a[x]<<" ";
    }
    return 0;
}
```


---

## 作者：kevin1616 (赞：1)

### 审题
给你一个长度为 $n$ 的数组 $a$，求这个数组经过 $q$ 次操作后的第 $b_i$ 位的个数。

其中，操作分以下两种：

1. 将 $a_l\sim a_r$ 向右循环移动一位。
2. 将 $a_l\sim a_r$ 反转。


***
### 方法
【暴力】暴力枚举所有操作，最后保存在一个数组里输出。时间复杂度 $O(qn)$，明显是会超时的。

【倒推】既然只是改变位置的操作，那么肯定可以表示出对于操作位置的变化情况。时间复杂度 $O(qm)$，是可以通过本题的。
***
### 思路
每次得到一个 $b_i$，即得到一个经过最多 $q$ 次操作的一个位置。既然是倒推，那么必然是需要从 $q$ 枚举到 $1$，对于每次操作取逆。以下是分类讨论：

+ 如果 $t=1$，即整体区间向右循环移动一位。设位置为 $x$，上一个位置为 $x'$，则当 $l+1\le x\le r$ 时，$x'=x-1$；当 $l=x$ 时，$x'=r$，否则不变。
+ 如果 $t=2$，即整体区间反转。设位置为 $x$，上一个位置为 $x'$，则当 $l\le x\le r$ 时，$x'=l+r-x$，否则不变。

最后只需要输出当前位的数即可。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,m;
int a[200005];
int t[200005];
int l[200005];
int r[200005];
int main(){
    cin >> n >> q >> m;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= q;i++) cin >> t[i] >> l[i] >> r[i];
    for(int i = 1;i <= m;i++){
        int x;
        cin >> x;
        for(int j = q;j >= 1;j--){ //逆推
            if(t[j] == 1 && x <= r[j] && x >= l[j] + 1) x--; //如果是操作1而且l<x<=r,那么x'=x-1
            else if(t[j] == 1 && x == l[j]) x = r[j]; //如果是操作1而且x=l,那么x'=r
            else if(t[j] == 2 && x <= r[j] && x >= l[j]) x = l[j] + r[j] - x; //如果是操作2而且l<=x<=r,那么x'=l+r-x
        }
        cout << a[x] << " "; //输出当前位对应的初始位的值即操作后当前位的值
    }
    return 0;
}
```
不抄题解，从我做起！

---

## 作者：Skies (赞：1)

看了看题解，有打平衡树的，还有链表

##### 但我不用高级算法，超级简单

## 思路

因为看到数据范围，m<100,所以考虑

##### <u>倒推</u>的思路

记录下每个操作，然后倒着推回去

设当前位置为x

对于1操作，x--(注意边界)

对于2,x=l+r-x.

##### ~~就这？~~

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void rd(T &x) {
	x=0;
	char ch=getchar();
	bool f=false;
	while(!isdigit(ch)) {
		if(ch=='-') {
			f=true;
		}
		ch=getchar();
	}
	while(isdigit(ch)) {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	x=f?-x:x;
	return ;
}
template <typename T>
inline void wr(T x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) wr(x/10);
	putchar(x%10^48);
	return ;
}
const int N=2e5+10;

int n,q,m;
int a[N],b[N];
//m突破口
struct node {
	int op,l,r;
} qus[N];
int main() {
	rd(n),rd(q),rd(m);
	for(int i=1; i<=n; i++) {
		rd(a[i]);
	}
	for(int i=1; i<=q; i++) {
		rd(qus[i].op),rd(qus[i].l),rd(qus[i].r);
	}
	for(int o=1; o<=m; o++) {
		int x;
		rd(x);
		for(int i=q; i>0; i--) {
			if(qus[i].l<=x&&x<=qus[i].r) {
				if(qus[i].op==1) {
					if(x==qus[i].l)x=qus[i].r;
					else x--;
				} else {
					x=qus[i].l+qus[i].r-x;
				}
			}

		}
		printf("%d ",a[x]);
	}
	return 0;
}
```





---

## 作者：yzx72424 (赞：1)

这道题CF官方给的标签是数据结构，链表。

但是我们观察数据可以发现m最大只有100，所以...直接开一个数组模拟就ok了，不需要任何优化，
按顺序离线操作：

```
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
struct x{
  int id, l, r;
}qq[N];
int n, q, m, p,a[N];
int main() {
  scanf("%d%d%d",&n,&q,&m);
  for (int i = 1; i <= n; i++)scanf("%d",&a[i]);  
  for (int i = 1; i <= q; i++)scanf("%d%d%d",&qq[i].id,&qq[i].l,&qq[i].r) ;
  while(m--){
    scanf("%d", &p);
    for (int i = q; i >= 1; i--) {
      if (qq[i].l <= p && qq[i].r >= p) {
       if (qq[i].id == 1) {
          if(qq[i].l == p) p =qq[i].r;
           else p--;
        }
      else p =qq[i].r+qq[i].l-p;
      }
    }
    printf("%d ", a[p]);
  }
  return 0;
}
```

---

## 作者：GeXiaoWei (赞：0)

# CF863D Yet Another Array Queries Problem
## 解析
众所周知，平衡树的代码很长不好写，所以我用的递推。

操作分为两种，一是将 $a_l \sim a_r$ 向右移动一为，二是将 $a_l\sim a_r$ 反转。

每得到一个 $b_i$，就以 $O(q)$ 的时间进行倒推，根据 $t$ 的值分类讨论。如果 $t=1$ 且位置为 $x$，上一个位置为 $y$，$l+1\le x\le r$，那么 $y=x-1$。若 $l=x$，则 $y=r$。否则不变。

若 $t=2$，位置为 $x$，上一个位置为 $y$，则当 $l\le x\le r$，$y=l+r-x$。否则不变。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,m,a[1000005],d[1000005][5],x;
inline int read(){
	int x=0,f=1;
	char ch;
	ch=getchar_unlocked();
	while(!(ch>='0'&&ch<='9')){
		if(ch=='-') f=-1;
		ch=getchar_unlocked();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar_unlocked();
	}
	return x*f;
}inline void write(int x){
	if(x<0) putchar('-'),x*=-1;
	if(x>9) write(x/10);
	putchar_unlocked(x%10+'0');
}int main(){
    n=read(),q=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=q;i++) d[i][1]=read(),d[i][2]=read(),d[i][3]=read();
    while(m--){
		x=read();
		for(int i=q;i;i--){
		    if(x<d[i][2]||x>d[i][3]) continue;
	        if(d[i][1]==1){
				if(x==d[i][2]) x=d[i][3];
				else x--;
			}else x=d[i][2]+d[i][3]-x;
		}
		write(a[x]);
		printf(" ");
    }
    return 0;
}
```

---

## 作者：Wind_love (赞：0)

## 思路
我们采用递归的形式，在所有操作完成后倒推每个数字的位置。   
这里分为两个操作，对于操作一，我们直接前推一位即可，注意判断边界。    
我们知道，如果一个数反转前位置为 $i$，则其所在区间 $[l,r]$ 反转后它的位置为 $r-i+l$。所以，对于每个操作二，我们按公式将其位置反转即可，注意判断当前数字是否在反转区间内。    
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,m;
long long t[1145140],l[1145140],r[1145140];
long long a[1145140];
long long dg(long long i,long long ans){
	if(i==0){
		return ans;
	}
	if(t[i]==1){
		if(l[i]<ans&&ans<=r[i]){
			return dg(i-1,ans-1);
		}
		else if(ans==l[i]){
			return dg(i-1,r[i]);
		}
		else{
			return dg(i-1,ans);
		}
	}
	if(t[i]==2){
		if(ans<=r[i]&&ans>=l[i]){
			return dg(i-1,r[i]-ans+l[i]);
		}
		else{
			return dg(i-1,ans);
		}
	}
}
int main(){
	scanf("%lld%lld%lld",&n,&q,&m);
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]); 
	}
	for(long long i=1;i<=q;i++){
		scanf("%lld%lld%lld",&t[i],&l[i],&r[i]);
	}
	long long x;
	while(m--){
		cin>>x;
		printf("%lld ",a[dg(q,x)]);
	}
}

---

## 作者：SJH__qwq (赞：0)

$m\le 100$，所以考虑对于每一个询问到答案的位置暴力倒推。

因为有效的操作次数最多只有 $q$，所以单次询问的时间复杂度为 $O(q)$，$m$ 次询问的总的时间复杂度为 $O(mq)$。

因为 $m\times q\le 2\times 10^7$，所以直接暴力模拟可以通过。

---

## 作者：Nuclear_Fish_cyq (赞：0)

## 思路

观察数据范围，我们发现查询数很小，而且每次都是单点查询。于是我们可以考虑逆向思维，每次查询都从后往前遍历每个操作并且计算操作前被查询的卡片所在的位置并不断更新即可。

上代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
//#define mod
//#define range
using namespace std;
int n, m, q, a[200000], opt[200000], l[200000], r[200000], now;

//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> q;
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	for(int i = 0; i < m; i++){
		cin >> opt[i] >> l[i] >> r[i];
		l[i]--;
		r[i]--;
	}
	for(int i = 0; i < q; i++){
		cin >> now;
		now--;
		for(int j = m - 1; j >= 0; j--){
			if(now >= l[j] && now <= r[j]){
				if(opt[j] == 1){
					now -= 1;
					if(now < l[j]){
						now = r[j];
					}
				}
				else{
					now = l[j] + r[j] - now;
				}
			}
		}
		cout << a[now] << " ";
	}
	return 0;
}

```

---

## 作者：fengxiaoyi (赞：0)

**注意：这篇题解是写给像我这样不会那个什么什么平衡树的萌新看的，大佬请自动跳过。**

### 简单易懂的解法：倒推

回归正题。

这题如果是暴力的话，时间复杂度为 $O(nq)$，肯定是会炸的，于是就可以利用 $m$ 很小这特殊性质，把时间复杂度跟 $m$ 扯上关系，于是就想到了倒推。

怎么倒推呢？其实很简单。

#### 先讲明白正序的操作吧

- 如果 $t_i=1$，不妨设当前下标为 $x$:  
$\circ$ 如果 $x\lt l_i$ 或者 $x\gt r_i$（既 $x$ 在操作区间的外面）则不做操作。  
$\circ$ 反之，$x$ 在操作区间的里面，如果 $x=r_i$，则 $x\gets l_i$，否则 $x\gets x+1$。
- 如果 $t_i=2$，同理，不妨设当前下标为 $x$:  
$\circ$ 如果 $x\lt l_i$ 或者 $x\gt r_i$（既 $x$ 在操作区间的外面）则不做操作。  
$\circ$ 反之，$x$ 在操作区间的里面，由于是对翻转操作，设 $x$ 的翻转后在 $x'$，则满足一个性质：$x+x'=l_i+r_i$，所以 $x\gets l_i+r_i-x$。

#### 那再来看看倒序的情况。

首先，记录当前的下标 $now_b$，初值 $now_b=b_i$。  
从后往前倒序枚举每个操作，计这是第 $j$ 个操作：

- 如果 $t_i=1$:  
$\circ$ 与正序一样，如果 $now_b\lt l_i$ 或者 $now_b\gt r_i$（既 $now_b$ 在操作区间的外面）则不做操作。  
$\circ$ 反之，$now_b$ 在操作区间的里面，操作即为正序的撤销操作，如果 $x=l_i$，则 $now_b\gets r_i$，否则 $now_b\gets now_b-1$。
- 如果 $t_i=2$:  
$\circ$ 与正序一样，如果 $now_b\lt l_i$ 或者 $now_b\gt r_i$（既 $now_b$ 在操作区间的外面）则不做操作。  
$\circ$ 反之，$now_b$ 在操作区间的里面，操作其实与正序时一样，由于是对翻转操作，设 $now_b$ 的翻转后在 $now_b'$，$now_b\gets l_i+r_i-now_b$。

最后输出 $a_{now_b}$ 即可。

### 代码，仅供参考

```
#include<bits/stdc++.h>
using namespace std;
int n,m,q,a[200010],t[200010],l[200010],r[200010];
int main(){
	scanf("%d%d%d",&n,&q,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=q;i++) scanf("%d%d%d",&t[i],&l[i],&r[i]);
	for(int i=1;i<=m;i++){
		int b;
		scanf("%d",&b);
		for(int j=q;j>=1;j--){
			if(l[j]>b||r[j]<b) continue;
			if(t[j]==1){
				if(b==l[j]) b=r[j];
				else b--;
			}
			else b=l[j]+r[j]-b;
		}
		printf("%d ",a[b]);
	}
	return 0;
}
```


---

## 作者：Zzzzzzzm (赞：0)

#### ~~蒟蒻不会线段树平衡树，随便瞎写~~

拿到题我们首先看数据，$1≤n$,$q≤200000$,$1≤m≤100$。
可以估计$nq$或者$mq$都是可以通过的。

然而没有精通线段树或者平衡树的我只好操作下标来做。

我们可以不用管任何操作，把操作和数存下来。不管操作对数的实际影响而只需要在询问时对下标进行倒推操作找到原坐标。
```
6 3 5
1 2 3 4 5 6
2 1 3
2 3 6
1 1 6
2 2 1 5 3
```
例如样例询问2号坐标，我们看最后一次将$1$~$6$右移，所以再次之前是$1$号坐标，倒数第二次操作是$3$~$6$交换，所以无关于$1$，第一次为$1$~$3$交换，交换前为$3$号坐标，所以输出$x[3]=3$。

总时间复杂度为询问次数$m×q$操作次数，即$m×q=2×10000000$。发现仍然能水过，所以不需要平衡树线段树就能做。

我们用$a[i][0]$表示对于第i个操作如果是右移的起始点，$a[i][1]$表示终止点。$b[i][0]$表示第$i$个操作如果是反转的起始点，$b[i][1]$表示终止点。其实完全没有必要分开，但这样也行。用$ch[i]$表示是这是右移操作还是反转操作。

正解如下：


```cpp
#include<bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T&x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return;
}

template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
	putchar(x%10^48);
    return;
}													//快读(可以读入long long和int)

int n, m, q, ch[200005];
int a[200005][2], b[200005][2], x[200005], w;

int main(){
	read(n), read(q), read(m);
	for(int i = 1; i <= n; i++){
		read(x[i]);
	}
	for(int i = 1; i <= q; i++){
		read(ch[i]);
		if(ch[i] == 1)
			read(a[i][0]), read(a[i][1]);
		if(ch[i] == 2)
			read(b[i][0]), read(b[i][1]);
	}
	for(int i = 1; i <= m; i++){
		read(w);
		int k = w;
		for(int j = q; j >= 1; j--){
			if(ch[j] == 2){
				if(k >= b[j][0] && k <= b[j][1]){
					k = b[j][1] + b[j][0] - k; 
				}
			}
			if(ch[j] == 1){
				if(k >= a[j][0] && k <= a[j][1]){
					if(k == a[j][0])
						k = a[j][1];
					else	k--;
				}
			}
		}
		write(x[k]);
		printf(" ");
	}
	return 0;
}
```


---

