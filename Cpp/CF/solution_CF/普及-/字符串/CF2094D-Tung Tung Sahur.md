# Tung Tung Sahur

## 题目描述

你面前有两个鼓：一个左鼓和一个右鼓。敲击左鼓可以记录为 "L"，敲击右鼓可以记录为 "R"。

这个世界的奇怪力量变幻莫测：有时一次敲击会发出一声响，有时会发出两声响。因此，敲击左鼓可能会发出 "L" 或 "LL"，敲击右鼓可能会发出 "R" 或 "RR"。

敲击的序列记录在字符串 $p$ 中，而实际听到的声音记录在字符串 $s$ 中。给定 $p$ 和 $s$，判断字符串 $s$ 是否可能是由 $p$ 的敲击产生的结果。

例如，如果 $p=$ "LR"，那么敲击产生的结果可能是 "LR"、"LRR"、"LLR" 或 "LLRR"，但不可能是 "LLLR" 或 "LRL"。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
R
RR
LRLR
LRLR
LR
LLLR
LLLLLRL
LLLLRRLL
LLRLRLRRL
LLLRLRRLLRRRL```

### 输出

```
YES
YES
NO
NO
YES```

# 题解

## 作者：szh_AK_all (赞：3)

求出两个字符串的每个极长的字符相同的连续段，然后判断两个字符串对应的连续段所代表的字符是否一致。如果不一致，则答案为 `NO`；否则判断两个字符串对应的连续段的长度的范围是否合法，假设字符串 $p$ 的某个连续段长度为 $k$，那么对应到 $s$ 上的连续段的长度 $len$ 需要满足 $k\le len\le 2k$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
int k[N], kk[N];
 
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	while (n--) {
		string s, ss;
		cin >> s >> ss;
		int c1 = 0, c2 = 0;
		int now = 0;
		while (1) {
			int pp = now;
			while (pp + 1 < (int)s.size() && s[pp + 1] == s[pp])
				pp++;
			k[++c1] = pp;
			now = pp + 1;
			if (now >= s.size())
				break;
		}
		now = 0;
		while (1) {
			int pp = now;
			while (pp + 1 < (int)ss.size() && ss[pp + 1] == ss[pp])
				pp++;
			kk[++c2] = pp;
			now = pp + 1;
			if (now >= ss.size())
				break;
		}
		int f = 1;
		if (s[0] != ss[0] || c1 != c2)
			f = 0;
		else {
			k[0] = -1, kk[0] = -1;
			for (int i = 1; i <= c1; i++) {
				int l1 = k[i] - k[i - 1], l2 = kk[i] - kk[i - 1];
				if (l1 <= l2 && l2 <= l1 * 2)
					continue;
				f = 0;
				break;
			}
		}
		if (f)
			cout << "YES";
		else
			cout << "NO";
		cout << "\n";
	}
}
```

---

## 作者：Aurelia_Veil (赞：2)

# 题解：CF2094D Tung Tung Sahur

这道题比较简单。

首先，先看看顺序，如果你的**第一个**声音不匹配，那就有问题，返回 `NO`。然后我们再看这些声音的段数是否相等，因为你实际的声音和你敲的声音顺序是相同的，所以相同相邻的声音实际听上去也是连续的，所以段数是相同的，反之则不匹配。最后枚举每一段的长度是否在符合范围内，必须大于等于你弹的的声音长度的一倍，小于等于你弹的声音长度的两倍，否则不匹配。

代码按照这个思路模拟就可以了，所以就不给了咩！

---

## 作者：_Star_Universe_ (赞：1)

## [CF2094D](https://www.luogu.com.cn/problem/CF2094D)
### 题意 & 思路
有两个字符串 $p,s$，保证两个字符串仅由 `R` 和 `L` 组成，$p$ 中的 `R` 可以对应 $s$ 中的 `R` 和 `RR`，$p$ 中的 `L` 可以对应 $s$ 中的 `L` 和 `LL`。在这样的规则下如果 $s$ 可能是由 $p$ 转化而来的，输出 `YES`，否则输出 `NO`。

先把两个字符串分别分成较长的字符相同的连续段，如果段数不匹配显然不可能。将分割出的连续段一一比对，若应该对应的两段字符不同（如 `LL:RRR`），则不可能变换成功。最后，因为敲一下左鼓或右鼓至少响一次，至多响两次，所以令 $len_p$ 为 $p$ 中某子串的长度，$s$ 中与其对应的子串长度为 $len_s$，有：$len_p \le len_s \le 2 \cdot len_p$，满足输出 `YES`，不满足输出 `NO`。

---

## 作者：jinhangdong (赞：1)

如果他们的第一个音符不同，肯定不对。

然后统计出，这些串有几段，把每段音符个数计入下来。

如果段数不同不合法。

然后枚举每一段如果实际比弹得少不合法，如果如果实际比弹的两倍多也不合法。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,cnt,cntx,cnty,X[N],Y[N];
string s,p;
int main()
{
	cin>>t;
	while(t--)
	{
		cntx=cnty=0;
		cin>>s>>p;
		if(s[0]!=p[0])
		{
			cout<<"NO\n";
			continue;
		}
		for(int i=0;i<=p.size();++i) X[i]=Y[i]=0;
		cnt=1;
		for(int i=1;i<s.size();++i)
		{
			if(s[i]!=s[i-1])
			{
				X[++cntx]=cnt;
				cnt=1;
			}
			else cnt++;
		}
		X[++cntx]=cnt;
		cnt=1;
		for(int i=1;i<p.size();++i)
		{
			if(p[i]!=p[i-1])
			{
				Y[++cnty]=cnt;
				cnt=1;
			}
			else cnt++;
		}
		Y[++cnty]=cnt;
		if(cntx!=cnty)
		{
			cout<<"NO\n";
			continue;
		}
		bool flag=1;
		for(int i=1;i<=cntx;++i)
		{
			if(Y[i]<X[i])
			{
				flag=0;
				cout<<"NO\n";
				break;
			}
			if(Y[i]>X[i]*2)
			{
				flag=0;
				cout<<"NO\n";
				break;
			}
		}
		if(flag) cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：lingyihan (赞：0)

简单题。

首先 `L` 是不可能敲出 `R`，同理 `R` 也不可能敲出 `L` 的，所以我们应该先分段（以连续 `L` 和 `R`）分段。

接下来看段匹不匹配：总段数一样，并且每段的字符 `L` 或 `R` 也一样。

并且考虑对于连续的 $x$ 个 `L` 或 `R`，能敲出几个，最少肯定是 $1$ 个对应 $1$ 个，最多 $1$ 个对应 $2$ 个，所以 $x \le$ 能敲出的个数 $\le 2x$。

再看每段是否都满足上面的要求。

题解结束了，有问题欢迎私信。

---

## 作者：Never_care (赞：0)

### 题意
判断 $s$ 是否是由 $p$ 的敲击序列产生的。每次操作可以生成一个或两个相同的字符，且生成的字符必须连续。
### 思路
首先根据题意可知 $s$ 的长度必须在 $p$ 的长度和 $2$ 倍 $p$ 的长度之间，因为每次操作最多可生成两个相同的字符。然后查找 $p$ 中字符在 $s$ 中的对应位置以及是否符合题意。$p$ 的字符在 $s$ 中的对应部分可以是 $1$ 或 $2$ 个相同字符，且必须连续。最后遍历 $p$ 和 $s$，确保足够对 $p$ 中的字符进行。
### code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        string p,s;
        cin>>p>>s;
        int len1=p.size();
        int len2=s.size();
        if(len2<len1||2*len1<len2){//判断长度 
            cout<<"NO\n";
            continue;
        }
        int i=0,j=0;
        bool flag=1;
        while(i<len1&&j<len2){
            if(s[j]!=p[i]){
                flag=0;
                break;
            }
            int m=len1-i-1;
            int t=min(len2-j-m,2);
            if(t<1){
                flag=0;
                break;
            }
            int op=1;
            if(j+1<len2&&s[j+1]==p[i]&&t>=2){
                op=2;
            }
            j+=op;
            i++;
        }
        if(i==len1&&j==len2&&flag==1){
            cout<<"YES\n";
        }
		else{
            cout<<"NO\n";
        }
    }
    return 0;
}
```

---

## 作者：Chen_Johnny (赞：0)

# CF2094D Tung Tung Sahur 题解
## 思路
这道题还是很容易想到的。我们发现在敲击的字符串 $p$ 中的任何一次敲击可以贡献 $1$ 或 $2$ 下。因此，我们对 $p,s$ 两个字符串进行分段即可。

例如：`LLRRLL` 会分为 $2$ 个 `L`，$2$ 个 `R`。

我们假设 $p$ 分段分出来的第 $i$ 段的长度为 $p[len]$，字母为 $p[lr]$（对于 $s$ 同理）。

显然此时，当且仅当满足以下条件，字符串为可行的：

- $p[lr]_i  = s [lr]_i$
- $p[len]_i \leqslant s[len]_i \leqslant 2 \times p [len]_i$
## 程序
程序只要照着写就可以了，没有任何技巧可言。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct turn {int len; bool LR;};
vector <turn> seperate (string x) {
    vector <turn> tmp;
    int cnt = 1;
    for (int i = 1; i < x.size (); i ++) {
        if (x [i] == x [i - 1]) cnt ++;
        else if (x [i] != x [i - 1]){
            tmp.push_back ({cnt, (x [i - 1] == 'L')});
            cnt = 1;
        }
    }
    if (cnt != 0) tmp.push_back ({cnt, (x [x.size () - 1] == 'L')});
    return tmp;
}
bool work (string p, string s) {
    vector <turn> pp = seperate (p);
    vector <turn> ss = seperate (s);
    if (pp.size () != ss.size ()) return false;
    for (int i = 0; i < pp.size (); i ++)
        if (pp [i].LR != ss [i].LR || ss [i].len > 2 * pp [i].len || ss [i].len < pp [i].len)
            return false;
    return true;
}
int main () {
    int T; cin >> T;
    while (T --) {
        string p, s;
        cin >> p >> s;
        if (work (p, s)) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
}
```

---

## 作者：HYdroKomide (赞：0)

### 题意

给定一个 0-1 串，可以选择其中一些位置的数字变成两个并且放回原处。问一个串 $p$ 是否可以变成 $s$。

### 思路

考虑对于这两个串分连续段，每段由 $0$ 或者 $1$ 组成。显然这两个串能分成的段数一定相同，同时这些段都是一一对应的。

那么对于在 $p$ 和 $s$ 中对应的同一段，$s$ 的段长度最大是 $p$ 中此段长度的两倍，此时所有 $p$ 中此段的数字都变成了两个。最小是 $p$ 中此段的长度，此时 $p$ 中此段数字都未翻倍。而在这两个长度之间的任何值都是合法的，否则为非法。

模拟判断即可，注意边界的特殊处理。

思考题：假设所有位数字都有 $k$ 的概率变成两个，求 $s$ 可以变成 $p$ 的概率。

### 程序如下

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=2e5+5;
int T,n;
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		string p,s;
		cin>>p>>s;
		int curs=0;
		bool flag=true;
		for(int i=0;i<p.size();i++){
			int stp=i,sts=curs;
			if(s[curs]!=p[i]){
				flag=false;
				break;
			}
			while(i!=p.size()-1&&p[i]==p[i+1])i++;
			int lenp=i-stp+1;
			while(curs!=s.size()-1&&s[curs]==s[curs+1])curs++;
			int lens=curs-sts+1;
			if(lenp>lens||(lenp<<1)<lens){
				flag=false;
				break;
			}
			curs++;
		}
		if(curs!=s.size())flag=false;
		if(flag)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

### THE END

---

## 作者：wwwidk1234 (赞：0)

~~[在博客园食用更佳（？）](https://www.cnblogs.com/wwwidk1234)~~

## 题目

给定原串 $s$ 和目标串 $t$，你可以把 `L` 变成 `LL` 或把 `R` 变成 `RR`，求是否可以将 $s$ 在有限次操作内变成 $t$。

## 思路

可以试着将 `L` 和 `R` 分割来看，比如 `LLLLRRLL` 可以分割成 `LLLL,RR,LL`。

首先，如果每一段的字符不同（即遇到了类似 `LL:RRR` 的情况）显然答案为 `NO`。

接下来对于每一个段，设该段的长度为 $x$，变化后的长度为 $L$，不难发现：当不做任何操作时，$L=x$ 为最小值；当把所有的 `L` 都替换成 `LL` 时（`R` 同理），$L=2x$ 为最大值。故 $L$ 的取值范围为 $x \le L \le 2x$。

为了方便判断，代码中，如果该串的字符为 `L` 则长度变成相反数。即代码中的 `if(s[i]=='L') a.push_back(-bfs(s,i));`。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=-1;
inline int bfs(string &s,int x)  //找连通块
{
	char a=s[x];
	int cnt=1;
	for(int i=x+1;s[i];i++)
	{
		if(s[i]!=a) break;
		cnt++;
		s[i]='A';
	}
	return cnt;
}
inline bool solve()
{
	string s,t;
	vector<int> a,b;
	cin>>s>>t;
	for(int i=0;s[i];i++)
	{
		if(s[i]=='R') a.push_back(bfs(s,i));
		else if(s[i]=='L') a.push_back(-bfs(s,i));
	}
	for(int i=0;t[i];i++)
	{
		if(t[i]=='R') b.push_back(bfs(t,i));
		else if(t[i]=='L') b.push_back(-bfs(t,i));
	}
	if(a.size()!=b.size()) return 0;
	const int n=a.size();
	for(int i=0;i<n;i++)
	{
		// cerr<<i<<' '<<a[i]<<' '<<b[i]<<endl;
		if(a[i]<0&&b[i]>0) return 0;
		if(a[i]>0&&b[i]<0) return 0;
		a[i]=abs(a[i]),b[i]=abs(b[i]);
		if(!(a[i]<=b[i]&&b[i]<=2*a[i])) return 0;
	}
	return 1;
}
int main()
{
//	freopen("neuvillette.in","r",stdin);
//	freopen("neuvillette.out","w",stdout);
    int T;
	cin>>T;
	while(T--)
	{
		puts(solve()?"YES":"NO");
		// cerr<<endl;
	}
	return 0;
}
/*
LLL 最小可以构造 LLL  最大可以构造 LLLLLL  3<=size<=2*3
*/
```

---

## 作者：zhangli828 (赞：0)

## 题目大意
给你两个字符串 $p,s$ 你可以把 $p$ 中的 `L` 换成 `LL` 或者把 `R` 换成 `RR`。请问最后 $p$ 能否变成 $s$。
## 题目思路
我们可以把 $p$ 和 $s$ 字符相同的两段提取出来，然后看是否满足即可。但是如果两个字符串的第一个字符不同或 $p$ 和 $s$ 中有一个字符串没有处理玩，那么直接输出 `NO`。
## 题目解法
我们可以统计出 $p$ 和 $s$ 字符相同的两段提取出来，假设长度分别为 $sum1$ 和 $sum2$，因为 $p$ 只增不减所以 $sum1$ 一定小于等于 $sum2$，因为一个字符最多只能增加一个相同的字符，所以又得到 $2\times sum1$ 一定大于等于 $sum2$，所以按以上方法处理即可。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 2e5 + 10;

int a[2][kMaxN], T, i, j, sum1, sum2, flag;
string p, s;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> T; T--; flag = 0) {
    cin >> p >> s;
    if (p[0] != s[0]) {  // 特判前两个是否相等
      cout << "NO\n";
      continue;
    }
    for (i = 0, j = 0; i < p.size() && j < s.size(); i++, j++) {
      sum1 = sum2 = 1;
      for (; i < p.size() - 1 && p[i] == p[i + 1]; sum1++, i++);  // 统计 sum1
      for (; j < s.size() - 1 && s[j] == s[j + 1]; sum2++, j++);  // 统计 sum2
      if (sum1 > sum2 || sum1 * 2 < sum2) {  // 看是否满足
        flag = 1;
        break;
      }
    }
    cout << (i != p.size() || j != s.size() || flag ? "NO\n" : "YES\n");  // 最后输出
  }
  return 0;
}
```

---

## 作者：metrixgo_caozhendi (赞：0)

一道字符串遍历的问题。先看范围是 $n\le2\times10^5$，所以不能暴力枚举每一个打击是否是双响。仔细观察后会发现，当字符串 $p$ 中出现一段一样的字符，比如 ```LLL``` 时，$s$ 里也会相应地出现若干个 ```L```。我们称这两段字符串为对应字符串。你会发现对于 $s$ 上的对应字符串，我们有两个限制：一是它不能小于 $p$ 上的对应字符串，因为每一次打击至少产生一次声响；二是相对的，它不能大于 $p$ 上的对应字符串的长度的**两倍**，因为每一次打击至多产生两次声响。

察觉到以上规律以后，我们可以定义两个指针，两个指针从左往右扫到一段重复字符的末尾，然后进行长度比较。如果不符合上述限制，就输出 ```NO```。当整个字符串遍历完以后都没出现问题，就是 ```YES```。

代码如下（其实有些地方可以优化一下，但是影响不大）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=805;
int t,n,m,k,l,r,flg;
int a[N][N],book[2*N];
string s,p;
queue<int> q;
int main()
{
   cin>>t;
	while(t--)
	{
		cin>>p>>s;
		n=p.size(),m=s.size();
		p='0'+p,s='0'+s,l=1,r=1,flg=0;
		int lcnt=0,rcnt=0;
		while(l<=n&&r<=m)
		{
			while(l<=n&&p[l]=='L') l++,lcnt++;
			while(r<=m&&s[r]=='L') r++,rcnt++;
			if(!(lcnt<=rcnt&&rcnt<=lcnt*2)) break;
			lcnt=0,rcnt=0;
			while(l<=n&&p[l]=='R') l++,lcnt++;
			while(r<=m&&s[r]=='R') r++,rcnt++;
			if(!(lcnt<=rcnt&&rcnt<=lcnt*2)) break;
			lcnt=0,rcnt=0;
			if(l>n&&r>m) flg=1;
		}
		if(flg) cout<<"YES\n";
		else cout<<"NO\n";
	}
   return 0;
}
```

---

