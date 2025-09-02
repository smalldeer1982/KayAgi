# Squaring

## 题目描述

ikrpprpp found an array $ a $ consisting of integers. He likes justice, so he wants to make $ a $ fair — that is, make it non-decreasing. To do that, he can perform an act of justice on an index $ 1 \le i \le n $ of the array, which will replace $ a_i $ with $ a_i ^ 2 $ (the element at position $ i $ with its square). For example, if $ a = [2,4,3,3,5,3] $ and ikrpprpp chooses to perform an act of justice on $ i = 4 $ , $ a $ becomes $ [2,4,3,9,5,3] $ .

What is the minimum number of acts of justice needed to make the array non-decreasing?

## 说明/提示

In the first test case, there's no need to perform acts of justice. The array is fair on its own!

In the third test case, it can be proven that the array cannot become non-decreasing.

In the fifth test case, ikrpprppp can perform an act of justice on index 3, then an act of justice on index 2, and finally yet another act of justice on index 3. After that, $ a $ will become $ [4, 9, 16] $ .

## 样例 #1

### 输入

```
7
3
1 2 3
2
3 2
3
3 1 5
4
1 1 2 3
3
4 3 2
9
16 2 4 2 256 2 4 2 8
11
10010 10009 10008 10007 10006 10005 10004 10003 10002 10001 10000```

### 输出

```
0
1
-1
0
3
15
55```

# 题解

## 作者：Special_Tony (赞：9)

# 前言&注意事项
不要相信 double 的精度，注意使用 ceil 时要提前减去一个 $eps$/tuu。
# 思路
首先若任意一个 $1$ 不是前导的（即出现 $a_i=1$ 但存在 $a_j>1(1\le j<i)$ 的情况），则无解。我们设最终，$a_i\to a_i^2$ 执行了 $k_i$ 次，若 $a_i\to a_i^{p_i}$，则 $p_i=2^{k_i},k_i=\lceil\log_2p_i\rceil$，因此我们只要知道 $p_i$ 就能得出 $k_i$。

让我们来推算一下 $k_i$：

$$
a_i^{p_i}=a_{i-1}^{p_{i-1}}\\
a_i^{(2^{k_i})}=a_{i-1}^{(2^{k_{i-1}})}\\
2^{k_i}=\log_{a_i}a_{i-1}^{(2^{k_{i-1}})}\\
2^{k_i}=2^{k_{i-1}}\log_{a_i}a_{i-1}\\
k_i=\log_2(2^{k_{i-1}}\log_{a_i}a_{i-1})\\
k_i=log_2(2^{k_{i-1}})+\log_2\log_{a_i}a_{i-1})\\
k_i=k_{i-1}+\log_2\frac{\lg a_{i-1}}{\lg a_i}
$$

注意要向上取整，若计算结果 $<0$ 则 $k_i=0$。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const double eps = 1e-9;
int t, n, x, lst, use;
bool flag;
ll sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> lst, sum = use = 0, flag = 0;
		for (int i = 1; i < n; ++ i) {
			cin >> x;
			if (lst != 1 && x == 1)
				flag = 1;
			if (flag || x == 1)
				continue ;
			use += max (-1.0 * use, ceil (log2 (log2 (lst) / log2 (x)) - eps));
			sum += use;
			lst = x;
		}
		cout << (flag ? -1 : sum) << '\n';
	}
	I AK IOI
}
```

---

## 作者：Fire_flame (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1995C)

## $\mathtt{Solution}$

提供一个不需要数学推导的方法。

首先很明显要从前往后推导，设 $f_i$ 表示位置 $i$ 的最少操作次数。

对于两个数 $a_i,a_{i+1}$，我们可以分以下类：

1. 如果 $\sqrt {a_{i}}<a_{i+1}< a_{i}$，显然，$f_{i+1}=f_i+1$。

- $\mathbf{Proof}$：因为 $\sqrt {a_{i}}<a_{i+1}<a_{i}$，所以 $a_i^{2^{f_i}}\div a_{i+1}^{2^{f_i+1}}=\dfrac{a_i^{2^{f_i}}}{a_{i+1}^{2^{f_i}}}\div a_{i+1}^{2^{f_i}}<1$。结论成立，证毕。

2. 如果 $\sqrt {a_{i}}>a_{i+1}$，那么你先操作几次 $a_{i+1}$，直到达到上面那种情况。

3. 还有 $\sqrt {a_{i+1}}<a_{i}< a_{i+1}$ 和 $\sqrt {a_{i+1}}>a_{i}$ 两种情况，这里不再赘述。

赛时代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5;
int t, n, flag, flag2, ans, a[MAXN], f[MAXN];
signed main(){
	t = read();
	while(t --){
		n = read(), ans = flag = flag2 = 0;
		for(int i = 1;i <= n;i ++)a[i] = read(), f[i] = 0;
		for(int i = 1;i <= n;i ++){
			if(a[i] > 1)flag2 = 1;
			if(a[i] == 1 && flag2){
				flag = 1;
				break;
			}
			if(i == 1){
				f[i] = 0;
				continue;
			}
			if(a[i] * a[i] <= a[i - 1]){
				int h = a[i];
				if(a[i] == 1){
					f[i] = 0;
					continue;
				}
				while(h * h < a[i - 1]){
					h *= h;
					f[i] ++;
				}
				if(h != a[i - 1])f[i] += f[i - 1] + 1;
				else f[i] += f[i - 1];
			}
			else if(a[i] < a[i - 1])f[i] = f[i - 1] + 1;
			else if(a[i] >= a[i - 1] * a[i - 1]){
				int h = a[i - 1];
				if(a[i - 1] == 1){
					f[i] = 0;
					continue;
				}
				while(h * h <= a[i]){
					h *= h;
					f[i] --;
				}
//				printf("%lld %lld %lld\n", i, f[i], f[i - 1]);
				f[i] += f[i - 1];
				f[i] = max(f[i], 0ll);
			}
			else f[i] = f[i - 1];
		}
		if(flag){
			puts("-1");
			continue;
		}
		for(int i = 1;i <= n;i ++)ans += f[i];
//		for(int i = 1;i <= n;i ++)printf("%lld\n", f[i]);
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：HasNoName (赞：4)

### 思路

由于每一次只能将一个数变为它的平方，所以一个数如果在很多次平方操作之后，第一次大于等于它前面的数时，还要再做它前面那个数做过的次数。

只有在一个数为 $1$ 且它前面的数大于 $1$ 的情况下才无解。

特别的，如果一个数大于等于它前面的数的 $k$ 次操作，则这个数就可以少操作 $k$ 次。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;
ll a[N],b[N];//10^6的平方要开long long。用b数组记录每个值至少要操作的次数
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T,n;
	cin>>T;
	while(T--)
	{
		cin>>n;
		ll ans=0;
		bool flag=1;//用flag记录是否无解
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]==1&&a[i-1]>1)flag=0;
		}
		if(!flag)
		{
			cout<<-1<<'\n';
			continue;
		}
		for(int i=2;i<=n;i++)
		{
			ll t=a[i],f=a[i-1];
			while(t<a[i-1])//由于每次平方，复杂度小于logn
			{
				t*=t;
				b[i]++;
			}
			while(f!=1&&f*f<=t)//要考虑到前面一项为1的情况
			{
				f*=f;
				b[i]--;
			}
			b[i]+=b[i-1];
			b[i]=max(b[i],0ll);//不能低于0次
			ans+=b[i];
		}
		cout<<ans<<'\n';
		memset(b,0,sizeof(b));
	}
	return 0;
}
```

---

## 作者：NEKO_Daze (赞：3)

[洛谷CF1995C](https://www.luogu.com.cn/problem/CF1995C) || [CodeForces 1995 C](https://codeforces.com/contest/1995/problem/C)

### 简要题意

给出一个由整数组成的数组 $a$， 对于每个索引 $1 \le i \le n$，可以将 $a_i$ 改为 $a_i^2$，求最少需要多少次才能让数组不递减。

### 思路

根据对数函数 $\log$ 的性质，我们知道 $\log(a_i^2)=\log(a_i\times a_i)=2\log(a_i)$，将对数运算优化为 $\times 2$。但由于浮点的精度，所以这样做仍然 MLE，怎么办呢？

~~再优化一遍不就得了。~~

因为有 $\log(2\times a_i)=\log(2)+log(a_i)$,所以每次操作只需要加上若干个 $\log(2)$ 即可，这样就无需担心浮点的精度了。

因此，我们定义第 $i$ 位所需的操作数为 $b_i$，初始化 $b_1=0$（毕竟如果把第一项扩大，那么其他项所需的操作数会相应变多），对于每个 $2\le i \le n$，$a_i$ 所需的操作数为 $b_i=\lceil \frac{b_i-b_{i-1}}{\log(2)}\rceil$，不过我们可以先预处理 $b_i=\log\log a_i$，这样又可以优化一些。最终时间复杂度为 $O(tn)$。

```cpp
//码风怪异，见谅
#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef long long       ll;
typedef long double     ld;
typedef pair<ll, ll>   pll; 
typedef pair<int, int> pii; 
const long long kk = 1000;
const long long ml = kk * kk;
const long long mod = ml * kk + 7;
const long long inf = ml * ml * ml + 7; 
const ld eps = 1e-9;  
int n;
vector<ld> v;
void solve() {
	cin >> n;
	v.resize(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	reverse(v.begin(), v.end());
	while (v.size() && v.back() == 1)
		v.pop_back();
	reverse(v.begin(), v.end());
	for (auto i : v)
		if (i == 1) {
			cout << "-1\n";
			return;
		}
 
	for (int i = 0; i < n; i++)
		v[i] = log(log(v[i]));
	ll ans = 0;
	for (int i = 1; i < v.size(); i++) {
		ld need = v[i - 1] - v[i];
		if (need > eps) {
			int cnt = 1 + (need - eps) / log(2);
			ans += cnt;
			v[i] += cnt * log(2);
		}
	}
	cout << ans << '\n';
}
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1; 
	cin >> t;
	while (t--) solve();
}
```

---

## 作者：doby (赞：3)

原题 [CF1883E Look Back](https://www.luogu.com.cn/problem/CF1883E)  
令相邻的前后两个数为 $a[i-1]$ 和 $a[i]$，第 $i$ 个数操作次数为 $f[i]$。  
只需要关注相邻两个数的大小情况，就可以根据 $a[i-1]$ 的操作次数递推出 $a[i]$ 的操作次数。  
$a[i-1]>a[i]$，此时 $a[i]$平方次数为 $cnt$，$f[i]=f[i-1]+cnt$。  
$a[i-1]<a[i]$，此时 $a[i]$开平方次数为 $cnt$，$f[i]=\max(f[i-1]-cnt,0)$。  
最后$ans=\sum_{i=1}^{n}f[i]$。  
注意特判 $a[i-1]=1$ 和 $a[i]=1$。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,cnt,out,fh,a[200010];
long long now,ok,ans,f[200010];
char cc;
int read()
{
	out=0,fh=1,cc=getchar();
	while(cc<48||cc>57){if(cc==45){fh=-1;}cc=getchar();}
	while(cc>=48&&cc<=57){out=(out<<3)+(out<<1)+(cc&15),cc=getchar();}
	return out*fh;
}
void Solve()
{
	n=read(),ok=1,ans=0;
	for(int i=1;i<=n;++i){a[i]=read();}
	for(int i=2;i<=n;++i)
	{
		now=a[i],cnt=0;
		if(now<a[i-1])
		{
			if(a[i]==1){ok=0;break;}
			while(now<a[i-1]){now=now*now,++cnt;}
		}
		else
		{
			while((a[i-1]==1&&sqrt(now)>a[i-1])||(a[i-1]!=1&&sqrt(now)>=a[i-1])){now=sqrt(now),--cnt;}
		}
		f[i]=f[i-1]+cnt;
		if(f[i]<0){f[i]=0;}
		ans+=f[i];
	}
	if(!ok){puts("-1");return;}
	printf("%lld\n",ans);
}
int main()
{
	T=read();
	while(T--){Solve();} 
	return 0;
}
```

---

## 作者：BrotherCall (赞：2)

## 题意转换

给定序列 $\{a_n\}$，要求序列 $\{b_n\}$ 满足 $\{c_n\}$ 单调不降，其中 $c_i = a_i^{2^{b_i}}$，求出最小的 $\sum b_i$。

朴素做法：$i$ 从 2 扫到 n。若 $a_i < a_{i-1}$ 则一直让 $a_i$ 做平方运算，记录次数。

做法缺陷：

1. 爆 ll。

2. 平方次数太多复杂度爆了。

## 猜结论

若 $a_{i - 1} \leq a_i < a_{i - 1}^2$，则 $b_i$ 最小取 $b_{i-1}$。

## 证明

$$c_{i-1} = a_{i-1}^{2^{b_{i - 1}}}$$

$$c_i = a_i^{2^{b_i}}$$

两边同时取 $\log$。

$$\log c_{i-1} = 2^{b_{i - 1}}\log(a_{i-1})$$

$$\log c_{i} = 2^{b_{i}}\log(a_{i})$$

$$\therefore 2^{b_{i - 1}}\log(a_{i-1}) \leq 2^{b_{i}}\log(a_{i})$$

$$\therefore 2^{b_{i-1}-b_i}\leq \frac{\log(a_i)}{\log(a_{i-1})}$$

$$\because 1 \leq \frac{\log(a_i)}{\log(a_{i-1})} < 2$$

$$\therefore b_{i-1} - b_i < 1$$

$$b_i > b_{i-1} - 1$$

又 $b_i$ 均为整数，所以 $b_i$ 最小取 $b_{i-1}$。

## 实现

设 $f_i$ 代表第 $i$ 位满足 $c_i \geq c_{i-1}$ 最小的 $b_i$。

先把原序列中的 $a_i$ 调整到大于等于 $a_{i-1}$ 且小于其两倍的位置。

再拿调整次数（往小调为负号）+ $f_{i-1}$ 即可得到 $f_i$。

## Ending

作者数学水平有限，若上面有瑕疵请及时与作者联系。

[提交记录](https://codeforces.com/contest/1995/submission/272158910)。

[视频讲解](https://www.bilibili.com/video/BV1Lb421J7Gu)。

---

## 作者：luqyou (赞：1)

写一篇不需要注意精度问题的题解。

# 思路

令 $f(x,k)$ 为将数 $x$ 平方 $k$ 次后的结果。

注意到若 $a<b(a,b>0)$，有 $f(a,k)<f(b,k)$。

我们记 $p_i$ 为 $a_i$ 操作到仍然小于等于 $a_{i-1}$ 的最多操作次数。

于是，我们分讨：

- 若 $a_i < a_{i-1}$，则我们直接在原序列上不断平方 $a_i$ 直到不满足条件，不难发现若 $a_i<a_{i-1}$ 则 $p_i = p_{i-1}+1$（因为此时你再平方一次有 $a_i > a_{i-1}$，此时有 $f(a_i,p_{i-1}) > f(a_{i-1},p_{i-1})$），否则 $p_i = p_{i-1}$。

- 否则我们可以不断平方 $a_{i-1}$。记平方的次数为 $k$，则 $p_i = \min(k,p_{i-1})$。

答案为上述过程情况一中执行平方操作的次数 $+\sum p_i$。

# code

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define sc second
#define pii pair<int,int>
#define pb push_back
using namespace std;
const int maxn=2e5+10;
int n,a[maxn],pw,res,testcase;
void solve(){
	cin>>n,pw=res=0,testcase++;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++){
		if(a[i]>=a[i-1]){
			int rep=pw,num=a[i-1];
			while(num*num<=a[i]&&rep) num*=num,rep--;
			res+=rep,pw=rep;
//			cout<<i<<":"<<res<<endl;
			continue;
		}
		if(a[i]==1) return cout<<-1<<endl,void();
		while(a[i]*a[i]<=a[i-1]) a[i]*=a[i],res++;
		res+=pw;
//		cout<<i<<":"<<res<<endl;
		if(a[i]>=a[i-1]) continue;
		pw++,res++;
//		cout<<"+1"<<endl;
//		cout<<i<<" "<<pw<<endl;
	}
//	cout<<testcase<<":";
	cout<<res<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t=1;
    cin>>t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1995C)

本做法不用考虑精度误差。

根据初中知识我们可以知道如果比较 $a$ 和 $b$ 的大小可以比较 $\sqrt a$ 和 $\sqrt b$ 的大小。

在本题中，很明显，对于一个数 $i$ 如果在它前面还有一个 $i$，那么这个 $i$ 的幂次一定要大于等于前面的 $i$ 的幂次，才可以保证这个 $i$ 不会比前一个数小。

然后我的思路是对于一个数 $i$，直接去与前一个数比较，如果更小幂次就翻倍。

现在记数 $i$ 的幂次翻倍次数为 $v_i$，则这个 $i$ 实际变为的数就是 $i^{2^{v_i}}$。

现在想如何实现比较数 $a$ 和数 $b$ 的真实数的大小，也就是比较 $a^{2^{v_a}}$ 和 $b^{2^{v_b}}$ 的大小。

我们已经知道比较 $a$ 和 $b$ 的大小可以比较 $\sqrt a$ 和 $\sqrt b$ 的大小，那么我们就可以把 $a^{2^{v_a}}$ 和 $b^{2^{v_b}}$ 不断开方，知道有一个数幂次变为 $1$。

如果 $v_a\le v_b$，则经过不断开方后要比较的数就变为 $a$ 和 $b^{2^{v_b-v_a}}$，如果 $v_b-v_a\ge 5$，因为 $a\le 10^6$，且 $2^{v_b-v_a}\ge 32$，所以一定有 $a\le b^{2^{v_b-v_a}}$。接下来考虑如果 $v_b-v_a=4$，那么如果 $b=2$ 就直接比较 $a$ 和 $b^{2^{v_b-v_a}}$ 的大小，否则很明显是 $b^{2^{v_b-v_a}}$ 大，根据前面 $v_b-v_a\ge 5$ 的情况的思路来想就可以证明。对于 $v_b-v_a=3$，$v_b-v_a=2$，$v_b-v_a=1$ 的情况也这样讨论一下就行。

如果 $v_a\ge v_b$，只需要按照相同的思路来想就行。

现在已经解决比较大小的实现，但是如果 $v_i$ 每次加一加一地增长会超时，那么这时候考虑倍增。

如果第一次 ${a_i}^{2^{v_{a_i}}}$ 小于 ${a_{i-1}}^{2^{v_{a_{i-1}}}}$，那么 $v_{a_i}$ 加一，如果第二次判断还是如此那么 $v_{a_i}$ 加二，以此类推，直到 ${a_i}^{2^{v_{a_i}}}$ 大于 ${a_{i-1}}^{2^{v_{a_{i-1}}}}$ 时退出循环。

然后记最后一次 $v_{a_i}$ 加的数是 $f$，那么接下来再用一个循环，如果 ${a_i}^{2^{v_{a_i}-f}}$ 大于 ${a_{i-1}}^{2^{v_{a_{i-1}}}}$，则 $v_{a_i}$ 减去 $f$，然后 $f$ 除以 $2$，否则只执行 $f$ 除以 $2$ 的操作就行。若 $f$ 被除到等于 $0$ 时退出循环。

对于 $a_i=1$ 的情况特判即可，在此不过多阐述。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
int n;
ll a[200010];
double v[1000010];
ll c[1000010];
inline bool check(int x,int y)
{
	double mx=v[x],my=v[y];
	if(mx>my)
	{
		mx-=my,my-=my;
		if(mx>=5) return 0;
		if(mx>=4&&x>=3) return 0;
		if(mx>=3&&x>=10) return 0;
		if(mx>=2&&x>=100) return 0;
		return pow(x*1.0,pow(2,mx))<y;
	}
	else
	{
		my-=mx,mx-=mx;
		if(my>=5) return 1;
		if(my>=4&&y>=3) return 1;
		if(my>=3&&y>=10) return 1;
		if(my>=2&&y>=100) return 1;
		return x<pow(y*1.0,pow(2,my));
	}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ll ans=0;
		scanf("%d",&n);
		for(register int i=1;i<=n;i++) scanf("%lld",&a[i]),c[a[i]]++;
		c[a[1]]--;
		for(register int i=2;i<=n;i++)
		{
			if(a[i]<a[i-1]&&a[i]==1)
			{
				ans=-1;
				break;
			}
			ll f=1;
			while(check(a[i],a[i-1]))
			{
				v[a[i]]+=f;
				ans+=c[a[i]]*f;
				f*=2;
			}
			f/=2;
			while(f)
			{
				v[a[i]]-=f;
				if(!check(a[i],a[i-1])) ans-=c[a[i]]*f;
				else v[a[i]]+=f;
				f/=2;
			}
			c[a[i]]--;
		}
		printf("%lld\n",ans);
		for(register int i=1;i<=n;i++) v[a[i]]=c[a[i]]=0;
	}
	return 0;
}
```

---

## 作者：Leeb (赞：1)

### 题意简述

给定长度为 $n$ 序列 $a_i$，求至少进行多少次平方操作（对于每个 $a_i$）使得序列 $a_i$ 变为不降序列。

### 解题思路

我们假设对每个 $a_i$ 进行 $k_i$ 次平方操作，于是有：$a_i^{2^{k_i}}\le a_{i+1}^{2^{k_{i+1}}}(1\le i\lt n)$，$k_1 = 0$。

于是问题就变成了确定 $k_i(2 \le i \le n)$ 的值。 

我们考虑对原式进行两次 $\log$ 操作，于是得到：$k_i\cdot\log 2 + \log \log a_i \le k_{i+1} \cdot \log 2 + \log \log a_{i+1}$。

每次对于确定的 $k_i(1\le i \lt n)$，我们需要计算出 $k_{i+1}$。可以直接暴算，但是精度不好控制（可能是我太菜了）。我选择了二分 $k_{i+1}$ 的值。如果有一次二分出来的 $k_{i+1}$ 的值仍为 $0$，则说明无解。

可能讲的不是很清楚，下面展示一下代码。

### 参考代码

```cpp
// Code by Leeb
// Powered by Visual Studio Code
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
#include <bits/stdc++.h>
// #include <cstdio>
// #include <cstring>
// #include <algorithm>
#define N 200005
#define eps 1e-9
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
#define int long long 
#define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define PII pair<int, int>
#define fir first
#define sec second
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, a[N], k[N], ans;
inline int in() {
	int a = 0; bool f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = 1; ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
	if (f) return ~a + 1;
	return a;
}
inline void print(int x) {
	if (x < 0) putchar('-'), x = ~x + 1;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
	print(x);
	putchar(ch);
}
inline bool check(double k1, double a1, double k2, double a2) {
	double lg2 = log10(2.0), lga = log10(log10(a1 * 1.0)), lgb = log10(log10(a2 * 1.0));
	return (k2 * lg2 + lgb) + eps >= (k1 * lg2 + lga);
}
inline void init() {
	n = in(); ans = 0;
	for (int i = 1; i <= n; ++i) 
		a[i] = in(), k[i] = 0;
}
inline void work() {
	for (int i = 1; i < n; ++i) {
		if (check(k[i], a[i], 0, a[i + 1])) continue;
		int l = 1, r = 1e10; 
		while (l <= r) {
			int mid = l + r >> 1ll;
			if (check(k[i], a[i], mid, a[i + 1])) k[i + 1] = mid, r = mid - 1ll;
			else l = mid + 1ll;
		}	
		if (k[i + 1] == 0) { puts("-1"); return ; }
		ans += k[i + 1]; /* printf("<%d %d>\n", i + 1, k[i + 1]); */
	}
	out(ans, endl);
}
signed main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	int t = in();
	while (t--) {
		init();
		work();
	}
	return 0;
}
```

---

## 作者：LiJoQiao (赞：1)

### 简要题意  
>$t$ 组数据，给定长度为 $n$ 的数列，你可以对每个数令它等于自身的平方，求多少次之后使得这个数列单调不减。

### 解题思路
平方和比较大小放一块我只想到朴素做法。  

我们只能使一个数变大（或不变，$1$ 的情况），因此对于一个本身就单调不减的数列，我们改变最后的数不会影响这个性质，但改变最前面的数可能会改变这个性质，需要后面的数继续修改。  
这也就是说，如果我们满足了一个数列的前面的子序列已经单调不减，我们就无需修改这个子序列中的数，应考虑如何修改后面的数。  

单调递减即除第一个数外每一个数都要大于等于前一个数，我们可以正着扫一遍，边对数列进行平方操作边记录操作次数。  
由于精度、时间、不需要得到准确的值，我们只记录给定的该数和这个数被平方了多少次。  

接下来就是对于每个数计算应该平方多少次。  
第一个数不用平方。  
对于其他的数，我们已经知道前一个数给定时的值和其平方的次数。  
我们先考虑前一个数平方 $0$ 次时，后一个数需要一直做平方操作直至大于等于这个数。  
简单的不等式性质相信大家都会吧。  
>如果 $\left|x\right|>\left|y\right|$，则 $x^2>y^2$。  

对于其他的次数，在后一个数小于等于前一个数的情况下，我们应在后一个数在上述平方次数的基础上加上这个次数。  
这个结论可以用下面的不等式反证出来。  
>如果 $x^2>y^2$，则 $\left|x\right|>\left|y\right|$。  

如果后一个数本身就比前一个数大，那么就可能存在前一个数平方一次后仍小于后一个数的情况，这时我们就应该忽略不能使前一个数大于后一个数的最大次数。  
注意后一个数的平方次数不能小于 $0$。  

对于 $1$ 的情况还需要特判，$1^2=1$，所以前一个数给定时不是 $1$ 且后一个数是 $1$ 的情况无解。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int MAXN=2e5+10;
int n,a[MAXN];
ll ans;
bool flag;
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        ans=0;
        flag=false;
        scanf("%d",&n);
        for(int i=1;i<=n;++i){
            scanf("%d",&a[i]);
        }
        ll val=a[1],val2;int times=0;
        for(int i=2;i<=n;++i){
            val2=a[i];
            if(val==1){
                val=a[i];
                continue;
            }
            if(a[i]==1){
                if(val!=1){
                    flag=true;
                    break;
                }
            }
            while(times&&val*val<=a[i]){
                --times;
                val=val*val;
            }
            while(val2<val){
                val2=val2*val2;
                ++times;
            }
            ans+=times;
            val=a[i];
        }
        if(flag)puts("-1");
        else printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：GoldenCreeper (赞：0)

无解很显然：对于所有的 $2\le i\le n$，当第 $i$ 位为 $1$ 且第 $i-1$ 位 $>1$ 时，无解。

我们从左到右进行贪心地进行操作，我们尝试通过枚举出最小的平方数使得前 $i$ 项满足要求。但是这样导致会导致运算中的数字太大，即使 `int128` 也难以满足要求。

所以，我们可以考虑在对数意义下进行操作。对 $a$ 中所有元素取对数，那么有 $\log x^2=2\log x$，所以平方操作就变成了 $\times 2$。

但这样还是很大，我们可以再取一次，那么有 $\log\log x^2=\log 2x=\log x+\log2$，这样，我们就把每步平方操作变成了加 $\log 2$。

所以，我们取 $b_i = \log\log a_i$，如果 $b_i <b_{i-1}$，设 $k=\left \lceil \dfrac{b_{i-1}-b_i}{\log2} \right \rceil$，那么就把 $b_i$ 加上 $k\times\log 2$ 然后答案加上 $k$ 即可。

注意对浮点误差的处理。

[AClink.](https://codeforces.com/contest/1995/submission/272492965)

---

## 作者：JimmyLee (赞：0)

# 题意

给定序列 $a$，每次操作可以使 $a_i\gets a_i^2$，求使 $a$ 不降的最少操作次数。

# 分析

因为 $1^k=1$，所以无解的情况只有 $\exist\ a_i=1$ 且 $\exist\ j\in[1,i), a_j>1$。

---

在有解的情况下，假设对 $a_{i-1}$ 操作 ${k_{i-1}}$ 次，对 $a_i$ 操作 ${k_i}$ 次。

此时 $a_{i-1}\gets a_{i-1}^{2^{k_{i-1}}}$，$a_i\gets a_i^{2^{k_i}}$。

因为单调不降，且序列中所有元素均为正数，所以满足：

$$
\begin{aligned}
a_{i-1}^{2^{k_{i-1}}} &\leq a_i^{2^{k_i}} \\
\log_2a_{i-1}^{2^{k_{i-1}}} & \leq \log_2a_i^{2^{k_i}} \\
2^{k_{i-1}}\log_2 a_{i-1} & \leq 2^{k_i}\log_2 a_i \\
\log_2(2^{k_{i-1}}\log_2 a_{i-1}) & \leq \log_2(2^{k_i}\log_2 a_i) \\
{k_{i-1}}+\log_2 \log_2 a_{i-1} & \leq {k_i}+\log_2 \log_2 a_i \\
{k_{i-1}}+\log_2\log_2a_{i-1}-\log_2\log_2a_i & \leq {k_i} \\
\end{aligned}
$$

所以 ${k_i}$ 的最小取值为 $\lceil {k_{i-1}}+\log_2\log_2a_{i-1}-\log_2\log_2a_i \rceil$。

注意 ${k_i}$ 不能取负数，所以 ${k_i} \gets \max({k_i}, 0)$。

显然第一位不操作，故 $k_1=0$。

逐项处理即可。

答案就是 $\sum k_i$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
#define eps 1e-8

int a[maxn];

void solve()
{
    int64_t n, ans=0;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int la=0;
    for(int i=2;i<=n;i++)
    {
        if(a[i]==1&&a[i-1]!=1) return cout<<-1<<'\n', void();
        la=max((int)ceil(la+log2(log2(a[i-1]))-log2(log2(a[i]))-eps), 0);
        ans+=la;
    }
    cout<<ans<<'\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin>>t;
    while(t--) solve();
}
```

---

