# [ABC257E] Addition and Multiplication 2

## 题目描述

高桥君有一个整数 $x$ 。一开始的时候， $x=0$ 。

高桥君可以无限执行以下操作：

- 选择一个整数 $i$ （ $1 \leq i \leq 9$ ）。支付 $C_i$ 日元，把 $x$ 变为 $10x+i$ 。

高桥君有 $N$ 日元，问 $x$ 最大是多少？

### 约束 ###

$1 \leq N \leq 10^6$

$1 \leq C_i \leq N$

保证 $N,C_i$ 都是整数。

## 样例 #1

### 输入

```
5
5 4 3 3 2 5 3 5 3```

### 输出

```
95```

## 样例 #2

### 输入

```
20
1 1 1 1 1 1 1 1 1```

### 输出

```
99999999999999999999```

# 题解

## 作者：ikunTLE (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc257_e)

### 思路

为了使 $x$ 最大，必须使 $x$ 的位数最大。在保证位数的情况下，必须要先使高位最大，再使更低的位数更大。也就是说，最终答案从高位到低位一定是个不升的序列。

首先需要求出序列的长度 $L$，则 $L=\lfloor\frac{N}{\min\{C_i\}}\rfloor$。我们保证 $L$ 最长的前提下，枚举 $1$ 到 $L$。每一位一定是越大越好，故从大向小枚举，如果可以直接输出当前数字，更新当前 $N$ 的值，然后接着枚举下一位。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
int a[15];
int main(){
	int n=read(),minn=INT_MAX;
	for(int i=1;i<=9;++i){
		a[i]=read();
		minn=min(minn,a[i]);
	}
	int l=n/minn;
	for(int i=1;i<=l;++i)
		for(int j=9;j>=1;--j)
			if(n-a[j]>=(l-i)*minn){
				printf("%d",j);
				n-=a[j];
				break;
			}
	printf("\n");
	return 0;
}
```

---

## 作者：DengDuck (赞：9)

本题十分简单。

我们想一想，比较两个非负整数的第一条件是什么？

对了，是长度。

所以我们要保证最长的长度。

怎么求呢？我们可以一直选择最便宜的数字，尽管最优解可能不是一直选择最便宜的数字，但这样求的来得到最长长度，说明最优解肯定是这个长度。

为什么？因为如果解的长度没达到这个最长长度，那就没有一直选择最便宜的数字好，因为比较两个非负整数的第一条件是长度。

而答案长度也不可能大于最长长度，因为最长长度已经是一直选择最便宜的数字了，它都买不下了，你换成别的数字不是更贵更买不起？

得到了长度，接下来比较什么？

对了，从高位到低位逐行比对。

我们从高位向低位枚举，每一位尽可能选最大，但要保证后面还填的了数字，不然就不满足长度要求了。

我们假设后面都填的是最便宜的，判断钱是否足够即可，这里和上面一样，不一定最优解是这样的，我们只是判断是否存在可行解，来判断当前解是否合法。

通常第五题都是普及组第三题难度，可以这道题感觉比第四题简单？

```cpp
#include <bits/stdc++.h>
using namespace std;

long long n, c[10], mn = 1e9, len;

int main() {
    cin >> n;
    for (int i = 1; i <= 9; i++) {
        cin >> c[i];
        mn = min(mn, c[i]);
    }
    len = n / mn;
    // cout<<len<<endl;
    for (int i = 1; i <= len; i++) {
        for (int j = 9; j >= 1; j--) {
            if ((n - c[j]) >= (len - i) * mn) {
                cout << j;
                n -= c[j];
                break;
            }
        }
    }
}
```

---

## 作者：沉石鱼惊旋 (赞：4)

### 题目翻译

有 $9$ 种数字，$1,2,\dots9$。

数字 $i$ 可以花 $c_i$ 的价格购买，你有 $n$ 元。

最后输出你购买的数字拼成的最大值。

### 题目思路

我们考虑，先让位数最大。

然后，再最大化最高位、次高位、次次高位，一直往下。

最大位数，即为用 $n$ 除以最便宜的价钱。

然后，你可能会有剩余的钱。

剩余的，我们开始置换。

从 $9$ 开始枚举，能换就换，并输出你置换的数字。

这样最大化了较高位，还保证位数没有变少。

具体可以品味下代码。

### 主要代码

```cpp
int c[20];
int main()
{
    int n, mnc = INT_MAX, maxn;
    cin >> n;
    for (int i = 1; i <= 9; i++)
    {
        cin >> c[i];
        if (c[i] <= mnc)
        {
            mnc = c[i];
            maxn = i;
        }
    }
    int cnt = n / mnc;
    int x = 0, cnt2 = 0;
    int s = n - cnt * mnc;
    for (int i = 9; i >= 1; i--)
    {
        if (i > maxn)
        {
            if (c[i] - mnc <= s)
            {
                cnt2 = s / (c[i] - mnc);
                cnt -= cnt2;
                s%=c[i] - mnc;
                for (int j = 1; j <= cnt2; j++)
                {
                    cout << i;
                }
            }
        }
    }
    for (int i = 1; i <= cnt; i++)
    {
        cout << maxn;
    }
    return 0;
}
```



---

## 作者：Hacker_Cracker (赞：0)

## [ABC257E] Addition and Multiplication 2 题解
### Solution
一道比较基础的贪心题。

首先我们需要知道高精比大小的规则。对于两个由数字组成的字符串 $S_1$ 和 $S_2$，只要 $|S_1|>|S_2|$，那么 $S_1$ 表示的数字一定大于 $S_2$ 表示的数字。所以我们贪心的基本原则是，在最大化答案字符串的长度的基础下，再最大化各个位的值。

在程序中，我们首先需要处理出能够拼出的最大长度的字符串。然后我们从高位开始遍历，这样优先增加高位，可以再余额一定的情况下最大化答案的值。在这里记所有的 $C_i$ 中的最小值 $MN=\displaystyle{\min_{i \in [1,9]}C_i}$，记最大长度 $Len=\lfloor \cfrac{N}{MN} \rfloor$，我们当前遍历到的是从左往右数第 $i$ 位，想要填充的是数字 $j$。那么当前可以填充 $C_{j}$ 的充分必要条件为 $MN \times (Len-i) \le N-C_j$。此后 $N$ 的值也需要更新，即 $N \gets N-C_j$。

这样我们就做完了。
### [Accepted Code](https://www.luogu.com.cn/record/203745510)
```cpp
#include<iostream>
using namespace std;
int c[15],mn=1e9,n,len;
int main(){
	cin>>n;
	for(int i=1;i<=9;i++) cin>>c[i],mn=min(mn,c[i]);
	len=n/mn;
	for(int i=1;i<=len;i++){//从高位到低位枚举 
		for(int j=9;j>=1;j--){//贪心，枚举符合条件的最大数字 
			if(mn*(len-i)<=n-c[j]){
				cout<<j;//以字符串形式打印 
				n-=c[j];//更新n 
				break;
			}
		}
	}
	cout<<endl; 
    return 0;
}
```

---

## 作者：songtaoran (赞：0)

首先必须让位数最多，很简单，位数最大就是 $\lfloor \frac{n}{\min(a_i)} \rfloor$。  
其次，必须让每一位最大，怎么办呢？对于每一位，从 $9$ 到 $1$ 枚举，判断条件是：当前日元 $-$ 花费的日元 $\ge$ 接下来花费的最少日元，即 $n - a_j \ge (len - i) \times \min(a_i)$，其中 $i$ 为当前在第几位，$j$ 为枚举的数字。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n, a[20];
int main(){
	cin >> n;
	ll mn = 9e18, now;
	for(ll i = 1; i <= 9; i++) scanf("%lld", &a[i]), mn = min(mn, a[i]);
	ll wei = n / mn;
	for(ll i = 1; i <= wei; i++)
		for(ll j = 9; j >= 1; j--)
			if(n - a[j] >= (wei - i) * mn){
				n -= a[j]; printf("%lld", j); break;
			}
	return 0;
}
```

---

## 作者：fyn1234 (赞：0)

### 思路

> 要使一个数尽可能的大，首先要让它的位数尽可能的大。然后再考虑由高位到低位由大到小排列。

首先计算出数字的位数 $l$，则 $l = \lfloor \dfrac{N}{\min(c(i))} \rfloor$。在保证 $l$ 最长的前提下，从 $1$ 到 $l$ 从大到小逐个枚举（因为每一位越大越好）。如果可以就直接输出当前数字，更新当前 $N$ 的值，然后再枚举下一位。

### solution

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[114];
int main(){
   int n,minn = 0x7FFFFFFF;
   cin>>n;
   for(int i=1;i<=9;++i){
   	cin>>a[i];//输入
   	minn=min(minn,a[i]);
   }
   int l=n/minn;
   for(int i=1;i<=l;i++){
   	for(int j=9;j>=1;j--)
   		if(n-a[j]>=(l-i)*minn){
   			cout<<j;
   			n-=a[j];
   			break;
   		}
 }
   return 0;
}
```

---

## 作者：iranai (赞：0)

~~一道比较水的题。~~
# 思路
要得到最大的数，长度自然是越大越好，因此先考虑全部选择花费最小的数填充，这样可以先求出最大长度。

得到最大长度之后，手中的 money 可能还有剩余，这时候就可以考虑从高位到低位将数字换成更大的数字，而这样的花费显然会比原来的花费多 $num_i-mi$（$num_i$ 表示数字 $i$ 的花费，$mi$ 表示所有数字中的最小花费），我们只需要从 $9$ 到花费最小的数字遍历，如果多出来的花费小于等于总钱数花费掉构造最长长度的数的花费后还剩的钱，就可以把这一位上的数换掉。
# 代码

```
#include <bits/stdc++.h>
using namespace std;
int n;
int num[10];
int idx;
int mi=0x3f3f3f3f;
int main(){
	cin>>n;
	for(int i=1;i<=9;i++){
		cin>>num[i];
		if(mi>=num[i]){
			mi=num[i];
			idx=i;
		}
	}
	int sum=n/mi;
	n%=mi;
	for(int i=1;i<=sum;i++){
		bool flag=true;
		for(int i=9;i>idx;i--){
			if(n-num[i]+mi>=0){
				n=n-num[i]+mi;
				flag=false;
				cout<<i;
				break;
			}
		}
		if(flag) cout<<idx;
	}
	return 0;
}
```

---

## 作者：Meickol (赞：0)

感觉题解区大家给出的解法不是很优雅，在此给出一个更通用的完全背包的做法。

直接给出 DP 定义：以 $f_j$ 表示 $j$ 元一共能凑出多少个数字。

我们可以思考一下，保证选取个数最多就一定更优吗？

这显然是的，因为对于一个数而言，长度大的肯定比长度小的值更大。

首先我们解决了最多能凑出数字的个数。

然后 DP 完后再回头求一下具体方案即可。

注意我们 DP 之前先贪心处理，优先使用大的数。

最后求具体方案时我们也是直接正着枚举即可，因为因为 DP 前已贪心处理，先枚举的一定是更大的数字。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
const int N=15,M=1e6+5;
int m;
int f[M];
struct node{
	int cost,val;
	bool operator<(node &t){
		return val>t.val;
	}
}p[N];
void solve(){
	cin>>m;
	rep(i,1,9) cin>>p[i].cost,p[i].val=i;
	sort(p+1,p+1+9);
	rep(i,1,9){
		rep(j,p[i].cost,m){
			f[j]=max(f[j],f[j-p[i].cost]+1);
		}
	}
	int j=m;
	rep(i,1,9){
		while(j>=p[i].cost && f[j-p[i].cost]+1==f[j]){
			cout<<p[i].val;
			j-=p[i].cost;
		}
	}
}
```

---

## 作者：xmy201315 (赞：0)

这道题让我们要 $x$ 最大，那么什么样的数最大呢？那肯定是位数越多的数越大。那我们在 $x$ 后面加上什么数字代价最小？

假设我们在 $x$ 后面放 $j$ 代价最小，那么我们最多放 $\lfloor \dfrac{N}{C_j} \rfloor$ 位。那么在位数最多的情况下，什么样的数最大呢？

这道题可以贪心，一位一位地放数字，数字当前能放多大就放多大，数字要大，越往前数字就要尽可能的大，所以我们可以从高位往低位填。

那怎么看这一位能不能填一个数字呢？那就枚举从 $9\sim 1$ 一个一个试过去，那我们怎么知道这个数字要不要放上去呢？

假设现在我们还剩 $y$ 日元，假设我们枚举到 $k$ ，那我们放上去后，后面那些位能用的钱就是 $y-C_k$，那放不放呢？我们一定要 $y-C_k\ge C_j\times(9 - k)$，那么我们一位一位确定下来就行。

时间复杂度其实是 $\mathcal O(n)$,因为假设每个数的代价都是 $1$，那么一共得枚举 $n$ 位。

[AC记录](https://www.luogu.com.cn/paste/9goqd4ao)
```cpp
#include <bits/stdc++.h>
using namespace std;
#define sc scanf
#define pr printf
int n, c[10];   // c 记的是9个位的代价
int main(){
    sc ("%d", &n);
    for (int i = 1; i <= 9; i++)
        sc ("%d", &c[i]);
    int m = 1 << 30;
    for (int i = 1; i <= 9; i++)
        m = min (m, c[i]);
    int l = n / m;
    for (int i = 1; i <= l; i++)
        for (int j = 9; j; --j)
            if (n - c[j] >= m * (l - i)){
                n -= c[j];
                pr ("%d", j);
                break;
            }
}
```

---

## 作者：run_away (赞：0)

## 题意

最开始有一个为零的数 $x$。

你可以花费一定代价在 $x$ 后面加入一个 $0\sim9$ 的数字。

给定你拥有的钱和加入每一个数字的代价，求能组合出的最大数。

## 分析

考虑贪心。

首先，不管是什么数字，较长的数字肯定比较短的数字大。

所以找出代价最小的数，先求出最大长度。

然后考虑用更大的数字替换一些小的数字。

从最左边开始逐位替换，若剩余的钱可以替换就替换，每次都选择最大的。

注意在判断和扣钱时加入之前用的最小值。

使用 string 会方便一些，线性时间可过。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
// static char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf;
// #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
// #define putchar(x) (p3-obuf<1000000)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar('\n');return;}ll top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar('\n');}
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
const ll mod=1e9+7,maxn=1e5+5,maxt=505;
ll n,c[10]={INT_MAX},mn;
string ans;
inline void solve(){
    n=read();
    for(ll i=1;i<=9;++i){
        c[i]=read();
        if(c[i]<c[mn])mn=i;
    }
    for(ll i=1;i<=n/c[mn];++i){
        ans.push_back(mn+'0');
    }
    n-=ans.size()*c[mn];
    for(ll i=0;i<ans.size();++i){
        for(ll j=9;j>=1;--j){
            if(n+c[mn]>=c[j]){
                n-=c[j]-c[mn],ans[i]=j+'0';break;
            }
        }
    }
    cout<<ans;
}
signed main(){
    ll t=1;
    while(t--){
        solve();
    }
    // fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```

---

## 作者：Luxingguang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc257_e)

[ $Atcoder$ 传送门](https://atcoder.jp/contests/abc257/tasks/abc257_e)

## 一、简述题意
------------
有一个数 $x$，初始化为 $0$。选择一个数 $i$，花费 $C_i$ 的权值使得 $x$ 变为 $10x+i$。

$1\leq i\leq9$。

## 二、思路分析
------------
首先先算出 $x$ 最多有多少位，再在最多位数的前提下，尽可能多的让前面的数字更大

## 三、构造代码
------------

```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int n,a[15],minn=0x3f3f3f3f,maxn;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=9;i++){
		scanf("%lld",&a[i]);
		minn=min(minn,a[i]);
	}maxn=n/minn;
	for(int i=maxn;i>=1;i--){
		for(int j=9;j>=1;j--){
			if((n-a[j])>=(i-1)*minn){
				printf("%lld",j);
				n-=a[j];
				break;
			}
		}
	}
	return 0;
}

```


---

## 作者：Disjoint_cat (赞：0)

# [ABC257E](https://www.luogu.com.cn/problem/AT_abc257_e) [Addition and Multiplication 2](https://atcoder.jp/contests/abc257/tasks/abc257_e)

（注意看，上面是两个题目链接）

## 题意

你有 $n$ 元钱，有一个数字 $x$ 初始值为 $0$。

每次你可以花 $c_i\ (1\le i\le9)$ 元，向 $x$ 后面加一个数字 $i$。

求你能得到的最大数字。$n\le10^6$。

## 题解

~~这也能评到绿？~~

显然贪心，如果全选最便宜的，可以让位数最大。（虽然并不一定真的全加最便宜的。）

考虑替换掉前面一些位，显然肯定换比它更大的。

那就肯定要尽量换掉原本小的数，直到钱不够了。

**这时还不能停止，要再检查更小一点（但仍然大于最便宜的数）的数**。

例如，$9$ 不够钱换了就换 $8$，然后再换 $7$，以此类推，

直到比最便宜的数还小为止。

然后就只能用最便宜的数了。

## Code

```cpp
int n,a[10],mx=INT_MAX,id;
void Solve()
{
	cin>>n;
	for(int i=1;i<=9;i++){cin>>a[i];if(a[i]<=mx)mx=a[i],id=i;}
	int tmp=n/mx;//位数
	n%=mx;
	for(int i=9;i>id;i--)//只要钱够就换（这里直接输出了）
		while(tmp&&a[i]-a[id]<=n)cout<<i,n-=a[i]-a[id],tmp--;
	while(tmp--)cout<<id;//没钱了
}
```

## 彩蛋

下面这组数据非常好玩：

```
2559
256 257 258 260 264 272 288 320 384
```

输出为 $987654321$！

---

## 作者：Bulyly (赞：0)

### 解析
- 很不错的一道贪心题目，首先你需要明白 $10x$ 加 $i$ 的含义，因为 $i$ 是个位数我们可以将其忽略，其实质就是将 $x$ 左移一位。

- 接下来就好办了我们想要让 $x$ 越大即使 $x$ 的数位越大，所以我们可以采取贪心的办法:每次选择最小的数，这样位数一定是最大的我们通过 $N \div \min$ 来得到最大数位 $k$。

- 接下来我们继续贪心，从高到底枚举每一位，挑选出不影响数位且尽可能大的数  $i$。

下附代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define rs register
using namespace std;
const int MAXN=110522;
int w[MAXN];
int N,Min=0x3f3f3f3f;
int main()
{
	scanf("%d",&N);
	
	for(rs int i=1;i<=9;i++)  scanf("%d",&w[i]),Min=min(Min,w[i]);
	
	int k=N/Min;
	
	for(rs int i=1;i<=k;i++)
	{
		for(rs int j=9;j>=1;j--)
		{
			if(N-w[j]>=(k-i)*Min)
			{
				N-=w[j];
				printf("%d",j);
				break;
			}
		}
	}
	printf("\n");
	return 0;
}
```
完结撒花~

---

## 作者：binbin_200811 (赞：0)

~~本篇质量较水请谨慎阅读。~~

#### 题目大意

初始时，$x=0$。

有 $n$ 元钱，你可以花 $c_i(1\leq i\leq 9)$ 元将 $x=x\times 10+i$。求 $x$ 最大多少。

#### 思路


考试最后 $30$ 分钟，一开始排除动态规划想到贪心，$10$ 分钟兜兜转转又回到动态规划？？？

不过还好 $5$ 分钟就想出了正解。

不扯了，下面是正经的。

有 $10$ 个物品，把 $c_i$ 看成物品重量，$n$ 看成背包体积，$i$ 作为物品价值 $(1\leq i \leq 9)$。

是不是有了背包的感觉。

设 $dp_i$ 表示剩余 $i$ 容量时的最大值。

由于我们的数字可能十分大，属于 `long long` 见了都落泪，`int` 看了直下跪。让我们来分析一下。

本题其实本质是在一定条件下选若干数字，使他们的放在一起最大。根据小学奥数，我们知道要把较大的数字放大前面来使数字最大。因此，我们其实只要存下每个状态的每个数字有多少个就可以了。

那我们在比较大小的时候，先比较位数，再从大到小比较每个数字的数量。

我们的动态转移方程就是：
$$
dp_i=\max(dp_i,dp_{i+c_k}+k)
$$
其中 $+k$ 为添加一个数字 $k$。

我们的 $dp_i$ 用结构体会好打很多，在代码中 `dp[i].cis[j]` 表示 $dp_i$ 状态下数字 $j$ 有多少个。

#### CODE

```c++
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const ll maxn=2e6+5;

struct node
{
    ll m=0;
    ll cis[11]={0};//第几个数字有多少个
}dp[maxn];

ll n;
ll vis[15];//c_i

ll cmp(node a,node b)//比较，a>b返回1，a<b返回-1，a=b返回0
{
        if(a.m>b.m) return 1;
        else if(a.m<b.m) return -1;//比较位数
    for(ll i=9;i>=1;i--)
    {
        if(a.cis[i]>b.cis[i]) return 1;//比较哪一个数字多，多的直接比另外一个大
        else if(b.cis[i]>a.cis[i]) return -1;
    }
    return 0;
}

int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=9;i++) scanf("%lld",&vis[i]);
    for(ll i=1;i<=9;i++)
    {
        for(ll j=n-vis[i];j>=0;j--)
        {
            node tmp=dp[j+vis[i]];
            tmp.m++;//增加1个数字，位数++
            tmp.cis[i]++;//对应的数字个数++
            if(cmp(dp[j],tmp)==-1)//tmp>dp[j]
                dp[j]=tmp;
        }
    }//背包
    for(ll i=9;i>=1;i--)
    {
        for(ll j=dp[0].cis[i];j>=1;j--) printf("%lld",i);//输出
    }
}
```

忘记判断位数，考试没了 $88$ 分惨寄。

---

## 作者：G1yu (赞：0)

# 题解 [[ABC257E] Addition and Multiplication 2](https://www.luogu.com.cn/problem/AT_abc257_e)

### 思路

我们观察题面，首先可以确定的是，要保证 $x$ 最大，$x$ 本身的数位个数要尽可能地大，也就是要先求 $\max(\log_{10}x)$。因为我们每次选择一个数都能让位数加一，所以一开始我们就要一直买花费最少的数字，保证数位最大。最终我们能得到 $\max(\log_{10}x) = \lfloor \frac{N}{\min(c_i)} \rfloor$。

在求出数位的最大值后，我们考虑能否用剩余的金额买其他的数字提升价值，我们首先为了最大化数位花费了 $\min(c_i) \times \lfloor \frac{N}{\min(c_i)} \rfloor$ 那么我们剩余的金额就是 $N \bmod \min(c_i)$ 了。相应的，对于其他的数字，我们同样取模。为了使最终答案最大，我们在遍历时要从高位开始，记录 $\min (c_i)$ 的下标 $i$，从 $9 \sim i$ 取值判断，如果剩余金额足够，就输出。详细见代码。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+6;

int a[11],Min=2e9,mind;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	for(int i = 1; i<=9;i++){
		cin>>a[i];
		if(a[i]<=Min){
			mind = i;Min = a[i];
		}
	}
	for(int i =1; i<=9;i++){
		a[i] %= Min;
	}
	int len = n/Min;
	n%=Min;
	for(int i = 1;i<=len;i++){
		for(int j = 9;j>=mind;j--){
			if(a[j] <= n){ 
				n-= a[j];
				cout<<j;
				break;
			} 
		}
	}
	return 0;
}

```

---

