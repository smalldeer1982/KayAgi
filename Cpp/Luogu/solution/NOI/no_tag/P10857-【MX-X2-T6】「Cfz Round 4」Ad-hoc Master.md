# 【MX-X2-T6】「Cfz Round 4」Ad-hoc Master

## 题目背景

原题链接：<https://oier.team/problems/X2F>。

---

意気込むことはないけれど  
尽管不会每天干劲十足

生きていけるよ　君をさがして  
但我会继续一边寻找着你一边生活

## 题目描述

给定一个正整数 $h$。我们令 $n=2^h-1$。

现给出对于每个不大于 $n$ 的正整数 $u$ 和不大于 $2h-2$ 的正整数 $k$ 所对应的 $f_{u,k}$ 的值，你需要构造一组数对 $(r,w)$，满足 $1 \le r \le n$，$0 \le w \lt 2^{30}$，且存在一棵层数为 $h$ 的**满**二叉树 $T$ 满足：

- 满二叉树 $T$ 中所有结点的编号形成 $1 \sim n$ 的一个排列，且每个结点都有权值；
- 满二叉树 $T$ 的根结点为结点 $r$；
- 满二叉树 $T$ 中每个结点的权值都为小于 $2^{30}$ 的非负整数，且根结点的权值为 $w$；
- 对于每个不大于 $n$ 的正整数 $u$ 和不大于 $2h-2$ 的正整数 $k$，所有满足 $\operatorname{dis}(u,v)=k$ 的结点 $v$ 的权值的**异或和**为 $f_{u,k}$；特殊地，若没有满足条件的结点 $v$，则需要满足 $f_{u,k}=0$。

其中，$\operatorname{dis}(u,v)$ 的值等于结点 $u$ 和结点 $v$ 之间的简单路径所包含的边的数量。特殊地，$\operatorname{dis}(u,u)=0$。

题目保证至少存在一组满足条件的数对 $(r,w)$。

## 说明/提示

**【样例解释 #1】**

对于第一组测试数据：

当构造的数对 $(r,w)=(2,1)$ 时，存在一棵如图所示的二叉树符合题意，其中结点 $1,2,3$ 的权值分别为 $2,1,0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/go56fx7w.png)

当你输出 `2 2` 时，你可以获得该测试点 $50\%$ 的分数，因为 $(r,w)=(2,2)$ 虽然不满足条件，但存在一组满足条件的数对 $(r',w')=(2,1)$ 满足 $r'=r=2$。

当你输出 `1 1` 时，你也可以获得该测试点 $50\%$ 的分数。

但当你输出 `1 2` 时，你将不能获得该测试点的分数。

**【数据范围】**

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有测试数据，$1\le T \le 1000$，$2 \le h \le 16$，$\sum n \le 2^{16}$，$0 \le f_{u,k}\lt2^{30}$，保证至少存在一组满足条件的数对 $(r,w)$。

**本题采用捆绑测试。**

- Subtask 1（20 points）：$h=2$。
- Subtask 2（20 points）：满足特殊性质。
- Subtask 3（60 points）：无特殊限制。

特殊性质：存在一组数对 $(r,w)$，满足 $1 \le r \le n$，$0 \le w \lt 2^{30}$，且在此基础上存在一棵符合题意的满二叉树，其所有结点的权值均为 $w$。

## 样例 #1

### 输入

```
2
2
1 0
2 0
1 2
4
75 0 89 1 0 56
0 52 19 84 1 0
0 27 19 108 1 0
0 89 1 0 56 0
85 19 108 1 0 0
75 0 89 1 0 56
1 1 56 0 0 0
0 88 19 84 1 0
0 79 19 108 1 0
74 0 88 1 0 56
0 88 1 0 56 0
109 19 84 1 0 0
19 56 1 0 0 0
74 0 88 1 0 56
18 1 0 56 0 0```

### 输出

```
2 1
7 19```

# 题解

## 作者：Coffee_zzz (赞：13)

注意到，将所有 $\operatorname{dis}$ 为 $k$ 的信息异或起来可以得到所有深度为 $k$ 的结点的权值的异或和 $(2 \le k \le h)$，因为在满二叉树中，对于某个满足 $dep_u=k$ 的结点 $u$，满足 $\operatorname{dis}(u,v)=k$ 的结点 $v$ 的数量为奇数，而对于某个满足 $dep_u\ne k$ 的结点 $u$，满足 $\operatorname{dis}(u,v)=k$ 的结点 $v$ 的数量为偶数。证明显然。

于是我们可以得到，对于所有满足 $2\le k \le h$ 的整数 $k$，深度为 $k$ 的结点的权值的异或和，这恰恰是根结点的信息。枚举一下，找到恰好能匹配上的点即为满足条件的根结点。

再求根结点的权值。我们可以先求出所有点的权值的异或和，再异或上根结点的所有信息，得到根结点的权值。

再次注意到，如果两个点的距离为奇数，那么将两个点中所有满足 $\operatorname{dis}$ 为奇数的信息异或起来就能得到所有点的权值的异或和。如果两个点的距离为偶数，则异或起来会得到 $0$。

那我们任选一个点，枚举剩下的点，按照上述方法求出异或和。注意如果得到的全是 $0$，那么其实所有点的权值的异或和就是 $0$。

于是我们就可以求出根节点的编号和根结点的权值了。

---

## 作者：Wf_yjqd (赞：13)

零贡献所以来补个题。

很好的对上了 cfz 的脑电波。

---

Update on 240815：想当然了导致被 hack。

思路无错，仅代码实现问题。

如果 $f_{u,k}\not =0$（$h\le k\le h\times2-2$），$u$ 肯定不能作为根。

而我原本代码中直接判断了总异或和是否相等，显然忽略了多个非 $0$ 数异或和为 $0$ 的情况。

现已修正。

---

显然需要凑出大量关于根节点的信息。

比较关键的是想到对若干 $f$ 求异或和后，每个点的权值是否被统计到取决于与他距离为 $k$ 的点数的奇偶性。

除根外每个点的邻接点个数都是奇数。用 $w_i$ 表示 $i$ 点点权，$rt$ 表示根的编号，那么 $\bigoplus\limits_{i=1}^n f_{i,1}=(\bigoplus\limits_{i=1}^n w_i)\oplus w_{rt}$。

仅靠这一点显然没法确定根。拓展上面的想法可以发现：对于 $k\in[2,h]$，$\bigoplus\limits_{i=1}^n f_{i,k}=f_{rt,k-1}$。

实际上你就确定了题目给出的所有与根有关的信息，那么满足以上条件的点一定可以作为答案。

求根的权值略难一点。

凑了很久，发现实际上很难多个点让统计到根节点的次数为奇。

考虑能否只用除根外一个点的值，就没那么复杂了。

以根的子节点为例，要统计到根就需要和统计他距离为 $1$ 的点。但这样就会导致他的子节点也被统计到。这就很烦。

莫名考虑求出 $\bigoplus\limits_{i=1}^n w_i$，这样只需要和 $\bigoplus\limits_k f_{rt,k}$ 异或一下就能得到 $w_{rt}$。

然后延续上面的思路，统计与每个点距离奇偶性不同的点权异或和。根节点与他儿子奇偶性不同，这样恰好能不重不漏地（主要指根能统计到儿子，儿子能统计到根）把每个点都统计到。

但是衍生了一个问题，并不知道根的儿子是谁。然后发现上面的结论也是只跟奇偶性有关的，所以只需要任意一个和他距离为奇的点，得到的答案都是一样的。

好像还是不好求，反过来考虑，和他距离为偶的点的答案实际上和他相同，那么不同的就是和他距离为奇的点（如果找不到的话说明答案本身就是 $0$）。

然后就做完了。Ad-hoc Master！

---

最后水个代码。显然是很好写的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=7e4+26;
namespace Ai_I{
    inline int read(){
        int x=0;
        char c=getchar();
        while(c<'0'||c>'9')
            c=getchar();
        while(c>='0'&&c<='9'){
            x=x*10+c-'0';
            c=getchar();
        }
        return x;
    }
}
using namespace Ai_I;
int T,h,n,f[maxn][32],s[maxn][2],ss[32],rt,ans;
inline bool check(int x){
	if(s[x][1]!=ss[1])
		return 0;
	for(int i=h;i<=h*2-2;i++)
	    if(f[x][i])
	        return 0;
	for(int i=2;i<=h;i++)
		if(f[x][i-1]!=ss[i])
			return 0;
	return 1;
}
int main(){
	T=read();
	while(T--){
		h=read();
		n=(1<<h)-1;
		for(int j=1;j<=h*2-2;j++)
			ss[j]=0;
		for(int i=1;i<=n;i++){
			s[i][0]=s[i][1]=0;
			for(int j=1;j<=h*2-2;j++){
				f[i][j]=read();
				if(j&1)
					s[i][0]^=f[i][j];
				s[i][1]^=f[i][j];
				ss[j]^=f[i][j];
			}
		}
		rt=0;
		for(int i=1;i<=n;i++)
			if(check(i)){
				rt=i;
				break;
			}
		ans=s[rt][1];
		for(int i=1;i<=n;i++)
			if(s[i][0]!=s[rt][0]){
				ans^=s[i][0]^s[rt][0];
				break;
			}
		printf("%d %d\n",rt,ans);
	}
	return 0;
} 
```

---

## 作者：McIron233 (赞：9)

数据人题解，**仅提供思路导引。**

个人认为是一个个人差很大的题目。

## 算法 1

先画一棵 $h=2$ 的二叉树，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/oubw6rse.png)

然后列一张表格，表示 $f_{u,k}$ 的值，根据题意可以得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/2i1nc7k0.png)

其中 $v_u$ 是结点 $u$ 的权值。

不难发现，$f_{2,1}$ 和 $f_{3,1}$ 是相等的。因此只需要找到这三个点中 $f_{u,1}$ 与其他两者不同的那个 $u$ 就行，剩下两者就是所需的 $w$。

若三个相等，则 $w$ 仍然是 $f_{u,1}$，而根结点 $r$ 只需要满足 $f_{r,2}=0$ 即可。这个结论读者自证不难。期望得分 $20$。

## 算法 2

注意到对于根节点 $r$，必有 $f_{r,k}=0$。因此找到符合这个条件的结点即可。

对于根节点的权值，由于二叉树的每个结点的权值都为 $w$，因此只需要找到 $f_{u,k}$ 中的非零值即可。若没有非零值，则 $w=0$。

期望得分 $20$，结合算法 1 期望得分 $40$。

## 算法 3.1

考虑对 $h=4$ 列出 $f_{u,k}$ 的表格。

由于只有 $h$ 和 $f_{u,k}$，考虑对这张表格的每一行和每一列求异或和。

然后你会发现，第 $k(2 \leq k \leq h)$ 列的异或和与根节点的 $f_{r,k-1}$ 信息在数值上是能够对应上的。利用此规律就能找到根节点，期望得分 $50$，结合前面算法期望得分 $70$。

## 算法 3.2

求出根节点之后，可以计算 $f_{r,k}$ 的异或和，显然这个异或和是除了根节点外所有其他结点权值的异或和。

给出一个结论（from Cfz）：

> 如果两个点的距离为奇数，那么将两个点中所有满足 $\operatorname{dis}$ 为奇数的信息异或起来就能得到所有点的权值的异或和。如果两个点的距离为偶数，则异或起来会得到 $0$。

利用这个结论就能直接求出所有结点权值的异或和。

如何发现这个结论？可以观察一下表格去凑出所有结点权值的异或和，由于直接取一列的异或和会把根节点的权值消掉，所以考虑只使用两行信息，然后就能凑出来了。

于是根节点的权值就求出来了，期望得分 $100$。

## 造数据思路

确定每个结点的权值之后使用树形 dp 得到输入数据。

第一个子任务造法比较鲁莽：所有点随机权值、所有点权值为零、部分点权值为零其余随机、所有点权值为同一个值等等。造了一个 $T=1000$ 的测试点。

第二个子任务由于特殊性质，只造了这样的测试点：

所有点权值为 $0$ 或同一个随机权值。然后按照数据范围卡了程序运行效率。

第三个子任务造法：

共造 $5$ 组测试点。其中每一组按照程序运行效率来卡，分别有 $n=2,3,4, \cdots, 15$，$n=16$，$T=1000,n=6$。

第一组测试点中：每一个点都是随机权值，其中随到 $0$ 的概率为 $1\%$，剩下的权值等概率。

第二组测试点中：每一个点都是随机权值，其中随到 $0$ 的概率为 $99\%$，剩下的权值等概率。

第三组测试点中：除第一层外，每一层随机将左半边或右半边的结点权值全部设置为 $0$，剩下半边随机权值。

第四组测试点中：每个点的权值很小，并且从根节点开始，对每个没有赋予权值的点进行随机游走，本次游走遍历到的点全部赋予一个相同的权值。

第五组测试点中：造法不予公开。

可能还是放过了一些错解。在此谢罪。

---

## 作者：xhgua (赞：7)

妙妙题。

下文中令根节点的深度为 $0$。

我们先考虑如何找出根节点 $r$，显然的有 $f_{r,k} = \bigoplus\limits_{u = 1}^n [\text{dep}_u = k]w_u$，我们不妨思考如何求出 $g_k = \bigoplus\limits_{u = 1}^n [\text{dep}_u = k]w_u$。

> 结论 1：所有 $f_{u, k + 1}$ 的异或和即为 $\bigoplus\limits_{u = 1}^n [\text{dep}_u = k]w_u$。

对于每个 $u$ 计算出到其距离为 $k + 1$ 的节点个数的奇偶性，从而判断其对答案有无贡献。

若 $\text{dep}_u = k$，则在 $u$ 子树内有偶数个节点到 $u$ 的距离为 $k + 1$，在 $u$ 的子树外只有 $1$ 个节点到 $u$ 的距离为 $k + 1$（不妨假设 $u$ 在根节点的左子树中，那么唯一的节点 $v$ 就是根节点的右儿子），总个数为奇数，其对答案的贡献为 $w_u$。

若 $\text{dep}_u \lt k$，子树内仍然是有偶数个节点，子树外的部分，我们考虑 $u$ 的每个祖先 $f$（不妨设 $u$ 在 $f$ 的左子树内），钦定 $v$ 在 $f$ 的右子树内，则对于每个 $f$，我们都有偶数个节点 $v$ 满足条件，于是其对答案的贡献为 $0$。

若 $\text{dep}_u \gt k$，子树内同理，子树外还是考虑 $u$ 的每个祖先 $f$，对于 $\text{dep}_u - \text{dep}_f\lt k$ 的祖先，我们都有偶数个满足条件的 $v$，对于 $\text{dep}_u - \text{dep}_f = k$ 的祖先，我们只有一个节点（即 $f$ 的右儿子）满足条件，对于 $\text{dep}_u - \text{dep}_f = k + 1$ 的祖先，同样也只有一个节点（即 $f$ 本身）满足条件，所以总个数为偶数，对答案贡献为 $0$。

于是，只有深度为 $k$ 的节点会被计算贡献，也就证明了上述引理。

现在我们已经求出了 $g_k$，我们将其与每个节点的 $f$ 逐一比对，找出根节点 $r$（注意要判断 $k\geq h$ 时，$f_{r, k}$ 是否全为 $0$）。

接下来我们考虑如何求出根节点的权值，注意到我们只需求出所有节点的权值异或和即可，于是问题转化为如何求出所有节点的权值异或和。

> 结论 2：对于两个节点 $u, v$，若 $\text{dis}(u, v)$ 为奇数，则所有点权的异或和即为：
> $$
> \bigoplus\limits_{k = 1}^{2h - 2}[2\nmid k]f_{u, k}\oplus f_{v, k}
> $$
> 若 $\text{dis}(u, v)$ 为偶数，则上述式子为 $0$。

我们要证明的就是，对于两个节点 $u, v$，若 $\text{dis}(u, v)$ 为奇数，则到 $u$ 距离为奇数的点集 $S_u$ 和到 $v$ 距离为奇数的点集 $S_v$ 交集为空，且并集为全集。

其实已经很显然了，对于一个节点，要么它到 $u$ 的距离为奇数，要么它到 $v$ 的距离为奇数，容易证明这两者是对立的。

$u, v$ 距离为偶数的证明也是类似，这里不再赘述。

于是我们只需随意固定一个点，枚举另外一个点，根据结论 2 中的式子求出异或和，若该值不为 $0$，则所有点权的异或和即为该值（如果得到的所有值均为 $0$，那么说明所有点权的异或和就是 $0$），然后就能求出根节点的权值 $w$。

总的时间复杂度为 $\mathcal{O}(h2^h)$。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 5, LOG = 16;

int T, n, h;
int f[N][LOG << 1], g[LOG];

void solve() {
	std::cin >> h; n = (1 << h) - 1;
	for (int u = 1; u <= n; u++) for (int k = 1; k <= 2 * h - 2; k++) std::cin >> f[u][k];
	for (int k = 1; k < h; k++) {
		g[k] = 0;
		for (int u = 1; u <= n; u++) g[k] ^= f[u][k + 1];
	}
	for (int u = 1; u <= n; u++) {
		bool ok = true;
		for (int k = 1; k < h; k++) ok &= (g[k] == f[u][k]);
		for (int k = h; k <= 2 * h - 2; k++) ok &= (f[u][k] == 0);
		if (ok) {
			int v1 = (u == 1 ? 2 : 1), all = 0;
			for (int v2 = 1; v2 <= n; v2++) if (v1 != v2) {
				all = 0;
				for (int k = 1; k <= 2 * h - 2; k += 2) all ^= f[v1][k] ^ f[v2][k];
				if (all != 0) break;
			}
			int w = all;
			for (int k = 1; k < h; k++) w ^= f[u][k];
			return std::cout << u << " " << w << "\n", void();
		}
	}
}

int main() {

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> T;
	while (T--) solve();

	return 0;
}
```

---

## 作者：MatrixGroup (赞：5)

Let's find one possible $r$ first. Since the given information of the nodes are symmetric, one should focus on the XOR sum of all the $f_{u,k}$ for a specific $k$. One can easily verify that, for $k\ge 2$, the value is exactly $f_{r,k-1}$. Additionally, since the only given information of a node is its $f$ value, one can arbitrarily choose one $r$ whose $f$ value matches the desired value.

It can be easily verified that the XOR sum of all $f_{r,k}$ is the XOR sum of the value of all nodes except $r$. Therefore, to find $w$, one only needs to find the XOR sum of the value of all nodes. Using the given $f$, one can easily evaluate the XOR sum of the value of the nodes whose distance from one specific node is odd. If one colors the tree in two colors by the parities of the nodes' depths, or their distances from the root, then two nodes' distance is odd if and only if they are of different colors. Therefore, the value described above is the same for nodes of the same color, and the XOR sum of the value of two different colored nodes is exactly what is needed. Find all the distint values, and the needed value if $0$ is there is only one distinct value, and their XOR sum if there are two distinct values.

---

