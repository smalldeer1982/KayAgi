# Nastia and a Hidden Permutation

## 题目描述

This is an interactive problem!

Nastia has a hidden permutation $ p $ of length $ n $ consisting of integers from $ 1 $ to $ n $ . You, for some reason, want to figure out the permutation. To do that, you can give her an integer $ t $ ( $ 1 \le t \le 2 $ ), two different indices $ i $ and $ j $ ( $ 1 \le i, j \le n $ , $ i \neq j $ ), and an integer $ x $ ( $ 1 \le x \le n - 1 $ ).

Depending on $ t $ , she will answer:

- $ t = 1 $ : $ \max{(\min{(x, p_i)}, \min{(x + 1, p_j)})} $ ;
- $ t = 2 $ : $ \min{(\max{(x, p_i)}, \max{(x + 1, p_j)})} $ .

You can ask Nastia at most $ \lfloor \frac {3 \cdot n} { 2} \rfloor + 30 $ times. It is guaranteed that she will not change her permutation depending on your queries. Can you guess the permutation?

## 说明/提示

Consider the first test case.

The hidden permutation is $ [3, 1, 4, 2] $ .

We print: "? $ 2 $ $ 4 $ $ 1 $ $ 3 $ " and get back $ \min{(\max{(3, p_4}), \max{(4, p_1)})} = 3 $ .

We print: "? $ 1 $ $ 2 $ $ 4 $ $ 2 $ " and get back $ \max{(\min{(2, p_2)}, \min{(3, p_4)})} = 2 $ .

Consider the second test case.

The hidden permutation is $ [2, 5, 3, 4, 1] $ .

We print: "? $ 2 $ $ 3 $ $ 4 $ $ 2 $ " and get back $ \min{(\max{(2, p_3}), \max{(3, p_4)})} = 3 $ .

## 样例 #1

### 输入

```
2
4

3

2

5

3```

### 输出

```
? 2 4 1 3

? 1 2 4 2

! 3 1 4 2

? 2 3 4 2

! 2 5 3 4 1```

# 题解

## 作者：meyi (赞：6)

~~CF救命题，没这题就rk 5k了...~~

不难发现，若我们已经掌握 $p_i=1$ 的 $i$，则可以用这样一条询问：`1 i j n-1` 来得到 $p_j$ 的值，其相当于询问 $\max(\min(n-1,p_i),\min(n,p_j))$，因为 $p_i=1,1<p_j\leq n$，所以 $\max(\min(n-1,p_i),\min(n,p_j))=\max(1,p_j)=p_j$。

于是我们用 $n-1$ 次查询得到了所有 $j\neq i$ 的 $p_j$ 的值，那么问题转化为用 $\leq \lfloor\frac{n}{2}\rfloor+31$ 次查询找出 $p_i=1$ 的 $i$。

考虑这样一条询问的意义：`2 j k 1`

根据题意，它表示的是 $\min(\max(1,p_j),max(2,p_k))$，其中 $\max(1,p_j)$ 必定为 $p_j$，故其可以简化为 $\min(p_j,max(2,p_k))$。好像还是看不出什么东西，我们来具体讨论一下它的返回值：

- 返回值为 $1$，即 $\min(p_j,max(2,p_k))=1$，其中 $max(2,p_k)\geq2$，故 $p_j=1$。

- 返回值为 $2$，即 $\min(p_j,max(2,p_k))=2$，则 $p_j=2$ 或 $p_k\leq2$。

- 返回值 $>2$，即 $\min(p_j,max(2,p_k))>2$，则 $p_j>2$ 且 $p_k>2$。

分别观察一下：第一种给了我们需要的 $p_i=1$ 的 $i$；第二种说明 $p_k$ 可能 $=1$，且只会在 $p_j=2$ 或 $p_k\leq2$ 时得到，故我们只会遇见第二种范围值不超过 $2$ 次，且可以通过查询 `2 k j 1` 确定 $p_k$的值；第三种范围过广，没有用。

先假设 $n$ 为偶数（因为按如下方法若没有找到 $p_i=1$ 的 $i$，则 $i=n$ ），考虑对所有奇数 $k$ 进行如下查询 `2 k k+1 1`，则我们会共执行 $\lfloor\frac{n}{2}\rfloor$ 次查询，且这些查询包括了排列的每个元素，故至少会有一个查询的返回值 $\leq2$，然后按上述方式进行处理，即可得到 $i$ 的值。

于是我们通过 $\leq \lfloor\frac{3n}{2}\rfloor+2$ 次查询解决了本题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define SZ(k) k.size()
#define ALL(k) k.begin(),k.end()
#define DEBUG(k...) fprintf(stderr,k)
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;
template<class T>inline bool chkmax(T &x,const T &y){return x<y?x=y,true:false;}
template<class T>inline bool chkmin(T &x,const T &y){return x>y?x=y,true:false;}
const int maxn=2e5+10;
int ans[maxn],n,rt,t_case;
inline void ask(int op,int i,int j,int x){
	cout<<"? "<<op<<" "<<i<<" "<<j<<" "<<x<<endl;
}
int main(){
	cin>>t_case;
	while(t_case--){
		cin>>n;
		rt=0;
		for(ri i=1,j;i<n;i+=2){
			ask(2,i,i+1,1);
			cin>>j;
			if(j==1){rt=i;break;}
			if(j==2){
				ask(2,i+1,1,1);
				cin>>j;
				if(j==1){rt=i+1;break;}
			}
		}
		if(!rt)rt=n;
		ans[rt]=1;
		for(ri i=1;i<=n;++i)
			if(i!=rt){
				ask(1,rt,i,n-1);
				cin>>ans[i];
			}
		cout<<"!";
		for(ri i=1;i<=n;++i)cout<<" "<<ans[i];
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Macesuted (赞：4)

[点击此处以获得更佳阅读体验](https://www.macesuted.cn/article/cf1521c/)

---

[题面](https://www.luogu.com.cn/problem/CF1521C)

# 题意

交互题。

交互库在开始时会生成一个长为 $n$ 的排列 $p$。你在开始时仅知道排列的长度 $n$，你需要在进行不超过 $\lfloor \frac {3 \times n} 2 \rfloor + 30$ 次询问后输出这个排列。

你可以进行两种类型的提问：

1. `? 1 i j x`： 交互库会告诉你 $\max(\min(x,p_i),\min(x+1,p_j))$ 的值。
2. `? 2 i j x`： 交互库会告诉你 $\min(\max(x,p_i),\max(x+1,p_j))$ 的值。

# 分析

我们考虑指定 $i,~j,~x$ 后所有可能的情况下的询问结果，为了方便归类，下面忽略了相等的情况。

1. $p_i >x,~p_j>x+1$： $1$ 询问返回 $x+1$，$2$ 询问返回 $\min(p_i,p_j)$。
2. $p_i>x,~p_j<x+1$： $1$ 询问返回 $x$，$2$ 询问返回 $x+1$。
3. $p_i<x,~p_j>x+1$： $1$ 询问返回 $x+1$，$2$ 询问返回 $x$。
4. $p_i<x,~p_j<x+1$： $1$ 询问返回 $\max(p_i,p_j)$，$2$ 询问返回 $x$。 

我们发现这四种情况中仅 $1$ 情况的 $2$ 询问，和 $4$ 情况的 $1$ 询问返回的值与 $p$  相关，我们考虑从此处入手。

由于我们需要得知具体的 $p$ 中的每一个元素的值，考虑可以对两个元素同时进行 $1$ 情况的 $2$ 询问和 $4$ 情况的 $1$ 询问，以得到这两个元素中的较大值和较小值，但无法确定这两个值具体对应的位置。接着可以再通过 $2$ 情况和 $3$ 情况下的询问确定这两个元素的具体大小关系，就可以确定这两个位置上分别的值。

具体地，我们可以先考虑将 $n$ 长度的排列两两分组，如果 $n$ 为奇数则先忽略最后一个元素。对于每组内的两个元素：

1. 询问 `? 2 i j 1`，在大部分情况下 $p_i\ge1,~p_j\ge2$，可以对应 $1$ 情况，得到 $\min(p_i,p_j)$；当 $p_j=1$ 时该询问会对应 $2$ 情况，返回 $2$。我们可以对于所有返回值为 $2$ 的情况再询问 `? 1 i j 1`，若返回值为 $2$ 则确认对应 $1$ 情况，$\min(p_i,p_j)=2$；否则返回值一定为 $1$，确认对应 $2$ 情况，$p_j=1$。
2. 询问 `? 1 i j n-1`，在大部分情况下 $p_i \le n-1,~p_j \le n$，可以对应 $4$ 情况，得到 $\max(p_i,p_j)$；当 $p_i=n$ 时该询问会对应 $2$ 情况，返回 $n-1$。我们可以对于所有返回值为 $n-1$ 的情况再询问 `? 2 i j n-1`，若返回值为 $n-1$ 则确认对应 $4$ 情况，$\max(p_i,p_j)=n-1$；否则返回值一定为 $n$，确认对应 $2$ 情况，$p_i=n$。
3. 询问 `? 1 i j min(p[i],p[j])`，若返回值为 $\min(p_i,p_j)$ 则说明对应 $2$ 情况，$p_i > \min(p_i,p_j),~p_j<\min(p_i,p_j)+1$，所以 $p_i>p_j$；否则返回值一定为 $\min(p_i,p_j)+1$，对应 $3$ 情况，$p_i<\min(p_i,p_j),~p_j>\min(p_i,p_j)+1$，所以 $p_i < p_j$。（由于忽略了相等的情况所以式子可能不成立，但是足以判断两个元素的大小关系了）
4. 对于上一步中得到的 $p_i$ 与 $p_j$ 的大小关系，和之前得到的 $\min(p_i,p_j),~\max(p_i,p_j)$，得到 $p_i,~p_j$ 的值。

对于 $n$ 为奇数的情况，在前 $n-1$ 个元素的值被求出后，找到那个没有被求出过的值赋值到 $p[n]$ 即可。

对于每两个元素我们进行了大约三次操作，且步骤 $1$ 和步骤 $2$ 中用于检验的询问次数相当少，所以总操作次数大约为 $\lfloor \frac {3 \times n} 2 \rfloor$，可以通过本题。

# 代码

如果上面的解释看懵了，也许可以尝试看一下代码。

~~代码比解释清楚多了~~

```cpp
/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

int ask1(int i, int j, int p) {
    cout << "? 1 " << i << ' ' << j << ' ' << p << endl;
    int ret;
    cin >> ret;
    return ret;
}
int ask2(int i, int j, int p) {
    cout << "? 2 " << i << ' ' << j << ' ' << p << endl;
    int ret;
    cin >> ret;
    return ret;
}

int p[10005];
bool vis[10005];

int main() {
    ios::sync_with_stdio(false);
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        for (register int i = 1; i <= n; i++) vis[i] = false;
        for (register int i = 1; i < n; i += 2) {
            int ret = ask1(i, i + 1, n - 1);
            p[i] = (ret == n - 1 && ask2(i, i + 1, n - 1) == n) ? n : ret;
            ret = ask2(i, i + 1, 1);
            p[i + 1] = (ret == 2 && ask1(i, i + 1, 1) == 1) ? 1 : ret;
            if (ask1(i, i + 1, p[i + 1]) == p[i + 1] + 1) swap(p[i], p[i + 1]);
            vis[p[i]] = vis[p[i + 1]] = true;
        }
        if (n & 1)
            for (register int i = 1; i <= n; i++)
                if (!vis[i]) p[n] = i;
        cout << '!';
        for (register int i = 1; i <= n; i++) cout << ' ' << p[i];
        cout << endl;
    }
    return 0;
}
```


---

## 作者：hgckythgcfhk (赞：2)

注意到：

$\min(\max(1,p_i),\max(2,p_j))=1$ 时，当且仅当 $p_i=1$，这个东西等于 $2$ 时，当且仅当 $p_j\le 2$，对于第一种情况，我们可以得出 $1$ 的位置，对于第二种情况，我们可以通过任选一个 $x$，进行 $2\ p_j\ x\ 1$ 操作，检查 $p_j$ 是 $1$ 还是 $2$，整个序列有且恰好有两个这种 $j$，所以我们可以这样找到 $1$ 的位置。

同时，$\max(\min(n-1,1),{n,p_i})=p_i$，我们可以通过 $p_1$ 的位置推出所有的其他位置。

于是这个题做完了，程序写的时候思路有点乱，不是最体现这个思路的写法，但是能过，程序并不重要，思路很明确，很容易写出来。

为防止火车头导致打回，省略了宏定义和头文件，但不影响阅读。
```cpp
unsigned a[N];
#define fls cout<<endl
signed main(){open;int T;cin>>T;while(T--){int n;cin>>n;
	int p1=0,p2=0;
	for(int i=1+(n&1);i<n;i+=2){int x;
		cout<<"? 2 "<<i<<" "<<i+1<<" 1",fls;
		cin>>x;if(x==1){p1=i;break;}
		if(x==2){p2?p1=i+1:p2=i+1;if(p1)break;}
	}if(p2){cout<<"? 2 "<<p2<<" "<<p2-1<<" 1";fls;
		int x;cin>>x;if(x==1)p1=p2;}if(!p1)p1=1;
	for(int i=1;i<=n;++i)if(i^p1)cout<<"? 1 "<<p1<<' '<<i<<' '<<n-1,fls,cin>>a[i];else a[i]=1;
	cout<<"! ";for(int i=1;i<=n;++i)cout<<a[i]<<' ';fls;
}}

```

---

## 作者：DaiRuiChen007 (赞：1)

# CF1521C 题解



## 思路分析

首先考虑通过指定 $x$ 为极大值或极小值来确定内层的 $\min,\max$ 运算的结果。

假设在第一种操作中，我们令 $x=n-1$，那么询问 `? 1 i j n-1` 的结果会变成 $\max(\min(n-1,p_i),p_j)$，在大部分情况下，这个式子的值为 $\max(p_i,p_j)$，而假如我们已经知道了其中 $p_i$ 的值，那么当 $p_j>p_i$，我们能确定 $p_j$ 的值，而当 $p_i=1$ 时，我们就能靠这个操作还原整个排列 $\{p_i\}$。

那么原问题转化成找到 $1$ 在 $\{p_i\}$ 里的位置。

接下来我们应该考虑采用第二种操作，我们令 $x=1$，那么询问 `? 2 i j 1` 的结果会变成 $\min(p_i,\max(2,p_j))$，讨论一下 $1$ 所在的位置对答案带来的影响：

- $p_i=1$ 时，原式答案为 $1$。
- $p_j=1$ 时，原式答案为 $2$。

注意到此时我们剩下的操作数大约为 $\dfrac n2+30$ 次，因此考虑每次询问相邻的两个数的答案，比如询问 $(1,2),(3,4),(5,6),\cdots,(n-1,n)$，如果某次返回的答案 $>2$，说明这两个数中没有 $1$。

而我们记录下所有让返回答案 $\le 2$ 的 $(i,j)$，不过注意到 $p_i$ 或 $p_j$ 为 $2$ 时，返回答案也为 $2$，所以我们接下来要进行一些操作来甄别究竟是那种情况。

考虑交换 $(i,j)$，询问 `? 2 j i 1`，那么对于每对可能的 $(i,j)$，如果询问 $(i,j)$ 的答案为 $1$，那么 $p_i=1$，如果询问 $(j,i)$ 的答案为 $1$，那么 $p_j=1$，否则 $p_i,p_j$ 中只有 $2$ 没有 $1$。

所以我们再对于每个可能的 $(i,j)$ 花费一次询问即可，可以证明这样的 $(i,j)$ 数量极少，再确定 $p_i=1$ 的具体 $i$ 值这一步骤的花费极小，肯定不到 $30$ 次，因此这个策略能够通过本题。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(int t,int i,int j,int x) {
	cout<<"? "<<t<<" "<<i<<" "<<j<<" "<<x<<endl;
	int ret; cin>>ret; return ret;
}
const int MAXN=1e4+1;
int p[MAXN],val[MAXN];
inline void solve() {
	int n,pos=0;
	cin>>n;
	vector <int> ch;
	for(int i=1;i<n;i+=2) {
		val[i]=read(2,i,i+1,1);
		if(val[i]<=2) ch.push_back(i);
	}
	if(n%2==1) {
		val[n-1]=read(2,n-1,n,1);
		if(val[n-1]<=2) ch.push_back(n-1);
	}
	for(int x:ch) {
		val[x+1]=read(2,x+1,x,1);
		if(val[x]==1) {
			pos=x;
			break;
		}
		if(val[x+1]==1) {
			pos=x+1;
			break;
		}
	}
	p[pos]=1;
	for(int i=1;i<=n;++i) {
		if(i==pos) continue;
		p[i]=read(1,pos,i,n-1);
	}
	cout<<"! ";
	for(int i=1;i<=n;++i) cout<<p[i]<<" ";
	cout<<endl;
}
signed main() {
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```



---

## 作者：jdsb (赞：1)

### 分析
对于操作 $1$，如果我们询问的 $x=n-1$，在正常情况下的返回值就是 $p_i$，$p_j$ 中的较大值，同理对于操作 $2$，如果询问的 $x=1$ 会返回两者中的较小值，那如果我们通过 $\lfloor \frac n2 \rfloor$操作 $1$ 找到了最大值 $n$ 的位置，那么我们就可以直接用 $n$ 次操作 $2$ 来把整个序列找出来。

但是有对于操作 $1$ 有一种情况可能出错，就是当 $p_i=n$ 时，并不会返回 $n$ 而是 $n-1$，但是我们又可以发现一个性质，就是当且仅当 $p_j=n$ 时才会返回 $n$，也就是说我们对于所有返回值为 $n-1$ 的一对询问 $p_i,p_j$，我们可以再次用一次查询 $1$询问 $p_j,p_i$，如果此时返回值为 $n$ 说明 $p_i=n$，而返回值为 $n-1$ 的情况最多只有两种，所以不会超过询问次数。

因为我的实现时是对于相邻两个数之间询问，所以对于 $n$ 为奇数时，如果恰好此时 $n$ 排在最后一个，我们之前就判不出来了，但此时也只有可能 $n$ 在最后一个，特判一下就行了。

### 代码
```cpp
#include<bits/stdc++.h>
#define fre(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout)
#define ll long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') { if(c=='-') f=-1;c=getchar(); }
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^'0'),c=getchar();
	return x*f;
}
const int N=1e4+5;
int n,mn[N],mx[N],po[N];
inline int  query1(int x,int y){
	cout<<"? 1"<<' '<<x<<' '<<y<<' '<<n-1<<endl;
	int p=read();
	cout.flush();
	return p;
}
inline int query2(int x,int y){
	cout<<"? 2"<<' '<<x<<' '<<y<<' '<<1<<endl;
	int p=read();
	cout.flush();
	return p;
}
int ans[N];
inline void solve(){
	n=read();
	vector<int>vt;
	for(int i=1;i<=n;i++) ans[i]=0;
	for(int i=1;i+1<=n;i+=2){
		mn[i]=query1(i,i+1);
		if(mn[i]>=n-1) vt.push_back(i);
	}
	int posn=0;
	if(vt.size()==1){
		int i=vt[0];
		if(query1(i,i+1)==n) ans[i+1]=n,posn=i+1;
		else if(query1(i+1,i)==n) ans[i]=n,posn=i;
	}
	else if(vt.size()==2){
		int i=vt[0],j=vt[1];
		if(query1(i,i+1)==n) ans[i+1]=n,posn=i+1;
		else if(query1(i+1,i)==n) ans[i]=n,posn=i;
		else if(query1(j,j+1)==n) ans[j+1]=n,posn=j+1;
		else if(query1(j+1,j)==n) ans[j]=n,posn=j;
	}
	if(!posn) ans[n]=n,posn=n;
	for(int i=1;i<=n;i++) if(!ans[i]) ans[i]=query2(i,posn);
	cout<<"! ";
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	cout<<endl;
}
int main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```


---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

### 题意

[CF1521C](https://www.luogu.com.cn/problem/CF1521C)。

一个长度为 $n$ 的排列 $p$，需要在 $\lfloor\frac{3n}{2}\rfloor+30$ 次操作内还原这个序列。

可以进行的操作如下：

- `1 i j x`，查询 $\max(\min(x,p_i),\min(x+1,p_j))$。
- `2 i j x`，查询 $\min(\max(x,p_i),\max(x+1,p_j))$。

以上两种操作要求 $x\in[1,n),i,j\in[1,n]$ 且 $i\ne j$。

### 题解

看见这种 $\max$ 和 $\min$ 套一起可以尝试把一部分的 $\max$ 或者 $\min$ 变成定值来简化。最显然的定值就是 $1$，如果我们知道 $p_t=1$，就可以通过 $\max(\min(n-1,p_t),\min(n,p_i))=p_i$ 在 $n-1$ 次查询内还原整个排列。

注意到给定的上界是$\lfloor\frac{3n}{2}\rfloor+30$ 次操作，忽略后面的 $30$，去掉知道 $1$ 的位置后花费的 $n-1$ 次操作还剩下 $\lfloor\frac{n}{2}\rfloor$ 次操作。

考虑每次查询相邻两项是否可行，讨论一下发现是可行的，这里查询 `2 i i+1 1`，记返回值 $t$：

- 若 $p_i=1$，此时 $t=1$。
- 若 $p_{i+1}=1$，此时 $t=2$。
- 若 $p_i\ne1,p_{i+1}\ne1$，此时 $t>1$。

注意到第一种情况时直接找到了 $1$ 的位置，第二种情况交换 $i,i+1$ 再进行一次查询可以变成第一种情况。

而第三种情况若 $t>2$ 则可以直接跳过，问题在 $t=2$ 会被归为第二种情况进行无用查询。仔细思考后可以发现无须担心，$t=2$ 仅会在 $p_i=2$ 或 $p_{i+1}=2$ 时出现，而由于排列的性质只会进行一次无用查询。

至此我们在 $\lceil\frac{3n}{2}\rceil$ 次操作内完成了排列的还原。

[record](https://codeforces.com/contest/1521/submission/325896012)。

```cpp
#include <bits/stdc++.h>
#define lint __int128
//#define int long long
#define fi first
#define se second
#define Il inline
#define vec vector
#define pb push_back
#define IT ::iterator
#define p_q priority_queue

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef double db;
const int N=1e4,Inf=1e9;
const db eps=1e-9,pi=acos(-1.0);

mt19937 rnd(time(0));
Il int rint(int l,int r){return rnd()%(r-l+1)+l;}

int T,n,a[N+5]; 

Il int solve(){
	for(int i=1;i<n;i+=2){
		cout<<"? 2 "<<i<<' '<<i+1<<" 1"<<endl;cout.flush();
		int t;cin>>t;if(t>2)continue;
		if(t==1)return i;
		cout<<"? 2 "<<i+1<<' '<<i<<" 1"<<endl;cout.flush();
		cin>>t;if(t==1)return i+1;
	}
	return n;
}

Il void buwanyuanshen(){
	cin>>n;int ps=solve();a[ps]=1;
	for(int i=1;i<=n;i++){
		if(i==ps)continue;
		cout<<"? 1 "<<ps<<' '<<i<<' '<<n-1<<endl;cout.flush();
		cin>>a[i]; 
	}
	cout<<"! ";for(int i=1;i<=n;i++)cout<<a[i]<<' ';
	cout<<endl;cout.flush();
	return;
}

signed main(){
    cin>>T;while(T--)buwanyuanshen();
	return 0;
}
//g++ -o a a.cpp -std=c++14 -O2 -Wall
```

---

## 作者：1234567890sjx (赞：0)

看到这种题先考虑若已知序列中某一个数是否能够容易的将整个序列推平。考虑若序列中存在一个位置 $p$ 满足当前已知 $a_p=1$，则考虑一直询问 `1 p i n-1`（$p\neq i$），此时答式的值为 $\max(\min(n-1,1),\min(n,a_i))=\max(1,\min(a_i,n))=a_i$。因此对该问题的回答的值就正好是 $a_i$ 的值！于是就可以在 $n-2$ 次操作内询问（为什么不是 $n-1$ 次？排列确定了 $n-1$ 个数另一个数的值可以直接确定。）

问题变为如何确定位置 $p$ 满足 $a_p=1$。这一类询问还是考虑给 $x$ 赋一个特殊值。发现除了上面的操作以外还有 $\frac{n}{2}+32$ 次询问可用，于是考虑把元素两两配对然后每组分别询问。考虑每一次询问 `2 x y 1`，则询问返回的值即为 $\min(\max(1,a_x),\max(2,a_y))=\min(a_x,\max(2,a_y))$。钦定这个值为 $t$，考虑她到底是什么。

+ $t=1$。则此时显然右边式子取不到 $1$，因此 $a_x=1$。
+ $t=2$。则此时若左侧式子取到最小值则 $a_x=2$，若右侧式子取到最小值则 $a_y\le 2$。
+ $t>2$。则此时左右两个式子的值都比 $2$ 大，也就是 $a_x>2,a_y>2$。

容易发现若 $\min(a_x,a_y)\le 2$ 则 $t\le 2$。于是只需要处理每一组满足 $t\le 2$ 的二元组 $(x,y)$。显然询问中这样的二元组数量不会超过 $2$。

现在只需要对于一组 $(x,y)$，在不超过 $16$ 次询问内确定其中是否存在一个 $w\in\lbrace x,y\rbrace$ 满足 $a_w=1$ 并确定 $w$ 的值了。首先在前面询问 `2 x y 1` 时，若 $t=1$ 则必然有 $a_x=1$，若 $t=2$ 则必然有 $a_x=2$ 或 $a_y\le 2$。考虑再反方向询问答案，即询问 `2 y x1`。此时若 $p_x=2$，则返回的表达式的值为 $\min(p_y,2)$。若 $p_y=1$ 则返回 $1$，否则返回 $2$；若 $p_y\le 2$，则返回的表达式的值为 $p_y$。若 $p_y=1$ 则返回 $1$，否则返回 $2$。最多额外询问 $2$ 次，于是可以通过该题啦。

代码，因为我懒所以最后的排列询问了 $n-1$ 次。

```cpp
int a[N];
void run() { int T = read(); while (T--) { int n = read();
    int pos = -1; for (int i = 1; i <= n; i += 2) {
        int l = i, r = i + 1; if (r > n) r = i - 1;
        cout << "? 2 " << l << ' ' << r << " 1" << endl; int o = read();
        if (o == 1) {pos = l; break;} if (o == 2) {
            cout << "? 2 " << r << ' ' << l << " 1" << endl; o = read();
            if (o == 1) {pos = r; break;}
        }
    }
    int now = 0; a[pos] = 1;
    for (int i = 1; i <= n; ++i) {
        if (i == pos) continue;
        cout << "? 1 " << pos << ' ' << i << ' ' << n - 1 << endl;
        int o = read(); a[i] = o;
    }
    cout << "! "; for (int i = 1; i <= n; ++i) cout << a[i] << ' '; cout << endl; }
}
```

---

## 作者：Hoks (赞：0)

## 前言
交互构造题，真的是太有意思了！

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
发现题目给出的交互次数并不充裕，但是给的是个排列，所以肯定是有什么特殊性质。

首先我们必然会用掉 $n$ 次，因为一个数想要猜出来肯定要花费一次。

考虑如何解决一个数只猜一次这个问题。

不妨先把他转化一下，这就相当于把题目中的式子化简为一项。

考虑我们能否将 $t=1$ 的式子化简：

如果另我们要求的为 $p_i$，那么想要令 $ \max{(\min{(x, p_i)}, \min{(x + 1, p_j)})}=p_i$ 的话，就要保证 $x>p_i$ 且 $p_j<p_i$。

考虑什么时候我们可以保证这个条件。

令 $p_j=1,x=n-1$，那么 $p_i>1$ 必然能满足这个条件。

这样就可以用 $n-1$ 次弄出其他所有数字，但是前提是要找到 $p_j=1$ 才行。

接着考虑怎么找这个 $p_j=1$。

考虑使用 $2$ 操作，并且类似的尽可能降低 $x$ 的影响。

所以取 $t=2,x=1$，这样式子即为：

$$\min(p_i,\max(2,p_j))$$

考虑对其值 $x$ 分类讨论：

1. $x=1$ 时，$p_i=1$。
2. $x=2$ 时，$p_i=2$ 或 $p_j\le2$。
3. $x>2$ 时，$p_i>2$ 且 $p_j>2$。

考虑对于所有奇数的 $i$ 都做一次 $2~i~i+1~1$ 这样的询问。

如果找到值为 $1$ 的，那么 $p_i=1$。

如果找到值为 $2$ 的，那么再把 $p_{i+1}$ 放到前面去询问，如果再次得到值为 $1$，则 $p_{i+1}=1$。

否则，$n$ 肯定为奇数且 $p_n=1$。

接着跑上面的方法即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+10,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int a[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='0'||c<='1'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
signed main()
{
    int T,n;cin>>T;
    while(T--)
    {
        cin>>n;int op=0;
        for(int i=1,x;i<n;i+=2)
        {
            cout<<"? "<<2<<" "<<i<<" "<<i+1<<" "<<1<<endl;
            cin>>x;if(x==1){op=i;break;}
            if(x==2){cout<<"? "<<2<<" "<<i+1<<" "<<1<<" "<<1<<endl;cin>>x;if(x==1){op=i+1;break;}}
        }if(!op) op=n;a[op]=1;
        for(int i=1;i<=n;i++)
        {
            if(i==op) continue;
            cout<<"? "<<1<<" "<<op<<" "<<i<<" "<<n-1<<endl;
            cin>>a[i];
        }cout<<"! ";
        for(int i=1;i<=n;i++) cout<<a[i]<<" ";cout<<endl;
    }
    genshin:;flush();return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

$\textbf{1.1 Hints}$

- $\textbf{1.1.1 Hint 1}$

如果你知道当 $i=k$ 时，$a_i = 1$，在 $n-1$ 次询问内问出排列。

- $\textbf{1.1.2 Hint 2}$

在 $\lfloor \dfrac{n}{2} \rfloor + 2$ 次询问内得到 $k$ 的值。

- $\textbf{1.1.3 Hint 3}$

为了完成 $\text{Hint 2}$，你可以只选用 $t=2$，并尝试消除 $x$ 的影响。

- $\textbf{1.1.4 Hint 4}$

令 $\text{Hint 3}$ 中所有询问的 $x = 1$。

$\textbf{1.2 Solution}$

如果你知道当 $i=k$ 时，$a_i = 1$，你可以通过每次询问 $t = 1,i = k,j = q,x =n-1$ 来得到 $a_q$ 的值，显然这组询问的答案是 $\max(\min(n-1,1),\min(n,a_q)) = a_q$，只需要 $n-1$ 次询问。

考虑 $\text{Hint 4}$。我们每次询问 $t = 2$，选择两个下标 $p,q$，令 $x = 1$，则会返回 $\min(\max(1,a_p),\max(2,a_q))$。如果返回值是 $1$，那么 $a_p$ 必然等于 $1$。如果返回值是 $2$，则只可能是 $a_p = 2,a_q = 2$ 或者 $a_q = 1$。我们考虑如何检验 $a_q = 1$，类似的，只需要将 $p,q$ 反过来再问一次，判断返回值是否为 $1$ 即可。

小细节是如果 $n$ 是奇数，且前 $n-1$ 个数字都没有 $1$，不必再问而可以直接确定 $k=n$。谨防此时询问越界。

最多需要 $\lfloor \dfrac{n}{2} \rfloor+2+n-1$ 次操作，可以通过。

$\textbf{1.3 Code}$

```cpp
/**
 *    author: sunkuangzheng
 *    created: 04.10.2023 10:45:54
**/
#include<bits/stdc++.h>
using namespace std;
int t,n,x,T,k,a[500005];
int ask(int t,int i,int j,int x){cout << "? " << t << " " << i << " " << j << " " << x << endl,cin >> k;return k;}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> T;
    while(T --){
        cin >> n;int p1 = -1;
        for(int i = 1;i+1 <= n;i += 2){
            int b = ask(2,i,i+1,1);
            if(b == 1) {p1 = i;break;}
            if(b == 2) if(ask(2,i+1,i,1) == 1) {p1 = i + 1;break;}
        }if(p1 == -1) p1 = n;a[p1] = 1;
        for(int i = 1;i <= n;i ++) if(i != p1) a[i] = ask(1,p1,i,n-1);
        cout << "! ";
        for(int i = 1;i <= n;i ++) cout << a[i] << " ";cout << endl;
    }
}
```


---

## 作者：DJRzjl (赞：0)


观察到这题询问回答非常怪，很不直观，我们需要考虑对与不同的询问 $op,i,j,x$​​​ 下的询问结果分类（下面忽略了等于的情况，等于可以分在任意一种中）：

1. $p_i>x,~p_j>x+1$​​​： $op=1$​​​ 时返回 $x+1$，$op=2$ 时返回 $\min(p_i,p_j)$​​​；
2. $p_i>x,~p_j<x+1$： $op=1$ 时返回 $x$，$op=2$ 时返回 $x+1$；
3. $p_i<x,~p_j>x+1$： $op=1$ 时返回 $x+1$，$op=2$ 时返回 $x$；
4. $p_i<x,~p_j<x+1$​： $op=1$​ 时返回 $\max(p_i,p_j)$​，$op=2$​ 时返回 $x$​​。

考虑以情况 $1,4$​ 的方式询问，不难发现，如果我们知道了 $1$​ 的位置 $pos_1$​，可以通过第 $4$​ 类询问的形式询问 `1 pos_1 j n-1`，返回值就是 $max(1,p_j)=p_j$​。于是我们就可以用 $n-1$​ 次询问确定其他位置的值，问题转化为如何在不多于 $\lfloor\frac{3n}{2}\rfloor+30-(n-1)=\lfloor\frac n2\rfloor+31$​ 次询问内确定 $pos_1$​。

如何确定 $pos_1$？考虑询问 `2 i j 1` 的意义。

若 $p_i\ge1,p_j\ge 2$​​​，就是第 $1$​​​ 类询问的形式，所以会返回 $\min(p_i,p_j)$​​​；否则 $p_j=1$​​​，此时是第 $2$​​​ 类询问，返回 $2$​​​。进而可以推得：

- 当返回值为 $1$。于是有 $p_i=1$，那么我们要求的 $pos_1$ 就等于 $i$​​；
- 当返回值为 $2$。此时有 $p_j=1$ 或 $\min(p_i,p_j)=2$​，$j$ 可能成为 $pos_1$；
- 否则，返回值 $>2$。此时 $\min(p_i,p_j)>2$，所以 $i,j$ 都不是要求的 $pos_1$。

那么我们考虑依次询问所有 `2 2i-1 2i 1`，其中 $2\le2i\le n,i\in N^*$（即询问 $(1~2),(3~4)\dots$），总共 $\lfloor \frac n2 \rfloor$​​​ 次询问。

如果其中第 $i$ 个询问返回了 $1$，直接有 $pos_1=2i-1$；否则没有返回 $1$​ 的询问，此时：

① 若仅存在一个询问返回了 $2$，那么这个询问对应的 $2i$ 就是 $pos_1$​​；

② 若存在两个询问返回 $2$（最多存在两个，此时一个询问中 $p_{2i}=1$，另外一个有 $\min(p_{2i-1},p_{2i})=2$），两个询问的 $2i$ 都有可能成为答案，不妨设这两个置为 $p1,p2$，我们再询问一次 `2 p1 p2 1`，若返回值为 $1$ ，则 $pos_1=p1$，否则 $pos_1=p2$​​​。

看起来已经可以解决问题了，但是在 $n$ 为奇数的情况下，开始我们询问的 $\lfloor \frac n2 \rfloor$ 次询问不能覆盖到第 $n$ 个位置，所以此时我们需要多花费一次询问确定 $pos_1$ 是否等于 $n$​，具体就是询问 `2 n i 1`，其中 $i$ 是任意位置，若返回 $1$ 就说明 $pos_1=i$，否则我们可以当 $n$ 不存在继续处理。

于是我们总共用了不超过 $\lfloor \frac n2 \rfloor +2+n-1=\lfloor \frac {3n}2 \rfloor +1$​ 次操作确定了排列，可以通过本题。

---
### Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=1e3+10;

int t,n,k,in[N];
vector<int>c[N];
char myd[20];

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) in[i]=0;
		for(int i=1,sz,x;i<=k;i++){
			scanf("%d",&sz);
			c[i].clear();
			while(sz--) scanf("%d",&x),in[x]=i,c[i].pb(x);
		}
		int mx,L=1,R=n,mid,ret,p=0;
		printf("? %d",n);
		for(int i=1;i<=n;i++) printf(" %d",i);
		putchar('\n');
		fflush(stdout);
		scanf("%d",&mx);
		for(int i=1;i<=n;i++)
		while(L<=R){
			mid=L+R>>1;
			printf("? %d",mid-L+1);
			for(int i=L;i<=mid;i++) printf(" %d",i);
			putchar('\n');
			fflush(stdout);
			scanf("%d",&ret);
			if(ret==mx) R=mid-1;
			else L=mid+1;
		}
		p=in[L];
		if(p){
			printf("? %d",n-(int)c[p].size());
			for(int i=1;i<=n;i++) if(in[i]!=p) printf(" %d",i);
			putchar('\n');
			fflush(stdout);
			scanf("%d",&ret);
		}
		putchar('!');
		for(int i=1;i<=k;i++) printf(" %d",i==p?ret:mx);
		putchar('\n');
		fflush(stdout);
		scanf("%s",myd);
	}
	return 0;
}
```



---

