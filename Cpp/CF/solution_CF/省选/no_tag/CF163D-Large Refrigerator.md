# Large Refrigerator

## 题目描述

$t$ 组数据。给定长方体的体积 $V$（以质因子乘积的形式给出），找到 $3$ 个正整数 $a,b,c$，使得 $V = abc$，且长方体的表面积 $S = 2(ab + bc + ac)$ 尽可能小。

## 说明/提示

$1 \leq t \leq 500,2 \leq V \leq 10^{18},p_i \in {\rm prime}$，所有 $p_i$ 互不相同。

## 样例 #1

### 输入

```
3
1
2 3
1
17 1
3
3 1
2 3
5 1
```

### 输出

```
24 2 2 2
70 1 1 17
148 4 6 5
```

# 题解

## 作者：Computer1828 (赞：9)

不难发现此题可以爆搜。

由题意 $abc = V$。

变形得到 $bc = \frac{V}{a}$。

所以有 $\frac{1}{2}S = ab+bc+ac = a(b+c) + \frac{V}{a}$。

考虑不等式： $a+b \geq 2\sqrt{ab}, a,b\geq 0$。

所以 $a(b+c) \geq 2a\sqrt{bc} = 2a\sqrt{\frac{V}{a}}$。

所以 $\frac{1}{2}S \geq 2a\sqrt{\frac{V}{a}} + \frac{V}{a}$。

上面的这条式子规定了 $a$ 的范围。

考虑剪枝：我们可以假设 $a \leq b \leq c$，那么显然有 $a \leq \sqrt[3]{V}, b \leq \sqrt{\frac{V}{a}}$，这使得得到一个合法的 $a$ 后就能得到对应的合法 $b$ 的范围。所以爆搜的思路就很简单：先对 $a$ 进行爆搜，得到一个合法 $a$ 后，爆搜 $b$，得到 $c = \frac{V}{ab}$，更新答案即可

请注意根号操作的精度问题。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,k;
ll p[105];
int q[105];
ll V,ans,ansa,ansb,ansc,a,b,c;
ll MAXA,MAXB;
inline void bfs(int dep,ll sum){//爆搜b，搜到第dep个因子，此时的b的值为sum 
	if(sum > MAXB) return ;
	if(dep > k){
		if(sum < a) return ;
		b = sum,c = V/a/b;
		if(a*b+b*c+a*c < ans) ans = a*b+b*c+a*c,ansa = a,ansb = b,ansc = c;	
		return ;
	}
	if(q[dep]) q[dep]--,bfs(dep,sum*p[dep]),q[dep]++;
	bfs(dep+1,sum);
}

inline void dfs(int dep,ll sum){
	if(sum > MAXA) return ;
	if(dep > k){
		a = sum;
		if(V/a + 2*a*sqrt(V/a) < ans) MAXB = sqrt(V/a)+1e-8,bfs(1,1);//这个+(1e-8)是为了调整上限的精度 
		return ;
	}
	if(q[dep]) q[dep]--,dfs(dep,sum*p[dep]),q[dep]++;
	dfs(dep+1,sum);
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&k);
		V = 1;
		for(int i = 1;i<=k;++i){
			scanf("%lld%d",p+i,q+i);
			for(int j = 1;j<=q[i];++j) V *= 1ll*p[i];
		}
		MAXA = pow(V,1.0/3)+1e-8,ansa = ansb = ansc = 0,ans = 9223372036854775800;
		dfs(1,1);
		printf("%lld %lld %lld %lld\n",2*ans,ansa,ansc,ansb);
	}
	return 0;
}
```

---

## 作者：柳易辰 (赞：6)

## Start
简单思维 + 爆搜，目前最优解。

关于数据范围，不会爆 `long long`，$k\le20$。

&nbsp;  
## 简单数学知识

（以下的讨论均针对于 $a,b,c$ 为自然数）

$b+c\ge2\sqrt{bc}$

浅显易懂，人人都会，于是：

$
\begin{aligned}
\frac S2&=ab+bc+ca=a(b+c)+bc\\
&\ge2a\sqrt{bc}+bc=2a\sqrt\frac Va+\frac Va
\end{aligned}
$

下面会用到。

&nbsp;
## 爆搜
由于数据范围很小，想到爆搜。

假设 $a\le b\le c$，则 $a\le\sqrt[3]{V},b\le\sqrt{\frac Va}$。

肯定先搜索 $a$。

我们先设答案 $S$ 是一个极大值，那么搜索答案的过程是一个 $S$ **逐渐减小**的过程。

由于 $\frac S2\ge 2a\sqrt\frac Va+\frac Va$ ，那么可以在搜索时将 $\frac S2<2a\sqrt\frac Va+\frac Va$ 的情况直接剪掉（剪枝）。

确定了 $a$ 以后搜索 $b$，大概就是这样。

&nbsp;
## 搜索 $a$
显然 $a=\prod^{k}_{i=1}p_i^{q_i}$，其中 $q_i$ 是我们需要爆搜的，并且 $q_i\le a_i$。
```cpp
inline void DFS_a(int i, ll a, ll max)
{
	if (a > max) return;
	if (i > k) // a 搜索完了
	{
		if (v / a + (a << 1) * sqrt(v / a) < S) DFS_b(1, a, 1, sqrt(v / a)); // 剪枝
		return;
	}
	if (e[i]) --e[i], DFS_a(i, a * p[i], max), ++e[i];
	DFS_a(i + 1, a, max);
}
```
其中 $i$ 表示搜素进行到第 $i$ 位（上面的连乘式子），$\max$ 表示 $a$ 的上限，$\max=\sqrt[3]{V}$。

$a$ 数组和 $a$ 重名，用 $e$ 数组代替。

`DFS_b` 是搜索 $b$，如下。  
&nbsp;
## 搜索 $b$

过程与 `DFS_a` 差不多。
```cpp
inline void DFS_b(int i, ll a, ll b, ll max)
{
	if (b > max) return;
	if (i > k) // b 搜索完成
	{
		if (b >= a)
		{
			ll c = v / a / b;
			if (a * b + b * c + c * a < S) S = (_a = a) * b + (_b = b) * c + (_c = c) * a;
			// 统计答案
		} 
		return;
	}
	if (e[i]) --e[i], DFS_b(i, a, b * p[i], max), ++e[i];
	DFS_b(i + 1, a, b, max);
}
```
`S,_a,_b,_c` 记录答案。  
&nbsp;
## End

$v$ 直接暴力计算即可。$\sqrt[3]{V}$ 计算时有可能会因为向下取整失去正确答案，可以 $+1$ 补偿精度。具体地，`DFS_a(1, 1, pow(v, 1.0 / 3) + 1);`

---

## 作者：ethan0328 (赞：3)

其实这是一道水黑。

## 思路
$\because a\times b\times c=V$

$\therefore b\times c=\dfrac{V}{a}$

$\therefore \dfrac{1}{2}S=a\times b+a\times c+b\times c$

$\ \ \ \ \ \ \ \ \ \ \ =a\times (b+c)+\dfrac{V}{a}$

$\ \ \ \ \ \ \ \ \ \ \ \ge 2\cdot a\cdot \sqrt{b\times c}+\dfrac{V}{a}$

$\ \ \ \ \ \ \ \ \ \ \ =2\cdot a\cdot \sqrt{\dfrac{V}{a}}+\dfrac{V}{a} $

这个式子后面会用。

我们不妨令 $a\le b\le c$，则 $a\le \sqrt[3]{V}$，$b\le \sqrt{\dfrac{V}{a}}$。

于是我们可以在这个范围内枚举 $a$，再枚举 $b$。

考虑剪枝，当 $\dfrac{1}{2}S<2\cdot a\cdot \sqrt{\dfrac{V}{a}}+\dfrac{V}{a}$ 时，退出循环。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t;
ll k,v,maxa,maxb,ans,ansa,ansb,ansc,p[1000],a[1000];
void dfsb(ll numa,ll l,ll sum)
{
	if(sum>maxb)
	{
		return;
	}
	if(l>k)
	{
		ll numc=v/numa/sum;
		if(numc*sum+sum*numa+numa*numc<ans)
		{
			ans=numc*sum+sum*numa+numa*numc;
			ansa=numa;
			ansb=sum;
			ansc=numc;
		}
		return;
	}
	if(a[l]>0)
	{
		a[l]--;
		dfsb(numa,l,sum*p[l]);
		a[l]++;
	}
	dfsb(numa,l+1,sum);
}
void dfsa(ll l,ll sum)
{
	if(sum>maxa)
	{
		return;
	}
	if(l>k)
	{
		if(v/sum+2*sum*sqrt(v/sum)<ans)
		{
			maxb=sqrt(v/sum);
			dfsb(sum,1,1);
		}
		return;
	}
	if(a[l]>0)
	{
		a[l]--;
		dfsa(l,sum*p[l]);
		a[l]++;
	}
	dfsa(l+1,sum);
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>k;
		v=1;
		for(int i=1;i<=k;i++)
		{
			cin>>p[i]>>a[i];
			for(int j=1;j<=a[i];j++)
			{
				v*=p[i];
			}
		}
		maxa=cbrt(v);
		ans=2e18;
		dfsa(1,1);
		cout<<ans*2<<" "<<ansa<<" "<<ansb<<" "<<ansc<<endl;
	}
}
```


---

## 作者：KobeBeanBryantCox (赞：2)

# CF163D Large Refrigerator 题解

------------

upd on 2024.11.3：增加了均值不等式的证明。

[题目传送门](https://www.luogu.com.cn/problem/CF163D)

~~本蒟蒻首杀的黑题，名副其实的水黑（doge~~

upd on 2024.11.3：怎么降紫了。。。

------------

## 题意

此题题目描述简洁无废话，题意见题目描述。

------------

## 分析

没有好方法，那就暴力搜索吧。

我们可以先假设 $a\le b\le c$，这样就大大减少了枚举次数。

分别暴力搜索 $a,b$，然后根据 $V$ 求出 $c$，再求出 $S$，比较最小值即可。

由于时间复杂度不好计算，所以提交一下试试。

发现超时，考虑剪枝。

------------

## 优化

引理（均值不等式）：$a+b\ge 2\sqrt{ab}$。

证明放在最后。

$\because abc=V$

$\therefore bc=\displaystyle \frac{V}{a}$

$\because S=2(ab+ac+bc)$

$\begin{aligned}
\therefore \displaystyle \frac{S}{2}&=ab+ac+bc\\
&=a(b+c)+\displaystyle \frac{V}{a}
\end{aligned}$

然后我们发现这玩意长得很像均值不等式。

$\because b+c\ge 2\sqrt{bc}$（见引理）

$\begin{aligned}
\therefore a(b+c)+\displaystyle \frac{V}{a}&\ge2a\sqrt{bc}+\displaystyle \frac{V}{a}\\
&\ge2a\sqrt{\displaystyle \frac{V}{a}}+\displaystyle \frac{V}{a}
\end{aligned}$

即 $\displaystyle \frac{S}{2}\ge2a\sqrt{\displaystyle \frac{V}{a}}+\displaystyle \frac{V}{a}$

于是当 $\displaystyle \frac{S}{2}<2a\sqrt{\displaystyle \frac{V}{a}}+\displaystyle \frac{V}{a}$ 时剪枝。

------------

## AC代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
long long t,k,a[100000],p[100000],v,minn,ma,mb,mc; // 十年 OI 一场空，不开 long long 见祖宗 
void dfsb(long long i,long long s,long long sum) // 搜索 b 
{
	if(sum*sum>v/i)return; // 保证 a<=b<=c 
	if(s>k)
	{
		long long kk=v/i/sum; // a 和 b 已经搜索完，求出 c 
		if(kk*sum+sum*i+i*kk<minn)minn=kk*sum+sum*i+i*kk,ma=i,mb=sum,mc=kk; // 比较最小值 
		return;
	}
	if(a[s]>0)a[s]--,dfsb(i,s,sum*p[s]),a[s]++; // 由于 V 是以质因子的形式给出，于是就可以这样搜索 
	dfsb(i,s+1,sum);
}
void dfsa(long long s,long long sum) // 搜索 a 
{
	if(sum*sum*sum>v)return; // 保证 a<=b<=c 
	if(s>k) // a 搜索完，再搜索 b 
	{
		if(2*sum*sqrt(v/sum)+v/sum<minn)dfsb(sum,1,1); // 剪枝 
		return;
	}
	if(a[s]>0)a[s]--,dfsa(s,sum*p[s]),a[s]++; // 由于 V 是以质因子的形式给出，于是就可以这样搜索 
	dfsa(s+1,sum);
}
int main()
{
	scanf("%lld",&t); // t 组数据 
	while(t--)
	{
		scanf("%lld",&k),v=1; // 多测不清空，爆零两行泪 
		for(long long i=1;i<=k;i++)
		{
			scanf("%lld%lld",&p[i],&a[i]);
			for(long long j=1;j<=a[i];j++)v*=p[i];
		}
		minn=9e18,dfsa(1,1); // 多测不清空，爆零两行泪 
		printf("%lld %lld %lld %lld\n",minn*2,ma,mb,mc);
	}
	return 0;
}
```

注意事项：
> 1. 十年 OI 一场空，不开 long long 见祖宗！
> 2. 多测不清空，爆零两行泪。

------------

## 关于 $a+b\ge 2\sqrt{ab}$ 的证明

首先我们有 $(\sqrt a-\sqrt b)^2\ge 0$。

拆开来得到 $a+b-2\sqrt{ab}\ge 0$。

移项得 $a+b\ge 2\sqrt{ab}$。

证毕。

------------

后记 1：版权所有@[KobeBeanBryantCox](https://www.luogu.com.cn/user/865625)，请勿抄袭代码。

后记 2：写代码的习惯一定要好，代码不要乱七八糟，优秀的码风是很醉人的~

~~还有，能不能不要脸地要个赞呀QwQ~~

---

## 作者：Mirasycle (赞：1)

搜索题。

先确定思路，应该是逐一确定 $abc$。然后对于要搜的数考虑  $V$ 的每一个质因子应该放几次方进去。

接下来就是剪枝

1. **可行性剪枝**，不妨设 $a \le b \le c$，那么 $a\le\sqrt[3]{V}$ 且 $b^2 \le \frac{V}{a}$。

1. **优化搜索顺序**，发现 $abc$ 三个数尽可能平均时答案应该会更大。所以 $a$ 作为最小的数应该尽可能大一点才能保证平均，这样才会先搜到更优答案以方便后续更快排序不优的答案。同理确定 $a$ 后 $b$ 也是如此，于是我们需要对于每一个质因子从最大的指数开始枚举。

1. ****最优性剪枝****，

固定 $a$，
$$abc=V \to bc=\frac{V}{a}$$
$$b+c \ge 2\sqrt{bc}=2\sqrt{\frac{V}{a}}$$
考虑面积表达式，
$$\frac{1}{2}S=ab+bc+ca=a(b+c)+bc$$
$$\frac{1}{2}S \ge 2a\sqrt{\frac{V}{a}}+\frac{V}{a}$$

如果当前搜到的 $a$ 所得面积下限大于当前最优面积那么直接剪掉。

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

搜索加剪枝。

很经典的，我们不妨设 $a\le b\le c$。这时候，显然有 $a\le\sqrt[3]{v},b\le\sqrt{\frac{v}{a}}$。

这时候，我们基于上述范围进行枚举。显然，题目中给出了其因数分解，我们也可以利用这个分解加速枚举。

但是这样好像过不了。我们需要再减一次枝。已知 $ans=2(ab+bc+ca)$。

因为 $bc=\frac{v}{a}$，所以由均值不等式可得 $b+c \ge 2\sqrt{bc}=2\sqrt{\frac{v}{a}}$。此时 $\frac{1}{2}ans=ab+bc+ca=bc+a(b+c) \ge \frac{v}{a}+2a\sqrt{\frac{v}{a}}$。

因此，$\frac{1}{2}ans\ge\frac{v}{a}+2a\sqrt{\frac{v}{a}}$ 也应用来剪枝。

我并不会分析上述过程的时间复杂度，但一定是 $O(\text{能过})$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int tt, n, p[105], t[105], v, ma, mb, a, ans, aa, ab;
inline void dfsb(const int& dep, const int& vl) {
	if (vl > mb) return;
	if (dep > n) {
		if (vl < a) return;
		int cv = v / a / vl;
		if (a * vl + vl * cv + cv * a < ans)
			ans = a * vl + vl * cv + cv * a,
			aa = a, ab = vl;
		return;
	}
	if (t[dep]) t[dep]--, dfsb(dep, vl * p[dep]), t[dep]++;
	dfsb(dep + 1, vl);
}
inline void dfsa(const int& dep, const int& vl) {
	if (vl > ma) return;
	if (dep > n) {
		a = vl; mb = sqrt(v / a) + 1;
		if (v / a + 2 * a * sqrt(v / a) < ans) dfsb(1, 1);
		return;
	}
	if (t[dep]) t[dep]--, dfsa(dep, vl * p[dep]), t[dep]++;
	dfsa(dep + 1, vl);
}
signed main() {
	ios::sync_with_stdio(0);
	cin >> tt;
	while (tt--) {
		cin >> n; v = 1;
		for (int i = 1; i <= n; ++i) {
			cin >> p[i] >> t[i];
			for (int j = 0; j != t[i]; ++j)
				v *= p[i];
		}
		ma = pow(v, 1.0 / 3) + 1; ans = 9e18; dfsa(1, 1); 
		cout << ans * 2 << " " << aa << " " << ab << " " << v / aa / ab << endl;
	}
	return 0;
}
```

---

## 作者：tder (赞：0)

给定 $V=a\times b\times c$，试求 $S=2\times(ab+ac+bc)$ 的最小值。

暴搜暴搜！

推式子。由 $V=a\times b\times c$ 有 $a=\dfrac V{bc}$，即 $bc=\dfrac aV$。

而就有 $S=2\times(ab+ac+bc)=2\times(a(b+c)+bc)$。

由基本不等式，有 $b+c\ge2\sqrt{bc}$，所以 $a(b+c)+bc\ge2a\sqrt{bc}$，而 $2\times(a(b+c)+bc)\ge4a\sqrt{bc}$，即 $S\ge4a\sqrt{bc}$。

有了上面的结论，我们令 $a\le b\le c$，则显然有 $a\le\sqrt[3]{V}$，且 $b\le\sqrt{\dfrac Va}$，于是暴搜即可。

另外注意极大值的赋值，若为 $10^{18}$ 可能不够。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5, INF = 0x3f3f3f3f3f3f3f3f; const double EPS = 1e-8;
int v, k, p[N], q[N], mxa, mxb, a, b, c, ansa, ansb, ansc, ans = INF;
inline int read() {
    int r = 0, f = 1;
    char c = getchar();
    while(c != '-' && (c < '0' || c > '9')) c = getchar();
    if(c == '-') {
        f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
        r *= 10; r += c - '0';
        c = getchar();
    }
    return r * f;
}
inline void write(int x) {
    if(x < 0) {
        putchar('-');
        x = -x;
    }
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
void dfs2(int t, int s) {
    if(s > mxb) return;
    if(t == k + 1) {
        b = s, c = v / (a * b);
        if(a <= b && 2 * (a * b + b * c + a * c) < ans) {
            ans = 2 * (a * b + b * c + a * c);
            ansa = a, ansb = b, ansc = c;
        }
        return;
    }
    if(q[t]) {
        q[t]--;
        dfs2(t, s * p[t]);
        q[t]++;
    }
    dfs2(t + 1, s);
    // int u = 0, uu = uq[t];
    // for(int i = 1; i <= q[t] - uu && s * p[t] <= mxb; i++) {
    //     if(s * p[t] > mxb) break;
    //     s *= p[t], uq[t]++, u++;
    //     dfs2(t + 1, s);
    // }
    // while(u--) uq[t]--;
}
void dfs1(int t, int s) {
    if(s > mxa) return;
    if(t == k + 1) {
        a = s;
        b = (sqrt(v / a) + EPS);
        c = v / a / b;
        if(2 * (a * b + a * c + b * c) >= ans) return;
        if(4 * a * b + 2 * v / a < ans) {
            mxb = b;
            dfs2(1, 1);
        }
        return;
    }
    if(q[t]) {
        q[t]--;
        dfs1(t, s * p[t]);
        q[t]++;
    }
    dfs1(t + 1, s);
    // int u = 0, uu = uq[t];
    // for(int i = 1; i <= q[t] - uu && s * p[t] <= mxa; i++) {
    //     s *= p[t], uq[t]++, u++;
    //     dfs1(t + 1, s);
    // }
    // while(u--) uq[t]--;
}
void solve() {
    v = 1, a = b = c = 0, ans = INF;
    k = read();
    for(int i = 1; i <= k; i++) {
        p[i] = read(), q[i] = read();
        for(int j = 1; j <= q[i]; j++) v *= p[i];
    }
    mxa = pow(v, 1.0 / 3) + EPS;
    dfs1(1, 1);
    write(ans); putchar(' ');
    write(ansa); putchar(' ');
    write(ansb); putchar(' ');
    write(ansc); putchar('\n');
}
signed main() {
    int T = read();
    while(T--) solve();    
}
```

---

## 作者：云岁月书 (赞：0)

首先题面看起来恐怖，其实爆搜解决一切。

但是太纯的爆搜应该是会死的很惨的，所以我们考虑剪枝:

首先，比较容易想的剪枝:

保证 $a \geqslant b \geqslant c$,这样可以减少一些重复的搜索量(下面没用)。

接下来考虑最优化剪枝:

$bc = \frac{V}{a}\leftarrow V = abc \rightarrow a = \frac{V}{bc}$

$ab+bc+ac = a(b+c)+bc = a(b+c)+\frac{V}{a} \geqslant 2a\sqrt{bc}+\frac{V}{a} = 2a\sqrt{\frac{V}{a}}+\frac{V}{a}$

如上述式子:

若存在 $ans \leqslant 2a\sqrt{\frac{V}{a}}+\frac{V}{a}$，
就可以剪掉。

再就是很基本的可行性剪枝:

$a^3 < V,ab^2 < V$

综上这道水题就被解决了。

~~~
# include <ctime>
# include <cmath>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <algorithm>
# include <queue>
# include <iostream>
# define LL long long

LL ansa,ansb,ansc,ans,S,p[105][65],V = 1;
int sp[105],n;

void dfs_bc(const int cur,const LL a,const LL b)
{
    if((double)b*b > V/a) return;
    else if(cur > n)
    {
        const LL c = V/a/b;
        if(a*(b+c)+b*c < ans)
        {
            ans = a*(b+c)+b*c;
            ansa = a;
            ansb = b;
            ansc = c;
        }
    }
    else 
    {
        for(int j = sp[cur]; j >= 0 ; --j)
        {
            sp[cur] -= j;
            dfs_bc(cur+1,a,b*p[cur][j]);
            sp[cur] += j;
        }
    }
}

void dfs_a(int cur,const LL a)
{
    if((double)a*a > V/a) return;
    else if(cur > n)
    {
        const int x = V/a;
        if(ans <= 2*a*sqrt(x)+x) return;
        dfs_bc(1,a,1);
    }
    else 
    {
        for(int j = sp[cur]; j >= 0 ; --j)
        {
            sp[cur] -= j;
            dfs_a(cur+1,a*p[cur][j]);
            sp[cur] += j;
        }
    }
}

int main()
{
    int T;
    for(scanf("%d",&T); T ; T--)
    {
        scanf("%d",&n);V = 1;
        for(int i = 1; i <= n ; ++i) scanf("%lld%d",&p[i][1],sp+i);
        for(int i = 1; i <= n ; ++i)
        {
            p[i][0] = 1;
            for(int j = 2; j <= sp[i] ; ++j) p[i][j] = p[i][j-1]*p[i][1];
            V *= p[i][sp[i]];
        }
        ans = ((1LL)<<(62LL));
        dfs_a(1,1);
        printf("%lld %lld %lld %lld\n",ans*2,ansa,ansb,ansc);
    }
    return 0;
}

~~~

---

