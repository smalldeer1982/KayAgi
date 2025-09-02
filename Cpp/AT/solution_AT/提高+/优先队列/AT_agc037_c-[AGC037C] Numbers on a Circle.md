# [AGC037C] Numbers on a Circle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc037/tasks/agc037_c

円環状に $ N $ 個の正整数が並んでおり、それらには円環に沿った順に $ 1 $ から $ N $ の番号がついています。

今 $ i $ 番目の数は $ A_i $ です。高橋君は $ i $ 番目の正整数が $ B_i $ となるようにしたいです。 そこで、高橋君は以下の操作を繰り返し行うことにしました。

- $ 1\ \leqq\ i\ \leqq\ N $ なる整数 $ i $ を一つ選ぶ。
- $ i-1,i,i+1 $ 番目の数をそれぞれ $ a,b,c $ としたとき、$ i $ 番目の数を $ a+b+c $ に置き換える。

ただし、$ 0 $ 番目の数は $ N $ 番目の数を指し、$ N+1 $ 番目の数は $ 1 $ 番目の数を指すことに注意してください。

高橋君が条件をみたすように操作を行うことができるかどうか判定してください。 また可能である場合は、高橋君が行う必要のある操作回数として考えられる最小の値を求めてください。

## 说明/提示

### 制約

- $ 3\ ≦\ N\ ≦\ 2\ \times\ 10^5 $
- $ 1\ ≦\ A_i,\ B_i\ ≦\ 10^9 $
- 入力中のすべての値は整数である

### Sample Explanation 1

例えば高橋君は以下のように操作を行うことができます。 - $ 2 $ 番目の数を $ 3 $ に置き換える。 - $ 2 $ 番目の数を $ 5 $ に置き換える。 - $ 3 $ 番目の数を $ 7 $ に置き換える。 - $ 1 $ 番目の数を $ 13 $ に置き換える。

## 样例 #1

### 输入

```
3
1 1 1
13 5 7```

### 输出

```
4```

## 样例 #2

### 输入

```
4
1 2 3 4
2 3 4 5```

### 输出

```
-1```

## 样例 #3

### 输入

```
5
5 6 5 2 1
9817 1108 6890 4343 8704```

### 输出

```
25```

# 题解

## 作者：installb (赞：4)

忘记判 $A_i>B_i$ 直接无解了，怎么这样还能 `AC` 啊，~~AtCoder 数据太水了。~~  
感谢 @strangers 在评论区提供的 hack 数据。  

---

...后面是正文  

直接加感觉不可做，于是考虑反过来，这样一次操作将 $B$ 数组中一个数减去他左右数之和。  

即将 $B_i$ 变为 $B_i-B_{i-1}-B_{i+1}$。  

再找切入点，相当于我们找转化后第一次操作，也就是原来的最后一次操作，由于每一个数必须是正整数，所以对于当前 $B$ 数组中的最大值 $B_i$，$B_{i-1}$ 和 $B_{i+1}$ 是不可以执行操作的，也就是说这两个数在对 $B_i$ 执行操作前不能够改变。  

这样即使 $B_{i-1}$ 需要操作，也**必定在 $B_i$ 之后（转化后的问题）操作**。所以我们先对最大值操作，操作结束后，我们发现这个序列还可以继续按上面的方式找出最大值，于是再找最大值，这个过程可以用堆维护。  

- 每一步找出数组中最大值，对这个数执行操作直到不能再减为止。

注意如果把一个数减到了 $A_i$，就弹出可以数找剩下里面的最大值，相当于这个数永远不需要再操作了，移出这个体系。  

如果最大值已经没法再操作了，但是还是 $\neq A_i$，就无解，因为能且只能影响它的左右位置的两个数一样没法变化。

这样不能保证时间复杂度，所以需要把多次操作一起执行，我们直接每次减去直到不能再减为止，因为如果还可以再减，$B_i>B_{i-1}+B_{i+1}$，$B_{i-1}$ 和 $B_{i+1}$ 是还是不可以执行操作。  

这样一个数每次一定至少减半。  

时间复杂度 $O(n\log n\log W)$，$W$ 为值域。  

```cpp
using namespace std;
typedef long long LL;

LL n,ans = 0;
LL a[200005],b[200005];
LL c[200005];

struct node{
    LL id,val;
    // 注意元素同时要存在数组中的位置
    bool operator < (const node &nd)const{
        return nd.val > val;
    }
}h,t;
priority_queue <node> q;

bool cmp(LL x,LL y){
    return b[x] > b[y];
}

LL getnum(LL x){
    if(x == 0) return n;
    if(x == n + 1) return 1;
    return x;
    // 处理环问题
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    for(LL i = 1;i <= n;i ++) cin >> a[i];
    for(LL i = 1;i <= n;i ++) cin >> b[i];
    
    for(LL i = 1;i <= n;i ++){
    	if(a[i] > b[i]){
    		cout << -1 << endl;
    		return 0;
		}
	} // 无解
    
    for(LL i = 1;i <= n;i ++){
        if(a[i] < b[i]){
            t.id = i; t.val = b[i];
            q.push(t);
        }
    }

    while(!q.empty()){
        LL del,mns,i = q.top().id; q.pop();
        del = b[i] - a[i];
        mns = b[getnum(i - 1)] + b[getnum(i + 1)];

        if(del / mns == 0 && b[i] != a[i]){ cout << -1 << endl; return 0; }
        // 无解

        ans += del / mns;
        b[i] -= (del / mns) * mns;
        // 直接减完
        if(b[i] > a[i]){
            t.id = i; t.val = b[i];
            q.push(t);
        }
		// 还没到 a[i]，到了就不用再入队了
    }
    cout << ans << endl;
    return 0;
}
```

原评分 $\sf{\color{blue}1961}$  
前置知识：堆  
代码难度/实现难度：很低吧  

---

## 作者：gdf_yhm (赞：2)

[AT_agc037_c](https://www.luogu.com.cn/problem/AT_agc037_c)

[Numbers on a Circle](https://atcoder.jp/contests/agc037/tasks/agc037_c)

### 思路

正难则反。正向使数组 $a$ 变成数组 $b$，才疏学浅，不会。

可以考虑逆向模拟 $b$ 变 $a$。每次使 $b_i$ 减小为 $b_i-b_{i-1}-b_{i+1}$，直至 $b_i=a_i$。

从一组样例入手：

```cpp
6
1 1 4 5 1 4
6 31 4 29 69 25

ans:9
```

显然，$b_5=69$ 是数组中最大的。如果先做 $b_5$ 的邻居是不符合条件的，只能先做 $b_5$。得到：

```cpp
6
1 1 4 5 1 4
6 31 4 29 15 25
```

同理再做 $b_2$。所以使用优先队列，每次弹出最大值，处理后再将新的值入队。而样例中 $a_3$ 处，$a_3=b_3=4$，不用处理，则不用入队。

于是写了一发，TLE，瓶颈在于一个数可能多次减他的左右两边。例如：

```cpp
3
1 2 1
1 1000000000 1
```

所以能减就一次减到底。

```cpp
b[t]=(b[t]-a[t])%(b[t-1]+b[t+1])+a[t];
```

注意：

- 令 $b[0]=b[n],b[n+1]=b[1]$。

- 答案开long long

- 如果没法减了且 $b_i\neq a_i$，输 $-1$。

---

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int n,a[maxn],b[maxn],cnt;
struct nd{
	int id,val;
    bool operator <(const nd &u)const{
        return u.val>val;
    }
}u;
priority_queue<nd> q;

signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		b[i]=read();
		if(b[i]<a[i]){
			printf("-1\n");
			return 0;
		}
		if(a[i]!=b[i]){
			u.id=i;u.val=b[i];
			q.push(u);
		}
	}
	b[0]=b[n];b[n+1]=b[1];
	while(!q.empty()){
		int t=q.top().id;q.pop();
		if((b[t]-a[t])/(b[t-1]+b[t+1])==0 && b[t]!=a[t]){
			printf("-1\n");
			return 0;
		}
		cnt+=(b[t]-a[t])/(b[t-1]+b[t+1]);
		b[t]=(b[t]-a[t])%(b[t-1]+b[t+1])+a[t];
		if(b[t]>a[t]){
			u.id=t;u.val=b[t];
			q.push(u);
		}
		b[0]=b[n];b[n+1]=b[1];
	}
	printf("%lld\n",cnt);
}
```

---

## 作者：XCDRF_ (赞：1)

# AT_agc037_c \[AGC037C] Numbers on a Circle

[原题传送门](https://atcoder.jp/contests/agc037/tasks/agc037_c)

[更好的阅读体验](https://www.luogu.com.cn/article/d8g72s5x)

## 题目大意

一个环上有 $n$ 个正整数，一次操作可让 $a_i\to a_{i-1}+a_i+a_{i+1}$，求多少次操作可以使 $a$ 变成 $b$，若无解输出 $-1$。

## 解题思路

看到题目后，首先想暴力。每个点都可以加，加的次数还不确定，状态实在太多，无法在多项式时间内解决这个问题。

正难则反，我们可以尝试让 $b$ 变成 $a$，一次操作也就转化成了 $b_i\to b_i-b_{i-1}-b_{i+1}$。

再怎么做？观察到所有数都是正整数，所以一次操作能执行的前提条件就是 $b_i\ge b_{i-1}+b_{i+1}$。我们不妨先找最大值操作，再找次大值操作，再找更小的值操作……这样可以保证所有能操作的数都不会漏掉。这个过程可以用一个堆维护。

如果一个 $b_i$ 已经减到了 $a_i$，就将这个数出堆，不再进行操作。如果当前的最大值已经无法操作，但还是 $≠a_i$，就无解了。因为它无法操作，它旁边的两个也会无法操作，它不可能有操作的机会，无解。

还可能一个数可以多次减它旁边的数，如果一次一次的减，复杂度得不到保证。所以一次全减完，直到不能再减。这样一次至少能减去一半以上。

时间复杂度 $O(n\log n\log w)$，其中 $w$ 为值域。

答案记得开 long long。

## 参考代码

```cpp
#include<iostream>
#include<queue>
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int N=2e5+5;
int n;
long long ans;
int a[N],b[N];
priority_queue<pii> q;
int num(int x){//环上操作
	if(x==0) return n;
	if(x==n+1) return 1;
	return x;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
    	cin>>b[i];
    	if(b[i]<a[i]){
    		cout<<-1;//如果b比a小，直接无解
    		return 0;
		}
		if(b[i]>a[i]) q.push(mp(b[i],i));//入堆
	}
	while(!q.empty()){
		int t=q.top().se;
		q.pop();
		int now=b[t]-a[t],d=b[num(t-1)]+b[num(t+1)];
		if(now/d==0&&now!=0){
			cout<<-1;//如果不能操作，且a不等于b，则无解
			return 0;
		}
		ans+=1ll*now/d;//一次减完
		b[t]-=(now/d)*d;
		if(b[t]!=a[t]) q.push(mp(b[t],t));
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/agc037/submissions/61907853)

---

## 作者：tzjahinie (赞：1)

思路：因为对 $A_i$ 的一次操作是使其加上左右两边的数，思考一下，可以容易得出结论：**小的数一定是先得得到，大的数是后得到的**。

由于正推有多种可能，我们需要使用反推来开做此题。

由前面得出的结论可得：反推方式是固定的，即在 $B$ 数组开始操作，依次从大到小操作，大于目标数时，按操作后数的大小入队；等于目标数时出队；小于目标数或者无法操作时，结束循环输出 $-1$。

至此，整道题的大体思路就到此为止，接下来开始考虑用何种方式实现。

由于要记录 $B$ 数组的实时大小和对应的下标，所以使用结构体。由于过程中需要插入新的元素。考虑使用优先队列。可以用重载运算符来排序。代码如下：

~~~cpp
struct candy{
	int id,val;
	bool operator < (const candy &x) const {
		return val<x.val;
	}
};
priority_queue <candy> q;
~~~

这样就有一个按 $val$ 为关键字从小到大排序的优先队列了。

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long ans;
int a[200005],b[200005];
struct candy{
	int id,val;
	bool operator < (const candy &x) const {
		return x.val > val;
	}
};
priority_queue <candy> q;
int find(int x){
	if(x== 0 ) return n;
	if(x==n+1) return 1;
	return x;
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for (int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		if(a[i]>b[i]){
			puts("-1");
			return 0;
		}else if(a[i]<b[i]){
			candy k={i,b[i]};
			q.push(k);
		}		
	}
	while(!q.empty()){
		candy k=q.top();
		q.pop();
		int sum=b[find(k.id-1)]+b[find(k.id+1)];
		if(b[k.id]-a[k.id]<sum){
			puts("-1");
			return 0;
		}
		ans+=(b[k.id]-a[k.id])/sum;
		b[k.id]-=(b[k.id]-a[k.id])/sum*sum;
		if(b[k.id]>a[k.id]){
			k.val=b[k.id];
			q.push(k);
		}
	}
	printf("%lld\n",ans);
}
~~~

---

## 作者：yshpdyt (赞：0)

## 题意
一个环上有 $n$ 个正整数，一次操作可以令 $A_i\leftarrow A_{i-1}+A_i+A_{i+1}$，求多少次操作可以使 $A$ 变成 $B$，无解输出 $-1$。


$1 \leq n \leq 2\times10^5$。


## Sol

加法的可能性太多，随随便便就超过限制了，考虑倒着对 $B$ 进行减操作，由于原序列最后操作的元素会比较大，为了防止减成负数，我们应该对每个极大值点，即 $B_i>B_{i-1}+B_{i+1}$ 这样的 $i$ 优先操作，对于所有符合题意的 $i$，不妨设一对相邻的极大值点一个为 $i_1$，另一个为 $i_2$，其满足 $|i_2-i_1|+1\ge3$，这也就是说，**对 $i_1$ 操作不会使 $i_2$ 变成非极大值点**，于是乎所有极大值点无关操作顺序。

考虑每次如何快速求出一个极大值点，显然的，序列的最大值一定是一个极大值点，于是可以用优先队列维护，每次取出最大值进行操作直到该位置非极大值点，或已经 $\le A_i$。

考虑算法复杂度，每次每个数至少减少一半，这是因为如果 $2(B_{i-1}+B_{i+1})< B_i$，减若干次后 $ B_i'<B_{i-1}+B_{i+1}$，如果 $2(B_{i-1}+B_{i+1})\ge B_i$，减一次后 $ 2B_i'\ge B_i$，复杂度为 $O(n\log n\log V)$。
## Code
```cpp
ll n,a[N],b[N];
priority_queue<pair<ll,ll> >q;
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
        q.push({b[i],i});
    }
    ll res=0;
    while(!q.empty()){
        auto t=q.top();
        q.pop();
        if(b[t.se]==a[t.se])continue;

        ll l=(t.se-1+n)%n,r=(t.se+1)%n;
        ll now=(b[l]+b[r]);
        if(b[t.se]<a[t.se]||now==0||(b[t.se]-a[t.se])/now==0){
            cout<<-1<<endl;
            return 0;
        }
        res+=(b[t.se]-a[t.se])/now;
        b[t.se]=a[t.se]+(b[t.se]-a[t.se])%now;
        t.fi=b[t.se];
        if(b[t.se]<a[t.se]){
            cout<<-1<<endl;
            return 0;
        }
        if(b[t.se]!=a[t.se])q.push(t);
    }
    cout<<res<<endl;
    return 0;
}
```

---

## 作者：Jsxts_ (赞：0)

从 $A$ 变成 $B$ 似乎不好下手，考虑从 $B$ 变成 $A$，那么每次的操作就是 $B_i\rightarrow B_i-B_{i-1}-B_{i+1}$。

注意到这个操作只有 $B_i>B_{i-1}+B_{i+1}$ 时才能操作，所以 $B_{i-1}$ 和 $B_{i+1}$ 在 $B_i$ 操作不了后才能操作。那么也就意味着，必须将每个尚未达到目标且大于相邻数的和的减到不能减为止，这样这题就变成了模拟。实现的话直接扫数组会被卡，那么用队列存下每个可能能操作的数，直到队列为空就结束，这样会操作 $O(n\log n)$ 次（类似辗转相除），每次加入队列的数是 $O(1)$ 的，复杂度为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 2e9;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n,a[200010],b[200010];
int l(int x) {return (x - 1 + n) % n;}
int r(int x) {return (x + 1) % n;}
int main() {
	n = read();
	for (int i = 0;i < n;i ++ ) a[i] = read();
	for (int i = 0;i < n;i ++ ) b[i] = read();
	queue<int> q;
	for (int i = 0;i < n;i ++ ) {
		if (b[i] > b[l(i)] + b[r(i)]) q.push(i);
	}
	ll ans = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		if (b[x] != a[x] && b[x] > b[l(x)] + b[r(x)]) {
			int t = b[l(x)] + b[r(x)];
			if ((b[x] - a[x]) % t == 0) ans += (b[x] - a[x]) / t, b[x] = a[x];
			else ans += b[x] / t, b[x] %= t;
			q.push(l(x)), q.push(r(x));
		}
	}
	for (int i = 0;i < n;i ++ ) if (b[i] != a[i]) puts("-1"), exit(0);
	cout << ans;
	return 0;
}
```


---

