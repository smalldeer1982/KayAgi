# [ABC169D] Div Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc169/tasks/abc169_d

正の整数 $ N $ が与えられます。 $ N $ に対して、以下の操作を繰り返し行うことを考えます。

- はじめに、以下の条件を全て満たす正の整数 $ z $ を選ぶ。
  - ある素数 $ p $ と正の整数 $ e $ を用いて、 $ z=p^e $ と表せる
  - $ N $ が $ z $ で割り切れる
  - 以前の操作で選んだどの整数とも異なる
- $ N $ を、$ N/z $ に置き換える

最大で何回操作を行うことができるか求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 10^{12} $

### Sample Explanation 1

例えば、次のように操作を行うことで、 $ 3 $ 回操作を行うことができます。 - $ z=2\ (=2^1) $ とする。( 操作後、 $ N=12 $ となる。) - $ z=3\ (=3^1) $ とする。( 操作後、 $ N=4 $ となる。 ) - $ z=4\ (=2^2) $ とする。( 操作後、 $ N=1 $ となる。 )

### Sample Explanation 2

一度も操作を行うことができません。

### Sample Explanation 3

例えば、次のように操作を行うことで、 $ 3 $ 回操作を行うことができます。 - $ z=2\ (=2^1) $ とする。( 操作後、 $ N=32 $ となる。) - $ z=4\ (=2^2) $ とする。( 操作後、 $ N=8 $ となる。 ) - $ z=8\ (=2^3) $ とする。( 操作後、 $ N=1 $ となる。 )

### Sample Explanation 4

例えば、次のように操作を行うことで、 $ 1 $ 回操作を行うことができます。 - $ z=1000000007\ (=1000000007^1) $ とする。( 操作後、 $ N=1 $ となる。 )

## 样例 #1

### 输入

```
24```

### 输出

```
3```

## 样例 #2

### 输入

```
1```

### 输出

```
0```

## 样例 #3

### 输入

```
64```

### 输出

```
3```

## 样例 #4

### 输入

```
1000000007```

### 输出

```
1```

## 样例 #5

### 输入

```
997764507000```

### 输出

```
7```

# 题解

## 作者：orpg (赞：5)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc169_d)
### 题意
题目给我们一个正整数 $n$，$ (1\ \leq\ n\ \leq\ 10^{12})$，再找一个数 $z$。要求 $z$ 表示为一个质数 $e$ 次方，同时每一个 $z$ 互不相同。然后让操作：$n/z$，次数尽可能多。
### 做法分析
看到 $10^{12}$ 我们想到根号级别的算法，所以我们考虑先把 $n$ 进行质因数分解。即：$n=p_1^{e_1} × p_2^{e_2} × ⋯ × p_n^{e_n}$。

由于每一个 $z$ 互不相同，所以对于 $p^{n}$。最贪心的情况就是：先除 $p^{1}$，再除 $p^{2}$，直到 $p^{m}$。使得：$1+2+3+⋯+m \le n$。
### 时间复杂度分析
外层的循环是，$i×i \le n$，也就是 $O( \sqrt n )$ 的复杂度，中间的 while 循环是一个常数，所以可以过。
### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int cnt=0;
main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(long long i=2;i*i<=n;i++){
        int tmp=0;
        if(n%i==0){
            while(n%i==0){
                n/=i;
                tmp++;
            }//筛质因数
            int sum=0,ad;
            for(int j=1;sum+j<=tmp;j++){
                ad=j;
                sum+=j;
            }//寻找最贪心的方案
            cnt+=ad;
        }
    }
    if(n!=1) cnt++;//如果有剩余，就是一个新的质数，所以要加一
    cout<<cnt;
    return 0;
}
```
新人题解，管理员求过~

---

## 作者：ran_qwq (赞：5)

因为要操作次数尽可能大，所以每次的 $z$ 要尽可能小。

把 $N$ 分解质因数，$N=a_1^{p_1}\times a_2^{p_2}\times\dots\times a_m^{p_m}$。又因为 $z=p^e$，$p$ 为质数，$e$ 为正整数，所以 $z$ 只能在一个 $a_i^{p_i}$ 里取。

对于每个 $a_i^{p_i}$ 分开计算，注意到还有一个要求：每次的 $z$ 互不相同。所以第一次取 $a_i$，第二次取 $a_i^2$，第三次取 $a_i^3$……如果不能取就停止。算出每个 $a_i^{p_i}$ 的操作次数求和即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,len,ans,pr[N],cnt[N];
int f(int x)
{
	int ret=0;
	while(x-ret>0) x-=ret+1,ret++;
	return ret;
}
void solve()
{
	n=read();
	for(int i=2;i*i<=n;i++)
		if(n%i==0)
		{
			pr[++len]=i;
			while(n%i==0) cnt[len]++,n/=i;
		}
	if(n!=1) pr[++len]=n,cnt[len]=1;
	for(int i=1;i<=len;i++) ans+=f(cnt[i]);
	write(ans,"");
}
signed main()
{
	int T=1;
	while(T--) solve();
}
```

---

## 作者：DDF_ (赞：3)

## 题面

给一个整数 $N(1 \leq N \leq 10^{12})$ 。

找一个整数 $z$ ，需要满足三个条件：$z$ 不重复、 $z \mid N$ 、 $z=p^{e}$ 。

进行操作：$N \leftarrow \frac {N}{z}$ 。

求进行操作次数最大值。

## 思路

根本思路：贪心。

题面中 $z= p^{e}$ 且 $z \mid N$ 我们就可以想到分解质因数。

我们知道分解 $N$ 的质因数可以得到 $N= p_{1}^{c_{1}} \times p_{2}^{c_{2}}\times \cdots \times p_{i}^{c_{i}} \times \cdots \times p_{m}^{c_{m}}$ ，其中数组 $p$ 中全为 $N$ 的质因数。

然后要想使答案最大化，我们可以对每个 $c_{i}$ 进行拆分。

按照贪心的策略，我们知道每一次选的都要尽可能小，所以我们将 $c_{i}$ 划分成 $\sum _{j=1}^{m} j$时，也就是将其分成一个首项为 $1$ ，公差为 $1$ 的等差数列相加，是最优的。

然后在分解质因数的同时处理一下答案，然后就可以 AC 。

别忘记处理大于 $\sqrt{n}$ 的可能有唯一一个质因数。

时间复杂度 $O(\sqrt{n})$ 。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
int main() {
    scanf("%lld",&n);
    for(long long i=2;i*i<=n;i++) {
        long long s=1,t=0;
        while(n%i==0) {
            n/=i,t++;
            if(t==s) ans++,s++,t=0;
        }
    }
    if(n>1) ans++;
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Inexistented (赞：3)

## 题目意思

给定一个正整数 $n$ ,你可以对它进行若干次操作。

对于每一次操作：选择一个正整数 $x$ ,满足$x=p 
^e$且 $x$ 与其它操作中的 $x$ 不一样。

其中 $e$ 为正整数 , $p$ 为质数 ,并将 $n$ 变为 $\frac{n}{x}$。

问最多操作的次数。

## 解析

首先对 $n$ 进行质因数分解：

$n=p_{1}^{e_1} \times p_{2}^{e_2} \times \dots \times p_{m}^{e_m}$

对于每一个$p_{i}^{e_i}$ ,可再次拆分为：

$p_{i}^{e_i}=p_{i}^{a_1} \times p_{i}^{a_2} \times \dots \times p_{i}^{ak_i}$

得到需要求出的答案：

$ans= \displaystyle \sum_{i=1}^m{k_i}$

最后考虑如何让每一个 $a_i$ 尽可能小时，$k_i$ 最大。

## 代码

```c
#include <bits/stdc++.h>
using namespace std;

int main()
{
	long long n,ans=0;
	
	int i;
	
	vector <long long> v;
	
	cin>>n;
	
	for(i=2;i<=n/i;i++)
	{
		long long cnt=0;
		
		if(n%i==0)
		{
			while(n%i==0)
			{
				n=n/i;
				
				cnt=cnt+1;
			} 
			
			v.push_back(cnt);
		}	
	}
	 
	if(n>1)
	{
		v.push_back(1);
	} 
	
	for(i=0;i<v.size();i++)
	{
		long long sum=0;
		
		int j=1;
   
        while(sum+j<=v[i])
        {
        	sum=sum+j;
        	
        	ans=ans+1;
        	
        	j=j+1;
		}
	}
	
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：违规用户名720023 (赞：1)

# [ABC169D] Div Game

## 题目描述

给定一个正整数 $N$。重复以下操作：

首先，任意选择一个满足以下所有条件的正整数 $z$：

* $z$ 是某个质数的 $k$ 次方。
* $z$ 整除 $N$；
* $z$ 与之前操作中选择的所有整数不同。

然后，将 $N$ 修改为 $N/z$ 。

求最多可以进行的操作次数。

## 算法分析与实现

题目已经说得很清楚了，需要每次选一个 $N$ 的因数，很自然的想到因数分解。分解后可以得到 $N = p_1^{e_1} \times p_2^{e_2} \times \cdots \times p_k^{a_k}$（$k$ 是 $N$ 的质因子个数）。

我们可以遍历每一个质因子，发现对于在 $N$ 内指数为 $a_i$ 的质因子 $p_i$ ，将其分解为 $p_i^1 \times p_i^2 \times \cdots \times p_i^{t}$ 总是更划算的，于是问题就转化为了对于每个质因子，求最大的 $t$ 使得 $t(t + 1) / 2 \le a_i$。于是可以写出如下代码：

```cpp
#include <iostream>
#define int long long
using namespace std;
int t_num[10] = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45};
int num[40];
signed main()
{
	int n;
	cin >> n;
	int c = 1;
	for(int i = 1; i <= 40; i++)
	{
		if (i == t_num[c + 1]) c++;
		num[i] = c;
	}
	int ans = 0;
	if(n == 1)
	{
		cout << 0;
		return 0;
	}
	for(int i = 2; i * i <= n; i++)
	{
		int cnt = 0;
		while(n % i == 0) cnt++, n /= i;
		ans += num[cnt];
	}
	if(n != 1) ans++;
	cout << ans;
	return 0;
}
```

---

## 作者：BJ_BSGF_Lyc (赞：1)

# AT_abc169_d [ABC169D] Div Game 题解
## 题目大意
给定一个正整数 $N$。重复以下操作：
首先，任意选择一个满足以下所有条件的正整数 $z$：
* $z$ 可以表示为 $z＝p^e$，其中 $p$ 是素数，$e$ 是正整数；
* $z$ 整除 $N$；
* $z$ 与之前操作中选择的所有整数不同。

然后，将 $N$ 修改为 $\displaystyle \frac{N}{z}$ 。

求最多可以进行的操作次数。
## 思路
如果我们想让操作次数尽可能最多，那么 $z$ 就得尽可能小，首先 $z$ 是 $N$ 的因数，所以 $p$ 必定是 $N$ 的质因数，那么我们来设 $N$ 第质因数中有 $x$ 个 $p$ ，则 $p$ 可以执行 $y$ 次操作，并且这里的 $y$ 满足 $\displaystyle \sum_{i=1}^{y}i\le x $。

很明显，我们只需要直接累加 $N$ 的每个质因数的个数，再 $-1,-2,-3,...$ 共能减几次答案就会累加几。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,cnt[100005],len;
int cntfunc(int num){
    int sum=0;
    while(num-sum>0) num-=sum+1,++sum; //根据题面写出函数
    return sum;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0); //IO 好习惯！
    cin>>n;
    for(int i=2;i*i<=n;++i){
        if(n%i==0){
            while(n%i==0) ++cnt[len],n/=i;
            ++len;
        }
    }
    if(n!=1) cnt[len++]=1;
    for(int i=0;i<len;++i)
        ans+=cntfunc(cnt[i]);
    cout<<ans<<endl; //AtC 题记得换行，养成好习惯
    return 0; //下课！
}
```

---

## 作者：Mierstan085 (赞：1)

CYEZ 模拟赛做的题目，刚好写下题解。

显然可以根据唯一分解，另第 $i$ 个 $n$ 的质因子为 $p_i$，满足 $p_i^{e_i}\mid n$，则 $n = \prod p_i^{e_i}$。

容易发现，假设可以将 $e_i$ 分拆成 $f(e_i)$ 个互不相同的正整数，则答案为 $\sum f(e_i)$。

发现到，可以计算 $\sum x \le e_i$ 中 $x$ 的极限，这时 $f(e_i) = i$。

于是容易写出代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;
signed main(){
	// freopen("divgame.in", "r", stdin);
	// freopen("divgame.out", "w", stdout);
	
	cin >> n;
	int ans = 0;
	for (int i = 2; i * i <= n; i ++){
		if (n % i != 0) continue;
		int cnt = 0;
		while (n % i == 0){
			cnt ++;
			n /= i;
		}
		int ab = 0, c = 0;
		for (int j = 1; ab + j <= cnt; j ++){
			c = j;
			ab += c;
		}
		ans += c;
	}
	if (n != 1) ans ++;
	cout << ans;
}
```

~~CYEZ 什么唐诗键盘。~~

---

## 作者：Code_Select_You (赞：1)

## 思路
这道题把 $n$ 分解质因数后 $n$ 就成了 $a^b \times c^d \times \cdots$ 的格式，每个质因数就成了 $z = p^e$ 的格式。题目让求最多操作几次，且 $z$ 与之前操作中选择的所有整数不同，所以对于一个质因数 $a^b$，每次操作的 $e$ 都是不同的，为了最优，每次取得 $e$ 都要尽可能的小，所以 $e$ 依次是 $1$，$2$，$3 \cdots$ 最后当所有所有取过的 $e$ 的和大于 $b$ 时就停止。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int ans;
int calc(int x){
	int sum=0;
	for(int i=1;i;i++){
		int tmp=0;
		while(!(n%x) && tmp<i){
			n/=x,tmp++;
		}
		if(tmp<i) return sum;
		else sum++;
	}
	return sum;
}
int main(){
	scanf("%lld",&n);
	for(long long i=2;i<=sqrt(n);++i){
		if(n%i==0) ans+=calc(i);
	}
	printf("%d",ans+(n==1 ? 0 : 1));
}
```


---

## 作者：WuMin4 (赞：0)

## [[ABC169D] Div Game](https://atcoder.jp/contests/abc169/tasks/abc169_d)

## 思路

对 $n$ 分解质因数后可以得到 $n=p_1^{c_1}\times p_2^{c_2}\times \cdots\times p_m^{c_m}$。因为每个 $z$ 要互不相同，所以考虑贪心地去除以 $p_i^1,p_i^2,\cdots,p_i^{x_i}$，则可以得到：

$$
1+2+\cdots+x_i\le c_i \\ 
\frac{x_i\times (x_i+1)}{2}\le c_i \\ 
1\le x_i\le \sqrt{2\times c_i+\frac{1}{4}}-\frac{1}{2}
$$

答案即为 $\sum_{i=1}^m\max{x_i}$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,mx,ans;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n,mx=sqrt(n);
	for(int i=2;i<=mx;i++)
		if(n%i==0){
			int cnt=0;
			while(n%i==0)
				n/=i,cnt++;
			ans+=floor(sqrt(2*cnt+0.25)-0.5);
		}
	if(n!=1)
		ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：ztrztr (赞：0)

看到题解里面好像没有用二分写的，我这个蒟蒻就写一个了。
## 题意
题目翻译写得很清楚了，我就不多写了。
## 思路
先把给定的 $N$ 分解质因数，得出：
$$
N = a_1^{p_1} \times a_2^{p_2} \times a_3^{p_3} \times \dots \times a_k^{p_k}
$$

我们分开算每一个 $a_i$，每一个的答案就是把 $p_i$ 分解成多个不同的正整数的个数的最大值，我们可以预处理出一个数组 $p$，定义 $p_i = (i - 1) \times i \div 2$，也就是前 $i$ 个正整数之和。

我们可以二分求出每一个 $p_i$ 的答案，注意不能用 `lower_bound` 减去 $1$，要用 `upper_bound` 再减去 $1$，因为用 `lower_bound` 的时候遇到 $x$ 刚好是 $p$ 中的一个数的时候会出现问题。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
/*
*/
#define int long long
long long N, a[1000005];
vector <int> p, e;
signed main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N;
        if (N == 1) {
        cout << 0;
        return 0;
    }
    for (int i = 1; i <= 64; i ++) a[i] = i * (i + 1) / 2;
    for (int i = 2; i * i <= N; i ++) {
        // if (N == 1) break;
        int cnt = 0;
        while (N % i == 0) {
            cnt ++;
            N /= i;
            // cout << cnt << " " << i << " " << N << "\n";
        }
        if (cnt != 0) p.push_back(i), e.push_back(cnt);
    }
    int ans = 0;
    if (N != 1) p.push_back(N), e.push_back(1);
    for (int i = 0; i < e.size(); i ++) {
        ans += upper_bound(a + 1, a + 64 + 1, e[i]) - a - 1;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：jnxx_zhuyueqi (赞：0)

本题的大致思路就是判断一个质数是否是 $N$ 的质因子，从一次幂开始试，如果是的话那就除掉，然后接着试这个质数的更高次幂是不是 $N$ 的因子，重复这一过程就好了，时间复杂度 $O( \sqrt N )$。

又及：附上手写的快读快写
```cpp
#include<bits/stdc++.h>
using namespace std;
#define getchar_unlocked() getchar()
#define int long long
int n,cnt,len,ans;
int scan(){
    int k=0,f=1;
    char c=getchar_unlocked();
    while(c<'0'||c>'9'){
        if(c=='-') f=-f;
        c=getchar_unlocked();
    }
    while(c>='0'&&c<='9'){
    	k=k*10+c-'0';
		c=getchar_unlocked();
	}
    return k*f;
}
void print(int x){
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x<10) putchar(x+'0');
    else{
    	print(x/10);
		putchar(x%10+'0');
	}
}
signed main(){
	//freopen("divgame.in","r",stdin);
	//freopen("divgame.out","w",stdout);
	n=scan();
	for(int i=2;i*i<=n;i++){
		cnt=0;
		if(n%i==0){
			while(n%i==0){
				n/=i,cnt++;
			}
			int sum=0,ad;
			for(int j=1;j+sum<=cnt;j++){
				ad=j,sum+=j;
			}
			ans+=ad;
		}
	}
	if(n!=1) ans++;
	print(ans);
	return 0;
}
```

---

## 作者：lukepanpyz (赞：0)

## 题目大意
给定一个数 $n$，求 $n$ 的只含一个除 $1$ 和自己以外的素因数的因数的个数。
## 解题思路
1. 对 $n$ 分解质因数，计算每个质因数的个数。
2. 对于每个质因数的个数，不断拆分出（连续）正整数，直到他们的和最逼近当前质因数个数为止。每拆分一次，累加一次。因为只有每个拆分出来的质因数个数不同，得到的每个因数也就不同。这里采用的是贪心策略。
3. 将累加的个数输出，当最后分解质因数结束的 $n$ 不为 $1$ 时，说明还剩一个素数未分，计数器加一再输出。
## AC code
```cpp
include <bits/stdc++.h>
using namespace std;
int main()
{
//	freopen("divgame.in","r",stdin);
//	freopen("divgame.out","w",stdout);
	long long n,sum = 0;
	cin >> n;
	long long tmpn = n;
  //分解质因数。
	for(long long i = 2;i * i <= tmpn;i++)
	{
		if(n % i == 0)
		{
			long long cnt = 0,j = 1,tmp = 0;
    //cnt 计算当前素因数个数。
			while(n % i == 0)
			{
				cnt++;
				n /= i;
			}
    //贪心累加。
			while(tmp + j <= cnt)
			{
				tmp += j;
				sum++;
				j++;
			}
		}
	}
	if(n != 1) //分完后 n 不为 1 ，说明还剩下一个素数未分，结果要加一。
	{
		cout << ++sum;
	}
	else
	{
		cout << sum;
	}
	return 0;
}
```

---

## 作者：wbxxxx (赞：0)

# 思路：
这是一道贪心题，由题意我们可以知道 $p$ 为 $n$ 质因数，所以我们可以先将 $n$ 进行质因数分解，因为对于每 $z$ 互不相同，可以对于 $p^{n}$ 从小到大依次除以，则我们可以得到一个等差数列，这样的结果是最优的，最后在质因数分解的过程中统计答案即可。

千万不要忘记判断当 $n\ne1$ 时，结果加 $1$。

**代码：**

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 100000009
using namespace std;
int read()
{
    int X=0,w=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-') w=-1;ch=getchar();}
    while(ch<='9' && ch>='0') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}//快读 
int a[10000009],b[100000009],f[10000009];
int n,m,i,j,k,sum,cnt,ans,s;
signed main()
{
	n=read();
    for(i=2;i<=sqrt(n);i++) 
	{
        sum=1,s=0;
        if (n%i==0){
        	while(n%i==0) {
                n/=i,s++;//筛查质因数 
                if(s==sum) {
            	   ans++;
				   sum++;
				   s=0;
			   }//判断能进行几次操作 
			  else continue;
            }
		}
    }
    if(n!=1) ans++;//当 n!=1,本身也是，所以答案加1 
    cout<<ans;
	return 0;
}
```

---

## 作者：xzz_0611 (赞：0)

[洛谷题目传送门](/problem/AT_abc169_d)  
[AtCoder 传送门](https://atcoder.jp/contests/abc169/tasks/abc169_d)
### 思路
想要让操作次数最多，$z$ 就要尽可能小。

由于 $z$ 是 $N$ 的因数，所以 $p$ 就是 $N$ 的质因数。

设 $N$ 的质因数中有 $x$ 个 $p$，则这个 $p$ 能执行 $y$ 此操作，并且 $y$ 满足 $\displaystyle\sum_{i=1}^y i\le x$。

所以我们只需要累加 $N$ 的每个质因数的个数，再依次减 $1$、减 $2$、减 $3$、……能减几次就将答案累加几。
### Code
```cpp
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
int n,ans,cnt[100000],len;
int Cnt(int num) {
	int sum=0;
	while(num-sum>0) num-=sum+1,++sum;//判断能减几次
	return sum;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=2;i*i<=n;++i)//累加质因数个数
		if(n%i==0) {
			while(n%i==0) ++cnt[len],n/=i;
			++len;
		}
	if(n!=1) cnt[len++]=1;//如果N不为1那么N本身也可以
	for(int i=0;i<len;++i) ans+=Cnt(cnt[i]);//累加答案
	cout<<ans;
	return 0;
}
```

---

## 作者：crzcqh (赞：0)

## 分解

根据题意，容易想到贪心策略，即对于每一个质因数，第 $i$ 次除 $p^i$，直到除不了，这样能使除的质因数数量最多。故  $n$ 可以表示成 $p_1^{(1)}\times p_1^{(2)} \times \dots p_1^{(k1)}\times p_2^{(1)}\times p_2^{(2)}\times \dots p_m^{(km)}$。简化一下就是 $p_1^{(\sum_{i=1}^{k1}i)}\times p_2^{(\sum_{i=1}^{k2}i)}\times \dots p_m^{(\sum_{i=1}^{km}i)}$。

## 解题

由于 $p$ 都是质数，所以我们可以先对 $n$ 分解质因数，然后对于每一个 $p_i^{k_i}$ 考虑求 $v$，使得 $v$ 最大，$\sum\limits_{i=1}^{v}\le k$。最后将所有 $v$ 加起来即是答案。

时间复杂度：$O(A\times\sqrt{n})$，$A$ 是个常数。

---

## 作者：ForgetOIDuck (赞：0)

### 思路
首先考虑分别处理每个质因数。

令 $N = \Pi_{i=1}^k p_i^{a_i}$（其中 $p_i$ 为质数，$a_i$为正整数）

则我们需要考虑如何将  $p_i^{a_i}$ 分解为几个数的乘积使得这几个数互不相同且数量最大化。

因为  $p_i^{a_i}$ 只能转化成 $p_i$ 的幂的乘积的形式，我们从对 $a_i$ 的分解入手。问题转化为将 $a_i$ 转化为几个互不相同的正整数的和的形式并且使数量最大。

不难发现选的数应尽量小，即 $1,2,3\cdots$ 这样的数。所以我们的选法就可以是求一个最大的 $c$ 使得 $1+2+\cdots+c\le a_i$。

数据范围： $1\le N\le 10^{12}$，分解质因数是 $O(\sqrt N)$ 的，对 $a_i$ 的划分可以暴力求，是 $O(\sqrt{\log N})$ 的（其实 $a_i$ 最大不超过 $40$，这东西基本就可以忽略不计），所以总时间复杂度应该是 $O(\sqrt N)$级别~~再加上划分那个相当于常数的复杂度~~。

### AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long ans, n, c, t, s;
int main() {
	cin >> n;
	for (long long i = 2; i * i <= n; i ++ ) {
		c = s = 0, t = 1;
		while (n % i == 0) n /= i, c ++;
		while (s + t <= c) s += t, t ++;
		ans += t - 1;
	}
	if (n - 1) ans ++;
	cout << ans << endl;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc169_d)。

## Solution

每次除以一个 $N$ 的因数，还要求是质数的正整数次方，显然可以想到将 $N$ 进行质因数分解。设 $N=\prod\limits_{i=1}^{k} p_i^{k_i}$。

我们贪心地取数，肯定是 $p_i,p_i^2,p_i^3$ 依次往上取。枚举 $i$ 后这样做即可。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=1e6+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,cnt,ans;
int tot[N],v[N];

bool check(int x){
	if(x<2) return 0;
	if(x==2 || x==3) return 1;
	if(x%2==0) return 0;
	for(int i=3;i*i<=x;i+=2){
		if(x%i==0) return 0;
	}
	return 1;
}

void init(int n){
	if(check(n)){
		v[++cnt]=n,tot[cnt]=1;	
		return;
	}
	
	for(int i=2;i*i<=n;++i){
		if(n%i==0){
			v[++cnt]=i;
			while(n%i==0) n/=i,++tot[cnt];
		}
	}
	if(n>1) v[++cnt]=n,tot[cnt]=1;
}

main(){
	n=wrd();
	if(n==1) return puts("0"),0;
	init(n);
	for(int i=1;i<=cnt;++i) for(int j=1;j<=tot[i];++j) ++ans,tot[i]-=j;
	return printf("%lld",ans),0;
}
```

---

## 作者：watcher_YBH (赞：0)

# 题目大意：
将 $n$ 分解成几个值不同的几个 $p^e$ 相乘，其中 $p$ 为质数，$e$ 为正整数，求 $n$ 最多可以分解成多少个 $p^e$ 相乘。
# 思路：
首先我们可以知道，两个不同的质数的任意正整数次方永远不会相同，所以问题就转变成了将 $n$ 分解成 $p_1^{e_1} \times p_2^{e_2} \times p_3^{e_3} \times … \times p_m^{e_m}$ 后（分解质因数），统计每一个 $e_i$ 最多可以分解成几个不同的数相加。

那么，该如何求每一个 $e_i$ 最多可以分解成几个不同的数相加呢？我们可以用抽屉原理来做，所以这个值就是 $1+2+3+…+(x-1)+x \le n$ 中 $x$ 的最大值。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX = 1e6+5;
int n,cnt;
int prm[MAX],fac[MAX];
signed main(){
	cin>>n;
	int x = n;
	for(int i = 2; i<=sqrt(x); i++){// 分解质因数
		if(!(x%i)) prm[++cnt] = i;
		while(!(x%i)) fac[i]++,x /= i;
	}
	int ans = 0;
	for(int i = 1; i<=cnt; i++){
		int z = 0;
		for(int j = 1; z<=fac[prm[i]]; z+=j,j++)// 用抽屉原理求每一个 $e_i$ 最多可以分解成几个不同的数相加，并统计答案
			if(z+j <= fac[prm[i]]) ans++;
	}
	cout<<ans+(x>1);// 如果x余下为质数，那么+1
	return 0;
}

```


---

