# [USACO05DEC] Cow Patterns G

## 题目描述

Farmer John 的 $N$（$1 \leq N \leq 10^5$）头奶牛中出现了 $K$（$1 \leq K \leq 25000$）只坏蛋！这些坏蛋在奶牛排队的时候总站在一起。现在你需要帮助 FJ 找出他们。

为了区分，FJ 给每头奶牛发了号牌，上面写着一个 $1 \ldots S$ 之间的数字（$1 \leq S \leq 25$），虽然这不是个完美的方法，但也有一定作用。现在 FJ 记不得坏蛋们的具体号码，但他给出了一个模式串。原坏蛋的号码相同，模式串中的号码依旧相同，模式串中坏蛋号码的大小关系也和原号码相同。

例如模式串：$1,4,4,3,2,1$，原来的 $6$ 只坏蛋，最前面和最后面的号码相等且最小（不一定是 $1$），位置 $2,3$ 的坏蛋号码相同且最大（不一定是 $4$）。

现在有这样一个队列：$5, 6, 2, 10, 10, 7, 3, 2, 9$，它的子串 $2, 10, 10, 7, 3, 2$ 匹配模式串的相等关系和大小关系，这就可能是一个坏蛋团伙。

请找出所有团伙的可能情况。 

## 样例 #1

### 输入

```
9 6 10
5
6
2
10
10
7
3
2
9
1
4
4
3
2
1```

### 输出

```
1
3```

# 题解

## 作者：konjakujelly (赞：7)

## 前言
第一眼看到题目，觉得是 kmp+平衡树，仔细一做，结果写出了 kmp+线段树（前置知识）
## 解法
读题我们知道，这是一道 kmp，比较是用的每个数的大小关系

上来我直接算出每个数加入时的排名，用这个跑了一遍 kmp（WA 声一片~）

仔细读题，发现 $S$ 只有25，所以就有很多重复的号码，出现正确性问题

那么，我们可以多记录一个值，与自己相同的数有多少个，与排名一起判断，就能保证正确性

我们可以用线段树维护这个 kmp，一个数只会进出线段树各一次，所以时间复杂度为 $\Theta(\log{n}+\log{k})$ ，完美通过， $73ms$ ，最优解第四
## CODE
代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX = 1e5+10;
int n,k,s,cnt,hed,res;
int nex[MAX],rnk[MAX],sum[MAX],a[MAX],b[MAX],ans[MAX];
int ls[110];
inline int read() {
	int x = 0;
	char ch = getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
//线段树
void build(int l,int r,int lr){
	ls[lr]=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,lr<<1),build(mid+1,r,lr<<1|1);
}
void add(int l,int r,int x,int v,int lr){
	ls[lr]+=v;
	if(l==r) return;
	int mid = (l+r)>>1;
	if(x<=mid) add(l,mid,x,v,lr<<1);
	else add(mid+1,r,x,v,lr<<1|1);
}
int query(int l,int r,int L,int R,int lr){
	if(R<L) return 0;
	if(l>=L and r<=R) return ls[lr];
	int mid=(l+r)>>1,res=0;
	if(mid>=L) res=query(l,mid,L,R,lr<<1);
	if(mid<R) res+=query(mid+1,r,L,R,lr<<1|1);
	return res;	
}
//处理 next 数组，初始化
void init(){
	for(int i = 1;i<=k;++i) add(1,s,b[i],1,1),rnk[i]=query(1,s,1,b[i]-1,1),sum[i]=query(1,s,b[i],b[i],1);
	build(1,s,1);
	int p=0;
	for(int i = 2;i<=k;++i){
		add(1,s,b[i],1,1);
		int l=query(1,s,1,b[i]-1,1),r=query(1,s,b[i],b[i],1);
		while(p and (l!=rnk[p+1] or r!=sum[p+1])){
			for(int j = i-p;j<i-nex[p];j++) {
				add(1,s,b[j],-1,1);
				if(b[j]==b[i]) --r;
				if(b[j]<b[i]) --l;
			}
			p=nex[p];
		}
		if(l==rnk[p+1] and r==sum[p+1]) p++;
		nex[i] = p;
	}
	build(1,s,1);
}
signed main() {
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
	n = read(),k = read(),s = read();
	for(int i = 1;i<=n;++i) a[i]=read();
	for(int i = 1;i<=k;++i) b[i]=read();
	init();
	int p = 0;
	for(int i = 1;i<=n;++i){
		add(1,s,a[i],1,1);
		int l=query(1,s,1,a[i]-1,1),r=query(1,s,a[i],a[i],1);//提前记录，以免时间爆炸
		while(p and (l!=rnk[p+1] or r!=sum[p+1])) {
			for(int j = i-p;j<i-nex[p];++j) {
				add(1,s,a[j],-1,1);
				if(a[j]==a[i]) r--;//更新当前的排名与相同字符数
				if(a[j]<a[i]) l--;
			}
			p=nex[p];
		}
		if(l==rnk[p+1] and r==sum[p+1])++p;
		if(p==k) ans[++res]=i-k+1;
	}
	printf("%d\n",res);
	for(int i = 1;i<=res;++i) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：LinkWish (赞：6)

## 前言
这道题是一道 kmp 好题，做完了才发现没题解，那我就来一发吧！
## 审题
给定一个模式串，求原串中与模式串匹配的字串的数量，其中“匹配”指字串内每项之间的相对大小与模式串之间每项之间的相对大小相同。

样例分析：


模式串：```1 4 4 3 2 1```

原串：```5 6 2 10 10 7 3 2 9```

原串中：```2 10 10 7 3 2``` 的相对大小与模式串匹配。

审完题立马想到前几天刚做的[P4696 [CEOI2011]Matching](https://www.luogu.com.cn/problem/P4696)，做完这道题的同学可以去看看，这道题其实可以说是它的加强版，因为模式串中的数可能相同，但是这道题不知道为什么只是道蓝题。

## 思路

这道题一看：匹配？那多半和 kmp 有关，但是 kmp 是判断完全一样的串，而这道题是判断相对大小，所以我们需要在 kmp 上稍微改一下，改变它的判断方式即可。

定义模式串里一个数的前驱 $l_i$ 为下标小于它且值最大的小于等于它的元素，一个数的后继 $r_i$ 为下标小于它且值最小的大于等于它的元素，即：

$l_i=\max{j}(1 \leqslant j < i,vul_j \leqslant vul_i)$

$r_i=\max{j}(1 \leqslant j < i,vul_j \geqslant vul_i)$

我们很容易就能发现，若对于原串中的一个字串 $s$ ,如果 $s$ 中的每一项都可以满足模式串里的前驱和后继的关系，那么这个字串一定是一个合法解。

## 初始化

现在的问题是如何在规定时间内求出模式串每一项的前驱和后继。我们看到题目中的模式串长度最大是25000，就意识到不可能是 $O(n^2)$ 的暴力去求。这种数据一般来说大常数 $O(n\log{n})$ 就可以过。

这个地方有许多种做法，最优复杂度可以达到 $O(n)$ ，但是比较难懂（我也不懂），所以我就采用了一种简单一点的方法：利用 STL 里的 set 容器来初始化前驱后继，具体做法如下。

1.定义一个结构体 p ，里面存放模式串里每个元素的排名和下标，并重载小于运算符，使排名作为第一关键字升序排列，下标作为第二关键字降序排列。

2.读入模式串的一个元素 a ，并将其插入 set 里面。

3.利用 set 本身自带的 lower_bound 函数搜索 a 自身，你将会得到一个指向 set 里 a 自己的迭代器 it 。

4.根据 set 的性质、结构体里的重载运算符和后继的定义， ++it 必定指向 a 的后继。

5.--it 使其再次指向 a 自身。

6.根据 set 的性质、结构体里的重载运算符和前驱的定义， --it 必定指向 a 的前驱。

7.kmp 的初始化，不过有一点变化。我们在检验一个元素是否匹配时，可以比较这个元素在模式串里的前驱相对于自身的大小关系是否与模式串内的大小关系相符合，具体实现的代码如下：

```cpp
inline bool check(int *arr,int x,int y){
	//这里的rk是每一项的排名，x是已经匹配到了模式串的第几位，y是匹配到了原串的第几位
	if(l[x]){
		//这里有两种情况：小于或相等
		//y-x+l[x]是y的前驱在原串里的实际位置，l[x]只是相对位置，下同
		if(rk[l[x]]==rk[x]&&arr[y-x+l[x]]!=arr[y])return 0;
		else if(rk[l[x]]<rk[x]&&arr[y-x+l[x]]>=arr[y])return 0;
	}
	if(r[x]){
		//这里有两种情况：大于或相等
		if(rk[r[x]]==rk[x]&&arr[y-x+r[x]]!=arr[y])return 0;
		else if(rk[r[x]]>rk[x]&&arr[y-x+r[x]]<=arr[y])return 0;
	}
	return 1;
}
```

## KMP
这道题的 kmp 部分没有什么特殊的地方，只需要把判断是否匹配的地方换成 check 函数就可以了。

## 时间复杂度
这道题的时间复杂度来自两个部分，分别是初始化时 set 所使用的 $O(K \log{K})$ ，和 kmp 时使用的 $O(N)$ ，所以总时间复杂度为 $O(K \log{K}+N)$ 。吸氧后 91ms ，最优解第四。

## 上代码!
```cpp
//Linkwish's code
#include<bits/stdc++.h>
using namespace std;
int n,k,s,ans,res[1000010];
int a[1000010],rk[25010],l[25010],r[25010],nxt[25010];
struct p{
	int num,pos;
	bool operator < (const p x)const{
		if(num==x.num)return pos>x.pos;
		return num<x.num;
	}
};
set <p> q;
set<p>::iterator it;
inline bool check(int *arr,int x,int y){
	if(l[x]){
		if(rk[l[x]]==rk[x]&&arr[y-x+l[x]]!=arr[y])return 0;
		else if(rk[l[x]]<rk[x]&&arr[y-x+l[x]]>=arr[y])return 0;
	}
	if(r[x]){
		if(rk[r[x]]==rk[x]&&arr[y-x+r[x]]!=arr[y])return 0;
		else if(rk[r[x]]>rk[x]&&arr[y-x+r[x]]<=arr[y])return 0;
	}
	return 1;
}
int main(){
	scanf("%d%d%d",&n,&k,&s);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	//在读入的同时初始化，因为要用到的数据刚好就是已经读入的数据，即下标比自己小
	for(int i=1,j;i<=k;i++){
		scanf("%d",&rk[i]);
		q.insert((p){rk[i],i});
		it=q.lower_bound((p){rk[i],i});
		it++;
		j=(*it).pos;
		if(rk[j]>=rk[i]&&j<i)r[i]=j;
		it--;
		it--;
		j=(*it).pos;
		if(rk[j]<=rk[i]&&j<i)l[i]=j;
	}
	//kmp里的初始化
	for(int i=2,j=0;i<=k;i++){
		while(j&&!check(rk,j+1,i))j=nxt[j];//原来的判断条件换成了check
		if(check(rk,j+1,i))j++;
		nxt[i]=j;
	}
	//kmp
	for(int i=1,j=0;i<=n;i++){
		while(j&&!check(a,j+1,i))j=nxt[j];
		if(check(a,j+1,i))j++;
		if(j==k)res[++ans]=i-j+1,j=nxt[j];
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)printf("%d\n",res[i]);
	return 0;
}
```

---

## 作者：NuoCarter (赞：4)

## 前置芝士：

如果你不知道 $\pi$ 函数（前缀函数）是什么的话，可以看看我混着 $Z$ 函数一起写的总结：

[Link](https://www.cnblogs.com/NuoCarter/p/14470033.html)

## 题解：


在很多普通的字符串匹配中，$\pi$ 函数表示的是前缀中最长的 $border$ ，也就是前缀中前后缀相等的最长长度。

但在这道题中，很明显，无法用相等来表示。

首先，将模式串（$K$ )和数字串（$N$）拼起来，中间插入一个特殊符号 “#”。

根据题意：我们应该将 $\pi$ 函数中的“相等”看做大小关系相同，于是$ \pi[i]$ 就表示当前 $S_0 \ $~$ \ S_{j-1}$ 中前后缀大小关系最长的长度，因为有个特殊符号 “#” ，所以所有的 $\pi[\ i\ ] \leq K$。

而满足“坏蛋团体”区间的右端点，一定满足 $\pi[\ r\ ]=K$。

那么这时问题就出在了如何判断大小关系相同了。

假定 $S_0 \ $~$ \ S_{j-1}$与$S_{i-j}\ $ ~ $\ S_{i-1}$ 大小关系相同。

那么对于 $j$ 与 $i$ 这两个位置

如果说 $[0,j-1]$ 中 比$j$ 大的数与$[i-j,i-1]$中比 $i$ 大的数的个数相等

而且 $[0,j-1]$ 中 和$j$ 相等的数与$[i-j,i-1]$中和 $i$ 相等的数的个数相等

又因为两个区间长度是一样的，那么区间中小于 $j$ ,与小于 $i$ 的数的个数也是相等的。

所以这$[0,j]$ 与 $[i-j,i]$两个区间的大小关系相等。

如此我们只需要用一个桶的前缀和，就可以在 $O(S)$ 的复杂度中求出区间中比它小的与相等的数的个数了。

（可以理解为重载了 $=$ 这个运算符，将两个位置的相等转为了大小关系相同）

**Warning** : 最后需要的是左端点，但利用 $\pi$ 函数判断的话，符合条件的是右端点.

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x)	x&(-x)
const int N=2e5+3,K=2503;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch))	f|=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
template <typename T>
inline void print(T x){
	if(x<0)	putchar('-'),x=-x;
	if(x>9)	print(x/10);
	putchar(x%10^48);
}
int n,k,S,s[N+K],pi[N+K],tong[N+K][27],suf[N+K][27];
vector<int> ans;
inline bool Judge(int i,int j){
	if(tong[i][s[i]]-tong[i-j-1][s[i]]!=tong[j][s[j]]) return false;
	int tep1=0,tep2=0;
	for(register int o=s[i]-1;o>=1;--o)	tep1+=tong[i][o]-tong[i-j-1][o];
	
	for(register int o=s[j]-1;o>=1;--o)	tep2+=tong[j][o];
	if(tep1!=tep2)	return false;
	return true;
}
inline void Pre_function(int *s){
	for(register int i=1;i<=n+k;++i){
		int j=pi[i-1];
		while(j&&!Judge(i,j)){j=pi[j-1];}
		if(Judge(i,j))	++j;
		pi[i]=j;
	}
}
int main(){
	read(n),read(k),read(S);
	for(register int i=1;i<=n;++i)	read(s[k+i]);
	for(register int i=0;i<k;++i)	read(s[i]);
	s[k]='#';
	for(register int i=0;i<k;++i)	suf[i][s[i]]++;
	for(register int i=k+1;i<=n+k;++i)	suf[i][s[i]]++;
	for(register int i=1;i<=S;++i)	tong[0][i]=suf[0][i];
	for(register int i=0;i<=n+k;++i){
		for(register int j=1;j<=S;++j){
			tong[i][j]=tong[i-1][j]+suf[i][j];
		}
	}
	Pre_function(s);
	for(register int i=k+1;i<=n+k;++i){
		if(pi[i]==k)	ans.push_back(i-k-k+1);
	}
	int siz=ans.size();
	print(siz),putchar('\n');
	for(register int i=0;i<siz;++i) print(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：jur10n (赞：2)

# [P6080 [USACO05DEC] Cow Patterns G](https://www.luogu.com.cn/problem/P6080)

做法：**树状数组**+**kmp**

## 前言

最近在学习 kmp，这题看了很久都没有弄明白，弄懂之后且当作记录一下思路吧（也是本蒟蒻第一篇题解）。

## 题意

对于两个数串 A 和 B，在 A 中找出所有长度等于 B 的子串，使这个子串与 B 中每个位置对应数**在各自串中的相对排名**都对应相等。

## 思路

### tip1：排名

首先要考虑如何维护排名，我最先想到的就是离散化，但是这个题目需要动态维护子串排名，感觉不太可行。

因此可以利用**树状数组**或者**线段树**，查询对应下标的前缀和，就可以查出小于等于自己的有几个数，而且可以动态维护，易于删点增点。

树状数组比较简单好搓，那么我们用树状数组，简单写一个**单点修改，前缀查询**，就可以达到我们的目的。

### tip2：kmp

剩下的就是爆改 kmp 了，我们考虑求 Next 数组的部分。

需要看对于前后两个子串，对于后子串中末尾（即为 i 指针）的地位，与前子串中末尾 j 指针的地位是否相同，这便是我们判断是否匹配的条件。

需要注意的是，由于会出现重复的数字，所以我们需要维护每个数以及每个数前面的一个数的排名，这样就相当于变相的记录了与自己相同的数的个数了（后减去前）。

由于前子串是顺着来的，所以我们可以提前预处理出来每个子串的排名，用两个 Rank 数组标记即可。

另一部分同理，记得及时删点。

## 代码

```cpp
class Solution_Case	//我的小习惯
{
	/*
	1.统计排名可以利用树状数组或者线段树，不用非要离散化（无法动态维护）
	查询对应下标的前缀和，就可以查出前面有几个数字，而且可以动态维护
	2.动态维护后子串的排名，需要删除前面的数，即add-1
	*/
};

#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define N 500005
using namespace std;

int n, m, s, cnt;
int A[N], B[N];
int Rank1[N], Rank2[N];
int Next[N], ans[N];

class BIT //树状数组，单点修改，前缀查询
{
  public:
	int bitSum[N];
	void Add(int x, int val)
	{
		for (; x <= s; x += lowbit(x)) bitSum[x] += val;
	}
	int Query(int x, int ans = 0)
	{
		for (; x; x -= lowbit(x)) ans += bitSum[x];
		return ans;
	}
	bool Check(int x, int y)
	{
		//这里是为了应对重复的值，查询前一位，确保地位完全相同
		//变相的相当于记录了与自己相同的有多少个（Rank1-Rank2）
		return (Query(y) == Rank1[x]) && (Query(y - 1) == Rank2[x]);
	}
} Bit;

void Make_Next()	//处理出next数组
{
	memset(Bit.bitSum, 0, sizeof(Bit.bitSum));
	for (int i = 2, j = 0; i <= m; ++i)
	{
		//printf("j=%d i=%d\n", j, i);
		Bit.Add(B[i], 1);
		while (j && !Bit.Check(j + 1, B[i])) //失配
		{
			//删掉前面的点，因为要维护后子串的排名
			//printf("k=%d~%d add-1\n", i - j, i - Next[j]);
			for (int k = i - j; k < i - Next[j]; ++k)  Bit.Add(B[k], -1);
			j = Next[j];
		}
		if (Bit.Check(j + 1, B[i]))  ++j;
		Next[i] = j;
	}
}

void Cul_Ans()	//计算答案
{
	memset(Bit.bitSum, 0, sizeof(Bit.bitSum));
	for (int i = 1, j = 0; i <= n; ++i)
	{
		Bit.Add(A[i], 1);
		while (j && !Bit.Check(j + 1, A[i])) //失配
		{
			for (int k = i - j; k < i - Next[j]; ++k)  Bit.Add(A[k], -1);	//删点
			j = Next[j];
		}
		if (Bit.Check(j + 1, A[i]))  ++j;

		if (j == m)	//整个串匹配完毕
		{
			ans[++cnt] = i - m + 1;

			//匹配上了以后要向前跳继续匹配，所以仍要删点
			//printf("k=%d~%d add-1\n", i - j, i - Next[j]);
			for (int k = i - j + 1; k <= i - Next[j]; ++k)  Bit.Add(A[k], -1);
			j = Next[j];
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 1; i <= n; ++i)  scanf("%d", &A[i]);

	//维护出B的每个前缀中末尾的排名，在kmp时候要用
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d", &B[i]), Bit.Add(B[i], 1);
		Rank1[i] = Bit.Query(B[i]), Rank2[i] = Bit.Query(B[i] - 1);
	}

	Make_Next();
	Cul_Ans();
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; ++i)  printf("%d\n", ans[i]);
	return 0;
}

```

# 小结

在我个人看来 kmp 这一算法很难理解，建议各位像我一样的初学者们多在纸上模拟模拟过程，千万不要不求甚解，争取弄明白（毕竟对着枯燥的课件确实难看懂）。

感谢各位耐心看完！

---

## 作者：Quintus09 (赞：2)

# 题解：P6080 [USACO05DEC] Cow Patterns G
---

本蒟蒻的第一道紫题和第一篇 tj。

前置知识：[kmp](https://www.luogu.com.cn/problem/P3375) 和前缀和。

## 1 暴力的 kmp
---
很明显可以将匹配变成文本串和模式串中的某一位与前几位的大小关系是否一致。如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/nlvfd95u.png?x-oss-process=image/resize,m_lfit,h_800,w_1200)
大概为   $O ( n m )$，显然超时（没代码）。

## 2 前缀和
---
可以将匹配改成目前这个区间比它大的数的个数，比它小的数的个数，跟它一样大的数的个数是否符合模式串。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6did3tlm.png?x-oss-process=image/resize,m_lfit,h_800,w_1200)

总个数  $-$  大的  $-$  等于  $=$  小的，**所以只要维护其中两个**。

可以用一个数组  $sum [ i ] [ j ]$ 再加一维。

为  $1$  到  $i$   中多少个数小于  $j (0)$  或等于  $j (1)$。

而  $S \le 25$   所以初始化为 $O(nS)$，$a$ 为文本串。
```cpp
for (int i=1;i<=n;i++){
    for (int j=1;j<=s;j++){
			suma[i][j][0]+=suma[i-1][j][0];
			suma[i][j][1]+=suma[i-1][j][1];
			if (j>a[i]) suma[i][j][0]++;
			if (j==a[i]) suma[i][j][1]++;
    }
}
```

模式串同理。

## 3 你老是关注这些题干嘛，他会把 kmp 的付出给异化掉的
---

### **0 开头**
---



异化 kmp 已经是很多题中必干的事，下文将讲如何异化。

首先，根据前文可以将代码写成这样（基于 kmp 模板）。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[25005],suma[100005][30][2],sumb[25005][30][2],nxt[25005];
int main(){
	int n,m,s;
	cin>>n>>m>>s;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++){
		for (int j=1;j<=s;j++){
			suma[i][j][0]+=suma[i-1][j][0];
			suma[i][j][1]+=suma[i-1][j][1];
			if (j>a[i]) suma[i][j][0]++;
			if (j==a[i]) suma[i][j][1]++;
		}
	}
	for (int i=1;i<=m;i++) cin>>b[i];
	for (int i=1;i<=m;i++){
		for (int j=1;j<=s;j++){
			sumb[i][j][0]+=sumb[i-1][j][0];
			sumb[i][j][1]+=sumb[i-1][j][1];
			if (j>b[i]) sumb[i][j][0]++;
			if (j==b[i]) sumb[i][j][1]++;
		}
	}
	//前缀和 
	int len=0;
	for (int i=2;i<=m;i++){
		while(b[len+1]!=b[i]&&len) len=nxt[len];
		if (b[len+1]==b[i]) nxt[i]=++len;
	}//求nxt 
	int j=0;
	int p[100005],cnt=0;
	for (int i=1;i<=n;i++){
		while ((suma[i][a[i]][0]-suma[i-j-1][a[i]][0]!=sumb[j+1][b[j+1]][0]//大于个数 
		||suma[i][a[i]][1]-suma[i-j-1][a[i]][1]!=sumb[j+1][b[j+1]][1])&&j) j=nxt[j];//等于个数 
		if (suma[i][a[i]][0]-suma[i-j-1][a[i]][0]==sumb[j+1][b[j+1]][0]
		&&suma[i][a[i]][1]-suma[i-j-1][a[i]][1]==sumb[j+1][b[j+1]][1]) j++;
		if (j==m){
			p[++cnt]=i-j+1;
			j=nxt[j];
		}
	}
	cout<<cnt<<endl;
	for (int i=1;i<=cnt;i++) cout<<p[i]<<endl;//输出 
	return 0;
} 
```
但。。。[54](https://www.luogu.com.cn/record/207700123)

### 1   $nxt$   不能为 0 

---



模式串。
```
b  1 2 3
```

对应。  
```
b  1 2 3
```

如果匹配上 2 位，但无法匹配上第 3 位，则指针跳到 0。

但这样将吃掉以第二位为开头的匹配。

所以将  $nxt$  求解该为。


```cpp
int len; 
for (int i=2;i<=m;i++){
	len=nxt[i-1];
	while(b[len+1]!=b[i]&&len) len=nxt[len];
	if (b[len+1]==b[i]) nxt[i]=++len;
	nxt[i]=max(nxt[i],1); 
}
```
###  3 $/$2    $len$  的值

---



kmp 模板这么写的注意(下)，$nxt$ 可能是通过上代码中的 max 更新，而 $len=0$。

这里不能这样。
```cpp
int len=0;
for (int i=2;i<=lb;i++){
    while (b[i]!=b[len+1]&&len){
	len=nxt[len];
    }
    if (b[i]==b[len+1]) nxt[i]=++len;
}
```
这里不能这样。

但 [82？！](https://www.luogu.com.cn/record/207700582)

### 2 求  $nxt$  不一定等

---



若模式串  $b$  为。

```1 3 5 2 4 6......```

而  $nxt$。

 ```0 1 1 1 1 1......```

但 ```1 3 5``` 和 ```2 4 6``` 的大小关系一样。

那跳  $nxt$。
 
![](https://cdn.luogu.com.cn/upload/image_hosting/mpcaoxol.png?x-oss-process=image/resize,m_lfit,h_800,w_1200)

所以说求  $nxt$  要看与前一数的大小关系。代码：


```cpp
	int len;
	for (int i=2;i<=m;i++){
		len=nxt[i-1];
		while(len&&((b[len+1]>b[len])!=(b[i]>b[i-1])
		||(b[len+1]==b[len])!=(b[i]==b[i-1])
		||(b[len+1]<b[len])!=(b[i]<b[i-1]))) len=nxt[len];
		if ((b[len+1]>b[len])==(b[i]>b[i-1])
		&&(b[len+1]==b[len])==(b[i]==b[i-1])
		&&(b[len+1]<b[len])==(b[i]<b[i-1])) nxt[i]=++len;//大小关系 
		nxt[i]=max(nxt[i],1); 
	}
```
## 4.code

---

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[25005],suma[100005][30][2],sumb[25005][30][2],nxt[25005];
int main(){
	int n,m,s;
	cin>>n>>m>>s;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++){
		for (int j=1;j<=s;j++){
			suma[i][j][0]+=suma[i-1][j][0];
			suma[i][j][1]+=suma[i-1][j][1];
			if (j>a[i]) suma[i][j][0]++;
			if (j==a[i]) suma[i][j][1]++;
		}
	}
	for (int i=1;i<=m;i++) cin>>b[i];
	for (int i=1;i<=m;i++){
		for (int j=1;j<=s;j++){
			sumb[i][j][0]+=sumb[i-1][j][0];
			sumb[i][j][1]+=sumb[i-1][j][1];
			if (j>b[i]) sumb[i][j][0]++;
			if (j==b[i]) sumb[i][j][1]++;
		}
	}
	//前缀和 
	int len;
	for (int i=2;i<=m;i++){
		len=nxt[i-1];
		while(len&&((b[len+1]>b[len])!=(b[i]>b[i-1])
		||(b[len+1]==b[len])!=(b[i]==b[i-1])
		||(b[len+1]<b[len])!=(b[i]<b[i-1]))) len=nxt[len];
		if ((b[len+1]>b[len])==(b[i]>b[i-1])
		&&(b[len+1]==b[len])==(b[i]==b[i-1])
		&&(b[len+1]<b[len])==(b[i]<b[i-1])) nxt[i]=++len;//大小关系 
		nxt[i]=max(nxt[i],1); 
	}//求nxt 
	int j=0;
	int p[100005],cnt=0;
	for (int i=1;i<=n;i++){
		while ((suma[i][a[i]][0]-suma[i-j-1][a[i]][0]!=sumb[j+1][b[j+1]][0]//大于个数 
		||suma[i][a[i]][1]-suma[i-j-1][a[i]][1]!=sumb[j+1][b[j+1]][1])&&j) j=nxt[j];//等于个数 
		if (suma[i][a[i]][0]-suma[i-j-1][a[i]][0]==sumb[j+1][b[j+1]][0]
		&&suma[i][a[i]][1]-suma[i-j-1][a[i]][1]==sumb[j+1][b[j+1]][1]) j++;
		if (j==m){
			p[++cnt]=i-j+1;
			j=nxt[j];
		}
	}
	cout<<cnt<<endl;
	for (int i=1;i<=cnt;i++) cout<<p[i]<<endl;//输出 
	return 0;
} 
```
[AC](https://www.luogu.com.cn/record/207706148)

## **5.结尾**
---
题解结束了，好像有点长，代码也有点丑陋。

对于 $sumb$  全是  $sumb[b[j+1]][j+1]$，显然能优化掉一维。

时间复杂度  $O(ns)$，可以轻松 AC。

希望对你有帮助，阿里嘎多。

---

## 作者：Laoshan_PLUS (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P6080)

### 题意

给定一个长度为 $N$ 的整数串 $A$ 和一个长度为 $K\ (K\le N)$ 的整数串 $B$，$A$ 和 $B$ 中的元素均为不大于 $S$ 的正整数。

定义两个串是相等的，当且仅当两个串的长度相当，且两个串中，对于任意的 $i$，第 $i$ 个元素在两个串中的排名是一样的。

求在 $A$ 的所有长度等于 $K$ 的子串中，有多少子串与 $B$ 相等。

### 暴力出奇迹

考虑暴力算法，枚举 $A$ 每个子串，查看排名并与 $B$ 匹配。可以用树状数组维护子串排名，枚举子串时便可以 $O(N)$ 查询排名。去重后辅之用桶存储 $A_i$ 个数，易得暴力代码：

```cpp
#include <bits/stdc++.h>
#define lowbit(x) x & -x
using namespace std;

constexpr int MAXN = 5e5 + 5, MAXS = 10005;
int n, k, s, a[MAXN], b[MAXN], r[MAXN], ans; // r[]存排名
int cnt[MAXN], i, j; // cnt[]存桶
int c[MAXS]; // 树状数组

inline void add(int x, int k) {
	while (x <= s) {
		c[x] += k;
		x += lowbit(x);
	}
}

inline int sum(int x) {
	int res = 0;
	while (x != 0) {
		res += c[x];
		x -= lowbit(x);
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> k >> s;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= k; i++) cin >> b[i], r[i] = b[i];
	sort(r + 1, r + k + 1);
	int len = unique(r + 1, r + k + 1) - r - 1;
	for (int i = 1; i <= k; i++)
		b[i] = lower_bound(r + 1, r + len + 1, b[i]) - r; // 类似离散化
	for (int i = 1; i <= k; i++) {
		if (cnt[a[i]] == 0) add(a[i], 1);
		cnt[a[i]]++;
	}
	bool flag = 1;
	for (int i = 1; i <= k; i++)
		if (sum(a[i]) != b[i]) {
			flag = 0;
			break;
		}
	if (flag) r[++ans] = 1;
	for (int i = 1; i <= n - k; i++) {
		if (cnt[a[i]] == 1) add(a[i], -1);
		cnt[a[i]]--;
		if (cnt[a[i + k]] == 0) add(a[i + k], 1);
		cnt[a[i + k]]++;
		bool flag = 1;
		for (int j = i; j <= i + k - 1; j++)
			if (b[j - i + 1] != sum(a[j + 1])) {
				flag = 0;
				break;
			}
		if (flag) r[++ans] = i + 1;
	}
	cout << ans << '\n';
	for (int i = 1; i <= ans; i++) cout << r[i] << '\n';

	return 0;
}
```

**暴力代码理论时间复杂度 $\boldsymbol{O(NK\log N)}$，可以得到 82pts 的好成绩。**

### KMP

为了追求满分，我们再来想想~~难想~~的 KMP。

我们仍要比较两串是否相等，但现在我们有了 $next$ 数组，我们可以让 $next$ 存储 $B$ 的排名，就可以用 KMP 算法~~愉快地~~切掉此题啦……吗？

且慢！去重又变为一个新问题：我们只需比较 $A_i$ 和 $B_{j+1}$ 吗？不然。由于没有了桶，我们必须在去重时比较小于等于的数和小于的数，才能避免相同的数排名查询出错。时间复杂度 $O(N\log N)$。

```cpp
#include <bits/stdc++.h>
#define lowbit(x) x & -x
using namespace std;

constexpr int MAXN = 5e5 + 5, MAXS = 10005;
int n, k, s, a[MAXN], b[MAXN], r[MAXN], ans;
int nxt[MAXN], equ[MAXN], les[MAXN];
int c[MAXS];

inline void add(int x, int k) {
	while (x <= s) {
		c[x] += k;
		x += lowbit(x);
	}
}

inline int sum(int x) {
	int res = 0;
	while (x != 0) {
		res += c[x];
		x -= lowbit(x);
	}
	return res;
}

void get_nxt() {
	memset(c, 0, sizeof(c));
	for (int i = 2, j = 0; i <= k; i++) {
		add(b[i], 1);
		while (j > 0 && (sum(b[i]) != equ[j + 1] || sum(b[i] - 1) != les[j + 1])) {
			for (int kk = i - j; kk < i - nxt[j]; kk++) add(b[kk], -1);
			j = nxt[j];
		}
		if (sum(b[i]) == equ[j + 1] || sum(b[i] - 1) == les[j + 1]) j++;
		nxt[i] = j;
	}
}

void kmp() {
	get_nxt();
	memset(c, 0, sizeof(c));
	for (int i = 1, j = 0; i <= n; i++) {
		add(a[i], 1);
		while (j > 0 && (sum(a[i]) != equ[j + 1] || sum(a[i] - 1) != les[j + 1])) {
			for (int kk = i - j; kk < i - nxt[j]; kk++) add(a[kk], -1);
			j = nxt[j];
		}
		if (sum(a[i]) == equ[j + 1] || sum(a[i] - 1) == les[j + 1]) j++;
		if (j == k) r[++ans] = i - j + 1;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> k >> s;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= k; i++) {
		cin >> b[i];
		add(b[i], 1);
		equ[i] = sum(b[i]);
		les[i] = sum(b[i] - 1);
	}
	kmp();
	cout << ans << '\n';
	for (int i = 1; i <= ans; i++) cout << r[i] << '\n';
	
	return 0;
}
```

---

## 作者：Iratis (赞：2)

## 前言

我看题解中一个是用的 Z 函数，另一个是 set，所以决定将链表解法分享出来。

这道题的思路与 [P4696](https://www.luogu.com.cn/problem/P4696) 差不多，都是记录前驱与后继。

## 解法

在这道题目中，我们只需要记录出模式串的大小关系，使用树状数组显然处理具有相等关系时更具有优势，但是本题解想另寻思路，利用链表的形式储存。

我们发现 $ 1 \leq K \leq 25000 $ ，所以不妨 sort 完之后进行离散化，并暴力解决前驱后继。这里需要注意的就是要确保是稳定排序，因为顺序也会对答案产生影响。

然后就对于模式串算出 $ next $ 数组（没学过的同学可以了解一下），更改一下判断两个位置是否匹配的函数，注意取等的情况：
```cpp
bool check1(int n1,int n2)
{
	bool flag=true;
	if(les[n1])
	{
		int xi=n2-(n1-les[n1]);
		if(val[les[n1]]==val[n1])
		{
			if(val[xi]!=val[n2])flag=false;
		}
		else
		{
			if(val[xi]>=val[n2])flag=false;
		}
	}
	if(mor[n1])
	{
		int xi=n2-(n1-mor[n1]);
		if(val[mor[n1]]==val[n1])
		{
			if(val[xi]!=val[n2])flag=false;
		}
		else
		{
			if(val[xi]<=val[n2])flag=false;
		}
	}
	return flag;
}
bool check2(int n1,int n2)
{
	bool flag=true;
	if(les[n1])
	{
		int xi=n2-(n1-les[n1]);
		if(val[les[n1]]==val[n1])
		{
			if(h[xi]!=h[n2])flag=false;
		}
		else
		{
			if(h[xi]>=h[n2])flag=false;
		}
	}
	if(mor[n1])
	{
		int xi=n2-(n1-mor[n1]);
		if(val[mor[n1]]==val[n1])
		{
			if(h[xi]!=h[n2])flag=false;
		}
		else
		{
			if(h[xi]<=h[n2])flag=false;
		}
	}
	return flag;
}
```
整体代码如下：
```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,S;
int p[1000001],h[1000001];
int pos[1000001],val[1000001];
int les[1000001],mor[1000001];
int nex[1000001];
int ans,ge[1000001];
struct Node
{
	int val,pos,ls;
	int next,prev;
}node[1000001];
bool check1(int n1,int n2)
{
	bool flag=true;
	if(les[n1])
	{
		int xi=n2-(n1-les[n1]);
		if(val[les[n1]]==val[n1])
		{
			if(val[xi]!=val[n2])flag=false;
		}
		else
		{
			if(val[xi]>=val[n2])flag=false;
		}
	}
	if(mor[n1])
	{
		int xi=n2-(n1-mor[n1]);
		if(val[mor[n1]]==val[n1])
		{
			if(val[xi]!=val[n2])flag=false;
		}
		else
		{
			if(val[xi]<=val[n2])flag=false;
		}
	}
	return flag;
}
bool check2(int n1,int n2)
{
	bool flag=true;
	if(les[n1])
	{
		int xi=n2-(n1-les[n1]);
		if(val[les[n1]]==val[n1])
		{
			if(h[xi]!=h[n2])flag=false;
		}
		else
		{
			if(h[xi]>=h[n2])flag=false;
		}
	}
	if(mor[n1])
	{
		int xi=n2-(n1-mor[n1]);
		if(val[mor[n1]]==val[n1])
		{
			if(h[xi]!=h[n2])flag=false;
		}
		else
		{
			if(h[xi]<=h[n2])flag=false;
		}
	}
	return flag;
}
bool cmp(Node a,Node b)
{
	if(a.val==b.val)return a.pos<b.pos;
	return a.val<b.val;
}
bool tmp(Node a,Node b)
{
	return a.pos<b.pos;
}
void pre()
{
	for(int i=1;i<=n;i++)
	{
		node[i].val=val[i];
		node[i].pos=i;
	}
	sort(node+1,node+n+1,cmp);
	int g=0;
	for(int i=1;i<=n;i++)
	{
		if(i==1||node[i].val>node[i-1].val)g++;
		node[i].ls=g;
	}
	for(int i=1;i<=n;i++)
	{
		node[i].prev=node[i-1].pos;
		node[i].next=node[i+1].pos;
	}
	node[1].prev=0;
	node[n].next=0;
	sort(node+1,node+n+1,tmp);
}
int main()
{
	scanf("%d%d%d",&m,&n,&S);
	for(int i=1;i<=m;i++)scanf("%d",&h[i]);
	for(int i=1;i<=n;i++)scanf("%d",&val[i]);
	for(int i=1;i<=n;i++)pos[val[i]]=i;
	pre();
	for(int i=n;i>=1;i--)
	{
		les[i]=node[i].prev;
		mor[i]=node[i].next;
		node[node[i].next].prev=node[i].prev;
		node[node[i].prev].next=node[i].next;
	}
	for(int i=2;i<=n;i++)
	{
		int j=nex[i-1];
		while(j>0&&check1(j+1,i)==false)j=nex[j];
		if(check1(j+1,i)==true)j++;
		nex[i]=j;
	}
//	for(int i=1;i<=n;i++)cout<<nex[i]<<" ";
//	cout<<endl;
	int j=0;
	for(int i=1;i<=m;i++)
	{
		while(j>0&&check2(j+1,i)==false)j=nex[j];
		if(check2(j+1,i)==true)j++;
		if(j==n)
		{
			j=nex[j];
			ge[++ans]=i-n+1;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)printf("%d\n",ge[i]);
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：1)

**KMP？树状数组？去你的。**

> 所有的字符串题都可以用哈希解的哦～  
> ——阿毛

为了光辉阿毛~~遗~~德（咕噜咕噜），我们决定用哈希来轻松搞定这个题喵～！

首先，我们要思考一下，如何用哈希来描述这个匹配问题呢？其实很简单哦喵！只要我们保持相对的大小关系一致，那么就是匹配啦喵～所以呢，我们可以把每个数换成自己的排名，嗯，简单来说就是离散化咯～然后用哈希来处理就好了喵～

举个例子吧，题面中的 $\left[2,10,10,7,3,2\right]$，我们可以把它转化成 $\left[1,4,4,3,2,1\right]$，这个很简单喵。(｡•̀ᴗ•́｡)

然后嘛，哈希值就可以计算出来啦～每个位置的值就可以通过这种方式转换成排名喵～（咕噜咕噜，狐狸耳朵都在抖啦）

---

现在要考虑的是母串上的区间怎么移动？这个问题怎么处理喵？(・o・)

其实很简单哟～区间会随着每一步的移动而变化，所以排名也会随之变化。要怎么保持哈希的更新喵？

我们可以为每一个值开一个哈希数组，记作 $h$。这样每个数组 $h_x$ 就是计算一个只有 $x$ 出现的串喵～计算方式和普通的哈希类似，只不过它计算的是：仅当原串上的位置是 $x$ 的时候，才加一喵！这样就不会错过任何一个位置啦～由于值域 $S \le 25$，这种方法还是蛮能接受的呢～而且因为区间的长度是固定的，所以这个哈希就可以轻松地滚动更新啦喵～(*•̀ᴗ•́*)و ̑̑

就比如说，当我们区间是 $\left[\color{#CCC}5,6,\color{#33A}2,10,10,7,3,2\color{#CCC},9\color{black}\right]$，像这样一个例子的蓝色部分，哈希数组 $h_{10}$ 维护的就会是 $\left[0,1,1,0,0,0\right]$ 的形式。因为在这两位置上，都是 $10$ 呢！这个哈希值就很好更新啦喵～ (●´ω｀●)

每次我们移动区间的时候呢，只需要整体乘上一个 $base$，然后再分别处理新加入的右边元素和左边退出的元素就好啦喵！

---

然后呢，我们~~事后发现可以用桶，但是阿毛以为~~需要开一个 `set`，用来记录当前区间内有多少种不同的牛哟～如果我们发现区间的牛的数量和模式串中的一样多，那就可以从小到大地处理出每一个排名对应的真实编号喵～

然后呀，只要把它们每个对应的哈希数组分别乘上它们的排名，求个和，就能得到完整的哈希啦喵！这样，最后我们就可以轻松比较一下哈希值是不是一致了喵～ (づ｡◕‿‿◕｡)づ

到目前为止呢，数据完全不卡阿毛，自然溢出也能处理喵～所以问题就解决啦！好简单对吧喵～(≧▽≦)

---

你说阿毛语言太花哨难懂了？没关系，还有更丑陋的代码喵～

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long

using namespace std;
using namespace __gnu_pbds;

const int N = 100005, base = 19260817;

int a[N], t[N];
int h[N];
set<int> st;
gp_hash_table<int, int> mp;

signed main() {
  int n, k, s;
  cin >> n >> k >> s;
  if (k > n) {
    cout << 0;
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= k; i++) {
    cin >> t[i];
    st.insert(t[i]);
  }
  int x = 0;
  for (auto it : st) {
    mp[it] = ++x;
  }
  unsigned int hsh = 0, basep = 1;
  for (int i = 1; i <= k; i++) {
    hsh = (hsh * base + mp[t[i]]);
    basep *= base;
  }
  multiset<int> ms;
  st.clear();
  for (int i = 1; i <= k; i++) {
    if (ms.find(a[i]) == ms.end()) {
      st.insert(a[i]);
    }
    ms.insert(a[i]);
    for (int j = 1; j <= s; j++) {
      h[j] = h[j] * base + (a[i] == j);
    }
  }
  vector<int> ans;
  if (st.size() == x) {
    int y = 0;
    mp.clear();
    for (auto it : st) {
      mp[++y] = it;
    }
    unsigned int hsh2 = 0;
    for (int i = 1; i <= x; i++) {
      hsh2 += h[mp[i]] * i;
    }
    if (hsh2 == hsh) {
      ans.push_back(1);
    }
  }
  for (int i = k + 1; i <= n; i++) {
    ms.erase(ms.find(a[i - k]));
    if (ms.find(a[i - k]) == ms.end()) {
      st.erase(a[i - k]);
    }
    if (ms.find(a[i]) == ms.end()) {
      st.insert(a[i]);
    }
    ms.insert(a[i]);
    for (int j = 1; j <= s; j++) {
      h[j] = h[j] * base + (a[i] == j) - (a[i - k] == j) * basep;
    }
    if (st.size() == x) {
      int y = 0;
      mp.clear();
      for (auto it : st) {
        mp[++y] = it;
      }
      unsigned int hsh2 = 0;
      for (unsigned int i = 1; i <= x; i++) {
        hsh2 += h[mp[i]] * i;
      }
      if (hsh2 == hsh) {
        ans.push_back(i - k + 1);
      }
    }
  }
  cout << ans.size() << '\n';
  for (int i : ans) {
    cout << i << '\n';
  }
}
```

---

灵感来源：<https://www.luogu.com.cn/article/lnfxpwm6>

不可爱的“原文”链接：<https://www.luogu.com.cn/paste/aklynhtr>

本文为实验性文风，希望得到大家的理解和支持。~~翻译由 DeepSeek R1 完成。~~

---

## 作者：Figo17 (赞：1)

# P6080 [USACO05DEC]Cow Patterns G 题解

先说，我没用 kmp，用的是简单 hash。

看到这题时，想，既然是道篮题，不用魔改的 kmp 应该也能过。

然后一篇小题解就诞生了。

## 1 分析

发现 $s$ 很小，理论上 $O(n \times s)$ 规模约为 $O(n \times \log n)$ 级别。

所以考虑桶排，滑动窗口，附带哈希，每次 check 时暴力乘上桶的权值即可。

## 2 构造

首先开 unsigned long long；

取 $base$ 进制表示序列，预处理出每个位置 $i,i \in [1,n]$ 的 $pw_i$ ，表示 $base^i$；

对模式串离散化后，随机附哈希权值 $hs_i$ ；

现在我们就可以愉快地表示出某段序列的哈希值了：

$now=\left( \sum_{i=l}^{r}{pw_i \times hs_{num_i}} \right)\div{pw_{i-1}}$

其中 $num_i$ 表示当前序列中 $a_i$ 对应离散后的顺序大小。

这里理解后可以暴力 $O(n^2)$。

## 3 对味



对**每种** $num_i$ 设其为 $j$；

然后开桶统计 $sum_j=\sum\limits_{i=l}^r {pw_i,\left(num_i=j\right)} $;

最后每次 check 对每个 $j$ 的 $sum_j\times hs_j$ 求和。

复杂度 $O(n\times k)$。

## 4 Code
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
int n,k,s;
int a[100005],b[25004];
int stk[100005],top;

ull hs[30],pw[100005],toth,sum[30];
int ls[30],cnt;

inline int read(){
	int s=0;char c=getchar();
	while(c<48||c>57) c=getchar();
	while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();
	return s;
}

void write(int x){
	if(x>9) write(x/10);
	putchar(x%10+48);
}

void check(int x){
	int num=0;ull now=0;
	for(int i=1;i<=s;i++) if(sum[i]) now+=sum[i]*hs[++num];
	if(now==toth*pw[x-1]) stk[++top]=x;
}

int main(){
	n=read(),k=read(),s=read();
	srand(time(0));
	for(int i=1;i<=s;i++) hs[i]=998244353ull*rand()*rand();
	pw[0]=1; for(int i=1;i<=n;i++) pw[i]=998244353ull*pw[i-1];
	
	for(int i=1;i<=n;i++) a[i]=read();
	
	for(int i=1;i<=k;i++) ls[b[i]=read()]++;
	for(int i=1;i<=s;i++) if(ls[i]) ls[i]=++cnt;
	for(int i=1;i<=k;i++) toth+=pw[i]*hs[ls[b[i]]];

	for(int i=1;i<=k;i++) sum[a[i]]+=pw[i];
	check(1);
	
	for(int l=2,r=k+1;r<=n;l++,r++) sum[a[l-1]]-=pw[l-1],sum[a[r]]+=pw[r],check(l);
		
	write(top),puts("");
	for(int i=1;i<=top;i++) write(stk[i]),puts("");
	return 0;
}
```



---

## 作者：_ZHONGZIJIE0608_ (赞：0)

给你一个长度为 $n$ 的序列 $a$ 和一个长度为 $m$ 的序列 $b$，你需要输出所有 $a$ 中的子区间，使得每个子区间的数之间的相对大小关系和 $b$ 相同。

观察到区间长度是定值，字符集很小。我们可以用哈希维护“相对大小关系”。

由此，我们可以对于“目标窗口”，也就是 $b$，以及在序列中维护的“滑动窗口”，也就是 $a$，的每一个出现的编号的出现位置集合分别当成一个串来哈希。

由于此时你存储的哈希的串是排好序的（从 $1$ 到 $s$），我们排查两个窗口的“相对大小关系”是否相同的方法就是：用两个指针（代表两个窗口）从 $1$ 到 $s$ 枚举每个哈希值，如果是 $0$ 就直接忽略，然后比较是否相同。如果有一个不同则关系就是不同的。

$O(s)$ 比较两窗口“关系”和维护窗口，$O(n)$ 扫一遍。总的时间复杂度是 $O(ns)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
const int N=1e5+10;
const int base=13331;
int n,k,s,a[N],b[N];
ull ton[30],bon[30],mi[N];
vector<int>ans;
bool check(){
    int cnt1=1,cnt2=1;
    while(cnt1<=s && cnt2 <=s){
        while(cnt1<=s && !ton[cnt1])++cnt1;
        while(cnt2<=s && !bon[cnt2])++cnt2;
        if(ton[cnt1]!=bon[cnt2])return 0;
        else ++cnt1,++cnt2;
    }
    return 1;
}
signed main(){
    //freopen("P6080_7.in","r",stdin);
    //freopen("a.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n>>k>>s;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=k;++i)cin>>b[i];
    mi[0]=1;
    for(int i=1;i<N;++i)mi[i]=mi[i-1]*base;
    if(k>n){cout<<0;return 0;}
    for(int i=1;i<=k;++i){
        bon[b[i]]+=mi[k-i];
        ton[a[i]]+=mi[k-i];
    }
    if(check())ans.push_back(1);
    for(int i=k+1;i<=n;++i){
        ton[a[i-k]]-=mi[k-1];
        for(int i=1;i<=s;++i)ton[i]*=base;
        ton[a[i]]+=mi[0];
        
        if(check())ans.push_back(i-k+1);
    }
    cout<<ans.size()<<'\n';
    for(int i:ans)cout<<i<<'\n';
    return 0;
}
```

---

## 作者：eastcloud (赞：0)

### 题意简述

给定一个队列和一个模板串，称一个串匹配另一个串当且仅当两个串中所有字符的大小关系相同，求所有能匹配模板串的队列的子串在队列中的起始位置。

### 题目分析

对于给定两个串进行匹配的题目，首先想到 kmp，而 kmp 处理的是单纯的字符串匹配，所以此题关键就在于对题意进行转换。

考虑大小关系相同有什么特殊性质，模仿 kmp 的操作，注意到当 $ i-1 $ 之前的数已经匹配时，第 $ i $ 位能是否能一起匹配只用决定于前面的大小关系。

继续观察，发现这种大小关系实质上只要满足 $ a_j < a_i < a_k $ 或 $ a_i = a_j $ 即可，其中 $ 1 \leq j,k \leq k $。因此，我们只需要对于每个 $ i $ 求出对应的数字即可。

由于$ a_j $ 和 $ a_k $ 最接近 $ a_i $，我们用 set 查询每个数掉的前驱后继，最后转换比较的方式进行 kmp。

### 代码

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
#define maxx 60
#define minx -3
using namespace std;
int a[1000001],b[1000001];
int l[1000001],r[1000001];
int loc[1000001];
int nex[1000001],f[1000001];
int ans[1000001];
set<int> t;
set<int>::iterator it;
int n,m;
int tot;
bool jud(int x,int y){
	if(l[y]==-1){int dis=y-r[y];return (a[x-dis]==a[x]);}
	if(l[y]>0){int dis=y-l[y];if(a[x-dis]>=a[x]) return false;}
	if(r[y]==m+1)return true;
	int dis=r[y]-y;
	if(a[x]>=a[x+dis]) return false;
	return true;
}
bool jud2(int x,int y){
	if(l[y]==-1){int dis=y-r[y];return (b[x-dis]==b[x]);}
	if(l[y]>0){int dis=y-l[y];if(b[x-dis]>=b[x]) return false;}
	if(r[y]==m+1)return true;
	int dis=r[y]-y;
	if(b[x]>=b[x+dis]) return false;
	return true;
}
int main(){
	int s;
	t.insert(maxx);t.insert(minx);
	cin>>n>>m>>s;
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int j=1;j<=m;j++) cin>>a[j];
	loc[32]=m+1;loc[0]=-2;
	for(int i=1;i<=m;i++){
		it=t.find(a[i]);
		if(it==t.end()){
			loc[a[i]]=i;
			r[i]=min(32,(*t.upper_bound(a[i])));
			it=t.lower_bound(a[i]);it--;l[i]=max(0,*it);
			r[i]=loc[r[i]];l[i]=loc[l[i]];
			t.insert(a[i]);
		}
		else{
			l[i]=-1;
			r[i]=loc[*t.find(a[i])];
		}
	}
	for(int i=2,j=0;i<=m;i++){
		while(j && !jud(i,j+1)) j=nex[j];
		if(jud(i,j+1)) j++;
		nex[i]=j;
	}
	for(int i=1,j=0;i<=n;i++){
		while(j && (j==m || !jud2(i,j+1))) j=nex[j];
		if(jud2(i,j+1)) j++;
		if(j==m)ans[++tot]=i-m+1;
	}
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++) cout<<ans[i]<<endl;
}
```


---

