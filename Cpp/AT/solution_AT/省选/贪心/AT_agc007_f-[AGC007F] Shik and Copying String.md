# [AGC007F] Shik and Copying String

## 题目描述

Shikk 的工作是复制。有一天，Shikk 从他的上司那里拿到了一个由小写英文字母组成的长度为 $N$ 的字符串 $S_{0}$（假设这天是第 $0$ 天）。这之后第 $i$ 天的工作是把 $S_{i-1}$ 复制到 $S_{i}$。下文中的 $S_{i}[j]$ 表示字符串 $S_{i}$ 的第 $j$ 个字母。

Shikk 还不怎么习惯这个工作。每天，当 Shikk 从第一个字母开始按顺序复制字符串时，他有可能会写下和刚刚写下的字母相同的字母，而不是本来应该写下的字母。也就是说，$S_{i}[j]$ 要么与 $S_{i-1}[j]$ 相同，要么与 $S_{i}[j-1]$ 相同。（特别地，字符串开头的字母不可能出错。也就是说，$S_{i}[1]$ 必然与 $S_{i-1}[1]$ 相同。）

输入两个字符串 $S_{0}$ 和 $T$，请求出使得 $S_{i}$ 有可能与 $T$ 相同的最小的整数 $i$。如果这样的 $i$ 不存在，请输出 $-1$。


## 样例解释

#### 样例 1 解释

一种可能的最佳方案：$S_{0}= \texttt{abcde}$，$S_{1} = \texttt{aaccc}$，$S_{2} = \texttt{aaacc}$。

## 说明/提示

- $1\le N\le 10 ^ 6$；
- $S_{0}$ 和 $T$ 的长度都等于 $N$；
- $S_{0}$ 和 $T$ 均只由小写英文字母组成。

## 样例 #1

### 输入

```
5
abcde
aaacc```

### 输出

```
2```

## 样例 #2

### 输入

```
5
abcde
abcde```

### 输出

```
0```

## 样例 #3

### 输入

```
4
acaa
aaca```

### 输出

```
2```

## 样例 #4

### 输入

```
5
abcde
bbbbb```

### 输出

```
-1```

# 题解

## 作者：ouuan (赞：26)

[博客链接](https://ouuan.github.io/AGC007F-Shik-and-Copying-String%EF%BC%88%E8%B4%AA%E5%BF%83%EF%BC%8C%E5%AE%9E%E7%8E%B0%EF%BC%89/)

## 题目链接

[洛谷](https://www.luogu.org/problem/AT2173)

[AtCoder](https://atcoder.jp/contests/agc007/tasks/agc007_f)

## 题意简述

给你初始串 $S_0$ 和目标串 $T$，每一步操作可以将当前串 $S_i$ 变成 $S_{i+1}$，其中：

$$S_{i+1}[j]=\begin{cases}S_i[1]&j=1\\S_i[j]\text{ 或 }S_{i+1}[j-1]&j>1\end{cases}$$

求最少需要几次操作可以将当前串变为 $T$。

串长 $10^6$。

这题题解真的难写..之前觉得别人的题解写的不清楚，然而自己也写的不是很清楚...

## 简要做法

首先，这个过程可以用折线表示：

![ ](https://i.loli.net/2019/08/18/1786yhidmZVzUwo.png)

（如果您在色觉方面存在障碍，还请见谅。）

可以发现，每条折线都尽量靠右是最优的，一旦画不下了，就加一行。

现在问题变成了如何高效地维护这一贪心。

当 $S_0=T$ 时，先特判掉，输出 $0$。

由于每次拐点都会往左下移动一格，我们可以用队列来维护当前折线的每个拐点（折线往右拐的点，也就是 $S_i[j]=S_i[j-1]$ 的 $j-1$ 这个点）（不包括最后一行的拐点），其中靠近队首表示靠下（离 $T$ 较近）的拐点，靠近队尾表示靠上（靠近 $S_0$）的拐点。

详见代码（因为这题文字写出来不如代码好理解）：

## 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int n, ans;
string s, t;
queue<int> q;

int main()
{
    cin >> n >> s >> t;

    if (s == t) // 特判两串相等
    {
        puts("0");
        return 0;
    }

    int up = n - 1, down = n - 1;

    while (down >= 0)
    {
        while (down && t[down - 1] == t[down]) --down; // 找到当前折线在最后一行最左的位置
        while (up >= 0 && (up > down || s[up] != t[down])) --up; // 找到当前折线在第一行最左的位置
        if (up < 0) // 如果第一行没有对应的字符，输出无解
        {
            puts("-1");
            return 0;
        }
        while (!q.empty() && q.front() - q.size() >= down) q.pop(); // 把当前折线不会碰到的部分弹出
        if (up != down) q.push(up); // 如果当前折线真的是“折线”而不是竖直下来不拐弯，就把 S1 的拐点压入队列
        ans = max(ans, (int)q.size() + 1); // 后文会解释为什么这样更新答案
        --down;
    }

    cout << ans;

    return 0;
}
```

## 补充说明

这个维护拐点的方式应该画画图就能明白。

最后剩下一个问题：为什么是这样更新答案？

换句话说：为什么答案是拐点个数的历史最大值？（加一是因为没有维护最后一行的拐点）

如果没有这个 pop 操作，应该是很显然的。但 pop 操作破坏了“队列中每个元素对应除最后一行外每一行最左位置”这个性质。

这里需要一个引理：

> 除了最后一行的拐点，其它拐点一定位于连续的前几行。

我们可以归纳地证明：

- 对于最右的那条折线，显然成立。
- 对于之后的每条折线，一定是先贴着上一条折线，再直接往下到最后一行。由于上一条折线满足引理，如果中途有一段没有拐点而后又出现拐点，中途的那一段就没有紧贴上一条折线。

有了这个引理，就可以~~感性理解~~说明为什么有 pop 操作的情况下答案依然是拐点个数的历史最大值了。

---

## 作者：command_block (赞：20)

**题意** : 定义字符串的复制操作如下 ：

将字符串 $S$ 复制得到 $S'$。则 $|S'|=|S|$ ，且 $S'[1]=S[1]$ ，而 $S'[i]=S[i]$ 或者 $S'[i-1]$。

现在给出字符串 $S,T$ ，问 $S$ 至少经过几次复制之后可以得到 $T$。

$|S|\leq 10^6$ ，时限$\texttt{2s}$。

------------

首先特判 $S=T$。

考虑 $T$ 中的每个字符来源于 $S$ 中的那个字符，表示对应关系的边是不会相交的，且一定是一个字符对应一个区间。

假设我们得知了对应关系和所需步数，那么可以采取这样的策略 ： 先一直尽量右移，直到移动到需要覆盖的左边界处，然后向下到达底线，然后横向覆盖。（实际上就是让路径尽量靠右）

如图 ：

![](https://cdn.luogu.com.cn/upload/image_hosting/5vcyvglv.png?x-oss-process=image/resize,w_500)

不难证明这是最优策略。

考虑我们得知了对应关系，如何得到最优步数。

我们从后往前考虑每个 $T$ 中需要匹配的左端点，让路径尽量靠右，若目前的层数无法完成，则加一层。

具体地，用**队列**维护上一条路径的所有（右侧）转折点。这些转折点的横纵坐标都是单调增加的。

当 $S_i$ 要前往 $T_j$。

末端弹出（pop）那些横坐标在 $j$ 后面的所有转折点。

然后，所有转折点都向左下方移动一位。

若起点衔接不紧密，则会新增（push）一个转折点。如图 ：

![](https://cdn.luogu.com.cn/upload/image_hosting/6aser8dt.png?x-oss-process=image/resize,w_400)

（深蓝色是上一条路径的转折点，深红色是新路径的转折点）

答案是所有转折点的纵坐标的最大值 $+1$。

若事先未给定匹配关系，从后往前考虑 $T$ ，贪心地选择 $S$ 中能匹配的最靠右的字符即可。

复杂度为 $O(n)$。

```cpp
#include<algorithm>
#include<cstdio>
#define MaxN 1005000
using namespace std;
char s[MaxN],t[MaxN];
int n,pre[MaxN],p[255],ans,ql,qr;
struct Data{int i,j;}q[MaxN];
int main()
{
  scanf("%d%s%s",&n,s+1,t+1);
  bool fl=1;
  for (int i=1;i<=n;i++)
    if (s[i]!=t[i])fl=0;
  if (fl){puts("0");return 0;}
  for (int i=1;i<=n;i++){
    pre[i]=p[s[i]];
    p[s[i]]=i;
  }
  int ql=1,qr=0;
  for (int i=n,las=n+1,c=0;i;i--){
    if (t[i]==t[i-1])continue;
    while(p[t[i]]>min(las,i))p[t[i]]=pre[p[t[i]]];
    if (!p[t[i]]){puts("-1");return 0;}
    int u=p[t[i]],v=i;
    while(ql<=qr&&v<q[ql].i-c+1)ql++;
    if (las!=u&&u<v)q[++qr]=((Data){u+c,1-c});
    if (ql<=qr)ans=max(ans,q[ql].j+c);
    c++;las=u;
  }printf("%d",ans+1);
  return 0;
}
```

---

## 作者：tommymio (赞：4)

做这种没啥想法的题，先考虑特殊情况，再考虑一般情况。

特殊情况有：

- $S_0=T$。
- $S_0\to T$ 只需要移动一种字符。如 $ababc\to abaaa$

从第二种情况推广。如果需要移动两种字符呢？我们将每次变换中字符移动的轨迹用折线画出来，存在两种情况，轨迹相交或者不相交。相交的情况自然是不合法的，我们加上一步就能让它合法。进而拓展到当前字符移动轨迹与 $m$ 个字符移动轨迹相交的情况，我们需要加上 $m$ 步才能让它合法。对于必要步数取最大值即可，时间复杂度为 $O(n)$。

具体做法使用一个队列维护之前字符移动的轨迹，只需记录起点就可大致表示出这一轨迹。注意，如果在 $S_0,T$ 中位置 $x$ 上的字符都没有变，那么不需要考虑，因为一定不会有之前的移动轨迹与它相交。最终 $ans$ 还需 $+1$，因为没有考虑到达 $T$ 的一步。

以上算法正确性基于移动轨迹尽可能靠右是最优的，不会更劣。

```cpp
#include<cstdio>
#include<cstring>
char s[1000005],t[1000005];
int q[1000005];
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline int max(const int &x,const int &y) {return x>y? x:y;}
int main() {
	int n,hd=1,tl=0,ans=0;
	scanf("%d%s%s",&n,s,t);
	if(!strcmp(s,t)) {printf("0\n");return 0;}
	for(register int i=n-1,pos=n-1;i>=0;--i) {
		if(t[i]==t[i-1]) continue;
 		pos=min(pos,i);
		while(pos>=0&&s[pos]!=t[i]) --pos;
		if(pos==-1) {printf("-1\n");return 0;}
		while(hd<=tl) {
			if(q[hd]-(tl-hd+1)+1>i) {++hd;}
			else {break;}
		}
		q[++tl]=pos;
		if(i!=pos) ans=max(ans,tl-hd+1);
	}
	printf("%d",ans+1);
	return 0;
}
```

---

## 作者：jucason_xu (赞：1)

首先，我们来证明一个引理：

+ 若最优解中，最终串中的字符 $j$ 在最早来自原串中的字符 $i$（显然，$i\le j,s_i=t_j$），则称 $j$ 的匹配是 $i$，则在所有的匹配方案中，$t_j$ 会在全串存在匹配的前提下尽量选择 $|i-j|$ 最小的的 $s_i$ 进行匹配。

我们可以运用数学归纳法。

第一，显然所有 $t$ 中字符的匹配单调不降，设结论在后缀对 $(i,j+1)$ 成立，那么如果 $x<y\le i$，$s_x=s_y=t_j$，因为匹配不交叉，所以用 $s_x$ 匹配的操作 $s_y$ 都能做，$s_y$ 能做的 $s_x$ 却不一定能做，并且 $j$ 后面的都被 $i$ 后面的匹配完了，所以 $y$ 只要存在就一定可以选（而不会和后面产生冲突，所以对于 $(i,j)$ 成立。

接着，对于 $(i+1,j)$ 成立，$(i,j)$ 必然成立，这是显然的。

又有对后缀 $(n,n)$ 成立（没有后面的可以干扰），所以就全部成立了。

我们就可以倒着匹配跑出每个位置的最优匹配。如果匹配不存在，直接输出 $-1$。

到这里，就一定有解了，因为我们显然可以做 $n$ 次倒着依次满足所有的匹配。然后考虑如何计算最小操作次数。

首先，我们构造匹配段，设 $r_i$ 是匹配到 $i$ 的最大的位置，那么显然最终匹配到 $i$ 的是一段区间 $[l_i,r_i](i\le l_i)$。

在这里，我先观察一些数据，写了一个假的贪心，我猜答案是特判掉不操作之后，每个位置被 $[i,r_i]$ 覆盖次数的最大值。但是这是一点依据都没有的假做法。

那么，我们把所有有匹配的 $i$ 依次罗列出来，开始考虑暴力一点的做法。

我们设所有有匹配的 $i$ 一共有 $m$ 个，每个对应一段区间 $[a_i,b_i]$，其中 $a_i$ 就是原始的起点，$b_i$ 就是 $r_{a_{i}}$。

然后我们把原先的操作映射上来，其实就是要通过若干次增加 $a$ 数组的方式到达 $b$，我们设 $a_{i,j}$ 表示 $i$ 次操作之后，匹配 $j$ 所扩展到的最右端。每次扩展的时候，$a_{i,j}$ 必须小于 $a_{i-1,j+1}$（否则会完全把后一种匹配覆盖掉）。

然后我们就得到了一个 $O(n^2)$ 的做法，暴力扩展 $a_{i,j}$ 为 $\max\{a_{i-1,j+1}-1,a_{i-1,j},b_j\}$，因为答案一定不超过 $n$，所以复杂度是 $O(n^2)$。

考虑优化。

我们发现，我们上面能这样做的原因是我们只需要考虑每个匹配所达到的最右端。只要最右端都符合条件，因为 $b_i$ 是单调增的，然后前一个的最右端又不会跑到自己这边来，自己从 $a_i$ 过来已经把这一段全部染过一次了，所以就达成目的了。

然后我们重新定义 $t_{i,j}$ 为 $i$ 轮操作之后 $a_j$ 的理论最大值。也就是在只有限制条件小于 $a_{i-1,j+1}$ 下，所能达到的最大值。

很明显，每轮操作之后，最后一个数就变成 $+\inf$ 了。

然后我们考虑这个理论最大值和实际最大值的关系。我们发现，实际最大值只是在拓展的过程中多了一个 $b_i$ 的限制。而这个限制一旦达到，我们这里也就达成了，不需要再往后了。然后如果 $j+1$ 已经受限了，因为 $b_j<b_{j+1}$，所以我们也一定可以直接一步达到 $b_i$。

所以，只要 $a_{i,j}=\min(t_{i,j},b_j)$ 即可。

考虑计算 $t_{i,j}$ 什么时候大于等于 $b_j$，我们发现，因为 $t_i$ 单调递增，所以每轮直接用 $t_{i-1,j+1}-1$ 作为 $t_{i,j}$ 一定最优，那么 $k$ 轮之后就是 $t_{i-k,j+k}-k$。

我们成功的把问题转化成找到最小的 $j$ 使得 $j-i$ 次迭代之后，$a_j-(j-i)$ 要大于等于 $b_i$，重新写一下，就是最小的 $j$ 使得 $a_j-j\ge b_i-i$，$res_i=j$，$ans=\max_{i=1}^n(res_i-i)$。

这个问题显然可以直接用树状数组求解，我们就得到了一个 $O(n\log n)$ 的做法，也就可以通过了。

```cpp
int n,r[1000005],b[1000005];
int a[1000005],m;
st s,t;
int fen[2000005];
inline void add(int x,int v){
	for(;x<=n;x+=(x&(-x)))fen[x]=min(fen[x],v);
}
inline int qry(int x){
	int res=m+1;
	for(;x;x-=(x&(-x)))res=min(res,fen[x]);
	return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>s>>t;
	s='$'+s,t='$'+t;
	if(s==t){
		cout<<0<<endl;
		return 0;
	}
	for(int i=n,j=n;i>=1&&j>=1;j--,i=min(i,j)){
		while(i>=1&&s[i]!=t[j])i--;
		if(!i){
			cout<<-1<<endl;
			return 0;
		}r[i]=max(r[i],j);
	}
	rp(i,n)if(r[i])a[++m]=i,b[m]=r[i];
	rp(i,m)a[i]-=i,b[i]-=i; 
	int ans=0;
	rep(i,1,n)fen[i]=m+1;
	per(i,1,m){
		ans=max(ans,qry(n-b[i])-i);
		add(n-a[i],i);
	}
	cout<<ans<<endl;
	return 0;
}
//Crayan_r
```

这版代码调试了不短的时间，尤其是最后 RE 两个点的时候，主要问题在于树状数组的值域。首先，$a_i-i$ 和 $b_i-i$ 的值域是 $[0,n-1]$。然后逆转偏序关系，用 $n-a_i+i$ 来代替就可以做到 $[1,n]$ 的树状数组。但是我在一开始分析的时候，把 $a_i-i$ 的值域当作了 $[-m,m]$，从而使用 $2m-a_i+1$ 代替（实际上并没有仔细思考），这样最后是 RE 两个点，最终通过是使用 $M=10^6$ 以及 $2M$ 的值域通过这题。但是后来经过分析，才得出了正确的结论，也就有了上面的最优版代码。

但是 $O(n\log n)$ 不是终点！

我们发现，因为 $a_i$ 是单调增的，所以 $a_i-i$ 是单调不降的。也就是说，我们查找的序列是满足单调性的。可以优化掉 Fenwick Tree，直接用 two pointers 即可。

然后还有一点不起眼的小优化，我们发现，我们可以在处理匹配的同时计算答案。因为每个 $i$ 第一次被匹配到一定是被 $r_i$ 匹配的，所以如果我们保存每个位置有没有被匹配过就可以计算了。

但是这里还存在一个问题，我们从后往前，还不知道有多少个位置，如何知道 $a_i-i$ 中的 $i$ 呢？实际上，我们可以把比较 $a_i-i$ 和 $b_i-i$ 转化成比较 $a_i+m-i+1$ 和 $b_i+m-i+1$，而后面的 $m-i+1$ 就是从后往前跑的时候的编号。这样，我们就得到了一个 $O(n)$ 的做法。而且不用考虑值域了。

~~虽然代码短又快，但还是被 AT 上 14ms 的不知道哪个神仙老哥爆杀了。~~

```cpp

int n,a[1000005],cnt=0,ans=0,res[1000005];
st s,t;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>s>>t;
	for(int i=n,j=n,cur=0;j>=1;j--,i=min(i,j)){
		while(i>=1&&s[i-1]!=t[j-1])i--;
		if(!i){
			cout<<-1<<'\n';
			return 0;
		}if(!res[i]){
			cnt++,a[cnt]=i+cnt,res[i]=1;
			while(cur<cnt&&a[cur+1]>=j+cnt)cur++;
			ans=max(ans,cnt-cur);
		}
	}cout<<ans<<'\n';
	return 0;
}
//Crayan_r
```

---

## 作者：SunsetSamsara (赞：1)

## 分析

不难发现，字符串 $S$ 的每一个字符最终都将对应一个区间。设当前区间为 $[l, r]$，则下一次复制后对应的区间 $[x, y]$ 满足条件 $x \le r$。所以，每个区间的开始位置是单调不减的。

于是，就有一个很简单的贪心：把 $T$ 从右向左贪心取，使一个字符对应的区间组成的轨迹尽量靠右（尽量不与其它轨迹相交）。~~不难证明~~这个贪心是正确的。

实现时维护一个队列，记录区间移动的轨迹。如果 $S$ 和 $T$ 在当前位置上字符不变，则不需要考虑。同时，如果 $T$ 的这个位置上的字符与前一个位置上的字符相同，也不需要考虑。注意，第一种情况需要更新队列。

## 代码

最优解榜一。

```cpp
#include <stdio.h> 
#include <string.h> 
const int N = 1000010;
int n;
char s[N];
char t[N];
int q[N];
inline int min(const int &x, const int &y) { return x < y ? x : y; }
inline int max(const int &x, const int &y) { return x > y ? x : y; }
int ans;
int main() {
	scanf("%d%s%s", &n, s + 1, t + 1);
	int head = 1, tail = 0;
	if (!strcmp(s + 1, t + 1)) { // 特判s和t相等 
		puts("0");
		return 0;
	}
	for (int i = n, pos = n; i >= 1; -- i)
		if (t[i] != t[i - 1]) {
			pos = min(pos, i);
			while (pos >= 1 && s[pos] != t[i]) -- pos;
			if (!pos) {
				puts("-1");
				return 0;
			}
			while (head <= tail) {
				if (q[head] - tail + head > i) ++ head;
				else break;
			}
			q[++ tail] = pos;
			if (i != pos) ans = max(ans, tail - head + 1);
		}
	printf("%d", ans + 1);
}
```

---

## 作者：无意识躺枪人 (赞：1)

从T串从右往左贪心取，使得折线尽量靠右。可以证明这样子是最优的

维护一个队列，里面存在T中的位置和S中匹配尽量靠后匹配位置的最大值

且满足这些位置和当前位置的折线会交在一起

数组最好多开几位

![](https://img-blog.csdn.net/20180821204324943?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V6XzIwMTZnZGd6b2k0NzE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


------------

```c
#include<bits/stdc++.h>
#define MAXN 1000005
using namespace std;

int n,pos,ans,head,tail;
int q[MAXN];
char s[MAXN],t[MAXN];

int min(int a,int b) {return a<b?a:b;}
int max(int a,int b) {return a>b?a:b;}

int main()
{
    scanf("%d%s%s",&n,s+1,t+1);
    if(strcmp(s+1,t+1)==0){putchar('0');return 0;}
    pos=n;head=1;tail=0;
    for(int i=n;i>=1;i--)
    {
        if(t[i]==t[i-1]) continue;
        pos=min(pos,i);
        while(pos&&t[i]!=s[pos]) pos--;
        if(pos==0) {putchar('-');putchar('1');return 0;}
        while(head<=tail)
        {
            if(q[head]-(tail-head+1)+1>i) head++;
            else break;
        }
        q[++tail]=pos;
        if(i!=pos) ans=max(ans,tail-head+1);
    }
    printf("%d\n",ans+1);
    return 0;
}
```


------------

AT紫题水得一批

麻烦管理dalao了%%%

---

