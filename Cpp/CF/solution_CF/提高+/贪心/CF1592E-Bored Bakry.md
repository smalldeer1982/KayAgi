# Bored Bakry

## 题目描述

Bakry got bored of solving problems related to xor, so he asked you to solve this problem for him.

You are given an array $ a $ of $ n $ integers $ [a_1, a_2, \ldots, a_n] $ .

Let's call a subarray $ a_{l}, a_{l+1}, a_{l+2}, \ldots, a_r $ good if $ a_l \, \& \, a_{l+1} \, \& \, a_{l+2} \, \ldots \, \& \, a_r > a_l \oplus a_{l+1} \oplus a_{l+2} \ldots \oplus a_r $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) and $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Find the length of the longest good subarray of $ a $ , or determine that no such subarray exists.

## 说明/提示

In the first case, the answer is $ 2 $ , as the whole array is good: $ 5 \& 6 = 4 > 5 \oplus 6 = 3 $ .

In the third case, the answer is $ 4 $ , and one of the longest good subarrays is $ [a_2, a_3, a_4, a_5] $ : $ 1\& 3 \& 3 \&1 = 1 > 1\oplus 3 \oplus 3\oplus 1 = 0 $ .

## 样例 #1

### 输入

```
2
5 6```

### 输出

```
2```

## 样例 #2

### 输入

```
3
2 4 3```

### 输出

```
0```

## 样例 #3

### 输入

```
6
8 1 3 3 1 2```

### 输出

```
4```

# 题解

## 作者：Tony102 (赞：12)

## 题解
[My blog](https://tony102.com/archives/136/)

首先 $\&$ 出来要不是 $0$，那肯定是该区间所有数的二进制在那一位上全是 $1$。

其次还要满足 $\&$ 出来要大于异或和。那如果该区间长度为奇数，那么 $\&$ 和有可能与异或和相等。所以只有长度为偶数的子区间合法。

现在要做的事就是找到一个位满足这个条件：在某一个子区间上这一位全是 $1$。如果高位满足条件，那么低位都可以不考虑。

但是出现了一个问题，不一定 $\&$ 出来比异或和大。强制规定更高为的异或和为 $0$ ，这样在枚举到更高位时情况没有算漏。

## Code

非常精简

```cpp
for (int i = 19; ~i; -- i) {
    for (int j = 1; j <= n; ++ j) {
        And[j] = And[j - 1] + ((a[j] >> i) & 1), 
        Xor[j] ^= ((And[j] & 1) << i);
    }
    memset(pre, -1, sizeof(pre));
    pre[0] = 0;
    for (int j = 1; j <= n; ++ j) {
        if (pre[Xor[j]] == -1) pre[Xor[j]] = j;
        else {
            int k = pre[Xor[j]];
            if (And[j] - And[k] == j - k) ans = std::max(ans, j - k);
            else pre[Xor[j]] = j;
        }
    }
}
```

---

## 作者：walk_alone (赞：6)

（这好像是 CF 最近第二次出这种与起来大于异或的条件了）。

考虑什么情况下一个连续子段与起来才会严格大于异或——有一个二进制位，在该子段内二进制表示全部为 $1$，并且长度为偶数；此外，比它高的二进制位全部要打平（即与起来的结果和异或起来的相同，均为 $0$）。

考虑到 $n \leq 1\times 10^6$，因而只能 $O(n \log N)$ 的复杂度——枚举每一个二进制位，然后线性的扫一遍得到答案。

对于某一个特定的二进制位 $d$ （以下 $0,1$ 的讨论均发生在这一个二进制位上），由于需要这一段上这一个二进制位全为 $1$，因而合法段不会越过有 $0$ 的，所以考虑在两个二进制为 $0$ 的数之间统计答案。

接下来考虑其他的性质——高位全部打平，这一位上异或值为 $0$。区间求异或值一个常用方法就是前缀和。用一个 map 存储**比 $d$ 高的二进制位**上的异或前缀和——$map[x]=id$，$x$ 为异或前缀和而 $id$ 为**第一次出现这个前缀和的下标**。注意此处的前缀和是从上一个二进制为 $0$ 的数开始统计的。那么这样就可以保证尽可能的长了。

可能会有疑问说这样没法保证奇数。但是注意到一个性质——这一段全是 $1$，因而想要异或值是 $0$ 长度只能是偶数。因而不用区分奇偶性，直接用异或的性质解决。

```cpp
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
const int N = 1000000;
int a[N + 5];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n;i++)
        scanf("%d", &a[i]);
    map<int, int> pre;
    int ans = 0;
    for (int d = 0; d <= 20;d++)
    {
        pre.clear();
        int sum = 0;
        pre[0] = 1;//注意初始条件
        for (int i = 1; i <= n;i++)
        {
            if ((a[i] & (1 << d)) == 0)
            {
                sum = 0;
                pre.clear();
                pre[0] = i + 1;
                continue;
            }
            sum ^= (a[i] >> d);
            if(pre.count(sum)==0)
                pre[sum] = i + 1;//记录的是下一位
            else
                ans = max(ans, i - pre[sum] + 1);
        }
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：Alex_Wei (赞：4)

> ### 1592E. [Bored Bakry](https://www.luogu.com.cn/problem/CF1592E)
>
> 摘自 [CF 比赛记录](https://www.cnblogs.com/alex-wei/p/codeforces_compete_upsolve_virtual_participation_record.html)（密码可以私我 qwq）。

子区间 $\rm and>xor$，则其最高位一定相同且长度为偶数：因为长度为奇数时对于剩下来的所有位 $d$，若子区间第 $d$ 位全为 $1$ 则异或和也为 $1$，不优；而若至少有一个位置第 $d$ 位为 $0$ 则该位按位与为 $0$，不优。

上述结论是充要条件，因为 $\rm xor$ 最高位为 $0$ 而 $\rm and$ 最高位为 $1$ 故无论低位是什么都符合条件。所以直接枚举最高位就行。时间复杂度 $\mathcal{O}(n\log a_i)$。

```cpp
const int N=1e6+5;
const int inf=0x3f3f3f3f;

int n,ans,a[N],pr[N],buc[2][1<<20];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)a[i]=read(),pr[i]=a[i]^pr[i-1]; 
	for(int i=20;~i;i--){
		mem(buc,-1);
		for(int j=1,r=1;j<=n;r=j=r+1){
			if((a[j]>>i&1)==0)continue;
			while(r<n&&(a[r+1]>>i&1))r++;
			for(int k=j-1;k<=r;k++){
				int res=pr[k]>>i+1;
				if(buc[k&1][res]==-1)buc[k&1][res]=k;
				else ans=max(ans,k-buc[k&1][res]);
			} for(int k=j-1;k<=r;k++)buc[k&1][pr[k]>>i+1]=-1;
		} 
	} cout<<ans<<endl;
	return 0;
}
```

---

## 作者：_edge_ (赞：2)

给出一种 $O(n \log ^2 a_i)$ 的做法，常数很小，实测能过，不过需要一点点小卡常。

我们分析一下 $\&$ 的性质，发现他非常优美，如果一个 $r$ 为右端点，那么他往左边扫，这个 $\&$ 和肯定最多只有 $\log a_r$ 种不同的数。

然后我们先把异或和拆成异或前缀和。

下面的 $\oplus$ 是异或的意思。

我们大力先把这些连续段拿出来，然后问题变成了从左往右扫描，询问最靠左的 $sum_{l-1}$，使得 $sum_i \oplus sum_{l-1} \le A$，这里的 $A$ 是当前的 $\&$ 和。

由于是后缀，并且其需要最小，所以我们把 $i$ 后面的东西也算进去问题不大。

于是我们就可以从后往前做一个可持久化 trie，然后异或和那个东西就是一段后缀，在上面找到最小的点就可以了。

值得一提的是，这样需要一个剪枝，遇到 trie 子树内部的点最小值已经超过当前答案的时候可以直接返回。

下面代码删去了缺省源，有需要同学可以去 CF 上搜 fzx 的提交记录。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF=1e6+5;
const int INFN=21000005;
int res;
struct trie1{
    #define ls(x) lson[x]
    #define rs(x) rson[x]
    int lson[INFN],rson[INFN],sum[INFN],tot,rt[INF];
    int N(int x) {++tot;lson[tot]=lson[x];rson[tot]=rson[x];sum[tot]=sum[x];return tot;}
    void push_up(int id) {
        sum[id]=min(sum[ls(id)],sum[rs(id)]);
    }
    void add(int dep,int x,int y,int &id) {
        id=N(id);
        if (dep==-1) {sum[id]=min(sum[id],y);return ;}
        if ((x>>dep)&1) add(dep-1,x,y,rson[id]);
        else add(dep-1,x,y,lson[id]);
        push_up(id);
    }
    void query(int dep,int y,int z,int id) {
        if (!id) return ;
        if (res<=sum[id]) return ;
        if (dep==-1) {res=min(res,sum[id]);return ;}
        if ((z>>dep)&1) {
            if ((y>>dep)&1) {res=min(res,sum[rs(id)]);query(dep-1,y,z,ls(id));return ;}
            else {res=min(res,sum[ls(id)]);query(dep-1,y,z,rs(id));return ;}
        }
        else {
            if ((y>>dep)&1) {query(dep-1,y,z,rs(id));return ;}
            else {query(dep-1,y,z,ls(id));return ;}
        }
    }
}T1;
const int INFF=105;
int a[INF],n,pre[INFF],sum2[INF],p[INFF],p1[INFF],p2[INFF];
signed main()
{
    // freopen("data.in","r",stdin);
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    T1.sum[0]=1e9;
    sum2[1]=a[1];
    for (int i=2;i<=n;i++) 
        sum2[i]=sum2[i-1]^a[i];
    for (int i=n;i;i--) {
        T1.rt[i]=T1.rt[i+1];
        T1.add(19,sum2[i-1],i,T1.rt[i]);
    }
    int ans=0;
    memset(pre,255,sizeof pre);
    for (int i=1;i<=n;i++) {
        for (int j=0;j<21;j++) {
            if ((a[i]>>j)&1) ;
            else pre[j]=i;
        }
        p[0]=0;
        for (int j=0;j<21;j++) 
            if (pre[j]!=-1 && (a[i]>>j)&1) p[++p[0]]=pre[j],p2[p[0]]=j;
        for (int j=1;j<=p[0];j++) p1[j]=j;
        sort(p1+1,p1+1+p[0],[](int x,int y){return p[x]>p[y];});
        int xx=a[i];
        for (int j=1;j<=p[0];j++) {
            if (xx<=0) continue;
            res=1e9;
            T1.query(19,sum2[i],xx-1,T1.rt[p[p1[j]]+1]);
            int kk=res;
            ans=max(ans,i-kk+1);
            xx^=(1<<p2[p1[j]]);
        }
        if (xx-1>=0) {
            res=1e9;
            T1.query(19,sum2[i],xx-1,T1.rt[1]);
            int kk=res;
            ans=max(ans,i-kk+1);
        }
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：luogubot (赞：2)

给定 $a_{1\cdots n}$，找到最长的区间 $[l,r]$ 满足 $\operatorname{and}_{i=l}^r a_i>\operatorname{xor}_{i=l}^r a_i$。

$1\leq n,a_i\leq 10^6$。

第一直觉是枚举某一位 and 起来大于 xor，即一个**长度为偶数**的区间在这一位全是 1，于是遇到的麻烦是难以保证更高位的 and 大于等于 xor，不妨进行一些讨论：

- 若高位的 xor 是 0，那一定大于等于；
- 若高位的 xor 是 1，其 and 是 1 的情况的不存在的，因为区间长度是偶数，则此时 and 一定为 0，也就是**不允许出现高位的 xor 是 1 的情况**。

直接枚举每一位，钦定更高位的 xor 起来是 0，枚举这一位都是 1 的极长长度为偶数，且更高位 xor 是 0 的区间，直接做即可，复杂度 $O(n\log V)$。

---

## 作者：TLE_Automat (赞：2)

## **题意：**

给定一个长度为 $n$ 的数组 $a$ ，定义这个数组的子段 $a_l,a_{l+1},\cdots,a_r$ 是**好的**，当且仅当 $a_l \& a_{l+1} \& \cdots \& a_{r} > a_l \oplus a_{l+1} \oplus \cdots \oplus a_r$ ，现在请求出数组 $a$ 的最长好的子段的长度。

这里 $\&$ 代表二进制下的按位与，$\oplus$ 代表二进制下的按位异或。

 ## **数据范围：**

$1\le n \le 10^6 , 1\le a_i \le 10^6$ 。

## **思路：**

出现了**按位与**和**按位异或**，那么我们下意识的去按二进制位考虑。

首先我们考虑一个数 $a$ 大于另一个数 $b$ 的条件：$a$ 与 $b$ 从高到低前 $x$ 位相同，且 $a$ 的第 $x+1$ 位为 $1$ ，而 $b$ 的第 $x+1$ 位为 $0$ 。

如果一个区间与起来第 $x$ 位等于 $1$ ，那么这个区间所有数的第 $x$ 位一定等于 $1$ 。如果一个区间异或起来第 $x$ 位等于 $1$ ，那么这个区间第 $x$ 位等于 $1$ 的数的个数一定为奇数个。

那么综上，一个区间能满足区间与大于区间异或的**充要条件**是：

1. 区间长度为偶数。
2. 区间从高到低第 $x$ 位全为 $1$ 。
3. 区间从高到低前 $x-1$ 位每一位上 $1$ 的个数都是偶数个。

这样的话我们可以枚举 $x$ ，对于第 $x$ 位等于 $1$ 的标记出来，得到第 $x$ 位等于 $1$ 的连续段。

接下来的问题就是怎么满足第 $3$ 个条件，实际上只需要维护一个前 $x-1$ 位的异或前缀和，并且用哈希表记录每个值最早出现的位置即可。（因为两个相同的数异或等于 $0$ ，所以这样做找到的区间一定满足第 $3$ 个条件）

$\text{Source} :$

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#define SZ(x) ((int)((x).size()))
#define lb(x) ((x)&(-(x)))
#define mkp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;

const int MAXN=1e6+10;

int n;
int a[MAXN];
bool flg[MAXN];

void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);

	int ans=0;
	for(int x=20;x>=0;x--)
	{
		memset(flg,0,sizeof(flg));
		for(int i=1;i<=n;i++)
			if(a[i]&(1<<x))	flg[i]=true;
		
		int cur=0;
		gp_hash_table<int,int> odd,even;
		even[0]=-1;
		for(int i=1;i<=n;i++)
		{
			if(!flg[i])
			{
				cur=0;
				odd.clear();
				even.clear();
				if(i&1) odd[0]=i;
				else even[0]=i;
				continue;
			}

			cur^=(a[i]>>(x+1));
			if(i&1)
			{
				if(!odd[cur]) odd[cur]=i;
				else ans=max(ans,i-odd[cur]);
			}
			else
			{
				if(even[cur]!=-1 && !even[cur]) even[cur]=i;
				else ans=max(ans,even[cur]==-1 ? i-even[cur]-1 : i-even[cur]);
			}
		}
	}

	printf("%d\n",ans);
}

int main()
{
	int T=1;
	while(T--) solve();
	return 0;
}
```

完结撒花！！(′・∀・『)



---

## 作者：ran_qwq (赞：0)

考虑区间与和大于区间异或和的充要条件。

- 首先，必须要有一位 $i$，使得 $[l,r]$ 内所有数第 $i$ 位都是 $1$。

- 其次，异或和的这一位为 $0$，也就是区间长度为偶数。

- 最后，比 $i$ 位高的所有位上，区间与和、区间异或和都为 $0$。

这很好地提示了要对于每一位分开处理。

对于一位 $i$，从左往右扫一遍 $a$ 数组，同时维护 $i$ 及高位的前缀异或和。一个合法的区间 $[l,r]$ 的 $i$ 及高位的异或和必为 $0$（如果第 $i$ 位不是 $0$ 就不可能出现区间与和大于区间异或和的情况），所以用一个桶记录前缀异或和。

- 如果 $a_j$ 第 $i$ 位为 $0$。则区间必须从这里断开，把桶清空。

- 如果 $a_j$ 第 $i$ 位为 $1$。设目前前缀和为 $sum$。

  - 如果桶中出现过 $sum$，记录答案。
  
  - 否则把 $sum$ 插入桶中。
  
注意要把 $0$ 插入桶中，还有清空的细节。

---

