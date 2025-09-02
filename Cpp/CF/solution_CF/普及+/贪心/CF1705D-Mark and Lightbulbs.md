# Mark and Lightbulbs

## 题目描述

Mark has just purchased a rack of $ n $ lightbulbs. The state of the lightbulbs can be described with binary string $ s = s_1s_2\dots s_n $ , where $ s_i=\texttt{1} $ means that the $ i $ -th lightbulb is turned on, while $ s_i=\texttt{0} $ means that the $ i $ -th lightbulb is turned off.

Unfortunately, the lightbulbs are broken, and the only operation he can perform to change the state of the lightbulbs is the following:

- Select an index $ i $ from $ 2,3,\dots,n-1 $ such that $ s_{i-1}\ne s_{i+1} $ .
- Toggle $ s_i $ . Namely, if $ s_i $ is $ \texttt{0} $ , set $ s_i $ to $ \texttt{1} $ or vice versa.

Mark wants the state of the lightbulbs to be another binary string $ t $ . Help Mark determine the minimum number of operations to do so.

## 说明/提示

In the first test case, one sequence of operations that achieves the minimum number of operations is the following.

- Select $ i=3 $ , changing $ \texttt{01}\color{red}{\texttt{0}}\texttt{0} $ to $ \texttt{01}\color{red}{\texttt{1}}\texttt{0} $ .
- Select $ i=2 $ , changing $ \texttt{0}\color{red}{\texttt{1}}\texttt{10} $ to $ \texttt{0}\color{red}{\texttt{0}}\texttt{10} $ .

 In the second test case, there is no sequence of operations because one cannot change the first digit or the last digit of $ s $ .In the third test case, even though the first digits of $ s $ and $ t $ are the same and the last digits of $ s $ and $ t $ are the same, it can be shown that there is no sequence of operations that satisfies the condition.

In the fourth test case, one sequence that achieves the minimum number of operations is the following:

- Select $ i=3 $ , changing $ \texttt{00}\color{red}{\texttt{0}}\texttt{101} $ to $ \texttt{00}\color{red}{\texttt{1}}\texttt{101} $ .
- Select $ i=2 $ , changing $ \texttt{0}\color{red}{\texttt{0}}\texttt{1101} $ to $ \texttt{0}\color{red}{\texttt{1}}\texttt{1101} $ .
- Select $ i=4 $ , changing $ \texttt{011}\color{red}{\texttt{1}}\texttt{01} $ to $ \texttt{011}\color{red}{\texttt{0}}\texttt{01} $ .
- Select $ i=5 $ , changing $ \texttt{0110}\color{red}{\texttt{0}}\texttt{1} $ to $ \texttt{0110}\color{red}{\texttt{1}}\texttt{1} $ .
- Select $ i=3 $ , changing $ \texttt{01}\color{red}{\texttt{1}}\texttt{011} $ to $ \texttt{01}\color{red}{\texttt{0}}\texttt{011} $ .

## 样例 #1

### 输入

```
4
4
0100
0010
4
1010
0100
5
01001
00011
6
000101
010011```

### 输出

```
2
-1
-1
5```

# 题解

## 作者：happy_dengziyue (赞：11)

### 1 视频题解

![](bilibili:BV1ud4y1Q7f5)

### 2 思路

我们可以发现，设刚开始字符串为 $a$，结束时字符串为 $b$，如果 $a[1]\not=b[1]$ 或 $a[n]\not=b[n]$，那么就一定无解。

否则我们可以发现，操作本质上是将一个全为 `1` 的极大子串增长或缩短，但是两个子串不能合并，当然也不能调换位置顺序。

所以，我们分别求出 $a$ 和 $b$ 中的全为 `1` 的极大子串的数量即可，如果它们不相等就无解。

否则，对于两边对应的极大子串，分别求出左端点和右端点的移动的距离即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 200000
int t;
int n;
char a[max_n+20];
char b[max_n+20];
int al[max_n+2];
int ar[max_n+2];
int ai=0;
int bl[max_n+2];
int br[max_n+2];
int bi=0;
long long ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1705D_1.in","r",stdin);
	freopen("CF1705D_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%s%s",&n,a+1,b+1);
		if(a[1]!=b[1]||a[n]!=b[n]){
			printf("-1\n");
			continue;
		}
		ai=bi=0;
		for(int l=1,r;l<=n;++l){
			if(a[l]=='0')continue;
			for(r=l;r+1<=n&&a[r+1]=='1';++r);
			++ai;
			al[ai]=l;
			ar[ai]=r;
			l=r;
		}
		for(int l=1,r;l<=n;++l){
			if(b[l]=='0')continue;
			for(r=l;r+1<=n&&b[r+1]=='1';++r);
			++bi;
			bl[bi]=l;
			br[bi]=r;
			l=r;
		}
		if(ai!=bi){
			printf("-1\n");
			continue;
		}
		ans=0;
		for(int i=1;i<=ai;++i)ans+=abs(al[i]-bl[i])+abs(ar[i]-br[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80111624)

By **dengziyue**

---

## 作者：jiangtaizhe001 (赞：9)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16490548.html)

[题目传送门](http://codeforces.com/problemset/problem/1705/D)
### 题目大意
给定一个长度为 $n$ 的 01 字符串 $s$，现在你可以选定一个 $i\in(1,n)$ 满足 $s_{i-1}\not=s_{i+1}$，然后把 $s_i$ 变成 $s_i\oplus1$。现在你需要把 $s$ 变成另一个给定的字符串 $t$。求最小的操作数。  
$n\le 2\times 10^5$  
### 题目解析
我们考虑这个操作究竟能干什么。  
我们可以发现，进行一次操作可以 **使 01 分界线移动** $1$，不会改变 01 的段数。  
所以如果 $s$ 和 $t$ 的 01 段数不同，或者 $s_1,t_1$、$s_n,t_n$ 不同，就无解。  

可以证明存在一种方案使得移动分界线的时候仅仅往同一方向移动，所以就不会有额外的操作出现。  
所以就只需要扫一次得到 $s,t$ 所有的 01 分界线，然后答案就是这些对应两个分界线的差的绝对值的和。  

代码是非常简短的
```cpp
int n; ll ans; char s1[maxn],s2[maxn];
int p1[maxn],p2[maxn],cnt1,cnt2;
void work(){
	n=read(); scanf("%s%s",s1+1,s2+1); if(s1[1]!=s2[1]||s1[n]!=s2[n]){ puts("-1"); return; }
	int i; cnt1=cnt2=0; ans=0;
	for(i=2;i<=n;i++) if(s1[i]!=s1[i-1]) p1[++cnt1]=i;
	for(i=2;i<=n;i++) if(s2[i]!=s2[i-1]) p2[++cnt2]=i;
	if(cnt1!=cnt2){ puts("-1"); return; }
	for(i=1;i<=cnt1;i++) ans+=mabs(p1[i]-p2[i]);
	print(ans),pc('\n');
}
```

---

## 作者：Anguei (赞：2)

## 题意
给定两个长度为 $n$ 的 0-1 串 $s$ 和 $t$，每次操作可以：选择 $s$ 在 $[2, n-1]$ 区间内的一个字符，若 $s_{i-1} \not= s_{i+1}$ 则将 $s_i$ 取反。

问，能否通过一定次数的操作，把字符串 $s$ 转换成 $t$？如果能，求出最小操作次数。

## 分析

性质观察题。

首先，由于每次操作仅能选择 $[2, n-1]$ 区间内的字符，所以若 $s$ 和 $t$ 的首尾字符不同，一定不可能。

然后考虑哪些位置可以进行操作。
1. 由于能操作的位置需要满足 $s_{i-1} \not= s_{i+1}$，故对于任意一段连续的 0 或 1，只有其两端可以被进行操作（因为中间部分不能满足上述条件）。
2. 特殊地，若两段连续的 1 之间，仅有一个 0 隔开，这个孤立存在的 0 也是不能被操作的。

接着考虑操作之后会对 $s$ 串造成什么变化？
1. 由上述限制 1 得知，由于每次操作的都是端点，所以每段连续的 1 都可以在端点位置变成 0（缩短了），或者是对旁边 0 的端点进行操作，这相当于对 1 的延长。即：**每次操作之后，一段连续的 0 或 1，会被压缩或者拉长**。且：**每次压缩或拉长的距离等于操作的次数**。
2. 由上述限制 2 无论如何操作，两段被分隔开的连续的 1，无论如何都不可能连接到一起。即：**操作不会改变连续的 0 或 1 的串的数量**。

至此，此题做法呼之欲出：
1. 判断 $s$ 和 $t$ 的首尾字符是否相同；
2. 判断 $s$ 和 $t$ 中连续的 1 的子串个数是否相同；
3. 求出 $s$ 和 $t$ 中每段连续 1 的子串被压缩或拉长的距离总和，这个距离和就是最终答案。

时间复杂度 $\mathcal{O}(n)$。

当然，无论分析连续 0 还是连续 1，都是同样的。

## 代码

```cpp
void solution() {
  int n;
  read(n);
  std::string s, t;
  std::cin >> s >> t;
  if (s.front() != t.front()) return print(-1);
  if (s.back() != t.back()) return print(-1);
  s = " " + s;
  t = " " + t;
  std::vector<pii> segS, segT;
  // 处理 s 串当中连续 1 的子串的首尾坐标
  for (int i = 1; i <= n; ++i) {
    if (s[i] == '0') continue;
    int j = i;
    while (j + 1 <= n && s[j + 1] == '1') ++j;
    segS.emplace_back(i, j);
    i = j;
  }
  // 处理 t 串当中连续 1 的子串的首尾坐标
  for (int i = 1; i <= n; ++i) {
    if (t[i] == '0') continue;
    int j = i;
    while (j + 1 <= n && t[j + 1] == '1') ++j;
    segT.emplace_back(i, j);
    i = j;
  }
  if (segT.size() != segS.size()) return print(-1);
  ll ans = 0;
  int m = int(segS.size());
  // 对压缩或伸长的总距离求和，就是最终答案
  for (int i = 0; i < m; ++i) ans += std::abs(segS[i].first - segT[i].first);
  for (int i = 0; i < m; ++i) ans += std::abs(segS[i].second - segT[i].second);
  print(ans);
}
```


---

## 作者：Noby_Glds (赞：1)

思路比较清奇，希望大家能跟上。
### 思路：
这题的题意我们可以理解成：对于一个连续 $1$ 段，我们可以对它进行扩展和收缩。

但前提是，我们不能让一个 $1$ 段消失，或者让一个 $1$ 段和另一个 $1$ 段合并。

为什么不能合并，如图：
```latex
1110111
```
可以发现，中间的 $0$ 的两边全都是 $1$，无法修改。

所以，我们发现：

虽然我们可以改变 $1$ 段的位置和长度，**但我们不能改变原字符串中 $1$ 段的个数**。

所以我们可以统计原字符串和目标字符串中 $1$ 段的个数，如果不一样说明无解。

另外题目所述，我们不可以修改第一个位置和最后一个位置的数字。

这两个位置的原数和目标如果不一样，也是无解。

统计答案比较简单，先记录原字符串和目标字符串中所有的 $1$ 段的起始位置和末尾位置。

再对于每个**对应**的原 $1$ 段和目标 $1$ 段，计算它们起始位置和末尾位置的绝对值，加入答案。
### 代码：
```cpp
#include<bits/stdc++.h>
#define N 1000010
#define int long long
using namespace std;
int t,n,a[N],b[N],l[N],r[N],l2[N],r2[N],sum,sum2;
char p;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		sum=sum2=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>p;
			a[i]=p-'0';
			if(a[i]!=a[i-1]&&a[i]) sum++,l[sum]=i;
			if(a[i]!=a[i-1]&&!a[i]) r[sum]=i-1;
		}
		if(a[n]) r[sum]=n;
		for(int i=1;i<=n;i++){
			cin>>p;
			b[i]=p-'0';
			if(b[i]!=b[i-1]&&b[i]) sum2++,l2[sum2]=i;
			if(b[i]!=b[i-1]&&!b[i]) r2[sum2]=i-1;
		}
		if(b[n]) r2[sum2]=n; 
		if(sum!=sum2||a[1]!=b[1]||a[n]!=b[n]){
			cout<<"-1\n";
			continue; 
		}
		int ans=0;
		for(int i=1;i<=sum;i++) ans+=abs(l[i]-l2[i])+abs(r[i]-r2[i]);
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：D2T1 (赞：0)

# 题解 CF1705D

[Luogu](https://www.luogu.com.cn/problem/CF1705D) [CodeForces](https://codeforces.com/problemset/problem/1705/D)

考虑一个连续极长的 $\texttt1$ 段，显然在这一段中，只有两端的 $\texttt1$ 可以改变，中间的 $\texttt1$ 全部都不能改变，所以可以得出：对一个连续极长的 $\texttt1$ 段，不能将它拆分长两个连续极长的 $\texttt1$ 段。

同理，对于两个中间只隔有 $\texttt0$ 的连续极长的 $\texttt1$ 段，也不能合并。如下所示：

$$\texttt{...11111110111111...}$$

这里的 $\texttt0$ 怎么样都不能消除。

所以得出结论：若一个串 $s$ 能变成串 $t$，**二串中必然要包含相同数目的连续极长 $\texttt1$ 段**。

当然，还要再判断一下 $s_1,s_n,t_1,t_n$。

------------

现在来考虑步数问题。一次操作现在看起来是什么：令一个连续极长 $\texttt1$ 段向任意一侧扩张一格，或从任意一侧缩小一格。

把 $s$ 和 $t$ 中每个连续极长 $\texttt1$ 段从左往右一一对应。那么我们的目标就是把 $s$ 中每个连续极长 $\texttt1$ 段经过若干次扩张、缩小从而变成 $t$ 中所对应的那一段。答案很显然：设对应段在 $s$ 中下标为 $[sl,sr]$，在 $t$ 中下标为 $[tl,tr]$，答案即累加上 $\operatorname{abs}(sl-tl)+\operatorname{abs}(sr-tr)$。

```cpp
//CF1705D
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int You_AK_IOI, n, vis[N];
char s[N], t[N];
int l[N], r[N], tl[N], tr[N];

int main(){
	scanf("%d", &You_AK_IOI);
	while(You_AK_IOI--){
		scanf("%d", &n);
		scanf("%s", s+1);
		scanf("%s", t+1);
		long long ans = 0;
		int cnt1 = 0, cnt2 = 0;
		for(int i = 1; i <= n+1; ++ i){
			if(s[i] == '1' && s[i-1] != '1'){
				++ cnt1;
				l[cnt1] = i;
			}
			if(s[i] != '1' && s[i-1] == '1'){
				r[cnt1] = i-1;
			}
			if(t[i] == '1' && t[i-1] != '1'){
				++ cnt2;
				tl[cnt2] = i;
			}
			if(t[i] != '1' && t[i-1] == '1'){
				tr[cnt2] = i-1;
			}
		}
		if(s[1] != t[1] || s[n] != t[n] || cnt1 != cnt2){
			puts("-1");
			continue;
		}
		for(int i = 1; i <= cnt1; ++ i){
			int a = l[i], b = r[i], c = tl[i], d = tr[i];
			ans += abs(a-c) + abs(b-d);
			l[i] = r[i] = tl[i] = tr[i] = 0;
		}
		printf("%lld\n", ans);
		
	}
	return 0;
}
```

---

## 作者：codemap (赞：0)

## 题目分析
通过分析题目中所述的操作，我们可以得出几个结论：

1. 我们称原序列连续的 $0$ 或连续的 $1$ 为一段，那么可以发现，题目中的操作本质上是在一段的一端变化一个数字。

2. 由于操作的前提是两端数字不同，段的数量和排列都是不可被改变的，可改变的只有它们的位置。

由此，我们可以得出做法：记录两个字符串的段数和每一段的左节点，如段数不一样或开头结尾不一样，则无法变换，否则，因为每次移动可看成移动一段的左节点，所以答案即为左节点位置差之和。

最后注意要开 long long，即可。
## 代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
long long l1[200001],l2[200001];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long t,n,s1,s2,ans,i;
    string a,b;
    cin>>t;
    while(t--)
    {
        cin>>n>>a>>b;
        if(a[0]!=b[0]||a[n-1]!=b[n-1])
        {
            //开头结尾不一样则不行
            cout<<"-1\n";
            continue;
        }
        s1=1;
        s2=1;
        l1[1]=0;
        l2[1]=0;
        for(i=1;i<n;i++)
        {
            if(a[i]!=a[i-1])
            {
                //新的一段
                s1++;
                l1[s1]=i;
            }
            if(b[i]!=b[i-1])
            {
                s2++;
                l2[s2]=i;
            }
        }
        if(s1!=s2)
        {
            //如果段数不一样则不行
            cout<<"-1\n";
            continue;
        }
        ans=0;
        for(i=2;i<=s1;i++)
            ans+=abs(l1[i]-l2[i]);
        cout<<ans<<"\n";
    }
    return 0;
}
```


---

## 作者：MortisM (赞：0)

# 前言
[传送门](https://codeforces.com/contest/1705/problem/D)

这道题是个思维题，想起来挺妙的，但是比较不容易想到。这种题还是要多观察，最好是手推一些范围合适的样例，观察分析性质。这类题我还是做得不太好，以后要多练习。

感谢这位大佬的帮助：
![](https://cdn.luogu.com.cn/upload/image_hosting/mxxdnu7k.png)
# 题意
有两个长度为 $n$ 的 01 串 $s$ 和 $t$。你可以在 $s$ 上做一些操作：

- 在 $i=2\cdots n-1$ 中选一个，满足 $s_{i-1}\neq s_{i+1}$。
- 反转 $s_i$，即若 $s_i=\text{0}$，则令 $s_i=\text{1}$，反之同理。

想将 $s$ 通过这些操作变成 $t$，问是否可能。若可能要求出最小的移动步数。
# 思路
通过观察发现，$s$ 中 $s_i\neq s_{i+1}$ 的个数与 $t$ 中 $t_i\neq t_{i+1}$ 的个数相同。

这是为什么呢？因为无论是 `001` 变成 `011` 还是 `100` 变成 `110`，它们的 `01` 个数加上 `10` 个数都是相等的。

知道了这个以后就可以维护所有 $s_i\neq s_{i+1}$ 的 $i$ 为 $x_1,\cdots,x_k$。同理，所有 $t_i\neq t_{i+1}$ 的 $i$ 为 $y_1,\cdots,y_k$。

那么显然答案为 $\sum\limits_{i=1}^k|x_i-y_i|$。

时间复杂度 $O(N)$。
# 程序
[完整程序](https://www.luogu.com.cn/paste/y55jieru)

核心部分如下：

```cpp
void solve(){
	scanf("%d%s%s",&n,s+1,t+1);
	if(s[1]!=t[1]||s[n]!=t[n]){
		puts("-1");
		return;
	}
	v1.clear();
	v2.clear();
	for(int i=1;i<n;i++){
		if(s[i]!=s[i+1]){
			v1.pb(i); 
		}
		if(t[i]!=t[i+1]){
			v2.pb(i);
		}
	}
	if(sz(v1)!=sz(v2)){
		puts("-1");
		return;
	}
	ll ans=0;
	for(int i=0;i<sz(v1);i++){
		ans+=1ll*abs(v1[i]-v2[i]);
	}
	printf("%lld\n",ans);
}
```

---

