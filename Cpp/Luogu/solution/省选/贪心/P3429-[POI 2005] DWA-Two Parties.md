# [POI 2005] DWA-Two Parties

## 题目描述

拜占庭国王要举办两个大派对，并且希望邀请更多的居民。

国王从他的丰富经验里知道，如果一个居民在派对上能遇到偶数个的朋友，那他会非常高兴。因此，他要求你邀请国家的居民去两个派对，而使尽可能多的人在他们的聚会上有偶数个的朋友。

认识是一种对称关系，如 $A$ 认识 $B$，那么 $B$ 也认识 $A$。


## 样例 #1

### 输入

```
5
3 2 3 4
2 1 3
4 2 1 4 5
2 1 3
1 3```

### 输出

```
3
1 2 3```

# 题解

## 作者：耳朵龙_ (赞：8)

本题现有题解没有提供答案为 $n$ 的证明，补一个证明。

将人看做点，认识关系看作无向边，原题意等价于：给定一张无向图，$0/1$ 染色后，称一个点是好的，当且仅当与之相邻且同色的点的个数为偶数。构造一种染色方案使好点的个数最多。

记点 $i$ 的颜色为 $col_i$，度数为 $deg_i$，图的边集为 $E$。

假设好点个数可以为 $n$，那么当好点数为 $n$ 时，根据与点 $i$ 相邻且同色的点的个数为偶数，可知点的颜色满足一个 $n$ 行的异或方程组，第 $i$ 行为：

$$\begin{cases}\bigoplus\limits_{(i,v)\in E}col_v=0&2\mid deg_i\\\left(\bigoplus\limits_{(i,v)\in E} col_v\right)\oplus col_i=1&2\nmid deg_i\end{cases}$$

若该方程组有解，那么容易构造出使好点个数为 $n$ 的染色方案，下面证明该方程组一定有解。

若该方程组无解，则必然能将某几行异或起来，使得等号左边各未知数系数均为 $0$，而等号右边常数为 $1$。即存在 $S\subseteq\mathbb{N^*}$，$\bigoplus\limits_{i\in S}$ 第 $i$ 个方程左边 $=0$，$\bigoplus\limits_{i\in S}$ 第 $i$ 个方程右边 $=1$。

称点 $i$ 被选择，当且仅当 $i\in S$。称 $v$ 属于 $u$ 的邻域，当且仅当 $(u,v)\in E$。则方程组无解当且仅当存在 $S$ 使得：

+ 选择了奇数个奇度点（右边异或和为 $1$）
+ 每个被选择的奇度点的邻域内都选了奇数个点，其他点的邻域内都选了偶数个点（左边各未知数系数均为 $0$）

可以根据 $S$ 构造一张无向图 $G'$，其点集与原图相同，边集为 $\{(u,v)\mid u\in S\lor v\in S\}\cap E$。由于 $G'$ 是一张无向图，其度数和为偶数。在 $G'$ 中，容易发现被选择的奇度点度数为奇数，而其他点度数为偶数，由于被选择的奇度点有奇数个，$G'$ 的度数和为奇数。前后矛盾，因此这样的选点方案不存在，方程组有解。

高斯消元解该方程组，输出方案即可，时间复杂度 $O\left(\frac{n^3}{\omega}\right)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=205;
int n,m,b[N];
bitset<N>a[N];
int main(){
	scanf("%d",&n);
	for(int i=1,l,x;i<=n;++i){
		scanf("%d",&l),a[i][n+1]=a[i][i]=l&1;
		while(l--) scanf("%d",&x),a[i][x]=1;
	}
	for(int i=1,l;i<=n;++i){
		for(l=i;l<=n&&!a[l][i];++l) ;
		if(l<=n){
			if(l^i) swap(a[i],a[l]);
			for(l=1;l<=n;++l) if(l!=i&&a[l][i]) a[l]^=a[i];
		}
	}
	for(int i=n;i;--i) if(a[i][i]&a[i][n+1]) b[++m]=i;
	printf("%d\n",m);
	while(m) printf("%d ",b[m--]);
	return 0;
}
```

---

## 作者：oscar (赞：7)

【POI补全计划#13 POI2005 DWA】

首先照例吐槽翻译

题目的意思是将一张无向图的点分成两个集合，去掉所有跨越集合的边，使得尽量多的点度数为偶数，输出分到其中一个集合中的所有点，有SPJ

题面里的“允许一小部分人没有参加派对”和“并且尽量使一个居民在派对上的朋友数更多”都是骗人的

还是要仔细读英文题面


以下是题解


-----------------------------分割线-----------------------------


首先随便手画几个图

```plain
(1)---(2)
 | \   |
 |  \  |
 |   \ |
(3)---(4)
```
之类的

手玩发现所有（画出来的）图都存在一种分割方案使得所有点剩余度数都为偶数（大胆猜想，不需证明）

然后考虑怎么输出方案

记第i个点度数为deg[i]，与第i个点有边相连的点构成的集合为adj[i]，某些数的异或和为XOR{条件}{内容}

记x[i]为i所属集合（0或1），按如下方式列方程

若deg[i]为偶数，则(XOR{j属于adj[i]}{x[j]}) == 0，即与i相邻的节点有偶数个在集合1中（这个公式可以对i分情况讨论得到）

否则deg[i]为奇数，则(XOR{j属于adj[i]}{x[j]}) xor x[i] == 1，即i节点和与i相邻的节点有奇数个在集合1中


这样就构造出来了n个未知数和n个方程


高斯消元搞一下就可以把方程解出来，然后输出所有x[i]==1的i就解决了

注意方程有多解，需要自己思考细节


贴代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int deg[233],mat[233][233],val[233];
int main()
{
    int n,tmp;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",& /*  这里有个luogu的bug，如果去掉这段注释的话代码会变为一个符号(°)  */ deg[i]);
        for(int j=1;j<=deg[i];j++)
        {
            scanf("%d",&tmp);
            mat[i][tmp]=1;
        }
        if(deg[i]&1)mat[i][i]=val[i]=1;
    }
    for(int i=1;i<=n;i++)
    {
        int sw=0;
        for(int j=i;j<=n;j++)
        {
            if(mat[j][i]==1)
            {
                sw=j;
                break;
            }
        }
        if(sw)
        {
            for(int j=i;j<=n;j++)
            {
                swap(mat[i][j],mat[sw][j]);
            }
            swap(val[i],val[sw]);
        }
        for(int j=i+1;j<=n;j++)
        {
            if(mat[j][i]==0)continue;
            for(int k=i;k<=n;k++)
            {
                mat[j][k]^=mat[i][k];
            }
            val[j]^=val[i];
        }
    }
    mat[n][n]=1;
    for(int i=n-1;i>=1;i--)
    {
        for(int j=i+1;j<=n;j++)
        {
            if(mat[i][j])
            {
                for(int k=j;k<=n;k++)
                {
                    mat[i][k]^=mat[j][k];
                }
                val[i]^=val[j];
            }
        }
        mat[i][i]=1;
    }
    int sum=0;
    for(int i=1;i<=n;i++)if(val[i])sum++;
    printf("%d\n",sum);
    for(int i=1;i<=n;i++)if(val[i])printf("%d ",i);
    return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

看到 $N \le 200$ 的数据范围，考虑高斯消元。

设 $x_i$ 为第 $i$ 个人在哪个组，则问题条件可以变为

$$\bigoplus \limits_{(i,j) \in E} (x_i \operatorname{xor} x_j \operatorname{xor} 1) =0$$。

即与 $i$ 所属组别相同的 $j$ 有偶数个。

这样就有了 $n$ 个异或方程了，高斯消元解之即可。

时间复杂度 $O(\frac{n^3}{\omega})$。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn=200;

bitset<maxn+5> bit[maxn+5];
bool b[maxn+5];
int n;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int l;
		cin>>l;
		for(int j=1;j<=l;j++){
			int x;
			cin>>x;
			bit[i][x]=1;
		}
		if(l&1){
			bit[i][i]=1;
			b[i]=1;
		}
	}
	for(int i=1;i<=n;i++){
		label:if(bit[i][i]==1){
			for(int j=1;j<=n;j++){
				if(j==i){
					continue;
				}
				if(bit[j][i]){
					bit[j]^=bit[i];
					b[j]^=b[i];
				}
			}
		}
		else{
			for(int j=1;j<=n;j++){
				if(bit[j][i]==0){
					continue;
				}
				for(int k=1;k<i;k++){
					if(bit[j][k]){
						goto label2;
					}
				}
				swap(bit[i],bit[j]);
				swap(b[i],b[j]);
				goto label;
				label2:;
			}
		}
	}
	vector<int> ans;
	for(int i=1;i<=n;i++){
		if(b[i]){
			ans.push_back(i);
		}
	}
	cout<<ans.size()<<"\n";
	for(auto i:ans){
		cout<<i<<" ";
	}
}
```

---

## 作者：Purslane (赞：0)

# Solution

对于每个居民定义状态 $x_i$，如果它被分到了第一个派对则 $x_i=0$，否则 $x_i=1$。

用 $x_{u} \oplus x_v$ 刻画 $u$ 和 $v$ 是否在同一个派对中。如果要每个人都被选中，需要满足

$$
\bigoplus_{(u,v) \in G} (x_u \oplus x_v) = \deg_u \bmod 2
$$

这个异或方程必定有解。选中的任意多个方程，如果左边异或能把所有元都消去，右边还有 $1$，则有奇数个“奇度数”的点。每个奇度数的点要选奇数个邻居在集合中，偶度数点要选偶数个邻居在集合中，这会导致集合的导出子图的总度数为奇数，显然是不可能的。

随便高斯消元解一个就行了，复杂度 $O(\dfrac{n^3}{w})$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=200+10;
int n,x[MAXN];
bitset<MAXN> st[MAXN]; 
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) {
		int c;
		cin>>c;
		ffor(j,1,c) {
			int k;
			cin>>k;
			st[i][k]=1;
		}
		st[i][i]=c&1,st[i][n+1]=c&1;
	}
	int tpos=1;
	ffor(i,1,n) {
		if(!st[tpos][i]) {
			ffor(j,tpos+1,n) if(st[j][i]) {
				swap(st[tpos],st[j]);
				break ;
			}
		}
		ffor(j,tpos+1,n) if(st[j][i]) st[j]^=st[tpos];
		if(st[tpos][i]) tpos++;
	}
	roff(i,n,1) if(st[i].count()) {
		int fst=-1,tmp=st[i][n+1];
		ffor(j,1,n) if(st[i][j]) {
			if(fst==-1) fst=j;
			else tmp^=x[j];	
		}
		x[fst]=tmp;
	}
	int sum=0;
	ffor(i,1,n) sum+=x[i];
	cout<<sum<<'\n';
	ffor(i,1,n) if(x[i]) cout<<i<<' ';
	return 0;
}
```

---

## 作者：JustPureH2O (赞：0)

[更好的阅读体验](https://justpureh2o.cn/articles/3429)

题目地址：[P3429](https://www.luogu.com.cn/problem/P3429)

> 拜占庭国王要举办两个大派对，并且希望邀请更多的居民。
>
> 国王从他的丰富经验里知道，如果一个居民在派对上能遇到偶数个的朋友，那他会非常高兴。因此，他要求你邀请国家的居民去两个派对，而使尽可能多的人在他们的聚会上有偶数个的朋友。认识是一种对称关系，如 $A$ 认识 $B$，那么 $B$ 也认识 $A$。
>
> 输出第一行是一个整数 $M$，是前往第一个排队的人数。第二行 $M$ 个整数，是去第一个派对的居民编号，其余的居民前往第二个派对。如果有多种答案，你只需要输出一个。

建方程组的思路和 [P6126 始祖鸟](https://justpureh2o.cn/articles/9850/) 相同。分朋友数的奇偶性讨论，如果朋友数是偶数，那么只要 $A,B$ 任意一处出现偶数个朋友，另一处就一定也会出现偶数个朋友，那么这个人去哪里都可以；如果朋友数是奇数，且在 $A$ 地出现奇数个朋友，那么 $B$ 地就一定会有偶数个朋友，他只能去 $B$ 地，反之亦然。

如果第 $i$ 个人去 $A$ 地，那么令 $x_i=1$，否则令 $x_i=0$。对于有偶数个朋友的人，只要他的朋友里存在偶数个 ${1}$ 和偶数个 ${0}$ 即可，不难发现，这些朋友的代表值异或起来是等于 ${0}$ 的；相对地，对于有奇数个朋友的人，他只能去偶数的那一方，此时如果算上这个人，就会出现偶数个 ${0/1}$ 和奇数个 ${1/0}$，全部异或的结果是 ${1}$。然后就可以列方程组求解了。

```cpp
#include <bits/stdc++.h>
#define N 210
using namespace std;

bitset<N> matrix[N];
bitset<N> ans;
int n;

void out() {
    cerr << "-----------------" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cerr << setw(5) << matrix[i][j];
        }
        cerr << endl;
    }
    cerr << "-----------------" << endl;
}

int gauss() {
    int rank = 0;
    for (int c = 1, r = 1; c <= n; c++) {
        int t = r;
        for (int i = r; i <= n; i++) {
            if (matrix[i].test(c)) {
                t = i;
                break;
            }
        }
        if (!matrix[t].test(c)) continue;
        if (t ^ r) swap(matrix[r], matrix[t]);

        for (int i = 1; i <= n; i++) {
            if (matrix[i].test(c) && i ^ r) {
                matrix[i] ^= matrix[r];
            }
        }
        r++;
        rank++;
    }
    if (rank < n) {
        for (int i = rank + 1; i <= n; i++) {
            if (matrix[i].test(n + 1)) return 0;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n + 1; j++) {
                if (matrix[i].test(j)) {
                    ans[j] = matrix[i][n + 1];
                    break;
                }
            }
        }
        return 1;
    }
    for (int i = 1; i <= n; i++) ans[i] = matrix[i][n + 1];
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        if (k & 1) matrix[i].flip(i);
        matrix[i][n + 1] = k & 1;
        while (k--) {
            int x;
            cin >> x;
            matrix[i].flip(x);
        }
    }
    int res = gauss();
    if (res) {
        cout << ans.count() << endl;
        for (int i = 1; i <= n; i++) {
            if (ans.test(i)) cout << i << ' ';
        }
    } else cout << "Impossible" << endl;
    return 0;
}
```

$\texttt{The End}$

---

## 作者：cmk666 (赞：0)

[题目传送门](/problem/P3429) | [双倍经验](/problem/P6126)

题目大意：给出一个有向图，把点分成两部分，使「每个点的出边指向的，且与它同一部分的点」的数量为偶数。给出一种方案。

看到偶数，考虑异或。下文中 $\oplus$ 代表异或运算。

设 $a_{i}$ 表示 $i$ 的出边所指向的点构成的序列，$x_i$ 表示 $i$ 号点在哪个部分（$0$ 或 $1$）。

根据出度 $d_i$ 的奇偶性进行分类讨论：

- 若 $d_i$ 为偶数，那么无论如何，在两个部分的点都应当是偶数，异或和为 $0$，因此有 $x_{a_{i,1}}\oplus x_{a_{i,2}}\oplus\cdots\oplus x_{a_{i,\lvert a\rvert}}=0$；
- 若 $d_i$ 为奇数，我们假设加入一条 $i\to i$ 的自环，则在两个部分的点都应当是奇数，异或和为 $1$，那么有 $x_{a_{i,1}}\oplus x_{a_{i,2}}\oplus\cdots\oplus x_{a_{i,\lvert a\rvert}}\oplus x_i=1$。

这样就可以列出 $n$ 条异或方程。高斯消元即可。

用 bitset 进行优化，时间复杂度 $O\left(\dfrac {n^3}\omega\right)$。核心代码如下：
```cpp
int n, m, x, cnt; bitset < 2009 > a[2009]; bool ans[2009], f;
inline void calc()  // 高斯消元
{
	For(k, 1, n)
	{
		f = false;
		For(i, k, n) if ( a[i][k] ) { swap(a[i], a[k]), f = true; break; }
		if ( f ) For(i, 1, n) if ( a[i][k] && k != i ) a[i] ^= a[k];
	}
	Fol(i, n, 1)
		if ( a[i][i] ) cnt += ans[i] = a[i][n + 1];
		else if ( a[i][n + 1] ) puts("Impossible"), exit(0);
}
int main()
{
	read(n);
	For(i, 1, n)
	{
		read(m); if ( m & 1 ) a[i][i] = a[i][n + 1] = true;
		For(j, 1, m) read(x), a[i][x] = true;
	}
	calc(), printf("%d\n", cnt);
	For(i, 1, n) if ( ans[i] ) printf("%d%c", i, --cnt ? ' ' : '\n');
	return 0;
}
```

---

