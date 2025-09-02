# [ABC146E] Rem of Sum is Num

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc146/tasks/abc146_e

長さ $ N $ の正整数列 $ A_1,\ A_2,\ \ldots\ ,\ A_N $ と正の整数 $ K $ が与えられます。

$ A $ の空でない連続する部分列であって、要素の和を $ K $ で割った余りが要素の数と等しくなるものの数を求めてください。ただし、$ 2 $ つの部分列が列として同じでも、取り出す位置が異なるならば区別するものとします。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ 10^9 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

$ (1) $, $ (4,2) $, $ (1,4,2) $, $ (5) $ の $ 4 $ つが条件をみたす部分列です。

### Sample Explanation 2

$ (4,2) $ が $ 4 $ 回、$ (2,4) $ が $ 3 $ 回数えられています。

## 样例 #1

### 输入

```
5 4
1 4 2 3 5```

### 输出

```
4```

## 样例 #2

### 输入

```
8 4
4 2 4 2 4 2 4 2```

### 输出

```
7```

## 样例 #3

### 输入

```
10 7
14 15 92 65 35 89 79 32 38 46```

### 输出

```
8```

# 题解

## 作者：liangbowen (赞：14)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc146_e)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17421804.html)

简单题，whk 的时候就秒了，但是不知道为什么很喜欢这题，就来写题解啦！

（还有一个原因是，现有题解都不知道在讲啥东西。）

## 思路

区间求和，容易想到前缀和。题目等价于，有多少个 $sum_r - sum_{l-1} \equiv r-l+1 \pmod k$。

比较有趣的是移项，右边的都移到左边去，发现等价于求 $(sum_r - r) - \Big(sum_{l-1} - (l-1)\Big) \equiv 0 \pmod k$。

所以维护 $val_i=(sum_i - i)\bmod k$ 是否相同就完事了，上 `map`。

## 代码

细节有两个：

1. 注意算上 $val_0$，因为 $(l-1)$ 可能跑到 $0$ 去。
2. 超出区间范围要剔除。

```cpp
#include <iostream>
#include <cstdio>
#include <unordered_map>
using namespace std;
int val[200005];
unordered_map <int, int> cnt;
int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	long long ans = 0, sum = 0;
	
	val[0] = 0, cnt[0]++;
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x), x %= k, sum += x;
		val[i] = ((sum - i) % k + k) % k;
		if (i >= k) cnt[val[i - k]]--;
		ans += cnt[val[i]], cnt[val[i]]++;
	}
	cout << ans;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：installb (赞：6)

来自 https://kenkoooo.com/atcoder 的评分：$\sf{\color{blue}1710}$  

题目条件很奇怪，很难直接处理。  

区间和没法转化了，考虑把区间长度转化，把一个区间的长度视为这个区间里每一个数都为区间长度提供了 $1$ 的贡献，而每一个区间长度就是该区间里所有数对区间长度的贡献之和。  

最后要求的式子是 满足 区间和减去区间长度 是 $K$ 的倍数。  

我们根据上面的思路，给每一个数赋予对区间长度 $-1$ 的贡献，这样一段长度为 $L$ 的区间就会产生 $-L$ 的贡献，然后我们用区间和加上这个贡献就是最后的 区间和减去区间长度。  
然后这个 $-1$ 直接在原数 $a_i$ 上减一就可以了，**这样以后再做区间和，得到的结果就是原先的区间和减去区间长度。  

接下来统计区间数比较容易了，考虑做一遍前缀和，用差分统计有多少区间和为 $K$ 的倍数，$S_{l,r}=pre_r-pre_{l-1}$，枚举 $r$，寻找所有符合条件的 $l$，由于 $pre_r\mod K$ 是确定的，我们只要找到满足 $pre_{l-1}\mod K=pre_r\mod K$ 的所有 $l$，这里我们对每一个余数 $i$ 存储有多少个 $l$ 满足 $pre_l\mod K=i$，这里用`map`容器来做了。  

这里还有一个限制，就是区间长度必须 $<K$，那就每一次枚举 $r$ 时把过期的 $l$ 从 `map` 里删除即可。  

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
using namespace std;
typedef long long LL;

LL n,k,a[200005];
LL pre[200005] = {0};
map <LL,LL> mp;
LL tot = 0;

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for(LL i = 1;i <= n;i ++){
		cin >> a[i]; a[i] --; a[i] %= k;
		pre[i] = pre[i - 1] + a[i]; pre[i] %= k;
		// 预处理前缀和
    }
	mp[pre[0]] = 1;
	for(LL i = 1;i <= n;i ++){
		if(i >= k) mp[pre[i - k]] --; // 删除过期元素
		tot += mp[pre[i]]; // 统计有多少l
		mp[pre[i]] ++; // 加入r
	}
	cout << tot << endl;
	return 0;
}
```

代码难度几乎没有，思维难度还可以。  
绿+/蓝- 1300

---

## 作者：Hilaria (赞：1)

这个题，我们可以 $O(n)$ 跑一遍以 $i$ 为结尾的（$i$ 从 $1$ 到 $n$），再 $O(1)$ 求出以 $i$ 为结尾的合法子区间有多少个，最后统计一下就是答案了。

那现在问题就在于我们如何 $O(1)$ 求出以 $i$ 为结尾的合法子区间的个数。

让我们再仔细地康康题目给出的式子。

$K|((a_l+a_{l+1}\dots +a_r)-(r-l+1))$

我们可以先用前缀和维护一下区间求和问题，再用一个数组维护一下长度（具体做法可以给每个数赋 $-i$，因为式子是 $-(r-l+1)$ 嘛，赋成负数后面可以直接加）。

我们用 $sum[i]$ 记录数值的前缀和，用 $res[i]$ 记录长度的前缀和，那么题目的式子就变成了：

$K|(sum[r]-sum[l-1]+res[r]-res[l-1])$

给它换个位置，就变成了：

$K|(sum[r]+res[r]-(sum[l-1]+res[l-1]))$

这么一看，那行，我们直接把 $sum$ 和 $res$ 合并成一个不就好了，省点空间。

那我们就只用维护一个数组 $b[i]=sum[i]+res[i]$。

所以现在我们只需要枚举每个结尾 $r$（$r$ 从 $1$ 到 $n$），然后数数前面有多少个数满足 $K|b[r]-b[l-1]$，简单来说就是算前面有多少个数的 $b$ 和自己的 $b[r]$ 同余。

那我们可以开个 map 记录一下每种余数有多少个，边算边加就行了。

注意：区间长度不能超过 $K$，$b$ 数组要记得模 $K$ 还有开头的 $l$ 可以是 $1$，所以记录余数个数时要记得再加上一个 $0$（就是说因为 $l$ 可能是 $1$，所以算 $K|b[r]-b[l-1]$ 时，$b[l-1]$ 是 $b[0]$）。

- 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXX=2e5+10;

int n,k;
ll a[MAXX],b[MAXX];
ll sum[MAXX],res[MAXX];
map<ll,int> num;
int main()
{
	scanf("%d%d",&n,&k);
	num[0]++;
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=(a[i]+sum[i-1])%k;
		res[i]=res[i-1]-1;
		b[i]=(sum[i]+res[i])%k;
		
		if(i>=k) num[b[i-k]]--;
		ans+=num[b[i]];
		num[b[i]]++;
	}
	printf("%lld\n",ans);	

	return 0;
}
```

代码看看就好了，因为它似乎出现不知名错误，它 UKE 了，编译信息提示说：

```
UnexpectedResponse: got an unexpected response when requesting `https://atcoder.jp/contests/abc146/submissions/me`: unable to find the source code
```
知道哪里出错的私信告知，谢谢啦。


---

## 作者：Skyjoy (赞：1)

别的网站的每日一题，思路比较巧妙，可以秒，记录一下。

# 思路

其实翻译那里已经把题目转化为求区间和减去区间长度被 $k$ 整除的组数了，把题目简化了好多（因为个人认为这一步是这道题最难想的）。经过明示之后，我们再记录一下 $a_i-1$ 的前缀和模 $k$ 的余数，装进计数器里进行计数，计算前面与其同余的元素的个数，答案就出来了。

值得注意的是，一个数除以 $k$ 的余数必须小于 $k$ ，所以我们截取的区间长度也必须小于 $k$ ，所以当我们枚举到 $i$ 时，要把第 $i-k$ 个元素所对应的计数器减1，然后就做完了。

# 代码

```cpp
#include<bits/stdc++.h>
#define I using
#define love namespace
#define Elaina std
#define ll long long
I love Elaina;
const int N=200010;
ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
ll n,k,a[N],sum[N],ans;
map<ll,ll>cnt;
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)a[i]=(read()-1)%k,sum[i]=(sum[i-1]+a[i])%k;//前缀和
	cnt[0]++;
	for(int i=1;i<=n;i++){
		if(i>=k)cnt[sum[i-k]]--;//已经超出截取区间了，计数器要减1
		ans+=cnt[sum[i]];//计算答案
		cnt[sum[i]]++;
	}
	printf("%lld",ans);
	return 0;
}
```

祝各位大神们省选顺利，取得理想的成绩！

---

## 作者：封禁用户 (赞：0)

这道题是前缀和的思想，太水了，都不知道为什么是绿题！！！

这题可以用 map 解决。
map 是一个映射的类型，和数组差不多（可以当做数组）。
***code***:

```cpp
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
int arr[200005];
map <int, int> cnt;
int main(){
	int n, k;//输入
	cin>>n>>k;
	long long ans = 0, sum = 0;
	arr[0] = 0, cnt[0]++;
	for (int i = 1; i <= n; i++){
		int x;
		cin>>x;
		x=x%k;
		sum += x;
		arr[i] = ((sum - i) % k + k) % k;
		if (i >= k) cnt[arr[i - k]]--;
		ans += cnt[arr[i]], cnt[arr[i]]+=1;
	}
	cout << ans;//输出
	return 0;
}
``````


---

## 作者：OcTar (赞：0)

## 题目大意

给定序列 $a$，求有多少个子区间的元素和模 $k$ 为区间长度。

## 题目分析

拿到题目时看到这个限制条件感觉很怪，尤其是区间长度这一块。思路比较灵活。考虑将序列中每一个元素的值减 $1$，于是问题就转化成了“存在几个子段的和为 $k$ 的倍数”（请读者仔细思考，应该不难得出）。但是需要注意排除掉子段长度大于等于 $k$ 的情况，因为子段和对 $k$ 取模的结果是不可能大于等于 $k$ 的。

完整代码如下：

```cpp
#include <iostream>
#include <map>
using namespace std;
const int maxn = 200200;
long long a[maxn];
int n, k;
long long sum = 0;
map<int, int> T;
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        a[i]--;//减1
    }
    T[0] = 1;
    for (int i = 1; i <= n; i++) {
        a[i] = (a[i] + a[i - 1]) % k;
        if (i >= k) {
            T[a[i - k]]--;//删除掉>=k的情况
        }
        sum += T[a[i]];
        T[a[i]]++;
    }
    cout << sum << endl;
    return 0;
}
```
~~作者最喜欢这种小清新题了！~~

---

## 作者：gdf_yhm (赞：0)

[abc146e](https://www.luogu.com.cn/problem/AT_abc146_e)

### 思路

由题，$k\mid (a_l+a_{l+1}+...+a_{r-1}+a_r)-(r-l+1)$，可以转换为平均每个数在模 $k$ 下都贡献了 $1$。所以对区间每个数都减 $1$，则长度为 $len$ 的区间和减了 $len$，此时如果区间和为 $k$ 的倍数则符合条件。

预处理对 $k$ 取模的前缀和 $sum_i$，如果 $sum_{l-1}=sum_r$，则区间 $[l,r]$ 符合条件。又因为 $r-l+1<k$，所以 $r-(l-1)+1\leq k$。

所以 $i$ 的 $sum_i$ 对答案的贡献为 $i-k+1\leq j\leq i-1$ 中与 $sum_i$ 相等的 $sum_j$ 的个数。

$sum_i$ 值域大，不能用桶处理。用 map 处理，删除 $sum_{i-k}$ 过期的，统计答案，加入 $sum_i$。

注意最开始的 $sum_0=0$ 也要算。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1000000000;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,k,a[maxn];
map<int,int> mp;
int ans;

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();k=read();
	mp[0]++;
	for(int i=1;i<=n;i++){
		a[i]=read();
		a[i]+=k-1;a[i]%=k;//a[i]+k-1=a[i]-1，在模 k 时。
		a[i]+=a[i-1];a[i]%=k;
		if(i>=k)mp[a[i-k]]--;
		ans+=mp[a[i]];
		mp[a[i]]++;
	}
	printf("%lld\n",ans);
}

```


---

## 作者：极寒神冰 (赞：0)

先对整个序列求前缀和$sum_k=\sum_{i=1}^{k}a_i$

题目求有多少对$(l,r)$ 满足$sum_r-sum_l\equiv r-l \mod k $

移项得 $sum_r-r\equiv sum_l-l \mod k $

那么使用一个$mp$存储$sum_l-l$的差，枚举右端点求和即可。

($mp[0]$要赋初值为$1$)

```
signed main()
{
	n=read(),k=read();
	R(i,1,n) a[i]=read(),sum[i]=sum[i-1]+a[i];
	mp[0]=1;
	R(R,1,n) 
	{
		if(R>=k) mp[(sum[L]-L+k)%k]--,L++;
		res+=mp[(sum[R]-R+k)%k];
		mp[(sum[R]-R+k)%k]++;
	}
	printf("%lld\n",res);
}
```




---

