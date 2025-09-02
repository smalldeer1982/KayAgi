# 8月31日

## 题目描述

高桥君注意到虽然今天暑假已经结束了，但是作业完全没有做完。

做作业的时间还有 $T$ 分钟。而且高桥君必须要做的作业有 $N$ 个。第 $i$ 个作业高桥君要解的话需要 $A_i$ 分钟，高桥君的朋友青木君做的作业全部抄下来的话，$B_i$ 分钟就可以完成了。但是抄朋友的作业是不太好的，所以高桥想尽量**不抄写**。为了在规定时间之前完成所有作业，请求出高桥君需要抄写的作业个数的最小值。但是，如果无法按时完成作业的话，请输出 `-1`。

## 样例 #1

### 输入

```
5 7
1 0
3 0
5 0
2 0
4 0```

### 输出

```
2```

## 样例 #2

### 输入

```
1 1000000000
5 0```

### 输出

```
0```

## 样例 #3

### 输入

```
1 0
100 99```

### 输出

```
-1```

## 样例 #4

### 输入

```
3 11
5 2
6 4
7 3```

### 输出

```
2```

## 样例 #5

### 输入

```
6 92
31 4
15 9
26 5
35 8
97 9
32 3```

### 输出

```
3```

# 题解

## 作者：Kaidora (赞：2)

不知道为什么新生群会发这题链接，因为是所谓处女题么？

题意很简单，机翻就能看懂，已提交题意概括。

首先解决有无解的问题。抄作业都做不完，那就只能`-1`。能做完的话，我们也先假设是全抄来的作业，答案目前是`N`。这时应该留下一些时间的，也就是说有些作业并不用抄。那么如何减少抄作业数？

```
3 11
5 2
6 4
7 3

```

看这个样例。全部抄作业的话，`9`分钟就做完了，此时答案是`3`。如果要把答案降到`2`，就要尝试一下某份作业自己做。做第一份需要多用`3`分钟，第二份多用`2`分钟，第三份多用`4`分钟。很明显选第二份作业自己做耗时少。

到这里应该都看出来了吧，这题就是一贪心题，选a与b的差值小的那些作业自己做。按生活经验来想也是，抄作业不比自己写快多少，那不就自己写好了；只有太费事的作业抄一下。

~~讨论版有一年前的题意，才4提交是因为都去At做么。~~

代码写了`C++`与`Ruby`，`Python`就不写了。~~反正这里都是面向过程编程。~~

```cpp

#include <iostream>
#include <algorithm>
using namespace std;

int N, T;
int A[100006];
int B[100006];
int sum;
int ans;

int main()
{
	cin >> N >> T;
	sum = 0;
	ans = N;
	for(int n = 1; n <= N; ++n) {
		cin >> A[n] >> B[n];
		sum += B[n];
		A[n] -= B[n];
	}
	if(sum > T) {
		puts("-1");
		return 0;
	}
	sort(A + 1, A + 1 + N);
	for(int n = 1; n <= N; ++n) {
		if(sum + A[n] > T)
			break;
		sum += A[n];
		--ans;
	}
	cout << ans << endl;
	return 0;
}

```

```ruby

N, T = gets.split.map(&:to_i)
ans = N
sum = 0
arr = []
N.times do
	a, b = gets.split.map(&:to_i)
	sum += b
	arr << a - b
end
if sum > T
	ans = -1
else
	arr.sort!
	arr.each do |x|
		break if sum + x > T
		sum += x
		ans -= 1
	end
end
puts ans

```

---

## 作者：kkk_dex (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_codefestival_2015_qualA_c)

[更好的食用方法](https://www.luogu.com.cn/blog/kkk-dex/8yue31ri)
~~无耻的广告~~

在做本题之前我先**提醒**大家一点，这导致我来回提交十几次：
## 此题库题似乎每一个输出都需要一个换行！！！ 
回到正题，本题思路：

1. 首先特判一点就是你每一个都不抄作业的时间总和如果 $\leq$ $t$， 那么你只需要抄 $0$ 个题解。
1. 第二，是你每一个作业都抄的时间总和如果 $>$ $t$，那么你将会超时，输出 $-1$。
1. 第三，就是最少抄几个作业，按每个作业自己做的时间与抄作业的时间之差，即每个作业的贡献从大到小排序，接着让每一个都不抄作业的时间总和一个一个减去贡献，直至时间 $\leq$ $t$，这时就可以输出了。
# 具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
struct node{
	int a,b;//a:不抄作业的时间。
               //b:抄作业的时间。
}x[100005];
long long ans,ans1,s;//不开long long见祖宗。
bool xx(node x,node y)
{
	return abs(x.a-x.b)>abs(y.a-y.b);
}
int main()
{
	cin>>n>>t;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i].a>>x[i].b;
		ans+=x[i].a;//计算每个作业都不抄的时间。
		ans1+=min(x[i].a,x[i].b);//计算每个作业都抄的时间，因为抄作业的时间有可能大于不抄作业的时间，所以取min。
	}
	if(ans<=t)//第一种情况，每个作业都不抄的时间小于t，输出0。
	{
		cout<<0<<endl;//换行！
		return 0;//结束程序，不再执行下面的。
	}
	if(ans1>t)//第二种情况，每个作业都抄的时间大于t，那么无法按时完成，输出-1。
	{
		cout<<-1<<endl;//再说一遍换行！
		return 0;
	}
	sort(x+1,x+1+n,xx);//按贡献从大到小排序。
	for(int i=1;i<=n;i++)
	{
		ans=ans-(x[i].a-x[i].b);//减去每个的贡献。
		s++;//计数，抄了几个作业。
		if(ans<=t)//如果这时所用时间<=t,直接输出s,结束程序。
		{
			cout<<s<<endl;
        return 0;
		}
	}
	return 0;//完结了
}
```
~~你确定不点个赞再走吗~~

---

## 作者：Griseo_nya (赞：1)

这道题是肥肠简单的题呢。

我的思路是以自己写作业的总时间为基础，找到最大的自己写时间与抄作业时间之差减去来使写作业变成抄作业。

我们在输入的时候维护 $tot1$ （抄作业的总时间）和 $tot2$ (自己写的总时间)，如果输入过程中 $tot1>t$ 了直接输出-1退出程序就ok了。在输入的时候同时维护两个时间的差值，把抄作业的时间、自己写的时间和两个时间的差值都存在一个结构体内，快排一遍，然后从大往小减去时间差，直到 $tot2<t$ 为止。

另外，AtCoder 的题最后要有换行！！！！

废话不多说，上代码:



```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,ans,tot1,tot2;					//tot1是抄作业的总时间，tot2是自己写的总时间
const int maxn=1e5+1;
struct work{
	int copy,delta,finish;				//分别是抄作业的时间、自己写的时间和两个时间的差
}home[maxn];
bool cmp(work a,work b){
	return a.delta>b.delta;				//比较差值，差值大的靠前
}
int main(){
	ios::sync_with_stdio(false);		//读入优化
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>home[i].finish>>home[i].copy;	
		home[i].delta=home[i].finish-home[i].copy;//维护两个时间之差
		tot1+=home[i].copy;				//维护tot1(抄作业的时间和)
		tot2+=home[i].finish;			//维护tot2(写作业的时间和)
		if(tot1>t){						//如果抄作业都抄不完就直接退出
			cout<<-1<<endl;
			return 0;
		}
	}
	if(tot2<=t){						//如果正常写可以写完就不用抄了
		cout<<0<<endl;
		return 0;
	}
	sort(home+1,home+n+1,cmp);			//按差值从大往小排序
	int pos=1;							//进行到哪一个作业了
	while(tot2>t){						
		tot2-=home[pos++].delta;		//减去差值，位置+1
		ans++;							//给ans+1
	}
	cout<<ans<<endl;					//输出答案
	return 0;
}
```




---

## 作者：Shadow_Lord (赞：1)

### 题目大意：
做作业的时间还有 $T$ 分钟。要做的作业有 $N$ 个。第 $i$ 个作业要解的话需要 $A_i$ 分钟作业全部抄下来的话，$B_i$ 分钟就可以完成了。但是高君桥想尽量不抄写。为了在规定时间之前完成所有作业，请求出高桥君需要抄写的作业个数的最小值。但是，如果无法按时完成作业的话，请输出 $-1$。

emmm...

#### 这题十分的真实

首先我们要知道无论抄的题节约了多长时间，都算抄了一个且对以后抄作业无影响，十分典型的贪心。只要先抄贡献时间最大的，最后在输出 $ans$ 就可以了，需要注意的是如果 $A_i$ 的和本来就小于 $T$ 就直接输出零，反之 $B_i$ 的和如果小于 $T$ 的话就输出 $0$ 。

注意：输出要有换行符。

# Code


```cpp
#include<bits/stdc++.h> //万能头 
using namespace std;
const int N=1e6+6;
long long t,n,ans,e,z;
struct node{
	long long a,b; 
}f[N];
bool cmp(node x,node y) //排序
{
	return (x.a-x.b)>(y.a-y.b);
}
int main()
{
	cin>>n>>t;
	for(int i=1;i<=n;i++)
	{
		cin>>f[i].a>>f[i].b;
		e+=f[i].a;
		z+=f[i].b;
		if(z>t) //如果全抄也会超时直接输出-1 
		{
			cout<<"-1\n"; 
			return 0;
		}
	}
	if(e<=t) //不抄作业 
	{
		cout<<"0\n";
		return 0;
	}
	
	sort(f+1,f+n+1,cmp); //按贡献排序
	
	for(int i=1;i<=n;i++)
	{
		e-=(f[i].a-f[i].b);
		ans++;
		if(e<=t) //如果时间小于规定时间时跳出 
		{
			break;
		}
	}
	printf("%lld",ans); 
	cout<<endl;  //最后注意换行
	return 0;
}
```


---

## 作者：LeiZeProMax (赞：0)

题意：给定作业数量 $n$，剩余的时间 $t$，做作业用的时间 $a_i$ 以及抄作业用的时间 $b_i$，求：能否做完作业？如果能做完，最少需要抄几份作业？

我们需要先判断能否做完作业，设所有作业都抄，将所用时间与剩余时间作比较，如果小于等于 $t$，那么他可以做完；反之则不能。

当所用时间小于剩余时间时，说明可以做完，那么我们就该判断至少需要的时间了。

我们定义一个数组 $c_i$ 表示每项作业抄作业和做作业的时间差，将他们排序。因为要求抄的作业越少越好，所以我们要优先选择时间差大的作业来抄。

# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,t,a[100001],b[100001],c[100001],chao,zuo;
ll ans;//ans为至少需抄作业的数量 
inline ll read()//快读 
{
	ll s=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
	return s*f;
}
int main()
{
	n=read();t=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read();b[i]=read();
		c[i]=a[i]-b[i];//统计每项作业抄和做的时间差 
		zuo+=a[i];chao+=b[i];//统计做作业用的时间和抄作业用的时间 
	}
	if(chao>t)//如果全部作业都抄时间还不够，输出-1 
	{
		puts("-1");
		return 0;
	}
	sort(c+1,c+n+1);//将时间差排序 
	ll r=n;//因为上面是从小到大排序，所以要从后枚举 
	while(zuo>t)//求最少需要抄的作业数量 
	{
		zuo-=c[r];
		ans++;
		r--;
	}
	printf("%lld\n",ans);//记得换行
	return 0;
}
```


---

