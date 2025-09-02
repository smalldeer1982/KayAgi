# Arranging The Sheep

## 题目描述

You are playing the game "Arranging The Sheep". The goal of this game is to make the sheep line up. The level in the game is described by a string of length $ n $ , consisting of the characters '.' (empty space) and '\*' (sheep). In one move, you can move any sheep one square to the left or one square to the right, if the corresponding square exists and is empty. The game ends as soon as the sheep are lined up, that is, there should be no empty cells between any sheep.

For example, if $ n=6 $ and the level is described by the string "\*\*.\*..", then the following game scenario is possible:

- the sheep at the $ 4 $ position moves to the right, the state of the level: "\*\*..\*.";
- the sheep at the $ 2 $ position moves to the right, the state of the level: "\*.\*.\*.";
- the sheep at the $ 1 $ position moves to the right, the state of the level: ".\*\*.\*.";
- the sheep at the $ 3 $ position moves to the right, the state of the level: ".\*.\*\*.";
- the sheep at the $ 2 $ position moves to the right, the state of the level: "..\*\*\*.";
- the sheep are lined up and the game ends.

For a given level, determine the minimum number of moves you need to make to complete the level.

## 样例 #1

### 输入

```
5
6
**.*..
5
*****
3
.*.
3
...
10
*.*...*.**```

### 输出

```
1
0
0
0
9```

# 题解

## 作者：Waaifu_D (赞：3)

## 题意简述

给我们 $t$ 组数据，每组数据第一行为 $n$ ，为字符串长度，下一行为一个字符串（只有 ' . ' 和 ' * '字符），每次可以向右或者向左移动 ‘  * ’ 字符，求把所有的 ' * ' 字符连起来的最小移动次数

## 思路

可以运用贪心的思想

要求我们求最少移动次数，我们就需要一个明确的移动方向，那么向哪里移动最好呢？我们举一个例子

```
n=7
* . * . . * .
```


1. 全部向右移动

一共需要 $2+3=5$ 次（思考一下为什么最左边的只需要 $3$ 次）

2. 全部向左移动

一共需要 $1+3=4$ 次

3. 向最中间的‘*’符号靠拢

一共需要 $1+2=3$ 次 

不难发现，向中间靠拢是最优解方式，我们就用这个总思路来写程序

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
string s;
long long n,m[1000005],pop=0,flag=0,ans=0;
/*
n同题意，m存储*符号在哪个位置出现，pop是*出现的次数，flag用来判断是否整个字符串都是*（特判），ans存储答案
*/
long long t;//t组数据
int main()
{
	cin>>t;
	while(t--)
	{
		pop=0,flag=0,ans=0;//清空数据
		cin>>n;
		cin>>s;
		for(int i=0; i<n;i++)
		{
			if(s[i]=='*')//如果这个位置是*
			{
				m[++pop]=i+1;//存储一下位置，i+1是因为字符串下标从0开始，如果直接用i会出大问题
			}
			if(s[i]=='.') flag=1;//判断是否整个字符串都是*(样例中第二组数据)
		}
		if(pop==0||pop==1||flag==0) {cout<<0<<endl;continue;}//特判
		int mid=pop/2+1;//中间的*号所在位置的下标（m数组的下标）
		for(int i=1; i<=pop;i++)//求距离
		{
			ans+=abs(m[mid]-m[i])-abs(mid-i);
		}
		cout<<ans<<endl;
	}
	
}
```



---

## 作者：云浅知处 (赞：2)

## E. Arranging The Sheep

### Description

简要描述有点难，建议自己看原题喵

[Link](https://codeforces.com/contest/1520/problem/E)

### Solution

把 `*` 放到一起相当于把 `.` 放到两边。

因此对每个 `.` ，算一下它放到左边所需步数 $L_i$ 与放到右边所需步数 $R_i$。

然后记

$$
\text{pre}[k]=\sum_{i=1}^kL_i,\text{suf}[k]=\sum_{i=k+1}^nR_i
$$

那么答案就是

$$
\min_{0\leqslant i\leqslant n}\left(\text{pre}[i]+\text{suf}[i]\right)
$$

ps：$\text{WA On 5}$ 可能是因为求最小值的时候开的不够大。建议开到 $\texttt{1<<63}$ 喵qwq。

```cpp
#include<cstdlib>
#include<iostream>
#include<cstring>

#define int long long
#define MAXN 1000005

using namespace std;

int l[MAXN],r[MAXN],suf[MAXN],pre[MAXN],n,t,a[MAXN];
string s;

signed main(void){

    cin>>t;
    while(t--){
        
        for(int i=1;i<=n;i++)l[i]=r[i]=suf[i]=pre[i]=a[i]=0;
        
        cin>>n;
        cin>>s;

        int cnt=0;
        l[n]=r[n]=suf[n]=pre[n]=0;
        for(int i=0;i<n;i++){
            l[i]=r[i]=suf[i]=pre[i]=0;
            if(s[i]=='.')a[++cnt]=i+1;
        }
        if(cnt==0){
            puts("0");
            continue;
        }
        
        for(int i=1;i<=cnt;i++)l[i]=a[i]-i,r[i]=n-cnt+i-a[i];
        int ans=1919810114514;
        for(int i=1;i<=cnt;i++)pre[i]=pre[i-1]+l[i];
        for(int i=cnt;i>=1;i--)suf[i]=suf[i+1]+r[i];
        for(int i=0;i<=cnt;i++)ans=min(ans,pre[i]+suf[i+1]);
        cout<<ans<<endl;
    }

    return 0;
}
```


---

## 作者：oimaster (赞：1)

> 众所周知，草是一种可以被推动的动物，羊是一种被草威胁移动的植物。

各种奇怪推羊的方法全部出来了。这时候我们注意，羊最后推到哪里我们是不确定的，但是草如果可以动的话它最后的位置是可以确定的。

怎么说？

- 如果这个草向左推动，那么这个草左边所有的草都会被向左推。那么我们算出左边有多少草，假设为 $x$ 个草，那么这个草就会被推到 $x+1$ 号位置。
- 如果这个草向右推动，那么这个草右边所有的草都会被向右推。那么我们算出右边有多少草，假设为 $x$ 个草，那么这个草就会被推到 $n-x$ 号位置。

接下来，每个草向左推和向右推的代价都可以算出来。

剩下我们要做的就很简单了，我们枚举对于所有 $0\le i\le n$，看看**向前推的代价**和**从后面一棵草算起向后推的代价**加起来的和最小是多少。注意因为向前推的草数量可能为 $0$，所以 $i$ 可能是 $0$。

时间复杂度：$\text{O}(n)$

参考代码：

```cpp
#include<iostream>
using namespace std;
#define int long long
void solve(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	int fr[n];
	fr[0]=0;
	int bk[n+1];
	bk[n-1]=0;
	bk[n]=0;
	int minv=100000000000;
	int ctot=0;
	if(s[0]=='.')
		ctot=1;
	for(int i=1;i<n;++i)
		if(s[i]=='.'){
			fr[i]=fr[i-1]+(i-ctot);
		}
		else
			fr[i]=fr[i-1];
	ctot=n-1;
	if(s[n-1]=='.')
		ctot=n-2;
	for(int i=n-2;i>=0;--i)
		if(s[i]=='.')
			bk[i]=bk[i+1]+(ctot-i);
		else
			bk[i]=bk[i+1];
	for(int i=0;i<=n;++i)
		minv=min(minv,fr[i]+bk[i+1]);
	cout<<minv<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
```

---

## 作者：LinkZelda (赞：1)

- **题意**：给定一个长度为 $n$ 的字符串，字符串包含 `*` 与 `.` 两种字符，每次可以将 `*` 向左或者向右移动一个位置，求将所有 `*` 连成一段的最小操作次数。

- $Solution$:

首先我们思考发现，应该是将所有 `*` 向其中一个选定的 `*` 靠拢，这样是最优的。容易看出我们选择的位置应该是选**中间**那个，这是一个和中位数有关的显然结论。

那么我们只需要将整个字符串扫描一次，记录每一个 `*` 的位置，算出中间的位置（即 $\left\lfloor\dfrac{n}{2}\right\rfloor+1$），然后扫描其他位置算距离之和即可。

时间复杂度为 $O(n)$。

- [代码](https://www.luogu.com.cn/paste/tnzbyfet)

---

## 作者：qwq___qaq (赞：0)

首先，我们把这道题带入数轴，那么，对于任意两点 $p$、$q$，目标到达 $x$ 我们可以发现，它们的需要走距离是 $\mid p-x\mid+\mid q-x\mid$，然后减去它们中间的绵羊。那么我们可以发现：对于这个距离，如果在 $p$ 和 $q$ 的两边，那么显然是不够优的，所以 $x$ 一定在 $p$ 和 $q$ 的中间。那么，我们就可以想到中位数，然后求解即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int T,n,a[maxn],k,d[maxn];
inline int read(){
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return res;
}//读入优化
int main(){
	T=read();
	for(int tot=1;tot<=T;++tot){
		n=read(),k=0;
		for(int i=1;i<=n;++i){
			char ch=getchar();
			while(ch!='.'&&ch!='*')
				ch=getchar(); 
			if(ch=='*')
				a[++k]=i;
		} //预处理那些位置有绵羊
		int qwq=k+1>>1,qaq=a[qwq];//中位数
		long long ans=0;
		for(int i=1;i<=k;++i){
			if(i<=qwq)
				ans+=qaq-(qwq-i)-a[i];
			else
				ans+=a[i]-(qaq+(i-qwq));
		}//求解
		printf("%lld\n",ans);
	} 
	return 0;
}
```
此外，再推广种方法，对于当前选的位置 $k$，如果它右移一位，那么它左边的就多走一格，右面的就少走一格（包括在 $k$ 这个位置上的）。那么，我们先求出原点的答案，再往后推进即可。

---

