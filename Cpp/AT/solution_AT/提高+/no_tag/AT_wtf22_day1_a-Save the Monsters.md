# Save the Monsters

## 题目描述

[problemUrl]: https://atcoder.jp/contests/wtf22-day1-open/tasks/wtf22_day1_a

$ 1 $ から $ N $ までの番号がついた $ N $ 体のモンスターをあなたは飼っています．

あなたのモンスターを討伐するために勇者がやってきました． 勇者はこれから $ M $ ターンかけてモンスターに攻撃を仕掛けます． $ i $ ターン目には，勇者は以下のいずれかの行動を行います．

- MP を $ 1 $ 消費してモンスター $ X_i $ を攻撃する． この行動は，モンスター $ X_i $ がまだ生きており，かつ勇者の MP が $ 1 $ 以上のときにのみ行える．
- 何もしない．

勇者が攻撃を行った場合，あなたはそれに対して以下のいずれかの行動を行います．

- MP を $ 1 $ 消費してモンスター $ X_i $ を守る． この行動はあなたの MP が $ 1 $ 以上のときにのみ行える．
- 何もしない．このとき，モンスター $ X_i $ は死んでしまう．

最初のターンが始まる前の段階で，勇者の MP は $ A $，あなたの MP は $ B $ です． また，勇者もあなたも $ N,M,A,B,X_i $ の値をすべて把握しています． このとき，以下の条件をみたす最大の整数 $ k $ を求めてください．

- あなたが適切な戦略を取ることで，勇者がどのように行動したとしても，$ k $ 体以上のモンスターを最後まで生存させることができる．

## 说明/提示

### 制約

- $ 1\ \leq\ N,M\ \leq\ 250000 $
- $ 1\ \leq\ B\ \leq\ A\ \leq\ M $
- $ 1\ \leq\ X_i\ \leq\ N $
- 入力される値はすべて整数．

### Sample Explanation 1

あなたは $ 1 $ 体以上のモンスターを必ず生存させることができます． 以下にありうる進行の一例を示します． - $ 1 $ ターン目: 勇者がモンスター $ 1 $ を攻撃する． - あなたは何もせず，モンスター $ 1 $ が死ぬ． - $ 2 $ ターン目: 勇者がモンスター $ 2 $ を攻撃する． - あなたはモンスター $ 2 $ を守る． - $ 3 $ ターン目: 勇者はなにもしない．

## 样例 #1

### 输入

```
2 3 2 1
1 2 1```

### 输出

```
1```

## 样例 #2

### 输入

```
2 6 3 2
1 1 1 2 2 2```

### 输出

```
1```

## 样例 #3

### 输入

```
100 1 1 1
100```

### 输出

```
100```

## 样例 #4

### 输入

```
6 20 16 5
5 6 1 3 2 1 4 3 2 4 1 4 4 6 3 3 5 2 2 2```

### 输出

```
2```

# 题解

## 作者：佬头 (赞：2)

## Description
你的对手（初始 MP 为 $A$）将用 $M$ 个回合来攻击你（初始 MP 为 $B$）饲养的 $N$ 只宠物。在第 $i$ 个回合，他**选定**了宠物 $X_i$：
- **选择**消耗 $1$ MP 来攻击宠物 $X_i$（他至少有 $1$ MP 且宠物 $X_i$ 存活）；
  - 此时你可以消耗 $1$ MP 来保护宠物 $X_i$（你至少有 $1$ MP），否则宠物将死亡。
- **选择**什么都不做。

通过适当的策略，保证无论对手如何行动，你都可以让至少 $k$ 个宠物存活。求最大整数 $k$。

## Solution
无论对手如何行动，等价于对手会采取**最优策略**。

显然对手有 $\left(A-B\right)$ MP 的可操作空间（有至少 $\left(A-B\right)$ 次攻击可以保证不被保护掉），但最终结果取决于 $X_i$ 的种类数（毕竟一只宠物仅能被杀死一次），那么策略就是尽量使对手可操作的 $X_i$ 的**种类数最少**。

而我们则有 $B$ MP 的可操作空间，那么策略就是挑出部分**被选定**次数 $C_i$ 较少的 $K$ 只宠物并**一直保护**他们，使得 $K$ 最大的同时他们的总次数 $\sum_{i=1}^{K} C_i'\le A$。

将上述两种情况合并，则在剩余的 $\left(N-K\right)$ 只宠物中，对手有 $\left(A-B\right)$ MP 的可操作空间，答案就是 $N-\min\left\{N-K,A-B\right\}$，即 $\max\left\{K,N-A+B\right\}$。

统计完次数 $C_i$ 后用一个计数排序就可以了，代码时间复杂度 $\mathcal O(N+M)$。

## Code
```cpp
#include <iostream>
using namespace std;
const int N = 250005;
int n, m, a, b, x[N], cnt[N], ans;
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(int x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	n = read(), m = read(), a = read(), b = read();
	if(a == b) return write(n), 0;
	a -= b;
	for(int i = 1; i <= m; ++ i) ++ x[read()];
	for(int i = 1; i <= n; ++ i) ++ cnt[x[i]];
	for(int i = 0; ; ++ i)
		if(b >= cnt[i] * i) ans += cnt[i], b -= cnt[i] * i;
		else{
			ans += b / i;
			break;
		}
	write(n - a > ans? n - a: ans);
	return 0;
}
```

---

## 作者：_AyachiNene (赞：1)

# 思路：
由于每个怪物的价值是一样的，首先有容易想到两个贪心：

1. 防守的优先防守能被砍的次数少的。如果把被砍的次数多的给对面砍，这个怪物死了后就不能再砍了，相当于浪费攻击的人的攻击的机会。
2. 攻击的优先砍能被砍次数少的。和上面相似的，次数少的错过了就砍不到了，次数多了先跳过一次，下次再砍是一样的。

发现两个人贪心策略是相同的，所以可以同时贪心去做。排个序再模拟就做完了。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){x="";char ch=getch();while(!(ch>='a'&&ch<='z')&&!(ch>='A'&&ch<='Z'))ch=getch();while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);putch(' ');write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,m,a,b;
int cnt[250005];
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m,a,b);
	for(int i=1;i<=m;i++)
	{
		int x;read(x);
		++cnt[x];
	}
	sort(cnt+1,cnt+n+1);
	int ans=0;
	for(int i=1;i<=n;i++)
		if(cnt[i])
		{
			if(a<=b) break;
			if(b>=cnt[i]) a-=cnt[i],b-=cnt[i];
			else a-=b+1,++ans,b=0;
		}
	write(n-ans);
	flush();
	return 0;
}
```

---

## 作者：_Cheems (赞：0)

无论如何，英雄都会有 $a-b$ 个操作不被抵消。一个简单的想法是会有 $\min(n,a-b)$ 个怪兽被杀死。但是我们可以保护一些怪兽，使得留给英雄的怪兽数量最小化。

显然，保护一个怪物就必须全程保护它，否则等于没保护。易得贪心：按照怪物被攻击次数（需要保护次数）排序，从小到大保护。

按照上述策略保护怪兽 $p_1\dots p_k$，假如英雄攻击当中的怪兽就防御；否则判断防御后能否保证 $p_1\dots p_k$ 可被保护，再进行防御。这样答案就是 $n-\min(k,a-b)$。

复杂度 $O(n\log n)$，桶排即可线性。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, m, x, buc[N], a, b;

signed main(){
	cin >> n >> m >> a >> b;
	for(int i = 1; i <= m; ++i) scanf("%d", &x), ++buc[x];
	int cnt = 0;
	sort(buc + 1, buc + 1 + n);
	for(int i = 1, s = 0; i <= n; ++i){
		s += buc[i];
		if(s > b) break;
		++cnt;
	}
	cout << n - min(n - cnt, a - b);
	return 0;
}

```

---

## 作者：ljy_luogu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_wtf22_day1_a)

首先思考最简单的策略，即只要英雄攻击就防御（有 $MP$ 的情况下），此时 $\max(N+B-A,0)$ 只怪物就能存活下来。

[此时的代码](https://www.luogu.com.cn/record/141492415)

但这样我们会发现连样例都过不了，所以思考应该防御英雄的哪些攻击。

假设 $cnt_i$ 是怪物 $i$ 被攻击的总次数。把 $cnt$ 从小到大排序，如果前 $\sum_{i = 1}^{ans} cnt_i$ 的总和小于 $B$，则可以使 $ans$ 只怪物存活下来（只在这 $ans$ 只怪物受到攻击时防御）。

此时 $ans$ 就是存活怪物数量的最小值。证明如下：

证：反证法，假设有一种防御方案使得存活下来怪物比 $ans$ 多，易知不可能在使前 $ans$ 个 $cnt_i$ 最小的怪物存活的同时使另外一个怪物存活下来，故至少不防御前 $ans$ 个 $cnt_i$ 最小的怪物中的一个，假设为不防御 $cnt_p$ 而去防御 $cnt_q$（$q \gt p$）则所需的 $MP$ 必然不变或更多，则现在这种方案下存活下来的怪物数量必然小于等于之前那种方案存活下来的怪物数量，与假设矛盾，证毕。

所有计算都可以在 $O(N+M)$ 时间内完成。

[现在 AC 的代码](https://www.luogu.com.cn/record/141492546)

---

