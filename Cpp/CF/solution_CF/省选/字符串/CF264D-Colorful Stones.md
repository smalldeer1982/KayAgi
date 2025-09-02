# Colorful Stones

## 题目描述

There are two sequences of colorful stones. The color of each stone is one of red, green, or blue. You are given two strings $ s $ and $ t $ . The $ i $ -th (1-based) character of $ s $ represents the color of the $ i $ -th stone of the first sequence. Similarly, the $ i $ -th (1-based) character of $ t $ represents the color of the $ i $ -th stone of the second sequence. If the character is "R", "G", or "B", the color of the corresponding stone is red, green, or blue, respectively.

Initially Squirrel Liss is standing on the first stone of the first sequence and Cat Vasya is standing on the first stone of the second sequence. You can perform the following instructions zero or more times.

Each instruction is one of the three types: "RED", "GREEN", or "BLUE". After an instruction $ c $ , the animals standing on stones whose colors are $ c $ will move one stone forward. For example, if you perform an instruction «RED», the animals standing on red stones will move one stone forward. You are not allowed to perform instructions that lead some animals out of the sequences. In other words, if some animals are standing on the last stones, you can't perform the instructions of the colors of those stones.

A pair of positions (position of Liss, position of Vasya) is called a state. A state is called reachable if the state is reachable by performing instructions zero or more times from the initial state (1, 1). Calculate the number of distinct reachable states.

## 说明/提示

In the first example, there are five reachable states: (1, 1), (2, 2), (2, 3), (3, 2), and (3, 3). For example, the state (3, 3) is reachable because if you perform instructions "RED", "GREEN", and "BLUE" in this order from the initial state, the state will be (3, 3). The following picture shows how the instructions work in this case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF264D/ff8e8d184349ca742f85291d5c556a28aebdf7a7.png)

## 样例 #1

### 输入

```
RBR
RGG
```

### 输出

```
5
```

## 样例 #2

### 输入

```
RGBB
BRRBRR
```

### 输出

```
19
```

## 样例 #3

### 输入

```
RRRRRRRRRR
RRRRRRRR
```

### 输出

```
8
```

# 题解

## 作者：FlashHu (赞：12)

神仙思维题。

对于两个字符串的匹配问题，似乎之前蒟蒻写的[HAOI2010最长公共子序列题解](https://www.cnblogs.com/flashhu/p/9572132.html)中提到的建网格图模型是一种套路？

给一个稍微强一点的样例（把字母换成了ABC）
```cpp
AABCB
BACBA
```
它所对应的网格图如下（横轴代表$s$，纵轴代表$t$，显示的点表示可达状态）

![](https://cdn.luogu.com.cn/upload/image_hosting/7n92j08c.png)

我们首先可以大致确定，所有的可达状态在一个不规则图形的界内
（红色线条）。第$i$行（或列）的界是$[l_i,r_i]$，而且类似two pointers，$l_i$和$r_i$都随$i$单调不降。拐角的顶点$(x,y)$出现在前缀$s_x$和前缀$t_y$第一次匹配到其中一个是另一个的子序列的地方。

那么是不是这个界里面的状态都可达呢？显然不是，我们还可以看到这样的位置（中间有三个）：如果$s_x=t_{y-1}\neq s_{x-1}=t_y$的话，$(x,y)$也会不可达。对应的两个子串形如`AB`和`BA`，蒟蒻接下来把该状态记作AB-BA。

仔细观察一下（~~或者打个表~~），除了这种情况，还有没有别的情况也是在界内却不可达的？貌似找不到啊。。。。。。

实际上，我们大概可以证明，在这个界内有且仅有AB-BA状态不可达。

图中的若干有向边从前驱节点指向后继节点。显然如果一个状态不可达，那么要么它没有前驱，要么它的所有前驱都不可达。

首先，一个节点没有前驱的情况就只有AB-BA那一种。当$s_x=t_y$时，我们可以肯定$(x,y)$有前驱，随手画画就可以发现。

于是现在我们就需要证明，如果一个点不可达，那么它一定没有前驱，而不会出现它有前驱且前驱不可达。反证法，我们现在开始判定一个在界内的有前驱的节点$(x,y)$，并假设它和它的前驱都不可达。

1. 它的前驱中有一个是$(x-1,y-1)$。刚刚已经得出$(x-1,y-1)$有前驱，那么我们又需要假设$(x-1,y-1)$的前驱不可达。
2. 它的前驱中没有$(x-1,y-1)$。则它的前驱可能有$(x-1,y)$、$(x,y-1)$。如果$(x-1,y)$有前驱，那么我们又需要假设$(x-1,y)$的前驱不可达；如果$(x-1,y)$没有前驱，那么说明出现了AB-BA状态，则一定会有$(x-1,y-1)$到$(x,y)$的边，不符合设定。对$(x,y-1)$的讨论同理。

于是，我们如果要假设某个点的所有前驱都不可达，我们必须假设它的某一个前驱的所有前驱都不可达，接着是前驱的前驱的前驱。。。。。。这个过程中$x,y$在递减，而最终$(x,y)$到了边界上。显然边界上的点都是可达状态（从$(0,0)$出发形成一条轮廓状路径），于是所有的假设都被推翻了。

思路清晰了以后，代码就简单了，只需要注意些细节。动态匹配子序列，维护$l,r$，还有对不同的状态记前缀和，这些都没什么好说的了。

```cpp
#include<bits/stdc++.h>
#define RG register
#define R RG int
using namespace std;
const int N=1e6+9;
char s[N],t[N];
int f[N][8];
int main(){
    R n=0,m=0,x,y,l=0,r=0;
    RG long long ans=0;
    scanf("%s%s",s,t);
    for(n=0;s[n];++n)s[n]%=3;//只是凑巧发现RBG%3的余数不一样
    for(m=0;t[m];++m)t[m]%=3;
    for(x=1;x<n;++x){
        memcpy(f[x],f[x-1],32);//前缀和
        if(s[x-1]!=s[x])
            ++f[x][(s[x-1]>s[x])*4+s[x-1]+s[x]];
    }
    memcpy(f[n],f[n-1],32);
    for(y=0;y<m;++y){
        if(y&&t[y-1]!=t[y]){//注意边界
            x=(t[y-1]<t[y])*4+t[y-1]+t[y];
            ans-=f[r][x]-f[l][x];
        }
        while(r<n&&s[r]!=t[y])++r;
        ans+=r-l+1-(r==n);//同样注意边界
        if(r<n)++r;
        if(l<r&&s[l]==t[y])++l;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：王鲲鹏 (赞：6)

部分借鉴了官方题解和[这篇](https://www.cnblogs.com/lishuyu2003/p/11502858.html)，~~甚至还剽了他的图~~。

考虑如果现在有一个起始状态和终止状态，想知道能不能构造出一个串 $I$ 到达终止状态：
![CF162D1.png (600×240) (codeforces.com)](http://assets.codeforces.com/images/162/CF162D1.png)

图中 $A,C$ 是要走过的位置，如果能走到，要满足

- $A$ 是 $I$ 的子序列且 $B$ 不是；
- $C$ 是 $I$ 的子序列且 $D$ 不是。

能构造出 $I$ 的一个必要条件是 $B$ 不是 $C$ 的子序列 且  $D$ 不是 $A$ 的子序列。（不妨叫它**条件1**。）但计数要用充分必要条件，所以我们需要看一看它是不是充分的。（先举个反例：A="GBG"，B="GBGB"，C="BGB"，D="BGBG"。）

把这个状态记作 $(A,B,C,D)$，令 $A'$ 为 $A$ 去掉第一个字符后的串，其他类似。

![CF162D2.png (600×240) (codeforces.com)](https://assets.codeforces.com/images/162/CF162D2.png)

分情况讨论一下，

* 若 $c1=c2$，只要构造一位 $c1$，就转移到状态 $(A',B',C',D')$，一定满足**条件1**；
* 若 $c1\not=c2$，
  - $B'$ 不是 $C'$ 的子序列，构造一位 $c1$，转移到状态 $(A',B',C,D)$；
  - $D'$ 不是 $A'$ 的子序列，构造一位 $c2$，转移到状态 $(A,B,C',D')$；
  - 都不满足，这种情况不合法（比如上面给出的反例）。

重点关注不合法的情况。手玩几个就会发现，一定是形如 A="...y"，B="...yx"，C="...x"，D="...xy"。统计一下这个的数量，前缀和优化一下。

所以答案就是满足**条件1**的且$B$ 以xy结尾时，$D$ 不以yx结尾。

考虑在 $s$ 串中走到了 $i$ （站在 $i$ 处，匹配完了前 $i-1$ 个），可以维护出一个区间 $[l,r]$ 表示在 $t$ 串中最少/最多站到哪个位置。则 $[l,r]$ 中排除掉不合法的就是这一次的答案。

代码：

```cpp
#include <cstdio>
#include <cstring>
int const maxn = 1000003;
int n = 0, m = 0;
char a[maxn], b[maxn];
int s[3][3][maxn];

int main() {
	scanf("%s%s", a + 1, b + 1);
	n = strlen(a + 1);
	m = strlen(b + 1);
	for (int i = 1; i <= n; ++i) a[i] %= 3;
	for (int i = 1; i <= m; ++i) b[i] %= 3;
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			for (int i = 2; i <= m; ++i) {
				s[x][y][i] = s[x][y][i - 1];
				if (b[i - 1] == x && b[i] == y) ++s[x][y][i];
			}
	int l = 1, r = 1;
	while (r < m && b[r] != a[1]) ++r;
	long long ans = r - l + 1; // 这一次不用排除什么
	for (int i = 2; i <= n; ++i) {
		if (l <= m && a[i - 1] == b[l]) ++l;
		if (l > m) break;
		if (r < m) {
			++r;
			while (r < m && b[r] != a[i]) ++r;
		}
		if (l > r) continue;
		int x = a[i - 1], y = a[i];
		ans += r - l + 1;
		if (x != y) ans -= s[y][x][r] - s[y][x][l - 1];
	}
	printf("%lld", ans);
	return 0;
}
```



---

## 作者：Cry_For_theMoon (赞：4)

用网格图那个巨佬很神，讲的很好%%%

首先钦定 $s$ 中走到 $x$，不难发现我们可以用双指针求出 $t$ 中最小/最大的 $y$ 满足 $(x,y)$ 可达，记为 $l_x,r_x$。首先我们大胆猜测 $y\in[l_x,r_x]$ 都满足 $(x,y)$ 可达。测样例后发现假了。

那我们就看是哪里出了问题。

我们研究 $s$ 中位置 $(x-1)$ 和 $x$，以及 $t$ 中位置 $(y-1)$ 和 $y$。

如果 $(x,y)$ 可达，等价于至少 $(x-1,y-1)$ 或者 $(x-1,y)$ 或者 $(x,y-1)$ 是可达的。

考虑一个 $y\in (L_{x-1},R_{x-1}]]$，每次 $y=L_{x-1}$ 我们特殊考虑，因为它的前驱并不满足 $(x-1,y-1)$ 可达，而其它的 $y$ 满足 $(x-1,y-1)$ 可达

当 $x,y$ 位置字符相同。$(x,y)$ 可达。可以通过大力分类讨论解决。

当 $x,y$ 位置字符不同，经过大力分类讨论，我们得到一种唯一的情况：

$s,t$ 分别以形如 $RG,GB$ 的形式作为 $s$ 的 $x$ 前缀和 $t$ 的 $y$ 前缀的结尾时，$(x,y)$ 不可达，即：

$$s=......RG$$

$$t=...GR$$

这样，$s,t$ 末尾就不可能同时到达。

但是这种不可达性不会影响后续的 $(x+1,y)$。因为 $(x+1,y+1),(x,y-1),(x-1,y)$ 都是可达的，用这三个状态走几步，就会发现那个 $(x,y)$ 不可达，不会让其他非 $RG-GR$ 形式结尾的状态也变得不可达。

所以对 $s$ 的末尾两个字符的 $9$ 种情况，分别对出现次数作前缀和即可。

时间复杂度 $O(n)$。我带个常数 $9$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e6+10;
int n,m;
char s[MAXN],t[MAXN];
int a[MAXN],b[MAXN];
int sum[9][MAXN];
int qry(int* s,int l,int r){
    if(l>r)return 0;
    if(l==0)return s[r];
    return s[r]-s[l-1];
}
ll ans;
int main(){
    scanf("%s%s",s+1,t+1);
    n=strlen(s+1);
    m=strlen(t+1);
    rep(i,1,n)a[i]=s[i]%3;
    rep(i,1,m)b[i]=t[i]%3;
    rep(i,2,n){
        rep(j,0,8)sum[j][i]=sum[j][i-1];
        sum[a[i-1]*3+a[i]][i]++;
    }
    for(int i=1,l=1,r=1;i<=m;i++){
        //拓展r
        while(r+1<=n && a[r]!=b[i])r++;
        ans+=(r-l+1);
        if(i>1 && b[i]!=b[i-1])ans-=qry(sum[b[i]*3+b[i-1]],l,r);
        if(a[l]==b[i]){
            l++;
            if(l>n)break;
        }
        if(r<n)r++;
    }
    printf("%lld",ans);
    return 0;
}
```

---

