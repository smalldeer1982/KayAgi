# [POI 2021/2022 R1] Impreza krasnali

## 题目背景

译自 [XXIX Olimpiada Informatyczna – I etap](https://sio2.mimuw.edu.pl/c/oi29-1/dashboard/) [Impreza krasnali](https://sio2.mimuw.edu.pl/c/oi29-1/p/imp/)。

## 题目描述

有 $n$ 个人依次站成一排，每个人手上都有一个数字，这 $n$ 个数字形成一个排列。

每个人会二选一地报告他左边或右边的人手上的数字。注意第一个人与第 $n$ 个人并不相邻，所以第一个人总是会报告第二个人的数字，第 $n$ 个人总是会报告第 $n-1$ 个人的数字。

现在你得到了 $n$ 个人报告的数字，求出原先的排列有多少种可能。

## 说明/提示

对于所有数据，$2\leq n\leq 100000$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $n\leq 10$ | 12 |
| 2 | $n\leq 20$ | 30 |
| 3 | $n\leq 1000$ | 30 |
| 4 |  | 28 |

## 样例 #1

### 输入

```
5
3 4 3 4 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
见附件```

### 输出

```
0```

## 样例 #3

### 输入

```
见附件```

### 输出

```
1```

# 题解

## 作者：船酱魔王 (赞：6)

## 题意回顾

给定一个长度为 $ n $ 的序列 $ p $，你需要找出有多少个排列 $ a $ 满足 $ \forall 1 \le i \le n $，有 $ p_i = a_{i-1} $ 或 $ p_i=a_{i+1} $。

## 分析

当一个数字出现三次及以上或出现两次且两次位置差不为 $ 2 $ 时，无解。

在把出现两次的位置确定好后，我们考虑把每个仅出现一次的 $ p_i $ 分配给 $ a_{i-1} $ 或 $ a_{i+1} $，因为每个位置仅出现最多一次无重复且影响范围很小所以考虑设计动态规划。

定义 $ dp_{i,0/1,0/1} $ 表示对于位置 $ i $ 及之前所有出现一次的 $ p_i $ 都被分配完后，$ a_i $ 和 $ a_{i+1} $ 是否分配了值。我们分类讨论该位置是否属于出现两次的位置和该位置是否还可以被分配进行转移即可。

最后我们要把空位置填上所有未在 $ p_i $ 中出现过的值，乘上全排列即可。

时间复杂度 $ O(n) $，分类讨论详见代码。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5 + 5;
const int mod = 1e9 + 7;
int n;
int a[N];
int buc[N];
int typ[N], dne[N];
int dp[N][2][2];
int main() {
    scanf("%d", &n);
    bool ok = true;
    int o = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if(buc[a[i]] == 0) buc[a[i]] = i;
        else if(buc[a[i]] > 0) {
            if(buc[a[i]] != i - 2) ok = false;
            buc[a[i]] = -1;
            o++, dne[i - 1] = 1, typ[i - 2] = typ[i] = 1;
        } else ok = false;
    }
    if(!ok) {
        puts("0");
        return 0;
    }
    //for(int i = 1; i <= n; i++) cout << dne[i] << typ[i] << endl;
    dp[1][0][1] = 1;
    for(int i = 2; i <= n; i++) {
        if(typ[i]) {
            dp[i][1][dne[i + 1]] = (dp[i - 1][0][1] + dp[i - 1][1][1]) % mod;
            if(!dne[i]) dp[i][0][dne[i + 1]] = (dp[i - 1][0][0] + dp[i - 1][1][0]) % mod;
        } else {
            if(!dne[i]) dp[i][0][0] = dp[i - 1][0][0], dp[i][0][1] = (dp[i - 1][1][0] + dp[i - 1][0][0]) % mod,
                dp[i][1][0] = dp[i - 1][0][1], dp[i][1][1] = (dp[i - 1][1][1] + dp[i - 1][0][1]) % mod;
            else dp[i][1][0] = dp[i - 1][0][1], dp[i][1][1] = (dp[i - 1][0][1] + dp[i - 1][1][1]) % mod;
        }
        //cout << i << " " << dp[i][0][0] << " " << dp[i][0][1] << " " << dp[i][1][0] << " " << dp[i][1][1] << endl;
    }
    int ans = (dp[n][1][0] + dp[n][0][0]) % mod;
    for(int i = 1; i <= o; i++) ans = (long long)ans * i % mod;
    printf("%d\n", ans);
    return 0;
}

```

---

## 作者：ran_qwq (赞：1)

如果一种数出现大于两次，显然无解。

如果一种数出现两次，且两个位置不隔一个数，显然无解。否则我们可以确定中间那个数。

如果一种数出现一次，我们把它转化为图论问题，如果数 $i$ 可以第 $j$ 个人，那么 $i$ 向 $n+j$ 连边，建出这么一个二分图。那么如果左边的数没被钦定，就向左边连边，右边同理。

对于一个连通块，根据 Hall 定理，如果左部点数大于右部点数，无解。如果左部点数小于右部点数，连通块内匹配方案有右部点数种（空出一个右部点）。如果左部点数小于右部点数，连通块内匹配方案有 $1$ 种。因为根据连边的性质，一个连通块总是形如这样，左部点个数和右部点个数之差 $\le1$，读者不妨手玩一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/bp9mipov.png)

如果一种数不出现，它的位置不受任何限制，如果有 $c$ 种这样的数，有 $c!$ 种方案。

```cpp
int n,id,as=1,c,c1,c2,a[N],b[N],hd[N],vs[N],fc[N],pw[N]; vi t[N];
struct EDGE {int to,ne;} e[N*4];
il void add(int u,int v) {e[++id]={v,hd[u]},hd[u]=id;}
void dfs(int u) {
	vs[u]=1;
	if(u<=n) c1++; else c2++;
	for(int i=hd[u],v;i;i=e[i].ne) if(!vs[v=e[i].to]) dfs(v);
}
void QwQ() {
	n=rd();
	for(int i=1;i<=n;i++) a[i]=rd();
	for(int i=1;i<=n;i++) t[a[i]].pb(i);
	for(int i=1;i<=n;i++) if(t[i].size()>=3) return wr(0,"\n");
	for(int i=1;i<=n;i++) if(t[i].size()==2)
		if(t[i][0]!=t[i][1]-2) return wr(0,"\n");
		else b[t[i][0]+1]=i;
	for(int i=1;i<=n;i++) if(t[i].size()==1) {
		int j=t[i][0];
		if(j>1&&!b[j-1]) add(j,j+n-1),add(j+n-1,j);
		if(j<n&&!b[j+1]) add(j,j+n+1),add(j+n+1,j);
	}
	for(int i=1;i<=n;i++) if(t[a[i]].size()==1&&!vs[i]) {
		c1=c2=0,dfs(i);
		if(c1>c2) return wr(0,"\n");
		if(c1<c2) cmul(as,c2);
	}
	for(int i=1;i<=n;i++) if(!t[i].size()) cmul(as,++c);
	wr(as,"\n");
}
```

---

## 作者：CYZZ (赞：1)

设原排列为 $a$，题目给出的排列为 $b$。

如果 $b$ 中有出现次数大于 $2$ 的相同数，或者相同数之间距离 $\neq 2$，直接无解。

发现 $b_{odd}$ 只和 $a_{even}$ 有关；$b_{even}$ 只和 $a_{odd}$ 有关。看成两个等价问题。

什么时候会产生确定某个 $a_i$？

1. $a_2=b_1,a_{n-1}=b_n$。这个条件还会产生一些“连锁反应”。
2. $b_i=b_{i+2}$，此时 $a_{i+1}=b_i=b_{i+2}$。

我们把**被上面两种情况确定的位置**称为**确定元**。

不难发现确定元把序列分割成了若干个 `W` 字形，设它们的数量为 $cnt$。

每个 `W` 字形会且仅会产生一个**自由元**。自由元在 `W` 字形内有 $len+1$ 种放法，自由元之间有 $cnt!$ 种放法。

综上，答案为 $\prod (len+1) \cdot cnt!$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define eb emplace_back
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define N 100005
#define mod 1000000007
int n,h[N];
int t[N],pre[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&h[i]);t[h[i]]++;
		if(t[h[i]]>2) return printf("0"),0;
		if(pre[h[i]]) if(i-pre[h[i]]!=2) return printf("0"),0;
		pre[h[i]]=i;
	}
	int ans1=1,cnt2=0;
	if(n&1)
	{
		int lst=0;
		for(int i=1;i<=n-2;i+=2)
		{
			if(h[i]==h[i+2])
			{
				if(lst)
				{
					ans1=1ll*ans1*((i-lst)/2-1)%mod;
					cnt2++;
				}
				lst=i;
			}
		}
		if(!lst) return printf("0"),0;
		lst=-2;
		for(int i=2;i<=n-3;i+=2)
		{
			if(h[i]==h[i+2])
			{
				ans1=1ll*ans1*((i-lst)/2-1)%mod;
				cnt2++;
				lst=i;
			}
		}
		ans1=1ll*ans1*((n+1-lst)/2-1)%mod;
		cnt2++;
	}
	else
	{
		int lst=0;
		for(int i=1;i<=n-3;i+=2)
		{
			if(h[i]==h[i+2])
			{
				if(lst)
				{
					ans1=1ll*ans1*((i-lst)/2-1)%mod;
					cnt2++;
				}
				lst=i;
			}
		}
		if(lst)
		{
			ans1=1ll*ans1*((n+1-lst)/2-1)%mod;
			cnt2++;
		}
		lst=-2;
		for(int i=2;i<=n-2;i+=2)
		{
			if(h[i]==h[i+2])
			{
				ans1=1ll*ans1*((i-lst)/2-1)%mod;
				cnt2++;
				lst=i;
			}
		}
	}
	for(int i=1;i<=cnt2;i++)
		ans1=1ll*ans1*i%mod;
	printf("%d",ans1);
}
```

---

## 作者：iBaeJuhyun (赞：1)

显然这是一道数学题；

### 首先考虑不存在，即答案为 $0$ 的情况：
由于数字为 $1$ 到 $n$ 的排列
1. 当一个数字被第 $i$ 个人重复提到时，若未被 $i-2$ 个人提到，则必不能满足条件；
1. 当一个数被提到三次及以上时；
1. 从不同方向开始确定数时，一个位置上的数有多种可能；

### 同时在判断有解过程中我们可以顺便确定所有可确定的数：
剩下的看代码注释吧


------------
code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9+7;
int a[100005],vis[100005],sure[100005];
inline int fac(int x)
{
	int res=1;
	if(!x) return 1;
	for(int i=1; i<=x; i++)
	{
		res=res*i%mod;
	}
	return res;
}
inline int read()
{
	#define ppp c=getchar()
	char ppp;
	int x=0,b=1;
	while(c<'0'||c>'9')
	{
		if(c=='-') b=-1;
		ppp;
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+(c^48);
		ppp;
	}
	return x*b;
}
inline void write(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x / 10);
	putchar(x%10+'0');
}
signed main(void)
{
	int n=read();
	a[1]=read(),a[2]=read();
	vis[a[1]]=1,vis[a[2]]=1;
	sure[2]=a[1];//第二个数必然是被第一个提到的；
	for(int i=3; i<=n; i++)
	{
		a[i]=read();
		vis[a[i]]++;//被提到的次数;
		if(vis[a[i]]!=1&&(a[i-2]!=a[i]||vis[a[i]]>2)) cout<<0,exit(0);//无解的1,2种情况
		if(a[i]==a[i-2]) sure[i-1]=a[i];//两个相同的被提到的数可以确定中间的数；
		if(sure[i-1]&&sure[i-1]!=a[i])//如果上一个数已被确定，且与当前提到数不相同
		{
			if(i==n) cout<<0,exit(0);//如果第n个人提到的不是第n-1个数则判错 
			sure[i+1]=a[i];//提到的不是上一个数，则必然为下一个数；
		}
		if(i==n) sure[i-1]=a[i];//第n-1个数必然为第n个人提到的数；
	}
	for(int i=n-2; i>=2; i--)//重新倒着确定一遍，第n-1个数的确定会导致前面的变化；
	{
		if(sure[i+1]&&sure[i+1]!=a[i])
		{
			if(sure[i-1]&&sure[i-1]!=a[i]) cout<<0,exit(0);
			sure[i-1]=a[i];
		}
	}
//设无法确定的数为X,
//则当形如 X1X2X 的情况出现时 ，1与2的排布有三种；
//1X2   12X   X12   
//X1X2X3X的排列方式有4种；
//123X  12X3  1X23  X123
//方式是等同于X的个数的
//这是因为每一个位置的X被设定为其余数时剩余的数位置就被固定了
//若存在k个这样的结构，则有k个位置仍未被确定，可能的排列数A(k,k)即为 k!;
	int ans=1,mm=0;
	for(int i=1; i<=n; i++)
	{
		if(!sure[i])
		{
			mm++;
			int t=1,j=i;//mm即为以上结构个数
			while(j+=2)
			{
				if(!sure[j]&&j<=n) t++,sure[j]=1;
				else
				{
					ans*=t;
					ans%=mod;
					break;
				}
			}
		}
	}
	cout<<fac(mm)*ans%mod;
	return 0;
}

```



---

## 作者：chaeminter2467 (赞：0)

### 前言

模拟赛T1，正解是DP但是很显然本蒟蒻不会，所以搞了个神秘做法。

### 题意

有一个 $1 \sim n$ 的排列 $P$。现在给定一个长度为 $n$，值域为 $[1,n]$ 的序列 $A$，其中 $A_i$ 表示 $P_{i-1}$ 或 $P_{i+1}$ 为 $A_i$。

特别的，$P_2$ 总是等于 $A_i$，$P_{n-1}$ 总是等于 $A_n$。

问你有多少个 $P$ 满足 $A$ 对其的限制，对 $10^9+7$ 取模。

$1 \le n \le 10^5$

### 题解

先判断掉一些不合法的情况：

- 某个数在 $A$ 之中的出现次数 $> 2$。
- 两个相同的数的间隔 $\not = 2$。
- $\forall i \in [1,n],P_i=i$，且 $n$ 为奇数。

现在来依次看看这些不合法的情况。

第一种情况很显然，直接讨论第二种。

如果有两个相同的数 $P_{i-1}$ 和 $P_{i+1}$，我们就可以确定 $A_i=P_{i-1}$。

反之不合法。

对于第三种，因为我们可以结合已经确定的 $A_2$ 和 $A_{n-1}$ 来进一步确定中间的 $A_i$，如果 $n$ 是奇数的话，拓展到中间时就会矛盾。

举个例子

```
P: 1 2 3 4 5
A: ? 1 ? 5 ?
```

我们发现对于 $P_3=3$ 来说，既没有 $A_2=3$，也没有 $A_4=3$。所以矛盾了。

在这个手摸的过程中我们还发现如果 $P_i=i$ 且 $n$ 为偶数时有且仅有一种排列满足。

我们先将可以确定的数确定下来。因为每一次确定的数都可能对前/后的数有影响，所以我们没有办法通过顺序扫一遍完成这个操作。

我这里是使用了两个指针 $l,r$ ，不断往前推来进行互相更新。

现在我们再来思考怎么样计算答案。

这里给出一组样例：

```
10
3 1 3 4 9 8 10 6 2 6
```

在这个样例中，能确定的数如下

```
? 3 ? ? ? ? ? ? 6 ?
```

把这两个序列结合起来看，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/hguxsv3d.png)

一个数箭头指向的两个位置指的是这两个位置中一定要有一个位置的值和它相等。

观察发现，红色箭头与蓝色箭头是相互独立的，所以我们可以分开考虑。

单独拎出来的话长这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/maiv1cxx.png)

假设另外加入的数为 `x`，情况如下

> 加入的 `x`，指在 $A$ 中没有出现过的数，即没有限制。

```
x 1 4 8
1 x 4 8
1 4 x 8
1 4 8 x
```

实际上就是把 `x` 插入每两个数之间。假设这段 $0$ 有 $tot$ 个，就会有 $tot$ 种方案。 

分别单/偶数下标遍历一遍找到每一个 $tot$ 即可。

根据乘法原理，每一段 $0$ 之间不互相影响，需要乘起来。

又因为我们要给每一段 $0$ 分配一个 `x`，假设有 $cnt$ 个数没有出现过，分配的方案即为 $cnt!$。

答案为
$$
cnt! \prod tot
$$
时间复杂度 $\mathcal{O}(n)$。

~~talk is cheap,show me the code!~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define debug(x)	cerr<<"in "<<x<<"!!!\n";
const int N=1e5+5,mod=1e9+7;
int n;
int h[N],a[N];
bool used[N];
int bk[N]; 
int ans=1;
bool deal(int x){//推导能确定的 A_i。
	if(a[x-1]&&a[x+1]&&a[x-1]!=h[x]&&a[x+1]!=h[x])	return 1;
	if(a[x-1]||a[x+1]){
		if(a[x-1]&&a[x-1]!=h[x])	a[x+1]=h[x];
		else a[x-1]=h[x];
	}
	return 0;
}
signed main(){
	scanf("%d",&n);
	bool fl=1;
	for(int i=1;i<=n;i++){
		scanf("%d",&h[i]);
		bk[h[i]]++;
		if(bk[h[i]]>2){
			printf("0\n");
			return 0;
		}
		if(h[i]!=i)	fl=0;
	}
	if(fl){//判断 P_i=i 的情况。
		printf("%d\n",!(n&1));
		return 0;
	}
	for(int i=3;i<=n-2;i++){
		if(bk[h[i]]==2){
			if(h[i]!=h[i-2]&&h[i]!=h[i+2]){//判断距离。
				printf("0\n");
				return 0;
			}
		}
	}
	for(int i=2;i<=n-1;i++){
		if(h[i-1]==h[i+1]){//确定那种 P_{i-1} 和 P_{i+1} 都确定的。
			a[i]=h[i-1];
			if(used[a[i]]){
				printf("0\n");
				return 0;
			}
			used[a[i]]=1;
		}
	}
	if((a[2]&&a[2]!=h[1])||(a[n-1]&&a[n-1]!=h[n])){
		printf("0\n");
		return 0;
	}
	a[2]=h[1],a[n-1]=h[n];
	used[a[2]]=used[a[n-1]]=1;
	int l=3,r=n-2;
	while(l<n||r>1){//确定能确定的 A_i。
		while(l<n&&used[h[l]])	l++;
		while(r>1&&used[h[r]])	r--;
		if(l<n&&deal(l)){
			printf("0\n");
			return 0;
		}
		if(r>1&&deal(r)){
			printf("0\n");
			return 0;
		}
		if(l<n) l++;
		if(r>1)	r--;
	}
	int qwq=0;
	for(int i=1;i<=n;i++){
		if(!bk[i])	qwq++;//找出没有出现过的数的个数。
	}
	int tot=0;
	for(int i=1;i<=n;i+=2){//单数下标
		if(!a[i])	tot++;
		else{
			if(tot)	ans=1ll*ans*tot%mod;
			tot=0;
		}
	}
	if(tot)	ans=1ll*ans*tot%mod;
	tot=0;
	for(int i=2;i<=n;i+=2){//偶数下标
		if(!a[i])	tot++;
		else{
			if(tot)	ans=1ll*ans*tot%mod;
			tot=0;
		}
	}
	if(tot)	ans=1ll*ans*tot%mod;
	if(qwq){
		for(int i=1;i<=qwq;i++)	ans=1ll*ans*i%mod;//阶乘
	}
	printf("%d\n",ans);
	return 0;
}
/*//一些样例
10 
3 1 3 4 9 8 10 6 2 6 
*/
/*
5
3 2 3 2 4
*/
```

---

## 作者：_EternalRegrets_ (赞：0)

## P9418 题解

### 题意描述：

>有 $n$ 个人依次站成一排，每个人手上都有一个数字。每个人会二选一地报告他左边或右边的人手上的数字。现在你得到了 $n$ 个人报告的数字，求出原先的排列有多少种可能.

### Solution:

顺序扫一遍，第一个人一定说出的是第二个人的数字。

如果有一个数字出现了大于等于三遍，无解。

如果两个相同数字隔了一个，则中间位置的数字可以确定（隔超过一个则无解）。

如果一个坐标左侧已经有数字确定，且不等于当前坐标的数字，即可确定此坐标右侧的数字。

逆序再扫一遍，判定正序扫描结果是否正确。

根据确定出的数字，计算答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[100005];
int vis[100005];
int found[100005];

const int mod=1e9+7;
signed main(){
	int n; cin>>n;
	
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	
	vis[a[1]]++;
	vis[a[2]]++;
	found[2]=a[1];
	
	for(int i=3;i<=n;i++){
		vis[a[i]]++;
		
		if(vis[a[i]]>2 || (a[i-2]!=a[i] && vis[a[i]]>1)){
			cout<<0;
			return 0;
		}
		
		if(a[i]==a[i-2]){
			found[i-1]=a[i];
		}
		
		if(found[i-1] && found[i-1]!=a[i]){
			if(i==n){
				cout<<0;
				return 0;
			}
			
			found[i+1]=a[i];
		}
		
		if(i==n){
			found[i-1]=a[i];
		}
	}
	
	for(int i=n-2;i>=2;i--){
		if(found[i+1] && found[i+1]!=a[i]){
			if(found[i-1] && found[i-1]!=a[i]){
				cout<<0;
				return 0;
			}
			
			found[i-1]=a[i];
		}
	}
	
	int ans,cnt; ans=1,cnt=0;
	for(int i=1;i<=n;i++){
		if(!found[i]){
			cnt++;
			
			int tmp,x; tmp=1,x=i;
			
			while(x+=2){
				if(!found[x] && x<=n){
					tmp++;
					found[x]=n+1;
				}
				else{
					ans*=tmp;
					ans%=mod;
					break;
				}
			}
		}
	}
	
	for(int i=1;i<=cnt;i++){
		ans*=i;
		ans%=mod;
	}
	
	cout<<ans%mod;
	return 0;
}
```

---

