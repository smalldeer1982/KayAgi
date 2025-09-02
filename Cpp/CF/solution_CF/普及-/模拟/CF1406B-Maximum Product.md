# Maximum Product

## 题目描述

You are given an array of integers $ a_1,a_2,\ldots,a_n $ . Find the maximum possible value of $ a_ia_ja_ka_la_t $ among all five indices $ (i, j, k, l, t) $ ( $ i<j<k<l<t $ ).

## 说明/提示

In the first test case, choosing $ a_1,a_2,a_3,a_4,a_5 $ is a best choice: $ (-1)\cdot (-2) \cdot (-3)\cdot (-4)\cdot (-5)=-120 $ .

In the second test case, choosing $ a_1,a_2,a_3,a_5,a_6 $ is a best choice: $ (-1)\cdot (-2) \cdot (-3)\cdot 2\cdot (-1)=12 $ .

In the third test case, choosing $ a_1,a_2,a_3,a_4,a_5 $ is a best choice: $ (-1)\cdot 0\cdot 0\cdot 0\cdot (-1)=0 $ .

In the fourth test case, choosing $ a_1,a_2,a_3,a_4,a_6 $ is a best choice: $ (-9)\cdot (-7) \cdot (-5)\cdot (-3)\cdot 1=945 $ .

## 样例 #1

### 输入

```
4
5
-1 -2 -3 -4 -5
6
-1 -2 -3 1 2 -1
6
-1 0 0 0 -1 -1
6
-9 -7 -5 -3 -2 1```

### 输出

```
-120
12
0
945```

# 题解

## 作者：_Aoi_ (赞：4)

### 十年OI一场空，不开longlong见祖宗
一开始，我信心满满，写了一个${21}$行的代码，结果：

![](https://cdn.luogu.com.cn/upload/image_hosting/luvo64cz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### 思路
要让${5}$个数乘积最大，在考虑负数的情况下，有这几种情况：

- 最大的${5}$个数乘在一起(不用考虑正负）
- 最小的${2}$个**负数**和最大的${3}$个数乘在一起
- 最小的${4}$个**负数**和最大的${1}$个数乘在一起

综上所述：只要有足够的数量，**负数**的个数必须是偶数

### 注意
- 开$long \ long$
- 排序
- 多组数据

### code
```cpp
#include<bits/stdc++.h>//万能头 
#define ll long long
using namespace std;
ll t,n,a[100010],ans1,ans2,ans3,ans=-1e9;
int main()
{
	cin>>t;//多组数据 
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+n+1);//排序 
		ans1=a[n]*a[n-1]*a[n-2]*a[n-3]*a[n-4];//5个最大数 
		ans2=a[1]*a[2]*a[n]*a[n-1]*a[n-2];//2个最小数+3个最大数 
		ans3=a[1]*a[2]*a[3]*a[4]*a[n];//4个最小数+1个最大数 
		ans=max(ans1,max(ans2,ans3));//取最大 
		cout<<ans<<endl;//输出 
	}
	return 0;//好习惯 
 } 
```


---

## 作者：Tenshi (赞：4)

题解好像没有我的~~毒瘤~~做法。

# 分析
## 做法：暴搜
当然直接搜是不行的，n的范围这么大，稳稳的TLE

那我们可以这样做：

①n≤10的时候，可以直接搜，正确性绝对保证。

②n＞10的时候，我们取数组最小的五个值以及最大的五个值，得到一个新数组，对这个数组进行搜索就可以了。

对②，为什么可以保证正确呢？或者说，为什么能够保证答案在这10个数选出的5个数的乘积之中呢？

假设答案存在于这10个数的“组合之外”，记这样的数之一为x

比如下面12个数：

```
-9 -8 -7 -5 -3 -1 0 1 1 4 5 6 
```


-1,0都是“组合之外”


若x≥0 最大的乘积肯定在最大的五个数中，不会选到x。

若x<0 乘积可以保证为正数且最小的五个数不可能全部被选取（这两点较易得知），若选了x，将x替换为最小的五个数中没被选上的一个，所得答案大于上述的组合，故不会选到x。

正确性得证。

那我们就可以搜了：

```cpp
void dfs(int st,ll res){
    if(st==5){
        ans=max(ans,res);
        return;
    }
    for(int i=1;i<=min(n,10);i++){
        if(vis[i]) continue;

        vis[i]=1;
        dfs(st+1,res*rec[i]);
        vis[i]=0;
    }
}
```

AC code:

```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define SET0(a) memset(a,0,sizeof(a))
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define DWN(i,a,b) for(int i=(a);i>=(b);i--)
typedef long long ll;
#define N 200005
int T;
int a[N];
int n; 
int rec[15];
int vis[15];
ll ans;
void dfs(int st,ll res){
    if(st==5){
        ans=max(ans,res);
        return;
    }
    for(int i=1;i<=min(n,10);i++){
        if(vis[i]) continue;

        vis[i]=1;
        dfs(st+1,res*rec[i]);
        vis[i]=0;
    }
}
int main(){
    cin>>T;
    while (T--)
    {
        cin>>n;
        FOR(i,1,n) cin>>a[i];
        sort(a+1,a+1+n);

        if(n<=10){
            FOR(i,1,n) rec[i]=a[i];
            ans=LLONG_MIN;
            dfs(0,1);
            cout<<ans<<endl;
        }
        else{
            FOR(i,1,5) rec[i]=a[i];
            FOR(i,n-4,n) rec[i-n+10]=a[i];
            ans=LLONG_MIN;
            dfs(0,1);
            cout<<ans<<endl;
        }
    }
    
    return 0;
}
```



---

## 作者：grass8cow (赞：3)

题意简述：给你 $n$ 个整数，让你选 $5$ 个，使它们乘积最大。

考虑枚举选择的负数的个数，设其为 $x$ 。若 $(-1)^x$ 为正，则尽量选绝对值最大的数，否则尽量选绝对值最小的。对每个答案取 $max$ ，便为最后的答案。

复杂度 $O(\sum nlogn)$ 。（要排序）

当然 $O(n)$ 建堆，单次查询 $O(logn)$ ，最后复杂度 $O(\sum n+logn)$ ，显然更优，但比赛时懒得打。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,n,a[100010],n1,n2,b[100010];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);int ss=0;n1=0;n2=0;
		for(int i=1,x;i<=n;i++){scanf("%d",&x);if(x>=0)a[++n1]=x;else b[++n2]=-x;}
		sort(a+1,a+n1+1);sort(b+1,b+n2+1);
		ll ans=-1e18;
		for(int i=0;i<=min(5,n2);i++)if(5-i<=n1)
		{
			ll now=(i&1)?-1:1;
			if(i&1){for(int j=1;j<=5-i;j++)now*=a[j];for(int j=1;j<=i;j++)now*=b[j];}
			else {for(int j=n1;j>=n1-(5-i)+1;j--)now*=a[j];for(int j=n2;j>=n2-i+1;j--)now*=b[j];}
			ans=max(ans,now);
		}
		printf("%lld\n",ans);
	}
	return 0;
 } 
```


---

## 作者：QwQcOrZ (赞：1)

容易想到一个简单的想法：设 $f_{i,j}$ 表示前 $i$ 个数选 $j$ 个的最大值，然后转移

但有负数的话这样做就会假掉，因为负负得正可能会得到更大值

那么可以再记一个 $g_{i,j}$ 表示前 $i$ 个数选 $j$ 个的最小值，就能处理负数的问题

然后转移时处理一下细节就好了

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
const int inf=243000000000000005ll;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
int mn[N][6],mx[N][6],a[N];//mx:最大值,mn:最小值

signed main()
{
	memset(mn,0,sizeof(mn));
	memset(mx,0,sizeof(mx));
	int T=read();
	while (T--)
	{
		int n=read();
		for (int i=1;i<=n;i++) a[i]=read();
		for (int i=0;i<=5;i++)
		for (int j=i+1;j<=5;j++) mn[i][j]=inf,mx[i][j]=-inf;
		for (int i=0;i<=n;i++) mn[i][0]=mx[i][0]=1;
		for (int i=1;i<=n;i++)
		for (int j=1;j<=min(i,5ll);j++)
		{
			mx[i][j]=max(mx[i-1][j],max(mx[i-1][j-1]*a[i],mn[i-1][j-1]*a[i]));
			mn[i][j]=min(mn[i-1][j],min(mx[i-1][j-1]*a[i],mn[i-1][j-1]*a[i]));//从上一个选 j 个的转移过来，或上一个选 j-1 个再选上当前的转移过来，取个最大/最小值即可
		}
		print(mx[n][5]);
	}

	return 0;
}
```

---

## 作者：dead_X (赞：1)

## 前言
好像挺有名一题？

我刚入门的时候做过三个数的乘积最大值/cy
## 题意
求序列中任意五个数乘积的最大值。
## 思路
考虑选出的数中有几个是**负数**，对于每种情况的答案取最大值。

如果答案是负数（即乘积中有奇数个负数），取的数应该是绝对值最小的，反之绝对值应取最大的。

最后只需要分别记录个数并排序即可实现。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[500003],b[500003],cnt1,cnt2;
int main()
{
	int T=read();
	while(T--)
	{
		cnt1=cnt2=0;
		int n=read();
		for(int i=1; i<=n; i++) 
		{
			int x=read();
			if(x>=0) a[++cnt1]=x; else b[++cnt2]=-x;
		}
		sort(a+1,a+cnt1+1),sort(b+1,b+cnt2+1);
		long long ans=-9223372036854775800ll;
		if(cnt1>=5) ans=max(ans,1ll*a[cnt1]*a[cnt1-1]*a[cnt1-2]*a[cnt1-3]*a[cnt1-4]);
		if(cnt1>=4 && cnt2>=1)ans=max(ans,-1ll*a[1]*a[2]*a[3]*a[4]*b[1]);
		if(cnt1>=3 && cnt2>=2)ans=max(ans,1ll*a[cnt1]*a[cnt1-1]*a[cnt1-2]*b[cnt2]*b[cnt2-1]);
		if(cnt1>=2 && cnt2>=3)ans=max(ans,-1ll*a[1]*a[2]*b[1]*b[2]*b[3]);
		if(cnt1>=1 && cnt2>=4)ans=max(ans,1ll*a[cnt1]*b[cnt2]*b[cnt2-1]*b[cnt2-2]*b[cnt2-3]);
		if(cnt2>=5)ans=max(ans,-1ll*b[5]*b[4]*b[1]*b[2]*b[3]);
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：miao5 (赞：0)

**题目大意**

让你从 $n$ 个数中选$5$个数，使他们乘积最大。输出乘积。

**大体思路**

这题注意几点就可以了。

- 给定的 $n$ 个数中会有负数。
- 如果正数数量足够并且要选负数的话，复数个数必须是偶数。
- 搭配时有三种搭配方案：
    - 选绝对值最大的五个正数。
    - 选绝对值最大的两个负数和三个正数。
    - 选绝对值最大的四个负数和一个正数。
    - 在这三种方案中取 $\max$ 就是最终答案。
    
之后就可以愉快的 AC 了~~

---

## 作者：_Harrisonwhl_ (赞：0)

本题的关键知识：负负得正。

首先我们可以对数组进行一下排序，由于我们要找最大的乘积，所以可能是最大的乘积的只有最大的五个数（不予解释）、最小的两个和最大的三个（负负得正）、最小的四个和最大的一个（上一种情况的继续延伸），我们将这些情况算出来，取最大就好了。

另外，本题的初值很重要：本人先将初值设为$0$，WA#1，设为$-1e9$，WA#3，设为$-1e18$,AC。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main()
{
    int t,n;
    long long ans,now;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        sort(a + 1,a + n + 1);
        ans = -1e18;//每次都要设初值
        now = 1;
        for (int i = n;i >= n - 4;i--)//最大的五个
            now *= a[i];
        ans = max(ans,now);
        now = 1;
        for (int i = n;i >= n - 2;i--)//最小的两个和最大的三个
            now *= a[i];
        now *= a[1] * a[2];
        ans = max(ans,now);
        now = 1;
        for (int i = 4;i >= 1;i--)最小的四个和最大的一个
            now *= a[i];
        now *= a[n];
        ans = max(ans,now);
        printf("%lld\n",ans);//输出，记得换行，\n也把本人卡了。
    }
    return 0;
}
```


---

## 作者：CDFLS_mao_zx (赞：0)

居然没有爆搜？？我来写吧。  
题意不说了吧。  
我们考虑不存在正数的情况，显然答案是最大的五个数乘起来。  
为什么，因为你乘起来一定是非正数，所以绝对值最小的五个数乘起来就是答案。  
如果有正数，分两种情况讨论，一是我们得不到正数，我们发现这种情况只会在n=5时出现，为什么？你只需要选奇数个正数，再乘上一些负数就得到正的了，如果只有5个并且有偶数个正数，我们就选不齐，此时5个数乘起来就是答案。第二种情况，我们一定能得到正的答案，因为答案最大即绝对值最大，所以只用考虑正数和负数选绝对值最大的5个即可，否则一定有更优的方案，我们按绝对值排序后直接爆搜就可以了。  
复杂度：$C_{10}^5*t*10=5e7$左右，因为dfs，所以要乘上枚举的10，加上排序的复杂度，没了。  
```
#include<bits/stdc++.h>
#define int long long//不开longlong见祖宗。
using namespace std;
int i,j,k,m,n,s,t;
const int N=1e5+10;
int a[N],vis[11],t1[N],t2[N],ans,num[11];
int abbs(int a)
{
	return a<0?-a:a;//自带的abs似乎处理不了longlong。
}
bool cmp(int x,int y)
{
	return abbs(x)>abbs(y);
} 
void dfs(int x,int nt)
{
	if(nt==6)
	{
		ans=max(ans,x);
		return;
	}
	for(int i=1;i<=s;i++)
	{
		if(vis[i])//标记已选
		continue;
		vis[i]=1;
		dfs(x*num[i],nt+1);
		vis[i]=0;//撤掉标记
	}
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		ans=-1e18;
		scanf("%lld",&n);
		for(i=1;i<=n;i++)	
		scanf("%lld",&a[i]);
		sort(a+1,a+n+1,cmp);
		int js1=0,js2=0;
		for(i=1;i<=n;i++)
		{
			if(js1<5&&a[i]>=0)
			t1[++js1]=a[i];
			if(js2<5&&a[i]<=0)
			t2[++js2]=a[i];
		}
        //统计个数
		if(js1==0)
		{
			int tmp=1;
			tmp=a[n]*a[n-1]*a[n-2]*a[n-3]*a[n-4];
			cout<<tmp<<endl;
			continue;
		}
		int now=0;
		for(i=1;i<=js1;i++)
		num[++now]=t1[i];
		for(i=js1+1;i<=js1+js2;i++)
		num[++now]=t2[i-js1];
		s=now;
		dfs(1,1);
		cout<<ans<<endl;
	}
	return 0;
}
```



---

## 作者：chenxia25 (赞：0)

> ### [洛谷题目页面传送门]( https://www.luogu.com.cn/problem/CF1406B ) & [CF 题目页面传送门]( https://codeforces.com/contest/1406/problem/B )
>
> 给定 $n$ 个整数（可正可负可零），求其中 $5$ 个数的乘积的最大值。本题多测。
>
> $n\in\left[5,10^5\right],\sum n\leq 2\times10^5$。

这个就分个两种情况吧，有 $0$ 和无 $0$。

有 $0$ 的话就是 $0$ 了。

无 $0$ 的话就枚举正数个数，然后排个序贪个心就切了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
const int inf=0x3f3f3f3f3f3f3f3f;
int n;
void mian(){
	cin>>n;
	vector<int> po,ne;
	int ans=-inf;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(x>0)po.pb(x);
		if(x==0)ans=0;
		if(x<0)ne.pb(x);
	}
	sort(po.begin(),po.end(),greater<int>());
	sort(ne.begin(),ne.end());
	for(int i=0;i<=5;i++){
		if(i<=po.size()&&5-i<=ne.size()){
			int res=1;
			if(5-i&1){
				for(int j=(int)(po.size())-1;j>=(int)(po.size())-i;j--)res*=po[j];
				for(int k=(int)(ne.size())-1;k>=(int)(ne.size())-(5-i);k--)res*=ne[k];
			}
			else{
				for(int j=0;j<i;j++)res*=po[j];
				for(int k=0;k<5-i;k++)res*=ne[k];
			}
			ans=max(ans,res);
		}
	}
	cout<<ans<<"\n";
}
signed main(){
	int testnum=1;
	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

## 作者：KSToki (赞：0)

作为 CF 的 B，别想那么复杂！！~~比如我开始就想复杂了~~

题目大意是给你 $n$ 个数，从中选出 $5$ 个数，使得这 $5$ 个数的积最大。

对负数的数量分类讨论即可，如果我们将要选择奇数个负数，则选出绝对值最小的 $5$ 个数（这时肯定保证有 $0$ 就选了）；如果选出偶数个负数，则选出绝对值最大的 $5$ 个数。~~因为我懒~~用 sort 和 lower_bound，时间复杂度为 $O(nlogn)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100001];
long long ans;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(register int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        int pos=lower_bound(a+1,a+n+1,0)-a-1;
        ans=-0x7ffffffffffffff;//初始化要大！别写0x7fffffff
        for(register int i=0;i<=min(5,pos);++i)
        {
            if(n-pos<5-i)
                continue;
            long long sum=1;
            if(i&1)
                for(register int j=pos-i+1;j<=pos-i+5;++j)
                    sum*=a[j];
            else
            {
                for(register int j=1;j<=i;++j)
                    sum*=a[j];
                for(register int j=n;j>n-5+i;--j)
                {
                    if(j<=pos)
                    {
                        sum=-0x7ffffffffffffff;
                        break;
                    }
                    sum*=a[j];
                }
            }
            ans=max(ans,sum);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：Remake_ (赞：0)

依据贪心的思路，我们理应选择$5$个最大的数并对其作乘积。

但是我们发现，负负得正，最小的数也有可能在这$5$个数之列。

但是负负得正也是有条件的，只有这五个数中有偶数个负数时才是正数。

所以这五个数中显然只可能有$0,2,4$个负数，另外需要注意的一点是，取负数也需要尽量取绝对值最大的负数，所以我们直接从最小值开始取即可，所有的可能情况为：

* $1,$取五个最大的数

* $2,$取三个最大的数和两个最小的数

* $3,$取最大的数和四个最小的数

这些情况分别对应取$0,2,4$个负数。

至此，本题就做完了，需要注意的一点是：数组无序，需要先将其```
sort```成升序。

代码短到离谱：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long T, a;
long long b[500005];
int main()
{
    cin >> T;
    while (T--)
    {
        cin >> a;
        for (int i = 1; i <= a; i++)
            cin>>b[i];
        sort(b + 1, b + a + 1);
        cout << max(max(b[1] * b[2] * b[3] * b[4] * b[a], b[1] * b[2] * b[a] * b[a - 1] * b[a - 2]), b[a] * b[a - 1] * b[a - 2] * b[a - 3] * b[a - 4]) << endl;
    }
}
```


---

## 作者：smallfang (赞：0)

简述题意：给定 $n$ 个数、让你找 $5$ 个数，让它们的积最大。

我们按绝对值从大到小排个序，选前 $5$ 个，如果当前的值小于 $0$ ，那么我们从第 $6$ 个数到第 $n$ 个数。依次枚举，查看如果将该数替换到前面的 $5$ 个数里是否会产生最大的值。 **注意！ $0$ 是大于负数的 **

另外，如果前 $5$ 个数里、 $5$ 个数都是负数的话，对于后面（ $6-N$ 中）出现负数的情况，是不能替换任何数的。但是当前面 $5$ 个数、负数个数少于 $3$ 个的话，是可以将一个负数替换调一个正数。

例如：
$-9$  $3$  $3$  $3$  $3$  $2$  $-1$

我们可以将 $-1$ 替换 $3$
也可以将 $2$ 替换 $-9$

Code:
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

const int N = 1e5 + 5;

int a[N], n, m, res = 0;

bool cmp(int a, int b)
{
	if (abs(a) == abs(b))
	{
		return a < b;
	} 	
	return abs(a) > abs(b);
}

bool cmp2(int a, int b)
{
	return abs(a) < abs(b);
}

int main()
{
    int t;
    ios::sync_with_stdio(false);
    cin >> t;
    while (t -- )
    {
    	cin >> n;
    	memset(a, 0, sizeof(a));
    	bool flag = false;
    	for (int i = 1; i <= n; i ++ )
    	{
    		cin >> a[i];
    		if (a[i] > 0)
    		{
    			flag = true;
    		}
    	}
    	if (flag == false || n == 5)
    	{
    		sort(a + 1, a + 1 + n, cmp2);
    		long long k = 1;
    		for (int i = 1; i <= 5; i ++ )
    		{
    			k *= a[i];
    		}
    		cout << k << endl;
    		continue;
    	}
    	sort(a + 1, a + 1 + n, cmp);
    	long long k = 1, rk;
    	int cnt = 0;
    	for (int i = 1; i <= 5; i ++ )
    	{
    		k *= a[i];
    		cnt += (a[i] < 0);
    	}
    	rk = k;
    	if (k < 0)
    	{
    		long long as = 0, b = 0, cans = 0;
    		for (int j = 5; j >= 1; j -- )
    		{
    			if (as == 0 && a[j] > 0)
    			{
    				as = a[j];
    			}
    			if (b == 0 && a[j] < 0)
    			{
    				b = a[j];
    			}
    		}
    		for (int i = 6; i <= n; i ++ )
    		{
    			cans = rk;
    			if (a[i] == 0)
    			{
    				cans = 0;
    				k = max(cans, k);
    				continue;
    			}
    			if (cnt <= 3)
    			{
    				if (a[i] < 0)
    				{
    					cans /= as;
    				}
    				else
    				{
    					cans /= b;
    				}
    				cans *= a[i];
    			}
    			else
    			{
    				if (a[i] > 0)
    				{
    					cans /= b;
    					cans *= a[i];
    				}
    			}
    			k = max(cans, k);
			}
    	}
    	cout << k << endl;
    }
    return 0;
}
```

$UPD:$ 积的最大值。

---

