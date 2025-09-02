# [ABC306F] Merge Sets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc306/tasks/abc306_f

$ A\ \cap\ B\ =\ \emptyset $ を満たす $ 2 $ つの整数の集合 $ A,\ B $ に対して、$ f(A,B) $ を以下のように定義します。

- $ A\ \cup\ B $ に含まれる要素を昇順に並べた数列を $ C=(C_1,C_2,\dots,C_{|A|+|B|}) $ とする。
- $ A=\lbrace\ C_{k_1},C_{k_2},\dots,C_{k_{|A|}}\rbrace $ となるような $ k_1,k_2,\dots,k_{|A|} $ をとる。 このとき、$ \displaystyle\ f(A,B)=\sum_{i=1}^{|A|}\ k_i $ とする。
 
例えば、$ A=\lbrace\ 1,3\rbrace,B=\lbrace\ 2,8\rbrace $ のとき、$ C=(1,2,3,8) $ より $ A=\lbrace\ C_1,C_3\rbrace $ なので、$ f(A,B)=1+3=4 $ です。

それぞれが $ M $ 個の要素からなる $ N $ 個の整数の集合 $ S_1,S_2\dots,S_N $ があり、各 $ i\ (1\ \leq\ i\ \leq\ N) $ について $ S_i\ =\ \lbrace\ A_{i,1},A_{i,2},\dots,A_{i,M}\rbrace $ です。 ただし、$ S_i\ \cap\ S_j\ =\ \emptyset\ (i\ \neq\ j) $ が保証されます。

$ \displaystyle\ \sum_{1\leq\ i\ <\ j\ \leq\ N}\ f(S_i,\ S_j) $ を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 10^4 $
- $ 1\leq\ M\ \leq\ 10^2 $
- $ 1\leq\ A_{i,j}\ \leq\ 10^9 $
- $ i_1\ \neq\ i_2 $ または $ j_1\ \neq\ j_2 $ ならば $ A_{i_1,j_1}\ \neq\ A_{i_2,j_2} $
- 入力は全て整数
 
### Sample Explanation 1

$ S_1,S_2 $ はそれぞれ問題文中で例示した $ A,B $ と一致し、$ f(S_1,S_2)=1+3=4 $ です。 $ f(S_1,S_3)=1+2=3,f(S_2,S_3)=1+4=5 $ であるため、$ 4+3+5=12 $ が答えです。

## 样例 #1

### 输入

```
3 2
1 3
2 8
4 6```

### 输出

```
12```

## 样例 #2

### 输入

```
1 1
306```

### 输出

```
0```

## 样例 #3

### 输入

```
4 4
155374934 164163676 576823355 954291757
797829355 404011431 353195922 138996221
191890310 782177068 818008580 384836991
160449218 545531545 840594328 501899080```

### 输出

```
102```

# 题解

## 作者：红火恍惚cxy (赞：3)

## ABC306_F Merge Sets 题解  

### 题意简述：  

给你 $N$ 个大小为 $M$ 的正整数集，两两之间交集为空。  

定义 $f(A,B)$ 为 $A \cap B$ 从小到大排序后，原 $A$ 中每个元素在新集合中的位置（下标）的和。  

求 $\sum\limits_{1 \leq i \leq j \leq N} f(S_i,S_j)$。  

$N \leq 10^4$，$M \leq 10^2$。  

### 题目分析：  

首先注意到 $f(A,B) \ne f(B,A)$，因此集合之间有先后之分。  

感觉位置和不是很好处理啊，我们想办法把答案转化一下。  

一个数在一个有序集合之中的位置，其实可以看成集合中比他小的数的个数加一。  

既然要算 $\sum f(S_i,S_j)$，那其实 $S_i$ 中一个数 $A_{i,j}$ 的贡献可以对多个 $S_j$ 拆开，即：  

$$1 + \text{ 在 } S_i \text{ 中比它小的数的个数 } + \text{ 在 } S_{i+1} \text{ 中比它小的数的个数 } + \cdots +  \text{ 在 } S_n \text{ 中比它小的数的个数 }$$  

题目转化成这样其实解决方法就很多了，这里提供我的做法。  

$1 + \text{ 在 } S_i \text{ 中比它小的数的个数 }$ 可以提前一起算出来，即：$\frac{(1+m) \times m}{2} \times C_n^2$。  

因为题目保证不出现重复数字，因此离散化后，只需要减掉在当前集合之前的个数即可。这里我使用了树状数组保存删掉的数。  

总复杂度 $O(nm\log(nm))$。  

### 完整代码：  

```c++
#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) ((x)&(-(x)))
using namespace std;
int n,m;
int cnt,tot;
int a[10004][102];
struct qwq{
    int val;
    int x,y;
}ss[1000006];
inline bool cmp(qwq x,qwq y){
    return x.val<y.val;
}
int tr[1000006];
inline void insert(int x){
    for(int i=x;i<=n*m;i+=lowbit(i)) tr[i]++;
    return;
}
inline int ask(int x){
    int re=0;
    for(int i=x;i;i-=lowbit(i)) re+=tr[i];
    return re;
}
int main(){
    scanf("%d%d",&n,&m);
    int x;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            scanf("%d",&x);
            ++cnt;
            ss[cnt].val=x;
            ss[cnt].x=i;
            ss[cnt].y=j;
        }
    }
    sort(ss+1,ss+cnt+1,cmp);
    for(int i=1;i<=n*m;++i) a[ss[i].x][ss[i].y]=i;
    ll ans=1ll*((1+m)*m/2)*n*(n-1)/2;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j) insert(a[i][j]);
        for(int j=1;j<=m;++j) ans+=a[i][j]-ask(a[i][j]);
    }
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：x某人 (赞：2)

# [ABC306F] Merge Sets 题解

## 题意简述

给定 $n$ 个大小为 $m$ 的集合(任意两个集合的数不重复)，每次选定两个集合 $S_i$，$S_j$ （$i<j$），将 $S_i$，$S_j$ 中的数加入到序列 $C$ 中并从小往大排序，算出在 $C$ 中原本属于集合 $S_i$ 的数在 $C$ 中的下标和 $ans_{i,j}$。最后答案为 $\sum\limits_{i=1}^{n-1} \sum\limits_{j=i+1}^n ans_{i,j}$。

## 解法

考虑到数据范围（$n\le10^4$），枚举两个集合再排序求答案肯定是不行的，所以我们可以换一种思路：计算一个集合中的一个数对另一个数的贡献。也就是说，**把原本集合对集合的贡献转化为数对数的贡献**。

根据题意可得，一个数 $p$ 小于 另一个数 $q$ 时，说明当这两数所属集合进行排列时 $p$ 会排在 $q$ 的前面，也就是说 $p$ 会使 $q$ 的排名 $+1$。

按照这种思路，我们可以分几种情况考虑（$i$ , $j$ 为任意两个集合，$x$ , $y$ 为两数在集合中的下标）：

* $a_{i,x}>a_{j,y}$，$a_{i,x}$ 不对 $a_{j,y}$ 产生贡献。
* $a_{i,x}<a_{j,y}$，$a_{i,x}$ 可能对 $a_{j,y}$ 产生贡献。

从第二种情况中再分为三类考虑：

* $i<j$，$a_{i,x}$ 对 $a_{j,y}$ 产生 $1$ 的贡献。
* $i>j$，$a_{i,x}$ 不对 $a_{j,y}$ 产生贡献。
* $i=j$，在每次与其他集合的计算中 $a_{i,x}$ 都会对 $a_{j,y}$ 产生 $1$ 的贡献，所以总贡献为 $(n-i)$。

于是做法就很清晰了。我们先记录一下每个数是属于哪个集合的，再对所有数从小到大排序，按顺序依次处理每个数。设 $sum_k$ 表示在集合 $k$ 中有多少个数字比当前数字小，当前数所属集合为 $i$，那前面的所有数对当前数的贡献是：$\sum\limits_{k=1}^{i-1} sum_k+sum_i\times(n-i)+(n-i)$。最后还要加一个 $(n-i)$ 是原本排名贡献的 $1$。$sum$ 的和用树状数组维护就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-(x)))
using namespace std;
int a[10005][105],c[10005],n,m,sum[10005];
struct node
{
    int val,id;
}s[1000005];
bool cmp(node x,node y)
{
    return x.val<y.val;
}
void add(int x,int val)
{
    for(int i=x;i<=n;i+=lowbit(i))
        c[i]+=val;
}
int find(int x)
{
    int ans=0;
    for(int i=x;i;i-=lowbit(i))
        ans+=c[i];
    return ans;
}
int main()
{
    long long ans=0;
    int cnt=0,x;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
            cnt++,s[cnt].val=a[i][j],s[cnt].id=i;
        }
    sort(s+1,s+cnt+1,cmp);
    for(int i=1;i<=cnt;i++)
    {
        x=s[i].id;
        ans+=find(n)-find(x)+sum[x]*(n-x)+(n-x);
        add(x,1),sum[x]++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：__Louis__ (赞：1)

## [ABC306F] Merge Sets 题解

### 题目描述
对于两个集合 $A$ 和 $B$，保证 $A\cap B=\varnothing$，定义 $f(A,B)$ 表示 $A$ 和 $B$ 的集合相交后  $A$ 中的每个元素在新集合中的排名之和。

现在我们有 $n$ 个整数集合 $S_1,S_2,\cdots,S_n$。
保证对于 $i\neq j$，$S_i\cap S_j=\varnothing$。

求：
$$\sum_{1\le i<j\le n}f(S_i,S_j)$$

### 暴力做法

对于每一组数据，$n^2$ 枚举每一个集合，然后拼在一起排序，遍历算出下标即可。

复杂度 $O(NM^2\log_{}{M})$。

### 如何优化

$$\sum_{1\le i<j\le n}f(S_i,S_j)$$

这个式子其实可以拆开，设 $G_i$ 表示每个数下标的贡献，$H_{i,j}$ 表示原来第 $i$ 个集合中第 $j$ 小数，则有原式转换成：

$$ \sum_{ 1\le i\le n}\sum_{1\le j\le m}  G_{i,j} $$

然后可以分别算每一个数的贡献，分为自己在原来数组的的下标，加上后面的数有多少个比它小，即：

$$G_{i,j} =  j*m + \sum_{ i< p\le n}\sum_{1\le q\le m}  [H_{i,j}>H_{p,q}]$$ 

最后用树状数组存下所有数的排名，边加边删即可。复杂度$O(nm\log{}{nm})$。

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e4+10;
const int maxm=1e2+10;
int n,m;
int tree[maxn*maxm];
int arr[maxn][maxm],sor[maxn*maxm];
unordered_map<int,int> res;
int lowbit(int x){
	return x&-x;
}
void add(int x,int a){
	while(x<=n*m){
		tree[x]+=a;
		x+=lowbit(x);
	}
}
int find(int x){
	int ans=0;
	while(x>0){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
signed main(){
	
	scanf("%lld%lld",&n,&m);
	int cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&arr[i][j]);
			sor[++cnt]=arr[i][j];
		}
	}
	sort(sor+1,sor+1+n*m);
	for(int i=1;i<=n*m;i++){
		res[sor[i]]=i;
		add(i,1);
	}
	int ans=0;
	for(int i=1;i<n;i++){
		sort(arr[i]+1,arr[i]+1+m);
		for(int j=1;j<=m;j++){
			ans+=j*(n-i);
			int p=find(res[arr[i][j]])-1;
			ans+=p;
			add(res[arr[i][j]],-1);
		}
	}
	printf("%lld",ans);
	return 0;
} 
```

---

## 作者：_ZML_ (赞：1)

# 题意
对于两个**交集为**空的的集合，定义 $f(A,B)$ 表示，将 $A$ 与 $B$ 中的所有数合在一起从小到大排序后，$A$ 中所有元素排名之和。

现在给出 $n$ 个**两两无交**，且大小都为 $m$ 的集合 $S_1,\cdots,S_n$，你的目的是算出：
$$\sum_{1\le i<j\le n}f(S_i,S_j)$$ 
# 思路
暴力应该很显然，按照题意模拟即可。对于计算 $f$ 函数部分，我们可以暴力排序，时间复杂度 $\Theta(n^2m\log_2n)$。显然无法通过此题。

来理解一件事情，原本算出答案的方法可以简化为将比它编号大的集合里的所有数与 $A$ 一起排序，然后将这个大数组内 $A$ 的排名之和相加以及 $A$ 数组被少算了几次（原本 $f$ 会算上 $A$ 数组自身的排名）

拿样例 $1$ 来说。想要算出 `1 2` 的答案，我们可以将 $1,2,3$ 数组一起排序，得到一个大数组：
$$
{\color{red}1},2,{\color{red}3},4,6,8
$$
其中 `1 2` 分别排在第 $1$ 和第 $3$ 。

所以它对答案的贡献就是 $1+3=4$ 还有被少算的 $1$ 次的贡献，即为 $1+3+（1+2）$，和分开来算是一样的。

算比自身小的数的个数可以用树状数组加离散化优化到  $\log(n*m)$ 级别。

所以这道题也就解决了，时间复杂度$\Theta(nm\times \log(nm)$ 。

注意因为算的是：
$$\sum_{1\le i<j\le n}f(S_i,S_j)$$ 

所以得倒序循环加数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int c[N*2];
int a[10010][110];
void add(int x,int add) {
    for(;x<=N;x+=(x&-x)) {
        c[x]+=add;
    }
}
int query(int x) {
    int ans=0;
    for(;x;x-=(x&-x)) {
        ans+=c[x];
    }
    return ans;
}
int nums[N],tot;
unordered_map<int,int> mp;
signed main() {
//    cin.tie(0),cout.tie(0);
//    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) {

        for(int j=1;j<=m;j++) {
            cin>>a[i][j];
            nums[++tot]=a[i][j];
        }
    }
    sort(nums+1,nums+tot+1);
    for(int i=1;i<=tot;i++) {
        mp[nums[i]]=i;
    }
    int ans=0;
    for(int i=n;i>=1;i--) {
    	
        for(int j=1;j<=m;j++) {
            int num=mp[a[i][j]];
            ans+=query(num);
        }
        ans+=(n-i)*m*(m+1)/2;
        for(int j=1;j<=m;j++) {
            int num=mp[a[i][j]];
            add(num,1);
        }
    }
    cout<<ans;
    return 0;
}
````

---

## 作者：farfarqwq (赞：1)

## 题目翻译

对于两个集合 $A$ 和 $B$，**保证没有相同的元素**。有一个序列 $C$，它包含 $A$ 和 $B$ 里所有的元素，且长度为 $|A|+|B|$ **并按升序排列**。定义 $f(A,B)$ 为对于 $A$ 里的**所有元素**，它在 $C$ 中的**下标之和**。

如 $A=\{1,4\}$，$B=\{2,8\}$，那么序列 $C=\{1,2,4,8\}$，那么 $1=C_1$，$4=C_3$，$f(A,B)=1+3=4$。

现在给你 $n$ 个元素个数为 $m$ 的集合 $S_1,S_2,\dots,S_n$，求 $\sum\limits_{1\le i < j \le n}^n f(S_i,S_j)$。

## 解法

发现对于 $S_i$ 中第 $k$ 小的数，它对 $S_j$ 计算时所贡献的值就是：$S_j$ 中小于这个数的数的数量 $+ k$。

由于 $i < j$，所以它对整个答案的贡献就为：$S_i$ 后面的所有 $S_j$ 小于这个数的数的数量加 $k(n-i)$。

后面一项很好求，前面那项考虑用值域线段树/树状数组。

处理时先离散化（值域是 $1 \sim 10^9$），然后倒着枚举，计算完了再把这个数添加到线段树/树状数组里，就做完了。

答案记得开 long long。

## 代码

```cpp
//这边是和同学用一个AT号打的比赛，所以代码是一样的
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
using namespace std;
typedef long long ll;
const int N = 10005, M = 105;
int a[N][M];
int b[N * M];//离散化数组
int t[N * M << 2];//线段树数组
void upd(int p, int L, int R, int x) {//值域线段树单点修
    ++t[p];
    if (L == R) {
        return ;
    }
    int mid = (L + R) >> 1;
    if (x <= mid)
        upd(p << 1, L, mid, x);
    else
        upd(p << 1 | 1, mid + 1, R, x);
}
int qry(int p, int L, int R, int x) {//值域线段树查询1~x（鬼畜做法）
    if (R <= x)
        return t[p];
    int mid = (L + R) >> 1;
    if (x <= mid)
        return qry(p << 1, L, mid, x);
    return t[p << 1] + qry(p << 1 | 1, mid + 1, R, x);
}
int main() {
    int n, m, cnt = 0;
    scanf("%d%d", &n, &m);
    ll ans = 0;//要开 long long
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            b[++cnt] = a[i][j];//离散化
        }
        sort(a[i] + 1, a[i] + m + 1);//排序好处理
    }
    sort(b + 1, b + cnt + 1);
    for (int i = n; i; i--) {//倒着循环
        for (int j = 1; j <= m; j++) {
            a[i][j] = lower_bound(b + 1, b + cnt + 1, a[i][j]) - b;//离散化
            ans += qry(1, 1, n * m/*一共有 n*m 个不同的数，离散化完了最高是 n*m */, a[i][j]) + j * (n - i);//对答案做贡献

        }
        for (int j = 1; j <= m; j++)
            upd(1, 1, n * m, a[i][j]);//添加到线段树中
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Z1qqurat (赞：1)

朝算贡献，夕死可矣！

首先考虑集合 $S_i$ 中数 $S_{i, k}$ 对答案的贡献。它的贡献只有在 $S_i$ 和 $S_j$ 并的时候会出现，其中 $j > i$，然后我们将贡献拆为两部分：两个集合并起来 $S_{i, k}$ 的排名一部分就是 它在原集合 $S_i$ 中的排名，另一部分就是 $S_j$ 中所有小于 $S_{i, k}$ 的元素的数量。前者可以在计算 $S_i$ 的贡献的时候直接整体求和加，后者考虑一个集合一个集合地依次加入元素，用树状数组统计。

然后聪明的我以为我可以直接不管 $i < j$ 的条件，把所有的都算上最后除 $2$ 就可以了，然后这并不是等价的，推推式子就可以发现。这个弱智错误调了一周。所以说如果真不是不去掉限制条件就不好算的话还是尽量老老实实按照大小限制条件模拟，如果实在要对称转化的时候记得证一下啊。只会结论而不会证结论不如不会这个结论。

给出清新的代码实现：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
#include <vector>
#include <map>
#define ll long long
using namespace std;
const int N = 1e4 + 5, M = 105;
int n, m, tr[N * M], aa[N * M], tot, a[N][M];
map <int, int> mp;
ll ans;

int lowbit(int x) {
    return x & (-x);
}

void modify(int x, int val) {
    while(x <= tot) {
        tr[x] += val;
        x += lowbit(x);
    }
    return ;
}

int query(int x) {
    int ret = 0;
    while(x > 0) {
        ret += tr[x];
        x -= lowbit(x);
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> aa[(i - 1) * m + j];
            a[i][j] = aa[(i - 1) * m + j];
        }
    }
    if(n == 1) return puts("0"), 0;
    sort(aa + 1, aa + n * m + 1);
    for (int i = 1; i <= n * m; ++i) {
        if(!mp[aa[i]]) mp[aa[i]] = ++tot;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            a[i][j] = mp[a[i][j]];
        }
    }
    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= m; ++j) {
            ans += query(a[i][j]);
        }
        ans += (n - i) * m * (m + 1) / 2;
        for (int j = 1; j <= m; ++j) {
            modify(a[i][j], 1);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：luogu_gza (赞：1)

考虑每一个元素的贡献，答：有几个数比它小（包括原数列）。

发现了这一点后就很好做了，但是原数列本身需要特殊处理。

从后往前在 `vector` 里面插入一个横排，然后寻找这个横排在 `vector` 中的位置，就是这个横排对于答案的贡献（相当于一次性统计多排答案）。

后面有 $x$ 个横排的时候，在 `vector` 中统计后还需要加上原数列比它小的数的量的 $x-1$ 倍。

细节见代码。

纯粹的二分似乎会时间超限，因此，我们采用高贵的 `pdds` 中的平衡树。

这里注意一下，定义的时候要在开头加入以下语句。

```cpp
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
```

[代码](https://atcoder.jp/contests/abc306/submissions/42359522)



---

## 作者：GI录像机 (赞：1)

### 解题思路：

考虑枚举每个数，然后快速求出这个数在不同情况下的贡献之和。

把要快速求的数定为 $x$，其属于集合 $u$。再考虑属于集合 $v$ 的数 $y$ 对 $x$ 的贡献。假定 $y<x$（否则显然无贡献）。

如果 $v<u$，则 $y$ 对 $x$ 无贡献，因为题目中要求 $ \displaystyle\ \sum_{1\leq\ i\ <\ j\ \leq\ N}\ f(S_i,\ S_j) $，只有前面的集合编号小于后面的时候才会考虑。

如果 $v=u$，则 $y$ 对 $x$ 的贡献为集合编号大于 $u$ 的个数，因为在每次运算中其都有贡献，每次都能使 $x$ 的下标加 $1$。

如果 $v>u$ 所处的集合编号，则 $y$ 对 $x$ 有 $1$ 的贡献，因为当且仅当这两个集合在一起运算时，其有贡献，可以让 $x$ 的下标加 $1$。

可以建立一个动态开点权值线段树，按集合编号从大到小，集合中值从小到大的顺序将其加入线段树。线段树内维护 $v>u$ 的贡献，$v=u$ 的贡献可直接计算。

### 参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 1e4 + 10, M = 1e2 + 10, INF = 0x3f3f3f3f;
int n = read(), m = read(), b[N][M], tot = 1, ans;
struct Node {
	int num, lson, rson;
} a[(int)8e7];
void pushup(int pos) {
	a[pos].num = a[a[pos].lson].num + a[a[pos].rson].num;
}
void add(int pos, int l, int r, int L) {
	if (l == r) {
		a[pos].num = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if (!a[pos].lson)a[pos].lson = ++tot;
	if (!a[pos].rson)a[pos].rson = ++tot;
	if (mid >= L)add(a[pos].lson, l, mid, L);
	else add(a[pos].rson, mid + 1, r, L);
	pushup(pos);
}
int query(int pos, int l, int r, int L, int R) {
	if (L <= l && r <= R)return a[pos].num;
	int mid = (l + r) >> 1, tmp = 0;
	if (a[pos].lson && mid >= L)tmp += query(a[pos].lson, l, mid, L, R);
	if (a[pos].rson && mid + 1 <= R)tmp += query(a[pos].rson, mid + 1, r, L, R);
	return tmp;
}
signed main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			b[i][j] = read();
		sort(b[i] + 1, b[i] + m + 1);
	}
	for (int i = n; i >= 1; i--)
		for (int j = m; j >= 1; j--) {
			ans += query(1, 1, 1e9, 1, b[i][j]) + j * (n - i);
			add(1, 1, 1e9, b[i][j]);
		}
	write(ans);
	return 0;
}
```

---

## 作者：MornStar (赞：1)

# AT_abc306_f Merge Sets 题解

[link](https://www.luogu.com.cn/problem/AT_abc306_f)

[获得更差的观看体验](https://www.luogu.com.cn/blog/zhuyixin666/solution-at-abc306-f)

## 废话
蒟蒻第一次在赛场上切掉 f 题，必须写一篇题解记录一下。

## 题目大意
对于两个集合 $A$ 和 $B$，保证 $A\cap B=\varnothing$，定义 $f(A,B)$ 如下。

- 定义一个新集合 $C=A\cup B$ ，即 $C=(C_1,C_2,\cdots,C_{\left | A \right |+\left | B \right |})$。

- 对于 $A_i(1\le i \le \left | A \right |)$，若 $C_j=A_i(1\le j \le \left | A \right |+\left | B \right |)$，则 $k_i=j$。

- $f(A,B)=\sum_{i=1}^{\left | A \right |}k_i$。

现在我们有 $n$ 个整数集合 $S_1,S_2,\cdots,S_n$。

每个集合有 $m$ 个数，即 $S_i=(A_{i,1},A_{i,2},\cdots,A_{i,m})(1\le i\le n)$。

保证对于 $i\neq j$，$S_i\cap S_j=\varnothing$。

求 
$$\sum_{1\le i<j\le n}f(S_i,S_j)$$

- $1\le n\le 10^4$

- $1\le m\le 10^2$

## 思路

首先思考一种做法，暴力合并两个集合并计算贡献。

因为输入是无序的，所以在计算时，会有排序的 $O(m\log m)$。

时间复杂度 $O(n^2m\log m)$，并不能通过此题。

但是，这种做法给了我们一个很好的思路。

我们可以将所有 $n$ 个集合混在一起进行排序，那么对于 $S_i$ 和 $S_j$ 其内元素的相对顺序是不变的，也就并不会影响我们计算 $f(S_i,S_j)$ 。所以我们完全可以将所有元素进行一个排序，再来统计答案。

接下来就是如何统计答案了。

先来考虑只有两个集合 $S_i$，$S_j(1\le i<j\le n)$ 的情况。

假设在 $C_{i,j}=S_i\cup S_j$ 下。$S_{i,k}=C_{i,j,l}$。则 $S_{i,k}$ 对于 $f(S_i,S_j)$ 的贡献就是 $l$。

因为在排序的情况下，集合本身是有序的。

那么 $S_{i,k}$ 对 $f(S_i,S_j)$ 产生的贡献就是当遍历到 $S_i$ 时，$S_i$ 和 $S_j$ 共被遍历到的元素之和。

即：
$$l=\sum_{l=1}^{m}\left [ S_{j,l}<S_{i,k} \right ]+k$$

再扩展到多个集合，则 $S_{i,k}$ 对总答案产生的贡献则为：

$$\sum_{j=i+1}^{n}\left(\sum_{l=1}^{m}\left [ S_{j,l}<S_{i,k} \right ]+k\right)=\sum_{j=i+1}^{n}\sum_{l=1}^{m}\left [ S_{j,l}<S_{i,k} \right ]+k\times(n-i)$$

当遍历到第 $i(1\le i\le n\times m)$ 个元素时，如果其属于 $S_j$，我们就只需要查询再前面的集合编号大于 $j$ 的集合已遍历到的元素总和加上 $k\times(n-i)$ 。就能轻松计算这个元素的贡献。

而对于集合编号大于 $j$ 的集合已遍历到的元素总和，我使用树状数组的区间修改，单点查询和桶进行维护。

## code
代码时间。
```cpp
//by MornStar
#include<bits/stdc++.h>
using namespace std;
struct num{
	int in,val;
	num(int _in=0,int _val=0){
		in=_in;
		val=_val;
	}
}a[1000005];
bool cmp(num a,num b){
	return a.val<b.val;
}
int n,m,tree[10005],t[10005];
inline int lb(int x){return x&(-x);}
void change(int x,int add){
	for(int i=x;i<=n;i+=lb(i))	tree[i]+=add;
}
int get(int x){
	int ret=0;
	for(int i=x;i!=0;i-=lb(i))	ret+=tree[i];
	return ret;
}//树状数组
long long ans;
int main(){
 	ios::sync_with_stdio(false);
  	cin.tie(0);
  	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[m*(i-1)+j].in=i;//记录每一个元素所属的集合。
			cin>>a[m*(i-1)+j].val;
		}//将输入矩阵压缩成行，方便排序。
	}
	sort(a+1,a+n*m+1,cmp);
	for(int i=1;i<=n*m;i++){
		change(1,1);
		change(a[i].in,-1);//差分，将小于此集合编号的集合区间加。
		t[a[i].in]++;
		ans+=(get(a[i].in)+t[a[i].in]*(n-a[i].in));
	}
	cout<<ans;
}
```
时间复杂度 $O(nm\log nm)$。

最慢点用时不超过 $250ms$。

---

## 作者：Claire0918 (赞：0)

我们注意到题目输入中的集合实际上与数列更接近，下文以数列称其。

对于 $A, B$，我们钦定在所谓“正常状态”下对于 $A$ 的 $k_i$ 与 $[1, n]\cap \mathbb{Z}$ 满足双射，从而
$$
\sum_{i = 1}^{m} k_i = \sum_{i = 1}^{m} i = \frac{m(m + 1)}{2}
$$

如果对于任意的 $i < j$，都有 $S_i$ 和 $S_j$ 形成“正常状态”，则结果为
$$
{n \choose 2} \times \sum_{i = 1}^{m} k_i = \frac{n(n - 1)}{2}\frac{m(m + 1)}{2} = \frac{n(n - 1)m(m + 1)}{4}
$$

但是显然并非任何时候都会出现“正常状态”。具体地，如果对于 $i < j$，存在 $x \in S_i, y \in S_j, x > y$，则组合后的 $x$ 至少在 $y$ 之后，结果将会比“正常状态”多 $1$。

从而实际的结果为直接当作“正常状态”算得的结果加上使得 $i < j, x \in S_i, y \in S_j, x > y$ 的 $(x, y, i, j)$ 数量。

不难发现这可以使用逆序对维护，即将 $n$ 个数列顺次连接成一个数列 $\{a_i\}$。形式化地，
$$
a_i = s_{\lfloor \frac{i - 1}{m} \rfloor + 1, (i - 1 \bmod m) + 1}
$$
在这之后，我们发现每一个 $(x, y, i, j)$ 与 $\{a_i\}$ 中每一个原本不在同一个 $s_i$ 的逆序对满足双射。形式化地，每一个 $(x, y, i, j)$ 与 $i < j, \lfloor \frac{i - 1}{m} \rfloor \neq \lfloor \frac{j - 1}{m} \rfloor, a_i > a_j$ 的 $(i, j)$ 满足双射。

我们只需要用“正常状态”的结果加上 $\{a_i\}$ 的逆序对数量减去每一个 $s_i$ 的逆序对数量即可。

Code：

```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 1e4 + 10, maxm = 1e2 + 10;

long long n, m;
int a[maxn][maxm], all[maxn * maxm], temp[maxn * maxm];

inline void mergesort(int l, int r, int* a, long long & res){
    if (l >= r){
        return;
    }
    const int mid = l + r >> 1;
    mergesort(l, mid, a, res);
    mergesort(mid + 1, r, a, res);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r){
        if (a[i] <= a[j]){
            temp[k++] = a[i++];
            res += j - mid - 1;
        }else{
            temp[k++] = a[j++];
        }
    }
    while (i <= mid){
        temp[k++] = a[i++];
        res += r - mid;
    }
    while (j <= r){
        temp[k++] = a[j++];
    }
    for (int i = l; i <= r; i++){
        a[i] = temp[i];
    }
}

int main(){
    scanf("%lld %lld", &n, &m);
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            scanf("%d", &a[i][j]);
            all[(i - 1) * m + j] = a[i][j];
        }
    }
    if (n == 1){
        putchar('0');
        return 0;
    }
    long long res = n * (n - 1) * m * (m + 1) >> 2;
    mergesort(1, n * m, all, res);
    for (int i = 1; i <= n; i++){
        long long now = 0;
        mergesort(1, m, a[i], now);
        res -= now;
    }
    printf("%lld", res);

return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

这种有序数对的题钦定一个位置然后算贡献是比较显然的方法。考虑一个 $j$ 中的元素 $x$ 对答案有贡献是一个 $i$ 中一个元素 $y$ 小于 $x$ 的时候。再考虑答案一开始的时候可以按一个集合中的大小把元素对答案的贡献设置为 $1$ 到 $m$，这样在 $y$ 上贡献完之后就可以使得 $y$ 的位置成为我们想要的东西。同时在一开始设置的时候有序数对是可选的，要乘上一个组合数。

实现需要对于每个元素数前面的集合中大于他的个数，数完之后再把整个集合插入。离散化之后树状数组即可简单维护。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long

const int N = 1e4 + 5, M = 1e2 + 5;
int n, m, a[N][M], b[N * M], tot;

namespace FenwichTree {
	int c[N * M];
	int qwq(int x) { return x & (-x); }
	void update(int x) { for (; x <= n * m; x += qwq(x)) c[x]++; }
	int Query(int x) { int a = 0; for (; x; x -= qwq(x)) a += c[x]; return a; }
	int query(int x) { return Query(n * m) - Query(x); }
} using namespace FenwichTree;

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		cin >> a[i][j], b[++tot] = a[i][j];
	sort(b + 1, b + tot + 1); int len = unique(b + 1, b + tot + 1) - (b + 1);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		a[i][j] = lower_bound(b + 1, b + len + 1, a[i][j]) - b;
	int ans = n * (n - 1) / 2 * (1 + m) * m / 2;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) ans += query(a[i][j]);
		for (int j = 1; j <= m; j++) update(a[i][j]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Pretharp (赞：0)

这道题，让人看到直呼 What the f... ~~fuck~~ fantastic！本题其它题解已经写的很全面了，但是我还是想将自己的思路整理一下，同时也希望其它题解看完还有些迷糊的人从我这得到解答。

不难发现，本题的最终答案并没有一定要按照题目所给的顺序求出（枚举两个集合计算贡献）。因此，我们可以考虑使用一些更加高效的处理方式——考虑任意一个数在统计另一个数的情况下是否会对答案产生贡献。

假设，当前有两个数 $x$ 和 $y$，它们分别来自编号为 $a$ 和 $b$ 的集合中的第 $i$ 和 $j$ 位（即 $x = S_{a,i}$ 且 $y=S_{b,j}$），我们对此分类讨论：

- 如果 $x>y$，因为 $x$ 和 $y$ 在两个集合合并之后 $x$ 的下标大于 $y$ 的下标，故 $x$ 所在之处不会影响 $y$ 的下标，不对答案产生贡献；
- 当 $x<y$ 时：
  - 如果 $a=b$，则在当前 $x$ 和 $y$ 共同所在的区间的每一次与其它区间合并中，$x$ 都会产生贡献，此时贡献为 $n-a$；
  - 如果 $a<b$，则当两区间合并时，$x$ 的存在会导致 $y$ 向后移动一位，故贡献为 $1$。
  - 如果 $a>b$，这两个区间永远不会合并，所以不产生贡献。

因此，$y$ 来源于其它所有数对答案的贡献应当为 $(mn_n - mn_b) + (mn_b - mn_{b-1} + 1)\times(n-b)+(n-b)$，其中，$mn_t$ 表示集合 $1$ 至 $t$ 中有多少个比 $y$ 小的数。

代码实现中，我们可以先将所有数排序并记录其所在区间，$mn$ 数组可以用树状数组维护。

[记录](https://atcoder.jp/contests/abc306/submissions/43697216)

---

## 作者：f2021ljh (赞：0)

[AtCoder ABC306 DEF - f2021ljh - 博客园](https://www.cnblogs.com/f2021ljh/p/17489000.html)

---

[洛谷](https://www.luogu.com.cn/problem/AT_abc306_f) | [AtCoder](https://atcoder.jp/contests/abc306/tasks/abc306_f)

---

### 题意

对于两个由整数构成的集合 $A,B$ 满足 $A\cap B=\varnothing$，我们定义 $f(A,B)$ 表示将 $A\cup B$ 按升序排序后 $A$ 中每个元素在 $A\cup B$ 中的下标之和。

现在给定 $N$ 个大小为 $M$ 的整数集合 $S_1,S_2,\dots,S_N$，保证它们两两不交。

求出 $\displaystyle\sum_{1\le i<j\le N}f(S_i,S_j)$。

$1\le N\le10^4$，$1\le M\le10^2$，$1\le A_{i,j}\le 10^9$。

### 思路

首先把所有数离散化，那么值域变为 $[1,N\times M]$，可以发现这并不影响答案。

先来考虑两个集合 $A,B$ 的 $f(A,B)$ 怎么求。

我们可以把集合中的每个数的大小看做**高度**，那么 $A_i$ 的排名即为在 $A_i$ 下方的 $B$ 中的点的数量加上 $A_i$ 在 $A$ 中的排名。

由于 $A$ 和 $B$ 是有前后顺序的，我们不妨放到平面上考虑：

设 $A=\{2,4,1,7\}$，$B=\{3,8,6,5\}$。我们把这些点画在平面上，如下图：（红点是 $A$，蓝点是 $B$）

![](https://cdn.luogu.com.cn/upload/image_hosting/gt8o7c1n.png)

可以看到，在 $A_i$ 右下方范围内的蓝点数量即为小于 $A_i$ 的 $B$ 中数的数量。

于是每个 $A_i$ 的贡献可以拆成两部分：在 $A_i$ 右下方的蓝点数量、$A_i$ 在 $A$ 中的排名是第几小。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qm8q22vs.png)

那么对于许多个集合，我们同样可以这样来求：

![](https://cdn.luogu.com.cn/upload/image_hosting/23affqz6.png)

每个点的贡献：在它右下方且不与它在同一个集合的点的数量，加上它在自己集合中的排名乘以后面还有几个集合。

于是我们从右到左、从上到下（为了消除同一集合中的点的影响）遍历所有点，用树状数组维护高度即可。

时间复杂度 $O(NM\log(NM))$。

### 代码

```cpp
#include <iostream>
#include <algorithm>
#define f(x, y, z) for (int x = (y); x <= (z); ++x)
#define g(x, y, z) for (int x = (y); x >= (z); --x)
using namespace std;
const int N = 1e4 + 10, M = 110;
int n, m, a[N][M], val[N * M], cnt, c[N * M];
long long ans;
inline int lb(int const &x) { return x & (-x); }
void add(int x) { while (x <= n * m) ++c[x], x += lb(x); }
int sum(int x) { int r = 0; while (x) r += c[x], x -= lb(x); return r; }

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> n >> m;
    f(i, 1, n) f(j, 1, m) cin >> a[i][j], val[++cnt] = a[i][j];
    sort(val + 1, val + cnt + 1);
    // cnt = unique(val + 1, val + cnt + 1) - val - 1;
    f(i, 1, n) f(j, 1, m) sort(a[i] + 1, a[i] + m + 1), a[i][j] = lower_bound(val + 1, val + cnt + 1, a[i][j]) - val;
    g(i, n, 1) g(j, m, 1) ans += sum(a[i][j]), add(a[i][j]), ans += (i - 1) * j;
    cout << ans << '\n';
    
    return 0;
}
```



---

## 作者：MYiFR (赞：0)

### 题目大意
首先定义 $f(A,B)$：

对于两个没有公共元素的集合 $A$，$B$，设它们的并集为 $C$，那么 $f(A,B)$ 就等于 $A$ 中每个元素在 $C$ 中的下标之和。

给定 $N$ 个容量为 $M$ 且任意两个都没有公共元素的集合 $S_i$，让你求出 $\displaystyle\sum_{1\leq i<j\leq N}f(S_i,S_j)$ 。

### 解题思路
很容易想到对于任意两个集合 $S_i$，$S_j$，$S_{i,k}$ 对 $f(S_i,S_j)$ 的贡献是在这两个集合的并集中小于 $S_{i,k}$ 的元素的个数 $+1$。

再多想一点，因为题目要求 $i<j$，**所以对于每个 $S_i$，它自身对于答案的贡献就是 $\displaystyle(N-i)\times\frac{M\times(M+1)}{2}$，其它集合 $S_j(j>i)$ 关于 $S_i$ 对答案的贡献就是在 $S_{i+1}\cup S_{i+2}\cup\cdots S_N$ 中小于 $S_{i,k}$ 的元素个数**。

那么我们从 $N$ 到 $1$ 枚举，对除了 $S_N$ 以外的集合求一遍上面加粗字体的过程，求完后再把 $S_i$ 加入并集中（$S_N$ 当然也要加进去），最后输出答案即可。

维护并集的方法可能有很多，但是建议是将 $S_{i,j}$ 离散化后用树状数组维护，因为[ stl 常数太大了](https://atcoder.jp/contests/abc306/submissions/42738726)。

### AC 代码
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e4+5,M=1e2+5;
ll n,m,a[N][M],ans,cnt,tr[N*M],b[N*M];
ll lowbit(ll x){
	return x&(-x);
}
void updt(ll x){
	while(x<=n*m){
		++tr[x];
		x+=lowbit(x);
	}
}
ll query(ll x){
	ll res=0;
	while(x){
		res+=tr[x];
		x-=lowbit(x);
	}
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	cnt=m*(m+1)/2;
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j){
		scanf("%d",&a[i][j]);
		b[(i-1)*m+j]=a[i][j];
	}
	sort(b+1,b+n*m+1);
	for(int i=n;i>=1;--i){
		if(i!=n){
			ll tmp=ans;
			ans+=cnt*(n-i);
			for(int j=1;j<=m;++j){
				ans+=query(lower_bound(b+1,b+n*m+1,a[i][j])-b-1);
			}
		}
		for(int j=1;j<=m;++j) updt(lower_bound(b+1,b+n*m+1,a[i][j])-b);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Chthologist7507 (赞：0)

纪念一下这场 unr 的 ABC。

### 题意简述

存在 $n$ 个元素数量为 $m$ 的集合 $S_1,S_2...S_N$，其中 $\forall i,j\in[1.n],i\neq j,S_i\cap S_j=\emptyset$。定义 $f(A,B)$ 为集合 $A$ 中的每个元素在 $A\cup B$ 从小到大排序后的排名，求 $\sum\limits_{1\leq i<j\leq n}f(S_i,S_j)$。

### 题目分析

对于集合中的每个数，我们分开算贡献。

将 $S_i$ 中的数先排好序。定义 $T_i=\bigcup\limits_{j=i}^n S_j$。

对于 $S_{i,j}$
- 在 $T_i$ 中，不大于 $S_{i,j}$ 的数都要算一次贡献，这里需要求 $S_{i,j}$ 在 $T_i$ 中的排名。

- 在 $S_i$ 中，不大于 $S_{i,j}$ 的数都要算 $n-i-1$ 次贡献（$n-i$ 是 $S_i$ 要和其他所有 $S_j$ 的总比较次数，$-1$ 是因为其中每项在 $T_i$ 里已经算过贡献了），因为 $S_i$ 已经有序，这样的数共有 $j$ 个。

我们需要维护集合 $T_i$，支持插入和算排名，考虑使用平衡树。

code：

```cpp
#include<bits/stdc++.h>
#define int long long//记得开 long long
#define inl inline
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(int i=(a),i##end=(b);i>=i##end;--i)
#define pb push_back
#define mp make_pair
#define x first
#define y second
using namespace std;
const int N=1e4+10,M=110,inf=0x3f3f3f3f,mod=1e9+7;
int a[N][M],ans;
struct Node{
    int l,r,siz,val,rnd;
}t[N*M];
int x,y,z,s,cnt;
namespace FHQTreap{
    #define ls t[k].l
    #define rs t[k].r
    void pushup(int k){t[k].siz=t[ls].siz+t[rs].siz+1;}
    void split(int k,int v,int &x,int &y){
        if(!k){x=y=0;return;}
        if(t[k].val<=v){x=k,split(rs,v,rs,y);}
        else {y=k,split(ls,v,x,ls);}
        pushup(k);
    }
    int merge(int u,int v){
        if(!u||!v)return u+v;
        if(t[u].rnd>t[v].rnd){t[u].r=merge(t[u].r,v);pushup(u);return u;}
        else{t[v].l=merge(u,t[v].l);pushup(v);return v;}
    }
    int getkey(int k,int v){
        if(!k)return 0;
        if(v<=t[ls].siz)return getkey(ls,v);
        else if(v<=t[ls].siz+1)return t[k].val;
        else return getkey(rs,v-t[ls].siz-1);
    }
    int getnode(int v){
        t[++cnt].val=v;
        t[cnt].siz=1;
        t[cnt].rnd=rand();
        return cnt;
    }
    void insert(int v){
        split(s,v-1,x,y);
        s=merge(merge(x,getnode(v)),y);
    }
    void remove(int v){
        split(s,v,x,z);split(x,v-1,x,y);
        y=merge(t[y].l,t[y].r);
        s=merge(merge(x,y),z);
    }
    int getrank(int v){
        split(s,v-1,x,y);
        int k=t[x].siz+1;
        s=merge(x,y);
        return k;
    }
    int prev(int v){
        split(s,v-1,x,y);
        int tmp=getkey(x,t[x].siz);
        s=merge(x,y);
        return tmp;
    }
    int next(int v){
        split(s,v,x,y);
        int tmp=getkey(y,1);
        s=merge(x,y);
        return tmp;
    }
}
using namespace FHQTreap;
signed main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,m;cin>>n>>m;rep(i,1,n)rep(j,1,m)cin>>a[i][j];
	rep(i,1,n)sort(a[i]+1,a[i]+m+1);
	pre(i,n,1){
		rep(j,1,m)insert(a[i][j]);
		rep(j,1,m){
			int idx=getrank(a[i][j]);
			ans+=idx+j*(n-i-1);
		}
	}
	cout<<ans;
}
```



---

