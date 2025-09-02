# Brutality

## 题目描述

在全新的格斗游戏《Kortal Mombat XII》中，你需要对对手的角色实施一招强势的「残暴攻击」。

手柄配备了 $26$ 个按钮，每个按钮上标有不同的小写字母，从 'a' 到 'z'。这意味着每个按钮只能通过对应字母按键激活。

我们有一系列的攻击动作，第 $i$ 次攻击会造成 $a_i$ 点伤害。为了执行第 $i$ 次攻击，你必须按下手柄上的 $s_i$ 按钮。攻击的编号依次为 $1$ 到 $n$。

然而如果连续按下某个按钮超过 $k$ 次，该按钮就会损坏。为了保护你的手柄不被损坏，你需要限制连续按同一按钮的次数。

「残暴攻击」要求你在不改变攻击顺序的前提下选择执行这些攻击动作中的若干次。每一次攻击都可以选择执行或跳过。跳过某次攻击不会重置同一按钮的连续按压次数。

你的任务是：跳过一些攻击，确保在不损坏任何手柄按钮的情况下，达到最大的总伤害值。

## 说明/提示

- 在第一个例子中，你可以选择攻击序列 $[1, 3, 4, 5, 6, 7]$，这样总伤害为 $1 + 16 + 18 + 7 + 2 + 10 = 54$。
- 在第二个例子中，选择全部攻击的总伤害为 $2 + 4 + 1 + 3 + 1000 = 1010$。
- 在第三个例子中，选择除第三次攻击外的其他攻击，总伤害为 $2 + 4 + 3 + 1000 = 1009$。
- 在第四个例子中，选择攻击序列 $[2, 3, 6, 8]$，可以最大化总伤害，即 $15 + 2 + 8 + 16 = 41$。
- 在第五个例子中，选择攻击序列 $[2, 4, 6]$，总伤害为 $18 + 19 + 15 = 52$。
- 在第六个例子中，只能选择第一个或第二个攻击，总伤害为 $10$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7 3
1 5 16 18 7 2 10
baaaaca
```

### 输出

```
54
```

## 样例 #2

### 输入

```
5 5
2 4 1 3 1000
aaaaa
```

### 输出

```
1010
```

## 样例 #3

### 输入

```
5 4
2 4 1 3 1000
aaaaa
```

### 输出

```
1009
```

## 样例 #4

### 输入

```
8 1
10 15 2 1 4 8 15 16
qqwweerr
```

### 输出

```
41
```

## 样例 #5

### 输入

```
6 3
14 18 9 19 2 15
cccccc
```

### 输出

```
52
```

## 样例 #6

### 输入

```
2 1
10 10
qq
```

### 输出

```
10
```

# 题解

## 作者：wlzhouzhuan (赞：2)

我们先将这个字符串分成几段，其中每端是一串相同的字符。

比如字符串$aaabddd$，我们将其分为$aaa$，$b$，$ddd$三段。

然后对于每一段，有以下两种可能：

$1.$如果这一段长度$<=k$，那么是合法的，对答案的贡献就是$\sum_{i=left}^{right}w[i]$，其中$left$和$right$是指这段区间的左端点和右端点.

$2.$如果这一段长度$>k$，那么我们需要挑出$w[i],left<=i<=right$中的最大的$k$个$w[i]$，自然想到用堆去维护最大的k个w[i]，当然也可以用STL里的$priority \space queue$卡过去.

最后奉上本蒟蒻的代码：

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; i++)

const int N = 200005;
char a[N];
int w[N], heap[N], n, k, cnt;
long long ans;

void read(int &x) {
	x = 0; int f = 1;
	char op = getchar();
	while (!isdigit(op)) {
		if (op == '-') f = -1;
		op = getchar();
	}
	while (isdigit(op)) {
		x = 10 * x + op - '0';
		op = getchar();
	}
	x *= f;
}

void read(char &x) {
	x = getchar();
	while (x < 'a' || x > 'z') x = getchar();
}

// 大根堆 
void up(int u) {
	int fa = u >> 1;
	if (fa > 0 && heap[fa] < heap[u]) {
		swap(heap[fa], heap[u]);
		up(fa);
	}
}

void down(int u) {
	int son = u << 1;
	if (son <= cnt) {
		if (son < cnt && heap[son] < heap[son + 1]) son++;
		if (heap[u] < heap[son]) {
			swap(heap[u], heap[son]);
			down(son);
		}
	}
}

int main() {
	read(n), read(k);
	rep(i, 1, n) read(w[i]);
	rep(i, 1, n) read(a[i]);
	rep(i, 1, n) {
		int j = i;
		while (j < n && a[j + 1] == a[i]) j++;
		// [i, j]
		if (j - i + 1 <= k) {
			rep(_, i, j) ans += w[_];
			i = j;
			continue;
		}
		cnt = 0;
		rep(_, i, j) {
			heap[++cnt] = w[_];
			up(cnt);
		}
		rep(_, 1, k) {
			ans += heap[1];
			heap[1] = heap[cnt--];
			down(1);
		}
		i = j;
	}
	printf("%lld\n", ans);
	return 0;
} 
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/solution/CF1107C)
### 题解
把打字的顺序分成一段一段相同连续字母的区间，比如字符串 `aaabbbbcc` 分成区间 $[1,3],[4,7],[8,9]$。

对于每一个区间 $[l,r]$，若 $r-l+1\leqslant k$，那么答案要加上 $\displaystyle\sum_{i=l}^{r}w_i$，否则，这个连续的区间里一定要加上其中的 $k$ 个（因为这个区间有一个字母不点，其他的字母点击顺序也是连续的），为了使答案最优，就要加上区间中最大的 $k$ 个。

总结一下做法：

1. 先把整体分成连续的相同字母的区间，这个可以用双指针实现。
2. 抠出区间里的数，从大到小排序，如果个数 $>m$ 的话就选择排序后前 $m$ 个，否则就选取所有的数（其实就是把前面的过程简化了）。

### 代码
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
const int N = 200010;
int n,m;
int a[N];
char s[N];
vector <int> seq[26];
int main () {
	cin >> n >> m;
	for (int i = 1;i <= n;i++) cin >> a[i];
	cin >> s + 1;
	LL ans = 0;
	for (int i = 1;i <= n;) {
		int j = i;
		vector <int> v;
		while (j <= n && s[j] == s[i]) v.push_back (a[j++]);
		sort (v.begin (),v.end (),greater <int> ());
		for (int k = 0;k < min (m,(int)v.size ());k++) ans += v[k];
		i = j;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 题目分析：

原题翻译中说要求对于 $i$ 个键必须按，其实是没有什么用处的，由于每一个按键的价值都是大于一的，所以一定不会出现不按要比按的价值高的情况，所以直接求出最大的价值就行了。

由于每一个相同按键连续按 $k$ 次就会坏，那么为了方便处理，可以考虑将所有的相同键的操作都改成一段区间，如果这个区间的长度没有 $k$ 大，那么根本不会有影响，否则就要考虑按什么键了。

发现对于一段长于 $k$ 的操作，摁造成伤害最高的 $k$ 个键一定能使得总伤害最高，否则将某一个伤害低的按键替换成某一个伤害更高的按键就可以在代价不变的前提下使得价值更优，那么就考虑把伤害最高的 $k$ 个操作取出来。

实现上，用一个堆来维护在键位一样的操作序列中的伤害值，在这样的一个序列结束的时候，将最大的 $k$ 个元素提取出来，累加即可。

---------
### 代码：

```cpp
#include<cstdio>
#include<queue>
using namespace std;
priority_queue <long long> atk;
long long n,k,a[200005],ans;
char s[200005];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		s[i]=getchar();
		while(s[i]>'z'||s[i]<'a')s[i]=getchar();
	}
	s[0]=s[1];
	for(int i=1;i<=n;i++){
		if(s[i]!=s[i-1]){
			for(int j=1;j<=k;j++){
				if(atk.empty())break;
				ans+=atk.top();
				atk.pop();
			}
			while(!atk.empty())atk.pop();
		}
		atk.push(a[i]);
	}
	for(int j=1;j<=k;j++){
		if(atk.empty())break;
		ans+=atk.top();
		atk.pop();
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：ciwomuli (赞：0)

读完题以后会发现这是一个很显然的贪心  
对于连续的字母我们自然是要取其中前k大的  
然后用priority_queue搞一下就可以了
```
#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#define LL long long
#define P pair<int,int>
using namespace std;
template <typename T>
inline void read(T &t)
{
    int f = 0, c = getchar();
    t = 0;
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        t = t * 10 + c - 48, c = getchar();
    if (f)
        t = -t;
}
template <typename T, typename... Args>
inline void read(T &t, Args &... args)
{
    read(t);
    read(args...);
}
const int maxn = 2e5 + 5;
int a[maxn];
priority_queue<LL> q;
int main(){
    int n,k;
    read(n, k);
    for (int i = 1;i<=n;i++) read(a[i]);
    LL ans = 0;
    int last = 0;
    for (int i = 1;i<=n;i++) {
        int ch=getchar()-'a';
        if(ch!=last){
            int cnt=k;
            while(cnt>0 && !q.empty()){
                ans+=q.top();
                q.pop();
                cnt--;
            }
            while(!q.empty())
                q.pop();
            last = ch;
        }
        q.push(a[i]);
    }
    int cnt=k;
    while(cnt>0 && !q.empty()){
        ans+=q.top();
        q.pop();
        cnt--;
    }
    while(!q.empty())
        q.pop();
    cout << ans;
}
```

---

