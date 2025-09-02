# Gleb and Boating

## 题目描述

程序员 Gleb 经常访问 IT Campus "NEIMARK" 参加编程训练。

Gleb 不仅是程序员，还是一位著名的划船运动员，因此他选择通过划皮划艇沿河流完成部分通勤路程。假设 Gleb 从点 $0$ 出发，必须到达点 $s$（即沿直线划行 $s$ 米）。为增加挑战性，Gleb 决定不离开线段 $[0, s]$。皮划艇的尺寸可忽略不计。

Gleb 是实力强劲的程序员！初始时他的力量为 $k$。Gleb 的力量直接影响皮划艇的运动：若当前力量为 $x$，则每次划桨可使皮划艇沿当前方向移动 $x$ 米。Gleb 可以调头并继续向相反方向移动，但此操作十分困难，每次调头后力量会减少 $1$。力量永远不会变为 $0$ —— 若当前力量为 $1$，则即使调头后仍保持 $1$。此外，Gleb 不能连续两次调头 —— 每次调头后必须至少移动一次才能再次调头。同理，Gleb 不能在出发后立即调头 —— 必须先进行一次划桨。

Gleb 希望在从点 $0$ 到达点 $s$ 的过程中不离开线段 $[0, s]$ 并尽可能保留最多力量。请帮助他 —— 给定 $s$ 和初始力量 $k$，确定到达点 $s$ 时可能保留的最大力量。

## 说明/提示

第一个样例中 Gleb 的一种可能移动方式：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091G/776d3b954c1b6c71e54b3d9667d6f17ccd68b4e7.png)  

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
9 6
10 7
24 2
123456 777
6 4
99 6
10 4
99 4```

### 输出

```
4
1
2
775
1
4
2
2```

# 题解

## 作者：沉石鱼惊旋 (赞：4)

# 题意

你需要在 $[0,s]$ 的数轴上移动。不能超出这个范围。初始步长是 $k$。初始默认方向是 $0\to s$。即 $p$ 走一步走到 $p+k$。转弯一次会令 $k\gets \max\{k-1,1\}$。转弯一次是从 $p$ 走一步走到 $p-k$，以此类推。

问到达 $s$ 时最后的 $k$ 最大是几。

多测，$1\leq t\leq 100$，$1\leq s\leq 10^9$，$1\leq k\leq 1000$，$1\leq \sum k\leq 2000$。

# 做法

$s$ 很大的时候显然有通解。$s\geq k^2$ 的时候若 $k\mid s$ 则答案就是 $k$。否则答案是 $\max\{k-2,1\}$。

考虑直接走到 $k\lfloor s/k \rfloor$ 的位置。即最后一个 $k$ 的倍数。此时剩下的距离设为 $r=s\bmod k$。

$r=0$ 直接判掉答案为 $k$。

对于 $r\neq 0$ 的情况分讨如下。

若 $r\lt k-2$，考虑到我们往后一步往前一步相当于后退一步，往后 $p$ 步往前 $p$ 步就是后退 $p$ 步。我们总能找到一个 $p$ 满足 $r+p=k-2$，且由于 $s\geq k^2$ 所以 $p(k-1)\leq k\lfloor s/k \rfloor\lt k^2$。

若 $r=k-2$，我们往后退 $k-2$ 步然后往前就是一个解。显然有 $k-2 \mid (k-2)(k-1)+(k-2)$。

若 $r=k-1$，我们往后退 $k-3$ 步然后往前就是一个解。显然有 $k-2 \mid (k-3)(k-1)+(k-1)$。

所以 $s\geq k^2$ 总能找到 $k$ 或 $k-2$ 作为答案。

若 $s\lt k^2$ 则在数据范围下有 $s\lt 10^6$。而我们有显然的状态设计 $f_{i,j}$ 表示步长为 $i$ 时是否可以走到 $j$。转移就枚举走几个 $i$，直接做难以通过。

但是可以直接 bitset 优化。其实跑得很快。

---

@[wuxigk](https://www.luogu.com.cn/user/287029) 在这篇题解底下的回复（经过格式修复）：

>复杂度算错了吧，外层调和级数是 $s+s/2+\dots +s/k$，乘上单次 bitset 的 $s/w$，是 $s^2\log k/w$，正确的 bitset 优化应该是移 1 次 2 次 4 次 8 次这样吧。

我先阐述一下为什么我这个 DP 跑的很快。

考虑到 $s\geq k^2$ 的时候答案是不小于 $k-2$，所以答案是 $\sqrt s$ 量级的。

这个 DP 实际运算量是 $\mathcal O(\sum\limits_{\sqrt s}^k s^2/i/w)$ 的，打个表跑一下其实大概是 $2\times 10^{10}/w$ 的，可以轻松通过。

wuxigk 指出的做法，正如本文章代码部分所说，我尝试写了一个然后 WA 了一个很大的点，应该是这个做法下使用 `std::tr2::dynamic_bitset` 被叉了。我的这个 DP 能过只是因为本题答案的特性。如果真的想要学习正常的 bitset 优化，还是得写这个做法。另外这里也征求一份写了这个做法的代码 qaq。

---

多测可以用 `std::tr2::dynamic_bitset`（这个东西大概是唯一一个 OI 赛场上能直接用的动态 bitset，但是有 bug，参考 <https://codeforces.com/blog/entry/129454>，但是这个题我本地拍了十万组没拍出来有锅），或者说开若干个大小为 $2$ 的幂的 bitset 每次选一个刚好够的用一下，或者直接手写一个。

# 代码

感谢 @[wuxigk](https://www.luogu.com.cn/user/287029) 指出的复杂度分析问题以及更优的 bitset 优化。但是我写挂了（流汗。WA 了一个很后的点，大抵是 `dynamic_bitset` 的 bug 在这种做法下体现出来被叉掉了。这份代码还是文中的暴力转移。

<https://codeforces.com/contest/2091/submission/312735736>

```cpp
#include <bits/stdc++.h>
#include <tr2/dynamic_bitset>
using namespace std;
using namespace tr2;
void solve()
{
    int s, k;
    cin >> s >> k;
    if (s >= k * k)
        return cout << (s % k ? max(1, k - 2) : k) << '\n', void();
    vector<dynamic_bitset<>> f(k + 1);
    for (int i = 0; i <= k; i++)
        f[i].resize(s + 1);
    for (int i = 0; i <= s; i += k)
        f[k][i] = 1;
    for (int i = k; i >= 2; i--)
    {
        if (f[i][s])
            return cout << i << '\n', void();
        if (k - i & 1)
        {
            for (int j = 0; j <= s; j += i - 1)
                f[i - 1] |= (f[i] <<= i - 1);
        }
        else
        {
            for (int j = 0; j <= s; j += i - 1)
                f[i - 1] |= (f[i] >>= i - 1);
        }
        // cout << i - 1 << '\n';
        // for (int j = 0; j <= s; j++)
        //     cout << f[i - 1][j] << ' ';
        // cout << '\n';
    }
    cout << 1 << '\n';
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：Priestess_SLG (赞：3)

考虑到 $d\ge k\times k$ 的时候一定可以在两次转弯之内得出答案，因此特判即可，剩余情况均满足 $d<k\times k$。

此时暴力枚举答案为 $i$，则使用 bitset 维护当前所有可以到达的位置即可，更新答案可以直接暴力更新。

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define int long long
using namespace std;
signed main(){
    // freopen("1.out","w",stdout);
    cin.tie(0)->sync_with_stdio(false);
    int T;cin>>T;
    while(T--){
        int d,k;cin>>d>>k;
        if(d%k==0)cout<<k<<'\n';
        else if(d>=k*k)cout<<max(1ll,k-2)<<'\n';
        else{
            //d<=1e6
            bitset<2000010>bit,bit2,lim;
            bit.set(0);
            int o=1;
            for(int i=0;i<=d;++i)lim.set(i);
            for(int i=k;;--i){
                bit2.reset();
                if(!i)i=1;
                int cnt=1;
                if(o)bit2=bit<<i;
                else bit2=bit>>i;
                while(i*cnt<=d){
                    if(o==1)bit2|=(bit2<<i);
                    else bit2|=(bit2>>i);
                    ++cnt;
                }
                bit=bit2;
                bit&=lim;
                o^=1;
                // cerr<<"debug: ";
                // for(int i=0;i<=d;++i)cout<<bit[i];
                // cout<<'\n';
                // _sleep(100);
                if(bit[d]){
                    cout<<i<<'\n';
                    break;
                }
            }
        }
    }
}
```

---

## 作者：woden (赞：0)

## 题意简述
你在数轴上 $[0,s]$ 的区间内移动，最开始一次走 $k$ 步，方向为自 $0$ 到 $s$。移动途中你可以转身（即：将移动方向变为原来相反的方向），每转身一次会使 $k$ 的值变为 $\max\{k-1,1\}$。每次转身至少要走一步才能再次转身。

求：到达点 $s$ 时，$k$ 的最大值。
## 思路
首先，若 $k\mid s$，则答案显然就是 $k$。

否则，当 $s>k^2$ 时，答案必为 $k-2$，证明如下：  
首先一直往前移动到无法再移动为止。此时我们必然可以在向后移动若干次后到达一个位置使得该位置到点 $s$ 的距离恰为 $k-2$ 的倍数。然后往前走就好了。

当 $s<k^2$ 时，暴力的复杂度为 $O(k^3)$。考虑到本题时限宽裕，可以直接暴力解决。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1E6+99;
int s,k;
bitset<N>vis1,vis2;
int to;
void bfs(){
	queue<int>q;
	for(int i=0;i<s;i++){
		if(vis1[i]){
			q.push(i);
		}
	}
	while(q.size()){
		int x=q.front();
		q.pop();
		int y=x+to*k;
		if(y>=0&&y<=s&&!vis1[y]){
			vis1[y]=1;
			q.push(y);
		}
	}
}
void solve(){
	cin>>s>>k;
	if(s%k==0){
		cout<<k<<endl;
		return;
	}
	if(s>k*k){
		cout<<max(1ll,k-2)<<endl;
		return;
	}
	vis1.reset(),vis2.reset();
	to=1,vis1[k]=1;
	while(1){
		bfs();
		if(vis1[s]){
			cout<<k<<endl;
			return;
		}
		k=max(k-1,1ll);
		to*=-1;
		vis2.reset();
		for(int i=0;i<s;i++){
			if(vis1[i]&&i+to*k>=0&&i+to*k<=s){
				vis2[i+to*k]=1;
			}
		}
		swap(vis1,vis2);
	}
}
signed main() {
	fst;
	//freopen("xxx.in","r",stdin);
	//freopen("xxx.out","w",stdout);
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：DengStar (赞：0)

# CF2091G 题解

> 时间复杂度分析，bfs

看到这题的第一想法是抽象成图论模型：用三元组 $(pos, x, d)$ 代表在位置 $pos$，体力值为 $x$，方向为 $d$ 的状态。可以用 bfs 跑最短路，状态数为 $O(sk)$。实际上的时间复杂度比状态数更高，因为可能多次尝试转移到同一个状态。

我们需要优化这个做法，因为 $s$ 太大了。合理的猜测是很多状态是无用的，我们可以尝试减少状态数量。

当 $k | s$ 时，答案取到最优值 $k$，否则答案最优为 $k - 2$。我们先以 $k$ 的步长前进若干次，再以 $k - 1$ 的步长后退若干次，如果能找到某个位置，到终点的距离是 $k - 2$ 的倍数，那么答案就可以取到 $k - 2$。根据直觉，当 $s$ 很大的时候，我们就有更多的自由控制前进和后退的步数，从而找到一个到终点距离能被 $k - 2$ 整除的位置，所以答案不劣于 $k - 2$。

具体而言，一开始我们以 $k$ 的步长前进到无法前进为止。设 $r$ 是我们所在位置到终点的距离模 $k - 2$ 的余数，每往回以 $k - 1$ 的步长走一次，都会让 $r$ 在模 $k - 2$ 的意义下增加 $1$。一开始 $r$ 最小为 $0$，所以后退至多 $k - 2$ 次就会使 $r$ 变为 $0$，此时再掉头就可以一直到达终点。（注意，由于不能连续掉头，即使一开始 $r = 0$ 也要往回走。）最坏情况下需要 $k - 2 + (k - 2)(k - 1) = k(k - 2) < k^{2}$ 的长度，因此**只要当 $s \ge k^{2}$，答案就一定是 $k - 2$ 或 $k$**。

这个结论的正确性还和出发的位置无关：当 $s \ge k^{2}$ 时，从 $[0, s)$ 中的任何一个位置出发，答案都不劣于 $k - 2$。

知道这个结论之后，我们就可以只在 $s < k^{2}$ 时 bfs。此时时间复杂度最坏为 $O(k^{3})$，似乎还是过不去，但实际上已经可以过了。继续分析：设答案为 $x$，我们其实只需 bfs $k - x$ 次，时间复杂度为 $O(s(k - x))$。根据之前得到的结论，如果当前体力值不超过 $\sqrt{s}$ 且方向向右，就可以在两次掉头内到达终点，所以 $x \ge \sqrt{s} - 3$。（不是 $\sqrt{s} - 2$，因为要考虑方向，但这不重要）因此时间复杂度最坏为 $O(s(k - \sqrt{s}))$。

我们用均值不等式来求出 $T = s(k - \sqrt{s})$ 的上界。把 $T$ 改写成
$$
T = \sqrt{s} \cdot \sqrt{s} \cdot (k - \sqrt{s}) = \dfrac{\sqrt{s} \cdot \sqrt{s} \cdot (2k - 2\sqrt{s})}{2}
$$
分子中三项的和为 $2k$，根据均值不等式有
$$
T = \dfrac{1}{2} \cdot (\sqrt{s} \cdot \sqrt{s} \cdot (2k - 2\sqrt{s})) \le \dfrac{1}{2} \cdot \left( \dfrac{2k}{3} \right)^{3} = \dfrac{4k^{3}}{27}
$$
因此，虽然算法的状态数最多是 $O(k^{3})$，但常数很小，可以通过。[AC 记录](https://codeforces.com/contest/2091/submission/312517863)

---

