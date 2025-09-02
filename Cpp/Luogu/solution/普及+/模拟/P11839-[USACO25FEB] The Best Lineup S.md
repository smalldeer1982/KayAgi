# [USACO25FEB] The Best Lineup S

## 题目描述

Farmer John 有 $N$（$1 \leq N \leq 2 \cdot 10^5$）头奶牛排成一条队伍 $a$。队伍 $a$ 中从前到后第 $i$ 头奶牛编号为一个整数 $a_i$（$1 \leq a_i \leq N$）。可能存在多头奶牛编号为同一整数。

FJ 将以以下方式构造另一条队伍 $b$：

- 初始时，$b$ 为空。
- 当 $a$ 非空时，移除 $a$ 最前面的奶牛，并选择是否将该奶牛添加到 $b$ 的最后。

FJ 想要构造队伍 $b$，使得 $b$ 中从前到后的编号序列是字典序最大的（见脚注）。

在 FJ 构造队伍 $b$ 之前，他可以执行以下操作至多一次：

- 选择队伍 $a$ 中的一头奶牛，并将其移动至当前位置之前的任意位置。

假设 FJ 以最优方式执行至多一次上述操作，输出他可以达到的字典序最大的 $b$ 的编号序列。

每个测试点将包含 $T$（$1 \leq T \leq 100$）个独立的测试用例。

## 说明/提示

样例 1 解释：

在第一个测试用例中，FJ 可以将第五头奶牛移动到第二头奶牛之后。现在，$a = [4, 3, 3, 2, 1]$。可以证明，$[4, 3, 3, 2, 1]$ 也是字典序最大的 $b$。

在第二个测试用例中，FJ 可以将第四头奶牛移动到队伍的最前面。

在第三个测试用例中，FJ 不需要执行任何操作。他可以通过将除第二头奶牛之外的每头奶牛添加到 $b$ 的最后来构造 $b$。可以证明，这得到了字典序最大的 $b$。

- 测试点 $2\sim 4$：$N \leq 100$。
- 测试点 $5\sim 8$：$N \leq 750$。
- 测试点 $9\sim 18$：没有额外限制。

### 脚注

我们知道，序列 $s$ 的字典序大于序列 $t$ 当且仅当以下条件之一成立：
- 在 $s_i \neq t_i$ 的第一个位置 $i$ 处，有 $s_i > t_i$。
- 当不存在这样的 $i$ 时，$s$ 的长度大于 $t$。

## 样例 #1

### 输入

```
3
5
4 3 2 1 3
6
5 1 2 6 3 4
6
4 1 3 2 1 1```

### 输出

```
4 3 3 2 1
6 5 4
4 3 2 1 1```

# 题解

## 作者：XGTD (赞：12)

# 题解：P11839 [USACO25FEB] The Best Lineup S

## Preface

提供一种 $O(n)$ 贪心解法，自认为比官解更好理解，代码也非常好写。

[视频题解。](https://www.bilibili.com/video/BV12mP3e5ECM/?spm_id_from=333.1387.homepage.video_card.click&vd_source=e30c5bf3cf935b96ec8bab557be3afbd)

9 场银组，~~我终于 Au 了~~。分数线才 700 分？~~这应该是 2020 年以来最简单的一场银组了~~。

## Problem Statement

[P11839](https://www.luogu.com.cn/problem/P11839)。
有一个序列，给你一次操作改变原序列顺序的机会，让你从前往后每个数可以选或不选，构造一个字典序最大的序列。

## Solution

首先，由于是要最大化字典序，显然是从最大的开始，能选就选。

因此对原数组按照元素大小为第一关键字降序排序，原位置为第二关键字升序排序（至于为什么等会解释）。然后就贪心的从前往后能选就选（因为字典序吗，前面更优就总体更优）。

如何判断能不能选呢？记录一个 $max1$ 和一个 $max2$， 分别代表已经选了的中，原位置最靠后的（$max1$），和已经选了的中原位置第二靠后的（$max2$）。

此时发现对于一个每一个元素 $i$，想选他则他必须要么在所有已经选了的元素之后出现，也就是 $pos_i > max1$，**或者已经选了的里面只有一个原位置比它靠后**，也就是 $max1 > pos_i > max2$。如果这样我们则可以通过用掉我们有的一次操作来把那个那个唯一一个比 $i$ 靠后的元素挪到 $i$ 前面。如果连 $max2$ 都比 $i$ 靠后，或者我们已经用了一次操作的机会了，则只能跳过 $i$ 不选了。

但是我们只有一次操作，怎么确保把它用到最优的 $i$ 上呢？其实第一次需要就用就行了。因为假设我们第一次需要的时候不用，而是跳过这个 $i$，那不管后面选的有多优，字典序都一定不可能更大了。因为我们是根据元素值的大小排的序。

但别忘了最后还有两个元素相同的情况，这种情况下我们之所以要以初始位置为第二关键字升序排序就是为了不会在两个相同的元素上因为位置反了而浪费掉操作的机会。

## Code
实现非常简单，记录 $max1$ 和 $max2$，以及是否用过操作机会就行了。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T1, n, a[200005];
pair<int, int> val[200005];
int cmp(pair<int, int> &x, pair<int, int> &y){
	if(x.first != y.first)return x.first > y.first;
	else return x.second < y.second;
	//if they have different value, return bigger one, otherwise
	//return the one that appeared earlier
}
signed main(){
	cin>>T1;
	while(T1--){
		cin>>n;
		for(int i = 1; i <= n; i++){
			cin>>a[i];
			val[i].first = a[i];
			val[i].second = i;
		}
		int ma = 0, ma2 = 0, moved = 0, outp = 0;
		sort(val + 1, val + n + 1, cmp);
		for(int i = 1; i <= n; i++){
			if(val[i].second > ma){
				ma2 = ma;				
				ma = val[i].second;
				if(outp)cout<<" "<<val[i].first;
				else cout<<val[i].first;
				outp = 1;
			}else if(val[i].second > ma2 && !moved){
				ma = val[i].second;
				//we move ma
				if(outp)cout<<" "<<val[i].first;
				else cout<<val[i].first;
				outp = 1;
				moved = 1;
//				cout<<val[i].second<<endl;
			}
		}
		cout<<endl;
	}
	return 0;
}

```

赛时代码，略丑。

## After thought

这场真的有点简单了，~~我都怀疑 USACO 是不是故意放水，打算再加一个组呀？就像 2015 年加白金之前放水那样。~~

求赞。

---

## 作者：hanyu0722 (赞：3)

### 题目链接

[P11839 [USACO25FEB] The Best Lineup S](https://www.luogu.com.cn/problem/P11839)

### 题目做法

这里提供一种时间复杂度为 $O(n \log{n}) $ 的做法。

使用一个结构体，存储每头奶牛的编号以及奶牛的位置。   
读入该数组后，以**编号不同则编号大的优先、编号相同则位置小的优先**的顺序排序。

这样，我们就可以遍历一遍数组。当遇到有一头奶牛的位置在其之前两头奶牛中间时，此时，我们本不应选取该奶牛进入队伍 $b$，但我们可以将该奶牛的前一头奶牛前移，使得该奶牛可以进入队伍 $b$。

### 代码时间


[link](https://www.luogu.com.cn/record/206012162)

code

```cpp
#include<bits/stdc++.h>
using namespace std;
//usaco S 1
int n;
struct cow{
	int num;
	int wei;
} a[200005]; 
bool cmp(cow x,cow y){
	if (x.num==y.num) return x.wei<y.wei;
	else return x.num>y.num; 
}
void work(){
	cin>>n;
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i].num);
		a[i].wei=i;
	}
	sort(a+1,a+1+n,cmp);
	int prepr=0,prer=0,nowl=0;
	for (int i=1;i<=n;i++){
		if (a[i].wei>a[prer].wei){
			prepr=prer;
			prer=i;
		}
		if (a[prepr].wei<a[i].wei && a[i].wei<a[prer].wei){
			a[prer].wei=a[prepr].wei;
			break;
		}
	}
	//for (int i=1;i<=n;i++) cout<<a[i].wei<<" ";
	//cout<<endl;
	int pre=-1,prew=0;
	for (int i=1;i<=n;i++){
		if (a[i].wei>=prew){
			if (pre!=-1) printf("%d ",pre);
			prew=a[i].wei;
			pre=a[i].num;
		}
	}
	printf("%d\n",pre);
}
int main(){
	int t;
	cin>>t;
	while (t--) work();
	return 0;
}

```

---

## 作者：littlebug (赞：3)

讲一下赛时思路吧。

## Solution

先求出来字典序最大的子序列，用个 ST 表贪心地维护（~~我是唐诗忘了这个可以直接后缀最大值线性做~~）。然后找一个数插入原序列前面，使答案更大。

想到可以贪心地从大到小选数，然后想应该插入到哪里，如果选的是 $a_i$，应该插入到 $a_j$ 前面，那么 $i>j$ 就直接做；$i<j$ 则如果在子序列中 $i,j$ 相邻（把 $i$ 按照原数组中的位置 $i$ 插入后），那么可以通过把 $j$ 换到 $i$ 前面来完成；否则就不能做了。

然后发现样例没过，原因是把 $j$ 换到前面之后形成的子序列可能比只塞上一个 $a_i$ 更大（指字典序）。

这时候以为做法假了，或者处理会非常麻烦，但是细想了下，好像这样做就是最优的，毕竟保证了将最大的且**最靠前的**可能插入的插入了嘛，所以把 $j$ 换到 $i$ 前面再跑一遍字典序最大子序列就可以了。

## Code

注意排序顺序，也不知道谁因为这个挂了好几发。

```cpp
int n,a[MAXN],aa[MAXN];
bitset <MAXN> c;
vector <pii> ans,b;

class __spare_table
{
private:
	int *a,n;
	int lg2[MAXN],v[MAXN][MAXlg],d[MAXN][MAXlg];
	
	il void init_lg2(){lg2[1]=0; rep(i,2,n) lg2[i]=lg2[i>>1]+1;}
	il void init_st()
	{
		rep(i,1,n) v[i][0]=a[i],d[i][0]=i;
		int x,y;
		rep(i,1,MAXlg-2) rep(j,1,n-(1<<i-1)) 
		{
			x=j,y=j+(1<<(i-1));
			v[x][i-1]>=v[y][i-1] ? (v[j][i]=v[x][i-1],d[j][i]=d[x][i-1]) : (v[j][i]=v[y][i-1],d[j][i]=d[y][i-1]);
		}
	}
	
public:
	il void init(int *_a,int _n){a=_a,n=_n; init_lg2(),init_st();}
	il int q(int l,int r){int t=lg2[r-l+1],x=l,y=r-(1<<t)+1; return v[x][t]>=v[y][t] ? d[x][t] : d[y][t];}
} s;

il void calc(int *a,int n) // 计算一个数组的字典序最大的子序列，直接 O(n) 维护后缀最大值即可，但是某人脑抽使用了 ST 表做到了 O(n log n) 的复杂度，并且码量多了 6737151 倍。
{
	c=0,a[0]=a[n+1]=0;
	
	s.init(a,n);
	int l=0;
	while(l<n) c[l=s.q(l+1,n)]=1;
}

il void solve(int __Ti)
{
	read(n),_::r(a,n);
	
	c=0,clr(ans),clr(b);
	
	calc(a,n);
	rep(i,1,n) c[i] ? (ans.pb(a[i],i),1) : (b.pb(a[i],i),1);
	sort(all(b),[](const auto a,const auto b){return a.st==b.st ? a.nd<b.nd : a.st>b.st;});
	
	int ind;
	for(auto x:b)
	{
		ind=lower_bound(all(ans),x,[](const auto a,const auto b){return a.st==b.st ? a.nd<b.nd : a.st>b.st;})-ans.begin();
		if(ind==1 || x.nd>ans[ind-1].nd || (x.nd<ans[ind-1].nd && x.nd>ans[ind-2].nd))
		{
			int tot=0;
			if(ind>1) rep(i,1,ans[ind-2].nd) aa[++tot]=a[i];
			aa[++tot]=ans[ind-1].st;
			rep(i,x.nd,n) i!=ans[ind-1].nd && (aa[++tot]=a[i]);
			
			calc(aa,tot);
			clr(ans);
			rep(i,1,n) c[i] && (ans.pb(aa[i],i),1);
			
			break;
		}
	}
	
	for(auto x:ans) write(x.st," \n"[x==ans.back()]);
}
```

---

华风夏韵，洛水天依！

---

## 作者：ZHR100102 (赞：2)

感觉有点直觉又有点难的贪心题。

# 观察

观察答案，根据直觉，不难发现我们最后的答案一定是将序列中的元素从大到小排序后选出的。同时，如果两个元素值相等，那么我们一定会选位置在前面的那个元素。

因此，我们可以先用结构体存每个元素，然后每个元素以值为第一关键字从大到小排序，位置为第二关键字从小到大排序。然后实时维护一个当前位置 $pos$，只有当前元素的位置大于 $pos$ 时才能选进答案序列中。

# 反悔

考虑把一个元素往前提的操作，显然是将答案序列中的某个元素对 $pos$ 的贡献去掉，然后重新计算 $prepos$ 后的贡献。其中 $prepos$ 指上一个 $pos$ 的值，可以看做是对 $pos$ 进行了一次撤销操作。

因为只能往前提一次，所以这个操作也只会进行一次。同时因为一个数字不会向后移动，所以我们反悔的也只能是将选的前一个反悔掉（也就是用掉这一次机会），即条件是一个数能反悔当且仅当他的位置 $x$ 满足 $prepos< x< pos$，这就规避了我们将最后一个数字向后移动的特判。

那么我们什么时候会反悔呢？显然是第一个满足反悔条件的。因为反悔选值更大的数肯定比选更小的数更优。

于是排序后模拟即可，时间复杂度 $O(n\log n)$。注意到数字的值域较小，可以用桶排序来达到 $O(n)$ 的复杂度，但是我太懒了。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=200005;
int n,now,lst;
bool flag;
struct Node{
    int pos,v;
    bool operator<(const Node &x)const{
        if(v!=x.v)return v>x.v;
        return pos<x.pos;
    }
}a[N];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].v;
        a[i].pos=i;
    }
    sort(a+1,a+n+1);
    now=lst=flag=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i].pos>now)
        {
            lst=now;
            now=a[i].pos;
            cout<<a[i].v<<" ";
        }
        else if(flag==0&&lst<a[i].pos)
        {
            flag=1;now=a[i].pos;
            cout<<a[i].v<<" ";
        }
    }
    cout<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：FZY_CZY (赞：2)

又是某老师办的模拟赛上见到的，感觉题目还是很有趣的，需要一些思维能力。

[题目](https://www.luogu.com.cn/problem/P11839) 在这里←。

# 思路
根据题目的要求，我们很自然就会有一个想法，就是先给原数组赋值到另一个数组 $f$ 上面，$f$ 数组从大到小排序，找到第一个 $f_i \ne a_i$，将 $f_i$ 插入到 $a_i$ 前，并记录此时的 $t=i$。

我们可以提前用一个二位数组（用 map 实现）来记录，$m_{i,j}$ 表示 $i$ 在 $a$ 数组中第 $j$ 次出现的位置，也就是我们还需要一个 $cnt$ 数组，来记录每一个数字出现的频率，这样，我们就可以知道我们插入的 $f_i$ 在 $a$ 数组中什么位置。

在做完上面这个操作后，我们可以继续遍历 $f$ 数组，将每一个 $f_i \ne a_i$ 的 $f_i$ 记录下来，并判断 $f_i$ 在 $a$ 中的位置是否在上一个我们找到的 $f_i$ 之前，如果是的话，我们就标记该数字在 $a$ 中的 $a_j$，最后按照次序输出满足 $i\le t$ 或者被标记过的 $a_i$。

我们来思考一下这个思路是否正确，比如在面对数据 `6 1 1 5 2 4` 的时候，我们的正解应该是将 $4$ 移到 $2$ 之前，就构成了 $b$ 数组的 `6 5 4 2`，但是按照我们的思路，我们的答案应该是 `6 5 4`，这样，我们就被 hack 了。

那我们来思考为什么是错的。

根据这组 hack 数组，我们发现，$5$ 不需要移动，它移动了之后，没有使得答案变得更优，所以是没有意义的，所以我们找到的 $i$ 还需要是第一个移动有意义的 $i$。

那么我们来重新设计这道题的思路。

我们从后往前，用 $f_i$ 记录 $[i,n]$ 中 $a_i$ 的 $\max$，这个时候我们发现，如果 $f_i = a_i$，则我们可以输出 $a_i$，从字典序最大的要求可以推导出该结论，因为此时在所有选择中，该选择的作用是最大的，即字典序最大。

因为我们的移动是有意义的，所以必须是在 $f_i = a_i$ 的前提下，然后我们保留一个区间最大值以及这个最大值的位置 $t$，如果我们这个区间最大值 $\ge f_{i+1}$，那么说明我们此次移动可以将序列变长（增加该区间最大值为其中一个元素），是有意义的，那么我们就移动 $a_i$ 到 $a_t$ 之前，并且退出循环。

我们在更新后，再次用 $f_i$ 记录 $[i,n]$ 中 $a_i$ 的 $\max$，此时我们已经完成了移动一个数的事情，所以如果 $f_i=a_i$，我们将 $a_i$ 赋值给 $b_i$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
int T;
int n;
int a[N],f[N];
signed main(){
    cin>>T;
    while (T--)
	{
    	scanf("%d",&n);
        int t=0,mvis=0;
        //t表示如果有一个数是某一个区间最大值，那么t作为该区间的左端点
        //mvis表示上述顶一下，该区间的最大值
        f[n+1]=0;
        for (int i=1;i<=n;i++) scanf("%d",&a[i]);
        for (int i=n;i>=1;i--) f[i]=max(a[i],f[i+1]);
        for (int i=1;i<=n;i++)
		{
            if (f[i]==a[i])
			{
                if (mvis>=f[i+1])
				{
                    for (int j=i;j>t+1;j--)
						swap(a[j],a[j-1]);
					//将a[i]插入到a[t]之前
                    break;
                }
                t=i;
                mvis=0;
            }
            else mvis=max(mvis,a[i]);
        }
        for (int i=n;i>=1;i--)
        //重复后缀区间最大值的操作
			f[i]=max(f[i+1],a[i]);
        for (int i=1;i<=n;i++)
			if (a[i]==f[i])
			//判断是否是子序列的一部分
				printf("%d ",a[i]);
        puts("");
    }
    return 0;
}
``````

---

## 作者：qhr2023 (赞：2)

## solution

一道贪心。

对于不执行操作，我们从大到小选且保证下标递增即可。

对于执行之多一次操作，也是从大到小选。

若 $b$ 序列是 ```p q```，从大到小选到 $t$ 了，不选的话序列不变，选 $t$ 的话分类讨论。
* 若 $t$ 的下标大于 $q$，显然选 $t$ 更优，序列变成 ```p q t```。
* 若 $t$ 的下标小于 $q$ 但大于 $p$，选 $t$ 序列变成 ```p t q```，对 $q$ 操作，序列变成 ```p q t```，这是更优的。
* 若 $t$ 的下标小于 $p$，此时选要 $t$ 序列变成 ```t p q```，对 $p$ 执行操作，序列就变成 ```p t q```，这种情况不选 $t$ 更优。

综上，我们的贪心策略是从大到小选且保证下标递增，特别的，对遇到的第一个，下标小于 $b$ 序列中最后一个，但大于倒数第二个的元素也选。

实现上，由于元素都不大于 $n$，所以排序可以用桶排，时间上更优一些。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, a[200005], b[200005];
vector<int> v[200005];
int main() {
	for (cin >> T; T--; cout << '\n') {
		cin >> n;
		for (int i=1; i<=n; ++i)
			cin >> a[i], 
			v[a[i]].push_back(i);
		b[0]=1, b[1]=0;
		for (int i=n, f=1; i>=1; --i)  
			for (int j:v[i]) 
				if (j>b[b[0]])
					b[++b[0]]=j;
				else if (j>b[b[0]-1]&&f)
					b[++b[0]]=j, f=0;
		for (int i=2; i<=b[0]; ++i)
			cout << a[b[i]] << ' ';
		for (int i=1; i<=n; ++i)
			v[i].clear();
	}
	return 0;
}
```

---

## 作者：Z_Z_Y (赞：2)

### 题目描述
有一个长为 $n$ 的数列，现可将其中一个数移动到它当前位置前的任意一位，求操作后可能得到的字典序最大的子序列。
### 分析
首先设 $ma_i$ 为 $\max(a_j) (j\in i\sim n)$ 如果一个数 $a_i$ 满足 $a_i=ma_i$ 则为了字典序最大，显然它必须计入答案。那么当且仅当上一个这样的数到 $a_i$ 间有至少一个数（即至少最大数）满足这个数大于等于 $ma_{i+1}$，将它移到上一个数后面才有用。  
理由很简单，因为字典序要最大，所以如果这中间的最大数都不到 $ma_{i+1}$，那么答案不会变，操作无用。而在保持 $a_i$ 对答案有贡献的前提下（如果 $a_i$ 在上一个数前面，则要么 $a_i$ 被浪费掉，要么答案不变），肯定越靠前越好。   
由于只能操作一次，所以找到第一个满足条件的 $a_i$ 即可，将数列操作后求一下答案就没了，只需遍历几次数列，由于多测，时间复杂度 $O(Tn)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans[200005],ma[200005],a[200005];
int read(){
	int r=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))r=(r<<1)+(r<<3)+(ch&15),ch=getchar();
	return r*f;
}
int main(){
	t=read();
    while(t--){
    	n=read();
    	ma[n+1]=0;
    	for(int i=1;i<=n;i++)a[i]=read(); 
	    for(int i=n;i;i--){//倒序处理i~n的最大值
	    	if(ma[i+1]<a[i])ma[i]=a[i];else
	    	ma[i]=ma[i+1];
		}
		int Ma=0,lst=0;//分别为上一个数~这个数中间的最大值，上一个数的位置（用于交换操作）
	   for(int i=1;i<=n;i++){//操作
	   	 	if(a[i]==ma[i]&&Ma>=ma[i+1]){
	   	 		for(int j=i;j>lst+1;j--)a[j]=a[j-1];
	   	 		a[lst+1]=ma[i];
	   	 		break;
			}else if(a[i]==ma[i])Ma=0,lst=i;else
	   	if(a[i]>Ma)Ma=a[i];
	   }
	    for(int i=n;i;i--){//由于数列变动重新处理i~n的最大值
	    	if(ma[i+1]<a[i])ma[i]=a[i];else
	    	ma[i]=ma[i+1];
		}
	   int k=0;
	   for(int i=1;i<=n;i++)if(a[i]==ma[i])ans[++k]=a[i];//处理答案
		  for(int i=1;i<=k;i++)
	    if(i!=k)printf("%d ",ans[i]);else
	    printf("%d",ans[i]);
	    if(t)printf("\n");
	}
	return 0;
} 
``````

---

## 作者：PDAST (赞：1)

## 题目大意
有一个序列，你可以做一次如下操作：将一个数插入这个数前面的位置（包括自己的位置）。求操作完后的字典序最大的该序列的子序列。
## 思路
我们发现，对于一个为从自己往后所有数的最大值的数，如果到前面的更大数之间没有不小于后面最大值的数时，向前调换是没有意义的，因为在你调换之后，如果被你因插入而向后排的数中，比后面任意数要小，那么都会为了子序列的字典序最小而删去，我们要找到第一个调换有意义的数进行调换，才能保证最优，否则后面的就会覆盖前面的，找到之后，求一个字典序最大的子序列（即由比后面的数都大的数组成的子序列）即可。
## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define ac() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[100000];
inline int read(){
    register int x=0,f=1;
    char ch=ac();
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=ac();
    }
    while(isdigit(ch))x=x*10+ch-48,ch=ac();
    return x*f;
}
int T,n,m;
const int inf=-0x3f3f3f3f,N=2e5+5;
int a[N],maxn[N];
signed main(){
    // freopen("lineup.in","r",stdin);
    // freopen("lineup.out","w",stdout);
    T=read();
    while(T--){
        int n=read(),h=0,maxx=0;
        maxn[n+1]=0;
        for(int i=1;i<=n;++i)a[i]=read();
        for(int i=n;i>=1;--i)maxn[i]=max(a[i],maxn[i+1]);
        for(int i=1;i<=n;++i){
            if(maxn[i]==a[i]){
                if(maxx>=maxn[i+1]){
                    for(int j=i;j>h+1;j--)swap(a[j],a[j-1]);
                    break;
                }
                h=i;
                maxx=0;
            }
            else maxx=max(maxx,a[i]);
        }
        for(int i=n;i>=1;i--)maxn[i]=max(maxn[i+1],a[i]);
        for(int i=1;i<=n;i++)if(a[i]==maxn[i])cout<<a[i]<<" ";
        cout<<"\n";
    }
}

~~~

---

## 作者：hinin (赞：1)

[更好的阅读体验，包括银组前二](https://www.cnblogs.com/hinin/articles/18731858)。

# T1：The Best Lineup

### 题意
给定一个序列 `a`，将其中**任意一个**元素向前调，之后选取一个序列，使得字典序最大。

### 思路

第一眼贪心，但单纯贪心最大值不对，~~否则那还叫银组吗~~。

你每次贪心是可能会出现一次无效操作，如序列 `4 1 9 8 6 1 6`，此处应该移动的是最小的 `1`。

正解：

先生成一个目前来说字典序最大序列，之后通过调换，使得这个序列变大。

先对奶牛按编号从大到小排序，若编号相同则按原位置从小到大排序。

仍然是贪心（？）。

记录前一个候选元素、当前候选元素的索引，遍历指针。

1. 当前候选元素的位置大于后续元素的位置
    * 如果当前候选元素的位置比后续元素的位置更靠后，说明此时存在更优的移动机会。
	* 将当前候选元素的位置修改为上个候选的位置，并结束（仅允许一次操作）。

2. 当前候选元素的位置小于等于后续元素的位置
    * 说明后续元素的位置更优，更新指针，继续向后寻找更优的候选。

### 代码

``` cpp
// By Hinin（Neko233）
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "-funroll-all-loops")
#define ll long long
#define pii pair<int, int>

#define y1 kairiki
#define x first
#define y second

#define repeat(x, a, b) for(int x = a; x <= b; x ++)
#define rpless(x, a, b) for(int x = a; x >= b; x --)
#define repeatl(x, a, b) for(int x = a; x < b; x ++)
#define rplessr(x, a, b) for(int x = a; x > b; x --)

using namespace std;

const int N = 2e5 + 5;
pii a[N];
int T, n, x;

bool cmp(const pii & a, const pii & b)
{
	if (a.first != b.first) { return a.first > b.first; }

	return a.second < b.second;
}

int main()
{
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); 
	
	cin >> T;

	while (T --) {
		cin >> n;

		repeat(i, 1, n) {
			cin >> x;
			a[i] = {x, i};
		}

		sort(a + 1, a + n + 1, cmp);

		for (int pre = 0, now = 1, i = 2; i <= n; i++) {
			if (a[now].second > a[i].second) {
				if (a[pre].second < a[i].second) {
					a[now].second = a[pre].second;
					break;
				}
			} else { pre = now, now = i; }
		}

		cout << a[1].first;

		for (int i = 2, Max = a[1].second; i <= n; i ++) {
			if (a[i].second >= Max) {
				cout << " " << a[i].first;
				Max = a[i].second;
			}
		}

		cout << endl;
	}

	return 0;
}
```

---

## 作者：SunsetVoice (赞：1)

贪心题浪费一大堆时间最后没切数学题遗憾离场了，如此水平，如何 OI？

先想想没有操作怎么做，这是一个经典的贪心，字典序的性质直接保证了贪心的正确性，故先按值域压一遍后从大到小贪着取即可。

考虑操作。下称没有操作的序列为“原序列”。

充分手造几组样例。我们发现：

- 原序列的数一定都是要选的。
- 原、新序列一定不升。
- 新加的数一定都是原序列中两个数中间的一段数，且比后一个数大，新选的满足单调不升。

综上，直接在原序列的两个相邻的数之间仿照原序列找然后加上就可以了，这是 $O(n)$ 的。

又因为要尽量大，所以新加的数要尽可能在前面，找到合法的加数区间直接退。

就做完了。

细节：

- 新加的数不降。
- 最后一段单独维护，比较好的方式是在原数列加最后一个 $0$。

就过了，记得多测清空。
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int T,n,a[500001] = {0};
vector<int>e[500001];
int ans[500001] = {0},ansn = 0;
int tans[500001] = {0},hjx = 0;
signed main(){
	cin.tie();
	cout.tie();
	cin>>T;
	a[500000] = 0;
	while(T--){
		cin>>n;
		hjx = 0;
		for(int i = 0;i<=n;i++){
			while(e[i].size()>0)e[i].pop_back();
		}
		for(int i = 1;i<=n;i++)cin>>a[i];
		for(int i = 1;i<=n;i++){
			e[a[i]].push_back(i);
		}
		e[0].push_back(n);
		ansn = 0;
		int dpos = 0;
		for(int i = n;i>=1;i--){
			for(int v:e[i]){
				if(v>dpos){
					dpos = v;
					ans[++ansn] = v;
				}
			}
		}
		a[n+1] = 0;
		ans[++ansn] = n+1;
		int lstpos = 0,l = ans[ansn-1],r = n;
		for(int i = 1;i<=ansn;i++){
			if(a[ans[i]]!=a[ans[i+1]]){
				bool fl = 0;
				for(int j = lstpos+1;j<ans[i];j++){
					if(a[j]>=a[ans[i+1]]){
						fl = 1;
						break;
					}
				}
				if(fl==1){
					l = lstpos;
					r = ans[i];
					break;
				}
			}
			lstpos = ans[i];
		}
		for(int i = 1;i<ansn;i++){
			tans[++hjx] = a[ans[i]];
			if(ans[i]>l and ans[i]<=r){
				int lst = l;
				for(int j = a[ans[i]]-1;j>=a[ans[i+1]];j--){
					for(int v:e[j]){
						if(v>lst and v<r){
							lst = v;
							tans[++hjx] = j;
						}
					}
				}
			}
		}
		for(int i = 1;i<hjx;i++){
			cout<<tans[i]<<" ";
		}
		cout<<tans[hjx];
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：沃若 (赞：1)

这道题从下标考虑，比从原数列的数值考虑会简单很多。

先考虑如果不能移动奶牛，那么最优策略就是从前到后贪心选择剩下后缀里的最大值，形成一个单调不增的序列。**换句话说：从大到小依次选择这些数字，同时保证选择的下标单调递增。**

例如第二组样例：`5 1 2 6 3 4`。我们先选择 `6`，接着发现 `5` 不能选了（下标比刚才的小），所以只能选择 `4`。

再考虑可以向前移动一只奶牛：对于本来不能选择的 `5`，如果把刚才选过的 `6` 向前移动就可以完美解决。

所以我们依然从大到小依次选择这些数字，如果下标大于刚才选的最后一个下标，就可以选择。否则，**如果小于最后一个下标但大于倒数第二个下标，则可以把最后选的那个数字向前移动，这样也可以选择。**

算法的正确性读者自证不难，关键在于要求字典序最大，所以从大到小处理时，遇到第一个能移动的，立刻移动就是最优。

时间复杂度：$O(n)$。

空间复杂度：$O(n)$。

代码（C++17）：

```cpp
#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a[200005];
vector<int> v[200005];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	for (cin >> t; t--; ) {
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i], v[a[i]].push_back(i);
		vector<int> p{0};
		for (int i = n, flag = 1; i >= 1; i--) {
			for (const auto& j : v[i]) {
				if (j > p.back())
					p.push_back(j);
				else if (j > p[p.size() - 2] && flag)
					p.push_back(j), flag = 0;
			}
		}
		for (size_t i = 1; i < p.size(); i++)
			cout << a[p[i]] << "\n "[i + 1 < p.size()];
		for (int i = 1; i <= n; i++)
			v[i].clear();
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

显然，如果没有向前移动的操作，那么我们就是将所有的数从大到小排序之后，如果 $p$ 在 $lp$ 后就直接输出对应的值，并更新 $lp=p$，否则直接抛弃。

但是有向前移动的操作怎么办呢？我们注意到，我们只会向前移动一次。因此我们会将机会分配给最大的，最需要的而且可行的点，向前移动来被输出。

这样的点满足什么条件呢？我们将初始状态下排好序后的序列令为 $a$，记录这一位置的原始下标。当我们发现 $p$ 出现在被选中的最后一个 $p$ 之前，并且在被选中的倒数第二个 $p$ 之后时，就可以最后一个 $p$ 前移使之能被输出即可。

模拟一下就好了。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n; bool cn;
struct node {
	int p, v;
	node(int pi = 0, int vi = 0) :p(pi), v(vi) {};
	inline bool operator<(const node& r) {
		return v != r.v ? v > r.v:p < r.p;
	}
}a[200005]; vector<node>ps;
int main() {
	ios::sync_with_stdio(0);
	for (cin >> t; t; t--) {
		cin >> n; ps.clear();
		for (int i = 1; i <= n; ++i)
			cin >> a[i].v, a[i].p = i;
		sort(a + 1, a + n + 1); 
		ps.emplace_back(a[1]); cn = 1;
		for (int i = 2; i <= n; ++i)
			if (a[i].p < ps.back().p) {
				if (cn && (ps.size() < 2 || a[i].p > ps[ps.size() - 2].p))
					cn = 0, ps.emplace_back(a[i]);
			}
			else ps.emplace_back(a[i]);
		for (int i = 0; i != ps.size(); ++i)
			cout << ps[i].v << " \n"[i == ps.size() - 1];
	}
}
```

---

## 作者：rich_xty (赞：1)

首先我们先来了解一下如何比较字典序的大小：从左到右逐个比较对应的数字或字母的大小来比较。

也就是说，我们首要保证的并不是我们所构造出来的序列的长度，而是在保证让大数在前面的同时，尽量让序列变长，而且必须是一个单调不上升子序列（因为如果某个位置上的数比它前面的一些数要大，还不如将它前面那些比它小的数删掉）,并且我们的这个子序列的最后一个一定也是 $a$ 数组中的最后一个 为了尽可能使子序列变长）。

我们先不考虑换位操作，直接求出目前的字典序最大的 $b$（代码中存在了 $c$ 数组中）。

接下来我们来考虑在什么时候可以进行交换操作。因为我们要让字典序尽可能大，所以我们应该优先从大数进行评估。不难发现：在未进行操作前的 $b$ 数组中，如果对于一个数 $b[i]$ ,在它与前一个数 $b[i−1]$ 之间，有大于等于它的数，就可以与那个数（在这个区间内大于等于它的最前面的数）进行交换操作。

最后我们只要在 $a$ 数组中模拟一下交换，然后再求一遍就可以了。

---
细节标注在代码里了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,ma,mai,cnt;
int a[200020],b[200020];
struct node{
	int sum,id;
}c[200020];
void work(){
	memset(c,0,sizeof(c));//记得要清空
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	ma=mai=cnt=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
		if(a[i]>ma){
			ma=a[i];
			mai=i;
		}
	} 
	for(int i=n;i>=1;i--)//倒序求会好写一点
		if(a[i]>=c[cnt].sum) c[++cnt].sum=a[i],c[cnt].id=i;
	for(int i=1;i<=cnt/2;i++) swap(c[i],c[cnt-i+1]);
	for(int i=1;i<=cnt;i++){
		int f=0;
		for(int j=c[i-1].id+1;j<c[i].id;j++){
			if(a[j]>=c[i+1].sum && !f) f=j;//寻找区间内第一个大于等于a[j]的数
		}
		if(f){
			for(int j=c[i].id-1;j>=f;j--) a[j+1]=a[j];
			a[f]=c[i].sum;//模拟交换，然后强制结束循环
			break;
		}
	}
	cnt=0;
	for(int i=n;i>=1;i--)//再求一遍
		if(a[i]>=c[cnt].sum) c[++cnt].sum=a[i];
	for(int i=cnt;i>1;i--) cout<<c[i].sum<<' ';
	cout<<c[1].sum<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>t;
	while(t--) work();
	return 0;
}
```

---

## 作者：Colinxu2020 (赞：1)

首先考虑通过 $a$ 数组构造 $b$ 数组的本质是什么，容易发现题目里给的一大长串的本质是求 $a$ 的一个字典序最大的子序列，当 $a$ 固定时，不妨贪心的去求，不断向后跳到能跳的最大值中最靠前的。

考虑如何调整是最优的，这里我们令 $p_i$ 为按上面的方法跳了 $i$ 次的结果，特别的，$p_0=0$，讨论如果我们确定了要调整一个位置应当如何调整，不难发现，我们一定会尽可能的往前调整，但如果太往前调 $\leq p_{i-1}$ 的时候，就会导致这个位置被浪费掉，因为会选择更后面的，所以应该调整到 $p_{i-1}+1$ 的位置，接下来只需讨论要调整哪个位置即可。

考察在什么时候进行贪心调整是有贡献的，我们对于每一个位置 $i$，求出假如将他按上述方法调整后得到的位置 $p'_i$，若调整前与调整后能挑到的点是不一样的，则说明我们取得了不调整更优的解法，所以选择调整这个点，因为字典序的贪心性质，所以我们从小到大考虑位置，注意不能错误把 $p_i$ 算成 $p'_i$ 会跳到的点。

考虑优化求这个位置的过程，用一个 ST 表维护区间最大值。注意也需要考虑修改第一位的情况，然后就做完了。

考虑为什么这么做是对的，显然调整前后所得到的值不变（否则会直接选择更大的那个值），因此实际上只有位置变了，这就给予了后面更大的发挥空间，而如果我们将这个操作机会留到后面，那么能够给予的发挥空间就变小了，所以我们会贪心的选择尽可能早的调整。

考虑到建 ST 表的复杂度，总体复杂度为 $O(n \log n)$。

```cpp
#include<iostream>
#include<cmath>
using namespace std;

const int maxn=2e5+10,lg=20;
int n,ai[maxn],st[maxn][lg];

int maxx(int x, int y){ return (ai[x]>ai[y]||(ai[x]==ai[y]&&x<y))?x:y; }
void build(){
    for(int i=1;i<=n;i++)st[i][0]=i;
    for(int j=1;j<lg;j++)for(int i=1;i+(1<<j)-1<=n;i++)st[i][j]=maxx(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int query(int l, int r){
    if(l>r)return 0;
    int k=log2(r-l+1);
    return maxx(st[l][k],st[r-(1<<k)+1][k]);
}
void move(int from, int to){
    for(int i=from;i>to;i--)swap(ai[i], ai[i-1]);
}
int main(){
    int T; cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>ai[i]; build();
        int secondary=0,mxpos=query(1,n);
        for(int i=1;i<=n;i++)if(i!=mxpos&&ai[i]>ai[secondary])secondary=i;
        if(query(mxpos+1,n)!=secondary){
            move(mxpos,1);
        }else{
            for(int i=mxpos;i!=n;i=query(i+1,n)){
                int x=query(i+1,n);
                if(query(x+1,n)!=maxx(query(i+1,x-1),query(x+1,n))){
                    //cout<<i<<endl;
                    move(x,i+1);
                    break;
                }
            }
        }
        //for(int i=1;i<=n;i++)cout<<ai[i]<<' '; cout<<endl;
        build();
        for(int i=query(1,n);i;i=query(i+1,n)){
            cout<<ai[i]<<" \n"[i==n];
        }
    }
}
```

---

## 作者：iced_tea543 (赞：0)

## 题目大意：
我们来看看 2 月银组的第一题。这一题我个人认为是三道题里面最难的一道。

FJ 有两个队列 $a$ 和 $b$，操作 $a$ 得到一个字典序最大的 $b$。
流程是这样的：
1.FJ 可以移动队伍里的**至多一头**奶牛到其目前位置之前的位置；
2.接下来，FJ 可以每次将 $a$ 队列的队头出队，选择将其入队 $b$ 或直接扔掉。

## 题解：

对于操作 1 怎么移动奶牛，我们可能目前没有什么思路。那不妨先看看操作 2——假设我们已经以最优方式移好了奶牛。

很显然，比较字典序大小的原则我们都是知道的：两个数组从第一个元素开始往后比，如果不同，则当前**元素大者**字典序较大；如果到较短的数组结尾所有元素都相同，则**较长者**字典序大。

Eg1

>1 2 3 4 5 较小  
1 2 4 4 5 较大


Eg2

>1 2 3 4 5 较大  
1 2 3 较小
>

知道了字典序比较，怎么使得字典序最大呢？我们不妨取一个数据看看。

Eg3

>5 ~~1 2~~ 6 ~~3~~ 4

发现没有，我们从前往后过，如果发现目前的数比前面的数大，则一定会把前面的数吞掉，因为这样才会使得序列最优。如 $2$ 会吞掉 $1$，$6$ 会吞掉 $2$，$4$ 会吞掉 $3$……直到碰到一个大于等于它的数，就停止了。于是，很容易想到用单调栈维护。只用过一遍，效率就是 $O(n)$。

接下来，我们可以返回操作 1，看看移动奶牛的最优策略是什么。可以再找个数据看看。

Eg4

>1 2 3 7 1 1 4

在这个例子里面，很显然需要移动的数据是 $4$，因为发现这个操作可以拯救出两个 $1$ 不被 $4$ 吞掉。为什么不是 $7$ 呢？因为就算 $7$ 移动到最开头，其他的数也全都会被 $4$ 吞掉。于是，最优策略就非常明显了——就是拯救能拯救的数的集合里面最大的那个数。

于是，另一个问题出现了，什么是能拯救的数呢？首先能被拯救的数一定是会被吞掉的数。然后观察发现，因为只能移动一次，所以只有这个数后面比它大的数的数量恰为 $1$ 时，这个数可以被拯救。在这个例子里面，$1$、$2$、$3$ 均不能被拯救，因为他们后面有 $7$ 和 $4$，一共两个数，不论移动哪一个都是救不了他们的。但是两个 $1$ 都可以被拯救，因为他们后面只有一个 $4$。那么把 $4$ 一直往前移动直到 $7$ 即可（超过 $7$ 就亏了，因为它自己也被吞了）。

## 算法：
对于要拯救的数，我们要首先考虑的问题便是如何统计一个数后面又多少个比它大的数。因为需要比它大，所以考虑桶，因为桶——如果从后往前查——可以统计出目前后面的所有数的数量，然后我们只需要找比这个数大的数的数量不就行了吗？那么如何找出比目前的数大的所有数呢？观察发现，每次操作无非有两个：把桶的对应位置加 $1$，以及求出目前这个数到桶顶的所有数的和。

>点修 + 区查 -> 考虑树状数组。

不过需要注意一点，这里的树状数组是和正常的树状数组反过来的：我们需要求的是比目前整个数组位置后面的所有数的和而不是前面的。代码上要注意把所有的全部反过来。

这里树状数组的效率是 $O(\log{n})$。

那么，我们把 $a$ 数组从后往前遍历，同时判断目前的树状数组的查询如果等于 $1$，则和前面的最大值比一下，因为我们需要拯救最大的数，同时记得记录目前的最大值，因为如果后面只有一个数比它大，说明一定是目前最大的数。

把那个统计出来的目前最大的数后面的最大的数往前挪，碰到大于等于它的数为止。
最后挪好之后的数组用单调栈维护即可。

最后，该算法总的效率应当是：$O(T\times n\times \log{n})$。

注意每一轮数组都要初始化！

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans[(int)2e5 + 5];

#define lowbit(x) (x & -x)
#define N (2e5 + 1)
long long s[(int)2e6 + 1];
void change(int x, int c) {
	while (x)
		s[x] -= c, x -= lowbit(x);		
}
int query(int x) {
	int ret = 0;
	while (x <= N)
		ret -= s[x], x += lowbit(x);
	return ret;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		fill(s, s + (int)2e5 + 1, 0);
		fill(ans, ans + (int)2e5 + 1, 0);
		int n;
		cin >> n;
		vector<int> a = vector<int>();
		a.push_back(-1);
		for (int i = 1, v; i <= n; i++)
			cin >> v, a.push_back(v);

		int id = a.size() - 1;
		int maxn = -1, change_index = -1;
		for (int i = a.size() - 1; i > 0; i--)
		{
			if (a[id] < a[i])
				id = i;
			if (query(a[i] + 1) == 1)
				if (maxn < a[i])
					maxn = a[i], change_index = id;
			change(a[i], 1);
		}

		int i = change_index - 1;
		if (change_index == -1)
			goto skip;

		for (; a[change_index] > a[i] and i > 0; i--);

		a.insert(a.begin() + i + 1, a[change_index]);
		a.erase(a.begin() + change_index + 1);

		skip:

		stack<int> s = stack<int>();
		for (auto i : a)
		{
			while (!s.empty() and s.top() < i)
				s.pop();
			s.push(i);
		}

		int index = s.size() - 1, size = s.size();
		while (!s.empty())
			ans[index--] = s.top(), s.pop();

		for (int i = 0; i < size; i++) {
			cout << ans[i];
			if (i != size - 1)
				cout << ' ';
			else
				cout << endl;
		}
	}
}
```

---

## 作者：Your_Name (赞：0)

## 题解

首先我们不考虑修一次，那么我们要字典序最大显然就是从开头，每次选后缀最大的位置。

例如 `1 2 3 2 1`，我们就可以依次选出 `3 2 1`。

那么我们考虑带修。

观察发现我每次相当于往后跳，并且略过一些数字。

又因为我们前面走过的数是一定要选的，且顺序不能改变，所以我们操作当前数就相当于我们不略过当前位置和前面一个位置之间的数。

因此，我们要考虑这中间的一段数什么时候可以产生贡献呢？

其实就是这一段数在当前位置移动后能变成新的下一个位置。

这么说可能有点抽象，我们来举个例子：

`5 1 2 6 3 4` 如果我们不考虑修的话即选 `6 4`。

可是我们发现，在从下标 $1$ 跳到 $4$ 去选 $6$ 的过程中我们略过了 $5$。

而如果我们不跳过 $5$，那么他将成为 $6$ 的新的下一个位置。

也就是他对答案产生了贡献。

那么我们归纳一下，到底什么时候他可以产生贡献呢？

设我们不考虑代修时选出来的下标为 $v$ 数组。

那么，如果存在一个 $x$ 使得 $\max_{i=v_{x-1}+1}^{v_x-1} a_i\ge a_{v_{i+1}}$ 那么把 $v_x$ 移动到 $v_{x-1}$ 的后面就是优的。

但是题目规定只能移一次，我们怎么知道移哪个更优呢？

其实这个也是简单的，只要我们按顺序遍历 $v$ 数组，最先一个能产生贡献的一定是最优的，正确性显然。

因为我们相当于让更靠近选出子序列开头的元素大了。

求区间 $\max$ 用 ST 表即可，代码实现细节注意不要让 $v$ 数组重复，判断时注意越界即可。    

### AC_Code

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, INF = 1e9;
int T, n, a[N], mx[N], m, f[N][20];
int get(int l, int r){
    if(l > r)return -INF;
    int len = r - l + 1;
    int k = log2(len);
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}
vector<int> v, ans;
void sol(){
    m = 0;
    mx[n + 1] = 0;
    for(int i = n; i >= 1; i --){
        mx[i] = mx[i + 1];
        if(m <= a[i]){
            m = a[i];
            mx[i] = i;
        }
    }
    for(int j = 1; j <= n; j ++){
        if(v.empty() || (!v.empty() && mx[j] != v.back()))v.push_back(mx[j]);
    }
}//建立v数组
void bu(){
    for(auto j : v){
        ans.push_back(a[j]);
    }
    if(v.back() != n){
        for(int j = v.back() + 1; j <= n; j ++){
            ans.push_back(a[j]);
        }
    }
}//放答案
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while(T --){
        ans.clear();
        cin >> n;
        m = 0;
        for(int i = 1; i <= n; i ++){
            cin >> a[i];
            f[i][0] = a[i];
        }
        for(int k = 1; k < 20; k ++){
            for(int i = 1; i <= n; i ++){
                if(i + (1 << (k - 1)) - 1 <= n)f[i][k] = max(f[i][k - 1], f[i + (1 << (k - 1))][k - 1]);
                else break;
            }
        }
        v.clear();
        v.push_back(0);
        sol();
        v.push_back(n + 1);
        a[n + 1] = 0;
        for(int i = 0; i + 2 < v.size(); i ++){
            if(get(v[i] + 1, v[i + 1] - 1) >= a[v[i + 2]]){
                int k = a[v[i + 1]];
                for(int j = v[i + 1]; j > v[i]; j --){
                    a[j] = a[j - 1];
                }
                a[v[i] + 1] = k;//把v[i+1]移到v[i]后面
                v.clear();
                sol();
                bu();
                break;
            }
        }
        if(ans.empty())bu();//没有可以修的就不修
        for(int i = 0; i < ans.size(); i ++){
            if(ans[i] == 0)continue;
            if(i != ans.size() - 1)cout << ans[i] << ' ';
            else cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
```
_完结撒花。_

---

