# [ARC191A] Replace Digits

## 题目描述

给出长度为 $ N $ 的字符串 $ S $ 和长度为 $ M $ 的字符串 $ T $。$ S $ 和 $ T $ 都由 `1` 到 `9` 的数字组成。

您将按照 $ k = 1,2, \dots ,M $ 的顺序执行以下操作。
* 选择满足 $ 1 \le i \le N $ 的整数 $ i $。然后用 $ T $ 的第 $ k $ 个字母替换 $ S $ 的第 $ i $ 个字母。

求 $ M $ 次操作结束后的字符串 $ S $ 作为整数的最大值。

## 说明/提示

#### 制约

- $ 1\le\ N,M\le\ 10^6 $
- $ N,M $ 是整数
- $ S $ 是长度 $ N $ 的字符串，由 `1` 到 `9` 的数字组成。
- $ T $ 是长度为 $ M $ 的字符串，由 `1` 到 `9` 的数字组成。


以下操作方法是最佳的。
- 当 $k = 1$ 时，选择 $i = 3$。这时$S = $ `193`。
- 当 $k = 2$ 时，选择 $i = 1$。这时$S = $ `293`。
- 当 $k = 3$ 时，选择 $i = 1$。这时$S = $ `593`。

在这种情况下，$ S $ 作为整数的值是 $ 593 $，这是最大值。

## 样例 #1

### 输入

```
3 3
191
325```

### 输出

```
593```

## 样例 #2

### 输入

```
3 9
191
998244353```

### 输出

```
993```

## 样例 #3

### 输入

```
11 13
31415926535
2718281828459```

### 输出

```
98888976555```

# 题解

## 作者：ARIS2_0 (赞：3)

又是一场 ARC，继上次 [ARC189 0A](https://www.luogu.com.cn/article/5rmvavbt) 的惨状，小 S 决定，要再次找回属于自己的荣誉。

开赛了，读题后，有一个还算好想的结论：如果 $m$ 个数中有些可以扔掉而不用全部覆盖，是可以用贪心去做的，即从小到大对于每一个 $i$，看是否有 $a_i$ 不小于（注意不是大于）当前 $b$ 中的最大值，如果是，这一位就选 $a_i$，否则选 $b$ 中的最大值，然后将这个最大值去掉。

注意下文中的 $a$ 皆为**使用贪心策略覆盖后的 $a$**。

不久，小 S 又意识到了一个重要结论：

- 对于贪心地覆盖，最后如果正确答案与贪心出来的答案不一样，肯定只有 $b_m$ 的值会影响答案。因为答案不一样的话，无非就是覆盖的时候没有用到 $b_m$，导致 $b_m$ 要强制覆盖在一个数上。而对于其他没有覆盖到的数，它们都可以覆盖在 $b_m$ 要覆盖的地方，这样它们就没有影响了。

小 S 想：如果 $b_m$ 在贪心覆盖的时候有用到，那直接输出 $a$ 即可；如果 $b_m$ 覆盖的时候没有用到，那 $b_m$ 肯定是不大于 $a$ 中所有其他数的。也就是说，我们要找到一个 $a$ 上的数位，使得用 $b_m$ 覆盖这个数位之后，$a$ 减少的大小最小。

显然，$a$ 上如果有 $i$ 满足 $a_i=b_m$，直接覆盖即可；否则，$b_m$ 覆盖在 $a_n$ 上一定是最优的。

做法直接按上述过程模拟即可。

于是小 S 愉快地以两发罚时通过了此题，真是与 ARC189B 的 -10 截然不同的结局啊。

也许，这就是小 S 每天殷切地对着卫星许愿的原因吧。

**S.A.T.E.L.L.I.T.E.**

### Code

```cpp
#include<algorithm>
#include<bitset>
#include<deque>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector> 
#include<chrono>
#include<random>
#include<tuple>
#include<unordered_map>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"\n"
const int inf=1e16,maxn=1e6+10;
int a[maxn],ans[maxn],cnt[10];
struct node{int id,v;}b[maxn];
bool vis[maxn];
bool cmpv(node a,node b){return a.v>b.v;}
bool cmpid(node a,node b){return a.id<b.id;}
int read(){
    char c;cin>>c;
    return c-'0';
}
signed main(){
    //freopen("data.in","r",stdin);
    //freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=m;i++)b[i].id=i,b[i].v=read();
    sort(b+1,b+m+1,cmpv);
    int tot=1;
    for(int i=1;i<=n;i++){
        if(a[i]>=b[tot].v or tot==m+1)ans[i]=a[i],vis[i]=1;
        else{
            ans[i]=b[tot].v;
            cnt[b[tot].v]++;
            tot++;
        }
    }
    sort(b+1,b+m+1,cmpid);
    bool g=cnt[b[m].v];
    for(int i=1;i<=n;i++){
        if(vis[i] and a[i]==b[m].v){
            g=1;break;
        }
    }
    if(!g)ans[n]=b[m].v;
    for(int i=1;i<=n;i++)cout<<ans[i];
    cout<<"\n";
	return 0;
}
/*
clang++ -std=c++14 -Wall -Wextra -Wshadow -Wconversion -Wl,-stack_size -Wl,512000000
*/
```

### 后记

[小 S 的 ARC191 参赛记-2（即 ARC191B 题解）](https://www.luogu.com.cn/article/yyv8znp9)

---

## 作者：__little__Cabbage__ (赞：3)

注意到题目中说 $t$ 的每一位都必须操作，所以直接贪心是不可以的，因为有的位在操作的时候可能会将前面已确定的顶掉。

但是因为要求「字典序最大」，所以操作后 $s$ 前面的位数越大越好，可以发现 $s_1 \sim s_{n-1}$ 都是可以随便被操作的，可以直接贪心，重点在于 $s_n$ 比较不好处理。

考虑先按照直接贪心的方法跑一遍（设此时得到的字符串为 $s'$），然后再对最后一位进行调整。

我们发现，如果在 $t$ 中与 $t_m$ 相等的字符（设为 $x$）已经经过了操作，那么答案就是 $s'$，考虑操作 $t_m$ 的时候选择被 $x$ 替换的字符即可。

反之，就很显然了，一定找不到一种方法避免 $t_m$ 替换掉 $s'$ 中的某个字符，于是选择 $s'_n$ 来被替换即可。

---

## 作者：chenxi2009 (赞：2)

## 思路
数码 $T_M$ 必须出现在答案中，$T_{1\cdots M-1}$ 可以自由选择替换或不替换（不替换等价于放在下一个数码替换的位置，然后被覆盖）。

可以先排序 $T$，贪心地从左往右扫 $S$，每一次尝试用 $T$ 中当前最大的数码替换；然后再扫一遍 $S$，如果没有出现 $T_M$ 就把 $S_N$ 替换成 $T_M$。

为什么正确？因为替换相同的数码等价于不替换。

时间复杂度 $O(N+M\log M)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,it;
char s[2000000],t[2000000],c;
bool u;
int main(){
	scanf("%d%d%s%s",&n,&m,s + 1,t + 1);
	c = t[m];
	sort(t + 1,t + m + 1);
	it = m;//it 指向 t 中剩余的最大的数码
	for(int i = 1;i <= n;i ++) if(it && t[it] > s[i]) s[i] = t[it --];
	for(int i = 1;i <= n;i ++) if(s[i] == c) u = true;
	if(!u) s[n] = c;// 没有就替换最后一个
	for(int i = 1;i <= n;i ++) printf("%c",s[i]);
	return 0;
}
```

---

## 作者：tuget (赞：1)

分析交换操作可知，对于任意 $1 \le i <m$，$t_i$ 可以不出现在 $s$ 中，$t_m$ 必须出现在操作后的 $s$ 中。

考虑贪心，令 $c = t_m$，将 $t$ 降序排序，依次遍历 $s_i$，若 $s_i < t_j$，将 $s_i$ 替换为 $t_j$，$j$ 右移一位，若操作后不存在 $s_i = c$，那么令 $s_n = c$ 显然不劣。

具体来说，$c$ 不在替换后的 $s$ 中，意味着对于任意的 $s_i$，有 $s_i>c$，有要求 $s$ 字典序最大，所以替换 $s_n$ 最优。

代码：


```cpp
int n,m;
char s[maxn],t[maxn];
int main()
{
	int i,j;
	n=read(),m=read(),scanf("%s %s",s+1,t+1);
	char c=t[m];
	sort(t+1,t+m+1,[](char a,char b){return a>b;});
	for(i=j=1;i<=n;++i)
		if(j<=m&&s[i]<t[j])s[i]=t[j],++j;
	bool fl=0;
	for(i=1;i<=n;++i)if(s[i]==c)fl=1;
	if(!fl)s[n]=c;
	printf("%s",s+1);
	return 0;
}
```

---

## 作者：Ecaps (赞：0)

看到这题的第一个想法就是贪心，尽量往高位上填大的数字，具体做法是将 $T$ 中的每个数字加入一个大根堆，然后枚举 $S$ 中的每一位，如果这一位上的数字比堆顶小，则用堆顶换掉这一位，一看样例一可以过。

但发现样例二寄了，因为我们忽略了题目条件：对于每个 $k \in [1,m]$ 都要执行一次操作。这使得匹配完 $S$ 之后如果 $T$ 中还剩一些元素没有匹配，我们也必须给他们找到一个归宿。考虑之前我们规定的匹配规则，不难发现，$T$ 中剩下的元素必然不大于 $S$ 中的元素。于是我们考虑将 $T$ 中排在最后未匹配元素放进 $S$ 的个位上（因为它排在最后，**可以且必须**覆盖掉前面的元素）。

这样一折腾，我们发现，欸样例二倒是过了，但是样例一又寄了。究其原因，我们发现匹配完之后 $T$ 中还剩下 $2$ 这个未匹配元素，可我们的程序把它放在了最后的个位上，那为什么个位上应该是 $3$ 呢？因为我们可以先把 $2$ 放在 $S$ 的第一位，然后再用 $5$ 来把它替换掉，这样子 $3$ 就理所当然地填入最后一位了。汲取这次的教训，我们意识到，如果 $T$ 中的第 $k$ 位成功与 $S$ 的第 $i$ 位匹配，那么前面的第 $[1,k)$ 位全都可以先填入 $S_i$ ，再由 $T_k$ 把它们全部替换掉。

于是改进算法：新开一个标记数组 $c$ ，如果 $T_k$ 成功匹配，那么 $c_k$ 打上标记，这样就可以知道哪些剩余元素可以“躲”在 $T_k$ 下而不是填入 $S$ 的最后一位了。

一交代码，WA了？考虑当 $S_i$ 等于 $T_k$ 时，如果 $S_i$ 后面的匹配中不再用到 $T_k$ ，也就是 $T_k$ “空闲”下来时，是否也可以让 $k$ 之前的剩余元素先来 $S_i$ 这，然后再用 $T_k$ 覆盖？答案是可行的，就是对这个 $k$ 也得进行标记，但我们还得加一点细节：一个 $S_i$ 可能有多个相等的 $T_k$ 但不一定会全部遇到，这时候结合 $c$ 标记数组的性质，我们再在大根堆的元素中加入一个 $id$ 信息，大根堆不仅保证堆顶的值最大，还保证 $id$ 尽量大（因为对于多个值相同的 $T_k$ ，只对 $k_{max}$ 进行标记等同于对所有 $k$ 进行标记）。

于是这道题就做完了。

PS：赛时我一直怀疑贪心的正确性，直到过掉这道题（真的细节巨多）。如果有非贪心做法，欢迎分享。

代码如下：

```c++
#include <bits/stdc++.h>
#define MAXN 1000003
using namespace std;
int n,m;
int a[MAXN],b[MAXN];
struct NUM{
    int num;
    int id;
    bool operator<(const NUM &B)const{
        if (num==B.num) return id<B.id;
        else return num<B.num;
    }
};
bool c[MAXN];
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;i++){
        char ch; cin>>ch;
        a[i]=int(ch-'0');
    }
    for (int i=1;i<=m;i++){
        char ch; cin>>ch;
        b[i]=int(ch-'0');
    }
    priority_queue <NUM> q;
    for (int i=1;i<=m;i++) q.push((NUM){b[i],i});
    for (int i=1;i<=n;i++){
        if (q.empty()) break;
        if (q.top().num==a[i]){
            c[q.top().id]=1;
        }
        if (q.top().num>a[i]){
            c[q.top().id]=1;
            a[i]=q.top().num; q.pop();
        }
    }
    if (!q.empty()){
        int last=-1;
        for (int i=1;i<=m;i++){
            if (!c[i]) last=b[i];
            else last=-1;
        }
        if (last!=-1) a[n]=last;
    }
    for (int i=1;i<=n;i++) cout<<a[i];
    cout<<'\n';
    return 0;
}
```

---

## 作者：Milky_Cat (赞：0)

简单题，但是 vp 的时候能写 $20$ 多分钟，劣势在我。

很容易就能想到，大的数应该放高位，但是由于必须放，有多的怎么办？

注意到最后一个数可以覆盖掉前面多余的数，所以只需要考虑最后一个数。

+ 如果最后一个数需要用来替换某一位，前面多余的数就拿来覆盖这一位，最后用最后一个数来填掉。

+ 否则肯定放末位，这样最优。

然后进行一个分类讨论。

边界情况：

+ 最后一位可以拿来覆盖一个相等的数，这样可以不用改个位。
+ 如果数本来就不够放，那就不特判最后一位。

具体见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s, t;
int n, m, buk[20], pos, chk;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	cin >> s >> t;
	s = " " + s;
	t = " " + t;
	for (int i = 1; i <= m; i++){
		int vl = t[i] - '0';
		++buk[vl];
		pos = max(pos, vl);
	}
	for (int i = 1; i <= n; i++){
		int vl = s[i] - '0';
		if (pos == vl && pos == t[m] - '0')
			chk = 1;
		if (pos > vl){
			s[i] = (pos + '0');
			--buk[pos];
			if (pos == t[m] - '0')
				chk = 1;
			while (!buk[pos])
				--pos;
		}
		if (pos < 0)
			break;
	}
	if (pos < (t[m] - '0') || chk){
		for (int i = 1; i <= n; i++)
			cout << s[i];
	}else{
		for (int i = 1; i < n; i++)
			cout << s[i];
		cout << t[m];
	}
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：0)

令答案序列为 $ans$。
可以得到的结论是：对于每个 $1\leq i< m$，$t_i$ 能被 $t_{i+1}$ 替换。也就是说，$T$ 中只有 $t_m$ 是一定在 $ans$ 里的。（其他都可能被后来的替换） 

那么我们考虑贪心。（需先将 $T$ 降序排序）

令 $T$ 中最大的数为 $mx$，当前指针为 $p,q$（分别对应 $S$ 和 $T$）。
对于一般情况：

- 如果 $s_{p}\geq t_{q}$，不替换，将 $p$ 往后移 $1$ 位。
- 否则替换，$ans_{p}=t_{q}$，并将 $p,q$ 都往后移 $1$ 位。

对于特殊情况：

如果没有 $t_m$，说明对于每个 $1\leq i\leq \min(n,m)$，都有 $s_i\geq t_m$。题目要求字典序最大，那么对第 $n$ 位进行修改显然更优（影响最小）。

## Code

[Link](https://atcoder.jp/contests/arc191/submissions/62402938)

---

## 作者：wfc284 (赞：0)

提供一种非常丑陋的写法。

有一个贪心策略就是，我们从 $T$ 中从数字 $9$ 到 $1$ 依次考虑每个数该替换哪些数。比如 $T$ 里面可能有一堆 $9$，我们考虑这些 $9$ 分别应该替换到哪。  
具体地，我们从 $9$ 到 $1$ 枚举 $x$，用一个指针 $p$ 指向【当前（即经过一些替换之后的）$S$ 中最前面的，且**严格小于**当前处理到的数 $x$】的位置，显然 $p$ 是不降的。能替换就替换（高位越大越好）。  
当 $p$ 指向 $N+1$ 时，跳出循环。  

我们现在处理了 $T$ 中一些数的替换，现在还剩一些数让我们掉贡献（因为我们并不是按照下标顺序来操作的）。  
我们发现，如果 $T$ 中一个数当前并没有替换进 $S$，而它后面有数替换进了 $S$，这个数就不用管了。  
也就是说，我们只需要管极大未处理后缀。如果为空，就不用管了，直接输出答案。  
这个后缀的数是会减少我们的答案的。

一个想法是，直接将这个后缀的尾字符替换到 $S$ 的尾字符。这样是错的。因为这个后缀中，可能有某些字符在 $S$ 中有同样字符。我们把它替换到 $S$ 中的同样字符，显然不会掉贡献。尾字符可能不是让我们掉贡献的那个。    

我们需要判断 $T$ 中最后一个字符有没有在【现在的】$S$ 中出现。没出现就要将 $S$ 的尾字符改成 $T$ 的尾字符，否则什么都不做。  
其他字符都不用管了，因为刚刚一次操作后，其他字符的后面均有字符被操作，可以被覆盖掉。

于是就做完了，时间复杂度 $O(n)$，不带值域。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)
//#define multi_cases 1

namespace Traveller {
	const int N = 1e6+2;
	
	int n, m;
	char s[N], t[N];
	
	int a[N], b[N];
	vector<int> v[10];
	int w[10];
	
	void main() {
		scanf("%d%d%s%s", &n, &m, s+1, t+1);
		for(int i = 1; i <= n; ++i) a[i] = s[i] - 48;
		for(int i = 1; i <= m; ++i) b[i] = t[i] - 48;
		
		for(int i = m; i >= 1; --i) v[b[i]].push_back(i);
		int last = 1;
		for(int x = 9, p = 1; x >= 1; --x) {
			for(int i : v[x]) {
				while(p <= n && a[p] >= x) ++p;
				if(p > n) break;
				a[p] = x, last = max(last, i+1);
			}
			if(p > n) break;
		}
		for(int i = 1; i <= n; ++i) w[a[i]] = 1;
		if(w[b[m]] == 0) a[n] = b[m];
		for(int i = 1; i <= n; ++i) printf("%d", a[i]);
	}
}

signed main() {
#ifdef filename
	FileOperations();
#endif
	
	signed _ = 1;
#ifdef multi_cases
	scanf("%d", &_);
#endif
	while(_--) Traveller::main();
	return 0;
}
```

---

