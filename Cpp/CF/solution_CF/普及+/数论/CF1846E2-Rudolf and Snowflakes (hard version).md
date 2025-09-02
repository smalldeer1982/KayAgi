# Rudolf and Snowflakes (hard version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ n \le 10^{18} $ .

One winter morning, Rudolf was looking thoughtfully out the window, watching the falling snowflakes. He quickly noticed a certain symmetry in the configuration of the snowflakes. And like a true mathematician, Rudolf came up with a mathematical model of a snowflake.

He defined a snowflake as an undirected graph constructed according to the following rules:

- Initially, the graph has only one vertex.
- Then, more vertices are added to the graph. The initial vertex is connected by edges to $ k $ new vertices ( $ k > 1 $ ).
- Each vertex that is connected to only one other vertex is connected by edges to $ k $ more new vertices. This step should be done at least once.

The smallest possible snowflake for $ k = 4 $ is shown in the figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1846E2/2fc3f5caf761ddee75c017a3deae10ee696f63d1.png)After some mathematical research, Rudolf realized that such snowflakes may not have any number of vertices. Help Rudolf check whether a snowflake with $ n $ vertices can exist.

## 样例 #1

### 输入

```
9
1
2
3
6
13
15
255
10101
1000000000000000000```

### 输出

```
NO
NO
NO
NO
YES
YES
YES
YES
NO```

# 题解

## 作者：sgl654321 (赞：9)

### 题目大意
判断一个数 $n$ 是否可以写成 $1+k+k^2+k^3+\cdots+k^q$ 的形式。其中 $k\ge 2,q\ge 2$，$k,q$ 均为整数。$n\le 10^{18}$。

### 解题思路
首先，$k<\sqrt{n}\le10^9$。如果直接枚举 $k\in[2,\sqrt{n}]$，那么执行次数一定超过了十亿，就会超时。

怎么办呢？我们发现，后面有很多很多 $k$，它都只能对应一个 $q=2$。如果 $q=3$，那么就超出 $n\le 10^{18}$ 的范围了。

这样的 $k$ 一定大于 $\sqrt[3]n$，即 $k\ge 10^6$。

我们就把合法的 $k$ 分成了两段。

第一段： $k\in[2,10^6-1]$，这些 $k$ 我们采用 CF1846E1 的方法，直接枚举 $k$，枚举 $q$，并将合法的 $n$ 标记出来。由于 $n$ 这里比较大，我们可以使用 STL 中的 ```map```。

第二段： $k\in[10^6,10^9-1]$。这一段最多只有一个对应的 $q$，即 $q=2$。


每输入进一个 $n$，我们先看看 ```map``` 中它是否被标记为合法答案。如果是，那么直接输出 ```YES```。如果不是，我们再思考第二段。

由于 $1+k+k^2$ 在 $k\in[10^6,10^9-1]$ 是单调递增的，我们可以使用二分查找的办法。或者，我们可以用一元二次方程求根公式，求出 $k$，看看是不是整数，而且在 $k\in[10^6,10^9-1]$ 范围内。

### 参考代码
在第一段标记 ```map``` 时，由于 $10^{18}$ 实在太大了，我怕爆 ```long long```，就使用了下 ```__int128```。

第二段我用的是二分查找，没有用一元二次方程求根公式。
```cpp
#include<bits/stdc++.h>
using namespace std;

long long tt,n;
__int128 now; 
map<long long,bool>f;

long long l,r,mid;
bool flag;
int main(){
	cin>>tt;
	for(long long k=2;k<=1000000;k++){
		now=k*k;
		for(long long q=2;;q++){
			now=now*k;
			if((now-1)/(k-1)>1e18)break;
			else f[(now-1)/(k-1)]=1;
		}	
	}
//	cout<<f.size()<<endl;//实测 f.size()=2037542，可以接受
	while(tt--){
		cin>>n;
		if(f[n])cout<<"YES"<<endl;
		else{
			flag=0;
			l=1000001;r=1000000000;
			while(l<=r){
				mid=(l+r)>>1;
				if(mid*mid+mid+1==n){
					flag=1;
					break;
				}
				if(mid*mid+mid+1<n)l=mid+1;
				else r=mid-1;
			}
			if(flag)cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
	return 0;
}

```

---

## 作者：escapist404 (赞：5)

# CF1846E2 Rudolf and Snowflakes (hard version) 题解

### Statement

$T$ 次给定整数 $n$，判断是否存在 $q, k \ge 2$ 使得 $1 + q + q^2 + \cdots + q^k = n$。

$1 \le T \le {10^4}$，$1 \le n \le {10}^{18}$。

### Solution

考虑弱化问题 CF1846E1。这里 $1 \le n \le {10}^6$。

设 $w = {10}^6$，可能的 $n$ 的数量是

$$
\begin{aligned}
s&=\log_2 w + \log_3 w + \cdots + \log_{\sqrt{w}} w\\
&= \ln w (\frac{1}{\ln2} + \frac{1}{\ln3} + \cdots + \frac{1}{\ln\sqrt{w}}).\\
\end{aligned}
$$

这里 $s \approx 2453.4073$。[Link.](https://www.wolframalpha.com/input?i=sum+from+1+to+1e3+of+%5Cdfrac%7B1%7D%7B%5Clog%28n+%2B+1%29%7D+times+%5Clog+1e6)

打表存进 `set` 里面即可。

但是这题 $1 \le n \le {10}^{18} = w$，估计一下必然超时了。

注意到

$$999999 ^3 + 999999 ^2 + 999999 + 1 = 999,998,000,002,000,000 < {10}^{18}.$$

$$1000000 ^3 + 1000000 ^2 + 1000000 + 1 = 1,000,001,000,001,000,001 > {10}^{18}.$$

大可以枚举 $2 \sim {10}^6 - 1$ 的数作为 $q$，把所有合法的 $n$ 存进 `set` 容器。

可能的 $n$ 的数量是

$$
\begin{aligned}
S &= \log_2 w + \log_3 w + \cdots + \log_{\sqrt[3]{w}} w \\
&= \ln w (\frac{1}{\ln2} + \frac{1}{\ln3} + \cdots + \frac{1}{\ln\sqrt[3]{w}}).\\
\end{aligned}
$$

这里 $S \approx 3.258 \times 10^6$。[Link.](https://www.wolframalpha.com/input?i=sum+from+1+to+1e6+of+%5Cdfrac%7B1%7D%7B%5Clog%28n+%2B+1%29%7D+times+%5Clog+1e18)

对于不小于 ${10}^6$ 的数怎么做？

注意到它们已经没有 $k \ge 3$ 的解了。具体地，假设存在一个 $q_0$ 和 $k = 2$ 使得 $q_0^2 + q_0 + 1 = n$，容易得到（另一根舍去）

$$
q_0 = \frac{-1 + \sqrt{4n - 3}}{2}.
$$

求出 $q_0$ 后再代回方程验证即可。

这样，我们在 $O(S \log S + T\log S)$ 的时间内解决了此问题。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

set <__int128> s;

const __int128 INF = 1000000000000000000ll;

int main()	{
	for(long long i = 2; i <= 1000000; ++i)	{
		__int128 j = i + 1;
		__int128 l = i * i;
		while(j + l <= INF)	{
			j += l;
			l *= i;
			s.insert(j);
		}
	}
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int tt;
	cin >> tt;
	while(tt--)	{
		long long x;
		cin >> x;
		if(s.count(x))	{
			cout << "YES" << endl;
		}
		else if(x >= 1000000000000ll){
			long long delta = 1 - 4 * (1 - x);
			long long x1 = 0.5 * (-1 + sqrt(delta));
			if(x1 * x1 + x1 + 1 == x)	{
				cout << "YES" << endl;
			}
			else	{
				cout << "NO" << endl;
			}
		}
		else	{
			cout << "NO" << endl;
		}
	}
}
```



---

## 作者：Coffee_zzz (赞：4)

### 分析

我们首先观察给定的雪花：它的第 $1$ 层有 $1$ 个节点，第 $2$ 层有 $4$ 个节点，第 $3$ 层有 $16$ 个节点。

可以发现它第 $i\ (i \gt 1)$ 层的节点数为第 $i-1$ 层节点数的 $4$ 倍。

同理，对于 $k$ 为其他值的雪花，第 $i\ (i \gt 1)$ 层的节点数为第 $i-1$ 层节点数的 $k$ 倍，那么这个雪花的总点数就是 $1+k+k^2+k^3+\cdots k^{p-1}$，其中 $p$ 为这个雪花的层数。也就是说如果一个数可以写成 $1+k+k^2+k^3+\cdots k^{p-1}$ 的形式，它就可以作为一个雪花的顶点数。

由于 $k$ 最小是 $2$，$n$ 最大是 $10^{18}$，那我们的 $p$ 只需要枚举到 $63$ 即可。

同时由于 $p$ 最小是 $3$，$n$ 最大是 $10^{18}$，那我们的 $k$ 只需要算到 $10^9$ 即可。

$p$ 的范围只有 $2 \sim 63$，直接枚举。$k$ 可以二分，判断是否存在 $k$ 满足 $1+k+k^2+k^3+\cdots k^{p-1}=n$ 即可。

要注意二分的 `check()` 函数中，计算过程可能会爆 `long long`，需要使用 `__int128`。

```c++
#define int long long
const int P=1e9,K=2e18;
int check(int m,int i){
	__int128 p=1,las=1;
	for(int k=1;k<=i;k++){
		las=las*m;
		p=p+las;
		if(p>=K) return K;
	}
	int res=p;
	return res;
}
void solve(){
	int n=read(),l,r;
	for(int i=2;i<=62;i++){
		l=2,r=P;
		while(l<=r){
			int m=(l+r)/2,p=check(m,i);
			if(p==n){
				puts("Yes");
				return;
			}
			else if(p<n) l=m+1;
			else if(p>n) r=m-1;
		}
	}
	puts("No");
}
```

---

## 作者：引领天下 (赞：3)

题意：

给定一个 $n$，试判断其能否表示成 $1+k+k^2+k^3+\dots+k^m$ 的形式。

做法：

考虑计算这个式子。

$1+k+k^2+\dots+k^m=\frac{k^{m+1}-1}{k-1}$。

那么我们现在就需要枚举 $k,m$。

直接枚举显然是寄的，所以我们考虑分段。

注意到如果 $m>10$，那 $k^m$ 会相当恐怖，此时 $k$ 的可能取值必然很小，所以分 $m\le10,m>10$ 两种情况分别枚举。

- $m\le10$：此时的 $k$ 可能取值较多，所以我们写一个二分来判断是否存在可能的 $k$。

- $m>10$：此时 $k$ 必然很小，所以直接从 $2$ 开始向上枚举即可。

为了加速写了个快速幂。运算过程中数字会达到 $n^2=10^{36}$ 级别，所以需要使用 `__int128`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
inline __int128 qpow(__int128 x,int p){
    __int128 sum=1;
    while(p){
        if(p&1)sum*=x;
        x*=x;p>>=1;
    }
    return sum;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        bool ok=0;
        for(int m=3;!ok&&m<=10;m++){
            __int128 l=2,r=pow(n,1.0/(m-1)),ans=-1,mid;
            while(l<=r){
                mid=(l+r)>>1;
                __int128 k=qpow(mid,m)-1;
                if(k==(mid-1)*n){ans=mid;break;}
                else if(k>(mid-1)*n)r=mid-1;
                else l=mid+1;
            }
            ok|=(ans!=-1);
        }
        for(int m=11;!ok&&m<=log2(n+1)+1;m++)
        for(int b=2;!ok&&qpow(b,m)-1<=(b-1)*n;b++)if(qpow(b,m)-1==(b-1)*n)ok=1;
        cout<<(ok?"YES":"NO")<<endl;
    }
    return 0;
}
/*
b^m-1=(b-1)n
*/
```

---

## 作者：Otue (赞：2)

## 题意
给定 $n(1\leq n\leq 10^{18})$，存不存在 $k,p(k≥2,p≥2)$ 满足 $1+k^2+k^3+...+k^p=n$。
## 分析
考虑 $p$ 的最大值：取 $k$ 的最小值 $2$，可求出 $p$ 最大值约为 $63$。

考虑 $k$ 的最大值：取 $p$ 的最小值 $2$，可求出 $k$ 最大值约为 $10^9$。
 
既然 $p$ 的范围不大，那么我们枚举 $p$，因为 $1+k^2+k^3+...+k^p$ 满足随着 $k$ 增大则增大的性质，可以二分符合条件的 $k$。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int __int128
const int N = 2e5 + 5;

int t, n;

int read() {
	char c = ' ';
	int f = 1, x = 0;
	while (c <  '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int check(int x, int p) {
	__int128 ans = 0, kk = 1; // 这里会爆 long long，须开__int128
	for (int i = 1; i <= p + 1; i++) {
		ans += kk;
		kk *= x;
		if (ans > n) return 1; // 二分结果大于n
	}
	if (ans == n) return 2; // 二分结果等于n
	else return 0; // 二分结果小于n
}

signed main() {
	t = read();
	while (t--) {
		n = read();
		int flg = 0;
		for (int i = 2; i <= 63; i++) {
			int l = 2, r = 1e9;
			while (l < r) {
				int mid = (l + r) >> 1;
				int t = check(mid, i);
				if (t == 1 || t == 2) r = mid; // 如果二分结果大于等于n，调整右端点
				else l = mid + 1; // 否则调整左端点
			}
			if (check(l, i) == 2) { // 最后需要检查答案是否恰好为n
				flg = 1;
				break;
			}
		}
		if (flg) puts("Yes");
		else puts("No");
	}
}
```

---

## 作者：Nwayy (赞：1)

考场上也是切完 E2 没剩多少时间了，前面的时间花的还是太多了。

---

观察一下就会发现，所谓“雪花图”，其实每一层的点数都是上一层的 $k$ 倍。

发现这个后题目可以转换成：给出一个整数 $n$，问是否能找出一个二元组 $(k,m)$ 使得 $\sum\limits_{i=0}^mk^i=n$，其中必须保证 $k \ge 1,m \ge 2$。

先考虑弱化版：对于 $10^6$ 级别的数据，我们显然可以枚举 $k \in [2,10^3]$，在此过程中让 $k^i$ 不断乘上 $k$，其实和题意是等价的，最后把这过程中得到的所有数在数组里标记即可。而注意到 $m \ge 2$，所以至少有 $k^2$，因此对于 $10^6$ 级别而言，枚举这么多就够了。时间复杂度 $\mathcal {O}(\sqrt n \log \sqrt n)$。

再来看 $10^{18}$ 级别的数据。我们显然不能按照 E1 做法去做，但是可以发现，对于某个整数 $n=k^0+k^1+k^2$，我们可以转换为 $k(k+1)=n-1$，这个显然可以直接判断是否合法，那我们 E1 中的预处理其实只是找 $m \ge 3$ 的情况而已。但是注意到，当 $k \ge 10^6$ 时，$m$ 不可能大于 $2$。所以我们只需要在原先的基础上多枚举到 $10^6$，把此过程中得到的所有数存进 ```map``` 里，剩下的只需判断是否有 $m=2$ 的情况即可。时间复杂度 $\mathcal {O}(\sqrt [3]{n} \log \sqrt [3]{n})$。

**提醒**：

1. 此做法最好特判 $1,2,3$。

1. E2 实现过程中容易爆， 最好先处理自乘的边界。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000005
#define int unsigned long long
int n,m,i,j,ans,T,flag,x,P[N];
map<int,int>f;
int get(int a,int b){
	int cnt=0;
	while(a) a/=b,cnt++;
	return cnt;
}
void check(int k){
	int sum=0,s=1,p=P[k];
	for(int i=1;i<=p;i++){
		sum+=s,s*=k;
		if(i>=3 && sum<=(int)1000000000000000000) f[sum]=1;
	}
}
signed main(){
	for(i=2;i<=1000000;i++){
		P[i]=get(1000000000000000000,i);
		check(i);
	}
	scanf("%llu",&T);
	while(T--){
		scanf("%llu",&x);
		if((int)sqrt(x-1)*(int)(sqrt(x-1)+1)==x-1 && (int)sqrt(x-1)!=1 && (int)sqrt(x-1)!=0) printf("YES\n");
		else if(f[x]) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

```


---

## 作者：_sunkuangzheng_ (赞：1)

**【题目分析】**

首先观察图的性质，容易发现第一层有 $1$ 个点，第二层 $k$ 个，第三层 $k^2$ 个，由此类推不难发现对于一张每次扩展 $k$ 个点，扩展 $x$ 次的图，其点数为 $\sum\limits^{x}_{i=0}k^i = \dfrac{k^{x+1}-1}{k-1}$。

因此我们的问题变为：给定整数 $n$，构造正整数 $x,k(x,k \ge 2)$ 使得 $\dfrac{k^{x+1}-1}{k-1} = n$。

观察到当 $x \ge 4$ 时暴力枚举的单次复杂度为 $\Theta(n^3)$，单测下可以通过。那么考虑 $x = 3$ 时如何做。容易发现，答案是具有单调性的，即随 $k$ 的增大而增大。因此直接二分，复杂度 $\Theta(\log n)$。

因为本题多测，所以需要优化 $x \ge 4$ 时的算法。容易发现合法解的数量较少，所以开一张 `map` 预处理记录合法位置的权值，我们只需要用 $3$ 张 `map` 维护 $x = \{4,5,6\}$ 时的答案，其他答案暴力即可。这部分的时间复杂度为 $\Theta(\log n \sqrt[7]n)$。

总的时间复杂度为 $\Theta(\sqrt[3]{n} + T \log n \sqrt[7]n )$。



------------
然而上面的做法还不够优秀，我们考虑对每一个 $x$ 都进行二分，就可以将总复杂度降到 $\Theta(T \log^2 n)$。

**【代码】**

为了防止溢出等诸多问题，使用了 `__int128`。

$\Theta(\sqrt[3]{n} + T \log n \sqrt[7]n )$ 版本：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define iint __int128
long long nn,tt;
const iint M = 3e18+5;
map<long long,bool> mp[5];
iint n,t;
void work(){
    cin >> nn;n = (iint)nn;
    iint l = 2,r = 1e9,ans = -1;
    for(int i = 1;i <= 3;i ++) if(mp[i][n]) return cout << "YES\n",void();
    while(l <= r){
        iint mid = (l + r) / 2;
        if((mid * mid * mid - 1) / (mid - 1) < n) l = mid + 1;
        else if((mid * mid * mid - 1) / (mid - 1)  == n) {return cout << "YES\n",void();}
        else r = mid - 1;
    }
    for(iint i = 2;i <= 400;i ++){
        iint s = i*i,sum = 1 + i*i + i;
        for(iint j = 3;j <= 65;j ++){
            s *= i,sum += s;
            if(sum > n) break;
            if(sum == n) return cout << "YES\n",void();
        }
    }
    cout << "NO\n";
}
int main(){
    cin >> tt;t = tt;
    for(int i = 1;i <= 4;i ++){
        for(__int128 j = 2;j <= 1e5+2;j ++){
            __int128 k = 1;
            for(int m = 1;m <= i+3;m ++) k *= j;
            if((k-1)/(j-1) > M) break;
            mp[i][(int)((k-1)/(j-1))] = 1;
        }
    }
    while(t --) work();
    return 0;
}
```

$\Theta(T \log^2 n)$ 版本：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define iint __int128
long long nn,tt;
const iint M = 3e18+5;
map<long long,bool> mp[5];
iint n,t;
iint f(iint x,iint b){
    iint ans = 1;
    for(int i = 1;i <= b;i ++) ans *= x;
    return ans-1;
}
void work(){
    cin >> nn;n = (iint)nn;
    for(int i = 3;i <= 65;i ++){
        iint l = 2,r = pow(n,1/(double)(i-1))+5,ans = -1;
        while(l <= r){
            iint mid = (l + r) / 2;
            if(f(mid,i) / (mid - 1) < n) l = mid + 1;
            else if(f(mid,i) / (mid - 1)  == n) {return cout << "YES\n",void();}
            else r = mid - 1;
        }
    }
    cout << "NO\n";
}
int main(){
    cin >> tt;t = tt;
    while(t --) work();
    return 0;
}
```

---

## 作者：Qerucy (赞：0)

题意：给定 $n$，问是否能找出两个数 $m$ 和 $k$，使得 $\sum\limits_{i=0}^mk^i=n$，其中 $k\ge2$，$m\ge2$。

因为 $n\le10^{18}$，所以我们可以分类讨论。

我们先判断 $m\ge3$ 的情况，因为 $n\le10^{18}$，所以当 $m\ge3$ 时，$k$ 一定小于 $10^6$。此时我们预处理 $m\ge3$ 所有可行的方案即可。

时间复杂度：$\mathcal{O}(\sqrt[3]{n}\log\sqrt[3]{n})$

然后再判断 $m=2$ 的情况，当 $m=2$ 时，易得：

$$\sum\limits_{i=0}^mk^i=1+k+k^2$$

我们定义函数 $f(x)=1+x+x^2$，易得：当 $x\ge2$ 时，$f(x)$ 单调递增，因此我们可以二分判断 $m=2$ 的情况是否可行即可。

时间复杂度：$\mathcal{O}(T\log_2 {n})$

这里放一下我赛时写的代码：

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
#define int long long
 
map<int,int>mp;
 
int q;
int n;
 
int check(int x){
    return 1+x+x*x;
}
 
signed main(){
    int maxn=1e18;
	scanf("%lld",&q);
	for(int i=2;i<=1000000;i++){
	    int sum=1+i+i*i,beg=i*i;
	    mp[sum]=1;
	    for(int j=3;;j++){
	        if(beg>maxn/i) break;
	        beg*=i;
	        if(sum>maxn-beg) break;
	        sum+=beg;
	        mp[sum]=1;
	    }
	}
    while(q--){
        scanf("%lld",&n);
        if(mp[n]){
            puts("YES");
            continue;
        }
        
        else if(n<4){
            puts("NO");
            continue;
        }
        
        int l=2,r=1e9;
        while(l<r){
            int mid=(l+r)/2;
            if(check(mid)<n) l=mid+1;
            else r=mid;
        }
        if(check(l)!=n) puts("NO");
        else puts("YES");
    }
	return 0;
}
```


---

