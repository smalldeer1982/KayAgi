# [ABC333E] Takahashi Quest

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc333/tasks/abc333_e

高橋くんは冒険に出ようとしています。

冒険では、$ N $ 個の出来事が起こります。 $ i $ 番目 $ (1\leq\ i\leq\ N) $ の出来事は整数の組 $ (t\ _\ i,x\ _\ i) $ $ (1\leq\ t\ _\ i\leq\ 2,1\leq\ x\ _\ i\leq\ N) $ で表され、次のような出来事です。

- $ t\ _\ i=1 $ のとき、タイプ $ x\ _\ i $ のポーションを $ 1 $ つ発見する。高橋くんは、発見したポーションを拾うか捨てるかのどちらかを選択する。
- $ t\ _\ i=2 $ のとき、タイプ $ x\ _\ i $ のモンスター $ 1 $ 体と遭遇する。高橋くんがタイプ $ x\ _\ i $ のポーションを持っている場合、それを $ 1 $ つ消費することでモンスターを撃退することができる。モンスターを撃退しなかった場合、高橋くんは敗北する。
 
高橋くんが敗北することなく全てのモンスターを撃退することができるか判定してください。

高橋くんが全てのモンスターを撃退することができない場合、`-1` を出力してください。

高橋くんが全てのモンスターを撃退することができる場合、高橋君が冒険の途中で持っているポーションの個数の最大値を $ K $ とします。 高橋くんが敗北しないような戦略全体にわたる $ K $ の最小値を $ K\ _\ {\min} $ とします。 $ K\ _\ {\min} $ の値と、$ K\ _\ {\min} $ を達成する高橋くんの行動を出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10^5 $
- $ 1\leq\ t\ _\ i\leq2\ (1\leq\ i\leq\ N) $
- $ 1\leq\ x\ _\ i\leq\ N\ (1\leq\ i\leq\ N) $
- 入力はすべて整数
 
### Sample Explanation 1

出力例は、次のような行動に対応しています。 - タイプ $ 2,3,1 $ のポーションをこの順に発見する。これらのポーションをすべて拾う。 - タイプ $ 3,2 $ のポーションをこの順に発見する。これらのポーションをいずれも拾わない。 - タイプ $ 3 $ のモンスターと遭遇する。持っているタイプ $ 3 $ のポーションを $ 1 $ つ消費してモンスターを撃退する。 - タイプ $ 3 $ のポーションを発見する。このポーションを拾う。 - タイプ $ 3 $ のポーションを発見する。このポーションを拾わない。 - タイプ $ 3 $ のモンスターと遭遇する。持っているタイプ $ 3 $ のポーションを $ 1 $ つ消費してモンスターを撃退する。 - タイプ $ 3 $ のポーションを発見する。このポーションを拾う。 - タイプ $ 2 $ のモンスターと遭遇する。持っているタイプ $ 2 $ のポーションを $ 1 $ つ消費してモンスターを撃退する。 - タイプ $ 3 $ のモンスターと遭遇する。持っているタイプ $ 3 $ のポーションを $ 1 $ つ消費してモンスターを撃退する。 - タイプ $ 1 $ のモンスターと遭遇する。持っているタイプ $ 1 $ のポーションを $ 1 $ つ消費してモンスターを撃退する。 この行動では、$ K $ の値は $ 3 $ となります。 $ K\leq\ 2 $ として敗北しない方法はないので、求める $ K\ _\ {\min} $ の値は $ 3 $ です。 $ K=3 $ を満たして高橋くんが敗北しない行動は複数ありますが、どれを出力しても構いません。

### Sample Explanation 2

高橋くんはかならず最初に遭遇するモンスターに敗北してしまいます。

## 样例 #1

### 输入

```
13
1 2
1 3
1 1
1 3
1 2
2 3
1 3
1 3
2 3
1 3
2 2
2 3
2 1```

### 输出

```
3
1 1 1 0 0 1 0 1```

## 样例 #2

### 输入

```
4
2 3
1 4
2 1
1 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
30
1 25
1 2
1 10
1 18
2 18
1 11
2 11
1 21
1 6
2 2
2 10
1 11
1 24
1 11
1 3
1 2
1 18
2 25
1 8
1 10
1 11
2 18
2 10
1 10
2 2
1 24
1 10
2 10
1 25
2 6```

### 输出

```
4
1 1 1 1 1 0 1 0 0 0 0 1 1 0 1 0 1 0 0 0```

# 题解

## 作者：2020luke (赞：10)

# [AT_abc333_e [ABC333E]Takahashi Quest](https://www.luogu.com.cn/problem/AT_abc333_e)  题解

## 思路解析

可以发现一瓶药水无论什么时候拿被使用掉的时间都是不会变的，所以如果我们想让一瓶药水再背包里待得时间尽可能的短就要让它尽可能的被晚拿起来，于是我们就可以想到使用栈存下每一瓶同类的药水分别出现的时间，此时每遇到一只怪物那么它对应的栈顶就是最晚出现的药水，使用该瓶药水并打上标记。如果栈空则说明药水不够，高橋就寄了。最后统计每时每刻背包容量最大值输出即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n;
int t[N], x[N];
stack<int> st[N];	//stack[i] 代表 i 种类的药水分别出现的时间
int flag[N];
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> t[i] >> x[i];
		if(t[i] == 1) {
			st[x[i]].push(i);	//存入每瓶药水出现的时间
		}
		else if(t[i] == 2) {
			if(st[x[i]].size() <= 0) {	//药水不够了
				cout << "-1";
				return 0;
			}
			flag[st[x[i]].top()] = 1;	//打上标记，记为使用该瓶药水
			st[x[i]].pop();	//药水被用掉了
		}
	}
	int cnt = 0, maxn = 0;
	for(int i = 1; i <= n; i++) {
		if(flag[i] > 0) {	//背包里多进一瓶药水
			cnt++;
			maxn = max(maxn, cnt);	//记录最大值
		}
		else if(t[i] == 2) {	//用掉一瓶药水
			cnt--;
		}
	}
	cout << maxn << "\n";
	for(int i = 1; i <= n; i++) {
		if(t[i] == 1) {
			cout << flag[i] << " ";
		}
	}
	return 0;
}
```

---

## 作者：STARSczy (赞：8)

# 题目翻译
(By 翻译网站 Deepl，不简化题意的原因是为了让读者更准确地理解题意，本人对翻译做过调整)

### 题目描述
高桥将开始一次冒险。在探险过程中，会发生 $N$ 个事件。第 $i$ 个事件 $(1\leq i\leq N)$ 由一对整数 $(t_i,x_i)$ 表示。$(1\leq t_i \leq 2,1\leq x_i\leq N)$ 并如下所示：

- 如果 $t_i=1$，他找到了一个 $x_i$ 类型的药水。他可以选择捡起或丢弃。
- 如果是 $t_i=2$，他将遇到一只 $x_i$ 类型的怪物。如果他有 $x_{i}$ 型药水，他可以使用一种药水击败怪物。如果没有打败它，他就会被打败。

判断他是否可以打败所有怪物而不被打败。如果他不能打败所有的怪物，就打印出来。否则，让 $K$ 成为他在冒险过程中拥有的药水的最大数量。让 $K_{\min}$ 成为 $K$ 在所有策略中不会被打败的最小值。打印 $K_{\min}$ 的值以及高桥实现 $K_{\min}$ 的行动。

### 数据范围：
-   $1\leq N\leq2\times10^5$
-   $1\leq t _ i\leq2\ (1\leq i\leq N)$
-   $1\leq x _ i\leq N\ (1\leq i\leq N)$

### 输入格式：
$N$

$t _ 1$ $x _ 1$

$t _ 2$ $x _ 2$

$\vdots$

$t _ N$ $x _ N$

### 输出格式：
如果高桥不能打败所有的怪物，打印 `-1`。如果他能，则在第一行打印 $K_{\min}$ 的值，在第二行，对于 $i$ 中的每一个 $t_i=1$，按升序打印，如果他在i事件中捡到了药水，则打印 `1`，否则打印 `0`，中间用空格隔开。如果多个行动序列都达到了 $K_{\min}$，并且让他在没有被打败的情况下完成了冒险，那么你可以打印其中的任何一个。

# 思路：
我们可以明显的意识到药水肯定是当之后需要药水是才会保留下来。我们可以开 $n$ 个栈来维护。

- 对于 $t_i=1$ 的操作 $i$，其对应的药水的栈 $stack_x$ 插入 $i$，表示药水 $x$ 最后一次出现的位置。
- 对于 $t_i=2$ 的操作 $i$，如果其对应的药水的栈 $stack_x$ 为空，则说明无法打败，输出 `-1`，结束程序；否则，则不为空，也就是下标为 $stack_x$ 的栈顶的药水需要被保留，最后别忘了弹出栈顶药水。

最后 $K_{\min}$ 做一下差分和取最小值即可，输出药水的取舍情况。

# 代码：
https://atcoder.jp/contests/abc333/submissions/48579534
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10,mod=1e9+7;
inline int read(){
	int c,w=0,n=0;
	while((c=getchar())<'0'||'9'<c) w=c=='-';
	do n=n*10+c-'0';while('0'<=(c=getchar())&&c<='9');
	return w?-n:n;
}
int write(int n){
	if(n<0) putchar('-'),n=-n;
	if(n>9) write(n/10);
	putchar(n%10+'0');
	return n;
}
/*
注：在AT、CF等比赛中为了追求写程序的速度，可以使用快读快写；
但是在信奥赛中，不建议使用。
*/

int n=read(),ans,q1[maxn],a[maxn],f[maxn];
stack<int> t[maxn];

signed main(){
	for(int i=1;i<=n;++i){
		int opt=read(),x=read();
		if(opt==1) q1[i]=1,t[x].push(i);//插入
		else if(t[x].empty()) puts("-1"),exit(0);//无法打败
		else a[t[x].top()]++,f[t[x].top()]=1,a[i+1]--,t[x].pop();//判断药水的可行性
	}
	for(int i=1,cnt=0;i<=n;++i) cnt+=a[i],ans=max(ans,cnt);//差分求ans
	write(ans),puts("");
	for(int i=1;i<=n;++i) if(q1[i]) write(f[i]),putchar(' ');
	return 0;
}
```

---

## 作者：Double_Light (赞：2)

## AT_abc333_e Takahashi Quest 题解

### 题目分析

显然对于每瓶药水，尽快的用完是最优的选择。

所以选择靠后出现但比怪物出现早的药水不劣于选择考前出现的药水。

优先选择靠后出现的，可以用后进先出的栈来模拟。

设 $st_i$ 是对于第 $i$ 种类型的药水的栈。假设出现了一瓶类型 $i$ 的药水，就将这瓶药水放到栈中。如果遇到了类型 $i$ 的怪物，就可以将栈顶弹出，用那瓶药水来打败怪物。

如果某次遇到怪物时发现栈为空，那么就没有足够的药水来对付怪物，直接输出 `-1`。

最终如果栈中有剩下的药水，那么这些药水就是多余的。所以就可以选择不捡起它们。

最终捡起的药水数量就是 $N$ 瓶药水减掉所有栈中剩下药水的数量。

同样，构造方案时，只需要看这瓶药水是否在栈中没有用到。

### AC 代码

```cpp
#include<iostream>
#include<stack>
using namespace std;
int n,t[200005],x[200005];
stack<int>st[200005];//因为xi<=N，所以开N个栈
bool f[200005],win=1;
int cnt,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t[i]>>x[i];
		if(t[i]==1)st[x[i]].push(i);
		if(t[i]==2){
			if(st[x[i]].empty()){
				win=0;//栈为空就不能打败怪物
				break;
			}
			else st[x[i]].pop();
		}
	}
	if(!win){
		cout<<-1<<endl;
		return 0;
	}
	for(int i=1;i<=n;i++){
		while(!st[i].empty()){
			f[st[i].top()]=1;//将栈中的药水标记为无用
			st[i].pop();
		}
	}
	for(int i=1;i<=n;i++){
		if(t[i]==1){
			if(!f[i])cnt++;
			ans=max(ans,cnt);//取拥有药水数量的值
		}
		if(t[i]==2)cnt--;
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		if(t[i]==1&&f[i]==0)cout<<1<<' ';
		else if(t[i]==1)cout<<0<<' ';
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：tbdsh (赞：1)

# 题意简述
[洛谷原题面](//www.luogu.com.cn/problem/at_abc333_e)

[AtCoder 原题面](https://atcoder.jp/contests/abc333/tasks/abc333_e)

Takahashi 在旅行时遇到了 $n$ 个事件，每个事件由两个数 $t_i,x_i$ 表示。事件为以下两种：

- 若 $t_i=1$，那么 Takahashi 找到了一瓶类型为 $x_i$ 的药。

- 若 $t_i=2$，那么 Takahashi 遇到了一只类型为 $x_i$ 的怪兽。如果它有类型为 $x_i$ 的药，那么可以打败怪兽，否则旅行就直接结束。

请判断 Takahashi 能否正常结束旅行。

如果能，令 $K$ 是 Takahashi 在旅行途中手上拿的药的最大值。

请输出 $K$ 的最小值和此情况下 Takahashi 每个药的拿取情况 $p_i$。如果 $p_i=1$，那么第 $i$ 瓶药 Takahashi 会拿，否则 $p_i=0$。 


# 分析
由于要让 $K$ 最小，那么我们肯定要在拿完药后尽快使用。

那么我们就可以记录下所有操作，然后倒叙进行。

在碰到 $x_i$ 类型的怪兽时，让 $dis_{x_i}\gets dis_{x_i}+1$。如果碰到了 $x_i$ 类型的药,判断 $dis_{x_i}$ 是否有值。如果有，那么这个药标记为捡起，同时 $dis_{x_i}\gets dis_{x_i}-1$。否则，这个药就不拿。

随后，扫一遍 $dis$ 数组。如果 $\exists\ i\in[1,n],dis_i\ne0$，那么说明 Takahashi 无法正常结束旅行，直接输出 `-1`。

否则，就在扫一遍，确定 $K$ 的值。

然后输出即可。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int n, cnt, ans[MAXN], dis[MAXN];
bool vis[MAXN];
struct Node{
  int x, y;
} a[MAXN];
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> a[i].x >> a[i].y;
  }
  for (int i = n; i >= 1; i--){
    if (a[i].x == 2){
      dis[a[i].y]++;
    }else if (a[i].x == 1){
      if (dis[a[i].y]){
        vis[i] = 1;
        dis[a[i].y]--;
      }
    }
  }
  for (int i = 1; i <= n; i++){
    if (dis[i]){
      cout << -1;
      return 0;
    }
  }
  multiset<int> b;
  for (int i = 1; i <= n; i++){
    if (vis[i]){
      b.insert(a[i].y);
    }else if (a[i].x == 2){
      if (b.find(a[i].y) != b.end()){
        b.erase(b.find(a[i].y));
      }
    }
    cnt = max(cnt, (int)b.size());
  }
  cout << cnt << '\n';
  for (int i = 1; i <= n; i++){
    if (a[i].x == 1){
      cout << vis[i] << ' ';
    }
  }
  return 0;
}
```

---

## 作者：stswkl (赞：1)

## 题意
Takahashi 要进行一次冒险，冒险途中会发生 $N$ 个事件，有两个整数 $t_i$ 和 $x_i(1\le i\le N)$ 表示。事件分两种：

- $t_i=1$，意为捡起属性为 $x_i$ 的药水（可以不捡）。
- $t_i=2$，以为遇到属性为 $x_i$ 的怪物，需要使用属性为 $x_i$ 的药水击败，否则冒险失败。

判断 Takahashi 是否可以完成冒险。若不可以输出 `-1`，否则输出 $K$（$K$ 为他最小的的背包大小），并且对于 $t_i=1(1\le i\le N)$ 的事件，输出是否捡起药水。

## 思路
不难发现，如果想让背包容量最小，需要让每瓶药水都发挥作用。

可以查找每一个 $i(1\le i\le N)$ 使得 $t_i=2$，在它的前面找离它最近的 $j(1\le j\le i)$ 使得 $t_j=1$ 且 $x_i=x_j$，标记上，若找不到，就说明无法打败该怪物，冒险失败。

最后循环 $i=1\sim N$，用变量 $sum_i$ 存储到事件 $i$ 时手中药水数量，最终答案为 $\max{(sum_1,sum_2,sum_3,\dots ,sum_N)}$。若 $t_i=1$ 且被标记过，就说明必须拿药水，$sum$ 加 $1$；若 $t_i=2$，就说明必须使用一瓶药水以击败怪物，$sum$ 减 $1$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
bool flag[N];
int n,op[N],a,sum,maxn;
stack<int>sta[N]; //sta[i] 存属性为 i 的药水在那个事件中出现
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>op[i]>>a;
        if(op[i]==1)sta[a].push(i);
        else
        {
            if(sta[a].empty()) //没有药水可以击败怪物
            {
                cout<<-1;
                return 0;
            }
            flag[sta[a].top()]=true;
            sta[a].pop();
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(op[i]==1&&flag[i])sum++; //拿起药水
        if(op[i]==2)sum--; //使用药水
        maxn=max(maxn,sum);
    }
    cout<<maxn<<'\n';
    for(int i=1;i<=n;i++)
        if(op[i]==1)cout<<flag[i]<<' ';
    return 0;
}
```

---

## 作者：OAer (赞：1)

### 问题简述

高桥出去冒险，冒险过程中一共有 $n$ 个事件，第 $i$ 个事件可以用一个数对 $(t_i,x_i)$ 来表示。事件有两种：

- 当 $t_i=1$ 时，表示高桥在此时发现了一个品种为 $x_i$ 的药水，它可以将这个药水装入背包，也可以不管它。

- 当 $t_i=2$ 时，表示高桥在此时遇到了一个品种为 $x_i$ 的怪物。若他的背包里有一瓶品种为 $x_i$ 的药水，他就可以用这瓶药水将这个怪物击败，否则他就会被怪物杀死。

求出一种方案，使得在整个冒险过程的所有时刻中，背包中药水的数量的最大值最小。（答案不唯一）若高桥无论怎么捡药都会被怪物杀死，输出 `-1`。

### 思路讲解

这道题可以使用贪心。这里就不得不提到一种反悔类的贪心策略，本人俗称“时光倒带”。这种方法在 [SP348 EXPEDI - Expedition](https://www.luogu.com.cn/problem/SP348) 中也用到过。



首先我们让高桥一直往前走，不管药水，直到遇到一只怪物（设他的品种为 $x_i$)。此时，时光倒带，高桥在之前经过的并且没捡的品种为 $x_i$ 的药水中选取一瓶，用它来击杀这只怪物，然后继续前进。若找不到符合条件的药水，就可以输出 `-1` 了。



不过，为了使在整个冒险过程的所有时刻中，背包中药水的数量的最大值最小，选取药水也是有讲究的。本人第一个想到的就是选取最后一个已经出现的（即 $i$ 最大的）符合条件的药水，现在我们来证明它的正确性。



提供一组样例：

```
5
1 2  
1 3  
2 3  
1 2  
2 2
```

若我们选择第 $1$ 瓶药水（$i=1$）和第 $2$ 瓶药水（$i=2$），在打第 $1$ 只怪物（$i=3$）前，背包里已经积了 $2$ 瓶药水，不是最优解。而最优的办法是不捡第 $1$ 瓶药水，先把品种为 $3$ 的药水用掉（此时没有药水了），然后再捡第 $3$ 瓶药水（$i=4$）打最后一只怪物，故答案为 $1$。



所以，我们要在捡药水之前，尽可能多通过打怪消耗药水，而最后一个已经出现的药水既满足已经消耗的药水最多，又方便计算，所以，这个贪心策略是正确的。



创建 $n$ 个栈，对于第 $j$ 个栈，里面的元素表示品种为 $j$ 的药水出现的位置（也就是发现品种为 $j$ 的事件编号 $i$）。当遇到药水时，就将它出现的位置（当前的 $i$）放入对应品种（$x_i$）的栈里，此时栈顶元素永远为整个栈中最大的元素。而遇到怪物时，就让对应品种的栈顶元素出栈（反正是最大值），出栈的元素表示击杀这只怪物的药水的位置（发现这瓶药水的事件编号 $i$）。当然，若这个栈为空，高桥就没有办法击杀这只怪物了，可以直接输出 `-1`。

### 范例代码

```cpp
#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
stack <int> S[200005];	//栈 
int ans[200005];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int t1,t2;	//t1为t[i]，t2为x[i] 
		scanf("%d %d",&t1,&t2);
		if(t1==1) S[t2].push(i);	//见到药水就将它入栈 
		else{
			ans[i]=-1;	//用答案数组标记怪物 
			if(S[t2].empty()){	//没有药水 
				printf("-1");
				return 0;
			}
			else{
				ans[S[t2].top()]=1;	//标记使用的药水 
				S[t2].pop();
			}
		}
	}
	int ansss=0,tmp=0;	//分别为那个最小值、当前的药水数量 
	for(int i=1;i<=n;i++){
		if(ans[i]==1) tmp++;	//捡药水 
		else if(ans[i]==-1) tmp--;	//使用药水 
		ansss=max(ansss,tmp);
	}
	printf("%d\n",ansss);
	for(int i=1;i<=n;i++){
		if(ans[i]!=-1) printf("%d ",ans[i]);	//对所有不是怪物的（就是药水的）输出 
	}
	return 0;
}
```

[ATCODER 中的提交记录](https://atcoder.jp/contests/abc333/submissions/48586490)

### 最后的忠告
建议使用 STL 的栈，如果自己手写栈的话就会 MLE。


---

## 作者：yshpdyt (赞：1)

## 题意
$n$ 起事件，事件分为两种。
1. 遇到一瓶 $x$ 类型的药水，可以选择拾取或者丢弃。
2. 遇到一只 $x$ 类型的怪物，可以消耗一瓶药水 $x$ 类型的药水将其打败。

求**旅途中**最小的持有药水数量，以及相应拾取方式，或报告无解。

## Sol
考虑建立一个药水储藏库，遇到药水丢进去，遇到妖怪时取出一瓶**最近遇到的**相应类型的药水进行攻击，如果没有相应类型就无法通关，报告无解。

考虑为什么这样是正确的（~~其实挺显然的~~。放入药水库不代表就要拾取，到最后库里还剩下的药水是没必要拾取的，可以认为我们遇到相应的怪物时，取出药水的行为是回到过去拾取这瓶药水，这样保证有解情况一定是最小的答案。接着考虑为什么是消耗最近遇到的，拾取最近的一定比拾取之前遇到的药水优，为了让**旅途中**最小的持有药水数量最小，要尽可能减少一瓶药水持有时间。

![](https://cdn.luogu.com.cn/upload/image_hosting/jiwoqgel.png)

显然拾取靠后的药水答案更优秀。建造药水库可以给每个药水类型开个栈，遇到药水时放进去，使用时弹出栈顶即可。

接着想一想如何维护答案，我们要实现以下操作：
1. 将拾取药水的时间到使用的时间 实现区间 $+1$ 表示这段区间内持有了一瓶药水。
2. 查询所有时刻持有药水数量的最大值，
3. 查询某一时刻的药水是否被捡取使用。

简单线段树操作维护即可。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
stack<ll>q[N];
ll n;
ll f[N],fl[N];
namespace tr{
    #define mid ((l+r)>>1)
    #define ls (p<<1)
    #define rs (p<<1|1)
    ll mx[N*4],lzy[N*4];
    void lt(ll p,ll x){
        mx[p]+=x;
        lzy[p]+=x;
    }
    void build(ll p,ll l,ll r){
        mx[p]=lzy[p]=0;
        if(l==r){
            mx[p]=0;
            return ;
        }
        build(ls,l,mid);
        build(rs,mid+1,r);
        mx[p]=max(mx[ls],mx[rs]);
    }
    void pushdown(ll p){
        lt(ls,lzy[p]);
        lt(rs,lzy[p]);
        lzy[p]=0;
    }
    void upd(ll p,ll l,ll r,ll le,ll ri,ll t){
        if(le<=l&&ri>=r){
            lt(p,t);
            return ;
        }
        pushdown(p);
        if(le<=mid)upd(ls,l,mid,le,ri,t);
        if(ri>mid)upd(rs,mid+1,r,le,ri,t);
        mx[p]=max(mx[ls],mx[rs]);
    }
    ll qr(ll p,ll l,ll r,ll le,ll ri){
        if(le<=l&&ri>=r)return mx[p];
        pushdown(p);
        ll ans=-inf;
        if(le<=mid)ans=max(ans,qr(ls,l,mid,le,ri));
        if(ri>mid)ans=max(ans,qr(rs,mid+1,r,le,ri));
        return ans;
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        ll op,t;
        cin>>op>>t;
        f[i]=2;
        if(op==2){
            if(q[t].empty()){
                cout<<"-1\n";
                return 0;
            }
            else {
                auto x=q[t].top();
                q[t].pop();
                f[x]=1;//标记使用
                tr::upd(1,1,n,x,i,1);
            }
        }else{
            f[i]=0;//默认不使用
            q[t].push(i);
        }
    }
    cout<<tr::qr(1,1,n,1,n)<<endl;
    for(int i=1;i<=n;i++){
        if(f[i]<2){
            cout<<f[i]<<" ";
        }
    }
    return 0;
}
```


---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc333_e)

## 思路

这题乍一看求最小值，很像 dp，但是却不是 dp，用优先队列模拟就可以解决。

读入数据后先用一个桶模拟，看看在捡起每个药水的情况下能否打败所有怪物，如果不能直接输出 `-1`，结束程序。

之后再次从 $1$ 到 $N$ 循环，用 $N$ 个优先队列存储每种药水出现的位置。如果碰到了对应的怪物，那么优先用**最后捡起**的药水来打这个怪物（这也是为什么**不用小根堆**的原因，如果拿很多药水之后存起来用**并不能**保证每个时间持有的药水量最少），并记录当前所用药水的位置。拿完药水后别忘把这个药水的位置从队列中弹出，因为一个药水只能用一次。

随后第三次从 $1$ 到 $N$ 循环。如果当前位置的药水必捡（**存在标记**）那么当前持有的药水数量 $+1$；如果当前位置是怪物，那么当前持有的药水数量 $-1$。每次循环都要记录当前持有药水数量的最大值。循环完成后输出这个最大值。

最后进行一次从 $1$ 到 $N$ 循环。如果当前是药水：

- 是必捡的（**存在标记**），那么输出 `1`。

- 如果不是必捡的就输出 `0`。

**提醒**

- 本题为 Special Judge，输出任意一种可行方案即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
const int N=2e5+10;
int n,tom[N],op[N],x[N],cnt,ans=-1e9;
priority_queue<int>q[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){//第一次循环读入数据模拟并判断是否能通关。
		op[i]=read(),x[i]=read();
		if(op[i]==1)++tom[x[i]];
		else{
			if(!tom[x[i]]){//没有对应药水说明不能通关。
				cout<<"-1";
				return 0;
			}
			--tom[x[i]];
		}
	}
	memset(tom,0,sizeof tom);//记得再次赋 0 为初始值。
	for(int i=1;i<=n;++i){//第二次循环记录必捡药水的位置。
		if(op[i]==1)q[x[i]].push(i);
		else{
			tom[q[x[i]].top()]=1;
			q[x[i]].pop();
		}
	}
	for(int i=1;i<=n;++i){//第三次循环记录持有药水数量的最大值。
		if(tom[i])++cnt;
		else if(op[i]==2) --cnt;//注意不要写成 else。
		ans=max(ans,cnt);
	}
	cout<<ans<<"\n";
	for(int i=1;i<=n;++i){//第四次循环输出必捡药水的位置。
		if(op[i]==1){//只有当前位置是药水的时候需要输出。
			if(tom[i])putchar('1');
			else putchar('0');
			putchar(' ');//别忘输出空格。
		}
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/139960332)

---

## 作者：_Weslie_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc333_e)。

## 思路

从后往前扫一遍，如果遇到怪兽就使该种类怪兽的 $cnt$ 加 $1$，反之如果遇到药水且后方有该种类的怪兽等待消灭就捡起该药水并将 $ans_i$（答案的第二行）设为 $1$。

如果最后还有某种怪兽等待消灭，输出 $-1$。

否则，再次模拟，输出 $p$ 及 $ans$。

## 证明答案最小

因为每一瓶药水在该策略下都不会被浪费，所以是最小的。
```
#include<iostream>
using namespace std;
int n,a[200005],b[200005],cnt[200005],ans[200005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
	for(int i=n;i>=1;i--){
		if(a[i]==2){
			cnt[b[i]]++;
		}
		else{
			if(cnt[b[i]]){
				cnt[b[i]]--;
				ans[i]=1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(cnt[i]){
			cout<<-1<<endl;
			return 0;
		}
	}
	int p=0,anss=0;
	for(int i=1;i<=n;i++){
		if(a[i]==1&&ans[i]==1)p++;
		else if(a[i]==2)p--;
		anss=max(anss,p);
	}
	cout<<anss<<endl;
	for(int i=1;i<=n;i++)if(a[i]==1)cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：fcy20180201 (赞：0)

## 题意
Takahashi 正在进行一次冒险。冒险中发生了 $N$ 个事件，第 $i(1 \le i \le N)$ 个事件是以下两种之一：

- Takahashi 找到了一瓶能克制 $x_i$ 类怪兽的魔药。Takahashi 需要选择拿不拿它。

- Takahashi 遇到了一头 $x_i$ 类怪兽。如果 Takahashi 手中有能克制 $x_i$ 类怪兽的魔药，就用掉一瓶打败怪兽。否则 Takahashi 的冒险就失败了。

如果 Takahashi 必须失败，输出 `-1`。否则，输出在 Takahashi 所有选魔药的方案中，在同一时间内拥有的魔药的瓶数的**最大值最小**是多少，再输出一种选魔药的方案。

## 思路
这题是真
![](https://cdn.luogu.com.cn/upload/image_hosting/fj92kmfb.png)。

要想让同一时间内拥有的魔药尽可能少，那用来打败任意一头怪兽的魔药一定是**在这头怪兽出现前最后发现**的。然后这题基本上就没了（？）。

等等，如果有多头同类怪兽，但能打败它们的药水都在第一头怪兽的前面，那用哪瓶药水打败哪头怪兽呢？其实这根本不需要考虑，因为同类药水**使用**的前后无关紧要。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,op[200005],ev[200005];//ev 数组记录魔药瓶数的变化（顺便记录了每一瓶魔药是否拿）。
vector<int>po[200005];//po 记录每种药水在哪里出现过。
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d%d",&op[i],&x);
		if(op[i]==1)po[x].push_back(i);
		if(op[i]==2){
			if(po[x].empty()){//如果之前没有出现过能打败这头怪兽的药水，Takahashi 一定失败。
				puts("-1");
				return 0;
			}
			ev[po[x].back()]=1;//拿最后发现的可用魔药，那时拥有魔药数加一。
			ev[i]=-1;//打败怪兽，拥有魔药数减一。
			po[x].pop_back();//用掉的魔药不能再用
		}
	}
	int ans=0,cnt=0;
	for(int i=1;i<=n;i++)cnt+=ev[i],ans=max(ans,cnt);
	//对每个时刻的拥有魔药数取最大值。
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)if(op[i]==1)printf("%d ",ev[i]);//输出每瓶魔药是否取。
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[[ABC333E] Takahashi Quest](https://www.luogu.com.cn/problem/AT_abc333_e)

# 题意简述

高桥将踏上冒险之旅。在探险过程中，会发生 $n$ 个事件。每个事件会由 $opt_i$ 和 $a_i$ 呈现并如下所示：

- 如果 $opt_i=1$，说明他找到了一个 $a_i$ 类型的药水。他可以选择捡起或丢弃。
- 如果 $opt_i=2$，说明他将遇到一只 $a_i$ 类型的怪物。如果他有 $a_i$ 型药水，他可以使用一种药水击败怪物。如果他没有打败怪物，他就会被打败。

判断他是否可以打败所有怪物而不被打败。

如果他无法打败所有怪物，则输出 `-1`，否则输出他探险过程中携带的药水数量的最小最大值和对于每个 $opt_i=1$ 的情况携带药水的方案。

# 解题思路

容易看出，最优情况在过程中携带的药水一定是到最后刚好用完的。然后我们可以在输入过程中记录一下某个药水最迟可以得到的时候，等到怪物来了时，如果之前的过程中没有给这瓶药水，则直接输出 `-1`，否则就取我们最迟可以得到的药水，为什么呢？因为越迟得到药水，我们花费的药水数量一定是最多的，此时的药水数量是一定不比拿这瓶药水之前的药水数量多的，因此这样贪心是最优的。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//#define endl printf("\n")
#define QwQ return 0;
long long n,kkk,ss,a[200010],b[200010],ans[200010],minn[200010],an,kk;
struct node{
	map<int,int>mp;
	long long size,si;
}sum[200010];
int main()
{
	IOS;
	cin>>n;
	forl(i,1,n)
	{
		cin>>a[i]>>b[i];
		if(a[i]==1)
			kk++,sum[b[i]].mp[++sum[b[i]].size]=kk;
		else
		{
			if(sum[b[i]].size==0)
			{
				cout<<-1;
				QwQ;
			}		
			minn[sum[b[i]].mp[sum[b[i]].size]]++;
			ans[sum[b[i]].mp[sum[b[i]].size]]=1;
			sum[b[i]].size--;
			minn[i]--;
		}
	}
/*	forl(i,1,n)
	{
	//	minn[i]=minn[i-1];
		if(minn[i]==0)
			minn[i]=minn[i-1];
		else if(minn[i]==1)
			minn[i]=minn[i-1]+1;
		else
			minn[i]=minn[i-1]-1;
		an=max(an,minn[i]);
	}*/
	forl(i,1,n)
	{
		if(a[i]==1)
		{
			kkk++;
			if(ans[kkk]==1)
				ss++;
		}
		else 
			ss--;
		an=max(an,ss);
	}
	cout<<an<<endl;
	forl(i,1,kk)
		cout<<ans[i]<<" ";
	QwQ;
}

```

---

## 作者：_smart_stupid_ (赞：0)

# [题目](https://www.luogu.com.cn/problem/AT_abc333_e)

## 思路：

我们用 vector 记录每一种药在哪里出现，如果这里有药，就在 vector 的相应位置标记，然后依次判断每一处怪有没有药。

## 具体细节：

首先，vector 开二维，第 $i$ 个数组记录第 $i$ 种药的出现位置。

再用一个答案数组，对于每一个时间，初始化为 $-1$，如果为 $1$，说明这里有药，要捡。为 $0$，说明这里有药，但不捡，为 $-1$，说明这里有怪。

然后处理事件，碰到一个药就向 vector 数组里加一个这个时间的下标。

处理捡药事件时，要倒着处理，对于每一个怪，尽量找最靠近它的在他前面的药。这意味着捡了这个药就会很快使用它，策略是对的。

我们发现 vector 数组里的元素是升序排序的，所以我们倒着找，找到第一个满足的地方，标记答案数组中药物出现地方为 $1$，然后移除后面的元素。

**为什么是倒着找？为什么找完后要移除后面的元素？**

因为事件是倒着处理的，对于这个事件，药物已经不适用了，而后面的怪物更不可能用这个药，移除是优化时间复杂度。倒着找意味着每个药物最多找一次，而正着找每个药物要找多次，倒着找为 $O(n)$ 时间复杂度，而正着找可能为 $O(n^ 2)$ 时间复杂度，容易 TLE。

继续说明做法，如果我们找不到合适的药物，说明无解，输出 ```-1```，结束程序，否则有解。

最后，如果有事件是捡药事件，但是答案数组对应地方为 $-1$，就把答案数组对应地方标记为 $0$。

然后根据答案数组里的元素，统计药物数量，输出答案，完结撒花。

时间复杂度：$O(n)$。

## AC Code：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<list>
#include<set>
#include<map>
using namespace std;
int n;
struct node{
	int t, x;
};
node a[200100];
int ans[200100];
int cntt[200100];
int maxx;
vector<int> v[200100];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	memset(ans, -1, sizeof(ans));
	for (int i = 1; i <= n; i ++) {
		cin >> a[i].t >> a[i].x;
	}
	for (int i = 1; i <= n; i ++) {
		if (a[i].t == 1) {
			v[a[i].x].push_back(i);
		}
	}
	int cnt = 0;
	for (int i = n; i >= 1; i --) {
		if (a[i].t == 2) {
			if (v[a[i].x].size() > 0) {
				int tmp = 0;
				bool flag = 0;
				for (int ii = v[a[i].x].size() - 1; ii >= 0; ii --) {
					if (v[a[i].x][ii] != -1) {
						if (v[a[i].x][ii] < i) {
							tmp = ii;
							flag = 1;
							break;
						}
					} else break;
				}
				if (flag == 0) {
					cout << -1;
					return 0;
				}
				ans[v[a[i].x][tmp]] = 1;
				v[a[i].x].erase(v[a[i].x].begin() + tmp);
			} else {
				cout << -1;
				return 0;
			}
		}
	}
	for (int i = 1; i <= 200000; i ++) {
		if (a[i].t == 1 && ans[i] != 1) {
			ans[i] = 0;
		}
	}
	for (int i = 1; i <= n; i ++) {
		cnt += ans[i];
		maxx = max(maxx, cnt);
	}
	cout << maxx << '\n';
	for (int i = 1; i <= n; i ++) {
		if (ans[i] != -1) cout << ans[i] << ' ';
	}
	return 0;
}
```

---

## 作者：zhangjiting (赞：0)

## 题意

有 $N$ 个事件：

`1 x` 出现类型为 $x$ 的药水，可以捡起或丢掉。

`2 x` 出现类型为 $x$ 的怪兽，必须用同种类型的药水把它杀死，否则高桥死。

$k$ 是背包容量，既可以同时装下的药水数量。

求最小的 $k$，若没有合法的 $k$，输出 `-1`。

若可以找到，输出方案。

## 思路

已知，只要对于一只怪兽无法打败，高桥就会死，所以，对于每一个事件 $1$，如果在它后面出现了一个类型相同的怪兽，就必须捡起这瓶药水。

当从后到前遍历完之后，如果现在还有怪兽没有药水匹配，就输出 `-1`。

否则，模拟整个过程，算出 $k$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,t[N],x[N],s1[N],s2[N],sum,ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>t[i]>>x[i];
	for(int i=n;i>=1;i--){
		if(t[i]==2)s1[x[i]]++,s2[i]=114514*2;
		if(t[i]==1&&s1[x[i]])s1[x[i]]--,s2[i]=1;
	}	
	for(int i=1;i<=n;i++){
		if(s1[i]>0)return cout<<-1,0;
		if(t[i]==1&&s2[i]==1)sum++,ans=max(sum,ans);
		if(t[i]==2)sum--;
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++)if(s2[i]!=114514*2)cout<<s2[i]<<" ";
	return 0;
 } 
```


---

## 作者：1234567890sjx (赞：0)

**【前言】**

赛时读错题了。

**【正文】**

贪心选取。能不选就不选。

首先需要判掉不合法的情况，其他的就直接弄。

然后对于每一个药品编号开一个链表。每看到一个 $1$ 操作，就把她给插到链表里。$2$ 操作就是去掉这个药品的编号所对应的链表中最后一个元素。

最后遍历所有的链表，仍然存储在链表中的元素全部删除即可。

时间复杂度 $O(n)$。

**【代码】**

实现的并不优美，略。

---

## 作者：Uuuuuur_ (赞：0)

很妙的一道题啊。

题意：会遇到 $N$ 个事件，要么是遇到 $a_i$ 种类的药水（可以选择捡起或扔掉），要么是 $a_i$ 种类的怪物，需要**消耗**一瓶同种类的药水将它击败，若无法击败，则自身失败。问能否胜利，并且保证胜利的情况下，找到一个捡起药水的策略，满足在任何时刻拥有的药水**最大值最小**。


如果我们正着做，即便二分答案，也无法判断当前要捡起哪个，因为无法知道后面能遇到什么。

不过如果**从时间顺序反方向做**，维护一个**多重集合**，遇到一个怪物就加进去，遇到一瓶药水，如果集合内有可以击败的怪物，捡起药水并**删除一个**对应的怪物。对应答案就是**某一时刻集合最大的大小**。

其实我们这里的思想就是贪心，尽可能满足一捡起药水就击败怪兽，更快消耗掉药水，如果在某一时刻集合内需要击败的怪物为 $k$，意味着我现在至少要保存 $k$ 瓶药水，因为再后面（时间顺序）的点是捡不到那些药水的。

当然还有无解，就是最后多重集不空。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
multiset<int> s;

int typ[N], a[N];
int n;
int ans;
stack<bool> r;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> typ[i] >> a[i];
	for (int i = n; i >= 1; i--) {
		if (typ[i] == 2) s.insert(a[i]);
		else {
			auto f = s.find(a[i]);
			if (f != s.end()) r.push(1), s.erase(f);
			else r.push(0);
		}
		ans = max(ans, int(s.size()));
	}
	if (!s.empty()) cout << -1;
	else {
		cout << ans << '\n';
		while (!r.empty()) {cout << r.top() << ' '; r.pop();}
	}
	return 0;
}
```


---

## 作者：ilibilib (赞：0)

### 题目分析：

意义不明的模拟题目。

很容易想到贪心策略，就是要用药水的时候拿时间距离最近的药水就行了。

这样持有每瓶药水的时间就最短了，同时持有药水的数量最多也最少了。

我们可以用栈记录每种药，然后按照时间从头进栈。

因为栈是先进先出，所以我们要用药的时候取栈顶就是时间最近的药水了。

取出的药水标记一下，最后输出。

如果栈为空就说明没有药水，则输出 `-1`。

至于 $k$，模拟一遍就可以求出来了。 

### code：

```Cpp
#include<bits/stdc++.h>
#define sc scanf
#define pt printf
#define gc getchar
#define pc putchar
#define N 300050
using namespace std;
template<typename T>
inline void read(T &x)
{
	x=0;char ch=gc();
	while(ch<'0'||ch>'9') {ch=gc();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+ch-48,ch=gc();}
}
template<typename T>
inline void write(T x)
{
	if(x>9) write(x/10);
	pc(x%10^48);
}
int last[N],n,a;
int op[N];
bool bl[N];
stack<int>s[N];
signed main()
{
	int ans=0,k=0;
	read(n);
	for(int i=1;i<=n;++i)
	{
		read(op[i]);
		read(a);
		if(op[i]==1)
		{
			s[a].push(i);
		}
		else
		{
			if(s[a].empty()) {puts("-1");return 0;};
			bl[s[a].top()]=true;
			s[a].pop();
		}
	}
	for(int i=1;i<=n;++i)
	{
		if(op[i]==1&&bl[i]) ++k;
		else if(op[i]==2) --k;
		ans=max(ans,k);
	}
	write(ans);pc('\n');
	for(int i=1;i<=n;++i)
		if(op[i]==1) {write(bl[i]),pc(' ');}
	return 0;
}
```



---

## 作者：xz001 (赞：0)

- 考虑贪心，我们先判无解，然后我们遍历一遍，一边遍历一边维护每一种药剂的所有位置，如果此时有怪物，就将**最靠近**这个怪物的此类药剂消耗了，标记其为捡起。
- 使用最靠近每个怪物的药剂一定最优，因为这样可以保证手中的药剂尽量处于捡一个用一个的状态。
- 然后我们再扫一遍标记数组，计算一下其过程中手中最多的药剂数量，然后将其和标记数组一起输出即可。
- 代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, mod = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

const int ny = 499122177;

int n, t[N], x[N], cnt[N];

bool is[N];

set <int> s[N];

signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++ i) scanf("%lld%lld", t + i, x + i);
    int sum = 0;
    for (int i = 1; i <= n; ++ i) {
    	if (t[i] == 1) ++ cnt[x[i]];
    	else {
    		-- cnt[x[i]];
    		if (cnt[x[i]] < 0) {
    			puts("-1");
    			return 0;
			}
		}
	}
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; ++ i) {
		if (t[i] == 1) {
			s[x[i]].insert(i);
		} else {
			is[*s[x[i]].rbegin()] = 1;
			s[x[i]].erase(*s[x[i]].rbegin());
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++ i) {
		if (t[i] == 1) {
			sum += is[i];
		} else {
			-- sum;
		}
		ans = max(ans, sum);
	}
	printf("%lld\n", ans);
	for (int i = 1; i <= n; ++ i)
	    if (t[i] == 1)
	        printf("%lld ", (int)is[i]);
    return 0;
}


```

---

