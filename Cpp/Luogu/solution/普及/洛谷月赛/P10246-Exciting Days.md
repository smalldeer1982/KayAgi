# Exciting Days

## 题目背景

网上流传一种说法，称 $10$ 月 $24$ 日是“程序员节”，因为 $1024$ 恰好是 $2^{10}$，而计算机和二进制有密切联系。

如果某个不使用地球历法的外星文明，也不一定用传统的二进制计算机，会不会也有类似的传统呢？

## 题目描述

某个星球的历法和地球虽然数值上和地球不同，但是其结构和地球人的历法大体相似。具体地，他们的一年有 $n$ 个月，其中第 $i$ 个月有 $a_i$ 天。

定义 $m$ 月 $d$ 日的**特征值**为将 $m,d$ 的十进制写出（不含前导 $0$）后，直接拼接的结果。例如 $3$ 月 $7$ 日特征值是 $37$，$12$ 月 $20$ 日特征值是 $1220$。

如果一个日期的特征值是 $k$ 的自然数次幂，则称这个日期是**广义程序员节**。你可以求出这个星球的所有广义程序员节吗？

## 说明/提示

【样例解释】

对于第一组数据，外星人的日历有两个月，第一个月有 $11$ 天，第二个月有 $12$ 天。现在要求特征值是 $1$ 的整数次幂，只能是 $1$，然而日期的特征值**至少是两位数**，因此不存在符合要求的日期。

对于第二组数据，这是地球人闰年时的公历，不难发现输出的日期特征值确实都是 $2$ 的自然数次幂。

【数据范围】

本题共 $25$ 个测试点，每个 $4$ 分。数据范围中，$\sum n$ 表示所有测试数据的 $n$ 之和，例如样例的 $\sum n=14$。

|测试点编号|$T\le$|$\sum n\le$|$a_i\le$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$1$|$1000$|$1000$|$k=6$|
|$2\sim 3$|$1$|$1000$|$1000$||
|$4\sim 6$|$3$|$1000$|$1000$||
|$7\sim 11$|$3$|$10^4$|$10^4$||
|$12\sim 14$|$1$|$3\times 10^5$|$10^9$||
|$15\sim 17$|$3$|$3\times 10^5$|$10^9$||
|$18\sim 19$|$10^4$|$10^4$|$10^9$|$n=1$|
|$20\sim 21$|$10^4$|$9\times 10^4$|$10^9$|$n\le 9$|
|$22\sim 25$|$10^4$|$3\times 10^5$|$10^9$||

对于全部数据，保证 $1\le T\le 10^4$，$1\le n\le 3\times 10^5$，$1\le \sum n\le 3\times 10^5$，$1\le a_i,k\le 10^9$，输入皆为整数。

为避免卡常，题目保证单个测试点输出的日期不超过 $2\times 10^4$ 个。

## 样例 #1

### 输入

```
2
2 1
11 12
12 2
31 29 31 30 31 30 31 31 30 31 30 31
```

### 输出

```
0
7
1 6
1 28
3 2
5 12
6 4
10 24
12 8```

# 题解

## 作者：yummy (赞：15)

# C. Exciting Days 官方题解

本题涉及的主要知识点：

- 【1】模拟法
- 【3】排序
- （推荐）【4】`vector` 容器

---

记 $V$ 为特征值；$k=1$ 时应该什么都不输出，所以下面的讨论中默认 $k>1$。

## 前 $24\sim 44$ 分

枚举每个日期，然后判断其是否为 $k$ 的整数次幂。

若依次计算 $k^1,k^2,\ldots$ 判断是否相等，单次时间复杂度 $O(\log V)$，可得 $24$ 分。

但是如果把特征值除以 $k$，直到不能整除，再判断剩下的数是不是 $1$，时间复杂度就是平均 $O(1)$ 的了，可以拿到 $50$ 分。

测试点 $1$ 中 $k=6$ 的好处有二：不用判 $k=1$，$10^6$ 内 $6$ 的整数次幂不含 $0$。

## 正解

反过来，枚举特征值，然后找出特征值对应的日期。

特征值只有 $O(\log V)$ 个，并且每个特征值只有 $O(\log V)$ 位数，这也就意味着每个特征值最多对应 $O(\log V)$ 个日期，总体只需要判断 $O(\log ^2 V)$ 个日期是否合法。

判断完是否合法后，对答案进行排序输出。这一步可以是 `struct` 配合 STL 的 `sort`，也可以手写冒泡排序等。根据具体的实现方式，时间复杂度介于 $O(\log^2 V\log\log V)$ 和 $O(\log^4 V)$ 之间。

## 参考代码

以下为 C++ 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long Mx=1e17;
int n,a[1000005];
long long k;
struct date{int m,d;};
bool operator < (date x,date y){return x.m<y.m || x.m==y.m && x.d<y.d;}
vector<date> all;
void mian(){
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	if(k==1){puts("0");return;}
	for(long long v=k;;){
		long long sep=10;
		while(v/sep>n)sep*=10;
		while(v>=sep){
			long long m=v/sep,d=v%sep;
			if(d!=v%(sep/10) && 1<=d && d<=a[m])
				all.emplace_back((date){m,d});
			sep*=10;
		}
		if(v<=Mx/k)v*=k;
		else break;
	}
	sort(all.begin(),all.end());
	printf("%llu\n",all.size());
	for(date i:all)
		printf("%d %d\n",i.m,i.d);
}
int T;
int main(){
	for(scanf("%d",&T);T;T--){
		all.clear();
		mian();
	}
}
```

参考 Python 3 代码：

```python
for T in range(int(input())):
    n,k=map(int,input().split())
    a=[0]+list(map(int,input().split()))
    dates=[]
    Mx=10**16
    if k>1:
        val=k
        while val<Mx:
            T=str(val)
            for i in range(1,len(T)):
                m,d=T[:i],T[i:]
                if d[0]!='0' and 1<=int(m)<=n and int(d)<=a[int(m)]:
                    dates.append((m,d))
            val*=k
    def key_of(x):
        return int(x[0])*Mx+int(x[1])
    dates.sort(key=key_of)
    print(len(dates))
    for i in dates:
        print(i[0],i[1])
```

---

## 作者：saixingzhe (赞：6)

# 分析
我们发现枚举每一天复杂度过高，想到枚举所有的**广义程序员节**，判断其是否能被某一天表示出来。

### 枚举范围
每个月能被表示出来的最大一天，就是这个月的最后一天，所有月能表示出的最大一天的最大值，就是能被表示出的最大值，也就是枚举上限。
```cpp
for(int i=1;i<=n;i++){
	scanf("%lld",&a[i]);
	maxn=max(maxn,stoll(to_string(i)+to_string(a[i])));
}
```
以上代码中的 `maxn` 即为枚举上限。

### 枚举判断
对于每个数枚举其在哪个点分段，左边即为月，右边即为日。判断是否存在这一天。
```cpp
for(long long i=k;i<=maxn;i*=k){
			string s=to_string(i);
			for(int i=1;i<s.size();i++){
				if(s[i]=='0')	continue;
				long long c=stoll(s.substr(0,i)),d=stoll(s.substr(i));
				if(c<=n&&d<=a[c])	cnt++,ans.push({c,d});
			}
		}
```

### 枚举统计
开一个优先队列，并重载结构体的运算符，每次直接扔进优先队列即可。
```cpp
struct Node{
	int m,d;
	friend bool operator < (Node x,Node y){
		if(x.m!=y.m)	return x.m>y.m;
		return x.d>y.d;
	}
};
```
```cpp
while(!ans.empty()){
			printf("%d %d\n",ans.top().m,ans.top().d);
			ans.pop();
		}
```
`ans` 即为优先队列。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
long long k,a[300001];
struct Node{
	int m,d;
	friend bool operator < (Node x,Node y){
		if(x.m!=y.m)	return x.m>y.m;
		return x.d>y.d;
	}
};
int main(){
	scanf("%d",&T);
	while(T--){
		priority_queue<Node>ans;
		long long maxn=0,cnt=0;
		scanf("%d%lld",&n,&k);
		for(int i=1;i<=n;i++)	scanf("%lld",&a[i]),maxn=max(maxn,stoll(to_string(i)+to_string(a[i])));
		if(k==1){
			printf("0\n");
			continue;
		}
		for(long long i=k;i<=maxn;i*=k){
			string s=to_string(i);
			for(int i=1;i<s.size();i++){
				if(s[i]=='0')	continue;
				long long c=stoll(s.substr(0,i)),d=stoll(s.substr(i));
				if(c<=n&&d<=a[c])	cnt++,ans.push({c,d});
			}
		}
		printf("%d\n",cnt);
		while(!ans.empty()){
			printf("%d %d\n",ans.top().m,ans.top().d);
			ans.pop();
		}
	}
    return 0;
}
```

### 一些闲话
由于本人数学非常差，导致在 T2 卡了一个小时，跳过了 T2，结果在 15 分钟内过了 T3，然后又在帮助下死磕出了 T2\bx。

最后祝大家省选都能反向挂分，取得满意的成绩！

---

## 作者：IGA_Indigo (赞：5)

## 题意分析
这道题是个大模拟，而且有轻微卡常，还会爆 int，还要考虑越界，需要注意很多点，背景就是在一个别的星球，历法和地球不太一样，有 $m$ 个月，第 $i$ 个月有 $a_i$ 天，问你月份和日期直接拼接满足是给的 $k$ 的 $x$ 次方的方案。
## 大体思路
就是枚举出来所有 $k$ 的 $x$ 次方，然后枚举所有拆成月份和日期的可能情况。举个例子，$2$ 的 $10$ 次方是 $1024$，我们需要枚举 $10$ 月 $24$ 日的情况和 $102$ 月 $4$ 日的情况，$1$ 月 $24$ 要记得舍去。最后依照时间顺序输出出来即可。

代码注释有详细解说。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(long long x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return ;
}//快读快写
int a[300005];
vector<int> ansm,ansd;
struct node{
	int mmm,ddd;
}ans[20005];
void init(){
	for(int i=1;i<=300000;i++) a[i]=0;
}
bool cmp(node aa,node bb){
	if(aa.mmm==bb.mmm){
		return aa.ddd<bb.ddd;
	}
	return aa.mmm<bb.mmm;
}
int main(){
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++){
		ansm.clear();
		ansd.clear(); 
		init();//每一次询问先都初始化成0 
		int n,k;
		n=read();
		k=read();
		int maxx=-1;
		for(int i=1;i<=n;i++){
			a[i]=read();
			maxx=max(maxx,a[i]);//找出最大的日期便于我们规定界限 
		}
		if(k==1){//注意特殊情况，如果k=1，后面的for循环会死掉，因为不会出现月份和日期合起来只有1的情况，直接输出0即可 
			write(0);
			cout<<'\n';
			continue ;
		}
		long long len=1,c=maxx;
		while(c){
			c/=10;
			len*=10;//算一下maxx（最大日期）的位数 
		}
		long long mma=n*len+maxx;//限制最大情况 
		for(long long i=1;i<=mma;i*=k){//i是可能出现的合起来的情况 
			long long lenn=0,ci=i;
			while(ci){
				ci/=10;
				lenn++;
			}
			for(int j=1;j<lenn;j++){//枚举拆成月份和日期的情况 
				long long lr=1;
				for(int dd=1;dd<=j;dd++){
					lr*=10;
				}
				long long mo=i/lr;
				long long da=i%lr;//枚举月份和日期 
				long long dda=da;
				long long jlc=1;
				while(dda){
					jlc*=10;
					dda/=10;
				}
				if(mo*jlc+da!=i){
					continue ;//避免出现例子中的一月二十四日的情况 
				}
				if(mo<=n){
					if(da>a[mo]){
						continue ;
					}//避免越界搜索 
					ansm.push_back(mo);
					ansd.push_back(da);//存储月份和日期 
				}
			}
		}
		int vlen=ansm.size();
		write(vlen);
		printf("\n");
		for(int i=0;i<vlen;i++){
			ans[i].mmm=ansm[i];
			ans[i].ddd=ansd[i];//平提到struct中 
		}
		sort(ans,ans+vlen,cmp);//按照时间顺序排序 
		for(int i=0;i<vlen;i++){
			write(ans[i].mmm);
			printf(" ");
			write(ans[i].ddd);
			printf("\n");//输出 
		}
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：4)

### 思路：

发现日期数量太多，考虑枚举**特征值**。

当 $k=2$ 时，特征值是最多的，有 $\log_2 W$ 个，而一个特征值的数位最多是 $\log_{10} W$ 个，那么我们的时间复杂度为 $O(T \log_2 W \log_{10} W)$。

简要说一下 ``check`` 的过程，考虑枚举这个特征值**断开**的位置，即左边是月份 $x$，右边是天数 $y$，则只要 $y \le a_x$，就是广义程序员节。

**注意：天数的前面不能有前导零，要判一下。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int128 ll;
typedef double db;
const ll N=1e6+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll x,y;
	bool operator<(const Node&rhs)const{
		if(x!=rhs.x)
		  return x<rhs.x;
		return y<rhs.y;
	}
}Q[N];
ll T,n,k,cnt;
ll a[N],b[N];
void check(ll x){
	ll sum=0,p=x,h=1;
	while(x){
		b[++sum]=x%10;
		x/=10;
		h*=10ll;
	}
	if(sum==1)
	  return ;
	ll t=0;
	for(int i=sum;i>=1;i--){
		h/=10;
		t=t*10+b[i];
		p-=h*b[i];
		if(t>n)
		  return ;
		if(!t||!b[i-1])
		  continue;
		if(p<=a[t])
		  Q[++cnt]={t,p};
	}
}
void solve(){
	cnt=0;
	n=read(),k=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	if(k==1){
		puts("0");
		return ;
	}
	ll s=k;
	while(1){
		if(s>5e14)
		  break;
		check(s);
		s=s*k;
	}
	sort(Q+1,Q+cnt+1);
	write(cnt);
	putchar('\n');
	for(int i=1;i<=cnt;i++){
		write(Q[i].x);
		putchar(' ');
		write(Q[i].y);
		putchar('\n');
	}
}
int main(){
	T=read();
	while(T--)
	  solve();
	return 0;
}
```

---

## 作者：xiaoshumiao (赞：4)

显然枚举所有的日期再判断是否是广义程序员日会超时。

所以我们反过来枚举所有 $k$ 的幂，然后将 $k^i$ 数位分离之后枚举月和日之间的断点。

注意特判 $k=1$。
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=3e5+10,M=2e4+10; int a[N],t[20]; pair<int,int>cna[M];//记录答案，用 pair 的原因是方便 sort
int pow10(int k) {
  int ans=1;
  while(k--) ans*=10;
  return ans;
}
void solve() {
  int n,k,mx=0; scanf("%lld %lld",&n,&k);
  for(int i=1;i<=n;i++) scanf("%lld",&a[i]),mx=max(mx,a[i]);
  if(k==1) return puts("0"),void();//特判，否则会死循环
  int anc=0;
  int tmp=mx,cnt=0;
  while(tmp) cnt++,tmp/=10;
  for(int ans=k;ans<=n*pow10(cnt)+mx/*最大的特征值*/;ans*=k) {//枚举特征值
  	int tmp=ans,cnt=0;
  	while(tmp) t[++cnt]=tmp%10,tmp/=10;//数位分离
  	for(int i=1;i<=cnt/2;i++) swap(t[i],t[cnt-i+1]);
  	for(int i=1;i<cnt;i++) {//枚举断点
  	  if(t[i+1]==0) continue;
	  int m=0,d=0;
  	  for(int j=1;j<=i;j++) m=m*10+t[j];
  	  for(int j=i+1;j<=cnt;j++) d=d*10+t[j];
  	  if(m>=1&&m<=n)//是否合法
  	    if(d>=1&&d<=a[m]) cna[++anc]=make_pair(m,d);
	}
  }
  sort(cna+1,cna+anc+1);
  printf("%lld\n",anc);
  for(int i=1;i<=anc;i++) printf("%lld %lld\n",cna[i].first,cna[i].second);
}
signed main() {
  int t; scanf("%lld",&t);
  while(t--) solve();
  return 0;
}
```

---

## 作者：PR_CYJ (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/P10246)
# 思路
这道题我采用了暴力的做法。先找出特征值的最大值，再枚举 $k$ 的自然数次幂，找出可能的月份和日期，同时记录答案，最后排序输出即可。
# 代码
- 变量比较复杂，有很多都是用来拆位的，勿喷。
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
struct lucky
{
	int m,d;
};
inline bool cmp(lucky a,lucky b)
{
	if (a.m<b.m)
		return true;
	if (a.m>b.m)
		return false;
	if (a.d<b.d)
		return true;
	return false;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,k,s=0,maxx=0,nsz=0;
		scanf("%d%d",&n,&k);
		int a[n+10]={};
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),maxx=max(maxx,a[i]);
		if (k==1)
		{
			cout<<0<<endl;
			continue; 
		}
		lucky ot[200010]={};
		int ttmx=maxx,mxs=0,ttnn=n;
		while(ttmx)
		{
			mxs++;
			ttmx/=10;
		}
		while(ttnn)
		{
			nsz++;
			ttnn/=10;
		}
		long long spmx=n*pow(10,mxs)+maxx;//spmx为特征值的最大值 
		for(long long i=1;i<=spmx;i*=k)//枚举 k的自然数次幂 
		{
			if (i<10)//特征值最少两位 
				continue;
			if (i<100)
			{
				int mm=i/10,dd=i%10;
				if (mm<=n&&1<=dd&&dd<=a[mm])//判断日期是否合法 
					ot[++s].m=mm,ot[s].d=dd;
			}
			else
			{
				long long ttii=i,isz=0;
				while(ttii)
				{
					ttii/=10;
					isz++;
				}
				for(int j=1;j<=nsz&&pow(10,j)<i;j++)//枚举月份可能的位数 
				{
					int mm=i/((long long)(pow(10,isz-j))),dd=i%((long long)(pow(10,isz-j)));
					if (mm<=n&&1<=dd&&dd>=pow(10,isz-j-1)&&dd<=a[mm])//dd>=pow(10,isz-j-1)用来判断日期前有无前导零 
						ot[++s].m=mm,ot[s].d=dd;
				}
			}
		}
		sort(ot+1,ot+s+1,cmp);
		printf("%d\n",s);
		for(int i=1;i<=s;i++)
			printf("%d %d\n",ot[i].m,ot[i].d);
	}
}
//ttmx,ttnn,ttii都是用来拆位的变量 
```

---

## 作者：MrPython (赞：2)

可以发现，在极限情况（$k=2$）时，所有可能作为日期的 $k$ 的自然数次幂也不会超过 $64$ 个。

我们对于每个月都枚举一遍所有的 $k^p(p\in \mathbb{N})$，判断其字符串长度是否比表示月份的字符串长度小、前缀是否为月份、去掉表示月的部分（即应该表示日的部分）数值是否小于该月天数以及有无前导 $0$。

本题涉及字符串与整数间的转换较多，力推 [`std::stoll`（字符串转数字）](https://zh.cppreference.com/w/cpp/string/basic_string/stol)、[`std::to_string`（数字转字符串）](https://zh.cppreference.com/w/cpp/string/basic_string/to_string)、[`std::equal`（判断区间是否相等）](https://zh.cppreference.com/w/cpp/algorithm/equal) 等 STL 函数。

```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        size_t n;ui k;cin>>n>>k;
        vector<string> kpow({to_string(k)});
        if (k>1) while (__uint128_t(stoll(kpow.back()))*k<=numeric_limits<uli>::max())
            kpow.push_back(to_string(stoll(kpow.back())*k));
        vector<pair<ui,ui>> ans;
        for (size_t i=1;i<=n;++i){
            string month=to_string(i);
            ui x;cin>>x;
            if (k>1)
            for (string const& j:kpow) if (month.size()<j.size()
                &&equal(month.cbegin(),month.cend(),j.cbegin())){
                    string k(j.cbegin()+month.size(),j.cend());
                    if (k.front()!='0'&&stoll(k)<=x) ans.emplace_back(i,stoll(k));
                }
        }
        cout<<ans.size()<<'\n';
        for (pair<ui,ui> i:ans) cout<<i.first<<' '<<i.second<<'\n';
    }
    return 0;
}
```

---

## 作者：Vitamin_B (赞：2)

# 注意事项
如果你 TLE 并且 $68$ 分，请开 __int128！
# 思路
因为 $\sum a_i$ 很大，所以我们肯定不能枚举日期，我们应该枚举 $k^{i=1,2,3,\dots,\log_k\infin}$，其中 $\infin$ 可以设为 $\max\sum a_i=3\times10^{14}$。然后要枚举月份和日期的分割点就行。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
typedef pair <int, int> pii;
const ll inf = 3e14 + 5;
int t, n,a[300005],  k;
bool flag;
ll month, day;
vector <pii> v;
bool cmp (const pii& a, const pii& b) {
	return a.first != b.first ? a.first < b.first : a.second < b.second;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> k;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i];
		if (k < 2) {
			cout << "0\n";
			continue ;
		}
		v.clear ();
		for (ll i = k; i <= inf; i *= k)
			for (ll j = 10; j <= i; j *= 10) {
				month = i / j, day = i % j;
				if (day != i % (j / 10) && month <= n && day && day <= a[month])
					v.push_back ({month, day});
			}
		sort (v.begin (), v.end (), cmp);
		cout << v.size () << '\n';
		for (pii i : v)
			cout << i.first << ' ' << i.second << '\n';
	}
	return 0;
}
```

---

## 作者：CaiZi (赞：1)

## Exciting Days 题解
**[题目链接](https://www.luogu.com.cn/problem/P10246)**
### 题意理解
求所有满足 $\overline{bc}=k^x$ 的数量，其中 $b\in[1,n]\land c\in[1,a_b]\land 0\le x$。
### 题目分析
直接枚举日期复杂度是爆炸的，考虑枚举 $k^x$，然后把这个数拆成所有可能的 $\overline{bc}$，若 $b\in[1,n]\land c\in[1,a_b]$ 且 $c$ 不包含前导 $0$，则是一种可行答案。把所有答案存下来后，排序即可。特别注意，若 $k=1$ 显然没有任何方案。

$k^x$ 的上限是 $n\times max\{a_i\}$，也就是 $3\times10^{14}$，有可能会爆 ```long long```，需要开 ```__int128```。
### 代码展示
时间复杂度 $O(\sum\log_k(\log_{10}\max\{a_i\}\times n))$，代码如下：
```cpp
#include<bits/stdc++.h>
#define int __int128
#define mx 2e14
using namespace std;
char str;
template<typename T>inline void read(T&num){
	num=0;
	str=getchar();
	while(str<'0'||str>'9'){
		str=getchar();
	}
	while(str>='0'&&str<='9'){
		num=(num<<1)+(num<<3)+(str^48);
		str=getchar();
	}
	return;
}
template<typename T,typename...Ts>inline void read(T&num,Ts&...rest){
	read(num);
	read(rest...);
	return;
}
template<typename T>inline void print(T num){
	if(num>=10){
		print(num/10);
	}
	putchar(num%10+'0');
	return;
}
int t,n,k,a[300001],x,r,w,u,ans;
vector<pair<int,int>>v;
bool flag;
signed main(){
	read(t);
	while(t--){
		read(n,k);
		for(int i=1;i<=n;i++){
			read(a[i]);
		}
		w=k;
		ans=0;
		v.clear();
		if(k==1){
			putchar('0');
			putchar('\n');
			continue;
		}
		while(w<mx){
			r=w;
			x=0;
			u=1;
			while(r!=0){
				x+=r%10*u;
				flag=(r%10!=0);
				r/=10;
				u*=10;
				if(flag){
					if(r<=n&&x<=a[r]){
						ans++;
						v.push_back(make_pair(r,x));
					}
				}
			}
			w*=k;
		}
		sort(v.begin(),v.end());
		print(ans);
		putchar('\n');
		for(int i=0;i<ans;i++){
			print(v[i].first);
			putchar(' ');
			print(v[i].second);
			putchar('\n');
		}
	}
	return 0;
}
```
**[提交记录](https://www.luogu.com.cn/record/150289648)**

---

## 作者：ZettaByte (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10246)

### 题意

给你一年的月份数量和每个月的天数，把一个日期的月和日拼接在一起时会得到一个数，请求出使得拼接后的数是 $k$ 的幂次的所有日期。

### 解法

这题其实很简单，只要枚举 $k$ 的幂次，然后对其进行数位拆分，如果是一个符合要求的日期，那么就放入答案，并不需要逐个枚举日期。

这里说几点需要注意的：

- 当 $k=1$ 时，需要特判，直接输出 $0$，否则会死循环；

- 由于 `long long` 可能存不下，因此我们保险起见，使用 `__int128`；

- 最后一定要对日期排序，否则会答案错误。

#### AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n, k, a[300010], b[110];
struct node { ll m, d; }ret[200010];
bool cmp(node a, node b) { return (a.m != b.m ? a.m < b.m : a.d < b.d); }

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		scanf("%lld%lld", &n, &k);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		if (k == 1) { puts("0"); continue; }
		ll tot = 0; __int128 tmp = k;
		while (tmp <= 1e18)
		{
			__int128 sum = tmp; ll x = 0;
			while (sum)
			{
				b[++x] = sum % 10, sum /= 10;
				ll sum1 = 0; for (int i = x; i >= 1; i--) sum1 = sum1 * 10 + b[i];
				if (b[x] != 0 && sum <= n && sum1 <= a[sum]) ret[++tot] = {sum, sum1};
			} tmp *= k;
		}
		sort(ret + 1, ret + tot + 1, cmp); printf("%lld\n", tot);
		for (int i = 1; i <= tot; i++) printf("%lld %lld\n", ret[i].m, ret[i].d);
	}
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10246)

## 思路

以下 $i$ 均 $1\le i\le n$。

看到最后要凑成的是 $k$ 的自然数次幂的日期，可以想到预处理出 $k$ 所有小于 $3\times 10^{14}$ 的所有值（因为要 $n$  和 $a_i$ 两个数拼）。

记得特殊处理 $1$，不然会死循环。处理完后用 string 类型保存，方便截取。

然后从 $1$ 到 $n$ 循环遍历每个月份，再循环遍历每个广义程序员节。如果这个月份能拼成广义程序员节且去掉月份后的下一位**不为 $0$**（题中要求去除前导 $0$），那么继续判断这个月份能否找出一个符合要求的日期。

在当前遍历到的这个广义程序员节日期中**去除月份位**后，转成整型存储。如果后面的日期 $\le a_i$，那么说明这个月的这天是广义程序员节。计数器 $+1$，并把这个日期用 vector 存储起来。

输出计数器数量。若计数器不为零，那么再次从 $1$ 到 $n$ 循环遍历，并迭代输出这个日期。最后别忘清空变量。

定义 $C$ 为 $1$ 到 $3\times 10^{14}$ 的广义程序员节的总数量，则时间复杂度约为 $\mathcal{O}(Tn\log^2 C)$，尽管常数较大，但仍旧可以通过此题。

- 记得开 long long。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
inline ll read(){
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
void print(ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)print(x/10);
    putchar(x%10+'0');
	return ;
}
const int N=3e5+10;
ll n,k,a[N];
string s[50];
vector<ll>v[N];
inline void solve(){
	n=read(),k=read();
	ll ans=0;
	int cnt=0;
	for(int i=1;i<=n;++i)a[i]=read();
	if(k!=1){//用 to_string() 函数方便些。
		for(ll i=0;pow(k,i)<=(ll)3e14;++i)s[++cnt]=to_string((ll)pow(k,i));
	}
	else s[++cnt]="1";//1 的情况只记录一个就够了。
	for(int i=1;i<=n;++i){
		string now=to_string(i);//月份转 string。
		int len=now.size();
		for(int j=1;j<=cnt;++j){
			if(len>=s[j].size()||s[j][len]=='0'||s[j].substr(0,len)!=now)continue;
        //记得位数减完之后不够了也要特判。
			string str=s[j].substr(len,30);//筛出日期。
			ll tlen=str.size();
			ll tmp=0;
			for(int p=0;p<tlen;++p)tmp=tmp*10+str[p]-'0';//目标日期转 int。
			if(tmp<=a[i]){
				++ans;
				v[i].pb(tmp);
			}
		}
	}
	print(ans);
	puts("");
	if(!ans)return ;
	for(int i=1;i<=n;++i){
		for(auto j:v[i])printf("%d %lld\n",i,j);
		v[i].clear();//多测别忘清空。
	}
	return ;
}
int main(){
	int T=read();
	while(T--)solve();
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/150302758)

---

## 作者：_Jocularly_ (赞：0)

考虑如何枚举天数，如果直接正着暴力选择天数显然太过麻烦，我们利用反向思维，直接枚举自然数次幂后拆分为天数，判断是否合法即可。

注意三点：第一，一千零二十四有可能会被划分为一月二十四日，拆分后注意要判断是否合法。第二，特判为一的时候，如果不，会陷入死循环，当为一是直接输出零即可。第三，数字拆分后是反向的，要变成正的再进行操作。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"//endl效率比\n低 
int t; 
int d[300005];//天数 
int temp[1005];//拆分数要用的 
int n,k;
struct T{
	int m,d;//month,day 
}a[300005];
int all;//总量 
int check(int day,int month,int yuan){//检查是否合法，1024被拆分为1月24即为不合法
	//大体思路为把月份和日拆分后储存在数组里，然后依次和原来的数检查 
	int qwq[1005],qaq[1005],cntq=0,cnta=0;//拆分数组 
	int qd=day,qm=month,qy=yuan;//待拆分数字 
	//基础拆分数字，注意顺序是反的 
	while(qd != 0){
		qwq[++cntq] = qd%10;
		qd/=10;
	}
	while(qm != 0){
		qwq[++cntq] = qm%10;
		qm/=10;
	}
	while(qy != 0){
		qaq[++cnta] = qy%10;
		qy/=10;
	}
	//用reverse把反的变为正的 
	reverse(qwq+1,qwq+1+cntq);
	reverse(qaq+1,qaq+1+cnta);
	if(cntq != cnta) return 0;//如果长度不一样则不合法 
	for(int i=1;i<=cntq;i++){
		if(qwq[i] != qaq[i]) return 0;//有一项对不上则不合法 
	}
	return 1;//返回合法 
}
int cmp(T a,T b){//比较规则，最后输出的时候要按照月份和日来 
	if(a.m != b.m) return a.m < b.m;
	return a.d < b.d;
}
signed main(){
	//提高cin cout效率 
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	//freopen("data.in","r",stdin);
	cin >> t;
	while(t--){
		all = 0;//合法的数量 
		cin >> n >> k;
		for(int i=1;i<=n;i++){
			cin >> d[i];
		}
		if(k == 1){//特判 
			cout << 0 << endl;
			continue;
		}
		/*
		if(n == 1){
			
			continue;
		}*/
		for(int i=1;i<=1000;i++){//枚举正整数次幂 
			int v=pow(k,i),tot=0;
			int yuan = v;//保存 
			if(v < 10) continue;//如果不是两位数，则返回 
			while(v != 0){//拆分 
				temp[++tot] = v%10;
				v/=10;
			}
			reverse(temp+1,temp+tot+1);//同上，要变反为正 
			for(int j=1;j<tot;j++){//分割点
				int month=0,day=0;//月，日 
				for(int k=1;k<=j;k++){//累计月份 
					month = month*10 + temp[k];
				}
				day = yuan - month*pow(10,tot-j);//算出日 
				//cout << qian << " " << hou << " " << yuan <<endl;
				if(month > 0&&month <= n&&day > 0&&day <= d[month]&&check(day,month,yuan)){//如果合法 
					//累计答案 
					a[++all].m = month;
					a[all].d = day;
				}
			}
		}
		sort(a+1,a+1+all,cmp);//按照规则排序 
		cout << all << endl;
		for(int i=1;i<=all;i++){
			cout << a[i].m << " " << a[i].d << endl;
		}
	}
	return 0;
}

```

---

