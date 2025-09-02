# Delete Two Elements

## 题目描述

有一个有 $n$ 个元素的数组 $a$ 。令 $k$ 为所有元素算术平均数。

求删掉其中两个元素后剩下元素算术平均数仍为 $k$ 的方案数。（注：先删掉第 $i$ 个，再删掉第 $j$ 个元素和先删掉第 $j$ 个元素，再删掉第 $i$ 个元素只算一种方案。）

## 样例 #1

### 输入

```
4
4
8 8 8 8
3
50 20 10
5
1 4 7 3 5
7
1 2 3 4 5 6 7```

### 输出

```
6
0
2
3```

# 题解

## 作者：XL4453 (赞：3)

### 解题思路：

对于任意一个数，可以发现如果存在可以使得两者同时删去后数列均值不变，那么这个值是唯一且确定的。

那么就考虑用 map 存储每一个值的数量，然后算出这个值直接统计答案。

---
### 颓式子：

设一共有 $n$ 个数，总和为 $sum$，当前数为 $i$。现在要用这些已知量表示应当删去的数 $x$。

直接列式：$\dfrac{sum}{n}=\dfrac{sum-i-x}{n-2}$。

化简得：$x=\dfrac{2\times sum}{n}-i$。

由于数列中都是整数，当 $\dfrac{2\times sum}{n}$ 不为整数时一定无解。

然后根据上面的思路直接做就行了。

---
### 代码：
```cpp
#include<cstdio>
#include<map>
#define int long long
using namespace std;
int T,n,a[200005],ans,sum;
map <int,int> m;
signed main(){
	scanf("%I64d",&T);
	while(T--){
		m.clear();ans=0;sum=0;
		scanf("%I64d",&n);
		for(int i=1;i<=n;i++)
		scanf("%I64d",&a[i]),sum+=a[i];
		sum*=2;
		if(sum%n!=0){
			printf("0\n");
			continue;
		}
		sum/=n;
		for(int i=1;i<=n;i++){
			ans+=m[sum-a[i]];
			m[a[i]]++;
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
```


---

## 作者：xiaozeyu (赞：3)

简单的 map 应用

题目要求删去两个数字后，剩下的数字的算术平均数不变。

算术平均数就是把每个数加起来，再将这个求出来的和除以数的个数。

显然删去的两个数的平均值跟剩下的一样（跟原来的平均数一样）。

数字大，用 long long 存可以。然后直接算平均数。

可以先判断当平均数不是整数时的无解情况。

然后就只要用一个 map 存一下数字，每次然后遍历有的元素就行了。

---

代码

```cpp

#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=a;i<=b;i++)
#define Rep(i,a,b) for(register int i=a;i>=b;i--)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
inline long long lread()
{
    char c=getchar();long long x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
const int mod=998244353;
const int maxn=2e5+10;
const int maxm=3e5+10;
int T,n;
int a[maxn];
long long k,sum;
map<int ,int >m;
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		long long ans=0;sum=0;
		For(i,1,n)
		{
			a[i]=read();
			m[a[i]]++;
			sum+=a[i];
		}
		sum*=2;
		if(sum%n!=0) 
		{
			puts("0");
		}
		else
		{
			k=sum/n;
			For(i,1,n)
			{
				if(k-a[i]!=a[i])
					ans+=m[k-a[i]];
				else ans+=m[k-a[i]]-1;
			}
			ans/=2;
			printf("%lld\n",ans);
		}
		For(i,1,n)
			m[a[i]]--;
	}
	
}

```

感谢洛谷管理员的审核。

---

## 作者：Chenyichen0420 (赞：1)

# 简要题意

给你 $t$ 组数据，每组有一个含有 $n$ 个数的数组。问你有没有办法使得这个数组中删掉两个数，其平均值仍然不变。

# 思路分析

首先我们一定能想到一个思路：一个数去掉后必定要有一个另一个数对平均值作差的值是等于所去掉的数对平均值作差的相反数。

又因为原数组中的每一个数都是整数，因此平均值要有可能满足上述条件则一定为整数或者零点五一类的数。亦即我们将每个数乘 $2$ 的平均值为整数。

这时我们可以再使用 `map` 将每种差值出现的次数记录下来，算到一个差值时先统计情况再进行差值次数加。算平均值时的

总时间复杂度为 $O(t\times n)$，总量为所有 $n$ 的总和。不过稍加注意一下 `map` 还有 $\log n$ 左右的常数。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,a[200005]; long long n,sum;
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n; sum=0;
		for(int i=1;i<=n;++i) cin>>a[i],a[i]*=2,sum+=a[i];
		if((sum/n)*n!=sum){
			cout<<0<<endl;
			continue;
		}
		sum/=n; map<int,int>v;int ans=0;
		for(int i=1;i<=n;++i){
			ans+=v[sum-a[i]];
			v[a[i]-sum]++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 题意
给出一个序列要求去掉任意两个数使得平均值不发生改变。

# 思路
我们通过简单思考就能够知道我们要删掉的数要是我们原本序列的 $2$ 倍才能够让平均数不变，那么我们就可以记录一个数组 `mp`，`mp[i]` 表示 `i` 这个数有 `mp[i]` 个。

那么我们剩下的任务就是遍历每一个在序列里的数然后计算能够和其的总和等于 $2$ 倍平均值的数就行了。

最后提醒几点：
- 因为数组开不了那么大，这里统计用了 `map`。
- 记得开 `long long`。
- 这里枚举序列里的数时，枚举到的数是平均值的一半要记得统计的时候把它自己减掉。
- 因为选第 $i$ 个数和第 $j$ 个数是一样的，最后要记得除以 $2$。
- 多测别忘了清空。

该说的都说了剩下的就是代码了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
map<i64, int> mp;
i64 a[maxn];
void solve() {
	i64 n, sum = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
		mp[a[i]]++;
	}
	sum *= 2;
	if (sum % n != 0) {
		cout << "0\n";
	} else {
		sum /= n;
		i64 ans = 0;
		for (int i = 1; i <= n; i++) {
			if (mp.count(sum - a[i])) {
				if (sum - a[i] == a[i]) {
					ans += mp[sum - a[i]] - 1;
				} else {
					ans += mp[sum - a[i]];
				}
			}
		}
		cout << ans / 2 << "\n";
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		solve();
		mp.clear();
	}
	return 0;
}
```

---

## 作者：洛桃 (赞：0)

## 思路

首先要发现一个结论，那就是若剩下的数平均值仍然为 $k$ ，则去掉的这两个数的平均值必定为 $k$ 。这个结论稍微思考一下应该就可以明白。

然后我们会发现，由于输入的数都是整数，所以若答案非 $0$ ，则 $k*2$ 必为整数，才能使找到的两个数平均值为 $k$。

于是我们先把这种情况考虑完，再用一个整数类型的 $kk$ 来存下之前double类型的 $k$ 。记得 $k$ 要变为两倍再去考虑，此时的 $kk$ 是平均值的两倍。

之后我们就该考虑如何统计答案。我们要找的实际上是有多少对不重复的 $(i,j)$
，能使 $a_i+a_j=kk$ 。因此我们先扫一遍给出的序列，将值大于kk的都去掉，并用一个新的数组b存下来。接着我们对数组b进行排序，好使我们后续操作可以顺利进行。

排序之后，就开始遍历数组 $b$ ，统计答案。对于一个数 $b_i$ ,我们就是要找这个数组中 $kk-b_i$ 的个数。一个个找太慢，如果统计值的个数数组开不下，这时我们可以使用二分寻找大于等于 $kk-b_i$ 的位置与大于 $kk-b_i$ 的位置，设为 $l,r$ ，实际的个数就是 $r-l$ 。为了节约时间，我是用STL代替二分。

还有一点细节就是去重。由于数组有序，我们只要统计 $b_i\le kk-b_i$ 时的答案，一旦大于，就可以退出循环。然而有时候会出现 $b_i=kk-b_i$ 的情况，这时我们使用暴力循环统计答案，然后让 $i$ 直接跳到 $r-1$ 的位置，下一次循环直接从 $r$ 开始。实际复杂度并没有增加。

其他更具体的可以看代码。

## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
long long n,t,a[200010],b[200010];
bool ex[200010];
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		long long sum=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]),sum+=a[i];
		double k=(double)sum*2/n;
		if((long long)k/1!=k){
			printf("0\n");continue;
		}
		long long kk=k;
		int tot=0;
		for(int i=1;i<=n;i++)if(a[i]<=kk)b[++tot]=a[i];
		sort(b+1,b+tot+1);
		long long ans=0;
		for(int i=1;i<=tot;i++)
		{
			if(kk-b[i]<b[i])continue;
			int l=lower_bound(b+1,b+tot+1,kk-b[i])-b;
			int r=upper_bound(b+1,b+tot+1,kk-b[i])-b;
			if(kk-b[i]==b[i]){
				for(int j=r-l-1;j>=1;j--)ans+=j;
				i=r-1;continue;
			}
			else ans+=r-l;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Xhesika_Frost (赞：0)

根据我们的数学知识，很容易意识到这个 $k$ 其实就是平均数。那么删除两个数后，数列的平均数不变，这就意味着我们删除的这两个 $a,b$ 满足 $a+b=2*k$ 。

这样解决这一道题只要先求出平均数 $k$ 然后找满足这个关系的数就可以了。

显然 $O(n^2)$ 的暴力是不行的，我们可以统计每一个数的出现次数，然后直接查询对应的 $2*k-a$ 存不存在，然后统计答案。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map> 
#define int long long
using namespace std;
int sum;
int t;
int n;
int a[200005];
map<long long,int> ma;
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		sum=0;
		ma.clear();
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
			sum+=a[i];
			ma[a[i]]++;
		}
		if((2*sum%(n))!=0){
			cout<<0<<endl;
			continue; 
		}
	//	cout<<"F";
		sum=sum*2/n;
		int cnt=0;
		for(int i=1;i<=n;++i){
			if(a[i]*2>sum) continue;
			if(ma.find(sum-a[i])!=ma.end()){
				if(sum!=a[i]*2)
					cnt+=(ma[a[i]]*ma[sum-a[i]]);
				else{
					cnt+=(ma[a[i]]-1)*ma[a[i]]/2; 
				}
				ma[a[i]]=0;
				ma[sum-a[i]]=0;
			//	cout<<cnt<<endl;
			}
		}
		cout<<cnt<<endl;
	} 
	return 0;
}
```

---

## 作者：SegTre (赞：0)

## 题意简述
给定一个 $n$ 个整数的序列，现在要求删去两个数，同时保持序列的平均数不变。

## 思路
设数列和为 $sum$，假设删去 $a_i,a_j$ 而平均数不变，可以得到：

$$\dfrac{sum-(a_i+a_j)}{n-2} = \dfrac{sum}{n}$$

化简得：

$$a_i+a_j = \dfrac{2*sum}{n}$$

于是我们先判断右边是不是整数（不是的话直接输出 $0$），然后统计数列中满足该式的 $a_i,a_j$ 个数。记等式右边为 $k$，我们就要统计满足 $k-a_i=a_j$ 的数对个数。[是不是很眼熟？](https://www.luogu.com.cn/problem/P1102)

直接枚举 $a_i$，统计 $[i+1,n]$ 之间有多少个数是满足条件的累积到答案中。可以先排序再二分查找，具体实现看代码。

## Code
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#define int long long
using namespace std;
inline int read() {
	int res;char c;
	while(!isdigit(c=getchar()));res=c^48;
	while(isdigit(c=getchar())) res=(res<<3)+(res<<1)+(c^48);
	return res;
}
int n,a[200005],sum,x;
signed main() {
	int t=read(),ans;
	while(t--) {
		n=read();
		sum=ans=0;
		for(int i=1;i<=n;++i) {
			a[i]=read();
			sum+=a[i];
		}
		if((2*sum)%n) {
			printf("0\n");
			continue;
		}
		x=2*sum/n;
		sort(a+1,a+n+1);
		for(int i=1,l,r;i<=n;++i) {
			if(x-a[i]>=a[1]&&x-a[i]<=a[n]) {
				l=lower_bound(a+i+1,a+n+1,x-a[i])-a;
				r=upper_bound(a+i+1,a+n+1,x-a[i])-a;
				if(l==r) continue;
				ans+=r-l;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：zplqwq (赞：0)

经典 map 好题。

首先题意应该很清楚了。

他的重点在于:

> 求删掉其中 **两个** 元素后剩下元素算术平均数仍为 $k$ 的方案数

因此我们可以考虑每次枚举每一个数，设为 $x$ 。

我们既然知道了这个数，那么显然的，对应要删除的另外一个数也已经知道了，设为 $y$ 。

假设此时有 $n$ 个数，其总和为 $s$。

那么 $y= \frac{s\times 2}{n}-x$ 。

我们此时判断一下 $y$ 在这个数组里存不存在即可。

因为显然这个数据范围开桶式开不下的，因此我们考虑用 map 。

```cpp

		mp.clear();
		cin>>n;
		ll sum=0;
		ll summ=0;
		ll ans=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum+=a[i];
			++mp[a[i]];
		}
		if((sum*2)% n) 
		{
			puts("0"); 
			continue;
		}
		summ=sum*2/n;
		for(int i=1;i<=n;i++)
		{
			if(summ-a[i]>a[i]) ans+=mp[summ-a[i]];
		}
		if(!(summ%2)) ans+=mp[summ/2]*(mp[summ/2]-1)/2;
		cout<<ans<<endl;
```




---

## 作者：happy_dengziyue (赞：0)

### 1 思路

设数列平均值为 $k$。

设一对方案分别为 $u$ 和 $v$。

很明显，$u+v=k\times2$。

设数列的总和为 $sum$，则 $u+v=sum\times2\div n$。因为 $u$ 和 $v$ 都是整数，所以，如果 $sum\times2\bmod n>0$，则无解。

我们可以将这个数列排序。

现在，我们顺序枚举每一个数字，设这个数为 $u$，另外一个数为 $v$。如果 $u\ge v$，退出循环。

那么，$u$ 对答案的贡献就是数列中 $v$ 的个数。因为 $a[i]\le1\times10^9$，所以不可能计数。

那么，$v$ 的个数就是，第一个大于 $v$ 的数字的位置减去第一个大于等于 $v$ 的数字的位置。考虑二分。

我们还要注意 $u=v$ 的情况。

如果 $sum\equiv0\pmod n$，那么，如果 $u=v$，则必有 $u=v=sum\div n$。

统计数列中 $sum\div n$ 的个数，设为 $cnt$。

则答案还要加上 $cnt\times(cnt-1)\div2$。

输出答案即可。

### 2 代码与记录

一定要开 `long long`，不然你第 $3$ 个点就会炸 `int`。

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 200000
int t;
int n;
long long a[max_n+2];
long long sum;
long long ave;
long long cnt;
long long ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1598C_1.in","r",stdin);
	freopen("CF1598C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		sum=0;
		for(int i=1;i<=n;++i){
			scanf("%lld",a+i);
			sum+=a[i];
		}
		if((sum*2)%n){
			printf("0\n");
			continue;
		}
		ave=sum*2/n;
		sort(a+1,a+n+1);
		ans=0;
		for(int i=1;i<=n;++i){
			long long u=a[i];
			long long v=ave-a[i];
			if(u>=v)break;
			ans+=upper_bound(a+1,a+n+1,v)-lower_bound(a+1,a+n+1,v);
		}
		cnt=0;
		if(ave%2==0)cnt=upper_bound(a+1,a+n+1,ave/2)-lower_bound(a+1,a+n+1,ave/2);
		ans+=(cnt-1)*cnt/2;
		printf("%lld\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/59662612)

By **dengziyue**

---

## 作者：Farkas_W (赞：0)

$$\text{题目大意}$$

$\quad$从 $n$ 个数中删除两个数 $a_i,a_j(i<j)$，且满足平均数不变，问有多少种删法?

$$\text{思路}$$

$\quad$设原数列的平均数为 $k$，且删除 $a_i,a_j$ 后平均数不变，可得：

$$\frac{a_i+a_j}{2}=k $$

$\quad$又 $\because a_i,a_j$ 为整数，$\therefore k\times 2$ 为整数，若 $k$ 不符合这条件就直接输出 $0$。

$\quad$显然开个桶计数即可，即：

$$ \left\{
\begin{aligned}
& ans+=num[x]\times num[y],& ,x+y=k\times2\\
& ans+=num[x]\times (num[x]-1)/2& ,x=k
\end{aligned}
\right.
$$

$\quad$依次统计答案即可，时间复杂度 $O(n\log n)$ (使用 $map$ 作为桶)，记得每次统计完要清零，防止多次统计。

$\quad$这里还有另一种思路，可以直接排序，然后两个指针从一头一尾向中间跑，每次处理一段相同的值，或者用结构体，一维存大小，一维存数量，再排序，时间复杂度也是 $O(n\log n)$。

注意：开 long long，多组数据清空数组。

```cpp
const int N=2e5+5;
int T,n,a[N],k,ans;
map<int,int>b;
signed main()
{
	T=read();
	while(T--){
		n=read();a[0]=0;ans=0;
		for(re i=1;i<=n;i++)a[i]=read(),a[0]+=a[i],b[a[i]]++;
		if(a[0]*2%n!=0){for(re i=1;i<=n;i++)b[a[i]]=0;puts("0");continue;}
		k=a[0]*2/n;
		for(re i=1;i<=n;i++)
		{
			int x=a[i],y=k-x;
			if(b[x]==0)continue;
			if(x==y){ans+=(long long)(b[x]-1)*b[x]/2;b[x]=0;}
			else ans+=(long long)b[x]*b[y],b[x]=b[y]=0;
			if(b[x])b[x]=0;
		}
		print(ans);putchar('\n');
	}
	return 0;
}
```

---

