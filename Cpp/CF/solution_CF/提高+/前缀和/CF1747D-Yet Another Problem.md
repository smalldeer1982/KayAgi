# Yet Another Problem

## 题目描述

You are given an array $ a $ of $ n $ integers $ a_1, a_2, a_3, \ldots, a_n $ .

You have to answer $ q $ independent queries, each consisting of two integers $ l $ and $ r $ .

- Consider the subarray $ a[l:r] $ $ = $ $ [a_l, a_{l+1}, \ldots, a_r] $ . You can apply the following operation to the subarray any number of times (possibly zero)- 
  1. Choose two integers $ L $ , $ R $ such that $ l \le L \le R \le r $ and $ R - L + 1 $ is odd.
  2. Replace each element in the subarray from $ L $ to $ R $ with the XOR of the elements in the subarray $ [L, R] $ .
- The answer to the query is the minimum number of operations required to make all elements of the subarray $ a[l:r] $ equal to $ 0 $ or $ -1 $ if it is impossible to make all of them equal to $ 0 $ .

You can find more details about XOR operation [here](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 说明/提示

In the first query, $ l = 3, r = 4 $ , subarray = $ [3, 3] $ . We can apply operation only to the subarrays of length $ 1 $ , which won't change the array; hence it is impossible to make all elements equal to $ 0 $ .

In the second query, $ l = 4, r = 6 $ , subarray = $ [3, 1, 2] $ . We can choose the whole subarray $ (L = 4, R = 6) $ and replace all elements by their XOR $ (3 \oplus 1 \oplus 2) = 0 $ , making the subarray $ [0, 0, 0] $ .

In the fifth query, $ l = 1, r = 6 $ , subarray = $ [3, 0, 3, 3, 1, 2] $ . We can make the operations as follows:

1. Choose $ L = 4, R = 6 $ , making the subarray $ [3, 0, 3, 0, 0, 0] $ .
2. Choose $ L = 1, R = 5 $ , making the subarray $ [0, 0, 0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
7 6
3 0 3 3 1 2 3
3 4
4 6
3 7
5 6
1 6
2 2```

### 输出

```
-1
1
1
-1
2
0```

# 题解

## 作者：luo_shen (赞：8)

## 题意简述
有一个长度为 $n$ 的序列 $a$，每次询问其中一段区间，需要几次操作才能将这段区间全部变为 $0$。

一次操作定义为选定一个 $l,r$ 且 $r-l+1$ 为奇数，将 $a_{l\sim r}$ 全部替换为 $\oplus_{i=l}^r$，$\oplus$ 表示异或。
## 题目分析
显然可以发现一次操作只有将区间里的数均变为 $0$，才为有效，且这样的操作至多操作两次。证明：
>设三次连续的有效操作分别为 $\begin{bmatrix}l_1,r_1\end{bmatrix},\begin{bmatrix}l_2,r_2\end{bmatrix},\begin{bmatrix}l_3,r_3\end{bmatrix}$ 且 $l_2=r_1+1,l_3=r_2+1$，此时发现 $r_3-l_1+1$ 是奇数为一个符合条件的区间，且 $0\oplus 0\oplus 0=0$，因此可以将三次操作合并为一次操作。

接下来先考虑无解的情况——若这 $\oplus_{i=l}^ra_i\not= 0$，这肯定不能通多次操作得到一个均为 $0$ 的区间。

$0$ 次操作可以完成的区间为原区间即为满足条件的区间。

剩下的区间中可以 $1$ 次操作完成的区间有什么呢？首先长度为奇数的是可以的。其次若一个区间两端有 $0$，则它也可以 $1$ 次操作完成，因为 $0$ 的加上和去掉并不影响操作的异或和，只影响操作区间的长度。

**Code**
```cpp
    while(q--){
        int l,r,L,R;
        read(l),read(r);
        L=l,R=r;
        while(l<=r&&!a[l]){//向后跳0
            l++;
        }
        while(l<=r&&!a[r]){//向前跳0
            r--;
        }
        if(l>r){//全是0的情况
            write_endl(0);
            continue;
        }
        if(xsum[r]^xsum[l-1]){//无解——异或和不为0
            write_endl(-1);
            continue;
        }
        if(l==L&&r==R){
            if((r-l+1)%2){//区间长度为奇数
                write_endl(1);
            }
            else{//区间长度为偶数
            	write_endl(2);
            }
        }
        else{//前后有0
            write_endl(1);
        }
    }
```
那么，剩下的区间就都是 $2$ 次操作可以完成的吧。  
如果这么想，就会样例都过不去。仔细想想，为什么？

我们剩下的区间都是长度为偶数的区间，但并不意味着这个区间一定能拆成两个长度为奇数且异或和为 $0$ 的子区间，如这个例子
```
2 2 4 4 6 6
```
这个区间若拆成两个异或和为 $0$ 的子区间只有两种拆法：$2,4$ 和 $4,2$。这两种拆法拆出的子区间长度均为偶数，不满足题意，答案应该为无解。

为了解决这种问题，从前往后扫一遍，求出前缀异或和 $xsum$ 数组和 $nxt$ 数组。$nxt_i$ 表示 $i$ 后面第一个满足 $xsum_i=xsum_j$ 且 $j-i\equiv 1 \pmod 2$ 的 $j$，这样区间 $\begin{bmatrix}i+1,j\end{bmatrix}$ 为一个异或和为 $0$，长度为奇数的区间。

**Code**
```cpp
    unordered_map<int,int>lst[2];//统计在奇数和偶数位置是否出现过该数
    int opt=1;//表示当前位置的奇偶性
    for(int i=1;i<=n;i++){
        if(lst[opt^1][xsum[i]]||(opt&&xsum[i]==0)){//出现过或在奇数位置为0
            nxt[lst[opt^1][xsum[i]]]=i;
        }
        lst[opt][xsum[i]]=i;//修改最近出现的位置
        opt^=1;
    }
```
但当你开心的交上去后，
![](https://cdn.luogu.com.cn/upload/image_hosting/koce8mtc.png)  
再思考一下，可以发现统计时有可能覆盖了前面的值，所以应当从后往前扫。

**更改后的Code**
```cpp
    int opt=1;
    for(int i=n;i>=0;i--){//只将从前往后扫变成了从后往前扫
        if(lst[opt^1][xsum[i]]){
            nxt[i]=lst[opt^1][xsum[i]];
        }
        lst[opt][xsum[i]]=i;
        opt^=1;
    }
```
改完的你脸上挂着天真的笑容，满怀期望交了，结果
![](https://cdn.luogu.com.cn/upload/image_hosting/ibppbkmx.png)  
仔细检查代码发现原来是不能暴力跳 $0$，统计每个 $0$ 前后第一个不是 $0$ 的数的位置。  
**Code**
```cpp
    int Lst=0;//前面第一个非0数的位置
    for(int i=1;i<=n;i++){//统计r应该跳到哪里
        read(a[i]);
        lst_zero[i]=Lst;//lst_zero[i]为i前面第一个非0数的位置
        if(a[i]>0){
            Lst=i;
            tot[i]=tot[i-1]+1;//统计0的个数，方便判全为0的情况
        }
    }
    Lst=0;//这里为后面第一个非0数的位置
    for(int i=n;i;i--){//统计l应该跳到哪里
        nxt_zero[i]=Lst;//nxt_zero[i]为i后面第一个非0数的位置
        if(a[i]>0){
            Lst=i;
        }
    }
```
终于，历经千辛万苦，这份充满细节的代码总算过了这道充满细节的题。
## 完整Code
```cpp
unordered_map<int,int>lst[2];
int n,q,a[200100],xsum[200100],tot[200100],nxt[200100],nxt_zero[200100],lst_zero[200100];
void solve(){
    read(n),read(q);
    int Lst=0;
    for(int i=1;i<=n;i++){
        read(a[i]);
        lst_zero[i]=Lst;
        if(a[i]>0){
            Lst=i;
            tot[i]=tot[i-1]+1;
        }
    }
    Lst=0;
    for(int i=n;i;i--){
        nxt_zero[i]=Lst;
        if(a[i]>0){
            Lst=i;
        }
    }
    for(int i=1;i<=n;i++){
        xsum[i]=xsum[i-1]^a[i];
    }
    int opt=1;
    for(int i=n;i>=0;i--){
        if(lst[opt^1][xsum[i]]){
            nxt[i]=lst[opt^1][xsum[i]];
        }
        lst[opt][xsum[i]]=i;
        opt^=1;
    }
    while(q--){
        int l,r,L,R;
        read(l),read(r);
        L=l,R=r;
        if(tot[r]-tot[l-1]==0){
            write_endl(0);
            continue;
        }
        if(a[l]==0){
            l=nxt_zero[l];
        }
        if(a[r]==0){
            r=lst_zero[r];
        }
        if(xsum[r]^xsum[l-1]){
            write_endl(-1);
            continue;
        }
        if(l==L&&r==R){
            if((r-l+1)%2){
                write_endl(1);
            }
            else{
                if(nxt[l-1]>=r||!nxt[l-1]){
                //注意，因为若后面没有nxt，计算时nxt为0，因此需特判
                    write_endl(-1);
                }
                else{
                    write_endl(2);
                }
            }
        }
        else{
            write_endl(1);
        }
    }
}
```
## 题外话
这篇题解是我赛场上的一个经历，直接性导致我写+调代码花了一个半小时，总计罚了 $18$ 发。事实证明，赛场上情况还是考虑少了，是边写边修正的方案，以后写代码之前还需要多加考虑。因为我们是边写边修正的思路，也帮大家踩了很多的坑。如果你踩了和我一样的坑，那么相信你可以通过我的题解明白错哪里了，希望大家能有所收获。

---

## 作者：Semorius (赞：6)

#### 题意

给定一个长度为 $n$ 的序列 $a$ 和若干询问区间，问能否通过若干次操作使询问区间均变为 $0$。一次操作可以选择一个长度为奇数的区间并将这个区间区间赋值为这个区间的异或和。

#### 思路

考虑这样一个性质：每次操作后不会改变这个区间的异或值。

>证明：设当前操作的区间为 $a_l,a_{l+1},...,a{r}$。设 $\oplus_{i=l}^ra_i=v$，操作后序列变为 $r-l+1$ 个 $v$ 连接而成，由于 $r-l+1\equiv 1 \pmod {2}$，所以 $\oplus_{i=l}^rv=v$，即操作后区间异或值不改变。

根据这个性质开始分类讨论。

如果询问区间每个数初始时均为 $0$，操作次数为 $0$。

如果一个区间的异或值不为 $0$，无论如何操作，都无法使该区间每个数都变为 $0$。

如果询问区间长度为奇数，对整个区间操作 $1$ 次即可。

最后剩下区间长度为偶数的情况。发现并不是所有的情况都有解，比如 $3,0,0,3$ 这个情况，虽然它的区间异或和为 $0$，但无论先操作前三个或后三个，都会使整个序列变为 $3,3,3,3$，然后无法操作。

所以，当询问区间长为偶数时，当且经当这个区间存在一个长为奇数的异或和为 $0$ 的前缀时有解。

考虑如何快速判断是否存在长为奇数的前缀异或和为 $0$。先预处理出原序列的前缀异或和，记一个 $nxt_x$ 表示从下标为 $x$ 的位置开始往后第一个下标与当前位奇偶性不同且其前缀异或和与当前位相等的位置，每次询问判断 $nxt_{L-1}$ 是否在询问区间内，如果在即有解。

但我赛时以为偶数情况有解时一定要操作两次，导致WA on test2了无数发。其实有些情况只需要操作一次。比如 $1,2,3,0$ 这种情况，只需要操作一次前三位就可以变为 $0,0,0,0$。更普遍的，只要区间两端点有一个值为 $0$，就可以通过忽略这个 $0$ 使区间长变为奇数，再整体操作 $1$ 次即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll SIZE = 200005;
const ll mod = 998244353;
ll n, T;
ll a[SIZE], sum[SIZE];
ll cnt[SIZE];
ll nx[SIZE];
map<ll, ll> mp[2];

inline ll rd(){
	ll f = 1, x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f*x;
}

int main(){
	n = rd(); T = rd();
	for(ll i = 1; i <= n; i++) {
		a[i] = rd(), sum[i] = (sum[i-1] ^ a[i]);
		cnt[i] = cnt[i-1] + a[i];
	}
	for(ll i = n; i >= 0; i--){
		nx[i] = mp[(i%2)^1][sum[i]];
		if(nx[i] == 0) nx[i] = n+1;
		mp[i%2][sum[i]] = i;
	}
	while(T--){
		ll l = rd(), r = rd();
		if(sum[r] ^ sum[l-1]) printf("-1\n");
		else if(cnt[r] - cnt[l-1] == 0) printf("0\n");
		else if((r-l+1)&1) printf("1\n");
		else if(nx[l-1] <= r){
			if(a[l] == 0 || a[r] == 0) printf("1\n");	
			else printf("2\n");
		}
		else printf("-1\n");
	}
	return 0;
}
```


---

## 作者：二叉苹果树 (赞：4)

- 若区间的元素全部为 $0$，答案为 $0$。
- 若区间的元素的异或和不为 $0$，无解，答案为 $-1$。
- 若区间的元素个数为奇数个，或区间的元素个数为偶数个且首个元素或末个元素为 $0$，答案为 $1$。
- 若区间的元素个数为偶数个，考虑能否在区间中选出一个位置，使区间首位到这个位置区间的异或和为 $0$。若存在，答案为 $2$；否则无解，答案为 $0$。

对于前两点性质，是十分显然的，接下来主要谈谈后两点。

对于第三点，若区间的元素个数为奇数个，则我们可以在一次选择整个区间并进行操作，使得整个区间的元素都变为 $0$。若区间的元素个数为偶数个且首个元素或末个元素为 $0$，我们选择除去首或尾那个为 $0$ 的元素，将剩下的区间的元素进行操作，使得整个区间的元素都变为 $0$。

对于第四点，我们考虑区间的首项位置为 $l$，末项位置为 $r$，异或和前缀和为 $s$。我们需要考虑一个分割点 $k$，使得 $l \sim k$ 以及 $k+1\sim r$ 两段区间的异或和分别为零。显然，此时要求 $s_k-s_{l-1}=0$ 且 $s_r-s_{k}=0$。由于 $l \sim r$ 的异或和为 $0$，所以上述两项满足其一即可。

如何快速找到分割点？以 $s_k-s_{l-1}=0$ 为例，有 $s_{l-1}=s_k$，即两个位置的异或和前缀和相等，于是我们可以将异或和前缀的相等的位置全部存储，在二分查找在 $l$ 之后的，满足 $s_{l-1}=s_k$ 的 $k$ 是否满足 $k<r$ 即可。

容易发现，不存在其他情况。

```cpp
#include<bits/stdc++.h>

int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}

#define MAXN 200005

int tot,x[MAXN],s[MAXN];
long long sum[MAXN];
std::map<int,std::vector<int> >t[2];

int main()
{
    int n=read(),q=read();
    for(int i=1;i<=n;i++)
    {
        x[i]=read();
        s[i]=s[i-1]^x[i];
        sum[i]=sum[i-1]+x[i];
        t[i%2][s[i]].push_back(i);
    }
    for(int i=1;i<=q;i++)
    {
        int l=read(),r=read();
        if(sum[r]-sum[l-1]==0)
            printf("0\n");
        else if(s[l-1]!=s[r])
            printf("-1\n");
        else if((r-l)%2==0||((r-l)%2!=0&&(x[l]==0||x[r]==0)))
            printf("1\n");
        else
        {
            auto it=std::lower_bound(t[l&1][s[l-1]].begin(),t[l&1][s[l-1]].end(),l);
            if(it!=t[l&1][s[l-1]].end()&&*it<r)
                printf("2\n");
            else
                printf("-1\n");
        }
    }
    return 0;
}
```


---

## 作者：Yusani_huh (赞：1)

[洛谷题面传送](https://www.luogu.com.cn/problem/CF1747D)，[CF 题面传送](http://codeforces.com/problemset/problem/1747/D)。

观前提示：这篇题解使用了暴力分块做法，对数据结构过敏者不建议观看。

题目要求最少操作数，所以对于已经操作过的段再次操作不会更优，证明如下：如果有一段已经被操作，那么当前操作涉及到该段中偶数个元素则等效于没有涉及，涉及到奇数个元素则等效于涉及了整段。根据这一点进行转化后，所有进行操作的区间要么包含，要么相离，发现包含必不优，所以只会相离。

这样问题就变成了把询问区间分成尽量少的若干段，使得每段异或和都为 $0$。

若区间长度为奇数，那么不论如何分段都可以合并为在整个区间上的一次操作，答案最多为 $1$；若长度为偶数，必可以拆成两个奇数段（若拆成多个奇数段，可以将奇数个奇数段合并为一个），答案最多为 $2$。

首先注意特判区间全为 $0$（不需要操作）和区间异或和不为 $0$（无解）的情况。

长度为奇数的区间可以预处理前缀异或和然后整段判，考虑偶数如何处理。

若偶数区间的最左边或最右边有一个 $0$，那么可以直接将其化为奇数区间来处理。否则拆成两个奇数段，其异或和分别为 $0$。这样就把问题在前缀异或和数组 $s$ 上转化为：在 $[l,r]$ 中找一个数 $x$，使得 $s_x=s_{l-1}$，且 $x-l+1$ 为奇数（也就是 $x$ 与 $l$ 奇偶性相同）。

由于有奇偶性限制，可以把整个序列的奇数位和偶数位分离，对两个新序列分别进行分块，将值域离散化后用 `bitset` 记录每块内出现了哪些不同的 $s_i$，然后在询问区间内暴力处理整块和散块即可。细节见代码。

时间 $\Theta(n\sqrt{n})$，空间略大，但是能过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200003
#define LL long long
#define INF 0x3f3f3f3f
int n,q,a[N],s[N],z[N],len;
vector<int>un;
bitset<N>bs[1003];
int get(int i){ //get块编号，注意奇偶分离
	if(i&1) return i/len;
	else return i/len+500;
}
int getp(int x)
	{return lower_bound(un.begin(),un.end(),x)-un.begin();}
bool query(int l,int r,int x){
	int lb=get(l),rb=get(r-1);
	if(lb==rb){ //若首位端点在同一块内直接暴力
		for(int i=l;i<=r;i+=2)
			if(s[i]==x) return true;
		return false;
	}else{
		int le=(lb>=500?lb-500:lb)*len+len-1;
		int rs=(rb>=500?rb-500:rb)*len;
		int p=getp(x);
		if(rs-l&1) rs++;
		for(int i=lb+1;i<rb;++i) //扫整块
			if(bs[i][p]) return true;
		for(int i=l;i<=le;i+=2) //扫左边散块
			if(s[i]==x) return true;
		for(int i=rs;i<=r;i+=2) //扫右边散块
			if(s[i]==x) return true;
		return false;
	}
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),
		s[i]=s[i-1]^a[i],z[i]=z[i-1]+!!a[i],
		un.push_back(s[i]);
	sort(un.begin(),un.end());
	un.erase(unique(un.begin(),un.end()),un.end());
	len=sqrt(n);
	for(int i=1;i<=n;++i)
		bs[get(i)][getp(s[i])]=true;
	while(q--){
		int l,r;
		scanf("%d%d",&l,&r);
		if(z[r]-z[l-1]==0) puts("0"); //全0
		else if(s[r]^s[l-1]) puts("-1"); //无解
		else if((r-l+1)&1) puts("1"); //奇数
		else if(!a[l]||!a[r]) puts("1"); //偶数但有左右0
		else if(query(l,r,s[l-1])) puts("2");
		else puts("-1");
	}
	return 0;
}
```

---

## 作者：XenonWZH (赞：0)

[更好的阅读体验请点这](https://xenonwzh.github.io/cf-1747d/)

# 解题思路

首先我们分析询问。通过异或的性质，我们很容易得出：在询问 $[l, r]$ 中，当 $\oplus_{i = l}^{r}a_{i} \ne 0$ 时无解。否则会进行下列情况：

- 当 $\forall a_i = 0 (i \in [l, r])$ 时：显然操作数为 $0$。
- 当 $r - l + 1$ 为奇数时：此时只需要进行 $l \rightarrow r$ 一次操作即可将整个区间变为 $0$，即操作数为 $1$。
- 当 $r - l + 1$ 为偶数时，需要分下列两种情况讨论：
    - 当 $a_l = 0 \vee a_r = 0$ 时：去掉 $a_l$ 或 $a_r$ 可变为奇数情况，故操作数为 $1$。
    - 当该区间可被分为两个奇数长度的区间（且这两个区间的异或和均为 $0$）时：分别将这两个化为 $0$，显然操作数为 $2$。
    - 其余情况：由于只能选择奇数长度的段，于是无论如何都选择不出异或和为 $0$ 的段，导致无法将区间化为 $0$。于是无解。

于是我们只需要预处理出异或前缀和 $\text{res}$，$a_i$ 中 $0$ 的个数 $\text{cnt0}$ 和每个异或前缀和所对应的坐标集合 $f_{0 / 1, m}$（第一维中 $0$ 表示偶数坐标，$1$ 表示奇数坐标），然后查询即可。

- 首先判断 $\text{cnt0}_r - \text{cnt0}_{l - 1}$ 是否等于 $r - l + 1$。
- 然后判断 $\text{res}_{l - 1}$ 是否等于 $\text{res}_{r}$。
- 当 $r - l + 1$ 为奇数时：直接得出答案。
- 当 $r - l + 1$ 为偶数时：对 $f_{l \bmod 2, \text{res}_{l - 1}}$ 二分求出大于 $l$ 的最小坐标。若该坐标小于 $r$，则说明可将该区间分割，答案为 $2$，否则无解。

时间复杂度为 $O(n \log n)$。

# 代码演示

```cpp
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    std::vector<int> res(n + 1);
    for (int i = 1; i <= n; i++) res[i] = res[i - 1] ^ a[i];

    std::vector<int> cnt0(n + 1);
    for (int i = 1; i <= n; i++) cnt0[i] = cnt0[i - 1] + (a[i] == 0);

    std::map<int, std::vector<int>> f[2];
    for (int i = 1; i <= n; i++) f[i % 2][res[i]].push_back(i);

    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);

        if (cnt0[r] - cnt0[l - 1] == r - l + 1) puts("0");
        else if (res[l - 1] != res[r]) puts("-1");
        else if ((r - l + 1) % 2 || a[l] == 0 || a[r] == 0) puts("1");
        else {
            auto p = std::upper_bound(f[l % 2][res[l - 1]].begin(), f[l % 2][res[l - 1]].end(), l);
            if (p != f[l % 2][res[l - 1]].end() && *p < r) puts("2");
            else puts("-1");
        }
    }

    return 0;
}
```

---

## 作者：AKPC (赞：0)

前缀和与大分讨。

首先要知道，在 $[l,r]$ 内选择区间 $[L,R]$ 做操作时，$[L,R]$ **修改前后的区间异或和是一成不变的**，$[l,r]$ **前后的异或和也是一成不变的**。这是因为异或这个特殊运算的自身性质，且 $R-L+1$ 只能为奇数。

可以特判一些条件：

- $[l,r]$ 中全都是 $0$ 输出 $1$（原因显然）。
- $\bigoplus_{i=l}^ra_i\neq0$，输出 $-1$（因为你无论怎么选 $[L,R]$，$[l,r]$ 前后的异或和都是一成不变的，自然永远不会为 $0$，这也说明了永远不可能将 $[l,r]$ 全改成 $0$）。
- $\bigoplus_{i=l}^ra_i=0$，且 $r-l+1$ 为奇数，输出 $1$（选择 $L=l$，$R=r$ 即可）。
- $\bigoplus_{i=l}^ra_i=0$，且 $r-l+1$ 为偶数，但是 $a_l=0$，输出 $1$（选择 $L=l+1$，$R=r$ 即可），$a_r=0$ 同理。

现在情况只剩下 $\bigoplus_{i=l}^ra_i=0$，且 $r-l+1$ 为偶数，$a_l,a_r\neq0$ 了。

可以考虑选择一个 $k\in[l,r]$，$k-l+1$ 为奇数（自然 $r-k+1$ 为偶数），故选择 $L_1=l$，$R_1=k$，$L_2=k+1$，$R_2=r$，判断 $\bigoplus_{i=L_1}^{R_1}a_i=0$ 以及 $\bigoplus_{i=L_2}^{R_2}a_i=0$ 时有解输出 $2$ 即可，没有满足条件的 $k$ 输出 $-1$。

如何找这个 $k$？根据 P9753 判断栈相同类似的思想，可以发现当 $\bigoplus_{i=1}^{R_1}a_i=\bigoplus_{i=1}^{L_1}a_i$ 时，$\bigoplus_{i=L_1}^{R_1}a_i=0$，而因为 $\bigoplus_{i=l}^{r}a_i=0$，自然根据异或性质 $\bigoplus_{i=L_2}^{R_2}a_i=0$。

那么只需要找到 $[l,r]$ 区间内任意一个 $k$ 满足 $k-l+1$ 为奇数且 $\bigoplus_{i=l}^{k}a_i=0$ 即可。可以用桶处理不同奇偶的每个前缀异或值最新一次出现的位置，然后预处理出每个 $l$ 对应的 $k$。

具体预处理代码如下：

```cpp
unordered_map<int,int>mp[2];//桶
int nxt[200005];//存储每个 l 对应的 k

for (int i=n;i>=0;i--){
	nxt[i]=mp[i&1^1][sum[i]];
	mp[i&1][sum[i]]=i;
}
```

至于最后一种情况为何不选更多区间？以区间个数 $3$ 为例，假设区间为 $[L_1,R_1]$，$[L_2,R_2]$，$[L_3,R_3]$，由于这三段异或和都为 $0$，故 $\bigoplus_{i=L_1}^{R_3}a_i=0$ 也成立，而且选择 $[L_1,R_3]$ 后依然符合 $R_3-L_1+1$ 为奇数，故三个连续的符合条件的区间可以拼成一个，那么即证选最多两个区间一定有解。

[code](/paste/ioly7a88)。

---

