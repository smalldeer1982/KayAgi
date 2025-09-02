# Omkar and the Meaning of Life

## 题目描述

It turns out that the meaning of life is a permutation $ p_1, p_2, \ldots, p_n $ of the integers $ 1, 2, \ldots, n $ ( $ 2 \leq n \leq 100 $ ). Omkar, having created all life, knows this permutation, and will allow you to figure it out using some queries.

A query consists of an array $ a_1, a_2, \ldots, a_n $ of integers between $ 1 $ and $ n $ . $ a $ is not required to be a permutation. Omkar will first compute the pairwise sum of $ a $ and $ p $ , meaning that he will compute an array $ s $ where $ s_j = p_j + a_j $ for all $ j = 1, 2, \ldots, n $ . Then, he will find the smallest index $ k $ such that $ s_k $ occurs more than once in $ s $ , and answer with $ k $ . If there is no such index $ k $ , then he will answer with $ 0 $ .

You can perform at most $ 2n $ queries. Figure out the meaning of life $ p $ .

## 说明/提示

In the sample, the hidden permutation $ p $ is $ [3, 2, 1, 5, 4] $ . Three queries were made.

The first query is $ a = [4, 4, 2, 3, 2] $ . This yields $ s = [3 + 4, 2 + 4, 1 + 2, 5 + 3, 4 + 2] = [7, 6, 3, 8, 6] $ . $ 6 $ is the only number that appears more than once, and it appears first at index $ 2 $ , making the answer to the query $ 2 $ .

The second query is $ a = [3, 5, 1, 5, 5] $ . This yields $ s = [3 + 3, 2 + 5, 1 + 1, 5 + 5, 4 + 5] = [6, 7, 2, 10, 9] $ . There are no numbers that appear more than once here, so the answer to the query is $ 0 $ .

The third query is $ a = [5, 2, 4, 3, 1] $ . This yields $ s = [3 + 5, 2 + 2, 1 + 4, 5 + 3, 4 + 1] = [8, 4, 5, 8, 5] $ . $ 5 $ and $ 8 $ both occur more than once here. $ 5 $ first appears at index $ 3 $ , while $ 8 $ first appears at index $ 1 $ , and $ 1 < 3 $ , making the answer to the query $ 1 $ .

Note that the sample is only meant to provide an example of how the interaction works; it is not guaranteed that the above queries represent a correct strategy with which to determine the answer.

## 样例 #1

### 输入

```
5

2

0

1```

### 输出

```
? 4 4 2 3 2

? 3 5 1 5 5

? 5 2 4 3 1

! 3 2 1 5 4```

# 题解

## 作者：vectorwyx (赞：4)

为了方便，我们把要猜的序列称为 $a$，用来询问的序列成为 $b$。

次数 $2n$，要求猜出一个序列。这种交互题的思路一般都是先用 $n$ 次操作确定某一位置的值，然后利用这个已确定的值依次确定其他位置的值。

先来解决后半段，假设已知 $a_i=x$，那我们可以令 $b_i=y$，其余位置为 $x$，如果 $y$ 所在位置在 $i$ 之前，就可以通过一次询问得到 $y$ 所在位置。这样我们能用 $n$ 次操作得到 $a_{1\sim i}$ 的值。如果 $i=n$，那就可以通过 $n$ 次操作知道所有位置的值。

现在问题只剩下如何用 $n$ 次操作确定 $a_n$ 的值。考虑利用值域进行排除。先令 $b_n=n,b_{i<n}=1$，询问有解当且仅当 $a_n=1$。无解则继续询问，令 $b_n=n-1$，由于 $a_n\not= 1$ 因此询问有解当且仅当 $a_n=2$，以此类推最多询问 $n$ 次就能确定 $a_n$，那么这题就做完了

代码如下：
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}

int a[105],b[105],n;

int query(){
	putchar('?'),putchar(' ');out(b,1,n);
	cout.flush();
	return read();
}

int main(){
	cin>>n;
	fo(i,1,n-1) b[i]=1;
	fo(i,1,n){
		b[n]=n+1-i;
		int x=query();
		if(x){
			a[n]=i;
			break;
		}
	}if(!a[n]) a[n]=n;
	fo(i,1,n-1) b[i]=a[n];
	fo(i,1,n) if(i!=a[n]){
		b[n]=i;
		int x=query();
		a[x]=i;
	}
	putchar('!'),putchar(' ');out(a,1,n);
	return 0;
}
/*
-------------------------------------------------
*/
```


---

## 作者：pitiless0514 (赞：2)


听说考试之前发题解可以增加 rp 。

这是一个交互题，题目让我们最多交互 $2n$ 次。

每次会告诉我们对于我们询问的序列与实际的序列的和序列中有没有相同的数，如果有就会输出第一个位置，否则就返回 $0$ 。

考虑以 $1$ 个 $2$ ，$n-1$ 个 $1$ 的序列做 $n$ 次交互，这里面当 $2$ 的位置到了最大的值的时候，交互库会返回 $0$ 。

如果不是最大值将会返回一个位置，这个位置和我 $2$ 所在的位置的数有一个为 $1$ 的差。

但是由于返回的值可能是 $2$ 所在的位置，这样不能让每一个位置都有一个关系。

于是将 $1$ 全部变为 $2$ ，$2$ 变为 $1$ 再做 $n$ 次就可以让每一个位置都有一个关系。

最后直接暴力从最大值的位置开始进行求解即可。

交互次数恰好为 $2n$ 次。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200;
int tim, n, vis[N][N], mx, a[N];
signed main () {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  int pos = 1;
  for(int i = 1; i <= n; i++) a[i] = -1;
  while(1) {
    cout << "? ";
    for(int i = 1; i <= n; i++) {
      if(i == pos) {
        cout << 2 << " ";
      }
      else cout << 1 << " ";
    } 
    cout << "\n";
    cout.flush();
    int y;
    cin >> y;
    if(y == 0) a[pos] = n;
    else {
      if(y != pos) {
        vis[pos][y] = 1;
        vis[y][pos] = -1;
      }
    }
    pos++;
    if(pos > n) pos = 1;
    tim++;
    if(tim == n) break;
  }
  tim = 0;
  pos = 1;
  while(1){
    cout << "? ";
    for(int i = 1; i <= n; i++) {
      if(i == pos) {
        cout << 1 << " ";
      }
      else cout << 2 << " ";
    }
    cout << "\n";
    cout.flush();
    int y;
    cin >> y;
    if(y != 0) {
      if(y != pos) {
        vis[pos][y] = -1;
        vis[y][pos] = 1;
      }
    }
    tim++;
    pos++;
    if(tim == n) break;
  }
  while(1) {
    int fl = 0;
    for(int i = 1; i <= n; i++) {
      if(a[i] > 0) {
        for(int j = 1; j <= n; j++) {
          if(a[j] > 0) continue;
          if(vis[i][j] != 0) {
            a[j] = a[i] + vis[i][j];
          }
        }
      }
      else fl++;
    }
    if(fl == 0) {
      cout << "! ";
      for(int i = 1; i <= n; i++) cout << a[i] << " ";
      cout << "\n";
      cout.flush();
      return 0;
    }
  }
  return 0;
}

```

---

## 作者：123zbk (赞：1)

大体思路肯定是先通过 $n$ 次询问求出某一个数的值。因为每次返回的是第一个出现相同数的值，所以我们尽量求最后一个数。

$i$ 从 $n$ 循环到 $2$，每次都输入 $n-1$ 个 $i$ 和 $1$ 个 $1$，当第一个返回的值不是 $0$ 时，可以确定 $p_n=i$。当确定 $p_n$ 之后，每往下循环一次都会确定一个比 $p_n$ 小的数的位置。注意，如果循环结束后 $p_n$ 还没有值，说明 $p_n=1$。

再用剩下的次数结合 $p_n$ 的值询问。此时 $i$ 从 $n-1$ 开始往后循环，输入 $n-1$ 个 $i$ 和 $1$ 个 $n$，每次都能确定一个比 $p_n$ 大的数的位置。这样求能求出所有数。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,op,ok,res[1005],ans;
int main()
{
	cin>>n;
	for(int i=n;i>1;i--)
	{
		cout<<"? ";
		for(int j=1;j<n;j++)
		{
			cout<<i<<" ";
		}
		cout<<1<<endl;
		cin>>op;
		if(ok==1)
		{
			res[op]=res[n]+1-i;
		}
		if(op!=0&&ok==0)
		{
			ok=1;
			res[n]=i;
			res[op]=1;
		}
	}
	if(res[n]==0)
	{
		res[n]=1;
	}
	for(int i=1;i<=n;i++)
	{
		if(res[i]!=0)
		{
			ans++;	
		} 
	}
	for(int i=n-1;i>ans-1;i--)
	{
		cout<<"? ";
		for(int j=1;j<n;j++)
		{
			cout<<i<<" ";
		}
		cout<<n<<endl;
		cin>>op;
		res[op]=res[n]+n-i;
	}
	cout<<"! ";
	for(int i=1;i<=n;i++)
	{
		cout<<res[i]<<" ";
	}
	return 0;	
} 
```

---

## 作者：tttianyu (赞：1)

写一个 $n+1$ 询问的做法吧，还是蛮明显的

因为原数列是排序，所以如果你询问一个都是 $1$ 的数列，那么肯定是不会有相同数字的。如果你把某个位置改成 $2$ 那么你就会发现，返回的数字肯定是比他大 $1$ 的数字的位置，如果返回的是 $0$，代表这一位的数字是 $n$。

显然，询问一个都是 $2$ 的数组，把某一位改成 $1$，返回的显然是比他小 $1$ 数字的位置，同样也能确定 $1$ 的位置，然后使用类似链表的做法确定每一个数字。

需要注意的是，因为他返回的是第一个相同数字的位置，所以我们需要从后往前枚举，保证不会出现返回值是当前位置编号的情况。这样相当于是确定了每一位的大小关系，次数显然是 $n+1$ 次的。

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,lst[110],nxt[110],ans[110];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		lst[i]=nxt[i]=-1;
	int tmp;
	for(int i=n;i;i--)
	{
		int x;
		if(lst[i]==-1)
		{
			printf("? ");
			for(int j=1;j<i;j++)
				printf("2 ");
			printf("1 ");
			for(int j=i+1;j<=n;j++)
				printf("2 ");
			puts("");
			fflush(stdout);
			scanf("%d",&x);
			if(x!=0)
				lst[i]=x,nxt[x]=i;
			else
				lst[i]=0,tmp=i;
		}
		if(nxt[i]==-1)
		{
			printf("? ");
			for(int j=1;j<i;j++)
				printf("1 ");
			printf("2 ");
			for(int j=i+1;j<=n;j++)
				printf("1 ");
			puts("");
			fflush(stdout);
			scanf("%d",&x);
			if(x!=0)
				nxt[i]=x,lst[x]=i;
			else
				nxt[i]=n+1;
		}
	}
	printf("! ");
	int cnt=1;
	while(cnt<=n)
	{
		ans[tmp]=cnt;
		++cnt;tmp=nxt[tmp];	
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	fflush(stdout);
	return 0;
}
```


---

## 作者：Alex_Wei (赞：1)

> ### 1586D. [Omkar and the Meaning of Life](https://codeforces.ml/contest/1586/problem/D)

有趣的交互题。

---

一般遇到这种交互题，如果确定了一个数就很好做了，所以我们尝试**通过 $n$ 个询问固定一个位置的值，再通过 $n$ 个询问确定整个序列**。

前者是非常容易的，因为如果你要确定位置 $i$ 的值，在询问的时候将该位置设为 $n$，那么 $p_i+a_i=p_i+n$。因此从 $1$ 到 $n$ 枚举 $k$，并在其它位置上询问 $a_j=k\ (j\neq i)$。若问了 $n$ 次还没有得到结果，显然 $p_i=n$：若 $p_i\neq n$ 那么在询问 $k=p_i$ 时一定会返回非零值，因为 $p_i\neq n$ 故排列必定有一个位置 $j$ 使得 $p_j=n$，此时 $p_i+n=n+k$ 即 $p_i+a_j=p_j+a_j$。否则，第一次使得到的返回值非零的 $k$ 就是 $p_i$。

注意到交互库返回的是位置的最小值，使得如果确定的位置 $i<n$ 那么较难判断出 $i$ 后面的数，所以我们就确定 $p_n$。

现在 $p_n$ 已经求出，接下来确定整个序列变得轻而易举了：如果我们要知道数 $i$ 落在哪个位置上，只需询问 $p_n,p_n,\cdots,p_n,i$，返回值即数字 $i$ 的下标，正确性显然。 

询问刚好 $2n$ 次，精细实现可以做到 $2n-2$ 次。CF 上有位老哥给出了 $n$ 次的做法，比较清晰易懂，这里就不赘述了。

```cpp
const int N=105;
int n,ans[N];
int main(){
	cin>>n,ans[n]=-1;
	for(int i=1,r;i<=n&&ans[n]==-1;i++){
		cout<<"? ";
		for(int j=1;j<n;j++)cout<<i<<" ";
		cout<<n<<endl;
		cin>>r; if(r)ans[n]=i;
	}
	if(ans[n]==-1)ans[n]=n;
	for(int i=1,r;i<=n;i++){
		cout<<"? ";
		for(int j=1;j<n;j++)cout<<n+1-i<<" ";
		cout<<n+1-ans[n]<<endl;
		cin>>r; if(r)ans[r]=i;
	}
	cout<<"! ";
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

提供一种严格 $ n $ 次询问的做法，优于题解区目前最优的 $ n+1 $ 次询问。

首先不断询问 $ 1,1,1,...,k(k=2,3,...) $，直到回答为 $ 0 $ 为止。想象如果前面 $ n-1 $ 位是一个完整的排列则它们会覆盖 $ [2,n+1] $ 之间所有数字，但是缺失了一个数字，相当于出现了一个空洞，那么如果某一次询问为 $ 0 $ 代表这次询问恰好补上这个空洞，然后可以发现所有比 $ p_n $ 大的数字在 $ p_n $ 填上空洞之前都至少和 $ p_n $ 匹配过一次（因为它们之间不可能匹配，排列 $ +1 $ 之后元素仍然互不相同），于是我们得到 $ p_n=n-i+1 $ 之后可以反推出比它大的所有数，具体地，设第 $ i $ 次询问的答案为 $ ans $，则有 $ p_{ans}=p_n+i $。不难发现上面一共使用了 $ n-p_n+1 $ 次操作。

然后对于已经确定的位置（除了 $ p_n $ 以外），每次询问都将这些位置设置为 $ n $，将 $ p_n $ 位置的询问设置为 $ 1 $，遍历所有 $ k=(2,3,..,p_n) $，将没确定的位置填上 $ k $，则发现所有的元素 $ +k $ 之后仍然不可能超过那些比 $ p_n $ 大的数，只能和 $ p_n $ 相等，于是可以逐次从大到小确定剩下所有的数。具体地，如果第 $ i $ 次询问的答案为 $ ans $，则 $ p_{ans}=p_n-i $。一共使用了 $ p_n-1 $ 次操作，和上面的询问加起来刚好是 $ n $。

上面的做法实际上每次确定了一个数，所以总次数是 $ n $ 次。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[200020],b[200020];
int tot;
void query() 
{
	tot++;
	cout<<"? ";
	for (int i=1;i<=n;i++)
	cout<<a[i]<<' ';
	cout<<endl;
}
void answer() 
{
	cout<<"! ";
	for (int i=1;i<=n;i++)
	cout<<b[i]<<' ';
	cout<<endl;
}
int read() 
{
	int x;
	cin>>x;
	return x;
}
void test() 
{
	if(tot>n)
	    puts("hacked");
}
int main() 
{
	n=read();
	for (int i=1;i<=n;i++)
	a[i]=1;
	for (int i=1;i<=n;i++) 
    {
		a[n]++;
		int tmp=0;
		if(i!=n) 
        {
			query();
			tmp=read();
		} 
        else
		tmp=0;
		if(!tmp) 
        {
			b[n]=n-i+1;
			for (int j=1;j<=n-1;j++)
			if(b[j])
			b[j]+=b[n];
			break;
		} 
        else
		b[tmp]=i;
	}
	a[n]=1;
	for (int i=1;i<=b[n]-1;i++)
     {
		for (int j=1;j<n;j++)
		if(b[j])
		a[j]=n; 
        else
		a[j]=i+1;
		query();
		b[read()]=b[n]-i;
	}
	answer();
	test();
}
```


---

## 作者：_Clown_ (赞：0)

# D.Omkar and the Meaning of Life
这是一道**交互**题。

不难想到一种非常暴力的查询。

对于每一个 $i(1\le i\le n)$，

我们进行两次查询。

先查一次形如 `222212222` 的，其中第 $i$ 位为 `1`。

再查一次形如 `111121111` 的，其中第 $i$ 位为 `2`。

其他细节可以自行处理。

最终我们总共查询了 $2n$ 次，可以通过本题。

应该还有更优的解法，可惜 $\texttt{lz}$ 不会。

代码应该不难写出吧。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,A[101],S[101];
int main(void)
{
	BetterIO;
	register int i,j,X,Y;cin>>N;
	for(i=1;i<=N;i++)
	{
		cout<<"? ";
		for(j=1;j<=N;j++)if(i==j)cout<<1<<' ';
						 else cout<<2<<' ';
		cout<<endl;
		cin>>X;
		if(!X)Y=i;
		if(X!=i&&X)S[X]=i;
		cout<<"? ";
		for(j=1;j<=N;j++)if(i!=j)cout<<1<<' ';
						 else cout<<2<<' ';
		cout<<endl;
		cin>>X;
		if(X!=i&&X)S[i]=X;
	}
	A[Y]=1;
	for(i=1;i<N;i++)A[Y=S[Y]]=i+1;
	cout<<"! ";
	for(i=1;i<=N;i++)cout<<A[i]<<' ';
	cout<<endl;
	return 0;
}
```

---

## 作者：KSToki (赞：0)

# 题目大意
交互题，你需要在 $2n$ 次询问内得出一个长度为 $n$ 的排列 $p$。每次询问给出一个长度为 $n$ 的数组 $a$，$a$ 内的数字范围为 $[1,n]$，交互库会计算出数组 $s$，$s_i=a_i+p_i$，并返回最小的 $k$ 满足 $s_k$ 在 $s$ 中至少出现两次，没有则返回 $0$。
# 题目分析
这个 $n$ 只有 $100$，只要保证了询问次数正确基本可以随便搞了。有询问次数为 $n$ 的做法，这里介绍的是一种简单的 $2n$ 的做法。

首先每个位置可以用两次询问，当前位置 $a$ 为 $1$，其它位置为 $2$，返回为当前位置或者比当前位置数小一的数的位置；当前位置 $a$ 为 $2$，其它位置为 $1$，返回为当前位置或者比当前位置数大一的数的位置。对于每一组 $(x,x+1)$，一定存在先后顺序，那么在尝试查 $x$ 大一的数或 $x+1$ 小一的数时一定有一次没有返回当前位置。

这样通过 $2n$ 次询问可以得知每个位置上比这个位置上大一的位置在哪里，而唯一一个找不到的就是 $n$，首先即可确定 $n$ 的位置。于是从 $n-1$ 开始枚举，暴力找对应大一的数的位置正确的位置，继续进行下去即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n,k,a[101],p[101],pre[101],nxt[101];
int main()
{
	cin>>n;
	For(i,1,n)
	{
		For(j,1,n)
		{
			if(i!=j)
				a[j]=2;
			else
				a[j]=1;
		}
		cout<<"?";
		For(i,1,n)
			cout<<" "<<a[i];
		cout<<endl;
		cin>>k;
		if(k!=i)
			nxt[k]=i;
		For(j,1,n)
		{
			if(i!=j)
				a[j]=1;
			else
				a[j]=2;
		}
		cout<<"?";
		For(i,1,n)
			cout<<" "<<a[i];
		cout<<endl;
		cin>>k;
		if(k!=i)
			nxt[i]=k;
	}
	int lst;
	For(i,1,n)
		if(!nxt[i])
		{
			p[i]=n;
			lst=i;
		}
	Rof(i,n-1,1)
		For(j,1,n)
			if(nxt[j]==lst)
			{
				p[j]=i;
				lst=j;
				break;
			}
	cout<<"!";
	For(i,1,n)
		cout<<" "<<p[i];
	cout<<endl;
	return 0;
}
```

---

