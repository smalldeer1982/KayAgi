# Walking!

## 题目描述

There is a sand trail in front of Alice's home.

In daytime, people walk over it and leave a footprint on the trail for their every single step. Alice cannot distinguish the order of the footprints, but she can tell whether each footprint is made by left foot or right foot. Also she's certain that all people are walking by alternating left foot and right foot.

For example, suppose that one person walked through the trail and left some footprints. The footprints are RRLRL in order along the trail ('R' means right foot and 'L' means left foot). You might think the outcome of the footprints is strange. But in fact, some steps are resulting from walking backwards!

There are some possible order of steps that produce these footprints such as $ 1→3→2→5→4 $ or $ 2→3→4→5→1 $ (we suppose that the distance between two consecutive steps can be arbitrarily long). The number of backward steps from above two examples are $ 2 $ and $ 1 $ separately.

Alice is interested in these footprints. Whenever there is a person walking trough the trail, she takes a picture of all these footprints along the trail and erase all of them so that next person will leave a new set of footprints. We know that people walk by alternating right foot and left foot, but we don't know if the first step is made by left foot or right foot.

Alice wants to know the minimum possible number of backward steps made by a person. But it's a little hard. Please help Alice to calculate it. You also need to construct one possible history of these footprints.

## 说明/提示

For the first sample, one possible order is $ 2→5→1→3→4 $ , among them only the step $ 5→1 $ is backward step so the answer is $ 1 $ .

For the second example one possible order is just to follow the order of input, thus there are no backward steps.

For the third sample, there will be $ 4 $ backward steps because every step from L to R will be a backward step.

## 样例 #1

### 输入

```
RRLRL
```

### 输出

```
1
2 5 1 3 4
```

## 样例 #2

### 输入

```
RLRLRLRLR
```

### 输出

```
0
1 2 3 4 5 6 7 8 9
```

## 样例 #3

### 输入

```
RRRRRLLLL
```

### 输出

```
4
4 9 3 8 2 7 1 6 5
```

# 题解

## 作者：Kinandra (赞：8)

标签: 贪心.

#### Part 1

显然本题等价于将字符串划分成若干个 `L` , `R` 交错的子序列, 最小化子序列的个数.

那么我们从左向右扫描字符串, 贪心地将当前地字母插入之前地子序列中.

之后把子序列拼接起来就行啦!

#### Part 2

你以为这么简单就可以了, naive!

我们看看这种情况 :`RLLR` , 这个字符串可能被我们划分成: `RL` 和  `LR` . surprise! 我们发现他没有办法拼接了, 需要划分成 `RLR(1,2,4)` 和 `L(3)` 才满足条件.

于是我们需要艰苦卓绝地分类讨论了...吗?

#### Part 3

分类讨论稍微有些麻烦, 我们进一步观察发现我们发现我们可以将所有 `RL` (指开头为 `R` 结尾为 `L`  的子序列) 拼成个 `RL` , `LR` 也可以. 

所以我们发现只有当所有的子序列都为 `RL` 和 `LR` (即无 `RR` 和 `LL` )的情况我们才无法拼接, 并且此时两种子序列均至少有一个.

这是我们不妨取出一个 `RL` 和一个 `LR` , 根据它们结尾的位置关系我们必然可以把它们变一个 `RR` 和 `LL` , 比如若 `LR` 的结尾在 `RL` 结尾之后, 我们将 `LR` 的结尾接给 `RL` 就行了.

这样可以避免分类讨论了.

时间复杂度 $\mathcal O(n)$.

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, idcnt;
char s[100005];
vector<int> v[100005], id[2], ve[2][2];

void adjust() {
    if (!ve[1][0].empty() || !ve[1][1].empty()) return;
    if (ve[0][0].empty() || ve[0][1].empty()) return;
    int a = ve[0][0].back(), b = ve[0][1].back();
    (v[a].back() < v[b].back())
        ? (v[a].push_back(v[b].back()), v[b].pop_back())
        : (v[b].push_back(v[a].back()), v[a].pop_back());
    ve[0][0].pop_back(), ve[0][1].pop_back();
    ve[1][0].push_back(b), ve[1][1].push_back(a);
}

void print(int x) {
    for (int i = 0; i < v[x].size(); ++i) printf("%d ", v[x][i]);
}

int main() {
    scanf("%s", s + 1), n = strlen(s + 1);
    for (int i = 1, c, t; i <= n; ++i) {
        c = s[i] == 'R';
        if (id[c ^ 1].empty()) id[c ^ 1].push_back(++idcnt);
        t = id[c ^ 1].back();
        v[t].push_back(i), id[c ^ 1].pop_back(), id[c].push_back(t);
    }
    printf("%d\n", idcnt - 1);
    for (int i = 1; i <= idcnt; ++i)
        ve[v[i].size() & 1][s[v[i].back()] == 'R'].push_back(i);
    adjust();

    int t = (ve[1][0].size() != ve[1][1].size())
                ? ve[1][1].size() > ve[1][0].size()
                : ve[0][0].size() > ve[0][1].size();

    while (!ve[0][t ^ 1].empty())
        print(ve[0][t ^ 1].back()), ve[0][t ^ 1].pop_back();

    while (!ve[1][t].empty()) {
        print(ve[1][t].back()), ve[1][t].pop_back();
        while (!ve[0][t].empty()) print(ve[0][t].back()), ve[0][t].pop_back();
        t ^= 1;
    }
    return 0;
}
```


---

## 作者：关怀他人 (赞：8)

#### Solution
将$L$看作$0$，$R$看作$1$，那么本题等价于将$s$划分成若干个$01$交替的子序列，且子序列首尾拼接后仍是$01$交替出现的，要求最小化子序列个数。贪心即可，对于每个子序列尽可能多的加入字符，若无法加入字符则新开一个子序列即可。

然后考虑如何满足**首尾拼接后仍是$01$交替出现的**这个限制，将所有子序列按照开头和结尾划分为$4$类，分别为$00,01,10,11$。不难发现，在只有$01$和$10$的时候，是无法拼在一起的，其他情况都是可以拼接的。考虑如何处理这种情况，可以通过将$01$和$10$转化为$00$和$11$解决。具体来说，考虑$01$与$10$最后一个位置的大小关系，将最后一个位置较小的子序列的末尾给较大的那个子序列，那么$01$就变成了$00$，$10$就变成了$11$，可以拼在一起。

时间复杂度$\mathcal O(n)$
```cpp
int n,tot;
int a[MAXN],id[MAXN];
vector<int> pos[MAXN],vec[2][2],tmp[2];
char s[MAXN];

void print(const vector<int> &v){
    for(int x : v){
        for(int y : pos[x])
            printf("%d ",y);
    }
}

int main(){
    scanf("%s",s + 1);
    n = strlen(s + 1);
    for(int i = 1;i <= n;i++){
        a[i] = (s[i] == 'R');
        if(tmp[a[i] ^ 1].empty())
            id[i] = ++tot;
        else
            id[i] = tmp[a[i] ^ 1].back(), tmp[a[i] ^ 1].pop_back();
        tmp[a[i]].push_back(id[i]);
        pos[id[i]].push_back(i);
    }
    for(int i = 1;i <= tot;i++)
        vec[a[pos[i][0]]][a[pos[i].back()]].push_back(i);
    if(!vec[1][0].empty() && !vec[0][1].empty() && vec[0][0].empty() && vec[1][1].empty()){
        int x = vec[1][0].back(), posx = pos[x].back();
        int y = vec[0][1].back(), posy = pos[y].back();
        int t = 0;
        if(posx > posy)
            swap(x,y), swap(posx,posy), t ^= 1;
        pos[y].pop_back();
        pos[x].push_back(posy);
        vec[t][t ^ 1].pop_back();
        vec[t ^ 1][t].pop_back();
        vec[t ^ 1][t ^ 1].push_back(x);
        vec[t][t].push_back(y);
    }
    int t = 0;
    if(vec[1][1].empty()) t ^= 1;
    printf("%d\n",tot - 1);
    print(vec[t][t]);
    print(vec[t ^ 1][t]);
    print(vec[t ^ 1][t ^ 1]);
    print(vec[t][t ^ 1]);
    return 0;
}
```

---

## 作者：chen_zhe (赞：8)

# CF578E Walking!

期中考之余做做构造题玩玩。其实我期中考完了，当然期中考也完了。

---

题目保证原数据有解，那么会发现 `L` 的个数和 `R` 的个数必然相差不超过 $1$。如果超过了 $1$ 则必定会因为没有不同的字符进行阻断而产生一个连续的 `LL` 或者一个连续的 `RR`，这样就可以把原字符串序列的结果划分成三种。

-   当 `L` 比 `R` 多的时候，结果是 `LRLR...RLRL`。
-   当 `L` 和 `R` 数量一样，结果是 `LRLR...RLR` 或者 `RLRL...LRL`。
-   当 `L` 比 `R` 少的时候，结果是 `RLRL...LRLR`。

其中第一种和第三种本质是一样的。

然后我们手玩一下样例，以样例 $1$ 为例：输入数据为 `RRLRL`，输出数据为 `2 5 1 3 4`。而样例中给出的仅仅只是一种可能方案，我们手玩一些其他的方案，可以发现 `1 3 4 5 2`，也是可以保证只存在 $(3,2)$ 一对 $p[i]>p[i+1]$ 的情况的。而对于样例 $3$，也有一种情况是 `1 6 2 7 3 8 4 9 5`，也能保证只存在 $(5,2),(6,3),(7,4),(8,5)$ 这 $4$ 对 $p[i]>p[i+1]$ 的情况的。

那么上面的构造方法有什么共通之处呢？

首先，根据上面三种划分结果，选择了合法的那种结果，然后找到第一个相应字符，填充在答案序列开头。特别地，当 `L` 和 `R` 数量相等的时候，则看是 `L` 先出现还是 `R` 先出现。

然后，对于答案序列之后的每一个数，从当前位置向右找到第一个未被使用的字符，且保证相邻两个字符互异后填入进去。如果当前位置往右没字符了，就从头开始。

关于这个贪心构造的一个看起来很感性的证明：每次从当前位置开始，找到下一个可以匹配上的字符，那么可以做到每一次从左往右扫，匹配到最多的字符对，从而保证折回去的次数最少。

然而现在的贪心还是会有问题的。直接这么写会 WA On Test 6，这是为什么呢。

举个简单的例子，`RRLLRRLLLRR`，如果用我们刚刚的贪心会输出 `1 3 5 7 10 4 6 8 9 11 2`，有三对 $p[i]>p[i+1]$。实际上有一种更好的解法是 `1 3 5 7 2 4 6 8 10 9 11`。，此时只有两对 $p[i]>p[i+1]$。

其实我们再多造几组数据，就会发现出现这种情况的时候，假定以当前选定了 `L` 为例，而且在它之后全都是 `R` ，在它之前有 `R` 未进行匹配，那么这段代码会先匹配后面的 `R`，然后再折回来去找前面的 `L` 和 `R` 再以此类推陷入僵局（如果选定了 `R` 的话也同理）。而实际上，在这种情况中如果先折回去匹配前面的 `R`，然后再从前面把 `L` 或者 `R` 一路匹配下来的话，那么结果必定会更优。

给个很感性的证明：以当前选定 `L` 为例的情况下，那么先匹配后面的 `R`，再匹配前面的 `L`，在上面的假设下，在第二个被匹配的 `L` 前面必定还存在至少一个未被匹配的 `R`，那么到时候还得再多折回至少一次（在上述例子中最后的那个 `2` 就是一个体现）。而如果是先匹配前面的 `R` 再回来的时候，则可以少掉为了专门去匹配这个 `R` 的至少一个折回。

因此我们的代码中只需要对这种情况进行额外处理，这样就可以 AC 了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>
#include <set>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

const int inf=1e6;

string s;

set <int> s1,s2;

int ans[100050],aid;

int main()
{
	cin >> s;
	for (int i=0;i<s.length();i++)
	{
		if (s[i]=='L')
			s1.insert(i);
		else
			s2.insert(i);
	}
	s1.insert(inf);
	s2.insert(inf);
	if (s1.size()<s2.size() || (s1.size()==s2.size() && *s1.begin()>*s2.begin()))
		swap(s1,s2);
	int cnt=0,pos=-1,next=*s1.begin();
	bool flag=false;
	for (int i=0;i<s.length();i++)
	{
		flag=!flag;
		if (flag)
		{
			if (next==inf || (*s2.lower_bound(next)==inf && *s1.begin()!=next && *s1.begin()<*s2.begin()))
			{
				cnt++;
				next=*s1.begin();
			}
			pos=next;
			s1.erase(pos);
			next=*s2.lower_bound(pos);
			ans[++aid]=pos+1;
		}
		else
		{
			if (next==inf || (*s1.lower_bound(next)==inf && *s2.begin()!=next && *s1.begin()>*s2.begin()))
			{
				cnt++;
				next=*s2.begin();
			}
			pos=next;
			s2.erase(pos);
			next=*s1.lower_bound(pos);
			ans[++aid]=pos+1;
		}
	}
	cout << cnt << endl;
	for (int i=1;i<=aid;i++)
		cout << ans[i] << " ";
	return 0;
}

```



---

## 作者：Karry5307 (赞：7)

### 题意

略。

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13733909.html)

好毒瘤啊，我最多就口胡第一问的样子吧。

第一问很显然（~~跟凤凰县探险队员一样显然~~），就是每次贪心选长度最大的满足条件的子序列，选不到就折返回来。所以折返的次数很明显就是选出子序列的个数 $-1$。

考虑第二问，很明显不能暴力拼接子序列，这样很容易被 hack。具体方法剩下的题解有讲。

注意到找到的子序列可以按照开头和结尾分成 $4$ 类：`LL`，`LR`，`RL` 和 `RR`。

首先有一个性质：可以将所有的 `LR` 拼在一起得到一个更长的 `LR`，`RL` 同理。

接下来 `LL` 和 `RR` 有一个特殊的作用，就是将一段 `LR` 和一段 `RL` 拼起来，类似于 `L...RL...LR...L` 和 `R...LR...RL...R`。（这里两个字母中间三个点表示一段子序列）

但是有些时候，没有 `LL` 和 `RR`，但是有 `LR` 和 `RL`，这两段是无法拼起来的。难道我们就这样失败了吗？没有的事！

我们可以通过已经有的 `LR` 和 `RL` 自己造一个 `LL` 和 `RR` 出来。具体地话就是考虑 `LR` 与 `RL` 中最后一个位置的关系。然后最后一个位置小的那个序列把最后一个位置给大的那个，然后 `LR` 就变成了 `LL`，而 `RL` 就变成了 `RR`。

然后这题就做完了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,tot,x,y,swp;
vector<ll>v[MAXN],vg[2],g[2][2];
char ch[MAXN]; 
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	scanf("%s",ch+1),n=strlen(ch+1);
	for(register int i=1;i<=n;i++)
	{
		x=ch[i]=='R',vg[x^1].empty()?vg[x^1].push_back(++tot):(void)1;
		y=vg[x^1].back(),v[y].push_back(i);
		vg[x^1].pop_back(),vg[x].push_back(y);
	}
	printf("%d\n",tot-1);
	for(register int i=1;i<=tot;i++)
	{
		g[v[i].size()&1][ch[v[i].back()]=='R'].push_back(i);
	}
	if(!g[0][0].empty()&&!g[0][1].empty()&&g[1][0].empty()&&g[1][1].empty())
	{
		x=g[0][0].back(),y=g[0][1].back();
		v[x].back()<v[y].back()?1:(swap(x,y),swp=1);
		v[x].push_back(v[y].back()),v[y].pop_back();
		g[0][0].pop_back(),g[0][1].pop_back(),swp?swap(x,y):(void)1;
		g[1][0].push_back(y),g[1][1].push_back(x);
	}
	if(g[1][0].size()!=g[1][1].size())
	{
		x=g[1][1].size()>g[1][0].size();
	}
	else
	{
		x=g[0][0].size()>g[0][1].size();
	}
	while(!g[0][x^1].empty())
	{
		for(register int i:v[g[0][x^1].back()])
		{
			printf("%d ",i);
		}
		g[0][x^1].pop_back();
	}
	while(!g[1][x].empty())
	{
		for(register int i:v[g[1][x].back()])
		{
			printf("%d ",i);
		}
		g[1][x].pop_back();
		while(!g[0][x].empty())
		{
			for(register int i:v[g[0][x].back()])
			{
				printf("%d ",i);	
			}
			g[0][x].pop_back();
		}
		x^=1;
	}
}
```

---

## 作者：xht (赞：3)

> [CF578E Walking!](https://codeforc.es/contest/578/problem/E)

## 题意

- 给定一个长度为 $n$ 的只包含 `L,R` 的字符串 $s$。
- 构造一个 $n$ 排列 $p$ 满足 $s[p_i] \ne s[p_{i+1}](1 \le i < n)$。
- 最小化 $p$ 中 $p_i > p_{i+1}(1 \le i < n)$ 的数量。
- $n \le 10^5$，数据保证有解。

## 题解

问题等价于，将 $s$ 划分成尽可能少的 `L,R` 交替的非连续子序列。

考虑贪心，每添加一个字符，就在前面划分好的子序列中找一个可以接到末尾的接进去，没有可以接的就新开一个子序列。

最后要将若干个子序列拼接在一起，分类讨论一下即可。

## 代码

```cpp
const int N = 1e5 + 7;
int n, t[N];
char s[N];
vi e[2], Ans;
vector< pi > g[4], ans;

int main() {
	rds(s, n);
	map< char, int > p;
	p['L'] = 0, p['R'] = 1;
	for (int i = 1; i <= n; i++) {
		int c = p[s[i]];
		if (e[c^1].size()) {
			t[i] = e[c^1].back();
			e[c^1].pop_back();
		}
		e[c].pb(i);
	}
	print(e[0].size() + e[1].size() - 1);
	for (ui i = 0; i < e[0].size(); i++) {
		int x = e[0][i], y = x;
		while (t[y]) y = t[y];
		g[p[s[y]]<<1|p[s[x]]].pb(mp(y, x));
	}
	for (ui i = 0; i < e[1].size(); i++) {
		int x = e[1][i], y = x;
		while (t[y]) y = t[y];
		g[p[s[y]]<<1|p[s[x]]].pb(mp(y, x));
	}
	while (g[1].size() > 1u) {
		pi x = g[1].back();
		g[1].pop_back(); 
		t[x.fi] = g[1].back().se;
		g[1].back().se = x.se;
	}
	while (g[2].size() > 1u) {
		pi x = g[2].back();
		g[2].pop_back(); 
		t[x.fi] = g[2].back().se;
		g[2].back().se = x.se;
	}
	if (g[1].size() && g[2].size()) {
		pi x = g[1][0], y = g[2][0];
		g[1].pop_back(), g[2].pop_back();
		if (x.se > y.se) {
			g[0].pb(mp(x.fi, t[x.se]));
			t[x.se] = y.se;
			g[3].pb(mp(y.fi, x.se));
		} else {
			g[3].pb(mp(y.fi, t[y.se]));
			t[y.se] = x.se;
			g[0].pb(mp(x.fi, y.se));
		}
	}
	if (g[0].size() > g[3].size() || (g[0].size() == g[3].size() && !g[2].size())) {
		if (g[1].size()) ans.pb(g[1][0]);
		for (ui i = 0; i < g[3].size(); i++)
			ans.pb(g[0][i]), ans.pb(g[3][i]);
		if (g[0].size() > g[3].size()) ans.pb(g[0].back());
	} else {
		if (g[2].size()) ans.pb(g[2][0]);
		for (ui i = 0; i < g[0].size(); i++)
			ans.pb(g[3][i]), ans.pb(g[0][i]);
		if (g[3].size() > g[0].size()) ans.pb(g[3].back());
	}
	while (ans.size() > 1u) {
		pi x = ans.back();
		ans.pop_back(); 
		t[x.fi] = ans.back().se;
		ans.back().se = x.se;
	}
	Ans.pb(ans.back().se);
	while (t[Ans.back()]) Ans.pb(t[Ans.back()]);
	while (Ans.size()) print(Ans.back(), " \n"[Ans.size()==1u]), Ans.pop_back();
	return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：0)

这里是细节换常数的做法，全程使用链表，截止目前是 rk1。

首先我们把排列写下来，每有一个贡献的地方断一次：

![](https://cdn.luogu.com.cn/upload/image_hosting/7x6zjcha.png)

发现每一段都是一个子序列，且由题意满足对应的字符串 LR 交错。

下面用 $str(X,Y)$ 代表一个以 $X\in\{L,R\}$ 开头，以 $Y\in\{L,R\}$ 结尾的 LR 交错的字符串。

由于保证数据有解，我们将此过程反过来：

答案满足断开是子序列且 LR 交错，我们构造答案就先构造 LR 交错的子序列再拼起来，这样我们就只用考虑拼接的问题了。

如果是 $str(L,L)$ 、$str(R,R)$ 的子序列，是很好处理的，直接交错拼接即可。

如果是 $str(L,R)$ 、$str(R,L)$ 的子序列，发现这样的序列可以接在同种序列的后面，最后这两种都只会剩下 **一个** 相同形式的很长的 **排列**，只剩下一个的话就简单了许多。

注意这里并不是子序列而是排列，但这并不影响我们使用。

我们拼接只关心以什么字符开头和什么字符结尾，发现 $str(L,L)$ 、$str(R,R)$，除了和自己都能拼，但由于保证有解不可能只剩一种都是同种形式。

考虑 $str(L,R)$ 、$str(R,L)$ ，如果只有其中一个，可以随便和 $str(L,L)$ 、$str(R,R)$ 拼起来。

但如果 $str(L,R)$ 、$str(R,L)$ 都有，就可能出现 $str(L,L)$ 、$str(R,R)$ 都没有导致拼不起来的情况。

那么我们就考虑 $str(L,R)$ 、$str(R,L)$ 都有的情况。

发现可以把 $str(L,R)$ 结尾的 $R$ 移给 $str(R,L)$ 或是把 $str(R,L)$ 结尾的 $L$ 移给 $str(L,R)$。

由于结尾肯定一前一后，所以肯定可以把一个结尾移给另一个，可以使得两类串均变为 $str(L,L)$ 、$str(R,R)$。

代码就是上述过程的实现，具体流程如下：

- 先把子序列按结尾分类；

- 把开头结尾不同的拼起来，相同的放一边；

- 如果两种开头结尾不同的串都有，把一个的结尾移给另一个，然后所有串的开头结尾全部相同；

- 如果只有一种开头结尾不同的且放在最前面不行就放到最后面；

- 最后交错拼起来即可。

此流程主要是为了方便对链表拼接，只有开始一步要边分类边拼接出链表，其他的都是暴力拼一串链表或暴力改两个链表，方便实现。

主要是我写的链表不好分类，但很好挨着拼接，如果有更好的办法也可以自己实现。

[代码](https://www.luogu.com.cn/paste/jvxtre0z)~~不保证能看懂~~。

---

