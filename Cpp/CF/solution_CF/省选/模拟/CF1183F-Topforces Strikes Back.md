# Topforces Strikes Back

## 题目描述

著名编程平台 Topforces 即将举办一场重要的比赛！

出题人有 $n$ 道题目可供选择，需要从中选出最多三道题目组成本次比赛。第 $i$ 道题目的美观度为 $a_i$。出题人希望组成一场美观度总和尽可能大的比赛（也就是说，所选题目的美观度之和应尽量大）。

但在比赛准备过程中有一个重要的要求：由于出题人的一些迷信，所选题目的美观度不能互为整除关系。换句话说，若选中的题目的美观度为 $x, y, z$，则 $x$ 不能被 $y$ 或 $z$ 整除，$y$ 不能被 $x$ 或 $z$ 整除，$z$ 不能被 $x$ 或 $y$ 整除。如果选中两道题目的美观度为 $x$ 和 $y$，则 $x$ 不能被 $y$ 整除，$y$ 也不能被 $x$ 整除。任何只选一道题目的比赛都被认为是合法的。

你的任务是，对于每个询问，求出从给定题库中选出最多三道题目组成比赛时，所能获得的最大美观度总和。

你需要回答 $q$ 个独立的询问。

如果你使用 Python 编程，建议在提交代码时使用 PyPy。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
4
5 6 15 30
4
10 6 30 15
3
3 4 6
```

### 输出

```
30
31
10
```

# 题解

## 作者：wucstdio (赞：13)

## 题意

从$n$个数中选出来最多$3$个数，使得这三个数中不存在任意一个数是另一个数的倍数，同时使得这三个数的和最大。

## 题解

这是一道十分巧妙的贪心题。

首先我们将答案按照选出来的数字个数分情况。

### 一

如果选出来的数字个数为$1$，显然答案就是最大的数字。

### 二

如果选出来的数字个数为$2$，我们考虑最大的数$a$是否在最优答案里。

答案是肯定的，因为如果选出来的两个数$x,y$都不是$a$，那么这样的答案一定不会更大。证明如下：

1、如果有一个数不是$a$的因数，那么直接用$a$替换这个数。

2、如果两个数都是$a$的因数，那么这两个数的和最大是$\dfrac a2+\dfrac a3<a$，也就是说我们在步骤一中就已经得到最优解了。

所以对于这一种情况，我们只需要选出来最大的数，然后从剩下的数中找到一个不是它的因数的最大的数即可。

### 三

如果选出来的数字个数为$3$，我们还是考虑最大的数$a$是否在最优答案里。

可以发现，如果选出来的三个数中有一个或两个数不是$a$的因数，那么就可以由情况二进行证明，一定要选出来$a$。

而如果三个数都是$a$的因数，我们发现有唯一的一种特殊情况：$\dfrac a2+\dfrac a3+\dfrac a5>a$，其余的都小于$a$。

所以我们需要特判一下$\dfrac a2+\dfrac a3+\dfrac a5$这种情况，特判完后就选出来最大的$a$并把它所有的因数删掉，然后用情况二中的方法来做。

时间复杂度$O(n)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int t,n,a[200005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			ans=max(ans,a[i]);
		}
		sort(a+1,a+n+1);
		int an=a[n];
		bool flag1=0,flag2=0,flag3=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]*2==an)flag1=1;
			if(a[i]*3==an)flag2=1;
			if(a[i]*5==an)flag3=1;
		}
		if(flag1&&flag2&&flag3)ans=max(ans,an/2+an/3+an/5);
		for(int i=1;i<=n;i++)
		  if(a[n]%a[i]==0)a[i]=2000000000;
		sort(a+1,a+n+1);
		while(a[n]==2000000000)n--;
		ans=max(ans,an+a[n]);
		for(int i=1;i<=n;i++)
		  if(a[n]%a[i]!=0)ans=max(ans,an+a[n]+a[i]);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：夜猫子驱蚊器 (赞：4)

Div. 3的题，竟然卡了好久，自闭.jpg  
好像我的思路不太一样呢QAQ

首先注意到，如果一个数是另一个的因子，那它肯定不会出现在答案中。

我们先把所有数排序，然后对每个数，我们要往前再找两个数（或者一个，都差不多，就不区分了）和它凑个答案，那我们暴力往前扫，如果碰到它的因子，就直接将这个因子从数列中删掉；如果不是它的因子，就加到答案里，凑满 $3$ 个就`break`。

Q：那这样做找到的前面两个数万一有倍数关系咋办？  
A：不存在的，因为我们之前就把所有数的因子删掉了。  
Q：那怎么删啊？set？map？  
A：删除的话，用类似链表的东西维护下就好了。  
Q：你这个辣鸡做法好暴力啊，复杂度？  
A：扫到每个数的时候，它要么被删掉，要么被统计到答案里了，所以每组是 $O(n)$ 的，再加`sort`的 $O(nlogn)$，还挺快的亚子，目前洛谷是rank 3。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define re register
#define fr(i,x,y) for(int i=(x);i<=(y);i++)
#define frz(i,x,y) for(int i=x,z=y;i<=z;i++)
#define rf(i,x,y) for(int i=(x);i>=(y);i--)
#define frl(i,x,y) for(int i=(x);i<(y);i++)
using namespace std;
const int N=200003;
int n,a[N],p[N];

inline void read(int &x){
	char ch=getchar();x=0;int w=0;
	for(;ch<'0'||ch>'9';ch=getchar()) if (ch=='-') w=1;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	if (w) x=-x;
}

int main(){
	//init();
	int T;
	read(T);
	while(T--){
		read(n);
		fr(i,1,n) read(a[i]);
		sort(a+1,a+1+n);
		int ans=0;
		fr(i,1,n) p[i]=i-1;
		fr(i,1,n){
			int sum=a[i],s=1,x=i;
			while(s<3&&x){
				if (a[i]%a[x]) s++,sum+=a[x];
				while(p[x]&&a[i]%a[p[x]]==0) p[x]=p[p[x]];
				x=p[x];
			}
			ans=max(ans,sum);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

最后当然是例行宣传[博客](https://www.cnblogs.com/ymzqwq/p/cf1183f.html)啦


---

## 作者：紊莫 (赞：1)

有点神秘的贪心。

注意到题目中“至多”的要求，容易想到分类讨论。

1. 选择 $1$ 个数字，显然是最大值。
2. 选择 $2$ 个数字，那么一定是选择最大值后再选择一个**合法**的最大值。
3. 选择 $3$ 个数字，那么先选择一个最大值，然后转化为再选 $2$ 个。

先解释一下为什么一定要选最大值，假设现在选了两个数字，如果有不是最大值的因数的数字，直接替换成最大值答案更优。否则，两个数之和最大为 $\dfrac{\max}{2}+\dfrac{\max}{3}<\max$。

然后是三个数，看起来似乎没什么问题？

但是注意到一个事情，$\dfrac{\max}{2}+\dfrac{\max}{3}+\dfrac{\max}{5}>\max$。显然，这是唯一一个满足此条件的情况，特判即可。

我感觉这个贪心加上特判还是蛮牛的。

[示例代码。](https://www.luogu.com.cn/paste/xl9xx87y)

稍微解释下，因为 $a_i$ 的值域不大，所以可以直接暴力枚举因数再删除，我用了 ``set`` 来辅助运算，取最大值的时候不要用 ``*end()``，应该是 ``*rbegin()``。

---

## 作者：MuYC (赞：1)

#### 前言

这道题目是一道非常巧妙的贪心。

难度：4星

#### 简略题意：

给定一个长度为 $n$ 的序列,在序列中取**至多**三个数，使得这取的数互不为倍数关系。 $a[]$，$a_i <= 2 * 10 ^ 5 , n <= 2 * 10 ^ 5$

#### 具体做法：

因为是最多取 3 个数，不妨按取的数的个数进行分类讨论。

+ $Case 1$ ： 取一个数

这样的话当然是取最大的那个数最优，Pass。

+ $Case 2$：取两个数

通过手玩几组样例后，我们发现最大的那个数总是出现在 取两个数得到的最大值中。于是大胆猜想，最后的答案一定会包含最大的数。

首先约定最大的数为 $Max$

接下来我们严谨证明这一点：

证明：$a + b <= c + Max$ （$a , b$不能为最大值,$a != b,c$有可能取不到）

这时候，进行分类讨论：

倘若 $a,b$ 都是 $Max$ 的因子，$a,b$不同，所以$max(a + b)$ = $\frac{Max}{2} + \frac{Max}{3}$，不等式成立。这时候显然应该取 $Max$ 能得到最优解，那么无法构造一个序列使得等式不成立。

倘若 $a,b$ 其中一个是 $Max$ 的因子，可以使得等式右边的那个 $c$ 等于 $a,b$ 中 不是 $Max$ 的因子的数，不等式成立。这时候应该取 $Max + c$ 能得到最优解。

倘若 $a,b$ 都不是 $Max$ 的因子, 我们可以使得等式右边的那个 $c$ 等于 $a,b$ 中 较大的不是 $Max$ 的因子的数，不等式成立。这时候显然应该取 $Max + c$ 能得到最优解。

所以两个数的情况的最大值无论如何都会包含 $Max$。

因此两个数的做法就是：取序列中的最大值，然后取不是 $Max$ 的因子的数中的最大值，两个数相加得到两个数的情况的最优解。

+ $Case 3$： 取三个数。

这是一个重头戏。

根据我们在 $Case 2$ 中证明的结论来看，我们第三个情况也应该朝那个方向思考。

假设取三个数 :

$a + b + c <= d + e + Max$ ($a,b,c$互不为倍数关系并且小于等于最大值 $Max$ , $d,e$ 有可能取不到)

+ 倘若 $a,b,c$ 都是 $Max$ 的因子。 那么 $max(a + b + c)$ = $\frac{Max}{2} + \frac{Max}{3}  +\frac{Max}{5}  = \frac{31Max}{30}$ ,不难发现这个情况下，构造一个序列，其中的所有数都是 $Max$ 的因子，取 $a + b + c$ 是优于取 $Max + d + e$ 的(d + e不存在)。因此在这种情况下不等式有可能不成立，于是我们特判一下是否同时存在 $\frac{Max}{2},\frac{Max}{3},\frac{Max}{5}$。

+ 倘若$a,b,c$ 其中一个不是 $Max$ 的因子，那么不妨令等式的右边的 $d,e$ 中任意一个等于这个非 $Max$ 的因子的数，那么就转化到了 $Case2$ 中两个数都是 $Max$ 的因子的情况，不再赘述。这时候取 $Max + d + e$  取得最优解。

+ 倘若$a,b,c$ 其中两个不是 $Max$ 的因子，那么不妨令等式的右边的 $d,e$等于这两个非 $Max$ 的因子的数，剩下的一个数必然小于等于 $Max$

+ 倘若$a,b,c$ 三个都不是 $Max$ 的因子，同上面两个不是 $Max$ 的因子的情况，不再赘述。

所以说：取三个数的做法就是：首先特判一下是否存在 $\frac{Max}{2},\frac{Max}{3},\frac{Max}{5}$ 都为 $Max$ 的因子，这种情况下对于答案取一个 $max$，使得情况如果存在就被考虑。 接下来取 $Max$ ， 然后删去所有 $Max$ 的因子（要取 $Max$ 的话，$Max$ 的因子一定不出现在最后答案里面）

接下来就变成了取两个数的情况。

在剩下的数里面仍然取 $Max$ ， 按照两个数的做法做即可。
```cpp
#include <bits/stdc++.h>
using namespace std; 
const int MAXN = 2e5 + 50;
int arr[MAXN],n,Maxa;
int ST[MAXN],T[MAXN];

inline int read()
{
    int x = 0 , flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}

int main()
{
    int Q;
    cin >> Q;
    for(int v = 1 ; v <= Q ; v ++)
    {
        n = read();
        for(int i = 1 ; i <= n ; i ++)
            arr[i] = read(),ST[arr[i]] = arr[i];
        sort(arr + 1 , arr + 1 + n);
        int Max = arr[n];
        Maxa = arr[n];
        //上面是取两个数的最大情况。
        int f2 = 0,f3 = 0,f5 = 0;
        if(Maxa % 5 == 0 && ST[Maxa / 5] != 0) f5 = 1; //ST是一个桶
        if(Maxa % 3 == 0 && ST[Maxa / 3] != 0) f3 = 1; 
        if(Maxa % 2 == 0 && ST[Maxa / 2] != 0) f2 = 1;
        if(f2 && f3 && f5)
        Max = max(Max,Maxa / 5 + Maxa / 3 + Maxa / 2);//特判
        for(int i = 1 ; i <= n ; i ++)
        {
            T[i] = arr[i];
            if(arr[n] % T[i])
            Max = max(Max,arr[n] + T[i]);
        }//这里是取两个数的情况，求一个Max
        for(int i = 1 ; i <= n ; i ++)//首先取Max，删掉Max的因子
            if(Maxa % T[i] == 0) T[i] = 2e9;
        int M = 0;
        for(int i = 1 ; i <= n ; i ++)
            if(T[i] != 2e9)M = max(M,T[i]);//找出剩下的数的里面的最大值
        for(int i = 1 ; i <= n ; i ++)//按照两个数的做法做
            if(M % T[i] != 0 && T[i] != 2e9) Max = max(Max,Maxa + M + T[i]);
        cout << Max << endl;
        for(int i = 1 ; i <= n ; i ++)
            ST[arr[i]] = 0;//多组数据，清空桶
    }
    return 0;
}
```

---

## 作者：decoqwq (赞：1)

先使用贪心策略，选取最大的后选取另外两个

注意到能与最大的相互整除的三个数并且加起来大于最大的的情况只有$\frac{a}{2}+\frac{a}{3}+\frac{a}{5}>a+...$，所以只需要枚举$\frac{a}{2},\frac{a}{3},\frac{a}{5}$是否存在即可

```cpp
/**************************/
/*It is made by decoration*/
/*gzzkal   gzzkal   gzzkal*/
/*It is made by decoration*/
/**************************/
#include <bits/stdc++.h>
using namespace std;
string a;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> vc;
        map<int,int> mp;
        for(int i=1;i<=n;i++)
        {
            int x;
            scanf("%d",&x);
            vc.push_back(x);
            mp[x]=1;
        }
        sort(vc.begin(),vc.end());
        int ans=vc[n-1];
        for(int i=n-2;i>=0;i--)
        {
            if(vc[n-1]%vc[i]!=0)
            {
                ans+=vc[i];
                for(int j=i-1;j>=0;j--)
                {
                    if(vc[n-1]%vc[j]!=0&&vc[i]%vc[j]!=0)
                    {
                        ans+=vc[j];
                        break;
                    }
                }
                break;
            }
        }
        int ans1=0;
        if(vc[n-1]%2==0&&vc[n-1]%3==0&&vc[n-1]%5==0)
        {
            if(mp[vc[n-1]/2]&&mp[vc[n-1]/3]&&mp[vc[n-1]/5])
            {
                ans1=(vc[n-1]/30)*31;
                if(ans1>ans)
                {
                    cout<<ans1<<endl;
                }
                else
                {
                    cout<<ans<<endl;
                }
                continue;
            }
        }
        cout<<ans<<endl;
    }
} 
```

---

## 作者：喵仔牛奶 (赞：0)

## Solution

一个神秘做法（？）

考虑 $a$ 中的最大值 $x$ 选不选：
- 如果选，那么最优解中剩下的数一定都不是 $x$ 的因子。
- 如果不选，那么最优解一定都是 $x$ 的因子。

不选的结论的证明：
- 如果最优解只有一个数是 $x$ 的因子，将这个数替换成 $x$ 是更优解。
- 如果最优解有三个数且两个数是 $x$ 的因子，那么这两个数之和必然不超过 $\frac{x}{2}+\frac{x}{3}<x$，将这两个数替换成 $x$ 即可。

综上，每次将 $a$ 分成两份求解递归求解即可。复杂度不会算，但是应该是对的。

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	int n, x; vector<int> s;
	int slv(vector<int> &s, int k) {
		if (!SZ(s)) return -1e9;
		if (k == 1) return s[0];
		vector<int> p, q;
		for (int x : s) {
			if (s[0] % x) p.pb(x);
			else if (x != s[0]) q.pb(x);
		}
		return max({slv(p, k - 1) + s[0], slv(q, k)});
	}
	int main() {
		cin >> n, s.clear();
		REP(i, 1, n) cin >> x, s.pb(x);
		sort(ALL(s), greater<>());
		cout << max({s[0], slv(s, 2), slv(s, 3)}) << '\n';
		return 0;
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int T = 1; cin >> T;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：CQ_Bab (赞：0)

# 思路
这不是性质题吗？

首先我们可以考虑只取一个，这个很好求直接取 max 即可。
然后我们可以想到一个贪心，从小到大遍历每一个数，每次先将 $i$ 的因数给删掉，然后看剩余的 set 中最大的两个的和（这里 set 中的值都小于 $i$），用它们的和来更新答案，这种解法看似很错，但是打完之后发现能过，然后理性证明一下发现十分有道理。

我们考虑这种贪心什么情况下有问题，我们定义 $a,b,c$ 其中 $c\bmod a=0,c\bmod b=0$ 就是我们在遍历到 $c$ 时会将 $a,b$ 都删掉，此时如果有 $a+b>c$ 便可证明这种贪心错了，因为 $c\bmod a=0,c\bmod b=0$ 这里的 $a,b$ 一定是 $c$ 最大的两个因数不然不优，因为 $a\neq b$ 所以 $a,b$ 一定等于 $c\div 2,c\div 3$ 而因为 $c\times 5\div 6<c$，所以一定有 $a+b>c$ 此贪心便得证。
# 代码
非常简单。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T;
int n;
int res;
const int N=2e5+10;
int a[N],vis[N];
set<int>s;
void solve() {
	in(n);
	res=0;
	s.clear();
	rep(i,1,n) in(a[i]),res=max(res,a[i]),vis[a[i]]=1;
	int Max=res;
	rep(i,1,Max) {
		if(!vis[i]) continue;
		rep(j,1,i/j) {
			if(i%j==0) {
				if(s.find(j)!=s.end()) {
					s.erase(j);
				}
				if(s.find(i/j)!=s.end()) {
					s.erase(i/j);
				}
			}
		}
		if(s.size()) {
			int sum=false;
			sum=*s.rbegin();
			if(s.size()>=2) {
				auto it=s.end();
				it--;
				it--;
				sum+=*it;
			}
			res=max(res,i+sum);
		}
		s.insert(i);
	}
	rep(i,1,n) vis[a[i]]=0;
	printf("%lld\n",res);
}
fire main() {
	in(T);
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：灵茶山艾府 (赞：0)

暴力出奇迹。

写一个三重 for 循环，从大到小找最大的数 $a_i$，然后再找次大的数 $a_j\ (a_j\nmid a_i)$，和第三大的数 $a_k\ (a_k\nmid a_i, a_k\nmid a_j)$。由于一个数的非因子个数远多于因子个数，对于内部的两层循环，找到若干个非因子后一定能找到符合要求的答案。

AC 代码 （Golang）:

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
	"sort"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	max := func(a, b int) int {
		if a > b {
			return a
		}
		return b
	}

	var t, n int
	for Fscan(in, &t); t > 0; t-- {
		Fscan(in, &n)
		a := make([]int, n)
		for i := range a {
			Fscan(in, &a[i])
		}

		// 排序+去重
		sort.Ints(a)
		j := 0
		for i := 1; i < n; i++ {
			if a[j] != a[i] {
				j++
				a[j] = a[i]
			}
		}
		ans := a[j]
		n = j + 1
		a = a[:n]

		// 从大到小三重循环，内部的两层循环最多找 10 个非因子
		for i := n - 1; i >= 0; i-- {
			ai := a[i]
			cnt := 0
			for j := i - 1; j >= 0; j-- {
				aj := a[j]
				if ai%aj != 0 {
					ans = max(ans, ai+aj) // 找到一个二元组
					cnt2 := 0
					for k := j - 1; k >= 0; k-- {
						ak := a[k]
						if ai%ak != 0 && aj%ak != 0 {
							ans = max(ans, ai+aj+ak) // 找到一个三元组
							if cnt2++; cnt2 == 10 {
								break
							}
						}
					}
					if cnt++; cnt == 10 {
						break
					}
				}
			}
		}
		Fprintln(out, ans)
	}
}
```

---

## 作者：米奇 (赞：0)

## 思维题

首先发现n个数会形成若干关系树（关系森林）

考虑一个数选或不选。

若选那么他的因数都不能选，若不选那么只有一种情况，即$ai/2+ai/3+ai/5=31*ai/30$

我们就暴力选最大的即可，同时特判一下不选的那种情况即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define next Next
const int N=1e6+5;
int n,a[N],b[N],vis[N],q[N];
/*char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}*/
#define gc getchar
inline int read()
{
	int ret=0,f=0;char c=gc();
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){ret=ret*10+c-48;c=gc();}
	if(f)return -ret;return ret;
}
bool cmp(int a,int b)
{
	return a>b;
}
signed main()
{
	int T=read();
	while(T--)
	{
		int gs=0,ans=0,r=0,ma=0;
		n=read();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			b[a[i]]=1;
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			if(!vis[a[i]])
			{
				vis[a[i]]=1;
				gs++;
				ans+=a[i];
				if(gs==3)break;
				for(int j=1;j*j<=a[i];j++)
					if(a[i]%j==0)
					{
						vis[j]=1;
						vis[a[i]/j]=1;
						q[++r]=j;
						q[++r]=a[i]/j;
					}
			}
			if(a[i]%30==0&&b[a[i]/2]&&b[a[i]/3]&&b[a[i]/5])ma=max(ma,a[i]/2+a[i]/3+a[i]/5);
		}
		ma=max(ma,ans);
		cout<<ma<<endl;
		for(int i=1;i<=n;i++)b[a[i]]=vis[a[i]]=0;
		for(int i=1;i<=r;i++)vis[q[i]]=0;
	}
}
```

---

