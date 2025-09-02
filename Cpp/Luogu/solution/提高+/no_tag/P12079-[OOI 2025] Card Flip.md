# [OOI 2025] Card Flip

## 题目背景

[试题来源](https://inf-open.ru/2024-25/final-materials/)。

## 题目描述

Petya 和 Vasya 买了一款新卡片游戏，名为“Flip”。游戏中有 $n$ 张双面卡片和 $m$ 张单面卡片：
- **双面卡片**：卡片正面写有数字 $a_i$，背面写有数字 $b_i$。
- **单面卡片**：卡片正面写有数字 $c_i$。

所有卡片上数字均不相同。初始时，所有卡片正面朝上，放置在桌面上。在每轮回合中，玩家可以执行以下两个动作之一：
- 从桌面上移除剩余卡片中数字最小的那一张卡片。
- 如果数字最小的卡片是双面卡片并且正面朝上，可以将其翻转。

谁先移除桌面上的最后一张卡片，谁就获胜。Petya 先行，确定游戏的胜者。

## 说明/提示

**样例解释**

在第一个样例中，初始时桌面上是数字 $3$、$4$ 和 $5$。Petya 先手移除数字 $3$，接着 Vasya 只能移除单面牌 $4$，最后 Petya 再移除 $5$，此时卡牌全部被移除，Petya 获胜。

在第二个样例中，初始桌面为 $1$、$2$、$4$。Petya 必须移除单面牌 $1$，然后 Vasya 可以翻转双面牌 $2$（反面是 $3$），使桌面为 $3$、$4$。Petya 只能移除 $3$，接着 Vasya 移除 $4$，最终 Vasya 获胜。

**评分**

本题包含九个测试点分组。只有在该分组的所有测试点以及其所有依赖分组的测试点全部通过的情况下，才能获得该分组的分数。请注意，通过样例测试点对于部分分组不是必需的。**Offline-evaluation** 表示该分组的评测将在比赛结束后进行。

| 组别 | 分数 | 限制条件：$n$ | 限制条件：$m$ | 依赖组别 | 说明 |
| :--- | :--- | :------------- | :------------- | :------- | :---- |
| 0    | 0    | --             | --             | --       | 样例测试点。 |
| 1    | 12   | $n \le 20$     | $m \le 10$     | 0        |          |
| 2    | 13   | $n \le 20$     | --             | 0, 1     |          |
| 3    | 9    | --             | --             | --       | 满足 $a_i > b_i$。 |
| 4    | 10   | --             | --             | --       | 满足 $\max_{i = 1}^n a_i < \min_{i = 1}^n b_i$。 |
| 5    | 6    | --             | --             | --       | 所有区间 $[\min(a_i, b_i), \max(a_i, b_i)]$ 两两不相交。 |
| 6    | 11   | $n \le 200$    | $m \le 200$    | --       | 所有区间 $[\min(a_i, b_i), \max(a_i, b_i)]$ 要么嵌套，要么不相交。 |
| 7    | 14   | --             | --             | 5, 6     | 所有区间 $[\min(a_i, b_i), \max(a_i, b_i)]$ 要么嵌套，要么不相交。 |
| 8    | 13   | $n \le 5000$   | $m \le 5000$   | 0, 1, 6  |          |
| 9    | 12   | --             | --             | 0 -- 8   | **Offline-evaluation.** |

## 样例 #1

### 输入

```
2 1
5 3
1 2
4```

### 输出

```
First```

## 样例 #2

### 输入

```
1 2
2
3
4 1```

### 输出

```
Second```

# 题解

## 作者：Tairitempest (赞：2)

## [OOI 2025] Card Flip

卡片没有固定的顺序，因此我们可以先把卡片排序。

我们看看只有单面卡片会发生什么。

如果只有单面卡片是很好做的，判断一下奇偶性就可以判断谁会赢了。

现在让我们加入一张双面卡片。

当这个游戏只有一张双面卡片的时候，我们假设某个人最终可以拿到了双面卡片。

当这个双面卡片右侧剩下的单面卡片数量可以使先手胜利时，那么就可以翻转这张卡片；否则就可以直接取走这张卡片，那么拿到这张双面卡的人一定可以取得胜利。

现在让我们加入更多的双面卡片。

显然根据前面的推断，拿到最后一张双面卡的人一定可以取得胜利。

让我们考虑一下拿到最后一张双面卡需要什么条件。如果能够拿到倒数第二张双面卡，考虑这个双面卡能不能改变局势——而这取决于它的反面大小是否大于下一张有效的双面卡正面大小。如果是的，那么它被翻过以后就会被放到下一张有效的双面卡后面，也就是说相当于一张单面卡，可以无视；否则它就是一张有效的双面卡。拿到了一张有效的双面卡意味着必定得到胜利。

这么判断下来，可以从后往前，根据后面的双面卡，推出会先被拿的有效的双面卡。

最后判断一下第一张被拿的有效的双面卡前面有几个卡牌会被取就可以了。第一个拿到有效的双面卡的人一定可以取得胜利。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct db{
	ll a,b;
} d[500010];
ll n,m,c[500010],lst,ans;
bool comp(db a,db b){
	return a.a<b.a;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>d[i].a;
	for(int i=1;i<=n;i++) cin>>d[i].b;
	for(int i=1;i<=m;i++) cin>>c[i];
	sort(d+1,d+n+1,comp);
	lst=n;
	for(int i=n-1;i>=1;i--)
		if(d[i].b<d[lst].a) lst=i;
	for(int i=1;i<=m;i++) if(c[i]<d[lst].a) ans++;
	if((ans+lst)%2) cout<<"First"<<endl;
	else cout<<"Second"<<endl;
	return 0;
}
```

---

## 作者：spacebar (赞：0)

你应该已经搞过好多两个人取石子硬币叶子之类的题目了，这里面总有一个核心——自由选择接下来某个状态的先后手。

何为选择先后手？比如有一个游戏，在黑板上有从一到某个大数的正整数，每次选择一个数把它和它的因数删了，谁先动不了谁就输了。而这一题我们可以考虑不包括一的情况（称为新情况），肯定先手后手会有一个能赢的。如果新情况下后手赢，先手就先选一，他就成了新情况的后手；反之先手就按照在新情况中先手的选法选，一肯定是它的因数会被直接删了，相当于成为新情况的先手。

就像这样，在一些存在先后关系的游戏中（比如这题要求先选前头的在选后头的，刚才的游戏要先选择选不选一）如果你能通过某个选择让自己拥有在接下来某个状态选择先后手的权力你必赢！

考虑怎么在这道题选先后手，假如只有一张双面牌，轮到你走，翻牌可以让这张牌多消耗一个回合被消去，在消去它之后的那个状况下先后手的顺序于不翻直接消是相反的，这就控制了选先后手的权力。

而如果有好多张双面牌怎么办呢？在若干双面变成单面后只剩一张双面时谁拿到谁就赢了，所以其他牌是为拿到最后的双面牌做铺垫。

由于双面牌是决定其背面被消去的时候双方先后手，所以要争取一张牌就要确保其背面的数字小于要争的牌（否则它只影响那张要争的牌后面的单面牌数量），按正面数字排序，从大到小，更新实际争取的牌，就比如说样例一中第一张双面牌（正面五）决定了输赢而第二张决定了第一张的归属，所以双方实际在争取第二张。

最后统计一下谁能拿到实际争取的牌就行了（看这张牌前面的牌数的奇偶性）。

---

## 作者：diqiuyi (赞：0)

注意到谁能抢到最后一个能翻面（即 $a$ 最大的）的卡片，谁就赢了，因为是否翻转这张卡片带来的是相反的结果，必然有一种可能使得当前的决策者获胜。

我们记这张卡片为 $x$。

考虑什么样的卡片能影响 $x$ 的归属，发现是满足 $a_i<a_x\land b_i>a_x$ 且 $a_i$ 最大的 $i$。也就是说谁抢到 $i$ 谁就能获胜。

注意到这个找卡片的过程可以递归，那么只要一直找到新的 $x$，最后判断它将被谁拿到即可（显然这是固定的，不会被决策影响）。

具体实现上可以先按 $a$ 从小到大排序，每次暴力往前找即可，时间复杂度为 $O(n\log n)$，桶排可以做到 $O(n)$。
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define uint unsigned int
#define pii pair<int,int>
#define io ios::sync_with_stdio(0),cin.tie(0),cout.tie(0) 
using namespace std;
inline int read(){
	int x=0;bool f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f?x:-x;
}
int n,m;
pii p[500005];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) p[i].first=read();
	for(int i=1;i<=n;i++) p[i].second=read();
	sort(p+1,p+n+1);
	int now=n;
	while(1){
		int i;
		for(i=now-1;i;i--)
			if(p[i].second<p[now].first)
				break;
		if(!i) break;
		now=i;
	}
	bool flg=1;
	for(int i=1;i<now;i++)
		flg^=(p[i].second>p[now].first);
	for(int c;m--;)
		c=read(),flg^=(c<p[now].first);
	cout<<(flg?"First\n":"Second\n");
    return 0;
}
```

---

## 作者：Acit (赞：0)

**思路**

首先明确一点：抢到最后一张双面牌操作权的人必胜（如果拿走它赢不了，那就翻转它）。

于是我们可以按照 $a_i$ 升序排好所有的双面牌，从后往前考虑：对于牌 $i$ 和必胜牌 $j$，若 $b_i<a_j$，则抢到牌 $i$ 后一定可以抢到牌 $j$（与最后一张双面牌情况类似），那么我们将牌 $i$ 钦定为新的必胜牌。否则牌 $i$ 可以视为单面牌（翻转产生的新牌不会影响牌 $j$ 的争夺）。

找到第一张必胜牌 $d$ 后，所有满足 $c_i<a_d $ 的 $i$ 的个数与 $d-1$ 的和（即牌 $d$ 之前的单面牌和等效单面牌数）若为偶数，则先手必胜，反之则后手必胜。

**Code**


```cpp
#include<bits/stdc++.h>
//#define int long long
#define forr(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int N=5e5+10;
int n,m;
pair<int,int> p1[N];
int c[N],win,cnt;
signed main() {
	ios::sync_with_stdio(0);
//	freopen("read.in","r",stdin);
//	freopen("out.out","w",stdout);
	cin>>n>>m;
	forr(i,1,n)cin>>p1[i].first;
	forr(i,1,n)cin>>p1[i].second;
	forr(i,1,m)cin>>c[i];
	sort(p1+1,p1+1+n);
	sort(c+1,c+1+m);
	win=n;
	roff(i,n-1,1){
		if(p1[i].second<p1[win].first)win=i;//更改新的必胜牌
	}
	forr(i,1,m)cnt+=(c[i]<=p1[win].first);
	cnt+=win-1;
	cout<<(cnt%2==0?"First":"Second");
	return 0;
}

```

---

## 作者：zhuweiqi (赞：0)

输赢取决于剩余牌堆的奇偶性，把取到双面牌看做成**任意调节**剩余牌堆的奇偶性就不难注意到，取到 $a_n$ 者必胜。因为此时牌堆的奇偶性是确定了的，且可任意调节牌堆奇偶性的牌已经被取完了，所以当前玩家根据不同情况进行操作即可必胜。那是否同理可得取到 $a_{n-1}$ 就必定取到 $a_n$ 呢？非也，如果 $b_{n-1}>a_n$ 的话，我们发现就不能调节牌堆的奇偶性了，从而输赢与 $a_{n-1}$ 无关，**等价于其是一张单面牌**，所以我们把 $a_{n-1}$ 放进单面牌堆里，然后继续比较 $b_{n-2}$ 和 $a_n$ 的大小，以此类推；否则 $b_{n-1}<a_n$ 的话就和上面同理，必胜的充要条件转变为取到 $a_{n-1}$。最终只需算出小于具有必胜性的最小的那张双面牌的正面数字的单面牌的奇偶性即可。

Code：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+2;
pair<int,int> a[N];
int c[N<<1];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,m,las;
	cin>>n>>m;las=n;
	for(int i=1;i<=n;i++) cin>>a[i].first;
	for(int i=1;i<=n;i++) cin>>a[i].second;
	for(int i=1;i<=m;i++) cin>>c[i];
	sort(a+1,a+1+n);
	for(int i=n-1;i>=1;i--){
		if(a[i].second>a[las].first) c[++m]=a[i].first;
		else las=i;
	}
	sort(c+1,c+1+m);
	int i=1;
	while(i<=m && c[i]<a[las].first) i++;
	if((i&1)) cout<<"First";
	else cout<<"Second";
	return 0;
}
```

---

