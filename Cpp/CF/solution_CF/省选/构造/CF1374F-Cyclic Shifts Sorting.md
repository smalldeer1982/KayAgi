# Cyclic Shifts Sorting

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

In one move, you can choose some index $ i $ ( $ 1 \le i \le n       - 2 $ ) and shift the segment $ [a_i, a_{i + 1}, a_{i + 2}] $ cyclically to the right (i.e. replace the segment $ [a_i, a_{i +       1}, a_{i + 2}] $ with $ [a_{i + 2}, a_i, a_{i + 1}] $ ).

Your task is to sort the initial array by no more than $ n^2 $ such operations or say that it is impossible to do that.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
5
5 4 3 2 1
8
8 4 5 2 3 6 7 3
7
5 2 1 6 4 7 3
6
1 2 3 3 6 4```

### 输出

```
0

6
3 1 3 2 2 3 
13
2 1 1 6 4 2 4 3 3 4 4 6 6 
-1
4
3 3 4 4```

# 题解

## 作者：World_Creater (赞：4)

神似 [P3516](https://www.luogu.com.cn/problem/P3516) 的一道题。

考虑让数字从小到大归位。

利用选择排序，每次选择当且未归位的数中最小的那个往前跳。

图像模拟一下，我们用红色表示要归位的，蓝色表示最终位置，$X_i$ 表示其他无关紧要的位置。

以如下序列为例：

$$1,2,3,\textcolor{blue}{X_1},X_2,X_3,\textcolor{red}4\ldots$$

我们可以操控红色位置前两个的位置做循环位移，这样红色就往前跳了两格：

$$1,2,3,\textcolor{blue}X_1,\textcolor{red}4,X_2,X_3$$

当然最后跳两格可能会跳过头（像上面），这时候我们连续操控一次蓝色位置，就可以让红色位置后移一格，然后在跳两格，即：

$$1,2,3,X_2,\textcolor{blue}X_1,\textcolor{red}4,X_3$$
$$1,2,3,\textcolor{red}4,X_2,\textcolor{blue}X_1,X_3$$

每次归位一个数都不影响之前的数，因此每次都可以完美的归位一个数从而影响问题规模。

但这样有一个问题，最后两个数的时候动不了了，要交换的位置超过了上限。

比如：

$$1,2,3,5,4$$

此时有结论：遇到这种情况下，若有重复数字，有解，否则无解。

有重复数字的构造：

1. 倒数第三个数字和倒数第一个数字重复。

直接令倒数第三个数字循环位移即可，例：

$$1,2,1\to1,1,2$$

2. 之前有数字重复。

例：
$$1,2,2,3,5,4$$

构造下列做法：

+ 找到最后一对相邻的重复的数字，并先将后面一个循环位移，再将前面一个循环位移，即：

$$1,2,2,3,5,4$$
$$1,2,5,2,3,4$$
$$1,2,2,5,3,4$$

然后重做一遍选择排序的流程，可以证明有解。

关于上面做法的证明：

首先若我们交换相邻两个不同的数，序列逆序对奇偶性改变（加一或减一）。

然后一次循环位移可以被拆成两次相邻交换，因此若序列没有重复数字，经过任意多次操作都不会改变逆序对奇偶性。

发现我们上面唯一无解情况恰巧就是：有一个逆序对，序列无重复数字，这个时候你不可能改变奇偶性变成零个。

而有重复数字时，我们上面的做法本质上是构造了一次值指交换相邻两个数操作，这个操作会改变奇偶性，把原来奇数个变成偶数个，然后我们后面没有归位的数字中又没有重复的，因此一定可以把逆序对置零，因此一定可以排序。

操作次数和时间复杂度均为 $\mathcal{O}(n^2)$，但是完全到不了这个上界。

[码](https://codeforces.com/contest/1374/submission/212345307)

---

## 作者：stoorz (赞：4)

题目大意：给出一个长度为 $n$ 的序列，每次可以将任意一个数字向前移动两位。求是否有将这个序列变为单调不降的方案。如果有，请输出方案，其中方案的第 $i$ 个数字 $x$ 表示第 $i$ 次将序列中第 $x+2$ 个数字移动到第 $x$ 个数字的前面。

首先容易发现按照这种移动方式不可能在不改变其他数字的前提下交换相邻两个数字。因为如果存在一种交换两个数字的方式的话，那么任意序列都可以有方案复原。~~那么样例中第 4 个数据就不可能是 -1。~~

所以可以很轻松的想到先把前 $n-2$ 个数字复原。具体的，如果位置 $i$ 的数字要移动到位置 $j(i>j)$：
- 如果 $i=j+1$，那么分别将位置 $i+1$ 和 位置 $i$ 的数字向前移。此时该数字到达位置 $j$。
- 如果 $i>j+1$，那么直接将 $i$ 往前移，然后令 $i=i-2$ 继续。

排完前 $n-2$ 个数字后，根据我们得出的结论，所以只需要判断最后两个数字的大小关系即可。

但是有一种例外，如果数列中存在两个位置的数字相等，那么此时即使最后两个数字是前面大于后面，但是我们可以同时交换最后两个数和相等的两个数，这样显然前 $n-2$ 个数依然保持单调不减，最后两个数也保证了单调不减。

此时我们就全盘推到重来，在判断这两个相同的数的前后顺序时颠倒一下就行了。为了方便，可以利用离散化给数字重新编号，满足编号依然按照原来的数字大小顺序排列且两两不同。最终如果有例外情况，那么就找到相等的两个数字，将他们的编号调换一下即可。

显然这种构造移动方式在 $n^2$ 步以内。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=510;
int Q,n,top,b[N],a[N],c[N],ans[N*N],vis[N];

bool solve()
{
	for (int k=1;k<=n-2;k++)  //枚举，表示前 k-1 位已经搞定，正在移动第 k 小的数到第 k 位
	{
		int minn=2147483647,pos;
		for (int i=k;i<=n;i++)
			if (a[i]<minn) minn=a[i],pos=i;
		for (int i=pos;i>k;)
		{
			if (i==k+1)  //按照上述方法移动
			{
				ans[++top]=k; ans[++top]=k; i--;
				swap(a[i],a[i+1]); swap(a[i],a[i+2]);
				swap(a[i],a[i+1]); swap(a[i],a[i+2]);
				break;
			}
			else
			{
				ans[++top]=i-2; i-=2; 
				swap(a[i],a[i+1]); swap(a[i],a[i+2]);
			}
		}
	}
	if (a[n]>a[n-1]) return 1;  //判断是否还原
	return 0;
}

int main()
{
	scanf("%d",&Q);
	while (Q--)
	{
		top=0;
		scanf("%d",&n);
		memset(vis,0,sizeof(vis));
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&c[i]);
			vis[c[i]]++;
		}
		for (int i=1;i<=500;i++)  //重新编号
			vis[i]+=vis[i-1];
		for (int i=1;i<=n;i++)
			b[i]=vis[c[i]]--;
		memcpy(a,b,sizeof(a));
		if (solve())  //判断一般情况下能否还原
		{
			printf("%d\n",top);
			for (int i=1;i<=top;i++)
				printf("%d ",ans[i]);
			putchar(10);
		}
		else
		{
			top=0;
			memset(vis,0,sizeof(vis));
			for (int i=1;i<=n;i++)
			{
				if (vis[c[i]]) //已经标记过这个数字，也就是这个数字重复了
				{
					swap(b[vis[c[i]]],b[i]);  //交换编号
					break;
				}
				vis[c[i]]=i;
			}
			memcpy(a,b,sizeof(a));
			if (solve())  //重新排序
			{
				printf("%d\n",top);
				for (int i=1;i<=top;i++)
					printf("%d ",ans[i]);
				putchar(10);
			}
			else printf("-1\n");
		}
	}
	return 0;
}

```

---

## 作者：WaterSun (赞：3)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18575320)

与 @Zelotz duel，苦战 129min AC。

# 思路

（本文中默认字符的大小顺序为：$a < b < c < \dots$）

首先发现不关心最后两个数是否合法，将前 $n - 2$ 个位置变得递增是容易的。具体的，对于每一个位置 $i$，在最终的序列中的值记为 $t_i$，那么在当前序列中找到一个位置 $x$，使得 $a_x = t_i$。这时候我们就可以将 $x$ 暴力往前跳，需要注意的是当 $x,i$ 奇偶不同时，在最后一步需要操作两次。

若现在最后两个数 $a \leq b$ 则直接合法了，否则只需考虑将最后两个数交换一下。手玩一下 $n = 3$ 的样例，注意到形如 `aba` 的串只需操作一次 $1$ 即可合法。推广到 $n \geq 3$，若最后三位形如 `aba` 则通过操作一次 $n - 2$ 即可。

其次，观察最后一个样例，它出现了形如 `aacb` 的结构，通过操作两次 $1$，两次 $2$ 将串变成了 `aabc`。这启示我们如果能让 `cb` 贴上一个 `aa`，就可以换成 `bc`。

不妨找到一个 $id$ 使得 $a_{id - 1} = a_{id}$，若找不到一定无解。我们只需将最后两个数移动到 $id + 1,id + 2$ 的位置上，做一次 `aacb`，然后再移回去。

具体的，你发现若两个点 $x \leq y$ 奇偶性相同，则 $y$ 能通过一直操作达到 $x$；否则，需要调整一下 $y$ 的奇偶再移动。若 $id + 1$ 和 $n - 1$ 奇偶不同，操作两次 $n - 2$，即可将最后两个数分别移到 $n - 2,n - 1$，此时可以直接移动。

若回来的时候奇偶不同，同理操作两次 $id$ 再移动即可。因为前面将 $n - 2$ 个数操作的步数带 $\frac{1}{2}$ 的常数，所以若有解按照上述操作方式一定能在 $n^2$ 次操作中变化成功。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 510;
int n;
int arr[N],tmp[N];
vector<int> ans;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void move(int x){
    ans.push_back(x);
    int a = arr[x],b = arr[x + 1],c = arr[x + 2];
    arr[x] = c; arr[x + 1] = a; arr[x + 2] = b;
}

inline void gopre(int a,int b){
    while (a - 2 >= b) move(a - 2),a -= 2;
    if (a != b) move(b),move(b);
}

inline void gonxt(int a,int b){
    while (a != b) move(a),move(a),a += 2;
}

inline void solve(){
    ans.clear(); n = read();
    for (re int i = 1;i <= n;i++) arr[i] = tmp[i] = read();
    sort(tmp + 1,tmp + n + 1);
    for (re int i = 1;i <= n - 2;i++){
        int id = 0;
        for (re int j = i;j <= n;j++){
            if (arr[j] == tmp[i]){
                id = j; break;
            }
        }
        gopre(id,i);
    }
    if (arr[n - 1] > arr[n]){
        if (arr[n] == arr[n - 2]) move(n - 2);
        else{
            int id = -1;
            for (re int i = 1;i < n;i++){
                if (arr[i] == arr[i + 1]) id = i + 2;
            }
            if (!~id) return puts("-1"),void();
            int a = n - 1,b = n;
            if ((n - 1) % 2 != id % 2){
                move(n - 2); move(n - 2);
                a = n - 2; b = n - 1;
            }
            gopre(a,id); gopre(b,id + 1);
            move(id - 2); move(id - 2);
            move(id - 1); move(id - 1);
            if ((n - 1) % 2 == id % 2){
                gonxt(id + 1,n); gonxt(id,n - 1);
            }
            else{
                move(id - 1); move(id - 1);
                gonxt(id,n); gonxt(id - 1,n - 1);
            }
        }
    }
    if (ans.size() > n * n) puts("-1");
    else{
        printf("%d\n",ans.size());
        for (int x:ans) printf("%d ",x); puts("");
    }
}

int main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
很好玩的题。

摘自[交互、构造、博弈](https://www.luogu.com.cn/training/676672)。

关联题目 [P3516](https://www.luogu.com.cn/problem/P3516)。
## 思路分析
我们考虑这个循环位移会产生什么影响。

其实总共只有三种可能性嘛，也就是 $a,b,c/c,a,b/b,c,a$。

注意到 $a,b,c$ 到 $c,a,b$ 可以将 $c$ 这个数前移两位。

那么我们可以先通过这样的操作不断前移，将 $i$ 这个数移动到 $i+1$ 或者 $i$ 位置。

如果已经到 $i$ 了就不用管了。

如果目前是在 $i+1$ 的话，我们考虑怎样搓出一个前移 $1$ 位且不影响更前面的数的方法。

那么假设目前是 $a,i,b$ 的话，就直接移动成 $i,b,a$ 就好了。

这里我们发现对后面会产生一个影响：$a,b$ 的相对顺序变了。

并且这样操作的限制在于 $i$ 后面必须还有一个 $b$。

所以最后可能会变成 $1,2,3,\dots,n,n-1$ 的情况。

考虑这种情况能不能微操调回来。

我们发现不管怎么样，翻转一对数必然是伴随着另一对数的翻转的。

证明而言从逆序对角度考虑，操作带来的逆序对变化数总是偶数，所以总是成双成对的变化。

那么这个判断就非常简单了，存在相同的数就是可以，否则就是不行。

这里给出一个比较无脑的写法，考虑到前面翻转一次会导致后面也翻转一次，所以我们在前面找到相同数字的时候就先翻转一下，自然就可以把贡献传递到这个时候了。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=5e5+10,M=5e3+10,V=5e5,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,a[N],b[N],c[N],d[N];vector<int>ans;
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='#'||c=='.'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline void get(int c[])
{
	for(int i=1;i<=n-2;i++)
	{
		int j=1;for(;c[j]!=i;j++);if(i==j) continue;
		while(j-i>1) j-=2,ans.emplace_back(j);
		if(j==i)
		{
			for(j=1;j<=i;j++) d[j]=j;int tot=i;
			for(j=i;j<=n;j++) if(c[j]>i) d[++tot]=c[j];
			for(j=1;j<=n;j++) c[j]=d[j];continue;
		}int tot=i,x=0,y=0;ans.emplace_back(j-1),ans.emplace_back(j-1);
		for(j=1;j<=n;j++)
			if(c[j]>i&&!x) x=c[j];
			else if(c[j]>i&&!y) y=c[j];
		for(j=1;j<=i;j++) d[j]=j;d[++tot]=y;d[++tot]=x;
		for(j=1;j<=n;j++) if(c[j]>i&&c[j]!=x&&c[j]!=y) d[++tot]=c[j];
		for(j=1;j<=n;j++) c[j]=d[j];
	}
}
inline void solve()
{
	n=read();for(int i=1;i<=n;i++) b[i]=a[i]=read();sort(b+1,b+1+n);ans.clear();
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(a[i]==b[j]){c[i]=j,b[j]=INF;break;}
	for(int i=1;i<=n;i++) b[i]=c[i];get(c);
	if(c[n]==n)
	{
		print(ans.size());put('\n');
		for(auto x:ans) print(x),put(' ');put('\n');
		return;
	}ans.clear();
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(i!=j&&a[i]==a[j]){swap(b[i],b[j]);goto play;}
	return put("-1\n");play:;get(b);
	if(b[n]==n)
	{
		print(ans.size());put('\n');
		for(auto x:ans) print(x),put(' ');put('\n');
		return;
	}put("-1\n");
}
signed main()
{
	int T=1;
	T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：Democlight (赞：0)

注意到对 $i$ 进行两次操作会将 $a_{i+1}, a_{i+2}$ 向左移动一位。

所以有一个不成熟的想法，考虑冒泡排序， 每次寻找排名为 $i$ 的数，向左如此移动到第 $i$ 位。

但这么干有时候会出现最后序列形如 [$1,2,3,5,4$] 的情况。

观察到，如果一个序列每个数的排名是确定的，那么无论怎么操作，最终序列都是这样的。

所以问题在于处理值相同的数的排名。

因为我不会处理，所以我选择随机交换排名。

复杂度 $ O(kn^2) $ 

正确率 （ $ 1-2^{-k} $） 其中 $ k $ 为随机次数。

代码见下。

```cpp
#include<bits/stdc++.h>
#define Democlight signed main()
#define int long long
#define maxn 2005
#define maxe 5005
using namespace std;
inline int read(){int ret=0,f=1;char ch=getchar();for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-f;for(;isdigit(ch);ch=getchar())ret=(ret<<3)+(ret<<1)+(ch&15);return ret*f;}
int ans[maxn * maxn ],cnt,c[maxn];
struct AC{
	int x,id;
	bool operator <(const AC &b)const{return x<b.x;}
}a[maxn],b[maxn];
inline void work(int x){
	AC q=a[x+2];ans[++cnt]=x;
	a[x+2]=a[x+1],a[x+1]=a[x],a[x]=q;
}int w;
inline int init(){
	int n=read();srand(time(0));cnt=0;w=0;
	for(int i=1;i<=n;i++)c[i]=b[b[i].id=a[i].id=i].x=a[i].x=read();sort(b+1,b+n+1);loop:cnt=0,w++;for(int i=1;i<n;i++)if(b[i].x==b[i+1].x and rand()&3)swap(b[i],b[i+1]);
	for(int i=1;i<=n;i++)a[b[i].id].id=i,a[i].x=c[i];
	for(register int i=1;i<=n-2;i++){
		for(register int j=i;j<=n;j++){
			if(a[j].id==i){if(j==n)work(j-2),j-=2;
				for(register int k=j-1;k>=i;k--)work(k),work(k);break;
			}
		}
	}
	for(int i=1;i<=n;i++)if(a[i].x^b[i].x){if(w<=100)goto loop;else return puts("-1"),0;}
	printf("%d\n",cnt);for(int i=1;i<=cnt;i++)printf("%d ",ans[i]);putchar('\n');return 0;
}
Democlight{for(int t=read();t--;)init();}

---

## 作者：王熙文 (赞：0)

## 思路

看到这种操作排序的题，可以想到要看逆序对个数。

如果一次循环移位中数互不相同，则逆序对个数奇偶性不变。因此这种题还有一种套路，是对序列中有无重复数字分类讨论。

* 序列中无重复数字：一次操作逆序对个数奇偶性不变，而排序的数组逆序对个数为 $0$，因此当逆序对个数为奇数时一定无解。对于逆序对偶数的情况，我们可以先复原排名为 $n,n-1,\cdots, 3$ 的数。具体操作为，如果当前位置 $i$ 在 $1$，则操作 $1$，否则操作 $i-1$，可以发现这样操作一次一定能前进一个位置且保证了不会影响已经排好的数。那么最后还剩最前面的两个数没有复原，因为逆序对个数个数为偶数，且这个时候逆序对个数一定 $\le 1$，所以这个时候的逆序对个数为 $0$，即已经排好序了。

* 序列中有重复数字：这种情况一定有解。考虑随便拿出来相等且排名相邻的两个数（这里的排名每个数都不同，可以理解为最终每个数所在的位置），此时只需要分别将排名比它小的和排名比它大的复原即可。因为剩下两个数相等，所以复原完一定排好序了。对于复原排名比它小的数，如果当前位置 $i$ 在相等且排名相邻的两个数的左边一个位置，则操作两次 $i-2$，否则操作两次 $i-1$。对于复原排名比它大的数，按照无重复数字的方法操作即可。

这种操作方法操作次数一定小于等于 $n^2$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n; int a[510];
bool vis[510];
pair<int,int> px[510];
int rk[510];
int tot,ans[250010];
void oper(int wz)
{
	ans[++tot]=wz;
	int a1=a[wz],a2=a[wz+1],a3=a[wz+2];
	int r1=rk[wz],r2=rk[wz+1],r3=rk[wz+2];
	a[wz]=a3,a[wz+1]=a1,a[wz+2]=a2;
	rk[wz]=r3,rk[wz+1]=r1,rk[wz+2]=r2;
}
int main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n;
		memset(vis,0,sizeof(vis)); bool flag=0;
		for(int i=1; i<=n; ++i) cin>>a[i],flag|=vis[a[i]],vis[a[i]]=1,px[i]={a[i],i};
		sort(px+1,px+n+1);
		for(int i=1; i<=n; ++i) rk[px[i].second]=i;
		tot=0;
		if(!flag)
		{
			for(int i=n; i>=3; --i)
			{
				int wz;
				for(int j=1; j<=i; ++j)
				{
					if(rk[j]==i) { wz=j; break; }
				}
				if(wz==1) oper(wz),++wz;
				for(int j=wz; j<=i-1; ++j) oper(j-1);
			}
			if(a[1]>a[2]) cout<<-1<<'\n';
			else
			{
				cout<<tot<<'\n';
				for(int i=1; i<=tot; ++i) cout<<ans[i]<<' ';
				cout<<'\n';
			}
		}
		else
		{
			int gt;
			for(int i=1; i<=n-1; ++i)
			{
				if(px[i].first==px[i+1].first) { gt=i; break; }
			}
			for(int i=n; i>=gt+2; --i)
			{
				int wz;
				for(int j=1; j<=i; ++j)
				{
					if(rk[j]==i) { wz=j; break; }
				}
				if(wz==1) oper(wz),++wz;
				for(int j=wz; j<=i-1; ++j) oper(j-1);
			}
			memset(vis,0,sizeof(vis));
			for(int i=1; i<=gt-1; ++i)
			{
				int wz;
				for(int j=i; j<=gt+1; ++j)
				{
					if(rk[j]==i) { wz=j; break; }
				}
				if(wz==gt+1) oper(wz-2),oper(wz-2),--wz;
				for(int j=wz; j>=i+1; --j) oper(j-1),oper(j-1); 
				assert(rk[i]==i);
			}
			cout<<tot<<'\n';
			for(int i=1; i<=tot; ++i) cout<<ans[i]<<' ';
			cout<<'\n';
		}
	}
	return 0;
}
```

---

