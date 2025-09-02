# 【MX-X2-T2】「Cfz Round 4」Xor Counting

## 题目背景

原题链接：<https://oier.team/problems/X2B>。

---

生きてもいいような　気がして  
或者　就这样活着也不错吧  

繰返し笑い合うんだ　居たくなる旅  
想要有一段充满欢笑的旅程啊

## 题目描述

给定一个长度为 $n$ 的**非负整数**序列 $a_1, \ldots, a_n$。

请你求出满足 $a_i \le (a_i \oplus a_j) \le a_j$ 的下标对 $(i, j)$ 的数量。其中 $\oplus$ 表示**按位异或**，即 C++ 中的 `^`。


## 说明/提示

**【样例解释】**

对于第 $1$ 组测试数据，满足条件的下标对有 $(2,1),(2,2),(2,3),(2,4),(3,1),(3,4)$。

**【数据范围】**

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有测试数据，$1 \le T \le 1000$，$1 \le n \le 5\times10^5$，$0 \le a_i \lt 2^{30}$，$\sum n \le 5\times10^5$。

**本题采用捆绑测试。**

- Subtask 1（30 points）：$\sum n \le 1000$。
- Subtask 2（30 points）：$a_i \ge 1$。
- Subtask 3（40 points）：无特殊限制。

## 样例 #1

### 输入

```
7
4
3 0 1 3
5
0 1 2 3 4
1
6
1
0
6
1 1 4 5 1 4
10
10 32 43 28 19 83 10 10 83 23
15
132 256 852 31 1 0 12 13 12 0 0 255 143 23 32```

### 输出

```
6
6
0
1
3
12
65```

# 题解

## 作者：Butterfly_qwq (赞：16)

简单题。

考虑什么时候会满足条件，设 $a_i<a_j$。

现在 $a_i$ 和 $a_j$ 的最高位不能相同，否则，$a_i\oplus a_j<a_i$。

然后 $a_i$ 的最高位在 $a_j$ 中必须是 $1$，否则 $a_i\oplus a_j>a_j$。

显然只需统计满足这些条件的数目就行了。枚举 $i$，看有多少个 $j$ 满足条件，具体直接维护两个数组，一个是有多少个数满足最高位是定值，一个是有多少数的第定值位是 $1$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,ans,a[500005],hb[500005],ct1[500005],ct2[500005];
int highbit(int x)
{
	if(!x)return 114514;
	for(int j=30;~j;j--)if(x&(1<<j))return j;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		memset(ct1,0,sizeof(ct1));
		memset(ct2,0,sizeof(ct2));
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			hb[i]=highbit(a[i]);
			ct2[hb[i]]++;
			for(int j=30;~j;j--)if(a[i]&(1<<j))ct1[j]++;
		}ans=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i])ans+=ct1[hb[i]]-ct2[hb[i]];
			else ans+=n;
		}
		cout<<ans<<'\n';
	}
}
```

---

## 作者：Coffee_zzz (赞：13)

显然，对于正整数 $p,q$，设 $p,q$ 在二进制表示下的位数分别为 $x,y$，若 $p\le q$，则：

- $p \le p \oplus q$，当且仅当 $x \ne y$，因为若 $x=y$ 则 $p$ 和 $q$ 异或后最高位会抵消，$p \oplus q$ 一定小于 $p$ 和 $q$；
- $p \oplus q \le q$，当且仅当 $q$ 在二进制表示下的第 $x$ 位为 $1$，因为若 $q$ 在二进制表示下的第 $x$ 位为 $0$，则 $q$ 与 $p$ 异或后一定会变大。

要注意，对于任意非负整数 $m$，都满足 $0 \le 0 \oplus m \le m$，所以需要特判 $0$。

在特判 $0$ 后，我们可以把剩下的元素从小到大排序，开一个桶，把枚举过的数在二进制表示下的位数记录在桶里，动态地根据上面的讨论计算即可。

时间复杂度 $\mathcal O(n \log n+n \log V)$，其中 $V$ 为值域。

---

## 作者：shuqiang (赞：8)

$30$ 分做法：考虑暴力枚举每一个 $(i,j)$，时间复杂度 $O(n^2)$。

代码：

```cpp
#include<iostream>

using namespace std;

const int N = 1e5 * 5 + 10;
int t, n, a[N];

int main(){
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 0; i < n; i++) cin >> a[i];
		int ans = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
                //a[i] ^ a[j] 记得加括号
				if(a[i] <= (a[i] ^ a[j]) && (a[i] ^ a[j]) <= a[j]){
					ans++;
				}
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
```


满分做法：

可以用打表找规律的做法，把暴力枚举的代码改一下：
```cpp
#include<iostream>

using namespace std;

int main(){
	for(int i = 1; i <= 16; i++){
		cout << i << ": ";
		int cnt = 0; 
		for(int j = 1; j <= 100; j++){
			if(i <= (i ^ j) && (i ^ j) <= j){
				cout << j << ' ';
				cnt++;
			}
			if(cnt > 10) break;
		} 
		cout << '\n';
	}
	return 0;
}
```

输出为（加了注释，第一行是变化规律，第二行是转化为二进制后的数）：

```cpp
1: 3 5 7 9 11 13 15 17 19 21 23
// 3 -> +2 ...;
// 11 -> 101 -> 111 -> 1001
2: 6 7 10 11 14 15 18 19 22 23 26
3: 6 7 10 11 14 15 18 19 22 23 26
// 6 -> +1 -> +3
// 110 -> 111 -> 1010 -> 1011 -> 1110 -> 1111
4: 12 13 14 15 20 21 22 23 28 29 30
5: 12 13 14 15 20 21 22 23 28 29 30
6: 12 13 14 15 20 21 22 23 28 29 30
7: 12 13 14 15 20 21 22 23 28 29 30
// 12 -> +1 -> +1 -> +1 -> +5;
// 1100 -> 1101 -> 1110 -> 1111 -> 10100
8: 24 25 26 27 28 29 30 31 40 41 42
9: 24 25 26 27 28 29 30 31 40 41 42
10: 24 25 26 27 28 29 30 31 40 41 42
11: 24 25 26 27 28 29 30 31 40 41 42
12: 24 25 26 27 28 29 30 31 40 41 42
13: 24 25 26 27 28 29 30 31 40 41 42
14: 24 25 26 27 28 29 30 31 40 41 42
15: 24 25 26 27 28 29 30 31 40 41 42
16: 48 49 50 51 52 53 54 55 56 57 58
```


可以发现，当 $2 \le i \le 3$ 时满足条件的 $j$ 是一样的，当 $4 \le i \le 7$ 时满足条件的 $j$ 是一样的……，归纳一下，当 $2^{x-1} \le i \le 2^x-1$ 时满足条件的 $j$ 是一样的，所以可以开一个桶，按照上面不等式中的 $x$ 来计数，这段代码的复杂度为 $\mathcal{O}(\log V)$，其中 $V$ 是 $a_i$ 的值域。

接下来可以观察当 $2^{x-1} \le i \le 2^x-1$ 时满足条件的 $j$ 与 $x$ 有关的规律，观察每一组最小 $j$，发现每一个最小的 $j$ 都是上一个的两倍，所以可以推出 $j \ge 2^{x-1} \times 3$。第二个规律可以尝试把上面符合条件的 $j$ 转化成二进制，发现 $j$ 转化为二进制时的倒数第 $x$ 位是 $1$ 时 $j$ 满足条件。这里可以再开一个桶来统计，然后要特判一下 $i=0$，当 $i=0$ 时所有的 $j$ 都满足条件，这段代码的复杂度也为 $\mathcal{O}(\log V)$。

最后遍历两个桶，统计答案就可以了，单个测试点的复杂度为 $\mathcal{O}(n \log V)$。

AC 代码：

```cpp
#include<iostream>

using namespace std;

const int N = 1e5 * 5 + 10;
int t, n, a[N], b[35], c[35]; 
//记得开 long long。 
long long ans = 0;

int f1(int x){
	int cnt = 0;
	while(x) {cnt++; x >>= 1;}
	return cnt;
}

bool f2(int x, int y){
	if(y == 0) return 1;
	int t1 = (1 << (y-1));
	int t2 = t1 + (1 << y);
	if(x < t2) return 0;
	return x & t1;
}

int main(){
	cin >> t;
	while(t--){
		for(int i = 0; i <= 30; i++) b[i] = c[i] = 0;
		ans = 0;
		cin >> n;
		for(int i = 0; i < n; i++){
			cin >> a[i];
			b[f1(a[i])]++;
			for(int j = 0; j <= 30; j++) c[j] += f2(a[i], j);
		}
		for(int i = 0; i <= 30; i++){
			ans += (long long) b[i] * c[i];
		}
		cout << ans << '\n';
	}
	return 0;
}

```

---

## 作者：xxseven (赞：7)

这是一篇 01 Trie 题解。

首先判掉所有的 $0$，每一个 $0$ 的贡献为 $n$。

考虑从小到大枚举每一个数，统计以该数作为 $a_j$ 的下标对数量后加入 Trie 中。

首先有一个结论：如果两数 $x,y$ 的二进制表示下位数相同，那么这两数肯定不满足条件。因为两数异或后最高位变为 0，小于任何一个数。

这样，我们按位数将数分段，由于每一段内没有贡献，可以先进行这一段的统计，再将其全部加入 Trie 中。

这样做的好处是，由于当前的数位数一定大于 Trie 内部的所有数，$a_i \le (a_i \oplus a_j)$ 这个限制是自然成立的。接下来，只需要找到满足使得 $(a_i \oplus a_j) \le a_j$ 的数即可。

这个限制是满足贪心条件的：只要一位由 $1$ 改变为 $0$，下面的所有位无论怎么变化，新数还是小于原数。

那我们的查询方式就显而易见了：首先记录每个子树的大小，查询时忽略掉这个数的最高位，之后如果有一位为 $1$，那么 $1$ 子树内的所有数都能使其满足条件，使答案加上子树大小即可。之后，我们移动至 $0$ 子树，代表不改变这一位的情况。

时间复杂度 $O(n \log n+ n \log v)$，可以通过此题。

下面是赛时代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=5e5+6;
int ans,n,a[N],trie[N<<5][2],siz[N<<5],idx;

void ins(int x){
	int rt=1;
	for(int i=30;i>=0;--i){
		int u=(x>>i)&1;
		if(!trie[rt][u]) trie[rt][u]=++idx;
		rt=trie[rt][u];
		siz[rt]++;
	}
}

int qry(int x){
	int res=0,rt=1; int temp=x; 
	x-=(1<<(__lg(x)));
	for(int i=30;i>=0;--i){
		int u=(x>>i)&1;
		if(u==1) res+=siz[trie[rt][1]];
		rt=trie[rt][0];
	}
	if(rt!=0) res+=siz[rt];
	return res;
}

signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T; cin>>T;
	while(T--){
		for(int i=0;i<=idx;++i) siz[i]=trie[i][0]=trie[i][1]=0;
		cin>>n; ans=0; idx=1;
		for(int i=1;i<=n;++i) cin>>a[i];
		sort(a+1,a+n+1);
		int pos=1; 
		while(a[pos]==0&&pos<n) ans+=n,pos++;
		if(a[n]==0) ans+=n;
		for(int L=pos,R;;L=R+1){
			R=L;
			while((__lg(a[L])==__lg(a[R+1]))&&R<n) R++;
			for(int i=L;i<=R;++i)
				ans+=qry(a[i]);
			for(int i=L;i<=R;++i)
				ins(a[i]);
			if(R==n) break;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：thh_loser (赞：5)

# P10853 【MX-X2-T2】「Cfz Round 4」Xor Counting 题解

[题目链接](https://www.luogu.com.cn/problem/P10853)

## 题意

给定一个长度为 $n$ 的非负整数序列 $a_1, \ldots, a_n$，求出满足 $a_i \le (a_i \oplus a_j) \le a_j$ 的下标对 $(i, j)$ 的数量

## 思路

考虑满足题意的下标对 $(i, j)$，如果 $a_i \le (a_i \oplus a_j) \le a_j$，由于是异或运算，则 $a_j$ 的二进制位数至少比 $a_i$ 大 $1$，否则异或得到的结果一定小于 $a_i$（因为最高位变成 $0$ 了）。同时我们考虑如何使异或结果小于 $a_j$：如果 $a_j$ 在 $a_i$ 的最高位上对应位置为 $0$，则异或后这个位置就会变为 $1$，一定比 $a_j$ 大，从而导致不符合条件。

于是我们可以先将 $a$ 数组排序，再逐个统计位数，进行前缀和，计算的时候按照二进制位数分组，每次将相同位数的一起统计，该位数的答案即为更高位数中该位为 $1$ 的数个数之和（可以用前缀和统计）。

## code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[500010];
int hig[500010],ans;
int p[500010][32];
void fun(int x,int id){
	int xx=0;
	while(x){
		p[id][xx]+=(x&1);//二进制统计 
		x>>=1;
		xx++;
	}
	hig[id]=xx-1;//记录位数 
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		for(int i=1,x;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		sort(a+1,a+n+1);//先排序 
		for(int i=1;i<=n;i++){
			for(int j=0;j<=31;j++){
				p[i][j]=p[i-1][j];//前缀和统计每一位 
			}
			fun(a[i],i);
		}
		for(int i=1;i<=n;){
			int k=i;
			while(hig[i]==hig[k]&&k<=n){//将相同位数的一起统计 
				k++;
			}
			if(!a[i])ans+=(k-i)*n;//注意为0的与任何数（包括自己）都合法 
			else{
				ans+=(k-i)*(p[n][hig[i]]-p[k-1][hig[i]]);//前缀和统计后面 该位为1的数 的 个数 
	//			cout<<(k-i)<<" "<<p[n][hig[i]]-p[k-1][hig[i]]<<endl;
			}
			i=k;
		//	cout<<k<<" "<<ans<<endl;
		}
		cout<<ans<<"\n";
	}
}
```

---

## 作者：lzxyl (赞：3)

### 题目描述

给定一个长度为 $n$ 的**非负整数**序列 $a_1, \ldots, a_n$。

请你求出满足 $a_i \le (a_i \oplus a_j) \le a_j$ 的下标对 $(i, j)$ 的数量。其中 $\oplus$ 表示**按位异或**，即 C++ 中的 `^`。

### 解题思路

题目要求求出满足 $a_i \le (a_i \oplus a_j) \le a_j$ 的下标对 $(i, j)$ 的数量，对此我们可以分别枚举下标 $i,j$，进行比较判断，然后累加答案，最终得分 $30$ 分。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int a[N];
int main(){
	int t,n;
	cin>>t;
	while(t--){
		cin>>n;
		int ans=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int x=a[i]^a[j];
				if(a[i]<=x&&x<=a[j]) ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
下面来进行优化。

设有两个正整数 $a,b$，且它们在二进制下的位数分别表示为 $x,y$。

由题意，我们可知：$a,b$ 之间是满足 $a \le (a \oplus b) \le b$ 的，而异或运算是指两个数在二进制的表示下，两个对应位相同，则异或结果该位为 $0$，否则为 $1$。

根据以上条件，我们可以得出：

当 $x=y$ 时，异或结果的第 $x,y$ 位会变成  $0$，所以 $(a \oplus b) < a,b$，故不满足题意。

当 $b$ 在二进制表示下的第 $x$ 位为 $1$ 时，这时异或结果的第 $x$ 位会变成 $0$，$(a \oplus b)$ 的值变小，从而满足 $(a \oplus b) \le b$，而且因为 $y>x$，所以满足 $a \le (a \oplus b)$。

综上所述，当 $x=y$，且 $b$ 在二进制表示下的第 $x$ 位为 $1$ 时，满足题意。

由此，我们需要做的就是分别累加所有数的最高位的个数，和每个数在二进制下位数为 $1$ 的个数，最后再将它们的差进行求和。

这里需要注意的是，$0$ 需要特判，因为 $0$ 与任何一个自然数都符合题意。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10,M=40;
int a[N],b[N];
long long x[M],y[M];
int get(int m){
	if(!m) return 31;//用31是因为0~30的下标都可能被用，借此区分开来
	for(int i=30;i>=0;i--){
		if(m&(1<<i)) return i;
	}
}
int main(){
	int t,n;
	cin>>t;
	while(t--){
		cin>>n;
		long long ans=0;
		memset(x,0,sizeof x);
		memset(y,0,sizeof y);
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			b[i]=get(a[i]);//记录数的最高位
			x[b[i]]++;//记录最高位出现次数
			for(int j=30;j>=0;j--){
				if(a[i]&(1<<j)) y[j]++;//记录所有数每一位上非0值个数
			}
		}
		for(int i=1;i<=n;i++){
			if(a[i]) ans+=y[b[i]]-x[b[i]];
			else ans+=n;//特判0,因为0与任何一个自然数都符合题意
		}
		cout<<ans;
		if(t) puts("");//判断一下是否输出空行
	}
	return 0;
}
```
点个赞吧，谢谢~

---

## 作者：FreedomKing (赞：3)

简单题结论题。

### 思路

显然的，可以考虑对 $a_j$ 归纳合法 $a_i$ 的性质。不难看出当 $a_i$ 对应的 $a_j$ 的二进制最高位那位为 $0$，那么就能得出 $(1????)_2\oplus(0????)_2=(1????)_2$，其中 $\oplus$ 表示按位异或，$?$ 表示此位上的数不确定，这样得出来的数肯定是不优的，所以我们可以由此推出对于任一对于 $a_j$ 合法的 $a_i$，$a_j$ 对应的 $a_i$ 二进制最高位必然为 $1$。

记录 $f_k$ 表示所有以 $k$ 为二进制最高位数的总数，每次对于一个 $a_j$ 枚举其二进制下每一位统计即可。

### AC Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=5e5+5,mN=1e3+5,mod=1e9+7;
namespace FreedomKing_qwq{
#define lowbit(_) (_&-_) 
	struct Tree{
		int tree[N];
		inline void add(int x,int j){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=j;
			return;
		}
		inline int query(int x){
			int ans=0;
			for(int i=x;i>1;i-=lowbit(i)) ans+=tree[i];
			return ans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[y]=x;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}    
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
	inline int abss(int x){return (x>=0?x:-x);}
}
int a[N],f[N];
inline int fppc(int x){
	int cnt=0;
	while(x>0){
		cnt++;
		x>>=1;
	}
	return cnt-1;
}
signed main(){
	int T=qr;
	while(T--){
		int n=qr,ans=0;
		for(int i=0;i<=30;i++) f[i]=0;
		for(int i=1;i<=n;i++){
			a[i]=qr;
			ans+=n*(a[i]==0);
			f[fppc(a[i])]++;
		}
		for(int i=1;i<=n;i++)
			for(int j=0;j<fppc(a[i]);j++)
				if(a[i]&(1<<j))
					ans+=f[j];
		qwe(ans+cnt);
	}
	return 0;
}
```

---

## 作者：_Supernova (赞：3)

### 一、前言

一道很好的思维题，考察了异或的性质和位运算的功底。考场上没想出来。

### 二、思路分析

首先，异或的一大性质为若给定一个数 $x$，则有：

$x\oplus0=x$。

于是若 $a_i=0$，则对答案的贡献为 $n$。

非零情况呢？

我们记 $t=a_i\oplus a_j$。

因为 $a_i\leq t\leq a_j$，注意到 $a_i\leq a_j$。

当 $a_i=a_j$ 时，当且仅当 $a_i=0$ 时，已在之前的考虑范畴中。

于是考虑 $a_i<a_j$。

根据不等式，注意到 $i$ 的最高位一定不高于 $j$ 的最高位。

同时，若 $i$ 的最高位等于 $j$ 的最高位，则有 $t<a_i$，不合法。

故 $j$ 最高位大于 $i$ 最高位。

记 $i$ 最高位为 $w$。

若 $j$ 的第 $w$ 位为 $0$，则有 $t>a_j$，不合法。

故 $j$ 的第 $w$ 位为 $1$。

以上可能有点啰嗦，但是讲解的非常详细。

我们把思路理一遍。

首先，记 $bit_i$ 表示有多少个数最高位为 $i$，并求出该数组。

记 $numb_i$ 表示有多少个数第 $i$ 位为 $1$。

记 $obit_i$ 表示第 $i$ 个数的最高位。

从左到右遍历 $a$ 数组。求值即可。

详情见代码。

时间复杂度 $O(TN)$。常数不大，可以通过本题。

记得每组数据要初始化！


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair <int, int> pii;
const int N = 5e5 + 5;
ll t, n, a[N], ans, bit[N], obit[N], numb[N];
int max_bit(ll x) { // 求最高位
	if (!x) {
		return 35;
	}
	for (ll i = 30; i >= 0; --i) 
		if (x & (1 << i)) 
			return i;
}
void init(void) { // 初始化
	ans = 0;
	memset(bit, 0, sizeof bit);
	memset(numb, 0, sizeof numb);
	return ;
}
int main(void) {
	cin.tie(0), cout.tie(0);
	cin >> t;
	while (t--) {
		init();
		cin >> n;
		for (ll i = 1; i <= n; ++i) {
			cin >> a[i];
		}
		for (ll i = 1; i <= n; ++i) {
			obit[i] = max_bit(a[i]); // 求最高位
			++bit[obit[i]]; // 统计最高位
			for (ll j = 30; j >= 0; --j) {
				if (a[i] & (1 << j)) {
					++numb[j]; // 依次统计
				}
			}
		}
		for (ll i = 1; i <= n; ++i) {
			if (!a[i]) { // 特判
				ans += n;
			}
			else {
				ans += (numb[obit[i]] - bit[obit[i]]); // 贡献
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
```
感谢管理员的审核！谢谢大家！

---

## 作者：zhoumurui (赞：3)

### 题面展示

给定一个长度为 $n$ 的**非负整数**序列 $a_1, \ldots, a_n$。

请你求出满足 $a_i \le (a_i \oplus a_j) \le a_j$ 的下标对 $(i, j)$ 的数量。




首先想到对数组排个序，这样在考虑一个数作为 $a_i$ 时，就只需计算它右边的数作为 $a_j$ 的贡献了，除非 $a_i =0 $，为了方便后续处理，我们把 $0$ 都特判掉，$0$ 可以和任何数配对，**包括自己**。

现在给出一个结论：$a_i$ 可以与 $a_j$ 配对的充要条件是 $a_j$ 在 $a_i$ 的最高位上是 $1$，且该位不是 $a_j$ 的最高位。

必要性容易证明，这里证明充分性：

1. 假设 $a_j$ 在二进制中的位数不大于 $a_i$ 在二进制中的位数，那么因为 $a_i \le a_j$，两数的位数显然相等，那么两数在 $a_i$ 的最高位上都是 $1$，异或起来以后自然变成了 $0$，那么 $a_i \oplus a_j < a_i$，与已知条件矛盾。

2. 假设 $a_j$ 在 $a_i$ 的最高位上是 $0$，那么 $a_i \oplus a_j$ 在该位上必然是 $1$，而 $a_i \oplus a_j$ 与 $a_j$ 在 $a_i$ 最高位上方显然相等，那么那么 $a_i \oplus a_j > a_j$，与已知条件矛盾。

那么原命题得证，我们只需统计在某个数以后，二进制的某一位上是 $1$ 且该位不是这个数的最高位的数的数量就可以了。

这个过程可以用后缀和实现，这样这个题就做完了。

### 核心代码展示

```cpp
int a[500005];
int b[500005][32],c[500005][32];
signed main(){
    while (t--){
        sort(a+1,a+1+n);
        int ans=0;
        for (int j=29;j>=0;j--){
                b[n+1][j]=0;
                c[n+1][j]=0;
            }
        for (int i=n;i>=1;i--){
            for (int j=29;j>=0;j--){
                b[i][j]=b[i+1][j]+((a[i]>>j)&1);
                c[i][j]=c[i+1][j]+(((a[i]>>j)&1)&&((a[i]>>j+1)));
            }
        }
        for (int i=1;i<=n;i++){
            if (a[i]==0){
                ans+=n;
                continue;
            }
            int d=29;
            for (;d>=0;d--){
                if (b[i][d]>b[i+1][d])break;
            }
            ans+=c[i+1][d];
        }
        cout<<ans<<endl;
    }

---

## 作者：Melo_qwq (赞：2)

参考了[这位大佬的题解](https://www.luogu.com.cn/article/ur76ay47)，想解释得再详细一点。
## 题目大意
需要注意对 $(i,j)$ 是有序的。

注意开 long long。
## 题目实现
我们不妨设 $a_i<a_j$。

首先，如果这两个数位数相同（也就是最高位相同），那么 $a_i\oplus a_j$ 一定小于 $a_i$，因为最高位被抵消了。

然后，现在我们可以假设 $a_i$ 的位数小于 $a_j$ 的，那么 $a_i$ 的最高位对应到 $a_j$ 上的那个数字必须是 $1$，否则 $a_j$ 一定会变大。

总结：只用考虑最高位，不用考虑后面的，因为最高位优一定更大，最高位劣一定更小（~~小学数学？~~）。

需要特判 $0$ 的情况，容易证明对于 $0$ 任意的数都是合法的。

### 推销：新增“代码解释”部分。

首先求最高位，只需从高到低枚举即可：

```cpp
inline int get_high (const int &a) {
	if (! a) return -1 ;
	for (int i = 30 ;i != -1 ;i --) {
		if ((1 << i) & a) return i ;
	}
}
```
所以对于每个数，我们开一个桶统计一下最高位的出现次数：``tot1[get_high (a[i])] ++ ;``。

但是这个显然不够，所以我们再开一个桶统计每个数的为 $1$ 的位的出现次数：


```cpp
for (int j = 30 ;j != -1 ;j --) {
	if ((1 << j) & a[i]) tot2[j] ++ ;
}
```

最后统计答案，先放代码：

```cpp
f (i ,1 ,n ,1) {
	if (! a[i]) {
		ans += n ;
	} else ans += tot2[get_high (a[i])] - tot1[get_high (a[i])] ;
}
```
其中 ``tot2`` 表示对于当前数的最高位，有多少个数的这一位是 $1$，此时这些数有两种情况：当前位是最高位或者不是。

根据我们的推导，第一种情况不合法，也就是说要减去这一位是最高位的数的数量，也就是 ``tot1``。

不难发现其他情况都是合法的。

---

## 作者：Lucyna_Kushinada (赞：1)

这里提供一个复杂度为 $O(n \log V)$ 的做法。

先讨论 $0$，$0$ 非常特殊，任何一个非负整数异或上 $0$ 都是它本身，所以序列 $a$ 中的每一个 $0$ 都会有 $n$ 的贡献。

然后我们讨论正整数的情况，设两个正整数 $x$ 与 $y$，并且 $x\le(x\oplus y)\le y$，因为 $x\oplus x=0$，所以一定有 $x<y$。

接下来我们先不妨将 $x$ 赋一个值，再去看看 $y$ 能取什么值。  
设 $x=1$，$y$ 从小到大可以取 $3,5,7,9,11,13$ 等。  
设 $x=2$，$y$ 从小到大可以取 $6,7,10,11,14,15$ 等。  
设 $x=3$，$y$ 从小到大也可以取 $6,7,10,11,14,15$ 等。  
设 $x=4$，$y$ 从小到大可以取 $12,13,14,15,20,21,22,23$ 等。

这显然是有规律的，$y$ 的所有取值所构成的序列是由若干个连续且长度相等的小序列组成的，相邻两个小序列间首尾的差值也等于小序列的长度。

不妨设每个 $x$ 对应 $y$ 所有取值构成的序列中小序列的长度为 $len$。设每个 $x$ 对应 $y$ 的最小取值为 $y_{min}$

于是可以整理出一张表。

|$x$|$len$|$y_{min}$|$\lfloor \log_2x\rfloor$|
|:-:|:-:|:-:|:-:|
|$1$|$1$|$3$|$0$|
|$2$|$2$|$6$|$1$|
|$3$|$2$|$6$|$1$|
|$4$|$4$|$12$|$2$|
|$5$|$4$|$12$|$2$|
|$6$|$4$|$12$|$2$|
|$7$|$4$|$12$|$2$|
|$8$|$8$|$24$|$3$|

不难发现，$len=2^{\lfloor \log_2x\rfloor}$，而 $y_{min}=3\times len$。

也就是说，所有满足 $\lfloor \log_2x\rfloor$ 相等的 $x$ 值，其 $y$ 所有的取值也都是相等的。

这条结论一出来，我们便可以回到序列 $a$ 中，将所有正整数的 $a_i$ 分成 $31$ 组，$a_i$ 处于第 $\lfloor \log_2a_i\rfloor$ 组。

接下来，直接开一个大小为 $31$ 的桶 $c$，$c_k$ 表示序列中所有满足与第 $k$ 组中任意的数（即满足 $\lfloor \log_2x\rfloor=k$ ）组对后能使得题干所述表达式成立的正整数 $a_i$ 的数量，计算 $c$ 中的数值，只需要对每一个正整数 $a_i$ 执行 $31$ 次循环，逐一判断即可。

判断的方式可以从 $y$ 组成的序列出发，显然 $a_i$ 只要在这个序列中，就会使得题干的表达式成立，具体判断的式子如下，式子的值为 $0$ 则成立，为 $1$ 或不满足条件则不成立。

$$\large\displaystyle

\operatorname{cmp}(a_i,k)=\lfloor \frac{a_i-3\times2^k}{2^k}\rfloor\bmod 2
 
$$

其中 $a_i\ge3\times2^k$。

这样下来，对于正整数 $a_i$，其贡献为 $\large c_{\lfloor \log_2a_i\rfloor}$，将所有的 $a_i$ 贡献相加即为答案。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;

#define N 500010
#define int long long

int t,n,a[N],c[31];

inline int pw(int k){//快速计算2的k次方
	if(k==0)return 1;
	return 2<<(k-1);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);

	cin>>t;

	while(t--){
		int ans=0;
		for(int i=0;i<=30;i++)c[i]=0;
		
		cin>>n;
		
		for(int i=1;i<=n;i++){
			cin>>a[i];
			
			for(int j=0;j<=30;j++){
				int st=pw(j)*3,d=pw(j);
				if(a[i]<st)break;
				
				c[j]+=((a[i]-st)/d)%2==0;
			}
		}
		
		for(int i=1;i<=n;i++){
			if(a[i]==0)ans+=n;
			else ans+=c[__lg(a[i])];
		}
		
		cout<<ans<<"\n";
	}

	return 0;
}
```

---

## 作者：xiaoke2021 (赞：1)

~~赛时和同学想到了正解，没实现出来，$ 100pts \to 30pts $，唐~~


---


### 30 分做法

数据很小，可以写 $O(n^{2})$ 的暴力，枚举所有的 $(i,j)$，判断是否符合要求即可。

第一个子任务稳过，后面两个 TLE 飞了。

### 100 分做法

考虑异或的性质。

首先想到 0。异或的恒等律告诉我们，0 与任何数异或都是原来那个数，容易证明 $a_i$ 和 $a_j$ 中只要有一个为 0，那么这组 $(i,j)$ 必然符合要求。

接着是一般情况。我们令 $a_i < a_j$。

注意到 $a_i$、$a_j$ 在二进制下的位数不相等（因为一旦位数相等，那么他们的最高位的两个 1 就会在一起异或，最后的结果的那一位为 0，结果就会变小，会小于 $a_i$，不符题意），所以异或的结果一定大于 $a_i$，更不可能小于 $a_i$，结合下图很好理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/4foqe595.png)

所以只要考虑怎样使结果不大于 $a_j$ 就行了。这里先给出一个结论：设 $x$ 为 $a_i$ 在二进制下的位数，则 $a_j$ 在二进制下的第 $x$ 位为 1 时的 $(i,j)$ 符合要求。

尝试证明。仍以上图为例（此时 $x = 4$）。由于 $a_i$ 在二进制下的位数小于 $a_j$ 的，所以 $a_j$ 在二进制下的最高位到第 $x+1$ 位都会与 0 异或，结果的对应位数上的值不变；而 $a_j$ 在二进制下的第 $x$ 位为 1，由于第 $x$ 位是 $a_i$ 在二进制下的最高位，所以 $a_i$ 在二进制下的第 $x$ 位显然也是 1，结果的第 $x$ 位变成了 0，显然结果必然比 $a_j$ 小，跟不可能大于 $a_j$，符合要求。

思路已经明确了，可以枚举 $a_i$，找到符合条件的 $a_j$ 即可。具体细节见代码：


```cpp
#include<bits/stdc++.h>
#define int long long //十年 OI 一场空，____________
using namespace std;
const int MAXN=500000+5;
int T;
int n;
int a[MAXN];
int x[MAXN]; //用 x[i] 储存 a[i] 的最高位
int is_one[30+5],is_highest[30+5]; //用 is_one[i] 储存二进制下第 i 位为 1 的数的数量，is_highest[i] 储存二进制下第 i 位为最高位的数的数量
void work(int pos){
	int maxx=-1; //存 a[pos] 的最高位
	for(int i=0;i<=30;i++)
		if(a[pos]&(1<<i)) //如果二进制下第 i 位为 1
			is_one[i]++,maxx=max(maxx,i);
	x[pos]=maxx;
	is_highest[maxx]++;
}
int main(){
	cin>>T;
	while(T--){
		memset(is_one,0,sizeof(is_one));
		memset(is_highest,0,sizeof(is_highest)); //多测不清空，亲人两行泪
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],work(i);
		for(int i=1;i<=n;i++){
			if(a[i]!=0) ans+=is_one[x[i]]-is_highest[x[i]]; //第 x 位为 1 的数的数量减去第 x 位为最高位的数的数量，这样使得 a[i] 和 a[j] 位数不同
			else ans+=n; //0 和任何数异或都满足条件，包括它自己
		}cout<<ans<<endl;
	}
}
```

---

## 作者：guojiahong (赞：1)

$a_i=0$ 时需要特判。  
否则，当且仅当 $a_i$ 二进制位数小于 $a_j$ 且 $a_i$ 最高位对应的 $a_j$ 的那一位为 1 时，$(i,j)$ 成立。只需要排序后开桶维护即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500001];
long long cnt[32];
int main(){
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=0;i<32;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+1+n);
		long long ans=0;
		for(int i=1;i<=n;i++)
		{
			if(!a[i])
			{
				cnt[0]++;
				continue;
			}
			int l=__lg(a[i])+1;
			cnt[l]++;
			for(int j=1;j<l;j++)
			{
				int t=a[i]%2;
				a[i]/=2;
				if(t)ans+=cnt[j];
			}
		}
		ans+=n*cnt[0];
		cout<<ans<<'\n';
	}
}
```

---

## 作者：zh1221_qwq (赞：1)

简单题，但赛时调了半个小时。

我们先令 $a_i < a_j$。

因为 $a_i \oplus a_j > a_i$，所以 $a_i$ 的最高位肯定要比 $a_j$ 的小。

又因为 $a_i \oplus a_j < a_j$，所以 $a_i$ 的最高位在 $a_j$ 中必须为 $1$，这样才能讲 $a_j$ 的值减小。

所以我们开一个 一维数组记录这一位上为 $1$ 的数的个数之和，且这个数不为当前位作为第一位，将数组中对应每个数最高位的值加进答案里。

但我们发现还有一个问题，就是 当 $a_i$ 为 $0$ 时，$a_j$ 为什么都满足条件，所以我们再记录 $0$ 的个数，乘 $n$ 后加进答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,x,f[31],cnt[35],tot,k[35],h[500005],ls1,ls2;
main(){
	f[0]=1;
	for(int i=1;i<=30;i++)f[i]=f[i-1]*2;
	cin>>t;
	while(t--){
		cin>>n;
		tot=0;
		memset(cnt,0,sizeof(cnt));memset(k,0,sizeof(k));
		ls1=ls2=0;
		for(int i=1;i<=n;i++){
			h[i]=0;
			cin>>x;
			if(x==0)tot++; 
			for(int j=30;j>=0;j--){
				if(x>=f[j]){
					if(!h[i])h[i]=j+1,cnt[j+1]++,k[j+1]--;
					k[j+1]++;
					x-=f[j];
				}
			}
		}
		for(int i=1;i<=n;i++){
			ls2+=k[h[i]];
		}
		cout<<ls2+tot*n<<"\n";
	}
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[P10853 【MX-X2-T2】「Cfz Round 4」Xor Counting](https://www.luogu.com.cn/problem/P10853)
## 分析

直接考虑记录一个数组 $num_i$，表示二进制下最高位为 $i$ 数的个数，输入的时候即可记录。

对于每一个数，答案 $ans= \sum_{i=1}^n \sum_{j=1}^{k_i} num_{s_j}$，此处 $k$ 表示 $a_i$ 二进制下除了最高位的 $1$ 的个数，$s_j$ 表示每一个 $1$ 在哪一位。容易得到，答案为且仅为此等式，因为若一个数与另一个最高位不相同，且其中一个数最高位的位置另一个数也为 $1$，则两者异或的答案一定居于两者权值中间。

## Code

```cpp
#include<bits/stdc++.h>
#define f_inline inline __attribute__((always_inline))
#define nc() getchar()
#define int long long
f_inline int read() {
	register char c =nc();
	register int x = 0, f = 1;
	while (!isdigit(c)) {
		f|=c=='-';
		c=nc();
	}
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) +(c^48);
		c = nc();
	}
	return x * f;
}
f_inline void write(int x) {
	if(x<0)
		putchar('-'),x=-x;
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
int num[50],num2[500010];
int a[500010],n;
signed main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld",&n);
		for(int i=0;i<=45;i++)num[i]=0;
		for(int i=1;i<=n;i++)
		{
			num2[i]=0;
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			int x=a[i];
			int t=0;
			while(x)
			{
//				printf("%lld",x&1);
				if((x&1)&&x!=1)num2[i]=t+1;
				x>>=1;
				
				t++;
			}
//			puts("");
//			printf("QwQ%lld %lld %lld\n",i,t,num2[i]);
			num[t]++;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
//			printf("%lld %lld\n",num[num2[i]],num2[i]);
			ans+=num[0];
			int x=a[i];
			int t=1;
			while(x)
			{
				if((x&1)&&x!=1)ans+=num[t];
				x>>=1;
				t++;
			}
//			ans+=num[num2[i]];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

