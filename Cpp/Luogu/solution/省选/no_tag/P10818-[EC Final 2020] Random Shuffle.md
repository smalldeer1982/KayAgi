# [EC Final 2020] Random Shuffle

## 题目描述

庞教授正在选择晋级世界总决赛的队伍。由于地区赛被取消，他使用随机打乱来对队伍进行排名。总共有 $n$ 支队伍。他的代码如下：  

```cpp
uint64_t x;//uint64_t 表示 64 位无符号整数
int n;
uint64_t rand() {//这是一个异或移位随机生成器
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
int main() {
    cin >> n;
    cin >> x;
    for (int i = 1; i <= n; i++) {//随机打乱 [1, 2,..., n]
         a[i] = i;
         swap(a[i], a[rand() % i + 1]);
     }
     for (int i = 1; i <= n; i++) {//打印结果
       cout << a[i] << (i == n ? '\n' : ' ');
    }
}
```

他编译并运行了他的代码，然后输入了 $n$ 和某个特殊的非负整数 $x$。他将结果打印在纸上。  一天后，庞教授忘记了他选择的 $x$。给定代码的结果和整数 $n$。请恢复庞教授输入的数字 $x$。

## 说明/提示

注意样例输入的第二行被换行以适应页面宽度。（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
50
36 22 24 21 27 50 28 14 25 34 18 43 47
13 30 7 10 48 20 16 29 9 8 15 3 31 12
38 19 49 37 1 46 32 4 44 11 35 6 33 26
5 45 17 39 40 2 23 42 41```

### 输出

```
16659580358178468547```

# 题解

## 作者：Purslane (赞：7)

# Solution

Reunite 推荐的题目。

发现这个随机运算没有任何规律可言，考虑直接解出一些东西。

我们相当于知道了这个变量操作若干次之后模一个数的值。设模数是 $x = 2^a b$，其中 $b$ 是奇数，我们可以得到当前变量二进制下后 $a$ 位的值。

显然当前变量的每一位是 $x$ 某些位组合而成的，可以得到很多线性方程组。

$n \ge 50$ 的时候，解的组数不算太多，可以直接枚举。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100000+10;
int n,res[MAXN],val[MAXN],a[MAXN],rev[MAXN],le=64;
bitset<70> bt[70],eq[70];
uint64_t rand(uint64_t &x) {//this is a xor-shift random generator
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
void insert(bitset<70> f,int v) {
	roff(i,63,0) if(f[i]) {
		if(eq[i][i]) f^=eq[i],v^=val[i];
		else return le--,eq[i]=f,val[i]=v,void();
	}
	return ;
}
void lm(int d) {
	ffor(i,0,63-d) bt[i]=bt[i]^bt[i+d];
	return ;	
}
void rm(int d) {
	roff(i,63,d) bt[i]=bt[i]^bt[i-d];
	return ;	
}
void dfs(int u,uint64_t x) {
	if(u==64) {
		uint64_t ox=x;
		ffor(i,1,n) if(rand(x)%i!=res[i]) return ;	
		cout<<ox;
		exit(0);
	}
	if(eq[u][u]) {
		int op=val[u];
		ffor(j,0,u-1) if(eq[u][j]&&(x&(1ll<<j))) op^=1;
		if(op) x+=(1ll<<u);
		dfs(u+1,x);
	}
	else dfs(u+1,x+(1ll<<u)),dfs(u+1,x);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i],rev[a[i]]=i;
	ffor(i,0,63) bt[i][i]=1;
	roff(i,n,1) res[i]=rev[i]-1,rev[a[i]]=rev[i],swap(a[i],a[rev[i]]);
	ffor(i,1,n) { 
		rm(13),lm(7),rm(17);
		ffor(j,0,30) if((i&(1<<j))==0) {
			insert(bt[j],!!(res[i]&(1<<j)));
			if(le==0) break ;
		}
		else break ;
	}
	dfs(0,0);
	return 0;
}
```

---

## 作者：a1a2a3a4a5 (赞：4)

# 题意：
求 $x$，使得以 $x$ 为参数的随机排序可以把排列 $1,2,3,4,…,n$ 排成 $a$ 序列，具体信息看题面的代码。
# 思路
省选模拟赛这题放在了 T2，可以推断出不是诈骗题，所以我们不得不从代码中推出一些性质：  
### 一
```cpp
for (int i = 1; i <= n; i++)
{
    a[i] = i;
    swap(a[i], a[rand() % i + 1]);
}
```
发现这是前缀交换，所以最后一个数只会被交换一次。设 $n$ 在 $a_p$，那么 $\operatorname{rand}\bmod n+1=p$，然后再 `swap(a[p],a[n])`，那么相当于抛去了 $n$ 的影响，现在 $n-1$ 是最后一个数……  
我们推出了：  
$\operatorname{rand}\bmod n+1=p$  
$\operatorname{rand}\bmod(n-1)+1=p'$  
$\operatorname{rand}\bmod(n-2)+1=p''$  
……  
### 二
```cpp
uint64_t rand()
{
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
```
我们的 $x$ 与 $\operatorname{rand}$ 有关，我们考虑用 $x$ 表示 $\operatorname{rand}$。  
由于 $x'=\operatorname{rand}(n)$ 所以下面我都用 $x'$ 来表示 $\operatorname{rand}(n)$。

手玩一下左右移异或的性质，为了方便，我们手玩下面这份代码：
```cpp
uint64_t rand()
{
    x ^= x << 1;
    x ^= x >> 2;
    return x;
}
```
假设 $x_{(2)}=101$ （二进制表示）。  
$x$ 左移 $1$ 位为 $1010$  
$1010$ 右移 $2$ 位为 $10$  
结果为 $(101\operatorname{xor} 1010)\operatorname{xor} 10=1101$，每一位的来源我们可以记录下来，此例：  
$101=x_1x_2x_3$  
$1010=x_1x_2x_30$  
$10=x_1x_2$  
$1101=(x_1)(x_1\operatorname{xor}x_2)(x_2\operatorname{xor}x_3\operatorname{xor}x_1)(x_3\operatorname{xor}x_2)$  
所以关于 $x$ 的方程组大概是这样的：  
$x'=(x_1)(x_1\operatorname{xor}x_2)(x_2\operatorname{xor}x_3\operatorname{xor}x_1)(x_3\operatorname{xor}x_2)$

综上，我们可以把 $x'$ 的每一位用 $x$ 来表示，然后 $x''$ 也用 $x'$ 的 $x$ 表示来表示……最终所有式子都化成了初始的 $x$，这样我们就处理了 $x$ 变化带来的影响并把所有 $\operatorname{rand}$ 值都用 $x$ 表示出来了（$\operatorname{rand}$ 就是上文的 $x'、x''$）。
### 三
移项整理上面两个性质，这里写的 $x^2$ 的意思是 $x''$，而并非次方：  
$x^n\equiv p-1 \pmod n$  
$x^{n-1}\equiv p'-1 \pmod{(n-1)}$  
$x^{n-2}\equiv p''-1 \pmod{(n-2)}$   
……  
我们显然是想解方程似得把 $x$ 解出来，我们性质二的 $x'$ 是依赖二进制位的，所以我们不得不把上面这个式子在二进制上考虑。$x$ 拆成二进制，猜出模数拆成二进制数肯定不劣，我们考虑二进制如何取模？  
先分类思考一下，如果模数为 $2^x$，那么取模相当于保留了后 $x$ 位。在上面式子相当于可以直接求出 $x'$ 后几个二进制位，然后我们可以得到只有 $x_i$ 未知的帅方程。帅方程可以用线性基解，所以我们可以找出 $2^x$ 模数找出他们的帅方程。

但是这样做感觉方程好少啊！

此时**宇宙射线**横着走过来说：“ 不是，我不是二的整次幂，我直接把多的位数不要了不得了？  然后我再跟你说：  
对于 $p=2^xq$，$(n\bmod p)\equiv n\pmod{2^x}$。  
证明：  
$n=kp+(n\bmod p)=kq2^x+(n\bmod p)$，则 $ (n\bmod p)\equiv n\pmod{2^x}$。”

真是说的道理，我们模 $p$ 的式子再模一个 $2^x$ 肯定还成立，我们直接取后 $x$ 位并对右边的常数模 $2^x$ 再拿来写方程就好了。  
关于为什么取 $lowbit$，因为你除以这玩意就是奇数了，所以这玩意就是 $2^x$。
# 终末之章
显然我们后来推的都是必要条件，因为充要条件没法推，难道真的无法做到吗？可是！你别忘了！我们 OI 从来都是把必要当充分用的啊！！！

我们现在相当于有 $x$ 的一些位数没有解出来，祈祷其少——指数级枚举，到最后还是选择了暴力吗？对不起 T2 大人，我没让你用尽全力……

跑得...  
飞快[吗](https://www.luogu.com.cn/record/228031759)？

---

## 作者：Reunite (赞：2)

我觉得很难啊为什么全都会。/ll

设初始时 $x$ 二进制上第 $i$ 位为 $x_i=\{0,1\}$，那显然任意时刻运算完之后，$x$ 第 $i$ 为可以确定地被表示为 $x_i'=\bigoplus_{j\in S_i} x_j$。使用 $\text{bitset}$ 即可以 $O(\frac{n\log^2 V}{\omega})$ 的复杂度预处理前 $n$ 次操作的每一位与原数每一位的线性异或关系。

显然可以倒着模拟来求出每一次真正的 $x\bmod i$，现在我们希望通过每一次操作后 $x$ 的二进制表示和 $x\bmod i=h_i$ 来解出原来的 $x$。

注意到二进制表示和取模运算并不好兼容，我们能找到的信息只有，取模完前后，被除数和余数在二进制上第 $[0,lowbit(x))$ 位是相同的，因为显然无法被除。那我们只需要，把这些位上的 $x_i'$ 与 $h_i$ 在这些位上的 $01$ 取值联立，即可得到异或线性方程组。

看起来会得到 $\sum _{i=1}^nlowbit(i)$ 个方程，但是因为未知量只有 $64$ 个，因此只需要保留任意 $64$ 个方程即可。因为我们这样表示的信息不全，所以会有自由元无法被解出，但是可以发现，在 $n=50$ 的下界，矩阵最不满秩且限制最松，实际实现后发现最多不会超过 $19$ 个自由元，直接暴力枚举自由元的值再回带验算即可。因为随机的特性，可以认为对不合法的情况判定是 $O(1)$ 的。

复杂度即为 $O(2^{F(n)}\log^2 V)$，其中 $F(n)$ 是关于 $n$ 的减函数，在 $n\ge 50$ 时其上界为 $19$ 左右，有题解说上界不到 $19$，可能是我实现的问题。


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <iostream>
#define ll unsigned long long
using namespace std;

int T,n,m;
int a[100005];
int g[100005];
int h[100005];
bitset <65> f[65],F[65];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline bool check(ll x){
	for(int i=1;i<=n;i++){
		x^=x<<13;x^=x>>7;x^=x<<17;
		if(x%i!=h[i]) return 0;
	}
	return 1;
}

inline ll solve(){
	int mp[65]={0},h[65]={0},mm=0;
	for(int i=0;i<m;i++){
		if(!F[i][i]) for(int j=i+1;j<m;j++) if(F[j][i]){swap(F[i],F[j]);break;}
		if(!F[i][i]) continue;
		mp[i]=1;
		for(int j=0;j<m;j++) if(i!=j&&F[j][i]) F[j]^=F[i];
	}
	for(int i=0;i<m;i++) f[i]=F[i];
	for(int i=0;i<64;i++) if(!mp[i]) h[++mm]=i;
	for(int s=0;s<(1<<mm);s++){
		ll SS=0;
		for(int i=1;i<=mm;i++) if(s>>(i-1)&1) SS|=1llu<<h[i];
		for(int i=m-1;i>=0;i--)
			if(F[i][i]){
				int x=F[i][64];
				for(int j=i+1;j<64;j++)
					if(F[i][j]&&(SS>>j&1)) x^=1;
				if(x) SS|=1llu<<i;
			}
		if(check(SS)) return SS;
	}

	return 0;
}

int main(){
	// freopen("qwq.in","r",stdin);
	// freopen("qwq.out","w",stdout);
	//in(T);
	T=1;
	while(T--){
		in(n);
		for(int i=1;i<=n;i++) in(a[i]),g[a[i]]=i;
		for(int i=n;i>=1;i--){
			h[i]=g[i];
			swap(g[i],g[a[i]]);
			swap(a[i],a[h[i]]);
			h[i]--;
		}
		m=0;
		for(int i=0;i<64;i++) f[i].reset(),F[i].reset();
		for(int i=0;i<64;i++) f[i][i]=1;
		for(int i=1;i<=n;i++){
			bitset <65> g[65];
			for(int i=0;i<64;i++) g[i]=f[i];
			for(int j=13;j<64;j++) f[j]^=g[j-13];
			for(int j=0;j<64;j++) g[j]=f[j];
			for(int j=7;j<64;j++) f[j-7]^=g[j];
			for(int j=0;j<64;j++) g[j]=f[j];
			for(int j=17;j<64;j++) f[j]^=g[j-17];
			for(int j=0;(1<<(j+1))<=(i&-i)&&m<64;j++) F[m++]=f[j],F[m-1][64]=(h[i]>>j)&1;
		}
		printf("%llu\n",solve());
	}

	return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

给定 $n$ 和随机数种子 $x$，下述代码可以生成一个长度为 $n$ 的随机排列。

```cpp
auto generate(int n, uint64_t x){
    auto next = [&x](){
        x ^= x << 13, x ^= x >> 7, x ^= x << 17;
        return x;
    };
    vector<int> ret(n + 1);
    iota(ret.begin(), ret.end(), 0);
    for(int i=1;i<=n;i++) swap(ret[i], ret[next() % i + 1]);
    return ret;
}
```

现在给定 $n$ 和一个排列 $p$，求任意一个可以生成它的随机数种子。

$50\leq n\leq 10^5$。保证存在种子 $x\in[0,2^{64})$。

## 思路

这道题有点强。

首先我们考虑还原每次随机生成的数，这是容易的，倒序枚举 $i$，则 $p_i$ 和 $p_j=i$ 间必有交换。于是可以求得 $f(x)=\mathrm{next}()\bmod x$ 为每次随机数对次序取模后的值。

由于随机数生成是基于 xor-shift 算法的，所以我们可以逐位考虑，然后立即可得每一位都是由初始种子 $x$ 的若干位异或得到（这个同样是可以简单维护的），因此对于每一位，就可以看成一个异或方程，自然想到高斯消元法解异或方程组，所以现在我们的核心任务是将做法往异或方程上套。

观察到这个取模非常难搞，不过如果 $i$ 为 $2$ 的自然数次幂的话，$f(i)$ 是有意义的，它就是 $\mathrm{next}()$ 的后若干位，可以贡献等量的方程。

不过这点方程仍然不够，我们需要更多的方程。

真的只有模数为 $2$ 的整数次幂的模数才有用吗？答案是否定的。假如模数为 $6=(110)_2$，我们能得到什么信息？

观察到如果存在 $2^0$ 进制位，那么与 $6$ 的余数也存在 $2^0$，反之亦然。这是容易证明的。

将结论一般化，我们需要证明的是这样一个结论：

> 对于 $p=2^xq$，则 $(n\bmod p) \equiv n\pmod{2^x}$。

证明：取 $n$ 同余分解 $n=kp+r=kq2^x+r$。则 $n-r\equiv{0}\pmod{2^x}$，故原命题得证。

所以对于 $f(x)$，只需要将 $x$ 分解为 $2^ab$，就可以得到 $a$ 个方程，分别对应 $f(x)$ 的位 $[1,a]$。

于是我们可以得到的方程大为增加，不过我们只需要保留 $64$ 个，因为 $x$ 最多 $64$ 位，不足的话用空方程补齐。

然后解这个方程，大概率无法得到解，会有若干个自由元无法确定。经过实践，大约最多 $17$ 个，而 $2^{17}$ 是一个枚举可以接受的范围，所以暴力枚举自由元，将其他元推算出来，检验是否合法即可。

## 代码

考试上写的，有点混乱，建议别学。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ui64 = unsigned long long;

const int N = 1e5 + 5;
int n, a[N], pos[N], rnd[N];
bitset<64> bs[65], eq[65];
ui64 ret[65];
bool vis[65], answer[N];
int in_free[65];

ui64 next_rnd(ui64 &x){
    x ^= (x << 13);
    x ^= (x >> 7);
    x ^= (x << 17);
    return x;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i], pos[a[i]] = i;
    for(int i=n;i;i--){
        rnd[i] = pos[i];
        swap(a[i], a[rnd[i]]);
        pos[a[rnd[i]]] = rnd[i];
        rnd[i]--;
    }
    int tot = 0;
    for(int i=0;i<64;i++) bs[i][i] = 1;
    for(int i=1;i<=n;i++){
        // x ^= (x << 13);
        for(int j=63;j>=13;j--) bs[j] ^= bs[j - 13];
        // x ^= (x >> 7);
        for(int j=0;j<64-7;j++) bs[j] ^= bs[j + 7];
        // x ^= (x << 17);
        for(int j=63;j>=17;j--) bs[j] ^= bs[j - 17];
        for(int j=1;j<64;j++){
            if(i % (1ull << j)) continue;
            eq[++tot] = bs[j - 1], ret[tot] = (rnd[i] >> (j - 1)) & 1;
            if(tot == 64) break;
        }
        if(tot == 64) break;
    }
    vector<int> free;
    for(int i=0;i<64;i++){
        int pos = -1;
        for(int j=1;j<=64;j++){
            if(eq[j][i] && !vis[j]){
                pos = j, vis[pos] = 1;
                break;
            }
        }
        if(!(~pos)){
            free.push_back(i);
            continue;
        }
        for(int j=1;j<=64;j++){
            if(j == pos || !eq[j][i]) continue;
            eq[j] ^= eq[pos], ret[j] ^= ret[pos];
        }
    }
    int t = free.size();
    // cerr << t << '\n';
    tot = 0; ui64 S = 0;
    for(int i : free) in_free[i] = tot++, S |= (1ull << i);
    for(int i=0;i<(1<<t);i++){
        ui64 x = 0;
        for(int k=0;k<64;k++){
            if(S & (1ull << k)) x ^= (ui64)((i >> in_free[k]) & 1) << k;
        }
        for(int j=1;j<=64;j++){
            int pos = -1;
            bool tmp = 0;
            for(int k=0;k<64;k++){
                if(S & (1ull << k)) tmp ^= ((i >> in_free[k]) & 1) & eq[j][k];
                else if(eq[j][k]) pos = k;
            }
            tmp ^= ret[j];
            if(!(~pos)) continue;
            if(tmp) x |= (1ull << pos);
        }
        ui64 bak = x;
        bool flag = 0;
        for(int j=1;j<=n;j++){
            if((next_rnd(x) % j) != rnd[j]){
                flag = 1;
                break;
            }
        }
        if(!flag){
            cout << bak << '\n';
            return;
        }
    }
    // cout << "no solution\n";
}

void clear(){
    for(int i=0;i<=64;i++){
        bs[i].reset(), eq[i].reset();
        ret[i] = vis[i] = answer[i] = in_free[i] = 0;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t = 1;
    while(t--) solve(), clear();
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：XZhuRen (赞：1)

规定：下文把 $rand()$ 写作 $Rand(x)$，且意义为对 $x$ 进行一次代码中的操作。

首先我们可以通过倒推得到每一个随机值 $K_{i}\equiv Rand()\pmod i$。

然后发现对于不同的 $i$，$Rand()$ 每一位的取值来源于原始 $x$ 不同的位的异或和。

考虑每一个初始位 $i$ （从 $1$ 开始）对一个 $Rand()$ 值的贡献，这个东西直接递推求出，记为 $base_{i}$，初始为 $2^{(i-1)}$，递推一次即是 $Rand(base_{i}) \to base_{i}$。

现在求出了所有的 $base$，考虑异或意义下的高斯消元，这个是关于二进制位的，所以我们考虑每个 $i$ 中有用的部分，即 $lowbit(i)$，把 $K_{i}\bmod lowbit(i)\to K_{i}$，这样对于 $2^{(j-1)}< lowbit(i)$ 的每一位 $j$ 都可以列出方程，总共有 $\log_{2}{lowbit(i)}$ 个方程，经打表可得最终方程在 $n=66$ 时就取满了（共需要 $64$ 个）。

题目中 $n\ge 50$，所以直接搜索就行（自由元数量为 $17$）。

时间复杂度 $\mathcal{O}(2^{c}n+V^{3})$，$n>66$ 时时间复杂度 $\mathcal{O}(V^{3}+n)$，其中 $c$ 为自由元个数，$c\le 17$，$V=64$。

注意高斯消元的最后要求值，所以最好用约旦消元法，把整个矩阵消成对角矩阵，第 $i$ 行就代表第 $i$ 主元的取值，这样方便 $dfs(frees)$ 的操作和 $getnum()$ 求值，直接对位乘求和就好。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int SK=120;
typedef uint64_t ll1;
#define int ll1
ll1 Rand(ll1 x){x^=x<<13;x^=x>>7;x^=x<<17;return x;}
const ll1 _1=1;
ll1 base[SK];
void getbase(){//原始这一位对哪些位有贡献
	for(int i=1;i<=64;i++)base[i]=Rand(base[i]);
}
int n;
int a[N],b[N];
void init(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=0;i<64;i++)base[i+1]=_1<<i;
}
bool check(ll1 tx){
	ll1 x=tx;
	for(int i=1;i<=n;i++){
		b[i]=i;
		swap(b[i],b[Rand(x)%i+1]);
		x=Rand(x);
	}
	bool flag=1;
	for(int i=1;i<=n;i++)
		if(a[i]!=b[i])flag=0;
	return flag;
}
int ans=0;
int c[SK][SK];
int tot=0;
int totfree;//自由元数量
int frees[SK];
bool got[SK];//已经找到主元的行
namespace jordan{//高消
	void Swap(int x,int y){
		for(int i=1;i<=65;i++)swap(c[x][i],c[y][i]);
	}
	void fkof(int x,int y,int o){
		if(x==y)return;
		if(!c[y][o])return;
		for(int i=1;i<=65;i++)c[y][i]^=c[x][i];
	}
	ll1 getnum(){
		ll1 res=0;
		for(int i=1;i<=64;i++){
			res|=c[i][65]<<(i-1);
		}
		return res;
	}
	bool dfs(int now){
		if(now>totfree){
			if(check(getnum())){
				ans=getnum();
				return 1;
			}
			return 0;
		}
		int pos=frees[now];
		if(dfs(now+1))return 1;
		c[pos][65]=1;
		for(int i=1;i<=64;i++){
			if(i==pos)continue;
			if(c[i][pos])c[i][65]^=1;
		}
		if(dfs(now+1))return 1;
		c[pos][65]=0;
		for(int i=1;i<=64;i++){
			if(i==pos)continue;
			if(c[i][pos])c[i][65]^=1;
		}
		return 0;
	}
	void calc(){
		totfree=0;tot=max(tot,(ll1)64);//每个主元
		for(int i=1;i<=64;i++)got[i]=0;
		for(int now=1;now<=64;now++){
			for(int i=1;i<=tot;i++){//找到一行合理的
				if(got[i])continue;//已经找到主元的行，用不了
				if(c[i][now]){Swap(i,now);break;}
			}
			if(!c[now][now]){
				frees[++totfree]=now;got[now]=0;
				continue;//这个是自由元
			}
			got[now]=1;
			for(int i=1;i<=tot;i++){
				fkof(now,i,now);
			}
		}
		dfs(1);
	}
}
int bot[N];
int K[N];//余数
void work(){
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)bot[a[i]]=i;
	for(int i=n;i;i--){
		K[i]=bot[i];
		swap(a[bot[i]],a[i]);
		bot[a[bot[i]]]=K[i];
		bot[i]=i;K[i]--;
	}
	for(int i=1;i<=n;i++)swap(a[i],a[K[i]+1]);
	ans=1;
	tot=0;
	for(int now=1;now<=n;now++){
		getbase();
		if((now&1)||tot>=64)continue;//是可以取的位置
		int mod=((now)&(-now));
		K[now]%=mod;
		for(int o=1,bt=0;o<mod&&tot<64;o<<=1,bt++){
			++tot;
			for(int i=1;i<=64;i++)
			c[tot][i]=(base[i]>>bt)&1;//对这一位的贡献
			c[tot][65]=(K[now]>>bt)&1;
		}
	}
	jordan::calc();
	cout<<ans<<'\n';
}
signed main() {
	init();
	work();
}
```

---

## 作者：_Ch1F4N_ (赞：0)

模拟赛场切了，开心。

容易还原出每一轮生成的随机数模 $i$ 后的值，不妨记为 $to_i \bmod i$。

考虑怎么通过 $to_i \bmod i$ 还原出最开始的 $x$。

由于是通过二进制操作生成的 $to_i$，所以 $to_i$ 在二进制下每一位一定都是 $x$ 二进制下一些位异或的结果，先处理出来，然后考虑怎么通过 $to_i \bmod i$ 获取 $to_i$ 的二进制位的值。

首先 $to_i \bmod 2^k$ 就是 $to_i$ 二进制下第 $[0,k)$ 位的值，但是只知道这些信息远远不够。

注意到 $to_i \bmod (2^k \times l) \bmod 2^k = to_i \bmod 2^k$，结合这一部分的信息后，当 $n = 50$ 时对得到的所有方程做高斯消元后，你发现存在 $17$ 个位置没有确定，于是暴力枚举这 $17$ 个位置的值，check 就是把跑出来的 $x$ 对前 $50$ 个位置做一下，如果这部分合法则很大概率则为合法解。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
bitset<64> bit[maxn][64];
bitset<64> now;
vector< bitset<64> > vec;
int cnt[maxn];
bitset<64> v[64],ans[64];
#define ull unsigned long long
ull w[64];
ull jump(ull x){
    x^=x<<13;
    x^=x>>7;
    x^=x<<17;
    return x;
}
int ChiFAN[17]={63,62,61,60,59,58,57,56,55,54,53,52,51,50,48,47,45};
//0 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
void init(){
    int n=50;
    for(int i=0;i<64;i++) bit[0][i][i]=1;
    for(int i=0;i<17;i++){
        bitset<64> b;
        b[ChiFAN[i]]=1;
        vec.push_back(b);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<64;j++){
            bit[i][j]=bit[i-1][j];
        }
        for(int j=63;j>=13;j--) bit[i][j]^=bit[i][j-13];
        for(int j=0;j+7<64;j++) bit[i][j]^=bit[i][j+7];
        for(int j=63;j>=17;j--) bit[i][j]^=bit[i][j-17];
        int lowbit=(i&(-i));
        for(int j=0,p=0;(1<<j)<lowbit;j++,p++){
            vec.push_back(bit[i][p]);
            now|=bit[i][p];
            cnt[i]++;
            if(vec.size()==64&&now.count()==64) break;
        }
        if(vec.size()==64&&now.count()==64) break;
    }
    for(int i=0;i<64;i++) v[i][i]=1;
    for(int i=0;i<64;i++){
        for(int j=i;j<64;j++){
            if(vec[j][i]==1){
                swap(vec[j],vec[i]);
                swap(v[j],v[i]);
                break;
            }
        }
        for(int j=i+1;j<64;j++){
            if(vec[j][i]==1){
                vec[j]^=vec[i];
                v[j]^=v[i];
            }
        }
    }
    for(int i=63;i>=0;i--){
        ans[i]=v[i];
        for(int j=i+1;j<64;j++){
            if(vec[i][j]==1){
                ans[i]^=ans[j];
            }
        }
    }
    for(int i=0;i<64;i++){
        for(int j=0;j<64;j++){
            if(ans[i][j]==1) w[i]+=((ull)(1)<<j);
        }
    }
    return ;
}
int a[maxn],p[maxn],to[maxn];
const int warma = 50;
void work(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],p[a[i]]=i;
    for(int i=n;i>=1;i--){
        to[i]=p[i];
        swap(a[i],a[to[i]]);
        swap(p[a[i]],p[a[to[i]]]);
    }
    for(int i=1;i<=n;i++) to[i]--;
    ull S=0;
    int chifan=0;
    for(int i=1;i<=50;i++){
        for(int j=0;j<cnt[i];j++){
            if(((ull)(1)<<j)&to[i]){
                S+=((ull)(1)<<chifan);
            }
            chifan++;
        }
    }
    for(ull v=0;v<(1<<17);v++){
        ull T=v+(S<<17);
        //__builtin_popcountll()
        ull x=0;
        for(int i=0;i<64;i++){
            if(__builtin_popcountll(T&w[i])%2==1) x+=((ull)(1)<<i);
        }
        ull y=x;
        int i=1;
        for(i=1;i<warma;i++){
            y=jump(y);
            if(y%i!=to[i]) break;
        }
        if(i==warma){
            cout<<x<<'\n';
            return ;
        }
    }
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    init();
    int T;
    T=1;
    while(T--) work();
    return 0;   
}
/*
1
50
47 14 37 36 43 2 34 26 48 6 45 11 27 22 9 42 4 13 33 46 18 25 12 19 32 49 8 40 15 7 1 29 44 24 20 17 30 50 16 35 39 21 28 41 10 23 3 5 38 31
18446744073709551615
*/
```

---

## 作者：minstdfx (赞：0)

首先还原对 $i$ 取模的序列 $c_i=r_i\bmod i$。约定 $B(x, k)=\lfloor\frac x {2^k}\rfloor\bmod 2$。  
显而易见的，$r_i$ 的第 $k$ 位显然是初始 $x$ 某些位的线性组合。  
由于 $a\mid b\iff(c\bmod b)\bmod a=c\bmod a$，对于 $2^k\mid i$，$\forall m=0,1,2,\cdots,k-1$ 这些二进制位上满足 $B(c_i,m)=B(r_i,m)$。  
然后我们就可以得到一系列的线性异或方程组。我们只取前 64 个，不足补齐。  
具体的，系数矩阵通过每次维护 $A_{i,j}$ 表示当前第 $i$ 位是否异或了最开始的第 $j$ 位，则当前处理到的位 $k(2^{k+1}\mid i)$ 对应的方程的系数矩阵的一行就是 $A_i$，对应的增广矩阵最后一列的元素为 $B(c_i,k)$。$A_{i,j}$ 的维护是平凡的，这里不再赘述。  
先高斯消元。最后对于所有自由变量（不妨设个数为 $f$）暴搜判断即可。
对于复杂度，注意到 $n$ 越大，方程越多，且系数矩阵只与 $n$ 有关（事实上，就连系数矩阵每一行都是确定的）。当 $n=50$ 时，自由变量最多，为 17 个，复杂度可以接受。

---

## 作者：songhongyi (赞：0)

首先可以很容易的通过模拟得出每次生成的随机数模 $i$ 的结果。

不难发现，如果当 $2^{k+1} \mid i$ 的时候，$k$ 这个二进制位的值就是生成的数的二进制位。

我们考虑设 $f_{i,j}$ 表示当前 $i$ 这一位上初始 $j$ 这一位的系数，显然可以通过 bitset 实现。

然后我们就得到了一系列的异或线性方程组，直接高消即可。自由元枚举一下即可。

```cpp
using ull = unsigned long long int;
const int MAXN = 1e5 + 10;
int n;
int a[ MAXN ], p[ MAXN ];
int t[ MAXN ];
bitset< 64 > bs[ 64 ], tmp[ 64 ];
bool check( ull x )
{
    bool f = 1;
    for ( int i = 1; i <= n; i++ )
    {
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        // cerr << x % i << ' ' << t[ i ] << endl;
        if ( t[ i ] != x % i )
        {
            f = 0;
            return f;
        }
    }
    return f;
}
void solve( vector< pair< bitset< 64 >, bool > > v )
{
    v.resize( 64 );
    vector< int > fr;
    for ( int i = 0; i < 64; i++ )
    {
        if ( !v[ i ].first[ i ] )
        {
            for ( int j = i; j < 64; j++ )
            {
                if ( v[ j ].first[ i ] )
                {
                    swap( v[ i ], v[ j ] );
                    break;
                }
            }
        }
        if ( !v[ i ].first[ i ] )
        {
            fr.emplace_back( i );
        }
        else
        {
            for ( int j = 0; j < 64; j++ )
            {
                if ( i != j and v[ j ].first[ i ] )
                {
                    v[ j ].first ^= v[ i ].first;
                    v[ j ].second ^= v[ i ].second;
                }
            }
        }
    }
    int m = fr.size();
    for ( int i = 0; i < ( 1 << m ); i++ )
    {
        ull S = 0;
        for ( int j = 0; j < m; j++ )
        {
            if ( i & ( 1 << j ) )
            {
                S |= ( 1ull << fr[ j ] );
            }
        }
        for ( int j = 0; j < 64; j++ )
        {
            if ( v[ j ].first[ j ] )
            {
                bool t = v[ j ].second;
                for ( int k = j + 1; k < 64; k++ )
                {
                    if ( v[ j ].first[ k ] and ( ( 1ull << k ) & S ) )
                    {
                        t ^= 1;
                    }
                }
                if ( t )
                {
                    S |= 1ull << j;
                }
            }
        }
        if ( check( S ) )
        {
            cout << S << endl;
            return;
        }
    }
}
int main()
{
    io >> n;
    for ( int i = 1; i <= n; i++ )
    {
        io >> a[ i ];
        p[ a[ i ] ] = i;
    }
    for ( int i = n; i >= 1; i-- )
    {
        t[ i ] = p[ i ];
        swap( a[ t[ i ] ], a[ i ] );
        p[ a[ t[ i ] ] ] = t[ i ];
        p[ a[ i ] ] = i;
        t[ i ]--;
    }
    vector< pair< bitset< 64 >, bool > > v;
    for ( int i = 0; i < 64; i++ )
    {
        bs[ i ][ i ] = 1;
    }
    for ( int i = 1; i <= n; i++ )
    {
        for ( int j = 0; j < 64; j++ )
        {
            tmp[ j ] = bs[ j ];
        }
        for ( int j = 13; j < 64; j++ )
        {
            bs[ j ] ^= tmp[ j - 13 ];
        }
        for ( int j = 0; j < 64; j++ )
        {
            tmp[ j ] = bs[ j ];
        }
        for ( int j = 7; j < 64; j++ )
        {
            bs[ j - 7 ] ^= tmp[ j ];
        }
        for ( int j = 0; j < 64; j++ )
        {
            tmp[ j ] = bs[ j ];
        }
        for ( int j = 17; j < 64; j++ )
        {
            bs[ j ] ^= tmp[ j - 17 ];
        }
        for ( int j = 0; i % ( 1 << ( j + 1 ) ) == 0; j++ )
        {
            v.emplace_back( bs[ j ], ( ( 1 << j ) & t[ i ] ) );
        }
        if ( v.size() >= 64 )
        {
            break;
        }
    }
    solve( v );
}
```

---

