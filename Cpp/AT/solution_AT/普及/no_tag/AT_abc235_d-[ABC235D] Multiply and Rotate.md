# [ABC235D] Multiply and Rotate

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc235/tasks/abc235_d

正の整数 $ a $ があります。また、黒板に $ 1 $ 個の数が $ 10 $ 進表記で書かれています。  
 黒板に現在書かれている数を $ x $ としたとき、高橋君は次のいずれかの操作を行い、黒板に書かれている数を変化させることができます。

- $ x $ を消し、 $ x $ を $ a $ 倍した数を $ 10 $ 進表記で新たに書きこむ。
- $ x $ を文字列とみなして、列の末尾の数字を文字列の先頭に移動させる。  
   ただし、この操作は $ x\ \geq\ 10 $ かつ $ x $ が $ 10 $ で割り切れないときにしか行えない。

たとえば $ a\ =\ 2,\ x\ =\ 123 $ であるとき、高橋君は次のいずれかの操作を行うことができます。

- $ x $ を消して、 $ x\ \times\ a\ =\ 123\ \times\ 2\ =\ 246 $ を新たに書きこむ。
- $ x $ を文字列とみなして、`123` の末尾の数字である `3` を先頭に移動させる。黒板に書かれている数は $ 123 $ から $ 312 $ に変化する。

はじめ、黒板には $ 1 $ が書かれています。書かれている数を $ N $ に変化させるには最小で何回の操作が必要ですか？ただし、どのように操作しても書かれている数を $ N $ に変化させられない場合は $ -1 $ を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ a\ \lt\ 10^6 $
- $ 2\ \leq\ N\ \lt\ 10^6 $
- 入力はすべて整数である。

### Sample Explanation 1

以下に説明する操作を行うことで、 黒板に書かれている数を $ 4 $ 回で $ 1 $ から $ 72 $ に変化させることができます。 - $ 1 $ つ目の操作を行う。黒板に書かれている数は $ 1\ \to\ 3 $ に変わる。 - $ 1 $ つ目の操作を行う。黒板に書かれている数は $ 3\ \to\ 9 $ に変わる。 - $ 1 $ つ目の操作を行う。黒板に書かれている数は $ 9\ \to\ 27 $ に変わる。 - $ 2 $ つ目の操作を行う。黒板に書かれている数は $ 27\ \to\ 72 $ に変わる。 $ 3 $ 回以下の操作で $ 72 $ に変化させることはできないため、答えは $ 4 $ になります。

### Sample Explanation 2

どのように操作しても黒板に書かれている数を $ 5 $ に変化させることはできません。

### Sample Explanation 3

適切に操作を選ぶことで、 $ 1\ \to\ 2\ \to\ 4\ \to\ 8\ \to\ 16\ \to\ 32\ \to\ 64\ \to\ 46\ \to\ 92\ \to\ 29\ \to\ 58\ \to\ 116\ \to\ 611 $ と $ 12 $ 回の操作で黒板に書かれている数を $ 611 $ に変化させることができ、これが最小です。

## 样例 #1

### 输入

```
3 72```

### 输出

```
4```

## 样例 #2

### 输入

```
2 5```

### 输出

```
-1```

## 样例 #3

### 输入

```
2 611```

### 输出

```
12```

## 样例 #4

### 输入

```
2 767090```

### 输出

```
111```

# 题解

## 作者：zk_y (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc235_d)

这道题目让我们找最少的次数，我们就自然而然地想到了广度优先搜索求最短路。（其实这道题目有点像[神奇的电梯](https://www.luogu.com.cn/problem/P1135)）

我们只需要把转移位数的方式写好就行了。我们可以写一个判断位数的函数，让前面的几位个位移动，然后将之前个个位上的数前移就行了，这里我们最好写一个优化，因为如果这个数大于等于 $1\times 10^6$。那么他就无法再小于 $N$ 了。（$N\le 1\times 10^6$）

---
# AC代码
```cpp
#include<bits/stdc++.h>//头文件 
using namespace std;
#define ll long long//a乘当前数可能会超出long long 
struct INT{
	ll num;
	int step;
}top,top_1;
bool vis[1000005];
queue<INT> number;
ll wei(ll x){//判断位数 
	ll ans=0;
	if(x==0)return 1;
	while(x){
		x/=10;
		ans++;
	}
	return ans;
}
ll n,a,x;
int main(){
	scanf("%lld%lld",&a,&n);
	top.num=1;top.step=0;
	number.push(top);
	while(!number.empty()){
		top=top_1=number.front();
		number.pop();
		if(top.num==n){
			printf("%d",top.step);
			return 0;
		}//如果满足条件，退出 
		top.num*=a;
		if(top.num<=(ll)(1e6)){
			if(!vis[top.num]){
				top.step++;
				number.push(top);
				vis[top.num]=1;
			}
		}
		if(top_1.num%10!=0){
			x=top_1.num%10;
			top_1.num/=10;
			top_1.num+=(pow(10,wei(top_1.num))*x);//将个位移动到最高位之前 
			top_1.step++;
			if(!vis[top_1.num])number.push(top_1);
			vis[top_1.num]=1;
		}
	}
	printf("-1");
	return 0;
}
```


---

## 作者：CQ_Bob (赞：0)

## 分析

BFS 爆搜即可。

我们开个数组判断某一个数字是否搜索过，因为在 BFS 中第一次搜到的步数一定是最优的，所以在第二次找到时，我们就不需要将其再次加入队列。同时，我们还要判断一下上界，不然会一直搜索。这个上界很好判断，因为 $k \le 10^6$，而操作一只会使当前搜索到的数字更大，可能使这个数字变小的只有操作二。对于操作二，我们能执行到的数最多只有 $99999$，因为 $1000000$ 不满足条件，而 $1000001$ 是无法通过操作二变成小于等于 $10^6$ 的数的。所以这个上界就是 $10^6$。当然，往上加一点也是可以的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
const int MAXX=1e6+100;
int a,n;
map<int,bool> vis;
int qmi(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a;
		a=a*a,b>>=1;
	}
	return ans;
}
int bfs()
{
	queue<PII> qu;
	qu.push({1,0});
	while(!qu.empty())
	{
		PII now=qu.front();
		qu.pop();
		if(now.x==n) return now.y;
		else 
		{
			if(!vis[now.x*a]&&now.x*a<=MAXX)//操作1
			{
				vis[now.x*a]=1;
				qu.push({now.x*a,now.y+1});
			}
			if(now.x>10&&now.x%10!=0)//操作2
			{
				int s=now.x,siz=0,last=now.x%10;
				while(s) siz++,s/=10;
				int ans=(now.x/10+last*qmi(10,siz-1));
				if(!vis[ans]&&ans<=MAXX)
				{
					vis[ans]=1;
					qu.push({ans,now.y+1});
				}
			}
		}
	}
	return -1;
}
signed main()
{
	cin>>a>>n;
	cout<<bfs();
}
```


---

## 作者：chengning0909 (赞：0)

# abc 235 d

## 题意

现在给定一个 $a$ 和一个操作数 $X$，有两种操作：

1. 将 $X$ 乘 $a$。

2. 将 $X$ 看做成字符串，把 $X$ 循环右移一位（$X \ge 10$ 且 $X$ 不被 $10$ 整除）。

最开始 $X = 1$，请问最少需要多少次操作可以使得 $X$ 变为 $N$。

如果不能变成 $N$，输出 $-1$。

## 思路

我们可以将每种操作看作成一条边，那么其实就是求从 $1$ 到 $N$ 的最短路，可以用 `bfs`。

但是，这道题目还有一个比较有趣的点，它可以用**记忆化搜索**。

因为它有一个循环右移的操作，所以如果不停的做操作 2，就会构成一个环，但是这个环上的边必定有一条是不会走的，不然就会浪费，所以这是一张**有向无环图**，带有拓扑序。


---

## 作者：wnsyou (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc235_d)

## 题意

给定两个整数 $a$ 和 $n$，有一个整数 $x$，初始值为 $1$，有两种操作：

1. 将 $x$ 变成 $x \times a$。
2. **在 $x > 10$ 且 $x$ 不是十的倍数的情况下可以执行此操作：** 将 $x$ 当成一个字符串，将其循环右移一次。

求最少执行多少次操作能把 $x$ 变成 $n$，若无法将其变为 $n$，输出 `-1`。

## 思路

简单的广搜题。

首先，我们可以发现，操作 $1$ 只能把 $x$ 变大，操作 $2$ 既可以变小也可以变大，但并不能把 $x$ 的位数缩小，所以就可以推出来：当 $x$ 的位数比 $n$ 多时，是不可能再经过若干次操作变成 $n$ 的，也就自然不用往下进行了。

有了这个剪枝，这题也就可以轻松地过掉了。

详见代码。

## Code

```cpp
#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 1e6 + 10, INF = 1e6;

int a, n, f[MAXN];
queue<long long> q;

void Record (long long x, int lv) {
  if (x >= INF || f[x] != -1) { // 这种情况不合法或者有更优的操作次数
    return ; // 筛掉
  }
  f[x] = lv; // 记录
  q.push(x);
}

// 操作 2 会将最低位移到第高位，这里就是在求需要乘几才能把它移到最高位
long long W (long long x) {
  long long sum = 1;
  while (x) {
    x /= 10;
    sum *= 10;
  }
  return sum / 10;
}

void bfs () {
  Record(1, 0); // 初始状态
  while (!q.empty()) {
    long long t = q.front();
    q.pop();
    Record(t * a, f[t] + 1); // 操作 1
    if (t > 10 && t % 10) { // 满足要求，可以执行操作 2
      Record(t / 10 + (t % 10) * W(t), f[t] + 1); // 操作 2
    }
  }
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> a >> n;
  for (int i = 1; i < INF; i++) { // 无脑初始化
    f[i] = -1;
  }
  bfs();
  cout << f[n]; // 输出答案
  return 0;
}
```



---

## 作者：冷却心 (赞：0)

## 题意

给定整数 $a,n$。
有一个整数 $x$ 最初为 $1$。

每次可以操作 $x$，有两种操作:

- 将 $x$ 变为 $a\times x$。

- 如果 $x$ 不是 $10$ 的 倍数，则可以将 $x$ 在 $10$ 进制下的个位移动到开头，如 $51$ 变为 $15$.。

输出 $x$ 变为 $n$ 的最小步数。

## 解法

一个 BFS，但是普通的 BFS 过不了，可以加以下两个剪枝：

- 如果操作后新的 $x$ 大于 $n \times 10$，那么剪枝，因为操作 $1$ 可以将 $x$ 变大，操作 $2$ 可以变大也可以缩小，前提是 **数的位数** 相同。如果 $x$ 比 $n$ 还多一位，那就怎么也变不成 $n$。 

- 打标记数组，如果之前已经变成过 $x$ 且 步数也小于等于当前，就剪枝。根据 剪枝 $1$ 可得标记数组要打到 $n \times 10$。

队列的状态是一个结构体，存了 $x$ 和步数。

如果 当前已经到达 $n$，就输出答案退出。如果结束了广搜还是没有答案，就输出 $\mathtt{-1}$。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Fcin\
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
const LL N = 1e7 + 10;
LL A, n, vis[N];
struct Status{
	LL result, num;
};
int main(){
    Fcin;
    cin >> A >> n;
    queue<Status> q;
    q.push((Status){0, 1});
    memset(vis, 0x3f, sizeof(vis));
    vis[1] = 0;
    while (!q.empty()){
    	Status now = q.front(); q.pop();
    	if (now.num > n * 10)
    		continue;
    	if (now.num == n){
    		cout << now.result;
    		return 0;
		}
		if (vis[now.num] <= now.result && now.num != 1)
			continue;
		vis[now.num] = now.result;
    	if (now.num * A <= n * 10){
    		if (vis[now.num * A] > now.result + 1)
    			q.push((Status){now.result + 1, now.num * A});
		}
		if (now.num % 10 != 0){
			LL next = now.num / 10, g = now.num % 10, w = log10(now.num);
			next += g * pow(10, w);
    		if (vis[next] > now.result + 1)
				q.push((Status){now.result + 1, next});
		}
	}
	cout << -1;
	return 0;
}

```



---

