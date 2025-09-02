# [ABC179E] Sequence Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc179/tasks/abc179_e

$ x $ を $ m $ で割った余りを $ f(x,m) $ と表します。

初期値 $ A_1=X $ および漸化式 $ A_{n+1}=\ f(A_n^2,\ M) $ で定まる数列を $ A $ とします。$ \displaystyle{\sum_{i=1}^N\ A_i} $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{10} $
- $ 0\ \leq\ X\ <\ M\ \leq\ 10^5 $
- 入力は全て整数

### Sample Explanation 1

数列 $ A $ は $ 2,4,16,256,471,620,\ldots $ となるので、答えは $ 2+4+16+256+471+620=1369 $ となります。

### Sample Explanation 2

数列 $ A $ は $ 2,4,0,0,\ldots $ となるので、答えは $ 6 $ となります。

## 样例 #1

### 输入

```
6 2 1001```

### 输出

```
1369```

## 样例 #2

### 输入

```
1000 2 16```

### 输出

```
6```

## 样例 #3

### 输入

```
10000000000 10 99959```

### 输出

```
492443256176507```

# 题解

## 作者：asas111 (赞：2)

## 思路
一个个去加的时间复杂度为 $O(n)$，肯定会超时。

显然，当 $a_i$ 出现了 $2$ 次时，一定存在循环节，而且这个循环节的长度不超过 $m$，因为 $a_i$ 一共只有 $m$ 种，从 $0$ 到 $m-1$。

由于 $0< m\le 10^5$，所以可以考虑枚举循环节，这样就将序列分成 $3$ 个部分：循环节前的部分，循环节重复部分，结尾循环节不完整的部分。不过不是所有的序列都有完整的 $3$ 个部分，所以要进行判断。

第 $1$ 个部分和第 $3$ 个部分可以用前缀和算，第 $2$ 个部分直接用循环节重复次数乘以循环节之和就可以了。

时间复杂度为 $O(m)$，可以通过此题，记得开 long long。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200009
#define v x%m
#define l (d-c+1) //循环节长度
using namespace std;
int n,x,m;
int a[N],b[N],q=1,c,d,e[N],f[N],g=0,h=0,ans=0,k;
signed main(){
	cin>>n>>x>>m;
	while(1){
		a[q]=v;
		b[v]++;
		if(b[v]>1){d=q-1;k=v;break;}//发现出现2次的数
		q++;
		x=x*x%m;
	}
	for(int i=1;i<=d;i++)
		if(a[i]==k){c=i;break;}//寻找循环节头部位置
	for(int i=1;i<c;i++)
		h+=a[i],e[i]=e[i-1]+a[i];//计算循环节前的部分
	for(int i=c;i<=d;i++)
		g+=a[i],f[i+1-c]=f[i-c]+a[i];//计算尾部循环节不完整部分
	if(n>=c){//判断是否大于循环节头部位置
		ans+=h;
		ans+=(n-c+1)/l*g;
		ans+=f[(n-c+1)%l];
	}
	else ans+=e[n];
	cout<<ans;
	return 0;
}
```


---

## 作者：STARSczy (赞：1)

# 思路：
看到第一个样例，$x=2$，$m=1001$，数列为：

$$2,4,16,256,471,620,16,256,471,620,16,256,471,620,\ldots$$

可以看到，数列是存在循环节的。而数列中不同的数的个数不会超过 $mod$，即不超过 $10^5$，因此直接枚举循环节即可。注意开始还有一段，末尾还有一段。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int __int128/*保险起见开int128*/
using namespace std;
const int maxn=2e5+10,mod=1e9+7;
inline int read(){
	int c,w=0,n=0;
	while((c=getchar())<'0'||'9'<c) w=c=='-';
	do n=n*10+c-'0';while('0'<=(c=getchar())&&c<='9');
	return w?-n:n;
}
inline int write(int n){
	if(n<0) putchar('-'),n=-n;
	if(n>9) write(n/10);
	putchar(n%10+'0');
	return n;
}

int n=read(),x=read(),m=read(),ans,a[maxn],t[maxn],top,l,r,len,sum;

signed main(){
	a[1]=x,t[x]=1;
	for(top=2;;++top){//查找循环节
		a[top]=a[top-1]*a[top-1]%m;
		if(t[a[top]]){
			l=t[a[top]],r=top-1;
			break;
		}
		else t[a[top]]=top;
	}
	for(int i=1;i<=top;++i) a[i]+=a[i-1];//求前缀和，也可以麻烦一点不用前缀和
	len=r-l+1,sum=a[r]-a[l-1];//每段循环节
	n-=l-1,ans=a[l-1];//开头的那一段
	ans+=sum*(n/len),n%=len;//中间循环
	ans+=a[l-1+n]-a[l-1];//结尾的那一段
	write(ans);//输出
	return 0;
}
```

---

## 作者：lilong (赞：1)

### 题意

定义 $f(x,m)= x \bmod m$。

有一个序列 $a$，满足 $a_1=1$，$a_i=f(a_{i-1}^2,m)$。

求 
	
$$\sum_{i=1}^na_i$$

### 思路

这道题 $n$ 的数据范围很大，但 $m$ 最多只有 $10^5$，因此考虑以此为突破口。

需要用到如下的同余性质：

$$(a \times b) \bmod m = (a \bmod m \times b \bmod m) \bmod m$$

证明过程不详解。

有了这条性质，我们可以得知，当某个余数第二次出现时，则意味着出现了“循环节”（因为其再继续运算下去的结果也与先前一样）。因此，我们可以暴力计算前面的 $a_i$，同时找出“循环节”，找到即可终止循环。

接下来，我们要将序列分割为三部分计算。

1. “循环节”前非循环节部分

2. 完整的一段一段的“循环节”

3. 尾部不完整的“循环节”

具体实现详见代码。

### Code

```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

int pd[1000001],sum[1000001];

int ans,x,n,m,len,w,s;

signed main()
{
	cin >> n >> x >> m;
	for( int i = 1 ; true ; i++,x = x * x % m)
	{
		if(pd[x]) 
		{
			len = i - pd[x];
			w = pd[x];
			break;
		}
		else pd[x] = i;
		sum[i] = sum[i-1] + x;
	}
	ans = min ( n , w - 1 );
	ans = sum[ans]; //非循环节部分
	if( w < n ) 
	{
		s = n - w + 1;
		ans += ( sum[w + len - 1] - sum[w - 1] ) * (s / len );//完整的一段一段的“循环节”
		ans += sum[w - 1 + s % len] - sum[w - 1];//尾部不完整的“循环节”
	}
	cout << ans;
	return 0;	
} 
```


---

## 作者：taojinchen (赞：0)

# 思路
感觉就是数学题。

首先，对于每一个 $a_i$ 的值实际上只和 $a_{i-1}$ 有关，所以当 $a_i = a_j$ 其中 $j<i$ 时，就会产生循环，因为后面执行的操作和前面是相同的。

所以说循环节大小会不会很大，甚至没有？答案是不可能。因为 $m$ 是模数，$a_i$ 的取值最多只有 $m$ 个，$0 \le a_i < m$，所以说必定存在 $a_i = a_j,2 \le j<i \le m$，我们发现 $m \le 10^5$，所以我们只需要暴力模拟找循环节。

注意，要判第一个循环节以前和最后一个循环节以后的数的总和。
# 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll kM = 3e5 + 5;
ll n, m, x, i, j, s[kM], tx, vis[kM];
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> x >> m;
  tx = s[1] = x; //初始状态
  vis[x] = 1;
  for(i = 2; i <= m; i++){
    tx *= tx;
    tx %= m;
    s[i] = s[i - 1] + tx;//直接模拟
    if(vis[tx]) break;
    vis[tx] = i;//为了确定循环节大小
  }
  ll ans = ((s[i] - s[vis[tx]]) * ((n - vis[tx]) / (i - vis[tx]))); // i - vis[tx] 是循环节大小
  ans += s[((n - vis[tx]) % (i - vis[tx])) + vis[tx]] - s[vis[tx]];
  cout << (s[vis[tx]] + ans);
  return 0;
}
```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/AT_abc179_e)

## 题意

定义 $a_1=x,a_i=a_{i-1}^2\bmod m$，求 $\displaystyle\sum_{i=1}^{n}a_i$。

## 思路

由于 $m \le 10^5$，$a_i$ 的循环节至多为 $10^5$，于是我们可以暴力找出循环节并算出其的和。注意 $x$ 并不一定在循环节中，需要特殊判断。最后把前面和后面剩余不在循环节的部分额外加上即可。

时间复杂度为 $O(m)$。

## 代码

```cpp
// BLuemoon
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using DB = double;

const int kMaxN = 2e5 + 5;

LL n, x, m, a[kMaxN], ans, cnt = 1, s, tmp, sum, k, p, cnt_;
map<LL, bool> v;
bool flag;
vector<LL> e;

void pr(bool pr) {
  cout << (pr ? "Yes" : "No") << '\n';
}

int main() {
  cin >> n >> x >> m, v[x] = 1, e.push_back(x);
  for (tmp = x * x % m; !v[tmp]; v[tmp] = 1, e.push_back(tmp), (tmp *= tmp) %= m) {
  }
  for (LL o : e) {
    if (flag == 0 && o != tmp) {
      ans += o, cnt_++;
      if (cnt_ == n) {
        cout << ans << '\n';
        return 0;
      }
    } else if (flag == 0 && o == tmp) {
      flag = 1, sum += o;
    } else if (flag) {
      sum += o, cnt++;
    }
  }
  ans += sum * ((n - cnt_) / cnt);
  for (LL i = cnt_ + 1 + (n - cnt_) / cnt * cnt; i <= n; i++, (tmp *= tmp) %= m) {
    ans += tmp;
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：zcr0202 (赞：0)

## 题目大意

让你构造一个数组，求数组中的所有数之和。

## 解题思路

我们可以发现 $n$ 很大，因此我们不能直接构造数组，所以我们可以找规律来做。我们在手玩样例时可以发现会有循环节，那么我们找出循环节后用前缀和求出整个序列就可以了。

## Code

```
#include<bits/stdc++.h>
#define int long long
#define ready() ios::sync_with_stdio(0), cout.tie(0), cout.tie(0);
#define fre(a) freopen(#a".in", "t", stdin), freopen(#a".out", "w", stdout);
#define up(i, a, b) for(int i = a; i <= b; i++)
#define down(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 1e6 + 5;
const int mod = 998244353;
int n, x, m;
int a[N], d;
int h, t, ans;
map<int, int> mp;
signed main() {
	cin >> n >> x >> m;
	a[1] = x;
	mp[x] = 1;
	for (d = 2;; d++) {
		a[d] = a[d - 1] * a[d - 1] % m;
		if (mp[a[d]]) {
			h = mp[a[d]];
			t = d - 1;
			break;
		}
		mp[a[d]] = d;
	}
	up(i, 1, d) {
		a[i] += a[i - 1];
	}
	n -= h - 1;
	ans = a[h - 1];
	ans += (a[t] - a[h - 1]) * (n / (t - h + 1));
	n %= (t - h + 1);
	ans += a[h - 1 + n] - a[h - 1];
	cout << ans;
	return 0;
}
```

---

## 作者：DFbd (赞：0)

这是一道数学题，直接找周期，从前往后求 $a_i$ 并打标记，出现重复的就是找到周期了。

由于要求 $a_1$ 到 $a_n$ 的和，就算出周期的前缀和，再用周期重复次数乘周期内的数的和，加上最后一段不完整的周期的和。

但是周期的起始不一定是第一个，所以中途打标记时，把当前的 $i$ 记录下来，重复之后就可以直接找到前面不算在周期内的那一段的长度和总和，在最后算答案时，就把前面的排除，后面的就是从第一个开始周期了，算完后面的再加上前面的和就好了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node {
  long long b, d;
} c[100005];
long long n, x, m, a, ans[100005], sum;
int main() {
  cin >> n >> x >> m;
  a = x;
  while (!c[a].b) {
    sum++;
    ans[sum] = ans[sum - 1] + a;
    c[a].b = 1;
    c[a].d = sum;
    a = (a * a) % m;
  }
  cout << (ans[sum] - ans[c[a].d - 1]) * ((n - c[a].d + 1) / (sum - c[a].d + 1)) + ans[(n - c[a].d + 1) % (sum - c[a].d + 1) + c[a].d - 1];
  return 0;
}
```

---

## 作者：loser_seele (赞：0)

首先不难观察到有模数的存在，所以 $ a_i $ 的取值不超过 $ \bmod $ 种，所以实际上序列会以至多 $ \bmod $ 个数为循环节循环。

因为 $ \bmod $ 很小，所以可以暴力预处理找到周期，然后答案即为循环周期前面的数之和加上若干个循环节以及一个小节，前后两部分的答案可以暴力算，周期内的和预处理即可。

时间复杂度 $ \mathcal{O}(\bmod) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
long long n;
long long x,m;
int sa[100100];
long long add[100010];
int main()
{
	cin>>n>>x>>m;
	int Bit=1;
	long long l,r;
	for(long long a=x;;a=(a*a)%m,Bit++)
	{
		if(!sa[a]) 
		sa[a]=Bit;
		else
		{
			l=sa[a],r=Bit-1;
			break;
		}
		add[Bit]=add[Bit-1]+a;
	}
	long long len=r-l+1;
	long long ans=add[min(n,l-1)];
	n=max(0ll,n-l+1);
	if(n) 
	ans+=(add[r]-add[l-1])*(n/len)+(add[n%len+l-1]-add[l-1]);
	cout<<ans;
}
```


---

