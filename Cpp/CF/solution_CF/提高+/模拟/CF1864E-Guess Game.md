# Guess Game

## 题目描述

Carol has a sequence $ s $ of $ n $ non-negative integers. She wants to play the "Guess Game" with Alice and Bob.

To play the game, Carol will randomly select two integer indices $ i_a $ and $ i_b $ within the range $ [1, n] $ , and set $ a=s_{i_a} $ , $ b=s_{i_b} $ . Please note that $ i_a $ and $ i_b $ may coincide.

Carol will tell:

- the value of $ a $ to Alice;
- the value of $ b $ to Bob;
- the value of $ a \mid b $ to both Alice and Bob, where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

Please note that Carol will not tell any information about $ s $ to either Alice or Bob.

Then the guessing starts. The two players take turns making guesses, with Alice starting first. The goal of both players is to establish which of the following is true: $ a < b $ , $ a > b $ , or $ a = b $ .

In their turn, a player can do one of the following two things:

- say "I don't know", and pass the turn to the other player;
- say "I know", followed by the answer " $ a<b $ ", " $ a>b $ ", or " $ a=b $ "; then the game ends.

Alice and Bob hear what each other says, and can use this information to deduce the answer. Both Alice and Bob are smart enough and only say "I know" when they are completely sure.

You need to calculate the expected value of the number of turns taken by players in the game. Output the answer modulo $ 998\,244\,353 $ .

Formally, let $ M = 998\,244\,353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test case, there are only $ 4 $ possible situations:

1. $ i_a=1 $ , $ i_b=1 $ , $ a=2 $ , $ b=2 $ , the number of turns is $ 2 $ ;
2. $ i_a=1 $ , $ i_b=2 $ , $ a=2 $ , $ b=3 $ , the number of turns is $ 3 $ ;
3. $ i_a=2 $ , $ i_b=1 $ , $ a=3 $ , $ b=2 $ , the number of turns is $ 2 $ ;
4. $ i_a=2 $ , $ i_b=2 $ , $ a=3 $ , $ b=3 $ , the number of turns is $ 3 $ .

The expected number of turns is $ \frac{2+3+2+3}{4}=\frac{5}{2}=499122179\pmod{998244353} $ .

Consider the first case, when $ a=2 $ , $ b=2 $ . The guessing process is as follows.

In the first turn, Alice thinks, "I know that $ a=2, a\mid b=2 $ . I can infer that $ b=0 $ or $ b=2 $ , but I am not sure which one". Thus, she says, "I don't know".

In the second turn, Bob thinks, "I know that $ b=2, a\mid b=2 $ . I can infer that $ a=0 $ or $ a=2 $ . But if $ a=0 $ , then Alice would have already said that $ a<b $ in the first turn, but she hasn't. So $ a=2 $ ". Thus, he says, "I know, $ a=b $ ". The game ends.

In the second test case, for $ a=0 $ , $ b=0 $ , Alice knows that $ a=b $ immediately. The expected number of turns equals $ 1 $ .

## 样例 #1

### 输入

```
4
2
2 3
3
0 0 0
3
9 9 6
8
34124838 0 113193378 8 321939321 113193378 9463828 99```

### 输出

```
499122179
1
332748120
77987843```

# 题解

## 作者：EuphoricStar (赞：9)

感觉是很费脑子的题，可能是因为我没有脑子。

因为 $a, b$ 都没有的位可以通过更高的位往右平移填上，所以下面只考虑 $a \mid b = 2^k - 1$ 的情况。

考虑 $a = b$。例如 $a = b = (1111)_2$：

- A 不知道 $a = b$ 还是 $a > b$；
- B 知道了 $a$ 的最高位是 $1$，否则它就知道 $a < b$，但是 B 现在也不知道 $a = b$ 还是 $a < b$；
- A 知道了 $b$ 的最高位和第 $2$ 高位都是 $1$，但是 A 还是不知道 $a = b$ 还是 $a > b$；
- B 知道了 $a$ 的第 $2, 3$ 高位都是 $1$，但是 B 还是不知道 $a = b$ 还是 $a < b$；
- A 知道了 $b$ 的第 $3, 4$ 高位都是 $1$，因此 A 知道 $a = b$。

因此可以发现，若 $a = b$，则需要 $\operatorname{popcount}(a) + 1$ 轮。

若 $a \ne b$，例如 $a = (111010)_2, b = (111101)_2$：

- A 不知道 $a < b$ 还是 $a > b$；
- B 知道了 A 的最高位是 $1$，但是 B 还是不知道 $a < b$ 还是 $a > b$；
- A 知道了 B 的最高位和第 $2$ 高位都是 $1$，但是 A 还是不知道 $a < b$ 还是 $a > b$；
- B 知道了 A 的第 $2, 3$ 高位都是 $1$，但是 B 还是不知道 $a < b$ 还是 $a > b$；
- A 知道了 B 的第 $3, 4$ 高位都是 $1$，因此 A 知道 $a < b$。

因此可以发现，若 $a < b$，设 $a$ 最高是 $0$ 的位是第 $i$ 高位，会经过 $i + [i \bmod 2 = 0]$ 轮；同理，若 $a > b$，设 $b$ 最高是 $0$ 的位是第 $i$ 高位，会经过 $i + [i \bmod 2 = 1]$ 轮。

这样，我们枚举 $a$，枚举 $a, b$ 在二进制下的 $\text{LCP}$，就能知道会经过多少轮。

若使用 01Trie 计算 $b$ 的数量，时空复杂度均为 $O(n \log V)$。

[code](https://codeforces.com/contest/1864/submission/220576879)

---

## 作者：六楼溜刘 (赞：5)

## 题意

- 现在从长度为 $n$ 的序列 $s$ 中随机选两个数 $a,b$（可相同），两个人要进行猜数游戏。
- 具体规则如下：
	- $A$ 知道 $a$ 的值，$B$ 知道 $b$ 的值，两人都知道 $a|b$ 的值（其中 $|$ 表示按位或）。
   - $A,B$ 轮流猜数，他们的目标是猜出 $a,b$ 的大小关系，他们可以回答“不知道”和“我知道了”，当且仅当在确定 $a,b$ 的大小关系时才会回答“我知道了”，两人可以听到对方说的话。
- 问回答“我知道了”的期望轮数（**任意一人回答一次算一轮，包含回答“我知道了”的这一轮**）。
- $1\le n \le 2\times 10^5,0\le s_i < 2^{30}$，多组测试数据。

## 题解

这个问题看起来不知所云，但是如果认真按逻辑推理其实还挺合理的，~~有点像三个逻辑学家去酒吧的段子~~。

首先由于或运算是有 $1$ 得 $1$，那么显然我们可以忽略二进制下 $a,b$ 中均未 $0$ 的部分。那么不妨设 $a,b$ 中从最高位到最低位没有两边都为 $0$ 的位置，最后扩展一下结论即可。

令 $c=a|b$，那么假如 $a$ 的最高位小于 $c$ 的最高位，$A$ 很容易判断出 $b>a$，就会直接回答“我知道了”，所以 $A$ 第一次说“我不知道”其实向 $B$ 传达了“$a$ 的最高位和 $c$ 的最高位相同”的信息。

然后轮到 $B$，同理，假如 $B$ 说“我不知道”就是向 $A$ 传达了 $b$ 和 $c$ 最高位相同。同时，假如 $b$ 的次高位不为 $1$，那么 $B$ 就可以确定 $a$ 的次高位必定为 $1$（因为前面假设某一位不是 $a$ 为 $1$ 就是 $b$ 为 $1$ 要不然两个都是 $1$），也可以判断 $a>b$,所以这里还传达了一个“$b$ 的次高位为 $1$”的信息。

然后类似地，就这样每次传达两位，最终在某一位 $a,b$ 不同时即可确定。

那么分类讨论一下这是哪一位。这里暂时约定二进制下位数高到低编号。

1. $a=b$ 

最简单的情况，即 $a=b$，设 $a$ 有 $k$ 位，分奇偶讨论。

假如 $k$ 为**奇数**，那么在 $\frac{k-1}{2}\times2=k-1$ 轮后，$A$ 就只剩下最后一位无法确定，此时轮到 $A$，他会说“我不知道”，那么下一轮 $B$ 就会说“我知道了”，共计 $k+1$ 轮。

假如 $k$ 为**偶数**，在 $\frac{k}{2}\times2=k$ 轮后，$A$ 就能确定 $a=b$（注意在第 $k$ 轮 $B$ 并不能确定 $a$ 的最后一位是 $0$ 还是 $1$），下一轮轮到 $A$，他会说“我知道了”，共计 $k+1$ 轮。

综上，当 $a=b$，需要 $k+1$ 轮。

2. $a<b$

假如 $a<b$ ，那么 $a,b$ 的第一个不同的位必定是 $a$ 为 $0$ 且 $b$ 为 $1$，设这是第 $i$ 位，仍然分奇偶考虑。

假如 $i$ 为**奇数**，那么在第 $\frac{i-1}{2}\times2=i-1$ 轮后 $A$ 就能确定 $a,b$ 的前 $i-1$ 位相同，而第 $i$ 位 $a$ 为 $0$ 且 $b$ 为 $1$，那么会回答“我知道了”，共计 $i$ 轮。

假如 $i$ 为**偶数**，那么在第 $\frac{i}{2}\times2=i$ 轮后，$A$ 已经能确定前 $i-1$ 位相同，会在第 $i+1$ 轮回答“我知道了”，仍然注意在第 $i$ 轮 $B$ **无法确定** $a$ 的第 $i$ 位。

综上，当 $a<b$，需要 $i+i\bmod 2$ 轮。

3. $a>b$

仍设第 $i$ 位 $b$ 为 $0$ 且 $a$ 为 $1$，分奇偶讨论。

假如 $i$ 为**奇数**，在第 $i-1$ 轮后，$A$ 已经确定前 $i-1$ 位相同，但无法确定 $b$ 的第 $i$ 位，会回答“我不知道”，此时 $B$ 就能确定 $a$ 的第 $i$ 位为 $1$，会回答“我知道了”，共计 $i+1$ 轮。

假如 $i$ 为**偶数**，在第 $i$ 轮时，$B$ 就能确定第 $i$ 位了（原因类似于前文“一次传达两位”部分），共计 $i$ 轮。

综上，当 $a>b$ 时，需要 $i+1-i\bmod 2$ 轮。

然后扩展一下，把上述所有“第 $i$ 位”替换成 $c$ 中“第 $i$ 个 $1$”即可，感觉很显然，而且前面已经提过了。

那么现在已经有一个显而易见的 $O(n^2 \log V)$ 暴力了（其中 $V$ 为值域），考虑如何优化。

这里提供一个时空常数都极小的方法，跑出了 156ms 1568KB 的[好成绩](https://codeforces.com/contest/1864/submission/220690415)。

不同于题解中的 01Trie，我们考虑直接在序列上分治。

首先把期望拆成**总贡献**除以**方案数**，而方案数非常好求，我们只考虑总贡献。

从高往低分治，每次重新排序，把当前区间（区间是什么后文会解释）中这一位为 $0$ 的放在左侧，为 $1$ 的放在右侧（这部分可以~~基数排序~~计数排序，时间复杂度 $O(n)$，空间复杂度 $O(n)$），然后考虑左右侧配对，设这是第 $q$ 位，前面有 $p$ 个 $1$，那么每一对就会产生 $(p+p\bmod 2)+(p+1-p\bmod 2)=2p+1$ 的贡献，这样的配对数就是左侧数数量乘以右侧数的数量，然后对左右侧分治，容易发现每个分治到的区间内 $1\sim q$ 位均相同（这部分讲的有点抽象，看代码注释）。

然后当 $q<0$，说明整个区间内所有数全部相同，设区间大小为 $L$，那么贡献即为 $L^2\times (p+1)$。

由于分治 $\log V$ 层，每层是 $O(n)$ 的，故时间复杂度 $O(n\log V)$，空间复杂度 $O(n)$，常数极小。

另外注意取模。

## code

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=2e5+5,mod=998244353;
int t,n,a[N],b[N],ans;
int cntc[2];
void solve(int l,int r,int q,int cnt){
	if(l>r) return;
	if(q<0){
		(ans+=1ll*(r-l+1)*(r-l+1)%mod*(cnt+1)%mod)%=mod;
		return;
	}
	cntc[1]=cntc[0]=0;
	forup(i,l,r) cntc[(a[i]>>q)&1]++;//计数排序先统计个数
	cntc[1]+=cntc[0];//然后计算前缀和，因为只有两种就直接这样写了
	int lp=l+cntc[0];//顺便找到左右侧分界点（左闭右开）
	forup(i,l,r) b[l-1+cntc[(a[i]>>q)&1]--]=a[i];//往回填，注意不要覆盖原数组
	forup(i,l,r) a[i]=b[i];//刷新
	(ans+=1ll*(lp-l)*(r-lp+1)%mod*(cnt*2+3)%mod)%=mod;
	solve(l,lp-1,q-1,cnt);solve(lp,r,q-1,cnt+1);
//此时左边的第 q 位全为 0,右边的第 q 位全为 1，可以直接分治。
//注意这个重排的根本原理是答案与原序列中每个数具体怎么排列无关
}
int ksm(int a,int b){
	int c=1;
	while(b){
		if(b&1) c=1ll*c*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return c;
}
signed main(){
	t=read();
	while(t--){
		n=read();
		forup(i,1,n) a[i]=read();
		ans=0;//多测不清空，罚时两行泪
		solve(1,n,30,0);//初始区间为 [1,n]
		printf("%lld\n",1ll*ans*ksm(1ll*n*n%mod,mod-2)%mod);//最后输出时记得除以总方案数
	}
}


```

---

## 作者：Purslane (赞：4)

# Solution

简单博弈题。

首先考虑告诉你了 $a$ 和 $b$ 如果计算出答案。

我们分析一下每个人的心理状态：

- Alice 第一轮。她能发现两者的大小关系，当且仅当 $a|b$ 的最高位在 $a$ 中为 $0$，这说明 $b$ 的最高位比 $a$ 要高，那么她可以判断出 $b>a$，否则无法做出任何判断。 

- Bob 第一轮。Alice 这一轮能传给他，说明 $b$ 的最高位不会高于 $a$。那么他会检查 $a|b$ 的最高位在 $b$ 中对应是否为 $1$。如果是 $0$ 那么可以判断 $b<a$，否则说明 $a$ 和 $b$ 的最高位相同。那么 Alice 和 Bob 都知道了这件事，可以化归为检查 $a|b$ 的第二位 $1$。注意，这时候 Bob 并不会把任务交给 Alice 处理。相反，他会利用这一机会，充当刚刚 Alice 的角色，首先判断这个第二位在 $b$ 中的对应。

这样不停的下去，如果 $a=b$ 那么很容易知道会进行 $\text{popcount}(a)+1$ 轮后的到答案，这个是平凡的，可以单独处理。

否则，大小关系会在 $a$ 和 $b$ 第一次不等的位置被判出来。我们发现，第一轮判断的是第 $1$ 位，第二轮判断的是第 $1$ 和第 $2$ 位，第三轮判断的是第 $2$ 和第 $3$ 位。那么假设出现不同的之前两者有 $k$ 个共同的 $1$，那么应当是第 $k$ 轮开始判断这一位。

但是，我们思考这样的情况：这一位 Alice 得到的数是 $1$，Bob 是 $0$。如果 Alice 首先判断这一位，她并不能在第 $k$ 轮得出结论，需要 Bob 在第 $k+1$ 轮做出判断；然而如果是 Bob 首先判断这一位，那么他就恰好能在第 $k$ 轮做出判断。这是个麻烦的事情。

但是注意到，在总体贡献中，$a$ 和 $b$ 时可以交换的。也就是说，无论如何，这里的 $k$ 和 $k+1$ 都会各出现一次：整体可以当做出现一次 $2k+1$。就解决了这个问题。

因此我们只需要批量统计任意两个数二进制下第一个不同的位置即可。这个可以用 Trie 树轻松解决。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MOD=998244353;
int T,n,s[MAXN],ans;
int tot,tr[MAXN*31][2],sze[MAXN*31];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;	
	}
	return ans;
}
void insert(int v) {
	int u=0;
	roff(i,30,0) {
		int ch=((v&(1ll<<i))>0);
		if(tr[u][ch]==0) tr[u][ch]=++tot;
		u=tr[u][ch];
		sze[u]++;
	}
	return ;
}
void dfs(int u,int dep,int cnt) {
	if(dep==-1) {
		ans+=sze[u]*sze[u]%MOD*(cnt+1)%MOD,ans%=MOD;
		return ;	
	}
	if(tr[u][0]&&tr[u][1]) ans+=sze[tr[u][0]]*sze[tr[u][1]]%MOD*(cnt+1+cnt+2)%MOD,ans%=MOD;	
	if(tr[u][0]) dfs(tr[u][0],dep-1,cnt);
	if(tr[u][1]) dfs(tr[u][1],dep-1,cnt+1);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n,ans=0;
		ffor(i,1,n) cin>>s[i];
		ffor(i,0,tot) tr[i][0]=tr[i][1]=0,sze[i]=0; tot=0;
		ffor(i,1,n) insert(s[i]);
		dfs(0,30,0);
		cout<<ans*qpow(n*n%MOD,MOD-2)%MOD<<'\n';
	}
	return 0;
}
```

---

## 作者：__little__Cabbage__ (赞：3)

## Solution

~~不建议学博弈论，因为过于容易上瘾了。~~

但是博弈论真的很好玩很好玩很好玩很好玩很好玩很好玩很好玩很好玩很好玩很好玩。

先手搓几个样例，具体过程就不放了，其它题解都有。

因为要比大小，所以博弈的过程是从高位到低位的，所以根据这个思路，可以发现两个数 $(a,b)$ 所需的操作次数与它们二进制分解后的 LCP 有关，于是我们手动模拟一下每一轮中 A 知道的 $b$ 中的前缀字符数和 B 知道的 $a$ 中的前缀字符，然后就可以得到结论：

- 对于 $(a,b)$，设 $p(a,b) = {\rm popc}({\rm LCP}(a,b))$，${\rm len}(a,b)$ 为 ${\rm LCP}(a,b)$ 的长度，则其操作次数为 $p(a,b) + 1 + [p(a,b) \bmod 2 = b_{{\rm len}(a,b)+1}]$。
- 总数为 $\sum \limits _{a \in s} \sum \limits _{b \in s} ( p(a,b) + 1 + [p(a,b) \bmod 2 = b_{{\rm len}(a,b)+1}] )$。

但是直接统计是 $O(n^2)$ 的，所以考虑优化。而这种位运算题一般可以考虑用 01trie 做，所以考虑如何在 01trie 上统计答案。可以把上面那个式子拆成 $3$ 部分：

- $p(a,b)$：可以在 01trie 的每个节点上计算每个字符的贡献，即 $siz_u ^2$。
- $1$：直接拿出来，化为 $n^2$。
- $[p(a,b) \bmod 2 = b_{{\rm len}(a,b)+1}]$：我们观察到，对于节点 $u$，其左右子节点分别为 $lc,rc$，计算分别以 $lc,rc$ 结尾（LCP 的结尾）的数字，我们发现 $p(a,b) \bmod 2$ 是固定的，而 $lc,rc$ 分别作为 $b$ 时，$b_{{\rm len}(a,b)+1}$ 不同，于是正好可以产生 $siz_{lc} \times siz_{rc}$ 的贡献。

注：$siz_u$ 为在 01trie 中 $u$ 的子树大小。

记得最后除以 $n^2$。

## Code

```cpp
const int MAXN=2e5+5,Vlg=30;
const int mod=998244353;
int n,a[MAXN];

class __01trie
{
private:
    struct node{int ch[2],siz,cnt;} v[MAXN*Vlg];
    int tot=1;

    il void update(int x,int k)
    {
        int pos=1; bool now;
        rpe(i,Vlg-1,0)
        {
            now=(x&(1ll<<i));
            if(!v[pos].ch[now]) v[pos].ch[now]=++tot;
            pos=v[pos].ch[now];
            v[pos].siz+=k;
        }
        v[pos].cnt+=k;
    }

    il int get_rank(int x) // count numbers which < x
    {
        int pos=1,ans=0; bool now;
        rpe(i,Vlg-1,0)
        {
            now=(x&(1ll<<i));
            if(now) ans+=v[v[pos].ch[0]].siz;
            pos=v[pos].ch[now];
            if(!pos) break;
        }
        return ans;
    }

    il int get_kth(int x)
    {
        int pos=1,ans=0;
        rpe(i,Vlg-1,0)
        {
            if(x>v[v[pos].ch[0]].siz) x-=v[v[pos].ch[0]].siz,pos=v[pos].ch[1],ans|=(1ll<<i);
            else pos=v[pos].ch[0];
            if(!pos) break;
        }
        return ans;
    }

public:
    il void clear() {rep(i,0,tot+1) v[i]=(node){{0,0},0,0}; tot=1;};
    il void upd(int x,int k) {update(x,k);}
    il int grk(int x) {return get_rank(x)+1;}
    il int gth(int x) {return get_kth(x);}
    il int pre(int x) {return get_kth(get_rank(x));}
    il int nxt(int x) {return get_kth(get_rank(x+1)+1);}

    il int calc(int u,bool op)
    {
        int ans=0;
        op && (ans+=v[u].siz*v[u].siz%mod);
        ans+=v[v[u].ch[0]].siz*v[v[u].ch[1]].siz%mod;
        v[u].ch[0] && (ans+=calc(v[u].ch[0],0));
        v[u].ch[1] && (ans+=calc(v[u].ch[1],1));
        return ans%mod;
    }
} tr;

template <typename T> il void exgcd(T a,T b,T &x,T &y) {if(!(a%b)) x=0,y=1; else exgcd(b,a%b,y,x),y-=a/b*x;}
template <typename T> il T ginv(T a) {T x,k; exgcd(a,mod,x,k); return (x%mod+mod)%mod;}

il void solve(int __Ti)
{
    tr.clear();
    read(n); _::r(a,n);

    rep(i,1,n) tr.upd(a[i],1);

    int ans=n*n%mod+tr.calc(1,0);
    ans=ans*ginv(n*n)%mod;
    write(ans,'\n');
}
```

---

## 作者：hanjinghao (赞：3)

# 思路

如果 $ a $ 的位数小于 $ b $ 的位数（当然是二进制），那么一轮就会结束。如果 $ a $ 的位数大于 $ b $ 的位数，那么两轮就会结束。

其余情况，$ a $ 和 $ b $ 的位数相同，那么我们从高位到低位考虑。可以发现，每轮游戏能够确定一个二进制位。如果 $ a = b $，那么游戏会进行 $ \operatorname{popcount}(a) + 1 $ 轮——两个数都为 $ 0 $ 的二进制位，或运算之后还是 $ 0 $，这是一开始就能确定的。

对于 $ a \neq b $ 的情况，我们令 $ x $ 表示 $ a $ 和 $ b $ 从高位到低位，第一个不相等的二进制位。确定了这一位的大小关系，即可确定 $ a $ 和 $ b $ 的大小关系，后面的二进制位就不用管了。

令 $ y $ 表示从最高位到第 $ x $ 位，两个数均为 $ 1 $ 的二进制位的个数。如果 $ a \gt b $，那么游戏会进行 $ y + 1 $ 轮。如果 $ a \lt b $，那么游戏会进行 $ y + 2 $ 轮。

得出结论之后，用字典树即可求出答案。

# 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

template < typename T >
inline const void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline const void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline const void writesp(const T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline const void writeln(const T x)
{
	write(x);
	putchar(10);
}

const int N = 2e5 + 5, P = 998244353;
int T, n, a[N], tot, tr[N << 5][2], cnt[N << 5], ans;

inline void Add(int &x, int y)
{
	x += y;
	if (x >= P) x -= P;
}

inline int power(int x, int y)
{
	int ret = 1;
	while (y)
	{
		if (y & 1) ret = (ll)ret * x % P;
		x = (ll)x * x % P;
		y >>= 1;
	}
	return ret;
}

void dfs(int p, int dep, int num)
{
	if (dep)
	{
		if (tr[p][0] && tr[p][1] && cnt[tr[p][0]] && cnt[tr[p][1]]) Add(ans, (ll)cnt[tr[p][0]] * (ll)cnt[tr[p][1]] % P * (num * 2ll + 3ll) % P);
		if (tr[p][0]) dfs(tr[p][0], dep - 1, num);
		if (tr[p][1]) dfs(tr[p][1], dep - 1, num + 1);
	}
	else Add(ans, (ll)cnt[p] * (ll)cnt[p] % P * (num + 1ll) % P);
}

int main()
{
	read(T);
	while (T--)
	{
		read(n);
		for (int i = 1; i <= n; ++i)
		{
			read(a[i]);
			int p = 0;
			for (int j = 30; ~j; --j)
			{
				int tmp = (a[i] >> j) & 1;
				if (!tr[p][tmp]) tr[p][tmp] = ++tot;
				p = tr[p][tmp];
				++cnt[p];
			}
		}
		ans = 0;
		dfs(0, 31, 0);
		int Inv = power(n, P - 2);
		ans = (ll)ans * (ll)Inv % P * (ll)Inv % P;
		writeln(ans);
		for (int i = 0; i <= tot; ++i)
			tr[i][0] = tr[i][1] = cnt[i] = 0;
		tot = 0;
	}
	return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：2)

## 前言

为什么所有人都用 `Trie` 树，没有更短一点的做法吗？？？参考某 `Trie` 树被卡 `MLE` 的同学赛时思路和代码。

## 代码

```cpp
ll t,n,a[200005];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	ll ans=0;
	for(int i=30;i>=0;i--){
		map<ll,ll>mp;
		for(int j=1;j<=n;j++)mp[(a[j]>>i)]++;
		for(int j=1;j<=n;j++){
			if((a[j]>>i)&1)ans=(ans+mp[(a[j]>>i)]+mp[(a[j]>>i)-1])%mod;
		}
	}
	cout<<(fastpow(n*n,mod-2)*ans+1)%mod<<endl;
}
```

## 思路

推结论部分都是相似的。

如果给你一个 $a$ 和一个 $b$，求多少轮后游戏结束。我们先手玩几组数据，然后容易得到结论与 $a|b$ 二进制表示中 $1$ 的位置有关。

如果 $a|b$ 的二进制表示中第一个是 $1$ 的位在 $a$ 的二进制表示中为 $0$，则一轮即可判断 $a<b$，否则会说“我不知道”。同理，如果 $a|b$ 的二进制表示中第一或第二个是 $1$ 的位在 $b$ 的二进制表示中为 $0$，则两轮即可判断 $a>b$，否则会说“我不知道”。如果 $a|b$ 的二进制表示中第二或第三个是 $1$ 的位在 $a$ 的二进制表示中为 $0$，则三轮即可判断 $a<b$，否则会说“我不知道”。以此类推。

然后总结一下推出结论：

设 $a$ 和 $b$ 的前 $k$ 个 $1$ 的位置都相同。

若 $a=b$，则轮数为 $k+1$。

若 $a<b$，则轮数为 $k+1+[k\equiv1\pmod2]$。

若 $a>b$，则轮数为 $k+1+[k\equiv0\pmod2]$。

如果结论推得不清楚请参考其他题解。

我们得到结论后直接暴力是 $O(n^2\log{V})$ 的，显然过不去。我们考虑怎么优化。二进制表示把很多人引到了 `01Trie` 的路上，但其实没必要。

我们考虑说“我不知道”的期望轮数，最后把结果加一就行了。

我们从小到大考虑用三十二位二进制表示的前 $i$ 位，这前 $i$ 位所组成的前缀。用 `map` 统计 $S$ 中每个存在的前缀的个数。然后我们枚举 $S$ 中每个数，计算这个数在考虑到前 $i$ 位时新的贡献（即拥有这个数的人在考虑第 $i$ 位的这一轮说“我不知道”的情况个数）。容易发现，如果一个前缀和另一个前缀在 $i-1$ 位及以前就有不同，那么一定不会有贡献，因为这一局早就结束了；如果这个前缀的最后一位是 $0$，那么不会产生贡献，因为要么他会说“我知道”，要么第 $i$ 位本来都是 $0$，不需要考虑。因此，会产生贡献的，就是这个前缀最后一位是 $1$ 的数；能和它产生贡献的数，前 $i-1$ 位都和它一样。于是分第 $i$ 位是 $0$ 还是 $1$ 求和即可。

虽然复杂度多了 `log`，但是时限三秒，跑了两秒左右，够了。

---

## 作者：masonpop (赞：1)

推出了结论但是没写下去，有点可惜。

考虑两个数 $a,b$ 确定时如何统计需要的场数。设 $t=a\operatorname{or}b$。考虑 $t$ 的每一位，显然若该位是 $0$，则只能推出 $a,b$ 的这一位都是 $0$，对判断大小关系没有任何影响。因此，我们可以忽略 $t$ 中的 $0$，**将 $t$ 视为全是 $1$，同时忽略 $a,b$ 中对应的这些位置。**

接着模拟一下这个博弈的过程。先将 $a,b$ 按位对齐，不足的地方补 $0$。若 $a$ 的最高位是 $0$，那么它马上可以得知 $b$ 的这一位是 $1$，从而判断出自己更小。否则，$b$ 就会知道 $a$ 的这一位是 $1$，如果自己的这一位或者下一位是 $0$ 的话它也能判断出来。否则，$a$ 就知道了 $b$ 的这两位是 $1$，可以继续判断。

举个例子。假设 $a=110,b=111$。首先，$a$ 会说自己不知道。然后，$b$ 由于自己的前两位都是 $1$，因此也会说自己不知道。然后，$a$ 知道了 $b$ 的前两位是 $1$，看看自己第二位，也是 $1$。再看看自己第三位是 $0$，判断出自己更小，游戏结束，用时三轮。

我们可以根据 $a,b$ 的大小关系分类讨论。稍加模拟可得：

① $a=b$ 时，设 $a,b$ 各有 $k$ 位，则答案是 $k+1$。

② $a<b$ 时，设 $a$ 的第一个 $0$ 是第 $k$ 位，则答案是 $k+1-[k\equiv 1\pmod 2]$。

③ $a>b$ 时，设 $b$ 的第一个 $0$ 是第 $k$ 位，则答案是 $k+[k\equiv 1\pmod 2]$。

但凡这种二进制位相关的计数问题都可以往 01-trie 这方面想想。具体的，我们先把所有数全部插入 01-trie，并且对于每一个节点，统计出它子树内有多少个位置是某一个数的结尾，记为 $w_i$。到达一个位置时统计这一段前缀的答案即可，具体细节见代码。时间复杂度 $O(n\log V)$。[代码](https://codeforces.com/contest/1864/submission/220628976)。

---

## 作者：鱼跃于渊 (赞：0)

感觉很神仙。  

## 解法

首先考虑如何求出单次游戏的轮数。  
设 $z\gets x \operatorname{or} y$，分类讨论：  
1. 若 $z$ 当前位为 $0$，先后手都不可能通过这一位得到 $x,y$ 的大小关系，所以先手会跳过这一位，轮数不增加。  
   所以下面的讨论均忽略为 $0$ 的位。  
2. 若 $z$ 当前位为 $1$：
    + 轮到先手，若 $x$ 的当前位为 $0$，显然 $y$ 的当前位为 $1$。  
    先手会知道 $x<y$，轮数加 $1$，游戏结束，否则会说不知道。  
    + 轮到后手，轮数加 $1$。  
    若 $y$ 的当前位为 $0$，显然 $x$ 的最高位为 $1$。  
    后手会知道 $x>y$，轮数加 $1$，游戏结束。  
    否则后手会看下一位，先后手交换。

这样重复下去，游戏的轮数会是 $x,y$ 的最高不同位之前同为 $1$ 的数量，加上一个常数（由这一不同位是 $x=1,y=0$ 还是 $x=0,y=1$ 来决定）。  
若 $x=y$，则轮数为 $x$ 中为 $1$ 的数量加 $1$。  

我们考虑把所有的数丢进 trie 树里，再 dfs 一遍，于分岔口计算答案。  
时空复杂度均为 $O(n\log n)$。  

由于题目问的是期望，输出时再将答案乘上 $n^2$ 的逆元即可。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
const int N=2e5+5,M=N<<5,mod=998244353;
int T,n,ans,a[N];
int tot,t[M][2],siz[M],fin[M];
void insert(int x){
	int p=0,c;
	rep(i,30,0){
		c=((x>>i)&1);
		if(!t[p][c]) t[p][c]=++tot;
		p=t[p][c];siz[p]++;
	}
	fin[p]=1;
}
void dfs(int p,int num){
	if(fin[p]){
		ans=(ans+siz[p]*siz[p]%mod*(num+1))%mod;
		return;
	}
	ans=(ans+siz[t[p][0]]*siz[t[p][1]]%mod*(2*(num+1)+1))%mod;
	if(t[p][0]) dfs(t[p][0],num);
	if(t[p][1]) dfs(t[p][1],num+1);
}
int qpow(int a,int b){
    int res=1;
    for(;b;b>>=1,a=(a*a)%mod)
        if(b&1) res=(res*a)%mod;
    return res;
}
void solve(){
    per(i,0,tot) t[i][0]=t[i][1]=siz[i]=fin[i]=0; 
    tot=ans=0;
    cin>>n;
	per(i,1,n){
		cin>>a[i];
		insert(a[i]);
	}
	dfs(0,0);
	cout<<(ans*qpow(n*n%mod,mod-2))%mod<<'\n';
}
void main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    cin>>T;
    while(T--) solve();
}}
signed main(){
	fisher::main();
	return 0;
}
```

---

## 作者：lml0928 (赞：0)

### Part 0. 题目大意

给定一个数列 $a$，长度为 $n$。甲、乙和丙在这个数列上玩一个游戏。

丙从序列中随机选两个可能相同的位置 $i,j$。

甲会被告诉 $a_i$ 和 $a_i \operatorname{or} a_j$，乙会被告诉 $a_j$ 和 $a_i \operatorname{or} a_j$。

甲和乙每次可以说：

- $a < b$；
- $a = b$；
- $a > b$；
- 不确定。

现在请求出比出两个数大小的期望轮数对 $998244353$ 取模。

### Part 1. 题目解法

我们可以分别计算每一位对期望的贡献，然后再除以 $n \times n$ 即可。

现在只考虑其中一位的情况：

- $a_i$ 和 $a_j$ 这一位都是 $1$：

	甲会发现：我的这一位是 $1$，而且我们两个的数 $\operatorname{or}$ 起来的值也是 $1$，但是我不能判断乙这一位是 $1$ 还是 $0$，所以我只能说“我不知道”，然后让乙考虑下一位。
- $a_i$ 和 $a_j$ 这一位都是 $0$：

	甲会发现：我的这一位是 $0$，而且我们两个的数 $\operatorname{or}$ 起来的值也是 $0$，所以乙这一位也是 $0$，我这一轮可以直接考虑下一位。

- $a_i$ 和 $a_j$ 这一位不同。
	
    如果 $a_i$ 这一位是 $0$，那么甲会发现：我的这一位是 $0$，而且我们两个的数 $\operatorname{or}$ 起来的值也是 $1$，所以他一定大，可以直接说出结果。
    
    如果 $a_i$ 这一位是 $1$，那么甲会发现：甲会发现：我的这一位是 $1$，而且我们两个的数 $\operatorname{or}$ 起来的值也是 $1$，但是我不能判断乙这一位是 $1$ 还是 $0$，所以我只能说“我不知道”，然后让乙考虑下一位。
    但是这里，乙发现两人的数 $\operatorname{or}$ 起来的值是 $1$，而自己的数为 $0$，所以甲一定大于自己。

然后把这些数扔到 01trie 里面，做一遍 DFS 即可。

### Part 2. 代码
~~附上代码供众人批判~~
```c++
#include<bits/stdc++.h>
using namespace std;
map<int, int> mp;
int res = 0;
const int N = (int)2e5 * 32;
int num[N];
int nxt[N][2];
const int P = 998244353;
int cnt = 1;
void Insert(int x)
{
	int now = 1;
	for(int i = 30; i >= 0; i--)
	{
		int son = (x >> i) & 1;
		if(nxt[now][son] == 0) nxt[now][son] = (++cnt);
		now = nxt[now][son];
		num[now]++;
	}
}
void Dfs(int x, int dep)
{
	int num0 = num[nxt[x][0]];
	int num1 = num[nxt[x][1]];
	res = ((1ll * num0 * num1 + res) % P);
	res = ((2ll * num1 * num0 + res) % P);
	if(num0 > 0 && dep >= 0) Dfs(nxt[x][0], dep - 1);
	if(num1 > 0 && dep >= 0)
	{
		res = ((1ll * num1 * num1 + res) % P);
		Dfs(nxt[x][1], dep - 1);
	}
}
int Pow(int a, int b)
{
	int res = 1;
	while(b > 0)
	{
		if(b & 1) res = (1ll * res * a % P);
		a = (1ll * a * a % P);
		b >>= 1;
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++)
		{
			int x;
			cin >> x;
			mp[x]++;
			Insert(x);
		}
		Dfs(1, 30);
		for(auto i : mp) res = (1ll * i.second * i.second + res) % P;
		cout << (1ll * res * Pow((1ll * n * n % P), P - 2) % P) << '\n';
		res = 0;
		for(int i = 1; i <= cnt; i++)
		{
			nxt[i][0] = nxt[i][1] = num[i] = 0;
		}
		mp.clear();
		cnt = 1;
	}
	return 0;
}
```

### Part 3. 后记
~~多测不清空，亲人两行泪~~

---

