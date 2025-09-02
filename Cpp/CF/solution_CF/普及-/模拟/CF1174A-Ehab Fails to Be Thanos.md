# Ehab Fails to Be Thanos

## 题目描述

You're given an array $ a $ of length $ 2n $ . Is it possible to reorder it in such way so that the sum of the first $ n $ elements isn't equal to the sum of the last $ n $ elements?

## 说明/提示

In the first example, the first $ n $ elements have sum $ 2+1+3=6 $ while the last $ n $ elements have sum $ 1+1+2=4 $ . The sums aren't equal.

In the second example, there's no solution.

## 样例 #1

### 输入

```
3
1 2 2 1 3 1
```

### 输出

```
2 1 3 1 1 2```

## 样例 #2

### 输入

```
1
1 1
```

### 输出

```
-1```

# 题解

## 作者：YLWang (赞：3)

一眼过去随机化

将a数组随机打乱10000次，若存在一次满足题设则输出。

否则即无解。输出-1.

```
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(int i = (k); i <= (j); i++)
#define INF 2147483647
using namespace std;
inline int read()
{
    int num = 0; char c=' '; int flag = 1;
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num * flag;
}
#define MAXN 200005
int n, a[MAXN];
signed main()
{
	srand(time(0));
	n = read();
	For(i, 1, 2 * n)
		scanf("%d", &a[i]);
	For(i, 1, 10000) {
		random_shuffle(a + 1, a + 1 + 2 * n);
		int sum1 = 0;
		For(i, 1, n) sum1 += a[i];
		For(i, n+1, 2*n) sum1 -= a[i];
		if(sum1 != 0) {
			For(i, 1, 2 * n) cout << a[i] << ' ';
			return 0;
		}
	}
	cout << -1 << endl;
    return 0;
}
```

---

## 作者：_byta (赞：2)

考虑尽量使两部分的数之和不一样，那显然，我们想到把数组从小到大排序。

这样可以使两部分的差值最大，也就是说两部分的数的不一样的程度最大。

如果排序后的两部分和相同，则判为无解。

细节详见代码注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100002;
int n,m,k,p,q,ans,sum,tot,cnt,a[N],b[N],c[N];
int main()
{
	cin>>n;
	for(int i=1;i<=2*n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+2*n+1);//排序
	p=n+1;
	for(int i=1;i<=n;i++)
	{
		sum+=a[i];//sum为前n个数的和
		ans+=a[p];//ans为后n个数的和
		p++;
	}
	if(ans==sum)//如果相等，则判为无解
	{
		cout<<"-1";
	}
	else//否则输出
	{
		for(int i=1;i<=2*n;i++)
		{
			cout<<a[i]<<" ";
		}
	}
	return 0;
}
```




---

## 作者：Vidoliga (赞：1)

# 题解

前言$:$我同学[Agent008](https://www.luogu.com.cn/user/319042)的题解弱爆了$,$于是我打算帮他加强一下

他的那篇题解的思路没有任何问题$,$就是代码过水$:$他的[题解](https://www.luogu.com.cn/blog/agent008/solution-cf1174a)

$Ta$已经讲的很清楚了$,$于是我直接放出代码帮他加强一下

本蒟蒻代码$:$

```
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int main(){
	int n,a[2000];bool f=true;
	scanf("%d",&n);
	n<<=1;
	scanf("%d",&a[0]);
	for(int i = 1;i < n;i++){
		scanf("%d",&a[i]);
		if(a[i]!=a[0]){
			f=false;
		}
	}
	if(f){
		putchar('-');putchar('1');
		return 0;
	}
	sort(a,a+n);
	for(int i = 0;i < n;i++){
		printf("%d ",a[i]);
	}
	return 0;
}
```

完结撒花$!!$

---

## 作者：SFWR (赞：1)

根据题意只需要找出一个满足条件的序列即可，所以只需要找到$[1,n]$与$[n+1,n*2]$中任意一对不相等的数进行交换即可，但要注意有可能会本身已满足条件，此时直接输出原序列即可。

根据出题人提供的方法还有一个是对数组直接排序，输出的也一定会是符合条件的序列。

法一
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10000],n;
int main()
{
	cin>>n;
	for(int i=1;i<=2*n;i++)cin>>a[i];
	int s1=0,s2=0;
	 for(int i=1;i<=n;i++)s1+=a[i];
	 for(int j=n+1;j<=n*2;j++)s2+=a[j];
	 if(s2!=s1)
	 {
	 	for(int i=1;i<=2*n;i++)cout<<a[i]<<" ";
		return 0;
	 }
	for(int i=1;i<=n;i++)
	for(int j=n+1;j<=n*2;j++)
	if(a[i]!=a[j])
	{
		swap(a[i],a[j]);
		for(int i=1;i<=2*n;i++)cout<<a[i]<<" ";
		return 0;
	}
	cout<<-1;
}
```


---

## 作者：Fearliciz (赞：0)

此题因该改为红题。

非常简单的小学思维题。

#### 题目大意：

你被给予了一个长度为 $2n$ 的序列 $a$。

试问：是否存在重排方法，前 $n$ 个元素的和不等于后 $n$ 个元素的和？

如果有，输出排列，否则输出 `-1`。

#### 解题思路：

同样非常简洁。

因为给出的序列原本前 $n$ 项和后 $n$ 项时的和是相同的。

要使新的排序前后差距最大，就可以将序列排序，如果排序完的数列符合题目要求，则直接输出排完序的序列，否则直接输出 `-1`。

#### 代码：

这样代码就很简单了：


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2001],cnt1,cnt2;
signed main()
{
	int n;
	cin>>n; n*=2;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
		if(i<=n/2) cnt1+=a[i];
		else cnt2+=a[i];
	if(cnt1!=cnt2) for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	else cout<<"-1";
	return 0;
}
```




---

## 作者：WinterRain208 (赞：0)

CF1174A 【Ehab Fails to Be Thanos】

很简单，只要数组中元素钚全部一样即可。

否则我们一定可以分为和不同两组。

模拟两个过程

先判断所有元素是否一样，是则输出无解。

否则排序，输出即可。

题解要有题解的样子，我们来介绍几种排序算法。

快排和归并，复杂度$O(nlogn)$，不推荐。

其他各种算法：冒泡，选排，插入，复杂度$O(n^2)$，不考虑。

因为$a_i$小于$1e6$，所以桶排。

### 代码（快排）

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=2000+5;

#define int long long

int n,a[N];
bool flag=1;

signed main(){
	cin>>n;
	F(i,1,2*n){
		cin>>a[i];
		if(a[1]!=a[i])flag=0;
	}
	if(flag)puts("-1");
	else{
		sort(a+1,a+1+2*n);
		F(i,1,2*n)cout<<a[i]<<" ";
		puts("");
	}
	exit(0);
}
```

$wtrl$

---

## 作者：FP·荷兰猪 (赞：0)

> 题意：

> 你被给予了一个长度为2n的序列a.

> 试问：是否存在重排方法，前n个元素的和不等于后n个元素的和？

一道简单的贪心。。。

解法：将数组从小到大排序，如果此时前n个数的和等于后n个数的和，输出-1，否则输出排完序的数组。

详见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,x,y) for (ll i=x;i<=y;i++)

inline int read()
{
    char c=getchar(); int x=0, f=1;
    while(c<'0' || c>'9') {if(c=='-')f=-1; c=getchar();}
    while(c>='0' && c<='9') {x=x*10+c-'0'; c=getchar();}
    return x*f;
}

int main()
{
    int n=read();
    int a[n*2+1];
    rep(i,1,n*2)
    {
        a[i]=read();
    }
    sort(a+1,a+n*2+1);//对a数组排序
    ll cnt;
    cnt=0;
    rep(i,1,n)
    {
        cnt+=a[i];
    }
    rep(i,n+1,n*2)
    {
        cnt-=a[i];
    }//cnt是前n个数的和与后n个数的和之差
    if (cnt==0)//差为0，则输出-1
    {
        cout<<"-1"<<endl;
        return 0;
    }
    else//否则输出这个排列
    {
        rep(i,1,n)
        {
            cout<<a[i]<<" ";
        }
        rep(i,n+1,n*2)
        {
            cout<<a[i]<<" ";
        }
    }
    return 0;
}
```

---

## 作者：Agent008 (赞：0)

我们第一眼看过去，可以发现两件事：

### 1. 只有当全部的数都是相同的时候，才会输出-1

### 2.只要有数不相同，直接一个sort排序就可以输出了

刚开始这道题目有点烦。。我第一次处理得很SB

$2n$个数，结果只要输入$n$，所以代码里我就直接把$n=2n$了。（估计猪都会，我第一次还做错了，脑子被吃掉了我）

然后的话就判断所有的数相不相等，如果相等的话，就输出$-1$；不然的话，就$sort$排序，然后输出排完序后的数组。完结，撒花！！✿✿ヽ(°▽°)ノ✿

#### 当然出题人这次很良心，不用开longlong,也不卡时间。

所以献上我那丑陋的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(int a,int b){
	return a>b;
	
}
int main(){
	int n,tmp=0;
	cin>>n;
	n=2*n;
	int a[n+1];
	bool b[n+1];
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=false;
	}
	b[1]=true;
	for(int i=2;i<=n;i++){
		if(a[1]==a[i]){
			b[i]=true;
		}
	}
	for(int i=1;i<=n;i++){
		if(b[i]==true){
			tmp++;
		}
	}
	if(tmp==n){
		cout<<"-1"<<endl;
	}
	else{
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++){
			cout<<a[i]<<" ";
		}
	}
}
```


---

