# [ABC225F] String Cards

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc225/tasks/abc225_f

カードが $ N $ 枚あり、$ i $ 番目のカードには文字列 $ S_i $ が書かれています。

この中からちょうど $ K $ 枚選び、好きな順序で繋げてできる文字列のうち辞書順最小のものを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ |S_i|\ \leq\ 50 $
- $ S_i $ は英小文字からなる

### Sample Explanation 1

カードの中に書かれている文字を、反転させたり並び替えたりすることはできません。 たとえば $ 1 $ 枚目のカードに書かれている `ode` を、`edo` や `deo` のように使うことはできません。

### Sample Explanation 2

$ S_i\ =\ S_j $ を満たす $ i,j(i\neq\ j) $ の組が存在することもあります。

## 样例 #1

### 输入

```
4 3
ode
zaaa
r
atc```

### 输出

```
atcoder```

## 样例 #2

### 输入

```
5 2
z
z
zzz
z
zzzzzz```

### 输出

```
zz```

# 题解

## 作者：wbwone1 (赞：4)

# ABC225F 题解

## 思路

对于两个串 $A$ 和 $B$，定义 $A+B$ 表示将 $B$ 串接在 $A$ 的后面，$A<B$ 表示 $A$ 的字典序比 $B$ 小。

我们想对这些字符串进行排序，使排序后的数组中任意两个字符串 $S_i,S_j(i<j)$，都满足 $S_i+S_j<S_j+S_i$。

写成代码是这样的：

```c++
bool cmp(string a,string b){
	return a+b<b+a;
}
string s[N];
sort(s+1,s+1+n,cmp);
```

但是，一般的排序，比如大于小于，都是通过相邻项之间关系的传递性，使任意两项之间都具有这个性质，而上面的东西，从表面上看很难知道是否有传递性。

不妨把这些仅包含小写字母的字符串写成 $26$ 进制数，$0$ 代表 $a$，$1$ 代表 $b$，以此类推。

设 $S_i$ 对应的数为 $a$，$S_j$ 对应的数为 $b$，$S_i$ 的长度为 $len_1$，$S_j$ 的长度为 $len_2$，则上面的关系可以写成：

$a\cdot 26^{len2}+b<b\cdot 26^{len_1}+a$

移项：

$a(26^{len_2}-1)<b\cdot (26^{len_1}-1)$

显然 $len_1,len_2$ 都不为 $0$，于是可以除：

$\frac{a}{26^{len_1}-1}<\frac{b}{26^{len_2}-1}$

于是你惊喜的发现：这个式子的两边只和 $S_i,S_j$ 本身相关！这个排序也是有传递性的！

排好序的数组又有什么好处呢？

假设我们已经知道字典序最小的串由 $S_{a_1},S_{a_2},\cdots,S_{a_K}$ 以某种顺序拼成，其中 $1 \leq a_i \leq n,a_i\neq a_j(i\neq j)$，现在要确定一个拼接顺序，使最终组成的串字典序最小。

结论是：只有在 $a_i$ 递增时，字典序最小。

证明：反证法。

假设存在 $1 \leq i<K$，满足 $a_i>a_{i+1}$，在排完序的数组中，显然有 $S_{a_{i+1}}+S_{a_i}<S_{a_i}+S_{a_{i+1}}$，而且在拼起来的串中，这两个串交换对其他的部分没有影响，所以把 $S_{a_{i+1}}$ 放在 $S_{a_i}$ 前面更优，矛盾。

现在只需要枚举每个串选不选，再把选了的按顺序拼起来就行了，于是可以用 DP 解决。

设 $f[i][j]$ 表示后 $i$ 个串中，取了 $j$ 个串拼起来字典序最小的串，可以得到状态转移方程：

$f[i][j] = \min(f[i+1][j],s[i]+f[i+1][j-1])$

答案就是 $f[1][K]$。

时间复杂度 $O(NK^2L)$，其中 $L$ 是所有 $S_i$ 中长度的最大值。

这道题巧妙的地方在于用排序解决了重排的问题，大大降低了时间复杂度。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
int n,k;
string s[N],f[N][N];
bool cmp(string a,string b){
	return a+b<b+a;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>k;
	for (int i=1;i<=n;i++) cin>>s[i];
	sort(s+1,s+1+n,cmp);
	for (int i=n;i>=1;i--){
		for (int j=1;j<=k;j++) f[i][j].insert(0,"{"); //{ 是 ASCII 中比 z 大的第一个字符
		if (i == n){
			f[i][1] = s[i];
			continue;
		}
		for (int j=1;j<=k;j++) f[i][j] = min(s[i]+f[i+1][j-1],f[i+1][j]);
	}
	cout<<f[1][k]<<endl;
	return 0;
}
```

---

## 作者：hyxgg (赞：3)

# 前言
发现其他所有题解都是 `DP`，实际上这题只需要一个贪心。

# 思路
## 假作法
老师看错难度把这题放到模拟赛的签到题，以至于我随意看了一眼后把字符串排了序后直接顺次输出。

发现过不了样例：
```
3 2
baa
ba
b
```

## 尝试解决
### 问题
问题出在哪？

最小字符串为 $S$，记含有其作为前缀的字符串 $S+A=SA$，$A$ 为字符串中除前缀 $S$ 外的部分。

发现可能出现 $A$ 比 $S$ 外所有字符串都小的情况，放到样例中就是 `aa` $\lt$ `ba`。

### 解决方案
如何解决？

首先，无论我们选什么，$S$ 的前缀必然不会变，于是答案可以先加上一个 $S$。

采用类似反悔贪心的思想，看能不能将 $A$ 转化成新的字符串，再和其他的字符串作比较。

如果我们下一个字符串选了 $A$，则意味着我们的第一个字符串从 $S$ 换成了 $SA$，但是我们其实是在第二轮选了 $A$，所以 $A$ 后还应选一个字符串接着，又因为 $S$ 是最小的字符串，所以 $A$ 后接着的必然是 $S$。

于是对于 $SA$，将其变为 $AS$ 。

以上操作重复 $k$ 遍即可。

### 新的问题已经出现~
交上去发现并不行，发现 $SA$ 本身也可作为下一个字符串接在后面，不能直接将其变为 $AS$，而开一个新的字符串则会导致空间时间双双阵亡。
## 真正做法
其实解决这个问题也很简单，无论是 $SSA$ 还是 $SAS$ 都只涉及到 $S$ 和 $SA$，长度也一样，选哪个都不会对其他的字符串及后面的选择产生影响，于是在这里直接贪心地选择 $SA$ 和 $AS$ 中更小的那个作为新的字符串即可。
# 时间复杂度
- 一找共 $k$ 个字符串，时间复杂度为 $\mathcal{O}(k)$。

- 每轮一个排序找 $S$，时间复杂度为 $\mathcal{O}(n\log{n})$。

- 然后找 $SA$，遍历找，逐字比较即可，更改也一个一个字符加即可，时间复杂度为 $\mathcal{O}(n\left|S\right|)$。

于是总的时间复杂度为 $\mathcal{O}(kn\log{n}+kn\left|s\right|)$，题目中 $n$，$\left|S\right|$，$k$ 均小于 $50$，轻松通过。
# 代码
代码很清晰，不写注释了，有问题评论区见。
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
struct yc
{
    string s;
    bool bj;
}yy[5005];

string ans;
ll n,k,dd=1;
bool cmp(yc a,yc b){
    return a.bj==b.bj?a.s<b.s:a.bj<b.bj;
}
void yb(){
    sort(yy+1,yy+1+n,cmp);
    ans+=yy[1].s;
    ll dn=yy[1].s.size();
    yy[1].bj=1;
    ll i;
    ll nn=n;
    for(i=2;i<=n;i++){
        if(yy[i].bj)break;
        bool p=0;
        for(ll j=0;j<dn;j++){
            if(yy[i].s[j]!=yy[1].s[j]){
                p=i;break;
            }
        }
        if(p){
            break;
        }
        string ns;
        ns.clear();
        ll id=yy[i].s.size();
        for(ll j=dn;j<id;j++){
            ns+=yy[i].s[j];
        }
        yy[i].s=(yy[i].s>(ns+yy[1].s))?ns+yy[1].s:yy[i].s;
    }
    n=nn;

}
int main(){
    scanf("%lld%lld",&n,&k);
    for(ll i=1;i<=n;i++){
        cin>>yy[i].s;
    }
    while(k){
        yb();
        k--;
        dd++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Z1qqurat (赞：3)

这个题简直是泰裤拉！至少它在字符串字典序这方面给了我很大启发。

* 首先不难想到一种显然又错误的做法：将这 $n$ 个字符串按字典序排序，然后将前 $k$ 个拼起来，就是答案。看起来没啥问题，但是如果给出的两个字符串分别是 $\tt b, ba$ 且 $k = 2$，那么按这种直接排序的做法，得到的是 $\tt bba$，但是更优的有 $\tt bab$。这是为什么会出错呢？因为当我们比较的两个字符串 $s, t$  长度不相等时，字典序的大小会受到后面拼接上的字符串的影响，也就是说我们不能直接比较 $s, t$，我们需要通过对拼接后的比较来确定优劣。

* 这启示我们得出一个这样的比较方式：比较 $s, t$ 在拼接过程中谁放在前面更好，也就是比较 $s + t$ 和 $t + s$ 的字典序。如果 $s + t < t + s$，那么 $s$ 放在 $t$ 前面肯定更优（但是我不太能理解严谨的证明？个人体感就是像普通的数大小排序一样，字典序它也是有一个大小关系的传递性的）。

* 现在我们按新的方式对字符串排序之后，剩下的就是 dp 了。不难想到状态 $f_{i, j}$ 表示从前 $i$ 个字符串中选择了 $j$ 个时得到的字典序最小的字符串。那么显然转移就是 $f_{i, j} = \min (f_{i - 1, j}, f_{i - 1, j - 1} + s_i)$，答案就是 $f_{n, k}$。但是你会发现一个问题，这个转移还是可以被类似上一个例子的数据轻松卡飞，因为当你比较这两种选择时，你只是比较了它们目前的字典序，而无法确定之后加上新的字符串之后的字典序大小关系，也就是说你仍然受到字符串长度不等的影响。所以考虑倒着 dp，这样你每次是往前面接字符串，后缀的形态时确定了，就不会再影响到后续的拼接了（这，莫名，让我想起了，写图上期望 dp 时努力写正推然后样例都模拟错了的我）。所以我们定义 $f_{i, j}$ 表示后 $i$ 个字符串中选择了 $j$ 个能组成的字典序最小的字符串，转移就是 $f_{i, j} = \min(f_{i + 1, j}, s_i + f_{i + 1, j - 1})$。最后的答案就是 $f_{1, k}$。注意初始化初始化初始化！初始的时候所有的 $f$ 都设成一个字典序极大的字符串，$f_{i, 0}$ 设为空串就行了！（为了避免一些越界我把 $f_n$ 单独处理了，还把 $f_{n, 1}$ 设为了 $s_n$）。

纯野生代码！

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 55;
int n, k;
string a[N], f[N][N], inf;

bool cmp(string s, string t) {
    return (s + t) < (t + s);
}

string Min(string s, string t) {
    return (s < t) ? s : t;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i], inf = inf + 'z';
    inf += "zzz";
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i) {
        fill(f[i], f[i] + n + 1, inf);
        f[i][0] = "";
    }
    f[n][1] = a[n];
    for (int i = n - 1; i >= 1; --i) {
        for (int j = 1; j <= min(k, n - i + 1); ++j) {
            f[i][j] = Min(f[i + 1][j], a[i] + f[i + 1][j - 1]);
        }
    }
    cout << f[1][k] << "\n";
    return 0;
}
```

---

## 作者：Motonic_queues (赞：2)

首先很容易想到这一题：[P1012](https://www.luogu.com.cn/problem/P1012)。  
这一题里面用到了一个贪心策略：按照这个方式排序
$$ a+b>b+a $$  
于是一开始的思路直接照做，排完序取前 $k$ 个，然后喜提 WA。  

考虑一下问题出在哪，很显然，P1012 最终得到的字符串长度是固定的，但本题不是，比如下面这组数据，就会因为答案字符串的长度而寄：  

```markdown
3 2
bba
bb
bba
```
按照原先的思路会这样排序：`bba bba bb`，然后就挂了。  

那就 DP 吧。  

不难想到状态 $dp_{i,j}$ 是考虑到第 $i$ 个字符串时取 $j$ 个字符串的答案，但因为如果考虑的是 $[1,i]$ 的话仍然会被字符串长度背刺，而考虑 $[i,n]$ 就没问题了。  

但在转移前我们首先要排序，这样可以更方便的求出答案，这种技巧叫做 `exchange argument`，用和 P1012 一样的方式就行了。  
转移很简单，每个字符串选或不选，有
$$ dp_{i,j}=\min(s_i+dp_{i+1,j-1},dp_{i+1,j}) $$  
只用考虑把 $s_i$ 放在 $dp_{i+1,j-1}$ 前面的情况就够了，由于我们排过序，所以 $dp_{i+1,j-1}+s_i$ 一定大于 $s_i+dp_{i+1,j-1}$。  
同时也有边界条件 $dp_{n,1}=s_n$。

记得初始化。

---

## 作者：CQ_Bab (赞：2)

# 前言
有一句话逻辑不太对，改了一下。
# 思路
乍一看，这道题是不是觉得很简单，就是一个排序而已。但是有一种数据就能把它卡掉，例如：
```
2 2
b
ba
```
所以我们就用动态规划来解决它，我们可以令 $f_{i,j}$ 等于从 $i\sim n$ 中取 $j$ 个的最小排列，然后我们就能发现好像需要排序，那么怎么排呢？我们其实只需要按照能够有效保留一个相对大小关系并且不会出现以上情况的一种排序方式就行了，那么就为 $S_i+S_{i+1}<S_{i+1}+S_i$。

那么状态转移方程是什么呢？我们发现 $f_{i,j}$ 只能从 $f_{i+1,j}$ 以及 $f_{i+1,j-1}$ 推导过来，然而 $f_{i+1,j-1}$ 我们还需要加上一个 $S_i$ 并且 $S_i$ 是加在 $f_{i+1,j-1}$ 前面的哦，然后将这两个取个最小值即可，但是有一个问题就是 $f_{i+1,j}$ 不一定有值，所以还要特判一下即可。而且 $i$ 要是倒着循环的，毕竟前面说了 $S_{i}$ 要加在前面，最后的答案就为 $f_{1,k}$ 啦！
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(i,x,y) for(int i=x;i<=y;i++)
const int N=55;
string f[N][N],s[N];
int n,k;
#define rep1(i,x,y) for(int i=x;i>=y;--i)
bool cmp(string a,string b) {
	return a+b<b+a;
}
int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	rep(i,1,n) cin>>s[i];
	sort(s+1,s+1+n,cmp); //按照组合后的大小排序
	rep1(i,n,1) { //从前往后递归（越小的放在越前面）
		rep(j,1,n-i+1) {
			if(f[i+1][j]!="") f[i][j]=min(f[i+1][j],s[i]+f[i+1][j-1]); //特判
			else f[i][j]=s[i]+f[i+1][j-1];
		}
	}
	cout<<f[1][k]<<endl;
	return false;
}
/*
5 2
z
z
zzz
z
zzzzzz
*/
```

---

## 作者：sybs1145 (赞：2)

# [[ABC225F] String Cards](https://www.luogu.com.cn/problem/AT_abc225_f) 题解

## 思路
因为本蒟刚做过 [[NOIP1998 提高组] 拼数](https://www.luogu.com.cn/problem/P1012)。

所以写了一个 sort 就风风火火的交了（~~当时我还以为这道紫题是水题~~）……
```cpp
bool cmp(string A,string B)
{
    return A+B<B+A;
}
```
然后喜提满江红。

实际上这组数据就可以轻松的 hack 掉这段代码。

```
3 2
bba
bb
bba
```

所以这道题的正解其实是动态规划。

我们可以定义 $f_{i,j}$ 为在 $S_i$ 到 $S_n$ 中选取 $j$ 个字符串，得到的字典序最小的结果。

状态转移有两种情况，即选与不选。

即：
$$f_{i,j} = f_{i-1,j}\ \operatorname{or}\ f_{i,j} = S_i + f_{i-1,j-1}$$

题目要求我们求字典序最小的结果，所以最终的状态转移方程即为：
$$ f_{i,j} = \min(f_{i-1,j},S_i + f_{i-1,j-1}) $$
最终的结果即为 $f_{1,k}$。
## AC code
```cpp
#include <bits/stdc++.h>

using namespace std;

int n,k;
string s[55],f[55][55];

bool cmp(string A,string B)
{
    return A+B<B+A;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i = 1; i <= n; i++)
        cin>>s[i];
    sort(s+1,s+n+1,cmp);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= k; j++)
            f[i][j] = char('z'+1);  //初始化数组 f
    for(int i = n; i >= 1; i--)
    {
        if(n == i) //特判
        {
            f[i][1] = s[i];
            continue;
        }
        for(int j = 1; j <= k; j++)
            f[i][j] = min(s[i]+f[i+1][j-1],f[i+1][j]);
    }
    cout<<f[1][k];
    return 0;
}
```
## 2025.1.23 UPD：修正了一处笔误。

---

## 作者：xyloph0nex17 (赞：2)

先不考虑选哪些串拼起来最优，先考虑如果能选出多个串拼起来，怎么拼最优。  
直接 `sort` 拼起来显然不对，会被以下数据卡掉：  

```
2 2
ba
b
```

这个例子启发我们思考两个字符串的相对位置，若 $a + b < b + a$ 则 $a$ 应该排在 $b$ 前，考虑证明这个东西。  

将一个字符串看作一个 $bas$ 进制数，那么上式可以表示为：  

$$a \times {bas}^{|b|} + b < b \times {bas}^{|a|} + a$$  

移项可得  

$$\frac{a}{{bas}^{|a|}-1} < \frac{b}{{bas}^{|b|}-1}$$  

我们将一个二元的大小比较转化成了一个只与每个字符串自身有关的大小比较，因此显然按这种排序的大小关系具有传递性，即若 $a + b < b + a$，$b + c < c + b$，则 $a + c < c + a$。  

所以按这种方式排完序后交换任意两项都不会使得答案变得更优。注意到如果上式相等那么它们的先后顺序是被其它串决定的，因此不需要考虑相等的情况。

排完序后首先想到 dp 解决，设 $f_{i,j}$ 表示从前向后考虑到第 $i$ 个，已经加入了 $j$ 个字符串后的字典序最小的字符串，容易发现从前向后dp会因为字符串长度的原因存在后效性，那么考虑把状态转为从后往前 dp 考虑到第 $i$ 个，加入了 $j$ 个后字典序最小的字符串，这样每次转移时加在 $f_{i-1,j}$ 位置的最优字符串头的字符串长度是为固定 $|s_i|$ 的，因此不会影响它是 $f_{i-1,j}$ 时的最优字符串的事实，没有后效性。  

因为字符串长度为 $n^2$ 级别，所以 dp 复杂度还要乘上每次比较字符串的复杂度，总时间复杂度为 $O(n^4)$。

---

## 作者：ymx2009 (赞：1)

# 前言  
做这道题之前可以先去看看 [P1012](https://www.luogu.com.cn/problem/P1012)。  
# 思路  
想到特殊的排序方式。  
当且仅当 $s_i+s_j\le s_j+s_i$ 时，$s_i$ 排在 $s_j$ 的前面。  
然后就很容易陷入误区，并不是选排在最前面的就最优。
不理解就看下面这个例子：

```
3 2
za
z
za
```
排序后的顺序为 `za za z`，如果直接选前两个构成的字符串为 `zaza` 很明显不如 `zaz` 更优。  
所以我们考虑动态规划，设 $f_{i,j}$ 表示 $[i,n]$ 中取 $j$ 个字符串形成的字典序最小的字符串。  
状态转移方程为：
$$
f_{i,j}=\min(s_i+f_{i+1,j-1},f_{i+1,j})
$$
因为是排好序的，所以 $s_i+f_{i+1,j-1}$ 肯定比 $f_{i+1,j-1}+s_i$ 更优。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=60;
int n,k;
string s[N],f[N][N];
bool cmp(string x,string y){return x+y<y+x;}
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>s[i];
	sort(s+1,s+1+n,cmp);
	for(int i=1;i<=n+1;i++) for(int j=1;j<=k;j++) f[i][j]='~';//'~'是一个ASCII比'z'大的字符
	f[n][1]=s[n];
	for(int i=n-1;i>=1;i--)	for(int j=1;j<=k;j++) f[i][j]=min(s[i]+f[i+1][j-1],f[i+1][j]);
	cout<<f[1][k];
	return 0;
}
```

---

## 作者：LeavingAC (赞：1)

**begin**

# 思路

第一眼：建议降红。

第二眼：满江红。。。。。。。

首先我们可以想到一个看似正确实则错误的贪心思路：


```cpp
bool cmp(string a,string b){return a+b<b+a;}
```

在这组数据下直接被打爆：

```
input:
3 3
bab
bab
bb

example_output:
babbb

my_output:
babbab
```

基于以上思路我们继续将思维发散到动态规划。

我们定义 $f_{i,j}$ 为从 $S_i \sim S_n$ 中取 $j$ 个字符串组成的字典序最小的字符串。

那么显然有： 

$$f_{i,j}=\min(f_{i+1,j},S_i+f_{i+1,j-1})$$

边界条件：

$$f_{n,1}=S_n$$

最后答案：

$$f_{1,k}$$

### Tips

注意 $S_i$ 是加在前面的，而且我们要从后往前枚举 $i$。

# Code


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
ll n,k;
string s[60],f[60][60];
bool cmp(string a,string b){return a+b<b+a;}
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for (ll i=1;i<=n;i++) cin>>s[i];
    sort(s+1,s+n+1,cmp);
    for (ll i=1;i<=n;i++) for (ll j=1;j<=k;j++) f[i][j]=(char)('z'+1);
    for (ll i=n;i>=1;i--)
    {
        if (n==i)
        {
            f[i][1]=s[i];
            continue;
        }
        for (ll j=1;j<=k;j++)
        {
            f[i][j]=min(s[i]+f[i+1][j-1],f[i+1][j]);
        }
    }
    cout<<f[1][k];
    return 0;
}
```

**end**

---

## 作者：druzewang (赞：0)

第一眼：建议降红。

风风火火地交上去后发现并没有那么简单。

其实这道题很快就能看出来一个看起来正确的写法:

```cpp
bool cmp(string a,string b){
	return a + b < b + a;
} 
```
然后就 WA 了。。。。。。

其实这道题的正解其实是动态规划。

我们定义 $f_{i,j}$ 为从 $S_i$ 到 $S_n$ 中选取 $j$ 个字符串，得到的字典序最小的结果。

状态转移就会有选和不选两种情况。

题目要求我们求字典序最小的结果，所以最终的状态转移方程为：

$$f_{i,j} = \min(f_{i-1,j},f_{i-1,j-1} + S_i)$$

最终输出 $f_{1,k}$。 

**AC 代码**


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
string s[55],f[55][55];
bool cmp(string A,string B){return A+B<B+A;}
int main()
{
    cin>>n>>k;
    for(int i = 1; i <= n; i++)cin>>s[i];
    sort(s+1,s+n+1,cmp);//先排序 
    for(int i = 1; i <= n; i++)
		for(int j = 1; j <= k; j++)
			f[i][j] = char('z'+1);  //初始化数组 f
    for(int i = n; i >= 1; i--)
    {
        if(n == i) //特判
        {
            f[i][1] = s[i];
            continue;
        }
        for(int j = 1; j <= k; j++)
            f[i][j] = min(s[i]+f[i+1][j-1],f[i+1][j]);//转移方程 
    }
    cout<<f[1][k];//输出 
    return 0;//华丽收场
}
```

---

## 作者：qnqfff (赞：0)

### 思路

首先典中典排序使得对于任意 $i,j(i<j)$ 有 $s_i+s_j<s_j+s_i$，那么题目变成选 $k$ 个串按顺序接起来字典序最小，考虑设 $dp_{i,j,k}$ 表示考虑到第 $i$ 个串，选了 $j$ 个串，选的串的总长度为 $k$ 的答案，转移很简单 $dp_{i,j,k}=\min(dp_{i-1,j,k},dp_{i-1,j-1,k-siz_i}+s_i)$ 其中 $siz_i$ 表示 $s_i$ 的大小，空间有点爆，把 $i$ 滚动掉即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<23],*p1=buf,*p2=buf;
int read(){char c=getchar();int p=0,flg=1;while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m;string s[55],dp[2][55][2510];
signed main(){
	n=read();m=read();for(int i=1;i<=n;i++) cin>>s[i];sort(s+1,s+1+n,[&](auto x,auto y){return x+y<y+x;});
	string lim="";for(int i=1;i<=55;i++) lim+='z';for(int i=0;i<=1;i++) for(int j=0;j<=m;j++) for(int k=0;k<=2500;k++) dp[i][j][k]=lim;
	dp[0][0][0]=dp[1][0][0]="";for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) for(int k=0;k<=2500;k++){
		dp[i&1][j][k]=dp[i&1^1][j][k];
		if(s[i].size()<=k) dp[i&1][j][k]=min(dp[i&1][j][k],dp[i&1^1][j-1][k-s[i].size()]+s[i]);
	}string ans=lim;for(int i=0;i<=2500;i++) ans=min(ans,dp[n&1][m][i]);cout<<ans;
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

## part 1 弱化版

看到这道题的第一眼想到了 [P1012](https://www.luogu.com.cn/problem/P1012) 这道题。

但是，这两道题选择的数量是有区别的。

我们可以由拼数得出一个结论性的排序规则（这里就不多做解释了）：

```cpp
inline bool cmp(string a,string b){
	return a + b < b + a;
}
```

如果用这样的做法，有 [hack](https://www.luogu.com.cn/paste/zvhp92yi)。

## part 2 状态定义

我们首先可以定义状态 $dp_{i,j}$ 为在前 $i$ 个字符串中取 $j$ 个字符串字典序最小的结果。

我们便能很轻松的得出以下状态转移方程：

$$dp_{i,j} = \min(dp_{i - 1,j},dp_{i - 1,j - 1} + s_i)$$

但是，仔细一看就能发现一些问题：在你搞字典序最小的字符串时，是不是先确定前面的字符串再确定后面的字符串吗？计算机也是这样的。

所以，我们修改状态函数 $dp_{i,j}$ 表示在后 $i$ 个字符串中取 $j$ 个字符串字典序最小的结果。

状态转移方程为：

$$dp_{i,j} = \min(dp_{i + 1,j},s_i + dp_{i + 1,j - 1})$$

## part 3 整理

我们由拼数这道题可以再次得出一个结论：如果假设按照上述排序规则排序后，要使自字典序最小的字符串序列为 $s_{a_1},s_{a_2},\dots,s_{a_k}$，那么 $a$ 序列必定是严格单调递增的。

那么，这题何尝不是呢？

所以，我们要在执行 DP 前，按照上述排序规则排一次序。时间复杂度为：$\Theta(n\log n + nk)$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 60;
int n,k;
string s[N];
string dp[N][N];

inline bool cmp(string a,string b){
	return a + b < b + a;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for (re int i = 1;i <= n;i++) cin >> s[i];
	sort(s + 1,s + 1 + n,cmp);//排序 
	for (re int i = 1;i <= n;i++){//将 dp 数组初始化为正无穷 
		for (re int j = 1;j <= k;j++) dp[i][j] = "{";//因为 '{' 的 ASCII 码比 'x' 的大 
	}
	dp[n][1] = s[n];//状态起点 
	for (re int i = n - 1;i;i--){//转移 
		for (re int j = 1;j <= k;j++) dp[i][j] = min(dp[i + 1][j],s[i] + dp[i + 1][j - 1]);
	}
	cout << dp[1][k];
	return 0;
}
```

---

