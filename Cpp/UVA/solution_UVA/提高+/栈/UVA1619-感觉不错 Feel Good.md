# 感觉不错 Feel Good

## 题目背景

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4494

[PDF](https://uva.onlinejudge.org/external/16/p1619.pdf)

## 题目描述

给出正整数 $n$ 和一个长度为 $n$ 的数列 $a$，要求找出一个子区间 $[l,r]$，使这个子区间的数字和乘上子区间中的最小值最大。

形式化的，要求找出 $[l,r]$ 使得：
$$
\left(\sum \limits_{i=l}^{r}a_i\right)\times\min\limits_{i=l}^{r}a_i
$$
最大。输出这个最大值与区间的两个端点。

在答案相等的情况下最小化区间长度，最小化长度的情况下最小化左端点序号。


## 说明/提示

$1 \leq n \leq 10^5, 0 \leq a_i \leq 10^6$。

## 样例 #1

### 输入

```
6
3 1 6 4 5 2```

### 输出

```
60
3 5```

# 题解

## 作者：Mr_think (赞：25)

## [UVA1619 感觉不错 Feel Good](https://www.luogu.com.cn/problem/UVA1619)
## 题目大意： 
给出正整数n和一个$(1 <= n <= 100 000)$长度的数列，要求找出一个子区间，使这个子区间的数字和乘上子区间中的最小值最大。输出这个最大值与区间的两个端点。
## solution:

很暴力的去想，我们可以枚举区间$[l,r]$,遍历这个区间找到最小值，同时算出区间和。但很明显时间复杂度爆炸$O(N^3)$

我们再审一遍题：
```
使这个子区间的数字和乘上子区间中的最小值最大
```
既然枚举区间行不通，不妨试着枚举**最小值**：对于每一个数列中的数字 $a_i$ ，找到当它作为数列最小值时最长的序列，得到序列的端点 $l,r$。预处理前缀和，通过$a[r]-a[l-1]$求出区间的和，乘这个最小值$a[i]$最后取一个$max$

## 接下来是细节的处理：
我们想要找到当$a[i]$作为最小值的最长序列，就要找到$a[i]$左边、右边最后一个比它大的数，或者说找到第一个**比它小的数**，左右分别为$a[l]$、$a[r]$,我们想要得到的左端点、右端点就为：$l+1$、$r-1$

现在我们请出主角：[**单调栈**](https://www.luogu.com.cn/problem/P5788)
~~在这不多做赘述，不会的自己看看吧~~

具体操作见代码：

```cpp
//找右端第一个比a[i]小的数，把右端点赋成i-1
for(int i=1;i<=n;i++)
{
    while(top&&a[i]<a[st[top]]) 
        you[st[top--]]=i-1;
    st[++top]=i;
}
while(top) you[st[top--]]=n;//剩下的就是没找到比它小的，就将右端点r赋成n



//找左端第一个比a[i]小的数，把左端点赋成i+1
for(int i=n;i>=1;i--)
{
	while(top&&a[i]<a[st[top]]) 
       	zuo[st[top--]]=i+1;
    st[++top]=i;
}
while(top) zuo[st[top--]]=1;同理，没找到将左端点l赋值成1
```
再处理下前缀和
```cpp
for(int i=1;i<=n;i++)
{
    scanf("%lld",&a[i]);
    p[i]=p[i-1]+a[i];
}
```
~~完结撒……~~**此题还有很多坑点**

UVA是多组输入 我们需要
```cpp
while(scanf("%d",&n)!=EOF)
```
此题**没有**SPJ，需要在最大值相同时，使区间尽量**短**，于是出现了下面的判断：
```cpp
long long now;//不开long long见祖宗 
now=a[i]*(p[you[i]]-p[zuo[i]-1]);//当前乘积 
if(now>ans||(now==ans&&you[i]-zuo[i]<dy-dz))
{
	ans=now;
	dz=zuo[i];dy=you[i];//保存答案 
}
```
平均下来时间复杂度$O(N)$

看到这的同学，可以自己去写代码了(~~tf口吻~~)

[还是给你们吧[手动滑稽]](https://www.luogu.com.cn/paste/xnya0dek)

### End

## 作者的碎碎念：

作为一个初三党，做题的时间可谓少之又少，写题解就更不用说了，这是刚期末考试完才抽出时间写的，觉得有帮助的话就点个赞，谢谢了

---

## 作者：Stinger (赞：5)

### solution

题目要求求出一个连续子序列，求出这个子序列各个元素之和乘上该序列中的最小值，最简单的做法就是枚举序列的起点和终点，然后找最小值和求和，时间复杂度 $O(n^3)$ ，直接TLE……

求和的过程大家都会优化，可以用一个数组保存前缀和，设为 $t_i$。

既然是一个连续子序列，那么我们考虑枚举该序列的最小值，设为 $a_i$。 从 $a_i$ 开始向左右进行“扫描”，直到找到左边和右边第一个小于 $a_i$ 的数，这违反了将 $a_i$ 作为该序列最小值的规定，于是确定下来序列的起点和终点。

综上时间复杂度为 $O(N^2)$ ， 在 $O(N^3)$ 的基础上优化掉了求和和找最小值的过程。

那我们考虑继续优化，这个算法的时间全部花在了枚举 $a_i$ 和计算序列起点和终点上。枚举 $a_i$ 似乎很难优化掉，但是找序列起点和终点的过程其实就是找到每个数在左右第一个小于它的数，于是可以考虑进行预处理：$l_i$ 表示以 $a_i$ 做最小值序列的左边界，$r_i$ 同理。

这是本题的难点，可以使用一个栈进行计算。具体过程如下：
  
1. 建立一个栈，初始时为空；

2. 从1到 $n$ 进行扫描，若栈为空，转4，否则转3；

3. 当栈非空时，如果栈顶元素大于当前元素，则 $r[s.top()] = $ 当前元素编号 - 1，弹栈；

4. 当前元素入栈；

5. 扫描完毕后，栈中所有元素r值明显为n，依次弹出并给他们的r值赋值。

为什么这样做是成立的，~~请自己思考~~对上述做法的证明：

我们在栈内保存的元素都是当前还没有找到右边比它大的数的编号，因此栈里的元素（设为 $i$ )离栈顶越近 $a_i$ 越大，因为如果栈中存在一个压在它下面的数 $j$ 则 $j < i$，且 $a_j > a_i$ 则 $a_i$ 这个数是一个在 $a_j$ 右边的比他小的数，那么 $j$ 肯定已经找到了“右边比它大的数的值”所以 $a_j < a_i$。

因此，这个栈是从底往顶单调递增的。对于一个新入栈的元素编号 $x$, 如果当前栈顶元素 $i$ 满足 $a_i < a_x$ ，则栈中压在元素 $i$ 下面的数也肯定比 $a_x$ 小，那么此时我们break。由于每个元素至多被弹出和删除一次，所以时间复杂度为 $O(N)$。~~好像有点单调队列的味道~~。

计算r值的代码如下：

```cpp

for (int i = 1; i <= n; i ++)
{
	while (s.size() && a[s.top()] > a[i])
	{
		r[s.top()] = i - 1;
		s.pop();
	}
	s.push(i);
}
while (s.size())
r[s.top()] = n, s.pop();
```

计算l值的方法类似。

另外本题没有SPJ，另外的题解说过了（雾）。

综上时间复杂度为 $O(N)$，完结撒花~

code：

```cpp
#include <cstdio>
#include <stack>
#define MAX_N 100005
#define int long long //日常防毒瘤数据 

using namespace std;

int a[MAX_N], t[MAX_N], l[MAX_N], r[MAX_N];
stack<int> s; 
char ch;

//日常卡常优化，这个题不用读负数 
inline void read(int &x)
{
	x = 0;
	while ((ch = getchar()) < 48 || ch > 57);
	while (ch >= 48 && ch <= 57)
	x = (x << 1) + (x << 3) + ch - 48, ch = getchar();
}

signed main()
{
	int n, ans, sta, e;
	bool b = 0;
	while (scanf("%lld", &n) != EOF)
	{
		if (b) putchar('\n');//这里输出格式很重要，我在vjudge上总是PE计算因为这个 
		else b = 1;
		ans = 0, sta = 1, e = 1;
		for (int i = 1; i <= n; i ++)
		read(a[i]);
		//经典的前缀和…… 
		for (int i = 1; i <= n; i ++)
		t[i] = t[i - 1] + a[i];
		//预处理，这是重点 
		for (int i = 1; i <= n; i ++)
		{
			while (s.size() && a[s.top()] > a[i])
			{
				r[s.top()] = i - 1;
				s.pop();
			}
			s.push(i);
		}
		while (s.size())
		r[s.top()] = n, s.pop();
		for (int i = n; i >= 1; i --)
		{
			while (s.size() && a[s.top()] > a[i])
			{
				l[s.top()] = i + 1;
				s.pop();
			}
			s.push(i);
		}
		while (s.size())
		l[s.top()] = 1, s.pop();
		//正文开始，撒花，没有SPJ 
		for (int i = 1; i <= n; i ++)
		{
			int st = l[i], en = r[i];
			if ((t[en] - t[st - 1]) * a[i] > ans)
			ans = (t[en] - t[st - 1]) * a[i], sta = st, e = en;
			else if (ans == (t[en] - t[st - 1]) * a[i] && (e - sta > en - st || (e - sta == en - st && sta > st)))
			sta = st, e = en;
		}
		printf("%lld\n%lld %lld\n", ans, sta, e);
	}
	return 0;//程序中最激动人心的一句话 
}
```

---

## 作者：Steadywelkin (赞：5)

[UVA1619 Feel Good](https://www.luogu.com.cn/problem/UVA1619)

题意就是找到一个子区间，一个子区间的值定义为区间内最小的值与区间总和的乘积，求子区间的值的极大值，并输出左右端点。

首先，子区间的加和可以直接预处理前缀和即可，关键在于如何求出最大值。对于每一个子区间，如果它可以向两边延展且在区间内的最小值不发生变化，那么这个区间的值必然会增大。所以，如果要求得子区间的最大值，它必然到达了这个序列的边界或者再向外延展会使区间内的最小值变得更小，我们只要找到所有这样的无法再向外延展的子区间，再一一比较即可。

考虑如何寻找这样的一个子区间。其实我们可以对于每一个子区间这样看：以某一个数为中心，两边所能延展的最长长度乘上它的值。也就是下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/4i5k3cjq.png)

所以，我们只要考虑求这个区间的长度。可以发现，这个区间对向左和向右两个方向都满足单调不降性，所以，只要用两个单调栈维护这两个长度，最后再一一进行比较，就可以AC了。

---

## 作者：让风忽悠你 (赞：4)

[原题](https://www.luogu.com.cn/problem/UVA1619)

## 题意

给出一个长度为 $n$ 的序列，要求一个区间满足这个区间的最小值和区间和的积最大，并输出这个值和区间的左右端点。

## 做法

悬线法的大概思想就是把一个区间当作一条具有初始位置和高度两个性质的线，再在满足一定条件的情况下将这条线拓宽。

此题中可以将每个位置所代表的数抽象为高度，区间和可以用前缀和维护，而区间最小值可以将初始位置的数当作最小值，即**拓宽这条线时要满足的条件为大于等于初始位置的数**。

值得一提的是这道题没有设置 $spj$，所以在更新最优解的时候需要选择区间长度最小的。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#define N 100005
#define ll long long

using namespace std;

int n;
int l[N],r[N];
ll a[N],sum[N],ans;
int ansl,ansr;
bool fl;

int main(){
	while(scanf("%d",&n)!=EOF){
		ans=0;
		ansl=ansr=1; // 初始化 
		if(fl) printf("\n");
    	else fl=1; // uva 恶心的过行 
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			sum[i]=sum[i-1]+a[i]; 
			l[i]=r[i]=i; // 维护前缀和和悬线初始位置 
		}
		for(int i=1;i<=n;i++)
			while(l[i]>1 && a[i]<=a[l[i]-1]) l[i]=l[l[i]-1];
		for(int i=n;i>=1;i--)
			while(r[i]<n && a[i]<=a[r[i]+1]) r[i]=r[r[i]+1];
		// 拓宽悬线 
		for(int i=1;i<=n;i++){
			ll cur=(sum[r[i]]-sum[l[i]-1])*a[i];
			if(cur>ans || (cur==ans && (r[i]-l[i]+1)<(ansr-ansl+1))){
				ans=cur;
				ansr=r[i];
				ansl=l[i];
			} // 更新最优解 
		}	
		printf("%lld\n%d %d\n",ans,ansl,ansr);
	}
	return 0;
}
```


---

## 作者：iiiiiyang (赞：2)

[逆天的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17836147.html)

[题目链接](https://www.luogu.com.cn/problem/UVA1619)

依然枚举每个位置作为最小值的情况，记录“值/下标”二元组，按第一维从大到小排序后，每次将第二位的位置在序列中标成 $1$，那么选择的一定是序列里一个 $1$ 的极长段。加入一个位置检查其左右是否加入过，如果加入过就用并查集合并掉，同时维护极长段的和/左右端点是简单的，复杂度 $\mathcal O(n \log n + n \alpha (n))$，瓶颈在于排序。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define ui unsigned int
#define ld long double
#define power(x) ((x)*(x))
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define mp make_pair
#define fi first
#define se second
#define TT template<typename T>
#define TA template<typename T,typename ...Args>
#define dbg(x) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<'\n'
using namespace std;
using pii=pair<int,int>;
using pdi=pair<double,int>;
using piii=pair<pair<int,int>,int>;

bool Mbe;

namespace IO
{
    inline int read()
    {
        int s=0,w=0; char c=getchar();
        while(!isdigit(c)) w|=c=='-',c=getchar();
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*(w?-1:1);
    }
    TT inline void read(T &s)
    {
        s=0; int w=0; char c=getchar();
        while(!isdigit(c)) w|=c=='-',c=getchar();
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s*=w?-1:1;
    }
    TA inline void read(T &x,Args &...args) {read(x),read(args...);}
    TT inline void write(T x,char ch=' ')
    {
        if(x<0) x=-x,putchar('-');
        static char stk[30]; int top=0;
        do stk[top++]=x%10+'0',x/=10; while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
    }
}
using namespace IO;

namespace MTool
{
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=max(a,b);}
    TA inline void cmax(T &a,T b,Args ...args) {a=max({a,b,args...});}
    TT inline void cmin(T &a,T b) {a=min(a,b);}
    TA inline void cmin(T &a,T b,Args ...args) {a=min({a,b,args...});}
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
}

namespace LgxTpre
{
    constexpr int MAX=100010;
    constexpr int inf=2147483647;
    constexpr int INF=4557430888798830399;
    
    int n,vis[MAX],fl,ansl,ansr,ans;
	pii a[MAX];
    
    namespace DSU
    {
    	int fa[MAX],siz[MAX],sum[MAX],L[MAX],R[MAX];
    	inline void init() {for(int i=1;i<=n;++i) fa[i]=i,siz[i]=1,sum[i]=a[i].fi,L[i]=R[i]=i;}
    	int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}
    	inline void merge(int x,int y)
		{
			x=find(x),y=find(y);
			if(x==y) return;
			siz[x]>siz[y]
			?(siz[x]+=siz[y],fa[y]=x,sum[x]+=sum[y],cmin(L[x],L[y]),cmax(R[x],R[y]))
			:(siz[y]+=siz[x],fa[x]=y,sum[y]+=sum[x],cmin(L[y],L[x]),cmax(R[y],R[x]));
		}
	}
	using namespace DSU;
    
    inline void lmy_forever()
    {
    	while(scanf("%lld",&n)!=EOF)
    	{
    		if(fl) puts(""); else fl=1;
    		for(int i=1;i<=n;++i) a[i]=mp(read(),i);
    		init(),sort(a+1,a+n+1,[](pii a,pii b){return a.fi>b.fi;}),ans=0,ansl=ansr=1;
    		for(int i=1;i<=n;++i)
    		{
    			auto [v,p]=a[i]; vis[p]=1;
    			if(vis[p-1]) merge(p,p-1);
    			if(vis[p+1]) merge(p,p+1);
    			int f=find(p);
    			if((ans<sum[f]*v)||(ans==sum[f]*v&&R[f]-L[f]<ansr-ansl)||(ans==sum[f]*v&&R[f]-L[f]==ansr-ansl&&L[f]<ansl)) ans=sum[f]*v,ansl=L[f],ansr=R[f];
			}
			for(int i=1;i<=n;++i) vis[i]=0;
			write(ans,'\n'),write(ansl),write(ansr,'\n');
		}
	}
}

bool Med;

signed main()
{
//  file();
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    fprintf(stderr,"\nMemory: %.3lf MB",abs(&Mbe-&Med)/1024.0/1024.0);
    fprintf(stderr,"\nTime: %.3lf ms",1e3*(Ted-Tbe)/CLOCKS_PER_SEC);
    return (0-0);
}
```

---

## 作者：ztasd (赞：2)

## 0.题面：
>给出正整数 $n$ 和一个($1 <= n <= 100 000$)长度的数列，要求找出一个子区间，使这个子区间的数字和乘上子区间中的最小值最大。输出这个最大值与区间的两个端点。

## 1.思路

一开始试图使用单调栈，然而在调试一上午无果后愤然打了个分治，然后就过了233

根据分治三步法，算法流程分为：

1.分解：定义 $dfs(l,r)$ 为区间 $[l,r]$ 的最优解，$mid = (l+r)/2$ ，可以把问题分为 $dfs(l,mid)$ 和 $dfs(mid+1,r)$ 两部分，分别对应最优解完全位于左子区间和右子区间的情况。

2.边界：当 $l=r$ 时，$dfs(l,r)={a_l}^2$。（数列为 $a$）

3.合并：在第一步处理了最优解完全位于左子区间和右子区间的情况，还有最优解跨越 $mid$ 的情况没处理。注意到当最小值一定时，区间越大越好，所以可以从大到小地选择最大值，再从中点开始往左右两端“放宽”当前区间。

## 2.Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000000
typedef long long ll;
int n;
ll a[MAXN+5],sum[MAXN+5],ans;
struct answ{
	int l,r;ll v;
	answ(){
		l=r=v=0;
	}
	answ(int L,int R,ll V){
		l=L;r=R;v=V;
	}
};
bool operator < (answ l,answ r){
	return l.v<r.v;
}
struct ST{
	ll st[MAXN+1][31];
	int query(int l,int r){
        int k=log2(r-l+1);
        return min(st[l][k],st[r-(1<<k)+1][k]);
    }
    void build(){
    	for(int i=1;i<=n;i++){
    		st[i][0]=a[i];
		}
    	for(int j=1;j<=30;j++){
            for(int i=1;i+(1<<j)-1<=n;i++){
                st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            }
        }
	}
}qwq;
ll query(int l,int r){
	return qwq.query(l,r)*(sum[r]-sum[l-1]);
}//求一个区间的“数字和乘上子区间中的最小值”
answ dfs(int l,int r){//分治主体
	int mid=(l+r)/2;
	if(l==r){//边界
		return answ(l,r,query(l,r));
	}
	answ ans=max(dfs(l,mid),dfs(mid+1,r));
	vector<int> tmp;
	for(int i=l;i<=r;i++){
		tmp.push_back(a[i]);
	}
	sort(tmp.begin(),tmp.end());reverse(tmp.begin(),tmp.end());//从大到小地取区间最小值
	int L=mid,R=mid+1;
	ans=max(ans,answ(L,R,query(L,R)));
	for(int i=0;i<tmp.size();i++){//由于最小值“逐渐放宽”，所以区间只增不减
		if(tmp[i]>a[mid]||tmp[i]>a[mid]){
			continue;
		}
		while(a[L-1]>=tmp[i]&&L!=l){
			L--;
		}
		while(a[R+1]>=tmp[i]&&R!=r){
			R++;
		}//区间越大越好
		ans=max(ans,answ(L,R,query(L,R)));
	}
	return ans;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	sum[i]=sum[i-1]+a[i];
    }
    qwq.build();
    answ ans=dfs(1,n);
    cout<<ans.v<<endl;
    cout<<ans.l<<" "<<ans.r<<endl;
    return 0; 
}
```

###### 3. $\texttt{求管理员大大通过！QWQ}$

---

## 作者：haomie (赞：2)

这题可以利用栈的特性，我们把从a[1]开始，将每个元素入栈，当栈顶元素大于当前元素，说明以栈顶元素为最小值的区间的右端位于当前位置之前，将1->n个元素为最小值的区间的右端找出来，然后从a[n]开始，同理可得到左区间。

然后利用前缀和，可以快速计算出以当前元素为最小值的区间的sum并乘于当前元素，然后for：1->n跑一遍取max即可出答案。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
using namespace std;
const int mx=100005;
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9'){
        if(c=='-')
            flag=1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    if(flag)
        x=-x;
    return x;
}
long long sum[mx],a[mx];
int main()
{
	int n=0,T=0;
	while(cin>>n)
	{
		if(T++)printf("\n");//按题目要求，每个答案间要有空行
		int l[mx],r[mx];
		memset(sum,0,sizeof(sum));
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++)
			a[i]=read(),sum[i]+=sum[i-1]+a[i];
		stack<int> s;
		for(int i=1;i<=n;i++)
		{
  		//若栈顶的值大于当前的值，说明栈顶所能到达的最右边就在i-1处
			while(!s.empty()&&a[s.top()]>a[i])
			{
				r[s.top()]=i-1;
				s.pop();
			}
			s.push(i);
		}
     		//还在栈内的元素所能达到的最右明显为n
		while(!s.empty())
		{
			r[s.top()]=n;
			s.pop();
		}
		for(int i=n;i>=1;i--)
		{
     		//同理，最左边在i+1处
			while(!s.empty()&&a[s.top()]>a[i])
			{
				l[s.top()]=i+1;
				s.pop();
			}
			s.push(i);
		}
    		//还在还在栈内的元素最左边明显为1
		while(!s.empty())
		{
			l[s.top()]=1;
			s.pop();
		}
		long long mxx=a[0];
		int ll=1,rr=1;
		for(int i=1;i<n;i++)//找出答案
		{
			if(mxx<(sum[r[i]]-sum[l[i]-1])*a[i])
			{
				mxx=(sum[r[i]]-sum[l[i]-1])*a[i];
				rr=r[i];
				ll=l[i];
			}
           //题目实际不存在SPJ，实际要求区间长度最小，然后区间左端最小
			else if(mxx==(sum[r[i]]-sum[l[i]-1])*a[i])
			{
            	
				if(rr-ll>r[i]-l[i])
				{
					rr=r[i];
					ll=l[i];
				}
				else if(rr-ll==r[i]-l[i]&&l[i]+1<ll)
				{
					rr=r[i];
					ll=l[i];
				}
			}
		}
		printf("%lld\n",mxx);
		printf("%d %d\n",ll,rr);
	}

}
```


---

## 作者：✨USTCJYZ✨ (赞：2)

###### ~~这段代码在UVA上过了~~
### 首先al+…+ar=s[r]-s[l-1],所以求和用前缀和来记录
### 其次求第l个数到第r个数的最小元素，由贪心可知只需计算每个ai作为最小元素的最大区间即可
### 求每个ai作为最小元素的最大区间可用单调优先队列来实现。
#### **另外，此题的坑点是当最大值相同时不是输出任意区间都可以的，应该是输出最短的区间，当区间长度相同时输出左端点最小的区间
# **
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<queue>
#include<map>
#include<sstream>
#include<set>
#include<stack>
#include<iterator>
#include<cctype>
#include<cmath>
#include<cassert>
using namespace std;
#define ll long long
const ll maxn=100000+10;
ll n,s[maxn];
struct point{
	ll num,l,r,d,s;
	point(ll num=0,ll l=0,ll r=0,ll d=0,ll s=0):num(num),l(l),r(r),d(d),s(s){};
	bool operator <(const point&p)const {
		return s>p.s||(s==p.s&&d<p.d)||(s==p.s&&d==p.d&&l<p.l);
	}
}p[maxn];
struct po{
	ll num,id;
	po(ll num=0,ll id=0):num(num),id(id){};
	bool operator <(const po&p)const{
		return num<p.num;
	}
};
int main(){
	bool f=false;
	while(scanf("%lld",&n)!=EOF){
		if(f)cout<<endl;
		else f=true;
		priority_queue<po> q;
		memset(s,0,sizeof(s));
		for(ll i=1;i<=n;i++){
			scanf("%lld",&p[i].num);
			s[i]=s[i-1]+p[i].num;
			if(q.empty()){
				q.push(po(p[i].num,i));
				p[i].l=1;
				continue;
			}
			po u=q.top();
			p[i].l=i;
			while(u.num>=p[i].num){
				p[u.id].r=i-1;
				p[i].l=min(p[i].l,p[u.id].l);
				q.pop();
				if(q.empty())break;
				u=q.top();
			}
			q.push(po(p[i].num,i));
		}
		while(!q.empty()){
			po u=q.top();
			p[u.id].r=n;
			q.pop();
		}
		for(ll i=1;i<=n;i++){
			p[i].d=p[i].r-p[i].l;
			p[i].s=(s[p[i].r]-s[p[i].l-1])*p[i].num;
		}
		sort(p+1,p+n+1);
		printf("%lld\n%lld %lld\n",p[1].s,p[1].l,p[1].r);
	}
	return 0;
}

```


---

## 作者：gyfer (赞：2)

没人发题解，那我就发一波吧

$n<=1e5$

$O(n^2)$暴力显然过不了，那么我们考虑优化

题目中说是区间的和乘上区间的最小值最大，我们转化一下问题把枚举区间转化为枚举最小值然后算区间答案，那么我们就可以先预处理每个数左边最后一个比它大的数，右边最后一个比它大的数。
例如它们的下标是$l,r$那么我们的答案是$sum_{l~r}*a[now]$难点在于预处理。
预处理有两种方法
1. 维护单调栈，每次更新栈顶，大于现在的值的元素弹出。
2. 链表形式每次向左跳（~~和NOIP2018初赛类似~~）
注意答案输出，最左边区间长最短的序列
代码（不要粘我的，UVA这题有坑，但POJ我过了）

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
#include<cmath>
#include<map>
#include<set>
using namespace std;
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define PER(i, a, b) for(int i = a; i >= b; i--)
#define int long long
inline int read(){
    int x = 0, flag = 1;char ch = getchar();
    while(!isdigit(ch)) {
        if(ch == '-') flag = -1;
        ch = getchar();
    }
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x * flag;
}

const int N = 1e6 + 5;
int n, a[N], l[N], r[N], ansl, ansr;
int s[N], ans;

signed main() {   
    int tim = 0;
    while(scanf("%lld", &n) == 1 && n) {
        if(tim) cout << endl;
        ++tim;
        REP(i, 1, n) a[i] = read(), s[i] = s[i - 1] + a[i], l[i] = r[i] = i;
        REP(i, 1, n) 
            while(a[l[i] - 1] > a[i]) l[i] = l[l[i] - 1];
        PER(i, n, 1)
            while(a[r[i] + 1] > a[i]) r[i] = r[r[i] + 1];
        ans = 0; ansl = ansr = 0;
        REP(i, 1, n) {
            int sum = a[i] * (s[r[i]] - s[l[i] - 1]);
            if(sum > ans || (sum == ans && ansr - ansl > r[i] - l[i])) {
                ans = sum;
                ansr = r[i]; ansl = l[i];
            }
        }
        printf("%lld\n%lld %lld\n", ans, ansl, ansr);
    }
	return 0;
}
```


---

## 作者：fanypcd (赞：1)

[UVA1619 感觉不错 Feel Good](https://www.luogu.com.cn/problem/UVA1619)

预处理+DP  $O(n)$ 。

我们记：

- n 为数列的长度
- $a_i$ 表示数列的第 i 号元素
- $l_i$ 表示从第 i 号元素向左最多延伸到哪里（使得 $a_i$ 始终是 $\min_{j=l_i}^{i} a_j$）
- $r_i$ 表示从第 i 号元素向右最多延伸到哪里（使得 $a_i$ 始终是 $\min_{j=i}^{r_i} a_j$）
- 题目中**子区间的数字和乘上子区间中的最小值**为这个子区间的权值

这样以 $a_i$ 号元素为最小值的区间的权值最大就是 $a_i \times  \sum_{j=l_i}^{r_i}a_j$

前面部分显然 $O(1)$ ，前缀和可以让后面的部分变成 $O(1)$，所以总复杂度为 $O(n)$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 100005
int n, a[N], b[N], l[N], r[N];
signed main()
{
	int T = 0;
	while(scanf("%lld", &n) != EOF && n)
	{
		if(T++)
		{
			putchar(10);
		}
		for(int i = 1; i <= n; i++)
		{
			scanf("%lld", &a[i]);
			b[i] = b[i - 1] + a[i];
		}
		for(int i = 1; i <= n; i++)
		{
			if(i == 1)
			{
				l[i] = 1;
				continue;
			}
			int pos = i - 1;
			for(; pos >= 1; pos--)
			{
				if(a[i] > a[pos])
				{
					break;
				}
				else
				{
					pos = l[pos];
				}
			}
			l[i] = pos + 1;
		}
		for(int i = n; i >= 1; i--)
		{
			if(i == n)
			{
				r[i] = n;
				continue;
			}
			int pos = i + 1;
			for(; pos <= n; pos++)
			{
				if(a[i] > a[pos])
				{
					break;
				}
				else
				{
					pos = r[pos];
				}
			}
			r[i] = pos - 1;
		}
		int ans = 0, ansl = 1, ansr = 1;
		for(int i = 1; i <= n; i++)
		{
			if(ans < a[i] * (b[r[i]] - b[l[i] - 1]))
			{
				ans = a[i] * (b[r[i]] - b[l[i] - 1]);
				ansl = l[i];
				ansr = r[i];
			}
			else if(ans == a[i] * (b[r[i]] - b[l[i] - 1]))
			{
				if(ansr - ansl + 1 > r[i] - l[i] + 1)
				{
					ansl = l[i];
					ansr = r[i];
				}
				else if(ansr - ansl + 1 == r[i] - l[i] + 1)
				{
					if(l[i] < ansl)
					{
						ansl = l[i];
						ansr = r[i];
					}
				}
			}
		}
		printf("%lld\n", ans);
		printf("%lld %lld\n", ansl, ansr);
	}
	return 0;
}
```



---

## 作者：漠寒 (赞：1)

# 温馨提示（放在最前面）

1.$UVA$多组数据。

2.两组数据之间应有空行。

3.所有数据都为0时，$ans$=0，$anl$=$anr$=1（卡了我半小时的坑）。

还有一点于代码中讲。

## 正文

我们可以发现影响答案的只有两个因素，前缀和就不用说了，用一个数组保存（我亲眼见证隔壁一个一个加$TLE$的惨案）。

对于区间内的最小值，可以用单调栈的思想来解决，我们现在以一个值设置为接下来的区间最小值，很容易想到它当然是影响力越大越好（函数单调递增），所以就往前往后安排一个单减栈，在出现一个比它更小的值之后， 它的影响力便烟消云散（让着小朋友）。

总结而来，对于$a_i$来说，它作为区间最小值能得到的最大答案便是左边第一个小于它的值的位置+1到右边第一个小于它的值的位置-1，这两个之间的和乘上它自己。

### 即：

```cpp
ans=max(ans,a[i]*(b[r[i]]-b[l[i]-1]))
```

当然，你还不能用$max$，因为还要找左右端点。

### 于是我们可以上代码了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int unsigned long long
using namespace std;
int n,a[100050],l[100050],r[100050],anl=1,anr=1,ans,b[100050];
char ch;
int s[100050],top,bb;
inline void read(int &x)
{
	x = 0;
	while ((ch = getchar()) < 48 || ch > 57);
	while (ch >= 48 && ch <= 57)
	x = (x << 1) + (x << 3) + ch - 48, ch = getchar();
}
signed main()
{
	while(cin>>n){
		if (bb) putchar('\n');
		else bb = 1;
		top=0;
		ans=0;
		anl=1;
		anr=1;
		memset(a,0,sizeof(a));
		memset(l,0,sizeof(a));
		memset(r,0,sizeof(a));
		memset(b,0,sizeof(a));
		memset(s,0,sizeof(a));
		for(int i=1;i<=n;i++){
			read(a[i]);
			b[i]=b[i-1]+a[i];
		}
		for(int i=1;i<=n;i++){
			while(top&&a[s[top]]>=a[i])top--;
			l[i]=s[top]+1;
			s[++top]=i;
		}
		top=0;
		s[0]=n+1;
		for(int i=n;i>=1;i--){
			while(top&&a[s[top]]>=a[i])top--;
			r[i]=s[top]-1;
			s[++top]=i;
		}
		for(int i=1;i<=n;i++){
			int x=a[i]*(b[r[i]]-b[l[i]-1]);
			if(x>ans){
				anl=l[i];
				anr=r[i];
				ans=x;
			}
			/*
			最后一个 温馨提示
			本题没有SPJ，因此在ans相等时需要找区间长度更短的
            		同样短的时候又要找左端点最左边的
			*/ 
			if(x==ans&&((r[i]-l[i]<anr-anl)||(r[i]-l[i]==anr-anl)&&l[i]<anl)){
				anl=l[i];
				anr=r[i];
				ans=x;
			}
		}
		cout<<ans<<endl;
		cout<<anl<<" "<<anr<<endl;
	}
	
	return 0;
}
```


---

## 作者：frank520 (赞：1)

# 典型单调栈
（蒟蒻学会写单调栈之后的嚎叫声~~~）

（对于数据输出和多组阴间数据的输入我就不讲了）

分析
我们可以看到题目的数据范围为100000，如果我们用暴力你是绝对过不了的，那我们就要考虑单调栈。那么 怎么去维护呢？就是找到每一个数的一个区间，让这个数是这个区间里的最小值，最后在跑一次$1$~$n$算出$ans$，每跑一次比较一次$ans$取$max$。

对于这个区间的左端点，从1循环到你，如果数组里没有元素，就直接入栈，如果有元素，且$top$的这个元素小于等于（要等于!）此时你枚举的这个元素，那就让它出队，最后把此时的栈顶元素存入$l[i]$中；对于右端点，从$n$循环到$1$就行。

给各位提供一组数据 如果你不知道为啥过不了可以试试 输入


```cpp
8 10 10 19

390
2 4
```

上代码（这个代码直接抄是过不了的哦亲 要自己改一下输入输出）

```cpp
#include<iostream>
#include<cstring>
#include<stack>
#define int long long//日常不放心 
using namespace std;
int n,l[100005],r[100005],in[100005],a[100005];//a存前缀和 in为输入 
stack<int> s;
inline int read(){
    int f=1,res=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        res=res*10+ch-'0';
        ch=getchar();
    }
    return f*res;
}
inline void cancel(){
    while(s.size()!=0) s.pop();
}
signed main(){//要改成signed 
    int ans=0;
    int al,ar;//存答案的左右端点 
    memset(a,0,sizeof(a));
    n=read();
    for(int i=1;i<=n;i++){
        in[i]=read();
        a[i]=a[i-1]+in[i];
    }//输入并计算前缀和 
    for(int i=1;i<=n;i++){
        if(s.size()==0) {
            s.push(i);
            l[i]=i-1;//我的命名为左端点再左边一个的那个位置 
            continue;
        }
        while(s.size()!=0&&in[s.top()]>=in[i]) s.pop();
        if(s.size()==0) {//万一出栈出完了不特判就会出问题 
            l[i]=0;
            s.push(i);
            continue;
        }
        l[i]=s.top();
        s.push(i);
    }//找左端点 
    cancel();//一定要清空栈！！！！！ 
    for(int i=n;i>=1;i--){
        if(s.size()==0){
            s.push(i);
            r[i]=i+1;
            continue;
        }
        while(s.size()!=0&&in[s.top()]>=in[i]) s.pop();
        if(s.size()==0) {
            r[i]=n+1;
            s.push(i);
            continue;
        }
        r[i]=s.top();
        s.push(i);
    }//找右端点同理 
    /*for(int i=1;i<=n;i++) printf("%d ",l[i]);
    printf("\n");
    for(int i=1;i<=n;i++) printf("%d ",r[i]);//这几行验证左右端点

    printf("\n");
    for(int i=1;i<=n;i++) printf("%d ",a[i]);//验证前缀和 
    printf("\n");*/
    for(int i=1;i<=n;i++){//跑一遍找答案 
        long long x;
        if(r[i]-l[i]==2){
            x=in[i]*in[i];
            if(ans<=x){
                ans=x;
                al=i;
                ar=i;
            }
            continue;
        }
        x=in[i]*(a[r[i]-1]-a[l[i]]);
        if(ans<=x){
            ans=x;
            al=l[i]+1;
            ar=r[i]-1;//要存位置 注意加减 
        }
    }
    printf("%lld\n",ans);
    printf("%lld %lld",al,ar);//输出 
    return 0;//我喜欢这句话 
}
```


## 感谢支持蒟蒻
（我居然发现这代码刚好能过[poj](http://poj.org/problem?id=2796)上的这题）

---

## 作者：__usingnamespace__ (赞：1)

### [link](https://www.luogu.com.cn/problem/UVA1619)
一道不错的单调栈板子题。如果不知道单调栈的话建议先过[模板](https://www.luogu.com.cn/problem/P5788),此外这道题还有一个[简化版的](http://poj.org/problem?id=2559)（可惜洛谷上没有这道题）。

由于是求区间最小的数与区间所有数之和的积，考虑维护一个不下降的栈来求区间最小值。可以通过计算当以第 $i$ 列的数为最小值时最大宽度以获取最大区间和，并把所有计算结果取最大值即可。

对于每个数，记录其入栈时间(即位置 $i$ )、以它为最小值的最宽区间的左端点 $l$ 。

每当一个新元素 $a_i$ 入栈前，先从栈顶反复查看其大小与 $a_i$ 的关系。

若 $a_i$ 更小，则弹出栈顶元素并更新 $ans$ ，宽度就是从左端点 $l$ 到 $i$ ，并使用前缀和计算区间和。

若 $a_i$ 更大，则将 $a_i$ 其左端点 $l$ 设置为栈顶元素的入栈时间$+1$，因为维护了栈的单调不下降，所以不用考虑比 $a_i$ 更小的数已经被弹出的情况。最后将 $a_i$ 入栈，记录当前 $i$ 值。具体代码如下：
```cpp
for(int i=1;i<=n+1;i++)
{
    while(tot&&st[tot]>a[i])
    {
        if(ans<(sum[i-1]-sum[fr[tot]-1])*st[tot])
        {
            ans=(sum[i-1]-sum[fr[tot]-1])*st[tot];
            al=fr[tot];
            ar=i-1;
        }else if(ans==(sum[i-1]-sum[fr[tot]-1])*st[tot])
        {
            if(ar-al>i-fr[tot]||ar-al==i-fr[tot]&&fr[tot]<al||al==0&&ar==0)
            {
                al=fr[tot];
                ar=i-1;
            }
        }
        tot--;
    }
    tot++;
    st[tot]=a[i];
    fr[tot]=pl[tot-1]+1;
    pl[tot]=i;
}
```
最后就是一些小处理：

通过讨论我们得知：此题并无spj，而是在满足 $ans$ 最大的情况下最小化宽度；最小化宽度的情况下最小化左端点 $l$ 序号。所以要在更新 $ans$ 时要加特判。

把第 $n+1$ 个数赋值为 $-1$ 然后循环的时候多跑一遍把结束时仍在栈内的数全部清空。

还有就是这个题卡 $long$ $long$ 。
## Code
```cpp
#include<iostream>
#include"stdio.h"
#define int long long//懒人写法 
using namespace std;
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
    return x*f;
}
int n,a[100010],st[100010],fr[100010],pl[100010];
//记录数值，栈内数值，栈内元素左端点，栈内元素入栈时间 
int tot,ans,sum[100010],al,ar;
//栈长度，最大结果，前缀和，最大结果左右端点 
signed main()
{
    n=read();
    for(int i=1;i<=n;i++)a[i]=read(),sum[i]=sum[i-1]+a[i];
    a[n+1]=-1;
	for(int i=1;i<=n+1;i++)
	{
	    while(tot&&st[tot]>a[i])
	    {
	        if(ans<(sum[i-1]-sum[fr[tot]-1])*st[tot])
	        {
	            ans=(sum[i-1]-sum[fr[tot]-1])*st[tot];
	            al=fr[tot];
	            ar=i-1;
	        }else if(ans==(sum[i-1]-sum[fr[tot]-1])*st[tot])
	        {
	            if(ar-al>i-fr[tot]||ar-al==i-fr[tot]&&fr[tot]<al||al==0&&ar==0)
	            {
	                al=fr[tot];
	                ar=i-1;
	            }
	        }
	        tot--;
	    }
	    tot++;
	    st[tot]=a[i];
	    fr[tot]=pl[tot-1]+1;
	    pl[tot]=i;
	}
    cout<<ans<<endl;
    cout<<al<<" "<<ar<<endl;
}
```


---

## 作者：Viktley (赞：0)

**题目大意:**

$n$ 个数，求某段区间的最小值 * 该段区间所有元素之和的最大值 

------------

**思路：**

其实这道题是 [Imbalanced Array](https://www.luogu.com.cn/problem/CF817D) 的基础版，思路也其实是一样的。

我们以当前点为中心，分左右用 while 扩展，由于题目要求最小值，那么我们就建立一个单调递增栈（~~反之，此点是最大值，我们就建一个单调递减栈，主要是题目不用求~~),直到不能求为止，求完后得到 $[l....i....r]$ （ $l$ 表示能到的最大的左边界，$r$ 同理可知）

**注意:**

1. 左右区间可能会有重复数字，所以扩展时的判断条件有不同（为了判重）

2. 每次处理前要初始化（注意要放墙，不同情况的墙有所不同）

**code:**

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#define ll long long
#define fre(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
using namespace std;
const int MAX=2147483647;
const int N=1e6+10;
struct node
{
	int val,l,r;
} a[N];
ll n,sum[N],sta[N],ans=0,ans_l=1,ans_r=1;
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i].val),sum[i]=sum[i-1]+a[i].val,a[i].l=a[i].r=i;
	ll top=0;
	for(int i=1;i<=n;i++)
	{
		while(top&&a[sta[top]].val>=a[i].val) a[i].l=a[sta[top]].l,top--;
		sta[++top]=i;
 	}
 	memset(sta,0,sizeof(sta));
 	top=0;
	for(int i=n;i>=1;i--)
	{
		while(top&&a[sta[top]].val>=a[i].val) a[i].r=a[sta[top]].r,top--;
		sta[++top]=i;
	}
	for(int i=1;i<=n;i++)
		if(a[i].val*(sum[a[i].r]-sum[a[i].l-1])>ans) 
			ans=a[i].val*(sum[a[i].r]-sum[a[i].l-1]),ans_l=a[i].l,ans_r=a[i].r;
	printf("%lld\n%lld %lld",ans,ans_l,ans_r);
	return 0;
}
```


---

