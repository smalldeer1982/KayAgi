# [ARC023D] GCD区間

## 题目描述

## 题意翻译

给出一个长度为 $n$ $(1<=n<=10^{5})$ 的序列和 $m$ $(1<=m<=10^{5})$ 个询问。对于每个询问，输入 $x$ $(1<=x<=10^{9})$，输出满足 $gcd(a_l,a_{l+1},...,a_r)=x$ 的 $(i,j)$ 的对数。

## 样例 #1

### 输入

```
3 4
1
2
4
1
2
3
4```

### 输出

```
3
2
0
1```

## 样例 #2

### 输入

```
6 7
12
6
4
3
2
1
1
2
3
4
6
12
8```

### 输出

```
13
3
1
1
2
1
0```

## 样例 #3

### 输入

```
5 8
4
6
42
28
41
1
2
4
6
7
14
14
41```

### 输出

```
4
4
1
2
0
1
1
1```

# 题解

## 作者：BetterGodPig (赞：5)

### 本题解之前已过审， $\text{update on 2023.11.6}$ 修改了部分笔误

[双倍经验](https://www.luogu.com.cn/problem/CF475D)。

首先容易想到利用 `map` 模拟桶进行计数，然后 $O(1)$ 回答。

那么瓶颈转到预处理，首先是一个很常见的技巧，使用 $\text{ST}$ 表预处理区间最大公约数。然后对于最大公约数来说，他肯定是单调不升的，那么就可以枚举左端点，使用二分找到最大公约数相同的区间右端点（找有序数列中等于某个数的最后一个），动态处理到每一个右端点，这也是一个常用的优化 $O(n^2)$ 暴力的手段。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5+5;
int n,q;
int a[maxn];
int st[maxn][26];
int lg[maxn];
int Gcd(int a,int b){
	if(!a || !b) return a|b;
	register int az = __builtin_ctz(a),bz = __builtin_ctz(b),z = az>bz?bz:az,diff;
	b>>=bz;
	while(a){
		a>>=az;
		diff = b-a;
		az = __builtin_ctz(diff);
		if(a<b) b=a;
		a = diff<0?-diff:diff;
	}
	return b<<z;
}
void init(){
	lg[1] = 0;
	for(int i(2);i <= n;++i){
		lg[i] = lg[i>>1]+1;
	}
	for(int i(1);i <= n;++i){
		st[i][0] = a[i];
	}
	for(int j(1);j <= lg[n];++j){
		for(int i(1);i+(1<<j)-1 <= n;++i){
			st[i][j] = Gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}
int query(int l,int r){
	int s = lg[r-l+1];
	return Gcd(st[l][s],st[r-(1<<s)+1][s]);
}
unordered_map<int,int> mp;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>q;
	for(int i(1);i <= n;++i){
		cin>>a[i];
	}
	init(); 
	for(int i(1);i <= n;++i){
		int pos = i;
		int now = st[i][0];
		while(1){
			int l = pos,r = n+1;
			while(l < r){
				int mid = (l+r)>>1;
				if(query(i,mid) == now){
					l = mid+1;
				}else r = mid;
			}
			mp[now] += r-pos;
			pos = r;
			if(pos == n+1) break;
			now = Gcd(now,a[r]);
		}
	}
	while(q--){
		int x;
		cin>>x;
		cout<<mp[x]<<'\n';
	}
	return 0;
}
```


---

## 作者：hopelessness (赞：2)

Update on 2023.11.6 改了一堆东西

Update on 2023.11.8 改了一堆东西

Update on 2023.11.9 再也不加空格啦

Update on 2023.11.9 怎么这么多空格

Update on 2023.11.9 怎么又少空格啦

Update on 2023.11.10 滥用代码块

~~好吧，这道题暴力卡不过去，只能写正解了~~

首先，对于 $\gcd$，我们知道 Ta 的粗劣复杂度是 $\log$ 的，（[严谨复杂度请看这里](https://zhuanlan.zhihu.com/p/344094740#:~:text=%E5%BC%95%E7%90%86%20%EF%BC%9A%E5%AF%B9%E4%B8%A4%E6%95%B0%20a%2Cb%20%E7%94%A8%E8%BE%97%E8%BD%AC%E7%9B%B8%E9%99%A4%E6%B1%82%20gcd%20%E7%9A%84%E5%A4%8D%E6%9D%82%E5%BA%A6%E6%98%AF%20Theta%20%281%29%2BO,%281%29%2BO%20%28logdfrac%20%7Bmin%20%28a%2Cb%29%7D%20%7Bgcd%20%28a%2Cb%29%7D%29%20%EF%BC%8C%E5%BE%97%E8%AF%81%E3%80%82%20%E4%BA%8C%E3%80%81%E8%AF%81%E6%98%8E)），所以，我们可以先用 ST 表预处理出区间 $\gcd$（[不会的看这里](https://oi-wiki.org/ds/sparse-table/)）。

由于每个区间的 $\gcd$ 是单调不升的，所以我们可以二分处理出每一个值出现的次数。

对了，记得开 long long，还有 AtCoder 不支持 C++14，所以不可以用 register。

Code：

```cpp
/*
    by hopelessness
*/
#include<bits/stdc++.h>

#define il inline
#define MAXN 1010101
#define LL long long
// #define ri register int
#define random(a,b) ((a)+rand()%((b)-(a)+1))

using namespace std;

unordered_map<int,LL>cnt;

int a[MAXN];
int Log[MAXN];
int ST[MAXN][20];

int n,m,tot,x;

template<typename T>il void read(T &x){
    char c=getchar();
    x=0;
    int f=0;
    for(;!isdigit(c);c=getchar()) f|=(c=='-');
    for(;isdigit(c);c=getchar()) x=((x<<3)+(x<<1)+(c^48));
    x=f?-x:x;
}
template<typename T>il void write(T x){
    if(x<0) x=-x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10^48);
}
il int Query(int l,int r){
    int x=Log[r-l+1];
    return __gcd(ST[l][x],ST[r-(1<<x)+1][x]);
}
il void Init(){
    for(int i=2;i<=n;i=-~i) Log[i]=Log[i>>1]+1;
    for(int j=1;j<17;j=-~j){
        for(int i=1;i<=n;i=-~i) ST[i][j]=__gcd(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
    }
    for(int i=1;i<=n;i=-~i){
        int pos=i,val=a[i];
        while(1){
            int l=pos,r=n+1;
            while(l<r-1){
                int mid=(l+r)>>1;
                if(Query(i,mid)!=val) r=mid;
                else l=mid;
            }
            cnt[val]+=r-pos;
            pos=r;
            val=Query(i,r);
            if(r==n+1) break;
        }
    }
}

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    read(n),read(m);
    for(int i=1;i<=n;i=-~i) read(a[i]),ST[i][0]=a[i];
    Init();
    while(m--) read(x),write(cnt[x]),putchar('\n');
    return 0;
}
```

完结，撒花

---

## 作者：teen_Eden (赞：2)

# [ARC023D] GCD区間

## 题解

对于这道题，我们很容易想到可以先预处理，将所有区间的答案记录下来，这样在之后的询问中我们就可以每次 $O(1)$ 输出了。

那么怎么预处理答案呢？

### 1、暴力优化

有一个很显然的优化暴力写法，就是在去枚举每个区间 $[i,j]$，如果当前的 $\gcd$ 已经变为 $1$ 说明之后的 $\gcd$ 肯定都为 $1$，那么我们直接将 $\gcd$ 为 $1$ 的答案加上剩下的区间长度就可以了，这个做法可以过 $8$ 个点。

code：

```c++
#include<bits/stdc++.h>
#define MAXN 100010
#define int long long
using namespace std;

int n,m,GCD;
int a[MAXN],x;
map<int,int>ans;
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
	{
		GCD=a[i];
		ans[GCD]++;
		for(int j=i+1;j<=n;j++)
		{
			GCD=__gcd(GCD,a[j]);
			ans[GCD]++;
			if(GCD==1) 
			{
		    	ans[1]+=n-j;
				break;	
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%lld",&x);
		printf("%lld\n",ans[x]);
	}
	return 0;
}
```

### 2、线段树 + 二分

那么接下来考虑优化的问题，我们先来看个另外的序列 $32,24,24,12,12,8,8,4$，以 $i=1$ 开头的区间 $\gcd$ 分别为 $32,12,12,12,12,4,4,4$，我们发现序列中有很多 $\gcd$ 是一样的，特别是在数据更大时，为什么呢？

回顾一下 $\gcd$ 的辗转相除法，我们可以发现 $\gcd$ 每次至少都是减半的，也就是说 $\gcd$ 从一个值 $n$ 变为 $1$ 的过程中，只会有最多 $O(\log n)$ 次变化，那么对应到区间上来说就是只会有 $O(\log n)$ 个节点，节点与节点之间的 $\gcd$ 都是一样的。拿之前举的序列来说，它的所有节点编号就是 $1$，$2$，$6$。那么问题就变成了快速求区间 $\gcd$ 和找到节点了。节点非常好找，直接二分就可以了，单次效率是 $O(\log n)$ 的。快速求区间 $\gcd$ 开始我用的是线段树，但交上去还是只过了 $8$ 个点。

code：

```c++
#include<bits/stdc++.h>
#define MAXN 200010
#define int long long
using namespace std;
template <typename T> inline void read(T &x)
{
	char c=getchar();x=0;int f=0;
	for(;!isdigit(c);c=getchar()) f|=(c=='-');
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	x=f?-x:x;
}
int t[MAXN*4],k;
int n,m,opt;
int a[MAXN],x,y;

int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void push_up(int x) {t[x]=__gcd(t[ls(x)],t[rs(x)]);}

void build(int x,int l,int r)
{
	if(l==r) {t[x]=a[l];return;}
	int mid=(l+r)>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	push_up(x);
}
int query(int x,int l,int r,int nl,int nr)
{
	int flag=0;
	if(nl<=l&&nr>=r) return t[x];
	int mid=(l+r)>>1,ret;
	if(mid>=nl) ret=query(ls(x),l,mid,nl,nr),flag=1;
	if(mid<nr) 
	{
		if(flag) ret=__gcd(ret,query(rs(x),mid+1,r,nl,nr));
		else ret=query(rs(x),mid+1,r,nl,nr);
	}
    return ret;
}

int las,GCD,pos;
map<int,int>ans;

int find(int i,int l,int r)
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(query(1,1,n,i,mid)!=GCD) return find(i,l,mid);
	else return find(i,mid+1,r); 
}
signed main()
{
    read(n);read(m);
    for(int i=1;i<=n;i++) read(a[i]);
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
    	las=i;pos=i;GCD=a[i];
        while(pos<n)
        {
        	las=pos;
        	pos=find(i,pos+1,n);
        	ans[GCD]+=pos-las;
        	GCD=__gcd(GCD,a[pos]);
		}
		ans[GCD]+=n-pos+1;
	}
    for(int i=1;i<=m;i++)
    {
        read(x);
        printf("%lld\n",ans[x]);
	}
	return 0;
} 

```

### 3、ST 表 + 二分 

线段树常数有点大，不过没关系，直接把线段树换成 ST 表，最后的复杂度是 $O(n \log(a)\log(n))$($a$ 指的是值的大小，$n$ 指的是区间范围)。

code:

```c++
#include<bits/stdc++.h>
#define MAXN 1000010
#define int long long
using namespace std;
template <typename T> inline void read(T &x)
{
	char c=getchar();x=0;int f=0;
	for(;!isdigit(c);c=getchar()) f|=(c=='-');
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	x=f?-x:x;
}
int k,st[MAXN][20];
int n,m,opt;
int x,y;
void Get_ST()
{
	for(int j=1;j<=19;j++)
	{
		for(int i=1;i<=n;i++)
		{
			st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}
int mlog[MAXN];
void Get_log(){for(int i=2;i<=n;i++) mlog[i]=mlog[i>>1]+1;}
int query(int l,int r)
{
	int t=mlog[r-l+1];
	return __gcd(st[l][t],st[r-(1<<t)+1][t]);
}
int las,GCD,pos;
map<int,int>ans;

int find(int i,int l,int r)
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(query(i,mid)!=GCD) return find(i,l,mid);
	else return find(i,mid+1,r); 
}
signed main()
{
    read(n);read(m);
    for(int i=1;i<=n;i++) read(st[i][0]);
    Get_ST();Get_log();
    for(int i=1;i<=n;i++)
    {
    	las=i;pos=i;GCD=st[i][0];
        while(pos<n)
        {
        	las=pos;
        	pos=find(i,pos+1,n);
        	ans[GCD]+=pos-las;
        	GCD=__gcd(GCD,st[pos][0]);
		}
		ans[GCD]+=n-pos+1;
	}
    for(int i=1;i<=m;i++)
    {
        read(x);
        printf("%lld\n",ans[x]);
	}
	return 0;
} 
```

$ps:$ 本蒟蒻的第一篇题解，若有写的不对的地方请私信，谢谢。



---

## 作者：pinewood (赞：2)

观察题意，可以每一次确定左端点然后二分右端点。具体就是找到使序列 $\gcd$ 改变的第一个位置，这样可以直接找到对于每一个答案值的长度。具体可以直接用 map 离散化，直接对对应值统计答案就可以了。但是我们需要快速求出区间的 $\gcd$。观察到题目要求是静态的，所以直接用 st 表。最终复杂度为 $O(n\log n\log m)$。其中 $m$ 为值域。
```cpp
#include<bits/stdc++.h>
using namespace std;
int gcdd[100010][20],n,m,a[100010];
void stpre(){//st表预处理
	for(int i=1;i<=n;i++)gcdd[i][0]=a[i];
	int k=log(n)/log(2)+1;
	for(int j=1;j<k;j++)
		for(int i=1;i<=n-(1<<j)+1;i++)
			gcdd[i][j]=__gcd(gcdd[i][j-1],gcdd[i+(1<<(j-1))][j-1]);
}
int stask(int l,int r){//st表答案查询
	int k=log(r-l+1)/log(2);
	return __gcd(gcdd[l][k],gcdd[r-(1<<k)+1][k]);
}
unordered_map<int,long long>ans;//离散化记录答案
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	stpre();
	for(int i=1;i<=n;i++){//固定左端点二分
		int now=a[i];
		int h=i;//当前gcd值下的左端点
		while(true){
			int head=h;
			int tail=n+1;//二分的头尾
			while(head<tail-1){
				int mid=(head+tail)/2;
				if(stask(i,mid)!=now)tail=mid;
				else head=mid;
			}
			ans[now]+=1ll*(tail-h);//统计答案
			h=tail;
			now=stask(i,tail);//更新gcd值
			if(tail==n+1)break;//没有更新值直接退出
		}
	}
	while(m--){
		int x;
		scanf("%d",&x);
		printf("%lld\n",ans[x]);
	}
}
```


---

## 作者：HowToCarry (赞：1)

[AT_arc023_4](https://www.luogu.com.cn/problem/AT_arc023_4)

### 先考虑暴力
显然对每一次询问，枚举每一个左端点向右统计，单次 $O(n^2)$，总复杂度 $O(m\times n^2)$。
### 优化
不难发现每次统计时的瓶颈在于枚举时有大量多余的位置，于是我们考虑直接预处理的时候直接把值存起来，即可 $O(1)$ 询问。我们来想想求一个区间的 $\gcd$ 的性质，随便举个例子：
```
8 16 4 28 36 8 2 14 3 34 45
```
我们以第一个数为左端点，那么到每一个右端点的区间的 $\gcd$ 为:
```
8 8 4 4 4 4 2 2 1 1 1
```
容易发现这样的相同的 $\gcd$ 是连续的，且每次 $\gcd$ 变小至少小二分之一（显然，因为 $2$ 是最小的质因数），所以我们的 $\gcd$ 最多改变 $\log{V}$ 次就变为 $1$ 了，且因为 $\gcd$ 是单调不增的，所以我们考虑对每一个左端点，二分得出每个 $\gcd$ 值可到达的右端点，二分的效率为 $O(\log{n})$，为了快速求出一个区间的 $\gcd$，我们可以采用 ST 表做到近似 $O(1)$ 的效率，那么总效率为 $O(n\log{n}\log{V})$。

### 注意
记得开 long long！
### Code
```cpp
#include<bits/stdc++.h>
#define il inline
#define ll long long
#define Angry 0
using namespace std;
const int N=100005;
int n,m,p,len;
int f[N][30];
int a[N];
unordered_map<int,ll>mp;
il int gcd(int x,int y){// 二进制gcd
	if(!x||!y) return x|y;
	int az=__builtin_ctz(x),bz=__builtin_ctz(y),z=az>bz?bz:az,df;
	y>>=bz;
	while(x){
		x>>=az;
		df=y-x;
		az=__builtin_ctz(df);
		if(x<y) y=x;
		x=df<0?-df:df;
	}
	return y<<z;
}
il int query(int l,int r){
	len=log(r-l+1)/log(2);
	return gcd(f[l][len],f[r-(1<<len)+1][len]);
}
il void solve(int u){//二分
	int val=a[u],l,r,mid,pos=u;
	l=r=0;
	while(r!=n){
		l=pos,r=n;
		while(l<r){//二分求出每一个 val 所到达的最右边
			mid=l+r+1>>1;
			if(query(u,mid)!=val) r=mid-1;
			else l=mid;
		}
		mp[val]+=r-pos+1;// 需要用 map 存
		pos=r+1;
		val=query(u,r+1);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i][0]=a[i];
	}
	len=log(n)/log(2)+1;
	for(int j=1;j<len;j++){// ST表预处理
		for(int i=1;i<=n-(1<<j)+1;i++){
			f[i][j]=gcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
	for(int i=1;i<=n;++i) solve(i);
	while(m--){
		cin>>p;
		cout<<mp[p]<<'\n';
	}
	return Angry;
}
```


---

## 作者：_exist (赞：1)

# [ARC023D] GCD区間

首先很容易想到 $O(n^2)$ 的暴力写法，固定左端点 $l$，枚举右端点 $r$，然后用 map 存储每一个区间的 $\gcd$ 的数量即可，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5+9;
int a[N],n,m;
unordered_map<int,int>s;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		int res=0;
		for(int j=i;j<=n;j++){
			res=__gcd(res,a[j]);
			s[res]++;
		}
	}
	while(m--){
		int x;cin>>x;
		cout<<s[x]<<'\n';
	}
	return 0;
}

```

设值域为 $V$，仔细想想就会发现对于一个区间而言，每次向后延伸的话，$\gcd$ 是不可能上升的，并且 $\gcd$ 也只会变化 $\log V$ 次，那么这样就可以直接考虑二分 $\gcd$ 的变化端点并统计答案即可，并且区间 $\gcd$ 可以用 ST 表或线段树维护，时间复杂度 $O(n\log^2 V\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5+9;
int n,m,a[N][35],f[N*4],mlog[N],stk[N],t[N];
unordered_map<int,int>s;
void ST_init(){
	for(int j=1;j<=25;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			a[i][j]=__gcd(a[i][j-1],a[i+(1<<(j-1))][j-1]);
		}
	}
}
inline int query(int x,int y){
	int h=mlog[y-x+1];
	return __gcd(a[x][h],a[y-(1<<h)+1][h]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i][0];
	for(int i=2;i<=n;i++)mlog[i]=mlog[i>>1]+1; 
	ST_init();
	for(int i=1;i<=n;i++){
		int pos=i,l,r,las=a[i][0],p=0;
		stk[++p]=i;
		t[p]=a[i][0];
		while(1){
			int res;
			l=pos;r=n;
			while(l<r){
				int mid=(l+r)>>1;
				res=query(i,mid);
				if(res>=las)l=mid+1;
				else r=mid;
			}
			int kkk=query(i,l);
			if(kkk==las)break;
			stk[++p]=l;
			t[p]=query(i,l);
			pos=stk[p],las=t[p];
		}
		stk[++p]=n+1;
		for(int i=2;i<=p;i++){
			s[t[i-1]]+=stk[i]-stk[i-1];
		}
	}
	while(m--){
		int x;cin>>x;
		cout<<s[x]<<"\n";
	}
	return 0;
}

```



---

## 作者：RedLycoris (赞：1)

[link](https://www.luogu.com.cn/problem/AT_arc023_4)

题目大意：

给出一个长度为 $n$ $(1 \le n \le 10^{5})$ 的序列和 $m$ $(1 \le m \le 10^{5})$ 个询问。对于每个询问，输入 $x$ $(1 \le x \le 10^{9})$，输出满足 $gcd(a_l,a_{l+1},...,a_r)=x$ 的 $(l,r)$ 的对数。

题解：

考虑我们固定一个起点 $l$，从 $l$ 到 $n$ 扩张区间的右端点 $r$，考虑区间 gcd  的变化。

显然，这个 gcd 最多只会变化 $\log A$ 次（$A$ 是值域），因为每次变化必然是砍掉一个（或一些）质因数，而质因数的个数是 $\log A$ 级别的。

所以我们可以考虑枚举开头，每次二分出下一个变化点的位置，每个开头二分 $\log A$次，就可以求出所有可能的 gcd 的值并得到出现次数了。

注意用 $ST$ 表预处理一下 gcd，复杂度就可以做到 $n \log A \log n$ 了。

---

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mxn=1e6+6;
int st[mxn][20],n,q,a[mxn],lg[mxn];
inline int ask(int l,int r){
	int t=lg[r-l+1];
	return __gcd(st[l][t],st[r-(1<<t)+1][t]);
}
map<int,ll>cnt;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;++i)cin>>a[i],st[i][0]=a[i];
	for(int i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
	for(int j=1;j<20;++j)for(int i=1;i<=n;++i)st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	for(int i=1;i<=n;++i){
		int cur=i,val=a[i];
		while(1){
			int lo=cur,hi=n+1,md;
			for(;lo<hi-1;){
				md=lo+hi>>1;
				if(ask(i,md)!=val)hi=md;
				else lo=md;
			}
			cnt[val]+=hi-cur;
			cur=hi;val=ask(i,hi);
			if(hi==n+1)break;
		}
	}
	for(;q--;){
		int x;cin>>x;
		cout<<cnt[x]<<'\n';
	}
}
```

---

## 作者：small_john (赞：0)

## 思路

众所周知，对于两个数 $x,y$，满足 $\gcd(x,y)$ 要么等于 $x$ 中的一个，要么小于等于 $\frac x 2$。

证明是简单的，我们分情况讨论：

1. $x$ 是 $y$ 的倍数：$\gcd(x,y)=x$；
2. 否则，$\gcd(x,y)$ 是 $x$ 的因数，而 $x$ 的因数最大也是 $\frac x 2$。

所以，我们去维护每个 $i$ 为起点的区间，每一次找一段最大公约数相同的区间，这样的区间最多 $\log n$ 个。

如何去找一段最大公约数相同的区间呢？

考虑用 ST 表，这样就能 $O(1)$ 求出任意一段区间的最大公约数，然后二分这段区间的长度即可。

最后，把二分出的长度加入对应的最大公约数的贡献（具体可以用 map），输出即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 1e5+5;
int n,m,a[N],st[N][18];
unordered_map<int,long long> mp;
int ask(int l,int r)
{
	int k = log2(r-l+1);
	return __gcd(st[l][k],st[r-(1<<k)+1][k]);
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m);
	for(int i = 1;i<=n;i++)
		read(a[i]),st[i][0] = a[i];
	for(int j = 1;j<=17;j++)
		for(int i = 1;i+(1<<j)-1<=n;i++)
			st[i][j] = __gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	for(int i = 1;i<=n;i++)
	{
		int p = i,val = a[i];
		while(p<=n)
		{
			int l = 0,r = n-p,res = 0;
			while(l<=r)
			{
				int mid = (l+r)/2;
				if(__gcd(val,ask(p,p+mid))==val) l = mid+1,res = mid;
				else r = mid-1;
			}
			mp[val]+=res+1;
			p+=res+1;
			val = __gcd(val,a[p]); 
		}
	}
	while(m--) writen(mp[read<int>()]);
	return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# [ARC023D] GCD区間

upd on 2024.1.26：修正了 ST 表的时间复杂度分析。

一道数据结构维护 $\gcd$ 的好题。

---

首先，大家应该都能想到一种大暴力：枚举左右端点 $l, r$, 暴力计算 $\gcd$ 然后开个哈希表记录每个 $\gcd$ 出现了几次。

复杂度 $O(n^2\log{n})$ 预处理，$O(1)$ 查询。

---

很明显，$O(n^2\log{n})$ 压根卡不过去。

但是这道题涉及到了区间求 $\gcd$，可以考虑用数据结构维护。

所以我们简单用一个 ST 表来维护 $\gcd$，成功做到 $O(n^2)$ 预处理，$O(\log{n})$ 查询。（ST 表中 $\gcd$ 操作的复杂度为 $O(\log{n})$）

```c++
template<typename Tp, size_t siz>
struct ST
{
    Tp _con[siz][21];   
  
    Tp& operator[](int i) {return _con[i][0];}

    void pre()
    {
        for(int i=1;i<=20;i++)
            for(int j=1;j+(1<<i)-1<=siz;j++)
                _con[j][i]=gcd(_con[j][i-1], _con[j+(1<<(i-1))][i-1]);
    }

    Tp query(int l, int r)
    {
        if(l>r) return 0;
        int len=lgs[r-l+1];
        return gcd(_con[l][len], _con[r-(1<<len)+1][len]);
    }
};
```

---

~~但是还是卡不过去啊~~

考虑这样一个序列：`12 8 4 6 4 3` 。

当 $l=1$ 时，区间 $[l,r]$ 内的 $\gcd$ 为（ $r$ 从 $1$ 到 $n$ ）：`12 4 4 2 2 1` 。

我们发现该题的 $\gcd$ 有一条重要性质：

- $l$ 一定时，$\gcd$ 单调递减。

所以我们想到二分答案。

二分一段相同 $\gcd$ 的右端点，直接统计答案。
时间复杂度 $O(n\log{n})$。

## Code

```c++
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb __gnu_pbds
using namespace std;

template< typename T >inline void read(T &x)
{
	char c=getchar();x=0;int f=0;
	for(;!isdigit(c);c=getchar()) f|=(c=='-');
	for(;isdigit(c);c=getchar()) x=((x<<3)+(x<<1)+(c^48));
	x=f?-x:x;
}

template< typename T >inline void write(T x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
}

template< typename T,typename ... Args > 
inline void read(T &_x, Args &... args) 
{read(_x), read(args...);}

template< typename T,typename ... Args > 
inline void write(T _x, Args ... args) 
{ write(_x), write(args...);}

//快读快写

pb::gp_hash_table<int,long long> gcdct; //用一个哈希表存储 gcd 为某值的对数

inline int gcd(int a,int b)
{
	if(!(a&&b)) return a|b;
	int alow=__builtin_ctzll(a), blow=__builtin_ctzll(b);
	int low=(alow<blow)?alow:blow;
	int c=0;
	b>>=blow;
	while(a)
    {
		a>>=alow;
		c=b-a;
		alow=__builtin_ctzll(c);
		if(a<b) b=a;
		a=(c<0)?-c:c;
	}
	return b<<low;
} // Stein gcd 更相减损法求 gcd

int lgs[100005];
void prel()
{
    for(int i=2;i<=100000;i++) lgs[i]=lgs[(i>>1)]+1;
} // 预处理 log2(n) 

template<typename Tp, size_t siz>
struct ST
{
    Tp _con[siz][21];   
  
    Tp& operator[](int i) {return _con[i][0];}

    void pre()
    {
        for(int i=1;i<=20;i++)
            for(int j=1;j+(1<<i)-1<=siz;j++)
                _con[j][i]=gcd(_con[j][i-1], _con[j+(1<<(i-1))][i-1]);
    }

    Tp query(int l, int r)
    {
        if(l>r) return 0;
        int len=lgs[r-l+1];
        return gcd(_con[l][len], _con[r-(1<<len)+1][len]);
    }
};

ST<int, 100005> lis; // 相当简单的 ST 表，维护区间 gcd

inline int find(int l, int r0, int n)
{
    int g0=lis.query(l, r0);
    int ret=0, r=n;
    while(r0<=r)
    {
        int mid=(r0+r)>>1;
        if(lis.query(l, mid)==g0) r0=mid+1, ret=mid;
        else r=mid-1;
    }
    return ret;
} // 二分查找右端点

signed main()
{
    int n,q;
    read(n, q);
    prel();
    for(int i=1;i<=n;i++) read(lis[i]);
    lis.pre(); // 读入和预处理部分
    for(int l=1;l<=n;l++)
    {
        int ls, nr=l;
        for(;nr<=n;)
        {
            ls=nr;
            nr=find(l, nr, n);
            gcdct[lis.query(l, ls)]+=nr-ls+1;
            nr++;
        } // 枚举左端点，统计答案
    }
    while (q--)
    {
        read(n);
        write(gcdct[n]); putchar(10); // O(1)查询
    }
}
```

---

## 作者：Xy_top (赞：0)

简单题，考虑一遍预处理答案。

$\gcd$ 有一个很好的性质，每次减小都至少会减半，所以枚举区间起点，二分变化位置即可，至于区间 $\gcd$ 可以用 st 表快速求得。

由于跑不满，且时间限制 3s，所以过了。实际上每个点用时都没到 1s。

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, m;
int f[100005][17];
int lg[100005];
map <int, int> ans;
int gcd (int x, int y) {
	if (y == 0) return x;
	return gcd (y, x % y);
}
int query (int i, int j) {
	int l = lg[j - i + 1];
	return gcd (f[i][l], f[j - (1 << l) + 1][l]);
}
void solve () {
	lg[1] = 0;
	For (i, 2, 100000) lg[i] = lg[i / 2] + 1;
	cin >> n >> m;
	For (i, 1, n) cin >> f[i][0];
	For (j, 1, 16) For (i, 1, n - (1 << j) + 1) f[i][j] = gcd (f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
	For (i, 1, n) {
		int i_ = i, val = f[i][0];
		while (1) {
			int res = i_;
			foR (j, 16, 0)
				if (res + (1 << j) <= n && query (i, res + (1 << j) ) == val) res += (1 << j);
			ans[query (i, res) ] += res - i_ + 1;
			val = query (i, res);
			i_ = res + 1;
			if (i_ == n + 1) break;
		}
	}
	while (m --) {
		int x;
		cin >> x;
		cout << ans[x] << '\n';
	}
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) solve ();
	return 0;
}
```


---

