# Big Secret

## 题目描述

Vitya has learned that the answer for The Ultimate Question of Life, the Universe, and Everything is not the integer 54 42, but an increasing integer sequence $ a_1, \ldots, a_n $ . In order to not reveal the secret earlier than needed, Vitya encrypted the answer and obtained the sequence $ b_1, \ldots, b_n $ using the following rules:

- $ b_1 = a_1 $ ;
- $ b_i = a_i \oplus a_{i - 1} $ for all $ i $ from 2 to $ n $ , where $ x \oplus y $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of $ x $ and $ y $ .

It is easy to see that the original sequence can be obtained using the rule $ a_i = b_1 \oplus \ldots \oplus b_i $ .

However, some time later Vitya discovered that the integers $ b_i $ in the cypher got shuffled, and it can happen that when decrypted using the rule mentioned above, it can produce a sequence that is not increasing. In order to save his reputation in the scientific community, Vasya decided to find some permutation of integers $ b_i $ so that the sequence $ a_i = b_1 \oplus \ldots \oplus b_i $ is strictly increasing. Help him find such a permutation or determine that it is impossible.

## 说明/提示

In the first example no permutation is valid.

In the second example the given answer lead to the sequence $ a_1 = 4 $ , $ a_2 = 8 $ , $ a_3 = 15 $ , $ a_4 = 16 $ , $ a_5 = 23 $ , $ a_6 = 42 $ .

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
No
```

## 样例 #2

### 输入

```
6
4 7 7 12 31 61
```

### 输出

```
Yes
4 12 7 31 7 61 
```

# 题解

## 作者：AzureHair (赞：4)

因为集训一上午只会这一道题所以来发一篇题解(?

首先我们可以写出这样的式子 $a_i=a_{i-1}\oplus b_i$ 然后我们要使得 $a_i>a_{i-1}$，考虑在 $a_{i-1}$ 已知的情况下什么样的 $b_i$ 才能使得 $a_i>a_{i-1}$。容易发现，当且仅当 $b_i$ 的二进制位的最高位与在 $a_i$ 中不同，即前面的 $b_i$ 在这一位出现了偶数次，$a_i>a_{i-1}$。

推到这里问题转化成了给了一个数列，构造出一个排列使得每个数的最高位在前面的数中1的个数为偶数个。

由于最高位高的数可能会对最高位低的数产生影响，所以考虑排序令最高位低的优先选，但是在有多个最高位相同的数的情况下需要使用最高位更高的数来辅助低位，那么自然是按照刚才的方法找到当前出现了偶数次且是未使用过的最高位为这位的数，注意到由于低于该数的数位均出现过奇数次，所以当你选择这个数时只会使答案变得不劣或更优（因为该数的低位有1则可以给低位清空，为0也只会变得不劣）所以可以随便选择最高位相同的数中的一个，按照上述过程模拟即可通过此题。

有些许抽象看看代码画个图好理解一些。

```cpp
#include<bits/stdc++.h>
//#include<windows.h>
#define int long long
using namespace std;
int n,cnt1=0,cnt2=0,pos[100010],flag[110],ans[100010],pos1[100010];
struct node
{
	int h,s;
	bool operator <(const node &b) const
	{
		return h<b.h;//按最高位从小到大排序
	}
}a[100010];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		int x,cnt=0;
		scanf("%lld",&x);
		a[i].s=x;
		while(x)
		{
			x>>=1;
			cnt++;
		}
		a[i].h=cnt;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(a[i].h!=a[i-1].h)
		{
			pos[++cnt1]=i;//记录该最高数位下的第一个数的位置
			pos1[cnt1]=pos[cnt1];
		}
	}
	/*for(int i=1;i<=cnt1;i++)
	{
		cout<<pos[i]<<" ";
	}
	cout<<endl;*/
	for(int i=1;i<=cnt1;i++)
	{
		//cout<<i<<"!!!!!!!!"<<endl;
		while(pos[i]!=pos1[i+1])
		{
			if(cnt2==n)break;
			int j=i;
			while(flag[a[pos1[j]].h]||pos[j]==pos1[j+1])
			{
				if(j>n)
				{
					//cout<<cnt2<<endl;
					cout<<"No"<<endl;
					return 0;
				}
				j++;
			}
			//system("pause");
			//cout<<i<<" "<<j<<" "<<pos[i]<<" "<<cnt2<<endl;
			ans[++cnt2]=a[pos[j]].s;
			pos[j]++;
			if(cnt2==n)break;
			for(int k=a[pos1[i]].h;k<=a[pos1[j]].h;k++)
			{
				if((a[pos[j]-1].s>>(k-1))&1)
				{
					flag[k]^=1;//暴力更改低位01
				}
			}
		}
	}
	cout<<"Yes"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<" ";
	}
	return 0;
}
```

---

## 作者：SoyTony (赞：3)

对于一个排列，$i$ 位置合法的充要条件是其最高位 $k$ 在前缀 $[1,i-1]$ 出现次数为偶数，可以按最高位从高到低排序，这样加入时所有可能对最高位出现次数产生影响的数都已经加入了，不会出现后插入的数影响先插入的数。

每次批量加入最高位为 $k$ 的数，一个方法是在当前序列开头以及每个第 $k$ 位为 $1$ 的位置后插入都加入一个最高位为 $k$ 的数，这种加入方法说明了最高位相同的数相对顺序无关紧要。

使用链表维护当前的序列，发现第 $i$ 次最多加入 $2^{i-1}$ 个数，每次每次暴力遍历链表是可以接受的。

提交记录：[Submission - CodeForces](https://codeforces.com/contest/925/submission/226162155)

---

## 作者：YxYe (赞：3)

# [[CF925C] 大秘密 题解](https://www.luogu.com.cn/problem/CF925C)

非常简单的一道构造。

upd:2023/10/7 修改了一点小问题

## 思路

注意：以下所说的位数等皆为二进制。

### Pre

先考虑 $n=2$ 怎么做

考虑最简单的：数字 $1$ 如何与其他排序。

- 对于最低位为 $1$ 的，如果不是 $1$，那么可以排在 $1$ 后面。

- 对于最低位为 $0$ 的，都可以排在 $1$ 的后面。

拓展到高位数，从低位向高位考虑一个数 $x$。

- 对于数位比 $x$ 高的，显然可以排在 $x$ 后面。

- 对于位数比 $x$ 低的，不可以排在 $x$ 后面。因为如果可以，那么会在低位数算到。
    
- 对于位数相同的，考虑从高往低的第一位不同的数：若 $x$ 在该位为 $0$，显然可以放在后面。若 $x$ 在该位为 $1$，那么还得往后找……

最后一点貌似好麻烦，但其实我们只需要知道这个数最高位是否可以。因为通过最高位的异或，新的数字肯定比这个数字大。

### Sol

对于 $n\le 10^5$，可以维护前缀异或和。

这样每次相当于合并两个数，转化为做 $n$ 次 $n=2$ 时的操作。

为了方便，可以用容器记录每个数的最高位，省下枚举从高位向低位找的一维。

### Code

记得开 long long！

## 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<stack>
#include<queue>
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,a,b) for(int i=(a);i<=(b);i++)
#define fp(i,a,b) for(int i=(a);i<(b);i++)
#define de(i,a,b) for(int i=(a);i>=(b);i--)
#define fs(e,i,u) for(int i=e.head[u];i;i=e.nxt[i])
#define pii pair<int, int>
#define pdd pair<db,db>
#define pb push_back
#define fir first
#define sec second
#define ls (now<<1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline int getc(){
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
inline ll read(){
    ll x=0,f=1;char ch=getc();
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=getc();
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getc();
    }
    return x*f;
}
const int maxn=1e5+10;
int n,ansn;
ll ans[maxn];
queue<ll>q[66];
int main(){
	n=read();
	fo(i,1,n){
		ll x=read();
		de(j,60,0){
			if((1ll<<j)&x){
				q[j].push(x);
				break;
			}
		}
	}
	ll sum=0;
	fo(i,1,n){
		bool flag=0;
		fo(j,0,60){
			if(((1ll<<j)&sum)||q[j].empty())continue;
			ans[++ansn]=q[j].front();
			sum^=q[j].front();q[j].pop();
			flag=1;
			break;
		}
		if(!flag){
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	fo(i,1,ansn){
		printf("%lld ",ans[i]);
	}
	return 0;
}
```

---

## 作者：Shapy_UI_Tools (赞：0)

## 题意
给一个序列 $b$，设 $a$ 为 $b$ 的前缀异或和数组，即 $a_i=a_{i-1} \oplus b_i$，你需要将 $b$ 重新排列，使得 $a$ 单调递增。

## 解法
### 思路
因为要保证 $a$ 单调递增，而 $a_1=b_1$，所以先令重排后的第一个数为 $\min\limits_ib_i$。然后我们考虑每次要让让当前的数（初始为 $b_1$）$x$ 跟谁异或。为了满足单调递增，我们要每次尽可能取一个 $b_i$ 使得 $(x \oplus b_i)-x$ 在满足 $>0$ 的情况下最小。

以下定义“位数”为最高位的 $1$ 的位置。
1. $(x \oplus b_i)-x>0$。要满足这个条件，设 $b_i$ 的位数为 $y$，则 $x$ 的第 $y$ 位必须为 $0$，否则进行异或运算后，$x$ 的比第 $y$ 位更高的位全都不会改变的，同时 $x$ 的第 $y$ 位变成了 $0$，也就是 $x$ 变小了，就不满足单调递增了。因此我们可以找出所有满足条件的 $b_i$。
2. $(x \oplus b_i)-x$ 最小。要满足这个条件很简单，从小到大枚举 $x$ 为 $0$ 的位，一旦遇到有 $b_i$ 满足条件且未被使用过就直接使用。

如果所有位数小于 $x$ 的 $b_i$ 全都不符合条件，我们就再枚举位数大于 $x$ 的 $b_i$，此时显然 $(x \oplus b_i)-x>0$。千万不能选择位数与 $b_i$ 相等的，因为两个数的最高位相同还都是 $1$，异或后就变成 $0$ 了，值就减小了，不符合单调递增。
### 实现
先预处理出来位数为 $i$ 的所有数，然后每把一个数加入答案就删除这个数。如果所有位数都枚举了一遍也无法找到一个合法的，就直接输出 No。

## 代码
[提交记录](https://www.luogu.com.cn/record/127648000)
```cpp
#include <iostream>
#include <queue>
#define int long long
using namespace std;

const int N=1e5+10;

int n;
int b[N];
queue<int> c[N];
int ans[N];

int bitcnt(int x){
	int res=0;
	while(x>0){
		res++;
		x>>=1;
	}
	return res-1;
}

signed main(){
	scanf("%lld",&n);
	int now=0x3f3f3f3f3f3f3f3f,nowpos=0;
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
		if(b[i]<now){
			now=b[i];
			nowpos=i;
		}
	}
	for(int i=1;i<=n;i++) if(i!=nowpos) c[bitcnt(b[i])].push(b[i]);
	ans[1]=now;
	int ws=bitcnt(now);
	for(int i=2;i<=n;i++){
		int pos=0;
		while((c[pos].empty()||(now>>pos&1))&&pos<=ws-1) pos++;
		if(pos>ws-1){
			int pos2=ws+1;
			while(c[pos2].empty()&&pos<=60) pos2++;
			if(pos2>60){
				printf("No");
				return 0;
			}
			now^=c[pos2].front();
			ans[i]=c[pos2].front();
			c[pos2].pop();
			ws=pos2;
		}
		else{
			now^=c[pos].front();
			ans[i]=c[pos].front();
			c[pos].pop();
		}
	}
	printf("Yes\n");
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
}
```

---

## 作者：E1_de5truct0r (赞：0)

首先，如果 $x \oplus y>x$，则一定是前面有一段 $y$ 为 $0$，然后在某一个二进制位上 $x$ 为 $0$ 而 $y$ 为 $1$。

因此考虑贪心的实现这个问题，即我们尽可能让前面的 $a_i$ 更小。

容易发现，假设当前的 $a_i=c$，那么我们从低到高枚举每一个二进制位，找到所有的这一位是第一个 $1$ 的数，选择最小的异或起来。如果找不到，则无解。

具体的，我们对每一个二进制位开一个 set，对每个数进行预处理，存储下这一位为 $1$ 且这一位为**最高位**的数。然后，从 $1$ 到 $n$ 枚举一遍，每次找到之后就从 $s$ 中删除即可。

复杂度 $O(n \log n)$。

[Code & Submission](https://codeforces.com/contest/925/submission/226668909)

---

