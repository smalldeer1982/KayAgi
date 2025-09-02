# Modified GCD

## 题目描述

Well, here is another math class task. In mathematics, GCD is the greatest common divisor, and it's an easy task to calculate the GCD between two positive integers.

A common divisor for two positive numbers is a number which both numbers are divisible by.

But your teacher wants to give you a harder task, in this task you have to find the greatest common divisor $ d $ between two integers $ a $ and $ b $ that is in a given range from $ low $ to $ high $ (inclusive), i.e. $ low<=d<=high $ . It is possible that there is no common divisor in the given range.

You will be given the two integers $ a $ and $ b $ , then $ n $ queries. Each query is a range from $ low $ to $ high $ and you have to answer each query.

## 样例 #1

### 输入

```
9 27
3
1 5
10 11
9 11
```

### 输出

```
3
-1
9
```

# 题解

## 作者：111l (赞：8)

#### 用什么二分？

通过暴力枚举可以发现，在[$1$,$10^{9}$]中，约数最多的数也只有$1344$个约数$(735134400)$，因此直接暴力枚举公约数存下来，暴力枚举每个公约数是否在区间内就做完了。

注意：对求出来的公约数中可能会有重复的，从小到大排序去重以后循环倒着找，一找到就输出，最大时间复杂度：$O(1344^{2})$，其实也很快的。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a,b,n,r[1345][2],szd[2],d[1345],sz;//r数组代表统计出的a的约数和b的约数，d数组代表a和b的公约数
int find(int l,int r){
	for(int i=sz;i;i--) if(d[i]>=l&&d[i]<=r) return d[i];//暴力找符合要求的答案 
	return -1;//边界判断 
}
int gcd(int a,int b){while(b^=a^=b^=a%=b);return a;}
int main(){
	scanf("%d%d%d",&a,&b,&n);
	for(int i=1;i*i<=a;i++) if(!(a%i)) r[++szd[0]][0]=i,r[++szd[0]][0]=a/i;//求a的约数 
	for(int i=1;i*i<=b;i++) if(!(b%i)) r[++szd[1]][1]=i,r[++szd[1]][1]=b/i;//求b的约数 
	for(int i=1;i<=szd[0];i++) for(int j=1;j<=szd[1];j++) if(r[i][0]==r[j][1]) d[++sz]=r[i][0];//暴力枚举相同约数，a和b的约数个数不同，可能会出现相同约数统计两次的情况，之后去重就好 
	sort(d+1,d+sz+1);
	sz=unique(d+1,d+sz+1)-d-1;
	for(int l,r;n;n--){
		scanf("%d%d",&l,&r);
		if(l>gcd(a,b)) printf("-1\n");//边界判断 
		else printf("%d\n",find(l,r));
	}
}
```

~~事实上，暴力枚举才是最耗时间的。~~

---

## 作者：ADay (赞：7)

没有用$upper\_bound$的题解？
那我来一篇吧~  
## 思路：预处理公约数，再二分查找
### 预处理公约数:  
我们知道，$a,b$任何一个公约数都能整除$\gcd(a,b)$，那么，怎么证明呢？   
#### 证明：
分解质因数，$a=p_1\times p_2\times \cdots \times p_x,b=q_1\times q_2\times\cdots\times q_y$    
根据公约数的定义,$a,b$的任意公约数$x$一定是集合$p,q$的相同元素集合$r$中的乘积组合$r_{i_1}\times r_{i_2}\times\cdots\times r_{i_k}$.  
那么$\gcd(a,b)=r_1\times r_2\times\cdots\times r_z$,即$r$的所有元素之积。则$x=r_{i_1}\times r_{i_2}\times\cdots\times r_{i_k}$一定被包含在$\gcd(a,b)=r_1\times r_2\times\cdots\times r_z$之中。   
即$a,b$任意公约数$x | \gcd(a,b)$,证毕。   


------------
很好，那么我们只枚举$\gcd(a,b)$的因数即可。  
我们从$1$枚举到$\left\lfloor \sqrt{\gcd(a,b)} \right\rfloor$,把$i$和$\dfrac{\gcd(a,b)}{i}\;push\_back$进一个$vector$即可。
### 二分查找
先把$vector:v$排序,方便查找.  
每次输入$x,y$时,设$pos=upper\_bound(v.begin(),v.end(),y)-v.begin()$.   
因为$upper\_bound(v.begin(),v.end(),y)$的返回值为$v$中第一个大于$y$的数的地址，若没找到返回$v.end()$，复杂度$\mathcal{O}(log\,_2n)$.  
则按理来说$v_{pos-1}$就是要找的数   
那么，就有两种情况：  
1. $v_{pos-1}<x$,则它小于$x$，输出$-1$ 
1. 找到了，输出$v_{pos-1}$   


------------
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int a,b,x,y,g;
vector<int>v;

int main()
{
	scanf("%d%d",&a,&b);
	g=__gcd(a,b);//求gcd(a,b)
	for(int i=1;i*i<=g;i++)if(g%i==0)v.push_back(i),v.push_back(g/i);//找公约数
	scanf("%d",&a);
	sort(v.begin(),v.end());//排序
	while(~scanf("%d%d",&x,&y))
	{
		int pos=upper_bound(v.begin(),v.end(),y)-v.begin();//二分查找
		if(v[pos-1]<x)puts("-1");//没找到
		else printf("%d\n",v[pos-1]);//找到了
	}
	return 0;
}
```


---

## 作者：tobie (赞：7)

首先，我们可以证明， $a$ 和 $b$ 的公约数一定是 $\gcd(a,b)$ 的约数。

证明（反证法）：

我们假设有一个数 $k$ 是 $a$ 和 $b$ 的公约数但不是 $\gcd(a,b)$ 的约数。

（我们先将这里的 $\gcd(a,b)$ 写作 $x$ ）

$\because k|a\ ,k|b\ ;\ \ x|a\ ,x|b\ $

$\therefore kx|a\ ,kx|b$

$\because kx>x$

$\therefore \text{命题不成立}$

所以我们可以先把 $\gcd(a,b)$ 的所有约数打一个表

然后对于每一个询问二分查找离右端点最接近的约数，再判断是不是在这个区间范围里就可以了。

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int gcd(int x,int y)  //求gcd
{
	return y==0?x:gcd(y,x%y);
}
int x,y,z,ans[100099],anss,t,a,b,ll,rr,r,mid;
int main()
{
	scanf("%d%d",&x,&y);
	z=gcd(x,y);
	for(int i=1;i*i<=z;i++)//枚举因数
	if(z%i==0)
	{
		ans[++ans[0]]=i;
		if(i*i!=z)
		ans[++ans[0]]=z/i;
	}
	sort(ans+1,ans+ans[0]+1);
	/*
	for(int i=1;i<=ans[0];i++)
	printf("%d ",ans[i]);//*/
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&a,&b);
		r=-1;
		ll=1,rr=ans[0];
		while(ll<=rr)//二分查找
		{
			mid=(ll+rr)/2;
			if(ans[mid]<=b)
			{
				r=mid;
				ll=mid+1;
			}
			else rr=mid-1;
		}
	//	printf("%d\n",r);（调试部分）
		if(a<=ans[r])
		printf("%d\n",ans[r]);
		else printf("-1\n");
	}
	return 0;
}
```


---

## 作者：xiaoPanda (赞：2)

### Problem
给定 $a,b$ ，多次询问，每次求 $a,b$ 在 $[l,r]$ 之间最大的公共约数。

### Solution
解决这题首先要来看一个命题：

$a,b$ 所有公共的约数一定是 $\gcd(a,b)$ 的约数。

很明显，$\gcd(a,b)$ 至少是 $a,b$ 的公共约数的几倍，所以命题为真。

（好吧其实我也说不太清，可以看看楼上几位巨佬的）

然后就很简单了，将 $\gcd(a,b)$ 的所有约数存起来，可以预处理到 $O(\sqrt{\gcd(a,b)})$ ，然后对其排序，满足单调性（然鹅我懒得打 sort 就用了 set ）。

对于每个询问，二分找到 $\le r$ 且最大的约数，如果它大于等于 $l$ ，就找到了答案，否则输出 $-1$ （如果最大的约数小于 $l$ ，那更小的约数也一定小于 $l$ )。

二分的话直接 upper_bound 一下在减去 $1$ 就是 $\le r$ 的最大的数了。

时间复杂度为 $O(\sqrt{\gcd(a,b)}+T\log tot)$ ，其中 $tot$ 表示 $\gcd(a,b)$ 的约数个数。
### Code
```cpp
void solve() {
	int l,r;
	cin>>l>>r;
	int ans=*--s.upper_bound(r);
	if(ans>=l)
		cout<<ans<<endl;
	else cout<<-1<<endl;
}
main() {
	cin >> a >> b >> T;
	w=__gcd(a,b);
	for(int i=1;i*i<=w;i++)
	if(w%i==0)s.insert(i),s.insert(w/i);
	while (T--)solve();
}
```


---

## 作者：奥特战士 (赞：2)

[原题链接](https://www.luogu.com.cn/problem/CF75C)
## 分析题面
>找出 $a$，$b$ 的最大公因子，然后给几个查询，每次查询包含 $x$，$y$ 两个数字，查询在 $x$ ~ $y$ 之间的 $a$，$b$ 的最大公因子

~~翻译得真详细~~

------------


首先当然应该找出 $a,b$ 的最大公因数

代码也十分的简单，不多讲

```cpp
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
```
------------
根据题意，我们应该找出 $[x,y]$ 中 $a,b$ 的最大公因数

不难看出，它一定是 $\gcd(a,b)$ 的因数

所以我们要把 $\gcd(a,b)$ 所有的因数找出来

我采用的是[整除分块](https://www.cnblogs.com/peng-ym/p/8661118.html)

复杂度 $O(\sqrt{n})$

------------
最后对于每一组 $x,y$ ，用二分查找就可以了
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,n,p,q;
int d[100005],cnt;
void gcd(int x,int y){
	if(!y){c=x;return;}
	gcd(y,x%y);return;
}
int main(){
	scanf("%d%d",&a,&b);gcd(a,b);
	for(int l=1,r=0;l<=c&&r<=c;l=r+1){
		r=c/(c/l);
		if(c%r==0)d[++cnt]=r;
	}
	d[++cnt]=1e9+5;
	scanf("%d",&n);
	while(n--){
		scanf("%d%d",&p,&q);
		if(p>c){puts("-1");continue;}
		int tmp=upper_bound(d+1,d+cnt+1,q)-d-1;
		if(d[tmp]>=p)printf("%d\n",d[tmp]);
		else puts("-1");
	}
	return 0;
}
```


---

## 作者：EDqwq (赞：2)

### 思路：

首先非常显然的一点：所有的公因数，一定是最大公因数的一个因数。

所以我们可以求出最大公因数，然后 $O(\sqrt n)$ 枚举出所有的因数。

对于大于 $\sqrt n$ 的因数，他一定和某个小于 $\sqrt n$ 的因数相乘等于最大公因数，所以我们枚举时可以一次获得两个因数。

然后对于询问，我们可以对所有的因数进行排序，然后直接二分就可以快速得出答案。

二分的时候，如果在范围内，就取 max 更新答案，并尝试变大，找到最大的因数。

如果二分结束后仍然没有更新过答案，输出-1。

复杂度来源于排序。

***

### 代码：

```cpp
/*
  Author: EnderDeer
  Online Judge: Luogu
*/

#include<bits/stdc++.h>

#define int long long
#define mem(x) memset(x,0,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n,m,q;
int a[1000010];
int gcdd;
int cnt;

signed main(){
	cin>>n>>m;
	gcdd = __gcd(n,m);
	for(int i = 1;i <= sqrt(gcdd);i ++){
		if(gcdd % i == 0){
			int num = gcdd / i;
			int num1 = gcdd / num;
			cnt ++;
			a[cnt] = num;
			if(num != num1){
				cnt ++;
				a[cnt] = num1;
			}
		}
	}
	sort(a + 1,a + cnt + 1);
	cin>>q;
	while(q --){
		int x,y;
		x = read(),y = read();
		int l = 1,r = cnt;
		int ans = -2147483647;
		while(l <= r){
			int mid = (l + r) / 2;
			if(a[mid] > y)r = mid - 1;
			else if(a[mid] < x)l = mid + 1;
			else {
				l = mid + 1;
				ans = max(ans,a[mid]);
			}
		}
		if(ans != -2147483647)cout<<ans<<endl;
		else cout<<-1<<endl;
	}
	return 0;
}
```

---

## 作者：李至擎 (赞：2)

[点我看题](https://www.luogu.com.cn/problem/CF75C)

思路：因为 $gcd(a,b)$ 是 $a$ 和 $b$ 的公因数，所以 $gcd(a,b)$ 的所有因数也是 $a$ 和 $b$ 的公因数和所有公因数（具体证明过程见dalao[@ADay](https://www.luogu.com.cn/user/312393)的[这篇题解](https://aday526.blog.luogu.org/solution-cf75c)的解释，本题解不再证明）——因此，我们可以先找出 $a$ 和 $b$ 的所有公因数，然后每次输入时再寻找答案。

方法：

- $1.$ 输入数据；

- $2.$ 求出最大公因数；

- $3.$ 通过找最大公因数的因数，预处理并记录下出 $a$ 和 $b$ 的所有公因数；

- $4.$ 对于每一组询问，在范围内进行寻找答案。

细节：

- 如果要快速找到答案，我们就可以用二分来查找。这里我用的是 $STL$ 自带的 $upper$_$bound$ 函数（它的作用是查找数组中第一个大于目标数的数的地址，如果找不到就返回尾迭代器）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n,gcd,num[1000005];//a、b和n如题意，gcd表示a和b的最大公因数，num数组是a和b的所有公因数 
int l,r,len;//l和r是每次查询的左右区间，len是a和b公因数的个数 
int main()
{
	cin>>a>>b;//输入 
	gcd=__gcd(a,b);//__gcd是STL的自带函数，求最大公因数的 
	for(int i=1;i*i<=gcd;i++)//从1到根号gcd枚举因数 
	{
		if(gcd%i==0)//如果i是gcd的因数 
		{
			num[++len]=i;//将i存入数组，个数+1 
			if(gcd/i!=i)//如果gcd不是平方数 
			{
				num[++len]=gcd/i;//那么，gcd/i也是gcd的因数
				//这里之所以要加上一个判断，是因为当i^2=gcd的时候，就会有重复的情况 
			}
		}
	}
	sort(num+1,num+len+1);//二分要保证数组有序 
	cin>>n;
	while(n--)
	{
		cin>>l>>r; 
		int x=upper_bound(num+1,num+len+1,r)-num-1;//因为upper_bound返回的是一个地址，所以要-num
		//而为什么要-1，原因是找到的是大于r的第一个数，要-1才在l到r的范围内 
		if(num[x]>=l)cout<<num[x]<<endl;//如果找到了，就输出答案 
		else cout<<-1<<endl;//反之，则无解，输出-1 
	}
    return 0;//结束程序 
}
```

---

## 作者：houpingze (赞：2)

分享一种~~常数极大~~的方法（

我们枚举 $1$ 到 $\sqrt{\min(a,b)}$ 中的每一个数，然后如果
 $i$ 是$a,b$的一个公约数，我们把它丢进数组，如果
 $\min(a,b)/i$ 是 $a,b$ 的一个公约数，我们也把它丢进数组。最后排个序以保证查询的二分。

然后查询的时候首先就是二分找一下现在数组里最后一个小于等于$y$的数的位置，如果符合条件就输出，否则输出 $-1$ .

---

## 作者：Lates (赞：1)

考虑预处理 $a,b$ 的公约数并存入一个 vector。

首先显然 $\gcd(a,b)|a,\gcd(a,b)|b $

因为 $\gcd(a,b)$ 是 $a,b$ 公约数中最大的，所以对于所有 $d|a,d|b$ 有 $d|\gcd(a,b)$

也就是说 $d | a,d|b$ 是 $d|\gcd(a,b)$ 的充要条件。

然后就可以愉快的枚举约数找出 $a,b$ 的所有因子了。

然后排序，通过 upper_bound 找出第一个大于 $high$ 的元素的位置，其上一个位置必然是 $<r$ 的，此时判断上一个位置的值是否在 $low$ 以内即可。

$Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
vector<int>v;
int ans,T,a,b,l,r,mid; 
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
signed main(){
	a=read(),b=read();
	a=gcd(a,b);
	for(register int i=1;i*i<=a;++i){
		if(a%i==0){
			v.push_back(i);
			v.push_back(a/i);
		}
	}
	sort(v.begin(),v.end());
	T=read();
	while(T--){
		l=read(),r=read();
		ans=upper_bound(v.begin(),v.end(),r)-v.begin()-1;// 注意有-1
		printf("%d\n",v[ans]<l?-1:v[ans]);
	}
	return 0;
}


```


---

## 作者：Plozia (赞：1)

题目大意很简洁明了，“最大公因子”就提示我们一定要用 $gcd$ 求最大公因子，设此处求出来的最大公因子为 $GCD$ 。

其中，有一个显而易见的事实：若 $a$ , $b$ 两个数的任意一个公因数设为 $x$ ,则 $x$ 一定是 $GCD$ 的因数。

明白了这一点，题目就很好做了。

首先，我们需要先求出 $a$ ,$b$ 的最大公因子，然后对分解出来的数求出它的因数，代码中我使用了 vector 来实现这一点。

其次，为了方便查找，我们需要对 vector 内求出来的数排序。

接下来，由于本蒟弱十分的弱，只想到了暴力算法：首先设立一个查找标记 $flag=0$ 。从大到小枚举vector内的数（因为要求范围内的**最大公因子**），发现第一个合法的数就可以输出，结束枚举,令 $flag=1$。如果枚举结束, $flag$ 依然是0，说明没有查找到，输出 `-1` 。

C++代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n,Gcd;
vector<int>book;
int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}//最大公约数 
void get()
{
	int i;
	for(i=1;i*i<Gcd;i++)
		if(Gcd%i==0) book.push_back(i),book.push_back(Gcd/i);
	if(i*i==Gcd) book.push_back(i);
}//GCD的因数 
int main()
{
	scanf("%d%d",&a,&b);
	Gcd=gcd(a,b);
	get();
	scanf("%d",&n);
	sort(book.begin(),book.end());//排序，方便后面查找 
	for(int i=1;i<=n;i++)
	{
		int x,y;
		bool flag=0;
		scanf("%d%d",&x,&y);
		for(int j=book.size()-1;j>=0;j--)//枚举  
		{
			if(book[j]>=x&&book[j]<=y)
			{
				printf("%d\n",book[j]);
				flag=1;break;//找到 
			}
		}
		if(flag==0) printf("-1\n");//没找到 
	}
	return 0;
}
```

---

## 作者：Limit (赞：1)

这题,貌似无从下手QAQ

~~但是很简单就可以想到二分吧,正好二分能过QAQ~~

自然就是先跑一个gcd~~(想必大家都会了)~~

然后...

然后就是一个二分呀QAQ

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int A,B,N,number=0;
int divisor[10000];
int gcd(int x,int y)//gcd
{
	if(y==0)return x;
	return gcd(y,x%y);
}
void solve()
{
	int low,high;
	scanf("%d%d",&low,&high);//每次查询的区间
	int _left=1,_right=number,middle,answer=-1;
	while(_left<=_right)//二分
	{
		middle=(_left+_right)/2;//取mid
		if(divisor[middle]>high/*判断是大了还是小了*/)_right=middle-1;else
		{
			_left=middle+1;
			if(divisor[middle]>=low)answer=divisor[middle];//记录下答案
		}
	}
	printf("%d\n",answer);//输出answer
}
int main()
{
	scanf("%d%d",&A,&B);
	int num=gcd(A,B);//记录下gcd后的值
	int Max=(int)(sqrt(num)),i;
	for(i=1;i<=Max;i++)
	if(num%i==0)//取出因数
	{
		divisor[++number]=i;
		divisor[++number]=num/i;
	}
	sort(divisor+1,divisor+number+1);//排一下序,符合单调性
	scanf("%d",&N);
	for(i=1;i<=N;i++)solve();//解决问题QAQ
}
```
然后
...
就
...
过了...


---

## 作者：傅思维666 (赞：0)

## 题解：

关键性质：

两个数的任意公因子一定是其最大公因子的因子。

这个性质的正确性是显然的。

如果数感不太好，完全可以用反证法证明一下。

然后就自然而然地想到先求gcd，再处理gcd的所有约数，再在其上二分查找。

二分查找的形式多种多样，可以手动，也可以STL upper_bound，你要是喜欢，打一棵权值线段树也没人管你。

我用的是upper_bound：

代码：

```cpp
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
int a,b;
vector<int> v;
int gcd(int a,int b)
{
	return !b?a:gcd(b,a%b);
}
void fac(int x)
{
	for(int i=1;i<=sqrt(x);i++)
		if(x%i==0)
		{
			v.push_back(i),v.push_back(x/i);
			if(i==x/i)
				v.pop_back();
		}
}
int main()
{
	scanf("%d%d",&a,&b);
	int g=gcd(a,b);
	fac(g);
	sort(v.begin(),v.end());
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int pos=upper_bound(v.begin(),v.end(),y)-v.begin();
		pos--;
		if(v[pos]<x)
			puts("-1");
		else
			printf("%d\n",v[pos]);
	}
	return 0;
}
```



---

## 作者：megalovania (赞：0)

这一题先把两个数字的公因数全找出来

然后在询问的时候，二分下标寻找公因数中符合范围的数就可以了
```cpp
#include<bits/stdc++.h>
using namespace std;
int num[150000],ying[150000];
long long head,tail,a,b,t;
void gkd(int x,int y){                  //寻找公因数
                                        //先找一半
	for(int i=1;i*i<=x;i++)         //先找比较小的数的因数，装进数组里
		if(x%i==0)            
			num[++head]=i;
	int zz=head;
	for(int i=1;i<=zz;i++)          //把下一半找出来
		if(x/num[i]!=num[i])    //不让根号的数进去两次
			num[++head]=x/num[i];
	for(int i=1;i<=head;i++)       //找公因数
		if(y%num[i]==0)
			ying[++tail]=num[i];
}
int main(void){
	cin>>a>>b;
	gkd(min(a,b),max(a,b));
	cin>>t;
	sort(ying+1,ying+1+tail);
	for(int i=1;i<=t;i++){
		long long ll,rr;
		cin>>ll>>rr;
		int l=1,r=tail+1,mid,ans=-1;   //l,r，mid都是下标
		while(l<=r){
			mid=(l+r)/2;
			int quin=ying[mid];
			if(quin<ll) l=mid+1;
			else if(quin>rr) r=mid-1;
			else{ l=mid+1;ans=max(quin,ans);}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：RiverFun (赞：0)

先求出两数的 $\gcd$，然后再求出 $\gcd(a,b)$ 的因子，存到vector里，排一下序，最后用二分查找就可以了。

因为我们是要求两数之间最大的，所以我门可以取因子的相反数再排序后查找。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#define MAXN 10010
struct node {
	int l, r;
}p[MAXN << 2];
std::vector <int> v;
int a, b, x, y, n, m;
template <typename T>
T gcd(T a, T b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}
int main() {
	scanf("%d%d%d", &a ,&b, &n);
	m = gcd(a, b);
	for (int i = 1; i <= sqrt(m); i++) {
		if (m % i == 0) {
			v.push_back(-i);
			if (i * i != m) {
				v.push_back(-(m / i));
			}
		}
	}
	sort(v.begin(), v.end());
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &x, &y);
		int k = std::lower_bound(v.begin(), v.end(), -y) - v.begin();
		if (-v[k] < x) puts("-1");
		else {
			printf("%d\n", -v[k]);
		}
	}
}
```

---

## 作者：yzx72424 (赞：0)

快速gcd+二分答案

一开始打了一个手残的做法：开一个map _x[i]记录所有的到i为止最大约数，然后判断，然后然后第十一个点就T了


然后问了某个dalao说是二分，然后苦思冥想一上午才想出来：
先求出a,b的最大公约数然后根据约数的性质对1-sqrt(gcd(a,b))枚举，这样就可以在sqrt(1e9)的时间内找出所有公因子，然后对于每次询问二分答案即可

Tle代码

```
#include<bits/stdc++.h>
using namespace std;
map<long long,long long>x;
int main() {
     long long a,b;
     long long m;
     scanf("%lld%lld",&a,&b);
     for(long long i=1;i<=a;i++){
     	if(a%i==0&&b%i==0)x[i]=i;
        else x[i]=x[i-1];
      } 
     scanf("%lld",&m);
     int maxn=a;
     while(m--){
   	 long long aa,bb;
     	scanf("%lld%lld",&aa,&bb);
     	if(maxn<bb){for(int i=maxn+1;i<=bb;i++)x[i]=x[i-1];maxn=bb;}
     	if(aa>a){printf("-1\n");continue;}
        else if(x[aa]!=x[bb]){printf("%lld\n",max(x[aa],x[bb]));continue;}
    	else if(x[aa]==x[bb]&&x[aa-1]!=x[aa]){printf("%lld\n",x[aa]);continue;}
  	    else if(x[aa]==x[bb]&&x[aa-1]==x[aa]){printf("-1\n"); continue;}
    }
} 
```

正解：
```
#include<bits/stdc++.h>
using namespace std;
int x[30000000];int oo=1;
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){ 
    char ch=nc();int sum=0;
    while(!(ch>='0'&&ch<='9'))ch=nc();
    while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=nc();
    return sum;
}
inline void put(int x)  
{     
    int num =0;char c[25];
    while(x) c[++num] =(x%10)+48,x/=10;
    while(num) putchar(c[num--]);
    putchar('\n'); 
}
inline int kgcd(int a, int b)
{ 
    if (a == 0) return b; 
    if (b == 0) return a; 
    if (!(a & 1) && !(b & 1)) 
        return kgcd(a>>1, b>>1)<<1;
    else if (!(b & 1))
    return kgcd(a, b>>1); 
    else if (!(a & 1)) return kgcd(a>>1, b); 
    else return kgcd(abs(a - b), min(a, b)); 
} 

int main() {
     int a,b;
	 int m;
	  a=read();b=read();
	 int uk=kgcd(a,b);
	 for(int i=1;i<=sqrt(uk);i++){
	 	if(uk%i==0){
		 if(uk/i==i){x[oo]=i;oo++;break;}
		 x[oo]=i;oo++;x[oo]=uk/i;oo++;}
  	  } oo--;
     sort(x,x+oo+1);
    // for(int i=1;i<=oo;i++)printf("%d ",x[i]); 
	 m=read();
     while(m--){
		int aa,bb;
        aa=read();bb=read();
        int tp=lower_bound(x+1, x + oo+1, bb)-x;
            if(x[tp]>bb||tp==oo+1)tp--;
            if(x[tp]<aa||x[tp]>bb)puts("-1");
            else printf("%d\n",x[tp]);
    }
} 
```

---

