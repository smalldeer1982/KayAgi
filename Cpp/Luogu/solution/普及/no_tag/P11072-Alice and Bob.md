# Alice and Bob

## 题目描述

Alice 和 Bob 在一起玩游戏。

初始时给定一个值域在 $0$ 到 $n$ 之间的整数序列 $a$，然后他（她）们轮流进行如下操作，Alice 先操作。

- 操作：任意重排 $a_{1\sim a_1}$。

如果某一个人操作前 $a_1=0$，则他（她）立刻输，因为他（她）无法进行操作。

如果某次操作结束后某一个人存在两次**他（她）的**操作满足**操作结束后**的 $a_1$ 相同，则他（她）立刻输。

现在给定非负整数序列 $a$，假设两人足够聪明，问谁有必胜策略。

## 说明/提示

| 测试点编号 $id$ | $n=$ | 特殊性质 |
| :----------: | :----------: | :----------: |
| $1\sim 20$ | $id$ | 无 |
| $21$ | $20$ | $a_1=0$ |
| $22$ | $20$ | $a_1=1$ |
| $23$ | $20$ | $a_i$ 全相同 |
| $24\sim 25$ | $20$ | $a_i$ 两两不同 |

对于所有数据，保证 $1\le T,n\le 20$，$0\le a_i\le n$。

## 样例 #1

### 输入

```
4
2
2 1
2
2 0
3
1 2 3
3
0 1 1```

### 输出

```
Bob
Alice
Bob
Bob```

# 题解

## 作者：Vct14 (赞：4)

本场比赛第二难的题目。

考虑到 Bob 可以选择不动，那么他操作后的 $a_1$ 一定与他操作前 Alice 操作后的 $a_1$ 一样。而为了不让自己输，Alice 会一直选择她曾经没有选择过的 $a_1$，直到将所有的 $a_i$ 全都选择过一次。此时 Alice 会落败。

那么 Alice 想要反败为胜，只能寄希望于某一次操作后她可以使 $a_1=0$，也就是操作前存在 $i\in [2,a_1]$，有 $a_i=0$。但是由于 Bob 的策略是不动，因此 Alice 只能在前一步操作时就使得存在 $i\in [2,a_1]$，有 $a_i=0$。事实上，如果 Alice 这样操作的话，Bob 的下一步就可以直接将 $a_1$ 变成 $0$ 从而获胜。因此，当且仅当一开始就存在 $i\in [2,a_1]$，有 $a_i=0$ 时 Alice 可以获胜。否则 Bob 都可以获胜。

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[22];

int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1; i<=n; i++) cin>>a[i];
		bool als=0;
		for(int i=1; i<=a[1]; i++) if(a[i]==0){
			als=true;
			puts("Alice");
			break;
		}
		if(!als) puts("Bob"); 
	}
	return 0;
}
```

---

## 作者：Delete_error (赞：2)

听讨论区是诈骗题。

直接讲思路，可以发现我们每次操作是尽量让 $a_1$ 变小的，这样能让后手重排的范围更小；若 $a_1$ 不是能变的最小值，则后手范围一定更大，能将新区间的最小值换给 $a_1$ 。所以序列前面的数尽量小，每次将 $a_{1∼a_1}$ 按从小到大排一遍就好了，然后按题意判正负。每组数据时间复杂度为 $  O (n \log n)$ 。
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
ll t,n,a[25],vis[25][2];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		ll q=0;
		while(1){
			ll now=a[1];
			if(a[1]==0){
				if(q) cout<<"Alice"<<endl;
				else cout<<"Bob"<<endl;
				break;
			}
			sort(a+1,a+a[1]+1);
			if(a[1]==0){
				if(!q) cout<<"Alice"<<endl;
				else cout<<"Bob"<<endl;
				break;
			}
			if(vis[a[1]][q]){
				if(q) cout<<"Alice"<<endl;
				else cout<<"Bob"<<endl;
				break;
			}
			vis[a[1]][q]=1;
			q^=1;
		}
	}
	return 0;
}
```
有问题私信沟通我。

---

## 作者：luanyanjia (赞：2)

简单博弈题。

先说结论，如果存在 $a_i = 0$ 使得 $1 \le i \le a_1$ 的话，那么先手必胜，否则后手必胜。

若满足上述条件显然先手必胜，将 $0$ 搞到第一个就行。否则 Alice 每操作一次，如果操作后满足了上述条件，那么 Bob 赢，否则 Bob 只要不动就行。但是下一轮 Alice 必须动，要不然两次操作的 $a_1$ 就相同了。这样一直进行下去，Alice 是必败的。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	char ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
int T,n,a[25];
inline void Solve(){
	rd(n);
	int mn=n+1;
	for(int i=1;i<=n;i++){
		rd(a[i]);
		if(a[i]==0)mn=min(mn,i);
	}
	if(mn<=a[1])printf("Alice\n");
	else printf("Bob\n");
}
signed main(){
	rd(T);
	while(T--)Solve();
	return 0;
}

```

---

## 作者：jdfz2251533 (赞：2)

# 题解：P11072 Alice and Bob
## 题意
原题的描述已经很清晰了。

## 分析与解
如果第一次的可操作范围内已经有 $0$，Alice 一定把它放到第一个，于是 Bob 输，答案为 Alice；如果没有，Bob 就先不管 Alice 怎么动，只要 Alice 把 $0$ 换到了可操作范围内（也有可能是范围变大了），Bob 就把 $0$ 换到第一个，于是 Alice 输，答案为 Bob。

如果问要是 $a_1 = 0$ 或者 $a_1 = 1$ 咋判的，其实不判也行，只需要循环从 $2$ 开始，这情况就进不去，直接输出 Bob 了（显然看出答案就是 Bob）。

于是我们解决了这道题的所有情况。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, a[25];

int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		int f = 0;
		for (int i = 2; i <= a[1]; i++) {
			if (a[i] == 0) {
				f = 1;
				break;
			}
		}
		if (f) {
			cout << "Alice" << endl;
		} else {
			cout << "Bob" << endl;
		}
	}
	return 0;
}
```

---

## 作者：dehsirehC (赞：1)

结论：先手必胜当且仅当存在 $1\le i\le a_1$ 满足 $a_i=0$ 。

---

证明：

首先当 $a_1=0$ 时显然先手必败。

若存在 $1\le i\le a_1$ 满足 $a_i=0$ ，则先手只需第一步操作将 $a_1$ 换成 $0$ 即可获胜。

否则若后手操作时存在 $1\le i\le a_1$ 满足 $a_i=0$ ，则后手必胜，否则后手保持不动即可。

容易证明按照上述策略一直操作下去后手总能获胜。

---

运用该结论容易做到总时间复杂度 $O(Tn)$ 。

如果你使用了复杂度更高的做法通过了此题，欢迎联系我。

---

## 作者：joker_opof_qaq (赞：0)

我看到 $n$ 的范围真的觉得是个暴力，但是……

如果第一次第一个人操作范围有 $0$ 那就直接赢了，放到第一个即可。

此时我们要先明白，在无法完成绝杀时，不动，是最好的，能不动就不动。

而且经过 [SuperAlex4](https://www.luogu.com.cn/user/179187) 大佬的指导，我明白了，因为大冤种第一个人会在每一次我们开始前都会帮我们换成一个新的数字，所以大冤种第一个人却要因此在每一次开始前都要改第一个字符，所以第二个人也就掌握了主动权，只要可以绝杀，就绝杀，否则就保持不动，第二个人就赢了。

最后只要特判注意全都一样，是第二个人赢了。

---

## 作者：ELECTRODE_kaf (赞：0)

记 $first$ 为 $a_{1}$，$p$ 为 $a$ 中第一个 $0$ 的位置（如果有）。

如果 $first=0$，那么如题，Bob 胜。

如果 $first>0$：

如果全数列无 $0$，那么 Bob 也胜，因为首先 Alice 无法通过把 $0$ 放到开头的方式取胜。其次 Alice 只能尝试使 Bob 无法改变数列。但无论 Alice 怎么操作，她自己会先无法改变数列（因为当前状态是她创造的，Bob 必定不动，所以 Alice 就面对同一个序列两次了）

如果数列存在 $0$，那么考察该 $0$ 能否被调换到队头。显然当且仅当 $first \ge p$ 时该 $0$ 能被调换到队头。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,x,y) for(ll i=x;i<=y;i++)

ll q,n,a,first;

int main() {
	cin>>q;

	while(q--) {
		cin>>n;
		ll p=0;

		rep(i,1,n) {
			cin>>a;
			
			if(i==1){
				first=a;
			}

			if(p==0&&a==0) {
				p=i;
			}
		}

		if(first==0) {
			cout<<"Bob\n";
		} else {
			if(p>0&&first>=p) {
				cout<<"Alice\n";
			}else{
				cout<<"Bob\n";
			}
		}
	}
}
```

---

## 作者：gh_AC (赞：0)

## 思路：

首先我们可以知道如果 $ a_{1} $ 在一开始的值就为 $ 0 $ 的话，那么先手也就是 Alice 还没有操作就输了，所以就输出 ```Bob```。

接着我们可以发现如果一开始时在 Alice 能操作的范围内有一个是 $ 0 $，那么 Alice 就可以直接将这个 $ 0 $ 移到 $ a_{1} $ 上来，这样 Bob 就输了，就输出 ```Alice```。

最后一点我们知道 Bob 是可以不动的，那么只要 Alice 一开始不能让 Bob 输掉比赛，Bob 就可以一直不动，最后就是 Bob 获胜，就输出 ```Bob```。

## 代码：


```cpp
#include<iostream>
using namespace std;
int t;
int n,a[101];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(a[1]==0){
			cout<<"Bob"<<endl;
			continue;
		}
		for(int i=1;i<=a[1];i++){
			if(a[i]==0){
				cout<<"Alice"<<endl;
				break;
			}
			if(i==a[1]) cout<<"Bob"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：NingMeng_yang (赞：0)

# [题目传送阵](https://www.luogu.com.cn/problem/P11072)

题意不难 ，只用考虑 $ a_{1} $ 的值 ，并且考虑三种情况 ：

1. 当 $ a_{1} $ 的值为 $ 0 $ 或 $ 1 $ 时 ，则满足题意的第一种失败情况( 如果某一个人操作前 $ a_{1} = 0 $ ，则立刻输 )和第二种失败情况（ 如果某次操作结束后 ，存在两次操作满足操作结束后的 $ a_{1} $ 相同 ，则立刻输 ），再根据先手操作 ，则 Bob 赢 。
2. 整数序列中存在 $ 0 $ ，并且第一个 $ 0 $ 的位置在 $ a_{1} $ 的范围之内 ，因为 Alice 先手 ，则可以在第一次就把 $ 0 $ 放第一个位置 ，则 Bob 一定输 。
3. 针对第二种失败情况 ，如果每次 Bob 都复制 Alice 的操作 ，则当所有情况都遍历完 ，则 $ a_{1} $ 一定会有重复 ，满足第二种失败情况 ，因为 Alice 先手 ，则 Bob 必胜 。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=25;
int T;
int n;
int s[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		int idx=0;
		bool bl=false;
		bool vis=false;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>s[i];
			if(s[i]==0&&!bl) idx=i,bl=true;//判断是否有零 ，并记录第一个的位置
		}
		if(s[1]==0||s[1]==1)//第一种
		{
			cout<<"Bob"<<endl;
			continue;
		}
		if(s[1]>=idx&&bl)//第二种
		{
			cout<<"Alice"<<endl;
			continue;
		}
		cout<<"Bob"<<endl;//第三种
	}
	return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：0)

如果 Alice 第一步就输了或者第一步走完就赢了，这个情况是容易判断的。

考虑去掉这两种情况之后怎么做。

比如说现在 Bob 是个懒狗。如果 Alice 给他送了一个赢的机会（可以直接把 $0$ 移到 $a_1$ 处）那他就直接移动，否则他什么都不修改。

因为如果 Alice 移出了可以碰到 $0$ 的位置就会直接输，所以她只能在各种状态之间来回切换，而因为 Bob 不做任何变化，所以他产生的所有状态都和 Alice 是一样的，而 Alice 是先操作者，因此这个时候她必败。

~~合着我们随便想的一个懒狗玩法都能稳赢~~

```cpp
int n,a[25],p0;

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>n;
	p0=-1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(!a[i]&&!~p0)p0=i;
	}
	if(p0==1)cout<<"Bob\n";
	else if(~p0&&p0<=a[1])cout<<"Alice\n";
	else cout<<"Bob\n";
}
```

---

## 作者：xiaoliebao1115 (赞：0)

良心诈骗出题人。

- 初始时 $a_1=0$，后手胜。
- 若 $1$ 到 $a_1$ 当中有 $a_i=0$，可以让 $a_1=0$，那么先手胜。
- 剩下的情况，后手一定能取得胜利。若后手操作时 $1$ 到 $a_1$ 当中有 $0$，那么直接获胜，否则直接保持不变即可。这样操作先手必定比后手多出一种操作结束后的 $a_1$，先手必败。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[21],n;
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        if(a[1]==0) cout<<"Bob"<<endl;
        else{
            bool p=false;
            for(int i=1;i<=a[1];i++){
                if(a[i]==0){
                    cout<<"Alice"<<endl;
                    p=true;
                    break;
                }
            }
            if(!p) cout<<"Bob"<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

你说得对，但是数据范围让人感到困惑。

首先注意到题目给出了一些特殊性质，我们一个一个推。

首先全是 $0$，显然先手无法操作，输出 `Bob`。

接下来全是 $1$，先手第二轮必然做出与第一轮相同的举动，输，故输出 `Bob`。

然后 $a_i$ 全是相同的，注意到不管怎么样重排都是徒劳无功，第二轮操作必然步第一轮操作之后尘，所以输出 `Bob`。

最后 $a_i$ 全是不同的。其实并没有什么用，以下就是一般情况。

如果有 $0$ 能被拿到首位，那么一定拿，因为变成了第一种特殊情况。

那么没 $0$ 可拿呢？

我们可以这么做：

> 你动我不动，你不动我动。

其实这也是唯一的解决方法。为什么？因为如果对面不动的话，你不动就会输。映射到对面同理。

所以，要是没有 $0$，先手铁定输。

就是这样。时间复杂度 $O(\sum n)$。

```c++
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 21;
int n, a[N];
void run()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", a + i);
	}
	if (!a[0])
	{
		puts("Bob");
		return;
	}
	if (a[0] == 1)
	{
		puts("Bob");
		return;
	}
	for (int i = 0; i < a[0] and i < n; i++)
	{
		if (!a[i])
		{
			puts("Alice");
			return;
		}
	}
	puts("Bob");
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)
		run();
}
```

---

