# [USACO18FEB] Rest Stops S

## 题目描述

Farmer John 和他的私人教练 Bessie 正在攀登温哥华山。为了他们的目的（以及你的目的），这座山可以表示为一条长度为 $L$ 米的长直步道（$1 \leq L \leq 10^6$）。Farmer John 将以每米 $r_F$ 秒的恒定速度徒步（$1 \leq r_F \leq 10^6$）。由于他正在锻炼耐力，他不会在途中休息。

然而，Bessie 被允许在休息站休息，她可能会在那里找到一些美味的草。当然，她不能随便停下来！步道上有 $N$ 个休息站（$1 \leq N \leq 10^5$）；第 $i$ 个休息站距离步道起点 $x_i$ 米（$0 < x_i < L$），并且有一个美味值 $c_i$（$1 \leq c_i \leq 10^6$）。如果 Bessie 在第 $i$ 个休息站休息 $t$ 秒，她会获得 $c_i \cdot t$ 的美味单位。

当不在休息站时，Bessie 将以每米 $r_B$ 秒的固定速度徒步（$1 \leq r_B \leq 10^6$）。由于 Bessie 年轻且健康，$r_B$ 严格小于 $r_F$。

Bessie 希望最大化她摄入的美味草量。但她担心 Farmer John；她认为如果在徒步的任何时刻她在步道上落后于 Farmer John，他可能会失去继续前进的动力！

请帮助 Bessie 找到在确保 Farmer John 完成徒步的情况下，她能获得的最大总美味单位。

## 说明/提示

在这个例子中，Bessie 最优的策略是在 $x=7$ 的休息站休息 $7$ 秒（获得 $14$ 个美味单位），然后在 $x=8$ 的休息站再休息 $1$ 秒（获得 $1$ 个美味单位，总共 $15$ 个美味单位）。

## 样例 #1

### 输入

```
10 2 4 3
7 2
8 1```

### 输出

```
15```

# 题解

## 作者：pzc2004 (赞：18)

[题目传送门](https://www.luogu.org/problem/P4266)

思路：这题就是一个贪心，先将每个休息站按照美味值从大到小排序，然后从头到尾扫一遍，能吃就一直吃到FJ追上来为止。

细节：要开long long！！！~~别问我是怎么知道的~~

代码：
```
#include <bits/stdc++.h>
using namespace std;
long long l,n,v1,v2,ans,a2;//v1为FJ的速度，v2为Bessie的速度，a2记录Bessie吃了多久的草
struct sb
{
	long long a,b;
}a[100001];
bool cmp(const sb &sb1,const sb &sb2)
{
	return sb1.b>sb2.b;
}
int main()
{
	scanf("%lld%lld%lld%lld",&l,&n,&v1,&v2);
	for(long long i=1;i<=n;i++)scanf("%lld%lld",&a[i].a,&a[i].b);
	sort(a+1,a+n+1,cmp);//排序（C++党的优越感）
	for(long long i=1;i<=n;i++)//从头往后扫
	{
		if(a[i].a*v2+a2<=a[i].a*v1)//如果Bessie到这块草地的时间加上她已经用来吃草的时间小于等于FJ到这块草地的时间
		{
			ans+=(a[i].a*v1-a[i].a*v2-a2)*a[i].b;//吃个痛快！
			a2=a[i].a*v1-a[i].a*v2;//将吃草的时间加上
		}
	}
	printf("%lld",ans);//输出
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：t14Zack (赞：9)

这题还蛮简单，~~像我这种蒟蒻都能做出来~~。  
先按价值排序。  
如：  
10 2 4 3  
7 1  
8 2  
排序后是：  
8 2  
7 1  
先把第一个价值最大的求出来：  
ans = a[1].c*(a[1].x*t);  
t是速度差（rf - rb）。  
接着往下找，只要发现当前坐标 > 上回坐标，ans就+=当前可得到的价值。  
ans += a[i].c*((a[i].x-a[last].x)*t);  
a[last].x是上回坐标。  
对了，这题貌似要开long long  
### 好了，上代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct node {
	long long x;
	long long c;
} a[100010];
bool cmp(const node &a, const node &b) {
	if(a.c > b.c)
        return true;
    return false;
}
int main() {
	long long l, n, f, b;
	cin >> l >> n >> f >> b;
	for(int i = 1; i <= n; i++)
		cin >> a[i].x >> a[i].c;
	long long t = f-b;
	sort(a+1, a+n+1, cmp);
	long long ans = a[1].c*(a[1].x*t), last = 1;
	for(int i = 2; i <= n; i++) {
		if(a[i].x > a[last].x) {
			ans += a[i].c*((a[i].x-a[last].x)*t);
			last = i;
		}
	}
	cout << ans << endl;
	return 0;
}
}
```
**完美结束。**

---

## 作者：Ruo_Xu_void (赞：5)

其他几个题解我这个蒟蒻没太看看懂，所以写下自己思路:
先比较出美味值最大的休息点，然后只要重复求出从此休息点往后的休息点之中美味值最大的，直到最后一个休息点，然后把每一个记录下来，再分别求出以上每个休息点能获得的最大美味值，以下为代码。（952ms, 3744KB~~思路过于简单所以快超时了，希望能采纳~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x[100010],c[100010],m=0,k,a[100010],b[100010],e=1,l,n,rf,rb,ans=0;
//x,c为输入数据 a,b记录每个最大值
void s(long long u){//递归求出每一个最大值
    e++;
    m=0;
    for(long long j=u+1;j<=n;j++){
        if(c[j]>m){
            m=c[j];
            k=j;
        }
    }
    a[e]=x[k];
    b[e]=c[k];
    if(k!=n){
        s(k);
    }
}
int main(){
    scanf("%lld%lld%lld%lld",&l,&n,&rf,&rb);
    for(long long i=1;i<=n;i++){
        scanf("%lld%lld",&x[i],&c[i]);
        if(c[i]>m){//求第一个最大值
            m=c[i];
            k=i;
        }
    }
    a[1]=x[k];
    b[1]=c[k];
    s(k);
    for(long long i=1;i<=e;i++){ //求最终结果
        if(i>1){
            ans+=(a[i]-a[i-1])*(rf-rb)*b[i];	
        }
        else{
            ans+=a[i]*(rf-rb)*b[i];
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Lolierl (赞：4)

这题其实可以不用排序。

在当前点（此时和FJ在一起），下一个走到的点肯定是接下来所有点中美味值最大的点，在那一直吃直到FJ再追上来。于是这就是一个后缀最大值，用类似后缀和的办法即可，因为L很小所以甚至可以不用离散化。时间复杂度是严格线性的。


```cpp
#include<iostream>
#include<cstdio>
using namespace std; 

const int N = 1e6 + 5; 
int l, n, rf, rb, s[N], t[N]; 

int main()
{
	scanf("%d%d%d%d", &l, &n, &rf, &rb); 
	
	for(int i = 1; i <= n; i++)
	{
		int x, c; 
		scanf("%d%d", &x, &c); 
		t[x] = max(t[x], c); 
	}
	
	for(int i = l - 1; i >= 1; i--)
		s[i] = (t[s[i + 1]] > t[i]) ? s[i + 1] : i; 
	//s[i]表示i到l上美味值最大的休息点位置
	int x = 0; 
	long long ans = 0; 
	while(s[x + 1])
	{
		ans += 1ll * (rf - rb) * (s[x + 1] - x) * t[s[x + 1]]; 
		x = s[x + 1]; 
	}
	printf("%lld", ans); 
	return 0; 
}
```

---

## 作者：木木！ (赞：4)

这题可以用每次暴力比较贪心的做法。如果数据随机，这种做法的时间复杂度为$\Theta(n\log n)$。但是如果数据构造了的话，这种做法可以被卡到$\Theta(n^2)$。排序的做法是$\Theta(n\log n)$，这里介绍一种$\Theta(n)$的单调队列做法。

[单调队列模板题](https://www.luogu.org/problem/P1886)

可以发现，每次如果一个休息站的位置比较远且$c_i$比较大的话，就可以把前面那个挤出去。这样就很容易想到结合单调队列的贪心。

由于输入数据已经按照位置排好序，所以只需要$\Theta(n)$单调队列，然后$\Theta(n)$扫一遍单调队列就好。

三个`int`乘起来可能会爆`int`，要记得开`long long`。因为都是$10^6$级别，不会爆`long long`。

附AC代码：

```cpp
#include <cstdio>
using namespace std;

int q[100005];
int xi[100005];
int ci[100005];

int main()
{
	int l,n,f,b;
	scanf("%d%d%d%d",&l,&n,&f,&b);
	for(int i=1; i<=n; ++i)
	{
		scanf("%d%d",xi+i,ci+i);
	}

	int head = 0;
	for(int i=1; i<=n; ++i)
	{
		while(head && ci[i]>=ci[q[head]])
		{
			--head;
		}
		++head;
		q[head] = i;
	}

	long long ans = 0;
	for(int i=1; i<=head; ++i)
	{
		ans += 1LL*(xi[q[i]]-xi[q[i-1]])*(f-b)*ci[q[i]];
	}

	printf("%lld",ans);
}
```

---

## 作者：SUNCHAOYI (赞：3)

**这道题算一个贪心吧！**

**具体思路：把草美味值大的放在前面，然后循环一遍，若要去的点在已到的点的后面，那么就去下一个点（每次加上的值为两者速度差 * 草美味值 * 这个点能待的时间）**

**代码如下：**
```
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
struct node
{
    int x,c;
}a[100000];
bool cmp(node xx,node yy)
{
    if(xx.c != yy.c) return xx.c > yy.c;
    else return xx.x < yy.x;
}
int main()
{
    int r,n,f,b;
    long long ans = 0,k = 1,m = 0;
    scanf("%d%d%d%d",&r,&n,&f,&b);
    for(int i = 0;i < n;i++) scanf("%d%d",&a[i].x,&a[i].c);
    sort(a,a + n,cmp);
    for(int i = 0;i < n;i++)
    {
        if(m > a[i].x) continue;
        k = 1;
        k= (long long)((a[i].x - m) * (f - b));
        k *= a[i].c;ans += k;
        m = a[i].x; 
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：封禁用户 (赞：3)

## 此题可以优化到$O(N)$
在$O(N\log N)$算法中，排序的目的是求出一个价值递减的序列，以保证当前所选的是当前最优解。

既然我们不必在乎其他不是最优解的价值，排序没有必要。

只须先逆序扫一遍所有的休息站，找出在每一阶段的最优解，将其记录在一个数组中，在第二遍扫的时候，算出价值即可。

49ms，luogu 1st。
```cpp
#include <cstdio>
#include <iostream>
#include <cctype>
#include <cstring>
#include <map>
#include <stack>
#include <utility>
#include <string>
#include <algorithm>
#define gc() getchar()
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define dec(i,a,b) for(int i=(a);i>=(b);--i)
#define endll putchar('\n');
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int  MAXOUT=10000;
const int MAXBUF=10000;
char buf[MAXBUF],*ps=buf,*pe=buf+1;
inline void rnext(){
    if(++ps == pe)
        pe = (ps = buf)+fread(buf,sizeof(char),sizeof(buf)/sizeof(char),stdin);
}
inline bool in(ll &ans){
    ans = 0;
    ll f = 1;
    if(ps == pe) return false;//EOF
    do{
        rnext();
        if('-' == *ps) f = -1;
    }while(!isdigit(*ps) && ps != pe);
    if(ps == pe) return false;//EOF
    do{
        ans = (ans<<1)+(ans<<3)+*ps-48;
        rnext();
    }while(isdigit(*ps) && ps != pe);
    ans *= f;
    return true;
}
char bufout[MAXOUT], outtmp[50],*pout = bufout, *pend = bufout+MAXOUT;
inline void write(){
    fwrite(bufout,sizeof(char),pout-bufout,stdout);
    pout = bufout;
}
inline void out_char(char c){ *(pout++) = c;if(pout == pend) write();}
inline void out_str(char *s){
    while(*s){
        *(pout++) = *(s++);
        if(pout == pend) write();
    }
}
inline void out_int(ll x) {
    if(!x){
        out_char('0');
        return;
    }
    if(x < 0) x = -x,out_char('-');
    int len = 0;
    while(x){
        outtmp[len++] = x%10+48;
        x /= 10;
    }
    outtmp[len] = 0;
    for(int i = 0, j = len-1; i < j; i++,j--) swap(outtmp[i],outtmp[j]);
    out_str(outtmp);
}
inline void out_int_ln(ll k){
	out_int(k);
	out_char('\n');
}
const int maxn=101101;
ll l,n,rf,rb;
struct kusa{
	ll dis,val;
	kusa(){}
	kusa(ll _dis,ll _val){dis=_dis;val=_val;}
}k[maxn];
bool operator <(const kusa &a,const kusa &b){
	if(a.val==b.val) return a.dis>b.dis;
	return a.val>b.val;
}
ll ans;
ll tmp_max;
bool decmax[maxn];
int tmp_dis=0;
int main(){
	in(l),in(n),in(rf),in(rb);
	rep(i,1,n) in(k[i].dis),in(k[i].val);
	dec(i,n,1)
		if(k[i].val>tmp_max) decmax[i]=true,tmp_max=k[i].val;
	rep(i,1,n)
		if(decmax[i]==true){
			ans+=k[i].val*(rf-rb)*(k[i].dis-tmp_dis);
			tmp_dis=k[i].dis;
		}
	out_int_ln(ans);
	write();
	return 0;
}
```


---

## 作者：StudyingFather (赞：3)

一道并不算太难的贪心题。

显然可以看出，在单位价值越高的地方停留的越久，收益就会越高。所以我们先按照每个休息站的价值的降序排序。（如果价值相同，就按坐标降序排序）

然后把这些休息站从前往后扫描一遍，只要满足该休息点的坐标小于最近一个休息点的坐标，就在这个点休息，并累加收益及更新最新休息点位置。

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
struct reststop
{
 long long x,c;
}a[100005];
bool cmp(const reststop&a,const reststop&b)
{
 return a.c>b.c||(a.c==b.c&&a.x>b.x);
}
long long maxc[100005],s;
long long ans;
int main()
{
 int l,n,rf,rb;
 cin>>l>>n>>rf>>rb;
 for(int i=1;i<=n;i++)
  cin>>a[i].x>>a[i].c;
 sort(a+1,a+n+1,cmp);
 for(int i=1;i<=n;i++)
  if(s<a[i].x)
  {
   ans+=(a[i].x-s)*(rf-rb)*a[i].c;
   s=a[i].x;
  }
 cout<<ans;
 return 0;
}
```

---

