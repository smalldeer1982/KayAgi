# Make Array Good

## 题目描述

我们称一个长度为 $m$ 序列 $b$ 是好的，当且仅当对于每一个二元组 $i,j \in [1,m]$，都有 $\min(b_i,b_j) | \max(b_i,b_j)$。

其中 $|$ 表示整除，即 $a|b$ 表示 $a$ 被 $b$ 整除。

接下来给定一个长度为 $n$ 的序列 $a$。

你可以对他进行以下操作：

- 选择 $i(1 \le i \le n)$ 和一个非负整数 $x(0 \le x \le a_i)$，将 $a_i$ 变成 $a_i+x$。

- 你应该保证在操作后 $a_i \le 10^{18}$。

你需要使用最多 $n$ 个操作，使得 $a$ 序列成为一个好的序列，可以证明一定是可以构造出来的。

请输出构造方案。

## 样例 #1

### 输入

```
4
4
2 3 5 5
2
4 8
5
3 4 343 5 6
3
31 5 17```

### 输出

```
4
1 2
1 1
2 2
3 0
0
5
1 3
1 4
2 1
5 4
3 7
3
1 29
2 5
3 3```

# 题解

## 作者：cjh20090318 (赞：5)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

给定 $n$ 个数 $a_i$，你可以进行下面这个操作**至多** $n$ 次（当然也可以一次也不执行），让 $a$ 数组中的每一个数成倍数关系：

- 将 $a_i$ 赋值为 $a_i+x$，其中 $x$ 为一个不超过 $a_i$ 的非负整数，还需要保证修改后的 $a_i \le 10^{18}$。

## 分析

在 $a_i \sim 2a_i$ 中，必定存一个 $2$ 的整次幂，所以我们只需要将每个 $a_i$ 修改为最小的不小于 $a_i$ 的 $2$ 的整次幂，即可保证两两之间为倍数关系。

看到另外一篇题解是使用的循环来找到这个值，我使用的是更加简洁的数学方法，这个值为：

$$2^{\lceil \log_2 a_i \rceil}$$

所以可以直接用位移和数学函数即可解决问题。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
int n,a[100001];
int main(){
	int t;scanf("%d",&t);
    while(t--){
    	scanf("%d",&n);
    	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    	printf("%d\n",n);//每个数都进行一个操作，如果不需要则进行一个加 0 的操作。
    	for(int i=1;i<=n;i++) printf("%d %d\n",i,(1<<((int)ceil(log2(a[i]))))-a[i]);//用这个式子求解上述的值。
    }
	return 0;
}
```

---

## 作者：FQR_ (赞：4)

## 思路

题目中存在条件：$0 \le p\le n$，因此我们可以把所有数字都修改一次。

题目中规定，任意两个数都是倍数关系。我们便可以将每个数变成 $2^k$（$k$ 为非负整数）。

题目中还说，$0 \le x \le a_i$，所以，一定可以将 $a_i$ 加上一个数字，使它变为 $2^k$。

找到大于 $a_i$ 的最小的 $2^k$，使 $a_i$ 变成这个数字即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
	int n;cin>>n;
	cout<<n<<endl;
	for(int i=1;i<=n;i++)
	{
		int x;cin>>x;
		int k=1;
		while(k<=x) k*=2;//找到大于a[i]，最小的2^k
		cout<<i<<" "<<k-x<<endl;//将a[i]加上k-a[i]，此时a[i]变为k
	}
	
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--) solve();
	return 0; 
}
 
```

---

## 作者：szh_AK_all (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1762B)

## 题意加分析
有一个长度为 $n$ 的序列，我们要将每个元素进行一次调整，也就是将每个元素扩大到不超过自身两倍的数，最后让序列中的每两个数都成倍数关系。

既然让每两个数都成倍数关系，那么序列中的所有元素肯定都有一个公约数，我们为了满足“将每个元素扩大到不超过自身两倍的数”这一条件，尽量让这个公约数最小，也就是 $2$。但是，仅仅让每个数都是 $2$ 的倍数是不行的，举个例子：有两个数，第一个数为 $4$，另一个数为 $6$，他们都是 $2$ 的倍数，但不成倍数关系。所以，为了让每个数都成倍数关系，我们将他们都扩大为 $2$ 的整数次幂。这个很好证明，假设一个数为 $2$ 的 $k$ 次方，另一个数为 $2$ 的 $m$ 次方（第一个数大于第二个数），则第一个数除以第二个数等于 $2$ 的 $k-m$ 次方，为整数，且没有余数，则第一个数可以整除第二个数。

有了以上想法，代码便很容易写出来了，由于每次操作是让元素扩大，所以我们将每个元素扩大为大于这个元素的 $2$ 的整数次幂。

## Code
```c
#include<iostream>
using namespace std;
int a[100005];
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n;
        cin>>n;
        for(int j=1;j<=n;j++)
        cin>>a[j];
        cout<<n<<endl;
        for(int j=1;j<=n;j++)
        {
            int tmp=1;
            while(1)
            {
                tmp*=2;
                if(tmp>a[j])
                break;
            }
            cout<<j<<" "<<tmp-a[j]<<endl;
        }
    }
}
```


---

## 作者：郑朝曦zzx (赞：1)

### 题解
很巧妙的一个题目

- 引理：对于任意正整数 $x$，在 $x$ 到 $2x$ 中一定有一个 $2$ 的整数次幂

证明：把 $x$ 二进制分解，最高位的 $1$ 所对应的数的位值乘 $2$ 就在 $x$ 与 $2x$ 之间。

然后就很简单了，由于题目没要求操作数最小，我们把每个数都转换成大于等于它的最小 $2$ 的整数次幂即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pf printf
#define test int T = rd(); while (T--)
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define fr freopen("input.txt", "r", stdin);
#define IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define yes printf("YES\n");
#define no printf("NO\n");
#define int long long
inline int rd()
{
    char c=getchar(); int x=0, s=1;
    while(c<'0'||c>'9') { if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<= '9') { x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*s;
}
signed main()
{
	test
	{
		int n = rd(); printf("%lld\n", n);
		F(i, 1, n)
		{
			int x = rd(); int k = log2(x) + 1;
			printf("%lld %lld\n", i, (1 << k) - x);
		}
	}
    return 0;
}
```


---

## 作者：loser_seele (赞：1)

走了一圈没发现用我这个奇怪思路的啊。

第一次没看题，以为 $ x $ 可以是任意值，所以全部修改为最大值即可。但这样没法保证 $ x \leq a_i $。

于是从序列中的最小值入手，思考序列中的数会被修改为什么形式。

观察到加操作不可能使得一个数超过自己的两倍，否则不得不在这个数上使用超过一次操作，总操作次数就不够用了。

于是找到序列中的最小值，每次将最小值倍增，设当前最小值为 $ x $，倍增后为 $ 2x $，然后将所有位于区间 $ [x,2x] $ 内的数修改为 $ 2x $ 即可。

分析这样为什么是对的：首先可以保证每个数只用一次操作，因为只有在 $ x \leq a_i \leq 2x $ 的情况下才会执行修改操作。

然后序列中的所有数显然都可以写成 $ x \times 2^i $ 的形式，而 $ 2 $ 的幂之间显然两两整除。

时间复杂度 $ \mathcal{O}(n\log{\max{a_i}}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read() 
{
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') 
	{
		if (ch=='-') 
		f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') 
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n) 
{
	int f[2000020];
	for (int i=1;i<=n;i++)
	f[i]=i;
	do 
	{
		if(0)//add something here.
		ans++;
	}
	while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
bitset<2000020>vis;
signed main() 
{
	int T;
	cin>>T;
	while(T--) 
	{
		int n;
		cin>>n;
		int sum=0,minn=2e9;
		for (int i=1;i<=n;i++)
		cin>>a[i],minn=min(minn,a[i]),vis[i]=0;
		vector<int>ans;
		while(minn<=2e9) 
		{
			for (int i=1;i<=n;i++)
			if(a[i]<=minn&&!vis[i])
			ans.push_back(i),ans.push_back(minn-a[i]),vis[i]=1;
			minn*=2;
		}
		cout<<ans.size()/2<<'\n';
		for (int i=0;i<ans.size();i+=2)
		cout<<ans[i]<<' '<<ans[i+1]<<'\n';
	}
}
```


---

## 作者：FSHYLHX (赞：0)

# 题目大意
我们可以给每个数都加上 $x$，要求 $x$ 必须小于这个数，并且全部修改完之后，这个数组中任意两个数都存在倍数关系，求每个数要加上多少。
# 思路分析
因为这道题可能有多个答案，所以我们只要将每个数都修改一遍即可，因为要求存在倍数关系，我们不妨让数组中的每个数都变成大于这个数的第一个 $2$ 的整数次幂，然后输出这个 $2$ 的整数次幂减去它原本的数即可。
# 代码实现
```c
#include<bits/stdc++.h>
using namespace std;
int i,j,k,m,n,ans,sum,t,l; 
int a[100005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++) scanf("%d",&a[i]);
		printf("%d\n", n);
		for(int i=1; i<=n; i++){
			ans = 1;
			while(ans <= a[i]) ans *= 2;
			printf("%d %d\n", i, ans-a[i]);
		}
	}
	return 0;
}
```


---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1762B)

本题简单，故不带任何废话。

我们先分析一下题意：

给定一个长度为 $n$ 的数组 $a$，你可以对这个序列中的第 $i$ 个数进行以下操作：

- 任意选一个**非负整数** $x$，将 $a_i$ 变为 $a_i+x$。

- 注意改变后的 $a_i$ 不能超过 $10^{18}$。

你可以至多执行操作 $n$ 次，执行完的数组需要满足从中选出任意两个数，他们是倍数关系。请你输出**操作次数**，**每次操作的第几个数**，**要加的数**。

**注意本题多测**。

首先这道题答案只要符合就能过，所以操作次数可以直接无脑输出 $n$，也就是对数组中每个数进行操作。

其次也是操作的第几个数。这我们就直接从 $1$ 输出到 $n$ 就可以了，道理同上。

**最后，也是最最重要的一环**，我们要求出加的数 $x$。

作为构造题，我的第一反应是排序后将最小的数翻 $2$ 的几次幂。但由于要输出编号，数组不能乱排序，这种方案不可行。

进一步思考后发现:我们是不是可以直接将数组中的数**变为** $2^n$ 的形式呢。这样**就能满足条件并防止排序的出现**。

沿着这个思路继续：在 $a_i$ 和 $2 \times a_i$ 之中，肯定有 $2$ 的几次幂，我们不妨将其搜出来，这样输出的 $x$ 就为这个搜出来的 $2$ 的次幂减去 $a_i$。

大功告成，上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[114514];
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		cout<<n<<endl;
		//找大于a且小于2a的2的幂次方
		for(int i=1;i<=n;i++)
		{
			int k=1;
			while(k<=a[i])k*=2;
			cout<<i<<" "<<k-a[i]<<endl;
		}
	}
	return 0;
}
```
拜拜！

---

## 作者：sdjgxl666 (赞：0)

# 大概题意
给定 $n$ 个数 $a_1 ∼ a_i$，最多修改 $n$ 次，修改方式为将 $a_i$ 修改为  $a_i ∼ a_i\times2$ 的任意一个数。
# 思路
不难发现，$a_i ∼ a_i\times2$ 之间必有一个 $2$ 的整数次幂（可以去网上搜）那么，我们可以将每个数都改为 $\ge a_i$ 的最接近的 $2$ 的整数次幂，而修改次数最多为 $n$ 次，是肯定够的。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
long long a[100005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);//输入
		printf("%d\n",n);
		for(int i=1;i<=n;i++)
		{
			int j=1;
			while(j<a[i]) j*=2;//找最接近的2的整数次幂数
			printf("%d %d\n",i,j-a[i]);
		}
	}
	return 0;
}
```

---

## 作者：zzy0618 (赞：0)

### 题目大意

给定一个序列 $b$，可以将每个 $b_i$ 加上 $x$，但是要保证 $0\le x\le b_i$。最终使得 $b$ 数组中的每对数是倍数关系。

### 大体思路

为了实现倍数关系，如果两数不同，那么最小的关系是 $2$ 倍。两数 $2^k$ 与 $2^l$，其中 $k，l$ 是非负整数，那么它们一定存在倍数关系。

在 $b_i$ 至 $2\times b_i$ 中，定存在一个 $2^k$。所以我们可以用一个数组先记录 $2$ 的非负整数次幂（为了查找方便），用上 STL 的 ```lower_bound ``` 查找第一个 $\ge b_i$ 的 $2^k$。输出 $2^k -b_i$。

虽然题目说最终 $b_i\le10^{18}$，但是初始的 $b_i\le10^9$ 所以只用 ```int``` 就够了。

### 完整代码




```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}//快读模板 
int s[32];
signed main(){
	register int t,n,i,x;
	s[0]=1;
	for(i=1;i<=30;i++){
		s[i]=s[i-1]<<1;
	}//计算 2 ^ k  
	t=read();
	while(t--){
		n=read();
		printf("%d\n",n);//直接输出 n 
		for(i=1;i<=n;i++){
			x=read();
			int l=lower_bound(s,s+31,x)-s;//查找 
			printf("%d %d\n",i,s[l]-x);
		}
	}
	return 0;
}
```


---

