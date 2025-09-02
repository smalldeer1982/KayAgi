# Array Cloning Technique

## 题目描述

You are given an array $ a $ of $ n $ integers. Initially there is only one copy of the given array.

You can do operations of two types:

1. Choose any array and clone it. After that there is one more copy of the chosen array.
2. Swap two elements from any two copies (maybe in the same copy) on any positions.

You need to find the minimal number of operations needed to obtain a copy where all elements are equal.

## 说明/提示

In the first test case all elements in the array are already equal, that's why the answer is $ 0 $ .

In the second test case it is possible to create a copy of the given array. After that there will be two identical arrays:

 $ [ \ 0 \ 1 \ 3 \ 3 \ 7 \ 0 \ ] $ and $ [ \ 0 \ 1 \ 3 \ 3 \ 7 \ 0 \ ] $

After that we can swap elements in a way so all zeroes are in one array:

 $ [ \ 0 \ \underline{0} \ \underline{0} \ 3 \ 7 \ 0 \ ] $ and $ [ \ \underline{1} \ 1 \ 3 \ 3 \ 7 \ \underline{3} \ ] $

Now let's create a copy of the first array:

 $ [ \ 0 \ 0 \ 0 \ 3 \ 7 \ 0 \ ] $ , $ [ \ 0 \ 0 \ 0 \ 3 \ 7 \ 0 \ ] $ and $ [ \ 1 \ 1 \ 3 \ 3 \ 7 \ 3 \ ] $

Let's swap elements in the first two copies:

 $ [ \ 0 \ 0 \ 0 \ \underline{0} \ \underline{0} \ 0 \ ] $ , $ [ \ \underline{3} \ \underline{7} \ 0 \ 3 \ 7 \ 0 \ ] $ and $ [ \ 1 \ 1 \ 3 \ 3 \ 7 \ 3 \ ] $ .

Finally, we made a copy where all elements are equal and made $ 6 $ operations.

It can be proven that no fewer operations are enough.

## 样例 #1

### 输入

```
6
1
1789
6
0 1 3 3 7 0
2
-1000000000 1000000000
4
4 3 2 1
5
2 5 7 6 3
7
1 1 1 1 1 1 1```

### 输出

```
0
6
2
5
7
0```

# 题解

## 作者：xzyg (赞：3)

## 题意简述

给定长度为 $n$ 的数组 $a$。

- 操作 1：从已有的数组里复制一份

- 操作 2：从已有的所有数组里交换任意两个数的位置

求将一个数组都变为相同的元素所需的的最少步数。

## Sol

设 _操作 1_ 有 $p$ 次，_操作 2_ 有 $q$ 次。

不难发现，最后选定的数在原数组出现次数越多，操作数越少，所以最后数组的元素都为原数组的众数（或之一）。

不妨设原数组中一个众数 $x$ 出现的次数为 $s$。

我们要做的是：复制数组，并使所有 $x$ 交换到同一个数组里。

忽略 $p$ 的值，研究 $q$ 的值。原问题转化为将原数组除 $x$ 以外的数都换为 $x$。

显然在原数组内，除 $x$ 以外的数共有 $n-s$ 个，因此 $ q = n - s $。

同时考虑 $p,q$ 的值。要使 $p$ 的值尽可能小，那么就要使待复制数组中 $x$ 的数量尽可能多。由于 $q$ 的值与操作顺序无关，那么就可以将当前所有 $x$ 转到同一数组内，然后复制该数组，这样就能使得每次复制尽可能多的 $x$。

每次复制都使 $x$ 的总个数乘 2，当 $x$ 的总个数大于等于 $n$ 时停止复制。即 $p$ 为满足 $ s \times 2^p \ge n $ 的最小值。

把 $s$ 除过去，再对不等式两遍取个对数：

$$p \ge \log_2\dfrac{n}{s}$$

将上式化为等式：

$$p = \lceil \log_2\dfrac{n}{s} \rceil$$

答案 $ans = p + q = \lceil \log_2\dfrac{n}{s} \rceil + n - s$

计算众数可以用 map（好像也可以排序+双指针），然后按上面的柿子输出即可。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
#define ll long long

using namespace std;

ll a[100010];

map <ll,ll> f;

int main(){
	ll t;
	cin >> t;
	for(ll i = 1; i <= t; i++){
		memset(a,0,sizeof(a));
		f.clear();
		ll n;
		cin >> n;
		for(ll j = 1; j <= n; j++){
			cin >> a[j];
			f[a[j]]++;
		}
		
		ll s = -1;
		
		for(ll j = 1; j <= n; j++){
			s = max(f[a[j]],s);
		}
        
		// 这里别忘了乘1.0转小数
		cout << ceil(log2(1.0*n/s)) + n - s << endl;
		
	}
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：2)

### 1 思路

很明显，让出现次数最多的数字成为那个“天选之子”是最优的。

那么，首先我们设“天选之子”的出现次数设为 $cnt$。

我们可以发现，我们可以克隆一个数列，然后将这个数列中所有的“天选之子”都复制到原数列上，然后依据原数列再克隆出一个数列……以此类推。

那么，很明显，每克隆并复制一次，“天选之子”个数就会翻倍。那么，克隆次数就是满足 $cnt\times2^i\ge n$ 的最小的非负整数 $i$。并且，复制次数就是 $n-cnt$。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 100000
int t;
int n;
int a[max_n+2];
long long cnt;
long long ans;
long long ma(long long a,long long b){
	return a>b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1665B_1.in","r",stdin);
	freopen("CF1665B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		sort(a+1,a+n+1);
		a[0]=a[1]-2;
		cnt=0;
		for(int i=1,k;i<=n;++i){
			if(a[i]!=a[i-1])k=1;
			else ++k;
			cnt=ma(cnt,k);
		}
		for(int i=0,x=1;;++i,x<<=1){
			if(cnt*x>=n){
				ans=i;
				break;
			}
		}
		ans+=n-cnt;
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/73510227)

By **dengziyue**

---

## 作者：tZEROちゃん (赞：1)

贪心。

记原数组中出现最多的数是 $x$，那么我们就把最终的数组全写 $x$，这样操作数显然是最少的。

我们可以复制一个数组，然后把所有 $x$ 再交换回来，重复这个过程直到原数组所有元素全是 $x$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); i ++)

void solve() {
  int n;
  cin >> n;
  map<int, int> mp;
  rep (i, 1, n) {
    int x; 
    cin >> x;
    ++mp[x];
  }
  int commonTime = 0;
  for (auto i : mp) {
    commonTime = max(commonTime, i.second);
  }
  int ans = 0;
  while (commonTime < n) {
    int d = min(n - commonTime, commonTime);
    ans = ans + d + 1;
    commonTime += d;
  }
  cout << ans << endl;
}

int main(){
  int _; cin >> _; while(_--) {
    solve();
  } 
  return 0;
}
```

---

## 作者：CodeMao (赞：0)

说真的，这道题有点小难度。~~也许是我太弱了~~

**思路**：

- 题目要求我们把所有的数都变成一样的，所以我们很容易想到把所有的数都变成出现次数最多的那个数。
  
- 设此时出现最多的数有 $mxx$ 个，那么我们每次需要复制的数量就为 $\min(n-mxx,mxx)$ 次。
  
- 这里对复制的数量进行解释。原因很简单，因为此时不是出现最多的数的个数可能小于 $\frac{n}{2}$ ，这时只需要加上 $n-mxx$ 即可。
  

**一些细节**：

- 查找出现次数最多的数需要用到 `map` 。不会的请戳这里：[map简介](https://blog.csdn.net/sevenjoin/article/details/81943864)
  
- 在修改 $ans$ 的时候别忘记加上克隆操作的次数 $1$ 。~~因为这个我调了20min~~
  

直接上代码：

```cpp
#include <map>
#include <cstdio>
#define maxn 100005
using namespace std;
map<int,int> mp;
int t,n,x,ans,mxx;
inline int max(int a,int b){ //取两个数中较大的
    return a>b?a:b;
}
inline int min(int a,int b){ //取两个数中较小的
    return a<b?a:b;
}
inline void in(int &a){ ///快速读入
    a=0;char ch=getchar();bool f=0;
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=1;ch=getchar();
    }
    while(ch>='0'&&ch<='9')
        a=(a<<1)+(a<<3)+(ch^48),ch=getchar();
    if(f) a=~a+1;
}
inline void op(int a){ //快输输出
    if(a>9) op(a/10);
    putchar(a%10+'0');
}
int main(){
    in(t); //读入数据组数
    while(t--){
        in(n);mp.clear();ans=0,mxx=-1; //记得初始化map。要么每次初始化map，要么每次新开map。
        for(int i=1;i<=n;++i){  
            in(x);mp[x]++; //统计每个数出现的次数
        }
        map<int,int>::iterator it; //定义迭代器
        for(it=mp.begin();it!=mp.end();++it) //找到出现次数最多的数
            mxx=max(mxx,it->second); 
        while(mxx<n) 
            ans+=min(n-mxx,mxx)+1,mxx+=min(n-mxx,mxx);
        op(ans),puts("");
    }
    return 0;
}
```

---

## 作者：lanretE (赞：0)

这道题的目的是要把所有数变成一样的，那么很容易想到要把所有数变成最开始数组中的众数。

那么如何把所有非众数修改为众数呢？

首先要把所有众数复制一份，操作量为 $1$ 次，记此时众数有 $k$ 个，然后我们就可以把原数组中 $min(n-k,k)$ 个非众数一个一个地与复制数组中的众数交换一遍，其中取最小值是因为到最后时原数组中众数可能会比非众数多，所以这次操作量为 $min(n-k,k)$ 次。

然后由于我们要记录每个数出现次数，题目中又说了 $-10^9\le a_i \le 10^9$，因此使用 map 来记录出现次数。

```
#include<iostream>
#include<map> 
using namespace std;
int a[100010];
map<int,int>cnt;//记录出现个数 
int main(){
	int t; cin>>t;
	while(t--){
		cnt.clear();//注意一定要每次清空
		int n; scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]); ++cnt[a[i]];
		} 
		int maxx=-0x7fffffff,ans=0;
		map<int,int>::iterator it;//指针
		for(it=cnt.begin();it!=cnt.end();++it) maxx=max(maxx,it->second);//用指针访问
		while(maxx<n){
			ans+=min(maxx,n-maxx)+1;
			maxx+=min(maxx,n-maxx);
		}
		printf("%d\n",ans);
	}
    return 0;
}
```



---

## 作者：miao5 (赞：0)

**题意：**

给定一个长度为 $n$ 的数列，每次可以做两种操作：

1. 把当前序列复制一份。
2. 交换任意两份序列中的任意两数。

求最少的操作次数，使得原数列中只含一种数。

**思路：**

因为求最小次数，所以肯定要用原数列中的出现次数最多的数来填充。我们考虑填充流程：设原数列中出现次数最多的数为 $x$，出现了 $y$ 次，那么我们复制一份原数列，把复制数列中的 $x$ 全换回原数列中，这样原数列中就有了 $2\times y$ 个 $x$，之后对更改后的数列执行相同的操作，第 $i$ 次可以增加 $2^i\times y$ 个 $x$。

直接模拟求出即可。

```cpp
#include<iostream>
#include<map>
using namespace std;
map<int,int> vis;
int a[200005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			vis[a[i]]++;
		}
		int x=-1000000009,y=-1;
		for(int i=1;i<=n;i++){
			if(vis[a[i]]>y){
				x=a[i];
				y=vis[a[i]];
			}
		}
		int ans=0;
		int k=y;
		int q=1;
		while(k<n){
			ans++;
			if(k+y*q<=n){
				k=k+y*q;
				ans=ans+y*q;
			}
			else{
				ans=ans+(n-k);
				k=n;
			}
			q=q*2;
		}
		cout<<ans<<endl;
		for(int i=1;i<=n;i++) vis[a[i]]=0;
	}
}
```

---

## 作者：Tx_Lcy (赞：0)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/CF1665B)

题目大意为你每次可以选择两个操作，一个是把当前的数列克隆出一个一模一样的数列。一个是交换之前克隆出的数列和原数列中的任意两个数。求把原数列变成每个数都相同的最小次数。
## 题目思路
首先根据贪心的思路。要找到原数列中出现次数最多的数 $a$，把其它的所有数都改成这个数。
接下来我们就可以开始克隆。
可以肯定的一点是，当一个克隆出来的数列中所有的 $a$ 都被取完后，这个数列就没用了。必须再克隆一个数列。
接下来我们再观察一下，每克隆出一个数列，在原数列中的 $a$ 的个数都会变成原来的两倍，于是我们只要求一个 $\log$ 就好了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e5+10;
int a[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;cin>>t;
	while (t--){
		int n,ans=1;cin>>n;
		for (int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);
		int i=1;
		while (i<n){
			int tf=1,f=0;
			while (a[i]==a[i+1] && i<n) f=1,tf++,i++;
			ans=max(ans,tf);
		    if (!f) i++;
		}
		if (ans==n) cout<<0<<'\n';
		else{
			int k=n/ans;
			if (ans*k<n) k++;
			int kt=log2(k);
			while ((1<<kt)<k) kt++;
			//cout<<k<<' '<<kt<<'\n';
			cout<<n-ans+kt<<'\n';
		}
	}
	return 0;
}
```


---

## 作者：heaksicn (赞：0)

## 1 题意
现在有一个由序列组成的**可重集合** $S$，对于这个 $S$ 有两种操作：

1. 选择一个序列 $S_i$，将其复制一份加入集合 $S$ 中。

2. 对于第 $x$ 个序列的第 $i$ 个数和第 $y$ 个序列的第 $j$ 个数，交换两个数的值。

求最小的操作数使得集合中有一个序列的所有元素都相等。

初始时集合中只有一个长度为 $n$ 的序列 $a$。

多组数据。

## 2 思路
因为只要使一个序列的所有元素相等，那么所有的操作都应该在同一个序列中执行。

为了使操作数最小，最后操作完符合条件的序列的元素在原始序列中出现的次数应该尽量多。

那么，操作可以分为如下几步：

1. 设最终求的序列为 $S_1$。

2. 求出 $S_1$ 中出现次数最多的数 $x$，设它出现了 $y$ 次。

3. 复制一份 $S_1$，记为 $S_2$。

4. 将 $S_2$ 中所有的 $x$ 放到 $S_1$ 中。

5. 此时 $S_1$ 中 $x$ 的个数为 $2y$ 个。

6. 重复第 2 到 5 步的操作，直到 $y\geq n$ 为止。

注意特判原数列已经满足条件的情况。

时间复杂度 $O(Tn)$。

## 3 code
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
map <int,int> mp;
int T,n;
int a[100001]; 
int main(){
	T=read();
	while(T--){
		n=read();
		int maxn=-1;
		for(int i=1;i<=n;i++){
			a[i]=read();
			mp[a[i]+1e9]++;
			maxn=max(maxn,mp[a[i]+1e9]);
		}
		if(n==1||maxn==n){//特判
			write(0);
			puts("");
			for(int i=1;i<=n;i++) mp[a[i]+1e9]--;
			continue;
		}
		int now=maxn;
		int ans=1;
		while(maxn!=n){
			if(maxn+now>=n){//满足条件
				ans+=n-maxn;
				break;
			}else{//倍增
				maxn+=now;
				ans+=now;
				now=maxn;
				ans++;
			}
		}
		write(ans);
		puts("");
		for(int i=1;i<=n;i++) mp[a[i]+1e9]--;
	}
	return 0;
}

```


---

## 作者：EtHereal_Algorithm (赞：0)

## CF1665B Array Cloning Technique
`unordered_map -> map`，`TLE -> 78ms`。

超，`FST` 最后一个点。
## 1.思路
显然，我们的思路就是把最后的序列的每一个元素变成众数。

然后按照题意强行计算即可。
```cpp
while(maxn < n)
	ans = ans + min(n - maxn, maxn) + 1,maxn += min(n - maxn, maxn);
```
这里是核心代码。`maxn` 代表最开始某个众数存在的数量。

注意到，我们每次复制的数量是 `min(n - maxn. maxn)`。

原因很简单：有可能这是最后一次操作，剩下来的非众数小于 $n$ 的一半了，就只需要加上 `n - maxn`。

对于 `ans`，不要忘了每次加上 `clone` 操作的 $1$。
## 2.代码
```cpp
#include <bits/stdc++.h>

//standard

#define up(i,l,r) for(int i=(l);i<=(r);i++)
#define down(i,r,l) for(int i=(r);i>=(l);i--)
typedef long long ll;
using namespace std;

//quick in / out

#define int ll
inline int readl(){
    int f = 1, x = 0;
	char ch;
    do{ch = getchar();if(ch == '-')f = -1;}while(ch < '0' || ch > '9');
    do{x = x * 10 + ch - '0';ch = getchar();}while(ch >= '0' && ch <= '9');
    return f * x;
}
void printl(int x, string aft = ""){
	if(x > 9) printl(x / 10);
	putchar(x % 10 + '0');
	cout << aft;
}
#undef int
inline int read(){
    int f = 1, x = 0;
	char ch;
    do{ch = getchar();if(ch == '-')f = -1;}while(ch < '0' || ch > '9');
    do{x = x * 10 + ch - '0';ch = getchar();}while(ch >= '0' && ch <= '9');
    return f * x;
}
void print(int x, string aft = ""){
	if(x > 9) printl(x / 10);
	putchar(x % 10 + '0');
	cout << aft;
}

//main function

int main() {
	int T = read();
	while(T--)
	{
		int n = read(), x;
		map<int, int> m;//要么就每次清空，要么就每次新定义
		up(i, 1, n) x = read(),m[x]++;//初始化，计算每个数出现了多少次。
		int maxn = -1;
		for(auto it = m.begin();it != m.end();it++)
			maxn = max(maxn, it -> second);//计算 maxn
		int ans = 0;//答案，统计次数
		while(maxn < n)//某个众数的数量没到n的时候就执行。
			ans = ans + min(n - maxn, maxn) + 1,maxn += min(n - maxn, maxn);//强行计算答案，按照题意模拟
		print(ans, "\n");
	}
	return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

[本人的翻译](https://www.luogu.com.cn/paste/bife7cvu)

我们来考虑一下如何贪心地进行操作才能使在操作次数尽可能小的情况下满足题目要求。我们很容易地想到一下操作方式。

- 选中你想让所有元素相同的数组
- 复制一遍该数组
- 找到数组中元素最多的值
- 将你复制的数组中的这些数一个一个交换到你想让所有元素相同的数组中。
- 如果在任何时候当前数组中所有元素相同了，停止，否则继续重复上面的步骤。

我们发现在整个流程中，我们只关注数组中元素最多的值是多少，所以我们只需要记录数组中元素最多的值的数量，然后就可以做到 $O(1)$ 进行一遍上面的步骤了。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
void cf(){
	int n=read();
	map<int,int> mp;
	int a[n+1];
	for(int i=1;i<=n;i++){
		a[i]=read();
		mp[a[i]]++;
	}
	int mx=0;
	for(int i=1;i<=n;i++)
		mx=max(mx,mp[a[i]]);
	int ans=0;
	while(mx<n){
		if(mx*2<=n){
			ans+=mx+1;
			mx*=2;
		}
		else{
			ans+=n-mx+1;
			mx=n;
		}
	}
	printf("%d\n",ans);
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

