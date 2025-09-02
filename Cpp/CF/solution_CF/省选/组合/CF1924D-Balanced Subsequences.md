# Balanced Subsequences

## 题目描述

A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters '+' and '1'. For example, sequences '(())()', '()', and '(()(()))' are balanced, while ')(', '(()', and '(()))(' are not.

A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements.

You are given three integers $ n $ , $ m $ and $ k $ . Find the number of sequences consisting of $ n $ '(' and $ m $ ')', such that the longest balanced subsequence is of length $ 2 \cdot k $ . Since the answer can be large calculate it modulo $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 说明/提示

For the first test case "()()", "(())" are the $ 2 $ sequences

For the second test case no sequence is possible.

For the third test case ")((()", ")(()(", ")()((", "())((" are the $ 4 $ sequences.

## 样例 #1

### 输入

```
3
2 2 2
3 2 3
3 2 1```

### 输出

```
2
0
4```

# 题解

## 作者：UnyieldingTrilobite (赞：20)

场上看到这玩意直接傻了。不止在一个地方见过这个形式。

我们考虑对一个固定的字符串，存在贪心算法求它的最长合法子序列。维护一个初始为空的栈并从左到右扫描每一个括号，若为左括号则入栈，若为右括号且栈非空则弹栈并更新答案。若不妨 $n\ge m$，则要考虑的仅仅是有多少个右括号入栈时栈为空。考虑维护一条折线，从 $(0,0)$ 到 $(n+m,n-m)$；随着横坐标的增大，纵坐标依照横坐标对应下标的括号而变化：若为左括号则增一，否则减一。那么不难发现，当有右括号无法入栈时，本质上是折线当前落点在横轴上，将减一的折线修正为与横轴贴合。如此一来，所有该位置之后的折线全体向上平移一格。以此视角来看，右括号入栈时栈为空的次数恰等于折线所能达到最低点的纵坐标的绝对值。换而言之，折线能达到的最低点纵坐标为 $k-m$。

由于折线起始点在 $(0,0)$，所以一旦 $k\gt m$ 则会直接矛盾。否则，我们本质上是要统计这样折线的数量：从 $(0,0)$ 到 $(n+m,n-m)$，且最低点纵坐标为 $k-m$。我们意识到这玩意不太好做。记 $f(t)$ 为从 $(0,0)$ 到 $(n+m,n-m)$，且最低点纵坐标不大于 $t-m$ 的数量，那么答案显然为 $f(k)-f(k-1)$。熟悉卡特兰数的话这里就很典了，把折线最后一次触碰直线 $y=t-m$ 的交点之后的部分全部上下反转，那么这就成为了一条从 $(0,0)$ 到 $(n+m,2t-n-m)$ 的折线，方案数显然等于 $\binom{n+m}{t}$。

于是这个题就做完了。代码丢个核心部分吧。

```cpp
  for (cin >> T; T; --T) {
    cin >> n >> m >> k;
    if (k > min(n, m)) {
      cout << 0 << '\n';
      continue;
    }
    cout << (C(n + m, k) - C(n + m, k - 1)).val() << '\n';
  }
```

---

## 作者：MiniLong (赞：5)

首先判掉无解（即 $\min(n,m) < k$ 的情况）。

先考虑有 $k$ 个左括号，$k$ 个右括号组成 $2k$ 长度合法括号序列个数。不妨把问题转化为在矩形上从 $(0,0)$ 走到 $(k,k)$ 的方案数。遇到左括号就往右走，即 $(x,y) \to (x+1,y)$，遇到右括号就向上走 $(x,y) \to (x,y+1)$，由于合法的括号序列每个前缀左括号个数是大于等于右括号个数的，所以我们钦定每个时刻都所在的点都只能在函数 $y=x+1$ 的下方（不能在函数上）。直接求不好求，考虑容斥，求所有走到函数以上的方案。容易发现，所有这种方案在以 $y=x+1$ 为对称轴对称后到达 $(k-1,k+1)$（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/tjt6id9y.png)

且每种上述不合法的方案与无限制地走到 $(k-1,k+1)$ 的方案一一对应，于是答案就是 $\binom{2k}{k} - \binom{2k}{k-1}$。

其实上面的问题是经典的卡特兰数，但是为我们提供了一种好的思路。

考虑有 $n$ 个左括号 $m$ 个右括号。

最后的括号串去掉所有匹配的括号对一定是形如 `)))((((` 的，不妨枚举最后一个右括号前有 $i$ 对匹配的括号，根据上面的思路，也就是要求从 $(0,0)$ 走到 $(i,i+m-k)$。但如果直接走就不知道最后一步是不是往上（就是不能确定最后一位是不是右括号），那么强制钦定最后一位为右括号，就剩下 $m - k -1$ 个右括号放到前面，从 $(0,0)$ 走到 $(i,i+m-k-1)$，且不能超过 $y=x+m-k-1+1$，方案计算与上面类似，即 $\binom{2i+m-k-1 }{i}-\binom{2i+m-k-1}{i-1}$。

这是前 $i$ 对的方案，后面 $k-i$ 对再加上 $n$ 个左括号也类似，但是不用强制规定某个位必须是左括号了，方案就是 $\binom{2(k-i)+n-k}{k-i}-\binom{2(k-1)+n-k}{k-i-1}$。

预处理组合数计算就行，时间复杂度 $O(n)$。

---

## 作者：EuphoricStar (赞：5)

发现去掉匹配的 $2k$ 个括号后，剩下的串一定形如  $)) \ldots )(( \ldots ($，其中右括号数量为 $a = m - k$，左括号数量为 $b = n - k$。

考虑把剩下的串像 $)) \ldots ) \mid (( \ldots ($ 一样分成两半。枚举左半边加入了 $\frac{i}{2}$ 对匹配，则长度为 $a + i$，右半边长度为 $b + 2k - i$。根据乘法原理把两半的方案数相乘即可。下面只讨论左半边的计算，右半边类似。

考虑折线图。相当于每一步可以向右上或右下走，求 $(0, 0) \to (a + i, -a)$ 且不接触直线 $y = -a - 1$ 的方案数。这是经典问题。考虑容斥，总方案数 $\binom{a + i}{a + \frac{i}{2}}$ 减去接触的方案数。把折线与 $y = -a - 1$ 最后一个交点之前的部分对称过去，相当于 $(0, -2a - 2) \to (a + i, -a)$。可以解得需要向右上走 $a + \frac{i}{2} + 1$ 步，所以接触的方案数就是 $\binom{a + i}{a + \frac{i}{2} + 1}$。

注意为了避免算重，我们钦定左半边到达 $(a + i, -a)$ 是最后一次接触直线 $y = -a$。也就是说右半边除了第一步外不能接触直线 $y = -a$。钦定第一步向右上走后也可以类似地计算。

时间复杂度 $O(\sum n + m + k)$。

[code](https://codeforces.com/problemset/submission/1924/243641586)

---

## 作者：OrezTsim (赞：5)

随到了这道题。

首先钦定 $n \ge m$，反过来一样的。

显然 $k>m$ 时无解。

考虑模拟计算一个确定的括号串的答案。

记 $c_i$ 为加入第 $i$ 个字符后，还需匹配的左括号的数目。

- 若第 $i$ 个字符为左括号，$c_i=c_{i-1}+1$。
- 否则当 $c>0$ 时，$c_i=c_{i-1}-1$。

即对于第二种情况，有 $c_i=\max(c_{i-1}-1,0)$。

那么没有计入答案的右括号总共有 $m-k$ 个，即经过此次操作 $c$ 仍然保持 $0$ 不变。

想象一下，如果这个时候依然选择 $-1$，那么这之后的所有 $c_j$ 均会 $-1$。

转化一下，得到 $c_i$ 必须满足 $\min\limits_{i=1}^n c_i=k-m$。

规定右方为 $y$ 轴正方向，上方为 $x$ 轴正方向，下方为 $x$ 轴负方向。

将 $(i,c_i)$ 放在二维平面上，那么等同于：

- 从 $(0,0)$ 出发前往 $(n+m,n-m)$，每次往右上或右下走一格。
- 路径经过 $y=k-m$，且 $\min\limits_{i=1}^n c_i=k-m$。

这样做实在抽象，所以逆时针旋转 $45 \degree$，那么题意又转化为：

- 从 $(0,0)$ 出发前往 $(n,m)$，每次往右或往上走一格。
- 路径经过 $y=x+(k-m)$，且不得经过该函数右侧。

第二条限制可以转化为：

- 经过 $y=x+(k-m)$ 的路径数减去经过 $y=x+(k-m-1)$ 的路径数。

计算经过某斜线的方案数比较经典，直接将 $(n,m)$ 关于该斜线对称得到 $(n',m')$，然后计算 $(0,0)$ 出发前往 $(n',m')$ 的方案数即可。

因为从一个矩形的左下角走到右上角显然经过一条将其拦腰斩断的斜线。

那么代入一下，答案就是 $\Large\binom{n+m}{k}-\binom{n+m}{k-1}$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=4e3+10,P=1e9+7;
int n,m,k,C[N][N];
void md(int &x,int y) { ((x+=y)>=P)&&(x-=P); }
int Mod(int x,int y) { md(x,y); return x; }

void solve() {
    cin>>n>>m>>k;
    if(k>n||k>m) return cout<<"0\n",void();
    cout<<Mod(C[n+m][k],P-C[n+m][k-1])<<"\n";
}

auto main() -> signed {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    for(int i=0;i<=4e3;++i) C[i][0]=1;
    for(int i=1;i<=4e3;++i)
        for(int j=1;j<=i;++j)
            C[i][j]=Mod(C[i-1][j-1],C[i-1][j]);
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：Flan (赞：4)

在任一满足条件的序列中，都有 $n-k$ 个左括号和 $m-k$ 个右括号未配对；显然所有未配对的左括号都在所有未配对的右括号的后面，这些未配对括号的相对顺序是唯一的。在这些 $n+m-2k$ 个未配对括号之间的 $n+m-2k+1$ 个位置中插入一系列总长度为 $2k$ 的合法括号序列就可以得到所有满足要求的序列，且不会重复计算。于是原问题转换为：

计算长度为 $n+m-2k+1$ 的序列 $A=\{a_1, a_2, \ldots, a_{n+m-2k+1}\}$ 的个数，其中 $A$ 的元素 $a_i$ 为合法括号序列，且 $\sum\limits_{i=1}^{n+m-2k+1} |a_i| = 2k$。（$|a_i|$ 表示 $a_i$ 的长度）

令 $H$ 为卡特兰数的 OGF，则我们只需求 $[x^k]H^{n+m-2k+1}$。我们本可以利用 NTT 进行 $O(n^2\log n)$ 的预处理求出 $H$ 的所有幂；但本题刻意卡了 NTT，时限很短且模数非 NTT 模数。

不过我们知道，卡特兰数的 OGF 满足 $xH^2-H+1=0$，移项得 $H^2=\dfrac{H-1}{x}$，即 $H^n=\dfrac{H^{n-1}-H^{n-2}}{x}$（$n\ge 2$）；由于 $H$ 的任意次幂的常数项均为 $1$，所以 $H^{n-1}-H^{n-2}$ 的常数项为 $0$，可以直接除以 $x$。因此，可以通过 $H^{n-1}$ 和 $H^{n-2}$ 在 $O(n)$ 时间内求出 $H^n$。

通过 $O(n^2)$ 的预处理得到 $H$ 的 $1$ 至 $4001$ 次幂，即可常数回答每组询问。

---

## 作者：_ANIG_ (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1924D)

最长的平衡子序列实际上就是求有多少对能匹配的括号。

先考虑如何求最长平衡子序列。

枚举到一个右括号，记录一下当前匹配了多少对括号。

若当前的前缀中左括号的数量小于已经匹配的括号的对数，则存在一个左括号与当前的右括号匹配。

把这两个信息塞到状态里，就得到了 dp 状态：

$dp_{n,m,k}$ 表示当前有 $n$ 个左括号，$m$ 个右括号，已经匹配了 $k$ 对括号的方案数。

但是这样的状态是 $O(n^3)$ 的。

打个表可以发现状态的值只与 $n+m$ 和 $k$ 有关。

把 $n+m$ 压到一维，复杂度就变为了 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mods=1e9+7,N=8005;
int f[6005][2005],t,n,m,k,rs[N];
struct node{
    int m,k,bh;
};
vector<node>q[N];
signed main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n>>m>>k;
        if(n<m)swap(n,m);
        q[n].push_back((node){m,k,i});
        
    }
    f[0][0]=1;
    for(int i=0;i<=2000;i++){
        for(int j=0;j<=4000;j++){
            for(int l=i;l<=i;l++){
                if(l>i)continue;
                if(j){
                    if(l&&l-1<=j-1)f[j+i][l]+=f[j+i-1][l-1];
                    if(l==i&&l<=j-1)f[j+i][l]+=f[j+i-1][l];
                }
                f[j+i][l]%=mods;
            }
        }
        for(int j=0;j<q[i].size();j++){
            if(q[i][j].m>=q[i][j].k)rs[q[i][j].bh]=f[q[i][j].m+i][q[i][j].k];
        }
    }
    for(int i=1;i<=t;i++)cout<<rs[i]<<"\n";
}
```


---

## 作者：EthanOI (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1924D)

看到题干知道是 $\text{Catalan}$ 数的很经典的 $\text{Dyck}$ 路径问题变体。

比较容易想到的是传统的画法：一个 $n\times m$ 网格，将括号序列对应到一条从 $(0,0)$ 到 $(n,m)$ 的路径，是 $\texttt($ 则往右走，是 $\texttt)$ 则往左走。但我更喜欢的表达：一个赌徒在赌场赌钱，$\texttt($ 代表赢钱，$\texttt)$ 代表输钱，左边 $(t,q)$ 表示 $t$ 时刻赌徒有 $q$ 元钱，则最后对应从 $(0,0)$ 到 $(n+m,n-m)$ 的折线路径。以下使用此组合模型对问题进行叙述。

下面关键在于如何对最长子序列为 $k$ 进行刻画：注意到赌徒赢钱次数一定是越多越好，最后有剩余的只需去掉最后几个即可。而要 $k$ 尽可能大，序列中包含尽可能多的输钱的情形。这样，贪婪算法的想法就产生了：遇到赢钱全部保留，遇到输钱，若输完钱数非负，则加入序列，否则跳过。不难验证此算法是最优的。

在此算法下，序列长度为 $2k$ 代表输了 $k$ 次钱，因此有 $m-k$ 次输钱没用上。但这些时刻位置比较明确，如下图所示：

![$n=13,m=11,k=8$](https://i.postimg.cc/d0jsLRZx/20240223123059.jpg)

第一次未用上代表此时已经输光，即触碰到 $x$ 轴，我们将轴向下平移一个单位。第二次未用上即为第一次触碰到变换后的实轴，再将其向下平移一个单位。共 $m-k$ 次，因此最终平移 $m-k$ 个单位，为直线 $y=k-m$。

现在只需计算折线最低点恰在 $y=k-m$ 上的方法数了，运用经典的 $\text{Dyck}$ 路径对应方法可以解决。对任何一条 $y=t$，设 $N(t)$ 为最低点不高于 $y=t$ 的方法数，则将每一条路径与 $y=t$ 的最后一个交点取出，将之后的路径关于 $y=t$ 对称，这样构造了一个从 $(0,0)$ 到 $(n+m,2t-n+m)$ 的任意路径的双射（双射细节的证明读者自行验证）。从而 $N(t)=\binom{n+m}{t+m}$。最后，所求即为 $N(k-m)-N(k-m-1)=\binom{n+m}{k}-\binom{n+m}{k-1}$，求出表达式后就基本做完了。

~~希望这次能过了~~

---

## 作者：zifanwang (赞：2)

先判掉 $k>\min(n,m)$ 的情况。

首先有个明显的计算最长合法括号子序列的贪心方法：初始一个值为 $0$ 的计数器，从左到右枚举每个字符，遇到 `(` 时将计数器加一，遇到 `)` 时如果计数器不为 $0$ 就减一然后将答案加一。

考虑绘制它的折线图。初始时纵坐标为 $0$，从左到右枚举每个字符，遇到 `(` 加一，遇到 `)` 减一。考虑有多少个 `)` 不会被匹配到，即在开头需要加入的最少 `(` 的数量使得折线不会有在横轴下方的部分。于是题目中的限制就转化为了要使折线能到达的最低点纵坐标为 $k-m$。

记 $f(k)$ 表示能到达的最低点纵坐标为 $k-m$ 的折线个数，那么答案就是 $f(k)-f(k-1)$。考虑将折线最后一次碰到直线 $y=k-m$ 以后的部分上下翻转，那么就转化为了从 $(0,0)$ 走到 $(n+m,2k-m-n)$ 的路径方案数，组合数直接求即可。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 4003
#define md 1000000007
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int t,n,m,k;
ll fac[mxn],ifac[mxn];
ll power(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1)ans=ans*x%md;
		x=x*x%md;
	}
	return ans;
}
inline ll C(int n,int m){
	if(n<m||m<0)return 0;
	return fac[n]*ifac[m]%md*ifac[n-m]%md;
}
int f(int k){
	return C(n+m,(n+m-(2*k-m-n))>>1); 
}
void init(int n){
	fac[0]=1;
	rep(i,1,n)fac[i]=fac[i-1]*i%md;
	ifac[n]=power(fac[n],md-2);
	drep(i,n,1)ifac[i-1]=ifac[i]*i%md; 
}
signed main(){
	init(4e3);
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&k);
		if(k>min(n,m)){
			puts("0");
			continue;
		}
		cout<<(f(k)-f(k-1)+md)%md<<'\n'; 
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

考虑在 $n×m$ 的网格图上，从 $(0,0)$ 移动到 $(n,m)$，左括号对应向右移动一步，右括号对应向上移动一步。那么未被匹配的右括号的数量就是 $x-y$ 的最大值。要让匹配括号对数不超过 $k$，$x-y$ 的最大值要不小于 $m-k$，即折线与直线 $x-y=m-k$ 相交。

我们在第一个交点处，将之后的折线关于直线翻转，则终点变为 $(n+m-k,k)$。且终点为 $(n+m-k,k)$ 的折线和满足前面条件的折线之间是双射关系（因为终点为 $(n+m-k,k)$ 的折线一定穿过直线 $x-y=m-k$，而翻转操作又是可逆的）。则方案数即为 $C_{n+m-k+k}^{k}=C^k_{n+m}$。

```cpp
Z get(int n, int m, int k) {
    if (k >= min(n, m)) return comb.get(n + m, m);
    else return comb.get(n + m, k);
}
 
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    cout << get(n, m, k) - get(n, m, k - 1) << "\n";
}
```


---

## 作者：123456xwd (赞：2)

首先，若 $\min(n,m)<k$，显然无解。

我们发现，假设我们确定了序列中受匹配的左右括号，整个序列都确定了，你一定是从最左边的空位一直开始填 ``)``，填完后在剩下的空位填写 ``(`` 即可。

那么，$\tbinom{n+m}{k}$ 其实就表示在长度为 $n+m$ 的空串中，选出来 $\le k$ 对合法括号子序列的方案数，相当于我们统计受匹配的左括号，然后就可以确定与之对应的右括号，然后就可以得到整个序列了。

不过由于我们随便放可能导致这 $k$ 个左括号中有的无法填写合法的右括号，所以是 $\le k$（如左括号填写在最右边的情况）。

所以我们最终的答案就是 $\tbinom{n+m}{k}-\tbinom{n+m}{k-1}$，就是 $\le k$ 对匹配的减去 $\le k-1$ 对匹配的，其实就是有 $k$ 对匹配的方案数。

代码显然，就不放了。

---

