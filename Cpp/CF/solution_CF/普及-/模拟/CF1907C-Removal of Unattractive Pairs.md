# Removal of Unattractive Pairs

## 题目描述

Vlad found a string $ s $ consisting of $ n $ lowercase Latin letters, and he wants to make it as short as possible.

To do this, he can remove any pair of adjacent characters from $ s $ any number of times, provided they are different. For example, if $ s $ =racoon, then by removing one pair of characters he can obtain the strings coon, roon, raon, and raco, but he cannot obtain racn (because the removed letters were the same) or rcon (because the removed letters were not adjacent).

What is the minimum length Vlad can achieve by applying any number of deletions?

## 说明/提示

In the first test case of the example, you need to act as follows: "aabc" $ \rightarrow $ "ac" $ \rightarrow $ "". Note that with a different order of deletions, the string will not become empty.

## 样例 #1

### 输入

```
10
4
aabc
5
abaca
10
avbvvcvvvd
7
abcdefg
5
dabbb
8
aacebeaa
7
bbbbacc
6
dacfcc
6
fdfcdc
9
dbdcfbbdc```

### 输出

```
0
1
2
1
1
0
1
0
0
1```

# 题解

## 作者：mywzj_mo (赞：13)

### 题目大意
给定一个字符串 $s$，每次可以删除其中两个相邻且不同的两个字符（当且仅当 $s_i \ne s_{i+1}$ 时，可以删除 $s_i$ 和 $s_{i+1}$），求删除后字符串的最小长度。

### 详细思路
我们只需要考虑出现次数最多的字符的个数，如果出现次数最多的字符的个数没超过 $\frac{n}{2}$，则一定可以删掉,反之，则会剩下一些。

证明：设出现次数最多的字符个数为 $a$，其余字符的个数为 $b$，如果 $a \le b$ ，则一定存在方案使得出现次数最多的字符全被删除，且剩下 $b-a$ 个不同字符，且一定存在方案使得 $b-a$ 个字符两两相除，剩下 $1$ 个（$n \bmod 2 = 1$）或 $0$ 个（$n \bmod 2 = 0$）字符。但如果 $a>b$，则出现次数最多的字符不能够被全部删除，会留下 $a-b$ 相同的字符，这些字符不能够再删除，答案就是 $a-b$。

### 代码
温馨提示：诚信作人，不要抄袭。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans,maxn;
int ch[30];
string s;
int main(){
	cin>>t;
	while(t--){
		memset(ch,0,sizeof(ch));
		cin>>n;
		cin>>s;
		for(int i=0;i<n;i++){
			ch[s[i]-'a']++;
		}
		ans=n%2;
		maxn=0;
		for(int i=0;i<26;i++){
			maxn=max(maxn,ch[i]);
		}
		ans=max(ans,maxn*2-n);
		cout<<ans<<"\n";
	}
}
```


---

## 作者：zhouruoheng (赞：2)

## C.Removal of Unattractive Pairs

### 题面翻译

有一个长为 $n$ 的字符串，每次可以删除相邻两个**不同**的字符，问删除若干次最终可能的最短长度

### 分析

这让我想到一种类似的题，只不过是把题目和解法反过来。

已知小写字母组成的长度为 $n$ 的字符串，求个数超过 $n/2$ 的小写字母，保证至多至少有一个，$1<n<1 \times 10^8$。

* 直接排序，取最中间的那个数，复杂度为 $O(n\log{n})$。
* 用一个桶统计个数，再找出满足的那个，复杂度为 $O(n)$。

还能不能更快呢？于是聪明的你一定能想到每次读入后删掉两个不同的字母，没错，删掉两个不同的字母后，永远不会影响我们要求的答案。用我们要求的答案来和其他字母相删，最后一定有剩余。这样就能做到更快的线性复杂度求出答案了。

接下来回到这道题，考虑删除难想，不如考虑不删除的情况：
* 字符串为空。
* 只剩下一个字符。

那就好了，相邻的限制已经无所谓了，我们可以知道最短的长度就是让数量最多的字母与其他字母互删，得到剩下的数量 $num$，还要注意 $n$ 如果是奇数的话一定会剩下一个，最后答案就是 $\max(num,n\bmod2)$。
### code
``` cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,t,a[N];
string s;
void solve()
{
	cin>>n>>s;
	for(int i=0;i<n;i++) a[s[i]-'a']++;
	int ma=0;
	for(int i=0;i<26;i++) ma=max(ma,a[i]),a[i]=0;
	cout<<max(n&1,ma*2-n)<<"\n";
}
int main ()
{
	cin>>t;
	while(t--) solve();
	return 0;
}

```

---

## 作者：yuyc (赞：2)

## 题意
给定一个长度为 $n$ 的字符串 $s$，为了让这个字符串变短，你可以选择字符串中相邻的两个不同的字符进行删除。

问经过若干次操作，这个字符串可以达到的最短长度。

### 解析
我们不难发现，操作到最后可能会有以下两种情况：

- 字符串中没有字符。
- 字符串中只有单种字符。

我们记一个字符串中出现次数最多的字符为 $c$，其出现次数为 $maxcnt$，则字符串中其它字符的个数总和为 $n-maxcnt$。

操作到最后，如果字符串中有单种字符，那么这种字符必定是 $c$。 

也就是说，字符串中 $(n-maxcnt)$ 个所有其它字符都跟 $maxcnt$ 个 $c$ 消除了，还剩下 $maxcnt - (n - maxcnt)$ 个 $c$，此时必定有 $2maxcnt \ge n$。

反过来，如果 $2maxcnt \ge n$，那么让所有其它字符都跟 $c$ 消除，必定剩下 $maxcnt-(n-maxcnt)=2maxcnt-n\ge 0$ 个 $c$。

故如果 $2maxcnt \ge n$，答案就为 $maxcnt-(n-maxcnt)$。

否则每次消除操作都能够使得两个不同字符的出现次数减 $1$，最终答案就是 $n\bmod2$。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt[30];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		memset(cnt,0,sizeof(cnt));
		int n,maxcnt = 0;
		string s;
		cin>>n>>s;
		for(int i=0;i<s.size();i++){
			cnt[s[i] - 'a']++;
			maxcnt = max(maxcnt,cnt[s[i] - 'a']);
		}
		if(maxcnt <= n / 2) cout<<n % 2;
		else cout<<maxcnt - (n - maxcnt);
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：dhpzy (赞：0)

# 题意
给你 $t$ 个长度为 $n_i$ 的字符串 $s_i$，每次可以删除相邻两个不一样的字符，求删除若干次后的最短长度。
# 思路
我们发现当某两个相邻的字符如果是相同的，可以通过别的字符来删除他们，所以我们只需考虑出现次数最多的字符的个数。

记出现次数最多的字符的个数为 $maxn$，如果 $maxn$ 超过 $\dfrac{n_i}{2}$，那么最短长度为 $2maxn-n_i$，否则为零。

特别地，如果字符串的长度为奇数，那么最短长度为一。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int t,a[1000];
int main()
{
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof a);//多测记得清空
		int n,maxn=-10;
		string s;
		cin>>n>>s;
		for(int i=0;i<n;i++) a[s[i]-'a']++;
		for(int i=0;i<26;i++) maxn=max(maxn,a[i]);
		cout<<max((n&1),maxn*2-n)<<endl;
	}
}
```


---

## 作者：abensyl (赞：0)

原题：[CF1907C Removal of Unattractive Pairs](https://www.luogu.com.cn/problem/CF1907C)。

## 思路

考虑如果有奇数个字符，一定会剩下一个。

考虑如果数列中有两种互不相同的字符，那么他们就一定在某一个位置出现不同字符挨在一起的情况。

那么，最后如果有剩下来的，一定是原本出现次数最多的字母，所以如果有奇数个字符，我们要优先考虑把出现次数最多的剩下来。

否则，如果某个字符的占比超过了 $1\over 2$，那么它才可能被剩下来，然后就很容易求出答案了。

## 代码
```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;
int cnt[128];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--) {
		memset(cnt,0,sizeof cnt);
		int n,res=0;
		cin>>n;
		string s;
		cin>>s;
		for(auto c:s) cnt[c]++;
		if(n%2) {
			int mxid=0;
			for(int i=1;i<128;++i)
				if(cnt[i]>cnt[mxid]) mxid=i;
			cnt[mxid]--,res=1,--n;
		}
		for(int i=0;i<128;++i) {
			if(n-cnt[i]>=cnt[i]) continue;
			else res+=cnt[i]*2-n;
		} cout<<res<<'\n';
	}
	return 0;
}
```

---

