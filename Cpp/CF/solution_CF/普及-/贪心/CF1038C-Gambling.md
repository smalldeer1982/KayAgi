# Gambling

## 题目描述

### 题目大意：
两个人$A,B$玩游戏，每个人有1个长度为$n$的序列，每次一个人可以从序列中拿一个数并加入自己的分数，或者把对手序列中没选的数中去掉一个，这两个人都足够聪明，求$A$分数与$B$分数的差

## 样例 #1

### 输入

```
2
1 4
5 1
```

### 输出

```
0```

## 样例 #2

### 输入

```
3
100 100 100
100 100 100
```

### 输出

```
0```

## 样例 #3

### 输入

```
2
2 1
5 6
```

### 输出

```
-3```

# 题解

## 作者：Moon_Wind (赞：6)

[题目：CF1038C](https://www.luogu.com.cn/problem/CF1038C)

------------
**本题坑点**：

留心数据范围，开 ```int``` 会爆，开 ```long long``` 即可解决该问题。

需要将数组 $a$ 和 $b$ 从大到小排序。


------------
**本题核心**：**贪心**

因为 $A$ 和 $B$ 足够聪明，所以，为了使自己的分数最大化，就会加上自己序列中最大的数。但是，如果能破坏他人的计划，使他人的分数不能最大化，并且他人的最大数大于自己的最大数，他们也很乐意去以一次不选择自己的最大数的代价去去掉他人的最大数。所以当 $A$ 的序列中最大的数大于等于 $B$ 的序列中最大的数时，$A$ 就会将他的序列中最大的数累加进自己的分数中，否则，他就会去掉 $B$ 的序列中最大的数。同理，$B$ 的操作与 $A$ 相同，这里不再赘述。

所以我们可以 **用两个数组来模拟优先队列** 来解决此题。

------------
代码部分。
```cpp
#include<bits/stdc++.h>
#define ll long long//需要开long long 
using namespace std;

const int MAXN=1e6+10;
ll n,a[MAXN]={0},b[MAXN]={0},ans=0,sum=0;
//a为 A的序列  b为 B的序列  ans是 A的分数  sum是 B的分数 

bool cmp(int x,int y){//自定义排序 
      return x>y;
}

int main(){
	ios::sync_with_stdio(0);//开下优化 
	cin.tie(0);cout.tie(0); 
	
	cin>>n;
	for(ll i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(ll i=0;i<n;i++)
	{
		cin>>b[i];
	}
	sort(a,a+n,cmp);//按从大到小排序 
	sort(b,b+n,cmp);
	for(ll i=0,j=0;i<n&&i+j<n*2||j<n&&i+j<n*2;)//模拟队列 
	{
		//如果队列 a中最大的数大于等于队列 b中最大的数 或队列 b为空 
		//那么ans就加上队列 a中最大的数
		//否则去掉队列 b中最大的数 
		if(a[i]>=b[j]||j>=n) 
		{
			ans+=a[i];
			i++; 
		} 
		else
		{
			j++;
		}
		//如果队列 b中最大的数大于等于队列 a中最大的数 或队列 b为空 
		//那么sum就加上队列 b中最大的数
		//否则去掉队列 a中最大的数
		if(a[i]<=b[j]||i>=n)
		{
			sum+=b[j];
			j++; 
		}
		else
		{
			i++;
		}
	}
	cout<<ans-sum;//最后输出A与B分数之差 
	return 0;//代码部分结束 
}
```


------------
本人只是一名蒟蒻，若有错误请多多包涵，谢谢大家。

---

## 作者：VenusM1nT (赞：2)

贪心。  
因为两个人都是理论最优决策，而结果求的是差值，这可以提供突破口。  
令 $a_i$ 为 A 的当前最大值，$b_i$ 为 B 的当前最大值，假设现在轮到 A 决策，如果他选择选自己的最大值，那么对答案贡献为 $a_i$；如果他选择删对面的最大值，对答案贡献为 $-b_i$，这一步可以看做为 A 自己的分数加上 $b_i$，那么做法就非常明显了：每次比较 $a_i$ 和 $b_i$，选择较大的那个进行操作就可以了。
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
#define int long long
using namespace std;
priority_queue <int> a,b;
int n,A,B;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(reg int i=1;i<=n;i++)
	{
		reg int x;
		cin>>x;
		a.push(x);
	}
	for(reg int i=1;i<=n;i++)
	{
		reg int x;
		cin>>x;
		b.push(x);
	}
	for(reg int i=1;i<=n*2;i++)
	{
		if(i&1)
		{
			if(b.empty() || (!a.empty() && a.top()>=b.top()))
			{
				A+=a.top();
				a.pop();
			}
			else if(a.empty() || a.top()<b.top()) b.pop();
		}
		else
		{
			if(a.empty() || (!b.empty() && b.top()>=a.top()))
			{
				B+=b.top();
				b.pop();
			}
			else if(b.empty() || b.top()<a.top()) a.pop();
		}
	}
	cout<<A-B<<endl;
	return 0;
}
```

---

## 作者：qiuqiuqzm (赞：0)

# CF1038C Gambling 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1038C)

## 分析
这道题的核心思路其实就是**贪心**。

因为 $A$ 和 $B$ 足够聪明，所以他们肯定会在使自己的分数最大化的情况下，让对方的分数最小化。所以当自己的最大值大于对方的最大值时，那他们肯定就会选择把自己的最大值加入自己的分数。反之如果自己的最大值小于对方的最大值，那就会把对方的最大值删掉。

所以我们只需要在开局排序下，然后一步步模拟即可。

## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXX=100005;
int n,a[MAXX],b[MAXX],ma,mb,mode=1;
long long ansa,ansb;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	ma=mb=n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	while(ma||mb)
	{
		if(mode==1)
		{
			if(a[ma]>=b[mb]&&ma)
				ansa+=a[ma],ma--;
			else if(mb)
				mb--;
			mode=1-mode;
		}
		if(mode==0)
		{
			if(a[ma]<=b[mb]&&mb)
				ansb+=b[mb],mb--;
			else if(ma)
				ma--;
			mode=1-mode;
		}
	}
	cout<<ansa-ansb;
	return 0;
}
```

---

## 作者：InversionShadow (赞：0)

听说 csp 前一天发题解可以攒 RP。

显然当 $a$ 操作的时候，如果 $b$ 序列最大的大于 $a$ 序列最大值的时候，$a$ 会选择把 $b$ 的最大值去掉，否则 $a$ 会取他自己的最大值。

$b$ 同理。

注意一下 `long long` 和一些边界的处理就可以了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define f(i, x, y) for (int i = x; i <= y; i++)

using namespace std;

const int N = 1e5 + 100;

int n, a[N], b[N], f = 1, suma, sumb;

priority_queue<int> q1, q2;

signed main() {
  cin >> n;
  f(i, 1, n) cin >> a[i], q1.push(a[i]);
  f(i, 1, n) cin >> b[i], q2.push(b[i]);
  while (1) {
    if (q1.empty() && q2.empty()) {
      break;
    }
    if (f & 1) {
      if (!q1.size()) {
        f ^= 1;
        q2.pop();
        continue;
      }
      if (q2.empty() || q1.top() > q2.top()) {
        suma += q1.top();
        q1.pop();
      } else {
        q2.pop();
      }
    } else {
      if (!q2.size()) {
        f ^= 1;
        q1.pop();
        continue;
      }
      if (q1.empty() || q1.top() < q2.top()) {
        sumb += q2.top();
        q2.pop();
      } else {
        q1.pop();
      }
     }
     f ^= 1;
//   cout << ' ' << suma << ' ' << sumb << '\n';
  }
// cout << suma << ' ' << sumb << '\n'; 
  cout << suma - sumb;
  return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

应该算是一道贪心。

有题目可知两人都足够聪明，所以他们都能想到当前的最优解。

然后，我们对于每个人都可以分为两种情况讨论。

1. 拿自己的加入分数。

可以用这个方案的情况无非就是：自己能取到的最大值比能丢掉的最大值大，或者说，对方没有数了。

2. 取别人的丢掉。

因为不能用第一种方案，就只能取别人的了。

我们知道了这些，便可以使用优先队列维护最大值了，并求出答案了。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

int n,ansa,ansb;
priority_queue<int> a,b;//一定要定义大根堆 

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + c - 48;
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++){
		int x;
		x = read();
		a.push(x);
	}
	for (re int i = 1;i <= n;i++){
		int x;
		x = read();
		b.push(x);
	}
	n <<= 1;
	for (re int i = 1;i <= n;i++){
		if (i & 1){//两个人每个人两种方案 
			if ((!a.empty() && a.top() > b.top()) || b.empty()){//方案1 
				ansa += a.top();
				a.pop();
			}
			else b.pop();//方案2 
		}
		else{
			if ((!b.empty() && b.top() > a.top()) || a.empty()){//方案1 
				ansb += b.top();
				b.pop();
			}
			else a.pop();//方案2 
		}
	}
	printf("%lld",ansa - ansb);
	return 0;
}
```

---

## 作者：fengxiaoyi (赞：0)

### 思路

**这是一道贪心+模拟题。**

首先输入 $A$ 和 $B$ 的数列，分别用一个优先队列（大根堆）存下来。

------------

定义 $now$ 表示当前轮到谁了，$0$ 表示 $A$，$1$ 表示 $B$，每次操作完将 $now\oplus 1$（其中 $\oplus$ 表示按位异或）。

定义 $ans$ 表示 $A,B$ 的分数差。

------------

对于 $A$ 的数列所对应的优先队列（以下简称 $P_A$）的队首与 $B$ 的数列所对应的优先队列（以下简称 $P_B$）的队首做比较：
- 如果 $P_A$ 的队首更大，那么看 $now$ 的值：  
$\circ$ 如果 $now=1$ 则表示 $B$ 将 $P_A$ 的队首删去，弹出 $P_A$ 的队首。  
$\circ$ 如果 $now=0$ 则表示 $A$ 将 $P_A$ 的队首加入自己的分数，即 $ans+P_A$ 的队首的分数，弹出 $P_A$ 的队首。 
- 如果 $P_B$ 的队首更大，那么看 $now$ 的值：  
$\circ$ 如果 $now=1$ 则表示 $B$ 将 $P_B$ 的队首加入自己的分数，即 $ans-P_B$ 的队首的分数，弹出 $P_B$ 的队首。   
$\circ$ 如果 $now=0$ 则表示 $A$ 将 $P_B$ 的队首删去，弹出 $P_B$ 的队首。 

------------

最后输出 $ans$ 即可。

### 程序实现

其实没啥细节，建议自己实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,now;
long long ans;
priority_queue<int>A;
priority_queue<int>B;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int a;
		scanf("%d",&a);
		A.push(a);
	}
	for(int i=1;i<=n;i++){
		int b;
		scanf("%d",&b);
		B.push(b);
	}
	while(!A.empty()&&!B.empty()){
		int a=A.top(),b=B.top();
		A.pop(),B.pop();
		if(a>b){
			if(!now) ans+=a;
			B.push(b);
		}
		else if(a<b){
			if(now) ans-=b;
			A.push(a);
		}
		else{
			if(!now) ans+=a,B.push(b);
			else ans-=b,A.push(a);
		}
		now^=1;
	}
	while(!A.empty()){
		int a=A.top();
		A.pop();
		if(!now) ans+=a;
		now^=1;
	}
	while(!B.empty()){
		int b=B.top();
		B.pop();
		if(now) ans-=b;
		now^=1;
	}
	return !printf("%lld",ans);
}
```


---

## 作者：_szs9601 (赞：0)

### 思路

贪心，因为两个人都是理论最优决策，结果求的是差值，所以我们可以从中寻找突破口。

假设当前有两个数 $a$ 和 $b$，且 $a<b$，两序列的差值为 $c$。当 $A$ 序列把 $a$ 加进来时，$B$ 序列肯定会把 $b$ 加进来，那么 $c$ 就会变小；当把 $b$ 删除后，$B$ 序列肯定会把 $a$ 删除，则 $c$ 不变。显然，第二种方案是更优的。所以我们就得到了一种贪心思路。

所以我们先将 $A$ 和 $B$ 序列从大到小排序，然后判断两序列中最大的那个数 $a$ 和 $b$ ，如果 $a<b$ 就删掉 $b$；反之，就加上 $a$。
### 代码
```cpp
#include<bits/stdc++.h>
#define LL long long//别忘了开long long
using namespace std;
int t,w,i,n,a[100100],b[100100];
LL x,y;
bool cmp(int x,int y){return x>y;}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<=n;i++) scanf("%d",&b[i]);
	sort(a+1,a+n+1,cmp);sort(b+1,b+n+1,cmp);//读入+排序
	t=1;w=1;
	while(t+w<=2*n){
		if(t<=n){
			if(a[t]<b[w]) w++;//a<b时，删除大的
			else x+=a[t],t++;//a>b时，加上大的
		}
		else w++;//A回合
		if(w<=n){
			if(a[t]>b[w]) t++;
			else y+=b[w],w++;//同理
		}
		else t++;//B回合
	}//贪心
	printf("%lld\n",x-y);
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

这是一道简单的博弈论。
## 思路
我们假设当前是 A 的回合。从贪心的角度，他必定要在这一轮结束后使 A 的分数与 B 的分数的差值最大。他有两个选择，一是砍掉 B 剩余序列的数中**最大的**，二是取出自己剩余序列中数**最大的**。从贪心的想法，肯定是两个中取大的。B 同理。

现在我们来证明一下这个结论：假设当前是 A 的回合，且 B 的序列中存在两个数分别为：$b_1,b_2\ \ (b_1>b_2)$，设当前 A 的分数为 $ans_a$，B 的分数为 $ans_b$。若 A 选择 $b_1$，则 B 的分数为 $ans_b'=ans_b+b_2$，$delta_1=ans_a-ans_b'=ans_a-ans_b-b_2=(ans_a-ans_b)-b_2$。若 A 选择 $b_2$，则 $ans_b'=ans_b+b_1$，$delta_2=ans_a-ans_b'=ans_a-ans_b-b_1=(ans_a-ans_b)-b_1$。

$delta_1-delta_2=-b_2+b_1=b_1-b_2>0$

所以 $delta_1>delta_2$，即 A 选择砍掉 B 序列中最大的选择是正确的。更显然的是，A 选择取出自己剩余序列中数最大的选择也是正确的。我们再综合两种情况求最优解一定是正确的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
int ansa,ansb;
priority_queue<int>qa,qb;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for (rint i=1,x;i<=n;++i) cin>>x,qa.push(x);
    for (rint i=1,x;i<=n;++i) cin>>x,qb.push(x);
    for (rint i=1;i<=2*n;++i)
    	if (i&1){
    		if (qa.top()<qb.top() && !qb.empty() || qa.empty()) qb.pop();
    		else ansa+=qa.top(),qa.pop();
    	}else{
    		if (qa.top()>qb.top() && !qa.empty() || qb.empty()) qa.pop();
		    else ansb+=qb.top(),qb.pop();
		}
	cout<<ansa-ansb<<'\n';
	return 0;
}
```


---

## 作者：傅思维666 (赞：0)

## 题解：

看到”足够聪明“就开始想贪心。

贪心这个东西，就是直觉好的人一眼切，直觉不好的人反复错。

对于这道题，贪心策略非常好想也非常好证明。如果当前我方剩下的最大数要比对面剩下的最大数大，那对面怎么拿，我们都是赚的，所以这时取我方最大的。反之，我们怎么拿，只要对面把对面最大的拿走，我们都是亏的。所以贪心策略就出来了。

至于实时维护最大值，可以用堆来实现。

代码：

```cpp
#include<cstdio>
#include<queue>
#define int long long
using namespace std;
int n,ansa,ansb;
priority_queue<int> q[3];
//q[1]:A q[0]:B
signed main()
{
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%I64d",&x);
		q[1].push(x);
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%I64d",&x);
		q[0].push(x);
	}
	q[1].push(-1);
	q[0].push(-1);
	int tot=n*2;
	for(int i=1;i<=tot;i++)
	{
		int a=q[1].top();
		int b=q[0].top();
		if(i&1)//a's turn
		{
			if(a<b)
				q[0].pop();
			else
			{
				q[1].pop();	
				ansa+=a;
			}
		}
		else//b's turn
		{
			if(b<a)
				q[1].pop();
			else
			{
				q[0].pop();
				ansb+=b;
			}
		}
	}
	printf("%I64d",ansa-ansb);
	return 0;
}
```




---

## 作者：LJB00131 (赞：0)

考虑证明这个贪心。

把$b[i]$转化为$-b[i]$, 与$a[i]$ 置于同一序列中，从这个序列里取数或者删数，此时A要使取出的数和最大化，而B反之。

对于A,显然取数取最大，删数删最小。B反之。

设轮到A操作时最大数为x，最小数为y

删去最小数能使给最终答案贡献为-y， 取出最大数贡献为x
则显然哪个绝对值大就做哪个操作。

直接排序搞一搞就好了。不知道为啥之前的题解写那么复杂(小声BB)

```cpp
#include<bits/stdc++.h>

using namespace std;

#define N 100005
typedef long long ll;

int n;

ll a[N], b[N];

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	ll ans = 0;
	int l = n, r = n;
	for(int i = 1; i <= 2 * n; i++)
	{
		if(i & 1)
		{
			if(a[l] > b[r]) ans += a[l--];
			else r--;
		}
		else
		{
			if(b[r] > a[l]) ans -= b[r--];
			else l--;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：zhaotiensn (赞：0)

很简单的贪心:

对于每一次选择，如果对面当前最大的数比自己当前最大的数小，那么选自己最大的数。如果对面当前最大的数比自己当前最大的数大，那么就弃掉对面最大的数。

~~这应该是很显然的。~~

另外cf的[官方题解](http://codeforces.com/blog/entry/61692)讲的很详细。

大致意思是：

先将每个数除以2之后加入到各自的总数中，然后每次再从除以2后的数中找出最大的，因为假设是自己的数，那么就是自己的总数加，对最后答案的贡献是这个数除以2，假设是对方的数，那么就是对方的总数减，对最后答案的贡献也是这个数除以2。

~~然后因为手残调了好久~~

自己的代码：
```
#include <iostream>
#include <cstdio>
#include <queue>

#define ll long long

using namespace std;

inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline ll read(){
    ll x=0;char ch=gc();bool positive=1;
    for(;!isdigit(ch);ch=gc())if(ch=='-')positive=0;
    for(;isdigit(ch);ch=gc())x=x*10+ch-'0';
    return positive?x:-x;
}

inline void write(ll x){
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);putchar(x%10+'0');
}

inline void writeln(ll x){
    write(x);puts("");
}//以上皆是没有用的快读快输

ll n,m,a,ans;

priority_queue<ll>que1,que2;//因为懒，所以我直接用堆了

int main(){
    n=read();
    for(ll i=1;i<=n;i++){
        a=read();
        que1.push(a);
    }
    for(ll i=1;i<=n;i++){
        a=read();
        que2.push(a);
    }
    for(ll i=1;i<=n;i++){
        if(que1.empty()||que2.empty()){//特判没有了的情况
            if(que1.empty()){
                que2.pop();
            }
            if(que2.empty()){
                ans+=que1.top();
                que1.pop();
            }
        }else{
            if(que2.top()>que1.top()){//比较最大的数的大小
                que2.pop();//弃掉对面的数
            }else{
                ans+=que1.top();//选自己的数
                que1.pop();
            }
        }
        if(que1.empty()||que2.empty()){//再来一次
            if(que1.empty()){
                ans-=que2.top();
                que2.pop();
            }
            if(que2.empty()){
                que1.pop();
            }
        }else{
            if(que1.top()>que2.top()){
                que1.pop();
            }else{
                ans-=que2.top();
                que2.pop();
            }
        }
    }
    writeln(ans);
    return 0;
}

```

---

