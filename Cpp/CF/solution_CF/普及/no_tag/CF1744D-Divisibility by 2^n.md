# Divisibility by 2^n

## 题目描述

你被给予一个正整数数列 $ a_1, a_2, \ldots, a_n $ .

你需要让数列中所有数字的乘积 (也就是 $ a_1 \cdot a_2 \cdot \ldots \cdot a_n $ ) 能被 $ 2^n $ 整除.

你可以进行下列操作任意次:

- 选择一个正整数 $ i $ ( $ 1 \leq i \leq n $ ) 然后把 $ a_i $ 替换为 $ a_i=a_i \cdot i $ .

你不能重复地对同一个 $ i $ 进行操作. 换句话说, 你选择的所有的 $ i $ 都必须不同.

你要找到让数列中所有数字的乘积能被 $ 2^n $ 整除的最少操作. 注意方案不一定存在.

## 说明/提示

在第一个测试数据中, 数列中所有数字的乘积已经为 $ 2 $ , 因此不需要操作.

在第二个测试数据中, 数列中所有数字的乘积为 $ 6 $ . 我们可以对 $ i = 2 $ 进行操作, 于是 $ a_2 $ 变为 $ 2\cdot2=4 $ , 然后数列中所有数字的乘积为 $ 3\cdot4=12 $ , 这个数字能被 $ 2^n=2^2=4 $ 整除.

在第四个测试数据中, 就算我们执行所有可能的操作, 我们还是无法让数列中所有数字的乘积能被 $ 2^n $ 整除 — 结果为 $ (13\cdot1)\cdot(17\cdot2)\cdot(1\cdot3)\cdot(1\cdot4)=5304 $ , 不能被 $ 2^n=2^4=16 $ 整除.

在第五个测试数据中, 我们可以对 $ i = 2 $ 和 $ i = 4 $ 进行操作.

## 样例 #1

### 输入

```
6
1
2
2
3 2
3
10 6 11
4
13 17 1 1
5
1 1 12 1 1
6
20 7 14 18 3 5```

### 输出

```
0
1
1
-1
2
1```

# 题解

## 作者：蒟蒻且菜鸡 (赞：4)

首先我们先算出在不需要任何操作的帮助下的时候，序列中所有数字的积能够满足2的数量，这里的时间复杂度是 $O(n)$ 的。

如果现在数字的积已经达到了要求及数量大于等于 $n$，输出 $0$；

如果没有达到要求，就枚举每个下标能的 $2$ 的数量，然后从大到小进行排序，进行枚举，直到数量大于等于 $n$ 为止。

```
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof(a));
		int n;
		cin>>n;
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			while(x%2==0)
			{
				x/=2;
				cnt++;
			}
			x=i;
			while(x%2==0)
			{
				a[x]++;
				x/=2;
			}
		}
		if(cnt>=n)
		{
			cout<<0<<endl;
			continue;
		}
		sort(a+1,a+n+1);
		int ans=-1;
		int sum=0;
		for(int i=n;i>=1;i--)
		{
			if(a[i])
			{
				cnt+=a[i];
				sum++;
			}
			if(cnt>=n)
			{
				ans=sum;
				break;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：ycy1124 (赞：3)

## 题意
有一段数列，将它的所有数乘起来之后，再乘上一些数的下标，使它能整除 $2^n$ 。求**最少**需要乘上多少个数的下标。
## 分析 + 思路
首先不难发现这是一道贪心题，具体的贪心思路也很好想，只需要先将原数列所有数的乘积有多少个 2 的质因子，然后求出每个下标乘上后能增加多少个 2 的质因子，从大到小排序后每次取**能增加最多的 2 的质因子**的下标乘起来，直到满足要求。
## 注意事项
1.**没有**方法时要输出 $-1$ 。

2.每个下标**最多乘一次**。

3.循环时边界要注意。

4.有 $t$ 组数据。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int b[200001];
int work(int x){//求有多少个2的质因子。
	int js=0;
	while(x%2==0){
		++js;
		x/=2;
	} 
	return js;
}
bool cmp(int x,int y){//自定义排序。
	return x>y;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t){
		t--;
		int n,js=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			js+=work(x);//记录原有的质因子。
			b[i]=work(i);//求每个下标有多少2的质因子。
		}
		sort(b+1,b+n+1,cmp);
		int i=0;
		while(js<n&&i<=n){//循环直至满足要求或超出边界。
			++i;
			js+=b[i];
		}
		if(i>n){//判断是否有方案。
			printf("-1\n");
			continue;
		}
		printf("%d\n",i);//输出答案。
	}
	return 0;
}
``````
[AC 记录](https://www.luogu.com.cn/record/168919726)。

最后复杂度 $\mathcal{O}(t n\log n)$ 两秒足够了。

---

## 作者：M_CI (赞：3)

### 思路

首先，我们定义一个正整数 $n$ 含有质因子 $p$ 的个数为 $v_p(n)$，则题目即求最少的进行 $a_i=a_i\times i$ 操作的次数，使得

$$
\sum\limits_{i=1}^{n}v_{\tiny 2}(a_i) \geq n
$$

且对于每个 $i$ 所对应的 $a_i$ 至多执行一次操作。

所以我们先令原序列对应的上式值为 $sum$。

若 $sum \geq n$，则不用执行操作，输出 $0$。

否则将 $v_{\tiny 2}(i)$ 的值存入一个 $b$ 数组并从大到小排序，依次加进 $sum$ 直到 $sum \geq n$ 为止，输出答案。

若无论如何无法让 $sum \geq n$ ，输出 $-1$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,c[200010];

int main () {
	cin>> t;
	while (t--) {
		cin>> n;
		memset (c,0,sizeof (c));
		int tot=0;
		for (int i=1,a;i<=n;i++) {
			cin>> a;
			while (a%2==0) {
				tot++;
				a/=2;
			}
		}
		if (tot>=n) {
			puts ("0");
			continue;
		}
		for (int i=1;i<=n;i++) {
			int a=i;
			while (a%2==0) {
				c[i]++;
				a/=2;
			}
		}
		sort (c+1,c+n+1);
		int ans=0;
		bool f=0;
		for (int i=n;i>=1;i--) {
			tot+=c[i];
			ans++;
			if (tot>=n) {
				cout<< ans<< "\n";
				f=1;
				break;
			}
		}
		if (!f) puts ("-1");
	}
	return 0;
}
```

---

## 作者：Alice2012 (赞：2)

## Solution

首先，若输入的 $a_i$ 含有因子 $2$ 的总个数已经大于等于 $n$，直接输出 $0$。

否则，考虑怎样用最少个数的 $i$ 使得其贡献的 $2$ 的因子的数目尽量大。

显然，要选肯定先选含 $2$ 的因子尽量多的 $i$。将 $1$ 至 $n$ 的所有 $i$ 所包含的 $2$ 的因子数目全部处理出来，记为 $p_i$。将 $p_i$ 从大到小进行选择，总的因子数目不断加上当前的 $p_i$。什么时候总数目大于等于 $n$ 了，就输出已经选的 $p_i$ 的个数。

若将所有 $p_i$ 都选完都凑不齐 $n$ 个 $2$，输出 `-1`。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int T,n;
int p[N];
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		int cnt=0;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			while(x%2==0)
				x/=2,cnt++;
		}
		if(cnt>=n){//已经合法 
			cout<<"0\n";
			continue;
		}
		for(int i=1;i<=n;i++)//处理p[i] 
			p[i]=0;
		for(int i=1;i<=n;i++){
			int tmp=i;
			while(tmp%2==0)
				tmp/=2,p[i]++;
		}
		sort(p+1,p+n+1);
		int res=0,flg=0;
		for(int i=n;i>=1;i--){//选择 
			cnt+=p[i];
			res++;
			if(cnt>=n){
				flg=1;
				break;
			}
		}
		if(flg)
			cout<<res<<"\n";
		else
			cout<<"-1\n";
	}
	return 0;
}
```

---

## 作者：songzhixin (赞：2)

### 思路

根据贪心可知，你选 $i$ 肯定要选含 `2` 多的，所以可以先预处理把所有 $i$ 含的 `2` 算出来，再在输入时记录已经有几个 `2` 了，还差几个 `2`。

如果差的比所有 $i$ 含有的还多，输出 `-1`。

如果不差任何，输出 `0`。

否则从含 `2` 最多的数含 `2` 的数量开始 DFS，将数量一个一个往下减，直到够了为止。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=2*1e5+5;
long long a[N],f[N],b[N];
long long get_2(long long x){
	long long cnt=0;
	while(x%2==0){
		cnt++;
		x/=2;
	}
	return cnt;
}
long long ans=0;
long long p(long long x,long long y){
	long long ans=1;
	while(y){
		if(y&1){
			ans*=x;
		}
		x*=x;
		y>>=1;
	}
	return ans;
}
long long dfs(long long x,long long k,long long y,long long sum){
	long long c=p(2,k);
	long long d=y/c-sum;
	d*=k;
	if(x+d<y){
		long long e=d/k;
		return dfs(x+d,k-1,y,sum+e);
	}
	long long e=y-x;
	d/=k;
	long long g=e/k;
	if(g*k<e){
		g++;
	}
	return sum+g;
}
int main(){
	long long t;
	scanf("%lld",&t);
	for(long long i=1;i<=N-4;i++){
		f[i]=get_2(i);
		b[i]=b[i-1]+f[i];
	}
	while(t--){
		long long n;
		scanf("%lld",&n);
		long long sum=0;
		for(long long i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			sum+=get_2(a[i]);
		}
		if(sum>=n){
			printf("0\n");
			continue;
		}
		if(sum+b[n]<n){
			printf("-1\n");
			continue;
		}
		ans=0;
		long long k=log2(n);
		printf("%lld\n",dfs(sum,k,n,0));
	}
	return 0;
}
```

### 总结与反思

我们的 DFS 函数里面写的是 `long long d=y/c;`，因为都包含 $c$，所以这样就会把之前已经讨论过的数又加上一遍，应该写作 `long long d=y/c-sum;`。

---

## 作者：Allanljx (赞：2)

## 思路
先算出初始序列的积是 $2$ 的多少次方（对于每个数能除 $2$ 就除 $2$，直到除不了为止），如果 $2$ 的个数已经够了就输出 $0$。然后处理出每个下标 $i$ 能提供多少个 $2$（和对序列的处理一样），从大到小排序，直到选够 $n$ 个为止。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q;
int a[200005];
int b[200005];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) b[i]=0;
		int now=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			int d=a[i];
			while(d)//初始序列能除多少个2
			{
				if(d%2==0) now++;
				else break;
				d/=2;
			}
			d=i;
			while(d)//每个下标i能除多少个2
			{
				if(d%2==0) b[i]++;
				else break;
				d/=2;
			}
		}
		sort(b+1,b+n+1,greater<int>());
		if(now>=n) cout<<0<<endl;//已经够了
		else
		{
			for(int i=1;i<=n;i++)
			{
				now+=b[i];
				if(now>=n)//选够了
				{
					cout<<i<<endl;
					break;
				}
			}
			if(now<n)
			{
				cout<<"-1\n";
			}
		}
	}
}
```

---

## 作者：joyslog (赞：1)

## Divisibility by 2^n

[CF1744D](http://codeforces.com/problemset/problem/1744/D)

给定正数数列 $a_1\dots a_n$，你需要用最少次操作，使得 $2^n \mid \prod\limits_{i=1}^n a_i$。

在一次操作中，你可以选择一个 $i(1\le i\le n)$，让 $a_i$ 变为 $a_i\times i$。不能重复选取相同的 $i$。

求出最少的操作次数。

### 题解

记 $x$ 能贡献的因子 $2$ 的个数为 $\operatorname{count}(x)$。

若 $cnt=\sum\limits_{i=1}^n \operatorname{count}(a_i) \ge n$，则不用操作。

否则，我们发现每次乘法操作实际上只会贡献 $\operatorname{count}(i)$ 个 $2$，所以我们按 $\operatorname{count}(i)$ 的大小从大到小排序，贪心地加到原来的 $cnt$ 上，直到 $cnt\ge n$。

参考代码（省略快读快写）：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX_N = 2e5 + 10;
int f[MAX_N];
inline ll read() {...}
inline void write(ll x) {...}
inline int count(int x) {
    int ret = 0;
    while(!(x & 1)) x >>= 1, ret++;
    return ret;
}
int solve(int cnt, int n) {
    if(cnt >= n)    return 0;
    int ret = 0;
    for(int i = 1; i <= n; i++) f[i] = count(i);
    sort(f + 1, f + n + 1, greater<int>());
    for(int i = 1; i <= n; i++) {
        cnt += f[i];
        ret++;
        if(cnt >= n)    return ret;
    }
    return -1;
}

int main() {
    int t = read();
    while(t--) {
        int n = read(), cnt = 0;
        bool flag = 1;
        for(int i = 1; i <= n; i++) {
            int x = read();
            cnt += count(x);
        }
        write(solve(cnt, n)), putchar('\n');
    }
    return 0;
}
```

---

## 作者：__AFO__ (赞：0)

# 题解

一道数学题，其实只需要看总共有多少 $2$ 的个数，每次操作里 $i$ 有多少个 $2$ 即可，也就是看每个数最多能除几个 $2$。所以我们要先写一个函数来判断。

```cpp
long long pd(long long x) {
	y=0;
	while(1) {
		if(x%2==0){
		y++;
		x/=2;	
		}else{
			break;
		}
	}
	return y;
}
```
如果 $2$ 的个数够了，就可以直接输出，否则枚举在 $n$ 以内以能除多少个 $2$ 来排序一次寻找即可。

完整的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200005],t,n,k,f[200005],g,y;
long long pd(long long x) {
	y=0;
	while(1) {
		if(x%2==0){
		y++;
		x/=2;	
		}else{
			break;
		}
	}
	return y;
}
int main() {
	scanf("%lld",&t);
	while(t--) {
		k=0;
		g=0;
		scanf("%lld",&n);
		for(long long i=1; i<=n; i++) {
			scanf("%lld",&a[i]);
			k+=pd(a[i]);
		//	cout<<k<<" ";
			f[i]=pd(i);
		}
		//cout<<endl;
		if(k>=n) {
			printf("0\n");
		} else {
			sort(f+1,f+1+n);
			for(long long i=n; i>=1; i--) {
				g++;
				k+=f[i];
				if(k>=n) {
					break;
				}
			}
			if(k>=n){
				printf("%lld\n",g);
			}else{
				printf("-1\n");
			}
		}
	}
	return 0;
}
```

完结撒花

---

## 作者：ny_Dacong (赞：0)

# 思路

既然所有数相乘，要满足能被 $2^n$ 整除，那么我们可以先统计原来的数中有多少个 $2$，然后看看能不能通过操作把没有的 $2$ 补齐即可。

具体的实现方法：可以统计在每个数位上进行操作可以增加 $2$ 的几次方。然后贪心，优先加大数。最后统计答案即可。

记得判无解。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n = 0,tot = 0,ans = 0,tp,Max = 0,sum = 0;
long long num[200010],pos[32];
long long get2(long long x){
	long long res = 0;
	while(x%2 == 0){
		x /= 2;
		res++;
	}
	return res;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		tot = 0,ans = 0,Max = 0,sum = 0;
		memset(num,0,n*4+20);
		memset(pos,0,sizeof(pos));
		scanf("%lld",&n);
		for(long long i = 1; i <= n; i++){
			scanf("%lld",&num[i]);
			while(num[i]%2 == 0){
				num[i] /= 2;
				tot++;
			}
			tp = get2(i);
			pos[tp]++,Max = max(Max,tp);
			sum += tp;
		}
		tot = n-tot;
		if(sum < tot){
			printf("-1\n");
			continue;
		}
		for(long long i = Max; i >= 1; i--){
			for(long long j = 1; j <= pos[i]; j++){
				if(tot < i){
					break;
				}
				tot -= i;
				ans++;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Addicted_Game (赞：0)

## [Divisibility by 2^n](https://www.luogu.com.cn/problem/CF1744D)

### 题目大意
给出一个长为 $n$ 的数组 $a$，你可以对 $a_i$ 进行一次操作使得 $a_i$ 变成 $a_i \times i$，每个数仅能操作一次。问最少多少次操作可以使 $a$ 中所有数的乘积可以整除 $2^n$。

### 思路
能整除 $2^n$ 即因子包含 $n$ 个 $2$。而唯一可以增加因子的方式就是进行一次操作，每次操作能增加因子 $i$，而 $i$ 要尽可能包含多个 $2$。所以每次操作的数下标为 $k2^x$，其中 $k$ 和 $x$ 是正整数，$x$ 尽可能大。统计操作后因子 $2$ 的个数有没有达到 $n$。

但是这样可能会产生一个数反复进行操作，所以说每次操作前都要判断 $k2^x$ 能不能被 $2^{x+1}$ 整除（也就是 $k$ 包不包含因子 $2$），若可以就一定在处理 $k2^{x+1}$ 中就已经被处理过了，不用再次计算。

---

## 作者：Z_AuTwT (赞：0)

## 思路

因为 $2^n$ 可以被分解为 $n$ 个 $2$ 相乘的结果，所以题目就变成了在序列中找出 $n$ 个 $2$ 相乘。

先扫一遍整个序列，将所有的 $2$ 分解出来，再去扫下标（$2$ 的倍数）。

但这样没法过掉，我们可以想到，在扫下标的时候应该先扫含更多 $2$ 的下标。

## CODE

```c++
#include<bits/stdc++.h>
using namespace std;
int C[200010];
bool cmp(int a,int b){
	return a>b;
}
main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int cnt=0;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			while(x%2==0){//逐一分解
				x/=2;
				cnt++;
			}
		}
		if(cnt>=n){
			puts("0");
			continue;
		}
		bool flag=false;
		int Cnt=0,v=0;
		for(int i=n/2*2;i>=1;i-=2){//寻找下标
			int dt=i;
			while(dt%2==0){
				dt/=2;
				Cnt++;
			}
			C[++v]=Cnt;
			Cnt=0;
		}
		sort(C+1,C+v+1,cmp);
		for(int i=1;i<=v;i++){
			cnt+=C[i];
			Cnt++;
			if(cnt>=n){
				cout<<Cnt<<"\n";
				flag=true;
				break;
			}
		}
		if(!flag) puts("-1");
	}
}
```

---

## 作者：minVan (赞：0)

**解题思路**

首先我们暴力算出所有 $a_i$ 所包含的 $2$ 的个数 $s$，若 $s\ge n$，输出 $0$ 并退出。

接着我们令 $b_i$ 表示 $i$ 所包含的个数，然后把 $b_1\sim b_n$ 从大到小排序。再从前往后枚举，直到总个数大于等于 $n$。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, a[N];
inline bool cmp(int x, int y) {
  return x > y;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    memset(a, 0, sizeof(a));
    int s = 0;
    cin >> n;
    for(int i = 1, x; i <= n; i++) {
      cin >> x;
      while(x % 2 == 0) { x >>= 1, ++s; }
      int tmp = i;
      while(tmp % 2 == 0) {
        tmp >>= 1;
        ++a[i];
      }
    }
    if(s >= n) { cout << "0\n"; continue; }
    s = n - s;
    sort(a + 1, a + n + 1, cmp);
    int ans = 0, i = 1;
    while(s > 0 && i <= n) {
      ++ans;
      s -= a[i++];
    }
    if(s > 0) { cout << "-1\n"; }
    else { cout << ans << '\n'; }
  }
  return 0;
}

```

---

## 作者：haokee (赞：0)

首先，看到 $1\le a_i\le 10^9$，我们暴力出奇迹的念头就已经消失了。但是我们能够发现，让乘积为 $2^n$ 的倍数就等同于所有数当中 $2$ 的因子的数量需要大于等于 $n$，而一个数 $2$ 的因子的数量很容易计算，因此我们就能很轻易地判断不执行任何操作能否满足条件。

然后就是贪心地去操作了。要想让在尽可能少的操作数量下 $2$ 的因子的数量尽可能的多，那么乘上的 $i$ 的 $2$ 的因子数量也要尽可能的多，因此我们只需要预处理出 $1\sim n$ 所有数的因子数量，然后从大到小排一个序，最后再贪心地选择即可。

```kotlin
import java.util.*

val cin = Scanner(System.`in`)

fun main() {
  for (t in 1..cin.nextInt()) {  // t 组数据
    val n = cin.nextInt()        // 元素数量
    var cnt = 0                  // 记录因子数量
    var ans = 0                  // 记录答案
    val a = IntArray(n + 1)      // 1—n 的因子数
    for (i in 1..n) {
      var x = cin.nextInt()
      while (x % 2 == 0) {       // 如果还有 2 的因子
        cnt++                    // 记录数量
        x /= 2                   // 去掉
      }
    }
    for (i in 1..n) {            // 预处理 1—n 的因子数
      var x = i
      while (x % 2 == 0) {       // 如果还有 2 的因子
        a[i - 1]++               // 记录数量
        x /= 2                   // 去掉
      }
    }
    a.sortDescending()           // 从大到小排序
    for (i in 0..<n) {           // 遍历前 n 个元素
      if (cnt >= n) {            // 已经满足要求
        break                    // 跳出循环
      }
      cnt += a[i]                // 计数器累加
      ans++                      // 记录答案
    }
    println(if (cnt >= n) ans else -1)
  }
}
```

---

## 作者：weihaozhen2010 (赞：0)

****思路：****

- 排序的思想
- 先计算原数组 $2$ 的个数，如果已经大于等于 $n$ 了，直接输出 $0$。
- 如果小于 $n$，再计算每一位下标 $2$ 的个数，存在一个数组里。
- 接着，排序这个数组，从 $2$ 最多的下标开始补。
- 如果大于等于 $n$ 了。则跳出并输出次数。
- 否则计数器加一。

****参考代码：****
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,a[200005],f[200005];
int main()
{
	cin>>t;
	while(t--)
	{
		int n,sum=0,ans=-1,p=0;
		cin>>n;
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			while(a[i]%2==0)
			{
				a[i]/=2;
				sum++;
			}
		}
		for(int i=1;i<=n;i++)
		{
			int s=i;
			while(s%2==0)
			{
				f[s]++; 
				s/=2;
			}
		}
		if(sum>=n) 
		{
			cout<<"0"<<endl;
		}
		else
		{
			sort(f+1,f+n+1);
			for(int i=n;i>=1;i--)
			{
				if(sum>=n)
				{
					ans=p;
					break;
				}
				sum+=f[i];
				p++;
			}
			cout<<ans<<endl;
		}
	}
	return 0;
} 
```

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**排序，枚举**的思路：

- 先记录每个数里有多少个 $2$，再看是否符合要求。

- 符合的话直接输出 $0$，然后继续。

- 否则，记录下标里有多少个 $2$，另开数组储存，从大到小排序，从前往后看，发现符合后，立马输出。

- 如果全找完了，还不符合，输出 $-1$。

## CODE

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
int t,n,a[N],id[N],sum,ans;
inline int twos(int a)
{
	int cnt=0;
	while(a%2==0)
	{
		a/=2;
		cnt++;
	}
	return cnt;
}//找二的个数
inline bool cmp(int a,int b)
{
	return a>b;
}//从大到小排
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof(a));
		memset(id,0,sizeof(id));
		sum=0;
		ans=0;//清空!!!
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum+=twos(a[i]);//直接加
			id[i]=twos(i);//储存下标里的二
		}
		if(sum>=n)
		{
			cout<<"0\n";//直接符合
			continue;
		}
		sort(id+1,id+n+1,cmp);//排序
		for(int i=1;i<=n;i++)
		{
			sum+=id[i];//往上加
			ans++;//记录
			if(sum>=n)//符合了
			{
				cout<<ans<<"\n";//输出
				break;
			}
		}
		if(sum<n)
		{
			cout<<"-1\n";//不符合
		}
	}
	return 0; 
}
~~~

---

## 作者：renmoyi (赞：0)

## [CF1744D](https://www.luogu.com.cn/problem/CF1744D)题解：

- 本题实际上是在判断给出的正整数数列 $a_1, a_2, ······, a_n $ 的乘积的因子中含有多少个 $2$。肯定不能直接算出数再判断，那就判断初始序列的每一项中有多少个 $2$。如果 $2$ 的个数已经够了，那就输出 $0$，然后 `continue`，进入下一次测试。如果不够，就处理下标 $i$，看每个 $i$ 能提供多少个 $2$，存入数组 $b$，然后从大到小排一遍 $b$，让初始的 $2$ 的数量每次加 $b_i$，用 $ans$ 记录加的次数，并判断现在 $2$ 的数量够不够。如果够，输出 $ans$ 即可。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],b[200005]; 
int main()
{
	ios::sync_with_stdio(0);//细节优化 
	int t,n;
	cin>>t;
	while(t--)
	{
		int cnt=0,x;
		cin>>n;
		for(int i=1;i<=n;i++) b[i]=0;//每次访问要重置 
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++)//数初始序列2
		{
			while(a[i]%2==0)
			{
				a[i]/=2;
				cnt++;
			}
		}
		if(cnt>=n)//判断初始序列2的数量够不够
		{
			cout<<"    "<<0<<endl;
			continue;
		}
		for(int i=1;i<=n;i++)//如果不够，就判断下标2的数量
		{
			x=i;
			while(x%2==0)
			{
				b[x]++;//每个下标的2的数量存在数组b里
				x/=2;
			}
		}
		sort(b+1,b+n+1);//排序
		int ans=0;
		for(int i=n;i>=1;i--)//从大到小检查
		{
			if(b[i])//保证b[i]不是空的
			{
				cnt+=b[i];
				ans++;//记录次数
			}
			if(cnt>=n)//判断够不够
			{
				cout<<"    "<<ans<<endl;
				break;
			}
		}
		if(cnt<n) cout<<"    "<<"-1"<<endl;//如果出了for循环的cnt比n还小，说明不够，输出-1
	}
	return 0;
}
	
	
```


---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1744D)

duel bot.duel bot.duel bot.

让乘积是 $2^n\times k$，则必须凑出 $n$ 个因数 $2$。

首先看看原数组里 $a_i$ 分解质因数能拆出几个 $2$，不行的话再修改。对所有 $i$ 也提出 $2$，扔进一个数组从大到小排序，然后一个一个操作，达到 $n$ 个 $2$ 退出即可。

如果全部操作完还不能满足题意，报告无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,a[N],sum,res,b[N];
int split(int u){
    int ret=0;
    while(!(u&1))ret++,u>>=1;
    return ret;
}
int solve(){
    res=sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum+=split(a[i]);
    for(int i=n;i>=1;i--)b[i]=split(i);
    sort(b+1,b+n+1);
    for(int i=n;i>=1&&sum<n;i--)sum+=b[i],res++;
    if(sum<n)res=-1;
    return res;
}
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d",&T);
    while(T--)printf("%d\n",solve());
    system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/123627475)

---

## 作者：_HiKou_ (赞：0)

乍一看很简单但是还是有坑的...

[题面传送门](https://www.luogu.com.cn/problem/CF1744D)

乘积能被 $2^n$ 整除，也就是最后的 $a_i$ 中有 $n$ 个 $2$。 显然，只有当 $i$ 能被 $2$ 整除时才对答案有贡献。而且质因数有越多个 $2$ 的 $i$ 对答案的贡献更大。

我们可以先把原来序列中原本有的 $2$ 统计出来。如果够了输出 $0$，如果不够，因为含有 $2$ 越多的 $i$ 应该先用掉，所以我们统计所有的 $i$ 含有的 $2$ 的数量，然后排序优先取 $2$ 比较多的。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,n,a[214514],pla[214514];
ll pt(ll q){//含有多少 2
	ll cnt=0;
	while(q%2==0)cnt++,q/=2;
	return cnt;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		ll two=0,ans=0;
		scanf("%lld",&n);
		for(ll i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			two+=pt(a[i]);//统计初始序列 2 的个数
		}
		if(two>=n){
			printf("0\n");
			continue;
		}
		
		
		for(ll i=2;i<=n;i+=2)
			pla[i/2]=pt(i);//对答案有贡献的 i
			
		sort(pla+1,pla+1+n/2);
		
		for(ll i=n/2;i>=1;i--){
			two+=pla[i];
			ans++;
			if(two>=n)break;
		}
		
		if(two>=n)printf("%lld\n",ans);
		else printf("-1\n");
	}
	return 0;
} 
```

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1744D) & [CF 传送门](//codeforces.com/problemset/problem/1744/D)
# 思路
首先，我们可以看每个 $a_i$ 中有多少个 $2$（最多能被几个 $2$ 整除），并添加到 $sum$ 里。如果 $sum\ge n$，那就不需要操作，直接输出 $0$。否则，我们就要对每个 $i$ 也进行拆分，我们设 $i$ 中有 $x$ 个 $2$，那我们就可以对 $tot_x+1$（$tot_i$ 表示有 $i$ 个 $2$ 的数的个数）。记录下来以后，我们肯定是 $2$ 多的先操作，直到满足要求为止。时间复杂度为 $n+\log n$，足以通过。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, x, sum, a[20], tot;
int f () {
	cin >> n;
	memset (a, 0, sizeof a); //多组数据要清空
	tot = sum = 0; //多组数据要清零
	for (int i = 1; i <= n; ++ i) {
		cin >> x;
		while (! (x & 1)) //拆 a[i]
			x >>= 1, ++ sum;
		x = i;
		while (! (x & 1)) 拆 i
			x >>= 1, ++ tot;
		++ a[tot];
		tot = 0;
	}
	if (sum >= n)
		return 0;
	for (int i = 19; i; -- i) { // 倒着枚举，2 多的先操作
		x = sum + a[i] * i;
		if (x >= n) //满足要求
			return tot + (n - sum + i - 1) / i;
		tot += a[i], sum = x;
	}
	return -1;
}
int main () {
	cin >> t;
	while (t --)
		cout << f () << '\n';
	return 0;
}
```

---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

把我卡了好久……

## 题面大意

给定整数序列 $S$ ，你可以选出一个操作集 $Q$，满足 $\forall q \in Q,q \in [1,n]$，然后将所有 $S_q$ 替换成 $qS_q$，求要使原序列能被 $2^n$ 整除所需的最少操作次数。

## 解题思路

只记录每个数 $2$ 的因子的出现次数即可。

同时，为了确保操作次数最少，我们肯定首选 $2$ 的次幂最多的数字进行乘法。

所以我们可以设计一个简单的 dp，定义 $f_i$ 为 $i$ 含有 $2$ 的因子的个数，我们不难得到 $f_i = \begin{cases}f_\frac{i}{2}+1 & (i = 2k,k \in N) \\ 0\end{cases}$。

最后将 $f$ 数组排序，从大往小减即可。

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>

typedef long long i64;
const i64 mod = 1, maxn = 200007;

i64 T, n, li[maxn], lg[maxn], res, p2, t2, solved, logg[maxn], op, rem;

int main()
{
    scanf("%lld", &T);

    while (T--)
    {
        scanf("%lld", &n);
        rem = n;
        op = 0;

        memset(logg, 0, sizeof logg);
        logg[2] = 1;
        for (int i = 3; i <= n; i++)
            if (!(i & 1))
                logg[i] = logg[i >> 1] + 1;
            else
                logg[i] = 0;

        for (int i = 0; i < n; i++)
            scanf("%lld", li + i);

        for (int i = 0; i < n; i++)
            while (!(li[i] & 1))
                li[i] >>= 1,
                    rem--;

        if (rem <= 0)
            printf("0\n");
        else
        {
            std::sort(logg, logg + n + 1);
            for (int i = n; i; i--)
            {
                rem -= logg[i];
                op++;
                if (rem <= 0)
                {
                    printf("%d\n", op);
                    break;
                }
            }

            if (rem > 0)
                printf("-1\n");
        }
    }
    return 0;
}
```


---

## 作者：zbk233 (赞：0)

## 解题思路

设 $x=a_1 \times a_2 \times \dots \times a_{n-1} \times a_n$。

要使得变化过的 $x$ 能整除 $2^n$，就要尽量增加因子 $2$ 的个数。

因为每次操作都是乘 $i$，所以要使得操作次数尽量少，就要 $i$ 因子 $2$ 的个数尽量多。

那么我们就可以预处理出 $[1,n]$ 中的数因子 $2$ 的个数，再进行一次从大到小排序，之后依次遍历即可。

---

## 作者：隐仞Mrsu (赞：0)

# 题意分析
给定一个 $n$ 长的数组 $a$， 输出最少操作几次，使得 ${\prod \limits_{i=1}^n{a_i}}$ 能被 $2^n$ 整除。

每次操作可以选定一个**未操作的**元素 $a_i$，使其数值变为 $a_i \times i$。

首先计算每个 $a_i$ 能提取出多少个因子 $2$，若一共提取出了 $m$ 个 ，且 $m \ge n$，则此时不用操作即可满足条件，输出最少操作次数为 $0$。

当共提取出的因子 $2$ 有 $m$ 个，且 $m < n$，则需要进行操作。

为了能够达到被 $2^n$ 整除的条件，我们需要通过最少次数的操作凑出尽量多的 $2$。而且每次操作时，$a_i$ 需要乘以其序号 $i$。因此我们对 $1$ 到 $n$ 进行排序，能提取越多 $2$ 的排在前面。

然后按照排好的顺序依次做题目的乘法操作，当操作处理后的乘积含有的因子 $2$ 数量大于 $n$，则输出答案。若所有序号都乘完了，但仍然无法达到条件，则输出 $-1$。

比如：当 $n=20$ 时，应该先乘 $16$，因为它能够提取出 $4$ 个因子 $2$，是该情况下得到最多的。而后是 $8$，再然后是 $4,12,20$，依次类推。

# 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e6+6;
LL _,n,a[N],w[N],b[N];
bool cmp(LL x,LL y){
	return x>y;
}
void work(){
	cin>>n;
	LL yz=0,res=0;
	for(LL i=1;i<=n;i++){
		cin>>a[i];
		b[i]=w[i];//用数组b存储每个序号能提取出因子2的个数
	}
	for(LL i=1;i<=n;i++){
    //统计数组a中每个元素能提取出多少个因子2
		LL t=a[i];
		while(t){
			if(t%2){
				break;
			}
			else{
				t/=2;
				yz++; 
			}
		}
	}
	sort(b+1,b+1+n,cmp);//能提取的因子2个数越多，就排在前面
	for(LL i=1;i<=n;i++){
		if(yz>=n){
			cout<<res<<'\n';
			return;
		}
		res++;
		yz+=b[i];
	}
	cout<<"-1\n";
}
int main(){
	ios::sync_with_stdio(false);
   //预处理
	for(LL i=1;i<=200000;i++){
		LL t=i,r=0;
		while(t){
			if(t%2){
				break;
			}
			else{
				t/=2;
				r++; 
			}
		}
		w[i]=r;
	} 
	cin>>_;
	while(_--){
		work();
	}
}
```


---

## 作者：XiaoQuQu (赞：0)

记 $\prod\limits_{i=1}^na_i=s$。显然，若想要 $s$ 能被 $2^n$ 整除，那么 $s$ 在二进制下的后 $n$ 位就必定是 $0$。

那么，设 $i$ 在二进制下有 $k$ 个 $0$，如果我们操作 $a_i$，相当于是在 $s$ 的后面补了 $k$ 个 $0$。也就是说，我们可以贪心的选取 $i$，使得在 $s$ 后面补的 $0$ 尽量多。

显然，对于每个 $i$，由于 $1\le i\le 2\times 10^5$，我们可以预处理出 $i$ 的末尾零的个数，记为 $t_i$，这个 $t$ 的递推关系式为 $t_i=t_{\left\lfloor \frac i2 \right\rfloor}+1$。接下来贪心的选取即可。

```cpp
// Problem: D. Divisibility by 2^n
// Contest: Codeforces - Codeforces Round  #828 (Div. 3)
// URL: https://codeforces.com/contest/1744/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

// #define endl '\n'
#define int long long
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

const int MAXN = 2e5 + 5;
int n, a[MAXN], ans[MAXN], q[MAXN], t, cnt;

void init() {
	ans[2] = 1;
	for (int i = 4; i <= MAXN; i += 2) {
		ans[i] = ans[i / 2] + 1;
	}
}

void work() {
	t = cnt = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
    	cin >> a[i];
    	cnt += __builtin_ctzll(a[i]); // __builtin_ctzll(a[i]): 求出 a[i] 末尾 0 的个数
    }
    // cout << "cnt = " << cnt << endl;
    for (int i = 1; i <= n; ++i) if (i % 2 == 0) q[++t] = ans[i];
    // cout << "t = " << q[1] << ' ' << q[2] << endl;
    sort(q + 1, q + 1 + t, greater<int>());
    if (cnt >= n) {
    	cout << 0 << endl;
    	return;
    }
    for (int i = 1; i <= t; ++i) {
    	cnt += q[i];
    	if (cnt >= n) {
    		cout << i << endl;
    		return;
    	}
    }
    cout << -1 << endl;
}

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    int T;
    cin >> T;
    while (T--) {
        work();
    }
    return 0;
}
```



---

## 作者：litachloveyou (赞：0)

让我们将 $S$ 定义成一个序列的乘积。

如果想让 $S \bmod 2^n=0$，那么 $S$ 在质因数分解之后，$2$ 的次数一定要大于等于 $n$，否则是没有办法整除的。因此，只需要判断 $S$ 在质因数分解之后 $2$ 的次数是几次。

因为每一个 $i$ 只能用一次，并且每一个元素都大于等于 $1$，那也就意味着，只需要判断当前 $i$ 能给 $2$ 的次数加多少次，每一次贪心的用加的最多的就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve()
{
	int n;
	scanf("%d", &n);
	int sum = 0;
	priority_queue<int, vector<int>, less<int>>q;
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		while (x % 2 == 0)
		{
			sum++;
			x = x / 2;
		}
		int p = i, cnt = 0;
		while (p % 2 == 0)
		{
			cnt++;
			p = p / 2;
		}
		q.push(cnt);
	}
	int ans = 0;
	while (!q.empty()&&sum < n)
	{
		int t = q.top();
		q.pop();
		ans++;
		sum += t;
	}
	if (sum < n)ans = -1;
	printf("%d\n", ans);
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：_Weslie_ (赞：0)

## [题目传送门。](https://www.luogu.com.cn/problem/CF1744D)

由于题目有了样例解释，所以直接上思路。

可以非常简单地用 ```get2``` 函数求出一个数所有因子中 $2$ 的数量：
```
int get2(int x) {
	int cnt=0;
	while(1) {
		if(x%2==1)break;
		x/=2;
		cnt++;
	}
	return cnt;
}
```
那么我们可以把 $1$ 到 $n$ 中所有数的所有因子中 $2$ 的数量存储在一个名字叫 ```two``` 的数组中。

同理，可以将每一个 $a_i$ 的所有因子中 $2$ 的数量存储在一个名字叫 ```two2``` 的数组中。

那么输入及存储 ```two```,```two2``` 的代码就是这样：
```
for(int i=1; i<=n; i++) {
	two[i]=get2(i);
	sum1+=two[i];
	cin>>a[i];
	two2[i]=get2(a[i]);
	sum2+=two2[i];
}
```

接着，如果总和还没有 $n$ 大，则一定不满足，输出 $-1$；

如果 ```two2``` 的总和已经 $\geq n$，则输出 $0$；
```
if(sum1+sum2<n) {
	cout<<-1<<endl;
} else if(sum2>=n) {
	cout<<0<<endl;
}
```
接着，对 ```two``` 数组排序；

然后遍历 ```two``` 数组，利用贪心找出最小次数，此题终。
```
sort(two+1,two+n+1,cmp);
sum3=n-sum2;
for(int i=1; i<=n; i++) {
	sum3-=two[i];
	if(sum3<=0) {
		cout<<i<<endl;
		break;
	}
}
```
全代码：
```
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[200001],two[200001],two2[200001],sum1,sum2,sum3,t;
int get2(int x) {
	int cnt=0;
	while(1) {
		if(x%2==1)break;
		x/=2;
		cnt++;
	}
	return cnt;
}
int cmp(int a,int b) {
	return a>b;
}
int main() {
	cin>>t;
	while(t--) {
		cin>>n;
		sum1=0;
		sum2=0;
		for(int i=1; i<=n; i++) {
			two[i]=get2(i);
			sum1+=two[i];
			cin>>a[i];
			two2[i]=get2(a[i]);
			sum2+=two2[i];
		}
		if(sum1+sum2<n) {
			cout<<-1<<endl;
		} else if(sum2>=n) {
			cout<<0<<endl;
		} else {
			sort(two+1,two+n+1,cmp);
			sum3=n-sum2;
			for(int i=1; i<=n; i++) {
				sum3-=two[i];
				if(sum3<=0) {
					cout<<i<<endl;
					break;
				}
			}
		}

	}
	return 0;
}
```

---

