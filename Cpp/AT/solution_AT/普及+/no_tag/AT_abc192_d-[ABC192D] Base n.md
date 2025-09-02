# [ABC192D] Base n

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc192/tasks/abc192_d

`0` ～ `9` からなる文字列 $ X $ と、整数 $ M $ が与えられます。

$ X $ に含まれる最も大きい数字を $ d $ とします。

$ d+1 $ 以上の整数 $ n $ を選んで $ X $ を $ n $ 進法表記の数とみなして得られる値のうち、$ M $ 以下であるようなものは何種類あるでしょうか？

## 说明/提示

### 制約

- $ X $ は `0` ～ `9` のみからなる
- $ X $ の長さは $ 1 $ 以上 $ 60 $ 以下
- $ X $ の先頭の文字は `0` ではない
- $ 1\ \leq\ M\ \leq\ 10^{18} $

### Sample Explanation 1

$ X $ に含まれる最も大きい数字は `2` です。 - $ X $ を $ 3 $ 進法表記とみなして得られる値は $ 8 $ です。 - $ X $ を $ 4 $ 進法表記とみなして得られる値は $ 10 $ です。 得られる値のうち $ 10 $ 以下のものはこの $ 2 $ つのみです。

### Sample Explanation 2

$ X $ に含まれる最も大きい数字は `9` です。 - $ X $ を $ 10 $ 進法表記とみなして得られる値は $ 999 $ です。 - $ X $ を $ 11 $ 進法表記とみなして得られる値は $ 1197 $ です。 - $ X $ を $ 12 $ 進法表記とみなして得られる値は $ 1413 $ です。 得られる値のうち $ 1500 $ 以下のものはこの $ 3 $ つのみです。

### Sample Explanation 3

$ X $ を $ 2 $ 進法表記とみなして得られる $ 576460752303423488 $ が、唯一の $ 1000000000000000000 $ 以下の得られる数です。

## 样例 #1

### 输入

```
22
10```

### 输出

```
2```

## 样例 #2

### 输入

```
999
1500```

### 输出

```
3```

## 样例 #3

### 输入

```
100000000000000000000000000000000000000000000000000000000000
1000000000000000000```

### 输出

```
1```

# 题解

## 作者：EternalHeart1314 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc192_d)

# 思路

一看就知道 $X$ 转化成 $n$ 进制的 $X^{\text{'}}$ 有单调性，$n$ 越大，$X^{\text{'}}$ 也越大。

[但是！我在考场上一直没有切。](https://www.luogu.com.cn/record/list?pid=AT_abc192_d&user=982513)这是因为题目翻译有 BUG，题目中的“求 $n$ 的个数”应改成“求有多少个 $X^{\text{'}}$ 满足 $X^{\text{'}}\le M$。”特判一下就好。

要开 `unsigned long long`。

# Code
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;

int n, mx, l, r, mid, a[99];
string s;

int qwq(int x) {
	static int w, sum;
	w = 1, sum = 0;
	for(int i = 0; s[i]; ++ i, w *= x) {
		if(s[i + 1] && w > n / x) {
			return (int)9e18;
		}
		sum += a[i] * w;
	}
	return sum;
}

signed main() {
	cin >> s >> n;
	if(s.size() == 1) {
		return cout << (s[0] - '0' <= n), 0;
	}		//特判 
	reverse(s.begin(), s.end());
	for(int i = 0; s[i]; ++ i) {
		mx = max(mx, a[i] = s[i] - 48);
	}
	l = mx, r = 1e18 + 7;
	while(l < r) {
		mid = l + r + 1 >> 1;
		if(qwq(mid) <= n) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}
	return cout << l - mx, 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：_maple_leaf_ (赞：3)

### [原题](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc192_d)[链接](https://www.luogu.com.cn/problem/AT_abc192_d)
### 思路
- 刚看到这一题，以为是短除法+暴力枚举，看到数据，人都不淡定了，因此可以发现，时间复杂度肯定在 $O( \log n)$ 一下，于是想到二分和倍增。
- 但这题倍增实在想不出来，只能二分。
- 稍微思考一下，可以发现可以二分最大的 $k$ 然后减去 $d$。
- 证明一下单调性：设有一个 $k$ 进制下的 $({abc}
)_k$，拆开来为 $ak^3+bk^2+c(0\le a,b,c)$，若 $({abc})_{(k+1)}
 \le m$，即 $a(k+1)^3+b(k+1)^2+c \le m$，而 $ak^3+bk^2+c$ 一定小于 $a(k+1)^3+b(k+1)^2+c$，则 $ak^3+bk^2+c< m$。
- 知道单调性之后，便可以愉快的二分了~
- 但是还有一个小特性，就是如果 $X$ 的长度只有 $1$，那么 $m$ 大于 $X$ 则有一种，否则一种都没有。
- 同时，本题要用高精度，~~不过我太懒~~，就用 int128 了。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n[65];
short maxx=-1;
long long m,ans;
bool check(long long k){
	__int128 ret=0;//懒得开高精
	for(int i=0;i<s.size();i++){
		ret=ret*k+n[i];//进制转换
		if(ret>m)return 0;//大于就退出，并返回false
	}return 1;//返回true
}
short mmax(short a,short b){return (a>b?a:b);};
int main(){
	cin>>s>>m;
    if(s.size()==1){//特判最后说的情况
        if(m>=s[0]-'0')cout<<1;
        else cout<<0;
        return 0;
    }
	for(int i=0;i<s.size();i++)n[i]=s[i]-'0',maxx=mmax(maxx,n[i]);//转成数字，并找最大值
	long long l=maxx+1,r=m;
	while(l<r){
		long long mid=(l+r)/2+1;
		if(check(mid))l=mid;
		else r=mid-1;
	}if(check(l))cout<<l-maxx;//有可能l并不是答案，所以再判一下
	else cout<<l-maxx-1;//减去l的贡献
	return 0;
}
```
最后说句题外话，我赛时~~脑残~~将 check 写成了[短除法](https://www.luogu.com.cn/paste/6ugg8v2y)了

---

## 作者：fengenrong (赞：3)

这其实是一道二分的题目，我们不难发现只要那个数的进制越大，所表示的数就越大。比如第一个样例，$X$ 中最大的数字为 $2$，将 $X$ 看做 $3$ 进制，则 $X$ 的值为 $8$；将 $X$ 看做 $4$ 进制，则 $X$ 的值为 $10$，进制越大值就越大。

根据这个条件，我们就可以用二分了。通过枚举 $mid$ 来表示是 $mid$ 进制的值是否大于 $m$。而二分的范围则是，所有数中的最大值加一到 $m$。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
string x;
int a[100005], len;
int m;
bool check(int xx) {//判断
    __int128 sum = 0;//用sum来存储mid进制的值并使用__int128来存可以存很大
    for (int j = 0; j < x.size(); j++) {//枚举各个位置
        sum = sum * xx + a[j];//计算
        if (sum > m) {//不符合题意
            return false;
        }
    }
    return true;
}
signed main() {
    cin >> x >> m;
    for (int i = 0; i < x.size(); i++) {//转化为用int来存
        a[i] = x[i] - '0';
    }
    if (x.size() == 1) {//特判
        if (a[0] <= m) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
        return 0;
    }
    int maxa = 0;
    for (int i = 0; i < x.size(); i++) {
        maxa = max(maxa, a[i]);//求出所有数中的最大值
    }
    int ans = 0;
    int l = maxa + 1, r = m;//分别表示左端和右端
    while (l <= r) {//二分
        int mid = (l + r) >> 1;//求出中间值
        if (check(mid)) {//符合题意
            ans = max(ans, mid);//记录答案
            l = mid + 1;//缩小范围
        } else {
            r = mid - 1;//缩小范围
        }
    }
    if (ans == 0) {//没找到任何答案
        puts("0");
        return 0;
    }
    ans = ans - maxa;//减去左端
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Tachibana27 (赞：1)

有点思维的二分



------------
### 为什么二分？

不难发现 $x$ 的进制越大，$x$ 的值越大，此时二分 $x$ 的进制，是具有单调性的。当然，进制下界 $d$，上界 $m$。

### 代码实现

$x$ 有一点点大，而且数字类型输入比较麻烦，我们可以字符串读入，存到 int 类型的数组里。check 也很方便，将 $mid$ 进制的 $x$ 转换成十进制，与 $m$ 比较即可

想到二分还是比较水的。

code：

```cpp
%:include<bits/stdc++.h>
#define int __int128
inline int read()<%
	int s=0;
	int w=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
    	if(ch=='-')
			w=-1;
	for(;ch>='0' and ch<='9';ch=getchar())
		s=s*10+ch-'0';
	return s*w;
%>

void write(int x)<%
	if(x<0)<%
   		putchar('-');
   		x=-x;
	%>
	if(x>9)
    	write(x/10);
	putchar(x%10+'0');
	return;
%>//快读快写自动掠过
std::string s;
int a[10086];
int m;
int maxn;
int point;
bool check(int x){
	int sum=0;
    for(int i=1;i<=point;i++){
        sum=sum*x+a[i];
        if(sum>m)
            return false;
    }
    return true;
}//简短的check，将x进制转换十进制
int ans;
signed main()<%
  	//freopen(".in","r",stdin);
  	//freopen(".out","w",stdout);
	std::cin>>s;
	m=read();
	for(int i=0;i<s.size();i++)
		a[++point]=s[i]-'0';
	if(s.size()==1){
		if(a[1]>m)
			write(0);
		else
			write(1);
		exit(0);
	}
	for(int i=1;i<=point;i++)
		maxn=std::max(maxn,a[i]);
	int l=maxn;
	int r=1e18;
	while(l<=r){
		int mid=((l+r)>>1);
		if(check(mid)){
			l=mid+1;
			ans=std::max(ans,mid);
		}
		else
			r=mid-1;
	}//二分不要写错了，会出现死循环
	if(!ans)
		ans=maxn;//这样写等价于输出0
	write(ans-maxn);
  	return 0;//撒花
%>
```
~~管理快快审tj~~

---

## 作者：InversionShadow (赞：1)

洛谷翻译没有树脂！强烈不满！

模拟赛交了几十发，加个特判就过了。

题意中“求 $n$ 的数量”应该改为：在得到的值中，有多少种满足 $X^{'}\le M$。

一眼进制转换后的值具有单调性，二分出第一个 $X$ 转换成 $n$ 进制后大于 $M$ 的 $mid$，统计答案即可。

注意判定函数要开 `__int128` 或 `double` 等等。

当 $|X|=1$ 时，特判即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

string s;
int m, l, r, p, n;

bool check(int mid) {
  __int128 sum = 0;
  for (int i = 0; i < n; i++) {
    sum = (__int128)(sum * mid) + (__int128)(s[i] - '0');
     if (sum > (__int128)m) {
       return 0;
     }
   }
  return sum <= (__int128)m;
}

signed main() {
  cin >> s >> m;
  n = s.size();
  if (n == 1) {
    cout << ((s[0] - '0') <= m ? 1 : 0) << endl;
    return 0;
  }
  for (int i = 0; i < n; i++) {
    l = max(l, (long long)s[i] - '0');
  } 
  r = 1e18, p = l;
  int ans = p;
  while (l <= r) {
    int mid = (l + r) >> 1ll;
    if (check(mid)) {
      l = mid + 1;
      ans = mid;
    } else {
      r = mid - 1;
    }
  }
  cout << ans - p << endl;
  return 0;
}
```

---

## 作者：YuYuanPQ (赞：1)

# 洛谷 AT_abc192_d 题解

## $66pts$
其实我也不知道为什么考场上会想出 dfs 这种做法（严格来说应该不算），但是最后的分数还是**比较可观**的。

### 主要思路
首先，将 $X$ 视为一个 $n$ 进制数 $X'$。

**枚举** $n$ 进制，从字符串 $X$ 中的最大数字加 $1$ 开始。在此过程中，如果 $X'$ 比 $M$ 大就输出。

### 评测结果
$44$ 测试点；

$29$ `AC`，$14$ `TLE`，$1$ `WA`；

$66pts$。

### Code1
[云剪贴板链接](https://www.luogu.com.cn/paste/y1ioga6l)

### 时间复杂度
~~我**不会**算~~ 

貌似**算不了**。

如有人会算，欢迎[私信我](https://www.luogu.com.cn/chat?uid=1029900)。


## $91 pts$
考试之后，我对于 $66pts$ 很不满足，于是在教练讲之前，随便瞎改，得到了 $77pts$。

讲完，我觉得不服，没打正解。随后，在原来 $66pts$ 的基础上，加了对于个位数以及其他的特判，得到了 $91pts$。

### 特判的原因

这是为了**避免超时**。

因为第 $1$ 行的数，如果是个位数，且 $M$ 比第 $1$ 行的数要大。那么此时无论如何，在 $n$ 进制下的数值都是它本身，dfs 就会由于 $n$ 进制可以无限大，而超时。

**感谢**[zhangzhengyan0831](https://www.luogu.com.cn/user/715244)的反馈。

### 评测结果
$44$ 测试点；

$40$ `AC`，$4$ `TLE`；

$91pts$。

### 时间复杂度
~~我**不会**算~~ 

貌似还是**算不了**。

如有人会算，欢迎[私信我](https://www.luogu.com.cn/chat?uid=1029900)。

### Code2
[云剪贴板链接](https://www.luogu.com.cn/paste/8x02vc09)


## $100 pts$
后来，看到那**无药可救**的 `TLE`。

~~我陷入了沉思......~~

于是，按照教练讲的**正解**思路：**二分**，打了 $1$ 遍，然后**过了**。
### 主要思路
首先，套个二分模板。

然后，判断将 $n$ 进制数 $X$ 转为 $10$ 进制后是否小于或者等于 $M$；

如果**小了**，就往**大的**进制走，也就是 ```left=mid```；

如果**大了**，就往**小的**进制走，也就是 ```right=mid-1```；

全剧终。

### 评测结果
$44$ 测试点；

$44$ `AC`；

共 $100pts$。

### Code3
[云剪贴板链接](https://www.luogu.com.cn/paste/08nyy772)


### 时间复杂度
$O{( \log{M} \times \left| X \right| )}$。

### 成功抢到[**最优解**](https://www.luogu.com.cn/record/list?pid=AT_abc192_d&orderBy=1&status=&page=1)
[![最优解](https://cdn.luogu.com.cn/upload/image_hosting/awsuupj1.png)](https://www.luogu.com.cn/record/list?pid=AT_abc192_d&orderBy=1&status=&page=1)

# 另附
- 前 $2$ 种非正解解法的评测结果在我校评测平台上，正解评测结果在洛谷和我校评测平台均有。
- [题目链接](https://www.luogu.com.cn/problem/AT_abc192_d)
- 如有**更好**做法，欢迎[私信我](https://www.luogu.com.cn/chat?uid=1029900)。
- [我的提交记录](https://www.luogu.com.cn/record/list?pid=AT_abc192_d&user=1029900)
- 这是我第 $7$ 次写题解，如有错误请**指出**。

---

## 作者：minVan (赞：0)

**解题思路**

首先写造出判断函数 `check`，即将 $X$ 变为 $n$ 进制下的十进制值，再和 $m$ 比较，代码如下：

```cpp
inline bool check(int jz) {
  int ans = 0;
  for(int i = 0; i < n; i++) {
    int tmp = s[i] - '0';
    if((__int128_t)ans * jz + tmp > m) {
      return 0;
    }
    ans = ans * jz + tmp;
  }
  return 1;
}
```

注意在判断时要用 `__int128_t` 或 `double`。

接着由于答案显然具有单调性，所以可以二分，总时间复杂度为 $\mathcal{O}(\log_2n_{\max}\times|X|)=\mathcal{O}(63\times60)$ 跑得很快。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int m, n, maxi = -1;
inline bool check(int jz) {
  int ans = 0;
  for(int i = 0; i < n; i++) {
    int tmp = s[i] - '0';
    if((__int128_t)ans * jz + tmp > m) {
      return 0;
    }
    ans = ans * jz + tmp;
  }
  return 1;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> s >> m;
  n = s.size();
  for(int i = 0; i < n; i++) {
    maxi = max(maxi, (int)s[i] - '0');
  }
  if(n == 1) {
    cout << (maxi <= m);
    return 0;
  }
  int l = maxi + 1, r = 1e18, ans = maxi;
  while(l <= r) {
    int mid = (l + r) >> 1;
    if(check(mid)) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << ans - maxi;
  return 0;
}
```

---

## 作者：Super_Builder (赞：0)

这题翻译有误。可以看下讨论区
## 思路
我们考虑二分 $n$ 的值。

如果当前二分到的值合法，那么在 $d+1$ 到当前 $n$ 之间的值都合法，所以答案把答案范围往大找，否则往小的找。

如何判断合法呢？因为 $X$ 长度很小，所以可以枚举求出 $X$ 在 $n$ 进制下的值，再判断是否小于 $M$。小于 $M$ 则合法，否则不合法。

注意：

- 当 $X$ 长度为 1 时，$n$ 取任何数均可，而所有值均为同一数，所以应该把长度等于 1 的特判掉。

- 在求 $X$ 的 $n$ 进制下的值时可能会炸，所以应该在求的时候判断一下是否大于 $m$。

## AC CODE
写的码风不好，见谅。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long 
#define fst first
#define scd second
inline void write(int x){
    if(x<0)x=-x,putchar('-');
    if(x>=10)write(x/10);
    putchar(x%10+'0');
    return;
}
int m;
string s;
signed main(){
	cin>>s>>m;
	__int128 cnt=0;
	int f=0;
	for(int i=0;i<s.size();i++){
		f=max(f,(unsigned long long)s[i]-'0');
	} 
	if(s.size()==1){
		if(s[0]-'0'<=m)cout<<1;
		else cout<<0;
		return 0;
	}
	int l=f+1,r=LONG_LONG_MAX;
	while(l<=r){
		__int128 sum=0;
		bool ok=1;
		__int128 mid=l+r>>1ll;
		for(int j=0;j<s.size();j++){
			sum=sum*mid+(s[j]-'0');
			if(sum>m||sum>LONG_LONG_MAX){
				ok=0;
				break;
			}
		}
		if(sum<=m&&ok==1){
			cnt=mid-f;
			l=mid+1ll;
		}
		else r=mid-1ll;
	}
	write(cnt);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

一眼二分。

对于一个进制 $x$，我们可以暴力地将其转化成 $10$ 进制，然后和 $m$ 进行大小判断。如果比 $m$ 大，则表示我们的进制需要改小，否则看改大的情况是否可以。

很简单，然后你就会错 $11$ 个点。

为什么？想想就会知道在 $x$ 的位数为 $1$ 的时候，由于 $x^0=1$，所以无论我们怎么增大都没有区别。这个时候只需要把 $x$ 和 $m$ 的大小比较一下。

注：洛谷的翻译有点离谱，怎么是求 $n$ 的个数。

## 代码

[Link](https://atcoder.jp/contests/abc192/submissions/47173751).

---

## 作者：loser_seele (赞：0)

首先不难发现进制转换后的数有显然的单调性。

如果 $ \left| X \right|=1 $，则分类讨论即可，答案总为 $ 0 $ 或 $ 1 $。

所以考虑朴素二分，每次二分的时候判断进制转化后的答案是否满足条件即可。由于 $ X $ 是 $ 10 $ 进制数，所以答案最大为 $ M $，注意计算时可能会溢出。

时间复杂度显然为 $ \mathcal{O}(\left| X \right| \times \log{M}) $，来源于二分的时间复杂度和每次检查答案都需要遍历数组。

据说有严格 $ \mathcal{O}(\log{M}) $ 的做法，不过对于本题而言不是必要的。

代码：

```cpp
#import<bits/stdc++.h>
using namespace std;
#define ll long long
int main() 
{
    string X;
    ll M;
    cin>>X>>M;
    if(X.size()==1) 
    {
        if(stoi(X)<=M) 
        cout<<1;
        else 
        cout<<0;
        return 0;
    }
    int d=0;
    for(auto c:X) 
    d=max(d,c-'0');
    ll left=d;
    ll right=M+1;
    while(right-left>1) 
    {
        ll mid=(left+right)>>1;
        ll v=0;
        for(auto c:X) 
        {
            if(v>M/mid) 
            v=M+1;
            else 
            v=v*mid+c-'0';
        }
        if(v<=M) 
        left=mid;
        else
        right=mid;
    }
    cout<<left-d;
}
```


---

