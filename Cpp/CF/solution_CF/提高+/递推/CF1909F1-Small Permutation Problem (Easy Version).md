# Small Permutation Problem (Easy Version)

## 题目描述

[Andy Tunstall - MiniBoss](https://soundcloud.com/tunners/miniboss)

⠀



In the easy version, the $ a_i $ are in the range $ [0, n] $ ; in the hard version, the $ a_i $ are in the range $ [-1, n] $ and the definition of good permutation is slightly different. You can make hacks only if all versions of the problem are solved.

You are given an integer $ n $ and an array $ a_1, a_2 \dots, a_n $ of integers in the range $ [0, n] $ .

A permutation $ p_1, p_2, \dots, p_n $ of $ [1, 2, \dots, n] $ is good if, for each $ i $ , the following condition is true:

- the number of values $ \leq i $ in $ [p_1, p_2, \dots, p_i] $ is exactly $ a_i $ .

Count the good permutations of $ [1, 2, \dots, n] $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the only good permutation is $ [1, 2, 3, 4, 5] $ .

In the second test case, there are $ 4 $ good permutations: $ [2, 1, 5, 6, 3, 4] $ , $ [2, 1, 5, 6, 4, 3] $ , $ [2, 1, 6, 5, 3, 4] $ , $ [2, 1, 6, 5, 4, 3] $ . For example, $ [2, 1, 5, 6, 3, 4] $ is good because:

- $ a_1 = 0 $ , and there are $ 0 $ values $ \leq 1 $ in $ [p_1] = [2] $ ;
- $ a_2 = 2 $ , and there are $ 2 $ values $ \leq 2 $ in $ [p_1, p_2] = [2, 1] $ ;
- $ a_3 = 2 $ , and there are $ 2 $ values $ \leq 3 $ in $ [p_1, p_2, p_3] = [2, 1, 5] $ ;
- $ a_4 = 2 $ , and there are $ 2 $ values $ \leq 4 $ in $ [p_1, p_2, p_3, p_4] = [2, 1, 5, 6] $ ;
- $ a_5 = 4 $ , and there are $ 4 $ values $ \leq 5 $ in $ [p_1, p_2, p_3, p_4, p_5] = [2, 1, 5, 6, 3] $ ;
- $ a_6 = 6 $ , and there are $ 6 $ values $ \leq 6 $ in $ [p_1, p_2, p_3, p_4, p_5, p_6] = [2, 1, 5, 6, 3, 4] $ .

In the third test case, there are no good permutations, because there are no permutations with $ a_6 = 5 $ values $ \leq 6 $ in $ [p_1, p_2, p_3, p_4, p_5, p_6] $ .

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
6
0 2 2 2 4 6
6
0 1 3 4 5 5
6
1 2 3 2 4 6
15
0 0 1 1 1 2 3 4 5 6 7 9 11 13 15```

### 输出

```
1
4
0
0
532305727```

# 题解

## 作者：ForgotDream_CHN (赞：18)

 **UPD on 2024.01.04：换了个图床，望过审。**

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17926475.html)

> 给定一个长度为 $n$ 的数组 $a$，其中 $a_i \in [1, n]$，试计算满足以下条件的 $[1, n]$ 的排列 $p$ 的个数：
>
> + $\forall i \in [1, n], \sum_{1 \le j \le i} [p_j \le i] = a_i$
>
> $n \le 2 \times 10^5$。

图是拿 Excel 画得，有点丑，请见谅。

将 $(i, p_i)$ 视为二维平面上的点，则 $a_i$ 的限制就等价于在原点到点 $(i, i)$ 的正方形内一共填了 $a_i$ 个数字。

举个例子：

![](https://www.z4请更换图床a.net/images/2024/01/04/image4ffb59d7bbb667ce.png)

假设我们已经填完了前 $5$ 个位置的数，现在要填 $i = 6$ 的情况。设 $a_5 = 3, a_6 = 5$，那也就是说我们要在红色的 L 形区域中填两个数。

而 $p$ 是排列，且一个位置只能填一个数字，因此我们可以得到，已填数字的横坐标是互异的，其纵坐标也是互异的。那么也就是说，在这个红色的 L 形区域中，我们最多也只能填两个数字。否则就一定会出现某两个数字横坐标或者纵坐标相等的情况。因此我们得到，若设 $a_0 = 0$ 则 $\forall i \in [i, n], a_i - a_{i - 1} \in \{0, 1, 2\}$。

但是是不是所有的红色格子里都能填数字呢？也不是。由于需要满足之前的限制，因此此时在横坐标 $[1, i - 1]$ 的范围里，已经有 $a_{i - 1}$ 个纵坐标 $\in [1, i - 1]$ 的格子被占用了。再用上边的数据举个例子：

![](https://www.z4请更换图床a.net/images/2024/01/04/image292808d5a69b29cf.png)

假设此时为了满足 $a_5 = 3$ 的限制，我们在 $(1, 1), (3, 2), (5, 4)$ 这三个点上填上了数字，那么显然，此时横坐标为 $1, 3, 5$，纵坐标为 $1, 2, 4$ 的格子就都不可用了，剩下的位置只有 $5$ 个是可用的了。

记 $d_i = a_i - a_{i - 1}$，那么我们此时就可以开始分类讨论了：

+ 若 $d_i = 0$，则不需要填数字，方案数不变。
+ 若 $d_i = 1$，则需要填一个数字，方案数为 $2(i - a_{i - 1}) - 1$。
+ 若 $d_i = 2$，则需要填两个数字，且此时 $(i, i)$ 是不能填的，否则就只能填一个数字了，因此方案数为 $(i - a_{i - 1} - 1)^2$。

这样就可以做到时空复杂度线性了！

无解的话，判断一下 $d$ 的大小和 $a_n$ 是否为 $n$ 以及 $a_1$ 是否 $\le 1$ 就行了吧

[Code](https://codeforces.com/contest/1909/submission/238796315)


---

## 作者：myyyIisq2R (赞：6)

考虑将 $a_i$ 差分，思考意义，可以将 $a_i$ 放在二维平面的棋盘格上，第 $i$ 列表示第 $i$ 个位置，第 $i$ 行表示元素的值，而排列中的元素就是可以放在棋盘上的点，每个点对应一个数。发现 $a_i-a_{i-1}$ 为“排列前 $i-1$ 位大于 $i-1$ 的数和排列第 $i$ 位的数”即一个 $(1,i)$ 连到 $(i,i)$ 再连到 $(i,1)$ 的 $L$ 形区域。又因为排列的意义等同于每行每列只能放一个数，因此这个 $L$ 形区域里至多放两个数，即 $a_i - a_{i-1} \le 2$，分情况讨论（设可以放置的空行空列个数为 $k$)：

- 当 $a_i-a_{i-1} = 0$ 时，说明 $L$ 形区域没放元素，即可被放置元素的空行空列增加，$k \Leftarrow k+1$。

- 当 $a_i - a_{i-1} = 1$ 时，说明在 $L$ 形区域中放了一个元素，可以在之前统计出的空行空列中挑一行或一列放置，并且也可以在 $L$ 形拐角放置，$ans \Leftarrow ans \times (2k+1)$。
- 当 $a_i - a_{i-1} = 2$ 时，说明在 $L$ 形区域中放了两个元素，即在第 $i$ 行的空余格子内选一个，在第 $i$ 列空余格子内再选一个，共 $k^2$ 种，$ans \Leftarrow ans \times k^2$，$k \Leftarrow k-1$。

线性递推统计答案。

```cpp
inline void work()
{
	n = read();
	a.resize(n+1);
	for(int i{1};i<=n;i++) a[i] = read();
	if(a[n] != n) {puts("0");return;}
	for(int i{1};i<=n;i++) if(a[i] > i) {puts("0");return;}
	int ans{1},k{};
	for(int i{1};i<=n;i++)
	{
		if(a[i] - a[i-1] == 0) k++;
		else if(a[i] - a[i-1] == 1) ans = ans * (2*k + 1) % MOD;
		else if(a[i] - a[i-1] == 2) (ans *= k * k % MOD) %= MOD,k--;
		else ans = 0;
	}
	writeln(ans);
}
```

---

## 作者：_LiWenX_ (赞：3)

计数题。

首先，发现排列中的一个数 $p_i$ 对序列 $a$ 的贡献一定为一段后缀，所以直接把序列 $a$ 给差分掉，得到的序列为 $c$。

然后就可以比较方便的转换一下题意，对于数字 $i$，我们可以在 $\max(p_i,i)$ 上 $+1$，然后构造排列 $p$，将整个序列变为 $c$，求方案数。

而此时 $a_i$ 的含义就是前 $i$ 个位置中已经有 $a_i$ 个被 $1\sim i$ 的数填过了。

首先特判掉一些显然无解的地方：

- 存在 $c_i<0$，这个显然。

- 存在 $a_i>i$，这个显然。

- $a_n\not =n$ 这个还是显然。

- 存在 $c_i>2$，这是因为 $\max(p_x,x)$ 要么是 $p_x$ 贡献到了 $i$ 上，要么是 $x$ 贡献到 $i$，一个位置至多贡献两次

对于其余情况，我们从左向右考虑填满一个位置。

设我们填到了 $i$，在 $1\sim i$ 中有 $s$ 个数是还没有决定填在哪里的，我们可以通过分类讨论求出答案。

- $c_i=0$，啥也不用干，因为这次不存在一个地方贡献到了 $i$ 上。

- $c_i=1$，分两种情况，要么是 $i$ 放到了 $1\sim i-1$ 的地方，这种方案数为 $i-1-a_{i-1}$，要么是把 $s$ 中的一个数放到了 $i$ 上，这种方案数就是 $s$，那么总方案就是把它们加起来，把答案乘上 $i-1-a_{i-1}+s$ 即可。

- $c_i=2$，对于这种情况，发现你必须把 $i$ 放到 $1\sim i-1$ 的一个位置而且还要把 $s-1$（去除掉其中放过的 $i$）中的一个数放到 $i$ 上，所以把答案乘上 $(i-1-a_{i-1})\times (s-1)$ 即可。

记得每次都把 $s$ 更新一下就完事了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int tt,n;
int a[200001],b[200001];
signed main(){
	cin>>tt;
	while(tt--){
		cin>>n;
		bool flag=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[i]=a[i]-a[i-1];
			if(b[i]<0||b[i]>2||a[i]>i){
				flag=1;
			}
		}
		if(a[n]!=n||flag){
			cout<<0<<'\n';
			continue;
		}
		int ans=1,s=0;
		for(int i=1;i<=n;i++){
			s++;
			if(b[i]==2){
				ans=ans*(i-1-a[i-1])%mod*(s-1)%mod;
			}
			else if(b[i]==1){
				ans=ans*(i-1-a[i-1]+s)%mod;
			}
			s-=b[i];
		} 
		cout<<ans<<'\n';
	}
}
```




---

## 作者：lyhqwq (赞：2)

# Solution

挺厉害的一个题。

显然只有 $[1,i]$ 的数会对 $a_i$ 有影响，我们不妨在填到 $i$ 的时候只把 $[1,i]$ 填好并计算方案数，剩下的会在填 $[i+1,n]$ 的时候考虑。

考虑 $p_i$ 的影响，即 $a_i-a_{i-1}$。

若 $a_i-a_{i-1}=0$，有 $p_i>i$，根据我们之前的结论，答案不变。

若 $a_i-a_{i-1}=1$，一定是 $i$ 填在了 $[1,i-1]$ 上的空位或者 $[1,i]$ 中剩下的数字填在了 $i$ 上，空位有 $i-1-a_{i-1}$ 个，剩下 $i-a_{i-1}$ 个数字，答案要乘上 $2(i-a_{i-1})-1$。

若 $a_i-a_{i-1}=2$，一定是 $i$ 填在了 $[1,i-1]$ 上且 $[1,i-1]$ 填在了 $i$ 上，答案要乘上 $(i-a_{i-1}-1)^2$。

递推即可。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int Mod=998244353;
int _;
int n;
int a[N];
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int ans=1;
    if(a[1]>1) return puts("0"),void();
    for(int i=1;i<=n;i++){
        int d=a[i]-a[i-1];
        if(d<0||d>2) return puts("0"),void();
        if(!d) continue;
        if(d==1) ans=1ll*ans*(2*(i-a[i-1])-1)%Mod;
        else ans=1ll*ans*(i-1-a[i-1])%Mod*(i-1-a[i-1])%Mod;
    }
    if(a[n]!=n) return puts("0"),void();
    printf("%d\n",ans);
}
int main(){
    scanf("%d",&_);
    while(_--) solve();
    return 0;
}

```

---

## 作者：_yi_ (赞：2)

# 题意简述

给定一个长度为 $ n $ 的序列 $ a $，其中 $ 0 \le a_i \le n $。需要求出有多少个长度为 $ n $ 的排列 $ p $，满足对于任意的 $ 1 \le i \le n $，$ \sum_{j=1}^i [p_j \le i] = a_i $。换句话说，对于每个位置 $ i $，排列 $ p $ 中小于等于 $ i $ 的数的个数应该正好是 $ a_i $。输出结果对 $ 998244353 $ 取模。有多组测试数据，每组数据包含一个 $ n $ 和一个序列 $ a $。

# 解题思路

首先，若将 $ p_i $ 转化为点对 $ (i,p_i) $，则 $ a_i $ 描述的是横坐标小于 $i$，纵坐标小于 $ a_i $ 的点的个数。

不难发现，$ 0 \le a_i - a_{i-1} \le 2$（最多新的一列和新的一行分别多出一个点对），否则没有答案。

- 当 $ a_i = 0 $，则代表没有增加任何点对，答案不变。
- 当 $ a_i = 1 $，则代表增加了一个点对，有 $2 \times i - 1 - 2 \times a_{i-1}$ 种可能的选择，将其乘入答案。
- 当 $ a_i = 2 $，则代表增加了两个点对，每个点有 $i - 1 - a_{i-1}$ 可能的选择，将其的平方乘入答案。

最后，将答案对 $ 998244353 $ 取模即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
void read(T &x){
    char c; bool f = 0;
    while(((c = getchar()) < '0' || c > '9') && c != '-');
    if(c == '-'){f = 1; c = getchar();}
    x = c - '0';
    while((c = getchar()) >= '0' && c <= '9')x = x * 10 + c - '0';
    if(f) x = -x;
}
template <typename T>
void write(T x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9)write(x / 10);
    putchar(x % 10 + '0');
}
const ll mod=998244353;
int main(){
    int T;
    read(T);
    while(T--){
        int n;
        read(n);
        int *a=new int[n+2];
        for(int i=1;i<=n;i++){
            read(a[i]);
        }
        if(a[n]!=n){
            write(0);
            putchar('\n');
            delete[] a;
            continue;
        }
        int last=0;
        ll ans=1;
        for(int i=1;i<=n;i++){
            if(a[i]-last>2||a[i]-last<0){
                ans=0;
                break;
            }
            if(a[i]-last==1){
                if(2*i-2*last-1<0){
                    ans=0;
                    break;
                }
                ans=ans*(2*i-2*last-1)%mod;
            }
            else if(a[i]-last==2){
                if(i-1-last<0){
                    ans=0;
                    break;
                }
                ans=ans*(i-1-last)%mod*(i-1-last)%mod;
            }
            last=a[i];
        }
        write(ans);
        putchar('\n');
        delete[] a;
    }
    return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

感觉这个题还是挺不错的。

考虑 F1。考察 $a_i$ 差分后的意义，发现 $a_i - a_{i - 1}$ 就是 $(\sum\limits_{j = 1}^{i - 1} [p_j = i]) + p_i \le i$。

考虑将其转化为棋盘问题。在 $(i, p_i)$ 放一个车，那么 $a_i - a_{i - 1}$ 就是 $(1, i) \sim (i, i)$ 和 $(i, 1) \sim (i, i - 1)$ 这些格子组成的“L”字形的车的数量。

一个放车的方案合法当且仅当所有车互不攻击。因此容易发现合法的 $a_i - a_{i - 1}$ 一定 $\in [0, 2]$。考虑从前往后扫，同时维护答案 $ans$ 和现在还没被占用的行（列）数量 $t$。

- 若 $a_i = a_{i - 1}$，无事发生，多了第 $i$ 行和列没被占用，因此 $t \gets t + 1$。
- 若 $a_i - a_{i - 1} = 1$，相当于可以在 $(1, i) \sim (i - 1, i)$ 和 $(i, 1) \sim (i, i - 1)$ 中还没被占用的格子放车，同时也可以在 $(i, i)$ 放车，那么 $ans \gets ans \times (2t + 1)$，$t$ 不变。
- 若 $a_i - a_{i - 1} = 2$，$(1, i) \sim (i - 1, i)$ 和 $(i, 1) \sim (i, i - 1)$ 中还没被占用的格子各放一个车，那么 $ans \gets ans \times t^2$，然后 $t \gets t - 1$。

如上讨论可以[通过 F1](https://codeforces.com/contest/1909/submission/238617437)。

---

## 作者：Unnamed114514 (赞：0)

你把它抽象成一个棋盘，每个 $p_i$ 的坐标想象成一个棋子 $(i,p_i)$，相当于不能有两个棋子在同一行/同一列。

那么 $a_i$ 就是 $(i,i)$ 左上角的棋子数。

然后每次加一行加一列，所以最多加两个且一定不会减少，即 $0\le a_i-a_{i-1}\le2$。

对 $d=a_i-a_{i-1}$ 分类讨论：

- $d=0$：都不加，只有 $1$ 种方案。

- $d=1$：新增的一行和一列加一个都行，乘上 $2(i-1-a_{i-1})+1$。

- $d=2$：多的行和多的列都放一个，交界处不能放，即 $(i-1-a_{i-1})^2$。

$d=1/2$ 的时候记得减去前面已经占用的行数/列数。

然后 $a_n$ 总棋子数没达到 $n$ 单独特判输出 $0$，样例提示中就已经说了这种情况。

---

