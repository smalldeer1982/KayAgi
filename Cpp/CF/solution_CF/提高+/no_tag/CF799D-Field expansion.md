# Field expansion

## 题目描述

In one of the games Arkady is fond of the game process happens on a rectangular field. In the game process Arkady can buy extensions for his field, each extension enlarges one of the field sizes in a particular number of times. Formally, there are $ n $ extensions, the $ i $ -th of them multiplies the width or the length (by Arkady's choice) by $ a_{i} $ . Each extension can't be used more than once, the extensions can be used in any order.

Now Arkady's field has size $ h×w $ . He wants to enlarge it so that it is possible to place a rectangle of size $ a×b $ on it (along the width or along the length, with sides parallel to the field sides). Find the minimum number of extensions needed to reach Arkady's goal.

## 说明/提示

In the first example it is enough to use any of the extensions available. For example, we can enlarge $ h $ in $ 5 $ times using the second extension. Then $ h $ becomes equal $ 10 $ and it is now possible to place the rectangle on the field.

## 样例 #1

### 输入

```
3 3 2 4 4
2 5 4 10
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 3 3 3 5
2 3 5 4 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5 5 1 2 3
2 2 3
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3 4 1 1 3
2 3 2
```

### 输出

```
3
```

# 题解

## 作者：yuzhechuan (赞：4)

### 题解：

虽然n给的范围很大，但首先要明确，最坏情况下也至多操作34次，因为$a,b\leq2^{17}$，所以34之后的操作都可以无视

这其实就说明这道题可以用指数级算法解决，如bfs

考虑在bfs设两个参数$x$和$y$，分别表示两边的目标放大倍数，并且使$x<y$

贪心的，操作肯定是从大到小选的

这样每次操作至多只会产生两种新状态，要么在$x$中砍掉一定倍数，要么在$y$中砍掉一定倍数

如果某个时刻$x$和$y$都等于1了，就说明已经合法，输出答案

否则到不了就无解输-1

---

下面的代码看起来可能是$2^{34}$的，但其实是$2^{17}$的，因为在一边达到目标倍数后，它的x就一直会保持1的状态被map记录下，不再增加新状态，从而就从双选变成单选了

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return  x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

#define pii pair<int,int>
#define x first
#define y second

const int N=1e5+5;
int a,b,h,w,n,val[N];
queue<pii> q;
map<pii,int> v; //map记录该状态有没有走过，至少走几步

pii adjust(pii x){ //维护x和y，使得x始终y
	if(x.x>x.y) swap(x.x,x.y);
	return x;
}

int divi(int x,int y){ //计算目标放大倍数
	return x/y+(x%y!=0);
}

signed main(){
	read(a);read(b);read(h);read(w);read(n);
	for(int i=1;i<=n;i++) read(val[i]);
	sort(val+1,val+1+n,greater<int>()); //倒着排序
	int lim=min(34,n); //最大操作次数
	pii hii=pii(divi(a,h),divi(b,w)),wii=pii(divi(a,w),divi(b,h)); //旋转也可以，所以有两种起始状态
	v[hii]=v[wii]=1; //起始步数为1
	q.push(hii);
	q.push(wii);
	while(!q.empty()){ //bfs
		pii now=q.front();
		q.pop();
		int step=v[now];
		if(now.x==1&&now.y==1){
			write(step-1); //操作次数=步数-1
			return 0;
		}
		if(step>lim) continue;
		pii nxt=adjust(pii(divi(now.x,val[step]),now.y)); //该操作给x
		if(v[nxt]==0){ //没有走过就走
			v[nxt]=step+1;
			q.push(nxt);
		}
		nxt=adjust(pii(now.x,divi(now.y,val[step]))); //该操作给y
		if(v[nxt]==0){
			v[nxt]=step+1;
			q.push(nxt);
		}
	}
	write(-1);
}
```

---

## 作者：_AyachiNene (赞：2)

# 思路：
首先有一个很显然的贪心，肯定把 $a_i$ 大到小排序，先把大的用了。还有一个很容易发现的性质，如果把 $1$ 去掉后，让一个长度满足条件就只需要 $\log n$ 次，$n$ 和值域同阶。这样让两个数满足，最坏只要 $40$ 次。考虑 dp，设 $f_{i,j}$ 表示前 $i$ 个数，有一个数是 $j$ 时，另一个数的最大值，转移背包板子，就不讲了。对于旋转，发现没用，只用把两个数交换跑一下就行。
# Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n;
int x[114514];
int tmp[114514];
int cnt;
int f[41][100005];//Ç°i´Î²Ù×÷£¬h³¤ÎªjÊ±£¬wµÄ×î´ó³¤¶È 
int work(int a,int b,int h,int w)
{
	memset(f,0,sizeof f);
	f[0][min(a,h)]=min(b,w);
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<=a;j++)
		{
			f[i][min(a,j*x[i])]=min(max(f[i][min(a,j*x[i])],f[i-1][j]),b);
			f[i][j]=min(max(f[i][j],f[i-1][j]*x[i]),b);
		}
	for(int i=0;i<=cnt;i++)
		if(f[i][a]==b) return i;
	return 1e9;
}
signed main()
{
	int a,b,h,w;
	a=read(),b=read(),h=read(),w=read(),n=read();
	for(int i=1;i<=n;i++) tmp[i]=read();
	sort(tmp+1,tmp+n+1);
	for(int i=n;i>=1;i--) 
		if(tmp[i]>1) x[++cnt]=tmp[i];
	cnt=min(cnt,40ll);
	int ans=min(work(a,b,h,w),work(a,b,w,h));
	if(ans==1e9) write(-1);
	else write(ans);
	return 0;
}
```

---

## 作者：nb_jzy (赞：1)

# 题意
给你一个 $h\times w$ 的矩形，和长度为 $n$ 的序列。每个数只能用一次，可以将 $h\times d_i$ 或 $w\times d_i$，问你用最少的步数使得操作之后 $a\times b$ 的矩形可以被放进最终的 $h'\times w'$ 的矩形中。
# 思路
首先，我们注意到 $n\le 10^5$，但是这显然没用。发现 $a,b,h,w\le 10^5$，$2\le d_i\le 10^5$，这意味着实际上最多只需要操作 $\log_2 a+\log_2 b$ 次就可以达成目标。

而又可以贪心地发现**用最大的几个数**就好了，于是这意味着我们只需要在前 $\min (\log_2 a+\log_2 b,n)$ 大的数中考虑。
# 做法
首先，我们显然有一种暴力的 dp，设 $f_{i,j}$ 表示 $h'=i,w'=j$ 的最小操作次数。

经过刚刚的分析，我们发现 $f$ 的值域很小，$i,j$ 两维也只有 $10^5$ 级别，所以不难发现可以**交换答案和状态**。

所以我们可以重新设 $f_{i,j}$ 表示用了 $i$ 个数，$h'=min(j,a)$，$w'$ 的最大值就行了。转移即考虑这个数乘在 $h'$ 还是 $w'$ 上。

$$
f_{i,j}=\max(f_{i,j},f_{i-1,j}\times d_i)
$$
$$
f_{i,\min(a,j\times d_i)}=\max(f_{i,\min(a,j\times d_i)},f_{i-1,j})
$$

答案即找到最小的 $i$，使得 $f_{i,a}\ge b$。

**注意，矩形可以翻转**，所以我们**还需要考虑将 $a,b$ 交换后的情况**，两个答案取最小的就行了。

时间复杂度 $\mathcal O(\min(n,\log_2 a+\log_2 b)\times \max(a,b))$。
# 代码
```cpp
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int f[50][maxn],d[maxn],n;
int solve(int a,int b,int h,int w){
	memset(f,0,sizeof f);
	f[0][min(a,h)]=min(b,w);
	for(int i=1;i<=min(n,36);i++){
		for(int k=36;k>=1;k--){
			for(int j=1;j<=a;j++){
				f[k][j]=max((long long)f[k][j],min((long long)b,(long long)f[k-1][j]*d[i]));
				f[k][min((long long)d[i]*j,(long long)a)]=max(f[k][min((long long)d[i]*j,(long long)a)],f[k-1][j]);
			}
		}
	}
	for(int i=0;i<=36;i++){
		if(f[i][a]>=b){
			return i;
		}
	}
	return -1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int a,b,h,w;
	cin>>a>>b>>h>>w>>n;
	for(int i=1;i<=n;i++){
		cin>>d[i];
	}
	sort(d+1,d+n+1,greater<int>());
	int ans=solve(a,b,h,w);
	if(ans==-1){
		ans=solve(a,b,w,h);
	}
	else{
		ans=min(ans,solve(a,b,w,h));
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Resurgammm (赞：1)

> 给出一个 $a\times b$ 的目标矩形和一个 $h\times w$ 的现有矩形，现在有 $n$ 个操作，每个操作有一个数 $arr_i$，该可将现有矩形 $h$ 边乘上 $arr_i$，或将 $w$ 边乘上 $arr_i$。问：至少进行几次操作，可以使得目标矩形能放入现有矩形中（可以旋转 $90$ 度）。若无解输出 $-1$。

观察数据范围能发现 $a,b\leq 2^{17}$，所以最坏也只需进行 $34$ 次操作。

那么可以考虑一下指数级算法：BFS。

我们在每个状态里设置三个参数 $x,y,step\ (x<y)$，分别表示长和宽要达到的目标放大倍数及步数。

贪心一下，将操作数组 $arr$ 从大到小排序。

所以每次就最多能产生两种状态，分别在 $x,y$ 中砍掉一定倍数。

当 $x,y$ 都等于 $1$ 时直接输出答案即可，注意因为 $step$ 是要迎合 $arr$ 数组下标的，所以起始为 $1$，那么最后输出的时候就要减一。

判重有很多方法，可以开个 $map$，这里我手写了一个哈系表。

最后分析一下复杂度，虽然最劣时看着可能像是 $2^{34}$ 的，但其实是 $2^{17}$ 的，因为一边如果已经为 $1$ 的时候，它就不会再增加新的状态了。

这也就是为什么设定要往下砍倍数而不是加倍数，因为加倍数的话如果一边已经合法那么无法控制它不变。

还有就是因为可以旋转 $90$ 度再放入，所以开始时加入两个相反的状态。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=1e5+5;
	
	int a,b,h,w,n,border;
	int arr[maxn];
	struct node{
		int x,y,step;
		node(){}
		node(int a,int b,int c){x=a,y=b,step=c;}
	};
	namespace HashTable{//哈希表判重
		const int mod=20051107;
		struct Hash{
			int head[mod+50],id;
			struct e{int x,y,next;}edge[maxn*10];
			inline void add(int x,int y){
				int u=(1ll*x*(n-1)+y)%mod;
				edge[++id]=(e){x,y,head[u]};
				head[u]=id;				
			}	
			inline int query(int x,int y){
				int u=(1ll*x*(n-1)+y)%mod;
				for(int i=head[u];i;i=edge[i].next)
					if(edge[i].x==x && edge[i].y==y) return 1;
				return -1;
			}
		}H;
	}using namespace HashTable;
	inline node maintain(node x){//保持 x<y
		if(x.x>x.y) swap(x.x,x.y);
		return x;
	}
	inline int calc(int x,int div){return x/div+(x%div!=0);}//往下砍倍数
	inline void bfs(){
		queue<node> q;
		node sta1=maintain(node(calc(a,h),calc(b,w),1));
		node sta2=maintain(node(calc(a,w),calc(b,h),1));
		q.push(sta1); q.push(sta2);
		while(!q.empty()){
			node now=q.front(); q.pop();
			int x=now.x,y=now.y,step=now.step;
			if(x==1 && y==1) return printf("%d\n",step-1),void();
			if(step>border) continue;
			node nxt=maintain(node(calc(x,arr[step]),y,step+1));
			if(H.query(nxt.x,nxt.y)==-1){
				H.add(nxt.x,nxt.y);
				q.push(nxt);
			}
			nxt=maintain(node(x,calc(y,arr[step]),step+1));
			if(H.query(nxt.x,nxt.y)==-1){
				H.add(nxt.x,nxt.y);
				q.push(nxt);
			}
		}
		puts("-1");
	}
	
	inline int main(){
		a=read(); b=read(); h=read(); w=read(); n=read();
		for(int i=1;i<=n;i++) arr[i]=read();
		sort(arr+1,arr+1+n,greater<int>());//贪心，从大到小
		border=min(n,34);
		bfs();
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：wgyhm (赞：1)

# 【搜索记录】CF799D Field expansion

## 题目大意

给出 $a,b,h,w$，和长度为 $n$ 数列 $g$。可以进行两个操作：

* $h=h*g_i$
* $w=w*g_i$

每个 $g_i$ 只能使用一次。

求至少进行几次操作，可以使 $a\le h,b\le w$ 或 $a\le w,b\le h$。

$1\le a,b,h,w,n\le 10^5,2\le g_i\le 10^5$

## 解法

首先把 $a\le h,b\le w$ 的最小操作数求出， $a\le w,b\le h$ 同理，最后比较一下就好了。

因为 $a,b\le 2^{17}$ ，所以最多只需要 $34$ 次操作。排序取前 $34$ 大的即可。

直接求不太好。加二分长度进行判断。

考虑搜索，直接搜比较简单，但是复杂度是 $2^{34}$ 的，显然会 $T$。那么采用折半搜索。

对于两个乘积数列，排序后二分。最后判断即可。

复杂度 $O(2^{17}\cdot\log{2^{17}}\cdot \log{34})=O(2^{17}\cdot17\cdot \log{34})$。

## Code:

```cpp
#define rg register
#define int long long 
#define maxn 100005
#define maxm 1<<19
#define put() putchar('\n')
using namespace std;
int tmp1,tmp2,tmp3,tmp4,n,a[maxn],num,len;
int rt1[maxm],tot1,rt2[maxm],tot2; 
inline bool cmp(int x,int y){return x>y;}
inline void dfs1(int id,int sum){
	if (id>num) {rt1[++tot1]=sum;return;}
    dfs1(id+1,sum*a[id]);
    dfs1(id+1,sum);
}
inline void dfs2(int id,int sum){
	if (id>len) {rt2[++tot2]=sum;return;}
    dfs2(id+1,sum*a[id]);
    dfs2(id+1,sum);
}
inline bool check(void){
	rg int i,l,r,mid,sum1,sum2;
	num=(len+1)/2;tot1=tot2=0;
	dfs1(1,1);dfs2(num+1,tmp3);sum1=rt1[1];sum2=rt2[1];
	for (sort(rt1+1,rt1+1+tot1),i=1;i<=tot2;i++){
		if (sum1*rt2[i]<tmp1) continue;
		l=0;r=tot1+1;
		while (l+1<r){
			mid=l+r>>1;
			if (rt1[mid]*rt2[i]<tmp1) l=mid;
			else r=mid;
		}
		if ((sum1/rt1[r])*(sum2/rt2[i])*tmp4>=tmp2) return 0;
	}
	return 1;
}
inline int solve(void){
	rg int i,l,r;l=0;r=n+1;
	while (l+1<r){
		len=l+r>>1;
		if (check()) l=len;
		else r=len;
	}
	return r;
}
signed main(){
	rg int i,x,y,sum;
	read(tmp1);read(tmp2);read(tmp3);read(tmp4);read(n);
	if (tmp1<=tmp3&&(tmp2<=tmp4)||(tmp1<=tmp4&&tmp2<=tmp3)) return puts("0"),0;
	for (i=1;i<=n;i++) read(a[i]);
	sort(a+1,a+1+n,cmp);i=0;
	if (tmp3<tmp1) for (sum=tmp3,i=1;i<=n;i++,sum*=a[i]) if (sum*a[i]>tmp1) break;
	if (tmp4<tmp2) for (sum=tmp4,i++;i<=n;i++,sum*=a[i]) if (sum*a[i]>tmp2) break;
	n=min(n,i);
	x=solve();swap(tmp1,tmp2),y=solve();
	if (min(x,y)==n+1) puts("-1");
	else printf("%lld",min(x,y));
	return 0;
}
```



---

## 作者：2018ty43 (赞：1)

首先发现最多只需要 $2\lceil\log_2a\rceil=34$ 次操作。如果直接每个操作给谁爆搜会 TLE。  
发现如果没有 $2$ 的情况，最多只需要 $2\lceil\log_3a\rceil=22$ 此操作，可以爆搜，于是直接枚举有多少个 $2$ 乘给 $h$ 剩下的全乘给 $w$。然后对其他数爆搜即可。

代码
```cpp

void dfs(int u,long long k1,long long k2)
{
	if((k1>=a1&&k2>=a2)||(k1>=a2&&k2>=a1)||u>ans)
	{
	//	printf("%d %d %d %d\n",u,k1,k2,ans);
		ans=(ans<u-1)?ans:(u-1);
		return;
	}
	if(u>n)return;
	if(a[u]==2)
	{
		if(be[u])
		{
			if(k1<((a1>a2)?a1:a2))dfs(u+1,k1*2,k2);
		}
		else if(k2<((a1>a2)?a1:a2))dfs(u+1,k1,k2*2);
	}
	else
	{
		if(k1<((a1>a2)?a1:a2))dfs(u+1,k1*a[u],k2);
		if(k2<((a1>a2)?a1:a2))dfs(u+1,k1,k2*a[u]);
	}
}
int main()
{
	scanf("%d%d%d%d%d",&a1,&a2,&b1,&b2,&n);
	for(int i(1);i<=n;++i)
	{
		scanf("%d",a+i);
		if(a[i]==2)que[++tot]=i;
	}
	std::sort(a+1,a+n+1,std::greater<int>());
	for(int i(0);i<=tot&&que[i]<ans;be[que[++i]]=1)dfs(1,b1,b2);
	printf("%d\n",(ans<=n)?ans:-1);
}
```

---

## 作者：zhangjiting (赞：0)

考试挂掉了，写个题解记录一下。

## 思路

首先，所有 $a_i>1$。

发现 $a,b,w,h \le 10^5$，而 $2^{17} > 10^5$，所以，最多只会使用前 $34$ 大的 $a_i$，直接枚举有 $2^{34}$ 种情况，会超时，但是 $3^{11} > 10^5$，$2^{22}$ 不会超时。


对于所有大于 $2$ 的 $a_i$，枚举子集，分成两部分，对于 $a,b$ 分别操作完，再枚举它们分别乘几个 $2$。

注意：当 $a$ 大于 $10^5$ 后，不能再乘了，不然会溢出，$b$ 同理。

当 $34$ 也不合法时，输出 `-1` 即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug(x) cout<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e5+5;
int A,B,H,W;
int len,n,l2;
int tmp[N],a[N];
bool cmp(int x,int y){
	return x>y;
}
bool ok(int x,int y,int nx,int ny){
	if(x>y) swap(x,y);
	if(nx>ny) swap(nx,ny);
	if(x>=nx&&y>=ny) return 1;
	else return 0;
}
bool check(int x,int y,int top){
	for(int bit=0;bit<(1<<(min(top,n)));bit++){
		int xx=x,yy=y;
		int fx=1,fy=1;
		for(int i=1;i<=min(top,n);i++){
//			if(!fx&&!fy) break;
//			debug(a[i]);
			if(bit&(1<<(i-1))&&fx){
				x*=a[i];
				if(x>1e5) fx=0;
			}
			else if(fy){
				y*=a[i];
				if(y>1e5) fy=0;
			}
		}
		int nx=x,ny=y;
		for(int i=0;i<=max(0ll,top-n);i++){
			for(int j=1;j<=i;j++){
				if(x<=1e5) x*=2;
			}
			for(int j=1;j<=top-n-i;j++){
				if(y<=1e5) y*=2;
			}
			if(ok(x,y,H,W)) return 1;
			x=nx,y=ny;
		}
		if(ok(x,y,H,W)) return 1;
		x=xx,y=yy;
	}
	return 0;
}
signed main(){
	IOS;
	cin>>W>>H>>A>>B>>len;
	for(int i=1;i<=len;i++) cin>>tmp[i];
	for(int i=1;i<=len;i++){
		if(tmp[i]>2) a[++n]=tmp[i];
		if(tmp[i]==2) l2++;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=0;i<=min(34ll ,l2+n);i++){
		if(check(A,B,i)) return cout<<i,0;
	}
	cout<<-1;
	return 0;
}

```

---

## 作者：Addicted_Game (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF799D)

## 题目大意
给定 $n$ 个数，选择其中的数乘上矩形边长直到可以包含现有矩形。

## 思路
$ n \le 100000$！这也太大了。但是 $1 \le a,b,h,w,n \le 100000$。当扩大的倍数 $a_i$ 为 $1$ 时可以直接忽略它。那么最多也只需要 $2 \times \log_{2}{a}=34$ 次操作，完全可以直接搜索。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,h,w,n;
long long kl,kr;
long long num[100005];
struct node{
	long long x,y,step;
};
map<pair<long,long>,bool> vis;
bool cmp(long long x,long long y){
	return x>y;
}
long long ans=35;
queue<node> q;
void bfs(int kl,int kr){//bfs可以节省大量时间
	q.push({h,w,0});
	q.push({w,h,0});
	while(!q.empty()){
		node t=q.front();
		q.pop();
		if(t.x>=kl&&t.y>=kr||t.x>=kr&&t.y>=kl){
			ans=t.step;
			return ;
		}
		if(t.step>=n+1||num[t.step+1]==1) return ;
		if(t.y<kr&&(!vis[{t.x,t.y*num[t.step+1]}])){
			q.push({t.x,t.y*num[t.step+1],t.step+1});
			vis[{t.x,t.y*num[t.step+1]}]=true;
		}
		if(t.x<kl&&(!vis[{t.x*num[t.step+1],t.y}])){
			q.push({t.x*num[t.step+1],t.y,t.step+1});
			vis[{t.x*num[t.step+1],t.y}]=true;
		}
	}
}
int main(){
	scanf("%lld%lld%lld%lld%lld",&a,&b,&h,&w,&n);
	for(int i=1;i<=n;i++) scanf("%lld",&num[i]);
	if(h>=a&&w>=b){
		printf("0");
		return 0;
	}
	sort(num+1,num+n+1,cmp);
	bfs(a,b);
	if(ans>=35) printf("-1"); 
	else printf("%lld",ans);
	return 0;
}
```

---

## 作者：OE_AiHAn (赞：0)

## [CF799D](https://codeforces.com/problemset/problem/799/D)

### 题意
给定一个长宽为 $a$ 和 $b$ 的目标矩形、一个宽高为 $h$ 和 $w$ 的初始矩形及 $n$ 个操作 $a_i$。对于每个操作，可以将初始矩形的宽或高乘以 $a_i$，求使目标矩形能放入初始矩形的最少操作（目标矩形可以旋转 90 度）。

### 解析
这题算是一道有趣的背包题。

由于 $a, b \le 10^5$，不可能直接进行二维 dp。考虑到 $a_i \ge 2$，又有 $\left \lceil \log{10^5} \right \rceil = 17$，可以得出结论————至多只需要进行 34 个操作。

我们可以将操作数从大到小进行排序，设 $i$ 为当前进行第几个操作，$j$ 为初始矩形宽度，$dp_{i, j}$ 为进行到第 $i$ 个操作时初始矩形宽为 $j$ 时高最大为多少。则可以得到转移方程：

$$dp_{i,j \times a_i} = \max(dp_{i - 1, j \times a_i} \times a_i, dp_{i - 1, j})$$

初始化 $dp_{0, w} = h$。当 $j \times a_i > \max(a, b)$ 时，可以将 $j \times a_i$ 并入 $\max(a, b)$，此做法不会对决策造成影响。

在每次计算转移之后对 $dp_{i, j \times a_i}$ 进行判定是否符合题目要求，若符合，输出当前的 $i$ 即为答案。要注意目标矩形可以做 90 度旋转（测试点 27 会卡）。

另外，观察每次转移时都只和 $i - 1$ 有关，且 $j < a_i$，可以用类似 01 背包的方式对数组进行滚动优化。

### 代码
```c++
#include <bits/stdc++.h>
#define LL long long
#define pii pair<int, int>
#define pll pair<LL, LL>

using namespace std;

vector<LL> dp(100005, 0);
LL a[100005];

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    LL h0, w0, h, w, n;
    cin >> h0 >> w0 >> h >> w >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    //判定是否已符合条件
    if (h >= h0 && w >= w0 || h >= w0 && w >= h0)
    {
        cout << "0\n";
        return 0;
    }

    sort(a + 1, a + n + 1, greater<LL>());
    if (h >= h0 || h >= w0 || w >= h0 || w >= w0) //判断有一条边已符合条件的情况
    {
        a[0] = 1;
        for (int i = 1; i <= n; i++)
            a[i] *= a[i - 1];

        int ans = n + 5;
        if (h >= h0)
        {
            for (int i = 1; i <= n; i++)
                if (w * a[i] >= w0)
                {
                    ans = min(ans, i);
                    break;
                }
        }
        if (h >= w0)
        {
            for (int i = 1; i <= n; i++)
                if (w * a[i] >= h0)
                {
                    ans = min(ans, i);
                    break;
                }
        }
        if (w >= h0)
        {
            for (int i = 1; i <= n; i++)
                if (h * a[i] >= w0)
                {
                    ans = min(ans, i);
                    break;
                }
        }
        if (w >= w0)
        {
            for (int i = 1; i <= n; i++)
                if (h * a[i] >= h0)
                {
                    ans = min(ans, i);
                    break;
                }
        }

        cout << (ans > n ? -1 : ans) << "\n";
        return 0;
    }

    dp[w] = h; //dp数组初始化
    for (int i = 1; i <= n; i++)
        for (int j = max(w0, h0); j >= w; j--)
        {
            dp[min(j * a[i], max(w0, h0))] = max(dp[j], dp[min(j * a[i], max(w0, h0))]);
            dp[j] *= a[i];
            if (j * a[i] >= w0 && dp[min(j * a[i], max(w0, h0))] >= h0 || j >= w0 && dp[j] >= h0) //判断正放目标矩形的情况
            {
                cout << i << "\n";
                return 0;
            }
            if (j * a[i] >= h0 && dp[min(j * a[i], max(w0, h0))] >= w0 || j >= h0 && dp[j] >= w0) //判断旋转目标矩形的情况
            {
                cout << i << "\n";
                return 0;
            }
        }

    cout << "-1\n";
}
```

最后祝各位顺利AC。>w<

---

## 作者：Find_Yourself (赞：0)

有趣的 BFS 题。

首先发现，一个数最多乘 $2^{17}$ 次后超过上限，所以我们可以考虑 BFS。

将 $a$ 数组元素从大到小排序，定义 $(x,y,t)$ 表示当前长为 $x$，宽为 $y$，操作了 $t$ 次。每次操作将两个数中没超过上限的乘上 $a_i$。

由于可以旋转 $90\degree$，把长宽交换一下再跑一遍。

复杂度 $O(2^{17})$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
ll a,b,h,w,n,x[N],ans=1e9;
bool cmp(int p,int q){return p>q;}
struct node{
  ll x,y,t;
  node(ll x=0,ll y=0,ll t=0):x(x),y(y),t(t){}
};
map<pair<ll,ll>,int>mp;
queue<node>q;
void get(node nw){
  if(!mp.count(make_pair(nw.x,nw.y))){
    mp[make_pair(nw.x,nw.y)]=1;
    q.push(nw);
  }
}
void solve(ll aa,ll bb){
  mp.clear();
  while(!q.empty())q.pop();
  ll fir=min(h,aa),sec=min(w,bb);
  q.push(node(fir,sec,0));
  mp[make_pair(fir,sec)]=1;
  while(!q.empty()){
    node u=q.front(),nw;q.pop();
    if(u.x==aa&&u.y==bb){
      ans=min(ans,u.t);
      break;
    }if(u.t==n)continue;
    if(u.x<aa){
      nw=node(min(aa,u.x*x[u.t+1]),u.y,u.t+1);
      get(nw);
    }if(u.y<bb){
      nw=node(u.x,min(bb,u.y*x[u.t+1]),u.t+1);
      get(nw);
    }
  }
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>a>>b>>h>>w>>n;
  for(int i=1;i<=n;++i)cin>>x[i];
  sort(x+1,x+n+1,cmp);
  solve(a,b);solve(b,a);
  if(ans==1e9)cout<<-1<<endl;
  else cout<<ans<<endl;
  return 0;
}

```


---

