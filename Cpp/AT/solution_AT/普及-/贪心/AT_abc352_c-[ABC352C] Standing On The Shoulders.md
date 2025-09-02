# [ABC352C] Standing On The Shoulders

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc352/tasks/abc352_c

$ N $ 人の巨人がいます。巨人にはそれぞれ $ 1,\ 2,\ \ldots,\ N $ の名前がついており、巨人 $ i $ が地面に立ったとき、肩の高さは $ A_i $、頭の高さは $ B_i $ となります。

あなたは $ (1,\ 2,\ \ldots,\ N) $ を並べ替えて得られる数列 $ (P_1,\ P_2,\ \ldots,\ P_N) $ を選び、以下の規則に従って $ N $ 人の巨人を積み上げることができます。

- まず地面に巨人 $ P_1 $ を立たせる。巨人 $ P_1 $ の肩は地面を基準として $ A_{P_1} $、頭は地面を基準として $ B_{P_1} $ の高さとなる。
- $ i\ =\ 1,\ 2,\ \ldots,\ N\ -\ 1 $ の順に巨人 $ P_i $ の肩の上に巨人 $ P_{i\ +\ 1} $ を立たせる。巨人 $ P_i $ の肩が地面を基準として高さ $ t $ のとき、巨人 $ P_{i\ +\ 1} $ の肩は地面を基準として $ t\ +\ A_{P_{i\ +\ 1}} $、頭は地面を基準として $ t\ +\ B_{P_{i\ +\ 1}} $ の高さとなる。
 
一番上に立っている巨人、すなわち巨人 $ P_N $ の地面を基準とした頭の高さとして実現できる最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ B_i\ \leq\ 10^9 $
- 入力される値はすべて整数
 
### Sample Explanation 1

$ (P_1,\ P_2,\ P_3)\ =\ (2,\ 1,\ 3) $ とすると、地面を基準として巨人 $ 2 $ は肩の高さが $ 5 $、頭の高さが $ 8 $、巨人 $ 1 $ は肩の高さが $ 9 $、頭の高さが $ 15 $、巨人 $ 3 $ は肩の高さが $ 11 $、頭の高さが $ 18 $ となります。 一番上に立っている巨人の頭の高さが地面を基準として $ 18 $ より大きくなることはないため $ 18 $ を出力します。

## 样例 #1

### 输入

```
3
4 10
5 8
2 9```

### 输出

```
18```

## 样例 #2

### 输入

```
5
1 1
1 1
1 1
1 1
1 1```

### 输出

```
5```

## 样例 #3

### 输入

```
10
690830957 868532399
741145463 930111470
612846445 948344128
540375785 925723427
723092548 925021315
928915367 973970164
563314352 832796216
562681294 868338948
923012648 954764623
691107436 891127278```

### 输出

```
7362669937```

# 题解

## 作者：Dream_Mr_li (赞：13)

## Problem

有 $n$ 个巨人，每个巨人都有一个肩膀到地面的高度 $a_i$ 和头到地面的高度 $b_i$ 。

现在让你把这 $n$ 个巨人堆叠在一起，堆叠操作是将一个巨人放在另一个巨人的肩上，即不算此巨人的头高（ 头高 = 头到地面的高度 - 肩膀到地面的高度 ）。

最后输出堆叠后的最大的高度。

## Solution

这道题要求最大高度，所有肩膀高度的就一定都会加上，所以需要先累加肩膀的高度。

因为有一个头在最顶上，为了求出最大高度，就得求出最大的头的高度。

最后把累加的肩膀的高度和最大的头的高度相加就好了。

![](https://cdn.luogu.com.cn/upload/image_hosting/2w9mf0cx.png)

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,mx,a,b;
signed main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>a>>b;
		ans+=a;//加身体的和的高度
		mx=max(mx,b-a);//求出最大头的高度
	}
	cout<<ans+mx;//最后加和
	return 0;
}
```

**警钟敲烂：不开 long long 见祖宗！！**

---

## 作者：spfa_ (赞：7)

[[ABC352C] Standing On The Shoulders](https://www.luogu.com.cn/problem/AT_abc352_c)

最终高度显然为下面 $n-1$ 个巨人的肩膀高之和加上最上面巨人的高度，所以我们可以枚举具体是哪个巨人在最上面即可。

代码：

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

typedef vector <int> vi;
typedef pair <int, int> pii;

inline int rd() { int x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
inline ll rdll() { ll x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
template <typename T> inline void write(T x) { if (x < 0) x = -x, putchar('-'); if (x > 9) write(x/10); putchar(x%10+48); }

int main() {
	ll n, sum = 0, ans = 0; cin >> n;
	vi a(n+1), b(n+1);
	for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i], sum += a[i];
	for (int i = 1; i <= n; ++i) ans = max(ans, sum-a[i]+b[i]);
	cout << ans;
	return 0;
}
```

---

## 作者：cyx012113 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_c)

[文章传送门](https://www.luogu.com.cn/article/gmm35efq)
### 题意
有 $N$ 个巨人，分别是 $1\sim N$。当巨人 $i$ 站在地上时，他们的肩高是 $A_i$，头高是 $B_i$。

你可以根据以下规则堆叠 $N$ 个巨人：

1. 将巨人 $P_1$ 放在地上。巨人 $P_1$ 的肩膀距离地面的高度为 $A_{P_1}$，头部距离地面的高度为 $B_{P_1}$。
    
2. 按照 $i = 1\sim N - 1$ 的顺序，把巨人 $P_{i + 1}$ 放在巨人 $P_i$ 的肩膀上。如果巨人 $P_i$ 的肩膀距离地面 $t$，那么巨人 $P_{i + 1}$ 的肩膀距离地面就是 $t + A_{P _{i + 1}}$，他们的头距离地面的高度就是 $t + B_{P_{i + 1}}$。

求最顶端巨人头部距离地面的最大高度 $P_N$。
### 题目分析
首先，瞄一眼题意，发现要求最顶端巨人头部距离地面的最大高度：妥妥的贪心！

接着，瞄一眼数据大到离谱的样例三：**要开 long long！**

**十年 OI 一场空，不开 long long 见祖宗。**
### 贪心策略
贪心策略的核心在于优先选择那些肩高和头高差最小的巨人放置在前面：
1. **主要关键字**：肩高与头高的差值（$B_i - A_i$）：
   - 选择肩高与头高差值最小的巨人放置在前面，有助于在后续巨人的堆叠过程中提供更高的基座。
2. **次要关键字**：肩高（$A_i$）：
   - 在肩高与头高差相等的情况下，选择肩高较小的巨人放置在前面，同样有助于提高后续巨人的基座。
### 贪心策略的证明
**_贪心算法并不难，难的是证明。_**

为了证明贪心策略的正确性，可以使用**交换证明法**：
- 考虑任意两个相邻的巨人 $P_i$ 和 $P_{i+1}$，我们希望调整它们的顺序，以达到更高的头部高度。
- 如果 $B_{P_i} - A_{P_i}>B_{P_{i+1}} - A_{P_{i+1}}$，将其交换可以降低基座高度，从而有利于后续堆叠。
- 如果 $B_{P_i} - A_{P_i}=B_{P_{i+1}} - A_{P_{i+1}}$，比较 $A_{P_i}$ 和 $A_{P_{i+1}}$ 来决定顺序，同理，这样有利于后续堆叠。
   
**贪心成立。**

通过以上的贪心策略，可以确保在每一步都为后续的巨人提供更高的基座，从而最终达到最顶端巨人头部距离地面的最大高度。
### 代码实现
友情提醒：题解千万条，理解第一条。直接粘题解，棕名两行泪。
#### 原始代码
```cpp
#include <bits/stdc++.h>
#define int long long // ans太大，不开 long long 会爆
using namespace std;

struct s { // 结构体，存储巨人的肩高及头高
	int a, b;
}a[200002];

bool cmp(s x, s y) { // 贪心+快排
	if (x.b - x.a != y.b - y.a) return x.b - x.a < y.b - y.a;
    // 核心部分：双关键字快序
	return x.a < y.a;
    // 如果肩与头的高度差更大，则排在前面；
    // 如果高度差相等，则按肩高排序
}

signed main() {
	int n, ans;
	cin >> n;
	for (int i = 1;i <= n;i++) cin >> a[i].a >> a[i].b;
	if (n >= 1) ans = a[1].a;    // 特判n == 1的情况
	else  {
		ans = a[1].b;
		cout << ans << endl;     // n == 1，直接退出
      return 0;
	}
	sort(a + 2, a + 1 + n, cmp); // 贪心走起
	for (int i = 2;i <= n;i++) ans += a[i].a;    // 累加高度
	ans += a[n].b - a[n].a;      // 加上头高
	cout << ans << endl;         // 输出
    return 0;
}
```
代码有点长，我们可以根据代码进行缩短（改良）。
#### 缩短后的代码
```cpp
#include <bits/stdc++.h>
using namespace std;

long long n, ans = 0, maxn = 0;

int main(){
	cin >> n;
	while (n--) { // 压行小技巧
		long long a, b;
		cin >> a >> b;
		ans += a;
		maxn = max(maxn, b - a);
	}
	cout << ans + maxn << endl;
	return 0;
}
```
可能这只是其中的一种贪心策略，但还是可以勉勉强强通过的喵~。

> Update 7.31：
> - 针对[《洛谷主题库题解规范》](https://help.luogu.com.cn/rules/academic/solution-standard)进行修改；
> - 对于未完全修改的代码进行修改；
> - 删除多余的内容。

---

## 作者：chinazhanghaoxun (赞：6)

### ~~这道题其实挺水的~~
题意其实就是每个巨人都踩在下面一个人的肩上，那就是中间的人的头的高度是不被计算在总高度内的。那我们仔细想一想，会发现其实每个巨人的身体的高度都是在总高度内的，只是不同的站法会影响最上面一个巨人的头高度。

我们就可以用一个变量计算一下所有巨人身体的高度之和，再用一个 $\text{mx}$ 变量求出最长的头的高度，及最后输出所有身体的高度和最长的头的高度之和就是答案了，接下来直接看代码吧。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
//注意所有数据加起来有可能会爆 int，记得开 long long
ll n,x,mx=-1e7;// x 表示身体加起来高度,mx 为最高的头 
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		ll a,b;
		scanf("%lld%lld",&a,&b);
		x+=a;//对所有身体求和
		b-=a;//算出这一位巨人头的高度
		mx=max(mx,b);//记录最高的巨人的头
	}
	printf("%lld",x+mx);//输出答案
	return 0;//完结撒花~~
}
```
本蒟蒻第一次发题解，不足之处请大家提出

~~希望管理员大大通过本题解~~

---

## 作者：fengzhaoyu (赞：5)

## 题意
有 $n$ 个巨人，肩高和身高分别是 $a[i]$，$b[i]$。一个巨人能踩再临一个巨人的肩膀上，求他们叠起来最高高度。
## 思路
由题可知，只有最上面的巨人才算身高，其余都算肩高，所以先算出肩高。再遍历每一个巨人：如果把它当作最上面的，即肩高和减去当前肩高再加身高，是否最大。
```cpp
for(int i=1;i<=n;i++){
		long long s=ans-a[i]+b[i];
		maxx=max(maxx,s);}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/xofwj4lm.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200001],b[200001];
int main()
{
	int n;
	long long ans=0,maxx=-1;// ans 存肩高和，maxx 存答案
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		ans+=a[i];
	}//读入
	for(int i=1;i<=n;i++)
	{
		long long s=ans-a[i]+b[i];
		maxx=max(maxx,s);
	}//求最大身高
	cout<<maxx<<endl;
	return 0;
 } 
```

---

## 作者：2023fyc (赞：5)

## 正解
由于每个巨人只能站在另一个巨人的肩膀上，所以只有每个巨人肩膀到地面才算到总高度里（除了最上面的巨人）。所以我们只需要枚举所有巨人，用这个巨人头高度加上剩余巨人的肩膀高度得到一个数，再在这些数中取最大值，就搞定了。
## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],b[200005];
long long s,mx;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		s+=a[i];
	}
	for(int i=1;i<=n;i++) if(mx<s-a[i]+b[i]) mx=s-a[i]+b[i];//找最大值
	cout<<mx;
	return 0;
}
```

---

## 作者：Xzf110618 (赞：4)

### 题目
给出 $n$ 个巨人，第 $i$ 个巨人的肩高为 $a_i$，头高为 $b_i$，将所有巨人叠在一起，上面的巨人踩在下面巨人的肩上，求最上面的巨人的头离地面有多高。
  
### 分析
由于肩高和不会变，所以为了使最上面的巨人的头离地面最高，要让最上面的巨人的头高与肩高之差最大。
  
### 代码
```
#include<bits/stdc++.h>
using namespace std;
long long c,a[200005],b[200005],ss,mx=-1;//记得给 mx 赋一个极小值 
int main()
{
	cin>>c;
	for(int i=1;i<=c;i++)
	{
		cin>>a[i]>>b[i];
		ss+=a[i];//求肩高之和 
		mx=max(mx,b[i]-a[i]);//找最大的头高与肩高之差 
	}
	cout<<ss+mx;
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

# 题意

最大化这个式子的值：

$$\sum\limits^{n}_{i=1} a_i\times (i\not = k)+ b_k ，k\in [1,n]$$

# 思路

考虑贪心，枚举 $k$，取最大值即可。

```cpp
#include<bits/stdc++.h>
#define sd std::
#define int long long
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
const int N=2e5+10;
int n,sum;
int a[N],b[N];
il void solve()
{
	n=read();
	F(i,1,n) a[i]=read(),b[i]=read(),sum+=a[i];
	int ma=0;
	F(i,1,n)
	{
		ma=MAX(ma,sum-a[i]+b[i]);
	}
	put(ma);
}
signed main()
{
    int T=1;
//    T=read();
    while(T--) solve();
    return 0;
}

```

---

## 作者：Roronoa__Zoro (赞：3)

### 题意
给你巨人个数 $n$ 和肩高 $A$ 与头高 $B$，让你求这些巨人叠罗汉后最上面的巨人的头距离地面的高度的最大值。

### 做法
巨人叠罗汉都是第一个巨人踩地上后面的巨人踩在前一个巨人的肩膀上，这样从地面到最上面巨人的肩膀的高度为 $A_1+A_2+A_3\cdots+A_n$，这时就只差了一个头高，题中头高 $B_i$ 表示的是头到地面的距离，此中包含了肩高，故需要减去肩高，即 $B_i-A_i$，而每个巨人的头有长有短~~十分有趣~~，需要算出来挨个比较求头最长的那个，最后相加求和。

### 具体代码

光看上面的做法可能会有点乱，我们来分步处理一下。

1. 求所有巨人的肩高。

```cpp
for(int i=1;i<=n;i++)
{
	m+=a[i];//m表示肩高
}
```
2. 求最长的头长。

```cpp
for(int i=1;i<=n;i++)
{
	maxx=max(b[i]-a[i],maxx);//maxx表示最长头长
   //b[i]-a[i]表示每个头的长度
}
```
3. 最后相加。

```cpp
m+=maxx;
```
### 完整代码

将以上代码合并即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200010],b[200010],maxx;
int m;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		maxx=max(b[i]-a[i],maxx);//最长头长
		m+=a[i];//肩高求和
	}
	m+=maxx;
	cout<<m;
	return O;//反作弊
}
```
复制加粘贴，棕名两行泪。

---

## 作者：Pink_Cut_Tree (赞：3)

# AT_abc352_c [ABC352C] Standing On The Shoulders 题解

### 解析

可以观察出来，后面的巨人踩着前面的巨人的肩膀，所以头到肩膀的这部分距离就浪费了。

所以我们对巨人排序，关键字为头到肩膀的距离。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n;
struct giant{
	int a,b;
	friend bool operator<(giant x,giant y){
		return x.b-x.a<y.b-y.a;
	}
}g[N];
long long ans;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>g[i].a>>g[i].b;
	}
	sort(g+1,g+n+1);
	for(int i=1;i<n;i++){
		ans+=g[i].a;
	}
	ans+=g[n].b;
	cout<<ans;
return 0;
}
```

### 题外话

好像大家普遍反映这场比赛简单，怎么就我感觉略难啊……幸亏我没打，不然就真的下大分了！

---

## 作者：what_can_I_do (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc352_c)

设 $S=\sum_{i=1}^n a_i$，则显然如果让第 $i$ 个巨人站在最顶上，他贡献的高度就变成了头到脚的高度，所以这个时候与地面的距离为 $S-a_i+b_i$。

所以只需要先处理出 $S$，然后枚举每一个 $i$ 直接计算与地面的距离，取最大值即可。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
struct aaa
{
	ll x,y;
}a[200010];
ll ans=0;
int main()
{
	ll sum=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y,sum+=a[i].x;
	for(int i=1;i<=n;i++)
		ans=max(ans,sum-a[i].x+a[i].y);
	cout<<ans;
	return 0;
}
```

---

## 作者：ANDER_ (赞：2)

## 思路
对于每一个巨人，若他不是叠在最上面的那个。那么他对整体的贡献就是他肩膀的高度（即 $a_i$ ）。只有叠在最上面的巨人，对整体的贡献才会是其头的高度（即 $b_i$ ）。

如果我们选择一个巨人做叠在最上面的那个，那么他会给整体贡献 $b_i$ 的高度，带来的后果就是他的 $a_i$ 将会被舍去。我们贪心地考虑，如何使整体高度最大呢？**我们需要在找出尽可能大的 $b_i$ 的同时，让其的 $a_i$ 尽量小**。实现也很简单，我们只需要计算出每个巨人的 $a_i$ 与 $b_i$ 的差，然后排序。让差值最大的巨人叠在最上面，之后模拟计算，输出。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, maxx, tic, ans; 
struct node {
	int a, c;
}arr[200005];
inline bool cmp(node x, node y) {
	return x.c < y.c;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i = 1, b ; i <= n ; i ++) {
		cin>>arr[i].a>>b;
		arr[i].c = b - arr[i].a;
	}
	sort(arr + 1, arr + n + 1, cmp);
	for(int i = 1 ; i < n ; i ++) {
		ans += arr[i].a;
	}
	cout<<ans + arr[n].a + arr[n].c;
	return 0;
}
```
求过 %%%%%

---

## 作者：RioFutaba (赞：1)

~~感觉这次的 c 题有点水啊。~~

显而易见，因为每个巨人都站在下面一个巨人的肩膀上，所以如果确定了前 $n-1$ 个巨人的序号，那么他们堆叠在一起的高度也是确定的，即这 $n-1$ 个巨人的肩离地面的高度的和，与他们的排列顺序无关。

那么某一种堆叠方式的最终高度只和最上面的巨人有关。设最上面的巨人为第 $i$ 个巨人，其它所有巨人的肩高和为 $m$。那么最终答案就是 $\max(m-a_i+b_i)$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
long long a[200005],b[200005],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i],&b[i]);
		a[0]+=a[i];
	}
	for(int i=1;i<=n;i++) ans=max(ans,a[0]-a[i]+b[i]);
	printf("%lld\n",ans);
	return 0;
} 	
```

---

## 作者：AK_400 (赞：1)

# [Standing On The Shoulders](https://atcoder.jp/contests/abc352/tasks/abc352_c) 题解
我们发现最终高度就是所有人的肩高加上最上面的人的头高。所以我们让头高最高的在最上即可。
# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200005],b[200005],mx=0,ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        mx=max(mx,b[i]-a[i]);
        ans+=a[i];
    }
    cout<<ans+mx;
    return 0;
}
```

---

## 作者：Cosine_Func (赞：1)

考虑暴力枚举选择 $B$ 数列的一个值。时间复杂度 $O(n)$

核心代码如下：
```cpp
cin>>n;
for(itn i=1;i<=n;i++)
	cin>>a[i]>>b[i],sa+=a[i];
for(int i=1;i<=n;i++)
	ans=max(ans,sa-a[i]+b[i]);
cout<<ans;
```

---

## 作者：dwr_2011 (赞：1)

## 题意
有 $n$ 个巨人，分别给你每个巨人肩膀到地的距离以及头到地的距离，如果第 $i$ 个巨人踩在第 $l$ 个巨人上，那么第 $i$ 个巨人的头离地面的距离是第 $l$ 个巨人的肩高加上 $i$ 个巨人的头高。
## 思路
我们可以发现是只有最顶层的巨人头的高度是有用的，所以我们可以把所有巨人的肩高加起来，然后再加上头的高度最高的巨人的头高。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	long long a,b,c;
}a[200010];
bool cmp(node a,node b)
{
	return a.c>b.c;
}
int main()
{
	int n;
	long long ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].a>>a[i].b;
		a[i].c=a[i].b-a[i].a;
	}
	sort(a+1,a+n+1,cmp);//头高最高的会排前面
	for(int i=1;i<=n;i++)
	{
		ans+=a[i].a;
	}
	cout<<ans+a[1].b-a[1].a;
	return 0;
}

```

---

## 作者：codingwen (赞：1)

注意到所有人的身高除了最后一个人的之外其他的只算肩膀的高度，所以可以在所有人的头高中去最大值，最后加上就行了。

注意：因为在算和的时候把那个也把放在最顶上的人的肩高加进去了，所以取最大时要用头高减去肩高。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int n;
	cin>>n;
	int ans=0,mx=0;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		ans+=x;
		mx=max(mx,y-x);
	}
	cout<<ans+mx;
	return 0;
}
```

---

## 作者：wfirstzhang (赞：1)

# ABC352C
## 题目简化版
有 $N$ 个巨人叠罗汉，第 $i$ 个巨人头高 $B_i$，肩膀高 $A_i$。

这些巨人叠起来的高度是**最上面巨人的头高**和下面**其它巨人的肩高之和**的和。

求这些巨人叠起来的最大可能高度。

## 思路
### 分析题面
这些巨人叠起来的高度只与**最上面巨人**的选择有关。

因为只要确定最上面的巨人，无论其它巨人是如何排列的，肩高之和都是一定的。
### 算法分析
根据上文的分析，考虑枚举最上面的巨人。建立一个变量记录最大值，枚举到比最大值大的就更新。
### 预处理方式
如果每枚举到一个巨人都要计算下面所有巨人的肩高之和，那么总的时间复杂度为 $\Theta(N^2)$，容易超时。

依据题面，以第 $i$ 个巨人为最上方的总高度 $H_i$ 为 $B_i$ 与其它巨人的肩高之和。其它巨人的肩高之和又可以分解为全部巨人的肩高之和减去 $A_i$，得到式子：

$$
H_i = B_i + \sum_{j=1}^{j\le n}{A_j} -A_i 
$$

可以建立一个变量表示所有巨人的肩高之和，每次使用时就可以 $\Theta (1)$ 查询其它巨人的肩高之和，总时间复杂度 $\Theta(N)$。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
struct giant { //结构体，也可不用
	long head, should;
} Ar[500000];
int main() {
	long N, ans = 0, max_Ans = 0, sum = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> Ar[i].should >> Ar[i].head;
		sum += Ar[i].should; //计算肩高总和
	}
	for (int i = 0; i < N; i++) {
		long tempAns = sum - Ar[i].should + Ar[i].head;
      		//求该排列方式下的总高度
		max_Ans = max(tempAns, max_Ans);
      		//如果超过最大值，那么更新最大值
	}
	cout << max_Ans << endl;
	return 0;
}

```

---

## 作者：SkyLines (赞：1)

## Translate

有 $N$ 个人，第 $i$ 个人肩高 $A_i$，头高 $B_i$。

将这 $N$ 个人按照任意一种方案排序，设第 $i$ 个人现在的头高 $P_i$ 为 $\sum_{i=1}^{n-1}A_j+B_i$，使得 $P_N$ 最大。

## Solution

因为 $P_N$ 只和之前的 $A_j$ 和 $B_i$ 有关，所以之前的人无论怎么排，都不会影响 $P_N$。可以直接算出当第 $i$ 个人排到最后的时候，此时 $P_N$ 的值。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll max_(ll aa, ll bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
int pow_(int aa, int bb, int cc){
	int ans = 1;
	while(bb){
		if(bb & 1) ans = ans * aa % cc;
		aa = aa * aa % cc;
		bb >>= 1;
	}
	return ans;
}
const int N = 2e5 + 5;
int n;

ll ans, tota;
struct node{
	int a, b;
} edge[N];
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &edge[i].a, &edge[i].b);
		tota += edge[i].a;
	}
	for(int i = 1; i <= n; i++){
		ans = max_(ans, tota + (ll)(edge[i].b) - (ll)(edge[i].a));
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：OIer_Tan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_c)

## 题意

有 $N$ 个巨人，他们分别标号为 $1\sim N$。当巨人 $i$ 站在地上时，他们的肩高是 $A_i$，头高是 $B_i$。

你可以将他们任意排列，然后把巨人一个一个叠到肩上。

求最上面的巨人 $P_N$ 的头部距离地面的最大可能高度。

## 思路

显然，一次只可能有一个巨人算头的高度，而下面的顺序是无关紧要的。所以我们另 $k\gets \sum^N_{i=1}a_i$，然后枚举 $i$，则第 $i$ 个巨人在顶部的总高度为 $k-a_i+b_i$，每次更新答案即可。

时间复杂度为 $O(N)$。

## 代码

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll n ;

struct man 
{
	ll a , b ;
} p [N] ;

ll sum , maxn ;

int main ()
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> p [i].a >> p [i].b ;
		sum += p [i].a ;
	}
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		maxn = max ( maxn , sum - p [i].a + p [i].b ) ;
	}
	cout << maxn << endl ;
	return 0 ;
}
```

---

## 作者：zzhbpyy (赞：1)

### [原题传送门](https://www.luogu.com.cn/problem/AT_abc352_c)

## 思路

最上面巨人头顶的高度就是所有巨人肩高之和加上最上面巨人头顶到肩膀的高度差。由于肩高之和是固定的，故只须让最上面的巨人头顶到肩膀的高度差最大。所以答案为 $(\sum\limits_{i=1}^{N}A_i)+\max(B_i-A_i)$。

## 代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005],b[200005],ans,res;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i],ans=max(ans,b[i]-a[i]),res+=a[i];
	cout<<res+ans;
}
```

---

## 作者：Tjaweiof (赞：1)

# AT_abc352_c 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_c)

首先，考虑到所有巨人的肩膀都必须加入答案，这一部分是固定的。题目让我们选择更高的方案，我们就考虑最上方的部分：最上方有一小部分是某个巨人的 $b_i-a_i$，那么我们找出 $\max b_i-a_i$，输出 $\sum_{i=0}^n a_i+\max b_i-a_i$ 即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FIRE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int n;
long long a, b, sum, maxn;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	while (n--){
		cin >> a >> b;
		sum += a;
		maxn = max(maxn, b - a);
	}
	cout << sum + maxn;
    return 0;
}

```

---

## 作者：L_xcy (赞：1)

[[ABC352C] Standing On The Shoulders](https://atcoder.jp/contests/abc352/tasks/abc352_c)



------------


#### 题目大意

给你一个正整数 $N$ $ (2 \le N \le 2 \times 10 ^ 5 )$ 和 $a[i]$ 和  $b[i]$ $( 1 \le  i \le N )$ $(1 \le a[i] \le  b[i] \le 10^9)$。

让你找一个 $i$ $( 1 \le  i \le N )$，使得
$$a[i]- b[i] + \sum_{j=1}^{N} b[j] $$
最小。


------------

#### 解题思路
暴力解法（不能拿满分）：我们可以枚举每一个 $i$，再每次都枚举 $j$，可以得到结果，但时间复杂度是 $O(N^2)$。

正解：可以发现每次不同的 $i$ 改变只是上文公式中 $a[i]-b[i]$ 的值，不改变
$$ \sum_{j=1}^{N} b[j] $$
的值，也就是说我们可以用 $O(N)$ 的时间预处理这个值，然后在枚举 $i$ 时直接使用。 

正解时间复杂度是 $O(N)$。

记得开 `long long`。


------------
#### code

```cpp
#include<bits/stdc++.h>

using namespace std;

long long n,a[200005],b[200005],s,ans;

int main() {
	//输入 
	scanf("%lld",&n);
	
	for(int i = 1;i <= n; i++) {
		scanf("%lld %lld",&a[i],&b[i]);
	}
	//预处理 s 
	for(int i = 1;i <= n; i++) {
		s += a[i];
	}
	//枚举求值 
	for(int i = 1;i <= n; i++) {
		ans = max(ans,s-a[i]+b[i]);
	}
	//输出 
	printf("%lld",ans);
	
	return 0;
}
```

---

## 作者：_xdd_ (赞：1)

先把所有巨人肩膀离**地面**的高度加起来，最后加上最大的头离**肩膀**的高度即可。可以用一个变量在输入时就打擂台寻找最大值，最后与肩的高度总和相加。

```
#include<iostream>
using namespace std;
long long n,maxn,sum,x,y;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x>>y;
        sum+=x;
        maxn=max(maxn,y-x);
    }
    cout<<sum+maxn;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：1)

很显然，只有最上面的巨人才会算进所有身高，所以先把从肩膀到脚的高度全部加起来，然后再算出从肩膀到头的高度的最大值加上就可以了。

还是很简单的，代码不放了。

---

## 作者：___Furina___ (赞：1)

### 题意简述：
有 $n$ 个巨人，需要你以某种顺序叠起来。某个巨人只能踩在地面上或者另一个巨人的肩上。现在给定你所有巨人站在地面上时的肩离地面的高度 $A_i$ 和头顶离地面的高度 $B_i$，求把所有巨人叠起来后的高度最大值。
### 题解：
容易发现，每一个巨人的肩高 $A_i$ 是一定有贡献的，而总高度比巨人的肩高和多了一个头到肩的距离，所以问题转化为了找头肩差最大的巨人。
### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,z,n,maxn;
long long ans;//开longlong
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>x>>y;
    	maxn=max(y-x,maxn);//找最大值
    	ans+=x;
	}
	cout<<ans+maxn;//输出答案
    return 0;//完结撒花
}

```
点个赞再走！

---

## 作者：n_ni (赞：0)

## 题目大意
有 $N(N \le 2 \times 10^5)$ 个巨人，巨人 $i$ 站在地面上时，肩高为 $A_i$，头高为 $B_i$。你可以将某个巨人放在另一个巨人的肩膀上。你要把这些巨人都叠起来，最上面巨人的头顶离地面的高度最大是多少？
## 思路
此题可用贪心求解。

将头高与肩高之差最大的巨人放在最高处即可。
### 推导
设将第 $i$ 个巨人放在最高处的高度大于将第 $j$ 个巨人放在最高处的高度。
$$
\begin{aligned}
A_1+A_2+\dots+A_N-A_i+B_i &> A_1+A_2+\dots+A_N-A_j+B_j\\
-A_i+B_i &> -A_j+B_j &\text{（两边同时减去} A_1+A_2+\dots+A_N \text{）}\\
B_i-A_i &> B_j-A_j &\text{（加法交换律）}
\end{aligned}
$$
易得需要把头高与肩高之差最大的巨人放在最高处。

## Code
``` cpp
#include<iostream>
#define ll long long
#define Max(x,y) (x)>(y)?(x):(y)
using namespace std;

ll a[200010],b[200010],ma,sum;

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%lld%lld",&a[i],&b[i]);
        sum+=a[i];
        ma=Max(b[i]-a[i],ma);//求头高与肩高之差的最大值
    }
    printf("%lld",sum+ma);//肩高之和加头高与肩高之差的最大值（加头高与肩高之差最大值是把最高处的巨人的头加上）
    return 0;
}
```

---

## 作者：Hughpig (赞：0)

> 如果说我看得更远，那就是因为站在巨人的肩膀上。——牛顿

考虑除了最顶端的巨人 $P_N$ 之外，其他巨人对答案的贡献都是他们的肩膀高度；而巨人 $P_N$ 对答案的贡献是他的头的高度。

可以把答案看作每个巨人都贡献了肩膀高度，巨人 $P_N$ 额外贡献了头部高度减去肩膀高度。

所以不管如何排列 $P$，所有巨人的肩膀高度和不变，所以要让答案最大，就要让顶端的巨人的头部高度减去肩膀高度的差最大。

因此只要最大化 $B_{P_N}-A_{P_N}$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,a[200007],b[200007],s,d;

int main()
{
    cin>>n;
    for(int i=0;i<n;++i)cin>>a[i]>>b[i],s+=a[i],d=max(d,b[i]-a[i]);
    cout<<s+d;
}
```

---

## 作者：Lame_Joke (赞：0)

- ### 大体思路
	题目大意有了就不说了。我们知道巨人的身高不可能是负数，所以肩膀到地板的距离就可以全部累加。这一定是最优的，然后我们考虑头，头最长的一定要在最上面，也就是将头部到地板的距离减去肩膀到地板的距离取最大值，再将这个最大值与肩膀到地板的距离和加起来就能得到最终答案。

- ### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200005],b[200005];
int main()
{
	scanf("%lld",&n);
	long long maxx=-1e10,ans=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i],&b[i]);
		maxx=max(b[i]-a[i],maxx);
		ans+=a[i];
	}
	printf("%lld",ans+maxx);
}

---

## 作者：Elysian_Realme (赞：0)

# ABC352_C

## 解题思路

显然，这道题可以直接递推求。

如果令不考虑谁放在最上面的答案为基础，那么总的结果就是 $a$ 中所有数的和。

接下来，很容易想到我选择 $i$ 作为头顶的所产生的额外贡献为 $b_i-a_i$。所以我们可以枚举 $i$ 直接求该额外贡献的最大值。

代码：
```cpp
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		a[i]=read(),b[i]=read(),
		sum+=a[i],d=max(d,b[i]-a[i]);
	cout<<sum+d;
	return 0;
}
```

---

## 作者：qhr2023 (赞：0)

## 题意

有 $n$ 个人叠在一起（一个踩在下一个的肩上），求 $n$ 个人叠的最高高度。

## 思路

小贪心，通过题意和样例，我们知道答案就是最上面的人的头高加上下面 $n-1$ 个人的肩高和，可以转化为 $n$ 个人的肩高和加上最上面那个人的头高与肩高的差。

我们用 $s$ 累加肩高，$mx$ 找头高与肩高的最大差，这样数组都不用开。

**注意**：数据范围很大，要开 long long。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long s, n, a, b, mx;
int main(){
	cin >> n;
	while(n--)
		cin >> a >> b,
		s+=a,
		mx=max(mx, b-a);
	cout << s+mx;
	return 0;
}
```

---

## 作者：Happy_Doggie (赞：0)

## 题目大意
意思就是说有 $N$ 个巨人，每个巨人踩在下面那个巨人的肩上（叠罗汉呗），第 $i$ 个巨人的肩高是 $A_i$ ，头高是 $B_i$ 。每个巨人只能踩在前一个巨人的肩上，求第 $N$ 个人的头高。
## 思路
直接先把所有巨人的肩高加起来，在枚举每一个巨人都站在最上面。

比方说第1个巨人站在最上边，那他的头高就是 `sum - a[1] + b[1]` 。有 `for` 循环枚举每一个人，假设他们站在最高点，求一下最大值即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int a[N], b[N];
int n;
int main()
{

    cin >> n;
    long long sum = 0, ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i] >> b[i];
        sum += a[i];
    }
    for (int i = 0; i < n; i++)
    {
        ans = max(ans, sum - a[i] + b[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Tachibana27 (赞：0)

或许只是下位橙难度？

------------
### 题意

给定长度为 $n$ 的数列 $a,b$，希望你选择一个 $i$，使得 $b_{i}+\sum \limits _{j=1}^{n}[j\neq i]\times a_j$ 最大。

### 思路

不妨直接考虑暴力算法,枚举所有的 $i$，并暴力求和取最大值，时间复杂度 $O(n^2)$。

可以将 $\sum \limits _{j=1}^{n}[j\neq i]\times a_j$ 写成 $(\sum \limits _{j=1} ^n a_j)-a_i$，预处理出 $\sum \limits _{j=1} ^n a_j$ 即可，复杂度 $O(n)$。

code:

```cpp
int n; 
int a[200086];
int b[200086];
int sum;
int ans;
signed main(){
	std::cin>>n;
	for(int i=1;i<=n;i++){
		std::cin>>a[i]>>b[i];
		sum+=a[i];//sum即预处理出的和
	}
	for(int i=1;i<=n;i++)
		ans=std::max(ans,sum-a[i]+b[i]);//最大值
	std::cout<<ans;
	return 0;//撒花
}
```

---

## 作者：FreedomKing (赞：0)

简单题，难度顶多橙。

### 题目大意

有 $n$ 个巨人，每个巨人给出 $a_i,b_i$ 分别代表他的肩和头距离地面的高度，每个巨人可以站在另一个巨人的肩上，求巨人的头最高能离地面多高。

### 思路

看到题首先可以想到一个很假的贪心，即让 $b_i$ 最高的巨人站在最顶上，答案即为 $\sum_{i=1}^n a_i+{b_{i_{mx}}}-a_{i_{mx}}$，其中 $mx$ 为 $b_i$ 最大的巨人的编号。

然而这种做法连样例都过不了。

既然贪心不行，考虑枚举站在最顶上的巨人，答案计算与上述类似，为 $\max_{i=1}^n\{\sum_{j=1}^na_j+b_i-a_i\}$。

显然最顶上的巨人固定后，下面的巨人无论如何排列答案都不变。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int xN=1e7+5,N=1e6+5,mN=2e3+5,mod=1e9+7;
namespace FreedomKing_qwq{
	//#define lc (p<<1)
	//#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int abss(int x){return (x>=0?x:-x);}
	inline int lowbit(int x){return (x&-x);}
}
struct node{
	int a,b;
}f[N];
signed main(){
	int n=qr,sum=0;
	for(int i=1;i<=n;i++){
		f[i].a=qr;f[i].b=qr;
		sum+=f[i].a;
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,sum-f[i].a+f[i].b);
	qw(ans);
	return 0;
}
```

---

## 作者：haokee (赞：0)

能够发现，下面的 $n-1$ 个巨人都被踩着肩膀，也就是贡献出肩膀的高度，只有最上面的巨人才能贡献出头的高度。因此，我们可以枚举哪一个巨人站在最上面，那么就需要计算其他巨人肩膀的高度和他自己头的高度之和。

如何计算其他巨人的肩膀高度之和呢？可以先将所有巨人的肩膀高度之和加起来，然后再减去枚举的巨人的肩膀高度，就能够得到其他巨人的肩膀之和了。

```
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 5;

long long a[kMaxN], b[kMaxN], n, sum, ans;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
    sum += a[i];
  }
  for (int i = 1; i <= n; i++) {
    ans = max(ans, sum - a[i] + b[i]);
  }
  cout << ans << '\n';
  return 0;
}
```

还有另外一种思路，那就是所有巨人都贡献了自己肩膀的高度，但是会有唯一的一个巨人不仅贡献了肩膀，还贡献了肩膀距离头部的那段距离。因此，我们也可以先将所有巨人的肩膀高度加起来，然后枚举一个最高的肩膀距离头部的那段距离。但是代码写起来是一样的，在此就不重复了。

---

## 作者：Special_Tony (赞：0)

# 思路
这是本人遇到的最简单 ABC-C。

$n$ 个巨人叠罗汉，其实就是所有巨人的肩膀高度加最上面的头高度，即 $\sum a_i+b_n-a_n$，要使高度最大，就选择头最长的巨人在最上面，即 $\sum a_i+\max(b_i-a_i)$。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, x, y, maxx;
ll sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	while (n --)
		cin >> x >> y, sum += x, maxx = max (maxx, y - x);
	cout << maxx + sum;
	return 0;
}
```

---

## 作者：Leo2011 (赞：0)

考场憋了很久，最后代码贼短……

------------

理想状态下，直接全排列解决问题。但是，$1 \le n \le 2 \times 10^5$，明显 TLE，试都不用试的。

咋优化呢？

其实，前面的巨人只负责“打地基”，作为“塔尖儿”的巨人有且仅有 1 个。而前面地基随便排列，地基高度（他们的和）都不会变。所以，我们只需要枚举塔尖即可。塔尖儿定了，下面的地基高度也就定了。

然后，又是一个问题——求和！理论来讲，最最暴力的方法就是一层循环。但是，一层循环时间复杂度为 $\Theta(n)$，联合上枚举塔尖的循环，时间复杂度为 $\Theta(n^2)$，又 TM 挂了……

这里，我们可以采用一种类似前缀和的思想：用一个 变量 $sum$（学名叫**累加器**） 来记录 $A$ 的总和，然后算去掉塔尖（$P_i$）的时候，答案就是 $sum - A_{P_i} + B_{P_i}$。这个操作，时间复杂度显然为 $\Theta(1)$，算上循环为 $\Theta(n)$，明显可以。

------------

赛场ACCode：
```cpp
// Problem: C - Standing On The Shoulders
// Contest: AtCoder - AtCoder Beginner Contest 352
// URL: https://atcoder.jp/contests/abc352/tasks/abc352_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

/*Code by Leo2011*/
#include <bits/stdc++.h>

#define log printf
#define EPS 1e-8
#define INF 0x3f3f3f3f
#define FOR(i, l, r) for (ll(i) = (l); (i) <= (r); ++(i))
#define IOS                      \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);            \
	cout.tie(nullptr);

using namespace std;

typedef __int128 i128;
typedef long long ll;
typedef pair<ll, ll> PII;

const ll N = 2e5 + 10;
ll n, mx = -INF, sum1;
PII g[N];  // pair 可以把两个数组怼到一块儿，具体使用方法见 https://blog.csdn.net/sevenjoin/article/details/81937695

template <typename T>

inline T read() {
	T sum = 0, fl = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T>

inline void write(T x) {
	if (x < 0) {
		putchar('-'), write<T>(-x);
		return;
	}
	static T sta[35];
	ll top = 0;
	do { sta[top++] = x % 10, x /= 10; } while (x);
	while (top) putchar(sta[--top] + 48);
}

int main() {
	n = read<ll>();  // 不开 long long 见**，别问，问就是实践出来的真知
	FOR(i, 1, n) g[i].first = read<ll>(), g[i].second = read<ll>(), sum1 += g[i].first;  // 累加器
	FOR(i, 1, n)
	mx = max(mx, sum1 - g[i].first + g[i].second);  // 上面简单的公式
	write<ll>(mx);
	return 0;
}

```

[AC 记录~](https://atcoder.jp/contests/abc352/submissions/53122314)

理解万岁！

------------

先别划走，说两件事儿。

1. 这道题可以用贪心（同学做法），但是，贪地基高度是错的，见[https://atcoder.jp/contests/abc352/submissions/53114017](https://atcoder.jp/contests/abc352/submissions/53114017)，贪心需谨慎啊！
2. 不开 long long 见**！

3. 一张~~绝世好~~很有用的图，可以收藏，拿走~![如图](https://cdn.luogu.com.cn/upload/pic/26845.png)

---

## 作者：Ivan422 (赞：0)

题目大意：有 $n$ 个巨人，肩膀高 $a_i$，头高 $b_i$。巨人可以站在上一个巨人的肩膀上，求这些巨人最多站到多高。

思路：我们会发现一个人 $b_i-a_i$ 的值越大就越不值得放在底下（浪费高度）。根据这个我们可以直接排序，再求解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=2e5+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
struct g{int a,b;}a[N];
bool cmp(g x,g y){
    return(x.b-x.a)<(y.b-y.a);
}
int n,ans;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){cin>>a[i].a>>a[i].b;}
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        if(i!=n){
            ans+=a[i].a;
        }else{
            ans+=a[i].b;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：WA2025 (赞：0)

## 题意

有 $n$ 个巨人，每个巨人的肩高为 $a_i$，头高为 $b_i$。

堆叠这 $n$ 个巨人，上面的巨人踩着下面巨人的肩膀，问最上面的巨人的头高最高为多少。

## 思路

算出这 $n$ 个巨人的肩高和，再去枚举最上面的巨人。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5 + 10;
ll a[N], b[N];

int main() {
    int n; scanf("%d", &n);

    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &a[i], &b[i]);
        sum += a[i];
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, sum - a[i] + b[i]);
    return printf("%lld", ans), 0;
}
```

---

## 作者：zhu_wen (赞：0)

## C - Standing On The Shoulders

我们可以发现，肩高每个人都是要算的，因为每个人都是踩着别人的肩，那么我们就可以贪心的想出，只要找到从头到肩最高的那个人，让他在最上面，就是我们要求的最大值。

### 代码

```cpp
fin >> n;
int maxx = 0;
fup(i, 1, n)
{
    fin >> a >> b;
    sum += a;
    maxx = max(maxx, b - a);
}
fout << sum + maxx << '\n';
```

##

---

## 作者：Angelina188 (赞：0)

#### 题目大意
将 $N$ 个巨人排列组合叠在一起，使得底下所有人的肩高 $A_i$ 的和加上最顶上人的头高 $B_i$ 最大。
#### 具体思路
输入 $A_i$ 和 $B_i$ 时用一个变量 $s$ 求所有 $A_i$ 的和，再从 $1$ 到 $N$ 循环枚举哪个巨人在最顶部，求 $s-Ai+Bi$ 的最大值。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5;
ll n,ans;
ll a[N],b[N],s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		s+=a[i];
	}
	for(int i=1;i<=n;i++)
		ans=max(ans,s-a[i]+b[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：cqbzhr (赞：0)

### 题目描述
有 $ N $ 个巨人。每个巨人都有一个名字，分别为 $ 1,\ 2,\ \ldots,\ N $，当巨人 $ i $ 站在地面上时，肩膀的高度为 $ A_i $，头顶的高度为 $ B_i $。

你可以选择对序列 $ (1,\ 2,\ \ldots,\ N) $ 进行重新排序，然后按以下规则堆叠 $ N $ 个巨人：

首先将巨人 $ P_1 $ 站立在地面上。巨人 $ P_1 $ 的肩膀高度为 $ A_{P_1} $，头顶高度为 $ B_{P_1} $。

依次将巨人 $ P_i ( i\ =\ 1,\ 2,\ \ldots,\ N\ -\ 1 ) $ 放在巨人 $ P_i $ 的肩膀上。如果巨人 $ P_i $ 的肩膀高度为 $ t $，则巨人 $ P_{i\ +\ 1} $ 的肩膀高度为 $ t\ +\ A_{P_{i\ +\ 1}} $，头顶高度为 $ t\ +\ B_{P_{i\ +\ 1}} $。

请找出站在最顶部的巨人的头顶高度（以地面为基准）的最大值。
### 解法
假设按照头顶高度从大到小的序列为 $ (P_1, P_2, \ldots, P_N) $，其中 $ P_1 $ 的头顶高度最大。那么，我们可以先依次累加每个巨人的肩膀高度，再计算累加后的头顶高度即可。
### code
```cpp
#include <bits/stdc++.h>
#define int long long//开long long。
using namespace std;
int n,ans,tot;
struct node{
	int j,t;//j为肩部高度，t为头部高度。
}a[200005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].j>>a[i].t;
		tot+=a[i].j;//累加肩部高度。
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,tot+a[i].t-a[i].j);
        //每一个巨人的头顶高度即为a[i].t-a[i].j。
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：f_hxr_ (赞：0)

### 题意

兵长利威尔~~矮之巨人~~即将来袭！为了保护后颈，巨人们建造起了 $1.7$ 米的高墙试图阻挡矮之利威尔。

不幸的是，利威尔一共有 $N$ 个。他们可以通过叠罗汉来增加高度。一个利威尔可以站在另一个利威尔的肩膀上。

现在已知每个利威尔站在地面上时，肩膀到**地面**的距离 $A_i$ 和头顶到**地面**的距离 $B_i$。现在巨人们想知道，在叠罗汉后，站在最上面的兵长**头顶到地面**的距离最高可能是多少。

### 分析

先看一个例子。假设这里有一些巨人：

![](https://cdn.luogu.com.cn/upload/image_hosting/3ukosxmg.png)

把他们随便排成一列：

![](https://cdn.luogu.com.cn/upload/image_hosting/rank8mx5.png)

把他们重排一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/dtj3eebk.png)

发现了什么？不管怎么排，躯干高度的和都是相同的！

我们只需要知道谁的头最大，让他站在最上面即可。

[AC 代码：](https://www.luogu.com.cn/record/158106560)

```cpp
#include<bits/stdc++.h>
using namespace std;
int N;
long long tot,head;
int main(){
	cin>>N;
	for(int i=1,a,b;i<=N;i++){
		cin>>a>>b;
		tot+=a;head=max(head,(long long)b-a);
	}
	cout<<tot+head;
	return 0;
}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_c)
## 思路
可以看出，当第 $i$ 个巨人在最顶端时，其高度为其余巨人的肩膀高度加上当前巨人的头部高度。
## 做法
用 $sum$ 表示所有巨人的肩膀高度和，则第 $i$ 个巨人在顶端的高度为 $sum - a_i + b_i$ 枚举求出最大值即可。  
**注意 int 存不下。**
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be(x) x.begin()
#define en(x) x.end()
using namespace std;
typedef long long LL;
typedef int I;
I n,a[200010],b[200010];
LL sum;
I main(){
	scanf("%d",&n);
	for(I i = 1;i <= n;i++){
		scanf("%d%d",&a[i],&b[i]);
		sum += a[i];
	}
	LL ans = 0;
	for(I i = 1;i <= n;i++){
		ans = max(ans,sum - a[i] + b[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：jess1ca1o0g3 (赞：0)

[Portal(AT)](https://atcoder.jp/contests/abc352/tasks/abc352_c)

[Portal(Luogu)](https://www.luogu.com.cn/problem/AT_abc352_c)

一眼贪心。

由于巨人站在巨人的肩膀上，所以所有的肩膀相加。

最后还要加上头，也就是把头和肩膀相差最大的放最上面。

[Code](https://paste.ubuntu.com/p/7xGwkgr3y4/)。

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_c)
### 思路
其实这题十分的简单，因为所有人的肩高都是需要累加的，所以最上面的人就是头高减去肩高最大的人。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct j
{
	long long b;
	long long c;
}a[200005];
bool cmp(j s1,j s2)
{
	return s1.c-s1.b<s2.c-s2.b;
}
int main()
{
	long long n;
	cin>>n;
	for (long long i=0;i<n;i++)
	{
		cin>>a[i].b>>a[i].c;
	}
	sort(a,a+n,cmp);
	long long ans=0;
	for (long long i=0;i<n;i++)
	{
		ans=ans+a[i].b;
		if (i==n-1)
		{
			ans=ans+a[i].c-a[i].b;
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目分析

通过观察题目可以得到一个结论：不管这些巨人怎么站，只要是叠在一起的，那么最顶上的巨人的头高就是所有巨人的肩高加上头高与肩高之差最大的巨人的头高与肩高之差。这样，这道题就做完了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=2e5;
int n,a[maxn+5],b[maxn+5];

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	
	ll sum=0;
	int res=0;
	for(int i=1;i<=n;i++) sum+=a[i],res=max(res,b[i]-a[i]);
	
	cout<<sum+res;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：crz_qwq (赞：0)

## 思路
- 我们可以用巨人的头距离肩膀的距离的最大值加上巨人的肩膀距离之和，就可以得出答案。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int a[N],b[N];
signed main()
{
	int n;
	cin>>n;
	int sum=0,mx=0;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i]>>b[i];
		sum+=a[i];
		mx=max(mx,b[i]-a[i]);
	}
	cout<<sum+mx;
} 
```

---

## 作者：孙轩宇 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc352_c)

## 题目大意
有 $n$ 个巨人，肩膀的高度是 $A_i$，头的高度是 $B_i$，你可以把巨人垒起来，求最上面的巨人的头离地面的高度。
## 思路
设巨人的编号从低到高依次为 ${P_1,P_2,\cdots,P_n}$，那么高度为 $\sum_{i=1}^{n-1}A_i+B_n$ = $\sum_{i=1}^{n}A_i+(B_n-A_n)$。

$\sum_{i=1}^{n}A_i$ 是固定的，所以我们要最大化 $B_n-A_n$。循环找到后加上 $\sum_{i=1}^{n}A_i$ 即可。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	long long ans = 0;
	int maxx = 0;
	for(int i = 1;i <= n;i++){
		int a,b;
		cin >> a >> b;
		ans += a;
		maxx = max(maxx,b - a);
	}
	cout << ans + maxx;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_c)

## 思路

贪心。

我们选择头高 $-$ 肩高最大的那个人当最上面的，这样可以保证底下所有人的亏损部分之和（头高 $-$ 肩高）最小，以做到总高度最大。

- 最多能达到 $2\times 10^{14}$ 的总高度，记得开 long long。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=2e5+10;
int n;
struct node{
	ll a,b,c;//a 肩高，b 头高，c 亏损。
}a[N];
bool cmp(node a,node b){return a.c<b.c;}//亏损从小到大排序。
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i].a>>a[i].b;
		a[i].c=a[i].b-a[i].a;
	}
	sort(a+1,a+1+n,cmp);
	ll ans=0;
	for(int i=1;i<n;++i)ans+=a[i].a;//前面的加上肩高，最后的是头高。
	ans+=a[n].b;
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/158053191)

---

## 作者：CheZiHe929 (赞：0)

### 简要题意

有 $n$ 个巨人，站在地面上时，巨人 $i$ 从地面到肩膀的高度为 $a_i$，从地面到头的高度为 $b_i$。将巨人站在一起，每个巨人站在另一个巨人的肩膀上（第一个巨人站在地上），求站的最高的巨人的头部距离地面的高度的最大值。

### 简要思路

贪心。

我们先考虑最终答案的组成。因为每个巨人站在另一个巨人的肩膀上，所以最终的答案为所有巨人站在地面上时肩膀到地面的高度总和加上站在最高的巨人的肩膀到头的高度。因为所有巨人站在地面上时肩膀到地面的高度总和为定值，无论怎么调换顺序都不会更改其值，所以我们只需要找出巨人头部到肩膀的高度最大值（注意，因为给定的是肩膀、头到地面的高度，所以头到肩膀的高度应该是其差值）。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Yes puts("Yes")
#define No puts("No")
const int MAXN=2e5+5;

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

int a[MAXN],b[MAXN];
int maxn=-1,ans;

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	int n=read();
	for(int i=1;i<=n;i++){
		a[i]=read(),b[i]=read();
		ans+=a[i];//肩膀高度总和 
		maxn=std::max(maxn,b[i]-a[i]);//维护头部到肩膀的高度最大值 
	}
	println(ans+maxn);

	return 0;
}
```

---

## 作者：xd244 (赞：0)

这道题的贪心策略不是很好想。

首先，我们考虑 $2$ 个巨人的情况，设两个巨人的肩膀距离地面 $4$ 和 $5$，头距离地面 $10$ 和 $8$。则它们的最高的顺序是 $(2,1)$，因为当有 $n$ 个巨人时，前 $n-1$ 个巨人贡献的高度都是肩膀，而最后一个巨人贡献的是全身体。

所以总高度可以表示为：（设有 $n$ 个巨人，第 $i$ 个巨人肩膀高 $a_i$，头高 $b_i$）

$$\sum_{i=1}^{n-1}a_i+b_n=\sum_{i=1}^{n}a_i+b_n-a_n$$

前面的 $\sum_{i=1}^{n}$ 一定是确定的，而让 $b_n-a_n$ 最大就能让总高度最大。

所以应该从小到大排序每组 $b_i-a_i$。

代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
    int a,b;
}p[200010];
bool cmp(node x,node y){
    return x.b-x.a<y.b-y.a;
}int main(){
    int n;cin>>n;
    long long sum=0;
    for(int c=1;c<=n;c++)cin>>p[c].a>>p[c].b;
    sort(p+1,p+n+1,cmp);
    for(int c=1;c<n;c++)sum+=p[c].a;sum+=p[n].b;
    cout<<sum;
}
```

---

## 作者：Dream_poetry (赞：0)

### 题意：
形式化一下，变为在序列 $B$ 中，对于任意 $1 \le i \le n$ 求 $b_i -a_i +\sum_{j=1}^{n}  a_j$ 的最大值。

### 思路：
显而易见的，我们可以在读入时处理出 $\sum_{i=1}^{n}  a_i$，然后据上面的公式，对每个人求出他在最上面时的高度，排序后输出即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
struct node{
	int a,b,zhi;
}z[500005];


bool cmp(node x,node y){
	return x.zhi>y.zhi;
}
int sum;

signed main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>z[i].a>>z[i].b;
		sum+=z[i].a;
	}
	for (int i=1;i<=n;i++){
		z[i].zhi=sum-z[i].a+z[i].b;
	}
	sort(z+1,z+n+1,cmp);
	cout<<z[1].zhi;
	
	return 0;
} 
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc352_c)
## 思路
我们可以将每一个巨人的身高重新分为两个部分：身体的部分和头的部分。我们用 $s_i$ 表示第 $i$ 个巨人身体部分的高度，用 $h_i$ 表示第 $i$ 个巨人头部分的高度。因为每一个巨人的身体部分的高一定会被算进总高度，所以可以讲 $s_i (1≤i≤n)$ 累加起来，再将所有巨人中头部分最高的再加一遍，这样就可以得到答案。

时间复杂度 $O(n)$，可以通过本题。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

struct giant
{
    int s, h;
} a[N];

int n;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)	
    {
        scanf("%d%d", &a[i].s, &a[i].h);
        a[i].h -= a[i].s; // 离散化巨人的两个部分
    }
    // 计算答案
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, 1ll * a[i].h);
    for (int i = 1; i <= n; i++)
        ans += a[i].s;
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：CuteForces (赞：0)

### 形式化题意
给定一组数对 $\{(A_1,B_1),(A_2,B_2),...,(A_N,B_N)\}$，把这些数对任意排列，使 $(\sum_{i=1}^{N-1}A_i)+B_N$ 最大。
### 思路    
将式子变一下，$(\sum_{i=1}^{N-1}A_i)+B_N=(\sum_{i=1}^{N}A_i)+(B_N-A_N)$。    
会发现，想要最大化答案，就要使 $B_N-A_N$ 最大，所以用 $O(N)$ 的解法，找到最大值就可以了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    int n,cnt=0,maxx=0;
	scanf("%lld",&n);
	for(int i=1,a,b;i<=n;i++){
	    scanf("%lld%lld",&a,&b);
	    cnt+=a;
	    maxx=max(maxx,b-a);
	}
	printf("%lld",cnt+maxx);
	return 0;
}
```

---

## 作者：Tulip_ (赞：0)

### 题意

有 $N$ 个巨人，他们的名字分别是 $1$ 到 $N$。当巨人 $i$ 站在地上时，他们的肩高是 $A_i$，头高是 $B_i$。

你可以选择 $(1, 2, \ldots, N)$ 的 $(P_1, P_2, \ldots, P_N)$ 排列组合，并根据以下规则堆叠 $N$ 个巨人：

- 首先，将巨人 $P_1$ 放在地上。巨人 $P_1$ 的肩膀距离地面的高度为 $A_{P_1}$，头部距离地面的高度为 $B_{P_1}$。

- 为了 $i = 1, 2, \ldots, N - 1$ 的顺序，把巨人 $P_{i + 1}$ 放在巨人 $P_i$ 的肩膀上。如果巨人 $P_i$ 的肩膀距离地面的高度是 $t$，那么巨人 $P_{i + 1}$ 的肩膀距离地面的高度就是 $t + A_{P_{i + 1}}$，他们的头距离地面的高度就是 $t + B_{P_{i + 1}}$。

求最上面的巨人 $P_N$ 的头部距离地面的最大可能高度。

### 思路

先求出巨人的总高度，再求出距离地面的高度就是 $t + B_{P_{i + 1}}$。

用结构体表示他们的肩高是 $A_i$，头高是 $B_i$。分别是 $x$ 和 $y$。

### 代码

结构体定义，如下。

```cpp
struct node{
	int x,y;
}a[Max];
```

一边输入，一边求出巨人的总高度，如下。

```cpp
for(int i=1;i<=n;i++) 
  cin>>a[i].x>>a[i].y,sum+=a[i].x;
```

求出距离地面的高度，如下。

```cpp
for(int i=1;i<=n;i++)
  ans=max(ans,sum-a[i].x+a[i].y);
```

整体代码，如下。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Max = 2e5 + 5;
int n,sum,ans;

struct node{
	int x,y;
}a[Max];

signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y,sum+=a[i].x;
	for(int i=1;i<=n;i++) ans=max(ans,sum-a[i].x+a[i].y);
	cout<<ans;
	return 0;
}

```

---

## 作者：yegengghost (赞：0)

由题易知，结果可转化为第一个巨人的头高加上剩下巨人的肩高，答案也就转化为第一个巨人的头高加上剩下巨人的肩高的最大值。

见到这种题要~~直接暴力~~再读下题，发现头高与肩高的差降序排列时答案最大，于是直接用排序解即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+114514; 
int n;
struct node
{
    int x,y,d;//分别指代肩高，头高；d表示这个蒟人的头高与肩高的差，便于排序 
}a[N];
bool cmp(node x,node y)
{
    return x.d>y.d;
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
	{
        cin>>a[i].x>>a[i].y;
        a[i].d=a[i].y-a[i].x;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=2;i<=n;i++)
		ans+=a[i].x;
	cout<<ans;
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题意分析
这道题大概就是在说给你 $n$ 个巨人和这几个巨人肩膀距离地面的高度和头距离地面的高度，问你怎么样堆叠巨人能够使这个“巨人塔”最高。

## 大体思路
考虑贪心，这个塔其实分为两部分，一种是最上面的巨人头，一种是在下面堆着的巨人身体，下面堆着的之间没有任何区别，所以我们就考虑让头最大的巨人在最上面，其他的在最下面即可。
题目中给的是身体的高度 $a_i$ 和整个巨人的高度 $b_i$，所以 $b_i-a_i$ 就是巨人头的高度，我们维护这样一个最大的巨人头高度 $max$，再加上所有巨人的身体高度就可以解决这个题了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200005],b[200005];
int main(){
	int n;
	cin>>n; 
	long long sum=0;
	long long maxx=0;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		sum+=a[i];//这是所有巨人身体的高度相加 
		maxx=max(maxx,b[i]-a[i]);//这是最大的巨人头 
	}
	cout<<maxx+sum;//相加即为答案 
	return 0; 
}
```
## The End.

---

## 作者：2023lpx (赞：0)

# AT_abc352_c [ABC352C] Standing On The Shoulders 题解

## 题目大意

有 $N$ 个巨人，每个的肩高为 $A_i$，头高为 $B_i$，求将所有巨人脚踩肩地叠在一起，求最高的那个巨人的头的高度。

## 思路

由于不论怎么叠，所有巨人的肩高总和都是不变的。所以要想让最高的头最高，就要让头肩的高度差最大。

找到头肩高度差最大的就行了。

## code

```cpp
#include<cstdio>
using namespace std;
int n;
int a[200001];
int b[200001];
long long ans;
void swap(int &a,int &b){
	int c=a;
	a=b;
	b=c;
}
void qsort(int l,int r){
	int i=l,j=r,mid=b[(l+r)>>1]-a[(l+r)>>1];
	while(i<=j){
		while(b[i]-a[i]<mid){
			i++;
		}
		while(b[j]-a[j]>mid){
			j--;
		}
		if(i<=j){
			swap(a[i],a[j]);
			swap(b[i],b[j]);
			i++;
			j--;
		}
	}
	if(i<r){
		qsort(i,r);
	}
	if(l<j){
		qsort(l,j);
	}
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
	}
	qsort(1,n);
	for(int i=1;i<n;i++){
		ans+=a[i];
	}
	ans+=b[n];
	printf("%lld",ans);
	return 0;
}
```

赛时一波脑残写了排序。

---

## 作者：unordered_yao (赞：0)

## 思路

1. 对于每一个巨人 $i$，我们可以先计算头的长度，也就是肩高与头高的差值 $B_i-A_i$。

2. 然后，我们可以采用贪心的思想，选择一个巨人，其差值最小，放在另一个巨人的肩膀上。这样，随着巨人的堆叠，我们能够保持较大的增长空间，从而最大化顶部巨人的头部高度。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+10;
pair<int,int> diffs[N];
signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a,b;
        cin >> a >> b;
        diffs[i] = {b-a,a};
    }
    sort(diffs, diffs+n);
    
    int height = 0;
    for (int i = 0; i < n; ++i) {
        height += diffs[i].second;
    }
    height += diffs[n - 1].first;
    cout << height;
    return 0;
}
```

---

## 作者：int_stl (赞：0)

刚开题我以为是排序，坑了我三发罚时。

不难发现，对于每种 $P$，最后一个巨人 $P_N$ 的头离地面的高度为：
$$
\sum_{i=1}^{N-1} A_{P_i} + B_{P_N}
$$

注意，$A_{P_i}$ 和 $B_{P_N}$ 是分开的。

也就是说，设 $t=\sum_{i=1}^N A_i$，我们要求的是：
$$
\max_{i=1}^N(t-A_i+B_i)
$$

枚举一下即可，时间复杂度 $O(N)$，可以轻松通过。

[Submission Link.](https://atcoder.jp/contests/abc352/submissions/53115019)

---

## 作者：volatile (赞：0)

# 大意

几个吃饱了撑的巨人在玩叠罗汉，每个人踩在前一个人的肩膀上，求这个叠罗汉最高有多高。

# 思路

直接先求出所有巨人的肩高之和，然后再一个一个枚举看加上哪一个巨人的头高最大就行了。

# 代码

```cpp
#include<iostream>
using namespace std;
int a[200005],b[200005];
int main()
{
    int n;
    long long sum=0,max=-114514;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        sum+=a[i];
    }
    for(int i=1;i<=n;i++){
        if(sum-a[i]+b[i]>max) max=sum-a[i]+b[i];
    }
    cout<<max;
    return 0;
}
```

---

## 作者：lilong (赞：0)

对于一个巨人 $i$，当他不在最上面的时候，他能贡献的高度为 $a_i$（无论他具体在哪个位置，只要不在最上面）。当他在最上面的时候，他能贡献的高度为 $b_i$，此时其他巨人能贡献的高度就如前文所述。于是就可以轮流让每个巨人在最上面，计算高度最大值即可。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

int a[1000001],b[2000001];
int n,ans,mx,s;

signed main()
{
	cin >> n;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i] >> b[i],s += a[i];
	for( int i = 1 ; i <= n ; i ++ )
		ans = max( ans , s - a[i] + b[i] );
	cout << ans;
	return 0;
}
```

---

## 作者：39xiemy (赞：0)

## 题目大意

有 $N$ 对数字 $A_i$ 和 $B_i$，在每一对 $A_i$ 和 $B_i$ 中，选取一个数求和，要求选且仅选一次 $B_i$，输出求和结果的最大值。

## 分析

由于选 $B_i$ 的次数一定为 $1$，所以可以先不选 $B_i$，算出所有 $A_i$ 的和 $sum$，为了最大化求和结果，就要使选取的 $B_i$ 对答案的贡献最大化。

如果要选取一个 $B_i$，对答案的贡献就会增加一个 $B_i$，但是与这个 $B_i$ 相对应的 $A_i$ 就不能选取，那么对答案的贡献也会减少一个 $A_i$。所以对于每个 $B_i$，对答案的贡献为 $B_i - A_i$。

然后再求出所有 $B_i - A_i$ 中的最大值，加上 $sum$ 即可得出答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,sum,mx=-1;//将求最大值的变量mx初始化为-1，就不易出错
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b;
		sum+=a;
		mx=max(mx,b-a);   //边输入，边计算sum和mx，节省时间
	}
	cout<<sum+mx;
	return 0;
}
```

---

