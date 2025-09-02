# Sequence and Swaps

## 题目描述

You are given a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ , and an integer $ x $ . Your task is to make the sequence $ a $ sorted (it is considered sorted if the condition $ a_1 \le a_2 \le a_3 \le \dots \le a_n $ holds).

To make the sequence sorted, you may perform the following operation any number of times you want (possibly zero): choose an integer $ i $ such that $ 1 \le i \le n $ and $ a_i > x $ , and swap the values of $ a_i $ and $ x $ .

For example, if $ a = [0, 2, 3, 5, 4] $ , $ x = 1 $ , the following sequence of operations is possible:

1. choose $ i = 2 $ (it is possible since $ a_2 > x $ ), then $ a = [0, 1, 3, 5, 4] $ , $ x = 2 $ ;
2. choose $ i = 3 $ (it is possible since $ a_3 > x $ ), then $ a = [0, 1, 2, 5, 4] $ , $ x = 3 $ ;
3. choose $ i = 4 $ (it is possible since $ a_4 > x $ ), then $ a = [0, 1, 2, 3, 4] $ , $ x = 5 $ .

Calculate the minimum number of operations you have to perform so that $ a $ becomes sorted, or report that it is impossible.

## 样例 #1

### 输入

```
6
4 1
2 3 5 4
5 6
1 1 3 4 4
1 10
2
2 10
11 9
2 10
12 11
5 18
81 324 218 413 324```

### 输出

```
3
0
0
-1
1
3```

# 题解

## 作者：TEoS (赞：11)

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/14074880.html)


------------


因为要求 $a_i>x$ 才可以交换，而序列要求 $a_{j\in[i+1,n]}\geq a_i$ ，所以如果有 $a_i>x$ 而不交换，那么后面都不能交换了。因此可以直接从前往后扫，遇到 $a_i>x$ 就交换。

但是显然有序的数列是不用处理的，那么我们只需要处理到最后一个乱序的位置即可。可以先遍历一遍序列，找到最后一个乱序的位置，然后就按上面的方法处理，到那个位置就停止。然后再遍历一遍判断是否有序即可，此时若仍然无序则无解。

```c++
#include<iostream>
#include<cstdio>
using namespace std;
const int N=700;
int T,n,x,ans,b;
int a[N];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&x);b=ans=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]<a[i-1])
				b=i;//最后一个乱序的位置
		}
		if(b)
		{
			for(int i=1;i<=b;i++)
				if(x<a[i])
					swap(x,a[i]),ans++;//遍历 [1,b] 并处理
			for(int i=1;i<=n;i++)
				if(a[i]<a[i-1])
					b=0;//仍然乱序
			printf(!b?"-1\n":"%d\n",ans);
		}
		else//有序
			puts("0");
	}
	return 0;
}
```



---

## 作者：_•́へ•́╬_ (赞：6)

### 思路

$DP$。

$f[i][j]$ 表示 把 $a[i]$ 换成了 $j$，那么现在的 $x$ 就被换成原来的 $a[i]$ 了。

$g[i][j]$ 表示 维持 $a[i]$ 不变，现在的 $x$ 是 $j$（可能是之前的某一个值，可能是初始的零）。

默认前面有一个 $a[0]=0$。显然它肯定不用换。

### $code$

注释中【有资格换】指【满足 $a[i]>x$】，【可以换】表示换后【满足 $a[i-1]\leq a[i]$】。

```cpp
#include<stdio.h>
#include<string.h>
#define N 501
#define M 501
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	register char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int t,n,x,a[N],f[N][M]/*换*/,g[N][M]/*不换*/,minn;
inline void min(int&x,const int&y){if(x>y)x=y;}
main()
{
	for(read(t);t--;)
	{
		read(n);read(x);for(register int i=1;i<=n;++i)read(a[i]);
		memset(f,0x3f,sizeof(f));memset(g,0x3f,sizeof(g));
		g[0][x]=0;
		for(register int i=1;i<=n;++i)for(register int j=x;j<M;++j)
		{
			if(j<a[i]/*有资格换*/&&a[i-1]<=j/*可以换*/)//i换，i-1不换
                min(f[i][j],g[i-1][j]+1);//a[i-1]=a[i-1],a[i]=j,x=a[i]
			if(a[i-1]<a[i]/*有资格换*/&&a[i-1]==j/*要保证i-1换后留下的x恰等于j*/)
                //i和i-1都换，要枚举i-1换成什么
                for(register int k=x;k<=j/*可以换*/;++k)min(f[i][j],f[i-1][k]+1);
			    //a[i-1]=k,a[i]=j==a[i-1],x=a[i]
			
			if(a[i-1]<=a[i]/*可以“换”*/)//i和i-1都不换
                min(g[i][j],g[i-1][j]);//a[i-1]=a[i-1],a[i]=a[i],x=j
			if(a[i-1]==j/*要保证i-1换后留下的x恰等于j*/)
                //i不换，i-1换，要枚举i-1换成什么
                for(register int k=x;k<=a[i]/*可以换*/;++k)min(g[i][j],f[i-1][k]);
				//a[i-1]=k,a[i]=a[i],x=j
		}
		minn=0x3f3f3f3f;
		for(register int j=x;j<M;++j)min(minn,f[n][j]),min(minn,g[n][j]);
		if(minn==0x3f3f3f3f)puts("-1");
		else printf("%d\n",minn);
	}
}
/*f[i][j]:把a[i]换成j，现在的x是a[i]
 *g[i][j]:a[i]不变，现在的x是j
 */
```



---

## 作者：Composite_Function (赞：2)

# 题意

你有一个序列 $a _ 1, a _ 2, ..., a _ n$ 和一个整数 $x$。你需要使 $a$ 升序排列（当然初始时也有可能是升序的）。

为了让 $a$ 升序排列，你可以做许多次这样的操作：选择一个整数 $i \in[1, n]$ 且 $a _ i > x$，交换 $a _ i$ 和 $x$。

举个例子，如果 $a = [0, 2, 3, 5, 4], x = 1$，以下的操作是可行的：

1. 令 $i = 2$（其中 $a _ 2 > x$）。这时 $a = [0, 1, 3, 5, 4], x = 2$。

2. 令 $i = 3$（其中 $a _ 3 > x$）。这时 $a = [0, 1, 2, 5, 4], x = 3$。

3. 令 $i = 4$（其中 $a _ 2 > x$）。这时 $a = [0, 1, 2, 3, 4], x = 5$。

你需要说出最少要几次交换才能使 $a$ 变成升序序列。

------------

# 思路

这题看起来毫无头绪。不过，只要从升序序列的特点出发，就能轻松出这题。

升序序列所具备的特点是 $\forall i \leq j~a _ i \leq a _ j$。因此，如果有 $x < a _ i$ 而不进行操作，那么后面都无法进行操作。因此，只要贪心找出每一个 $x < a _ i$ 并进行操作即可。

然而会遇到一个问题，已经有序的序列不需要进行操作。如果进行，反而使操作数更多。于是，可以提前找出无序的一段 $[1, tmp]$，再进行操作就行了，后面 $(tmp, n]$ 就不用进行操作了。

------------

```
# include <bits/stdc++.h>
using namespace std;

# define int long long
const int N = 1010;

int T, n, val[N], x;

signed main()
{
    cin >> T;
    while (T--) {
        int tmp = 0;
        cin >> n >> x;
        for (int i = 1; i <= n; ++i) {
            cin >> val[i];
            if (val[i] < val[i - 1])
                tmp = i; // 找出无序的部分，由于 a[0] 初始是 0，所以不用考虑
        }
        if (tmp == 0) cout << 0 << endl; // 如果有序就不用了
        else {
            int ans = 0;
            bool flag = true;
            for (int i = 1; i <= tmp; ++i)
                if (x < val[i]) {
                    swap(x, val[i]);
                    ++ans;
                }
            for (int i = 1; i <= n; ++i)
                if (val[i] < val[i - 1])
                    flag = false; // 如果还是无序，那么就没办法再继续了
            if (flag == true) cout << ans << endl;
            else cout << -1 << endl;
        }
    }
    return 0;
}
```

---

## 作者：zztqwq (赞：2)

# Codeforces 1455D

## Solution

*Lemma*：若 $a_i>x$ 但二者不交换，则后面的数无法通过交换使序列有序。  

*Prove*：取 $i<j\le n$，假设 $a_i,a_j$ 都能与 $x$ 交换，即 $a_i>x,a_j>x$。  
若 $a_i$ 不交换但 $a_j$ 交换，则交换后的 $a_j'=x<a_i$，这与题目要求的单调不降不符，而且这两个数无法再次还原，所以 $a_i$ 与 $x$ 必须交换。  
$\mathcal{Q.E.D.}$

由 *Lemma*，我们可以扫一遍序列，对于每个 $a_i$，一旦可以与 $x$ 交换就执行操作同时累加次数，若执行过程中序列已经有序，输出答案并直接退出；若序列已经扫描完毕但仍然不是有序的，说明无解，输出 `-1`。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=500;
int a[N+10],n;
bool check()
{
	for(int i=2;i<=n;i++)
		if(a[i]<a[i-1])
			return false;
	return true;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int x;
		scanf("%d %d",&n,&x);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		if(check())
		{
			printf("0\n");
			continue;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]>x)
			{
				swap(a[i],x);
				ans++;
			}
			if(check()) 
			{
				printf("%d\n",ans);
				break;
			}
		}
		if(!check()) printf("-1\n");
	}
	return 0;
}
```



---

## 作者：ykzzldz (赞：1)

题目翻译其实有些问题，序列其实应该是不下降的，不一定要升序。

因为每次交换会将一个较大的数换来，所以考虑先交换前面的，也就是从前往后交换，如果有能换的就直接换。但是，如果你这样写的话会错，原因也比较显然，因为最后一段序列如果是不下降的，那么就没有必要交换了，因为前面一段一定是越换越小的。最后，只要再扫一遍就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x,a[600];
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		int jsq=0,f=0,jl=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]<a[i-1])jl=i;
		}
		if(jl==0){
			cout<<"0\n";
			continue;
		}
		for(int i=1;i<=jl;i++){
			if(a[i]>x)swap(a[i],x),jsq++;
		}
		for(int i=1;i<n;i++){
			if(a[i]>a[i+1]){
				cout<<-1<<'\n';
				f=1;
				break;
			}
		}
		if(f==1)continue;
		cout<<jsq<<'\n';
	}
	return 0;
}
```

---

## 作者：yingkeqian9217 (赞：0)

## 前言

本题对于代码能力要求并不高，就是看你 ~~脑子好不好使~~ 能不能想到。
 
## 题目分析

读题之后，最先注意到的就是 $x$ 与 $a_i$ 的交换，让人首先想到，这是不是有点规律呢？

显然，答案是肯定的，毕竟人家 CF 标着个 1500。

这也不难想到，由于最终目的是单调不递减（即 $a_i\leqslant a_{i+1}$），越前面的数越要小，所以一定换编号最小的，即使得 $a_i>x$ 且 $i$ 为最小的 $i$。

证明也很简单，如果你换非编号最小的（记为 $a_j$），那么一定会有 $a_i>a_j$ 且 $i<j$，即逆序对，这就与我们的初衷不符了。

而接下来代码就很简单了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=10000001;
int T,n,x,a[maxn];
bool judge(){//判断是否达到目标
	for(int i=1;i<n;i++) if(a[i]>a[i+1]) return 0;
	return 1;
}
signed main(){
	scanf("%d",&T);
	while(T--){
		int ans=0;
		bool fl=1;//fl表示是否无解，注意初值不是0哦
		scanf("%d%d",&n,&x);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		while(!judge()){
			if(!fl) break;
			fl=0;
			for(int i=1;i<=n;i++)//简简单单遍历一遍
			 if(a[i]>x){
			 	fl=1;
			 	swap(a[i],x);
			 	break;
			 }
			ans++;
		}
		if(!fl) printf("-1\n");
		else printf("%d\n",ans);
	}
	return 0;//完结撒花
}
```

---

