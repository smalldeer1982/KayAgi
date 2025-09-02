# Recover an RBS

## 题目描述

A bracket sequence is a string containing only characters "(" and ")". A regular bracket sequence (or, shortly, an RBS) is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)");
- bracket sequences ")(", "(" and ")" are not.

There was an RBS. Some brackets have been replaced with question marks. Is it true that there is a unique way to replace question marks with brackets, so that the resulting sequence is an RBS?

## 说明/提示

In the first testcase, the only possible original RBS is "(())".

In the second testcase, there are multiple ways to recover an RBS.

In the third and the fourth testcases, the only possible original RBS is "()".

In the fifth testcase, the original RBS can be either "((()()))" or "(())()()".

## 样例 #1

### 输入

```
5
(?))
??????
()
??
?(?)()?)```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：BigSmall_En (赞：24)

[题目](https://www.luogu.com.cn/problem/CF1709C)

给一种 CF 上看到的代码简洁的做法。

定义左括号的值为 $1$，右括号的值为 $-1$，$cnt_i$ 为到 $i$ 位置的**已经确定**的括号值的前缀和，定义还没确定的问号数为 $q$。

从 $1$ 到 $n$ 扫字符串。发现当 $cnt_{i-1}=0$ 时，如果加入一个问号，那么这个问号必然只能是左括号（如果是右括号就不是合法的括号序列了），此时 $cnt_i=1,q=0$。

（此段内容为改正之后）同时上方这种情况并不严谨，当加入一个问号后如果 $q+cnt_{i}=1$，则 $q-1=|cnt_{i-1}|$ 也意味着先前的括号状态唯一，此时将这个问号变成左括号，同时 $cnt_i=1,q=0$。

到最后如果 $|cnt_n|=q$，则说明方案唯一，（即如果 $cnt_n\geq 0$，那么所有未确定的问号只能是右括号；如果 $cnt_n<0$，那么未确定的问号只能是左括号），反之可以选择至少一对括号，可以选择是 $A(B)C$ 的情况或 $A)B(C$ 的情况，其中 $A,B,C$ 各代表一串括号序列。

代码如下

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N=200005;
char s[N];int n;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%s",s+1);n=strlen(s+1);
		int cnt=0,qry=0;
		for(int i=1;i<=n;++i){
			if(s[i]=='(')++cnt;
			else if(s[i]==')')--cnt;
			else ++qry;
			
			if(cnt+qry==1)cnt=1,qry=0;
		}
		if(abs(cnt)==qry)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

先前错误的代码

```cpp
if(!cnt&&qry==1)cnt=1,qry=0;
```

根据过去错误的代码给一组 hack 数据

```cpp
?????))))?
```

感觉说得不是很清晰，希望大佬们多多指正。

更新之后还是感觉不太满意，许多本质的东西感觉仍不到位，再次希望多多指正。

---

## 作者：Jr_Zlw (赞：13)

## 贪心构造

首先题目里面保证了必定有一个合法的状态，我们不妨先构造一个出来。

经过某个经典转换，将左右括号分别标为  $+1,-1$，那么一个串合法当且仅当这个串的和为  $0$  且任意前缀和  $\geq 0$  。

所以贪心地选择先填写左括号，使得前缀和尽量大即可构造出一个合法串。

然后考虑判断是否能通过改变这个合法串来构造出另一个合法串。

我们肯定是将一个左括号改成右括号，一个右括号改成左括号，相当于转换序列中将一个  $+1$  转换为  $-1$。而这样做的风险在于会因为某个前面的  $+1$  改成  $-1$  导致后面的某个前缀  $<0$。

所以尽可能晚的选择将  $+1$  改成  $-1$，尽可能早的将  $-1$  改成  $+1$  来挽回可能  $<0$  的前缀。改完以后再判一次是否合法即可。

具体来说就是先给前面的空填上左括号，直到总左括号数等于长度的一半，剩下的空填上右括号以构造第一个合法解，再交换最后一个填左括号的空和第一个填右括号的空以判断是否存在第二个解。另外，如果问号里完全没填某一种括号一定有唯一解。

代码：

```
#include<cstdio>
#include<cstring>
#define rep(a,b,c) for(int c(a);c<=(b);++c)
#define drep(a,b,c) for(int c(a);c>=(b);--c)
inline int read()
{
	int res=0;char ch=getchar();bool flag=0;while(ch<'0'||ch>'9')ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();return flag ? -res : res ;
}
template<typename T> inline T min(const T&x,const T&y){return x<y?x:y;}
template<typename T> inline T max(const T&x,const T&y){return x<y?y:x;}
template<typename T> inline void Swap(T&x,T&y){T tmp=x;x=y;y=tmp;}
const int N=2e5+10;char c[N];int n;int s[N],a[N];
inline void Solve()
{
	scanf("%s",c+1);n=strlen(c+1);
	rep(1,n,i)if(c[i]=='(')a[i]=1;else if(c[i]==')')a[i]=-1;else a[i]=0;
	int sm[2]={0,0};rep(1,n,i)if(c[i]=='(')++sm[0];else if(c[i]==')')++sm[1];
	if(!(n/2-sm[0])||!(n/2-sm[1])){puts("YES");return;}
	int k=0;rep(1,n,i)if(c[i]=='?'&&k<n/2-sm[0]){++k;a[i]=1;}else if(c[i]=='?')a[i]=-1;
	int l=1,r=1;drep(n,1,i)if(c[i]=='?'&&a[i]==1){l=i;break;}
	rep(1,n,i)if(c[i]=='?'&&a[i]==-1){r=i;break;} a[l]=-1;a[r]=1;
	int res=0;rep(1,n,i){res+=a[i];if(res<0){puts("YES");return;}}
	puts("NO");return;
	
}
signed main()
{
	int T=read();
	while(T--)Solve();
}
```

---

## 作者：Gokix (赞：8)

[CF1709C](https://www.luogu.com.cn/problem/CF1709C)

容易被误导到一些奇怪思路上

------------

记原序列长度为 $n$。

想要搞出一个 RBS，有一个明显的必要条件是左括号和右括号个数得相等（同时也说明 $n$ 得是偶数）。这点我们可以通过统计原序列中的左括号数和右括号数，并用 $\frac{n}{2}$ 分别减去它们，得到的结果分别记为 $L,R$。

显然，当 $L=0$ 或者 $R=0$，必然只有唯一解。直接特判掉。

接下来让我们回想起一个括号序列是 RBS 的**等价**表述：对于任意右括号，其之前的右括号个数均小于左括号个数。

而题目又保证了原序列有至少一种合法分配方式，所以把从左往右数前 $L$ 个 `?` 替换成 `(`，后 $R$ 个 `?` 替换成 `)` 一定是一种合法分配方案。

证明考虑其它方案必然是该方案某几对左右括号互换位置而得，但每互换一对左右括号，在这对左右括号之间的括号前的右括号数就会加 1，而其它位置的括号数目不受影响。所以每互换一对括号都是一个不优操作。从而证明了上述方案为合法分配方案。

上一个分配方案是最不劣的。而判断是否存在多解，我们只需判断次不劣的方案是否合法。这里直接给出次不劣的方案：在最不劣分配方案基础上，将第 $L$ 个 `?` 替换为 `)`，将第 $L+1$ 个 '?' 替换为 `(`，其余不变。

证明思想与上一个证明类似，这里不再赘述。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long rd(){char ch=getchar();long long x=0,f=1;while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
                        while('0'<=ch && ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void wr(long long x){if(x<0){putchar('-');x=-x;}if(x>9) wr(x/10);putchar(x%10+'0');}

const long long N=2e5+10;
long long t,n,l,r,L,R,y,a[N+10],f[N+10],ct,po,op;
string s;

int main(){
	long long i,j,u,v,gx;
	t=rd();
	while(t--){
		cin>>s;
		n=s.size();
		l=r=x=0;
		for(i=0;i<n;i++){
			if(s[i]=='(') a[i+1]=1,l++;
			else if(s[i]==')') a[i+1]=2,r++;
			else a[i+1]=3;
		}
		if(n&1){putchar('N'),putchar('O'),putchar('\n');continue;}
		y=n/2;
		L=y-l;R=y-r;
		ct=0;
		for(i=1;i<=n;i++){
			if(a[i]==3){
				ct++;
				if(ct==L) po=i;
				if(ct==L+1) op=i;
				if(ct>L) a[i]=4;
			}
		}
		for(i=0;i<=n+1;i++) f[i]=0;
		for(i=1;i<=n;i++){
			if(a[i]==1 || a[i]==3) gx=1;
			else gx=-1;
			f[i]=f[i-1]+gx;
		}
		if(L==0 ||R==0){putchar('Y'),putchar('E'),putchar('S'),putchar('\n');continue;}
		swap(a[po],a[op]);
		for(i=0;i<=n+1;i++) f[i]=0;
		for(i=1;i<=n;i++){
			if(a[i]==1 || a[i]==3) gx=1;
			else gx=-1;
			f[i]=f[i-1]+gx;
		}
		gx=1;
		for(i=1;i<=n;i++){
			if(f[i]<0){
				gx=0;
				break;
			}
		}
		if(!gx){putchar('Y'),putchar('E'),putchar('S'),putchar('\n');continue;}
		else{putchar('N'),putchar('O'),putchar('\n');continue;}
	}
	return 0;
}
```

正如[官方题解评论区](https://codeforces.com/blog/entry/105164?#comment-935234)所指出的那样，有更为简洁的写法。

---

## 作者：2018ljw (赞：4)

这场 C 比 D 难（确信）

题目大意：给定一个残缺的括号序列，问将其变为合法括号序列的方案数是否唯一。括号序列长 $2\times 10^5$，保证至少存在一种合法的方案。

判断方案数是否唯一，等价于我们能否构造出第二种序列，使得其合法。考虑我们贪心构造的流程：记录还需要几个左右括号，当遇到一个 `?` 时，如果能填 `(` 尽量填 `(`。

这样贪心显然是对且最优秀的，考虑我们判断括号匹配时，左括号进栈，右括号出栈。不合法当且仅当某次出栈时栈为空或最终栈不为空。那么我们就不妨前期多进栈，让元素尽量晚的弹出去，一定是更为优秀的。

考虑如何构造一个不同的串。那么我们就要钦定一个括号的方向与原串不同，看剩下的能不能构造出。不难发现，出入栈的过程中，如果"第二优秀的"不行，那么更劣的一定不行。但如果”第三优秀的“不行，”第二优秀的“可能行。

所以我们考虑这个”第二优秀的“方案应该长啥样。不难发现，”最优秀“的方案优秀是因为其尽可能让左括号进去，再用右括号一点点弹出去。那么我们”第二优秀的“，就应该让最后一个左括号**慢一步进栈**。因此得解。

实质上就是交换最中间的左右括号，匹配有影响的只有被交换的括号中间的区间。我们可以把左括号看成 $1$，右括号看成 $-1$，就等价于 $[l,r-1]$ 中有没有一个位置前缀和 $\le 1$。有则方案数唯一，否则不唯一。其中 $l,r$ 为被交换的左右括号位置。

赛时代码如下，实现时采用二次构造的方式。

```cpp
#include<cstdio>
#include<cstring>
char s[200005],p[200005];
int main(){
	int i,n,t,lpos=0;
	scanf("%d",&t);
	while(t--){
		scanf("%s",s+1);
		n=strlen(s+1);
		int ls=0,rs=0,nl=0,nr=0;
		for(i=1;i<=n;i++){
			if(s[i]=='(')ls++;
			if(s[i]==')')rs++;
		}
		nl=n/2-ls;nr=n/2-rs;
		if(!nl||!nr){
			printf("YES\n");
			continue;
		}
		for(i=1;i<=n;i++)if(s[i]=='?'&&nl)nl--,lpos=i;
		nl=n/2-ls;
		nr--;s[lpos]=')';
		for(i=1;i<=n;i++){
			if(s[i]!='?')p[i]=s[i];
			else{
				if(nl)nl--,p[i]='(';
				else nr--,p[i]=')';
			}
		}
		bool ok=1;
		int sum=0;
		for(i=1;i<=n;i++){
			if(p[i]=='(')sum++;
			else sum--;
			if(sum<0){
				ok=0;
				break;
			}
		}
		if(ok)printf("NO\n");
		else printf("YES\n");
	}
}
```

---

## 作者：yukimianyan (赞：2)

大家好，我非常喜欢猜结论 + 暴力，于是我以 $O(n\log n)$ 的二分 + ST 表过了这道题。

## 题意简述
一个由 `(`、`)`、`?` 组成的原括号串，`?` 可以转变成 `(` 或 `)`，问你是否存在多种方案，使原括号串转变为由 `(` 或 `)` 组成的合法括号串，保证原括号串可以转变成至少一个合法括号串。

分成两个部分：构造合法方案、交换一对 `?`。在此之前我们把括号串抽象一下：

## 模型的建立
我们试图把一个括号串搬到平面直角坐标系里，我们把 `(` 看作 $+1$，`)` 看作 $-1$，例如红线是 `((()()))`，蓝线是 `(())()())`：

![](https://cdn.luogu.com.cn/upload/image_hosting/hzs2zdqg.png)

找一点性质：

1. 这是一条曲线，从 $(x,y)$ 能到达 $(x+1,y\pm 1)$。
2. 这条曲线从 $(0,0)$ 出发，最后回到 $(x,0)$。实际意义：每个左括号都找到了一个右括号，它们之间互相抵消了。
3. 对于任一点 $(x,y)$，都有 $y\geq 0$。实际意义：右括号前面必须有左括号。为了叙述方便，称前缀和 $x$ 为 $y$，记作 $s_x=y$。

这题用到的结论到这里为止。

## 构造合法方案
我们看到性质 3，它要求前缀和要尽可能大，那我们尽可能填 `(` 吧！

但是这么暴力不行，记 $cnt$ 是你这样填出来最后一个前缀和 $s_n$，你再倒着扫一遍填 `)`，把错填的 $+1$ 改成 $-1$，再改回来需要满足 $cnt\geq 2$，不然就破坏了性质 3，这是反悔贪心的思想。

## 交换一对问号
我们已经有了一个合法方案，再试图构造出另一种合法方案，先猜个结论：一个合法方案可以看作是另一种合法方案**交换若干对 `?` 转变而来的左右括号**得到的，简要证一下：

- 加法有交换律，$+1-1$ 和 $-1+1$ 没有区别，在不考虑性质 3 的情况下合法。但是 $+1-1$ 和 $+1+1$ 有区别，破坏性质 3，因此不能单独把一个 `)` 转变成 `(`。
- 因为 `?` 的数量是固定的，所以左右括号的数量是固定的，因为我们可以交换一对括号，又因为括号之间是没有区别的，所以无论是怎样的转换，都能拆成若干个交换操作的和。证毕。

但是我们应该交换哪些括号呢？还是这个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hzs2zdqg.png)

这是样例 5，本质上是第 3 个 `(` 和第 7 个 `)` 交换而输出了 `NO`。分别考虑 `(` 和 `)` 互换与 `)` 和 `(` 互换：
1. `(` 和 `)` 互换：相当于红线转变成蓝线。不难看出这条红线的 $[3,7)$ 部分往下降了两格，而端点 $7$ 不变。猜结论：**当左、右括号之间的前缀和的最小值 $\geq 2$ 时（不包括右括号），这两个括号可以交换。**
2. `)` 和 `(` 互换：相当于蓝线转变成红线，往上抬两格，猜结论：**只要原来方案合法，换完的方案也合法。**

现在翻译成 OI 语言：令原方案为括号串 $a$。
1. 若 $a_i={\tt'('},a_j={\tt ')'}$，且 $i<j,\min\limits_{i\leq k<j}{s_k}\geq 2$，则 $a_i,a_j$ 可以交换，即有多个解。
2. 若 $a_i={\tt')'},a_j={\tt '('}$，且 $i<j$，则 $a_i,a_j$ 可以交换，即有多个解。

对于第一种情况，我们有暴力的实现方法：ST 表预处理 $s$ 的最小值，作 $[a_i={\tt ')']}$ （即右括号个数）的前缀和 $f$，枚举 $i$，二分最大的 $j$ 满足 $\min\limits_{i\leq k< j}{s_k}\geq 2$，判断是否有 $f_{j+1}-f_{i-1}\geq 0$。

对于第二种情况，同理，只是不需要二分，钦定 $j=n$ 即可。

这道题做完了。

## 代码
有点复杂，但在赛场上只能写出些这样的东西了，我太菜了。
```cpp
#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
template<class T,int N> struct STable{
    int lg[N+10],n;
    T f[21][N+10];
    int pw(int x){return 1<<x;}
    STable():n(0){lg[0]=-1;}
    void insert(T x){
        f[0][++n]=x,lg[n]=lg[n>>1]+1;
        for(int t=1;pw(t)<=n;t++){
            int i=n-pw(t)+1;
            f[t][i]=min(f[t-1][i],f[t-1][i+pw(t-1)]);
        }
    }
    T query(int l,int r){
        int len=lg[r-l+1];
        return min(f[len][l],f[len][r-pw(len)+1]);
    }
};
int n,f[200010],g[200010][2];
char a[200010],s[200010];
STable<int,200010> t;
int binary(int L,int R,int d){
	int ans=0;
	while(L<=R){
		int mid=(L+R)>>1;
		if(t.query(L,mid)>=d) ans=mid,L=mid+1;
        //         ^ 为什么这里写个 L 是对的呢？
        //如果这个条件成立，L 跳到右边，以后不再访问这一段了，相当于省下一段要访问区间。
        //如果不成立，L 不会改，没什么影响。所以这真的是对的。
		else R=mid-1;
	}
	return ans;
}
int mian(){
	t.n=0,t.lg[0]=-1;
    //构造合法方案
	int cnt=0;
	for(int i=1;i<=n;i++){
		s[i]=a[i];
		if(a[i]=='(') cnt++;
		else if(a[i]==')') cnt--;
		else{
			cnt++;//'('
			s[i]='(';
		}
	}
	for(int i=n;i>=1;i--) if(a[i]=='?'&&cnt>=2) cnt-=2,s[i]=')';
//	s[n+1]=0,puts(s+1); 
	//预处理
	for(int i=1;i<=n;i++){
		if(s[i]=='(') f[i]=f[i-1]+1;
		else f[i]=f[i-1]-1;
		assert(f[i]>=0);
		t.insert(f[i]);
		g[i][0]=g[i-1][0],g[i][1]=g[i-1][1];
		if(a[i]=='?'){
			if(s[i]=='('){
				g[i][0]++;
			}else{
				g[i][1]++;
			}
		}
//		printf("(%d,%d)%c",g[i][0],g[i][1]," \n"[i==n]);
	}
	g[n+1][0]=g[n][0],g[n+1][1]=g[n][1];
    //二分 + ST 表
	for(int i=1;i<=n;i++){
		if(a[i]=='?'){
			if(s[i]=='('){
				//find last 2
				int pos=binary(i,n,2);
//				printf("i=%d,pos=%d\n",i,pos);
				//if there is a ')' in [i,pos+1] then swap
				if(g[pos+1][1]-g[i-1][1]>0) return puts("NO"),0;
                //      ^~ 不包括右括号！
			}else{
				//find last 0=n
				int pos=n;
				//if there is a '(' in [i,pos+1] then swap
				if(g[pos+1][0]-g[i][0]) return puts("NO"),0;
			}
		}
	}
	//OK we believe ans=YES
	puts("YES");
	return 0;
}
int main(){
//	#ifdef LOCAL
//	 	freopen("input.in","r",stdin);
//	#endif
	for(scanf("%*d");~scanf("%s",a+1);n=strlen(a+1),mian());
	return 0;
}
/*
9
(?))
??????
()
?(?)()?)
(?))
??
(??)
(?(?))
?(?) 
YNYNYYNNY
*/
```


---

## 作者：Zeardoe (赞：1)

#### CF1709C
题意：给定一个匹配括号序列，将部分位置变成问号，问是否有唯一的方案将所有问号变成左括号或右括号，使得该括号序列依然为匹配的。

分析：
首先我们考虑构造一组方案。先算出括号中左括号和右括号的位置。当左括号没用完的时候我们优先使用左括号。否则使用右括号。

为什么这么做呢？证明：因为题目保证一定存在一组合法的括号序列，故一定有一种合法的序列。假设这种方案（记为 $S$）不成立，那么一定存在另一种方案（记为 $T$）成立。并且这种方案一定是 $S$ 中经历若干次左右括号交换而来的。考虑在 $S$ 的某个位置 $x$ 出现不成立的情况，说明 $1 \sim x$ 中右括号数量大于左括号数量。考虑被交换的位置 $y,z$，满足 $S_y=\mathtt{'('},S_z=\mathtt{')'}$，则 $y<z$ 一定成立。
1. 如果 $x<y<z$，那么交换之后，$x$ 左边右括号和左括号数量不变，依然会在 $x$ 处不成立。
2. 如果 $y<x<z$，那么交换之后，$x$ 左边会多出一个右括号少掉一个左括号，更不会成立。
3. 如果 $y<z<x$，那么交换之后，$x$ 左边右括号和左括号数量不变，依然会在 $x$ 处不成立。
与假设矛盾，原命题成立。

然后我们考虑是否能构造出其他方案合法。考虑这个方案：将 $S$ 中最后一个左括号和第一个右括号交换，依然类似的思路证明该方案次优。判断这种方案是否可行，如果可行那么 $\mathtt{NO}$，否则 $\mathtt{YES}$。（如果不存在这种方案，也就是问号中没填左/右括号，一定 $\mathtt{YES}$）。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i, a, b) for(int i = (a); i <= (b); i++)
#define cl(i, n) i.clear(),i.resize(n);
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int inf = 1e9;
int l, r, q, nl, nr;
stack<int> lft; queue<int> rgt;
bool check(string s){
    int cnt=0;
    f(i,0,(int)s.size()-1){if(s[i]=='(')cnt++;else cnt--;if(cnt<0)return 0;}
    return 1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t; cin >> t;
    while(t--) {
        while(!lft.empty())lft.pop();while(!rgt.empty())rgt.pop();
        string s; cin >> s; int n = s.size();l=r=0;
        f(i, 0, (int)s.size() - 1) {
            if(s[i]=='(')l++; else if(s[i]==')')r++; 
        }
        nl=(n/2)-l, nr=(n/2)-r;
        f(i, 0, (int)s.size() - 1) {
            if(s[i]=='?'){
                if(nl) {lft.push(i);s[i]='(';nl--;}
                else {rgt.push(i);s[i]=')';nr--;}
            }
        }
        if(lft.empty()||rgt.empty()) {cout<<"YES\n";continue;}
        int x=lft.top(), y=rgt.front(); 
        swap(s[x],s[y]); if(check(s)){cout<<"NO\n";} else {cout<<"YES\n";}
    }
    return 0;
}
```

---

## 作者：Jeremiahy (赞：0)

### 大致题意

给你一些括号序列，一些位置为问号，询问将它填补为一个合法的括号序列是否存在唯一解（数据保证有解）。

# 分析

首先，既然数据已经保证有唯一解，我们不妨先将构造出来一种，方法是在问号位置全部填补左括号，直到所有左括号的数量达到序列长度的一半，剩下的问号填右括号。

一个合法的括号序列在任何位置左括号的数量都大于等于右括号的数量，并且整体左括号数量等于右括号数量，所以上述构造方法保证正确。

然后我们可以考虑能否在原有序列的基础，改变为另一个括号序列并且合法就可以了。

改变肯定是将一个原来是问号的左括号改变为右括号，另一个原来是问号的右括号改变为左括号。

由于一个合法的括号序列在任何位置左括号的数量都大于等于右括号的数量，所以我们可以将变为右括号尽可能地往后拖，变为左括号尽可能提前，来保证前面满足上述性质。

所以可以交换最后一个填左括号的问号和第一个填右括号的问号，然后判断是否合法。

除此之外，如果问号里填的全是一种括号一定有唯一解。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[200005], T, s[200005];
string c;
signed main(){
	cin >> T;
	while (T--) {
		int flag = 0, cntl = 0, cntr = 0, k = 0, l = 1, r = 1, num = 0; //初始化
		cin >> c;
		for (register int i = 0; i < c.length(); i++)
			if (c[i] == '(')//经典的 +1 -1转化策略
				a[i] = 1;
			else if (c[i] == ')')
				a[i] = -1;
			else 
				a[i] = 0;
		for (register int i = 0; i < c.length(); i++)
			if (c[i] == '(')//预处理左括号和右括号的数量
				cntl++;
			else if (c[i] == ')')
				cntr++;
		if (c.length() / 2 == cntl || c.length() / 2 == cntr) {//如果全填的某一括号
			puts("YES");
			continue;
		}
		for (register int i = 0; i < c.length(); i++)
			if (c[i] == '?' && k < c.length() / 2 - cntl)
				k++, a[i] = 1;
			else if (c[i] == '?')
				a[i] = -1;
		for (register int i = c.length() - 1; i >= 0; i--)
			if (c[i] == '?' && a[i] == 1) {
				l = i;//最后一个左括号
				break;
			}
		for (register int i = 0; i < c.length(); i++)
			if (c[i] == '?' && a[i] == -1) {
				r = i;//第一个右括号
				break;
			} 
		a[l] = -1, a[r] = 1;
		for (register int i = 0; i < c.length(); i++){
			num += a[i];
			if (num < 0) {//不合法（存在唯一解）
				puts("YES");
				flag = 1;
				break;
			}
		}
		if (!flag)
			puts("NO");
	}
	return 0;
}
```


---

## 作者：BigJoker (赞：0)

# Solution

首先判断一下绝对只有一种的情况。

当左括号或者右括号的数量达到了 $\frac{n}{2}$ 时，问号只有填没有满的。

然后我们再来思考一下，有一种情况肯定是合法的，那就是左边的问号全都是 `(` 而其余的全是 `)` 这种情况是一定会有解的，这个可以根据栈判断括号的原理来判断，肯定先加了左括号，右括号才会有匹配的。

因为题目不止说了一种，还要考虑一种情况。

贪心的想，将问号所组成的左括号最右边的与问号所组成的右括号最左边的进行交换，如果可行，那一定可行，这个也是栈判断括号的原理。

# Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define mem(a,x) memset(a,x,sizeof(a))
#define inf 0x3f3f3f3f
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define re register
#define il inline
using namespace std;
typedef long long LL;
const int N=2e5+5;
il int qr(){
	int s=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9') (ch=='-'?f=-1:1),ch=getchar();
	while(ch>='0' && ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*f;
}
il void qw(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) qw(x/10);
	putchar(x%10+'0');
}
int T=qr(),n,lans,rans;
char a[N];
int main(){
	while(T--){
		cin>>(a+1);
		n=strlen(a+1);
		lans=rans=0;
		for(re int i=1;i<=n;i++){
			if(a[i]=='(') lans++;
			if(a[i]==')') rans++;
		}
		if(lans*2==n || rans*2==n) puts("YES");
		else{
			lans=n/2-lans;
			int lmax=0,rmin=2e6,sum=0;
			for(re int i=1;i<=n;i++){
				if(a[i]=='?'){
					if(lans) a[i]='(',lans--,lmax=max(lmax,i);
					else a[i]=')',rmin=min(rmin,i);
				}
			}
			swap(a[rmin],a[lmax]);
			for(re int i=1;i<=n;i++){
				if(a[i]=='(') sum++;
				else{
					sum--;
					if(sum<0) break;
				}
			}
			if(sum<0) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

## 题意

共 $t$ 组数据，每组给定一个字符串 $s$，包括 `(`， `)` 和 `?`。你可以进行无限次操作，每次把一个 `?` 换成一个 `(` 或者一个 `)`。问是否有多种方法可以将这个字符串变为一个正确的括号序列。

## 解法

考虑贪心。

对于每一个字符串，我们不妨先找到其中一个正确的括号序列。假设最初这个字符串长度为 $n$，其中有 $x$ 个 `(`，$y$ 个 `)`。那么我们要将 $\dfrac{n}{2} - x$ 个 `?` 替换成 `(`，把 $\dfrac{n}{2} - y$ 个 `?` 替换成 `)`。

显然当一个字符串是一个括号序列时，对于每一位 $i$，从 $1$ 到 $i$ 中 `(` 的出现次数一定 $\geq$ `)` 出现的次数。并且最终 `(` 和 `)` 出现次数一样。

我们不妨找到 `?` 变成 `(` 的所有字符中最靠后的一个和 `?` 变成 `)` 最靠前的一个。交换这两个 `(` 和 `)`。如果交换后这是一个合法括号序列，那么至少有两种合法方案，如果不合法，则只有一种合法方案。

接下来考虑证明：

假设找到的两个位置为 $i$ 和 $j$。反证，如果有另一个合法序列，交换了 $x$ 和 $y$，显然不存在 $x > i$ 或 $y < j$，因为 $i$ 和 $j$ 都是端点。那么一定有 $x \leq i$ 和 $y \geq j$。显然对于 $1$ 到 $x - 1$ 和 $y + 1$ 到 $n$ 而言，与交换 $i, j$ 没有区别对于中间的括号，由于 $x$ 和 $y$ 的范围比 $i$ 和 $j$ 大，显然选取较小的范围也一定可以。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

int t;
string s;

inline bool check(string p)
{
	int c1 = 0, c2 = 0, l = p.size() - 1;
	for (int i = 0; i <= l; i++)
	{
		c1 += p[i] == '(';
		c2 += p[i] == ')';
		if (c1 < c2) return 0;
	}
	if (c1 != c2) return 0;
	return 1;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> t;
	while (t--)
	{
		cin >> s;
		int l = s.size() - 1;
		int c1 = count(s.begin(), s.end(), '('), c2 = count(s.begin(), s.end(), ')');
		string copy = s;
		int pl = 0, pr = 0;
		for (int i = 0; i <= l; i++)
		{
			if (copy[i] == '?' && c1 + 1 <= (l + 1) / 2) copy[i] = '(', c1++, pl = i;
			else if (copy[i] == '?')
			{
				copy[i] = ')', c2++;
				if (!pr) pr = i;
			}
		}
		string h = copy;
		swap(copy[pl], copy[pr]);
		if (h != copy && check(copy))
		{
			printf("NO\n");
		}
		else printf("YES\n");
	}
	return 0;
}
```


---

## 作者：codemap (赞：0)

## 题目分析

我们从前往后扫一遍，使用两个计数器，一个 $s_1$ 记录左括号数量减右括号数量，一个 $s_2$ 记录还不能确定的问号数量。

当 $s_1$ 为零且当前遇到问号，说明之前无需再考虑，且当前必为左括号，直接记录当前为左括号并继续。

除此之外，遇到左括号 $s_1$ 加一，遇到右括号 $s_1$ 减一，遇到问号 $s_2$ 加一。

$s_0$ 小于零时，说明前面有问号必为左括号，$s_1$ 加一，$s_2$ 减一。

特别要注意的是，若 $s_1$ 为零且 $s_2$ 为奇数，说明前面左右括号数量相同，且问号不能自己组成合法序列，为使左括号不少于右括号，必有一个为问号为左括号，$s_1$ 加一，$s_2$ 减一。

最后结尾时判断一下， 如果 $s_2 >s_1$，说明还不能判断的问号数量大于当前失配的左括号数量，则不存在单一匹配，否则则可以找到。

## 代码

```pascal
#include<iostream>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t,i,s1,s2;
    string a;
    cin>>t;
    while(t--)
    {
        cin>>a;
        s1=0;
        s2=0;
        for(i=0;i<a.size();i++)
        {
            if(s1==0&&a[i]=='?')
            {
                s1++;
                continue;
            }
            if(a[i]=='(')
                s1++;
            else if(a[i]==')')
                s1--;
            else
                s2++;
            if(s1<0)
            {
                s2--;
                s1++;
            }
            if(s1==0&&s2%2==1)
            {
                s2--;
                s1++;
            }
        }
        if(s2>s1)
            cout<<"NO\n";
        else
            cout<<"YES\n";
    }
    return 0;
}
```


---

