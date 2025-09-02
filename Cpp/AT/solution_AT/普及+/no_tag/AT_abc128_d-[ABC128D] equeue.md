# [ABC128D] equeue

## 题目描述

有一个双端队列，初始时队列中共有 $n$ 个元素，元素从头到尾的权值为 $v_{1},v_{2},\cdots,v_{n}$

你可以进行不超过 $k$ 次操作（也可以一次都不操作），每次操作可以选择队头或队尾的一个元素，将它归为己有，或将自己手上的一个元素塞到队头或队尾

问最终你手上所有元素的权值之和的最大值是多少

## 说明/提示

$ 1 \le n \le 50,1 \le k \le 100, -10^7 \le v_{i} \le 10^7 $

## 样例 #1

### 输入

```
6 4
-10 8 2 1 2 6```

### 输出

```
14```

## 样例 #2

### 输入

```
6 4
-6 -100 50 -2 -5 -3```

### 输出

```
44```

## 样例 #3

### 输入

```
6 3
-6 -100 50 -2 -5 -3```

### 输出

```
0```

# 题解

## 作者：Licykoc (赞：7)

# 题意：
给定一个长度为 $n$ 的序列，和一个最大操作次数 $k$。

有以下四种操作：
- 操作 A：在序列左侧取走一个数放入手中。

- 操作 B：在序列右侧取走一个数放入手中。

- 操作 C：将手中**任意**一个数放在序列左侧。

- 操作 D：将手中**任意**一个数放在序列右侧。

求在若干次操作后手中留下数的最大值。
# $\mathcal{Sol:}$
首先观察题目的数据范围：$1 \le n \le 50$，$1 \le k \le 100$ 。

这么小的 $n$ 很明显暴力啊！但是如果纯暴力的话铁定T，考虑优化。

观察到在操作C，D中可以将**任意**一个数放在序列左/右测，那么也就是说：如果从手中取出一个负数，那么最终答案会变大；如果取出一个正数，那么最终答案会变小。

这样就是一个贪心的思路，枚举操作A，B的次数，然后使用贪心来确定操作C，D。这样就很可行了。

还有一点，在取出数时一定是从最小的数开始取，也就是按照递增的顺序取，这样才能保证结果最大，正确性显然。

综上，我们得到了一个 $\mathcal{O}(n^2k)$ 的算法。

# $Code:$
```cpp
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
int n,k,_,ans;
int a[51];
priority_queue<int,vector<int>,greater<int> > Q;//保证递增序列，使用stl封装的小顶堆
int main () {
	IOS;
	cin>>n>>k;
	for (int i=1;i<=n;++i) cin>>a[i];
	for (int i=0;i<=k;++i)	
		for (int j=0;i+j<=k&&i+j<=n;++j) { //注意操作A，B的次数不能超过k
			for (int x=1;x<=i;++x) Q.push(a[x]);
			for (int x=1;x<=j;++x) Q.push(a[n-x+1]);
			_=k-i-j;
			while (!Q.empty()&&_--&&Q.top()<0) Q.pop();
			_=0;
			while (!Q.empty()) _+=Q.top(),Q.pop();
			ans=max(ans,_);
		}
	cout<<ans<<endl;
}
```


---

## 作者：Erica_N_Contina (赞：4)

# [ABC128D] equeue


## 大意

有一个双端队列，初始时队列中共有 $n$ 个元素，元素从头到尾的权值为 $v_{1},v_{2},\cdots,v_{n}$，你可以进行不超过 $k$ 次操作。

$A.$ 选择队头的一个元素，将它归为己有。

$B.$ 选择队尾的一个元素，将它归为己有。

$C.$ 将自己手上的一个元素塞到队头或队尾。

问最终你手上所有元素的权值之和的最大值是多少。

## 思路

看到 $1 \le n \le 50,1 \le k \le 100 $ 我们可以想到**枚举操作 $A,B$ 的次数**，计算出结果，取最大值即可。

我们用两层循环枚举 $A,B$ 的次数，计算出 $C$ 的次数。我们取出队列前 $A$ 个和后 $B$ 个，组成新的数组 $t$，对 $t$ 进行排序，贪心的选择其中的负数执行操作 $C$。对于 $t$ 中的负数我们从小到大执行操作 $C$，直到没有负数或者操作数 $A+B+C=k$ 时停止。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code by Ntsc .
       . WHY NOT????? .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define ll long long
#define db double
#define rtn return
using namespace std;

const int N=1e5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

ll n,m,ans,sum,k;
ll t[N],v[N];


signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>v[i];
	}
	for(int ia=0;ia<=n&&ia<=k;ia++){//枚举A
		for(int ib=0;ib+ia<=n&&ib+ia<=k;ib++){//枚举B
			int cnt=0;sum=0;
			for(int i=1;i<=ia;i++)t[++cnt]=v[i],sum+=v[i];
			for(int i=1;i<=ib;i++)t[++cnt]=v[n-i+1],sum+=v[n-i+1];
			sort(t+1,t+cnt+1);
			int c=k-ia-ib;//计算C
			for(int i=1;i<=c&&i<=cnt;i++){
				if(t[i]>0)break;//一直丢到没有负数或者操作数达到k或者t中没有剩余元素
				sum-=t[i];//从t中挑选出负数，丢掉
			}
			ans=max(ans,sum);
		}
	}
	cout<<ans<<endl;
	return 0;
}

```




---

## 作者：qiuqiuqzm (赞：0)

# [ABC128D] equeue 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc128_d)

## 题目大意
~~自己去看吧~~（翻译简洁明了）。

题意就是给定一个双端队列，有 $n$ 个元素，可以进行至多 $k$ 次操作。每次可选如下 $4$ 种操作：

* A 操作：从队首取一个元素。

* B 操作：从队尾取一个元素。

* C 操作：从自己手中取一个元素放入队首。

* D 操作：从自己手中取一个元素放入队尾。

求最后自己手中的元素权值总和最大多少。

## 分析
~~这是一道非常简单的绿题~~

* 看到数据范围：$1\le n\le50,1\le k\le100$。那这不是妥妥的暴力枚举吗。
* 但操作数有四种，直接暴力肯定会~~开心的~~ T 飞。那就要考虑优化。
* 我们可以直接暴力枚举选择的情况，然后用贪心把放回去的情况写出来。

* 放回去的元素肯定要是负数，这样还能让权值变大，正数去掉会变小，不考虑，$0$ 去掉没影响，但会浪费步骤，一样不考虑。所以只要从小到大去掉负数即可。

## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,v[1001],ans=-1;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>v[i];
	for(int i=0;i<=min(n,k);i++) //选总个数和可执行次数小的,如果执行次数多，到 n 就不能再拿了
	{
		for(int j=0;j<=min(n-i,k-i);j++) //同上，只不过变成了剩下的
		{
			int maxx=0,small[1001],num=0;
			for(int l=1;l<=i;l++)
			{
				maxx+=v[l]; //操作 A
				if(v[l]<0) //记录负数
					small[++num]=v[l];
			}
			for(int r=n;r>n-j;r--)
			{
				maxx+=v[r]; //操作 B
				if(v[r]<0) //同上
					small[++num]=v[r];
			}
			sort(small+1,small+1+num); //从小到大排序，更小的先去掉
			int last=min(k-i-j,num); //判断剩余步骤和总的负数哪个小
			for(int sum=1;sum<=last;sum++)
				maxx-=small[sum]; //去掉
			ans=max(maxx,ans); //记录答案
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：L_zaa_L (赞：0)

## 题意
给你 $n$ 个数，可以做 $m$ 次修改，可以做以下修改：

+ 取出原序列左边或右边的数，放入另一个序列（原序列必须有数）。
+ 将另一个序列的任意一列数放入原序列的左边或右边（另一个序列必须有数）。

## 分析
由题意可以得出，数据只有 $ n \leq 50,k \leq 100$。所以，可以使用暴力，枚举从左右两边取的个数（只能从两边取），用一个数组记录下负数，去玩两边之后，将负数排个序，再用剩下的步骤，每次将最小的负数放回原序列（正数不要丢！），直到步骤用完或者负数全部放回原序列。最后找出最大值即可。

#### 时间复杂度
$O(N^3\log n)$

## Code
```
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int a[1000005];
int fs[10005],tot;//fs记录负数
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n-i;j++){//不能将全部取完
			if(i+j>m) continue;//不能超过步数
			int sum=0;//sum记录当前方案的值
			tot=0;
			for(int k=1;k<=i;k++){
				sum+=a[k];
				if(a[k]<0)
					fs[++tot]=a[k];//从左边取出i个数，并将负数加入到fs数组中
			}
			for(int k=n;k>=n-j+1;k--){
				sum+=a[k];
				if(a[k]<0)
					fs[++tot]=a[k];//从右边取出j个数，并将负数加入到fs数组中
			}
			sort(fs+1,fs+tot+1);//将负数排序，就可以从小到大将负数丢掉
			int s=m-i-j;
			for(int k=1;k<=tot;k++){//枚举负数
				if(s==0) break;//不能超过步骤
				s--;
				sum-=fs[k];//将最小的负数丢掉
			}
			ans=max(ans,sum);//求出最大值
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：FrozenDream (赞：0)

### 前言：
~~绿题的耻辱~~
### 思路：
首先看一下数据范围：$1\leq n\leq 50$,$1\leq k\leq 100$，这么小~~水~~的数据范围，肯定打暴力呀。

我们可以考虑把 $A,B$ 操作和 $C,D$ 操作分开考虑，枚举分别从左右两端取的操作数，再分别模拟取宝石，然后对于贡献为负数的宝石，记录在一个数组里，最后再用剩下的操作数，从小到大依次取出就可以了。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,v[100005],fs[100005],tot,ans=-1;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>v[i];
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n-i;j++){
			if(i+j<=m){
				int sum=0;
				tot=0;
				for(int k=1;k<=i;k++){
					sum+=v[k];
					if(v[k]<0){
						fs[++tot]=v[k];
					}
				}
				for(int k=n;k>n-j;k--){
					sum+=v[k];
					if(v[k]<0){
						fs[++tot]=v[k];
					}
				}
				sort(fs+1,fs+tot+1);
				for(int k=1;k<=min(tot,m-i-j);k++){
					sum-=fs[k];
				}
				ans=max(ans,sum);
			}
		}
	}
	cout<<ans;
}
```


---

## 作者：zjc5 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT4724)

**思路：**

这一题可以看成从左边取出 $a$ 个宝石，从右边取出 $b$ 个宝石，最后从手中取出 $(k-a-b)$ 颗宝石。

但是从手中取出的 $(k-a-b)$ 颗宝石不一定是手中最小的 $(k-a-b)$ 颗，因为题目说你最多可以进行 $k$ 次（可能为 $0$ ）的操作。

只有负数才会减少手中宝石的价值，因此，最小的 $(k-a-b)$ 颗宝石只需要删除其中的负数即可。

因为本题的$n$数据范围很小，所以直接暴力枚举 $a+1$ 和 $n-b$ （即左边取出 $a$ 个宝石，从右边取出 $b$ 个宝石后数列的左端点和右端点），对于每一组合法的区间算出答案，取一个最大值。

代码的时间复杂度为 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110],ans,s[110];
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int l=1;l<=n;l++) //左端点
        for(int r=n;r>=l-1;r--){ //右端点 注意是l-1,因为可以全部取走
            if(l-1+(n-r)>k) break; //如果操作次数大于k，直接退出
            int t=k-(l-1+(n-r)),tot=0,pos,sum=0;
            for(int i=1;i<l;i++) s[++tot]=a[i];
            for(int i=r+1;i<=n;i++) s[++tot]=a[i];
            sort(s+1,s+tot+1);
            for(pos=1;pos<=t;pos++)
            if(s[pos]>=0) break; //遇到正数，不取出
            for(int i=pos;i<=tot;i++) sum+=s[i];
            ans=max(ans,sum);
        }
    cout<<ans;
    return 0;
}
```

---

## 作者：lkjzyd20 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT4724)

___

### 思路

这一题可以看成从左边取出 $l$ 个宝石，从右边取出 $r$ 个宝石，最后从手中取出 $k-l-r$ 颗宝石。

但是从手中取出的 $k-l-r$ 颗宝石不一定是手中最小的 $k-l-r$颗，因为题目说你最多可以进行 $K$ 次（可能为 $0$）的操作。

只有负数才会减少手中宝石的价值，因此，最小的 $k-l-r$ 颗宝石只需要删除其中的负数即可。

因为本题的 $n$ 数据范围很小，所以直接暴力枚举 $l$ 和 $r$，对于每一组合法的 $l$ 和 $r$ 算出答案，取一个最大值。
 
代码的时间复杂度为 $O(n^3)$。
___
### 代码如下

```cpp
//#include<bits/stdc++.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=0x3f3f3f3f,MOD=1e9+7;
#define pu putchar
#define endl puts("")
//#define int __int128
//#define int long long
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define me0(a); memset(a,0,sizeof a);
#define me3(a); memset(a,0x3f,sizeof a);
#define PII pair<int,int>
void read(int &n){char c,w=1;for(;48>c||c>57;c=getchar())
w=c==45?-1:1;for(n=0;47<c&&c<58;c=getchar())n=n*10+c-48;n*=w;
}void write(int x){if(x<0)pu(45),x=-x;char c[41],s=0;
for(;x;)c[s++]=x%10,x/=10;if(!s)pu(48);for(;s--;)pu(c[s]+48);
}void debug(int n){printf("\tdebug:\t"); write(n); pu('\t');}
const int MAXN=100+10;
int n,k;
int ans;
int a[MAXN],s[MAXN];
main(){
	read(n); read(k);
    rep(i,1,n){
    	read(a[i]);
	}rep(l,0,n){
    	rep(r,0,n-l){
            if(l+r<=k){
            	int pos,tot=0,sum=0;
            	rep(i,1,l){
            		s[++tot]=a[i];	
				}rep(i,n-r+1,n){
					s[++tot]=a[i];	
				}sort(s+1,s+tot+1);
	            for(pos=1;pos<=k-l-r;++pos)
	            	if(s[pos]>=0){
	            		break;
					}
				rep(i,pos,tot){
	            	sum+=s[i];
				}ans=max(ans,sum);
			}
        }
	}write(ans); endl;
}
```
### [$AC$ 记录](https://www.luogu.com.cn/record/85932344)

### 完结撒花 $\sim\sim\sim$

---

## 作者：Jairon314 (赞：0)

> [题目链接](https://atcoder.jp/contests/abc128/tasks/abc128_d)

$ Solution $

------------

注意到这题数据很小，所以怎么都能过（bushi

注意到不管是什么样的操作，把手里的数放回 dequeue 的操作都可以留到最后进行。枚举从队首拿了几个元素，从队尾拿了几个元素，看看还能进行几次操作，贪心把手中小于 0 的元素拿出来一些就行了。

手里的数用 multiset 维护即可。

（突然发现我这个 multiset 一开始想干的没干其实可以用其他的容器把复杂度降一个 log

[AC记录](https://atcoder.jp/contests/abc128/submissions/29209951)

代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
using namespace std;

#define $int long long

/***** Fast_IO *****/

using vii = vector<int>;
using pii = pair<int,int>;

namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;

	#define gc getchar
	#define pc putchar

	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}

	template<typename I,typename ...Args>
	inline void read(I &a, Args &...args){
		read(a),read(args...);
	}

	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		int tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}
	
	template<class I>
	inline void chmax(I &x,I y){ return x=max(x,y),void(); }
	
	template<class I>
	inline void chmin(I &x,I y){ return x=min(x,y),void(); }

	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define all(v) (v).begin(),(v).end()
	#define each(i,v) for(auto &i:v)
	#define umap unordered_map
	#define sqr(k) ((k)*(k))
	#define inf 0x3f3f3f3f3f3f
	#define pb push_back
	#define mp make_pair
	#define fir first
	#define sec second
	#define db double
}using namespace IO;

/***** Fast_IO *****/

#define maxn 1000010
#define SIZE 5010

int n,k;
int ans=0;
int v[maxn];

multiset<int> m_Set;

int main(){
	read(n,k);
	FOR(i,1,n){ read(v[i]); }
	FOR(pos1,0,n){
		FOR(i,1,pos1){ m_Set.insert(v[i]); }
		ROF(pos2,n+1,pos1+1){
			if(pos2==n+1){}
			else{ m_Set.insert(v[pos2]); }
			int K=k-pos1-(n-pos2+1),res=0;
			if(K<0){ break; }
			each(ver,m_Set){
				if(ver<0){
					if(K){ --K; }
					else{ res+=ver; }
				} else{ res+=ver; }
			} chmax(ans,res);
			// assi(),out(pos1),out(pos2),outn(res);
		} m_Set.clear();
	} outn(ans);
	return 0;
}
```


---

## 作者：_zexal_ (赞：0)

## 思路
注意到 $n \leq 50$ 和 $k \leq 100$，很明显，可以暴力。我们用 $k_1$ 表示用来取数的次数，$k_2$ 表示用来取消拿的数的次数，然后我们在枚举拿的两个区间即可。至于拿的数字，我们不妨采用贪心，拿最小的数即可。总的复杂度为 $O(n^3 \log n)$，可以通过本题。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define F(i,a,b) for(int i=a;i<=(b);i++)
using namespace std;
const int Maxn=2e6;
long long n,m,x,y,k,a[Maxn],sum,sum1,answer=-1e9,aaa;
inline int read() {
	int x = 0,f = 1;
	char ch = getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
void write(int x) {
	if(x<0)putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}
priority_queue<int,vector<int>,greater<int> > Q;
signed main() {
	cin>>n>>k;
	F(i,1,n) {
		cin>>a[i];
		if(a[i]>0) aaa+=a[i];
	}
	int k1=k;
	if(2*n<=k) {
		cout<<aaa;
		return 0;
	}
	F(z,0,k1) {
		k=k1-z;
		sum1=0;
		F(i,0,k) {
			//	cout<<i;
			sum1+=a[i];
			int sum3=0;
			for(int j=1; j<=i; j++) Q.push(a[j]);
			for(int j=n; j>=n-(k1-i-z)+1; j--) {
				//	cout<<j;
				if(j<=i) continue;
				sum3+=a[j];
				Q.push(a[j]);
			}
			//cout<<i<<" "<<n-(k1-i-z)+1<<" "<<z<<" "<<sum1+sum3<<" "<<Q.top()<<endl;
			int sum2=sum1+sum3;
			for(int j=1; j<=z; j++) {
				answer=max(answer,sum2);
				if(Q.size()==0) break;
				sum2-=Q.top();
				Q.pop();
			}
			answer=max(answer,sum2);
			while(Q.size()!=0) Q.pop();
			//	cout<<answer<<endl;
		}
	}
	cout<<answer<<endl;
	return 0;
}
```


---

## 作者：tZEROちゃん (赞：0)

> 给你一个长为 $N$ 的序列 $v$，你有 $4$ 种操作。   
>  
> - 操作 A：从序列首拿一个元素。
> - 操作 B：从序列尾拿一个元素。
> - 操作 C：放一个元素到序列首。
> - 操作 D：放一个元素到序列尾。
>
> 输出至多 $K$ 次操作后你手中元素和的最小值。

我们可以把操作 C 和 D 放到最后，于是操作 C 和 D 就是等价的了，即：「扔掉手中任意一个元素」。

观察到 $n = 50$，所以可以考虑枚举操作 A 和操作 B 的个数，然后就剩下了 $K - (A+B)$（其中 $A, B$ 分别表示操作 A 和操作 B 的个数）次操作的机会。

我们设 $S$ 为现在我们手中所有元素的和，显然如果我们扔掉一个负数会使答案变大，扔掉一个正数会使答案变小，所以我们 **一直扔负数**。

我们还可以发现 **扔掉的负数越小，答案就会变的越大**。比如我们现在序列的 $S = 5$，显然扔掉一个 $-3$ 之后答案变成 $8$，扔掉一个 $-114$ 之后答案变成 $119$，所以肯定选扔掉 $-114$。

所以我们对原来的序列按升序排序，然后依次取 $K$ 个数，如果取到的数已经是正数了，那么我们就可以不取了。

然后就按照上面的过程模拟就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); i ++)
#define per(i, r, l) for(auto i = (r); i >= (l); i --)

int v[55];

void solve() {
  int N, K;
  cin >> N >> K;
  rep (i, 1, N) {
    cin >> v[i];
  }
  int mx = 0;
  rep (A, 0, min(N, K)) {
    rep (B, 0, min(N, K)) {
      if (A + B > min(N, K)) break;
      vector<int> que;
      rep (i, 1, A) que.push_back(v[i]);
      rep (i, 1, B) que.push_back(v[N - i + 1]);
      int CandD = K - (A + B);
      if (CandD < 0) break;
      sort(que.begin(), que.end());
      // for (auto &i : que) {
      //  cout << i << ' ';
      // }
      // cout << endl;
      for (auto &i : que) {
        if (i < 0 && CandD > 0) {
          i = 0;
          --CandD;
        } if (CandD < 0 || i > 0) {
          break;
        }
      }
      int cnt = 0;
      for (auto &i : que) {
        cnt += i;
      }
      // for (auto &i : que) {
      //  cout << i << ' ';
      // }
      // cout << endl;
      // cout << "---------\n";
      mx = max(mx, cnt);
    }
  }
  cout << mx;
  putchar('\n');
}

int main(){
  solve();
  return 0;
}
```

---

