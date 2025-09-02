# 「LAOI-9」Update

## 题目描述

给定长度为 $n$ 的序列 $a$，接下来 $m$ 次操作，每次操作形如：

- 给定 $l,r$，对于 $i \in [l,r]$，令 $a_i \leftarrow a_i + \lfloor \log_2 a_i \rfloor $。

$m$ 次操作后，输出 $a$ 序列。

## 说明/提示

**本题目采用捆绑测试**。

| 子任务编号 | $n,m \le$ | 特殊性质 | 分值 |
| :-----: | :------: | :------: | :------: |
| $1$ | $10^3$ | 无 | $30$ |
| $2$ | $10^5$ | A | $20$ |
| $3$ | $10^5$ | 无 | $50$ |

特殊性质 A：$a_i \le 100$。 

对于 $100 \%$ 的数据，满足 $1 \le n,m \le 10^5$，$1 \le a_i \le 10^5$，$1 \le l \le r \le n$。

## 样例 #1

### 输入

```
5 2
2 3 4 5 6
2 3
1 1```

### 输出

```
3 4 6 5 6```

# 题解

## 作者：lilong (赞：17)

#### A 性质

首先使用差分维护每个 $a_i$ 的操作次数。

不难发现由于数的种类很少，因此直接用一个数组记录每个数 $i$ 操作 $j$ 次后的值。预处理完后，记 $A$ 为 $a_i$ 的最大值，则时间复杂度 $O(mA)$。


```cpp
for( int i = 1 ; i <= 100 ; i ++ )
{
	f[i][0] = i;
	for( int j = 1 ; j <= m ; j ++ )
		f[i][j] = f[i][j - 1] + lg[f[i][j - 1]];
}
```

#### 正解

其实我们可以从 A 性质出发继续思考。当值域达到 $10^5$ 时，我们需要寻找一个能平衡时间空间的做法。如果一次能够完成不止一次操作，那么运行效率将得到提高。不难想到可以倍增，记 $f_{i,j}$ 表示从 $i$ 进行 $2^j$ 次操作得到的数，则 $f$ 是好预处理的。同时 $i$ 的上界也是确定的，由于 $10^5 \times 20 < 2^{21}$，故 $\log_2i$ 不超过 $20$，即修改后的 $i$ 不超过 $2.1 \times 10^6$。剩下的就不难了。

令 $A=2.1 \times 10^6$，则总时间复杂度 $O(n+m+(n+A)\log m)$，可以通过。


```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int N = 2100010;
int n,m,a[200001],l,r,d[200001],f[2400001][19],lg[2400001];

int g( int x , int y )
{
	for( int i = 18 ; i >= 0 ; i -- )
		if( y & ( 1 << i ) )
			x = f[x][i];
	return x;
}

int read( void )
{
	int x = 0,f = 1;
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();
	while( ch >= '0' && ch <= '9' ) x = x * 10 + ch - '0',ch = getchar();
	return x * f;
}

void write( int x )
{
    if( x <= 9 )
    {
        putchar( x + '0' );
        return;
    }
    write( x / 10 );
    putchar( x % 10 + '0' );
    return;
}

int main()
{
    cin >> n >> m;
	lg[1] = 0,f[1][0] = 1;
	for( int i = 2 ; i <= N ; i ++ )
		lg[i] = lg[i >> 1] + 1,f[i][0] = i + lg[i];
	for( int j = 1 ; j <= 18 ; j ++ )
		for( int i = 1 ; i <= N ; i ++ )
			f[i][j] = f[f[i][j - 1]][j - 1];
	for( int i = 1 ; i <= n ; i ++ )
		a[i] = read();
	while( m -- )
	{
		l = read(),r = read();
		d[l] ++,d[r + 1] --;
	}
	for( int i = 1 ; i <= n ; i ++ )
	{
		d[i] += d[i - 1];
		write( g( a[i] , d[i] ) );
        putchar( ' ' );
	}
	return 0;
}
```

有一种实际效率更高的解法。大致思路是考虑当前需要多少次操作才能使当前 $\lfloor \log_2 a_i \rfloor$ 增加 $1$，显然这个操作次数为 $\lceil \dfrac{2^{\lfloor \log_2 a_i \rfloor+1}-a_i}{\lfloor \log_2 a_i \rfloor} \rceil$。将其与剩余操作次数比较并计算即可，注意特判 $\lfloor \log_2 a_i \rfloor=0$ 的情况。时间复杂度也是线性对数。以下给出这种解法的实现。


```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define N 200001

using namespace std;

int n,a[N],d[N],m,l,r,k,tt;

int main()
{
	cin >> n >> m;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i];
	while( m -- )
	{
		cin >> l >> r;
		d[l] ++,d[r + 1] --;
	}
	for( int i = 1 ; i <= n ; i ++ )
	{
		d[i] += d[i - 1];
		m = d[i];
		k = int( log2( a[i] ) );
		if( k == 0 )
		{
			cout << a[i] << ' ';
			continue;
		}
		while( m )
		{
			tt = ( ( 1 << ( k + 1 ) ) - a[i] ) / k;
			if( ( ( 1 << ( k + 1 ) ) - a[i] ) % k ) tt ++;
			if( tt >= m )
			{
				a[i] += m * k;
				m = 0;
			}
			else
			{
				a[i] += tt * k;
				m -= tt;
			}
			k ++;
		}
		cout << a[i] << ' ';	
	}
	return 0;
}
```

---

## 作者：末然Ender (赞：3)

# 题解：P11894 「LAOI-9」Update

## 思路

多次区间修改，很容易让我们想到 ~~线段树~~ 差分。

首先对着 $m$ 次操作差分最后统一处理，但是直接处理只能过 $\text{Subtask}1$，我们发现在很多的操作次数内所加的数 $\log_2a_i$ 是不变的，我们通过计算可以得知多少次操作以后 $\log_2a_i$ 才会变化，这中间的部分可以直接 $O(1)$ 加上的。

然后注意一下 $\log_2a_i$ 有可能是 $0$ 不要拿 $0$ 做除数就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>
void read(T& x){x=0;char ch=getchar();long long f=1;while(!isdigit(ch)){if(ch=='-')f*=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}x*=f;}
template<typename T,typename... Args>
void read(T& first,Args&... args){read(first);read(args...);}
template<typename T>
void write(T arg){T x=arg;if (x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
template<typename T,typename... Args>
void write(T arg,Args... args){write(arg);if(sizeof...(args) !=0){putchar(' ');write(args...);}}
const int N=4e5+4,M=2e6+5;
ll n,m;
ll a[N],cf[N];
int main(){
	read(n,m);
	for(int i=1;i<=n;i++){
		read(a[i]);
	}
	ll l,r;
	while(m--){
		read(l,r);
		cf[l]++,cf[r+1]--;
	}
	ll sum=0;
	for(int i=1;i<=n;i++){
		sum+=cf[i];
		ll t=sum;
		if((ll)log2(a[i])){
			ll lg=((1<<(ll)log2(a[i])+1)-a[i])/(ll)log2(a[i])+(((1<<(ll)log2(a[i])+1)-a[i])%(ll)log2(a[i])?1:0);
			while(t>=lg){
				t-=lg;
				a[i]+=lg*(ll)log2(a[i]);
				lg=((1<<(ll)log2(a[i])+1)-a[i])/(ll)log2(a[i])+(((1<<(ll)log2(a[i])+1)-a[i])%(ll)log2(a[i])?1:0);
			}
			if(t>0)a[i]+=t*(ll)log2(a[i]);
		}
		write(a[i]);
		putchar(' ');
	}
	return 0; 
}
```

---

## 作者：Accepetd (赞：3)

### 题目大意

对一个长度为 $n$ 的序列进行 $m$ 次操作。

每次操作给定一个区间 $[l,r]$，对区间内的每个 $a_i$ 加上 $\log_2 a_i$，$i \in [l,r]$。

---

### 大致思路

对于每次输入 $l$ 和 $r$，我们不急于直接操作，我们可以先存起来，到最后再统一操作。

我这里用的是线段树，对区间 $[l,r]$ 内的每个数的操作次数加一，但最后如果逐个操作很显然会超时。

那么我们可以进行优化。

---

### 具体作法

我们将每次操作的增量 $\lfloor \log_2 a_i \rfloor$ 记为 $m$，不难发现，当 $a_i$ 处于区间 $[2^m,2^{m+1}-1]$ 时，增量 $m$ 是一定的。

例如：

- 当 $a_i \in [8,15]$ 时 $m=3$。
- 当 $a_i$ 增加到 $16$ 时进入下一个区间，$m$ 变为 $4$。

因此我们可以通过计算每个区间内可以执行的最大操作次数，直接跳到下一区间的起始点或耗尽剩余操作次数。

这里可以使用位运算快速计算 `floor(log2(x))`。

- 即 `m = 31 - __builtin_clz(x)`。

下一区间的起始值为 $2^{m+1}$。

- 即 `next = 1 << (m + 1)`。

到下一区间的操作数为 `( ( next - x ) + m - 1) / m`。

- 即 `lgsum = ( ( next - x ) + m - 1) / m`

---

### AC代码
```cpp
//习惯压行，请见谅
#include<bits/stdc++.h>
#define F(i,a,b) for(register int i=a;i<=b;i=-~i)
#define lc p<<1 //左儿子 
#define rc p<<1|1 //右儿子 
using namespace std;typedef long long LL;
const int N=100002;int n,m,a[N],t[N];
struct tree{int l,r;LL sum,add;}tr[N*4];
inline void pushup(const int p){tr[p].sum=tr[lc].sum+tr[rc].sum;}//和 
inline void pushdown(const int p){//懒标记下移 
	if(tr[p].add){
		tr[lc].sum+=tr[p].add*(tr[lc].r-tr[lc].l+1);
		tr[rc].sum+=tr[p].add*(tr[rc].r-tr[rc].l+1);
		tr[lc].add+=tr[p].add;tr[rc].add+=tr[p].add;
		tr[p].add=0;
	}
}inline void build(const int p,const int x,const int y){//构建线段树 
	tr[p]={x,y,a[x],0};if(x==y)return;
	const int m=(x+y)>>1;
	build(lc,x,m);build(rc,m+1,y);
	tr[p].sum=tr[lc].sum+tr[rc].sum;
}inline void update(const int p,const int x,const int y,const int k){//区间修改 
	if(x<=tr[p].l&&tr[p].r<=y){
		tr[p].sum+=(long long)k*(tr[p].r-tr[p].l+1);
		tr[p].add+=k;return;
	}const int m=(tr[p].l+tr[p].r)>>1;
	pushdown(p);if(x<=m)update(lc,x,y,k);if(y>m)update(rc,x,y,k);pushup(p);
}inline LL query(const int p,const int x,const int y){//取件查询 
	if(x<=tr[p].l&&tr[p].r<=y)return tr[p].sum;
	pushdown(p);const int m=(tr[p].l+tr[p].r)>>1;LL sum=0;
	if(x<=m)sum+=query(lc,x,y);if(y>m)sum+=query(rc,x,y);
	return sum;
}inline void mylog2(int &x,const int k){
    int num=k;
    while(num>0){//仍需继续操作 
        if(x==1)break;
        int m=31-__builtin_clz(x);//位运算，等效于floor(log2(x)) 
        int next=1<<(m+1);//下一区间的起始值 
        if(m==0)break;//防止错误 
		int lgsum=((next-x)+m-1)/m;//到下一区间的操作次数 
        if(lgsum<=num){x+=m*lgsum;num-=lgsum;}//操作m*lgsum次后仍未操作完或刚好操作完 
		else{x+=m*num;num=0;}//剩余的操作次数小于m*lgsum
    }
}signed main(){
	cin>>n>>m;
	build(1,1,n);//建树 
	F(i,1,n)cin>>a[i];
	F(i,1,m){int l,r;cin>>l>>r;update(1,l,r,1);}//区间[l,r]内的每个数的操作次数+1 
	F(i,1,n){
		int o=query(1,i,i);//查询当前这个数的操作次数 
		mylog2(a[i],o);cout<<a[i]<<" ";//操作并输出 
	}return 0;
}//写注释真的有点费时间
```

---

## 作者：hoko (赞：3)

看到题目是区间修改，容易想到差分。但是题目要求对于每个 $a_i \leftarrow a_i + \lfloor \log_2 a_i \rfloor $。所以计算答案时要运用数学方法，对于当前这个 $a_i $，令 $\lfloor \log_2 b_i\rfloor=\lfloor\log_2 a_i\rfloor+1$，计算 $a_i$ 与 $b_i$ 之间的差值再除以 $\lfloor\log_2 a_i\rfloor$，如果差值要小于等于当前剩余的计算次数，就可以直接跳；否则就拿答案再加上剩余次数乘上 $\lfloor\log_2 a_i\rfloor$。时间复杂度是线性对数。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010101;
int n,m,a[N],sum[N],num,cnt[N];
int main(){
	scanf("%d%d",&n,&m);
	cnt[1]=1;
	for(int i=2;i<=25;i++)cnt[i]=cnt[i-1]*2;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		sum[l]++,sum[r+1]--;
	}
	for(int i=1;i<=n;i++){
		num+=sum[i];
		int ans=a[i],k;
		for(int j=1;j<=25;j++){
			if(cnt[j]>a[i]){
				k=j-1;break;
			}
		}
		for(int j=1;j<=num;){
			int w=log2(ans);
			int v=(cnt[k+1]-ans);
			if(w==0)break;
			else v=(v+w-1)/w;
			if(v<=num-j+1){
				j+=v;
				ans+=w*v;
				k++;
			}
			else{
				ans+=w*(num-j+1);
				j=num+1;
			}
		}
		printf("%d ",ans);
	}
	return 0;
}
```

---

## 作者：Fiendish (赞：2)

每一个数是独立的。

所以可以考虑把操作离线下来，用差分统计 $a_i$ 被操作的次数 $b_i$，然后对 $a_i$ 进行 $b_i$ 次操作即可。

但是这样直接做复杂度是 $O(nm)$ 的，无法保证通过此题。所以我们考虑如何在知道操作次数的情况下快速计算最终结果。

对于一个数 $x$，我们称一次操作为 $x\gets x+\lfloor \log_2x\rfloor$。容易观察到，只有 $x$ 大于等于 $2^{\lfloor \log_2x\rfloor+1}$ 之后 $\lfloor \log_2x\rfloor$ 才会发生变化。所以可以把 $b_i$ 次加法变成 $O(\log m)$ 次加法和 $O(\log m)$ 次乘法。这样时间复杂度大概为 $O(n\log m)$。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long a[100010];
int b[100010];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		b[l]++,b[r+1]--;//差分统计操作次数
	}
	for(int i=1;i<=n;i++) b[i]+=b[i-1];
	for(int i=1;i<=n;i++){
		if(a[i]==1){
			cout<<"1 ";
			continue;
		}
		while(b[i]){
			int mylg=__lg(a[i]);
			int cnt=ceil(1.0*((1<<mylg+1)-a[i])/mylg);//现在可以合并在一起的加法的次数，也是这一次乘法的乘数之一
			if(b[i]>=cnt) a[i]+=1ll*cnt*mylg,b[i]-=cnt;
			else{
				a[i]+=1ll*b[i]*mylg;
				break;
			}
		}
		cout<<a[i]<<' ';
	}
}
```

---

## 作者：canwen (赞：2)

题意不难理解，直接去看题目描述即可，这里不赘述。

容易想到做差分数组 $f$，每次给定 $l,r$ 就令 $f_{l}\gets f_l +1,f_{r+1}\gets f_{r+1}-1$。

最终对于 $1\le i \le n$，让 $f_{i}\gets f_{i-1}+f_{i}$，此时 $f_{i}$ 表示的就是 $a_{i}$ 需要做多少次操作。

不妨考虑最坏情况下存在 $a_{i}=10^{5}$，且 $f_{i} = 10^5$，容易证明最终结果应该是 $a_{i} = 2012379$，我们可以先处理出数组 $lg_{0\le i \le 2012379} = \lfloor \log_2 i \rfloor $。

显然 $lg$ 数组中会存在一些连续的 $lg_{i}$ 相同，而这是可以优化的，记录每个连续相同的 $lg_{i}$ 区间的右端点二分查找即可，这样我们可以一次性加一大部分相同的数字，而不用一个一个加。

最劣情况下，复杂度是 $O(n\log_2f_i)$ 的，$f_{i}$ 最大能到达 $10^5$，可以通过。
## Code
注意除以 $0$ 会神秘 RE！

```cpp
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
#define const constexpr
using namespace std;
#define int long long
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#define mk make_pair
#define pb emplace_back
#define pint pair<int,int>
#define i128 __int128
#define pc putchar('\n')
#define fst first
#define snd second
#define nowtime (double)clock()/CLOCKS_PER_SEC
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for(int i=(a);i<=(b);c)
#define _rrep(i,a,b) for(int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for(int i=(a);i>=(b);c)
#define _graph(i) for(int i=head[u];i;i=e[i].nxt)
int in(){
	char a = getchar();
	int k = 0, kk = 1;
	while(!isdigit(a)){
		if(a == '-') kk=-1;
		a=getchar();
	}
	while(isdigit(a)){
		k = k*10 + a - '0', a = getchar();
	}
	return k*kk;
}
void out(int a){
	if(a < 0) putchar('-'),a=-a;
	if(a > 9) out(a/10);
	putchar(a%10+'0');
}
const int N = 1e5 + 5;
int f[N],a[N],r[25],tot,lg[2012399];
signed main(){
	_rep(i,1,2012379) lg[i] = (int)log2(i);
	_rep(i,1,2012379){
		r[++tot] = i;
		int k = lg[i];
		while(i<2012379&&lg[i+1] == lg[i]) r[tot]=(++i);
	}
	int n = in(), m = in();
	_rep(i,1,n) a[i] = in();
	while(m--){
		int l = in(), r = in();
		f[l]++,f[r+1]--;
	}
	_rep(i,1,n){
		f[i] = f[i-1]+f[i];
		int k = f[i];
		while(k){
			int kk = lower_bound(r+1,r+1+tot,a[i])-r;
			if(lg[a[i]] == 0) {k = 0; break;} // 小心 RE 
			int can = (r[kk]-a[i])/lg[a[i]];
			if(k >= can){
				a[i] += can*lg[a[i]], k -= can;
				if(k) a[i] += lg[a[i]], --k;
			}else a[i] += lg[a[i]]*k, k = 0;
		}
		out(a[i]), putchar(' ');
	}
	return 0;
}
```

稳定切黄，被绿暴虐。

美味代码，欢迎 hack。

---

## 作者：luchenxi2012 (赞：2)

题目传送门 [P11894 「LAOI-9」Update](https://www.luogu.com.cn/problem/P11894)

注意到每次操作根本不需要任何参数，所以根本不需要用到数据结构（当然，如果要用到的话我应该不会做了）

我们维护每个数被操作的次数。这个不用线段树，差分即可。关键在于求出每个数的修改次数后怎么求出答案。

我们发现，$\lfloor\log_2a_i\rfloor$ 这个函数不减，而且差为 $1$ 的两个数之间至多差 $1$，所以我们想到只需知道这个函数在 $a_i$ 是几的时候会增加一就行了。

具体地，我们设 $x$ 是目前的 $\lfloor\log_2a_i\rfloor$，那么使 $x$ 变化的下一个数就是 $2^{x+1}$。那么，$a_i$ 就需要 $\lfloor\frac{2^{x+1}-a_i-1}{x}\rfloor+1$ 次操作使 $x$ 增加 $1$。所以只需要让 $a_i$ 不停往上跳就行了。

## 时间复杂度分析

注意到每个数至多操作 $m$ 次，就当成是 $m$ 次好了。

设目前的 $\lfloor\log_2a_i\rfloor$ 是 $x$，那么这一次至多会跳 $\frac{2^{x+1}-2^x}x=\frac{2^x}x$ 次，但是除了头尾跳的次数可能少一点之外，其余每次跳的时候都会跳这么多次。

并且注意到当 $x\ge20$ 时，$\frac{2^x}x\gt50000$，所以总跳的次数（算上头尾）可以直接小于 $1+20+\frac m{50000}+1=\frac m{50000}+22$，再乘上一个 $n$ 就是 $n(\frac m{50000}+22)\lt25n$，不会超时。（当然，这个估算非常松，实际上根本用不了那么多。不过既然不可能超时，那就不用管他了。）

看代码之前，还有一个坑点：注意当一开始 $a_i=1$ 时 $\lfloor\log_2a_i\rfloor$ 恒等于 $0$，所以千万要特判！不然除以 $0$ 会 RE。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int a[N], cf[N], g(int); // 求 log2 的函数
int getans(int x, int s) {
	int pl = g(x), nxt = 1 << pl + 1;
	if (!pl) return x; // 注意特判
	while (1) {
		int dis = nxt - x;
		int tm = (dis - 1) / pl + 1;
		if (s <= tm) return x + pl * s;
		x += pl * tm, s -= tm, ++pl, nxt <<= 1;
	}
}
int main() {
	int n, m, l, r;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	while (m--)
		scanf("%d%d", &l, &r),
		cf[l]++, cf[r + 1]--; // 不用线段树，差分即可
	for (int i = 1; i <= n; i++)
		cf[i] += cf[i - 1],
		printf("%d ", getans(a[i], cf[i]));
	return 0;
}
inline int g(int x) {return 31 - __builtin_clz(x);}
```

---

## 作者：guoshengyu1231 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/solution/P11894)
# 初步思考
首先这道题暴力肯定是不可行的， $n$ 和 $m$ 都是 $10^5$ 级别的。通过理解题意我们可以知道这道题本质上是一道区间修改的题目。既然是区间修改，首先联想到差分。但是这道题目又有些不同，因为只有修改的量是同一个时才可以用差分，而这题是让我们在一个区间内的所有数都加上那个数的对数，而每个数的对数是不一样的，所有肯定不能直接用差分。但或许可以通过某些方法，或是将这个数组转化一下，说不定就可以用差分了。 $\\$ 

我当时也是这样想的，而且想了好久。当然，在大部分的时候，你的方向应该是对的。你只要再坚持想下去，或许你离成功就不远了。但现在，你想了好久都没有想出来，那你是不是应该换一个方向，也许是你想复杂了，说不定马上就豁然开朗了。回归正题，事实证明，将整个数组差分是不可行的（不信的话就自己去试一试），那我们得换个思路。考虑到 $1\le n,m\le10^5$，那可能是时间复杂度 $O(n \log n)$ 的算法。那我们得想出一种方法，来计算一个数被进行了若干次操作后是什么的算法，并且时间复杂度 $O( \log n)$。最终，你查遍了全部的算法，终于找到了一种非常合适的算法——倍增。而且利用倍增的思想建立 ST 表，时间复杂度也是 $O(n \log n)$ 。~~你不禁感叹：“天哪，这简直是为倍增量身定做的题目。”~~
# 具体步骤
- 初始化 ST 表，$f_{i,j}$表示 $i$ 经过 $2^j$ 次操作后得到的数。
- 通过差分的方法计算出数组中每个数经历了多少次操作。
- 通过查询 ST 表来快速计算出每个数经历了若干次操作后得到的数。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2100005;
int n,m,f[maxn][20],a[200005],lg[maxn],s[200005];
void init()
{
	f[1][0]=1;
	for(int i=2;i<=maxn;i++)
	 {
		lg[i]=lg[i>>1]+1;
		f[i][0]=i+lg[i];
	 }	
	for(int j=1;j<=18;j++)
	 for(int i=1;i<=maxn;i++)
	  f[i][j]=f[f[i][j-1]][j-1];	
}//初始化 
int main()
{
	init();
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	while(m--)
	 {
		int x,y;
		cin>>x>>y;
		s[x]++;s[y+1]--;	
	 }
	//差分
	for(int i=1;i<=n;i++) 
	 {
		s[i]+=s[i-1];
		int ans=a[i];
		for(int j=18;j>=0;j--)
		 if(s[i]&(1<<j)) ans=f[ans][j];
		cout<<ans<<' ';
	 }
	return 0;
}
```

---

## 作者：yihang2011 (赞：1)

## [P11894 「LAOI-9」Update](https://www.luogu.com.cn/problem/P11894)

代码很好写，但是想不太好想。

-----

### 30 分暴力：

首先想到打暴力，时间复杂度 $\mathcal{O}(nm)$，可以通过 Subtask 1，得到 30 分，代码如下：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int n, m;
int a[100010];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        for (int i = l; i <= r; i++) {
            a[i] += log2(a[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
```

------

### 50 分暴力+特殊性质：

当然 30 分不能接受，考虑特殊性质 A，可以发现此时 $a_{i}$ 最多只有 100 种情况，用 $c_{i,j}$ 表示 $i$ 在更新 $j$ 次后的值，同时用差分数组 $cnt_{i}$ 来表示第 $i$ 个数需要更新几次。记 $A$ 为 $a_{i}$ 的最大值，则时间复杂度为 $\mathcal{O}(mA)$，可以通过 Subtask 1 和 Subtask 2，得到 50 分，代码如下：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int n, m;
int a[100010];
int c[110][100010];
int cnt[100010];

int main() {
    cin >> n >> m;
    int A = -2e9;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        A = max(A, a[i]);
    }
    if (A <= 100) {
        for (int i = 1; i <= 100; i++) {
            c[i][0] = i;
            for (int j = 1; j <= m; j++) {
                c[i][j] = c[i][j - 1] + log2(c[i][j - 1]); 
            }
        }
        while (m--) {
            int l, r;
            cin >> l >> r;
            cnt[l]++, cnt[r + 1]--; // 差分
        }
        for (int i = 1; i <= n; i++) {
            cnt[i] += cnt[i - 1];
            cout << c[a[i]][cnt[i]] << " ";
        }
        return 0;
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        for (int i = l; i <= r; i++) {
            a[i] += log2(a[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
```

---

### 100 分正解：

根据特殊性质解法考虑正解，对于正整数 $x$ 与 $t$，定义 $\text{change}(x, t)$ 为 $x$ 在更新 $t$ 次后的值。

根据题意，可以得知 $\text{change}(9,4) = 22$，可以发现前三次更新均增加 3，而当 $x = 18 \ge 2^{4}$ 时改为增加 4，记 $\text{up}(y)$ 为第一个大于正整数 $y$ 的 2 的整数次幂，例如 $\text{up}(9) = 1$，$\text{up}(16) = 32$。即正整数 $x$ 会有 $\displaystyle \min(t, \lceil \frac{\text{up}(x) - x}{\lfloor \log_{2} x \rfloor} \rceil)$ 更新增加 $\lfloor \log_{2} x \rfloor$。清楚这一点之后就没什么难的了，差分很好写，详解看[顾z的文章](https://www.luogu.com.cn/article/46kuw69w)吧。时间复杂度 $\mathcal{O}(n \log n)$，代码如下：

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int n, m;
int a[100010];
int c[110][100010];
int cnt[100010];
int P[40]; // 二的整数次幂

int up(int x) {
    int k = upper_bound(P + 1, P + 30 + 1, x) - P; // 这里二分，但是直接枚举也可以
    return P[k];
}

int change(int x, int t) {
    int add = log2(x);
    while (t > 0) {
        int tims = min(t, (int)ceil(1.0 * (up(x) - x) / add));
        x += tims * add;
        t -= tims;
        add++; // 随着x的变大，log x也在变大
    }
    return x;
}

int main() {
    cin >> n >> m;
    P[0] = 1;
    for (int i = 1; i <= 30; i++) {
        P[i] = P[i - 1] * 2;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        cnt[l]++, cnt[r + 1]--; // 差分
    }
    for (int i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];
        cout << change(a[i], cnt[i]) << " ";
    }
    return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

本题是一道思维题，运用普及组算法即可解决。（前置知识：差分）

注意本题数据范围 $n \le 10^5$，又由修改查询性质：区间修改，统一查询。我们不难想到差分维护，询问部分便不会超时。差分结束后，我们如何运用 $\lfloor\log_{2}{a}\rfloor$ 性质实现在对数复杂度内对一个数统一修改呢？

注意到 $\lfloor\log_2 a\rfloor$ 的增长速率是十分缓慢的！也就是说，我们可以采取在一定数值范围内记录此 $\lfloor\log_2 a\rfloor$ 的操作次数！易知此操作是对数复杂度的（类似倍增复杂度）。实现细节见代码。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[200010],cf[200010],sc[200010],p2[100010]={1};
int main()
{cin>>n>>m;
 for(int i=1;i<=n;i++)
  cin>>a[i];
  for(int i=1;i<=62;i++)
  p2[i]=p2[i-1]*2;
 for(int i=1,l,r;i<=m;i++)
 {cin>>l>>r;
  cf[l]++;cf[r+1]--;
 }
 for(int i=1;i<=n;i++)
 sc[i]=sc[i-1]+cf[i];
 for(int i=1;i<=n;i++)
 {long long k=log2(a[i]);
  while(sc[i]>0)
  {if(k==0) break;
   long long cnt=(p2[k+1]-a[i]-1+k)/k;
   if(sc[i]<cnt)
   {a[i]+=sc[i]*k;
    break;
   }
   sc[i]-=cnt;
   a[i]+=cnt*k;
   k++;
  }   
  cout<<a[i]<<' ';
 }
}
```

---

## 作者：fish_love_cat (赞：1)

首先操作数可以差分，那么问题就变成了如何快速对于某个数进行操作。

注意到在相当长的一段时间内增加量不会改变，所以可以对于某个增加量算出其增加次数。

然后你会发现这样时间复杂度就变成 $O(n\log n)$ 了，做完了。

实现细节见代码。

---

坑点：当某个数为 $1$ 时无论怎么操作结果都是 $1$，此时实现不当可能会除零 RE，建议特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],f[100005];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    while(m--){
        int x,y;
        cin>>x>>y;
        f[x]++;
        f[y+1]--;
    }
    for(int i=1;i<=n;i++)f[i]+=f[i-1];
    for(int i=1;i<=n;i++){
        while(f[i]&&a[i]!=1){
            int flc=floor(log2(a[i]));
            int cat=(1<<(flc+1));
            if(ceil((cat-a[i])*1.0/flc)>f[i]){
                a[i]+=f[i]*flc;
                f[i]=0;
            }else{
                f[i]-=ceil((cat-a[i])*1.0/flc);
                a[i]+=ceil((cat-a[i])*1.0/flc)*flc;
            }
        }
        cout<<a[i]<<' ';
    }
    return 0;
}
```

---

## 作者：ni_ju_ge (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11894)
## 思路
容易发现当 $k$ 较大时 $2^{k+1}-2^k$ 是很大的，介于 $2^k\sim 2^{k+1}$ 的 $a$ 需要加很多次 $k$ 才能 $\ge2^{k+1}$。若一次一次加时间复杂度很高，只要一轮加 $t$ 次且保证 $a+t\times k\le 2^{k+1}$ 即可。

可以通过差分数组记录每个 $i$ 对应的 $a_i$ 被操作的次数（设为 $c_i$），然后在加的时候先尝试直接加 $t=c_i$ 次，若超过则使 $t\to \frac{t}{2}$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[114514],n,m,a[114514],t[30],k,l,r;
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	k=1;
	for(int i=2;i<=29;i++) t[i]=t[i-1]+k,k*=2;//记录每个 (2^k)-1 方便计算 log(a_i)
	for(int i=1;i<=m;i++) {
		cin>>l>>r;
		c[l]++,c[r+1]--;
	}
	for(int i=1;i<=n;i++) c[i]=c[i]+c[i-1];
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=c[i];j++) {
			for(int p=1;p<29;p++) {
				if(a[i]<=t[p+1]&&a[i]>t[p]) {
					a[i]+=p-1;//至少加一次
					for(int q=c[i]-j;q>=1;q/=2) {
						if(a[i]+(p-1)*q<t[p+1]&&q<=c[i]-j) {//不超过
							a[i]+=(p-1)*q;
							j+=q;
						}
					}
					break;
				}
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
}
```

---

## 作者：tangzirui1016 (赞：0)

场切了这道题。

想要 AC 此题，你需要会解决下面两个问题：

### 如何快速记录修改次数

注意到这道题是先修改，然后在最后查询。所以我们可以先用一个差分数组来记录，最后再前缀一下，即为修改次数。总时间复杂度为 $O(n)$。

```cpp
while(m--){
  int l,r;
  cin>>l>>r;
  d[l]++,d[r+1]--; //差分
}
for(int i=1;i<=n;i++) d[i]+=d[i-1];
```

### 已知最开始的数 $a_i$ 和修改次数 $k$，如何快速求修改后的数

显然，对于 $\set{x\in \mathbb{N}|2^k\le x < 2^{k+1},k \in \mathbb{N}}$ 中，都有 $\lfloor\log_{2}{x}\rfloor=k$。

运用到上面这个性质，对于正整数 $x$（$2^k\le x < 2^{k+1}$），每一次操作，它一直会以加上 $k$，直到 $x\ge 2^{k+1}$。所以当 $x$ 的增加量变化，需要的代价（操作次数）为：$\lceil\frac{2^{k+1}-x}{k}\rceil$。因此每次给 $x$ 叠加到下一层（下一个 $k$），直到操作次数用完，时间复杂度大致为 $O(\log_2a_i)$。  
```cpp
int getans(int x,int k){
	if(x==1) return 1;
	while(k){
		int _2=log2(x),ne=1<<_2+1;
        //它会先算加法，后算位移
        //这里用到了c++中的log函数
		int dis=ne-x,to=ceil(dis*1.0/_2);
		if(k>=to) k-=to; //可以到下一层
		else to=k,k=0; //不可以到下一层
		x+=_2*to;
	}
	return x;
}
```
### 关于时间复杂度

时间复杂度的瓶颈在修改数上，因此时间复杂度大致为 $O(\sum a_i)$，不会超时。

---

## 作者：_H17_ (赞：0)

## 前言

迟到了 $2$ 小时，被诈骗想错方向了。

好在后来实力压制，想到正解了。

## 题目分析

错误想法：鉴于每次增加数量不多，批量区间加，用珂朵莉数维护相同相加的段。我就被错误引导了。

注意到操作先后没有影响，而且是离线的，考虑差分记录每个数要操作几次。

考虑递推：$f_{i,j}$ 表示 $i$ 变化 $j$ 次的答案。这个数是 $n^2\log n$ 级别的（变化量是 $\log n$ 左右的）。

考虑倍增优化一下，就做完了。

时间复杂度 $O(n\log^2 n)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
#define lowbit(x) ((x)&(-(x)))
using namespace std;
constexpr int N=100003,T=3100000;
int n,q,a[N],log2_[T],diff[N],opt[N],f[T][18];
int qp(int b){
    int a=2,ret=1;
    while(b){
        if(b&1)
            ret*=a;
        b>>=1,a*=a;
    }
    return ret;
}
signed main(){
    log2_[1]=0;
    for(int i=2;i<T;i++)
        log2_[i]=log2_[i/2]+1;
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1,l,r;i<=q;i++){
        cin>>l>>r;
        diff[l]++,diff[r+1]--;
    }
    for(int i=1;i<=n;i++)
        opt[i]=opt[i-1]+diff[i];
    for(int i=1;i<T;i++)
        f[i][0]=i+log2_[i];
    for(int j=1,curmax=1500000,nmax;j<=17;j++){
        nmax=curmax;
        for(int i=1;i<=curmax;i++){
            f[i][j]=f[f[i][j-1]][j-1];
            nmax=max(nmax,f[i][j]);
        }
        curmax=nmax;
    }
    for(int i=1;i<=n;i++){
        while(opt[i]){
            int val=log2_[opt[i]];
            a[i]=f[a[i]][val];
            opt[i]-=qp(val);
        }
    }
    for(int i=1;i<=n;i++)
        cout<<a[i]<<' ';
    return 0;
}
```

---

## 作者：SecuritySetting (赞：0)

题意很简单了就不在赘述。

思路：

最先想到的肯定是暴力，一次一次操作过去，但是肯定会超时。

考虑优化两个地方：
1. 一次处理一个数，即记录每一个数的操作次数；
2. 快速计算操作后的答案，即不要一次次模拟，否则和暴力基本没区别。

首先，考虑怎么记录一个数的操作次数。作者用的是线段树（其实用差分就可以了，但是作者最近学线段树学得太过于热情了），再求出每一个数的操作次数。

其次，怎么计算操作后的答案呢？我们找规律可以发现，一定范围内的 $a_i$ 的 $\lfloor \log_2(a_i) \rfloor$ 是相同的，设 $x=\lfloor \log_2(a_i) \rfloor$，则 $2^x$ 到 $2^{x+1}-1$ 的之间的 $a_i$ 的 $\log_2(a_i)$ 的值是相同的。这也不难证明。

特殊的，$\lfloor \log_2(1) \rfloor = 0$，所以无论怎么操作都不会变，需要特殊处理。

既然有了结论，那么就能运用结论求答案了，现在每次操作差不多相当于原来的好几次甚至更多操作，快了不少。

最后，就能通过这道题了。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std; 
const int N = 1e5+5; 
int n, m, a[N]; 
int ans[N*4], tag[N*4]; 
inline int ls(int x){
	return x << 1; 
}
inline int rs(int x){
	return x << 1 | 1; 
}
inline void push_up(int x){
	ans[x] = ans[ls(x)] + ans[rs(x)]; 
}
inline void f(int x, int l, int r, int k){
	tag[x] += k; 
	ans[x] +=(r - l + 1) * k; 
}
inline void push_down(int x, int l, int r){
	int mid =(l + r) >> 1; 
	f(ls(x), l, mid, tag[x]); 
	f(rs(x), mid + 1, r, tag[x]); 
	tag[x] = 0; 
}
inline void update(int l, int r, int nowl, int nowr, int x, int k){
	if(nowl >= l && nowr <= r){
		ans[x] += k *(nowr - nowl + 1); 
		tag[x] += k; 
		return ; 
	}
	push_down(x, nowl, nowr); 
	int mid =(nowl + nowr) >> 1; 
	if(l <= mid){
		update(l, r, nowl, mid, ls(x), k); 
	}
	if(r > mid){
		update(l, r, mid + 1, nowr, rs(x), k); 
	}
	push_up(x); 
}
int query(int l, int r, int nowl, int nowr, int x){
	if(nowl >= l && nowr <= r){
		return ans[x]; 
	}
	int res = 0; 
	push_down(x, nowl, nowr); 
	int mid =(nowl + nowr) >> 1; 
	if(l <= mid){
		res += query(l, r, nowl, mid, ls(x)); 
	}
	if(r > mid){
		res += query(l, r, mid + 1, nowr, rs(x)); 
	}
	return res; 
}//以上为线段树板子
int lg[N*100];//lg[i]为log2(i),数组开大一点是怕a[i]操作次数太多，作者并没仔细算
int Pow(int x, int y){
	int res = 1;
	while(y){
		if(y & 1){
			res *= x;
		}
		y >>= 1;
		x *= x; 
	}
	return res;
}//快速幂
signed main(){
	scanf("%lld%lld", &n, &m); 
	for(int i = 1; i <= n; i++){
		scanf("%lld", &a[i]); 
	}
	for(int i = 2; i <= 1e7; i++){//预处理lg[i]
		lg[i] = lg[i >> 1] + 1;
	}
	for(int i = 1; i <= m; i++){
		int l, r; 
		scanf("%lld%lld", &l, &r); 
		update(l, r, 1, n, 1, 1); //线段树
	}
	for(int i = 1; i <= n; i++){
		if(a[i] == 1){//a[i]=1特殊处理
			printf("1 ");
			continue;
		}
		int cnt = query(i, i, 1, n, 1); //a[i]的操作次数
		while(1){
			int lgx = lg[a[i]];//log2(a[i])
			int x = Pow(2, lgx + 1);//求出右端点
			int y = x - a[i];//求出与右端点的距离
			int ccnt = y / lgx;//求出可以操作几次，要向下取整，具体原因结合下面
			if(ccnt <= cnt){//操作次数小于等于剩余总操作次数
				cnt -= ccnt;
				a[i] += ccnt * lgx;//直接加
				if(cnt == 0){//操作次数等于剩余总操作次数
					break;//结束
				}
				if(lgx * ccnt == y){//操作次数后刚好到右端点不进行下面的操作
					continue;
				}
				cnt--;//没到右端点可以再操作一次
				a[i] += lgx;
			}
			else{操作次数大于剩余总操作次数
				a[i] += cnt * lgx;
				break;
			}
		}
		printf("%lld ", a[i]);
	}
	return 0; 
}
```
这应该是这道题的最繁解了。

---

## 作者：jubingkun (赞：0)

## 分析

区间修改+单点查询，不难想到用线段树。

用 $lazy$ 标记来记录修改的次数，其余与线段树模板大致相同。

但难点在于已知一个点的操作次数，如何快速求出结果。

不妨设要查询的点的数值为 $x$，那么总能找到一个正整数 $k$，使得 $2^{k-1}\leq x < 2^k$，那么从 $x$ 到越过 $2^k$ 一共所需的操作次数为 $\Big\lceil\dfrac{2^k-x}{\lfloor \log_2x\rfloor}\Big\rceil$，$lazy$ 够的话直接减掉并更新 $x$，然后对新 $x$ 继续如上操作；不够就让 $x$ 加上 $lazy \times \lfloor{\log_2x}\rfloor$，然后退出循环。

时间复杂度 $O(n\log^2n)$。

## Code
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
#define ls id << 1
#define rs id << 1 | 1
const int MAXN = 1e5 + 5;
int n, m; 
int a[MAXN];
struct segment_tree{
    int l, r;
    int lazy;
}t[MAXN << 2];
void push_down(int id) {
    if (t[id].lazy) {
        t[ls].lazy += t[id].lazy;
        t[rs].lazy += t[id].lazy;
        t[id].lazy = 0;
    }
}
void build(int id, int l, int r) {
    t[id].l = l, t[id].r = r, t[id].lazy = 0;
    if (l == r) return ;
    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
  //push_up(id);
}
void update(int id, int l, int r) {
    if (t[id].l == l && t[id].r == r) {
        t[id].lazy += 1;
        return ;
    }
    push_down(id);
    if (l >= t[rs].l) {
        update(rs, l, r);
    } else if (r <= t[ls].r) {
        update(ls, l, r);
    } else {
        update(ls, l, t[ls].r);
        update(rs, t[rs].l, r);
    }
}
int getnum(int id, int x) {
    if (t[id].l ==x && t[id].r == x) {
        while(t[id].lazy > 0) {
            double Log = log2(a[x]);
            int cishu = max((int)ceil(((int)pow(2, (int)ceil(Log)) - a[x]) / floor(Log)), 1);
            //当x恰好为2的整数幂时，为防止cishu为0，故要与1取最大值
            if (t[id].lazy >= cishu) {
                t[id].lazy -= cishu;
                a[x] += cishu * floor(Log);
            } else {
                a[x] += t[id].lazy * floor(Log);
                t[id].lazy = 0;
            }
        }
        return a[x];
    }
    push_down(id);
    if (x >= t[ls].l && x <= t[ls].r)   return getnum(ls, x);
    else    return getnum(rs, x);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        update(1, l, r);
    }
    for (int i = 1; i <= n; i++) {
        cout << getnum(1, i) << ' ';
    }
    return 0;
}
```

---

## 作者：Little_Fox_Fairy (赞：0)

同学给我说这个东西是 DS 题然后过来看，~~结果被诈骗了。~~

讲一下我的思路。

由于区间加单次查，所以使用差分记录一下每个数被加了多少次。

注意到这个加 $ \lfloor \log_2a_i \rfloor $ 相同的值会加多次，然后直到这个值大于等于 $ 2^{\lfloor \log_2a_i \rfloor} $ 的时候增加的值会加一。然后模拟这个过程即可。

Code：

```cpp
#include<bits/stdc++.h>
#define int long long 
#define pii pair<int,int>
#define pb push_back 
#define eb emplace_back
#define rep(i,a,b) for (int i=(a);i<=(b);i++) 
#define Rep(i,a,b) for (int i=(a);i>=(b);i--)
#define grep(i,a,b) for (auto i : a[b]) 
using namespace std;
const int N=2e5+10;

int n,m,e[N];
int d[N];
string s;
inline int calc(int x,int cnt) {
    while (cnt>0) {
        int delta=floor(log2(x));
        int up=(1<<(delta+1));
        int tim=ceil(1.0*(up-x)/delta);
        cnt-=tim;
        if (cnt<0) {
            cnt+=tim;
            x+=delta*cnt;
            break;
        }
        x+=delta*tim;
    }
    return x;
}
signed main() {
	cin>>n>>m;
    rep(i,1,n) cin>>e[i];
    rep(i,1,m) {
        int l,r;cin>>l>>r;
        d[l]++,d[r+1]--;
    }
    int cnt=0;
    rep(i,1,n) {
        cnt+=d[i];
        cout<<calc(e[i],cnt)<<" ";
    }
	return (0-0);
}
```

---

