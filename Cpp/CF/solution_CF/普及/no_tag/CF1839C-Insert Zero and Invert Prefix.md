# Insert Zero and Invert Prefix

## 题目描述

You have a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , each element of which is either $ 0 $ or $ 1 $ , and a sequence $ b $ , which is initially empty.

You are going to perform $ n $ operations. On each of them you will increase the length of $ b $ by $ 1 $ .

- On the $ i $ -th operation you choose an integer $ p $ between $ 0 $ and $ i-1 $ . You insert $ 0 $ in the sequence $ b $ on position $ p+1 $ (after the first $ p $ elements), and then you invert the first $ p $ elements of $ b $ .
- More formally: let's denote the sequence $ b $ before the $ i $ -th ( $ 1 \le i \le n $ ) operation as $ b_1, b_2, \ldots, b_{i-1} $ . On the $ i $ -th operation you choose an integer $ p $ between $ 0 $ and $ i-1 $ and replace $ b $ with $ \overline{b_1}, \overline{b_2}, \ldots, \overline{b_{p}}, 0, b_{p+1}, b_{p+2}, \ldots, b_{i-1} $ . Here, $ \overline{x} $ denotes the binary inversion. Hence, $ \overline{0} = 1 $ and $ \overline{1} = 0 $ .

You can find examples of operations in the Notes section.

Determine if there exists a sequence of operations that makes $ b $ equal to $ a $ . If such sequence of operations exists, find it.

## 说明/提示

In the first test case,

1. Before the first operation, $ b = [\,] $ . You choose $ p = 0 $ and replace $ b $ with $ [\, \underline{0} \,] $
2. On the second operation you choose $ p = 0 $ and replace $ b $ with $ [\, \underline{0}, 0 \,] $ .
3. On the third operation you choose $ p = 2 $ and replace $ b $ with $ [\, 1, 1, \underline{0} \,] $ .
4. On the fourth operation you choose $ p = 1 $ and replace $ b $ with $ [\, 0, \underline{0}, 1, 0 \,] $ .
5. On the fifth operation you choose $ p = 3 $ and replace $ b $ with $ [\, 1, 1, 0, \underline{0}, 0 \,] $ .

Hence, sequence $ b $ changes in the following way: $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 0 \,] $ $ \xrightarrow{p \, = \, 2} $ $ [\, 1, 1, \underline{0} \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 0, \underline{0}, 1, 0 \,] $ $ \xrightarrow{p \, = \, 3} $ $ [\, 1, 1, 0, \underline{0}, 0 \,] $ . In the end the sequence $ b $ is equal to the sequence $ a $ , so this way to perform operations is one of the correct answers.

In the second test case, $ n = 1 $ and the only achiveable sequence $ b $ is $ [\, 0 \, ] $ .

In the third test case, there are six possible sequences of operations:

1. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 0 \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 0, 0 \,] $ .
2. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 0 \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 1, \underline{0}, 0 \,] $ .
3. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 0 \,] $ $ \xrightarrow{p \, = \, 2} $ $ [\, 1, 1, \underline{0} \,] $ .
4. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 1, \underline{0} \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 1, 0 \,] $ .
5. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 1, \underline{0} \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 0, \underline{0}, 0 \,] $ .
6. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 1, \underline{0} \,] $ $ \xrightarrow{p \, = \, 2} $ $ [\, 0, 1, \underline{0} \,] $ .

None of them makes $ b $ equal to $ [\, 0, 1, 1 \,] $ , so the answer is "NO".

## 样例 #1

### 输入

```
4
5
1 1 0 0 0
1
1
3
0 1 1
6
1 0 0 1 1 0```

### 输出

```
YES
0 0 2 1 3
NO
NO
YES
0 1 0 2 4 2```

# 题解

## 作者：aeiouaoeiu (赞：4)

首先发现无解的情况只有 $a_n=1$。

正着做有点难搞，考虑倒着满足。 $a_i=0$ 时，在首插入 $0$。在一个长度为 $q$ 的连续 $1$ 块的结束点 $x$（即 $a_x=1,a_{x-1}=0$）中，如果 $i\neq x$ 则在首位插入 $0$，如果 $i=x$ 则在第 $q+1$ 为插入零，此时前 $q$ 个 $0$ 会变为 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100005;
ll n,a[maxn];
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T=1;
	cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(a[n]==1){
			cout<<"No\n";
			continue;
		}
		cout<<"Yes\n";
		ll cnt=0;
		for(int i=n;i>=1;i--){
			if(a[i]==0) cout<<"0 ";
			else{
				cnt++;
				if(a[i-1]==0){
					cout<<cnt<<" ";
					cnt=0;
				}else cout<<"0 ";
			}
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：233L (赞：4)

### 思路
构造题。题目要求将 $b$ 变成 $a$，考虑反着来，把 $a$ 变成空序列。那么原来的插入操作就变成删除，每次选一个 ```0``` 删去，并把它前面的元素翻转。

判断无解。显然，若 $a_n=1$，那么它永远不能被选中，即永远不能被删除，此时一定无解。

现在讨论 $a_n=0$ 的情况，可以删除 $a_n$，但如果删除后 $a_{n-1}$ 翻转成了 ```1```，不就又无解了吗？所以若此时的 $a_{n-1}$ 为 ```0```，那就先删除 $a_{n-1}$，否则就删除 $a_n$。每次都一定能删除一个元素，故一定有解。

### 实现细节
1. 输出操作时记得倒序。
2. 每次翻转时不要真的翻转，开一个 ```bool``` 标记现在的翻转即可。

### code
~~本来不想放的~~

```cpp
#include<bits/stdc++.h>
#define N 100004
using namespace std;
int n;
int a[N];
stack<int>s;

inline int read(){
	int x=0;
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch&15);
		ch=getchar();
	}
	return x;
}
int main(){
	int t=read(),rev;//rev 标记翻转的情况
	while(t--){
		rev=0,n=read();
		for(int i=0;i<n;i++)a[i]=read();//我把下标改成0~n-1，方便输出
		if(a[n-1]){
			printf("NO\n");
			continue;
		}
		printf("YES\n");
		for(int i=n-1;~i;i--,rev^=1){
			if(!i||a[i-1]^rev)s.push(i);//删除 a[i]
			else a[i-1]^=1,s.push(i-1);//删除a[i-1]
                	//原来的 a[i] 跑到 i-1 的位置上
                	//a[i] 是没有被翻转的，异或上 1 抵消反转效果
		}
		while(!s.empty()){
			printf("%d ",s.top());//倒序输出
			s.pop();
		}
		printf("\n");
	}
}
```

---

## 作者：Lonehll (赞：2)

首先当然是简单翻译一下题目啦！
### 题意
给定一个由 $0$ 和 $1$ 构成的序列，求出能构造出该序列的操作序列，规定操作如下：  
对于一个目前长度为 $n$ 的序列（最开始长度为 0），操作 $i$（$i$ 的取值范围为 $0-n$）会将该序列中前 $i$ 个元素进行反转（即 $0$ 变成 $1$,$1$ 变成 $0$），然后在第 $i+1$ 位插入一个 $0$。  
举例，对于操作序列$(0, 0, 2, 1)$，序列变化如下：
1. 操作 $0$，序列变为$[0]$。
1. 操作 $0$，序列变为$[0, 0]$。
1. 操作 $2$，序列变为$[1, 1, 0]$。
1. 操作 $1$，序列变为$[0, 0, 1, 0]$。

### 解法
首先我们就要判断是否具有合法解，不管做什么操作，显而易见的，操作完了之后最后一位都只能是 $0$，因此当序列最后一位是 $1$ 时，不具有合法解。  
那么对于最后一位是 $0$ 的时候，我们需要如何进行构造，如何思考其是否合法呢？  
首先给出结论，最后一位是 $0$ ，则必然有合法解。下面请听我慢慢分析。  
对于一个序列$[1, 1, \cdots, 1, 0]$，聪明的你一定能想到，我们可以使用操作序列$(0, 0, \cdots, 0, k)$来构造（$k$ 为该序列中 $1$ 的个数，$0$ 的个数为 $k$）。特殊地，对于 $k = 0$ 的情况，操作序列为$(0)$。   
而对于两个这样的序列拼起来的序列$[1, 1, \cdots, 1, 0, 1, 1, \cdots, 1, 0]$（前半部分和后半部分连续 $1$ 的个数分别为 $k_1$, $k_2$）的序列，可以使用操作序列$(0, 0, \cdots, 0, k_2, 0, 0, \cdots, 0, k_1)$（前半部分和后半部分连续 $0$ 的个数分别为 $k_2$，$k_1$），并且这种拼装对 $k = 0$ 的情况仍然适用。  
于是聪明的你一定发现了，对于最后一位为 $0$ 的序列，不管它是什么样的，都可以用这种拼装来表示，于是它们都合法，并且你也找到了它们所对应的操作序列，至此你就可以开心地 AC 了！

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int t, n, a[100010], b[100010], cnt = 0;

int main() {
	cin >> t;
	while(t--) {
		cnt = 0;
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		if(a[n] == 1) {
			cout << "NO" << endl;
			continue;
		}
		cout << "YES" << endl;
		
		int j = 0;
		for(int i = 1; i <= n; i++) {
			if(a[i] == 1) {
				j++;
			}
			else{
				b[++cnt] = j;
				for(int k = 1; k <= j; k++) {
					b[++cnt] = 0;
				}
				j = 0;
			}
		}
		for(int i = cnt; i >= 1; i--)
			cout << b[i] << " ";
		cout << endl;
	}
    return 0;
}
```


---

## 作者：Scorilon (赞：1)

首先考虑无解的情况，很明显 $a_n$ 必须为 $0$，否则没有解，因为如果最后一位为 $1$ 那么必须有 $n$ 这个数存在于 $b$ 序列中，而这种情况时不符合题意的。

然后考虑如何求解，先考虑一种比较特殊的情况，就是若干个 $1$ 后面接着一个 $0$，这里假设 $1$ 的数量有 $k$ 个，这种情况很明显可以先插入 $k$ 个位置为 $0$，然后再插入一个数 $k$，令前面 $k$ 个 $0$ 全部取反。

然后就是正解，通过上面的特殊的情况，我们可以从后往前扫，如果遇到了当前位为 $0$ 且前一位也为 $0$，那么就输出 $0$，因为这时我们可以多加一个 $0$ 且不会取反，注意到是从后往前扫，因此这个数最后会跑到相应的位置上去。如果遇到了当前位为 $0$ 但前一位为 $1$ 的情况，就是上面特殊的情况，我们可以继续往前扫，每遇到一个 $1$ 就输出一个 $0$，最后在输出我们统计的 $1$ 的数量。这样子就可以构造出合法的序列。

时间复杂度 $O(n)$。

```cpp
#include <cstdio>

int t,n;
int a[100005];

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
		}
		if(a[n]) {
			printf("No\n");
			continue;
		}
		printf("Yes\n");
		int f=0;
		for(int i=n;i>=1;i--) {
			if(!a[i]&&!a[i-1]) printf("0 ");
			else if(!a[i]) f=0;
			else if(a[i]) {
				f++;
				printf("0 ");
				if(!a[i-1]) printf("%d ",f);
			}
		}
		printf("\n");
	}
	return 0;
} 
```


---

## 作者：Saka_Noa (赞：0)

抽象做法。

考虑从后往前确定状态。新建一个虚点，我们维护从虚点的一棵树，那么答案就是子树 `size`。

具体的，一个点只受从虚点到它的路径的长度的奇偶性影响，若为 $1$ 则接在奇链下，$0$ 接在偶链。为保证路径不交叉，我们每次只接最近的奇/偶链。最后遍历一下这棵树，输出子树大小 `size` $-1$。

```cpp

#include<bits/stdc++.h>

typedef long long ll;
using namespace std;

#define gc getchar
int re() {
    int x = 0, f = 1;
    char c = gc() ;
    while(!isdigit(c)) {if(f == '-') f = -1; c = gc();}
    while(isdigit(c)) x = x * 10 + c - '0', c = gc();
    return x * f;
}

const int N = 2e5 + 5'0;

#define fail return (void)puts("NO")

int T;
int n;
int a[N], siz[N];

vector <int> e[N];

void dfs(int u) {
    siz[u] = 1;
    for(int v : e[u]) {
        dfs(v);
        siz[u] += siz[v];
    }
    if(u != n + 1) cout << siz[u] - 1 << " ";
}

void solve() {
    n = re();
    for(int i = 1; i <= n; ++i) a[i] = re();
    if(a[n] == 1) fail;
    for(int i = 0; i <= n + 2; ++i) e[i].clear();
    int si = 0, se = n + 1;
    for(int i = n; i >= 1; --i) {
        if(a[i] == 1) e[si].push_back(i), se = i;
        else e[se].push_back(i), si = i;
    }  
    puts("YES");
    dfs(n + 1);
    cout << endl;
}

int main(){
    T = re();
    while(T--) solve();

    return 0;
}

```

---

## 作者：rainygame (赞：0)

> 笑话：考场上想出来了，但是写成了答辩，最后差 $5$ 分钟就调完。差亿点点就可以破个人记录了。

本题还算简单，但是考验逆向思维。

我们现在得到了一个操作结束后的序列，我们该如何恢复它呢？

我们可以把插入看成是删除。这样问题就转化成了：给定一个序列，每次可以删除任意一个 $0$，且删除后将前面的所有数反转，求如何删除，或报告无解。

显然，当最前面是 $0$ 时，我们可以把它直接删除而没有任何影响。

而当前面的是 $1$ 时，我们可以删除最前面的一个 $0$，然后删除它，这样前面的所有 $1$ 都变成 $0$ 了，可以删除。

`NO` 的条件是最后一个数是 $1$，因为这样就永远无法删除这个 $1$。

不懂的话可以手摸一下样例。

为了操作方便，我们可以将连续的 $0$ 和 $1$ 分块以更好的处理这些数据。比如样例一分为 $[1,1][0,0,0]$，样例四分为 $[1][0,0][1,1][0]$。

然后枚举块，对于不同的值，有以下两种处理方法：

- 如果是值为 $0$ 的块，就直接输出块长那么多个 $0$（这里的 $0$ 表示从最前面删除），表示删除这些 $0$。
- 如果是值为 $1$ 的块，就先输出块长（表示删除后面一个块的第一个 $0$），然后再输出块长那么多个 $0$（此时这个块已经变成了 $0$）。

**注意：因为是从后往前删除的，所以要先用栈来储存要输出的东西，然后再栈里“倒”出来真正地输出。**

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001

int t, n, last, len, val, flag, ind;
stack<int> st;
struct Node{
	int len, val;
};
deque<Node> deq;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> t;
	
	while (t--){
		cin >> n;
		len = 0;
		last = -1;
		deq.clear();
		for (int i(1); i<=n; ++i){
			cin >> val;
			if (last != val){
				if (last != -1) deq.push_back({len, last});
				last = val;
				len = 1;
			}else ++len;
		}
		deq.push_back({len, last});
		
		if (deq.back().val){
			cout << "NO\n";
			continue;
		}

		ind = 0;
		for (auto i: deq){
			++ind;
			if (i.val){
				st.push(i.len);
				--deq[ind].len;
			}
			while (i.len--) st.push(0);
		}
		
		cout << "YES\n";
		while (!st.empty()){
			cout << st.top() << ' ';
			st.pop();
		}
		cout << '\n';
	}
	
	return 0;
}

```


---

