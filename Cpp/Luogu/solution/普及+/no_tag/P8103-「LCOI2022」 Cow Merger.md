# 「LCOI2022」 Cow Merger

## 题目背景

Bessie 来到她的新家之后，Farmer John 突然意识到自己农场的大小不够了！

所以，Farmer John 需要把所有的奶牛合并到一个牛棚里。

## 题目描述

Farmer John 的农场里本来有 $n$ 个牛棚，第 $i$ 个牛棚里住着 $a_i$ 只牛。

我们定义一次合并 $i,j(a_i\ge a_j)$ 两个牛棚的操作为：从 $i$ 号牛棚中拿出 $a_j$ 头牛，放入 $j$ 号牛棚中。如果在合并结束后 $a_i=0$，那么可以看做 $a_i$ 被合并了，接下来的操作也与 $a_i$ 无关。

由于时间不够了，他决定最多你 $1$ 秒的时间。

## 说明/提示

【数据范围与约定】

对于 $100\%$ 的数据，$1 \leq T \leq 5$，$1 \leq n \leq  10^5$，$0 \leq a_i \leq 10^9$。

## 样例 #1

### 输入

```
3
4
1 2 3 2
5
3 9 6 18 12
5
2 3 5 7 11```

### 输出

```
YES
4
3 1
1 2
3 4
2 4
YES
6
2 1
1 2
4 3
2 3
4 5
3 5
NO```

# 题解

## 作者：猫猬兽 (赞：4)

### Part 1 

**判断可行性**

我们先把所有数除以他们的最大公约数，考虑到答案一定是一个数翻倍得到的，所以此时如果所有数的和是 $2$ 的整数幂次，则有解，否则无解。

### Part 2 

**构造方案**

考虑到如果所有数的和大于 $1$，则必有偶数个奇数，将它们两两配对操作，则所有数都变为偶数。我们再把所有数除以他们的最大公约数，重复上述操作，直至序列中只剩下 $1$。

### Part 3

**代码**
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,i,t,k,a[100001],b,c,d,m,l[1000001],r[1000001];
int main()
{
	scanf("%lld",&t);
	for(k=1;k<=t;k=k+1)
	{
		scanf("%lld",&n);b=0;c=0;d=0;
		for(i=1;i<=n;i=i+1)
		{
			scanf("%lld",&a[i]);
			b=__gcd(b,a[i]);
		}
		for(i=1;i<=n;i=i+1)a[i]=a[i]/b;
		for(i=1;i<=n;i=i+1)c=c+a[i];
		for(i=1;;i=i*2)
		{
			if(i>c){d=1;break;}
			if(i==c)break;
		}
		if(d==1){printf("NO\n");continue;}
		else
		{
			printf("YES\n");m=0;
			while(1)
			{
				b=0;c=0;d=0;
				for(i=1;i<=n;i=i+1)
				{
					if(a[i]%2==1)
					{
						c=c+1;
						if(c==2)
						{
							m=m+1;c=0;
							if(a[i]>a[d]){l[m]=i;r[m]=d;a[i]=a[i]-a[d];a[d]=a[d]*2;}
							else {l[m]=d;r[m]=i;a[d]=a[d]-a[i];a[i]=a[i]*2;}
						}
						else d=i;
					}
				}
				if(c==1)break;
				for(i=1;i<=n;i=i+1)b=__gcd(b,a[i]);
				for(i=1;i<=n;i=i+1)a[i]=a[i]/b;
			}
			printf("%lld\n",m);
			for(i=1;i<=m;i=i+1)printf("%lld %lld\n",l[i],r[i]);
		}
	}
	return 0;
}
```


---

## 作者：little_cindy (赞：1)

## 思路
我们可以思考一下：最后的答案一定是一个数翻倍（多次）得到的。所以，我们先把和统计出来，再把这个和一直分解 $2$ 直到不能再分解为止。将所有的 $a_i(1\le i\le n)$ 除以这个数，便可以将 $a_i$ 化到最简。

我们考虑一下目标：只要数组 $a$ 中只剩下一个元素即可。

而每次变化是翻倍，所以我们需要尽可能的分解 $2$，但由于每次需要把全部都分解，所以必须全是偶数。所以很容易就可以想出：由于奇数减奇数为偶数，奇数乘 $2$ 为偶数，把两个奇数进行一次操作，就可以把他们变成偶数。

我们用一个变量 $last$ 表示当前的变量表示数组中上一个奇数的下标。每次把奇数下来，再进行操作，记录两个值的编号。

接下来像上面说的那样，全部除 $2$。如果和为 $1$，则说明所有的奶牛已经合并在了一起。输出答案即可。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=100005;
ll n,a[N],ansx[N*10],ansy[N*10],tot;
template <typename T> inline void read(T& x) {
	x=0;T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=x*f;
	return;
}
template <typename T,typename ...Arg>void read(T& x,Arg& ...arg){
	read(x);
	read(arg...);
}
template <typename T>inline void write(T x) {
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
template <typename T,typename ...Arg>void write(T& x,Arg& ...arg){
	write(x);
	putchar(' ');
	write(arg...);
}
void solve(){
	read(n);
	for(ll i=1;i<=n;i++){
		read(a[i]);
	}
	ll sum=0;
	for(ll i=1;i<=n;i++){//获取a[i]数组的和
		sum+=a[i];
	}
	while(sum%2==0){//找到a[i]数组除去因数2后的结果
		sum/=2;
	}
	for(ll i=1;i<=n;i++){
		if(a[i]%sum!=0){//判断该数是否不为sum的倍数（此处其实是判断该数是否能通过翻2倍得到总和的倍数）
			puts("NO");//如果不能得到，说明本组数据无法得到结果，输出NO并换行
			return;
		}
		a[i]/=sum;//将a[i]改成sum的倍数（带着sum倍也没用）
	}
	puts("YES");//满足条件，输出YES并换行
	tot=0;//组合的次数清零
	ll sigma=0;
	while(sigma!=1){//一直执行直到数列中只有一个数（最开始的sum是总和一直除2，所以只要一个时候a[i]中有且仅有1个1，那么这个数如果不除2一定是Σa[i]）
		ll last=0;//这个值表示数组中上一个奇数的下标
		for(ll i=1;i<=n;i++){//这里将所以数操作为偶数
			if(a[i]%2==1){//如果当前数为奇数
				if(last==0){//如果没有上一个奇数（或是已经匹配）
					last=i;//将当前下标设为下一个奇数的last
				}
				else{//如果又上一个奇数可以匹配
					ll x=last,y=i;//用两个数记录last和i的值
					if(a[x]<a[y]){//将a[x]和a[y]从大到小排序
						ll t=x;
						x=y;
						y=t;
					}
					tot++;//记录组合
					ansx[tot]=x;
					ansy[tot]=y;
					a[x]-=a[y];//做操作
					a[y]*=2;
					last=0;//已经使用当前的last和i，于是将last设为0
				}
			}
		}
		for(ll i=1;i<=n;i++){//将所有数除以2，方便下一次操作
			a[i]/=2;
		}
		sigma=0;//清零和的计数器
		for(ll i=1;i<=n;i++){
			sigma+=a[i];//统计Σa[i]
		}
	}
	write(tot);
	puts("");//输出操作次数
	for(ll i=1;i<=tot;i++){
		write(ansx[i],ansy[i]);
		puts("");//输出对应的x,y
	}
	return;
}
int main(){
	ll T;
	read(T);//多组数据
	while(T--){
		solve();
	}
	return 0;
}	
```

---

## 作者：BDFZ_hym_AK_hym_ing (赞：0)

### 题意分析：
题目已知有一个长度为 $n$ 的数列 $a$，且可以进行合并操作，求是否能合成唯一一个数，如可以，则给出操作。  
**合并操作：**
对于 $a_i,a_j$（$1\le i,j \le n,a_i\ge a_j$），使 $a_i \gets a_i-a_j,a_j \gets a_j+a_j$，且当 $a_i=0$ 时，相当于将 $a_i$ 删除（此题下标不变，可见样例，有些题目会改变下标，需要小心）。
### 做题思路：
首先我们先来分析一下 $a_i,a_j$ 的奇偶性。  
$1$：$a_i \bmod 2 =0,a_j \bmod 2 =0$。  
此时 $a_i$ 将变成 $a_i-a_j$，为偶数，$a_j$ 将变成 $a_j+a_j$，为偶数，所以不变。  
$2$：$a_i \bmod 2 =0,a_j \bmod 2 =1$。  
此时 $a_i$ 将变成 $a_i-a_j$，为奇数，$a_j$ 将变成 $a_j+a_j$，为偶数，所以不变。  
$3$：$a_i \bmod 2 =1,a_j \bmod 2 =0$。  
此时 $a_i$ 将变成 $a_i-a_j$，为奇数，$a_j$ 将变成 $a_j+a_j$，为偶数，所以不变。  
$4$：$a_i \bmod 2 =1,a_j \bmod 2 =1$。  
此时 $a_i$ 将变成 $a_i-a_j$，为偶数，$a_j$ 将变成 $a_j+a_j$，为偶数，所以减去两个奇数，增加两个偶数。  
**综上所述**：当且仅当 $a_i \bmod 2 =1,a_j \bmod 2 =1$ 时，整体的奇偶性将会被改变。

因为我们要使最后只剩一个数，且这个数被合并而来（应该为偶数），所以我们应该将奇数两两配对并消除。  
但当一轮消除完后，所有数都为偶数，无法按照上述方法消除，所以我们可将这个数列除以最大公因数，创造出新的奇数以合并、消除。  
当场上有且仅有一个奇数时，无法配对消除，此时无解。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long sz,wz;
};
bool cmp(node a,node b){
	return a.sz<b.sz;
}
long long t;
long long n;
long long a[100005];
vector<node>odd;
long long len;
long long ans[2500005][2];
int main(){

	ios::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	cin>>t;
	while(t--)
	{
		odd.clear();
		len=0;
		cin>>n;
		long long i,sum=0;
		for(i=1;i<=n;i++)
		{
			cin>>a[i];
			sum+=a[i];
			if(a[i]&1)
			{
				odd.push_back(node{a[i],i});
			}
		}
		if(sum<=1)
		{
			cout<<"YES\n0\n";
			continue; 
		}
		sort(odd.begin(),odd.end(),cmp);
		bool flag=false;
		while(sum>1)
		{
			if(odd.size()==1)
			{
				cout<<"NO\n";
				flag=true;
				break;
			}
			for(i=0;i<odd.size()/2;i++)
			{
				a[odd[i*2+1].wz]-=a[odd[i*2].wz];
				a[odd[i*2].wz]*=2;
				len++;
				ans[len][0]=odd[i*2+1].wz;
				ans[len][1]=odd[i*2].wz;
			}
			long long gcd=0;
			for(i=1;i<=n;i++)
			{
				if(a[i]!=0)
				{
					if(gcd==0)
					{
						gcd=a[i];
					}
					else
					{
						gcd=__gcd(gcd,a[i]);
					}
				}
			}
			odd.clear();
			sum=0;
			for(i=1;i<=n;i++)
			{
				a[i]/=gcd;
				sum+=a[i];
				if(a[i]&1)
				{
					odd.push_back(node{a[i],i}); 
				}
			}
			sort(odd.begin(),odd.end(),cmp);
		}
		if(flag)
		{
			continue;
		}
		cout<<"YES\n";
		cout<<len<<"\n";
		for(i=1;i<=len;i++)
		{
			cout<<ans[i][0]<<" "<<ans[i][1]<<"\n";
		}
	}

	return 0;
}
```

---

