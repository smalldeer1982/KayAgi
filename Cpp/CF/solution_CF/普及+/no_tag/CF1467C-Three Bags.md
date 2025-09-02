# Three Bags

## 题目描述

You are given three bags. Each bag contains a non-empty multiset of numbers. You can perform a number of operations on these bags. In one operation, you can choose any two non-empty bags, and choose one number from each of the bags. Let's say that you choose number $ a $ from the first bag and number $ b $ from the second bag. Then, you remove $ b $ from the second bag and replace $ a $ with $ a-b $ in the first bag. Note that if there are multiple occurrences of these numbers, then you shall only remove/replace exactly one occurrence.

You have to perform these operations in such a way that you have exactly one number remaining in exactly one of the bags (the other two bags being empty). It can be shown that you can always apply these operations to receive such a configuration in the end. Among all these configurations, find the one which has the maximum number left in the end.

## 说明/提示

In the first example input, let us perform the following operations:

 $ [1, 2], [6, 3, 4, 5], [5] $

 $ [-5, 2], [3, 4, 5], [5] $ (Applying an operation to $ (1, 6) $ )

 $ [-10, 2], [3, 4], [5] $ (Applying an operation to $ (-5, 5) $ )

 $ [2], [3, 4], [15] $ (Applying an operation to $ (5, -10) $ )

 $ [-1], [4], [15] $ (Applying an operation to $ (2, 3) $ )

 $ [-5], [], [15] $ (Applying an operation to $ (-1, 4) $ )

 $ [], [], [20] $ (Applying an operation to $ (15, -5) $ )

You can verify that you cannot achieve a bigger number. Hence, the answer is $ 20 $ .

## 样例 #1

### 输入

```
2 4 1
1 2
6 3 4 5
5```

### 输出

```
20```

## 样例 #2

### 输入

```
3 2 2
7 5 4
2 9
7 1```

### 输出

```
29```

# 题解

## 作者：PersistentLife (赞：5)

答案有两种情况：

- 两个在不同集合中的数贡献为负，其余为正。
- 一个集合中的元素贡献为负，其余为正。

具体的操作方法为:

- 选取两个在不同集合中的数，然后用这两个数去减其他可以减的数，然后用这两个数中的一个减去另一个。
- 选取一个数，让它减去其余的可以减去的数（注意要留下一个数），然后用留下的一个数减去选取的这个数所在的集合中的每一个元素。

有点绕口，大家细细品。

所以答案就是两种情况的最大值。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n1,n2,n3,m1,m2,m3,s1,s2,s3;
int a[300005],b[300005],c[300005];
signed main()
{
	cin>>n1>>n2>>n3;
	m1=m2=m3=0x3f3f3f3f;
	
	for(int i=1;i<=n1;i++) scanf("%lld",&a[i]),m1=min(m1,a[i]),s1+=a[i];
	for(int i=1;i<=n2;i++) scanf("%lld",&b[i]),m2=min(m2,b[i]),s2+=b[i];
	for(int i=1;i<=n3;i++) scanf("%lld",&c[i]),m3=min(m3,c[i]),s3+=c[i];
	int ans=0;
	ans=max(ans,s2+s3-s1);
	ans=max(ans,s1+s3-s2);
	ans=max(ans,s1+s2-s3);
	ans=max(ans,s1+s2+s3-2*min(m1+m2,min(m1+m3,m2+m3)));
	cout<<ans;
	return 0;
}
```

---

## 作者：wmy_goes_to_thu (赞：2)

我们先随便选一个数，然后开始“杀”。

先把另外两个集合除了最小值全杀掉，变成一个绝对值非常大的负数。

然后我们从那两个集合里选一个来“报仇”，把大负数吃掉，现在还是两个单和一个大集合（除去了一个数）。

现在我们把另外一个单和大集合竞争，得到了这个单的值减去大集合的值这个东西，把它的绝对值加上选的那个单现在的值就是答案。

一句话：

![](https://cdn.luogu.com.cn/upload/image_hosting/guqiq0m2.png)

---

## 作者：Imitators (赞：1)

我们想，$a'=a-b$,$c-a'=c-(a-b)=c-a+b$.

相当于我们把 $b$ 通过 $a$ ,“置换”了出来。

这种“置换”只能存在于两个不同的集合。

所以现在考虑，最少可以只用 $2$ 个不同集合的数，把全部 $3$ 个集合“置换” 出来。

故选每个集合最小的数在取一下 $Min$。

这是一种情况，另一种是我们只用一个数“置换”另外两个集合，那他自己的集合只能全部减去。

综上就是这个题全部情况。

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int a,b,c;
int x[400000],y[400000],z[400000];
priority_queue<int,vector<int>,greater<int> >q1,q2,q3,q;
int sum1,sum2,sum3;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>a>>b>>c;
	int r1=1e9,r2=1e9,r3=1e9; 
	int sum=0;
	for(int i=1;i<=a;i++) cin>>x[i],sum1+=x[i],q1.push(x[i]);
	for(int i=1;i<=b;i++) cin>>y[i],sum2+=y[i],q2.push(y[i]);
	for(int i=1;i<=c;i++) cin>>z[i],sum3+=z[i],q3.push(z[i]);
	r1=1e9;
    sum=sum1+sum2+sum3;
    r1=min(sum1,min(sum2,sum3));
    //以上是情况2
    q.push(q1.top());
    q.push(q2.top());
    q.push(q3.top());
	r2=q.top();
	q.pop();
	r2+=q.top();
    //以上是情况1
	cout<<sum-2*min(r1,r2)<<endl;;
}
```

---

## 作者：lndjy (赞：1)

这个蒟蒻没有脑子，所以只会根据样例找规律。

先观察一下样例，很明显策略是把一个数堆成负数，然后把它加给一个正数。那么，被堆的数的贡献是负数。

仔细观察样例 $1$，和它一个集合的数不能堆给他，只能给别的数，那么被堆的数所在的集合的贡献就都是负数。

根据样例 $1$。我们得到了第一种可能的最优情况。就是一个集合为负数，剩下的为正数。

然后观察样例 $2$。发现 $1,2$ 贡献是负数，然后手玩策略，大概是这样的：

如果集合的数都很大不想浪费怎么办？那么就要把这个集合里除了最小的全部丢给一个其他集合里最小的数。那么就有了两个集合里最小的数是负数，其他的是正数。

于是，通过观察两个样例，我们过了这道题。

---

## 作者：_JF_ (赞：0)

[CF1467C Three Bags ](https://www.luogu.com.cn/problem/CF1467C)

~~这个标题可能是我第一个看懂的的英文标题，三个包。~~

首先观察阳历，可以发现就是大概的思路就是选某个集合 $x$，用其他集合的数把它搞成一个巨大的负数，然后喂给一个正数，让答案尽可能大。

不妨枚举喂的那个正数。然后不考虑它。同时注意同一个集合里面的数不能合并。

然后这时候有两种情况：

- 选的数在两个不同的集合里面，注意这时候我不能选和喂的正数在同一个集合里面数。

这时候观察到我们选两个数即可，因为两个数就足以把其他的所有数消掉了，显然的，我们选的数越多显然越不好。

为了让最后的负数尽可能大，我们应该选择两个集合里面最小的数，然后，让大的数消小的数所属集合的贡献，让小的消剩下另外集合的贡献。（~~这里为什么对的我也不清楚，~~ 理论上应该要再分类？）

然后分讨剩下如果，剩下两个负数的话，直接喂给正数即可，如果剩下一正一负，那就先把负的给正的，然后再喂。

- 选的数在同一个集合里面，记和为 $S$，因为该集合里面的数是不能互消的，所以只能用另外两个集合的数的和 $S1$ 去填，贡献就是 $S-S1$。

然后就做完了，大力分讨贪心，感觉做起来挺难受的。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10; 
#define int long long 
struct node{
	int val,id;
};
int ans,len,len1,len2,a[N],b[N],c[N],S[10];
signed main(){
	cin>>len>>len1>>len2;
	for(int i=1;i<=len;i++)		cin>>a[i],S[1]+=a[i];
	for(int i=1;i<=len1;i++)	cin>>b[i],S[2]+=b[i];
	for(int i=1;i<=len2;i++)	cin>>c[i],S[3]+=c[i];
	sort(a+1,a+len+1),sort(b+1,b+len1+1),sort(c+1,c+len2+1);
	int Minn1=a[1],Minn2=a[2],Minn3=b[1],Minn4=b[2],Minn5=c[1],Minn6=c[2];
	for(int i=1;i<=len;i++){
		int pre=S[1]-a[i];
		node now={Minn3,2},now1={Minn5,3};
		if(now.val>now1.val)	swap(now,now1);
		int lst=now1.val;
		now1.val-=S[now.id]-now.val;
		now.val-=pre,now.val-=(S[now1.id]-lst);
		if(now.val>0||now1.val>0){
			if(now.val>0)	ans=max(ans,a[i]-(now1.val-now.val));
			else	ans=max(ans,a[i]-(now.val-now1.val));
		}
		else	ans=max(ans,a[i]-now1.val-now.val);
	} 
	for(int i=1;i<=len1;i++){
		int pre=S[2]-b[i];
		node now={Minn1,1},now1={Minn5,3};
		if(now.val>now1.val)	swap(now,now1);
		int lst=now1.val;
		now1.val-=S[now.id]-now.val;
		now.val-=pre,now.val-=(S[now1.id]-lst);
		if(now.val>0||now1.val>0){
			if(now.val>0)	ans=max(ans,b[i]-(now1.val-now.val));
			else	ans=max(ans,b[i]-(now.val-now1.val));
		}
		else	ans=max(ans,b[i]-now1.val-now.val);
	} 
	for(int i=1;i<=len2;i++){
		int pre=S[3]-c[i];
		node now={Minn1,1},now1={Minn3,2};
		if(now.val>now1.val)	swap(now,now1);
		int lst=now1.val;
		now1.val-=S[now.id]-now.val;
		now.val-=pre,now.val-=(S[now1.id]-lst);
		if(now.val>0||now1.val>0){
			if(now.val>0)	ans=max(ans,c[i]-(now1.val-now.val));
			else	ans=max(ans,c[i]-(now.val-now1.val));
		}
		else	ans=max(ans,c[i]-now1.val-now.val);
	} 
	for(int i=1;i<=len;i++){
		ans=max(ans,a[i]-(S[2]-S[3]-(S[1]-a[i])));
		ans=max(ans,a[i]-(S[3]-S[2]-(S[1]-a[i])));	
	}
	for(int i=1;i<=len1;i++){
		ans=max(ans,b[i]-(S[1]-S[3]-(S[2]-b[i])));
		ans=max(ans,b[i]-(S[3]-S[1]-(S[2]-b[i])));	
	}
	for(int i=1;i<=len2;i++){
		ans=max(ans,c[i]-(S[2]-S[1]-(S[3]-c[i])));
		ans=max(ans,c[i]-(S[1]-S[2]-(S[3]-c[i])));	
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Hooch (赞：0)

### 题目大意

有 $3$ 个集合，分别有 $n_1,n_2,n_3$ 个数，每次可以选择两个**不同集合**的数（记为 $a$ 和 $b$）。

将 $a$ 替换成 $a-b$，最后一定只会剩一个数，让你求出最后这个数的**可能最大值**。

### 思路

我们可以看看样例解释，他**把一个数变成了负数**，这样才有最大值。

他就是选取了一个位置，将这个数**减去其他集合的数**，最后当**其他集合只剩一个数**时，作差得到了最大值。

于是我们可以想到一个策略：

选取一个位置，用这个位置减去其他集合的数（__除了最小值__）。

这个最小值用来干嘛呢？就是当这个位置减完了，我们用两个集合中任意一个集合的__最小值__减去这个绝对值巨大的负数。

接下来__剩下的那一个集合和另一个只剩最小值的集合作差__，将**两个绝对值相加**就是答案。

### 实现

我们尝试将上述的复杂的策略转化成代码。

我们首先将三个集合排序，得到了最小值，令为 $m_1,m_2,m_3$。用 $s_1,s_2,s_3$ 分别代表三个集合的和。

我们枚举一个任意集合中的数，将它的值令为 $X$​。

用这个数减去其他集合的数就是减去其他两个集合的 $s$。

这里为了方便起见，把最小值令为 $mi_1,mi_2$​​​​，其他两个集合的和表示成 $sum_1,sum_2$，这个集合的和是 $S$​​。

接着用上面的策略，得出最终的答案的公式是：
$$
ans = \max\{ans,\ (sum_1+sum_2-mi_1-mi_2)-X+\max(|S-X-mi_1|+mi_2,|S-X-mi_2|+mi_1)\}
$$
代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (register int i = j; i <= (int)(n); ++i)
#define rep2(i, j, n) for (register int i = j; i >= (int)(n); --i)
#define reg register int
#define il inline
#define ll long long
#define int ll
using namespace std;
const int Buffer_Size = 1 << 10;
char buffer[Buffer_Size], *ihead = buffer + Buffer_Size, *itail = ihead;
char Next_Char() {
    if (ihead == itail) fread(buffer, 1, Buffer_Size, stdin), ihead = buffer;
    return *ihead++;}
template <typename T>
il void read(T &x) {
    x = 0; T f = 1; char ch = Next_Char();
    while (!isdigit(ch)) {if (ch == '-') f = -1; ch = Next_Char();}
    while (isdigit(ch)) {x = (x << 1) + (x << 3) + (ch & 15); ch = Next_Char();} x *= f;
}
const int N = 3e5 + 5, inf = 0x3f3f3f3f, mod = 1;
int x, y, z, s1, s2, s3, a[N], b[N], c[N];
signed main(void) {
	read(x); read(y); read(z); 
	rep1(i, 1, x) read(a[i]);
	rep1(i, 1, y) read(b[i]);
	rep1(i, 1, z) read(c[i]);
	sort(a + 1, a + 1 + x); sort(b + 1, b + 1 + y); //排序得到最小值
	rep1(i, 1, x) s1 += a[i]; rep1(i, 1, y) s2 += b[i];
	rep1(i, 1, z) s3 += c[i]; int ans = 0; //算和
	rep1(i, 1, z) {
		int X = c[i];
		ans = max(ans, (s2 + s1 - a[1] - b[1]) - X + max(abs(s3 - X - a[1]) + b[1], abs(s3 - X - b[1]) + a[1]));
	} //枚举 X 在集合 3
	rep1(i, 1, y) {
		int X = b[i];
		ans = max(ans, (s1 + s3 - a[1] - c[1]) - X + max(abs(s2 - X - a[1]) + c[1], abs(s2 - X - c[1]) + a[1]));
	} //枚举 X 在集合 2
	rep1(i, 1, x) {
		int X = a[i];
		ans = max(ans, (s2 + s3 - b[1] - c[1]) - X + max(abs(s1 - X - b[1]) + c[1], abs(s1 - X - c[1]) + b[1]));
	} //枚举 X 在集合 1
	printf("%lld\n", ans);
}
```



---

## 作者：OYBDOOO (赞：0)

题意大概是有三个集合

进项一次操作，可以把分别位于两个集合的数$a,b$，进行$a=a-b$，删掉$b$的操作

考虑构造一棵树若选择$a,b$，$a$向$b$连一条边（$a$为爸爸）

可以发现树的偶数层被减掉，奇数层被加上

答案为奇数层减去偶数层

由于后面的层数差不多，可以想象树有三层

第一层只有一个点

若第二层的点位于两个集合，为了最小，选择两个集合最小的数

这样的话第三层可以填所有的数

若第二层的点位于一个集合，那么必须使得选择全集

这样第三层才能填

```cpp
/*=========================
Source:
Problem:
Author:OYBDOOO
Date:
Result:
=========================*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=3e5+10;
ll n1,n2,n3,all1,all2,all3,mi1,mi2,mi3,a1[maxn],a2[maxn],a3[maxn];
int main()
{
	ll i;
	cin>>n1>>n2>>n3;mi1=mi2=mi3=(1ll<<60);
	for(i=1;i<=n1;i++)cin>>a1[i],all1+=a1[i],mi1=min(mi1,a1[i]);
	for(i=1;i<=n2;i++)cin>>a2[i],all2+=a2[i],mi2=min(mi2,a2[i]);
	for(i=1;i<=n3;i++)cin>>a3[i],all3+=a3[i],mi3=min(mi3,a3[i]);
	ll all=all1+all2+all3;
	cout<<max(all-mi1*2-mi2*2,max(all-mi2*2-mi3*2,max(all-mi1*2-mi3*2,max(all1+all2-all3,max(all1+all3-all2,all2+all3-all1)))));
	//cout<<endl<<all<<" "<<all1<<" "<<all2<<" "<<all3<<" ";
	return 0;
}
```


---

## 作者：duyi (赞：0)

# CF1467C Three Bags

一次操作，相当于令 $a\texttt{-=}b$，并删除 $b$。由此可以发现一些性质：

1. 每个数都会“贡献”到答案里，只不过它们贡献的正负性不同。
2. 假设一个数 $a$ 在答案里贡献的正负性已知，则选择一个与它不在同一集合里的 $b$，可以进行的操作是，令 $b$ 的正负性与 $a$ 相反。
3. 最后一次被操作到的数 $a$，它的正负性必为正。

考虑每次操作 $(a,b)$，就把 $b$ 挂到 $a$ 下面。那么，以最后一次操作到的数为根，我们得到了一个**树形结构**。

假设根节点深度为 $0$，则树上每个节点 $u$ 对答案贡献的正负性，就是 $(-1)^{\text{dep}(u)}$。即奇偶层贡献的正负性交替。

另有一个限制是，不能存在父亲和儿子来自同一个集合。

我们要构造这样一棵树，使得权值和最小。有如下两种构造方法，取个 $\min$ 就是答案了：

1. 考虑枚举一个根。再枚举一个与根所在集合不同的集合 $t$ ($1\leq t\leq 3$)。令 $t$ 里的元素全部作为根的儿子。则可以发现，除 $t$ 里的元素贡献符号为负外，其他两个集合的元素全部为正。因此实际不必枚举根，只需要枚举 $t$ 即可。
2. 考虑枚举一个根。在另外两个集合里，各选一个最小的元素作为根的儿子。发现除这两个元素外的其他元素，对答案的贡献符号都可以为正。

时间复杂度 $\mathcal{O}(n)$。

参考代码：

```cpp
// problem: C
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

/* --------------- fast io --------------- */ // begin
namespace Fread {
const int SIZE = 1 << 21;
char buf[SIZE], *S, *T;
inline char getchar() {
	if (S == T) {
		T = (S = buf) + fread(buf, 1, SIZE, stdin);
		if (S == T) return '\n';
	}
	return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 21;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
	fwrite(buf, 1, S - buf, stdout);
	S = buf;
}
inline void putchar(char c) {
	*S++ = c;
	if (S == T) flush();
}
struct NTR {
	~ NTR() { flush(); }
} ztr;
} // namespace Fwrite
#ifdef ONLINE_JUDGE
	#define getchar Fread :: getchar
	#define putchar Fwrite :: putchar
#endif
namespace Fastio {
struct Reader {
	template<typename T>
	Reader& operator >> (T& x) {
		char c = getchar();
		T f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		x = 0;
		while (c >= '0' && c <= '9') {
			x = x * 10 + (c - '0');
			c = getchar();
		}
		x *= f;
		return *this;
	}
	Reader& operator >> (char& c) {
		c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		return *this;
	}
	Reader& operator >> (char* str) {
		int len = 0;
		char c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		while (c != '\n' && c != ' ') {
			str[len++] = c;
			c = getchar();
		}
		str[len] = '\0';
		return *this;
	}
	Reader(){}
} cin;
const char endl = '\n';
struct Writer {
	template<typename T>
	Writer& operator << (T x) {
		if (x == 0) { putchar('0'); return *this; }
		if (x < 0) { putchar('-'); x = -x; }
		static int sta[45];
		int top = 0;
		while (x) { sta[++top] = x % 10; x /= 10; }
		while (top) { putchar(sta[top] + '0'); --top; }
		return *this;
	}
	Writer& operator << (char c) {
		putchar(c);
		return *this;
	}
	Writer& operator << (char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer& operator << (const char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer(){}
} cout;
} // namespace Fastio
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl
/* --------------- fast io --------------- */ // end

const int MAXN = 3e5;
const ll LL_INF = 1e18;

int n[3];
ll a[3][MAXN + 5], sum[3], sumall, mn[3];

int main() {
	cin >> n[0] >> n[1] >> n[2];
	for (int t = 0; t < 3; ++t) {
		mn[t] = LL_INF;
		for (int i = 1; i <= n[t]; ++i) {
			cin >> a[t][i];
			sum[t] += a[t][i];
			ckmin(mn[t], a[t][i]);
		}
		sumall += sum[t];
	}
	ll ans = 0;
	// 策略1:
	for (int t = 0; t < 3; ++t) {
		ckmax(ans, sumall - sum[t] * 2); // 这一层全部作为根的儿子 
	}
	// 策略2:
	for (int t = 0; t < 3; ++t) { // 根节点 
		ll cur_ans = sumall;
		for (int tt = 0; tt < 3; ++tt) {
			if (tt == t)
				continue;
			cur_ans -= mn[tt] * 2;
		}
		ckmax(ans, cur_ans);
	}
	cout << ans << endl;
	return 0;
}
```





---

