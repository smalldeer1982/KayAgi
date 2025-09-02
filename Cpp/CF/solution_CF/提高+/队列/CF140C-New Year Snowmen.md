# New Year Snowmen

## 题目描述

As meticulous Gerald sets the table and caring Alexander sends the postcards, Sergey makes snowmen. Each showman should consist of three snowballs: a big one, a medium one and a small one. Sergey's twins help him: they've already made $ n $ snowballs with radii equal to $ r_{1} $ , $ r_{2} $ , ..., $ r_{n} $ . To make a snowman, one needs any three snowballs whose radii are pairwise different. For example, the balls with radii $ 1 $ , $ 2 $ and $ 3 $ can be used to make a snowman but $ 2 $ , $ 2 $ , $ 3 $ or $ 2 $ , $ 2 $ , $ 2 $ cannot. Help Sergey and his twins to determine what maximum number of snowmen they can make from those snowballs.

## 样例 #1

### 输入

```
7
1 2 3 4 5 6 7
```

### 输出

```
2
3 2 1
6 5 4
```

## 样例 #2

### 输入

```
3
2 2 3
```

### 输出

```
0
```

# 题解

## 作者：lqhsr (赞：13)

来一篇舒服的题解

这也是我退役前最后一篇题解啦

闲话少说我们开始思考这题

**一句话题意:给你n个数,从中尽可能多的选出三元组满足三个数都不相同,最后按照降序顺序输出这些三元组**

看完题目我们可以很自然地想到**贪心算法:**

## step1:去重

因为题目要求三个数互不相同 , 所以我们不能把所有数独立的看待 **(因为可能会选到重复的数)**

但我们注意到$a_i$的范围是$1e9$

**不能直接开桶存**

于是我们用map哈希一下 ~~(STL大法好)~~,**把这是第几个不同的数作为哈希的值**

记得顺便统计该种元素出现的次数

## step2:贪心

众人皆知,这题的贪心策略是**从所有数中选出三个出现次数最多的数,循环这个操作知道剩下的数少于3个**

**考虑到每次选完三个数之后会更改他们的出现次数,我们需要维护所有数的出现次数**

于是用$priority$$_$$queue$来完成这项操作

## step3:三元组排序

这也是本题的价值之一

**我们可以借鉴冒泡排序的思想,把最大的数一步一步放到最前面去**

于是就有了一下代码

```cpp
if(y<z)y^=z,z^=y,y^=z;
if(x<z)x^=z,z^=x,x^=z;
if(x<y)x^=y,y^=x,x^=y;
//注意三个if的顺序!!!
```

那三个异或是交换两个数

## 好了重点讲完放代码了

不要担心map常数大 ~~(人帅常数小)~~ ,整份代码用时3.99s内存14.43MB总长1.43KB

最优解第9页(总共20页)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ji,mem[100005][4];
int read(){
	int x=0;char ch=getchar();
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
struct node{
	int s,cnt;
}a[1000005];
map<int,int>mp;
priority_queue<pair<int,int> >dui;
bool cmp(node aa,node bb){return aa.cnt>bb.cnt;}
int main(){
	n=read();
	int ci;
	for(int i=1;i<=n;i++){
		ci=read();
		if(!mp[ci])++ji,mp[ci]=ji,a[ji].s=ci;
		++a[mp[ci]].cnt;
	}
	for(int i=1;i<=ji;i++)dui.push(make_pair(a[i].cnt,a[i].s));
	int ans=0;
	while(dui.size()>=3){
		int x=dui.top().second,cntx=dui.top().first;
		dui.pop();
		int y=dui.top().second,cnty=dui.top().first;
		dui.pop();
		int z=dui.top().second,cntz=dui.top().first;
		dui.pop();
		if(y<z)y^=z,z^=y,y^=z,cnty^=cntz,cntz^=cnty,cnty^=cntz;
		if(x<z)x^=z,z^=x,x^=z,cntx^=cntz,cntz^=cntx,cntx^=cntz;
		if(x<y)x^=y,y^=x,x^=y,cntx^=cnty,cnty^=cntx,cntx^=cnty;//运用冒泡的思想把三数从大到小排序
		mem[++ans][1]=x,mem[ans][2]=y,mem[ans][3]=z;
		if(cntx>1)dui.push(make_pair(cntx-1,x));
		if(cnty>1)dui.push(make_pair(cnty-1,y));
		if(cntz>1)dui.push(make_pair(cntz-1,z));
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++){
		printf("%d %d %d\n",mem[i][1],mem[i][2],mem[i][3]);
	}
}
```

---

## 作者：Itst (赞：12)

结论挺显然的，但是证起来不太好证。

这里补一个CF tutorial里面的证明。

首先声明：我们的贪心策略是每一次选择出现次数最多的三个位置将其$-1$。

先求出每种数的出现次数，设最后的答案为$k$。把出现次数$>k$的数的出现次数设为$k$，因为多于$k$的部分没用。此时所有数的出现次数之和$\geq 3k$，否则一定不会存在方案。

考虑用数学归纳法证明命题：对于一个出现次数序列$\{r_i\}$，如果满足$\forall i , r_i \leq k$且$\sum r_i \geq 3k$，则若每一次选择三个出现次数最多的数$-1$，一定可以操作$\geq k$次。

证明：

当$k=1$时命题显然成立；

当$k>1$时，根据鸽巢原理，必定存在至少三个数不为$0$，所以一定可以进行操作。

如果序列中存在至少$3$个数$=k$，那么我们只需要每一次操作这三个数即可达成要求，不难得知这一定不会比每一次选择三个最大的数的方案优，所以一定存在方案。

否则如果只存在$\leq 2$个数$=k$，操作三个最大的数，则可以变为新的出现次数序列$\{r'_i\}$满足$\forall i , r'_i \leq k-1$且$\sum r'_i \geq 3(k-1)$。根据归纳这样的出现次数序列的操作次数不少于$k-1$，所以当前序列选择三个最大的数操作的操作次数不少于$k$。

这样我们就证明了贪心策略的正确性。代码诸位都放了，我就不放了= =

---

## 作者：撤云 (赞：6)

### 广告
[点我食用效果更加](https://www.cnblogs.com/hbxblog/p/10150701.html)

#### 题目链接
[戳这](https://www.luogu.org/problemnew/show/CF140C)

贪心+优先队列，只要每次讲数量前三大的半径拿出来就好了，用优先队列维护一下


```cpp
#include<bits/stdc++.h>
#define rg register
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9') f=(c=='-')?-1:1,c=getchar();
    while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
    return f*x;
}
struct hh{
    int v,id;
    bool operator < (hh a) const {
        return v<a.v;
    }
}a[100001];
struct node {
    int x,y,z;
}c[100001];
int b[100001],d[100001];
priority_queue<hh> q;
int main(){
//	file("");
    int n=read(),tot=1,cnt=0;
    for(int i=1;i<=n;i++)
        a[i].v=read(),a[i].id=i;
    sort(a+1,a+1+n);
    a[0].v=-2147483647;
    for(int i=2;i<=n+1;i++){
        if(a[i].v!=a[i-1].v){
            hh now;
            now.id=a[i-1].v,now.v=tot;
            q.push(now),tot=1;
        }
        else
            tot++;
    }
    hh now;
    now=q.top();
//	printf("%d",now.v);
    int cc=0;
    while(q.size()>=3){
        hh now1,now2,now3;
        now1=q.top(),q.pop();
        now2=q.top(),q.pop();
        now3=q.top(),q.pop();
        now1.v--,now2.v--,now3.v--;
        if(now1.v) q.push(now1),cc++;
        if(now2.v) q.push(now2),cc++;
        if(now3.v) q.push(now3),cc++;
        c[++cnt].x=now1.id,c[cnt].y=now2.id,c[cnt].z=now3.id;
    }
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++){
        int l=min(c[i].x,min(c[i].y,c[i].z)),r=max(c[i].x,max(c[i].y,c[i].z));
        
        printf("%d ",r);
        if(c[i].x<r&&c[i].x>l)
            printf("%d ",c[i].x);
        if(c[i].y<r&&c[i].y>l)
            printf("%d ",c[i].y);
        if(c[i].z<r&&c[i].z>l)
            printf("%d ",c[i].z);
        printf("%d\n",l);
    }
    return 0;
}

```




---

## 作者：andysk (赞：4)

[Link](https://www.luogu.org/problem/CF140C)

一道堆的好题。

一看到题我先考虑的了DP，但是你看这个配对问题好像并不需要DP并且DP也不好处理。再观察构成雪人的条件是 $r_1 < r_2 < r_3$，就可以往用堆处理数据再贪心地选这方面的想。

具体的，我们可以把 $r_i$ 按照降序排序，相同半径的雪人球我们可以另开一个结构体存储，并且对于同一半径的雪人球我们要对他们统计数量。之后把这些去完重并且统计好数量的雪人球压进一个堆里，按照数量排序。

接下来我们每次取三个最多的雪人球，记为答案，如果这一半径的雪人球还有，我们就再次压进堆里。

就是这样。

证明可看我校神仙[神tst](https://www.luogu.org/blog/pengSiJin/solution-cf140c)的Blog，如有不懂可看上楼M_sea小姐姐和撤云的题解，也可以私信。

[The Code You Want Is Here!](https://tony102.xyz/index.php/2019/11/05/cf140c-new-year-snowmen/)



---

## 作者：yuzhechuan (赞：2)

贪心+优先队列

每次取出数量最多的三种球，合成一个答案，再把雪球数都-1再插回去，只要还剩下三种雪球就可以不断地合成

雪球数用优先队列维护

---

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,a[N],b[N],nm;
struct ball{
    int i,n; //i是离散数组中的编号,n为该种雪球的剩余数量
    inline bool operator < (const ball &nt) const{
        if(n==nt.n) return i<nt.i;
        return n<nt.n;
    }
};
struct ANS{
    int x,y,z;
    inline void change(){
        int tx=x,ty=y,tz=z;
        x=max(max(tx,ty),tz); //求最大
        z=min(min(tx,ty),tz); //求最小
        y=tx+ty+tz-x-z; //和减去最大最小就是中间值
    }
}ans[N/3];
priority_queue<ball> q;
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),b[i]=a[i];
    sort(b+1,b+1+n);
    sort(a+1,a+1+n);
    int un=unique(b+1,b+1+n)-b-1; //离散化
    for(int i=1;i<=n;){
        int j=i;
        while(j+1<=n&&a[j+1]==a[i]) j++; //找到该种雪球最右到哪
        int hn=j-i+1,id=lower_bound(b+1,b+1+un,a[i])-b; //该种雪球数量
        q.push((ball){id,hn});
        i=j+1; //跳过这一串相同的雪球
    }
    while(q.size()>=3){ //如果还有三种以上雪球
        ball alpha=q.top();q.pop(); //最多的
        ball beta=q.top();q.pop(); //次多的
        ball gamma=q.top();q.pop(); //第三多的
        alpha.n--;if(alpha.n) q.push(alpha); //都减去一个雪球
        beta.n--;if(beta.n) q.push(beta);
        gamma.n--;if(gamma.n) q.push(gamma);
        ans[++nm]=((ANS){b[alpha.i],b[beta.i],b[gamma.i]}); //合成答案
    }
    printf("%d\n",nm);
    for(int i=1;i<=nm;i++){
        ANS now=ans[i];
        now.change(); //整理一下答案的排序
        printf("%d %d %d\n",now.x,now.y,now.z);
    }
}
```

---

## 作者：Imiya (赞：0)

#### 思路
题目要求找出尽可能多组三个不同的数，因此我们看的是不同的数的个数，那么若拿一个出现次数多的数和出现次数少的数配对，则会导致若干次配对后，出现次数多的数还有，出现次数少的数没了，这会影响后续的配对，因此我们要尽量避免这种情况，于是贪心策略就出来了：**优先拿出现次数最多的三个数配对**。
#### 实现
因为我们取的是**当前**出现次数最多的数，因此我们可以先排序查重求出每个数的出现次数 $cnt$，然后以 $cnt$ 为键值存入优先队列。每次取出三个堆顶的数，记录答案后将三个数的 $cnt$ 自减，把自减后 $cnt>0$ 的数扔回优先队列即可。因为总共有 $\sum cnt=n$ 次取出和插入，所以复杂度是 $\mathcal{O}(n\times\log n)$。
#### 代码
```cpp
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
const int N=100010;
struct node{
    int val,cnt;
    bool operator<(const node&b)const&{
        return cnt<b.cnt;
    }
}a[N];
bool cmp(node x,node y){return x.val<y.val;}
priority_queue<node>q;
int n,ans[N][3],k;
void init(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i].val,
        a[i].cnt=1;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
        if(a[k].val!=a[i].val)a[++k]=a[i];
        else a[k].cnt++;
    n=k;
    k=0;
    for(int i=1;i<=n;i++)q.push(a[i]);
}
signed main(){
//    freopen("read.in","r",stdin);
    init();
    while(q.size()>=3){
        node t[3];
        k++;
        for(int i=0;i<3;i++)
            t[i]=q.top(),
            ans[k][i]=t[i].val,
            q.pop();
        for(int i=2;i>=0;i--)
            if(t[i].cnt>1)q.push((node){t[i].val,t[i].cnt-1});
    }
    cout<<k<<endl;
    for(int i=1;i<=k;i++)
        sort(ans[i],ans[i]+3),
        cout<<ans[i][2]<<' '<<ans[i][1]<<' '<<ans[i][0]<<endl;
    return 0;
}
```
--------------
修改（22.01.18）：两个月后意识到代码错了QAQ

---

## 作者：傅天宇 (赞：0)

[luogu's link](https://www.luogu.com.cn/problem/CF140C)

[CF's link](https://codeforces.com/problemset/problem/140/C)

#### 题意：

给定一个序列，每次取 $3$ 个不同的数，问最多能取几次。

#### Solution：

贪心想到每次取的时候都取当前次数最多的那 $3$ 个数。用优先队列 priority_queue 维护即可。

注意一开始还需要离散化下原序列。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-11-15 18:41:25 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-11-15 19:13:09
 */
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
const int N=1e5+5;
int n,tot,a[N],Ans,Sort[5];
struct SnowBall{
	int R,Sum;
	bool operator <(const SnowBall x) const{
		return Sum<x.Sum;
	}
}SB[N];
struct Answer{
	int S,M,L;
}Answer[N];
priority_queue<SnowBall>q;
int main(){
	n=read();
	FOR(i,1,n) a[i]=read();
	sort(a+1,a+1+n);
	FOR(i,1,n){
		if(a[i]!=a[i-1]){
			SB[++tot].R=a[i];
			SB[tot].Sum=1;
		}
		else SB[tot].Sum++;
	}
	FOR(i,1,tot) q.push(SB[i]);
	while(q.size()>=3){
		SnowBall A=q.top();q.pop();
		SnowBall B=q.top();q.pop();
		SnowBall C=q.top();q.pop();
		Ans++;
		Answer[Ans].S=A.R;A.Sum--;
		Answer[Ans].M=B.R;B.Sum--;
		Answer[Ans].L=C.R;C.Sum--;
		if(A.Sum!=0) q.push(A);
		if(B.Sum!=0) q.push(B);
		if(C.Sum!=0) q.push(C);
	}
	write(Ans);puts("");
	FOR(i,1,Ans){
		Sort[1]=Answer[i].S;
		Sort[2]=Answer[i].M;
		Sort[3]=Answer[i].L;
		sort(Sort+1,Sort+4);
		write(Sort[3]);putchar(' ');
		write(Sort[2]);putchar(' ');
		write(Sort[1]);putchar(' ');
		puts("");
	}
    return 0;
}
```



---

## 作者：C20210114卢思吉 (赞：0)

这道题其实吧，~~水，我们教练说过，不要看标签，这只是CSP第一题的题目~~

思路嘛，priority_queue和贪心，就这样，很水
这是代码

~~还有，一定要在cf上交，不然……可以看一下提交记录，有几个人的代码回来了~~
```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 1e6 + 5;
 
inline int read(){
	int k = 0,f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if (ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		k = k * 10 + ch - '0';
		ch = getchar();
	}
	return k * f;
}
 
inline void write(int x){
	if (x < 0){
		putchar('-');
		x = -x;
	}
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
 
struct node{
	int cnt,num,id;
	node(){}
	node(int Cnt,int Num){
		cnt = Cnt,num = Num;
	}
	bool operator <(const node& a) const{
		return cnt < a.cnt;
	}
}a[MAXN];
 
priority_queue <node> q;
int cnt = 1;
int ans;
 
struct ball{
	int big,mid,sma;
}k[MAXN];
 
bool cmp(node x,node y){
	return x.num < y.num; 
}
 
int main(){
	
	int n;
	n = read();
	
	for (int i = 1; i <= n ; i++) a[i].num = read();
	
	sort(a + 1,a + 1 + n,cmp);
	
	for (int i = 1; i <= n; i++){
		if (a[i].num != a[i + 1].num){
			q.push(node(cnt,a[i].num));
			cnt = 1;
		} 
		else cnt++;
	}
 
	if (q.size() < 3){
		printf("0");
		return 0;
	}
	
	while(q.size() >= 2){
		node x = q.top();q.pop();
		node y = q.top();q.pop();
		node z = q.top();q.pop();
		x.cnt--,y.cnt--,z.cnt--;
		k[++ans].big = x.num;
		k[ans].mid = y.num;
		k[ans].sma = z.num;
		if (x.cnt)	q.push(node(x.cnt,x.num));
		if (y.cnt)	q.push(node(y.cnt,y.num));
		if (z.cnt)	q.push(node(z.cnt,z.num));
	}
	
	write(ans);
	putchar(10);
	
	for (int i = 1 ; i <= ans ; i++){
		int m[5];
		m[1] = k[i].big;
		m[2] = k[i].mid;
		m[3] = k[i].sma;
		sort(m + 1,m + 4);
		printf("%d %d %d\n",m[3],m[2],m[1]);
	}
	return 0;
}
```


---

## 作者：AcerMo (赞：0)

### 优先队列好题

不难发现，每次取最多的几个雪球能保证凑出来的雪人最多，然后我们就先离散化一下，然后封装丢到优先队列里，每次取出队首的三个，将数量各自减一 ，表示凑了一个雪人，然后将数量大于一的再丢回去，直到剩余种数小于3为止，因为这时就凑不出来了

代码
```cpp
//By AcerMo
#include<queue>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int M=100500;
int n,a[M],b[M],c[M];
struct emm
{
	int v,id;
	bool friend operator < (emm a,emm b)
	{
		return a.v<b.v;
	} 
}ad;
struct an{int a,b,c;}e[M];
priority_queue<emm>q;
inline int read()
{
	int x=0;char ch=getchar();
	while (ch>'9'||ch<'0') ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;	
}
signed main()
{
	n=read();int cnt=0,s=0,tot=0;
	for (int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for (int i=1;i<=n;i++)
	if (a[i]==a[i-1]) b[cnt]++;
	else b[++cnt]++,c[cnt]=a[i];
	for (int i=1;i<=cnt;i++)
		ad.id=c[i],ad.v=b[i],q.push(ad);
	if (q.size()<3) return puts("0"),0;
	while (q.size()>=3)
	{
		emm x=q.top();q.pop();
		emm y=q.top();q.pop();
		emm z=q.top();q.pop();
		s++;x.v--;y.v--;z.v--;
		e[++tot].a=x.id;e[tot].b=y.id;e[tot].c=z.id;
		if (e[tot].a<e[tot].b) swap(e[tot].a,e[tot].b);
		if (e[tot].a<e[tot].c) swap(e[tot].a,e[tot].c);
		if (e[tot].b<e[tot].c) swap(e[tot].b,e[tot].c);
		if (x.v>0) q.push(x);
		if (y.v>0) q.push(y);
		if (z.v>0) q.push(z);
	}
	printf("%d\n",s);
	for (int i=1;i<=tot;i++)
	printf("%d %d %d\n",e[i].a,e[i].b,e[i].c);
	return 0;
}
```

---

