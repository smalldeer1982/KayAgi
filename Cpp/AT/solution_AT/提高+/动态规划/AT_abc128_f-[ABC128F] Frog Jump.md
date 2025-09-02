# [ABC128F] Frog Jump

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc128/tasks/abc128_f

無限に広がる池があり、数直線とみなせます。この池には $ N $ 個の蓮が浮かんでおり、それらは座標 $ 0,1,2,....N-2,N-1 $ にあります。

あなたは、最初座標$ 0 $ の蓮の上にいます。あなたは、以下の手順に従ってゲームを行うことにしました。

- 1.正の整数 $ A,B $ を決める。得点ははじめ $ 0 $ である。
- 2.現在の位置を $ x $ として、$ y=x+A $とする。$ x $ にある蓮を消して、$ y $ に移動する。
  
  
  - $ y=N-1 $ ならば、ゲームが終了する。
  - そうでなくて、$ y $ に蓮があるならば、得点が $ s_y $ 増加する。
  - そこに蓮がないならば、あなたは溺れる。得点が $ 10^{100} $ 減少して、ゲームが終了する。
- 3.現在の位置を $ x $ として、$ y=x-B $とする。$ x $ にある蓮を消して、$ y $ に移動する。
  
  
  - $ y=N-1 $ ならば、ゲームが終了する。
  - そうでなくて、$ y $ に蓮があるならば、得点が $ s_y $ 増加する。
  - そこに蓮がないならば、あなたは溺れる。得点が $ 10^{100} $ 減少して、ゲームが終了する。
- 4.手順2に戻る。

あなたは、最終得点をできるだけ大きくしたいです。 最適に $ A,B $ の値を決めたときの最終得点はいくらになるでしょうか。

## 说明/提示

### 制約

- $ 3\ \leqq\ N\ \leqq\ 10^5 $
- $ -10^9\ \leqq\ s_i\ \leqq\ 10^9 $
- $ s_0=s_{N-1}=0 $
- 入力はすべて整数である。

### Sample Explanation 1

$ A\ =\ 3,\ B\ =\ 2 $ としたとき、ゲームは次のように進行します。 - 座標 $ 0\ +\ 3\ =\ 3 $ に移動し、得点が $ s_3\ =\ 1 $ 増加する。 - 座標 $ 3\ -\ 2\ =\ 1 $ に移動し、得点が $ s_1\ =\ 2 $ 増加する。 - 座標 $ 1\ +\ 3\ =\ 4 $ に移動し、得点 $ 3 $ でゲームが終了する。 得点 $ 4 $ 以上でゲームを終了することはできないため、答えは $ 3 $ です。座標 $ 2 $ にある蓮に乗ってその後溺れずに済ますことはできないことに注意してください。

### Sample Explanation 2

ここでの最適な戦略は、$ A\ =\ 5 $ を選んで ($ B $ の値は不問) ただちに最後の蓮に乗ることです。

## 样例 #1

### 输入

```
5
0 2 5 1 0```

### 输出

```
3```

## 样例 #2

### 输入

```
6
0 10 -7 -4 -13 0```

### 输出

```
0```

## 样例 #3

### 输入

```
11
0 -4 0 -99 31 14 -15 -39 43 18 0```

### 输出

```
59```

# 题解

## 作者：Erica_N_Contina (赞：4)



# [ABC128F] Frog Jump



## 大意

有一排荷花漂浮于水中，用它们表示一个数列 $s$，坐标 $0$ 到 $n-1$。你现在的分数为 $0$，当前为于坐标 $y=0$。

进行下列操作：

选择两个数 $A$ 和 $B$。

不断执行：设 $y=y+A$，设 $y=y-B$。

每次到达一个 $y$ 有三种情况：

- 若 $y = n-1$ 游戏结束。

- 若 $y \not= n-1$ 且 $y$ 点有荷花，你的分数加上 $s_{i}$。

- 若 $y \not= n-1$ 但否则你淹死，得分 $-INF$，游戏结束。

## 思路

我们考虑每一次会跳到哪个位置。


我们知道，最后我们一定要跳到 $n-1$ 这个点，否则答案为 $0$。并且我们一定是在向右跳了 $A$ 之后到达的 $n-1$，所以我们加上向右跳了 $k+1$ 次，那么 $n-1=A(k+1)-Bk$。整理一下，$n-1=k(A-B)-A$，其中 $k,A-B,A$ 对我们来说是未知量。所以我们考虑枚举其中两个。那就枚举 $k$ 和 $A-B$ 好了。

由于无论怎么跳我们都不能跳出边界，所以 $k(A-B)≤n$。对于每一组操作 $A,B$，我们假设 $A$ 很大，$B$ 很小，那么 $A$ 最大从 $0$ 跳到 $n-2$，$B$ 最小从 $n-2$ 跳到 $n-3$（如果 $A$ 直接跳到 $n-1$ 那么游戏结束，得分为 $0$）

所以我们枚举 $A-B$ 从 $1$ 到 $n-3$，然后对于每一组操作，我们都可以向右前进 $A-B$，所以 $k$ 枚举到 $(n-1)\div(A-B)$ 即可。我们也可以直接计算出 $A=n-1-k(A-B)$。

我们再次考虑每一次会跳到哪个位置。我们可以发现，是两个很明显的等差数列，且只和 $k,A-B$ 有关。

所以当 $A-B$ 确定时，当 $k$ 增加 $1$ 时，我们会多跳到点 $k(A-B)$ 和点 $n-1-k(A-B)$（你把两个等差数列拎出来，代入 $k$ 和 $k+1$ 自己看看区别就知道了），所以我们从 $k-1$ 转移到 $k$ 时，只需要在之前求出来的 $ans$ 上加上 $k(A-B)$ 和点 $n-1-k(A-B)$ 的值即可。

当然，在枚举 $k$ 计算出 $A$ 时，如果 $A≤(A-B)$，那么应该及时 `break`。若 $A$ 可以被 $(A-B)$ 整除（即每一组操作会向右跳 $tA\ (t\in \Z^+,t>1)$ 单位），那么当 $(t+1)≤k$，即 $t<k$ 时，也要 `break`。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . CCode by Ntsc .
       . Fancy Chargcy .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=1e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,m,ans;
int a[N],b[N];


signed main(){
	cin>>n;
	
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	
	
	for(int i=1;i<=n-3;i++){
		int res=0;
		for(int k=1;k<=(n-1)/i;k++){
			int A=n-1-k*i;
			if(A<=i||(A%i==0&&A/i<=k))break;
			res+=a[k*i]+a[n-1-k*i];
			ans=max(ans,res);
		}
	}
	
	cout<<ans<<endl;
	return 0;
}
```






---

## 作者：MSqwq (赞：4)

也是一个好题了，难度感觉不止绿了。  
形象化每个操作那么就是：  
$0\ \ A\ \ A-B\ \ 2 A-B\ \ 2(A+B)\ ...\ n-1-(A+B)\ \ n-1$。  
那么可以发现奇数步就是加上一个 $k\times(A+B)$，偶数步就是在前一步多加一个 $A$。
那么假如把 $A-B$ 看出一个整体，因为是一个周期的结束，也是每个周期是步长嘛，来进行讨论把奇数布和偶数布分成两列看，就变成了。   
$0\ \ x\ \ 2x\ \ 3x\ ......$  
$......\ n-1-2x\ \ n-1-x\ \ n-1$  
哇！这不两个等差数列嘛，一个正着的，一个倒着的，而且放眼整个问题，就是上面，然后跳到下面，再跳到上面，再跳下来，一直往返，直到最后跳到 $n-1$。那么上下步骤一样多，那么我们枚举这个 $x$，再模拟跳的过程，因为只需要枚举一半嘛，所以复杂的就是 $\sum\limits_{x-1}^n\lfloor \frac{n}{k} \rfloor$，约等于 $O(n\log n)$ 非常快，而且非常好写。  
代码如下：  
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=1e5+10;
ll a[N];
int main()
{
	int n=read();
	for(int i=0;i<n;i++)a[i]=read();
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		ll sum=0;
		for(int p=i;p<=n-1;p+=i)
		{
			int r=n-1-p;
			if(r<=i)break;
			sum+=a[p]+a[n-1-p];
			if(r%i!=0||p<r)ans=max(ans,sum);
		}
	}
	cout<<ans<<endl; 
	return 0;
}

```


---

## 作者：Sky_Maths (赞：3)

提供一种丑陋做法。

最终得到 $(0, A)|(A - B, 2A - B)\cdots$ 的序列，将 $(0, A)$ 视为第 $1$ 组。

与 $n - 1$ 重合，即 $x(A - B) + B = n - 1$，有 $B = n - 1 - x(A - B)$。

枚举 $d = A - B$，对于每个 $d$，枚举 $x$ 从而求出 $B$。

发现还需满足不走回头路，$(y - 1)(A - B) = A$，其中 $y$ 表示在第 $y$ 组重合，若 $y 
\le x,A - B|A$，这组 $A, B$ 不满足条件。

发现作为一个有 $n$ 种差值的等差数列，求和是 $O(n^2)$ 的，考虑数据分治，做到 $O(n\sqrt{n\log n})$ 常数很小，可以通过。

另一种做法就是考虑最终都会到达 $n - 1$，从 $n - 1$ 倒推，可以做到 $O(n\ln n)$。

[代码](https://atcoder.jp/contests/abc128/submissions/53224122)

---

## 作者：μηδσ (赞：3)

## Definition

给定长度为$N$的序列$s_0,s_1,s_2,\cdots s_{N-1}$现在要选取两个正整数$A$和$B$，从$s_0$七条，安好线往前条$A$步，再往后跳$B$步的规则正好跳到$s_{N-1}$每跳到一个地方，其所对应的元素值将会计入你的总分。有如下限制：

1.不能跳出序列

2.同一个地方只能被跳一次

请选适当的$A$和$B$，使得得分最大

## Solution

假设跳了k次B，那么$s_{A-B}, s_{2*(A-B)}, \dots, s_{k*(A-B)}$为每次跳 B 步后所能到达的点。而$s_{N-1 - (A-B)}, s_{N-1 - 2*(A-B)}, \dots, s_{N-1 - k*(A-B)}$为每次跳 A 步后所能到达的点。

于是我们可以暴力枚举所有的 A - B 和 k，复杂度大概为$O(N*(1 + \frac{1}{2} + \frac{1}{3} + \dots + \frac{1}{N}))$，大概是O(nlogn)的。

思路大概就是这样了

## Code

~~~cpp
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>

#define rep(a, b, c) for(int a = b;a <= c;a++)
#define per(q, b, c) for(int a = b;a >= c;a--)

using namespace std;
typedef long long ll;
typedef double ld;

const int MAXN = 400005;

int N, s[MAXN];
ll ans;

int main(){
    cin >> N;							//输入长度N 
    rep(i, 0, N - 1) 
		cin >> s[i];					//输入对应元素所对的积分 
    rep(i, 1, N - 3){					//循环枚举A和B 
        ll ret = 0;
        rep(k, 1, (N - 1) / i){
            ll tmp = N - 1 - i * k;
            if(tmp <= i || tmp % i == 0 && tmp / i <= k) 	
				break;
            ret += s[i * k] + s[tmp];
            ans = max(ans, ret);
        }
    }
    cout << ans << endl;				//输出答案 
    return 0;
}
~~~

---

## 作者：elbissoPtImaerD (赞：2)

绿色的 2400？  
挠头。

首先需要明确：一定是跳了奇数步到 $n-1$，否则就落水了。

$n-1$ 太丑了，不妨记作 $n$ 吧。

一次跳两步显然可以拆开来看：

把形如 $(iA-(i-1)B,iA-iB)$ 一次两跳的位置拆成 $iA-(i-1)B$ 和 $iA-iB$ 两组。

如果这不够明显的话我们换元：$C=A-B$。  
那么两组便是 $A+iC$ 和 $iC$ 的形式。

等差数列！

不妨把跳跃的轮数记为 $D$，那么一条路径的权值就是：$\sum\limits_{i=0}^D({s_{A+(i-1)C}+s_{iC}})+s_n$。

但还是有三个未知数才能刻画一条路径，还要消元。

我们遗漏了以 $n$ 为终点这个约束：$A+CD=n$。  
这样就可以把 $A$ 消去。

和式变形为：$\sum\limits_{i=0}^D(a_{iC}+a_{n-iC})$。

可以先枚举 $C$ 再枚举 $D$ 递推求得。

复杂度 $\mathcal{O(n\ln n)}$。

注意删去不合法的路径。

```cpp
const int N=1e5+3;
bool*MS;
int n,a[N];
bool b[N];
LL ans;
bool*MT;
il void Solve()
{
  rd(n),--n;
  for(int i=0;i<n;++i) rd(a[i]);
  for(int i=1;i<=n;++i)
  {
    LL s=0;
    for(int j=i;j<n;j+=i)
    {
      if(b[j]||b[n-j]||j==n-j||n-j<i) break;
      b[j]=b[n-j]=true,cx(ans,s+=a[j]+a[n-j]);
    }
    for(int j=i;j<n;j+=i) b[j]=b[n-j]=false;
  }
  wrt(ans);
  return;
}
```

---

## 作者：cosf (赞：2)

## [ABC128F](https://www.luogu.com.cn/problem/AT_abc128_f)

校内模拟赛做到这题，很快切了。

---

令 $d = a - b$。则它跳到的点一定是两个等差数列：

$$
\begin{cases}
a, &a + d, &a + 2d, &\dots, &a+kd\\
0, &d, &2d, &\dots, &kd\\
\end{cases}
$$

显然，它走的顺序是 $0, a, d, a + d, 2d, \dots$，结束在 $a+kd$，也就是说，$a+kd$ 就是 $n-1$。

我们可以枚举 $d$，显然符合要求的 $a$ 只有 $O(\frac{n}{d})$ 个，并且，它们是 $n - 1, n - 1 - d, \dots, n - 1 - kd$。

如果 $a=n-1$，显然答案就是 $0$，否则，可以从 $a' = a + d$ 递推得来。

观察等差数列，发现多了的两项就是 $kd$ 和 $a$。只要这两个和原来的数列中没有重复，就可以更新答案。

判断重复：只要 $(k-1)d, kd, a$ 中没有相同即可。证明略。

## 代码

```cpp
#include <iostream>
using namespace std;

#define MAXN 100005

using ll = long long;

int n;

ll val[MAXN];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> val[i];
    }
    ll res = 0;
    for (int d = 1; d < n; d++) // a - b
    {
        ll sr = 0;
        ll cr = 0;
        int k = -d;
        for (int j = n - 1; j > d; j -= d) // a
        {
            if (j == k)
            {
                break;
            }
            k += d;
            if (j == k)
            {
                break;
            }
            sr += val[j];
            if (k > -1)
            {
                sr += val[k];
            }
            cr = max(cr, sr);
        }
        res = max(res, cr);
    }
    cout << res << endl;
    return 0;
}

```

---

## 作者：qwerty12346 (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc128_f)

## 题意

就是求所能达到的最大分数。

## 思路

循环枚举 $A-B$ 和 $k$ 的值。然后每一次 $f_{i}$ 加上一组前面算的值，最后输出最大值。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ret,a[1000005],f[1000005];
int main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=1;i<=n-3;i++)
    {
        for(int j=1;j<=(n-1)/i;j++)
        {
            long long k=n-1-j*i;
            if(k<=i||(k%i==0&&k/i<=j))break;//特判
            f[i]+=a[i*j]+a[k];//算f[i]的值
            ret=max(ret,f[i]);//找最大值
        }
    }
    cout<<ret<<endl;
    return 0;
}
```


---

## 作者：yinpeichu2021 (赞：1)


[题目链接](https://www.luogu.com.cn/problem/AT4288)

# 简短题意

以每 $2$ 次为一组，第一次往右移 $A$ 步，第二次往左移 $B$ 步，最终到达 $N-1$ 这个点。

# sol
设共跳了 $k$ 组步数，则每一次能到的点如下表所示

||往左移 $B$ 步能到的点(由左至右)|往右移 $A$ 步能到的点(由右至左)|
|-|-|-|
|**1**|$s_{1\times(A-B)}$|$s_{n-1-1\times(A-B)}$|
|**2**|$s_{2\times(A-B)}$|$s_{n-1-2\times(A-B)}$|
|**3**|$s_{3\times(A-B)}$|$s_{n-1-3\times(A-B)}$|
|$\dots$|$\dots$|$\dots$|
|**4**|$s_{k\times(A-B)}$|$s_{n-1-k\times(A-B)}$|


可以发现，其中 $A-B$ 和 $k$ 是未知的。
我们可以枚举 $A-B$ 和 $k$，每一次 $sum$ 加上一组(即上表中每一行前后两个数)前面算的，并求出 $max$。

# code

```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗！
using namespace std;
int n,a[200005],ans;
signed main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];//数组下标从0开始
    for(int i=1;i<=n-3;i++){//第一次跳A步最少跳到n-1-1，再跳B步最大跳到n-1-1-1=n-3。
        int sum=0;
        for(int k=1;k<=(n-1)/i;k++){
            int tem=n-1-k*i;//往右移A步到的位置
            if(tem<=i||(tem%i==0&&tem/i<=k))break;//当他下一次再往左跳就要出界时，或已经与左移B步的重复了，就退出。
            sum+=a[i*k]+a[tem];
            ans=max(ans,sum);
        }
    }
    cout<<ans;
    return 0;
}
```



---

## 作者：Kketchup (赞：0)

### [[ABC128F] Frog Jump](https://atcoder.jp/contests/abc128/tasks/abc128_f)

- Ad-hoc

**Sol:** 首先，我们一定要跳到 $n-1$，否则答案是 $0$。那么类似小学青蛙跳水井，令 $k$ 是往回跳次数，$A\times(k+1)-B\times k=n-1$，即 $k\times (A-B)+A=n-1$。三个未知数，我们任意枚举两个，可以算出第三个，这里枚举 $k$ 和 $A-B$。

注意枚举范围，$A-B$ 最小值显然为 $1$，最大值考虑 $B$ 最小值为 $1$，而 $A$ 最大值为 $n-2$（因为一步直接到 $n-1$ 答案是 $0$），所以 $A-B$ 最大值为 $n-3$。而我们最大跳到 $n-1$，所以 $k$ 的最大值为 $\left\lfloor\frac{n-1}{A-B}\right\rfloor$。容易算出 $A=n-1-k\times(A-B)$。

接下来考虑跳到的位置：假设跳了 $i-1$ 轮前后，再跳一次前会到达 $A+(i-1)\times (A-B)$，跳一次后会到达 $i\times (A-B)$，这是两个等差数列。所以从 $i-1$ 转移到 $i$，答案加上 $i\times (A-B)$ 和 $n-1-i\times (A-B)$。

注意边界条件，若 $A\le(A-B)$，此时 $B\le 0$ 不符合条件；若 $(A-B)|A$，且 $\frac{A}{A-B}<k$，即会在前 $k$ 轮走到重复点，都是不符合的。时间复杂度是大约是调和，$O(n\log n)$ 级别。

**Trick:** 观察到达点构成等差数列，并只有单项转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define F(i,x,y) for(int i=(x);i<=(y);++i)
#define Fo(i,x,y) for(int i=(x);i>=(y);--i)
const int N=2e5+10;
#define int ll
int n,ans;
int a[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=0;i<n;++i) cin>>a[i];
    for(int i=1;i<=n-3;++i){
        int res=0;
        for(int k=1;k<=(n-1)/i;++k){
            int A=n-1-k*i;
            if(A<=i||(A%i==0&&A/i<=k)) break;
            res+=a[k*i]+a[n-1-k*i];
            ans=max(ans,res);
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Ming_dao (赞：0)

- 题目简单明了，说一只青蛙从坐标为 $0$ 跳到坐标为 $n-1$。它可以向前跳 $A$ 格也可以向后跳 $B$ 格。每次跳到的位置不能再跳第二遍，除开始和终点的权值为 $0$ 其他位置的权值当青蛙位于时，便累加上。
求最大的权值。
   

  本题体现的了数的可拆分和可合并性。

  考虑把走过的路径写成如下形式：
  $$
  0,A,A-B,2A-B\dots \\
  \dots n-1-(A-B),n-1-A,n-1
  $$
  也就是说，我们把所有经过的点拆成了如下形式：$A+i(A-B)$。

  显然，最后一步是由 $A$ 来完成的，换言之可以到达终点的做法都可以认为是走了奇数步。

  不妨将所有经过的点列出来：

  $A,2A,3A\dots$ 和 $n-1-(A-B),n-1-2(A-B)\dots$

  显然的等差数列。

- 然后就做完了，枚举 $(A-B)$ 然后统计答案。

- 复杂度接近 $O(n\log n)$ 能过！

---

## 作者：Mirasycle (赞：0)

最暴力的思路就是枚举 $A$ 和 $B$，然后统计。复杂为 $O(n^2 \log n)$。一般来说为了简化计算可以只枚举其中一个端点剩下一个端点可以放在一起计算减少重复计算。这题不太方便这么做，但是思路也是类似的。可以画一下图，模拟一下跳的过程。然后发现 $A-B$ 为一个周期。注意点的分类，奇数步为从终点开始的 $A-B$ 往回眺，偶数步为从起点开始的 $A-B$ 往前跳，于是就可以列出答案式子
 $$ \sum\limits_{i=0}^k a_{i \times (A-B)}+a_{n-i \times (A-B)} $$
 发现这次枚举的是 $A-B$ 就可以了，而且这样子每个答案计算式子中就有重合部分了可以前缀和减少重复计算，因为 $A$ 的不同决定了第 $k$ 个周期后跳到终点，于是 $k$ 取任意一个合法的数都可以对答案产生贡献。

---

## 作者：封禁用户 (赞：0)

## 前言：
竟然有如此水的蓝题。

## 思路：

本道题目就是让我们求出所能达到的最大分数。

循环枚举 $A-B$ 和 $k$ 的值。然后每一次 $f_{i}$ 加前一组前面算的值。

最后输出 $sum$ 即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=1000005;
long long n,sum=0,a[N],b[N];

int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(long long i=0;i<n;i++)
	{
		cin >> a[i];
	} 
	for(long long i=1;i<=n-3;i++)
	{
		for(long long j=1;j<=(n-1)/i;j++)
		{
			long long ans=n-1-j*i;
			if(ans<=i||(ans%i==0 && ans/i<=j))
			{
				break;
			}
			b[i]+=a[i*j]+a[ans];
			sum=max(sum,b[i]);
		}
	}
	cout << sum << endl;
	return 0;
}
``````

---

