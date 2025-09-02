# [ABC342D] Square Pair

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc342/tasks/abc342_d

長さ $ N $ の非負整数列 $ A=(A_1,\ldots,A_N) $ が与えられます。以下の条件を共に満たす整数組 $ (i,j) $ の個数を求めてください。

- $ 1\leq\ i\ <\ j\leq\ N $
- $ A_i\ A_j $ は平方数
 
ここで非負整数 $ a $ は、ある非負整数 $ d $ を用いて $ a=d^2 $ と表せる場合平方数と呼ばれます。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 0\leq\ A_i\leq\ 2\times\ 10^5 $
 
### Sample Explanation 1

条件を満たす整数組は $ (i,j)=(1,2),(1,3),(1,4),(1,5),(2,5),(3,4) $ の $ 6 $ つです。 例えば、$ A_2A_5=36 $ であり $ 36 $ は平方数なので、$ (i,j)=(2,5) $ は条件を満たします。

## 样例 #1

### 输入

```
5
0 3 2 8 12```

### 输出

```
6```

## 样例 #2

### 输入

```
8
2 2 4 6 3 100 100 25```

### 输出

```
7```

# 题解

## 作者：Hughpig (赞：12)

考虑两个非负整数 $a,b$，如果 $a\times b$ 是完全平方数，只有两种情况：

* $a=0$ 或 $b=0$，此时 $a\times b=0$，很显然是完全平方数。

* $a\times b$ 是完全平方数且不为 $0$。

对于第二种情况，我们发现一个完全平方数乘一个完全平方数还是完全平方数。具体的，$x^2\times y^2=(x\times y)^2$。

所以一个完全平方数因子对 $a\times b$ 是不是完全平方数没有影响。记 $a'$ 为 $a$ 除去所有完全平方数因子，$b'$ 为 $b$ 除去所有完全平方数因子。

因为 $a'$ 和 $b'$ 没有完全平方数因子，所以只有 $a'=b'$ 时，$a'\times b'$ 才是完全平方数。

所以我们可以把所有 $A_i$ 除去完全平方数因子。每个非 $0$ 数对答案的贡献是在此之前 $A_i$ 出现次数之和加上 $0$ 的出现次数和。$0$ 对答案的贡献是 $i-1$ （前面所有 $i-1$ 个数乘以 $0$ 都是 $0$，是完全平方数）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,a[200007],times[200007],ans;

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=2;j*j<=a[i];++j){
			while(a[i]%(j*j)==0)a[i]/=(j*j);
		}
	}
	for(int i=1;i<=n;i++){
		if(a[i])ans+=times[a[i]],ans+=times[0];
		else{
			ans+=i-1;
		}
		times[a[i]]++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：N0_1 (赞：3)

## 题意
给定一个长度为 $n$ 的序列，询问有多少组 $(i, j)$ 满足 $a_{i}\times a_{j}$ 为完全平方数且 $i <j$。

### 数据范围
$2\leq N\leq 2\times 10^5$

$0\leq A_i\leq 2\times 10^5$

### 基本结论
当正整数 $x$ 为完全平方数时，令 $x$ 分解质因数的结果为 

$$x = p _ {1} ^ {k_{1}}\times p _ {2} ^ {k_{2}}\times p _ {3} ^ {k_{3}}\times p _ {i} ^ {k_{i}}$$

则对于所有的 $k_{i}$，其一定是偶数。

### 推论
若 $x$ 不是完全平方数，则至少有一对 $p _ {i} ^ {k_{i}}$ 的 $k_{i}$ 为奇数（假设只有这一对为 $2^3$，例如 $8$），若 $x\times y$ 为完全平方，则 $y$ 分解质因数的结果，当且仅当存在 $2^{k}$，且 $k$ 为奇数。

### 例如
$x = 24$，其分解质因数的结果为 $24 = 2^3\times 3^1$，则对于所有满足 $x\times y$ 为完全平方数成立的 $y$，其分解质因数的结果 

$$y = 2^{k_{1}} \times 3 ^ {k_{2}}\times p _ {3} ^ {k_{3}}\times p _ {i} ^ {k_{i}}$$

满足 $k_{1}$ 为奇数，$k_{2}$ 为奇数，$k_{i}$为偶数（$i\ge 3$）。

### 求解
考虑到 $1$ 个 $2$ 与 $1$ 个 $3$ 的乘积为 $6$（~~思考为什么不考虑 $3$ 个 $2$ 与 $1$ 个 $3$ 的乘积？~~），对于 $a_{i} = x$，只需要考虑在 $i$ 之前，有多少个 $a_{k}$ 满足 $a_{k}$ 分解质因数后的乘积为 $6$ 即可($k < i$)，这一步可以 $O(n)$ 求解，分解质因数的时间复杂度为 $O(\sqrt n)$，总时间复杂度为 $O(n\times \sqrt n)$。

### code
```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 2e5 + 10;
int a[N], pre[N];

int solve(int x) {
	int num = 1;
	for (int i = 2; i <= x / i; i++) {
		int cnt = 0;
		while (x % i == 0) {
			cnt ++;
			x /= i;
		}
		if (cnt & 1) num *= i;
	}
	return num * x;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);	

	int n; cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	
	LL ans = 0;
	for (int i = 1; i <= n; i++) {
		if (!a[i]) {
			ans += i - 1;
			pre[0] ++;
			continue ;
		}
		int num = solve(a[i]);
		ans += pre[num] + pre[0];
		pre[num] ++;
	}
	
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：Otue (赞：3)

先将所有数写成唯一分解形式，去掉平方因子。

观察到如果 $d^2=a\times b$，那么 $a$ 去掉平方因子后和 $b$ 去掉平方因子的数相等。简单证明：

* 若 $a,b$ 都为平方数，去掉平方因子后都为 $1$。
* 否则，$a,b$ 就都不为平方数，如果乘积为平方数，则表示这两个数的奇数次幂因子互补，则奇数次幂都为 $1$。

那么我们开个桶来存储，计算之前有多少个数去掉平方因子后和该数相等即可。注意特殊处理 $0$。

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5, base = 131;

int n, a[N], vis[N], prime[N];
pair<int, int> tt[N];
int len;

int check(int x) {
	if (x == 2) return 1;
	for (int i = 2; i <= x / i; i++) {
		if (x % i == 0) return 0;
	}
	return 1;
}

signed main() {
	cin >> n;
	int ans = 0;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] == 0) { // 特殊处理 0 
			ans += n - (cnt + 1);
			cnt++;
			continue;
		}
		int t = a[i]; len = 0;
		for (int j = 2; j <= t / j; j++) {
			if (t % j == 0) {
				int cnt = 0;
				while (t % j == 0) t /= j, cnt++;
				tt[++len] = {j, cnt % 2};
			}
		}
		if (t > 1) tt[++len] = {t, 1};
		int res = 1;
		for (int j = 1; j <= len; j++) {
			if (tt[j].second) res = res * tt[j].first;
		}
		ans += vis[res];
		vis[res]++;
	}
	cout << ans << endl;
}
```

我的代码肯定不是最简化的，事实上，可以牺牲一点效率，直接枚举所有平方数，让 $a_i$ 除以他们（当然要求没有余数），就是去掉平方因子后的数。

祝大家学习愉快！

---

## 作者：PikachuQAQ (赞：3)

## **Description**

### [**D - Square Pair**](https://atcoder.jp/contests/abc342/tasks/abc342_d)

## **Solution**

不妨将每个 $a_i$ 开根然后化简。例如： $\sqrt{12}=\sqrt{2^2\times3}=2\sqrt{3}$。

关于这个化简的实现也很简单，我们可以将 $a_i$ 所有的平方数因子抽出来。

注意到当任意两个数的根号下的数相同时，它们的乘积一定是完全平方数。例如：$x=12,y=27,\sqrt{x}=2\sqrt{3},\sqrt{y}=3\sqrt{3}$，其中根号下的数均为 $3$，而且 $\sqrt{xy}=18$。

所以我们可以给所有根号下的数开个桶，设当处理到 $a_i$ 时，当前根号下的数的出现次数为 $x$，多一个数显然可以多组成 $x$ 对答案对，答案加上 $x$，然后 $x$ 自增 $1$ 即可。

但要注意，$0$ 可以和任何数组合，所以 $0$ 单独计算。

## **Code**

```cpp
// 2024/2/25 PikachuQAQ

#include <iostream>

using namespace std;

typedef long long ll;

const int kMaxN = 2e5 + 7;

int n;
ll g[kMaxN], ans;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (ll i = 1, x, f, j; i <= n; i++) {
        for (cin >> x, f = x, j = 2; j * j <= f; j++) {
            while (f % (j * j) == 0) f /= j * j;
        }
        ans += g[f], g[f]++;
    }
    cout << ans + (g[0] * (n - g[0]));
    
    return 0;
}
```

---

## 作者：whx2009 (赞：2)

## 本题思路：
这道题其实很简单，我们知道两个数相乘如果要是完全平方数，那么他因式分解后的质数每一个都会有偶数个，那么我们就可以直接把这些数字偶数个的质数除掉，那么剩下的部分如果两个数相等就可以成为一组。

这样我们就可以直接用一个桶记录每一个数字有多少个，然后直接等差求和即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200001],b[200001];
map<int,int>s;
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){cin>>a[i];b[i]=a[i];}
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	int sum=0;
	for(int i=1;i<=n;i++){
		if(a[i]==b[i-1]){
		s[a[i-1]]++;a[i]=a[i-1];continue;}
		sum=1;
		int u=a[i];
		for(int j=sqrt(u);j>=2;j--){
			if(a[i]%j==0){
				for(int k=j*j;;a[i]/=k,k*=(j*j)) if(a[i]%k!=0) break;
			}
		}
		s[a[i]]++;
	}
	int ans=0;
	for(int i=1;i<=200000;i++){
		if(s[i]>0){ans+=s[i]*(s[i]-1)/2;
		}
	}
	cout<<ans+(n-1+n-s[0])*(n-(n-s[0]))/2;
	return 0;
}
```

---

## 作者：Dream_poetry (赞：2)

### 翻译：
给定一个长度为 $n$ 的序列 $A$，求有多少组 $(i,j)$ 使得 $A_i A_j$ 是一个完全平方数且 $i<j$。

### 思路：
暴力，死得很惨。

不难发现，两个完全平方数相乘也是一个完全平方数，也就是说，若 $A_i A_j$ 是一个完全平方数，则 $A_i A_j$ 可以表示为 $x^2y^2$ 的形式。

也就是说，若 $A_i$ 与 $A_j$ 不同且 $A_iA_j$ 是完全平方数，则两者分别除掉自己所包含的非 $1$ 的完全平方数后相等。

知道了这个原理，我们直接将每个 $A_i$ 都化简为最简，然后用计数器累加，最后计算结果即可。

注意判断零。

### 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, ans, num, sp, a[500005], cnt[500005], tot[500005];
signed main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		for (int j=2;j*j<=a[i];j++){
			int v=j*j;
			while (a[i]%v== 0)	a[i]/=v;
		}// 处理 
		cnt[a[i]]++;
		tot[i]=tot[i-1]+(a[i]==0);
	}
	for (int i = 1; i <= n; i++){
		if (!a[i]) op+=n-tot[i];// 判 0 
		else ans+=cnt[a[i]]-1;
	}
	cout<<ans/2+op;// 因为 Ai*Aj 和 Aj*Ai都计算了，所以要除以2 
	return 0;
}
```


---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc342_d)

## $\mathtt{Solution}$

考虑按照顺序枚举 $a_i$。

对于每一个 $a_i$，求出最小的使得 $a_i\times p$ 为平方数的 $p$。

然后枚举答案 $q$，即组成的数为 $a_i\times p\times q^2$，此时只需要看有多少个数是 $q^2\times p$ 就行了。

最后，要将 $0$ 进行特判，因为 $0$ 与任何数相乘都是平方数，所以如果有 $k$ 个 $0$，最后答案要加 $\dfrac{(2n-k-1)k}{2}$。

时间复杂度 $O(n\sqrt n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5;
struct node{
	int x, y;
};
int n, ans, cnt, a[MAXN], num[MAXN];
vector<node>g;
signed main(){
	n = read();
	for(int i = 1;i <= n;i ++){
		a[i] = read();
		int h = a[i];
		if(h == 0){
			cnt ++;
			continue;
		}
		g.clear();
		for(int j = 2;j * j <= h;j ++){
			int ct = 0;
			if(h % j == 0){
				while(h % j == 0){
					ct ++;
					h /= j;
				}
				g.push_back({j, ct});
			}
		}
		if(h != 1)g.push_back({h, 1});
		int p = 1;
		for(node v : g){
			int vx = v.x, vy = v.y;
			if(vy % 2)p *= vx;
		}
//		printf("%lld %lld\n", i, p);
		for(int j = 1;j * j * p <= 200000;j ++)
			ans += num[j * j * p];
		num[a[i]] ++;
	}
	printf("%lld\n", ans + (n * 2 - cnt - 1) * cnt / 2);
	return 0;
}

```


---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc342_d)

## 思路

这题本质是质因数分解。

假设我们有一个数，质因数分解出来是 $a\times a\times b$；另外一个数分解出来是 $b\times c\times c$。不难发现这两个数相乘的结果是 $a^2\times b^2\times c^2$，是 $abc$ 的平方。

所以我们可以统计每个数质因数分解后有**奇数个**的因子之积。如果两个数奇数个因子之积相同，那么这两个数相乘一定是一个平方数（如上面给出的例子）。这个积的数量 $k$ 的贡献为 

$$\sum_{i=1}^{k-1}i$$

但是由于 $0\le A_i\le 2\times 10^5\space(1\le i\le N)$，我们需要特殊考虑 $A_i=0$ 的情况。此时数列中任何一个数 $A_j\space(j\not=i)$ 和 $A_i$ 相乘均为平方数。由于我们要保证相乘的两个数**不能重复计算**（如 $(0,4)$ 和 $(4,0)$ 应算作一对），所以还要每次减去当前已访问过的 $0$ 的个数。

我们设每个非零数的贡献值为 $k_i$ 且总共有 $m$ 个非零数（**去重后**），$0$ 的个数为 $num$，则最终答案为：

$$\sum_{i=1}^{num}(n-i)+\sum_{i=1}^m \sum_{j=1}^{k_i-1}j$$

- 记得开 long long。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){//快读
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
const int N=2e5+10;
int n,cnt,p[N],x[N],h[N];//h 数组是这个数处理完后的结果。
ll ans,cnt0,tom[N];
bool vis[N];
int main(){
    cin>>n;
    vis[1]=1;
    for(int i=2;i<=(int)2e5;++i){//处理出质数。
        if(!vis[i])p[++cnt]=i;
        for(int j=1;j<=cnt&&i*p[j]<=(int)2e5;++j){
            vis[i*p[j]]=1;
            if(i%p[j]==0)break;
        }
    }
    for(int i=1;i<=n;++i){
        x[i]=read();
        if(!x[i]){//0 的特判。
            ++cnt0;
            continue;
        }
        int t=x[i],tmp=1;
        if(h[x[i]]){//优化：访问过直接记录。
            ++tom[h[x[i]]];
            continue;
        }
        for(int j=1;j<=cnt;++j){//分解质因数。
            if(p[j]>t)break;//优化：大于当前值的质数不可能整除。
            if(t&&t%p[j]==0){
                int num=0;
                while(t&&t%p[j]==0){
                    t/=p[j];
                    ++num;
                }
                if(num&1)tmp*=p[j];
            }
        }
        ++tom[tmp];
        h[x[i]]=tmp;
    }
    memset(vis,0,sizeof vis);
    for(int i=1;i<=n;++i){
        if(vis[h[x[i]]])continue;
        ll k=tom[h[x[i]]];
        vis[h[x[i]]]=1;//标记重复。
        ans+=k*(k-1)/2;//计算非零数的贡献。
    }
    ans+=n*cnt0-cnt0*(cnt0+1)/2;//计算 0 的贡献。
    cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/148299765)

---

## 作者：Genius_Star (赞：1)

### 题意：

给定一个长度为 $n$ 的序列 $a$，其中第 $i$ 个数为 $a_i$。

求有多少个 $(i,j)$ 满足 $a_i \times a_j$ 是一个完全平方数。

### 思路：

根据**唯一分解定理**，任意一个大于 $1$ 的正整数都可以分解为以下形式：

$$x=\sum_{i=1}^k p_i^{s_i}$$

那么如果一个数 $d$ 是**完全平方数**，则：

$$d=(\sum_{i=1}^k p_i^{s_i})^2=\sum_{i=1}^k p_i^{2 \times s_i}$$

所以对于 $a_i$ 和 $a_j$，需要满足两者乘积的**质因子分解**形式的每一个指数都是偶数.

则考虑先将每一个数的所有**偶数幂次**剔除，然后将所有**奇数幂次**的幂次改为 $1$（因为答案只看**奇偶数**，所以对答案不影响），设 $a_i$ 进行**剔除**后的值为 $b_i$。

那么只要 $b_i=b_j$ 满足，则 $a_i \times a_j$ 就是完全平方数了，于是开个桶记录一下即可，对于 $0$ 要特判一下。

时间复杂度为 $O(N \sqrt{W}$)。

**注意要先排序。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,ans,sum;
ll a[N],b[N],s[N];
void solve(ll x){
	if(!a[x])
	  return ;
	ll h=a[x];
	for(int i=2;i*i<=h;i++){
		if(a[x]%i==0){
			ll sum=0;
			while(a[x]%i==0){
				a[x]/=i;
				sum++;
			}
			if(sum&1)
			  b[x]*=i;
		}
	}
	if(a[x]!=1)
	  b[x]*=a[x];
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=1;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	  solve(i);
	for(int i=1;i<=n;i++){
		ans+=sum;
		if(!a[i]){
			sum++;
			continue;
		}
		ans+=s[b[i]];
		s[b[i]]++;
	}
	write(ans);
	return 0;
}
```


---

## 作者：Mu_leaf (赞：1)

## [思路]

看到相乘为平方数，可以考虑质因数分解。

可以发现平方数的每种质因数的个数必定为偶数，所以考虑将一个数进行质因数分解，对于每一种质因数对 2 取模，现在只需要统计有哪些数的质因数种类与个数均相同就可以了。

考虑开一个桶，将剩下来的质因数重新相乘，得到的数一定不大于 $2 \times 10^5$ 直接存进桶里。

令 $f_x$ 为剩下质因数相乘结果为 $x$ 的个数，则 $f_x$ 对答案的贡献是 
$$\frac {(f_x-1) \times f_x}{2}$$

然后对 0 进行特判，第 $i$ 个 0 对答案的贡献是 $n-i$。

## [Code。](https://atcoder.jp/contests/abc342/submissions/50591138)

---

## 作者：rainbow_cat (赞：0)

### 思路：
首先，我们知道，若 $A_i=0$ 则它与任何数的积都是平方数。接下来，设 $d_i$ 为小于等于 $A_i$ 的最大平方数，若 $A_iA_j$ 是平方数，则 $\frac{A_i}{d_i}\frac{A_j}{d_j}$ 也是平方数，所以我们不难得到 $\frac{A_i}{d_i}=\frac{A_j}{d_j}$。我们开一个桶来记录 $\frac{A_i}{d_i}$ 即可。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,ans,cnt,a[200010],bin[200010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		int tmp;
		for(int j=1;j*j<=a[i];j++)if(a[i]%(j*j)==0)tmp=j*j;//求 d[i]
		if(a[i]==0)bin[0]++;
		else bin[a[i]/tmp]++,cnt++;
	}
	for(int i=1;i<=200000;i++)ans+=bin[i]*(bin[i]-1)/2;
	cout<<ans+(n-1)*bin[0]-bin[0]*(bin[0]-1)/2;
    /*
    这里的 (n-1)*bin[0]-bin[0]*(bin[0]-1)/2 是包含 0 的对数。
    (n-1)*bin[0] 是每一个 0 与其他数配对。
    bin[0]*(bin[0]-1)/2 是将重复的 0 与 0 的配对去掉。
    */
	return 0;
}
```

---

## 作者：_299817_ (赞：0)

## Part 1：思路
不难发现一个事实，就是如果我们对于每个数将它除以它因数中的最大的完全平方数，答案是不会变的。

做完这个操作后，我们发现每个数的质因数有且仅有一个。

而且完全平方数有一个性质，就是它所有的质因数都是成对出现的。

于是我们发现：只有相同的数能凑成一对。

于是这题就做完了，记得特判 $a_i = 0$ 的情况。

## Part 2：代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#include<list>
#define rep(i, l, r) for(int i = signed(l); i <= signed(r); i++)
#define per(i, l, r) for(int i = signed(l); i >= signed(r); i--)
#define sort stable_sort
#define int long long
using namespace std;
typedef long long ll;

const int MAXN = 200010;

int n;
int a[MAXN];
map <int, int> mp; // 用来记录每个数的出现次数

signed main(){
    #ifdef QwQ_ATM
        freopen("input.in", "r", stdin);
        freopen("output.out", "w", stdout);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    int ans = 0;
    rep(i, 1, n){
        cin >> a[i];
        int _sqrt = sqrt(a[i]);
        int now = 1;
        rep(j, 1, _sqrt){ // 做上述的操作
            if(a[i] % j == 0){
                int sqrt1 = sqrt(j);
                if(sqrt1 * sqrt1 == j) now = max(now, j);
                sqrt1 = sqrt(a[i] / j);
                if(sqrt1 * sqrt1 == a[i] / j) now = max(now, a[i] / j);
            }
        }
        a[i] /= now;
    }
    int cnt = 0; // 记录当前 0 的个数
    rep(i, 1, n){
        if(a[i] == 0){
            ans += (n - 1 - cnt);
            cnt++;
            continue;
        }
        ans += mp[a[i]];
        mp[a[i]]++;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：Milthm (赞：0)



容易发现质因数分解之后，如果两个数对于所有质因子的指数之和都是偶数，那么一定两个数乘起来是平方数。

而我们又知道，两个整数相加是偶数，要么都是奇数，要么都是偶数。所以我们质因数分解的时候把所有指数都对 $2$ 取模，得到一个新数。这样的话两个数乘起来是平方数，当且仅当它们得到的新数是相同的。于是我们用 `map` 记录，就做完了……吗？

你发现 $0$ 是不满足这个的，所以你要特判 $0$。具体地说，在 `map` 记录的时候忽略 $0$，假如有 $k$ 个 $0$，那么最后的答案就是你统计出来的加上 $(n-1)k-\frac{n(n-1)}2$，后面那个减去的式子是因为两个 $0$ 会被算 $2$ 次。

赛时代码太丑不放了。

---

## 作者：HappyJaPhy (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc342_d)

[原题传送门](https://atcoder.jp/contests/abc342/tasks/abc342_d)

# 题意

给出一个数列 $A$，求出满足 $A_iA_j$ 为完全平方数的无序数对 $(i,j)$ 的个数。

# 分析

容易想到（但是我在昨晚没想到，可以原地 AFO 了），对于每个数，如果是 $0$ 的话可以直接统计答案（记录 $0$ 的个数 $cnt$，最后 $ans\leftarrow ans+cnt(n-cnt)+\frac{cnt(cnt-1)}2$ 即可）。如果不是 $0$ 的话就把 $A_i$ 中最大的平方数因子除掉，留下没法开方的那一部分。如果剩下的和其他数相同，那么相乘肯定也是平方数。

证明一下这个很显然的结论：令 $A=a\sqrt{r},B=b\sqrt{r}$，且其为最简形式，那么 $A\times B$ 一定是个平方数。

具体怎么统计看代码。时间复杂度 $O(n\sqrt{A_{max}})$。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int n, ans, x, k, cnt, num[N];

inline int read(int &x) {
	char ch = x = 0;
	int m = 1;
	while (ch < '0' || ch > '9') {
		ch = getchar();
		if (ch == '-') m *= -1;
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar();
	}
	x *= m;
	return x;
}

signed main() {
	read(n);
	for (int i = 1; i <= n; i++) {
		read(x);
		if (x == 0) {
			cnt++;
			continue;
		}
		for (int j = sqrt(x) + 1; j; j--) {
			if (x % (j * j) == 0) { //把最大的平方数因子找出来
				k = j;
				break;
			}
		}
		x /= k * k; //然后除掉，留下开不尽的
		ans += num[x]; //如果有可以结合的，计入答案
		num[x]++; //更新 num
	}
	ans += cnt * (n - cnt) + cnt * (cnt - 1) / 2; //把 0 也要计入答案
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：Lotus_Land (赞：0)

## 题意

给出 $n$ 个数 $a_1,a_2,\dots a_n$，求有多少对 $(i,j)$ 满足以下条件：

- $1\leq i<j\leq n$；
- $a_ia_j$ 为完全平方数（0 也是完全平方数）。

## 分析

我的解法与官方题解基本相同。

先将 $a_i$ 从小到大排序。考虑对于每个 $a_i$，统计他对答案的贡献。

如果 $a_i=0$，那么他和后面的所有数都能组成符合要求的数对，答案加上 $n-i$。

如果 $a_i\not=0$，考虑 $a_i$ 要和哪些数相乘才会形成完全平方数。完全平方数有一个性质：所有质因数的次数均为偶数。

设 $a_i=\prod\limits_{k=1}^{q}p_k^{c_k}$，那么要找到一个小于等于 $a_i$ 的 $a_j=\prod\limits_{k=1}^{q}p_k^{d_k}$（其中 $p_k$ 均为质数，$c_k,d_k$ 为自然数），使得 $c_1+d_1,c_2+d_2,\dots,c_q+d_q$ 均为偶数。则 $c_i$ 与它对应的 $d_i$ 奇偶性相同。

那么就先把 $a_i,a_j$ 分别除以 $\prod\limits_{k=1}^{q}p_k^{2\left\lfloor\frac{c_k}{2}\right\rfloor}$ 和 $\prod\limits_{k=1}^{q}p_k^{2\left\lfloor\frac{d_k}{2}\right\rfloor}$，显然得到的数中所有质因子的指数都为 1。如果得到的这两个数相等，则 $a_ia_j$ 的所有质因数的指数都为偶数。

具体到代码实现上，预处理出 $1$ 到 $2\times 10^5$ 的完全平方数，对于每个 $a_i$ 把它能被整除的完全平方数都除掉，统计前面有多少数经过处理之后和 $a_i$ 剩下的数相等。

时间复杂度 $O(n\sqrt{A_i})$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define int long long
using namespace std;
inline LL read() {
	char ch=getchar();
	LL x=0;
	bool t=0;
	while(ch<'0'||ch>'9')   t|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return t?-x:x;
}
LL n,ans,ans2,a[200005];
int cnt;
int vis[200005];
int lst[200005];
main() {
	cin>>n;
	for(int i=1; i*i<=200000; i++) {
		lst[++cnt]=i*i;
	}
	for(int i=1; i<=n; i++) {
		a[i]=read();
	}
	sort(a+1,a+1+n);
	for(int i=1; i<=n; i++) {
		int tmp=a[i];
		if(a[i]==0){
			ans+=n-i;
		} else {
			for(int j=2; j<=cnt&&lst[j]<=a[i]; j++) {
				while(tmp%lst[j]==0){
					tmp/=lst[j];
				}
			}
			ans+=vis[tmp];
		}
		vis[tmp]++;
	}
	cout<<ans;
	return 0;
}
```

---

