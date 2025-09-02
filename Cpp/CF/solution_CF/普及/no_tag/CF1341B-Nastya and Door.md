# Nastya and Door

## 题目描述

On February 14 Denis decided to give Valentine to Nastya and did not come up with anything better than to draw a huge red heart on the door of the length $ k $ ( $ k \ge 3 $ ). Nastya was very confused by this present, so she decided to break the door, throwing it on the mountains.

Mountains are described by a sequence of heights $ a_1, a_2,       \dots, a_n $ in order from left to right ( $ k \le n $ ). It is guaranteed that neighboring heights are not equal to each other (that is, $ a_i \ne a_{i+1} $ for all $ i $ from $ 1 $ to $ n-1 $ ).

Peaks of mountains on the segment $ [l,r] $ (from $ l $ to $ r $ ) are called indexes $ i $ such that $ l < i <       r $ , $ a_{i - 1} < a_i $ and $ a_i > a_{i + 1} $ . It is worth noting that the boundary indexes $ l $ and $ r $ for the segment are not peaks. For example, if $ n=8 $ and $ a=[3,1,4,1,5,9,2,6] $ , then the segment $ [1,8] $ has only two peaks (with indexes $ 3 $ and $ 6 $ ), and there are no peaks on the segment $ [3, 6] $ .

To break the door, Nastya throws it to a segment $ [l,l+k-1] $ of consecutive mountains of length $ k $ ( $ 1 \le l \le       n-k+1 $ ). When the door touches the peaks of the mountains, it breaks into two parts, after that these parts will continue to fall in different halves and also break into pieces when touching the peaks of the mountains, and so on. Formally, the number of parts that the door will break into will be equal to $ p+1 $ , where $ p $ is the number of peaks on the segment $ [l,l+k-1] $ .

Nastya wants to break it into as many pieces as possible. Help her choose such a segment of mountains $ [l, l+k-1] $ that the number of peaks on it is maximum. If there are several optimal segments, Nastya wants to find one for which the value $ l $ is minimal.

Formally, you need to choose a segment of mountains $ [l,       l+k-1] $ that has the maximum number of peaks. Among all such segments, you need to find the segment that has the minimum possible value $ l $ .

## 说明/提示

In the first example, you need to select a segment of mountains from $ 2 $ to $ 7 $ . In this segment, the indexes $ 3 $ and $ 6 $ are peaks, so the answer is $ 3 $ (only $ 2 $ peaks, so the door will break into $ 3 $ parts). It is not difficult to notice that the mountain segments $ [1, 6] $ and $ [3, 8] $ are not suitable since they only have a $ 1 $ peak (for the first segment, the $ 6 $ index is not a peak, and for the second segment, the $ 3 $ index is not a peak).

In the second example, you need to select a segment of mountains from $ 2 $ to $ 4 $ . In this segment, the index $ 3 $ is a peak, so the answer is $ 2 $ (only $ 1 $ peak, so the door will break into $ 2 $ parts).

In the third example, you need to select a segment of mountains from $ 1 $ to $ 4 $ . In this segment, the index $ 3 $ is a peak, so the answer is $ 2 $ (only $ 1 $ peak, so the door will break into $ 2 $ parts). You can see that on the segments $ [2, 5] $ , $ [4, 7] $ and $ [5, 8] $ the number of peaks is also $ 1 $ , but these segments have a left border greater than the segment $ [1, 4] $ , so they are not the correct answer.

## 样例 #1

### 输入

```
5
8 6
1 2 4 1 2 4 1 2
5 3
3 2 3 2 1
10 4
4 3 4 3 2 3 2 1 0 1
15 7
3 7 4 8 2 3 4 5 21 2 3 4 2 1 3
7 5
1 2 3 4 5 6 1```

### 输出

```
3 2
2 2
2 1
3 1
2 3```

# 题解

## 作者：tangber (赞：8)

## 思路
用数组存下数据，标记山峰的位置，用前缀和计算山峰的数量，最后暴力枚举，就可以 AC 啦。

注：区间两边的山峰不会增加新的区间，故计算时需将区间向内缩 $1$。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500010;
int t,n,k;
int ans,q;
bool flag[N];//标记峰 
int a[N],feng[N];
signed main()
{
	cin>>t;
	for(int ask=1;ask<=t;ask++)
	{
		cin>>n>>k;
		ans=0;q=0; 
		memset(flag,0,sizeof flag);//多测清空
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=2;i<=n-1;i++) if(a[i-1]<=a[i] and a[i]>=a[i+1]) flag[i]=1;//标记峰 
		for(int i=2;i<=n;i++)feng[i]=feng[i-1]+flag[i];//统计峰 
		for(int i=1;i<=n-k+1;i++)
		{
			int anss=feng[i+k-2]-feng[i]+1;
			if(anss>ans)
			{
				q=i;
				ans=anss;//更新答案 
			}
		}
		cout<<ans<<" "<<q<<endl;//输出答案 
	}
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：2)

## CF1341B Nastya and Door 题解
### 思路

“峰”的定义：当 $a_{i-1} \le a_i \ge a_{i+1}$ 时，位置 $i$ 为“峰”。

我们记录峰的数量，打擂台留峰最多且下标最小的，最后 $+1$ 求被峰隔断的数量。

注意：峰的构成由峰本身和相邻的两个元素构成，缺一不可，所以求区间和时，需向区间内部缩 $1$。

### 代码

```cpp
#include<assert.h> 
#include<ctype.h> 
#include<errno.h> 
#include<float.h> 
#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<wchar.h> 
#include<wctype.h>
#include<algorithm> 
#include<bitset> 
#include<cctype> 
#include<cerrno> 
#include<clocale> 
#include<cmath> 
#include<complex> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<ctime> 
#include<deque> 
#include<exception> 
#include<fstream> 
#include<functional> 
#include<limits> 
#include<list> 
#include<map> 
#include<iomanip> 
#include<ios> 
#include<iosfwd>
#include<iostream> 
#include<istream> 
#include<ostream> 
#include<queue> 
#include<set> 
#include<sstream> 
#include<stack> 
#include<stdexcept> 
#include<streambuf> 
#include<string> 
#include<utility> 
#include<vector> 
#include<cwchar> 
#include<cwctype>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int maxn=2e5+10;
int t,n,k,l,ans;
int a[maxn],x[maxn],sum[maxn];
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		k=read();
		ans=0;
		memset(x,0,sizeof(x));
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
		}
		for(int i=2;i<n;i++)
		{
			if(a[i]>=a[i-1]&&a[i]>=a[i+1])
			{
			    x[i]=1;
			}
		}
		for(int i=1;i<=n;i++)
		{
		    sum[i]=sum[i-1]+x[i];
		}
		for(int i=1;i<=n-k+1;i++)
		{
			int p=sum[i+k-2]-sum[i]+1;
			if(p>ans)
			{
				l=i;
				ans=p;
			} 
		} 
		cout<<ans<<" "<<l<<endl;
	} 
	return 0;
} 

---

## 作者：HEzzz (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1341B)

## 解析

找出里面的山峰，并用数组标记。对于要求长度为 $k$ 的区间中含有峰最多的区间，我们枚举每个区间并提前用前缀和维护区间山峰的数量，这样就可以来 $O(1)$ 判断。

其中这道题有一个细节就是对于一个区间中山峰的数量，我们要区间两端缩小 $1$，因为山峰和山峰旁矮小的山是相互依存的。

## code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=2e5+5,SN=1e3+5,Mod=998244353;  
int T,n,k,a[N],f[N],ans,beg;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);  
	cin>>T;
	while(T--)
	{
		ans=beg=0;
		cin>>n>>k;
		_rep(i,1,n) cin>>a[i],f[i]=0;
		_rep(i,1,n) if(a[i-1]<=a[i]&&a[i]>=a[i+1]) f[i]=1;
		_rep(i,1,n) f[i]+=f[i-1];
		_rep(i,1,n-k+1)
		{
			int cnt=f[i+k-2]-f[i]+1;
			if(cnt>ans) ans=cnt,beg=i;
		}
		cout<<ans<<" "<<beg<<"\n";
	}
	return 0;
}
```

多测要清空的喔。完结撒花。

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1341B)

题目大意：给定一个长为 $n$ 的数组 $a$。如果一个元素 $a_i$ 满足 $a_{i - 1} < a_i > a_{i + 1}$，那么定义这个元素为一个“峰”。现在想要求出，在 $a$ 中长度为 $k$ 的区间里出现的有效的“峰”最多可以把区间分为几个部分。注意：如果一个“峰”在区间的边缘（如选择区间 $[1,5]$，$a_5$ 为“峰”），那么这个“峰”是无效的，不能分割区间。

做法：把所有的“峰”记录下来，并使用前缀和求区间中“峰”的数量。枚举每个长为 $k$ 的区间，求得“峰”数量的最大值，同时记录区间的起始位置。

注意：因为在区间边缘的“峰”是无效的，所以枚举时左右两边要各缩短一格。

最后，因为是求分割的区间数量，所以答案要加一。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200001], k, pre[200001], maxn, idx;
int main(){
	scanf("%d", &t);
	while (t--){
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		a[0] = a[n + 1] = 2147483647;//防止边界被认为是“峰”
      	maxn = 0, idx = 1;
		for (int i = 1; i <= n; i++){
			if (a[i] > a[i + 1] && a[i] > a[i - 1]) pre[i] = pre[i - 1] + 1;
			else pre[i] = pre[i - 1];
		}//求前缀和
		int l = 2, r = k - 1;//前后缩短区间
		while (r < n){
			if (maxn < pre[r] - pre[l - 1]) maxn = pre[r] - pre[l - 1], idx = l - 1;
			l++, r++;
		}//枚举
		printf("%d %d\n", maxn + 1, idx);
	}
	return 0;
}
```

---

## 作者：ZigZagKmp (赞：0)

本文同步发表于我的[cnblog](https://www.cnblogs.com/ZigZagKmp/p/13749280.html)

本场题解见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1340-solution)
## CF1341B
### 题意简述
给定一个长度为 $n$ 的数组$a_i$。定义一个位置 $i$ 是“峰”，当且仅当 $a_{i-1}\le a_i \ge a_{i+1}$。

求长度为 $k$ 的区间中含有“峰”个数最多的区间。

多测，$1\le t\le 10^4,3\le k\le n\le 2\times10^5,0\le a_i\le 10^9,\sum n\le 2\times 10^5$。
### 算法标签
前缀和，模拟
### 算法分析
我们可以预先处理出每个位置是否可能为“峰”，然后取区间长度为 $k$ 的包含“峰”最多的区间，这个可以借助前缀和 $O(1)$ 求出。

注意每个区间的边界位置不能算做“峰”。
### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp>void read(Tp &x){
	x=0;int fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=fh;
}
int n,m;
int a[maxn],b[maxn],s[maxn];
int posl,ans;
signed main(){
	int T;
	read(T);
	while(T--){
		read(n);read(m);
		for(int i=1;i<=n;++i)read(a[i]);
		for(int i=1;i<=n;++i){
			if(i==1||i==n)b[i]=0;
			else{
				if(a[i-1]<=a[i]&&a[i+1]<=a[i])b[i]=1;
				else b[i]=0;
			}
		}
		for(int i=1;i<=n;++i)s[i]=s[i-1]+b[i];
		posl=0,ans=-1;
		for(int l=1;l+m-1<=n;++l){
			int tmp=s[l+m-2]-s[l]+1;
			if(tmp>ans){
				posl=l;ans=tmp;
			}
		}
		printf("%d %d\n",ans,posl);
	}
	return 0;
}
```

---

## 作者：lingfunny (赞：0)

前言：题解区树状数组第一人 ~~好像总的也才1个人~~。
## 题目翻译
有$n$个数$a_1,a_2...a_n$，再给定一个区间长度$k$，请你找出这个区间的左端$l$，使得$(a_l,a_{l+k-1})$中，有最多的“峰”。

其中，“峰”的定义是，如果$a_{i-1} \le a_i\ge a_{i+1}$，那么$a_i$就是一个“峰”。
## 题目分析
注意，这是**闭区间**，即如果$a_l$或$a_{l+k-1}$是“峰”，也不计算在总数里面。

先拆分问题，第一步要做的是找峰，遍历一遍数组即可：
```cpp
//A[]是原始数组
for(int i=1;i<=n;++i)
	if(a[i] >= a[i-1] && a[i]>=a[i+1])
		mountains[i]=true;
```
那么接下来就很简单了，只要从```mountains```的第1个元素一直找到第$n-k$个元素当做左端，然后记录区间和，打标记。
```cpp
for(int i=1;i<=n-k;++i){
	cnt=0;
	for(int j=0;j<k;++j)
		if(mountains[i+j])
			++cnt;
	if(cnt>maxans){
		maxans=cnt;
		ans=i;
	}
}
```
但是，时间复杂度：
$$O(nk)$$
显然是必炸的，那么还有什么可以优化呢？

看到区间和，首先可以打前缀和，$O(n)$预处理，$O(n)$查询答案，这题是离线的，可以放心食用。预估时间复杂度：
$$O(n)$$
这样就可以愉快的敲代码了。

但是，看到$n,k\le 2\times10^5$的我抖了个机灵：
> 这不是标准的$O(nlog_2n)$吗？线段树啊，树状数组啊！

于是默默地打了个树状数组（
## 上代码
```cpp
#include <cstdio>
#include <cstring>

const int maxn = 200005;

int T,n,k,a[maxn],tree[maxn],ans,l;

inline int lowbit(int x){return x&-x;}
inline int read();
void add(int k,int x){
	while(k<=n){
		tree[k]+=x;
		k+=lowbit(k);
	}
}
int ask(int x){
	int res=0;
	while(x>=1){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}

int main(){
	//freopen("file.in","r",stdin);
	T=read();
	while(T--){
		memset(tree,0,sizeof(tree));
		memset(a,0,sizeof(a));
		ans=l=0;
		n=read();k=read();
		for(int i=1;i<=n;++i)a[i]=read();
		for(int i=2;i<n;++i)
		if(a[i]>a[i-1] && a[i]>a[i+1])
		add(i,1);
		for(int i=1;i<=n-k+1;++i){
			int res = ask(i+k-2)-ask(i) + 1;
			if(res > ans){
				l = i;
				ans=res;
			}
		}
		printf("%d %d\n",ans,l);
	}
	return 0;
}

inline int read(){
	int x=0,f=1;
	char ch = getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*f;
}
```

---

## 作者：juicyyou (赞：0)

# CF1341B - Nastya and Door
## 题目大意：
本体一共有 $t$ 组数据，对于每一组数据，给定一个 $n$ 和一个 $k$ 以及一个长度为 $n$ 的数列 $a$ 。如果一个 $i$ 满足 $1 < i < n$ 并且 $a_{i - 1} < a_i$ 同时还满足 $a_i > a_{i + 1}$，那么，我们就称 $a_i$ 是一个 Peaks of mountains ，求出对于所有的 $i \le n - k + 1$，区间 $\left(i,\, i+k-1\right)$ 中 Peaks of mountains 的数量的最大值+1，并且输出一个 $i$ 满足区间 $\left(i,\, i+k-1\right)$ 中 Peaks of mountains 的数量最大。
## 解法：
直接模拟即可。

我们统计一个 Peaks of mountains 的数量的前缀和，然后去枚举每一个长度为 $k$ 的合法的开区间，然后用前缀和查询，最后再枚举一便找到一个解即可。最后不要忘记 +1 啊。

下面是我的Code：
```cpp
/*
This Code Is for Practice
Alforithm: None
Author: LiangJiaWen2007
IEE
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#include<set>
#include<cstdlib>
#include<cctype>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 5e5 + 5;
const ll maxm = 1e3 + 5;
template<class T>
inline T qread(T &IEE){
	register T x = 0, f = 1;
	register char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -f;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return IEE = x * f;
}
ll cnt1, cnt2, t, n, k;
ll f[maxn], a[maxn];
int main(){
	qread(t);
	while(t--){ // 多测
		qread(n);
		qread(k);
		for(int i = 1;i <= n;i++){
			qread(a[i]);
		}
		f[1] = 0;
		for(int i = 2;i < n;i++){ // 前缀和
			if(a[i] > a[i - 1] && a[i] > a[i + 1]){
				f[i] = f[i - 1] + 1;
			} else {
				f[i] = f[i - 1];
			}
		}
		f[n] = f[n - 1];
		cnt2 = cnt1 = 0;
		for(int i = 1;i + k - 1 <= n;i++){ // 求最大值
			cnt1 = max(cnt1, f[i + k - 2] - f[i]);
		}
		for(int i = 1;i + k - 1 <= n;i++){ // 求一个解
			if(f[i + k - 2] - f[i] == cnt1){
				cnt2 = i;
				break;
			}
		}
		cnt1++; // 加1
		cout << cnt1 << " " << cnt2 << endl; // 输出
	}
	return 0;
}
```
上述算法单次复杂度 $\mathcal O(n)$ ，算上多组数据之后，总复杂度即为 $\mathcal O(\sum n)$，可以通过此题。

---

