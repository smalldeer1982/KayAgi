# [USACO24JAN] Balancing Bacteria B

## 题目描述

Farmer John 有 $N$（$1\le N\le 2\cdot 10^5$）块草地排成一行，其中草地 $i$ 的细菌水平与健康草的细菌水平相差 $a_i$（$−10^{15}\le a_i\le 10^{15}$）。例如，如果 $a_i=−3$，则草地 $i$ 的细菌水平比正常水平低 $3$，需要额外添加恰好 $3$ 个单位的细菌才能将其提高到被认为是健康的程度。

Farmer John 想要确保每一块草地都被修复至健康的细菌水平。方便的是，他有两种品牌的农药可以喷洒在他的田地里，一种可以添加细菌，另一种可以去除细菌。当 Farmer John 喷洒任一类型的农药时，他站在草地 $N$（最右边的草地）并为他的喷雾器选择功率等级 $L$（$1\le L\le N$）。

喷雾器对靠近 Farmer John 的草地效果最大，随着距离增加效果逐渐减弱。如果 Farmer John 选择添加细菌的农药，则 $L$ 单位的细菌将被添加至草地 $N$，$L−1$ 单位添加至草地 $N−1$，$L−2$ 单位添加至草地 $N−2$，以此类推。草地 $1\ldots N−L$ 不会得到任何细菌，因为喷雾器设置的功率不足以到达它们。类似地，如果 Farmer John 选择去除细菌的农药，则 $L$ 单位的细菌将被从草地 $N$ 去除，$L−1$ 单位被从草地 $N−1$ 去除，以此类推。同样，草地 $1\ldots N−L$ 将不受影响。

求 Farmer John 使用喷雾器的最少次数，使得每块草地都具有健康草的推荐细菌值。输入保证答案不超过 $10^9$。

**注意这个问题涉及到的整数可能需要使用 64 位整数型（例如，C/C++ 中的 "long long"）。**

## 说明/提示

### 样例解释 1

使用去除细菌的农药，功率等级为 $1$，使用五次。然后使用添加细菌的农药，功率等级为 $2$，使用一次。

### 测试点性质

- 测试点 $3-5$：$N\le 10^3$，答案不超过 $10^3$。
- 测试点 $6-10$：$N\le 10^3$。
- 测试点 $11-15$：没有额外限制。

## 样例 #1

### 输入

```
2
-1 3```

### 输出

```
6```

## 样例 #2

### 输入

```
5
1 3 -2 -7 5```

### 输出

```
26```

# 题解

## 作者：jokiii (赞：17)


前言：第一眼看到题在一个给定序列上加上一个等差数列就觉的和[这题](https://www.luogu.com.cn/problem/P1438)有点类似，但发现首项和公差均为 $1$ 且结束点一定为 $n$ 便发现了有蹊跷。

------------
- 题意：给定数组 $a$，可以在任意位置 $i$ 加上（或减去）一个首项为 $1$，公差为 $1$，长度为 $n-i+1$（即结束点为 $n$）的等差数列。问需要加（或减）几个等差数列可使 $a$ 中的值全为 $0$。 

此题正解应为：_二阶差分_。

观察到

| 等差数列 | 1 | 2 | 3 | 4 | 5 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 差分一次 | 1 | 1 | 1 | 1 | 1 |
| 差分两次 | 1 | 0 | 0 | 0 | 0 |

可得结论：在差分两次后的数组的 $i$ 位置上加 $1$，就等价于在原数组 $i$ 至 $n$ 上加上了一个首项为 $1$ 公差为 $1$ 的等差数列。 

所以，数组 $a$ 两次差分后所有数的绝对值的和，即为将原数列应加上等差数列的个数。

代码如下

```cpp
#include <iostream>
#include <cmath>
using namespace std;
long long n,a[200010],s[200010],s2[200010],ans;
//别忘了long long
int main(){
    cin>>n;
    for(int i = 1;i<=n;i++){
        cin>>a[i];
        s[i]=a[i]-a[i-1];
        s2[i]=s[i]-s[i-1];
        ans+=abs(s2[i]);
    }
    cout<<ans;
}

```



---

## 作者：__Cby___ (赞：12)

等差数列区间加，我们想到了什么？没错，差分！
## 解题思路
先把每块草地的初始细菌水平存在一个数组里，差分一下，问题就变成了数组上的区间加减 $1$，可以结合贪心的思路，每次从前往后把每一块草坪都变成具有健康草的推荐细菌值的草坪。  
正常看到区间加减的都会直接上线段树或树状数组。但本题中查询是有规律的，所以我们只要拿一个变量记录下接下来的草坪中的变化量，就可以啦！本代码时间复杂度为 $O(n)$。  
## 注意事项
要开 `long long`。   
## 建议事项
本题中差分一次与差分两次的代码时间复杂度相同，故**没必要**差分两次。
## 代码
```cpp
#include <iostream>
using namespace std;
long long int a[200025],cnt=0,al=0,n,m;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n;i>=1;i--)a[i]=a[i]-a[i-1];
	for(int i=1;i<=n;i++){
		cnt+=abs(a[i]+al);
		al=-a[i];
	}
	cout<<cnt<<endl;
	return 0;
}
```
是不是十分的简短？点个赞吧，谢谢！

---

## 作者：Super_Cube (赞：6)

upd on 2024.02.20: 修改了题解中的小错误。

# Solution

可以看出如果功率等级越小，那么从后往前覆盖到的区间就会越小。

贪心的想，从左往右开始扫一遍，如果当前草地不健康，那么就用刚好能覆盖到这个位置的功率来进行修改。这样前面已经健康的草地不会受到后面修改的影响。

于是乎每个位置需要喷雾器的次数为 $|a_i|$，然后对于 $\forall j \in [i+1,n],a_j\leftarrow a_j-(j-i+1)\cdot a_i$。这也就是在模拟使用喷雾器后对于当前位置后面的草地健康值的变化。

这样就得到了一份时间复杂度为 $O(n^2)$ 的算法，代码如下：

```cpp
for(int i=1;i<=n;++i){
	ans+=std::abs(a[i]);
	for(int j=i+1;j<=n;++j)
		a[j]-=a[i]*(j-i+1);
}
printf("%lld",ans);
```

下面来考虑如何优化。

把修改的式子像这样拆开：$a_j\leftarrow a_j-(j+1)\cdot a_i+i\cdot a_i$。

然后你会发现到 $j$ 这个位置的时候，前面所有的 $i$ 对它的影响都可以直接被计算出来，因为 $j+1$ 此时是定值，而 $a_i$ 与 $i\cdot a_i$ 可以分别用两个前缀和统计得到。

所以上面的代码成功被优化到了 $O(n)$。

# Code

```cpp
//用 s 维护 a[i] 的前缀和，S 维护 i*a[i] 的前缀和
for(int i=1;i<=n;++i){
	ans+=std::abs(a[i]-=s*(i+1)-S);
	s+=a[i];
	S+=a[i]*i;
}
printf("%lld",ans);
```

---

## 作者：Genius_Star (赞：6)

### 思路：

先将原序列转化为差分序列 $d$，即 $d_i = a_i - a_{i-1}$。

这样每次操作相当于选择一个 $x$，将 $d_{x \sim n}$ 都加上 $1$ 或者都减去 $1$，求使得 $d$ 序列为 $0$ 的最小步数。

考虑从左到右考虑，如果第 $d_i < 0$，则需要进行 $|d_i|$ 次加 $1$ 操作；否则需要 $d_i$ 次减 $1$ 操作；然后再维护一个全局加的标记 $sum$ 即可。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n;
ll a[N],d[N];
int main(){
	n=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	for(int i=1;i<=n;i++)
	  d[i]=a[i]-a[i-1];
	ll t1=0,t2=0,sum=0;
	for(int i=1;i<=n;i++){
		ll t=d[i]+sum;
		if(t<0){
			t1+=-t;
			sum+=-t;
		}
		else{
			t2+=t;
			sum-=t;
		}
	}
	write(t1+t2);
	return 0;
}
```


---

## 作者：sgl654321 (赞：3)

## 题目大意
- 现在你有一条一维的农场，长度为 $n$，$1\sim n$ 每片田地上，都存在一个细菌含量 $a_i$。

- 你位于最右边的田地上。你手上有两种农药，一种是加虫剂，一种是杀虫剂。你可以向左边喷洒农药。

- 每种农药都有一个功率 $L(1\le L\le n)$。如果是一个加虫剂，那么它会把第 $i$ 片田地 $(n-L+1\le i\le n)$ 的细菌含量加上 $L-(n-i)$。如果是一个杀虫剂，那么它会把第 $i$ 片田地 $(n-L+1\le i\le n)$ 的细菌含量减去 $L-(n-i)$。

- 每种功率的每种农药都有无限瓶。询问最少使用多少瓶农药，你能把所有田地的细菌含量都变为 $0$。

## 解题思路
首先考虑一个显然的事实：第 $1$ 处田地只能被 $L=n$ 的农药影响到，第 $2$ 处田地能被 $L=n$ 或 $n-1$ 的农药影响到，$\cdots$，第 $i$ 处田地能被 $L=n-i+1\sim n$ 的农药影响到。

因此我们可以考虑一个贪心的过程，从第 $1$ 处田地开始杀虫或者加虫，第 $1$ 处归零之后，再考虑第 $2$ 处，依次向右处理过来。

如果我们暴力的进行杀虫或者加虫的过程，那么时间复杂度是 $O(n^2)$ 的，喜提 10 个测试点。接着考虑优化。

可以发现，一次杀虫或者加虫，相当于区间加上或者减去一个**等差数列**。

对于这个题，我们可以把原序列 $a$ 进行一次差分，得到差分序列 $f$。

请读者思考一下，$a$ 的区间加减一个等差数列，相当于在差分序列的对应位置上进行什么操作呢？

事实上，对于一个数列 $a$，我们把 $[n-l+1,n]$ 加上一个 $1$ 为首项，公差为 $1$ 的递增等差数列，相当于把这个序列的差分数组 $f$ 的 $[n-l+1,n]$ 的每一项，加上 $1$。减去等差数列类似。

因此求出差分序列后，我们就可以直接进行线性的模拟了。我们需要记录下我们以前使用的农药，对当前这个农场的影响有多少，记录为 $now$。

我们用样例来举一个例子：

例如说样例 $2$，$a=\{1,3,-2,-7,5\}$，$f=\{1,2,-5,-5,12\}$。

- 对于 $f_1=1$，我们使用 $1$ 次 $L=5$ 的杀虫剂，$now=-1$。序列变成了 $\{0,1,-6,-6,11\}$。
- 对于 $f_2=2$，由于 $now=-1$，其实它已经变成 $1$ 了，因此用 $1$ 次 $L=4$ 的杀虫剂就行了。于是 $now=-2,f=\{0,0,-7,-7,10\}$。
- $f_3=-5,now=-2$，故 $f_3'=-7$，使用 $7$ 次 $L=3$ 的加虫剂，$now=5,f=\{0,0,0,0,17\}$。

- $f_4=-5,now=5$，故 $f_4'=0$，不必使用农药。

- $f_5=12,now=5$，故 $f_5'=17$，使用 $17$ 次 $L=1$ 的杀虫剂，完成了给定任务。

所以输出 $1+1+7+0+17=26$。

### 参考代码
这个 $save$ 就是上文所说的 $now$。

```cpp
#include<bits/stdc++.h>
#define maxn 200010
using namespace std;
typedef long long ll;
ll n,a[maxn],b[maxn],ans,save;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)b[i]=a[i]-a[i-1];
	for(int i=1;i<=n;i++){
		b[i]+=save;
		if(b[i]<0){
			save+=0-b[i];
			ans+=0-b[i];
		}else{
			save-=b[i];
			ans+=b[i];
		}
	}
	cout<<ans<<endl;
	return 0;
}
```




---

## 作者：Su777 (赞：3)

## 题意简述

有一个长度为 $n$ 的序列 $a$，每次可以选择一个数值 $L\ (1 \leq L \leq n)$，对应区间 $[n-L+1,n]$。对于任意 $i\ (0\leq i < L)$，将第 $N-i$ 个元素增加或减少 $L-i$。求将这个序列的所有元素都变为 $0$ 的最少操作次数。

## 解题思路

因为本题中唯一的修改方式是**修改后缀**，左边的元素会对右边有影响，从左到右依次处理。  
具体操作方式是，从 $a_1$ 开始处理。选择 $L=n$，根据 $a_1$ 的正负，执行增加或减少操作 $|a_1|$ 次。类似地，从 $a_1$ 一直处理到 $a_n$，总共的操作次数即为答案。

根据以上思路，写出以下暴力核心代码：
```cpp
int ans = 0;
for (int i = 1; i <= n; i ++) {
    for (int j = i + 1; j <= n; j ++) {
        arr[j] -= (j - i + 1) * arr[i];
    }
	ans += abs(arr[i]);
}
```

### 考虑优化

用 $b_i$ 来表示为了让 $a_i$ 变为 $0$ 的操作次数。如果是减少操作，就把 $b_i$ 设置为操作次数的相反数，方便计算。

我们发现，每一次操作都会对后续的所有元素产生影响。把所有的影响累加起来，可以得到 $a_i\ (2 \leq i \leq n)$ 受到的总影响为 $\sum \limits_{j=1}^{i-1} a_j(j-i+1)$。

在每次循环时记录该位置受到的影响值，然后记录这次操作值即可。因为计算影响值的时间复杂度是 $O(n)$，总体时间复杂度 $O(n^2)$。虽然没有比暴力算法更优，但是有了可优化空间。

### 正解

在暴力的基础上再加一点小优化即可。

为了方便计算，用 $s_i$ 表示第 $i$ 次操作受到前面操作的影响偏移量。$s_1$ 初始为 $0$（第一次操作不受任何影响）。显然，$b_i=a_i+s_i$。

这里以 $i=5$ 和 $i=6$ 的情况为例：
- $s_5=5b_1+4b_2+3b_3+2b_4$
- $s_6=6b_1+5b_2+4b_3+3b_4+2b_5$

可以看到，$s_6$ 在 $s_5$ 的基础上加了 $b_1+b_2+b_3+b_4+2b_5$，而这正好可以利用前缀和来进行 $O(1)$ 计算！在循环过程中动态维护即可。总体时间复杂度优化为 $O(n)$。

核心代码：
```cpp
ll a[N]; // 原始数组 a
ll b[N]; // 操作值数组 b
ll sumb[N]; // 操作值数组 b 的前缀和
ll s[N]; // 偏移量数组 s

for (int i = 1; i <= n; i ++) {
    if (i == 1) {
        // s[1] 初始为 0（最左端不受任何影响）
        s[i] = 0;
    } else {
        // 偏移量数组转移方程，可以参考上面例子理解
        // 注意后面要再加一个 b[i - 1]
        s[i] = s[i - 1] + sumb[i - 1] + b[i - 1];
    }
    b[i] = -1 * (a[i] + s[i]); // 计算本次操作值
    sumb[i] = sumb[i - 1] + b[i]; // 维护前缀和
}

ll ans = 0;
for (int i = 1; i <= n; i ++) {
    ans += abs(b[i]); // 操作值可能为负，取绝对值
}
cout << ans << endl;
```

---

## 作者：lilong (赞：3)

不难发现，越往左影响范围越大，因此考虑从左往右依次对每块田地进行操作（从右往左则已完成的会被再次影响）。设当前处理到第 $i$ 块田地，则为了不让前面的 $i-1$ 块田地受到影响，每次对第 $i$ 块田地的影响量只能为 $1$。因此可以很容易求得处理第 $i$ 块田地需要 $\left| a_i \right|$ 次操作，关键在于如何维护 $a_i$。

还是首先考虑暴力修改。对于每个 $i+1,\cdots, n$，分别计算出其影响量并修改。不难写出以下代码：

```cpp
for( int i = 1 ; i <= n ; i ++ )
{
	for( int j = i + 1 ; j <= n ; j ++ )
		a[j] -= a[i] * ( j - i + 1 );
	ans += abs( a[i] );
}
```

接下来考虑如何优化。已知位置 $i$，已知影响为 $1$，则容易得在 $n$ 放置了 $n - i + 1$ 的药物（$-1$ 的情况同理）。因此可以用两个变量统计在 $n$ 处放的药物总和，然后对于每个 $i$，一次计算出影响总量即可。

完整代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long

using namespace std;

int n,a[1000001],ans,tia,tib,ta,tb;

signed main()
{
	cin >> n;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i];
	for( int i = 1 ; i <= n ; i ++ )
	{
		a[i] = a[i] + ( tia - ( n - i ) * ta ) - ( tib - ( n - i ) * tb );
		if( a[i] < 0 )
			tia += ( n - i + 1 ) * ( -a[i] ),ta += ( -a[i] );
		else if( a[i] > 0 )
			tib += ( n - i + 1 ) * a[i],tb += a[i];
		ans += abs( a[i] );
//		cout << ans << endl;
	}
	cout << ans;
	return 0;
}

```


---

## 作者：Graph (赞：1)

由于前面的比较难被影响，因此策略是先复原前面再复原后面，那么假设处理第 $i$ 个位置，当前位置的健康程度为 $a_i$，那么相当于在 $i \sim n$ 加一个首项和公差均为为 $-a_i$ 的等差数列。

转化完之后，我立刻想到了 [P1438](https://www.luogu.com.cn/problem/P1438)，不就是区间加等差数列，单点查询吗？然后手打了一边差分套线段树过了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e5+5;
int tree[4*N],tag[4*N],a[N],diff[N],n,ans;

void pushup(int cur)
{
	tree[cur]=tree[2*cur]+tree[2*cur+1];
	return ;
}

void build(int cur,int lt,int rt)
{
	if(lt==rt)
	{
		tree[cur]=diff[lt];
		return ;
	}
	int mid=(lt+rt)>>1;
	build(2*cur,lt,mid);
	build(2*cur+1,mid+1,rt);
	pushup(cur);
	return ;
}

void addtag(int cur,int lt,int rt,int val)
{
	tag[cur]+=val;
	tree[cur]+=(rt-lt+1)*val;
	return ;
}

void pushdown(int cur,int lt,int rt)
{
	if(tag[cur]==0)
		return ;
	int mid=(lt+rt)>>1;
	addtag(2*cur,lt,mid,tag[cur]);
	addtag(2*cur+1,mid+1,rt,tag[cur]);
	tag[cur]=0;
	return ;
}

int query(int cur,int lt,int rt,int qx,int qy)
{
	if(qy<lt||rt<qx)
		return 0;
	if(qx<=lt&&rt<=qy)
		return tree[cur];
	pushdown(cur,lt,rt);
	int mid=(lt+rt)>>1;
	return query(2*cur,lt,mid,qx,qy)+query(2*cur+1,mid+1,rt,qx,qy);
}

void update(int cur,int lt,int rt,int qx,int qy,int val)
{
	if(qy<lt||rt<qx)
		return ;
	if(qx<=lt&&rt<=qy)
	{
		addtag(cur,lt,rt,val);
		return ;
	}
	pushdown(cur,lt,rt);
	int mid=(lt+rt)>>1;
	update(2*cur,lt,mid,qx,qy,val);
	update(2*cur+1,mid+1,rt,qx,qy,val);
	pushup(cur);
	return ;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		diff[i]=a[i]-a[i-1];
	}
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		int tmp=query(1,1,n,1,i);
		ans+=abs(tmp);
		update(1,1,n,i,i,-tmp);
		update(1,1,n,i+1,n,-tmp);
	}
	cout<<ans;
	return 0;
}
```

时间复杂度：$O(n \log n)$。

---

## 作者：M1saka16I72 (赞：1)

# P10133 [USACO24JAN] Balancing Bacteria B 题解

## 前言

[更可爱的阅读体验](http://misaka16172.github.io/solution-usaco-2024-jan.html)

update on 2024/2/11：修改了递推式中错误的求和公式。

## 题意

给定一个长度为 $N$ 的序列 $a$，可以进行如下操作：
- 选定一个值 $L$（$1\leq L\leq N$）
- 对序列进行两种修改之一，使得 $a_N\gets a_N+L,a_{N-1}\gets a_N+(L-1),\cdots,a_{N-L+1}\gets a_{N-L+1}+1$ 或 $a_N\gets a_N-L,a_{N-1}\gets a_N-(L-1),\cdots,a_{N-L+1}\gets a_{N-L+1}-1$。

求进行若干次操作，使得序列 $a$ 中的元素全部变为 $0$ 的最少次数。

## 思路

讲一种赛时想出的（比起三四行代码的差分）很复杂的递推思路。

想让序列全部归零，必须从第 $1$ 个元素开始修改，否则如果从第 $i$ 个元素进行修改，那后续再对 $[1,i)$ 之间的元素进行修改就会影响到 $i$ 的值。

所以我们的修改流程就是首先选定 $L=N$，进行 $|a_1|$ 次操作使 $a_1$ 归零，然后选定 $L=N-1$，进行 $|a_2|$ 次操作后使 $a_2$ 归零（**注意此时 $a_2$ 的值是已经被修改过的**），最后选定 $L=1$，进行 $a_N$ 次操作后序列就全部归零了。

现在的问题就是求出第 $i$ 次修改前 $a_i$ 的值是多少，设第 $i$ 次修改前 $a_i$ 的值是 $d_i$，操作次数总和即为 $\sum^{N}_{i=1}|d_i|$。

下面就是愉快的推式子环节。

## 递推方法

显然 $d_1=a_1$，因为第一个元素是第一个被修改的。

在进行完 $|d_1|$ 次 $L=N$ 的操作后，$a_1$ 的值变为 $0$，也就是减小了 $d_1$，则 $a_2$ 被修改为 $d_2-d_1\times 2=a_2-a_1\times 2$，$a_i$ 被修改为 $d_i-d_1\times i=a_i-a_1\times i$。

同理，在进行完 $|d_2|$ 次 $L=N-1$ 的操作后，$a_2$ 的值变为 $0$，也就是减小了 $d_2$，则 $a_3$ 被修改为 $d_3-d_2\times 2=a_3-d_1\times 3-d_2\times 2$，$a_i$ 被修改为 $d_i-d_2\times 2=a_i-a_1\times i-a_2\times i-1$。

于是在上面对过程的模拟后，我们可以得到如下公式：
>  $d_i=a_i-2\times a_{i-1}-3\times a_{i-2}-\cdots-i\times a_1$

但好像没有什么方法能直接算出这个式子的值，于是考虑用递推的方法去做，找一找 $d_i$ 和 $d_{i-1}$ 的关系：

将式子后一大段的值设为 $g_i$，即 $d_i=a_i+g_i$，则：
> $g_{i-1}=-2\times a_{i-2}-3\times a_{i-3}-\cdots-(i-1)\times a_{1}$

> $g_i=-2\times a_{i-1}+(-2\times a_{i-2}-3\times a_{i-3}-\cdots-(i-1)\times a_1)-\sum^{i-2}_{j=1}a_j$

> $=-2\times a_{i-1}+g_{i-1}-\sum^{i-2}_{j=1}a_j$

于是我们的递推关系就求出来了，至于后面的 $\sum^{i-2}_{j=1}a_j$ 用前缀和求出即可，初始状态为 $g_1=0$ 且 $d_1=a_i+g_1=a_1$。
### 代码
```cpp
const int N = 200005;
ll a[N],d[N],pf[N],g[N];	//pf代表前缀和数组
void solve(){
	int n;cin>>n;
	for(int i=1;i<=n;i++){cin>>a[i];}
	d[1] = a[1];g[1] = 0;pf[0] = 0;pf[1] = a[1];	//设置初始状态
	for(int i=2;i<=n;i++){
		g[i] = 2*d[i-1]+g[i-1]+pf[i-2];	//更新g[i]
		d[i] = a[i]-g[i];	//更新d[i]
		pf[i] = pf[i-1]+d[i];	//更新前缀和
	}
	ll sum = 0;
	for(int i=1;i<=n;i++){
		sum+=abs(d[i]);	//答案即为d[i]的绝对值之和
	}
	cout<<sum;
}

int main(){
	int t = 1;
//	read(t);
	for(int tt=1;tt<=t;tt++){
		solve();
	}
}
```

---

## 作者：NATO (赞：1)

考虑我们改 $\forall i<j$ 的 $a_i$ 必然会对 $a_j$ 产生影响，那么我们只能先改完 $\forall i<j$ 的 $a_i$ 才能确定 $a_j$ 的修改次数，那么我们从 $a_1$ 开始往后改即可，发现每次都是加上了一个等差数列，于是用线段树维护等差数列即可。

时间复杂度 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 214748364719260817ll
#define db double
using namespace std;
ll n,a[200005];
struct tree
{
	ll l,r,len,sum;
	ll d;
}tr[800005];
void pushdown(ll id)
{	
	ll sum=tr[id].sum,s2=tr[id].sum+tr[id*2].len*tr[id].d;
	tr[id*2].sum+=sum;tr[id*2].d+=tr[id].d;
	tr[id*2+1].sum+=s2;tr[id*2+1].d+=tr[id].d;
	tr[id].d=tr[id].sum=0;
}
void update(ll id,ll l,ll r,ll k,ll d)
{
	if(l<=tr[id].l&&tr[id].r<=r)
	{
		tr[id].sum+=(tr[id].l-l)*d+k;
		tr[id].d+=d;
		return;
	}
	pushdown(id);
	ll mid=tr[id].l+tr[id].r>>1;
	if(l<=mid)
		update(id*2,l,r,k,d);
	if(mid<r)
		update(1+id*2,l,r,k,d);
}
ll query(ll id,ll p)
{
	if(tr[id].l==tr[id].r)return tr[id].sum;
	pushdown(id);
	if(p<=tr[id*2].r)
		return query(id*2,p);
	else
		return query(id*2+1,p);
}
void build(ll id,ll l,ll r)
{
	tr[id].l=l;
	tr[id].r=r;
	tr[id].len=r-l+1;
	if(l==r)
	{
		tr[id].sum=tr[id].d=a[l];
		return;
	}
	ll mid=tr[id].l+tr[id].r>>1;
	build(id*2,l,mid);
	build(id*2+1,mid+1,r);
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(ll i=1;i<=n;++i)cin>>a[i];
	build(1,1,n);
	ll res=0;
	for(ll i=1;i<=n;++i)
	{
		ll now=query(1,i);
		if(now==0)continue;
		res+=abs(now);
		update(1,i,n,-now,-now);
	}
	cout<<res;
}
```

---

## 作者：yyrwlj (赞：0)

## 思路

首先发现操作的先后次序是无所谓的，那么我们就可以从左往右修复，修复了之后就不要再喷它了。

那么每次操作必须保证喷到当前草地时，恰好只会去除 $1$ 或 $-1$ 单位的细菌，然后操作当前草地的当前细菌水平的绝对值次。

我们发现这对于从当前草地到第 $n$ 个草地到影响是一个等差数列，然后每次看当前草地的细菌水平是一个单点查询。

那么我们可以用一个支持区间加等差数列，单点查询的线段树，发现这是[原](https://www.luogu.com.cn/problem/P1438)，让原序列转成差分序列后，就方便用区间和线段树维护了。

## Code

```cpp
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 200005;
LL a[N], w[N << 2], tag[N << 2];
int n;
inline void pushup(int u)
{
 	w[u] = w[u << 1] + w[u << 1 | 1];
}
void build(int u,int l,int r)
{
	if (l == r)
	{
		w[u] = a[l];
		return;
	}
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}
inline void pushdown(int u,int l,int r,int mid)
{
    tag[u << 1] += tag[u];
    tag[u << 1 | 1] += tag[u];
    w[u << 1] += tag[u] * (mid - l + 1);
    w[u << 1 | 1] += tag[u] * (r - mid);
    tag[u] = 0;
}
void update(int u,int l,int r,int L,int R,LL x)
{
    if (L <= l && r <= R)
    {
    	tag[u] += x;
    	w[u] += (r - l + 1) * x;
    	return;
    }
    int mid = (l + r) >> 1;
    if (tag[u])
    	pushdown(u, l, r, mid);
    if (L <= mid)
    	update(u << 1, l, mid, L, R, x);
    if (mid < R)
    	update(u << 1 | 1, mid + 1, r, L, R, x);
    pushup(u);
}
LL query(int u,int l,int r,int L,int R)
{
    if (L <= l && r <= R)
        return w[u];
    int mid = (l + r) >> 1, res = 0;
    if (tag[u])
    	pushdown(u, l, r, mid);
    if (L <= mid)
    	res += query(u << 1, l, mid, L, R);
    if (mid < R)
    	res += query(u << 1 | 1, mid + 1, r, L, R);
    return res;
}
inline void change(int l,int r,int k,int d)
{
	update(1, 1, n, l, l, k);
    if (l < r)
    	update(1, 1, n, l + 1, r, d);
}
inline LL ask(int p)
{
	return query(1, 1, n, 1, p);
}
int main()
{
    scanf("%d", &n);
    for(int i=1;i<=n;i++)
        scanf("%lld", &a[i]);
    for(int i=n-1;i;i--)
        a[i + 1] -= a[i];
    build(1, 1, n);
    LL ans = 0;
	for (int i=1;i<=n;i++)
	{
		const LL ai = ask(i);
		if (ai < 0)
			ans -= ai;
		else
			ans += ai;
		change(i + 1, n, (-ai) * 2, -ai);
	}
	printf("%lld", ans);
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

做两次差分后会发现这个操作变成了单点加减，因为（假设进行了一次功率为 $x$ 的操作）（后面括号内的数表示位置）：

$+0(n-x),+1(n-x+1),+2(n-x+2),+3(n-x+3),\cdots+x(n)$

一次差分后：

$+0(n-x),+1(n-x+1),+1(n-x+2),\cdots +1(n)$

两次差分后：

$+0(n-x),+1(n-x+1),+0(n-x+2),\cdots +0(n)$

设 $b_i$ 为做了两次差分的 $a_i$，只用计算 $\sum\limits_{i=1}^{n}|b_i|$ 即可。

---

## 作者：indream (赞：0)

## P10133 [USACO24JAN] Balancing Bacteria B 题解
[USACO](http://usaco.org/index.php?page=viewproblem2&cpid=1373) | [P10133](https://www.luogu.com.cn/problem/P10133)

### 思路
显然药水的先后次序不重要。

有一个贪心：每次把离 $n$ 最远的非零土地处理为零，直到所有土地均为零。

感性理解：考虑第一次，若要把其变为零，有且只有一种方法，如果将其归零后再进行操作即为重复，其余土地同理。故从远到近依次设零。


这种方法是 $O(n^2)$ 的。考虑优化。

开始乱搞：

~~好吧一个星期后我也不太懂了~~

解释一下，设 $sum1_i$ 记录将第 $i$ 片土地调零时的代价和，即目前为止每次将最远的土地调零时在最远的土地上付出的代价和，$sum2_i$ 指截止此时其它土地的附加代价和。

显然，第 $i$ 次操作，第 $i$ 片土地会为零，此前 $a_i=a_i+sum1_{i-1}+sum2_{i-1}$。而此时使其为零需 $|a_i|$ 次。

在本次操作后，下次操作前，$sum1_i=sum1_{i-1}-a_i$，$sum2_i=sum1_{i}+sum2_{i-1}$。

至于如何理解本做法，请参照代码最后的样例二的该版本样例解释！作者认为那部分会更易懂些。
### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define MAXN 200005
using namespace std;
typedef long long ll;
ll a[MAXN],ans,n,tmp;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%lld",&a[i]);
    ll sum1=0,sum2=0;
    for(int i=1;i<=n;++i){
        a[i]+=sum1+sum2;
        ans+=abs(a[i]);
        
        sum1+=-1*a[i];
        sum2+=sum1;
        
        //cerr<<a[i]<<' '<<sum1<<' '<<sum2<<' '<<lsum1<<' '<<lsum2<<'\n';
    }
    cout<<ans;
    return 0;
}
/*
1  3  -2 -7  5
0  1  -5 -11 0    1  -0                 (+0=1) sum1=0(0)    sum2=0
0  0  -7 -14 -4   3  -2*1               (-2=1) sum1+=-1(-1) sum2=-1*1             =-1
0  0  0  0   17   -2 -3*1-2*1          (-5=-7) sum1+=-1(-2) sum2=-1*2-1*1         =-3
0  0  0  0   17   -7 -4*1-3*1+2*7       (+7=0) sum1+=7(5)   sum2=-1*3-1*2+7*1     =2
0  0  0  0   0    5  -5*1-4*1+3*7+2*0 (+12=17) sum1+=0(5)   sum2=-1*4-1*3+7*2+0*1 =7
*/
//样例2 O(n)解释：
//第一个5*6的矩阵是变化过程，第一行是初值
//第二列是每个在此时设零的数的初值
//第三列是该数此前遭到的变化（暴力做法）
//第四列括号里表示变化总值和设零前的值
//第五列是sum1的变化情况，即上次设零对sum1的影响，括号里是当前值
//第六列是sum2的变化情况，即本次主代价和+上次附加代价，最后是当前sum2的值
//一语道破：注意sum1展开式与sum2展开式每项提取公因数即为第三列中的变化！
//原因：每往后一次会使累计代价每项系数加一并加上新的一次代价，即sum2+=sum1
```


---

## 作者：Guizy (赞：0)

对于一块田，如果要对它进行操作，必然会影响到它右边的田。不难发现操作顺序的调换是对答案没有影响的。所以考虑从左到右一个一个处理。

但是，我们发现，如果要修改，时间复杂度是 $\mathcal{O}(len)$ 的，所以考虑优化修改。

众所周知，等差数列是可以叠加的，所以我们维护一个末项，一个公差即可 $\mathcal{O}(1)$ 修改与查询。

具体可以看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int Max=200001;
int n,a[Max],ans,an,p;

int main(){
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	
	an=p=0;int ai;
   //ai 当前项，an 末项，p 公差
	for(int i=1;i<=n;i++){
		ai=a[i]+(an-(n-i)*p);
		ans+=abs(ai);
		p-=ai;
		an-=ai*(n-i+1);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：0)

本题显然是从左往右依次把最左边的地调整到正常状态。

每次最左边的地用的药物效果一定为 $1$，否则会继续往左传递，左边的地会被破坏。所以每一块地要用 $a_i$ 次药水（这里的 $a_i$ 指加上前面的地产生的贡献后当前地的细菌值）。

具体实现见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[200005],ans,ngx,tot;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		ngx+=tot;//tot 是前面所有地产生的药水贡献和
		a[i]+=ngx;//前面的地对当前地的贡献
		ans+=abs(a[i]);//要用的药水次数
		tot-=a[i];//因为如果当前值为负，要用正的药水，否则用负的药水，所以要加上 -a[i]
		ngx-=a[i];//下一块地效果为 2，再加一次
	}
	cout<<ans;
}

```

---

## 作者：apiad (赞：0)

因为对于 $i$ 进行操作，肯定会影响到后面的数，因此得先改前面的数再改后面的数，为了线性，不妨对 $a$ 数组进行差分。

我们实时维护两个变量。

$sum$ 数组是此时进行完操作后，之后会有多少增加细菌的个数。

然而 $ans$ 维护的是答案，每一次会加上 $d_i + sum$ 的绝对值。$d_i$ 是差分数组。

时间复杂度 $O(n)$。

```cpp
#define int long long
int n,a[N];
int d[N];
int sum;
int ans;
void solve(){
	cin >> n;for(int i = 1;i <= n;i++){cin >> a[i];d[i]=a[i]-a[i-1];}
	for(int i = 1;i <= n;i++){
		ans += abs(d[i]+sum);
		sum = sum-(d[i]+sum);
	}cout<<ans;		
}

```

---

## 作者：WA_WonderfulAnswer (赞：0)

考试时直接 AK 了，来水一篇题解。

## 思路
因为农夫只能站在草地最右侧使用喷雾，所以要先从最左侧开始调整。先用 $n$ 的功率喷，直到最左侧的草坪为 $0$。以此类推，从左往右调整。

为什么要从左往右调整？如果先把右侧的草喷成 $0$，那在开大功率时刚刚喷好的草坪也会被修改。

***

### 举例

输入:
```c
3
1 -2 3
```

#### 模拟

1. 用减少细菌的喷雾，功率 $3$，喷 $1$ 下。变成:

```c
0 -4 0
```

2. 用增加细菌的喷雾，功率 $2$，喷 $4$ 下。变成：

```c
0 0 8
```

3. 用减少细菌的喷雾，功率 $1$，喷 $8$ 下。变成：

```c
0 0 0
```

***

### 结论
应输出：$13$。

程序输出：$13$。

结果：正确。
## AC Code
```c
#include <stdio.h>
#include <math.h>
#define N 200005
long long n, a[N], ans, len, dis;

int main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++)
		ans += abs(a[i] + dis + len), dis -= a[i] + dis + len, len += dis;
	printf("%lld", ans);
	return 0;
}
```

## AC 记录
![AC](https://cdn.luogu.com.cn/upload/image_hosting/pvgl1afl.png)

[洛谷记录](https://www.luogu.com.cn/record/146525309)

---

## 作者：Crazyouth (赞：0)

## 分析

不难想到，最优方案一定是从左往右依次把每一片田地变成 $0$。而且每一次喷洒完成后，$\Delta a_i$ 比 $\Delta a_{i+1}$ 少（多）的部分刚好是喷洒次数，所以可以统计喷洒次数并 $O(1)$ 求得当前的田地细菌数量，最后把加农药和减农药数量加起来即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200010];
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int add=0,sub=0;
	for(int i=1;i<=n;i++)
	{
		int now=-a[i-1]-sub+add+a[i];
		if(now>0)
		{
			sub+=now;
		}
		else if(now<0)
		{
			add+=-now;
		}
	}
	cout<<add+sub;
	return 0;
}

---

