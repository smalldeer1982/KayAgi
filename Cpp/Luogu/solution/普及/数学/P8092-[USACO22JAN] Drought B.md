# [USACO22JAN] Drought B

## 题目描述

Farmer John 的草地里的草在一场大旱中都干死了。经过数小时的绝望和沉思，Farmer John 想到了一个绝妙的主意，购买玉米来喂养他宝贵的奶牛。

FJ 的 $N$ 头奶牛（$1 \leq N \leq 10^5$）排成一行，队伍中的第 $i$ 头奶牛的饥饿度为 $h_i$（$0 \leq h_i \leq 10^9$）。由于奶牛是社会性动物，她们坚持一起进食，FJ 降低奶牛饥饿度的唯一方法是选择两头相邻的奶牛 $i$ 和 $i+1$ 并分别喂她们一袋玉米，令她们的饥饿度各减少 1。

FJ 想将他的奶牛喂至所有的奶牛都具有相同的非负饥饿度。请帮助 FJ 求出他喂奶牛达到上述状态所需的最少玉米袋数，或者如果不可能达到，输出 $-1$。

## 说明/提示

【样例解释】

对于第一个子测试用例，给奶牛 $2$ 和 $3$ 各两袋玉米，然后给奶牛 $1$ 和 $2$ 各五袋玉米，可以使得所有奶牛的饥饿度均为 $3$。

对于第二个子测试用例，给奶牛 $1$ 和 $2$ 各两袋玉米，奶牛 $2$ 和 $3$ 各两袋玉米，奶牛 $4$ 和 $5$ 各两袋玉米，奶牛 $5$ 和 $6$ 各两袋玉米，可以使得所有奶牛的饥饿度均为 $2$。

对于余下的子测试用例，均不可能使得奶牛们的饥饿度相等。

【数据范围】

- 测试点 2 的所有子测试用例满足 $N \leq 3$ 以及 $h_i\le 100$。

- 测试点 3-8 的所有子测试用例满足 $N\le 100$ 以及 $h_i\le 100$。

- 测试点 9-14 的所有子测试用例满足 $N\le 100$。

- 测试点 15 没有额外限制。

- 此外，测试点 3-5 和 9-11 中的 $N$ 均为偶数，测试点 6-8 和 12-14 中的 $N$ 均为奇数。

## 样例 #1

### 输入

```
5
3
8 10 5
6
4 6 4 4 6 4
3
0 1 0
2
1 2
3
10 9 9```

### 输出

```
14
16
-1
-1
-1```

# 题解

## 作者：Nevergonna_CCF (赞：16)

### P8092 [USACO22JAN] Drought B
该题是USACO1月铜组T3，蒟蒻在最后三分钟AC了这道题，不得不说，该题~~思维难度较大~~还是很简单的。

首先我们观察一下样例的第二个序列：
`4 6 4 4 6 4`

很明显，我们要尽可能的让这个序列所有值相差最少，就要让最大的降低，和他周围的尽量保持一致。

#### 具体步骤
首先我们从下标为1的元素开始正序判断这个序列——如果当前 $h_{i}$ 大于 $h_{i+1}$ 或 $h_{i-1}$ ,判断 $h_{i+1}$ 和 $h_{i-1}$ 谁大。如果 $h_{i+1}$ 大，则将 $h_{i}$ 和 $h_{i-1}$ 自减到 $h_{i} = h_{i+1}$，反之亦然。

经过上面的步骤，我们肯定能得到一个单调递增的序列，我们在反序一次就行了，最后输出减了多少次。

#### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;

int n;
int a[MAXN];
unsigned long long ans = 0;

void func()
{
    memset(a, 0x3f3f3f3f, sizeof(a));
    ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    if (n == 2)
    {
        cout << (a[1] == a[2] ? 0 : -1) << endl;
        return;
    }
    for (int i = 2; i < n; i++)
    {
        if (a[i] > a[i+1])
        {
            int t = a[i] - a[i+1];
            a[i-1] -= t;
            a[i] -= t;
            ans += t * 2;
        }
        if (a[i] > a[i-1])
        {
            int t = a[i] - a[i-1];
            a[i+1] -= t;
            a[i] -= t;
            ans += t * 2;
        }
    }
    for (int i = n - 1; i >= 2; i--)
    {
        if (a[i]>a[i+1])
        {
            int t = a[i] - a[i+1];
            a[i-1] -= t;
            a[i] -= t;
            ans += t * 2;
        }
        if (a[i] > a[i-1])
        {
            int t = a[i] - a[i-1];
            a[i+1] -= t;
            a[i] -= t;
            ans += t * 2;
        }
    }
    for (int i = 1; i < n; i++)
    {
        if (a[i] != a[i + 1] || a[i] < 0)
        {
            cout << -1 << endl;
            return;
        }
    }
    cout << ans << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        func();
    }
    return 0;
}

```

---

## 作者：lsj2009 (赞：12)

[也许并不会有更好的阅读体验。](https://www.luogu.com.cn/blog/lvsiji/solution-p8092)
## 题目大意
<https://www.luogu.com.cn/problem/P8092>。
## 思路
~~这真是道黄题?(超小声。~~

看一眼数据范围：$n\le 10^5,h_i\le 10^9$，这不是 $O(n)$ 就是 $O(n\log{n})$ 了。

容易发现，当 $2 \mid n$ 时，答案满足单调性；但 $n$ 为奇数就不一定了。

我们考虑 $O(n)$ 解。

可以看出，如果第 $i$ 个位置的奶牛饥饿度减少，那么它一定是与 $i-1$ 或 $i+1$ 号奶牛一起进食的。我们设 $f_i$ 为第 $i$ 号奶牛与第 $f_{i+1}$ 号奶牛一起进食的数量（不是 $i$ 和 $i+1$ 进食的总数），又设 $x$ 为奶牛们最后保持的饥饿度，那么
$$x=h_i-f_{i-1}-f{i}$$
（$f_0=f_n=0$）
$$f_i=h_i-f_{i-1}-x$$
$$f_1=h_1-x$$
$$f_2=h_2-f_1-x=h_2-h_1+x-x=h_2-h_1$$
$$f_3=h_3-f_2-x=h_3-h_2+h_1-x$$
$$......$$
$$f_{n-1}=h_{n-1}-f_{n-2}=...$$
$$f_n=h_n-f_{n-1}=...$$
将他们列出来：
$$f_1=h_1-x$$
$$f_2=h_2-h_1$$
$$f_3=h_3-h_2+h_1-x$$
发现规律：
$$f_n=\begin{cases}\sum\limits_{i=1}^n=\begin{cases}+h_i\quad2\nmid i\\-h_i\quad2\mid i\end{cases}-x\qquad2\nmid n\\\sum\limits_{i=1}^n=\begin{cases}-h_i\quad2\nmid i\\+h_i\quad2\mid i\end{cases}\qquad2\mid n\end{cases}$$
同时，
$$h_n-f_{n-1}-x=0$$
$$\begin{cases}x=+h_1-h_2+h_3-...+h_{n-2}-h_{n-1}+h_n\qquad2\nmid n\\0=-h_1+h_2-h_3+...+h_{n-2}-h_{n-1}+h_n\qquad2\mid n\end{cases}$$
通过上述方程，我们可以直接计算出 $n$ 为奇数的 $x$，然后计算出答案（若 $x$ 为负，则答案为 $-1$）。
```cpp
if(n&1) {
	int x=0,ans=0;
	for(int i=1;i<=n;i++) //根据公式计算 x
		x+=(i&1? 1:-1)*h[i];
	if(x<0) return -1; //x 为负
	for(int i=1;i<n;i++) {
		f[i]=h[i]-f[i]-x; ans+=f[i]; if(f[i]<0) return -1; //计算 f[i] 并累加，同时 f[i] 必须大于等于 0，否则无解
	}
	return ans<<1; //由于 f[i] 为“第 i 头和 i+1 头的进食量”，所以需*2
} 
```

而当 $n$ 为偶数时，我们并不能计算出 $x$，但如果上式答案不为 $0$，则不能完成任务，答案为 $-1$。
```cpp
int x=0;
for(int i=1;i<=n;i++)
	x+=(i&1? -1:1)*h[i];
if(x) return -1;
```
可以看出，如果我们确定 $x$，那么只有 $f_1,f_3,...,f_{n-1}$ 会受到影响，而 $f_i$ 不能为负（必须喂至少奶牛 $0$ 袋玉米，而每喂一袋，饥饿度必 $-1$），那么我们只能设定 $x$ 为当前的 $\min\limits_{1\le i\le n,2 \nmid i}(f_i)$，当前 $f_i$ 为 $h_i-f_{i-1}$。
```cpp
int ans=0,m=INF;
for(int i=1;i<n;i++) {
	f[i]=h[i]-f[i]; if(f[i]<0) return -1;
}
for(int i=1;i<n;i++) m=min(f[i],m);
for(int i=1;i<n;i++) ans+=f[i]-m;
return ans<<1;
```
最后留一句话：十年 OI 一场空，不开 ``long long`` 见祖宗。

完美撒花！

---

## 作者：ztlh (赞：9)

**第一次参加这玩意儿，就是这道题害我卡了好久，差点没 AK 。。**

对于这道题，我们首先应该知道：令原数组最小值为 $h_{min}$，则最后的所有 $h_i \leq h_{min}$。

因此可以得到：

- 若 $h_i < h_{i+1} (2 \leq i < n)$，则 $h_{i+1}$ 与 $h_{i+2}$ 必然同减 $(h_{i+1} - h_i)$。

- 同理，若 $h_i < h_{i-1} (2 \leq i < n)$，则 $h_{i-1}$ 与 $h_{i-2}$ 必然同减 $(h_{i-1} - h_i)$。

于是，对于每一组数据，我们可以用一个 **while** 循环，**正反各扫一遍**，每次按照上面步骤进行操作，直到某一次正扫（或反扫）**没有进行任何操作**（表示数组中**所有元素相等**），或是某个元素 $h_i < 0$ (表示**没有合法方案**),退出循环。

重点来了：

- 一定要开 **long long** ,不然会 **WA** ！

- 一定要优化，不然会 **TLE** （特别是12~14点）！

------------
## AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T;
ll n;
ll sum,minn;
ll h[100005];
int flag;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        sum=0;minn=1e16L;
        for(ll i=1;i<=n;i++){
            scanf("%lld",&h[i]);
            sum+=h[i]; minn=min(minn,h[i]);
        }
        if(n==1) {printf("0\n");continue;} //特判
        if(n==2){
            if(h[1]==h[2]) printf("0\n");
            else printf("-1\n");
            continue;
        }
        if((sum-minn*n)%2==1&&n%2==0) {printf("-1\n");continue;} //小优化：奇偶性
        if(h[1]>h[2]||h[n]>h[n-1]) {printf("-1\n");continue;} //小优化：边界判断
        flag=1;
        while(flag==1){
            flag=0;
            for(int i=2;i<n;i++) //正扫
                if(h[i]>h[i-1]){
                    flag=1;
                    int d=h[i]-h[i-1];
                    h[i]-=d;
                    h[i+1]-=d;
                    if(h[i]<0||h[i+1]<0) {flag=-1;break;} //这个不加就会卡在12~14点
                }
            if(flag!=1) break; //同上
            for(int i=n-1;i>1;i--) //反扫
                if(h[i]>h[i+1]){
                    flag=1;
                    int d=h[i]-h[i+1];
                    h[i]-=d;
                    h[i-1]-=d;
                    if(h[i]<0||h[i-1]<0) {flag=-1;break;} //同上
                }
        }
        if(flag==-1) printf("-1\n");
        else printf("%lld\n",sum-h[1]*n);
    }
    return 0;
}
```

---

## 作者：fz20181223 (赞：6)

这题可以证明答案的单调性。

很明显，令我们当前使每个奶牛的饥饿值降至 $x$（保证降至 $x$ 是可行的），易证：我们可以将每个奶牛的饥饿值降至 $[1,x]$ 之间的任意数，只需对于每个投喂操作加上对应数量的玉米袋即可（例如我当前设定将所有奶牛饥饿值设为 $6$，每头奶牛分别需要投喂 $a_1,a_2,a_3,\cdots,a_N$，如果我将所有奶牛饥饿值改为 $4$，则只需将每头奶牛投喂的数量改为$a_1+2,a_2+2,a_3+2,\cdots,a_N+2$）。

故该题可以通过二分最大饥饿值求解。

由于二分左边界为 $0$，我们为了区分边界是因为二分结果是 $0$ 还是无解，我们可以将初始时左边界设为 $-1$ 以与找到答案区分。检查时我们可以从第一头奶牛开始模拟，看看它能不能降至当前设定的饥饿值，并且逐次向后推，若遇到当前奶牛的饥饿值因为为了满足上一只奶牛而饥饿值降为负数，则说明当前预设是不行的。

值得注意的是我们可能需要一些特判，比如：当奶牛数大于 $1$ 时，第一头奶牛的饥饿值不得大于第二头的饥饿值，且倒数第一头奶牛的饥饿值不得大于倒数第二头的饥饿值。同时，在不满足上述条件且奶牛数不足 $3$，则答案必为 $0$（因为不需做任何修改，所有奶牛饥饿值必然一样）。

赛时源代码（有删改）：
```cpp
#include<bits/stdc++.h>
#define mset(a,x) memset(a,x,sizeof(a))
using namespace std;
const int N=1e5+9;
int n,a[N],b[N];
bool check(int x){
	memcpy(b,a,sizeof(a));
	for(int i=1;i<n;++i){
		if(b[i]<x) return 0;
		b[i+1]-=(b[i]-x);
	}
	return b[n]>=x;
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",a+i);
	if(n>1&&(a[1]>a[2]||a[n-1]<a[n])){
		puts("-1");
		return;
	}
	if(n<3){
		puts("0");
		return;
	}
	int l=-1,r=1e9+7;
	for(int i=1;i<=n;++i) r=min(r,a[i]);
	int tmp=r;
	while(l<r){
		int mid=(l+r+1)>>1;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	if(l>tmp||l<0){
		puts("-1");
		return;
	}
	ll ans=0;
	for(int i=1;i<=n;++i) ans+=(a[i]-l);
	printf("%lld\n",ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--)solve();
	return 0;}

```

---

## 作者：untrigintillion (赞：4)

## 思路：

考虑数组 $\{x_n\}$ 即奶牛的饥饿值，及差分数组 $\{c_{n-1}\}$, 其中 $c_i=x_{i+1}-x_{i}$。

显然，在**大多数情况**下，$x_i,x_{i+1}$ 同时减 1， 意味着 $c_{i-1}$ 减去 1，$c_{i+1}$ 加上 1.

于是，我们就从 $c_0$ 开始，轮流将 $c_i$ 减 1，将 $c_{i+2}$ 加 1，直到 $c_i=0$ 为止。如果中间出现小于0的情况，说明无解。

然而，我们需要考虑一下它们的实际意义：

当我们将 $c_0$ 减 1 时，实际上 $x_1$ 与 $x_2$ 减去了 1.

**这就意味着，我们没考虑** $x_0$ **与** $x_1$ **同时减1的情况！**

当 $x_0$ 与 $x_1$ 同时减1时，仅 $c_1$ 加上了 1. 同理，当 $x_{n-2}$ 与 $x_{n-1}$ 同时减 1 时，仅 $c_{n-3}$ 减去了 1.

那么，当 $x_i <0$ 时，我们就可以试着用 $c_1$ 把它补回 0，接着把 $c_1$ 再补回 0.

将这问题解决后，代码看起来没啥问题，但是却被下面一组数据卡掉了：

```
3
1 4 1
```

在苦思冥想之后，我们发现，**没有考虑能够达到相等，但是结果小于 0 的情况！**

于是，我们在代码中用 `x[0]` 去存储最后的相同的数，当可以“补回”时，就在 `x[0]` 中扣除相应的值。

## 代码

下面的代码中，行末的 `//` 代表最后添加的对 `x[0]` 的修改操作。

```cpp
//AC #1...15
#include <bits/stdc++.h>
using namespace std;
long long T,n,x[50050],ans,k;
long long cfsz[50050];
int main(){
	cin>>T;
	while(T--){
		ans=0;
		cin>>n;
		for(int i=0;i<n;i++)cin>>x[i];
		for(int i=0;i<n-1;i++)cfsz[i]=x[i+1]-x[i];
		if(n==1)cout<<0<<endl;
		else if(n==2)cout<<(cfsz[0]==0?0:-1)<<endl;
		else{
			for(int i=0;i<n-3;i++){
				if(cfsz[i]<0){
					if(i%2==1){
						x[0]+=cfsz[i];//
						ans-=cfsz[i]*(i+1)/2;
						cfsz[i]=0;
						if(x[0]<0)break;//
					}
					else{
						ans=-1;
						break;
					}
				}
				else{
					ans+=cfsz[i];
					cfsz[i+2]+=cfsz[i];
					cfsz[i]=0;
				}
			}
			if(ans!=-1){
				if(n%2==0){
					if(cfsz[n-2]!=0)ans=-1;
					else if(cfsz[n-3]>0)ans+=cfsz[n-3];
					else{
						ans-=cfsz[n-3]*(n-2)/2;
						x[0]+=cfsz[n-3];//
					}
				}
				else{
					if(cfsz[n-3]<0)ans=-1;
					else ans+=cfsz[n-3];
					if(ans!=-1){
						if(cfsz[n-2]>0)ans=-1;
						else{
							ans-=cfsz[n-2]*(n-1)/2;
							x[0]+=cfsz[n-2];//
						}
					}
				}
			}
			if((ans==-1)||(x[0]<0))cout<<"-1\n";
			else cout<<ans*2<<endl;
		}
	}
	return 0;
}
```

### 本蒟蒻写的第 `3` 篇题解

---

## 作者：CANTORSORT (赞：3)

~~**FJ（和他的奶牛）可真惨……**~~

为了获得快速的解决方案，

我们可以在数组 $h$ 上 **从左向右移动**，

对 $(h_i,h_{i+1})$ 操作，使得 $h_i=h_{i-1}$，

完成这些操作以后，

我们发现了一条性质：

**对于所有 $1\le i\le N$，执行操作前满足 $h_i>h_{i-1}$**。

遍历数组后，
要么，$h_N>h_{N-1}$（在这种情况下无解）；
要么，对于所有 $2\le i\le N，h_i\le h_{i-1}$，$h_i$ 将不增加。

在后一种情况下，让我们反转数组 $h$。

再按照上述过程执行操作之后，$h_1\sim h_{N-1}$，都将相等，如果 $h_N>h_{N-1}$，则无解；
否则，$h$ 的所有元素是否相等，还需要验证这些元素是否为非负数。

该解决方案需要 $O(N)$ 级别的时间复杂度。

**上代码！**
## Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define isdight(c) (c>='0'&&c<='9')
#define swap(a,b) a^=b^=a^=b
using namespace std;
int t,n,h[100005];
inline int read() //快读
{
	int x=0,f=1;
	char c=getchar();
	while(!isdight(c))
		f=(c^'-'?1:-1),c=getchar();
	while(isdight(c))
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x*f;
}
int solve()
{
	int ans=0;
	if(n<2)
		return 0; //无需改变
	for(int j=1;j<3;j++) //正序变化与倒序变化
	{
		for(int i=2;i<n;i++)
		{
			if(h[i]>h[i-1])
			{
				int differ=h[i]-h[i-1];
				ans+=differ<<1; //每次喂两袋
				h[i+1]-=differ;
				h[i]=h[i-1]; //同时变化
			}
		}
		if(h[n]>h[n-1])
			return -1; //无解
		reverse(h+1,h+1+n); //反转
	}
	return h[1]<0?-1:ans;
}
signed main()
{
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;i++)
			h[i]=read();
		printf("%lld\n",solve());
	}
	return 0;
}
```

---

## 作者：RootMirzayanov (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P8092)

## 题意

给定一个长度为 $N$ 的数列 $\{h_n\}$, 定义一次操作为选取一个数 $i$, 使 $h_i,h_{i+1}$ 的值减少 $1$, 求出使数列 $\{h_n\}$ 的每项相等且为非负数的最小操作数的**二倍**，否则输出 $-1$。

## 解析

我们可以对于所有的 $2\le i\le n-1$ 进行判断，如果 $h_i<h_{i+1}$，则我们对 $h_{i+1},h_{i+2}$ 进行 $h_{i+1}-h_i$ 次操作（按照如上逻辑进行的操作定义为操作 $1$）；同理如果 $h_i<h_{i-1}$，则我们对 $h_{i-1},h_{i-2}$ 进行 $h_{i-1}-h_i$ 次操作（按照如上逻辑进行的操作定义为操作 $2$）。

按照这样的思路，我们可以首先按照 $1\sim (n-2)$ 的顺序进行 $n-2$ 次操作 $1$，然后按照 $n\sim 3$ 的顺序进行 $n-2$ 次操作 $2$，如此往复直到出现任意的 $h_i<0$ 或某次顺序操作判断都不成立时不再进行任何操作。前者因为已经在进行了最小次操作仍然不符合约束，则不存在合法解。后者因为已经遍历的所有可能的不相等情况，则说明在所有数非负的情况下相等，即存在合法解。

我们可以将每次的操作数累加在一个 `ans` 变量上，如果存在合法解要输出**二倍**的 `ans`(因为是一次操作耗费两袋玉米)，否则输出 $-1$，平均时间复杂度为 $\Theta(n\log n)$，所以我们可以考虑在每次判断时再次加上是否非负的判断进行优化避免 `TLE`。

---

## 作者：mcDinic (赞：1)

这题就是道贪心，先扫描整个序列，一旦发现满足不了（即当前元素比前一个大），就回去扫描，调整不了，直接输出答案（即不满足），否则调整。

由于上述过程虽然有双重循环，但毕竟回去调整很可能半路中断，而且一旦不行就不会再循环了，复杂度算是线性的（不过我懒得证明，估计也证不出）。

最后考虑下首尾的情况，如果满足序列条件，输出答案，否则首尾相等，也可以再调。这时判断下序列中有无负数即可。

## Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,a[100005];
signed main(){
	scanf("%lld",&T);
	while(T--){
		int ans=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		if(n==1){
			printf("0\n");
			continue;
		}
		for(int i=2;i<n;i++){
			if(a[i-1]>a[i]){
				if((i+2)%2){
					int xp=a[i-1]-a[i];
					ans+=xp*(i-1);
					for(int j=1;j<=i-1;j++){
						a[j]-=xp;
						if(a[j]<0){
							printf("-1\n");
							goto label;
						}	
					}
				}
				else{
					printf("-1\n");
					goto label;	
				}
			}
			ans+=2*(a[i]-a[i-1]);
			a[i+1]-=(a[i]-a[i-1]);
			a[i]=a[i-1];
		}
		if(a[1]==a[n]&&a[2]>a[1]){
			int x=a[2]-a[1];
			ans+=2*(n-1)*x;
			for(int i=1;i<n;i++){
				a[i]-=x;
				a[i+1]-=x;
			}
		}
		if((n+2)%2&&a[n-1]>a[n]){
			int x=a[n-1]-a[n];
			ans+=(n-1)*x;
			for(int i=1;i<n;i++)a[i]-=x;
		}
		if(a[n]!=a[n-1]){
			printf("-1\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			if(a[i]<0){
				printf("-1\n");
				goto label;
			}
		}
		printf("%lld\n",ans);
		label:;
	}
	return 0;
}
```


---

## 作者：tZEROちゃん (赞：1)

不妨从 $2$ 到 $n-1$ 遍历整个数组，对于每一组 $(a_i, a_{i+1})$ 我们让 $a_i$ 与 $a_{i-1}$ 相等，这样一来 $a$ 数组就有两种情况。

1. $a_n > a_{n-1}$
2. $a$ 是非增的

对于第二种情况，考虑翻转整个数组，此时就变成非降的了，在经过一次上述操作，显然所有元素就相等了，除了 $a_n$，此时又有两种情况。
 
1. $a_n > a_{n - 1}$，此时显然是无解的。
2. 否则，显然所有元素是相等的，判断任意一个元素是否为非负整数即可。

### Code
```cpp
#define int long long
const int N = 1e6 + 10;
int a[N];
int ans;

void solve() {
  int n; iocin >> n;
  ans = 0;
  rep (i, 1, n) {
    cin >> a[i];
  }
  if (n == 1) return ans = 0, void();
  rep (j, 1, 2) {
    rep (i, 2, n - 1) {
      if (a[i] > a[i - 1]) {
        int diff = a[i] - a[i - 1];
        ans += 2 * diff;
        a[i + 1] -= diff;
        a[i] = a[i - 1];
      }
    }
    if (a[n] > a[n - 1]) return ans = -1, void();
    reverse(a + 1, a + n + 1);
  }
  return a[1] < 0 ? ans = -1 : ans = ans, void();
}

signed main(){
  multiCase() solve(), printf("%lld\n", ans);
  return 0;
}
```

---

