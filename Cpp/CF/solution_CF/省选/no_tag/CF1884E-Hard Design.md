# Hard Design

## 题目描述

Consider an array of integers $ b_0, b_1, \ldots, b_{n-1} $ . Your goal is to make all its elements equal. To do so, you can perform the following operation several (possibly, zero) times:

- Pick a pair of indices $ 0 \le l \le r \le n-1 $ , then for each $ l \le i \le r $ increase $ b_i $ by $ 1 $ (i. e. replace $ b_i $ with $ b_i + 1 $ ).
- After performing this operation you receive $ (r - l + 1)^2 $ coins.

The value $ f(b) $ is defined as a pair of integers $ (cnt, cost) $ , where $ cnt $ is the smallest number of operations required to make all elements of the array equal, and $ cost $ is the largest total number of coins you can receive among all possible ways to make all elements equal within $ cnt $ operations. In other words, first, you need to minimize the number of operations, second, you need to maximize the total number of coins you receive.

You are given an array of integers $ a_0, a_1, \ldots, a_{n-1} $ . Please, find the value of $ f $ for all cyclic shifts of $ a $ .

Formally, for each $ 0 \le i \le n-1 $ you need to do the following:

- Let $ c_j = a_{(j + i) \pmod{n}} $ for each $ 0 \le j \le n-1 $ .
- Find $ f(c) $ . Since $ cost $ can be very large, output it modulo $ (10^9 + 7) $ .

Please note that under a fixed $ cnt $ you need to maximize the total number of coins $ cost $ , not its remainder modulo $ (10^9 + 7) $ .

## 说明/提示

In the first test case, there is only one cycle shift, which is equal to $ [1] $ , and all its elements are already equal.

In the second test case, you need to find the answer for three arrays:

1. $ f([1, 3, 2]) = (3, 3) $ .
2. $ f([3, 2, 1]) = (2, 5) $ .
3. $ f([2, 1, 3]) = (2, 5) $ .

Consider the case of $ [2, 1, 3] $ . To make all elements equal, we can pick $ l = 1 $ and $ r = 1 $ on the first operation, which results in $ [2, 2, 3] $ . On the second operation we can pick $ l = 0 $ and $ r = 1 $ , which results in $ [3, 3, 3] $ . We have used $ 2 $ operations, and the total number of coins received is $ 1^2 + 2^2 = 5 $ .

## 样例 #1

### 输入

```
5
1
1
3
1 3 2
5
3 2 4 5 1
8
6 5 6 4 2 6 2 2
4
10 10 10 10```

### 输出

```
0 0
3 3
2 5
2 5
7 18
7 16
6 22
5 28
5 28
9 27
9 27
9 27
9 27
11 23
9 27
9 27
13 19
0 0
0 0
0 0
0 0```

# 题解

## 作者：sunzz3183 (赞：6)

# CF1884E 题解

~~闲话：赛后看别人代码过的。~~

感谢 [Misono_Mika](https://codeforces.com/profile/Misono_Mika) 的代码与 [programmingysx](https://www.luogu.com.cn/user/724742) 思路上的帮助。

------------


## 分析

先转化题目：

求出一个 $maxa$，让每个 $a_i=maxa-a_i$ 题目就转化成了给定一个长度为 $n$ 的数组 $a$，每次选定一个 $a_{[l,r]}$ 全部 $-1$，花费代价 $1$，得到 $(r-l+1)^2$ 的价值。问最后使得全部 $a_i=0$ 的最少代价 $cnt$，并在代价最少的情况下求出最大价值 $cost$。

请对每一个 $i$ 开始的 $a$ 求出结果。

显然每次删除区间越长越好。

考虑先考虑代价 $cnt$ 怎么求，见下图：

![](https://pic.imgdb.cn/item/6536137cc458853aefd4fba8.png)

我们发现，对于这样的图，我们删除是这样删的：

- $[2,7],[2,7],[2,7],[2,2],[5,7],[2,2],[5,6],[2,2],[6,6]$

然后，我们把上面的每一段区间称为一条**删除线段**。

我们完全可以统计有多少个删除线段的**左端点**。

而每个左端点 $i$ 出现时的状态是 $a_i-a_{i-1}>0$，所以整个 $cnt$ 就等于，$\sum_{i=1}^{n} \max(0,a_i-a_{i-1})$。

然后我们对于每个起点求 $cnt$ 可以预处理出一个 $b$ 数组每个 $b_i$ 等于 $b_{i-1}+\max(0,a_i-a_{i-1})$ 每个起点的 $cnt_i=b_{i+n-1}-b_{i}+a_{i}$（注意此时 $a_i$ 是起点，且 $a_i$ 要复制一倍来求 $b_i$）。

然后求 $cost$。

我们考虑直接求不好求，我们发现对于一个 $a_i=0$（一定存在）的点是没有影响的，我们考虑把 $a_i=0$ 的 $i$ 设为 $pos$，把 $pos$ 作为中点，预处理从 $pos$ 向左和向右的 $l,r$ 数组，表示预处理从 $pos$ 开始向左和向右 $i$ 位的 $cost$，显然由于 $a_{pos}=0$ 的性质 $cost_i=l_j+r_{n-1-j},j=pos-i$，注意可能会越界，所以要对 $n$ 取 $mod$。

那么怎么求 $l,r$ 呢？

先考虑 $r$，$l$ 反着来一遍就可以了。

我们假设从 $a_{i-1}$ 推到 $a_i$ 的时候，可以和 $a_i$ 一起的删除线段长下面这个样子：

![](https://pic.imgdb.cn/item/65361c2ac458853aefeda270.png)

（显然是递增的，如果出现递减的，相当于线段已经到了右端点，贡献已经结束了）。

把前面所有红色的线段长度都设为 $c_j$，设 

$$ num=\sum_{j=1}^{a_i} c_j $$

那么，加进来一个 $a_i$ 之后，每个 $c_j$ 都变成了 $c_j+1$，价值从 $c_j^2$ 变成 $(c_j+1)^2=(c_j^2+2c_j+1)$，总价值就从 

$$ \sum_{j=1}^{a_i} c_j^2$$ 

变成 

$$ \sum_{j=1}^{a_i} (c_j+1)^2=\sum_{j=1}^{a_i} c_j^2+2\sum_{j=1}^{a_i} c_j+a_i=\sum_{j=1}^{a_i} c_j^2+2num+a_i$$

所以从 $r_{i-1}$ 到 $r_i$ 价值增加了 $2num+a_i$。

只要 $num$ 能线性求，$r_i$ 就能线性求。

如何线性求 $num$ 呢？发现 $num$ 的具象化和上面的图是一样的，而删除比当前 $a_i$ 大，保留一个单调递增的序列我们想到了什么？**单调栈**！

具体代码很好实现，不懂的可看注释：

$sum$ 表示，最大的一个 $sum$，满足 $\forall j\in [i-sum+1,i],a_j\geq a_i$ 

```cpp
stack<pair<int,int>>st;
    for(int i=pos+1,j=1,num=0;i<=pos+n;i++,j++){
        int sum=1;
        while(!st.empty()&&a[i]<=st.top().first){
            int h=st.top().first,w=st.top().second;st.pop();//h 为 a_j,w 相当于 a_j 的 sum
            (num+=mod-w*(h-a[i])%mod)%=mod;//减去比 a_i 高的部分
            sum+=w;
        }
        (r[j]=(a[i]+(num<<1))%mod+r[j-1])%=mod;
        num+=a[i];//每条线段都会增加1的长度，一共增加a_i
        st.push({a[i],sum});
    }
```

详细解释一下 `while` 函数里单调栈的实现：

考虑这样一张图：

![](https://pic.imgdb.cn/item/6536714ac458853aefd8901f.png)

假设序列长这样：

显然红色部分是栈里的元素，$a_i$ 前面的那个点就是要被弹出去的元素。

`-w*(h-a[i])` 就是删去的部分 $1$ 中的部分，你会问部分 $2,3$ 呢？因为，部分 $2,3$ 已经被之前的那些点删去了，所以不需要考虑。

而 $a_i$ 的 $sum$ 需要继承栈顶的 $sum$，所以 `sum+=w`。

$l$ 同理求。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=3e6+2,mod=1e9+7;
int n,a[N],l[N],r[N],b[N];
void Main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read(),l[i]=r[i]=0;
    int maxa=*max_element(a+1,a+n+1);
    for(int i=1;i<=n;i++)a[i+n+n]=a[i+n]=a[i]=maxa-a[i];
    for(int i=1;i<=n<<1;i++)b[i]=b[i-1]+max(a[i]-a[i-1],0ll);
    int pos=0;
    for(int i=n+1;i<=n<<1;i++)pos=a[i]?pos:i;
    stack<pair<int,int>>st;
    for(int i=pos+1,j=1,num=0;i<=pos+n;i++,j++){
        int sum=1;
        while(!st.empty()&&a[i]<=st.top().first){
            int h=st.top().first,w=st.top().second;st.pop();
            (num+=mod-w*(h-a[i])%mod)%=mod;
            sum+=w;
        }
        (r[j]=(a[i]+(num<<1))%mod+r[j-1])%=mod;
        num+=a[i];
        st.push({a[i],sum});
    }
    while(!st.empty())st.pop();
    for(int i=pos-1,j=1,num=0;i>=pos-n;i--,j++){
        int sum=1;
        while(!st.empty()&&a[i]<=st.top().first){
            int h=st.top().first,w=st.top().second;st.pop();
            (num+=mod-w*(h-a[i])%mod)%=mod;
            sum+=w;
        }
        (l[j]=(a[i]+(num<<1))%mod+l[j-1])%=mod;
        num+=a[i];
        st.push({a[i],sum});
    }
    for(int i=1;i<=n;i++){
        int L=pos-i,R=n-1-L;
        L=(L%n+n)%n;R=(R%n+n)%n;
        printf("%lld %lld\n",b[n+i-1]-b[i]+a[i],(l[L]+r[R])%mod);
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    int T=read();
    while(T--)Main();
    return 0;
}
```



---

## 作者：Petit_Souris (赞：1)

先不考虑环，就做一个序列的情况。改变一下 $a_i$ 的定义，定义为与初始最大值的差（因为最优策略显然是全部改到最大值）。 

第一问是容易的，就是经典的积木大赛，结论是 $\sum\limits_{i=1}^{n}\max(a_{i}-a_{i-1},0)$，这里我们认为 $a_0=0$.

第二问我们考虑上面那个式子是怎么来的。如果你依稀记得积木大赛的做法的话，我们实际上是在维护目前覆盖到 $i$ 的线段数量，如果 $a_{i+1}>a_i$ 就加入 $a_{i+1}-a_{i}$ 条新线段，否则断开 $a_i-a_{i+1}$ 条旧线段。那么为了使平方和尽可能大，我们每次一定会继续延长最长的线段，断开最短的线段。这个过程可以用单调栈维护。

最后考虑一下环怎么做。第一问还是容易的，第二问我们需要观察到一个很重要的事情：因为所有数都要改到最大值，所以最大值所在位置的 $a_i=0$。这启发我们从这个位置断环成链，因为不存在经过这个位置的操作。接着预处理前缀和后缀的答案，那么一个位移的答案就能表示成一个前缀 + 一个后缀的答案了。时间复杂度 $\mathcal O(n)$。

注意取模。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e6+9,Mod=1e9+7;
ll T,n,a[N],top,L[N],R[N];
pii stk[N];
void solve(){
    n=read();
    rep(i,1,n)a[i]=read();
    ll mx=*max_element(a+1,a+n+1);
    rep(i,1,n)a[i]=mx-a[i];
    top=0;
    ll P=0;
    rep(i,1,n){
        if(!a[i])P=i;
    }
    rep(i,0,n+1)L[i]=R[i]=0;
    ll lst=P,sum=0,cnt=0;
    rep(i,1,n){
        ll now=(lst==n?1:lst+1);
        if(a[now]>a[lst]){
            ll d=a[now]-a[lst];
            stk[++top]={d,i},cnt+=d;
        }
        else {
            ll d=a[lst]-a[now];
            while(d){
                if(stk[top].first<=d){
                    d-=stk[top].first,cnt-=stk[top].first,sum-=stk[top].first*(i-stk[top].second);
                    stk[top]={0,0},top--;
                }
                else cnt-=d,stk[top].first-=d,sum-=d*(i-stk[top].second),d=0;
            }
        }
        R[i]=(R[i-1]+2*sum+cnt)%Mod,sum+=cnt,lst=now;
    }
    lst=P,sum=0,cnt=0;
    rep(i,1,n){
        ll now=(lst==1?n:lst-1);
        if(a[now]>a[lst]){
            ll d=a[now]-a[lst];
            stk[++top]={d,i},cnt+=d;
        }
        else {
            ll d=a[lst]-a[now];
            while(d){
                if(stk[top].first<=d){
                    d-=stk[top].first,cnt-=stk[top].first,sum-=stk[top].first*(i-stk[top].second);
                    stk[top]={0,0},top--;
                }
                else cnt-=d,stk[top].first-=d,sum-=d*(i-stk[top].second),d=0;
            }
        }
        L[i]=(L[i-1]+2*sum+cnt)%Mod,sum+=cnt,lst=now;
    }
    ll C=0;
    rep(i,1,n){
        ll lst=(i==1?n:i-1);
        C+=max(0ll,a[i]-a[lst]);
    }
    rep(i,1,n){
        ll lst=(i==1?n:i-1);
        ll ncnt=C-max(0ll,a[i]-a[lst])+a[i];
        write(ncnt),putchar(' ');
        if(P>=i)write((L[P-i]+R[n-(P-i)-1])%Mod);
        else write((R[i-P-1]+L[n-(i-P-1)-1])%Mod);
        putchar('\n');
    }
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：zhongpeilin (赞：1)

## 题目大意：
你对于一个长度为 $N$ 的数组，现在有一种操作：  
选择两个整数 $1 \leq i \leq j \leq n$，将这一段区间都加 $1$，代价是 $(j - i + 1)^2$。  
设 $cnt$ 为他最少操作次数，$cost$ 表示在最小操作步数最小的前提下，代价最小。  
现在给你长度为 $N$ 的序列 $A$，请输出 $A$ 右移 $0 \leq i < n$ 的 $cnt$ 和 $cost$。  
## 解题思路：
一开始，我们设 $maxn$ 表示 $A$ 中的最大值，那么将所有的 $A$ 变成 $maxn - A_{i}$。这样会方便我们去处理后面的事情。  
现在，问题从区间加变成了区间减，从目标是 $maxn$ 变成了 $0$。  
那么，因为涉及到右移，我们不难想到多开两倍数组，破环为链，就是将一开始的 $A$ 的长度变成 $3 \times N$，并将 $A$ 变成 $A + A + A$，那么我们接下来分别考虑如何快速求出 $cnt$ 和 $cost$。  
求 $cnt$ 和 $cost$ 之前，我们不难发现一定是先将一个极大的非 $0$ 的块整体减 $1$。这个性质能帮我们更好的去解决 $cnt$ 和 $cost$。  
$cnt$：  
这个是比较容易想到的，我们在 $A$ 上再算一个 $B$ 数组， $B_{i}$ 表示前 $i$ 个数将他们都消掉的最小操作步数，那么我们考虑因为在 $i-1$ 这里一定会有 $A_{i-1}$ 个操作的目前的右端点是 $i-1$，那么如果 $A_{i} \ge A_{i-1}$，那么需要在以 $i$ 为开头，新建 $A_{i} - A_{i-1}$ 的操作。所以这种情况下 $B_{i} = B_{i-1} + A_{i} - A_{i-1}$。而对于 $A_{i} < A_{i-1}$ 的情况，我们需要断掉 $A_{i-1}-A_{i}$ 条区间减的操作，那么总操作数不变，所以 $B_{i} = B_{i-1}$。  
综上：$B_{i} = B_{i-1} + \max(A_{i} - A{i-1}, 0)$。  
那么对于 $i \sim i + n - 1$，$cnt$ 答案是 $B_{i + n - 1} - B_{i} + A_{i}$。为什么呢？因为如果减去 $B_{i-1}$ 的话，还要考虑 $A_{i-1}$，而减去 $B_{i}$ 只需要最后 $+ A_{i}$ 就行。  
时间复杂度：$O(n)$。  
$cost$：  
这里是本题的难点。但不难想到：设 $posmax$ 为 $A$ 中一个 $0$ 的位置。那么 $posmax$ 左边的和 $posmax$ 右边的答案是满足加法原理的，按照这个思路，我们设 $l_{i}$ 表示 $posmax - i \sim posmax - 1$ 所需要的最小的 $cost$，$r_{i}$ 表示 $posmax+1 \sim posmax + i$ 所全部消掉的最小代价。  
那么一下只讲 $r_{i}$ 的处理方式，而 $l_{i}$ 只需要再倒着做一遍即可。  
推 $r_{i}$ 的时候，我们考虑设 $cnt$ 表示那些长度未定的区间的长度总和，那么我们就可以维护个单调递增的单调栈，里头存个 pair，表示高度和之前以它为结尾的区间长度。那么我们可以通过 $r_{i} = r_{i - 1} + 2 \times cnt + a_{i}$ 就能推出 $r_{i}$，$l_{i}$。
时间复杂度：$O(n)$。
# code:
```cpp
#include<bits/stdc++.h>
#define int long long 
#define pii pair<int, int>

using namespace std;
const int mod = 1000000007;

int n, a[3000005], l[3000005], r[3000005], b[3000005];
stack< pair<int, int> > S;

void solve(){
	cin >> n;
	for(int i = 1; i <= 3 * n; i++) l[i] = r[i] = 0;
	int maxn = 0;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		maxn = max(maxn, a[i]);
		a[i + 2 * n] = a[i + n] = a[i]; //复制
	}
	for(int i = 1; i <= 3 * n; i++) { //计算+更改a[i]
		a[i] = maxn - a[i];
		b[i] = b[i - 1] + max(0ll, a[i] - a[i - 1]);
	}
	int pos_max = 0;
	for(int i = n + 1; i <= 2 * n; i++){ //寻找最大值
		if(a[i] == 0) pos_max = i;
	}
	
	int cnt = 0;
	while(!S.empty()) S.pop();
	for(int i = pos_max + 1; i <= pos_max + n; i++){ //算r[i]
		int val = 1;
		while(!S.empty() && a[i] <= S.top().first){
			int h = S.top().first, w = S.top().second; S.pop();
			cnt = (cnt + mod - w * (h - a[i]) % mod) % mod;
			val += w;
		}
		r[i - pos_max] = (a[i] + (cnt * 2) + r[i - pos_max - 1]) % mod; //套公式
        cnt += a[i];
        S.push({a[i], val});
	}
	
	while(!S.empty()) S.pop();
	cnt = 0;
	for(int i = pos_max - 1; i >= pos_max - n; i--){
        int val = 1;
        while(!S.empty() && a[i] <= S.top().first){
            int h = S.top().first, w = S.top().second; S.pop();
            cnt = (cnt + mod - w * (h - a[i]) % mod) %mod;
            val += w;
        }
		l[pos_max - i] = (a[i] + cnt * 2 % mod + l[pos_max - i - 1]) % mod; //这里同理
        cnt += a[i];
        S.push({a[i], val});
    }
    pos_max -= n;
    for(int i = 1; i <= n; i++){
    	cout << b[n + i - 1] - b[i] + a[i] << " ";
    	if(i <= pos_max) cout << (l[pos_max - i] + r[n - 1 - (pos_max - i)]) % mod << endl;
    	else cout << (l[pos_max + n - i] + r[n - 1 - (pos_max + n - i)]) % mod << endl;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int rp = 1; rp <= t; rp++) solve();
	return 0;
}
```
创作不易，点个赞吧 QWQ！

---

## 作者：Muse_Dash (赞：0)

考虑找到 $a$ 的最大值 $mx$，并把所有 $a_i$ 变成 $mx-a_i$。

对于 $cnt$：

显然，对于一个非循环数列，答案即为 $\sum_{i=1}^n\max\{0,a_i-a_{i-1}\}$，参见 [**P5019**](/problem/P5019)。把它变成循环的，只需要破环成链然后做前缀和。

对于 $cost$：

因为 $a_i=0$ 的地方是不用操作的，所以找到一个 $id$ 使得 $a_{id}=0$，然后记录 $l_i,r_i$ 分别表示 $[i,id-1],[id+1,i]$ 区间的 $cost$。

对于求 $l$，可以从右往左去搜这个序列。搜到 $i$ 时，如果 $a_i<a_{i+1}$，部分操作区间会终止；如果 $a_i>a_{i+1}$，操作区间会有所增加。这个统计过程可以单调栈进行维护。

具体地，考虑一个操作区间，如果其长度增加，那么一次插入元素只会将长度增加 $1$。而假定操作区间原长 $c$，那么原 $cost$ 就是 $c^2$，而 $c$ 在添加元素时变成 $c+1$，那么新的 $cost$ 会变为 $c^2+2c+1$，即增加了 $2c+1$。利用这个可以快速求 $cost$。

求 $r$ 与 $l$ 同理。因为是循环数组，且需要求 $l,r$，将原数组复制至三倍并使 $id\in[n+1,2n]$ 较为稳妥。

```cpp
for (int i=id-1,j=1,c=0,s=1;i>=id-n;i--,j++,s=1){
	while (!S.empty()&&S.top().fr>=a[i]){
  	int h=S.top().fr,w=S.top().sc;
		S.pop();
		c-=w*(h-a[i])%M,c=(c%M+M)%M;
		s+=w;
	}
	l[j]=(l[j-1]+(a[i]+(c<<1))%M)%M;
	c+=a[i],S.push({a[i],s});
}
```

---

