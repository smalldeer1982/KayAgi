# [GCJ 2011 Qualification] Bot Trust

## 题目描述

Blue 和 Orange 是两台友好的机器人。一个邪恶的电脑主谋把它们分别关在不同的走廊里进行测试，之后可能会给它们蛋糕。

每条走廊里都有 $100$ 个按钮，编号为正整数 $\{1, 2, \ldots, 100\}$。按钮 $k$ 总是在距离走廊起点 $k$ 米的位置，两个机器人都从按钮 $1$ 开始。在一秒钟内，机器人可以向任意方向走一米，或者按下当前位置的按钮一次，或者停在当前位置不按按钮。为了完成测试，机器人需要按照给定顺序依次按下某些按钮。两个机器人都提前知道完整的按钮序列。请问它们最少需要多少秒才能完成任务？

例如，考虑如下按钮序列：

O $2$, B $1$, B $2$, O $4$

这里，O $2$ 表示 Orange 走廊上的按钮 $2$，B $1$ 表示 Blue 走廊上的按钮 $1$，以此类推。机器人可以用如下策略在 $6$ 秒内完成按钮序列：

| 时间 | Orange | Blue |
| --- | --- | --- |
| $1$ | 移动到按钮 $2$ | 停在按钮 $1$ |
| $2$ | 按下按钮 $2$ | 停在按钮 $1$ |
| $3$ | 移动到按钮 $3$ | 按下按钮 $1$ |
| $4$ | 移动到按钮 $4$ | 移动到按钮 $2$ |
| $5$ | 停在按钮 $4$ | 按下按钮 $2$ |
| $6$ | 按下按钮 $4$ | 停在按钮 $2$ |

注意，Blue 必须等到 Orange 完全按完 O $2$ 之后，才能开始按 B $1$。

## 说明/提示

**限制条件**

- 对所有 $i$，$1 \leq P_i \leq 100$。

**小数据集（10 分，测试集 1 - 可见）**

- $1 \leq T \leq 20$。
- $1 \leq N \leq 10$。
- 时间限制：3 秒。

**大数据集（10 分，测试集 2 - 隐藏）**

- $1 \leq T \leq 100$。
- $1 \leq N \leq 100$。
- 时间限制：6 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
4 O 2 B 1 B 2 O 4
3 O 5 O 8 B 100
2 B 2 B 1```

### 输出

```
Case #1: 6
Case #2: 100
Case #3: 4```

# 题解

## 作者：tujiaqi12 (赞：2)

## 思路
设 Blue 的位置为 $bp$，完成上次任务用的时间为 $bt$。

设 Orange 的位置为 $bp$，完成上次任务用的时间为 $ot$。

如果 Blue 接到了任务，若只考虑自身，则应是如下代码。
```cpp
bt = bt + abs(bp - p) + 1;
```
但因为要和 Orange 按顺序来，所以应稍稍修改。
```cpp
bt = max(ot + 1,bt + abs(bp - p) + 1);
bp = p;
```
同理，如果 Orange 接到了任务，若只考虑自身，则应是如下代码。

```cpp
ot = max(bt + 1,ot + abs(op - p) + 1);
op = p;
```
## 整体代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t,n;
char r;
ll p;
int main(){
	scanf("%lld",&t);
	for(ll i = 1;i <= t;i++){
		scanf("%lld",&n);
		ll op = 1,ot = 0,bp = 1,bt = 0;
		for(ll j = 1;j <= n;j++){
			scanf(" %c %lld",&r,&p);
			if(r == 'O'){
				ot = max(bt + 1,ot + abs(op - p) + 1);
				op = p;
			}
			else{
				bt = max(ot + 1,bt + abs(bp - p) + 1);
				bp = p;
			}
		}
		printf("Case #%lld: %lld\n",i,max(ot,bt));
	}
	return 0;
}
```

---

## 作者：QQ9178 (赞：1)

思路：  
两个机器人初始位置都是 $1$，时间初始化为 $0$。  
处理每个按钮：对于每个按钮，确定是哪个机器人需要操作。计算该机器人移动到目标位置所需的时间，然后按按钮（需要 $1$ 秒），另一个机器人的移动时间会被并行处理，并且确保顺序正确。  
代码：  

```cpp
#include <bits/stdc++.h>
using namespace std;
struct T {
    char r;
    int p;
};
void solve() {
    int C;
    cin >> C;
    for (int t = 1; t <= C; ++t) {
        int N;
        cin >> N;
        vector<T> v(N);
        for (int i = 0; i < N; ++i) {
            cin >> v[i].r >> v[i].p;
        }
        
        int o = 1, b = 1;
        int ot = 0, bt = 0;
        int tt = 0;
        for (const T& task : v) {
            if (task.r == 'O') {
                int mt = abs(task.p - o);
                ot = max(ot + mt, bt) + 1;
                tt = ot;
                o = task.p;
            } else {
                int mt = abs(task.p - b);
                bt = max(bt + mt, ot) + 1;
                tt = bt;
                b = task.p;
            }
        }
        cout << "Case #" << t << ": " << tt << endl;
    }
}
int main() {
    solve();
    return 0;
}
```

---

## 作者：TFX_Y (赞：1)

## 本题思路
第一眼看到此题，我们就可以想到模拟机器人的位置来解决问题。

我们可以用 $pos$ 表示机器人当前的位置，$num$ 表示机器人已经按了多少个按钮。

然后我们依次查看每个按按钮操作，判断该哪一个机器人按按钮，并计算出来这个机器人走到下一个按钮位置和按按钮的用时，也就是距离 $+1$。

再看另一个机器人，如果这个机器人要按的下一个按钮的位置在后面，如果能到就停在那里，否则走到能走到的最远位置。

最后更新两个机器人的位置和已经按了多少个按钮即可。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int nm=1005;
int t,n,m,k,leno,lenb;
int o[nm],b[nm];
char c[nm];
int solve(){
  int poso=1,posb=1;  //pos表示机器人当前的位置
  int numo=0,numb=0,ans=0;  //num表示机器人已经按了多少个按钮
	for(int i=1;i<=n;i++){
        if(c[i]=='O'){
            int tim=abs(o[++numo]-poso)+1;  //计算出来机器人O走到下一个按钮位置和按按钮的用时
            ans+=tim;
            if(b[numb+1]>=posb) posb=min(b[numb+1],posb+tim);
            //如果下一个按钮的位置在后面，如果能到就停在那里，否则走到能走到的最远位置
            else posb=max(b[numb+1],posb-tim);
            poso=o[numo];
        }
        else{
            int tim=abs(b[++numb]-posb)+1;
            ans+=tim;
            if(o[numo+1]>=poso) poso=min(o[numo+1],poso+tim);
            else poso=max(o[numo+1],poso-tim);
            posb=b[numb];
        }
    }
	return ans;
}
int main(){
	cin>>t;
	for(int j=1;j<=t;j++){
        leno=lenb=0;
		cin>>n;
		for(int i=1;i<=n;i++){
            cin>>c[i]>>k;
            if(c[i]=='O') o[++leno]=k;
            else b[++lenb]=k;  
        }
		cout<<"Case #"<<j<<": "<<solve()<<"\n";
	}
	return "MB WILL AK IOI",0;
} 
```

## PS

看到数据范围和时间限制，$T$ 和 $N$ 都小于等于 $100$，时限在 $3$~$6$ 秒之间。我们感觉它一把，即使时间限制是 $10$ $ms$ 的话 $O(Tn)$ 应该也能过。结果事实证明了它确实可以。

~~Google Code Jam 的题很奇特，据说还有一些不知道为什么时限开了 4 分钟的题，简直是在浪费评测机的时间。不知道这是哪道神题？~~

---

## 作者：BlackHoles (赞：1)

### 正解

我们使用 deque $O$ 和 $B$ 分别存储小 O 和小 B 的操作，用另一个 deque $Opt$ 存操作顺序。

每次模拟即可，用 $posO$ 和 $posB$ 记录二人位置，对小 O 和小 B 分别判断，能按按钮就按按钮，否则就判断是否需要移动。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n;
int sgn(int x) {
	if (x > 0) return 1;
	else return -1;
}
int main(void) {
	cin.tie(0), cout.tie(0);
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		cin >> n;
		deque <int> O, B;
		deque <char> Opt;
		char opt;
		int pos, posO = 1, posB = 1;
		for (int i = 1; i <= n; ++i) {
			cin >> opt >> pos;
			if (opt == 'O')
				O.push_back(pos);
			else
				B.push_back(pos);
			Opt.push_back(opt);
		}
		int cnt = 0;
		while (!O.empty() || !B.empty()) {
			++cnt;
			bool flag = false;
			if (!O.empty() && posO == O.front() && Opt.front() == 'O') {
				O.pop_front();
				flag = true;
			}
			else if (!O.empty() && posO != O.front())
				posO += sgn(O.front() - posO);
			if (!B.empty() && posB == B.front() && Opt.front() == 'B') {
				B.pop_front();
				flag = true;
			}
			else if (!B.empty() && posB != B.front())
				posB += sgn(B.front() - posB);
			if (flag)
				Opt.pop_front();
		}
		cout << "Case #" << t << ": " << cnt << '\n';
	}
	return 0;
}
```

谢谢大家！点个赞吧（逃

---

## 作者：hlb44 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13361)

模拟题。

容易发现最开始的时候，两个机器人都从按钮 $1$ 开始，初始时间为 $0$。

现在我们只需要对于序列中的每个按钮，确定对应的机器人。

接着我们根据机器人的位置和到目标按钮的距离，计算到达目标位置所需的移动时间。

有坑：

机器人必须到达目标位置后才能按下按钮。

必须在前一个按钮操作完成后才能进行当前操作。因此，操作时间是到达目标位置的时间与前一个操作完成时间中的较大值加 $1$。

最后更新状态即可。


```cpp
#include<iostream>
using namespace std;
int main() {
	int T;
	cin>>T;
	for(int c=1; c<=T; ++c) {
		int N;
		cin>>N;
		int t=0,pB=1,pO=1,tB=0,tO=0;
		for(int i=0; i<N; ++i) {
			char R;
			int P;
			cin>>R>>P;
			if(R=='B') {
				int a=tB+abs(P-pB);
				int pt=max(a,t)+1;
				t=pt;
				pB=P;
				tB=pt;
			} else {
				int a=tO+abs(P-pO);
				int pt=max(a,t)+1;
				t=pt;
				pO=P;
				tO=pt;
			}
		}
		cout<<"Case #"<<c<<": "<<t<<endl;
	}
	return 0;
}
```

---

## 作者：yuxinrui0618 (赞：0)

# 题解：P13361 [GCJ 2011 Qualification] Bot Trust
## 1. 题目大意
- 按照一定次序使用两个机器人进行按按钮的操作；
- **一定要在一个机器人的任务完成后另一个才能开始动**。

## 2. 思路
- 因为同一时间只会有一个机器人运作，这个机器人的任务完成后另一个才开始运作；
- 所以只需要计算某机器人上个机器人完成任务后，要花多长时间来完成当下他的任务即可；
- 一定要注意，虽然题目问的是最小值，但一定是要两个机器人的任务都完成才结束，即每次保存两个机器人用时更大的一个作为时间。

## 3. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin>>t;
	for (int x=1;x<=t;x++)
	{
		int n;
		cin>>n;
		int p=1,t=0,pp=1,tt=0;  //p：当前Orange所在位置，t：上次Orange完成任务后的时间 pp：当前Blue所在位置，tt：上次Blue完成任务后的时间
		for (int i=1;i<=n;i++)
		{
			char r;
			int pos;
			cin>>r>>pos;
			if (r=='O')
			{
				int dis=abs(p-pos); //计算移动距离
				t=max(tt+1,t+dis+1); //为保证时间正确，每次都要取时间更久的那个
				p=pos;
			}
			else
			{
				int dis=abs(pp-pos);
				tt=max(t+1,tt+dis+1);
				pp=pos;
			}
		}
		cout<<"Case #"<<x<<": "<<max(tt,t)<<endl; //注意冒号后面要空格
	}
    return 0;
}
```

## 4. 总结
谢谢观赏！  
如存在问题或可以优化的地方还请各位大佬指出！

---

## 作者：abc1234shi (赞：0)

# 分析
模拟题和贪心结合。

在每一秒中，两个机器人都要进行操作，有以下操作：

- 前进 $1$ 步。
- 按下按钮。
- 停止不动。

问题的关键在于如何高效安排两个机器人的移动和按钮按下顺序（模拟），使得总时间最短（贪心）。这里有个规定：每个机器人必须等待另一个机器人完成其当前任务后才能继续。

# 思路实现
遍历所有的按钮，对于每个按钮，计算要按下这个按钮的机器人从上一个位置移动到目标按钮所需的时间，同时考虑另一个机器人在这段时间内可以移动或等待（如果时间足够，可以到达自己下一个要到达的按钮等待）。

要保证按下按钮时机器人在按钮上，不能隔空按按钮。并且要保证这个按钮按下时，上一个操作已完成（上一个要按的按钮被按了）。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin>>t;
	for(int c=1; c<=t; ++c) {
		int n,p[100];
		char r[100];
		cin>>n;
		for(int i=0; i<n; ++i) {
			cin>>r[i]>>p[i];
		}
		int s=0,op=1,bp=1,ot=0,bt=0;
		for(int i=0; i<n; ++i) {
			if(r[i]=='O') {
				int d;
				if(p[i]>op)d=p[i]-op;
				else d=op-p[i];
				int nt=ot+d+1;
				if(nt<s+1)nt=s+1;
				ot=nt;
				op=p[i];
				s=nt;
			} else {
				int d;
				if(p[i]>bp)d=p[i]-bp;
				else d=bp-p[i];
				int nt=bt+d+1;
				if(nt<s+1)nt=s+1;
				bt=nt;
				bp=p[i];
				s=nt;
			}
			
		}
		cout<<"Case #"<<c<<": "<<s<<endl;
	}
	return 0;
}
```

---

## 作者：Clouds_dream (赞：0)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13361)  
就是计算两个机器人按照给定顺序按下按钮序列所需的最短时间。

### 题目分析
我们只需要模拟两个机器人（蓝色和橙色）的当前位置以及它们上一次操作完成的时间。对于每个按钮，计算当前机器人完成该操作所需的时间，即该机器人上一个操作完成的时间加上移动时间（当前位置到目标位置的差的绝对值加 1 秒的按键时间）。最后，总时间更新为当前操作完成的时间与另一个机器人完成上一个操作的时间中的较大值即可。

### 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int ti;

void f(int t){
	int x;
	cin>>x;
	vector<pair<char,int> >a(x);//颜色和位置
	for(int i=0;i<x;i++){
		cin>>a[i].first>>a[i].second;
	}
	int ans=0;
	int poso=1,posb=1;//初始位置
	int tb=0,to=0;//初始时间
	for(auto &e:a){
		if(e.first=='O'){
			int mt=abs(e.second-poso)+1;
			to=max(to+mt,tb+1);
			poso=e.second;
			ans=max(ans,to);
		}
		else{
			int mt=abs(e.second-posb)+1;
			tb=max(tb+mt,to+1);
			posb=e.second;
			ans=max(ans,tb);
		}
	}
	cout<<"Case #"<<t<<": "<<ans<<endl;
}

signed main()
{
	fst
	cin>>ti;
	for(int i=1;i<=ti;i++){
		f(i);
	}
	return 0;
}
```

---

## 作者：wurang (赞：0)

由于两个机器人同时移动不好考虑，我们先考虑一次只有一个机器人移动的情况。

我们记录机器人 Orange 和 Blue 的位置分别为 $posa$ 和 $posb$，那么他们移动的时间开销便是 $\left| posa - x \right|$ 与 $\left| posb - x \right|$。

这时候我们会想到一个做法，在 Orange 或 Blue 移动时。累加他们按按钮的时间开销，然后另一个机器人在这段时间中是完全自由的，记录 $tima$，$timb$ 表示 Orange 闲置的时间与 Blue 闲置的时间，那么 Orange 移动的时间开销就是 $\max\left(0,\left| posa - x \right| - tima\right)$，Blue 移动的时间开销就是 $\max\left(0,\left| posb - x \right| - timb\right)$。

那么如何维护 $tima$ 与 $timb$ 呢？


在 Orange 去按按钮时，有以下更新，此处 $v$ 为 Orange 去按按钮的时间开销。
$$
\begin{align} \notag
&tima = 0 \\ \notag
&timb = timb + v \\ \notag
\end{align}
$$

Blue 同理。

注意按按钮时有 $1$ 的开销，以及一个人按按钮时，另一个人不能按按钮。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

char c;
int n, T, x, sum, v;
int posa, posb, tima, timb;

signed main()
{
    cin >> T;
    for(int i = 1; i <= T; i++)
    {
        posa = posb = 1, tima = 0, timb = 0; // 多测初始化
        sum = 0;
        cin >> n;
        while(n--)
        {
            cin >> c >> x;
            if(c == 'O')
            {
                v = max(0ll, abs(posa - x) - tima) + 1; // 时间开销
                // 此处将 + 1 写出来就避免了两个人同时按按钮的现象
                timb += v; // 更新
                tima = 0;
                sum += v;
                posa = x;
            }
            else
            { // 同理
                v = max(0ll, abs(posb - x) - timb) + 1;
                tima += v;
                timb = 0;
                sum += v;
                posb = x;
            }
        }
        cout << "Case #" << i << ": " << sum << "\n";
    }
	return 0;
}


```

---

