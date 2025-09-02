# Vlad and Division

## 题目描述

Vladislav has $ n $ non-negative integers, and he wants to divide all of them into several groups so that in any group, any pair of numbers does not have matching bit values among bits from $ 1 $ -st to $ 31 $ -st bit (i.e., considering the $ 31 $ least significant bits of the binary representation).

For an integer $ k $ , let $ k_2(i) $ denote the $ i $ -th bit in its binary representation (from right to left, indexing from 1). For example, if $ k=43 $ , since $ 43=101011_2 $ , then $ 43_2(1)=1 $ , $ 43_2(2)=1 $ , $ 43_2(3)=0 $ , $ 43_2(4)=1 $ , $ 43_2(5)=0 $ , $ 43_2(6)=1 $ , $ 43_2(7)=0 $ , $ 43_2(8)=0, \dots, 43_2(31)=0 $ .

Formally, for any two numbers $ x $ and $ y $ in the same group, the condition $ x_2(i) \neq y_2(i) $ must hold for all $ 1 \leq i < 32 $ .

What is the minimum number of groups Vlad needs to achieve his goal? Each number must fall into exactly one group.

## 说明/提示

In the first test case, any two numbers have the same last $ 31 $ bits, so we need to place each number in its own group.

In the second test case, $ a_1=0000000000000000000000000000000_2 $ , $ a_2=1111111111111111111111111111111_2 $ so they can be placed in the same group because $ a_1(i) \ne a_2(i) $ for each $ i $ between $ 1 $ and $ 31 $ , inclusive.

## 样例 #1

### 输入

```
9
4
1 4 3 4
2
0 2147483647
5
476319172 261956880 2136179468 1671164475 1885526767
3
1335890506 811593141 1128223362
4
688873446 627404104 1520079543 1458610201
4
61545621 2085938026 1269342732 1430258575
4
0 0 2147483647 2147483647
3
0 0 2147483647
8
1858058912 289424735 1858058912 2024818580 1858058912 289424735 122665067 289424735```

### 输出

```
4
1
3
2
2
3
2
2
4```

# 题解

## 作者：__Dist__ (赞：4)

$2$ 发罚时，疼。

用一个 `map` 记录前 $i - 1$ 个数中数字 $p$ 出现的次数。

这个表是个好东西，建议保存。

![](https://cdn.luogu.com.cn/upload/image_hosting/vz03m4xz.png)

遍历 $1\sim n$，求出与 ${a_i}_{(2)}$ 的前 $31$ 位相反的数 $p$。如果 $p$ 在前 $i - 1$ 个数中出现过且没有被 $a_1 \sim a_{i-1}$ 匹配过，那么就把 $p$ 出现的次数 $-1$，表示有一个 $p$ 与 $a_i$ 分在了一组；否则，增加答案数量，并把 $a_i$ 出现的次数 $+1$，相当于新开了一组。

### 代码

```cpp
#include <bits/stdc++.h>
#define gt getchar
#define pt putchar
#define ll long long

using namespace std;

const int MAXN = 1e5 + 5;

ll read() {
	ll x = 0, f = 1;char ch = gt();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1;ch = gt();}
	while (ch >= '0' && ch <= '9') {x *= 10;x += ch - '0';ch = gt();}
	return x * f;
}

ll fan(ll x) {
	ll res = 0;
	for (ll i = 1; i <= 31; i++) {
		if(x >> (i - 1) & 1) {
			res = res & ~(1 << (i - 1));
		}
		else {
			res = res | (1 << (i - 1));
		}
	}
	return res;
}

void solve() {
	ll res = 0;
	map<ll, ll> mp;
	ll n = read();
	for (ll i = 1; i <= n; i++) {
		ll a = read();
		ll p = fan(a);
		if(!mp[p]) {
			++res;
			mp[a]++;
		}
		else {
			mp[p]--;
		}
//		cout << mp[a] << ' ' << mp[p] << ' ';
//		cout << p << ' ' << res << '\n';
	}
	cout << res << '\n';
}

int main() {
	ll T = read();
	while(T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：lovely_hyzhuo (赞：3)

首先推导一个结论，只有两数异或值为 $2147483647$ 时，才能分到同组。

考虑 $1$ 和 $2$。

$1$ 在二进制下的数为 $00000000000000000000000000000001$。

$2$ 在二进制下的数为 $00000000000000000000000000000010$。

显然，前面那一坨 $0$ 都相同，所以 $1$ 和 $2$ 不能分到同组。

考虑对于一个数 $n$，想要和这个数在同组，必要所有位均不相同。

故结论成立。

所以开一个 map 记录一个数的出现次数。

每次对于一个非空的 map 的键的值，组数直接加上 $\min(mp_i,mp_{INF-i})$，其中 $mp$ 是开的 map，$INF$ 是 $2147483647$。然后答案再加上剩下的，单独分组。

总复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[2000010];
const int INF=2147483647;
void solve()
{
	map<int,int>mp;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],mp[a[i]]++;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(mp[a[i]]==0)
			continue;
		ans+=min(mp[a[i]],mp[INF-a[i]]);
		if(mp[a[i]]>mp[INF-a[i]])
			mp[a[i]]-=mp[INF-a[i]],mp[INF-a[i]]=0;
		else
			mp[INF-a[i]]-=mp[a[i]],mp[a[i]]=0;
		ans+=mp[a[i]];
		mp[a[i]]=0;
	}
	cout<<ans<<endl; 
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
```


---

## 作者：HashHacker_Peas (赞：1)

## 解题思路
不难得出一个结论，一个组内至多只有两个数 $a,b$，且 $b$ 由 $a$ 按位取反得到（不包括符号位）。于是我们可以用桶存储每个 $a_i$ 出现的次数，分组的时候答案个数加一，并将 $a_i$ 出现的次数减一，令 $h$ 为 $a_i$ 取反后的值，如果序列中存在 $h$，就将 $a_i$ 与 $h$ 合并在同一个组内即可。

## 代码实现
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
map<int,int>mp;
int t,n,a[maxn];
string tnbit(int n){//取反n
    string s="";
    while(n){
        int res=!(n&1);
        s.push_back(res+'0');
        n>>=1;
    }
    while(s.length()<31)
        s.push_back('1');//这里不写reverse，是想让下面的get函数更方便与省时间
    return s;
}
int get(string s){//获得n的值
    int res=0;
    for(int i=0;i<s.length();i++)
        if(s[i]=='1')
            res+=(1<<i);
    return res;
}
int main(){
    scanf("%d",&t);
    while(t--){
        mp.clear();//多测记得清空
        int res=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]),mp[a[i]]++;
        for(int i=1;i<=n;i++)
            while(mp[a[i]]){
                res++;
                mp[a[i]]--;
                if(mp[get(tnbit(a[i]))])//如果序列中存在取反后的a[i]
                    mp[get(tnbit(a[i]))]--;//那就合在一个组
            }
        printf("%d\n",res);
    }
    return 0;
}
```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1926D)

## 思路

题目要找到两两配对（两个 **int 类型的**数在转换为二进制以后的 $31$ 位里**都互不相同**）后的最少对数。看到互不相同可以立马想到异或运算。我们定义 $\inf$ 为 int 类型最大值。如果 $a\oplus\inf=b$，那么这两个数一定可以配对（按位两两异或后等于 $\inf$ 就符合要求，而异或运算具有传递性）。

我们读入每个数后在一个 multiset 中利用 ``find()`` 函数找是否有满足上述性质的数，如果有就将这个数从集合中弹出，并让计数器 $+1$；反之则把这个数加入集合。最后输出计数器的个数。

- 有多组测试数据，别忘清空变量、数组等。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,inf=0x7fffffff;
multiset<int>st;
inline void solve(){
    cin>>n;
    st.clear();
    int ans=0;
    for(int i=1;i<=n;++i){
        int x;
        cin>>x;
        auto p=st.find(x^inf);
        if(p==st.end()){
            st.insert(x);
            ++ans;
        }
        else st.erase(p);
    }
    cout<<ans;
    puts("");
    return ;
}
int main(){
    int T;
    cin>>T;
    while(T--)solve();
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/147913643)

---

## 作者：tder (赞：1)

给定序列 $\{a_n\}$，试将其分为若干组，使得每组内的数两两的二进制位各不相同。

---

要求两两的二进制位各不相同，即 $a_i~\text{and}~a_j=0$。但注意是第 $1\sim32$ 位各不相同，因此需要 $a_i+a_j=2^{32}-1$，那么显然每组只能 $2$ 个数。

因此，我们考虑用 $s_i$ 表示 $i$ 在序列中出现的次数。

对于每一个 $a_i$，若 $s_{(2^{32}-1)-a_i}>0$，即序列中存在 $(2^{32}-1)-a_i$，那么考虑将每个 $a_i$ 和每个 $(2^{32}-1)-a_i$ 组成一组，共 $\min(s_{a_i},s_{(2^{32}-1)-a_i})$ 组。

统计答案即可。

时间复杂度 $O(\sum n\log n)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5, M = 2147483647;
int t, n, a[N];
signed main() {
    cin>>t;
    while(t--) {
        cin>>n;
        int ans = n;
        map<int, int> s;
        for(int i = 1; i <= n; i++) {
            cin>>a[i];
            s[a[i]]++;
        }
        sort(a + 1, a + n + 1);
        int k = unique(a + 1, a + n + 1) - a - 1;
        for(int i = 1; i <= k && a[i] <= M / 2; i++) if(s[M - a[i]]) ans -= min(s[a[i]], s[M - a[i]]);
        cout<<ans<<endl;
    }
}
```

---

## 作者：Code_Select_You (赞：0)

## 思路
看大家好像都用 map 做的，我提供一个二分的思路。如果两个数二进制下的各位都不同，那么这两个数字的和便是 $2147483647$（$2^0+2^1+...+2^{30}=2^{31}-1$）。所以可以先把数组排序，然后遍历整个数组。对于每个数，如果有数能和它一组，就从数组中把他们两个删掉，否则把这个数删掉，最后更新答案。

## AC code
```cpp

#include<bits/stdc++.h>
using namespace std;
int T,n,a[200001],ans;
bool f[200001];
const int q=2147483647;
int main(){
	scanf("%d",&T);
	while(T--){
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
//			for(int i=1;i<=n;i++) printf("%d ",a[i]);
//			printf("\n");
		memset(f,true,sizeof(f));
		for(int i=1;i<=n;i++)
			if(f[i]){
				int l=0,r=n+1,k=q-a[i];
				while(l+1<r){
					int mid=(l+r)/2;
					if(a[mid]>k) r=mid;
					else l=mid;
				}
//					printf("%d:%d\n",i,l);
				if(!f[l]) while(l>1 && f[l-1] && a[l-1]==a[l]) l--;
				if(!f[l]) while(l<n && f[l+1] && a[l+1]==a[l]) l++;
//					printf("%d:%d\n",i,l);
				if(!f[l] || 1LL*(a[i]+a[l])!=q) ans++,f[i]=false;
				else ans++,f[i]=f[l]=false;
			}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：RyanLi (赞：0)

传送门：洛谷 [Vlad and Division](https://www.luogu.com.cn/problem/CF1926D) | Codeforces [D. Vlad and Divison](https://codeforces.com/contest/1926/problem/D)

更佳的阅读体验：[CF1926D 题解](https://blog.ryanli.top/index.php/archives/38/)

---

**简要题意**：两个二进制下第 $1$ 到 $31$ 位都不同的数可以组合成一组，一个单独的数也可以成为一组。有 $n$ 个数，求最少可以构成多少组。

二进制下，每一位只可能是 $0$ 或 $1$，所以对于一个数，在二进制下 $1$ 到 $31$ 位都不同的数是**唯一**的，并且这两个数的和是一定的，即 $2147483647$（$2^{31} - 1$）。

考虑使用 `map` 维护每个数出现的数量。读入时存下每个数的数量，然后遍历整个序列，如果发现当前数 $a_i$ 和 $2147483647 - a_i$ 都有出现，那么即可贪心地凑成一对。

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

const int N = 2e5 + 10, LIM = 2147483647;
int t, n, a[N], ans;
map<int, int> mp;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        ans = 0, mp.clear();
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i], ++mp[a[i]];
        for (int i = 1; i <= n; ++i) if (mp[a[i]]) {
            --mp[a[i]];
            if (mp[LIM - a[i]]) --mp[LIM - a[i]];
            ++ans;
        } cout << ans << '\n';
    } return 0;
}
```

---

**后记**

![Verdict: Hacked](https://img.ryanli.top/i/2/65d454e4c0a01.png)

没事别用 `unordered_map`，血的教训。

---

## 作者：minVan (赞：0)

**题目大意**

给定长度为 $n$ 的序列 $a$，问有多少对 $(a_i,a_j)$ 满足 $a_i,a_j$ 转换为二进制后每位都不相同。

**解题思路**

`int` 范围内，所以转换为有多少对 $a_i+a_j=2^{31}-1=(11\cdots1)_2$。考虑用 map 存储当前 $2^{31}-1-a_j$ 的个数，如果有，则其个数减一并且答案加一。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    map<int, int> mp;
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
      if(!mp[a[i]]) {
        ++mp[(1ll << 31) - 1 - a[i]];
        ++ans;
        // cout << a[i] << ' ' << (1ll << 31) - 1 - a[i] << ' ' << i << '\n';
      } else {
        --mp[a[i]];
      }
    }
    cout << ans << '\n';
  }
  return 0;
}

```

---

## 作者：Eason_cyx (赞：0)

首先，题目中说每一组中的数需要两两之间都满足二进制完全不相等，所以一组只能有 $2$ 个数。

考虑给定 $x$，如何构造出二进制与 $x$ 每一位都不相同的数。

其实，这个数就是 $x \operatorname{xor} 2147483647$。

那么我们只需对于每一个 $a_i$，寻找 $a_i \operatorname{xor} 2147483647$ 是否存在于数组中且未被配对过。如果有，那么标记两个数被配对过并令 $ans + 1$；否则，说明 $a_i$ 只能自己单独成一组，同样令 $ans+1$。

最后答案就是 $ans$，单组时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[200005],b[200005];
//b[i]表示a[i]在相同元素中是第几个
map<long long,int> mp,c;
//mp[i]表示i在整个数组中出现了几次
map<long long,int> mp2;
//mp2[i]表示为i的元素有几个已经配对完成
int main() {
    int t; scanf("%d",&t);
    while(t--) {
    	mp.clear();
    	c.clear();
    	mp2.clear();
        int n; scanf("%d",&n);
        for(int i = 1;i <= n;i++) {
        	scanf("%lld",&a[i]);
        	mp[a[i]]++;
        	b[i] = mp[a[i]];
        }
        int cnt = 1;
        for(int i = 1;i <= n;i++) {
        	if(b[i] <= mp2[a[i]]) {
        		// cout << i << " of course it not!!!\n";
        		continue;
        	}
        	if(i != 1) cnt++;
        	long long fan = a[i] ^ 2147483647ll;
        	int last = mp[fan] - mp2[fan];
        	if(!last) {
        		continue;
        		// cout << i << " I think it's not.\n'";
        	}
        	mp2[fan]++;
        	mp2[a[i]]++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
```

注意这题不卡时间但是卡 `unordered_map`。

橙到黄吧。

---

