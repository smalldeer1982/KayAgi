# [DTCPC 2024] Ultra

## 题目背景

Tony2 喜欢玩某二字游戏，这一天他在小 C 面前展示他的 $\text{Ultra}$。

但是小 C 不会 $\text{Ultra}$，所以他跑去图图酱一去了。

~~然后图图失败了~~

于是小 C 趁 Tony2 不在的时候偷偷地把他的跳跃键和下冲键交换了（

## 题目描述

Tony2 的操作可以看作下冲和跳跃的组合。

称一个 $\text{Ultra}$ 为一段连续的操作，以下冲开头，然后跳跃和下冲交替，并以下冲结束。由于是 $\text{Ultra}$，所以至少要有一次跳跃。

小 C 每次可以将一个 $\text{Ultra}$ 变成 $\text{uLTRA}$，也就是将这个 $\text{Ultra}$ 的每个下冲变成跳跃，将每个跳跃变成下冲。

小 C 不喜欢 $\text{Ultra}$，所以想要使得下冲次数尽量少。

**形式化题意**

给你一个 $01$ 序列，你可以进行如下操作若干次（或零次）:

- 将序列中形如 $101\cdots01$ 的一个子串（即 $1(01)^k$，$k\ge 1$）替换成**等长**的 $010\cdots10$（即 $0(10)^k$）。

你要操作使得 $1$ 的个数尽可能少，输出最少的 $1$ 的个数。

## 说明/提示

样例 $1$ 解释：选中该串的前三个字符 $101$，对其操作后该串变为 $0100011$，仅包含 $3$ 个 $1$。容易证明这是最优的。

## 样例 #1

### 输入

```
1010011```

### 输出

```
3```

# 题解

## 作者：Register_int (赞：7)

比较恶心的一道题。

先来找找规律：如果是 $10101\cdots01$ 的序列，最少可以剩几个 $1$。

$$10101\cdots01\to01010\cdots10\to00101\cdots00\to\cdots\to00\cdots0100\cdots0$$

显然可以反复横跳到只剩一个。那如果是两个这样的序列拼起来呢？

$$10101101\to01010101$$

可以发现套娃又开始了，显然也能只剩一个。同时我们可以发现，只要他接上的是一个 $1$，就有：

$$101011\to010101$$

而且用 $1$ 连接的两个序列也是可以合并的：

$$1011\cdots101\to01011\cdots101\to\cdots$$

到最后中间的 $1$ 一定会被削完。

此时我们发现了一些性质，可以直接尝试定义合法的序列。它满足以下条件：

- $1(01)^k$ 是合法的 $(k\ge1)$。
- 若 $\text A$ 是合法的，则 $1\text A$ 与 $\text A1$ 是合法的。
- 若 $\text A,\text B$ 是合法的，则 $\text{AB}$ 是合法的。

那么一个合法序列最终必定能缩成只剩一个 $1$。此时的合法序列已经涵盖了所有我们可操作的序列了，直接用双指针处理出原字符串中所有极长的合法序列，手动将每个区间中 $1$ 全部删掉再补上一个即可，时间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;

int n, ans; char s[MAXN];

int l[MAXN], r[MAXN], sum[MAXN], cnt;

int main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	for (int i = 1; i <= n; i++) if (s[i] == '1') ans++;
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (s[i] & 1);
	for (int i = 1, j = 1, k = 0; i <= n; ) {
		if (s[i] != '1') { i++, k = 0; continue; }
		for (j = i; j + 2 <= n && s[j + 1] == '0' && s[j + 2] == '1'; j += 2);
		if (i != j) {
			if (cnt && r[cnt] + k + 1 == i) r[cnt] = j;
			else l[++cnt] = i - k, r[cnt] = j; k = 0;
		} else {
			if (cnt && l[cnt] != r[cnt] && r[cnt] + 1 == i) r[cnt]++;
			else k++;
		}
		i = j + 1;
	}
	for (int i = 1; i <= cnt; i++) ans -= sum[r[i]] - sum[l[i] - 1] - 1;
	printf("%d", ans);
}
```

---

## 作者：ran_qwq (赞：4)

以下称由连续两个 $0$ 划分而成的极大子段为连续段。

注意到操作后左右两边的字符由 $1$ 变为 $0$，也就是连续段会越来越小。

所以不同连续段独立。

对于一个连续段，如果它中间没有 $0$，那么就不能动。

否则可以通过一次操作将 $1$ 的个数减少 $1$，且当还剩大于一个 $1$ 时，将其中一个 $0$ 移到两个 $1$ 的中间来继续进行操作。

所以一个连续段可以消到只剩一个 $1$。

每个连续段答案相加即可。

```cpp
string s;
void QwQ() {
	cin>>s;int n=s.size(),ans=0,cnt=0,fg=0,st=0,en=n-1;
	while(st<n&&s[st]=='0') st++;
	while(~en&&s[en]=='0') en--;
	for(int i=st;i<=en;i++) {
		if(i<en&&s[i]=='0'&&s[i+1]=='0') {
			ans+=fg?1:cnt,cnt=fg=0;
			for(int j=i+1;j<=en;j++) if(s[j]=='1') {i=j-1;break;}
		}
		else cnt++,fg|=s[i]=='0'; 
	}
	wr(ans+(fg?1:cnt),"");
}
```

---

## 作者：Kao_Potato (赞：2)

# 题目翻译
给定一个只由 $01$ 构成的字符串，可以将形如 $101\dots01$ 的子串变为 $010\dots10$，问整个字符串经过操作后可以得到最小的 $1$ 的个数是多少。
# 思路
首先容易发现形如 $101\dots01$ 的子串最终都可以变为一个 $1$，因为每变换一次其变换后的中间部分都可以再变换一次，直到只剩下一个 $1$。

然后考虑将 $101\dots01$ 这样的子串向外延伸，如果相邻的是 $1$，即 $1101\dots01$，可以变换一次变为 $101\dots01$，最终也可以变为一个 $1$。

也就是说对于一个 $101\dots01$ 这样的子串，只要两边相接的不是连续两个 $0$，都可以不断延伸，最终变为一个 $1$，答案也就出来了。
# 代码
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int l,bj[1000005],ans;
char s[1000005];
int main(){
	scanf("%s",s+1);
	l=strlen(s+1);
	for(int i=2;i<=l;i++){
		if(s[i-1]=='1' && s[i]=='0' && s[i+1]=='1' && bj[i]==0){ //找到一个101且还没被统计过
			ans++; //最终剩余1的数量增加1
			int now=i;
			while(now>1){ //向左扩展
				bj[now]=1; //将能扩展到的地方都标记
				if(s[now-1]=='1' || s[now-2]=='1'){ //只要不是连续两个0就继续往左延伸
					now--;
				}else{
					break;
				}
			}
			bj[now]=1;
			now=i;
			while(now<l){ //向右扩展
				bj[now]=1;
				if(s[now+1]=='1' || s[now+2]=='1'){
					now++;
				}else{
					break;
				}
			}
			bj[now]=1;
		}
	}
	for(int i=1;i<=l;i++){
		if(s[i]=='1' && bj[i]==0){ //剩余没办法操作的1
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：jr_linys (赞：2)

[P10160 [DTCPC 2024] Ultra](https://www.luogu.com.cn/problem/P10160)

以长度大于一的连续 `0` 分割为若干段，若段中有子串 `101` 则整段可操作至只剩 $1$ 个 `1`，否则无法操作。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int ans=0;

signed main(){
	cin>>s;
	bool flag=0;//是否有 101
	int sum=0;//1 的个数
	for(int i=0;i<s.size();++i){
		if(s[i]=='0'){
			if(i&&s[i-1]=='0') ans+=(flag?1:sum),sum=flag=0;
		}else{
			++sum;
			if(i>2&&s[i-1]=='0'&&s[i-2]=='1') flag=1;
		}
	}
	ans+=(flag?1:sum);
	printf("%d",ans);
}
```

---

## 作者：CbrX (赞：2)

观察到一个事实：如果 $a_i=0$ 且 $a_{i+1}=0$ 则不存在一个操作 $[l,r]$ 满足反转了 $i$ 或者 $i+1$ 。

否则若反转了 $a_i$ 则一定有 $a_{i+1}=1$ ，若反转了 $a_{i+1}$ 则一定有 $a_i=1$ ，显然都矛盾。

因此每个这样的 $i$ 把序列分成了若干段，每一段都是形如 $11\cdots101\cdots101\cdots11$ 这样的段，也就是若干个 $1$ 连续段被单个的 $0$ 拼接。

当然也有可能没有 $0$， 这种情况无法操作，它的答案就是 $1$ 的个数。

如果有 $0$ 我们可以证明一定可以操作得到只剩一个。

其实很简单，只要保证每次都存在操作使得操作完还是形如上面描述的段就可以了，我们称这是合法的。

设 $1$ 连续段大小从左到右为 $b_1,b_2,\cdots,b_k$ ，我们选择 $b_1$ 这一段最靠右的 $1$ ，然后向右找到第一个 $b_i>1$ ，则我们操作 $b_1$ 最右边的 $1$ 到 $b_i$ 最左边的 $1$ 即可，容易验证它操作后还是合法的。

也有可能找不到这样的 $i$ ，这种情况我们操作 $b_1$ 最右边的 $1$ 到 $b_k$ 即可，同样也是合法的。

时间复杂度 $\mathcal{O}(n)$ 。 

核心代码：
```
for(int i=1,fl=0,last=0;i<=n;i++){
	if(!last)last=c[i]=='1'?i:0;
	else fl|=c[i]=='0';
	if(last&&c[i+1]=='0'&&c[i+2]=='0')ans+=fl?1:i-last+1,fl=last=0;
}
printf("%d\n",ans);
```

---

## 作者：zyn_ (赞：1)

# P10160 [DTCPC 2024] Ultra

## 题目大意

给你一个 $01$ 序列，你可以进行如下操作若干次（或零次）:

- 将序列中形如 $101\cdots01$ 的一个子串（即 $1(01)^k$，$k\ge 1$）替换成**等长**的 $010\cdots10$（即 $0(10)^k$）。

你要操作使得 $1$ 的个数尽可能少，输出最少的 $1$ 的个数。

## 题目分析

### 将序列分段

如果序列形为 $\dots 00\dots$，那么由操作的定义，不难得到 $00$ 的左右两部分互不影响。

也就是说，我们可以将原序列分成若干段（并去掉一些 $0$），分割的标志为两个及以上的 $0$。分割后，每一段中连续的 $0$ 至多一个。（分割会舍去序列中首尾的 $0$）

比如，$001011001101010$ 会分割为 $1011$ 和 $110101$ 两段。

显然，原序列的答案即为分割后的每个序列的答案之和。

### 处理每一段

#### 情况一

这一段形如 $11\dots 11$，全是 $1$。

无法操作，答案为这段的长度。

#### 情况二

这一段不全为 $1$。

**以下做一个约定：一次操作，限定为对一个极长的 $101\dots 01$ 子串替换为等长的 $010\dots 10$，也就是说不论如何向左右拓展这个子串都不能变成更长的 $101\dots 01$。**

先证明一个定理：对一个不存在连续 $2$ 个 $0$ 的序列，无论如何做以上的操作，均不会使序列**中间**出现连续 $2$ 个 $0$（序列两头可以出现）。

考虑序列

$$
xx\dots x1101\dots 011xx\dots xx
$$

**（其中 $x$ 为不知道也不重要的字符，下同。）**

由于极长串限制，左右两处 $11$ 是必要的。

做一次操作，变为

$$
xx\dots x1010\dots 101xx\dots xx
$$

也不在中间出现连续 $2$ 个 $0$。

*证明结束。*

设这一段形如 

$$
111\dots 11101xx\dots xx
$$

因为一段中不存在两个连续的 $0$，故第一个 $0$ 后为 $1$。

对第一个 $0$ 前面的 $1$ 做一次操作，变为

$$
111\dots 11010xx\dots xx
$$

对操作后新的第一个 $0$ 前面的 $1$ 再做一次操作，变为

$$
111\dots 10101xx\dots xx
$$

以此类推，最后变成

$$
10xx\dots xx
$$

紧接着，不断对以第一个 $1$ 为开头的极长 $101\dots 01$ 串做操作，则这一段最终将剩下 $1$ 个 $1$。为什么呢？

首先，由上面的定理，整个段在操作过程中不会“断”成两截。

其次，每次操作不断将第一个 $1$ 变为 $0$，且开头的 $101$ 变为 $010$，$010$ 后必然为 $1$，故操作后的开头变为 $0101$，即仍然为 $101$，可继续操作。

这样的操作，直到这一段结束为止，即 $101$ 变 $010$，成为一个孤立的 $1$。

因此无论这一段长什么样子，只要有了不含连续 $2$ 个 $0$ 的条件，就一定可以消成 $1$ 个 $1$。

事实上，也至少会留下 $1$ 个 $1$，因为操作是会产生 $1$ 的。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000009
char d[N];int n,l,r,ans;
inline int get(int l,int r){
	for(int i=l;i<=r;++i){if(d[i]=='0')return 1;}
	return r-l+1;
}
int main(){
	scanf("%s",d+1);n=strlen(d+1);
	d[0]=d[n+1]=d[n+2]='0';n+=2;
	l=1;r=0;
	for(int i=1;i<=n;++i){
		if(d[i]=='1')r=i;
		else if(d[i-1]=='0')ans+=get(l,r),l=i+1,r=i;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Determination_Y (赞：1)

### 【题目描述】

给你一个 $01$ 序列，你可以进行如下操作若干次（或零次）:

- 将序列中形如 $101\cdots01$ 的一个子串（即 $1(01)^k$，$k\ge 1$）替换成**等长**的 $010\cdots10$（即 $0(10)^k$）。

你要操作使得 $1$ 的个数尽可能少，输出最少的 $1$ 的个数。

### 【思路】

一开始看到这道题不会做，问老师，于是：

![Niveton](https://cdn.luogu.com.cn/upload/image_hosting/ax45lt2m.png)

于是开始自己造数据，把结论玩出来了。

首先考虑这样子的情况：`A00B`，$A,B$ 是一个 $01$ 序列。我们不难发现，对于这种情况，$A,B$ 不管怎么替换，都不可能将 $A,B$ 连在一起。于是我们有了第一步，将整个串分割开，分割条件是出现两个及以上连续的 $0$。

现在我们得到了一大堆 $01$ 序列，这些序列都没有两个及以上连续的 $0$。对于每一个序列，可以分为两种情况：

* $111\cdots111$：对于全部都是 $1$ 的串，我们无法对其进行操作，答案加上区间长度。
* $111\cdots101\cdots111$：对于其中至少有一个 $0$ 的串，我们一定有一种方法让他只剩下一个 $1$，答案加 $1$。证明过程放在最后。

于是这道题就做完了。

嗯。

### 【Code】

```cpp
#include <bits/stdc++.h>
using namespace std;

char s[1000005];
int n,ans;

//判断是否是区间开始
bool Is_start(int x){
	if(x==1&&s[x]=='1') return true;
	if(x==2&&s[x-1]=='0'&&s[x]=='1') return true;
	if(x>=3&&s[x-2]=='0'&&s[x-1]=='0'&&s[x]=='1') return true;
	return false;
}

//判断是否为区间结束
bool Is_end(int x){
	if(s[x]=='1'&&s[x+1]=='0'&&s[x+2]=='0') return true;
	return false;
}

//判断一个区间中是否有 0
bool No_zero(int l,int r){
	for(int i=l;i<=r;i++){
		if(s[i]=='0') return false;
	}return true;
}

int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	s[n+1]=s[n+2]='0';
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		if(Is_start(i)) l=i; //是区间开始
		if(Is_end(i)){	     //是区间结束
			r=i;
			if(No_zero(l,r)) ans+=r-l+1; //全部是 1，无法消去
			else             ans+=1;     //其中有 0，消到一个
		}
	}
	printf("%d",ans);
	return 0;
}
```

### 【证明】

**证明内容：一个至少包含一个 $0$ 的 $01$ 串，最后一定可以被消除到只剩一个 $1$ **

我们从这个 $01$ 串最右边的那个 $0$ 开始。

那么这个串可以表示为 $1\cdots1110111 \cdots 1A$ 的形式，$A$ 是一个 $01$ 串。

$\begin{array}{c}
\ \ \ \ \ \ \ \ {\color{Blue}1} \cdots {\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1} \cdots {\color{Blue}1}A \\
\Longrightarrow {\color{Blue}1} \cdots {\color{Blue}1}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1} \cdots {\color{Blue}1}A \\
\Longrightarrow {\color{Blue}1} \cdots {\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1} \cdots {\color{Blue}1}A \\
\Longrightarrow {\color{Blue}1} \cdots {\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0} \cdots {\color{Blue}1}A 
\end{array}$

在替换的这个串的左边会碰到这个串的边缘：

$\begin{array}{c}
\ \ \ \ \ \ \ \ {\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0} \cdots A \\
\Longrightarrow {\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1} \cdots A \\
\Longrightarrow {\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0} \cdots A \\
\Longrightarrow {\color{Blue}1}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1} \cdots A \\
\Longrightarrow {\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0} \cdots A \\
\Longrightarrow {\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1} \cdots A \\
\Longrightarrow {\color{Red}0}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0} \cdots A \\
\Longrightarrow {\color{Red}0}{\color{Red}0}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1} \cdots A \\
\Longrightarrow {\color{Red}0}{\color{Red}0}{\color{Red}0}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0} \cdots A \\
\Longrightarrow {\color{Red}0}{\color{Red}0}{\color{Red}0}{\color{Red}0}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1} \cdots A \\
\end{array}$

然后慢慢缩回来。

而它的右边则有两种情况：

* 碰到 $1$，一起改变掉。

* 碰到 $0$：

  $\begin{array}{c}
  \ \ \ \ \ \ \ \ {\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1} \cdots A \\
  \Longrightarrow {\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1} \cdots A \\
  \Longrightarrow {\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1} \cdots A \\
  \Longrightarrow {\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1} \cdots A \\
  \Longrightarrow {\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1}{\color{Blue}1} \cdots A \\
  \Longrightarrow {\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Blue}1} \cdots A \\
  \Longrightarrow {\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1}{\color{Red}0}{\color{Blue}1} \cdots A \\
  \end{array}$

---

## 作者：lzkAK2009 (赞：1)

## 分析
在尝试中，我们能发现本题有非常多的规律。下面是我用来解决和优化算法的规律：
1. $1$ 个 Ultra 最终能被转换为 $1$。因为 $1$ 个 Ultra 转换后，就是 `0` $+$ $k$ 小 $1$ 的 Ultra $+$ `0`，最终一定能转换为 $1$。
2. `00` 分割开的两段互不影响，所以我们可以把超过两个的 `0` 改写为 `00`。
3. 若干个相连的 `1` 在转换的过程中和 $1$ 个 `1` 是等价的，即最后都会只剩 $1$。所以我们可以把若干个相连的 `1` 改写为一个 `1`，但需要记录它实际的个数，防止它无法被转化。

这样子，我们就把原来的字符串改写成了若干个被 `00` 分开的 Ultra 或只有一个 `1`。因此，我们可以每遇到一个 `00` 就统计一下上一个 Ultra 或 `1` 的答案。如果是 Ultra，答案就是 $1$；如果不是，就是其中含有的 `1` 的个数。但需要注意，原字符串结尾不一定有 `00`，应该在其后加上 `00` 再改写。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int ans, num[1000005] /*一个点压缩的1的数量*/;

char s[1000005] /*原字符串*/, t[1000005] /*改写后的字符串*/;

int main () {
	scanf ("%s", s + 1);
	int len = strlen (s + 1);
	s[len + 1] = s[len + 2] = '0'; //末尾加两个0
	len += 2;
	int j = 0, k = 0, l = 0;
	for (int i = 1; i <= len; i++) { //改写字符串
		if (j == 0 && s[i] == '0')
			continue; //最前面的0无意义
		if (s[i] == '1') {
			k++; //统计1的数量
			l = 0; //0的数量归零
			if (k > 1) {
				num[j]++; //这个点压缩数量加1
				continue;
			}
		}
		else {
			l++; //统计0的数量
			k = 0; //1的数量归零
			if (l > 2)
				continue; //大于2个0，后面的省略
		}
		t[++j] = s[i];
	}
	bool pan = 0 /*前一个是0*/ , flag = 0 /*前一个是1*/ ;
	for (int i = 1; i <= j; i++) {
		if (t[i] == '1') {
			if (pan) {
				flag = 1;
				pan = 0;
			}
		}
		else {
			if (!pan)
				pan = 1;
			else { //两个0，统计答案
				pan = 0;
				if (flag) { //是Ultra，答案加1
					ans++;
					flag = 0;
				}
				else ans += num[i - 2] + 1; //是1，答案加压缩的个数+1
			}
		}
	}
	cout << ans;
	return 0;
}
``````

---

## 作者：SICKO (赞：0)

观察题目，我们得知我们可以处理形如 $1(01)^k$，$k\geq1$ 的串，次数不限。

模拟一下我们就会发现，如果出现了形如 $(0)^k$，$k\geq2$ 的串，左右的结果将会互不干扰；对于被切开的串，只要**不是**形如 $(1)^k$，$k\geq2$ 的串，就可以最终被处理为只有**一个**一。

压缩题目所给的串后模拟即可。

```c++
#include<iostream>
using namespace std;
const int N = 1e6+6;
char a[N];
int num[N];
int main(){
    cin>>(a+1);
    int n=0; while(a[n+1]) n++;
    // 不难发现 在开头的0一点用都没有
    a[0] = '&';
    int i=1, idx=0;
    while(a[i]=='0') i++;
    for(; i<=n; i++){
        if(a[i]==a[i-1]) num[idx]++;
        else num[++idx]++;
    }
    if(idx%2!=0) num[++idx]=100; // 思考为什么加一
    else num[idx] += 100;
    // 如何判断出现 101 很简单 偶数位上出现 0 即可
    // 有没有更快的方法 有 找上次 0^k 出现的地方 判断距离
    int res = 0, last=0;
    for(int j=1; j<=idx; j++){
        if(j%2==0 && num[j]!=1 && j-last>2){
            last = j;
            res += 1;
        }
        if(j%2==0 && num[j]!=1 && j-last==2){
            res += num[j-1];
            last = j;
        }
    }
    cout<<res;
    return 0;
}
```

---

## 作者：WZWZWZWY (赞：0)

规律题。（~~还没写完作业就来水题解的我真伟大~~）

因为以下内容大多是字符串中的某段，所以就说成字符段便于理解。


------------

题目说的是什么呢？

`101` 可以变成 `010`，`10101` 可以变成 `01010`……以此类推，每个由 `01` 交替且最左和最右为 $1$ 的字符段都能被取反。

我们发现**这样的字符段取反后 $1$ 的个数会变少 $1$ 个**，然后题目问最少的 $1$ 的个数。

没思路，只能举例子找规律。

+ $10101010$

可以转换成：

+ $01010100$

再转换：

+ $00101000$

+ $00010000$

最后竟然只剩一个 $1$！

1. **这说明所有类似 $1010101$ 的字符段化简后都只剩一个 $1$。**

再举例子：

+ $10010101001$

化简一下中间的一段后为

+ $10001010001$

欸？化简后，中间的 $1$ 离两边的 $1$ 更远了，再化简肯定更不能与两边的一组合了。所以：

2. **两个距离大于等于 $2$ 的数字 $1$ 永远不能组合并化简。**

再造数据。

+ $1010111$

+ $0101111$

+ $0010111$

+ $0001011$

+ $0000101$

+ $0000010$

化简成功了！看来只要有 $...10$，后面有连续的 $1$ 也能行。

但是交上去 `WA` 了，因为我忘记了前面也有连续 $1$ 的情况……（大概只有我这么菜）

可以用一个 $vis$ 数组存是否被判定为连续的后面的 $1$ 过。否则就是下一段的前面的连续 $1$。

比如 $10101110101$，如果前面使用了连续$1$，需要被记录。

3. **要判断连续 $1$ 的存在**。




------------

## 代码：

（我太菜了，所以代码很长……）


```
#include <bits/stdc++.h>
using namespace std;
char c[1000005];
bool vis[1000005];
int ans = 0;
int main() {
	cin >> c;
	int n = strlen(c);
	for (int i = 0; i < n; i++) {
		if (c[i] == '1' && c[i + 1] == '0') { //化简 
			ans++;
			while (i < n) {
				if (c[i] == '0' && c[i + 1] == '0') break; //连续两个0，不能化简 
				int k = i - 1;
				if (c[i + 2] == '1') // 判断前面的连续1 
					while (k >= 0 && !vis[k] && c[k]=='1'){ 
						ans--;
						k--;
					}
				vis[i] = 1;
				i++; //继续化简 
			}
		}
		else if ((c[i] == '1' && c[i + 1] == '1') || (c[i] == '1' && i == n - 1)) ans++; // 后面连续1和末尾的单独1 
	}
	cout << ans;
}

```

还有什么不懂的可以问我哦。

---

## 作者：Night_sea_64 (赞：0)

赛时这道题调了好久。

首先，$101\cdots01$ 可以经过多次操作变成一个 $1$，这非常显然。

其次，$11\cdots1101\cdots0111\cdots1$ 可以经过多次操作变成一个 $1$。下面展示一下：

```
11101011111
11010101111
10101010111
01010101011
00101010101
```

然后就是上面那种形式。

接下来，$10111\cdots1101$ 可以经过多次操作变成一个 $1$。下面展示一下：

中间 $1$ 的个数为奇数：

```
101111101
010111010
001010100
```

中间 $1$ 的个数为偶数：

```
10111101
01011010
00101010
```

可以发现都能变成最上面那种形式。

于是总结一下：一堆 $101\cdots01$ 的子串，相邻两个中间都是 $1$，那么它们能通过多次操作变成一个 $1$。找出这些段当然很容易。

```cpp
#include<iostream>
using namespace std;
int sum[1000010],l[1000010],r[1000010],cur;
int main()
{
    string s;
    cin>>s;
    int n=s.size();
    s=' '+s;
    int last=0,ans=0;
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+(s[i]=='1');
    for(int i=1;i<=n;i++)
        if(s[i]-'0'!=(i-last)%2)
        {
            if(s[i]=='0')
            {
                if(last<i-3)
                    l[++cur]=last+1,r[cur]=i-2;
                last=i;
            }
            else
            {
                if(last<i-2)
                    l[++cur]=last+1,r[cur]=i-1;
                last=i-1;
            }
        }
    if(s[n]=='0')
    {
    	if(last<n-2)l[++cur]=last+1,r[cur]=n-1;
    }
    else
    {
    	if(last<n-1)l[++cur]=last+1,r[cur]=n;
    }
    last=1;
    for(int i=1;i<=cur;i++)
    {
    	//cout<<l[i]<<" "<<r[i]<<" "<<last<<endl;
        if(i>1)
        {
            if(sum[l[i]-1]-sum[r[i-1]]<l[i]-1-r[i-1])
            {
                while(l[last]>1)
                    if(s[l[last]-1]=='1')l[last]--;
                    else break;
                while(r[i-1]<n)
                    if(s[r[i-1]+1]=='1')r[i-1]++;
                    else break;
                for(int j=l[last];j<=r[i-1];j++)s[j]='0';
                ans++,last=i;
            }
        }
    }
    if(cur)
    {
	    while(l[last]>1)
	        if(s[l[last]-1]=='1')l[last]--;
	        else break;
	    while(r[cur]<n)
	        if(s[r[cur]+1]=='1')r[cur]++;
	        else break;
	    for(int i=l[last];i<=r[cur];i++)s[i]='0';
	    ans++;
    }
    for(int i=1;i<=n;i++)ans+=(s[i]=='1');
    cout<<ans<<endl;
    return 0;
}
```

Upd：上面的是赛时的 sb 做法。其实也就是一个子串只要中间没有两个连续 $0$ 就能变成一个 $1$……

---

## 作者：言琢დ (赞：0)

结论题。

首先，连续的 $\tt 10101\cdots 10101$ 可以被缩成 $\tt 000\cdots010\cdots000$，只剩一个 $\tt 1$。

方法的话，就是每次把整条序列（从第一个 $\tt 1$ 到最后一个 $\tt 1$）操作一遍，显然中间又会形成长度递减的 $\tt 101\cdots101$ 串。

另外，如果这种 $\tt 10101$ 串的左右两边没有 $\tt 00$ 字段，它可以无限延伸。

考虑一个简单的假设，$\tt 101111$，可以先对 $\tt 101$ 变成 $\tt 010$，接着发现原序列 $\tt 010111$，平白无故地少掉了边缘的一个 $\tt 1$。

以此类推，只要没有 $\tt 00$ 子段拦路，就可以一直延伸，把整条序列全部变成 $\tt000\cdots010\cdots000$。

代码如下：

```cpp
const int N = (int) 1e6 + 5;
char s[N];
int main(){
  scanf("%s", s+1);
  int len = strlen(s+1), ans = 0;
  s[0] = s[len+1] = '0';
  for (int i = 1; i <= len; ++i)
    if (s[i] == '1' && s[i+1] == '0' && s[i+2] == '1') {
      int j;
      int x;
      for (x = i-1; x >= 1; --x)
        if (s[x] == '0' && s[x-1] == '0') break; // 此后只要没有 00 拦着，就能一直延续
      int y;
      for (y = i+3; y <= len; ++y)
        if (s[y] == '0' && s[y+1] == '0') break; // 此后只要没有 00 拦着，就能一直延续
      for (int j = x+1; j <= y-1; ++j)
        s[j] = '0'; // 这一段全部都可以变成 0
      s[i+1] = '1';
    }
  for (int i = 1; i <= len; ++i)
    ans += s[i] == '1';
  print(ans), putchar('\n');
}
```

---

## 作者：lovely_codingcow (赞：0)

## 题意 

给定一个 01 串，可以将串中的 `1010101...010101` 替换为 `0101010...101010` 反之亦然。求可能的最小的 `1` 的数量。

## 思路

我们可以发现，如果有连续的多个（$\geq2$）$0$，那么我们不可能将连续 $0$ 左侧或右侧的一起处理。因此，为了方便，我们可以将左右两侧分开处理。当我们将左右两侧分到无法再分的程度时，我们再次观察。

容易发现，去除两侧的前导零和后缀零之后，如果剩下的部分中仍有 $0$，那么这个部分一定可以被化简为只有 $1$ 个 $1$ 的串；如果没有 $0$，那么这个部分不能再被任何方式化简，故该部分的 $1$ 的数量为剩余的部分的长度。

## 实现

这道题的实现有一个巨大的坑。我们考虑使用 DFS 来处理。一开始，我将待处理的字符串作为参数传递进去，但是很显然这样会占用大量的内存，我赛时就是没有注意到这一点导致了 MLE 遗憾离场。为了解决这样的问题，我们可以只传递起始和结尾的下标，然后共用全局的字符串。这样就可以非常有效的避免 MLE 的问题，轻松又愉快的 AC。

```cpp
#include <iostream>

#define int long long

using namespace std;

int n, a, b, cnt, ccnt, ans;
string s;

void dfs(int L, int R) {
    int cnt = 0;
    for (int i = L; i < R; i++) {
        if (s[i] == '1') {
            if (cnt > 1) {
                dfs(L, i - cnt);
                dfs(i, R);
                return;
            }
            cnt = 0;
        } else {
            cnt += 1;
        }
    }
    int l = L, r = R - 1;
    while (l <= r && l < R && s[l] == '0') {
        l += 1;
    }
    while (l <= r && r >= L && s[r] == '0') {
        r -= 1;
    }
    for (int i = l; i <= r; i++) {
        if (s[i] == '0') {
            ans += 1;
            return;
        }
    }
    ans += r - l + 1;
}

signed main() {
    cin >> s;
    dfs(0, s.size());
    cout << ans;
}
```

---

