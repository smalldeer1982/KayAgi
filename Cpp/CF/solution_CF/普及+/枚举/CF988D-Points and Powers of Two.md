# Points and Powers of Two

## 题目描述

There are $ n $ distinct points on a coordinate line, the coordinate of $ i $ -th point equals to $ x_i $ . Choose a subset of the given set of points such that the distance between each pair of points in a subset is an integral power of two. It is necessary to consider each pair of points, not only adjacent. Note that any subset containing one element satisfies the condition above. Among all these subsets, choose a subset with maximum possible size.

In other words, you have to choose the maximum possible number of points $ x_{i_1}, x_{i_2}, \dots, x_{i_m} $ such that for each pair $ x_{i_j} $ , $ x_{i_k} $ it is true that $ |x_{i_j} - x_{i_k}| = 2^d $ where $ d $ is some non-negative integer number (not necessarily the same for each pair of points).

## 说明/提示

In the first example the answer is $ [7, 3, 5] $ . Note, that $ |7-3|=4=2^2 $ , $ |7-5|=2=2^1 $ and $ |3-5|=2=2^1 $ . You can't find a subset having more points satisfying the required property.

## 样例 #1

### 输入

```
6
3 5 4 7 10 12
```

### 输出

```
3
7 3 5```

## 样例 #2

### 输入

```
5
-1 2 5 8 11
```

### 输出

```
1
8
```

# 题解

## 作者：HMZHMZHMZ (赞：8)

## 思路
我们考虑一下集合内元素的个数最多能有几个，当集合内元素个数 $\leq 2$ 的时候解法显然，我们考虑当集合内元素为 $3$ 个的时候。

首先我们考虑集合内元素为 $3$ 个的情况，我们设这三个数分别为 $a,b,c$ ,并且 $a < b < c$ 。

由于他们之间的差值为 $2$ 的幂次方，所以我们不妨这么表示$a+2^{k_1} = b , b+2^{k_2} = c$ 。

所以 $a$ 与 $c$ 之间的差值便为 $2^{k_1}+2^{k_2}$ 。我们知道，一个 $2$ 的幂次方在二进制表达式下有且只有一个 $1$ ，所以当 $2^{k_1} \ne 2^{k_2}$ 时，他们的 $1$ 不会加在同一个位置上，构成的二进制数中会存在两个 $1$ ,这样它就不是 $2$ 的幂次方了，所以我们可以得出结论，在任何条件下，$k_1 = k_2$ 恒成立。

然后我们考虑集合内元素个数 $4$ 的集合，不妨设相邻两个数的差分别为 $k_1 , k_2 ,k_3$ ，我们将上面的结论带下来，可以得出 $k_1 = k_2 = k_3$ ，所以第一个数和最后一个数的差便为 $3 \times 2^{k_1}$ ，显然不为 $2$ 的幂次方，所以集合内个数为 $4$ 的时候无解。

对于集合内元素个数 $> 4$ 的，其中必定有一个子集含有 $4$ 个元素，这是无解的。

综上，只有在集合内元素个数 $\leq 3$ 时有解。

有了这一结论，再写这道题就不难了。我们只需要暴力枚举集合内元素个数即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
ll n,m,lt,rt,a[N];
inline int llread(){
    ll s=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0') {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch<='9'&&ch>='0'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
    return s*f;
}
int main(){
    n=llread();
    for(register int i=1;i<=n;++i) a[i]=llread();
    sort(a+1,a+n+1);
    for(register ll i=2;i<n;++i){
        for(register ll j=0;j<=30;++j){//我们已经证过，他们两两之间差相等，所以我们枚举2^d，以a[i]为中间的数，二分查找一下即可
            lt=lower_bound(a+1,a+i,a[i]-(1ll<<j))-a;
            rt=lower_bound(a+i+1,a+n+1,a[i]+1ll*(1<<j))-a;
            if(a[lt]==a[i]-1ll*(1<<j)&&a[rt]==a[i]+1ll*(1<<j)){
                printf("3\n");
                printf("%lld %lld %lld",a[lt],a[i],a[rt]);
                return 0;
            }
        }
    }
    for(register ll i=2;i<=n;++i){//枚举两个数的方案
        for(register ll j=0;j<=30;++j){
            lt=lower_bound(a+1,a+i,a[i]-1ll*(1<<j))-a;
            if(a[lt]==a[i]-(1ll<<j)){
                printf("2\n");
                printf("%lld %lld",a[i],a[lt]);
                return 0;
            }
        }
    }
    printf("1\n%lld",a[1]);
    return 0;
}
```


---

## 作者：Little_x_starTYJ (赞：8)

### 解题思路
首先我们可以得出我们选择的数不超过 $3$ 个。

为什么呢？我们都知道如果 $2^i+2^j=a^k$，那么 $i=j,k=2\times i=2\times j$，我们设取出的 $3$ 个数为 $a,b,c$，首先它们一定满足 $|a-b|=2^i,|b-c|=2^j,|a-c|=2^k$。

$\because |a-c|=|a-b|+|b-c|$。

$\therefore k = i + j$。

因此我们可以构造这个序列，比如 $a=1,b=3,c=5$。

如果我们再取一个数 $d$，那么 $|a-b|=2^i,|b-c|=2^j,|c-d|=2^p,|a-d|=2^q$。

$\because |a-d|=|a-b|+|b-c|+|c-d|$。

$\therefore q=i+j+p$

然而 $3\times 2^i \ne 2^q$，这个序列既然连一部分的条件都满足不了，那么所有条件一定也不能全部满足，所以当我们取的数字数量为 $4$ 的时候无解。

如果我们取 $x(x>4)$ 个数字，那么包含了取 $4$ 个数字的情况，显然无解。

所以我们取的序列长度必须小于等于 $3$，且经递增排序后，相邻两数之差相等。因此，我们可以先枚举整个序列中起始位置的数 $y$，再依次判断 $y+2^k,y+2^{k+1}$ 是否在序列中出现过并进行统计即可。

CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200010];
int n;
map<int, bool> m;
int k[200010];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (register int i = 1; i <= n; i++) {
		cin >> a[i];
		m[a[i]] = 1;
	}
	int ans = 0;
  //蒟蒻赛时没有想那么多，这里枚举的是序列长度大于 1 且小于等于 3 的解
	for (register int i = 1; i <= n; i++) {
		for (register int j = 0; j <= 30; j++) {
			int o = 1;
			o <<= j;
			if (m.count(a[i] + o)) {  //也可以排序后二分哦
				int temp = a[i] + o;
				if (ans <= 2)
					k[1] = a[i], k[2] = temp, ans = 2;
				if (m.count(temp + o)) {
					cout << 3 << endl;
					cout << k[1] << ' ' << k[2] << ' ' << k[2] + o;
					return 0;
				}
			}
		}
	}
	if (ans == 0) {    //如果找不到长度大于 1 且小于等于 3 的序列随便输出序列中的一个数即可。
		cout << 1 << endl;
		cout << a[1] << endl;
		return 0;
	}
	cout << ans << endl;
	for (int i = 1; i <= ans; i++)
		cout << k[i] << ' ';
	return 0;
}

```

### 总结
这道题目主要是序列长度小于等于 $3$ 的地方需要一定的时间去证明，总体来说还是比较好做的。

---

## 作者：liaoxingrui (赞：4)

## Content

给你一个 $n$ 和有 $n$ 个数字的数组，问最多有多少个数字它们两两的差是 $2$ 的幂次方数，并输出其中一种方案。

## Solution

我们可以发现如果有两个数（$x$，$y$）的差是 $2$ 的幂次方数，其中一个数（$y$）与另一个数（$z$）的差也是 $2$ 的幂次方数，那么这三个数要想两两的差是 $2$ 的幂次方数，就得让 $y - x = z - y (x < y < z)$。因为这样才能让 $z - x$ 为 $2$ 的幂次方数。

$$z - x = (z - y) + (y - x) = 2 \times (y - x) = 2 \times 2^k = 2^{k + 1}$$

继续看，我们已知 $y - x = z - y = 2^k,z - x = 2^{k + 1}$，若再想加一个数（$a$，$x < y < z < a$）要让它为 $z + 2^{k + 1}$ 还是 $z + 2^k$（如果加其它的 $2$ 的幂次方数，就不满足刚刚所推的式子）。

- $a = z + 2^k$，那 $a - x = (a - z) + (z - x) = 2^k + 2^{k + 1}$，并不是 $2$ 的幂次方数，不成立。

- $a = z + 2^{k + 1}$，那 $a - y = (a - z) + (z - y) = 2^{k + 1} + 2^k$，并不是 $2$ 的幂次方数，不成立。

可以发现答案最多为 $3$。

- 答案为 $1$，取数组中任意一个值。

- 答案为 $2$，可先排序，使用二分查找数组中是否存在数组中某一个数再加上 $2$ 的幂次方数。

- 答案为 $3$，思路同上，多查一遍。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,sum=1;
int a[N],ans[4];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	ans[1]=a[1];
	sort(a+1,a+n+1);
	for(int i=1;i<n;i++){
		for(int j=0;j<=31;j++){
			int x=lower_bound(a+1,a+n+1,a[i]+(1<<j))-a;
			if(a[x]==a[i]+(1<<j)){
				ans[1]=a[i];
				ans[2]=a[x];
				sum=2;
				break;
			}
		}
		if(sum==2)
			break;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=31;j++){
			int cnt=a[i];
			for(int k=2;k<=3;k++){
				int x=lower_bound(a+1,a+n+1,cnt+(1<<j))-a;
				if(a[x]!=cnt+(1<<j))
					break;
				cnt+=(1<<j);
				if(k==3){
					sum=3;
					ans[1]=a[i];
					ans[2]=a[i]+(1<<j);
					ans[3]=a[i]+(1<<j+1);
				}
			}
			if(sum==3)
				break; 
		}
		if(sum==3)
			break; 
	}
	cout<<sum<<endl;
	for(int i=1;i<=sum;i++)
		cout<<ans[i]<<" "; 
	return 0;
}
```

---

## 作者：WaterSun (赞：3)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DCF988D%20Points%20and%20Powers%20of%20Two)

# 思路

首先发现选出的数最多 $3$ 个，考虑反证法。假设选出了四个数 $a,b,c,d$，并令：

$$
|a - b| = 2^{x_1},|b - c| = 2^{x_2},|c - d| = 2^{x_3}
$$

又因为，$|a - c|,|b - d|$ 也都是 $2$ 的次幂，那么有 $x_1 = x_2 = x_3$。于是 $|a - d| = 3 \times 2^{x_0} \neq 2^k$。

在上述过程中可以发现，相邻的数的差是相同的。

直接用 `map` 乱存一下即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10;
int n,arr[N];
map<int,bool> vis;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

signed main(){
    n = read();
    for (re int i = 1;i <= n;i++) arr[i] = read(),vis[arr[i]] = true;
    for (re int i = 1;i <= n;i++){
        for (re int j = 0;j <= 30;j++){
            int t = (1ll << j);
            if (vis.count(arr[i] + t) && vis.count(arr[i] + 2 * t)) return printf("3\n%lld %lld %lld",arr[i],arr[i] + t,arr[i] + 2 * t),0;
        }
    }
    for (re int i = 1;i <= n;i++){
        for (re int j = 0;j <= 30;j++){
            int t = (1ll << j);
            if (vis.count(arr[i] + t)) return printf("2\n%lld %lld",arr[i],arr[i] + t),0;
        }
    }
    printf("1\n%lld",arr[1]);
    return 0;
}
```

---

## 作者：CodingOIer (赞：1)

## [CF988D] Points and Powers of Two 题解

### 思路分析

显然，最多存在 $3$ 个数，证明如下：
$$
a < b < c < d \\
a + 2^i = b, b + 2^j = c \\
\because c - a = 2^k, k \in \mathbb{Z} \\
\therefore i = j \\
\therefore d = c + 2^{i + 1} = a + 2^{i + 2} \\
\therefore \neg l \in \mathbb{Z}, d - b = 2 ^ l \\
$$
所以最多只能有 $3$ 个数。

### 代码实现

```cpp
#include <cstdio>
#include <map>
constexpr int MaxN = 2e5 + 5;
int n;
long long p[MaxN];
std::map<long long, bool> map;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &p[i]);
        map[p[i]] = true;
    }
    for (int i = 1; i <= n; i++)
    {
        for (long long j = 1; j <= 2e9; j *= 2)
        {
            if (map.count(p[i] + j) && map.count(p[i] + 2 * j))
            {
                printf("3\n");
                printf("%lld %lld %lld\n", p[i], p[i] + j, p[i] + 2 * j);
                return 0;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (long long j = 1; j <= 2e9; j *= 2)
        {
            if (map.count(p[i] + j))
            {
                printf("2\n");
                printf("%lld %lld\n", p[i], p[i] + j);
                return 0;
            }
        }
    }
    printf("1\n");
    printf("%lld\n", p[1]);
    return 0;
}
```

---

## 作者：xxboyxx (赞：1)

### 思路

可以发现最多只会有三个数，证明如下：

首先为了差都是 $2$ 的幂次方数，所以设第二大的数为 $x$，它们之间的差为 $2^p$，则有剩下两个数分别为 $x-2^p$ 和 $x+2^p$，这时如果再加一个数，与 $x$ 的差为 $2^k$，则与另外两数之差为 $|2^k-2^p|$ 和 $|2^k+2^p|$，则当且仅当 $x+2^k=x$ 时才会满足题意，但这时 $k=0$，所以舍去，则最多只会有三个数。

有了这条性质，就可以进行分类讨论，利用二分查找快速得出答案。

### 注意

二分答案时一定要记住判断是否超过边界。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,maxx=1;
int aa,bb;
int a[20000005];
signed main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	for (int i=1;i<=n;i++)
	{
		int ans=0;
		for (int j=0;j<=50;j++)//枚举每一种p 
		{
			int x=a[i]+pow(2,j);
			int y=a[i]-pow(2,j);
			int k1=lower_bound(a+1,a+n+1,x)-a;
			int k2=lower_bound(a+1,a+n+1,y)-a;//两个数是否在序列里 
			if (a[k1]==x && a[k2]==y && k1>=1 && k2>=1 && k1<=n && k2<=n)
			{
				cout<<3<<'\n';
				cout<<x<<' '<<a[i]<<' '<<y<<'\n';
				return 0;
			}
			else if (a[k1]==x && k1>=1 && k1<=n)//只满足其中一个 
			{
				maxx=2;
				aa=a[i],bb=x;
			}
			else if (a[k2]==y && k2>=1 && k2<=n)
			{
				maxx=2;
				aa=a[i],bb=y;
			}
		}
	}
	if (maxx==1)//一个都不满足，输出任意一个 
	{
		cout<<1<<'\n';
		cout<<a[1];
	}
	else if (maxx==2)
	{
		cout<<2<<'\n';
		cout<<aa<<' '<<bb;
	}
	return 0;
}
```

---

## 作者：seika27 (赞：1)

### 题意
给定一个序列 $A$，要求在 $A$ 中选尽可能多的数，使每两个的数的差的绝对值皆为 $2$ 的非负数整数次幂。
### 分析
如果我们只选一个数，显然成立。

如果我们选两个数，我们需要让这两个数的差的绝对值为 $2$ 的非负整数次幂。

如果我们选三个数，我们令三个数分别为 $x_1$，$x_2$，$x_3$。我们保证这三个数从小到大排列。我们令 $x_2-x_1=2^k$。那么 $x_3-x_2$ 为多少呢？
我们先假设 $x_3-x_2=2^{k+p}$。那么 $x_3-x_1=2^{k+p}+2^k$，原式也就是 $x_3-x_1=2^k\times (2^p+1)$。很容易可以发现只有当 $p=0$ 时，$2^p+1$ 是 $2$ 的非负整数次幂。

所以这三个数分别为 $x-2^k$，$x$，$x+2^k$。

如果我们要选四个数，对于前三个数，刚刚的结论仍然成立，那我们所加的 $x_4$ 与 $x_3$ 的差为 $2^k$。
但是此时 $x_4-x_1=3\times2^k$，所以我们根本不可能选四个数，所以我们最多选三个数。

接下来就比较好做了，用一个 ```map``` 来存 $2$ 的次方。
一个 ```set``` 来存数列 $A$，这里一定要用 ```set``` 来存，用 ```map``` 的话会被卡掉。

然后从三往一去试，有了就直接输出。

---

## 作者：遥遥领先 (赞：1)

# 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF988D)

题意：给你有 $n$ 个数字的一个数列，问最多有多少个数字他们 **两两的差是 2 的幂次方数**。

# 思路

首先，我们想**一**个数能不能组成一个满足题目要求的序列，答案是肯定的。~~（直接输出 $a_1$ 不就彳亍了吗）~~

再想**两**个数彳亍不彳亍。看看样例：

### **输入 #1**

```cpp
6
3 5 4 7 10 12
```

### **输出 #1**

```cpp
3
7 3 5
```

举个栗子：$3$ 和 $5$ 之间差距是 $2$，即 $2^1$。

再来看**三**个数的，样例输出就已经给了。

看**四**个数，还是举个栗子：

```cpp
输入：
1 2 3 4
```
发现如果是**四**个数，$1$ 和 $4$ 相差 $3$，并不是 $2$ 的次方，发现不行。

证明一下：

令四个数为 $a,b,c,d$，则：

$|a-b|=2^{x_0}, |b-c|=2^{x_1}, |c-d|=2^{x_2}$

此时需要满足两两之差为 $2$ 的次方，则 $x_0=x_1=x_2$

∴ $|a-c|=2^{x_0+1}, |b-d|=2^{x_1+1}$

∴ $|a-d|=3 \times 2^{x_0} \ne 2^k$

**所以，可以满足题目要求的序列的元素个数只能输 $1, 2, 3$ 个。**

# 代码核心部分：

```cpp
for (int i = 1;i <= n;i++) //枚举3个数组成的序列 
{
	for (int j = 0;j <= 30;j++)
	{
		int w = sum[j]; //w获取了2的j次方
		if (s.count(a[i]+w) >= 1 && s.count(a[i]+2*w) >= 1) //判断是否有一个满足条件的序列 
		{
			printf("3\n%lld %lld %lld",a[i],a[i]+w,a[i]+2*w); //可以输出啦 
			return 0; //直接结束程序 
		}
	}
}
```

最后，附上我的 AC 代码：

```cpp
#include <bits/stdc++.h> //万能头 
#define int long long //可能会超int 
using namespace std;
int n;
int a[200010];
set <int> s; //用集合去存储，会自动去重和排序 
int sum[40]; //sum[i]表示2的i次方 
signed main() //这里注意是signed 
{
	sum[0] = 1; //这里初始化是为了优化pow函数 
	for (int i = 1;i <= 30;i++)
	{
		sum[i] = sum[i-1] * 2;
	}
	scanf("%lld",&n); //以防万一，就用scanf吧 
	for (int i = 1;i <= n;i++)
	{
		scanf("%lld",&a[i]);
		s.insert(a[i]); //将a[i]加入集合 
	}
	for (int i = 1;i <= n;i++) //枚举3个数组成的序列 
	{
		for (int j = 0;j <= 30;j++)
		{
			int w = sum[j]; //w获取了2的j次方
			if (s.count(a[i]+w) >= 1 && s.count(a[i]+2*w) >= 1) //判断是否有一个满足条件的序列 
			{
				printf("3\n%lld %lld %lld",a[i],a[i]+w,a[i]+2*w); //可以输出啦 
				return 0; //直接结束程序 
			}
		}
	}
	for (int i = 1;i <= n;i++) //枚举2个数组成的序列
	{
		for (int j = 0;j <= 30;j++)
		{
			int w = sum[j]; //w获取了2的j次方
			if (s.count(a[i]+w) >= 1) //判断是否有一个满足条件的序列 
			{
				printf("2\n%lld %lld",a[i],a[i]+w); //可以输出啦 
				return 0; //直接结束程序 
			}
		}
	}
	printf("1\n%lld",a[1]); //最后，如果3个或2个都不行，那就随便输出原数列中的一个数 
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF988D)
## 思路
我先推了一个 $\verb!DP!$，设 $f_{i,j}$ 为到第 $i$ 个数为止，最大差值为 $2^j$ 的最大长度，然后接下来我们就要看在 $i$ 的前面是否有一个数 $a_k$ 为 $a_i-2^j$，如果有的话就转移为 $f_{i,j}=\max(f_{k,j}+1)$，然后记录一下前驱。

然后终于我发现这个东西最大值只有 $3$，我们不妨设这三个数为 $x,y,z$，其中 $y=x+2^a,z=x+2^b$，则这三个数实际上可以表示为 $x,x+2^a,x+2^b$，现在我们要再加进来一个数，不妨设为 $x+2^c,c>a$，$x+2^c-(x+2^a)=2^c-2^a=2^a \times (2^c-1)$，显然 $c>0$，因为 $a \ge 0$，所以 $2^c-1$ 是个奇数，所以 $2^a \times (2^c-1)$ 也是个奇数，不可能是 $2$ 的整数次幂。
## 代码
因为加了 $\verb!STL!$，所以跑的很慢。
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=2e5+10;
int ans=1,ans1,ans2,a[N];
map<int,int>mp;
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int n;cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i];
    sort(a+1,a+n+1);
    for (int i=1;i<=n;++i){
        mp[a[i]]=1;
        for (int j=0;(1LL<<j)<=2000000000;++j){
            if (mp[a[i]-(1LL<<j)] && mp[a[i]-(1LL<<(j+1))]){
                cout<<"3\n";cout<<a[i]-(1LL<<(j+1))<<' '<<a[i]-(1LL<<j)<<' '<<a[i]<<'\n';
                return 0;
            }
            if (mp[a[i]-(1LL<<j)]){
                if (ans<2) ans=2,ans1=a[i],ans2=a[i]-(1LL<<j);
            }
        }
    }
    if (ans==1) cout<<1<<'\n'<<a[1]<<'\n';
    else cout<<2<<'\n'<<ans1<<' '<<ans2<<'\n';
    return 0;
}

```


---

## 作者：daniEl_lElE (赞：1)

## 思路

首先给出结论：满足要求的最多数字数小于等于 $3$。

为什么呢？设 $1<j<k$，考虑当我们选出 $(i,j,k)$ 后，$j-i=2^x$，$k-j=2^y$，要想让 $2^x+2^y=2^z$，必须满足 $x=y=z-1$。故对于所有符合要求的三元组 $(i,j,k)$，$j-i=k-j$。

反证，若满足要求的最多数字数是 $4$，则存在满足要求的 $(i,j,k,l)$，即 $j-i=k-j=l-k=2^x$，容易发现 $l-i=3\times2^x\not=2^y$，所以不符合条件。

接下来我们只需要枚举差 $2^x$ 即可，注意使用 $\texttt{map}$ 可能会 $\texttt{MLE}$，建议排序后二分即可，复杂度 $O(n\log a_i\log n)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
map<int,int> mp;
int maxv,ans1,ans2,ans3;
int a[200005];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	maxv=1,ans1=a[1];
	for(int i=1;i<=n;i++){
		for(int j=0;j<31;j++){
			int l=(1<<j);
			if(a[lower_bound(a+1,a+n+1,a[i]+l)-a]==a[i]+l&&lower_bound(a+1,a+n+1,a[i]+l)-a<=n){
				if(maxv<=1){
					maxv=2,ans1=a[i],ans2=a[i]+l;
				}
				if(a[lower_bound(a+1,a+n+1,a[i]+l*2)-a]==a[i]+l*2&&lower_bound(a+1,a+n+1,a[i]+2*l)-a<=n){
					if(maxv<=2){
						maxv=3,ans1=a[i],ans2=a[i]+l,ans3=a[i]+l*2;
					}
				}
			}
		}
	}
	cout<<maxv<<endl;
	if(maxv>=1) cout<<ans1<<" ";
	if(maxv>=2) cout<<ans2<<" ";
	if(maxv>=3) cout<<ans3<<" ";
	return 0;
}
```

---

## 作者：serverkiller (赞：1)

虽然是D题，但是也不是很难。
没有什么思维含量，就是开一个set然后血腥（）地搜索就好了

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200005];
set<long long>st;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
    	scanf("%lld",&a[i]);
    	st.insert(a[i]);
    }
    for(int i=1;i<=n;i++)
        for(long long j=1;j<=2e9;j*=2)
        {
        	if(st.count(a[i]+j)&&(st.count(a[i]+j+j)))
        	{
        		cout<<3<<endl;
        		cout<<a[i]<<' '<<a[i]+j<<' '<<a[i]+j+j;
        		return 0;
            }
        }
    for(int i=1;i<=n;i++)
        for(long long j=1;j<=2e9;j*=2)
        {
        	if(st.count(a[i]+j))
        	{
        		cout<<2<<endl;
        		cout<<a[i]<<' '<<a[i]+j;
        		return 0;
            }
        }
    cout<<1<<endl;
    cout<<a[1];
    return 0;
}
```


---

## 作者：EternalAlexander (赞：1)

首先，直觉告诉我们，选中点集的大小不超过3。

证明：

设选中点集为{a, b, c, d}

a--b--c--d

设dis(a, b)=2^m,dis(b, c)=2^n

若m!=n：
不妨设m<n，

则dis(a, c)=2^m+2^n=2^m+2^m*2^(n-m)

=2^m*(2^(n-m)+1)!=2^k

∴m=n
∴dis(a, b)=dis(b, c)=2^n, dis(a, c)=2^(n+1)

同理，对于b, c, d, dis(b, c)=dis(c, d)=2^n, dis(b, d)=2^(n+1)

∴dis(a, d)=2^n+2^n+2^n=3*2^n!=2^k

∴选中点集大小<4

然后就好办了。枚举中间那个点，然后枚举到两边的点的距离n,二分check一下。

复杂度n*(logn)^2

```cpp
#include <cstdio>
#include <algorithm>

int arr[300000];
int a[300000];
int v[300000];
int min,max;
int n;

int check(long long v) {
	if (v<min||v>max) return -1;
	int l=1; int r=n;
	int ans=-1;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (a[mid]==v) return mid;
		if (a[mid]<v) l=mid+1;
		if (a[mid]>v) r=mid-1;
	}return -1;
}

int main() {
	scanf("%d", &n);
	for (int i=1;i<=n;++i) {
		scanf("%d", &arr[i]);
		min=std::min(arr[i], min);
		max=std::max(max, arr[i]);
	}std::sort(arr+1, arr+n+1);
	int cnt=1; int tail=0;
	for (int i=1;i<=n;++i) {
		if (arr[i]!=arr[i+1]||i==n) {
			a[++tail]=arr[i];
			v[tail]=cnt;
			cnt=1;
		} else cnt++;
	}
	if (n==1) {
		printf("%d\n%d", 1, arr[1]);
		return 0;
	}n=tail;
	int ans=0; int ans0=0; int ans1=0; int ans2=0;
	for (int i=1;i<=tail;++i) {
		for (long long j=1; j<=1073741824; j<<=1) {
			int lp=check(a[i]-j); int rp=check(a[i]+j);
			int sum=v[i]; if (lp>0) sum+=v[lp];
			if (rp>0) sum+=v[rp];
			if (sum>ans) {
				ans=sum;
				ans0=lp; ans1=i; ans2=rp;
			}//if (lp<0&&rp<0) break;
		}
	} printf("%d\n", ans);
	if (ans0>0) 
		for (int i=1;i<=v[ans0];++i) printf("%d ", a[ans0]);
	if (ans1>0) 
		for (int i=1;i<=v[ans1];++i) printf("%d ", a[ans1]);
	if (ans2>0) 
		for (int i=1;i<=v[ans2];++i) printf("%d ", a[ans2]);
	return 0;
}
```

---

## 作者：Three_leaf (赞：0)

### 题面
给你有 $n$ 个数字的一个数列，问最多有多少个数字他们两两的差是 $2$ 的幂次方数。

### 思路
#### 有一个证明：
对于一个合法的集合 $S$，我们可以得到一个最大数 $x$，和其它集合里的数（如果有的话）$a=x-2^p,b=x-2^q$。

所以说$|a-b|=2^l$ 即 $|x-2^p-x+2^q|=|2^q-2^p|=2^l$。于是 $|p-q|$ 只能是 $1$。

#### 所以说：
$S$ 只有至多三种数，于是我们枚举最大值 $x$ 和 $p$，再取一个最大答案，完了。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 200005 
using namespace std;
int a[Maxn];
int n;
int res[Maxn],g[Maxn],ans=0;
map<int,int> mp;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	int L=0,l0=0,R=0,r0=0,To=0;
	for(int i=1;i<=n;i++)
		mp[a[i]]++;
	for(int i=1;i<=n;i++)
		for(int d=0;d<33;d++) {
			int G=1ll<<d,F=1ll<<(d-1);
			int P=mp.count(a[i]-G),Q=mp.count(a[i]-F);
			if(P+Q+1>ans)ans=P+Q+1,L=a[i]-G,R=a[i]-F,l0=P,r0=Q,To=a[i];
		}
	cout<<ans<<"\n"<<To<<" ";
	for(int i=1;i<=l0;i++)
		cout<<L<<" ";
	for(int i=1;i<=r0;i++)
		cout<<R<<" ";
	return 0;
 } 
```

---

