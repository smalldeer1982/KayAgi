# Sofia and the Lost Operations

## 题目描述

Sofia had an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ . One day she got bored with it, so she decided to sequentially apply $ m $ modification operations to it.

Each modification operation is described by a pair of numbers $ \langle c_j, d_j \rangle $ and means that the element of the array with index $ c_j $ should be assigned the value $ d_j $ , i.e., perform the assignment $ a_{c_j} = d_j $ . After applying all modification operations sequentially, Sofia discarded the resulting array.

Recently, you found an array of $ n $ integers $ b_1, b_2, \ldots, b_n $ . You are interested in whether this array is Sofia's array. You know the values of the original array, as well as the values $ d_1, d_2, \ldots, d_m $ . The values $ c_1, c_2, \ldots, c_m $ turned out to be lost.

Is there a sequence $ c_1, c_2, \ldots, c_m $ such that the sequential application of modification operations $ \langle c_1, d_1, \rangle, \langle c_2, d_2, \rangle, \ldots, \langle c_m, d_m \rangle $ to the array $ a_1, a_2, \ldots, a_n $ transforms it into the array $ b_1, b_2, \ldots, b_n $ ?

## 样例 #1

### 输入

```
7
3
1 2 1
1 3 2
4
1 3 1 2
4
1 2 3 5
2 1 3 5
2
2 3
5
7 6 1 10 10
3 6 1 11 11
3
4 3 11
4
3 1 7 8
2 2 7 10
5
10 3 2 2 1
5
5 7 1 7 9
4 10 1 2 9
8
1 1 9 8 7 2 10 4
4
1000000000 203 203 203
203 1000000000 203 1000000000
2
203 1000000000
1
1
1
5
1 3 4 5 1```

### 输出

```
YES
NO
NO
NO
YES
NO
YES```

# 题解

## 作者：toolong114514 (赞：5)

# CF1980C Sofia and the Lost Operations 题解
## 题面大意
~~不是，现在怎么还没有上题面翻译啊？~~

Sofia 有两个长度为 $n(1\le n\le 10^5)$ 的数组 $a$ 和 $b$。

TA 需要对 $a$ 顺序进行以下 $m(1\le m\le10^5)$ 次操作，使 $a$ 变成 $b$：

每次操作可以用一个二元组 $(c_i,d_i)(1\le c_i\le n,1\le d_i\le 10^9)$ 表示，含义是将 $a_{c_i}\gets d_i$。

现在给出 $m$ 次操作的 $d_1,d_2,\cdots,d_m$，判断是否存在一个序列 $c_1,c_2,\cdots,c_m$，使 $a$ 变成 $b$。

如果存在，输出 ```YES```，否则输出 ```NO```。
## 解题思路
首先从 $1$ 到 $n$ 扫一遍，将所有满足 $a_i\neq b_i$ 的 $b_i$ 扔到一个桶里去计数，再把 $d_1,d_2,\cdots,d_m$ 扔到另一个桶里去计数。

如果需要修改成 $b_i$ 的位置数量超过了提供的与 $b_i$ 相等的 $d_j$，那么一定无解。

我们会发现，存在一些 $d_j$，没有任何一个需要修改的 $b_i$ 与它相等。

因为同一个位置的数可以被修改多次，所以**当且仅当**在这种 $d_j$ 后面存在把某个位置的 $a_i$ 改成目标的 $b_i$ 或者改回原样，才有解，否则无解。

按照上述过程编写代码即可。

注意，桶的类型需要使用 ```map```，或将 $a,b,d$ 的元素离散化后用数组存，千万不可使用 ```unordered_map```，不然会被卡 ```TLE```！
## 参考代码
```cpp
#include<algorithm>
#include<iostream>
#include<map>
#include<unordered_map>
using namespace std;
const int N=2e5+10;
int a[N],b[N],d[N],t[N];
int tt,n,m,cnt;
bool cmp(int pre,int nxt){
	return pre>nxt;
}
map<int,int> mp1,mp2,mp3;
int main(){
	//freopen("hack.in","r",stdin);
	ios::sync_with_stdio(false);
	cin>>tt;
	while(tt--){
		cin>>n;
		
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		cnt=0;
		mp3.clear();
		for(int i=1;i<=n;i++){
			cin>>b[i];
			if(a[i]!=b[i]) t[++cnt]=b[i];
			if(a[i]==b[i]) mp3[b[i]]++;
		}
		cin>>m;
		for(int i=1;i<=m;i++){
			cin>>d[i];
		}
		mp1.clear();mp2.clear();
		for(int i=1;i<=m;i++){
			mp2[d[i]]++;
		}
		bool flag=true,sb=false;
		for(int i=1;i<=cnt;i++){
			mp1[t[i]]++;
			if(mp1[t[i]]>mp2[t[i]]){
				cout<<"NO\n";
				flag=false;
				break;
			}
		}
		for(int i=m;i>0;i--){
			if(!flag) break;
			if(mp1[d[i]]||mp3[d[i]]) sb=true;
			if((!mp1[d[i]]&&!sb)){
				cout<<"NO\n";
				flag=false;
				break;
			}
		}
		if(flag) cout<<"YES\n";
	}
}
//逆天的155组测试数据
```
[本代码可以通过 CF 的评测。](https://www.luogu.com.cn/record/161331129)

Written by [toolong114514](www.luogu.com.cn/user/477821) on 2024/6/8.

---

## 作者：ArcNick (赞：2)

## 分析可能出现的情况
1. 你有的数缺少目标序列里的数（缺项），那么答案是 NO。
2. 某个目标序列里需要的数你有，但是数量不够，答案是 NO。
3. 你有的某个数，对于目标序列根本不需要，而且这个数还在 $d$ 数组的最后，那么它就没法被后续覆盖，答案是 NO。
4. 除了以上情况，答案就是 YES。
## Code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using ll = long long;
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 2e5 + 22;
int n, m;
int a[N], b[N], d[N];
void solve() {
    map<int, int> need, have, cnt;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (a[i] != b[i]) {
            need[b[i]]++; // 统计需要的数
        }
        cnt[b[i]]++; // 统计目标序列出现的数
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> d[i];
        have[d[i]]++; // 统计你可替换的数
    }

    // 处理缺项：目标序列里有你没有的数，直接NO
    for (auto x : need) {
        int val = x.first;
        if (have[val] < x.second) {
            cout << "NO\n";
            return;
        }
    }

    bool flag = 0;
    // flag的作用：判断是不是你有的数的序列的最后一个数
    
    for (int i = m; i >= 1; i--) if (have.count(d[i])) {
        // 如果最后一个数是你不需要的，这个数就无法被后续的数覆盖，就NO
        if (!need.count(d[i]) && !flag && cnt[d[i]] == 0) {
            cout << "NO\n";
            return;
        }
        flag = 1;

        //判断你有的某个数，够不够用
        if (have[d[i]] < need[d[i]]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}
int main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
    freopen("b.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _;
    cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
```
[评测记录](https://www.luogu.com.cn/record/165366891)

---

## 作者：MuQYun (赞：2)

#### 考虑以下几件事
1. 如果 $a$ 数组与 $b$ 数组相同：

- 我们只需要找到 $d$ 数组中最后一项元素是否是 $a$ 数组的一个数。

- 这样的话 $d$ 数组的其他元素可以全部依次叠加到 $a$ 数组的这个相匹配的数上，最后再用 $d$ 数组最后一个元素替换就可以了。

2. 如果 $a$ 数组与 $b$ 数组不同：

- 首先考虑 $d$ 数组最后一项元素是否在 $b$ 数组中出现，如果没有出现则输出 No。

- 然后考虑 $d$ 数组中的元素是否够换 $a$ 数组为 $b$ 数组，如果不够则输出 No。

**如果都满足条件则输出 Yes。**
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n;
    cin >> n;
    set<int> s1; // a中元素
    set<int> s2; // b中元素
    map<int, int> mp1; // a和b不一样的元素的个数
    map<int, int> mp2; // d中元素个数
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        s1.insert(a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        s2.insert(b[i]);
    }
    int m;
    cin >> m;
    vector<int> d(m + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> d[i];
        mp2[d[i]]++;
    }
    vector<int> dif;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] != b[i])
        {
            mp1[b[i]]++;
            dif.push_back(i);
        }
    }
    int last = d[m];
    if (!s2.count(last))
    {
        puts("NO");
        return;
    }
    if (dif.empty()) // 发现a和b数组一样, 只需要d最后一个元素是a中的一个元素就可以了
    {
        if (s1.count(d[m]))
        {
            puts("YES");
            return;
        }
        puts("NO");
        return;
    }
    else // a和b数组中有元素不一样
    {
        for (auto item : mp1)
        {
            int x = item.first;
            int y = item.second;
            if (!mp2.count(x)) // 不存在可替换
            {
                puts("NO");
                return;
            }
            else
            {
                if (mp2[x] < y) // 不够换的
                {
                    puts("NO");
                    return;
                }
            }
        }
        puts("YES");
    }
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：yshpdyt (赞：1)

## 题意
一个长度为 $n$ 初始序列 $a_i$，一个长度为 $n$ 目标序列 $b_i$，一个长度为 $m$ 的操作序列 $d_i$，问是否存在一个长为 $m$ 的下标操作序列 $c_i$，在依次进行 $a_{c_i}=d_i$  的赋值操作后，让 $\forall i\in[1,n]$，$a_i=b_i$。

## Sol 
~~感觉比 D，E 难想啊。~~


首先对于不匹配的位置，必须存在 $d_j=b_i$ 才能让该位置变成正确的值，这部分可以开个桶简单维护，即必须满足：

$$cnt_{d_j}\ge\sum\limits_{i=1}^n[a_i\neq b_i\land b_i=d_j]$$

如果任意位置不满足条件就是不可能。

然后考虑剩下的位置，注意到赋值操作只与最后的操作有关，也就是说，如果对于一个 $j$ 存在任意 $i$ 使得 $d_j=b_i$，那么前面没有匹配的的操作位置都可以先让 $b_i$ 更改，到 $j$ 时再改回 $b_i$。

这样直接写是很麻烦的，但是注意到如果最后一个元素，即 $d_m$，若 $\forall i\in[1,n],d_m\neq b_i$ 那么显然是无解的，因为最后一定会有一个位置不匹配，如果不成立，就变成了上述情况，一定有解，所以只需要简单判断最后一个位置即可，实现操作同样开桶。

注意要用 `map`。

##  Code
```cpp
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
ll n,a[N],b[N],m,c[N],d[N];
map<ll,ll>mp1;
map<ll,ll>mp2;
void sol(){
    mp1.clear();
    mp2.clear();
    cin>>n;
    ll res=0;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        cin>>b[i];
        if(a[i]!=b[i])mp1[b[i]]++,res++;
        mp2[b[i]]++;
    }
    cin>>m;
    for(int i=1;i<=m;i++)cin>>c[i];
    for(int i=1;i<=m;i++)if(mp1[c[i]]>0)mp1[c[i]]--,res--;
    if(res>0||mp2[c[m]]<=0)cout<<"NO\n";
    if(res>0||mp2[c[m]]<=0)return ;
    cout<<"YES\n";
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

## 作者：Kindershiuo (赞：0)

# 解题思路
这题其实还算简单，只要我们读懂了题目，这题的思路其实也就差不多出来了。
首先我们开个桶来装 $a$ 数组和 $b$ 数组不同的元素且记录个数(需要修改的值)，再开个桶记录下 $d$ 数组的每个元素且记录个数，再开个桶记录 $a$ 数组和 $b$ 数组相同的元素且记录个数(不需要修改的值)，然后我们就开始写关键部分：
1. 如果我们需要修改后的某个值超过了我们记录的 $d$ 中相同的那个值，那么一定无解，否则我们再进入下一步判断。
2. 大家一定会发现，我们所记录的 $d$ 数组，有些不是被修改后的值，那是因为一个数可以被修改很多遍，也就是可以把之前的修改给覆盖掉，所以我们就要判断，有没有一些这样的 $d_j$ 后面不存在被修改的值（修改成原值也要考虑）就一定无解。

当上述两个条件全部满足，才一定有解。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T;

void solve() {
	map<int,int>ma;
	map<int,int>md;
	map<int,int>mb;
	int n,m;
	cin>>n;
	int a[n+5];
	int b[n+5];
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		if(a[i]!=b[i]){
			mb[b[i]]++;
		}
	}
	for(int i=1;i<=n;i++){
		if(a[i]==b[i]){
			ma[a[i]]++;
		}
	}
	cin>>m;
	int d[m+5];
	for(int i=1;i<=m;i++){
		cin>>d[i];
		md[d[i]]++;
	}
	for(auto it=mb.begin();it!=mb.end();it++){
		if(it->second>md[it->first]){
			cout<<"NO"<<endl;
			return;
		}
	}
	int flag=0;
	for(int i=m;i>=1;i--){
		if(!mb[d[i]]&&!ma[d[i]]){
			if(flag==0){
				cout<<"NO"<<endl;
				return;
			}
		}
		else if(ma[d[i]]||mb[d[i]]){
			flag=1;
		}
	}
	cout<<"YES"<<endl;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Dtw_ (赞：0)

[cf](https://codeforces.com/problemset/problem/1980/C)
# 思路
首先考虑 $a$ 中和 $b$ 中有哪些字母不同，不同的有几个，然后用桶维护，在看一下可以用的数字都有哪些，如果这些可以用的够 $a$ 修改的，那在考虑其余的情况。

现在这个 $a$ 可以变成 $b$ 了，但还剩下一些其余的数字，而按照顺序放，所以放在前面的可以被放在后面的抵消掉，所以我把不应该放的先放上，然后再用应该放的覆盖他，然后大致就是这样。

梳理：

1. 首先判断我不看顺序，只看数字可不可以变过去，用桶维护即可。

2. 其次判断我最后面放的是不是合法的，因为只要合法的在 $d$ 的最后，那我前面不合法的都可以放到这个位置上，最后用合法的覆盖掉。

# Code

`mp` 存 $a$ 和 $b$ 有哪些是不同的，不同的有几个。

`Mp` 存 $d$ 中都有哪些数。

`v` 存这个字母起初是否合法。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n, m, a[N], b[N], x[N];

signed main()
{
	fst;
	int t;
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i=1; i<=n; i++)
		{
			cin >> a[i];
		}
		set<int> S;
		map<int, int> mp, Mp, v;
		int End = 0;
		for(int i=1; i<=n; i++)
		{
			cin >> b[i];
			if(a[i] != b[i]) mp[b[i]]++;
			else v[a[i]] = 1;
		}
		cin >> m;
		for(int i=1; i<=m; i++)
		{
			cin >> x[i];
			Mp[x[i]]++;
		}
		bool f = 1;
		for(int i=1; i<=n; i++)
		{
			if(Mp[b[i]] < mp[b[i]])
			{
				f = 0;
				break;
			}
		}
      // 数量上够，且最后一个放的是要放的，或者已经合法的
		if(f && (mp[x[m]] || v[x[m]])) puts("YES");
		else puts("NO");
	}
	return 0;
}


```

---

## 作者：Liyunze123 (赞：0)

其实，只要 $d_m$ 在 $b$ 中出现过，且对于所有的 $a_i \neq b_i$，$b_i$ 在 $d$ 中出现过，就输出 `YES`，否则输出 `NO`。

证明很简单：对于 $d_i$，假设有 $j\ge i$ 且 $d_j=b_k$，则把 $i$ 赋值给 $k$，成功消耗 $i$。但 $d_m$ 没在 $b$ 中出现过，就没有 $j$ 可消耗 $m$，显然不成立。而 $a_i=b_i$ 时，可以不对 $i$ 进行任何操作，因此不要考虑。

上代码：
```
#include<bits/stdc++.h>
#define buyao using
#define wan namespace
#define yuanshen std
buyao wan yuanshen; 
int t,n,m,a[200010],b[200010],c[200010];
map<int,int>k1[10010],k2[10010];
int main(){
    scanf("%d",&t);
    while(t--){
    	scanf("%d",&n);
    	for(int w=1;w<=n;w++)scanf("%d",&a[w]);
    	for(int w=1;w<=n;w++)scanf("%d",&b[w]),k1[t][b[w]]++;
    	scanf("%d",&m);
    	for(int w=1;w<=m;w++)scanf("%d",&c[w]),k2[t][c[w]]++;
    	if(k1[t][c[m]]){
    		int k=1;
    		for(int w=1;w<=n;w++)
				if(a[w]!=b[w])if(!k2[t][b[w]]--)k=0;
			if(k)printf("yes\n");
			else printf("no\n");
		}else printf("no\n");
	}
    return 0;
}
```

---

## 作者：haokee (赞：0)

首先，我们将相同的 $c_i$ 存到同一个 vector 里面，然后处理所有的更改。更改分为必选更改和可选更改（$a_i\ne b_i$ 为判定条件）。对于必选更改，我们要在 $b_i$ 对应的 vector 里面找到随便一个元素（一般是最后一个）并删除；对于可选更改，我们只需要找到那个元素就行了。

为什么要找到那个元素呢？因为假如那个元素是第 $j$ 个更改，所有的 $j$ 当中的最大值也就是可以应用到 $a$ 数组当中的最后一个更改。如果这就是 $m$ 个更改当中的最后一个，那么就有解，否则无解。时间复杂度 $\mathcal O((n+m)\log_2 m)$。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int kMaxN = 2e5 + 5;

int a[kMaxN], b[kMaxN], t, n, m, ch, ans;
map<int, vector<int>> f;
set<int> s;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t; t--) {
    cin >> n, ans = 0, ch = 1;
    s.clear(), f.clear();
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      cin >> b[i];
    }
    cin >> m;
    for (int i = 1, x; i <= m; i++) {
      cin >> x;
      f[x].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
      if (a[i] == b[i]) {
        if (f.count(b[i])) {
          ans = max(ans, f[b[i]].back());
        }
        continue;
      }
      if (f.count(b[i])) {
        ans = max(ans, f[b[i]].back());
        f[b[i]].pop_back();
        if (f[b[i]].empty()) {
          f.erase(b[i]);
        }
      } else {
        ch = 0;
      }
    }
    cout << (ans == m && ch ? "YES" : "NO") << '\n';
  }
  return 0;
}
```

---

