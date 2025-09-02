# New Product

## 题目背景

**一个经商的神奇故事……**

(善意提醒：注意时限！）


## 题目描述

LiM 有一家手工糕点店，因为糕点既实惠又好吃，于是积累了 $P$ 个常客（$P$ 为质数）。

每次这家店出 New Product（新品）的时候，都会做很多个，这 $P$ 个人都会支持，支持方法是：

**每个人买的数量都相同，而且买的总数要尽量多。**

这家店共有 $B$ 个工人，一分钟可以生产已经生产的数量的 $A$ 倍。

（注：一开始有一个已制作的 New Product 作为制作样品）

而当制作完毕，抢购（只考虑常客）完后：

**为了考虑工人们，最后要剩下正好 $B$ 个。**

下面给出已知条件，请你帮 LiM 算算最少要工作多长时间吧！

## 说明/提示



#### 样例 $1$ 解释：

有 $5$ 个常客，一分钟可以生产已生产的 $2$ 倍，有 $3$ 个工人。

则最小需要 $3$ 分钟（生产 $2^3=8$ 个）才能符合要求。

#### 样例 $2$ 解释：

有 $2$ 个常客，一分钟可以生产已生产的 $2$ 倍，有 $2$ 个工人。

因为不管是多长时间都会余下 $0$ 个，所以输出 `Couldn't Produce!`。


----------------------------------------------

说明：

LiM 不是工人哦！

对于每组 New Product，常客数量不同。

对于 $20\%$ 的数据，$T=1$，所有条件 $\leqslant 100$。

对于 $100\%$ 的数据，$T \leqslant 5000$，所有条件 $\leqslant 5 \times 10^4$。$P$ 为质数。

## 样例 #1

### 输入

```
1
5 2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
1
2 2 2```

### 输出

```
Couldn't Produce!```

# 题解

## 作者：NaCly_Fish (赞：10)

# 暴力出奇迹！！  
我是一个蒟蒻，我非常喜欢暴力算法，然后我就用暴力过了这道题。。  
枚举答案$\text{ans}$，从$1$~$p-1$，检查是否满足答案，如果满足就输出；如果枚举完了还没得出答案，输出无解就行了。。  

正确性证明也很简单，根据费马小定理，对于$a^n$模质数$p$的循环节长度为$p-1$(或者说是$φ(p)$)，所以$\text{ans}$肯定不会比这个大，于是这道题就做完了。。  

代码：  
其实不加循环展开和$\text{O}_3$也能过
```cpp
#pragma GCC optimize (3)
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 50003
#define ll long long
#define reg register
using namespace std;

bool vis[N];
int a,b,p,ans,cur;

inline void read(int &x){
	x = 0;
	char c = getchar();
	while(c<'0'||c>'9') c = getchar();
	while(c>='0'&&c<='9'){
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
}

void print(int x){
	if(x>9) print(x/10);
	putchar(x%10+'0');
}

inline void println(string str){
	int l = str.length();
	for(reg int i=0;i<l;++i) putchar(str[i]);
	putchar('\n');
}

void solve(){
	cur = 1;
	read(p),read(a),read(b);
	for(reg int i=0;;++i){
		if(cur==b){
			ans = i;
			break;
		}
		if(i>p){
			println("Couldn't Produce!");
			return;
		}
		cur = (ll)cur*a%p;
	}
	print(ans);
	putchar('\n');
}

int main(){
	reg int T,t;
	read(T);
	t = (T>>4)<<4;
	T &= 15;
	while(t){
		solve(),solve(),solve(),solve();
		solve(),solve(),solve(),solve();
		solve(),solve(),solve(),solve();
		solve(),solve(),solve(),solve();
		t -= 16;
	}
	while(T--) solve();
	return 0;
}
```

---

## 作者：皎月半洒花 (赞：6)

一道比较裸的$BSGS$。

但事实上，这个题有一堆坑点。以下就列举一下：

在对式子$$A^k \equiv B(\mod P~~)$$
进行$BSGS$时，

* 要判断是否合法，即

	* $1$、要判断$A$是不是$P$的倍数，**此处一定要判，因为当且仅当$A$和$P$互质的时候我们才可以拿费马小定理乱搞！**
    * $2$、判断$P-\sqrt P-1$是否非负。虽然光看式子的话他显然是不可能为负，但是代码中不一样。如果是负的话，不能进行$expow$

* 边界问题要注意。这个地方本人推荐$\sqrt P$**上取整**，然后$BSGS$内部选用$\leq$做边界而不是$<$。这个地方就牵扯到上面提到过的问题——当$\sqrt P$上取整之后，式子$P - \sqrt p -1$是可以$< 0$的，所以这个地方我们多加一倍就行了：

```cpp
	P = ceil(sqrt(p)), Q = expow(x, -P + 2 *(p - 1), p) ;
```
* 关于$map$的使用，笔者发现大家完全可以用$unordered\_map$替换$map$，毕竟我们只需要一个哈希表就够了。而$unordered\_map$是**真的快**！

剩下的大概就没啦~

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
#include<tr1/unordered_map>

#define LL long long

using namespace std ; 
using namespace tr1 ; int T ;
LL A, B, M, P, Q ; unordered_map <LL, LL> Hash ;

inline LL expow(LL a, LL b, LL p){
	LL res = 1 ;
	while (b){
		if (b & 1) 
			(res *= a) %= p ;
		(a *= a) %= p, b >>= 1 ;
	}
	return res % p ;
}
inline void bsgs(LL x, LL y, LL p){
	P = ceil(sqrt(p)), Hash.clear(), Q = expow(x, -P + 2 *(p - 1), p) ;
	//a ^ (p-1) = 1 (mod p) => Q = a^(-P) = a ^(-P + p -1) ;
	for (LL i = 1, j = 0 ; j < P ; ++ j, (i *= x) %= p) 
		if (!Hash.count(i)) Hash[i] = j ; // Push them into hash_table
	for (LL i = y, j = 0  ; j <= P ; ++ j, (i *= Q) %= p) 
		if (Hash.count(i)){ cout << Hash[i] + j * P << endl ; return ; }
	cout << "Couldn't Produce!" << endl ;
}
inline LL qr(){
    LL res = 0 ; char c = getchar() ; while (!isdigit(c)) c = getchar() ;
    while (isdigit(c)) res = (res << 1) + (res << 3) + c - 48, c = getchar() ;
    return res ;
}
int main(){
	cin >> T ;
	while (T --){
		M = qr(), A = qr(), B = qr() ;
		if ((!(A % M == 0 && B))) bsgs(A, B, M) ;
		else cout << "Couldn't Produce!" << endl ; 
	}
	return 0 ;
}
```

---

## 作者：zhylj (赞：6)

题意：求最小的$ans$使得$A^{ans}\equiv B\pmod P$

可以发现，$A^{ans} \mod P$的值总会出现循环，故枚举$ans$，使用数组记录$A^{ans}\mod P$

如果计算到已经出现过的值，则会回到之前计算的值，所以结束计算，输出无解

中途计算中若出现$A^{ans}\equiv B\pmod P$，输出当前的$ans$

$\rm AC$代码：$\rm(268ms / 2246KB)$

```
#include <bits/stdc++.h>

using namespace std;

const int MAXN=50005;

bool appeared[MAXN];//记录每个数是否出现过

int solve(int a, int b, int p)
{
	memset(appeared, 0, sizeof(appeared));
	int ans=0, x=1;
	for(;;++ans)//用ans累计答案
	{
		if(b==x) return ans;//如果b==x，则返回答案
		if(appeared[x]) break;
		appeared[x]=1;
		x=x*a%p;
	}
	return -1;
}

int main()
{
	ios::sync_with_stdio(false);
	int t, a, b, p;
	cin>>t;
	while(t--)
	{
		cin>>p>>a>>b;
		int ans=solve(a, b, p);
		if(ans!=-1) cout<<ans<<endl;
		else cout<<"Couldn't Produce!"<<endl;
	}
	return 0;
}

```

不是很懂上一个题解的做法，难度也很迷。。。

如果有$\rm Bug$，请私信我

---

## 作者：lao_wang (赞：4)

## 题意
我们读题可知有 $B$ 个厨师，每分钟生产上一次生产的 $A$ 倍，有 $P$ 个客人来买尽可能多了蛋糕（ $P$ 为素数）且最后需要剩余 $B$ 个给厨师，求时间。

我们就可以很容易的得出一个式子： $A^x\ \equiv B\ ( \bmod \ P) $

[模版](https://www.luogu.com.cn/problem/P3846)启动，这道题就做完了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std ;
int p , b , n , m , T ;
int ksm(int n,int m){
	int ans=1 , temp=n ;
	while(m){
		if(m&1)
			ans = ans*temp%p ;
		m >>= 1 ;
		temp = temp*temp%p ;
	}
	return ans ;
}
signed main(){
	cin >> T ;
	while(T--){
		map<int,int> mp ;
		scanf("%lld%lld%lld",&p,&b,&n) ;
		m = sqrt(p)+1 ;
		int temp=1 , ans=1 ;
		bool ant=1 ;
		for(int i=1;i<=m;i++){
			mp[ksm(b,i)*n%p] = i ;
		}
		temp = ksm(b,m) ;
		for(int i=1;i<=m;i++){
			ans = ans*temp%p ;
			if(mp[ans%p]){
				int t =  m*i-mp[ans] ;
				if(t==0&&n!=1) break ;  //这是一个坑 当t=0时只有一个样品
				ant = 0 ;
				printf("%lld",(t%p+p)%p) ;
				break ;
			}
		}
		if(ant)
			printf("Couldn't Produce!") ;
		printf("\n") ;
	}
	return 0 ;
}
```


---

## 作者：两年打铁 (赞：3)

一眼题面我们可以得到一个式子

设答案为$x$，则 ${A^x}\equiv{B}\pmod{P}$

那么这题就是裸的BSGS啦

然后我们来讲一蛤BSGS

对于${A^X}\equiv{B}\pmod{P}$
我们将$x$表示为$ik-j$的形式，其中$k=\left\lceil{\sqrt{P}}\right\rceil,i\in[0,k],j\in[0,k-1]$

这样就能表示所有的$P-1$以内的数。

那么为什么只要表示$P-1$以内的就行了呢，因为$P$是质数，所以由费马小定理可知超过$P-1$的$x$所得到的左边式子的值肯定在$P-1$之前被统计过了

接下来我们开始找答案。

很明显当左边的值等于右边的值答案就是可知的。

那么分别算出右边式子的所有值和左边式子的所有值。

当左边和右边有相同的值时，就是答案，然后查询可以直接开桶。

复杂度$O(\sqrt{P})$

```cpp
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define kong putchar(' ')
#define huan putchar('\n')
#define bug puts("QWQ")
#define pr putchar
#define int long long 
const int big=0x7fffffff;
using namespace std;
inline void read(int &x)
{
    x=0;char ch=getchar();int pd=1;
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}
inline void write(const int &x)
{
    char ggg[100];int s=0;int tmp=x;
    if(tmp==0){putchar('0');return;}
    if(tmp<0){tmp=-tmp;putchar('-');}
    while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
    while(s>0){putchar(ggg[--s]);}
}
inline void wrs(const int &x)
{
	write(x);
	putchar(' ');
}

inline void wrl(const int &x)
{
	write(x);
	putchar('\n');
}

const int N=2333;
int p,a,b;

int vis[233333];

inline int ksm(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)
		ans=(1ll*ans*x)%p;
		x=(1ll*x*x)%p;
		y>>=1;
	}
	return ans;
}



int bsgs()
{
	if(a%p==0||b%p==0)return -1;
	if(b==1)return 0;
	memset(vis,-1,sizeof(vis));
	int t=ceil(sqrt(p));
	int now=b%p;
	vis[now]=0;
	for(register int i=1;i<=t-1;++i)
	{
		now=1ll*now*a%p;
		if(vis[now]==-1)vis[now]=i;
	}
	now=ksm(a,t);
	if(vis[now]!=-1)
	{
		return t-vis[now];
	}
	for(register int i=1;i<=t;++i)
	{
		now=ksm(a,i*t);
		if(vis[now]!=-1)
		{
			return i*t-vis[now];
		}
	}
	return -1;
}

signed main()
{
	int T;
	read(T);
	while(T--)
	{
		read(p);
		read(a);
		read(b);
		int ans=bsgs();
		if(ans==-1)
		{
			puts("Couldn't Produce!");
			continue;
		}
		else wrl(ans);
	}
}
```



---

## 作者：123rrc (赞：1)

本篇题解略过了 BSGS 的实现，重点分析了本题的细节处理。

#### 前置知识

- 基础数论
- BSGS（Baby Step, Giant Step 算法），若有不会请移步 [模板题](https://www.luogu.com.cn/problem/P3846)。

#### 思路分析

看到 $P$ 为素数这个条件，猜测这是道数论题，于是大胆设未知数：

设工作了 $t$ 分钟，每个顾客买了 $x$ 个产品。显然题目要求 $t$ 的最小值。根据题意有 $A^t-Px=B$，移项得 $A^t=B+Px$。由于 $P$ 是素数，考虑两边对 $P$ 取模，得到这个式子：

$$A^t \equiv B \pmod P$$

由于 $P$ 是素数，于是 $A$ 与 $P$ 一定互素，可以直接用 BSGS 算法求出 $t$ 的最小值或报告无解。

---------------

**但是你以为这就完了？**

直接敲 BSGS 上去，你会得到 $48$ 分的 [好成绩](https://www.luogu.com.cn/record/175421589)。这是怎么回事？

考虑第 $2$ 组样例，扔进这份代码一测，应该报告无解的，可是输出了 $1$ ？？？

这说明有一些细节情况没有特判掉。

首先注意到题目中的一句话：

> 每个人买的数量都相同，而且买的总数要尽量多。

总数尽量多，说明 $x$ 要尽可能大，于是原式 $A^t=B+Px$ 就变成了被除数为 $A^t$，除数为 $P$ 的带余除法，商为 $x$，余数为 $B$。于是出现第一处细节：**要保证 $B \in [0,P-1]$，否则直接报告无解**。

仔细想想，BSGS 板子保证了 $A,B < P$，可是这题没有啊！于是出现第二处细节：**$A>P$ 时，要强制把 $A$ 对 $P$ 取模**。由于 $A,P$ 互素，这样不会影响结果。

可是这么操作的话，$A$ 可能会被模成 $0$，这是板子中没有出现的情况。仔细思考，$A \equiv 0 \pmod P$ 时，有：

$$ A^t \equiv \begin{cases}
1, t = 0 \\
0, t > 0
\end{cases} \pmod P $$

所以当 $B$ 等于 $0$ 时，显然 $t=1$ 是最优解，直接输出 $1$；既不等于 $1$ 也不等于 $0$ 时，报告无解；$B$ 等于 $1$ 的情况稍后讨论。

当 $B$ 等于 $1$ 时，无论 $A$ 为何值，由于题目中的一句话：

> （注：一开始有一个已制作的 New Product 作为制作样品）

所以出现了第三处细节：**只要 $B$ 为 $1$，不用工作就可以满足题目要求（剩下恰好 $1$ 个产品）。因此直接输出 $0$ 即可。**

**综上所述，我们应该以如下顺序进行特判：**

1. 判断 $B$ 是否属于 $[0,n-1]$，如果不属于，直接报告无解。
2. 判断 $B$ 是否等于 $1$，如果是，直接输出 $0$。
3. 把 $A$ 对 $P$ 取模，并判断 $A \bmod P$ 是否为 $0$。如果是，当 $B=0$ 是输出

以上所有操作完成后，运行 BSGS 算法并输出答案。

---------------------------------------

[AC 记录](https://www.luogu.com.cn/record/175419824)

AC Code（加了注释）：

BSGS 部分是直接从模板题搬运过来的，并且 long long 开得特别猛（我个人不喜欢用宏定义），所以代码可能较为丑陋，望各位 dalao 谅解。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,p;
long long ksm(long long a,long long b){ //快速幂
    long long base=a,ans=1ll;
    while(b){
        if(b&1){
            ans*=base;
            ans%=p;
        }
        base*=base;
        base%=p;
        b>>=1;
    }
    return ans;
}
long long bsgs(long long a,long long b){ //BSGS 算法模板，
//无解时返回 -1，否则返回最小的解
    map<long long,long long> mp;
    long long t=(int)sqrt(p)+1;
    for(long long i=0ll;i<t;i++){
        long long cur=(ksm(a,i)*b%p)%p;
        mp[cur]=i;
    }
    long long ans=2147483647,pre=ksm(a,t);
    for(long long i=0;i<=t;i++){
        long long cur=ksm(pre,i);
        if(mp.find(cur)!=mp.end()){
            long long j=mp[cur];
            if(i*t-j>0){
                ans=min(ans,i*t-j);
            }
        }
    }
    if(ans==2147483647){
        return -1;
    }
    return ans;
}
int main(){
    int t;
    cin>>t;
    //如果各位有什么东西开在了全局，切记下面这句话：
    //代码千万条，清空第一条。多测不清空，爆零两行泪！
    while(t--){
        cin>>p>>a>>b;
        a%=p; //可以提前取模，不影响结果
        if(b>=p){ //步骤 1
            cout<<"Couldn't Produce!"<<endl;
            continue;
        }
        if(b==1){ //步骤 2
            cout<<0<<endl;
            continue;
        }
        if(a==0){ //步骤 3
            if(b==0){
                cout<<1<<endl;
            }else{
                cout<<"Couldn't Produce!"<<endl;
            }
            continue;
        }
        //以下皆为模板操作
        long long as=bsgs(a,b);
        if(as==-1){
            cout<<"Couldn't Produce!"<<endl;
        }else{
            cout<<as<<endl;
        }
    }
    return 0;
}
```

-----------------

吐槽：

1. 产量指数爆炸是怎么做到的......
2. “注意时限”？时限不就是正常的 $1.00s$ 吗？？有什么好注意的？？？

---

## 作者：hanzhongtlx (赞：1)

~~从学习笔记上剥下来的东西当题解~~

$BSGS$ 是解决**离散对数问题**的，全称 $Baby\;Step\;Gaint\;Step$ (不是拔山盖世)，即求：  
$$a^x\equiv b\pmod{p}$$    
的最小整数解 $x$。    

但要保证 $p\in P$（质数集合）。   

那么我们可以发现$x$变化时得到的余数会出现循环节，长度大概是 $\left\lceil\sqrt{n}\right\rceil$ 的。  

那我们令 $m= \left\lceil\sqrt{n}\right\rceil$， 

就会存在常数 $u,v$ 使：  
$$a^{um+v}\equiv b\pmod{p}$$   
即：
$$a^{um}\equiv ba^{-v}\pmod{p}$$    
这样需要处理逆元，可有没有好点的方法呢？  

不妨设 $x=um-v$，   

我们可以知道：  
$$a^{um}\equiv ba^{v}\pmod{p}$$    

我们不妨枚举同余号任意一侧（下面代码是右边），存一下（这时要去重），然后枚举另一边，寻找一一对应关系即可。      

显然这时枚举两边的上界都是 $\sqrt{p}$ 的，这时是最小的。 

注意这里枚举的边界：$v$ 是 $[0,m),u$ 是 $(0,m]$（由于我们其实是把 $u$ 在本来正常想法上 $+1$）。    

如果有枚举一边得到的两对数有相同的对应值，那贪心的选用编号大的，另一边选编号小的，再二分找一下即可。 

然后要注意如果余数是 $1$，直接得 $0$ 就好了，不知道为啥算不出来。     

综上，复杂度是 $\mathcal O(\sqrt{p}\log\sqrt{p})=\mathcal O(\sqrt{p}\log p)$。   

（上面变量名很清奇......不要吐槽就好）   

```
#include"algorithm"
#include"iostream"
#include"cstring"
#include"cstdio"
#include"cmath"
using namespace std;

#define ll long long 
#define MAXN 200005
#define read(x) scanf("%lld",&x)

int t;
ll p,a,b;
int h;
struct num
{
    ll val;
    int id;
}op[MAXN];

bool cmp(num n,num m){if(n.val==m.val) return n.id>m.id;else return n.val<m.val;}

void get()
{
    ll now=b;
    for(int i=0;i<h;i++)
    {
        op[i+1].id=i,op[i+1].val=now;
        now=now*a%p;
    }
    sort(op+1,op+h+1,cmp);
    return;
}

int find()
{
    ll now,mi=1;
    for(int i=1;i<=h;i++) mi=mi*a%p;
    now=mi;
    for(int i=1;i<=h;i++)
    {
        int l=1,r=h,mid;
        while(l<r)
        {
            mid=(l+r)>>1;
            if(op[mid].val<now) l=mid+1;
            else r=mid;
        }
        if(op[l].val==now) return i*h-op[l].id;
        now=now*mi%p;
    }
    return -1;
}

void work()
{
    get();
    int rt=find();
    if(rt<0) puts("Couldn't Produce!");
    else printf("%d\n",rt);
}

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        read(p),read(a),read(b);
        a%=p;
        if(b==1){puts("0");continue;}
        if(b>=p||a==0){puts("Couldn't Produce!");continue;}
        h=ceil(sqrt(p));//注意是上取整
        work();
        memset(op,0,sizeof(op));
    }
    return 0;
}
```

---

## 作者：luxiaomao (赞：0)

## [P4028](https://www.luogu.com.cn/problem/P4028)

这题暴力能过为什么还有蓝啊。

## Problem

求关于 $x$ 的方程 $A^x \equiv B \pmod P$ 的最小自然数解。

## Solution

首先特判 $B=1$ 的情况，此时答案为 $0$，不多赘述。

不难发现，如果 $A$ 是 $P$ 的倍数，那么无解（每次乘上 $A$ 再模 $P$，剩下的糕点数量永远是 $0$）。

剩下的情况，由于 $P$ 是质数，考虑费马小定理。

费马小定理告诉我们，$\{1,2,\dots,p-1\}$ 中的每个数，都会在 $\{A^1,A^2,\dots,A^{p-1}\}\pmod p$ 这个序列中出现且仅出现一次。那么我们枚举指数 $x$，暴力跑 $(p-1)$ 次，找到符合题意的 $x$ 输出即可。

时间复杂度 $O(TP)$，可以通过。具体实现请看代码。

## Code

```cpp

#include<bits/stdc++.h>
using namespace std;

int T,p,a,b;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&p,&a,&b);
		if(b == 1)
		{
			printf("0\n");
			continue;
		}
		bool flag = 0;
		int x = 1;
		for(int i = 1;i < p-1;i++)
		{
			x = x*a%p;
			if(x == b)
			{
				printf("%d\n",i);
				flag = 1;
				break;
			}
		}
		if(!flag)printf("Couldn't Produce!\n");
	}
}
```

---

## 作者：lidagua1004 (赞：0)

这道题可以发现第 $x$ 分钟生产的数量为 $a^{x}$，所以每个顾客买了 $\lfloor \frac{a^{x}}{p} \rfloor$ 个。

等价于求 $a^{x}\equiv b\pmod p$。

于是我想到了 BSGS 算法。

[BSGS 模板题。](https://www.luogu.com.cn/problem/P3846)

[不会的看这里。](https://oi-wiki.org/math/number-theory/discrete-logarithm/)

OI-Wiki 上讲的已经十分清楚了，这里就不讲述了。

只不过有一点要注意：

使用 BSGS 是要注意 $a$ 和 $p$ 要互质，但是 $a$ 如果是 $p$ 的倍数的话要特判，这也很容易，只要 $b$ 不是 $0$ 就不行。

AC code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define gcd __gcd 
using namespace std;
unordered_map<int,int> mp;
int read(){//快读
	int s=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){s=(s<<3)+(s<<1)+ch-48;ch=getchar();}
	return s*f;
}
void write(int x) {//快写
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
int qpow(int a,int b,int p){//快速幂
	int ans=1,base=a;
	while(b){
		if(b&1) ans=ans*base%p;
		base=base*base%p;
		b>>=1;
	}
	return ans%p;
}
int bsgs(int a,int b,int p){//BSGS算法
	mp.clear();
	int k=ceil(sqrt(p));//向上取整
	b%=p;
	for(int i=1;i<=k;i++) b=b*a%p,mp[b]=i;
	a=qpow(a,k,p),b=1;
	for(int i=1;i<=k;i++){
		b=b*a%p;
		if(mp[b]) return (i*k-mp[b]+p)%p;
	}
    return -1;//不行就返回-1
}
int slove(){
	int a,b,p;
	p=read(),a=read(),b=read();
	if(a%p==0&&b!=0) return -1;//特判
	return bsgs(a,b,p);//求BSGS
}
signed main(){
	int t;cin>>t;
    while(t--){
        int ans=slove();
        if(ans==-1) puts("Couldn't Produce!");
        else write(ans),puts("");
    }
	return 0;
}

---

## 作者：5k_sync_closer (赞：0)

题意：求 $A^x\equiv B\pmod P$ 的最小正整数解。

BSGS 板子。

由欧拉定理 $a^b\equiv a^{b\bmod\varphi(p)}\pmod p$ 可知，$a^x$ 有周期 $\varphi(p)=p-1$，即原方程在 $[1,p)$ 上一定有解。

构造 $x=i\lceil\sqrt p\rceil-j|i,j\in[1,\lceil\sqrt p\rceil]$，容易发现 $x$ 可以取遍 $[1,p)$，则

$$
\begin{aligned}
A^{i\lceil\sqrt p\rceil-j}&\equiv B\pmod P\\
A^{i\lceil\sqrt p\rceil}&\equiv B^j\pmod P
\end{aligned}
$$

枚举 $B^j$ 存到哈希表里，枚举 $A^{i\lceil\sqrt p\rceil}$ 在哈希表中查询即可。

```cpp
#include <cmath>
#include <cstdio>
#include <unordered_map>
using namespace std;
int T, M, a, b, q;int Q(int x, int y)
{
	int z = ceil(sqrt(M));long long B = y, T = 1;unordered_map<int, int> H;
	for(int i = 1;i <= z;++i) H[B = B * x % M] = i;for(int i = B = 1;i <= z;++i) B = B * x % M;
	for(int i = 1;i <= z;++i) if(H[T = T * B % M]) return i * z - H[T];return -1;
}
int main()
{
	scanf("%d", &T);while(T--)
	{
		scanf("%d%d%d", &M, &a, &b);
		if(!(a % M) || b >= M) puts("Couldn't Produce!");
		else if(~(q = Q(a, b))) printf("%d\n", q);
		else puts("Couldn't Produce!");
	}
	return 0;
}
```


---

## 作者：emptysetvvvv (赞：0)

## $\mathrm{BSGS}$
### 背景
小萌新$\varnothing$被嫌弃竞赛和文化课太菜了，她很伤心，她伤心的时候喜欢疯狂地写博客。

### 思路
- 题面说的很模糊，观察样例可知，$x$分钟后产品数为$A^{\displaystyle x}$。$p$位常客尽可能多的买，就是他们会一直买直到剩下的产品数小于$p$个，要求剩下$B$个，也就是说$A^{\displaystyle x}\equiv B\pmod p$。

- 综上，题意为求方程$A^{\displaystyle x}\equiv B\pmod p$的最小非负整数解。

- 由费马小定理$A^{\displaystyle p-1}\equiv1\pmod p$可知$A^{\displaystyle p-1+k}\equiv A^{\displaystyle k}\pmod p$，所以最终的解$x\in[0,p-1]$。

>我会暴力！！！反正这题数据不大，直接枚举$x$从$0$到$p-1$，复杂度$O(p)$不吸氧也能过！！

>有优秀一点的做法吗？$\mathrm{BSGS}$！！专门解决这类问题的算法！！

- 令$q=\lceil\displaystyle \sqrt p\rceil$，

- 设$x=iq-j$，$j\in[0,q-1]$，则原方程化为$A^{\displaystyle iq}\equiv B\cdot A^{\displaystyle j}\pmod p$.

- $O(\sqrt p)$枚举左边的值，$O(\sqrt p)$枚举右边的值，看看有没有相等的，有的话$iq-j$就是解了。

- 这就是$\mathrm{BSGS}$的核心思想，复杂度$O(\sqrt p)$。

- 这里讲的很粗略，详细的说明还请移步我的博客[BSGS及其扩展](https://www.luogu.org/blog/emptyset/bsgs-ji-ji-kuo-zhan)

### 代码

```cpp
#include <map>
#include <cmath>
#include <iostream>
using namespace std;
map<int,int> Hash;
int kase, A, B, p;
int power(int x, int k, int mod) {
    int ans = 1;
    while(k) {
        if(k & 1) ans = ans * x % mod;
        x =  x * x % mod, k >>= 1;
    }
    return ans;
}
int BSGS(int A, int B, int p) {
    if(A % p == 0) return -1;
    if(B == 1) return 0;
    const int q = ceil(sqrt(p));
    long long temp = B % p;		//枚举 j
    for(int j = 1; j <= q; j++) {
        temp = temp * A % p;
        Hash[(int)temp] = j;
    }
    A = power(A, q, p), temp = 1;		//枚举 i
    for(int i = 1; i <= q; i++) {
        temp = temp * A % p;
        if(Hash[(int)temp]) return ((i * q - Hash[temp]) % p + p) % p; 
    }
    return -1;
}
int main() {
    ios :: sync_with_stdio(false);
    cin >> kase;
    while(kase--) {
        Hash.clear(); 
        cin >> p >> A >> B;
        int ans = BSGS(A, B, p);
        if(~ans) cout << ans << endl;
        else cout << "Couldn't Produce!" << endl;
    }
    return 0;
}
```

---

