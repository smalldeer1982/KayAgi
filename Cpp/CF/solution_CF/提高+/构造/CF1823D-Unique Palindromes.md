# Unique Palindromes

## 题目描述

令 $p(t)$ 表示字符串 $t$ 的不同回文子串数（不同即多次出现只算一次）。

令 $p(s,m)$ 表示字符串 $s$ 的 $m$ 前缀的不同回文子串数，即 $p(s,m)=p(t)$，其中 $t=s[1..m]$。

如：$t=\texttt{abcbbcabcb}$，则 $p(t)=6$（$\texttt{a},\texttt{b},\texttt{c},\texttt{bb},\texttt{bcb},\texttt{cbbc}$），$p(t,5)=p(\texttt{abcbb})=5$（$\texttt{a},\texttt{b},\texttt{c},\texttt{bb},\texttt{bcb}$）。

给定整数 $n$ 和 $k$ 个条件，第 $i$ 个条件用 $(x_i,c_i)$ 表示，意思是对于字符串 $s$，满足 $p(s,x_i)=c_i$。

请你构造一个由小写拉丁字母组成的长度为 $n$ 的字符串 $s$，使其满足所有的 $k$ 个条件。

## 说明/提示

$1\le t\le10^4$，$3\le n\le2\times10^5$，$1\le k\le20$。

$3\le x_1<x_2<\dots<x_k=n$，$3\le c_1\le c_2\le\dots\le c_k\le\min\left(10^9,\frac{(n+1)n}2\right)$。

每组数据的 $n$ 的总和 $\sum n\le2\times10^5$。

## 样例 #1

### 输入

```
7
10 2
5 10
5 6
3 1
3
3
4 2
3 4
3 3
4 2
3 4
3 4
4 1
4
5
10 3
4 6 10
4 5 8
10 4
4 6 7 10
4 5 7 8```

### 输出

```
YES
abcbbcabcb
YES
foo
YES
ayda
YES
wada
NO
YES
abcbcacbab
NO```

# 题解

## 作者：ForgotDream_CHN (赞：4)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17374435.html)

## 题意

你要构造一个长度为 $n$ 的由小写字母组成的字符串，满足给出的 $k$ 个约束。其中，每个约束以 $p(x_i, c_i)$ 的方式给出，表示构造的字符串长度为 $x_i$ 的前缀中应包含 $c_i$ 个本质不同的回文子串（单个字符也算）。

$3 \le n \le 2 \times 10^5$，$1 \le k \le 20$。数据间的具体关系请参照原题题面。

## 思路

我的做法来自 @[LeavingZ](https://www.luogu.com.cn/user/215697) 学长，跟官方题解不太一样。

容易发现一个长度为 $n$ 的字符串，其本质不同的回文子串不会超过 $n$ 个，而当这个字符串只由同一个字符构成时，正好有 $n$ 个本质不同的回文子串。

于是我们可以做出如下的考虑：如果只有一个约束 $p(x_i, c_i)$，先随便选一个小写字母，就假设是 $\texttt{a}$ 吧，组成一个长度为 $c_i - 2$ 的字符串，然后剩余的部分用不同的两个小写字母，假设为 $\texttt{x}$ 与 $\texttt{y}$ 吧，与你之前选的那个字母拼在一起，得到 $\texttt{xya}$，把这个字符串剩余的部分填满，如果剩余的长度不为 $3$ 的倍数，则把多余的部分截断就行了。这样做的话，前面长度为 $c_i - 2$ 的部分会构成 $c_i - 2$ 个回文子串，而后边的 $\texttt{xya}$ 由于不会出现重复，所以只会出现两个回文子串 $\texttt{x}$ 与 $\texttt{y}$。这样就刚好有了 $c_i$ 个回文串。

选取的两个字符相当于分隔符，从而保证不含这两个字符的回文串只出现在前边的部分，并且不会与后边的部分构成回文串。但为什么要选两个不同字符呢？因为至少两个不同的字符才能做分隔符，否则仍然会出现跨越前后部分的回文串，比如 $\texttt{aaxa}$ 中，$\texttt{axa}$ 就是一个多出来的回文串。

可能还没说清楚？举个例子。比如说 $x_i = 8$，$c_i = 5$，先写下 $c_i - 2 = 3$ 个 $\texttt{a}$，得到 $\texttt{aaa}$，此时还剩下 $5$ 个字符没填，再用 $\texttt{xya}$ 去填剩余的部分，得到 $\text{aaaxyaxy}$，不难发现这个串刚好有 $5$ 个回文子串。

这是只考虑一个约束的情况，如果有多个约束呢？直接接着像上边那样构造肯定是不行的，因为 $\texttt{x}$ 与 $\texttt{y}$ 都已经被计算过了，不能重复计算。而且，也不能接着用 $\texttt{a}$ 来构造了，否则就可能会意想不到的回文串或者因为重复计算而导致个数不足。由于前边已经填了 $c_i$ 个，所以只需要再构造 $c_{i + 1} - c_i$ 个回文串就行了，因此为了方便，我们记 $\Delta c = c_{i + 1} - c_i$。

这两个问题都是很好解决的。对于第一个问题，我们可以直接用 $\Delta c$ 个字母去填，这样就可以保证至少还能再填出 $\Delta c$ 个回文串，而对于第二个问题，我们可以不用 $\texttt{a}$ 去填嘛，反正除去 $\texttt{x}$ 与 $\texttt{y}$ 之后，还剩 $24$ 个字母，而题目中的 $k \le 20$，显然是够用的。

好像做完了？当然没有！考虑样例中的一组数据：

```
10 3
4 6 10
4 5 8
```

如果单纯的按照上边的算法来填的话，最终会得到 $\texttt{aaxyb{\color{red}{xcccx}}}$，标红的部分多出了一个回文串。这是由于在填第二个的时候刚好剩余一个字符，而这就会导致出现重复的回文串。

解决办法有两种，一种是由学长提出的，同时交替使用 $\texttt{xy}$ 与 $\texttt{wz}$ 来做冗余，剩余的 $22$ 个字母仍然够用；另一种是我个人的做法，即当出现这种刚好剩余一个字符的情况时，将 $\texttt{xy}$ 反转为 $\texttt{yx}$ 再按照上边的方法去填，如果采取这种方法，样例得到的串就是 $\texttt{aaxybxcccy}$，不会出现前后交叉的回文串。如果再出现这种情况，则再将 $\texttt{xy}$ 翻转回去即可。这其实也是冗余的思想。

## 一些细节

这道题可能会出现无解的数据。首先就是当存在 $c_i > x_i$ 的时候，由于长度为 $n$ 的串最多有 $n$ 个本质不同的回文子串，显然这种状况是不合法的。当存在 $c_{i + 1} - c_i > x_{i + 1} - x_i$ 时，该组数据同样是无解的，理由与上边的那种一样。

还有一个细节就是这种做法需要把 $x$ 与 $c$ 都相等的约束合并到一起，否则样例都过不了。

## 代码

代码写得比较粪，可能与上边的叙述稍有出入，但是逻辑是一样的。

```cpp
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> x(k), c(k);
  for (int i = 0; i < k; i++) {
    std::cin >> x[i];
  }
  for (int i = 0; i < k; i++) {
    std::cin >> c[i];
  }

  for (int i = 0; i < k; i++) {
    if (x[i] < c[i]) {
      std::cout << "NO\n";
      return;
    }
  }

  std::vector<int> newx, newc;
  int prec = 0, prex = 0;
  for (int i = 0; i < k; i++) {
    if (c[i] != prec) {
      if (i != 0) {
        newx.push_back(prex);
        newc.push_back(prec);  
      }
      prec = c[i];
    }
    prex = x[i];
  }
  newx.push_back(prex), newc.push_back(prec);

  x = newx, c = newc;

  std::string ans = "", delta = "xy";
  int pre = 0, pivot = 0;
  for (int i = 0; i < x.size(); i++) {
    char ch = i + 'a';
    int cur = c[i] - pre;
    if (i == 0) {
      for (int i = 0; i < cur - 2; i++) {
        ans += ch;
        ++pivot;
      }
      if (pivot > x[i]) {
        std::cout << "NO\n";
        return;
      }
    } else {
      for (int i = 0; i < cur; i++) {
        ans += ch;
        ++pivot;
      }
      if (pivot > x[i]) {
        std::cout << "NO\n";
        return;
      }
    }
    int rst = (x[i] - pivot) / 3;
    for (int i = 0; i < rst; i++) {
      ans += delta + ch;
      pivot += 3;
    }
    if (pivot < x[i]) {
      ans += delta.substr(0, x[i] - pivot);
      if (x[i] - pivot == 1) {
        std::reverse(delta.begin(), delta.end());
      }
      pivot = x[i];
    }
    pre = c[i];
  }

  std::cout << "YES\n";
  std::cout << ans << "\n";

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
```

---

## 作者：UnyieldingTrilobite (赞：1)

致敬传奇字符串 1k9 两个人做了 48 分钟。

由经典结论：以一个位置为结尾的新增本质不同回文串至多一个。于是我们可以非常方便地判掉无解。我们考虑对于除了被判掉以外的所有情况执行构造。我们考虑重复字母的堆叠可以以较高的效率达到这个上界，于是我们计划在相邻两个关键位置之间塞一个形如 `zzzzzzzzzzzzzzzzzzz` 的串来完成对答案的贡献。注意到前三个字符用 `abc` 也可以达到一样的效率，为啥要判出来下面会说。

由于我们只有不超过 20 组约束，我们可以对每一组约束使用一个不同的字母来填充答案。那接下来就只需要构造对其他位置的一个填充方案满足不存在多余的回文串即可。如果一个回文串经过了一段重复字母，显然它一定完整包含之且以其作为中点。于是我们可以直接把这段字母删掉并考虑一个更强的结论：这个填充方案不存在长度超过 1 的回文子串。注意到 `abc` 结构的重复堆叠很适合这一点，于是就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=29;
int T,n,k,c[N],x[N];
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	for(cin>>T;T;--T){
		cin>>n>>k;
		for(int i=1;i<=k;++i)cin>>x[i];
		for(int i=1;i<=k;++i)cin>>c[i];
		adjacent_difference(x+1,x+k+1,x+1);
		adjacent_difference(c+1,c+k+1,c+1);
		string ans="abc";
		int p=0;
		for(int i=1;i<=k;++i)
			if(x[i]<c[i])goto NO;
		for(int i=1;i<=k;++i){
			int z=x[i]-c[i];
			while(z--)ans+=p+'a',(++p==3&&(p=0));
			z=c[i];
			if(i==1)z-=3;
			ans+=string(z,'z'-i+1);
		}
		cout<<"YES"<<'\n'<<ans<<'\n';goto YES;
		NO:cout<<"NO"<<'\n';YES:;
	}
	return cout<<flush,0;
}
```

---

## 作者：StarRain3 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/LuoGuyexc/articles/17397324.html)。

一道贪心题。

首先，本质不同的回文串最多只有 $n$ 个.

我们注意到 $k$ 很小，甚至小于字符集的大小，我们不难发现一个长度为 $x$ 的由相同字母组成的串能够贡献 $x$ 个本质不同回文子串。

所以其实每一段我们都可以使用一种相同的字母来实现回文子串数量的增加，因为 $k$ 小于 $26$，所以字母数量是够用的。

下面还有个问题就是要把相同串之间填充，使得不产生新的回文子串。

我们可以考虑第一段用后面全部为 $c$ 的方式填充，然后中间空余的部分就不停地用重复的循环串来填充，可以发现这样不会产生新的回文子串。


```cpp
for (int i = 0; i < k; i++) {
	if (c[i] > x[i]) {
		s.clear();
		break;
	}
	if (i == 0) {
		s += "ab", s += string(c[i] - 2, 'c');
		int cnt = x[i] - c[i];
		s += add.substr(st, cnt), st += cnt;
	} else {
		if (c[i] - c[i - 1] > x[i] - x[i - 1]) {
			s.clear();
			break;
		}
		int need = c[i] - c[i - 1];
		int cnt = x[i] - x[i - 1] - need;
		s += add.substr(st, cnt);
		st += cnt;
		s += string(need, char('a' + i + 2));
	}
}

```

---

