# Hills And Valleys

## 题目描述

You are given a sequence of $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ . Let us call an index $ j $ ( $ 2 \le j \le {{n-1}} $ ) a hill if $ a_j > a_{{j+1}} $ and $ a_j > a_{{j-1}} $ ; and let us call it a valley if $ a_j < a_{{j+1}} $ and $ a_j < a_{{j-1}} $ .

Let us define the intimidation value of a sequence as the sum of the number of hills and the number of valleys in the sequence. You can change exactly one integer in the sequence to any number that you want, or let the sequence remain unchanged. What is the minimum intimidation value that you can achieve?

## 说明/提示

In the first test case, changing $ a_2 $ to $ 2 $ results in no hills and no valleys.

In the second test case, the best answer is just to leave the array as it is.

In the third test case, changing $ a_3 $ to $ 6 $ results in only one valley (at the index $ 5 $ ).

In the fourth test case, changing $ a_3 $ to $ 6 $ results in no hills and no valleys.

## 样例 #1

### 输入

```
4
3
1 5 3
5
2 2 2 2 2
6
1 6 2 5 2 10
5
1 6 2 5 1```

### 输出

```
0
0
1
0```

# 题解

## 作者：CaiXY06 (赞：4)

我们考虑贪心。

显然改变某一个点的高度只会对其左右和自身是否是山谷或山峰产生影响。

又因为改变单点高度与左边或右边同高，会使该点和同高点不为山谷山峰。

所以我们就可以暴力枚举每一个点使其与左右同高，并统计对答案的影响，取个 $max$。

我们设

$$f(i)=0(i\in{1,n})$$

$$f(i)=1(i\in(1,n),a_{i}>a_{i-1},a_{i}>a_{i+1})$$

$$f(i)=1(i\in(1,n),a_{i}<a_{i-1},a_{i}<a_{i+1})$$

$$x=f(i-1)+f(i)+f(i+1)$$

$$y=f(i-1)+f(i)+f(i+1)$$

$y$是在$a_{i}$值改变后。

则对答案的影响为 $x-y$

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[300010],finalans,ans;
inline bool hill(int i){
	return i>1&&i<n&&a[i]>a[i-1]&&a[i]>a[i+1];
}
inline bool valley(int i){
    return i>1&&i<n&&a[i]<a[i-1]&&a[i]<a[i+1];
}
inline int work(int i,int j,int k){
	int res=0,cnt=0;
	res+=hill(i-1)||valley(i-1);
	res+=hill(i)||valley(i);
	res+=hill(i+1)||valley(i+1);
	a[i]=a[i+j];
	cnt+=hill(i-1)||valley(i-1);
	cnt+=hill(i)||valley(i);
	cnt+=hill(i+1)||valley(i+1);
	a[i]=k;
	return res-cnt;
}
int main(){
	scanf("%d",&T);
	while(T--){
		finalans=ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=2;i<n;i++)finalans+=hill(i)||valley(i);
		for(int i=2;i<n;i++)ans=max(ans,max(work(i,-1,a[i]),work(i,1,a[i])));
		printf("%d\n",finalans-ans);
	}
	return 0;
}
```



---

## 作者：pigstd (赞：2)

一个非常 naive 的方法。

枚举修改的点 $i$，那么显然 $a_i$ 可能的修改的取值为 $a_{i-1},a_{i+1},\max(a_{i-1},a_{i+1})+1,\min(a_{i-1},a_{i+1})-1,\max(a_{i-1},a_{i+1})-1$ 。显然当 $a_i$ 取任意值的时候都会与上述方法中的一种等价。

然后暴力查询就好了。

code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int M=3e5+10;
int T,n,a[M],p[M];

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

bool cmp(int k)
{
	if (k<=1||k>=n)return 0;
	return (a[k]>a[k-1]&&a[k]>a[k+1])||(a[k]<a[k-1]&&a[k]<a[k+1]);
}

int work(int i)
{
	int cnt1=abs(p[i-1])+abs(p[i])+abs(p[i+1]);
	int cnt2=0;
	if (cmp(i))cnt2++;
	if (cmp(i-1))cnt2++;
	if (cmp(i+1))cnt2++;
	return cnt1-cnt2;
}

signed main()
{
	T=read();
	while(T--)
	{
		n=read();int cnt=0;
		for (int i=1;i<=n;i++)
			a[i]=read();
		for (int i=2;i<n;i++)
			if (a[i]>a[i-1]&&a[i]>a[i+1])p[i]=1,cnt++;
			else if (a[i]<a[i-1]&&a[i]<a[i+1])p[i]=-1,cnt++;
		int maxn=0;
		for (int i=1;i<=n;i++)
		{
			int k=a[i];
			a[i]=a[i-1];maxn=max(work(i),maxn);
			a[i]=a[i+1];maxn=max(work(i),maxn);
			a[i]=max(a[i-1],a[i+1])-1;maxn=max(work(i),maxn);
			a[i]=min(a[i-1],a[i+1])-1;maxn=max(work(i),maxn);
			a[i]=max(a[i-1],a[i+1])+1;maxn=max(work(i),maxn);
			a[i]=k;
		}
		cout<<max(0ll,cnt-maxn)<<endl;
		for (int i=1;i<=n;i++)p[i]=0;
	}
	return 0;
}
```
多测千万要清空！！！

---

## 作者：lndjy (赞：1)

考虑一个点的修改，只可能对他本身，他左边，他右边这三个数的峰谷情况有影响。

那么就可以枚举修改的数，然后考虑变化量。

结论：一个数只能修改成他左面或右面的数一定不劣于其他情况。

证明：一个数修改后，如果比左右的数都大，那么对于他本身，会是山峰，对于他左右，和他变成和左面/右面相等的数，没有影响，因为如果一个数和他旁边的一个数相等，那么他峰谷都不是。比左右的数都小的情况同理。

于是枚举每个数修改成左面和右面的数的情况就行了。

```cpp
#include<iostream>
using namespace std;
int a[300005],n;
bool gu(int i)
{
	if(i==1||i==n) return 0;
	return (a[i-1]>a[i]&&a[i+1]>a[i]);
}
bool feng(int i)
{
	if(i==1||i==n) return 0;
	return (a[i-1]<a[i]&&a[i+1]<a[i]);
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		cin>>a[i];
		if(n==1)
		{
			cout<<0<<endl;
			continue;
		}
		int ans=0,delta=0;
		for(int i=2;i<=n-1;i++)
		{
			if(gu(i)) ans++;
			if(feng(i)) ans++;
		}
		int now,now1;
		for(int i=2;i<=n-1;i++)
		{
			now=now1=0;
			if(gu(i)||feng(i)) now++;
			if(gu(i-1)||feng(i-1)) now++;
			if(gu(i+1)||feng(i+1)) now++;
			int t=a[i];
			a[i]=a[i-1];
			if(gu(i)||feng(i)) now1++;
			if(gu(i-1)||feng(i-1)) now1++;
			if(gu(i+1)||feng(i+1)) now1++;
			delta=max(delta,now-now1);
			now1=0;
			a[i]=a[i+1];
			if(gu(i)||feng(i)) now1++;
			if(gu(i-1)||feng(i-1)) now1++;
			if(gu(i+1)||feng(i+1)) now1++;
			delta=max(delta,now-now1);
			a[i]=t;
		}
		cout<<max(ans-delta,0)<<endl;
	}
 	return 0;
}


```


---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1467B)

这 sb 题我调了一天……

注意到我们并不关心一个点究竟是山峰还是山谷，于是直接处理一遍打标记。

考虑暴力枚举修改点。对于要修改的点 $a_i$，显然修改之后只有两种情况： $a_i=a_{i+1}$ 或 $a_i=a_{i-1}$。

于是直接枚举要修改的 $a_i$ 即可，分别令 $a_i=a_{i+1}$ 和 $a_i=a_{i-1}$，看看答案总数减小了多少。

巨大坑点：注意判断的时候数组不要越界！

时间复杂度 $O(\sum n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned ll
using namespace std;
ll read()
{
    ll x=0,f=1;
	char ch=getchar();
    while(ch<'0'||ch>'9')
    {
      	if(ch=='-')
      		f=-1;
      	ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
      	x=x*10+ch-'0';
      	ch=getchar();
    }
    back x*f;
}
int t,n,a[300005];
bool flag[300005];
int main()
{
	t=read();
	while(t--)
	{
		int sum=0,ans=0;
		memset(flag,0,sizeof(flag));
		n=read();
		for(ri i=1;i<=n;i++)
			a[i]=read();
		for(ri i=2;i<=n-1;i++)
			if((a[i]>a[i+1]&&a[i]>a[i-1])||(a[i]<a[i+1]&&a[i]<a[i-1]))
				flag[i]=1,sum++;
		ans=sum; 
		for(ri i=2;i<=n-1;i++)
		{
			int lsbl=a[i];
			int now=0,now1=0;
			int tot=flag[i-1]+flag[i]+flag[i+1];
			if(!tot)
				continue;
			a[i]=a[i-1];
			if(i<n-1&&((a[i+1]<a[i+2]&&a[i+1]<a[i])||(a[i+1]>a[i+2]&&a[i+1]>a[i])))
				now++;
			a[i]=a[i+1];
			if(i>2&&((a[i-1]>a[i]&&a[i-1]>a[i-2])||(a[i-1]<a[i]&&a[i-1]<a[i-2])))
				now1++;	
			tot-=min(now,now1);
			ans=min(ans,sum-tot);
			a[i]=lsbl;
		}
		cout<<ans<<"\n";
	}
	back 0;
}
```

---

## 作者：jiangtaizhe001 (赞：0)

[题目传送门](http://codeforces.com/problemset/problem/1467/B)  
解题思路：  
题目中说只能修改一个数字的值，那么显然我们就可以枚举每个 $i\ \left(2\le i \le n\right)$ ，那么我们修改第 $i$ 个数字的话，显然我们修改之后只有 $i-1,i,i+1$ 三个位置的状态发生了改变，我们只要预处理不修改的答案总和就可以了。  
修改的时候我们会发现，要想让修改之后的答案最小，我们就需要将这个数字的值修改成前一个数的值或者后一个数字的值，也可能是两者的平均数。   
最后记得注意修改第 $1$ 个和修改第 $n$ 个的情况，~~因为这个我WA了3发~~。  
Tips:记得多组数据清空数组。  
代码：
```cpp
#include<cstdio>
#include<cstring>
#define maxn 300039
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
//#define debug
typedef int Type;
inline Type read(){
	Type sum=0;
	int flag=0;
	char c=getchar();
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') c=getchar(),flag=1;
	while('0'<=c&&c<='9'){
		sum=(sum<<1)+(sum<<3)+(c^48);
		c=getchar();
	}
	if(flag) return -sum;
	return sum;
}
int T;
int n,a[maxn];
int cheg(int x){
	if(x==1||x==n) return 0;
	return (a[(x)]<a[(x+1)]&&a[(x)]<a[(x-1)]);
}
int ches(int x){
	if(x==1||x==n) return 0;
	return (a[(x)]>a[(x+1)]&&a[(x)]>a[(x-1)]);
}
void work(){
	memset(a,0,sizeof(a));
	n=read();
	for(int i=1;i<=n;i++)
	    a[i]=read();
	int sum,ans;
	sum=0;
	for(int i=2;i<n;i++){
	    if(cheg(i)) sum++;
		if(ches(i)) sum++;
	}
	ans=sum;
	int tmp,pre,end;
	for(int i=2;i<n;i++){
		tmp=a[i];
		pre=cheg(i)+cheg(i-1)+cheg(i+1)+ches(i)+ches(i-1)+ches(i+1);
		
		a[i]=a[i-1];
		end=cheg(i)+cheg(i-1)+cheg(i+1)+ches(i)+ches(i-1)+ches(i+1);
		ans=min(ans,sum-pre+end);
		
		a[i]=a[i+1];
		end=cheg(i)+cheg(i-1)+cheg(i+1)+ches(i)+ches(i-1)+ches(i+1);
		ans=min(ans,sum-pre+end);
		
		a[i]=(a[i+1]+a[i-1])>>1;
		end=cheg(i)+cheg(i-1)+cheg(i+1)+ches(i)+ches(i-1)+ches(i+1);
		ans=min(ans,sum-pre+end);
		
		a[i]=tmp;
	}
	pre=cheg(2)+ches(2);
	a[1]=a[2];
	end=cheg(2)+ches(2);
	ans=min(ans,sum-pre+end);
	
	pre=cheg(n-1)+ches(n-1);
	a[n]=a[n-1];
	end=cheg(n-1)+ches(n-1);
	ans=min(ans,sum-pre+end);
	
	printf("%d\n",ans);
	return;
}
int main(){
    T=read();
    while(T--) work();
	return 0;
}
```

---

## 作者：Refined_heart (赞：0)

考虑分类讨论。

首先对于第一个数和最后一个数的修改无非就是判断它本身是不是作为旁边一个数为峰或谷的条件。

对于其他在中间的数，下面对于$a[i]$而言，$Mx=\max(a[i+1],a[i-1]).Min=\min(a[i+1],a[i-1]).$

考虑修改$a[i]$有几种可能：要不然与左右两边一者相等，要不然大于最大值，要不然小于最小值，要不然在它们中间。

而且它只影响它周围的两个点。

于是五种情况分类即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[300010];
inline int low(int i) {
	if(i==1||i==n)return 0;
	if(a[i]<a[i+1]&&a[i]<a[i-1])return 1;
	return 0;
}
inline int high(int i) {
	if(i==1||i==n)return 0;
	if(a[i]>a[i+1]&&a[i]>a[i-1])return 1;
	return 0;
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1; i<=n; ++i)scanf("%d",&a[i]);
		int ans=0;
		if(n==1||n==2){
			cout<<0<<endl;
			continue;
		}
		for(int i=1; i<=n; ++i) {
			if(i==1||i==n)continue;
			if(a[i]>a[i-1]&&a[i]>a[i+1])ans++;
			if(a[i]<a[i-1]&&a[i]<a[i+1])ans++;
		}
		if(ans==0){
			cout<<0<<endl;
			continue;
		}
		int res=ans,G=ans;
		for(int i=1; i<=n; ++i) {
			if(i==1) {
				if(a[1]<a[2]&&a[2]>a[3])res--;
				if(a[1]>a[2]&&a[2]<a[3])res--;
				ans=min(ans,res);
				continue;
			}
			if(i==n) {
				if(a[n-1]<a[n]&&a[n-1]<a[n-2])res--;
				if(a[n-1]>a[n]&&a[n-1]>a[n-2])res--;
				ans=min(ans,res);
				continue;
			}

			int m=min(a[i+1],a[i-1]);
			int f=a[i];
			if(low(i+1)||high(i+1))res--;
			if(low(i-1)||high(i-1))res--;
			if(low(i)||high(i))res--;
			a[i]=m-1;
			res+=low(i)+high(i)+low(i-1)+high(i-1)+low(i+1)+high(i+1);
			ans=min(ans,res);

			res=G;
			a[i]=f;
			if(low(i+1)||high(i+1))res--;
			if(low(i-1)||high(i-1))res--;
			if(low(i)||high(i))res--;
			m=max(a[i-1],a[i+1]);
			a[i]=m+1;
			res+=low(i)+high(i)+low(i-1)+high(i-1)+low(i+1)+high(i+1);
			ans=min(ans,res);
			
			res=G;
			a[i]=f;
			if(low(i+1)||high(i+1))res--;
			if(low(i-1)||high(i-1))res--;
			if(low(i)||high(i))res--;
			a[i]=m-1;
			res+=low(i)+high(i)+low(i-1)+high(i-1)+low(i+1)+high(i+1);
			ans=min(ans,res);
			
			res=G;
			a[i]=f;
			if(low(i+1)||high(i+1))res--;
			if(low(i-1)||high(i-1))res--;
			if(low(i)||high(i))res--;
			a[i]=m;
			res+=low(i)+high(i)+low(i-1)+high(i-1)+low(i+1)+high(i+1);
			ans=min(ans,res);
			
			res=G;
			a[i]=f;
			if(low(i+1)||high(i+1))res--;
			if(low(i-1)||high(i-1))res--;
			if(low(i)||high(i))res--;
			m=min(a[i-1],a[i+1]);
			a[i]=m;
			res+=low(i)+high(i)+low(i-1)+high(i-1)+low(i+1)+high(i+1);
			ans=min(ans,res);
			a[i]=f;
			res=G;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：wmy_goes_to_thu (赞：0)

这里波峰和波谷的定义是严格大于小于，所以等于一边的数是最好的。

我们可以枚举改哪个位置，改成左边的还是右边的，然后因为只会影响旁边的元素，所以可以算一下多了或少了几个。

然后别忘了答案不能是负数。

---

