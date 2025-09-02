# [ARC122B] Insurance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc122/tasks/arc122_b

すぬけくんは明日の運勢を占いました． その結果，$ N $ 個のシナリオのうちどれか一つが等確率で発生し，そのうち $ i $ 番目のシナリオでは $ A_i $ 円を失うことを知りました．

そこですぬけくんは，今日保険に入ることにしました． 保険会社に $ x $ 円を支払ったとすると，$ A_i $ 円を失った場合には $ \min(A_i,2x) $ 円が補填されます． ここで，$ x $ として任意の非負**実数**を選ぶことができます．

すぬけくんは，最終的に自分が失う金額（$ =x+A_i-\min(A_i,2x) $）の期待値を最小化したいです． この最小値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力される値はすべて整数である

### Sample Explanation 1

$ x=1.5 $ とするのが最適です． $ 1.5 $ 円支払ったあと，以下の $ 3 $ つのシナリオが等確率で起こります． - シナリオ $ 1 $: $ 3 $ 円失ったあと，$ \min(3,2x)=3 $ 円が補填される． 最終的にすぬけくんが失う金額は，$ x+A_1-\min(A_1,2x)=1.5+3-3=1.5 $ 円である． - シナリオ $ 2 $: $ 1 $ 円失ったあと，$ \min(1,2x)=1 $ 円が補填される． 最終的にすぬけくんが失う金額は，$ x+A_2-\min(A_2,2x)=1.5+1-1=1.5 $ 円である． - シナリオ $ 3 $: $ 4 $ 円失ったあと，$ \min(4,2x)=3 $ 円が補填される． 最終的にすぬけくんが失う金額は，$ x+A_3-\min(A_3,2x)=1.5+4-3=2.5 $ 円である． よって，失う金額の期待値は，$ (1.5+1.5+2.5)/3=1.833333\cdots $ です．

## 样例 #1

### 输入

```
3
3 1 4```

### 输出

```
1.83333333333333333333```

## 样例 #2

### 输入

```
10
866111664 178537096 844917655 218662351 383133839 231371336 353498483 865935868 472381277 579910117```

### 输出

```
362925658.10000000000000000000```

# 题解

## 作者：under_the_time (赞：0)

## 题意

> 有 $n$ 个事件，每个事件发生概率均为 $\cfrac{1}{n}$，第 $i$ 个事件发生会产生 $a_i$ 的代价。要求选择一个非负实数 $x$，产生 $x$ 的代价；若第 $i$ 个事件发生，那么产生的代价变为 $a_i-\min\{a_i,2x\}$。求最小的代价期望值。
>
> $n\le 10^5$，$1\le a_i\le 10^9$。

## 解法

最终的期望值即为
$$
\cfrac{1}{n}\left(\sum_{i=1}^n x+a_i-\min\{a_i,2x\}\right)
$$
选定 $x$ 后，$\forall a_i<2x$ 代价为 $x$，$\forall a_i>2x$ 代价为 $a_i-x$（$a_i=2x$ 归到一种情况中即可），那么我们考虑将 $a$ 从小到大排序，预处理一个后缀和，那么找到分界点后就可以直接算出括号里的值。观察到取 $x=\cfrac{a_i}{2}$ 并不劣，于是我们让 $x$ 取遍每个 $\cfrac{a_i}{2}$ 求个最小值即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5, P = 1e9 + 7;
#define ll long long
int a[maxn], n;
ll sum[maxn];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1); 
    for (int i = n; i >= 1; i --) sum[i] = sum[i + 1] + a[i];
	double all_ans = 2e18;
	for (int i = 1; i <= n; i ++) {
		double x = a[i] / 2.0;
		double pre = x * i, suf = sum[i + 1] - x * (n - i);
        all_ans = min(all_ans, pre + suf);
	} all_ans /= n;
	return printf("%.12lf", all_ans), 0;
}
```

---

## 作者：XYQ_102 (赞：0)

## 思路
要求最小化 $\frac{\sum_{i=1}^{n}x+a_i-min(a_i,2x)}{n}$，把常量扔掉后即最小化 $y=nx-\sum_{i=1}^{n}min(a_i,2x)$。

后面那个 $min$ 的取值与 $a_i$ 和 $2x$ 的相对大小有关，所以想到给 $a$ 排序。

如果 $2x$ 落在某段 $[a_i,a_{i+1}]$ 的区间上：

$y=nx-\sum_{i=1}^{n}min(a_i,2x)=(-n+2i)x-\sum_{j\leq i}a_j$

发现 $y$ 在这段区间上单调或不变，$x$ 取某一端点不会更劣。

于是枚举 $x=\frac{a_i}{2}$ 即可。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a[100010];
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	sort(a+1,a+n+1);
	double ans=1e18,sum=0;
	for(int i=0;i<=n;++i)
	{
		sum+=a[i];
		double x=(double)a[i]/2;
		ans=min(ans,n*x-(sum+(n-i)*x*2));
	}
	ans=(ans+sum)/n;
	cout<<fixed<<setprecision(10)<<ans<<"\n";
	return 0;
}
```

---

## 作者：smydahaoren (赞：0)

**做题感想：还是吃了很多没有看清数据范围的亏。**

本来以为要二分做，后来发现数据范围小了，可以暴力加前缀和。再后来发现我又忘记了开 `long long`。

------------
**题目思路：**

首先带入一个 $x$ 值，对于 $A_i<2\times x$ 的，可以将损失定为 $x$。对于 $A_j >2\times x$ 的，可以将损失定为 $A_j-2\times x$。那么总损失就是所有的两种情况相加了。现在需要求出 $x$ 的值。

对于 $x$ 的值的大小对总损失的影响，就是考虑多一个 $A_i$ 可以用保险解决。那么因此可以得出 $2\times x$ 的值一定和一个 $A_i$ 相等。因此，对 $A$ 进行遍历即可，选择总损失最小的情况。



------------
**AC 代码：**

```
#include<bits/stdc++.h>
#define int long long
#define INF 2e18
using namespace std;
const int N=10000009;
int ans=INF;
int a[N],n,s[N],x;
signed main(){
	//freopen(" ","r",stdin);
	//freopen(" ","w",stdout);
	cin>>n;
	s[0]=0;
	for(int i=1;i<=n;i++){
	cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
	s[i]=s[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		x=a[i];
		ans=min(ans,x*(2*i-n)+(s[n]-s[i])*2);
	}
	double cnt=ans;
	cout<<fixed<<setprecision(10)<<cnt/2/n;
	return 0;
}

```


---

## 作者：CarlosLiu (赞：0)

## 题目大意
一个人有 $n$ 种情况，有概率损失 $A _ {i}$ 元，但可以支付 $x$ 元获得 $\min(A _ {i},2x)$ 元的补偿。求 $x$ 变化时此人损失的钱的期望的最小值。
## 解题思路
我们把 $A _ {i}$ 排序，并假设 $A _ {i}\le 2x \le A _ {i+1}$ 成立。

对于 $1\le j \le i$ 的部分，损失值 $A _ {i}+x-\min(A _ {i},2x)$ 与 $x$ 相等。否则，损失值与 $A _ {i}-x$ 相等。期望值就是所有这些之和除以 $n$ 的结果。显然这关于 $x$ 是线性函数，最小值在端点取到，所以 $2x$ 等于某个 $A _ {i}$ 是需要的。

接下来就简单了，把每一种可能遍历一遍求最小值就行了。为了加快速度，可以动用 $sum _ {i}$ 计算前 $i$ 个数之和。

最后，处理好数据范围和小数就行了。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[100009],sum[100009],x;
long long ans,tem;
double t;
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		a[i]*=2;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	tem=2000000000000000000;
	for(int i=1;i<=n;i++) {
		x=a[i]/2;
		ans=0;
		ans+=i*x*1.0;
		ans-=x*(n-i)*1.0;
		ans+=(sum[n]-sum[i]);
		if(ans<tem) tem=ans;
	}
	t=tem*0.5/n;
	printf("%.10lf",t);
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

最小化这个式子：

$$\dfrac{\sum\limits_{i=1} ^n a_i+x-\min(a_i,2x)}{n}$$

$\frac{1}{n}$ 与 $\sum a_i$ 是常量，先丢掉，式子变为 $nx-\sum\limits_{i=1} \min(a_i,2x)$ 这个东西。

观察发现，当我们将 $a_i$ 排升序之后，$-\sum\min(a_i,2x)$ 应该分为两段贡献，假设断点为 $k$：前面一段满足 $a_i\le 2x$，贡献为 $-\sum \limits_{j=1}^k a_j$，后面一段每个数的贡献全为 $2x$，总贡献 $2x\times (n-k)$。

容易发现 $2x$ 在 $[a_i, a_i+1]$ 中时 $-\sum\min(a_i,2x)$ 的贡献是一样的，那么要使得前面的 $nx$ 最小，我们应该取端点，即 $a_i$ 或者 $a_{i+1}$。

所以枚举 $2x=a_i$，即 $x=\frac{a_i}{2}$，计算答案即可。

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define inf 0x3f3f3f3f
#define linf 1e18
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define umap(x,y) sd unordered_map<x,y>
#define pque(x) sd priority_queue<x>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=1e5+10;
int n;
int a[N];
db s[N];//记录前缀和
il void solve()
{
	n=read();
	F(i,1,n) a[i]=read();
	sd sort(a+1,a+1+n);
	F(i,1,n) s[i]=1.0*s[i-1]+1.0*a[i];
	db ans=1.0*linf;
	F(i,1,n)
	{
		db x=1.0*a[i]/2;
		ans=MIN(ans,s[n]+n*x-s[i]-(n-i)*x*2);
	}
	printf("%.10f",ans/n);
	
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

