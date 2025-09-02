# Counting Kangaroos is Fun

## 题目描述

There are $ n $ kangaroos with pockets. Each kangaroo has a size (integer number). A kangaroo can go into another kangaroo's pocket if and only if the size of kangaroo who hold the kangaroo is at least twice as large as the size of kangaroo who is held.

Each kangaroo can hold at most one kangaroo, and the kangaroo who is held by another kangaroo cannot hold any kangaroos.

The kangaroo who is held by another kangaroo cannot be visible from outside. Please, find a plan of holding kangaroos with the minimal number of kangaroos who is visible.

## 样例 #1

### 输入

```
8
2
5
7
6
9
8
4
2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
8
9
1
6
2
6
5
8
3
```

### 输出

```
5
```

# 题解

## 作者：Jr_Zlw (赞：3)

## CF372A 数袋鼠很有趣 题解

### STEP1：理解题目

~~(CF的题真让人搞不懂）~~

翻译用了非常严谨的语言精确的描述了题目要求的意思（然而蒟蒻看不太懂，我太菜了），所以我撇开360难看的翻译读了一遍题，还真挺有意思的（啊哈？

题目讲的是（~~一个无聊的人数袋鼠~~）有$n$只袋鼠，它们有袋子。

袋子的大小与它们自身的大小成正比(自身大小=$self$，袋子大小=$bag$)$\frac{self}{bag}=\frac{2}{1}$

它们的袋子可以装下比袋子小的其它袋鼠，（参考俄罗斯套娃）。

但每一只袋鼠都只能装一只袋鼠在袋子里。

而且袋子里的袋鼠不能装其它袋鼠（可以想象为一个只允许套一层的俄罗斯套娃）。

现在想让我们求最多能让多少只袋鼠在外面（即宁需要把更多的袋鼠塞进别人的袋子里~~谔谔~~）

（如果宁逻辑思维比较强建议看前台大佬的翻译）

### STEP2：如何实现

我们知道想要匹配更多的袋鼠，就应该尽可能的把更大的袋鼠塞进更小的袋子里（即使ai尽可能大而aj尽可能小）

这里我想到的是类似归并中一个子段的排序，使一个指针从中间开始搜，另一个从末尾开始搜。

因为我们把一只袋鼠塞到另一个袋鼠里这两只袋鼠都会废掉，所以也就是说最少还是会有$\frac{n}{2}$ 个组合。

所以从中间搜可以实现无错（因为最优的情况也就是$\frac{n}{2}$ ，搜索时也肯定找的是最优解（因为排过序），所以无论如何这种搜索都能找出答案。）

在这样的条件下从中间搜索无疑是个很好的选择，只要保持右指针在右半段而左指针在左半段且指针均不越界即可。

### STEP3：遍历过程

此处方便还在晕圈中的童鞋理解：

下面上图：

![遍历过程图](https://cdn.luogu.com.cn/upload/image_hosting/qk9f3m9g.png?x-oss-process=image)

### STEP4：上代码啦

下面直接上代码（受到某篇的启发觉得还是解释代码最管用）

如果宁已经有思路却缺乏实现的可以看看（附解释）：

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;//std命名空间
int a[500001];//定义数组，别开小了（我第一次交就RE了）
int main()
{
	int n;cin>>n; 
	ufor(int i=1;i<=n;++i)
	{
		cin>>a[i];
	}//很简单的输入，应该不用说了
	sort(a+1,a+n+1);//sort是个好东西，小到大排序
	int mid=(1+n)>>1;//位运算，即(1+n)/2，二分常用，+1为了防奇偶性的问题
	int l=mid,r=n;//两个指针，0<l<=mid,mid<r<=n
	int ans=0;//一个关于答案的变量
	while(r>mid&&l>0)//实现r始终在右边，l始终在左边，越界则停止。
	{
		if((a[l]<<1)>a[r])//位运算+比较（真快
		{
			l--;//如果前面的数较小，则用更小的数比（即l往左移）
		}
		else
		{
			a[l]=0;//将塞进别人袋子里的袋鼠标记
			l--;r--;//此时两个指针所在的数都废了，于是都往左移，继续比较小一点的数
		}
	}
	for(int i=1;i<=n;++i)
	{
		if(a[i]!=0)
		{
			ans++;
		}
	}//最后看看还剩多少没塞进袋子里的袋鼠，即为答案
    //其实还可以简化，但这更好懂
	cout<<ans;//输出
	return 0;//return
}
```


---

## 作者：Xdl_rp (赞：2)

看到其他的大佬运用的都是贪心，蒟蒻这里用的是二分。



- 首先要将题目所给的数组**排序**，然后是普普通通的二分（模板），二分的是**装进去的数量**。

```
	int l = 0, r = n / 2;//由于如果每一个都可以装进另一个的话，最多只能装 n / 2 次
	while (l <= r) {
		int mid = (l + r) / 2;
		if (check(mid)) l = mid + 1;//这里的check是判断是否合法
		else r = mid - 1;
	}
```

- 接下来我们需要将二分出来的数进行一个判断，判断这个数量是否合法，如果不合法，范围缩小在这个数量之前，如果合法，则将范围集中到这个数量之后。

- 判断的方法是：$i$ 从 $1$ 开始枚举，再从 $1$ 到 $n$ 进行枚举，如果这一对符合题意，则记录下来，答案加一，退出循环，代码如下：

```cpp
int n;
bool check(int num) {
	int l = num + 1;
	bool f = false;
	for (int i = 1; i <= num; i++) {
		f = false;
		for (int j = l; j <= n; j++) {
			if (a[i] * 2 <= a[j]) {
				l = j + 1;
				f = true;
				break;
			}
		}
		if (!f) return false;
	}
	return true;
}
```

最后将 $n - r$ 输出就可以啦！

---

## 作者：_Flame_ (赞：1)

看到同机房好多大佬用 **二分** 的，但是我不会，所以我来写一篇 **贪心** 的题解。

题目让我们求最少可以留下几个数，我们可以反过来，先求最多可以删掉几个数。

我们先给整个数列排序一遍，然后我们可以把数列分成前后两部分，我们可以发现，较大的那一部分中最大的数大于等于较小的部分中最大数的两倍，较大的那一部分中第二大的数大于等于较小的部分中第二大数的两倍，以此类推，我们可以很容易的得出贪心策略。及用较大的部分中尽量大的数去消较小部分中尽量大的数，以此来删除尽量多的数。

求出最多可以删掉几个数后，用总个数减去最大删除个数即可得出答案。

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[1000100];
bool bk[1000100];
int k;

int main(){
    cin>>n;
    k=n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
	}
	sort(a+1,a+n+1);
	int ans=0;
	for(int i=n/2;i>=1;i--){
		if(a[k]>=(a[i]*2)){
			ans++;
			k--;
		}
	}
	cout<<n-ans;
    return 0;
}
```

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF372A)

## 题意

给定一个数组，在其间选取两个数，若小的数 $\times2\le$ 大的数，那么删掉小数，大数变为 $0$。

## 思路

贪心。

先从小到大排序，然后用较大的数去删除较小数，即能消去最多的数。

答案为总数减最多能删除的数。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,s,a[500001];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];
	m=n;//m用来维护较大数的位置
	sort(a+1,a+n+1);
	for(i=n/2;i>=1;i--)
		if(a[m]>=a[i]*2)
			m--,s++;
	cout<<n-s;
	return 0;
}
```

---

## 作者：Fuxh_18 (赞：0)

[CF372A 题目](https://www.luogu.com.cn/problem/CF372A)

~~原题翻译另外的题解有，可以自己去看一下。~~

## 分析
看到许多题解都用的二分，但是本蒟蒻不熟练二分，所以提供一个**贪心**。

输入这一串数后，为了方便计算，要把它们排序一下。想要留的最少，装的就要多，用大的装尽量大的，才能最好地利用。因为每个只能装一个，所以最多有前 $n$ 个被装（可以减少时间）。
## 做法
最开始 $ans=n$。先排序，判断从 $\frac{n}{2}$ 到 $1$ 能否被当前最大且没装的装，如果能，$ans-1$。最后输出 $ans$。
## [AC](https://www.luogu.com.cn/record/168616264) Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n,a[N],ans;
inline int read(){
	register int x=0,t=1;
	register char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			t=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*t;
}
inline void write(int x){
	if(x<0){
		x=-x;
		putchar('-');
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return;
}
int main(){
	n=read();
	ans=n; //给ans赋初值 
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+1+n); //排序 
	for(int i=n/2;i>=1;i--){
		if(a[ans]>=a[i]*2){ //a[ans]指的是没装过的最大的数 
			ans--;
		}
	}
	write(ans); //输出答案 
	return 0;
}
```
结束。

---

## 作者：Chenyichen0420 (赞：0)

# 思路分析

首先，我们根据题意可以轻松地知道被删除的数一定 $\le\frac{n}{2}$。我们还可以知道，更小的数比更大的数更容易被删除。所以如果有被删除的数，那么一定是较小的那 $\frac{n}{2}$ 个数。

这时候我们就从第 $\frac{n}{2}$ 个数起，开始向更小的数枚举。找有没有满足要求的数。可以倒序枚举，用指针指向最大的数。如果这个数都不满足，则一定没有数满足，枚举更小的数看是否满足，直到匹配再移动指针。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[500005],ps;
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	sort(a+1,a+n+1); ps=n;
	for(int i=n>>1;i;i--)
		if(a[ps]>=a[i]<<1)
			n--,ps--;
	cout<<n<<endl;
	return 0;
}
```

---

## 作者：f_x_f (赞：0)

这道题我是用贪心的思路做的，题目让我们求出最少可以留下多少个数，显然，我们可以反向枚举，枚举最多可以删除多少个数。

最多可以删除的个数，这个数一定在 $n/2$ 以内，因此我们开两个参数，一个用来记录大的数据，另一个用来记录小的数据。因此可以写出代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[100100];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	ll i=n/2,j=n,ans=0;
	while(i>=1&&j>n/2){
		if(a[i]*2<=a[j]){
			--i;
			--j;
			++ans;
		}
		else{
			--i;
		}
	}
	cout<<n-ans<<endl;
}
```

---

## 作者：Edmundino (赞：0)

# 题意

```
数组a有n个数,若对于两个数a[i],a[j] (1<=i,j<=n且a[i]≠0),若a[i]<=a[j]/2,即可把a[i]删去,a[j]变为0。

输入n及数组a,求出最后可剩下的最少数量的数,输出其个数
```
简单来说，就是：

在 $a$ 数组中，如果有两个数，较小的数$\times2\le$较大的数，那么删掉最小数，最大的数变为$0$。

# 分析

其实有点是贪心思想，

我们可以先从小到大的排序。

然后我们取中间的数，记为 $mid$，前面的部分相比后面的部分比较小（~~应该都知道吧~~）。

然后，我们分别取两段的最大值，分别为 $a_{mid},a_n$。

如果  $a_{mid}\times2\le a_n$，那么删除的数量（我们记为$s$）加一，然后两段最右边的数减一，即每段第二大的数。

但是，如果这个 $if$ 语句不成立了话，左边那一段也要减一，因为这个数的两倍比较大，那就只有将左段的数变小了。

搞定后，$n-s$ 就是最后的答案。

# 代码

**变量声明**

$l$：左段最大数的下标。

$r$：右段最大数的下标。

$mid$：中间数的下标。

$a_i$：即题面说的 $a$ 的数组。

$n$：即数组 $a$ 的长度。

$s$：要删除的数。


**贪心部分**

```cpp
	sort(a+1,a+1+n);
	mid=n/2;
	r=n;
	l=mid;
	while(l>=1&&r>mid)
	{
		if(a[l]*2<=a[r])
		{
			s++;
			r--;
		}
		l--;
	}
```

**$AC$代码**

```cpp
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>

using namespace std;

const int N=5e5+50;

int n,a[N],s,c,bo[N],r,l,mid;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	mid=n/2;
	r=n;
	l=mid;
	while(l>=1&&r>mid)
	{
		if(a[l]*2<=a[r])
		{
			s++;
			r--;
		}
		l--;
	}
	cout<<n-s;
	return 0;
}
```



---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
有 $n$ 只袋鼠，每只的大小为 $s_i$，每只大小为 $x$ 的袋鼠可以装在大小不少于 $2x$ 的袋鼠的袋子里。  
每只袋鼠的袋子最多装一只袋鼠，且装在别的袋鼠袋子里的袋鼠不能继续装袋鼠（不能套娃），求最多能让多少只袋鼠被装入别的袋鼠的袋子。  
## $\text{Solution}$
一道本人做的不太好的题。  
一开始显然是想贪心，比如从大往小选，每个尽可能装大的之类，但是都可以被轻易的 hack。  
~~然后就写了个垃圾的二分多只 log 艹过去了~~  

下面讲线性的贪心正解。  
其实刚才朴素的贪心是可以借鉴的，唯一的错误就在与尽可能装的的那只“大袋鼠”可能用来装别的袋鼠。  

证明：
由于装的个数最多肯定不超过 $n/2$ 个，所以最小的 $n/2$ 只袋鼠肯定不会装别人。  
同时，如果某只袋鼠装了一只不在这 $n/2$ 只袋鼠里的袋鼠，那它改成这 $n/2$ 只袋鼠中没有被装的一只（必然存在）也是不劣的。  
所以这个贪心是真的。  

维护双指针从 $n/2$ 开始尽可能的装大的即可。  
## $\text{Code}$
（双指针的代码题解区很多了，这里就贴的一开始二分的码，也算是另一种思路）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e6+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n;
int a[N];
bool check(int k){
  int l=1,r=k+1;
  while(l<=k){
    while(r<n&&a[r]<2*a[l]) ++r;
    if(a[r]<2*a[l]) return false;
    ++l;++r;
  }
  return true;
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=1;i<=n;i++) a[i]=read();
  sort(a+1,a+1+n);
  int st=0,ed=n/2;
  while(st<ed){
    int mid=(st+ed+1)>>1;
    if(check(mid)) st=mid;
    else ed=mid-1;
  }
  printf("%d\n",n-st);
  return 0;
}
/*
*/

```


---

## 作者：lihanyang (赞：0)

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
long long a[10000004];//开大点没关系
int main()
{
	long long n,x,ok=1;
	cin>>n;
	for(long long i=1;i<=n;i++)
	{
		cin>>a[i];
	}//读入
	x=a[1];
	for(long long i=2;i<=n;i++) if(x!=a[i]) ok=0;
	if(ok) 
	{
		cout<<n<<endl;
		return 0;
	}//13-19行为特判，指所有元素一样时的输出（#41测试点）
	sort(a+1,a+n+1);
	long long xiabiao=1;
	for(long long i=1;i<=n;i++)
	{
		if(a[i]>=2*a[xiabiao])
		{
			xiabiao++;
		}
	}
	cout<<n-min(n/2,xiabiao-1)<<endl;//这样就AC了
}
```

---

## 作者：_Felix (赞：0)

```cpp
//我才不会告诉你我是乱做a了。。。看代码
#include<bits/stdc++.h>
using namespace std;
int main() 
{
	int n,d[500005];//数组开小会TLE啊啊啊，记得啊
	int k=0;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>d[i];
	sort(d,d+n);//读入+排序哈哈哈
	for(int i=0;i<n;i++)
	{
		if(d[i]>=2*d[k])
			k++;
	}//每个袋鼠都装自己能装的最小的袋鼠（每只袋鼠也到能装自己的最小的袋鼠里去）
	cout<<n-min(k,n/2)<<endl；//输出！嗯？乱做出奇迹！！！ac了？！
    return 0;
}
```
**By 你们阔耐 的czy**

---

## 作者：xyf007 (赞：0)

- # pascal的题解
- 1.读入，先排序
- 2.因为最多前半部分全部小于后半部分的$2$倍，所以令$b_1$~$b_{n/2}$为$a_1$~$a_{n/2}$，$c_1$~$c_{n-n/2}$为$a_{n/2+1}$~$a_n$，对于每一个$b_i$找到最小可以放入的$c_j$
- # 以下代码

------------

```
var
  n,aa,bb,sum:int64;
  i:longint;
  a,b,c:array[1..500001] of int64;
procedure sort(l,r: longint);
var
  i,j,x,y: longint;
begin
  i:=l;
  j:=r;
  x:=a[(l+r) div 2];
  repeat
    while a[i]<x do
      inc(i);
    while x<a[j] do
      dec(j);
    if not(i>j) then
      begin
        y:=a[i];
        a[i]:=a[j];
        a[j]:=y;
        inc(i);
        dec(j)
      end;
    until i>j;
    if l<j then
      sort(l,j);
    if i<r then
      sort(i,r)
end;//排序
begin
  readln(n);
  for i:=1 to n do
    readln(a[i]);
  sort(1,n);
  for i:=1 to n div 2 do
    b[i]:=a[i];
  for i:=n div 2+1 to n do
    c[i-n div 2]:=a[i];
  aa:=1;
  bb:=1;
  sum:=n;//记录剩余个数
  while (aa<=n div 2) and (n div 2+bb<=n) do//查找最小可放入的
    if 2*b[aa]<=c[bb] then
      begin
        inc(aa);
        inc(bb);
        dec(sum)
      end
    else
      inc(bb);
  write(sum)
end.
```

---

