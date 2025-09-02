# Berland Music

## 题目描述

Berland Music is a music streaming service built specifically to support Berland local artist. Its developers are currently working on a song recommendation module.

So imagine Monocarp got recommended $ n $ songs, numbered from $ 1 $ to $ n $ . The $ i $ -th song had its predicted rating equal to $ p_i $ , where $ 1 \le p_i \le n $ and every integer from $ 1 $ to $ n $ appears exactly once. In other words, $ p $ is a permutation.

After listening to each of them, Monocarp pressed either a like or a dislike button. Let his vote sequence be represented with a string $ s $ , such that $ s_i=0 $ means that he disliked the $ i $ -th song, and $ s_i=1 $ means that he liked it.

Now the service has to re-evaluate the song ratings in such a way that:

- the new ratings $ q_1, q_2, \dots, q_n $ still form a permutation ( $ 1 \le q_i \le n $ ; each integer from $ 1 $ to $ n $ appears exactly once);
- every song that Monocarp liked should have a greater rating than every song that Monocarp disliked (formally, for all $ i, j $ such that $ s_i=1 $ and $ s_j=0 $ , $ q_i>q_j $ should hold).

Among all valid permutations $ q $ find the one that has the smallest value of $ \sum\limits_{i=1}^n |p_i-q_i| $ , where $ |x| $ is an absolute value of $ x $ .

Print the permutation $ q_1, q_2, \dots, q_n $ . If there are multiple answers, you can print any of them.

## 说明/提示

In the first testcase, there exists only one permutation $ q $ such that each liked song is rating higher than each disliked song: song $ 1 $ gets rating $ 2 $ and song $ 2 $ gets rating $ 1 $ . $ \sum\limits_{i=1}^n |p_i-q_i|=|1-2|+|2-1|=2 $ .

In the second testcase, Monocarp liked all songs, so all permutations could work. The permutation with the minimum sum of absolute differences is the permutation equal to $ p $ . Its cost is $ 0 $ .

## 样例 #1

### 输入

```
3
2
1 2
10
3
3 1 2
111
8
2 3 1 8 5 4 7 6
01110001```

### 输出

```
2 1
3 1 2
1 6 5 8 3 2 4 7```

# 题解

## 作者：让风忽悠你 (赞：6)

[原题](https://www.luogu.com.cn/problem/CF1622B)

## 题意

给出一个数列 $p$，要求一个数列 $q$，给每个数一个类型，数列 $q$ 满足 $\sum\limits_{i=1}^n|p_i-q_i|$ **且**每个类型 0 的数都小于类型 1 的数。

## 做法

先从全部数的类型都相同开始想，不难想到当每个 $q_i$ 的都和 $p_i$ 一样时 $\sum\limits_{i=1}^n|p_i-q_i|$ 最小。

考虑到数列连续不重复的性质，可以将每个数所对应的位置记录下来，再将数列排序，这样就可以升序进行构造，在填到相应的位置。

进一步的，当数列有两种类型时可以考虑将 0 和 1 分开来处理，具体的就看代码吧。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#define N 200005 

using namespace std;

int T,n,cnt;
struct node{
	int p,idx;
}a[N];
int q[N];
bool pd[N];
char ch;

inline bool cmp(const node &a,const node &b){
	return a.p<b.p;
} //按照数值从小到大 

int main(){
	scanf("%d",&T);
	while(T--){
		cnt=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i].p);
			a[i].idx=i;// 记录位置 
		}
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++){
			scanf(" %c",&ch);
			pd[i]=(ch=='0'); //记录类型 
		}
		for(int i=1;i<=n;i++)
			if(pd[a[i].idx])
				q[a[i].idx]=++cnt; 
		for(int i=1;i<=n;i++)
			if(!pd[a[i].idx])
				q[a[i].idx]=++cnt;
		//分类型构造 
		for(int i=1;i<=n;i++)
			printf("%d ",q[i]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：_lmz_ (赞：2)

## 题目大意：
给定序列 $p$，以及一个 01 串 $s$，请构造一个序列 $q$。

序列 $q$ 满足：

1. 对于 01 串 $s$ 来说，每一个 0 位置上的元素要比 1 位置上的元素少。
2. $\sum\limits_{i=1}^{n}|p_i-q_i|$ 的值最小。

## 思路：
从条件入手：要使 $\sum\limits_{i=1}^{n}|p_i-q_i|$ 的值最小，我们要尽量然 $p_i=q_i$，所以我们构造的时候最好直接使用原数。

再看第一个条件：这个也很简单，先构造 0，再构造 1，因为题目问的是序号，所以 0 位置的序号是严格小于 1 位置的序号的。

---

## 作者：a_girl (赞：1)

[CF1622B Berland Music](https://www.luogu.com.cn/problem/CF1622B)

## 题意
给定一个长度为 $n$ 的数组 $a$ 表示评分，和长度为 $n$ 的 只包含 $0$ 和 $1$ 串 $s$ ，其中，$0$ 表示不好听，$1$ 表示好听。现在对他们重新进行排序，排序并评分。

## 思路
拿一个结构体，分别储存评分，喜爱度和序号，因为要排序，然后我们以喜爱度从大到小排序，算出每个数离最后的长度，再来一次排序，按序号从小到大排序，最后输出这个数离最后的长度。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int a,b,id,s;
}x[200005];
int t,n; 
char c； 
bool cmp(node x,node y)
{
	if(x.b!=y.b) return x.b>y.b;
	else return x.a>y.a;
}
bool cmp2(node x,node y)
{
	return x.id<y.id;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>x[i].a;
			x[i].id=i;
		}
		for(int i=1;i<=n;i++)
		{
			cin>>c;
			x[i].b=c-'0':
		}
		sort(x+1,x+n+1,cmp);
		for(int i=1;i<=n;i++) x[i].s=n-i+1;
		sort(x+1,x+n+1,cmp2);
		for(int i=1;i<=n;i++) cout<<x[i].s<<" ";
		cout<<endl;
	}
	return 0； 
} 
```

---

## 作者：tzjahinie (赞：1)

### 题目链接：[CF1622B](https://www.luogu.com.cn/problem/CF1622B)

### 题目大意：

将一个有序序列根据优先级重新排序后，使所有数在原序列的编号减去新序列的编号的绝对值求和后最小，输出新序列。

### 题目思路：

使所有歌的原预测得分减去新预测得分的绝对值求和后最小，即使原歌的预测得分尽量不变，可证明（证明如下）。可以考虑记录 $1$ 的数量为 $cnt$。根据题目要求，在新预测得分中，若 Mooncarp 对第 $i$ 首的歌的评价为 $1$，则这首歌一定在前 $cnt$ 名，反之亦然。将原序列根据预测得分排序后，对第 $i$ 首歌，有三种情况。

1. 这首歌的原预测得分符合 Mooncarp 对这首的歌的评价，此时预测得分不变。
1. 这首歌的原预测得分高但 Mooncarp 对这首的歌的评价为 $0$，此时预测得分应变低。
1. 这首歌的原预测得分低但 Mooncarp 对这首的歌的评价为 $1$，此时预测得分应变高。

可以观察到，情况二与情况三相反，可以推测预测得分变低的歌与预测得分变高的数量相等，易得。分别将符合情况二和情况三的歌一一交换位置，可得到符合题目要求的新预测得分，易得。

### 证明：
设第 $i,j,k$ 首歌的原预测评分分别为
 $a_i,a_j,a_k(a_i>a_j>a_k)$，Mooncarp 对第 $i,j,k$ 首歌的评价分别为 $0,1,0$。若将第 $i$ 和第 $j$ 首歌互换，则差距为 $2*|a_i-a_j|$。若将第 $i$ 和第 $j$ 首歌和第 $k$ 首歌互换，则差距为 $|a_i-a_j|+|a_j-a_k|+|a_i-a_k|$。易得：第一种情况的差距小于第二种情况的差距，证毕。

### code
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int v[3][200005];
struct node{
	int k,f,id;
}a[200005];
bool cmp1(node a,node b){
	return a.k>b.k;
}
bool cmp2(node a,node b){
	return a.id<b.id;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for (int i=1;i<=n;i++){
			scanf("%d",&a[i].k);
			a[i].id=i;
		}
		string str;
		int cnt=0;
		cin>>str;
		for (int i=0;i<n;i++){
			a[i+1].f=str[i]-'0';
			if(a[i+1].f==1){
				cnt++;
			}
		}
		sort(a+1,a+n+1,cmp1);
		int cnt1=0,cnt2=0;
		for (int i=1;i<=n;i++){
			if(cnt<i&&a[i].f==1){
				v[1][++cnt1]=a[i].id;
			}
			else if(i<=cnt&&a[i].f==0){
				v[2][++cnt2]=a[i].id;
			}
		}
		sort(a+1,a+n+1,cmp2);
		for (int i=1;i<=cnt1;i++){
			swap(a[v[1][i]],a[v[2][i]]);
		}
		for (int i=1;i<=n;i++){
			printf("%d ",a[i].k);
		}
		puts("");
	}
}
~~~

---

## 作者：Xdl_rp (赞：1)

solution
------------

- 首先，因为 $1$ 的歌曲评分高于 $0$ 的歌曲，如果有 $k$ 首歌是 $0$，那么将 $1$ 到 $k$ 给这 $k$ 首歌，再将 $k + 1$ 到 $n$ 给剩下的 $n - k$ 首歌。
- 其次，考虑同样是 $0$ 的 $k$ 首歌具体如何评分，由于要使得分差的绝对值尽可能小，所以将 $1$ 给这 $k$ 首歌原来预测评分最低的，$2$ 给原来预测评分次低的……依此类推。$1$ 的 $n - k$ 首歌也类似给分。
- 复杂度就是排序的复杂度 $O(N \log N)$

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int v, id;
}a[200005];
node sm[200005], bi[200005];
int ans[200005];
bool cmp(const node& x, const node& y) {
	return x.v < y.v;
}
signed main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i].v;
			a[i].id = i;
		}
		string s;
		cin >> s;
		int rs = 0, rb = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '0') {
				sm[++rs] = a[i + 1];
			}
			else {
				bi[++rb] = a[i + 1];
			}
		}
		sort(sm + 1, sm + rs + 1, cmp);
		sort(bi + 1, bi + rb + 1, cmp);
		for (int i = 1; i <= rs; i++) {
			ans[sm[i].id] = i;
		}
		for (int i = 1; i <= rb; i++) {
			ans[bi[i].id] = rs + i;
		}
		for (int i = 1; i <= n; i++) cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}
```


---

## 作者：ArrogHie (赞：1)


## 题意

给定一个 $1$ 到 $n$ 的排列 $a$，再给定一个 $01$ 串 $s$，需要构造出一个排列 $b$，使得对于任意一个满足 $s_i=1,s_j=0$ 的数对 $(i,j)$，满足  $b_i>b_j$，且 $\sum_{i=1}^n|a_i-b_i|$ 的值最小

## 题解

设 $s$ 中 $0$ 的个数为 $l$，因为对于所有 $s_i=1,s_j=0$ 的数对 $(i,j)$，满足 $b_i>b_j$，所以在 $0$ 的位置上只能填 $[1,l]$ 区间内的数，$1$ 的位置上只能填 $[l+1,n]$ 区间内的数。于是把 $0$ 和 $1$ 分离形成两个序列，对这两个序列分别求解即可。

相当于把问题转换成一个序列 $a$，构造出一个序列 $b$ 满足 $\sum_{i=1}^n|a_i-b_i|$ 的值最小，其中 $b_i$ 的范围为 $[1,l]$ 或者 $[l+1,n]$。结论即为构造出一个 $b$ 使得对于任意一个满足 $a_i<a_j$ 的数对 $(i,j)$，满足 $b_i<b_j$。

## 证明

对于任意一个满足 $a_i<a_j$ 的数对 $(i,j)$，考虑将较小的数填入 $b_i$ 还是 $b_j$，假设预备填入的两个数为 $x,y$，其中 $x<y$ 且 $a_i<x,a_j<y$。将 $a_i,a_j,x,y$ 四个数在数轴上表示

![](https://s2.loli.net/2021/12/29/oCYRKmP1yA4fNur.png)

其中将 $x$ 填入 $b_i$，将 $y$ 填入 $b_j$，则答案为红线部分的长度

![](https://s2.loli.net/2021/12/29/HPfi93waZVA8Mtr.png)

将 $x$ 填入 $b_j$，将 $y$ 填入 $b_i$，则答案为绿线部分的长度

![](https://s2.loli.net/2021/12/29/kVbH3uY65sShGd7.png)

显然是将 $x$ 填入 $b_i$ 更优，对于其他三种 $x,y$ 与 $a_i,a_j$ 的大小关系，也可以用同样的方法证明，故将较小的数填入 $b_i$ 更优

---

## 作者：MAX007_CRN (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1622B)

一道简单的结构体排序，适合新手练习。

## 思路

先定义一个结构体，分别储存歌曲序号，评分和喜爱程度。然后从大到小快排一下喜爱程度，计算一下分数。然后再从小到大排一下序号，输出即可。

## 代码

##### 只贴重要部分，防抄。

**排序函数：**

```cpp
bool cmp1(node x1, node y1) {
	if (x1.y != y1.y) return x1.y > y1.y;
	else return x1.x > y1.x;
}
bool cmp2(node x1, node y1) {
	return x1.id < y1.id;
}
```

**重要部分：**

```cpp
cin>>k;
while (k--) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x;
		a[i].id = i;//统计编号
	}
	for (int i = 1; i <= n; i++) {
		cin >> c;
        a[i].y = c - '0':
	}
	sort(a + 1, a + n + 1, cmp1);
	for (int i = 1; i <= n; i++) a[i].s = n - i + 1;
	sort(a + 1, a + n + 1, cmp2);//这个应该没人不会写吧
	for (int i = 1; i <= n; i++) cout << a[i].s << " ";
	cout << endl;
}
```

---

## 作者：shiziyu111 (赞：0)

## 题目大意
给定一个长度为 $n$ 的数组 $a$ 表示评分（保证评分从小到大排序为 $1$ 到 $n$），和长度为 $n$ 的 $0/1$ 串 $s$，其中，$0$ 表示不好听，$1$ 表示好听。

现在对他们重新进行排序，以 $1/0$ 优先排序，评分次之。

求最后的评分（也要求包含 $1$ 到 $n$ 的所有数）。
## 分析

先定义一个结构体，分别储存评分，喜爱程度和其所代表的歌曲序号（因为要用快排）。

然后再叫出快排小能手，先排 $1/0$，再排评分。

最后就可以快乐的把序号排回去，输出新评分，就可以快快乐乐的 AC 了。
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct laoxu{
	int zo,frankk,num; 
}rankk[200005];
bool cmp(laoxu a,laoxu b)
{
	if(a.zo==b.zo)
	{
		return a.frankk<b.frankk;
	}
	return a.zo<b.zo;
}

int main()
{
	int T;
	cin>>T;
	for(int k=1;k<=T;k++)
	{
		int n,erank[200005];
		char a;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>rankk[i].frankk;
			rankk[i].num=i; 
		}
		for(int i=1;i<=n;i++)
		{
			cin>>a;
			if(a=='1')
			{
				rankk[i].zo=1;
			}
			else
			{
				rankk[i].zo=0;
			}
		}
		sort(rankk+1,rankk+1+n,cmp);
		for(int i=1;i<=n;i++)
		{
			erank[rankk[i].num]=i;
		}
		for(int i=1;i<=n;i++)
		{
			cout<<erank[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Harm_zoneQ (赞：0)

## 题意

各位 dalao 都有题意了就不说了。

## 分析
本题答案共两个条件，我们可以分开分析

1.要使 $ \sum\limits_{i=1}^n |p_i-q_i| $ 为最小值，经过简单的计算可以得到： $p_i$ 越接近 $q_i$，$ \sum\limits_{i=1}^n |p_i-q_i| $ 的值就越小，因此我们要尽量让 $q_i$，$p_i$ 的值接近。

2.在代入第一个条件，将 0 和 1 的情况区分。

 Code 大差不差，看其他佬的也都差不多，
撒花！

---

## 作者：hcy1117 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1622B)
## 思路
题目要求所有 Mooncarp 喜欢的歌曲的预测得分都必须大于 Mooncarp 不喜欢的歌曲的预测得分，所以先将所有数按 $s_{i}$ 降序排序。

接下来想到要使 $\sum_{k=1}^n|p_{i}-q_{i}|$ 最小，可以贪心地按 $p_{i}$ 从大到小排序（不知道会不会被卡，个人证不出来，不过能过，[提交记录](https://www.luogu.com.cn/record/166083254)）。这样就可以了。

还有不懂的可以参考代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,op,id;//x记录p[i] 
}a[200005];
int b[200005];
bool cmp(node x,node y)
{
	if(x.op==y.op)return x.x>y.x;
	return x.op>y.op;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i].x,a[i].id=i;
		string s;
		cin>>s;
		for(int i=1;i<=n;i++)a[i].op=(s[i-1]=='1');
		sort(a+1,a+n+1,cmp);
		for(int i=n;i>=1;i--)
		{
			b[a[n-i+1].id]=i;
		}
		for(int i=1;i<=n;i++)cout<<b[i]<<" ";
		cout<<"\n";
	}
}
```

---

## 作者：lmz_ (赞：0)

## 题目大意：
给定序列 $p$，和一个 01 串 $str$，求序列 $q$，并且使 $\sum\limits_{i=1}^{n}|p_i-q_i|$ 最小。

我们设 $i (1 \leq i \leq n)$，再设 $j(1\leq j \leq n)$，如果 $str_i=0$ 并且 $str_j=1$，那么 $q_j$ 必定大于 $q_i$。
## 做法：
我们可以发现，要使 $\sum\limits_{i=1}^{n}|p_i-q_i|$ 最小，我们要让 $p_i$ 和 $q_i$ 最接近，最好可以相等。

我们先把序列 $p$ 里面的每一个元素标记位置，再排序，最后从 $1$ 到 $n$ 构造序列 $q$。

---

## 作者：Noby_Glds (赞：0)

这道题的贪心还是很容易想出来的。

我们给歌曲排序时，把喜欢和不喜欢作为第一标准，让不喜欢的歌排到后面去。

接着把初始评分作为第二标准，让评分高的歌排到前面去。

因为很显然，如果初始评分分别为 $2$ 和 $1$ 的歌，如果评分调换，差距会更大。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct hhh{
	int a,b,bh,ans;//a为初始评分，b为是否喜欢，ans为最终评分
}p[200005];
int t,n;
char c;
bool cmp(hhh x,hhh y){
	return x.b!=y.b?x.b>y.b:x.a>y.a;
}
bool cmp2(hhh x,hhh y){
	return x.bh<y.bh;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>p[i].a,p[i].bh=i;
		for(int i=1;i<=n;i++){
			cin>>c;
			p[i].b=c-'0';
		}
		sort(p+1,p+n+1,cmp);
		for(int i=1;i<=n;i++) p[i].ans=n-i+1;
		sort(p+1,p+n+1,cmp2);
		for(int i=1;i<=n;i++) cout<<p[i].ans<<" ";
		cout<<endl;
	}
	return 0; 
} 
```


---

## 作者：O_v_O (赞：0)

# CF1622B Berland Music题解

这道题目很简单，洛谷的翻译不行蒟蒻在这里写一篇题解。

## 思路

我们可以先将其按数值进行排序，然后先求解 Mooncarp 不喜欢的歌曲，然后再求解 Mooncarp 喜欢的，因为题目中说要预测评分和原预测得分的差距小。

##  _Code_ 

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, t, p[N], cnt, q[N];
char c;
struct node{
    int id, num;
}a[N];//存储结构体
bool cmp(node a, node b){return a.num < b.num;}//排序函数
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);//读入读写优化
    cin >> t;
    while(t--){
        cnt = 0;//初始化
        cin >> n;
        for(int i = 1;i <= n;i++){
            cin >> a[i].num;
            a[i].id = i;//记录记号点读入的
        }
        sort(a + 1, a + n + 1, cmp);//排序
        for(int i = 1;i <= n;i++){
            cin >> c;
            p[i] = (c == '0');//读入处理
        }
      	//求解答案
        for(int i = 1;i <= n;i++)
            if(p[a[i].id])
                q[a[i].id] = ++cnt;
        for(int i = 1;i <= n;i++)
            if(!p[a[i].id])
                q[a[i].id] = ++cnt;
        for(int i = 1;i <= n;i++)
            cout << q[i] << ' ';//输出
        cout << '\n';
    }
    return 0;
}
```

---

