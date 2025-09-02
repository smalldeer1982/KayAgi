# GCD-sequence

## 题目描述

最大公约数（GCD）是两个整数 $x$ 和 $y$ 可以整除的最大整数 $z$。例如，$\text{GCD}(36, 48) = 12$，$\text{GCD}(5, 10) = 5$，以及 $\text{GCD}(7,11) = 1$。

Kristina 有一个由正整数组成的数组 $a$，其中有 $n$ 个数。她想要计算相邻两个数的最大公约数，得到一个新数组 $b$，称为最大公约数序列。

因此，最大公约数序列的元素 $b$ 将使用公式 $b_i = \text{GCD}(a_i, a_{i + 1})$ 计算得到 $1 \le i \le n - 1$。

确定是否可以从数组 $a$ 中移除恰好一个数字，使得最大公约数序列 $b$ 是非递减的（即，$b_i \le b_{i+1}$ 始终为真）。

例如，如果 Khristina 有一个数组 $a = [20, 6, 12, 3, 48, 36]$。如果她从中移除 $a_4 = 3$ 并计算 $b$ 的最大公约数序列，她会得到：

+ $b_1 = \text{GCD}(20, 6) = 2$
+ $b_2 = \text{GCD}(6, 12) = 6$ 
+ $b_3 = \text{GCD}(12, 48) = 12$ 
+ $b_4 = \text{GCD}(48, 36) = 12$  

结果得到的最大公约数序列 $b = [2,6,12,12]$ 是非递减的，因为 $b_1 \le b_2 \le b_3 \le b_4$。

## 样例 #1

### 输入

```
12
6
20 6 12 3 48 36
4
12 6 3 4
3
10 12 3
5
32 16 8 4 2
5
100 50 2 10 20
4
2 4 8 1
10
7 4 6 2 4 5 1 4 2 8
7
5 9 6 8 5 9 2
6
11 14 8 12 9 3
9
5 7 3 10 6 3 12 6 3
3
4 2 4
8
1 6 11 12 6 12 3 6```

### 输出

```
YES
NO
YES
NO
YES
YES
NO
YES
YES
YES
YES
YES```

# 题解

## 作者：Lijiangjun4 (赞：6)

## 解题思路
解决这题需要分以下步骤：

1. 输入 $a$ 数组；
2. 通过 $\operatorname{gcd}$ 处理 $b$ 数组；
3. 预处理两个 bool 数组 $flag1$ 和 $flag2$，$flag1_i$ 表示 $b_1$ ~ $b_i$ 是否不降，$flag2_i$ 表示 $b_i$ ~ $b_{n-1}$ 是否不降；
4. 遍历每个 $a_i$ ，判断去掉 $a_i$ 后：
+ $b$ 数组左半部分是否不降 `flag1[i-2]`；  
+ $b$ 数组右半部分是否不降 `flag2[i+1]`；  
+ 新产生的 `gcd(a[i-1],a[i+1])` 是否合法。

**注意**边界特判。
不理解的，可以看图。（纠正：图片左下角的 `flag[i-2]` 应改为 `flag1[i-2]`。）

![](https://cdn.luogu.com.cn/upload/image_hosting/zf7huq20.png)

## AC Code
```cpp
#include<iostream>
#include<cstring>
using namespace std;
long long a[200005],b[200005],n;
long long gcd(long long x,long long y)
{
	//欧几里得算法求最大公因数 
	return y==0?x:gcd(y,x%y);
}
bool check()
{
	bool flag1[200005],flag2[200005];//flag1[i]表示从b[1]到b[i]是否不降,flag2[i]表示从b[i]到b[n-1]是否不降
	b[n]=2e9;
	for(int i=1;i<n;i++)
	{
		b[i]=gcd(a[i],a[i+1]);//预处理b[i] 
	}
	flag1[0]=true;
	for(int i=1;i<n;i++)
	{
		flag1[i]=flag1[i-1]&&b[i]>=b[i-1];//计算前缀 
	}
	flag2[n-1]=flag2[n]=true;
	for(int i=n-2;i>=1;i--)
	{
		flag2[i]=flag2[i+1]&&b[i]<=b[i+1];//计算后缀 
	}
	int ans=flag1[n-2]|flag2[2];//特判 
	for(int i=2;i<n;i++)
	{
		int k=gcd(a[i-1],a[i+1]);
		ans|=(
		flag1[i-2]&&//前缀
		flag2[i+1]&&//后缀
		k>=b[i-2]&&
		k<=b[i+1]//匹配左右 
		);
	}
	return ans;
}
int main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(check())
		{
			cout<<"YES\n";
		}
		else
		{
			cout<<"NO\n";
		}
	}
	return 0; 
}
```
一定要小心**第 31~37 行**的写法！

---

## 作者：haokee (赞：4)

先预处理 $\gcd(a_i, a_{i+1})$，存进 $b_i$，然后枚举删第 $i$ 个数，那么 $i$ 前面的相邻的最大公因数以及 $i$ 后面的相邻的最大公因数就必须递增。既然将 $i$ 删掉了，那么补充的元素就是 $\gcd(a_{i-1},a_{i+1})$，需要位于上一个 $b_i$ 和下一个 $b_i$ 的中间。

怎样快速求前缀或后缀 $b_i$ 都是单调非递增或单调非递减的呢？以前缀单调非递减举例，令 $p_i$ 表示 $1\sim i$ 当中的所有 $b_i$ 是否递增，那么求 $p_i$ 的时候如果 $p_{i-1}=0$ 就当然不满足条件啦，如果为真就看一下 $b_i$ 是否大于等于 $b_{i-1}$ 就行了。

```cpp
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 5;

int a[kMaxN], b[kMaxN], p[kMaxN], s[kMaxN], t, n, ans;

int gcd(int n, int m) {
  return !m ? n : gcd(m, n % m);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t; t--) {
    cin >> n, ans = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    p[0] = s[n] = 1, b[n] = 1e9;
    for (int i = 1; i < n; i++) {
      b[i] = gcd(a[i], a[i + 1]);
      p[i] = p[i - 1] && b[i] >= b[i - 1];
    }
    for (int i = n - 1; i; i--) {
      s[i] = s[i + 1] && b[i] <= b[i + 1];
    }
    for (int i = 1; i <= n; i++) { 
      ans |= (i <= 2 || p[i - 2]) &&
          (i >= n || s[i + 1]) &&
          (i == 1 || i == n || 
           (b[i - 2] <= gcd(a[i - 1], a[i + 1]) && 
            gcd(a[i - 1], a[i + 1]) <= b[i + 1]));
    }
    cout << (ans ? "YES" : "NO") << '\n';
  }
  return 0;
}
```

---

## 作者：jiangxinyang2012 (赞：3)

根据题意，如果由 $a$ 得到的数组 $b$ 的前 $n - 2$ 个元素是非递减的，删除 $a$ 的最后一个元素即可。否则，找到 $a$ 中的第 $i$ 个元素位置为递减的，即有：$\gcd(a_i, a_{i}) > \gcd(a_{i + 1}, a_{i + 2})$，删除这三个元素中的任意一个，判断对应的 $b$ 是否为非递减。如果存在 $b$ 为非递减数组，则可行，否则不可行。

---

## 作者：__zhuruirong__ (赞：2)

## 做法分析

观察题目，可以发现只会删除一个数字，那就可以想到用 $b$ 存储 $\gcd(a_i,a_{i+1})$，用 $pre_i$ 记录 $b$ 的从左数前 $i$ 位是否有序，用 $suf_i$ 记录 $b$ 的从右数前 $i$ 位是否有序，然后计算删除一个位置时会出现的新数是否可以满足不递减。注意要特判边缘位置的贡献。

## AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int T, n, a[N], b[N], pre[N], suf[N];

int main() {
  cin >> T;
  while(T--) {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i < n; i++) b[i] = __gcd(a[i], a[i + 1]);
    pre[1] = suf[n - 1] = 1;
    for(int i = 2; i < n; i++) pre[i] = pre[i - 1] & (b[i] >= b[i - 1]);
    for(int i = n - 2; i >= 1; i--) suf[i] = suf[i + 1] & (b[i] <= b[i + 1]);
    bool flag = false;
    for(int i = 3; i <= n - 2; i++) {
      if(pre[i - 2] && suf[i + 1] && __gcd(a[i - 1], a[i + 1]) >= b[i - 2] && __gcd(a[i - 1], a[i + 1]) <= b[i + 1]) {
        flag = true;
        break;
      }
    }
    if(suf[2] || suf[3] && __gcd(a[1], a[3]) <= b[3] || pre[n - 2] || pre[n - 3] && __gcd(a[n], a[n - 2]) >= b[n - 3] || flag) cout << "YES\n";
    else cout << "NO\n";
  }

  return 0;
}
```

---

## 作者：yshpdyt (赞：2)

## 题意
给定长为 $n$ 的序列 $a_i$，定义长为 $n-1$ 的序列 $b_i$ 满足 $b_i=\gcd(a_i,a_{i+1})$。问是否能删除 $a_i$ 序列的一个位置，让 $b_i$ 单调不降。

## Sol
~~是不是和 C 反了~~。

注意到删除操作只会导致 $b_i$ 删除两个数，增加一个数，只需要删除部分以前和以后分别单调不降，并判断增加的数是否大于等于左边，小于等于右边即可。

具体来说，维护每个前缀和后缀是否单调不降可以递推完成，先算出 $b_i$，然后不妨设 $l_i$ 表示 $[1,i]$ 是否单调不降，$r_i$ 表示 $[r,n]$ 是否单调不降。考虑删除的位置为 $i$，对应删除的应该是 $b_{i-1}$  和 $b_{i}$，新增的数为 $t=\gcd(a_i,a_{i+1})$，然后判断以下条件，有任意位置符合即可：

$$[l_{i-2}\land r_{i+1}\land b_{i-2}\le t\le b_{i+1}]=1$$

注意特判一下删除首尾位置。

##  Code 
``` cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,a[N],b[N],l[N],r[N];
void sol(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        l[i]=0,r[i]=0;
    }
    for(int i=1;i<n;i++)b[i]=__gcd(a[i],a[i+1]);
    b[n]=inf;
    b[0]=0;
    l[0]=1,r[n]=1;
    for(int i=1;i<n;i++)l[i]=(l[i-1]&&(b[i]>=b[i-1]));
    for(int i=n-1;i>=1;i--)r[i]=(r[i+1]&&(b[i+1]>=b[i]));
    if(r[2]){
        cout<<"YES\n";
        return ;
    }
    if(l[n-2]){
        cout<<"YES\n";
        return ;
    }
    for(int i=2;i<n;i++){
        ll t=__gcd(a[i-1],a[i+1]);
        if(l[i-2]&&r[i+1]&&t>=b[i-2]&&t<=b[i+1]){
            cout<<"YES\n";
            return ;
        }
    }
    cout<<"NO\n";
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}

```

---

## 作者：Daniel_yao (赞：1)

# Solve

考虑在原数列中删去一个数 $a_i$，$b$ 数列会怎样改变。

因为 $b_i=\gcd(a_i,a_{i+1})$，所以当 $a_i$ 删除时，会影响到 $b_i,b_{i-1}$。

先预处理出 $l,r$ 表示从左到右、从右到左递增序列的区间，即 $[1,l],[r,n]$ 为递增区间。

然后暴力枚举删除哪个 $a_i$，然后将 $a_i$ 影响到的 $b_i,b_{i-1}$ 删去，插入新贡献 $c=\gcd(a_{i-1}, a_{i+1})$。最后检查新贡献 $c$ 在数列中是否能让数列满足递增，即修改的区间 $[i-2,i+1]$ 能否拼接上 $[1,l],[r,n]$，并且 $b_{i-2} \leq c \leq b_{i+1}$。

总时间复杂度 $O(n)$。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)
#define inf 1e8

using namespace std;

const int N = 2e5 + 10;

int T, n, a[N], b[N];

void solve() {
  cin >> n;
  For(i,1,n) cin >> a[i];
  a[n+1] = a[0] = 0;
  For(i,1,n-1) b[i] = __gcd(a[i], a[i+1]);
  b[n] = inf;
  int l = 1, r = n-1;
  while(l <= n-1 && b[l+1] >= b[l]) l++;
  while(r >= 1 && b[r-1] <= b[r]) r--;
  if(l == n-2 || r == 2) {
    puts("YES"); return ;
  }
  For(i,1,n) {
    int New = __gcd(a[i-1], a[i+1]);
    if(New >= b[max(0ll, i-2)] && New <= b[min(n, i+1)] && l >= i - 2 && r <= i + 1) {
      puts("YES"); return ;
    }
  }
  puts("NO");
  return ;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：lhz123bc (赞：1)

这是一道简单但是充满细节的的题。

我们先看一下数据范围：$3 \leq n \leq 2 \times 10^5$。若时间复杂度为 $\mathcal{O}(n^2)$，显然在时间上是过不去的。

那么我们怎么判断一个数是否应该删除呢？可以定义一个长度为 $n - 1$ 的序列 $GCD_i$ 使得 $GCD_i=\gcd(shu_i,shu_{i+1})$。这个时候我们需要从前往后看看哪个地方使得 $GCD_i > GCD_{i+1}$，同理，也从后往前扫一遍，并分别用两个数组记录下来即可。最后一步从 $1 \sim n$ 挨个特判一遍，判断前一个和后一个是否都合法，还要判断前一个和后一个是否能接上，**注意首项和末两项的特判**。这就是这个题的完整思路。

[AC code](https://www.luogu.com.cn/paste/qor640h3)

---

## 作者：__LZH__ (赞：1)

# CF1980D GCD-sequence 题解

## 题意

有两个数组 $a$ 和 $b$，其中 $b_i$ 为 $a_i$ 与 $a_{i+1}$ 的最大公因数，请求出在 $a$ 可删至多 $1$ 个元素的情况下所对应的 $b$ 是否单调递增。

## 思路

首先 $3 \leqslant n \leqslant 2 \times 10^5$，肯定不能 $n^2$，可以花 $O(n)$ 的时间找前缀最大值与后缀最小值，然后判断如果删去是否符合条件即可。

直接上代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int gcd(int a, int b){
	return (!b) ? a : gcd(b, a % b);
}

int T, n, a[200010], b[200010], f1[200010], f2[200010];

int main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--){
  	cin >> n;
  	for(int i = 1; i <= n; i++){
  		cin >> a[i];
		}
		b[n] = 2e9;
		for(int i = 1; i < n; i++){
			b[i] = gcd(a[i], a[i + 1]);
		}
		f1[0] = 1;
		for(int i = 1; i < n; i++){
			f1[i] = f1[i - 1] && (b[i] >= b[i - 1]);
		}
		f2[n - 1] = f2[n] = 1;
		for(int i = n - 2; i >= 1; i--){
			f2[i] = f2[i + 1] && (b[i] <= b[i + 1]);
		}
		int f = f2[2] | f1[n - 2];
		for(int i = 2; i <= n - 1; i++){
			int k = gcd(a[i - 1], a[i + 1]);
			f |= (f1[i - 2] && f2[i + 1] && b[i + 1] >= k && k >= b[i - 2]);
		}
		cout << ((f) ? "YES\n" : "NO\n");
	}
  return 0;
}

```

---

## 作者：bryce (赞：0)

## 思路
先处理出每个 $b_i$，接着从前往后和从后往前扫一遍，找到从前往后非递减的最远的位置 $l$ 和从后往前非递减的最远的位置 $r$。

然后暴力枚举删除的 $a_i$，此时位置是 $i$，求出位置 $i$ 相邻两个的最大公约数，即 $k = \gcd(a_{i - 1}, a_{i + 1})$，将 $b_i$ 与 $b_{i - 1}$ 合并，它的上一个为 $b_{i - 2}$，下一个为 $b_{i + 1}$，判断 $k$ 是否大于等于 $b_{i - 2}$ 和是否小于等于 $b_{i + 1}$，还要满足 $i - 2$ 小于等于 $l$，$i + 1$ 大于等于 $r$ 使前一段和后一段的非递减序列能与 $k$ 拼接上。

接下来就是模拟时间。

## 代码

```cpp
#include<iostream>
#include<cstring>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 2e5 + 10;
int T, n;
int a[N], b[N], l, r;
int gcd(int x, int y){
    return (y == 0 ? x : gcd(y, x % y));
}

signed main(){
    T = read();
    while (T--){
        n = read();
        for (int i = 1; i <= n; i++) a[i] = read();
        for (int i = 1; i < n; i++) b[i] = gcd(a[i], a[i + 1]);
        l = 1;
        for (int i = 2; i <= n; i++){
            if (b[i - 1] <= b[i]) l = i;
            else break;
        }//找到最远前缀
        r = n - 1;
        for (int i = n - 2; i >= 1; i--){
            if (b[i + 1] >= b[i]) r = i;
            else break;
        }//找到最远后缀
        if (r <= 2 || l >= n - 2){
            cout << "yes\n";
            continue;
        }
        bool f = 0;
        b[n] = 0x7fffffff, b[0] = 0;
        for (int i = 2; i < n; i++){
            int k = gcd(a[i - 1], a[i + 1]), li = max(i - 2, 0ll), ri = min(i + 1, n);
            if (li <= l && ri >= r && k >= b[li] && k <= b[ri]){
                cout << "yes\n";
                f = 1;
                break;
            }//满足条件
        }
        if (!f) cout << "no\n";
    }
    return 0;
}
```

---

## 作者：banned_gutongxing (赞：0)

## 思路分析
直接枚举删除哪一个。

判断一个数的时候需要判断：
1. 前缀是否升序；
2. 后缀是否升序；
3. 断开的前一个和后一个是否能接上。

前缀和后缀直接预处理即可。

时间复杂度：$O(n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+10;
int T,n,a[MAXN];
int gcd[MAXN];
bool pre[MAXN],suc[MAXN];
map<int,int> apper,be;
signed main(){
	scanf("%d",&T);
	while(T--){
		apper.clear();be.clear();
		scanf("%d",&n);
		for(int i = 1;i<=n;i++){
			scanf("%d",a+i);
			if(i>1) gcd[i] = __gcd(a[i],a[i-1]);
		}
		gcd[0] = gcd[1] = 0;
		gcd[n+1] = 0x3f3f3f3f;
		pre[1] = pre[2] = true;
		for(int i = 3;i<=n;i++){
			pre[i] = pre[i-1]&&(gcd[i]>=gcd[i-1]);
		}
		suc[n] = suc[n-1] = true;
		for(int i = n-2;i>=1;i--){
			suc[i] = suc[i+1]&&(gcd[i+1]<=gcd[i+2]);
		}
		bool fg = 0;
		for(int i = 2;i<n;i++){
			int g = (__gcd(a[i-1],a[i+1]));
			if(pre[i-1]&&suc[i+1]&&g>=gcd[i-1]&&g<=gcd[i+2]){
				fg = 1;
				break;
			}
		}
		if(fg||pre[n-1]||suc[2]) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

第一次做 ```codeforces``` 的题，前两道没看，做了 ```C``` 题和 ```D``` 题，只有 ```D``` 题做对了，这题比 ```C``` 题简单多了。

------------

### 思路：

首先这数据范围肯定不能一个一个试，然后去判断，时间复杂度 $O(n^2)$。考虑优化，优化判断的部分，暴力的判断需要 $O(n)$ 的时间复杂度，考虑如何优化成 $O(1)$，由于我们发现，对于一个长度为 $n$ 的序列 $a$，如果删掉下标为 $x$ 的值，那么我们就要使 $b_1 \le b_2 \le b_3 ... \le b_{x-2} \le \gcd(a_{x-1},a_{x+1}) \le b_{x+1} \le b_{x+2} ... \le b_{n-1}$，因为删掉 $x$ 后和 $x$ 有关的都得删掉，于是离 $x$ 最近且比 $x$ 小而且和 $x$ 无直接关系的是 $x-2$，所以从 $b_1$ 到 $b_{x-2}$ 的值都得不下降，由于删了 $x$ 后，$a_{x-1}$ 和 $a_{x+1}$ 就有了直接联系，同时离 $x$ 最近且 大于 $x$ 而且和 $x$ 无直接关系的是 $x+1$，所以 $\gcd(a_{x-1},a_{x+1})$ 被夹在中间。

于是左边的 $b_1,b_2,...,b_{x-2}$ 和右边的 $b_{x+1},b_{x+2},...,b_{n-1}$ 都可用类似前缀和的方式做到 $O(n)$ 预处理。

总时间复杂度：$O(Tn)$。

------------

### 代码（细节过多，本人表述不好，全都放在代码注释里）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int a[N];
bool dao[N];//处理b[1],b[2],b[3],...,b[x-2]
bool zheng[N];//处理b[x+1],b[x+2],...,b[n-1]
int b[N];//题目中的b
signed main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i = 1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		for(int i = 1;i<=n-1;i++)
		{
			b[i] = __gcd(a[i],a[i+1]);//计算
		}
		zheng[1] = 1;//对于b[1]~b[1]，他一定是不下降的，因为只有一个数
		for(int i = 2;i<=n-1;i++)//因为b的下标最大值为n-1，所以只需要遍历到n-1
		{
			zheng[i] = (zheng[i-1]&&b[i]>=b[i-1]);//上一个是不下降的并且b[i]>=b[i-1]，那么从b[1]~b[i]就是不下降的
		}
		dao[n-1] = 1;//从b[n-1]~b[n-1]一定是不下降的，因为只有一个数
		for(int i = n-2;i>=1;i--)
		{
			dao[i] = (dao[i+1]&&b[i]<=b[i+1]);//简单易懂的递推公式
		}
		int ans = 0;
		for(int i = 1;i<=n;i++)
		{
			int qian = 0;//表示从b[1],b[2],...,b[i-2]是否不下降
			if(i == 1||i == 2)//i是1或2要特殊处理
			{
				qian = 1;
			}
			else
			{
				qian = (zheng[i-2] == 1);
			}
			int hou = 0;//表示从b[i+1],b[i+2],...,b[n]是否不下降
			if(i == n||i == n-1)//要特殊处理
			{
				hou = 1;
			}
			else
			{
				hou = (dao[i+1] == 1);
			}
			int cnt = 0;//表示gcd(a[i-1],a[i+1])是否被夹在中间
			if(i == 1||i == n)//特殊处理
			{
				cnt = 1;
			}
			else if(i == n-1)//第二种特殊处理
			{
				int t = __gcd(a[i-1],a[i+1]); 
				cnt = (t>=b[i-2]);
			}
			else//本来还有一种i == 2的特殊处理，但因为b[i-2] = b[0] = 0，t一定大于等于0，所以可以忽视
			{
				int t = __gcd(a[i-1],a[i+1]); 
				cnt = (t>=b[i-2]&&t<=b[i+1]);
			}
			if(qian&&hou&&cnt)//全都满足，数量加一
			{
				ans++;
			}
		}
		if(ans == 0)//如果没有一个满足题意
		{
			printf("NO\n");//不可能
		}
		else
		{
			printf("YES\n");//可以
		}
	}
	return 0;
}
```

---

