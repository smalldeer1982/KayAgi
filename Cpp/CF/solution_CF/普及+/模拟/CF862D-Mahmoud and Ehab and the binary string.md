# Mahmoud and Ehab and the binary string

## 题目描述

Mahmoud and Ehab are in the fourth stage now.

Dr. Evil has a hidden binary string of length $ n $ . He guarantees that there is at least one '0' symbol and at least one '1' symbol in it. Now he wants Mahmoud and Ehab to find a position of any '0' symbol and any '1' symbol. In order to do this, Mahmoud and Ehab can ask Dr. Evil up to $ 15 $ questions. They tell Dr. Evil some binary string of length $ n $ , and Dr. Evil tells the Hamming distance between these two strings. Hamming distance between 2 binary strings of the same length is the number of positions in which they have different symbols. You can find the definition of Hamming distance in the notes section below.

Help Mahmoud and Ehab find these two positions.

You will get Wrong Answer verdict if

- Your queries doesn't satisfy interaction protocol described below.
- You ask strictly more than $ 15 $ questions and your program terminated after exceeding queries limit. Please note, that you can do up to $ 15 $ ask queries and one answer query.
- Your final answer is not correct.

 You will get Idleness Limit Exceeded if you don't print anything or if you forget to flush the output, including for the final answer (more info about flushing output below).If you exceed the maximum number of queries, You should terminate with 0, In this case you'll get Wrong Answer, If you don't terminate you may receive any verdict because you'll be reading from a closed stream .

## 说明/提示

Hamming distance definition: [https://en.wikipedia.org/wiki/Hamming\_distance](https://en.wikipedia.org/wiki/Hamming_distance)

In the first test case the hidden binary string is 101, The first query is 000, so the Hamming distance is $ 2 $ . In the second query the hidden string is still 101 and query is 001, so the Hamming distance is $ 1 $ .

After some queries you find that symbol at position $ 2 $ is '0' and symbol at position $ 1 $ is '1', so you print "! 2 1".

## 样例 #1

### 输入

```
3
2
1
3
2
1
0```

### 输出

```
? 000
? 001
? 010
? 011
? 100
? 101
! 2 1```

# 题解

## 作者：DPair (赞：2)

提供一种随机化的写法，能保证正确性，一遍 $\text{AC}$ 。

## 【思路】
~~看到这种询问少的交互题第一反应随机化~~

我们发现只需要求一个 $0$ 和一个 $1$ ，考虑分开来求。

我们又发现求 $0$ 和求 $1$ 本质上是相同的。

因此我们就只拿其中一个来讲，假设我们要求 $1$ 。

首先我们必然需要一次询问求出整个序列中 $1$ 的总个数，设为 $cnt1$ ，方法为询问一个全 $0$ 的序列，返回值显然为 $1$ 的总个数。

然后我们就可以通过询问拼凑出 **一个区间内 1 的个数** 。

具体方法如下：

-----
假设我们要询问 $[l, r]$ 之间 $1$ 的个数。

我们可以把全零串中这个区间内的所有 $0$ 变成 $1$ ，相当于这个区间内原本 $1$ 产生贡献现在变成了 $0$ 产生贡献，记返回值为 $res$ 。

假设这个区间内有 $x$ 个 $1$， $y$ 个 $0$ ，可得：

$$
x+y=r-l+1
$$
$$
x-y=cnt1-res
$$
然后解一个二元一次方程即可，这个应该都会。

-----
现在我们有了一个工具，接下来继续说剩下的解法。

我们可以分两类讨论：

### 1、假设 $cnt1 \ge \frac{n}{2}$ 
这种情况下，我们随机去一个点 **取不到** $1$ 的概率是 $\frac{1}{2}$ ，多取几次这个概率就会指数级下降。运用刚才的方法我们可以得出一个点是否是 $1$ ，因此我们可以通过这种随机取点的方法得到 $1$ 的位置。

### 2、假设 $cnt1 < \frac{n}{2}$
此时我们只能二分。

每一次看一个子区间中是否有 $1$ ，这显然也可以通过询问一个区间 $1$ 的个数转化而来。

然后每一次区间缩小一半即可，这里要询问 $logn$ 也就是 $10$ 次左右。

然后我们就可以合并 $0,1$ 两个子问题了。

不难发现若 $1$ 满足情况 $1$ ，则 $0$ 必然满足情况 $2$ ，反之亦然。

于是我们随机化的次数最多 $4$ 次，正确性是保证不了的。

还是拿 $1$ 来说。

我们改为每一次随机两个点，若这两个点都是 $1$ ，那么任取其中一个即可，若有 $1$ 个不是 $1$ ，那么再询问这两个中的一个是否是 $1$ 就可以确定 $1$ 的位置，否则再次随机。

这样我们就能取 $6$ 个点（因为还需要一次询问两个点中是否有 $1$），再次提升了正确性。

实测这种解法一般可以在 $13$ 次询问以内得出答案。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, cnt1;
inline int get0(int l, int r){
    printf("? ");
    for (register int i = 1;i <= n;i ++) putchar(48 + (i <= r && i >= l));
    putchar(10);
    fflush(stdout);
    int res;scanf("%d", &res);
    return r - l + 1 - ((r - l + 1 + cnt1 - res) >> 1);
}
inline int get1(int l, int r){
    return r - l + 1 - get0(l, r);
}
inline int getpos(int l, int r){
    printf("? ");
    for (register int i = 1;i <= n;i ++) putchar(48 + (i == r || i == l));
    putchar(10);
    fflush(stdout);
    int res;scanf("%d", &res);
    return (2 + cnt1 - res) >> 1;
}
int main(){
    scanf("%d", &n);
    printf("? ");
    for (register int i = 1;i <= n;i ++) putchar(48);
    putchar(10);
    fflush(stdout);
    scanf("%d", &cnt1);
    srand(time(NULL));
    if(cnt1 >= (n >> 1)){
        int tot = 14;
        int l = 1, r = n, pos;
        while(l <= r){
            int mid = (l + r) >> 1;
            tot --;
            if(get0(l, mid)) pos = mid, r = mid - 1;
            else l = mid + 1;
        }
        while(tot --){
            int x = rand() % n + 1;
            int x2 = rand() % n + 1;
            while(x == x2){
                x = rand() % n + 1;
                x2 = rand() % n + 1;
            }
            int res = getpos(x, x2);
            if(res == 2){
                printf("! %d %d\n", pos, x);
                fflush(stdout);
                return 0;
            }
            if(res == 1){
                if(!get0(x, x)){
                    printf("! %d %d\n", pos, x);
                    fflush(stdout);
                    return 0;
                }
                else{
                    printf("! %d %d\n", pos, x2);
                    fflush(stdout);
                    return 0;
                }
            }
        }
    }
    else{
        int tot = 14;
        int l = 1, r = n, pos;
        while(l <= r){
            int mid = (l + r) >> 1;
            tot --;
            if(get1(l, mid)) pos = mid, r = mid - 1;
            else l = mid + 1;
        }
        while(tot --){
            int x = rand() % n + 1;
            int x2 = rand() % n + 1;
            while(x == x2){
                x = rand() % n + 1;
                x2 = rand() % n + 1;
            }
            int res = getpos(x, x2);
            if(res == 0){
                printf("! %d %d\n", x, pos);
                fflush(stdout);
                return 0;
            }
            if(res == 1){
                if(get0(x, x)){
                    printf("! %d %d\n", x, pos);
                    fflush(stdout);
                    return 0;
                }
                else{
                    printf("! %d %d\n", x2, pos);
                    fflush(stdout);
                    return 0;
                }
            }
        }
    }
}
```

---

## 作者：dead_X (赞：2)

## 前言
超级水的交互题，可以秒切（确信）
## 思路
我们先求出第一位是什么，这个任务可以用这两个询问解决：

```
? 00000...000
? 10000...000
```

不难发现，第一位为 $0$ 时上面比下面大 $1$，第一位为 $1$ 时下面比上面大 $1$。

然后我们的任务就变成了在剩余的 $999$ 个数中找另外一个。我们还剩下 $13$ 次询问，不难想到使用二分。注意到这些数中必定有一个对应种类的数（题目给定的要求），我们考虑判断**一个区间中是否全部是我们不需要的这种数**。

稍加思考就知道这玩意很水。不妨设我们要判断 $[l,r]$ 是否全是 $0$，我们只需要在 $[l,r]$ 的位置上输出 $1$，其余位置输出 $0$ 后，判断返回值和最开始全部输出 $0$ 的大小关系即可。

如果这些位置全是 $0$，那么返回值一定比全 $0$ 大 $(r-l+1)$，全 $1$ 同理。

因此，我们直接二分答案区间。我们先找一个肯定有目标数的区间 $[2,n]$，然后每次二分时判断左区间是否全是我们不需要的数，如果都是不需要的就将范围变成右区间，在 $l=r$ 的时候退出即可。
## 代码
```
#include<bits/stdc++.h>
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
using namespace std;
signed main(){
    int n=read();
	printf("? ");
	for(int i=1; i<=n; i++) printf("0");
	puts(""),fflush(stdout);
	int p=read();
	printf("? 1");
	for(int i=1; i<n; i++) printf("0");
	puts(""),fflush(stdout);
	int q=read();
	int id0=-1,id1=-1; 
	if(p>q) 
	{
		id1=1;//we need 0
		int l=2,r=n;
		while(l<=r)
		{
			if(l==r) 
			{
				id0=l;
				break;
			}
			int mid=(l+r)>>1;
			printf("? ");
			for(int i=1; i<=n; i++) if(l<=i && i<=mid) printf("1"); else printf("0");
			puts(""),fflush(stdout);
			int res=read();
			if(p-res==mid-l+1) l=mid+1; else r=mid; 
		}
	}
	else
	{
		id0=1;//we need 1
		int l=2,r=n;
		while(l<=r)
		{
			if(l==r) 
			{
				id1=l;
				break;	
			}
			int mid=(l+r)>>1;
			printf("? ");
			for(int i=1; i<=n; i++) if(l<=i && i<=mid) printf("1"); else printf("0");
			puts(""),fflush(stdout);
			int res=read();
			if(res-p==mid-l+1) l=mid+1; else r=mid; 
		}
	}
	printf("! %d %d\n",id0,id1);
	fflush(stdout);
    return 0;
}
```

---

## 作者：wmrqwq (赞：1)

简单题。

# 题目链接

[CF862D Mahmoud and Ehab and the binary string](https://www.luogu.com.cn/problem/CF862D)

# 解题思路

首先我们可以发现，字符串的第一个字母不是 $1$ 就是 $0$，因此我们可以容易花费 $2$ 次询问来找到数字 $0$ 或数字 $1$ 所在的一个位置。

然后，显然的，我们以先找到的数字为 $0$ 为例，那么我们就可以先询问一个全为 $0$ 的字符串，然后通过构造前 $Mid$ 位为 $1$，其余都为 $0$ 的字符串来二分出第一个 $1$ 的位置，因为你会发现，如果这个字符串与全为 $0$
的字符串的权值差为 $Mid$，那么前 $Mid$ 为都为 $0$，反之，前 $Mid$ 位必然有至少一个 $1$，因此我们可以通过二分来确定，而先找到的数字为 $1$ 也是同理。

综上，询问次数为 $3 + \log n$ 次，可以通过此题。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//#define endl '\n'
#define QwQ return 0;
ll _t_;
void _clear(){}
ll n;
string ans;
string S;
ll get(string s)
{
	ll sum=0;
	forl(i,0,n-1)
		sum+=s[i]!=ans[i];
	return sum; 
}
ll ask(string s)
{
	cout<<"? "<<s<<endl;
	ll x;//=get(s);
	cin>>x;
	return x;
}
string f(ll x)
{
	string SS="";
	forl(i,1,x)
		SS+='0';
	forl(i,x+1,n)
		SS+='1';
	return SS;
}
string f2(ll x)
{
	string SS="";
	forl(i,1,x)
		SS+='1';
	forl(i,x+1,n)
		SS+='0';
	return SS;	
}
ll ans0,ans1;
void solve()
{
	_clear();
	cin>>n;
	forl(i,1,n)
		S+='0';
	ll q1=ask(S);
	S[0]='1';
	ll q2=ask(S);
	if(q1>q2)
		ans1=1;
	else
		ans0=1;
	S="";
	forl(i,1,n)
		S+='1';
	ll q3=ask(S);
	if(!ans0)
	{
		ll L=1,R=n;
		while(L<R)
		{
			ll Mid=(L+R)/2;
			if(ask(f(Mid))==q3+Mid)
				L=Mid+1;
			else
				R=Mid; 
		}
		cout<<"! "<<L<<' '<<ans1<<endl;
	}
	else
	{
		ll L=1,R=n;
		while(L<R)
		{
			ll Mid=(L+R)/2;
			if(ask(f2(Mid))==q1+Mid)
				L=Mid+1;
			else
				R=Mid; 
		}
		cout<<"! "<<ans0<<' '<<L<<endl;		
	}
	
}
int main()
{
//	IOS;
	_t_=1;
 //	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：lytqwq (赞：0)



首先我们查询 $00000000$，得到不一样的就是 $1$ 的个数。

再查询一遍 $10000000$ ，就能得到 第一个位置是 $0 $ 还是 $1$ ， 我们再找另一个答案。


再查询 $11110000$ ：

设 $len$ 为这次查询改变的数个个数 。

如果答案因此恰好变化 $len$ ，分变化的正负讨论答案在哪一边。

否则直接在 $l,mid$ 里继续递归 （因为这里一定有答案）

这样递归下去 最多找 $logn$ 次，就能找到结果 。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int n;
int ans[N][N],ans0,ans1;
string ask=" ";
void findans(int l,int r,int flag,int bef){
	if(l==r){
		if(flag)ans1=l;
		else ans0=l;
		return ;
	}
	int mid=(l+r)>>1,now1;
	for(int i=l;i<=mid;i++){
		ask[i]='1'+'0'-ask[i];
	}
	cout<<"? "<<ask<<endl;
	cin>>now1;
	if(ask[l]-'0'==flag){
		if(now1-bef==mid-l+1)findans(mid+1,r,flag,now1);
		else findans(l,mid,flag,now1);
	}
	else{
		if(bef-now1==mid-l+1)findans(mid+1,r,flag,now1);
		else findans(l,mid,flag,now1);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)ask+="0";
	cout<<"? "<<ask<<endl;
	cin>>ans[1][n];
	ask[n]='1';
	cout<<"? "<<ask<<endl;
	cin>>ans[1][n-1];
	ask[n]='0';
	if(ans[1][n]>ans[1][n-1]){
		ans1=n;
		findans(1,n,0,ans[1][n]);
	}
	else{
		ans0=n;
		findans(1,n,1,ans[1][n]);
	}
	cout<<"! "<<ans0<<" "<<ans1<<endl;
}
```




---

## 作者：Leap_Frog (赞：0)

### P.S.
好家伙，第一次交互一发 A （在不看题解的情况下。  
这篇题解好像比楼上楼下的代码都简洁？（截至当前  
### Description.
给定一个 `01` 串，要求在 `15` 次询问内找到任意一个为 `0` 的位置和一个为 `1` 的位值。  
每次询问你可以给定一个和原串等长的 `01` 串，会回答你两个字符串相差的字符数。  
### Solution.
这个询问数量限制让人想到显然是复杂度 $\log$ 的二分。  

我们首先查询字符串中有多少个 `0`。  
然后我们把一段区间替换成 `1`，我们就能得到这段区间内 `0` 和 `1` 数量差。  
而我们显然知道了这段区间 `0` 和 `1` 和为区间长度，所以我们可以知道区间 `0` 数量和 `1` 数量。  

显然，我们随机选择一个位置，它肯定是最终答案的一半（下面代码中选择了第 n 个位置。  
然后，我们需要在剩下所有串中找到另一个数字。  
这个显然可以二分（虽然并没有单调性。  
我们首先可以用一次询问查询一个区间是否全部都为 `0` 或 `1`。  
（毕竟上面都已经可以求出区间有多少个 `0` 了。  
如果区间完全没有待查元素，那就别管这个区间。  
否则直接在这个区间递归就好了。  
虽然没有单调性，但我们只需要知道一个答案，所以这样是对的。  
查询次数为 $O(\log N)$。  
### Coding.
```cpp
//愿你和你重要的人能够再次重逢！
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>59;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:0;
}int n,tot;
inline int qry(int l,int r)
{//查询把 [l,r] 变成 1 后不同字符数量
	putchar('?'),putchar(' ');for(int i=1;i<=n;i++) putchar(48|(i>=l&&i<=r));
	putchar('\n'),fflush(stdout);int x;return read(x),x;
}
inline int solve(int l,int r,int qwq)//这是找到任一 !qwq 的函数
{
	int md=(l+r)>>1;if(l==r) return l;//终止条件
	if(qry(l,md)+(md-l+1)*((qwq<<1)-1)==tot) return solve(md+1,r,qwq);else return solve(l,md,qwq);
	//这个条件手玩/推式子搞一下就出来了，具体不解释。
}
int main()
{
	read(n),tot=qry(0,0);int tt=qry(n,n);//tot相当于是全0，tt判断第 n 个位置的类型
	if(tt==tot+1) printf("! %d %d\n",n,solve(1,n-1,0));else printf("! %d %d\n",solve(1,n-1,1),n);//找到就好了
	return 0;
}
```

---

