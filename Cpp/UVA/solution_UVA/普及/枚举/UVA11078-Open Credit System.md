# Open Credit System

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2019

[PDF](https://uva.onlinejudge.org/external/110/p11078.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11078/25cd6848e8285209c3495ee0e4d8dbf426b85add.png)

## 样例 #1

### 输入

```
3
2
100
20
4
4
3
2
1
4
1
2
3
4```

### 输出

```
80
3
-1```

# 题解

## 作者：Kdlyh (赞：7)

_蓝书上的题目的好多题解都是照搬啊，希望各位注明下出处吧。。。_

这道题蓝书上给的$O(n)$解法大概是这样的，大概就是维护一个$maxx$表示**当$i<j$时$a[i]$的最大值**，然后不断更新它的最大值和答案的最大值即可。

------------

但是!——在最后蓝书上还布置了个作业，写个边读入边处理的解法。现在就来讲下这个解法。

在$O(n)$解法中，我们发现，这个$maxx$的值是不会被**第$j$个数之后的数改变的**，所以根本不需要读入后再处理，直接在读入第$j$个数时把$maxx$更新一下就行了,然后同样更新下答案的最大值。

$\mathcal{CODE:}$
```cpp
#include <cstdio>
#define inf 0x7fffffff
#define max(a,b) (a)>(b)?(a):(b)

inline void read(int &x)
{
    x=0;char ch=0;bool sign=false;
    while(ch < '0' || ch > '9')
    {
        sign|=(ch == '-');
        ch=getchar();
    }
    while(!(ch < '0' || ch > '9'))
    {
        x=x*10+(ch^48);
        ch=getchar();
    }
    x=sign ? -x : x;
}

inline void print(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}

int n,a[10000100];
int ans,maxx;

int main()
{
    int T;
    read(T);
    for(int kase=1; kase<=T; kase++)
    {
        ans=-inf,maxx=-inf/3;
        read(n);
        for(int i=1; i<=n; i++)
        {
            read(a[i]);
            ans=max(ans,maxx-a[i]);
            maxx=max(a[i],maxx);
        }
        print(ans);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：Hiraeth (赞：4)

就暴力算法而言 这里就不展开讨论了

也是一种比较常见的打法吧

要求 ans=(f [ i ]-f [ j ]）max 

就当前位置 j 而言 如果要使得ans最大 则要求f [ i ]最大

那么可以边输入边更新当前位置之前所有元素的最大值 

然后在计算ans 不断更新ans 从而求出最优解

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],n,maxx,ans,t;
int main(){
	scanf("%d",&t);
	while(t--){
		memset(a,0,sizeof(a));
		maxx=-1e6;
		ans=-1e6;
		scanf("%d",&n);
		for (int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			ans=max(ans,maxx-a[i]);
			maxx=max(a[i],maxx);
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

## 作者：ygsldr (赞：3)

刘汝佳蓝书经典题，从O(n^2)优化到O(n)

首先是n^2的想法，很简单，枚举每个i和j，但是数据范围显然不能支持

然后是O(n)的想法，对于在某一个位置前的数，可以用O(n)的预处理处理出最大的，再用O(n)的预处理处理出某一个位置后的最小值。假设b[i]代表posi <= i中a[i]最大值，c[j]代表posj > j最小值，那只要枚举1~n,结果就是最大的b[i] - c[i]，正确性是显然的

但这样会浪费O(n)的空间复杂度，我们考虑边读入边操作，用一个max记录读入到现在的最大值，每读入一个就更新ans的最大值，这样，我们的时间复杂度是O(n),空间复杂度是O(1)

代码就不贴出了，重要的是扫描法优化复杂度的思想

---

## 作者：仰望半月的夜 (赞：1)

**原题：[UVA11078 Open Credit System](https://www.luogu.org/problem/UVA11078)**

估计有一部分人~~跟我一样~~是从[P5146 最大差值](https://www.luogu.org/problem/P5146)这题过来的。

有人说这两题基本一样，可是有个非常有趣的现象：

UVA11708标签：````线段树、枚举,暴力、优先队列````

P5146标签：````动态规划,动规,dp````

于是我就纳闷了，说好的极其相似呢？

于是我就用最简单的思路看了这两题，发现在这个思路里，两题真的区别不大。

（我等会儿也顺便讲讲P5146和这题的区别，也附上代码）

题意不难读懂，即给出多组数据，要我们在每一组数据中求较前面的数与较后面的数之差的最大值。

将这组数记在数组$a$中，即求：

## $\max(a[i]-a[j])$，其中$i<j$

接着进行分析。

## 很明显，在$a[j]$一定的情况下，要使差值最大，那么$a[i]$的值就必须尽量大。

### 所以此题用模拟，求出**前面所输入的数的最大值**与**当前的数**之差的最大值，就可以~~水~~过了。

### $\color{red}\text{而且我们边读边判，根本不需要开数组。}$

### $\texttt{code}$
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define s(a,b,c) scanf("%d %d %d",&(a),&(b),&(c))
#define x(a) scanf("%lld",&(a))
#define q(a) scanf("%s",(a))
#define d(a) printf("%lld\n",(a))
#define p(a,b) printf("%d %d\n",(a),(b))
#define ll long long
using namespace std;
ll t,ans,i,j,n,maxn,a;
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		scanf("%lld",&maxn);//把第一个读入的数当成初始最大值
		ans=-1231564987984564;
		for(i=1;i<n;i++){
			scanf("%lld",&a);
			ans=max(ans,maxn-a);
			maxn=max(maxn,a);//这两行顺序别搞错！！！这样避免i=j的情况出现
		}
		printf("%lld\n",ans);//别忘记换行
	}
	return 0;
}
```
然后说说[P5146 最大差值](https://www.luogu.org/problem/P5146)

题意：**只给出一组数据**，要我们在这组数据中求**较后面**的数与**较前面**的数之差的最大值。

看到区别了吧

## $\max(a[i]-a[j])$，其中$i>j$

相反的，求出**当前的数**与**前面所输入的数的最小值**之差的最大值即可。

同样不需要开数组。

### $\texttt{code}$
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define s(a,b,c) scanf("%d %d %d",&(a),&(b),&(c))
#define x(a) scanf("%lld",&(a))
#define q(a) scanf("%s",(a))
#define d(a) printf("%lld\n",(a))
#define p(a,b) printf("%d %d\n",(a),(b))
#define ll long long
using namespace std;
ll t,ans,i,n,minn,a;
int main(){
	scanf("%lld",&n);
	scanf("%lld",&minn);//把第一个读入的数当成初始最小值
	ans=-1231564987984564;
	for(i=1;i<n;i++){
		scanf("%lld",&a);
		ans=max(ans,a-minn);
		minn=min(minn,a);
	}
	printf("%lld\n",ans);//别忘记换行
	return 0;
}
```

---

## 作者：l_water (赞：1)

23333，用掉了STL库里面的优先队列水掉了这个题目QAQ，但是O(nlogn)的时间复杂度是水不过5e6的了（吸氧是可以的），那么这篇题解就仅供STL库的练习参考吧！
```
#include<bits/stdc++.h>
using namespace std;
int n,t,a[10000100],maxn=-0x7f7f7f7f;//线段树模板给的惨痛教训！！一定要设负值
priority_queue<int,vector<int>,less<int> > q;//定义一个大根堆
int main()
{
	ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	cin>>t;//以上为加速
	for(register int i=1;i<=t;i++)
	{
	memset(a,0,sizeof(a));
	while(!q.empty()) q.pop();
	maxn=-0x7f7f7f7f;
	cin>>n;
	for(register int i=1;i<=n;i++) cin>>a[i];
	for(register int i=1;i<=n;i++)
	{	
		if(i>1)//第一次因为i的缘故所以导致了RE，然后在前面加了q.push(0),WAWAWAl了QAQ
		maxn=max(q.top()-a[i],maxn);//保证i<j,取出最大的保证可以更新
		q.push(a[i]);
	}
	cout<<maxn<<endl;
	}
	return 0;
}
```
感谢 @zzsqwq大佬在讨论的指导！超级感谢哇！

---

## 作者：我不是小明 (赞：1)

一看到这题，首先可以想到的就是有二重循环枚举a[i]-a[j]的最大值，就是这样：
```cpp
#include<bits/stdc++.h>//懒人牌万能头文件 
using namespace std;
int main()
{
	int t,a[100001],n;
	scanf("%d",&t);//比cin快 
	while(t--)
	{
		int ans=-1e9;//初始化，不能为0！！因为可能比0小 
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)//满足i<j 
				ans=max(ans,a[i]-a[j]);//打擂台，取最大的a[i]-a[j] 
		printf("%d\n",ans);
	}
	return 0;
}
```
但这种方法的效率低下，时间复杂度是O(n^2)，而n最大是10000，所以会TLE。那么让我们来想想该怎么解决。其实我们这么想：a[i]-a[j]要尽可能大，那么a[j]就必须尽可能小，那我们可以将mina看成a[j]的最小值，将其初始化为a[n],因为要保证i<j,所以我们就从后往前枚举，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,a[100001],n;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		int ans=-1e9,mina=a[n];
		for(int i=n-1;i>=1;i--)
		{
			ans=max(ans,a[i]-mina);
			mina=min(a[i],mina);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Tenshi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA11078)

## 分析
题解都是线性复杂度的算法 $Orz$ ，而我第一眼的想法是分治。。。

所以我就来一个分治的做法吧，步骤如下：

> 我们约定 $mid=\lfloor \frac{l+r}{2} \rfloor$

1. $solve(l, r)$ 代表区间 $[l,r]$ 对应的题目所求的值 
2. 那么区间 $[l,r]$ 的答案所对应的 $i,j$ 分布情况只可能是以下三种：

$i\in [l,mid], ~j\in [mid+1,r]$
$i\in [l,mid], ~j\in [1,mid]$
$i\in [mid+1,r], ~j\in [mid+1,r]$

熟悉分治的同学都知道，第二、三种情况继续往下递归处理即可，重点在于求第一种情况。

3. 也就是说，我们需要高效地知道 $[l,mid]$ 对应的最大值，$[mid+1,r]$ 对应的最小值，而这个操作，我们用两个 st 表维护即可。

代码：
```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define debug(x) cerr << #x << ": " << x << endl
#define pb(a) push_back(a)
#define set0(a) memset(a,0,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define ceil(a,b) (a+(b-1))/b
#define INF 0x3f3f3f3f
#define ll_INF 0x7f7f7f7f7f7f7f7f
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;

inline int read()
{
	int x=0,y=1;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') y=-1;c=getchar();}
	while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x*y;
}

const int N=1e5+5;
int n, w[N];

int st_max[N][20], st_min[N][20], Log[N];
void build(){
	rep(i, 2, n) Log[i]=Log[i/2]+1;
	
	rep(j, 0, 19) for(int i=1; i+(1<<j)-1<=n; i++)
		if(!j) st_max[i][j]=w[i];
		else st_max[i][j]=max(st_max[i][j-1], st_max[i+(1<<j-1)][j-1]);
		
	rep(j, 0, 19) for(int i=1; i+(1<<j)-1<=n; i++)
		if(!j) st_min[i][j]=w[i];
		else st_min[i][j]=min(st_min[i][j-1], st_min[i+(1<<j-1)][j-1]);
}

int query_max(int l, int r){
	int s=Log[r-l+1];
	return max(st_max[l][s], st_max[r-(1<<s)+1][s]);
}

int query_min(int l, int r){
	int s=Log[r-l+1];
	return min(st_min[l][s], st_min[r-(1<<s)+1][s]);
}

int solve(int l, int r){
	if(l>=r) return -INF;
	int mid=l+r>>1;
	
	int res=query_max(l, mid)-query_min(mid+1, r);
	res=max(res, max(solve(l, mid), solve(mid+1, r)));
	return res;
}

int main(){
	int T; cin>>T;
	while(T--){
		cin>>n;
		rep(i, 1, n) cin>>w[i];
		build();
		
		cout<<solve(1, n)<<endl;
	}
    return 0;
}
```

---

