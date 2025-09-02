# Matrix

## 题目描述

You have a string of decimal digits $ s $ . Let's define $ b_{ij}=s_{i}·s_{j} $ . Find in matrix $ b $ the number of such rectangles that the sum $ b_{ij} $ for all cells $ (i,j) $ that are the elements of the rectangle equals $ a $ in each rectangle.

A rectangle in a matrix is a group of four integers $ (x,y,z,t) $  $ (x<=y,z<=t) $ . The elements of the rectangle are all cells $ (i,j) $ such that $ x<=i<=y,z<=j<=t $ .

## 样例 #1

### 输入

```
10
12345
```

### 输出

```
6
```

## 样例 #2

### 输入

```
16
439873893693495623498263984765
```

### 输出

```
40
```

# 题解

## 作者：shellyang2023 (赞：0)

要想 AK 这道题我们可以先处理出前缀和接着 $n^2$ 处理所有区间的和。

然后我们研究发现区间和不超过 $10 \times n$，所以我们开一个桶，记录和为 $i$ 的区间有多少个。

我们再 $O(\sqrt{a})$ 的枚举所有 $a$ 的因数，将答案加上 $T[i] \times T[a\div i]$。

注：**当** $a=0$ **时要特判**，时间复杂度为 $O(n^2+\sqrt{a})$。

见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20005;
string s;
long long a,T[N*10],qz[N],arr[N],ans,n;
int main () {
    freopen("confidence.in", "r", stdin);
    freopen("confidence.out", "w", stdout);
    cin>>a>>s;
    n=s.size();
    for(int i=1;i<=n;i++) {
    	arr[i]=s[i-1]-'0';
    	qz[i]=qz[i-1]+arr[i];
	}
	for(int i=1;i<=n;i++) {
		for(int j=0;j<i;j++) {
			T[qz[i]-qz[j]]++;
		}
	}
	for(int i=1;i*i<=a;i++) {
		if(a/i<N*10) {
			if(i*i==a) {
				ans+=1ll*T[i]*T[a/i];
			}else if(a%i==0) {
				ans+=2ll*T[i]*T[a/i];
			}
		}
	}
	if(a==0) {
		ans=1ll*T[0]*n*(n+1)-1ll*T[0]*T[0];
	}
	cout<<ans;
	return 0;
} 

```

---

## 作者：sherry_lover (赞：0)

# CF364A Matrix 题解

[Luogu题目传送门](https://www.luogu.com.cn/problem/CF364A)

[CF题目传送门](https://codeforces.com/contest/364/problem/A)

## 思路

首先，因为

$$\sum \limits_{i = 1}^{x} \sum \limits_{j = 1}^{y} s_i \times s_j = \sum \limits_{i = 1}^{x} s_i \times \sum \limits_{j = 1}^{y} s_j$$

可以得到每一个矩形的权值都和 $s$ 的两个区间和的乘积一一对应。

可以处理出所有区间的和，由于区间和不大于 $10n$，可以开个桶，记录和为 $i$ 的区间有多少个。枚举 $a$ 的因数，将答案贡献上 $s_i \times s_\frac{a}{i}$ 。注意 $a=0$ 时需要特判。时间复杂度 $O(n^2+\sqrt a)$，可过。

还可以继续进行优化，可以发现一个数 $a$ 的因数个数 $d(a)$ 一般远小于 $\sqrt a$。就可以直接枚举 $a$ 的因数，对每个因数 $i$ 可以 $O(n)$ 求区间和为 $i$ 的区间个数，时间复杂度 $O(\sqrt a+d(a)n)$，跑的很快。

[提交记录](https://codeforces.com/contest/364/submission/277059547)

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e4+5;
int a,len;
ll sum[N],t[N*10],ans;
char s[N];
ll ask(int k)
{
    ll tot = 0;
    ++t[0];
    for(int i = 1;i <= len;i++)
    {
        if(sum[i] >= k) tot += 1ll*t[sum[i]-k];
        ++t[sum[i]];
    }
    for(int i = 0;i <= len;i++) t[sum[i]] = 0;
    return tot;
}
int main()
{
    cin >> a;
    scanf("%s",s+1);
    len = strlen(s+1);
    for(int i = 1;i <= len;i++) sum[i] = sum[i-1] + s[i] - '0';
    for(int i = 1;i <= sqrt(a);i++)
    {
        if(a % i == 0 && a/i < N*10) ans += 2ll*ask(i)*ask(a/i);
        if(i*i == a && a/i < N*10) ans -= 1ll*ask(i)*ask(a/i);
    }
    if (!a) ans = 1ll * ask(0) * len * (len + 1) - 1ll * ask(0) * ask(0); 
    cout << ans;
    return 0;
}
```

### 鸣谢
感谢 @chaynflow 和林哲涵巨佬对本题解的大力支持（提供了做法）！

---

## 作者：TemplateClass (赞：0)

考虑如何求出区间和。

设区间为 $\left(x_1, y_1\right)$ 至 $\left(x_2, y_2\right)$，易知其和为

$$\begin{aligned} \sum \limits _ {x = x _ 1} ^ {x _ 2} \sum \limits _ {y = y _ 1} ^ {y _ 2} b _ {xy} &= \sum \limits _ {x = x _ 1} ^ {x _ 2} \sum \limits _ {y = y _ 1} ^ {y _ 2} s _ x \cdot s _ y \\ &= \sum \limits _ {x = x _ 1} ^ {x _ 2} \left( s _ x \sum \limits _ {y = y _ 1} ^ {y _ 2} s _ y \right) \\ &= \left( \sum \limits _ {x = x _ 1} ^ {x _ 2} s _ x \right) \left( \sum \limits _ {y = y _ 1} ^ {y _ 2} s _ y \right) \end{aligned}$$

这样，我们只需要预处理出 $s$ 的所有区间和，然后枚举一个区间，计算出是否有另一个区间和为 $a$ 除以当前区间和的区间即可。

注意特判 $a = 0$，答案记得开 `long long`。

```cpp
const int N = 1e4 + 5;
const int MOD1 = 998244353;
const int MOD2 = 1e9 + 7;

int a, sum[N]; std::string s;
std::map<int, int> sum_map;
long long ans = 0;

inline int query(int x, int y) {
	return sum[y] - sum[x - 1];
}

void solve(){
	std::cin >> a >> s;
	for(int i = 0; i < s.size(); ++i) {
		sum[i + 1] = sum[(i - 1) + 1] + (s[i] - '0');
	}
	
	for(int i = 1; i <= s.size(); ++i) {
		for(int j = i; j <= s.size(); ++j) {
			sum_map[sum[j] - sum[i - 1]] += 1;
		}
	}
	
	int cntsum = 0;
	for(const auto& [sum, cnt] : sum_map) {
		cntsum += cnt;
		if(sum == 0) continue;
		if(a % sum == 0 && sum_map.count(a / sum)) {
			ans += 1ll * cnt * sum_map[a / sum];
		}
	}
	
	if(a == 0) {
		ans += 1ll * cntsum * sum_map[0];
	}
	std::cout << ans;
}
```

---

## 作者：QWQ_123 (赞：0)

我们发现题目中 $b_{i,j} = s_i s_j$，那么一定是有什么性质。

考虑用 $s$ 表示一个子矩阵 $(x1,y1)(x2,y2)$ 的和，那么第一行是 $s_{x1}s_{y1}+s_{x1}s_{y1+1}+\dots$，那么实际上就是 $s_{x1}\sum_{j=y1}^{y2} s_{j}$；然后第二列是：$s_{x1+1} \sum_{j=y1}^{y2} s_j$，以此类推。

于是总和就是 $(\sum_{j=x1}^{x2} s_j)(\sum_{j=y1}^{y2}s_j)$，那么考虑将这个串的所有区间和存到桶中，然后查询即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, t;
string s;
map<ll, ll> ma;

int main() {
    scanf("%lld", &n); cin >> s;
    for (int i = 0; i < (int)s.size(); ++i) {
        ll ans = 0;
        for (int j = i; j < (int)s.size(); ++j) {
            ans = ans + (s[j] - '0');
            ma[ans]++;
        }
    }

    ll res = 0;

    for (auto [u, v] : ma) {
        // cout << u << ' ' << v << endl;
        t += v;
        if (!u) continue;
        if (n % u == 0 && ma.count(n / u))
            res += v * ma[n / u];
    }

    if (!n) res += t * ma[0];
    printf("%lld\n", res);

    return 0;
}
```

---

## 作者：Keroshi (赞：0)

# 题目分析    
题目需要求： $\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{k=i}^{n}\sum_{l=j}^{n}[\sum_{p=i}^{k}\sum_{q=j}^{l}s_p\cdot s_q=a]$ 。   
原式可以化为: $\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{k=i}^{n}\sum_{l=j}^{n}[\sum_{p=i}^{k}s_p \cdot \sum_{q=j}^{l} s_q=a]$ 。   
其中 $\sum_{p=i}^{k}s_p $ 与 $ \sum_{q=j}^{l}s_q$ 可以通过前缀和 $S$ 预处理。    
可以预处理所有的 $\sum_{i=1}^{n}\sum_{j=i}^{n} S_j-S_{i-1}$ ，并存在一个 unordered_map $M$ 中。   
这样最后的答案为：   
$$\sum_{i=1}^{n}\sum_{j=i}^{n}[S_j-S_{i-1} \ne 0][S_j-S_{i-1}\equiv 0~(mod~a)]M({\frac{a}{{S_j-S_{i-1}}}})$$   
时间复杂度: $O(n^2)$。    
注意：$a=0$ 时要特判， 答案会超出 long long ，要用 __int128。
# 代码   
```cpp
#include <bits/stdc++.h>
#define ll long long
#define lll __int128
using namespace std;
const ll N=4e3+5;
ll a,n;
string str;
ll s[N];
unordered_map <ll,ll> um;
lll ans;
int main(){
    cin >> a;
    cin >> str;
    n=str.size();
    for(ll i=1;i<=n;i++){
        s[i]=s[i-1]+str[i-1]-'0';
    }
    for(ll i=1;i<=n;i++){
        for(ll j=i;j<=n;j++){
            um[s[j]-s[i-1]]++;
        }
    }
    if(a==0){
        ans=um[0]*n*(n+1)-um[0]*um[0];
        cout << ans;
        return 0;
    }
    for(ll i=1;i<=n;i++){
        for(ll j=i;j<=n;j++){
            ll r=s[j]-s[i-1];
            if(r&&a%r==0){
                ans+=um[a/r];
            }
        }
    }
    cout << ans;
    return 0;
}
```

---

