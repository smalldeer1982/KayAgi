# [AGC037B] RGB Balls

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc037/tasks/agc037_b

色のついたボールが $ 3N $ 個あり、それぞれには $ 1 $ から $ 3N $ の番号がついています。 各ボールの色は長さ $ 3N $ の文字列 $ S $ によって表されており、ボール $ i $ の色は $ S_i $ が `R` のとき赤色、`G` のとき緑色、`B` のとき青色です。 赤色のボール、緑色のボール、青色のボールはそれぞれ $ N $ 個ずつあります。

高橋君はこの $ 3N $ 個のボールを、各人が赤、青、緑のボールを $ 1 $ つずつ割り当てられるよう、$ N $ 人の人に分配することにしました。 ただし、ボールをもらう人たちはできるだけ近い番号のボールが欲しいので、高橋君はさらに以下の条件をみたすように分配することにしました。

- $ j $ 番目の人が受け取ったボールの番号を小さい順に $ a_j\ <\ b_j\ <\ c_j $ とする。
- このとき $ \sum_j\ (c_j-a_j) $ ができるだけ小さくなるように分配する。

高橋君がボールを分配する方法は何通りあるか求めてください。 答えは非常に大きくなることがあるので、$ 998244353 $ で割ったあまりを求めてください。 ただし、$ 2 $ つのボールの分配方法が異なるとは、ある人が存在して、その人が受け取ったボールの集合が異なることを指します。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ |S|=3N $
- $ S $ は `R`, `G`, `B` のみからなり、それぞれ $ N $ 回ずつ $ S $ に登場する

### Sample Explanation 1

例えば以下のようにボールを分配したとき、$ \sum_j\ (c_j-a_j) $ の値が $ 18 $ となり最小となります。 - $ 1 $ 番目の人にボール $ 1,5,9 $ を渡す。 - $ 2 $ 番目の人にボール $ 2,4,8 $ を渡す。 - $ 3 $ 番目の人にボール $ 3,6,7 $ を渡す。

## 样例 #1

### 输入

```
3
RRRGGGBBB```

### 输出

```
216```

## 样例 #2

### 输入

```
5
BBRGRRGRGGRBBGB```

### 输出

```
960```

# 题解

## 作者：MattiaBinotto (赞：4)

## 思路

显然我们将每种颜色从左到右第 $i$ 个给第 $i$ 个人就可以做到最优解。

不难发现，最优解当且仅当此时作为第三个数的数仍然是第三个数，此时作为第一个数的数仍然是第一个数。

考虑匹配过程。我们从大往小匹配，每个数在做的事情其实类似于和后面的数**配对**。

对于后面的数，最好的情况显然是让它成为最小数，其次是中间数，最后是最大数。

所以我们枚举现在已经匹配好的 $R,G,B,RG,GB,RB$ 数量，如果每次能匹配上就一定匹配。

注意到 $R$ 可以同时匹配 $G,B$，但是如果 $G,B$ 都存在它们已经被匹配了，因此一定不会出现这种情况。

## 代码

```cpp
// Problem: B - RGB Balls
// Contest: AtCoder - AtCoder Grand Contest 037
// URL: https://atcoder.jp/contests/agc037/tasks/agc037_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//And in that light,I find deliverance.
#include<bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
char s[1000003];
signed main()
{
	int R=0,G=0,B=0,RG=0,GB=0,RB=0,ans=1;
	int n=read();
	scanf("%s",s+1);
	for(int i=1; i<=n*3; ++i) 
		if(s[i]=='R')
		{
			if(GB) ans=ans*GB%p,--GB;
			else if(G) ans=ans*G%p,++RG,--G;
			else if(B) ans=ans*B%p,++RB,--B; 	
			else ++R;
		}
		else if(s[i]=='G')
		{
			if(RB) ans=ans*RB%p,--RB;
			else if(R) ans=ans*R%p,++RG,--R;
			else if(B) ans=ans*B%p,++GB,--B; 	
			else ++G;
		}
		else
		{
			if(RG) ans=ans*RG%p,--RG;
			else if(R) ans=ans*R%p,++RB,--R;
			else if(G) ans=ans*G%p,++GB,--G; 	
			else ++B;
		}
	for(int i=1; i<=n; ++i) ans=ans*i%p;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：MiRaciss (赞：3)

嘛，其实直接来就好了。

考虑什么时候答案最小，那么一定是对于每一组来说第一个字符的下标最大，最后一个字符的下标最小。不难发现如果每一组都满足这个条件，那么最后的总答案一定是最小的。

既然如此，顺序遍历每一个字符，每个字符都要尽量成为最后的，避免成为最前的。什么时候它可以成为最后的呢？那就是他前面出现了两个字符且这两个字符还没有和其它字符配对。

推广一下这道题就出来了，顺序遍历每一个字符，并记录当前未配对的 
 `R` , `G` , `B` ,`RG` , `RB` , `RG` 的数量。对于一个 `R` 来说，他一定先选择 `BG` 配对这样它就能成为最后一个字符了，如果没有 `BG` 那么再通过与 `B` 或 `G` 配对让它成为第二个字符，不然它就只能成为第一个字符了。其它的字符同理。
 
 对了对了你这样配对后是没有顺序的，但是但是原题的 $n$ 个人是不同的，所以所以答案要乘个阶乘。
 
 ```cpp
 
 #include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=998244353;

ll ans=0;
char s[300005];
ll dp[300005];
int n;
int R=0,G=0,B=0,RG=0,BG=0,RB=0;

int main(){
	cin>>n;
	cin>>(s+1);
	ll ans=1;
	for(int i=1;i<=n*3;i++){
		if(s[i]=='R'){
			if(BG) ans*=BG,BG--,ans%=Mod;
			else if(B) ans*=B,ans%=Mod,RB++,B--;
			else if(G) ans*=G,ans%=Mod,RG++,G--; 
			else R++;
		}
		else if(s[i]=='B'){
			if(RG) ans*=RG,ans%=Mod,RG--;
			else if(R) ans*=R,ans%=Mod,RB++,R--;
			else if(G) ans*=G,ans%=Mod,BG++,G--;
			else B++;
		}
		else if(s[i]=='G'){
			if(RB) ans*=RB,ans%=Mod,RB--;
			else if(R) ans*=R,ans%=Mod,RG++,R--;
			else if(B) ans*=B,ans%=Mod,BG++,B--;
			else G++;
		}
	}
	for(int i=1;i<=n;i++) ans*=i,ans%=Mod;
	cout<<ans<<endl;
	return 0;
}
 
 ```

---

## 作者：chroneZ (赞：2)

显然可以先由贪心策略构造一组最小解，即将每种颜色从左到右第 $i$ 个球分给第 $i$ 个人。

寻找贪心解与通解的关联，可以发现通解满足**在贪心解中作为第一个球的仍然作为第一个球，作为第三个球的仍然作为第三个球**（充分性显然，必要性大概能用调整法证明）。

给出一种比较另类的实现方式。

对作为首位的球，中位的球，末位的球进行分类讨论，如果一个位置上的球是作为首位的球，则增加**当前可作为首位球的数量**；如果是作为中位的球，则对答案产生 **(当前可作为首位球的数量 - 之前同种颜色球的出现次数)** 的贡献；如果是末位球，则先对答案产生**另外两种颜色的出现次数中的较小值**的贡献（$\text{i.e.}$ 可以在增加该球后成为完整的一组 $\mathtt{RGB}$ 的数量），再减少**当前可作为首位球的数量**，并将**三种颜色的球的出现次数**均减一。

由于不同的人之间还需要区分，所以答案要乘以 $n!$。

```cpp
#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int mod = 998244353, N = 2e5 + 10, inf = 1e9;

int c[3][N], l[3]; int rec[512];
int pre[N * 3], suf[N * 3], t[3];
char s[N * 3];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	rec['R'] = 0, rec['G'] = 1, rec['B'] = 2;

	int n; cin >> n; cin >> s + 1;
	for(int i = 1; i <= n * 3; i++) {
		c[rec[s[i]]][++l[rec[s[i]]]] = i;
	}
	for(int i = 1; i <= n; i++) {
		pre[min({c[0][i], c[1][i], c[2][i]})] = 1;
		suf[max({c[0][i], c[1][i], c[2][i]})] = 1;
	}
	i64 ans = 1, valid = 0;
	for(int i = 1; i <= n * 3; i++) {
		t[rec[s[i]]]++;
		if(pre[i]) {
			valid++;
			continue;
		} else if(suf[i]) {
			int cur = inf;
			for(int j = 0; j < 3; j++) {
				if(j == rec[s[i]]) continue;
				cur = min(cur, t[j]);
			}
			t[0]--, t[1]--, t[2]--; valid--;
			ans = ans * cur % mod;
		} else {
			ans = ans * (valid - t[rec[s[i]]] + 1) % mod;
		}
	}
	for(int i = 2; i <= n; i++) {
		ans = ans * i % mod;
	}
	cout << ans << "\n";
}
```

---

## 作者：ln001 (赞：0)

~~致管理大大，latex 里没有单词，first 和 second 是变量名。~~

## 形式化题意
给定长度为 $3 \times n$ 的序列 $a_i$，值域为 $[1,3]$，每一种值的出现个数为 $n$，你需要计算满足如下条件的序列 $b_i$ 的个数。

- 序列长度为 $3 \times n$ 且值域为 $[1, n]$，每一种值的出现个数为 $3$。
- 对于任意 $i \in [1, n]$，令 $first, second, third$ 满足 ${first}<{second}<{third}, b_{first} = b_{second} = b_{third} = i$，有 $a_{first},a_{second},a_{third}$ 互不相等。
- 延续上面关于 $first, second, third$ 的定义，令 $f(b) = \sum_{i = 1}^n (third - first)$。不存在另一种序列 $b^{\prime}$，满足 $f(b^{\prime}) < f(b)$。
## 以[非形式化题意](https://vjudge.net/problem/AtCoder-agc037_b#author=GPT_zh)为基础的做法解析
首先可以想到构造方案的贪心方式，从左往右逐个去扫每个小球，判断能否作为某个人的最后一个球，如果可以则分配，否则判断能否作为倒数第二个球，能否作为第一个球。

可以证明，**不存在其他分配策略**能达到同样小的代价，因此只需要对这种策略计数。又可以发现，对于每个球而言，目前**拥有球的个数相同的人**是等价的，分配给谁都一样，方案数只会在这种情况下增加。

又因为每个人本质不同，所以答案需要乘上人的全排列的个数。

---

## 作者：yshpdyt (赞：0)

## 题意
给出一个只包含 $R,G,B$ 的字符串，保证它们三种字符出现的次数都为$n$，现在你要将这 $3n$ 个字符分给 $n$ 个人，使得每个人都拿到了三种字符，假设某人的三个字符在序列中的位置为 $p_1,p_2,p_3$，其中 $p_1≤p_2≤p_3$，那么这个人的贡献为 $p_3-p_1$，问使得总贡献最小的方案数有多少，答案对 $998244353$ 取模。



$1 \leq n \leq 10^5$。


## Sol
考虑先最小化答案，感性理解，同一人的所有字符离得越近越优，即对于每个前缀新加入一个字符，优先给配对了两种字符的人贡献，其次给配对了一种字符的人贡献，最后在分配给新的一人。

于是发现 $p_3-p_1$ 的贡献，可以在独自开一组时 $-p_1$，在填最后一个字符时 $+p_3$，所以贡献可以分离，例如当前位置是 $R$，给前面任意组合 $BG$ （或 $GB$）贡献相同，可以利用这点统计答案。

于是记 $r,g,b,rg,rb,gb$ 表示对应组合的个数，利用上述方法转移即可。

这样会不会因为如 $R$ 不知道贡献给单独的 $G$ 还是单独的 $B$ 的情形而出问题？事实上，两种字符会形成 $GB$ 的情况，所以不会出现。

这样的做法钦定了按编号顺序从小到大匹配，最终答案需要乘 $n!$。
## Code
```cpp
ll n,res=1;
ll r,g,b,rg,rb,gb;
string s;
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>s;
    s=" "+s;
    for(int i=1;i<=3*n;i++){
        if(i<=n)res=res*i%mod;//神秘的阶乘写法
        if(s[i]=='R'){
            if(gb)res=res*gb%mod,gb--;
            else if(b)res=res*b%mod,b--,rb++;
            else if(g)res=res*g%mod,g--,rg++;
            else r++;
            continue;
        }
        if(s[i]=='G'){
            if(rb)res=res*rb%mod,rb--;
            else if(b)res=res*b%mod,b--,gb++;
            else if(r)res=res*r%mod,r--,rg++;
            else g++;
            continue;
        }
        if(s[i]=='B'){
            if(rg)res=res*rg%mod,rg--;
            else if(r)res=res*r%mod,r--,rb++;
            else if(g)res=res*g%mod,g--,gb++;
            else b++;
            continue;
        }
    }
    cout<<res<<endl;
    return 0;
}
```

---

## 作者：lmy_2011 (赞：0)

### 题目大意
给定一个长度为 $3\cdot n$ 的字符串，分别有 $n$ 个 $\mathtt R$、$\mathtt G$、$\mathtt B$，你可将其中的 $1$ 个 $\mathtt R$、$1$ 个 $\mathtt G$ 与 $1$ 个 $\mathtt B$ 进行组合，他们所产生的贡献为他们两个元素之间最大的差值，你需要构成 $n$ 组排列，问有多少种方案使得总贡献最小。
### 题目思路
既然说有多少种方案使得总贡献最小，那么我们就得知道如何使得总贡献最小，那么我们就得尽可能地将大的早贡献，小的晚贡献，能放到前面的就尽量放，这样就是最优的。

接着我们讨论如何将统计方案变得更少：其实，第 $3$ 个元素只需去与第 $1$、$2$ 个元素进行比较，所以第 $1$、$2$ 个元素的先后顺序并不对统计方案有影响，那我们就直接记录第 $3$ 个字元素的 $6$ 种状态：$\mathtt{R,G,B,RG,RB,GB}$，三个三个的作比较，相减算贡献，就行了。
### 题目代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define ll long long
#define mo 998244353

using namespace std;

int n;
char s[300001];
ll ans, nm[6];//R G B RG RB GB 

int ck(int i) {
	if (s[i] == 'R') return 0;
	if (s[i] == 'G') return 1;
	return 2;
}

int to(int x, int y) {
	if (x > y) swap(x, y);
	if (x == 0 && y == 1) return 3;
	if (x == 0 && y == 2) return 4;
	return 5;
}

void cg(int x, int y) {
	if (nm[x]) nm[x]--, nm[y]++;
}

int main() {
	scanf("%d", &n);
	scanf("%s", s + 1);
	
	ans = 1;
	for (int i = 1; i <= n; i++) ans = ans * i % mo;
	for (int i = 1; i <= 3 * n; i++) {
		int now = ck(i);
		if (nm[5 - now]) ans = ans * nm[5 - now] % mo, nm[5 - now]--;
			else if (nm[(now + 1) % 3] || nm[(now + 2) % 3]) ans = ans * (nm[(now + 1) % 3] + nm[(now + 2) % 3]) % mo, cg((now + 1) % 3, to(now, (now + 1) % 3)), cg((now + 2) % 3, to(now, (now + 2) % 3));
				else nm[now]++;
	}
	
	printf("%lld", ans);
	
	return 0;
} 

```


---

