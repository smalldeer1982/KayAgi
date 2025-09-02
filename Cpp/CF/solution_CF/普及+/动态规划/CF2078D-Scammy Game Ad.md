# Scammy Game Ad

## 题目描述

考虑以下游戏。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2078D/08bde909876902ee9b6ced6653b4847e8c05fa58.png)

游戏中每个关卡包含 $n$ 对门。每对门包含一个左门和一个右门。每个门执行以下两种操作之一：
- **加法操作 (+ $a$)**：将该通道的人数增加固定值 $a$。
- **乘法操作 (× $a$)**：将该通道当前人数乘以整数 $a$。这意味着该通道人数将增加 $(a - 1)$ 倍当前值。

每个操作产生的新增人员可以分配到任意通道。但已存在于某个通道的人员不可转移到另一个通道。

初始时，每个通道各有 $1$ 人。你的任务是确定关卡结束时可达到的最大总人数。

## 说明/提示

第一个测试用例的最优操作方式如下：

初始时，左通道人数 $l=1$，右通道人数 $r=1$。

通过第一对门后：
- 左门产生 $4$ 人（加法操作），右门产生 $1 \cdot (2-1) = 1$ 人（乘法操作）
- 总新增 $4+1=5$ 人，分配 $2$ 人到左通道，$3$ 人到右通道
- 结果：$l=1+2=3$，$r=1+3=4$

通过第二对门后：
- 左门产生 $3 \cdot (3-1) = 6$ 人（乘法操作），右门产生 $4 \cdot (3-1) = 8$ 人（乘法操作）
- 总新增 $6+8=14$ 人，均分 $7$ 人到两个通道
- 结果：$l=3+7=10$，$r=4+7=11$

通过最后一对门后：
- 左门产生 $7$ 人（加法操作），右门产生 $4$ 人（加法操作）
- 总新增 $7+4=11$ 人，分配 $6$ 人到左通道，$5$ 人到右通道
- 结果：$l=10+6=16$，$r=11+5=16$

最终总人数为 $16+16=32$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
+ 4 x 2
x 3 x 3
+ 7 + 4
4
+ 9 x 2
x 2 x 3
+ 9 + 10
x 2 + 1
4
x 2 + 1
+ 9 + 10
x 2 x 3
+ 9 x 2
5
x 3 x 3
x 2 x 2
+ 21 + 2
x 2 x 3
+ 41 x 3```

### 输出

```
32
98
144
351```

# 题解

## 作者：chenxi2009 (赞：2)

## 思路
动态规划，左道 $0$ 右道 $1$，令 $f_{i,j}$ 表示 $j$ 道上第 $i$ 次操作**前**放上一个人，这个人可以对答案造成的贡献（当然小人自己本身算 $1$）。

初始令 $f_{n+1,0}=f_{n+1,1}=1$，然后从大到小递推，放在有加法一道的人只有后续沿这条道走下去的贡献（因为多一个人不会让加法生成更多的人）；放在有乘法一道的人除了有自己沿这条道走下去的贡献外，还有自己做乘法后额外产生的人的最大贡献。形式化地：
$$
f_{i,j}=\begin{cases}
f_{i+1,j}(\text{op}_{i,j}\ \text{is}\ +)\\
f_{i+1,j}+(a_{i,j}-1)\times\max(f_{i+1,0},f_{i+1,1})(\text{op}_{i,j}\ \text{is}\ \text{x})
\end{cases}
$$
然后我们就获知了每一次操作前小人放在两道的收益，贪心地，每一轮产生的小人放在下一轮开始前收益较大的一侧，模拟即可得出答案。

时间复杂度 $O(tn)$。
## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int T,n,a[40][2];
long long f[40][2],l,r,cnt;
char op[40][2][10];
int main(){
	T = read();
	while(T --){
		n = read();
		for(int i = 1;i <= n;i ++){
			scanf("%s",x[i][0] + 1);
			a[i][0] = read();
			scanf("%s",x[i][1] + 1);
			a[i][1] = read();
		}
		l = r = f[n + 1][0] = f[n + 1][1] = 1;
		for(int i = n;i;i --){
			f[i][0] = f[i + 1][0],f[i][1] = f[i + 1][1];//这个人本身走下去产生的价值 
			if(x[i][0][1] == 'x') f[i][0] += (a[i][0] - 1) * max(f[i + 1][0],f[i + 1][1]);//如果这个人经过了乘法，会额外产生 a_{i,0/1}-1 个人 
			if(x[i][1][1] == 'x') f[i][1] += (a[i][1] - 1) * max(f[i + 1][0],f[i + 1][1]);
		}
		for(int i = 1;i <= n;i ++){
			cnt = 0;//cnt 统计这一轮会增加多少人 
			if(x1[i][1] == '+') cnt += a1[i];
			else cnt += l * (a1[i] - 1);
			if(x2[i][1] == '+') cnt += a2[i];
			else cnt += r * (a2[i] - 1);
			if(f[i + 1][0] > f[i + 1][1]) l += cnt;//产生的人去往价值高的一方 
			else r += cnt;
		}
		printf("%lld\n",l + r);
	}
	return 0;
}
```

---

## 作者：lhc0707 (赞：1)

从前往后看问题，发现问题具有后效性，没法 DP，折半也是不行的因为我们并不能很好地合并前后两端的答案，于是正难则反，考虑反着做，发现这样就没有后效性，只用考虑后几位的答案就行了。

再求值之前，我们先做一些操作。我们将左边的门编号为 $0$，右边的门编号为 $1$，我们设 $a_{i,o}$ 表示第 $i$ 关编号为 $o$ 的门做乘法操作的倍数，如果是加法门，就令 $a_{i,o}=1$，然后另计 $b_{i,o}$ 表示加上的数。。我们设 $f_{i,o}$ 表示考虑到第 $i$ 个关卡左/右边的门对前面的决策产生的贡献。易知对于当前一个门，加法门所产生的贡献并不会对前面造成什么影响，而对于每个门产生的贡献，把这些贡献全部放到能产生更大贡献的那一边要比留一些在更劣的一边优，于是我们得到递推式

$$f_{i,o}=f_{i+1,o}+(a_{i,o}-1)\max(f_{i+1,0},f_{i+1,1})$$

并且如果当前出现加法门，则使

$$ans\leftarrow ans+b_{i,o}\max(f_{i+1,0},f_{i+1},1)$$

并且在最后给答案加上 $f_{1,0}+f_{1,1}$，时间复杂度 $O(nT)$，好奇为什么 $n$ 要放这么小。

code:

```cpp
#include<iostream>
#include<cstdio>
#define ll __int128
using namespace std;
inline int rd()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?x:-x;
}
void wt(ll x)
{
	if(x<0)	putchar('-'),x=-x;
	if(x>9)wt(x/10);
	putchar(x%10+'0');
}
const int N=35;
int n,a[N][2],b[N][2];
ll f[N][2],ans;
char op[N][2];
int main()
{
	int tt=rd();
	while(tt--)
	{
		n=rd(),ans=0;
		for(int i=1;i<=n;i++)
		{
			op[i][0]=getchar();getchar();
			if(op[i][0]=='+')a[i][0]=1,b[i][0]=rd();
			else a[i][0]=rd(),b[i][0]=0;
			op[i][1]=getchar();getchar();
			if(op[i][1]=='+')a[i][1]=1,b[i][1]=rd();
			else a[i][1]=rd(),b[i][1]=0;
		}
		f[n][0]=a[n][0],f[n][1]=a[n][1];
		if(op[n][0]=='+')ans+=b[n][0];
		if(op[n][1]=='+')ans+=b[n][1];
		for(int i=n-1;i>=1;i--)
		{
			for(int j=0;j<=1;j++)f[i][j]=f[i+1][j]+(a[i][j]-1)*max(f[i+1][0],f[i+1][1]);
			for(int j=0;j<=1;j++)if(op[i][j]=='+')ans+=b[i][j]*max(f[i+1][0],f[i+1][1]);
		}
		ans+=f[1][0]+f[1][1];
		wt(ans);
		puts("");
	}
	return 0;
}
```

---

## 作者：Yorg (赞：1)

## 思路
### 题意
抖音小游戏。

$n$ 道门，给定每道门左右两侧对应的操作 $\times a \textrm{ or } {+b}$，其中 $a\leq 3,b\leq 1000$。\
最初左右两道只有各 $1$ 人，每次操作增加的人数可以分配到任一车道，但是，已在一条车道上的人数**不能**被移动到另一条车道上。

求最终两车道的人数之和最多是多少。

### 性质

不难发现一个性质，因为乘法的可拆性，每次额外可分配的人数放到一条路径上之后，其本身的贡献是确定的。
#### 解释
这样说吧，假设当前有 $k$ 个人可以选择分配到任意一条道路上，我们只需要知道其后有多少乘法操作，就可以知道这一波人的贡献。
而后面产生的新的可分配人的贡献又是另外计算的了。

本质上就是乘法分配律。

---
### 做法
于是不难想到一个假做法，每次分配的人贪心地放到后面贡献最大的道路上。

看起来很正确，实则不然。你发现这样做，虽然保证了每次分配的人贡献最大，但是不能保证能够被分配的人数最多。很有可能会出现有一些可以被分配的人没有被分配。
#### 举个例子
![](https://s21.ax1x.com/2025/03/11/pENbnRH.png)

这种情况下，$\times 2$ 产生的东西一定会被全部放到左路。

然而你发现，完全可以放到右路之后，把 $\times 3$ 吃了放回左路，这样一定更优秀。

---
怎么处理？发现这已经不是简单的贪心了，必须出重拳！

类似于一个新问题：如何移动才能使得当次分配的人总共产生的贡献最大（也就是分出去的贡献也最大，比较抽象）。找性质，发现最优解大概就是左右横跳，尽可能吃到更多的乘法。考虑动态规划。

设 $f_{i, 0/1}$ 表示处于第 $i$ 个门的左/右，在 $i$ 后面的最优分配方法带来的倍数收益。初始化 $f_{i, 0/1}$ 为当前这个门的乘法系数（没有设为 $1$）。
$$
f_{i, 0} = \max\Big\{f_{i, 0} \times f_{i + 1, 0}, f_{i + 1, 0} + (f_{i, 0} - 1) \times f_{i + 1, 1}\Big\} \\
f_{i, 1} = \max\Big\{f_{i, 1} \times f_{i + 1, 1}, f_{i + 1, 1} + (f_{i, 1} - 1) \times f_{i + 1, 0}\Big\}
$$
然后每次贪心的选择更优的那个路径即可。

## 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <utility>  // for std::pair

#define endl '\n'

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 100005;

// 定义操作结构体
struct Operation {
    char type;  // 操作符类型 ('x' 或 '+')
    ll val;     // 操作数值
};
// 用 pair 封装左右操作
std::pair<Operation, Operation> ops[MAXN];
ll count_left[MAXN] = {1};
ll count_right[MAXN] = {1};
ll f[MAXN][2] = {0};

int main() {
    ll t;
    scanf("%lld", &t);

    while (t--) {
        ll n;
        scanf("%lld", &n);
        count_left[0] = count_right[0] = 1;
        // 输入处理
        for (ll i = 1; i <= n; ++i) {
            Operation op_left, op_right;
            // 注意 val 用 %lld 读取
            scanf(" %c %lld %c %lld", 
                &op_left.type, &op_left.val, 
                &op_right.type, &op_right.val);
            ops[i] = {op_left, op_right};

            // 计算累积值
            count_left[i] = count_left[i - 1];
            count_right[i] = count_right[i - 1];
            if (ops[i].first.type == 'x') count_left[i] *= ops[i].first.val;
            if (ops[i].second.type == 'x') count_right[i] *= ops[i].second.val;
        }


        // 动态规划计算
        for (ll i = n; i >= 1; --i) {
            ll t1 = count_left[i] / count_left[i - 1];
            ll t2 = count_right[i] / count_right[i - 1];
            f[i][0] = t1;
            f[i][1] = t2;

            if (i != n) {
                f[i][0] = std::max(f[i][0] * f[i + 1][0], 
                                  f[i + 1][0] + (f[i][0] - 1) * f[i + 1][1]);
                f[i][1] = std::max(f[i][1] * f[i + 1][1], 
                                  f[i + 1][1] + (f[i][1] - 1) * f[i + 1][0]);
            }
        }

        ll ans_left = 1, ans_right = 1;

        // 计算结果
        for (ll i = 1; i <= n; ++i) {
            const auto& [op_left, op_right] = ops[i];  // C++17 结构化绑定
            ll add = 0;

            // 处理左操作
            if (op_left.type == 'x') 
                add += ans_left * (op_left.val - 1);
            else 
                add += op_left.val;

            // 处理右操作
            if (op_right.type == 'x') 
                add += ans_right * (op_right.val - 1);
            else 
                add += op_right.val;

            // 分配结果
            if (i != n) {
                if (f[i + 1][0] >= f[i + 1][1])
                    ans_left += add;
                else
                    ans_right += add;
            } else {
                ans_left += add;
            }
        }

        printf("%lld\n", ans_left + ans_right);
    }

    return 0;
}
```

## 总结
常数条路径互相跳，求贡献最优这种问题，往往可以类似的解决。

一类不知道应该怎么决策的问题，可以尝试用 dp 辅助解决。

---

## 作者：Wei_Han (赞：0)

有点诈骗了吧。

发现正着贪心会对后面产生影响，影响不好计算，我们直接考虑倒着做。

令 $f_{i/0,1}$ 表示以 $1$ 开始经过第 $i$ 层左/右门及其后面所有门的最大价值。

先认定当前是乘法，假设当前在左门，因为初始的 $1$ 个人是固定不动的，所以他一定会走下一行的左门，也就是必须有一个 $f_{i+1,0}$，剩下多余的人可以选择 $\max(f_{i,0},f_{i,1})$ 走，右门同理。也就是有转移 $f_{i,j} = f_{i+1,j} + (a_{i,j} -1) \times \max(f_{i+1,0},f_{i+1,1})$。

如果当前是加法的话，令 $a_{i,j} = 1$ 即可，还是满足上面的式子，然后对于这一个门新增的人数肯定和上面的所有门产生的人数无关，产生的贡献是独立的，直接取 $\max$ 走就好了，对答案的贡献是 $a_{i,j} \times\max(f_{i+1,0},f_{i+1,1})$。

记得开 ```__int128```，复杂度 $O(Tn)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define pb push_back
//#pragma GCC optimize(2)
using namespace std;
//typedef int ll;
//typedef long long ll;
typedef __int128 ll;
typedef double db;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const ll N=1e6+5,M=2e4+5,mod=1e9+7;
ll n,f[N][2],a[N][2],b[N][2];
char ch[N][2];
inline void solve()
{
	read(n);fo(1,i,n) fo(0,j,1){cin>>ch[i][j];if(ch[i][j]=='+') a[i][j]=1,read(b[i][j]);else read(a[i][j]),b[i][j]=0;}
	f[n][0]=a[n][0],f[n][1]=a[n][1];
	ll ans=0;
	if(ch[n][0]=='+') ans+=b[n][0];
	if(ch[n][1]=='+') ans+=b[n][1];
	Fo(n-1,i,1)
	{
		fo(0,j,1) f[i][j]=f[i+1][j]+(a[i][j]-1)*max(f[i+1][0],f[i+1][1]);
		fo(0,j,1) if(ch[i][j]=='+') ans+=b[i][j]*max(f[i+1][0],f[i+1][1]);
	}
	wr(ans+f[1][0]+f[1][1]),pr;
	fo(1,i,n) fo(0,j,1) f[i][j]=a[i][j]=b[i][j]=0;
}
signed main(){
	ll tt;read(tt);while(tt--){solve();}
	return 0;
}
``````

---

