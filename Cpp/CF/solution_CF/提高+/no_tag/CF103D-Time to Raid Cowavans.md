# Time to Raid Cowavans

## 题目描述

众所周知，地球上最聪明的生物当然是奶牛。火星外星人以及许多其他外星智慧文明早已得出了这个结论。

有时，奶牛们会聚集成“牛队”。这似乎是季节性的现象。但在这段时间里，奶牛们会变得被动，对外界刺激反应迟钝。对于火星科学飞碟来说，牛队是绝佳的目标，这正是大规模绑架的好时机，或者用火星人的话说，就是“突袭”。简单来说，牛队就是一排排列的奶牛。

如果我们用正整数 $1$ 到 $n$ 给牛队中的所有奶牛编号，那么我们可以形式化描述一种流行的绑架模型，称为 $(a,b)$-牛队突袭：首先绑架编号为 $a$ 的奶牛，然后是编号为 $a+b$ 的奶牛，再然后是编号为 $a+2b$ 的奶牛，依此类推，直到被绑架的奶牛编号超过 $n$ 为止。在一次突袭过程中，奶牛不会重新编号。

外星人很想把所有奶牛都带上他们好客的飞船，但遗憾的是，货舱空间非常有限。研究人员已知牛队中每头奶牛的质量，并设计了 $p$ 种 $(a,b)$-突袭方案。现在他们想要分别计算每种方案下，飞船上能装载的牛肉总质量。所有方案互不影响，在计算过程中奶牛不会真的被绑架。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 3
2
1 1
1 2
```

### 输出

```
6
4
```

## 样例 #2

### 输入

```
4
2 3 5 7
3
1 3
2 3
2 2
```

### 输出

```
9
3
10
```

# 题解

## 作者：E_huan (赞：13)

### 根号分治+离线卡空间
这类一步跳多少的题一般都是根号分治。

扩展的说，当变量 $a$ 和变量 $b$ 乘积是定值，且既有复杂度关于 $a$ 的做法又有复杂度关于 $b$ 的做法的时候，常常采用根号分治平衡复杂度。

在本题，因为跳的步数与跳的长度的积一定（由于步长未必是 $n$ 的因数，所以不是积严格相等，但是基本相同、一个数量级），如果有一个关于步长的做法、一个关于步数的做法，就可以根号分治完美解决这题。

发现对于 $k$ 不超过 $\sqrt n$ 的部分，最多 $\sqrt n$ 个不同的 $k$，可以预处理（起点预处理在 $[0,k-1]$ 即可，不在这个范围就差分求，因为 $t$ 模 $k$ 的余数一定在这个范围）。对于超过 $\sqrt n$ 的部分，暴力模拟跳，最多 $\sqrt n$ 步。

但是发现预处理的空间开不下。原因是对于每个不超过 $\sqrt n$ 的步长都开一个前缀和数组的话需要 $O(n \sqrt n)$ 的空间，才能满足每次在线的查询。

考虑将询问离线，按照 $k$ 排序，对于所有不超过 $\sqrt n$ 的 $k$ 预处理一次，然后把所有 $k$ 值等于当前预处理的 $k$ 值的询问的答案全部求出。每次只需要一个前缀和数组，空间复杂度降到 $O(n)$，时间复杂度仍是  $O(n\sqrt n)$。

### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300010;
int n,m,a[N],B;
struct node
{
    int t,k,id;
    bool operator<(const node &w)const{return k<w.k;}
}q[N];
ll s[N],ans[N];
inline void init(int k)
{
    for(int i=0;i<k;i++) s[i]=a[i];
    for(int i=k;i<=n;i++)
        s[i]=a[i]+s[i-k];
}
int main()
{
    scanf("%d",&n); B=sqrt(n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++) 
        scanf("%d%d",&q[i].t,&q[i].k),q[i].id=i;
    sort(q+1,q+m+1);
    for(int i=1;i<=m;i++)
    {
        int t=q[i].t,k=q[i].k;
        if(q[i].k>B)
        {
            ll sum=0;
            while(t<=n)
            {
                sum+=a[t];
                t+=k;
            }
            ans[q[i].id]=sum;
        }
        else{
            if(k!=q[i-1].k) init(k);
            int ed=t+((n-t)/k)*k;
            ans[q[i].id]=s[ed]-((t>=k)?s[t-k]:0);
        }
    }
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：louhao088 (赞：6)


## 分析

这是一道根号分治简单题

本题是[哈希冲突](https://www.luogu.com.cn/problem/P3396)的不带修版本。

但是很遗憾，本题卡空间，

如果我们用哈希冲突的方式来做需要$n \sqrt n$的空间，会炸

但是我们发现他不带修，我们可以用离线方式处理。


## 具体方法
------------

对于小于$\sqrt n$的 k,先用$n\sqrt n$的方法处理全部答案，再按t排序，把小于t的减掉，类似于莫队的算法。

```cpp
struct node
{
	int x,y,id;
}a[maxn];
bool cmp(node a,node b){return a.x<b.x;}
int main()
{
	t=sqrt(n);
	for(int i=1;i<=n;i++)
	{
		v[i]=read();
		for(int j=1;j<=t;j++)
			s[j][i%j]+=v[i];
	}
	sort(a+1,a+m+1,cmp);d=0;
	for(int i=1;i<=m;i++)
	{
		if(a[i].y<=t)
		{
			while(a[i].x>d)
			{
				for(int j=1;j<=t;j++)s[j][d%j]-=v[d];d++;
			}
			ans[a[i].id]=s[a[i].y][a[i].x%a[i].y];
		}
   	}
}
```


------------

而对于大于$\sqrt n$的部分则按原先方法暴力处理，时间复杂度$n\sqrt n$
```cpp
for(int i=1;i<=m;i++)
{
  	if(a[i].y>t)
	{
		for(int j=a[i].x;j<=n;j+=a[i].y)
			ans[a[i].id]+=v[j];
	}
}
```


------------


这样就完成了，总体复杂度$n\sqrt n$，空间$O(n)$，但是注意要开$long long$，最好手动开个$O(2)$。








---

## 作者：OldVagrant (赞：3)

## 题意
给定一个长为 $n$ 的序列 $a$ ，有 $m$ 次询问，每次询问给出一对 $t,k$，
求 $a_t+a_{t+k}+a_{t+2k}+ ...+a_{t+pk}$,其中 $t+pk\leq n$ 且 $t+(p+1)k>n$。  
数据范围： $1\leq n,m\leq3\times 10^5,0\leq a_i\leq10^9$。
## Solution
做这道题之前建议先做一下[P3396-哈希冲突](https://www.luogu.com.cn/problem/P3396)，和这道题挺像的。
我是做完那道再来看这道题的，所以就直接照搬了那个的做法，$O(n\sqrt{n})$ 预处理比 $\sqrt{n}$ 小的模数所包含的池子的和 ，$O(1) \sim O(\sqrt{n})$ 查询。因为这个题的 $t$ 不一定是 比 $k$ 小的，所以查询时要先把多算的减掉，然后再 $O(1)$ 加上预处理的和。   
~~然后喜提TLE#71~~  。  
如果你点进原题，看看标签，就会发现标签上还有个 ```排序``` ，这启发我们用一种离线的做法，离线对询问进行排序，~~然后我第一反应是莫队，又想了想才发现我莫队根本不会用~~。     
先预处理一个数组 $sqzh$，$sqzh[k][i][j]$ 表示前 $k$ 个块内下标 $\mod i \equiv j$ 的数的总和，大小就开到 $sqzh[\sqrt{n}][101][101]$ （个人习惯下标从1开始）就好了，多开没用还会MLE，开小了跑得慢可能TLE。
同时预处理一个数组 $qzh$,$qzh[i][j]$ 表示所有下标 $\mod i \equiv j$ 的数的总和，这个要开到 $qzh[\sqrt{n}+1][\sqrt{n}+1]$。     
然后考虑对询问进行排序，以 $k$ 为第一关键字升序排序，对于 $\forall k\in[1,100]$,先找到 $t$ 所在的块的左端点 $l[belong_t]$，然后把$[l[belong_t],t)$ 之间所有下标满足 $i \equiv t(\mod k)$ 的数减掉,再差分一下预处理出来的东西，加到答案里即可。对于 $\forall k\in (100,\sqrt{n}]$ ，先判断一下 $t$ 在序列的哪半部分，如果在右半部分就直接暴力加，左半部分就先给答案加上之前预处理出来的 $qzh[k][t\mod k]$,然后减掉多余的部分即可。对于更大的 $k$ ，直接朴素加。
这样做的时间复杂度是 $O((n+m)\sqrt{n})$,就是常数可能有点大，~~但是超级快读快写会解决一切~~。
## Code
注释掉的代码为超级快读/快写，有需要可以自行去掉。
```c
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rint register int
#define gc getchar
#define pc(x) putchar(x)
int n,m,l[550],r[550],a[300001],len,num,pos,s,x,y,st,px,p[300001];//p数组即上文的belong，存储每个位置属于编号为多少的块。
ll qzh[550][550],sum,ans,d[300001],sqzh[550][101][101];//d为结果数组，不想再排一遍序
/*const int LEN=1<<21;
char BUF[LEN],*Pin,*Pin_last,PUF[LEN],*Pout=PUF,*Pout_last=PUF+LEN-1;
inline char gc(){
	return Pin==Pin_last&&(Pin_last=(Pin=BUF)+fread(BUF,1,LEN,stdin),Pin==Pin_last)?EOF:*Pin++;
}
inline void pc(char x){
	if(Pout==Pout_last) fwrite(PUF,1,Pout-PUF,stdout),Pout=PUF;
	*Pout++=x;
}*/
inline int read(){
	int x=0;
	char ch=gc();
	while(ch<'0'||ch>'9') ch=gc();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=gc();
	return x;
}
void write(ll a){
	if(a>9) write(a/10);
	pc(a%10+48);
}
struct query{
	int a,b,id;
}q[300001];
bool cmp(query aa,query bb){
	return aa.b<bb.b;
}
signed main(){
	n=read(),len=sqrt(n),num=n/len,q[0].a=q[0].b=300001;
	for(rint i=1;i<=num;i++) l[i]=r[i-1]+1,r[i]=r[i-1]+len;
	if(r[num]!=n) ++num,l[num]=r[num-1]+1,r[num]=n;
	for(rint i=1;i<=num;i++) for(rint j=l[i];j<=r[i];j++) a[j]=read(),sum+=a[j],p[j]=i;
	qzh[1][0]=sum,m=read();
	for(rint i=2;i<=len;i++) for(rint j=0;j<i;j++) for(rint k=j;k<=n;k+=i) qzh[i][j]+=a[k];
	for(rint i=1;i<=100;i++){
		for(rint j=0;j<i;j++){
			st=j;
			for(rint k=1;k<=num;k++){
				while(st<=r[k]) sqzh[k][i][j]+=a[st],st+=i;
				sqzh[k][i][j]+=sqzh[k-1][i][j];
			}
		}
	}//两个数组的预处理
   for(rint i=1;i<=m;i++) q[i].a=read(),q[i].b=read(),q[i].id=i;
	sort(q+1,q+m+1,cmp),pos=0,s=n>>1;
	for(rint i=1<<18;i;i>>=1) if(pos+i<=m&&q[pos+i].b<=len) pos+=i;//手写二分，找到最后一个 k<=sqrt(n) 的位置
	for(rint i=1;i<=pos;i++){
		x=q[i].a,y=q[i].b,ans=0;
		if(y<=100){
			px=p[x],st=x%y,x-=y;
			while(x>=l[px]) ans-=a[x],x-=y;
			ans+=sqzh[num][y][st]-sqzh[px-1][y][st]; //小于100就去掉多余的部分然后直接把之前处理好的加上去
		}else{//否则判断一下然后暴力去加
			if(x>s) for(rint j=x;j<=n;j+=y) ans+=a[j];
			else{
				ans+=qzh[y][x%y],x-=y;
				while(x>=0) ans-=a[x],x-=y;
			}
		}d[q[i].id]=ans;
	}for(rint i=pos+1;i<=m;i++){//直接暴力
		ans=0;
		for(rint j=q[i].a;j<=n;j+=q[i].b) ans+=a[j];
		d[q[i].id]=ans;
	}for(rint i=1;i<=m;i++) write(d[i]),pc('\n');
	//fwrite(PUF,1,Pout-PUF,stdout);
	return 0;
}
```




---

## 作者：vijone (赞：3)

题目链接：[link](https://www.luogu.com.cn/problem/CF103D)

目前本题的题解都是离线的，但这是一篇在线解法的题解。

本人的在线解法的时间大约是离线解法的两到三倍，且较为玄学，但大概会更容易理解。

使用根号分治来做，设阈值为 $T$

这个做法空间复杂度为 $O(T\sqrt{n})$ ，对于 $k\lt T$ 的单个询问，时间复杂度为 $O(\sqrt{n})$，对于 $k\gt T$ 的单个询问，时间复杂度为 $O(\frac{n}{T})$。

首先转化题意：将数列 $a[\;]$ 按下标 $i\mod\;k$ 分 $k$ 组，则我们要求 $t \mod\;k $ 组的 所有在 $t$ 后面的数 和 $t$ 的和（即某一组的某个后缀）。

先考虑一个会 MLE 的做法（空间复杂度 $O(T*n)$ )，将 $k\lt T$ 的部分预处理：枚举小于阈值的数 $l$，将数列按 $\mod\;l$ 分成 $l$ 组，每一组做一个前缀和。可以用 vector 减少空间浪费。询问时，若 $k\lt T$ 则在预处理的前缀和中 $O(1)$ 计算；否则，用 $O(\frac{n}{T})$ 暴力计算。

进行优化：将上文所述的每个组内的数 **分块** ，在 vector 里，不再存每个数的缀合，而是 每个块的和 的前缀和。询问时，若 $k\lt T$ 则将整组的和 减去 $t$ 所在的块的前一块的前缀和 ，记为 $ans$ ，再将 $ans$ 减去 $t$ 所在的块内在 $t$ 前面的数即可；若 $k\gt T$ ，依然暴力计算。

代码，注意对块的处理等细节：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int e=300010;
int n,m;
int p,t,k;
ll ans,a[e];
vector<ll>sum[110][110];
ll ss[e];
int T=0;
int tot=0;
ll tmp[e],tmp2[e];
int kuai(int x)
{
	return (x-1)/T;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		ss[i]=ss[i-1]+a[i];
	}
	T=ceil(sqrt(n));
	ll tt=0;
	for(int i=2;i<=min(n,108);i++)
	{
		for(int j=0;j<i;j++)
		{
			tot=0;
			for(int l=0;l*i+j<=n;l++)
			{
				tmp[++tot]=a[l*i+j];//将分成的组先存在tmp数组中
			}
			tt=0;
			for(int l=1;l<=tot;l++)
			{
				tt+=tmp[l];
				if(l%T==0)//块长要设为T即sqrt(n)，否则空间可能会退化。
				{
					tmp2[l/T]=tt;
				}
			}
			tmp2[tot/T+1]=tt;
			for(int l=0;l<=tot/T;l++)
			{
				sum[i][j].push_back(tmp2[l+1]);
			}
		}
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		ans=0;
		scanf("%d%d",&t,&k);
		p=t;
		if(k==1)//可以不特判 1 的。
		{
			ans=ss[n]-ss[t-1];
			printf("%lld\n",ans);
			continue;
		}
		if(k>101)//大于阈值 暴力
		{
			while(p<=n)
			{
				ans+=a[p];
				p+=k;
			}
			printf("%lld\n",ans);
		}
		else
		{
			int t1=t/k,t2=t%k;//t1表示t在组里是第几个
			int len=sum[k][t2].size();
			ll ans1=0;
			if(kuai(t1)!=0)ans1=sum[k][t2][len-1]-sum[k][t2][kuai(t1)-1];
			else ans1=sum[k][t2][len-1];
			ll ans2=0;
			for(int q=t2+k*(T*kuai(t1));q<=n and q<t;q+=k)//ans2是 在 t 那一块中的，在 t 前面的数的和
			{
				ans2+=a[q];
			}
			printf("%lld\n",ans1-ans2);
		}
	}
	return 0;
}
```





---

## 作者：Alarm5854 (赞：3)

这道题目和[哈希冲突](https://www.luogu.com.cn/problem/P3396)很像，都是用了根号分治的思想：设阈值为 $s$，若 $k>s$，就暴力；否则，就预处理。时间复杂度为 $O(n\times(\dfrac{n}{s}+s))$，取 $s=\sqrt{n}$ 最优，为 $O(n\sqrt{n})$。

但是，这道题目与哈希冲突的区别就在于这道题目如果用哈希冲突的方法预处理，那么就需要处理的是以 $i$ 开头，步长为 $j$，一直加到 $n$ 的和，空间复杂度为 $O(n\sqrt{n})$，需要 $1.11\text{GB}$ 的空间，所以，空间被卡了。

不过，这道题目与哈希冲突还有一个区别，就是这道题目的区间完全是静态的，没有修改操作，所以可以离线处理。先把所有的询问都记录下来，然后，对于 $k_i>s$ 的询问，直接暴力；否则，把 $k_i$ 相同的记录到同一个 `vector` 中，然后枚举 $k$，如果 $k$ 所在的 `vector` 不空，那么就用临时数组处理，这样空间复杂度就降为 $O(n)$ 了。

```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
#include<vector>
#include<cstring>
#define ll long long
using namespace std;
const ll N = 3.2e5 + 10;//为了后面写得方便一些，数组开大了
inline ll read() {
	ll x = 0, f = 1; char c;
	while (!isdigit(c = getchar())) f -= (c == '-') * 2;
	while (isdigit(c)) x = x * 10 + f * (c - 48), c = getchar();
	return x;
}
vector<ll> vec[522];
ll n, m, res, a[N], t[N], k[N], ans[N], f[N];
int main() {
	n = read();
	for (ll i = 1; i <= n; ++i) a[i] = read();
	m = read();
	for (ll i = 1; i <= m; ++i) t[i] = read(), k[i] = read();
	for (ll i = 1; i <= m; ++i) {
		if (k[i] >= 500) for (ll j = t[i]; j <= n; j += k[i]) ans[i] += a[j];//暴力处理
		else vec[k[i]].push_back(i);//记录询问编号
	}
	for (ll i = 1; i < 500; ++i) {
		if (vec[i].empty()) continue;
		memset(f, 0, sizeof(f));
		for (ll j = n; j; --j) f[j] = a[j] + f[j + i];//倒序统计和
		while (!vec[i].empty()) ans[vec[i].back()] = f[t[vec[i].back()]], vec[i].pop_back();
	}
	for (ll i = 1; i <= m; ++i) printf("%I64d\n", ans[i]);
	return 0;
}
```

---

## 作者：苏联小渣 (赞：2)

一眼根号分治。

前置知识 & 例题：根号平衡、[CF797E Array Queries](https://www.luogu.com.cn/problem/CF797E)

根号分治的思想就是用根号进行平衡，$\le \sqrt{n}$ 的用一种方法预处理，$\ge \sqrt{n}$ 的直接暴力，暴力次数不超过 $\sqrt{n}$。

我们发现这题和那题很像，因为如果 $k \ge \sqrt{n}$ 执行次数不会超过 $\sqrt{n}$，而 $k \le \sqrt{n}$ 时可以暴力 dp 预处理。

这题我们定义 $f_{i,j}$ 表示 $k \le \sqrt{n}$ 时的答案。容易写出转移方程 $f_{i,j}=f_{i+j,j}+a_i$。

贴一个暴力根号分治的代码：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, block, t, k, ans, a[300010], f[300005][600];
signed main(){
	scanf ("%lld", &n);
	block = sqrt(n);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
	}
	for (int i=n; i>=1; i--){
		for (int j=1; j<=block; j++){
			f[i][j] = f[i+j][j] + a[i];
		}
	}
	scanf ("%lld", &m);
	for (int i=1; i<=m; i++){
		scanf ("%lld%lld", &t, &k);
		if (k <= block){
			printf ("%lld\n", f[t][k]);
		}
		else{
			ans = 0;
			for (int j=t; j<=n; j+=k){
				ans += a[j];
			}
			printf ("%lld\n", ans);
		}
	}
	return 0;
}
```

可是空间炸了，考虑优化。

我们发现 dp 过程中第二维的 $j$ 可以压掉，因为转移方程中第二维除了 $j$ 没有其他参数。所以我们把询问离线下来，以 $k$ 为关键字排序。当 $k \le \sqrt{n}$ 时我们用一个一维数组记录下原本第二维为 $k$ 的答案，然后 $k$ 变化后直接更新答案即可。时间复杂度 $O(n \sqrt{n})$，这样就卡过去了！

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, block, s, a[300010], f[320010], ans[300010];
struct node{
	int t, k, id;
	bool operator < (const node &A) const{
		return k < A.k;
	}
}q[300010];
signed main(){
	scanf ("%lld", &n);
	block = sqrt(n);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
	}
	scanf ("%lld", &m);
	for (int i=1; i<=m; i++){
		scanf ("%lld%lld", &q[i].t, &q[i].k);
		q[i].id = i;
	}
	sort (q+1, q+m+1);
	for (int i=1; i<=m; i++){
		if (q[i].k > block){
			s = 0;
			for (int j=q[i].t; j<=n; j+=q[i].k){
				s += a[j];
			}
			ans[q[i].id] = s;
			continue;
		}
		if (q[i].k != q[i-1].k){
			memset(f, 0, sizeof(f));
			for (int j=n; j>=1; j--){
				f[j] = f[j+q[i].k] + a[j]; 
			}
		}
		ans[q[i].id] = f[q[i].t];
	}
	for (int i=1; i<=m; i++){
		printf ("%lld\n", ans[i]);
	}
	return 0;
}

```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF103D)
## 思路
根号分治板子题。

但是由于毒瘤出题人卡空间，正常的根号分治会爆空间。

所以我们要么 $\verb!vector!$ 优化空间，要么离线按 $k$ 值排序。

为了方便，我选择离线做法。

+ 若当前的 $k$ 值小于等于 $\sqrt n$，那么我们直接预处理，时间复杂度 $O(n)$，空间复杂度 $O(\sqrt n)$。
+ 若当前的 $k$ 值大于 $\sqrt n$，直接暴力枚举，时间复杂度 $O(\sqrt n)$。

由于不同的需要预处理的 $k$ 值最多只有 $\sqrt n$ 个，所以预处理最多执行 $\sqrt n$ 次，且暴力枚举的时间复杂度严格小于等于 $O(\sqrt n)$，所以时间复杂度约为 $O(m \sqrt n+n \sqrt n)$，可以通过本题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=6e5+10;
int a[N],f[N],n,ans[N];
struct node{int l,r,id;}q[N];
inline bool cmp(node x,node y){return x.r<y.r;}
inline void ycl(int k){
    memset(f,0,sizeof(f));
    for (int i=n;i;--i)
        f[i]=f[i+k]+a[i];
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int m;cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i];
    cin>>m;
    for (int i=1;i<=m;++i) cin>>q[i].l>>q[i].r,q[i].id=i;
    sort(q+1,q+m+1,cmp);
    for (int i=1;i<=m;++i){
        if (q[i].r!=q[i-1].r && q[i].r<=500) ycl(q[i].r);
        if (q[i].r<=500 && q[i].l<=n) ans[q[i].id]=f[q[i].l];
        else{
            int sum=0;
            for (int j=q[i].l;j<=n;j+=q[i].r) sum+=a[j];
            ans[q[i].id]=sum;
        }
    }
    for (int i=1;i<=m;++i) cout<<ans[i]<<'\n';
    return 0;
}
```


---

## 作者：论文 (赞：1)

利用剩余系的性质，可以给出一种在线的分块做法。

首先设置块长，取一个最小的 $p\in\mathbb{P}$ 使得 $p\ge \sqrt n$ 。通过粗略地估计素数的分布密度，知道 $p$ 和 $\sqrt n$ 大小差距不大，因此计算渐进复杂度时可以将 $p$ 认为是 $\sqrt n$ ，同时 $p$ 的选取并不需要过多的时间。

考虑每一次查询：

若 $b\ge p$ ，那么最多跳 $p$ 步。时间 $O(p)$ 。

反之，$\gcd(p,b)=1$，可知 $\{a,a+b,a+2b,\cdots,a+(p-1)b\}$ 构成一个模 $p$ 意义下的完系，所以最多跳 $p$ 步，就可以跳到一个位置 $pos$ 使得 $pos\equiv 1\mod p$ 。因此我们预处理出 $pre_{ij}$ 代表从第 $i$ 个块的左端点开始，步长为 $j\le p-1$ 的后缀和，$O(1)$ 查询。时间 $O(p)$ 。

对于后缀和的预处理，同样对于每个状态，最多只需要 $p$ 步可以到达另一个 $i$ 比它大的状态，递推即可。时间 $O(p^3)$ 。

因此总时间 $O(q\sqrt n +n^{\frac{3}{2}})$ 。

---

## 作者：Strelitzia (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF103D)

---

知识：根号分治。~~比较简单？？？？~~


从 _《根号分治——不只是分块》_ 中的例题一~~被称为水题~~。

时间复杂度是 $O(n\sqrt n)$，是可以过的。

对于第一种情况 $ k \leq \sqrt n$ 暴力跳会炸。

其他情况就暴力跳，最多也是$\sqrt n$。

如果 $k \leq \sqrt n$，只有 $\sqrt n$ 种，对于每一个 $k$，统计一个后缀和就行了。

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char buf[1 << 23],*p1 = buf,*p2 = buf,obuf[1 << 23],*O = obuf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 18,stdin),p1 == p2) ? EOF : *p1 ++)
#define putchar(x) *O ++ = x

template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
int read() {
	int x = 0, f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	return x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
	
template<typename T>T Abs(T x) {return x < 0 ? -x : x;}
template<typename T>T Min(T x,T y) {return x < y ? x : y;}
template<typename T>T Max(T x,T y) {return x > y ? x : y;}

const int N = 3e5 + 5;

int n,m;
int a[N];
long long ans[N],sum[N + 1000];

struct node {
	int b,k,id;
	bool operator <(node x) const {return k < x.k;}
}ask[N];

int main () {
	read(n);
	for (int i = 1 ; i <= n ; ++ i)
		read(a[i]);
	read(m);
	for (int i = 1 ; i <= m ; ++ i) {
		read(ask[i].b);read(ask[i].k);ask[i].id = i;
	}
	sort(ask + 1,ask + 1 + m);
	int t = sqrt(n);
	int i = 1;
	for (i = 1 ; i <= m && ask[i].k <= t ; ++ i) {
		int tmp = ask[i].k;
		for (int k = n ; k >= 1 ; -- k)
			sum[k] = sum[k + tmp] + a[k];
		int j = i;
		while (j <= m) {
			ans[ask[j].id] = sum[ask[j].b];
			if (ask[j + 1].k != ask[i].k)
				break;
			++ j;
		}
		i = j;
	}
	for (; i <= m ; ++ i) {
		int k = ask[i].k;
		long long tmp = 0;
		for (int j = ask[i].b ; j <= n ; j += k)
			tmp += a[j];
		ans[ask[i].id] = tmp;
	}
	for (int i = 1 ; i <= m ; ++ i)
		print(ans[i]),putchar('\n');
	fwrite(obuf,O - obuf,1,stdout);
	return 0;
}
```

---

## 作者：sysong (赞：1)

# 题解CF103D Time to Raid Cowavans

### Description

给一个序列 $a$ ，$m$ 次询问，每次询问给出 $t, k$。求 $a_t + a_{t+k}+a_{t+2k}+\cdots+a_{t+pk}$ 其中 $t+pk \leq n$ 且 $t+(p+1)k > n$

$n,m \leq 300000,a_i \leq 10^9$

**显然要开 $\text{long long}$**

### Solution

这道题在 2014年国家集训队论文 $\text{根号算法——不只是分块}$  中被~~作为水题~~提到：

![](https://cdn.luogu.com.cn/upload/image_hosting/y975h745.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/bwcpi7ga.png)

对于 $y > \sqrt{n}$ 的情况，我们直接暴力，复杂度小于 $\Omicron (\sqrt{n})$。

对于 $y \le \sqrt{n}$ 的情况，我们分类来看。

1. 如果当前 $y$ 与上一次相同，设上一次的 $t-1$ 为 $last$，处理一个后缀和数组 $s$，从 $last$ 开始，向前处理到 $t$。

   即`s[i]+=s[i+k]` ($t \le i < i+k \le \min(last,n)$ )

2. 如果不同，那么从 $n$ 开始处理，一直到 $t$，式子与上一次相同。

这里配一张样例1的解释，可能对于理解有所帮助。

![](https://cdn.luogu.com.cn/upload/image_hosting/r4aoh6b3.png)

#### 因为这一题卡空间，所以不能提前处理，只能每一次单独计算答案。

### Code

```c++
#include <bits/stdc++.h>
#define R register
#define gc() getchar()
#define ll long long
using namespace std;

inline int rd(){
	R int x=0;R char c=gc();//,f=1
	while(c>'9'||c<'0')c=gc();//{if(c=='-')f=-1;
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
	return x;//*f
}

struct que{
	int f,t,k;
	bool operator <(const que &a)const{
		return k==a.k?t>a.t:k>a.k;
	}
}q[300010];
int a[300010],n,m,sz;
ll Ans[300010],s[300010],ans;

int main(){
	n=rd(),sz=sqrt(n);
	for(R int i=1;i<=n;i++)a[i]=rd();
	m=rd();
	for(R int i=1;i<=m;i++)q[i].t=rd(),q[i].k=rd(),q[i].f=i;
	sort(q+1,q+m+1);
	for(R int i=1,last=n,t,k;i<=m;i++){
		ans=0,t=q[i].t,k=q[i].k;
		if(k>sz)
			for(R int j=t;j<=n;j+=k)ans+=a[j];
		else{
			if(k!=q[i-1].k)last=n;
			for(R int j=last;j>=t;j--){
				s[j]=a[j];
				if(j+k<=n)s[j]+=s[j+k];
			}
			last=t-1,ans=s[t];
		}
		Ans[q[i].f]=ans;
	}
	for(R int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}

```



***by jsntsys***

$2020.12.27$



---

## 作者：happybob (赞：0)

比较经典的问题。

考虑根号分治，令 $b=\lfloor\sqrt n\rfloor$。对于 $k \geq b$，直接暴力，复杂度是 $O(\sqrt n)$ 的。对于 $k < b$，考虑预处理 $f_{i,j}$ 表示 $t=i,k=j$ 时的答案，单组询问 $O(1)$。

容易发现 $f_{i,j}=f_{i+j,j}+a_i$，逆序枚举即可。

但是这样空间复杂度为 $O(n \sqrt n)$，本题还卡空间，于是过不去。

于是我们可以离线将 $k$ 排序，枚举 $j$ 并且只记录 $f_i$ 代替 $f_{i,j}$。这样就可以做到 $O(n)$ 空间，$O(n \sqrt n)$ 时间。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

const int N = 6e5 + 5;
int blo;
long long ans[N], a[N];

struct Node
{
	int t, k, id;
}q[N];
int n, m;

vector<pair<int, int> > v[N];
long long res[N];

int main()
{
	scanf("%d", &n);
	blo = max(1, (int)sqrt(n));
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &q[i].t, &q[i].k);
		q[i].id = i;
	}
	sort(q + 1, q + m + 1, [](Node x, Node y) {return x.k < y.k; });
	for (int i = 1; i <= m; i++)
	{
		if (q[i].k >= blo)
		{
			for (int j = q[i].t; j <= n; j += q[i].k)
			{
				res[q[i].id] += a[j];
			}
		}
		else
		{
			v[q[i].k].emplace_back(make_pair(q[i].id, q[i].t));
		}
	}
	for (int i = 1; i < blo; i++)
	{
		for (int j = 1; j <= n; j++) ans[j] = 0;
		for (int j = n; j >= 1; j--)
		{
			ans[j] = ans[j + i] + a[j];
		}
		for (auto j : v[i])
		{
			res[j.first] = ans[j.second];
		}
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", res[i]);
	return 0;
}
```


---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
一个序列 $a$ ，$m$ 次询问，每次询问给出 $t, k$。求 $a_t + a_{t+k}+a_{t+2k}+\cdots+a_{t+pk}$ 其中 $t+pk \leq n$ 且 $t+(p+1)k > n$。

$n,m \leq 300000,a_i \leq 10^9$
## $\text{Solution}$
似乎题解有对前缀和进行分块优化空间从而在线的神仙做法？  
~~但是这题离线就挺香的了~~  
不难想到根号分治，对于 $k>\sqrt n$ 的询问，直接暴力即可。  
对于 $k\le \sqrt n$ 的询问，离线下来对于 $\sqrt n$ 个可能的 $k$ 分别处理前缀和就可以 $O(1)$ 回答所有询问。  
时间复杂度 $O(n\sqrt n)$，空间复杂度 $O(n)$。
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=3e5+100;
#define ll long long
#define ui unsigned int
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}  
  while (isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}    
  return x*f;
}

int n,m;

ll sum[N],a[N];
struct query{
  int st,d,id;
  bool operator < (const query o)const{return d<o.d;}
}q[N];
int tot;
ll ans[N];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  int w=sqrt(n);
  for(int i=1;i<=n;i++) a[i]=read();
  m=read();
  for(int i=1;i<=m;i++){
    int aa=read(),b=read();
    if(b>w){
      ll res(0);
      for(int j=aa;j<=n;j+=b) res+=a[j];
      ans[i]=res;
    }
    else q[++tot]=(query){aa,b,i};
  }
  sort(q+1,q+1+tot);
  int now(0);
  for(int i=1;i<=tot;i++){
    if(now!=q[i].d){
      now=q[i].d;
      for(int j=1;j<=n;j++){
	sum[j]=a[j];
	if(j>now) sum[j]+=sum[j-now];
      }      
    }
    int id=q[i].id,st=q[i].st,d=q[i].d,ed=st+(n-st)/d*d;
    ans[id]=sum[ed];
    if(st>now) ans[id]-=sum[st-now];
  }
  for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
  return 0;
}
/*
*/

```


---

## 作者：Piwry (赞：0)

这题貌似在一篇集训队论文中（开头，~~被叫做水题~~）被提到过：$\text{根号算法--不只是分块 by 王悦同 in 2014}$

做完这题还可以顺便去写下 $\text{（洛谷）哈希冲突}$。写法稍微有些不一样。（~~说实话改的不多还没有这题的细节处理难...~~）

## 解析

对于每个步长 $k$，我们可以很暴力地以 $O(\frac n k)$ 的复杂度求出 $0$ ~ $k-1$ 的答案（至于对于所有 $t$ 的答案后面说）。

若设一个边界 $S$，对于所有 $k\leqslant S$ 预处理答案；对于所有 $k>S$ 只在询问时暴力求答案，就可以发现总复杂度是 $O(n\cdot \frac n S+mS)$（$m$ 是询问数），若将 $m$ 渐进地视为 $n$，就可以发现当且仅当 $S=\sqrt n$ 时总复杂度取最小值 $O(n\sqrt n)$，这是我们**可以接受的**。

---

但这题还有一些细节问题。若我们这样补素地预处理答案：

```cpp
for(int k =1; k <= S; ++k) for(int t =n; t >= 0; --t){
	ans[k][t] =val[t];
	if(t+k <= n) ans[k][t] +=ans[k][t+k];
}
```

对于这题的空间限制是**妥妥地炸掉的**。因此我们可以考虑将询问离线，**按 $k$ 排序**，每次更换 $k$ 的时候清空预处理数组并重求。可以想到这其实就是把预处理数组的 $k$ 那维压掉，然后将预处理出的答案**马上回答掉并抛弃**，以节省空间，复杂度是一样的。

## CODE

（下面的代码还对 $k$ 相等的元素按 $t$ **降序**排序，进一步压缩（时间）复杂度。稍微有点改动，不过看一下应该就能理解。（对于每个 $t$ 答案只需要所有编号大于 $t$ 的元素的值就可以算出））

（~~话说这样再按 $t$ 排序后还可以进一步把空间压到 $max(k)$，不过好像 $k$ 最大也还是 $n$...（逃~~）

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#define ll long long
using std::sort;

const int MAXN =3e5+10;

struct query{
	int t, k, ord;
}q[MAXN];

int cmp(query a, query b){
	return (a.k == b.k) ? a.t > b.t : a.k > b.k;
}

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

ll ans[MAXN]/*t*/, Ans[MAXN];
int val[MAXN];

int main(){
	int n =read();
	int S =sqrt(n);
	for(int i =1; i <= n; ++i) val[i] =read();
	int m =read();
	for(int i =0; i < m; ++i) q[i].t =read(), q[i].k =read(), q[i].ord =i;
	sort(q, q+m, cmp);
	for(int i =0, lastt, lastk =-1; i < m; ++i){
		int k =q[i].k, t =q[i].t, ord =q[i].ord;
		if(k <= S){
			if(k != lastk) lastt =n, lastk =k;/*换 k 重置*/
			for(int j =lastt; j >= t; --j){
				ans[j] =val[j];/*用到时才清空*/
				if(j+k <= n) ans[j] +=ans[j+k];
			}
			lastt =t-1;
			Ans[ord] =ans[t];
		}
		else for(int p =t; p <= n; p +=k) Ans[ord] +=val[p];
	}
	for(int i =0; i < m; ++i) printf("%lld\n", Ans[i]);
}
```


---

## 作者：Gypsophila (赞：0)

### Description 

给一个序列 $a$ ，$m$ 次询问，每次询问给出 $t, k$ 。求 $a_t + a_{t+k}+a_{t+2k}+\cdots+a_{t+pk}$ 其中 $t+pk \leq n$ 且 $t+(p+1)k > n$

$n,m \leq 300000,a_i \leq 10^9$

### Solution 

对 $k$ 即公差分块。设定一个 $T$ 。 

当 $k > T$ 时，直接暴力算。复杂度 $O(\frac{n}{T})$；

当 $k \le T$ 时，对于 $k$ 建立一个后缀和数组 $sum$。$sum_i$ 表示从 $n$ 开始往前这么跳公差 $k$ 跳到 $i$ 的和。它可以倒着遍历用 $sum_i = sum_{i+k} + a_i$ 更新。复杂度 $O(n)$

取 $T = \sqrt n$ 则可以预处理出所有小于 $T$ 的 $k$ 的 sum。复杂度 $O(n \sqrt n)$ 

但这样空间爆炸（MLE）所以开一个 sum 数组，把询问按照 $k$ 从小到大排序。每次若 $k>T$ 暴力；$k \leq T$ 时重新更新 sum。由于询问中最多有 $T$ 个不同的数 $\leq T$~~（废话）~~ 所以更新的复杂度不会超过 $n \sqrt n$


所以总时间复杂度是 $O(n \log n + n \sqrt n)$

### Code

[看代码戳这里](https://www.cnblogs.com/acfunction/p/10321146.html)



---

