# Replace by MEX

## 题目描述

You're given an array of $ n $ integers between $ 0 $ and $ n $ inclusive.

In one operation, you can choose any element of the array and replace it by the MEX of the elements of the array (which may change after the operation).

For example, if the current array is $ [0, 2, 2, 1, 4] $ , you can choose the second element and replace it by the MEX of the present elements — $ 3 $ . Array will become $ [0, 3, 2, 1, 4] $ .

You must make the array non-decreasing, using at most $ 2n $ operations.

It can be proven that it is always possible. Please note that you do not have to minimize the number of operations. If there are many solutions, you can print any of them.

 –

An array $ b[1 \ldots n] $ is non-decreasing if and only if $ b_1 \le b_2 \le \ldots \le b_n $ .

The MEX (minimum excluded) of an array is the smallest non-negative integer that does not belong to the array. For instance:

- The MEX of $ [2, 2, 1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3, 1, 0, 1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0, 3, 1, 2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the array, but $ 4 $ does not.

It's worth mentioning that the MEX of an array of length $ n $ is always between $ 0 $ and $ n $ inclusive.

## 说明/提示

In the first test case, the array is already non-decreasing ( $ 2       \le 2 \le 3 $ ).

Explanation of the second test case (the element modified by each operation is colored in red):

- $ a = [2, 1, 0] $ ; the initial MEX is $ 3 $ .
- $ a = [2, 1, {\color{red}{3}}] $ ; the new MEX is $ 0 $ .
- $ a = [ {\color{red}{0}} , 1, 3] $ ; the new MEX is $ 2 $ .
- The final array is non-decreasing: $ 0 \le 1 \le 3 $ .

Explanation of the third test case:

- $ a = [0, 7, 3, 1, 3, 7, 7] $ ; the initial MEX is $ 2 $ .
- $ a = [0, {\color{red}{2}}, 3, 1, 3, 7, 7] $ ; the new MEX is $ 4 $ .
- $ a = [0, 2, 3, 1, {\color{red}{4}}, 7, 7] $ ; the new MEX is $ 5 $ .
- $ a = [0, 2, 3, 1, {\color{red}{5}}, 7, 7] $ ; the new MEX is $ 4 $ .
- $ a = [0, 2, 3, {\color{red}{4}}, 5, 7, 7] $ ; the new MEX is $ 1 $ .
- The final array is non-decreasing: $ 0 \le 2 \le 3 \le 4 \le         5 \le 7 \le 7 $ .

## 样例 #1

### 输入

```
5
3
2 2 3
3
2 1 0
7
0 7 3 1 3 7 7
9
2 0 1 1 2 4 4 2 0
9
8 4 7 6 1 2 3 0 5```

### 输出

```
0

2
3 1
4
2 5 5 4
11
3 8 9 7 8 5 9 6 4 1 2
10
1 8 1 9 5 2 4 6 3 7```

# 题解

## 作者：Little_x_starTYJ (赞：33)

### 题目大意
令 $mex$ 为序列中最小的没有出现的数。

给你一个长度为 $n$ 的序列 $a$，你可以进行不超过 $2\times n$ 次操作，使得序列 $a$ 单调不降。每次操作你可以选定一个位置 $p$，并将 $a_p$ 赋值为 $mex$。请你输出总共的操作次数与每次操作的位置。
### 解题思路
题目说了，$\forall x \in a,0\le x\leq n$。所以，我们考虑将 $a$ 变为 $0,1,\cdots,n-1$。

我们在进行操作时，需分成两种情况讨论。
- 若 $mex \neq n$，由于最后的序列要满足 $a_i=i-1$，所以我们这里就将 $a_{mex+1}$ 赋值为 $mex$。
- 若 $mex = n$，那我们就找到序列中任意一个满足 $a_i \neq i - 1$ 的数，然后将其赋值为 $mex$。如果没有找到，说明现在的序列已经满足题意，不需要再进行操作了。

大概思路就是这样。瞟了一眼数据范围，发现 $n$ 比较小，于是我们在求 $mex$ 的值时可以暴力求解。

时间复杂度约为 $\mathcal{O}(n^2T)$。

### 简单证明

但是肯定有很多同学以为以上算法的操作次数可能大于 $2n$，在独立做这道题时把这个思路给扔了。

我们不妨简单理解一下。

由于我们每一次操作都把 $a_{mex+1} \to mex$，那么最多操作 $n$ 次就能使序列中出现了 $0\sim n - 1$ 这 $n$ 个数，只是不一定单调不降，所以我们需要再操作至多 $n$ 次，使得单调不降，总操作次数最大为 $2n$。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[1010], b[2010], vis[1010];
signed main() {
	ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
	int t, n;
	cin >> t;
	while (t--) {
		memset(vis, 0, sizeof vis);
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			vis[a[i]]++; 
		}
		int ans = 0;   //总共的操作次数
		/*
		最后
		a[i] = i - 1 
		*/
		while (1) {
			int mex = 0;
			for (int i = 0; i <= n; i++) {  //查找 mex
				if (!vis[i]) {
					mex = i;
					break;
				}
			}
			if (mex != n) {
				vis[a[mex + 1]]--;
				b[++ans] = mex + 1;
				a[mex + 1] = mex;
				vis[mex]++;
			} else {
                bool f = 0;
				for (int i = 1; i <= n; i++) {
					if (a[i] != i - 1) {
                        f = 1;
						vis[a[i]]--;
						a[i] = mex;
						vis[mex]++;
						b[++ans] = i;
						break;
					}
				}
                if (!f)  //序列合法，不需要再进行操作了
                    break;
			}
		}
		cout << ans << endl;
		for (int i = 1; i <= ans; i++)
			cout << b[i] << ' ';
		cout << endl;
	}
	return 0;
}
```

---

## 作者：xxgirlxx (赞：23)

### 更新日志

10 月 24 日：使用了更加精细的图片，增加了对操作次数的证明。

## 题外话

这题我们老师搬去当最后一题，虽然单组数据但是 $n \le 2\times 10^6$。我第一眼秒了，但是第二眼把正解否了，赛后打出来跑得飞快，我跑 699ms，第二名跑 921ms，std 跑 1.49s，这下变成小丑了······

## 题目大意

给你一个长度为 $n$ 的序列，并定义一次操作为选定一个数 $a_i$，将 $a_i$ 更改为该序列中没有的最小非负整数，要求操作次数不能大于 $2 \times n$ 次，求操作次数和每一此操作更改的数的位置。

## 题目思路

首先可以很明显的想到将整个序列更改为 $0$ 到 $n-1$。

然后既然能够更改 $2 \times n$ 次，很容易就能联想到将操作分成两部分，第一部分用来将所有的数都更改到 $0$ 到 $n-1$ 内且没有重复。第二部分就用来将所有的数都更改为 $0$ 到 $n-1$。

再想怎么操作，第一部分非常简单，只需要开一个数组记录出现的数组机器及其出现次数，然后扫一遍，如果说这个数字出现过了或者等于了 $n$，那么就进行一次操作。所有数字都检查一遍后，所有的数自然也就是 $0$ 到 $n-1$ 内且没有重复的了。

可是第二部分怎么办呢？

还是扫一遍序列，如果数字是正确的就不进行操作，如果是错误的，就进行一次操作，将其变为 $n$，这时，该位置原来的数字就空出来了，我们就可以把，这个数字原本改在的位置进行一次操作，让这个位置的数字变成正确的，然后这个位置原本的数字就空出来了，我们就可以继续操作，一直到回到开始的位置。

可能讲得比较抽象，画个图吧：

![](https://cdn.luogu.com.cn/upload/image_hosting/fr73jvz9.png)

我们扫到第二个位置的时候发现数字是错误的，于是进行操作，将其更改为 $n$：

![](https://cdn.luogu.com.cn/upload/image_hosting/x7w77fb7.png)

于是第二个位置原本的数字 $3$ 就空了出来，而 $3$ 原本是该在第四个位置的，所以我们对第四个位置进行操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/2l0pwh7s.png)

于是第四个位置原本的数字 $2$ 就空了出来，而 $2$ 原本是该在第三个位置的，所以我们对第三个位置进行操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/hsu2snmu.png)

于是第三个位置原本的数字 $1$ 就空了出来，而 $1$ 原本是该在第二个位置的，所以我们对第二个位置进行操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/ojaom49k.png)

因为已经回到了开始的位置二，所以操作停止。

可能有些人会觉得这样操作次数会超过 $2\times n$ 次（~~是的，我赛时就这么否掉的~~），但是仔细一看会发现：每一个环会多一次操作，而想要有一个环，就需要后面出现了这个数，那么这个位置就不需要进行第一轮的操作了，就可以补上第二轮多出来的一个操作了。

最后把代码写出来就可以啦！

复杂度约为 $O(n)$，但是常数有点屎，单组数据快但是多组数据偏慢。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+1;
int n,a[N],flag,b[N],num,sum,ans[N<<1],T,mp[N];
void work(){
	cin>>n,flag=0,num=0;
	for(int i=1;i<=n;++i)cin>>a[i],++mp[a[i]];
	for(int i=1;i<=n;++i){
		if(mp[a[i]]>1||a[i]==n){
			for(;flag<=n&&mp[flag]!=0;++flag);
			--mp[a[i]],a[i]=flag,++mp[a[i]],ans[++num]=i;
		}
		b[i]=a[i]+1;
	}
	for(int i=1;i<=n;++i){
		if(a[i]==i-1)continue;
		ans[++num]=i,sum=b[i];
		while(sum!=i)a[sum]=sum-1,ans[++num]=sum,sum=b[sum];
		ans[++num]=i;
	}
	cout<<num<<"\n";
	for(int i=1;i<=num;++i)cout<<ans[i]<<" ";
	cout<<endl;
	for(int i=0;i<=n;i++)mp[i]=0;
	return;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)work(); 
	return 0;
}
```

---

## 作者：Andrewzdm (赞：10)

读题时看到了这段话：
> Please note that you do **not** have to minimize the number of operations. If there are many solutions, you can print any of them.

可见是构造题无疑了。

也不知道为什么，经过尝试后就想到将数组变成 $[0,1,2,3,\dots,n-1]$ 的形式。

接下来我们想办法构造：  
**注：接下来的数组下标全部从 $1$ 开始。**
1. 如果当前某个数 $a_i=i-1$，我们后面就不要修改了；
2. 如果当前 $\operatorname{MEX}= n$，我们将任何一个不满足 $a_i=i-1$ 的 $a_i$ 替换为 $\operatorname{MEX}$；
3. 如果当前 $\operatorname{MEX}\neq n$，我们将 $a_{\operatorname{MEX}+1}$ 替换为 $\operatorname{MEX}$。

首先，每进行一次操作 $3$，就会固定一个 $a_i$ 的值，即 $a_i$ 不会再被操作。这是因为在该操作后，$\operatorname{MEX}$ 永远不可能等于 $a_i$，原因是 $\operatorname{MEX}$ 的定义。

其次，每个数最多被进行一次操作 $2$，因为如果我们进行了操作 $2$，那么 $n$ 在数组中没有出现过，进行过操作 $2$ 后 $\operatorname{MEX}$ 不可能为 $n$，在操作 $3$ 进行在该数上之前，此数不可能被再次替换。

综上，每个数最多被操作两次（变为 $n$ 后再变为 $i-1$），所以总操作个数最大为 $2n$，满足题目要求。

重复若干次如上所述的操作，直到数组变成 $[0,1,2,3,\dots,n-1]$ 即可。

由于数据范围比较小，所以很暴力地求 $\operatorname{MEX}$ 即可。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn = 1010;
int a[maxn], cnt, n;
bool vis[maxn], mark[maxn];
vector<int> op;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		cin >> n;
		fill(mark + 1, mark + n + 1, false);
		op.clear();
		cnt = n;
		for(int i = 1; i <= n; i++)
		{
			cin >> a[i];
			if(a[i] == i - 1)
			{
				mark[i] = true;
				cnt--; 
			} 
		}
		while(cnt)
		{
			int mex;
			fill(vis, vis + n + 1, false);
			for(int i = 1; i <= n; i++)
				vis[a[i]] = true;
			for(int i = 0; i <= n; i++)
				if(!vis[i])
				{
					mex = i;
					break;
				}
			if(mex == n)
			{
				for(int i = 1; i <= n; i++)
					if(!mark[i])
					{
						op.push_back(i);
						a[i] = mex;
						break;
					}
			}
			else
			{
				op.push_back(mex + 1);
				a[mex + 1] = mex;
				mark[mex + 1] = true;
				cnt--;
			}
		}
		cout << op.size() << endl;
		for(int i : op)
			cout << i << ' ';
		cout << endl;
	}
	return 0;
}
```

---

## 作者：BzhH (赞：7)

[博客内观看](https://www.cnblogs.com/A2484337545/p/15200354.html)

又是一道构造题，题目所求的是一个单调不降序列，并且要用不超过 $2n$ 的操作，
咋一眼看上去似乎没什么思路，但我们可以尝试一种构造方案，那就是令 $a_i=i-1$，这样的话这个序列就是一个单调上升的序列，满足题目要求，那么接下来的问题就是如何在 $2n$ 次操作内转化成这个序列，对于一个序列若他不满足 $[0,n-1]$ 的数都只出现了一次，那么它的 mex 必然在 $[0,n-1]$ 内，那么我们可以直接枚举 $n$ 次 mex，每次对 mex+1 的位置的数使用操作，这样就能在 $n$ 次内得到一个 $[0,n-1]$，都只出现了一次的序列，但它不一定满足上面的那个性质，所以对于每一个 $a_i=k\ne i-1$，对它使用一次操作 $a_i=n$，然后再对 $k-1$ 使用使用一次操作 $a_{k-1}=k$，如此循环，那么这个序列就能满足上面的条件了，并且操作数不会多于 $2n$。

代码
```
#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;

vector<int> ans;
int a[1005], tim[1005];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(tim, 0, sizeof(tim));
        ans.clear();
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++)
            tim[a[i]]++;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (!tim[j])
                {
                    ans.push_back(j + 1);
                    tim[a[j + 1]]--;
                    a[j + 1] = j;
                    tim[j]++;
                    break;
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (a[i] != i - 1)
            {
                int k = a[i] + 1;
                ans.push_back(i);
                a[i] = n;
                while (a[k] != k - 1 && k - 1 != n)
                {
                    ans.push_back(k);
                    int tmp = k;
                    k = a[k] + 1;
                    a[tmp] = tmp - 1;
                }
            }
        }
        printf("%d\n", ans.size());
        for (int i = 0; i < ans.size(); i++)
            printf("%d ", ans[i]);
        printf("\n");
    }
}
```

---

## 作者：Mine_King (赞：6)

在我的[博客](https://www.cnblogs.com/mk-oi/p/14044073.html)观看效果更佳。

## Problem

[CF1375D Replace by MEX](https://www.luogu.com.cn/problem/CF1375D)

题目大意：  
给你一个长度为 $n$,值域在 $[1,n]$ 的序列 $a$，每次操作可以将一个位置的数替换为当前序列的 $MEX$，请你让序列变成一个单调不降的序列，要求操作数在 $2n$ 以内。  
输出操作数和每次操作对应的位置，**不要求**操作数最少。

## Solution

既然不要求操作数最少，那么我们就可以尝试构造一个特殊的序列，比如 $0,0,\cdots,0$，$0,1,\cdots,n-1$ 或 $1,2,\cdots,n$ 等。    
第一种实现太难了些，所以我们尝试后两种。  
以 $1,2,\cdots,n$ 为例。  
首先，当一个数符合要求后，我们显然不会去改它。就算是出现了其他数都符合要求（指满足我们想要的结果，下同），剩一个数不同的情况，我们只要先让他变成当前的 $MEX$，如果当前 $MEX$ 刚好是我们想要的，就直接赋值完事，否则的话这个 $MEX$ 一定为 $0$，那么赋值之后就又变回第一种情况了，因为其他的数都已经把前面的那些数都填掉了。  
接下来我们对 $MEX$ 分类讨论。  

当 $MEX \not= 0$ 时，我们直接让 $a_{MEX}=MEX$ 即可。  
当 $MEX = 0$ 时，我们就把他赋到一个不符合要求的数中去。  

这样最后一定能得到我们想要的序列，接下来来检验他能否在 $2n$ 次操作内完成。  
显然一个数最多只会被操作两次。  
因为当把这个数赋值为 $0$ 后，除非让他符合要求，否则不会改变他，因为这时 $MEX$ 不可能会等于 $0$（只有等于 $0$ 时才可能对他再做一次操作）。  
于是操作次数最多为 $2n$，符合题意。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n,a[1005];
bool over[1005];//over[i]表示a[i]是否符合要求
int cnt,len,ans[2005];//cnt存有多少个数符合要求，len和ans存答案。
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		cnt=len=0;
		memset(over,false,sizeof(over));
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]==i) over[i]=true,cnt++;
		}
		while(cnt<n)
		{
			int mex;
			bool m[1005];
			memset(m,0,sizeof(m));
			for(int i=1;i<=n;i++) m[a[i]]=true;
			for(int i=0;i<=n;i++)
				if(!m[i]){mex=i;break;}
			if(mex==0)
			{
				for(int i=1;i<=n;i++)
					if(!over[i]){a[i]=0;ans[++len]=i;break;}
				continue;
			}
			a[mex]=mex;
			over[mex]=true;
			ans[++len]=mex;
			cnt++;
		}
		printf("%d\n",len);
		for(int i=1;i<=len;i++) printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}
```  

---

## 作者：Hisaishi_Kanade (赞：5)

首先看到 $n$ 个数，不停改成 $\text{mex}$，很直觉的想到最后会是 $0, 1, 2,\cdots,n-1$ 这样把。

大胆猜测一波，最后只有 $n$ 个数的话，我们或许可以通过改成 $\forall a_i,a_i=i-1$ 这种方式来达到要求。


那么这个构造就很自然了。每次求当前 $\text{mex}$，若 $\text{mex}=n$，则先判一遍是不是合法，否则就把不合法的位置改掉；否则就把 $a_{\text{mex}+1}$ 改掉就行。

为啥这个不超过 $2n$ 呢？我们考虑一个点最终会怎么变得合法呢，当然是被 $\text{mex}=i-1$ 时给搞掉了。这个最多是 $n$ 次肯定没问题。

考虑一共会有多少次把某个改成 $n$ 的情况？这种只有恰好取尽了 $0\sim n-1$ 才会出现，而这之后 $\text{mex}$ 会下降到小于 $n$。这个数从 $n$ 变成别的数是啥情况？当然是被 $\text{mex}=i-1$ 改掉了，而这之后他就不会再变。所以这种也是最多 $n$ 次。

没问题。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static int _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline int read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int N=3e5+5, inf=2e9;
const ll illf=1e18;
int a[N]; bool v[N];
int qt, n, i, j, k;
inline int mex()
{
	rep(i, 0, n) v[i]=false;
	rep(i, 1, n) v[a[i]]=true;
	rep(i, 0, n) if(v[i]==false) return i;
	assert(0); return -1;
}
int main()
{
	scanf("%d", &qt);
	while(qt--)
	{
		vector<int> ans;
		n=read(); rep(i, 1, n) a[i]=read();
		while(true)
		{
			int x=mex();
			if(x==n)
			{
				rep(i, 1, n) if(a[i]!=i-1) break;
				if(i>n) break;
				ans.emplace_back(i);
				a[i]=n;
			}else
			{
				ans.emplace_back(x+1);
				a[x+1]=x;
			}
		}
		printf("%d\n", ans.size());
		for(auto x : ans) printf("%d ", x);
		puts("");
	}
}

```

---

## 作者：TernaryTree (赞：4)

构造 $a_i=i-1$。若当前 $\rm mex$ 为 $n$ 则改变第一个 $a_i\neq i-1$ 的位置，否则 $a_{\textrm{ mex}+1}=\rm mex$。每个 $a_i$ 最多改成一次 $n$，且改为 $i-1$ 后不变，操作最多 $2n$，能过。

---

