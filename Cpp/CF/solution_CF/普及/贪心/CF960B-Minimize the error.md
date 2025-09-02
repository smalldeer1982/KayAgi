# Minimize the error

## 题目描述

You are given two arrays $ A $ and $ B $ , each of size $ n $ . The error, $ E $ , between these two arrays is defined ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960B/e950d33ee993b9f2e2ad61182c68b371192cc68e.png). You have to perform exactly $ k_{1} $ operations on array $ A $ and exactly $ k_{2} $ operations on array $ B $ . In one operation, you have to choose one element of the array and increase or decrease it by $ 1 $ .

Output the minimum possible value of error after $ k_{1} $ operations on array $ A $ and $ k_{2} $ operations on array $ B $ have been performed.

## 说明/提示

In the first sample case, we cannot perform any operations on $ A $ or $ B $ . Therefore the minimum possible error $ E=(1-2)^{2}+(2-3)^{2}=2 $ .

In the second sample case, we are required to perform exactly one operation on $ A $ . In order to minimize error, we increment the first element of $ A $ by $ 1 $ . Now, $ A=[2,2] $ . The error is now $ E=(2-2)^{2}+(2-2)^{2}=0 $ . This is the minimum possible error obtainable.

In the third sample case, we can increase the first element of $ A $ to $ 8 $ , using the all of the $ 5 $ moves available to us. Also, the first element of $ B $ can be reduced to $ 8 $ using the $ 6 $ of the $ 7 $ available moves. Now $ A=[8,4] $ and $ B=[8,4] $ . The error is now $ E=(8-8)^{2}+(4-4)^{2}=0 $ , but we are still left with $ 1 $ move for array $ B $ . Increasing the second element of $ B $ to $ 5 $ using the left move, we get $ B=[8,5] $ and $ E=(8-8)^{2}+(4-5)^{2}=1 $ .

## 样例 #1

### 输入

```
2 0 0
1 2
2 3
```

### 输出

```
2```

## 样例 #2

### 输入

```
2 1 0
1 2
2 2
```

### 输出

```
0```

## 样例 #3

### 输入

```
2 5 7
3 4
14 4
```

### 输出

```
1```

# 题解

## 作者：DarkShadow (赞：5)

# CF960B（模拟）

## 题目大意：

给出 $A$、$B$ 两个数组，分别对其**恰好**进行 $k_1$、$k_2$ 次操作，每次操作可以将一个元素加一或减一，求 $\sum_{i=1}^{n} (a_i-b_i)^2$ 的最小值。

## 思路分析：

首先因为 $A$ 数组减一和 $B$ 数组加一对答案来说是等价的，所以可以直接算 $k_1+k_2$ 次操作。

因为我们要算 $A$、$B$ 数组对应元素差的平方和最小值，所以我们可以贪心来做，每次选取差最大的两个对应元素减一，最后再算答案。这一步可以用 priority_queue 实现。

### 注意事项：

1. 由于需要进行**恰好** $k_1+k_2$ 次操作，所以如果当前所有元素差都为 $0$，也只能加一。

2. 十年 OI 一场空，不开 long long 见祖宗。

## 完整代码：

```cpp
#include <bits/stdc++.h>
#define ll long long//记得开long long
using namespace std;
int n,A[1005],B[1005],k1,k2;
priority_queue<int> q;
int main(){
	int t;
	ll ans=0ll;
	scanf("%d%d%d",&n,&k1,&k2);
	k1+=k2;
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&B[i]);
	for(int i=1;i<=n;i++)//将每组元素的差放进优先队列里
		q.push(abs(A[i]-B[i]));
	for(int i=1;i<=k1;i++){
		t=q.top();//贪心选取差最大的一组元素
		q.pop();
		if(t>0)  t--;
		else  t++;//如果所有元素差都为0也只能加一
		q.push(t);
	}
	for(int i=1;i<=n;i++){
		t=q.top();//计算答案
		q.pop();
		ans+=(ll)(t)*(ll)(t);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

首先发现对 $A$ 数组某个位置加或者减 1 等价于对 $B$ 数组一样位置做相反操作，于是这两个数组不用分别。可以看做为做对 $A-B$ 数组做 $k_1+k_2$ 个操作。

于是先对 $A-B$ 所有元素取绝对值，然后用 priority queue 模拟即可。注意当 pq 里最大元素是 0 然后还有操作没用完，必须替代为 1，否则最优来替代为（当前最大减 1）。

赛时代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define fi first
#define se second
#define pb push_back
 
#define ll long long
#define pii pair<int, int>
//#define int ll
const int MOD = 1000000007;

int a[1003], b[1003];

priority_queue<int, vector<int>> pq;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, k1, k2; cin >> n >> k1 >> k2;
    k1 += k2;
    rep(i, n) cin >> a[i];
    rep(i, n) {
        cin >> b[i];
        pq.push(abs(a[i]-b[i]));
    }
    while(k1--) {
        int t = pq.top(); pq.pop();
        if(t == 0) pq.push(1);
        else pq.push(t-1);
    }
    ll ans = 0;
    while(pq.size()) {
        ans = ans + 1ll * pq.top() * pq.top();
        pq.pop();
    }
    cout << ans << endl;
}


```

---

## 作者：Mzh2012 (赞：1)

若对 $a$ 加一相当于与对 $b$ 减一，对 $a$ 减一相当于与对 $b$ 加一。

由于最后要把 $a$ 数组中的元素跟 $b$ 数组中的元素相加，所以我们可以把问题简化成对 $a-b$ 数组做 $k_1+k_2$ 个加减操作。

先计算出 $a_i-b_i$ 的绝对值，用一个 ```priority_queue``` 模拟，最后再计算结果即可。


```cpp
#include<bits/stdc++.h>

using namespace std;

long long a[10005],b[10005];
priority_queue<long long> q;

int main(){
	long long n,k1,k2;
	cin>>n>>k1>>k2;
	for(long long i = 1;i<=n;i++) cin>>a[i];
	for(long long i = 1;i<=n;i++) cin>>b[i];
	for(int i = 1;i<=n;i++) q.push(abs(a[i]-b[i]));//计算绝对值并存入优先队列
	for(long long i = 1;i<=k1+k2;i++){
		long long tmp = q.top();
		q.pop();
		if(tmp>0) tmp--;
		else tmp++;
		q.push(tmp);
	}
	long long cnt = 0;
	while(!q.empty()){
		long long tmp = q.top();
		q.pop();
		cnt+=tmp*tmp;//可以最后再算平方
	}
	cout<<cnt;
	return 0;
}

```

---

## 作者：codeLJH114514 (赞：1)

[$\colorbox{#5898db}{\color{#fff}返回题目}$](https://www.luogu.com.cn/problem/CF960B)

## 题目描述

定义两个数组之间的距离为 ：

$\operatorname{dis}(a, b) = \sum^{n}_{i =1}(a_i - b_i) ^ 2$

对 $a$ 数组**恰好**进行 $k_1$ 次操作。对 $b$ 数组**恰好**进行 $k_2$ 次操作。

每次操作可以将一个数加一或减一。求最小 $\operatorname{dis}$。

## 解题思路

算法：贪心。

首先，我们可以把 $k_1$ 和 $k_2$ 加在一起（以下简称 $k$。），这样并不影响答案，因为无论是大的减一还是小的加一都是一样的（假设 $a$ 小 $b$ 大，$((a + 1) - b) ^ 2 = (a - (b - 1)) ^ 2$）。其次，由于需要的是最小的 $\operatorname{dis}$，且 $b - a$ 越大 $(b - a) ^ 2$ 越大，所以 $k$ 次操作只需要在 $b - a$ 最大的一组的小的加一（也可以是大的减一。）即可。

这样，我们不难写出代码：

```cpp
#include <iostream>
#include <queue>
#define maxn 1024
using namespace std;
int n, a, b;
int x[maxn], y[maxn];
class Node{
    public:
        int ix, iy, err; // ix = a, iy = b, err = (a - b) ^ 2（平方）
        Node(): ix(0), iy(0), err(0) {}
        Node(int _x, int _y): ix(_x), iy(_y), err((_x - _y) * (_x - _y)) {}
        // 直接在类的构造函数中计算 (a - b)^2
        bool operator<(const Node& o) const& {
            return err < o.err;
        } // 运算符重载，这样不用在声明 priority_queue 时加上比较参数。
};
priority_queue<Node> q;
template <class item> item& Min(item& a, item& b) {return (a < b ? a : b); } // 自定义Min函数，因为min函数返回的是常量，无法直接修改，所以自己写一个不带const的Min函数。
int main() {
    cin >> n >> a >> b;
    a = a + b;
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int j = 1; j <= n; j++) cin >> y[j];
    for (int i = 1; i <= n; i++) q.emplace(x[i], y[i]);
    for (int i = 1; i <= a; i++) {
        Node top = q.top();
        q.pop();
        Min(top.ix, top.iy) += 1; // 利用引用直接修改较小数，让其加一。
        q.emplace(top.ix, top.iy); // 入队，使用Node类的构造函数，所以不用再写一遍 "(top.ix - top.iy) * (top.ix - top.iy)"。
    }
    int ans = 0;
    while (q.size()) {
        ans += q.top().err;
        q.pop();
    } // 累加 ans。
    cout << ans; // 直接输出。
    return 0;
}
```

提交！

$\colorbox{#E74C3C}{\color{#fff}\texttt{WA}}$！

错误信息

```
Wrong Answer.wrong answer 1st numbers differ - expected: '178551232177681', found: '-2087312217'
```

一看到负数赶紧开 long long。

## 完整代码

跟前一个代码完全一样，这里不再赘述。

## STL priority_queue 用法详解。

### 声明方法、模板参数

```cpp
template<class _Tp, class _Sequence = std::vector<_Tp>, class _Compare = std::less<std::priority_queue<_Tp, _Sequence, _Compare>::value_type>> class std::priority_queue
```

其中第一个参数即为存放元素的类型。

第二个参数为基础容器，填 `vector<element_type>` 即可（或者可以填 `deque<element_type>`）。

第三个参数即为比较函数，注意，它不像 `sort` 一样是个函数，而是一个类（仿函数），声明方法如：

```cpp
class compare{
    public:
        bool operator()(int x, int y) {
            return x < y; // 比较，以整数为例，可以将int换成任意类型。
        }
};
// ...
priority_queue<int, vector<int>, compare> q;
```

### 成员函数、使用方法

|函数名|使用方法|返回值类型|备注|
|:-:|:-:|:-:|:-:
|$\text{emplace}$|`q.emplace(args, ...)`|$\text{void}$|加入一个元素。
|$\text{empty}$|`q.empty()`|$\text{bool}$|返回队列是否为空。
|$\text{pop}$|`q.pop()`|$\text{void}$|弹出队头元素。
|$\text{push}$|`q.push(element)`|$\text{void}$|加入一个元素。
|$\text{size}$|`q.size()`|$\text{size\_t}$|返回队列的大小。
|$\text{swap}$|`q.swap(other_queue)`|$\text{void}$|交换两个队列，前提是有相等的类型。
|$\text{top}$|`q.top()`|$\text{value\_type}$|返回队头元素。

注：$\text{size\_t}$ 一般情况下为 $\text{unsigned long long}$，$\text{value\_t}$ 即为元素的类型，$\text{emplace}$ 使用元素的构造函数来插入（例如 `q.emplace("Hello World", "C++", 12)` 即为 `q.push(value_type("Hello World", "C++", 12))`。）。

---

## 作者：fzj2007 (赞：1)

废话不多说，开始这篇题解！

# 第一步 读题

我们发现是要求所有的 $(a_i - b_i)^ 2$，又因为一次只能加1或减1，我们就可以把所有的次数（A与B）加在一起。因为 $((a_i+1)-b_i)^2 = (a_i-(b_i-1))^2$。因为我们要让和最小，**且 $a_i-b_i$ 越大平方也越大**，所以我们应该先处理 $a_i-b_i$最大的。我们可以用优先队列来进行处理。

# 第二步 知识点讲解

众所周知，队列是一种先进先出的数据结构，而优先队列是**拥有最高优先级的元素先出队列**。它可以按照给定的优先级**实时排序**。声明方式：
```
priority_queue<Type, Container, Functional>
```
使用时可以如下声明：

```
#include<queue>//头文件别忘了！
priority_queue<int> q;//默认优先级，是从大到小
priority_queue<int,vector<int>,less<int> > p;//两个尖括号不能放在一起，计算机会默认为右移运算符。这个也是从大到小。
priority_queue<int,vector<int>,greater<int> > a;//这个是从小到大
priority_queue<pair<int,int> > b;//用pair类型来声明优先队列
```

以上是基础声明方法。下面我们来看一看如何声明结构体类型的优先队列。例如：
```
#include<queue>
struct node{
	int x,y,val;//声明不解释
   bool operator<(const node b)const{//重载运算符，这里不赘述了（不然太多了......）
   	  return val<b.val;//按照val的值降序排序
   }
}
priority_queue<node> q;//这个是node类型的。
```
关于[重载运算符](https://www.luogu.com.cn/blog/Jydon/wzx-AK-IOI)。

# 第三步 快读

大家会快读吗？

[快读快写](https://www.luogu.com.cn/blog/encore/io-you-hua-nei-suo-shi)，这里不赘述

# 第四步 代码

温馨提示：请勿抄袭！

```
#include<bits/stdc++.h>
using namespace std; 
using std::cin;
using std::cout;
using std::endl;
namespace IN{
    const int MAX_INPUT = 1000000;
    #define getc() (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,MAX_INPUT),p1==p2)?EOF:*p1++)
    char buf[MAX_INPUT],*p1,*p2;
    template<typename T>inline bool read(T &x) {
        static std::streambuf *inbuf=cin.rdbuf();
        x=0;
        register int f=0,flag=false;
        register char ch=getc();
        while(!isdigit(ch)){
            if (ch=='-') f=1;
        	ch=getc();
        }
        if(isdigit(ch)) x=x*10+ch-'0',ch=getc(),flag=true;
        while(isdigit(ch)) {
            x=x*10+ch-48;
            ch=getc();
        }
        x=f?-x:x;
        return flag;
    }
    template<typename T,typename ...Args>inline bool read(T& a,Args& ...args) {
       return read(a)&&read(args...);
    }
    #undef getc
}

namespace OUT{
    template<typename T>inline void put(T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top=0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc('\n');
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc('\n');
    }
    inline void putc(const char ch){
        static std::streambuf *outbuf=cout.rdbuf();
        outbuf->sputc(ch);
    }
    inline void putstr(string s){
    	for(register int i=0;i<s.length();i++) putc(s[i]);
	}
    template<typename T>inline void put(const char ch,T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top = 0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc(ch);
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc(ch);
    }
    template<typename T,typename ...Args> inline void put(T a,Args ...args){
        put(a);put(args...);
    }
    template<typename T,typename ...Args> inline void put(const char ch,T a,Args ...args){
        put(ch,a);put(ch,args...);
    }
}
using IN::read;
using OUT::put;
using OUT::putc;
using OUT::putstr;
long long n,A,B,x[1005],y[1005],ans;//开long long。。。。
struct node{
	long long a,b,val;//还是开long long吧......
	bool operator<(const node h)const{//重载，按照val排序
		return val<h.val;
	}
};
priority_queue<node> q;//node类型的
//priority_queue<node> p;
int main(){
	read(n,A,B);
	A+=B;//直接结合就可以了
	for(int i=1;i<=n;i++) read(x[i]);//读入
	for(int i=1;i<=n;i++) read(y[i]);
	for(int i=1;i<=n;i++) q.push((node){x[i],y[i],(x[i]-y[i])*(x[i]-y[i])});//这里直接把val值算出来了，写一堆成员函数结果不对......
	while(A--){//只需要运行 A次
		node tmp=q.top();//获取第一个元素，我们这里优先队列自动排序，所以第一个元素就是a与b差距最大的
		q.pop();//扔了第一个
		if(tmp.a>=tmp.b) tmp.a=tmp.a-1;//如果a大，那就a减
		else tmp.b=tmp.b-1;//否则b减
		tmp.val=(tmp.a-tmp.b)*(tmp.a-tmp.b);//算出val（每一次都要更新）
		q.push(tmp);//最后再扔进去
	}
	while(!q.empty()){//一次一次地累加
		node tmp=q.top();//拿出来
		ans+=tmp.val;//加上
		q.pop();//扔了
	}
	put(ans);//最后输出即可
    return 0;
}
```
# 第五步 宣传

如果有帮助，请点个赞，谢谢！（撰文不易，dalao勿喷！）如果发现我的讲解有bug，请及时指出！

[我的主页](https://www.luogu.com.cn/user/172370)和[博客](https://www.luogu.com.cn/blog/fzj2007/)，欢迎关注！

---

## 作者：ChenJr (赞：1)

	题意：假如有两个大小为n的数组，假设能对A数组进行K1次操作，每次操作可以将A数组中的某个元素+1或-1；对B数组进行K2次操作，同样每次操作需要将数组B中的某个元素+1或-1。问进行完K1和K2个操作之后，∑(i=1->n)(Ai-Bi)^2的最小值为多少。
    分析题目，不难发现，每一次对Ai进行操作，等价于对Bi进行一次相反的操作。因此我们可以认为操作数K1与K2是等价的，我们大可合并成一个总的操作数Sum=K1+K2看代。
    同时因为Ai与Bi存在着一一对应的关系，再加上最终所求也只与Ai，Bi的差值有关，故可以从最开始将Ai、Bi看成一个整体，直接存储Ai与Bi的差的绝对值Ci，这样就相对简化了讨论。
    于是，题目就转化成：在进行Sum次+1或-1的操作下，要使得∑(i=1->n)Ci^2最小即可
    因为我们要Ci^2最小，因此每次操作数都必须要取Ci中的最大值进行操作。而维护一堆数中的最大值，最方便的操作就是用STL中的优先队列（当然每次都进行一次sort也可以）
    操作完之后只需要简单的统计答案即可。
 ```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 1000005
int a[maxn];
int b[maxn];
int num[maxn];
priority_queue<ll>que;
int main(){
    int n,k1,k2;
    cin>>n>>k1>>k2;//读入n和k1,k2
    for(int i=1;i<=n;i++){
        cin>>a[i];//读入数组a的大小
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];//读入数组b的大小
        que.push(abs(a[i]-b[i]));//将a[i]与b[i]的差的绝对值进入优先队列
    }
    int sum=k1+k2;//统计总共的操作数
    while(sum>0){//如果操作数大于0
        ll tmp=que.top();//取队顶元素
        que.pop();//剔除队顶元素
        que.push(abs(tmp-1));//将所取的队顶元素-1同时将所求结果的绝对值压入优先队列中
        sum--;//操作数-1
    }
    ll res=0;
    while(!que.empty()){//考虑进行完操作后的情况
        ll tmp=que.top();//取队顶元素
        que.pop();
        res+=1ll*tmp*tmp;//统计答案
    }
    cout<<res<<endl;
    return 0;
}

```

---

## 作者：OJ_killer (赞：0)

~~STL大法好~~

据题意我们可知~~这是一道贪心题~~这道题主要是看他们之间的差。

解法：

我们把 $a_i$ 和 $b_i$ 差的绝对值丢进一个容器里里，然后就进行操作：

每次弹出容器最顶端的值，且这个值我们要让它为最大。

如果是正数就就 $-1$，是 $0$ 的话就 $+1$，让后再丢进容器中。

那么用什么来做这个容器且满足要求呢？

就用优先队列来做。

有一些细节要注意：

操作时要用绝对值函数。

防止爆炸就让答案乘个 1LL 吧。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, k, k2, a[1003], b[1003];
long long ans, t;
priority_queue<int, vector<int>> q;

int main() {
	cin >> n >> k >> k2;
	k += k2;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		q.push(abs(a[i] - b[i]));
	}
	while (k--) {
		t = q.top();
		q.pop();
		if (t == 0)
			q.push(1);
		else
			q.push(t - 1);
	}
	while (!q.empty()) {
		ans = ans + 1ll * q.top() * q.top();
		q.pop();
	}
	cout << ans;
	return 0;
}

---

## 作者：L_shadow (赞：0)

## 思路：
令 $a1>a2$。

很显然，有 $a1^2-(a1-1)^2>a2^2-(a2-1)^2$。

即 $2\times a1-1>2\times a2-1$。

因此，这题变成了贪心，只要把差值最大的数减一。

当然，这需要一个优先队列来维护，因为需要重复处理而且要取最大值。

有个小细节：一定要把 $a$ 和 $b$ 用完，如果所有的差值都是零，那么选一个，将其变成一，一直操作，直到 $a$ 和 $b$ 变成零。
## code：
```
#include<bits/stdc++.h>
using namespace std;
priority_queue <int> q;
int n,k1,k2,a[1005],b[1005];
long long ans;//不开 long long 见祖宗
int main() {
	cin>>n>>k1>>k2;
	k1+=k2;
	for(int i=1; i<=n; i++) cin>>a[i];
	for(int i=1; i<=n; i++) {
		cin>>b[i];
		q.push(abs(a[i]-b[i]));
	}
	while(k1!=0) {
		int s=q.top();
		q.pop();
		if(s==0) s++;//重复处理
		else s--;
		k1--;
		q.push(s);
	}
	while(!q.empty()) {
		int s=q.top();
		q.pop();
		ans+=(long long)s*s;
	}
	cout<<ans;
}
```


---

## 作者：xuhanxi_dada117 (赞：0)

[题目传送门&题目大意](https://www.luogu.com.cn/problem/CF960B)

# 解法

考虑把 $a_{i}+1$ 对答案的结果影响等价于把 $b_{i}-1$：

所以，我们干脆令 $t_{i}+1=|a_{i}-b_{i}|$，只要对 $t_{i}+1$ 操作即可。

由于 $t_{i}$ 越大，$t_{i}^2$ 与 $(t_{i}-1)^2$ 的差更大，所以我们优先对较大的操作，采用**优先队列**解决。

**注意：如果全是零的话，记得特判！**

最后扫一遍优先队列即可，时间复杂度 $\Theta(n\times \log n)$。

# 代码
```cpp
#include<bits/stdc++.h>
#define N 1010
using namespace std;
int n,k1,k2,a[N],b[N];
priority_queue<int> pq;
int main(){
	cin>>n>>k1>>k2;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) cin>>b[i],a[i]-=b[i];
	for(int i=1;i<=n;++i) pq.push(abs(a[i]));
	for(int i=1;i<=k1+k2;++i){
		int r=pq.top();pq.pop();
		--r;
		if(r==-1) pq.push(1);
		else pq.push(r);
	}long long cnt=0;//一定要开long long!
	while(!pq.empty()){
		cnt+=1ll*pq.top()*pq.top();
		pq.pop();
	}cout<<cnt;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/111562810)

---

## 作者：Uuuuuur_ (赞：0)

## 思路
研究题目可以发现，$a,b$ 具体的值与答案无关，我们可以将每一个位置对应的差记录在数组 $c$ ，而对于 $k=k_1+k_2$ 次操作，都可以视作将 $c$ 中的一个元素减去或加上 $1$。

我们的目标是让 $c_i$ 的平方尽可能小，所以可以利用绝对值，每次操作都是对 $c_i - 1$ 然后取绝对值（如果是加的话答案就变大了）。

简单举几个例子就可以发现，如果值越大，我们对它操作所获的收益就越大，如 $4^2$ 到 $3^2$ 是比 $3^2$ 到 $2^2$ 优的。

所以，我们就可以用**优先队列**来进行维护，首先将所有差的绝对值加入队列，每次对值最大的进行操作，然后取绝对值。

时间复杂度 $O(k \log n)$。
## 代码

```cpp
#include <iostream>
#include <string>
#include <queue>
#include <cmath>
using namespace std;
priority_queue<long long> q;
int n, k1, k2;
int k;
long long a[100005], b[100005];
long long cost;
int main() {
    cin >> n >> k1 >> k2;
    k = k1 + k2;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) q.push(abs(a[i] - b[i]));
    for (int i = 1; i <= k; i++) {
        int now = q.top();
        q.pop();
        q.push(abs(now - 1));
    }
    while (!q.empty()) {
        cost += q.top() * q.top();
        q.pop();
    }
    cout << cost;
    return 0;
}
```


---

## 作者：傅思维666 (赞：0)

## 题解：

一道还不错的贪心。

发现首先应该考虑差最大的，然后等到把它消成第二大的之后再同时削第二大的...以此类推。

这个贪心的正确性可以证明，因为平方增长，先消差大的肯定不亏。

那么上面的消除过程就可以模拟来解决。

直接优先队列，非常方便。

需要注意的是，由于操作相同，对于两个数列的操作可以加一起。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define fi first
#define se second
#define pb push_back
#define ll long long
#define pii pair<int, int>
const int MOD = 1e9+7;
int a[1003], b[1003];
priority_queue<int, vector<int>> pq;
signed main() 
{
    int n, k1, k2; 
    scanf("%lld%lld%lld",&n,&k1,&k2);
    k1 += k2;
    rep(i, n) 
        scanf("%lld",&a[i]);
    rep(i, n) 
    {
        scanf("%lld",&b[i]);
        pq.push(abs(a[i]-b[i]));
    }
    while(k1--) 
    {
        int t = pq.top(); 
        pq.pop();
        if(t == 0) 
            pq.push(1);
        else 
            pq.push(t-1);
    }
    ll ans = 0;
    while(!pq.empty()) 
    {
        ans = ans + 1ll * pq.top() * pq.top();
        pq.pop();
    }
    cout << ans << endl;
    return 0;
}
```



---

## 作者：皮卡丘最萌 (赞：0)

这道题目由于只求每个$ai-bi$的平方和，所以可以把题目中$k1,k2$直接累加看作总改变次数。

具体来说，就是先求出每个$ai-bi$的值，然后加以维护，每次把最大的一个减一，然后用堆维护。

比如样例：

2 5 7

3 4

14 4

$k1,k2$直接累加看作总改变次数:
$12$

求出每个$ai-bi$的值:

$11$ $0$

接下来，每次对最大数$11$减一。

**问题来了，出现负数怎么办？**

因为每一次修改都必须做，所以我们可以对其绝对值。

像样例最后就变为了：

$1$ $0$

最后累计平方和：$1$

注意事项：

累加过程中可能会爆$longint/int$，所以用$int64/longlong$.

代码：
```pascal
var count,n,x,y,p,s:int64; i,ii:longint;
a,b,c:array[0..100001] of int64;
procedure up;
var fa,son,t:int64;
begin
inc(count); c[count]:=abs(a[count]-b[count]);
fa:=count>>1; son:=count;
while fa>0 do
  if c[son]>c[fa] then          //如果儿子更大就往上
    begin
    t:=c[son];c[son]:=c[fa];c[fa]:=t;
    son:=fa; fa:=fa>>1;
    end
  else break;
end;                   //建堆过程

procedure down;
var fa,son,t:int64;
begin
c[1]:=abs(c[1]-1);             //别忘了取绝对值
fa:=1;
while fa<<1<=count do
  begin
  son:=fa<<1;
  if (c[son]>c[fa])or(c[son+1]>c[fa]) then
    begin
    if (son+1<=count)and(c[son+1]>c[son]) then son:=son+1;
                                           //取最大的儿子
    t:=c[son];c[son]:=c[fa];c[fa]:=t; fa:=son;
    end
  else break;
  end;
end;                       //每次进行减1操作

begin
readln(n,x,y);
p:=x+y;                         //直接累加次数
for i:=1 to n do read(a[i]);
for i:=1 to n do read(b[i]);
for i:=1 to n do up;                      //建堆
for i:=1 to p do down;              //每次进行减1操作
for i:=1 to n do s:=s+c[i]*c[i];         //累计平方和
writeln(s);
end.
```

---

