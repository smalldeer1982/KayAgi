# [ABC216E] Amusement Park

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc216/tasks/abc216_e

髙橋君は遊園地に遊びに行きました。  
 この遊園地には $ N $ 個のアトラクションがあり、$ i $ 個目のアトラクションの「楽しさ」の初期値は $ A_i $ です。

髙橋君が $ i $ 個目のアトラクションに乗ると、以下の現象が順番に起きます。

- 髙橋君の「満足度」に、$ i $ 個目のアトラクションの現在の「楽しさ」が加算される。
- $ i $ 個目のアトラクションの「楽しさ」が、$ 1 $ 減少する。

髙橋君の「満足度」の初期値は $ 0 $ です。髙橋君はアトラクションに合計 $ K $ 回まで乗ることができます。  
 最終的な髙橋君の「満足度」の最大値はいくつですか？

なお、髙橋君の「満足度」はアトラクションに乗ること以外で変化しません。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ K\ \leq\ 2\ \times\ 10^9 $
- $ 1\ \leq\ A_i\ \leq\ 2\ \times\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

$ 1 $ 個目のアトラクションに $ 2 $ 回、$ 3 $ 個目のアトラクションに $ 3 $ 回乗ります。 最終的な「満足度」は、$ (100+99)+(102+101+100)=502 $ です。 「満足度」を $ 503 $ 以上にする方法はないので、$ 502 $ が答えになります。

### Sample Explanation 2

アトラクションに乗る合計回数は、$ K $ 回より少なくても構いません。

## 样例 #1

### 输入

```
3 5
100 50 102```

### 输出

```
502```

## 样例 #2

### 输入

```
2 2021
2 3```

### 输出

```
9```

# 题解

## 作者：Morax2022 (赞：5)

# ABC216E
考虑二分:

既然求满意度最大值，那一定会将大多乐趣值玩到还剩 $mid$ 点，先排个序，从前往后推，直到枚举出合适的 $mid$，如果不够则下调，如果多出来的次数太多则上调，最后再用高斯求和将和算出来即可，记住要把多出来的次数出来的加上。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[100001], b[100001], n, k;
bool cmp(int x, int y)
{
	return x > y;
}
bool check(long long mid)
{
	long long sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] - mid > 0)
		{
			sum += (a[i] - mid); 
		}else break;
	}
	if (sum > k) return 1;
	return 0;
}
main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> k; 
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1, cmp);
	long long l = 0, r = 2 * 1e9 + 1, mid;
	while (l < r)
	{
		mid = l + r >> 1;
		if (check(mid)) l = mid + 1;
		else r = mid;
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] <= l) continue;
		k -= (a[i] - l);
		if ((a[i] - l) * (a[i] + l + 1) / 2 > 0)
			ans += (a[i] - l) * (a[i] + l + 1) / 2;
	}
	cout << ans + l * k;
}
```


---

## 作者：highkj (赞：1)

# 思路
其实这就是一个贪心，我们首先能发现我们一定要让前 $i$ 个数都变为和 $a_i$ 一样然后继续向下变，那么我们就可以先用一个 $s_i$ 表示将前 $i-1$ 个变为 $a_i$ 的满意值。然后我们也可以对于每一个数算出它的次数，当遇到第一个大于 $k$ 的话，我们就将前 $s_{i-1}$ 加上然后我们再算出我们现在的 $i$ 个数同时能向下减得代价先加上，再将多余不足一组的向下减即可。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n,k;
int a[100100];
int sum,tot;
int s[100100],res[100100];
fire main() {
//	freopen("park.in","r",stdin);
//	freopen("park.out","w",stdout);
	cin>>n>>k;
	rep(i,1,n) cin>>a[i],sum+=a[i],tot+=(a[i]+1)*a[i]/2;
	if(sum<=k) {
		cout<<tot<<endl;
		return false;
	}
	pai(a,1,n);
	reverse(a+1,a+1+n);
	rep(i,1,n+1) s[i]=s[i-1]+a[i];
	int last=1;
	rep(i,2,n+1) {
		res[i]=res[i-1]+(a[i-1]+a[i]+1)*(a[i-1]-a[i])/2*(i-1);//算
		int p=s[i]-a[i]*i;
		if(p>=k) { //第一个大于
			int lst=s[i-1]-a[i-1]*(i-1);
			int shao=k-lst;
			int tong=shao/(i-1); //能将这一组的数全部改变
			int yu=shao%(i-1); //不足一组的
			int now=res[i-1]+(a[i-1]+a[i-1]-tong+1)*tong/2*(i-1)+(a[i-1]-tong)*yu;
			print(now); //输出
			break;
		}
	}
	return false;
}
/*
3 6
2 3 2
*/
```

---

## 作者：Jerrlee✅ (赞：1)

## 题意
高桥去游乐园玩。

有 $n$ 个游乐设施，每次玩时满意度加上此设施的乐趣值，同时设施的乐趣值减一，直到变成 $0$。

一个设施可以玩多次，求一共玩 $k$ 次后高桥满意度的最大值。

$n \leq 1 \times 10^5$；

$k,a_i \leq 2 \times 10^9$。

## 思路
贪心，高桥一定会选当前乐趣值最大的。

考虑将所有设施的乐趣值从大到小排序一下，形成阶梯分布。

每次把阶梯最高一层（也就是当前乐趣最大值）削掉，如此这样重复下去即可。

------------

还可以使用二分。

我们可以二分出分界值 $p$，其满足单调性，$p$ 肯定唯一。

把所有大于 $p$ 的变成 $p$，再把其中一些 $p$ 变成 $p-1$。

两方法均可在 $O(n \log n)$ 时间内跑完。

代码就不给了。

---

## 作者：WaterSun (赞：0)

# 思路

首先有一个显然的贪心策略：对于目前的 $a$ 序列，显然选择 $\max(a_i)$ 最优。

可以直接用优先队列维护。

如果当前最大的数是 $a$，与次大的数是 $b$，那么可以使所有的 $a$ 一直做贡献，直到 $a = b$。

由此，我们的优先队列中用一个 `pair`，分别存数值，以及这个数值出现的数量即可。

# code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define int long long
#define re register

using namespace std;

typedef pair<int,int> pii;
int n,m,ans;
priority_queue<pii> q;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read();
	m = read();
	for (re int i = 1;i <= n;i++){
		int x;
		x = read();
		q.push({x,1});
	}
	while (m && q.size() >= 2){
		pii a = q.top();
		q.pop();
		pii b = q.top();
		q.pop();
		if (a.fst == b.fst) q.push({a.fst,a.snd + b.snd});//如果数值相同，直接合二为一 
		else{
			int t = a.fst - b.fst;//对于每一个数从 a.fst -> b.fst 所需的次数 
			int num = t * a.snd;//对于所有数值为 a.fst 的数，变为 b.fst 所需的次数 
			if (num <= m){//如果剩余次数可以让当前操作执行，则执行 
				m -= num;//减去所需的操作次数 
				ans += ((2 * a.fst - t + 1) * t / 2) * a.snd;
				/*
				对于每一个数的贡献为 a.fst + (a.fst - 1) + (a.fst - 2) + ... + (a.fst - t + 1)
				                     = (2 * a.fst - t + 1) * t / 2
				所以，对于所有的数贡献为 ((2 * a.fst - t + 1) * t / 2) * a.snd
				*/
				if (a.fst > t) q.push({a.fst - t,a.snd});//传回去 
				q.push(b);
			}
			else{
				int A = m / a.snd;// A 表示所有的数能共同减多少 
				int B = m % a.snd;// B 表示有多少数在共同减完后还能减 1 
				ans += ((2 * a.fst - A + 1) * A / 2) * a.snd;//同上 
				ans += (a.fst - A) * B;
				if (a.fst > t) q.push({a.fst - t,a.snd});
				q.push(b);
				goto End;
			}
		}
	}
	if (m){//如果 m 有剩余，再执行一次 
		pii a = q.top();
		int t = a.fst;
		int num = t * a.snd;
		if (num <= m){
			m -= num;
			ans += ((t + 1) * t / 2) * a.snd;
		}
		else{
			int A = m / a.snd;
			int B = m % a.snd;
			num = t * a.snd;
			ans += ((2 * t - A + 1) * A / 2) * a.snd;
			ans += (t - A) * B;
		}
	}
	End:;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Symbolize (赞：0)

# 思路
首先，看到数据范围就可以知道突破口在于 $n$。其次，因为每次高桥都只会去玩目前最好玩的项目，所以当某两个项目的乐趣值并列第一时，高桥一定会交替游玩这两个项目，直到他们不再是最好玩的项目。那这个过程中，交替游玩的项目数量是单调不减的，且每次改变只会多 $1$。所以我们可以先对数组排序，再利用等差数列求和公式求出在多少个项目被交替游玩时，高桥累计游玩了 $k$ 次项目，再利用等差数列的末项公式重新计算本次交替游玩的项目乐趣值会降低到多少，最后加上答案结束循环就行了。
# Code
```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(register auto i:x)
#define debug() puts("----------")
const int N=1e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
const double pi=acos(-1);
using namespace std;
typedef complex<double> cp;
int n,k,a[N],ans;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
bool cmp(int x,int y){return x>y;}//从大到小
signed main()
{
	n=read();
	k=read();
	rep1(i,1,n) a[i]=read();
	sort(a+1,a+n+1,cmp);//排序
	a[n+1]=0;//加一个下限
	rep1(i,1,n)
	{
		int d=a[i]-a[i+1];//与下个项目相差的值（也就是项数）
		k-=i*d;
		if(k<0)//玩完了
		{
			k+=i*d;
			int num=k%i/*不构成一次交替游玩的数量*/,sum=k/i/*构成交替游玩的轮数*/;
			int last=a[i]-sum+1;//末项
			ans+=i*(a[i]+last)*sum/2;//等差数列求和
			ans+=num*(last-1);//单独加上剩下的次数
			break;//结束循环
		}
		ans+=i*(a[i+1]+1+a[i])*d/2;//等差数列求和
	}
	cout<<ans<<endl;//输出
	return 0;
}

```

---

