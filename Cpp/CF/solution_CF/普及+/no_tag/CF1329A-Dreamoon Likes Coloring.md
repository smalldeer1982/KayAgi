# Dreamoon Likes Coloring

## 题目描述

Dreamoon likes coloring cells very much.

There is a row of $ n $ cells. Initially, all cells are empty (don't contain any color). Cells are numbered from $ 1 $ to $ n $ .

You are given an integer $ m $ and $ m $ integers $ l_1, l_2, \ldots, l_m $ ( $ 1 \le l_i \le n $ )

Dreamoon will perform $ m $ operations.

In $ i $ -th operation, Dreamoon will choose a number $ p_i $ from range $ [1, n-l_i+1] $ (inclusive) and will paint all cells from $ p_i $ to $ p_i+l_i-1 $ (inclusive) in $ i $ -th color. Note that cells may be colored more one than once, in this case, cell will have the color from the latest operation.

Dreamoon hopes that after these $ m $ operations, all colors will appear at least once and all cells will be colored. Please help Dreamoon to choose $ p_i $ in each operation to satisfy all constraints.

## 样例 #1

### 输入

```
5 3
3 2 2```

### 输出

```
2 4 1```

## 样例 #2

### 输入

```
10 1
1```

### 输出

```
-1```

# 题解

## 作者：奇米 (赞：7)

# 题解 - $\mathrm{CF1329A\ Dreamoon\ Likes\ Coloring}$ 

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

### 题目意思

* [CF1329A](https://www.luogu.com.cn/problem/CF1329A)

* 就是让你构造一个长为$m(\leq 10^5)$的序列$p_i$，每次把颜色$i$覆盖$[p_i,p_i+l_i-1]$使得把$n$个位置全覆盖且$1-m$的颜色全部出现。

### $\mathrm{Sol}$
* 考场$FST$，我也真的自闭（现在发现一种更为简单的做法$qwq$）

* 我们首先考虑无解的情况，有两种：

	- $(1)\sum l_i\leq n-1$
    
    - $ (2)∃ l_i+i-1>n$ （即$p_j=j(j<i)$却满足不了）

* 那么我们就从无解的第二种情况下手：我们记录一个后缀和$suf_i$，我们先贪心地涂色即$p_i=i(i+suf_i-1>=n)$，否则我们就使得他刚好覆盖长度为$n$的区间即可，即$b_i=n-suf_i+1$。这很好理解，然后就撒花了。

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define int long long 
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

const int N=1e5+5;

int n,m,a[N],b[N],sum[N],suf[N],ans;

signed main()
{
	n=read();
	m=read();
	int all=0;
	for ( int i=1;i<=m;i++ ) 
	{
		a[i]=read(); 
		all+=a[i];
		if(i+a[i]-1>n) 
			return printf("-1\n"),0;
	}
	for ( int i=n;i>=1;i-- ) 
		suf[i]=suf[i+1]+a[i];
	if(all<n) return printf("-1\n"),0;
	b[1]=1;
	for ( int i=2;i<=m;i++ )
	{
		if(i+suf[i]-1>=n) b[i]=i;
		else b[i]=n-suf[i]+1;
	}
	for ( int i=1;i<=m;i++ ) printf("%lld ",b[i]);
	return 0;
}
		
		 
	
```


---

## 作者：Eibon (赞：6)

首先，如果所有 $l_{i}$ 加在一起，都比 $n$ 小，必然不符合题意。

因为后面的颜色会覆盖前面的颜色，我们不妨让第一个颜色从一开始，接下来的每一个颜色的开始位置都在上一个的后面一个。即第 $i$ 个颜色从第 $i$ 格开始涂。

发现如果 $l_{i}+i-1>n$，就会涂到外面，则必然不合法。

接下来的涂过的序列可能会小于 $n$，不妨对这个序列操作，让一些颜色的开始位置后移。

这里选择从后面开始，所能后移的最大长度就是 $\min\left(l_{i-1},n-p\right)$。

这里的 $p$ 表示末尾。

需要判断，在移动过程中，可能有其他颜色优先抵达 $n$ 点。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int T,n,m,num,VIP,sum,p;
int l[maxn],a[maxn];
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld",&l[i]);
		a[i]=1;
		num+=l[i];
		if(l[i]+i-1>n){
			VIP=1;
		}
	}
	if(num<n||VIP){
		printf("-1\n");
		return 0;
	}
	p=m+l[m]-1;//cout<<p<<endl;
	for(int i=m;i>=2;i--){
		if(p==n){
			break;
		}
		if(n-(i+l[i]-1)<=min(l[i-1]-1,n-p)){
			a[i]+=n-(i+l[i]-1);//cout<<a[i]<<endl;
			break;
		}
		a[i]+=min(l[i-1]-1,n-p);
		p+=min(l[i-1]-1,n-p);
	}
	for(int i=1;i<=m;i++){
		sum+=a[i];
		printf("%lld ",sum);
	}
	printf("\n");
	return 0;
}
//dyyyyds
```

---

## 作者：蒟酱 (赞：3)

提供一个简短的题解：  
首先如果所有长度加起来还不到 $n$ 直接无解。  
可以直接贪心，把第 $i$ 条线段的右端点放在 $n-i+1$ 这个位置，就可以最省长度（只占一个点）而且不会遗漏，如果左端点小于 $1$ 也判无解。  
操作完之后发现左边有一些没染色的格子，把最后盖上去的线段往左拖过来首位相接就行了。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<tuple>
#include<numeric>
#define siz(x) int((x).size())
#define cauto const auto
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
using std::cin;using std::cout;
using std::max;using std::min;
using std::tie;using std::ignore;
template<typename any>inline void cmin(any &x,const any &y){if(y<x)x=y;}
template<typename any>inline void cmax(any &x,const any &y){if(x<y)x=y;}
template<typename any,typename...args>inline void cmax(any &x,const any &y,const args &...z){cmax(x,y);cmax(x,z...);}
template<typename any,typename...args>inline void cmin(any &x,const any &y,const args &...z){cmin(x,y);cmin(x,z...);}
using loli=long long;
using uloli=unsigned long long;
using lodb=long double;
using venti=__int128_t;
using pii=std::pair<int,int>;
using inlsi=const std::initializer_list<int>&;
using bsi=std::basic_string<int>;
using bsc=std::basic_string<char>;
constexpr venti operator""_vt(uloli x){return venti(x);}
constexpr int N=1e5+1,inf=0x3f3f3f3f;
int n,m,p1=1,p2=inf,l[N],p[N];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n>>m;for(int i=1;i<=m;i++)cin>>l[i];
	if(std::accumulate(l+1,l+1+m,0ll)<n)return cout<<"-1",0;
	for(int i=1;i<=m;i++)if(cmin(p2,p[i]=n-i+2-l[i]),p2<=0)return cout<<"-1",0;
	for(int i=m;p1<=p2;i--)p[i]=p1,p1+=l[i];
	for(int i=1;i<=m;i++)cout<<p[i]<<' ';
	return 0;
}
```

---

## 作者：一扶苏一 (赞：3)

## 【构造】【CF1329A】Dreamoon Likes Coloring

### Analysis

减号写成加号导致 fst，嘤嘤嘤。

首先如果所有颜色都平铺开也不能铺满这 $n$ 个格子，那么显然无解。

考虑由于最后要求所有颜色都至少“露出”一个格子来，那么不妨首先保证所有颜色都有对应的格子，然后进行调整。方法是对于每一个颜色，都尽可能地贴着右侧放。也即第 $i$ 种颜色的右端点放在 $(n - i + 1)$ 格，这样对于每种颜色，都至少露出了最右侧的一个格子。在这个过程中，如果某一个颜色的左端点比 $1$ 小，那么无解（因为第 $i$ 个颜色至少要空出 $(i - 1)$ 个格子给之前的颜色，而在这种构造方式也恰好空出了 $(i - 1)$ 个格子，因此如果这种方式无法构造，那么不会有更优的选择，一定无解）。

先把所有颜色都尽可能往右放以后，发现左侧可能会空出来一部分位置。对于这些位置，我们从后往前用颜色铺满这些位置即可。也即先把编号为 $m$ 的颜色放到 $[1, l_m]$ 去，如果还没有铺满，就把 $(m - 1)$ 号的左端点放到 $(l_m + 1)$ 位置去，以此类推。之前已经判过铺不满了，所以这样一定能铺满。而需要把第 $i$ 个颜色这么处理一定意味着前 $i$ 个颜色的最靠左的左端点比后面几个颜色达到的右端点至少大 $2$。也就是说颜色 $i$ 一定是向左移动的，不会盖住比 $i$ 小的颜色露出的位置。

考虑如何判断是否铺满：在第一个过程中（也即尽可能往右放）维护前 $i$ 个颜色的左端点的最小值 $p_i$，在进行第二个过程时，设当前考虑到第 $i$ 个颜色，如果 $\sum_{k = i + 1}^k l_k < p_i - 1$，那么意味着至少 $p_i - 1$ 这个位置是空着的，需要把第 $i$ 个颜色向左移动。

时间复杂度 $O(n)$。

### Code

```cpp
const int maxn = 100005;

int n, m;
int a[maxn], l[maxn], r[maxn], pl[maxn];

int main() {
  freopen("1.in", "r", stdin);
  qr(n); qr(m);
  qra(a + 1, m);
  ll sum = 0;
  pl[0] = n;
  for (int i = 1; i <= m; ++i) {
    sum += a[i];
    r[i] = n - i + 1;
    l[i] = r[i] - a[i] + 1;
    if (l[i] <= 0) return puts("-1") & 0;
    pl[i] = std::min(l[i], pl[i - 1]);
  }
  if (sum < n) return puts("-1") & 0;
  if (pl[m] != 1) {
    sum = 0;
    for (int i = m; i; --i) {
      l[i] = sum + 1;
      sum += a[i];
      if (sum >= pl[i - 1]) {
        break;
      }
    }
  }
  qwa(l + 1, m, ' ', '\n');
  return 0;
}
```



---

## 作者：liuli688 (赞：2)

### 思路
一道比较简单的构造 & 贪心题，大概在下位绿。

考虑题目给我们的两个要求：
- 每个格子都被刷上了颜色；
- 每种颜色至少出现了一次。

由“每个格子都被刷上了颜色“可以想到，为了能尽可能的让被涂色的格子多，可以尽可能的让颜色不重叠。比如，当前颜色涂的是 $[p, p + l _ i)$ 格，那么下一个颜色可以涂 $[p + l _ i, p + l _ i + l _ {i + 1})$ 格。

再考虑第二个条件。显然，当当前颜色刷上之后出界了，那么就要将间距减小。到底要减小多少呢？正向考虑不好想，那么我们记录一个后缀和，倒序考虑是否要减小间距。

至于减小多少，只需要将间距设为 $1$ 即可，这样最方便。
### 代码
```cpp
#include <cstdio>
#include <numeric>
#include <algorithm>
using ll = long long;

constexpr int N = 1e5 + 2;
int n, m, l[N];
ll sum[N];

signed main()
{
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= m; ++i)
    {
		scanf("%d", l + i);
        if (l[i] + i - 1 > n) //如果一定会出界
            return printf("-1\n"), 0;
    }
    for (register int i = m; i; --i) //后缀和
        sum[i] = sum[i + 1] + l[i];
    if (sum[1] < n) //颜色不够
        return printf("-1\n"), 0;
    printf("1 ");
    for (register int i = 2; i <= m; ++i)
        if (i + sum[i] - 1 >= n) //超出范围，减小间距
            printf("%d ", i);
    	else //最大间距
            printf("%d ", n - sum[i] + 1);
    return 0;
}
```

---

## 作者：Meatherm (赞：2)

首先判断无解。

当 $\sum{l_i} \leq m$ 的时候，显然是无解的。但容易忽略另外一种无解的情况：例如 $n=5,l=[3,3,4]$，这也是无解的，因为就算前两种颜色只刷一个位置，轮到第三种颜色的时候起始位置也应该是 $3$，而从 $3$ 开始连刷 $4$ 格显然超过了 $n$，不合题意。所以如果存在 $i$ 满足 $i+l_i-1>n$，也无解。

判断完无解之后，我们可以算出在不重合的情况下刷完所有 $m$ 种颜色超出了多少格，即 $\sum l_i -n$，记作 $ret$。然后我们考虑将下一个颜色的起始位置往前移，抵消掉一部分 $ret$ ，直到 $ret=0$。

```cpp
# include <bits/stdc++.h>
# define rr register
# define int long long
const int N=100010,INF=0x3f3f3f3f;
int l[N];
int n,m;
int ans[N];
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
signed main(void){
	n=read(),m=read();
	int sum=0;
	for(rr int i=1;i<=m;++i){
		l[i]=read();
		sum+=l[i];
		if(i+l[i]-1>n){
			printf("-1");
			return 0;
		} 
	}
	if(sum<n){ 
		printf("-1");
		return 0;
	}
	int ret=sum-n,last=1; // last 是上一个放的位置 因为第一个颜色一定放在 1 所以 last = 1
	ans[1]=1;
	for(rr int i=2;i<=m;++i){
		if(ret>=(l[i-1]-1)){ // 注意 最多只能往前挪 (l[i-1]+1) 格 颜色 i-1 至少要有 1 格
			ret-=(l[i-1]-1);// 消去 ret
			ans[i]=last+1;
			++last;// 更新 last
		}else{
			last=last+l[i-1]-ret; // 如果 ret 不足 (l[i-1]+1) 则最多只能往前挪 ret 格 并顺手把 ret 清零
			ret=0;
			ans[i]=last;
		}
	}
	for(rr int i=1;i<=m;++i){
		printf("%I64d ",ans[i]);
	}
	return 0;
}
```

### 

---

## 作者：tommymio (赞：1)

这题非常好想，每次涂色可以看成是一个区间覆盖，那么我们让这些区间尽量靠近 $N$，并且没有交集，如果最左端点 $> 1$ 则必然不可行。

接着，可以想到，由于一部分区间在负半轴上，那我们将上面求出的区间的最左端点平移到 $1$ 上时，即将整个左端点在负半轴上的区间移动到正半轴上，若能够进行这样的一次平移，必然可行，否则不可行。

那考虑一下每一次对一组区间的移动，必然是把当前区间的右端点移到上一个区间的右端点 $-1$ 的位置，左端点也对应这个右端点移动，这样的一次移动对小于当前区间左端点的区间都会产生影响，所以是一个区间加的操作。

但是我们发现由于这个区间加的左端点是固定的，右端点单调递减，于是边统计答案边累加即可，时间复杂度为 $O(m)$.

**Show the Code**
```
#include<cstdio>
#include<algorithm>
#define int long long 
#define min(a,b) ((a)<(b)? (a):(b))
int res[100005],id[100005],l[100005],d[100005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline bool cmp(int x,int y) {return l[x]>l[y];}
signed main() {
	int n=read(),m=read(),mn=n+1,len=0,sumT=0;
	for(register int i=1;i<=m;++i) l[i]=read();
	res[0]=n+1;
	for(register int i=1;i<=m;++i) d[i]=res[i]=res[i-1]-l[i];
	for(register int i=1;i<=m;++i) mn=min(mn,res[i]);
	if(mn>1) {printf("-1\n");return 0;}
	len=1-mn;
	for(register int i=2;i<=m;++i) {
		//if(len==0) {res[i]+=sum;continue;}
		if(len==0) {d[i]+=sumT;continue;}
		int preL=res[i-1],preR=res[i-1]+l[i-1]-1;//[preL,preR]
		int L=res[i],R=res[i]+l[i]-1;//[L,R]
		int tmp=min(len,preR-1-R);
		len-=tmp;
		sumT+=tmp;
		d[i]+=sumT;
	}
	if(len) {printf("-1\n");return 0;}
	for(register int i=1;i<=m;++i) {if(d[i]<1) {printf("-1\n");return 0;}}
	for(register int i=1;i<=m;++i) printf("%lld ",d[i]);
	return 0;
}
```

---

## 作者：Mcggvc (赞：1)

构造题

题意：按顺序用给定长度的块覆盖区间，不能超出区间左右端点，要求最后每种颜色都要存在，序列上每个位置都要有覆盖的颜色。

先按顺序把每一个尽量靠左放置，第i个颜色放第i个位置，最后再调整。

有两种情况无法构造：

1.所有块总长度加起来小于区间长度，即$\sum_{i = 1}^{m} l_i < n$

2.放置第i个颜色时长度超过了右端点。

如果序列末尾有空余没有被覆盖，则从最后一个块开始，尽量靠右贴，直到没有空余的位置。

注意：
1.不能排序  2.所有块总长度能爆int
 ```cpp
 
 #include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lld;
const int N = 100010;
int n, m;
lld tot = 0;
int ans[N], e[N];
void print() {
	for(int i = 1; i <= m; i++) {
		printf("%d ", ans[i]);
	}
	return ;
}
int main() {
//	freopen("data.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		scanf("%d", &e[i]);
		tot += e[i];
	}
	if(tot < n) {
		printf("-1"); return 0;
	}
	for(int i = 1; i <= m; i++) {
		if(i + e[i] - 1 <= n) ans[i] = i;
		else {
			printf("-1"); return 0;
		}
	}
	if(e[m] + ans[m] - 1 > n) {
		printf("-1"); return 0;
	}
	if(e[m] + ans[m] - 1 == n) {
		print(); return 0;
	}
	int nowp = n;
	for(int i = m; i >= 1; i--) {
		if(ans[i] + e[i] - 1 < nowp) {
			ans[i] = nowp - e[i] + 1;
			nowp = ans[i] - 1;
		} else nowp = ans[i] - 1;
	}
	print();
	return 0;
}
 ```

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**模拟**的思路:

- 我们可以先忽略 $n$，把所有颜色**全部展开**，记录其开始位置。

- 然后我们可以理解为颜色需要**缩回** $(\sum_{i=1}^{m}{l_i})-n$ 格，这是因为**颜色可以覆盖**。

- 对于第 $i$ 个颜色，可以**缩回** $l_i-1$ 格。我们在缩回时**记录缩了几格**。

- 在输出时，我们就可以**累积**往前缩了几格，输出即可。

## CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,sum,ans,base,maxi,l[N],f[N],pos[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>l[i];
		sum+=l[i];//展开后的长度
		base+=l[i]-1;
		pos[i]=i+base;//记录展开后的位置（尾巴）
		maxi=max(maxi,i+l[i]-1);//最短情况
	}
	if(maxi>n||sum<n)
	{//最短情况过长或最长情况过短
		cout<<-1;
		exit(0);
	}
	else
	{
		base=0;
		ans=sum-n;
		for(int i=1;i<m;i++)
		{
			if(l[i]-1<=ans)
			{//当前点可以全缩
				ans-=l[i]-1;//缩
				f[i]-=l[i]-1;//缩了多少
			}
			else if(l[i]-1>ans&&ans!=0)
			{//缩一部分
				f[i]-=ans;
				ans=0;
			}
			if(ans==0)
			{//缩完了
				break;
			}
		}
		for(int i=1;i<=m;i++)
		{//原位置-前面缩了多少-自身
			cout<<pos[i]+base-l[i]+1<<" ";
			base+=f[i];//加上这个缩了多少
		}
	}
	exit(0);
}
```

---

## 作者：nao_nao (赞：0)

看了大佬的做法好厉害，我在这里分享一下我这个小蒟蒻的做法。

并不懂构造，因此并没有大佬那样系统的思路。我们可以发现，如果有解，那么当区间左端点按照区间顺序排序的话一定也有解 ~~（感性理解）~~。

想一想如果不要求输出最后方案怎么解决？我的想法是可以DP呀！我们可以发现按照顺序枚举区间，我们发现后一个区间的起始位置一定是前一个区间可以覆盖到的位置，当然了，为了保证最后每一种颜色都能露出来，区间的起始点不能重叠。我们这样枚举，往下DP，就可以得到是否能成功覆盖的答案了。

我们考虑如何输出答案呢？我们想一下需要具体方案的01背包问题，我们可以从结果开始往回推，就能得到答案。那么遇到多种合法情况怎么选择呢？当然是随便选啦，合法了害怕什么？

考虑复杂度，我们发现复杂度超了，怎么办？我们可以发现对于每一个区间的合法的可能的覆盖位置，一定是连续的（显然），因此我们只需要保存区间的左右端点即可，复杂度瞬间优化掉一维（空间也是）。

最后放上本蒟蒻的代码啦！

code：
```cpp
#include <cstdio>
#include <algorithm>
 
using namespace std;
const int INF=2e9,N=2e6+7;
int read()
{
	int a = 0,x = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') x = -1;
		ch = getchar();
	}
	while(ch <= '9' && ch >= '0'){
		a = a*10 + ch-'0';
		ch = getchar();
	}
	return a*x;
}
int m,n;
int l[N],ans[N];
int dp[N][3];
int find(int a,int b,int c,int d)//这里随便找一种合法方案
{
	if(b < c || d < a) return -1;
	return max(a,c); 
}
int main()
{
	n = read(),m = read();
	for(int i = 1;i <= m;i ++) l[i] = read();
	for(int i = 1;i <= m;i ++){//这里DP可能的覆盖区间
		int a,b;
		dp[i][1] = dp[i-1][1] + 1,dp[i][2] = min(dp[i-1][2]+l[i],n);
		if(dp[i][1] + l[i]-1 > n){//发现无合法区间，直接无解
			printf("-1");
			return 0;
		}
	}
	if(dp[m][2] < n) {//发现不能全覆盖，无解
		printf("-1");
		return 0;
	}
	int tmp = n-l[m]+1;
	ans[m] = n-l[m]+1,ans[1] = 1;
	for(int i = m-1;i >= 2;i --){//找一种合法方案
		int q = find(dp[i][1],dp[i][2],tmp-l[i],tmp-1);
		if(q == -1){
			printf("%d",-1);
			return 0;
		}
		ans[i] = q;
		tmp = q;
	}
	for(int i = 1;i <= m;i ++) printf("%d ",ans[i]);//输出方案
	return 0;
	
}
```

---

