# [USACO4.3] 逢低吸纳Buy Low, Buy Lower

## 题目描述

“逢低吸纳”是炒股的一条成功秘诀。如果你想成为一个成功的投资者，就要遵守这条秘诀：“逢低吸纳，越低越买”。

这句话的意思是：每次你购买股票时的股价一定要比你上次购买时的股价低。按照这个规则购买股票的次数越多越好，看看你最多能按这个规则买几次。

给定连续的 $N$ 天中每天的股价。你可以在任何一天购买一次股票，但是购买时的股价一定要比你上次购买时的股价低。写一个程序，求出最多能买几次股票。

以下面这个表为例，某几天的股价是：

|天数    |股价    |
|:-------|:-------|
|$1$|$68$|
|$2$|$69$|
|$3$|$54$|
|$4$|$64$|
|$5$|$68$|
|$6$|$64$|
|$7$|$70$|
|$8$|$67$|
|$9$|$78$|
|$10$|$62$|
|$11$|$98$|
|$12$|$87$|


这个例子中，如果每次买股票时的股价都比上一次买时低，那么最多能买 $4$ 次股票。一种买法如下（可能有其他的买法）：


|天数    |股价    |
|:-------|:-------|
|$2$|$69$|
|$5$|$68$|
|$6$|$64$|
|$10$|$62$|

## 说明/提示

$1 \le N \le 5000$。

## 样例 #1

### 输入

```
12
68 69 54 64 68 64 70 67
78 62 98 87```

### 输出

```
4 2```

# 题解

## 作者：Zhou_yu (赞：22)

## 题目描述：
### [P2687 题目传送门](https://www.luogu.com.cn/problem/P2687)
#### [双倍经验](https://www.luogu.com.cn/problem/P1108)
~~到死不打高精度~~
## 所用算法：

1. 求方案数的一道 dp 题。

2. 考察对数据范围的熟悉性。

#### 算法思路：
1. 先推转移方程：

众所周知，动态转移方程就是**最长下降子序列的方程**，
也就是**以自己**为子序列**结尾**，在**前面**比他**数据大**的中挑一个作为前一个，并取他们的**最大值加 $1$，也就是加上自己**。

注意：$f_i$ 的初始值为 $1$，因为**自己本身有可能就是最长下降子序列**。

所以轻松推出：$f_i=\max(f_i,f_j+1)$

范围及条件：$i>j \wedge a_i<a_j$

2. 统计方案数：

这是这道题的**重点**！（不考虑高精板子算法）

人人都知道加法原理，所以我们可以将长度为**当前长度减一**，并且最后一个元素**大于目前元素**的方案数量**加进当前方案数**中，让 $anses[i]$ 来存以第 $i$ 个元素为结尾的方案数。

注意：如果出现新的最长下降子序列，要赋初值为 $1$，因为它肯定出现过了。

3. 数据范围：

讨论中，是[这个的数据](https://www.luogu.com.cn/discuss/670562)和[这个](https://www.luogu.com.cn/discuss/30185)给了我信心来做~~玄学~~分析。

**只要威力足够大，精度就可以忽略不计！**

——by 王站长

`long double` 就是这样。

事实上，`long double` 的范围在：$(-1.2 \times 10^{4932},1.2 \times 10^{4932})$，而最大数据甚至小于 $3.8 \times 10^{752}$，虽精度有可能较低，但这数据实是大炮打蚊子，所以不用过多考虑。

## 蒟蒻の AC 代码
[AC 记录](https://www.luogu.com.cn/record/125002220)

```cpp
#include <bits/stdc++.h>
#define ld long double
using namespace std;
ld a[5005];
ld f[5005],anses[5005];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n;
    ld ma=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>a[i];
    for(int i=1;i<=n;i++)
    {
    	f[i]=1;//考虑自己本身就是最长下降子序列
        for(int j=1;j<i;j++)
        if(a[i]<a[j])
        f[i]=max(f[i],f[j]+1);//转移方程，方法不再赘述
        ma=max(ma,f[i]);
        //更新答案
        for(int j=1;j<i;j++)
        if(f[i]==f[j]&&a[i]==a[j])anses[j]=0;//如果都是最长，要停止。因为是下降，所以数据等于也要停止
        else if(f[i]==f[j]+1&&a[i]<a[j])anses[i]+=anses[j];//前一个答案可以再用
        if(!anses[i])anses[i]=1;//考虑出现新的最长下降子序列
    }
    ld ans=0;
    for(int i=1;i<=n;i++)
    if(f[i]==ma)
    ans+=anses[i];
    //记得输出时要抹掉小数
    cout<<fixed<<setprecision(0)<<ma<<' '<<ans;
    return 0;
}
```
## 总结
前一秒：我今天就算去打高精度也不会用玄学！

后一秒：`long double` 真香。

---

## 作者：Register_int (赞：5)

首先求出以 $a_i$ 结尾的最长下降子序列的长度 $dp_i$。有转移：

$$dp_i=\max_{j<i\land a_j>a_i}dp_j+1$$

之后计算最长下降子序列的个数 $f_i$。在转移的过程中，如果从 $j$ 转移到 $i$ 比当前最优解更优，那么将最优解方案数覆盖为 $f_j$；如果恰好与最优解相同，那么累加方案数即可。

不过这样只能统计 **天数序列** 不同的方案，而题目要求 **元素不同**。所以，对于相同的 $a_j$，只能统计最后一次在 $i$ 之前出现的元素，剩下要全部置 $0$。

为方便理解给个代码实现：

```cpp
for (int i = 1; i <= n; i++) {
    f[i] = dp[i] = 1;
    for (int j = 1; j < i; j++) {
        if (a[i] < a[j]) {
            if (dp[i] == dp[j] + 1) f[i] += f[j];
            else if (dp[i] < dp[j] + 1) dp[i] = dp[j] + 1, f[i] = f[j];
        } else if (a[i] == a[j]) f[j] = 0;
    }
    ans = max(ans, dp[i]);
}
```

结束……了吗？  
之前很多题解到这一步就结束了，因为他们认为这个做法的复杂度是 $O(n^2)$。但是我要告诉你，这个做法是 $O(n^3)$ 的。

为什么呢？先来考虑答案最大是多少：构造每两个数为一组，组内递增，每组的最小值递减。这样可以得出极限答案 $2^{n/2}$，说明答案的位数是 $O(n)$ 的。在 dp 的过程中需要维护这个高精度，所以要乘上高精加的复杂度。

下面给出两种解决方法：

#### 1. 压位高精

考虑物理上减少答案位数。极限数据下答案大约为 $750$ 位，使用压 $8$ 位高精可以将位数减少到 $95$，计算量大约为 $(5\times10^3)^2\times10^2/4=6\times 10^8$，在 2s 的时限下可以通过。

我由于实现垃圾使用的是压 $18$ 位高精。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e3 + 10;
const int MAXM = 42;
const ll BASE = 1e18;

struct Int {
    ll a[MAXM];

    Int(int k = 0) {
        for (int i = MAXM - 1; ~i; i--) a[i] = k % BASE, k /= BASE;
    }

    Int operator + (const Int &rhs) const {
        ll t = 0; Int res = *this;
        for (int i = MAXM - 1; ~i; i--) {
            t += res.a[i] + rhs.a[i];
            res.a[i] = t % BASE, t /= BASE;
        }
        return res;
    }

    friend ostream & operator << (ostream &out, const Int &n) {
        int p = 0;
        for (; p < MAXM && !n.a[p]; p++);
        if (p == MAXM) return out << 0;
        for (out << n.a[p++]; p < MAXM; p++) out << setw(18) << setfill('0') << n.a[p];
        return out;
    }

    Int & operator += (const Int &rhs) { return *this = *this + rhs; }
};

int n, a[MAXN], ans;

int dp[MAXN]; Int f[MAXN], sum;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        f[i] = dp[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[i] < a[j]) {
                if (dp[i] == dp[j] + 1) f[i] += f[j];
                else if (dp[i] < dp[j] + 1) dp[i] = dp[j] + 1, f[i] = f[j];
            } else if (a[i] == a[j]) f[j] = 0;
        }
        ans = max(ans, dp[i]);
    }
    for (int i = 1; i <= n; i++) if (dp[i] == ans) sum += f[i];
    cout << ans << " " << sum;
}
```

#### 2. 树状数组

计算最优方案的部分并不需要优化，需要优化的是方案数。

没有“元素不同”要求的情况下，实际上只需要以长度作为下标来记录方案数总和就能解决。有元素不同时，可以使用哈希表来记录 $a_j$ 在 $i$ 之前最后一次出现的位置，每次只会更新一个数的位置，在对应的长度处减去即可。

但是会多算 $a_j\le a_i$ 的情况，所以考虑对于每个值单独开一个树状数组来维护偏序关系。时间复杂度 $O(n^2\log n)$。

由于树状数组需要离散化，哈希表可以省掉。

代码不放了。

---

## 作者：chenhanzheapple (赞：2)

# [传送门](https://www.luogu.com.cn/problem/P2687)

## 题面概括

求一个数组的 LDS 及方案数。

## 分析

dp。

设 $f_i$ 为以 $i$ 号元素为结尾的 LDS 长度。

$f_i$ 的转移十分简单，在这里就不赘述了。

设 $g_i$ 为以 $i$ 号元素为结尾的 LDS 方案数。

则 $g_i = \sum\limits_{\forall
j \in [1,i-1],a_i < a_j,f_i=f_j+1}g_j$。

原数组 LDS 长度 $ans = \max\limits_{i=1}^{n}f_i$。

最后答案为 $\sum\limits_{\forall
i \in [1,n],f_i=ans}f_i$。

## 细节

1. 在 $g$ 转移的过程中，可能会遇到虽然选择的元素编号不同，但是元素相同的情况，即 $f_i=f_j \land a_i=a_j$，其中 $i>j$。这时候就需要将 $g_i$ 或 $g_j$ 中的一个设为 $0$，但是 $g_i$ 可能再次更新，所以需要将 $g_j$ 设为 $0$。

2. 方案数可能很大，需要高精度，但是本题可以用 long double 卡过，因为本人太懒，所以用了 long double。

3. 如果你使用了 long double，则最后输出是需要去掉小数。

4. 如果在 $g_i$ 没有发生任何转移，则需要将 $g_i$ 设为 $1$（因为可以构建一个同时以自己为开头结尾的 LDS）。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long double
using namespace std;
int n,ans,sum;
int a[5005],f[5005],g[5005];
signed main(){
    cin >> n;
    for(signed i=1;i<=n;i++){
        cin >> a[i];
    }
    for(signed i=1;i<=n;i++){
        f[i] = 1;
        for(signed j=1;j<i;j++){
            if(a[i]<a[j]){
                f[i] = max(f[i],f[j]+1);
            }
        }
        for(signed j=1;j<i;j++){
            if(f[i]==f[j]+1 && a[i]<a[j]){
                g[i]+=g[j];
            }
            else if(f[i]==f[j] && a[i]==a[j]){
                g[j] = 0;
            }
        }
        g[i] = max(g[i],(int)1);
        ans = max(ans,f[i]);
    }
    for(signed i=1;i<=n;i++){
        if(f[i]==ans){
            sum+=g[i];
        }
    }
    printf("%.0Lf %.0Lf",ans,sum);
    return 0;
}

```

---

## 作者：mayike (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/P2687)
~~看大佬的高精度看不懂，于是自己写了一篇~~

蒟蒻刚学高精度，勿喷！
## 思路
这题很明显是求最长下降子序列，恶心的是方法数的数据太大了，要用高精度。

易得状态转移方程  
$$b_i=\max(b_i,b_j+1)$$

前提是 $a_i<a_j$，$j<i$，$b_i$ 是序列长度，$a_i$ 是第 $i$ 个数。

对于方法，给出代码与注释：
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<i;j++){
        if(a[i]<a[j])b[i]=max(b[i],b[j]+1);
    }
    for(int j=1;j<i;j++){
	if(a[i]<a[j]&&b[i]==b[j]+1)c[i]+=c[j];
    //只有是下降子序列且前一段序列长度恰好是原序列长度减一，才把原序列的方案加等于前段序列的方案(加法原理)
	else if(a[i]==a[j]&&b[i]==b[j])c[j]=0;
    //这是要特判并清零的，以防a[i]后面的数会把这两种方案都算上
    //引用题目：如果两个方案的股价序列相同，那么这样的两个方案被认为是相同的（只能算做一个方案）
    }
    c[i]=max(c[i],1ll*1.0);//用double会卡到满分，但最后一个点是过不去的
    //自身也是一种方案(方案数为1)，这针对的是只有一个数的情况
    d=max(d,b[i]);//取最长长度
}
```
于是，拿满分的代码就有了，上代码(非 AC 代码)：
```cpp
#include<bits/stdc++.h>
using namespace std;
double n,d,m,a[5005],b[5005],c[5005];//数，长度，方案
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){cin>>a[i];b[i]=1;}//初始长度为1
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[i]<a[j])b[i]=max(b[i],b[j]+1);
		}
		for(int j=1;j<i;j++){
			if(a[i]<a[j]&&b[i]==b[j]+1)c[i]+=c[j];
			else if(a[i]==a[j]&&b[i]==b[j])c[j]=0;
		}
		c[i]=max(c[i],1ll*1.0);
		d=max(d,b[i]);
	}
	cout<<d<<" ";
	for(int i=1;i<=n;i++){
		if(b[i]==d)m+=c[i];//累计方案
	}printf("%.0lf",m);//保留0位
	return 0;
}
```
我点开最后一个数据点一看，长长的一大串，看来必须得高精度做了。

于是我就去学习了一下高精度加法，写了一份我们蒟蒻可以看懂的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,a[5005],b[5005],w[5005],p[1005][5005];//数，长度，每个方案的数字长度，方案的数字每位的数
void ab(int x,int y){
	int t=0,len=max(w[x],w[y]);
	for(int i=1;i<=len;i++){
		if(w[x]<i)p[i][x]=0;
        //注意，如果位数不够，就变为0，不然可能出错
		if(w[y]<i)p[i][y]=0;//同理
		p[i][x]=p[i][y]+p[i][x]+t;
		t=p[i][x]/10;
		p[i][x]%=10;//正常高精
	}if(t!=0)p[++len][x]=t;//注意进位
        w[x]=len;//改变方案数的数字长度
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){cin>>a[i];b[i]=1;}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[i]<a[j])b[i]=max(b[i],b[j]+1);
		}
		for(int j=1;j<i;j++){
			if(a[i]<a[j]&&b[i]==b[j]+1)ab(i,j);//如之前非高精做法
			else if(a[i]==a[j]&&b[i]==b[j])w[j]=0;//直接变长度为0(等价于赋值为零)
		}d=max(d,b[i]);
		if((w[i]==1||w[i]==0)&&p[1][i]<1)p[1][i]=1,w[i]=1;//特判一下，记得变长度，如非高精做法
	}cout<<d<<" ";//输出子序列长度
	for(int i=1;i<=n;i++){
		if(b[i]==d)ab(5003,i);
        //这里的5003只要是大于5000且在数组范围内的数均可
	}for(int i=w[5003];i;i--)printf("%d",p[i][5003]);//倒序输出
        return CTJ;
}
```
制作不易，希望大家多多支持，谢谢！

---

## 作者：Furina_Saikou (赞：2)

### 修改

数据加强力，~~关于 `double`，它死了~~，但是我们有 `long double`。

### 题目大意

给定 $ n $ 个数，求最长下降子序列的长度和个数。

### 思路

最长下降子序列只需要将[最长上升子序列](https://www.luogu.com.cn/problem/B3637)中 $ a_i $ 和 $ a_j $ 判断的 $ > $ 号改 $ < $ 号。

接下来是记录最长下降子序列的个数，定义一个数组 $ f $，$ f_i $ 记录 $ 1 $ 到 $ i $ 的最长下降子序列个数，我们对 $ f $ 有如下操作：

1. 如果 $ dp_j + 1 > dp_i $ 也就是要更新 $ dp $ 数组的情况，我们就同步更新 $ f $ 数组。

2. 如果 $ dp_j + 1 = dp_i $ 那 $ f $ 数组就要增加。

3. 我们还要注意一种情况就是在比较 $ a_i = a_j $ 的情况，要把 $ f_j $ 设为 $ 0 $ 否则在最后统计时会重复计算。

程序最后一遍循环统计最大值的个数就好。

### 思路正确的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5001],dp[5001],maxn=1,f[5001];
int main()
{
	cin>>n;
	f[1]=n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		dp[i]=f[i]=1;
	}
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			if(a[i]<a[j])
			{
				if(dp[j]+1>dp[i])
				{
					dp[i]=dp[j]+1;//求最长下降子序列长度
					f[i]=f[j];//更新f数组
				}else if(dp[j]+1==dp[i])
				{
					f[i]+=f[j];//更新f数组
				}

			}else if(a[i]==a[j])
			{
				f[j]=0;//防止重复
			}
		}
		maxn=max(maxn,dp[i]);//求最长下降子序列长度
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(dp[i]==maxn)
		{
			cnt+=f[i];//统记答案数
		}
	}
	printf("%d %d",maxn,cnt);
	return 0;
}
```

但是过不了，本题是蓝题，肯定有它的蓝处，那就是本题要求方案数，而求方案数就很容易爆 `long long`，因此要打高精度，但是在 c++ 中，有个可以存很大的数的变量 `long double`，运用 `long double` 就可以不打高精度，注意 `long double` 的占位符为 `%Lf`。

### 最终代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long double n,a[5001],dp[5001],maxn=1,f[5001];//long double类型
int main()
{
	cin>>n;
	f[1]=n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		dp[i]=f[i]=1;
	}
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			if(a[i]<a[j])
			{
				if(dp[j]+1>dp[i])
				{
					dp[i]=dp[j]+1;
					f[i]=f[j];
				}else if(dp[j]+1==dp[i])
				{
					f[i]+=f[j];
				}

			}else if(a[i]==a[j])
			{
				f[j]=0;
			}
		}
		maxn=max(maxn,dp[i]);
	}
	long double cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(dp[i]==maxn)
		{
			cnt+=f[i];
		}
	}
	printf("%.0Lf %.0Lf",maxn,cnt);//保留0位小数不然会以另外的形式输出
	return 0;
}
```

要用高精度的话也没问题，但是调试起来可能会比较麻烦。

---

## 作者：splendore (赞：1)

### 思路
利用最长下降子序列的思想容易推出转移方程：

$$f_i=\max_{j=1}^{j<i}(f_i,f_j+1)\ \ (a_i<a_j)$$

但这道题有一组很大的 hack 数据，解决方法有两种：

1.高精度。

2.`long double`。

考虑到实现难度，这里选择使用 `long double`。

代码如下：
```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5005;
int a[N],f[N];long double c[N];
int main(){
    int n,mx=0;scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i]);f[i]=1;
        for(int j=1;j<i;++j)
            if(a[i]<a[j])f[i]=max(f[i],f[j]+1);
        for(int j=1;j<i;++j)
            if(f[i]==f[j]&&a[i]==a[j])c[j]=0;
            else if(f[i]==f[j]+1&&a[i]<a[j])c[i]+=c[j];
        if(f[i]==1)c[i]=1;
        mx=max(mx,f[i]);
    }
    long double ans=0;
    for(int i=1;i<=n;++i)
        if(f[i]==mx)ans+=c[i];
    printf("%d %.0Lf\n",mx,ans);
    return 0;
}
```

---

## 作者：Eltaos_xingyu (赞：1)

[双倍经验](https://www.luogu.com.cn/problem/P1108)

[题目传送门](https://www.luogu.com.cn/problem/P2687)

省流：为什么要用高精度啊？

## 题目描述

求一个序列的最长下降子序列的长度与其个数。

## 分析

这是一道简单的 dp 题。

看到 $n \leq 5000$ 的数据范围，其实可以想到这道题可以用 $O(n^2)$ 的时间复杂度解决。

容易发现，如果我们设 $dp_{i}$ 是序列到达第 $i$ 位的最长下降子序列长度，转移方程为：

$$dp_i=\max(dp_i,dp_j+1)\ \ \ (a_i<a_j\land i>j)$$

其中 $a$ 为原序列。

通过这个转移方程，可知在一次转移中，如果达到了更优的情况，直接覆盖方案数；如果正好和当前的最优相同，那么直接累加方案即可。

注意题中要求去重，直接在遇到相同的数时，将前面的置 $0$ 即可，因为这两个数互相不影响，且后面的数可能将这两个数的贡献一起加上了。

### 高精度？

讨论区有一个 hack，说是最大的答案能卡到 $2^{2500}$......

不会写高精度怎么办？

有没有可能，这个数的值只有 $3.8 \times 10^{752}$。然而 `long double` 的存储范围是 $(-1.2 \times 10^{4932},1.2 \times 10^{4932})$，虽然精度可能有误差，但是过这道题还是绰绰有余的。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,vm[500001];
long double dp[500001],t[500001];
#define cn const
signed main()
{
	ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>vm[i];
	}
	long double ans1=-1,ans2;
	for(int i=1;i<=n;i++){
		t[i]=1;
		dp[i]=1;
		for(int j=1;j<i;j++){
			if(vm[i]<vm[j]){
				if(dp[i]==dp[j]+1)t[i]+=t[j];
				if(dp[i]<dp[j]+1){
					dp[i]=dp[j]+1;
					t[i]=t[j];
				}
			}
			if(vm[i]==vm[j])t[i]=0;
		}
	}
	
	for(int i=1;i<=n;i++){
		if(ans1==dp[i])ans2+=t[i];
		if(ans1<dp[i])ans2=t[i],ans1=dp[i];
	}
	cout<<fixed<<setprecision(0)<<ans1<<" "<<ans2;
	return 0;
}
```


---

## 作者：tony0530 (赞：0)

## solution

------

#### 题目
 

[传送门](https://www.luogu.com.cn/problem/P2687)

------

#### 算法

**long double** 真香！！

这就是一道最长下降子序列计数问题。

记 $f_i$ 为以 $i$ 结尾的最长下降子序列**长度**，$f_i \leftarrow \underset{a_i < a_j, j < i}{\max}{f_j + 1}$。

接着统计个数，暴力枚举找到贡献给自己的 $j$，将 $count_i \leftarrow count_i + count_j$，若 $i > j$，$f_i = f_j$ 则将 $j$ 合并成 $i$。

不用高精度，只要 **long double**！

------

#### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n;
int a[N];
int f[N];
long double ans[N];

signed main()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i ++ ) cin >> a[i];
    int max_ = 0;
    for(int i = 1 ; i <= n ; i ++ )
    {
        f[i] = 1;
        for(int j = 1 ; j < i ; j ++ )
            if(a[i] < a[j])
                f[i] = max(f[i], f[j] + 1);
        max_ = max(max_, f[i]);
        for(int j = 1 ; j < i ; j ++ )
            if(a[i] == a[j] && f[i] == f[j])
                ans[j] = 0;
        for(int j = 1 ; j < i ; j ++ )
            if(a[i] < a[j] && f[i] == f[j] + 1)
                ans[i] += ans[j];
        if(ans[i] == 0) ans[i] = 1;
    }
    cout << max_ << " ";
    long double answer = 0;
    for(int i = 1 ; i <= n ; i ++ )
        if(f[i] == max_)
            answer += ans[i];
    printf("%.0Lf", answer);
    return 0;
}
```

---

## 作者：block_in_mc (赞：0)

## 解题思路

先不考虑股价序列相同记为同一方案的情况，即这时 $\{2,1,1\}$ 的最长下降子序列个数为 $2$。用 $len_i$ 代表以 $a_i$ 结尾的最长下降子序列的长度，$dp_i$ 代表以 $a_i$ 结尾的最长下降子序列的个数，容易推出状态转移方程：

$$len_i=\mathop{\max}\limits_{j<i,\ a_j>a_i}len_j+1$$

$$dp_i=\sum\limits_{j<i,\ a_j>a_i,\ len_i=len_j+1}dp_j$$

初始值为 $dp_i=1$。

现在考虑如何处理股价序列相同的情况，对于序列 $a=\{5,4,3,4,2\}$，我们可以在计算 $dp_4$ 时将 $dp_2$ 设为 $0$。这样：

- 对于 $dp_1,dp_3$，显然没有影响，由于在 $dp_4$ 之前计算，结果没有影响，且利用 $dp_3$ 更新时，由于使用了 $dp_3$，一定为不同的股价序列，没有影响；
- 对于 $dp_5$，在不处理的情况下会被 $dp_2$ 更新一次，$dp_4$ 更新一次，而 $dp_2$ 中包含的情况总会被 $dp_4$ 包含，因此将 $dp_2$ 设为 $0$ 计算所得的结果是正确的。

计算 $len$ 和 $dp$ 的代码可以写在一起，当 $len_i$ 被比其大的数更新时，将 $dp_i$ 设为 $0$；当 $len_i$ 被与其相等的数 $a_j$ 更新时，将 $dp_i$ 加上 $dp_j$。这样初始值为 $dp_i=len_i=1$。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[5100], len[5100];
long double dp[5100];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        len[i] = 1, dp[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[i] < a[j]) {
                if (len[i] == len[j] + 1) dp[i] += dp[j];
                else if (len[i] < len[j] + 1) len[i] = len[j] + 1, dp[i] = dp[j];
            }
            else if (a[i] == a[j]) dp[j] = 0;
        }
    }
    int ans = 0; long double cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (len[i] > ans) ans = len[i], cnt = dp[i];
        else if (len[i] == ans) cnt += dp[i];
    }
    cout << fixed << setprecision(0) << ans << " " << cnt << endl;
    return 0;
}
```

---

## 作者：linjinkun (赞：0)

这题蓝点蓝在高精度，状态转移方面顶多黄，而我为了不再重蹈覆辙我之前的高精度调 $n$ 年的情况，我使用了 ```long double```。

那么这道题就变成了简单 ```dp```。

设 $f_i$ 表示以 $i$ 结尾最长下降子序列长度。那么枚举每个 $i$，再枚举每一个 $j$，保证 $1 \le j < i$，状态转移为当 $a_i < a_j$ 时 $f_i = \max(f_i,f_j+1)$。

接着设 $dp_i$ 表示以 $i$ 结尾的最长上升子序列方案数，这个转移就比较难一些（但也顶多黄题难度），要分类讨论，如果 $a_i < a_j$，并且 $f_j+1>f_i$，那么 $dp_i = dp_j$，因为把 $j$ 放在 $i$ 前面是比之前记录的以 $i$ 结尾的最优解优的，所以 $dp_i$ 直接等于 $dp_j$，因为 $f_i$ 已经不可能等于最优解了，接下来如果 $f_j+1 = f_i$，那么 $dp_i = dp_i+dp_j$，因为这两个的 $f$ 值相同，那么都有可能成为最优解，所以要加上，最后一个情况是如果 $a_i = a_j$，那么 $dp_j = 0$，因为两个相同的只能算一个。

最后枚举每一个 $f_i$，如果 $f_i = maxx$，那么  $sum = sum+dp_i$，意思就是如果 $f_i$ 是最长上升子序列，那么统计方案数的变量 $sum$ 就要加上 $dp_i$。

**注意：十年 OI 一场空，不开 ```long double``` 见祖宗。**

代码（前面讲的已经很详细了，这里就不放注释了）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5005;
long double a[N],f1[N],f2[N];
signed main()
{
	long double n;
	scanf("%Lf",&n);
	f2[1] = n;
	for(int i = 1;i<=n;i++)
	{
		scanf("%Lf",&a[i]);
		f1[i] = 1;
		f2[i] = 1;
	}
	long double maxx = 0;
	long double sum = 0;
	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<i;j++)
		{
			if(a[i]<a[j])
			{
				if(f1[j]+1>f1[i])
				{
					f1[i] = f1[j]+1;
					f2[i] = f2[j];
				}
				else if(f1[i] == f1[j]+1)
				{
					f2[i]+=f2[j];
				}
			}
			else if(a[i] == a[j])
			{
				f2[j] = 0;
			}
		}
		maxx = max(maxx,f1[i]);
	}
	for(int i = 1;i<=n;i++)
	{
		if(f1[i] == maxx)
		{
			sum+=f2[i];
		}
	}
	printf("%.0Lf %.0Lf",maxx,sum);
	return 0;
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目简化
给定一个长为 $n$ 的序列，求这个序列中最长下降子序列的长度和数量。元素相同的子序列只算一个。
## 题目分析
以下设 $a_i$ 表示第 $i$ 天的股价。

首先，求最长下降子序列的长度就是一个经典的 DP 问题。设 $dp_i$ 表示在前 $i$ 个元素中最长下降子序列的长度。那么，第 $i$ 个元素可以接在之前任意一个小于这个元素的元素的后面。所以有如下状态转移方程：
$$dp_i=\max{(1,\max_{j=1}^{i-1}{(dp_j+1)})}$$
接着是求最长下降子序列的数量。设 $f_i$ 表示以 $i$ 结尾的最长下降子序列的数量。在更新 $dp_i$ 时，如果 $dp_j+1>dp_i$，就说明此时以 $i$ 结尾的最长下降子序列的数量就是以 $j$ 结尾的最长下降子序列的数量，即 $f_j$。如果 $dp_j+1=dp_i$，就说明就说明此时以 $i$ 结尾的最长下降子序列的数量还需要加上以 $j$ 结尾的最长下降子序列的数量，即 $f_i+f_j$。综上，我们可以得到下面的式子：
$$f_i=\begin{cases} f_j & (dp_j+1>dp_i) \\ f_i+f_j & (dp_j+1=dp_i) \end{cases}$$
但是，由于元素相同的子序列只算一个，所以当 $a_i=a_j$ 且 $f_i=f_j$ 时，以 $i$ 结尾的最长下降子序列会被以 $j$ 结尾的最长下降子序列替代，即当 $a_i=a_j$ 且 $f_i=f_j$ 时，$f_i=0$。

**code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5005],dp[5005],ans;
long long dp2[5005],cnt;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		dp[i]=dp2[i]=1;
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[j]>a[i]){
				if(dp[j]+1>dp[i]){
					dp[i]=dp[j]+1,dp2[i]=dp2[j];
				}
				else if(dp[j]+1==dp[i]){
					dp2[i]+=dp2[j];
				}
			}
			else if(a[j]==a[i]){
				dp2[i]=0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[i]);
	}
	for(int i=1;i<=n;i++){
		if(dp[i]==ans){
			cnt+=dp2[i];
		}
	}
	printf("%d %d",ans,cnt);
	return 0;
}
```

---

## 作者：Slient_QwQ (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Manipula/p/17827433.html)

[双倍经验](https://www.luogu.com.cn/problem/P1108)

## 分析

这是一道求最长下降子序列的题目，且要统计方案，但是会有重复情况，例如以下的的数据，

```
4
4 2 2 3
```
我们可以选择 $1, 2$, $1, 2$, $1, 4$ 这几天来购买，但是 $1, 2$ 和 $1, 3$ 本质上是一样的，所以只算一种。

根据上面的说明，我们可以得出：

- 当 $dp_j + 1 = dp_i$ 而且 $a_j > a_i$，$i$ 的方案数加上 $j$ 的方案数。
- 当 $dp_j = dp_i$ 而且 $a_j = a_i$，$j$ 的方案数清零。

其中 $dp_i$ 指以第 $i$ 个数为结尾的最长公共下降子序列长度，$a_i$ 指第 $i$ 天的股票价格。
## 90 pts Code
```cpp
/*Code By Manipula*/
#include <bits/stdc++.h>
// #pragma GCC optimize(2)
#define INF 0x3f3f3f3f
#define int long long
#define swap(x, y) x ^= y ^= x ^= y
#define sqrt(n) pow(n, 0.5)
#define sort stable_sort
#define mk(x, y) make_pair(x, y)
#define mt(arr, num) memset(arr, num, sizeof(arr))
using namespace std;
const int N = 5005;
int dp[N], a[N], ans[N], n, last, sum;
signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)cin >> a[i];
	for (int i = 1; i <= n; i++)dp[i] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
			if (a[j] > a[i])dp[i] = max(dp[i], dp[j] + 1);
		if (dp[i] > dp[last])last = i;
	}
	for (int i = 1; i <= n; i++)
	{
		if (dp[i] == 1)ans[i] = 1;
		for (int j = 1; j < i; j++)
			if (a[j] > a[i] && dp[j] + 1 == dp[i])ans[i] += ans[j];
			else if (a[j] == a[i] && dp[j] == dp[i])ans[j] = 0;
	}
	for (int i = 1; i <= n; i++)
		if (dp[i] == dp[last])sum += ans[i];
	cout << dp[last] << " " << sum;
	return 0;
}
```

为什么是 90 pts 代码？因为这题要打十分讨厌的高精度！！

下面给出加上了高精度的代码。

## Accepted Code
```cpp
/*Code By Manipula*/
#include <bits/stdc++.h>
// #pragma GCC optimize(2)
#define INF 0x3f3f3f3f
#define int long long
#define swap(x, y) x ^= y ^= x ^= y
#define sqrt(n) pow(n, 0.5)
#define sort stable_sort
#define mk(x, y) make_pair(x, y)
#define mt(arr, num) memset(arr, num, sizeof(arr))
using namespace std;
const int N = 5005;
const int base = 1e18;
int dp[N], a[N], n, last;
struct BIGNUM{
	int num[N], len;
	void meset(){mt(num, 0); len = 1;}
	BIGNUM operator + (BIGNUM a) const {
		BIGNUM res = (BIGNUM){{}, max(a.len, len)};
		for (int i = 1; i <= res.len; i++)
		{
			res.num[i] += a.num[i] + num[i];
			res.num[i + 1] += res.num[i] / base;
			res.num[i] %= base;
		}
		if (res.num[res.len + 1])res.len++;
		return res;
	}
	void print()
	{
		for (int i = len; i; i--)
			if (i == len)cout << num[i];
			else cout << setw(18) << setfill('0') << num[i];
	}
}ans[N], sum;
signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)cin >> a[i];
	for (int i = 1; i <= n; i++)dp[i] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
			if (a[j] > a[i])dp[i] = max(dp[i], dp[j] + 1);
		if (dp[i] > dp[last])last = i;
	}
	for (int i = 1; i <= n; i++)
	{
		if (dp[i] == 1)ans[i] = (BIGNUM){{0, 1}, 1};
		for (int j = 1; j < i; j++)
			if (a[j] > a[i] && dp[j] + 1 == dp[i])ans[i] = ans[i] + ans[j];
			else if (a[j] == a[i] && dp[j] == dp[i])ans[j].meset();
	}
	for (int i = 1; i <= n; i++)
		if (dp[i] == dp[last])sum = sum + ans[i];
	cout << dp[last] << " ";
	sum.print();
	return 0;
}
```

---

