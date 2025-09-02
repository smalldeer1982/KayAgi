# Mad MAD Sum

## 题目描述

We define the $ \operatorname{MAD} $ (Maximum Appearing Duplicate) in an array as the largest number that appears at least twice in the array. Specifically, if there is no number that appears at least twice, the $ \operatorname{MAD} $ value is $ 0 $ .

For example, $ \operatorname{MAD}([1, 2, 1]) = 1 $ , $ \operatorname{MAD}([2, 2, 3, 3]) = 3 $ , $ \operatorname{MAD}([1, 2, 3, 4]) = 0 $ .

You are given an array $ a $ of size $ n $ . Initially, a variable $ sum $ is set to $ 0 $ .

The following process will be executed in a sequential loop until all numbers in $ a $ become $ 0 $ :

1. Set $ sum := sum + \sum_{i=1}^{n} a_i $ ;
2. Let $ b $ be an array of size $ n $ . Set $ b_i :=\ \operatorname{MAD}([a_1, a_2, \ldots, a_i]) $ for all $ 1 \le i \le n $ , and then set $ a_i := b_i $ for all $ 1 \le i \le n $ .

Find the value of $ sum $ after the process.

## 说明/提示

In the first test case, $ a=[1] $ initially.

In the first loop:

1. Set $ sum := sum + a_1 = 0+1=1 $ ;
2. Set $ b_1 :=\ \operatorname{MAD}([a_1])=\ \operatorname{MAD}([1])=0 $ , and then set $ a_1 := b_1 $ .

After the first loop, $ a=[0] $ and the process ends. The value of $ sum $ after the process is $ 1 $ .

In the second test case, $ a=[2,2,3] $ initially.

After the first loop, $ a=[0,2,2] $ and $ sum=7 $ .

After the second loop, $ a=[0,0,2] $ and $ sum=11 $ .

After the third loop, $ a=[0,0,0] $ and $ sum=13 $ . Then the process ends.

The value of $ sum $ after the process is $ 13 $ .

## 样例 #1

### 输入

```
4
1
1
3
2 2 3
4
2 1 1 2
4
4 4 4 4```

### 输出

```
1
13
9
40```

# 题解

## 作者：_anll_ (赞：4)

被简单结论题硬控 1h，我真的，糖丸了。

## 思路
拿到题目发现样例都太简单了，模拟不出个所以然，不妨手构一组大一点的样例后进行手模。

$$
1\ 1\ 4\ 2\ 2\ 4\ 9\ 9\ 9\ 0\\
0\ 1\ 1\ 1\ 2\ 4\ 4\ 9\ 9\ 9\\
0\ 0\ 1\ 1\ 1\ 1\ 4\ 4\ 9\ 9\\
0\ 0\ 0\ 1\ 1\ 1\ 1\ 4\ 4\ 9\\
0\ 0\ 0\ 0\ 1\ 1\ 1\ 1\ 4\ 4\\
0\ 0\ 0\ 0\ 0\ 1\ 1\ 1\ 1\ 4\\
0\ 0\ 0\ 0\ 0\ 0\ 1\ 1\ 1\ 1\\
0\ 0\ 0\ 0\ 0\ 0\ 0\ 1\ 1\ 1\\
0\ 0\ 0\ 0\ 0\ 0\ 0\ 0\ 1\ 1\\
0\ 0\ 0\ 0\ 0\ 0\ 0\ 0\ 0\ 1\\
0\ 0\ 0\ 0\ 0\ 0\ 0\ 0\ 0\ 0\\
$$

不难发现，在第一次操作后，序列会变成若干个段内相同的段，在非末尾段中会出一段长度为 $1$ 的情况。

而在第二次操作后，序列内除末尾段以外，所有段的长度都大于 $1$，且变换方案总是整个序列集体往右移 $1$。

因此做法就呼之欲出了。我们可以先暴力这个序列变换两次，从第三次变换开始，每个 $num_i$ 会出现 $n-i$ 次。统计即可。

理论上时间复杂度为 $O(Tn)$，但我实现的时候用了 set 去判是否出现过，因此总时间复杂度为 $O(Tn\log n)$。

## 代码
```cpp
#include<set>
#include<iostream>
#define int long long
using namespace std;
int t,n,sum,num[200005];
set<int> so;
map<int,int> mo; 
void solve(){
	cin>>n;sum=0;int awa=0,len=0,cs=0,las=0,lass=0;so.clear();
	for(int i=1;i<=n;i++) cin>>num[i],sum+=num[i];
	for(int i=1;i<=n;i++){
		if(so.find(num[i])!=so.end()) awa=max(awa,num[i]);
		so.insert(num[i]);num[i]=awa;sum+=awa;
	}
	so.clear();awa=0;
	for(int i=1;i<=n;i++){
		if(so.find(num[i])!=so.end()) awa=max(awa,num[i]);
		so.insert(num[i]);num[i]=awa;sum+=awa;
	}
	for(int i=1;i<=n;i++) sum+=(n-i)*num[i];
	cout<<sum<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
}
```

---

## 作者：GeXiaoWei (赞：2)

# CF1990C Mad MAD Sum
## 解析
本题考察模拟，难度在黄题左右。

读完题后，首先可以想到 $O(Tn^2)$ 的枚举，但是一定会超时。不如观察一下样例，每两次操作之后，数组 $a$ 单调递增。在单调递增的数组中，大小相同的数一定相邻，这时再操作，就等同于删除最后一个数，数组里的第 $i$ 项出现了 $n-i+1$ 次，直接一次计算即可。

时间复杂度为 $O(Tn)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=200005;
long long n,a[N],ans,maxx,t;
bool c[N];
void caozuo(){
    for(int i=1;i<=n;i++) c[i]=0;
    maxx=0;
    for(int i=1;i<=n;i++){
        if(c[a[i]]) maxx=max(maxx,a[i]);
        c[a[i]]=1,a[i]=maxx;
    }
}
int main(){
	scanf("%lld",&t);
    while (t--){
    	scanf("%lld",&n);ans=0;
    	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	    for(int i=1;i<=n;i++) ans+=a[i];
	    caozuo();
	    for(int i=1;i<=n;i++) ans+=a[i];
	    caozuo();
	    for(int i=1;i<=n;i++) ans+=(n-i+1)*a[i];
	    printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：Guchenxi0971 (赞：1)

## Sol

我们先对该序列进行一次操作，可以发现得到的是一个单调不减的序列 $b$，我们先不考虑序列 $b$ 中存在只出现一次的大于 $0$ 的数，（因为对于这种数，在进行一次操作就会消失。）那么我们可以发现，每次操作都会使整个序列向右平移一个位置，然后原来最后的数消失并在前面加入一个 $0$，那么我们就可以拆开算贡献，即第 $i$ 个数的贡献是 $a_i\times (n-i+1)$。但是如果有只出现一次的大于 $0$ 的数怎么办呢？由于其在经过一次就会消失，那么再来一次操作让其消失，只要在最后加上其贡献就行。

## Code

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define int long long
#define mk make_pair
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
using namespace std;
const int Max=2e5+10;
const int mod=998244353;
const int inf=1e9+10;



inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

int a[Max],b[Max];
int vis[Max];

int id=0;

void work(){
	++id;
	int n=read();
	int pos=0;
	int sum=0;
	for(int i=1;i<=n;++i){
		a[i]=read();
		vis[a[i]]=0;
	}
	for(int i=1;i<=n;++i){
		sum+=a[i];
		vis[a[i]]++;
		if(vis[a[i]]>=2){
			if(pos<a[i])pos=a[i];
		}
		b[i]=pos;
		a[i]=b[i];
	}
	//第一次操作 
	int z=0;
	for(int i=1;i<=n;++i){
		vis[b[i]]=0;
	}
	pos=0;
	for(int i=1;i<=n;++i){
		sum+=a[i];
		vis[a[i]]++;
		if(vis[a[i]]>=2){
			if(pos<a[i])pos=a[i];
		}
		b[i]=pos;
	}
	//第二次操作 
	
	for(int i=n;i>=1;--i){
		++z;
		sum=sum+z*b[i];
	}
	//算贡献 
	cout << sum << "\n";
}


signed main(){
	int T=read();
	while(T--)work();

	return 0;
}

```

---

## 作者：__ikun__horro__ (赞：1)

## solution

我们先按照题目意思模拟一轮，不难发现 $a$ 数组会变成单调递增的序列。

---

**证明：**

假设存在一个 $i$（$1 \le i < n$），使 $a_{i}>a_{i+1}$。

$a_{i}$ 在原序列 $1 \sim i$ 中出现次数 $\ge 2$，那么 $a_{i}$ 在原序列 $1 \sim i+1$ 中出现次数也一定 $\ge 2$。

而目前 $a_i$ 表示原序列 $1 \sim i$ 中出现次数 $\ge 2$ 的数字的最大值，所以 $a_{i+1} \ge a_{i}$，矛盾！

因此，对于任意 $i$（$1 \le i < n$），都存在 $a_{i} \le a_{i+1}$。

---

现在，数组变成了类似这种形式：

$$\begin{bmatrix}t_1 & t_1 & \cdots & t_1 & t_2 & t_2 & \cdots & t_2 & \cdots & \cdots & t_m & t_m & \cdots & t_m & t_m\\\end{bmatrix}$$

对于任意 $i$（$1 \le i < n$），$t_i < t_{i+1}$。

现在我们再模拟一遍：

$$\begin{bmatrix}0 & t_1 & t_1 & \cdots & t_1 & t_2 & t_2 & \cdots & t_2 & \cdots & \cdots & t_m & t_m & \cdots & t_m\\\end{bmatrix}$$

对比一下：

$$\begin{bmatrix}t_1 & t_1 & \cdots & t_1 & t_2 & t_2 & \cdots & t_2 & \cdots & \cdots & t_m & t_m & \cdots & t_m & t_m\\0 & t_1 & t_1 & \cdots & t_1 & t_2 & t_2 & \cdots & t_2 & \cdots & \cdots & t_m & t_m & \cdots & t_m\\\end{bmatrix}$$

可以发现每次就是把数字往右移了一格，溢出不算。

特别的，当数组的最后的两个元素与其它都不同：

$$\begin{bmatrix}t_1 & t_1 & \cdots & t_1 & t_2 & t_2 & \cdots & t_2 & \cdots & \cdots & t_{m-1} & t_m & t_m\\0 & t_1 & t_1 & \cdots & t_1 & t_2 & t_2 & \cdots & t_2 & \cdots & \cdots & t_{m-1} & t_{m-1}\\\end{bmatrix}$$

由于 $t_m$ 不足两个，所以会被 $t_{m-1}$ 替换掉。

这样问题就被解决了。

---

## 作者：aulive (赞：1)

# 前言
赛时因为菜导致被此题硬控 $40$ 分钟，写篇题解纪念一下
# Solution
简单手摸一下便可以发现第一次操作之后可以使序列单调不增，第二次操作之后可以使序列中元素的出现次数大于 $1$。
而接下来的操作会使得序列内所有数向右平移一位。
所以暴力进行两次操作后，记录每个元素出现次数和出现次数后缀和计算贡献即可。
# code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5;
int n,m,a[maxn+5],b[maxn+5],x,y,z,num[maxn+5];
string s;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int test;
	cin>>test;
	while(test--){
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)num[i]=0,b[i]=0;
		for(int i=1;i<=n;i++)cin>>a[i],ans+=a[i];
		for(int i=1;i<=n;i++){
			if(num[a[i]]){
				b[i]=max(b[i-1],a[i]);
			}else{
				b[i]=b[i-1];
			}
			num[a[i]]=1;
			ans+=b[i];
		}//第一次操作
		for(int i=1;i<=n;i++)num[i]=0;
		for(int i=1;i<=n;i++){
			if(num[b[i]]){
				a[i]=max(a[i-1],b[i]);
			}else{
				a[i]=a[i-1];
			}
			num[b[i]]=1;
		}//第二次操作
		int cnt=0;
		for(int i=1;i<=n;i++)num[i]=0;
		for(int i=1;i<=n;i++)num[a[i]]++;
		for(int i=n;i>=1;i--){
			if(!num[i])continue;
			if(num[i]==1)ans+=i,cnt++;
			if(num[i]>1){
				ans+=i*(num[i]*(num[i]+1)/2+cnt*num[i]);
				cnt+=num[i];//更新后缀和
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Engulf (赞：1)

考虑先进行一次操作，易发现序列变为单调递增。

考虑对一个单调递增的数列操作后的结果，举个例子（记下面这个数组为 $b$）：

$$[0, 2, 2, 3, 3, 3]$$

操作一次后

$$[0, 0, 2, 2, 3, 3]$$

发现是往右移动了数组，头部用 $0$ 补足，答案就是 $\sum\limits_{i = 1}^{n}b_i \cdot (n - i + 1)$

这仅限每个非 $0$ 的数的出现次数 $\ge 2$ 的时候。

如果有数字只出现了一次：

$$[0, 1, 1, 2, 3, 3]$$

操作后：

$$[0, 0, 1, 1, 1, 3]$$

发现仅出现一次的 $2$ 消失了，取而代之的是它前面的出现多次的 $1$，这里实现的时候先给答案加上这个只出现一次的数 $b_i$，然后直接令 $b_i$ 等于 $b_{i - 1}$，就可以做到用出现多次的数代替之。这样还是觉得乱的话看代码吧。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        ll sum = accumulate(a.begin(), a.end(), 0ll);

        vector<int> cnt(n + 1);
        vector<int> madcnt(n + 1);

        int mad = 0;

        vector<int> b(n);
        for (int i = 0; i < n; i++) {
            cnt[a[i]]++;
            if (cnt[a[i]] >= 2) mad = max(mad, a[i]);
            b[i] = mad;
            madcnt[mad]++;
        }

        for (int i = 0; i < n; i++) {
            if (!b[i]) continue;
            if (madcnt[b[i]] > 1) sum += 1ll * b[i] * (n - i);
            else if (madcnt[b[i]] == 1) {
                sum += b[i] + 1ll * b[i - 1] * (n - i - 1);
                b[i] = b[i - 1];
            }
        }

        cout << sum << "\n";

    }
    return 0;
}
```

---

## 作者：ZhongYuLin (赞：1)

不难想到先按题意模拟进行一轮迭代，使得数组变为若干个段内相等的连续段。然后考虑去对这个东西计算贡献。

模拟易得，每个连续段先缩短左端点，非空且不为最右侧的连续段延伸右端点。发现难以处理消失的段，考虑再迭代一轮，消去之。

于是，题目就变为了：若干个连续段，每次最右侧的连续段长度减一，求全为 $0$ 前的贡献。将前缀和加起来即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+3;
int a[N],b[N],cnt[N];
int n;
ll ans;
ll s[N];
void work(){
    int res=0;
    for(int i=1;i<=n;++i){
        ++cnt[a[i]];ans+=a[i];
        if(cnt[a[i]]>1&&a[i]>res)res=a[i];
        b[i]=res;
    }
    for(int i=1;i<=n;++i)a[i]=b[i],cnt[i]=0;
}
void solve(){
    cin>>n;ans=0;
    for(int i=1;i<=n;++i)cin>>a[i];
    work();work();
    for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i];
    for(int i=n;~i;--i)ans+=s[i];
    printf("%lld\n",ans);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;for(cin>>T;T--;)solve();
    return 0;
}
```

---

## 作者：w9095 (赞：1)

[CF1990C Mad MAD Sum](https://www.luogu.com.cn/problem/CF1990C)

好题。考虑操作一次之后序列的性质，不难发现存在单调性。因为定义为出现至少两次的最大值，而从左到右最大值是可以继承的，所以单升不降。

然后，手玩一下发现之后的操作相当于把整个序列向后移动一位，左边使用 $0$ 自动补齐。特别的，如果一个元素数量不足 $2$ 个，会被左边满足要求的最大值替代。根据位置求出每个元素被计算的次数累加即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,a[300000],c[300000];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	long long sum=0,mx=0;
	   	scanf("%lld",&n);
	   	for(int i=1;i<=n;i++)c[i]=0;
	   	for(int i=1;i<=n;i++)
	   	    {
		    scanf("%lld",&a[i]),sum+=a[i];
		    c[a[i]]++;
		    if(c[a[i]]>=2)mx=max(mx,a[i]);
		    a[i]=mx;
		    }
		mx=0;
	   	for(int i=1;i<=n;i++)c[i]=0;
		for(int i=1;i<=n;i++)
		    if(a[i]!=0)
		       {
		       c[a[i]]++;
		       if(c[a[i]]>=2)mx=max(mx,a[i]);
			   if((a[i]==mx)||(a[i]==a[i+1]))sum+=a[i]*(n-i+1);
			   else sum+=(a[i]+mx*(n-i));
		       }
		printf("%lld\n",sum);
	   }
	return 0;
}
```

---

## 作者：EricWan (赞：1)

这题有点结论题

先讲几个结论：

假如我们现在的数组 $a$ 已经单调不下降，而且除了最后一种元素，其他元素都至少有两个时，那么下一个数组就会成为当前数组后移一位的结果。

我们称满足上面的结论的数组为合法数组，我们可以证明至多两次操作后输入的数组会变成合法数组。

这两个结论证明都不复杂，你可以自己证明。

关于写代码，我有一个比较简便的写法：

```cpp
cin >> n;
maxn = ans = 0;
for (int i = 1; i <= n; i++) {
	cnt[i] = 0;
	cin >> a[i];
	ans += a[i];
}
for (int i = 1; i <= n; i++) { // 模拟第一次操作。
	cnt[a[i]]++;
	if (cnt[a[i]] == 2 && a[i] > maxn) {
		maxn = a[i];
	}
	b[i] = maxn;
}
for (int i = 1; i <= n; i++) { // 模拟第二次操作，因为第一次操作后数组已经不下降，所以第二次操作中只会把只出现一次的元素抹去。
	if (b[i] != b[i - 1] && b[i] != b[i + 1]) {
		ans += b[i];
		b[i] = b[i - 1];
		ans -= b[i];
	}
}
for (int i = 1; i <= n; i++) {
	ans += b[n - i + 1] * i;
}
cout << ans << endl;
```

---

## 作者：CoderMeow (赞：0)

# CF1990C 题解

## 题意简述

给出一个初始数组。重复同时将数组的每一位变为从数组到此为止出现至少两次的数中最大者，直到数组元素全为 $0$。求该过程中每一步得到的数组（包括初始数组）元素和。

## 性质

1. 对于任何数组经过一轮操作后数组元素单调不减。
2. 对于一个单调不减的数组进行一轮操作后得到的数按层级递增，其中除最高层外每一层级的数至少有两个。
3. 对于一个除了最大数外其他数的个数都多于一个的数组进行一轮操作，相当于将其向右平移一格，左侧补 $0$，右侧溢出。

都是显然的。

## 性质的利用

首先，$O(n)$ 模拟一轮操作是容易的。维护一个布尔数组判断一个数是否出现，依次遍历，若当前数大于当前最大数，在布尔数组中查询，未出现过则记录为出现过，否则用当前数替代当前最大数。然后利用性质求解：

输入初始数组，统计元素和。由性质 1，对初始数组模拟一轮操作后得到一个单调不减数组，统计该数组元素和；由性质 2，再模拟一轮操作后得到一个除最大数外其他数的个数都多于一的数组。由性质 3，此时数组中在 $i$ 位置的数字由当前到最终作出贡献为 $a_i \times (n-i)$，依次统计即可。

## Code

依据上一节实现即可。

赛时代码：[Code](https://codeforces.com/contest/1990/submission/271596746)

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[Mad MAD Sum](https://www.luogu.com.cn/problem/CF1990C)

## 分析
模拟一组数据

列表示第 $i$ 次操作前的结果，行表示当前数列，表格只模拟了前五次操作。

|1|1|4|5|1|4|1|9|1|9|8|1|0|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|0|1|1|1|1|4|4|4|4|9|9|9|9|
|0|0|1|1|1|1|4|4|4|4|9|9|9|
|0|0|0|1|1|1|1|4|4|4|4|9|9|
|0|0|0|0|1|1|1|1|4|4|4|4|9|

容易发现第二次操作之后本质归结为了数列整体向右移动。

之后每一个数后面会对结果贡献次数就可以算出来了，

偷懒没用数组存储，细节在此就不赘述了，具体看代码吧。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int hys1[400010],hys2[400010];
signed main() {
//	freopen("mad.in","r",stdin);
//	freopen("mad.out","w",stdout);
	int hys;
	scanf("%lld",&hys);
	while(hys--) {
		int sum=0,a=0,b=0,c=0,n;
		scanf("%lld",&n);
		for(int i=1; i<=n; i++)
			hys1[i]=hys2[i]=0;
		while(n--) {
			scanf("%lld",&a);
			if(hys1[a])b=max(b,a);
			else hys1[a]=1;
			if(hys2[b])c=max(b,c);
			else if(b!=0)hys2[b]=1;
			sum+=a+b+(n+1)*c;
		}
		printf("%lld\n",sum);
	}
	return 0;
}
```


谷的博客改版之后有点不习惯嘞。。。

---

## 作者：ZhaoV1 (赞：0)

### 题目大意
给出一个数组 $a$，每一轮用数组 $b$ 来存 $a$ 的被执行前缀 $ \operatorname{MAD} $ 后的值。具体来说：$b_{i}$ 的值等于 $a_{1}$ 到 $a_{i}$ 区间内满足 $\operatorname{MAD}$ 的值，直到 $b$ 数组中每一个数都为 $0$。

### 解析
经过纸上的小模拟，我们发现以下规律：
```
当 n = 11 时：
a 2 1 1 2 2 3 3 3 2 2 2
b 0 0 1 2 2 2 3 3 3 3 3
  0 0 0 0 2 2 2 3 3 3 3
  0 0 0 0 0 2 2 2 3 3 3
  0 0 0 0 0 0 2 2 2 3 3
  0 0 0 0 0 0 0 2 2 2 3
  0 0 0 0 0 0 0 0 2 2 2
  0 0 0 0 0 0 0 0 0 2 2
  0 0 0 0 0 0 0 0 0 0 2

当 n = 6 时：
a 1 1 2 3 2 3
b 0 1 1 1 2 3
  0 0 1 1 1 1
  0 0 0 1 1 1
  0 0 0 0 1 1
  0 0 0 0 0 1
```
不难发现，在我们按照规则预处理一次之后（即标有 $b$ 的那一行），凡是只出现一次的非零数，在以后都不会出现，而出现一次以上的非零数都将以倒三角或被覆盖，或不被覆盖的形式出现。我们只需特判只出现一次的数，他不在倒三角的考虑范围内，其他的数都看作等差数列做计算即可（维护一个 $last$ 来装存前一个数，在做计算时减去即可）。


AC Code
------------
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int t,n;
int a[N],b[N];
bool vis[N];
void solve(){
	int res = 0;
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		res += a[i];
		vis[i] = false;
	}
	int Max = 0;
	map<int,int> mp;
	for(int i=1;i<=n;i++){
		mp[a[i]]++;
		if(mp[a[i]] == 2 && a[i] > Max){
			Max = a[i];
		}
		b[i] = Max;//预处理
	}
	int last = 0;
	for(int i=1;i<=n;i++){
		if(b[i]){//0不考虑了
			if(i+1 <= n && !vis[b[i]] && b[i] != b[i+1]){
				res += b[i] - last;
				continue;
			}//跳过

			if(!vis[b[i]]){
				vis[b[i]] = true;
				res += b[i]*(n-i+1+1)*(n-i+1)/2 - last*(n-i+1+1)*(n-i+1)/2;
				last = b[i];
			}
		}
	}
	cout << res << '\n';
	mp.clear();
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}

```

还有一种思路，做两次预处理，也就不再做特判，直接进行计算，码量相当，就不做说明了。

---

## 作者：Linge_Zzzz (赞：0)

题意不再赘述。

# Sol

注意到操作一次后数列单调不降。

再操作一次后数列里数相等的连续的段长度至少为 $2$。

然后每一次操作相当于把数组往右移位，低位补 $0$。

操作两次后直接对每个数算贡献即可。

# Code

```cpp
#include <iostream>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,a[N],b[N],t[N];
int S(int x){return (1+x)*x/2;}
void solve(){
	int ans=0,mx=0;
	cin>>n;
	fill(b,b+1+n,0);
	fill(t,t+1+n,0);
	for(int i=1;i<=n;i++){
		cin>>a[i],ans+=a[i];
		t[a[i]]++;
		if(t[a[i]]>=2)mx=max(mx,a[i]);
		b[i]=mx; 
	}
	fill(t,t+1+n,0);
	for(int i=1;i<=n;i++){
		t[b[i]]++;
	}
	int lst=0;
	for(int i=1;i<=n;i++){
		if(t[b[i]]>1){
			lst=b[i];
			ans+=(n-i+1)*b[i];
		}else{
			ans+=b[i];
			ans+=lst*(n-i);
		}
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while(t--)solve();
	return 0;
}

```

---

