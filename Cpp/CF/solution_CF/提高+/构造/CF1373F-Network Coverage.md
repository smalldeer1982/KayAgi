# Network Coverage

## 题目描述

给你$n$个城市，这$n$个城市首尾相接形成一个环，已知每个城市有一定数量的家庭需要网络。同时每一座城市中有一个网络基站，每一个网络基站可以为一定数量的家庭提供网络，并且第$i$个网络基站只能给第$i$个城市和第$i+1$个城市的家庭提供网络（第$n$个网络基站可以给第$n$座城市和第$1$座城市提供网络）。

现在给你每一座城市需要网络的家庭数量$a_i$和每一个网络基站可以提供的最多网络数量$b_i$，请你判断能否使得所有的家庭都获得网络，可以则输出“YES“，否则输出”NO“。

## 样例 #1

### 输入

```
5
3
2 3 4
3 3 3
3
3 3 3
2 3 4
4
2 3 4 5
3 7 2 2
4
4 5 2 3
2 3 2 7
2
1 1
10 10```

### 输出

```
YES
YES
NO
YES
YES```

# 题解

## 作者：Froggy (赞：12)

赛后一分钟做出来有点崩溃，好在它重测的时候 FST 了。（雾

---

容易发现，只要确定了 $b_1$ 分给 $a_1$ 多少，那么之后的就可以贪心来搞，$\mathcal{O}(n)$ 即可判断是否可行。

## 做法 1：

二分这个 “$b_1$ 分给 $a_1$”  的值，

这里主要讲的不是这个，具体做法就直接推神仙 wyy 的题解了：[here](https://www.luogu.com.cn/blog/wyy2020/solution-cf1373f)。

时间复杂度：$\mathcal{O}(n\log a_1)$。

---

## 做法 2：

网络流。具体做法不再展开。

Q：$10^6$ 拿头过啊？

A：我不清楚但是我同学过了，可能因为图比较特殊吧。（[提交记录](https://codeforces.com/contest/1373/submission/85052834)）

有兴趣可以研究一下。

---

## 做法 3：

我具体要讲的做法，并且是**线性**做法。

换一个思路：

设 $b_1$ 给 $a_2$ 了 $x_1$，$b_2$ 给 $a_3$ 了 $x_2$，$\cdots$，$b_n$ 给 $a_1$ 了 $x_n$。

这样就可以得到一堆不等式：

$$
\forall i\in [1,n],
\begin{cases}
x_i\geq 0 \\
x_i\leq b_i \\
x_i+b_{(i\bmod n)+1}-x_{(i\bmod n)+1}\geq a_{(i\bmod n)+1}
\end{cases}
$$

愉快地差分约束一波然后建图。

$n=5$ 的图建出来就长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/bbbg7le7.png)

如果有正环就说明 NO（无解），否则就 YES（有解）。

直接跑 SPFA 是 $\mathcal{O}(n^2)$，如果把判定负环所需的入队次数改小（[比如我改成了 $8$](https://codeforces.com/contest/1373/submission/85083539])），然后光荣地 FST 了。（WA on 51，是 hack 数据。）

不过应该会发现这个长的像轮胎的图比较特殊，可以 “手动” 判正环。

首先判掉外边一圈是正的情况，剩下可能的正环都长这个样子：

$S\rightarrow x\rightarrow x\bmod n+1\rightarrow\cdots\rightarrow y\rightarrow S$

所以可以维护 $a_i-b_i$ 的前缀和 $sum$，同时维护 $sum+b_i$ 的最小值 $mn$。

如果某个位置满足 $mn<sum$ 就说明有正环。

注意由于这是个环，所以要**把环拆开然后复制一遍**。

时间复杂度：$\mathcal{O}(n)$。

---

***code:***

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
typedef long long ll;
#define N 1000010
int n,T,a[N],b[N];
bool Solve(){
	n=read();
	ll sum=0;
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=n;++i)b[i]=read();
	for(int i=1;i<=n;++i)sum+=a[i]-b[i];
	if(sum>0)return false;
	sum=0;
	ll mn=b[1];
	for(int i=1;i<=(n<<1)+1;++i){
		sum+=a[i%n+1]-b[i%n+1];
		mn=min(mn,b[i%n+1]+sum);
		if(mn<sum)return false;
	}
	return true;
}
int main(){
	T=read();
	while(T--){
		printf(Solve()?"YES\n":"NO\n");
	}
	return 0;
}
```

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!

---

## 作者：奇米 (赞：5)

# 题解 - $\mathrm{CF1373F}$

## 题目意思

* [题目传送门](https://www.luogu.com.cn/problem/CF1373F)

## $\mathrm{Sol}$

* 我们首先考虑二分$b_1$用了多少。关键如何改变上下界。

* 对于提升下界的情况：我们$a_1$本身不够用，需要增加

* 对于降低下界的情况：这样模拟过去，某个$a_i$不够用，我们需要减少自己的量给别人。

* 时间复杂度：$O(n \log a_1)$

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int mod=1e9+7;
const int mo=998244353;
const int N=1e6+5;

int n,m,a[N],b[N],c[N],Q,ans;

inline int check(int x)//用了多少 
{
	For(i,1,n) c[i]=a[i];
	int rem=b[1]-x;
	c[1]=max(0,a[1]-x);
	For(i,2,n) 
	{
		c[i]-=rem;
		c[i]=max(c[i],0);
		if(c[i]>b[i]) return 2;
		rem=b[i]-c[i];
		c[i]=0;
//		if(x==2) cout<<"rem="<<rem<<endl;
	}
	if(c[1]>rem) return 1;
	return 0;
}

int main()
{
	Q=read();
	For(q,1,Q)
	{
		n=read();
		For(i,1,n) a[i]=read();
		For(i,1,n) b[i]=read();
		int l=0,r=b[1],flg=0;
		while(l<=r)
		{
			int mid=(l+r)/2;
			int type=check(mid);
			if(!type) 
			{
				puts("YES");
				flg=1;
				break;
			}
			if(type==1) l=mid+1;
			else r=mid-1;
		}
		if(!flg) puts("NO");
	}
	return 0;
}
		

```


---

## 作者：subcrip (赞：3)

来一个题解区目前还没出现的思路。其实不是很懂为什么评 *2400。不用图论，不用差分约束，不用二分，它就是个模拟题。

首先如果满足条件，则不可能每个 $b_i$ 都分出去一部分给 $(i+1)\bmod n$，否则把这些值都去掉也可以满足条件。所以考虑枚举一个不需要 $(i-1)\bmod n$ 给它值的 $i$。不妨设第一个位置就是。然后往后暴力模拟，直到不满足条件为止，此时中间的所有点都不可能是起点，因为否则从这些点到刚刚不满足条件的那个点，向后转移的量一定更小。

这样从左到右遍历一遍就会找出可能存在的起点。复杂度 $O(n)$，代码也很好写。

Code:

```cpp
void solve() {
    read(int, n);
    readvec(int, a, n);
    readvec(int, b, n);

    int r = 0, s = 0, i = 0;
    for (; i < 2 * n; ++i) {
        if (r + b[i % n] < a[i % n]) {
            r = 0, s = i + 1;
        } else {
            r = min(b[i % n], r + b[i % n] - a[i % n]);
        }
    }
    if (i - s >= n) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
```

---

## 作者：duyi (赞：3)

## 题解 CF1373F Network Coverage

首先，如果知道任意某个$b_i$对$a_i$贡献了多少，比方说，我们枚举$b_1$对$a_1$贡献了多少，那接下来整个环上都可以一次递推出来。当然，如果直接枚举，时间复杂度是$O(n\cdot b_1)$或者$O(n\cdot \min(b_i))$的，肯定不行。

考虑**二分**$b_1$对$a_1$贡献了多少。我们来看怎么调整二分的上界和下界。还是和原来一样从$2$到$n$递推。

- 如果对中间某个$i$ ($2\leq i\leq n$)，$b_{i-1}$留给$a_i$的部分（在递推过程中是已知的）加上整个$b_i$，都小于$a_i$，换句话说就是中间某个$a_i$不够用，说明我们需要减少$b_1$对$a_1$的贡献，留给别人：在二分时也就是$\texttt{r=mid-1}$。
- 如果在递推时所有$a_i$都够用，但是到最后剩下的部分，加上$b_1$对$a_1$的贡献，不够$a_1$了，也就是$a_1$本身不够用，说明需要增大$b_1$对$a_1$的贡献，不能让过多的贡献留给别人然后消耗在路上，所以：$\texttt{l=mid+1}$。
- 排除上述两种情况，我们已经找到了合适的解。直接输出$\text{YES}$即可。

时间复杂度$O(n\log b_1)$。

参考代码：

```cpp
//problem:CF1373F
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int MAXN=1e6;
int n,a[MAXN+5],b[MAXN+5];
int check(int b1_to_a1){
	int v=b[1]-b1_to_a1;
	for(int i=2;i<=n;++i){
		if(a[i]>v){
			if(b[i]<a[i]-v){
				return -1;
			}
			v=b[i]-(a[i]-v);
		}
		else v=b[i];
	}
	if(v<a[1]-b1_to_a1)
		return 1;
	else
		return 0;
}
int main() {
	int T;cin>>T;while(T--){
		cin>>n;
		for(int i=1;i<=n;++i)cin>>a[i];
		for(int i=1;i<=n;++i)cin>>b[i];
		int l=0,r=b[1];
		int ans=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			int t=check(mid);
			if(t==0){
				ans=l;
				break;
			}
			if(t==-1)
				r=mid-1;
			else
				l=mid+1;
		}
		if(ans==-1)
			cout<<"NO"<<endl;
		else
			cout<<"YES"<<endl;
	}
	return 0;
}
```



---

## 作者：tzc_wk (赞：2)

[Codeforces 题面传送门](https://codeforces.ml/contest/1373/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1373F)

提供一个模拟网络流的题解。

首先我们觉得这题一脸可以流的样子，稍微想想可以想到如下建图模型：

- 建立源点 $S,T$ 和上下两排点，不妨设上排点为 $x_1,x_2,\cdots,x_n$，下排点为 $y_1,y_2,\cdots,y_n$。
- 对于每个 $i$ 我们连一条 $S\to x_i$，容量为 $b_i$ 的边，表示每个基站最多提供 $b_i$ 个网络服务。
- 对于每个 $i$，我们连边 $x_i\to y_i,x_i\to y_{i\bmod n+1}$，权值均为 $\infty$，表示基站 $i$ 可以为家庭 $i$ 和家庭 $i\bmod n+1$ 提供网络服务。
- 连边 $y_i\to T$，权值 $a_i$，表示家庭 $i$ 需要 $a_i$ 个网络服务。

然后跑最大流看看最大流是否等于 $\sum\limits_{i=1}^na_i$ 即可。

由于此题 $n$ 高达 $10^6$，因此直接跑最大流显然是不可取的。因此考虑**模拟网络流**，也就是用最小割解决最大流的思路。注意到图是一个环形结构，直接做可能会出现后效性有关的问题，因此我们不妨先解决链的情况，即，假设 $x_n\to y_1$ 的边不存在。设 $dp_{i,j}(j\in\{0,1\})$ 表示现在只考虑 $x_1,x_2,\cdots,x_i,y_1,y_2,\cdots,y_i,S,T$ 的导出子图，$S,T$ 在导出子图中不连通且 $S\to x_i$ 的边的状态为 $j$（$0$：连上，$1$：断开）的最小代价，那么有 $dp_{i,j}=\min\limits_{k\in\{0,1\}}dp_{i-1,k}+kb_i+[j=0\lor k=0]·a_i$，边界条件 $dp_{0,0}=0$。

接下来考虑环的情况，其实感觉会了链的情况，环的情况就异常 trivial 了。按照套路枚举 $S\to x_n$ 的边连上还是断开，设为 $c$，那么与链的情况不同之处在于，边界条件变为 $dp_{0,c}=0$，因为 $S\to x_n$ 的边连上等价于 $x_n\to y_1$ 的边没有被断开，最后用 $dp_{n,c}$ 更新答案即可。

时间复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define mt make_tuple
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long double ld;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=(c=='-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=-x;
	}
	template<typename T> void recursive_print(T x){
		if(!x) return;
		recursive_print(x/10);putc(x%10+'0');
	}
	template<typename T> void print(T x){
		if(!x) putc('0');if(x<0) putc('-'),x=-x;
		recursive_print(x);
	}
	template<typename T> void print(T x,char c){print(x);putc(c);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
template<typename Tv,int limN,int limM> struct link_list{
	int hd[limN+5],nxt[limM+5],item_n=0;Tv val[limM+5];
	void clear(){memset(hd,0,sizeof(hd));item_n=0;}//be aware of the TC of memset
	void ins(int x,Tv y){val[++item_n]=y;nxt[item_n]=hd[x];hd[x]=item_n;}
};
using namespace fastio;
const int MAXN=1e6;
const ll INF=0x3f3f3f3f3f3f3f3fll;
int n,a[MAXN+5],b[MAXN+5];ll dp[MAXN+5][2];
void solve(){
	read(n);ll sum=0,res=INF;
	for(int i=1;i<=n;i++) read(a[i]),sum+=a[i];
	for(int i=1;i<=n;i++) read(b[i]);
	for(int _=0;_<2;_++){
		for(int i=0;i<=n;i++) dp[i][0]=dp[i][1]=INF;
		dp[0][_]=0;
		for(int i=1;i<=n;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++)
			chkmin(dp[i][j],dp[i-1][k]+j*b[i]+(!(j&k))*a[i]);
		chkmin(res,dp[n][_]);
	} //printf("%lld\n",res);
	printf("%s\n",(res==sum)?"YES":"NO");
}
int main(){int qu;read(qu);while(qu--) solve();return 0;}
```



---

## 作者：「　」 (赞：2)

### 一个~~奇怪~~的思路。
在讲解题目之前，我们先来证明一个奇怪的东东：
#### 任何一种的可行状态，必然可以变为一个至少有一个城市不用向上一个网络站获取连接（即该城市自给自足）的可行状态。
先假设有一个全部向左右获取连接的可行状态。

![](https://cdn.luogu.com.cn/upload/image_hosting/vttkroq8.png)

如图，假设k是所有$bi$为$a(i+1)$提供的连接中最小的一个，我们可以尝试删去$k$，那么$b1$到$a1$就增加了$k$，$b1$到$a2$就减少了一个小于等于$k$的数……具体如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nhyx5rr7.png)

易得，$k>=k1>=k2>=k3>=k(i-1)>=ki$，因为$k$是其中最小的，所以没有连接会变成负数，也就是说情况依旧合法，由此得证。

因此，我们可以通过寻找这一个**不从上一个网络站获取连接**的点，再贪心，以消除后效性。因为贪心是线性的，所以我们接下来的问题就是，如何在$n$个城市中找出这一个**自给自足**的城市。

我们可以先看代码：
```
	for(int i=1;i<=n*2;++i)
	{
		if(b[i-1]-a[i-1]>0)
		a[i]-=b[i-1]-a[i-1];
		a[i]=max(a[i],0);
	}
```
这一步操作，实际上就是在破环成链后，贪心每个城市，使其能够从上一个网络站获取尽量多的连接，很容易就看出，这样的计算肯定是**不全部正确**的，因为第一个城市就没有考虑最后一个网络站对他的影响。

（下面的$ai$均已减去$b(i-1)$给它的连接数）

但是，我们可以判断一种情况，即在考虑$a(i-1)>b(i-1)$的情况下，此时，如果再选择将$b(i-1)$分给$ai$，只会是结果更差，而不能优化答案。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nxbc4afb.png)

假设$b(i-1)$给予$ai$ $k$个连接，我们依旧可以得知$k>=k1>=k2>=k3>=k(i-1)>=ki$，同时由于$a(i-1)>b(i-1)$，所以$b(i-1)$一定是用尽的，如果$b(i-1)$需要将$k$个连接给$ai$，那么$a(i-1)$就会少从$b(i-1)$获得$k$个。针对$a(i-1)$，我们可以发现它的连接增加了$k3$减少了$k$，因为$k>=k3$，所以$a(i-1)$获得的连接数只会更少，所以结果只能更差或不变。（$a(i-1)$本身就是不满足的）

所以我们就变相找到了自给自足的点，即寻找到的第一个$a(i-1)>b(i-1)$且$ai<=bi$的点。再在该点后贪心即可。

另外，我们可以发现，寻找**自给自足**的点的代码和贪心的代码实质上是一样的，所以我们可以一起进行。而判断是否成功的依据便是在**自给自足**点之后是否还有点的$ai>bi$，如果有，说明不成功，否则成功。

如还有不理解，可以结合代码食用：
```
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[4000005];
int b[4000005];
inline int read()
{
	char c=getchar();
	while(c<'0'||'9'<c)
	c=getchar();
	int x=0;
	while('0'<=c&&c<='9')
	{
		x*=10;
		x+=c-'0';
		c=getchar();
	}
	return x;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;++i)
		{
			a[i]=read();
			a[i+n]=a[i];
		}
		for(int i=1;i<=n;++i)
		{
			b[i]=read();
			b[i+n]=b[i];
		}
		if(n==2)
		{
			if(b[1]+b[2]>=a[1]+a[2])
			printf("YES\n");
			else
			printf("NO\n");
			continue;
		}
		for(int i=1;i<=n*2;++i)
		{
			if(b[i-1]-a[i-1]>0)
			a[i]-=b[i-1]-a[i-1];
			a[i]=max(a[i],0);//将判断自给自足点与贪心结合
		}
		bool ok=true;
		for(int i=n+1;i<=n*2;++i)
		{
			ok&=b[i]>=a[i];
		}//因为实际上在找到了自给自足点之后的贪心都是正确的，所以我们只需要随意找一个之后的点即可，而n+1~2n一定是正确的
		if(ok)
		printf("YES\n");
		else
		printf("NO\n");
	}
	return 0;
}
```
#### P.S.实际上本方法是在本蒟蒻交了这个奇怪的代码并ＡＣ之后才思考出来的思路，所以思路可能会有误，希望各位大佬积极指出。

---

## 作者：xuezhiyu (赞：1)

# 题面

## 题目描述

有 $n$ 个城市，这 $n$ 个城市按顺序首尾相连形成一个环，已知第 $i$ 个城市有 $a_i$ 个家庭需要网络，而第 $i$ 个城市的服务器能给第 $i$ 个和第 $i+1$ 个城市的 $b_i$ 个家庭需要网络，每个城市的服务器可以把它可以提供的 $b_i$ 个名额随便分配给后面的或当前的。请问在这种情况下能不能让每个家庭都获得网络，如果能，则输出 `YES`，否则输出 `NO`。

## 数据范围

一共有 $t~(1 \le t \le 10^4)$ 组测试数据，$1 \le n \le \sum n \le 10^6$。

# 分析题目

为了方便计算，我们设 $p_i$ 表示第 $i$ 个城市的前一个城市，$p_i=(i+n-2) \bmod n+1$

不妨设第 $i$ 个城市分给下一个城市的网络数量为 $x_i$，那么可以推出式子：

$$b_i-x_i+x_{p_i} \ge a_i$$

变形一下：

$$x_i \le x_{p_i}+b_i-a_i$$

这个式子是不是很眼熟？用 $dis_i$ 替换掉 $x_i$，用 $w$ 替换掉 $a_i-b_i$，然后就成了这个样子：

$$dis_i \le dis_{p_i}+w$$

这不就是我们在寻找最短路时的更新式吗！明显跑完最短路后，这个式子一定会被满足，因为如果这个式子不满足，我们就可以用 $dis_{p_i}+w$ 更新 $dis_i$。

当然，还有一些根据题目需要满足的式子：

$$
x \ge 0
~\text{与}~
x \le b_i
$$

那么我们就可以从 $p_i$ 向 $i$ 建一条边权为 $b_i-a_i$ 的有向边，再创建一个虚拟节点 $S$，向每个点都连一条边权为 $0$ 的边，再从每个点都连一条边权为 $-b_i$ 的边，这样就能满足题目的要求了。

如果这个图中有最短路，那么就是有解，否则就无解，即判一个负环。

但是直接用 `SPFA` 跑负权，很有可能被卡到 $\text O(N^2)$ 的，『~~关于 `SPFA`，它已经死了~~』，明显在 $10^6$ 的数据范围下会 `TLE`。

我们把样例这个图画出来看一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/fxijhght.png)

可以发现在这个图中出现负环有两种基本情况：

- **不经过 $S$ 节点**

不经过 $S$ 节点的负环就可能是最外圈由节点 $1,2,3$ 组成的负环，在读入的时候统计一遍最外圈的边权和，如果这个边权和小于 $0$，那么就代表存在负环。

- **经过 $S$ 节点**

经过 $S$ 节点的环无论回不回 $S$ 节点都一样，因为从所有点指向 $S$ 节点的边权都为 $0$，所以就是判断有没有从 $S$ 出发到达任意一个节点，因为任意节点都可以回到 $S$ 节点。而从其它节点出发的并经过 $S$ 节点的环都可以转化成从 $S$ 节点出发的环。

对于这个问题，我们处理出来每个点能向后走的最长距离 $S_i$，并在循环过程中寻找一个最大的 $S_i-b_i$，可以理解为从 $S$ 出发到达的任意点中距离最长的一个，如果当前的 $S$ 减去之前最大的 $S_i-b_i$ 大于等于 $0$，就是最外面的环长度最大的加上从 $S$ 出发到这个最小的链的第一个节点的距离（这也是为什么要选最大的值的原因，这样才能把距离保持最小），那么就不存在负环，否则这条链加上边权为 $0$ 的从链最后指向 $S$ 的边的这个环的边权之和就小于 $0$，代表这个图中存在负环，所以就无解。

**注意！这里是环，所以需要把环复制一遍接在后面，这样就可以处理环上问题了。还要开上 `long long`！**

明显这样的做法的时间复杂度和空间复杂度都是 $O(N)$ 的，过掉这道题绰绰有余。

# 代码时间

```cpp
#include <iostream>
#define int long long

using namespace std;

const int N = 1e6 + 10;
int n, a[N], b[N];

void solve() {
	scanf("%lld", &n);
	int sum = 0;
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), sum -= a[i];
	for (int i = 1; i <= n; i++) scanf("%lld", b + i), sum += b[i];
	if (sum < 0) { // 最外围的环（不包括点 S）
		puts("NO");
		return;
	}
	sum = 0;
	int mx = -b[1];
	for (int i = 1; i <= (n << 1) + 1; i++) {
		sum += b[i % n + 1] - a[i % n + 1]; // 取代直接复制一遍
		mx = max(mx, sum - b[i % n + 1]);
		if (mx > sum) {
			puts("NO");
			return;
		}
	}
	puts("YES");
}

signed main() {
	int T;
	scanf("%lld", &T);
	while (T --> 0) solve(); 
	return 0;
}
```

---

## 作者：wgyhm (赞：1)

Hall 定理的推论。

### 题意：

 $n$ 个城市，这 $n$个城市首尾相接形成一个环。每个城市需要 $a_i$ 个网络数量。$n$ 个网络基站，第 $i$ 个网络基站有 $b_i$ 的网络数量，可以给 $i$ 和 $i+1$ 提供 网络。（第 $n$ 个网络基站可以给第 $n$ 座城市和第 $1$ 座城市提供网络）。

判断能否使得所有的家庭都获得网络。

$n\le 10^6$。



### Hall 定理的推论

Hall 定理可以用于点有权值的情况。左部点 $i$ 需要匹配 $a_i$ 个右部点，右部点 $i$ 需要匹配 $b_i$ 个左部点。**匹配是可重复的。**只需要将定理改写一下。其有完美匹配的充要条件为：
$$
\forall S\subseteq X,|\sum\limits_{x\in S}a_x|\le |\sum\limits_{y\in N(S)}b_y|
$$
证明可以将左部点 $i$ 拆成 $a_i$ 个点，右部点同样。发现此条件和原本的 Hall 定理是等价的。

### 做法

显然是个带权二分图求完美匹配的题。

考虑枚举城市的集合 $L$，如果 $L$ 不是一个连续的区间，判断其是否合法，与其中每个连续的区间分别同时满足判定的条件是等价的。

转化为对于任意区间 $[l,r]$，$\sum\limits_{i=l}^r a_i\le \sum\limits_{i=l-1}^rb_i$ 都成立。

前缀和结合后缀最大值即可。题目要求为环的情况，断环为链。

### CODE

```cpp
int a[maxn],b[maxn],n,d[maxn],suf[maxn];
inline int solve(void) {
	int i,sum1=0,sum2=0;
	read(n);
	for (i=1;i<=n;i++) read(a[i]);
	for (i=1;i<=n;i++) read(b[i]),d[i]=a[i]-b[i],sum1+=d[i];
	if (sum1>0) return puts("NO");
	for (i=1;i<=n;i++) a[i+n]=a[i],b[i+n]=b[i];
	for (i=1;i<=n*2;i++) d[i]=d[i-1]+b[i]-a[i];
	for (suf[n*2+1]=1e18,i=n*2;i>=1;i--) suf[i]=min(suf[i+1],d[i]);
	for (i=1;i<=n;i++) {
		if (suf[i+1]-d[i]+b[i]<0) return puts("NO");
	}
	return puts("YES");
}
```







---

## 作者：intel_core (赞：1)

首先，很明显 $\sum b_i \ge \sum a_i$ 是必要条件。

现在我们假设有至少种分配方案可行，设 $i+1$ 城市帮 $i$ 城市分担了 $c_i$ 户家庭，则存在一种方案使得存在 $k$ 满足 $c_k=0$。

> 简证：任取一种方案，如果不存在这样的 $k$ ，设 $m=\min c_i $，那么将所有 $c_i$ 都变成 $c_i-m$，那么一定有一种合法的方案对应新的 $\{c_i \}$，且有 $k$ 满足 $c_k=0$。

所以我们现在假定 $p$ 城市的家庭连的都是 $p$ 城市的基站（$b_p \ge a_p$）。

现在 $p+1$ 城市家庭可以连到 $p+1,p+2$ 城市的基站，所以应该有 $a_{p+1} \le b_{p+1}+b_{p+2}$。

因为 $p$ 城市不会对 $p+1$ 造成任何影响，所以 $p+1$ 城市的家庭尽量都要连到 $p+1$ 城市的基站上；可以求出 $p+1$ 对 $p+2$ 的影响是 $\min \{0,a_{p+1}-b_{p+1} \}$。

所以 $p+2$ 城市的所有家庭能连上网就等价于 $a_{p+1}+a_{p+2} \le b_{p+1}+b_{p+2}+b_{p+3}$。

类似的，也应有 $\sum_{i=1}^k a_{p+i} \le \sum_{i=1}^{k+1}b_{p+i}$ 对于所有的 $k$ 都成立。

令 $s_k=\sum_{i=2}^{k+1}b_i-\sum_{i=1}^k a_i$ ，则条件转化为 $s_{k+p}-s_{p-1}+b_p \ge 0$ 对于所有 $k$ 都成立，即 $\min s_i \ge s_{p-1}-b_p$。

用单调队列 $O(n)$ 求区间最小值即可。

---

## 作者：chenxia25 (赞：1)

刷了 5 个 2400~2600 题了，还真就第一个遇到不会做的题，而且还是个 2400。看来我思维水平为
$$
\Huge\mathrm e^{\pi \mathrm i}+1
$$

---

**[Portal]( https://www.luogu.com.cn/problem/CF1373F )**

### 线性对数做法

先讲一个大部分人用的线性对数做法。

注意到，每个 city 显然是由相邻两个 station 共同贡献的。那么显然，如果确定了这 $2n$ 个贡献中的一个，那么就可以贪心地推出来其他 $2n-1$ 个，然后判断是否可行。

我们设第一个是 $?+x$，那么推出来的结果大概是

|         $?$          |              $x$              |
| :------------------: | :---------------------------: |
|       $b_1-x$        |       $M(a_2-(b_1-x))$        |
| $b_2-M(a_2-(b_1-x))$ | $M(a_3-(b_2-M(a_2-(b_1-x))))$ |
|       $\cdots$       |           $\cdots$            |

其中 $M(x)=\max(0,x)$。其中左一列就是当前 $b$ 最多能给它贡献多少了，不考虑超过了 $a_i$。最后会循环到左上角，发现左上角的式子是最长的。

注意到，左边一列任意一个如果 $<0$，就说明它上一行右边用的超过当前 $b$ 了，也就是当前 $b$ 不够用了，那肯定是不行的。如果都够用的话，还需要考虑到头来 $a_i$ 能不能被第一行两个数的和所 $\geq$。于是有解也就当且仅当能找到 $x\geq 0$ 满足这两个条件。

然后我们想到，总不能枚举这个 $x$ 吧，它可是关于值域的。那么二分？我证不出来它有单调性。但是注意到，$x$ 合法所要满足的两个条件分别关于 $x$ 满足单调性：

1. 容易发现，$x$ 增加一，那么左边一列全部都减少 $0\sim 1$，右边一列都增加 $0\sim 1$。那么 $x$ 越大，左边就越可能挂掉；$x$ 越小，左边就越会活得好好的。所以说这样可以二分出 $x$ 的一个上界；
2. 又因为 $x$ 增加一是铁定增加一的，而此时左上角有可能增加一，有可能不动。那么长期增加下来，第一行的和只会不减，于是 $x$ 越大，第二个条件就越容易满足。所以可以二分出 $x$ 的一个下界。

于是看下界是否 $\leq$ 上界即可。

**_[code]( https://www.luogu.com.cn/paste/dell7egl )_**

---

### 线性做法

会讲两个线性做法。~~这都是我在学校和路上苦思冥想的结果啊，精通时事的人应该看到了我一边拿草稿本一边走路（~~

刚开始做的时候用的就是下面的其一，只不过我有东西没考虑到，所以最终还是看题解了/ll

其一是继续在刚刚的做法的列表格的基础之上做。我们考虑分别探索两个条件的充要条件：

1. $\forall N\in[1,n],b_N-M(a_N-\cdots)\geq0$。移项得到 $M(a_N-\cdots)\leq b_N$。此时这个 $M$ 非常好去，注意到若里面 $<0$，泽肯定成立，去掉 $M$ 也肯定成立，所以无伤大雅；若里面 $\geq 0$，则去不去 $M$ 值一样。于是可以直接去掉 $M$，得到 $a_N-\cdots\leq b_N$，即 $\cdots\geq a_N-b_N$。于是可以（近似的）归纳到 $b_{N-1}-M(a_{N-1}-\cdots)\geq a_N-b_N$。那么是否还可以像上面那样想当然地直接得到 $\cdots\geq a_N-b_N+a_{N-1}-b_{N-1}$ 呢？nope。

   注意到到 $M(a_{N-1}-\cdots)\leq b_{N-1}-a_N+b_N$ 这一步，这时候右边不一定 $\geq0$（这就是我一开始的思路，但是没想到这一个问题，所以就 WA 了）。如果右边 $<0$，此时左边显然 $\geq$，不等式不可能成立；否则依然可以照上面分析，归纳下去。于是我们多了一系列条件：归纳的过程中，$M$ 左边的那串式子必须 $\geq0$。

   于是我们得到：$\forall N\in[1,n],\forall l\in(1,n],\sum\limits_{i=l}^Nb_i-\sum\limits_{i=l+1}^Na_i\geq 0$，并且 $x$ 满足 $\forall N\in[1,n],x\leq\sum\limits_{i=1}^Nb_i-\sum\limits_{i=2}^Na_i$。

2. $b_n-M(a_n-\cdots)+x\geq a_i$。这就相当于上面的不等式的右边从 $0$ 变成了 $a_i-x$。类似上面分析 $M$、归纳，我们可以得到 $\forall l\in(1,n],\sum\limits_{i=l}^nb_i-\sum\limits_{i=l+1}^na_i-a_1+x\geq 0\Leftrightarrow x\geq \sum\limits_{i=l+1}^na_i+a_1-\sum\limits_{i=1}^nb_i$。然后最后一步得到 $x\leq \sum\limits_{i=1}^nb_i-\sum\limits_{i=1}^na_i+x$，$x$ 直接消掉得到了一个不关于 $x$ 的条件。

就把上面得到的不关于 $x$ 的条件直接判，关于的发现有上界和下界，分别取 $\min$ 和 $\max$，最后看 $x$ 是否有解，别忘了 $x\geq0$。至于说有平方级个条件，那没关系，前缀和拆一拆递推一下即可。

**_[code]( https://www.luogu.com.cn/paste/ket12h4m )_**

---

其二。

其实做什么图论建模（比如网络流）做多了的人，看到这题都会感觉要建图。比如差分约束或者网络流。网络流其实是可以的，zqynb，但我不会。下面讲的是差分约束的方法。

依然考虑 $2n$ 个贡献，我们设它们为 $x_{i,1/2}$。显然可以列出一堆关于它们的不等式：
$$
\begin{cases}x_{i,1}+x_{i,2}\geq a_i\\x_{i,2}+x_{i+1,1}\leq b_i\\x_{i,1/2}\geq 0\end{cases}
$$
但是这里是 $+$ 号，差分约束个锤子啊？不急，不难发现前两条里面都是一个 $1$ 一个 $2$，于是我们可以用 $-x_{i,2}$ 来搞，这样就可以差分约束了。

然后判有解性即可。显然不等式的个数是线性的，那么直接 SPFA 是平方的，会爆炸。但注意到这个建图还是蛮有规律的，考虑能不能用一些巧妙的方法判负环的存在性，就好似以前做过的某个巧妙求最短路的题一样。

把 $n=4$ 的图画出来，还挺 good-looking 的（

![](https://s3.ax1x.com/2020/11/12/DSmV0J.png)

注意到，所有的环分为含 $0$ 的环和不含 $0$ 的环，我们只需要判断每个环都是非负环即可：

1. 含 $0$。那么 $0$ 两边只能是左边是正，右边是负，也就是正的每个到负的每个的路径要非负，即：

   - 对于 $u>v$ 有 $\sum\limits_{i=v}^{u-1}b_i-\sum\limits_{i=v+1}^{u-1}a_i\geq 0$；
   - 对于 $u\leq v$ 有 $sb-\sum\limits_{i=u}^{v-1}b_i-sa+\sum\limits_{i=u}^va_i\geq 0$，其中 $sa,sb$ 分别为 $a,b$ 的和。

   看似有平方级个条件，但按照上一个方法拆前缀和递推即可；

2. 不含 $0$。那显然只有一个环：$sb-sa$。

**_[code]( https://www.luogu.com.cn/paste/9hkb7k4o )_**

---

然后这两种线性方法的条件集合按理说应该是等价的，看上去也很等价。但我不想想了。

---

## 作者：违规用户名76G!ihcm (赞：1)

### 题意

有 $n$ 个城市和发电站，第 $i$ 个城市需要 $a_i$ 个单位的电，第 $i$ 个发电站可以给第 $i$ 或 $i+1$ 个城市供电（第 $n$ 个给的是 $n$ 和 $1$），这个发电站给两城市供电总量最多 $b_i$ 个单位，问是否能满足所有城市的需求。

$n \leq 10^6$，$a_i,b_i \leq 10^9$

### 题解

原题要求每个发电站最多供 $b_i$ 的电，每座城市要有 $a_i$ 的电，问是否可行。

和每个城市必须供 $b_i$ 的电，每座城市要有至少 $a_i$ 的电，问是否可行等价。

设第 $i$ 和发电站给第 $i$ 个城市供了 $x_i$ 的电，则给第 $i+1$ 个城市供了 $b_i -x_i$ 的电。

那么对于每个 $i$ 需要满足：

$$x_i+(b_{i-1}-x_{i-1})\geq a_i$$ 

移项后得：

$$x_i-x_{i-1}\geq a_i-b_{i-1}$$

差分约束后可以求出所有 $x_i$，判断是否 $\in [0,b_i]$ 即可。

注意要特判一下 $\sum b_i <\sum a_i$ 的情况（这样是负环，$10^6$ 个点判起来有点慢）
### 代码

```cpp
#include <iostream>
#include <queue>
#include <cstdio>
#define int long long
using namespace std;
struct edge
{
	int v,n,w;
}e[2000005];
int head[1000005],cnt,dis[1000005],CNT[1000005],vis[1000005],a[1000005],b[1000005];//这个CNT[]是差分约束板子里判负环的，好像这道题里没用（
inline void add(int u,int v,int w)
{
//	cout << u << " " << v << " " << w << "\n";
	e[++cnt]={v,head[u],w};
	head[u]=cnt;
}
queue <int> q;
signed main(int argc, char** argv) {
	int T;
	cin >> T;
	while(T--)
	{
		int n;
		cin >> n;
		int s=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),s+=a[i];
		for(int i=1;i<=n;i++)
			scanf("%d",&b[i]),s-=b[i];
		if(s>0)
		{
			puts("NO");
			continue;
		}
		cnt=0;
		for(int i=1;i<=n+1;i++)
			head[i]=0,vis[i]=0,CNT[i]=0;
		for(int i=1;i<=n;i++)
		{
			int nxt=i-1;
			if(!nxt) nxt=n;
			add(nxt,i,-(a[i]-b[nxt]));
		}
		dis[n+1]=0,q.push(n+1),vis[n+1]=1;
		for(int i=n;i>=1;i--) dis[i]=1e18,add(n+1,i,0);
		while(!q.empty())
		{
			int x=q.front();
	//		cout << x << " " << dis[x] << "\n";
			q.pop(),vis[x]=0;
			
			for(int i=head[x];i;i=e[i].n)
			{
				if(dis[e[i].v]>dis[x]+e[i].w)
				{
					dis[e[i].v]=dis[x]+e[i].w;
					if(!vis[e[i].v]) q.push(e[i].v),++CNT[e[i].v];
					vis[e[i].v]=1;
					if(CNT[e[i].v]>=100)
					{
						puts("-1");
						return 1;
					}
				}
			}
		}
		int flag=0;
		for(int i=1;i<=n;i++)
			if(-dis[i]>b[i]) flag=1;
		if(flag) puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：Qiaoqia (赞：0)

其实这是个结论题（  
做的时候没有想到有单调性可以二分也没有想到可以差分约束更没有想到模拟最大流，于是想出了个和现有题解都不同的线性做法。

结论是：若对于环上所有区间，满足这段 $a$ 的和不超过能贡献到这段的 $b$ 的和，则有解，否则无解。特别地，$b$ 不能算重复的点。

必要性是显然的，不然全部贡献这一段都没法满足。

我们找一个点把环展开成链，在满足上面条件的情况下，除了涉及头尾的可能不再满足能贡献它的 $b$ 和大于等于它，其它都不受影响。事实上，一定可以找到一个断点使头尾也不受影响。

受影响的只有可能是头尾中的一个，所以只要找 $a_i$ 可以被仅一个 $b$ 完全贡献的位置断开就好了。这样的位置是一定存在的，因为如果每个 $a_i$ 都大于 $b_i$，那么就不可能满足 $\sum a \le \sum b$ 了。

从这个位置断开之后，每加入一个 $a_i$，上面的条件就意味着前面的都被贡献完之后剩下来的仍然可以满足 $a_i$，这样就意味着一直到最后都存在分配方案使 $a$ 都被满足（手玩一下很好理解）。

那么把 $a,b$ 都复制一遍，做个前缀和，问题就变成了对于长度不超过 $n$ 的区间 $[i, j]$，都必须有 $\operatorname{sum}_a(j) - \operatorname{sum}_a(i) \le \operatorname{sum}_b(j) - \operatorname{sum}_b(i  - 1)$，移项后就是对于每个位置，后面长度不超过 $n$ 的位置里最大的 $\operatorname{sum}_a(j) - \operatorname{sum}_b(j)$ 不能大于 $\operatorname{sum}_a(i) - \operatorname{sum}_b(i - 1)$，用单调队列滑动窗口求区间最大值后判断即可。

CF 提交记录：[#150661563](https://codeforces.com/contest/1373/submission/150661563)。

独立想出这种结论题的做法还是很舒适的 ![](//图.tk/6)。

---

