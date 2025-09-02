# Arpa’s obvious problem and Mehrdad’s terrible solution

## 题目描述

There are some beautiful girls in Arpa’s land as mentioned before.

Once Arpa came up with an obvious problem:

Given an array and a number $ x $ , count the number of pairs of indices $ i,j $ ( $ 1<=i&lt;j<=n $ ) such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/80e8812f6abd24888e930488b3c56b15fb2a49a1.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/4298d47c0191af3c0a3103f431751061bc7e2362.png) is bitwise xor operation (see notes for explanation).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/7cd1b5aedffc45f296d333e099a050047eae38ee.png)Immediately, Mehrdad discovered a terrible solution that nobody trusted. Now Arpa needs your help to implement the solution to that problem.

## 说明/提示

In the first sample there is only one pair of $ i=1 $ and $ j=2 $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/c63bc815847bae57aeba51b11f6ec2211cbd1efa.png) so the answer is $ 1 $ .

In the second sample the only two pairs are $ i=3 $ , $ j=4 $ (since ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/360a9ab048a3005f1d532cfb7c78e96ffd10455b.png)) and $ i=1 $ , $ j=5 $ (since ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF742B/e00da54f194d914d5a9270c780a44af611f46740.png)).

A bitwise xor takes two bit integers of equal length and performs the logical xor operation on each pair of corresponding bits. The result in each position is $ 1 $ if only the first bit is $ 1 $ or only the second bit is $ 1 $ , but will be $ 0 $ if both are $ 0 $ or both are $ 1 $ . You can read more about bitwise xor operation here: [https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 样例 #1

### 输入

```
2 3
1 2
```

### 输出

```
1```

## 样例 #2

### 输入

```
6 1
5 1 2 3 4 1
```

### 输出

```
2```

# 题解

## 作者：过往梦魇之殇 (赞：5)

### 说实话，这道题思路想清楚，就很水了...~~(逃）~~

题意 ~~（题面上$copy$下来的）~~ ：

给出一串数组$a1..an$，和一个数字$x$，询问有多少对$ai$,$aj$满足$ai$^$aj=x$

由异或的性质可得：若$a$^$b=c$，则有$a$^$c=b$和$b$^$c=a$.

然后处理起来就很方便了$！！！$

代码很短，思路看看就明白了：

```cpp
#include<bits/stdc++.h>
#define re register
#define in inline
#define pi acos(-1.0)
#define inf 2147483640
using namespace std;
in int read()
{
    int sum=0,negative=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')negative=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum*negative;
}
int a[140000],n,x,t;
long long ans=0;
int main()
{
    n=read();
    x=read();
    while(n--)
    {
        t=read();
        ans+=a[x^t];
        ++a[t];
    }
    printf("%lld\n",ans);
    return 0;
}
```

本篇题解完……
>$Thanks$ $for$ $watching$ $!$

---

## 作者：lizulong (赞：2)

## 思路
1. 暴力求解。（TLE）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int s=0,w=1;
	char ch=getchar();
    while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	}
    while(ch>='0'&&ch<='9') s=s*10+ch-48,ch=getchar();
    return s*w;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48);
}
int a[100001];
signed main(){
	int sum=0,x,n
	n=read(),x=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			if( (a[i]^a[j]) ==x ) sum++;
	write(sum);
	return 0;
}   
```
时间复杂度大约是 $O(n^2)$。

2. 考虑优化：（AC）

题目需要求有多少对数满足 $a\bigoplus b=x$。

根据异或的性质：

$A\bigoplus (A\bigoplus B )=B$。

带入数得：$a\bigoplus x=b$，所以只需要统计 $a\bigoplus x$ 得出的 $b$ 的个数最后输出即可。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int s=0,w=1;
	char ch=getchar();
    while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	}
    while(ch>='0'&&ch<='9') s=s*10+ch-48,ch=getchar();
    return s*w;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48);
}
int a[200001],b[200001];
signed main(){
	int x,n,sum=0;
	n=read(),x=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),sum+=b[a[i]^x],b[a[i]]++;
	write(sum);
	return 0;
}
```
时间复杂度大约是 $O(n)$。

[AC记录](https://www.luogu.com.cn/record/122045545)

---

## 作者：Submerge_TA (赞：2)

这题是异或的板子题。

对于每一对元素 $(a_i, a_j)$，我们都可以计算它们的异或值，如果等于给定的数字 $x$，则满足条件。我们可以使用两层循环遍历所有的元素对，计算异或值并统计满足条件的对数。

在这里我用了```unordered_map```, 用于记录数字出现的频率，以便进行计数和查找操作。


代码（含注释）：

```
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int countPairs(vector<int>& nums, int x) {
    int count = 0;
    unordered_map<int, int> freq;
    for (int num : nums) {
        int complement = num ^ x;
        count += freq[complement];
        freq[num]++;
    }
    return count;
}

int main() {
    int n, x;
    cin >> n >> x;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int result = countPairs(nums, x);
    cout << result << endl;
    
    return 0;
}
```


---

## 作者：Eason_AC (赞：2)

## Content
有一个长度为 $n$ 的数组，请求出使得 $a_i \oplus a_j=x$ 且 $i\neq j$ 的数对 $(i,j)$ 的个数。其中 $\oplus$ 表示异或符号。

**数据范围：$1\leqslant n,a_i\leqslant 10^5,0\leqslant x\leqslant 10^5$。**
## Solution
利用一个异或的性质：$a\oplus b=c\Rightarrow a\oplus c=b,b\oplus c=a$，我们发现问题其实就迎刃而解了。直接统计每个数异或 $x$ 得到的数在原数组里面的个数再加起来就好了。

注意，数对可能很多，要开 $\texttt{long long}$。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <map>
using namespace std;

int n, x, a[100007];
map<int, int> vis;
long long ans;

int main() {
	scanf("%d%d", &n, &x);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		ans += vis[a[i] ^ x];
		vis[a[i]]++;
	}
	printf("%d", ans / 2);
	return 0;
}

```

---

## 作者：naroto2022 (赞：1)

# CF742B 题解

### 题意

给定两个整数 $n$，$t$，并给出一个数组 $a$：$a_1,a_2,\cdots,a_n$，问有多少组 $a_i,a_j$ 使得 $a_i \bigoplus a_j(i,j\in [1,n])$。

### 思路

首先，先熟悉一下 $ \bigoplus$（异或）的性质，其实他就是相同为假，不同为真：$1 \bigoplus0=1,0 \bigoplus1=1,1 \bigoplus1=0,0 \bigoplus0=0$。

于是再进阶一下，就可以知道异或的逆运算：若有 $a \bigoplus b=c$，则有 $a \bigoplus c=b,b  \bigoplus c=a$。于是就想到用一个桶数组，来记录 $a_i \bigoplus x=a_j$ 的情况数，最后加起来就可以输出正确答案了。

### 总结

1. 位运算。
2. 开 long long，不开 long long 见祖宗。
3. 快读快写。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long n,x,ans,t[200005],cnt;//一定要开long long 
long long read(){//快读 
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(long long x){//快写 
	if(x>9) write(x/10);
	putchar(x%10+'0'); 
}
int main(){
	n=read();x=read();
	for(int i=1; i<=n; i++){
		cnt=read();
		ans+=t[x^cnt];
        t[cnt]++;
	}
	write(ans);
	return 0;
} 
```


---

## 作者：ryl_ahu (赞：1)

##### [原题传送](https://www.luogu.com.cn/problem/CF742B)

首先，这道题需要用到一个基本原则：$a \oplus b = c$，$a \oplus c = b$。这里的 $\oplus$ 代表异或运算。

于是，我们通过 $a_i$ 和 $x$ 就可以求出 $a_j$ 了！然后我们用计数器累计在范围内的 $a_j$ 有多少个即可。

我们按照此操作先输入，于是就能找到每个数相对应的 $a_j$，再将每个点的个数值用另一个计数器累加。只不过答案是原来的两倍，因为前面计算时会计算重复，再除以 $2$ 就可以了。

此外提醒一点：我们需要特判 $x = 0$ 的情况。如果 $x = 0$，那么 $a_i \oplus x = a_i$ 了，所以我们要在 $x = 0$ 的时候计数器要减 $1$。

#### 十年 OI 一场空，不开_________见祖宗。

---
好了，现在我来构思一下代码框架：

- 输入（顺便初始化：$a_i$ 的位置加 $1$）。
- 从 $1$ 到 $n$ 循环。
	- 判断 $a_i \oplus x = a_i$。如果是，那么计数器就要再减去 $1$。
   - 否则判断 $a_i \oplus x$ 是否在范围内（$1 \times 10 ^ 5$），计数器累加。
- 输出计数器除以 $2$。

---
##### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

long long a[100005];
long long b[100005];

int main() {
	long long n, x, ans = 0;
	cin >> n >> x;
	for (long long i = 1; i <= n; i++)
		cin >> a[i], b[a[i]]++; // 位置初始化
	for (long long i = 1; i <= n; i++) {
		long long t = a[i] ^ x; // 偷懒
		if (a[i] == t or x == 0) ans += b[t] - 1; // 特判减1
		else if (t <= 100000) ans += b[t];
	}
	ans /= 2;
	cout << ans << endl;
	return 0;
}
```


---

## 作者：GWBailang (赞：1)

#### [原题传送](https://www.luogu.com.cn/problem/CF742B)
~~水黄~~，我们只需要知道 $a\oplus b=c$，$a\oplus c=b$ 就能做出这道题了。这里包括下文中的 $\oplus $ 都代表“异或”。

由于可以通过 $a_i$ 和 $x$ 这两个**已知**的值算出 $a_j$ 的值，那么我们只需要在 $a$ 数组输入的时候统计一下值为 $1$ 到 $10^5$ 的数分别有多少个。

输入完后，对于每个点都可以直接找到 $a_j$ 的值，所以将值为 $a_j$ 的点的个数相加，最终得到的结果是答案的两倍，所以除以 $2$ 然后输出。

还要注意一下 $x$ 可能是 $0$，那么 $a_i\oplus x$ 就等于 $a_i$ 了，但是我们不能选两个相同的点来做异或运算，所以需要特殊判断一下：如果 $x$ 等于 $0$，那么每个点统计时需要减去 $1$。

时间复杂度 $O(n)$。

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005];
long long hx[100005];//统计每个值出现过多少次
int main(){
	long long n,x,cnt=0;
	cin>>n>>x;
	for(long long i=1;i<=n;i++){
		cin>>a[i];
		hx[a[i]]++;
	}
	for(long long i=1;i<=n;i++){
		if((a[i]^x)==a[i])cnt+=hx[a[i]^x]-1;//特判x是否等于0
		else if((a[i]^x)<=100000)cnt+=hx[a[i]^x];
		//需要判断是否小于1e5，否则数组下标可能越界
	}
	cout<<cnt/2<<endl;
	return 0;
}
```


---

## 作者：LKY928261 (赞：1)

## 题目分析

#### 前置芝士

若 $a$^$b=c$，则 $b=a$^$c$ 。

#### 解题思路

对于每次读入的数 $u$，在计数数组中查询 $u$^$x$ 的个数，进行累加，最后再将 $u$ 进行计数即可。

#### 巨坑

因为异或是一种位运算，所以计数数组必须开到 $2^{17}$ 以上，否则会出现数组越界。

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,x,u,s,a[1048576],i;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>x;
	for(i=0;i<n;i++){cin>>u;s+=a[x^u];a[u]++;}
	cout<<s<<"\n";
}
```

---

## 作者：Chtholly_Tree (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF742B)

## Part 1 题意

$n$ 个数，有一个数字 $x$，定义 $i, j$ 为 $\{1, 2, \ldots n\}$，判断有几个 $a_i$ 异或 $a_j$ 的值为 $x$。

## Part 2 分析

如果使用双层循环，时间复杂度 $O(n^2)$，极限数据时，时间为 $10^5 \times 10^5 = 10^{10}$，超时。

考虑优化。

我们知道，如果 $a \text{\ xor\ } b = c$，那么 $a \text{\ xor\ } c = b, b \text{\ xor\ } c = a$。

举个例子，$5 \text{\ xor\ } 2 = 7, 7 \text{\ xor\ } 2 = 5, 2 \text{\ xor\ } 7 = 5$。

这样，我们就可以使用桶，每次让 $t_{a_i} + 1$，然后每次 $ans + t_{a_i \text{\ xor\ } x}$，就能得到正确结果。

有人可能会问，不会重复吗？

每次 $ans$ 加的时候，只加自己前面的值，自然不会重复。

## Part 3 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2 * 1e5 * 1.1;
int n, x, ans, a[N], tong[N];

signed main () {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> x;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		ans += tong[a[i] ^ x];
		tong[a[i]]++;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：linxuanrui (赞：0)

### 分析

题目让我们求 $a_i\operatorname{xor} a_j=x$ 的数量，显然，我们可以枚举 $a_i$，再求出 $a_j$。

因为异或的逆运算还是异或（也就是说当 $a\operatorname{xor}b=c$，那么 $b=a\operatorname{xor}c$），所以 $a_j=x\operatorname{xor}a_i$，用个 `map` 存储即可。

不过要注意的是，当 $x=0$ 时，$a_i\operatorname{xor}x=a_i$，就会重复统计。


### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
typedef long long ll;
using namespace std;
ll n,x,a[100001],ans;
unordered_map<ll,ll> m;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> x;
	for(int i = 1;i <= n;i++)cin >> a[i],m[a[i]]++;
	for(int i = 1;i <= n;i++){
		ans += m[a[i] ^ x];
		if((a[i] ^ x) == a[i])ans--;
	}
	cout << ans / 2;//刚刚我们算的是包含 i < j 和 i > j 的情况，但题目说这只算一种情况，所以要除以二。
}
```

---

## 作者：DengDuck (赞：0)

可能需要知道一点异或常识的题目。

异或有一个性质：$a\oplus b=c$，则 $a\oplus c=b$。

首先我们知道异或相当于二进制下不用进位的加法，而且我们发现，不但可以理解为这样，其实也是可以看作是不用退位而且每位负数变为整数的减法。

那么就类似于 $a+b=c$，则 $c-a=b$ 的道理了。

所以对于本题我们不妨统计对于每个 $a_i$ 前面有多少 $a_j=a_i\oplus x$，它们就是使 $a_i\oplus a_j=x$ 的数字。

我们可以利用 `map` 来解决，统计即可，时间复杂度为 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
map<LL,LL>ma;
LL n,k,x,ans;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		ans+=ma[x^k];
		ma[x]++;
	}
	cout<<ans<<endl;
}
```

---

## 作者：zjhzs666 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF742B)
# 题意
给出一段长度为 $n$ 的数组及数字 $x$，求有多少对 $a_i$ 和 $a_j$ 满足 $a_i\bigoplus a_j=x$ 且 $1\leq n\leq10^5,0\leq x\leq10^5,1\leq a_i\leq10^5$。

# 思路
首先拿到题目我们可以发现这题似乎可以暴力求解，非常的简洁~~爆时间~~，于是就有了这样一份代码。



```cpp
#include<bits/stdc++.h>
using namespace std;
int x,n,a[100001],s;
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			if((a[i]^a[j])==x)s++;
	cout<<s;
	return 0;
}   
```
~~然后就炸了......~~ 显然不行，可以看到 $n$ 的范围已经到了 $10^5$，而这份代码的时间复杂度大约是 $O(n^2)$，所以我们需要一种更快的方法。


题目需要求有多少对 $a_i$ 和 $a_j$ 满足 $a_i\bigoplus a_j=x$，根据异或的性质：


如果 $A\bigoplus B=C$，则 $A\bigoplus C=B$。
如 $16\bigoplus17=1,16\bigoplus1=17$。


~~~cpp
0 0 1 0 0 0 0   16
0 0 1 0 0 0 1   17
0 0 0 0 0 0 1   1
~~~


我们可以倒推出  $a_i\bigoplus x=a_j$，因此我们只需要统计 $a_i\bigoplus x$ 得出的 $a_j$ 的个数最后输出即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,n,a[200001],y[200001],s,aa;//记得开long long，不然会炸
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s+=y[a[i]^x];//统计在数组中出现的次数
		y[a[i]]++;//记录次数
	}
	cout<<s;
	return 0;
}
```

---

## 作者：SunnyLi (赞：0)

## 思路

题目要求对于 $\forall i,j$ 有多少个 $a_i\oplus a_j=x$。

那么我们需要知道异或最重要的一个性质：

$$a\oplus b=c\Rightarrow a\oplus c=b$$

那么每输入一个数字，我们可以判断与前面输入过的数字是否满足 $a_i\oplus a_j=x$ 即可。若满足则 `sum+=a[t^x]` 即可。注意开 long long 哦。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n,x,t,a[100005]={0},sum=0;
    cin >> n >> x;
    for(int i=1;i<=n;i++){
        cin >> t;
        sum += a[t^x];
        a[t]++;
    }
    cout << sum;
    return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

由异或的性质知，如果 $a \oplus b=c$，那么 $a \oplus c=b$。

对于每一个数 $a$，搜它前面有几个 $b=a \oplus x$。

坑点：要开 `long long`，数组有开大一点。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,sum[100001],ans;
signed main(){
	scanf("%lld%lld",&n,&x);
	for(int i=1;i<=n;i++){
		int a;
		scanf("%lld",&a);
		ans+=sum[a^x];
		sum[a]++;
	}
	printf("%lld",ans);
	return 0;
} 
```

---

## 作者：Larry76 (赞：0)

## 题目大意：

给定 $n$ 个数，找数对使其异或值为 $k$，求满足这样数对的个数。

## 题目分析：

考验位运算功底的题目（实际上也不是很难），主要运用到了下列性质：

$$
\begin{aligned}
\because a \oplus b = k \\
\therefore a \oplus k = b
\end{aligned}
$$

根据上述性质，题意就被转化为了：

>
> 对于任意一个数 $a_x$，问 $a_x \oplus k$ 在数列中的存在数量的和。
>

然后开个桶记录一下每个数的出现次数，求答案的时候我们先将当前数在桶中的数量减一，然后再将答案加上当前数异或 $k$ 在数列中存在的个数。

如果你使用数组开桶，则时间复杂度为 $O(n)$，然而这里我为了防止出现很大很变态的数卡我数组，所以使用的 `map`，时间复杂度 $O(n \log n)$。

## 代码实现：

```cpp
#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<": "<<x<<endl;
#define int long long
using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

namespace Larry76{
    const int MAX_SIZE = 1.1e6;
    map<int,int>hashtable;
    int ori[MAX_SIZE];
    void main(){
        //Code Here;
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>ori[i];
            hashtable[ori[i]]++;
        }
        int ans = 0;
        for(int i=1;i<=n;i++){
            hashtable[ori[i]]--;
            ans += hashtable[ori[i] ^ k];
        }
        cout<<ans<<endl;
    }
}

signed main(){
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    double c1 = clock();
#else
    ios::sync_with_stdio(false);
#endif
//============================================
    Larry76::main();
//============================================
#ifdef LOCAL
    double c2 = clock();
    cerr<<"Used Time: "<<c2-c1<<"ms"<<endl;
    if(c2-c1>1000)
        cerr<<"Warning!! Time Limit Exceeded!!"<<endl;
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
```


---

## 作者：cmk666 (赞：0)

[题目链接](/problem/CF742B)

题目大意：求有多少对 $(i,j)$ 满足 $a_i\operatorname{xor}a_j=x$。

考虑异或的性质，$a_i\operatorname{xor}a_j=x$ 等价于 $a_i\operatorname{xor}x=a_j$。因此对于每一个 $a_j$，统计前面有多少个 $a_i\operatorname{xor}x$ 与它相等即可。

而值域大约是 $2^{17}$ 的，开个桶统计一下即可。

时间复杂度 $O(n)$。核心代码如下：
```cpp
int n, x, a[100009], cnt[150009] = { 0 }; ll ans = 0;
int main()
{
	read(n), read(x);
	For(i, 1, n) read(a[i]), ans += cnt[a[i]], cnt[a[i] ^ x]++;
	return printf("%lld\n", ans), 0;
}
```

---

