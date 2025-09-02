# Hard Cut

## 题目描述

给定一个 `01` 字符串 $s$。  
你需要对其进行划分，使得最终把每一段当做二进制数加起来后得到的数是 $2$ 的幂。  
有解输出任意一组解，无解输出 `-1`。

## 样例 #1

### 输入

```
4
00000
01101
0111011001011
000111100111110```

### 输出

```
-1

3
1 3
4 4
5 5

8
1 2
3 3
4 4
5 6
7 7
8 10
11 12
13 13

5
1 5
6 7
8 11
12 14
15 15```

# 题解

## 作者：huangzirui (赞：5)

题意：

给定 $01$ 串，你需要切分成若干个串，满足每个子串和为二的幂次。

$n \leqslant 10^6$

---

巨大讨论题。

虽然我也不懂这种模拟赛风格题为什么会出现在 cf 上。

**结论：对于任意的存在 $1$ 的串都存在一种切分方案使得合法。**

设序列内有 $k$ 个 $1$，我们现在想凑出 $s_k=2^{\lceil \log_2 k \rceil}$。

对于一个比较大的 $k$，我们可以尝试把整个串匀成两半，每边约占一半的 $1$，然后分别凑一个 $2^{\lceil \log_2 k \rceil-1}$ 出来。

可能会出现的问题是：对于 $k=2^t+1$，可能匀下来就需要用 $2^k$ 个 $1$ 得到一个 $2^{k+1}$，这样就不满足我们之前的递归方案了。我们不妨先讨论这种情况。

容易发现我们能使用 $4$ 个 $1$ 凑出 $8$：

我们讨论最左侧的三个位：

- $111$：切割为 $111+1$
- $110$：切割为 $110+1+1$
- $101$：切割为 $101+11$ 或 $101+10+1$。
- $100$：切割为 $100+1+11$ 或 $100+1+10+1$。

于是我们向上递推，就能构造出使用 $2^k$ 个 $1$ 得到 $2^{k+1}$ 的方案。

此外，我们有一个可以从 $k$ 个 $1$ 得到任意 $w\in[k,1.5k]$ 的方法：

讨论最初的两个位，如果是 $11$ 则拆出 $11$，否则拆出 $10+1$，最后总有 $w=k$，拆成若干个 $1$ 即可。

接下来我们讨论所有较小的情况：

- $k=2,3,4,6,7,8,11$，采用上面的方法。
- $k=5$，拆分成 $1111+1$ 或 $101+1+1+1$ 或 $100+1+1+1+1$。
- $k=9$，类似的讨论最左的三个位：
	- $111$：切割出 $111$，接下来使用上面的方法。
   - $110$：切割出 $110$，接下来使用上面的方法。
   - $101$：切割出 $101$，然后我们使用 $4$ 个 $1$ 凑出 $8$，剩下的 $3$ 个 $1$ 分别拆开。
   - $100$：切割出 $100$，接下来使用上面的方法。
- $k=10$，我们使用 $4$ 个 $1$ 凑出 $8$，接下来使用上面的方法。

就做完了。/tuu






---

## 作者：一念之间、、 (赞：3)

## 题意简述

说：给定长度为 $n\le10^6$ 的 $01$ 串，你需要划分成若干个子段，使得将每一段视为一个二进制数之后，加和为 $2$ 的整数次幂。

## 题解

介绍一个随机化做法。

尝试找无解条件，观察样例，全 $0$ 无解，猜测其余情况一定有解。

尝试手动构造，可以发现限制是很松的，比如，一个很简单的想法是，划分成长度为 $1$ 的连续段，此时和为 $1$ 的个数，然后将一些相邻长度为 $1$ 的连续段合并，使得和增加一些，大部分情况是可构造的。

我们找到最小的 $t$ 满足 $2^t$ 大于等于 $1$ 的个数，我们称一定能通过小部分调整构造出 $2^t$ 或 $2^{t+1}$。

贪心的过程是，维护 $rem$ 表示当前和还剩余多少，从左往右扫描，让当前连续段尽可能长的合并，使得和+后缀 $1$ 个数仍然不超过 $rem$。

注意到，当 $1$ 的个数很少时，会有一些情况使得直接贪心构造不合法。

举例：长度为 $5$ 的 $11111$。

但是贪心是思路是正确的，我们尝试在此基础上用随机化加一些扰动以规避特殊情况，具体的，随机 $lim\in[3,5]$，强制要求当前连续段长度 $\le lim$。

对于 $2^t$ 执行 $30$ 次当前做法，对于 $2^{t+1}$ 执行 $30$ 次当前算法，当有解立刻弹出，复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
namespace ifzw{
#define ll long long
#define dd double
#define ull unsigned ll 
#define LL __int128
#define siz(A) ((int)A.size())
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
#define getchar gc
ll read()
{
	char c;
	ll w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	ll ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&(s==t)))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x),pc(op,0);
}
char ST;
//加点随机参数，加点
//放板子。
random_device R;
mt19937 G(R());
int rd(int l,int r){return uniform_int_distribution<int>(l,r)(G);}
vector<array<int,2> >ans;
void print()
{
	cout<<siz(ans)<<"\n";
	for(auto it:ans)cout<<it[0]<<" "<<it[1]<<"\n";
}
const int xx=1e6+5;
int sf[xx],n,v;
char s[xx];
bool run(int rem)
{
	vector<array<int,2> >tan;
	sf[n+1]=0;
	for(int i=n;i>=1;i--)sf[i]=sf[i+1]+(s[i]=='1');
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='0')
		{
			tan.push_back({i,i});
			continue;
		}
		int lim=min(n,i+rd(3,5));
		int nt=0,jc=lim;
		for(int j=i;j<=lim;j++)
		{
			nt<<=1,nt+=(s[j]=='1');
			if(rem-nt<sf[j+1])
			{
				jc=j-1;
				break;
			}
		}
		nt=0;
		for(int j=i;j<=jc;j++)nt<<=1,nt+=(s[j]=='1');
		rem-=nt;
		//~ cerr<<nt<<"@##@\n";
		tan.push_back({i,jc});
		i=jc;
	}
	//~ cerr<<rem<<"@qqq#\n";
	if(rem==0)return ans=tan,1;
	return 0;
}
char ED;
int main(){
	cerr<<abs(&ST-&ED)/1024.0/1024<<"\n";
	#ifdef AAA
	system("ulimit -s 524288");
	cerr<<" stack is on \n";
	#endif 
	//~ freopen("a.in","r",stdin);
	//~ freopen("a.out","w",stdout);
	//从左往右放？
	int T;
	cin>>T;
	while(T--)
	{
		scanf("%s",s+1);
		n=strlen(s+1),v=count(s+1,s+n+1,'1');
		if(v==0)
		{
			puts("-1");
			continue;
		}
		ans.clear();
		if((v&-v)==v)
		{
			for(int i=1;i<=n;i++)ans.push_back({i,i});
			print();
			continue;
		}
		else 
		{
			int ty=1<<(__lg(v)+1);
			//~ cerr<<ty<<"$\n";
			while(!siz(ans))
			{
				int cs=0;
				while((!run(ty))&&(++cs)<=30);
				ty<<=1;
				//~ cerr<<siz(ans)<<"@\n";
				//~ return 0;
			}
			
		}
		print();
	}
	pc('1',1);
	return 0;
}

}signed main(){return ifzw::main();}

```

---

## 作者：dead_X (赞：3)

## 前言
你说得对，但是你说的不对。

自己推的，可能和官方题解有一些区别。
## 思路
重量级结论：只要存在 $1$ 就有解。

记 $1$ 的数量为 $n$，$k$ 为最小的满足 $2^k\geq n$ 的非负整数。

然后我们假设 $n$ 不太小，很小的情况就直接暴力做一下了，显然都是有解的。

我们发现，我们可以将 $0\sim \lfloor\frac{n}{2}\rfloor$ 个数的权值选择为 $2$，剩下选择为 $1$。选择权值为 $2$ 的数就和后一个数分到同一组，选择权值为 $1$ 的数就单独分一组。

我们又发现，我们可以将 $4$ 个 $1$ 加起来弄出 $8$ 的权值，具体方法如下：

- 如果第一个 $1$ 后面是 $0$，则四个 $1$ 的权值分别为 $4,1,2,1$。
- 如果第一个 $1$ 后面是 $1$，则四个 $1$ 的权值分别为 $4,2,1,1$。

我们又发现，我们可以将 $6$ 个 $1$ 加起来弄出 $14$ 的权值，具体方法如下：

- 如果第一/四个 $1$ 后面是 $00$，则六个 $1$ 的权值分别为 $8,1,2,1,1,1$。
- 如果第一/四个 $1$ 后面是 $01$，则六个 $1$ 的权值分别为 $8,2,1,1,1,1$。
- 如果第一/四个 $1$ 后面都是 $1$，则六个 $1$ 的权值分别为 $4,2,1,4,2,1$。

考虑以上三种构造无法解决的情况，只有 $n=5$ 和 $n=9$。

手玩一下发现 $n=5$ 要么拆成 $4,1,1,1,1$，要么拆成 $8,4,2,1,1$，$n=9$ 在此基础上增加一个 $n=4$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
char s[1000003];
int a[1000003];
int n,m,p;
vector<pair<int,int>> ans;
void make_1(){ans.push_back({a[p-1]+1,a[p]}),++p;}
void make_num(int num)
{
	if(a[p+1]-a[p]==num)
		ans.push_back({a[p-1]+1,a[p+1]});
	else	
		ans.push_back({a[p-1]+1,a[p]+num}),
		ans.push_back({a[p]+num+1,a[p+1]});
	p+=2;
	return ;
}
void make_3(){return make_num(1);}
void make_5(){return make_num(2);}
void make_9(){return make_num(3);}
void make_7()
{
	if(a[p+2]-a[p+1]==1)
		ans.push_back({a[p-1]+1,a[p+2]});
	else	
		ans.push_back({a[p-1]+1,a[p+1]+1}),
		ans.push_back({a[p+1]+2,a[p+2]});
	p+=3;
	return ;
}
void make_8()
{
	if(a[p+1]-a[p]==1) make_7(),make_1();
	else make_5(),make_3(); 
}
void make_11(){return make_7();}
void make_14()
{
	if(a[p+1]-a[p]>=3) make_9(),make_3(),make_1(),make_1();
	else if(a[p+1]-a[p]==2) make_11(),make_1(),make_1(),make_1();
	else if(a[p+4]-a[p+3]>=3) make_3(),make_1(),make_9(),make_1();
	else if(a[p+4]-a[p+3]==2) make_1(),make_1(),make_1(),make_11();
	else make_7(),make_7();
	return ;
}
signed main()
{
	for(int T=read();T--;)
	{
		ans.clear(),
		scanf("%s",s+1),p=1,
		n=0,m=strlen(s+1);
		for(int i=1; i<=m; ++i)	
			if(s[i]=='1') a[++n]=i;
		if(n==0){puts("-1");continue;}
		if(n==5)
		{
			int pos=0;
			for(int i=2; i<=5; ++i)
				if(a[i]-a[i-1]>1) pos=i;
			if(pos>0)
			{
				for(int i=1; i<=pos-2; ++i) make_1();
				make_5();
				for(int i=pos+1; i<=5; ++i) make_1();
			}
			else ans.push_back({1,a[4]}),
				ans.push_back({a[4]+1,a[5]});
		}
		else if(n==9)
		{
			int pos=0;
			for(int i=2; i<=9; ++i)
				if(a[i]-a[i-1]>1) pos=i;
			if(pos>=6)
			{
				make_8();
				for(int i=5; i<=pos-2; ++i) make_1();
				make_5();
				for(int i=pos+1; i<=9; ++i) make_1();
			}
			else if(pos>=1)
			{
				for(int i=1; i<=pos-2; ++i) make_1();
				make_5();
				for(int i=pos+1; i<=5; ++i) make_1();
				make_8();
			}
			else ans.push_back({1,a[8]}),
				ans.push_back({a[8]+1,a[9]});
		}
		else
		{
			int val=1;
			while(val<n) val<<=1;
			int two=val-n,one=n-two;
			while(one<4&&two>=8) make_14(),two-=8,one+=2;
			while(two>=4) make_8(),two-=4;
			while(two) make_3(),--two,--one;
			while(one) make_1(),--one;
		}
		if(a[n]<m) ans.push_back({a[n]+1,m});
		printf("%d\n",(int)ans.size());
		for(auto [x,y]:ans) printf("%d %d\n",x,y);
		puts("HaitangSuki");
	}
	return 0;
}
```

---

## 作者：FZzzz (赞：3)

记 $(x,y)$ 为我们需要将一个有 $x$ 个 `1` 的串分成若干段加起来为 $y$。有一个朴素的想法是，初始时我们令 $y$ 为不小于 $x$ 的最小的 $2$ 的次幂，然后直接递归成 $\left(\left\lfloor\dfrac x2\right\rfloor,\dfrac y2\right)$ 和 $\left(\left\lceil\dfrac x2\right\rceil,\dfrac y2\right)$ 下去做。

这样，如果 $x$ 是 $2$ 的次幂，那么 $y=x$ 或 $2x$，否则 $y$ 为不小于 $x$ 的最小的 $2$ 的次幂。问题在于，并不是满足这个条件的 $(x,y)$ 就有解。比如，$(1,2)$，$(2,4)$ 和 $(5,8)$ 都不一定有解。但是我们断言这是仅有的三个特例。

接下来的一个想法是，我们使得递归到 $(5,8)$ 之前就结束递归，然后特判整个序列只有五个 `1` 的情况。也就是说，我们让 $x\le11$ 成为递归边界，在这种情况下我们直接进行构造。

~~然后你可以把多于三个的连续 `0` 缩成三个，这样情况就是有限的，写个爆搜打个表就做完了。~~

我们还是尊重一下构造题，搞个优美点的做法。首先我们解决一种特殊情况。
> 特殊情况 X：$x\le y\le\left\lfloor\dfrac{3x}2\right\rfloor$
>
> $x=y$ 是平凡的。否则 $x\ge2$，找到最左边的两个 `1`，它们要不然组成一个 `11`，要不然组成 `10` 和 `1`，都可以递归到 $(x-2,y-3)$，容易发现仍然属于情况 X。

现在我们来讨论 $x\le11$ 的所有情况。
## $x=11$
此时 $y=16$，适用情况 X。
## $x=10$
此时 $y=16$，递归成 $(4,8)$ 和 $(6,8)$。
## $x=9$
此时 $y=16$，我们考虑从第一个 `1` 开始的三个数字：
- `100`：递归到 $(8,12)$，情况 X；
- `101`：递归到 $(7,11)$；
- `110`：递归到 $(7,10)$，情况 X；
- `111`：递归到 $(6,9)$，情况 X；
 
## $x=8$
$y=8$ 平凡，$y=16$ 递归到两个 $(4,8)$。
## $x=7$
$y=8$ 适用情况 X，但上面还可能递归下来 $y=11$，此时我们递归到 $(3,3)$ 和 $(4,8)$。
## $x=6$
$y=8$ 适用情况 X。
## $x=4$
$y=4$ 平凡，上面递归下来 $y=8$，我们按照与 $(9,16)$ 类似的方法考虑。
- `100`：递归到 $(3,4)$，情况 X；
- `101`：递归到 $(2,3)$，情况 X；
- `110`：递归到 $(2,2)$，平凡；
- `111`：递归到 $(1,1)$，平凡；

## $x=3$
$y=4$，情况 X。
## $x=2$
$y=2$，平凡。
## $x=1$
$y=1$，平凡。

------------
不过我们还需要考虑 $x=5$ 的情况。此时如果五个 `1` 连在一起就分成 `1111` 和 `1`；否则一定存在一个 `100` 或者 `101`，这个连在一起其他全都单独分就可以。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=1e6+5;
int n,s[maxn];
char a[maxn];
vector<int> vec;
vector<pair<int,int>> ans;
int get(int l,int k){
	return vec[s[l-1]+k-1];
}
void solve(int l,int r,int y){
	int x=s[r]-s[l-1];
	if(x>11){
		int p=get(l,x/2);
		solve(l,p,y/2);
		solve(p+1,r,y/2);
	}
	else if(x==y) for(int i=l;i<=r;i++) ans.push_back({i,i});
	else if(y<=x*3/2){
		int p=get(l,1);
		for(int i=l;i<p;i++) ans.push_back({i,i});
		ans.push_back({p,p+1});
		for(int i=p+2;i<=get(l,2);i++) ans.push_back({i,i});
		solve(get(l,2)+1,r,y-3);
	}
	else if(x==10||x==8){
		int p=get(l,4);
		solve(l,p,8);
		solve(p+1,r,8);
	}
	else if(x==9||x==4){
		int p=get(l,1);
		for(int i=l;i<p;i++) ans.push_back({i,i});
		ans.push_back({p,p+2});
		solve(p+3,r,y-((a[p]-'0')<<2|(a[p+1]-'0')<<1|(a[p+2]-'0')));
	}
	else if(x==7){
		int p=get(l,3);
		solve(l,p,3);
		solve(p+1,r,8);
	}
}
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	int T=read();
	while(T--){
		scanf("%s",a+1);
		n=strlen(a+1);
		vec.clear();
		for(int i=1;i<=n;i++){
			s[i]=s[i-1]+a[i]-'0';
			if(a[i]=='1') vec.push_back(i);
		}
		if(!s[n]){
			printf("-1\n\n");
			continue;
		}
		ans.clear();
		if(s[n]==5){
			if(vec[4]==vec[0]+4){
				for(int i=1;i<vec[0];i++) ans.push_back({i,i});
				ans.push_back({vec[0],vec[3]});
				for(int i=vec[4];i<=n;i++) ans.push_back({i,i});
			}
			else for(int i:vec) if(a[i+1]=='0'){
				for(int j=1;j<i;j++) ans.push_back({j,j});
				ans.push_back({i,i+2});
				for(int j=i+3;j<=n;j++) ans.push_back({j,j});
				break;
			}
		}
		else{
			int y=1;
			while(y<s[n]) y*=2;
			solve(1,n,y);
		}
		printf("%d\n",(int)ans.size());
		for(auto x:ans) printf("%d %d\n",x.first,x.second);
		printf("\n");
	}
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：csyakuoi (赞：3)

假设一共有 $c$ 个 $1$ ，$2^{d-1}<c \leq 2^d$ （先把 $c=0$ 判掉）。

然后划分方案很多种，连续 $x$ 个 $1$ 划分到同一段对最终总和的增加量大约是 $2^x$ 。

这个感觉就是很容易有解（因为划分的自由度极高）。

大概分析一下连续 $x$ 个 $1$ 内部划分能够得到什么结果。

$x>10$ 时一定能得到 $x$ 到 $2x$ 范围内的任何数，因为 $2^d<2c$ 我们自然猜想一定存在一种划分使得总和为 $2^d$ 。

但是 $x$ 很小的时候就非常麻烦，看起来要大分类讨论，况且中间的 $0$ 也不好处理，一不小心还会把复杂度写高了。

------------

但是啊，我们还有一种神奇的算法。我们在很久之前就学过它，但是现在用的越来越少，而且使用它会被当成无能的表现。

回忆一下几年前普及组训练的时候，自己最拿手的是什么？最常用的是什么？最喜欢的是什么？？？

每一位教练都会强调它的重要性，但是我们肯定都记不得了。

**dfs+剪枝**

没错，伟大的dfs往往能够避免各种分类讨论。

dfs(i,rem)

表示目前从第 $i$ 位开始，后面还需要 $rem$ 的总和。

如果序列第 $i$ 位是 $0$ 就跳过连续的 $0$ 到下一个 $1$ 。

其它情况：

因为连续 $x$ 个 $1$ 划分到同一段对最终总和的增加量大约是 $2^x$ 。

所以我们最多允许长度 $15$ 的划分。

直接枚举 $j=1->15$ 搜索，在判一下末尾。

但是这样会tle。

如果所需要的**增加量**（即 $2^d-c$ ）非常大的话就会在最后一段几个位置一直搜，导致tle。

所以，当所需增加量大于20的时候倒过来搜（ $j=15->1$ ）。

最后再加个特判：前面一堆连续的 $0$ 最后连续 $5$ 个 $1$ 的情况。

这个凑不出 $8$ ，于是直接 $15+1$ 。

做完了。

代码：

https://codeforces.com/contest/1684/submission/157757076

---

## 作者：PosVII (赞：2)

## 前言

轻取构式构造。

无脑但是复杂度较劣的算法，复杂度大概 $O(2^4 \times 4 \times n)$，反正能过。

## 题解

设 $1$ 的数量为 $m$。

发现样例的无解只有全 $0$ 的情况，然后手造数据都有解，根据传统艺能猜测非全 $0$ 一定有解。

基于上面的结论可以证明，如果有 $k$ 个 $1$，可以凑出 $[k,\lfloor \frac{3k}{2} \rfloor]$ 以内的所有数，证明如下：

那么考虑不同的 $1$ 形成了大小分别为 $a_{1},a_{2},...,a_{k}$ 的联通块，此时最劣的情况是每个联通块之间只有一个 $0$，且最后一个连通块后没有 $0$。

我们要求每个 $1$ 只能作为 $1$ 或 $2$ 算入答案，我们发现在这样最劣的情况下，我们最多可以取 $\lceil \frac{a_{1}}{2} \rceil + \lceil \frac{a_{1}}{2} \rceil + ... + \lfloor \frac{a_{k}}{2} \rfloor \ge \lfloor \frac{k}{2} \rfloor$ 个 $2$。

如果再让每个 $1$ 也能作为 $4$ 算入答案后，可以猜测可以凑出范围一定会变大，如果你打个对拍的程序的话，你会发现除了 $11111$ 和类似的情况，每次划分的字段长度 $\leq 3$ 也有解。

进一步的，我们使每次划分的字段长度 $\leq 4$，发现就可以完美求出所有情况的解。

但是 $n$ 很大，数组存不下怎么办？考虑上述的 dp 除了部分 $1$ 的数量 $\leq 5$ 的字符串以外，都能求出使所有 $1$ 的和等于 $2^{\lfloor \log_2 k \rfloor +1}$ 的方案。那么考虑从整体开始分治，例如目前正在处理第 $[1,m]$ 个 $1$ 的方案，那么我们把它分治为 $[1,mid],[mid+1,m]$ 再处理，直到区间长度 $\leq 15$ 的时候就可以直接 dp 处理了，这样就不需要这么多分讨了，而那些特殊情况，我们根本就不会递归到它。

可能字符串本身 $1$ 的数量就 $\leq 5$，就直接 dp 处理掉就行了，影响不大。

最后记得把没用上的区间补上。

---

## 作者：I_am_Accepted (赞：2)

题意：给定长度 $\le 10^6$ 的 01 串，你需要划分成若干子串，满足每个子串看作二进制数之和为 $2$ 的幂。

* * *

设 $f(x)(x\in\mathbb N^+)$ 为不小于 $x$ 的最小 $2$ 的幂，即 $f(x)=2^{\lceil\log_2 x\rceil}$。

设 $g(x,y)$ 表示用 $x$ 个 `1` 构成的串，划分后和为 $y$ 的构造问题，以及 $g(x)=g(x,f(x))$。

以下约定 $c$ 为正整数。

**结论 A**：对于任意 $c$，$\exists d,g(c,d)$ 有解，且当 $c\ne 5$ 时 $g(c)$ 有解。

以下的构造即为此结论的证明。

尝试解决 $g(c)$，我们尝试分治：将序列分为左右两半使得 `1` 个数尽量相等，分别做 $g(\lfloor\frac{c}{2}\rfloor,\frac{f(c)}{2}),g(\lceil \frac{c}{2}\rceil,\frac{f(c)}{2})$。

这个分治**几乎**是对的，问题有三：

* $c$ 过小无法分治。
* 分治之后不是子问题，即 $f(\lfloor\frac{c}{2}\rfloor)\ne \frac{f(c)}{2}$。
	* 不考虑右半边是因为 $\forall c>1, f(\lceil \frac{c}{2}\rceil)=\frac{f(c)}{2}$。
* 分治之后有 $g(5)$。

对于第一个问题，我们有：

* * *

**结论 B**：对于任意 $c$，$\forall d\in \mathbb Z\cap [c,\frac{3}{2}c],g(c,d)$ 有解。

构造：将相邻的 `1` 两两配对，对于每对都可以：

* 拆成 `1+1`，和为 $2$。
* 拆成 `10+1` 或 `11`（具体看两个 `1` 是否相邻），和为 $3$。

证毕。

* * *

所以我们能直接解决 $\forall c\in [1,4],g(c)$。

接下来第二个问题只考虑 $c>5$ 的情况。

此时 $f(\lfloor\frac{c}{2}\rfloor)\ne \frac{f(c)}{2}\iff\exists k\in\mathbb N,c=2^k+1$。这样我们要解决 $g(2^{k-1},2^k)$，用下方的结论可以轻松解决：

* * *

**结论 C**：$g(4,8)$ 有解。

按最左边的 `1` 出现位置紧跟的两个字符分类：

* `11`：拆成 `111+1`。
* `10`：拆成 `110+1+1`。
* `00`：拆成 `100+` $g(3,4)$，可用结论 B。
* `01`：拆成 `101+` $g(2,3)$，可用结论 B。

证毕。

* * *

接下来只有第三个问题了。

我们先来构造 $c=5$ 的解（此时不能保证和是 $f(5)=8$，有可能是 $16$）。

如果 $5$ 个 `1` 都紧挨，那划分 `1111+1`，和为 $16$。

否则，一定存在 `100` 或 `101` 作为子串，将其划分出来剩下的一位一位划分即可，和为 $8$。

接下来，我们证明 $\forall c\in\{9,10,11\},g(c)$ 有解，就完结撒花了。

$c=10$：重新划分，分成 $g(4,8)$ 和 $g(6)$。

$c=11$：重新划分，分成 $g(4,8)$ 和 $g(7)$。

接下来 $c=9$，类似结论 C 的证明，按第一个 `1` 紧跟的两个字符分类：

* `11`：拆成 `111+` $g(6,9)$，结论B。
* `10`：拆成 `110+` $g(7,10)$，结论B。
* `00`：拆成 `100+` $g(8,12)$，结论B。
* `01`：拆成 `101+` $g(4,8)$ `+` $g(1)$ `+` $g(1)$。

**总结**：

分治时分出 $2$ 的幂要特判。

$c=5$ 害群之马。

结论 B 搞小数据。

---

