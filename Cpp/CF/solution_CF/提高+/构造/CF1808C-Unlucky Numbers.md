# Unlucky Numbers

## 题目描述

In this problem, unlike problem A, you need to look for unluckiest number, not the luckiest one.

Note that the constraints of this problem differ from such in problem A.

Olympus City recently launched the production of personal starships. Now everyone on Mars can buy one and fly to other planets inexpensively.

Each starship has a number —some positive integer $ x $ . Let's define the luckiness of a number $ x $ as the difference between the largest and smallest digits of that number. For example, $ 142857 $ has $ 8 $ as its largest digit and $ 1 $ as its smallest digit, so its luckiness is $ 8-1=7 $ . And the number $ 111 $ has all digits equal to $ 1 $ , so its luckiness is zero.

Hateehc is a famous Martian blogger who often flies to different corners of the solar system. To release interesting videos even faster, he decided to buy himself a starship. When he came to the store, he saw starships with numbers from $ l $ to $ r $ inclusively. While in the store, Hateehc wanted to find a starship with the unluckiest number.

Since there are a lot of starships in the store, and Hateehc can't program, you have to help the blogger and write a program that answers his question.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1808C/20c86d6a3ad44baab97e03914b693fecf3deba6f.png)

## 说明/提示

Let's look at two test examples:

- the luckiness of the number $ 59 $ is $ 9 - 5 = 4 $ ;
- the luckiness of $ 60 $ equals $ 6 - 0 = 6 $ ;
- the luckiness of $ 61 $ equals $ 6 - 1 = 5 $ ;
- the luckiness of $ 62 $ equals $ 6 - 2 = 4 $ ;
- the luckiness of $ 63 $ is $ 6 - 3 = 3 $ .

 So the unluckiest number is $ 63 $ .In the fifth test case, the unluckiest numbers are $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ , $ 7 $ , $ 8 $ , $ 9 $ , $ 11 $ , $ 22 $ , $ 33 $ , $ 44 $ , $ 55 $ , $ 66 $ , $ 77 $ , $ 88 $ , $ 99 $ , so you are allowed to choose any of them.

## 样例 #1

### 输入

```
5
59 63
42 49
48 53
90 90
1 100```

### 输出

```
63
44
53
90
1```

# 题解

## 作者：luguangxing (赞：8)

我认为这一题其实并不像前几篇题解所说的是全是 `dp` 其实有个可以降低复杂度的写法很好理解。

我们把情况分为两种，第一种就是两个数位数相等，如：$999$  和 $1000$ 根据题目意思找出的就是 $999$，因为他数位上的全部数都一样，如此得来一个定理，只要两个数数位不同，就一定至少有一个全部数位相等的数，我们只要找到他并把他输出就行了。

第二种情况就是两个数数位不同的情况：当然我们还是不能直接去跑一遍，那样还是会超时，于是就要用~~大佬~~们所说的数位 `dp` 了。

代码展示：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r,ans,minv;
vector<int>dl,dr;
int get(long long x)//计算数位
{
	int mx=-1,mi=10;
	while(x)
	{
		int t=x%10;
		mx=max(mx,t);
		mi=min(mi,t);
		x/=10;
	}
	return mx-mi;
}
int init(vector<int>&v,long long x)//初始化函数
{
	v.clear();
	long long b=x;
	while(x) v.push_back(x%10),x/=10;
	reverse(v.begin(),v.end());
	int t=get(b);
	while(minv>t)
	{
		minv=t;
		ans=b;
	}
}
void work(vector<int>&v)
{
	long long x=0;
	for(int i=0;i<v.size();i++)
	{
		for(int j=0;j<=9;j++)
		{
			long long res=x;
			for(int k=i;k<v.size();k++)
			res=res*10+j;
			if(res<l||res>r)
			continue;
			int t=get(res);
			if(minv>t)
			{
				minv=t;
				ans=res;
			}
		}
		x=x*10+v[i];
	}
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>l>>r;
		minv=10;
		init(dl,l),init(dr,r);
		if(dl.size()!=dr.size())//判断数位是否相等
		{
			long long res=0;
			while(res<l)
			res=res*10+9;
			cout<<res<<endl;
			continue;
		}
		work(dl),work(dr);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Eznibuil (赞：5)

很简单，按照套路可以将 $[l,r]$ 拆解为若干 $[x,x+10^a)$，其中 $x$ 是 $10^a$ 的倍数。

然后令 $\text{Luck}(x)$ 表示 $x$ 的幸运程度（也就是最大的数位减最小的数位），则 $[x,x+10^a)$ 的答案为 $\text{Luck}(\frac x{10^a})$，因为最后 $a$ 位数字总是能保持在前面的最大和最小之间。一种方案就是直接在后面附上 $a$ 个前面的最小。

显然只会拆出 $O(\log(r-l))$ 个区间，检查一遍即可。

代码极度好写。（注意：按理来说 $[x,x+10^a)$ 当 $x=0$ 时要特判的，不过题目保证 $l\ge1$，于是特判消失了。）
```cpp
#include<stdio.h>
int mak(long long x)
{
	int max=-1;
	while(x)
	{
		if(max<x%10)
			max=x%10;
		x/=10;
	}
	return max;
}
int mik(long long x)
{
	int min=10;
	while(x)
	{
		if(min>x%10)
			min=x%10;
		x/=10;
	}
	return min;
}
int main()
{
	int t;
	long long l,r;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lld%lld",&l,&r);
		long long ans=r,s=mak(r)-mik(r);
		for(long long i=1,j=0;i<=100000000000000000ll&&l<r;i*=10,j=j*10+1)
		{
			while(l%(i*10)&&l<r)
			{
				long long ma=mak(l/i),mi=mik(l/i);
				if(s>ma-mi)
					ans=l+j*mi,s=ma-mi;
				l+=i;
			}
			while(r%(i*10)&&l<r)
			{
				r-=i;
				long long ma=mak(r/i),mi=mik(r/i);
				if(s>ma-mi)
					ans=r+j*mi,s=ma-mi;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：2018ljw (赞：3)

2C 1900 从各种意义上都是很炸裂的。

关注到位数很少，考虑乱搞。

枚举最大值和最小值，问题变为能否用一个区间数集的数凑出目标区间内的某数。

差分，考虑用一个数集能凑出多少 $\le x$ 的数。这个也是经典问题，将 $x$ 按位分解后讨论每一位，如果填的比 $x$ 该位小后面随便填，否则只能填该位，递归做下去即可。需要单独考虑前导零的情况，因为 $0$ 不一定在数集内。

这样我们就可以得到最小极差和对应数集 $S$ 了，考虑构造答案。

记 $f(x,S)$ 表示 $\le x$，且数集为 $S$ 的数字个数。显然对于同一个 $S$，$f$ 关于 $x$ 是单调升的，且每个升的位置都是一个答案。

因此在 $[l,r]$ 内二分找到第一个 $f(x,S)\neq f(l-1,S)$ 的 $x$ 即为答案。

复杂度 $O(k^3+k\log V)$，$k$ 是数字位数，$V$ 是值域。[record](https://codeforces.com/contest/1808/submission/210550037)。

---

## 作者：__ikun__horro__ (赞：1)

### Solution

幸运值是数字中的最大值减去最小值，我们可以设计一个 dfs。

首先，把 $l$ 和 $r$ 处理成两个数组 $a$ 和 $b$，表示每一位的值。

dfs 中设置一个状态 $u$ 表示当前的位数。状态 $num$ 表示数字的 $1 \sim u-1$ 位。然后有两个状态 $Max$ 和 $Min$，表示 $1 \sim u-1$ 位的最大值和最小值。每次枚举 $0 \sim 9$ 表示第 $u$ 位。

但是这样枚举时有可能枚举出界，比如 $l=1,r=5$ 时，枚举第一位有可能枚举到 $0$，还有可能枚举到 $6$。因此我们要再设置两个状态 $isMax$ 和 $isMin$，分别表示当前是否为上界和下界。如果 $isMin$ 为 True，表示是下界，此时枚举第 $u$ 位时只能从 $a_u$ 开始枚举；如果 $isMax$ 为 True，表示是上界，此时枚举第 $u$ 位时只能枚举到 $b_u$。

我有个同学 ~~（都说了同学，怎么会是我）~~，就这样结果一看记录 `Wrong answer on test 2`。

那这究竟是道德的沦丧还是人性的扭曲？都不是，这是应为枚举的数字可能含有前导零，这时 $Max$ 和 $Min$ 也会被更新，所以还要设置一个状态 $f$，表示当前是否可以更新 $Max$ 和 $Min$，当且仅当 $1 \sim u-1$ 位都为 $0$ 时 $f$ 为 False。当 $f$ 为 False 且第 $u$ 位不为 $0$ 要把 $f$ 更新成 True。

当然，这样是会 TLE 的。容易发现，数字到底是多少和 dfs 关系并不大。重要的是 $Max$、$Min$、$isMax$、$isMin$ 和 $u$，这关系到后面的数以及答案，所以我们可以设计一个布尔类型的数组，表示当前状态有没有被访问过。这样操作次数最多为 $18 \times 10 \times 10 \times 2 \times 2=7200$，毫无悬念可以通过，我代码最慢也就跑了 $62$ 毫秒。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 25;
string ans;
int n, minans, a[N], b[N];
bool dp[N][10][10][2][2];
void dfs(int u, int Max, int Min, int is_Max, int is_Min, int f, string num) {
//	cout << u << "  " << Max << " " << Min << "  " << is_Max << " " << is_Min << "   " << num << "\n";
	if (u > n) {
		if (Max - Min < minans) {
			minans = Max - Min;
			ans = num;
		}
		return;
	}
	if (dp[u][Max][Min][is_Max][is_Min]) return;
	dp[u][Max][Min][is_Max][is_Min] = 1;
	int l = (is_Min ? a[u] : 0);
	int r = (is_Max ? b[u] : 9);
	for (int v = l; v <= r; v++) {
		if (v == 0 && f == 0) {
			dfs(u + 1, Max, Min, is_Max & (v == r), is_Min & (v == l), f, num + char(v + 48));
		} else {
			dfs(u + 1, max(Max, v), min(Min, v), is_Max & (v == r), is_Min & (v == l), f | (v != 48), num + char(v + 48));
		}
	}
}
int main() {
	int T;
	cin >> T;
	while (T--) {
		string l, r;
		cin >> l >> r;
		while (l.size() < r.size()) l = "0" + l;
		n = l.size();
		l = "0" + l, r = "0" + r;
		for (int i = 1; i <= n; i++) {
			a[i] = l[i] - 48, b[i] = r[i] - 48;
		}
		memset(dp, 0, sizeof dp);
		minans = 1000;
		dfs(1, 0, 9, 1, 1, 0, "");
		int flag = 0;
		for (int i = 0; i < (int)ans.size(); i++) {
			if (ans[i] != 48) flag = 1;
			if (flag) cout << ans[i];
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：Zimo_666 (赞：1)

## C. Unlucky Numbers

有点恐怖的一道题。

考虑数位动态规划。

由于他求的东西不能满足像前缀和那样转化，我们不妨换一种转换方式试一试。

我们考虑把 $l,r$ 都按位存进一个 $a,b$ 数组里，然后我们考虑类似数位动态规划的方式进行转移。

设 $dp_{i,j,k}$ 表示当前枚举的位置是 $i$，且 $limit1,limit2$ 均为 $false$，$j$ 为之前出现的最大数位，$k$ 为之前出现的最小数位的答案。这个数组是不需要每次都清空的，因为他好像和上下界没有关系。

然后就是一些常见的写法了。只不过我们是用 $a,b$ 数组约束上下界，也就是在代码中的 $limit1,limit2$ 了。实现细节见代码。

[Code](https://codeforces.com/problemset/submission/1808/224253496)

---

## 作者：masonpop (赞：1)

少见的 #1900 的 2C。但其实比较套路。怎么题解都这么多奇妙做法，这不就是个数位 dp 板子吗。

首先为了避免前导 $0$ 的判断，先判掉 $l$ 和 $r$ 位数不同的情况，这种情况显然答案是一车 $9$。否则，记 $f_{i,maxx,minn,p,q}$ 表示当前考虑到第 $i$ 位，当前数位最大值 $maxx$，最小值 $minn$，是否顶到上界，是否顶到下界。转移直接枚举当前位即可。

题目要输出方案，于是另开一个方案数组 $g$ 记录方案。一定注意数组别开小了。代码好写好调。[代码](https://codeforces.com/contest/1808/submission/219976637)。

---

## 作者：蒟酱 (赞：1)

可以证明答案是 $l$ 或 $r$ 的一段前缀，拼上后面全部相同的一段字符 $d$，证明方式类似数位 dp。能够自由填的数字一定是相等的，这样不会影响幸运值。前面那些不能自由填写的，就是 $l$ 或 $r$ 的一段前缀。假如不是 $l$ 或 $r$ 的一段前缀，必然填写相等的更好，而这种情况已经被考虑到了。  
枚举前缀长度，枚举修改成的字符 $d$，复杂度 $\mathcal O(T\log^2w\Sigma)$，字符集大小为 $10$。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define siz(x) int((x).size())
#define all(x) std::begin(x),std::end(x)
using std::cin;using std::cout;
using std::max;using std::min;
using loli=long long;
int n;
loli l,r;
std::vector<int>b1,b2,t,ans;
int calc(std::vector<int>b){
	reverse(all(b));
	while(!b.empty()&&!b.back())b.pop_back();
	return *max_element(all(b))-*min_element(all(b));
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	int T;cin>>T;while(T--){
		cin>>l>>r;
		b1.clear();b2.clear();
		ans.clear();
		for(;l;l/=10)b1.push_back(int(l%10));
		for(;r;r/=10)b2.push_back(int(r%10));
		n=max(siz(b1),siz(b2));
		while(siz(b1)<n)b1.push_back(0);
		while(siz(b2)<n)b2.push_back(0);
		reverse(all(b1));reverse(all(b2));
		for(int k=0;k<=n;k++)for(int d=0;d<=9;d++){
			t=b1;
			for(int j=k;j<n;j++)t[j]=d;
			if(b1<=t&&t<=b2&&(ans.empty()||calc(t)<calc(ans)))
				ans=move(t);
		}
		for(int k=0;k<=n;k++)for(int d=0;d<=9;d++){
			t=b2;
			for(int j=k;j<n;j++)t[j]=d;
			if(b1<=t&&t<=b2&&(ans.empty()||calc(t)<calc(ans)))
				ans=move(t);
		}
		reverse(all(ans));
		while(!ans.empty()&&!ans.back())ans.pop_back();
		reverse(all(ans));
		for(int i:ans)cout<<i;
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：1)

非常少的我能够场切的 dp！

首先发现不仅题目意思和 A 变了，数据范围也加大了。看到这个位数，我们能很快的想到数位 dp。

首先特判掉 $l$ 和 $r$ 位数不同，直接构造一大车 $9$ 即可。

然后我们随便口胡一个状态：

`f(w,mx,mn,up,down)` 表示需要构造一个位数为 $w$，前面每一位的最大值和最小值为 $mx$ 和 $mn$，现在这后 $w$ 位的上限和下限为 $up$ 和 $down$ 的满足所有位（包括前面）的 $mx-mn$ 最小的数。

可能比较抽象，但是实际上并不难想到。之后的式子也很好推。

首先如果上界和下界没有要求（即要求范围为 $000...0\sim999...9$），那么直接随便返回一个值在 $mn$ 到 $mx$ 中间的 $xxx...x$ 构造即可。

如果位数为 $0$，返回空气。

之后我们枚举当前可以取的每一位，计算这一位所对应的上下界（判一下枚举的值是不是最小的以及最大的），如果值超过了 $mn$ 和 $mx$ 就更新，然后直接递归取答案的最小值即可。

这个东西看起来递归非常多次，但是实际上每次到一个全空的块就直接返回了，复杂度 $O(|l|)$。

Code：

~~变量名比较抽象，不要在意~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
string a,b;
ll A,B;
ll p10[25]={1};
inline ll homo(int w,int v){ll ans=0;//形似 xxx...x的数
for(int i=1;i<=w;i++) ans=ans*10+v;
return ans;
}
pair<int,ll> f(int weishu,int mn,int mx,long long up,long long down){//返回值为mx-mn和一个构造
	if(!weishu) return {max(mx-mn,0ll),0};
	if(up==p10[weishu]-1&&down==0) return {max(mx-mn,0ll),homo(weishu,mx)};
	int ans=11,val=0;
	int D=(down==0?0:(ll)(down/p10[weishu-1]));//这位能选的下限
	int U=(up==p10[weishu+1]-1?9:(ll)(up/p10[weishu-1]));//这位能选的上限
	for(int now=D;now<=U;now++){
		ll v=p10[weishu-1]*now;
		pair<int,ll> fk=f(weishu-1,min(mn,now),max(mx,now),
		(up!=-1&&now==U)?up-v:p10[weishu-1]-1,(down!=-1&&now==D)?down-v:0);//记得判上下界
		if(fk.first<ans) ans=fk.first,val=v+fk.second;
	}
	return {ans,val};
}
signed main(){for(int i=1;i<=18;i++) p10[i]=p10[i-1]*10ll;int t;cin>>t;while(t--){//预处理一下10的若干次方
	cin>>a>>b;A=B=0;
	if(a.size()!=b.size()){//直接随便构造
		for(int i=0;i<a.size();i++) cout<<9;cout<<endl;
		continue;
	}
	for(int i=0;i<a.size();i++) A=A*10+a[i]-48,B=B*10+b[i]-48;
	cout<<f(a.size(),10,-1,B,A).second<<endl;//建议把最大值和最小值都设为值域外的数，避免出现一些奇怪的锅
}}
```

---

## 作者：Engulf (赞：0)

还是第一次遇到不是统计满足条件的数字个数，而是最值类问题的数位 dp，特此记之。

由于前导零什么的最讨厌了，如果 $l$ 和 $r$ 位数不相同，则一定可以取到 $\underbrace{99\cdots9}_{l 的位数个}$。

否则考虑数位 dp，跟计数类不同，计数类可以用一个容斥，这个不行，所以 dfs 的时候要记录是否取到上界和是否取到下界，其他跟普通数位 dp 没有区别。这里的记忆化就是记录一下有没有搜到过这个状态就行了。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 20;

int a[N], b[N];

int ansd;
ll ans;
bool f[N][10][10][2][2];

void dfs(int pos, int mn, int mx, int lim1, int lim2, ll num) {
    if (!pos) {
        if (mx - mn < ansd) {
            ansd = mx - mn;
            ans = num;
        }
        return;
    }
    if (f[pos][mn][mx][lim1][lim2]) return;
    f[pos][mn][mx][lim1][lim2] = 1;
    for (int i = (lim1 ? b[pos] : 0); i <= (lim2 ? a[pos] : 9); i++)
        dfs(pos - 1, min(mn, i), max(mx, i), lim1 && i == b[pos], lim2 && i == a[pos], num * 10 + i);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt;
    cin >> tt;
    while (tt--) {
        ll l, r;
        cin >> l >> r;
        int lenl = (int)log10(l) + 1, lenr = log10(r) + 1;
        if (lenl != lenr) {cout << string(lenl, '9') << "\n"; continue;}

        lenl = lenr = 0;
        while (l) b[++lenl] = l % 10, l /= 10;
        while (r) a[++lenr] = r % 10, r /= 10;

        ansd = 10;
        memset(f, 0, sizeof f);
        dfs(lenr, 9, 0, 1, 1, 0);

        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：Isharmla (赞：0)

数位 dp 板子。

容易发现，当 $l,r$ 的位数不相同时，答案一定可以构造为全部都是 $9$ 的数字。考虑 $l,r$ 位数相等的时候。这不就是个套路数形 dp 吗？根据数位 dp 传统套路，发现我们构造一个数只关心长度，是否到上界，是否到下界，最大值和最小值，把这些放进 $dp$ 里面，构造出 $f_{len,maxn,mixn,up,down}$ 对应数字长度，最大值，最小值，上界，下界为当前情况的是否存在，记忆化搜索即可。如何找到答案？也很简单，我们在 dp 的时候建一个辅助数组 $num_{len,maxn,mixn,up,down}$ 顺便记录一下即可。

```cpp
inline int dfs(int len,int Maxn,int Mixn,bool up,bool down) {
	if(len == Len + 1) return Maxn-Mixn;
	if(~f[len][Maxn][Mixn][up][down]) return f[len][Maxn][Mixn][up][down];
	int ans = INT_MAX, res;
	for(int i = 0; i <= 9; i++) {
		if (up && i > sj[len]) continue;
		if (down && i < xj[len]) continue;
		res = min(res, dfs(len+1, max(Maxn,i), min(Mixn,i), up&(i==sj[len]), down&(i==xj[len])));
		if (res < ans){
			ans = res;
			num[len][Maxn][Mixn][up][down]= i * 10pow[len] + num[len+1][max(Maxn,i)][min(Mixn,i)][up&(i==sj[len])][down&(i==xj[len])];
		}
	}
	return f[len][Maxn][Mixn][up][down]=ans;
}
```


---

