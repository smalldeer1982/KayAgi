# Gellyfish and Camellia Japonica

## 题目描述

Gellyfish 有一个长度为 $n$ 的整数数组 $c$，初始状态为 $c = [a_1, a_2, \ldots, a_n]$。接下来，Gellyfish 对数组进行 $q$ 次修改。每次修改由三个整数 $x_i, y_i, z_i$ 描述，表示将 $c_{z_i}$ 的值设置为 $\min(c_{x_i}, c_{y_i})$。经过 $q$ 次修改后，数组变为 $c = [b_1, b_2, \ldots, b_n]$。  
Flower 知道最终数组 $b$ 和所有修改操作 $(x_i, y_i, z_i)$，但不知道初始数组 $a$。她希望找到任意一个满足条件的初始数组 $a$，或者判断不存在这样的 $a$。如果存在多个解，输出任意一个即可。

## 说明/提示

**第一个测试用例：** 修改操作要求 $b_2 = \min(a_1, a_2)$，且 $b_1 = a_1$。但 $b_1 = 1 < b_2 = 2$，矛盾，无解。  
**第二个测试用例：** 初始数组 $a = [1, 2, 3]$ 经过两次修改后得到 $b = [1, 2, 3]$。  
**第三个测试用例：** 输出 $a = [1, 2, 3, 4, 5, 5]$ 是一个可行解。  

---  

由 DeepSeek 翻译

## 样例 #1

### 输入

```
3
2 1
1 2
2 1 2
3 2
1 2 3
2 3 2
1 2 1
6 4
1 2 2 3 4 5
5 6 6
4 5 5
3 4 4
2 3 3```

### 输出

```
-1
1 2 3 
1 2 3 4 5 5```

# 题解

## 作者：_O_v_O_ (赞：8)

赛时想到正解了，但是被 $z_i=x_i$ 的 corner case 卡了。/ll

人类智慧题，考虑正难则反。

我们从最后往前处理操作，假如遇到了 $i$，那么就令 $a_{x_i}\leftarrow\max\{a_{x_i},a_{z_i}\},a_{y_i}\leftarrow\max\{a_{y_i},a_{z_i}\}$ 因为想要达成目标，必须满足 $\min\{a_{x_i},a_{y_i}\}=a_{z_i}$，我们这样做就是相当于令 $\min\{a_{x_i},a_{y_i}\}\ge a_{z_i}$。然后令 $a_{z_i}\leftarrow0$，因为 $a_{z_i}$ 在操作后被覆盖了导致我们不能知道原来的，所以在前面假如 $z_i$ 成为了 $x_j$ 或者 $y_j$ 刚好就可以用前面的操作还原 $a_{z_i}$。

然后我们就发现这样处理就行了。最终的话就直接正着跑一遍判断是否无解即可。

code：

```
#include<bits/stdc++.h>
using namespace std;

const int N=3e5+5;
int n,q,a[N],b[N],c[N];
int x[N],y[N],z[N];

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;while(T--){
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			cin>>b[i];
			a[i]=b[i];
		}
		for(int i=1;i<=q;i++) cin>>x[i]>>y[i]>>z[i];
		for(int i=q;i>=1;i--){
			a[x[i]]=max(a[x[i]],a[z[i]]);
			a[y[i]]=max(a[y[i]],a[z[i]]);
			if(y[i]!=z[i]&&x[i]!=z[i]) a[z[i]]=0;
		}
		for(int i=1;i<=n;i++) c[i]=a[i];
		for(int i=1;i<=q;i++) a[z[i]]=min(a[x[i]],a[y[i]]);
		bool fg=1;
		for(int i=1;i<=n;i++) fg&=(a[i]==b[i]);
		if(!fg){
			cout<<-1<<endl;
		}
		else{
			for(int i=1;i<=n;i++) cout<<c[i]<<' ';
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：ShanQing (赞：5)

[link](https://www.luogu.com.cn/problem/CF2115B)

没见过的构造 trick，输的不冤，高妙，学习。~~某天赋哥说这是 *1800，果然 szc 不会构造。~~  

直接构造 $a$ 使得操作后 $a_i=b_i$ 非常不好做，考虑放宽条件，构造 $a$ 使得最后 $a_i\geqslant b_i$，其中每个 $a_i$ 尽可能小（显然初始值尽可能小最后的结果也会趋近于 $b_i$），最后只要测试一遍构造出的 $a$ 跑出来的结果是否等于 $b$ 即可。 

构造出这个 $a$ 是可做的。对于每个操作 $(u,v,w)$，对 $w$ 建立新点 $w'$，再连边 $u\rightarrow w'$ 和 $v\rightarrow w'$。最后给每个 $i$ 最后建立的新点赋值 $b_i$，反拓扑序跑一遍贪心即可（实现上不必拓扑排序，倒着跑 $p$ 组询问建立的边即可），每个点能取的最小值是指向所有点的最大值。于是最初存在的 $n$ 个点的值即为构造出的 $a$。

总结的话，主要的启发就是把 **构造使得与目标相等** 转换成 **最小的构造使得大于等于目标**。

```cpp
#include <bits/stdc++.h>
//taskkill /f /im 未命名1.exe
#define ED cerr<<endl;
#define TS cerr<<"I AK IOI"<<endl;
#define cr(x) cerr<<x<<endl;
#define cr2(x,y) cerr<<x<<" "<<y<<endl;
#define cr3(x,y,z) cerr<<x<<" "<<y<<" "<<z<<endl;
#define cr4(x,y,z,w) cerr<<x<<" "<<y<<" "<<z<<" "<<w<<endl;
#define popcnt __builtin_popcount
#define all(s) s.begin(),s.end()
#define bstring basic_string
//#define add(x,y) (x+=y)%=mod
#define pii pair<int,int>
#define epb emplace_back
#define pb push_back
#define mk make_pair
#define ins insert
#define fi first
#define se second
#define ll long long
//#define ull unsigned long long
using namespace std;
const int N=3e5+5,INF=2e9,mod=1e9+7;
int t,n,q;
int f[N+N],a[N],b[N];

struct node {
	int u,v,w;
}_e[N],e[N];
int nw[N];

void sol() {
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i) {
		scanf("%d",&b[i]),nw[i]=i;
	}
	int u,v,w;
	for(int i=1;i<=q;++i) {
		scanf("%d%d%d",&u,&v,&w);
		_e[i]={u,v,w},e[i]={nw[u],nw[v],nw[w]=n+i};
	}
	for(int i=1;i<=n+q;++i) f[i]=0;
	for(int i=1;i<=n;++i) f[nw[i]]=b[i];
	for(int i=q;i>=1;--i) {
		u=e[i].u,v=e[i].v,w=e[i].w;
		f[u]=max(f[u],f[w]),f[v]=max(f[v],f[w]);
	}
	for(int i=1;i<=n;++i) a[i]=f[i];
	for(int i=1;i<=q;++i) {
		a[_e[i].w]=min(a[_e[i].u],a[_e[i].v]);
	}
	for(int i=1;i<=n;++i) {
		if(a[i]!=b[i]) {
			puts("-1");return;
		}
	}
	for(int i=1;i<=n;++i) printf("%d ",f[i]);
	puts("");
}

int main()
{
	scanf("%d",&t);
	while(t--) {
		sol();
	}
	return 0;
}

```

---

## 作者：ZHR100102 (赞：2)

[Blog](https://www.cnblogs.com/zhr0102/p/18911345)

以此纪念把我送上 CM 的一道题。

不难发现由于这些变量是**具有传递性**的，所以可以把序列上每个位置的每次修改都看做一个节点，对于一次 $(x,y,z)$ 的修改，就将 $x,y$ 的当前版本向 $z$ 的当前版本连边，以表示两者取 $\min$ 的赋值操作。

进而考虑在每个节点的最终版本已知的情况下如何倒推出其余节点。先来**弱化限制**，假设节点 $v$ 的值 $a$ 已经确定，则对于给 $v$ 赋值的两个节点 $u_1,u_2$ 都必须满足值 $\ge a$ 的下界限制，因为如果小于 $a$ 则无法让 $v$ 取到 $a$。

于是可以**建反图**后，跑一遍**拓扑排序**，递推出每个节点能取到的最小值，然后惊奇的发现让**每个点取最小值**正是一种构造方式！因为每个节点的下界已经被满足了，为了让被赋值的点能恰好赋到对应值而不变大，所以尽可能取最小值以满足赋值上界是一定是不劣的。

最后在构造出方案后，自行模拟一下判断方案是否合法即可。

时间复杂度 $O(n+q)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=1000005,inf=0x3f3f3f3f,M=2000005;
int n,q,pos[N],id,dp[N],b[N],qx[N],qy[N],qz[N],tmp[N];
int h[N],rd[N],idx;
struct Edge{
    int v,ne;
}e[M];
void add(int u,int v)
{
    e[++idx]={v,h[u]};
    h[u]=idx;
}
void init()
{
    idx=0;
    for(int i=1;i<=id;i++)
    {
        h[i]=0;
        dp[i]=0;
        rd[i]=0;
    }
    id=0;
}
bool check()
{
    for(int i=1;i<=n;i++)
        tmp[i]=dp[i];
    for(int i=1;i<=q;i++)
    {
        int x=qx[i],y=qy[i],z=qz[i];
        tmp[z]=min(tmp[x],tmp[y]);
    }
    for(int i=1;i<=n;i++)
        if(tmp[i]!=b[i])return 0;
    return 1;
}
void solve()
{
    init();
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&b[i]);
        pos[i]=++id;
    }
    for(int i=1;i<=q;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&qx[i],&qy[i],&qz[i]);
        x=qx[i],y=qy[i],z=qz[i];
        int u=++id;
        add(u,pos[x]);
        add(u,pos[y]);
        rd[pos[x]]++;
        rd[pos[y]]++;
        pos[z]=u;
    }
    for(int i=1;i<=n;i++)
        dp[pos[i]]=b[i];
    queue<int>q;
    for(int i=1;i<=id;i++)
        if(rd[i]==0)q.push(i);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=h[u];i;i=e[i].ne)
        {
            int v=e[i].v;
            rd[v]--;
            if(rd[v]==0)q.push(v);
            dp[v]=max(dp[v],dp[u]);
        }
    }
    if(check()==0)
    {
        printf("-1\n");
        return;
    }
    for(int i=1;i<=n;i++)printf("%d ",dp[i]);
    printf("\n");
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    init();
    int t;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
```

---

## 作者：Air2011 (赞：2)

## B. Gellyfish and Camellia Japonica

### 题意

最开始有个未知的序列 $a$，每次操作有三个参数 $x,y,z$，代表将 $a_z$ 赋值为 $\min (a_x,a_y)$ 现已知操作完的序列 $b$ 和每次操作的三个参数，构造一种合法的序列 $a$，无解输出 $-1$。

### 思路

我们考虑从最后一个询问倒着往前推，对于最后一个询问，这里记作 $x,y,z$，我们知道 $b_x,b_y \ge b_z$，这个条件是必要的，即无法从 $b_x,b_y \ge b_z$ 向 $b_z= \min(b_x,b_y)$ 推导，之后我们考虑递归解决问题，我们考虑只差最后一步的操作没做的 $b'$ 数组，有 $b'_z$ 是可以任取的，因为只需要保证 $\min(b'_x,b'_y)=b_z$ 即可，注意此处是 $b_z$ 而非 $b'_z$。我们注意到一定有 $b'_x=b_x \ge b_z,b'_y=b_y \ge b_z$，我们注意到对于任意的 $a_i$，其都得满足他比他所更新的 $z$ 要更大，我们记录对于 $a$ 的限制数组为 $c$。

但上述还是一个必要条件，可证 $b_z= \min (b_x,b_y)$ 的充要条件是 $b_x,b_y \ge b_z$，$b_x,b_y$ 当中至少有一个等于 $b_z$。我们考虑怎样取数最优，因为 $a_i$ 无法取 $c_i$ 以下的数，而 $c_i$ 又一定是曾经的一个 $b_z$ 而在 $c_i$ 以上就不会存在另外一个曾经是 $b_z$ 的数，因此 $a_i$ 取 $c_i$ 一定最优，之后倒着模拟一边判断其是否合法即可。

### 代码

[Submission-322597568](https://codeforces.com/contest/2116/submission/322597568)

---

## 作者：zhangbo1000 (赞：1)

由于一个位置的数可能遭到多次操作，所以考虑由最终状态反推初始状态。

首先令 $a_i=b_i$，然后**倒序**遍历所有操作，考虑其对 $a$ 的影响（设当前处理第 $i$ 次操作）：

- $a_{x_i},a_{y_i}\ge a_{z_i}$。
- **若 $z_i$ 和 $x_i,y_i$ 都不相等**，则 $a_{z_i}$ 不受限制（因为其值将会在此次操作后被修改。）

仅仅这些信息还不足以确定 $a$，我们考虑更强的构造：

- $a_{x_i}\gets\max(a_{x_i},a_{z_i})$。
- $a_{y_i}\gets\max(a_{y_i},a_{z_i})$。
- **若 $z_i$ 和 $x_i,y_i$ 都不相等**，$a_{z_i}\gets 0$。

如果有解，这样的构造一定合法（$\max(a_{x_i},a_{z_i})\ge a_{x_i}$，$0$ 不超过任何非负整数。），且一定能使 $c_i=b_i$，因为当  $\min(a_{x_i},a_{y_i})$ 大于 $a_{z_i}$ 时，显然不存在解，否则，上述操作后一定有 $a_{x_i}=a_{z_i}$ 或 $a_{y_i}=a_{z_i}$。

无解的情况无非就是“一个数符合条件但是被操作替换掉了（即构造方式的第三条）”或者“$a_{x_i},a_{y_i}$ 都很大  $a_{z_i}$ 却很小（即上述合法性讨论中提到的情况）”，这些我们只需要构造完看一下对不对就行。

[代码和评测记录。](https://codeforces.com/contest/2115/submission/324323454)

---

## 作者：denominator (赞：1)

> [原题](https://www.luogu.com.cn/problem/CF2115B) / [CF 原题](https://codeforces.com/problemset/problem/2115/B)
>
> - 有长为 $n$ 的未知序列 $a$。
> - 进行 $q$ 次已知操作：
>    - 给定 $x,y,z$（可重），令 $a_z\gets\min(a_x,a_y)$。
> - 已知最后结果，构造 $a$ 或说明其无解。
> - $n,q\leq 3\times10^5$，$1\leq a_i\leq10^9$（构造时可以有 $0$）。

极具 simplicity 又有 difficulty 的构造！~~可惜在打这场时少写个 0 而寄了，具体可以见我的 [比赛日记](https://www.luogu.me/article/2nhf2mtk)~~。

首先显然是倒着向上。然后，可以维护每一个元素可行的取值范围，具体是 $a_i=x$ 或 $a_i\geq x$ 的形式。这可以使用 $[l,r]$ 来表示，其中 $r=l$ 或 $r=10^9$（~~考场上就是把它写成 $\sout{10^8}$ 了~~）。

可以发现以下范围限定更新的充要条件：

- 如果 $x\neq z$ 且 $y\neq z$，那么 $a_z$ 在前一时刻之前是可以取到任意值的，我们记作 $a'_z\geq1$，其中 $a'$ 为上一时刻的序列。
- 如果 $x=z$ 或 $y=z$，但是 $x=y=z$ **不成立**，只需要 $a_x$（或 $a_y$）的范围包含 $a_z$ 的范围，总可能会让 $a_z$ 变得更大，也就是说，若之前的限制为 $a_z=t$，可以将其扩增为 $a'_z\geq t$。
- $a'_x\geq a_z$ 或 $a'_y\geq a_z$ 是显然需要成立的。

中间出现矛盾直接判掉。

但是这个范围限定是假的——范围是有所牵扯的。拿上述的第三点为例，我们用以更新 $a'_x$ 与 $a'_y$ 的绝对是 $a_z$ 范围的最小值，那么万一 $a_z$ 在这一步变得更大呢？那岂不是要同步修改 $a'_x$ 与 $a'_y$ 的范围了吗？

这时我有了一个 aha moment：**让所有包含限定形式为 $\bm{a_i\geq x}$ 的 $\bm{a_i}$ 取到 $\bm{x}$ 跑一遍询问，检查结果是否相同**！这一点在考场上确实是猜的，并且认为其是一个很简单的结论。其实现在想想更加明晰了它的正确性，因为上面分析中的等号取到。

> 如果上面那个部分需要证明，我想想咋证 ~~或者把官解的那一部分话翻译过来~~。
>
> 这题的证明确实和 [季风](https://www.luogu.com.cn/problem/P10217)、[编辑字符串](https://www.luogu.com.cn/problem/P11361)、[幸运数字](https://www.luogu.com.cn/problem/P11830) 这种题一样，证明不太好言说。
>
> ~~快进到 NOIP、省选这种比赛放与这题类似的题~~。

理论上现在已经可以写代码了，但是如果你不想 ~~犯和我同样的错误~~ 写特别冗长的代码，可以把笨重的区间判断去掉了——中间的那些矛盾可以直接在最后一次跑时判掉。

这样算法逻辑就非常简单了：

- 倒着跑，对于某个 $x,y,z$，令 $a_x\gets\max(a_x,a_z)$，$a_y\gets\max(a_y,a_z)$。
- 如果 $x\neq z$ 且 $y\neq z$，令 $a_z\gets1$。
- 跑完所有询问后，再顺着维护，判断结果是否相同。

这一部分的代码就不放了 ~~懒得写~~，干脆还是放一个赛后搞好的代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 300010;
const ll mod = 998244353;
int T, n, q, a[N], l[N], r[N], x[N], y[N], z[N];
int main () {
	scanf ("%d", &T);
	while (T --> 0) {
		scanf ("%d%d", &n, &q);
		for (int i = 1; i <= n; i++) {
			scanf ("%d", &a[i]);
			l[i] = r[i] = a[i];
		}
		for (int i = 1; i <= q; i++) {
			scanf ("%d%d%d", &x[i], &y[i], &z[i]);
		}
		bool flag = false;
		for (int i = q; i >= 1; i--) {
			if (x[i] == y[i] && y[i] == z[i]) {
				continue;
			}
			if (x[i] != z[i]) {
				l[x[i]] = max (l[x[i]], l[z[i]]);
				if (l[x[i]] > r[x[i]]) {
					flag = true;
					break;
				}
			}
			if (y[i] != z[i]) {
				l[y[i]] = max (l[y[i]], l[z[i]]);
				if (l[y[i]] > r[y[i]]) {
					flag = true;
					break;
				}
			}
			if (x[i] != z[i] && y[i] != z[i]) {
				l[z[i]] = 1; // 在论述中为 0
			}
			r[z[i]] = 1000000000;
		}
		if (flag) {
			puts ("-1");
			continue;
		}
		for (int i = 1; i <= n; i++) {
			r[i] = l[i];
		}
		for (int i = 1; i <= q; i++) {
			r[z[i]] = min (r[x[i]], r[y[i]]);
		}
		for (int i = 1; i <= n; i++) {
			if (r[i] != a[i]) {
				flag = true;
				break;
			}
		}
		if (flag) {
			puts ("-1");
			continue;
		}
		for (int i = 1; i <= n; i++) {
			printf ("%d%c", l[i], " \n"[i == n]);
		}
	}
	return 0;
}
```

---

