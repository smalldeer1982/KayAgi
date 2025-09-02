# Complete the Projects (hard version)

## 题目描述

简单版和困难版的唯一区别在于，简单版要求你完成所有项目，而困难版则不要求。

Polycarp 是一位非常著名的自由职业者。他当前的评分为 $r$ 单位。

一些非常富有的客户请他为他们的公司完成一些项目。要完成第 $i$ 个项目，Polycarp 至少需要 $a_i$ 单位的评分；完成该项目后，他的评分会变化 $b_i$（评分会增加或减少 $b_i$，$b_i$ 可以为正或负）。Polycarp 的评分不能降到零以下，否则人们就不会信任评分如此低的自由职业者。

Polycarp 可以自行选择完成项目的顺序。此外，他甚至可以跳过某些项目。

为了获得更多的经验（当然还有金钱），Polycarp 想要选择一个包含尽可能多项目的子集，并决定完成它们的顺序，使得在开始每个项目之前，他的评分都足够，并且在完成每个项目后评分不会为负。

你的任务是计算 Polycarp 能够选择的最大项目子集的大小。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 4
4 6
10 -2
8 -1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 20
45 -6
34 -15
10 34
1 27
40 -45
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 2
300 -300
1 299
1 123
```

### 输出

```
3
```

# 题解

## 作者：yimuhua (赞：14)

# 题意：

$n$ 个项目，初始时评级为 $r$。每个项目中有两个数值 $a_i$ 和 $b_i$，$a_i$ 表示只有 $r\geq a_i$ 才能做这个项目，$b_i$ 表示完成这个项目后 $r$ 会加上 $b_i$ (可正可负)。求通过调整项目顺序最多可以完成多少项目。

# 思路：

贪心决定顺序，**DP**完成选择

## 贪心：

对于 $b_i \geq 0$，显然可以按照 $a_i$ 从小到大排序，算出 $cnt$ 和 $r$；

对于 $b_i < 0$，则按照 $a_i+b_i$ 从大到小排序

[具体证明](https://www.luogu.com.cn/blog/qcwlmqy/solution-cf1203f1)

可以将 $a_i+b_i$ 看作做完此任务后的 $r$ 的下界来理解

## DP：

### 方法一：

$dp_{i,j}$ 表示考虑完前 $i$ 个项目后评分为 $j$ 的最大任务完成数

枚举前面的任务，枚举能力值，满足条件则转移。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, r, cnt, ans, cnt1, cnt2, dp[105][60005];
struct node {
    int x, y;
}a[105], b[105];
bool cmp(node x, node y) {
    return x.x < y.x;
}
bool cmp2(node x, node y) {
    return x.x + x.y > y.x + y.y;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> r;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if(y < 0)
            b[++cnt2] = (node){x, y};
        else
            a[++cnt1] = (node){x, y};
    }
    sort(a + 1, a + cnt1 + 1, cmp), sort(b + 1, b + cnt2 + 1, cmp2);
    for(int i = 1; i <= cnt1; i++)
        if(r >= a[i].x)
            r += a[i].y, cnt++;
        else
            break;
    for(int i = 1; i <= cnt2; i++)
        if(r >= max(b[i].x, abs(b[i].y))) {
            dp[i][r + b[i].y] = 1, ans = max(ans, 1);
            for(int j = i - 1; j; j--)
                for(int k = max(b[i].x, abs(b[i].y)); k < 60001; k++)
                    if(dp[j][k])
                        dp[i][k + b[i].y] = max(dp[i][k + b[i].y], dp[j][k] + 1), ans = max(ans, dp[i][k + b[i].y]);
        }
    cout << cnt + ans;
    return 0;
}
```
时间复杂度为 $O(n \times b_i)$

### 方法二：

虽然方法一可以通过此题，但是我们不妨想想如何更快。

根据方法一可知，在评分确定时要最大化任务数，于是我们可以将第二维替换，在任务数确定时最大化评分

所以 $dp_{i,j}$ 表示前 $i$ 个任务完成任务数为 $j$ 时的最大评分

枚举任务和完成任务数，条件满足则转移。最后枚举 $dp_{cnt2,i}$，找到最大的 $dp_{cnt2,i}\geq 0$ 的 $i$

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, r, cnt, ans, cnt1, cnt2, dp[105][105];
struct node {
    int x, y;
}a[105], b[105];
bool cmp(node x, node y) {
    return x.x < y.x;
}
bool cmp2(node x, node y) {
    return x.x + x.y > y.x + y.y;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> r;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if(y < 0)
            b[++cnt2] = (node){x, y};
        else
            a[++cnt1] = (node){x, y};
    }
    sort(a + 1, a + cnt1 + 1, cmp), sort(b + 1, b + cnt2 + 1, cmp2);
    for(int i = 1; i <= cnt1; i++)
        if(r >= a[i].x)
            r += a[i].y, cnt++;
        else
            break;
    for(int i = 1; i <= cnt2; i++)
        for(int j = 0; j <= i; j++)
            dp[i][j] = -1e9;
    dp[1][0] = r;
    if(b[1].x <= r && abs(b[1].y) <= r)
        dp[1][1] = r + b[1].y;
    for(int i = 1; i <= cnt2; i++)
        for(int j = 0; j <= i; j++) {
            if(b[i + 1].x <= dp[i][j])
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + b[i + 1].y);
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
        }
    for(int i = 1; i <= cnt2; i++)
        if(dp[cnt2][i] >= 0)
            ans = max(ans, i);
    cout << cnt + ans;
    return 0;
}
```
时间复杂度为 $O(n^2)$
### 方法三：

我们考虑舍弃 DP，转而用带反悔的贪心来完成选择

我们可以使用优先队列来维护在当前任务之前所有已选任务中 $b_i$ 最小的，也就是扣分最多的，在判断去除此任务后当前任务是否能完成

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, r, cnt, ans, cnt1, cnt2;
struct node {
    int x, y;
    bool operator < (const node &b) const {
        return y > b.y;
    }
}a[105], b[105];
bool cmp(node x, node y) {
    return x.x < y.x;
}
bool cmp2(node x, node y) {
    return x.x + x.y > y.x + y.y;
}
priority_queue<node> pq;
int main() {
    ios::sync_with_stdio(0);
    cin >> n >> r;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if(y < 0)
            b[++cnt2] = (node){x, y};
        else
            a[++cnt1] = (node){x, y};
    }
    sort(a + 1, a + cnt1 + 1, cmp), sort(b + 1, b + cnt2 + 1, cmp2);
    for(int i = 1; i <= cnt1; i++)
        if(r >= a[i].x)
            r += a[i].y, cnt++;
        else
            break;
    for(int i = 1; i <= cnt2; i++)
        if(r >= b[i].x && r + b[i].y >= 0)
            r += b[i].y, pq.push(b[i]), ans++;
        else if(!pq.empty() && pq.top().y < b[i].y) {
            r -= pq.top().y;
            if(r >= b[i].x)
                r += b[i].y, pq.pop(), pq.push(b[i]);
            else
                r += pq.top().y;
        }
    cout << cnt + ans;
    return 0;
}
```
在最后一份代码中，有这样一段：

```cpp
if(r >= b[i].x)
    r += b[i].y, pq.pop(), pq.push(b[i]);
else
    r += pq.top().y;
```
我们发现这个判断其实不需要，可以证明：

对于 $a_1,b_1,a_2,b_2,a_3,b_3$

+ $a_1+b_1 \geq a_2+b_2 \geq a_3+b_3$

+ $r \geq a_1,r+b_1 \geq a_2,r+b_1+b_2<a_3$

+ $b_1\leq b_2,b_1\leq b_3$

求证 $r+b_2\geq a_3$

证：

$\because b_1<b_3$

$\therefore a_3+b_3>a_3+b_1$

$\because r+b_1\geq a_2$

$\therefore r+b_1+b_2 \geq a_2+b_2\geq a_3+b_3\geq a_3+b_1$

$\therefore r+b_2\geq a_3$

对于 $a_1,b_1,a_2,b_2,a_3,b_3,a_4,b_4$

+ $a_1+b_1 \geq a_2+b_2 \geq a_3+b_3 \geq a_4+b_4$

+ $r \geq a_1,r+b_1 \geq a_2,r+b_1+b_2\geq a_3,r+b_1+b_2+b_3<b_4$

+ $b_1\leq b_2,b_1\leq b_3,b_1\leq b_4$

求证 $r+b_2+b_3\geq a_4$

证：

$\because b_1<b_4$

$\therefore a_4+b_4>a_4+b_1$

$\because r+b_1+b_2\geq a_3$

$\therefore r+b_1+b_2+b_3\geq a_3+b_3\geq a_4+b_4 \geq a_4+b_1$

$\therefore r+b_2+b_3\geq b_4$

以此类推

最终代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, r, cnt, ans, cnt1, cnt2;
struct node {
    int x, y;
    bool operator < (const node &b) const {
        return y > b.y;
    }
}a[105], b[105];
bool cmp(node x, node y) {
    return x.x < y.x;
}
bool cmp2(node x, node y) {
    return x.x + x.y > y.x + y.y;
}
priority_queue<node> pq;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> r;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if(y < 0)
            b[++cnt2] = (node){x, y};
        else
            a[++cnt1] = (node){x, y};
    }
    sort(a + 1, a + cnt1 + 1, cmp), sort(b + 1, b + cnt2 + 1, cmp2);
    for(int i = 1; i <= cnt1; i++)
        if(r >= a[i].x)
            r += a[i].y, cnt++;
        else
            break;
    for(int i = 1; i <= cnt2; i++)
        if(r >= b[i].x && r + b[i].y >= 0)
            r += b[i].y, pq.push(b[i]), ans++;
        else if(!pq.empty() && pq.top().y < b[i].y)
            r -= pq.top().y, r += b[i].y, pq.pop(), pq.push(b[i]);
    cout << cnt + ans;
    return 0;
}
```


---

## 作者：AK_CSP_SZAuQH (赞：9)

## 题意简述
这一个人在完成第 $i$ 个项目时，必须要 $rating \ge a_i$ 的时候，并且要满足 $rating + b_i$ 后 $rating \ge 0$，最后求最多能完成多少个项目。

## 题目分析
理解完题目后，发现题目其实就是要求一个最多能完成多少个项目的问题，碰到最多、最少类的问题，我们考虑几种情况：

1. 动态规划；

2. 贪心；

3. 前两种方式结合起来。

为什么我们这一题需要使用到两种方式呢？我们可以来分情况讨论一下： 

1. 当 $b_i\ge0$ 的时候，我们可以使用贪心策略来完成，这里的贪心策略是：把正数 $a_i$ 给进行从小到大排序，每次只要 $rating\ge a_i$ 的情况被满足，我们就把这一个项目做下去，否则就不做，直接退出循环。

2. 当 $b_i<0$ 的时候，我们就需要使用贪心和动态规划相结合了，我们采用的排序方式时 $a_i+b_i$ 的和从小到大排序，原本如果只采用贪心的策略去完成的话，贪心策略应该是 $a_i+b_i$ 从大到小排序，但为什么这一题的排序顺序变了呢？原因就是采用了 01 背包，我们都知道背包是由以前已经有的状态来推导现在的状态，因此应该是反着排序。

解决了排序的问题，我们现在来解决一下为什么这一题要使用动态规划这个问题，证明如下：

假设初始 $rating$ 为 $10$ 时，$a_1$、$a_2$、$a_3$ 的值分别是 $10$、$3$、$3$。

$b_1$、$b_2$、$b_3$ 的值分别是 $-8$、$-2$、$-1$ 时。

如果我们用贪心做的话，我们发现最多只能完成**一个项目**，但我们如果只选择第 $2$、$3$ 个项目去完成的话，我们能得到更优的**两个项目**的答案。所以，我们碰到这一种**选或不选**的问题，我们通常会采用 **01 背包** 来解决问题。

紧接着，我们来解决怎么进行 01 背包的问题。

现在来定义一个状态，$f(i,j)$ 表示的是第 $i$ 个项目当 $rating$ 为 $j$ 的时候最多能够完成多少个任务，那就有了做或不做两种情况：

1. 不做，那么我们就可以由上一个项目 $rating$ 为 $j$ 的情况转移过来，也就是 $f(i,j)=f(i-1,j)$。

2. 做，那么我们要满足两个条件：

(1) 现在的 $rating\ge a_i$；

(2) 现在的 $rating+b_i\ge0$。

所以我们的状态转移方程就是 $f(i-1,j+b_i)+1$。

**注意：是要在 $j+b_i \ge 0$ 的情况成立下。**

这样我们的最终的答案就是，在正数那一部分得到的答案 $+f(n,rating)$。这里的 $rating$ 指的是做完正数后的 $rating$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline void read(int &x){
	int f=1;x=0;
	char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	x*=f;
}
const int N=1e6+5;
int n,s,A,B,f[N],ans,jzs,jfs,maxx;
struct z{
	int a,b;
}zs[N];//正数 
bool cmp(z x,z y){
	return x.a<y.a;
}
struct ff{
	int a,b;
}fs[N];//负数 
bool cmp2(ff x,ff y){
	return x.a+x.b<y.a+y.b;
}//上面讲述到的贪心排序策略 
signed main(){
	read(n),read(s);
	for(int i=1;i<=n;i++){
		read(A),read(B);
		if(B>=0) zs[++jzs].a=A,zs[jzs].b=B;
		else fs[++jfs].a=A,fs[jfs].b=B;
		/*
			正负数分段，使用结构体存储 
		*/
	}
	sort(zs+1,zs+jzs+1,cmp);
	sort(fs+1,fs+jfs+1,cmp2);
	for(int i=1;i<=jzs;i++){
		if(s<zs[i].a or s+zs[i].b<0) break;//能做就做，不然就退出 
		s+=zs[i].b,ans++;
	}
	/*
		这里对01背包进行了一个小优化，优化成一维数组 
	*/
	for(int i=1;i<=jfs;i++){
		for(int j=s;j>=fs[i].a;j--)//当rating满足题目要求时 
			if(j+fs[i].b>=0) f[j]=max(f[j],f[j+fs[i].b]+1);
	}
	printf("%lld",ans+f[s]);//输出答案，正数部分得到的答案+负数部分得到的答案 
	return 0; 
}
```

那这一题就圆满结束啦！

---

## 作者：ycyaw (赞：9)

对于$b_i$为正的任务，显然贪心，按$a_i$从小到大排序，当前能力值大于等于$a_i$就选上。

剩下一堆任务，题目变成，选第$i$个任务需要$a_i$能力值，做完这个任务能力值减少$b_i$。考虑$dp$，$f[i][j]$表示做前$i$个任务，能力值为$j$，最多能做多少个任务。

枚举前面的任务，枚举能力值，满足条件则转移。

$dp$前要对任务排序，我们考虑按$a_i+b_i$排序，这样显然后面的任务不会影响前面的任务。

$Code \ Below:$
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
#define pc putchar
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
int n,r,cnt1,cnt2,ans,f[105][60005],res;
struct node{
    int x,y;
}a[10005],b[10005];
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-ff;ch=getchar();}
    while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+ch-'0';ch=getchar();}
    return ret*ff;
}
void write(int x){
    if(x<0){x=-x;putchar('-');}
    if(x>9) write(x/10);
    putchar(x%10+48);
}
inline bool cmp1(node A,node B){
    return A.x<B.x;
}
inline bool cmp2(node A,node B){
    return A.x+A.y>B.x+B.y;
}
signed main(){
    n=read(),r=read();
    for(int i=1;i<=n;i++){
        int x=read(),y=read();
        if(y>=0) a[++cnt1]=(node){x,y};
        else b[++cnt2]=(node){x,y};
    }
    sort(a+1,a+cnt1+1,cmp1);
    int now=r;
    for(int i=1;i<=cnt1;i++){//先把正的都选上 
        if(now>=a[i].x){
            ans++;
            now+=a[i].y;
        }
        else break;
    }
    sort(b+1,b+cnt2+1,cmp2);
    for(int i=1;i<=cnt2;i++){
        if(now>=b[i].x&&now>=abs(b[i].y)){
            f[i][now-abs(b[i].y)]=1;
            res=max(res,1);
            for(int j=i-1;j>=1;j--)
                for(int k=max(abs(b[i].y),b[i].x);k<=60000;k++)
                    if(f[j][k]){
                        f[i][k-abs(b[i].y)]=max(f[i][k-abs(b[i].y)],f[j][k]+1);    
                        res=max(res,f[i][k-abs(b[i].y)]);
                    }
        }
    }
    write(ans+res);
    return 0;
}
```


---

## 作者：RainFestival (赞：4)

$\rm Difficulty = \color{orange}2300$

我们发现当 $b_i\ge 0$ 与 $b_i<0$ 情况不同，考虑分类讨论：

一个显然的观察得出，如果我们做任务 $x,y$，那么无论以什么顺序完成这些任务，即不论 $(x,y)$ 和 $(y,x)$，是没有对后面其他任务产生影响的。**于是我们只用关心相邻两个任务的顺序问题。**

注意到如果我们无论如何安排 $x,y$ 两个任务的顺序都只能完成其中的 $1$ 个或者 $0$ 个任务了，那么对于顺序的考虑是没有意义的。

也就是说，如果我们无论怎么调节这两个的任务的被考虑顺序，都不能找到一种两个任务都被完成的方案，那么这两个任务的被考虑的顺序是无关的。

说的通俗一些，只完成一个任务（或者不完成任务）硬着头皮完成它就行了，考虑个鬼的顺序！

于是我们思考两个任务都被完成的情况。

**显然我们先做 $b_i\ge0$ 的任务。**

**当 $b_i\ge0$ 的时候，我们对 $a_i$ 从小到大排序，然后依次考虑，如果能做就一定做。**

我们来简单说明以上结论的正确性。

注意到一个关键性质，就是说完成更多的 $b_i\ge 0$ 的问题，只会让评分上升（或保持不变），一定不会让评分下降，因此

+ 原先完成不了的任务，完成了一些其它任务之后回过头来继续完成这个任务，有可能还是完成不了，也有可能可以完成了。

+ 原先可以完成的任务，完成了一些其它任务之后回过头来继续完成这个任务，一定还可以完成。

对于一对完成顺序是相邻的两个任务 $x,y$，不妨设 $a_x\le a_y$。

我们考虑交换 $x,y$，则 $y$ 被先做。

如果原先的评分不足，是不可以完成 $y$ 的，而我们有可能通过先完成 $x$ 上涨评分后完成 $y$。这样就多完成任务 $y$。

如果原先评分连 $x$ 都不能完成，那么 $y$ 更不能完成了，评分的上涨一定是 $0$。

**当 $b_i<0$ 的时候，我们对 $a_i+b_i$ 从大到小排序，然后依次考虑。用动态规划解决问题。**

我们来简单说明以上结论的正确性。

注意到一个关键性质，就是说完成更多的 $b_i<0$ 的问题，只会让评分下降，一定不会让评分上升（或不变），因此

+ 原先完成不了的任务，完成了一些其它任务之后回过头来继续完成这个任务，还是完成不了。

+ 原先可以完成的任务，完成了一些其它任务之后回过头来继续完成这个任务，有可能还可以完成，也有可能完成不了了。

对于一对完成顺序是相邻的两个任务 $x,y$，不妨设 $a_x\ge a_y$。

最初的时候，评分一定要 $\ge a_x$，否则一定不能把两个任务都完成，也就失去了寻找他们被考虑顺序的意义。

所以，我们只需要想考虑这两个任务之前，评分 $\ge a_x$ 的情况。

因为评分 $\ge a_x$，所以也一定 $\ge a_y$ 所以我们无论先完成哪一个任务都是可以的，唯一只需要考虑在完成了第一个任务以后，另外一个任务是否可以完成。

记考虑这两个任务之前，评分为 $r$。

如果我们先完成任务 $x$，那么我们要保证 $r+b_x\ge a_y$ 才能再完成任务 $y$。

如果我们先完成任务 $y$，那么我们要保证 $r+b_y\ge a_x$ 才能再完成任务 $x$。

由于我们要完成更多的任务，于是要考虑更松的下界。

先完成 $x$，要求 $r\ge a_y-b_x$。

先完成 $y$，要求 $r\ge a_x-b_y$。

所以我们比较 $a_y+b_x$ 与 $a_x+b_y$ 的大小关系，来得出考虑 $x$ 与 $y$ 的先后顺序。

移项，可以知道当 $a_x+b_x>a_y+b_y$ 的时候，先完成 $x$ 更优秀；当 $a_x+b_x<a_y+b_y$ 的时候，先完成 $y$ 更优秀。如果 $a_x+b_x=a_y+b_y$, 那么先完成谁都可以。

这样，我们解决了任务的考虑顺序这一问题。

对于 $b_i\ge 0$，我们显然是能完成更多任务就完成更多。

对于 $b_i<0$，我们则需要使用动态规划，因为有些先被考虑的任务，可能因为 $b_i$ 太小，对评分的扣减太多，而不去完成。

如何做这个动态规划呢？

我们记 $dp_{i,j}$ 为考虑完评分为 $i$ 的任务后，当前评分为 $j$ 的最多完成多少个任务。

$dp_{i,j}$ 从哪里转移过来呢？我们只需要考虑完成 $i$ 号任务和不完成 $i$ 好任务就行了两种情况就行了。

记考虑完 $b_i\ge 0$ 的任务后积累的评分为 $r$，总共完成了 $k$ 个任务。

完成 $i$ 号任务，则完成任务前原先的评分 $j'$ 为 $j-b_i$。一定要满足 $a_i\le j'\le r$。

不完成 $i$ 号任务，则完成任务前原先的评分 $j'$ 为 $j$。$j'$ 不需要满足额外的额外的条件。

在满足条件的情况下，$dp_{i,j}=\max{dp_{i-1,j'}+1}$。

初始条件如果 $x=r$ 那么 $dp_{0,x}=k$，否则 $dp_{0,x}=0$。

完成任务的总数目 $s$，就是 $\max\limits_{x=0}^{r}dp_{n,r}$，这是因为最后剩余的评分只要大于 $0$ 一定是可以的，当然它也不可能 $>r$。

于是我们就解决了这个问题。

代码如下：

```cpp
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<algorithm> 
int n,r,m,cnt,dp[105][100005],ans=0;
std::pair<int,int> p[105],s[105];
int cmp(std::pair<int,int> a,std::pair<int,int> b){return a.first+a.second>b.first+b.second;} 
int main()
{
	scanf("%d%d",&n,&r);
	for (int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (y>=0) p[++m]=std::make_pair(x,y);
		else s[++cnt]=std::make_pair(x,y);
	}
	std::sort(p+1,p+m+1);
	std::sort(s+1,s+cnt+1,cmp);
	for (int i=1;i<=m;i++) if (r>=p[i].first) r=r+p[i].second,++ans;
	for (int i=0;i<=cnt;i++) for (int j=0;j<=r;j++) dp[i][j]=-1000000000;
	dp[0][r]=ans;
	for (int i=1;i<=cnt;i++)
		for (int j=0;j<=r;j++)
		{
			dp[i][j]=dp[i-1][j];
			if (j>=s[i].first+s[i].second&&r+s[i].second>=j) dp[i][j]=std::max(dp[i][j],dp[i-1][j-s[i].second]+1);
		}
	ans=0;
	for (int x=0;x<=r;x++) ans=std::max(ans,dp[cnt][x]);
	printf("%d\n",ans);
	return 0;
}
```

时间 $\tt 255ms$ 内存 $\tt 40.04MB$ 代码长度 $\tt 936B$ 

---

## 作者：This_Rrhar (赞：4)

## 题目分析

有 $n$ 个项目，初始的 $rating$ 为 $r$，第 $i$ 个项目分别有两个属性 $a_i,b_i$，表示当 $rating \ge a_i$ 时才能做此项目，完成项目后 $rating$ 提升 $b_i$（$b_i$ 可能为负数）。$rating$ 必须保持大于等于 $0$，问最多完成多少个项目。

## 解题思路

对于这道题，由于有一部分任务会增加 $rating$，一部分会减少 $rating$，考虑先完成 $b_i$ 值为正的项目让 $rating$ 达到可以达到的最大值后再完成 $b_i$ 值为负的项目，也就是将项目分成两部分：$b_i \ge 0$ 和 $b_i < 0$。

### 贪心部分

为了让 $rating$ 达到可达到的最大值，使用贪心策略：按 $a_i$ 从小到大排序，然后顺序遍历，如果当前的 $rating \ge a_i$ ，则可以完成第 $i$ 个项目，否则表示 $rating$ 无法再增加，因为第 $i$ 个项目及后面的所有项目所需的 $rating$ 都达不到。

### 动态规划部分

当 $rating$ 达到可达到的最大值时表示无法再增加，此时开始做 $b_i$ 为负值的项目。但由于完成一个项目后会使 $rating$ 下降，导致无法完成其它项目，也就是无法按照某个标准来决定优先完成哪个项目，所以考虑使用动态规划。

#### 排序

在动态规划之前，首先要确定项目出现的顺序：设有两个项目，编号分别为 $x,y$，如果要完成 $x$ 再完成 $y$，则当前 $rating$ 需要满足

$$
rating + b_x \ge a_y
$$

如果要完成 $y$ 再完成 $x$，则要满足

$$
rating + a_x \ge b_y
$$

当其中一个被满足时，另一条不能被满足。如果要先完成 $x$ 再完成 $y$，通过移项可以得到两条需要满足的条件：

$$
\begin{cases} rating \ge a_y - b_x\\rating < b_y - a_x \end{cases}
$$

也就是

$$
b_y - a_x > rating \ge a_y - b_x
$$

当然，在排序时不需要知道 $rating$ 的确切值，所以比较 $x,y$ 的出现顺序的函数 `cmp` 可以写成 $b_y-a_x>a_y-b_x$。

当然也可以通过移项改写成 $a_x + a_y > b_x + b_y$。

#### 状态转移方程

设 $dp_j$ 为 $rating \le j$ 时最多能完成的项目数量，则对于每个 $b_i < 0$ 的项目 $i$，有如下的状态转移方程：

$$
dp_j = \begin{cases} 0&j = 0 \\ \max(dp_j,dp_{j + b_i} + 1)&j > 0 \end{cases}
$$

注意：**在这个方程中的所有 $b_i$ 都为负值，所以应该用加号**。

## AC代码（C++20）

```cpp
#include<bits/stdc++.h>
using namespace std;
struct pj{int a,b;}t;
int n,s,dp[1000001],ans;
vector<pj>x,y;
inline bool cmp1(pj p,pj q){return p.a<q.a;}
inline bool cmp2(pj p,pj q){return p.a+p.b<q.a+q.b;}
int main()
{
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&t.a,&t.b);
		if(t.b>=0)x.push_back(t);
		else y.push_back(t);
	}
	sort(x.begin(),x.end(),cmp1),sort(y.begin(),y.end(),cmp2);
	for(pj i:x)
	{
		if(s<i.a)break;
		s+=i.b,ans++;
	}
	for(pj i:y)for(int j=s;j>=1;j--)if(j>=i.a&&j+i.b>=0)
		dp[j]=max(dp[j],dp[j+i.b]+1);
	printf("%d",ans+dp[s]);
}
```



---

## 作者：walk_out_study (赞：3)

### 题意
有 n 件商品，你有 $s$ 元，对于第 $i$ 件，需要有 $need_i$ 元，但只会花费 $val_i$ 元（$val_i$ 对应 $-b_i$），不能欠钱。

$1\leq n \leq100,1\leq s\leq30000,1\leq need_i\leq30000,-300\leq val_i\leq300$

### 思路

将原题变成以上题意，就挺有趣的。

#### 送钱！
$val_i\leq0$，意味着送钱。送钱还不要么，全收。   
根据以上奇妙理解，就可以得出本题的一个关键：

贪心。尝试将 $val_i \leq0$ 的全部收下，这里要将 $need_i$ 从小到大排序，边买边判断，可以买到更多的商品。

---
#### 背包

剩下的商品需要购买。此时就要考虑一个问题：“如何保证取商品的顺序”，如考虑不周，会出现错误。

假设 $need_n$，$val_n$ 很大，从大往小取可能就有问题。应该反过来。

假设我们要购买第 $a$，第 $b$ 两个商品，并且能满足条件。那么就有两种情况：

1. 先买 $a$，再买 $b$：$s-val_a \ge need_b$

1. 先买 $b$，再买 $a$：$s-val_b \ge need_a$

两式同时移项得：
$$\begin{cases}s \ge need_b+val_a\\s \ge need_a+val_b\end{cases}$$

假设第一种更优，即 $a$ 排在前面，那么 $need_b+val_a$ 就要尽量小。就有：
$$need_b+val_a < need_a+val_b$$
将左边的 $need_b$ 与右边的 $need_a$ 分别移项：
$$val_a-need_a < val_b-need_b$$

按照这个排序就好啦~~


##### 背包的实现

然后进行背包，还是有一点区别的...

```cpp
if(j+yyx2[i].val>=yyx2[i].need) dp[j]=max(dp[j],dp[j+yyx2[i].val]+1);
//本题背包
f[j]=max(f[j],f[j-a[i]]+b[i]);//正常的
```

这题是**剩下的价值会减少**，所以要反过来，数组的循环也要反过来。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node {
	int need,val;
}a1[111],a2[111];
int l1,l2,ans1,n,s,dp[111111],ans;
int main() {
	memset(dp,-0x3f,sizeof(dp));
	cin>>n>>s;
	for(int i=1,a,b;i<=n;i++) {
		cin>>a>>b;
		b=-b; 
		if(b<=0)
			a1[++l1]=Node{a,b};
		else 
			a2[++l2]=Node{a,b};
	}
	sort(a1+1,a1+l1+1,[](Node a,Node b) {return a.need<b.need;});
	sort(a2+1,a2+l2+1,[](Node a,Node b) {return a.val-a.need<b.val-b.need;});
	for(int i=1;i<=l1;i++)
		if(s>=a1[i].need) 
			ans1++,s-=a1[i].val;
	dp[s]=0;
	for(int i=1;i<=l2;i++) 
		for(int j=0;j<=60000;j++) {
			if(j+a2[i].val>=a2[i].need) 
				dp[j]=max(dp[j],dp[j+a2[i].val]+1);
			ans=max(dp[j],ans);
		}
	cout<<ans+ans1;
	return 0;
}
```

---

## 作者：Garbage_fish (赞：2)

## 一、分析题目

 [题目链接](https://www.luogu.com.cn/problem/CF1203F2)
 
对于不同的增加的声望值 $b_i$，可以分为两种情况：

> $1$. $ b_i\ge 0 $

> $2$. $ b_i\le 0 $

第 $1$ 种情况，可以采取贪心的策略，而第 $2$ 种情况可以采用动态规划的策略。

## 二、代码实现

### 1. 分类

首先，需要将增加的 $rating$ 按正数和负数分开到两个数组中。由于后面要排序，为了方便，此处应该选用 struct 结构体来存储。

### 2. 贪心

贪心时，应该先按 $rating$ 的要求 **从小到大** 排序，让~~这个可怜的~~项目经理先完成 $rating$ 要求尽量低的来增加更多的 $rating$，从而来完成更多的项目。

若当枚举到第 $i$ 个项目时，项目经理已经无法完成这个项目，那么后面的项目肯定也无法完成，所以此时可以直接退出贪心。


### 3. 动态规划

#### ①. 排序

在动态规划之前，要先确定动态规划选择的顺序：

设当处理完正数的情况时，项目经理的 $rating$ 为 $x$，接下来有两个项目，要求的 $rating$ 数分别是 $a_1$、$a_2$，增加的 $rating$ 分别是 $b_1$、$b_2$，那么，若要想同时都能完成两个，第一个放在第二个之前就要满足：

> $x+b_1\ge a_2$，即 $x\ge a_2-b_1$

反之，就要满足：

> $x+b_2\ge a_1$，即 $x\ge a_1-b_2$

所以我们的 cmp 要返回 $a_1-b_2$ 是否小于 $a_2-b_1$，即 $a_1+b_1$ 是否大于 $a_2+b_2$。

#### ②. 状态转移方程

若用 $i$ 来表示执行的第 $i$ 个项目，用 $j$ 来表示 $rating$ 值，用 $dp_j$ 来表示最多可完成的题目，用 $a_i$ 来表示要求的 $rating$ 值，用 $b_i$ 来表示增加的 $rating$ 值，那么就可以得到状态转移方程：
$$dp_{j+b_i}=\max(dp_{j+b_i}, dp_j+1), \max(a_i,-b_i)\le j\le 6\times 10^4$$

需要注意的是，$j$ 的起点不应该只是 $a_i$ ，因为若 $j=a_i$ 且 $a_i+b_i<0$ 时，$dp_{j+b_i}$ 就会发生数组越界，从而获得一个大大的 **RE**

## 三、代码展示
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,zn,fn,s,dp[100010],cnt,maxx;
struct A{
	int a,b;
}z[110],f[110];
//+     - 
bool cmpz(A x,A y){
	return x.a<y.a;
}
bool cmpf(A x,A y){
	return x.a+x.b>y.a+y.b;
}
int main(){
	scanf("%d%d",&n,&s);
	//1. 分类 
	for(int i=1;i<=n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		if(b>=0)z[++zn]=(A){a,b};
		else f[++fn]=(A){a,b};
	}
	//2. 贪心 
	sort(z+1,z+zn+1,cmpz);
	for(int i=1;i<=zn;i++){
		if(s>=z[i].a){
			cnt++;//统计增加的 rating 值为正数的项目中可完成的个数 
			s+=z[i].b;
		}
        else break;
	}
	//3. 动态规划
	sort(f+1,f+fn+1,cmpf);
	dp[s]=cnt,maxx=cnt;
	for(int i=1;i<=fn;i++){
    	for(int j=max(-f[i].b,f[i].a);j<=s;j++){
            dp[j+f[i].b]=max(dp[j+f[i].b],dp[j]+1);
            maxx=max(maxx,dp[j+f[i].b]);
		}
    }
	printf("%d",maxx);
}
```

---

## 作者：qcwlmqy (赞：2)

### 思路

**选择既有个数的限制，又有选择顺序的限制**

**是不是很像背包问题加贪心的结合版**

我们可以先用贪心决定选择的顺序，最后使用背包完成数量的选择

- 贪心
- 对于$b[i] > 0$按$a[i]$排序
- 对于$b[i] < 0$按$a[i] + b[i]$排序
- [证明链接](https://www.luogu.org/blog/qcwlmqy/solution-cf1203f1)
- DP
- 状态$dp[i]$表示rating为$i$时，最多完成项目数
- 状态转移方程`$dp[i + b[i]] = max(dp[i] + 1, dp[i + b[i])$

### 代码

DP


```cpp
for (int i = 1; i <= ml; i++) {
for (int j = 60000; j >= a[i].first; j--)
		if (dp[j] != -1) dp[j + a[i].second] = max(dp[j] + 1, dp[j + a[i].second]);
}
for (int i = 1; i <= mr; i++) {
for (int j = b[i].first; j <= 60000; j++)
		if (dp[j] != -1 && j + b[i].second >= 0) dp[j + b[i].second] = max(dp[j] + 1, dp[j + b[i].second]);
}
```

AC


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 105;
                 pii a[maxn], b[maxn];
bool cmp_a(const pii& a, const pii& b) {
	if (a.first == b.first) return a.second > b.second;
	return a.first < b.first;
}
bool cmp_b(const pii& a, const pii& b) {
	if (a.first + a.second == b.first + b.second) return a.second > b.second;
	return a.first + a.second > b.first + b.second;
}
int dp[66666];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, r, x, y;
	cin >> n >> r;
	int ml = 0, mr = 0;
	for (int i = 1; i <= n; i++) {
		cin >> x >> y;
		if (y >= 0)a[++ml] = pii(x, y);
		else b[++mr] = pii(x, y);
	}
	int k = ml;
	sort(a + 1, a + 1 + ml, cmp_a);
	sort(b + 1, b + 1 + mr, cmp_b);
	memset(dp, -1, sizeof(dp));
	dp[r] = 0;
	for (int i = 1; i <= ml; i++) {
		for (int j = 60000; j >= a[i].first; j--)
			if (dp[j] != -1) dp[j + a[i].second] = max(dp[j] + 1, dp[j + a[i].second]);
	}
	for (int i = 1; i <= mr; i++) {
		for (int j = b[i].first; j <= 60000; j++)
			if (dp[j] != -1 && j + b[i].second >= 0) dp[j + b[i].second] = max(dp[j] + 1, dp[j + b[i].second]);
	}
	int ans = -1;
	for (int i = 0; i <= 60000; i++)ans = max(dp[i], ans);
	cout << ans << '\n';
}
```



---

## 作者：cjrqwq (赞：1)

### 题干
给定任务个数 $n$ 和初始值 $r$，第 $i$ 个任务至少需要 $r$ 为 $a_i$ 时才能做，完成后 $r$ 会增长 $b_i$，每次完成任务后的能力值必须大于等于 $0$，最多能做多少个任务。
### 思路
一道贪心题，考虑 dp。  

> 对第一个或最后一个阶段进行**分类讨论**，化原问题为子问题。——某老师 

因为 $-300 \le b_i \le 300$，显然，分类讨论从 $b_i$ 入手,分正负两种。  

对于 $b_i \ge 0$ 的任务，比较简单，即对应的 $a_i$ 从小到大排序，当前能力值 $r \ge a_i$ 就选上。  

对于剩下的（$b_i<0$）任务，就需要解决“做第 $i$ 个任务需要 $a_i$ 的能力值，做完减少 $b_i$（此时 $b_i$ 为原 $b_i$ 的绝对值），最多能做多少个任务”的问题。这时，dp 就派上用场了。$dp_{i,j}$ 表示，做前 $i$ 个任务，能力值为 $j$ 时，最多能做几个任务。再优化压缩一下，可成为一维数组（不过还是两重循环）。  

dp 前要先对任务进行排序，对于以上两种的 $b_i$ 要分别用两个数组来装，对于装第一种的数组，以 $a_i$ 从小到大排序，若相等则 $b_i$ 更大者优先；对于第二种，则是以 $a_i+b_i$ 更大者优先。  
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node {
	int need,val;
}yyx1[111],yyx2[111];
int l1,l2,aa,n,s,dp[66666],ans;
int main() {
	memset(dp,-0x3f,sizeof(dp));
	cin>>n>>s;
	for(int i=1;i<=n;i++) {
		int a,b;
		cin>>a>>b;
		if(b>=0) {
			yyx1[++l1]=Node{a,b};
		}
		else {
			yyx2[++l2]=Node{a,b};
		}
	}
	sort(yyx1+1,yyx1+l1+1,[](Node a,Node b) {if(a.need==b.need)return a.val>b.val; return a.need<b.need;});
	sort(yyx2+1,yyx2+l2+1,[](Node a,Node b) {return a.need+a.val>b.need+b.val;});
	for(int i=1;i<=l1;i++) {
		if(s>=yyx1[i].need) {
			aa++,s+=yyx1[i].val;
		}
	}
	for(int i=0;i<=s;i++)dp[i]=0;
	for(int i=1;i<=l2;i++) {
		for(int j=0;j<=60000;j++) {
			if(j-yyx2[i].val<=60000&&j-yyx2[i].val>=yyx2[i].need) dp[j]=max(dp[j],dp[j-yyx2[i].val]+1);
			ans=max(dp[j],ans);
		}
	} 
	cout<<ans+aa;
	return 0;
}
```


---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1203F2)

&nbsp;

### 题目大意：

给定 $n$ 项任务和初始评级 $m$，完成第 $i$ 个任务需要评级至少为 $a_i$，完成任务后评级增加 $b_i$。

你可以以任何顺序完成这些任务，但在途中评级必须始终大于 $0$，求最多能完成多少任务。

&nbsp;

### 解题思路：

和 [`P3619`](https://www.luogu.com.cn/problem/P3619) 十分相似，但本题不需要完成所有任务。于是考虑先贪心排出最优顺序，然后 `dp` 求解。

首先考虑如何排序，显然的，我们要先解决完所有 $b_i$ 为正的任务，然后再解决非正的，于是分这两部分分别排序。对于 $b_i > 0$ 的部分，显然按照 $a_i$ 升序排序最优，而对于 $b_i \leq 0$ 的部分，则按照 $a_i+b_i$ 降序排列，证明如下：

- 对于 $b_i>0$，设有 $a_1<a_2$，当前评级为 $x$，则当 $x\ge a_2$ 时，两项任务的先后顺序没有影响；当 $a_1\le x < a_2$ 时，显然先完成 $1$ 是更优的，因为 $b_1+x$ 显然大于 $x$；而当 $x<a_1$ 时，$2$ 显然也无法完成，所以先后顺序显然也没有影响。综上，按照 $a_i$ 从小往大排序显然是优的。

&nbsp;

- 对于 $b_i \leq  0$，设有 $a_1$，$b_1$，$a_2$，$b_2$，当前评级为 $x$，那么若是 $1$ 在 $2$ 前更优，则有 

$$x+b_1\ge a_2$$

$$x+b_2<a_1$$

将两式相加并化简后可得 $a_1+b_1 > a_2+b_2$，于是得出按照 $a_i+b_i$ 降序排列最优。

接着考虑 `dp` 部分，定义 $dp[i][j]$ 为前 $i$ 个任务评级为 $j$ 时最多完成了多少个任务。转移方程如下：

$$dp[i][j]= \max(dp[i-1][j],dp[i-1][j-b_i]+1)$$

发现转移只和 $i$ 与 $i-1$ 有关，于是考虑滚动数组，缩减至 $1$ 维。

代码如下：
```cpp
int main(){
	for(int i=1;i<=n;i++){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		if(y>=0){//分为两部分
			a[++cnt].x=x;
			a[cnt].y=y;
		}
		else{
			b[++cnt1].x=x;
			b[cnt1].y=y;
		}
	}
	
	sort(a+1,a+1+cnt,cmp);
	sort(b+1,b+1+cnt1,cmp1);//排序
		
	for(int i=1;i<=cnt;i++){
		if(m<a[i].x) break;//统计非负数部分
		m+=a[i].y;
		ans=i;
	}
	
	memset(dp,-0x3f,sizeof(dp));//初始化dp数组
	dp[m]=0;
	for(int i=1;i<=cnt1;i++){
		for(int j=b[i].y+b[i].x;j<=m+b[i].y;j++){
			dp[j]=max(dp[j],dp[j-b[i].y]+1);
		}
	}
	
	int ans1=0;
	for(int i=0;i<=m;i++) ans1=max(ans1,dp[i])//统计最大值;
	printf("%d",ans+ans1);//合并两部分答案
    return 0;
}
```



---

## 作者：_Spectator_ (赞：0)

[可能更好的食用体验](/blog/523641/CF1203F2) $|$ 
[题目传送门](/problem/CF1203F2) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)


参见：[CF1203F1 Complete the Projects (easy version) 题解](/blog/523641/CF1203F1)

本题与 [Easy Version](/problem/CF1203F1) 的思路大体相同，唯一不同之处在于此题需要求出具体能够完成多少个任务。建议先阅读完 Easy Version 的题解再阅读本篇。

------------

${\large\color{#00CD00}\text{思路}}$

本题同样可以将项目分成 $b_i\ge0$ 和 $b_i<0$ 两种情况分别处理。

对于 $b_i\ge0$ 的情况，将项目按照 $a_i$ 从小到大排序，然后依次做每一个项目，只要能做就做，统计能做的个数。

对于 $b_i<0$ 的情况，先将项目按照 $a_i+b_i$ 从大到小排序（证明在 Easy Version）。  
在确定了项目处理的最优顺序后，我们顺理成章地会像 $b_i\ge0$ 的情况一样，依次做每一个项目，能做就做。然而，这样做是会 [WA](/record/116246590) 的。  

为什么呢？因为在 $b_i\ge0$ 的情况中，一个项目如果原本能做，那么先做其他的项目再来做这个项目仍然能做。而在 $b_i<0$ 的情况中，一个项目如果原本能做，那么做完几个其他项目之后，由于评分减少了，再回来做这个项目就不一定还能做了。

所以，这种情况需要使用**动态规划**解决。  
定义 $f_{i,j}$ 为“当前做到第 $i$ 个项目，评分为 $j$ 时能做的最大项目数”。  
转移方程很好理解，如果 $j-b_i\ge a_i$，那么 $f_{i,j}=\max(f_{i,j},f_{i-1,j-b_i}+1)$。  
然后可以发现 $f_i$ 只与 $f_{i-1}$ 有关，于是就可以愉快地把这一层给删掉啦（当然不删也可以）。

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s,k1,k2,ans1,ans2;
struct stu{
	int x,y;
}a[105],b[105];
int f[60005];
int main()
{
	cin>>n>>s;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		if(y>=0)a[++k1]=(stu){x,y};
		else b[++k2]=(stu){x,y};
	}
	sort(a+1,a+1+k1,[](stu a,stu b){return a.x<b.x;});
	sort(b+1,b+1+k2,[](stu a,stu b){return a.x+a.y>b.x+b.y;});
	for(int i=1;i<=k1;i++)
		if(s>=a[i].x)s+=a[i].y,ans1++;
	for(int i=0;i<s;i++)f[i]=-1e9;//初始化
	for(int i=1;i<=k2;i++)
		for(int j=0;j<=60000;j++)//注意j是顺序的，不用倒序
		{
			if(j-b[i].y<=60000&&j-b[i].y>=b[i].x)//判断一下j-b[i].y<=60000，防止越界
				f[j]=max(f[j],f[j-b[i].y]+1);//转移方程
			ans2=max(ans2,f[j]+0LL);
		}
	cout<<ans1+ans2;
	return 0;
}
```

---

## 作者：MiPloRAs_3316 (赞：0)

[可能更好的食用体验](/blog/560595/solution-cf1203f2) $|$ 
[题目传送门](/problem/CF1203F2)

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Meaning 题意}}}}$

给出 $n$ 个项目，初始 rating 为 $r$。

- 完成第 $i$ 个项目需要 rating 达到 $a_i$ 分（$1\leq a_i\leq 3\times 10^4$）。
- 完成第 $i$ 个项目后，rating 会增加 $b_i$ 分（$-300\leq b_i\leq 300$）。
- 任何时候，rating 不能小于 $0$。

求**最多可以完成**多少个项目。

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Analysis 思路}}}}$

浅浅贴个 tag：**贪心**，**DP**。（可以参考[简单版本](/problem/CF1203F1)的[题解区](/problem/solution/CF1203F1)，以证明贪心的正确性。）

---
首先进行分类讨论：

1. $b_i \geqslant 0$：贪心，按 $a_i$ 从小到大排序，当前能力值 $s$ 大于等于 $a_i$ 就完成第 $i$ 个项目。
1. $b_i < 0$：按 $a_i+b_i$ 从大到小的顺序排序，然后跑一遍背包（因为背包是反着计算的，所以本来**升序要变成降序**）

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Code 代码}}}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=6e4+10;
int n,s,f[maxn],aa;
int cnt,cnt2;
struct stu{
	int a,b;
}up[maxn],dw[maxn];
bool cmp(stu x,stu y)
{return x.a<y.a;}
bool cmp2(stu x,stu y)
{return x.a+x.b<y.b+y.a;}
int main()
{
	scanf("%d%d",&n,&s);
	memset(f,0,sizeof f);
	f[0]=0;
	for(int i=1; i<=n; i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(y>=0)
			up[++cnt]=(stu){x,y};
		else dw[++cnt2]=(stu){x,y};
	}
	sort(up+1,up+1+cnt,cmp);
	sort(dw+1,dw+1+cnt2,cmp2);
	for(int i=1; i<=cnt; i++)
		if(s>=up[i].a) aa++,s+=up[i].b;
	for(int i=1; i<=cnt2; i++)
	{
		for(int j=s; j>=max(dw[i].a,-dw[i].b); j--)
			f[j]=max(f[j],f[j+dw[i].b]+1);
	}
	printf("%d\n",f[s]+aa);
	return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

有 $n$ 个项目，做第 $i$ 个项目需要能力值至少为 $a_i$，做完后能力值会增加 $b_i$（可能为负），给定初始能力值，求是否能够做完所有的项目。

**解题思路**

先将所有项目按 `a[i].x` 从小到大排序，然后将所有 `a[i].y >= 0` 的项目做完。得到新的 $r$ 值。然后将所有 `a[i].y` 为负值的项目提取出来放到一个新的数组中，专门处理，假设有 $m$ 个这样的项目用 $b_m$ 保存，我们每次检查是否有项目可以最后完成即可。如果有第i个项目可以最后完成，就相当于我们的 $r$ 值减去其它 $m-1$ 个项目的 $y$ 值后，依然有 ` r >= a[i].x && r >= abs(a[i].y)`。这样确定了最后完成的项目后，我们再找是否有项目可以倒数第 $2$ 完成即可，以此类推。最后如果完成的项目数 $sum=n$ 说明我们完成了所有项目。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m, r, sum, sub;
int vis[N];
struct node {
	int x, y;
}a[N], b[N];
bool cmp(node x, node y) {
	return x.x < y.x;
}
int main() {
	cin >> n >> r;
	for(int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i++) {
		if(a[i].x <= r && a[i].y >= 0) {
			r += a[i].y;
			sum++;
		}
		if(a[i].y < 0) {
			b[++m] = a[i];
		}
	}
	bool flag = 0;
	while(true) {
		flag = 0;
		for(int i = 1; i <= m; i++) {
			if(vis[i]) {
				continue;
			}
			sub = 0;
			for(int j = 1; j <= m; j++) {
				if(i == j) {
					continue;
				}
				if(!vis[j]) {
					sub += abs(b[j].y);
				}
			}
			if(r - sub >= b[i].x && r - sub >= abs(b[i].y)) {
				vis[i] = 1;
				sum++;
				flag = 1;
			}
		}
		if(!flag) {
			break;
		}
	}
	if(sum == n) {
		cout << "YES";
	} else {
		cout << "NO";
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2300}$
---
### 解题思路：

首先发现 $b_i\ge 0$ 优先拿走一定是优的。将所有的 $b_i>0$ 的位置按照 $a_i$ 从小到大排序，依次完成直到不能完成。此时的能力值一定是最大的。

然后考虑 $b_i<0$ 的情况，发现不能通过简单的贪心解决问题，关键问题出在顺序对于结果的干扰。每一个位置对于之后的影响只有 $b_i$ 的减，考虑两个相邻位置交换对于之后的所有位置都不会有影响。

设当前能力值为 $t$，第一个位置要求为 $a_1$ 变化了 $b_1$，第二个位置是 $a_2$ 和 $b_2$。

第一个位置可以放在第二个位置之前要求：$t+b_1\ge a_2$，反之要求 $t+b_2\ge a_1$。也就是 $t\ge a_2-b_1$ 和 $t\ge a_1-b_2$，明显要求下界尽可能低，也就是要 $a_2-b_1$ 和 $a_1-b_2$ 中选择较小的一个，即 $a_2+b_2$ 和 $a_1+b_1$ 的大小决定了哪个更优先放在前面。转化过来就是 $a+b$ 较大的优先做。

然后就直接 $f_{i,j}$ 表示考虑到第 $i$ 个位置，$\text{rating}$ 为 $j$ 时最多能取到的项目，复杂度 $O(na)$，$a$ 表示值域。

----
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct str{
	int a,b;
}p1[105],p2[105];
//-      +
int n,r,x,y,cnt1,cnt2,f[60005],maxn,cnt;
bool cmd1(str x,str y){
	return x.a+x.b>y.a+y.b;
}
bool cmd2(str x,str y){
	return x.a<y.a;
}
int main(){
	scanf("%d%d",&n,&r);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		if(y<0){
			p1[++cnt1].a=x;
			p1[cnt1].b=y;
		}
		else{
			p2[++cnt2].a=x;
			p2[cnt2].b=y;
		}
	}
	sort(p2+1,p2+cnt2+1,cmd2);
	sort(p1+1,p1+cnt1+1,cmd1);
	for(int i=1;i<=cnt2;i++)
	if(r>=p2[i].a)r+=p2[i].b,cnt++;
	f[r]=cnt;maxn=cnt;
	for(int i=1;i<=cnt1;i++){
		for(int j=max(p1[i].a,-p1[i].b);j<=r;j++){
			f[j+p1[i].b]=max(f[j+p1[i].b],f[j]+1);
			maxn=max(maxn,f[j+p1[i].b]);
		}
	}
	printf("%d\n",maxn);
	return 0;
}
```




---

