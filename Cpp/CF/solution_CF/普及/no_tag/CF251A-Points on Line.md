# Points on Line

## 题目描述

Petya很喜欢点。最近，他的妈妈给了他n个位于OX（实数轴）上的点。现在，Petya想知道有多少种不同的方法可以在数轴上选择3个不同点，使3个点中距离最远的两个点的距离不超过d。

注意：三个点的排列顺序是无关紧要的（意思就是说，三个点是相同的，交换顺序也只算1种）。

## 说明/提示

在样例一中，任何挑选方式都是可行的。

在样例二中只有{-3, -2, -1}和{-2, -1, 0}是可行的。

在第三个样例中只有{1, 10, 20}是可行的。

感谢@Spoiler_haiwenhan 提供的翻译

## 样例 #1

### 输入

```
4 3
1 2 3 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 2
-3 -2 -1 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 19
1 10 20 30 50
```

### 输出

```
1
```

# 题解

## 作者：Purple_Circle (赞：3)

首先，看到题面，可以将题面简化为：

对于 $n$ 个数的数列取三个数使得最大数－最小数不大于 $d$。

那么，我们只要枚举从当前节点一直到 $n$ 距离不大于 $d$ 的点。

用左右指针分别指向数段的头和尾。

再通过求组合数得到答案。

Q:为什么要计算组合数？

A:题目告诉我们是共选取三个数，在我们已经确定了起点的情况下，是从  $[l,r]$ 区间任取两个数，方案数即为 $ C_{l-r} ^2 $。

时间复杂度 $O(n\log_2 n)$。

$\text{Code}$

------------

求 $ C_{x}^2$

```cpp
long long C(long long x){
	if(x%2) return ((x-1)/2)*x;
	return (x/2)*(x-1);
}
```

枚举双指针

```cpp
for(int l=1,r=1;l<=n;l++){
   while(r+1<=n&&a[r+1]-a[l]<=d)r++;
   ans+=C(r-l);
}
```

全代码

```cpp
#include<bits/stdc++.h>
#define rd read()
using namespace std;

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}//快读，忽略即可

long long C(long long x){
	if(x%2) return ((x-1)/2)*x;
	return (x/2)*(x-1);
}

const int N=1e5+10;
int a[N],n,d;
long long ans;
int main(){
	n=rd,d=rd;
	for(int i=1;i<=n;i++){
		a[i]=rd;
	}
	sort(a+1,a+n+1);//因为后面双指针要保证后面大于前面的点
	for(int l=1,r=1;l<=n;l++){
		while(r+1<=n&&a[r+1]-a[l]<=d){//穷举距离不大于d的点
			r++;
		}
		ans+=C(r-l);
	}
	cout<<ans;
}

```



---

## 作者：Leap_Frog (赞：3)

### PS.
首先，一看到这题，我就想到了一个方法。  
然后一看题解区，发现全都是二分、upper_bound的。  
补充一个其他的做法。  

### Problem.
给定数轴上的一些点。  
求有多少种方案，使得这些点中距离最远的两个点距离不大于$d$

### Solution.
首先，很显然，我们可以枚举每个起始点。  
然后找到所有距离这个起始点不大于$d$的点。  
就可以通过求组合数求出以这个点为起始点的方案数。  
然后找到所有可行点，可以使用排序之后找到距离起始点最远但是不超过$d$的那个点。  

接下来重点讲一下如何找出距离起始点最远的符合条件点（设其为$a_i$。  
首先，我们遍历起始点的时候一般都是从小到大遍历的。  
那么也就是说，如果一个点在第$i$个点和第$i+1$个点右边，  
且满足到第$i$个点的距离不超过$d$，则它到第$i+1$个点的距离也不超过$d$。  
所以肯定仍然满足，所以当起始点从$i$到第$i+1$时，那个$a_i$肯定不会向左移动。  

也就是说，在$i$向右时，$a_i$肯定不会向左移动。  
那么就很显然了，可以使用一个双指针，$l$记录$i$，$r$记录$a_i$。  
由于$l$与$r$都只会向右移动，所以这里复杂度是$O(N)$，比楼上楼下的稍微优越一点。  

然后，第$i$个点的方案数是可以在$i+1$~$a_i$之间任意选两个点。  
方案数为$C_{a_i-i}^2=\frac{(a_i-i)(a_i-i-1)}{2}$  

最后提醒，不要忘了开long long。具体实现见代码注释。  

### Coding.
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,x[100005];long long ans;
inline long long C2(long long x) {return x%2?(x-1)/2*x:x/2*(x-1);}//求组合数
int main()
{
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++) scanf("%d",x+i);//读入，不解释
	sort(x+1,x+n+1),ans=0;//显然要排序
	for(int l=1,r=1;l<=n;l++)//l与r即为双指针
	{
		while(r+1<=n&&x[r+1]-x[l]<=d) r++;//r向右找到a_l
		ans=ans+C2(r-l);//ans加上第l个点的方案数
	}
	return printf("%lld\n",ans),0;//返回
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：1)

## 题意简述

有一个长度为 $n$ 的序列 $\{a_i\}$，需要在这之中选出 $3$ 个数，使最大数 - 最小数不超过一个给定的整数 $d$，问有几种选法？

**数据保证 $\{a_i\}$ 按升序排列。**

## 开始解题！

比较一眼的双指针。

首先注意到对于一个区间 $[l, r]$，其最小值为 $a_l$，最大值为 $a_r$。

我们知道，对于一个区间 $[l, r]$，$a_r - a_l \le d$，并且我们能够知道 $l$，那么该区间对答案的贡献可以快速求出，即为 $C _ {r - l} ^ {2}$。也就是除了 $a_l$ 外的 $r - l + 1 - 1 = r - l$ 个元素中任意选取两个，都是符合条件的一种选法。故贡献为 $C _ {r - l} ^ {2}$。

而 $C _ {r - l} ^ {2}$ 可以高效求出，即 $C _ {r - l} ^ {2} = \frac{(r - l) \times (r - l - 1)}{2}$，而 $l, r$ 可以用双指针维护。

最后注意在实现上的一些细节，比如当 $r - l + 1 \ge 3$ 时该区间才是合法的。

做完了。

时间复杂度 $O(n)$。

code : 

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define endl "\n"

namespace fastio {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
	
	const ll getc() {
	    return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
	}
	
	const ll read() {
		ll x = 0, f = 1;
		
		char ch = getc();
		
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -1; ch = getc();
		}
		
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
		}
		
		return x * f;
	}
	
	const void write(ll x) {
		if (x < 0) {
			putchar('-'), x = -x;
		}
		
	    ll sta[35], top = 0;
	    
	    do {
	        sta[top++] = x % 10, x /= 10;
	    } while (x);
	    
	    while (top) putchar(sta[--top] + 48);
	}
}

#define read fastio::read
#define write fastio::write

using namespace std;

ll n = read(), d = read(), a[114514], ans = 0;

int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(0), cout.tie(0);

	for (ll i = 1; i <= n; i++) a[i] = read();

	for (ll l = 1, r = 1; l <= n; l++) {
		while (r + 1 <= n && a[r + 1] - a[l] <= d) r ++;

		if (r - l + 1 >= 3) {
			ans += (r - l) * (r - l - 1) / 2;
		}
	}

	write(ans);

	return 0;
}
```

[AC record](https://codeforces.com/contest/251/submission/297735311)

---

## 作者：hjyowl (赞：1)

### 题目大意

给定一条水平线上的 $n$ 个点的坐标，第 $i$ 个点的坐标是 $d_i$，要求选出 $3$ 个点，使得他们当中最远的两个点不超过 $m$,保证 $d$ 是有从小到大有序的。

### 暴力思路

枚举 $3$ 个点，如果最远的距离不超过 $m$，答案加一。

然而时间复杂度 $O(n^3)$，必定超时。

### 稍加优化

发现可以只枚举 $2$ 个点 $i$，$j$。首先得满足两个点之间的距离小于 $m$（这里假设 $d_i\le d_j$ )，接下来二分最后一个小于等于 $d_i+m$ 的 $k$，然后有 $k-j$ 个点符合条件，然后答案加上 $k-j$ 即可。

现在时间复杂度 $O(n^2 \log n)$，快了一点但是还是超时。

### 最终正解

发现只需要枚举出来一个点 $i$，同样二分出小于等于 $d_i+m$ 的点数有多少（和上面的稍加优化里面的求法一样），假设点数为 $k$，那么根据组合原理，发现其有 $C_k^2$ 种方案，也就是 $k \times (k-1) \div 2$，然后答案加上这么多种方案就可以了。

时间复杂度 $O(n \log n)$，时间复杂度在 $n \le 10^5$ 时能够通过。

对于为什么是 $C_k^2$，是因为选出来的顺序不重要，比如说 $1,5$ 和 $5,1$ 本质上是同一种方案。


### 代码实现

实现非常简单。

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 100010;
long long n,m;
long long a[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for (long long i = 1; i <= n; i ++ ){
		cin >> a[i];
	}
  //此处无需排序，因为题目保证了有序
	long long res = 0;
	for (long long i = 1; i <= n; i ++ ){
		long long t = upper_bound(a + 1,a + 1 + n,a[i] + m) - a - 1;//可以直接用upper_bound求出第一个大于a[i]+m的数然后再减一就是最后一个小于等于a[i]+m的
        if (t == n + 1){//如果没有，结束，防止答案错误
            continue;
        }
		long long c = t - i;//满足条件的点数
		res += c * (c - 1) / 2;	//根据公式C(k,2)计算
	}
	cout << res;
	return 0;
}
```

---

## 作者：zyn_ (赞：1)

# CF251A Points on Line

## 题面大意

按升序给出 $n$ 个整数 $x_i$，求三元组 $(i,j,k)$ 的数量（其中 $1\le i\lt j\lt k\le n$），使 $x_i,x_j,x_k$ 中任意两数的差的绝对值小于或等于 $d$。$1\le n\le 10^5$，$-10^9\le a_i\le 10^9$，$1\le d\le 10^9$。

## 分析题目

不难注意到，只需 $x_k-x_i\le d$，$(i,j,k)$ 即满足要求，因为我们假设 $i$ 最小，$k$ 最大，而 $x_i$ 升序给出。

如果直接枚举 $i$ 和 $k$，时间复杂度 $O(n^2)$，会超时。考虑优化。

令 $a_i$ 为最大的 $p$，使 $x_p\le x_i+d$。

那么，对于每个 $i$，$k$ 可取 $i+2$ 到 $a_i$ 的所有整数，$j$ 可取 $i+1$ 到 $k-1$ 的所有整数。

故共有 $\sum_{k=i+2}^{a_i}\sum_{j=i+1}^{k-1}1=\frac{(a_i-i)(a_i-i-1)}{2}$ 个三元组。此时，枚举 $i$ 即可。

所以最后的问题就是如何求 $a_i$。

## 求 $a_i$

看看 $a_i$ 的定义：使 $x_p\le x_i+d$ 的最小的 $p$ 的值。

由于 $x_i$ 升序给出，不难发现 $a_i$ 也单调递增。

于是可以用尺取法求出 $a_i$。

在实现代码时，你会惊奇的发现，根本不需要用数组存 $a_i$，因为每个 $a_i$ 都只被用了一次。

时间复杂度：$O(n)$。

## AC code

```cpp
#include<iostream>
using namespace std;
long long n,d,x[100009],ans,a[100009],p;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>d;
	for(int i=1;i<=n;++i)cin>>x[i];
	p=n;
	for(int i=n;i>=1;--i){
		while(x[i]+d<x[p])--p;  
		//上面的循环保证循环结束时p满足x[p]<=x[i]+d且最大
		//此时的p就是当前i对应的a[i]的值
		ans+=((p-i)*(p-i-1)>>1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：EnofTeiPeople (赞：1)

将点排序后，三点中的最远点就是编号最小的点和编号最大的点。

考虑枚举最大点，那么最小点的取值具有单调性，使用尺取法，可以做到线性。

知道了最小点的最小取值 $l$，那么其他两个点（包括最小点）一定在区间 $[l,r-1]$ 之间，答案就是 $r-l\choose2$.

### AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
template<typename T>
void read(T &s){
	s=0;bool flag=false;char c=getchar();
	while(c!='-' && (c<'0' || c>'9')) c=getchar();
	if(c=='-') flag=true,c=getchar();
	while(c>='0' && c<='9') s=s*10+c-'0',c=getchar();
	s=flag?-s:s;return;
}
template<typename T,typename..._Ts>
void read(T&x,_Ts&...y){
	read(x),read(y...);
}
int n,d,a[N];
ll ans;
inline void adans(ll d)
{if(d>1)ans+=d*(d-1)>>1;}
int main(){
	read(n,d);int i,l,r;
	for(i=1;i<=n;++i)read(a[i]);
	sort(a+1,a+n+1);
	for(l=r=1;r<=n;++r){
		while(l<n&&a[r]-a[l]>d)++l;
		adans(r-l);
	}cout<<ans<<endl;
	return 0;
}
```

---

## 作者：皮卡丘最萌 (赞：1)

由于这道题目$n<=100000$，所以我们考虑使用二分。

假设当前的数为$a[i]$，那么我们就可以在$a[i+1]$~$a[n]$之间找出一个**最大且与$a[i]$距离不超过$d$的数**，记为$a[j]$。

接下来求出$j-i$的值，表示这两个数之间的数的个数，**不包括$a[i]$但包括$a[j]$**，记为$p$。

求出$p$的值后，我们就可以求出方案数$p*(p-1)/2$并且累加。

这个算法的时间复杂度为$O(n logn)$，不会超时。

注意这道题目最后的累加和可能会很大，要用$int64/longlong$

代码：
```pascal
var x,ans:int64; 
n,m,i,t,w,mid,qwq:longint;
a:array[0..100001] of longint;
begin
readln(n,m);
for i:=1 to n do read(a[i]);
for i:=1 to n do
  begin
  t:=i+1; w:=n;        //确定查找范围
  qwq:=0; x:=a[i];
  while t<=w do
    begin
    mid:=(t+w) div 2;
    if a[mid]-x<=m then    //判断是否可行
      begin qwq:=mid; t:=mid+1; end   
                     //如果可以，则记录最优值
    else w:=mid-1;
    end;
  x:=qwq-i;           //求出距离
  if x>1 then inc(ans,(x*(x-1))>>1);   //累加方案数
  end;
writeln(ans);
end.

```


---

## 作者：haiwenhan (赞：1)

虽然这道题没人做，因为都在CF上做了

但我还是要发题解

题目的意思就是让你在n个数里找三个数三个数的组合方式，使三个数中最小的一个和最大的一个差小于等于d，求有多少种组合方式。

其实针对三个数 a[i] a[j] a[k] (i<j<k，a[i]<a[j]<a[k])，要满足a[k]-a[i]<=d就行了，所以针对每个i我们可以进行upper_bound( )寻找第一个比它加d大的数，统计一下，当k=i+1时，没有组合方式，当k=i+1时，有1种，当k=i+1时，有1+2种，依此类推。

不说了看代码。



------------
（分割菌）

------------



```cpp
#include<iostream>
#include<algorithm>//upper_bound()的头文件
using namespace std;
int n,d;
//要开long long不然会炸
long long x[100005];
long long ans;//答案
long long f[100005];//方便计算，种数找规律的结果
int main()
{
	int i,j;
	cin>>n>>d;
	for(i=0;i<n;i++)
	{
		cin>>x[i];
	}
    //输入不说了
	for(i=1;i<n;i++)//因为只有n个数，所以只用找规律到n
	{
		f[i]=f[i-1]+i;//找规律大法
	}
	ans=0;
	for(i=0;i<n;i++)
	{
		j=upper_bound(x+i,x+n,x[i]+d)-x;//口爱的upper_bound()返回值是iterator
		if(j==n)
		{
			j=n-1;//这是当所有数都小于等于a[i]+d时，j就是最后一个数的下标
		}else
		{
			j--;//当然upper找到的数是比a[i]+d大的第一个，所以要j--
		}
		ans+=f[j-i-1];//j-i-1就是i到j之间有多少个数，然后找规律数组就派上用场了，不预处理可能会TLE
	}
	cout<<ans;//输出ans
	return 0;
}

```

---

## 作者：Peiyuan (赞：1)

[题目通道](https://www.luogu.com.cn/problem/CF251A)

## 思路

相信很多人看到这道题，很快就会有一个朴实无华的暴力做法：用三个变量 $i,j,k$ 分别枚举线段上的三个点，再挑选符合条件的情况进行累加。但是很明显，$10^5\times10^5\times10^5$ 的时间复杂度肯定会超时。怎么办呢？这时，我们可以运用一个类似于 __尺取法__ 的方法。

我们可以定义两个指针，$i$ 和 $j$，然后在 $i$ 和 $j$ 之间选取任意两个端点，这里可以用 $C_{j-i}^2$ 快速求解方案数。其中，$C_{j-i}^2=\dfrac{(j-i)(j-i-1)}{2}$。具体实现看注释。

最后，还是鲁迅的那句话：“十年 OI 一场空，不开 ```long long``` 见祖宗”
。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,d,ans,a[100005],cnt;
int main(){
	cin>>n>>d;
	for(ll i=1; i<=n; i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1); //保证a数轴上的端点有序，方便处理 
	ll j=1; //右指针 
	for(ll i=1; i<=n; i++){ //遍历左指针 
		while(a[j+1]-a[i]<=d&&j+1<=n) j++; //满足条件间距大于d时右指针不断自增 
		ans+=(j-i)*(j-i-1)/2; //相当于C(j-i,2)，无序地从i,j指间选择两个，累加总方案数 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ggc123 (赞：0)

## 思路
### 1.暴力 $ O\left ( n^{3} \right ) $

暴力枚举 $3$ 个数，符合要求就将答案加 $1$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,d,a[100005],ans=0;
signed main(){
	cin.tie(0),cout.tie(0);
	cin>>n>>d;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(a[k]-a[i]<=d)
					ans++;
	
	cout<<ans<<"\n";
	return 0;
}
```
恭喜！[TLE](https://codeforces.com/problemset/submission/251/278520986)！

### 2.正解 $O \left ( n\log_{}{n}  \right ) $

- 枚举最小的数。
- 我们需要找出最大的合法的数，给定出界限，为了不超时，我们选择二分查找。
- 因为我们已经找出了最大的合法的数，所以只要小于这个数随机选两个数就可以算是一种结果，这里运用排列组合求出答案。
  
设最小的数的位置为 $l$，最大的数的位置为 $r$。所以 `r=(upper_bound(a+l,a+1+n,a[l]+d)-a-1)`，因此当前的合法选择有 $C_{r-l}^{2} $ 种方案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,d,a[100005],ans=0;
int C(int x){//组合数
	return (x*(x-1))/2;
}
signed main(){
	cin.tie(0),cout.tie(0);
	cin>>n>>d;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<=n;i++){
		int r=(upper_bound(a+i,a+1+n,a[i]+d)-a-1);
		ans+=C(r-i);
	}
	cout<<ans<<"\n";
	return 0;
}
```

[AC 记录](https://codeforces.com/problemset/submission/251/278520758)

---

## 作者：Phoenix114514 (赞：0)

# CF251A Points on Line
## 思路
这道题不用二分，直接枚举即可。

设要枚举区间的起点为 $l$，终点为 $r$。枚举 $l$ 从 1 到 $n$，$r$ 直到 $A_r-A_l$。在 $[l,r]$ 区间的答案数为

$$
\large{\frac{(r-l) \times(r-l-1)}{2}}
$$

然后对所有符合要求的区间 $[l,r]$ 的答案求和。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mxn=1e5+5;
int a[mxn],n,d,ans;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>n>>d;
    for (int i=1;i<=n;i++)cin>>a[i];
    for(int l=1,r=1;l<=n;l++){
        while(r+1<=n&&a[r+1]-a[l]<=d)r++;
        ans+=(r-l)*(r-l-1)/2;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路
设这任取的三个点的横坐标分别为 $a,b,c$，且 $a < b < c$。则我们需要保证 $c - a \le d$。

在确定点 $a,c$ 后，点 $b$ 就可以在 $(a,c)$ 范围内任取了。所以关键是找到合法的点 $a,c$。

考虑确定点 $a$ 时点 $c$ 应该如何取。显然，应该从 $a$ 开始，依次往后枚举点并更新答案，直到不满足 $c - a \le d$ 的条件为止。

那么如果不满足条件了，怎么办呢？因为 $a$ 和 $c$ 太远了，所以应该让 $a$ 向前枚举，直到满足条件。

综合上面的方法，我们发现，其实只要打一个双指针即可。那么确定一个点 $a$ 后，合法的选择点应该有 $C _ {c - a} ^ 2$ 个。

最后，记得开 `long long`。将和累加即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr int N = 1e5 + 1;
int n,d,x[N];
ll ans = 0;

ll C(ll x)
{
	if(x & 1)
        return ((x - 1) >> 1) * x;
	return (x >> 1) * (x - 1);
}

signed main()
{
    register int i,j;
    scanf("%d%d",&n,&d);
    for(i = 0;i < n;i++)
        scanf("%d",&x[i]);
    for(i = 0,j = 0;i < n;i++)
    {
        while(j + 1 < n && x[j+1] - x[i] <= d)
            j++;
        ans += C(j-i);
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Fur_Zes (赞：0)

先看题，是要你在一个长为 $n$ 的数列 $a$ 中任取三个数 $a_x,a_y,a_z(1\le x<y<z\le n)$ 并在这三个数中任意取两个数使他们的差值 $\le d$。

根据题目 ```保证坐标按绝对升序输入```，易知我们只需要保证 $a_z-a_x\le d$ 即可。

根据这一条性质，我们能很容易想到枚举 $x$，并且从 $x$ 开始往后面找到刚好使得 $a_z-a_x>d$ 的 $z$，这时表示在数列 $a_x\sim a_z$ 这一段任取三个数都满足题意。这里要注意的是 $z-x\le2$。

这个方法的正确性证明是显然的：

因为保证坐标按绝对升序输入，如果 $a_i\sim a_j$ 满足题意且 $a_i\sim a_{j+1}$ 也同时满足题意，那么后者产生的方案数一定比前者多。

另外要注意的是每次枚举完 $z$ 之后执行下一次循环并不需要重新把 $z$ 设为 $x+1$，原因同上面证明，否则时间复杂度会退化到 $O(n^2)$。

对于计算方案数，我们用公式 $C^n_m=n\times(n-1)\div m$ 代表在 $n$ 个数中取 $m$ 个数，并且在排序之后不会出现相同的排列。显然符合题意，则我们取 $n=z-x,m=2$。

为什么 $m\ne3$？因为我们是确定了 $x$ 去找能产生最大方案数的 $z$，所以此时只要在 $a_{x+1}\sim a_z$ 中选取 $2$ 个数即为 $1$ 种方案。

tips：十年OI一场空，不开 long long 见祖宗！

最后时间复杂度 $O(n)$，因为下面程序中的 $r$ 最多会将所有 $n$ 个数扫一遍，在 $O(n)$ 的 for 的基础上多了一个可以忽略不计的常数而已。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,d,a[1000005],cnt;
long long C(long long n,long long m)
{
	return n*(n-1)/m;
}
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	long long r=1;
	for(long long l=1;l<=n;l++)
	{
		while(a[r+1]-a[l]<=d&&r+1<=n) r++;
		cnt+=C(r-l,2);
	}
	cout<<cnt;
	return 0;
}
```

---

