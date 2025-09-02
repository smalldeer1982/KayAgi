# [ABC346F] SSttrriinngg in StringString

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc346/tasks/abc346_f

長さ $ n $ の文字列 $ X $ に対して、$ X $ を $ k $ 回繰り返して得られる文字列を $ f(X,k) $ と表記し、$ X $ の $ 1 $ 文字目、$ 2 $ 文字目、$ \dots $、$ n $ 文字目を $ k $ 回ずつこの順に繰り返して得られる文字列を $ g(X,k) $ と表記します。 例えば、$ X= $ `abc` のとき、$ f(X,2)= $ `abcabc`、$ g(X,3)= $ `aaabbbccc` です。 また、任意の文字列 $ X $ に対して、$ f(X,0) $ と $ g(X,0) $ は共に空文字列です。

正整数 $ N $ および文字列 $ S,T $ が与えられます。 $ g(T,k) $ が $ f(S,N) $ の（連続とは限らない）部分列であるような最大の非負整数 $ k $ を求めてください。 なお、定義より、$ g(T,0) $ は常に $ f(S,N) $ の部分列であることに注意してください。

部分列とは文字列 $ X $ の（連続とは限らない）部分列とは、$ X $ から $ 0 $ 個以上の文字を取り除いた後、残りの文字を元の順序で連結して得られる文字列のことをいいます。 例えば、`ac`、`atcoder`、` `（空文字列）などはどれも `atcoder` の部分列ですが、`ta` は `atcoder` の部分列ではありません。

## 说明/提示

### 制約

- $ N $ は整数
- $ 1\leq\ N\leq\ 10^{12} $
- $ S,\ T $ は英小文字からなる長さ $ 1 $ 以上 $ 10^5 $ 以下の文字列

### Sample Explanation 1

$ f(S,3)= $ `abcabcabc` です。 $ g(T,2)= $ `aabb` は $ f(S,3) $ の部分列ですが、$ g(T,3)= $ `aaabbb` は $ f(S,3) $ の部分列ではないので、$ 2 $ を出力します。

## 样例 #1

### 输入

```
3
abc
ab```

### 输出

```
2```

## 样例 #2

### 输入

```
3
abc
arc```

### 输出

```
0```

## 样例 #3

### 输入

```
1000000000000
kzazkakxkk
azakxk```

### 输出

```
344827586207```

# 题解

## 作者：2huk (赞：10)

对于一个字符串 $X$ 和一个非负整数 $k$，定义 $f(X, k)$ 表示将 $X$ 重复 $k$ 次得到的字符串，$g(X, k)$ 表示将 $X$ 的每个字符重复 $k$ 次得到的字符串。例如当 $X = \texttt{abc}$ 时，$f(X, 2) = \texttt{abcabc}, g(X, 3) = \texttt{aaabbbccc}$。特别的，当 $k = 0$ 时，$f(X, k), g(X, k)$ 为空串。

给定两个字符串 $S, T$ 和一个正整数 $n$。求最大的非负整数 $k$ 满足 $g(T, k)$ 是 $f(S, n)$ 的子序列。

$1 \le n \le 10^{12}$，$1 \le |S|, |T| \le 10^5$。

---

子序列是具有传递性的。对于字符串 $s_1, s_2, s_3$ 而言，如果 $s_1$ 是 $s_2$ 的子序列，$s_2$ 是 $s_3$ 的子序列，那么 $s_1$ 是 $s_3$ 的子序列。

容易发现 $g(T, k)$ 一定是 $g(T, k + 1)$ 的子序列。归纳可以证明，如果答案为 $k$，那么所有 $1 \le i \le k$ 都满足 $g(T, i)$ 是 $f(S, n)$ 的子序列。这启发我们可以二分答案。

问题就转化成了，已知 $S, T, k, n$，判断 $g(T, k)$ 是否是 $f(S, n)$ 的子序列。而对于这个问题，我们又可以计算最小的 $m$ 使得 $g(T, k)$ 是 $f(S, m)$ 的子序列，然后判断是否 $m \le n$。

所以我们的任务是求解 $m$。

这是一个简单贪心。在判断「字符串 $a$ 是否是字符串 $b$ 的子序列」时，我们逐位考虑 $a_i$ 与 $b$ 中的哪个字符匹配。如果 $a_i$ 与 $b_{pos_i}$ 匹配，那么在匹配 $a_{i + 1}$ 时，$pos_{i + 1}$ 应该是最靠前的 $p \in (pos_i, |b|]$ 使得 $a_{i + 1} = b_p$。

同理，我们想逐位考虑 $g(T, k)_i$ 但是是不现实的，因为 $k$ 太大了。所以我们逐位考虑 $T_i$，然后计算 $k$ 个 $T_i$ 后，匹配的位置在哪里。这是不难实现的。

定义 $x, y$ 表示当前在第 $x$ 个 $S$ 的第 $y$ 个位置，最开始 $x = 1, y = 0$。然后逐位考虑 $T_i$，调整 $x, y$。最终 $x$ 即所求的 $m$。

上述「调整」过程大致可分三步：

- 将第 $x$ 个 $S$ 的位置 $[y + 1, |S|]$ 匹配完；
- 匹配若干个完整的 $S$；
- 将 $T$ 中没匹配完的字符从头与 $S$ 匹配。

实现上，我们需要维护 $sum_{i, j}$ 表示 $S_{i \sim |S|}$ 中字符 $j$ 的出现次数。进行上述三个操作时需要时刻计算这个操作结束后是否有下一个操作。

完整[代码](https://atcoder.jp/contests/abc346/submissions/51617714)。

---

## 作者：Milthm (赞：3)

我们看到这个“最大值”，再加上子序列满足单调性，所以我们可以二分。

二分一个值 $k$，我们依次遍历 $t$ 串的每个字符，这个时候我们需要找 $s$ 重复 $n$ 遍后（设这个字符串为 $S$），最小的下标 $j_1$ 满足 $S_1\sim S_{j_1}$ 中 $t_i$ 的数量等于 $k$。假设我们能求出来这个 $j_1$，那下次再找下一个下标 $j_2$，在 $S_{j_1+1}\sim S_{j_2}$ 之间 $t_{i+1}$ 的数量等于 $k$，以此往复。如果 $i$ 还没有循环到 $n$，但是 $j_i>n\times |s|$ 了，那么这个 $k$ 值就不符合要求。

那我们怎么求这个最小的下标 $j_i$ 呢？我们只要预处理出来每个字母在 $s$ 中的前缀出现次数，然后再二分一下就可以了。

时间复杂度 $O(|t|\log^2 (|s|n) )$，需要一些卡常才能过。

### AC code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#pragma GCC optimize(2)
using namespace std;
int qwq[35],l1,l2,f[35][N];
ll n;
string s,t;
ll R(ll x,int ch){
	return 1ll*qwq[ch]*(x/l1)+f[ch][x%l1];
}
bool check(ll x){
	ll lst=1;
	for(int i=1;i<=l2;++i){
		ll l=lst-1,r=l1*n,ans=-1;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(R(mid,t[i]-'a')-R(lst-1,t[i]-'a')>=x)ans=mid,r=mid-1;
			else l=mid+1;
		}
		if(ans==-1)return 0;
		lst=ans+1;
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>s>>t;
	l1=s.size();l2=t.size();
	s=" "+s,t=" "+t;
	for(int i=1;i<=l1;++i){
		qwq[s[i]-'a']++;
		for(int j=0;j<26;++j){
			f[j][i]=f[j][i-1]+(s[i]==j+'a');
		}
	}
	ll l=0,r=n*l1,ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：KSCD_ (赞：2)

# 题意
给出整数 $N$ 和两个字符串 $S$ 和 $T$，将字符串 $S$ **整体**复制 $N$ 次拼接起来得到母串，要求把 $T$ 中每个字符**分别**复制 $k$ 次再拼接起来得到的串为母串的子序列，求 $k$ 的最大值。
# 思路
显然，若 $k$ 合法，则 $k-1$ 只需在 $k$ 的取法上把原串中每个字符少取一个即可，因此具有单调性，可以二分答案。

现在需要写出check函数，考虑反过来做，对于一个 $k$ 值求出需要复制 $S$ 串的次数，再与 $N$ 比较来check。

这样问题就成了求把 $T$ 中每个字母按顺序分别取 $k$ 个所需的 $S$ 数量。为了求出这个数量，需要维护 $S$ 串中各字母出现的后缀次数以及各字母出现的位置，具体看下边的代码实现吧。

这里要注意二分的上界，设 $S$ 长度为 $ls$，$T$ 长度为 $lt$，若 $N$ 个 $S$ 串被尽可能利用，最多能使 $k$ 达到 $\lfloor \frac{n\times ls}{lt}\rfloor$，以此为二分上界能在不爆longlong的前提下通过。
# 代码
```cpp
#include<iostream>
#include<vector>
#include<cstring>
#define int long long
using namespace std;
const int N=1e5+10;
const int K=26+10;
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') w=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){ s=s*10+ch-'0'; ch=getchar();}
    return s*w;
}
int n,ls,lt;
char s[N],t[N];
int a[N][K];//a_i 记录s串中第i位到末尾 各个字母出现次数
vector <int> pos[K];//pos_i 记录s串中第i个字母出现的位置 
bool check(int x)
{
	if(x==0) return true;
	int cnt=0,lpos=ls;//cnt表示构成g(T,x)需要的s串个数，lpos表示上一个s串用到了第(lpos-1)位 
	for(int i=0;i<lt;i++)//构成每个字母 
	{
		int tc=t[i]-'a',ts=x;//需要的字符及数量 
		if(ts<=a[lpos][tc]) //如果上一个s串中剩余的tc足够
			lpos=pos[tc][a[0][tc]-a[lpos][tc]+ts-1]+1;//只需修改使用到的位置 
		else
		{
			ts-=a[lpos][tc];//先把上个串用完 
			cnt+=ts/a[0][tc];//再用完整的若干个串 
			ts%=a[0][tc];//还需要多少个该字母 
			if(ts) 
			{
				cnt++;
				lpos=pos[tc][ts-1]+1;
			}//如果还需要，就多用一个串并记录位置 
			else lpos=pos[tc][a[0][tc]-1]+1;//否则记录s串中该字母最后一次出现的位置即可 
		} 
	}
	return cnt<=n;//判断是否合法 
}
signed main()
{
	n=read();
	cin>>s>>t;
	ls=strlen(s),lt=strlen(t);
	for(int i=ls-1;i>=0;i--)
	{
		for(int j=0;j<26;j++) a[i][j]=a[i+1][j];
		a[i][s[i]-'a']++;
	}//倒序处理后缀a数组 
	for(int i=0;i<lt;i++) if(!a[0][t[i]-'a'])
	{
		cout<<0;
		return 0;
	}//这里特判：若t串中有s串没有的字符，则直接输出0
	//如果不判的话，在check函数里会除以0寄掉 
	for(int i=0;i<ls;i++) pos[s[i]-'a'].push_back(i);//正序记录各字母出现位置 
	int l=0,r=n*ls/lt,ans;//这里二分上界要注意 
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}//二分答案 
	cout<<ans;
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：0)

### 简述题面
+ 你有一个正整数 $N$ 和两个小写字符串 $S$ 和 $T$。
+ 你需要把 $N$ 个 $S$ 首尾相接，同时你需要求最大的 $k$，使得把 $T$ 中的每个字母原地重复 $k$ 次以后得到的字符串是前面得到字符串的子串。
+ $1\le N \le 10^{12}, 1\le|S|,|T|\le10^5$。

### 思路
这道题不由得让我想起了 [P9572](https://www.luogu.com.cn/problem/P9572)，于是我打算拿我当时做这题的思路来做。

首先，我们可以思考对于一个确定的 $k$，我们如何判断其可行性。  
子串的题做了这么多，大家应该都知道如果仅判断是否为子串，那么肯定是越往前匹配越好。  
对于 $T$ 中的每一个字母，我们都往后匹配 $k$ 个 $S$ 中对应的字母，到尾了就从头来过，并且把已经使用过的循环节加一。  
因此，这要求我们提前预处理出 $S$ 中每个字母含有多少个，以及每个字母的第某一个在什么位置。  
然后到了 $T$ 中的下一个字母，我们从上一个字母的最后一个位置找到下一个和这个字母匹配的字母。继续如上流程。

由于上一个字母可能正匹配到 $S$ 中间的某一个位置，每一个字母需要有 $O(\log|S|)$ 的时间复杂度来找到应该从之后哪里开始第一个匹配才是最优的。因此对于某一个确定的 $k$，我们可以花 $O(|T|\log|S|)$ 的时间复杂度来确定其是否可行。

又可以发现，当 $k$ 不大于我们的最大值的时候，显然都是可行的，因此我们可以采用二分答案的方式。  
$k$ 的上界在 $S$ 最长、$T$ 最短且全部包含同种字母的时候，此时仍然是 $10^{17}$ 量级，可以接受。

总时间复杂度 $O(\log k|T|\log|S|)$。

### 代码
``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

vector<int> pos[30];

int n;
string s, t;

bool check(int x) {
  int now = 1, nop = -1; // now 表示当前是 S 的第几个循环节，nop 表示上一次匹配到了 S 的哪一个位置
  for(int i = 0; i < t.size(); i++) {
    int l = x;
    auto it = upper_bound(pos[t[i] - 'a'].begin(), pos[t[i] - 'a'].end(), nop);
    if(pos[t[i] - 'a'].size() == 0) {
      return 0;
    }
    if(it == pos[t[i] - 'a'].end()) { // 如果上一次匹配到的位置后面再没有这个字母了
      now++;
      if(now > n) {
        return 0;
      }
      nop = pos[t[i] - 'a'][0];
    } else {
      int y = distance(pos[t[i] - 'a'].begin(), it);
      if(l <= pos[t[i] - 'a'].size() - y) { // 如果上一次匹配到的位置后面的同一个循环节内足够匹配 k 个
        nop = *(it + l - 1);
        l = 0;
        continue;
      }
      now++;
      if(now > n) {
        return 0;
      }
      l -= pos[t[i] - 'a'].size() - y;
      nop = pos[t[i] - 'a'][0];
    }
    now += (l - 1) / pos[t[i] - 'a'].size(); // -1 是为了防止刚好匹配到最后一个，然后因为除法的整区间导致又到了下一个循环节
    if(now > n) {
      return 0;
    }
    l -= (l - 1) / pos[t[i] - 'a'].size() * pos[t[i] - 'a'].size();
    nop = pos[t[i] - 'a'][l - 1];
  }
  return 1;
}

signed main() {
  cin >> n >> s >> t;
  for(int i = 0; i < s.size(); i++) {
    pos[s[i] - 'a'].push_back(i);
  }
  int l = 0, r = 2e17, ans = 0;
  int cnt = 0;
  while(l <= r) {
    int mid = (l + r) / 2;
    if(check(mid)) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << ans;
}
```

---

## 作者：SJH__qwq (赞：0)

二分套二分板子。

显然答案满足单调性，于是考虑二分答案。

设当前二分到答案 $p$。预处理出 $1\sim i$ 中字符 $j$ 出现的次数（前缀和），然后暴力枚举第二个字符串 $T$ 中的每一个字符，在第一个字符串中第二次二分匹配即可。

时间复杂度为 $O(|s|\log^2|s|)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000100;
int n, l1, l2;
char s[N], t[N];
int su1[N][26], su2[N][26];
int get(int x[N][26], int l, int r, int p) {
    return x[r][p] - x[l - 1][p];
}
bool check(int p) {
    int turn = 1, id = 1;
    for (int i = 1; i <= l2; i++) {
        // t[i] 连续出现 p 次|
        // cout << i << ": " << turn << ' ' << id << '\n';
        int sheng = get(su1, id, l1, t[i] - 'a');
        if (sheng >= p) {
            int l = id, r = l1, best = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                if (get(su1, id, mid, t[i] - 'a') >= p) best = mid, r = mid - 1;
                else l = mid + 1;
            }
            if (best == -1) {
                cout << "0\n";
                exit(0);
            }
            id = best + 1;
            if (best == l1) turn++, id = 1;
            if (turn > n) {
                if (turn > n + 1 || id != 1) return false;
            }
        } else {
            int sh = p - sheng;
            int target = get(su1, 1, l1, t[i] - 'a');
            if (!target) {
                cout << "0\n";
                exit(0);
            }
            int gtu = sh / target;
            turn++;
            if (sh % target != 0) turn += gtu;
            else turn += gtu - 1;
            if (sh % target != 0) {
                int key = sh % target;
                int l = 1, r = l1, best = -1;
                while (l <= r) {
                    int mid = l + r >> 1;
                    if (get(su1, 1, mid, t[i] - 'a') >= key) best = mid, r = mid - 1;
                    else l = mid + 1;
                }
                if (best == -1) {
                    cout << "0\n";
                    exit(0);
                }
                id = best + 1;
                if (best == l1) turn++, id = 1;
                if (turn > n) {
                    if (turn > n + 1 || id != 1) return false;
                }
            } else {
                int key = target;
                int l = 1, r = l1, best = -1;
                while (l <= r) {
                    int mid = l + r >> 1;
                    if (get(su1, 1, mid, t[i] - 'a') >= key) best = mid, r = mid - 1;
                    else l = mid + 1;
                }
                if (best == -1) {
                    cout << "0\n";
                    exit(0);
                }
                id = best + 1;
                if (best == l1) turn++, id = 1;
                if (turn > n) {
                    if (turn > n + 1 || id != 1) return false;
                }
            }
        }
    }
    return true;
}
signed main() {
    cin >> n;
    scanf("%s%s", s + 1, t + 1);
    l1 = strlen(s + 1);
    l2 = strlen(t + 1);
    for (int i = 1; i <= l1; i++) {
        for (int j = 0; j < 26; j++) su1[i][j] = su1[i - 1][j];
        su1[i][s[i] - 'a']++;
    }
    for (int i = 1; i <= l2; i++) {
        for (int j = 0; j < 26; j++) su2[i][j] = su2[i - 1][j];
        su2[i][t[i] - 'a']++;
    }
    set<char> se;
    for (int i = 1; i <= l1; i++) se.insert(s[i]);
    for (int i = 1; i <= l2; i++) {
        if (!se.count(t[i])) {
            cout << "0\n";
            return 0;
        }
    }
    // cout << "CHECK YOUR ANSWER...\n";
    // cout << check(3) << '\n';
    int l = 0, r = 3e17, best = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) best = mid, l = mid + 1;
        else r = mid - 1;
    }
    cout << best << '\n';
}
/*
10
my
ym
*/

---

## 作者：small_john (赞：0)

## 思路

很明显，答案具有单调性，二分答案。那么如何对答案 $x$ 判断可行性呢？

依次考虑 $t$ 中的每一个字符，记 $now$ 表示现在匹配到 $s$ 的那个位置。

设当前字符在 $s$ 中出现的位置集合为 $v$，那么我们可以在 $v$ 中二分出第一个大于等于 $now$ 的位置（集合中的）$p$。

设 $v$ 的大小为 $|v|$，分两种情况讨论：

1. $|v|-p\ge x$：即不用再重复一次 $s$ 即可满足当前的位置，$now$ 赋值为 $v$ 中第 $p+x-1$ 大的数加一；
2. $|v|-p<x$：即周期问题，需要重复 $\lceil\frac{x-|v|+p}{|v|}\rceil$ 次 $s$ 才行。

判断的时候动态维护当前重复次数，如果次数小于等于 $n$ 就是可行的。注意这个数是可能超过 $2^{63}-1$ 的，推荐在遍历 $t$ 的同时判断。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
string s,t;
int c,n,m;
vector<int> v[1000];
inline int f(int x,int y){return (x+y-1)/y;}
inline bool ok(int x)
{
	int now = 1;
	int cc = 1;
	for(int i = 1;i<=m;i++)
	{
		if(now>n) now = 1,cc++;
		if(!v[t[i]].size()) return 0;
		int ch = t[i];
		int p = lower_bound(v[ch].begin(),v[ch].end(),now)-v[ch].begin();
		int px = x-(v[ch].size()-p);
		if(p+x-1<v[ch].size())
		{
			now = v[ch][p+x-1]+1;
			continue;
		}
		cc+=f(px,v[ch].size());
		p = px%v[ch].size();
		if(p==0) p = v[ch].size()-1;
		else p--;
		now = v[ch][p]+1;
		if(cc>c) return 0;
	}
//	if(now>n) now-=n,cc++;
	return cc<=c;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>c>>s>>t;
	n = s.size(),m = t.size(),s = ' '+s,t = ' '+t;
	for(int i = 1;i<=n;i++)
		v[s[i]].push_back(i);
	int l = 1,r = 1e18,ans = 0;
	while(l<=r)
	{
		int mid = (l+r)/2;
		if(ok(mid)) l = mid+1,ans = mid;
		else r = mid-1;
	}
	cout<<ans;
	return 0;
}
```

---

