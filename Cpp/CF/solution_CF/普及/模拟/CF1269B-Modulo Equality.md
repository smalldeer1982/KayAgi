# Modulo Equality

## 题目描述

你有一个正整数$m$和两个整数序列:

$a=[a_1, a_2, a_n]$和$b=[b_1,b_2b_n]$。

这两个序列的长度都是$n$。

然后将$a$序列中的数加上一个数$x$，$mod \ m$之后得到的序列改变或者不改变顺序与$b$序列相等.

## 样例 #1

### 输入

```
4 3
0 0 2 1
2 0 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2
0 0 0
1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5 10
0 0 0 1 2
2 1 0 0 0
```

### 输出

```
0
```

# 题解

## 作者：crpboy (赞：3)

$O(n\log n)$做法，十分优秀。

不难发现最终答案肯定是$[1,m]$之间的，而且满足条件的a,b序列相邻两数之间的差肯定是相同的。

于是我们把两个序列的相邻数字之间的差值都撸出来，然后哈希或者kmp匹配一下差值是否全部相同即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define dd ch=getchar()
inline int read()
{
	int x=0;char dd;bool f=false;
	while(!isdigit(ch))f|=ch=='-',dd;
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-48,dd;
	return f?-x:x;
}
#undef dd
void write(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+48);
}
#define writesp(x) (write(x),putchar(' '))
#define writeln(x) (write(x),putchar('\n'))

const int N=1e6+5;
int n,m,a[N<<1],b[N];
int oa[N<<1],ob[N];
int pre[N];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	if(n==1)return write((b[1]-a[1]+m)%m),0;
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++)
		b[i+n]=b[i]+m;
	for(int i=1;i<=n;i++)
		oa[i]=a[i];
	for(int i=1;i<=n<<1;i++)
		ob[i]=b[i];
	for(int i=1;i<n<<1;i++)
		b[i]=b[i+1]-b[i];
	for(int i=1;i<n;i++)
		a[i]=a[i+1]-a[i];
	pre[1]=0;
	for(int i=2,j=0;i<n;i++)
	{
		while(j&&a[j+1]!=a[i])j=pre[j];
		if(a[j+1]==a[i])j++;
		pre[i]=j;
	}
	int ans=0x3f3f3f3f;
	for(int i=1,j=0;i<n<<1;i++)
	{
		while(j&&a[j+1]!=b[i])j=pre[j];
		if(a[j+1]==b[i])j++;
		if(j==n-1)ans=min(ans,(-oa[1]+ob[i-j+1]+m)%m);
	}
	write(ans);
	return 0;
}
/*
a是模式串
b是文本串 
*/
```

---

## 作者：Dolphin_ (赞：2)

### CF1269B 题解
***

**题意**

给定$n(n<=2000)$，$m(m<=1e9)$，$a$数组，$b$数组，问把$a$数组都加上一个数（模$m$下），与$b$数组有唯一映射的最小解。

***

**解法**

对于每种可能的解：就是$(a[1]+m-b[i])$mod  m

然后去判断这个解是否行，并且维护最小解。

注意判断时不要用$map$，我被卡了$qwq$，直接排序比较即可。


复杂度$O(n * n * logn)$
****

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2200],b[2200],ans,n,m,x,tmp1[2200];
inline bool check()
{
	for(int i=1;i<=n;++i)
		tmp1[i]=(a[i]+x)%m;
	sort(tmp1+1,tmp1+1+n);
	for(int i=1;i<=n;++i)
		if(tmp1[i]!=b[i]) return false;
	return true;	
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	ans=0x7fffffff;
	sort(b+1,b+1+n);
	for(int i=1;i<=n;++i)
	{
		x=(b[i]+m-a[1])%m;
		if(check()) ans=min(ans,x);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：xuezhe (赞：2)

首先将 $b$ 排序。

枚举 $i \in [1,n]$，假定 $a_1 = b_i$，令 $x=(b_i-a_1+m)\bmod m$。

然后我们另建一个数组 $c$，使 $c_i=(a_i+x)\bmod m$。将 $c$ 排序后与 $b$ 比对，若完全相同，则当前 $x$ 为可行解，最后取最小值即可。

C++ 代码：
```cpp
#include <cstdio>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n,m;
ll a[2010],b[2010],c[2010],ans=0x7fffffffffffffffLL;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=n;++i)
		cin>>b[i];
	sort(b+1,b+1+n);
	bool can;
	for(int i=1;i<=n;++i){
		ll x=(b[i]-a[1]+m)%m;
		for(int j=1;j<=n;++j)
			c[j]=(a[j]+x)%m;
		sort(c+1,c+1+n);
		can=1;
		for(int j=1;j<=n;++j){
			if(b[j]^c[j]){
				can=0;
				break;
			}
		}
		if(can){
			ans=min(ans,x);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：liuyz11 (赞：2)

# 题解 CF1269B 【Modulo Equality】

**该场比赛题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12177652.html)**

题目大意：有两个长为$n$的数列$a$和$b$，现在让你给a中每个数加上一个数$x$并对$m$取模，并重新排列，使得两数列相同。求最小的$x$。

很明显x一定是在 $(a_1 - b_i + m)\mod m$ 中的一个数，我们只要枚举这个数，判断和数列$b$是否相同即可。

$n$最大只有2000，为了方便（我比较懒），判断相同时可以直接将$a$重新排序后判断，不会超时。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 2005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int a[MAXN], b[MAXN], c[MAXN];

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%d", &a[i]);
	rep(i, 1, n) scanf("%d", &b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	int ans = INF;
	rep(i, 1, n){
		int res = (b[1] - a[i] + m) % m;
		rep(j, 1, n) c[j] = (a[j] + res) % m;
		sort(c + 1, c + n + 1);
		bool flag = 1;
		rep(j, 1, n)
			if(c[j] != b[j]){
				flag = 0;
				break;
			}
		if(flag) ans = min(ans, res);
	}
	printf("%d\n", ans);
    return 0;
}
```

---

## 作者：wei2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1269B)

## 思路：
看到 $n \le 2000$，立刻思考暴力，但是在无任何优化的暴力情况下时间复杂度是 $\mathcal{O(m \times n \log n)}$，枚举所有的情况，并且每次扫一遍计算新的序列，再排序一遍，明显不行，会超时。

**优化：**

可以想到，暴力的 $m$ 完全是太大了，所以想想在这方面的优化，原本是枚举所有方案，但是这些方案大都不可行，打表观察符合条件方案的规律。可以发现对于答案，假设为 $x$，一定在 $b_i+m-a_1$ 的范围内，所以也只需要扫一遍 $b$ 序列，查找最小答案即可。
## 具体实现：
为了便于比较，我们可以将 $b$ 序列先排序一遍，再扫一遍 $b$ 序列，用一个新的数组来记录第 $i$ 次产生的新序列，再排序一遍，暴力比对，如果符合要求就与原本的最小值进行比对，去最小值，时间复杂度 $\mathcal{O(n\times n \log{n})}$。

**温馨提示：答案的初始值一定要给的足够大。**
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[2005],b[2005],x[2005],ans=0x7ffffffff;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		bool ok=0;
		long long xx=(b[i]+m-a[1]+m)%m;
		for(int j=1;j<=n;j++){
			x[j]=(a[j]+xx+m)%m;
		}
		sort(x+1,x+n+1);
		for(int j=1;j<=n;j++){
			if(x[j]!=b[j]){
				ok=1;
			}
		}
		if(!ok){
			ans=min(ans,xx);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：CznTree (赞：0)

### 题意

题意很好理解，就不说了。

### 题解

很显然，对于答案 $x$（每种可能的解），一定是在 $(m + b_i -  a_1) \bmod m$ 之间的，现在我们只要枚举该数即可。

将 $c$ 和 $b$ 都排个序，并且对 $c$ 与 $b$ 进行比较，最后取最小值即可。

### Code

```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr) 
#define rep(i, a, b) for (int i = a; i <= b; i++) 
#define per(i, a, b) for (int i = a; i >= b; i--) 
#define lc(x) x << 1ll
#define rc(x) x << 1ll | 1ll
#define lowbit(x) ((x) & (-x))
#define int long long 

const int N = 2e3 + 7; 
const int inf = INT_MAX; 
int a[N], b[N], c[N]; 
void solve() {
    int n, m; 
    std::cin >> n >> m; 
    rep(i, 1, n) {
        std::cin >> a[i];  
    }
    rep(i, 1, n) {
        std::cin >> b[i]; 
    }
    std::sort(b + 1, b + 1 + n); 
    int min = inf; 
    rep(i, 1, n) {
        int cal = (m + b[i] - a[1]) % m; 
        bool flag = true; 
        rep(j, 1, n) {
            c[j] = (a[j] + cal) % m; 
        }
        std::sort(c + 1, c + 1 + n); 
        rep(j, 1, n) {
            if(c[j] % m != b[j] % m){
                flag = false; 
            }
        }
        if(flag) {
            min = std::min(min, cal); 
        }
    }
    std::cout << min << std::endl; 
}

signed main() {
     IOS; 
     solve(); 
     return 0; 
}
```

---

