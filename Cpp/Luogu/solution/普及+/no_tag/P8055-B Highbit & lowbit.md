# B Highbit & lowbit

## 题目描述

定义一个正整数的 $\mathrm{highbit}$ 为该数在二进制表示下的最高二进制位的位值，如 $\mathrm{highbit}(22_{(10)})=\mathrm{highbit}(10110_{(2)})=10000_{(2)}=16_{(10)}$。

定义一个正整数的 $\mathrm{lowbit}$ 为该数在二进制表示下的最低非零二进制位的位值，如 $\mathrm{lowbit}(22_{(10)})=\mathrm{lowbit}(10110_{(2)})=10_{(2)}=2_{(10)}$。

再定义两种操作：

- 操作 $1$：将一个正整数 $x$ 变为 $x+\mathrm{lowbit}(x)$。
- 操作 $2$：将一个正整数 $x$ 变为 $x+\mathrm{highbit}(x)$。

现给定一个操作序列和 $q$ 次询问，每次询问包含 $3$ 个正整数 $l,r,x$，表示将 $x$ 从左到右依次执行 $l\sim r$ 的操作，请输出 $x$ 的值，由于答案可能很大，请输出答案对 $10^9+7$ 取模的值。

## 说明/提示

**【数据范围】**

**本题采用捆绑测试。**

对于所有测试点，满足 $1\leq n,q\leq 5\times 10^5$，$1\leq x<2^{30}$。详细数据范围如下：

- Subtask #1 (12 pts): $n,q\le 10$，$x\le 32767$。
- Subtask #2 (23 pts): $n,q\le 10^3$。
- Subtask #3 (11 pts): $n,q\leq 10^5$，字符串中仅含有 `1`。
- Subtask #4 (11 pts): $n,q\leq 10^5$，字符串中仅含有 `0`。
- Subtask #5 (6 pts): $n,q\leq 10^5$，保证每次询问的 $x$ 均可以表示为 $2^a$ 的形式，$a$ 为非负整数。
- Subtask #6 (15 pts): $n,q\leq 10^5$，保证每次询问的 $x$ 均可以表示为 $2^a+2^b$ 的形式，$a,b$ 均为非负整数。
- Subtask #7 (10 pts): $n,q\le 10^5$。
- Subtask #8 (12 pts): 没有任何附加限制。

## 样例 #1

### 输入

```
8 8
01100001
1 2 3
1 4 9
2 6 9
3 8 9
6 8 2
8 8 3
5 8 6
2 8 17```

### 输出

```
8
36
40
64
16
5
64
144```

# 题解

## 作者：Suzt_ilymtics (赞：17)

update on 2022/03/16: 感谢 @Clarence_Zhu 指出一处手误的地方。

------------

[题面传送w](https://www.luogu.com.cn/problem/P8055)

## Solution

### Subtask1

模拟。

复杂度 $\mathcal O(nq)$。

### Subtask2

记录位数模拟。

复杂度 $\mathcal O(nq)$

### Subtask3

观察操作 $2$ 的本质，把最高位的 $1$ 由 $k$ 位移到了 $k+1$ 位。

那每次操作一定是把最高位 $1$ 由 $k$ 位移到了 $k+r-l+1$ 位。

所以每次询问的答案为 $x - 2^k + 2^{k+r-l+1}$。

### Subtask5

~~4 没写~~

发现如果整个数在二进制位上只有一位是 $1$ 的话两种操作都可以看作将最高位的 $1$ 由 $k$ 位移到 $k+1$ 位。

然后这个和 Subtask3 的答案是相同的。

### 正解

考虑两个操作的本质，

如果最高位的 $1$ 和最低位的 $1$ 不是同一位（分别设为 $R,L$）（如果是同一位就是 Subtask5），$1$ 操作就是让两个位置之间减少一个 $0$，$2$ 操作就是让两个位置之间增加一个 $0$。

设两个位置之间有 $k$ 个 $0$，通过 $k+1$ 次 $1$ 操作就能让整个数的二进制位上只有一个 $1$，剩下的操作就可以划归到 Subtask5。

考虑什么时候出现这种情况？在某个位置 $1$ 操作比 $2$ 操作多 $k+1$ 次时。

设 $sum_{0/1,i}$ 表示对 $0$ 操作和 $1$ 操作做的一个前缀和。

设找到的位置为 $x$，那么就是要满足下面的式子：

$$
(sum_{0,x} - sum_{0,l-1}) - (sum_{1,x} - sum_{1,l-1}) = k + 1
$$

并且这个位置应该是我们遇到的第一个满足这样条件的 $x$。

发现其中有两项是常量，设 $p = k+1 + sum_{0,l-1} - sum_{1,l-1}$。

式子变为：

$$
sum_{0,x} - sum_{1,x} = p
$$

我们可以用值域 `vector` 存下每个 $p$ 出现的位置，然后每次询问直接 `lower_bound` 一下找到第一个满足条件的 $x$。

如果能找到一个合法的 $x$，那么答案为 $2^{R + sum_{1,p} - sum_{1,l-1} + 1 + r - p}$。（这个结论手模一下应该就能算出来）

如果找不到的话，分两种情况讨论。

设 $s_0 = sum_{0,r} - sum_{0,l-1}, s_1 = sum_{1,r} - sum_{1,l-1}$。

如果 $s_0 \le k$，也就是说最低位的 $1$ 移动后不会超过 $R$ 一开始的位置，又因为 $L$ 和 $R$ 这两个位置之间的差一定不会超过 $\log x$ 位，所以这种情况 $1$ 操作暴跳就行，每次 `x+=lowbit(x)`，复杂度只有 $\log x$。对于 $2$ 操作可以和 Subtask3 一样处理。

如果 $s_0 > k$，说明 $L$ 会移动到 $R$ 一开始的位置，但是永远没有一个时刻 $L$ 会超过 $R$，也就是说此时整个数中只剩下了这两位有 $1$，那么直接算出两个 $1$ 在第几位输出答案即可。答案为 $2^{R+s_0-k} + 2^{R + s_1}$。

然后这题就做完了，复杂度应该是 $\mathcal O(q \log V)$。

## Code

```cpp
/*
Work by: Suzt_ilymtics
Problem: 不知名屑题
Knowledge: 垃圾算法
Time: O(能过)
*/
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define int long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 2e6+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

int n, Q;
int a[MAXN], sum[2][MAXN];
vector<int> b[MAXN];

int read() {
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch)) f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0', ch = getchar();
    return f ? -s : s;
}

int Getl(int x) { for(int i = 0; i <= 40; ++i) if(x & (1ll << i)) return i; }
int Getr(int x) { for(int i = 40; i >= 0; --i) if(x & (1ll << i)) return i; }
int lb(int x) { return x & (-x); }
int Pow(int x, int p) {
    int res = 1;
    while(p) {
        if(p & 1) res = res * x % mod;
        x = x * x % mod, p >>= 1;
    }
    return res;
}

signed main()
{
    n = read(), Q = read();
    for(int i = 1; i <= n; ++i) scanf("%1d", &a[i]);
    for(int i = 1; i <= n; ++i) 
        sum[0][i] = sum[0][i - 1] + (a[i] == 0), sum[1][i] = sum[1][i - 1] + (a[i] == 1);
    int M = 100000;
    for(int i = 1; i <= n; ++i) b[M + sum[0][i] - sum[1][i]].push_back(i); // 用值域 vector 预处理一下位置
    for(int i = -M; i <= M; ++i) b[i + M].push_back(n + 1); // 每个值域都放一个 vector 方便判断有无解（其实我就是忘了 vector 用 lower_bound 找不到一个数是返回什么值）
    for(int i = 1, l, r, x; i <= Q; ++i) {
        l = read(), r = read(), x = read();
        int L = Getl(x), R = Getr(x), k = 0;
        if(L == R) { // Subtask5
            printf("%lld\n", Pow(2, L + r - l + 1));
        } else {
            ++k;
            for(int j = L; j <= R; ++j) if(!(x & (1ll << j))) ++k;
            k = M + k + sum[0][l - 1] - sum[1][l - 1];
            int p = lower_bound(b[k].begin(), b[k].end(), l) - b[k].begin();
            if(b[k][p] > r) {
                int s0 = sum[0][r] - sum[0][l - 1], s1 = sum[1][r] - sum[1][l - 1];
                k = k - M - sum[0][l - 1] + sum[1][l - 1];
                if(s0 < k) { // 无解下的情况 1
                    int ans = Pow(2, R + s1);
                    x -= (1ll << R);
                    while(s0--) x += lb(x);
                    ans = (ans + x) % mod;
                    printf("%lld\n", ans);
                } else { // 无解下的情况 2
                    int ans = (Pow(2, R + s0 - k) + Pow(2, R + s1)) % mod;
                    printf("%lld\n", ans);
                }
            } else { // 有解的情况
                p = b[k][p];
                printf("%lld\n", Pow(2, R + sum[1][p] - sum[1][l - 1] + 1 + (r - p)));
            }
        }
    }
    return 0;
}
```


---

## 作者：dingcx (赞：8)

~~题解没保存删了，还得重写一遍。~~

## 思路

考虑两个操作对一个二进制数有什么影响。

$+lowbit$ 操作：把结尾的连续的 $1$ 删掉，并在这一连续段的前面一位加上一个 $1$（$1011 \to 1100$）。

$+highbit$ 操作：把开头的 $1$ 向前挪一位。

观察性质，发现只需要考虑二进制数中最前面和最后面的 $1$，且 $1$ 的个数不会减少。

很自然地想到：把对二进制数的操作的阶段按照 $1$ 的个数划分为三部分，分别为 $\ge 3,=2,=1$。

### 第一阶段

这一阶段二进制数中 $1$ 的个数 $\ge 3$。

因为原二进制数的位数 $\le 30$，所以这一阶段需要进行的 $+lowbit$ 操作次数不超过 $30$，可以暴力处理。

但在这其中可能有许多 $+highbit$ 操作，于是想到把操作序列的连续的 $+highbit$ 操作合并成一个，把二进制数的最高位的 $1$ 向左挪操作次数位。

在二进制数中 $1$ 的个数 $\le 2$ 时退出这一阶段。

### 第二阶段

这一阶段二进制数中 $1$ 的个数 $=2$。

这一阶段主要需要判断后面的 $1$ 在几次操作后能和前面的 $1$ 合并，形象理解成后面的 $1$ 在什么时候第一次追上前面的 $1$。

考虑两个操作，$+lowbit$ 会让两个 $1$ 距离减少 $1$，$+highbit$ 会让距离增加 $1$。

转换一下问题，把操作序列中 $+lowbit$ 操作看作 $-1$，$+highbit$ 操作看作 $+1$（把转换后的数组记为 $a$），求从操作序列当前位置（这个位置就是第一阶段到的位置，记为 $i$）开始，最小的位置 $j$（$j \ge i$），使得 $a_i+...+a_j=-k$（$k$ 为第一阶段结束时两个 $1$ 的距离）。

这个转换后的问题解法就是，先算一下 $a$ 的前缀和（记为 $s$），按 $s$ 的值记到 ```vector``` 中，那么这个问题就在值为 $s_{i-1}-k$ 的 ```vector``` 上二分找到第一个大于 $i$ 的值即可，可以用 ```lower_bound```。

如果能在 $r$ 之前追上，则进入第三阶段。

### 第三阶段

此时所有操作都对那唯一的 $1$ 操作，合一起往左移即可。

## 实现

记录二进制数：记录有 $1$ 的位数，以及每个 $1$ 在第几位，代码中为 $pos,tot$。

把所有的 $+highbit$ 操作合成一个：如果 $l$ 或 $r$ 在一段 $+highbit$ 操作的中间就很麻烦，我这里的做法是在操作序列每个位置初始化从这里开始往后连续的 $1$ 的个数，这样直接加即可，代码中为数组 $suf$。

$s$ 数组：在代码中没有写到 $s$，我用两个前缀和数组 $s0,s1$ 表示操作 $0,1$ 的个数的前缀和，相减即可得到 $s$。

```vector```：$s$ 数组中可能存在负数，所以需要整体加上 ```MAXN``` 处理（当然 ```vector``` 也需要开两倍）。

计算答案：算 $2$ 的（每个 $1$ 的位数）次幂的和，用快速幂。

## 代码

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
const int MAXN=5e5+10,MOD=1e9+7;
int op[MAXN],suf[MAXN],s1[MAXN],s0[MAXN],pos[35],tot=0; //定义见上
vector<int> vs[MAXN<<1]; //空间两倍
int read(){
	int num=0,sign=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sign=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
	return num*sign;
}
void output(){ //算答案
	int ans=0;
	for(int i=1;i<=tot;i++){
		ll res=1,a=2;
		while(pos[i]){
			if(pos[i]&1) res=res*a%MOD;
			a=a*a%MOD,pos[i]>>=1;
		}
		ans=(ans+res)%MOD;
	}
	printf("%d\n",ans);
}
int main(){
	int n=read(),q=read();scanf("\n");
	for(int i=1;i<=n;i++) op[i]=getchar()-'0';
	for(int i=n;i>0;i--)
		if(op[i]==1) suf[i]=suf[i+1]+1; //算后面连续的 1 的个数
	for(int i=1;i<=n;i++){
		s1[i]=s1[i-1]+op[i]; //算 0,1 的前缀个数
		s0[i]=s0[i-1]+(op[i]^1);
		vs[s0[i]-s1[i]+MAXN].push_back(i); //把 s 的值记到 vector 中，注意 +MAXN
	}
	while(q--){
		int l=read(),r=read(),x=read();tot=0;
		for(int i=29;i>=0;i--)
			if((1<<i)&x) pos[++tot]=i; //转二进制
		int i=l;
		while(tot>2&&i<=r){ //第一阶段
			if(op[i]==0){ //暴力处理 +lowbit
				while(pos[tot]+1==pos[tot-1]) tot--; //去掉连续的 1
				pos[tot]++,i++; //前面加一个 1
			}
			else{ //用 suf 数组处理 +highbit
				if(i+suf[i]>r) //超了
					pos[1]+=(r-i+1),i=r+1;
				else pos[1]+=suf[i],i+=suf[i];
			}
		}
		if(i>r){output();continue;} //第一阶段就已经结束了
		if(tot==2){ //第二阶段
			int num=pos[1]-pos[2]+s0[i-1]-s1[i-1]+MAXN; //也就是前面的 s[i-1]-k
			int p=lower_bound(vs[num].begin(),vs[num].end(),i)-vs[num].begin(); //二分
			if(p==vs[num].size()||vs[num][p]>r) //到 r 也追不上
				pos[1]+=(s1[r]-s1[i-1]),pos[2]+=(s0[r]-s0[i-1]),i=r+1;
			else pos[1]+=(s1[vs[num][p]]-s1[i-1]+1),i=vs[num][p]+1,tot=1; //能追上
		}
		if(i>r){output();continue;} //第二阶段就结束了
		pos[1]+=(r-i+1); //第三阶段
		output(); //第三阶段结束
	}
	return 0; //华丽结束
}
```

不要忘了点赞~

---

## 作者：Jur_Cai (赞：6)

先考虑 $x$ 是 $2^n$ 的形式，那么 $\operatorname{lowbit}$ 与 $\operatorname{highbit}$ 的效果都相当于右移（ 即 $\times 2$ ），可以直接 $O(1)$ 算答案。

然后可以发现一个比较显然的性质：一个数加一次 $\operatorname{lowbit}$ 二进制下的一段 $1$ 会只剩一个 $1$，那么 $x$ 在没有 $\operatorname{highbit}$ 的情况下最多需要 $\log_2 x$ 次 $+\operatorname{lowbit}$ 二进制下就只剩 $1$ 个 $1$ 了（ 其实不会到 $\log$ 次，可以提前算出来需要几次 ）。

如果有 $\operatorname{highbit}$ 呢？只要找一个区间内最早的位置满足：

$$
(Sum_{lowbit_p}-Sum_{lowbit_{l-1}})-(Sum_{highbit_p}-Sum_{highbit_{l-1}}) \ge f(x)
$$

$Sum$ 是 $+\operatorname{lowbit}$ / $+\operatorname{highbit}$ 个数的前缀和。

$f(x)$ 是 $x$ 在二进制下变为 $1$ 个 $1$ 需要的 $lowbit$ 次数。

可以移项，得到：

$$
Sum_{lowbit_p}-Sum_{highbit_p} \ge f(x)+Sum_{lowbit_{l-1}}-Sum_{highbit_{l-1}}
$$

但是式子左边的东西并没有单调性，需要前缀 $\max$ 使其可以二分，实现可以是二分之后用 st 表进行验证。

如果找不到，就把最高位和剩下的分开处理。

原数为 $2^n$ 的要特殊处理一下，就可以过了这题。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define ll long long
using namespace std;
inline int real_popcount(ll x) {
    int res=0;
    while(x) {
        if(x&1) res++;
        x>>=1;
    }
    return res;
}
//计算上面定义的 f(x)
inline int popcount(ll x) {
    int res=0,last=0;
    while(x) {
        if(x&1) last=1;
        else if(last) res++;
        x>>=1;
    }
    return res+1;
}
inline ll highbit(ll x) {
    int res=0;
    while(x) {
        x>>=1;
        res++;
    }
    return 1ll<<(res-1);
}
inline ll lowbit(ll x) {
    return x&-x;
}
inline ll ksm(int b,int p) {
    ll base=b,res=1;
    while(p) {
        if(p&1) res=(res*base)%mod;
        base=(base*base)%mod,p>>=1;
    }
    return res;
}
int sum0[500005],sum1[500005],maxn[500005][20],lg[500005];
inline int query(int l,int r) {
    int p=lg[r-l+1];
    return max(maxn[l][p],maxn[r-(1<<p)+1][p]);
}
//二分查找
inline int getpos(int l,int r,int x) {
    int ans=r+1;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(query(l,mid)>=x) ans=mid,r=mid-1;
        else l=mid+1;
    }
    return ans;
}
int main() {
    int n,q;
    scanf("%d%d",&n,&q),lg[0]=-1;
    for(int i=1; i<=n; i++) {
        char x;
        cin>>x;
        lg[i]=lg[i>>1]+1;
        sum0[i]=sum0[i-1];
        sum1[i]=sum1[i-1];
        if(x=='0') sum0[i]++;
        else sum1[i]++;
        maxn[i][0]=sum0[i]-sum1[i];
    }
    for(int j=1; (1<<j)<=n; j++)
        for(int i=1; i+(1<<j)-1<=n; i++)
            maxn[i][j]=max(maxn[i][j-1],maxn[i+(1<<(j-1))][j-1]);
    while(q--) {
        int l,r,x;
        scanf("%d%d%d",&l,&r,&x);
        if(real_popcount(x)==1) {
            cout<<1ll*x*ksm(2,r-l+1)%mod<<'\n';
            continue;
        }
        int tot=popcount(x);
        int p=getpos(l,r,tot+sum0[l-1]-sum1[l-1]);
        if(p>r) {
            //找不到就分开处理
            ll y=highbit(x);
            ll z=x-y;
            ll need=popcount(z);
            if(sum0[r]-sum0[l-1]<=need) {
                for(int i=sum0[r]-sum0[l-1]; i>=1; i--) z=(z+lowbit(z))%mod;
            } else {
                z=(highbit(z)<<1)%mod;
                z=z*ksm(2,(sum0[r]-sum0[l-1]-need))%mod;
            }
            y=y*ksm(2,sum1[r]-sum1[l-1])%mod;
            cout<<(y+z)%mod<<'\n';
        } else {
            ll y=(highbit(x)<<1)%mod;
            y=y*ksm(2,sum1[p]-sum1[l-1])%mod;
            y=y*ksm(2,r-p)%mod;
            cout<<y<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：danny101 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8055)

题目大意：求解一些数执行一定数量的 $\textbf{highbit}$ 与 $\textbf{lowbit}$ 后的值。

考场思路：分成一个个 $\textbf{Subtask}$ 来处理。

$\textbf{Subtask 1:}$

暴力。不再多说。

$\textbf{Subtask 2:}$

考场上玄学WA（

其实按位模拟即可。$\mathcal{O}(nq)$ 搞定。

$\textbf{Subtask 3:}$

既然只有 $\textbf{1}$，把最高位乘上 $2^{r-l+1}$ 即可。

$\textbf{Subtask 4:}$

既然只有 $\textbf{0}$，从低位开始模拟即可。可以证明，复杂度只有 $\mathcal{O}(\log n)$。

$\textbf{Subtask 5:}$

因为对 $2^a$ 形式的数，无论 $\textbf{highbit}$ 还是 $\textbf{lowbit}$ 的效果都是原数增加一倍，那么答案一定是原数乘 $2^{r-l+1}$。

$\textbf{Subtask 6:}$

可以利用前缀和求出什么时候低位可以追上高位，之后会退化为 $\textbf{Subtask 5}$。追不上的话，用另一个前缀和求出最后的 $2^a$ 和 $2^b$ 相加得到答案。

$\textbf{Subtask 7\&Subtask 8:}$ 考场上没想出来（

#### 正解：

用 $low$ 数组记录每一次 $\textbf{lowbit}$ 操作的位置，$sum$ 数组记录 $\textbf{highbit}$ 的前缀和，$f$ 数组记录 $\textbf{highbit}$ 与 $\textbf{lowbit}$ 的差的前缀和，以及每个 $f$ 数组中的值出现的位置。

接下来，我们可以开始模拟 $\textbf{lowbit}$ 操作，直到变为 $2^a$ 或 $2^a+2^b$ 的形式，最通过记录的 $f$ 数组中的值出现的位置分出究竟是变成 $2^a$ 还是 $2^a+2^b$，用 $\textbf{Subtask 5}$ 和 $\textbf{Subtask 6}$ 的方法处理就行了。

#### 代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,l,r,x,i,m,cur,low[500001],sum[500001],f[500001],pow2[500001];
char s[500005];
vector<int>P[1000005];
inline int highb(int x){
	int tmp=1;
	while(tmp<=x)tmp<<=1;
	return tmp>>1;
}
inline int lowb(int x){
	return x&(-x);
}
void wr(int x){
	if(x>9)wr(x/10);
	putchar(x%10+'0');
}
void put(int x){
	wr(x);
	putchar('\n');
}
signed main(){
    scanf("%d%d%s",&n,&m,s+1);
	pow2[0]=1;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+s[i]-'0';
		f[i]=f[i-1]+(s[i]-'0')*2-1;
		pow2[i]=pow2[i-1]*2%mod;
		if(s[i]=='0')low[++cur]=i;
		P[n+f[i]].push_back(i);
	}
	for(int i=0;i<=n*2;i++)P[i].push_back(n+1);//上界
	while(m--){
		scanf("%d%d%d",&l,&r,&x);
		int hi=highb(x);
		x^=hi;
		if(x==0){//2^a
			put(hi*pow2[r-l+1]%mod); 
			continue;
		}
		int pos=lower_bound(low+1,low+cur+1,l)-low;//第一次lowbit操作
		for(i=pos;i<=cur&&low[i]<=r&&x!=hi/*没有到2^a*/;i++)x+=lowb(x);
		if(x!=hi)put((hi*pow2[sum[r]-sum[l-1]/*[l,r]里highbit的次数*/]+x)%mod);//既然追不上，处理highbit就行
		else{//只剩1或2位了
			int high=sum[low[--i]]-sum[l-1];//从l到最后一次lowbit之间highbit的次数
				if(id>r)put((hi*pow2[sum[r]-sum[l-1]]+hi*pow2[(r-low[i]-(sum[r]-sum[l
			if(high==0)put(hi*2*pow2[r-low[i]]%mod);//如果没有，则highbit全都集中在最后面，直接处理
			else{
				int t=n+f[low[i]]-high/*lowbit数量*/,id=*upper_bound(P[t].begin(),P[t].end(),low[i]);
				if(id>r)put((hi*pow2[sum[r]-sum[l-1]]+hi*pow2[(r-low[i]-(sum[r]-sum[low[i]]))])%mod);//2^a+2^b，追不上
				else{
					high+=sum[id]-sum[low[i]];
					put(hi*pow2[(++high)+r-id]%mod);//2^a，追上了
				}
			}
		}
	}
}
```

---

## 作者：Elma_ (赞：1)

一个简单的事实：若 $x$ 是 $2$ 的若干次幂，那么 $\mathrm{highbit}(x) = \mathrm{lowbit}(x) = x$。

另一个简单的事实：操作 $2$ 只可能影响二进制下的一个为 $1$ 的位置，而操作 $1$ 可能会将多个为 $1$ 的位置合并。

对于 $x = 2^a$ 的情况，$x$ 在二进制表示下只会有 $1$ 个位置上是 $1$，那么显然两种操作都只会使得 $x \leftarrow x \times 2$ ，设区间长度为 $c$，那么答案即为 $x \times 2^c$，预处理 $2$ 的幂次就可以 $O(1)$ 回答询问。

对于 $x = 2^a + 2^b(a>b)$ 的情况，$x$ 在二进制表示下会有 $2$ 个位置上是 $1$，此时操作 $1$ 相当于令 $a \leftarrow a+1$，操作 $2$ 相当于令 $b \leftarrow b+1$。此时可能有两种情况：

- 如果在某个时刻 $a=b$ 了，那么这两个 $1$ 的位就会合并成一个 $1$，转化成了 $x = 2^a$ 的情况。
- 如果没有合并，那么答案可以根据两种操作的次数直接计算。

对于没有合并的情况，两种操作的次数可以使用前缀和快速计算。现在考虑如何判断这两位是否会发生合并。

我们把操作 $1$ 看做 $1$，操作 $2$ 看做 $-1$，计算出前 $i$ 个操作的前缀和 $s_i$，那么 $a$ 和 $b$ 会合并当且仅当存在一个 $i \in [l,r]$ 使得 $s_i \geq s_{l-1} + b - a$。注意到 $|s_i - s_{i - 1}| = 1$，那么我们只需要找到 $s_{l - 1} + b - a$ 在 $l$ 后第一次出现的位置，因为 $s_i$ 的值域是 $O(n)$ 的，我们可以对每个值相同的 $s_i$ 开一个 vector 存下它们的位置，每次只需要在对应的 vector 上二分就可以了。

然后你会发现其实已经做完了...因为 $x$ 最多进行不超过 $\log x$ 次操作 $1$ 就会变成 $2^a+2^b$ 的形式，我们可以暴力找到这个次数 $c$，然后在询问的区间上二分找到 $x$ 变为 $2^a+2^b$ 形式的这段时间内有多少次操作 $2$，加上操作 $2$ 的影响后就可以按 $x = 2^a+2^b$ 的方式计算。

时间复杂度 $O(n + q(\log n + \log x))$，代码细节可能略多。

```cpp
int N, Q, A[MN], S[MN], S1[MN], S2[MN], Pow[MN]; char Str[MN];
vector <int> buc[MN * 2];

inline int lowbit(int x) {
    return x & (-x);
}

signed main(void) { 
    N = read(), Q = read(), scanf("%s", Str + 1);
    Pow[0] = 1;
    for (int i = 1; i <= N; i++) Pow[i] = Pow[i - 1] * 2 % Mod;
    for (int i = 1; i <= N; i++) {
        if (Str[i] == '0') S[i] = S[i - 1] + 1, S1[i] = S1[i - 1] + 1, S2[i] = S2[i - 1];
        else S[i] = S[i - 1] - 1, S1[i] = S1[i - 1], S2[i] = S2[i - 1] + 1;
    }
    for (int i = 1; i <= N; i++) buc[S[i] + N].pb(i);
    while (Q--) {
        int l = read(), r = read(), x = read();
        if (x == lowbit(x)) {
            printf("%lld\n", x * Pow[r - l + 1] % Mod);
            continue;
        }
        int a = 0, b = 0;
        int B = 1, o = x, c = 0;
        while ((B << 1) <= x) B <<= 1, a++;
        o -= B;
        while (o != lowbit(o)) o += lowbit(o), c++;
        b = (int)log2(o);
        int L = l - 1, R = r, p = -1;
        while (L <= R) {
            int mid = (L + R) >> 1;
            if (S1[mid] - S1[l - 1] >= c) R = mid - 1, p = mid;
            else L = mid + 1;
        }
        if (p == -1) {
            int c1 = S1[r] - S1[l - 1], c2 = S2[r] - S2[l - 1];
            x -= B;
            while (c1--) x += lowbit(x);
            printf("%lld\n", (x + B * Pow[c2] % Mod) % Mod);
            continue;
        }
        int c1 = S1[p] - S1[l - 1], c2 = S2[p] - S2[l - 1];
        B = B * Pow[c2] % Mod, a += c2;
        int pos = S[p] + a - b + N, q = 0;
        if (buc[pos].size()) {    
            L = 0, R = buc[pos].size() - 1;
            while (L <= R) {
                int mid = (L + R) >> 1;
                if (buc[pos][mid] >= p) R = mid - 1, q = buc[pos][mid];
                else L = mid + 1;           
            }
        }
        if (!q || q > r) {
            int c1 = S1[r] - S1[p], c2 = S2[r] - S2[p];
            printf("%lld\n", (B * Pow[c2] % Mod + o * Pow[c1] % Mod) % Mod);
            continue;
        }
        c1 = S1[q] - S1[p], c2 = S2[q] - S2[p], c = r - q;
        int C = (B * Pow[c2] % Mod + o * Pow[c1] % Mod) % Mod;
        printf("%lld\n", C * Pow[c] % Mod);
    }
    return 0;       
}
```


---

## 作者：耶梦加得 (赞：1)

在两个操作中，$highbit$ 相对容易处理，因为它只会影响最高位，我们可以维护 $highbit$ 操作数量的前缀和，以便后面快速计算最高位移动了多少位。

（$lowbit$ 操作指操作 $1$，$highbit$ 操作指操作 $2$，下同）

这里我们记 $highbit(x)$ 为 $hb$。记 $highbit$ 操作数量的前缀和数组为 $s1$；$s0$ 类似定义。

观察数据范围。容易发现在最多 $\log x$ 次 $lowbit$ 操作之后，$x$ 可以表示为 $2^a + 2^b$ 或者 $2^a$。

这部分需要预处理字符串存下所有 $lowbit$ 操作的位置，询问时 $lower\_bound$ 找到位置直接模拟即可，直到最低位处在**原来的**最高位的位置。

当然，有可能 $lowbit$ 操作数量太少，达不到这种效果。~~那就直接无脑算~~，判断操作数量够不够的方法可以看代码。

总而言之，排除掉这种情况，假设我们现在在执行了 $pos$ 处的操作后，我们剩下 $2^a + 2^b$ 或者 $2^a$。

本质上两种情况是一样的，我们先看 $2^a + 2^b$ 的情况，令 $a < b$。

那么每一次 $lowbit$ 会让 $a$ “追上” $b$ 一位，反之则拉开一位的距离。

不难想到维护 $lowbit$ 操作与 $highbit$ 操作的**差**的前缀和 $sd$，找到第一个满足 $sd[j] - sd[pos] \geq b - a$ 的 $j$。

$sd[pos]$ 为定值，移项略。我们发现由于 $sd$ 是个 $+1-1$ 数组，只要找到第一个**等于** $sd[pos] + b - a$ 的 $sd[j]$ 即可。

~~还是 $lower\_bound$ 的套路~~。由于该值可能为负数，我们要先给它加上一个 $n$ ~~不然等着RE~~。

注意到 $2^a$ 的操作本质上是 $lowbit$ 赢在起跑线，由于 $hb$ 摆烂躺平，导致 $lowbit$ 直接追上了它，相当于 $b - a = 0$，是可以和 $2^a+2^b$一同处理的，故在代码里没有区分。

总之现在我们算出了 $lowbit$ 会在执行 $j$ 操作后追上 $highbit$ ，变成 $2^a$ 的情况。

~~那你还有啥不会的~~。

等等，万一追不上呢？

追不上就追不上，两个位**再**分别乘上 $2^{s0[r] - s0[pos]}, 2^{s1[r]-s1[pos]}$ ，~~完事~~。

```
#include<algorithm>
#include<cassert>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
#define miu 500007
using namespace std;
const int mod = 1000000007;
inline int add(register int x, register int y) {
    register int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int read() {
    register int x = 0; register char ch = getchar();
    while(ch < '0' || ch > '9')ch = getchar();
    while(ch >= '0' && ch <= '9'){x = x * 10 + ch - 48; ch = getchar();}
    return x;
}
char s[miu];
int n, q;
int stk[miu], top; //放lowbit操作位置，保证复杂度
int sd[miu], s1[miu]; //差分前缀和和highbit操作前缀和
int p2[miu];
vector<int> hs[miu << 1]; //记录每个sd出现的位置
signed main() {
    n = read(); q = read();
    p2[0] = 1;
    for(int i = 1; i <= n; ++i) {
        p2[i] = add(p2[i - 1], p2[i - 1]);
    } //预处理每一位在模意义下的值
    scanf("%s", s + 1);
    for(int i = 1; i <= n; ++i) {
        sd[i] = sd[i - 1] + ((s[i] == '0') ? 1 : -1); //可能会有负数，+n 处理掉
        s1[i] = s1[i - 1] + ((s[i] == '1') ? 1 : 0);
        if(s[i] == '0') {
            stk[++top] = i; hs[sd[i] + n].push_back(i); 
            //+1 -1 序列，我们只关心 +1 之后的数字
        }
    }
    for(int i = 0; i <= (n << 1); ++i) {
        hs[i].push_back(n + 1); 
    } //这样的插入顺序自动有序，省去排序
    for(int i = 1; i <= q; ++i) {
        int l = read(), r = read(), x = read();
        int hb = 1;
        for(; hb <= x; hb <<= 1); 
        if(!(x ^= (hb >>= 1))) {
            printf("%lld\n", 1ll * hb * p2[r - l + 1] % mod);
            continue;
        }
        int pos = lower_bound(stk + 1, stk + top + 1, l) - stk;
        for(; pos <= top; ++pos) {
            if(stk[pos] > r || x == hb) break; //lowbit操作完了或者只剩下两位了
            x += x & (-x);
        }
        pos = stk[--pos];
        if(x != hb) { //lowbit操作不够，easy情况
            printf("%lld\n", (long long)add(x, 1ll * hb * p2[s1[r] - s1[l - 1]] % mod));
            continue;
            //记得加上highbit
        }
        //已经转为 2 ^ a + 2 ^ b 的情况
        //此时lowbit 和一开始的 highbit 重合，故 b - a 等于 highbit 操作的次数
        int hp = s1[pos] - s1[l - 1]; //hb 已经移动了这么多位
        int qs = sd[pos] + hp + n;
        int joint = *lower_bound(hs[qs].begin(), hs[qs].end(), pos); //追上的位置
        if(joint <= r) printf("%lld\n", 1ll * hb * p2[++(hp += s1[joint] - s1[pos]) + r - joint] % mod); //追上了
        else printf("%lld\n", (long long)add(1ll * hb * p2[s1[r] - s1[l - 1]] % mod, 1ll * hb * p2[(r - pos) - (s1[r] - s1[pos])] % mod)); //追不上
    }
    return 0;
}


    

```




---

## 作者：AKPC (赞：0)

这题也太麻烦了，火大。

首先考虑一个子问题，就是如果询问给出 $x$ 二进制下 $1$ 的个数 $\leq2$ 怎么做。

对于 $1$ 的个数为 $1$，答案显然。

对于 $1$ 的个数为 $2$，将其表示为 $2^a+2^b$ 的形式，并限制 $a,b\in\text N,a<b$。不难发现每次 $\operatorname{lowbit}$ 操作都是给 $x$ 增加 $2^a$，即 $a$ 增加 $1$，每次 $\operatorname{highbit}$ 操作都是给 $x$ 增加 $2^b$，即 $b$ 增加 $1$。

考虑找到形如 $[l,t]$ 的子段使得 $a=b$，这可以通过给操作 $0,1$ 分别赋权 $1,-1$ 做前缀和开值域 `vector` 实现。在 $a=b$ 之前，操作是对 $a,b$ 加 $1$，记录两种操作数量即可，同样使用前缀和；而之后是同时加 $1$，直接计算操作总数。这是很好做的。

对于给出 $x$ 二进制下 $1$ 的个数 $>2$ 的情况，$\operatorname{lowbit}$ 操作会将最低的 $1$ 连续段删除并设置其更高一位为 $1$，不难发现这不会增加 $1$ 连续段个数；而 $\operatorname{highbit}$ 操作只能影响到最高位，对低位毫无影响。结合两者性质，经过 $\log x$ 级别的 $\operatorname{lowbit}$ 操作会将 $x$ 的二进制下 $1$ 的个数变成 $\leq2$。$\log x$ 级别次操作暴力做掉即可。

[code](https://www.luogu.com.cn/paste/suiklwys)，细节还挺多。

---

