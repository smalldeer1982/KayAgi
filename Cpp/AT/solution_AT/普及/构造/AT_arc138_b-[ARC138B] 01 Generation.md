# [ARC138B] 01 Generation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc138/tasks/arc138_b

すぬけくんは，$ 0 $ と $ 1 $ からなる長さ $ N $ の整数列を作ろうとしています． 今すぬけ君は空の数列 $ x $ を持っており，これから以下の $ 2 $ 種類の操作を好きな順番で $ N $ 回行います．

- 操作A: $ x $ の要素をすべて flip する．つまり，$ 0 $ ならば $ 1 $ に変え，$ 1 $ ならば $ 0 $ に変える． その後，$ x $ の先頭に $ 0 $ を追加する．
- 操作B: $ x $ の末尾に $ 0 $ を追加する．

$ 0 $ と $ 1 $ からなる長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $ が与えられます． $ x $ を $ A $ に一致させることが可能かどうか判定してください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 1 $
- 入力される値はすべて整数

### Sample Explanation 1

以下のように操作すればよいです． - 始状態：$ x=() $ - 操作Aを行う．$ x=(0) $ となる． - 操作Bを行う．$ x=(0,0) $ となる． - 操作Aを行う．$ x=(0,1,1) $ となる． - 操作Bを行う．$ x=(0,1,1,0) $ となる．

## 样例 #1

### 输入

```
4
0 1 1 0```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4
1 0 0 0```

### 输出

```
No```

## 样例 #3

### 输入

```
4
0 0 0 1```

### 输出

```
No```

# 题解

## 作者：4041nofoundGeoge (赞：1)

~~估值快掉啦，赶紧写题解！~~

这道题需要用到逆向思维。

## 题目简述

给定一个长度为 $n$ 的 01 串，并给出 A B 两种操作，要求判断是否可以由一个空串通过这两种操作构造出该 01 串。

两种操作分别为：

- A 操作：将串中的每一位翻转，各位取反，最后再在串的最前面追加一个 $0$。
- B 操作：在串的最后面追加一个 $0$。

如果可以构造出来，输出 `Yes`，否则输出 `No`。

### 样例解析 $1$

1. 先做两次 B，即 $\{0,0\}$。
2. 再做一次 A，即 $\{1,1,0\}$。
3. 再做一次 A，即 $\{0,1,1,0\}$。

即可构造出这个 01 串，输出 `Yes`。

## 思路

如果我们正向思维，计算机不像人脑可以自动构造这个东西（也许吧），所以我们可以用逆向思维。利用双指针，并添加 $res$ 数据，代表现在是 $0$ 或 $1$，不难发现：

1. 如果这个数字为 $res$，可以把这个数丢弃，即右指针往左移，直到不成立。
2. 如果左指针**依然等于 $res$**，明显无解（可以模拟样例 $2$）。
3. 反之，$res$ 取反，左指针向右移。

然后这道题就迎刃而解了。

最坏复杂度：$O(n)$。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5; 
int a[MAXN];
int main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int l=1,r=n,res=1;
	while(l<=r) {
		while(a[r]!=res)r--;
		if (a[l]!=res) {
			res=(1-res);//取反，也可以写成res^=1; 
			l++;
		} 
		else {
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}
```

---

## 作者：_shine_ (赞：1)

## 题目大意
现在有一个长度为 $n$ 的 $01$ 串，现在有两种操作，请问，你是否能从一个空串构造出这个 $01$ 串：

操作一：把串中的每一位翻转，并且在串的最前面追加一个 $0$。

操作二：在串的末尾添加一个 $0$。

## 思路
这道题，我们不难发现以下两种性质：

性质一：删去这个串末尾的 $0$ 并不会影响这个我们要还原的串（因为这个串的操作二可以直接在末尾添加 $0$）。

性质二：在我们的开头，一定不是以 $1$ 开头，证明：

我们在性质一中，其实就可以发现，无论如何，就算是执行性质一的反转操作，也会在我们的串前面添加一个 $0$，而性质二跟开头无关。

那么，我们其实就可以看出，想要做出这道题，最好的方法其实就是倒推这样的逆向思维来推导出这道题的答案。

我们可以先疯狂的删去末尾的 $0$，直至末尾为 $1$（原因在性质一中有提及），随后模拟即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
    while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;ch=getchar();
	}
    while(ch>='0'&&ch<='9'){
    	s=s*10+ch-'0';
		ch=getchar();
	}
    return s*w;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x % 10 + '0');
}
int n,a[maxn];
int l=1,r,ans=1;
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
	}
	r=n;
	while(l<=r){
		if(a[r]!=ans)r--;
		else if(a[l]!=ans){
			ans^=1;
			l++;
		}else{
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}

```


---

## 作者：Pretharp (赞：1)

**思路：**

不妨先从题目给出的 $01$ 串向空串还原。上例子：

```
0 1 0 0 1 1 1 0 0
```

我们可以先将该 01 串划分成若干个子串，保证每个子串都满足字串内所有的字符相同，且最长。例如，以上例子可以按此划分：

```
0 | 1 | 0 0 | 1 1 1 | 0 0
```

我们可以想象，从空串操作为例子中的目标串中，最后两步是在后面添加了两个 $0$。因为我们是从目标串向空串还原，所以最后的两个 $0$ 我们可以先删掉，从而例子变成了：

```
0 | 1 | 0 0 | 1 1 1
```

此时，末尾的子串的字符为 $1$。很显然，从空串操作为例子中的目标串中，在添加字符为 $1$ 的子串与添加刚刚删除的字串中，在前面添加了一个 $0$，使得 $01$ 之间翻转了。那么我们删除前面的一个 $0$：

```
1 | 0 0 | 1 1 1
```

接着再删除后面的子串，以此往复，最终该串变为了空串，所以在这个例子中答案为 `Yes`。

那么什么时候答案为 `No` 呢？我们都知道，在前面添加 $0$ 会使得整个串 $01$ 翻转，换而言之，前面不可能出现一个长度为 $2$ 或更大的子串。若出现了，此时我们就输出 `No`。

**复杂度：**

读入 $O(n)$，处理 $O(n)$，共 $O(n)$。

**代码**：

```cpp
//#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define ll long long
#define in_ long long
#define db long double
#define endl '\n'
#define pii pair<int,int>
#define fir first
#define sec second
#define pb push_back
#define mijacs using
#define so namespace
#define lovely std
mijacs so lovely;
const int INF2=0x3f3f3f3f;
const int mod1=998244353;
const int mod2=1e9+7;
const ll INF1=1e18;
const int N=2e5+5;
int n,a[N];
signed main()
{
   // freopen("input.in","r",stdin);
   // freopen("output.out","w",stdout);
    cin.tie(0),cout.tie(0);
    ios_base::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int p=1,q=n,r=1;
    // 在实际操作中，我们不会真的删除字符串（因为很耗时间），我们会使用 p 和 q 记录当前字符串的首尾。
    // r 表示当前的后面的子串应当是什么颜色，否则我们应该删除前面的，同时也可以用于判断前面的子串是否有长度 >2 的。
    while(p<=q){
        if(a[q]!=r){
            q--;
        }else{
            if(a[p]!=r){
                r^=1,p++;
            }else{
                return cout<<"No"<<endl,0;
            }
        }
    }
    return cout<<"Yes"<<endl,0;
}
```

---

## 作者：Andy2011_swsgroitfh (赞：0)

## [AT_arc138_b [ARC138B] 01 Generation](https://www.luogu.com.cn/problem/AT_arc138_b)题解
### 思路
构造出两种 A B 的反向操作：
- A' 操作：将串中的每一位翻转，即 0 变成 1，1 变成 0，最后再在串的最前面**删除**一个 0。
- B' 操作：在串的最后面**删除**一个 0。

于是想到将原串逐步变为空串。
### 代码
双指针模拟头尾
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010];
int main(){
	//读入 
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	int l=1,r=n;//l左指针 r右指针 
	int k=0;//k表示当前最后一位应为的状态
	while (l<=r){//左指针应当小等于右指针 
		//右指针a[r]为零 
		if (a[r]==k){
			//进行B'操作 
			r--;
		}
		//左指针a[l]为一 
		else if (a[l]!=k){
			//左右都为一，无法进行操作 
			printf("No\n");
			return 0;
		}
		//左指针a[l]为零 
		else if (a[l]==k){
			//进行A'操作 
			k^=1;//全部进行翻转，相当于将最后一位应为的状态翻转 
			l++;
		}
	}
	printf("Yes\n");
	return 0;
}
```

---

## 作者：__Creeper__ (赞：0)

## 思路

双指针。

- 当末尾是 $0$ 的时候反复左移右指针，否则输出 ```No```。
- 末尾是 $1$ 的时候，把 $0$ 去掉，左指针右移，取反整个序列。

还需维护一个 $res$，表示翻转次数。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n, a[N];
int l, r, res;

void solve()
{
	cin >> n;
	for ( int i = 1; i <= n; i++ ) cin >> a[i];
	l = 1, r = n, res = 1;
	while ( l <= r ) 
	{
		while ( a[r] != res ) r--;
		if ( a[l] != res ) 
		{
			res ^= 1;
			l++;
		} 
		else 
		{
			cout << "No\n";
			return;
		}
	}
	cout << "Yes\n";
}

signed main() 
{
	int T = 1;
//	cin >> T;
	while ( T-- ) solve();
	return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## [ARC138B] 01 Generation 题解

### 思路分析

正序构造很难，考虑逆序消除。

对于 B 操作，考虑记录一个 $=f$，表示这个序列是否被反转。

写出获取第 $w$ 位的数字和反转序列的代码。

```cpp
bool rf;
inline int get(int w)
{
    return p[w] ^ rf;
}
inline void rev()
{
    rf ^= true;
}
```

然后使用双指针，当末尾是 $0$ 的时候反复左移右指针。

末尾是 $1$ 的时候取反整个序列，在取反前先判断开头是不是 $0$，不是就不能构造，是就将左指针右移。

如果消完了，就是可以构造。

### 代码实现

```cpp
#include <cstdio>
constexpr int MaxN = 2e5 + 5;
int n;
int p[MaxN];
bool rf;
inline int get(int w)
{
    return p[w] ^ rf;
}
inline void rev()
{
    rf ^= true;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    int i, j;
    i = 1;
    j = n;
    for (; i <= j;)
    {
        for (; get(j) == 0;)
        {
            j--;
        }
        if (get(i) == 1)
        {
            printf("No\n");
            return 0;
        }
        i++;
        rev();
    }
    printf("Yes\n");
    return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

给定一个长度为 $n$ 的 01 串，并给出 A B 两种操作，要求判断是否可以由一个空串通过这两种操作构造出该 01 串。

两种操作分别为：
- A 操作：将串中的每一位翻转，即 $0$ 变成 $1$，$1$ 变成 $0$，最后再在串的最前面追加一个 $0$。
- B 操作：在串的最后面追加一个 $0$。

如果可以构造出来，输出 `Yes`，否则输出 `No`。

观察题意。容易看出操作只能在结尾或开头，想到双指针。

发现 B 操作只会在结尾。所以，可以先把结尾的 $0$ 去掉，不影响答案。可以将右指针左移。

接下来，A 操作使得开头一定是 $0$，所以如果当前处理串的开头是 $1$，那么直接输出 `No`。

否则，把 $0$ 去掉，左指针右移，把剩下的部分反转，直到 $l = r$ 结束。

实际操作中只要维护一个 $cnt$，表示反转的次数，若 $cnt$ 为奇数则将判断条件反过来即可。

```cpp
#include <iostream>
using namespace std;

int n, a[200005];

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	int l = 1, r = n, cnt = 1;
	while(l <= r) {
		while(a[r] != cnt) r--;
		if(a[l] != cnt) {
			cnt = !cnt;
			l++;
		} else {
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";
}
```

---

## 作者：Union_Find (赞：0)

这道题首先从头开始想比较难想，所以我们可以从最终状态考虑。我们发现有以下性质。

- 当前字符串不管后面有几个 $0$ 都无所谓，都可以通过 $2$ 操作得到。

- 当前字符串必须由 $0$ 开头，因为我们无法操作得到开头是 $1$ 的字符串。

所以我们就有了这题的解法。从给定字符串开始，先去掉结尾的 $0$，然后判断开头是否是 $0$。如果是 $1$ 就无解。否则删除开头，然后反转剩下字符串。

具体实现的时候可以用双指针模拟删除。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), a[N], sum;
int main(){
	for (int i = 1; i <= n; i++) a[i] = rd();
	for (int i = 1, j = n, p = 0; i <= j; i++, p ^= 1){
		while (!(a[j] ^ p)) j--;
		if (a[i] ^ p) return 0 & puts("No");
	}puts("Yes");
	return 0;
}

```

---

## 作者：XYQ_102 (赞：0)

首先不妨考虑从给定序列出发看能不能删完。

发现第一个关键性质：从当前状态疯狂逆向做 B 操作（删末尾的  $0$）是不会对 A 操作产生影响的，这个应该比较好想。

而第二个关键性质就是：任何时候序列开头都不可能为 $1$，如果为 $0$ 的话，考虑先逆向做 B 操作后逆向做 A 操作（删掉开头并打上标记）。

使用 deque 模拟即可。
```cpp
const int maxn = 2e5 + 5;
int a[maxn], n, tag;
deque<int> q;

void delZero(deque<int> &q) {
    while (!q.empty() && ((q.back() ^ tag) == 0)) q.pop_back();
    return;
}

int main() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i], q.push_back(a[i]);
    while (true) {
        delZero(q);
        if (q.empty()) break;
        if (q.front() ^ tag) return puts("No"), 0;
        else {
            q.pop_front(), tag ^= 1;
        }
    }
    return puts("Yes"), 0;
}
```

---

## 作者：_QyGyQ_ (赞：0)

我们可以尝试把题目所给的串向空串还原。首先，我们可以利用操作二来删除串末尾的零。直到串末尾为一时，我们就需要先用操作一使串反转，再使用操作二。随后一直模拟即可。但是如果序列第一项是一，那么这个串就不可能还原成空串。因为能够影响开头的操作只有操作一，但是操作一会向序列前增加一个零。所以无法还原。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+7;
int a[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	if(a[1]==1){
		puts("No");
		return 0;
	}
	int nn=n;
	for(int i=nn;i>=1;i--){
		if(!a[i]) n--;
		if(a[i]) break;
	}
	int l=1,r=n,now=1;
	bool f=true;
	for(;l<=r;){
		if(a[r]!=now){
			r--;
		}
		else if(a[l]!=now){
			now^=1;
			l++;
		}
		else{
			puts("No");
			f=false;
			break;
		}
	}
	if(f) puts("Yes");
	return 0;
}

```

---

## 作者：Scean_Tong (赞：0)

## 解题思路

显然如果可以通过若干次 A 和 B 操作得到一个长度为 $n$ 的 01 串，则这个串的最后一位必定为 $0$。

那么我们可以顺着这个思路考虑，从后往前构造这个串。对于最后一位为 $0$ 的情况，显然直接进行 B 操作即可。而对于最后一位为 $1$ 的情况，我们需要先执行一次 A 操作，使其变为 $0$，再执行一次 B 操作，使得最后一位为 $0$。

依此类推，从后往前检查每一个位置，如果当前位置为 $1$，则先执行 A 操作，再执行 B 操作；否则直接执行 B 操作即可。最后再反转整个字符串，即可得到原来的 01 串。

代码实现中可以使用一个变量 $flag$ 来记录上一个位置的值，在循环中判断即可。

时间复杂度为 $O(n)$，可以通过本题。



---

