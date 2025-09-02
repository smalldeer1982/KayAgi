# [POI 2013] LAN-Colorful Chain

## 题目描述

Little Bytie loves to play with colorful chains.

He already has quite an impressive collection, and some of them he likes    more than the others.

Each chain consists of a certain number of colorful links.

Byteasar has noticed that Bytie's sense of aesthetics is very precise.

It turns out that Bytie finds a contiguous fragment of a chain nice if    it contains exactly    ![](http://main.edu.pl/images/OI20/lan-en-tex.1.png) links of color ![](http://main.edu.pl/images/OI20/lan-en-tex.2.png) links of color ![](http://main.edu.pl/images/OI20/lan-en-tex.3.png) links of color ![](http://main.edu.pl/images/OI20/lan-en-tex.4.png),    and moreover it contains no links of other colors.

A chain's appeal is its number of (contiguous) fragments that are nice.

By trial and error, Byteasar has determined the values ![](http://main.edu.pl/images/OI20/lan-en-tex.5.png) and ![](http://main.edu.pl/images/OI20/lan-en-tex.6.png).

Now he would like to buy a new chain, and therefore asks you to write a program to aid him in shopping.

给定一个长度为 $n$ 的序列 $a$ 和 $m$ 个条件（每个条件中包含键 $c_i$ 和值 $l_i$），要求找出满足下列条件的子串的数量并输出：

 + 条件中存在键 $c_i$ 的，要求子串中 $c_i$ 恰好出现 $l_i$ 次。

 + 条件中不存在键 $c_i$ 的，要求子串中不出现 $c_i$。

先输入 $n$ 和 $m$，再输入 $m$ 个条件的 $l_i$，然后输入 $m$ 个条件的 $c_i$，最后输入 $a_i$。

## 说明/提示



### 数据范围：

对于 $100\%$ 的数据，$1\leq m\leq n \leq 10^6$，$1\leq a_i,b_i,c_i\leq n$。

## 样例 #1

### 输入

```
7 3
2 1 1
1 2 3
4 2 1 3 1 2 5
```

### 输出

```
2
```

# 题解

## 作者：zhaoyp (赞：5)

# Solution

先求出每个数的 $\text{Hash}$ 值，再将目标串的各个数的 $\text{Hash}$ 值乘上各自出现次数，所得和即为目标串的 $\text{Hash}$ 值。

记目标串长度为 $len$。

同理求出原串每个长度为 $len$ 的字串的 $\text{Hash}$ 值，并与目标串比较即可。利用双指针从左到右扫描，时间复杂度 $O(n)$。

---

## 作者：ydnhaha (赞：4)

[题面](https://www.luogu.org/problemnew/show/P3560)

题外话：仍然(为什么是仍然)%一发下面的颜神233

比较裸的Hash题，先打个Hash表。把每个颜色拆成一个个拆成一串$1$对应在Hash表上，再乘上出现次数。按这个方法把所有好的颜色Hash成一个长串。最后在序列上移动左右端点$O(n)$扫过去，每次Hash一遍判断即可。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const unsigned long long mod=23333333333333333,bas=131;
unsigned long long hsh[1000009];
int cnt[1000009],num[1000009];
unsigned long long goal,noww;
int n,m,rd,l=1,r,ans,maxx;
int main ()
{
	scanf("%d%d",&n,&m);
	hsh[0]=1;
	for(int i=1;i<=n;i++)
		hsh[i]=hsh[i-1]*bas%mod;
	for(int i=1;i<=m;i++)
		scanf("%d",&cnt[i]),maxx+=cnt[i];//记录目标串的长度
	for(int i=1;i<=m;i++)
		scanf("%d",&rd),goal+=hsh[rd]*cnt[i];//构建目标串
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	for(int i=1;i<=n;i++)
	{
		noww+=hsh[num[i]];//修改当前串
		if(++r-l+1>maxx) noww-=hsh[num[l++]];//移动左右端点
		if(noww==goal) ans++;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：DYYqwq (赞：2)

### [P3560 [POI2013] LAN-Colorful Chain](https://www.luogu.com.cn/problem/P3560)

我们需要先求出目标串的 hash 值。

先求出每个数的 hash 值，再将目标串的每个数的 hash 值乘上各自出现次数，加和即可得到。

同理求出原串每个长度为目标串长度的串的 hash 值，随便比较一下，并记录答案即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7 , base = 13331;
int n , m , hsh[1000010] , sum[1000010] , l[1000010] , c[1000010] , a[1000010] , len , ans , res;
signed main()
{
    scanf("%lld%lld" , &n , &m);
    hsh[0] = 1;
    for(int i = 1 ; i <= n ; i ++) hsh[i] = hsh[i - 1] * base % mod;
    for(int i = 1 ; i <= m ; i ++) scanf("%lld" , &l[i]) , len += l[i];
    for(int i = 1 , x ; i <= m ; i ++) scanf("%lld" , &x) , res += hsh[x] * l[i] % mod , res %= mod;
    for(int i = 1 , x ; i <= n ; i ++) scanf("%lld" , &x) , sum[i] = (sum[i - 1] + hsh[x]) % mod;
    for(int i = 1 ; i + len - 1 <= n ; i ++) ans += ((sum[i + len - 1] - sum[i - 1] + mod) % mod == res);
    printf("%lld" , ans);
    return 0;
}
```

---

## 作者：tongzhenxuan (赞：2)

## 题意

对于一个长度为 $n$ 的序列，求有多少个子串（注意子串的元素是连续的），满足给出 $m$ 个数字，使每个给出的数字 $c_{i}$ 在子串中出现了 $l_{i}$ 次，且不含给出数字之外的其他数字。

数据范围：$1 \le m \le n \le 1e6$。

## 解题思路
对于给出的数字，因为题目要求的子串中不含其他数字，所以可以想到子串长度 $\sum l_{i}$ 是一定的。我们就可以像一个滑动窗口一样划过去。重点是怎样处理在滑动时数字个数的变化量。可以发现，向右滑动时右端点加入子串，左端点离开子串，所以可以用一个简单的映射来统计数字出现的次数。离开时数字的值减一，加入时加一，看最后符合要求的数字是否到达 $m$ 个，如果是，方案数加一。

时间复杂度：$O(n)$。

##	code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int limit;
	int x;
	int f;
};
map<int,node> mp;
int a[1000005];
int n,m;
int len;
int c[1000005];
int l[1000005];
int i,j;
int cnt,ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%d",&l[i]);
	for(i=1;i<=m;i++)
		scanf("%d",&c[i]),
		mp[c[i]].limit=l[i],
		mp[c[i]].f=1,
		len+=l[i];
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(i=1;i<len;i++)
	{
		mp[a[i]].x++;
		if(!mp[a[i]].f)
			continue;
		if(mp[a[i]].x==mp[a[i]].limit)
			cnt++;
		else if(mp[a[i]].x==mp[a[i]].limit+1)
			cnt--;
	}
	for(i=1;i<=n-len+1;i++)
	{
		j=i+len-1;
		mp[a[j]].x++;
		if(mp[a[j]].f)
		{
			if(mp[a[j]].x==mp[a[j]].limit)
				cnt++;
			else if(mp[a[j]].x==mp[a[j]].limit+1)
				cnt--;
		}
		mp[a[i-1]].x--;
		if(mp[a[i-1]].f)
		{
			if(mp[a[i-1]].x==mp[a[i-1]].limit)
				cnt++;
			else if(mp[a[i-1]].x==mp[a[i-1]].limit-1)
				cnt--;
		}
		if(cnt==m)
			ans++; 
	}
	printf("%d",ans);
}
```


---

## 作者：封禁用户 (赞：2)

显然这个题就是让求一些长度为$∑li$的子串，我们可以用滑动窗口去做，关键就是如何快速确定一个子串是满足要求的。

于是我就想，如果一个子串是满足要求的，那么它里边所有数的出现次数都是严格确定的（未作规定的数就是0个），也就是说这个记录数字出现次数的数组cnt是唯一确定的，于是我就想到了哈希，把这个数组看做一个字符串，把它用哈希搞出来即可快速判断。我在维护哈希值的时候，因为我们是滑动窗口，每次移动的时候肯定会有个数离开，有个数进来，这种改变会影响cnt数组，我直接在对应位（哈希可以看做一个位数很长的k进制数）上进行修改：

```cpp
hsh=(((hsh-cnt[ints[i]]*kx[ints[i]])%p)+p)%p;
cnt[ints[i]]++;
hsh=(hsh+cnt[ints[i]]*kx[ints[i]])%p;
```

举个例子：假如我们现在维护的是10进制数，现在是123456789，我们想把6改为1，那就先减去$6×10^3$，变成123450789，再直接加上1$×10^3$，变成123451789，大概就是这个道理，这样就能快速修改哈希值了。

还有，为了保险起见，应该把哈希的位数设为序列的最大数，把哈希的进制设为最多的出现次数（即cnt数组的最大可能值）。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
#define p 100000000003
using namespace std;
int ints[1000001];
int cnt[1000001];
int kx[1000001];
int fcnt[1000001];
char buf[100000000];int pptr=-1;
inline char get_char(){
	pptr++;return(buf[pptr]);
}
#define getchar get_char
inline int get(){
	int n;char c;while((c=getchar())||1)if(c>='0'&&c<='9')break;
	n=c-'0';while((c=getchar())||1){
		if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
	}
}
int tmp[1000001];
signed main(){
	fread(buf,1,100000000,stdin);
	
	int n=get(),m=get();int kp=0;int ln=0;int sid=0;
    //kp为进制，ln为哈希长度，sid为子串长度
	for(register int i=1;i<=m;i++)tmp[i]=get(),kp=max(kp,tmp[i]),sid+=tmp[i];
	for(register int i=1;i<=m;i++){
		int a=get();ln=max(ln,a);fcnt[a]=tmp[i];
	}
	for(register int i=1;i<=n;i++){
		ln=max(ln,ints[i]=get());cnt[ints[i]]++;kp=max(kp,cnt[ints[i]]);
	}memset(cnt,0,sizeof(cnt));
	//printf("%d %d\n",ln,kp);
	kx[0]=1;int realhsh=0;
	for(register int i=1;i<=ln;i++){
		kx[i]=(kx[i-1]*kp)%p;
		realhsh=(realhsh+kx[i]*fcnt[i])%p;
	}//先把答案子串的哈希值求出来
	int hsh=0;int ans=0;
	for(register int i=1;i<sid;i++){
		hsh=(((hsh-cnt[ints[i]]*kx[ints[i]])%p)+p)%p;
		cnt[ints[i]]++;
		hsh=(hsh+cnt[ints[i]]*kx[ints[i]])%p;
	}哈哈哈您别想抄代码
	for(register int i=sid;i<=n;i++){
		hsh=(((hsh-cnt[ints[i]]*kx[ints[i]])%p)+p)%p;
		cnt[ints[i]]++;
		hsh=(hsh+cnt[ints[i]]*kx[ints[i]])%p;
        //进来一个数
		if(i!=sid){
			hsh=(((hsh-cnt[ints[i-sid]]*kx[ints[i-sid]])%p)+p)%p;
			cnt[ints[i-sid]]--;
			hsh=(hsh+cnt[ints[i-sid]]*kx[ints[i-sid]])%p;
		}//出去一个数
		if(hsh==realhsh)ans++;//找到匹配成功的子串哈哈哈
	}
	cout<<ans<<endl;
	return(0);
}
```

---

## 作者：xixisuper (赞：1)

# P3560 [POI2013] LAN-Colorful Chain 题解

虽然我知道这是随机赋权的板子题，但是这个数据范围也太小了点，完全不需要随机赋权就能过。

下面给出一个完全不需要随机赋权的题解。

## 思路

观察题目发现数据范围和 $n$ 等阶，可以说非常小，所以我们直接开一个桶存每个数出现的次数。

不难发现的是，最终答案限定的区间长度是一定的，一定是 $\sum_{i=1}^ml_i$，所以我们只需要不断向右扩右端点，向左收左端点，以保证当前区间长度是 $\sum_{i=1}^ml_i$ 就可以了。

单次拉长缩放区间的时间复杂度是 $O(1)$ 的，而我们至多拉长 $2n$ 次，所以最终总时间复杂度就是 $O(n)$ 的了。

~~这题如果想强迫用随机赋权过的话，必须把 $n$ 的范围开到 $10^7$ 并把 $a_i,c_i$ 的范围开到 $10^9$，这样才能卡掉用桶暴力存的 $O(n\log n)$ 做法。~~

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define ll long long 
using namespace std;
const ll N=1e6+10;
ll tong[N],l[N],xian[N],a[N],c,n,m,mb;
ll duo,nlen,lst=1,ans=0;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=m;i++) cin>>l[i];
	for(ll i=1;i<=m;i++){
		cin>>c;
		xian[c]=l[i];
		mb+=l[i];
	}
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll i=1;i<=n;i++){
		nlen++;
		tong[a[i]]++;
		if(tong[a[i]]>xian[a[i]]) duo++;
		if(nlen>mb){
			nlen--;
			if(tong[a[lst]]>xian[a[lst]]) duo--;
			tong[a[lst]]--;
			lst++;
		}
		if(nlen==mb&&!duo) ans++;
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Epoch_L (赞：1)

## Solution
易知 $\sum l_i$ 为子串长度，所以从头开始拿一段区间往后滑，第一次的答案暴力得出，后面的答案可根据上一次的答案加一个数减一个数得到。开一个桶，维护 $now$ 为符合要求的数的数量，若 $now=m$，则答案加 $1$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=1e6+7;
int p[N],n,m,a[N],c[N],l[N],cnt[N],ans,len,now;
void add(int x){
  if(++cnt[a[x]]==p[a[x]])now++;
  if(cnt[a[x]]==p[a[x]]+1)now--;
  if(now==m)ans++;
}
void del(int x){
  if(--cnt[a[x]]==p[a[x]])now++;
  if(cnt[a[x]]==p[a[x]]-1)now--;
  if(now==m)ans++;
}
int main(){
  read(n);read(m);
  for(int i=1;i<=m;i++)read(l[i]),len+=l[i];
  for(int i=1;i<=m;i++)read(c[i]),p[c[i]]=l[i];
  for(int i=1;i<=n;i++)read(a[i]);
  for(int i=1;i<=len;i++)add(i);
  for(int i=2;i<=n-len+1;i++)del(i-1),add(i+len-1);
  cout<<ans;
  return 0;
}
```

---

## 作者：Moeebius (赞：1)

## Preface
> 随机跳题跳到的……为什么 solution 里面全是字符串 hash 啊 qwq
## Analysis
为了方便，我们把数列 $c$ 里的数字称为「关键数字」。

我们考虑用一个 ```vector``` 数组把所有数字出现的位置记下来。（为了方便，这里可以先不管是不是关键数字）

然后扫一遍，每走到一个位置就干三件事情：

1. 以**该点为起点**计算终点。
2. 判断是否合法并更新答案。
3. 将这个点挖掉。

然后逐一实现。

### 如何算终点？
之前不是搞了一堆 ```vector``` 吗？最开始扫一遍，找到第 $i$ 个关键数字第 $l_i$ 次出现的位置，然后取一个 $\max$，得到的结果 $mx$ 即为终点。

设置指针 $cur$，初始值均为 $0$，$cur_i$ 表示第 $i$ 个关键数字目前从第 $cur_i$ 次出现的位置开始取。 

至于如何更新，下面再说。

### 如何判断是否合法？
这个简单，由于取了 $\max$，可以确保每个关键数字都**按照要求被包含了**，接下来只要看有没有混进别的数字。

计算终点和起点之间的数字数量 $len$，如果 $len=\sum l_i$ 就是合法的。

### 如何把这个点挖掉？
首先，判断这个点是不是关键数字，如果不是，就不用管。

否则，更新 $cur$，将其自增 $1$。

然后更新终点，$mx\leftarrow \max\{mx,\text{该数字第 cur+l 次出现的位置}\}$。

> 此处的 $l$ 即为当前数字**需要**出现的数量。

实现时还有一些细节，比如关键数字不够用了就可以直接输出答案并终止程序。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define il inline
#define mkp make_pair
#define pii pair<int,int>
#define lll __int128
#define ll long long
#define For(i,j,k) for(int i=(j); i<=(k); ++i)
#define ForDown(i,j,k) for(int i=(j); i>=(k); --i)
#define pb push_back
#define init(filename) freopen(filename ".in" ,"r",stdin);freopen(filename ".out" ,"w",stdout)
template<typename T> 
il void read(T &x){ x=0;int f=1;char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}while(isdigit(c)){x=x*10+c-'0';c=getchar();}x*=f;}
template<typename T, typename ... Args>
il void read(T &x, Args &... y){ read(x);read(y...); }

#define int ll
int n,m;
const int MAXN=1e6+5;
int c[MAXN],l[MAXN],a[MAXN],id[MAXN],cur[MAXN]; // id 用于转换关键数字的值与编号。
vector<int> ptr[MAXN]; // 出现位置

signed main()
{
	read(n,m);
	For(i,1,m) read(l[i]);
	For(i,1,m) read(c[i]);
	For(i,1,n) read(a[i]);

	memset(cur,-1,sizeof(cur));
	For(i,1,n)
	{
		ptr[a[i]].pb(i);
	}
	ll ans=0,mx=0,sum=0;
	For(i,1,m)
	{
		cur[c[i]]=0,id[c[i]]=i;
		if(ptr[c[i]].size()<l[i]) return !printf("0");
		mx=max(mx,0ll+ptr[c[i]][l[i]-1]),sum+=l[i];
	}
	For(i,1,n)
	{
		if(mx-i+1==sum) ++ans; // mx-i+1 就是 len
		if(~cur[a[i]])
		{
			cur[a[i]]++;
			if(ptr[a[i]].size()<cur[a[i]]+l[id[a[i]]]) break;
			mx=max(mx,0ll+ptr[a[i]][cur[a[i]]+l[id[a[i]]]-1]);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：1)

+ 简要题意：给出一个序列 $\{a_n\}$，求其有多少个子串 $\{a_l,a_{l+1}\cdots,a_r\}$ 满足对于数字 $c_i$，恰好出现 $l_i$ 次。

我们其实不关心这个数到底出现在啥位置，只关心出现了多少次。

一个朴素的想法是用桶记录每个数出现了多少次，然后扫一遍，每次检查。这样的复杂度是 $O(nV)$ 的。

$n$ 估计是跑不掉，我们考虑怎么搞掉 $V$ 这一维。

我们用类似字符串哈希的方法哈希这个序列似乎是可行的！

我们给每个数字都钦定一个哈希值 $H_x$，将对于一个子串将之 $H_{a_i}$ 累加即可。

由于都是恰好出现，所以能合理的字符串显然是长度为 $\sum l_i$ 的。

这样对于每个长度合法的串哈希，和原串比对即可。这里用两个不同的质数取模。既然 $\text{Hash}(l,r)=\sum\limits_{i=l}^r H_{a_i}$，则现在检查的区间 $\text{Hash}(l,r)$ 可以快速从前一个区间的 $\text{Hash}(l-1,r-1)$ 推得。

```cpp
#include <iostream>
#define rep(i,l,r) for(i=l;i<=r;++i)
using namespace std;
using ull=unsigned long long;
const int N=1000005;
ull li[N],h[2][N],v[N];
const ull bse=122,p1=10000007ll,p2=10000537ll;
ull n1,m1,n2,m2,ci,len,n,m,i,ret,l;
int main ()
{
	cin>>n>>m;
	h[0][0]=h[1][0]=1;
	rep(i,1,n)
	{
		h[0][i]=h[0][i-1]*bse%p1;
		h[1][i]=h[1][i-1]*bse%p2;
	}
	rep(i,1,m)
	{
		cin>>li[i];
		len+=li[i];
	}
	rep(i,1,m)
	{
		cin>>ci;
		m1+=h[0][ci]*li[i];
		m2+=h[1][ci]*li[i];
	}
//	cout<<m1<<' '<<m2<<endl;
	rep(i,1,n)
		cin>>v[i];
	l=1;
	rep(i,1,len-1)
	{
		n1+=h[0][v[i]];
		n2+=h[1][v[i]];
	}
	rep(i,len,n)
	{
		n1+=h[0][v[i]];
		n2+=h[1][v[i]];
		if(i-l+1>len)
		{
			n1-=h[0][v[l]];
			n2-=h[1][v[l]];
			++l;
		}
		if(n1==m1 && n2==m2)
			++ret;
	}
	printf("%d",ret);
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

简要题意：

给定序列 $\{a_n\}$，给定 $m$ 个限制，问，能选出多少个子串，满足 $c_i$ 恰好有 $l_i$ 个，且没有其他数字。

保证 $c_i$ 互不相同（assert 过了）。

-----------------------------

本来想看看随机一个数进行 hash 的题目才过来的，没想到不是这样。当然 hash 可以做。

其实很简单，只要发现这个子串的长度是确定的，就是 $\sum l_i$。

$m$ 个限制中没有的数当作限制为 $0$ 个就好了。

我们可以令 $ned_x$ 表示 $x$ 需要多少个，$sum_x$ 表示当前子串中 $x$ 有多少个。注意到 $a_i\le n$，其实如果没有这个条件也可以离散化，复杂度多一个 $\log $。

再记录一下 $sum_x=ned_x,x\in[1,n]$ 这 $n$ 个条件中满足多少个，个数记为 $cnt$，统计 $cnt$ 是否为 $n$ 即可。这样增加/减少一个数都可以 $O(1)$ 解决。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, m, sum[N], cnt, x, ned[N], tot, a[N], ans, c[N];
inline void upd(int x){
    if(ned[x] == sum[x]) cnt--;
    sum[x]++;
    if(ned[x] == sum[x]) cnt++;
}
inline void del(int x){
    if(ned[x] == sum[x]) cnt--;
    sum[x]--;
    if(ned[x] == sum[x]) cnt++;
}
int main(){
    //freopen("data.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        scanf("%d", &c[i]);
        tot += c[i];
    }
    for(int i = 1; i <= m; i++){
        scanf("%d", &x);
        assert(ned[x] == 0);
        ned[x] = c[i];
    }
    if(tot > n){
        puts("0");
        return 0;
    }
    cnt = n - m;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= tot; i++){
        upd(a[i]);
    }
    ans += (cnt == n ? 1 : 0);
    for(int i = tot + 1; i <= n; i++){
        upd(a[i]);
        del(a[i - tot]);
        ans += (cnt == n ? 1 : 0);
    }
    printf("%d\n", ans);
    return 0;
}
```

为什么这么多题解都是 hash？感觉这种方法更好想。

---

## 作者：TernaryTree (赞：0)

典中典哈希。每个值 $v\in a_i$ 给它扔一个随机权值 $b_v$，然后对 $a$ 序列的元素权值前缀和 $p_i=\sum\limits_{j=1}^i b_{a_i}$，则一段 $[l,r]$ 的哈希值即为 $p_r-p_{l-1}$；同时算出符合条件的子串的哈希值 $k=\sum b_{c_i}l_i$，记 $z=\sum l_i$，统计有多少个 $p_i-p_{i-z}=k$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;
const int mod = 0x3b800001;

int n, m, s, k, z, r;
int l[maxn], c[maxn], a[maxn], b[maxn], p[maxn];

signed main() {
    cin >> n >> m;
    s = time(0) * n % mod * m % mod * 1145141 % mod;
    for (int i = 1; i <= m; i++) cin >> l[i];
    for (int i = 1; i <= m; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (!b[a[i]]) b[a[i]] = s, s = (s * rand() % mod + 20081118) % mod + 486;
        p[i] = p[i - 1] + b[a[i]];
    }
    for (int i = 1; i <= m; i++) {
        if (!b[c[i]]) return (puts("0"), 0);
        k += l[i] * b[c[i]], z += l[i];
    }
    for (int i = z; i <= n; i++) if (p[i] - p[i - z] == k) ++r;
    cout << r << endl;
    return 0;
}
```

---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3560)

## 题意

给定 $l_1,l_2,\dots,l_m$ 及 $c_1,c_2,\dots,c_m$。一个串是好的，当且仅当对于 $1\leq i\leq m$，$c_i$ 在串中正好出现了 $l_i$ 次，且不在序列 $c$ 中的数字没有出现。保证 $c_i\ne c_j(i\ne j)$。

现有一长度为 $n$ 的序列 $a$，请求出其中有多少个好的序列。

$1\leq n,m\leq 10^6$

## 思路

显然好的串的长度应为 $l_1+l_2+\dots+l_m$，因此可以扫描一遍 $a$，每次判断是否满足条件，由此联想到哈希。对于每一个 $c_i$ 赋键值 $p_i$，当子串总和为 $p_1\times l_1+p_2\times l_2+\dots+p_m\times l_m$ 时，我们有极大的把握称此时的串是好的。

现在就可以随便做了，比如用一个双指针。

Code（$\Theta(n)$）:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m,a[N],p[N],c[N],l=1,r,ans,len;
unsigned long long h[N];
__int128 now,aim; 
signed main()
{
    scanf("%d%d",&n,&m);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 Rand(seed);
    uniform_int_distribution<unsigned long long>dist(1,1e18);
    for(int i=1;i<=m;i++)scanf("%d",&p[i]),len+=p[i];
    for(int i=1;i<=m;i++)scanf("%d",&c[i]);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)h[i]=Rand();for(int i=1;i<=m;i++)aim+=h[c[i]]*p[i];
    while(l<=n&&r<=n)
    {
        now+=h[a[++r]];
        if(r-l+1>len)now-=h[a[l++]];
        ans+=(now==aim);
    }
    printf("%d\n",ans);
    return 0;
}
```

[record](https://www.luogu.com.cn/record/111657466)

---

## 作者：Starrydream (赞：0)

最上面这个题意是我读错了，不过你也可以做做看。

正确的题意的做法在底下。

# [POI2013]LAN-Colorful Chain

## 题意

给定一个$1e6$的序列，给定$1e6$的询问，每个询问包含$s_i,l_i$

问你$l_i$长度的$s_i$这个串出现了几次。

~~sb洛谷智障翻译。要不是做水题就用LOJ和BZOJ~~

## 题解

本来想用高级一点的SA随便做。

只需要后缀排序后二分即可。

结果发现$\sum l_i$是没有限制的。这样就不能对那些询问串直接建SA了。

然而由于都是一样的字符。

所以我们预处理每个后缀最长相同字符前缀长度$h_i$，指针模拟即可，由于有单调右移，这个复杂度是$O(n)$的。

```cpp
	 inline void pre()
	 {
		 int r = 1;
		 for(int i = 1 ; i <= n ; ++i)
		 {
			 r = std::max(r , i);
			 if(i != r) {
				 h[i] = r - l + 1;
				 continue;
			 }
			 while(r < n) if(s[r + 1] == s[i]) ++ r;
		 }
	 }
```



至于后缀首字母是什么，$O(1)$得到即可。。

然后后缀排序。然后用线段树维护$h_{sa_i}$

然后对于一个询问$(s_i,l_i)$，我们二分出合法的后缀区间。（一个显然的平凡性质，后缀排序后对于一个给定的串作为模式串匹配的后缀集合排序后是连续的，反证法即可证明）。

记：$c_i^{l_i}$表示一个长度为$l_i$的字符为$c_i$串。

>证明：设询问是$(c_i,l_i)$,假设排序后不是连续的，即$\exists s_k , LCP(c_i^{l_i},s_k) < L \and (LCP(s_{k-1},c_i^{l_i}) >= L \or LCP(s_{k+1},c_i^{l_i}) >= L) $
>
>此时第$L$个字符与字典序排序矛盾，因此原命题成立。
>
>当然这个一句话证明有点不是太严谨。
>
>从字典序的定义出发，首先第一个字符是$s_i$，开头比$s_i$小的都在前面，大的都在$s_i$后面。
>
>所以开头是$s_i$的构成一个连续区间$[l,r]$。
>
>将$[l,r]$按照$[1,n]$的方法归纳证明，得到结论：
>
>对于一个给定的相同前缀$S$，其匹配后缀必为连续区间。

然后线段树查询区间和就完成了一次询问。。。。。

所以SA上二分一个区间，再线段树查询一个区间和。

仔细想想真的需要线段树吗？静态查询一个区间和应该用啥？

数组！

$sum_i = \sum\limits_{j=1}^{i}h_{sa_j}$

复杂度是$O(nlogn+mlogn+m)$

二分出区间这个东西挺麻烦。


----
一看输出只有一个数，然后看了遍题。

原来是恰好$m$个$(s_i,l_i)$的字串有多少个。

这不是sb题吗？？直接双指针开始扫，**即时判断当前字符加入**，如果超了一直移动左指针，否则移动右指针并更新数组，为了避免大量暴力重复扫描，用变量记录有多少个满足了，$m$个满足时$Ans += 1$。答案最大是n。

说的更清晰一点。

按照右端点分类，每个右端点最多有一个符合答案。

需要注意到的是，由于每个字符都是给定数目的，因此当一个右端点与左端点形成的字串某个字符超过数目的时候，左端点向右移动直到满足条件位置这个贪心做法是正确的：

>对于新的右端点$r$，如果左端点保持不动，则每个字符数目只会增加不会下降，所以多的字符还是不符合答案，假如都没有大于，则需要更多字符，此时移动左端点没有意义。因此左端点有单调性。

~~真的懒得给普及题写一个形而上的符号系统证明了~~

然后就是指针模拟的一堆细节。。。

```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#define maxn 1000005
int cnt[maxn] , cur , ans , ln[maxn] , n , m , c[maxn] , l[maxn], s[maxn];

void print()
{
	for(int i = 1 ; i <= n ; ++i)
		printf("%d ",cnt[i]);
	putchar(10);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1 ; i <= m ; ++i)
		scanf("%d",&l[i]);
	for(int i = 1 ; i <= m ; ++i)
		scanf("%d",&c[i]);
	for(int i = 1 ; i <= n ; ++i)
		scanf("%d",&s[i]);
	for(int i = 1 ; i <= m ; ++i)
		ln[c[i]] = std::max(ln[c[i]] , l[i]);
//	for(int i = 1 ; i <= n ; ++i)
//		printf("%d ",ln[i]);
//	putchar(10);

	int l = 1 , r = 0; // [l,r]
	while(r < n)
	{
		++r;
		++cnt[s[r]];
		if(cnt[s[r]] == ln[s[r]]) ++cur;
		else if(cnt[s[r]] == ln[s[r]] + 1) --cur;
		if(cur == m) ++ ans;
//		print();
		if(cnt[s[r]] > ln[s[r]])
		{
			while(cnt[s[r]] > ln[s[r]])
			{
				--cnt[s[l]];
				if(cnt[s[l]] == ln[s[l]]) ++cur;
				else if(cnt[s[l]] == ln[s[l]] - 1) --cur;
				++l;
//				print();
				if(cur == m) ++ans;
			}
		}
	}
	printf("%d",ans);
}
```


---

