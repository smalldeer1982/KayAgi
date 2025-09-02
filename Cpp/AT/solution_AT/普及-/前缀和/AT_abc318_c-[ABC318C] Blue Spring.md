# [ABC318C] Blue Spring

## 题目描述

**题意简述**

高桥君要进行 $N$ 天的旅行，第 $i$ 天的费用为 $A_i$ 。他还可以使用优惠券，可以免除 $D$ 天的费用，价格为 $P$。如果剩余 $2$ 天，优惠券的作用是 $3$ 天，那么依然可以使用。

求这 $N$ 天旅行的最小费用。

## 说明/提示

- $1 \le N \le 2 \times 10^5$
- $1 \le D \le 2 \times 10^5$
- $1 \le P \le 10^9$
- $1 \le F_i \le 10^9$

**样例一解释**

使用一张优惠券免除 $1,3$ 天的费用，总费用为 $1+3+6+10=20$。

**样例三解释**

使用 $3$ 张优惠券，费用为 $3 \times 1000000000=3000000000$

## 样例 #1

### 输入

```
5 2 10
7 1 6 3 6```

### 输出

```
20```

## 样例 #2

### 输入

```
3 1 10
1 2 3```

### 输出

```
6```

## 样例 #3

### 输入

```
8 3 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
3000000000```

# 题解

## 作者：robertuu (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc318_c)

一道很简单的贪心题。

由于“券”可以在任何时候使用，说明每日的顺序对答案没有影响，可以先对每天的金额按照从大到小排序，之后统计每 $d$ 天的金额和，如果这 $d$ 天的金额和大于 $p$ 就用“券”，否则不用券（后面的天也肯定不用，因为已经排过序了）。

这样可以保证正确性，因为每一张“券”都满足尽量多省钱的原则，每次把最贵的 $d$ 天打包成一张“券”。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001];
int main()
{
	int n,d;
	long long p;
	scanf("%d%d%d",&n,&d,&p);
	for(int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n,greater<int>()); // 给金额排序
	long long ans = 0,cnt = 0;
	for(int i = 1;i <= n;i++)
	{
		cnt += a[i]; // 统计连续d天的金额和
		if(i % d == 0)
		{
			ans += min(cnt,p); // 券和单买取较小值
			cnt = 0;
		}
	}
	ans += min(cnt,p); // 最后不满d天的也要统计！！
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Submerge_TA (赞：4)

我们首先将数组 $F$ 从大到小排序，将其每隔 $D$ 个元素分为一段，如果每一段的所有元素的和小于或等于 $P$，就购买正常车票，也就是花费所有元素的和的价钱，否则花费 $P$ 元购买可以使用 $D$ 天的周游票。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,d,p,m,a[214514],s,st;
bool cmp(const int &x,const int &y) {
	return x>y;
}
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>d>>p;
	for(int i=0;i<n;i++) cin>>a[i];
	sort(a,a+n,cmp);
	int i=0;
	while(i<n) {
		st=0;
		for(int j=i;j<i+d&&j<n;j++) st+=a[j];
		i+=d;
		if(st<=p) s+=st;
		else s+=p; 
	}
	cout<<s;
	return 0;
}
```

---

## 作者：lrx___ (赞：3)

**题意简述**

高桥君要进行 $N$ 天的旅行。有一种优惠券，它可以抵消 $D$ 天的费用，价格为 $P$。求这 $N$ 天旅行所需要的最小花费。

**思路**

本题应使用贪心。先将所有价格从大到小排序，然后计算前缀和，计算每个长度为 $D$ 的区间的总和，如果总和小于 $P$，就使用优惠券。要注意的是，样例三中优惠券的作用是 $3$ 天，但最后两天也使用了一张。所以前缀和要再往后算 $D$ 天。

**代码**

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef unsigned long long ll;
const int N=4e5+5;
ll a[N];
/* 计算前缀和时会爆 int */
bool cmp(int x,int y){
	return x>y;
}
int main(){
	int n,d,i;
	ll s=0,p;
	scanf("%d%d%llu",&n,&d,&p);
	for(i=1;i<=n;i++){
		scanf("%llu",&a[i]);
	}
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n+d;i++){
		a[i]+=a[i-1];
	}
	/* 这里要多往后算D天的前缀和 */
	for(i=d;i-d<=n;i+=d){
		s+=min(a[i]-a[i-d],p);
		/* 对每个长度为D的区间取和与P的最小值
		需要注意的是要枚举到i-d<=n，因为不满D天也可以使用优惠券 */
	}
	printf("%llu\n",s);
	return 0;
}
```

---

## 作者：hjqhs (赞：1)

将 $F$ 数组从大到小排序。然后分段，一段最多 $D$ 个，可以分成 $\lceil \frac{N}{D} \rceil$ 段。对于每段，如果这段这和 $\ge P$ 则将和更新为 $P$。
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=b;i>=a;--i)
#define pv(i,p) for(int i=0;i<p.size();++i)
#define ptc putchar
#define il inline
#define reg register
// #define push_back pb
#define mp make_pair
#define eb emplace_back
// #define ret; return 0;
using namespace std;
const int N=200005;
const int MOD=998244353;
const int INF=0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int Max(int a,int b){return a>b?a:b;}
int MAX(int a,int b,int c){return Max(a,Max(b,c));}
int Min(int a,int b){return a<b?a:b;}
int MIN(int a,int b,int c){return Min(a,Min(b,c));}
void Swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int n,d,p,f[N],tot;
void solve(){
    cin>>n>>d>>p;
    for(int i=1;i<=n;++i)cin>>f[i],tot+=f[i];
    sort(f+1,f+1+n,[&](int x,int y){
        return x>y;
    });
    for(int i=1;i<=n/d;++i){
        int sum=0;
        for(int j=d*(i-1)+1;j<=d*i;++j){
            // cout<<j;
            sum+=f[j];
        }
        // cout<<i<<':'<<sum<<'\n';
        if(sum>=p)tot-=sum-p;
    }
    if(n%d!=0){
        int sum=0;
        for(int i=n/d*d+1;i<=n;++i){
            // cout<<i;
            sum+=f[i];
        }
        if(sum>=p)tot-=sum-p;
    }
    cout<<tot;
}
signed main(){
    // freopen(,,stdin);
    // freopen(,,stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
```

---

## 作者：Lydia1010__ (赞：1)

## 本题思路：
这道题其实很简单，我们只需要用到前缀和即可。

我们可以先把钱去从小到大排一个序，然后用一个数组去记录他的前缀和。随后我们就可以从后往前，若当前位置向前 $D$ 天钱数之和大于 $P$，那么就把这 $D$ 天用劵，否则输出当前的前缀和再加上用卷总共的钱即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200001],b[200005];
int main()
{
	long long n,d,p;
	cin>>n>>d>>p;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
	{
		b[i]=a[i]+b[i-1];
	}
	long long ans=0; 
	for(int i=n;i>=0;i-=d)
	{
		if(p<=b[i]-b[max((long long)0,i-d)]) ans++;
		else return cout<<b[i]+ans*p,0;
	}
	cout<<ans*p;
	return 0;
}

```


---

## 作者：Crazyouth (赞：0)

**翻译**

高桥要去一个 $n$ 天的旅游，第 $i$ 天的花费是 $f_i$。他也可以买一个或多个 $d$ 天的通票，在那 $d$ 天他就只需要总共花费 $p$ 元，求他旅游的最少花费。

**分析**

简单的贪心。先从大到小把 $f$ 排序，每 $d$ 天判断一次是否需要通票即可。如果那 $d$ 天的 $f_i$ 加起来比 $d$ 大，就 `ans+=d`，否则就加上那 $d$ 天 $f_i$ 的和。注意 $n$ 不一定被 $d$ 整除就行。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int f[200010];
int cmp(int a,int b)
{
	return a>b;
}
signed main()
{
	int n,d,p;
	cin>>n>>d>>p;
	for(int i=1;i<=n;i++) cin>>f[i];
	sort(f+1,f+n+1,cmp);
	int i=1,ans=0,j;
	while(i<=n)
	{
		int cost=0;
		for(j=1;j<=d&&i+j-1<=n;j++) cost+=f[i+j-1];//枚举d天，并确保不会越界
		if(cost>p) ans+=p;
		else ans+=cost;
		i+=j-1;
	}
	cout<<ans;
}

---

## 作者：so_find_skind (赞：0)

很简单的一道题。

先设 $cost$ 为最终最小花费钱数。

刚开始先 $cost=\sum^{i=1}_n a_i$。

由于我们每次可以花费 $P$ 元消耗至多 $D$ 次旅程，所以我们只需将 $n$ 次旅程排个序，然后每次找最大的 $D$ 次，设 $ans$ 为这 $D$ 次旅程之和，那么只要 $P\le ans$，我们就可以消除这 $D$ 次旅程，即 $cost\gets cost-ans+P$。

容易写出：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],d,p;
long long ans,s;
bool cmp(int a,int b){
    return a>b;
}
int main(){
    cin>>n>>d>>p;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        ans+=a[i];
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){//这里用遍历代替了一次次的删除，将这一步优化成线性
        s+=a[i];
        if(i%d==0){
            if(p<s)
                ans=ans-s+p;
            s=0;
        }
    }
    cout<<ans;
    return 0;
}
```

然后有人就傻乎乎交上去了（比如我）。

但是，实际上可以发现，这个代码过不了最后一个样例，原因是，就算只有一个旅程，你也可以消除它，所以最后，还要判断 $i$ 遍历至 $n$ 的情况，所以：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],d,p;
long long ans,s;//ans即为上文的cost
//不开long long见祖宗
bool cmp(int a,int b){
    return a>b;
}
int main(){
    cin>>n>>d>>p;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        ans+=a[i];
    }
    sort(a+1,a+1+n,cmp);//排序
    for(int i=1;i<=n;i++){
        s+=a[i];//s即为上文的ans
        if(i%d==0 || i==n){
            if(p<s)
                ans=ans-s+p;//具体见上文
            s=0;//注意这里必须清零
        }else//也可以不加，加了更好
        	break;
    }
    cout<<ans;
    return 0;
}
```

$O(n\log n)$ 快速跑过。

顺带建议将此题评橙（上位橙难度），标签排序加贪心。

---

## 作者：Sky_dreamer (赞：0)

### 题目描述
高桥要旅游 $n$ 天。对于每天，他可以使用普通票或日通卡。给定 $F_i$ 为每日普通票票价，在一开始给出 $D$ 和 $P$ 表示 $D$ 日的日通卡的价钱为 $P$ 元。  

日通卡可有剩余，求高桥这次旅行最少需要花多少钱。  

日通卡对于任意一天可以随便使用。

### 题目解法
考虑贪心。  

观察样例，可以发现日通卡比普通票便宜的情况仅在 $D$ 日的日通卡总价 $P$ 比 $D$ 日最大普通票价的和便宜的情况对答案有贡献。  

更清晰的讲，可以将题目中的 $F$ 数组按降序排序，随后从一开始比较 $i$ 至 $i+d-1$ 所有票价的和与 $D$ 日的日通卡的价钱 $P$ 取最小值对答案进行贡献。  

同时，可以对降序排序后的 $F$ 数组统计一遍前缀和，优化对 $i$ 至 $i+d-1$ 部分的求和操作。  

值得注意的是在统计到最后时要判断 $i+d-1$ 是否越界。

### 代码
时间复杂度 $O(n \log n)$。

[ACcode](https://atcoder.jp/contests/abc318/submissions/45198914)

---

## 作者：tder (赞：0)

[$\Large\color{black}\textbf{AT\_abc318\_c Blue Spring}$](https://www.luogu.com.cn/problem/AT_abc318_c) $\Large\textbf{题解}$

[$\textbf{题目传送门}$](https://www.luogu.com.cn/problem/AT_abc318_c)

[$\textbf{更好的阅读体验}$](https://www.luogu.com.cn/blog/tder/solution-AT-abc318-c)

~~排序 + 模拟~~

---

$$\large\textbf{题意}$$

给定一个长度为 $n$ 的序列 $F_1,F_2,\dotsm,F_n$，每次可以将最多 $d$ 项合并为 $p$，求合并若干次后序列中所有数字的总和的最小值。

---

$$\large\textbf{思路}$$

考虑先将 $F$ 从大到小排序，循环遍历，每次尽可能选取当前最大的 $d$ 个 $F_i$ 进行合并，对这 $d$ 项求和计为 $k$，若 $k>p$ 即合并后可以使总和减小则进行合并，否则不合并，由于排序后序列递减，后面的数字不可能比前面的数字更大，可以直接跳出循环，求后面所有项的和 $s$ 即可。计合并的次数为 $t$ 次，则最后的答案为 $t\times p+s$。  

---

$$\large\textbf{代码}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long // 注意要开 long long 防止爆 int
const int N = 2e5 + 5;
int f[N], ans; // ans 为答案
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, d, p;
	cin>>n>>d>>p;
	for(int i = 1; i <= n; i++) cin>>f[i];
	sort(f + 1, f + n + 1, greater<int>()); // 从大到小排序
	int i = 1;
	for(; i <= n; i += d) { // 每次跳过 d 个数
		int cnt = 0;
		for(int j = i; j < i + d && j <= n; j++) cnt += f[j]; // 求和
		if(cnt > p) ans += p;
		else break; // 不合并则直接跳出循环
	}
	for(; i <= n; i++) ans += f[i]; // 累加后面的项
	cout<<ans;
	return 0;
}
```

---

## 作者：Failure_Terminator (赞：0)

## Solution

贪心。

由于 $D$ 日游的日期可任意指定，因此考虑每次选取最大的 $D$ 天，判断是否买 $D$ 日游的票价格更低。

满足条件的情况下一直买 $D$ 日票，若发现单买更优，之后的天全部单独买票。

## AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int now=0,nev=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')nev=-1;c=getchar();}
	while(c>='0'&&c<='9'){now=(now<<1)+(now<<3)+(c&15);c=getchar(); }
	return now*nev;
}
void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

const int N = 2e5 + 5;
int a[N], s[N];
int n, m, p;

signed main()
{
	n = read(), m = read(), p = read();
	int ans = 0;
	for (int i = 1; i <= n; i ++)
		a[i] = read();
	sort(a + 1, a + n + 1, greater<int>());
	for (int i = 1; i <= n; i ++)
		s[i] = s[i - 1] + a[i];
	int k = 1;
	while (k <= n && s[min(k + m - 1, n)] - s[k - 1] > p)
		k += m, ans += p;
	if (k <= n) ans += s[n] - s[k - 1];
	cout << ans;
    return 0;
}
```

---

## 作者：_7Mr (赞：0)

# 翻译
高桥正在计划一次 $N$ 天的火车旅行。  

每天，他需要支付普通票价或者一日通票。

在这里，对于 $1\leq i\leq N$，第 $i$ 天的普通票价是 $F_i$ 元。一日通票的销售方式有所不同，共支付 $P$ 元可以获得 $D$ 张一日通票。您可以购买任意数量的一日通票。

每张购买的通票可在任何一天使用，旅行结束时剩下一些也没关系。

求 $N$ 天行程的最低总费用。
# 思路
我们可以先把一日通票的平均价格算出来，注意使用浮点型，防止取整后相同。然后遍历一遍数组，看有多少的普通票价是大于一日通票的，注意这里不要用大于等于，因为等于的最优选择是将一日通票留给后面大于一日通票的普通票价，然后我们就需要有这么多张一日通票，然后我们看买多少次一日通票大于等于我们需要的一日通票，然后我们将数组排序，因为可以随便买一日通票所以我们第一天就买齐，就不用担心后面的顺序问题了，然后统计一次答案，注意这时候我们还需要将购买一日通票的次数减一再次统计答案，因为这时候可能剩下一些一日通票，可能不是当前的最优答案，所以还有算一遍，最后判断特殊情况，如果其中有一个小于 $0$ 输出另外的一个就好了，如果不是就直接输出最小值。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF INT_MAX
using namespace std;
const int maxn=2e6+5;
int n,d,p,ans1,ans2;
int a[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>d>>p;
	int sum=0;
	double o=double(p)/double(d);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(double(a[i])>o) sum++;
	}
	if(sum==0){//如果没有大于一日通票的就不购买
		int ans=0;
		for(int i=1;i<=n;i++) ans+=a[i];
		cout<<ans<<endl;
		return 0;
	}
//	cout<<sum<<endl;
	sort(a+1,a+1+n);//排序
	int l=0;
	while(true){//看买多少次
		if(l*d>=sum) break;
		l++;
	}
	for(int i=n-l*d;i>=1;i--) ans1+=a[i];
	ans1+=l*p;//不减一的答案
	for(int i=n-(l-1)*d;i>=1;i--) ans2+=a[i];
	ans2+=(l-1)*p;//减一的答案
	if(ans1<0 && ans2<0) cout<<0<<endl;//判断输出
	else if(ans1<0) cout<<ans2<<endl;
	else if(ans2<0) cout<<ans1<<endl;
	else cout<<max(min(ans1,ans2),0ll)<<endl;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc318_c)

## 题目大意

有一个 $N$ 天的旅行，每天的花费是 $F_i\space (1\le i\le N)$。还有一种旅游通票，价格是 $P$，购买后可免费旅行 $D\space (1\le D\le N)$ 天。购买通票后**使用的日子不需要连续**，且可以购买多个通票。问最少花费多少钱才能完成这次旅行。

## 思路

可以用一种贪心的思想来解决此题。

读入数据后从大到小排序，贪心地找一个（或多个）区间，使得区间的总花费 $\geq$ 通票的价格。显而易见地，这就是我们要找的那些可以使用通票的日子的一部分（使用通票更实惠）。

最后计算出满足这样的区间的数量（也就是通票使用的数量）$\times$ 通票的价格，然后再加上不使用通票的日子的花费和就是最终结果。

- 数据量较大，记得开 long long。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
ll n,d,p,a[N],num,ans,pos;
int main(){
	cin>>n>>d>>p;
	for(int i=1;i<=n;++i)scanf("%lld",a+i);
	sort(a+1,a+1+n,greater<ll>());
	for(int i=1;i<=n;++i){
		ll sum=0,j;
		bool flag=0;
		for(j=i;j<=i+d-1&&j<=n;++j){//找到一个满足条件的区间。
			sum+=a[j];//求区间内的花费和。
			if(sum>=p){
				pos=j;
           //记录使用通票的最后的位置，后面的日子使用通票就不实惠了。
				flag=1;//标记此区间满足要求。
			}
		}
		i=j-1;//避免重复计算。
		if(flag)num++;//使用通票的数量 +1。
	}
	for(int i=pos+1;i<=n;++i)ans+=a[i];
	cout<<ans+num*p;
	return 0;
}
```

[已 AC](https://www.luogu.com.cn/record/123641897)

---

## 作者：KeatonBinary (赞：0)

# Solution?
这题可以贪心解决。先将每天的价格排序，再从最大的价格开始，检查 $D$ 天的价格之和是否超过 $P$，若是则可以为这些天购买通票。
# Code！
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
const int N = 3e5 + 5;
int n, d, p, f[N];
ll s[N], ans;

int main() {
  cin >> n >> d >> p;
  for (int i = 1; i <= n; ++i) cin >> f[i], ans += f[i];
  sort(f + 1, f + n + 1);
  for (int i = 1; i <= n; ++i) s[i] = f[i] + s[i - 1];
  for (int i = n; i > 0; i -= d) {
    ll now = s[i] - s[max(i - d, 0)];
    if (now > p) ans -= now - p;
    else break;
  }
  cout << ans << endl;
  return 0;
}
```

---

## 作者：ldj2006 (赞：0)

# [ABC318C] Blue Spring 题解

## 题意简述

&emsp;&emsp;主人公出去旅游要买票，共有若干天，每天要花不同钱。现在有“通行证”出售，通过购买通行证，可以在某一天直接用通行证，以此来省去当天原本需要花费的票价。通行证只能一套一套买，每套中有 $D$ 个，买一套要花费 $P$ 元。可以购买任意套数的通行证，求怎样最省钱。

## 解题思路

&emsp;&emsp;首先发现天和天之间独立，可以排序，排序不影响买票总价的性质。于是我们将原序列从小到大排序，方便处理。

&emsp;&emsp;我们将一套通行证中，每张通行证的平均单价计算出来，即 $\frac{P}{D}$（注意可能不是整数），然后我们发现，假如说一套中只有一张通行证，那么显然，只要某天票价高于通行证，就购买通行证。

&emsp;&emsp;假如有一套中有多于一张通行证，我们考虑贪心地按每天花费大到小，进行比较来购买通行证。如果当前买通行证单价比要替换掉的天数的花费全都低，那么显然是优的。而如果买的太多了，当前买通行证单价比要替换掉的天数的花费全都高，那么还不如不买这个通行证。

&emsp;&emsp;综上，我们统计出所有花费高于通行证单价的日期数量 $m$，只需要计算购买 $\lfloor \frac{m}{D} \rfloor$ 套通行证和购买 $\lceil \frac{m}{D} \rceil$ 套通行证后，总花费的最小情况就行。为什么不多买或者少买在上一段说过了。

## 代码

注意特判如果 $\lceil \frac{m}{D} \rceil$ 超过了 $n$（总天数）的情况。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 2e5 + 5;

LL n,d,p;
LL a[N],s[N];
double b[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> d >> p;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
	}
	sort(a+1,a+1+n);
	for(int i = 1;i <= n;i++)
	{
		s[i] = s[i-1] + a[i];
		b[i] = a[i];
	}
	LL idx = lower_bound(b+1,b+1+n,(double)p/(double)d) - b;
	LL tmp = (n - idx + 1)/d;
	LL ans = s[n-tmp*d+1-1] + tmp*p;
	if(n-(tmp+1)*d+1-1 < 1)
		ans = min(ans,(tmp+1)*p);
	else
		ans = min(ans,s[n-(tmp+1)*d+1-1]+(tmp+1)*p);
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：DerrickLo (赞：0)

先把 $F$ 从大到小排序，然后把每连续 $d$ 个的和判断是否大于 $p$，如果大于 $p$ 那么就将这 $d$ 个合在一起买，否则就单独买。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,d,p,f[400005],sum[400005],ans,pos;
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	cin>>n>>d>>p;
	for(int i=1;i<=n;i++)cin>>f[i];
	sort(f+1,f+n+1,cmp);
	for(int i=1;i<=n+d;i++)sum[i]=sum[i-1]+f[i];
	for(int i=1;i<=n;i++){
		if(sum[min(n,i+(d-1))]-sum[i-1]>p){
			if(i+d-1<=n)i=i+d-1;
			else i=n;
			ans+=p;
		}
		else ans+=f[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：flysfy_LJX (赞：0)

### 题意：
高桥计划进行为期 $n$ 天的旅行。
对于每一天，他可以支付常规票价或使用一日通行证，$d$ 个一日通行证售价为 $p$ 日元，但只能以 $d$ 的倍数购买，使用后无需支付常规票价。

每张购买的通行证可以在任何一天使用，最后剩下没使用的作废。找到 $n$ 天旅行的最小可能总费用。
### 思路：
先把每天常规票价倒序排序，再从低到高比较购买一日票和普通支付的价格，如果常规票价比购买一日票支付的价格更少，则输出即可。

注意：数据较大，记得开 `long long`。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,d,p,a[202020],sum;
int main()
{
	cin >> n >> d >> p;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		sum+=a[i];
	}
	sort(a+1,a+n+1);//正序排序
	reverse(a+1,a+n+1);//反转函数，将数组变为倒序
	for(int x=1;;x++)//枚举购买数量
	{
		long long cnt=sum+p;
		for(int i=1+((x-1)*d);i<=min(n,(x*d));i++)//为节省时间，区间枚举即可
			cnt-=a[i];
		if(cnt>=sum) return cout << sum,0;
		else sum=cnt;
	}
	return 0;
}

```


---

