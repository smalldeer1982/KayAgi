# Balanced

## 题目描述

You are given a cyclic array $ a $ with $ n $ elements, where $ n $ is odd. In each operation, you can do the following:

- Choose an index $ 1 \le i \le n $ and increase $ a_{i - 1} $ by $ 1 $ , $ a_i $ by $ 2 $ , and $ a_{i + 1} $ by $ 1 $ . The element before the first element is the last element because this is a cyclic array.

A cyclic array is called balanced if all its elements are equal to each other.

Find any sequence of operations to make this cyclic array balanced or determine that it is impossible. Please note that you do not have to minimize the number of operations.

## 说明/提示

In the first test case:

- After $ 1 $ operation applied to index $ i = 2 $ , the array $ a = [3, 3, 3] $ .

In the second test case:

- After $ 2 $ operations applied to index $ i = 1 $ , the array $ a = [5, 4, 5] $ .
- After $ 1 $ operation applied to index $ i = 2 $ , the array $ a = [6, 6, 6] $ .

In the third test case:

- After $ 2 $ operations applied to index $ i = 1 $ , the array $ a = [5, 4, 1, 2, 3] $ .
- After $ 3 $ operations applied to index $ i = 3 $ , the array $ a = [5, 7, 7, 5, 3] $ .
- After $ 2 $ operations applied to index $ i = 5 $ , the array $ a = [7, 7, 7, 7, 7] $ .

## 样例 #1

### 输入

```
6
3
2 1 2
3
1 2 3
5
1 2 1 2 1
7
1 2 1 2 1 3 1
9
10000 10000 10000 10000 10000 10001 10002 10001 10000
1
10```

### 输出

```
0 1 0 
2 1 0 
2 0 3 0 2 
4 2 7 0 8 0 6 
1 1 1 1 1 1 0 1 1 
0```

# 题解

## 作者：MarSer020 (赞：14)

萌萌题，感觉只有 *2000 啊，但是怎么 clist 有 2500 啊 /kk

有个看上去很像的题是 arc129d，但是很不一样。

$\Large\text{Solution}$

设最终 $i$ 位置被操作了 $c_i$ 次，则最终 $i$ 位置上的数为 $a_i+c_{i-1}+2c_i+c_{i+1}$，则：

$$a_i+c_{i-1}+2c_i+c_{i+1}=a_{i+1}+c_i+2c_{i+1}+c_{i+2}$$

即：

$$(c_{i-1}+c_i)-(c_{i+1}+c_{i+2})=a_{i+1}-a_i$$

记 $b_i=c_i+c_{i+1}$，则 $b_{i+1}=b_{i-1}+a_i-a_{i+1}$。

由于 $n$ 为奇数，由上式可以得到每个 $b_i$ 的值，那么就很容易求出 $c_i$ 了。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int int64_t
using namespace std;
int	n,T,sum,a[200005],b[200005],c[200005];
int chk(int x){
	return x>n?x-n:x;
}
int32_t main(){
	ios::sync_with_stdio(0),cin.tie(0),cin>>T;
	while(T--){
		cin>>n,sum=0;
		for(int i=1;i<=n;i++)
			cin>>a[i],b[i]=c[i]=0;
		if(n==1){
			cout<<"0\n";
			continue;
		}
		for(int i=chk(3),j=1;i!=1;j=i,i=chk(i+2))
			b[i]=b[j]+(a[chk(j+1)]-a[i]);
		if(b[n-1]+(a[n]-a[1])){
			cout<<"-1\n";
			continue;
		}
		for(int i=1;i<=n;i++)
			sum+=b[i];
		if(sum&1)
			for(int i=1;i<=n;i++)
				b[i]++,sum++;
		sum>>=1;
		for(int i=2;i<=n;i+=2)
			sum-=b[i];
		c[1]=sum;
		for(int i=2;i<=n;i++)
			c[i]=b[i-1]-c[i-1];
		sum=*min_element(c+1,c+n+1);
		for(int i=1;i<=n;i++)
			cout<<c[i]-sum<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Xy_top (赞：13)

简单题，没写完。

显然可以将 $a$ 数组做环形差分，这样操作变为四个位置 ``+1 +1 -1 -1``，最终要求差分数组全为 $0$。

然后我们发现，再做完 ``+1 +1 -1 -1`` 后，第三个位置再做一次操作，那么就变成 ``+1 +1 0 0 -1 -1``，周而复始最终我们会得到 ``-1 0 +1``，称这个操作为操作 $1$。

这时如果对第三个位置再进行操作 $1$，那么得到 ``-1 0 0 0 +1``，周而复始我们可以对任意位置 $-1$，再对任意位置 $+1$。

于是就写完了，代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n;
int a[200005], c[200005];
int upd[2][800005], ans[200005];
int u[2][800005];
queue <int> q1, q2;
//q1 存 <0   q2 存 >0
int r (int x) {
	if (x % n == 0) return n;
	return x % n;
}
void cz (int x, int z) {//对位置 x 进行 z 次操作 1
	u[(x + 1) & 1][x + 1] += z;
	u[(x + n) & 1][x + n] -= z;
}
void func (int x, int y, int z) {//第 x 个位置 -z 第 y 个位置 +z 
	if (x > y) y += n;//确保 x < y
	if ( (x & 1) != (y & 1) ) y += n;//确保奇偶性相同
	upd[x & 1][x] += z;
	upd[y & 1][y - 1] -= z;
}
void solve () {
	cin >> n;
	For (i, 1, 4 * n) upd[0][i] = upd[1][i] = u[0][i] = u[1][i] = 0;
	For (i, 1, n) ans[i] = 0;
	For (i, 1, n) cin >> c[i];
	if (n == 1) {
		cout << 0;
		return;
	} else if (n == 3) {
		int mx = max ({c[1], c[2], c[3]});
		For (i, 1, n) cout << mx - c[i] << ' ';
		return;
	}
	a[1] = c[1] - c[n];
	For (i, 2, n) a[i] = c[i] - c[i - 1];
	For (i, 1, n) {
		if (a[i] < 0) q1.push (i);
		else if (a[i] > 0) q2.push (i);
	}
	while (!q1.empty () ) {
		int i = q1.front ();
		q1.pop ();
		while (a[i] != 0) {
			int u = q2.front ();
			q2.pop ();
			if (a[u] > abs (a[i] ) ) {
				func (u, i, abs (a[i]) );
				a[u] -= abs (a[i]);
				a[i] = 0;
				q2.push (u);
			} else {
				func (u, i, a[u]);
				a[i] += a[u];
				a[u] = 0;
			}
		}
	}
	For (i, 1, 4 * n) {
		upd[0][i] += upd[0][i - 1];
		upd[1][i] += upd[1][i - 1];
		cz (r (i), upd[i & 1][i]);
	}
	For (i, 1, 4 * n) {
		u[0][i] += u[0][i - 1];
		u[1][i] += u[1][i - 1];
		ans[r (i + 1)] += u[i & 1][i];//这个是 i + 1 的操作次数
	}
	For (i, 1, n) cout << ans[i] << ' ';
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：mango2011 (赞：8)

贡献一发和目前看到的做法都不同的思路！

特别鸣谢：[lgx57 同学](https://www.luogu.com.cn/user/1053695) 熟练使用 Mathematica 对我的帮助。

**首先特殊处理掉 $n=1$ 的情况。**

看到这个题目感觉非常不能贪心，所以考虑用线性代数去搞（**字母系统与题中不同**）：

令 $v_i$ 表示最终 $a_i$ 的增加量；$t_i$ 表示位置 $i$ 上操作的次数。

假设我们已知了一组 $v_i$，要求这些 $t_i$，那么就有：

$$

\begin{equation*}
    \begin{cases}
        v_1=t_n+2t_1+t_2\\
        v_2=t_1+2t_2+t_3\\
        v_3=t_2+2t_3+t_4\\
        \dots\\
        v_{n}=t_{n-1}+2t_n+t_1
    \end{cases}
\end{equation*}

$$

然后写成矩阵的形式高斯消元一下就会发现 $t_i$ 的解的形式相当优美：

![](https://cdn.luogu.com.cn/upload/image_hosting/whb29pzq.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/f3ps5d37.png)

（上图中的 $a_i$ 表示本题解中的 $v_i$）

考虑一组系数 $b_i$，其中 $b_{\frac{n+1}{2}}=n$，由中间向两侧延伸，绝对值依次 $-2$，符号依次相反：

$n=3$ 时 $b=[-1,3,1]$；$n=5$ 时 $b=[1,-3,5,-3,1]$；$n=7$ 时 $b=[-1,3,-5,7,-5,3,-1]$，以此类推。

接下来我们就可以考虑表示出 $t_i$ 了：

对于每一个 $i$，令 $c_{i,j}$ 为一组系数，其中 $c_{i,i}=b_{\frac{n+1}{2}}$，其前后系数由 $b_i$ 顺时针延伸得到。

例如，当 $n=7$，$i=1$ 时 $c_{i}=[7,-5,3,-1,-1,3,-5]$；$i=2$ 时 $c_{i}=[-5,7,-5,3,-1,-1,3]$。

于是 $t_i=\frac{\displaystyle\sum_{j=1}^{n}c_{i,j}v_j}{4}$。

这启发我们对原数列进行 $\bmod 4$ 意义下的考虑：

显然，若存在 $t_i$ 为整数，那么所有的 $t_j$ 都是整数。

令 $v_{0,i}=M-a_i$，其中 $M$ 为 $a$ 中最大的数。

枚举全局偏移量 $\varDelta$（即 $v_{i}=v_{0,i}+\varDelta$） 模 $4$ 意义下的值，进行代入计算（具体方法就是先算出 $t_1,t_2$，然后用方程组进行代入），同时发现 $\displaystyle\sum_{i=1}^{n}b_i>0$，因此只要取充分大的 $\varDelta$ 就可以保证 $t_i$ 的非负性。

由于 $n$ 是奇数，所以解总是存在的。

综上，我们解决了这个有趣的问题，复杂度为 $O(n)$。

[提交记录](https://codeforces.com/contest/2032/submission/289343613)

---

## 作者：Day_Tao (赞：3)

小清新构造，感觉到不了 *2400。

题目中的约束是一段区间的修改，要让整个序列都变为相同的，而题目中也并没有让我们求出最优解，所以我们考虑能不能构造一种方案让操作转化为单点加减的。

容易知道，我们并不关心 $a$ 序列的具体数值，只关心 $a$ 的相对大小关系。

首先发现我们可以构造一种**相邻两个数都 -1 的方案**。具体的，由于 $n$ 为奇数，所以我们每隔一个位置进行一次操作，最终达成的效果是这样的：

修改：` 0  1  0 ...  1  0  0  1 ...  0  1`（1 表示修改）  
变化：`+2 +2 +2 ... +2 +1 +1 +2 ... +2 +2`

接着我们发现这个操作的长度是 $2$，为偶数，这样循环若干次就可以构造出一种**单点加**的情况了！具体的，效果如下：（前面的操作直接简化为 -1 -1 操作）

变化：`-1 -1 -1 ... -1 0 -1 -1 ... -1 -1`

这样我们就构造完了。这也证明，不存在无解情况。

接下来问题就转化为了一个模拟题。

直接暴力修改每一次操作是不明智的，所以我们考虑计算出所有要修改的地方之后一起操作。不难发现，对于单点加操作，其实每次都操作了一段**奇偶性相同的前后缀**，这就启示我们对操作做一个奇偶位置的差分，之后再前缀和。对于相邻两个数都 $-1$ 的操作也差不多，也是进行一个奇偶位置的差分。这样就彻底做完了。

时间复杂度 $O(n)$。写出来的码也比较小清新。感觉比现有题解都要好理解一些（吗）。

**Code：**

```cpp
int n,a[N],ans[N],mx,s[N];
inline void SOLVE(){
	n=rd(),mx=0;for(int i=1;i<=n;i++)a[i]=rd(),cmx(mx,a[i]);
	for(int i=1;i<=n;i++)a[i]=mx-a[i],ans[i]=s[i]=0;
	for(int i=1;i<=n;i++)
		if(i&1)s[i+1]+=a[i],s[1]+=a[i],s[i]-=a[i];
		else s[i+1]+=a[i],s[2]+=a[i],s[i]-=a[i];
	for(int i=3;i<=n;i+=2)s[i]+=s[i-2],s[i-1]+=s[i-3];
	for(int i=1;i<=n;i++)
		if(i&1)ans[i+2]+=s[i],ans[2]+=s[i],ans[i+1]-=s[i];
		else ans[i+2]+=s[i],ans[1]+=s[i],ans[i+1]-=s[i];
	for(int i=3;i<=n;i+=2)ans[i]+=ans[i-2],ans[i-1]+=ans[i-3];
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);puts("");
	return ;
}
```

---

## 作者：cdx123456 (赞：3)

不会性质，只能硬算了。

### Solution



注意到如果 $n$ 个数能变为 $x$，那么一定能变 $x+4$，因为可以在 $n$ 个数上各进行一次操作，故 $n$ 个数如果能变得相同，那么需要能变成 $x,x+1,x+2,x+3$ 中的一个，$x$ 是一个巨大的数，取到 $10^{17}$ 即可，问题转化为检查可行性。

设 $n$ 个数分别进行了 $b_1,b_2,...,b_n$ 次操作，则 $n$ 个数会变为 $a_1+2b_1+b_2+b_n,a_2+2b_2+b_1+b_3,...,a_n+2b_n+b_{n-1}+b_1$。

考虑高斯消元，这个东西是 $n$ 个变量和 $n$ 个条件，且条件线性不相关，故对于每次检查，只有唯一一组 $b$ 可以满足条件，那么直接设矩阵消元求方程组即可，然而有三个问题，下面分别来考虑如何解决。

#### 细节

由于消元可能出负数，将所有 $b$ 加上一个大偏移量即可。

#### 时间复杂度

直接消元复杂度 $O(n^3)$，显然不可做，但矩阵长成如下的样子。

$\begin{pmatrix}2&1&&&\cdots&&1\\1&2&1\\&1&2&1\\&&&&\ddots\\1&&&&&1&2\end{pmatrix}$

模拟一下过程不难发现每行最多有三个元素，且每行最多对两行进行消元，故消元复杂度可以降至 $O(n)$。

#### 精度

直接用 double 做大概率是无法通过的，考虑对一个大模数做这件事，这个模数要是质数，因为要求逆元，质数更为好做，我选的模数是 $99999999999999997$ ，模数比较小会被卡。

如果存在答案，猜测它不会太大，最多就 $10^{18}$，然后直接算，最后在模拟检验一下就好。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int b[200010],c[200010],d[200010],e[200010],n,a[200010],inv[200010];
const int mod=99999999999999997;
int q_pow(int x,int y){
	if(!y) return 1;
	int z=q_pow(x,y>>1);
	if(y&1) return (__int128)z*z%mod*x%mod;
	else return (__int128)z*z%mod;
}
bool check(int x){
	for(int i=1;i<=n;i++) b[i]=x-a[i];
	c[1]=1;
	c[n-1]=1;
	c[n]=2;
	d[1]=1;
	d[n-1]=1;
	for(int i=1;i<=n;i++) e[i]=2;
	for(int i=1;i<n-1;i++){
		int x=q_pow(e[i],mod-2);
		inv[i]=x;
		b[n]=(b[n]-(__int128)b[i]*c[i]%mod*x%mod+mod)%mod;
		c[i+1]=(c[i+1]-(__int128)c[i]*x%mod+mod)%mod;
		c[n]=(c[n]-(__int128)c[i]*x%mod*d[i]%mod+mod)%mod;
		c[i]=0;
		b[i+1]=(b[i+1]-(__int128)b[i]*x%mod+mod)%mod;
		e[i+1]=(e[i+1]-x+mod)%mod;
		d[i+1]=(d[i+1]-(__int128)x*d[i]%mod+mod)%mod;
	}
	int y=q_pow(e[n-1],mod-2);
	inv[n-1]=y;
	b[n]=(b[n]-(__int128)c[n-1]*y%mod*b[n-1]%mod+mod)%mod;
	c[n]=(c[n]-(__int128)d[n-1]*c[n-1]%mod*y%mod+mod)%mod;
	b[n]=(__int128)b[n]*q_pow(c[n],mod-2)%mod;
	for(int i=1;i<n;i++) b[i]=(b[i]-(__int128)b[n]*d[i]%mod+mod)%mod,d[i]=0;
	for(int i=n-1;i>1;i--){
		b[i]=(__int128)b[i]*inv[i]%mod;
		b[i-1]=(b[i-1]-b[i]+mod)%mod;
	}
	b[1]=(__int128)b[1]*inv[1]%mod;
	e[1]=1;
	for(int i=1;i<=n;i++) b[i]=(b[i]+10000000000000000)%mod;
	b[n+1]=b[1];
	for(int i=2;i<=n;i++) if(a[i]+2*b[i]+b[i+1]+b[i-1]!=a[1]+2*b[1]+b[2]+b[n]) return 0;
	for(int i=1;i<=n;i++) cout<<b[i]<<' ';
	cout<<'\n';
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int f=1;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(n==1){
			cout<<0<<endl;
			continue;
		}
		for(int i=0;i<=3;i++){
			if(check(1e17+i)){
				f=0;
				break;
			}
		}
		if(f) cout<<-1<<'\n';
	}
	return 0;
}
```

---

## 作者：tai_chi (赞：2)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18523933) 中阅读。

#### 题意

给一个**环形数组** $a$，你可以进行任意次操作，每次操作形如：

- 选一个位置 $i$，$a_{i-1}$ 增加 $1$，$a_i$ 增加 $2$，$a_{i+1}$ 增加 $1$。

构造一个操作方案，使得 $a$ 的每个位置都相等。

#### 分析

是官方解法。

我们不妨允许“负操作”：选择一个 $i$，将 $a_{i-1}$ 增加 $-1$，$a_i$ 增加 $-2$，以及 $a_{i+1}$ 增加 $-1$。如果最终在数组 $v$ 中出现负元素，我们可以通过将所有 $v_i$ 同时增加，从而使最终数组 $v$ 合法，不难发现这并不影响差分数组。

考虑 $n=3$ 的情况。让 $a_1=a_3$ 相等是容易的，只需要对小的那个进行差值次操作即可，最后在 $a_2$ 上进行一些操作让三者平衡。对任意 $n=3$ 这种解法都是正确的。

我们发现这种操作其实是让原数组有了对称性，接下来我们尝试把这种做法扩展到一般的情况下。

$n>3$ 怎么说？让 $a_1=a_n$ 可以用上面的第一步，但是让 $a_2=a_{n-1}$ 要花点心思。牢记我们的目标：让这两个位置的增量产生差值填补现有的差值。

拿官方题解 $a=[48,18,26,57,39]$ 的例子。

- 首先，我们平衡 $a_1$ 和 $a_5$。只需对 $a_5$ 进行 $9$ 次操作。数组变为 $[57,18,26,66,57]$。
- 然后，我们平衡 $a_2$ 和 $a_4$。我们从 $a_2$ 开始，每次向左移动两个（在循环意义下），直到到达 $a_5$，每次移动到一个位置就操作 $48$ 次。也就是说对 $a_2$ 和 $a_5$ 各操作 $48$ 次。数组变为：$[153, 114, 64, 114, 153]$。

至此数组有了良好的对称性。

一般地，想要平衡 $a_i$ 和 $a_{n-i+1}$，我们的操作指针需要从 $i$ 开始每次向前移动两个，直到到达 $a_{n-i+2}$，操作的次数就是 $|a_i - a_{n-i+1}|$。

接下来考虑第二步，回到例子，最中间的一个容易与两边平衡，数组变为 $[153,164,164,164,153]$。

接下来对 $a_2$ 和 $a_4$ 操作 $-11$ 次就行，数组变为 $[142,142,142,142,142]$。随便手玩下就能发现这是对目前已经平衡的中间一段隔一个操作一次。

至此操作结束。考虑如何统计每个位置的操作次数。第一步是一段前缀和一段后缀操作，注意到路径上奇偶性不变，那可以奇数位置和偶数位置分开做前缀和，操作次数就是差值。第二步同理。

别忘了把负的操作数加成非负的。

---

## 作者：MattL (赞：1)

~~第一次 div2 做出五题纪念一下。~~

奇妙构造题

---

题意：
> 对于一个长为 $n$ 的循环数组，每次可以选择任意一个位置 $i$，使这个位置 $+2$，其相邻位置 $+1$。求任意一个构造使数组元素全部一样。

首先从增加的 121 开始入手。

121 改变了 3 个数的值，比较多，操作起来比较麻烦，考虑能否减少改变的数量。

考虑要使整个数组值一样，不规定每个元素的值为多少，故可以对整个数组增加同一个值也不影响。

不难发现，可以有以下的操作方式。

---
第一种：

```
121
  121
    121
      121

122222221（和）
```

若我们对整个数组进行操作，可以认为是整个数组 $+2$（忽略），对两个相邻的数 $-1$。

---
第二种：
```
121
 121
  121
1  12
21  1
44444（和）
```
不难发现，我们对数组的每一个位置都操作一次，相当于对数组整体进行 $+4$，不影响相对的大小，可以忽略。

换句话说，我们可以对某个位置操作负数次，最后对操作数组的每一个数加上一个基准值，使操作数组非负即可。

---

既然我们可以对数组的相邻两个数同时加一或者减一，我们则可以将除了数组某个位置外的所有数变为 0。

但是我们还剩最后一个数，发现用第一种方法无论如何都消不掉。

注意到，对整个数组减去一个数，不消耗任何操作，由于数组长度为奇数，我们对整个数组都减去剩下的那个数，这样就只剩下偶数个非 0 的数，且大小均相等，可以全部消去。

---

对于实现，发现第一种操作一个个标记是 $\mathcal O(n)$ 的，总时间复杂度 $\mathcal O(n^2)$，无法通过。

观察第一种操作的操作序列：

```
121
  121
    121
0101010
```
不难发现，操作是都是隔一个操作一次，所以可以将操作序列奇偶拆开，差分来做。

---
下面给出一个例子：

```
3 1 2
0 -2 2（1,2的位置一起-3）
0 0 4（2,3的位置一起+2）
-4 -4 0（不操作，只是把最终数组每一个值+4）
0 0 0（1,2的位置一起+4）
```

可以结合代码理解：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int N=2e5+10;
int n;
LL ans[N],q[N],p[N],a[N];//q[i]即从i往前的差分数组，p[i]即往后
void do2(int id,LL k){//等价于id id+1 的位置都-k 
	q[id-1]+=k,p[id+2]+=k;
}void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)ans[i]=p[i]=q[i]=0;
	
	do2(1,a[1]);
	a[2]-=a[1];a[1]=0;
	for(int i=2;i<n;i++){
		do2(i,a[i]);
		a[i+1]-=a[i];a[i]=0;
	}//至此，只剩a[n]可能非0 
	
	for(int i=1;i<n;i++)a[i]=-a[n];a[n]=0;//所有数减去a[n] 
	
	do2(1,a[1]);a[2]-=a[1];a[1]=0;
	for(int i=2;i<n;i++){
		do2(i,a[i]);
		a[i+1]-=a[i];a[i]=0;
	}//同上操作一遍，所有数即可相等 
	
	LL tmp=0;for(int i=1;i<=n;i+=2)tmp+=p[i],ans[i]+=tmp;
	tmp=0;for(int i=2;i<=n;i+=2)tmp+=p[i],ans[i]+=tmp;
	tmp=0;for(int i=n;i>=1;i-=2)tmp+=q[i],ans[i]+=tmp;
	tmp=0;for(int i=n-1;i>=1;i-=2)tmp+=q[i],ans[i]+=tmp;//统计差分操作数组 
	
	LL minn=0;
	for(int i=1;i<=n;i++)minn=min(minn,ans[i]);//减去基准值，保证非负 
	for(int i=1;i<=n;i++)cout<<ans[i]-minn<<' ';cout<<'\n';
}int main(){
    int T;cin>>T;
	while(T--)
        solve();
    return 0;
}
```

---

## 作者：george0929 (赞：1)

显然的，操作具有交换律与结合律。

考虑如下情况：

```
1 1 1 ... 1 1 0 1 1 ... 1 1 1
```

能解决如上问题说明我们可以随意调整一个数的相对大小，自然也就能解决所有情况。

那么如何解决呢？

不妨先写一个贪心（如果想不到贪心，写暴力也可以）：每次选出最小数字进行操作，直至其大于相邻的数。

当然，这是错的，但可以把小数据做对，因此可以用来打表。

打表代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
int n, a[200005], x[200005];

int p(int x) {
	if (x < 1)
		return x + n;
	if (x > n)
		return x - n;
	return x;
}

struct node {
	int l, r, mn, mx, mnpos;
} t[800005];

/*
由于这是赛时代码，当时以为这么做是对的，故使用了线段树优化。
为了节省篇幅，线段树部分就省略了。
*/

int A(int p, int pos) {
	if (t[p].l == t[p].r) {
		return t[p].mn;
	}
	int mid = (t[p].l + t[p].r) / 2;
	if (mid >= pos)
		return A(p * 2, pos);
	else
		return A(p * 2 + 1, pos);
}

void solve() {
	int d;
	cin >> n >> d;
	for (int i = 1; i <= n; i++) {
		a[i] = 1;
		x[i] = 0;
	}
	a[d] = 0;
	build(1, 1, n);
	while (1) {
		int mn = t[1].mn, mx = t[1].mx, pos = t[1].mnpos;
		if (mx == mn)
			break;
		int X = A(1, pos), Y = max(A(1, p(pos - 1)), A(1, p(pos + 1)));
		if (Y == X)
			Y++;
		x[pos] += Y - X;
		modify(1, pos, (Y - X) * 2);
		modify(1, p(pos - 1), Y - X);
		modify(1, p(pos + 1), Y - X);
	}
	int mn = 1e9;
	for (int i = 1; i <= n; i++)
		mn = min(mn, x[i]);
	for (int i = 1; i <= n; i++) {
		x[i] -= mn;
		cout << x[i] << " ";
	}
	cout << "\n";
}

signed main() {
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
}
```

输入：

```cpp
5
21 3
21 5
21 8
21 18
21 20
```

输出：

```cpp
9 0 10 0 9 1 8 2 7 3 6 4 5 5 4 6 3 7 2 8 1
8 1 9 0 10 0 9 1 8 2 7 3 6 4 5 5 4 6 3 7 2
3 7 2 8 1 9 0 10 0 9 1 8 2 7 3 6 4 5 5 4 6
8 2 7 3 6 4 5 5 4 6 3 7 2 8 1 9 0 10 0 9 1
9 1 8 2 7 3 6 4 5 5 4 6 3 7 2 8 1 9 0 10 0
```

还是有一些规律的，将结果拆成两个数组，其中 $c1_i=ans_{i\times 2+1},c2_i=ans_{i\times 2}$，将 $c1,c2$ 输出：

```cpp
9 10 9 8 7 6 5 4 3 2 1
0 0 1 2 3 4 5 6 7 8

8 9 10 9 8 7 6 5 4 3 2
1 0 0 1 2 3 4 5 6 7

3 2 1 0 0 1 2 3 4 5 6
7 8 9 10 9 8 7 6 5 4

8 7 6 5 4 3 2 1 0 0 1
2 3 4 5 6 7 8 9 10 9

9 8 7 6 5 4 3 2 1 0 0
1 2 3 4 5 6 7 8 9 10
```

发现两个数组分别由两个等差数列拼接而成，容易通过分类讨论得出等差数列的首项、末项和左右端点，二阶差分即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
int n, a[200005], x[200005], c1[200005], c2[200005];

int p(int x) {
	if (x < 1)
		return x + n;
	if (x > n)
		return x - n;
	return x;
}

void add1(int l, int r, int st, int ed, int d, int tm) {
	if (l > r)
		return;
//	for (int i = l; i <= r; i++) {
//		c1[i] += tm * st;
//		st += d;
//	}
	st *= tm, d *= tm, ed = st + d * (r - l);
	c1[l] += st;
	c1[l + 1] += (d - st);
	c1[r + 1] -= (d + ed);
	c1[r + 2] += ed;
}

void add2(int l, int r, int st, int ed, int d, int tm) {
	if (l > r)
		return;
//	for (int i = l; i <= r; i++) {
//		c2[i] += tm * st;
//		st += d;
//	}
	st *= tm, d *= tm, ed = st + d * (r - l);
	c2[l] += st;
	c2[l + 1] += (d - st);
	c2[r + 1] -= (d + ed);
	c2[r + 2] += ed;
}

void solve() {
	cin >> n;
	int mx = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		mx = max(mx, a[i]);
		x[i] = c1[i] = c2[i] = 0;
	}
	int w = n / 2, n1 = n / 2 + 1, n2 = n / 2;
	for (int i = 1; i <= n; i++) {
		int t = mx - a[i];
		if (i % 2 == 1) {
			add1(1, (i - 1) / 2, w - (i - 1) / 2, w - 1, 1, t);
			int st = w - (n1 - (i + 1) / 2);
			add1((i + 1) / 2, n1, w, st, -1, t);
			//---
			add2((i + 1) / 2, n2, 0, n2 - (i + 1) / 2, 1, t);
			add2(1, (i - 1) / 2, (i - 1) / 2 - 1, 0, -1, t);
		} else {
			add2(1, (i - 1) / 2, w - (i - 1) / 2, w - 1, 1, t);
			int ed = w - (n2 - (i + 1) / 2);
			add2((i + 1) / 2, n2, w, ed, -1, t);
			//---
			add1(i / 2 + 1, n1, 0, n1 - (i / 2 + 1), 1, t);
			add1(1, i / 2, i / 2 - 1, 0, -1, t);
		}
	}
	for (int i = 1; i <= n1; i++)
		c1[i] += c1[i - 1];
	for (int i = 1; i <= n1; i++)
		c1[i] += c1[i - 1];
	for (int i = 1; i <= n2; i++)
		c2[i] += c2[i - 1];
	for (int i = 1; i <= n2; i++)
		c2[i] += c2[i - 1];
	int mn = 1e18;
	for (int i = 1; i <= n; i++) {
		if (i % 2 == 1)
			mn = min(mn, c1[i / 2 + 1]);
		else
			mn = min(mn, c2[i / 2]);
	}
	for (int i = 1; i <= n; i++) {
		if (i % 2 == 1) {
			cout << c1[i / 2 + 1] - mn << " ";
		} else {
			cout << c2[i / 2] - mn << " ";
		}
	}
	cout << "\n";
}

signed main() {
	int T;
	cin >> T;

	while (T--) {
		solve();
	}
}
```

---

## 作者：SunsetLake (赞：1)

## Solution

首先可以考虑每个 $a_i$ 最后会变成什么，记 $v$ 表示答案序列。那么最后的 $a_i$ 就是 $a_i + v_{i - 1} + 2 \times v_i + v_{i + 1}$。由于每个数都相等，于是根据 $a_i,a_{i + 1}$ 得到等式：$a_i + v_{i - 1} + 2 \times v_i + v_{i + 1} = a_{i + 1} + v_{i} + 2 \times v_{i + 1} + v_{i + 2}$，移项变为 $v_{i - 1} + v_i = v_{i + 1} + v_{i + 2} + a_{i + 1} - a_i$。此时再设一个序列 $b_i = v_i + v_{i + 1}$，那么 $b_{i - 1} = b_{i + 1} + a_{i + 1} - a_i$。

也就是求出 $b$ 序列这道题就做完了。怎么求？

先特判掉 $n = 1$ 的情况。注意到每一个 $b_i$ 对应的等式合起来就是一个 N 元一次方程组，解出方程即可。因为 $n$ 是奇数，所以方程关联关系一定是 $1 \to 3 \to \cdots \to n$，再从 $n \to 2 \to 4 \to \cdots \to n - 1 \to 1$，形成一个环。我们可以直接让 $b_1 = 0$ 去解这个方程，若 $v$ 有解，那么沿环绕一圈回来 $b_1$ 一定会等于 $0$。不过这个过程中是没有保证 $b_i \ge 0$ 的，不过注意到对每个 $i \in [1,n]$ 的 $v_i$ 加一个 $1$ 是不影响答案的，于是可以在最后将负数的位置全部加成正数就行了。

当然还要注意一个问题： $\sum\limits_{i = 1}^{n}b_i = \sum\limits_{i = 1}^{n}2 c_i$，所以我们必须保证 $\sum b_i$ 是偶数。若按照 $b_1 = 0$ 解出来的和是奇数，就需要把每个 $b_i$ 加一（$n$ 也是奇数，这样和就是偶数了）。

最后根据 $b_i$ 推出 $c_i$ 即可。

## code


```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N = 2e5 + 5;
int n;
ll a[N],b[N],c[N];
void solve(){
	cin >> n;
	for(int i = 1;i <= n;++ i) cin >> a[i],b[i] = c[i] = 0;
	if(n == 1) return cout << 0 << '\n',void();
	int now = 3;
	while(now != 1){
		int lst = now - 2;
		if(lst == 0) lst = n;
		if(lst == -1) lst = n - 1;
		int kk = lst + 1;
		if(kk == n + 1) kk = 1;
		if(kk == n + 2) kk = 2;
		b[now] = b[lst] + a[kk] - a[now];
		now += 2;
		if(now > n) now -= n;
	}
	if(b[n - 1] + a[n] - a[1] != 0) return cout << -1 << '\n',void();
	ll sum = 0;
	for(int i = 1;i <= n;++ i) sum += b[i];
	if(sum & 1) for(int i = 1;i <= n;++ i) b[i] ++,sum ++;
	sum /= 2;
	for(int i = 2;i <= n;i += 2) sum -= b[i];
	c[1] = sum;
	ll mn = c[1];
	for(int i = 2;i <= n;++ i) c[i] = b[i - 1] - c[i - 1],mn = min(mn,c[i]); 
	for(int i = 1;i <= n;++ i) cout << c[i] - mn << " ";
	cout << '\n'; 
}
int main(){
	int _;
	cin >> _;
	while(_ --) solve();
	return 0;
}
```

---

## 作者：__Louis__ (赞：1)

### 题解：CF2032E Balanced

### 前言

这里介绍一种感觉不像是正解，但又利用了性质的做法。

### 题目大意

有一个循环序列 $A$，可以选择一个数，使其增加 $2$，同时两边的数（因为是循环队列，所以 $a_{n+1} = a_1$）都会加上 $1$。

你需要找到一种方案，使得操作完了以后，$A$ 中的每一个数都相等。

注意 $n$ 为奇数。



### 思路

设 $B_i$ 表示在 $A_i$ 上增加的操作次数，再设 $c$ 表示操作完了以后相等的值的具体数值。

很明显，对于每一个位置有。

$$ c=A_i+B_{i-1}+ B_i \times 2 + B_{i+1}$$

设这个等式叫 $G(i)$，则有

$$G(i)-G(i-1) = A_i-A_{i-1}+ \\B_{i+1}+
B_i-B_{i-1}-B_{i-2}$$

然后我们注意到 $n$ 是奇数，我们试着两个两个往后写一下这个式子。

$$G(i+2)-G(i+1) = A_{i+2}-A_{i+1}\\+ B_{i+3}+
B_{i+2}-B_{i+1}-B_i$$

把这两个式子叠加，我们就又有一个式子。

$$B_{i+3}+ B_{i+2}-B_{i-1}-B_{i-2}\\ =-A_{i+2}+A_{i-1}-A_i+A_{i-1}$$

这个式子可以一直叠加，直到什么时候呢？直到式子左边第一项和最后一项抵消了，那么我们就有这个式子了。

$$ B_{n-1}-B_1=  \sum_{i=1}^{i\le n-1} A_i \times(-1)^{i-1}$$

又因为这是一个循环队列，所以这个递推式子可以移动，直接假设 $B_1$ 为 $0$，递推即可，可以做到复杂度 $O(n)$，只不过需要处理等式右边的值。

如果出现负数，那么给 $B_i$ 全体加一，直到没有负数为止即可。也可以找到最小的负数，然后直接加相反数。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
const int maxn=2e5+10;
int arr[maxn],b[maxn];
int n;
int g(int x){
	return (x+n-1)%n+1;
}
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&arr[i]);
			b[i]=0;
		}
		int sum=0;
		for(int i=1;i<n;i++){
			if(i&1) sum+=arr[i];
			else sum-=arr[i];
		}
		b[n-1]=sum;
		
		for(int i=n-3;i>=-n;i-=2){
			sum-=(arr[g(i+1)]-arr[g(i+2)]);
			sum+=(arr[g(i+2)]-arr[g(i+3)]);
			b[g(i)]=sum+b[g(i+2)];
		}
		int mn=0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=n;i++){
			mn=min(b[i],mn);
		}
		for(int i=1;i<=n;i++){
			printf("%lld ",b[i]+(-mn));
		}
		printf("\n");
//		return 0;
	}
	return 0;
}

```

---

## 作者：MrPython (赞：0)

赛时做不出来一点，赛后补不出来一点，丢给某个小朋友被一下子秒了，赶紧退役吧。

通过惊人的注意力，我们发现：操作 $第(i+2)\bmod n,(i+4)\bmod n,(i+6)\bmod n,\dots,(i-3)\bmod n,(i-1)\bmod n$ 项各一次，其结果为第 $i$ 和 $(i+1)\bmod n$ 项分别增加 $1$、而其余位置分别增加 $2$。在下文中使用“操作 A”指代这一操作。

同时，对所有数操作一遍的结果是所有数等增加 $4$。在下文中使用“操作 B”指代这一操作。

题目并不要求我们的数组最终结果是多少，仅要求所有数都一样。因此，一次操作 A 的结果可以看成“第 $i$ 和 $(i+1)\bmod n$ 项减 $1$，其他位置不变”。

我们还可以对某个数进行 “$-1$ 次操作”，即让第 $(i-1)\bmod n$ 和 $(i+1)\bmod n$ 项减 $1$，第 $i$ 项减 $2$。具体来讲，我们可以对所有数先进行非常多次操作 B（例如 $5\times10^7$ 次），然后将要进行负数次操作的位置少进行一些操作即可。

一次操作 A 的结果可以看成“第 $i$ 和 $(i+1)\bmod n$ 项减 $1$，那一次操作 “-A” 的结果可以看成“第 $i$ 和 $(i+1)\bmod n$ 项加 $1$。现在，我们只需要实现每次相邻两个数 $+1$ 或 $-1$，让数组相等即可。这样就简单多了！

```cpp
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    size_t n;
    fin >> n;
    vector<li> a(n);
    for (li& i : a) fin >> i;
    vector<li> ans(n);
    for (size_t i = 1; i + 1 < n; ++i) {
      li d = a[i - 1] - a[i];
      ans[i] += d;
      a[i] += d;
      a[i + 1] += d;
    }
    for (size_t i = n - 3; i < n; i -= 2) ans[i] += a.back() - a.front();
    li s = accumulate(ans.begin(), ans.end(), 0ll), s0 = ans[0];
    for (size_t i = 1; i < n; i += 2) s0 += ans[i];
    for (size_t i = 0; i < n; ++i) {
      fout << -(s0 - ans[i]) + (uli)1e18 / 2 << ' ';
      s0 = s - s0 + ans[(i + 1) % n];
    }
    fout.put('\n');
  }
  return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
唐题，但是最近是太累了，天天下分。
## 思路分析
首先可以看到重点 $n$ 为**奇数**。

注意抓住这点。

发现操作挺奇怪的是左右 $+1$ 中间 $+2$。

套路的直接差分，发现这东西就相当于在差分数组上 $-1,-1,+1,+1$。

对于相邻的 $-1,+1$ 是非常 ez 的，所以我们考虑给他转化过去。

这是 $n$ 是奇数就用到了。

我们把这些 $-1,-1,+1,+1$ 套在一起，重叠部分恰好是 $-1,-1$ 和 $+1,+1$。

这样绕出来一个环，环长显然是偶数。

而数字成的环是奇环。

所以绕了一圈后就可以把两点加两点减转化成单点加单点减。

因为奇环长度恰好比偶环短 $1$，所以加和减的两个数恰好中间间隔一个数。

所以无解显然是没有的。

然后就变成前面那个问题简单实现即可。

具体的实现可以见代码。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e5+10,V=1e6+10,M=21,INF=1e18,mod=998244353;
int n,ss,a[N],s[N],b[N];
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
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
inline void solve()
{
    n=read();for(int i=1;i<=n;i++) a[i]=read();
    if(n==1) return put("0\n");ss=0;
    for(int i=(2%n)+1,j=1;i!=1;j=i,i=(i+1)%n+1) s[i]=s[j]+(a[(j%n)+1]-a[i]);
    if(s[n-1]+(a[n]-a[1])!=0) return put("-1\n");
    for(int i=1;i<=n;i++) ss+=s[i];int mn=INF;
    if(ss&1) for(int i=1;i<=n;i++) s[i]++,ss++;ss/=2;
    for(int i=2;i<=n;i+=2) ss-=s[i];b[1]=ss;
    for(int i=2;i<=n;i++) b[i]=s[i-1]-b[i-1];
    for(int i=1;i<=n;i++) mn=min(mn,b[i]);
    for(int i=1;i<=n;i++) print(b[i]-mn),put(' '),b[i]=a[i]=s[i]=0;put('\n');
}
signed main()
{
    int T=1;
    T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：BMnya (赞：0)

先特判掉 $n=1$ 的情况。

设最终得到的数列为 $a'_i=a_i+v_{pre_i}+2v_i+v_{nxt_i}$。

这里先不考虑 $v_i\ge 0$ 的限制，如果有负数给最终给每个 $v_i$ 减去 $\min v_i$ 即可。

由于同时给所有 $v_i$ 加减 $1$ 相当于给所有 $a_i$ 加减 $4$，所以如有解一定存在一组解满足 $a_1\le a'_1 < a_1+4$，那么就可以枚举 $a'_1$。

设 $v_1=X,v_2=Y$，可以通过递推 $2\sim n$，用 $X,Y,1$ 的线性组合表示出任意 $v_i$，特别的有：

$$
\left\{
\begin{align*}
  v_n &= -(n-2)X-(n-1)Y+A \\
  v_1 &= (n-1)X+nY+B
\end{align*}
\right.
$$

（这里的 $A,B$ 是递推得到的两个常数），联立：

$$

\left\{
\begin{align*}
  a'_1 &=a_1 + v_n + 2v_1 + v_2 \\
  v_1 &= X
\end{align*}
\right.
$$

可以得到方程组：

$$
\left\{
\begin{align*}
  (4-n)X+(2-n)Y &= a'_1-a_1-A \\
  (2-n)X+(-n)Y &= B
\end{align*}
\right.
$$


解得：

$$
\left\{
\begin{align*}
  X &= \frac{(a'_1-a_1-A)\times (-n)-B\times (2-n)}{(4-n)\times (-n)-(2-n)\times (2-n)} \\ 
  Y &= \frac{(4-n)\times B-(2-n)\times (a'_1-a_1-A)}{(4-n)\times (-n)-(2-n)\times (2-n)}
\end{align*}
\right.
$$

如果此时 $X,Y$ 均为整数，则存在一组解，将 $X,Y$ 代入 $v_1,v_2$ 递推即可得到全部 $v_i$。

---

完整代码见 [提交记录](https://codeforces.com/contest/2032/submission/289289980)。

---

## 作者：AsiraeM (赞：0)

赛时把 increase 看成 decrease，警钟敲烂。

---

接下来记 $a_{x+y}$ 表示在循环序列（即 $a_{n}$ 后面是 $a_{1}$ 的序列）中从 $x$ 出发，向后走 $y$ 步到达的数（例如，$n=5$ 时，$a_{4+3}$ 相当于 $a_2$）。

首先，题目只要求所有数相等，而不要求全部为某个值。因此，可以有一些使整体增加同一个值的操作。  
进行构造，发现对于 $a_{x+1},a_{x+3},\dots,a_{x+n}$ 分别进行一次操作，可以使 $a_x$ 与 $a_{x+1}$ 相对于其他数增加 $1$（如下图），在下文中将这些操作记为一次对于 $a_x$ 与 $a_{x+1}$ 的“操作”。
![图](https://cdn.luogu.com.cn/upload/image_hosting/r13opslk.png)

于是问题转化为进行若干次操作使所有 $a_i$ 相等（因为最后可以把所有 $b_i$ 都加上同一个数，所以先假设 $a_i$ 最终等于 $0$，尽管这会使某些 $b_i$ 为负），设 $b_i$ 表示对与 $a_i$ 与 $a_{i+1}$ 的“操作”次数，$c_i$ 表示 $-a_i$，解以下方程：
$$b_1+b_2=c_2,b_2+b_3=c_3,\dots,b_n+b_1=c_1$$
稍微转化一下，得 $b_2=c_2-b_1,b_3=c_3-b_2=c_3-c_2+b_1$，以此类推，最终得到 $b_n=(-1)^{n-1}b_1+\sum\limits_{i=2}^{n}(-1)^{i-1}c_{i}$，由于 $n$ 为奇数，$(-1)^{n-1}=1$，则 $b_1=-b_1+\sum\limits_{i=1}^{n}(-1)^{i-1}c_{i}$，一定有解，可以解出 $b_1=\frac{\sum\limits_{i=1}^{n}(-1)^{i-1}c_{i}}{2}$，并算出其余的 $b_i$。  
$b_i$ 有可能为小数或负数，但注意到 $b_i$ 只可能全为整数，或全部可以表示为一个整数 $x$ 加上 $\frac12$ 的形式，所以只需要将所有的 $b_i$ 加上同一个数（相当于所有 $a_i$ 都加上同一个数），使得 $b_i$ 全为非负整数即可。

记 $ans$ 表示最终的答案序列。  
每次“操作”被拆分为前后两段，每一段相当于对 $i$ 全为奇/偶的 $ans_i$ 进行区间加（可以结合上面的图片理解），差分一下，统计答案时可以对 $i$ 为奇数与 $i$ 为偶数分别做前缀和。

---

