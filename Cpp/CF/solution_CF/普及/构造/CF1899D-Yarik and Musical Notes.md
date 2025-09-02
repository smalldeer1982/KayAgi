# Yarik and Musical Notes

## 题目描述

Yarik is a big fan of many kinds of music. But Yarik loves not only listening to music but also writing it. He likes electronic music most of all, so he has created his own system of music notes, which, in his opinion, is best for it.

Since Yarik also likes informatics, in his system notes are denoted by integers of $ 2^k $ , where $ k \ge 1 $ — a positive integer. But, as you know, you can't use just notes to write music, so Yarik uses combinations of two notes. The combination of two notes $ (a, b) $ , where $ a = 2^k $ and $ b = 2^l $ , he denotes by the integer $ a^b $ .

For example, if $ a = 8 = 2^3 $ , $ b = 4 = 2^2 $ , then the combination $ (a, b) $ is denoted by the integer $ a^b = 8^4 = 4096 $ . Note that different combinations can have the same notation, e.g., the combination $ (64, 2) $ is also denoted by the integer $ 4096 = 64^2 $ .

Yarik has already chosen $ n $ notes that he wants to use in his new melody. However, since their integers can be very large, he has written them down as an array $ a $ of length $ n $ , then the note $ i $ is $ b_i = 2^{a_i} $ . The integers in array $ a $ can be repeated.

The melody will consist of several combinations of two notes. Yarik was wondering how many pairs of notes $ b_i, b_j $ $ (i < j) $ exist such that the combination $ (b_i, b_j) $ is equal to the combination $ (b_j, b_i) $ . In other words, he wants to count the number of pairs $ (i, j) $ $ (i < j) $ such that $ b_i^{b_j} = b_j^{b_i} $ . Help him find the number of such pairs.

## 样例 #1

### 输入

```
5
1
2
4
3 1 3 2
2
1000 1000
3
1 1 1
19
2 4 1 6 2 8 5 4 2 10 5 10 8 7 4 3 2 6 10```

### 输出

```
0
2
1
3
19```

# 题解

## 作者：DerrickLo (赞：8)

我们考虑什么时候 $b_i^{b_j}=b_j^{b_i}$。

若成立，则 $2^{a_i\times2^{a_j}}=2^{a_j\times 2^{a_i}}$，可以得到 $a_i\times2^{a_j}=a_j\times2^{a_i}$。

所以 $\displaystyle{\frac{2^{a_i}}{a_i}=\frac{2^{a_j}}{a_j}}$，然后我们去画一个 $f(x)=\displaystyle{\frac{2^x}{x}}$ 的图像，发现当 $x>0$ 且 $x$ 为整数时只有 $x=1$ 与 $x=2$ 时相等，其余都不会相等，那么就很好求答案了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[200005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);
		a[n+1]=0;
		int cnt1=0,cnt2=0,ans=0,cnt=0;
		for(int i=1;i<=n;i++)if(a[i]==1)cnt1++;
		for(int i=1;i<=n;i++)if(a[i]==2)cnt2++;
		ans+=cnt1*cnt2;
		for(int i=1;i<=n+1;i++){
			if(a[i]!=a[i-1])ans+=cnt*(cnt-1)/2ll,cnt=0;
			cnt++;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：lailai0916 (赞：2)

## 原题链接

- [洛谷 CF1899D Yarik and Musical Notes](https://www.luogu.com.cn/problem/CF1899D)

## 题意简述

求数列中有多少对 $(i,j)$，设 $x=a_i,y=a_j$，满足 $(2^x)^{(2^y)}=(2^y)^{(2^x)}$。（$i<j$）

## 解题思路

用 [Desmos](https://www.desmos.com/) 作出 $(2^x)^{(2^y)}=(2^y)^{(2^x)}$ 的图像：

![](https://cdn.luogu.com.cn/upload/image_hosting/6ltg0cpi.png)

不难发现只有 $x=y$ 或 $x=1,y=2$ 时等式成立。（$x\le y$）

统计每个 $i$ 出现次数，记为 $m_i$，然后对 $(x,y)$ 分类讨论：

- $x=1,y=2$，选一个 $1$ 和一个 $2$，方案数为 $m_1\times m_2$；
- $x=y=i$，在所有的 $i$ 中选两个，方案数为 $C_{m_i}^2=\frac{m_i(m_i-1)}{2}$。

所以总方案数为 $m_1\times m_2+\sum\frac{m_i(m_i-1)}{2}$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		map<int,ll> m;
		for(int i=1;i<=n;i++)
		{
			int t;
			cin>>t;
			m[t]++;
		}
		ll ans=m[1]*m[2];
		for(auto x:m)
		{
			ans+=x.second*(x.second-1)/2;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：ax_by_c (赞：2)

一个另类做法。

原始的式子为 ${2^{ai}}^{2^{a_j}}={2^{a_j}}^{2^{a_i}}$。

显然可以转化为 $2^{a_i\times{2^{a_j}}}=2^{a_j\times{2^{a_i}}}$。

显然可以转化为 $\log_2^{2^{a_i\times{2^{a_j}}}}=\log_2^{2^{a_j\times{2^{a_i}}}}$

显然可以转化为 $a_i\times{2^{a_j}}=a_j\times{2^{a_i}}$。

显然可以转化为 $\log_2^{a_i\times{2^{a_j}}}=\log_2^{a_j\times{2^{a_i}}}$。

显然可以转化为 $\log_2^{a_i}+\log_2^{2^{a_j}}=\log_2^{a_j}+\log_2^{2^{a_i}}$。

显然可以转化为 $\log_2^{a_i}+a_j=\log_2^{a_j}+a_i$。

显然可以转化为 $a_i-\log_2^{a_i}=a_j-\log_2^{a_j}$。

所以处理出 $a_i-\log_2^{a_i}$ 后找相同对即可。

---

## 作者：WaterSun (赞：1)

# 思路

暴力化简公式题。

假定 $b_{i}^{b_j} = b_{j}^{b_{i}}$ 成立，那么有：

$$
2^{a_i \times 2^{a_j}} = 2^{a_j \times 2^{a_i}}\\
a_i \times 2^{a_j} = a_j \times 2^{a_i}\\
\frac{a_i}{a_j} = \frac{2^{a_i}}{2^{a_j}}\\
\frac{a_i}{a_j} = 2^{a_i - a_j}
$$

因为 $\frac{a_i}{a_j} = 2^{a_i - a_j}$ 成立，所以 $a_i,a_j$ 除了 $2$ 以外的所有质因子数量相同，不妨令 $t_i$ 表示 $a_i$ 中 $2$ 这个质因子出现的次数。那么有：

$$
2^{t_i - t_j} = 2^{a_i - a_j}\\
t_i - t_j = a_i - a_j\\
a_i - t_i = a_j - t_j
$$

所以直接用 `map` 维护一下所有 $a_i - t_i$ 的值，然后根据加法原理全部加起来即可。

注意在代码实现的时候，要在 `map` 中加上一维，表示 $\frac{a_i}{2^{t_i}}$，因为在证明中假定了条件成立，但是在实现中，需要加上 $a_i$ 与 $a_j$ 除 $2$ 外的质因子数量不同的情况。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register
#define int long long

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10;
int T,n;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    int ans = 0;
    map<pii,int> vis;
    n = read();
    for (re int i = 1;i <= n;i++){
        int x,t,num = 0;
        x = t = read();
        while (t % 2 == 0){
            num++;
            t >>= 1;
        }
        vis[{t,x - num}]++;
    }
    for (auto it = vis.begin();it != vis.end();it++){
        int cnt = it -> second;
        ans += cnt * (cnt -  1) / 2;
    }
    printf("%lld\n",ans);
}

signed main(){
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

赛时直接放弃，赛后一看官方题解就懂了。  

如果 $a_i=a_j$ 那么肯定满足。

否则，我们来推一下等式：

$$(2^{a_i})^{(2^{a_j})}=(2^{a_j})^{(2^{a_i})} $$
$$(2^{a_i\times (2^{a_j})})=(2^{a_j\times (2^{a_i})})$$
$$a_i\times (2^{a_j})=a_j\times(2^{a_i})$$
$$\frac{a_i}{a_j}=\frac{(2^{a_i})}{(2^{a_j})}$$

我们利用小学数学知识即可知道（观察右边）：$a_i$ 是 $a_j$ 的 $2$ 的整数次冥倍（假设 $a_i\ge a_j$）。

所以假设 $a_j=a_i\times(2^x)$：

$$\frac{a_i}{a_i\times(2^{x})}=\frac{(2^{a
_i})}{(2^{a_i\times2^x})}$$
$$\frac{1}{(2^x)}=\frac{1}{(2^{a_i\times((2^x)-1)})}$$
$$2^x=2^{((2^x)-1)\times a_i}$$
$$x=((2^x)-1)\times a_i$$

显然 $x=1$ 是等式才有解，此时 $a_i=1{,a_j=2}$。否则 $((2^x)-1)>x$，无解。

所以只有 $a_i=a_j$ 或 $a_i=1{,}a_j=2$（也可以反着）时才有解。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int T;
int n,a,ans;
map<int,int> mp;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		mp.clear();
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a;
			ans+=mp[a];
			if(a==1) ans+=mp[2];
			if(a==2) ans+=mp[1];
			mp[a]++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：DFbd (赞：0)

## 思路

通过找规律发现，只有当 $1$ 和 $2$ 一组和两数相同的情况下，才符合条件。

所以开一个 ```map``` 记录每个数在数组中出现了多少次就好了。

## 代码
```'
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, a[200005], ans;
map<int, int> mp;
signed main() {
  cin >> t;
  while (t--) {
    cin >> n;
    ans = 0;
    mp.clear();
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      mp[a[i]]++;//统计次数
    }
    for (auto i : mp) {
      ans += i.second * (i.second - 1) / 2;//两数相同的对数
    }
    cout << ans + mp[2] * mp[1] << "\n";//最后加上1和2一组的对数
  }
  return 0;
}
```

---

