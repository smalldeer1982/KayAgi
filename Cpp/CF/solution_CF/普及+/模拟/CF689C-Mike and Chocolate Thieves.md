# Mike and Chocolate Thieves

## 题目描述

Bad news came to Mike's village, some thieves stole a bunch of chocolates from the local factory! Horrible!

Aside from loving sweet things, thieves from this area are known to be very greedy. So after a thief takes his number of chocolates for himself, the next thief will take exactly $ k $ times more than the previous one. The value of $ k $ ( $ k&gt;1 $ ) is a secret integer known only to them. It is also known that each thief's bag can carry at most $ n $ chocolates (if they intend to take more, the deal is cancelled) and that there were exactly four thieves involved.

Sadly, only the thieves know the value of $ n $ , but rumours say that the numbers of ways they could have taken the chocolates (for a fixed $ n $ , but not fixed $ k $ ) is $ m $ . Two ways are considered different if one of the thieves (they should be numbered in the order they take chocolates) took different number of chocolates in them.

Mike want to track the thieves down, so he wants to know what their bags are and value of $ n $ will help him in that. Please find the smallest possible value of $ n $ or tell him that the rumors are false and there is no such $ n $ .

## 说明/提示

In the first sample case the smallest $ n $ that leads to exactly one way of stealing chocolates is $ n=8 $ , whereas the amounts of stealed chocolates are $ (1,2,4,8) $ (the number of chocolates stolen by each of the thieves).

In the second sample case the smallest $ n $ that leads to exactly $ 8 $ ways is $ n=54 $ with the possibilities: $ (1,2,4,8), (1,3,9,27), (2,4,8,16), (2,6,18,54), (3,6,12,24), (4,8,16,32), (5,10,20,40), (6,12,24,48) $ .

There is no $ n $ leading to exactly $ 10 $ ways of stealing chocolates in the third sample case.

## 样例 #1

### 输入

```
1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
8
```

### 输出

```
54
```

## 样例 #3

### 输入

```
10
```

### 输出

```
-1
```

# 题解

## 作者：zsyzsy_2012 (赞：3)

一道比较简单的二分练习题。

首先想到这个题拥有单调性，因为一个数（原题中指等比数列的末项，即最大值）小于等于另一个数（原题中指变量 $t$ ），把后者变大，前者仍然小于后者。但会有新的等比数列小于 $t$ ，所以很容易知道此题有单调性，想到二分。

本题中缺的变量只有 $t$ ，所以容易想到二分 $t$ 的值

接下来便是给定一个 $t$ ，求组数的问题。由于此题的数据范围只有 $10 ^ {15}$ ，在这一步只需枚举公比（设为 $i$ ) ，然后累加给定公比时数列的数量即可，可以知道每一步累加的值应为 $t$ 除以 $i ^ 3$ 下取整，即：

$
	ans = \Sigma t / i ^ 3
$

然后就是代码环节了，有了前面的推导这就很简单了，具体见注释 ：

```
#include<bits/stdc++.h>
#define int long long
//不开LL见祖宗
using namespace std ;
int T , n ;
int check(int num) {//计算给定t的答案的函数
	int ans = 0 ;
	for(int i = 2 ; i * i * i <= num ; i++) {
		ans += num / i / i / i ;//累加答案
	}
	return ans ;
}
signed main() {
	scanf("%lld" , &n) ;//读入
	int l = 1 , r = (int)1e18 + 10 ;
	int best = -1 ;
	while(l <= r) {
		int mid = (l + r) / 2 ;//二分
		if(check(mid) >= n) {
			r = mid - 1 ;//合格
			best = mid ;
		}
		else {
			l = mid + 1 ;//不合格
		}
	}//输出
	if(best == -1) printf("-1") ;
	else if(check(best) == n) printf("%lld" , best) ;
	else printf("-1") ;
	puts("") ;
	return 0 ;
}
```

---

## 作者：_hsr_ (赞：2)

对于一条欧拉回路，除起点外每个点相连的红边与蓝边数是相同的。对于起点，欧拉回路的第一条边和最后一条边的颜色可能是相同的。

若起点初始度数为奇数，由于先走了与新连出的边，所以就算第一条和最后一条边的颜色相同也没关系。(同色的话由于有影响的点在同行同列，一定连通，所以整个连通块只会额外多出一条边颜色不同)。

若起点初始度数为偶数，则连通块是一个二分图，第一条和最后一条边的颜色一定不相同。
  
## 代码：
```
#include<bits/stdc++.h>
#define fi(s) freopen(s,"r",stdin);
#define fo(s) freopen(s,"w",stdout);
using namespace std;
typedef long long LL;

inline int read() {
    int x=0,f=1;char ch=getchar();for(;!isdigit(ch);ch=getchar())if(ch==‘-‘)f=-1;
    for(;isdigit(ch);ch=getchar())x=x*10+ch-‘0‘;return x*f;
}

const int N = 400005;
const int D = 2e5;

struct Edge{
    int to, nxt, id;
}e[N << 1];
int head[N], deg[N], A[N], sk[N], En = 1, top;
bool ve[N << 1], vd[N];
char ans[N];

void add_edge(int u,int v,int id) {
    ++En; e[En].to = v, e[En].id = id, e[En].nxt = head[u]; head[u] = En;
    ++En; e[En].to = u, e[En].id = id, e[En].nxt = head[v]; head[v] = En;
    deg[u] ++, deg[v] ++;
}

37 void dfs(int u) {
    vd[u] = true;
    for (int i=head[u]; i; i=e[i].nxt) {
        if (!ve[i]) {
            ve[i] = ve[i ^ 1] = true; head[u] = i;  
dfs(e[i].to);
            sk[++top] = e[i].id; i = head[u];
        }
    }
}

int main() {
    int n = read(), cnt = 0;
    for (int i=1; i<=n; ++i) {
        int u = read(), v = read() + D;
        add_edge(u, v, i);
    }
    for (int i=1; i<=(D<<1); ++i) 
        if (deg[i] & 1) A[++cnt] = i;
    for (int i=1; i<=cnt; i+=2) 
        add_edge(A[i], A[i + 1], 0);
    
    for (int i=1; i<=cnt; ++i) {
        if (!vd[A[i]]) {
           dfs(A[i]);
           while (top) ans[sk[top]] = top & 1 ? ‘b‘ : ‘r‘, top --;
       }
   }
   for (int i=1; i<=(D<<1); ++i) {
       if (!vd[i]) {
           dfs(i);
           while (top) ans[sk[top]] = top & 1 ? ‘b‘ : ‘r‘, top --;
       }
   }
    ans[n + 1] = ‘‘;
    puts(ans + 1);
    return 0;
}
```

---

## 作者：fkcufk (赞：2)


[洛谷链接](https://www.luogu.com.cn/problem/CF689C)

[CF 链接](https://codeforces.com/problemset/problem/689/C)

[更好的体验](https://www.luogu.com.cn/blog/1234-hacker-pt/solution-cf689c)（推荐）

建议降绿。

题目大意：

给定一个 $n$，你需要求出最小的 $t$，使得在 $t$ 里有 $n$ 组四项的等比数列成立。若没有，则输出 `-1`。

解析：

本题可以使用[二分](https://blog.csdn.net/weixin_47406709/article/details/125660759?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168274941616800184165676%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=168274941616800184165676&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-125660759-null-null.142^v86^koosearch_v1,239^v2^insert_chatgpt&utm_term=%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE&spm=1018.2226.3001.4187)去做。

我们可以将 $l$ 设为 $1$，$r$ 设为 $2^{63}-1$，即 C++ 中的 `LONG_LONG_MAX`（需开 `long long`）。

我们可以定义一个 `check` 函数，采用枚举公比法用来判断有没有。

下面给出 `check` 函数：
```cpp
ll check(ll x){
    ll ret=0;
    for(ll i=2;i*i*i<=x;i++){
        ret+=x/(i*i*i);
    }
    return ret;
}
```
如果 `check` 函数中的 $ret$ 等于输入的 $n$，输出 $t$。

否则输出 `-1`。

注意点：

本题必须全程开 `long long`，否则直接炸精度。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; // 全程开 long long
ll check(ll x){
    ll ret=0;
    for(ll i=2;i*i*i<=x;i++){
        ret+=x/(i*i*i);
    }
    return ret;
}
int main(){
	ios_base::sync_with_stdio(false); // cin、scanf 断开连接
	cin.tie(NULL),cout.tie(NULL); // 可以稍微快一点
	ll n;
    cin>>n;
    ll l=1,r=LONG_LONG_MAX,mid; // r 取正无穷
	ll ans=0; // 题目中的 t
    while(l<=r){ // 二分
        mid=(l+r)/2;
        if(check(mid)>=n) ans=mid,r=mid-1;
        else l=mid+1;
    }
    if(check(ans)==n) cout<<ans;
    else cout<<-1;
    return 0;
}
```

---

## 作者：Bpds1110 (赞：1)

给出整数 $m$，求出最小的 $n$，使得正好有 $m$ 个不同的 $ak^{3} \le n$。其中 $a \ge 1$ 且 $k \ge 2$，注意并不是给出的。

发现 $n$ 越大，所满足 $ak^{3} \le n$ 的数量越多，具有单调性，所以考虑二分 $n$，满足第一个不同的 $ak^{3} \le n$ 数量**不少于** $m$。

对于每个二分的 $n$，枚举 $k$，然后统计对于每个 $k$ 有多少种不同的方式。根据数量调整二分范围即可。

设最终二分到的答案为 $ans$，考虑一种情况。当 $ak^{3} \le ans$ 的情况个数**严格大于** $m$ 时，答案不存在，输出 `-1`。

---

## 作者：xzggzh1 (赞：1)

题意：

有四个数组成一个等比数列.

给你一个 $n$ ，找一个最小数 $t$ ，使得在 $t$ 内有 $n$ 组等比数列成立。

---

假设这四个数为 $a_1,a_2,a_3,a_4$ 他们的公比为 $q$ 。

显然有 $a_1*q^3 = a_4$ ， $a_1$ 可以任意取，所以对于一个 $t$，

有 $\lfloor \frac t {d^3} \rfloor  $ 组公比为 $d$ 的组合。

若想求出所有小于 $t$ 的组合，那么只要枚举 $d$ 即可，单个时间复杂度是 $O(t^{\frac13})$ 。

现在我们已经可以容易地计算所有小于 $t$ 的组合，所以只要二分这个 $t$ 就可以解决了。

代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define mid (l+r>>1)
#define int  long long
inline int R()
{
    int res=0,sign=1;char ch;
    while((ch=getchar())>'9'||ch<'0') if(ch=='-') sign=-1;res+=ch-'0';
    while((ch=getchar())<='9'&&ch>='0') res=res*10+ch-'0'; 
    return res*sign;
}
int n;
int calc(int x){
    int res=0;
    for(int i=2;i;++i){
        int t=i*i*i;if(t>x) break;
        res+=x/t;
    }
	return res;
}
signed main(){
    n=R();
    int l=1,r=1LL<<55;
    while(l<=r){
        if(calc(mid)>=n) r=mid-1;
        else l=mid+1;
    }
	if(calc(r+1)!=n) puts("-1");
    else printf("%lld\n",r+1);
}
```

---

## 作者：GWBailang (赞：1)

#### [原题传送](https://www.luogu.com.cn/problem/CF689C)
算是比较模版的二分吧（不至于蓝题）。

在 $t$ 以内四人巧克力数量成等比数列有几种情况具有单调递增的性质，所以我们只需要二分查找 $t$ 是几，看 $t$ 以内是否能有 $n$ 组等比数列。

直接看代码里的注释。

#### 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long shu(long long x){//用来看范围是t有几种可能
	long long cnt=0;
	for(long long i=2;i*i*i<=x;i++)cnt+=x/i/i/i;
	return cnt;
}
int main(){
	long long n;
	cin>>n;
	long long l=8,r=1e18,mi,sc=-1;
	while(l<=r){//二分
		mi=(l+r)/2;//找中间的点
		if(shu(mi)<n)l=mi+1;//小了就移动左边界
		else{//大了就移动右边界
			sc=mi;//记录
			r=mi-1;
		}
	}
	if(sc==-1||shu(sc)!=n)cout<<-1<<endl;
	else cout<<sc<<endl;
	return 0;
}
```
###### 十年 OI 一场空，不开 ```long long``` 见祖宗！

---

## 作者：AKPC (赞：1)

### 思路
假设四个数为 $a_1,a_2,a_3,a_4$，因为他们是等比数列，假设 $x$ 是他们的公比，显然，$a_{i+1}=a_ix(i\in\{1,2,3\})$。显而易见地可以推出 $a_1x^3=a_4$。

那么问题就可以被转化为有多少组正整数解使得 $a_1x^3=t$。而暴力做法并不优秀，所以我们用二分答案求解 $x$ 并计算验证，结果就出来了。时间复杂度为 $O(t^{\frac{1}{3}}\log t)$
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,l=1,r=5e15+5;
int check(int mid){
	int ans=0;
	for (int i=2;i*i*i<=mid;i++) ans+=mid/i/i/i;
	return ans;
}
signed main(){
	cin>>n;
	while (l<r){
		int mid=(l+r)/2;
		if (check(mid)<n) l=mid+1;
		else r=mid;
	}
	check(r)==n?cout<<r:cout<<-1;
	return 0;
}
```


---

## 作者：yaolibo (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF689C)

## 题意解释：
给定一个数 $n$，求最小的 $t$，使得存在恰好 $n$ 个不同的等比数列 $a_1,a_2,a_3,a_4$ 满足 $1\le a_1<a_2<a_3<a_4\le t$。

## 思路：
设等比数列为 $a_1,a_2,a_3,a_4$，其公比为 $q$，

则有 $a_4=a_1\cdot q^3$。

对于每个公比 $q$，首项 $a_1$ 可以从 $1$ 开始取，其间只需满足 $a_4\le t$，即 $a_1\cdot q^3\le t$。

通过移项可以得到 $a_1\le \dfrac{t}{q^3}$，所以 $\max_{a_1}=\left \lfloor \dfrac{t}{q^3} \right \rfloor$。

故 $a_1$ 的值可以取 $\left [1,\left \lfloor \dfrac{t}{q^3} \right \rfloor \right ]$ 的所有正整数，

所以此时就有 $\left \lfloor \dfrac{t}{q^3} \right \rfloor$ 个满足条件的等比数列。

------------

容易发现，$n$ 具有单调性，即 $n$ 会随着 $t$ 的变大而变大；

又因为 $n$ 的范围为 $[1,10^{15}]$，

所以考虑二分答案 $t$，判定函数写法即为上述思路，

即对于每个 $t$，满足条件的等比数列的数量为 $\left \lfloor \dfrac{t}{q^3} \right \rfloor$。

具体见代码。

## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL Inf = 1e18;
LL n, l, r, mid, ans;
inline LL Check(LL t) {
    LL q, cnt = 0;
    for (q = 2; q * q * q <= t; q++)
        cnt += t / (q * q * q);   
    return cnt;
}
int main() {
    scanf("%lld", &n);
    l = 1; r = Inf;
    while (l <= r) {
        mid = l + r >> 1;
        if (Check(mid) >= n) {
            r = mid - 1;
            ans = mid;
        }
        else l = mid + 1;
    }
    if (Check(ans) == n) printf("%lld", ans);
    else printf("-1"); 
    return 0;
}
```

## 结束~Over~

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF689C)

## 题意
给定 $n$，找出最小数 $t$，要求 $t$ 内有 $n$ 组**等比数列**成立。

## 思路
一道二分题。

能发现 $t$ 的值有单调性，所以二分 $t$，判断是否有 $n$ 组数列即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long//记得开long long
using namespace std;
int n,l,r,mid,ans;
int check(int x){//求有几组等比数列
    int i,s=0;
    for(i=2;i*i*i<=x;i++)//枚举公比
        s+=x/i/i/i;//累加答案
    return s;
}
signed main(){
    cin>>n;
    l=1;r=1e18;
    while(l<=r){
        mid=(l+r)/2;//进行二分
        if(check(mid)>=n)
            ans=mid,r=mid-1;//调整范围
        else l=mid+1;
    }
    if(check(ans)==n) cout<<ans;
    else cout<<-1;
    return 0;
}
```

---

## 作者：wangjue233 (赞：0)

# Solution
[题目传送门](https://www.luogu.com.cn/problem/CF689C)

## 题目描述
题目要求我们找出最小的整数 $n$，使得有 $m$ 种不同的方式，使四个小偷能够以**等比数列**的方式偷取不超过 $n$ 个巧克力的数量。题目中的 $m$ 是给定的。

## 题目思路
因为小偷偷巧克力的方式形成**等比数列**，我们可以将问题转化为寻找四个数（四个小偷的巧克力数量），这四个数构成**等比数列**，并且它们的乘积不能超过 $n$。等比数列的每个首项 $a$ 和公比 $k$（其中 $a$ 为正整数，$k > 1$ 并为整数），小偷能偷取的巧克力数量可以表示为 $a$, $ak$, $ak^2$, $ak^3$。因为 $ak^3$ 是四个数中最大的数，所以它必须小于等于 $n$。

## 解题过程
为了找到有多少种偷取方式，我们需要检查每个可能的 $a$ 和 $k$，并且它们的乘积不能超过 $n$。对于每一个 $a$（从 $1$ 开始直到 $n$ 的立方根），我们可以用 $n$ 除以 $a^3$，得到的商就是可能的 $k$ 的数量。最后，我们将所有的 $k$ 数量累加起来，就得到答案啦。
***

我认为上述描述较详细，就不附代码了。如果有对于这篇题解有任何问题的，欢迎私信我。

---

## 作者：__zfy__ (赞：0)

~~一道很水的二份，建议黄或绿。~~
### 思路
二分，主函数里只需要板子即可，输出时只要判断 `judge(ans)` 是否等于 $n$，否则输出 $-1$。

函数 `judge` 里我采用的是枚举公比的方法，因为题中的四个数构成的是等比数列。

函数中返回 $t$ 即可。
### 代码
十年 OI 一场空，不开 `long long` 见祖宗！
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
//快读
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
//  变量名=read();
//  n=read();
}
ll judge(ll x)              //为什么这样写题解里已经讲述 
{
	ll t=0;
	for(ll i=2;i*i*i<=x;i++)//枚举公比 
	{
		t+=x/i/i/i;
	}
	return t;
}
int main()                  //里面均为二分模板 
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ll n,ans=0,l=1,r=1000000000000000010;
	cin>>n;
	while(l<=r)
	{
		ll mid=(l+r)/2;
		if(judge(mid)>=n)
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	if(judge(ans)==n)
	{
		cout<<ans;
	}
	else
	{
		cout<<-1;
	}
	return 0;
}
```


---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF689C)

[CodeForces 链接](https://codeforces.com/problemset/problem/689/C)

题目大意：

给你一个 $n$，让你输出最小的 $t$，使得在 $t$ 内有 $n$ 组四项的等比数列成立。如果没有符合要求的 $t$，那么输出 $\texttt{-1}$。

思路：

显然本题的 $t$ 具有[单调性](https://baike.baidu.com/item/%E5%8D%95%E8%B0%83%E6%80%A7?fromModule=lemma_search-box)。所以，我们可以考虑使用[二分答案](https://oiwiki.org/basic/binary/#%E4%BA%8C%E5%88%86%E6%B3%95)来解决此题。

可以想到二分 $t$。我们设定最小值为 $1$，最大值设为 $8\cdot 10^{15}$。

前面我们设一个 ```bool``` 类型的变量 $ok$，初始值为 ```false```，用来标记是否有符合要求的 $t$。

二分模板大家肯定都记得，我们在判断时可以把当前数值 $mid$ 对应的 $n$ 算出来。我们采用枚举公比的方法。
```cpp
long long sum = 0;
for (long long i = 2; i * i * i <= mid; i++){
    sum += mid / (i * i * i);
}
```
如果 $mid$ 对应的 $n$ 刚好等于原题中的 $n$，那么就把前面设的 $ok$ 标记为 ```true```。

坑点：

1. 全程开 ```long long```，否则炸精度！
1. 最后不要忘记特判没有符合条件的 $t$ 的情况！

上代码：
```cpp
#include <iostream>
using namespace std;

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    long long n;// 坑点 1：全程开 long long
    cin >> n;
    long long l = 1, r = 8e15;
    bool ok = false;
    // 二分大模板
    while (l < r){
        long long mid = (l + r) >> 1, sum = 0;// 坑点 1：全程开 long long
        for (long long i = 2; i * i * i <= mid; i++){
            sum += mid / (i * i * i);
        }
        if (sum < n){
            l = mid + 1;
        } else {
            r = mid;
        }
        if (sum == n){
            ok = true;
        }
    }
    if (ok){
        cout << l << "\n";
    } else {
        cout << "-1\n";// 坑点 2：特判没有符合条件的 t
    }
    return 0;
}
```

---

## 作者：koobee (赞：0)

~~这题是黄题吧~~

一道比较简单的二分题。

暴力：预处理，用 $ans_j$ 记为 $t=j$ 内有多少组等比数列成立，枚举公比即可。

代码（真的写了）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e7+5, M = 1e7;
long long n, t, f[N], ans[N], jj=1;
int main(){
	for(int i = 1; 8 * i <= M; i++)
		for(int j = 2; i * j * j * j <= M; j++) f[i * j * j * j]++; //求f
	for(int i = 1; i <= M; i++) f[i] += f[i-1]; //前缀和
	for(int i = 1; i <= f[M]; i++){
		while(f[jj] < i) jj++;
		if(f[jj] == i) ans[i] = jj;
		else ans[i] = 2e9;
	} //算答案
	cin>>n;
	if(ans[n] < 2e9) cout<<ans[n];
	else cout<<-1;
	return 0;
}
```
满分做法：

思路：不难看出，$t$ 越大，成立的等比数列越多，满足二分答案的单调性。二分 $t$，找到最小值。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, l = 1, r = 8e15;
ll cal(ll mid){
    ll ans = 0;
	for(ll i = 2; i * i * i <= mid; i++) ans += mid / (i * i * i);
	return ans;
}//计算mid内有多少组等比数列成立
int main(){
	cin>>n;
	while(l < r){
		ll mid = (l + r) / 2;
		if(cal(mid) < n) l = mid + 1;
		else r = mid;
	}//二分
	if(cal(r) == n) cout<<r;
	else cout<<-1;
	return 0;
} 
```


---

## 作者：XL4453 (赞：0)

### 解题思路：

设 $f_i$ 表示 $i$ 以内的可行等比数列个数，显然 $f_i$ 单调不减。所以考虑二分答案。

接下来的问题就是如何快速算出等比数列的个数。

发现，如果固定了等比数列的公比 $x$，那么首项和末项（因为一定只有四项）的比就是 $x^3$，如果末项在这这范围里面就一定可行，否则一定不可行，中间的项全都不要考虑。

然后问题就转化为了这个（不妨设为 $[0,n]$）范围里一共有多少组满足 $ax^3\le n$，其中 $a,x$ 都是正整数。

然后就简单了，直接枚举一下 $x$，然后除一下就出来了。每一次计算的复杂度是 $O(\sqrt[3]{n})$ 的，二分复杂度 $O(\log n)$，总复杂度 $O(\sqrt[3]{n}\log n)$，可以接受。

注意判断找出的答案是否正好为所要求的的数量。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long m,l,r,ans,mid;
long long check(long long n){
	long long i,ans=0;
	for(i=2;i*i*i<=n;i++)
	ans+=n/(i*i*i);
	if(ans>=m)return ans;
	else return 0;
}
int main(){
	scanf("%I64d",&m);
	l=0;r=9223372036854775807;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)==0)l=mid+1;
		else r=mid-1,ans=mid;
	}
	if(check(ans)==m)printf("%I64d",ans);
	else printf("-1\n");
	return 0;
}
```


---

## 作者：orz_z (赞：0)

### 题目大意

给定一个数 $n$，求最小的 $t$，使得存在恰好 $n$ 个不同的等比数列 $a_1,a_2,a_3,a_4$，满足 $1\le a_1<a_2<a_3<a_4\le t$。


### 解题思路

设等比数列为 $a_1,a_2,a_3,a_4$，其公比为 $q$，

则有 $a_4=a_1\cdot q^3$。

对于每个公比 $q$，首项 $a_1$ 可以从 $1$ 开始取，其间只需满足 $a_4\le t$，即 $a_1\cdot q^3\le t$。

通过移项可以得到 $a_1\le \dfrac{t}{q^3}$，所以 $a_1$ 的值可以取 $\left [1,\left \lfloor \dfrac{t}{q^3} \right \rfloor \right ]$ 的所有正整数，

所以此时就有 $\left \lfloor \dfrac{t}{q^3} \right \rfloor$ 个满足条件的等比数列。


容易发现，$n$ 具有单调性，即 $n$ 会随着 $t$ 的变大而变大，又因为 $n$ 的范围为 $[1,10^{15}]$，所以考虑二分答案 $t$。

具体见代码。



### CODE

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, l, r, mid, ans;

inline int check(int t)
{
    int q, cnt = 0;
    for (q = 2; q * q * q <= t; q++)
        cnt += t / (q * q * q);
    return cnt;
}

signed main()
{
    scanf("%lld", &n);
    l = 1;
    r = 1e18;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (check(mid) >= n)
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    if (check(ans) == n)
        printf("%lld", ans);
    else
        printf("-1");
    return 0;
}
```



---

