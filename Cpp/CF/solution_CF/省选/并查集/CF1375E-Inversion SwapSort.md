# Inversion SwapSort

## 题目描述

Madeline has an array $ a $ of $ n $ integers. A pair $ (u,       v) $ of integers forms an inversion in $ a $ if:

- $ 1 \le u < v \le n $ .
- $ a_u > a_v $ .

Madeline recently found a magical paper, which allows her to write two indices $ u $ and $ v $ and swap the values $ a_u $ and $ a_v $ . Being bored, she decided to write a list of pairs $ (u_i, v_i) $ with the following conditions:

- all the pairs in the list are distinct and form an inversion in $ a $ .
- all the pairs that form an inversion in $ a $ are in the list.
- Starting from the given array, if you swap the values at indices $ u_1 $ and $ v_1 $ , then the values at indices $ u_2 $ and $ v_2 $ and so on, then after all pairs are processed, the array $ a $ will be sorted in non-decreasing order.

Construct such a list or determine that no such list exists. If there are multiple possible answers, you may find any of them.

## 说明/提示

In the first sample test case the array will change in this order $ [3,1,2] \rightarrow [2,1,3] \rightarrow [1,2,3] $ .

In the second sample test case it will be $ [1,8,1,6]       \rightarrow [1,6,1,8] \rightarrow [1,1,6,8] $ .

In the third sample test case the array is already sorted.

## 样例 #1

### 输入

```
3
3 1 2```

### 输出

```
2
1 3
1 2```

## 样例 #2

### 输入

```
4
1 8 1 6```

### 输出

```
2
2 4
2 3```

## 样例 #3

### 输入

```
5
1 1 1 2 2```

### 输出

```
0```

# 题解

## 作者：duyi (赞：19)

# 进来看看吧↓


[更好的阅读体验](https://www.cnblogs.com/dysyn1314/p/13246526.html)

[题目链接](https://codeforces.com/contest/1375/problem/E)

考虑$a$是一个排列时怎么做。

我们设$\text{pos}[v]$表示$v$这个数在$a$里出现的位置。也就是$\text{pos}[a[i]]=i$。

从边界入手，我们先尝试把$n$放到排列的最后一个位置，然后转化为规模减$1$的子问题。具体来说，假设一波操作后，我们得到的排列为$b$，则$b$需要满足如下条件：

- $b[n]=n$。
- $\forall 1\leq i,j<n$，如果$a[i]<a[j]$，则$b[i]<b[j]$。
- $\forall1\leq i,j<n$，如果$a[i]>a[j]$，则$b[i]>b[j]$。

也就是说，要保证前面的数的**相对大小关系不变**，这样才能转化为一个等价的子问题。

我们怎么做呢？可以依次操作：$(\text{pos}[a[n]+1],n)$, $(\text{pos}[a[n]+2],n)$, $(\text{pos}[a[n]+3],n)$ ,......, $(\text{pos}[n],n)$。容易发现，这样一轮操作完成后，首先，$n$被放到了最后。同时，前面所有大于$a[n]$的数，相当于集体减$1$，显然前面所有数的相对大小关系不变。并且，我们恰好用掉了所有包含（位置）$n$的逆序对。所以剩下的是一个规模减$1$的子问题，继续做，直到$n=1$即可。

于是我们就解决了排列的情况。相当于我们用构造的方法证明了，$a$是一个排列时，一定有解。

再考虑不是排列的时候。对于两个相等的数$a[i]=a[j]$ ($i<j$)，我们强行令$a[i]<a[j]$，也就是以数值为第一关键字，位置为第二关键字，强行转成一个排列。发现转成排列后，序列里的逆序对和原来是一样的，所以直接按排列求解即可。

时间复杂度$O(n^2)$。

参考代码：

```cpp
//problem:CF1375E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int MAXN=1000;
int n,a[MAXN+5],vals[MAXN+5],cnt_val,p[MAXN+5],pos[MAXN+5];
vector<pii>ans;
void work(int p1,int p2){
	assert(pos[a[p1]]==p1);assert(pos[a[p2]]==p2);
	pos[a[p1]]=p2;
	pos[a[p2]]=p1;
	swap(a[p1],a[p2]);
	ans.pb(mk(p1,p2));
}
int main() {
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i],vals[++cnt_val]=a[i];
	sort(vals+1,vals+cnt_val+1);
	cnt_val=unique(vals+1,vals+cnt_val+1)-(vals+1);
	int x=0;
	for(int v=1;v<=cnt_val;++v){
		for(int i=1;i<=n;++i)
			if(a[i]==vals[v])
				p[i]=++x;
	}
	for(int i=1;i<=n;++i)a[i]=p[i];
	assert(x==n);
	//于是a变成了一个排列
	for(int i=1;i<=n;++i)pos[a[i]]=i;
	for(int i=n;i>=1;--i){
		for(int j=a[i]+1;j<=i;++j){
			work(pos[j],i);
		}
	}
	cout<<SZ(ans)<<endl;
	for(int i=0;i<SZ(ans);++i)cout<<ans[i].fi<<" "<<ans[i].se<<endl;
	return 0;
}
```


---

## 作者：George1123 (赞：10)

[$\Huge\color{orange}{\tt Come~to~cnblogs.}$](https://www.cnblogs.com/Wendigo/p/13245888.html)

---
> [CF1375E Inversion SwapSort](https://www.luogu.com.cn/problem/CF1375E)

> 给定长度为 $n$ 的序列 $a_i$，求一种将每个**逆序对**下标 $(u,v)$ 的排序，使依次交换每个 $(a_u,a_v)$ 后，$a_i$ 不减。

>  数据范围：$1\le n\le 1000$，$1\le a_i\le 10^9$。

---
很明显我的脑子被瘟化课搞残了，这整场的思维题，做出三道就脑子爆出弹簧了。于是只做出 $3$ 题，扣了 $95$ 分。

于是我奋发图强，决定写这篇题解，并全面改名为 $\tt CF$ 账号的名字 $\tt George1123$。废话不多说。

---
这题的 $a_i$ 不是互不相同的，但是为了简化问题，就当它是一个排列。

因为最后 $a_i$ 不减，所以**最终每个下标 要放 现在哪个下标的数 是固定的**，设最终 $i$ 处要放现在的 $a_{b_i}$。

如 $n=5$，$a_i$：``5 3 4 1 2``，$b_i$：``4 5 2 3 1``。

交换了 $a_{b_u}$ 和 $a_{b_v}$ 后，$b_u$ 和 $b_v$ 交换。当 $a_i$ 有序时，$b_i$ 也有序；$b_i$ 有序时，$a_i$ 也有序。

对于 $a_i$ 中的逆序对 $(b_u,b_v)$，

因为 $b_u<b_v$ 且 $a_{b_u}>a_{b_v}$，所以 $b_v>b_u$ 且 $v<u$。

考虑对 $b_i$ 做冒泡排序，所以 $b_i>b_{i+1}$ 的 $(b_i,b_{i+1})$ 会被交换。

因为最终 $b_i$ 会有序，所以每个 $b_v>b_u$ 且 $v<u$ 的 $(b_u,b_v)$ 都会被交换，$a_i$ 会有序。

**把每个 $b_i>b_{i+1}$ 的 $(b_{i+1},b_i)$ 记录下来就是答案。**

同理，在 $a_i$ 互有相同时，若有 $a_{b_u}=a_{b_v}(u<v)$，令 $b_u<b_v$ 可以防止答案中出现非逆序对。

---
- **代码**

```cpp
//Main
int main(){
	int n; cin>>n;
	vector<int> a(n),o(n);
	for(int i=0;i<n;i++) cin>>a[i];
	iota(b(o),e(o),0);
	sort(b(o),e(o),[&](int p,int q){
	return a[p]==a[q]?p<q:a[p]<a[q];});
	vector<pair<int,int>> ans;
	for(int t=0;t<n;t++)
		for(int i=0;i<n-1;i++)
			if(o[i]>o[i+1]) ans.pb(mp(o[i+1],o[i])),swap(o[i],o[i+1]);
	cout<<sz(ans)<<'\n';
	for(auto p:ans) cout<<p.x+1<<' '<<p.y+1<<'\n';	
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：Booksnow (赞：8)

# 构造

## 题目大意

给定长度为 $n$ 的数列 $a_1,a_2,……a_n$ ，找到其所有逆序对的一个排列 $(u_i,v_i)$ ，使得依次交换 $u_1$ 和 $v_1$ 位置上的数、 $u_2$ 和 $v_2$ 位置上的数、 $……$ 最后得到的数列**不减**。

## 分析

经过一定的思考我们能够发现，本题的过程类似于**冒泡排序**的过程，最后的目的是将其变成一个**单调不减**数列。

那么，我们如何使用冒泡排序将其解决呢？

我们发现，冒泡排序的每一次操作是交换两个相邻位置的值，很明显本题可以交换的数有可能是非相邻的，所以我们需要对原数列进行一定的操作。

如何操作才能使：

**交换两个位置上的数 $\iff$ 交换相邻的两个值**

我们发现，一个排列的逆排列是可以做到的。

因为对于一个长度为 $n$ 排列 $a[i]$ (满足 $a[i]\in[1,n]$ 且没有重复元素)，他的逆排列的定义是 $b[a[i]]=i$，深入解读他的意思其实是 $a[i]$ 在原排列中处于的位置，且我们发现若两个元素组成一组逆序对，在他的逆排列中他们值的大小**依然相反**，所以我们发现：

**原问题 $\iff$ 通过冒泡排序将 $b[i]$ 排序为 $1,2,3,4,……,n$**

至于交换路径我们只需要把我们交换的值记录下来就可以了。

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10,Time=1e6;
struct node{ int val,num,New; }a[N];
int n;
int b[N];
int tot,ansl[Time],ansr[Time];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline bool cmp1(node x,node y)
{
	if(x.val==y.val) return x.num<y.num;
	else return x.val<y.val;
}
inline bool cmp2(node x,node y) { return x.num<y.num; }
inline void initial() //离散化 
{
	sort(a+1,a+n+1,cmp1);
	for(register int i=1;i<=n;i++) a[i].New=i;
	sort(a+1,a+n+1,cmp2);
}
int main()
{
	n=read();
	for(register int i=1;i<=n;i++) a[i].val=read(),a[i].num=i;
	initial(); //离散化预处理 
	for(register int i=1;i<=n;i++) b[a[i].New]=i;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n-i;j++){
			if(b[j]>b[j+1]){
				int temp=b[j];
				b[j]=b[j+1],b[j+1]=temp;
				ansl[++tot]=b[j],ansr[tot]=b[j+1];
			}
		}
	}
	printf("%d\n",tot);
	for(register int i=1;i<=tot;i++) printf("%d %d\n",ansl[i],ansr[i]);
	return 0;
}
```

---

## 作者：SoyTony (赞：5)

前排提示：建议手玩理解。

先来考虑一个弱化版的问题，如果 $a$ 是一个**排列**该怎么做。

自然想到把逆序对连边，我们希望当一个数到达其应当到达的位置时，这个位置的所有边已经全部交换过，那么相当于每次把最后一位删去。

我们需要满足什么要求把这些边都走完？

要求即为之前有逆序对的位置现在仍然有逆序对，也就是相对的排名不变。满足这个要求非常简单，只需要我们按照交换位置上的数升序排序。

简单理解一下，假设现在倒序枚举到位置 $i$，$i$ 上的数为 $j$，那么 $[j+1,i]$ 所在的位置都对 $i$ 有连边，一次移动，那么 $j$ 去到了 $j+1$，$j+1$ 由 $j$ 过渡到 $j+2$，以此类推，满足了我们的要求，而 $i$ 最终也去到了 $i$ 这个位置。

以下建议结合数据 $\{3,4,3,1,2\}$ 理解。

那么如果不是排列，就会出现“原来位置上是逆序对，而现在的数位置相等”的情况，就要求先换到原来数更小的位置。

例如上面数据在把 $4$ 归位之后，得到 $\{2,3,3,1,4\}$，此时交换过 $2$ 后，先交换哪个 $3$ 实际上决定了 $2$ 将会去到那里，显然我们想要去到一个原来位置上数小的以满足逆序对要求，也就是选择 $(3,4)$。

最后就是题目要求不下降，因此默认的一个关键字就是下标，而当我们遇到原来和现在位置上数都相等的情况，就优先放到靠前的位置上去。

总结一下：排列比较好理解，序列和排列最大区别在于重复，实际上多个重复的怎么交换最重要的是第一个换谁，这决定了上一个较小的数去到哪里，我们希望去到一个合法的位置，若可以去到原来位置上数更小的就会优先选这个，反之选更靠前的位置。

对一个位置的全部交换的本质就是把当前要放到这里的数删去，剩下的数顺位移动到相应的位置。

---

## 作者：陈刀仔 (赞：5)

冒泡排序有一个与逆序对相关的性质，提出序列中**逆序数值对**，那么在冒泡排序的过程中，会交换的**数值对**，正好就是**原数组逆序数值对的集合**。

这就直接将这个单纯利用逆序对的排序与冒泡排序联系在一起了，但是你固定的是数值，并不能保证交换的始终是那几种**逆序下标对**。

为了保证下标对相同，我们考虑选择下标。但是如果考虑下标，一次交换后又很可能对其它的逆序下标对产生了影响。

**我们需要既考虑逆序下标对，又考虑逆序数值对。**

有一个经典套路，构造一个映射数组 $b[i]$ 表示 **在位置 $i$ 上 最终应该放置当前位置是 $b[i]$ 的数。** 

这个数组有一些性质：

- 交换 $(a[b[u]],a[b[v]])$ ，则 $(b_u,b_v)$ 也会交换。
- $u<v$ 且 $b[u]>b[v]$ 必然对应当前一个逆序数值对 $(a[b[u]],a[b[v]])$ 。
- 若$u<v$ ，则 $a[b[u]]<a[b[v]]$ 。

**不断交换当前的逆序对，一定最终会使得数组有序。**

冒泡排序一定会经过所有的逆序对，那么我们对 $b$ 进行冒泡排序，$b$ 有序后，$a$ 也有序了，**这样数值对上有了保证**。

**而且每次交换相邻的 $(b[i],b[i+1])$ 不会影响到其它的逆序下标对，因为 $i$ 和 $i+1$ 中间没有其它数。**

我们只需要记录下来每次需要交换的 $(b[i],b[i+1])$ ，就是答案。

特判一下相等情况。



---

## 作者：kiritokazuto (赞：2)

# 排序

- 对于这个题，它真的很妙，我们可以先考虑一下(如果 $a$ 是排列)暴力怎么打。

- 考虑两个数，他们互为逆序对，如果交换它们两个，如何让影响降到最小?那就是在他俩交换之后，他俩本来能构成的逆序对数是不变的(除去他俩这一组)，那么我们可以举个例子。

$$ 5 \ 4 \ 2 \ 1 \ 3 $$

- 所以下标 $1$ 和 $2,3,4,5$ 构成逆序对，下标 $2$ 和下标 $3,4,5$ 构成逆序对，剩下的以此类推。我们可以按照前边的说法模拟一下，例如，如果交换 $4$ 和 $5$ 之后只有本来他俩所产生的逆序对消失了，对于后三个数，仍然保持着逆序对的关系。

- 具体实现可以用一个二维树状数组维护一下，如果一组逆序对满足关系，就记录下答案，更新一下当前位置的值，暴力跑下一个，直到用够 $tot$ 次，这里挂一些核心代码，然后我们可以输出一下方案，就可以发现它的交换是很有规律的。

```cpp
 while(num <= tot){
        pos = 0;
        fr(i, 1, tot){
            if(vis[i]) continue;
            x = from[i];
            y = to[i];
            q1 = query(x - 1,a[x] - 1);
            q2 = query(y - 1,a[x] - 1);
            q3 = query(x - 1,a[y] - 1);
            q4 = query(y - 1,a[y] - 1);
            if(q2 == q4 && q1 == q3 && a[x] - q1 - 1 == a[y] - q3 && a[x] - q2 - 1 == a[y] - q4){
                pos = i;
                break;
            }
        }
        vis[pos] = 1;
        ans[num][0] = x;
        ans[num][1] = y;
        update(x,a[x],-1);
        update(y,a[y],-1);
        update(x,a[y],1);
        update(y,a[x],1);
        swap(a[x],a[y]);
        num++;
    }
```

- 它是一直在交换值相差 $1$ 的逆序对，因为这样就可以保证逆序对除了少的这一个其它都不变，那么在我将我当前想放的数归位之后，其余数的相对排名是不变的。

- 仍然是上边的例子。

- 第一次交换 $4,5$。

$$4 \ 5 \ 2 \ 1 \ 3$$

- 第二次交换 $3,4$。

$$3 \ 5 \ 2 \ 1 \ 4$$

- 第三次交换 $2,3$。

$$2 \ 5 \ 3 \ 1 \ 4$$

- 第四次交换 $1,2$。

$$1 \ 5 \ 3 \ 2 \ 4$$

- 我们发现在将 $1$ 放回原位后，后四个数的相对排名未变，原来下标 $2$ 处是四个数中最大的数，现在仍是，下标 $5$ 处是四个数中次大的值，现在也是，其余以此类推。

- 那么我们可以大胆归纳出结论，我从最小的数开始，以此将他放回原位，因为其余 $n - 1$ 个数相对排名不变，我可以重复这个过程(因为我要将一个小数放回原来的位置，肯定是先将大数换回去，再将小数换回来)，所以，这个题就解决了。

- 当然，这个题的 $a$ 是个序列，可以重复，那我们只需要再加一个判断，对于相同的数字，我强制它从后向前选，因为这样我在将数换回去之后，这些相同的数字仍是有序的，只不过相当于是整体平移而已，如果从前向后选，显然会乱。
- 然后就可以打出我们超级短的代码了。

- 当然，我们有 $10^{3}$ 个数，会产生 $10^{6}$ 个逆序对，数组记得开够。

```cpp


#include <bits/stdc++.h>
#define LL long long
#define Re register int
#define LD double
#define mes(x, y) memset(x, y, sizeof(x))
#define cpt(x, y) memcpy(x, y, sizeof(x))
#define fuc(x, y) inline x y
#define fr(x, y, z)for(Re x = y; x <= z; x ++)
#define fp(x, y, z)for(Re x = y; x >= z; x --)
#define delfr(x, y, z)for(Re x = y; x < z; x ++)
#define delfp(x, y, z)for(Re x = y; x > z; x --)
#define frein(x) freopen(#x ".in", "r", stdin)
#define freout(x) freopen(#x ".out", "w", stdout)
#define ki putchar('\n')
#define fk putchar(' ')
#define WMX aiaiaiai~~
#define pr(x, y) pair<x, y>
#define mk(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define re(x) return x
#define sec second
#define fst first


using namespace std;
namespace kiritokazuto{
    auto read = [](){
        LL x = 0;
        int f = 1;
        char c;
        while (!isdigit(c = getchar())){ if (c == '-')f = -1; }
        do{ x = (x << 1) + (x << 3) + (c ^ 48); } while (isdigit(c = getchar()));
        return x * f;
    };
    template  <typename T> fuc(void, write)(T x){
        if (x < 0)putchar('-'), x = -x;
        if (x > 9)write(x / 10); putchar(x % 10 | '0');
    }
}

using namespace kiritokazuto;



const int maxn = 2000000;

const LL Inf = 0x7ffffffffffffff;
int n;
int a[maxn];
struct Node {
    int from, to;
    int val;
    friend bool operator < (Node A, Node B) {
        if(A.from != B.from)return A.from < B.from;
        if(A.val != B.val) return A.val > B.val;
        return A.to > B.to;
    }
}q[maxn];

int tot = 0;
signed main() {
    n = read();
    fr(i, 1, n)a[i] = read();
    fr(i, 1, n) {
        fr(j, i + 1, n) {
            if(a[i] > a[j]) {   
                q[++tot].from = i;
                q[tot].to = j;
                q[tot].val = a[j];
            }
        }

    }
    write(tot);
    ki;
    sort(q + 1, q + tot + 1);
    fr(i ,1 ,tot) {
        printf("%d %d\n", q[i].from, q[i].to);
    }

    re(0); 

}
```


---

## 作者：Melon_Musk (赞：2)

### [题目链接](https://www.luogu.com.cn/problem/CF1375E)

### 分析

让我们先简化一下，假设数列是一个排列，怎么做？

容易发现此时交换位置就相当于交换值（毕竟是个排列，这两东西是相等的），为了保证我这次移动的两个数不会导致某一个没移动过的逆序对消失，以至其不能移动，我们显然每次要交换两个相邻的逆序对。

那这个怎么做呢，模拟一下交换的顺序发现这就是一个[冒泡排序](https://baike.baidu.com/item/%E5%86%92%E6%B3%A1%E6%8E%92%E5%BA%8F/4602306?fr=aladdin)板子！

现在题目拓展到了一个平常的数列，要交换的只是位置，当然容易想到我们也只用交换值相邻的逆序对就好，但是会发现正着往下做的时候比较难动态维护我们的值的逆序对。

于是我们可以变换一下思路，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xz4yxgyv.png)

记下标为 $x$ 轴，数大小为 $y$ 轴。

我们找到 $x$ 轴每个点在 $y$ 轴上的投影。

![](https://cdn.luogu.com.cn/upload/image_hosting/39pgm03j.png)

然后把 $y$ 轴和 $x$ 轴交换一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/78tvdgff.png)

！！！此时我们就发现了，原本题目要求的交换位置变成了交换值了！

于是只需要转换完成然后再做一个冒泡即可！

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+7;
int read() 
{
	int res=0,f=1;
	char c=getchar();
	while(!isdigit(c) && c!='-') c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(isdigit(c)) res=(res<<1)+(res<<3)+c-48,c=getchar();
	return res*f;
}
struct node
{
    int v,id,nw;  //值，位置，和离散化的位置
}a[maxn];
struct Ans { int x,y; }ans[maxn];
int n,m;
int b[maxn];
bool cmp(node a,node b) { return a.v==b.v?a.id<b.id:a.v<b.v; }
bool cmp2(node a,node b) { return a.id<b.id;}
int main()
{
	n=read();
    for(int i=1;i<=n;i++) a[i]=(node){read(),i,0};
    sort(a+1,a+n+1,cmp);  //离散化
    for(int i=1;i<=n;i++) a[i].nw=i;
    sort(a+1,a+n+1,cmp2);
    for(int i=1;i<=n;i++) b[a[i].nw]=i;  //得出转换玩后的数组b
    for(int i=1;i<=n;i++)
        for(int j=1;j<n;j++)
            if(b[j]>b[j+1])
                swap(b[j],b[j+1]),
                ans[++m]=(Ans){b[j],b[j+1]};
    printf("%d\n",m);
    for(int i=1;i<=m;i++) printf("%d %d\n",ans[i].x,ans[i].y);
	return 0;
}
```


---

## 作者：Zhao_daodao (赞：1)

## [原题传送门](https://www.luogu.com.cn/problem/CF1375E)

## [CF 传送门](https://codeforces.com/contest/1375/problem/e)

# 题目描述
在有 $n$ 个元素的序列 $a$ 中，求一种包含 $a$ 中所有逆序对的排列，使得排列玩的数组 $p$ 单调不减。
# 题目分析
### 推样例
构造题当然先推样例。

样例：
```txt
1 4 3 2 6 1 5
```
通过观察发现一共有 8 组逆序对，分别是：$(4,3),(4,2),(3,2),(4,1),(3,1),(2,1),(6,1),(6,5)$。

可以按照逆序对的第二个数排序：$\left\{\begin{matrix} 
  3:(4,3)\\  
  2:(4,2),(3,2)\\
  1:(4,1),(3,1),(2,1),(6,1)\\
   5:(6,5)
\end{matrix}\right. $

交换方法：$(4,3),(4,2),(3,2),(6,1),(4,1),(3,1),(2,1),(6,5)$。
### 结论
不难发现，将每一个相同结尾的逆序对排序，依次交换即可将原数交换到原位。

证明：设逆序对结尾的数为 $i$，当前逆序对为 $(j,i)$，$a_j>a_i$。

因为是顺序排序，所以 $a_k\le a_{k+1}(\forall k\in \left[1,i\right) )$。

所以将 $(i,j)$ 互换，与下一个逆序对 $(j',i)$ 的形成不受影响，因为 $j'<j,a_{j'}<a_j$。

这样交换通过交换与 $i$ 的所有逆序对，$i$ 就回到了它的位置，使得当前 $a_1$ 至 $a_i$ 单调不减。

初始时，$a_1$ 单调不减，每一次操作后仍是单调不减，最后剩下的 $p$ 数组肯定单调不减。
### 方法
发现题目要求输出下标的改变，可以将 $a$ 数组转化为权值数组 $b$，此时 $a$ 的下标转化为 $b$ 的数量，用枚举直接改变 $b$ 的下表就对答案没有影响了。

注意：要对数组离散化，不然 $10^9$ 的空间会 $RE$。
### 实现
[code](https://codeforces.com/contest/1375/submission/213436482)

---

## 作者：sry_ (赞：1)

为啥现在假做法一直过题啊！

有一个不知道对不对的做法，考虑当前序列 $A$ 中若没有 $i$ 使得 $A_i> A_{i+1}$ 那么肯定 $A$ 是不严格单调递增的。

否则我们将 $i$ 与 $i+1$ 对应的原 $A$ 的下标翻转，最后倒叙输出即可。

正确性未知，但交了一发就过了？？？

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<queue>
#include<vector>
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using namespace std;
inline int read(){
	int f=1,ans=0; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return f*ans;
}
const int MAXN=1e3+11;
int N,A[MAXN],id[MAXN]; vector<pii> vec,Ans;
int main(){
	N=read(); for(int i=1;i<=N;i++) A[i]=read(),id[i]=i;
	for(int i=1;i<=N;i++) for(int j=i+1;j<=N;j++) if(A[i]>A[j]) vec.pb(mp(i,j));
	while(1){
		int ps=-1; for(int i=1;i<N;i++) if(A[i]>A[i+1]){ps=i;break;}
		if(ps==-1) break; Ans.pb(mp(id[ps],id[ps+1])); swap(A[ps],A[ps+1]); swap(id[ps],id[ps+1]);
	}
	printf("%ld\n",Ans.size()); for(int i=Ans.size()-1;i>=0;i--) printf("%d %d\n",Ans[i].fi,Ans[i].se);
	return 0;
	//for(auto v:Ans) printf("%d %d\n",v.fi,v.se);return 0;
}
```


---

## 作者：Clever_Jimmy (赞：1)

CF1375E 【Inversion SwapSort】

### 题意简述：

给定一个长度为 $n$ 的序列 $a$，求 $a$ 中的所有逆序对 $(i_1, j_1), (i_2, j_2), \cdots, (i_m, j_m)$ 的一个排列 $p$，

使得依次交换 $(a_{i_{p_1}}, a_{j_{p_1}}), (a_{i_{p_2}}, a_{j_{p_2}}), \cdots, (a_{i_{p_m}}, a_{j_{p_m}})$ 后序列单调不降。

$1 \le n \le 10^3$，$1 \le a_i \le 10^9$。

[题目链接](https://codeforces.ml/contest/1375/problem/E)

### 解题思路：

首先我们考虑对一个排列 $q$ 怎么处理，令 $\textrm{pos}[x] = i,\textrm{s.t. }a_i = x$。

我们可以每次先将最大的安排好，然后将次大的安排好……以此类推。

第 $i$ 轮操作我们尝试着把第 $i$ 大的元素（也就是 $i$）归位（也就是放到第 $i$ 个位置）。

此时我们已经处理完了$[i + 1, n]$，第 $i$ 个位置上的元素是 $q_i$，但本来这个地方应该放 $i$。

那么 $q_i + 1, q_i + 2, \cdots, i$ 和 $q_i$ 都构成逆序对，

显然，依次交换 $(\textrm{pos}[q_i + 1], i), (\textrm{pos}[q_i + 2], i), \cdots, (\textrm{pos}[i], i)$ 可以将 $i$ 归位。

而且我们交换的这些位置，都构成逆序对。

---

然后我们考虑存在 $i < j, a_i = a_j$ 的情况怎么转化为上面的排列。

我们强行规定 $i < j, a_i = a_j$ 时有 $a_i$ 排在 $a_j$ 前面，即 **按照值为第一关键字、数组下标为第二关键字** 将 $a$ 进行重新标号。

这样就将 $a$ 转化为了一个排列；容易看出，这样修改后，逆序对的个数并没有改变。

总的时间复杂度为 $O(n^2)$。

### 参考代码：

```cpp
#include <bits/stdc++.h>
#define LL long long

const int N = 1e3 + 5;

int n, cntAns, a[N], pos[N];

struct PAIR {
    int ff, ss;
    bool operator<(const PAIR &rhs) const {
        if(ff == rhs.ff)
            return ss < rhs.ss;
        return ff < rhs.ff;
    }
    PAIR(int _f = 0, int _s = 0) {
        ff = _f, ss = _s;
    }
} b[N], ans[N * N];

int32_t main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[i] = PAIR(a[i], i);
    }
    
    std::sort(b + 1, b + n + 1);
    for(int i = 1; i <= n; ++i)
        b[i].ff = b[i - 1].ff + 1;
    for(int i = 1; i <= n; ++i)
        a[b[i].ss] = b[i].ff;
    // turned into a permutation
    
    for(int i = 1; i <= n; ++i)
        pos[ a[i] ] = i;
    
    for(int i = n; i >= 1; --i) {
        for(int j = a[i] + 1; j <= i; ++j) {
            int p1 = pos[j];
            int p2 = i;
            
            pos[a[p1]] = p2;
            pos[a[p2]] = p1;
            
            std::swap(a[p1], a[p2]);
            ans[++cntAns] = PAIR(p1, p2);
        }
    }
    
    printf("%d\n", cntAns);
    for(int i = 1; i <= cntAns; ++i)
        printf("%d %d\n", ans[i].ff, ans[i].ss);
    return 0;
}
```

---

## 作者：Andrewzdm (赞：1)

**为了便于阅读，以下部分变量的下标用代码中数组的形式代替。**

题目本质上就是让我们将所有逆序对的下标 $(u, v)$ 进行一个排列，使得我们依次交换 $a_u$ 和 $a_v$ 后，$a$ 成为一个不下降序列。

首先我们发现，因为我们的题目需要的是逆序对的下标，所以只要我们保证我们没有更改原数组中的逆序对下标，我们可以任意修改所有数的值。

这样一来，我们就可以将任意数据转化为一个排列以简化问题。转化的具体方式可以看代码理解。接下来我们只需要考虑怎么将一个排列按照要求排序就可以了。

此题数据范围 $1 \le n \le 1000$，这意味着我们可以用 $O(n^2)$ 的时间复杂度通过本题。

仿效冒泡排序和选择排序的思想，通过一系列步骤，将区间最小值放到排序区间的左端，或将区间最大值放到排序区间的右端，然后对一个更小的区间重复相同的操作，最后达到使数组有序的目的。于是我们也考虑每次将区间最大值放到排序区间的最右端。

但是要想这么做，我们必须满足一些规则：  
设当前排列为 $a$，进行一次操作后的排列为 $p$，那么：
1. $p_n=n$
2. 对于任意的 $1 \le i,j \lt n$，$p_i$ 和 $p_j$ 的大小关系与 $a_i$ 和 $a_j$ 的大小关系相同

规则 $1$ 就是为了满足我们的目的，规则 $2$ 保证我们的操作满足题目所给的条件——我们交换的逆序对一定对应原序列的一个逆序对。

接下来这题又变成了一个构造题：构造一个算法使得我们满足上述规则并且恰好用完所有的原序列中的逆序对。

算法是这样的：  
设 $pos[i]$ 表示数 $i$ 所在的位置，我们依次交换 $(pos[a_n+1],n),(pos[a_n+2],n),(pos[a_n+3],n),\dots,(pos[n],n)$。（这里括号内的都是数组下标）

执行完一次该算法后，我们满足了规则 $1$，因为 $n$ 被成功放到了最后；我们满足了规则 $2$，因为我们把 $a[pos[a_n+k]](1 \le k \lt n-a_n)$ 全部减了 $1$，大小关系自然不变；我们还用完了原序列中所有第二下标为 $n$ 的逆序对。

反复重复这个操作即可。

emmm……好像并没有无解的情况。

时间复杂度 $O(n^2)$。
```cpp
#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn = 1005;
struct element
{
	int val;
	int idx;
} p[maxn];
int a[maxn], pos[maxn];
vector<pair<int, int> > res;

bool cmp(element x, element y)
{
	if(x.val != y.val)
		return x.val < y.val;
	return x.idx < y.idx;  //注意下标的先后顺序
}

int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> p[i].val;
		p[i].idx = i;
	}
	sort(p + 1, p + n + 1, cmp);//以数值和下标为关键字排序
	for(int i = 1; i <= n; i++)
		p[i].val = p[i - 1].val + 1;
	for(int i = 1; i <= n; i++)
		a[p[i].idx] = p[i].val;//成功转化成排列
	for(int i = 1; i <= n; i++)
		pos[a[i]] = i;
	for(int i = n; i >= 1; i--)
	{
		for(int j = 1; j <= i - a[i]; j++)
		{
			res.push_back(make_pair(pos[a[i] + j], i));
			a[pos[a[i] + j]]--;
		}
		for(int j = 0; j < i - a[i]; j++)
			pos[a[i] + j] = pos[a[i] + j + 1];
		pos[i] = i;
	}
	cout << res.size() << endl;
	for(pair<int, int> i : res)
		cout << i.first << ' ' << i.second << endl;
	return 0;
}
```

---

## 作者：Celtic (赞：0)

考虑按照值域从小到大枚举，每次都让这个值域的前缀排好序。考虑新加入一个 $i$，那么由于 $1,2,\dots,i-1$ 是排好序的，我们加入 $i$ 后需要到这个子序列的最后，而因为 $1,2,\dots,i-1$ 都 $<i$ 所以他是随意交换的，于是可以将 $i$ 和逆序对中最大的一个位置交换，这样 $i$ 存储的就是 $i-1$ 了，再将 $i$ 和第二大的位置交换，一直这样进行下去。全部交换完后就是有序的了。

```cpp
#include<bits/stdc++.h>
#define N 2001001
#define MAX 3505
using namespace std;
typedef long long ll;
typedef double db;
const ll mod=998244353,inf=1e18;
inline void read(ll &ret)
{
	ret=0;char c=getchar();bool pd=false;
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
	ret=pd?-ret:ret;
	return;
}
ll n,a[N],pos[N];
vector<pair<ll,ll> >ans;
ll sum[N];
map<ll,ll>mp;
ll b[N];
signed main()
{
	read(n);
	ll sum=0;
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		b[i]=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		ll res=0;
		for(int j=1;j<=n;j++)
			res+=b[j]<b[i];
		a[i]=res+(++mp[b[i]]);
		pos[a[i]]=i;
		for(int j=1;j<i;j++)
			sum+=a[j]>a[i];
	}
	printf("%lld\n",sum);
	for(int i=2;i<=n;i++) 
	{
		vector<ll>now;
		for(int j=1;j<i;j++)
		{
			if(pos[j]>pos[i])
				now.push_back(pos[j]);
		}
		sort(now.begin(),now.end());
		for(int j=(int)now.size()-1;j+1;j--)
			printf("%lld %lld\n",pos[i],now[j]);
	}
	exit(0);
}
```

---

## 作者：Alkaid_Star (赞：0)

### 题目大意

>给定一个长度为 $n$ 的序列 $a_1,\dots,a_n$，求出 $a$ 中所有逆序对位置 $(pos1_{1},pos2_1),\dots,(pos1_n,pos2_n)$ 的一个排列，使得按照这个排列依次交换位置后序列单调不降。
>
>$1 \le n \le 10^3$，$1 \le a_i \le 10^9$。

### 解题思路

发现题目中要交换的是位置，而逆序对是跟着值走，而不是位置走的。

所以考虑如果交换的不是原本逆序对的位置而是交换后当前逆序对所在位置怎么做。

我们发现类似于**冒泡排序**的做法，我们可以每次交换相邻两个逆序对。

这样做，前面部分内部的贡献以及后面部分内部的贡献肯定不会变，我们只需要考虑当前部分内部贡献，以及当前部分与前面后面的跨区间贡献。那么显然，内部的交换减少了一个逆序对，前面部分与当前这两个数的贡献，以及和后面部分和当前这两个数的贡献是不会改变的（因为这两个数在相对于前后两个部分的位置是没有变的），那么整个序列的逆序对数就减少了 $1$。

而我们每次都这样调整，每次可以减少一个原序列中的逆序对。而这样的操作又可以进行逆序对数量次。所以最后一定可以到达一个有序状态。

然后考虑交换的是原本逆序对位置的情况，我们发现我们令 $b_{a_i}=i$，这样转化出的序列 $b_1...b_n$ 就满足交换的是跟着值走的逆序对位置。而且我们发现原本序列中的逆序对需要满足 $i<j$ 且 $a_i>a_j$，在 $b$ 序列中，我们发现这样的一对 $(i,j)$ 的关系变成了 $i>j$ （因为 $a_i>a_j$）且 $b_i<b_j$（因为 $i<j$），仍然是一对逆序对。也就是说，原序列和转化后序列的逆序对是完全不变的。

然后我们发现我们上面的讨论都是基于 $a$ 数组是一个排列的（$a \to b$ 的转化需要用到这一点），而题目中给出的序列可能并不是一个排列，怎么办呢？

注意到原序列中可能出现值相同的情况，所以我们对于原序列中的一个数，值作为它的第一关键字，人为给予它一个标号作为第二关键字，再进行**离散化**，保证没有相同的值。离散化后再进行上面的操作就可以了。

### Code

```cpp
#include<bits/stdc++.h>
#define mp make_pair
using namespace std;

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)){ if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}
const int N=2005;

int n,p[N];
pair<int,int> a[N],b[N];
vector < pair<int,int> > ans;

int main(){
	//freopen("CF1375E.in","r",stdin);
	//freopen("CF1375E.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i) a[i]=mp(read(),i),b[i]=a[i];
	sort(b+1,b+n+1);
	for (int i=1;i<=n;++i)
		a[i].first=lower_bound(b+1,b+n+1,a[i])-b;
	// printf("a: "); for (int i=1;i<=n;++i) printf("%d ",a[i].first); printf("\n");
	for (int i=1;i<=n;++i) p[a[i].first]=i;
	// printf("p: "); for (int i=1;i<=n;++i) printf("%d ",p[i]); printf("\n");
	for (int i=1;i<=n;++i)
		for (int j=n;j>=2;--j)
			if (p[j]<p[j-1]){
				ans.push_back(mp(p[j],p[j-1]));
				swap(p[j],p[j-1]);
			}
	printf("%d\n",(signed)(ans.size()));
	for (auto it : ans)
		printf("%d %d\n",it.first,it.second);
	return 0;
}
```



---

## 作者：lgswdn_SA (赞：0)

首先题目中的数列可以转换为排列。我们按 $a$ 为第一关键字，$pos$ 为第二关键字然后离散化一下就可以得到一个排列。设 $q_{p_i}=i$。

我们考虑像 swap sort 一样，每次安置好最大的一位。假设我们现在正在处理第 $x$ 位，我们需要保证处理完后，前面 $[1,x]$ 的元素的相对大小仍然不变，这样才能保证之后可以通过交换逆序对来达成结果。有一种方法，就是按次序 swap $(q_{p_x+i},x))$，这样一轮操作下来，前面比 $p_x$ 大的数全部-1，然后 $p_x=x$。

很妙！!1

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=1e3+9;
typedef pair<int,int> pii;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,a[N],q[N];
pii b[N];

void swp(int x,int y) {
	q[a[x]]=y, q[a[y]]=x, swap(a[x],a[y]);
	printf("%d %d\n",x,y);
}

int main() {
	n=read();
	rep(i,1,n) a[i]=read(), b[i]=make_pair(a[i],i);
	sort(b+1,b+n+1);
	rep(i,1,n) a[b[i].second]=i, q[i]=b[i].second;
	int cnt=0;
	rep(i,1,n) rep(j,i+1,n) cnt+=(a[j]<a[i]);
	printf("%d\n",cnt);
	per(i,n,1) {
		rep(j,a[i]+1,i) swp(q[j],i);
	}
	return 0;
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1375E)

# 题解

一道十分巧妙的构造题。

我们考虑先将所有数离散化，然后，对于一个数 $i$，如果我们已经使得 $1\sim i-1$ 有序（位置不一定相邻），现在要将 $i$ 加入进去，维护这个序列有序，那么，我们的最终目的其实就是将 $i$ 放到最后的位置去

我们考虑将 $i$ 的位置 $pos$ 将 $i-1$ 交换，然后再将 $pos$ 与 $i-2$ 的位置交换...持续下去，直到 $i-k$ 的位置小于 $pos$ 停止

这样做可以使得序列合法，并且原序列中亦一定存在这样的逆序对，因为我们 $1\sim i-1$ 中，无论谁在 $pos$ 的后面，都一定是和 $pos$ 的原数 $i$ 存在逆序关系，而我们是从 $1$ 开始往大枚举，那么所有在 $i$ 后面的数（枚举保证是 $1\sim i-1$），都和 $i$ 存在逆序关系，所以这样的方案一定存在

换句话说，这道题根本没有无解，输出 `-1` 是没用的

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13343329.html
```



---

