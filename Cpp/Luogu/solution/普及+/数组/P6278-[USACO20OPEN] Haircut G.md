# [USACO20OPEN] Haircut G

## 题目描述

Farmer John 由于对整理他难以整平的头发感到疲惫，于是决定去理发。他有一排 $N$ 缕头发，第 $i$ 缕头发初始时长度为 $A_i$ 微米（$0\le A_i\le N$）。理想情况下，他想要他的头发在长度上单调递增，所以他定义他的头发的“不良度”为逆序对的数量：满足 $i < j$ 及 $A_i > A_j$ 的二元对 $(i,j)$。  
对于每一个 $j=0,1,\ldots,N-1$，Farmer John 想要知道他所有长度大于 $j$ 的头发的长度均减少到 $j$ 时他的头发的不良度。

-----

（有趣的事实：人类平均确实有大约 $10^5$ 根头发！）

## 说明/提示

#### 样例解释：

输出的第四行描述了 Farmer John 的头发长度减少到 $3$ 时的逆序对数量。   
$A=[3,2,3,3,0]$ 有五个逆序对：$A_1>A_2,\,A_1>A_5,\,A_2>A_5,\,A_3>A_5,$ 和 $A_4>A_5$。

----

对于 $100\%$ 的数据，$1\le N\le 10^5$。

共 $13$ 个测试点，其中 $1$ 为样例，其余性质如下：
  
测试点 $2$ 满足 $N\le 100$。  
测试点 $3\sim 5$ 满足 $N\le 5000$。  
测试点 $6\sim 13$ 没有额外限制。  

-----


出题人：Dhruv Rohatgi


## 样例 #1

### 输入

```
5
5 2 3 3 0```

### 输出

```
0
4
4
5
7```

# 题解

## 作者：ghostdoglzd (赞：25)

### [原题](https://www.luogu.com.cn/problem/P6278)
#### 题意概括：
- 有长为$n$的序列 $a[1...n]$,$\forall a[i](0<i\le n),a[i]\le n$。
- 请你按 $j(j=0,1,2,...,n-1)$ 依次输出把大于 $j$ 的 $a[i]$ 变为 $j$ 后逆序对的个数。

#### 思路：

这是一道很好的思考题，我们可以把 $a[1..n]$ 按从小到大的顺序排序，对于每个 $a[i]$，在原序列中它前面比它大的数的个数即为其对 $j=a[i]+1,a[i]+2,...,n$ 时的答案的贡献。然后从 $0$ 到 $(n-1)$ 枚举 $j$。每次枚举先输出答案，再把答案加上等于 $j$ 的 $a[i]$ 的贡献即可。

这个贡献可以利用树状数组维护区间和把复杂度降为 $O(\log n)$ 。具体实现方式为先往树状数组的每一位上放$1$。然后每遍历到一个 $a[i]$,将它在原序列中的位置对应的树状数组值改为 $0$，其贡献即为它在原序列中的位置前还有多少 $1$，即 $query(num[i]-1)$,（$num[i]$ 为 $a[i]$ 在原序列中的位置）。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
inline int rread(){
	int x=0;
	char c=getchar(),o=' ';
	while(c<'0'||c>'9')o=c,c=getchar();
	while(c>='0'&&c<='9')x*=10,x+=(c^48),c=getchar();
	if(o=='-')x=-x;
	return x;
}
inline int lowbit(int x){
	return x&(-x);
}
struct node{
	int a,num;
}nd[100010];
bool operator <(const node& x,const node& y){
	return (x.a==y.a)?x.num<y.num:x.a<y.a;
}
int n,tree[100010];
inline void change(int x,int c){
	while(x<=n){
		tree[x]+=c;
		x+=lowbit(x);
	}
}
inline int query(int x){
	int ans=0;
	while(x>0){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
signed main(){
	n=rread();
	for(int i=1;i<=n;i++){
		nd[i].a=rread();
		nd[i].num=i;
		change(nd[i].num,1);
	}
	sort(nd+1,nd+1+n);
	int ans=0;
	int in=1;
	for(int i=0;i<n;i++){
		cout<<ans<<'\n';
		int t=in;
		while(i==nd[t].a){
			ans+=query(nd[t].num-1);
			change(nd[t].num,-1);
			t++;
		}
		in=t;
	}
	return 0;
}
```

------
### 更新日志
2020.10.16 修改了链接

---

## 作者：UltiMadow (赞：20)

思维题，挺不错的一个树状数组题，代码不长，~~甚至不需要排序~~

考场上一看到这题其实窝是懵的，接下来，输出的方式给了我一点提示

看到```对于每一个 j=0,1,…,N−1，用一行输出 Farmer John 头发的不良度```我们想到了倒推

如何倒推呢？我们考虑FJ去种头发而不是剃头发（大雾）

为了便于理解，我们~~强行~~加一个时间，我们假设每一秒fj的头发都会长1微米，然后第 $i $ 个头发在长度到达 $A_i$ 的时候就不会继续长了

于是，我们考虑每一秒新增的逆序对数

发现第 $i $ 秒新增的逆序对数就是每个长度为 $i-1$ 的头发的前面**在第 $i-1$ 秒时还在长的头发**数量

发现，这句话我们换一种方式说就是第 $i$ 个头发对答案的贡献从第 $A_i$ 秒开始，并且贡献的大小为满足 $A_j>A_i(j<i)$ 的 $j$ 的个数

发现这东西就是个逆序对，树状数组维护一下就好啦~

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 100100
#define int long long//别忘记longlong哦
using namespace std;
int n,a[MAXN];
class tarray
{
private:
	int tree[MAXN];
	int lowbit(int x){return x&(-x);}
public:
	void update(int x,int y){while(x<=n){tree[x]+=y;x+=lowbit(x);}}
	int query(int x){int ret=0;while(x){ret+=tree[x];x-=lowbit(x);}return ret;}
}t;//树状数组
int s[MAXN],ans;
signed main()
{
	freopen("haircut.in","r",stdin);
	freopen("haircut.out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),a[i]++;
	for(int i=1;i<=n;i++)//统计逆序对
	{
		int x=n-a[i]+2;
		s[a[i]]+=t.query(x-1);
		t.update(x,1);
	}
	printf("0");//第0秒的答案
	for(int i=2;i<=n;i++)//统计答案
	{
		ans+=s[i-1];
		printf("\n%lld",ans);
	}
	return 0;
}
```
后记：这个赛季usaco就卡在G组了，没能晋级P组，下赛季加油咯

---

## 作者：Lonely_NewYear (赞：14)

# 洛谷 P6278 题解

## 前置知识

[树状数组求逆序对个数](https://www.luogu.com.cn/problem/P1908)

## 题目分析

可以考虑在剪头发时，哪些逆序对会留下来，哪些逆序对会消失，易得：

（假设有一个逆序对 $(i,j)$,$k$ 表示目前减到的长度）

- 当 $A_j<k$ 时，此时 $A_i$ 仍然大于 $A_j$，逆序对 $(i,j)$ 可以留下来。

- 当 $A_j\ge k$ 时，此时 $A_i=A_j$，逆序对 $(i,j)$ 会消失。

那么每当 $k$ 下降 $1$，所有 $A_j=k$ 的逆序对 $(i,j)$ 都会消失。我们可以开一个 $cnt$ 数组，$cnt_k$ 记录上述值。容易想到在树状数组求逆序对时进行维护（注意此时已经求出来了以当前位置结尾的逆序对个数），设当前位置为 $j$，逆序对个数为 $x$，则 $cnt_{Aj}+=x$。

最后依次输出 $cnt$ 的前缀和即可。

## 代码

```cpp
#include<cstdio>
using namespace std;
long long s[100001],t[100001];
int n,a[100001];
int lowbit(int i)
{
	return i&-i;
}
long long query(int i)
{
	long long sum=0;
	while(i>0)
	{
		sum+=s[i];
		i-=lowbit(i);
	}
	return sum;
}
void change(int i,long long x)
{
	while(i<=n+1)
	{
		s[i]+=x;
		i+=lowbit(i);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		a[i]++;
		t[a[i]]+=i-1-query(a[i]);
		change(a[i],1);
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		printf("%lld\n",ans);
		ans+=t[i];
	}
	return 0;
}
```

谢谢观看！

---

## 作者：pocafup (赞：6)

楼上dalao解法非常清晰。蒟蒻的解法大致相同，但对于细节有些不同的处理。

为什么能够用线段树/树状数组？

我们知道，一个数产生的逆序对取决于他前面比他大的数的个数。

于是，题目转化为，每输入一个数，就将这个数对于逆序对的贡献值增加他前面比他大的数的个数，然后将这个数存下来。

答案的统计方法：

当头发长度为 $A_i$ 时逆序对的数量 $=$ 到 $A_i$ 之前的逆序对数量 $+$ 这个数所能贡献的逆序对的数量。

这个操作用树状数组会非常好实现，但是我树状数组不是特别熟，于是在比赛上选择了打线段树。

~~本来应该int能过，但懒得调，于是直接换成了long long~~

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
const long long MAXN = 1e5+5;
long long n,pos[MAXN],num[MAXN],seg[8*MAXN],pre;
#define lson (way<<1)
#define rson ((way<<1)+1)
#define mid (l+r)/2
void setIO(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
	ios_base::sync_with_stdio(0);
}

inline long long query(long long way, long long l, long long r ,long long qlow, long long qhigh){

  if (qlow<=l && r<=qhigh) return seg[way];
  if (l>qhigh || r<qlow) return 0;
  return (query(lson,l,mid,qlow,qhigh)+query(rson,mid+1,r,qlow,qhigh));
}//询问 Ai+1 到 n ，也就是比 Ai 大的数的数量
inline void update(long long way, long long l, long long r, long long qlow){
  if (l==r && l==qlow) {seg[way]++;return;}
  if (mid>=qlow) update(lson,l,mid,qlow);
  else update(rson,mid+1,r,qlow);
  seg[way]++;
}//更新Ai的数量
int main(){
  setIO("haircut");
  cin >> n;
  for (long long i=0;i<n;i++) {
    cin >> pos[i];
    if (pos[i]+1<=n) num[pos[i]]+=query(1,0,n,pos[i]+1,n);//询问
    update(1,0,n,pos[i]);//更新
  }
  cout << 0 << endl;
  for (long long i=1;i<n;i++){
    pre+=num[i-1];//先将这个数的贡献加上
    cout << pre << endl;//然后输出
  }
}
```

---

## 作者：yf最qhhh (赞：3)

这道题明显的树状数组啊 ~~（虽然我已经做了几十分钟再看了题解才知道）~~

**题意：**

有一个序列，长度为 n，且 1 ≤ A[i] ≤ n，
现在要求把大于 j(j ≤ 0 < n) 的 A[i] 变为 j 后有几个逆序对，每行输出一个。

**思路：**

头发长到 A[i] 时产生逆序对的数量 = 长到 A[i] 之前的逆序对数量 + 这个数本来就会产生的逆序对数量

得到这个规律之后就可以用树状数组来维护它了，看代码吧
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll n,ans,arr[1000005],C[1000005],Sum[1000005];
ll lowbit(ll x){//树状数组的基本操作，求第一个 1 出现的位置
	return x&(-x);
}
void qwe(ll x,ll k){//如果改变一个树那管辖它的其他位置都要改变
	for(ll i=x;i<=n+1;i+=lowbit(i))C[i]+=k;
}
ll GetSum(ll x) {//求和
	ll ans=0;
	for(ll i=x;i>0;i-=lowbit(i))ans+=C[i];
	return ans;
}
main(void){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) {
		scanf("%lld",&arr[i]);
		arr[i]+=1;//加1再存
	}
	for(ll i=1;i<=n;i++) {
		Sum[arr[i]]+=GetSum(n-arr[i]+1);//开一个 Sum 数组来记录和
		qwe(n-arr[i]+2,1);//加2是因为防止为0
	}
	for(ll j=0;j<n;j++) {//j按 0~n-1 输出就行了
		ans+=Sum[j];
		printf("%lld\n",ans);
	}
	return >.<;
}
```


---

## 作者：KSToki (赞：1)

为什么要想这么复杂，直接模拟不好吗。

把每一个数字的位置存下来，循环到 $i$ 时新增的贡献数一定是在每一个 $i$ 前比 $i$ 大的，由于小于 $i$ 的贡献已经在当时被删除了，所以这是正确的，用树状数组求逆序对即可。由于每个数字只会被加入、删除树状数组一次，查询也只会进行 $n$ 次，时间复杂度仍然是 $O(nlogn)$。

代码可能更好理解，~~去掉宏定义还是很短的~~。
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n,a[100001],c[100001];
ll ans;
vector<int>pos[100001];
I void update(int x,int v)
{
	for(;x<=n;x+=lowbit(x))
		c[x]+=v;
}
I int sum(int x)
{
	int res=0;
	for(;x;x-=lowbit(x))
		res+=c[x];
	return res;
}
int main()
{
	n=read();
	for(R int i=1;i<=n;++i)
	{
		a[i]=read();
		pos[a[i]].push_back(i);
		update(i,1);
	}
	puts("0");
	for(R int i=0;i<n-1;++i)
	{
		for(R int j=0,up=pos[i].size();j<up;++j)
		{
			update(pos[i][j],-1);
			ans+=sum(pos[i][j]);
		}
		putll(ans);
	}
	return 0;
}
```


---

## 作者：liuyanxi2 (赞：1)

我看到这道题的时候很蒙的，这输出方式非常像树状数组，所以我觉得应该从这里开刀

但是直接用树状数组处理是非常困难的，所以我的方法是将其题意改变一下，让剪头发变成植发，所有头发最初为0，然后不断生长，每根头发生长到一定值就不再生长了

这样就可以用树状数组做了，相信大家都会吧

代码如下

```
#include<bits/stdc++.h>
using namespace std;
long long a[500001],c[500001],n,m,i,j,k,z,x,s[500001],ans;
long long lowbit (long long w)
{
	return w&(-w);
}
void update(long long q,long long w)
{
	while(q<=n)
	{
		c[q]+=w;
		q+=lowbit(q);
	}
}
long long setsum(long long q)
{
	long long sum=0;
	while(q>0)
	{
		sum+=c[q];
		q-=lowbit(q);
	}
	return sum;
}
int main ( )
{
	cin>>n;
	for(i=1;i<=n;i++)
	scanf("%lld",&a[i]),a[i]++;
	for(i=1;i<=n;i++)
	{
		x=n-a[i]+2;
		s[a[i]]+=setsum(x-1);
		update(x,1);
	}
	printf("0");
	for(i=2;i<=n;i++)
	{
		ans+=s[i-1];
		printf("\n%lld",ans);
	}
	return 0 ;
}
```


---

## 作者：hhhyyyfff (赞：1)

- 题意简述：
  有一个数列 $a_1, a_2, \dots, a_N\ (0 \le a_i \le N)$，定义逆序对为 $a_i>a_j\ (1 \le i < j \le N)$。将满足 $a_i>K$ 的 $a_i$ 改为 $K$，求 $K=1,2,\dots,N$ 时，逆序对的数量。

- 前置知识：树状数组 或 线段树 等等

- 算法分析 $O(N \log N)$：  
  记 $f_i$ 为满足 $j<i$ 且 $a_j>a_i$ 条件 $j$ 的数量，则 $K = K_0$ 时的答案为 $\sum_{a_i<K_0} f_i$，因为对于 $a_i<K_0$，原本的逆序对依然存在，否则不存在。  
  $f_i$ 可以用树状数组、线段树等的基础操作求出。  
  从小到大枚举 $K$，依次加上 $f_K$ 即可。

- 代码：

``` cpp
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

pair<int, int> A[100010];
int N, b[100010];
long long ans;

int lowbit(int x) { return x & -x; }
void update(int x) { while (x <= N) { --b[x]; x += lowbit(x); } }
int query(int x) {
    int s = 0;
    while (x) { s += b[x]; x -= lowbit(x); }
    return s;
}

int main() {
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &A[i].first);
        A[i].second = i;
        b[i] = lowbit(i);
    }
    sort(A + 1, A + N + 1);
    for (int i = 0, j = 1; i < N; ++i) {
        printf("%lld\n", ans);
        while (j <= N && A[j].first == i) {
            update(A[j].second);
            ans += query(A[j].second);
            ++j;
        }
    }
    return 0;
}
```

---

## 作者：AChun (赞：1)

# P6278题解

[题目传送门](https://www.luogu.com.cn/problem/P6278)

### SOL:

考虑**树状数组**。

**正难则反**。

将原题转化为每个**值**（注意是**值**）对答案的贡献。

可以看出，这个贡献就是 $a[i]$ 所产生的逆序对个数。

我们建立数组统计。

输出时计算前缀和即可。

### CODE:

```
#include<iostream>
#include<cstdio>
#define N 101010
using namespace std;
long long t[N],d[N],a[N],n,m;
int lowbit(int x){
	return x&-x;
}
void add(int x,long long v){
	while(x<=n){
		t[x]+=v;
		x+=lowbit(x); 
	} 
}
long long query(int x){
	long long ans=0;
	while(x){
		ans+=t[x];
		x-=lowbit(x);
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i]++;
	}
	for(int i=1;i<=n;i++){
		d[a[i]]+=1ll*(i-1-query(a[i]));  
		add(a[i],1);
	}
	long long sum=0;
	cout<<sum<<endl;
	for(int i=2;i<=n;i++){
		sum+=d[i-1];
		printf("%lld\n",sum);
	}
	return 0;
}


```


---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候，都已经了解了题目意思

题目让我们求逆序对的数量

我们可以看到

$j=0,1,..(n-1)$,来输出$farmer  john$头发的不良程度

看到这里，相信大家想到了递推

我们可以考虑树状数组

$ps$：如果有没学过的，可以先学一下

我们可以设每一个单位时间，头发增长增加一个单位，当增加到$A_i$时，停止增长

换一种方式，我们可以求逆序对

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int ans;
int sum[100010];
int a[100010];
int tot[100010];
int n;
inline int lowbit(int x){
	return x&(-x);
}
inline int query(int x){
	int answer=0;
	while(x)
		{
			answer+=sum[x];
			x-=lowbit(x);
		}
	return answer;
}
inline void update(int x,int y){
	while(x<=n)
		{
			sum[x]+=y;
			x+=lowbit(x); 
		}
}
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		{
			a[i]=read();
			++a[i];
		}
	for(register int i=1;i<=n;++i)
		{
			int x;
			x=n-a[i]+2;
			tot[a[i]]+=query(x-1);
			update(x,1);
		}
	write(0);
	for(register int i=2;i<=n;++i)
		{
			ans+=tot[i-1];
			puts("");
			write(ans);
		}
	return 0;
}

```


---

## 作者：Midoria7 (赞：1)

对于一个逆序对，当目前削去的值要小于等于这个逆序对中的较小值的时候，这个逆序对就不存在了。

于是和普通树状数组逆向枚举求逆序对不同，我们可以正向枚举，求出以当前值为较小值的逆序对个数。

这样我们可以首先求出 $ans[n]$，然后逆向枚举 $j$，减去相应的 $cnt[j]$ 即可。

需要注意的是当值为 $0$ 的时候树状数组会死循环，所以我们预先都加一个 $1$ 即可。

```cpp

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n;
int a[maxn], b[maxn];
long long ans[maxn], cnt[maxn];

inline int read() {
    int x = 0; bool fopt = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') fopt = 0;
    for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + ch - 48;
    return fopt ? x : -x;
}

#define lowbit(x) (x & -x)
long long tree[maxn];
inline void add(register int x) {
    for(; x <= n + 1; x += lowbit(x))
        tree[x]++;
}

inline long long query(register int x) {
    long long res = 0;
    for(; x; x ^= lowbit(x))
        res += tree[x];
    return res;
}

int main() {
    n = read();
    for (register int i = 1; i <= n; i++) {
        a[i] = read();
        b[i] = a[i] + 1;
    }
    for (register int i = 1; i <= n; i++) {
        cnt[a[i]] += query(n + 1) - query(b[i]);
        ans[n] += query(n + 1) - query(b[i]);
        add(b[i]);
    }
    for (register int j = n - 1; j >= 0; j--)
        ans[j] = ans[j+1] - cnt[j];
    for (register int j = 0; j <= n - 1; j++)
        printf("%lld\n", ans[j]);
    return 0;
}
```

---

## 作者：麻省理工学院 (赞：1)

口胡一下各种时间复杂度（也许吧）的方法

$So1ution1$：直接上暴力

$\text{时间复杂度}O(n^{2}logn)$

$Solution2$： 考虑到相邻 $k$ 之间变化量等于所有 $k+1$ 变到 $k$ 导致逆序对的减量之和，因此算这个然后逆着推。

$Solution3$（正解）：优化一下的方法应该很容易想到吧，可以转化为一个类似求逆序对的一个东东，然后就显然了。

注意开long long

$Code$
```cpp
#include<cstdio>
#define ll long long

const int N = 1e5 + 5;
ll n, a[N], s[N], ans, t[N];

ll lowbit(ll x){return x & (-x);}
void update(ll x){while(x <= n) t[x]++, x += lowbit(x);}
ll query(ll x){ll ret = 0; while(x) ret += t[x], x -= lowbit(x); return ret;}

int main()
{
    freopen("haircut.in","r",stdin);
    freopen("haircut.out","w",stdout);
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), a[i]++;
    for(int i = 1; i <= n; i++)
        s[a[i]] += query(n - a[i] + 1), update(n - a[i] + 2);
    for(int i = 0; i < n; i++) ans += s[i], printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：LlLlCc (赞：0)

看到神仙PanH写了主席树题解，也来看看这题

把所有大于$j$的数降为$j$再求全局逆序对就等于先求出全局逆序对再减去两个大于等于$j$的数之间的逆序对即可

所有只要求逆序对时记一下逆序对的差分数组就行，代码很短

## code
```
#include<bits/stdc++.h>
#define maxn 2000005
#define ll long long
using namespace std;
const int N=2e5;
int n,a[maxn],c[maxn];
ll Ans,g[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void add(int x){for (;x<=N;x+=x&-x) c[x]++;}
inline int Get(int x){int sum=0;for (;x;x-=x&-x) sum+=c[x];return sum;}
int main(){
	n=read();
	for (int i=1;i<=n;i++) a[i]=read()+1;
    for (int i=1,x;i<=n;i++) x=i-1-Get(a[i]),g[a[i]]+=x,add(a[i]);
    for (int i=0;i<n;i++) Ans+=g[i],printf("%lld\n",Ans);
    return 0;
}
```


---

## 作者：PanH (赞：0)

题解区里的都是简单清晰的树状数组和线段树，那么来一个~~恶心的~~**主席树**吧。

众所周知，逆序对可以用主席树求，复杂度也是 $O(n \log n)$（常数比线段树和树状数组大到不知道哪里去了。。。）。

可能是我题做少了，第一眼并没有看出树状数组做法，但主席树确实是可行的。

明显地，只有当当前的 $j$ 已经大于 $a[i]$ ，才可以统计 $a[i]$ 的贡献，这里的贡献是指 $a[i]$ 与 $a[k(k < i)]$ 组成的逆序对的个数。

于是，~~想到这里我就没想下去了，~~ 直接上主席树暴力维护 $i$ 之前比它大的数的个数，从小到大统计 $a[i]$ 的贡献。

code：

```
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
const int N=1e5+5,MAXN=3e7+5;
int a[N],id[N],tree[MAXN],ls[MAXN],rs[MAXN],rt[N],n,tot;
long long ans;
bool cmp(int x,int y)
{
	return a[x]<a[y];
}
#define mid (l+r>>1)
void build(int l,int r,int &k)
{
	if(!k)	k=++tot;
	if(l==r)	return;
	build(l,mid,ls[k]),build(mid+1,r,rs[k]);
}
void add(int l,int r,int pre,int &k,int x)
{
	if(!k)	k=++tot;
	tree[k]=tree[pre];
	if(l==r)	return tree[k]++,void();
	if(mid>=x)	rs[k]=rs[pre],add(l,mid,ls[pre],ls[k],x);
	else		ls[k]=ls[pre],add(mid+1,r,rs[pre],rs[k],x);
	tree[k]=tree[ls[k]]+tree[rs[k]];
}
int query(int l,int r,int k,int x)
{
	if(l>=x)	return tree[k];
	int res=query(mid+1,r,rs[k],x);
	if(mid>=x)	res+=query(l,mid,ls[k],x);
	return res;
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)	read(a[i]),id[i]=i;
	sort(id+1,id+n+1,cmp);
	build(1,n+1,rt[0]);
	for(int i=1;i<=n;i++)	add(1,n+1,rt[i-1],rt[i],a[i]+1);
	for(int i=0,j=1;i<n;i++)
	{
		while(j<=n&&a[id[j]]<i)	ans+=query(1,n+1,rt[id[j]],a[id[j]]+2),j++;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：zzw4257 (赞：0)

我的方法奇怪了一点

考虑一个序列逆序对等于每个点前面比他大的点个数之和(树状数组做法依据)

记这个数为$l_i$，显而易见的，$l_i$要么为$0$要么为最初的值

考虑$l_i$什么时候改成$0$，也就是第一次比$l_i$大的值都被改成$l_i$的时刻，反过来说，只需要在全区间对$i$取最小值时对**第一次**(参照上句话)被改动的$l_i$变化即可

实现上让$i=n-1$时才暴力出来(包括初始值改掉)，只用把每个位置对初始值取$\min$时减掉$l_i$即可

```cpp
#include<bits/stdc++.h>
#define N 100001
using namespace std;
#define G if(++ip==ie)if(fread(ip=ibuf,1,L,stdin))
const int L=1<<19;
char ibuf[L],*ie=ibuf+L,*ip=ie-1;
inline char nc(void){G;return *ip;}
#define getchar nc
inline int read(void){
	char opt;int flag=1,res=0;
	while((opt=getchar())<'0'||opt>'9')if(opt=='-')flag=-1;
	while(opt>='0'&&opt<='9'){res=(res<<3)+(res<<1)+opt-'0';opt=getchar();}
	return res*flag;
}
typedef long long ll;
int n,a[N],l[N],c[N];
ll ans,Ans[N];
vector<int>g[N];
inline void Add(int x){while(x<=n)++c[x],x+=x&-x;}
inline int Ask(int x){int res=0;while(x)res+=c[x],x-=x&-x;return res;}
int main(void){
	int i;n=read();for(i=1;i<=n;++i)a[i]=min(n,read()+1),g[a[i]].push_back(i);
	for(i=1;i<=n;++i)l[i]=Ask(n)-Ask(a[i]),Add(a[i]),ans+=l[i];Ans[n-1]=ans;
	for(i=n-1;i;--i){for(int x:g[i])ans-=l[x];Ans[i-1]=ans;}
	for(i=0;i<n;++i)printf("%lld\n",Ans[i]);
	return 0;
}

```

---

## 作者：Strong_Jelly (赞：0)

**不用求逆序对的方法也可以做。**

逆序对指，设一个数列中有A和B两个元素，如果A的值大于B的值，且A的下标小于B的下标，称A和B为一对逆序对。

首先观察样例得知，如果数列中出现过j - 1，那么就会出现逆序对。具体出现多少呢？设当j增加1时，如果i点的值不变，那么称作一次修改。因为j在不断提高，所以j - 1也在不断提高，因此后来修改的值，肯定大于前面修改的值，并且小于没被修改过的值。不难得出，每一次修改，都会增加1 ~ i - 1中没被修改过的数量个逆序对。

所以我们只需要求出在当前j时，如果j - 1这个值出现过，答案就累加1 ~ i - 1中没被修改过的数量（i为j - 1这个值在原数列中的位置），问题就是求1 ~ i - 1中有多少个没被修改过的呢？暴力肯定是不行的，n ^ 2会炸，所以考虑线段树维护，具体参见代码。

全文 + 代码：https://www.cnblogs.com/qqq1112/p/13117572.html

---

