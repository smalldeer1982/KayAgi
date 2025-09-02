# 「Cfz Round 3」Circle

## 题目描述

给定一个长度为 $n$ 的 $\tt{01}$ 串 $S$ 和一个非负整数 $l$。

我们定义，对于一个 $1\sim n$ 的排列 $t$ 和非负整数 $k$：

$$f_{t,k}(i)=\begin{cases}i & k=0\\f_{t,k-1}(t_i) & k \neq 0\end{cases}$$

你需要构造一个 $1\sim n$ 的排列 $p$，满足：

- 对于任意一个不大于 $n$ 的正整数 $i$，都满足 $p_i \neq i$；
- 若 $S_i$ 为 $\tt1$，则 $f_{p,l}(i)=i$（若 $S_i$ 为 $\tt0$ 则没有限制）；

或报告无解。

其中，$1\sim n$ 的排列指满足所有不大于 $n$ 的正整数恰好出现一次的序列。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组数据，$f_{p,3}(1)=f_{p,2}(4)=f_{p,1}(5)=f_{p,0}(1)=1$，其余数同理，所以 $p$ 为 $\{4,3,2,5,1\}$ 时满足条件。

对于第 $2$ 组数据，可以证明不存在满足条件的排列 $p$。

对于第 $3$ 组数据，$\{2,1,4,5,3\}$ 等也为满足条件的排列 $p$。

#### 「数据范围」

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有数据，$1 \le T \le 100$，$2 \le n \le 5\times 10^5$，$0 \le l \le 10^{18}$，$\sum n \le 5\times 10^5$，保证 $S$ 中只包含 $\tt{0}$ 和 $\tt{1}$。

**只有你通过本题的所有测试点，你才能获得本题的分数。**

## 样例 #1

### 输入

```
4
5 3
10011
4 5
1000
5 6
11111
9 6
011111011```

### 输出

```
4 3 2 5 1
-1
5 4 2 3 1
3 1 2 6 4 5 9 7 8```

# 题解

## 作者：Coffee_zzz (赞：8)

容易发现，给出的要求其实就是找到若干个可以相同的 $l$ 的非 $1$ 因数，设其和为 $s$，使得 $c \le s \le n-2$ 或 $s=n$。不能等于 $n-1$ 是因为剩下那个点会自环。

那我们可以考虑对 $l$ 作因数分解，然后对所有非 $1$ 因数作完全背包。

接下来考虑两个优化：

- 非质数因数可以被拆成若干个相同的质因数，所以不需要管 $l$ 的非质因数。

- 因为 $s$ 肯定不能大于 $n$，所以只需要管 $l$ 的小于 $n$ 的质因数。

那我们可以先线性筛一遍，然后枚举 $2\sim n$ 留下 $l$ 的质因数，跑完全背包并记录转移方案即可。最后一步可以用链表把转移方案转化成要求的排列。复杂度 $\mathcal O(nw(l))$，其中 $w(l)$ 表示 $l$ 的质因数的个数。

---

## 作者：Phartial (赞：7)

# P10034 「Cfz Round 3」Circle 题解

对于一个排列 $p$，我们连边 $i\to p_i$，则其构成了若干个环。$f_{p,k}(i)$ 的含义即为：从 $i$ 开始走 $k$ 步到达的点。

题目限制可以等价描述为：使所有满足 $S_i=\texttt{1}$ 的点都位于一个大小为 $l$ 的因数的环上。

注意到如果存在方案，则必然存在一种使所有环的大小都为质数的方案（否则我们就可以把其中大小不是质数的环拆成若干个大小为质数的环而不影响合法性）。

考虑把 $l$ 的所有 $\le n$ 的质因数弄出来，其最多只有 $15$ 个。环的大小只可能是这几种。

观察一下最终方案长啥样：其有 $k$ 个节点在大小为 $l$ 的质因数的环上，$n-k$ 个节点单独成一环（这些节点中不应有 $S_i=\texttt{1}$ 的点），有约束条件 $c\le k\le n,k\ne n-1$（其中 $c$ 是 $S$ 中 $\texttt{1}$ 的数量）。

跑一遍完全背包即可判断可行性并得到一个可行的 $k$，记录一下转移路径即可还原出方案。

需要特判 $l=0$，代码有点难写。

```cpp
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

const int kN = 5e5 + 1, kC = 16;

int tt, n, ans[kN], d[kN], id[kN], c;
bool f[kC][kN], p[kC][kN], ip[kN];
vector<int> tp, pl;
string s;
LL l;

bool S() {
  pl.assign(1, 0);
  for (int i : tp) {
    if (i > n) {
      break;
    }
    if (l % i == 0) {
      pl.push_back(i);
    }
  }
  int m = pl.size() - 1;
  f[0][0] = 1;
  for (int i = 1; i <= m; ++i) {
    for (int j = 0; j <= n; ++j) {
      f[i][j] = 0;
      if (f[i - 1][j]) {
        f[i][j] = 1, p[i][j] = 0;
      } else if (j >= pl[i] && f[i][j - pl[i]]) {
        f[i][j] = 1, p[i][j] = 1;
      }
    }
  }
  int k = c;
  for (; k <= n && (k == n - 1 || !f[m][k]); ++k) {
  }
  if (k > n) {
    return 0;
  }
  int x = 1;
  for (int i = m; i >= 1; --i) {
    for (; p[i][k]; k -= pl[i]) {
      int _x = x;
      for (int j = pl[i] - 1; j--; ++x) {
        ans[x] = x + 1;
      }
      ans[x++] = _x;
    }
  }
  if (x < n) {
    ans[n] = x;
    for (; x < n; ++x) {
      ans[x] = x + 1;
    }
  }
  return 1;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (int i = 2; i < kN; ++i) {
    if (!ip[i]) {
      tp.push_back(i);
    }
    for (int j : tp) {
      int k = i * j;
      if (k >= kN) {
        break;
      }
      ip[k] = 1;
      if (i % j == 0) {
        break;
      }
    }
  }
  for (cin >> tt; tt--;) {
    cin >> n >> l >> s;
    s = "#" + s;
    int m = 0;
    for (int i = 1; i <= n; ++i) {
      if (s[i] == '1') {
        id[d[i] = ++m] = i;
      }
    }
    c = m;
    if (!l) {
      for (int i = 2; i <= n; ++i) {
        cout << i << ' ';
      }
      cout << 1 << '\n';
      continue;
    }
    for (int i = 1; i <= n; ++i) {
      if (s[i] == '0') {
        id[d[i] = ++m] = i;
      }
    }
    if (S()) {
      for (int i = 1; i <= n; ++i) {
        cout << id[ans[d[i]]] << ' ';
      }
    } else {
      cout << -1;
    }
    cout << '\n';
  }
  return 0;
}
```


---

## 作者：玄学OIER荷蒻 (赞：5)

本题是 DP，重要一步是发现性质。

我们发现这个东西可以理解成是一堆置换环。

容易发现，只有在一个大小为 $l$ 的因数（而且这个因数不能为 $1$，否则会不满足 $p_i\ne i$ 的条件）的一个置换环里，才能符合 $S_i=1$ 时的条件。我们也可以为此放入一些 $S_i=0$ 的点好凑够成为 $l$ 的因数。

那么我们就需要用 $l$ 的因数，去凑成一个 $\sum\limits^n_{i=1}S_i \sim n$ 的数；要特别注意这个数不能是 $n-1$，否则会导致存在 $p_i=i$。

这部分可以完全背包，但 $l$ 的因数可能很多，于是我们考虑优化。

我们发现，所有不是质数的 $l$ 的因数都可以用若干个 $l$ 的质因数来凑出。（因为我们只需要跑完全背包，能被其他数凑出的就不需要）

由于 $2\times 3\times 5\times 7\times 11\times 13\times 17\times 19\times 23\times 29\times 31\times 37\times 41\times 43\times 47\times 53 > 10^{18}$，所以质因数最多 $15$ 个。

接下来，一个问题来了，我们要如何寻找质因数呢？

如果您想用 $\sqrt l$ 的暴力蒙混过关，那么恭喜您，一个大质数就能直接让您 T 到飞起。

我们发现只有 $n$ 以内的质因数是有用的（完全背包只需要做到 $n$），我们不妨 $1 \sim n$ 的质数遍历一遍，复杂度 $O(n)$（反正做完全背包的时候也肯定比 $O(n)$ 大了）。

我们可以在 DP 的时候记录转移过程，这样方案就可以直接根据转移过程填数了。

至此，问题就解决了。

---

## 作者：HPXXZYY (赞：2)

$\color{blue}{\texttt{[Solution]}}$

这是道好题。

建图，对每一个 $i \to p_{i}$ 都建立一个有向边，就可以得到一个 $n$ 个点 $n$ 条边组成的图。题目所需要满足的条件可以等价于从任何一个 $S_{i}$ 为 $\texttt{1}$ 的边出发走 $l$ 步都能回到自身，且图中不存在自环。

显然，如果存在一个大小为 $g$ 的环（点数一定等于边数，因为每个点的**入度和出度均为 $1$**），且 $g$ 为 $l$ 的约数，那么这个环上的任意一点均可以走 $l$ 步后回到自身。

根据这个想法，我们就可以判定是否有解：把 $l$ 所有的大于 $1$ 的约数找出来，假设记为 $d_{1},d_{2},d_{3},\cdots,d_{m}$，有解等价于存在**自然数（包括 $0$）序列 $a_{1 \dots m}$**，满足：

$$\sum\limits_{i=1}^{m} a_{i}d_{i}=\beta$$

其中 $\beta$ 是 $k$ 到 $n$ 的任意一个整数（$k$ 表示 $S$ 为 $\texttt{1}$ 的点的个数）。$\beta$ 表示我们需要将有限制的 $k$ 个点和无限制的点中任意的 $(\beta - k)$ 个一起组成若干个大小为 $d_{i}$ 的环（如果 $a_{i}$ 为 $0$，则不存在大小为 $d_{i}$ 的环）。假设环的大小分别为 $D_{1},D_{2},\cdots,D_{M}$。

显然，我们用背包即可判断是否有解。同时还可以知道我们需要构造哪些大小的环。

注意：$\beta$ 不能等于 $n-1$。如果 $\beta=n-1$，那么剩下的那一个没有限制的点需要形成自环，不合题意。

如果判断有解，剩下的事情就比较简单了：只要依次挑出 $D_{i}$ 个点首尾相连形成大小为 $D_{i}$ 的环即可。这部分比较简单，具体看代码。

$\color{blue}{\texttt{[Notice]}}$

1. 如果 $k=0$，即没有有限制的点，那么一定有解（$1 \to 2,2 \to 3, \cdots, n \to 1$ 即可）。不然会 WA on test $10$。
2. 只有 $(n-1)$ 是不合要求的，大小为 $n$ 的环是符合要求的。写代码时要注意这一点，不然会 WA on test $13$。
3. dp 的时候找到了解就要及时退出，减少代码运行量，不然会 TLE on test $14$。
4. 记得及时清空数组，毕竟是多测。

$\color{blue}{\text{Code}}$

```cpp
const int N=5e5+100;

bool f[N],limit[N];
char s[N];long long l;
int T,n,k,p[N],lst[N];
int Div[N],dcnt,beg;
int unlimit[N];

void initdata(){
	for(int i=1;i<=n;i++){
		p[i]=lst[i]=Div[i]=0;
		f[i]=limit[i]=false;
		unlimit[i]=0;
	}
	k=dcnt=beg=0;
}

int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d%lld",&n,&l);
		scanf("%s",s+1);
		
		initdata();
		
		for(int i=1;i<=n;i++)
			if (s[i]=='1'){
				k++;//统计有限制的点的个数
				limit[i]=true;
			}
		
		for(int i=2;i<=n;i++)
			if (l%i==0&&i!=n-1){
				f[i]=true;
				Div[++dcnt]=i;
				lst[i]=i;//别忘了这个
			}
		
		for(int i=1,flag=1;i<=dcnt&&flag;i++)
			for(int j=Div[i];j<=n;j++)
				if (f[j-Div[i]]&&!f[j]){
					f[j]=true;
					lst[j]=Div[i];
					if (k<=j&&j<=n&&j!=n-1){
						flag=1;break;//及时退出
					}
				}
		
		for(int i=k;i<=n;i++)
			if (f[i]&&i!=n-1){
				beg=i;//对应解析里的 beta
				break;
			}
		
		if (beg!=0){
			for(int i=1,l=0;l<n-beg;i++)
				if (!limit[i]) unlimit[++l]=i;
			if (beg!=n){
				for(int i=1;i<n-beg;i++)
					p[unlimit[i]]=unlimit[i+1];
				p[unlimit[n-beg]]=unlimit[1];
			}//多余的无限制的点也要连成环（不过环的大小没限制啦是真的）
			
			int l=0,r=0,cnt=0,tmp=beg;
			for(int i=1;i<=n;i++)
				if (!p[i]){
					if ((++cnt)==lst[tmp]){
						p[r]=i;
						tmp-=lst[tmp];
						cnt=0;
					}
					
					p[i]=l;l=i;
					if (cnt==1) r=i;
				}//构造解
		}
		
		if (k==0){
			for(int i=1;i<n;i++)
				printf("%d ",i+1);
			printf("1\n");
		}
		else if (!beg) printf("-1\n");
		else{
			for(int i=1;i<=n;i++)
				printf("%d%c",p[i],(i==n?'\n':' '));
		}
	}
	
	return 0;
}

Wish You Good Luck!
```

---

## 作者：快斗游鹿 (赞：2)

## 思路

观察题面，发现题目等价于给每个 $i$ 与 $p_i$ 之间连边，需要保证每个 $s_i=1$ 的 $i$ 都在一个长度为 $l$ 的因数的环上。

容易想到，只需要考虑 $l$ 的质因数即可，因为一个非质因数一定可以被拆成若干质因数之积。那么可以进一步转化，即是否存在一种方案，使用若干 $l$ 的质因数可以凑出 $k$。如果共有 $c$ 个 $1$，那么 $k$ 应当满足 $c\le k\le n,k\neq n-1$。因为如果 $k=n-1$，则最后一个点会形成自环，不符合题意。

跑完全背包并记录方案即可。代码细节比较多。注意质数要提前处理出来。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int T,n,L,a[N],p[50],f[N],id[N],cnt,ans[N],b[N],g[N],r[N],ddd,ccc;
int prime[N],pcnt;
bool flag[N],isprime[N];
string s;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void init(){
	for(int i=2;i<=5e5;i++){
		if(!isprime[i]){
			prime[++pcnt]=i;
		}
		for(int j=1;j<=pcnt&&i*prime[j]<=5e5;j++){
			isprime[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	//for(int i=1;i<=pcnt;i++)cout<<prime[i]<<" ";
	//cout<<endl;
}
signed main(){
	freopen("c.txt","r",stdin);
	//freopen("std.in","r",stdin);
	//freopen("a.txt","w",stdout);
	T=read();
	init();
	while(T--){
		n=read();L=read();int m=0;
		cin>>s;
		for(int i=1;i<=n;i++){
			a[i]=s[i-1]-'0';
			if(a[i])m++;
			flag[i]=0;
		}
		if(!L){
			for(int i=1;i<=n;i++)printf("%lld ",i+1>n?1:i+1);
			putchar('\n');
			continue;
		}
		int x=L;cnt=0;
		for(int i=1;i<=pcnt;i++){
			if(x%prime[i]==0)p[++cnt]=prime[i];
		}
		//cout<<m<<endl;
		//for(int i=1;i<=cnt;i++)cout<<p[i]<<" ";
		//putchar('\n');
		ccc=0;
		for(int j=0;j<=n;j++)f[j]=0;
		f[0]=1;
		for(int i=1;i<=cnt;i++){
			for(int j=p[i];j<=n;j++){
				if(f[j-p[i]]){
					f[j]=1;id[j]=p[i];
				}
			}
		}
		bool fff=0;
		for(int i=m;i<=n;i++){
			if(i==n-1)continue;
			if(f[i]){
				m=i;
				fff=1;break;
			}
		}
		if(!fff){
			puts("-1");continue;
		}
		int now=m;
		while(now){
			ans[++ccc]=id[now];now-=id[now];
		}
		//for(int i=1;i<=ccc;i++)cout<<ans[i]<<" ";
		//putchar('\n');
		int l=1,c=0;cnt=0;ddd=0;
		for(int i=1;i<=n;i++){
			if(l==ccc+1)break;
			if(a[i]){
				flag[i]=1;
				cnt++;b[++c]=i;
				if(cnt==ans[l]){
					b[c+1]=b[1];
					for(int j=1;j<=c;j++)g[b[j]]=b[j+1];
					cnt=0;c=0;
					l++;
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(l==ccc+1)break;
			if(!flag[i]){
				flag[i]=1;
				cnt++;b[++c]=i;
				if(cnt==ans[l]){
					b[c+1]=b[1];
					for(int j=1;j<=c;j++)g[b[j]]=b[j+1];
					cnt=0;c=0;
					l++;
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(!flag[i])r[++ddd]=i;
		}
		if(ddd==1){
			puts("-1");continue;
		}
		r[ddd+1]=r[1];
		bool F=0;
		for(int i=1;i<=ddd;i++)g[r[i]]=r[i+1];
		for(int i=1;i<=ddd;i++){
			if(g[i]==i)F=1;
		}
		if(F){
			puts("-1");continue;	
		}
		for(int i=1;i<=n;i++)printf("%lld ",g[i]);
		putchar('\n');
	}
	return 0;
}

```


---

## 作者：JuRuoOIer (赞：1)

# 题解 P10034 「Cfz Round 3」Circle

前排提示：阅读本题解所需的前置知识包括
- **简单的动态规划**（普及，$4$）
- **素数筛**（普及，$4$）

### 思路

众所周知，在排列上不断从 $i$ 跳到 $p_i$ 若干次后一定会回到 $i$。由于排列是自己构造的，我们希望这个“若干”能固定下来。不难发现可以一格一格动，即 $1$ 放到排列最后，$2$ 到 $n$ 从头开始排，这时这个“若干”即为排列长度 $n$。于是现在我们希望把整个排列拆成若干个子排列，每个排列都如此构造，这要求每个排列的长度都是 $l$ 的大于 $1$ 的因数。

>- 为什么全都这么构造不会漏情况？
>
>每次跳的格数是可以控制的。假设排列长为 $p$，每次固定跳 $x$ 格，那如果 $x\nmid p$ 就和每次跳一个没有区别（只是经过各格的顺序不同）；否则排列可以分为 $x$ 个子排列，每个长为 $\left\lfloor\dfrac{p}{x}\right\rfloor$，也都是像刚才那样构造的。

现在问题转化为：设 $S$ 中 $\texttt{1}$ 的个数为 $a$，求满足下列条件的 $k=k_1+k_2+\dots+k_c$：
- $a\le k\le n-2$ 或者 $k=n$（注意如果是 $n-1$ 的话最后剩的 $0$ 就只能在自己的位置上，这是不符合题意的）；
- $2\le k_1,k_2,\dots,k_c\le n$；
- $\forall1\le i\le c,k_i\mid l$。

发现加的本质就是质因数相加，因为假设 $l$ 存在一个因数 $x=y\times z$，其中 $y,z$ 是质数，那 $y$ 和 $z$ 也一定是 $l$ 的因数，加 $x$ 就是加 $y$ 个 $z$。

但是直接分解质因数还是太慢了。但是我们发现我们最后加起来的值不超过 $n$，也就是只有不超过 $n$ 的部分是有用的。于是结合刚才说的东西想到设 $i=f_i+g_i$，其中 $f_i$ 是已经确定能表示出的数，$g_i$ 是小于 $i$ 的 $l$ 的质因数。转移的时候前推后，如果当前的 $i$ 可以被表示出来，则枚举 $l$ 中小于 $i$ 的质因数（最多只有 $15$ 个不同的质因数）即可。至于一个因数是否是质因数，提前筛出 $1$ 到 $n$ 的质数，dp 的时候进行判断并记录质因数表即可。而且由于我们记录了是哪两个数加起来的，所以我们有把某个数拆开的方案来进行构造。

dp 的复杂度是 $O(n\log n)$（级别），构造的复杂度是 $O(n)$，所以总复杂度是 $O(n\log n)$，可以通过。

### 细节提醒

>感谢@[OIbishop](https://www.luogu.com.cn/user/748239) 大佬在讨论区中[说明了此问题](https://www.luogu.com.cn/discuss/824302)，大大减少了本人调代码的时间。

注意特判 $S$ 全为 $\texttt{0}$ 的情况。症状是 WA on #10。

### 代码

前面的数组的含义我说明了下，但不想看可以不看，直接看后面每个模块的实现就好。

```cpp
ll T,n,l,a,f[500010],g[500010],p[500010],flg[500010],isp[500010],pri[500010],cnt,t[500010],sum,pos;
//f,g 用于文中的 dp，p 存构造的排列，flg 标记是否需要构造进环中 
//isp 存是否是素数，pri 用于 dp 时存质因数，cnt 存 pri 中质因数个数 
//t 存每次 make() 时的点，sum 存 t 中点数，pos 表示 pos 以前被标记的点已完成构造 
string s;
void make(){
	//将 t 中所有点构造成一个环 各点偏离自己的下标 1 格
	for(int i=0;i<sum;i++){
		p[t[(i-1+sum)%sum]]=t[i]+1;
	}
}
void work(ll now){
	//将接下来 now 个 flg[] 为 1 的点构造完
	if(f[now]==-1){
		//该数可以直接进行构造 
		sum=0;
		while(now){
			if(flg[pos]){
				now--;
				t[sum++]=pos;
			}
			pos++;
		}
		make();
		return ;
	} 
	//拆成转移过来的两个数
	work(f[now]);
	work(g[now]);
}
int main(){
	ios::sync_with_stdio(0);
	//筛子
	isp[0]=isp[1]=1;
	for(int i=2;i<500010;i++){ 
		if(isp[i]==0){
			for(int j=i*2;j<500010;j+=i){
				isp[j]=1;
			}
		}
	}
	cin>>T;
	while(T--){
		cin>>n>>l>>s;
		//记得清空哦 
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		a=0;cnt=0;pos=0;
		//统计 1 的个数 
		for(int i=0;i<n;i++){
			a+=(s[i]=='1');
			flg[i]=(s[i]=='1');
		}
		//特判 1 的个数为 0 的情况
		if(a==0){
			sum=0;
			for(int i=0;i<n;i++){
				t[sum++]=i;
			}
			make();
			for(int i=0;i<n;i++){
				cout<<p[i]<<' ';
			}
			cout<<endl;
			continue;
		} 
		//dp
		ll tot=0;
		for(int i=2;i<=n;i++){
			if(l%i==0){
				if(!isp[i])pri[cnt++]=i;//存 l 的质因数 用于后续转移 
				//i 直接能被整除的情况，进行标记，与不能拼出的数（f=g=0）进行区分 
				f[i]=-1;
				g[i]=-1;
			}
			if(f[i]==0)continue;
			if(i>=a&&i<=n&&i!=n-1){
				//有解，记录总共的元素数量，以及标记需要构造进环的元素 
				tot=i;
				for(int j=0;i-a>0;j++){
					if(!flg[j]){
						i--;
						flg[j]=1;
					}
				}
				break;
			} 
			for(int j=0;j<cnt;j++){
				if(i+pri[j]>n)break;//防止越界 
				//转移 
				f[i+pri[j]]=i;
				g[i+pri[j]]=pri[j];
			}
		}
		if(!tot){
			//无解 
			cout<<"-1\n";
			continue;
		}
		//构造 p 
		work(tot);//构造 flg[] 为 1 的部分
		sum=0;
		for(int i=0;i<n;i++){
			if(!flg[i]){
				t[sum++]=i;
			}
		} 
		if(sum)make();//flg[] 为 0 的也不能在自己的位置上 
		//输出
		for(int i=0;i<n;i++){
			cout<<p[i]<<' ';
		} 
		cout<<endl;
	} 
	return 0;
}
```

---

## 作者：User_Authorized (赞：1)

首先可以发现给出的函数实质上是在连边 $i \rightarrow p_i$ 的图中走 $k$ 步到达的点的标号。

由于 $p$ 是一个排列，所以这个图是由若干个环组成的。

考虑有解的充要条件，即对于所有 $S_i = 1$ 的 $i$，其所在的环的长度 $k$ 都满足 $k \mid l$。由于对于 $S_i = 0$ 的 $i$ 无限制，所以我们统计出所有 $S_i = 1$ 的 $i$ 的个数 $C$，这样我们的问题就转化为了：

> 给定 $l, C, n$，构造一个可重集，使得其元素均为 $l$ 的因子，且元素和在 $\left[C, n - 2\right] \cup \left\{n\right\}$ 之间。

元素和不能为 $n - 1$ 是因为这样会剩余一个长度为 $1$ 的环，而题目中限制了 $p_i \neq i$，因此这样的环是不合法的。

可以发现，若其元素为合数，那么一定可以通过若干质因子构造出来，因此我们可以枚举质因子，然后判断其是否可以存在在集合中。那么可以发现可以在集合中的数只有 $\mathcal{O}(\log l)$ 种，因此我们可以进行完全背包，进而可以得到方案，时间复杂度为 $\mathcal{O}(n \log l)$，可以通过。

---

## 作者：ダ月 (赞：1)

建议读者每一段读完想一想怎么做。

首先，我们注意到，所有 $s_i=1$ 的点所在的环长为 $l$ 的非 $1$ 因子的时候题目就做完了。

更具体点，记 $s_i=1$ 的个数为 $r$，我们记 $l$ 有不同的质因子 $p_i$ 若干，记有 $P$ 个。我们需要构造出一个非负整数序列 $a_i$，存在 $w\in[r,n-1)\cup \{n\}$，满足 $\sum\limits_{i=1}^Pa_ip_i=w$ 即可。让后构造出来的序列，优先分配给 $s_i=1$ 的点，然后多余的分配给剩下的点。未分配的点构成一个环。

再详细点，对于 $\sum\limits_{i=1}^Pa_ip_i=w$，我们可以对每个不同的 $p_i$ 跑完全背包，记录转移过程。

我们记 $w(n)$ 表示 $n$ 不同的质因子的个数。$w(l)$ 很小，因此整个题的时间复杂度：$O(nw(n))$。

这一段可以选择性阅读：

不过，每个状态只有 $0$ 或者 $1$ 转移是不是太浪费了，我们考虑对每个物品拆成二进制，做 $01$ 背包，这样，我们可以用 bitset 优化。至于记录路径，可以参考 CF356D。时间复杂度：$O(\dfrac{nw(n)\log n}{W})$，$W=64$。

[code](https://www.luogu.com.cn/paste/7tqcwrpq)。不过 `bitset` 板子是从网上贺的。

---

我造了这题的数据。这题大概要注意一些东西：

1. $l=0$ 的情况；
2. $l=1$ 的情况；
3. 不能直接暴力质因数分解 $l$（当然，你非要 pollard_rho 我也没办法。），而是在 $1\sim n$ 种寻找。
4. 不要做成寻找 $1\sim n$ 中的 $l$ 因子，是质因子。
5. 注意，$w\neq n-1$，因为剩下未分配的点会自环，不合法。

如果你赛时做了这道题，有没有吃到这题的罚时？

---

## 作者：zxh923 (赞：0)

# P10034 「Cfz Round 3」Circle 题解

[题目传送门](https://www.luogu.com.cn/problem/P10034)
### 题意

先把题目转化一下，这里假设 $s$ 中 $1$ 的数量为 $c$：

特判一些奇妙情况，这里判的是 $l=0$ 或者 $c=0$。

题目即为 $\exists x\in[c,n]$ 且 $x\ne n-1$，使得存在 $k$ 和序列 $y$，$\displaystyle\sum_{i=1}^{k}y_i=x$，且 $y_i\mid l,y_i>1,y_i\le n$。

比较正常的描述：所有在字符串中为 $1$ 的位置均需处于一个长度为 $l$ 的因数的环中，你需要构造出这样一个图。

### 思路

为什么 $x$ 不能是 $n-1$ 和 $1$ 呢，因为这样一定有一个数会不满足 $p_i\ne i$ 的条件。

接下来开始分析，首先看上述的整除条件，那显然如果一个数不是 $l$ 的质因数但是因数，显然可以用一些同样的质因数加和得到，所以选质因数是最优即最可能满足条件的。

所以考虑先用埃筛或线筛筛质数，方便接下来找质因数的过程。

输入时如果发现 $s_i=1$，标记它。

接下来把东西清空，顺便特判刚才提到的情况，如果特判不成立，在 $1\sim n$ 中遍历找出满足条件（是 $l$ 的因数）的质数，记作 $pre_{cnt}$，然后 $cnt\leftarrow cnt+1$，建议 $cnt$ 初始为 $1$。

然后用一个背包判断哪些数可以被凑出来，转移方程 $dp_i=dp_i$ 和 $dp_{i-pre_j}$ 的或，如果 $dp_{i-pre_j}$ 为 $1$ 即可以被凑出来，我们记录 $i$ 可以由 $i-pre_j$ 转移。

转移完之后，遍历 $c\sim n$，找出一个不是 $n-1$ 的数且它的 $dp$ 数组为 $1$，记作 $ned$。

如果发现没有找到合法的 $ned$，输出 `-1` 即可。

接下来找 $ned-c$ 个 $i$ 满足 $s_i=0$，标记它们，为了方便，把标记数组从小到大排序。

然后进行递归，对 $ned$ 拆成它的一个记录数组的值和 $ned$ 减去这个记录数组的值，如果遇到这个数是一个合法质因数，记录 $ans$ 即可。

### 代码

代码思路已经描述得很清楚了，就不给注释了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 500005
#define lim 500000
using namespace std;
int t,n,dp[N],p[N],tot,cnt,k,pre[N],ned,v[N],fir,ans[N],top,op;
char s[N];
bool vis[N];
vector<int>e[N];
queue<int>q;
void init(){
	vis[0]=vis[1]=1;
	for(int i=2;i<=lim;i++){
		if(!vis[i]){
			for(int j=i*2;j<=lim;j+=i){
				vis[j]=1;
			}
		}
	}
}
void clear(){
	ned=cnt=tot=0;
	fir=1;
	for(int i=1;i<=n;i++){
		e[i].clear();
		ans[i]=p[i]=pre[i]=v[i]=dp[i]=0;
	}
}
void dfs(int x){
	if(!x)return;
	if(!vis[x]&&!(k%x)){
		for(int i=fir;i<=fir+x-1;i++){
			if(i!=fir+x-1)ans[v[i]]=v[i+1];
			else ans[v[i]]=v[fir];
		}
		fir+=x;
		return;
	}
	for(int y:e[x]){
		dfs(y);dfs(x-y);
		return;
	}
}
signed main(){
	init();
	cin>>t;
	while(t--){
		cin>>n>>k;
		clear();
		for(int i=1;i<=n;i++){
			cin>>s[i];
			if(s[i]=='1'){
				p[i]=1;
				v[++tot]=i;
			}
			if(!vis[i]&&!(k%i)){
				pre[++cnt]=i;
				dp[i]=1;
			}
		}
		if(!k||!tot){
			cout<<n<<' ';
			for(int i=1;i<n;i++){
				cout<<i<<' ';
			}
			cout<<'\n';
			continue;
		}
		for(int j=1;j<=cnt;j++){
			for(int i=1;i<=n;i++){
				if(pre[j]>i)continue;
				dp[i]|=dp[i-pre[j]];
				if(dp[i-pre[j]])e[i].push_back(pre[j]);
			}
		}
		for(int i=tot;i<=n;i++){
			if(dp[i]&&i!=n-1){
				ned=i;
				break;
			}
		}
		if(!ned){
			cout<<"-1\n";
			continue;
		}
		for(int i=1;i<=n;i++){
			if(tot==ned)break;
			if(s[i]=='1')continue;
			v[++tot]=i;
			p[i]=1;
		}
		sort(v+1,v+tot+1);
		for(int i=1;i<=n;i++){
			if(p[i])continue;
			q.push(i);
		}
		dfs(ned);
		if(!q.empty()){
			op=q.front();
			while(q.size()>1){
				top=q.front();
				q.pop();
				ans[top]=q.front();
			}
			ans[q.front()]=op;
			q.pop();
		}
		for(int i=1;i<=n;i++){
			cout<<ans[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

