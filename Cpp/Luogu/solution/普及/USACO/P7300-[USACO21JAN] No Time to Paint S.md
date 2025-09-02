# [USACO21JAN] No Time to Paint S

## 题目描述

Bessie 最近收到了一套颜料，她想要给她的牧草地一端的栅栏上色。栅栏由 $N$ 个 1 米长的小段组成（$1≤N≤10^5$）。Bessie 可以使用 26 种不同的颜色，她将这些颜色由浅到深用字母 'A' 到 'Z' 标号（'A' 是很浅的颜色，'Z' 是很深的颜色）。从而她可以用一个长为 $N$ 且每个字符均为字母的字符串来描述她想要给栅栏的每一小段涂上的颜色。 

初始时，所有栅栏小段均未被上色。Bessie 一笔可以给任意连续若干小段涂上同一种颜色，只要她不会在较深的颜色之上涂上较浅的颜色（她只能用较深的颜色覆盖较浅的颜色）。 

例如，一段长为 4 的未被涂色的栅栏可以按如下方式上色：

`.... -> BBB. -> BBLL -> BQQL`

由于时间紧迫，Bessie 认为她可能需要放弃为栅栏上某个连续的区间上色！现在，她正在考虑 $Q$ 个候选的区间（$1≤Q≤10^5$），每个区间用满足 $1≤a≤b≤N$ 的两个整数 $(a,b)$ 表示，为需要不上色的小段 $a…b$ 的两端点位置。 

对于每个候选区间，将所有区间外的栅栏小段都涂上所希望的颜色，并且区间内的栅栏小段均不涂色，最少需要涂多少笔？注意在这个过程中 Bessie 并没有真正进行任何的涂色，所以对于每个候选区间的回答是独立的。 

## 说明/提示

在这个样例种，除去目标颜色 `BAAB` 所对应的区间，涂上颜色需要四笔，而除去 `ABBA` 仅需三笔。

`.... -> AA.. -> ABBB -> ABCB`

#### 测试点性质：

 - 测试点 1-4 满足 $N,Q≤100$。
 - 测试点 5-7 满足 $N,Q≤5000$。
 - 测试点 8-13 没有额外限制。

供题：Andi Qu，Brian Dean 

## 样例 #1

### 输入

```
8 2
ABBAABCB
3 6
1 4```

### 输出

```
4
3```

# 题解

## 作者：aaki (赞：10)

## 路线图
我们先拿部分分，然后不断优化收敛，得到满分。


## 概要分析

当然是把 $\text{[A,Z]}$ 映射为 $[1,26]$。  
我们可以把这道题抽象成存在很多山峰，字母映射的数字就是山峰的阶梯高度，我们从西坡登上山顶,然后从东坡下山 。  
![](https://cdn.luogu.com.cn/upload/image_hosting/fmgqby4g.png)
- 对于从西坡上山时，每一级楼梯都是上升的，必然存在山谷,因此需要多画一笔。
- 对于下山时,如果楼梯已经在西坡(也就是上山楼梯)出现过,笔画不增加,如果没出现过,笔画增加。
- 下坡时判断是否是当前山峰的西坡的标准是:向西没有遇到过比当前阶梯更低的山谷。
- 位于左边界的楼梯，我们认为是一步上山的。


## 拿到49分
### 分析

对于中间的断层 $[a,b]$ ,我们把数据拆分为 $[1,a-1]$ 和 $[b+1,n]$ 两部分,依次计算画的笔数。

### 详细设计
- 如果是上升的(就是在西坡上),笔数 + 1 。
- 如果是下降的，使用数组 $v$ 判断当前数字在西坡上是否存在。
- 上坡要新增 $v$ 数据,下坡时要把大于当前高度的数据删除。

### 代码实现
```cpp
#include<iostream>
#include<cstring>
using namespace std;
string s;
int ar[100010],n,q,ans,v[30];
int  find(int a,int b){
	memset(v,0,sizeof(v));
	int ans = 0;
	for(int i = a;i<=b;i++){
		if(ar[i] > ar[i-1] || i==a ) ans ++,v[ar[i]] = 1;
		else if(ar[i] < ar[i-1]){
			ans +=(!v[ar[i]]);
			v[ar[i]] = 1;
			for(int j = ar[i] + 1;j<=30;j++) v[j] = 0;
		}
	}
	return ans;
}
void cal(){
	int a,b;
	ans = 0;
	cin >>a>>b;
	if(a>1) ans += find(1,a-1);
	if(b<n) ans += find(b+1,n);
	cout << ans<<endl;
}
int main(){
	cin >> n>>q>>s;
	for(int i = 0;i<n;i++) ar[i+1] = s[i] -'A' +1;
	for(int i  = 1;i<=q;i++)cal();
	return 0;
}
```

### 时间复杂度
$O(n \times q)$

当然了循环次数会达到 $ 10^{10} $ 。

## 拿到满分

### 分析
在每次询问现计算是不可能的,我们要想办法把每次询问的时间复杂度降到和 $n$ 无关的 $O(1)$  。
### 详细设计
自然,我们想到预处理,因为是分为2段$[1,a-1]$ 和 $[b+1,n]$,因为西段是从1开始的,所以用 $f_i$ 记录在第 $i$ 步时的累计笔数,这是没问题的。
问题出在东段,因为起点是不一定的,西坡情况未知,造成 $f$ 缓存全部失效。

我们知道:
对于相同的一段路径 **从西到东走和从东到西走结果是一样的**  。
对于东段终点都是 $n$ (也就是从东到西走的起点)是不变的,我们再次从西到东维护一次记录 $fx$ ($fx$ 起点记为 $n$) 。 
最终的结果就是：  
$f_{a-1} + fx_{b+1}$

### 代码实现

部分代码
```cpp
int find2(int a,int b){
	memset(v,0,sizeof(v));
	int ans = 0;
	for(int i = b;i>=a;i--){
		if( ar[i] > ar[i + 1]|| i==b) ans ++,v[ar[i]] = 1;
		else if(ar[i] < ar[i+1]){
			ans +=(!v[ar[i]]);
			v[ar[i]] = 1;
			for(int j = ar[i] + 1;j<=30;j++) v[j] = 0;
		}
		fx[i] = ans;
	}
	return ans;
}
void cal(){
	int a,b;
	ans = 0;
	cin >>a>>b;
	if(a>1) ans += f[a-1];
	if(b<n) ans += fx[b+1];;
	cout << ans<<endl;
}
```
## 后记
这道题比赛时是翻车了的,误入了分制算法,想用线段树优化的,把时间白白浪费了。没有想到后缀数组的用法(倒序前缀和)  。

要注意全局变量和局部变量尽量不要重名,否则 debug 时就酸爽了。
 

---

## 作者：Skies (赞：5)

### 题面分析

因为每次询问，都会不染其中的一段区间，所以考虑用**前缀、后缀**记录答案。

所以，怎么预处理呢？

我们以前缀为例：

我们用 $ans1(i)$ 来记录$1--i$位需要染多少次色， $v[i]$数组的用来记录之前有没有第 $i$ 个字母

假如当前字符串：$ABAB$

$i=1: v('A')==0,ans(i)++,v('A')=1$(赋值)

$i=2: v('B')==0,ans(i)++,v('B')=1$

$i=3: v('A')==1,ans(i)$不变（可以从上一个'A'哪里延续）

$i=4:$ 这时，我们发现问题，上一个' $B$ '延续不过来，因为中间有个' $A$ '

所以对于每一步，操作过后，都要把**在他后面的字母**对应的 $v$ 清零

```cpp
for(int j=a[i]-'A'+1;j<26;j++)
{
	v[j]=0;
}
```

# code

```cpp
#include<bits/stdc++.h> 。
using namespace std;
const int N=1e5+10;
int ans1[N],ans2[N];
int n,m;
char a[N];
int v[27];
int main()
{
	cin>>n>>m;
	scanf("%s",a+1);
	for(int i=1;i<=n;i++)
	{
		ans1[i]=ans1[i-1];
		if(!v[a[i]-'A'])
		{
			ans1[i]++;
			v[a[i]-'A']=1;
		}
		for(int j=a[i]-'A'+1;j<26;j++)
		{
			v[j]=0;
		}
	}
	memset(v,0,sizeof(v));
	for(int i=n;i>=1;i--)
	{
		ans2[i]=ans2[i+1];
		if(!v[a[i]-'A'])
		{
			ans2[i]++;
			v[a[i]-'A']=1;
		}
		for(int j=a[i]-'A'+1;j<26;j++)
		{
			v[j]=0;
		}
	}
	while(m--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",ans1[l-1]+ans2[r+1]);//输出，注意不能取l,r
	}
}
```





---

## 作者：JiaY19 (赞：4)

## 题意

根据题意，不难看出一个很直观的写法，维护前缀和后缀。

再算一下复杂度，居然是$~O(n)~$的。

显然，可能这就是正解。

## 思路

观察题目染色规则，可以发现这些：

1. 对于一个十分浅的颜色，只要之前有过这个颜色，那么就只需要染一次；

1. 我们可以用一个标记数组，储存之前出现过得颜色，接着就是维护这个数组；

1. 根据一，就有一个显而易见的结论，只要遍历到了一个颜色，那么，所有比它深的颜色的标记，就要全部删除，这里大家可以感性理解一下；

1. 想完了这几点，就可以直接来两次遍历，一次维护前缀，一次维护后缀。

## Code

```
#include<bits/stdc++.h>
using namespace std;
int n , q , l , r , v[30] , f[100010] , f2[100010];
char a[100010];
int main()
{
	cin >> n >> q >> (a + 1);
	for(int i = 1;i <= n;i++)
	{
		f[i] = f[i - 1];
		for(int j = a[i] - 'A' + 1;j < 26;j++) v[j] = 0;
		if(v[a[i] - 'A'] == 0) v[a[i] - 'A'] = 1 , f[i] += 1;
	}
	memset(v , 0 , sizeof(v));
	for(int i = n;i >= 1;i--)
	{
		f2[i] = f2[i + 1];
		for(int j = a[i] - 'A' + 1;j < 26;j++) v[j] = 0;
		if(v[a[i] - 'A'] == 0) v[a[i] - 'A'] = 1 , f2[i] += 1;
	}
	for(int i = 1;i <= q;i++)
	{
		cin >> l >> r;
		cout << f[l - 1] + f2[r + 1] << endl;
	}
	return 0;
}

```
完结撒花！！！

---

## 作者：henrytb (赞：4)

我们可以先 dp 求出前缀的答案和后缀的答案。

具体可以开一个桶 $vis$，转移的时候分两种情况讨论即可。

对于前缀，我们可以这么转移：

$$pre_i=\left\{\begin{matrix}
f_i=f_{i-1}+1 & s_i>s_{i-1}\\ 
f_i=f_{i-1}+(\neg\ vis_{s_i}) & s_i\le s_{i-1}
\end{matrix}\right.$$

如果 $s_i>s_{i-1}$，应将 $vis_{s_i}$ 赋值为 $1$，因为之后如果没有降到这个地方以下的话相同颜色是可以一笔画的。

另外如果 $s_i\le s_{i-1}$，那么应赋值 $vis_{s_i+1}\sim vis_{s_{i-1}}=0,\ vis_{s_i}=1$。具体可以配合下图理解：

![](https://i.loli.net/2021/01/28/DeQ1MdFES3rbciY.png)

其中红色和绿色部分不能一笔画。

后缀同理。具体详见代码。

然后对一个挖掉的区间 $[l,r]$，答案就是 $pre_{l-1}+suf_{r+1}$。

详见代码：

```cpp
rep(i,1,n) {
    if(s[i]>s[i-1]) f[i]=f[i-1]+1,vis[s[i]-'A']=1;
    else {
        f[i]=f[i-1]+(!vis[s[i]-'A']);
        per(j,s[i-1]-'A',s[i]-'A'+1) vis[j]=0;
        vis[s[i]-'A']=1;
    }
}
rep(i,0,25) vis[i]=0;
per(i,n,1) {
    if(s[i]>s[i+1]) g[i]=g[i+1]+1,vis[s[i]-'A']=1;
    else {
        g[i]=g[i+1]+(!vis[s[i]-'A']);
        per(j,s[i+1]-'A',s[i]-'A'+1) vis[j]=0;
        vis[s[i]-'A']=1;
    }
}
rep(i,1,q) {
    int l,r;
    scanf("%d%d",&l,&r);
    printf("%d\n",f[l-1]+g[r+1]);
}
```

---

## 作者：Aiopr_2378 (赞：2)

# Solution[USACO21JAN] No Time to Paint S

这题是说给你一个由 $26$ 个大写字母组成的字符串，$26$ 个字母分别要用 $26$ 种颜色的颜料染色，从 ‘$A$’ 到 ‘$Z$’，颜色逐渐由浅到深。**并且深颜色的颜料可以覆盖浅颜色的。**同时你可以一次对一个连续区间涂上相同的颜色。

问你将给定的字符串去掉一个区间之后其他的都涂成对应的颜色，**最少**需要涂多少次。

我的想法是想先去遍历一遍当前的字符串，然后去遍历当前节点的后面的节点，看看是否由有和当前节点颜色一样的节点，有的话就标记后面的节点可以由当前节点染色，遇到一个比当前节点字母**小**的就结束。

```cpp
for(int i=1;i<n;i++){
	if(biao[i]) continue;
	for(int j=i+1;j<=n;j++){
		if(s[j]<s[i]) break;
		if(s[j]==s[i]){
			biao[j]=i;
		}
	}
} 
```

然后去记录一个**前缀和**，去记录从第一个节点开始，到当前节点最少需要染多少次

```cpp
for(int i=1;i<=n;i++){
	if(!biao[i]) sum[i]=sum[i-1]+1;
	else sum[i]=sum[i-1];
}
```

然后对于每一次询问，给定一个区间 $a$ , $b$ ，需要的最少染色次数不就等于 $sum[n] - sum[b] + sum[a - 1]$ 吗， 但是这个式子恒成立的条件只有当 $b = = n$ 时才可以，因为去掉了区间 $(a,b)$ ， 然后在区间 $(b + 1, n)$ 中有可能有从前面的点直接染色过来的，因此我们还需要去找有多少个点是从前面的点染色过来的，然后 $ans++$ 即可(因为**开始时是没有颜色的**)

下面是本蒟蒻的AC代码，可能有更优方案，大佬勿喷

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100005];
int n,k,sum[100005],biao[100005];
int main(){
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	for(int i=1;i<n;i++){
		if(biao[i]) continue;
		for(int j=i+1;j<=n;j++){
			if(s[j]<s[i]) break;
			if(s[j]==s[i]){
				biao[j]=i;
			}
		}
	} 
	for(int i=1;i<=n;i++){
		if(!biao[i]) sum[i]=sum[i-1]+1;
		else sum[i]=sum[i-1];
	}
	while(k--){
		int a,b;
		scanf("%d%d",&a,&b);
		if(b==n) cout<<sum[a-1]<<endl;
		else{
			int ans=sum[n]-sum[b]+sum[a-1];
			int minn=0x3f3f3f3f;
			for(int i=b+1;i<=n;i++){
				if(biao[i]&&biao[i]<=b&&biao[i]<minn){
					minn=biao[i];
					ans++;
					if(s[i]=='A') break;
				}
			} 
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

做完之后才感觉出来，**有更优方案**，其实我们既然记录从第一个点到 $a-1$ 的需要最少的染色方案，如果只是求这个，我们在 $O(1)$ 的时间内就可以求出来，那么为什么不倒过来去求 $(n, b + 1)$ 的需要的最少染色方案呢，这样是不是就可以保证在询问的时候的时间复杂度都变为 $O(1)$ 了。

## END

---

## 作者：Lonely_NewYear (赞：2)

# 洛谷 P7300 题解

## 题目分析

下文中 $f(x,y)$ 表示从第 $x$ 个栅栏涂到第 $y$ 个栅栏最少要多少笔。

注意如果 $[a,b]$ 一段栅栏不上色的话（注意是不能上色，不是可上可不上），答案应该就是 $f(1,a-1)+f(b+1,n)$。我们不妨先求出 $f(1,a-1)$。由于询问次数过多，容易想到预处理。

可以发现，如果第 $i$ 个位置需要涂的颜色还可以连着的话，那么就不需要重新涂一笔，那么 $dp_i=dp_{i-1}$；反之，如果中间有比当前颜色更浅的，就需要另起一笔，$dp_i=dp_{i-1}+1$。

问题在于如何维护当前是否还能继续涂。

注意如果第 $i$ 个位置需要涂的颜色为 $j$，那么所有比 $j$ 深的颜色都不能继续涂了。此时这个位置涂上了 $j$，那么颜色 $j$ 就可以继续涂。

这样我们就维护出了某一笔能否继续涂下去，也就能够求出 $f(1,a-1)$。

同理反过来就可以求出 $f(b+1,n)$。

对于每次询问，直接输出 $f(1,a-1)+f(b+1,n)$ 即可。

时间复杂度为 $O(26\times n)$。

## 代码

```cpp
#include<cstdio>
using namespace std;
char s[100010];
int f[100010],g[100010];
bool p[26],q[26];
int main()
{
	int n,m;
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=1;i<=n;i++)
	{
		f[i]=f[i-1];
		if(!p[s[i]-'A'])
		{
			f[i]++;
			p[s[i]-'A']=1;
		}
		for(int j=0;j<26;j++)
		{
			if(j>s[i]-'A')
			{
				p[j]=0;
			}
		}
	}
	for(int i=n;i>=1;i--)
	{
		g[i]=g[i+1];
		if(!q[s[i]-'A'])
		{
			g[i]++;
			q[s[i]-'A']=1;
		}
		for(int j=0;j<26;j++)
		{
			if(j>s[i]-'A')
			{
				q[j]=0;
			}
		}
	}
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",f[a-1]+g[b+1]);
	}
	return 0;
}
```

谢谢观看！

---

## 作者：xie_lzh (赞：1)


### 思路分析

首先我们先预处理一下，吧从前往后和从后往前的笔画数前缀和求出，再根据每一次提问得到答案。

那么，前缀和怎么求呢？

我们可以枚举每一个字母，从前扫到后求一次，再从后往前求一次。

对于当前枚举的字母，若是现在扫到了且没有标记，就把它标记起来，当前位置的 $ans+1$。

如果中途扫到了颜色浅的（看题） 就将标记删掉。

如果现在扫到了且有标记，就不加，继续扫。

剩下的看代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int len,q,x,y,ansl[maxn],ansr[maxn];
string s;
int read() //简单的快读
{
	int r=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') r=(r<<1)+(r<<3)+c-48,c=getchar();
	return r;
}
int main()
{
	len=read(); q=read();
	cin>>s;
	for(char c='A';c<='Z';c++)//求从左开始的前缀和
	{
		bool f=0;
		for(int i=0;i<len;i++)//枚举字符串
		{
			if(s[i]==c&&f==0)//如果扫到了且没有标记
			{
				ansl[i+1]++;//答案++
				f=1;		//标记
			}
			if(s[i]<c) f=0;//如果有颜色浅的就把标记删掉
		}
		f=0;
		for(int i=len-1;i>0;i--)//从右到左同理
		{
			if(s[i]==c&&f==0)
			{
				ansr[i+1]++;
				f=1;
			}
			if(s[i]<c) f=0;
		}
	}
	for(int i=1;i<=len;i++)//求左前缀和
		ansl[i]+=ansl[i-1];
	for(int i=len;i>0;i--)//求右前缀和
		ansr[i]+=ansr[i+1];
	while(q--)//询问
	{
		x=read(); y=read();
		printf("%d\n",ansl[x-1]+ansr[y+1]);//回答
	}
	return 0;
}
```
~~完结撒花~~

---

## 作者：青烟绕指柔 (赞：1)

显然答案可以分成一个前缀和一个后缀的和。

所以我们如果可以预处理前后缀，那么问题就能解决了。

假设对前缀考虑：
如果当前的字符和前一次出现的位置之间的字符全部大于，那么从上一次的位置涂色过来即可，答案为上一次的次数。否则那么需要1次来涂色。
对于求当前位置和上一次之间是否有小于的字符，做单调栈即可。

后缀同理。

代码：
```c
#pragma GCC optimize("-Ofast","-funroll-all-loops")
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=1e5+10;
int n,q,pre[N],suf[N],top; char str[N],s[N];
signed main(){
	scanf("%d %d %s",&n,&q,str+1);
	for(int i=1;i<=n;i++){
		while(top&&str[i]<s[top]) top--;
		pre[i]=pre[i-1]+(s[top]!=str[i]);
		s[++top]=str[i];
	}
	top=0;
	for(int i=n;i>=1;i--){
		while(top&&str[i]<s[top]) top--;
		suf[i]=suf[i+1]+(s[top]!=str[i]);
		s[++top]=str[i];
	}
	for(int i=1,l,r;i<=q;i++) scanf("%d %d",&l,&r),printf("%d\n",pre[l-1]+suf[r+1]);
	return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：1)

参考自自己在[这道题的加强版](https://www.luogu.com.cn/problem/P7416)中的[题解](https://www.luogu.com.cn/blog/ICANTAKIOI/solution-p7416)。

我们不妨考虑这道题的加强版，即不问前后缀而是问一段区间 $(l,r)$。

先将询问离线，挂在 $r$ 上，然后从 $1\sim n$ 依次加入每段栅栏。

每次向右移时先加自己的代价，再考虑能不能和前一个颜色连起来，如果可以就把前面的代价删掉，查询就是区间和，树状数组维护单改区查即可。

这里判能不能连起来可以用 RMQ，但码量太大，可以复制一遍树状数组，检查两个相同颜色中间有没有比其小的。

设当前颜色为 $c$，也就是看当前比 $c$ 小的个数和上一个 $c$ 前比 $c$ 小的个数差是否为 $0$。

这道题直接把前后缀的和累加在一个答案数组上即可。

坑点：字符集虽然比 $26$ 小但可能比 $n$ 大。

---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候，都已经知道了题目意思

我们可以发现，所有的询问操作都是删掉中间的一段

如果我们删掉的一段为$l-r$

那么，我们就可以发现，因为中间的一段不能涂色

所以，题目意思就等价于涂$1-(l-1)$和$(r+1)-n$的两段之和

我们不难发现，这两段求和就等价于前缀和与后缀和的和

所以，我们直接预处理前缀与后缀即可

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c))
		{
			f|=(c=='-');
			c=getchar();
		}
	while(isdigit(c))
		{
			x=(x<<1)+(x<<3)+(c^48);
			c=getchar();
		}
	return f?-x:x;
}
inline void write(int x){
	if(x<0)
		{
			putchar('-');
			x=-x;
		}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
int n,q;
string s;
int c[100010];
int ffront[30][100010],eend[30][100010];
signed main(){
	n=read();
	q=read();
	for(register int i=1;i<=n;++i)
		{
			char s;
			cin>>s;
			c[i]=int(s-'A'+1);
//			cout<<c[i]<<' ';
		}
	for(register int i=1;i<=26;++i)
		{
			int check=0; 
			for(register int j=1;j<=n;++j)
				{
					if(check==0 && i==c[j])
						ffront[i][j]=ffront[i][j-1]+1,check=1;
					else if(check==1 && i>c[j])
						ffront[i][j]=ffront[i][j-1],check=0;
					else
						ffront[i][j]=ffront[i][j-1];
				}
		}	
	for(register int i=1;i<=26;++i)
		{
			int check=0; 
			for(register int j=n;j;--j)
				{
					if(check==0 && i==c[j])
						eend[i][j]=eend[i][j+1]+1,check=1;
					else if(check==1 && i>c[j])
						eend[i][j]=eend[i][j+1],check=0;
					else
						eend[i][j]=eend[i][j+1];
				} 
		}
	for(register int i=1;i<=q;++i)
		{
			int l,r;
			l=read();
			r=read();
			int answer=0;
			for(register int j=1;j<=26;++j)
				answer=answer+ffront[j][l-1]+eend[j][r+1];
			write(answer);
			puts("");
		}
	return 0;
}

```


---

## 作者：Skies (赞：0)

来搬运一波大佬的solution

[原网页](http://usaco.org/current/data/sol_prob2_silver_jan21.html)

## 分析

对于候选范围（a，b），单独计算长度为a−1的前缀和长度为N−b的后缀的最小笔划数并相加就足够了。现在，我将描述如何计算每个前缀的最小笔划数（后缀的计算方式类似）。



让前缀[x]表示长度为x的前缀的答案。给定前缀[x]，我们如何计算前缀[x+1]？



设c表示围栏段x+1的颜色。如果c已经出现在长度x的前缀中，并且在c的最后一次出现和x+1段之间没有颜色较浅的段，那么我们可以简单地将绘制c的上一次出现的笔划扩展到绘制x+1段。在这种情况下
$$prefix[x+1]=prefix[x]$$
否则，我们最好使用一个额外的笔划来绘制新出现的c，这样
$$prefix[x+1]=prefix[x]+1$$



下面的代码保持自上次出现颜色t以来出现的最浅颜色，单位为min\u since\u last[t]。当添加新的颜色c时，我们为所有t≠c和min_since_last[c]=c设置min_since_last[t]=min（min_since_last[t]，c）。



下面两种程序都在O（N⋅∑+Q）时间内运行，其中∑是不同颜色的数目。

# code
## cpp
```cpp
#include <iostream>
using namespace std;
 
#define MAX_N 100000
int N, Q, min_since_last[26], prefix[MAX_N+1], suffix[MAX_N+2];
 
int main(void)
{
  string s;
  cin >> N >> Q >> s;
 
  // Build prefix counts of # of strokes needed
  for (int c=0; c<26; c++) min_since_last[c] = -1;
  for (int i=1; i<=N; i++) {
    int curchar = s[i-1] - 'A'; 
    for (int c=0; c<26; c++) min_since_last[c] = min(curchar, min_since_last[c]);
    prefix[i] = prefix[i-1];
    if (min_since_last[curchar] < curchar) prefix[i]++;
    min_since_last[curchar] = curchar;
  }
 
  // Build suffix counts of # of strokes needed
  for (int c=0; c<26; c++) min_since_last[c] = -1;
  for (int i=N; i>=1; i--) {
    int curchar = s[i-1] - 'A'; 
    for (int c=0; c<26; c++) min_since_last[c] = min(curchar, min_since_last[c]);
    suffix[i] = suffix[i+1];
    if (min_since_last[curchar] < curchar) suffix[i]++;
    min_since_last[curchar] = curchar;
  }
 
  for (int i=0; i<Q; i++) {
    int x, y;
    cin >> x >> y;
    cout << prefix[x-1] + suffix[y+1] << "\n";
  }
}
```
## java
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;
 
public class NoTimeToPaint {
 
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        String colors = " " + in.readLine();
        int[] last = new int[26];
        int[] prefixes = new int[n + 1];
        for (int j = 1; j <= n; j++) {
            prefixes[j] = prefixes[j - 1];
            int letter = colors.charAt(j) - 'A';
            boolean isLeft = last[letter] == 0;
            for (int lighter = 0; lighter < letter; lighter++) {
                if (last[lighter] > last[letter]) {
                    isLeft = true;
                }
            }
            if (isLeft) {
                prefixes[j]++;
            }
            last[letter] = j;
        }
        Arrays.fill(last, n + 1);
        int[] suffixes = new int[n + 2];
        for (int j = n; j >= 1; j--) {
            suffixes[j] = suffixes[j + 1];
            int letter = colors.charAt(j) - 'A';
            boolean isRight = last[letter] == n + 1;
            for (int lighter = 0; lighter < letter; lighter++) {
                if (last[lighter] < last[letter]) {
                    isRight = true;
                }
            }
            if (isRight) {
                suffixes[j]++;
            }
            last[letter] = j;
        }
        StringBuilder out = new StringBuilder();
        for (int j = 1; j <= m; j++) {
            tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken());
            int b = Integer.parseInt(tokenizer.nextToken());
            out.append(prefixes[a - 1] + suffixes[b + 1]).append('\n');
        }
        System.out.print(out);
    }
}
```



---

## 作者：极寒神冰 (赞：0)

询问显然为一个前缀和一个后缀的染色。

考虑用单调栈维护这个前缀，用一个$map$记录当前栈中有哪些颜色，当栈顶颜色颜色大于当前颜色时，便将栈顶颜色退栈。

若当前颜色目前并没有在栈中出现，便将$res++$

后缀同理

```cpp
map<int,int>mp1,mp2;
signed main()
{
	n=read(),q=read();
	scanf("%s",s+1);
	R(i,1,n) a[i]=s[i]-'A';
	R(i,1,n){
		if(top&&a[stk[top]]>a[i]||!mp1[a[i]]){
			while(top&&a[stk[top]]>a[i]) mp1[a[stk[top]]]--,top--;
			if(!mp1[a[i]]) res++;
		}
		pre[i]=res,stk[++top]=i;mp1[a[i]]++;
	}
	top=0,res=0;
	L(i,1,n) {
		if(top&&a[stk[top]]>a[i]||!mp2[a[i]]){
			while(top&&a[stk[top]]>a[i]) mp2[a[stk[top]]]--,top--;
			if(!mp2[a[i]]) res++;
		}
		suf[i]=res,stk[++top]=i;mp2[a[i]]++;
	}
	while(q--){
		int x=read(),y=read();
		printf("%lld\n",pre[x-1]+suf[y+1]);
	}
}
```


---

