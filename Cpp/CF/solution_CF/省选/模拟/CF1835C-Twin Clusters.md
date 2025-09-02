# Twin Clusters

## 题目描述

Famous worldwide astrophysicist Mleil waGrasse Tysok recently read about the existence of twin galaxy clusters. Before he shares this knowledge with the broader audience in his podcast called S.tarT-ok, he wants to prove their presence on his own. Mleil is aware that the vastness of the universe is astounding (almost as astounding as his observation skills) and decides to try his luck and find some new pair of twin clusters.

To do so, he used his TLEscope to observe a part of the night sky that was not yet examined by humanity in which there are exactly $ 2^{k + 1} $ galaxies in a row. $ i $ -th of them consist of exactly $ 0 \le g_i < 4^k $ stars.

A galaxy cluster is any non-empty contiguous segment of galaxies. Moreover, its' trait is said to be equal to the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all values $ g_i $ within this range.

Two galaxy clusters are considered twins if and only if they have the same traits and their corresponding segments are disjoint.

Write a program that, for many scenarios, will read a description of a night sky part observed by Mleil and outputs a location of two intervals belonging to some twin clusters pair, or a single value $ -1 $ if no such pair exists.

## 说明/提示

In the first test case we pick intervals $ [2, 4] $ and $ [6, 6] $ as our twin clusters. The trait of the first interval equals $ 15 \oplus 0 \oplus 7 = 8 $ , and the trait of the second interval equals $ 8 $ , so these galaxy clusters are indeed twins.

## 样例 #1

### 输入

```
4
2
4 15 0 7 11 8 3 2
1
0 1 2 3
0
0 0
3
15 63 57 39 61 25 42 61 50 41 27 41 56 23 17 27```

### 输出

```
2 4 6 6
2 2 3 4
1 1 2 2
1 1 4 10```

# 题解

## 作者：daduoli (赞：9)

[题目传送门](https://codeforces.com/contest/1835/problem/C)

看到数据范围有 $2^{k+1}$ 个数，然后我们的值域是 $4^k$。

我们首先容易想到进行一个前缀异或，即为 $a$ 数组。

然后可以知道每个数都有 $2k$ 位，不足的用前导 $0$ 补。

我们把 $a$ 数组中每个数分成前 $k$ 位，和后 $k$ 位。

然后我们分两步做，先用一个数组，存储上一个前 $k$ 位，和当前前 $k$ 位相同的，记为 $l$ ，然后把 $(l+1,i)$ 视作一个二元组，表示我们所选的区间，也就是说我们这个区间里的数异或起来只有后 $k$ 位是有值的。然后我们在前面所选的二元组里面，找到一个异或值与当前数相同的，就可以得到我们的答案。

说简单一点就是，当前 $k$ 位有相同的数，那么就能贡献一个二元组。

对于两个二元组如果是答案，记为 $(x_1,y_1)(x_2,y_2)$。

分三种情况。

- $y_1<x_2$ 输出 $(x_1,y_1)(x_2,y_2)$

- $x_1\le x_2\le y_1$，输出 $(x_1,x_2-1),(y_1+1,y_2)$

- $x_2<x_1$ 输出 $(x_2,x_1-1),(y_1+1,y_2)$

这个比较简单，不需要解释，但为什么我们上面找答案的过程就是对的呢。

首先我们有 $2^{k+1}+1$ 个前缀异或（包括了第 $0$ 位的 $0$）。

然后画个图，方便理解

![](https://cdn.luogu.com.cn/upload/image_hosting/xhr69z11.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这个图中 $a_3=a_4=a_6$ 那么我们就可以得到两个二元组。

$a_2=a_5$ 可以得到一个二元组。

但这时又有一个同学要问 $a_3=a_4=a_6$ 不是可以得到三个二元组吗，但实际上我们不需要三个，因为两个就足以求出答案。

这种解法的巧妙之处在于通过时间允许范围内的枚举次数保证求出答案，这就是这题构造算法的精髓。

如何证明呢：

$2^{k+1}+1=2^k+(2^k+1)$

首先最坏情况，前 $k$ 位所有可能的都出现过，有 $2^k$ 种情况，都是没有贡献的。

然后我们也至少还会有 $2^k+1$ 是有贡献的，因为前面的都已经出现过了，所以后面无论怎么选都有贡献。

而我们后 $k$ 为又只有 $2^k$ 中情况，根据鸽巢原理，可以知道一定会出现一个异或起来等于 $0$ 的情况。于是这题就做完了。

时间复杂度 $O(2^{k+1})$

[code here](https://codeforces.com/contest/1835/submission/211780586)

总结：

人类智慧题。

1、构造题不一定所有情况都要枚举，可以考虑枚举时间范围内允许得枚举次数来保证获得解，那么就可以直接暴力。

---

## 作者：Polaris_Australis_ (赞：6)

提供一种非随机做法。

首先如果存在 $i\ne j$，满足 $a_i=a_j$，则直接输出 $[i,i]$ 和 $[j,j]$ 即可，以下只讨论不存在两个位置值相等的情况。

首先可以发现，如果存在一个 $val$，满足有三个不同的区间，异或和均为 $val$，则一定存在两个不相交的区间异或和相等（注意相等但不一定是 $val$），具体仅分为以下两种情况：

* 存在两个区间满足左端点互不相等且右端点互不相等，如果不相交则直接输出这两个区间，否则设区间一为 $[l_1,r_1]$，区间二为 $[l_2,r_2]$，假定 $l_1<l_2$。若两者相交但不包含则去掉公共部分后异或和仍相等，输出 $[l_1,l_2-1]$ 和 $[r_1+1,r_2]$；若区间一包含区间二，把区间一分成三段，左右两段异或和的异或值一定为 $0$，即两者异或和相等，输出 $[l_1,l_2-1]$ 和 $[r_2+1,r_1]$。
* 三个区间的左端点（右端点）同时重合，这里仅考虑左端点重合，设三个区间分别为 $[l,r_1],[l,r_2],[l,r_3]$，则 $[r_1+1,r_2$] 和 $[r_2+1,r_3]$ 的区间异或和均为 $0$，输出这两个区间即可，右端点重合同理。

之后考虑整个序列共有 $\frac{2^{k+1}\times(2^{k+1}+1)}{2}=2^{2k+1}+2^k$ 个区间，而区间异或和最多只有 $2^{2k}$ 种值，所以至少存在一个 $val$ 满足有至少 $3$ 个区间异或和为 $val$。

接下来考虑如何找到 $val$，考虑逐位确定。对于每一位，区间异或和只有两种可能，按照这一位区间异或和的值把区间集合分成两部分，每位都取较大的一个集合，即可保证最终会保留至少三个区间。

但是区间太多，不能逐个记下。假设已经处理完后 $i-1$ 位，考虑对于每个 $r$ 记录一个最大的 $l$ 满足 $[l,r]$ 的区间异或和的后 $i-1$ 位恰为当前 $val$，设这样的 $l$ 为 $p_r$。记 $a$ 序列的前缀异或和为 $sum$，之后考虑其他的异或和为 $val$ 的区间左端点 $l'$，一定满足 $sum_{l'-1}$ 和 $sum_{p_r-1}$ 的后 $i-1$ 位相同，满足这样条件的左端点个数可以用 map 或者链表来维护，map 会多一个 $\log$ 过不去。记录下这个后，容易求出当前位异或和为 $0$ 的区间数和异或和为 $1$ 的区间数，取大的集合并更新 $val$ 即可。

具体地，记录 $lst_{j,0/1}$ 表示满足 $l<j$，$sum_l$ 与 $sum_j$ 的后 $i-1$ 位相同，$sum_l$ 的第 $i$ 位是 $0/1$ 的 $l$ 中最大的一个，并记录 $S_{j,0/1}$ 表示满足这样条件的 $l$ 的个数。更新的时候找到 $p_r$ 后，直接根据 $S_{p_r,0/1}$ 更新区间个数，并更新链表和 $p$ 数组即可。

时间复杂度 $\mathcal{O}(2^{k}k)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Umekawa_Kouko{
	void main();
}
int main(){
	return Umekawa_Kouko::main(),0;
}
namespace Umekawa_Kouko{
	#define int long long
	int k,a[300010],lst[300010],lstl[300010],lstb[300010];
	int sum1[300010],sum[300010];
	map<int,int>mp;
	void solve(){
		cin>>k;
		mp.clear();
		int n=1<<(k+1);
		for(int i=1;i<=n;++i)cin>>a[i];
		for(int i=1;i<=n;++i){
			if(mp.find(a[i])!=mp.end()){
				cout<<mp[a[i]]<<" "<<mp[a[i]]<<" "<<i<<" "<<i<<"\n";
				return;
			}
			mp[a[i]]=i;
		}
		for(int i=1;i<=n;++i)a[i]^=a[i-1],sum[i]=i;
		for(int i=0;i<=n;++i)lst[i]=i-1,lstl[i]=i-1,lstb[i]=-1;
		lst[0]=-1;
		int now=0;
		vector<int>vec; // 用于剪枝，记录所有存在对应 l 的 r，也用于最后处理答案
		for(int i=1;i<=n;++i)vec.push_back(i);
		for(int i=0;i<(k<<1);++i){
			for(int j=1;j<=n;++j){
				int op=((a[j]>>i)&1);
				if(~lstl[j])sum1[j]=sum1[lstl[j]]+(op==1);
				else sum1[j]=(op==1);
				if(!~lstl[j]){
					lstb[j]=-1;
					continue;
				}
				if(((a[lstl[j]]>>i)&1)!=((a[j]>>i)&1)){
					lstb[j]=lstl[j];
					lstl[j]=lstb[lstl[j]];
				}else{
					lstb[j]=lstb[lstl[j]];
				}
			}
			int t1=0,t0=0;
			for(int j:vec){
				int p=lst[j];
				int t=((a[j]>>i)&1);
				if(t){
					t1+=sum[j]-sum1[p];
					t0+=sum1[p];
				}else{
					t1+=sum1[p];
					t0+=sum[j]-sum1[p];
				}
			}
			if(t1>t0){
				now|=(1ll<<i);
				for(int j:vec){
					int p=lst[j];
					if((a[j]>>i)&1)sum[j]=sum[j]-sum1[p];
					else sum[j]=sum1[p];
					if(((a[j]>>i)&1)!=((a[p]>>i)&1))lst[j]=p;
					else lst[j]=lstb[p];
				}
			}else{
				for(int j:vec){
					int p=lst[j];
					if((a[j]>>i)&1)sum[j]=sum1[p];
					else sum[j]=sum[j]-sum1[p];
					if(((a[j]>>i)&1)!=((a[p]>>i)&1))lst[j]=lstb[p];
					else lst[j]=p;
				}
			}
			vec.clear();
			for(int i=1;i<=n;++i)if(~lst[i])vec.push_back(i);
		}
		int sz=vec.size();
		for(int ti=0;ti<sz;++ti){
			int i=vec[ti];
			for(int tj=ti+1;tj<sz;++tj){
				int j=vec[tj];
				if(lst[i]!=lst[j]){
					if(lst[j]<lst[i])cout<<lst[j]+1<<" "<<lst[i]<<" "<<i+1<<" "<<j<<'\n';
					else if(lst[j]<i)cout<<lst[i]+1<<" "<<lst[j]<<" "<<i+1<<" "<<j<<"\n";
					else cout<<lst[i]+1<<" "<<i<<" "<<lst[j]+1<<" "<<j<<"\n";
					return;
				}
			}
			break;
		}
		if(sz>2){
			cout<<vec[0]+1<<" "<<vec[1]<<" "<<vec[1]+1<<" "<<vec[2]<<"\n";
			return;
		}
		for(int ti=0;ti<sz;++ti){
			int i=vec[ti];
			for(int tj=ti+1;tj<sz;++tj){
				int j=vec[tj];
				int t=lst[j];
				int t2=0;
				for(int k=0;k<t;++k){
					if(a[k]==a[t]){
						t2=k;
						break;
					}
				}
				cout<<t2+1<<" "<<t<<" "<<i+1<<" "<<j<<"\n";
				return;
			}
		}
		int i=vec[0];
		int t=lst[i];
		for(int j=t-1;~j;--j){
			if(a[j]==a[t]){
				for(int k=j-1;~k;--k){
					if(a[k]==a[j]){
						cout<<k+1<<" "<<j<<" "<<j+1<<" "<<t<<"\n";
						return;
					}
				}
			}
		}
	}
	void main(){
		ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
		int T;
		cin>>T;
		while(T--)solve();
	}
}
```


---

## 作者：lndjy (赞：5)

首先，区间不交是假的，考虑有两个相交的区间，把相交的部分删去，剩下的两个区间异或和仍然相等。所以只需要找到任意两个区间就行。

然后发现题目的值域很奇怪，正好是序列长度的平方，这样就可以考虑生日悖论，每次随机一个区间，给他插进 map 里面，期望随机根号值域级别（也就是 $2^k$），就会出现相同的异或和。调调参就能过了。

注意一些细节：首先，对于有一个端点相同的两个区间，是不能拆成两个不交区间的，这种情况要特判。

然后数据比较小的时候，随机化效果并不好，需要特判然后暴力。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<random>
#define endl "\n"
#define pir pair<int,int>
#define mkp make_pair
#define int long long
using namespace std;
int inline read()
{
	int ans=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*f;
}
mt19937 rnd(19260817);
int rad(int x,int y){
	return rnd()%(y-x+1)+x;
}
int n,m,k;
const int N=1e6+5;
int a[N],sum[N];
map<int,pir > mp;
signed main()
{
	int T;
	cin>>T;srand(19260817);
	while(T--)
	{
		cin>>k;
		for(int i=1;i<=(1<<(k+1));i++)
		a[i]=read();
		for(int i=1;i<=(1<<(k+1));i++)
		sum[i]=sum[i-1]^a[i];
		if(k==0)
		{
			cout<<"1 1 2 2\n";
			continue;
		}
		if(k==1)
		{
			for(int l1=1;l1<=3;l1++)
			for(int r1=l1;r1<=3;r1++)
			for(int l2=r1+1;l2<=4;l2++)
			for(int r2=l2;r2<=4;r2++)
			if((sum[l1-1]^sum[r1])==(sum[l2-1]^sum[r2]))
			{
				cout<<l1<<" "<<r1<<" "<<l2<<' '<<r2<<endl;
				goto q123;
			}
			q123:
				continue;
		}
		mp.clear();
		int flg=0;
		while(1)
		{
			int l=rad(0,(1<<(k+1))),r=rad(0,(1<<(k+1)));
			if(l==r) continue;
			if(l>r) swap(l,r);
			if(mp.find(sum[r]^sum[l])==mp.end()) mp[sum[r]^sum[l]]=mkp(l,r);
			else if(mp.find(sum[r]^sum[l])!=mp.end()&&mp[sum[r]^sum[l]].first!=l&&mp[sum[r]^sum[l]].second!=r)
			{
				int l1=l+1,r1=r,l2=mp[sum[r]^sum[l]].first+1,r2=mp[sum[r]^sum[l]].second;
				if(l1>l2) swap(l1,l2),swap(r1,r2);
				if(l2>r1) cout<<l1<<" "<<r1<<" "<<l2<<' '<<r2<<endl;
				else if(r2<r1) cout<<l1<<" "<<l2-1<<" "<<r2+1<<" "<<r1<<endl;
				else cout<<l1<<' '<<l2-1<<' '<<r1+1<<" "<<r2<<endl;
//				flg=1;
				break;
			}
			flg++;
			if(flg>=(1<<(k+5)))
			{
				puts("-1");
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：Petit_Souris (赞：2)

这啥啊，我是真不会做。

设 $n=2^{k+1}$。

发现我们如果选出一组左端点和右端点都不相同的区间，那么一定可以构造出解：如果不交直接作为答案，否则把相交部分同时删掉不影响异或值相等。

把值域分成高 $k$ 位和低 $k$ 位。设前缀异或和为 $s_{0},s_{1},\dots ,s_{n}$，其中 $s_0=0$。对于一个值 $v$，如果我们能找到 $x_1<y_1<x_2<y_2$ 满足 $s_{x_1-1},s_{y_1}$ 高 $k$ 位相同，$s_{x_2-1}$ 和 $s_{y_2}$ 高 $k$ 位相同，且 $s_{x_1-1}\oplus s_{y_1},s_{x_2-1}\oplus s_{y_2}$ 的低 $k$ 位相同，那么一定可以通过 $[x_1,y_1]$ 和 $[x_2,y_2]$ 通过上一段中的构造方式得到答案。

考虑怎样找到这样的两个区间：设 $p$ 为 $i$ 前面第一个满足 $s_{p}=s_{i}$ 的位置，那么我们取出所有 $[p+1,i]$，至少有 $2^k+1$ 组这样的区间，所以其中必定有一对满足条件。拿个桶维护一下就行了，时间复杂度 $\mathcal O(2^k)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e6+9;
ll T,k,n,a[N],bin[N],pl[N],pr[N];
void solve(){
    k=read(),n=(2<<k);
    rep(i,1,n)a[i]=read();
    a[0]=0;
    rep(i,1,n)a[i]^=a[i-1];
    rep(i,0,n)bin[i]=pl[i]=pr[i]=-1;
    bin[0]=0;
    rep(i,1,n){
        if(~bin[a[i]>>k]){
            ll l=bin[a[i]>>k]+1,r=i,s=a[r]^a[l-1];
            if(!~pl[s])pl[s]=l,pr[s]=r;
            else {
                if(pr[s]<l)write(pl[s]),putchar(' '),write(pr[s]),putchar(' '),write(l),putchar(' '),write(r);
                else write(min(l,pl[s])),putchar(' '),write(max(l,pl[s])-1),putchar(' '),write(pr[s]+1),putchar(' '),write(r);
                putchar('\n');
                return ;
            }
        }
        bin[a[i]>>k]=i;
    }
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：orz_z (赞：2)





有点神奇。



只要有异或和相等的两个区间即可。



类似生日悖论，期望找到异或和相等的区间为根号值域次，数据小时暴力。



再想想正解。

共有 $2^{2k + 1}=4^k \times 2$ 个区间，但是值域只有 $4^k$，所以必然有解。



我们对值域分成前 $k$ 位和后 $k$ 位考虑，找到 $s_{r1}\oplus s_{l1-1} \oplus s_{r2} \oplus s_{l2-1}=0$ 的对，考虑 $s_{r1} \oplus s_{l1-1}$ 的前 $k$ 位相同，$s_{r2}\oplus s_{l2-1}$ 的前 $k$ 位相同，然后让他们的后 $k$ 位相同，这样就满足条件了。

就是找到前 $k$ 位相同的几堆，每堆可构成堆数减一对，然后考虑它们的后 $k$ 位异或和是否为 $0$。

想想为什么能找到，类似的，前 $k$ 位共有 $2^{k+1}+1=2^k+2^k+1$ 个前缀异或和，但值域只有 $2^k$，所有至少产生 $2^k+2$ 个相同的数，只能找到 $2^k+1$ 对前 $k$ 位相同的数即可，因为后 $k$ 位值域只有 $2^k$，所以一定有重复的。

时间复杂度 $\mathcal O(2^{k+1})$。

---

## 作者：JimmyF (赞：1)

[Link](https://codeforces.com/contest/1835/problem/C)

题解做法感觉很巧妙，是一道比较好的构造数论题。

首先推性质，看见题目那个 $-1$ 了吗，没错，是欺骗你的。

至于如何证明呢，我们先做一个前缀异或差分，然后一个区间就可以用形如 $(s_x,s_y)$ 的二元组表示（这很套路）。然后考虑我们一共有 $2^{k+1}$ 个数，于是就有 $2^{2k+1}=4^k\times 2$ 个二元组，二元组的取值一共有 $4^k\times2-1$，根据鸽巢原理，一定会有两个二元组相等。

接下来就是抽象的东西，我们考虑对于 $s$ 的二进制前 $k$ 位进行分类，然后对 $s$ 的后 $k$ 位进行匹配。即我们要找形如 $s_x \oplus s_y = s_a\oplus s_b$ 的东西，我们让 $s_a$ 和 $s_b$ 的 前 $k$ 位相等，$s_x$ 和 $s_y$ 的后 $k$ 位相等，然后匹配两两的后 $k$ 位。

至于这样的正确性，与 $-1$ 类似，我们一共有 $2^{k+1}+1=2^k+(2^k+1)$（算上空前缀）个前缀，前 $k$ 位一共有 $2^k$ 种可能性，所以至少会有 $2^k+1$ 个后 $k$ 位的贡献，但是后 $k$ 位最多又只有 $2^k$ 种可能，所以根据鸽巢原理，一定会有重复的。

所以对于每一个前缀（记为 $y$），我们记录上一次与他前 $k$ 位相同的前缀的位置（记为 $x$，然后将 $s_x\oplus s_y$（相当于将后 $k$ 位取出）放到 map 里看一下前面有没有相同的，有就是找到了，然后每次更新 map。

还有个理解性的问题，就是为什么只需要记录上一个，而不是记录前面所有出现过的。因为记一个已经够了，已经可以保证找到 $2^k+1$ 对相同的前 $k$ 位，不需要记更多。

于是这题就做完了...

[Code](https://codeforces.com/contest/1835/submission/211780952)

总结：

构造题还是要多推性质，数学还是得学好，然后枚举讲究策略。

---

## 作者：lfxxx (赞：0)

下面记 $n=2^{k+1}$。

找到两个不同的区间 $[x,y],[a,b]$ 后只要保证两个区间的对称差不为 $1$ 且区间异或和相等就能构造出一组合法解。

不难发现有 $2^{k+1}+1 \choose 2$ 个不同区间，而区间异或和只有 $4^k$ 种情况，根据抽屉原理总有一种异或值包含了至少 $3$ 个不同区间，而三个区间肯定不会两两对称差为 $1$，故一定有解。

考虑快速找到解，由于 $O(V)=O(n^2)$，考虑折半，枚举区间异或值的低 $k$ 位，有 $2^k$ 种情况，总有一种情况会包含 $2^{k+1}+1$ 个不同区间，所以后 $k$ 位一定存在一种情况包含 $3$ 个不同区间，找到合法前 $k$ 位后，可以暴力枚举找出足够多的区间，找到合法前 $k$ 位可以使用异或卷积，时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = (1<<18)+114;
double f[maxn];
int K,a[maxn];
void fwt_xor(double *f,double x=1){
    for(int o=2,k=1;o<=(1<<K);o<<=1,k<<=1){
        for(int i=0;i<(1<<K);i+=o){
            for(int j=0;j<k;j++){
                double a=f[i+j];
                double b=f[i+j+k];
                f[i+j]=a+b;
                f[i+j+k]=a-b;
                f[i+j]=f[i+j]*x,f[i+j+k]=f[i+j+k]*x;
            }
        }
    }
}
vector<int> pos[maxn];
vector< pair<int,int> > d[maxn];
bool check(int l,int r,int L,int R){
    if(l>L) swap(l,L),swap(r,R);
    if(l==L&&r>R) swap(l,L),swap(r,R);
    if(l!=L&&r!=R){
        if(r<L){
            cout<<l<<" "<<r<<" "<<L<<" "<<R<<"\n";
        }else if(R<r){
            cout<<l<<" "<<L-1<<" "<<R+1<<" "<<r<<"\n";
        }else{
            cout<<l<<" "<<L-1<<" "<<r+1<<" "<<R<<"\n";
        }
        return true;
    }else{
        if(l==L){
            if(R==r+1) return false;
            cout<<r+1<<" "<<r+1<<" "<<r+2<<" "<<R<<"\n";
        }else{
            if(l==L-1) return false;
            cout<<l<<" "<<l<<" "<<l+1<<" "<<L-1<<"\n";
        }
        return true;
    }
    return false;
}
void work(){
    cin>>K;
    f[0]++,pos[0].push_back(0);
    for(int i=1;i<=(1<<(K+1));i++) cin>>a[i],a[i]^=a[i-1],f[a[i]&((1<<K)-1)]++,pos[a[i]&((1<<K)-1)].push_back(i);
    fwt_xor(f);
    for(int i=0;i<(1<<K);i++) f[i]=f[i]*f[i];
    fwt_xor(f,0.5);
    f[0]-=(1<<(K+1))+1;
    for(int i=0;i<(1<<K);i++) f[i]/=2;
    int ans=0;
    for(int i=0;i<(1<<K);i++){
        if(f[i]>=(1<<(K+1))+1) ans=i;
    }
    vector< pair<int,int> > vec;
    for(int i=0;i<(1<<K);i++){
        int j=ans^i;
        if(i<j){
            for(int x:pos[i]){
                for(int y:pos[j]){
                    vec.push_back(make_pair(x,y));
                    if(vec.size()==(1<<(K+1))+1) break;
                }
                if(vec.size()==(1<<(K+1))+1) break;
            }
        }
        if(vec.size()==(1<<(K+1))+1) break;
        if(i==j){
            for(int p1=0;p1<pos[i].size();p1++){
                for(int p2=p1+1;p2<pos[i].size();p2++){
                    vec.push_back(make_pair(pos[i][p1],pos[i][p2]));
                    if(vec.size()==(1<<(K+1))+1) break;
                }
                if(vec.size()==(1<<(K+1))+1) break;
            }
        }
        if(vec.size()==(1<<(K+1))+1) break;
    }
    for(int i=0;i<vec.size();i++){
        if(vec[i].first>vec[i].second) swap(vec[i].first,vec[i].second); 
    }
    for(pair<int,int> now:vec){
        d[(a[now.first]^a[now.second])>>K].push_back(now);
    }
    for(int i=0;i<(1<<K);i++){
        if(d[i].size()>=3){
            bool flag=false;
            for(int p1=0;p1<3;p1++){
                for(int p2=p1+1;p2<3;p2++){
                    if(check(d[i][p1].first+1,d[i][p1].second,d[i][p2].first+1,d[i][p2].second)==true) flag=true;
                    if(flag==true) break;
                }
                if(flag==true) break;
            }
            break;
        }
    }
    for(int i=0;i<(1<<K);i++) pos[i].clear(),d[i].clear(),f[i]=0;
    return ;
}   
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
1
3 1 3 0
*/
```

---

## 作者：happybob (赞：0)

题意：

给定 $k$ 与一个长度为 $2^{k+1}$ 的整数序列，每个数 $a_i \in [0,4^k)$。求序列的两个非空不交子区间，异或和相等或确定无解。

$0 \leq k \leq 17$。

解法：

性质很多，逐步挖掘。

首先，不交的限制绝大多数情况都没意义。如果找到两个相交子区间异或相等，当且仅当一个区间包含另一个且长度差为 $1$ 时无法构造不交的区间。

其次，我们断言必然有解。考虑反证。根据上述结论，容易知道每种区间异或和出现次数不超过 $2$ 次，否则有解。其次，考虑区间个数为 $\dfrac{2^{k+1}(2^{k+1}+1)}{2} > \dfrac{2^{2k+2}}{2}=2^{2k+1}=2\times 4^k$，每种异或结果不超过 $2$ 个，故至少有 $4^k+1$ 个不同区间异或，与题意矛盾。

最后，根据生日悖论，每次随机一个区间并计算异或和，加入 `map` 维护即可。复杂度 $O(2^{k+1}\operatorname{poly}(k))$。

[Submission Link.](https://codeforces.com/problemset/submission/1835/294788316)

---

## 作者：封禁用户 (赞：0)

你考虑我们对所有的正整数做前缀异或和操作，我们要做的就是找到四个数的异或和为 $0$（其中有两个数可以相同），然后我们就可以得到 $2^k+1$个数。我们将 $4^k$ 拆成前 $2^k$ 和后 $2^k$，我们至少有 $2^k+1$ 对数的异或和在二进制下前 $k$ 位为 $1$。

根据鸽巢原理，这 $2^k+1$ 对数一定可以凑出 $4$ 个数的异或和为 $0$。

我们怎么求呢？我们可以对于前 $k$ 位开一个桶，后 $k$ 位开一个 ```map``` 存数对（当然开桶也可以），然后对于每一对前 $k$ 位异或和为零的数对，存到后 $k$ 位的  ```map``` 中，如果当前位置已经有数对，就可以输出答案了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int NN = 1 << 20;
int t;
ll pre[NN];
ll tong[NN];
struct Pair{
	int a,b;
};
 
int main(){
	scanf("%d",&t);
	while(t--){
		int k;
		scanf("%d",&k);
		tong[0] = -1;
		map<ll,Pair> mp;
		for(ll i = 1,x; i <= (1 << (k+1)); ++i) scanf("%lld",&x),pre[i] = pre[i-1] ^ x,tong[i] = -1;
		for(int i = 0; i <= (1 << (k+1)); ++i){
			if(tong[pre[i] >> k] != -1){
				if(mp.count(pre[i] ^ pre[tong[pre[i] >> k]])){
					Pair x = mp[pre[i] ^ pre[tong[pre[i] >> k]]], y = {i,tong[pre[i] >> k]};
					int w[4] = {x.a,x.b,y.a,y.b};
					sort(w,w+4);
					printf("%d %d %d %d\n",w[0]+1,w[1],w[2]+1,w[3]);
					break;
				}
				else mp[pre[i] ^ pre[tong[pre[i] >> k]]] = {i,tong[pre[i] >> k]};
			}
			tong[pre[i] >> k] = i;
		}
	}
}
```

---

