# [USACO07MAR] Gold Balanced Lineup G

## 题目描述

神仙 $\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 在许多方面都有着很强的能力。具体的说，他总共有 $m$ 种能力，并将这些能力编号为 $1 \sim m$。  

他的能力是一天一天地提升的，每天都会有一些能力得到一次提升，她对每天的能力提升都用一个数字表示，称之为能力提升数字，比如数字 $13$，转化为二进制为 $1101$，并且从右往左看，表示他的编号为 $1,3,4$ 的能力分别得到了一次提升。  

$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 把每天表示能力提升的数字的记了下来，如果在连续的一段时间内，她的每项能力都提升了相同的次数，她就会称这段时间为一个均衡时期，比如在连续 $5$ 天内，她的每种能力都提升了 $4$ 次，那么这就是一个长度为 $5$ 的均衡时期。

于是，问题来了，给出 $\mathsf E \color{red} \mathsf{ntropyIncreaser}$ $n$ 天的能力提升数字，请求出均衡时期的最大长度。


## 说明/提示

【数据范围】    
对于 $50\%$ 的数据，$1\le n \le 1000$。  
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le m \le 30$。

【样例解释】

每天被提升的能力种类分别为：

| 天数 | 提升的能力 |
| :-----------: | :-----------: |
| $1$ | $1,2,3$ |
| $2$ | $2,3$ |
| $3$ | $1,2,3$ |
| $4$ | $2$ |
| $5$ | $1$ |
| $6$ | $3$ |
| $7$ | $2$ |

第三天到第六天为长度最长的均衡时期，因为这四天每种能力分别提升了 $2$ 次。


## 样例 #1

### 输入

```
7 3
7
6
7
2
1
4
2
```

### 输出

```
4

```

# 题解

## 作者：karma (赞：45)

看完下面的题解,真心想说,你们讲的是个X.(顺手举报一个错题解).这么好的一个题,真是浪费了.我估计下面的写题解的人也是一知半解,没有明白此题的细节.有些细节不写注释估计自己也不知道为啥这么写.


进入正题.初看此题毫无思路,可以尝试将给出的序列中的每一个数转换成二进制并求一下前缀和.用样例举个例子:

```cpp
天数    今日数值(转换为二进制)    前缀和(假设不进位)
1       7->111                      111
2       6->110                      221
3       7->111                      332    
4       2->010                      342
5       1->001                      343
6       4->100                      443
7       2->010                      453
```
当区间满足是一个"均衡时期",必满足该区间中每项能力都提升X

.设区间为[L,R],即前缀和sum[R]-sum[L-1]的每一位都相等.

如样例中从第三天到第六天,前缀和为443-221=222.故每项能力都提升了2.


以此类推.设最长区间的起始天的前一天(因为要算前缀和)为L,末尾的一天为R.设L的每一位(从左向右数)为

```math
L_{1},L_{2},L_{3}...L_{n}
```
R的每一位(从左向右数)为

```math
R_{1},R_{2},R_{3}...R_{n}
```
则有
```math
R_{1}-L_{1}=R_{2}-L_{2}=R_{3}-L_{3}...=R_{n}-L_{n}
```
移项得:

```math
\left\{\begin{matrix}
 &R_{1}-R_{2} =L_{1}-L_{2} \\ 
 &R_{1}-R_{3} =L_{1}-L_{3} \\ 
 &R_{2}-R_{3} =L_{2}-L_{3} \\
 &...
\end{matrix}\right.
```
其实最后一个式子是没有意义的,因为用前N-1个式子可以推出来第N个式子.于是我们将这个式子用上.每次计算前缀和后可以减去第一位的值.之后如果得到的两个值相等.那么它们就是一个均衡区间.


**算法**:

- 哈希:保存每个状态和它对应的天数,每次插入之前查询这个状态是否在之前出现过.如果有,用现在的天数减去之前的天数.不断求ans=max(ans,天数差),就行了.可以手写,也可以用map

.楼下用map的题解.每次转换成二进制时顺便就减了,减之前的判断(x&1)是在判断最后一位是否为1.(因为他要将每一位数减去最后一位数)


- 排序,自定义比较,将状态相同的排在一起.然后扫一遍打擂台求出最大值.(最好用结构体存状态和对应的天数)有一点细节:要多加一个0天.否则有数据可以hack掉.如1   3这组数据.会输出0而不是1.


我觉得讲的够详细了,就不贴代码了.下面有.有兴趣可以看看耗时最少的人的代码,我表示看不懂.可能有什么快速的hash技巧.有什么错误请私信指出,谢谢.


---

## 作者：Anoxiacxy (赞：33)

刚看到这题时我是懵逼的，~~这TM是什么玩意？？？~~

然后突然灵机一动，用了个STL的map，利用前缀和的思想，将以前的状态直接用map存起来，

每到新的一天，查询之前是否有和现在相同的状态，如果有，我们就更新答案，不然就直接将该状态插入map

时间复杂度O（nmlogn）可以承受，而且代码超级短





```cpp
#include <iostream>
#include <cstdio> 
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define LL long long 
#define mod 9901
using namespace std;
map<vector<int>,int>f;
int ans;
int main(){
    int n,m;scanf("%d%d",&n,&m);
    vector<int>now(m);
    f[now]=0;
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        for(int j=0;j<m;j++)
            if(x&(1<<j))now[j]++;
        if(x&1)for(int j=0;j<m;j++)now[j]--;
        if(f.count(now))ans=max(ans,i-f[now]);
        else f[now]=i;
    }
    printf("%d",ans);
}
```

---

## 作者：SamariumPhosphide (赞：17)

首先显然就是用前缀和统计每天的能力值，设前 $i$ 天，$j$ 号魔法值为 $s[i][j]$。那么均衡时期如果是从 $l$~$r$，那么 $s[r][i]  - s[l-1][i]$ 为一个定值。考虑怎么快速判断这件事情。

比如一天的能力值为 $1, 9, 2, 6$， 另一天为 $3, 11, 4, 8$，那么可以把差相同的能力值转化成一个“标准形式”。比如 $1,9,2,6\to 0,8,1,5\qquad 3,11,4,8 \to 0, 8, 1, 5$，也就是说不停地把所有数-1直到有一个为 $0$ 为止。

那么用 map 和 vector 维护即可，不需要 hash。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<vector<int>, int> hsh;
int n, m, ans;

signed main() {
  scanf("%d %d", &n, &m);
  vector<int> v;
  v.resize(m);
  hsh[v] = 0;
  for (int tc = 1; tc <= n; tc++) {
    int d; scanf("%d", &d);
    bool flag = true;
    for (int i = 0; i < m; i++) {
      v[i] += ((d >> i) & 1);
      if (v[i] == 0) flag = false;
    }
    for (int i = 0; i < m; i++) {
      v[i] -= flag;
    }
    if (hsh.count(v)) {
      ans = max(ans, tc - hsh[v]);
    } else {
      hsh[v] = tc;
    }
  }
  printf("%d\n", ans);
  return 0;
}
```

---

## 作者：苍穹狮鹫 (赞：7)

7 3
7
6
7
2
1
4
2

转化为2进制

111

110

111

010

001

100

010

逐个累加

111

221

332

342

343

443

453

分别减去最右边的数

000

110《----

110

120

010

110《----

120
因为我们最开始求的是前缀和，所以一个前缀和数组记录了从1到它本身的累加和，减去右边的相同后如果两数相同，可以知道他们两个区间内的加和的每一位也是相同的。
这里我用的是map判重

用map记录以（比如110或120结尾的最开始的位置）

注意：初始的0天其实也算一个状态！！！！！！

```cpp
#include<cstdio>
#include<iostream>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
int a[1000001];
int book[100050][31];
int read()
{
    register int x = 0,f = 1;register char ch;
    ch = getchar();
    while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
    while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
    return x * f;
}
void pre(int num,int x)
{
	for(int i=1;i<=m;i++)
	book[num][i]=book[num-1][i];
	int wei=0;
	while(x>0)
	{
		wei++;
		book[num][wei]+=x%2;
		x=x/2;
	}
	return ;
}
int main()
{
	//freopen("num.out","w",stdout);
	cin>>n>>m;
	//pre(0,0);
	for(int i=1;i<=n;i++)
	{
		int x;
		//cin>>x;
		x=read();
		pre(i,x);
	}
	
	for(int i=0;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		book[i][j]-=book[i][m];
	}
	
	int ans=0;
	map < string ,int > mymap;
	for(int i=0;i<=n;i++)
	{
		
		string y;
		for(int j=1;j<=m;j++)
		y+=char(book[i][j]+65);
		
		//if(i==1)
		//cout<<y<<endl;
		
		//if(i==30000)
		//cout<<y<<endl;
		
		map <string ,int > :: iterator iter;
       	iter = mymap.find(y);
		if(iter != mymap.end())
		{
			ans=max(ans,i-mymap[y]);
		}
		else
		{
			mymap[y]=i;
		}
	}
	printf("%d",ans);
	return 0;
}
```
完结撒花

---

## 作者：vegetabird (赞：5)

#怎么没人写暴力？

给个暴力的思路：

大神们都$hash$去了，蒟蒻只能写个类，暂且叫它$ability$：

$pos$表示第$i$天

数组$level$表示第$i$天小R各项能力值减去该天小R最小的一项能力值。



则若第$i$~$j$天是一个均衡时期，则$ability_{i-1}$.$level$=$ability_j$.$level$

所以我们可以把$ability$排序一下，然后就能轻松求出答案了。

CODE:
```cpp
#ifndef IOOPTIMIZATION_H
#define IOOPTIMIZATION_H
#ifndef STDIO_H
#include<stdio.h>
#endif
#ifndef CTYPE_H
#include<ctype.h>
#endif
const int bufsize=1000000;
char buf[bufsize],ch,*p1=buf,*p2=buf;
inline char nextchar(){
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufsize,stdin),p1==p2)?EOF:*p1++;
}
inline void getint(int &des){
    des=ch=0;
    while(!isdigit(ch))ch=nextchar();
    while(isdigit(ch))des=des*10+ch-48,ch=nextchar();
}
#endif
#ifndef STRING_H
#include<string.h>
#endif
struct ability{
    int level[30];
    int pos;
    inline ability(){
        memset(level,0,sizeof(level));
    }
    inline void operator=(ability v){
        for(int i=0;i<30;i++){
            level[i]=v.level[i];
        }
        pos=v.pos;
    }
    inline bool operator<(const ability &v)const{
        for(int i=0;i<30;i++){
            if(level[i]<v.level[i])return true;
            if(v.level[i]<level[i])return false;
        }
        return pos<v.pos;
    }
    inline bool operator==(const ability &v)const{
        for(int i=0;i<30;i++)
            if(level[i]!=v.level[i])return false;
        return true;
    }
};
inline int min(const int &a,const int &b){
    return a<b?a:b;
}
inline int max(const int &a,const int &b){
    return a>b?a:b;
}
#ifndef _GLIBCXX_ALGORITHM
#include<algorithm>
#endif
int n,m;
ability a[100010];
int pos[100010];
const int INF=0x7fffffff;
int ans;
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int i,j,k,u;
    getint(n);
    getint(m);
    for(i=1;i<=n;i++){
        a[i].pos=i;
        getint(k);
        u=INF;
        for(j=0;j<m;j++){
            a[i].level[j]=a[i-1].level[j]+(bool)(k&(1<<j));
            u=min(u,a[i].level[j]);
        }
        for(j=0;j<m;j++){
            a[i].level[j]-=u;
        }
    }
    std::stable_sort(a+1,a+n+1);
    for(j=0;j<30;j++){
        a[n+1].level[j]=-1;
    }
    for(i=0;i<=n;i++){
        j=i;
        while(a[j+1]==a[j])j++;
        ans=max(ans,a[j].pos-a[i].pos);
        i=j;
    }
    printf("%d\n",ans);
}
```

---

## 作者：双管荧光灯 (赞：5)

Hash也可以

先处理一下前缀和

然后用1~k的能力值全减去1的能力值

为什么要这样做呢？

举个例子

1 1 0
0 1 0
1 0 1
0 0 1
1 0 0
前缀和：

1 1 0
1 2 0
2 2 1
2 2 2
3 2 2
减一下

0 0 -1
0 1 -1
0 0 -1
0 0 0
0 -1 -1

可以发现，对于l和r，若l和r所对序列相同，则[l+1，r]是一个均衡期（易证）

然后就可以Hash啦

O（nk\*（你的rp））

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <algorithm>
using namespace std;
const int M=1000007;
int n,k,i,j,a[35][100005],p,head[1000007],Next[100005],adj[35][100005],s,m,ans,l[100005];
void Push(int u,int i)//Hash插入
{
    int j;
    Next[++p]=head[u];
    head[u]=p;
    l[p]=i;
    for(j=1;j<=k;j++)
        adj[j][p]=a[j][i];
}
int main(){
    scanf("%d %d",&n,&k);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&p);
        for(j=1;j<=k;j++)
            a[j][i]=a[j][i-1]+((p>>(j-1))&1);
    }
    p=0;
    Push(0,0);//注意第0天也要加进去
    for(i=1;i<=n;i++)
    {
        s=0;
        for(j=2;j<=k;j++)
            s=((s+a[j][i]-a[1][i])*j%M+M)%M;
        for(j=head[s];j!=0;j=Next[j])
        {
            for(m=2;m<=k;m++)
                if(adj[m][j]-a[m][i]!=adj[1][j]-a[1][i])
                    break;
            if(m>k)
            {
                ans=max(ans,i-l[j]);
                break;
            }
        }
        if(j==0)//如果i能找到与它相同的序列，就不要加了，只要最早的，要不然会WA
            Push(s,i);
    }
    printf("%d",ans);
}

```

---

## 作者：Link_Space (赞：3)

从题解区 AnoxiacxyAnoxiacxy大佬代码中得到思路，现对该大佬的思路做一个更加详细的讲解

拿到题之后思考，我们试着去记录每一个将领的特性，并且求出前缀和。

假设我们现在正在考虑第i位将领，第j位将领为第i位将领之前的某一位将领。

那么第i位将领的前缀和的每一位如果能同时减去一个数k恰好与第j位将领的每一位将领相同，那么即说明第j+1位到第i位将领的每一位将领的前缀和的每一位加起来的和都恰好是k，就满足条件了，而我们只需要求出这样的满足条件的将领个数的最大值即可。

思路已经知道，考虑如何来实现代码，那么首先想到的肯定是用一个数组来存前缀和，但是如何和之前的相互比较看是否满足条件呢？那么我们考虑将数组改变成vector来存储当前的前缀和，假设该vector名为now，然后建立一个以now为映射的map,假设该map名为found，每次输入第i个将领的特性值时都更新now，然后查询之前的i-1个将领中前缀和同样为now的将领最后出现在什么位置，那么i这之间的所有将领都满足条件，而map存储的就是前缀和为now的最后一个将领。
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
using namespace std;
map<vector<int>, int> found;
int main()
{
    int maxn = 0;
    int n,k;
    scanf("%d%d", &n, &k);
    vector<int> now(k);
    found[now] = 0;
    for (int i = 1;i<=n;i++)
    {
        int x;
        scanf("%d", &x);
        for (int j = 0; j < k;j++)
            if(x&(1<<j))
                now[j]++;
        if(x&1)
            for (int j = 0; j < k;j++)
                now[j]--;//或许有的同学不理解这一步，讲解如下
        if(found.count(now))
            maxn = max(maxn, i - found[now]);
        else
            found[now] = i;
    }
    printf("%d\n", maxn);
```
这一步的意思就是每次存储进去时就将每一位减1，可以看作每一位都是最简形式，例如第i位的前缀和为221，那么存进去时每一位减了一直到最后一位为0，存进去时就变成了110。
而我们之后碰见了一个将领j的前缀和为554，那么存进去时即为110，与221的最简形式相同，那么i+1到j中的所有将领都可以杀死，即为合法方案，而我每一次存的时候都减一，即保证了随时都是最简形式，下一位将领的前缀和状态也是从当前这一位将领的now得到，那么下一位将领的now也为最简状态，直接存进found即可

---

## 作者：keep_ (赞：2)

# P1360 [USACO07MAR]Gold Balanced Lineup G (前缀和+思维)

## 前言

[题目链接](https://www.luogu.com.cn/problem/P1360)

本题作为一道Stl练习题来说，还是非常不错的，解决的思维比较巧妙

算是一道不错的题

## 思路分析

第一眼看到这题，我还以为是数据结构题，看来半天没看出来数据结构咋

做(~~我还是太菜了~~)。

我们对$m$种能力有$n$次操作，需要找到对每种能力提升相同的最大操作

区间的长度，求最大区间，我们考虑维护这 $m$ 种技能提升值的前缀和，

假设第 $l+1$ 次操作到第 $r$ 次操作对 $m$ 个能力的提升相同，那么一定有

一个重要的性质，任取$m$种操作中的一种操作 $q$ ，执行第 $l$ 次操作

后，每一种技能提升值的前缀和与q的提升值前缀和的差值与执行 $r$ 操作

后相等，该性质是很显然的，

因为区间操作后对每种技能提升相同，所以差值也一定相同。所以 $l$ 到

$r$就是一个均横时期，根据此性质我们就可以解决该题了。

我们先选定一种能力，用 vector 维护所有能力与其的差值，执行某一次操

作后，若发现此时的差值与过去某一次操作后差值相等(用map维护)，那

么从过去的那次操作(不包含其本身)到当前操作就是一个均衡时期。我们

扫一遍操作，找到最大长度即可。

## 代码

我的代码借鉴了楼上那篇用map实现的超短的题解

orz太强了，在此我对其进行部分解释

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<string>
#include<vector>
#define int long long 
using namespace std;
const int maxn=1e5+10;
inline int read(){
	int ret=0;
	int f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-f;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0'){
		ret=ret*10+(ch^'0');
		ch=getchar();
	}
	return ret*f;
}
int n,m;
int ans,q;
map<vector<int>,int>a; 
signed main(){
	n=read();
	m=read();
	vector<int>p(m+10);
	a[p]=0;//记得初始化，不然会wa
	for(int i=1;i<=n;i++){
		q=read();
		for(int j=0;j<m;j++){
			if(q&(1<<j)){
				p[j]++;//维护前缀和
			}
		}
        if(q&1)
        	for(int j=0;j<m;j++){
        		p[j]--;
			}
/*上述操作是在维护差值，我们选取第一种能力作为标准值，也就是上述
的q,如果本次操作对第一种能力有提升，因为我们要获得差值，所以就要把所给所有能力减1；
            */
        if(a.count(p)){//count函数，获得相同判断过去的操作是否有相同差值
        	ans=max(ans,i-a[p]);//获取最大长度，为什么不+1，应为不包含左端区间
		}
        else a[p]=i;
	}
	cout<<ans<<endl;
	return 0;
}
```
如果对此有疑惑，欢迎评论。

---

## 作者：Lates (赞：2)

这里位数按自 $0$ 到 $m-1$ 位计算。

考虑把二进制位做一个前缀和。

前缀和做完设第 $i$ 天,第 $j$ 位为 $a[i][j]$

题目转化成求最大区间 $[l,r]$ 使得对于每个 $k$ 有 $a[r][k]-a[l-1][k]$ 位定值。

为定值就有 $a[r][k]-a[l-1][k]=a[r][0]-a[l-1][0]$

即 $a[r][k]-a[r][0]=a[l-1][k]-a[l-1][0]$。

那么可以对于所有 $i$ 把 $a[i][k]$ 减去 $a[i][0]$ 

现在就相当于有 $n$ 天，每天是有一个序列，求最大区间 $[l,r]$ 使得第 $l$ 个序列和第 $r$ 的序列相同。

因为要使区间最大，所以左端点要尽量小，用 map 记录每种序列最早出现的位置。就做完了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX=1e5+5,MAXM=50;
int n,m;
int a[MAX][MAXM],x,ans;
vector<int>v(MAXM);
map<vector<int>,int>ma;
signed main(){
//	freopen("in.in","r",stdin);
	n=read();m=read();
	for(register int i=1;i<=n;++i){
		x=read();
		for(register int j=0;j<m;++j)a[i][j]=a[i-1][j]+(x>>j&1);
	}
	for(register int i=1;i<=n;a[i][0]=0,++i)for(register int j=1;j<m;++j)a[i][j]-=a[i][0];
	ma[v]=0;
	for(register int i=1;i<=n;++i){
		for(register int j=0;j<m;++j)v[j]=a[i][j];
		if(ma.count(v))ans=max(ans,i-ma[v]);
		else ma[v]=i;
	}
	printf("%d\n",ans);
	return 0;
}


```


---

## 作者：Azuree (赞：2)

[查看原图请戳这里](https://www.luogu.org/problem/P1360)

首先明确一点，题目求的是最长的每项能力提升大小都相等的区间，所以我们是不用关心一段区间每项能力到底提升了多少，只需要去记录每项能力的大小关系即可。即如果第i天能力x比能力y多k，第j天能力x比能力y也多k，那么在i~j天中x和y的变化量都相等。

所以我们就可以先维护一个二维前缀和来记录每一天每个能力的能力值，再用相邻两行做差来记录大小关系。于是，我们只需要去寻找x，y，使得第x天的大小关系与第y天相同且y-x尽可能大。我们可以发现，如果暴力枚举去寻找，复杂度是$O(n^2)$的，所以我们可以先对这个表示大小关系的二维矩阵的列排序，再去$O(n)$统计答案。

code:

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
#define INF 0x7fffffff
#define re register
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define qwq printf("qwq\n");

using namespace std;

int read()
{
	register int x = 0,f = 1;register char ch;
	ch = getchar();
	while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
	while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}

int n,m,x,y,ans,cnt,flag,f[37][1000015],h[37][1000015],e[100005];

struct two{
	int num[47],p;
}g[1000015];

void broke(int x,int i)
{
	int cnt = 0;
	while(x > 0)
	{
		f[++cnt][i] = x & 1;
		x >>= 1;
	}
}

void init()
{
	n = read(); m = read();
	for(int i = 1; i <= n; i++)
	{
		y = x;
		x = read();
		e[i] = x;
		if(x != y && x > 1) flag = 1;
		broke(x,i);
	}
}

void make1()
{
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++)
			f[i][j] = f[i][j - 1] + f[i][j];
}

int mysort(two a,two b)
{
	int k = 1;
	while(a.num[k] == b.num[k] && k <= m) k++;
	if(k <= m) return a.num[k] < b.num[k];
	return a.p < b.p;
}

void make2()
{
	for(int i = 2; i <= m; i++)
		for(int j = 1; j <= n; j++)
			g[j].num[i] = f[i][j] - f[i - 1][j],g[j].p = j;
	sort(g, g + n + 1,mysort);
}

bool cmp(int a,int b)
{
	for(int i = 1; i <= m; i++) if(g[a].num[i] != g[b].num[i]) return false;
	return true;
}

void find()
{
	ans = 0;
	int head = 0;
	while(head < n)
	{
		int k = head;
		while(cmp(k + 1,head) && k < n) k++;
		if(k <= n) ans = max(ans,g[k].p - g[head].p);
		head = k + 1;
	}
}

int main()
{
	init();
	if(flag == 0)
	{
		int k = 0;
		while(e[k + 1] == 0 && k < n) k++;
		printf("%d\n",k);
		return 0;
	}
	make1();
	make2();
	find();
	printf("%d\n",ans);
    return 0;
}
```

---

## 作者：eros1on (赞：2)

[博客食用更佳](https://tle666.github.io/2019/11/13/[USACO07MAR]%20Gold%20Balanced%20Lineup/)

# **Description**

有 $n$ 天， $m$ 种能力。每天都对应着一个给定的二进制数，第 $i$ 位是 $1$ 代表第 $i$ 种能力提升 $1$ 次。否则不提升。如果在连续的一段时间内，每项能力都提升了相同的次数，就称这段时间为一个均衡时期。求均衡时期的最大长度。

对于 $100 \%$ 的数据，有 $n \leq 10^5,m \leq 30$ 

[题目链接戳这里](https://www.luogu.org/problem/P1360)

# **Solution**

我们发现 $m$ 不大，于是考虑一次对每个能力算出前缀和。设第 $i$ 天所有 $m$ 个能力所构成的序列为 $S_i$ ，则一个从第 $l$ 天到第 $r$ 天的均衡时期肯定满足 $S_{l - 1}$ 和 $S_r$ 对应每项的差相同。比如 $\texttt{[1, 3, 2, 4]}$ 和 $\texttt{[3, 5, 4, 6]}$

由此，我们能够想到哈希。

我们希望给出一种对应法则使所有 对应每项的差相同 的序列都对应成一个哈希值。因为满足这个条件的序列之间一定是一个均衡时期。例如 $\texttt{[2, 1, 4, 0]}$ ， $\texttt{[4, 3, 6, 2]}$ ， 和 $\texttt{[5, 4, 7, 3]}$ 这三个序列应该对应同一种。

由于 $m$ 很小，可以直接把整个序列加上或减去一个数 $d$ ，使得序列的第一个数为 $0$ ，也就是把整个序列同时减去第一个数。比如把 $\texttt{[2, 1, 4, 0]}$ 全部减二，变为 $\texttt{[0, -1, 2, -2]}$ 。（负数也无妨，毕竟哈希跟正负无关）

现在，只需求出依次累积的能力即可。

对于每一次哈希的值：

- 若没有出现过，则把当前时间（天数）记录到一个数组中。
- 若出现过，即当前哈希值对应的数组已经有值，则说明 当前 与 数组中记录的时间 这两者间是一个均衡时期。更新答案即可。

**特别提醒：如果经过操作（即全序列减去第一个数）后得到全 0 序列，则第 1 天到它也是一个均衡时期，因为第 0 天的序列也是全 0 序列。**

（感谢 $\text{wzj dalao}$ 的提醒）

例如第 $5$ 天时序列为 $\texttt{[3, 3, 3, 3]}$ ，则对应着 $\texttt{[0, 0, 0, 0]}$ 序列，说明和第 $0$ 天之后一天（第 $1$ 天）构成了一个均衡时期。

# **Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
typedef long long ll;
const int N = 1e5 + 100;
const int bas = 29;
const int mod = 998244353;
const int bs2 = 19;
const int md2 = 19260817;
const int bs3 = 101;
const int md3 = 9291433;
const int bs4 = 67;
const int md4 = 1e9 + 7;

int n, m, a[N], b[N], ans;

unordered_map <ll, int> mp; // 哈希和时间的对应

ll Hash() { // 多重哈希，以防被卡
  ll num = 1, res = 0;
  rep(i, 1, m) {
    res += b[i] * num;
    res %= mod;
    num *= bas;
  }
  ll rs2 = 0; num = 1;
  rep(i, 1, m) {
    rs2 += b[i] * num;
    res %= md2;
    num *= bs2;
  }
  ll rs3 = 0; num = 1;
  rep(i, 1, m) {
    rs3 += b[i] * num;
    res %= md3;
    num *= bs3;
  }
  return (res * bs4 * bs4 + rs2 * bs4 + rs3) % md4; // “哈希 套 哈希”
}

void chg(int x) { // 对应序列。把 b 数组对应成上述序列（即第一个数为 0 ）
  per(i, m - 1, 0) {
    if (x >= (1 << i)) {
      x -= (1 << i);
      a[i + 1]++;
    }
  }
  b[1] = 0;
  rep(i, 2, m) b[i] = a[i] - a[1];
}

int main() {
  scanf("%d %d", &n, &m);
  mp[0] = 0;
  rep(i, 1, n) {
    int d;
    scanf("%d", &d);
    chg(d);
    ll tmp = Hash();
    if (!mp.count(tmp)) mp[tmp] = i; // 记录第一次时间
    else
      ans = max(ans, i - mp[tmp]); // 计算答案，更新答案
  }
  printf("%d\n", ans);
  return 0;
}
```



---

## 作者：说好不哭 (赞：1)

# 题解 P1360 【黄金阵容均衡】
## 这题放在STL的作业题里，但是，我真的没有想出任何关于STL的做法来，STL也不太懂，所以就手动随便乱写。
### 主要题意就是，让你对m个数组都进行一遍前缀和操作，然后让你找出连续的一段区间，使得这段区间两端点的各个前缀和数组差值都一样，把这个区间的最大长度记为答案。
### 处理完前缀和后，相信大家对于 O(n^2）的算法都知道，暴力枚举区间两端点然后判断是否成立。但是肯定会T，所以我想到另一种查询方法。对于每一天的m个前缀和数组，用另一个数组记录它们之间的差值，所以对于一个区间的两个端点来说，若这个记录它们之间差值的数组都一样，则说明这段区间内所有的前缀和增加的值都一样，这不就符合条件了吗？ 成功转化。
### O（n）处理完前缀和 与 所有前缀和之间的差值以后，对于这些差值进行排序，这样就可以在O（n）时间内查询到所有前缀和差值都一样的端点。而之前排序的复杂度为 n log n，对于十万级的数据，完全可以过。

## 下面放代码


```cpp
 #include <bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=35;
int n,m,v,k,b[N][M],sum[N][M],now[M],noww,ans;
bool jay;
struct number{int a[M],id;}num[N];

inline bool cmp(number x,number y){
for (register int i=1; i<m; ++i) if (x.a[i]<y.a[i]) return true; else if (x.a[i]>y.a[i]) return false;
if (x.id<y.id) return true;
return false;
}

int main(){
scanf("%d%d",&n,&m); 
memset(b,0,sizeof(b));
	for (register int i=1; i<=n; ++i)
	{
	scanf("%d",&v);
	k=1;
		while (v)
		{
		b[i][k]+=(v&1);
		k++;	
		v>>=1;	
		}
	}

for (register int i=1; i<=n; ++i)
for (register int j=1; j<=m; ++j) sum[i][j]=sum[i-1][j]+b[i][j];
	
	for (register int i=1; i<=n; ++i) 
	{
	for (register int j=1; j<m; ++j) num[i].a[j]=sum[i][j]-sum[i][j+1];
	num[i].id=i;
	}
n++;
for (register int i=1; i<m; ++i) num[n].a[i]=0; num[n].id=0;
sort(num+1,num+n+1,cmp);

for (register int i=1; i<m; ++i) now[i]=num[1].a[i]; noww=num[1].id;
	for (register int i=2; i<=n; ++i) 
	{
	jay=true;
	for (register int j=1; j<m; ++j) if (num[i].a[j]!=now[j]) {jay=false; break;}
		if (jay) 
			ans=max(ans,num[i].id-noww);
		else 
			{
			for (register int j=1; j<m; ++j) now[j]=num[i].a[j];
			noww=num[i].id;
			}
	}

printf("%d\n",ans);
return 0;	
}
```


---

## 作者：12mango (赞：1)

啊我写个稍微详细一点的……


求一段最长的“平衡区间”，就是在这段区间内各种特征的数量和相等。首先十进制转二进制，然后求前缀和sum，这是为了方便作差判断——区间开头两特征的差sum[start][x]-sum[start][0]==结尾两特征的差(sum[start][x]+y)-(sum[start][0]+y)==sum[end][x]-sum[end][0]，0<=x<k,y是每个特征增加的数量。那么，如果对于每个x都满足以上等式，就可以判断区间成立。为了减小时间复杂度，我们考虑一个哈希操作，minus[i][x]=sum[i][x]-sum[i][0],将∑minus[i][x] %mod表示为key[i]，它就是我们哈希的“钥匙”。当然，只是求和+mod还不够，我们需要进一步比较每一位是否都满足，更新答案为编号的差，这样我们就有了一个能AC的思路。


此外还有好多细节（如果你觉得太烦可以不看23333333）。


①22行 将key[i]变为正数再模——不然如果它还是负数就会数组越界。


②search找答案，如果判出相等直接return而不用放入队列——我们设a,b,c三个minus，id a<id b<id c，找到a==b更新答案，如果a==c，那么id c-id a>id b-id a，显然b没有必要放入队列。


③把list[0]放入0——给一组数据1 3 0，应该输出1而不是0。


```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath> 
#include<vector> 
#define mod 100003 
#define inf 1<<29
using namespace std;
int n,k,tz[mod][40],ms[mod][40],sum[mod][40],key[mod],ans; 
vector<int>list[mod];
void init()
{
    for(int i=0;i<mod;++i) list[i].clear();
    list[0].push_back(0);
    for(int i=1;i<=n;++i){
        for(int j=0;j<k;++j){
            sum[i][j]=sum[i-1][j]+tz[i][j];
            ms[i][j]=sum[i][j]-sum[i][0]; 
            key[i]+=ms[i][j]; 
        }
        key[i]=abs(key[i])%mod; 
    }
}
void search(int knum,int id)
{
    int len=list[knum].size();
    for(int j=0;j<len;++j){
        int f=1;
        for(int l=0;l<k;++l)
            if(ms[list[knum][j]][l]!=ms[id][l]){
                f=0;
                break; 
            } 
        if(f){
            ans=max(ans,id-list[knum][j]);
            return; 
        }
    }
    list[knum].push_back(id); 
}
int main()
{
    int t; 
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i){
        scanf("%d",&t); 
        for(int j=0;j<k;++j){
            tz[i][j]=t%2;
            t/=2; 
        }
    }
    init();
    for(int i=1;i<=n;++i) search(key[i],i);
    printf("%d",ans); 
    return 0;
}
```

---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P1360)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;第一步，很容易想到用一个$cnt[j][i]$的数组存储在第$j$中能力上面增加的前缀和。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后我们先思考暴力做法。枚举序列的左右端点，然后暴力检查这个区间是否合法，时间是$O(N^2M)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑优化。如果我们确定第$i$个位置为右端点，那么我们的最优左端点其实就是在$cnt$的差分数组上和$i$相同的最左的一个端点（$cnt$的差分数组指的是一个数组$f[j][i]=cnt[j][i]-cnt[j-1][i]$）。对每个$f[i]$进行哈希，丢到一个$map$或者$set$里面，每次查询，如果当前的哈希值在$map$里面出现了，就更新答案；否则就将当前的哈希值放到$map$里面。时间$O(Nlog_2N)$。  
# 代码
```cpp
#include <map>
#include <cstdio>
#include <utility>
using namespace std;

typedef unsigned long long ull;
typedef long long LL;

const LL mod = 1e9 + 7;
const int base = 200003;
const int MAXN = 100005, MAXM = 35; 

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

map<ull, int> mp; 

ull h1[MAXN];
int pro[MAXN], cnt[MAXM][MAXN];
int head[MAXM], nxt[MAXN];
int N, M;

bool chk( const int l, const int r )
{
	int sta = cnt[0][r] - cnt[0][l - 1];
	for( int i = 1 ; i < M ; i ++ ) if( sta ^ ( cnt[i][r] - cnt[i][l - 1] ) ) return false;
	return true;
}

void add( const int indx, const int ID )
{
	nxt[ID] = head[indx];
	head[indx] = ID;
}

int main()
{
//	freopen( "testdata.in", "r", stdin );
	read( N ), read( M );
	for( int i = 1 ; i <= N ; i ++ )
	{
		read( pro[i] );
		for( int j = 0 ; j < M ; j ++ ) cnt[j][i] = cnt[j][i - 1] + bool( pro[i] & ( 1 << j ) );
	}
	for( int i = 0 ; i <= N ; i ++ )
		for( int j = 1 ; j < M ; j ++ )
			h1[i] = h1[i] * base + ( cnt[j][i] - cnt[j - 1][i] + N );
	mp.clear();
	mp[h1[0]] = 0;
    //预先将0位置也放到map里面
	int res = 0;
	for( int i = 1 ; i <= N ; i ++ )
	{
		if( mp.find( h1[i] ) != mp.end() ) 
			res = MAX( res, i - mp[h1[i]] );
        //如果当前哈希值可以找到就不需要将当前的下标放到map里面，必然不优
		else 
			mp[h1[i]] = i;
	}
	write( res ), putchar( '\n' );
	return 0;
}
```

---

## 作者：huadongf (赞：0)

类似前缀和。每位分别做前缀和。然后减去第一位的数。每位均相同则表示区间可取。

```cpp
 1 #include <cstdio>
 2 #include <cstring>
 3 #include <algorithm>
 4 #include <set>
 5 #define inc(i,j,k) for(int i=j;i<=k;i++)
 6 #define maxn 100010
 7 using namespace std;
```
8
```cpp
 9 inline int read(){
10     char ch=getchar(); int f=1,x=0;
11     while(ch<'0'||ch>'9'){if(ch=='-')f=-1; ch=getchar();}
12     while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
13     return f*x;
14 }
15 int sum[maxn][50],n,k,ans;
16 struct nd{
17     int id; int num[50];
18     bool operator < (const nd &a)const{inc(i,1,k-1)if(num[i]!=a.num[i])return num[i]<a.num[i]; return 0;}
19 };
20 multiset<nd>st; nd a;
21 int main(){
22     n=read(); k=read();
23     inc(i,1,n){
24         int x=read(); inc(j,1,k)sum[i][j]=sum[i-1][j]; for(int j=k-1;j>=0;j--)if(x&(1<<j))sum[i][j+1]++;
25     }
26     inc(j,1,k-1)a.num[j]=0; a.id=0; st.insert(a);
27     inc(i,1,n){
28         inc(j,1,k-1)a.num[j]=sum[i][j]-sum[i][j+1]; a.id=i;
29         multiset<nd>::iterator sti=st.find(a); if(sti==st.end())st.insert(a);else{
30             ans=max(ans,i-sti->id);
31         }
32     }
33     printf("%d",ans); return 0;
34 }
```

---

## 作者：kczno1 (赞：0)

一开始我以为题意<=>求区间和mod(1<<m-1)=0的最长区间

用前缀和表示就是(s[r]-s[l-1]) mod (1<<m-1)=0，<=>s[r]=s[l-1](mod (1<<m-1))

于是一遍哈希后一遍找一下就好了。

然而我错了。区间和mod(1<<m-1)=0是肯定满足的，但不止满足这一条。

例如1+10+10+10=111就不行。

所以得记录每一位的个数。

但哈希仍然可用原来的。（我竟然是当前最优解）

···pascal








```cpp
```
const p=10000007;
type arr=array[0..30] of longint;
var
 n,m,i,j,num,ans,a:longint;
 s:array[0..100000] of int64;
 r:array[0..100000] of arr;
 t:array[0..p] of longint;
 l:array[1..100000,1..2] of longint;
procedure chmax(var x:longint;y:longint);
begin
 if x<y then x:=y;
end;
procedure jia(x:longint);//加入第i位
begin
 inc(num);
 l[num,2]:=t[s[x] mod p];l[num,1]:=x;
 t[s[x] mod p]:=num;
end;
function ok(var x,y:arr):boolean;//判断是否相等
var i:longint;
begin
  for i:=1 to m do
  if x[i]<>y[i] then exit(false);
  exit(true);
end;
function find(x:longint):longint;//找第i位
var i:longint;
begin
 i:=t[s[x] mod p];
 while i<>0 do
 begin
  if s[l[i,1]]=s[x] then
  if ok(r[l[i,1]],r[x]) then exit(l[i,1]);
  i:=l[i,2];
 end;
 exit(n+1);
end;
function yi(var a:arr):boolean;//是不是每位都是一（同时是的话减掉）
var i:longint;
begin
 for i:=1 to m do
 if a[i]=0 then exit(false);
 for i:=1 to m do
  dec(a[i],1);
 exit(true);
end;
begin
 assign(input,'1.in');reset(input);assign(output,'1.out');rewrite(output);
 read(n,m);
 for i:=1 to n do
 begin
  read(a);  s[i]:=s[i-1]+a;
  for j:=1 to m do begin r[i,j]:=r[i-1,j]+a and 1;a:=a>>1; end;
  if s[i]>=(1<<m-1) then
  if yi(r[i]) then
   dec(s[i],1<<m-1);
 end;
 for i:=n-1 downto 0 do jia(i);//因为s[r]-s[l-1]中l的范围是1..n
 for i:=n downto 1 do
  chmax(ans, i-find(i) );
 writeln(ans);   close(output)
end.

```cpp

---

