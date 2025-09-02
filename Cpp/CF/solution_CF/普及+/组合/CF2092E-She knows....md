# She knows...

## 题目描述

D. Pippy 正在为家中的"黑白派对"做准备。他只需要重新粉刷地下室的 floor，该 floor 可表示为 $n \times m$ 的棋盘。

在上次派对后，整个棋盘除 $k$ 个单元格 $(x_1, y_1), (x_2, y_2), \ldots, (x_k, y_k)$ 外均被涂成绿色，这些单元格已被涂成白色或黑色。为了即将到来的派对，D. Pippy 想要将剩余的绿色单元格涂成黑色或白色。同时，他要求重新粉刷后棋盘上相邻颜色不同的单元格对数量为偶数。

形式化地，若定义集合：
$$A = \left\{((i_1, j_1), (i_2, j_2)) \ | \ 1 \le i_1, i_2 \le n, 1 \le j_1, j_2 \le m, i_1+j_1 < i_2+j_2, |i_1-i_2|+|j_1-j_2| = 1, \operatorname{color}(i_1, j_1) \neq \operatorname{color}(i_2, j_2) \right\},$$
其中 $\operatorname{color}(x, y)$ 表示单元格 $(x, y)$ 的颜色，则要求 $|A|$ 为偶数。

请帮助 D. Pippy 计算满足条件的粉刷方案数。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

## 说明/提示

第一个测试案例中，绿色单元格 $(2, 1), (2, 2), (2, 3)$ 共有 $4$ 种合法涂色方案，分别为：$(1, 1, 0)$，$(0, 0, 1)$，$(1, 0, 0)$，$(0, 1, 1)$（颜色按单元格顺序排列），如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2092E/0ff35e90f545116ecc7d2fbe2de16f35bcaedb89.png)  
第二个测试案例中，棋盘已全部涂色且相邻异色对数量为奇数，因此答案为 $0$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
3 3 6
1 1 0
1 2 1
1 3 0
3 1 1
3 2 0
3 3 1
3 4 12
1 1 0
1 2 1
1 3 0
1 4 1
2 1 1
2 2 0
2 3 1
2 4 0
3 1 0
3 2 1
3 3 0
3 4 1```

### 输出

```
4
0```

# 题解

## 作者：Collapsarr (赞：4)

# CF2092E She knows... 题解

### 解题思路

首先，我们考虑每一个方格对于答案产生的影响，因为方格是有序的，否则答案就是任意了。

对于在中心的方格而言，它的颜色变化会导致周围四个方格答案变化，但总体而言，答案 $|A|$ 的奇偶性不会发生变化。

考虑某一个方格周围白色和黑色方格数之差为偶数，以下图为例（方格边界颜色为红色，其余同题意）：

![](https://cdn.luogu.com.cn/upload/image_hosting/uftbvvgi.png)

我们先计算中心黑色方格的答案，和它可以贡献答案的分别为其左边的白色方格和右边的白色方格，而如果我们将这个黑色替换为白色：

![](https://cdn.luogu.com.cn/upload/image_hosting/tu8tglwl.png)

我们再计算该中心白色方格的答案，发现和它可以贡献答案的分别为其上边的黑色方格和下边的黑色方格，对于变化颜色前后，其对于答案的奇偶性并没有改变。

而对于某一个方格周围白色和黑色方格数之差为奇数，可以同上得到奇偶性也不改变，这里只放图了：

![](https://cdn.luogu.com.cn/upload/image_hosting/lpk0t3sg.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/gp3hhb85.png)

对于在中心的，我们已经考虑完了，而对于在四个角上的方格，其规律和在中心的方格并无二致，区别仅在其相邻的方格数为二，而不为四。

对于在边上但不在角上的方格，因为它们相邻的方格数为三，所以其在变化颜色后会使答案 $|A|$ 的奇偶性翻转，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/3k321d39.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/4be51hv2.png)

因此，我们可以得到，答案 $|A|$ 的奇偶性仅和在边上不在角上的方格（以下简称边格）的答案奇偶性相关，和在中心、角上的方格无关，接下来考虑 $|A|$ 的大小。

为了方便讨论，我们将数据中除了给定边格颜色为黑色的方格设置为白色，这样 $|A|$ 的奇偶性仍然保持不变。而如果两个边格均为黑色且相邻，那么它们的答案和两个边格均为黑色但不相邻是一样的，所以黑色边格的位置对于答案也没有影响。

此时，我们分类答案：

如果所有边格的颜色均已给出，如果黑色边格的个数为偶数，那么答案 $|A|$ 为 $2^{n\times m-k}$，否则答案为 $0$。

如果边格的颜色有些没有给出，记 $S$ 为边格的总数，$K$ 为给定颜色的边格的数量，$sum$ 为给定边格的颜色之和，则未给定颜色的边格数量即为 $S-K$，不妨令其颜色之和为 $cnt$，则我们需要保证 $sum+cnt$ 为一个偶数，即 $(sum+cnt)\equiv 0 \pmod 2$，所以 $cnt\equiv (-sum) \pmod 2$，由二项式定理知：
$$
C^0_n + C^2_n + C^4_n + \dots = C^1_n + C^3_n + C^5_n + \dots
$$

$$
C^0_n + C^1_n + C^2_n + \dots + C^{n-1}_n + C^{n}_n = 2^n
$$

所以 $cnt = s^{S-K-1}$，所以总答案 $|A|$ 为 $2^{n\times m-1}$。

### code

赛时代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 1e9 + 7;

int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while(ch<'0'||'9'<ch)
	{
		if(ch=='-')
		{
			f = -1;
		}
		ch = getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x = (x<<3) + (x<<1) + ch - '0';
		ch = getchar();
	}
	return x * f;
}

int n,m,k;

int powerr(int a,int b)
{
	int ans = 1;
	while(b)
	{
		if(b&1)
		{
			ans = ans * a;
			ans %= mod;
		}
		a = a * a;
		a %= mod;
		b>>=1;
	}
	return ans;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T = read();
    while(T--)
	{
        n = read(),m = read(),k = read();
        int ans = 2 * (n + m - 4);
        int cnt = 0,sum = 0;
        for(int i = 1,x,y,c;i<=k;i++)
		{
			x = read(),y = read(),c = read();
            if(((x==1||x==n)&&(y!=1&&y!=m))||((y==1||y==m)&&(x!=1&&x!=n)))
			{
                cnt++;
                sum += c;
            }
        }
        int last = ans - cnt,yushu = sum % 2,need = n * m - k;
        if(last>=1)
		{
            ans = powerr(2,need-1) % mod;
        }
		else
		{
            if(yushu==0)
			{
                ans = powerr(2,need) % mod;
            }
			else
			{
                ans = 0;
            }
        }
        cout<<ans<<endl;;
    }
    return 0;
}
```

---

## 作者：chenxi2009 (赞：2)

## 思路
结论：**相邻的颜色不同格子对数的奇偶性，等同于在边上而不在角上的格子中，黑色格子数的奇偶性**。

证明：发现翻转角上的格子和不处于图边缘的格子是不会影响奇偶性的。翻转在边上而不在角上的格子会改变奇偶性。初始全白的图奇偶性为偶，翻转了多少个边上的格子图的奇偶性就改变了多少次，故二者奇偶性相同。

不妨令这些关键的格子中自由的有 $x$ 个。
- 当 $x\ne0$ 时，我们可以把所有的方格随便染色但留下一个关键格子，并通过决定这个关键格子翻转与否控制答案的奇偶性，故可以认为自由的格子个数 $-1$ 个格子是自由的，即答案为 $2^{nm-k-1}$。
- 当 $x=0$ 时，如果关键格子黑色个数为偶数，则所有方案均可，答案为 $2^{nm-k}$；否则所有方案均不可行，答案为 $0$。

时间复杂度 $O(\sum(k+\log(nm)))$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007;
int T,n,m,k,x,y,c,crn,p,s;
long long qp(long long b){//快速幂 
	if(!b) return 1ll;
	long long c = qp(b >> 1);
	c = c * c % MOD;
	if(b & 1) c = c * 2 % MOD;
	return c;
}
int main(){
	scanf("%d",&T);
	while(T --){
		p = s = 0;
		scanf("%d%d%d",&n,&m,&k);
		for(int i = 1;i <= k;i ++){
			scanf("%d%d%d",&x,&y,&c);
			crn = 0;
			if(x == 1 || x == n) crn ++;
			if(y == 1 || y == m) crn ++;
			if(crn == 1) p ++,s += c;
		}
		if(p < 2ll * (n + m - 4)) printf("%lld\n",qp(1ll * n * m - k - 1));//有自由关键格子 
		else if(s & 1) printf("0\n");//没有自由关键格子且关键黑格数为奇 
		else printf("%lld\n",qp(1ll * n * m - k));//没有自由关键格子且关键黑格数为偶 
	}
	return 0;
}
```

---

## 作者：zjh114514 (赞：2)

注意到能够影响到 $|A|$ 奇偶性的只有边上的格子（如图黄色部分）:

![](https://cdn.luogu.com.cn/upload/image_hosting/bk6xnoy3.png)

于是我们容易得到：如果有绿色单元格在边上，则答案为 $2^{nm-k-1}$，即先将其他绿色单元格染色，再由此单元格决定奇偶性；如果没有绿色单元格在边上，则我们可以先假设角落和边上的单元格的颜色都为白色，然后将每个在边上的格子都和相邻的格子算一下对 $A$ 的贡献，最后判一下 $|A|$ 奇偶即可：奇数无解，偶数答案为 $2^{nm-k}$。

---

## 作者：zhangzhixing99 (赞：1)

如果您想拥有更好的阅读体验，您可以尝试[隐藏评论区](https://www.luogu.me/paste/zvd72h9y)。
## 题目摘要
- 给一张长为 $n$，宽为 $m$ 的网格图。
- 三种颜色：黑、白、绿。
- 要给绿的格子全部染成黑白，求方法数。
- 要求最终的网格图满足如下要求：

$$
|\left\{((i_1, j_1), (i_2, j_2)) \ | \ 1 \le i_1, i_2 \le n, 1 \le j_1, j_2 \le m, i_1+j_1 < i_2+j_2, |i_1-i_2|+|j_1-j_2| = 1, \operatorname{color}(i_1, j_1) \neq \operatorname{color}(i_2, j_2) \right\}| \equiv 0\,(\bmod\,2)
$$
## 前置知识
- [快速幂](https://cloud.tencent.com/developer/article/2382608)
## 正题开始
$n,m$ 高达 $10^9$，只能使用 $\operatorname{log}_2$ 或者常数级别的做法。

怎么办？

我们想象一张洁白的网格图，没有黑色格子，一定满足要求。  
我们在上面这张网格图上的一个格子染成黑色，此时这个黑色格子与周围的白色格子对最开始给出的公式均有 $1$ 贡献，总贡献为 $4$。  
重复上面的操作。  
如果染上的格子与黑色格子拥有公共边，则这个黑色的格子对答案再贡献 $-1$，与之相邻的格子也再贡献 $-1$，上式奇偶性不变。  
染上角落里的格子时，两条边挨着边界，对答案贡献 $-2$。  
染上边界上的格子时（不含角落），一条边挨着边界，对答案贡献 $-1$。此时上式奇偶性变化。

于是，我们知道，上式的奇偶性仅取决于边界染色格子数。

加入绿色。  
若这个格子在角落或在中间，则黑白均可，方案数 $\times 2$。  
否则，我们需要保证这些格子的黑色数 $\equiv$ 边上（不含角落）黑色数 $(\bmod\,2)$。  
于是我们固定一个格子让其满足要求，其余仍然无所谓。  

于是我们得到答案：

$$
ans = \begin{cases}
{
\begin{cases}
0 &\text{if } cnt2 \equiv 1\,(\bmod\,2) \\
2^{nm-k} &\text{otherwise}
\end{cases}
} &\text{if } cnt1 = 2(n - 2) + 2(m - 2)\\
2^{nm-k-1} &\text{otherwise}
\end{cases}
$$

其中 $cnt1$ 代表边界（不含角落）非绿色格子数，$cnt2$ 代表边界固定黑色格子数。
## 实现方法
边读入边处理，$cnt2$ 可以使用异或的方法来减少码量。
## 时间复杂度
- $\Theta(k + \operatorname{log}_2(nm - k))$。
- 右侧近乎常数（$< 100$）。
## 空间复杂度
- 近乎无。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define EOL '\n'

#define __LOG true
#ifdef __LOG
#define PRINTF printf
#else
#define PRINTF //
#endif

#define __IOFILE true
#ifdef __IOFILE
#define FREOPEN freopen
#else
#define FREOPEN //
#endif

const int mod = 1e9 + 7;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

bool OutOfRange(long long n, long long m, long long x, long long y)
{
	return x < 1 || x > n || y < 1 || y > m;
}

bool atBorder(long long n, long long m, long long x, long long y) // 但不含角落
{
	int tot = 0;
	for (int i = 0; i < 4; ++i)
	{
		tot += OutOfRange(n, m, x + dx[i], y + dy[i]);
	}
	return tot == 1;
}

long long qpow(long long bas, long long t)
{
	long long mul = bas, ret = 1;
	while (t)
	{
		if (t & 1)
		{
			ret *= mul;
			ret %= mod;
		}
		mul *= mul;
		mul %= mod;
		t >>= 1;
	}
	return ret;
}

void mspaint()
{
	long long n, m, k;
	cin >> n >> m >> k;
	long long cnt1 = 0, cnt2 = 0;
	for (int t = 1; t <= k; ++t)
	{
		int x, y, c;
		cin >> x >> y >> c;
		if (atBorder(n, m, x, y))
		{
			++cnt1;
			cnt2 ^= c;
		}
	}
	if (cnt1 == 2 * (n - 2) + 2 * (m - 2))
	{
		if (cnt2)
		{
			cout << 0 << EOL;
		}
		else
		{
			cout << qpow(2, n * m - k) << EOL;
		}
	}
	else
	{
		cout << qpow(2, n * m - k - 1) << EOL;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int T;
	cin >> T;
	while (T--)
	{
		mspaint();
	}
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：1)

~~早知道有這麼好玩的題我就應該打一下了！~~

此文中的“边上”不包括角，类似于魔方的“棱”。

我们发现，如果和一个格子相邻的格子有偶数个，那么这个格子的颜色就无关紧要了。

譬如说，一个格子，和它相邻的有 $x$ 个黑格子和 $y$ 个白格子。由于和它相邻格子数 $x+y$ 是偶数，$x$ 和 $y$ 的奇偶是一致的，那么填黑色就会给答案加 $y$，填偶数就会给答案加 $x$，它们的奇偶一致所以没有区别。

所以，我们看到棋盘上面只有一类格子与奇数个格子相邻——在边上的，每个格子有三个相邻。在角上的只有两个相邻，而在中央的有四个相邻。

假设这些格子都已经填满了，那怎么样才能满足题目要求呢？

我们首先考虑整个网格全黑肯定是满足题目要求的。进而，由于其它格子可以忽略，边上的格子全黑肯定是满足题目要求的。

而后，如果把其中一个边上的格子变成白色的，就会导致答案的奇偶被翻转，这样就不满足要求了，如果再改变一个颜色就会翻回来，又满足要求了。

同时这也启发我们，只要还有一个边上的格子没有填满，那么就总有一种方法可以满足要求；如果恰好只有一个边上的格子没有填，那么就恰好只有一种方法可以满足要求。

于是我们得到，若还有边上的格子没有填满，我们单拎出来一个格子用来在最后确保满足要求，剩下的格子一共有 $(nm-k-1)$ 个格子可以随便填。故答案为 $2^{nm-k-1}$。

但是如果边上的格子本来就满了，那么就检查是否有偶数个白色格子（如前所说），如果是的话剩下的格子也可以随便填，答案为 $2^{nm-k}$，如果不是的话就已经无解可以输出 $0$ 了。

---

## 作者：linjunye (赞：1)

### 题目大意
有一张 $n\times m$ 的黑白网格，其中有 $k$ 个格子已知，现在你要填充剩下未知的网格，使得最终相邻颜色不同的格子总数为偶数，求方案数。

### 思路

一道不错的题目。

首先，我们发现这个网格有黑白两种状态，于是想到了二进制。

然后，“最终相邻颜色不同的格子总数”好像可以发掘性质。我们发现，如果一个颜色是黑，一个颜色是白，要算贡献，记作 $1$；两个黑或者两个白，不算贡献，记作 $0$。

这个时候，根据前面二进制的想法，我们发现：这不就是异或操作吗！两两不同结果为 $1$，否则为 $0$。

那么，我们将条件改为“使得最终相邻格子异或的值的总和为偶数”。这个时候，黑记作 $1$，白记作 $0$。

总和为偶数又很复杂，但是我们有了前面异或的想法，于是我们想再来用异或套进去。这个时候，我们又发现：因为一次贡献值为 $1$，所以总和为偶数，就相当于异或和为 $0$！

那么，我们又可以将条件改为“使得最终相邻格子异或的总值为 $0$”。

然后，我们就可以来找一找性质了，画出一个 $5\times 5$ 的图。

```cpp
o-o-o-o-o
| | | | |
o-o-o-o-o
| | | | |
o-o-o-o-o
| | | | |
o-o-o-o-o
```

其中，中间连接的线代表将线两端点的值异或起来。

根据异或的性质：$(a\oplus b)\oplus(c\oplus d)=a\oplus b\oplus c\oplus d$，我们可以将所有值统一处理，即将 $(a_{1,1}\oplus a_{2,1})\oplus\dots$ 转化成 $a_{1,1}\oplus a_{1,1}\oplus\dots\oplus a_{2,1}\oplus\dots$。

那么，我们只要看每个点会被异或几次即可。

因为 $a\oplus a=0$，所以如果一个点会被异或偶数次，它就对答案无影响。

那么我们只统计边上的总异或和即可（因为被异或 $3$ 次），当然，角是不算的。

最终，我们做分类讨论：

如果边上都已经确定：那么如果不合法（即边上权值的总异或和为 $1$），答案为 $0$；否则，答案为 $2^{nm-k}$（剩下的任意，反正不会算贡献）。

如果边上没有确定，那么剩下的 $nm-k-1$ 个点可以任意，但其中一个边上的点必须定下，不能乱选，不然总异或值可能会改变。所以，这种情况的答案为 $2^{nm-k-1}$。

然后就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000010;
const int mod=1e9+7;
int n,m,k;
int x,y,c;
int ksm(int a,int b){
	int z=1;
	while(b){
		if(b&1)z=z*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return z;
}
void solve(){
	cin>>n>>m>>k;
	int cnt=0,cntc=0;
	for(int i=1;i<=k;i++){
		cin>>x>>y>>c;
		if(x==1&&y==1)continue;//角
		if(x==n&&y==1)continue;//角
		if(x==1&&y==m)continue;//角
		if(x==n&&y==m)continue;//角
		if(x==1||y==1||x==n||y==m){//边
			cnt++;
			if(c)cntc^=1;//小优化：总异或中，0是没有贡献的，所以只用计算1即可
		}
	}
	if(cnt==(n-2)*2+(m-2)*2){//填满了
		if(cntc==1)cout<<"0\n";
		else cout<<ksm(2,n*m-k)<<"\n";
	}
	else cout<<ksm(2,n*m-k-1)<<"\n";
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T=1;
	cin>>T;
	while(T--)solve();
	return 0;
}
/*
a1^a2^a2^a3^a3^a4^a4^a1
*/
```

---

## 作者：WaterSun (赞：1)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18809458)

挺有意思的一个题。

# 思路

在下文中，记 $col_{x,y} = \operatorname{color}(x,y)$。

因为颜色只有 $0,1$，那么 $|A|$ 等于相邻两个位置 $(x_1,y_1),(x_2,y_2)$ 满足 $col_{x_1,y_1} + col_{x_2,y_2} \equiv 0 \pmod 2$ 的数量。

我们需要满足 $|A| \bmod 2 = 0$，即满足 $\sum_{x_1 \leq x_2 \wedge y_1 \leq y_2 \wedge |x_1 - x_2| + |y_1 - y_2| = 1}col_{x_1,y_1} + col_{x_2,y_2} \equiv 0 \pmod 2$。

考虑一个点 $(x,y)$ 的 $col_{x,y}$ 会做贡献的次数。注意到若 $x = 1 \vee x = n \vee y = 1 \vee y = m$ 并且 $(x,y) \neq (1,1),(1,m),(n,1),(n,m)$，贡献的次数为 $3$；其余位置的点贡献次数均为偶数。这意味着只有前者的颜色会对最后 $|A|$ 的值有影响，其余位置的点都可以任选颜色。

记被钦定颜色的满足 $x = 1 \vee x = n \vee y = 1 \vee y = m$ 并且 $(x,y) \neq (1,1),(1,m),(n,1),(n,m)$ 的点的数量为 $cnt$，它们的颜色和为 $sum$，则：

- 若 $cnt = 2 \times (n + m - 4)$：
  - 若 $sum \equiv 0 \pmod 2$，答案为 $2^{nm - k}$（除了这 $k$ 个点的颜色都可以任选）。
  - 否则，答案为 $0$。
- 否则，答案为 $2^{nm - k - 1}$（当边缘的点只剩下一个没有被填颜色，那么这个点的颜色已经被确定，因为需要满足边缘点的颜色和为偶数）。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define Mul(a,b) ((a) * (b) % mod)
#define chMul(a,b) (a = Mul(a,b))

using namespace std;

const int mod = 1e9 + 7;
int n,m,k;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline int qmi(int a,int b){
    int res = 1;
    while (b){
        if (b & 1) chMul(res,a);
        chMul(a,a); b >>= 1;
    } return res;
}

inline void solve(){
    int cnt = 0,sum = 0;
    n = read(),m = read(),k = read();
    for (re int i = 1,x,y,c;i <= k;i++){
        x = read(),y = read(),c = read();
        if ((x == 1) + (x == n) + (y == 1) + (y == m) == 1) cnt++,sum += c;
    }
    if (cnt == 2 * (n + m - 4)){
        if (sum & 1) puts("0");
        else printf("%lld\n",qmi(2,n * m - k));
    }
    else printf("%lld\n",qmi(2,n * m - k - 1));
}

signed main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

