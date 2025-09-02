# Last Chance

## 题目描述

Having read half of the book called "Storm and Calm" on the IT lesson, Innocentius was absolutely determined to finish the book on the maths lessons. All was fine until the math teacher Ms. Watkins saw Innocentius reading fiction books instead of solving equations of the fifth degree. As during the last maths class Innocentius suggested the algorithm of solving equations of the fifth degree in the general case, Ms. Watkins had no other choice but to give him a new task.

The teacher asked to write consecutively (without spaces) all words from the "Storm and Calm" in one long string $ s $ . She thought that a string is good if the number of vowels in the string is no more than twice more than the number of consonants. That is, the string with $ v $ vowels and $ c $ consonants is good if and only if $ v<=2c $ .

The task Innocentius had to solve turned out to be rather simple: he should find the number of the longest good substrings of the string $ s $ .

## 说明/提示

In the first sample there is only one longest good substring: "Abo" itself. The other good substrings are "b", "Ab", "bo", but these substrings have shorter length.

In the second sample there is only one longest good substring: "EIS". The other good substrings are: "S", "IS".

## 样例 #1

### 输入

```
Abo
```

### 输出

```
3 1
```

## 样例 #2

### 输入

```
OEIS
```

### 输出

```
3 1
```

## 样例 #3

### 输入

```
auBAAbeelii
```

### 输出

```
9 3
```

## 样例 #4

### 输入

```
AaaBRAaaCAaaDAaaBRAaa
```

### 输出

```
18 4
```

## 样例 #5

### 输入

```
EA
```

### 输出

```
No solution
```

# 题解

## 作者：Yuby (赞：3)

[题面](https://www.luogu.com.cn/problem/CF137E)

#### 题意：

注意题目中应该为 $v\leq 2\times c$。

#### 题目分析：

这题的理想复杂度为 $O(n\log n)$ 或者 $O(n)$。

首先我们把问题拆开。

如果我们已知最长连续子串的长度，能否在正确复杂度内得到个数？

我们不妨把一个辅音字母看做 $+2$，然后把一个元音字母看做 $-1$。由此来构造一个前缀和数组 pre。设最长连续子串长度为 $x$，那么只要 $pre_{i+x-1}-pre_{i-1}\geq 0$ 就是一个答案。复杂度 $O(n)$。

那么我们考虑另一个问题。

这道题最大的难点在于这个 pre 数组并不具有单调性，所以 CF 官方题解写的是排序后线段树维护这个数组。

#### 但是（划重点！）

我们思考长度怎么才会增加。对于一组答案对于 $i_1$ 和 $i_2$ 最优的 $(i_1,j_1)$ 和 $(i_2,j_2)$ 且 $i_2>i_1$，如果说后一个成立且长度超过前一个的长度那么必然有 $j_2>j_1$。

再考虑，如果有 $pre_{j_2}>pre{j_1}$ 显然不可行。因为如果 $pre_{j_2}>pre{j_1}$ 成立，那么必然有 $pre_{j_2}-pre_{i_1-1}\geq pre_{j_1}-pre_{i-1}$ 与 $(i_1,j_1)$ 的最优性不符。因此可以得出：如果存在更优答案必有 $pre_{j_2}<pre_{j_1}$ 又满足后一个的长度更长且成立即有 $pre_{i_2}<pre_{i_1}$。

因此每次只需找到比上一个的 pre 值更小的即可。

确定了 $i$ 我们怎么确定 $j$ 呢？我们发现最优的 $j$ 一定是最后一个比 $pre_{i-1}$ 大的位置。我们不妨设一个后缀最大值数组 suf。即：

```cpp
for(ll i=n;i>=1;i--)suf[i]=max(pre[i],suf[i+1]);
```

这样可以保证 suf 的值是非上升的。这里就可以直接二分第一个比 $pre_{i-1}$ 小的位置然后 $-1$，复杂度 $O(n\log n)$ 可以通过此题，二分部分代码过于简单就不放了，剩下的部分参考下面的思路。

接着我们考虑第二种方法，继续上面的思路 $pre_{i_2}<pre_{i_1}$ 和 $pre_{j_2}<pre_{j_1}$。那么可以发现在 $i$ 递增的同时 $j$ 也是不会下降的。用尺取的思路考虑这个问题得到一个 $O(n)$ 的解法。

代码相当简洁，但是跑的飞快：

```cpp
#include<bits/stdc++.h>//Yuby163 https://www.luogu.com.cn/record/67857047 120ms
#define pc putchar
using namespace std;
typedef long long ll;
const ll MAXN=2e5+7;
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
ll n,suf[MAXN],pre[MAXN];
char str[MAXN];
bool check(const char& x)
{
	return x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='A'||x=='E'||x=='I'||x=='O'||x=='U';
}
int main()
{
	scanf("%s",(str+1));
	n=strlen(str+1);
	for(ll i=1;i<=n;i++)
	{
		pre[i]=pre[i-1];
		if(check(str[i]))pre[i]--;
		else pre[i]+=2;
	}
	for(ll i=n;i>=1;i--)suf[i]=max(pre[i],suf[i+1]);
	ll i=1,j=1,minn=INF,ans=0,las=-1;
	while(i<=n)
	{
		while(pre[i-1]>=minn&&i<=n)i++;
		if(las==i)break;
		las=i;
		minn=pre[i-1];
		j=max(j,i);
		while(suf[j+1]>=pre[i-1]&&j<=n)j++;
		j--;
		if(pre[j]>=pre[i-1])ans=max(ans,j-i+1);
	}
	if(!ans)puts("No solution");
	else
	{
		ll cnt=0;
		for(ll i=1;i+ans-1<=n;i++)
			if(pre[i+ans-1]>=pre[i-1])cnt++;
		write(ans),pc(32),write(cnt),pc(10);
	}
	return 0;
}

```





---

## 作者：ofsl (赞：2)

题目链接：[CF137E Last Chance](https://www.luogu.com.cn/problem/CF137E)

宣传一下[我的博客](https://www.luogu.com.cn/blog/302437/)

有些地方的语言表达逻辑可能有点混乱，欢迎指出更好的说法qwq
## 简要翻译：
给定一个字符串，求其中一个最长子串满足元音字母个数小于辅音字母个数的两倍。输出的第一个数为该子串的长度，第二个数为满足该长度和题目要求的字串个数。如果不存在满足题目要求的字串，就输出 "No solution"。
## 思路：
设 $v_{i}$ 为字符串前 $i$ 个字符的元音个数，$c_{i}$ 为字符串前 $i$ 个字符的辅音个数的两倍，$s_{i,j}$ 为原字符串从第 $i$ 个字符到第 $j$ 个字符的子串，$t_{i}$ 为 $c_{i}-v_{i}$。如果 $s_{i,j}$ 符合题意，当且仅当 $v_{j}-v_{i-1}\leqslant c_{j}-c_{i-1}$，即 $t_{j}\geqslant t_{i-1}$。所以如果我们要找到一个最长的**结尾为第 $j$ 个字符的合法子串**，我们只需要找到一个最小的 $i$，使 $t_{j}\geqslant t_{i-1}$。如果 $t_{j}\geqslant 0$，则 $j$ 为当前子串最大长度（$t_{0}=0$）。

如果 $t_{j}< 0$，则用 $r$ 数组记录下当前位置，若 $l$ 数组无记录则也一起记录到 $l$ 数组里（$l$ 记录第一个出现 $t_{j}$ 的**值**的位置，$r$ 记录最后一个）。最后对 $t$ 值循环遍历，用当前的 $r$ 减去最小的 $l$ 就能得到当前合法子串的长度（最小的 $l$ 也就是 $\forall p<$当前的 $t$，取 $\min(l_t,l_p)$，原因见上）。

具体 $v$、$c$、$t$、$l$、$r$ 的实现见代码
## 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int v,c,ans,n,cnt=1,l[200005],r[200005];
char s[200005];
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]<97)s[i]+=32;
		if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u')v++;
		else c+=2;
		int t=c-v+n+1;//加上n+1来防止负数出现 
		if(t>n){
			ans=i;
			continue;
		}//t为正数直接取1到i 
		if(!l[t])l[t]=i;
		r[t]=i;
	}
	l[0]=0x3f3f3f3f;//防止有的t不存在 
	for(int i=1;i<=n;i++){//枚举可能的负数t值 
		if(l[i]){//l[i]不为0，i才存在 
			l[i]=min(l[i],l[i-1]);
			int len=r[i]-l[i];
			if(len==ans)cnt++;
			if(len>ans)ans=len,cnt=1;
		}else
			l[i]=l[i-1];
	}
	if(ans==0)puts("No solution");
	else printf("%d %d\n",ans,cnt);
	return 0;
}
```

代码还有优化的空间。

如有错误欢迎指出！

求赞qwq

---

## 作者：Day_Tao (赞：1)

### 题目大意

给定字符串 $s$，求最长的子串及其个数，该子串满足元音的个数 $v$ 小于等于辅音的个数 $c$ 的两倍，即 $v \le 2 \times c$ 。元音辅音字母不区分大小写。

### Sol

翻译有一点小锅，没把等号写上。题面可以转化成元音贡献为 $-1$，辅音贡献为 $2$，用数组 $a$ 储存，求最长区间使得 $\sum _ {i=l}^r a_i \ge0$ 时的 $r-l$ 最大。

考虑前缀和。记录下 $a$ 数组的前缀 $sum$，就相当于求前缀相减大于等于 $0$ 的情况。根据贪心，要使长度最长，$r-l$ 就一定为 $0$。假如说大于 $0$，由于每次最多减一，就可以继续往后考虑，证毕。所以可以在此时记录下相应的下标，在 $sum$ 相同的情况下找出最大以及最小的坐标，两者之差就是最终的答案了。要注意考虑答案为整串的情况，前者用这个算法无法判断，因为 $sum_n$ 并没有记录 $0$ 的情况，所以加个特判，不然会在第 $6$ 个点 WA。还有从第一个开始的情况，要加上一个 $sum=0,id=0$ 的情况，不然会在第 $56$ 个点 WA。

可以将数组按照 $sum$ 为第一关键字，$id$ 为第二关键字排序，对于 $sum$ 相同的一块找到最大与最小的 $id$ 存起来，再求出最大得差值。求到最大值后可以在没排序的 $sum$ 数组中进行尺取，找到最大长度的个数。注意到存 $id$ 的数组下标为 $sum$，可能出现负数，所以可以采用两种方法：开个 map 或者弄个偏移量。前者会多一只 $\log$，我是在模拟赛里碰到这个题的，数据开了 $2\times10^6$，并且会卡这个 $\log$，所以使用了后者。
### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 2e6 + 6;
const int INF = 0x7fffffff;
const int mod = 998244353;
const int p = 2000001; // 偏移量
struct node
{
    int sum, id;
} a[MAX];
int f[MAX];
char c;
int n, sum[MAX], len, ans;
int minn[MAX * 3], maxx[MAX * 3];
inline bool cmp(node Day, node Tao)
{
    if (Day.sum == Tao.sum)
        return Day.id < Tao.id;
    return Day.sum < Tao.sum;
} // 防伪
signed main()
{
    while (c = getchar())
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            f[++n] = -1;
        else if (c <= 'z' && c >= 'a' || c <= 'Z' && c >= 'A')
            f[++n] = 2;

        else
            break;
    for (int i = 1; i <= n; ++i)
        a[i].sum = a[i - 1].sum + f[i], a[i].id = i, sum[i] = a[i].sum; // 记录前缀
    if (a[n].sum >= 0)                                                  // 特判整串可行的情况
    {
        printf("%d 1", n);
        return 0;
    }
    sort(a, a + n + 1, cmp);
    for (int i = 0; i <= n; ++i)
        minn[a[i].sum + p] = INF;
    for (int i = 0; i <= n; ++i)
        minn[a[i].sum + p] = min(minn[a[i].sum + p], a[i].id), maxx[a[i].sum + p] = max(maxx[a[i].sum + p], a[i].id); // 求同一 sum 的最大与最小值
    len = -1;
    for (int i = 1; i <= 6000001; i++) // 找到最大的 len
        len = max(len, maxx[i] - minn[i]);
    if (len <= 0)
    {
        printf("No solution");
        return 0;
    }
    printf("%d ", len);
    for (register int i = 1; i <= n - len + 1; ++i) // 尺取部分
        if (sum[i + len - 1] - sum[i - 1] >= 0)
            ans++;
    printf("%d", ans);
    system("pause");
    return 0;
}
```
---
### END

---

## 作者：Genius_Star (赞：0)

### 思路：

令 $s_i$ 表示前缀元音字母的数量。

考虑推式子，设选的子串区间是 $[l,r]$，则需要满足：

$$s_r - s_{l - 1} \le 2 (r - l + 1  - (s_r - s_{l - 1}))$$

化简得：

$$3(s_r - s_{l - 1}) \le 2(r -l + 1)$$

分离一下得：

$$3s_r - 2r \le 3s_{l -1} -2l + 2$$

同乘 $-1$ 得：

$$2l - 3s_{l - 1} - 2 \le 2r - 3s_r$$

故我们枚举 $r$，找到最小的 $l$ 满足 $2l - 3s_{l - 1} - 2 \le 2r - 3s_r$ 即可，可以使用值域树状数组维护前缀 min。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10, M = 2e6 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, x, Max, ans;
int a[N];
char s[N];
inline bool check(char c){
	if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
	  return 1;
	if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
	  return 1;
	return 0;
}
namespace Tree{
	int a[M];
	inline void init(){
		memset(a, 0x7f, sizeof(a));
	}
	inline void add(int x, int v){
		x += 1e6;
		for(int i = x; i < M; i += lowbit(i))
		  a[i] = min(a[i], v);
	}
	inline int query(int x){
		x += 1e6;
		int ans = 1e9;
		for(int i = x; i; i -= lowbit(i))
		  ans = min(ans, a[i]);
		return ans;
	}
}
bool End;
int main(){
	Tree::init();
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; ++i)
	  a[i] = a[i - 1] + check(s[i]);
	for(int i = 1; i <= n; ++i){
		Tree::add(2 * i - 3 * a[i - 1] - 2, i);
		x = Tree::query(2 * i - 3 * a[i]);
		if(i - x + 1 > Max){
			Max = i - x + 1;
			ans = 1;
		}
		else if(i - x + 1 == Max)
		  ++ans;
	}
	if(!Max){
		puts("No solution");
		exit(0);
	}
	write(Max);
	putchar(' ');
	write(ans);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：_edge_ (赞：0)

大家好，我是暴力数据结构选手。


题面当中的 $v<2 \times c$ 要改成 $v \le 2 \times c$ 哦。

很简单的一个想法，我们先把元音字母看成 $+1$ 辅音字母看成 $-2$，做个前缀和。

然后该问题就变成求最大的 $r-l+1$ 使得 $sum_r-sum_{l-1} \ge 0$，前缀和的细节可以尝试自己玩。

于是我们再移项得到 $sum_r \ge sum_{l-1}$，然后该问题就转换成了一个经典的二维偏序，具体的，固定 $r$，查询最小的 $l$，使得 $r>l$ 并且 $sum_r \ge sum_{l-1}$

可以利用从左往右扫解决第一维问题，然后利用树状数组+离散化解决第二维。

主要是这样比较好想，还有各种神仙的 $O(n)$ 做法我实在是不太能理解（

时间复杂度 $O(n \log n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#define pb push_back 
#define int long long 
using namespace std;
const int INF=1e6+5;
string s1;
int a[INF],tree[INF],sum[INF];
vector <int> v;
int Get(int x) {return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
void add(int x,int y) {for (int i=x;i;i-=i&-i) tree[i]=min(tree[i],y);}
int query(int x) {int sum=1e18;for (int i=x;i<=1e6;i+=i&-i) sum=min(sum,tree[i]);return sum;}
signed main()
{
	memset(tree,63,sizeof tree);
	ios::sync_with_stdio(false);
	cin>>s1; int len=s1.size();
	for (int i=0;i<len;i++) {
		if (s1[i]>='A' && s1[i]<='Z')
			s1[i]=s1[i]-'A'+'a';
	}
	for (int i=0;i<len;i++) {
		if (s1[i]=='a' || s1[i]=='e' || s1[i]=='i' || s1[i]=='o' || s1[i]=='u') a[i+1]=1;
		else a[i+1]=-2;
	}
	v.pb(0);
	for (int i=1;i<=len;i++)
		sum[i]=sum[i-1]+a[i],v.pb(sum[i]);
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	add(Get(0),0);
//	cout<<Get(0)<<" aweirjawierj\n";
	int ans=-1,ans1=0;
	for (int i=1;i<=len;i++) {
		int id=Get(sum[i]);
//		cout<<id<<" yiw\n";
		int kk=query(id);
		if (ans<i-kk) ans=i-kk,ans1=1;
		else if (ans==i-kk) ans1++;
		add(id,i);
	}
	if (ans!=-1) cout<<ans<<" "<<ans1<<"\n";
	else cout<<"No solution\n";
	return 0;
}
```


---

