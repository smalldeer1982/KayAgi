# AB Flipping

## 题目描述

You are given a string $ s $ of length $ n $ consisting of characters $ \texttt{A} $ and $ \texttt{B} $ . You are allowed to do the following operation:

- Choose an index $ 1 \le i \le n - 1 $ such that $ s_i = \texttt{A} $ and $ s_{i + 1} = \texttt{B} $ . Then, swap $ s_i $ and $ s_{i+1} $ .

You are only allowed to do the operation at most once for each index $ 1 \le i \le n - 1 $ . However, you can do it in any order you want. Find the maximum number of operations that you can carry out.

## 说明/提示

In the first test case, we can do the operation exactly once for $ i=1 $ as $ s_1=\texttt{A} $ and $ s_2=\texttt{B} $ .

In the second test case, it can be proven that it is not possible to do an operation.

In the third test case, we can do an operation on $ i=2 $ to form $ \texttt{ABAB} $ , then another operation on $ i=3 $ to form $ \texttt{ABBA} $ , and finally another operation on $ i=1 $ to form $ \texttt{BABA} $ . Note that even though at the end, $ s_2 = \texttt{A} $ and $ s_3 = \texttt{B} $ , we cannot do an operation on $ i=2 $ again as we can only do the operation at most once for each index.

## 样例 #1

### 输入

```
3
2
AB
4
BBBA
4
AABB```

### 输出

```
1
0
3```

# 题解

## 作者：_qingshu_ (赞：3)

# 题意：

给定一个长度为 $n$ 的仅包含 $\texttt{A},\texttt{B}$ 的字符串，对于每一个 $0\le i < n$，如果 $s_i=\texttt{A}$ 且 $s_{i+1}=\texttt{B}$ 且之前没有操作过 $i$，那么可以交换这两个字符的位置。询问最多的次数。

# 思路：

既然每一个位置只能被操作一次，那么我们考虑查找字符串中第一个 $\texttt{A}$ 与最后一个字符 $\texttt{B}$。这两个位置的差就是我们的答案。

# 证明：

首先，在第一个 $\texttt{A}$ 之前的 $\texttt{B}$ 是不可能被操作的，最后一个 $\texttt{B}$ 之后的 $\texttt{A}$ 同理，这个是容易证明的。

然后考虑中间的情况。

- 如果这两个位置中间没有其余的 $\texttt{A}$。
	
    答案显而易见（笑，最优策略就是直接顺次交换过去。

- 如果这两个位置中间存在其余的 $\texttt{A}$。

	那么我们只考虑从最靠近最后一个 $\texttt{B}$ 的且在这个 $\texttt{B}$ 之前的 $\texttt{A}$ 开始交换，也就是说每一次都调换在一开始被标记的最后一个 $\texttt{B}$ 与最靠近最后一个 $\texttt{B}$ 的且在这个它之前的 $\texttt{A}$ 的位置。直到最后换到第一个 $\texttt{A}$ 才终止，最后答案也是他们两个的差。
    
由此得证。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>s;
		int lef=n,rig=-1;
		for(int i=0;i<n;i++){
			if(s[i]=='A'){
				lef=i;
				break;
			}
		}
		for(int i=n-1;i>=0;i--){
			if(s[i]=='B'){
				rig=i;
				break;
			}
		}
		if(lef<rig)cout<<rig-lef<<endl;
		else cout<<0<<endl;
	}
} 
```

update：

暂无。

---

## 作者：_anll_ (赞：3)

## 大体思路
考场上看到这种题，不妨先模拟一下它的过程。模拟后~~聪明的你一定~~发现交换结束后，A 总是在最前，B 总是在最后。所以在开头连续出现的 A 和在结尾连续出现的 B 显然对结果是没有任何贡献的。

所以我们只需要统计在开头连续出现的 A 和在结尾连续出现的 B 即可。

## 代码演示
~~这么简单的思路还需要代码吗。~~
```cpp
#include<iostream>
#define int long long
using namespace std;
int t,n,a,b;
string s;
signed main(){
	cin>>t;
	while(t--){
		a=b=0;
		cin>>n;
		cin>>s;
		for(int i=0;i<n;i++){
			if(s[i]=='A') break;
			b+=1;
		}
		for(int i=n-1;i>=0;i--){
			if(s[i]=='B') break;
			a+=1;
		}
		cout<<max(n-b-a-1,(int)0)<<endl;
	}
	return 0;
}
```


---

## 作者：zsh_haha (赞：2)

### 解题思路

与各位大佬们的思路不同，我们可以模拟调换字符的全过程，**尽量把每个 `B` 都往前移动**，这样就不会浪费每个可调换的机会。

字符串移动过程：

从前往后遍历每个字符，对于每个字符，进行如下操作：

1. 判断当前字符是否可以**往前移**，若可以，进入第二步，否则退出；

2. 交换当前字符和前一个字符，重点来了：**交换后应该跟着被移动的的字符，也就是说，指向字符的指针应随着字符移动，而不是停止在原来位置（若还不理解，可以结合代码理解）**，然后重复第一步。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[200001];
bool b[200001];
int main(){
	int t,n,ans,l;
	cin>>t;
	while(t--){
		memset(b,1,sizeof b);
		cin>>n>>c+1;
		l=1;
		ans=0;
		for(int i=2;i<=n;i++){
			int j=i;
			while(c[j]=='B'&&c[j-1]=='A'&&b[j-1]){//第一步：判断是否可以移动。
				swap(c[j],c[j-1]);//第二步：交换字符。
				b[j-1]=false;//标记当前位置为不可交换。
				j--;//重点：指针随着字符移动。
				ans++;
			}
		}
		cout<<ans<<endl;
	}
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

挺好的思维题。

首先，在前面出现的 $\texttt{B}$ 和在后面出现的 $\texttt{A}$ 肯定没用。

设第一个 $\texttt{A}$ 出现的下标为 $l$，第一个 $\texttt{B}$ 出现的下标为 $r$，那么对于 $[l,r)$ 之间的每个 $i$，都能进行一次操作。

证明：

首先我们考虑一个前面是 $\texttt{A}$ 后面是 $\texttt{B}$ 的 $s$。众所周知，$s$ 能进行 $|s|-1$ 次操作。

而我们就可以把 $[l,r]$ 分割成 $x$ 个上述的串，则根据上述结论，可以进行 $r-l-x$ 次操作。

我们继续考虑哪儿能进行操作：

我们发现，每个上述串执行完操作后第一项必为 $\texttt{B}$ 最后一项必为 $\texttt{A}$，所以在两个串的“接口”还能进行一次操作，也就是说，在 $[l,r]$ 中还能进行 $x-1$ 次操作作，总共就能进行 $r-l-x+x-1=r-l-1$ 次操作。

---

## 作者：kczw (赞：0)

# 题意
给定一个包含有字符 `A` 和字符 `B` 的字符串 $S$。

当字符串中有两种不同字符相邻并且字符 `A` 在左侧时，可以交换它们的位置。同时对于同一个位置 `A`，最多可以交换一次。

问对于 $S$ 最多可以交换几次。
# 思路
首先可以知道，所有交换结束后 $S$ 一定是左边全是字符 `B`，然后右边全是字符 `A`。

然后我们知道对于同种字符是不能交换的，所以我们就可以知道交换的范围是在从最左边的 `A` 到最右边的 `B`。

那么答案就显而易见了，因为每个位置最多交换一次，所以直接输出可以交换的区间的长度就可以了，也就是最右边的 `B` 的位置减去最左边 `A` 的位置。

当然如果只有 `A` 或者只有 `B` 要特判一下。
# 实现
```cpp
#include<iostream>
using namespace std;
int t,n;
char s[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%s",&n,s);
		int l=2e5+5,r=-1;
		for(int i=0;i<n;i++){
			if(s[i]=='A')l=min(l,i);
			else r=max(r,i);
		}if(l==2e5+5||r==-1||l>r)printf("0\n");
		else printf("%d\n",r-l);
	}
	return 0;
}
```

---

## 作者：_txb_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1896B)

## 思路：
如果 $A$ 在字母 $B$ 的下一个答案就加一，且把交换，再用一个标记数组把用过的打上标记，因为 $A$ 在后边和 $B$ 在前面没有用，我们要把 $B$ 往后调，把 $A$ 往前调。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s; 
int a[200005];
int main(){
	int t;
	cin>>t;
	while(t--)//多组数据 
	{
		memset(a,1,sizeof(a));//多组数据清空 
		int n,sum=0;
		cin>>n>>s;
		for(int i=1;i<n;i++)//遍历字符串 
		{
			int j=i;
			while(s[j]=='B'&&s[j-1]=='A'&&a[j-1])//前B后A且没换过 
			{
				swap(s[j],s[j-1]);//交换 
				a[j-1]=0;//标记 
				j--;//换位置 
				sum++;//答案+1 
			}
		}
		cout<<sum<<endl;//多组数据输出换行 
	}
    return 0;
}
```


---

## 作者：UncleSam_Died (赞：0)

### 解题思路
很简单的一道题，因为每个 `A` 只能向后移，每个 `B` 只能向前移，所以很容易想到，对于每一段连续的 `A`，直接往后移就是答案。但是因为每个坐标只能选择一次，那么，我们考虑用栈来维护这一过程：
- 如果当前位置上是 `A` 那么直接入栈；
- 如果当前位置上是 `B` 那么 $ans=ans+tail$，其中 $tail$ 表示当前栈中的元素的个数，同时，我们把 $tail$ 重置为 $\min(tail,1)$，从而避免有下标被重复选择，而之所以取 $\min$ 是因为在栈为空时不会有任何值的变化。

### AC 代码
```cpp
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#define N 200005
int n;char s[N];
inline void work(){
	scanf("%d",&n);
	scanf("%s",s);
	int ans=0,tail=0;
	for(register int i=0;i<n;++i){
		if(s[i]=='B'){
			ans+=tail;
			tail=std::min(tail,1); 
		}else tail++;
	}printf("%d\n",ans);
}signed main(){
	int T;scanf("%d",&T);
	while(T--) work();
}
```

---

