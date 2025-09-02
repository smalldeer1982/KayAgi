# [POI 2017] Podzielno

## 题目描述

$B$ 进制数，每个数字 $i \in [0,B)$ 有 $a_i$ 个。你要用这些数字组成一个最大的 $B$ 进制数 $X$（不能有前导零，不需要用完所有数字），使得 $X$ 是 $B-1$ 的倍数。 $q$ 次询问，每次询问 $X$ 在 $B$ 进制下的第 $k$ 位数字是什么（最低位是第 $0$ 位）。

## 说明/提示

对于 $100\%$ 的数据，$2\le B\le10^6$，$1\le q\le 10^5$，$1\le a_i\le10^6$，$0\le k\le10^{18}$。

## 样例 #1

### 输入

```
3 3
1 1 1
0
1
2```

### 输出

```
0
2 
-1```

# 题解

## 作者：jiangly (赞：10)

#### 题意

有一些 $B$ ($2\le B\le 10^6$) 进制数字，其中数字 $i$ 有 $a_i$ ($a_i\ge 1$) 个。现在要用其中的一些组成一个最大的 $B$ 进制数 $X$ 满足 $X$ 是 $B-1$ 的倍数。之后有 $q$ ($1\le q\le 10^5$) 次询问，第 $i$ 次询问 $X$ 从低位数起的第 $k_i$ 个数字是什么 (如果不存在第 $k_i$ 位则输出 $-1$)。

#### 题解

显然 $X$ 是 $B-1$ 的倍数当且仅当 $X$ 所有位的和是 $B-1$ 的倍数。当选择所有数不满足条件时，由于 $a_i\ge 1$，只需要删除对应的一个数字即可。之后将所有数字从大到小排列就是最大的 $X$。每次询问二分即可。

时间复杂度：$O(B+q\log B)$。

#### 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> a(n);
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        sum += i * a[i];
    }
    if (sum % (n - 1) != 0)
        --a[sum % (n - 1)];
    for (int i = 1; i < n; ++i)
        a[i] += a[i - 1];
    for (int i = 0; i < q; ++i) {
        long long k;
        std::cin >> k;
        if (k >= a[n - 1]) {
            std::cout << -1 << "\n";
        } else {
            std::cout << std::upper_bound(a.begin(), a.end(), k) - a.begin() << "\n";
        }
    }
    return 0;
}

```



---

## 作者：ZaleClover (赞：4)

# POI 2017 Podzielno 题解
[更好的阅读体验？](https://www.cnblogs.com/ZaleClover/p/18881668)
## $\text{Step1}$ 思路引入
不难联想到，生活中我们一个数是不是 $9$ 的倍数判别方法是判断它的各位数字之和是否是 $9$ 的倍数，这正是题目中 $B = 10$ 的情况。

于是我们便大胆猜想，是否对于所有 $X$ 的各位数字之和是 $B-1$ 的倍数的时候都满足 $X$ 为 $B-1$ 的倍数。
## $\text{Step2}$ 深入思考
形式化的表示上面的命题：
$$
X\equiv \sum_{i=0}^{B-1}i\times a_i\pmod{B-1}
$$
> 这里的 $\sum\limits_{i=0}^{B-1}i\times a_i$ 表示 $X$ 的各位数字之和。
> 
根据事实，该命题显然正确，下面给出证明：

> 证明：
> $$
> \begin{align*}	
> X &= 1\times a_1\times B^0+2\times a_2\times B^1+\cdots+n\times a_n\times B^{n-1}\\
> &= \sum_{i=0}^{B-1}i\times a_i\times B^{i-1}
> \end{align*}
> $$
> 显然，$B^{i-1}\equiv B^0\pmod{B-1}$，即 $B^{i-1}\equiv1\pmod{(B-1)}$ 那么
> $$
> \begin{align*}
> X&\equiv\sum_{i=1}^{B-1}i\times a_i\times B^{i-1} \pmod{\left(B-1\right)}\\
> &\equiv \sum_{i=1}^{B-1}i\times a_i \pmod{\left(B-1\right)}
> \end{align*}
> $$
> 证毕。

有了上面的结论，我们就可利用 $\sum\limits_{i=0}^{B-1}i\times a_i$ 判断并寻找 $B-1$ 的倍数。

接下来就是满足 $X$ 最大的条件，对于 $B$ 进制数显然位数越多且高位数字越大 $X$ 就越大，那么我们尽量用上所有的数字并让大数字尽量在高位上。如果 $\sum\limits_{i=0}^{B-1}i\times a_i$ 是 $B-1$ 的倍数最好，那不是又该怎么办？注意到 $a_i\ge1$，所以我们直接删掉 $\sum\limits_{i=0}^{B-1}i\times a_i \pmod{\left(B-1\right)}$ 的余数部分即可，满足了数字位数尽可能多的前提。这样对修改后的 $a_i$ 进行一次前缀和，然后二分查找 $k$ 即可。

## $\text{Step3}$ 付诸实践
### $\text{Code}$
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int b, q;
int a[N];
long long sum;
long long s[N];

template <typename type>
void read(type &res) {
    type x = 0, f = 1;
    char c = getchar();
    for (; c < 48 || c > 57; c = getchar()) if (c == '-') f = ~f + 1;
    for (; c > 47 && c < 58; c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
    res = f * x;
}

int main() {
	read(b), read(q);
	for (int i = 0; i < b; i++) read(a[i]);
	for (int i = 0; i < b; i++) sum += 1ll * a[i] * i; // 各位数字求和
	if (sum % (b - 1)) a[sum % (b - 1)]--; // 删去余数部分
	for (int i = 0; i < b; i++) s[i] = s[i - 1] + a[i]; // 前缀和
	for (int i = 1; i <= q; i++) {
		long long k;
		read(k); k++;
		if (k > s[b - 1]) puts("-1"); // 若数字位数没有 k 个，输出 -1 即可
		else printf("%lld\n", lower_bound(s, s + b, k) - s); // 二分查找 k
	}
    return 0;
}
```

---

## 作者：concert_B (赞：3)

# [P5956 [POI 2017] Podzielno](https://www.luogu.com.cn/problem/P5956) 题解

## tip

date: 2025/7/21DAY15

T1 也是花了 10 分钟场切，a_zjzj 还是太没水准了。

## 思路

> 对于任意大于 $2$ 的正整数 $n$，必有 $n-1$ 与它互质。
> 
>形式化的：
>
> $$ \forall n \in (2,+\infty )\cap\N,\gcd(n,n-1)=1 .$$

那么对于任意 $B$ 进制数 $A$。

$$\because B \equiv 1 \pmod{B-1}$$

$$\therefore B^i \equiv 1 \pmod{B-1}$$

$$\because A = \sum p_i\times B^i$$

$$\therefore A \equiv \sum p_i \pmod{B-1}$$

注意题目 $1 \le a_i \le 10^6$，每一位数字至少有一个，那么只要删去一个 $\sum a_i \times i$ 除以 $B-1$ 的余数就能保证 $X$ 是 $B-1$ 的倍数。

**注意**：当 $\sum a_i \times i$ 本身是 $B-1$ 的倍数时，不必删去。

因此，我们只要删数后前缀和，二分 $k$ 即可。

`lower_bound` 不会[点这里](https://www.luogu.me/article/wbkve70e#)。

不知道洛谷专栏什么时候修复，反正先[放着](https://www.luogu.com.cn/article/wbkve70e)。

希望早点修好吧。

## code

```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
const int N=1e6+5;
int n,m,s;
int mod;
int a[N];
int pre[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	mod=n-1;
	for(int i=0;i<n;i++)
		cin>>a[i],s=(s+a[i]*i%mod)%mod;
	if(s)	a[s]--;//特判
	pre[0]=a[0];
	for(int i=1;i<n;i++)
		pre[i]=pre[i-1]+a[i];
	while(m--){
		int k;
		cin>>k;
		int ans=lower_bound(pre,pre+n,k+1)-pre;
		if(ans==n){
			cout<<-1<<'\n';
			continue;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```


完结撒花！！！

---

## 作者：fish_love_cat (赞：2)

注意到 $x\times B^k\equiv x\pmod {B-1}$，于是可以得到这个数字的数位和与该数字在模 $B-1$ 的意义下相等。

然后观察数据范围，注意到 $a_i\ge 1$，这启示我们可以直接求所有数位的加和，然后减去一个位置就行了。数据范围表明这样的数位是一定存在的。

那么做完了，上一个前缀和然后对于每一个询问二分位置即可。

记得开 `long long`！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000005],sum;
signed main(){
    int B,q;
    cin>>B>>q;
    for(int i=0;i<B;i++)
    cin>>a[i],sum+=a[i]*i,sum%=B-1;
    if(sum)a[sum]--;
    for(int i=1;i<B;i++)a[i]+=a[i-1];
    while(q--){
        int x;
        cin>>x;x++;
        if(x>a[B-1])puts("-1");
        else cout<<(lower_bound(a,a+B,x)-a)<<'\n';
    }
    return 0;
}
```

---

## 作者：pengziyippp (赞：1)

## 题目大意  
给出一个 $B$ 进制的数 $X$，每个数字 $i \in [0,B)$ 有 $a_i$ 个。用数字组成最大 $X$ 使其是 $B-1$ 的倍数，并回答 $q$ 个第 $k$ 位是什么的询问。     
## 思路简述  
水题但赛时没有想出来，果然我是废物捶石了。  
思考观察在 $B$ 进制下一个数是 $B - 1$ 的倍数有什么性质。  
由于我们知道，在 $B$ 进制下，一个数由由多个 $B^{x}$ 组成，若我们使用 $ans[i]$ 表示 $X$ 第 $i$ 位的大小，则可得：  
$X = B^{0} \times ans[0] + B^{1} \times ans[1] + B^{2} \times ans[2] + \cdots$  
这里我们可以观察到 $B^{x}$ 一定不为 $B-1$ 的倍数，所以要想使 $X$ 为 $B-1$ 的倍数，我们只能将所有 $ans[i]$ 的和控制为 $B-1$ 的倍数。  
如何控制为 $B - 1$ 的倍数呢，由于 $a[i]\ge1$，即 $0$ ~ $B-1$ 每个数都至少给出了一个，所以我们只需要判断一下所有给出的数字之和是不是 $n-1$ 的倍数，若不是，删去 $sum$ 多余的部分即为最小代价，因为我们要保证最大时 $X$ 的位数应该尽可能的多。    
再考虑如何最大化，我们容易想到将数字大的放前面，小的放后面，最后判断一下位置输出答案即可。  
完结撒花。
## 代码实现  
马蜂良好。  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
int a[N], sum[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    int b, q; cin >> b >> q;
    int summ = 0, maxx = 0;
    for (int i = 0; i <= b - 1; i ++ ) {
    	cin >> a[i];
    	summ += (a[i] * i); // 统计和 
    	maxx += a[i]; // 统计出最多有多少位 
	}  
	if (summ % (b - 1)) a[summ % (b - 1)] --, maxx --; // 处理掉多余的数 
	sum[0] = a[0];
	for (int i = 1; i <= b - 1; i ++ ) {
		sum[i] = sum[i - 1] + a[i];
	} // 计算到数字i有多少个数位 
	for (int i = 1; i <= q; i ++ ) {
		int k; cin >> k;
		k ++; // 处理第0位 
		if (k > maxx) {
			cout << -1 << "\n"; // 判断是否存在 
		} else {
			cout << lower_bound(sum, sum + b - 1, k) - sum << "\n"; // 找出答案 
		}
	}
}
```

---

## 作者：Zhl2010 (赞：1)

首先这道题有一个结论：$B$ 进制数，如果 $X \bmod B-1$ 为 $0$，$X$ 的每一位相加一定是 $B$ 的倍数，比如 $10$ 进制，$9$ 的整除规律就符合这一点。


## 证明


首先：

$$X=a_1 \times B^0+a_2 \times B^1+a_3 \times B^2+a_4 \times B^3+\cdots$$

所以：

$$(a_1 \times B^0+a_2 \times B^1+a_3 \times B^2+a_4 \times B^3+\cdots)\equiv 0 \pmod {(B-1)}$$

然后我们发现：

$$B^k \equiv 1 \pmod {(B-1)}$$

所以将它带进去：

$$(a_1+a_2+a_3+a_4+\cdots)\equiv 0 \pmod {(B-1)}$$

---

根据这个和 $1\le a$，所以将 $X$ 减去 $X \bmod (b-1)$ 这一位，剩下的就是答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int b,q,a[1000010];
int bb[1000010];
struct node{
	int k,id;
}k[1000010];
bool cmp(node a,node b){
	return a.k<b.k;
}
int ans[1000010];
int mn=INT_MAX;

signed main(){
//	for(int i=1;i<=500;i++)cout<<9*i<<endl;
//	return 0;
	cin>>b>>q;
	int sum=0;
	for(int i=0;i<b;i++){
		scanf("%lld",&a[i]);
		sum+=a[i]*i;
	}
	int t=sum%(b-1);
	if(t!=0)a[t]--;
	for(int i=0;i<b;i++){
		bb[i]=bb[i-1];
		bb[i]+=a[i];
		//cout<<bb[i]<<endl;
	} 
	for(int i=1;i<=q;i++){
		scanf("%lld",&k[i].k);
		k[i].k++;
		k[i].id=i;
	}
	sort(k+1,k+q+1,cmp);
	int now=0;
	for(int i=1;i<=q;i++){
		//cout<<k[i].k<<' '<<bb[b-1]<<endl;
		if(k[i].k>bb[b-1]){
			ans[k[i].id]=-1;
			continue;
		}
		while(k[i].k>bb[now])now++;
		ans[k[i].id]=now;
		//else ans[k[i].id]=0;
	}
	for(int i=1;i<=q;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}

```

---

## 作者：yxy666 (赞：1)

首先我们需要证明一个很玄学的东西，也就是 若 $X$ 是 $B-1$ 的倍数，则各位数字加和一定也是 $B-1$ 的倍数。

证：设 $X$ 是 $B-1$ 的倍数，将 $X$ 拆分成 B 进制后，就为 $a_1*B^0+a_2*B^1+a_3*B^2+a_4*B^3+...+a_9*B^8$。也就是说$(a_1*B^0+a_2*B^1+a_3*B^2+a_4*B^3+...+a_9*B^8)\bmod(B-1)=0$。
将每一项分别 $\bmod$，我们会发现对于每一个 $B^k\bmod (B-1)=1$。为什么呢？将其拆分成$B*B*B*B*B*B*B*B*...*B$的形式，每一个都$\bmod(B-1)$，刚好为 $1$。所以就变成了$(a_1+a_2+a_3+a_4+...+a_9)\bmod(B-1)=0$。

那么我们将余下来的以为扣掉就好了。为什么只扣余数？如果扣其他的，就要扣 2 位及以上，数字就不是最大的了。对于询问，可以通过二分来查找。

code :
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int n,Q,a[maxn];
long long sum,k,s[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	n=read();Q=read();
	for(int i=0;i<n;i++)a[i]=read(),sum+=(long long)i*a[i];
	if(sum%(n-1)!=0)a[sum%(n-1)]--;
	for(int i=0;i<n;i++)s[i]=s[i-1]+a[i];
	while(Q--){
		scanf("%lld",&k);
		int L=0,R=n-1,mid,Ans=-1;
		while(L<=R){
			mid=(L+R)/2;
			if(s[mid]>k)Ans=mid,R=mid-1;
			else L=mid+1;
		}
		printf("%d\n",Ans);
	}
	return 0;
}
```


---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

有这么一个性质，若一个 $x$ 进制数 $a$ 是 $x-1$ 的倍数，那么其每一位的和是 $x-1$ 的倍数。证明：

假设这个数 $a=a_na_{n-1}\dots a_1a_0$，那么 $a=\sum_{i=0}^na_i\times x^i$。而我们又知道 $\forall i\ge0,x^i\equiv1\pmod{x-1}$，于是 $\sum_{i=0}^na_i\times x^i\equiv\sum_{i=0}^na_i\pmod{x-1}$，证毕。

说白了，你就只需要选出来一堆数，使其和为 $x-1$ 的倍数。

更加神奇的一点在于，$[0,B)$ 每个数都至少有一个。于是，我们算出其和之后，再抛弃掉一个多出来的那个数就完了。特判余数为 $0$ 的情况。此时不抛弃。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif
inline int read() {
	int r = 0; char c = getchar_unlocked();
	while (c < '0' || c>'9') c = getchar_unlocked();
	while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = getchar_unlocked();
	return r;
}
inline void write(long long x) {
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 ^ 48);
}
inline void writi(long long args) {
	write(args); putchar_unlocked(10);
}
constexpr bool online = 0;
int n, m, a[1000005], sm;
signed main() {
	if (online)
		freopen("Podzielno.in", "r", stdin),
		freopen("Podzielno.out", "w", stdout);
	ios::sync_with_stdio(0);
	n = read(); m = read();
	for (int i = 0;i < n;++i)
		a[i] = read(), sm += a[i] * i;
	sm %= (n - 1); if (sm) a[sm]--;
	for (int i = 1;i <= n;++i) a[i] += a[i - 1];
	for (int i = 1, p;i <= m;++i)
		p = read(), p++, cout << ((a[n] >= p) ?
			(lower_bound(a, a + n, p) - a) : (-1)) << '\n';
	return 0;
}
//私は猫です
```

---

## 作者：MoonCake2011 (赞：0)

一个数 $X$ 能被 $B-1$ 整除，当且仅当 $X$ 所有数位上的数之和能被 $B-1$ 整除。

于是可以先选择所有数，求和 $sum$，相当于我们需要减去 $sum \bmod (B-1)$。

说重点，$a_i>1$。

所以就直接只用删掉一个 $sum \bmod (B-1)$，就可以使得 $X$ 能被 $B-1$ 整除。

因为删去的数最少，位数最多，所以把所有数从大到小排序后，此数最大。

于是就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[1000010],sum; 
int main() {
	cin>>n>>m;
	for(int i=0;i<n;i++) cin>>a[i],sum+=i*a[i];
	if(sum%(n-1)!=0) a[sum%(n-1)]--;
	for(int i=1;i<n;i++) a[i]+=a[i-1];
	while(m--){
		int k;
		cin>>k;
		if(k>=a[n-1]) cout<<"-1\n";
		else cout<<upper_bound(a,a+n,k)-a<<"\n";
	}
	return 0;
}
```

---

## 作者：luogu_MeiFengqi (赞：0)

### 前言
由于本蒟蒻的思路已经被楼下几个大佬说的很明白了，所以本蒟蒻就再介绍两个有用的函数 $\operatorname{lower\_bound}$ 与 $\operatorname{upper\_bound}$。
___
#### $\operatorname{lower\_bound}$:
使用：`
lower_bound(a+begin,a+end,num)
`。

含义：从有序数组 $a$ 的 $begin$ 位置到 $end-1$ 位置二分查找**第一个大于等于 $num$** 的数并返回一个迭代器（此数字地址），不存在则返回 $end$。通过返回的地址减去 $a$，就可以得到数字在该数组中的下标。
___
#### $\operatorname{upper\_bound}$：
使用：一切同 $\operatorname{lower\_bound}$。

含义：与 $\operatorname{lower\_bound}$ 唯一不同的是查找**第一个大于 num** 的数。
### 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int b,q;
int a[1000010],sum;
signed main(){
	cin >> b >> q;
	for (int i = 1; i <= b; i++)
	{
		cin >> a[i];
		sum += (i-1)*a[i];
	}
	if (sum%(b-1)) a[sum%(b-1)+1]--;
	for (int i = 1; i <= b; i++)
	a[i] += a[i-1];//前缀和
	while (q--)
	{
		int k;
		cin >> k;
		int find = upper_bound(a+1, a+b+1, k)-a;//二分查找
		if (find == b+1) cout << -1 << endl;
		else cout << find - 1 << endl;
	}
    return 0;
}
```

---

## 作者：caohan (赞：0)

# 推荐
~~[我的博客](https://www.luogu.com.cn/blog/713916/)~~

# 题意

求在 $b$ 进制下, $0$  至  $b-1$  分别有  $a_i$  个，能整除  $b-1$  的最大值的第  $k$   位是多少。

# 前置证明

在 $b$ 进制下，$x$ 要是为 $b-1$ 的倍数，$x$ 的数字和必为 $x-1$ 的倍数。

以十进制为例

设 $x$ 的第 $y$ 位值是 $x_y$ ，$n$ 为 $x$ 的位数 ( 个位是第一位 ）。
可得 $x$  的数字和为：$x_1+x_2+x_3+\cdots+x_n$

 $x$ 也可表示为：$10^0\times x_1+10^1\times x_2+\cdots+10^n\times x_n$
 
 $x$ 和 $x$ 的数字和的差是 $9$ 的倍数 （小学知识）。

而由于 $(a\pm b)\bmod c=(a \bmod c+b \bmod c)\bmod c$

可知 $x$ 为  $9$  倍数时，$x$ 数字和也为 $9$ 倍数。

该规律可推广至 $b>1$ 的任何数。

# 思路

先算出题目给的这些数字的和，再扣除一个它除 $b-1$ 的余数的个数，再用前缀和统计，之后二分答案
查找即可。
# 代码

粘贴不可取，洛谷同维护。

```cpp
#include<bits/stdc++.h>
#include<iostream>
using namespace std;
long long n;long long q;
long long a[1000005];
long long p[1000005];//前缀和 
long long sum;
long long erfen(long long k,long long l,long long r)//二分答案 
{
	long long ans=-1;
	
	while(l<=r)
	{
		long long mid=(l+r)/2;
		if(p[mid]>k)
		{
			ans=mid;r=mid-1;
		}
		else 
		{
			l=mid+1;
		}
	}
	return ans;
}
int main()
{
	cin>>n>>q;
	for(long long i=0;i<n;i++)
	{
		cin>>a[i];
		sum+=a[i]*i;
	}
	if(sum%(n-1)!=0)
	{
		a[sum%(n-1)]--;
	}
	for(long long i=0;i<n;i++)
	{
		p[i]=p[i-1]+a[i];
	}//先删后算 
	while(q--)
	{
		long long k;
		cin>>k;
		cout<<erfen(k,0,n-1)<<endl;
		cout<<"1"; 
	}
	return 0;
}
```

---

## 作者：panyanppyy (赞：0)

一眼发现结论。
## Problem

在 $B$ 进制下，你有 $a_i$ 个数字 $i$，问拼出来最大的 $(B-1)$ 的倍数第 $k$ 位是多少，$q$ 次询问。

$\mathbf 1\le a_i\le10^6,q\le 10^5,2\le B\le10^6,k\le 10^{18}$
## Solution

转换一下就是拼出来的数 $\mod(B-1)\equiv0$。

考虑 $B$ 进制数的性质，$B$ 进制数 $X$ 一定是形如以下形式：

$$\sum B^i\times X_i$$

然后对 $B-1$ 取模会发现 $B^i\pmod {B-1} \equiv 1$，因为 $B\pmod{B-1}\equiv1$，所以式子就变成了：

$$\sum X_i$$

也就是所有数位的和。

接下来考虑怎么拼，当然要位数最多并且从大到小取。

取所有的数，如果所有的和 $\pmod{B-1}\ne0$，直接减掉多余的那个数就行了。

做一遍前缀和，然后每次询问直接二分就好了。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
using namespace std;
template<typename T_>void operator+=(vector<T_>&x,const T_&y){x.push_back(y);}
template<typename T_>void Min(T_&x,const T_&y){if(y<x)x=y;}
template<typename T_>void Max(T_&x,const T_&y){if(y>x)x=y;}
const int N=1e6+7;
int n,m;
ll sum,a[N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],sum+=(i-1)*a[i];
	if(sum%(n-1))a[sum%(n-1)+1]--;
	for(int i=1;i<=n;i++)a[i]+=a[i-1];
	for(int i=1;i<=m;i++){
		static ll k;
		cin>>k;
		auto it=upper_bound(a+1,a+n+1,k);
		if(it==a+n+1)cout<<"-1\n";
		else cout<<it-a-1<<'\n';
	}
	return 0;
}
```

---

## 作者：LiuHao2019 (赞：0)

由于本蒟蒻的思路已经被楼下大佬说过了/kk，所以本蒟蒻就补一个证明过程吧

>大佬:显然 $X$ 是 $B-1$ 的倍数当且仅当 $X$ 所有位的和是 $B−1$ 的倍数。

我: ? ? ?


------------

既然在 $B$ 进制下证明很难，那就先证明: 十进制下， $9$ 的倍数所有位的和是 $9$ 的倍数

我们可以设 $X = X_1 * 10^0 + X_2 * 10^1 + X_3 * 10^2 + …… + X_n * 10^{n-1} = 9k (k∈N+)$ $1\kern{-7.5pt} \bigcirc$

但是我们要证明 $X_1 + X_2 + X_3 + …… + X_n$ $2\kern{-7.5pt} \bigcirc$ 可以被 $9$ 整除

用 $1\kern{-7.5pt} \bigcirc$ 式减去 $2\kern{-7.5pt} \bigcirc$ 式，可得:

$(X_1 * 10^0 + X_2 * 10^1 + X_3 * 10^2 + …… + X_n * 10^{n-1}) - (X_1 + X_2 + X_3 + …… + X_n) = X_2 * 9 + X_3 * 99 + …… + X_n * (10^{n-1}-1) = 9 * (X_2 * 1 + X_3 * 11 + …… + X_n * [n$个$1])$

这个式子可以被 $9$ 整除，且 $1\kern{-7.5pt} \bigcirc$ 式可以被 $9$ 整除，所以 $2\kern{-7.5pt} \bigcirc$ 式可以被 $9$ 整除，得证

------------

用同样的方法，我们可以在 $B$ 进制下证明 $(B-1)$ 的倍数所有位上数之和是 $(B-1)$ 的倍数:

我们可以设 $X = X_1 * B^0 + X_2 * B^1 + X_3 * B^2 + …… + X_n * B^{n-1} = (B-1)k (k∈N+)$ $1\kern{-7.5pt} \bigcirc$

但是我们要证明 $X_1 + X_2 + X_3 + …… + X_n$  $2\kern{-7.5pt} \bigcirc$ 可以被 $(B-1)$ 整除

用 $1\kern{-7.5pt} \bigcirc$ 式减 $2\kern{-7.5pt} \bigcirc$ 式，得:

$(X_1 * B^0 + X_2 * B^1 + X_3 * B^2 + …… + X_n * B^{n-1}) - (X_1 + X_2 + X_3 + …… + X_n) = X_2 * (B-1) + X_3 * (B^2-1) + …… + X_n * (B^{n-1}-1)$

与上面的方法类似,我们需要证明 $B^{n-1}$ 可以被 $(B-1)$ 整除

通过因式分解可得 $B^n-1 = (B-1) * (1+B+B^2+……+B^{n-1})$

得证

注:因式分解的证明可见于 [这里](https://www.luogu.com.cn/paste/p26j2yrp)

---

