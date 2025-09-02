# X-OR

## 题目描述

This is an interactive problem!

Ehab has a hidden permutation $ p $ of length $ n $ consisting of the elements from $ 0 $ to $ n-1 $ . You, for some reason, want to figure out the permutation. To do that, you can give Ehab $ 2 $ different indices $ i $ and $ j $ , and he'll reply with $ (p_i|p_j) $ where $ | $ is the [bitwise-or](https://en.wikipedia.org/wiki/Bitwise_operation#OR) operation.

Ehab has just enough free time to answer $ 4269 $ questions, and while he's OK with answering that many questions, he's too lazy to play your silly games, so he'll fix the permutation beforehand and will not change it depending on your queries. Can you guess the permutation?

## 说明/提示

In the first sample, the permutation is $ [1,0,2] $ . You start by asking about $ p_1|p_2 $ and Ehab replies with $ 1 $ . You then ask about $ p_1|p_3 $ and Ehab replies with $ 3 $ . Finally, you ask about $ p_2|p_3 $ and Ehab replies with $ 2 $ . You then guess the permutation.

## 样例 #1

### 输入

```
3
1
3
2```

### 输出

```
? 1 2
? 1 3
? 2 3
! 1 0 2```

# 题解

## 作者：1kri (赞：10)

显然，求出 $0$ 的位置后，再用 $n-1$ 次询问就可以求出整个排列。

这样，问题就转换为了极限情况下使用不超过 $n+174$ 次操作，找到 $0$ 的位置。

我们发现可以先记录某个位置的值，再不断用这个位置与序列的其它位置进行询问。

具体地，我们将记录下的位置记为 $pos$ ，值为 $val$ ，将当前询问的位置记为 $pos'$ ，值为 $val'$ 。

若 $val|val'=val$ ，则 $val$ 不为 $0$ ，且 $val'$ 在二进制下是 $val$ 的子集。那么我们将 $pos$ 更新为 $pos'$ ，$val$ 更新为 $val'$ 。容易发现，这样下去最后得到的 $val$ 一定为 $0$ ，那么最后的 $pos$ 就是 $0$ 的位置。

因此我们便可以花费 $n-1$ 次操作扫描，不超过 $175$ 次操作确定某些位置的值，得到 $0$ 的位置。


现在我们考虑如何用若干次操作得到某个位置的值。很简单，我们随机 $20$ 个位置，将这些随机出来的位置与查询的位置进行询问，并将所有结果按位与起来，作为查询位置的值。这样，答案的每一个二进制位算错（将 $0$ 错算为 $1$）的概率为 $2^{-20}$ ，答案算错的概率就约为 $11\cdot2^{-20}$ ，可以忽略不计。

我们来估算下确定某些位置的值共用的询问次数：每次确定值，都会将 $val$ 变为它的一个二进制子集，那么二进制下 $val$ 的 `1` 就会至少减少 $1$ 。那么我们扫描时最多只需确定 $11$ 个位置的值，加上求出初始时的 $val$ ，共需确定 $12$ 个，即需要 $240$ 次询问，略大于 $175$ 。

其实，只要我们将排列随机打乱，初始时 $val$ 的二进制 `1` 个数就不会被卡满，每次变为子集时二进制 `1` 的减少量也不会被次次卡成 `1` ，就完全可以通过了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int n,now,id,q[10005],ans[10005];
int ask(int x,int y){
	cout<<'?'<<' '<<q[x]<<' '<<q[y]<<endl;
	int ans;
	cin>>ans;
	return ans;
}
int val(int id){
	int ans=-1;
	for (int i=1;i<=20;i++){
		int QwQ=rand()%n+1;
		while(QwQ==id)QwQ=rand()%n+1;
		if (ans==-1)ans=ask(id,QwQ);
		else ans&=ask(id,QwQ);
	}
	return ans;
}
int main(){
	srand(time(NULL));
	cin>>n;
	for (int i=1;i<=n;i++)q[i]=i;
	for (int i=1;i<=1000000;i++){
		int x=rand()%n+1,y=rand()%n+1;
		while(x==y)x=rand()%n+1,y=rand()%n+1;
		swap(q[x],q[y]);
	}
	id=1,now=val(1);
	for (int i=2;i<=n;i++)
		if (ask(id,i)==now)id=i,now=val(i);
	for (int i=1;i<=n;i++){
		if (i==id)ans[q[i]]=0;
		else ans[q[i]]=ask(i,id);
	}
	cout<<'!'<<' ';
	for (int i=1;i<=n;i++)cout<<ans[i]<<' ';
	cout<<endl;
	return 0;
}

```


---

## 作者：zhylj (赞：6)


考虑对于一个位置 $i$，如何求得它的值：我们随机若干个位置 $x_i$，询问 $\operatorname{Query}(i, x_i)$，然后把这些询问的回答与起来，令这个与起来的值就是 $p_i$。注意到这样若某一位 $p_i$ 为 $0$，那么这一位在某一轮被设为正确的值的概率为 $\dfrac 12$，所以每一轮期望正确的 $0$ 位数量减少一半，故而期望 $\log\log n$ 次就能跑出正确答案。

我们考虑随机一个位置 $i$，并求出 $p_i$ 的值，那么我们考虑其它所有数，若某个数按位或 $p_i$ 大于 $p_i$，那么这个数必然不可能为 $0$，否则若某个数按位或 $p_i$ 恰等于 $p_i$，那么这个数二进制为 $1$ 的位必然是 $p_i$ 二进制为 $1$ 的位的真子集，此时令 $i'$ 为这个是 $p_i$ 的真子集的数所在的位置，然后再暴力 $\log \log n$ 求出 $p_{i'}$，把 $i'$ 当成新的 $i$ 并重复以上步骤。

由于以上步骤每次会使得当前 $p_i$ 中 $1$ 的数量严格递减，所以我们只需要问 $\log n \log \log n$ 次就可以了。

于是我们就在期望 $2n + \log n\log \log n$ 次询问内求得了答案。

```cpp
const int kN = 3e3 + 5;

int n, p[kN];

int Query(int x, int y) {
	printf("? %d %d\n", x, y);
	fflush(stdout);
	int ret; rd(ret);
	return ret;
}
int RandDiff(int x) {
	int y = rand() % n + 1;
	while(x == y) y = rand() % n + 1;
	return y;
}
int GetVal(int x) {
	int cur = Query(x, RandDiff(x));
	for(int i = 1; i <= 15; ++i) {
		int tmp = RandDiff(x), tmp2 = Query(x, tmp);
		cur &= tmp2;
	}
	return cur;
}

int main() {
	int T = 1; //rd(T);
	while(T--) {
		srand(time(0));
		rd(n);
		int x = rand() % n + 1, cur_x = GetVal(x);
		for(int i = 1; i <= n; ++i) if(x != i) {
			if(Query(x, i) == cur_x) {
				cur_x = GetVal(i);
				x = i;
			}
		}
		p[x] = cur_x;
		for(int i = 1; i <= n; ++i) if(i != x) {
			p[i] = Query(x, i);
		}
		printf("! ");
		for(int i = 1; i <= n; ++i)
			printf("%d ", p[i]);
		printf("\n");
	} return 0;
}
```

---

## 作者：E_huan (赞：5)

### 不用找 $p_{i}=0$ 的位置的做法，而且可以推广到不是排列的情况（数据随机即可）。


------------
#### 做法及思考过程：

若 $x \& y=0$，则 $(a|x) \& (a|y)=a$，$\&$ 后是 $1$ 必定要 $a \& x$ 和 $a \& y$ 的这一位都是 $1$，而 $xy$ 二进制下的 $1$ 是不交的，所以只能都是 $a$ 的贡献。

因此考虑选择找两个 $ \& $ 为 $0$ 的数再花 $2n$ 次确定其它数。

错误的想法是认为必须找到若干个值确定的数，且有至少一对与为 $0$，这样会把询问次数花费在确定一个数上，能求出的数较少，容易出现没办法找出两数二进制下 $1$ 不交（即 $x \& y=0$）的情况，我刚开始就是这样做的，调了一会儿只过了前 $38$ 个点，放弃。

后来 nixnehc 也写了类似方法，并且通过了本题，原因是他将确定一个数的询问次数调到很小，以求出更多数，更大概率找出二进制下 $1$ 不交的两数。询问次数较小，确定的数肯定不准确的，但它一定是真实值的超集，如果两数的超集与是 $0$，那么两数的与一定是 $0$。

这个做法可以推广到不是排列的情况，也不用特定地包含数字 $0$，只需要限制一个不过分的值域，并且数据随机即可。

细节上注意由于找出的 $ \& $ 是 $0$ 的两数的值是不确定的（只是知道它们的超级不交），需要额外耗费一定次数确定这两个数，其它数可以直接由它们确定。具体参数见代码。

------------

#### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937 rd(time(0));
inline int read() {
    int res=0; bool f=0;
    char ch=getchar();
    while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) res=res*10+(ch^'0'),ch=getchar();
    return f?-res:res;
}
const int N=5050;
inline int ask(int i,int j) {
	printf("? %d %d",i,j);
	puts(""); fflush(stdout);
	return read();
}
int n,ans[N];
int q[N],tot;//询问的位置的下标
inline int r() {return ((rand()%n)+1);}
inline int query(int u,int times) {
	int v=-1;
	for(int t=1;t<=times;t++) {
		int x=r();
		while(x==u) x=r();
		if(v==-1) v=ask(x,u);
		else v&=ask(x,u);
	}
	return v;
}
int main() {
	memset(ans,-1,sizeof ans);//不知道值
	n=read(); tot=min(n,31);
	for(int i=1;i<=tot;i++) {
		q[i]=r();
		while(ans[q[i]]!=-1) q[i]=r();
		ans[q[i]]=query(q[i],5);
	}
	int p1=0,p2=0;
	for(int i=1;i<=tot&&(!p1);i++)
		for(int j=i+1;j<=tot&&(!p1);j++)
			if(!(ans[q[i]]&ans[q[j]])) 
				p1=q[i],p2=q[j];
    assert(p1>0);
    ans[p1]&=query(p1,9);
    ans[p2]&=query(p2,9);
	for(int i=1;i<=n;i++) 
		if(i!=p1&&i!=p2) 	
			ans[i]=(ask(i,p1)&ask(i,p2));
	printf("! ");
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	puts(""); fflush(stdout);
	return 0;
}
```

------------
补充：这题做法和 [CF1562F](https://www.luogu.com.cn/problem/CF1562F) 有些相似，CF1526 是找质数确定其它数，本题是找与为 $0$ 的数确定其它数。

------------
鸣谢 nixnehc （我不会 @）。 

------------


---

## 作者：huayucaiji (赞：5)

这个题是一道交互题。（蒟蒻第一次做交互题，所以一直不理解规则，于是。。。。）

![E](https://img-blog.csdnimg.cn/20200626162033210.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2h1YXl1Y2Fpamk=,size_16,color_FFFFFF,t_70#pic_center)

我们来具体讲讲怎么做。

首先我们先了解一下什么叫“按位或”。“按位或”就是对于两个数的每一个二进制位上进行布尔运算。每一位 $1,0$ 的结果如下表。

|或|1|0|
|---|----|----|
|**1**|1|1|
|**0**|1|0|
我们再来了解一些“按位或”的性质。

**性质1**

$$\max(x,y)\leq x|y$$

**证明1**

因为 $x,y$ 每一位上进行了“或”的操作后得到的结果，总归是大于等于这两个数的这一位二进制数。得证。

**性质2**

$$0|x=x$$

**证明2**

$0$ 的每一位二进制上都是 $0$，所以答案就等于 $x$。

知道这些后，我们就可以来做题啦。~~解法有点像模拟退火的思路？~~

我们发现 $4269$ 这个数很有意思，我们又有 $3\leq n\leq 2048$。我们就会发现 $4269=2048\times 2+173$。~~一开始还以为应该是 $4096$，出题人打错了。。。。~~

所以我们可以考虑通过两次 $n$ 次的询问，和一些小问题的处理。所以我们可以非常容易的相处一个方法。我们先用 $n+k(k\leq 173)$ 次找出 $0$ 的位置，在通过 $n-1$ 次询问就可以知道 $P$。问题就转化为如何在限定次数内找出 $0$ 的位置。

首先我们随机找两个位置记为 $x,y$ 作为 $0$ 的可能所在的位置，记 $val=P_x|P_y$。我们随机一个位置 $z(z\neq x,z\neq y)$。

1.如果 $P_x|P_y>P_y|P_z$，那么代表 $P_x\neq 0$。可由性质1得出，我们用 $z$ 代替 $x$。  
2.如果 $P_x|P_y<P_y|P_z$，还则罢了。  
3.如果 $P_x|P_y=P_y|P_z$，$P_y$ 一定不是 $0$，用 $z$ 代替 $y$。

现在我们找到了两个可能为 $0$ 的位 $x,y$。我们在他们之间只需要找出那个为 $0$ 的位置即可。我们只需要用跟上面相同的方法，还是随机出一个 $z$，同样 $z\neq x,z\neq y$：

1.如果 $P_x|P_z>P_y|P_z$，那么 $P_x=0$。  
2.如果 $P_x|P_z<P_y|P_z$，那么 $P_y=0$。

最后只需在询问一遍所有的位置便可得出答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=2100;

int n,tool[maxn],ans[maxn];

int PLA(int i1,int i2) {//Please Let me know the Answer
	cout<<"?"<<" "<<i1<<" "<<i2<<endl;
	cout.flush();//注意基本格式
	return read();
}


signed main() {
	srand(71179);//别乱想，没啥特殊意义（jiade）
	
	n=read();
	
	for(int i=1;i<=n;i++) {
		tool[i]=i;
	}

	random_shuffle(tool+1,tool+n+1);
	random_shuffle(tool+1,tool+n+1);//越随机越好
	random_shuffle(tool+1,tool+n+1);
	
	int x=tool[1],y=tool[2];
	int v=PLA(x,y);
	
	for(int i=3;i<=n;i++) {
		int z=tool[i];
		if(z==y||z==x) {
			continue;
		}
		int tv=PLA(z,y);
		
		if(tv<v) {
			v=tv,x=z;
		}
		else if(tv==v) {
			y=z;
			v=PLA(x,y);
		}
	}
	
	while(1) {
		int z=tool[rand()%n+1];
		if(z==x||z==y) continue;
		
		int v1=PLA(x,z),v2=PLA(y,z);
		
		if(v1==v2){
			continue;
		}
		if(v1>v2) {
			swap(x,y);
		}
		
		for(int i=1;i<=n;i++) {
			if(i!=x) {
				ans[i]=PLA(i,x);
			}
		}
		
		cout<<"!";
		for(int i=1;i<=n;i++) {
			cout<<" "<<ans[i];
		}
		cout.flush();//注意基本格式
		return 0;
	}

	return 0;
}

```

---

## 作者：syksykCCC (赞：4)

下面规范书写使用 $\lor$ 来表示位或，$\operatorname{Query}(x, y)$ 表示题目中的询问 `? x y`。

首先，可以发现 $0 \lor x = x$，这意味着，只要把排列里面的 $0$ 的位置找出来了，就可以把它分别和其他位置询问，来得到这个排列。

几个结论：

> 因为 $y \lor x \ge x$，所以**不存在其它的数 $\lor x$ 比 $0 \lor x$ 小**。换句话说，如果有 $a \lor x < b \lor x$，则 $b$ 必然不是 $0$（下面简称「结论 1」）。
>
> 因为 $0 \lor x = x$，如果 $a \ne b$，则**必然有 $a \lor 0 \ne b \lor 0$**。也就是说，如果存在一个数 $c$，使得 $a \ne b, a \lor c = b \lor c$，则 $c$ 不可能是 $0$。（下面简称「结论 2」）。


问题的关键出在了怎么找到 $0$ 所在的位置。

首先，我们可以把 $1 \sim n$ **打乱顺序**（开始信仰了），记作 $p$；存答案的排列记作 $ans$（也就是题目中的 $p$）。$p$ 的下标是 $0 \sim n - 1$，$ans$ 的下标是 $1 \sim n$。

比方说，我们有两个 $0$ 位置的候选选项 $a$ 和 $b$（$a, b \in [1, n]$），且它们的或和是已知的（即已知 $val = \operatorname{Query}(a, b)$），现在我们枚举到了 $p_i = c$ 这个位置，我们发起询问 $tmp = \operatorname{Query}(a, c)$，尝试用 $c$ 去更新 $a$ 和 $b$：

1. 如果 $tmp < val$，也就是 $p_c \lor p_a < p_b \lor p_a$，根据结论 1，可知 $b$ 所在的位置不可能是 $0$，所以 $b \gets c, val \gets tmp$。
2. 如果 $tmp > val$，也就是 $p_c \lor p_a > p_b \lor p_a$，根据结论 1，可知 $c$ 所在的位置不可能是 $0$，故不用更新。
3. 如果 $tmp = val$，也就是 $p_c \lor p_a = p_b \lor p_a$，因为 $p_c$ 肯定是不等于 $p_b$ 的，根据结论 2，可知 $a$ 所在的位置不可能是 $0$，所以 $a \gets c, val \gets \operatorname{Query(b, c)}$。

全部更新完后，我们就得到了两个 $0$ 的候选项 $a$ 和 $b$，我们开始**随机选择 $c \in [1, n]$**，在保证 $a \ne c, b \ne c$ 的前提下，每次询问 $t_1 = \operatorname{Query}(a, c)$ 和 $t_2 = \operatorname{Query}(b, c)$，如果 $t_1 \ne t_2$，根据结论 1 就可以舍去其中一个（留下结果较小的那个），即确定了 $0$ 的位置。

最后就可以快乐地和每个位置询问得出答案啦！

下面分析询问次数：

最终求答案肯定是 $n$ 级别次询问，第一步也肯定对于每个位置至少做了一次询问，所以总共做了 $2n$ 级别次询问。现在不能确定次数的就是第一步的情况 3 和第二步，~~通过大量尝试可知，询问次数非常少，最坏情况下仅仅十几而已~~，感性上可以理解为恰好选取一个数 $y$ 包含了 $x$ 的所有位的概率显然是十分小的，所以在**随机情况**下不会超过限制次数。有严谨证明可以联系我。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = (1 << 11) + 5;
int n, p[N], ans[N];
inline int query(int x, int y)
{
	cout << "? " << x << ' ' << y << endl;
	cout.flush();
	int res; 
	cin >> res;
	return res;
}
int main()
{
	srand(20050910);
	cin >> n;
	for(int i = 0; i < n; i++) p[i] = i + 1;
	random_shuffle(p, p + n);
	int a = p[0], b = p[1], val = query(p[0], p[1]);
	for(int i = 2; i < n; i++)
	{
		int tmp = query(b, p[i]);
		if(tmp < val)
		{
			a = p[i];
			val = tmp;
		}
		else if(tmp == val)
		{
			b = p[i];
			val = query(a, p[i]);
		}
	}
	int id0;
	while(1)
	{
		int i = rand() % n + 1;
		if(i == a || i == b) continue;
		int t1 = query(i, a), t2 = query(i, b);
		if(t1 == t2) continue;
		id0 = t1 < t2 ? a : b;
		break;
	}
	for(int i = 1; i <= n; i++) 
		if(i != id0) ans[i] = query(i, id0);
	cout << "! ";
	for(int i = 1; i <= n; i++) cout << ans[i] << ' ';
	cout << endl;
	cout.flush();
	return 0;
}
```

---

## 作者：pigstd (赞：3)

一种不太一样的乱搞做法：注意到限制是 $2n+173$，想象一下如果我们确定了两个位置 $i,j$ 满足 $p_i \And p_j=0$，那么我们可以在 $2n$ 的询问次数下确定每个数 $x$：$p_x=(p_x | p_i) \And (p_x | p_j)$。

那么问题是在 $173$ 次询问内找到两个位置 $i,j$ 满足 $p_i \And p_j=0$。如果随机一个数，可以以这样的方式确定这个数的值（但是可能会偏大，得到的结果是它的超集，但是这样是没关系的）：随机 $T$ 个数和他询问，然后把结果 $\And$ 起来，每次期望就能减去一半的位数，所以 $T$ 取比较小的数是没关系的。但是这样子经过程序验证正确率大概在 $99.8\%$ 左右。

然后再来个乱搞，如果直接随的话效果还是不好的话，不妨随两个数然后询问 $|$，如果 $\text{popcount}$ 比较小的话再找它，比较大的话也只会消耗一次代价，看着就比较优秀，通过调参和程序验证，大概可以得到 $99.999\%$ 左右的正确率。

[代码实现](https://codeforces.com/contest/1364/submission/193822569)。

---

## 作者：Zcus (赞：2)

本题解同时发表于 [Blog](https://oi.ender-zzm.pro/index.php/archives/95/)
### 题解

首先我们会发现， 其实如果我们现在求出来了 $0$ 的位置， 我们可以在 $n$ 次操作求出整个序列， 那如果不这么求的话， 由于或的性质并不是很多， 这个题是难以解决的， 这就促使我们沿着这个方向往下想



怎么求出 $0$ 的位置? 首先， 我们有一个想法， 每次在范围内rand出一个位置， 询问这个位置与每一个位置的或， 在最小的那几个中， 一定是有一个 $0$ 的， 那么我们缩小这个范围， 继续做， 看起来是可以的， 但是这样子十分的卡， 不用上一些奇怪的优化是不行的， 我们不需要这样的做法

考虑优化， 我们可以记录两个数$a,\ b$ 表示到此位置的两个指针

然后更新 $Query(a,\ i),\ Query(b,\ i),\ Query(a,\ b)$， 把最小的那一组， 作为新的 $a,\ b$。 显然的， 这样 $0$ 的位置一定存于最后的 $a,\ b$ 之中， 只要随机几个数判断一下就可以确定谁到底是 $0$



### 代码

```cpp
/*
Arthor: Ender_zzm
E-mail: ender-zzm@foxmail.com
Blog: oi.ender-zzm.pro
*/

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

//#define int long long
//#define FILE
#define fi first
#define se second
#define vec vector
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define ri read<int>
#define rl read<long long>
#define debug(x) cout << #x << " = " << x << endl
#define For(i, x, y) for (int i = x; i <= y; i++) 
#define Rep(i, x, y) for (int i = x; i >= y; i--) 
#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
#define filein(FILE_NAME) freopen(FILE_NAME".in", "r", stdin);
#define fileout(FILE_NAME) freopen(FILE_NAME".out", "w", stdout);


const int LEN = 1 << 20 | 1;
static char buf[LEN], *_s, *_t;
static char obuf[LEN], *O = obuf;
struct ios {
	inline bool Isdigit(char c) {
		return (c >= '0' && c <= '9') ? 1 : 0;
	}
    inline char gc(){
#ifdef FILE
        return (_s==_t)&&(_t=(_s=buf)+fread(buf,1,LEN,stdin)),_s==_t?-1:*_s++;
#endif
#ifndef ZZM
        return (_s==_t)&&(_t=(_s=buf)+fread(buf,1,LEN,stdin)),_s==_t?-1:*_s++;
#endif
		return getchar();
    }
    template <class T> 	inline ios & operator >> (T &x) {
        static char ch, sgn; ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc()) {if(ch==-1)return *this; sgn|= ch=='-';}
        for (x = 0; isdigit(ch); ch = gc()) x = x * 10 + (ch ^ '0');
        sgn&&(x=-x); return *this;
    }
	inline void flush() {
		fwrite(obuf,1,O-obuf,stdout);
        O=obuf;
        fflush(stdout);
	}
	~ios() {flush();}
	inline void pr(const char c) {
#ifdef FILE
  		if(O - obuf > LEN-2) flush();
        *O++=c;		
		return;
#endif
#ifndef ZZM
  		if(O - obuf > LEN-2) flush();
        *O++=c;		
		return;
#endif
		return (void)putchar(c);
	}
	template <class T> inline ios & operator << (T x) {
		static char a[25] = {0}, *p = a;
		if (x < 0) pr('-'), x = -x;
		if (x == 0) pr('0');
		while (x) *(++p) = x % 10, x /= 10;
		while (p != a) pr(char(*(p--)) + '0');
		return *this;
	}
	inline ios & operator << (const char c) {pr(c);return *this;}
} io;


template<class T> inline bool Chkmax(T& x, const T& y) { return x < y ? x = y, true : false; }
template<class T> inline bool Chkmin(T& x, const T& y) { return x > y ? x = y, true : false; }


const int maxn = 3010;
int p[maxn][maxn];
vec<int> ans;
int cs(int x, int y) {
	if (p[x][y] != -1) return p[x][y];
	cout << "?" << " " << x << " " << y << endl;	
	cout.flush();
	cin >> p[x][y];
	p[y][x] = p[x][y];
	return p[x][y];
}


int p1, p2, now;
int n;
int main() {
	memset(p, -1, sizeof p);
	srand(time(0));
	cin >> n;
	p1 = 1, p2 = 2; now = cs(p1, p2);
	for (int i = 3; i <= n; i++) {
		int tmp1 = p1, tmp2 = p2;
		int k = cs(i, p1);
		if (k > now) continue;
		int k2 = cs(i, p2);
		if (k < now) {now = k; p1 = i, p2 = tmp1;}
		if (k2 < now) {now = k2, p1 = tmp2, p2 = i;}
	}
	int pos0;
	while (1) {
		int x = rand() % n + 1;
		if (x == p1 || x == p2) continue;
		if (cs(x, p1) < cs(x, p2)) {
			pos0 = p1; break;
		}
		if (cs(x, p1) > cs(x, p2)) {
			pos0 = p2; break;
		}
	}
	For (i, 1, n) {
		if (pos0 == i) {
			ans.pb(0);
		}
		else ans.pb(cs(pos0, i));
	}
	cout << "! " ;
	for (int i = 0; i < n; i++) {
		cout << ans[i] << " ";
	}

	cout.flush();
	return 0;
}

```



---

## 作者：yangrunze (赞：2)

先 $\%\;\large \text{s\color{red}yksykccc}$ 为敬！

与 syk 神的题解一样，这里采用 $a \lor b$ 表示 $a$ 和 $b$ 进行按位或的值，用 $\mathrm{query}(x,y)$ 表示题目中给出的 `? x y` 操作。而且，下面提到的 $a,b,c$ 等数都是自然数。

按位或是啥就不用讲了吧，转成二进制，两位“**有1则1**”，得出结果。

example：$3\lor 5=0011 \lor 0101=0111=7$

------------
首先，这个题有一个非常重要的突破口—— 

> **$0$ 按位或上几就是几**，即 $0 \lor a=a$。

（这也是按位或的重要性质之一，非常好理解，$0$ 的二进制的每一位都是 $0$，然后 $a$ 的那一位是几，异或之后仍然还是几）

那这有什么用呢？我们只要**找到 $0$ 的位置**，就可以“窥一斑而知全豹”，找到所有数的位置啦！（只需要把 $0$ 和其它位置的数不停 $\mathrm{query}$ 即可）

那怎么找 $0$ 的位置呢？我们用**排除法**，把 $0$ 可能的位置锁定在**某两个位置上**。

那问题来了：究竟怎么排除呢？别忘了，按位或还有还有一个性质哦~

> 按位或是“**越或越大**”的，也就是说：$a \lor b\ge a$。

（好理解！按位或之后的每一位，要么和以前一样，要么由 $0$ 变成 $1$,不可能比以前小）


------------

由于还有个 $a \lor 0=a$，我们可以得到这两条性质：

> 1. 如果 $a \ne b$，且 $a \lor c=b \lor c$，那么 $c\ne 0$

（如果 $c=0$ 的话，那 $a \lor c=a , b \lor c=b$，他俩应该不相等啊）

> 2. 如果 $a \lor c<b\lor c$，那么 $b\ne 0$

（从上面按位或的基本性质可以得到：$0 \lor c<b \lor c\;(b\ne 0)$，那要是 $0$ 也只有 $a$ 可能是 $0$ ，$b$ 一定不可能是0了）

通过以上关于按位或的两条性质：我们就可以找到排除的方法啦！

我们先**随机选**两个位置 $a,b$ 当成 $0$ 的可能位置（为啥随机选？因为随机生成的不容易被卡），然后再随便选一个位置 $c$，通过 $\mathrm{query}(a,c)$ 来排除 $a,b$ 的其中一个。

为啥这样就能排除呢？听我慢慢道来：

我们设 $\mathrm{query}(a,b)=v_1,\mathrm{query}(a,c)=v_2$，然后比较 $v_1$ 和 $v_2$ 的大小。

- 如果 $v_2>v_1$，即$c \lor a>b \lor a$，根据上面的性质2， $c$ 不可能是 $0$
- 如果 $v_2<v_1$，即$c \lor a<b \lor a$，根据上面的性质2， $b$ 不可能是 $0$
- 如果 $v_2=v_1$，即$c \lor a=b \lor a$，根据上面的性质1， $a$ 不可能是 $0$

这样的话，每 $\mathrm{query}$ 一次，就可以排除一个不是 $0$ 的位置！



------------
然后，我们只需要把被排除的那个数换成 $c$ 就行了（当然，如果是新选的那个 $c$ 被排除了的话，那就啥也不用干了），别忘了顺便把 $v_1$ 和 $v_2$ 也给换过来。

一直这样下去，当把 $1$ 到 $n$ 的所有数都搞了一波之后，我们就可以把 $0$ 的位置限定到最终的 $a,b$ 两个位置上了，所以，我们要从最终的两个位置中判定出 $0$ 的位置。

有了前面排除的经验，这里就非常简单了，还是**随机选出**不等于 $a,b$ 的一个位置 $c$，算出 $\mathrm{query}(a,c)$ 和 $\mathrm{query}(b,c)$ 的值，根据刚才的性质2，**只要两个值不相等，那么值更小的那一个就是 $0$ 的位置**！

算出 $0$ 的位置之后，那就很简单了，接下来，我们来看看代码实现吧！



------------
如果理解了思路和原理，那这个题的代码就非常简单，但是还有几个小坑坑需要提醒一下：

1. 由于排除过程中的 $a,b,c$ 均为随机选出，那我们可以**随机打乱 $1$ 到 $n$，** 让打乱后的前两个数作为 $a,b$，剩下的每个数都作为 $c$ 试试，**随机打乱可以直接用 `algorithm` 库里的 `random_shuffle`。**

2. 蒟蒻第一次做交互题，虽然这次躲过了这个坑，但是还是要提醒大家：**交互千万条，`flush` 第一条，缓冲不清空，代码两行泪**。

```cpp
#include<iostream>
#include<algorithm>
#define syk using
#define AK namespace
#define IOI std
syk AK IOI;//syk AK IOI
int p[233333],ans[233333];
int query(int x,int y){//query，即题目中的"?"操作
	cout<<"? "<<x<<" "<<y<<endl;
	cout.flush();
	int qwq;
	cin>>qwq;
	return qwq;//交互怎么写？读入之后直接返回即可
}
int main(){
	srand(6600);//stO wyx Orz
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)p[i]=i;
	random_shuffle(p+1,p+1+n);//随机打乱1到n
	//开始逐一排除0的位置
	int a=p[1],b=p[2];
	int val=query(a,b);//val就是前面的v1
	for(int i=3;i<=n;i++){
		int temp=query(a,p[i]);//temp就是前面的v2
		//temp>val:c|a>b|a,c不可能是0,do nothing...... 
		if(temp<val){
			//temp<val:b|a>c|a,b不可能是0,把b换成c
			b=p[i];
			val=temp;	
		}
		else if(temp==val){
			//temp=val:b|a=c|a,a不可能0,把a换成c
			a=p[i];
			val=query(b,p[i]);
		}
	}
	//确定0就在a和b之间,接下来从他俩里面找到0的位置
	int pos;//0的位置
	while(1){
		int c=rand()%n+1;
		//随机选择一个不是a或b的位置去找0
		if(a==c||b==c)continue;
		int t1=query(a,c),t2=query(b,c);
		if(t1!=t2){
			//如果两个结果不相同，那么结果小的一个就是0 
			pos=t1<t2?a:b;
			break;
		}
	}
	for(int i=1;i<=n;i++)
	if(i!=pos)ans[i]=query(i,pos);//0与每一位进行按位或
	cout<<"! ";//输出就好啦
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	cout<<endl;
	cout.flush();
	return 0;
}
```
The end


---

## 作者：yzxoi (赞：1)

[Blog](https://yzxoi.top/archives/2067)

## 吹水

其他题解做法都讲得挺详细的，这里主要讲一下询问次数的分析。

## Tutorial

首先发现如果找到 $0$ 的位置，其他的全部问一遍就都出来了，因此转化为如何找 $0$。

不妨先随机两个位置 $x,y$，再枚举其他所有 $i$：

- $P_x | P_y > P_y | P_i$：$P_x$ 必然非 $0$，因此用 $i$ 代替 $x$ 继续循环。
- $P_x|P_y = P_y|P_i$：$P_y$ 必然非 $0$，因此用 $i$ 代替 $y$ 继续循环。
- $P_x|P_y <P_y|P_i$：$P_i$ 必然非 $0$，因此不换。

那么最后肯定剩下 $x,y$，其中一个必为 $0$。

于是我们可以再随机一个数 $i$：

- $P_x |P_i > P_y|P_i$：$P_x$ 必然非 $0$，因此 $P_y=0$。
- $P_x|P_i < P_y|P_i$：$P_y$ 必然非 $0$，因此 $P_x=0$。
- $P_x|P_i = P_y|P_i$：分辨不出来啥再重新随一个:(

---

简单分析一下询问次数：

首先第一部分找到两个中必有 $0$ 的一对数字，扫了一次所有的点，而其中第二种情况需要多询问一次新的 $P_x|P_i$ 的值（为下次循环做准备），而产生第二种情况的充要条件是 $P_x \& P_y = P_x,P_i\& P_y = P_i$，其概率可以估计为 $\sum_{i=1}^n\frac 1{n^3} 2^{2\operatorname{popcount}(i)}\approx 0.0056843422353267669677734375$，可以看出这是非常小的。

因此这部分的询问次数大约为 $0.0056843422353267669677734375\times 2048+2048\approx 2059$。

其次第二部分随到第三种情况的概率：$\sum_{i=1}^n \frac 1{n^2}2^{\operatorname{popcount}(i)}\approx 0.04223537445068359375$。

不妨设其期望次数为 $f$，则有 $f=0.04223537445068359375\times (f+1) +(1-0.04223537445068359375)\times 1$。

因此 $f=1.0441$。

所以总询问次数期望为：$2059+1+2048=4108$，远远小于 $4269$。

## Solution(C++)

[159907362](https://codeforces.com/contest/1364/submission/159907362)

---

## 作者：Wu_Ren (赞：1)

`CF`上的题解有三种做法，蒟蒻太菜了这里只讲一个。

首先，假设我们已经知道 $P_i=0$，那么我们显然可以用 $n-1$ 次询问把 $P$ 找出来。

现在我们的问题就变成了找到一个 $i$ 使得 $P_i=0$

有一个思路是这样的

假设我们在集合 $S$ 中找 $i$

首先随机一个数 $j$，然后记 $ans_k=query(j,k)$。

因为 $P$ 中有 $0$，所以 $min\{ans_k\}=P_j$

找出所有使得 $ans$ 最小的 $k$，可知 $P_k | P_j=P_j$，使得这些 $k$ 的集合为 $T$

于是发现我们只需要在 $T$ 中找 $i$

发现我们可以保证每次递归下去 $P_j$ 在二进制下 `1` 的个数严格递减，即递归后集合大小减半。

我们就可以在 $n+\frac{n}{2}+\frac{n}{4}+\dots=2n$ 次询问内找到 $i$

~~然后爆掉了~~

考虑优化询问次数。

我们肯定希望每次递归后 $P_j$ 在二进制下 `1` 的个数减半，于是不断随机选取两个数 $v_0,v_1$，直到 $query(v_0,v_1)$ 在二进制下 `1` 的个数至少为 $P_j$ 在二进制下 `1` 的个数的一半。

这样在期望下要一共询问 $\sqrt{n}+\sqrt{\sqrt{n}}+\sqrt{\sqrt{\sqrt{n}}}+\dots$ 次来找 $i$，可以通过本题。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(i,j) uniform_int_distribution<int>(i,j)(rng)
int n,p[2050],cnt[4100];
int query(int i,int j){
	printf("? %d %d\n",i,j);
	fflush(stdout);
	int ans;
	scanf("%d",&ans);
	return ans;
}
int get(vector<int>now){
	if(now.size()==1) return now[0];
	if(now.size()==2){
		while(1){
			int i=rand(1,n);
			if(i==now[0]||i==now[1]) continue;
			int res1=query(i,now[0]),res2=query(i,now[1]);
			if(res1==res2) continue;
			return res1<res2?now[0]:now[1];
		}
	}
	int it;
	while(1){
		int i=rand(0,now.size()-1),j=rand(0,now.size()-1);
		if(i==j) continue;
		int res=query(now[i],now[j]);
		if((1<<(2*cnt[res]-1))<=now.size()){
			it=i;
			break;
		}
	}
	vector<int>f,son;
	f.resize(now.size()),f[it]=1e9;
	for(int i=0;i<now.size();i++){
		if(i!=it){
			f[i]=query(now[i],now[it]);
			f[it]=min(f[it],f[i]);
		}
	}
	for(int i=0;i<now.size();i++){
		if(f[i]==f[it]) son.push_back(now[i]);
	}
	return get(son);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=4096;i++) cnt[i]=cnt[i>>1]+(i&1);
	vector<int>a;
	for(int i=1;i<=n;i++) a.push_back(i);
	int zero=get(a);
	for(int i=1;i<=n;i++){
		if(i!=zero) p[i]=query(i,zero);
		else p[i]=0;
	}
	printf("! ");
	for(int i=1;i<=n;i++) printf("%d ",p[i]);
	printf("\n");
	fflush(stdout);
}
```

---

## 作者：NATO (赞：0)

考虑你如果找到 $0$ 的位置，你就可以扫描一遍序列得到其它位置的值了，所以现在的问题即是在 $n+eps$ 次中找到 $0$ 的位置。

考虑你从 $[0,2^k-1]$ 中随机选一个数，你去看哪些数是它的子集（即或起来为它），选的这个数子集大小期望就是 $2^{\frac{k}{2}}$，然后再对这个部分递归做这个事情，你会发现这个询问次数就是 $n+\sqrt n +\sqrt{\sqrt n}+...$，发现这个是符合我们找 $0$ 的次数的，直到最后就会只剩两个数 $0$ 和某个 $2^x$，扫描序列时考虑对这两个位置都问一下，如果不相同小的那个就是 $0$，这个期望问 $O(\log n)$ 次就行了，然后再扫一边即可。

不过[过不了](https://codeforces.com/contest/1364/submission/318187569)。

细心想想可以发现选子集大小 $\le 2^{\frac{k}{2}}$ 这个每次概率 $\frac{1}{2}$，如果遇到最开始子集大小超了就很可能会爆。

考虑确定性地找这个折半。可以想到一个确定一个数的做法：随机 $x$ 个数，将它们与该数或起来得到的结果与起来就是这个数的值了，错误概率是 $s2^{-x}$，其中 $s$ 是二进制位数，$x$ 取到 $15$ 左右即可稳定正确。

于是我们对找子集大小 $\le 2^{\frac{k}{2}}$ 的数就可以随机后问一下这个数具体是多少判位数，多了就继续随直到找到，这样就能确定性位数减半了，不过这个找的次数略高，有点卡。

[提交记录](https://codeforces.com/contest/1364/submission/318191768)。

---

## 作者：do_while_true (赞：0)

如果问到 0 了那么直接用这个 0 和其它位置都问一遍就能得到所有数的值。现在问题就是怎么把 0 问出来，有 $n+173$ 次操作可以用。思考过程大概就是考虑如果现在这个位置不是 0，那么问一圈结果的 $\&$ 就是这个位置的值 $x$。然后问出值是 $x$ 的一定是 $x$ 的子集，所以可以递归下去继续找。如果现在序列里只剩两个数，就直接用其中一个数和 $n$ 个数随机问个多少遍，如果 $\&$ 为 0 那么一定就是这个位置 0，否则另一个位置 0．

但是这样子实际运行效果比较差，大概 20% 的概率超出询问次数。没想到的事情是：现在已经知道现存的那些数二进制位可能是 1，其它位置一定是 0．可以每次随机现存的两个数 $x,y$，问出来的结果如果 popcount 比现在的这个的一半还要小，那么就用 $x$ 去全询问一遍。

找到这样一个 $x$ 期望次数是 $\mathcal{O}(1)$ 的，所以询问次数毛估估就 $2n+\sqrt n+\sqrt{\sqrt n}+...+\mathcal{O}(\log\log n)$，当然能不能过还得看实际测试结果。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#include<map>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
#define flh fflush(stdout)
const int N=2050;
int n,a[N];
int Query(int x,int y){
	cout << "? " << x+1 << ' ' << y+1 << '\n';flh;
	int o;read(o);
	return o;
}
mt19937 rnd(time(NULL));
inline int rd(int a,int b){
	return a+rnd()%(b-a+1);
}
int solve(vi &vec,int las){
	if(vec.size()==1)return vec[0];
	if(vec.size()==2){
		int all=(1<<11)-1;
		for(int i=1;i<=30;i++){
			int x=rd(0,n-1);
			while(vec[0]==x)x=rd(0,n-1);
			all&=Query(vec[0],x);
		}
		if(all)return vec[1];
		return vec[0];
	}
	int len=vec.size(),p=0;
	do{
		int x=rd(0,len-1),y=rd(0,len-1);
		while(x==y)x=rd(0,len-1),y=rd(0,len-1);
		int o=Query(vec[x],vec[y]);
		if(__builtin_popcount(o)<=__builtin_popcount(las)/2){
			p=x;
			break;
		}
	}while(true);
	vi qwq=vec;
	int all=(1<<11)-1;
	for(int i=0;i<len;i++)if(p!=i){
		qwq[i]=Query(vec[p],vec[i]);
		all&=qwq[i];
	}
	if(!all)return vec[p];
	vi ovo;ovo.pb(vec[p]);
	for(int i=0;i<len;i++)if(i!=p&&qwq[i]==all)ovo.pb(vec[i]);
	return solve(ovo,all);
}
signed main(){
	read(n);
	vi vec;
	for(int i=0;i<n;i++)vec.pb(i);
	int x=solve(vec,(1<<11)-1);
	for(int i=0;i<n;i++){
		if(i!=x)a[i]=Query(x,i);
	}
	cout << "! ";
	for(int i=0;i<n;i++)cout << a[i] << ' ';
	return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

### 题意回顾

长度为 $ n $ 的排列，每次询问两个位置的或值，请在 $ 4269 $ 次内得出这个排列。

$ 3 \le n \le 2048 $。

### 分析

这个询问次数限制看起来很奇怪，大概比 $ 2n $ 多一点，故考虑扫描两次，加一点常数级别个数的询问。

如果我们知道哪个数是 $ 0 $，我们可以直接一次扫描解决问题。

考虑一个性质，对于两个数，如果或为第一个数，那么第二个数的二进制 $ 1 $ 位的集合一定是第一个数的子集。考虑类似于打擂台的方式，那么还有大概一百多次询问机会。

瓶颈在于求出一些数的真实值，考虑二进制位很少，很少次数内就可以把数变成 $ 0 $，因此我们只用求出十几个数的真实值，考虑随机化解决问题：随机 $ 20 $ 个数来或这个数，或出来的值求与即是这个数的值，正确率大概在 $ 1 - \frac{1}{2^{20}} $ 量级。

此时，$ 11 \times 20=220>4269-4096 $，怎么办？考虑随机打乱排列，这样不会被极限数据卡；而子集迭代的打擂台过程是跑不满的，因此可以认为可过。

为了便于实现可以用封装求两个位置的随机映射的或值的过程，这样可以不用每时每刻都带着一个映射数组去写代码。

### 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>
#include <utility>
#include <map>
using namespace std;
const int N = 2055;
int n;
int pi[N];
int ans[N];
map<pair<int, int>, int> mp;
int getor(int x, int y) {
    if(x > y) swap(x, y);
    if(mp.find((pair<int, int>){x, y}) != mp.end()) return mp[(pair<int, int>){x, y}];
    cout << "? " << pi[x] << " " << pi[y] << endl;
    int whr;
    cin >> whr;
    return mp[(pair<int, int>){x, y}] = whr;
}
int getwei(int x) {
    int ans = 2047;
    set<int> se;
    se.clear();
    for(int i = 1; i <= 20; i++) {
        int t = rand() % n + 1;
        if(x != t && se.find(t) == se.end()) ans &= getor(x, t), se.insert(t);
    }
    return ans;
}
int main() {
    srand(time(NULL));
    cin >> n;
    for(int i = 1; i <= n; i++) pi[i] = i;
    for(int i = 1; i <= n; i++) {
        int l = rand() % n + 1;
        int r = rand() % n + 1;
        swap(pi[l], pi[r]);
    }
    int t = getwei(1);
    int p = 1;
    for(int i = 2; i <= n; i++) {
        if(getor(p, i) == t) {
            p = i;
            t = getwei(i);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(i != p) ans[pi[i]] = getor(i, p);
    }
    cout << "! ";
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

```

---

## 作者：pengyule (赞：0)

~~请问随机化的题目应该怎么做呢？感觉正确率还是好玄！~~

发现找到 $0$ 的坐标是突破口，因为这样一来询问 $0|a_i=a_i$。

做一个随机的排列 $z_n$。

初始时 $x=z_1,y=z_2$，相当于随机了两个位置。

接下来枚举 $z_i(i\ge 3)$，想办法依赖之调整 $x,y$，使最终 $x,y$ 中有一个是 $0$。

假如 $a_x|a_y>a_y|a_z$，则 $a_x$ 不可能是 $0$，$x\gets z$；  
假如 $a_x|a_y=a_y|a_z$，则 $a_y$ 不可能是 $0$，$y\gets z$。

最终的 $x,y$ 中有一个满足对应 $0$（预期是这样）。

再遍历一遍 $z$，如果 $a_x|a_z\ne a_y|a_z$，则可以排除掉 $x,y$ 中的一个，并 `break`。预期这一部分询问数不会超过 $173$。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	register char ch=getchar();register int x=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
inline int q(int i,int j){
	cout<<"? "<<i<<' '<<j<<endl;
	return read();
}
int n,a[2500],z[2500];
int main(){
	srand(time(0)); 
	cin>>n;
	for(int i=1;i<=n;i++)z[i]=i;
	random_shuffle(z+1,z+n+1);
	int x=z[1],y=z[2],val=q(x,y);
	for(int i=3;i<=n;i++){
		if(x==z[i]||y==z[i])continue;
		int tmp=q(y,z[i]);
		if(val>tmp)x=z[i],val=tmp;
		else if(val==tmp)y=z[i],val=q(x,y);
	}
	for(int i=1;i<=n;i++){
		if(x==z[i]||y==z[i])continue;
		int t1=q(x,z[i]),t2=q(y,z[i]);
		if(t1>t2){swap(x,y);break;}
		if(t1<t2)break;
	}
	for(int i=1;i<=n;i++)if(x!=i)a[i]=q(x,i);//beware x!=i
	cout<<"! ";
	for(int i=1;i<=n;i++)cout<<a[i]<<' ';cout<<endl;
}
```

---

## 作者：ZillionX (赞：0)

# Description

给定一个长为 $n$ 的排列 $p$，值域为 $[0,n-1]$。支持 $4269$ 次询问 $p_i \mid p_j$，试求出 $p$。

$n \le 2048$，时限 1s。

# Solution

一道 educational 的交互。

考虑对每一位分类讨论，分别求出每一个 $p_i$，对每个元素都贡献几次询问，这样显然很不可做，事实上确实也不可做。

注意到排列 $p$ 的值域从 $0$ 开始，不难发现有 $0 \mid p_i=p_i$，也就是说，只要我们找出来 $0$ 的位置，就可以用 $n$ 次询问求出整个 $p$。

容易发现当 $p_i \mid p_j=p_i$ 时，$p_j$ 必然是 $p_i$ 的真子集，那么我们随机从一个数出发，若 $p_i \mid p_j=p_i$ 就将 $p_i$ 赋值为 $p_j$。由于 $p_i$ 中 $1$ 的个数每次至少减去 $1$，最坏 $\log n$ 次就能找到 $0$。

现在我们的问题就变成了怎么快速求出 $p_i$，这个看起来就很随机化，我乱搞过去了，最后发现其实正解也是乱搞。

考虑随机几个互不相同的位置 $f_i$，然后分别询问 $p_i \mid p_{f_i}$，把每个答案 and 起来，可以发现这样得到的数会与 $p_i$ 相差无几。那么现在的问题就是究竟取几个 $f_i$。

注意到对于每一个位置，$[0,n-1]$ 中 $0$ 与 $1$ 的个数比基本都是 $1$，也就是说每一次 and 后，$p_i$ 的每一位 $0$ 正确求出的概率都是 $\dfrac{1}{2}$。不难发现这样 $0$ 的个数每次减半，期望 $\log \log n$ 次就可以求出正确的 $p_i$。

至此我们在 $2n + \log n \log \log n$ 次操作下完成了本题。

# Code

这题代码难度基本没有，还用放？

---

