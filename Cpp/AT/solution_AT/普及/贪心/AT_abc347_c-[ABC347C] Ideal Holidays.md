# [ABC347C] Ideal Holidays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc347/tasks/abc347_c

AtCoder 王国の $ 1 $ 週間は $ A+B $ 日からなり、$ 1 $ 日目から $ A $ 日目が休日で、$ A+1 $ 日目から $ A+B $ 日目が平日です。

高橋くんは $ N $ 個の予定があり、$ i $ 番目の予定は今日から $ D_i $ 日後です。

高橋くんは今日が $ 1 $ 週間の何日目かを忘れてしまいました。高橋くんの $ N $ 個の予定が全て休日である可能性があるかを判定してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A,B\leq\ 10^9 $
- $ 1\leq\ D_1\ <\ D_2\ <\ \ldots\ <\ D_N\leq\ 10^9 $
 
### Sample Explanation 1

入力では $ 1 $ 週間は $ 7 $ 日からなり、$ 1 $ 日目から $ 2 $ 日目が休日、$ 3 $ 日目から $ 7 $ 日目が平日です。 今日が $ 1 $ 週間の $ 7 $ 日目だとします。このとき、$ 1 $ 日後は $ 1 $ 週間の $ 1 $ 日目、$ 2 $ 日後は $ 1 $ 週間の $ 2 $ 日目、$ 9 $ 日後は $ 1 $ 週間の $ 2 $ 日目となり、全ての予定が休日となります。そのため、高橋くんの $ N $ 個の予定が全て休日である可能性があります。

## 样例 #1

### 输入

```
3 2 5
1 2 9```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 5 10
10 15```

### 输出

```
No```

## 样例 #3

### 输入

```
4 347 347
347 700 705 710```

### 输出

```
Yes```

# 题解

## 作者：MinimumSpanningTree (赞：15)

[原题链接](https://www.luogu.com.cn/problem/AT_abc347_c)

由于 $d$ 是固定的，考虑移动序列 $d$，判断是否能恰好嵌入到假期里面。

所以把 $d_1$ 放在假期的第一天，那么我们现在可以向右移动 $A-1$ 天。

一周可以表示为 `a a b b b b a a`。（`a` 表示假期，`b` 表示工作日）

接下来分类讨论输出 `Yes` 的情况：

* 全部在前面的 `a`。

* 部分在前面的 `a`，部分在后面的 `a`。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+100;
int n,a,b,d[N];
bool flag;
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&d[i]);
		d[i]%=a+b;
		if(!d[i]) d[i]=a+b;
	}
	sort(d+1,d+n+1);
	if(d[n]-d[1]+1<=a) flag=true;
	for(int i=2;i<=n;i++)
	{
		if(d[i]-d[i-1]>b&&d[i-1]<=a) flag=true;
	}
	flag?printf("Yes"):printf("No");
	return 0;
} 
```

---

## 作者：XXh0919 (赞：10)

这次只是修正一个不合理的地方，请管理员过一下吧，谢谢。

比较简单的一道题。

### 题意

一周有 $A+B$ 天，从 $1$ 到 $A$ 天是假期，第 $A+1$ 天到 $A+B$ 天是工作日。有 $N$ 个计划将在 $D_1,D_2,D_3...D_N$ 天后进行，若所有计划都能在假期进行，输出 $\texttt{Yes}$，否则输出 $\texttt{No}$。

### 解法

根据第一个样例的提示，首先肯定是要把输入的数先模上一个 $A+B$ 的，接着我们把结果从小到大排序并用最后的元素减去第一个元素，若减出的结果是在 $A$ 以内那么就输出 $\texttt{Yes}$，否则输出 $\texttt{No}$。

如果你真是这样做的，那么恭喜你，你会 WA 一个点。请看如下样例：

```cpp
2 3 4 
6 8
```
这个样例按照上面的方法会输出 $\texttt{No}$，但是正确结果是 $\texttt{Yes}$（这里我不说为什么，请自行手推）。所以我们需要再次遍历一遍数组，看相邻两个数之间的差是否小于 $A$，就输出 $\texttt{Yes}$，否则输出 $\texttt{No}$。

### AC Code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=4e6+15;

int n,a,b;
int d[N];

void solve(){
	cin>>n>>a>>b;
	int sum=a+b;
	rep(i,1,n)cin>>d[i],d[i]%=sum;
	sort(d+1,d+n+1);
	if(d[n]-d[1]<a){
		cout<<"Yes"<<endl;
		return ;
	}
	rep(i,1,n){
		int last=d[i-1];
		last+=a+b;
		if(last-d[i]<a){
			cout<<"Yes"<<endl;
			return ;
		}
	}
	cout<<"No"<<endl;
}

signed main(){
	int T=1;
//	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：joe_zxq (赞：7)

# 思路

首先，我们将每一个 $D_i$ 对每星期的天数，即 $(A+B)$ 取模。

将取模后的天数从小到大排序，遍历寻找是否存在有两天之间把工作日空开了，即两者之差超过 $B$。若存在，则每一天都可以安排在休息日，答案为 `Yes`；否则，答案为 `No`。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, m, a[200005];
signed main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= (m + k);
    }
    sort(a + 1, a + n + 1);
    a[n + 1] = a[1] + m + k;
    for (int i = 1; i <= n; i++)
        if (a[i + 1] - a[i] > k)
            cout << "Yes", exit(0);
    cout << "No";
}
```

---

## 作者：_Yonder_ (赞：5)

很明显，如果这题我们枚举今天是星期几必然会超时，但如果我们更改一下题意这题就很简单了：今天是星期一，放假是从星期 $x$ 开始的，求是否有一个 $x$ 使得每个 $d_i$ 天后是假期。

根据贪心，$x$ 一定是其中一个 $d_i$ 天后所在的星期，所以枚举 $d_i$ 即可。
# Code
```
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define per(i,l,r) for(int i=l;i>=r;i--)
#define ll long long
using namespace std;
template<typename P>inline void read(P&x){bool f=0;x=0;char c=getchar();while(!isdigit(c)) f|=c=='-',c=getchar();while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();x=f?~(x-1):x;}
template<typename P>inline void write(P x){if(x<0) putchar('-'),x=-x;if(x>9) write(x/10);putchar((x%10)^48);}
const int N=2e5+5;
int n,a,b,d[N],Min=1e9,Max=-1e9;
int C(int x){return x%(a+b);}
int main(){
	read(n),read(a),read(b);
	rep(i,1,n) read(d[i]);
	rep(i,1,n){
		Min=min(Min,C(d[i]));
		Max=max(Max,C(d[i]));
		d[i]=C(d[i]);
	}sort(d+1,d+1+n);d[0]=-1;
	int ans=Max-Min+1;
	rep(i,1,n-1) ans=min(ans,d[i]+1+a+b-d[i+1]);
	if(ans>a) cout<<"No";
	else cout<<"Yes";
	return 0;
}
```

---

## 作者：FinderHT (赞：3)

### 题面描述

某王国一周由 $A+B$ 天组成，其中第一天至 $A$ 天为节假日，而 $(A+1)$ 至 $(A+B)$ 天为工作日。目前有 $N$ 个计划，第 $i$ 个计划在 $D_i$ 天后，不知道今天是星期几，问所有计划是否都在节假日。

### 思路

一个假了一半的思路是把每个 $D$ 对 $A+B$ 取余后记录最大值和最小值，然后判断他们的差是否小于 $a$，但这样会 WA $\times 1$。

我们可以把所有 $D_i$ 对 $A+B$ 取余后用数组 $E$ 储存，然后排序。当存在 $E_{i+1}-E_{i}>b$ 或者有 $E_n-E_1<a$ 时，答案为 `Yes`，否则为 `No`。容易证明我们总能找到一天作为开始时间而使所有计划时间都在节假日。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
int e[MAXN];
signed main(){
	int n,a,b;
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		int d;
		cin>>d;
		e[i]=d%(a+b);//计算得到e数组
	}
	sort(e+1,e+n+1);//排序
    if(e[n]-e[1]<a){
		cout<<"Yes";
		return 0;
	}
	for(int i=1;i<n;i++){
		if(e[i+1]-e[i]>b){
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";//如果两种为Yes的情况都不满足，输出No
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：2)

# AT_abc347_c [ABC347C] Ideal Holidays 题解

纪念一下这题我交了 $15$ 发才 AC。

[My Submissions](https://atcoder.jp/contests/abc347/submissions?f.Task=abc347_c&f.LanguageName=&f.Status=&f.User=PCT2506)|[AC record](https://atcoder.jp/contests/abc347/submissions/51850747)。

### 翻译

一周有 $a+b$ 天，前 $a$ 天是假期，后 $b$ 天是工作日，有 $n$ 个安排，它们在 $d_1,d_2,\ldots,d_n$ 天后进行，问它们是否都能在假期进行。

### 解析

不用管什么“前几天”、“后几天”，只需要判断所有安排是否在连续的 $a$ 天内进行。

于是写出代码：

```cpp
for(int i=1;i<=n;i++){
	cin>>d[i];
	d[i]%=(a+b);
}
sort(d+1,d+n+1);
if(d[n]-d[1]<a){
	cout<<"Yes";
}
else{
   cout<<"No";
}
```

于是我们喜提 WA*1。

思考如下数据：

```
2 5 10
11 15
```

对于第 $15$ 天，它会被自动转化为第 $15\bmod 15=0$ 天，于是天数差就是 $11-0=11>5$，而实际的天数差应该是 $15-11=4<5$，那怎么办呢？

想到把数组排序，去重然后复制一倍，令去重后的长度是 $l$，数据变为 $x_1,x_2,\ldots,x_l$，则复制后变为 $x_1,x_2,\ldots,x_{l-1},x_l,x_{l+1},\ldots,x_{2l-1},x_{2l}$。此时我们只需要检验对于 $\forall 1\leq i\leq l$，是否满足 $x_{x+l-1}-x_i<a$ 即可，若满足输出 `Yes`，若都不满足输出 `No`。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5,LOGN=19;
int n,a,b;
int d[N];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		d[i]%=(a+b);
	}
	sort(d+1,d+n+1);
	int len=unique(d+1,d+n+1)-d-1;
	for(int i=len+1;i<=2*len;i++){
		d[i]=d[i-len]+a+b; 
	}
	for(int i=1;i<=len;i++){
		if(d[i+len-1]-d[i]<a){
			cout<<"Yes"; return 0;
		}
	}
	cout<<"No";
return 0;
}
```

---

## 作者：cqbzcjh (赞：1)

## 分析
1. 我们把所有 $D_i$ 都模上 $A+B$，将所有天数压缩在一周内，因为不管过了多少周星期几都是一样的。
1. 把模后的数据从小到大排序，方便处理它们的差。
1. 特判一下 $D_n - D_1$ 小于 $A$ 的情况。这种情况所有天数都刚好在假期之间，直接输出 `Yes`。
1. 循环判断 $d_{i+1} - d_i$ 是否大于 $B$。如果是，说明其他数据可以保持在假期内，而差大于 $B$ 的这组数据则可以直接跳过中间的工作日，直接输出 `Yes`。
1. 如果以上条件一个都不满足，最后输出 `No`。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a,b,d[N];
int main(){
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);cout.tie(NULL);
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		d[i]%=(a+b);
	}
	sort(d+1,d+1+n);
	if(d[n]-d[1]<a){
		cout<<"Yes";
		return 0;
	}
	for(int i=1;i<n;i++){
		if(d[i+1]-d[i]>b){
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
首先将每个 $d_i$ 变成 $d_i\bmod(a+b)$，然后排序，破环成链，$d_{i+n}=d_i+a+b$，枚举每个 $i=1\sim n$，判断 $d_i\sim d_{i+n-1}$ 相隔距离是否在 $a$ 天内。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, a, b, x[400005], s;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> a >> b;
	s = a + b;
	for (int i = 0; i < n; ++ i)
		cin >> x[i], x[i] %= s;
	sort (x, x + n);
	for (int i = 0; i < n; ++ i)
		if (x[i + n - 1] - x[i] < a) {
			cout << "Yes";
			return 0;
		} else
			x[i + n] = x[i] + s;
	cout << "No";
	return 0;
}
```

---

## 作者：Ivan422 (赞：1)

题目大意：定义一周前 $A$ 天休息，后 $B$ 天休息，给定 $n$ 天的计划，求这些计划的时间是否可能全部是休息日，注意第一天不一定是本周的第一天。

注意：要注意的是我们并不知道开始星期几。

我们发现不管星期几，只要任意计划在一周的位置相等，有一个计划在休息日那么其他所有的计划都会在一周内。而虽然 $A$ 和 $B$ 都非常大，但是 $n$ 在可接受范围内，也就是说模数的数量同时小于 $A+B$ 和 $n$。那么得出第一步先用一个 `map` 记录余数。

这个时候我们就得出了一周内的计划表，对计划日期计算出最大值 $mx$ 和最小值 $mn$，可以求出时间区间大小 $mx-mn+1$。当这个区间大小 $\leq A$ 时，即可以把区间完整移动到休息日，就找到了答案。

但是还有一种情况：区间空隙不在头尾，在中间。这种也不难，在上一种情况没有找到答案时检查每 $2$ 天之间的时间差，只要这个时间差超过了 $B$，即可以把区间完整移出休息日，也找到了答案。

当两端或中间的时间空隙都找不到结果时，输出没有就可以了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=2e5+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,a,b,d[N],dd[N],cur,mx,mn;
map<int,bool>mp;
signed main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        cin>>d[i];
        mp[d[i]%(a+b)]=1;
    }
    mn=1e18;
    for(auto v:mp){
        mx=max(mx,v.first);
        mn=min(mn,v.first);
        dd[++cur]=v.first;
    }
    if(mx-mn+1<=a)cout<<"Yes";
    else{
        for(int i=2;i<=cur;i++){
            if(dd[i]-dd[i-1]>b){cout<<"Yes";return 0;}
        }
        cout<<"No";
    }
    return 0;
}
```

---

## 作者：Vocaloid世末歌者 (赞：1)

最开始的思路爆炸了我就不写了。

先 `d[i]%=(a+b)`。

然后，排序，破环为链，相当于存储了下一周。

再然后，从 $1$ 到 $n$ 进行一个循环，若 `d[i+n-1]-d[i]+1<=a` 就输出 `Yes`。

它的原理是什么？

翻译一下上面那个语句，就是“我前一个任务的日期的下一周距离我这个任务的日期小于等于节假日天数”。

那你直接把这个任务放在一周的第一天，其他不就好了！

有人会觉得后面的万一飞到工作日去了的话，会错，但是别忘了我们一周整整 `a+b` 天，破环为链的时候会加一周的天数，而且我们最初 `d[i]%=(a+b)` 了，一定是不可能飞到工作日去的。

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
#define N 1000010
#define MOD 998244353
#define esp 1e-8
#define INF 999999999999999999
#define LL long long
#define rep(i,a,b,g) for(LL i=a;i<=b;i+=g)
#define rem(i,a,b,g) for(LL i=a;i>=b;i-=g)
#define repn(i,a,b,g) for(LL i=a;i<b;i+=g)
#define remn(i,a,b,g) for(LL i=a;i>b;i-=g)
#define pll pair<LL,LL>
#define mkp(x,y) make_pair(x,y)
#define i128 __int128
#define lowbit(x) ((x)&(-(x)))
#define lc (u<<1)
#define rc (u<<1|1)
using namespace std;
void read(i128 &x)
{
	i128 f=1;
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
void writing(i128 x)
{
	if(x>=10)writing(x/10);
	putchar(x%10+'0');
}
void write(i128 x)
{
	if(x<0)
	{
		cout<<'-';
		x=-x;
	}
	writing(x);
}
LL n,a,b,d[400010];
bool f;
int main()
{
	cin>>n>>a>>b;
	rep(i,1,n,1)
	{
		cin>>d[i];
		d[i]%=(a+b);
	}
	sort(d+1,d+n+1);
	rep(i,1,n,1)
	{
		d[i+n]=d[i]+a+b;
	}
	rep(i,1,n,1)
	{
		if(d[i+n-1]-d[i]+1<=a)
		{
			cout<<"Yes"<<endl;
			return 0;
		}
	}
	cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc347_c)

## 思路

读入数据后将每个日子通过对一周中的总天数 $A+B$ 取模的形式，转化为这个日子在一周里会是哪一天。之后将这些日期从小到大排序。

- 如果最大的日期 $-$ 最小的日期 $+1\le A$，那么说明这些日期可以被安排在一个周末，输出 ``Yes``。

- 否则再次循环，如果发现有两个日期之差大于 $B$，那么说明这些日期**一定**可以被分成多个周末来办（即两边周末都有日期，中间的工作日空着的形式），输出 ``Yes``。

- 如果分类讨论完后还不行，输出 ``No``。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a,b,d[N];
signed main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;++i){
        cin>>d[i];
        d[i]%=a+b;
    }
	sort(d+1,d+1+n);
	if(d[n]-d[1]+1<=a){
		puts("Yes");
		return 0;
	}
	for(int i=2;i<=n;++i){
		if(d[i]-d[i-1]>b){
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/153614563)

---

## 作者：_QyGyQ_ (赞：0)

对于这道题，我们不知道今天是星期几，所以我们先找到安排的事情中在一周中最靠前的和一周中最靠后的，相减加一就是安排的事情的长度。如果小于放假日的天数，就可以直接输出 `Yes` 否则，就把数组排序，判断相邻两件事情相隔的日子是否大于等于工作日天数，如果是，那么就可以分开放假。也就是说可以先放几天，然后再上班，接着放假。所以只要出现有相邻两件事情相隔的日子是否大于等于工作日天数，就可以输出 `Yes`。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
const int N=1e6+7;
int d[N];
signed main(){
	int n,a,b;
	cin>>n>>a>>b;
	int days=a+b;
	int ma=-1,mi=1e11;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		int x=(d[i])%days;
		d[i]%=days;
		ma=max(ma,x);
		mi=min(mi,x);
	}
	int len=abs(ma-mi)+1;
	if(len<=a){
		puts("Yes");
		return 0;
	}
	sort(d+1,d+n+1);
	for(int i=1;i<n;i++){
		if(b<=(d[i+1]-d[i])-1){
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0;
}
```

---

## 作者：Dream_poetry (赞：0)

### 翻译：
一个周期前 $a$ 天是假期，后 $b$ 天是工作日。

高桥有 $n$ 个计划，每个计划在 $d_i$ 天后实行。

若今天可能是任何一天，是否可能所有计划都在假期内实行。

### 思路：
先把日期处理一下，令 $d_1=1$，其后类推。

假如两个相邻假期间隔 $b$ 天之内，那它们显然要在同一个周期之内。

据此，可以假设我们把这 $n$ 个假期分割成 $k$ 段，每一段的开头和结尾的差必须在 $a$ 之内，否则输出 ```No``` 即可。

若始终满足要求，输出 ```Yes``` 即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a,b;
int d[500005];

int p,o=1;

signed main(){
	cin>>n>>a>>b;
	int w;
	for (int i=1;i<=n;i++){
		cin>>d[i];
		if (i==1) w=d[i];
		d[i]=d[i]-w+1;
	}	
	for (int i=1;i<=n;i++){
		if (d[i]-d[i-1]<=b){
			p=i;
		}
		else{
			if (d[p]-d[o]>=a){
				cout<<"No";
				return 0;
			}
			o=i;
			p=i;
		}
	}
	if (d[p]-d[o]>=a){
		cout<<"No";
		return 0;
	}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：yegengghost (赞：0)

看到题面，首先想要对每个数取余，便于计算。

但是您怎么确定每天都在节假日捏？

对所有数据排序后，看下它们之间的差（即每个任务之间的天数）是否大于工作日天数。

当然，提前检查最后一个元素与第一个元素的差是否比节假日天数小也未尝不可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int d[N];
int n,a,b;
int read()
{
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
signed main()
{
	n=read(),a=read(),b=read();
	for(int i=1;i<=n;i++)
	{
		d[i]=read();
		d[i]%=(a+b);
	}
	sort(d+1,d+n+1);
	if(d[n]-d[1]<a)
	{
		cout<<"Yes"<<'\n';
		return 0;
	}
	for(int i=1;i<n;i++)
		if(d[i+1]-d[i]-1>=b)
		{
			cout<<"Yes"<<'\n';
			return 0;
		}
	cout<<"No"<<'\n';
	return 0;
}
```
赛时交了十多次才过的。

---

## 作者：Hughpig (赞：0)

先把所有的 $D_i$ 对 $a+b$ 取模，把所有日期缩到一周内。

然后把所有日期排序，再断环为链，统计起始日期和最后一个日期之间所间隔的日期数是否小于等于 $a$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,d[200007],x[400007],l=1,r;

int main()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;++i)cin>>d[i],d[i]%=(a+b);
	sort(d+1,d+n+1);
	for(r=1;r<=n;++r)x[r]=d[r];
	--r;
	while(l<=n){
		if(x[r]-x[l]+1<=a)cout<<"Yes\n",exit(0);
		x[++r]=x[l++]+a+b;
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：_KHIN (赞：0)

### 题意简述

一周的第 $1$ 天到第 $A$ 天为休息日，第 $A+1$ 天到第 $B$ 天为工作日。一共有 $N$ 个计划，第 $i$ 个计划在 $d_i$ 天后，请问能否通过选择今天是星期几，使得这些计划都在休息日。

### 解题思路

对于每一个 $d_i$，我们求出它在一周中的哪一天，并将结果存进一个 vector 数组 $t$ 里面，紧接着对 $t$ 排序。

如果 $t$ 中最大的数减去 $t$ 中最小的数所得的差比 $A$ 小，那么显然有解。否则，我们枚举整个 $t$，如果有一个 $t_i-t_{i-1}> B$，那么意味着我们可以跳过工作时间，显然有解，否则无解。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int> t;
int n,a,b,d[400005];
signed main()
{
 	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
	{
		cin>>d[i];
		t.push_back((d[i]-1)%(a+b)+1);
	}
	sort(t.begin(),t.end());
	if(t.back()-t[0]<a)
	{
		cout<<"Yes"<<endl;
	}
	else
	{
		for(int i=1;i<t.size();i++)
		{
			if(t[i]-t[i-1]>b)
			{
				cout<<"Yes"<<endl;
			}
		}
		cout<<"No"<<endl;
	}
    return 0;
}
```

---

## 作者：DHT666 (赞：0)

## 题意
[传送门](https://www.luogu.com.cn/problem/AT_abc347_c)

## 思路
因为周期数不影响，故先对 $A+B$ 取余，然后排升序。

然后我们就遍历，因为今天是星期几不确定，所以只要有 $i$ 满足 $D_{i + 1}-D_i>B$，那么就可以把 $D_i$ 定为周一，从而使得所有计划在节假日。

需要注意的是，$D_{n+1}$ 也需要判断，可将它设为 $D_i+A+B$，即下一周的第一天。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10; 

int n,a,b;
int d[N];

signed main() {
    cin >> n >> a >> b;
    
    for(int i = 1;i <= n;i++) {
    	cin >> d[i];
    	d[i] %= a + b;
    }
	
	sort(d + 1,d + 1 + n);
	
	d[n + 1] = d[1] + a + b; // 新的一周
	
	for(int i = 1;i <= n;i++) {
    	if(d[i + 1] - d[i] > b) { // 如上
    		cout << "Yes";
    		return 0;
		}
	}
	
	cout << "No"; // 不满足
    
    return 0;
}
```

---

## 作者：2huk (赞：0)

- 一周有 $a + b$ 天，其中前 $a$ 天为假日，后 $b$ 天为工作日。

  接下来会有 $n$ 件事情，第 $i$ 将事情在接下来的第 $d_i$ 天发生。当前是第 $1$ 天。

  你不知道今天是星期几。问是否有可能这 $n$ 件事情都在假日里发生。

- $n \le 2 \times 10^5$，$1 \le a, b \le 10^9$，$1 \le d_1 < d_2 < \dots < d_n \le 10^9$。

假设当前是星期 $x$，也就是一个星期中的第 $x$ 天。那么「所有事情都在假日发生」就可以转化为「所有 $i \in [1, n]$ 都满足 $(d_i + x) \bmod (a + b) < a$」。

最朴素的想法就是让除以 $a + b$ 余数最小的一天成为一个星期的第一天，然后计算出今天是星期 $x$，再判断是否对于所有事情都满足。

但是这样做会 WA*1。解决方法是如果按照上面方法得不到一个解，就随机某天 $i$ 并让第 $d_i$ 天成为这个星期的第一天。处理方法与上面类似。

时间复杂度 $\Theta(nv)$，其中 $v$ 是随机次数。这里取 $v = 50$。

```cpp
int n, a, b, d[N];

bool chk(int p) {
	p %= a + b;
	int t = a + b - p;
	if (!p) t = 0;
	for (int i = 1; i <= n; ++ i )
		if ((d[i] + t) % (a + b) >= a)
			return false;
	return true;
}

void Luogu_UID_748509() {
	fin >> n >> a >> b;
	for (int i = 1; i <= n; ++ i ) {
		fin >> d[i];
		d[i] %= a + b;
	}
	sort(d + 1, d + n + 1);
	bool flg = chk(d[1]);
	for (int i = 1; i <= 50 && !flg; ++ i )
		flg |= chk(d[rand() % n + 1]);
	puts(flg ? "Yes" : "No");
}
```

---

## 作者：MicroSun (赞：0)

恶心题。

可以将所有日期对 $a+b$ 取模并排序，将其放入同一个星期可以更方便计算。

因为要使所有日期都包含在一个区间里，这些日期里面的最小值放在区间的起点一定不劣。

于是考虑枚举每一个日期作为区间的起点的情况，假设当前考虑的是日期 $a_i$，那么显然这时所有日期距离区间起始点最远的一定是 $a_{i-1}$。

于是作差即可。

注意几个细节：

1. 由于星期 $a+b$ 的下一天是星期 $1$，所以在作差的时候要减一（以 $a_1$ 为起点时因为没有跨周，所以不用减 $1$）。

1. 注意负数取模。

Code:

```cpp
// Problem: C - Ideal Holidays
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int maxn=2e5+10;

ll d[maxn];
ll mod(ll a,ll mod1){
	ll x=a%mod1;
	if(x<0) x+=mod1;
	return x;
}
void solve(){
	ll n,a,b;
	cin>>n>>a>>b;
	rep(i,1,n) cin>>d[i];
	rep(i,1,n){
		d[i]%=(a+b);
		if(d[i]==0) ++d[i];
	}
	sort(d+1,d+1+n);
	if(d[n]-d[1]<a){
		cout<<"Yes"<<endl;
		return;
	}
	ll x1=a+b;
	rep(i,2,n){
		if(mod(d[i-1]-d[i]-1,x1)<a){
			cout<<"Yes"<<endl;
			return;
		}
	}
	cout<<"No"<<endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	//cin>>t;
	while(t--) solve();
    return 0;
}

```

---

## 作者：_Weslie_ (赞：0)

抽象题。

### 思路

显然如果这些天在这么多周里肯定不行，把 $D$ 序列中的每一个元素都对 $a+b$ 取模。但是，如果出现 $0$，把它改成 $a+b$。（好像不改也行？）

显然取完模后原序列不一定再有序了，所以排序，同时去重（方便计算）。设操作后的序列为 $g$。

接着，我们枚举 $i$，则 $g_i$ 天为该星期的第一天。那么 $g_{i-1}$ 天就是离 $i$ 最远的一天，只需算一下差值是否小于 $a$ 即可。

**细节：**

- 可能 $g_1$ 天是第一天，$g_{cnt}$ 天为最后一天。（$cnt$ 为去重后元素的个数）
- 差值一定要加 $1$，这样才是天数。有点像植树问题。

### 代码实现
```
#include<bits/stdc++.h>
using namespace std;
map<int,int>mp;
int n,cnt;
int f[200005],g[200005],a,b;
int main() {
	cin>>n>>a>>b;
	for(int i=1; i<=n; i++) {
		cin>>f[i];
		f[i]=f[i]%(a+b);
		if(f[i]==0)f[i]=a+b;
		mp[f[i]]++;
		if(mp[f[i]]==1)g[++cnt]=f[i];
	}
	sort(g+1,g+cnt+1);
	//1 9 10 11 1+a+b
	//cout<<g[2]<<' '<<g[cnt+1]<<endl;
	if((g[cnt]-g[1]+1)<=a){
		cout<<"Yes"<<endl;
		return 0;
	}
	else{
		for(int i=2; i<=cnt; i++) {
			if((g[i-1]+a+b-g[i]+1)<=a){
				cout<<"Yes"<<endl;
				return 0;
			}
		}
	}	
	cout<<"No"<<endl;
	return 0;
}
```

### 只错 $1$ 个点怎么办？

只错 $1$ 个点大概率是把 $g_{cnt}$ 默认算为最后一天了。

对于这组样例：

```
2 3 12
1 14
```

可以以第 $14$ 天为第一天，这样第 $1$ 天就是休息日的最后一天，是可以的。

---

## 作者：fuxiheng (赞：0)

### 题意
给你 $n$ 个计划，每个计划将会在 $D_i$ 天后进行。其中每一周的前 $A$ 天是周末，后 $B$ 天是工作日。求是否存在一天使得每一个计划都在周末执行。
### 分析
显然，将他们放在同一周的时候，极差一定在小于 $A$ 的时候合法。所以每一个计划我们先对 $A+B$ 取模，排序，去重。此时，我们尝试枚举每一个余数将其作为最大值，将它加上 $A+B$ 后与下一个余数相减，如果有一个差小于 $A$ 就是合法的。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 200005;
	int d[MAXN];
	int main(){
		int n, a, b;
		scanf("%d%d%d", &n, &a, &b);
		for(int i = 1;i <= n;i++){
			scanf("%d", &d[i]);
			d[i] %= (a + b);
		}
		sort(d + 1, d + n + 1);
		n = unique(d + 1, d + n + 1) - d - 1;
		if(d[n] - d[1] < a){
			printf("Yes");
			return 0;
		}
		for(int i = 1;i < n;i++){
			if(d[i] + a + b - d[i + 1] < a){
				printf("Yes");
				return 0;
			}
		}
		printf("No");
		return 0;
	}
} 
signed main(){
	return Luo_ty::main();
}
```

---

## 作者：Double_Light (赞：0)

因为一共有 $(A+B)$ 天，所以考虑将输入的数对 $(A+B)$ 取模，对应的星期几不会改变。

因为所有天都在一个周中，如果星期数最大的那一天在假期中，星期数最小的也在假期，那么所有的天都在假期当中。

但是思考一下，发现有时跨一个周的情况反而可能都安排在假期，反例可以看 XXh0919 的题解。这时遍历数组，让 $D_i+a+b-D_{i+1}$ 与 $a$ 比较。

最终代码如下：

```cpp
#include<iostream>
#include<algorithm>
#define int long long 
using namespace std;
int n,x,y,a[200005];
bool ans;
signed main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]%=x+y;
	}
	sort(a+1,a+n+1);
	if(a[n]-a[1]+1<=x)ans=1;
	for(int i=1;i<n;i++){
		if((a[i]+x+y)-a[i+1]+1<=x)ans=1;
	}
	if(ans)cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
} 
```

---

## 作者：WA2025 (赞：0)

~~刚打完比赛写题解是最好的时间~~

[去博客查看，效果效果更佳 (*￣︶￣)](https://www.luogu.com/article/i8b3ikx0)

## 题目传送门

[AtCoder](https://atcoder.jp/contests/abc347/tasks/abc347_c) | [Luogu](/problem/AT_abc347_c)

## 题意

判断 Takahashi 的 $N$ 个计划是否都可以安排在假期。

## 思路

由于星期一的日期不确定，所以不能直接判断 $D_i \bmod (A+B)$ 是否小于等于 $A$~~（比赛的时候我就栽在这里了）~~。

正确的做法是把 $D_i \bmod (A+B)$，$D$ 数组按从小到大的顺序排序。如果 $D_n-D_1<A$，也就是说，从计划时间最早的 $D_1$ 到计划时间最晚的 $D_n$ 间隔不超过 $A$ 天，那么说明绝对有一种方案可以使所有计划排在假期里，否则判断是否有 $D_{i+1}+(A+B)-D_i<A$，意思是将 $D_{i+1}$ 天设为计划的第 $1$ 天，$D_i$ 天设为计划的最后一天，是否可以在这样的情况下使得天数小于 $A$，也就是都在假期，如只要满足一个这样的情况，就找出了方案，如果都不满足，就无法满足方案。

## 代码

奉上你们最爱的代码 `(*^▽^*)`

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int d[N];

int main() {
    int n, a, b; scanf("%d%d%d", &n, &a, &b);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
        d[i] %= (a + b);
    }
    sort(d + 1, d + n + 1);

    if (d[n] - d[1] <= a) return puts("Yes"), 0;

    for (int i = 1; i < n; i++) {
        int x = d[i] + (a + b) - d[i + 1];
        if (x < a) return puts("Yes"), 0;
    }
    puts("No");

    return 0;
}
```

（安全提醒：切勿抄袭~~啊啊啊~~）

---

