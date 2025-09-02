# 不成熟的梦想家 (未熟 DREAMER)

## 题目背景

**どんな未来かは 誰もまだ知らない**

**那是个任谁也不会知晓的未来**

**でも楽しくなるはずだよ**

**但应该会充满乐趣吧**

**みんなとなら乗りこえられる**

**只要大伙儿同在 就能跨越难关**

**これからなんだねお互いがんばろうよ**

**现在才正要开始 彼此互相加油吧**

**どんな未来かは 誰もまだ知らない**

**那是个任谁也不会知晓的未来**

**でも楽しくしたホントに**

**不过真心期望能够充满着乐趣**

**みんなとなら無理したくなる**

**只要大伙儿同在 就会想将顾虑抛诸脑后**

**成長したいなまだまだ未熟DREAMER**

**愿能有所成长 如今还只是尚未成熟的梦想家**

 ![](https://cdn.luogu.com.cn/upload/pic/4493.png) 

Aqours的成员终于到齐了。


今天，是我们全员在一起的第一场演唱会。


大家都好好练习过了，相信一定会表现得很出色的。


不过，每个人的唱功也要尽量地接近才可以呢，如果太突出或者太落后，也是会影响表现的样子。


所以我们从隔壁的学园都市借来了一个发明，可以改变我们成员的唱功呢。


## 题目描述

我们Aqours的成员共有N+1人，他们会列成一队。

他们的唱功以A[0]到A[N]表示，A[i]$(0\le i \le N)$均给出。

学园都市的机器可以改变队列中连续多个成员的唱功值，并将其加上一个数Z，当然当Z是负数的时候就变成减去了。

我打算一共使用这个机器Q次，每次把第X到第Y号（$1\le X,Y\le10^6$）的成员都加上Z点唱功值。

而我们队伍的魅力值B，是这么算的：

一开始B=0，然后从第1号到第N号成员，

- 当$A_{i-1}<A_i$：$B = B-S\cdot|A_{i-1} - A_i|$
- 当$A_{i-1}>A_i$：$B = B+T\cdot|A_{i-1} - A_i|$
其中S和T是LoveLive组委会给我们的常数。

果然，我是バカチカ（笨蛋千歌）呢，所以作为领导我永远排在队伍的开头，唱功永远是0，机器也不会改到我头上呢。

你能帮我们算算，我**每次**使用完这个机器之后，成员的魅力B是多少吗？


## 说明/提示

30% 的数据 $N,Q\le 2000$,

另外20% 的数据 $S=T$

100%的数据 $N,Q\le 200000$；$1\le S,T,A_i\le10^6$；$|Z|\le 10^6$
请注意可能需要使用int64，cin/cout可能超时。

样例解释：

第一次变化后，

A 0 6 3 4 6

B -12 -3 -5 -9


#### 以下是彩蛋

没有。

哪来的那么多彩蛋？


## 样例 #1

### 输入

```
4 3 2 3
0
5
2
4
6
1 2 1
3 4 -3
1 4 2
```

### 输出

```
-9
-1
-5
```

# 题解

## 作者：lin_toto (赞：46)

# 洛谷三月月赛R1·官方题解 T3


#### 本题标程请见题目页面下方的标程部分。


### 1. 解析

本题的正解是O(n)算法。每次对于一个区间的唱功值的改变，**不会导致区间内的值相对大小的改变**。

因此对于B值，我们每次只需要**维护X、Y两个节点上的变更**就好了。

我本人的做法是预处理出f[i] = A[i]-A[i-1]，并通过f数组计算出初始的B值，每次在区间上增加Z的时候，先撤销之前f[X]和f[Y]对B值的贡献，计算出新的f[X]和f[Y]，然后同时更新B值。


### 2. 出题事故

本来应该70分给20万的数据，100分给100万。

结果因为一些出题组沟通上的问题，变成了并没有卡n\*logn的解法。

今天看到有很多人用奇奇怪怪的做法水过，各种树状数组等。


#### 本题标程请见题目页面下方的标程部分。


---

## 作者：顾z (赞：18)


# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

这题就是$JOI\ 2017$焚风现象啊 qwq

首先,这是一个**差分模板题**,不过应该不是很容易看出来.

涉及到了**区间修改与单点查询**.(我相信有人会写数据结构的.

但是这里的单点查询就是一个固定的点$n$。

#### 首先考虑为什么可以差分去做?

　~~题目中的描述就暗示着我们进行差分啊.~~

首先我们发现了题目中的变化规则

> 当$A_{i-1}< A_i$,$B=B-S|A_{i-1}-A_i|$

> 当$A_{i-1}> A_i$,$B=B+T|A_{i-1}-A_i|$

而,每个人的唱功$A_i$已知,所以我们可以在输入的时候求出每个位置的唱功差.

#### 做法

根据唱功差,我们又可以求出每个位置的魅力值.由于$n$位置不会变,且一直为最后一个位置.

所以我们可以累加$ans$.(因为最后一个位置$n$永远不会变。

而且考虑到某一段区间的唱功变化,相对位置不会变,我们只需要考虑从起始位置$l$的魅力值变化,后面到达$r$的魅力值就随之变化.

这里需要注意的位置就是当$r==n$的时候,是不需要变化$r+1$位置的唱功与魅力值的.

即我们的$ans$是不需要改变的.而改变的话,需要考虑相对唱功的变化.我相信大家能懂的 qwq.

``代码``

```cpp
#include<cstdio>
#include<cctype>
#define int long long
#define R register
using namespace std;
inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}
int N,Q,S,T,ans,last,A[200008];
inline int calc(int x)
{
	return x>0 ? -S*x:-T*x;
}

signed main()
{
	in(N),in(Q),in(S),in(T);
	for(R int i=0,x;i<=N;i++)
	{
		in(x);
		A[i]=x-last;
		ans+=calc(A[i]);
		last=x;
	}
	for(R int i=1,x,y,z;i<=Q;i++)
	{
		in(x),in(y),in(z);
		ans-=calc(A[x]);A[x]+=z;ans+=calc(A[x]);
		if(y!=N)ans-=calc(A[y+1]),A[y+1]-=z,ans+=calc(A[y+1]);
		printf("%lld\n",ans);
	}
}
```

---

## 作者：ILLENIUM_DOOR (赞：14)

~~蒟蒻被 **long long** 坑了无数次~~

首先这道题的 $n\leq 200000$，所以只能用 $\operatorname{O(n)}$ 或 $\operatorname{O(nlogn)}$ 算法。

然后我们看到题目里的这一行：**改变队列中连续多个成员的唱功值，并将其加上一个数 Z**。

这，不就是对**差分数组**的应用描述吗？!

首先，题目里要算的 $B$，是由前后两个数的差决定的。

一开始时，前后两个数的差是固定的，所以可以算出开始时的 $B$。

然后我们可以发现，对于修改的区间 $[l,r]$，只有 $l$ 和 $r+1$ 两个地方的差会改变。

所以，我们就先减去原来它们的差算出的 $B$，再算出现在的 $B$，就可以了。

最后还要注意：**开 long long**。

时间复杂度：$\operatorname{O(n)}$。

~~我不会告诉你我对树状数组一窍不通才用的差分~~

其实，差分数组是一种对于修改区间很好的算法。

我们定义 $d_i$ 为前后两数的差，那么修改区间时，就只需要修改 $d_l$ 与 $d_{r+1}$ 的值。

最后遍历时，就用 $a_{i-1}+d_i$ 就是当前 $a_i$ 的值。

太方便了有没有？

然后，由于 $a_{n+1}$ 与 $a_n$ 的差是不可能变的，所以要对此进行特判。

附 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long d[200010];
long long n,q,s,t;
long long js(long long n){
    return n>0?-s*n:-t*n;//计算 B 
}
int main(){
    long long last=0; //注意赋初值 
    long long ans=0;
    cin>>n>>q>>s>>t;
    for(int i=0;i<=n;i++){
        long long now; 
        cin>>now;
        d[i]=now-last;//当前位与前一位的差 
        last=now;
        ans+=js(d[i]);
    }
    while(q--){
        long long x,y,z;
        cin>>x>>y>>z;
        ans-=js(d[x]);//去掉原来的值 
        d[x]+=z; 
        ans+=js(d[x]);//更新现在的值 
        if(y!=n) //特判末端点不等于 n 
		{
            ans-=js(d[y+1]);//同上 
            d[y+1]-=z;
            ans+=js(d[y+1]);
        }
        cout<<ans<<endl;
    }
    return 0;     
}
```

---

## 作者：fyx_Catherine (赞：11)

### 这道题虽然是黄题，但蒟蒻的我觉得还是有一些思维的。
## 看其他巨佬都是用差分做的，我还是给大家一篇用树状数组做的题解。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
long long read(){
	long long a=0,k=1;char c=getchar();
	while (!isdigit(c)){if (c=='-')k=-1;c=getchar();}
	while (isdigit(c)){a=a*10+c-'0';c=getchar();}
	return a*k;
}
long long n,q,s,a[500005],t,u,b,now,x,y,z,sd,ans;//不开long long见祖宗
long long lowbit (long long t){//lowbit函数 其实就是取出x的最低位1
    return t&(-t);
}
long long work(long long x){
    return x>0?-s*x:-t*x;
}
void update(long long x,long long k){
    for(long long i=x;i<=n;i+=lowbit(i))
    a[i]+=k;
    return;
}
long long getsum(long long x) {
    long long ans=0;
    for(long long i=x;i>=1;i-=lowbit(i))
    ans+=a[i];
    return ans;
}
//以上是标准的树状数组模板
int main() {
    n=read(),q=read(),s=read(),t=read();
    a[0]=read();//先读入a[0]
    ans+=work(a[0]);
    now=a[0];
    for(long long i=1;i<=n;i++) {
	u=read();
	ans+=work(u-now);//ans每次都要加上work(u-now)
	update(i,u-now);
        now=u;//更新now值
    }
    for(long long i=1;i<=q;i++) {//关键代码
        x=read(),y=read(),z=read();//在线访问
        long long a=getsum(x)-getsum(x-1);
	long long b=getsum(y+1)-getsum(y);
	update(x,z);
	if(y!=n)update(y+1,-z);
	long long c=getsum(x)-getsum(x-1);
	long long d=getsum(y+1)-getsum(y);
        ans-=work(a)-work(c);
        if(y!=n)ans-=work(b)-work(d);
	printf("%lld\n",ans);//输出答案
    }
    return 0;
}//完美结束
```
//码风丑陋，勿喷，也望大佬们多多指教

---

## 作者：Suuon_Kanderu (赞：9)

我来系统的讲解一下差分。

1. What is 差分？

	- 随便给一组数，就  **1,2,3,6,5** ,设这组数据为$A_i$。
   - 那么他的差分数组$C_i$就是 **-1,-1,-1,-3,1**,你可能发现了$C_{i} = A_{i-1} - A_{i} $ ($ A_1$为0)
2. 有什么用?  ----------可以维护$O(1)$区间修改,$O(N)$区间查询.
   
   - 首先我们举个例子 ~~(遇到不会的问题就找规律)~~,比如,把第 1  个数到 第3 个加1.
   - 手算一波 
   
  	| $A_i$ | $C_i$ | $\Delta C_i$ |
	| -----------: | -----------: | -----------: |
	| 2 | -2 | -1 |
	| 3 | -1 | 0 |
	| 4 | -1 | 0 |
	| 6 | -2 | +1 |
	| 5 | 1 |  0 |
        
  	-  聪明的 OIer 已经发现了$C_{1} -1,C_{3+1}+1$.
   - 难道规律就是$C_ {l } - num,C_{r+1} + num$?( l 为操作的左边界，r 为右边界)
   - 不急，再来找个规律从$A_2$到$A_3$加1（真理需要打表来证明）
   
   | $A_i$ | $C_i$ | $\Delta C_i$ |
	| -----------: | -----------: | -----------: |
	| 2 | -2 | -1 |
	| 4 | -2 | 0 |
	| 5 | -1 | 0 |
	| 6 | -1 | +1 |
	| 5 | 1 |  0 |
   
   - 诶，真的是 $C_ {l } - num,C_{r+1} + num$。
   
   - 什么，要证明，算了，别看蒟蒻写的了
   	
    $C_i = A_{i-1} - A_i$
    ，在一个序列中，执行每个操作时，我分成4种情况。
		
      1. $  A_{i-1} $和$ A_i $都没变，自然$C_{i}$也不会变。
      2. $  A_{i-1} $和$ A_i $同时加，$C_i$也不变。
      3. $  A_{i-1} + \Delta A'$ ， $ A_i $不变。
      	所以$C_i = A_{i-1}-A_i+ \Delta A'$
      4. $  A_{i} + \Delta A'$ ， $ A_{i-1} $不变。所以$C_i = A_{i-1} - (A_i + \Delta A') = A_{i-1}-A_i-\Delta A'$
      5. 当处于第三种情况时，一定位于 r+1 的位置，第四种情况位于 l 的位置
      - 单点查询就是$C_i - A_{i-1}$（移项）
      - 区间查询就是单点一直加
3. 扯正题，跟本题有关系吗？
	当然
    题目里有$A_{i-1} - A_i$，这是关键。
    
    - 首先我们预处理出魅力值的和$Sum$，so easy
    - 其次，我们对每一次修改，撤销上一次的痕迹，也就是让$Sum - C_{l}- C_{r+1}$
    - 同另一篇题解说的
    
    当$r==n$的时候,是不需要变化$r+1$位置的唱功与魅力值的.
    - 然后按照我刚才讲的维护。
    - 每一次输出 sum 就好了。
    
 代码没有，我的偶像 kkk 和 ltt 就是这样的。

---

## 作者：mysssss (赞：7)

这题基本是裸的树状数组 可以练练手

[树状数组模板题传送门](https://www.luogu.org/problemnew/show/P3368)

但也有很多其他方法（参考标程和其他大佬的题解）

但本质应该都是差不多的

# 差分

通过记录各个数与前一个数的差

然后通过操作不断更新差值

这题要求的魅力值看似每次都要变动很大

其实如果区间内每个值都同时增减 他们的差显然是不会变的

而且两个数谁大谁小的状态也是不变的

故会变的只有变动区间的区间首和区间末和各自前后数的关系

即

变动区间x到y

变动的为 （x-1与x）（y和y+1）  的关系

然后判断其正负再增减ans就可以了

因为我们只是变动局部的魅力值 所以我们要把ans也就是魅力值初始值算出来

### 还有一个要注意的点是

因为a[0]=0所以它集合中也是0

故会出现死循环的状况（集合代码中lowbit理解）

所以我们需在for前单独输出（看代码）

上代码
```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
ll n,q,s,a[500010],t,u,b,gangan,x,y,z,sd,ans;
inline long long  read()
{
    int x=0,f=0;
    char c=getchar();
    for(;c>'9'||c<'0';c=getchar())
    if(c=='-')
    f=1;
    for(;c>='0'&&c<='9';c=getchar())
    x=(x<<1)+(x<<3)+c-'0';
    return f?-x:x;
}//快读
ll  lowbit(ll k)
{
    return k&-k;
}//树状数组中求a[i]包含哪几个子差值（不理解的先去学树状数组吧）
ll check(ll x)
{
    return x>0? -s*x:-t*x;//改变魅力值据题意
}
void built(ll dep,ll k)
{
    for(register ll i=dep;i<=n;i+=lowbit(i))
    a[i]+=k;//差值
    return ;
}
ll query(ll x)
{
   ll ans=0;
    for(register ll i=x;i>=1;i-=lowbit(i))
    ans+=a[i];
    return ans;
}
int main()
{
    n=read(),q=read(),s=read(),t=read();
    a[0]=read();
    ans+=check(a[0]);
    gangan=a[0];
    for(ll i=1;i<=n;i++)
    {
          u=read();
          ans+=check(u-gangan);
          built(i,u-gangan);
          gangan=u;
    }
    //cout<<ans<<endl;
    for(ll i=1;i<=q;i++)
    {
        x=read(),y=read(),z=read();
        ll  a=query(x)-query(x-1);//求出改变前两数差值
		ll  b=query(y+1)-query(y);
        built(x,z);
        if(y!=n)//要注意当y==n时魅力值是不用变的
        built(y+1,-z);
       /* for(int i=0;i<=n;i++)
        cout<<query(i)<<" ";
		cout<<endl; */
        ll c=query(x)-query(x-1);
		ll d=query(y+1)-query(y);
        ans-=check(a)-check(c);//ans=ans-check(a)+check(c);
        //把之前改变的魅力值还原加上当前情况下的魅力值
        if(y!=n)//要注意当y==n时魅力值是不用变的
        ans-=check(b)-check(d);//同理可得
        printf("%lld\n",ans);
    }
    return 0;
}
```
还有：一定要记得开long long 不然只有40分

别问我怎么知道的 因为我开intWA了近20次

感谢阅读 还请多多指教

---

## 作者：风急风也清 (赞：3)

发现最近我好像一直在打差分的题解。

根据题目描述中的：每次把第 $X$ 个到第 $Y$ 个加上 $Z$ 时！

我们就可以瞬间想到，此题可以使用差分！

什么是差分？ 差分就是**批量**对区间整体操作。

方法：

在 $d_{x}$ 上加上 $z$ 会让后面的学生全部加上 $z$。

但这时把后面全部都加了，因此多算了，要减掉一节,也就是从 $d_{y+1}$ 后开始减去 $z$。

把两个综合起来就是我们所需要的差分大法公式，如果不大理解的，可以试着自己画图推导一下。

最后要注意一下样例的数据，是不是该开个 long long 了？

综上所述，整合代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long d[200005];
long long n,q,s,t,ans=0;
long long f(long long k)  //因为下面需要用到很多次这玩意，因此可整个函数。
{
    if(k<0) return -t*k;
    else return -s*k;
}
int main()
{
    long long b=0;
    cin>>n>>q>>s>>t;
    for(int i=0;i<=n;i++)
    {
        long long a;
        cin>>a;
        if(i>0) d[i]=a-b,b=a; //存每个数之间的差。    
        ans+=f(d[i]);  //将一开始的结果存一下。
    }
    for(int i=1;i<=q;i++)
    {
        long long x,y,z;
        cin>>x>>y>>z;
        ans-=f(d[x]);  //以下都是差分大法。
        d[x]+=z;
        ans+=f(d[x]);
        if(y<n)
    	  { ans-=f(d[y+1]); d[y+1]-=z; ans+=f(d[y+1]); }
        cout<<ans<<endl;
    }
    return 0;     
}
```


---

## 作者：lsj2009 (赞：3)

# 题意
给定一个长度为 $n$ 的序列 $a_1,a_2,...,a_{n-1},a_n$ ，对于 $q$ 次操作，每次把 $a_l,a_{l+1},...,a_{r-1},a_r$ 加上一个值 $val$,每次操作后输出：
$$\boxed{\sum_{i=2}^n\begin{cases}(a_i-a_{i-1})*-S\qquad a_{i-1}<a_i\\(a_{i-1}-a_i)*+T\qquad a_{i-1}>a_i\end{cases}}$$

很显然，这题区间修改、区间查询，是道~~线段树~~****差分****。
# 思路
## ~~歪解~~ STEP 1:
~~在出题人善意地没有卡常数的情况下~~，我们可以借鉴  [P3368](https://www.luogu.com.cn/problem/P3368)，用****树状数组 $+$ 差分****，每次维护****修改区间的两端点****即可，代码借鉴其它 dalao，这里就不给出了。
## 正解 STEP 2:
不过也说了，这是在****在出题人善意地没有卡常数的情况下****，毕竟 $Θ(n\log n)$ 算法是不稳的，那么既然可以用树状数组维护差分序列，自然也可以有 $Θ(1)$ 的方法操作：

首先，我们设 $ans$ 为****原****整只队伍的魅力值，则每次修改只需要将 $ans$ 减去****原来****的魅力值，再将 $ans$ 加上****后来****的魅力值就行了。
# AC Code:
```cpp
#include<bits/stdc++.h>
#define LL long long //注意LL 
using namespace std;
const int N=1e6;
LL d[N],x,last,ans,S,T,val;
int n,q,l,r;
LL f(int x) { //x这个点贡献的魅力值 
	return d[x]*(d[x]>0? -S:-T);
}
int main() {
	scanf("%d%d%lld%lld",&n,&q,&S,&T);
	for(int i=0;i<=n;i++)
		scanf("%lld",&x),d[i]=x-last,last=x; //模板 
	for(int i=0;i<=n;i++) ans+=f(i); //最初的魅力值 
	while(q--) {
		scanf("%d%d%lld",&l,&r,&val); //超级强迫症 //差分模板 
		if(l!=0) ans-=f(l+0),d[l+0]+=val,ans+=f(l+0); //修改左端点 
		if(r!=n) ans-=f(r+1),d[r+1]-=val,ans+=f(r+1); //修改右端点 
		printf("%lld\n",ans);
	}
	return 0;
}
```
------------
~~这名蒟蒻在一旁的角落里瑟瑟发抖~~。


---

## 作者：RedreamMer (赞：3)

### [$\texttt{P3655}$](https://www.luogu.com.cn/problem/P3655)

思路理清楚就很好做了，~~不需要树状数组吧。~~

### $\texttt{Meaning}$

给你一个序列 $A$ ，以及两个常数 $S$ 和 $T$ ，每次会对一个区间内的所有数都加一个值（可为负数），并输出
$$\sum_{i=1}^{i\leq n}X_i =\begin{cases}-S*(A_i-A_{i-1})&if(A_i>A_{i-1})\\-T*(A_i-A_{i-1})&if(A_i<A_{i-1})\end{cases}$$

（已经对原公式进行了变形）

### $\texttt{Solution}$

先 $O(N)$ 预处理出一开始的 $X$ 序列。

我们从公式里看到，每个 $X_i$ 只跟 $A_i$ 和 $A_{i-1}$ 有关，如果区间修改 $l$ 到 $r$ ，那么显然只有 $X_{l}$ $X_{r+1}$ 的值是改变的，最后这个区间修改操作就变成了修改这两个值的操作。

最后时间复杂度：$O(N+Q)$

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N=200010;
//const int M=20010;

int a,b,X,Y,last,x,y,z,s[N],sum;//这里我为了方便，作了一个差分数组s可以更加方便地修改

inline int f(int n) {//公式部分
	return n>0?-X*n:-Y*n;
}

signed main() {
//	freopen("in.in","r",stdin);
	scanf("%lld%lld%lld%lld",&a,&b,&X,&Y);
	for(int i=0;i<=a;i++) {
		scanf("%lld",&x);
		s[i]=x-last;//差分
		sum+=f(s[i]);
		last=x;
	}
	for(int i=1;i<=b;i++) {
		scanf("%lld%lld%lld",&x,&y,&z);
		sum-=f(s[x]);
		s[x]+=z;
		sum+=f(s[x]);
		if(y!=a) {//细节，若y=a时，那么对y+1进行修改是无效且越界的
			sum-=f(s[y+1]);
			s[y+1]-=z;
			sum+=f(s[y+1]);
		}
		printf("%lld\n",sum);
	}
	return 0;
}
```

### [$\color{blue}\texttt{My Blog}$](https://www.luogu.com.cn/blog/184549/)

---

## 作者：XL4453 (赞：2)

------------
**解题思路：**
	
观察题目中给出的算式可以发现，
对于一个区间中的若干点，
无论怎样加减，都不会改变整体贡献：

可以设加上（减去）的数为 $k$，
则对于区间中连续被加（减）到的 $A[i]$ 和 $A[i-1]$ ,
其结果为 $A[i] + k$ , 和 $A[i-1] + k$ ,
其中 $A[i],A[i-1]$ 的相对大小关系没有改变,
而 $|A[i]-A[i-1]|=|(A[i]+k)-(A[i]-k)|$ ,
故结果不变。
        
由此可以想到差分，
只需改变修改的两个边界即可计算出整个 $ans$ 的变化情况。
        
修改时,先取消原本两个点 $(x，y+1)$ 的影响（对应代码19、24行），然后更改并计算出新的影响。
        
------------
**坑点：**
		
当修改末尾为 $n$ 时，不能更改后面的点，
否则会因为 $S$ 、$T$ 不等造成错误（对应代码23行）。
        
开 $long long$。

------------
**代码：**

```cpp
#include<cstdio>
using namespace std;
long long num[200005],n,m,S,T,x,y,z,ans;
void calc(long long x,int f){
	if(x>0)ans+=f*S*x;
	else ans+=f*T*x;
}
int main(){
	scanf("%lld%lld%lld%lld",&n,&m,&S,&T);
	S=-S;T=-T;
	for(int i=0;i<=n;i++){
		scanf("%lld",&x);
		num[i]=x-y;y=x;
		calc(num[i],1);
	}
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&x,&y,&z);
		
		calc(num[x],-1);
		num[x]+=z;
		calc(num[x],1);
		
		if(y!=n){
			calc(num[y+1],-1);
			num[y+1]-=z;
			calc(num[y+1],1);
		}
		
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

