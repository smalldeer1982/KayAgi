# Move Back at a Cost

## 题目描述

You are given an array of integers $ a $ of length $ n $ . You can perform the following operation zero or more times:

- In one operation choose an index $ i $ ( $ 1 \le i \le n $ ), assign $ a_i := a_i + 1 $ , and then move $ a_i $ to the back of the array (to the rightmost position). For example, if $ a = [3, 5, 1, 9] $ , and you choose $ i = 2 $ , the array becomes $ [3, 1, 9, 6] $ .

Find the lexicographically smallest $ ^{\text{∗}} $ array you can get by performing these operations.

 $ ^{\text{∗}} $ An array $ c $ is lexicographically smaller than an array $ d $ if and only if one of the following holds:

- $ c $ is a prefix of $ d $ , but $ c \ne d $ ; or
- in the first position where $ c $ and $ d $ differ, the array $ c $ has a smaller element than the corresponding element in $ d $ .

## 样例 #1

### 输入

```
3
3
2 1 3
5
1 2 2 1 4
6
1 2 3 6 5 4```

### 输出

```
1 3 3 
1 1 3 3 5 
1 2 3 4 6 7```

# 题解

## 作者：hgcnxn (赞：13)

## CF2046B Move Back at a Cost题解

### 题目大意

给定长度为 $n$ 的数列 $a$，你可以进行以下操作无限次：

- 选择一个 $1$ 到 $n$ 之间的正整数 $i$，将 $a_i$ 加 $1$，然后将 $a_i$ 移至数列末尾。

求出 $a$ 经过操作后的最小字典序。

### 思路

定义一个数 $a_i$ 为 A 数，当且仅当它满足如下条件：

- 存在 $a_j$ 满足 $a_i>a_j$ 且 $i<j$。

**为了使字典序最小，每一次都要操作 A 数。**

因此，我们将初始数列中所有 A 数进行操作。**由于我们可以控制操作顺序，所以我们可以保证操作后的数在数列末尾单调不降**。此时，数列被分为了两段连续的单调不降序列，或整体单调不降。

接下去，我们在还没有进行操作的数中寻找新的 A 数并进行操作。它们一定比第一轮找出的 A 数中最小的一个数操作完后大。将两轮找出来的所有 A 数加一，直接排序即可。

### 代码

我们不需要真正去移动被操作的数，额外开一个数组去记录是否被操作即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005],mn,mnn,f[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		mn=mnn=2e9;
		for(int i=0;i<n;i++){
			cin>>a[i];
			f[i]=0;
		}
		for(int i=n-1;i>=0;i--){
			if(mn>a[i])mn=a[i];
			if(a[i]>mn){
				a[i]++;
				f[i]=1;//标记是否操作过 
				mnn=min(mnn,a[i]);
			}
			//第一轮寻找A数
		}
		for(int i=n-1;i>=0;i--)if(f[i]==0&&a[i]>mnn)a[i]++;//第二轮寻找A数
		sort(a,a+n);
		for(int i=0;i<n;i++)cout<<a[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：litjohn (赞：4)

首先，不难发现一点：如果一个数的后面有比它更小的数，那么这个更小的数挪到前面来一定更优，而如果没有比它更小的数字，进行操作则一定不优。这是由字典序的性质决定的。

于是就发现需要对所有在它后面存在比它更小的数的数进行操作。

发现挪的过程如果暴力做是 $O(n)$ 的，但是我们其实并不需要把那些被挪走的数删掉，只需要打个标记就行了。而在尾端插入是很显然的。

通过观察样例发现一点：把数挪到尾端时不能胡乱来。因为可以按照数的大小排序，这样可以保证更优。

同样观察样例，发现并不是挪动一轮就可以完成的。有时挪了一轮之后会产生新的需要挪的数。于是还要再挪一轮。这第二轮也需要排序。

发现第二轮的数可以和第一轮放在一起排序，然后统一插入，而不是两轮单独排序。因为第一轮的数是必定要挪的，而在第一轮的数挪完之后第二轮的数也是必定要挪的，对于这些必定要挪的数，我们可以任意安排操作的顺序，所以可以放在一起统一排序插入以达到更优解。

我们还可以证明只需要两轮操作。因为在第一轮操作之后，没有被操作的数构成一个非降序列。第一轮操作的数都比任意没有被操作的数靠后，所以第二轮会操作所有大于第一轮操作的数中最小的数加一的数，并不会影响所有被操作的数中最小的数的大小。其余没有被操作的数不可能再比被操作的数更小了，而被操作了的数都已经被排好了序，也不可能产生新的需要操作的情况了。所以就是最优解了。
```cpp
#include <bits/stdc++.h>

using namespace std;
int t, n;
vector<int> a;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    for (int _ = 0; _ < t; ++_) {
        a.clear();

        cin >> n;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            a.push_back(x);
        }

        int min_val = 2e9;
        vector<int> tmp;
        for (int i = a.size() - 1; i >= 0; --i) {
            if (min_val < a[i]) {
                tmp.push_back(a[i] + 1);
                a[i] = -2e9;
            } else {
                min_val = a[i];
            }
        }

        sort(tmp.begin(), tmp.end());
        if (!tmp.empty()) {
            min_val = tmp.front();
        } else {
            min_val = 2e9;
        }

        for (int i = a.size() - 1; i >= 0; --i) {
            if (a[i] > 0) {
                if (min_val < a[i]) {
                    tmp.push_back(a[i] + 1);
                    a[i] = -2e9;
                } else {
                    min_val = a[i];
                }
            }
        }

        sort(tmp.begin(), tmp.end());
        for (auto i: tmp) {
            a.push_back(i);
        }
        tmp.clear();

        for (auto i: a) {
            if (i > 0) {
                cout << i << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：OrinLoong (赞：3)

# CFP2046B Move Back at a Cost 有价推迟 题解
## 前言
赛时被这道题硬控了，惨。  
赛时机房里有个初三的 Master 也被硬控了，怒斥 CF 老是放 Adhoc。然而最后还是做出来了，并且 20min 切掉了C。（不过还是掉分了）  
其实赛时也把性质观察的七七八八了，但是赛后才把思路连贯地组织出来。  
哎，我怎么连半个 CF Div2.D 都场切不下来呢？  
笔者自认为这篇题解分析透彻，尤其适合蒟蒻阅读。虽然对于 *1600 来说有杀鸡牛刀之嫌，但是其中思考方式对于切题来说是很重要的。  
## 题意
给定一个长为 $N$ 的序列 $A$。可以执行任意次以下操作：
+ 选择一个索引 $i$，令 $A_i:=A_i+1$，并将其移到序列末尾。

要求最小化序列的字典序。
## 分析
### 问题定性
这是一个操作次数不限、目标为最优化、在序列上进行的问题。
### 问题转化
+ 对于这种“操作……使……最优”的题目，我们不妨分析一波操作顺序的影响。手玩观察到当要操作的元素集确定时，最优的操作结果是唯一的——被操作的元素最后从小到大接在原序列后方。这个结果是一定能被达成的，所以我们现在不关心操作顺序了。
+ 由此可知，我们的操作本质上是在做这样一件事：对于所有被操作的元素，我们把它数值加一，从原序列里拎出去。最后我们可以从小到大重排这些被操作的元素，接在原序列后方。
### 发掘最优解性质
+ 我们猜测最优解的单调性：最优解是否一定是一个元素字典序单调不降的序列？答案是肯定的，反证法可以证明：若最优解并非元素字典序单调不降，则必然存在 $A_i>A_{i+1}$，我们对 $A_i$ 执行操作，则第 $i$ 位的值变为 $A_{i+1}$ ，小于原值，新解优于原解，原解并非最优解。
+ 看到操作次数不限，我们就要考虑：是否只有有限次的操作是有意义的。答案也是肯定的：任何元素被操作一次以上都是劣的，因为我们会使得一个元素的答案更坏，却没换来多余的重排机会。
+ 进一步地，我们考虑哪些元素是不应被操作的。对于最值问题，我们自然而然考虑原序列的最值。发现：数值最小的元素（下标记为 $p$）肯定不应被操作，因为不操作之也不可能影响最后形成解的单调性。相应地，$(0,p)$ 中所有元素必须被操作；至于它后面的元素，我们另行考虑——
### 推广到正解
+ 我们发现上文的决策可以递归地推广下去：我们记录原数列的后缀最大值下标 $smn_i$。我们第一次决策实质上就是以 $p$ 为断点，把其前面的元素全部发配；第二次决策我们以 $smn_{p+1}$ 为断点（记为 $p'$），$(p,p')$ 的元素也全部发配，理由与第一次发配类似；不同点在于，$A_{p'}$ 可能也得被发配（比如前面有一个被发配的 $2$ 变成 $3$ 而 $A_{p'}=4$，所以我们记录之前被发配的元素中（加一后的）的最小值。如果比 $A_{p'}$ 小那么就发配 $A_{p'}$。接着继续把问题递归下去。
## 代码
代码就很简单了。注意使用优先队列时要注意判空。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MaxN=1e5+5,Inf=0x3f3f3f3f;
int Tcn,N,A[MaxN],smn[MaxN];queue<int> q;
priority_queue<int,vector<int>,greater<int> > pq;
void mian(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++)scanf("%d",&A[i]);
    smn[N]=N;for(int i = N-1;i >= 1;i--)
    {smn[i]=(A[i]<=A[smn[i+1]]?i:smn[i+1]);}
    int l=1,p;while(l<=N){
        int p=smn[l];for(int i = l;i < p;i++)pq.push(A[i]+1);
        if(!pq.empty()&&pq.top()<A[p])pq.push(A[p]+1);
        else q.push(A[p]);l=p+1;
    }
    while(!q.empty()){printf("%d ",q.front());q.pop();}
    while(!pq.empty()){printf("%d ",pq.top());pq.pop();}
    printf("\n");
}
int main(){
    scanf("%d",&Tcn);
    while(Tcn--)mian();
    return 0;
}
```

---

## 作者：ARIS2_0 (赞：2)

### 前言

神秘的题目，赛时吃了一发。

### 题意

给定长度为 $n$ 的数列 $a$，你可以进行无限次以下操作：

>选定一个 $i(1\le i\le n)$ 使 $a_i+1\to a_i$，然后使 $a_i$ 移动到数列的最右端（即使 $a_i\to p,a_{i+1}\to a_i,a_{i+2}\to a_{i+1},\dots,a_{n}\to a_{n-1},p\to a_{n}$）。

问你能得到的、字典序最小的数列 $a$ 并输出。

注：若有长度为 $n$ 的数列 $a,b$，称数列 $a$ 的字典序小于数列 $b$，当且仅当有一个 $j(1\le j\le n)$ 满足 $\forall i\in[1,j-1],a_i=b_i$ 且 $a_j<b_j$。

### 思路

题目要求字典序最小，那我们可以选择一些数，使这些数移动到最右端。

显然，对于一个数，如果**有一个数在它右边且比它小**，为了保证字典序最小，**一定要对这个数进行操作**，我们称这样的数叫**特征数**。由于操作顺序任意，不妨认为所有的特征数操作后**都是有序地排列在数列的最后**。

以如下数列为例：

|$i$|1|2|3|4|5|6|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$a_i$|1|8|5|2|6|7|

可以发现 $a_2=8,a_3=5$ 是特征数，将它们操作后得到 $9,6$。由于可以任意决定操作顺序，我们可以先操作 $a_3$，再操作 $a_2$，此时我们就可以得到以下数列：

|$i$|1|2|3|4|5|6|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$a_i$|1|2|6|7|6|9|

发现此时数列被分成了两段有序数列 $a_1,a_2,\dots,a_k$ 与 $a_{k+1},a_{k+2},\dots,a_n$（$k$ 是**非特征数**的个数，此处 $k=4$），考虑如何进一步减小字典序。

我们找到 $[1,k]$ 中最大的满足 $a_{pos}$ 小于等于 $a_{k+1}$ 的 $pos$，发现对于 $a_{pos+1},a_{pos+2},\dots,a_k$，若我们把它们全部操作，因为 $a_{k+1}\le a_{pos+1}$，操作一定是不劣的。  
那么，我们对 $i\in[pos+1,k]$ 执行 $a_i+1\to a_i$，再对于 $[pos+1,n]$ 进行**整体排序**（因为操作顺序仍然可以任选，不一定要等 $a_{k+1},a_{k+2},\dots,a_n$ 全部生成后再操作 $a_{pos+1},a_{pos+2},\dots,a_k$），即可得到答案。易证明此时数列一定是有序的，即没有更优解。

### 实现

代码实现上，可以用结构体排序区分特征数（为方便表示，使用中括号）：按 $a[i].v$ 较小为第一关键字，$a[i].id$ 较小为第二关键字排序后，对于每个 $i\in [2,n]$，若 $a[i].id<\max(a[j].id)(j\in[1,i-1])$，则编号为 $a[i].id$ 的数为特征数。

区分完特征数后，可以将非特征数存入 $b$，特征数操作（即 $+1$）后存入 $c$，然后对 $c$ 排序。接着使用 ```upper_bound()``` 找到 $pos$，将 $b_{pos+1},b_{pos+2},\dots,b_k$ 操作（即 $+1$）后添加到 $c$ 数组后边，再对 $c$ 数组进行排序，最后输出 $b_1,b_2,\dots,b_{pos},c_1,c_2,\dots,c_{n-pos}$ 即可。

### 注意事项

- 本人代码中，$tot$ 代表 $b$ 数组中元素个数，$res$ 代表 $c$ 数组中元素个数。
  
- 当数列本身有序（即 $res=0$ 时）要特判，否则后面找 $pos$ 时会出锅。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e16,maxn=1e5+10;
namespace ARIS2_0{
	struct node{int id,v;}a[maxn];
	bool cmp(node a,node b){return a.v==b.v?a.id<b.id:a.v<b.v;}//结构体比较函数
	int b[maxn],c[maxn];
	void solve(){
		int n;cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i].v,a[i].id=i;
		sort(a+1,a+n+1,cmp);
		int tot=0,res=0,maxid=a[1].id;
        b[++tot]=a[1].v;
        //根据定义，数列中最小的数一定是非特征数
		for(int i=2;i<=n;i++){
			if(a[i].id<maxid)c[++res]=a[i].v+1;//特征数操作后放入c
			else b[++tot]=a[i].v;//非特征数放入b
            maxid=max(maxid,a[i].id);//更新maxid
		}
        if(res==0){//res=0时特判（即数列本身有序），否则下面找pos的地方会出锅（因为c[1]没有更新，可能是各种奇奇怪怪的值）
            for(int i=1;i<=tot;i++)cout<<b[i]<<" ";
            cout<<"\n";return;
        }
		sort(c+1,c+res+1);
		int pos=upper_bound(b+1,b+tot+1,c[1])-b-1;
		for(int i=pos+1;i<=tot;i++)c[++res]=b[i]+1;//将b[pos+1~tot]操作后放入c
		sort(c+1,c+res+1);
		for(int i=1;i<=pos;i++)cout<<b[i]<<" ";
		for(int i=1;i<=res;i++)cout<<c[i]<<" ";//res=n-pos
		cout<<"\n";
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)ARIS2_0::solve();
	return 0;
}
```

---

## 作者：hnczy (赞：1)

容易发现结果是一个单调不减的数组。

那我们吧每一个大于后面任意一个数的数放进小根堆里。

再遍历一遍数组，若有比小根堆的堆顶大的数，也放进堆里。

重复多遍，知道是顺序的即可。

```c++
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
int T,n,a[100005];
stack<int>st;
int f[100005],b[100005],c[100005];
priority_queue<int,vector<int>,greater<int>>q;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1; i<=n; i++) 
			scanf("%d",a+i);
		while(1) {
			int flag=0;
			memset(f,0,sizeof f);
			for(int i=1; i<=n; i++) {
				while(!st.empty()&&a[st.top()]>a[i]) {
					q.push(a[st.top()]);
					f[st.top()]=1;
					st.pop();
					flag=1;
				}
				st.push(i);
			}
			while(!st.empty())st.pop();
			if(!flag)break;
			int len=0;
			for(int i=1; i<=n; i++) {
				if(!f[i]){
					if(a[i]>q.top()+1)q.push(a[i]);
					else a[++len]=a[i];
				}
			}	
			while(!q.empty()){
				a[++len]=q.top()+1;
				q.pop();
			}
		}
		for(int i=1;i<=n;i++)
			printf("%d ",a[i]);
		printf("\n");
	}
	return 0;
}

---

## 作者：OIer_Hhy (赞：0)

观察数据，有一个显而易见的结论：当操作后的序列为单调不降序列时，字典序才会最小。

证明：反证法。
假设序列 $a=[a_1,a_2,\cdots,a_n]$ 为经过操作后可能的字典序最小的序列，且 $\exist 1 \le i<n$ 满足 $a_i>a_{i+1}$。

此时，我们可以删除 $a_i$，将 $a_i+1$ 放到序列的末尾，形成新序列 $a'=[a_1,\cdots,a_{i-1},a_{i+1},\cdots,a_i]$。容易发现 $a'<a$，与 $a$ 的最小性矛盾。

证毕。

于是我们把原序列中的数分为两类：

- 不动的。

- 放到后面的。

放到后面的数与原来数的顺序没有关系，我们只要将它们排序后输出即可。

由于我们刚才已经证明了，最后的序列为一个单调不降序列，因此，对于 $1 \le i \le n$ 满足$a_i>\min(a_{i+1},a_{i+2},\cdots,a_n)$ 的数 $a_i$，都要移到后面去。

然而又会出现一个新的问题：移到末尾的数可能会比 $a_i$ 小，怎么办？

我们只要维护一个移到末尾的数的最小值即可。

[my code](https://codeforces.com/contest/2046/submission/295393267)

---

## 作者：qwer6 (赞：0)

## 题意概述

定义一次操作为：选定一个序列中的元素 $x$，将这个元素加一后移动到序列的末尾。

给定序列，对这个序列进行任意次操作，要求得到的序列字典序最小。

## 解题思路

我们很容易可以知道：最多对每个数进行一次加一操作，就可以完成排序。

我们明确这两件事：

1. 我们只需要决定两件事情：那些数需要加一，这些数加一的顺序。
2. 我们可以先确定那些数需要加一，再确定这些数加一的顺序。

那我们先来考虑那些数需要加一。

这些数大致可以分为两类：后面有一个比它小的数，或者前面有一个加一之后仍比它小的数加一了。

我们可以观察样例来思考一下为什么：

对于样例中的第一组数据：$2\ 1\ 3$。

由于 $2$ 后面有一个比它小的数,所以我们需要对 $2$ 执行一次操作，序列就变成了 $1,3,3$。

对于样例中的第二组数据：$1\ 2\ 2\ 1\ 4$。

由于两个 $2$ 后面都有比它小的数，所以我们需要对两个 $2$ 执行操作。

又因为 $4$ 前面有加一之后仍比它小的数加一了，所以我们还需要对 $4$ 执行操作。 

这样我们得到的序列是：$1\ 1\ 3\ 3\ 5$。

对于样例中的第三组数据：$1\ 2\ 3\ 6\ 5\ 4$。

我们对 $6$ 和 $5$ 执行操作，这样我们得到的序列是：$1\ 2\ 3\ 4\ 6\ 7$。

这样我们就完成了第一步。

至于第二步......

模拟完之后对于经过操作的数排一次序即可。

## 代码实现

```c++
/*by qwer6*/
#include<bits/stdc++.h>
#define Nxt puts("")
#define Spa putchar(32)
namespace FastIO{
	inline void read(int &a){
		char c=getchar();
		int f=1;
		a=0;
		while(!isdigit(c)){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(isdigit(c)){
			a=(a<<1)+(a<<3)+(c^48);
			c=getchar();
		}
		a*=f;
		return ;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		int a[20];
		a[0]=0;
		do{
		   a[++a[0]]=x%10;
		   x/=10;
		}while(x);
		for(int i=a[0];i;i--)putchar(a[i]+'0');
		return ;
	}
	inline bool tomax(int &a,int b){
		if(a<b){
			a=b;
			return true;
		}
		return false;
	}
	inline bool tomin(int &a,int b){
		if(a>b){
			a=b;
			return true;
		}
		return false;
	}
}
using namespace FastIO;
using namespace std;
const int N=1e5+5,inf=0x3f3f3f3f;
int n,mi,cnt;
int a[N],b[N];
bool flag1[N],flag2[N];
signed main(){
	int t;
	read(t);
	while(t--){
		read(n);
		for(int i=1;i<=n;i++)read(a[i]);
		mi=inf;
		cnt=0;
		for(int i=1;i<=n;i++)flag1[i]=flag2[i]=0;
		for(int i=n;i;i--){
			if(mi<a[i]){
				flag1[i]=1;
				1++;
			}else mi=a[i];
		}
		mi=inf;
		for(int i=1;i<=n;i++){
			if(flag1[i])tomin(mi,a[i]+1);
			else if(mi<a[i]){
				flag2[i]=1;
				cnt++;
			}
		}
		for(int i=1,k1=0,k2=n-cnt;i<=n;i++){
			if(flag1[i]||flag2[i])b[++k2]=a[i]+1;
			else b[++k1]=a[i];
		}
		sort(b+n-cnt+1,b+n+1);
		for(int i=1;i<=n;i++)write(b[i]),Spa;
		Nxt; 
	}
}
```

---

## 作者：201012280925LSY (赞：0)

## 题意
有一个数列，长度为 $n$。你可以使用若干次操作。每次操作你可以在数列中选择一个数，然后把这个数加一放到数列最后面。输出若干次操作后所形成的字典序最小的数列。

多组测试。
## 思路
首先注意到如果我们把每个数操作一次，那么我们可以任意顺序的数列。

这个是非常容易证明的。我们开一个新的队列，初始时这个数列是空的。然后按顺序往里面放数即可。

根据题意，很轻松就可以想到暴力。我们令 $l$ 表示我们确定了答案数列的前 $l-1$ 位。那么我们第 $l$ 位的答案是 $l \sim n$ 当中的最小值。然后我们令 $a_x$ 为这个最小值，再把 $l \sim x-1$ 的数全部 $+1$ 放到数列最后面。

现在考虑优化。因为当前位置的答案，要么是后面的数的最小值，要么是前面没有被选上的数中的最小值。我们把前面没选上的数放进一个堆里，同时维护一个后缀最小值，然后判断堆顶端更小还是后面的更小，然后输出答案。

注意，当我们使用了堆里的数时，我们需要把剩下的在数列里的不在堆里的数扔进堆里面。因为毕竟被操作的数是在数列末尾的。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T;
long long n;
long long a[100010];
struct Node
{
	long long no,s;
	Node(long long x,long long y){no=x,s=y;}
	bool operator < (const Node &other)const // 以数值为第一关键字排序。
	{
		if(s!=other.s)return s>other.s;
		else return no>other.no;
	}
};
struct dick
{
	long long no,s;
}maxx_back[100010];
priority_queue<Node>dq;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		maxx_back[n+1].s=1e18;
		for(int i=n;i>=1;i--)//维护后缀最小值。
		{
			if(a[i]<=maxx_back[i+1].s)
			{
				maxx_back[i].s=a[i];
				maxx_back[i].no=i;
			}
			else
			{
				maxx_back[i]=maxx_back[i+1];
			}
		}
		long long l=1;
		for(int i=1;i<=n;i++)
		{
			if(dq.empty()||maxx_back[l].s<=dq.top().s)//如果没有数被操作或者后缀值更优
			{
				cout<<maxx_back[l].s<<" ";
				for(int j=l;j<maxx_back[l].no;j++)
				{
					dq.push(Node(j,a[j]+1));
				}
				l=maxx_back[l].no+1;
			}
			else 
			{
				cout<<dq.top().s<<" ";
				dq.pop();
				for(int j=l;j<=n;j++)//把数扔进堆里。
				{
					dq.push(Node(j,a[j]+1));
				}
				l=n+1;
				
			}
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：内拉组里 (赞：0)

这里提供一种新的思路，用双 `priority_queue` 模拟可删堆实现。

# Thoughts :

> 显而易见地，每一个元素最多被操作一次，
>
> 因为所有可能被操作的元素可以按照任意顺序移至数组尾部。
>
> 所以开两个可并小根堆 $ q1 $ 存储当前数组里的元素，$ q2 $ 存储已经移至数组尾部的元素。
>
> 1. 把所有元素都压进 $ q1 $，
>
> 2. 遍历 $ a_i $ 对每一个元素进行决策：
>
>    - $ a_i $ 是 $ q1 $ 中最小的元素，那么接下来字典序最小的方案必定以 $ a_i $ 开头，直接输出 $ a_i $ デス～
>
>    - $ a_i $ 不是 $ q1 $ 中最小的元素，那么这时存在更优解，$ a_i $ 应移至数组尾部，
>
>      所以往 $ q1 $ 和 $ q2 $ 中都压一个 $ a_i + 1 $。
>
>      > Ps：这里要往 $ q1 $ 中也要压是为了干扰后续元素的决策，
>      >
>      > 考虑在某一刻这次的 $ a_i + 1 $ 成为了 $ q1 $ 中的最小值，那剩余的元素肯定都要移至数组尾部了。
>      >
>      > 这一点在样例 #2中有体现。
>
>    最后，决策完毕后记得把 $ a_i $ 从 $ q1 $ 中弹出来。
>
> 3. 对 $ q2 $ 中的元素进行处理，一个一个弹出来输出デス～

# Analyses :

> 总时间复杂度 $ \Theta (TN \log{N}) $ 
>
> 总空间复杂度 $ \Theta (N) $ 

# Code :

```cpp
#include	<iostream>
#include	<cstring>
#include	<queue>
using namespace std;
constexpr int maxn = 1e5+4;

struct Q
{
	priority_queue<int,vector<int>,greater<int> > q1, q2;
	
	void clear (void)
	{
		while (!q1.empty()) q1.pop();
		while (!q2.empty()) q2.pop();
	}
	
	int empty (void)
	{
		return !(q1.size() - q2.size());
	}
	
	void push (int x)
	{
		q1.push(x);
	}
	
	void pop (int x)
	{
		q2.push(x);
	}
	
	int top (void)
	{
		while (!q1.empty() && !q2.empty() && q1.top() == q2.top())
		{
			q1.pop();
			q2.pop();
		}
		return q1.top();
	}
}q1, q2;
int t, n;
int a[maxn];
int vis[maxn];

signed main (void)
{
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		memset (vis, 0, sizeof vis);
		q1.clear();
		q2.clear();
		for (int i = 1; i <= n; i++) q1.push(a[i]);
		for (int i = 1; i <= n; i++)
		{
			if (a[i] == q1.top()) cout << a[i] << ' ';
			else
			{
				q1.push(a[i] + 1);
				q2.push(a[i] + 1);
			}
			q1.pop(a[i]);
		}
		while (!q2.empty())
		{
			cout << q2.top() << ' ';
			q2.pop(q2.top());
		}
		cout << endl;
	}
	return 0;
}
```

---

