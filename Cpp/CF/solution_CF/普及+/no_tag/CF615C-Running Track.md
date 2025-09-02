# Running Track

## 题目描述

A boy named Ayrat lives on planet AMI-1511. Each inhabitant of this planet has a talent. Specifically, Ayrat loves running, moreover, just running is not enough for him. He is dreaming of making running a real art.

First, he wants to construct the running track with coating $ t $ . On planet AMI-1511 the coating of the track is the sequence of colored blocks, where each block is denoted as the small English letter. Therefore, every coating can be treated as a string.

Unfortunately, blocks aren't freely sold to non-business customers, but Ayrat found an infinite number of coatings $ s $ . Also, he has scissors and glue. Ayrat is going to buy some coatings $ s $ , then cut out from each of them exactly one continuous piece (substring) and glue it to the end of his track coating. Moreover, he may choose to flip this block before glueing it. Ayrat want's to know the minimum number of coating $ s $ he needs to buy in order to get the coating $ t $ for his running track. Of course, he also want's to know some way to achieve the answer.

## 说明/提示

In the first sample string "cbaabc" = "cba" + "abc".

In the second sample: "ayrat" = "a" + "yr" + "at".

## 样例 #1

### 输入

```
abc
cbaabc
```

### 输出

```
2
3 1
1 3
```

## 样例 #2

### 输入

```
aaabrytaaa
ayrat
```

### 输出

```
3
1 1
6 5
8 7
```

## 样例 #3

### 输入

```
ami
no
```

### 输出

```
-1
```

# 题解

## 作者：Tx_Lcy (赞：6)

提供一种暴力碾标算的思路。

[题目传送门](https://www.luogu.com.cn/problem/CF615C)
## 思路
本题解使用纯暴力实现，目前是最优解，并且比别的 $\verb!AC!$ 代码快一倍以上。

我们记录一个初始字符串 $s1$ 表示用来匹配的串，$s2$ 表示要匹配的串，然后记录字符串 $s11$ 表示 $s1$ 翻转后的串。

然后就暴力匹配，没错，就是暴力，在 $s1$ 和 $s11$ 中从前往后扫，一个一个匹配过去。这个东西可以用 $\verb!kmp!$ 优化，但是我不想优化，因为这样的时间复杂度是正确的。

现在我们来证明一下这个东西的时间复杂度：

从 $1$ 开始扫，假设我们扫到的最大长度为 $l$，显然，另外扫到的长度一定小于 $l$，所以扫一次的时间复杂度为严格小于 $O(nl)$，由于 $\sum l=m$，所以总时间复杂度严格小于 $O(nm)$，且在实际中常数非常小，远远跑不到，严格吊打所有题解。
## 思路
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e3+10;
vector< pair<int,int> >ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	string s1,s2;cin>>s1>>s2;
	int l1=s1.length(),l2=s2.length(),l=1;
	s1=" "+s1,s2=" "+s2;
	string s11=s1.substr(1,l1);
	reverse(s11.begin(),s11.end()),s11=" "+s11;
	while (l<=l2){
		int maxn=0,maxni;
		for (int i=1;i<=l1;++i){
			int j=i,j1=l;
			while (s1[j]==s2[j1] && j<=l1 && j1<=l2) ++j,++j1;//暴力匹配
			if (j-i>maxn) maxn=j-i,maxni=i;
		}
		int maxn1=0,maxni1;
		for (int i=1;i<=l1;++i){
			int j=i,j1=l;
			while (s11[j]==s2[j1] && j<=l1 && j1<=l2) ++j,++j1;//暴力匹配
			if (j-i>maxn1) maxn1=j-i,maxni1=i;
		}
		if (!maxn && !maxn1) return cout<<"-1\n",0;
		if (maxn1>maxn) l+=maxn1,ans.push_back({l1-maxni1+1,l1-maxni1-maxn1+2});
		else l+=maxn,ans.push_back({maxni,maxni+maxn-1});
	}
    cout<<ans.size()<<'\n';
    for (auto i:ans) cout<<i.first<<' '<<i.second<<'\n';
	return 0;
}
```


---

## 作者：_edge_ (赞：1)

前言，这篇题解提两种思路 ~~然而有一种被卡常，过不去了。~~

首先说一下 $O(nm \log nm)$ 的做法。

我们发现这个字符串非常不好处理，所以我们可以将它搞成几个哈希的值，然后对于 $s$ 正着做一遍，反着做一遍，大概可以把所有情况都给计算出来，这边需要维护一个桶，或者一个数组来记录当前的哈希值。

然后对于 $t$ 这个字符串来讲，我想到了一种 DP 的想法，就是 $f_i = f_j +1$ 如果 $i$ 到 $j$ 这段字符串是在那个桶里面的，这也可以用哈希来搞。

然后发现这个常数非常的不友好，因为哈希本身就带了大常数，所以我卡了半天也没有卡过去。

有兴趣的同学可以卡一下，并告诉我一声。(

然后是正解 $O(nm)$，我们发现那个 DP 其实完全就不必要。

首先我们可以发现，如果存在一个子串假设长度为 $a$，能覆盖掉 $t$ 里面的一段子串，那么显然如果当长度为 $a-1$ 也可以覆盖掉对应的，$a-2$ 也一样，$a-3$ 也一样 …… 然后实际上如果我们当前这一步取了最优解，也就是最长的给它接上去，发现它其实就是最优的。

感性的理解一下，如果不是最优的话，那么后面肯定有一段空出来的，显然如果不给前面的肯定给后面的，那还不如给前面的。

然后你会发现这个贪心就非常容易实现，并且跑得飞快。

考虑维护出 $t$ 里面以 $t_i$ 为开头，在 $s$ 的对应开头为 $s_j$，他们的最长相同的子串。

转移方程就是当 $t_i = s_i$，那么 $f_{i,j}=f_{i+1,j+1}+1$。

这边注意也要倒着做一遍，然后你去暴力匹配那个 $t$ 串，寻找出当前以 $i$ 为开头的最长子串，然后大概记录一下路径答案之类的，这道题就解决了。

如有问题还请指出。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=2105;
string s1,s2;
int n,m,f[INF][INF],lcp[INF][INF],ans[INF*INF][5],tot;
int lcpe[INF][INF],f1[INF][INF];
signed main()
{
        ios::sync_with_stdio(false);
        cin>>s1>>s2; n=s1.size(); m=s2.size();
        s1=" "+s1; s2=" "+s2;
        for (int i=n; i>=1; i--)
                for (int j=m; j>=1; j--)
                        if (s1[i]==s2[j]) {
                                lcp[i][j]=lcp[i+1][j+1]+1;
                                if (lcp[i][j]>1) f[i][j]=f[i+1][j+1];
                                else f[i][j]=i;
                        }
        for (int i=1; i<=n; i++)
                for (int j=m; j>=1; j--)
                        if (s1[i]==s2[j]) {
                                lcpe[i][j]=lcpe[i-1][j+1]+1;
                                if (lcpe[i][j]>1) f1[i][j]=f1[i-1][j+1];
                                else f1[i][j]=i;
                        }
        for (int i=1; i<=m; ) {
                int j=0,j1=0; int fl=i;
                for (int k=1; k<=n; k++)
                        if (lcp[k][i]>lcp[j][i]) j=k;
                for (int k=1; k<=n; k++)
                        if (lcpe[k][i]>lcpe[j1][i]) j1=k;
                if (lcp[j][i]>lcpe[j1][i]) {
                        //cout<<f[j][i]<<" "<<i<<"\n";
                        // cout<<lcp[1][i]<<" "<<i<<"\n";
                        ans[++tot][0]=j;
                        ans[tot][1]=f[j][i];
                        i+=lcp[j][i];
                }
                else {
                        //cout<<i<<" "<<f1[j1][i]<<"\n";
                        // cout<<j1<5<"\n";
                        ans[++tot][0]=j1;
                        ans[tot][1]=f1[j1][i];
                        i+=lcpe[j1][i];
                }
                if (fl==i) {cout<<"-1\n"; return 0;}
        }
        cout<<tot<<"\n";
        for (int i=1; i<=tot; i++)
                cout<<ans[i][0]<<" "<<ans[i][1]<<"\n";
        return 0;
}

```



---

## 作者：RedLycoris (赞：0)

首先我们可以先贪心的想：

假设我们已经匹配到了 $t$ 串的第 $i$ 位，那么有一个结论，就是如果 $t$ 的子串 $t_{i\dots j}$ 是 $s$ 的子串，而 $t_{i\dots j+1}$ 不是，那么最优方案一定是将 $t_{i\dots j}$ 整个截下来。

可以感性证明：如果不用 $t_{i\dots j}$，用 $t_{i\dots j-1}$，那么  $t_{i\dots j-1}$ 肯定是在 $s$ 中的；但如果第 $j$ 个字符加到了后面，就不能确定原来的那一段加上它后是否还在 $s$ 中，就可能不是最优了。

如果暴力地枚举复杂度会达到 $O(n^3)$；

但如果对于 $i$ 二分最远可以匹配到的地方就可以优化到 $O(n^2log_2n)$。

ps. 我写的这个字符串匹配实质上是 $O(n^2)$ 的，但由于题目的要求跑起来实质上跟 $O(n)$ 的差不多。如果总时限要稳在 $O(n^2log_2n)$ 就可以写个  kmp 处理，但会变得更复杂。

code:

---

```cpp
using namespace std;
const int mxn=2e5+5;
string a,b,ta;
int n,m;
vector<pair<int,int> >ans;
inline bool check(int bg,int ed){           //正反都匹配
	if(ed-bg+1>a.size())return 0;
	string t=b.substr(bg,ed-bg+1);
	for(int i=0;i<a.size()-t.size()+1;++i){
		bool ok=1;
		for(int j=0;j<t.size();++j){
			if(a[i+j]!=t[j]){
				ok=0;
				break;
			}
		}
		if(ok)return 1;
	}
	for(int i=0;i<ta.size()-t.size()+1;++i){
		bool ok=1;
		for(int j=0;j<t.size();++j){
			if(ta[i+j]!=t[j]){
				ok=0;
				break;
			}
		}
		if(ok)return 2;
	}
	return 0;
}
inline pair<int,int> getp(int bg,int ed){       //找到位置
	string t=b.substr(bg,ed-bg+1);
	for(int i=0;i<a.size()-t.size()+1;++i){
		bool ok=1;
		for(int j=0;j<t.size();++j){
			if(a[i+j]!=t[j]){
				ok=0;
				break;
			}
		}
		if(ok)return mp(i,i+t.size()-1);
	}
	for(int i=0;i<ta.size()-t.size()+1;++i){
		bool ok=1;
		for(int j=0;j<t.size();++j){
			if(ta[i+j]!=t[j]){
				ok=0;
				break;
			}
		}
		if(ok)return mp(a.size()-i-1,a.size()-i-t.size());
	}
}
inline string E(int bg,int ed){
	return b.substr(bg,ed-bg+1);
}
inline void solve(){
	cin>>a>>b;ta=a;reverse(ta.begin(),ta.end());
	n=a.size(),m=b.size();
	int b=0;
	for(;b<m;++b){    //b是当前处理到的字符串的开头位置
		int l=b,r=m,md;
		for(;l<r-1;){   //二分
			md=l+r>>1;
			if(check(b,md))l=md;
			else r=md;
		}
		if(l==b and !check(b,l)){  //可能是无法匹配
			cout<<"-1\n";
			return;
		}
		if(check(b,l)==1)ans.push_back(getp(b,l));  //贪心过头了，最后一小截没法匹配，与上一个串合并
		b=l;
	}
	cout<<ans.size()<<'\n';
	for(int i=0;i<ans.size();++i)cout<<ans[i].first+1<<' '<<ans[i].second+1<<'\n';
	return;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;//cin>>T;
	for(;T--;)solve();
}
```

---

