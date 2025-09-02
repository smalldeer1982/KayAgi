# Shortest and Longest LIS

## 题目描述

给你一个有 $n(2 \le n \le 2\cdot 10^5)$ 个元素的排列 $A$ 中，每相邻两个元素的大小关系，要你构造出两组解，使得第一组解的 LIS 最短，第二组解的 LIS 最长。

## 样例 #1

### 输入

```
3
3 <<
7 >><>><
5 >>><
```

### 输出

```
1 2 3
1 2 3
5 4 3 7 2 1 6
4 3 1 7 5 2 6
4 3 2 1 5
5 4 2 1 3```

# 题解

## 作者：wucstdio (赞：31)

这道题构造方法感觉很多，我就说一说自己的吧。据我所知我的写法应该算是很简洁的。

### 题目大意

有一个 $1$ 到 $n$ 的排列，你知道所有相邻两个位置的大小关系，你需要构造出两个排列，满足第一个排列的 LIS 尽可能短，第二个排列的 LIS 尽可能长。

### 数据范围

$1\le n\le 2\times 10^5$

### 解题过程

首先考虑构造最短的 LIS。

容易发现此时答案的下界是连续相邻 `'<'` 的长度的最大值。现在我们尝试打到这个最大值。

我们可以这么构造：首先让这个排列等于 $n,n-1,n-2,\ldots,1$，然后对于一段连续的 `'<'`，我们直接把对应的位置翻转。

这样对于任意两个位置 $i<j$，除非这两个位置位于一段连续的 `'<'` 对应的区间之内，否则一定满足 $a_i>a_j$。可以发现这样构造出的 LIS 一定是最短的。

然后我们考虑构造最长的 LIS。

有了上面的思考过程，这次我们只需要让这个排列初始等于 $1,2,3,\ldots,n$，然后翻转所有连续的 `'>'` 对应的区间。这样对于任意两个位置 $i<j$，除非这两个位置位于一段连续的 `'>'` 对应的区间之内，否则一定满足 $a_i<a_j$。因此这样构造出的 LIS 一定是最长的。

时间复杂度 $O(n)$。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int t,n,p[200005];
char s[200005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%s",&n,s+1);
		for(int i=1;i<=n;i++)p[i]=n-i+1;
		for(int i=1;i<n;)
		{
			int j=i;
			while(s[j]=='<')j++;
			reverse(p+i,p+j+1);
			i=j+1;
		}
		for(int i=1;i<=n;i++)printf("%d ",p[i]);
		printf("\n");
		for(int i=1;i<=n;i++)p[i]=i;
		for(int i=1;i<n;)
		{
			int j=i;
			while(s[j]=='>')j++;
			reverse(p+i,p+j+1);
			i=j+1;
		}
		for(int i=1;i<=n;i++)printf("%d ",p[i]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：_ztyqwq (赞：4)

### Description

给定 $ n $ 和一个长度为 $ n - 1 $ 的字符串 $ s $。构造一个长度为 $ n $ 的数列 $ a $，使得

1. $ a $ 中 $ 1, 2, ..., n $ 每个数恰好出现一次（$ a $ 是 $1, 2, ..., n $ 的一个排列）

2. 若 $ s_i = \texttt{'<'} $，则 $ a_i < a_{i + 1} $；若 $ s_i = \texttt{'>'} $，则 $ a_i > a_{i + 1} $

3. $ a $ 的 `LIS`（最长上升子序列）长度 **最小** or **最大**

请构造这样的两个排列。

### Solution

不难想到，如果要求 `LIS` 长度最小，我们需要整个数列总体呈下降趋势；如果要求 `LIS` 长度最大，我们需要整个序列总体呈上升趋势。

---

不妨先看 `LIS` 长度最小的情况。我们希望构造一个数列使整体呈下降趋势。

我们发现，如果有 **连续的一段 `'<'`**，则有 **连续一串数将会构成一个上升的子数列**。我们考虑把这样的子数列称之为 “块”。块的大小可以等于 $ 1 $。

不难发现，**一个块中的最后一个数要大于下一个块中的第一个数**。（`'>'`）

~~题目中的样例略弱~~，我们不妨考虑一组新的数据：

**`9 <>>><<><`**

我们考虑让一个块中的数是一些 **连续** 的数组成的上升序列。则我们构造出来的数列会像这样：

![Min](https://cdn.luogu.com.cn/upload/image_hosting/hqknvsn1.png)

（横坐标为下标，纵坐标为该位置的数，这样的坐标图可以清晰地体现大小关系）

其中蓝色的边代表这条边的两个端点在一个块中，红色的边是连接块与块的边。容易发现蓝色的边都是上斜的，这印证了 “块中的数构成了一个上升的序列”；红色的边是下斜的，印证了 “前一个块的数大于后一个块的数”。

我们的构造方式是：从前往后依次处理每一个块，维护一个 **当前未被用过的数的最大值 `now`**，对于这个块，令它的最后一个数为 `now`，前面的数依次递减，使 **块中的数构成一个连续的上升序列**。然后修改 `now` 的值。

这样就可以得到类似上图的构造方式。

### Proof of Min LIS

不难发现，`LIS` 的长度最小值一定 $ \geqslant $ 最大的块长度，因为一个块中的数必定构成 `LIS`。

在这种构造方式下，**前面的块中的任何数必定大于后面的块中的任何数**。所以 `LIS` 不可能同时包含两个块中的数，只能在同一个块中选取。证毕。

---

接下来看 `LIS` 长度最大的情况。其实基本同理。

这次我们令连续的一段 `'>'` 为一个 “块”。与上文正好相反，这次 **一个块中的数构成一个下降的子数列**。**一个块的最后一个数小于下一个块的第一个数**。

还是考虑让一个块中的数构成连续的一串数。对于上文的那组数据，我们的构造会像这样：

![Max](https://cdn.luogu.com.cn/upload/image_hosting/zpeercdv.png)

蓝边与红边的意义与上文类似，这里不再赘述。

构造方式其实也大同小异，**维护当前未被使用过的数的最小值 `now`**，对于当前块，令它的最后一个数为 `now`，前面的数依次递增，这样使得 **一个块中的数构成一个连续的下降序列**。再更改 `now` 的值即可。

### Proof of Max LIS

令数列中的块数为 $ k $（$ k $ 事实上是一个由输入字符串确定的定值，如果有疑惑，请参看上文 “块” 的定义）。因为一个块中的数递减，所以 **`LIS` 中不可能有两个数位于同一个块中**，`LIS` 长度最大值 $ \leqslant k $。

在这种构造方式下，**前面的块的任何数必定小于后面的块的任何数**。所以一定可以在每个块中取出一个数构成 `LIS`。证毕。

两种情况的时间复杂度都是 $ O(n) $。

---

虽然这是 Div. 2 的 D 题，但其实并没有那么复杂~~与玄学~~。其实上文的构造方式也是一个比较好理解的想法，只是笔者水平有限，语言描述略微有些冗余。所以可以通过看上面的两张图来帮助理解。

最小值和最大值的构造几乎是完全对称的，许多性质也惊人的相似。也许，这就是 OI 中的对称之美吧。OIer 们平时在切题的时候，也可以用到许多对称的性质，方便做题。

---

### Code

代码实现中，是在直接枚举每一个下标的过程中顺便找块的。中间的在块中填数运用了一次函数的性质（点斜式 233）。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int n;
		scanf("%d", &n);
		string s;
		cin >> s;
		s = " " + s;
		int now = n, p = 1;
		while(p <= n)
		{
			int tmp = p;
			while(s[p] == '<' && p < n)
				p++;
			for(int i = tmp; i <= p; i++)
				printf("%d ", i - (p - now));
			now = tmp - (p - now) - 1;
			p++;
		}
		putchar('\n');
		now = 1;
		p = 1;
		while(p <= n)
		{
			int tmp = p;
			while(s[p] == '>' && p < n)
				p++;
			for(int i = tmp; i <= p; i++)
				printf("%d ", p + now - i);
			now = p + now - tmp + 1;
			p++;
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

~~优秀乱搞题~~

对与每一个比较列，叫每一个"<"的连续段一个上升段。

上升段的性质是一个数列的LIS的长度肯定可以写成某些上升段的长度之和，应为这些上升段可以贪心的连起来。如果有一个LIS的元素不在上升段里面，肯定可以不选择这一个元素而选一个上升段里的元素来保持或者增长LIS的长度。

发现来最大化LIS，必须让每一个上升段的初始值比上一个上升段的最后值要大，所以所有上升段可以挑出组成一个LIS，并且必须是最长可能的LIS。

相似思路，来最小化LIS，必须让每一个上升段的初始值比上一个上升段的最后值要小，所以所有上升段都不能连成一个LIS。

具体怎么构造？对与最大化LIS，来算第 $i$ 个元素值，如果这个元素比上一个元素大，那么设为数列的最大值+1，否则设为数列的最小值-1。输出时必须把所有值调到1-n位置里。

来最小化LIS，就对与上升段倒着做。

比赛当中瞌睡，所以写了特别乱的代码。

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

int cray[200005];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q; cin >> q;
    while(q--) {
        int n; cin >> n;
        string s; cin >> s;
        cray[0] = 0;
        int l = 1,r = -1;
        int pt = 0;
        while(pt != s.length()) {
            if(s[pt] == '<') { 
                int cat = pt;
                while(s[pt] == '<') pt++;
                pt--;
                int terms = pt - cat + 1;
                r -= terms;
                cray[cat] -= terms;
                int st = r+1;
                while(cat != pt+1) {
                    cray[cat+1] = cray[cat]+1;
                    cat++;
                }
            }
            else { cray[pt+1] = r; r--; }
            pt++;
        }
        int mi = 0;
        rep(i, n) mi = min(mi, cray[i]);
        rep(i, n) {
            if(i) cout << ' ';
            cout << cray[i] - mi + 1;
        }
        cout << endl;
        l = 1, r = -1;
        pt = 0;
        cray[0] = 0;
        while(pt != s.length()) {
            if(s[pt] == '<') { cray[pt+1] = l; l++; }
            else { cray[pt+1] = r; r--; }
            pt++;
        }
        mi = 0;
        rep(i, n) mi = min(mi, cray[i]);
        rep(i, n) {
            if(i) cout << ' ';
            cout << cray[i] - mi + 1;
        }
        cout << endl;
    }
}


```


---

## 作者：MyukiyoMekya (赞：1)

一种很巧妙的做法

我们从第二个样例开始讲

想要 LIS 最小，我们就先这样放置

```
7 6 5 4 3 2 1
```

然后如果碰到一连串的**小于**号，那就把那一段小于号所在的数字段**整段翻转**

也就是说

```
 > > < > > <
```

```
7 6 4 5 3 1 2
```

第一个小于使得 `4 5` 被翻转，第二个 `<` 使得 `1 2` 被翻转

这样 LIS 就为最大连续小于号的长度，无论如何 LIS 都没办法小于这个

要想 LIS 最大，反过来就行了

先放置

```
1 2 3 4 5 6 7
```

如果碰到一连串的**大于**号，那就把那一段大于号所在的数字段**整段翻转**

```
 > > < > > <
```

```
3 2 1 6 5 4 7
```

这样 LIS 就为连续小于号段的数量+1，无论如何 LIS 都没办法大于这个

于是就 $O(n)$ 搞定了

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
/*
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
*/
char s[200050];
int a[200050];
inline void myrev(int l,int r)
{
	reg int delta=l-1;
	reg int n=r-l+1;
	for(int i=1;i<=n/2;++i)
		swap(a[delta+i],a[delta+n-i+1]);
	return;
}
inline void work()
{
	reg int n;
	cin>>n;
	cin>>(s+1);
	for(int i=1;i<=n;++i)
		a[i]=n-i+1;
	reg int cnt=0;
	for(int i=1;i<n;++i)
		if(s[i]=='<')
			++cnt;
		else if(cnt)
			myrev(i-cnt,i),cnt=0;
	if(cnt)
		myrev(n-cnt,n);
	for(int i=1;i<=n;++i)
		cout<<a[i]<<" ";
	cout<<endl;
	for(int i=1;i<=n;++i)
		a[i]=i;
	cnt=0;
	for(int i=1;i<n;++i)
		if(s[i]=='>')
			++cnt;
		else if(cnt)
			myrev(i-cnt,i),cnt=0;
	if(cnt)
		myrev(n-cnt,n);
	for(int i=1;i<=n;++i)
		cout<<a[i]<<" ";
	cout<<endl;
	return;
}
signed main(void)
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)
		work();
	return 0;
}
```

---

## 作者：Flandre_495 (赞：1)

CF被这么简单的一道题给虐了，呜~。回来补锅。

**题意：** 多组数据，每次给定长度$n$，让你构造出一组排列，满足给你的$n-1$对相邻数字大小关系，大小关系用 " < " 或 " > " 表示。输出LIS（最长上升子序列）最小的一组排列和最大的一组排列。

莫了。

**思路：** 

对于连续的"<"，说明这几个数本来就是递增的，若想找LIS最小的排列，它们不可避免地成为了上升子序列。我们将每一段上升的序列分开，分隔符即为">"，既然每一段递增无法避免，那就让段与段之间尽量连接不了。我们发现只需要让靠左的段中的数都尽量大于靠右的段中的数，即第一段取最大的那几个数，第二段取剩下的数中最大的几个，长这样：

![](https://t1.picb.cc/uploads/2020/02/16/k7fsfJ.png)

对于最长的LIS，如果我们还用刚才的模型的话：

![](https://t1.picb.cc/uploads/2020/02/16/k7fLLr.png)

我们肯定是想让每一个大于号都下降的尽量小，使得马上又能回到上一次递增的最高点。但由于下降多少次不稳定，下降的量也不好控制，我们换一下，把每个递减的序列分段：

![](https://t1.picb.cc/uploads/2020/02/16/k7fzA0.png)

就可了，就是图1的翻转版本，容易发现LIS即为段数。

依次扫每一段挨个赋值，复杂度是O(n)的，看代码就知道了。  
一道水题，代码呢，也很好写。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define QWQ cout<<"QwQ"<<endl;
#define ll long long
#include <vector>
#include <queue>
#include <stack>
#include <map>
using namespace std;
const int N=201010;
const int qwq=303030;
const int inf=0x3f3f3f3f;

int T;
int n;
char cz[N];
int a[N],now;

inline int read() {
	int sum = 0, f = 1; char c = getchar();
	while(c<'0' || c>'9') { if(c=='-') f = -1; c = getchar(); }
	while(c>='0'&&c<='9') { sum = sum * 10 + c - '0'; c = getchar(); }
	return sum * f;
}

int main() {
	T = read();
	while(T--) {
		n = read(); 
		scanf("%s",cz+1);
        now = n; cz[n] = cz[0] = '>';
		for(int i=1;i<=n;i++) {
			if(cz[i]=='>') {
				int cnt = i;
				while(2333) {
					a[cnt] = now--;
					if(cz[cnt-1]=='>') break;
					cnt--;
				}
			}
		}
		for(int i=1;i<=n;i++) cout<<a[i]<<" "; cout<<"\n";
		now = n; cz[n] = cz[0] = '<';
		for(int i=n-1;i>=0;i--) {
			if(cz[i]=='<') {
				int cnt = i+1;
				while(2333) {
					a[cnt] = now--;
					if(cz[cnt]=='<') break;
					cnt++;
				}
			}
		}
		for(int i=1;i<=n;i++) cout<<a[i]<<" "; cout<<"\n";
	}
	return 0;
}


/*

3
3 <<
7 >><>><
5 >>><

*/
```

然后我们发现一个问题，图3既然是图1翻过来的，那么图1就既满足最短上升，又满足最长下降。

**那么是不是所有的最短上升都满足最长下降呢？**  
**反过来是否所有的最长下降都满足最短上升呢？**

答案都是否定的。

对于第一问：

![](https://t1.picb.cc/uploads/2020/02/16/k7iV8w.png)

本来是一个最短的上升子序列的构造，假如第一段特别长，如果我们将第三段与第四段移动到上方，使第四段高出第二段，不会影响最长上升序列（即使二三四段可以连在一块，也没有第一段长）是最短的，但是无法再找到一个长度为4的下降序列。

对于第二问：

![](https://t1.picb.cc/uploads/2020/02/16/k7fKJd.png)

本来是一个最长的下降子序列的构造，如果将第二段的右端点提升过第一段，不会影响最长的下降序列，但会破坏最短的上升。

---

## 作者：Reanap (赞：0)

这是一个构造贪心，我是根据自己的经验yy出来的，希望对大家有帮助。
~~经验主义~~

因为相邻两数之间存在大小关系，根据之前的经验，我决定将直接关联的两个数之间连边，大数向小数连接一条有向边。

由于仅有$n-1$条边，所以这会形成一个有向无环图。有了$DAG$咱想到啥，拓扑排序啊！

经过我们的观察，我们发现，最后形成的合法序列必然是对这个$DAG$进行拓扑排序后的结果之一。

我们想要求最短的一个$LIS$，那么我们可以贪心地去构造出来。什么情况下$LIS$是最小的呢？我们贪心地认为，越大的数的编号越小，这个序列的$LIS$越可能小，因此，求最大的$LIS$同理。所以我们在进行拓扑排序的时候所用的队列，可以用小(大)根堆来维护。

代码如下：

```cpp
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 2e5 + 5;
vector <int> G[MAXN];
int du1[MAXN] , ans1[MAXN] , du2[MAXN] , ans2[MAXN];
int main() {
	int T;
	scanf("%d" , &T);
	while(T -- > 0) {
		int n;
		scanf("%d" , &n);
		for (int i = 1; i < n; ++i) {
			char s = getchar();
			while(s != '<' && s != '>') s = getchar();
			if(s == '<') {
				G[i + 1].push_back(i);
				du1[i] ++;
				du2[i] ++;
			}
			else {
				G[i].push_back(i + 1);
				du1[i + 1] ++;
				du2[i + 1] ++;
			}
		}
		priority_queue <int , vector <int> , greater<int> > q1;
		priority_queue <int , vector <int> , less<int> > q2;
		for (int i = 1; i <= n; ++i) {
			if(!du1[i]) q1.push(i);
			if(!du2[i]) q2.push(i);
		}
		int tot = n;
		while(!q1.empty()) {
			int x = q1.top();
			q1.pop();
			ans1[x] = tot;
			for (int i = 0; i < G[x].size(); ++i) {
				du1[G[x][i]] --;
				if(!du1[G[x][i]]) q1.push(G[x][i]);
			}
			x = q2.top();
			q2.pop();
			ans2[x] = tot;
			tot --;
			for (int i = 0; i < G[x].size(); ++i) {
				du2[G[x][i]] --;
				if(!du2[G[x][i]]) q2.push(G[x][i]);
			}
		}
		for (int i = 1; i <= n; ++i) printf("%d " , ans1[i]);
		putchar('\n');
		for (int i = 1; i <= n; ++i) printf("%d " , ans2[i]);
		putchar('\n');
		for (int i = 1; i <= n; ++i) ans1[i] = ans2[i] = du1[i] = du2[i] = 0;
		memset(G , 0 , sizeof G);
	}
	return 0;
}

```

---

## 作者：MikukuOvO (赞：0)

考虑这样的一种构造方法：

首先我们考虑$LIS$的最小值，我们找到所有的$>$，考虑两个$>$之间的一段区间，首先这个区间一定是连续上升的，那么我们考虑怎样让$LIS$最小，肯定是把大的数放在前面的区间，因此我们贪心的从大的数往小的数放即可，最大值也同理。

注：代码中如果有你看不懂的函数，那么这个函数就没啥用。。。

```cpp
const int N=2e5+5;

int T,n;
int ans[N];
char s[N];

int main()
{
    fio();
    gi(T);
    while(T--)
    {
        gi(n),scanf("%s",s+1);
        int num=n,last=1;
        for(int i=1;i<=n;++i)
        {
            if(i==n||s[i]=='>') 
            {
                for(int j=i;j>=last;--j) ans[j]=num--;
                last=i+1;
            }
        }
        for(int i=1;i<=n;++i) print(ans[i]),pc(' ');
        pc(10);
        num=1,last=1;
        for(int i=1;i<=n;++i)
        {
            if(i==n||s[i]=='<') 
            {
                for(int j=i;j>=last;--j) ans[j]=num++;
                last=i+1;
            }
        }
        for(int i=1;i<=n;++i) print(ans[i]),pc(' ');
        pc(10);
    }
    end();
}
```

---

