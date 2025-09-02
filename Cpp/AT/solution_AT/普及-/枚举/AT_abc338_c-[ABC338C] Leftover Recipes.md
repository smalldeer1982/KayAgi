# [ABC338C] Leftover Recipes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc338/tasks/abc338_c

冷蔵庫に $ N $ 種類の材料があります。これらを材料 $ 1 $、$ \dots $、材料 $ N $ と呼びます。材料 $ i $ は $ Q_i $ グラムあります。

あなたは $ 2 $ 種類の料理を作れます。料理 A は、$ 1 $ 人分を作るのに各材料 $ i $ $ (1\ \leq\ i\ \leq\ N) $ が $ A_i $ グラム必要です。料理 B は、$ 1 $ 人分を作るのに各材料 $ i $ が $ B_i $ グラム必要です。どちらも整数人分しか作れません。

冷蔵庫にある材料のみを使って、最大で合計何人分の料理を作れますか。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10 $
- $ 1\ \leq\ Q_i\ \leq\ 10^6 $
- $ 0\ \leq\ A_i\ \leq\ 10^6 $
- $ A_i\ \geq\ 1 $ であるような $ i $ が存在する。
- $ 0\ \leq\ B_i\ \leq\ 10^6 $
- $ B_i\ \geq\ 1 $ であるような $ i $ が存在する。
- 入力値はすべて整数である。
 
### Sample Explanation 1

この冷蔵庫には、$ 800 $ グラムの材料 $ 1 $ と $ 300 $ グラムの材料 $ 2 $ があります。 $ 100 $ グラムの材料 $ 1 $ と $ 100 $ グラムの材料 $ 2 $ で料理 A を $ 1 $ 人分作れ、$ 200 $ グラムの材料 $ 1 $ と $ 10 $ グラムの材料 $ 2 $ で料理 B を $ 1 $ 人分作れます。 料理 A を $ 2 $ 人分、料理 B を $ 3 $ 人分作るのに必要な材料 $ 1 $ の量は $ 100\ \times\ 2\ +\ 200\ \times\ 3\ =\ 800 $ グラム、材料 $ 2 $ の量は $ 100\ \times\ 2\ +\ 10\ \times\ 3\ =\ 230 $ グラムで、いずれも冷蔵庫にある量を超えません。このようにして合計 $ 5 $ 人分の料理を作ることができますが、$ 6 $ 人分を作る方法はなく、答えは $ 5 $ です。

### Sample Explanation 2

$ 800 $ グラムの材料 $ 1 $ で料理 A を $ 8 $ 人分、$ 300 $ グラムの材料 $ 2 $ で料理 B を $ 30 $ 人分、合計 $ 38 $ 人分作れます。

### Sample Explanation 3

何も作れません。

## 样例 #1

### 输入

```
2
800 300
100 100
200 10```

### 输出

```
5```

## 样例 #2

### 输入

```
2
800 300
100 0
0 10```

### 输出

```
38```

## 样例 #3

### 输入

```
2
800 300
801 300
800 301```

### 输出

```
0```

## 样例 #4

### 输入

```
10
1000000 1000000 1000000 1000000 1000000 1000000 1000000 1000000 1000000 1000000
0 1 2 3 4 5 6 7 8 9
9 8 7 6 5 4 3 2 1 0```

### 输出

```
222222```

# 题解

## 作者：ToastBread (赞：10)

# ABC338 C 题解
## 大意
有 $N$ 种食材，第 $i$ 种食材有 $Q_i$ 克。做一份 A 菜品，第 $i$ 种食材要 $A_i$ 克，做一份 B 菜品，第 $i$ 种食材要 $B_i$ 克。求出最多能做出几份菜。
## 思路
关注数据范围：

- $1 \leq N \leq 10$
- $1 \leq Q_i \leq 10^6$
- $0 \leq A_i \leq 10^6$
- $0 \leq B_i \leq 10^6$

很明显可以发现，数据范围还是很小的，自然想到**枚举**。因为只有两种菜品，所以可以枚举 A 菜品的数量，用做出 A 菜品后剩下的食材来贪心出最多能做多少 B 菜品，最后统计出最多能做出多少菜品。具体的实现思路可以看我的代码。

需要注意，题目的样例 2 中已经写出了菜品消耗的量**可以为 0**，所以注意特判，不要除以 0。

## AC 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,q[15],a[15],b[15],amax=1e9,bmax=1e9,ans=-1;//amax表示最多能做几份a套餐 bmax同理 
int main()
{
	cin>>n;//输入 
	for(int i = 1; i <= n; i++)
	{
		cin>>q[i];
	}
	for(int i = 1; i <= n; i++)
	{
		cin>>a[i];
	}
	for(int i = 1; i <= n; i++)
	{
		cin>>b[i];
	}
	for(int i = 1; i <= n; i++)
	{
		if(a[i])//这里与a[i]>0等价 避免除以0 
		{
			amax=min(amax,q[i]/a[i]);//q[i]还有的量 a[i]一份要多少 自然求出这个材料只能做出q[i]/a[i]份 
		}
	}
	for(int i = 0; i <= amax; i++)//枚举选几份A套餐 记得考虑不选！ 
	{
		bmax=1e9;//初始化 
		for(int j = 1; j <= n; j++)//遍历求出最多能做多少份B套餐 
		{
			if(b[j])//与b[j]>0等价 
			{
				bmax=min(bmax,q[j]/b[j]);
			}
			q[j]-=a[j];//减少一份A的量 因为i可能等于0(不取)，所以这行代码要放到B套餐的判断后面 
		}
		ans=max(ans,i+bmax);//更新答案
	}
	cout<<ans;//输出 
	return 0;//华丽收尾 
} 
```


---

## 作者：Hog_Dawa_IOI (赞：3)

### 题意
冰箱里有 $n$ 种原料，第 $i$ 种原料有 $q_i$ 单位。    
你可以做两种菜，A 菜和 B 菜。要做一道 A 菜，第 $i$ 种原料需要 $a_i$ 单位；做一道 B 菜，第 $i$ 种原料需要 $b_i$ 单位。   
问最多可以做多少道菜（A 菜和 B 菜的数量总和）。      
**数据范围：$1 \le n \le 10,1 \le q_i \le 10^6,0 \le a_i,b_i \le 10^6(1 \le i \le n)$**。    
有至少一个 $a_i$ 和至少一个 $b_i$ 大于 $0$。      

### 思路
看到“最多可以做多少道菜”，会想到二分；但由于有 A 菜和 B 菜两个变量，也许你会尝试用三分。（我们机房里就有一位同学敲了三分，最后在三发罚时的惨烈教训下放弃了。）     
但是当我们看见 $1 \le n \le 10$ 的时候，就应该感觉到可能不需要三分了。  
事实上，这里只需要暴力枚举。        
我们枚举当前做多少道 A 菜，这样就可以求出每种原材料剩下的数量，接着把能做的最多的 B 菜数量求出来。二者一加，取最大值即可。        
时间复杂度：A 菜的数量最多是 $10^6$，$n$ 最大也才 $10$，二者相乘最多为 $10^7$，可以通过。        

### 提醒和代码
警钟敲烂：

- 枚举 A 菜数量时不要偷懒直接从 $0$ 枚举到 $10^6$，要老老实实求出 A 菜数量的取值范围。同时也别忘记把 $0$ 考虑到。      
- 如果不需要当前原料，即数字为 $0$，那么需要特判不能直接除，否则会运行时错误。（不过我想如果不特判的话连样例也过不了应该可以检查出来。）    
至于如何特判，可以直接把当前原料最多能做成多少份菜肴的数量设成无限大，反正总有一个 $a_i$ 和 $b_i$ 不是 $0$，到那个时候就可以更新成正确的值。  

附参考代码：
```cpp
#include<stdio.h>
long long n,s[15],a[15],b[15],ans;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&s[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
    long long num=1000005;
    for(int i=1;i<=n;i++)
    num=num<(a[i]==0?1000000:s[i]/a[i])
    ?num:(a[i]==0?1000000:s[i]/a[i]);
    for(int i=0;i<=num;i++)
    {
        long long min=1000005;
        for(int j=1;j<=n;j++)
        min=min<(b[j]==0?1000000:(s[j]-a[j]*i)/b[j])
        ?min:(b[j]==0?1000000:(s[j]-a[j]*i)/b[j]);
        ans=ans>min+i?ans:min+i;
    }
    printf("%lld",ans);
}
```

---

## 作者：M1saka16I72 (赞：2)


# AtCoder Beginner Contest 338 [C - Leftover Recipes](https://atcoder.jp/contests/abc338/tasks/abc338_c) 题解
## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-abc338-c.html)

场上刚开始还天真的以为是个爆搜或者奇怪的背包，浪费了好久。。

## 思路
看到这个题我们首先想到的一定是暴力 dfs 枚举做菜品 a 还是菜品 b，但复杂度为 $\mathcal O(2^{ans})$，显然无法通过本题。于是我们来思考一下贪心做法。

实际上，这道题的题意可以简化成 $n$ 个不等式，设我们最后做了 $x$ 道菜品 a，$y$ 道菜品 b，就可以表示成如下形式：

> $a_1x+b_1y\leq q_2,a_2x+b_2y\leq q_2,\cdots,a_nx+b_ny\leq q_n$

并且注意到题意里 $a,b,q$ 的取值范围都不超过 $10^6$，于是我们可以考虑枚举当前的 $x$ 或 $y$（这里选择枚举 $y$），对不等式做变形，得到如下式子：

> $x\leq \lfloor \frac{q_i-b_iy_i}{a_i} \rfloor(1\leq i\leq n,b_iy_i\leq q_i)$

按照以上思路，枚举 $y$ 并且按上式求出最大并且对于每一个 $q_i,a_i,b_i$ 都合法的 $x$ 即可，时间复杂度 $\mathcal O(kn)$，其中 $k$ 是最后的答案，而答案不超过 $10^6$，可以通过本题。

同时要注意判断当前 $y$ 是否合法以及特判 $a_i=0$ 的情况。

## 代码
```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pil pair<int,long long>
#define pll pair<long long,long long>
#define mp_ make_pair
#define pb_ push_back
#define pob_ pop_back
#define fst first
#define snd second
#define debug cout<<"********\n";
#define reset(x,y) memset(x,y,sizeof(x))
#define fi(x) freopen(x,"r",stdin)
#define fo(x) freopen(x,"w",stdout)
#define iosf ios::sync_with_stdio(0);cin.tie(0);
#define prec(x) cout<<setprecision(x);
#define prec0(x) cout<<fixed<<setprecision(x);
#define s(x,y) x[y-1]
#define Misaka16172 sb

using ll = long long;
using ld = long double;
using db = double;
using ull = unsigned long long;

const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;

using namespace std;

template <class T>
inline void read(T &x){
	x = 0;T w = 1;
	char c = 0;
	while(c<'0' || c>'9'){
		if(c=='-')	w = -1;
		c = getchar();
	}
	while(c>='0' && c<='9'){
		x = ((x<<3)+(x<<1))+c-'0';
		c = getchar();
	}
	x = x*w;
}
int n;
ll q[15],a[15],b[15];
ll ans = 0;

void solve(){
	read(n);
	for(int i=1;i<=n;i++)	read(q[i]);
	for(int i=1;i<=n;i++)	read(a[i]);
	for(int i=1;i<=n;i++)	read(b[i]);
	for(int y=0;y<=1e6;y++){
		bool flag = 0;
		for(int i=1;i<=n;i++){
			if(y*b[i]>q[i]){	//检查当前y是否合法，不合法直接退出
				flag = 1;
				break;
			}
		}
		if(flag)	break;
		ll x = INF;
		for(int i=1;i<=n;i++){
			if(a[i]>0)	x = fmin(x,floor(q[i]-b[i]*y)*1.0/a[i]);	//求出最大的且满足要求的x
		}
		if(x>=0)	ans = fmax(ans,x+y);	//更新答案
	}
	cout<<ans;
}	

int main(){
	int t = 1;
//	read(t);
	for(int tt=1;tt<=t;tt++){
		solve();
	}
}
```


---

## 作者：WilliamFranklin (赞：2)

这道题就是直接暴力。

### 主要思路

我们考虑如何暴力。

很容易就可以想到，我们是否可以暴力枚举做 A 型菜的数量？结果告诉我们，这个直觉是对的，因为 $Q_i,A_i,B_i$ 都是小于等于 $10^6$ 的。

然后，就考虑一下如何最优的实现我们上面的想法：考虑每一次将 $Q_i$ 都减去一次 $A_i$，然后 A 型菜的数量加 $1$，并求出 $\lfloor\frac{Q_i}{B_i}\rfloor$ 的最小值就是此时 B 型菜可做的最大数量，当然，如果我们发现有一个 $j$ 满足 $Q_j$ 小于 $0$ 了，那也就应该跳出循环了。最后我们取所有情况下 A 型菜和 B 型菜数量和的最大值就是最后的答案。

也许有些地方还是说的不太清楚，看看代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 15;
int q[N], a[N], b[N];
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	For(i, 1, n) cin >> q[i];
	For(i, 1, n) cin >> a[i];
	For(i, 1, n) cin >> b[i];
	long long maxn = 0;
	long long cntt = 0;
	while (1) { // 这里用死循环的方式写的
		long long cnt = 1e18;
		for (int i = 1; i <= n; i++) {
			if (b[i] == 0) continue;
			cnt = min(cnt, 1ll * q[i] / b[i]);
		}
		maxn = max(maxn, cnt + cntt);
		cntt++;
		for (int i = 1; i <= n; i++) {
			q[i] -= a[i];
			if (q[i] < 0) {
				cout << maxn;
				return 0;
			}
		}
	}
	cout << maxn;
	return 0;
} 
```

### 谢谢观看

---

## 作者：xz001 (赞：1)

枚举 $A$ 食材的制作次数，由题意得不会超过 $10^6$ 次，然后对于每种情况求得 $B$ 食材可以制作的数量，求其和的最大值即可。

代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, mod = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, q[N], a[N], b[N], tmp[N], ans;

signed main() {
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> q[i], tmp[i] = q[i];
    for (int i = 1; i <= n; ++ i) cin >> a[i];
    for (int i = 1; i <= n; ++ i) cin >> b[i];
    for (int i = 0; i <= 1e6; ++ i) {
    	for (int j = 1; j <= n; ++ j) q[j] = tmp[j];
    	bool f = 0;
    	for (int j = 1; j <= n; ++ j) {
    		q[j] -= a[j] * i;
    		if (q[j] < 0) {
    			f = 1;
                break;
			}
		}
		if (f) break;
		int minn = 1e18;
		for (int j = 1; j <= n; ++ j) if (b[j]) minn = min(minn, q[j] / b[j]);
		ans = max(ans, i + minn);
	}
	cout << ans << endl;
    return 0;
}


```

---

## 作者：_shine_ (赞：0)

因为 $n$ 只有 $10$，考虑以 $n$ 为切入点解决问题。

暴力枚举 A 菜有 $i$ 盘，而剩下的可直接暴力求材料的最小值算出对应最多能有多少盘 B 菜，此时两个加起来最大即为答案。

注意 $0$ 的问题，当 $b_i$ 为 $0$ 时不需要取最小值。

代码较为拙劣，建议自己写。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int n,all[maxn],a[maxn],b[maxn];
int ans,cnt1,cnt2;
bool check(int mid){
    cnt1=INT_MAX;
    for(int i=1;i<=n;++i){
        if(mid*a[i]>all[i])return false;
        else if(b[i]!=0)cnt1=min(cnt1,(all[i]-mid*a[i])/b[i]);
    }
    ans=max(ans,cnt1+mid);
    return true;
}
signed main(){
    cin >> n;for(int i=1;i<=n;++i)cin >> all[i];
    for(int i=1;i<=n;++i){cin >> a[i];cnt1+=a[i];}
    for(int i=1;i<=n;++i){cin >> b[i];cnt2+=a[i];}
    for(int i=0;check(i)==true;++i);
    cout << ans << endl;
	return 0;
}
```


---

## 作者：highkj (赞：0)

# 前言
~~就我一人写二分是吧，虽然说确实没必要~~。
# 思路
首先，我们可以发现对于答案 $ans$ 显然是满足单调性的所以我们果断二分答案，首先二分出一个 $mid$ 然后再枚举出第一种选多少瓶然后求出每一种需要的数量，然后再比较是否每一种需要的都比拥有的少即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n;
int q[1010],a[1010],b[1010],p[11];
bool check(int x) {
	rep(i,0,x) {
		rep(j,1,n) p[j]=a[j]*i;
		rep(j,1,n) p[j]+=b[j]*(x-i);
		int f=0;
		rep(j,1,n) {
			if(p[j]>q[j]) {
				f=1;
				break;
			}
		}  if(!f) return 1;
	}return false;
}
fire main() {
	in(n);
	rep(i,1,n) in(q[i]);
	rep(i,1,n) in(a[i]);
	rep(i,1,n) in(b[i]);
	int l=0,r=3000000,res=0;
//	cout<<check(5)<<endl;
	while(l<=r) {
		int mid=l+r>>1;
		if(check(mid)) l=mid+1,res=mid;
		else r=mid-1;
	} cout<<res;
	return false;
}
```

---

## 作者：Loser_Syx (赞：0)

因为保证了 $a_i$ 至少有一个 $\neq 1$，所以 $a$ 菜品我们最多只会做 $\max q_i$ 份，考虑枚举这个做的份数，可以根据这个得出剩下的配料，再根据贪心策略决策 $b$ 菜品所做的份数即可。

不要 $q_i \div 0$！！！

```cpp
const int N=15;
int a[N], b[N], q[N];
signed main() {
	int n=read(),ans=0;
	for (int i=1;i<=n;++i) read(q[i]);
	for (int i=1;i<=n;++i) read(a[i]);
	for (int i=1;i<=n;++i) read(b[i]);
	for (int i=0,flg=1;i<=1e6&&flg;++i) {
		for (int j=1;j<=n;++j) if (a[j]*i > q[j]) {
			flg=0;
			break;
		}
		if (!flg) break;
		int mn=1e9;
		for (int j=1;j<=n;++j) if (b[j]) mn=min(mn,(q[j]-a[j]*i)/b[j]);
		ans=max(ans,i+mn);
	}
	write(ans,'\n');
	return 0;
} 
```

---

## 作者：Floating_Trees (赞：0)

## 题意
冰箱里有 $n$ 种食材，第 $i$ 种食材有 $q_i$ 克，你可以做两种菜，做 A 菜需要 $a_i$ 克 $i$ 种食材，做 B 菜需要 $b_i$ 克 $i$ 种食材，问你用这些食材最多可以做出多少盘菜。
#### 数据
+ $1 \le n \le 10$
+ $1 \le q_i \le 10^6$
+ $0 \le a_i \le 10^6$
+ $0 \le b_i \le 10^6$
+ $a_i,b_i$ 中必有一个大于等于 1 。

## 思路
首先想到打暴力，枚举做几盘 A 种菜，做几盘 B 种菜，但显然这样会超时，所以考虑优化。题目说要求最大的那么就是做的越多越好，那么当确定下来一盘菜做多少盘，那剩下的食材肯定是都去做另外一盘菜，这样肯定是做出来菜最多的。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 20;
int n,q[N],a[N],b[N];

int main()
{
	scanf ("%d",&n);
	int Max = INT_MAX;
	for (int i = 1;i <= n;i++)
		scanf ("%d",&q[i]);
	for (int i = 1;i <= n;i++)
		scanf ("%d",&a[i]), Max = min(Max,(a[i] == 0 ? INT_MAX : q[i] / a[i]));
	for (int i = 1;i <= n;i++)
		scanf ("%d",&b[i]);
	int ans = 0;
	for (int i = 0;i <= Max;i++)
	{
		int ca = i, cb = INT_MAX;
		for (int j = 1;j <= n;j++)
			cb = min(cb,(b[j] == 0 ? INT_MAX : (q[j] - i * a[j]) / b[j]));
		ans = max(ans,ca + cb); 
	}
	printf ("%d",ans);
	
	return 0;
}
``````

---

