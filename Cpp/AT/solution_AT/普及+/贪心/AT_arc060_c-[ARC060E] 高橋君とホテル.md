# [ARC060E] 高橋君とホテル

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc060/tasks/arc060_c

$ N $ 軒のホテルが一直線上に並んでいます。$ i\ \,\ (1\ \leq\ i\ \leq\ N) $ 番目のホテルは、座標 $ x_i $ に位置しています。

旅行者である高橋君には、次の $ 2 $ つの信念があります。

- 高橋君の $ 1 $ 日の移動距離は $ L $ を超えない。
- 高橋君は野宿をしない。すなわち、$ 1 $ 日の終わりには必ずいずれかのホテルにいなければならない。

$ Q $ 個のクエリが与えられます。$ j\,(1\ \leq\ j\ \leq\ Q) $ 番目のクエリとして、異なる $ 2 $ つの整数 $ a_j,\,b_j $ が与えられます。 各クエリについて、前述の信念をともに守った上で、高橋君が $ a_j $ 番目のホテルから $ b_j $ 番目のホテルに移動するために必要な最小日数を求めてください。 なお、高橋君が $ a_j $ 番目のホテルから $ b_j $ 番目のホテルに移動できることは保証されます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ L\ \leq\ 10^9 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 1\ \leq\ x_i\ <\ x_2\ <\ ...\ <\ x_N\ \leq\ 10^9 $
- $ x_{i+1}\ -\ x_i\ \leq\ L $
- $ 1\ \leq\ a_j,b_j\ \leq\ N $
- $ a_j\ \neq\ b_j $
- $ N,\,L,\,Q,\,x_i,\,a_j,\,b_j $ はいずれも整数である

### 部分点

- $ N\ \leq\ 10^3 $ および $ Q\ \leq\ 10^3 $ を満たすデータセットに正解した場合は、$ 200 $ 点が与えられる。

### Sample Explanation 1

$ 1 $ つ目のクエリでは、次のように行動することで、$ 1 $ 番目のホテルから $ 8 $ 番目のホテルへ $ 4 $ 日間で移動することができます。 - $ 1 $ 日目には、$ 1 $ 番目のホテルから $ 2 $ 番目のホテルへ移動する。この日の移動距離は $ 2 $ である。 - $ 2 $ 日目には、$ 2 $ 番目のホテルから $ 4 $ 番目のホテルへ移動する。この日の移動距離は $ 10 $ である。 - $ 3 $ 日目には、$ 4 $ 番目のホテルから $ 7 $ 番目のホテルへ移動する。この日の移動距離は $ 6 $ である。 - $ 4 $ 日目には、$ 7 $ 番目のホテルから $ 8 $ 番目のホテルへ移動する。この日の移動距離は $ 10 $ である。

## 样例 #1

### 输入

```
9
1 3 6 13 15 18 19 29 31
10
4
1 8
7 3
6 7
8 5```

### 输出

```
4
2
1
2```

# 题解

## 作者：GaryH (赞：8)

# AT2039 题解

[题目传送门](https://www.luogu.com.cn/problem/AT2039)

前置算法：

1. 倍增
2. 尺取法

首先简化题意。

原题中要求为：初始给定一个有序的序列，将每次给定的询问区间分成几段，使每一段左右端点差不超过L，问分成的最小段数。

这种题型是一个套路，即在这种“**将区间按某种限制分段**”，**并使段数最小**的套路里，我们一般可以使用倍增加各种预处理解决。在这道题里，就是将每个点往后划分2的次幂个区间，最远可以划分到的点的位置预处理出来，最后在倍增求解。

当然，这种对划分区间长度的限制必须具有**单调性**，否则“**相同划分区间数与相同左端点，右端点越远越优**”的命题就不成立，我们也自然无法用这种方法求解。

所以我们来分析，这个题里划分区间的限制是否具有单调性。

题中要求“每个区间左右端点差不超过L”，而这显然具有单调性。因为若原来有一个区间符合要求，将左端点右移后，还要使区间符合要求，**右端点必不会往左移**。所以，我们接下来只需要处理出每个点往右符合“左右端点差不超过L”这个要求的**极长扩展右区间**，然后以此为基础，处理倍增数组即可。

至于如何处理每个点往右符合“左右端点差不超过L”的极长扩展右区间，二分是一个很好想的方法，但是这里我们使用相比二分更优的方法，即**双指针**。因为前面证明的区间限制单调性，也同样是使用双指针的限制。实现的方法就是，设定左右端点，伴随着左端点的右移，右端点当前的位置就是左端点的极长扩展区间。

做完这道题后，可以去做一做这两道题：

[CF1516D CUT](https://www.luogu.com.cn/record/list?user=100091&pid=CF1516D&page=1)


[nowcoder C 哲学家的沉思](https://ac.nowcoder.com/acm/contest/11175/C)

这两道题都和本题的大体思路一样，只是在预处理是有一些小的改动。

**CODE:**

```
#include<bits/stdc++.h>

#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)

using namespace std;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')f=ch=='-'?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x*f;
}

const int M(30);
const int N(1e5+10);

int n,L;

int x[N];
int sum[N];
int st[N][M+5];

inline int qry(int l,int r){
	int ans=1;
	per(i,M,0)if(st[l][i]<r)l=st[l][i],ans+=(1<<i);
	return ans;
}

signed main(){
	n=read();
	rep(i,1,n)x[i]=read();
	L=read();
	for(int l=1,r=0;l<=n;l++){
		while(r<=n&&x[r]-x[l]<=L)r++;
		if(x[r]-x[l]<=L){
			while(l<=n)st[l][0]=n+1,l++;
			break;
		}
		else st[l][0]=(--r);
	}
	st[n][0]=n+1;
	rep(j,1,M)rep(i,1,n){
		if(st[i][j-1]>n)st[i][j]=1e9;
		else st[i][j]=st[st[i][j-1]][j-1];
	}
	int q=read();
	rep(i,1,q){
		int a=read(),b=read();
		if(a>b)swap(a,b);
		cout<<qry(a,b)<<endl;
	}
	return 0;
}
```

好了，本题题解就到这里了，再见！

---

## 作者：封禁用户 (赞：5)

这是本**蒟蒻**的第一篇题解，希望大家多多支持啊。

点击[这里](https://www.luogu.com.cn/blog/TO676469346s/fen-kuai-er-fen)效果更佳。

*（分割线）*

------------

首先先介绍一下思路。

### 分块+二分。

因为这题 $n\le10^5$，直接暴力肯定肯定是过不了的。

那么就需要我们的优化神器**分块**。

用 $block$ 记录块的大小为 $\sqrt{n}$。

$cnt_{i}$ 记录当前 $i$ 跳出这个块最少需要多少步。

$nxt_{i}$ 记录当前 $i$ 跳出这个块之后到达的是哪个点。

```cpp
for(int i=tot;i>=1;i--)//tot为块的总数
{
	for(int j=t[i].r;j>=t[i].l;j--)//l,r分别为当前块的左右节点
	{
		int k=find(j+1,n,a[j]+L);
		if(k>t[i].r) cnt[j]=1,nxt[j]=k;
		//直接跳出这个块
		else cnt[j]=cnt[k]+1,nxt[j]=nxt[k];
		//跳不出这个块,那么就跳到k,让k去跳
	}
}
```

### 现在，问题来了。

因为我们是预处理的 $nxt_{i}$，枚举每一个 $i$ 需要 $O(n)$，现在如何在优于  $O(\sqrt{n})$ 的时限内求出 $nxt_{i}$。

相信聪明的朋友们已经想到了。

### 二分。

记 $i$ 点能到达的最远距离为 $x$ ，那么我们用二分去找最大的 $j$ 使得 $a_{j}\le x$。

二分代码如下。
```cpp
int find(int l,int r,int x)
{
	int ans=l;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(a[mid]>x) r=mid-1;
		else ans=mid,l=mid+1;
	}
	return ans;
}
```

AC 代码。
```cpp
#include<bits/stdc++.h>
#define M 100001
using namespace std;
inline int read()
{
	int k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
int n,a[M],block,L,Q,tot;
int nxt[M],cnt[M];
struct node
{
	int l,r;
}t[M];
int get(int i)
{
	return (i-1)/block+1;
}
int find(int l,int r,int x)
{
	int ans=l;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(a[mid]>x) r=mid-1;
		else ans=mid,l=mid+1;
	}
	return ans;
}
void ask(int l,int r)
{
	int num=0;
	while(get(l)!=get(r)&&l<r)
	{
		num+=cnt[l];
		l=nxt[l];
	}
	while(l<r)
	{
		int k=find(l+1,n,a[l]+L);
		l=k;
		num++;
	}
	printf("%d\n",num);
}
int main()
{
	n=read();
	block=pow(n,0.5);
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		int idx=get(i);
		if(!t[idx].l) t[idx].l=i;
		t[idx].r=i;
	}
	L=read(),Q=read();
	tot=get(n);
	for(int i=tot;i>=1;i--)//tot为块的总数
	{
		for(int j=t[i].r;j>=t[i].l;j--)//l,r分别为当前块的左右节点
		{
			int k=find(j+1,n,a[j]+L);
			if(k>t[i].r) cnt[j]=1,nxt[j]=k;
			//直接跳出这个块
			else cnt[j]=cnt[k]+1,nxt[j]=nxt[k];
			//跳不出这个块,那么就跳到k,让k去跳
		}
	}
	while(Q--)
	{
		int l=read(),r=read();
		if(l>r) swap(l,r);
		ask(l,r);
	}
	return 0;
}

```
## 谢谢！

---

## 作者：君のNOIP。 (赞：5)

#### 数据范围：

- $N \le 10^5 $ ， $L \le 10^9$ ， $Q \le 10^5$ 

- 部分分： $N \le 10^3 $ ，$Q \le 10^3$ 

------------


#### 对于部分分， $\Theta ( NQ)$ 暴力：

~~一步一步走就好，不必多言。~~

------------
然后考虑正解。

很明显，对于每次询问，可以**二分**直接跳到下一个最远の一次能到达の点。

~~撒花完结。（雾~~

~~毕竟好歹是一道绿题~~，怎么可能那么简单？

随便出一组样例：

------------
```
5
2 4 6 8 10
2
5
1 5
1 5
1 5
1 5
1 5
```


------------
这样每次都只能跳一格，很明显复杂度达到了 $\Theta(NQlogN)$

~~比暴力还慢。~~

我们发现如果一次只跳一天，是肯定会 $TLE$ 的。

于是我们考虑如何优化。

我一开始是想~~暴力~~分块，甚至想起了莫队。

~~好，想不出来~~（后来发现楼上就是分块  orz

不过我们想一次跳很多步，可以想到用**倍增**。

## **正片开始：**

#### **基本思路：$f_{i,k}$ 表示从第 $i$ 个点走 $k$ 步能到达の最远の点。**

考虑状态转移方程：

- $i$ 点走 $2^{k-1}$ 步到达 $f_{i,k-1}$

- $f_{i,k-1}$ 点再走 $2^{k-1}$ 步便到达 $f_{i,k}$

- 所以 $f_{i,k} \gets f_{{f_{i,k-1}},k-1} $ 


**初始化 $\Theta ( N)$：**

------------
```cpp
int t=0;
for(int i=1;i<=n;i++){
	while(va[t+1]-va[i]<=L&&t<n)t++;
	dp[i][0]=t;
} //这种方法很明显比二分法更快更好写。
```


------------


**预处理 $\Theta ( NlogN)$：**

------------
```cpp
for(int k=1;k<=16;k++)
	for(int i=1;i<=n;i++)
		dp[i][k]=dp[ dp[i][k-1] ][k-1];
```


------------

**询问部分 $\Theta ( QlogN)$：**


------------
```cpp
q=rd(); //读入
while(q--){
	l=rd(),r=rd();
	if(l>r)swap(l,r); //可以发现正着走反着走是一样的
	ans=0;
	for(int i=16;i>=0;i--)if(dp[l][i]<r)l=dp[l][i],ans+=lg[i];   //lg[i]表示2^i，从最大开始，如果走2^i次不能到r就走。
	printf("%d\n",ans+1);  //最后答案加1就能到r
}
```


------------

### 完整代码 $\Theta ( (N+Q)logN )$：

------------
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define G() Cr=getchar()
int Xr;char Cr;
inline int rd(){   //读入优化
	Xr=0,G();
	while(Cr<'0'||Cr>'9')G();
	while(Cr>='0'&&Cr<='9')Xr=(Xr<<3)+(Xr<<1)+Cr-'0',G();
	return Xr;
}
#define MAX_N 100002
int n,va[MAX_N];
int L,q,l,r,ans;
int lg[20],dp[MAX_N][20]; 
int main(){
	n=rd();
	for(int i=1;i<=n;i++)va[i]=rd();
	L=rd();
	lg[0]=1;
	for(int i=1;i<=16;i++)lg[i]=lg[i-1]<<1; // 预处理 2^i
	
	int t=0;
	for(int i=1;i<=n;i++){
		while(va[t+1]-va[i]<=L&&t<n)t++;
		dp[i][0]=t;
	}
	
	for(int k=1;k<=16;k++)
		for(int i=1;i<=n;i++)
			dp[i][k]=dp[ dp[i][k-1] ][k-1];
	
	q=rd();
	while(q--){
		l=rd(),r=rd();
		if(l>r)swap(l,r);
		ans=0;
		for(int i=16;i>=0;i--)if(dp[l][i]<r)l=dp[l][i],ans+=lg[i];
		printf("%d\n",ans+1);
	}
}
```


------------

~~跑得特别快，luogu第2~~

#### 真 $\bullet$ 撒花完结（逃


---

## 作者：henry_y (赞：4)

[推一下博客](http://www.cnblogs.com/henry-1202)

## 做法：分块+二分

首先用二分求出每个点每一天能够走到哪个点（贪心地想，能走更远肯定走更远，至于如果走过了，肯定在那天的一半的时候就走到目的地了，所以时间花费还是一样的）

然后我一开始是只处理出这个然后就一个个去跳了...结果只$A$了第一个点，其他全部$TLE$

所以要考虑优化，想了好久忽然想起弹飞绵羊那题，这题除了没有修改操作其实是和弹飞绵羊差不多的

所以大力分块！

二分预处理不变，然后对原序列分块。再维护一下每个点跳出该块后在哪以及跳出该块要花多少天

在查询的时候就可以一个块一个块的跳跳到目的地所在的那一块，剩下的路径暴力就可以

复杂度是$O(nlogn+q\sqrt{n})$的，AtCoder的时限三秒，很松，能过

 我写完后上网看了一下别人的做法怎么清一色的倍增...

```
#include <bits/stdc++.h>

using namespace std ;

#define N  100010

int n , L , m ;
int a[ N ] , to[ N ] ;
int num , block , belong[ N ] ; 
int nxt[ N ] , val[ N ] ;

int find( int x ) {
	int l = x + 1 , r = n , ans = 0 ;
	while( l <= r ) {
		int mid = ( l + r ) >> 1 ;
		if( a[ mid ] - a[ x ] <= L ) l = mid + 1 , ans = mid ;
		else r = mid - 1 ;
	}
	return ans ;
}

int main() {
	scanf( "%d" , &n ) ;
	for( int i = 1 ; i <= n ; i ++ ) {
		scanf( "%d" , &a[ i ] ) ;
	}
	sort( a + 1 , a + n + 1 ) ;
	scanf( "%d%d" , &L , &m ) ;
	for( int i = 1 ; i < n ; i ++ ) {
		to[ i ] = find( i ) ;
	}
	to[ n ] = n + 1 ;
	block = sqrt( n ) ;
	num = n / block ;
	if( n % block ) num ++ ;
	for( int i = 1 ; i <= n ; i ++ ) {
		belong[ i ] = ( i - 1 ) / block + 1 ;
	}
	for( int i = 1 ; i < n ; i ++ ) {
		int t = i , sp = 0 ;
		while( belong[ t ] == belong[ i ] ) {
			t=to[ t ] ;
			sp ++ ;
		}
		val[ i ] = sp ;
		nxt[ i ] = t ;
		if( i >= block * ( num - 1 ) + 1 ) val[ i ] -- , nxt[ i ] -- ;
	}
	for( int i = 1 ; i <= m ; i ++ ) {
		int x , y  , ans = 0 ;
		scanf( "%d%d" , &x ,&y ) ;
		if( x > y )swap( x , y ) ;
		while( belong[ x ] < belong[ y ] ) {
			ans += val[ x ] ;
			x = nxt[ x ] ;
		}
		while( x < y ) {
			x = to[ x ] ;
			ans ++ ;	
		} 
		printf( "%d\n" , ans  ) ;
	}
	return 0 ;
} 
```


---

## 作者：AlicX (赞：1)

## Solution 

很经典的套路题。

显然地，对于 $i$ 号旅店来说，每次走 $j$ 步可以到达的旅店是确定的，所以考虑 $O(n^2)$ 预处理出 $f_{i,j}$ 表示从 $i$ 号旅店开始走走 $j$ 步可以到达的旅店，然后参考倍增思想，有一个经典的优化：$f_{i,j}$ 表示从 $i$ 号旅店走 $2^j$ 步可以到达的旅店，则可以用二分找出 $f_{i,0}$，然后依次递推：$f_{i,j}=f_{f_{i,j-1},j-1}$，询问的时候从 $a$ 开始跳向 $b$ 点即可。时间复杂度为 $O(n \log n)$。

```cpp
const int N=1e5+10,M=20,INF=1e9+7;  
int L;  
int n,m;
int a[N]; 
int f[N][M]; 
signed main(){ 
	scanf("%d",&n); 
	for(int i=1;i<=n;i++) scanf("%d",&a[i]); a[n+1]=2*INF; 
	scanf("%d",&L); for(int i=1;i<=n;i++) f[i][0]=upper_bound(a+1,a+n+2,a[i]+L)-a-1; 
	for(int j=1;j<M;j++) for(int i=1;i<=n;i++) f[i][j]=f[f[i][j-1]][j-1]; 
	scanf("%d",&m); 
	while(m--){ int ans1=0,ans2=INF; 
		int s,t; scanf("%d%d",&s,&t); if(s>t) swap(s,t); 
		for(int j=M-1;j>=0;j--) if(f[s][j]<t) s=f[s][j],ans2=min(ans2,ans1+(1<<(j+1))),ans1+=(1<<j);  
		printf("%d\n",min(ans2,ans1+1)); 
	} return 0; 
} /* */ 
```



---

## 作者：Prean (赞：1)

怎么全是倍增啊，就没人来写个接近线性的算法吗

首先往右边跳，每次肯定跳得越远越优秀。

结束条件是什么？下标大于等于 $r$。

所以先把树建出来。

按照 $r$ 从大到小排序，相当于每次染色一个点，然后询问父亲中最深的被标记的节点。（$i<pre[i]$）

这样有点儿麻烦，转化成最浅的没被标记的节点。

现在可以按照 $r$ 从小到大排序了。$n$ 次并查集合并和 $m$ 次查询，可以做到 $O((n+m)\alpha(n))$。

也可以使用树上线性并查集做到真正的线性。

找 $pre$ 可以用双指针找，线性的。
```cpp
#include<cstdio>
#include<vector>
#include<cctype>
const int M=1e5+5;
int n,q,L,x[M],d[M],f[M],pre[M];std::vector<int>id[M];int l[M],r[M],ans[M];
inline int Find(const int&u){
	return f[u]==u?u:f[u]=Find(f[u]);
}
inline int read(){
	int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
}
inline void write(int n){
	static char s[10];int top(0);while(s[++top]=n%10^48,n/=10);while(putchar(s[top]),--top);putchar(10);
}
signed main(){
	n=read();for(int i=1;i<=n;++i)x[i]=read();L=read();x[n+1]=2.2e9;
	for(int R(n+1),i=n;i>=1;--i){
		while(x[R]-x[i]>L)--R;d[i]=d[pre[i]=R]+1;f[i]=i;
	}
	q=read();
	for(int i=1;i<=q;++i)l[i]=read(),r[i]=read(),l[i]>r[i]&&(l[i]^=r[i]^=l[i]^=r[i]),id[r[i]-1].push_back(i);
	for(int i=1;i<=n;++i){
		f[i]=pre[i];for(int&v:id[i])ans[v]=d[l[v]]-d[Find(l[v])];
	}
	for(int i=1;i<=q;++i)write(ans[i]);
}
```

---

## 作者：yxy666 (赞：0)

显然一步一步爬会超时。

那么想如何优化。

我们可以把一列数抽象成一个树链，那么如何快速找到两点之间的要走多少步？容易想到倍增。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int n,Ans,L,Q,pos[maxn],fa[maxn][21],lg[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	n=read();
	lg[1]=0;lg[2]=1;
	for(int i=1;i<=n;i++)pos[i]=read();
	for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
	L=read();
	int j=1;
	for(int i=1;i<=n;i++){
		while(pos[j]-pos[i]<=L&&j<=n)j++;
		j--;
		fa[i][0]=j;
		j++;
	}//用毛毛虫，也就是基于上一次的基础处理当前的f[i][0]
	for(int k=1;k<=20;k++)
	for(int i=1;i<=n;i++)fa[i][k]=fa[fa[i][k-1]][k-1];//倍增预处理
	Q=read();
	while(Q--){
		Ans=0;
		int x=read(),y=read();
		if(x>y)swap(x,y);//从左往右跳，两者是等价的
		int G=lg[y-x+1];
		for(int i=G+2;i>=0;i--)if(fa[x][i]<y)x=fa[x][i],Ans+=(1<<i);
		if(x<y)x=fa[x][0],Ans++;
		printf("%d\n",Ans);
	}
	return 0;
} //fa[x][i]表示从x开始，跳 2^i 次的最右端点 
```


---

## 作者：SMZX_LRJ (赞：0)

# 贪心 + 倍增

设数组 $fa_{i,j}$ 表示从 $i$ 号点出发走 $2^j$ 天最远到达的点。

类似 LCA 的预处理，从后往前预处理出 $fa$ 数组。

查询操作如下：

1. 若 $l>r$，则交换。不影响求解。

2. 使用指针。找到最小的大于 $r$ 的 $fa_{l,j}$。考虑跳 $2^j$ 步越过 $r$ 和跳 $2^{j-1}$ 步并重复当前操作两种选择。从其中求出最小值。

```cpp
int n,m,L,x[N],fa[N][19];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&x[i]);
	cin>>L;
	for(int i=1,j=1;i<=n;i++)
	{
		while(x[j]-x[i]<=L&&j<=n) j++;
		fa[i][0]=j-1;
	} 
	for(int i=n;i>=1;i--)
	for(int j=1;j<=18;j++)
	fa[i][j]=fa[fa[i][j-1]][j-1];
	cin>>m;
	while(m--)
	{
		int ans=0,ans2=1e9,l,r;
		scanf("%d%d",&l,&r);
		if(l>r) swap(l,r);
		for(int i=18;i>=0;i--)
		if(fa[l][i]<r)
		{
			ans2=min(ans2,ans+(1<<i+1));
			ans+=(1<<i);
			l=fa[l][i];
		}
		ans2=min(ans2,ans+1);//特判最后还要跳1步的情况
		printf("%d\n",ans2);
	}
	return 0;
}

```


---

## 作者：npqenqpve (赞：0)

算是半个经典套路了，贪心地，每一步走的应当尽量长；然而多次询问肯定不能直接跳，考虑将不久前做的 [弹飞绵羊](https://www.luogu.com.cn/problem/P3203) 的套路生搬硬套过来，记录按照贪心策略跳出这个块的时间和位置，直到跳到目标所在的块，可以通过记录 $d_{i,1/0}$ 表示 $i$ 跳出其所在块的第一个位置/时间实现；

还有些巧妙地倍增做法和上树做法。

[code](https://atcoder.jp/contests/arc060/submissions/33751808)

---

## 作者：Super_Builder (赞：0)

纪念模拟考考挂。

## 思路
首先二分查找出当前点往后走最远能去哪个点，当前点为 $i$，记最远能去的那个点为 $nt_i$。

考虑建一棵树，将 $nt_i$ 设为 $i$ 点的父节点。

暴力的话直接从当前点往上找，找到目标节点看几次就好了。

但显然是过不了的。

考虑使用倍增优化。

设 $g_{i,j}$ 为从 $i$ 往上跳 $2^j$ 次能到达哪个点，这个可以预处理。每次往上跳时，如果当前节点为 $nw$，则跳到 $g_{nw,j}$，$j$ 为当前指数，再将答案加上 $2^j$，然后能跳则跳，如果到了目标节点就可以退出了。整体类似求最近公共祖先。

### 注意
- 请记住，如果查找结束后并没有到目标节点，一定要将答案加上 $1$。不然会和我一样。

## AC CODE

希望这篇题解可以帮助到你。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f,a[100005],nt[100005],q,g[100005][22],dep[100005];
vector<int>e[100005];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	g[u][0]=fa;
	for(int j=1;(1<<j)<=dep[u];j++){
		g[u][j]=g[g[u][j-1]][j-1];
	}
	for(auto v:e[u]){
		if(v!=fa)dfs(v,u);
	}
} 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
	}
	scanf("%d",&f);
	for(int i=1;i<=n-1;i++){
		int l=i,r=n,pos=0;
		while(l<=r){
			int mid=l+r>>1;
			if(a[mid]<=a[i]+f){
				pos=mid;
				l=mid+1;
			}
			else {
				r=mid-1;
			}
		}
		nt[i]=pos;
	}
	for(int i=1;i<=n;i++){
		if(nt[i]!=i){
			e[nt[i]].push_back(i);
			e[i].push_back(nt[i]);
		}
	}
	dep[n+1]=-2;
	memset(g,0x3f,sizeof g);
	dfs(0,n+1);
	scanf("%d",&q);
	while(q--){
		int a,b;
		scanf("%d%d",&a,&b);
		if(a>b)swap(a,b);
		long long cnt=0;
		int now=a;
		for(int j=20;j>=0;j--){
			if((1<<j)<=dep[now]&&g[now][j]<=b){
				now=g[now][j];
				cnt+=(1<<j);
				if(now==b)break;
			}
		}
		if(now!=b)cnt++;//一定要加这句话，如果当前节点还没到，那么就要再多一天。
		printf("%lld\n",cnt);
	}
	return 0;
}
```


---

## 作者：BreakPlus (赞：0)

## [E - Tak and Hotels](https://atcoder.jp/contests/arc060/tasks/arc060_c)

倍增好题。

## Part1 询问祖先问题

类似于二分，倍增是一种利用二进制进行优化查找的方法。

比如，在多次询问一个点向上的第 $x$ 个祖先是多少的时候，我们就可以考虑倍增。

设 $\text{F}_{i,j}$ 表示从第 $j$ 个点向上的第 $2^i$ 个祖先是谁。

我们把 $x$ 看成二进制，比如 $100111$ 。

看下表。

| $i$ 的值 | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :----: |
| 二进制第 $i$ 位（从低到高） | $1$ | $1$ | $1$ | $0$ | $0$ |$1$ |
| 是否向上跳 $2^i$ 个 | 是 | 是 | 是 | 否 | 否 |是 |

利用 $F$ 数组，按照这样的表格来跳，很快能找到答案。这样，我们就可以在 $\log_2n$ 的时间复杂度内完成查找！

然后是初始化。 $\text{F}_{0,i}$ 是 $i$ 的父亲，$F_{i,j}=F_{i-1,F_{i-1,j}}$ （根据二进制的关系）

## Part2 引入本题

倍增的题，往往进入一个状态，下一个状态一定确定。

当高桥君走到第 $i$ 个旅店，为了快点走，他一定会走到离自己最远的、距离在范围内的旅店，所以下一个状态是确定的。

就像上一个问题一样，把从 $i$ 开始，当天能走到的最远的旅店视为 $i$ 节点的父亲，然后和上面的问题一样处理。

注意，此时我们不知道要跳多少次，但知道目的地。我们考虑倒序枚举 $i$：

如果从现在的位置走 $2^i$ 天还没有到达目的地，那么就走 $2^i$ 天；
否则看下一个 $i$。

最后，如果没有到达目的地，我们还需要将天数加 $1$。

$\large \text{Code:}$

```cpp
#include<iostream>
using namespace std;
int n,L,q,a[200010],jump[21][200010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>L>>q;
	for(int i=1;i<=n;i++){
		if(a[i]+L>a[n]){
			jump[0][i]=n+1;
			continue;
		}//如果超出了 a[n] ，走这一步不优，那么视为到达 n+1
		int l=i+1,r=n,mid,ans=i+1;
		while(l<=r){
			mid=l+r>>1;
			if(a[mid]-a[i]<=L){
				ans=mid;
				l=mid+1;
			}else r=mid-1;
		}
		jump[0][i]=ans;
	}// 二分预处理出每一个结点的父亲
	for(int i=0;i<=20;i++) jump[i][n+1]=n+1;
    
    //特判 n+1 
	for(int i=1;i<=20;i++)
		for(int j=1;j<=n;j++){
			jump[i][j]=jump[i-1][jump[i-1][j]];
		}// 初始化倍增
	while(q--){
		int x,y;
		cin>>x>>y;
		if(x>y){
			int t=x; x=y; y=t;
		}
		int nowx=x,tot=0;
		for(int i=20;i>=0;i--){
			if(jump[i][nowx]<=y){
				nowx=jump[i][nowx];
				tot+=(1<<i);
			}// 如果没有到达 y 那么跳
		}
		if(nowx<y) tot++;//还没到达加 1
		cout<<tot<<endl;
	}
	return 0;
}
```

---

