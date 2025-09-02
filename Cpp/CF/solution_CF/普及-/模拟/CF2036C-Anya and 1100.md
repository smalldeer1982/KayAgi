# Anya and 1100

## 题目描述

While rummaging through things in a distant drawer, Anya found a beautiful string $ s $ consisting only of zeros and ones.

Now she wants to make it even more beautiful by performing $ q $ operations on it.

Each operation is described by two integers $ i $ ( $ 1 \le i \le |s| $ ) and $ v $ ( $ v \in \{0, 1\} $ ) and means that the $ i $ -th character of the string is assigned the value $ v $ (that is, the assignment $ s_i = v $ is performed).

But Anya loves the number $ 1100 $ , so after each query, she asks you to tell her whether the substring "1100" is present in her string (i.e. there exist such $ 1 \le i \le |s| - 3 $ that $ s_{i}s_{i + 1}s_{i + 2}s_{i + 3} = \texttt{1100} $ ).

## 样例 #1

### 输入

```
4
100
4
1 1
2 0
2 0
3 1
1100000
3
6 1
7 1
4 1
111010
4
1 1
5 0
4 1
5 0
0100
4
3 1
1 1
2 0
2 1```

### 输出

```
NO
NO
NO
NO
YES
YES
NO
NO
YES
YES
YES
NO
NO
NO
NO```

# 题解

## 作者：Scean_Tong (赞：2)

## CF2036C Anya and 1100 题解

### 题意

给你一个仅含有 $0$ 和 $1$ 的字符串，$q$ 次操作，每次修改一个字符，并询问有没有子串为 $1100$。

### 思路

定义 $f_i$ 表示从第 $i$ 位开始的长度为 $4$ 的子串是否是 $1100$，这个显然可以 $O(1)$ 求出，那么可以 $O(n)$ 先求出操作前的 $f_i$，对于每次操作，因为只修改一个字符，所以只需要先减去这次修改的位置能影响到的答案，然后修改这个位置的字符，最后再加上这次修改的位置能影响到的答案即可。

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T=1;
string s;
int q,ans;
bool check(int pos){
	return s[pos]=='1'&&s[pos+1]=='1'&&s[pos+2]=='0'&&s[pos+3]=='0';
}
void solve(){
	cin>>s>>q;
	ans=0;
	int n=s.size();
	s='#'+s;
	for(int i=1;i<=n-3;i++){
		if(check(i)){
			ans++;
		}
	}
	while(q--){
		int i,v;
		cin>>i>>v;
		for(int k=max(1ll,i-3);k<=min(n,i+4);k++){
			if(check(k)){
				ans--;
			}
		}
		s[i]=v^'0';
		for(int k=max(0ll,i-3);k<=min(n,i+4);k++){
			if(check(k)){
				ans++;
			}
		}
		if(ans){
			cout<<"Yes"<<'\n';
		}
		else cout<<"No"<<'\n';
	}
}
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：zhang_kevin (赞：2)

首先，我们可以求出原式状态下有多少个满足条件的字串。

接着，对于每次修改，直接暴力判断会超时，所以考虑优化。

发现如果修改了位置 $i$，则只有 $4$ 个长度为 $4$ 的子串收到影响。因此判断这 $4$ 个即可。

我们可以用一个 `set` 记录所有符合要求的子串的位置。然后，对于每次修改，只需要暴力判断 $4$ 个位置并修改 `set` 即可。每次询问只需要看 `set` 中是否存在元素。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> s;
inline void output(bool flag){
    if(flag){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
    return;
}
inline void Solve(){
    s.clear();
    string str;
    cin >> str;
    bool Last = false;
    for(int i = 0; i < str.length() - 3; i++){
        if(str[i] == '1' && str[i+1] == '1' && str[i+2] == '0' && str[i+3] == '0'){
            s.insert(i);
            Last = true;
        }
    }
    int q; cin >> q;
    while(q--){
        int pos, v;
        cin >> pos >> v;
        pos--;
        if(str[pos] == v + '0'){
            output(Last);
            continue;
        }else{
            str[pos] = v + '0';
            for(int i = max(0, pos-3); i <= pos; i++){
                if(str[i] == '1' && str[i+1] == '1' && str[i+2] == '0' && str[i+3] == '0'){
                    if(s.count(i) != 0){
                        Last = true;
                    }else{
                        s.insert(i);
                        Last = true;
                    }
                }else{
                    if(s.count(i) != 0){
                        s.erase(i);
                        if(s.empty()){
                            Last = false;
                        }else{
                            Last = true;
                        }
                    }
                }
            }
            output(Last);
        }
    }
    return;
}
int main(){
	int t;
    cin >> t;
    while(t--){
        Solve();
    }
    return 0;
}
```

---

## 作者：Sakura_Emilia (赞：1)

# Solution

本题采用动态更新的思路。注意到一个关键点，$1100$ 型子串不会有重叠的现象，也就是不会有某一个位，它既作为一个子串的一部分，同时也作为另一个子串的一部分。

因此可以动态维护整个 $01$ 串中 $1100$ 型子串的总数量，每次修改一个点的时候，就来动态的更新。改变其中某一个位上的 $01$，仅仅只会影响到前后一两个位置上的子串。因此分类讨论即可。

注意修改一个位置，总的子串数量可能减少，也可能增加。

# Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
using namespace std;

int T, n, a, b, len, cnt;
string s;

inline bool check(int i) {
    if(s[i] == '1' and s[i + 1] == '1' and s[i + 2] == '0' and s[i + 3] == '0')
        return true;
    else
        return false;
}

inline void solve() {
    cin >> s >> n;
    len = (int) s.length();
    cnt = 0;

    for(int i = 0; i <= len - 4; i++)
        if(check(i))
            cnt++;

    while(n--) {
        cin >> a >> b;
        if(s[a - 1] != b + '0') {
            // a号位原来是1，现在是0
            if(!b) {
                if(check(a - 1) or check(a - 2))
                    cnt--;
                s[a - 1] = b + '0';
                if(check(a - 3) or check(a - 4))
                    cnt++;
            } else {    // a号位原来是0，现在是1
                if(check(a - 3) or check(a - 4))
                    cnt--;
                s[a - 1] = b + '0';
                if(check(a - 1) or check(a - 2))
                    cnt++;
            }
        }
        cout << (cnt == 0 ? "NO" : "YES") << endl;
    }
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
```

---

## 作者：K_J_M (赞：1)

## 题目大意
有 $t$ 组测试数据，每一组测试数据有一个只包含 $0,1$ 的字符串 $s$，还有一个操作次数 $q$，每一次操作给定两个正整数 $i,v$，表示你可以将 $s_i$ 改为 $v$，注意，字符串下标从 $1$ 开始，在每一次操作之后请你输出这个字符串中还有没有 $1100$ 这样的字串。每一次操作均不独立，即会影响到后面的询问。
## Solution
显然直接模拟时间复杂度为 $\mathcal O(qn)$，第三个点会超时。分析一下发现每一次的修改操作只会对与它**相邻的几个**有影响，所以考虑对每一次操作维护答案的变化量，这里的答案指的是字符串中一共有多少个为 $1100$ 的字串，记为 $cnt$，最后只需要查看 $cnt>0$ 即可。现在问题就在于怎么在修改过程中维护 $cnt$。显然，对于每一次操作，只会对 $s_{i-3\dots i},s_{i-2\dots i+1},s_{i-1\dots i+2},s_{i,\dots i+3}$ 有影响，所以我们只需要看更改后**是否形成了新的 $1100$**，或者有没有把**原来的 $1100$ 给顶替掉了**。这样做的时间复杂度为 $\mathcal O(1)$，总共的时间复杂度为 $\mathcal O(q)$。\
[Ac Code](https://www.luogu.com.cn/paste/8za06ar2)

---

## 作者：xingshuyan000 (赞：0)

[题目传送门 1：洛谷 CF2036C](https://www.luogu.com.cn/problem/CF2036C)

[题目传送门 2：Codeforces 2036C](https://codeforces.com/problemset/problem/2036/C)

[欢迎到我的博客阅读本文](https://www.cnblogs.com/xingshuyan/articles/18526402)

# 题目大意

给你一个由只有 `0` 和 `1` 组成的字符串 $s$，进行 $q$ 次操作，具体操作方案如下：

对于每次操作，给出两个整数 $i$ 和 $v$，然后把 $s_i$ 的值赋成 $v$，也就是 $s_i \leftarrow v$，操作完成后，查询这个字符串的子串中是否存在 `1100`，如果有则输出 `YES`，否则输出 `NO`。

本题的每个测试点包括 $T$ 组测试数据。

数据范围：$1 \leq T \leq 10^4$，$1 \leq |s| \leq 2 \cdot 10^5$，$1 \leq q \leq 2 \cdot 10^5$，$1 \leq i \leq |s|$，$v \in \{0, 1\}$。同时保证 $\sum |s|,\sum q \le 2 \times 10^5$。

# 题目分析

这是一道字符串匹配问题。

首先，读完题后，我马上就想出来了一种暴力的思路：执行每次赋值操作，赋值后从字符串的头枚举到尾，检查是否存在子串 `1100`，如果有就输出 `YES`，没有就输出 `NO`。这样，单组数据的时间复杂度是 $O(q \cdot |s|)$，本题显然超时。

考虑优化。

其实稍微思考一下，可以发现，我们可以先寻找一下最初的字符串中是否存在子串 `1100`，如果有的话，每找到一个，用变量 $cnt$ 存一下个数。然后，对于每次的赋值操作，其实只会改变这个被更改的字符的周围的子串。所以，我们可以直接先查找在区间 $[\max(i - 3,1),\min(i + 3,n)]$（这里的 $n$ 表示字符串 $s$ 的长度）上的 `1100` 的个数，如果不为 $0$，我这里就用 $p1=1$ 来表示，否则就让 $p1=0$；接着进行赋值操作，让 $s_i \leftarrow v$，然后查询在区间 $[\max(i - 3,1),\min(i + 3,n)]$ 上 `1100` 的个数，如果不等于 $0$，我这里就用 $p2 = 1$ 来表示，否则 $p2=0$。接着更新 $cnt$ 的值，让 $cnt \leftarrow cnt + (p2 - p1)$。如果在每次操作后，$cnt > 0$，则输出 `YES`，否则输出 `NO`。

这样子下来，单组数据的时间复杂度是 $O(n + q)$，在本题的数据范围限制下，可以通过。

# Code

这样分析完以后，代码就很好写了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
void solve()
{
	string s;
	cin >> s;
	int cnt = 0, n = s.length();
	for(int i = 0; i < n; i ++)
	{
		if(s.substr(i, 4) == "1100") cnt ++;
	}
	int q;
	cin >> q;
	while(q--)
	{
		int i;
		char v;
		cin >> i >> v;
		i --; //注意字符串的下标是从 0 开始的，而 i 是从 1 开始的，所以这里 i--
		int p1 = 0, p2 = 0;
		if(s[i] != v) //如果更新的值与原来相同，可以直接跳过
		{
			for(int j = max(i - 3, 0); j <= min(i, n - 3); j ++)
			{
				if(s.substr(j, 4) == "1100") p1 = 1;
			}
			s[i] = v;
			for(int j = max(i - 3, 0); j <= min(i, n - 3); j ++)
			{
				if(s.substr(j, 4) == "1100") p2 = 1;
			}
			cnt += p2 - p1;
		}
		if(cnt) cout << "YES" << endl; //如果 cnt > 0，输出 YES
		else cout << "NO" << endl; // 否则输出 NO
	}
	return;
}
int main()
{
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}
```

完结撒花~

---

## 作者：Starlit_Night (赞：0)

### 思路  
赋值操作之前，先预处理，用一个 `set` 保存每一个 `1100` 合法子串的位置。在进行赋值操作时，再来判断是否有对原先存在合法子串造成影响。如果有，将原先存在的合法子串位置删去，并且在赋值位置前 $3$ 位到后 $3$ 位的位置寻找有没有产生新的合法子串，有则加入到 `set` 中。最后，可以根据 `set` 中还有没有元素来判断字符串中还有没有合法的子串`1100`。
### 代码  
```cpp
#include <bits/stdc++.h>  
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        set<int> ok;
        string s;
        cin >> s;
        for(int i=0;i<s.size();++i){
            if(s[i]=='1'&&s[i+1]=='1'&&s[i+2]=='0'&&s[i+3]=='0') ok.insert(i);
        }
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            bool flag=true; int pos; char x;
            cin >> pos >> x;
            char tmp = s[pos - 1];
            s[pos - 1] = x;
            if(tmp==x){
                if(ok.empty()) cout<<"NO\n";//没有改变，且本来没有合法位置，那么肯定是no
                else cout<<"YES\n";
            }else{
                int j;
                if(tmp=='0'){
                    j=pos-2;
                    if(s[j]=='0') j-=2;
                    else j--;
                }else{
                    j=pos-1;
                    if(s[j+1]=='0') j--;
                }//找到开头
                if(j>=0&&ok.find(j)!=ok.end()) ok.erase(ok.find(j));//删掉旧的
                for(int k=max(0,pos-4);k<=pos+2;++k){
                    if(s[k]=='1'&&s[k+1]=='1'&&s[k+2]=='0'&&s[k+3]=='0') ok.insert(k);
                }
                if(ok.empty()) cout<<"NO\n";
                else cout<<"YES\n";
            }
        }
    }
    return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2036C)

一道维护题。

发现修改位置为 $pos$ 的字符只可能对 $[pos - 3,pos+3]$ 中的 $\texttt{1100}$ 的数量。

记录一个 $vis_i$ 表示第 $s_is_{i+1}s_{i+2}s_{i+3}$ 是否为 $\texttt{1100}$，再维护一个 $cnt$ 表示 $vis$ 中值为 $1$ 的个数。设某次修改的位置为 $pos$，将原字符串修改后对与 $i \in [pos-3, pos]$ 范围的 $vis_i$ 进行更新，最后查看 $cnt$ 是否为 $0$ 即可。


## Code
```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

const long long MOD1 = 998244353;
const long long MOD2 = 1000000007;
const long long MOD3 = 1000000009;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	#define SZ(x) (x.size())
	#define fst first
	#define snd second
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
const int N = 200005;
int T, n, q, cnt;
int a[N];
bool vis[N];
bool check(int pos) { return (a[pos] and a[pos + 1] and !a[pos + 2] and !a[pos + 3]); }
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> T;
	while (T--) {
		string s;
		cnt = 0;
		cin >> s >> q;
		n = s.size();
		for (int i = 0; i < n; i++) a[i + 1] = s[i] - '0';
		for (int i = 1; i <= n; i++) vis[i] = 0;
		for (int i = 1; i <= n - 3; i++) {
			if (check(i)) vis[i] = 1, cnt++;
		}
		while (q--) {
			int pos;
			char c;
			cin >> pos >> c;
			a[pos] = c - '0';
			for (int i = Max(1, pos - 3); i <= Min(pos, n - 3); i++) {
				cnt -= vis[i];
				vis[i] = check(i);
				cnt += vis[i];
			}
			cout << (cnt ? "Yes\n" : "No\n");
		}
	}
	return 0;
}
```

---

