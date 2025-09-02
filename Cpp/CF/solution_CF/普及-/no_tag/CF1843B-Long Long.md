# Long Long

## 题目描述

给出一个包含 $n$ 个数字的数列 $a$。你可以执行任意次操作，每次操作可以更改 [l, r] 范围内的正负性（正数变负，负数变正，0 不变）。你要使得数列每个元素之和尽量大，问最小的操作次数。

多组询问。

## 说明/提示

$1\leq T \leq 10^4$

$1\leq n \leq 2\times10^5$

$-10^9\leq a_i \leq 10^9$

数据保证所有询问的 $n$ 总和不超过 $2\times10^5$。

统计数字之和部分可能会爆 int，请选择合适的储存方式。

## 样例 #1

### 输入

```
5
6
-1 7 -4 -2 5 -8
8
-1 0 0 -2 1 0 -3 0
5
2 -1 0 -3 -7
5
0 -17 0 1 0
4
-1 0 -2 -1```

### 输出

```
27 3
7 2
13 1
18 1
4 1```

# 题解

## 作者：Auto_Accepted (赞：8)

## 题意：

给你一个序列，现可对它执行若干次操作，每一次操作可以把一个区间里的数乘 $-1$。

现在问数列和的最大值与达到这个最大值所需要的最少的操作次数。

## 题解：
贪心。

第一问是简单的，因为最优就是全非负数。输出序列绝对值之和即可。

接下来解决第二问。

不难发现，如果有几个负数是连续排列的，就可以用一次操作把他们全变成非负数，所以不断的找全是负数的区间，最后输出区间数即可。

证明：

假设有 $n$ 个负数区间，则有 $n-1$ 个非负数区间把它们隔开。而如果先对这整个区间进行一次操作的话，总操作次数为 $n-1+1=n$ 次，并没有比直接对负数区间进行操作更优。

所以贪心策略正确。

注意，要开 `long long`。

## 代码：
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n , a[1000005];
signed main() {
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		int ans = 0 , cnt = 0;
		for(int i = 1;i <= n;i++){
			cin >> a[i];
			ans += abs(a[i]);
		}
		a[0] = 114514;
		for(int i = 1;i <= n;i++){
			if(a[i] < 0){
				cnt++;
				while(a[i] <= 0 && i <= n) i++;
			}
		}
		cout << ans << ' ' << cnt << endl;
	}
	return 0;
}
```


---

## 作者：Dream__Sky (赞：1)

题意简述：

今天 Alex 得到了长度为 $n$ 的数组 $a_1,a_2,…,a_n$。他可以应用任意多的操作（包括零操作）来改变数组的元素。

在 $1$ 的操作中，Alex 可以选择任何 $l$ 和 $r$，使得 $1≤l≤r≤n$，并将数组中从 $l$ 到 $r$ 的所有元素乘以 $−1$。

Alex 上学要迟到了，所以你应该帮助他找到数组中数字的最大可能之和，这个数字可以通过进行任何数量的运算得到，以及为此必须进行的最小运算数量。

分析：

第一问是在求经过一系列的操作后，最大可能的和。那么我们想，只要把所有的负数都通过操作 $1$ 变成正数，以此来相加。

第二问是在求最大的和下，最少的操作次数。那我们只要在每一次操作时选择尽量多的负数和零（零不影响结果），即求元素为负数的最长连续子序列的数量。

附代码：

```cpp
#include <bits/stdc++.h>
#define int long long //记得开longlong
using namespace std;
int T,n,x;
signed main()
{
	cin>>T;
	while(T--)//T组数据
	{
		int daan1=0,daan2=0;
		bool p=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			daan1+=abs(x);//第一问
			if(x<0&&!p) p=1,daan2++;//如果这是新的连续负数子序列的第一个，那么第二问答案+1，p标记为1
			else if(x>0) p=0;//如果为正数，那么说明一个负数序列结束了，p标记为0
		}
		
		cout<<daan1<<" "<<daan2<<"\n";
	}
	return 0;
}
```


---

## 作者：_O_v_O_ (赞：1)

### 题意：

给你一个长的为 $n$ 的数列 $a$,每次能选择一个区间 $[l,r]$，表示将这个区间中所有数变成其相反数，你可以进行任意次该操作。问这个数列的和最大是多少，以及变成这个和最大的数列需要几次操作。

### 思路：

第一问是将所有数变成其绝对值再相加即可。

第二问中，我们可以发现：在区间 $[l,r]$ 中，假设里面的数全是 $\le 0$ 的数一次操作便可以将里面的数全部变成自然数。所以我们只用统计这个数列中有多少个满足该要求的区间即可。

有人会考虑正被一些反夹在中间的情况，但是，如果这样，正又变成负了，还要消一次，和分别消两次负次数一样。


### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long  //因为数据原因要开long long

int t,n,a;

signed main(){
	cin>>t;
	while(t--){
		int ans1=0,ans2=0;  //两问的答案
		bool flag=true;  //表示该数是否在特殊区间内
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a;
			ans1+=abs(a);
			if(a<0&&flag){  //一个特殊区间的开始
				ans2++;
				flag=false;
			} 
			if(!flag&&a>0) flag=true;  //一个特殊区间的的结束
		}
		cout<<ans1<<' '<<ans2<<endl;
	}
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/113159249)

---

## 作者：white_carton (赞：0)

[$\color{#52C41A}\text{题目传送门}$](https://www.luogu.com.cn/problem/CF1843B)

[$\color{#52C41A}\text{更好的体验}$](https://inksennns.blog.luogu.org/)

### 题意
有一个长 $n$ 的序列，通过若干次对某些子段取反，得到最大序列和，输出最大序列和和得到这个和的最小操作次数。

### 分析
很容易可以看出，得到最大序列和需要将序列中的所有负数变为正数，所以第一个答案显然就是 $\sum\limits_{i=1}^n\left|a_i\right|$。

再来看第二个问题，求最小操作次数。同样很显然，我们可以知道，一次取反越多个负数一定不劣，而取反 $0$ 与不取反没有区别，所以遇到负数时打上标记并将答案 $+1$，遇到正数时清空标记，遇到 $0$ 时不做处理。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int dc=1,a[200100];
void solve(){
	int n,flag=0,cnt=0,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<0){
			if(flag==0){
				cnt++;
				flag=1;
			}
		}
		if(a[i]>0){
			flag=0;
		}
		sum+=abs(a[i]);
	}
	cout<<sum<<" "<<cnt<<endl;	
}
signed main(){
	int t=(dc?read():1);
	while(t--)
		solve();
	return 0;
}
```
### end
~~题目名告诉我们，```#define int long long``` 是很必要的。~~

---

## 作者：EmptyAlien (赞：0)

# 题意

给定一个长度为 $n$ 的数组 $A$，有一种操作：

- 将一个区间内的 $A$ 值取反。

问题有两个：

- 经过若干次操作后，$\sum_{i=1}^n A_i$ 最大为多少。

- 在满足第一问的条件下，最少要经过几次操作。

# 思路

## 第一问

首先，第一问非常简单，既然不限制操作次数，那我们直接简单粗暴对于每一个 $A_i$ 为负数 $i$ 进行单独操作，这样答案就是：
$$
\sum_{i=1}^n |A_i|
$$

## 第二问

第二问，首先，我们看到 $0$ 非常不爽对不对，然后我们要做什么？

简单粗暴把 $0$ 扔掉，

对，因为 $0$ 无论是对和值还是操作次数都没有影响。

所以我们遇到 $0$ 直接 `continue` 掉就可以了。

```cpp
if (t == 0) continue;
```

现在就好办了，现在先说结论：

**答案就是极大负数子段的数量**。

也就是相当于说，我们把每一个极大负数子段直接一个操作干掉对吧。

表面上看是对的，就是个贪心吗。

有人就说了，那我不能先把一整段覆盖一遍，然后再把原本是正的操作回来吗？

确实有点道理哈。

但是只要上手算一下就能发现其实两个方法的答案是一样的。

# 忠告

如题目所说一样，**要开 `long long`**！

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    long long n, t;
    cin >> n;
    long long ans1 = 0, ans2 = 0;
    bool lst = true;
    for (int i = 1; i <= n; i++) {
        cin >> t;
        if (t == 0) continue;
        ans1 += abs(t);
        if (lst and t < 0) {
            ans2++;
            lst = false;
        }
        if (t > 0) lst = true;
    }
    cout << ans1 << " " << ans2 << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

---

## 作者：_Only_this (赞：0)

### Long Long

------------

这题本是道水题，但我却调了半个小时。

若干次操作，每次操作可将一个区间里的所有数变成其相反数。

所以显然，最大序列和就是所有数的绝对值之和。

至于最小操作次数，

在把 $0$ 排除的情况下，直接看有几堆相邻的负数即可。

另外，此题须开 long long。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 2e5+5;
ll T,n;
ll a[maxn];
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(ll i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			if(!a[i])
				n--,i--;
		}
		ll time=0,ans=0;
		a[0]=1;
		for(ll i=1;i<=n;i++)
			time+=(a[i]<0 && a[i-1]>0);
		for(ll i=1;i<=n;i++)
			ans+=(a[i]<0) ? -a[i] : a[i];
		printf("%lld %lld\n",ans,time);
	}
	return 0;
}
```
完结，散花(～￣▽￣)～



---

## 作者：Night_sea_64 (赞：0)

因为你可以做任意次操作，所以我们如果要使数列的总和最大，就一定要把数列中所有数都变成非负的。所以第一问的答案就是 $\sum\limits_{i=1}^n|a_i|$。

第二问，就是找数列中极大的非正子段的个数。换句话说，就是找这样的子段 $[l,r]$，满足 $a_l\sim a_r$ 全是非正的，而 $a_{l-1}$ 和 $a_{r+1}$ 都是正的。我们可以记录当前的元素是非正的还是非负的，如果当前的元素是 $0$，那么可以非正也可以非负，跟上一个元素的状态保持不变就可以。显然这样一定最优。

最后，题目名称提醒了我们：**十年 OI 一场空，不开 long long 见祖宗！**

```cpp
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
int t,n;
signed main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        int sum=0,cnt=0;
        bool now=1;//0 负 1 正
        for(int i=1;i<=n;i++)
        {
            int x;
            cin>>x;
            sum+=abs(x);
            if(x<0&&now)cnt++,now=0;
            if(x>0&&!now)now=1;
        }
        cout<<sum<<" "<<cnt<<endl;
    }
    return 0;
}
```

---

## 作者：Iniaugoty (赞：0)

题如其名。

## problem

给出一个长为 $n$ 的序列 $a_i$，可以进行一些操作，每次将一个子段取反。求出操作后可能的最大序列和及得到这个和的最小操作次数。

## solution

显然，将所有负数都取反可以得到最大和，第一个答案就是 $\displaystyle\sum_{i=1}^{n}|a_i|$。

一次操作，取反的负数肯定是越多越好，由于取反 $0$ 实际上没有任何改变，所以第二问要求的是极大非负子段的数量。

注意一个子段如果全为 $0$ 那么取反没有任何价值，所以计数时还要考虑是否全为 $0$。

## code

不开 `long long` 见祖宗。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int T,n,a[N],sum,ans,cnt;
signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n,ans=sum=cnt=0;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++){
			sum+=abs(a[i]);
			if(a[i]<=0) cnt+=a[i];
			else if(cnt) ans++,cnt=0;//要判断是否全为 0
		}
		if(cnt) ans++;//特判结尾子段
		cout<<sum<<" "<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

给定一个长度为 $n$ 的数组 $a$。对于一个区间 $[l,r]$，你可以将 $a_l,a_{l+1},\cdots,a_r$ 变为 $-a_l,-a_{l+1},\cdots,-a_r$，问 $\sum_{i=1}^{n}a_i$ 的最大值和最小操作次数。

**解题思路**

$\sum_{i=1}^{n}a_i$ 的最大值就是 $\sum_{i=1}^{n}|a_i|$。

注意到 $0=-0$，所以对于两个负数中间夹一堆 $0$ 这种就可以将这一段反转，所以我们可以看上一个非 $0$ 数的位置，如果上一个非 $0$ 数是正数并且当前数为负数，则代表该数为一个非正数区间的开头，从而答案加 $1$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n, sum = 0, cnt1 = 0, l = 0;
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            sum += abs(a[i]);
            if(a[i] < 0 && a[l] >= 0) {
                ++cnt1;
                l = i;
            }
            if(a[i] > 0) {
                l = i;
            }
        }
        cout << sum << ' ' << cnt1 << '\n';
    }
    return 0;
}
```

---

## 作者：CheZiHe929 (赞：0)

# CF1843B 题解
## 原题链接
[**codeforces**](https://codeforces.com/contest/1843/problem/B)

[**洛谷**](https://www.luogu.com.cn/problem/CF1843B)

## 题目大意
共 $ T $ 组测试样例，每组给你一个 $ n $ 和一个长度为 $ n $ 的数组，输出该数组通过最少操作次数得到的和的最大值。

**操作：**
选定 $ l $ 和 $ r $，并且它们要满足 $ 1 \leq l \leq r \leq n $。让 $ [a_l,a_r] $ 这个区间内的数变为原来的相反数，也就是说让 $ [a_l, a_{l + 1}, \dots, a_r] $ 变为 $ [-a_l, -a_{l + 1}, \dots, -a_r] $。

## 思路分析
该题目可以拆分为两个方面：**求最大的和**和**求最小操作次数**。

### 求最大的和
这个比较简单，我们只需要把所有的负数转化为正数后求和即可。

### 求最小操作次数
我们要保证操作后的数组中的元素都为非负数，这样才能保证数组的和最大，所以我们需要把非正数进行操作，那么我们只需看看该数组中有几个非正数子序列（把 $ 0 $ 加入其中是为了保证子序列的连续性，以保证为最优解），有几个子序列就要进行几次操作。

有一种特例要注意，如果一个子序列全为 $ 0 $ 的话取反是没有意义的，因为 $ 0 = -0 $，所以还要判断子序列是否全为 $ 0 $。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;//样例组数
int n;//长度为n的序列
int x;//每次读入的数
long long sum;//最小操作次数
long long ans;//最大的和
signed main(){
	cin>>T;
	while(T--){
		sum=0;
		ans=0;//不要忘记清空
		bool f=1;//记录上一个数的正负，0为负，1为正
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			if(x<0){//负数
				sum+=-x;//加上其相反数
				f=0;//标记
			}
			else if(x>0){//正数（可以直接不考虑0）
				if(f==0){//如果上一个数为负数
					ans++;
					f=1;//正数
				}
				sum+=x;
			}
		}
		if(f==0)ans++;//最后防止漏加最后一个为负数的子序列
		cout<<sum<<' '<<ans<<endl;
	}
	return 0;
}
```

## AC 记录
[**codeforces**](https://codeforces.com/contest/1843/submission/210714921)

[**洛谷**](https://www.luogu.com.cn/record/113154736)

**THE END.**

**THANK YOU.**


---

## 作者：rainygame (赞：0)

~~考场先过了 C 再过的 B。~~

这道题感觉可以评一个橙吧。

显然，最大和即为 $\sum\limits_{i=1}^n\lvert a_i\rvert$。因为全改成非负数一定是最好的。

然后考虑最小操作数，答案是负整数构成的连续子序列个数（注意这里 $0$ 既可以被算作正数，也可以被算作负数，甚至删掉都没有问题）。

可能有人会想到什么正数被夹在中间的情况。但是显然，正数的个数是负数 $-1$，而全部反过来也需要一次，两两抵消。

赛时代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define for1(i, s, t) for (int i(s); i<=t; ++i)
#define for2(i, t, s) for (int i(t); i>=s; --i)
#define for3(i, vec) for (auto i: vec)
#define INF 0x3f3f3f3f
#define opb pop_back
#define pb push_back
#define pf push_front
#define opf pop_front
#define fi first
#define se second
#define gc() getchar()
#define pc(x) putchar(x);
#define sp pc(' ');
#define el pc('\n');
#define Yes printf("YES");
#define No printf("NO");
#define err assert(0);
const int MAXN(2e5+1);
//const ll MOD(1e9+7);

ll re(){
	ll x(0), f(1);
	char ch;
	while ((ch = gc()) < 48) f = ch == '-' ? -1 : 1;
	do{
		x = (x << 1) + (x << 3) + (ch ^ 48);
	}while ((ch = gc()) > 47);
	return x * f;
}

void uwr(ll x){
	ll tmp(x/10);
	if (tmp) uwr(tmp);
	pc(x-(tmp<<1)-(tmp<<3)^48);
}

void wr(ll x){
	if (x < 0){
		pc('-');
		x = -x;
	}
	uwr(x);
}

int n, op;
int a[MAXN];
ll ans1, ans2;
vector<int> vec;
vector<vector<int>> b;

void solve(){
	n = re();
	ans2 = ans1 = 0;
	op = -1;
	b.clear();
	for1(i, 1, n){
		a[i] = re();
		ans1 += abs(a[i]);
		if ((abs(a[i]) == a[i]) != op && a[i]){
			b.pb(vec);
			vec.clear();
			op = abs(a[i]) == a[i];
		}
		vec.pb(a[i]);
	}
	b.pb(vec);
	vec.clear();
	
	uwr(ans1);
	sp
	for3(i, b){
		op = 0;
		for3(j, i){
			if (j){
//				wr(j);
//				el
				op = abs(j) == j ? 1 : -1;
				break;
			}
		}
//		el
		if (op == -1) ++ans2;
	}
	wr(ans2);
}

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	int t(1);
	t = re();
	while (t--){
		solve();
		el
	}

	return 0;
}

```


---

## 作者：liujy_ (赞：0)

最大值肯定是把所有数变成非负数，即取所有数的绝对值。   
最小的操作次数可以贪心，一段区间要尽可能多包含一些数字。容易证明反转的区间里面含有正数一定不会更优，如果一段操作区间包含正数，操作过后需要再一次操作把原先的正数变回来，这样不如一开始就分两次把正数左右的两段不含正数的区间操作过去。所以操作数量就等于不含正数且包含负数的极大子区间个数。   
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=2e5+5;
int t,n,a[N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);long long ans=0;int cnt=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			ans+=abs(a[i]);
		}
		a[n+1]=1;bool p=0;
		for(int i=1;i<=n+1;i++)
			if(a[i]>0)cnt+=p,p=0;
			else if(a[i]<0)p=1;
		printf("%lld %d\n",ans,cnt);
	}
	return 0;
}


```


---

