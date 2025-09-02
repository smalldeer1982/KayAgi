# [ARC132D] Between Two Binary Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc132/tasks/arc132_d

文字列の **美しさ** を、その文字列のなかで同じ $ 2 $ 文字が隣り合っている位置の個数として定義します。 例えば、`00011` の美しさは $ 3 $ で、`10101` の美しさは $ 0 $ です。

$ S_{n,m} $ を $ n $ 文字の `0` と $ m $ 文字の `1` からなる長さ $ n+m $ の文字列全体の集合とします。

$ s_1,s_2\ \in\ S_{n,m} $ について、$ s_1,s_2 $ の **距離** $ d(s_1,s_2) $ を 「隣り合った $ 2 $ 文字を入れ替える操作によって文字列 $ s_1 $ を文字列 $ s_2 $ に並び替えるのに必要な最小の操作回数」 と定義します。

また、$ s_1,s_2,s_3\in\ S_{n,m} $ について、$ s_2 $ が $ s_1 $ と $ s_3 $ の **間にある** ことを、$ d(s_1,s_3)=d(s_1,s_2)+d(s_2,s_3) $ で定義します。

$ s,t\in\ S_{n,m} $ が与えられるので、$ s $ と $ t $ の間にある文字列の美しさの最大値を出力してください。

## 说明/提示

### 制約

- $ 2\ \le\ n\ +\ m\le\ 3\times\ 10^5 $
- $ 0\ \le\ n,m $
- $ s,t $ は $ n $ 文字の `0` と $ m $ 文字の `1` からなる長さ $ n+m $ の文字列

### Sample Explanation 1

`10110` と `01101` の距離は $ 2 $ で、これらの間にある文字列は、`10110`, `01110`, `01101`, `10101` です。 それぞれの美しさは $ 1,2,1,0 $ であるため、答えは $ 2 $ です。

### Sample Explanation 2

`000011` と `110000` の距離は $ 8 $ です。 美しさが最大になる文字列は `000011` と `110000` で、答えは $ 4 $ です。

## 样例 #1

### 输入

```
2 3
10110
01101```

### 输出

```
2```

## 样例 #2

### 输入

```
4 2
000011
110000```

### 输出

```
4```

## 样例 #3

### 输入

```
12 26
01110111101110111101001101111010110110
10011110111011011001111011111101001110```

### 输出

```
22```

# 题解

## 作者：cjh20090318 (赞：7)

## 题意

参见[题意翻译](https://www.luogu.com.cn/problem/AT_arc132_d)。

## 分析

对于在 $s_1$ 和 $s_2$ 之间的字符串 $s_3$，那么 $s_3$ 的第 $i$ 个 $1$ 的位置一定在 $s_1$ 和 $s_2$ 的第 $i$ 个 $1$ 的位置之间。

为了使答案最大，就要尽量让相同的数字挨在一起。

很容易证明每一个 $1$ 的可选区间一定不会存在包含关系，所以依次考虑每一个区间，将 $1$ 放在区间尽量靠后的位置。

有一种特殊的情况：

```
111100
011110
```

根据刚刚的贪心策略得到的答案 `011110` 是不优的，因为将两个 $0$ 分开了，所以我们再尝试一种情况，将第一个区间放在最靠前的位置。

两种情况答案取最大值即可，时间复杂度 $O(n+m)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 300003
using namespace std;
int n,m,e;
char s[MAXN],t[MAXN];
struct SEG{
	int l,r;
	bool operator < (const SEG&B)const{return l<B.l;}
}a[MAXN];
bool p[MAXN];
int f(const bool op){
	memset(p+1,0,e);
	int w=0,ret=0;
	for(int i=1;i<=m;i++,++w) p[w=a[i].l>w?op&&i==1?a[i].l:a[i].r:w]=1;//位置不在当前区间内，就重新选择放在右端点。
	for(int i=2;i<=e;i++) ret+=p[i]==p[i-1];//统计答案。
	return ret;
}
int main(){
	scanf("%d%d %s %s",&n,&m,s+1,t+1),e=n+m;
	int t1=0,t2=0;
	for(int i=1;i<=e;i++){
		if(s[i]=='1') a[++t1].l=i;//统计 1 出现的位置。
		if(t[i]=='1') a[++t2].r=i;
	}
	for(int i=1;i<=m;i++)if(a[i].l>a[i].r) swap(a[i].l,a[i].r);
	printf("%d\n",max(f(0),f(1)));//求两种答案最大值。
	return 0;
}
```

---

## 作者：iiiiiyang (赞：4)

[更不好的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/16919689.html)

[题目链接](https://www.luogu.com.cn/problem/AT_arc132_d)

首先我们记要寻找的“位于 $s$ 和 $t$ 之间的字符串”为 $c$ 串，$s$ 串中的第 $i$ 个 $1$ 位置为 $cnts_i$，$t$ 串中的第 $i$ 个 $1$ 位置为 $cntt_i$，$c$ 串中的第 $i$ 个 $1$ 位置为 $cntc_i$，根据定义这个 $c$ 串需要满足 $\min(cnts_i,cntt_i) \le cntc_i \le \max(cnts_i,cntt_i)$。

容易想到我们要使答案尽可能大，就要尽可能多的让相同的数字凑在一起。考虑贪心，将 $1$ 插入 $0$ 中，由于 $c$ 串所要满足的性质定下了每一个 $1$ 可以放置的区间，所以我们应该将每一段的 $1$ 尽可能向后放，然后检查后面的每一段能不能接着放 $1$，如果可以放则放，不可以则重新另起一段，再从这一段的最后面开始放 $1$。

满心欢喜的交上去，你会发现红了一片，这是为什么捏？

考虑这么一组数据：

```
1 1 1 1 0 0
0 1 1 1 1 0
```

我们如果按照上面的贪心策略，会得到答案 `0 1 1 1 1 0`，但显然 `1 1 1 1 0 0` 更优。这是因为如果我们在第一位上可以放 $1$，并且有一个串的前面有一部分 $0$，第一段 $1$ 的后面又有一部分 $0$ 时，我们把 $1$ 往后放的策略就会使两段 $0$ 分开，这时就应该把第一段 $1$ 放在最前头，使得保证在同等贡献数量的 $1$ 的情况下，$0$ 的贡献也尽可能大。也非常好处理，让第一个 $1$ 在最开头就好了，剩下的还上面的贪心一致。

实现大概就是单指针，只需要枚举放 $1$ 的位置，遍历一遍存储答案的数组统计即可，时间复杂度 $O(n)$。

$Code$
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

namespace LgxTpre
{
    static const int MAX=500010;
    static const int INF=20070707070707;

    int n,m,len;
    char a[MAX],b[MAX];
    int posa[MAX],cnta;
    int posb[MAX],cntb;
    int L[MAX],R[MAX];
    int num[MAX],ans;

    inline int getans(int begin)
    {
        int sum=0;
        memset(num,0,sizeof num);
        num[begin]=1;
        for(int i=2,last=begin;i<=m;++i)
            if(last+1>=L[i]&&last+1<=R[i])
                ++last,num[last]=1;
            else    
                last=R[i],num[last]=1;
        for(int i=1;i<len;++i)
            if(num[i]==num[i+1])
                ++sum;
        return sum;
    }

    inline void lmy_forever()
    {
        scanf("%lld%lld",&n,&m); len=n+m;
        scanf("%s",a+1); scanf("%s",b+1);
        for(int i=1;i<=len;++i) if(a[i]=='1') posa[++cnta]=i;
        for(int i=1;i<=len;++i) if(b[i]=='1') posb[++cntb]=i;
        for(int i=1;i<=m;++i)
            L[i]=min(posa[i],posb[i]),
            R[i]=max(posa[i],posb[i]);
        ans=max(ans,getans(R[1]));
        if(L[1]==1) ans=max(ans,getans(L[1]));
        cout<<ans;
        return;
    }
}


signed main()
{
    LgxTpre::lmy_forever();
    return (0-0);
}
```

---

## 作者：EuphoricStar (赞：2)

提供一个 dp 思路。

下文设串长为 $n$，串中 $1$ 个数为 $m$。

考虑如何求 $d(s, t)$。设 $s$ 的 $1$ 位置分别为 $a_1, a_2, ..., a_m$，$t$ 的 $1$ 位置分别为 $b_1, b_2, ..., b_m$。那么 $d(s, t) = \sum\limits_{i=1}^m |a_i - b_i|$。

更进一步地，对于串 $s'$，设 $s'$ 的 $1$ 位置分别为 $c_1, c_2, ..., c_m$，那么 $\forall i \in [1, m], c_i \in [\min(a_i, b_i), \max(a_i, b_i)]$ 是 $d(s, s') = d(s', t)$ 的充要条件。设 $l_i = \min(a_i, b_i), r_i = \max(a_i, b_i)$。

考虑转化题中的 "beauty"，相当于最小化极长同字符连续段个数。

考虑 dp。设 $f_i$ 表示填完前 $i$ 个 $1$ 的最小极长连续段个数。枚举 $j$ 表示第 $j \sim i$ 个 $1$ 放一起，合法当且仅当 $l_i - r_j + 1 \le i - j + 1 \le r_i - l_j + 1$，此时有转移 $f_i = f_{j-1} + 2$，表示先加一段 $0$ 再加一段 $1$。

注意处理开头一段是 $1$ 和末尾一段是 $1$ 的情况。

感性理解，对于每个 $i$，合法的 $j$ 一定形成一个区间，因为不可能 $j_1 \sim i$ 能放一起但是 $j_2 \sim i$ 不能（$j_1 < j_2$）。可以二分得出左端点，然后使用线段树优化。可以做到 $O(n \log n)$，已经可以通过。

更进一步，发现对于每个 $i$，最左合法转移点单调不降。并且由于这个性质，$f_i$ 单调不降。可以双指针维护每个 $i$ 的最左合法转移点，然后 $O(1)$ 转移。总时间复杂度降至 $O(n)$。

[$O(n \log n)$ 的 code](https://atcoder.jp/contests/arc132/submissions/41626274)

[$O(n)$ 的 code](https://atcoder.jp/contests/arc132/submissions/41627023)

---

## 作者：happy_zero (赞：1)

首先考虑 $dis(s_1,s_2)$ 如何求。不妨只关注 $1$，那么目标就是把 $s_1$ 中的 $1$ 挪到 $s_2$ 的位置。如果两个 $1$ 移动的路径有交叉，则重叠的那段是无用的，一定不最优，所以为了不有重叠，就要将 $s_1$ 中的第 $i$ 个 $1$ 移到 $s_2$ 中第 $i$ 个 $1$ 的位置。

因此设 $s_1$ 中第 $i$ 个 $1$ 的位置为 $a_i$，$s_2$ 中第 $i$ 个 $1$ 的位置为 $b_i$，则 $dis(s_1,s_2)=\sum_{i=1}^m |a_i-b_i|$。

而对于“中间”这个限制，设 $s_3$ 中第 $i$ 个 $1$ 的位置为 $c_i$，则有：$\sum_{i=1}^m|a_i-b_i|=\sum_{i=1}^m|a_i-c_i|+|c_i-b_i|$，根据初中数学知识，当且仅当 $\forall i,min(a_i,b_i)\le c_i\le max(a_i,b_i)$ 时成立。

不难得出一个序列的美丽值其实就是序列长度减去连续 $01$ 段的数量，于是问题转化成了：将 $m$ 个 $1$ 放到 $n+m$ 个位置中，剩下填 $0$，第 $i$ 个 $1$ 必须放在 $[l_i,r_i]$ 中，最小化连续 01 段的段数。

贪心的策略是：不断放入 $1$，如果可以接上当前的连续 $1$ 段则接上，否则单独放一段。每一段在合法的范围内可以随便放，特别的，如果是头尾可以接上 $1$ 或 $n+m$ 就尽量放，这样头尾就可以减一段。

但有个小问题：若一个 $1$ 既可以接在前一段也可以接在后一段，这样是强制把它接在前面一段的，这样在第一段的时候可能会出事，因为接在前面可能会限制第一段不能放在头，例如样例 3 就是这种情况。一个解决办法是跑两遍取 $\min$，一遍正常跑，一遍强制第一个（如果可以）放在第 $1$ 个位置。

注意特判 $n=0$ 或 $m=0$ 的情况。时间复杂度 $O(n+m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int n, ts, l[N], r[N];
int cal() {
	int ans = 0, nl = 0, nr = 0, now = 0;
	for (int i = 1; i <= ts; i++) {
		if (!nl) nl = l[i], nr = r[i], now = i;
		nl = max(nl, l[i] - (i - now));
		nr = min(nr, r[i] - (i - now));
		if (i == ts || l[i + 1] - (i + 1 - now) > nr || r[i + 1] - (i + 1 - now) < nl) {
			ans++;
			if (now == 1 && nl != 1) ans++;
			if (i != ts || nr + (i - now) != n || (now == 1 && nl == 1)) ans++;
			//除掉了 n=0 的情况，如果接在前面就不能接在后面了
			nl = nr = now = 0;
		}
	}
	return ans;
}
int main() {
	int m; cin >> n >> m; n += m;
	if (n == m || !m) return cout << n - 1 << '\n', 0;
	for (int i = 1; i <= n; i++) {
		char x; cin >> x;
		if (x == '1') l[++ts] = i;
	} ts = 0;
	for (int i = 1; i <= n; i++) {
		char x; cin >> x;
		if (x == '1') r[++ts] = i;
	}
	for (int i = 1; i <= ts; i++)
		if (l[i] > r[i]) swap(l[i], r[i]);
	int ans = cal();
	if (l[1] == 1) r[1] = 1;
	ans = min(ans, cal());
	cout << n - ans << '\n';
	return 0;
}
```

---

## 作者：intel_core (赞：0)

注意到一次有用的交换一定是交换一个 0 和一个 1 。所以可以看成把一个 1 挪了一个位置。

我们把两个字符串里 1 的位置取出来，记为 $x_1,x_2,\cdots x_m$, $y_1,y_2,\cdots,y_m$。

这样满足要求的字符串只需要让第 $i$ 个 1 的位置在 $x_i$ 和 $y_i$ 之间即可。

贪心的使 1 的段数尽量少即可。从前往后扫，每次看一下能不能和当前的段拼成一个，不能就再加一段。

复杂度线性。

---

