# [ABC278F] Shiritori

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc278/tasks/abc278_f

$ N $ 個の文字列 $ S\ _\ 1,S\ _\ 2,\ldots,S\ _\ N $ が与えられます。 $ S\ _\ i\ (1\leq\ i\leq\ N) $ は英小文字からなる長さ $ 10 $ 以下の空でない文字列で、互いに異なります。

先手太郎君と後手次郎君がしりとりをします。 このしりとりでは、先手太郎君と後手次郎君の手番が交互に訪れます。 はじめの手番は先手太郎君の手番です。 それぞれのプレイヤーは自分の手番において整数 $ i\ (1\leq\ i\leq\ N) $ を $ 1 $ つ選びます。 このとき、$ i $ は次の $ 2 $ つの条件を満たしていなければなりません。

- $ i $ は、しりとりが開始してからこれまでの $ 2 $ 人の手番で選ばれたどの整数とも異なる
- この手番がしりとりの最初の手番であるか、直前に選ばれた整数を $ j $ として、$ S\ _\ j $ の最後の文字と $ S\ _\ i $ の最初の文字が等しい
 
条件を満たす $ i $ を選べなくなったプレイヤーの負けで、負けなかったプレイヤーの勝ちです。

$ 2 $ 人が最適に行動したときに勝つのはどちらかを判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 16 $
- $ N $ は整数
- $ S\ _\ i\ (1\leq\ i\leq\ N) $ は英小文字からなる長さ $ 10 $ 以下の空でない文字列
- $ S\ _\ i\neq\ S\ _\ j\ (1\leq\ i\lt\ j\leq\ N) $
 
### Sample Explanation 1

例えば、ゲームは以下のように進行します。 この進行例では $ 2 $ 人の行動が必ずしも最適とは限らないことに注意してください。 - 先手太郎君が $ i=3 $ を選ぶ。$ S\ _\ i= $`if` である。 - 後手次郎君が $ i=2 $ を選ぶ。$ S\ _\ i= $`float` であり、`if` の最後の文字と `float` の最初の文字は等しい。 - 先手太郎君が $ i=5 $ を選ぶ。$ S\ _\ i= $`takahashi` であり、`float` の最後の文字と `takahashi` の最初の文字は等しい。 - 後手次郎君は $ i\neq2,3,5 $ であって $ S\ _\ i $ の最初の文字が `i` と等しいものを選べないため、負ける。 このとき、先手太郎君が勝ちます。

## 样例 #1

### 输入

```
6
enum
float
if
modint
takahashi
template```

### 输出

```
First```

## 样例 #2

### 输入

```
10
catch
chokudai
class
continue
copy
exec
havoc
intrinsic
static
yucatec```

### 输出

```
Second```

## 样例 #3

### 输入

```
16
mnofcmzsdx
lgeowlxuqm
ouimgdjxlo
jhwttcycwl
jbcuioqbsj
mdjfikdwix
jhvdpuxfil
peekycgxco
sbvxszools
xuuqebcrzp
jsciwvdqzl
obblxzjhco
ptobhnpfpo
muizaqtpgx
jtgjnbtzcl
sivwidaszs```

### 输出

```
First```

# 题解

## 作者：liangbowen (赞：26)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc278_f)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16910421.html)

博弈论，状压，记忆化搜索。

[整合题解](https://www.luogu.com.cn/blog/liangbowen/abc278-ti-jie)。

## 思路

看到很小的 $n$，容易联想到状压、搜索。本题就是状压加搜索。

设状态 $x$ 的每一位表示：如果第 $i$ 位是 $0$，则当前数没有被选过。否则已经选过了。

每次 dfs 的时候，记录当前状态，以及上一次选的字符串。

如果有一种情况能使对手必败，那么我们就必胜。如果所有情况都是对手胜，那么我们必败。

注意要记忆话，否则会被卡到 $O(n!)$ 然后 TLE 几个点。

## 代码

省去了大段的缺省源。

```cpp
const int N = 17;
int n;
string a[N];

bool vis[1 << N][N], ans[1 << N][N]; //vis 是看 ans 有没有出现过
bool dfs(int x, int lst) //x 是状压
{
	if (vis[x][lst]) return ans[x][lst]; //记忆化搜索
	for (int i = 1; i <= n; i++)
		if ( !(x & (1 << (i - 1))) ) //意思：x的第i位是0
			if (lst == 0 || a[lst][a[lst].length() - 1] == a[i][0]) //如果可以接上去
				if ( !dfs(x | (1 << (i - 1)), i) ) //尝试接
					{vis[x][lst] = true; return ans[x][lst] = true;}  //对手必败，说明我方必胜
	vis[x][lst] = true; return ans[x][lst] = false; //怎样都是对手胜，那么我们必败
}
void solve()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) cin >> a[i];

	if (dfs(0, 0)) puts("First");
	else puts("Second");
}
```

希望能帮助到大家！

---

## 作者：StayAlone (赞：6)

### 题意

两个人玩游戏。

给定 $n$ 个仅包含小写字母的串 $s_i$，其中 $n\leq 16,|s_i|\leq 10$。

每一轮游戏中，要拿走一个串 $k$。$k$ 必须满足以下两个条件**之一**：

- 这是第一轮游戏。
- $s_k$ 的第一个字符与上一次取的串的最后一个字符相同。

两个人都光头般聪明，问先后手谁赢。

### 思路

显然状压。

对于一个 dp 状态，有用的信息只有目前取到的最后一个字符以及字符串的选/不选。因此，设 $f_{v, t}$ 表示目前取到的最后一个字符为 $v$，目前的字符串集为 $t$，先手能否胜利。

其中 $t$ 的二进制第 $i$ 位为 $1$ 表示 $s_i$ 已选；反之亦然。注意特判第一轮游戏。

显然有：

$$
f_{v, t} = \bigvee_{t_i = 0\land s_{i,first} = v} (f_{s_{i, last}},t + 2^{i - 1}) \oplus 1
$$

看式子容易劝退。含义即对于当前状态，对于所有 $i$，如果 $i$ 没被选而且合法，那么试一下选 $i$。如果这些 $i$ 中有某一个状态的先手必败（即当前状态的后手），那么就能保证现在这个状态先手必胜，否则必败。

[AC code record](https://www.luogu.com.cn/record/95031159)

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rep2(i, l, r) for (int i = l; i >= int(r); --i)
#define rer(i, l, r, a) rep1(i, l, r) read(a[i])
#define ptc putchar
#define il inline
#define rout return 0
using namespace std;
const int MAXN = 1e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
namespace stupid_lrc {

}
using namespace stupid_lrc;
string s[20]; int n, f[30][MAXN];

il int dfs(int b, int t) {
	if (~f[b][t]) return f[b][t];
	bool w = 0;
	rep1(i, 1, n) if (!((t >> i - 1) & 1) && (s[i][0] - 'a' + 1 == b || !b)) {
		w |= dfs(s[i][1] - 'a' + 1, t | (1 << i - 1)) ^ 1;
	} return f[b][t] = w; 
}

int main() {
	read(n); rep1(i, 1, n) {
		cin >> s[i]; char t = s[i][s[i].size() - 1];
		s[i] = s[i][0]; s[i] += t;
	}
	rep1(i, 0, 26) rep1(j, 0, 1 << n) f[i][j] = -1;
	puts(dfs(0, 0) ? "First" : "Second");
	rout;
}
```


---

## 作者：hejianxing (赞：2)

第一次见黄色的状压 dp 呢……

# 题目大意

就是单词接龙啦。每个单词只能用一次，接龙单词最后一个字母和第一个字母要相同。然后两个人博弈。

# 题解

这个数据范围和题面，显然是状压 dp。

考虑设 $f_{state,i}$ 表示状态为 $state$，接龙的最后一个单词是第 $i$ 个（从 $0$ 开始标号）单词，先手必胜值为 $1$（先手已经操作完毕），否则为 $0$。其中 $state$ 二进制下从右往左第 $i$ 位为 $1$ 表示第 $i$ 个单词已经被使用。

考虑正着转移，也即从一个都没用过到全部都用过。发现对于博弈论来说好像并不是很好做。

那么考虑倒着转移。显然全部单词都用过时，先手必胜。

$state'$ 与 $state$ 二进制下有且仅有一位不同，且 $state$ 那一位为 $0$，$state'$ 那一位为 $1$。

当所有 $state'$ 中存在一个状态是必胜，那么当前状态 $state$ 必败，因为对方会行动至必胜态。

列出如下转移：

$$
f_{state,i}=\neg\bigcap\limits_{state',j}f_{state',j}
$$

当然要判断第 $j$ 个单词后是否能接上第 $i$ 个单词。

时间复杂度 $O(2^{n}n^2)$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1 << 17;
int n, f[N][20], l[20];
char a[20][20];
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%s", a[i]), l[i] = strlen(a[i]) - 1;
    for (int i = 0; i < n; i++) f[(1 << n) - 1][i] = 1;
    for (int i = (1 << n) - 2; i >= 0; i--)
        for (int j = 0; j < n; j++)
            if ((i >> j) & 1) {
                f[i][j] = 1;
                for (int k = 0; k < n; k++)
                    if (k != j && !((i >> k) & 1) && a[k][l[k]] == a[j][0])
                        if (f[i ^ (1 << k)][k])
                            f[i][j] = 0;
            }
    int fl = 0;
    for (int i = 0; i < n; i++) fl = max(fl, f[1 << i][i]);
    if (fl) printf("First");
    else printf("Second");
    return 0;
}
```

# END

---

## 作者：Z1qqurat (赞：2)

奇妙的 dp。听说这题可以用 SG 函数做，但是我不会，A~hu~A~hu。感觉做过一道类似的计数题，是考虑的目前选的所有字符串拼成的串的末尾字符的一个计数类 dp。觉得很像，可以类比，但是这个题涉及到先手后手，直接 dp 貌似不行啦。

$n$ 只到 $16$，可以考虑状压，也不得不状压。设 $f _ {i,j}$ 表示目前 $n$ 个字符串的状态为 $i$，其中 $0$ 表示没有选这个字符串，$1$ 表示选了，此时结尾的字符为 $j$ 时是否可行。那么对于状态 $f _ {i,j}$，我们选择一个不属于 $i$ 也就是没有选过的字符串 $k$ 满足 $s _ k$ 为 $j$，设 $l$ 为 $i$ 加上选择了 $k$ 之后的状态，$r$ 为 $s _ k$ 的末尾字符，那么如果  $f _ {l,r}$ 为 $1$，$f _ {i,j}$ 必须为 $0$，否则若不存在这样的 $k$，就有 $f _ {i,j}$ 为 $1$，这可能是博弈论知识。那么只有存在 $i$ 属于 $[0,n)$，$j$ 为 $s _ i$ 的最后一个字符，满足 $f _ {2^i,j}$ 时先手必胜，否则是后手必胜。

所以，这其实是一种**以更晚状态推出更早状态**的 dp，所以我们应该将状态 $i$ 倒序枚举来维护。

需要注意的是，为了好写状压 dp，我们在压缩后的状态中的第 $j$ 位从右往左数。在转移的时候需要判掉不合法状态：$k$ 属于状态 $i$ 或 $s _ k$ 第一位不是 $j$。

建议结合代码食用：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 17;
int f[1 << N][26], n, l[N];
string s[N];

signed main() {
    scanf("%lld", &n);
    for (int i = 0; i < n; ++i) cin >> s[i], l[i] = s[i].length();
    for (int i = (1 << n) - 1; i > 0; --i) {
        for (int j = 0; j < 26; ++j) {
            bool b = 1; //用来记录f[i][j]
            for (int k = 0; k < n; ++k) {
                if((1 << k) & i || s[k][0] != j + 'a') continue; //不合法的状态判掉
                if(f[i | (1 << k)][s[k][l[k] - 1] - 'a']) { 
                    b = 0; 
                    break; 
                } //有可行的后继状态，那么f[i][j]就是0了
            }
            f[i][j] = b;
        }
    }
    for (int i = 0; i < n; ++i) {
        if(f[1 << i][s[i][l[i] - 1] - 'a']) return puts("First"), 0; //如果有这样的i，那么可以结束游戏了，此时先手必胜
    }
    puts("Second"); //否则就是后手
    return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：1)

博弈论题，使用记忆化搜索求出 $sg$ 值。    
首先我们知道当当前轮到的这一方发现 **TA** 已经接不上的时候，这个状态就是必败态。    
那么我们对于目前的状态，枚举 **TA** 的后继状态，按照 $sg$ 值的规律求出当前状态的 $sg$ 值即可。  
（对于 $sg$ 函数，大家应该知道，如果一个状态的后继状态全是必败态，那么当前状态就是必胜态，反之则为必败态。）     
然而就这样单纯地搜索的话会超时，所以需要考虑优化。而大部分人都用的是记忆化，所以这里也讲讲记忆化。    
对于每个单词，有选或者不选两种情况，分别用 `1` 或 `0` 表示。把这些数字按顺序排列，会组成一个 `01` 串。我们把这个 `01` 串看做一个二进制数，这样这个状态就可以被储存进数组里，这就叫状态压缩。    
由于字符串的数量 $\leq 16$，所以储存状态的数组只需要开到 $2^{16}=65536$ 即可。      
这样的话，我们当遇到重复的状态时，就可以直接利用之前算过的状态，而不需要重新再算一遍，这样大大减少了计算量。    
（当然我的某位[神犇同学](https://www.luogu.com.cn/user/808529)的[剪枝](https://www.luogu.com.cn/record/111361169)也不是不行，TA 拿下了全洛谷最优解，我们一起膜拜 %%%）     
参考代码：
```cpp
#include<stdio.h>
#include<string.h>
int n,ans,num[20],zt[70000];char s[20][15];bool f[20];
int sg(int where,int zhuangtai)
{
	if(zt[zhuangtai]!=-1) return zt[zhuangtai];
	int returns=0;
	f[where]=1;
	for(int i=1;i<=n;i++) if((!f[i])&&s[i][1]==s[where][num[where]]) returns|=sg(i,zhuangtai+(1<<(i-1)));
	//如果有后继状态能使得后手必败，那么先手就必胜
	f[where]=0;return zt[zhuangtai]=returns^1;
}
int main()
{
	memset(zt,-1,sizeof(zt))/*记得初始化为-1，因为状态必胜与否是用1和0表示的*/,scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%s",s[i]+1),num[i]=strlen(s[i]+1);
	for(int i=1;i<=n;i++)
	{
		memset(f,0,sizeof(f));
		if(sg(i,1<<(i-1)))//当前只选了第i个，TA的后面需要添加(i-1)个0
		{
			printf("First");//如果从这个单词开始是必胜态，那么先手必胜
			return 0;
		}
	}
	printf("Second");
}
```

---

## 作者：CodingOIer (赞：0)

## [ABC278F] Shiritori 题解

### 思路分析

我太弱了，只会暴搜。

定义 $status$ 的第 $x$ 位表示第 $x$ 个单词是否已经被选过，$last$ 表示上一个单词的末尾。

定义 $win(status, last)$ 表示在选了 $status$ 且末尾是 $last$ 的情况下是否有必胜策略。

显然，如果有一个单词，递归调用 $win$ 时对方没有必胜策略，则当前肯定有必胜策略。

否则，没有必胜策略。

然后对 $status$ 和 $last$ 记忆化一下是否有必胜策略。

最多的情况数是 $2^{16} \times 26 = 2 \times 10^6$，能过。

（没想到博弈论也能暴搜吧）

### 代码实现 

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>
#include <tuple>
constexpr int MaxN = 1e2 + 5;
int n;
char bg[MaxN];
char ed[MaxN];
char temp[MaxN];
std::map<std::tuple<int, char>, bool> map;
bool win(int status, char last)
{
    if (map.count({status, last}))
    {
        return map[{status, last}];
    }
    for (int i = 1; i <= n; i++)
    {
        if ((~status >> (i - 1)) & 1 && (status == 0 || bg[i] == last) && !win(status | (1 << (i - 1)), ed[i]))
        {
            map[{status, last}] = true;
            return true;
        }
    }
    map[{status, last}] = false;
    return false;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", temp + 1);
        bg[i] = temp[1];
        ed[i] = temp[strlen(temp + 1)];
    }
    printf("%s\n", win(0, '\0') ? "First" : "Second");
    return 0;
}
```

---

## 作者：_shine_ (赞：0)

爆搜减枝模板。

先进行爆搜，然后发现有几个点没有通过（超时），必定尝试剪枝。

因为会重复进行搜索，但是贸然改变顺序肯定也会有问题，但是当有两个重复头尾首字母以及同样的顺序时必定是重复的，所以可以直接排除掉，剪完后时间即可过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n;string s[maxn];
int e[maxn],ne[maxn],h[maxn],idx;bool vis[maxn];map<string,int>now_p;
int look_now[maxn][10];
void add(int a,int b){e[idx]=b,ne[idx]=h[a];h[a]=idx++;}
bool now_dfs(int u,int now_idx,string now){
	bool flag=false;int now_ans=0;int cnt=0;
	if(vis[u]==true || h[u]==-1){if(now_idx%2!=0)return true;else return false;}
	vis[u]=true;for(int i=h[u];i!=-1;i=ne[i]){
		if(vis[e[i]]==true)continue;
		if(now_p[now+" "+s[e[i]][0]+s[e[i]][s[e[i]].size()-1]]==true)continue;
		now_p[now+" "+s[e[i]][0]+s[e[i]][s[e[i]].size()-1]]=true;
		cnt++;
		if(now_dfs(e[i],now_idx+1,now+" "+s[e[i]][0]+s[e[i]][s[e[i]].size()-1])==false){if((now_idx+1)%2==0)flag=true;}
		else now_ans++;
	}vis[u]=false;
//	cout << now_idx << " " << u << " " << flag << endl;
//	if(u==5)cout << cnt << " fuck " << vis[3] << " " << now_idx << endl;
	if(cnt==0){if(now_idx%2!=0){return true;}else return false;}
	if(flag==false && now_ans!=0){/*cout << u << endl;*/return true;}
	else return false;
}
signed main(){memset(h,-1,sizeof(h));
	cin >> n;for(int i=1;i<=n;++i){cin >> s[i];}
	for(int i=1;i<=n;++i)add(0,i);
	for(int i=1;i<=n;++i)for(int j=1;j<=n;++j){if(i==j)continue;if(s[i][0]==s[j][s[j].size()-1]){add(j,i);/*cout << j << " " << i << endl;*/}}
	bool ans=false;if(now_dfs(0,0,"")==true)puts("First");
	else puts("Second");
//	for(int i=1;i<=n;++i)if(now_dfs(0,1,(string)((char)s[i][0]+(char)s[i][s[i].size()-1]))==true){/*cout << "look " << i << endl;*/ans=true;}
//	if(ans==true)puts("First");else puts("Second");
	return 0;
}
/*
6
enum
float
if
modint
takahashi
template

10
catch
chokudai
class
continue
copy
exec
havoc
intrinsic
static
yucatec

16
mnofcmzsdx
lgeowlxuqm
ouimgdjxlo
jhwttcycwl
jbcuioqbsj
mdjfikdwix
jhvdpuxfil
peekycgxco
sbvxszools
xuuqebcrzp
jsciwvdqzl
obblxzjhco
ptobhnpfpo
muizaqtpgx
jtgjnbtzcl
sivwidaszs


*/
```


---

## 作者：Expert_Dream (赞：0)

其实并不难，不知道为什么考场没有搞出来，没了一个小时。

实际上是一个状压 Dp，想到了，但不知道具体怎么搞。我们可以设 $dp_{i,j}$ 代表 $i$ 这个状态下面以 $j$ 这个字符出结尾的能否必胜。然而，$n \le 16$ 级的数据完全可以状压瞎枚举。通过转换一下，这个必胜，那么如果到达他之后的一个点那就是必输。~~很显然的博弈论嘛~~。

最后只要有一个必胜，那就是 first 胜利，毕竟他是主动权的嘛。如果一个没有，那么就是 Second 胜利。

~~感觉一有点博弈论就不行了~~。场切不过黄，太弱了，下次加油！！

[link](https://atcoder.jp/contests/abc278/submissions/48495222)。

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

---

## 作者：FL_sleake (赞：0)

好好好又一次显现了我的脑回路和别人不太一样。

是目前题解区唯一用哈希做的，虽然主体相同。

### 题意简述

给定 $n$ 个不同的字符串。

两人轮流取出一个还未被取出的字符串，要求除先手第一次外，每次取出的字符串的首字符和上一次取出的字符串的尾字符相同。不能操作者输。

问两人均采取最优方案时，先手是否必胜。

### 解题思路

第一反应是建图。对于任意两个 $i,j$，如果 $s_i$ 的末尾等于 $s_j$ 的开头，那么 $i$ 到 $j$ 连一条边，表示上一个选 $i$ 则当前可以选 $j$。然后我用一个 $0$ 号点连上所有的 $i=1,2,\cdots,n$，表示第一次可以选择任意一个串。

接下来就开始搜索。第一发是裸的搜索，超时了五个点。思路是如果当前是第一个人走，那么如果有一条能使他赢的路径，他就可以赢。如果当前是第二个人走，同理。因为两个人都很聪明，所以只要有一种必胜策略就一定会选择它。我选择建立一个变量 $ans$，$ans$ 为 $1$ 则第一个人胜，$ans$ 为 $0$ 则第二个人胜。这样是为了方便搜索过程中通过与和或操作得到结果。

然后考虑优化。如果当前第一个人走，并且已经找到一个必胜策略，那么就可以直接返回了。第二个人同理。然后再交上去，只有 after_contest 的点超时了。可能有的人做到这就走了，因为这样已经相当于赛中 AC 了。但是我们不能这么想，这只能说明造数据的人太水了对吧。

这个时候我们发现有很多状态被重复搜索到了。大部分题解在这一步使用的是状压记录状态，然后记忆化。然而我 ~~由于最近被哈希题折磨~~ 选择了哈希。开两个集合 $s1,s2$，将第一个人必胜的状态放入 $s1$，第二个人必胜的状态放入 $s2$。状态怎么记录呢？哈希。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,vis[20],mod=998244353;
vector<int> G[20];
string s[20];
set<int> s1,s2;
int KSM(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}
bool dfs(int x,int stp,int hs){
	hs=(hs+KSM(13331,x)%mod)%mod;
    	//哈希
	if(s1.count(hs)) return 1;
	if(s2.count(hs)) return 0;
    	//记忆化
	bool ck=stp^1;
	for(int v:G[x]){
		if(vis[v]) continue;
		vis[v]=1;
		if(stp==1) ck|=dfs(v,stp^1,hs);
		else ck&=dfs(v,stp^1,hs);
      		//有一个必胜策略则必胜
		vis[v]=0;
		if(stp&&ck) break;
		else if(!stp&&!ck) break;
        	//当前已经有必胜策略的剪枝
	}
	if(ck) s1.insert(hs);
	if(!ck) s2.insert(hs);
    	//记忆化
	return ck;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j||s[i][s[i].size()-1]!=s[j][1]) continue;
			G[i].push_back(j);
		}
	}
	for(int i=1;i<=n;i++) G[0].push_back(i);
	bool ans=dfs(0,1,0);//0点出发
	cout<<(ans?"First":"Second")<<endl;
	return 0;
}
```

---

## 作者：Windy_Hill (赞：0)

## 题意
两个人正在玩游戏，有 $n$ 个字符串，两房可以轮流取，规则是当前这个人取的字符串的首字母必须与上一个人取的字符串的最后一个字母相同，当两个人都足够智慧时，谁会赢？

注意：**第一个人在第一次取时可以任意取**。

## 思路
既然两个人都不是那种很愚蠢的人（~~s*~~），那么他会尽可能的让自己赢，当前这步只要有赢得可能，那么一定会选这个字符串使他赢。

所以，我们考虑用搜索这种方法，枚举两个人的走法。

时间复杂度应该是 $O(16!)=O(20,922,789,888,000)$ 应该会炸飞，但是吃不满，因为会在中途返回，复杂度吃不满，所以还是过了。

## 代码
```
#include <bits/stdc++.h>

using namespace std;

bool st[200010];
string s[200010];
vector<int> str[200010];

bool check(int u, int x)//u:第几步，x:谁在操作
{
    st[u] = true;//用过1

    for (int i = 0; i < str[u].size(); i ++ )
    {
        if (st[str[u][i]] == true) continue;//判断有没有用过
        bool z = check(str[u][i], 3 - x);
        if (x == 1)
            if (z == true)
            {//第一个人只要有可能赢，这盘他就赢了
                return true;
            }
        if (x == 2)
            if (z == false)
            {//第二个人只要有可能赢，这盘他就赢了
                return false;
            }
    }
    
    if (x == 1) return false;
    else return true;
}

int main()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i ++ ) cin >> s[i];

    //建图
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ )
            if (i != j)
                if (s[i][s[i].size() - 1] == s[j][0])//判断尾字母是否等于首字母
                    str[i].push_back(j);

    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <= n; j ++ ) st[j] = false;//初始化
        if (check(i, 1) == false)
        {
            cout << "First";
            return 0;
        }
    }

    cout << "Second";

    return 0;
}
```

---

## 作者：xiaoPanda (赞：0)

## Solution
简单状态压缩，考虑设 $f_{S,i}$ 表示状态为 $S$ 并且当前要求一个开头为 $s_i$ 的结尾字符的单词，$\text{First}$ 如果能赢为 $0$，否则为 $1$。

那么很明显有 

$$f_{S|2^{j-1},j}=[f_{S,i}=0]\times[end_i=begin_j]$$

枚举 $S,i,j$ 即可，时间复杂度为 $O(2^nn^2)$ ,注意最后如果存在 $f_{2^{i-1},i}=1$ 代表 $\text{First}$ 赢，否则代表 $\text{Second}$ 赢。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
using db=double;
using ll=long long;
using vi=vector<int>;
using pii=pair<int,int>;
using ull=unsigned long long;
#define ft first
#define sd second
#define gc getchar
#define pb push_back
#define emp emplace_back
#define mp make_pair
#define sz(a) (int)a.size()
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define lowbit(x) ((x)&(-x))
#define int long long
const int N=1e5+7;
const int mod=1e9+7;
const int INF=(1ll<<60);
const int inf=1e9;
const int K=5e5+1;
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<3)+(r<<1)+(ch^48),ch=getchar();
	x=r*w;
}
void write(int x) {
	char ch[20];
	int len = 0;
	if (x < 0)putchar('-'), x = -x;
	while (x) {
		ch[len++] = (x % 10) ^ 48;
		x /= 10;
	}
	if(len==0)printf("0");
	while (len--)putchar(ch[len]);
	puts("");
}
char s[N];
int x[N],y[N];
bool f[N][30];
signed main()
{
	int n;
	read(n);
	FOR(i,1,n)scanf("%s",s+1),
	x[i]=s[1]-'a'+1,y[i]=s[strlen(s+1)]-'a'+1;
	ROF(S,(1ll<<n)-1,1)
	{
        FOR(i,1,n)
            if(S>>(i-1)&1) 
                FOR(j,1,n)                
                {
                    if(S>>(j-1)&1)continue;
                    int t=S|1ll<<(j-1);
                    if(y[i]==x[j]&&f[t][j]==0) 
                    	f[S][i]=1;
                }
    }
    FOR(i,1,n)
    {
        if(!f[1ll<<(i-1)][i]) 
        {
        	puts("First");
        	return 0;
        }
    }
    puts("Second");
    return 0;
}
```

---

## 作者：MMXIandCCXXII (赞：0)

## 思路
这道题 $n$ 非常小，可以用状压做，不过我用的是剪枝的深搜。思路很简单，三个参数：上一个字符串，当前该谁选，记录当前选了的字符串的头尾，作用等会讲。

枚举下一个字符串，如果不能接上或用过了，换下一个。如果选了的字符串头尾接起来的串重复了也要换（头尾重复即使顺序不同结果也一样）。
注意，因为递归下去要换成对手选，所以返回回来的胜负要取反。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, len[20];
string s[20];
bool flag[20];

map <string, bool> mp;

bool dfs(int u, int now, string str)
{
	mp[str] = true;
	bool win = false;
	for (int i = 1; i <= n; i++)
	{
		if (u != 0 && s[i][0] != s[u][len[u] - 1]) continue;
		if (flag[i]) continue;
		if (mp[str + " " + s[i][0] + s[i][len[i] - 1]]) continue;
		flag[i] = true;
		win |= !(dfs (i, 3 - now, str + " " + s[i][0] + s[i][len[i] - 1]));
		flag[i] = false;
		if (win)
			return true;
	}
	return false;
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i], len[i] = s[i].size ();
	for (int i = 1; i <= n; i++)
		if (dfs (0, 1, ""))
		{
			puts ("First");
			return 0;
		}
	puts ("Second");
	return 0;
}
```

---

