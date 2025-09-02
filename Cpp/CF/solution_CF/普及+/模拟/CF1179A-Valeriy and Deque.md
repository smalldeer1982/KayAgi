# Valeriy and Deque

## 题目描述

Recently, on the course of algorithms and data structures, Valeriy learned how to use a deque. He built a deque filled with $ n $ elements. The $ i $ -th element is $ a_i $ ( $ i $ = $ 1, 2, \ldots, n $ ). He gradually takes the first two leftmost elements from the deque (let's call them $ A $ and $ B $ , respectively), and then does the following: if $ A > B $ , he writes $ A $ to the beginning and writes $ B $ to the end of the deque, otherwise, he writes to the beginning $ B $ , and $ A $ writes to the end of the deque. We call this sequence of actions an operation.

For example, if deque was $ [2, 3, 4, 5, 1] $ , on the operation he will write $ B=3 $ to the beginning and $ A=2 $ to the end, so he will get $ [3, 4, 5, 1, 2] $ .

The teacher of the course, seeing Valeriy, who was passionate about his work, approached him and gave him $ q $ queries. Each query consists of the singular number $ m_j $ $ (j = 1, 2, \ldots, q) $ . It is required for each query to answer which two elements he will pull out on the $ m_j $ -th operation.

Note that the queries are independent and for each query the numbers $ A $ and $ B $ should be printed in the order in which they will be pulled out of the deque.

Deque is a data structure representing a list of elements where insertion of new elements or deletion of existing elements can be made from both sides.

## 说明/提示

 Consider all 10 steps for the first test in detail:2. $ [1, 2, 3, 4, 5] $ — on the first operation, $ A $ and $ B $ are $ 1 $ and $ 2 $ , respectively.So, $ 2 $ we write to the beginning of the deque, and $ 1 $ — to the end.
  
  We get the following status of the deque: $ [2, 3, 4, 5, 1] $ .
3. $ [2, 3, 4, 5, 1] \Rightarrow A = 2, B = 3 $ .
4. $ [3, 4, 5, 1, 2] $
5. $ [4, 5, 1, 2, 3] $
6. $ [5, 1, 2, 3, 4] $
7. $ [5, 2, 3, 4, 1] $
8. $ [5, 3, 4, 1, 2] $
9. $ [5, 4, 1, 2, 3] $
10. $ [5, 1, 2, 3, 4] $
11. $ [5, 2, 3, 4, 1] \Rightarrow A = 5, B = 2 $ .

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
1
2
10
```

### 输出

```
1 2
2 3
5 2
```

## 样例 #2

### 输入

```
2 0
0 0
```

### 输出

```
```

# 题解

## 作者：lemon2021 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1179A)
## 思路
本蒟蒻一看这题，以为是一道双端队列模拟题，于是就用 STL 的 deque 写了一个普通模拟，~~相当于暴力~~。**STL 大法好**！结果一提交，$75$ 分，看来这题数据还是有一点强，于是就开了个 O2 优化，结果......还是 $75$ 分，完！看来这题水不了了，~~蒟蒻愤怒~~。
### 暴力 $75$ 分代码如下：
```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=300001;
deque<long long> q;
long long f[MAXN];
int n,m,tag;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int t;
		cin>>t;
		q.push_back(t);
	}
	for(int i=1;i<=m;i++)
	{
		cin>>f[i];
	}
	tag=1;
	for(long long i=1;i<=f[m];i++)
	{
		int a=q.front();
		q.pop_front();
        int b=q.front();
		q.pop_front();
		if(i==f[tag])
		{
			cout<<a<<" "<<b<<endl;
			tag++;
		}
		if(a>b)
		{
			q.push_front(a);
			q.push_back(b);
		}
		else
		{
			q.push_front(b);
			q.push_back(a);
		}
	}
	return 0;
}
```
然后本蒟蒻才开始想正解，先拿一组简单数据来想：$2,3,1,5,4$。其变化过程如下：

$23154\to31542\to35421\to54213\to52134\to51342\to53421\to54213 ......$

咦！原来从 $54213$ 开始，队列的第一位永远都是 $5$，即队列中的最大值。而队列的第二位则是 $4,2,1,3$ 这 $4$ 个数字轮流来的！搞半天，这道绿题居然是找规律啊！那这下就简单啦！本蒟蒻立马又写了一个代码，结果......还没 AC？原来这题的数据不是一点强，而是**亿**点强，简直堪称**毒瘤**！！！本蒟蒻终于体会到了**不开 long long 见祖宗**啊！~~蒟蒻再次愤怒~~。
## AC 代码(再次强调：不开 long long 见祖宗)
```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100001;
pair<int, int> p[MAXN];
int n,m,tag;
int maxx=-1e9;
int w[MAXN];
deque<int> q;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int t;
		cin>>t;
		maxx=max(maxx,t);
		q.push_back(t);
	}
	int x=0;
	while(true)
	{
		x++;
		int a=q.front();
		q.pop_front();
		int b=q.front();
		q.pop_front();
		p[x].first=a;
		p[x].second=b;
		if(a>b)
		{
			q.push_front(a);
			q.push_back(b);
		}
		else
		{
			q.push_front(b);
			q.push_back(a);
		}
		if(maxx==max(a,b))
		{
			tag=x;
			q.pop_front();
			for(int i=1;i<n;i++)
			{
				w[i]=q.front();
				q.pop_front();
			}
			break;
		}
	}
	for(int i=1;i<=m;i++)
	{
		long long t;
		cin>>t;
		if(t<=tag)
		{
			cout<<p[t].first<<' '<<p[t].second<<endl;
		}
		else
		{
			long long z=t-tag;
			if(z%(n-1)==0)
			{
				cout<<maxx<<' '<<w[n-1]<<endl;
			}
			else
			{
				cout<<maxx<<' '<<w[z%(n-1)]<<endl;
			}
		}
	}
}
```
最后若还有和本人一样的蒟蒻代码一直不知道哪错的，可以试一下以下数据，方便查错。
```
输入：
5 10
2 3 1 5 4
1 2 3 4 5 6 7 8 9 10
```
```
输出：
2 3
3 1
3 5
5 4
5 2
5 1
5 3
5 4
5 2
5 1
```


---

## 作者：Twlight！ (赞：2)

第一次写题解，有不好的地方还请多多关照 。

# 思路

队列比较中，每次都会取出队列的前两个元素比较，较小的元素会丢到后面，经过 $k$ 次操作后，队列头总是是原队列中最大的数。

不难看出，一旦最大的数到达队列头后，队列里剩下的数将会一直被丢到队尾，形成一个循环。

按照题目所说，模拟一个双端队列并记录比较过程，发现原队列中最大值到头后，记录一下循环节的数即可。

询问的步数较大，判断一下这步在哪个部分上并输出即可。

本题比较毒，需要注意一些细节不然容易爆零。


------------
## 结束了？

总感觉这样写代码太乱了，不妨再来看看比较过程中的数，这里出一个例子来看看：

$ 10 , 3 , 2 , 4 , 15 , 14 , 13 , 2 , 20 , 3 , 4 , 5 $

$10,3$

$10,2$

$10,4$

$10,15$

$15,14$

$…$

在循环节出现之前的比较中，第 $i$ 次比较时，队头总是是原队列中第 $1$ 个数到第 $i$ 个数的最大值，第二个数固然是队列中第 $i+1$ 个数。

因此循环前的部分我们可以创建个数组来存放前 $i$ 个数中最大的数，询问的时候直接输出这些即可（循环前的问题就搞定啦）。

再来看看循环一定次数后的队列。

$ 20 , 3 , 2 , 4 , 10 , 14 , 13 , 2 , 15 , 3 , 4 , 5 $

再对比一下原队列

$ 10 , 3 , 2 , 4 , 15 , 14 , 13 , 2 , 20 , 3 , 4 , 5 $

可以看到，原本的 $10$ 跑到了 $15$ 的地方，原本的 $15$ 跑到了 $20$ 的地方，$20$ 则跑到了开头，而这些数在原队列中都是他们自己到开头的最大的数。

扫一遍数组，记录一下当前最大数，有更大的数后把刚才记录的数丢到当前最大数的位置，以此类推（意思明白即可，实现代码可以有很多写法），到最后记录当前最大数的变量就是队列头了。

整个过程思路跟模拟队列差不多，不过算是另一种体现吧（毕竟能在读入的时候计算，还省下了几个队列）。

好了，循环与不循环都搞定了，快动手试试吧（注意细节哦）。

$code:$
```cpp
#include<bits/stdc++.h>
#define coin const int
#define lll (long long)
#define ll long long
#define ull unsigned long long

const int N = 200000 + 10;
const int inf = 1000000000;
using namespace std;

inline ll read() {
	ll x=0,k=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')k=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return (1ll*x*k);
}

ll n,q,x,maxnum;
ll que[N],newque[N];
ll curmax[N],nowarray = 0,maxstart=0;

int main() {
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		que[i]=read();
		curmax[i]=max(curmax[i-1],que[i]);
		if(i-1 == 0) continue;
		
		if(curmax[i] != curmax[i-1]){
			newque[nowarray++]=curmax[i-1];
			maxstart=i-1;
		}else{ 
			newque[nowarray++]=que[i];
		}
	}
	while(q--){
		x=read();
		if(x <= maxstart){
			printf("%lld %lld\n",curmax[x],que[x+1]);
		}else{
			printf("%lld %lld\n",curmax[n],newque[(x+nowarray-1)%nowarray]);
		}
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：1)

每次都会往后面丢一个较小的，则至少 $n$ 步后，最大值一定能到队头。

这个时候再进行操作就是不断地把第二个扔到队尾，是个循环的过程。

模拟一下直到最大值到队头，步数较大的时候直接看落在了循环节的哪一位上。

代码上应该各有千秋，理解思路即可。

```cpp
//Code by do_while_true
#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T> T Abs(T x) { return x < 0 ? -x : x; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 1000010;
int n, a[N<<1], mx, p, b[N], ans1[N], ans2[N];
signed main() {
	read(n); int q;
	read(q);
	for(int i = 1; i <= n; ++i) b[i] = read(a[i]), mx = Max(mx, a[i]);
	p = 2; int pn = n; ans1[1] = a[1]; ans2[1] = a[2]; 
	while(a[1] != mx) {
		if(a[1] > a[p]) a[++pn] = a[p];
		else std::swap(a[1], a[p]), a[++pn] = a[p];
		ans1[p] = a[1]; ans2[p] = a[p+1];
		++p;
	}
	--p;
	for(int i = 1; i <= q; ++i) {
		ll m; read(m);
		if(m < p) printf("%d %d\n", ans1[m], ans2[m]);
		else {
			printf("%d %d\n", mx, a[p+((m-p+1)%(n-1)==0?(n-1):(m-p+1)%(n-1))]);
		}
	}
	return 0;
}
```

---

## 作者：lukzia (赞：1)

## 题解

这题其实是一个毒瘤找规律题目,暴力会TLE,~~不开long long会见祖宗~~

对于这样一组数据:

$1, 2, 3, 4, 5$

继续操作下去之后,

它变成了这样:

$23451$

$34512$

$45123$

$51234$

$52341$

$53412$

$54123$

$51234$

$52341$

有没有发现出现循环节了???

$51234$

$52341$

$53412$

$54123$

这就是重复的部分

我们继续尝试~~亿~~组数据,可以发现一个显然的条件:

**最大的数总是出现循环节的开头,且循环节的长度为$n-1$**

我们就可以利用这个来做题了

我们先找出它的循环节,对于他询问的不在循环节内的,我们暴力跑一遍就可以,在循环节内的,我们对询问的步数取个模,之后在循环节中查找便可.

**详见注释**

## CODE

```cpp
#include <deque>
#include <iostream>
#include <vector>
#define endl '\n'
#define LL long long
 
std::vector<LL> ans;
std::deque<LL> q;
LL n, QAQ, maxx, m, pos;
LL vis[400005][2], cnt; //记录非循环节的队列信息
 
inline LL max (LL a, LL b)
{
    return a > b ? a : b;
}
 
int main ()
{
    std::ios::sync_with_stdio (false); //读入小优化
    std::cin.tie (0);
    std::cout.tie (0);
 
    std::cin >> n >> QAQ;
    for (register LL i = 0, x; i < n; i++)
    {
        std::cin >> x;
        maxx = max (maxx, x);  //找到最大的元素
        q.push_back (x);  //加入双端队列
    }
    for (register LL i = 1, a, b, done = 1; true; i++)
    {
        a = q.front (), q.pop_front ();  //取出元素
        b = q.front (), q.pop_front ();
        vis[++cnt][0] = a;  //记录
        vis[cnt][1] = b;
        if (a == maxx)   //出现循环节
        {
            if (done)   //我们记录循环节首次出现的操作步数
            {
                pos = i;
                done = 0;
                ans.push_back (b);  //加入存储循环节的数组
            }
            else if (ans[0] == b and i - pos >= n - 1) //当它的元素与之前重复且以循环n-1遍
            {
                m = i - pos; //记录循环节的长度
                break;
            }
            else
                ans.push_back (b);  
        }
        if (a > b)
        {
            q.push_front (a);
            q.push_back (b);
        }
        else
        {
            q.push_back (a);
            q.push_front (b);
        }
    }
 
    for (register LL i = 1, cmd; i <= QAQ; i++)  //输出答案
    {
        std::cin >> cmd;
        if (cmd <= pos) //在循环节内
            std::cout << vis[cmd][0] << " " << vis[cmd][1] << endl;
        else //不在循环节内
            std::cout << maxx << " " << ans[(cmd - pos) % m] << endl;
    }
    return 0;
}
```

## THE END

---

## 作者：F_Mu (赞：1)

题意：一个双端队列，每次取出前两个数进行比较，较大的放在前端，较小的放在后端。

分析：如果取出来的数中有一个是最大的数，那么一定是最大的数放前面，另一个数放后面，那么我们可以知道当第一个数第一次出现在首位时，后面的 _**n-1**_ 个数就开始循环了。那么看数据范围为1~1e5，先模拟，也就是最大的数若在最后也不过模拟操作1e5次，然后取的后面的数的循环。
```cpp
#include <bits/stdc++.h>

#define maxn 400005//数组开的有点大，可以优化
#define mod 1000000007
#define inf 0x3f3f3f3f
#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define LL long long
using namespace std;
int a[maxn];//数组
int c[maxn];//模拟双端队列
int q[maxn][2];//在未找到最大数之前的模拟操作

int main() {
    start;
    int maxt = 0;//最大数的位置
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] > a[maxt])
            maxt = i;
    }
    int maxx = 150005;//定一个较为中间的数
    int l = maxx, r = n + maxx - 1;//l为双端队列左端，r为双端队列右端
    for (int i = maxx; i < maxx + n; ++i)
        c[i] = a[i - maxx + 1];
    int cnt = 1;//模拟次数
    while (c[l] != a[maxt]) {
        int x = c[l++], y = c[l++];//取出队头两个元素
        q[cnt][0] = x;
        q[cnt++][1] = y;
        if (x > y) {//将大的放前面，小的放后面
            c[--l] = x;
            c[++r] = y;
        } else {
            c[--l] = y;
            c[++r] = x;
        }
    }
    while (m--) {
        ll x;//记得开long long！！！
        cin >> x;
        if (x < cnt)//如果x在模拟范围内
            cout << q[x][0] << ' ' << q[x][1] << endl;
        else {
            x -= cnt;//现将前面的模拟次数减去，此时队列为操作cnt次后的状态
            x %= (n - 1);//操作cnt次后，后面有n-1个元素，所以n-1为一个循环
            cout << a[maxt] << ' ' << c[l + x + 1] << endl;//一个是最大的元素，一个是最左端后的第x个元素（记得加一）
        }
    }
    return 0;
}
```


---

## 作者：wucstdio (赞：1)

### 题意

给你一个序列，每次拿出来开头的两个元素，把其中较大的放到开头，另一个放到结尾，求第$k$次拿出来的两个数。

### 题解

$k$很大，于是我们选择打表找规律：

$$\{2,3,4,5,1\}$$

$$\{3,4,5,1,2\}$$

$$\{4,5,1,2,3\}$$

$$\{5,1,2,3,4\}$$

$$\{5,2,3,4,1\}$$

$$\{5,3,4,1,2\}$$

$$\{5,4,1,2,3\}$$

$$\cdots$$

容易发现，当最大的数字$5$被移动到开头后，剩下的数字会不断进行循环移位。

同时我们发现最大的数字一定会被移动到开头，因为每一次操作它前面的数字都会减少一个。

所以我们只需要暴力求出前若干项，然后剩下的直接取模定位。

代码：（没开long long WA了一发）

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,q,a[500005],head,tail,b[500005],x[500005],y[500005],maxx;
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		maxx=max(maxx,a[i]);
	}
	head=1,tail=n;
	while(a[head]!=maxx)
	{
		int v1=a[head];
		int v2=a[head+1];
		x[++m]=v1;
		y[m]=v2;
		if(v1<v2)swap(v1,v2);
		a[++head]=v1;
		a[++tail]=v2;
	}
	for(int i=head+1;i<=tail;i++)b[i-head]=a[i];
	while(q--)
	{
		long long v;
		scanf("%I64d",&v);
		if(v<=m)printf("%d %d\n",x[v],y[v]);
		else
		{
			v-=m;
			printf("%d ",maxx);
			printf("%d\n",b[(v-1)%(n-1)+1]);
		}
	}
	return 0;
}
```

---

## 作者：gaoshengxiang (赞：0)

**Update 2023/8/1**

	1.增加文章注释
   	2.增加时间复杂度的描述
    3.增加关于数据范围的描述
有漏洞的地方欢迎补充。

# 主要思路

F1: 最朴素的算法：暴力按照题意模拟，时间复杂度 $O(\max(m_j))$。

F2: 先来模拟一下样例：
	
    1. 1 2 3 4 5
    2. 2 3 4 5 1
    3. 3 4 5 1 2
    4. 4 5 1 2 3
    5. 5 1 2 3 4
    6. 5 2 3 4 1
    
   不难发现，当最大的数移到最前面后，整个数组便开始循环。
   
   故我们只需模拟一个双端队列直到**最大值到队首**即可。
   
   对于询问：如果第 $m_j$ 次时最大值已经到队首，则按模拟输出；
   
   否则利用循环输出。
   
   时间复杂度：$O(n+q)$。
   
   注意到，$1\leq m_j \leq 10^{18}$，需要**开 long long**。

上代码：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
struct node{
	int fir , sec;
}s[100005];//记录最大值未到队首前的答案
int n , x , m , smax=-1 , ans , k[100005];
long long y;
deque<int>q;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>x;
		smax=max(smax,x);
		q.push_back(x);
	}
   //开始模拟
	for(int i=1;i>=1;i++){
		int a , b;
		a=q.front();
		q.pop_front();
		b=q.front();
		q.pop_front();
		s[i].fir=a;
		s[i].sec=b;
		q.push_front(max(a,b));
		q.push_back(min(a,b));
		if(max(a,b)==smax){//如果最大值到了队首
			ans=i;
			q.pop_front();
			for(int i=1;i<n;i++){
				k[i]=q.front();
				q.pop_front();
			}
			break;
		}
	}
	for(int i=1;i<=m;i++){
		cin>>y;
		if(y<=ans){//最大值没到队首
			cout<<s[y].fir<<' '<<s[y].sec<<endl;
		}
		else{//开始循环了
			long long p=y-ans;//利用循环节输出，注意，要用 long long
			p%=(n-1);
			s[n]=s[1];
			if(p==0){
				p=n-1;
			}
			cout<<smax<<' '<<k[p]<<endl;
		}
	}
}
```


---

## 作者：Ice_lift (赞：0)

# CF1179A Valeriy and Deque
[更好的观看体验](https://qinym-d.github.io/2023/06/26/CF1179A%20Valeriy%20and%20Deque/)

## 思路

首先，每次操作后会将大的那个数排至队首。所以说，当队列中最大的那个数到达队首时，队首元素将**不再改变**，而其他的元素依次循环。因此，我们可以记录最大数不在队首之前的操作，在其到达队首之后，记录其余元素的循环节即可。**注意：需要记录使最大数到达队首的步数，以便询问时判断取用哪个数组中的答案。**
## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 5;
int n, m, maxn, a, b;
deque<int> q;
struct Ans {//记录答案
	int Max, Min;
} ans[MAXN],res[MAXN];
int cnt,st;//cnt记录步数
void init(){//在最大数未到达前的操作
	a = q.front();q.pop_front();
	b = q.front();q.pop_front();
	ans[++cnt].Max = a;
	ans[cnt].Min = b;
	q.push_front(max(a, b));
	q.push_back(min(a, b));
}
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%lld", &x);
		maxn = max(x, maxn);
		q.push_back(x);
	}
	while (q.front() != maxn) {
		init();
	}
	q.pop_front();//由于队首固定，所以直接弹出
	for(int i=0;i<n-1;i++){
		res[i].Max=maxn;//队首数一定为最大数
		res[i].Min=q.front();
		q.pop_front();
	}
	for(int i=1;i<=m;i++){
		int p;
		scanf("%lld",&p);
		if(p<=cnt){//答案判断
			printf("%lld %lld\n",ans[p].Max,ans[p].Min);
		}else{
			int len=p-cnt-1;//循环的次数
			printf("%lld %lld\n",res[len%(n-1)].Max,res[len%(n-1)].Min);
		}
	}
	return 0;
}
```



---

## 作者：qwq___qaq (赞：0)

容易想到先预处理出所有的答案。

对于前 $n-1$ 次操作，可以直接暴力模拟；

这时，我们发现，所有数都至少比较过 $1$ 次，那么最大值一定放在队首，对于 $n$ 及其以后的操作，队首会依次弹出后面的 $n-1$ 个元素，那么此时就以 $n-1$ 形成了一个周期。也就是说，对于 $m>n-1$，我们得到的答案就是 $m\mod(n-1)+n-1$，如果 $m\mod(n-1)=0$，那么再加上一个 $n-1$。

---

## 作者：Aaplloo (赞：0)

额， 这道题， 先用 n 1e5跑出来知道队首最大， 再找到循环节即可，注意开long long.
```cpp
#include <queue>
#include <cstdio>
#define MAXN 100005
#define LL long long 
#define Int register int
using namespace std;
inline LL Max(const LL &x,const LL &y)
{
	return x > y ? x : y;
}
inline LL Min(const LL &x,const LL &y)
{
	return x < y ? x : y;
}
inline void read(LL &x)
{
	x = 0;
	LL f = 1;
	char s = getchar();
	while (s < '0' || s > '9')
	{
		if (s == '-')
			f = -1;
		s = getchar();
	}
	while (s >= '0' && s <= '9')
	{
		x = (x << 3) + (x << 1) + (s ^ 48);
		s = getchar();
	}
	x *= f;
}
LL MAX, Starttot, AS[MAXN], BS[MAXN], XHA[MAXN], XHB[MAXN];
deque<LL> Q;
int main()
{
	LL n, m;
	read( n ); read( m );
	for (Int i = 1; i <= n; ++ i)
	{
		LL a;
		read( a );
		MAX = Max(MAX, a);
		Q.push_back( a );
	}
	while (Q.front() != MAX)
	{
		Starttot ++;
		LL A = Q.front();
		Q.pop_front();
		LL B = Q.front();
		Q.pop_front();
		AS[Starttot] = A;
		BS[Starttot] = B;
		if (A > B)
		{
			Q.push_front( A );
			Q.push_back( B ); 
		}
		else
		{
			Q.push_front( B );
			Q.push_back( A );  
		}
	}
	for (Int i = 1; i < n; ++ i)
	{
		LL A = Q.front();
		Q.pop_front();
		LL B = Q.front();
		Q.pop_front();
		XHA[i] = A;
		XHB[i] = B;
		Q.push_front( A );
		Q.push_back( B ); 
	}
	while (m --)
	{
		LL x;
		read( x );
		if (x <= Starttot)
			printf("%lld %lld\n", AS[x], BS[x]);
		else
		{
			x -= Starttot;
			x %= (n - 1);
			if (! x) x = n - 1;
			printf("%lld %lld\n", XHA[x], XHB[x]);
		}
	}
	return 0;
}
```


---

## 作者：STOcjyORZ (赞：0)

# 大致思路
- 首先注意时间复杂度，以及要开longlong的细节 ~~（不开longlong见祖宗）~~
- 接下来本题的另一篇题解已经把方法讲的很清楚了，我来负责完善细节。
- 今天校内模拟赛里考的这道题，起先我先写纯暴力，但是由于操作次数最大是10的19次方，因此位数肯定爆数组了，接下来我又用循环队列的写法去模拟，结果TLE。当场心态爆炸，耗了好久忽然一看，这不是一道找规律嘛woc，最终用如下方法考场上还是写挂了，why？因为我用的输入输出是cin和cout，在**大概大于三十万次操作**时，scanf与cin的时间就会不一样（百度来的)


------------
# 做题反思
1. 少用cin和cout（如果对时间要求比较高的话）
1. 题目拿到手不要急于去做，有的题要先分析规律，否则事倍功半！
### 代码+解释部分如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[205000]={0},b[205000]={0};
long long zuida[205000]={0};//记录第i位以前的最大值为zuida【i】
long long ci,maxx=-12345;//ci是操作次数
int ask,n;//ask是询问次数
int h,t;//模拟队列
int main()
{
    int bj;
    cin>>n>>ask;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        b[i]=a[i]; 
        if(a[i]>maxx)
        {
            maxx=a[i];
            bj=i;//用于标记最大值的位置；
        }   
    }   
    zuida[1]=a[1];//赋初值
    for(int i=2;i<=n;i++)//递推过去
    {
        if(a[i]>zuida[i-1])
        {
            zuida[i]=a[i];
        }
        else
            zuida[i]=zuida[i-1];
    }
    h=1,t=n+1; 
	long long  pd;
    pd=bj-2+1;//pd==将最大的那个数放到最前面需要多少次
    for(int i=1;i<=pd;i++)//将数组转换成最大数在第一位的形式
    {
		if(b[h]>b[h+1])
		{	
		b[t]=b[h+1];
		b[h+1]=b[h];
		h++;
		t++;
		}
		else
		{
			b[t]=b[h];
			h++;
			t++;
		}
	}
    if(ask==0)//即样例2
    {
        return 0;
    }
    for(int i=1;i<=ask;i++)
    {
            scanf("%lld",&ci);
            if(ci==0)
            {
            cout<<0<<" "<<0<<endl;
            continue;
            }
        if(ci<=pd)//若ci小于把最大挪到第一位所需的次数
        {//则输出按顺序一定是前ci个数中最大的那个以及原数组第ci+1个数（自己画一下就知道了）
            printf("%lld %lld\n",zuida[ci],a[ci+1]);
        }
        else
        {//小心余数为零，刚好循环完
			long long yu=(ci-pd)%(n-1);
			if(yu==0) printf("%lld %lld\n",maxx,b[bj+n-1]);
            else printf("%lld %lld\n",maxx,b[bj+yu]);
        }   
    }   
return 0;
}
```


---

