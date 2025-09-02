# Add and Divide

## 题目描述

You have two positive integers $ a $ and $ b $ .

You can perform two kinds of operations:

- $ a = \lfloor \frac{a}{b} \rfloor $ (replace $ a $ with the integer part of the division between $ a $ and $ b $ )
- $ b=b+1 $ (increase $ b $ by $ 1 $ )

Find the minimum number of operations required to make $ a=0 $ .

## 说明/提示

In the first test case, one of the optimal solutions is:

1. Divide $ a $ by $ b $ . After this operation $ a = 4 $ and $ b = 2 $ .
2. Divide $ a $ by $ b $ . After this operation $ a = 2 $ and $ b = 2 $ .
3. Increase $ b $ . After this operation $ a = 2 $ and $ b = 3 $ .
4. Divide $ a $ by $ b $ . After this operation $ a = 0 $ and $ b = 3 $ .

## 样例 #1

### 输入

```
6
9 2
1337 1
1 1
50000000 4
991026972 997
1234 5678```

### 输出

```
4
9
2
12
3
1```

# 题解

## 作者：唐一文 (赞：5)

## Description

给定 $a,b$，你有两种操作：

- $a=\left\lfloor\dfrac{a}{b}\right\rfloor$。

- $b=b+1$。

求最少的操作次数使得 $a$ 变为 $0$。

## Solution

首先，显然先用操作二，再全用操作一最优。

假设操作二用了 $x$ 次，那么总操作数为 $x+\left\lceil\log_{b+x}^a\right\rceil$。

最坏情况 $b=1,a=1e9$ 时，显然答案不会超过 $1+\left\lceil\log_{1+1}^{1e9}\right\rceil=32$。

直接暴力枚举操作二的次数再模拟操作一即可。

## Code
```cpp
#include<bits/stdc++.h>
#define il inline
#define iL (1<<20)
#define re register
#define TEM template<class T>il void
#define Write(x,LC) write((x)),*iter++=LC
#define flush() fwrite(Out,1,iter-Out,stdout),iter=Out
#define gc() ((iS==iT)?(iT=(iS=ibuf)+fread(ibuf,1,iL,stdin),(iS==iT)?EOF:*iS++):*iS++)
using namespace std;
namespace IO{
    char ibuf[iL],*iS=ibuf+iL,*iT=ibuf+iL,Out[iL],*iter=Out;
    TEM read(re T &x){re char c;for(c=gc();!isdigit(c);c=gc());for(x=0;isdigit(c);x=(x<<1)+(x<<3)+(c^48),c=gc());}
    TEM write(re T x){re T c[35],l;for(l=0;!l||x;c[l++]=x%10,x/=10);for(;l;*iter++=c[--l]+'0');flush();}
}
using namespace IO;
int T,a,b;
int main(){
    for(read(T);T--;){
        read(a),read(b);
        int ans=1e9;
        for(re int i=0+(b==1);i<32;++i){
            int sum=0;
            for(re int t=a,tot=b+i;t;++sum,t/=tot);
            ans=min(ans,i+sum);
        }
        Write(ans,'\n');
    }
}
```

---

## 作者：jiang_cheng (赞：4)

## 解题思路：
直接暴力枚举除数，然后计算每个除数将被除数除到0所花的代价，如果当前枚举到的除数所花的代价大于上个枚举到的除数的代价，答案就是上个除数所花代价。注意除数为1时会死循环，记得特判。（管理员大大最帅了！！！）
## 附上代码：
```cpp
#include <cstring>
#include <iostream>

using namespace std;

const int kMaxN = 1e9 + 1;

int t, a, b, ans;

void A(int x, int y) {
  for (int i = y; i <= kMaxN; i++) {  //i为枚举的除数
    int n = x;                        //n为被除数
    for (int j = 1 + i - y;; j++) {   //j为当前除数所花代价
      if (i == 1) {                   //特判除数为1的情况
        break;
      } else {
        n = n / i;  //相除
      }
      if (!n) {           //当被除数变成0时
        if (j > ans) {    //如果当前除数所花代价大于上次所花代价
          i = kMaxN + 1;  //跳出循环
        }
        ans = min(ans, j);  //否则更新答案
        break;
      }
    }
  }
  cout << ans << endl;  //输出
}

int main() {
  cin >> t;
  while (t--) {
    ans = kMaxN;
    cin >> a >> b;
    A(a, b);  //函数调用
  }
  return 0;
}
```


---

## 作者：Fa1thful (赞：1)

### 题意：
给定两个数，可以用除以 $b$ 和把 $b$ 加一两种方式把 $a$ 变成$0$，问最少的用几次。

### 思路：
首先看到这题很容易想到明显除以是最优的，但是在 $b$ 为一的时候必须要加，因为除以一相当于浪费。

所以我们的思路就是把 $b$ 加到$2$以上，再一直除，循环枚举除数从$1$到$32$的次数，把每次次数取最小值。

### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int a, b;
        cin >> a >> b;
        if (a < b)               //如果可以一次除成0 
        {
            cout << 1 << endl;
            continue;
        }
        int ans = 999999999;
        for (int i = 0; i <= 32; i++)              //枚举到三十二是因为一个int数只有三十二位 
		{
			int x = b + i, y = i, z = a; 
			if (y > ans) break;               //如果不是最优的情况 
			if (x < 2) continue;              //如果除数是1，相当于浪费 
			while (z > 0)                   //除到等于0为止 
            {
                z /= x;
                y++;
            }
			ans = min(ans, y);             //更新ans 
		}
        cout << ans << endl;
	}
}
```


---

## 作者：endless_loop (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1485A)

很有趣的思维题，我们先来考虑操作二。

我们先来看一个例子：

$a=44,b=5$ 此时，我们要除的次数显然为 $3$。

显然得出要除的次数就是 $\left\lceil\log_ba\right\rceil$。

接着，我们再考虑操作一。

显然进行一次操作一后结果是这个： $\left\lceil\log_{b+1}a+1\right\rceil$。

我们可以看出先加后除要比先除后加好，给出一个简单的证明：
假设先进行操作二再进行操作一，则为

$$\left\lceil\log_{b+1} \left\lfloor\dfrac{a}{b}\right\rfloor+2\right\rceil$$

但如果先进行操作一再进行操作二，则为
$$\left\lceil\log_{b+1} \left\lfloor\dfrac{a}{b+1}\right\rfloor+2\right\rceil$$

显然，我们有

$$\left\lceil\log_{b+1} \left\lfloor\dfrac{a}{b}\right\rfloor+2\right\rceil\le\left\lceil\log_{b+1} \left\lfloor\dfrac{a}{b+1}\right\rfloor+2\right\rceil$$

于是我们一定有先加后乘比先乘后加划算。

我们又知道，$b$ 最坏为 $1$，$a$ 最坏为 $10^9$，易得最坏情况下不会超过 $40$ 次，那么我们就可以枚举进行几次操作二，然后求出在此时要多少次操作一。

**注意：不能用log来求！精度有误差，会错的**

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int divide(int a,int b){//求出操作一次数
	int cnt=0;
	while(a){
		a/=b;
		cnt++;
		if(cnt>100)break;
	}
	return cnt;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int a,b;
		cin>>a>>b;
		int minx=100000;
		for(int i=0;i<=40;++i){//枚举操作二次数
			minx=min(divide(a,b+i)+i,minx);
		}
		cout<<minx<<endl;
	}
	return 0;
}
```

---

## 作者：Link_Space (赞：0)

由于是Div2的A题，不会有什么思维难度，所以直接想最暴力的做法即可。由于只有两种操作，所以直接考虑暴搜枚举所有情况，但是注意暴搜的时候需要特判b等于1的情况，否则会死循环，如果害怕暴搜不稳的话可以加一个小剪枝。

以下是代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
int ans=0x7fffffff;
void dfs(ll a,ll b,int cnt)
{
    if(cnt>ans)
        return;
    if(a==0)
    {
        ans = min(cnt, ans);
        return;
    }
    if(b!=1)
        dfs(a / b, b, cnt + 1);
    dfs(a, b + 1, cnt + 1);
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        ans = 0x7fffffff;
        ll a, b;
        scanf("%lld%lld", &a, &b);
        dfs(a, b, 0);
        printf("%d\n", ans);
    }
}
```


---

## 作者：lxgw (赞：0)

#### [传送门](https://www.luogu.com.cn/problem/CF1485A)

### 题意
有两个整数 $a$ , $b$ ，支持以下两种操作：

- ```a/=b```
- ```b++```

问至少要多少次操作能使 $a = 0$ 。

### 思路
这题可以用 bfs 过，用一个结构体存数当前的 $a$ , $b$　的值和当前所用的操作次数 $ste$ ，一搜到就输出就好了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
inline int read()//快读
{
    int x=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if (ch=='-')w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*w;
}
int T=read(),n,m;
struct node{//结构体
	int n,m,ste;
}s,nw,nx,nt;
void bfs(node s);
int main()
{
	while(T--)//多组数据
	{
		s.n=read();s.m=read();
		s.ste=0;
		bfs(s);
	}
    return 0;
}
void bfs(node s)
{
	queue<node> q;
	q.push(s);
	while(!q.empty())
	{
		nw=q.front();
		q.pop();
		nx=nt=nw;
		nx.n=nw.n/nw.m,nx.ste++;//a/=b的情况
		q.push(nx);
		if(!nx.n) 
		{
			cout<<nx.ste<<endl;//a=0了
			return;
		}
		nt.m++,nt.ste++;//b++的情况
		q.push(nt);
		if(!nt.n) 
		{
			cout<<nt.ste<<endl;
			return;
		} 
	}	
}
```


谢谢 qwq 。

bye.

---

## 作者：fanfansann (赞：0)

整套题目全部题解链接：[Codeforces Round #701 (Div. 2) A ~ F ，6题全，超高质量良心题解【每日亿题】2021/2/13](https://fanfansann.blog.csdn.net/article/details/113799739) 

## A - Add and Divide
**Problem A Add and Divide**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210213111821279.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_16,color_FFFFFF,t_70)
**Translation**
给定两个正整数 $a$, $b$ ，你可以进行两种操作：

- 使得 $a=\lfloor\frac{a}{b}\rfloor$
- 使得 $b = b + 1$

请问最少多少次操作，使得 $a=0$。

**Word**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210213112029516.png)


**Solution**


 签到题 ~ 

之前做过这种题目，链接：[2021年洛谷一月月赛（Div1、Div2，6题）全部题解](https://fanfansann.blog.csdn.net/article/details/113060963#CP7287_EZEC5_166) C题，比这个难多了 ~ 

但是万变不离其宗，那道题同样有两个操作，加一或者 $\times 2$ ，最小费用修改，使得整个序列满足一个条件，需要套一个二分加DP。

中心思想还是分析性质。我们发现 $+$ 操作前期比 $\times$ 收益更大，后期 $\times$ 操作比  $+$ 操作收益更大，由于乘的话是指数级增长，所以那么数据是 $10^9$ ，实际的操作次数也是常数级别的，所以我们可以暴力。这道题仅要求将 $a$ 除到 $0$，我们仅需将 $b$ 加到 $10$ 即可，然后暴力计算。

其实可以简单地证明一下，为什么到 $10$ 一定ok，实际上一次加操作，最后的总贡献是你乘的次数，如果当你乘一次的贡献就已经超过了乘的次数，也就是说乘的贡献此时一定超过了加的贡献，所以简单算一下，我们发现 $\log_{10}10^9=9$， 所以只需要加到10即可 ~


**Code**

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;
typedef int itn;
const int N = 5007;
const ll INF = 4e18;

int n, m, t;
ll a, b;

void solve()
{
    scanf("%lld%lld", &a, &b);
    if(a == 0) {
        puts("0");
        return ;
    }
    ll res = INF, ans;
    ll cnt = 0;
    ll B = b;
    if(b == 1) b ++ , cnt ++ ;
    for(; b <= 10; ++ b) {

        ans = 0;
        cnt ++ ;
        ll tmp_a = a;
        while(tmp_a) {
            tmp_a /= b;
            ans ++ ;
        }
        ans += cnt;
        ans -- ;
        if(ans < res) res = ans;
    }
    if(B > 10) {
        ans = 0;
        while(a) {
            a /= B;
            ans ++ ;
        }
    }
    res = min(res, ans);
    printf("%lld\n", res);
    return ;
}

int main()
{
    scanf("%d", &t);
    while(t -- ) {
        solve();
    }
}
```

---

## 作者：wgyhm (赞：0)

## A. Add and Divide

### 题意

* 有两个正整数 $a,b,1\le a,b\le 10^9$。
* 你可以进行以下两个操作：$a=\left\lfloor\dfrac{a}{b}\right\rfloor$ 或者 $b=b+1$。
* 问最少多少次操作可以使 $a=0$。
* **多组数据。**

### 题解

显然，如果要进行第二个操作，把第二步操作在第一个前最优。

枚举进行多少步第二个操作，最后取最小值。大概枚举 $100$ 就肯定够了。

```cpp
inline int work(int x,int y){
    int cnt=0;
    if (y==1) return 1e9;//记得特判，不然会死循环 
	while (x) x/=y,cnt++;
	return cnt;
}
signed main(){
    rg int i,T,n,m,Max;
    read(T);
    while (T--){
    	read(n);read(m);Max=1e9;
		for (i=m;i<=m+100;i++) Max=min(Max,i-m+work(n,i));
		printf("%d\n",Max);
	}
	return 0;
}
```

完整题解 [Codeforces Round #701](https://www.luogu.com.cn/blog/51569/codeforces-round-701-post)。

---

## 作者：_caiji_ (赞：0)

这道题 dfs 剪枝能过，那我来写一篇 dfs 的题解吧。

### dfs 的思路：

0. 定义函数 $\operatorname{dfs}(a,b,stp)$，分别表示 $a$、$b$ 和当前的操作次数。
1. 如果 $a=0$，那就更新答案，否则调用 $\operatorname{dfs}(a\div b,b,stp+1)$ 和 $\operatorname{dfs}(a,b+1,stp+1)$.
2. 注意到 $a=b$ 时可以用两步把 $a$ 变为 $0$，即 $b\gets b+1,a\gets a\div b$，那我们对这部分剪枝，直接更新答案。
3. 如果现在的 $stp\geq ans$，那继续搜下去没意义，直接剪枝。
4. 当 $b=1$ 时，调用 $\operatorname{dfs}(a\div b,b,stp)$ 没用，会无限递归，那我们特判一下。

有这几个剪枝就够了，下面给出代码：

### 代码

```cpp
#include <cstdio>
using namespace std;
#define min uehfyue//为了不与std重名
int T,a,b,ans=0x3f3f3f3f;//ans要初始化为极大值
int min(int a,int b){return a<b?a:b;}//手写比std快
void dfs(int a,int b,int stp){
    if(a==0){//1
        ans=min(ans,stp);
        return ;
    }
    if(a==b){//2
        ans=min(ans,stp+2);
        return ;
    }
    if(stp>=ans) return ;//3
    if(b!=1)/*4*/ dfs(a/b,b,stp+1);
    dfs(a,b+1,stp+1);
}
int main(){
    for(scanf("%d",&T);T--;ans=0x3f3f3f3f){
        scanf("%d%d",&a,&b);
        dfs(a,b,0);
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Doubeecat (赞：0)

> [A. Add and Divide](https://codeforces.ml/contest/1485/problem/A)
> 
> 有两个数 $a$ 和 $b$，每次可以选择把 $a$ 除去 $b$ （下取整）或者把 $b$ 加 $1$ ，问最少操作几次使 $a$ 等于 $0$。
> 
> $a,b \leq 10^9$

## Solution：

首先可以发现，这个次数不会很大，最多不超过 $32$ 次。因为 $2^{31} = 2147483648 > 10^9$。

其次我们发现，第二个操作肯定先放在前面，所以我们可以暴搜（雾）

## Code：

```cpp
int judge(int p,int q) {
    int ans = 0;
    while (p) {
        p /= q;
        ans++;
    }
    return ans;
}

void solve() {
    ll a,b;cin >> a >> b;
    int ans = 0;
    while (1) {
        //printf("%d %d\n",a,b);
        if (b <= 1) {
            ++b;
            ++ans;
            continue; 
        } else if (judge(a,b) >= judge(a,b+1) + 1) {
            ++b;
            ++ans;
            continue;
        }
        ans += judge(a,b);
        break;
    }
    printf("%d\n",ans);
}
```

---

