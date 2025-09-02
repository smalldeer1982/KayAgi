# [GCJ 2014 #1B] The Repeater

## 题目描述

Fegla 和 Omar 每天都喜欢玩游戏。但现在他们已经玩腻了所有的游戏，于是决定自己发明一个新游戏，叫作 **"The Repeater"**（重复者）。

这是一个两人游戏。Fegla 写下 $N$ 个字符串，Omar 的任务是**将所有字符串变得完全相同**（如果可能），并且在此过程中所使用的操作次数要尽量少（也可以为 $0$ 次）。允许的操作有以下两种：

- 从任意一个字符串中，**选择一个字符，并重复它一次**（即在它后面再加上一个相同的字符）。例如，Omar 可以用一次操作把 `"abc"` 变成 `"abbc"`（重复字符 `'b'`）。
- 从任意一个字符串中，**选择两个相邻且相同的字符，并删除其中一个**。例如，Omar 可以用一次操作将 `"abbc"` 变成 `"abc"`（删除一个 `'b'`），但不能将其变成 `"bbc"`。

这两种操作是独立的，没有顺序要求，既不需要操作一之后紧跟操作二，也不要求操作二只能跟在操作一之后。

你的任务是帮助 Omar 胜利：判断是否有可能将这 $N$ 个字符串通过若干次操作变得完全一样；如果可以，求出最少的操作次数。


## 说明/提示

**限制条件**

- $1 \leq T \leq 100$
- 每个字符串的长度不超过 $100$

**小数据集（10 分）**

- 时间限制：$60$ 秒
- $N = 2$

**大数据集（13 分）**

- 时间限制：$120$ 秒
- $2 \leq N \leq 100$

翻译由 ChatGPT-4o 完成。

## 样例 #1

### 输入

```
5
2
mmaw
maw
2
gcj
cj
3
aaabbb
ab
aabb
2
abc
abc
3
aabc
abbc
abcc```

### 输出

```
Case #1: 1
Case #2: Fegla Won
Case #3: 4
Case #4: 0
Case #5: 3```

# 题解

## 作者：__CuSO4__ (赞：3)

### 题解

首先，我们可以将字符串处理成“字符及其连续出现次数”的形式，比如：

- `"mmaw"` 转化为 `('m', 2), ('a', 1), ('w', 1)`。
- `"maw"` 转化为 `('m', 1), ('a', 1), ('w', 1)`。

显然，当这样的元素个数不同，或是字符顺序不同时，无解。

可以发现，在有解的情况下，答案只跟字符连续出现的次数有关。

那么，我们就可以枚举每个字符最终的重复次数，分别算出答案，取最小值即可。

记第 $i$ 个字符串中第 $j$ 个字符连续出现的次数为 $L_{i, j}$, 总共有 $m$ 个不同的字符，则答案为 $\displaystyle\sum_{i=1}^{n} { (\min_{1\le j \le n}(\displaystyle\sum_{k=1}^{n}{|L_{i,j}-L_{i,k}|})) } $。

虽然时间复杂度是 $O(Tn^3)$ 的，但由于 $n$ 和 $T$ 都很小，所以也能过。

### 代码（附注释）
```cpp
#include <iostream>
#include <vector> 
using namespace std;

struct Node { char ch; int l; };

int T, n;
string s;
vector<Node> v[105];//vector可以直接push_back，本题中比较方便 

int main()
{
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
        	v[i].clear();
            cin >> s; s = " " + s;
            for (int j = 1; j < s.size(); j++)
            {
                if (s[j] != s[j-1]) v[i].push_back({s[j], 1});
                else v[i][v[i].size()-1].l++;
            }
        }
        //判断是否有解 
        int cur = v[1].size(); bool f = 0;
        for (int i = 2; i <= n && !f; i++)
        {
        	if (v[i].size() != cur)
        	{
        		printf("Case #%d: Fegla Won\n", t);
        		f = 1; break;
			}
			for (int j = 0; j < cur; j++)
			{
				if (v[1][j].ch != v[i][j].ch)
				{
					printf("Case #%d: Fegla Won\n", t);
        			f = 1; break;
				}
			} 
		}
		if (f) continue;
		//有解，计算答案
		int ans = 0, minn, sum; 
		for (int i = 0; i < cur; i++)
		{
			minn = 1e9;
			for (int j = 1; j <= n; j++)
			{
				sum = 0;
				for (int k = 1; k <= n; k++) sum += abs(v[j][i].l - v[k][i].l);
				minn = min(minn, sum);
			}
			ans += minn;
		}
		printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}
```

---

## 作者：qkj_qwq (赞：3)

## 解题思路
不是，数据这么㵘？直接暴力。

既然题目说是把整个字符串中，一个相同字母的字符串变成任意一个正整数的长度，那么我们可以把连续字母的个数记录下来。若记录过程中，当前串的字母与上一个串的字母配对不上，则无解（因为不能删除这个字母），输出 `Fegla Won`。

接着，对于每一个不同的字母，我们取所有字符串的当前字母的个数的中位数作为标准，对其它字符串进行修改（因为这样能使所有字母的修改次数最少，通过画数轴可证得），累加修改次数的总和即可得到答案。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char c[110][110];
int a[110][110],tp[110];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		cout<<"Case #"<<tt<<": ";
		memset(tp,0,sizeof tp);
		int n;
		bool f=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			string s;
			cin>>s;
			for(int j=0;j<s.size();j++)
				if(s[j]!=c[tp[i]][i])//新字母
				{
					c[++tp[i]][i]=s[j];
					if(i>1&&c[tp[i]][i]!=c[tp[i]][i-1])f=1;//字母不匹配
					a[tp[i]][i]=1;
				}
				else a[tp[i]][i]++;//相同字母
			if(i>1&&tp[i]!=tp[i-1])f=1;//字母种数不匹配
		}
		if(f)cout<<"Fegla Won\n";
		else
		{
			int s=0;
			for(int i=1;i<=tp[1];i++)
			{
				sort(a[i]+1,a[i]+n+1);//排序，得到中位数
				int p=(a[i][(n+1)/2]+a[i][(n+2)/2])/2;//中位数
				for(int j=1;j<=n;j++)
					s+=abs(a[i][j]-p);
			}
			cout<<s<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：llhlhx (赞：2)

# 题意简述
有 $T$ 组数据，每组数据给定 $n$ 个字符串，对于每个字符串，有以下两种操作：

1. 选择一个字符，复制一个相同的字符插入在原字符后面。

2. 选择两个相同的相邻字符，删去其中一个。

判断是否有解。如果有，则输出最小的操作次数，使得 $n$ 个字符串相同。

# 思路

对于上述两种操作，可以发现，字符串中不可能自己凭空出现一个字符，而是必须由其他字符复制而来；字符串中一段最长的且每个字符都相同的子串不可能被删光，因为一个字符必须要有一个相邻且相同的字符，才能将其删去。


于是可以定义一个二维整型数组 $a_{i,j}$，表示第 $i$ 个字符串中第 $j$ 段最长的且每个字符都相同的子串的长度，再定义一个二位 char 数组 $b_{i,j}$，表示组成第 $i$ 个字符串中第 $j$ 段最长的且每个字符都相同的子串的字符。

所以无解当且仅当两个字符串 $s_x$ 和 $s_y$ 中，最长的且每个字符都相同的子串的个数不同，或者 $b_{x,i}$ 和 $b_{y,i}$ 无法一一对应。 

接下来就是有解的情况,考虑对 $n$ 个字符串中第 $j$ 个最长的且每个字符都相同的子串一起进行操作。我们要选出一个基准量 $x$,操作让每个 $a_{i,j} = x(i=1,2, .. ,n)$。

显然最优的 $x$ 为 $a_{i,1...n}$ 的中位数。此时 $ans_j=\overset{n}{\underset{i=1}{\sum}}|x-a_{i,j}|$ 有最小值。设每个字符串中最长的且每个字符都相同的子串的个数是 $m(m\le n)$，则最终答案就是

$$\overset{m}{\underset{j=1}{\sum}}\overset{n}{\underset{i=1}{\sum}}|x-a_{i,j}|$$

时间复杂度 $O(T\sum|s|)$，可以轻松通过。

## $AC$代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int T, n, ans, a[N][N], c[N], top[N];
// top[i]为第i个字符串中最长的且每个字符都相同的子串的段数
char b[N][N];
string s[N];
bool check;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    for (int t = 1; t <= T; t++) {
        memset(top, 0, sizeof(top));
        check = 0;
        ans = 0;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> s[i];
            a[i][++top[i]] = 1;
            b[i][top[i]] = s[i][0];
            for (int j = 1; j < s[i].size(); j++)
                if (s[i][j - 1] == s[i][j])
                    a[i][top[i]]++;
                else {
                    a[i][++top[i]] = 1;
                    b[i][top[i]] = s[i][j];
                }
        }
        for (int i = 2; i <= n; i++) {
            if (top[i - 1] != top[i]) {
                check = 1;
                break;
            }
            for (int j = 1; j <= top[i]; j++)
                if (b[i - 1][j] != b[i][j]) {
                    check = 1;
                    break;
                }
            if (check)
                break;
        }
        if (check) {
            cout << "Case #" << t << ": Fegla Won\n";
            continue;
        }
        for (int i = 1; i <= top[1]; i++) {
            for (int j = 1; j <= n; j++) c[j] = a[j][i];
            sort(c + 1, c + 1 + n);  //求中位数要先排序
            int x = (n + 1) / 2;
            for (int j = 1; j <= n; j++) ans += abs(c[x] - a[j][i]);
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
```

---

## 作者：ziyanlin2013 (赞：1)

# 题解：P13250 [GCJ 2014 #1B] The Repeater

[题目传送门](https://www.luogu.com.cn/problem/P13250)  

# 题面

给定 $n$ 个字符串，可以对每一个字符串做以下操作：

1. 对于任意一个字符，复制一个相同字符在其后面。
2. 对于任意相邻两个相同字符，删去其中一个。

求将 $n$ 个字符串变成相同的最小操作次数。

有 $t$ 组测试。

# 解题思路

一步一步来，先考虑有无解。对于每一段相同的字符，一定可以通过一定次数的操作，将其变为若干个相同字符。于是可以先把这些相同的字符全部改为 $1$ 个，这样如果所有字符串完全一样，那么就是有解。

正确性证明：对于一个最后所有字符串变成的相同串 $s$，形如 $c_1 c_1 c_1 ... c_2 c_2 c_2 ... c_{k-1} c_{k-1} c_{k-1} ... c_k c_k c_k ...$，那么这个串将相邻字符 $c$ 删除只剩下 $1$ 个之后变为 $c_1 c_2 c_3 ... c_{k-1} c_k$，即前面将相同字符段全部改为 $1$ 之后的字符串，所以这个串和答案串可以互相转化，得证。

然后考虑最优解。现在，每一个字符串都通过操作 $2$ 变成了 $c_1 c_2 c_3 ... c_{k-1} c_k$ 的形式。即可以对于每一个 $c_i$ 统计最小操作次数，相加得到答案。

令 $f_{i,j}$ 代表第 $i$ 个字符串字符 $c_j$ 修改前相同字符的个数，例如字符串 $i$ 是 `aabbbc`，修改后是 `abc`，$f_{i, 1} = 2, f_{i, 2} = , f_{i, 3} = 1$。

对于所有 $j = k$ 的 $f_{i, j}$，需要通过操作 $1,2$ 变成相同的值，容易发现操作一可以将 $f_{i, j}$ 加 $1$，操作二可以将 $f_{i, j}$ 减 $1$，假设最后 $f_{i, j}$ 变成的相同值是 $x$，那么字符 $c_j$ 对答案的贡献是：

$$\sum_{i = 1}^{n} |f_{i, j} - x|$$

这是一个经典的绝对值问题，要使贡献最小 $x$ 应该取所有 $f_{i,j}$ 排序后的中位数，不会的可以看 [货仓选址](https://www.luogu.com.cn/problem/P10452) ，这里不给出证明。

下面给出代码，代码中 $f$ 数组使用 $a$ 数组代替。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int t, n, ans;
char c[N][N], d[N][N];
int a[N][N], len[N], cnt[N];
int b[N];
void solve(int T) {
	cin >> n;
	bool flag = 1;
	memset(a, 0, sizeof a);
	for (int i = 1; i <= n; i++) {
		cin >> (c[i] + 1);
		len[i] = strlen(c[i] + 1);
		cnt[i] = 0;
		for (int j = 1; j <= len[i]; j++) {
			if(c[i][j] != c[i][j-1]) {
				d[i][++cnt[i]] = c[i][j];
				a[i][cnt[i]] = 1;
			}
			else a[i][cnt[i]] ++;
		}
	}
	for (int i = 1; i < n; i++) {
		if(cnt[i] != cnt[i+1]) {
			flag = 0;
			break;
		}
		for (int j = 1; j <= cnt[i]; j++) {
			if(d[i][j] != d[i+1][j]) {
				flag = 0;
				break;
			}
		}
	}
	if(!flag) {
		cout << "Case #" << T << ": Fegla Won\n";
		return;
	}
	int ans = 0;
	for (int i = 1; i <= cnt[1]; i++) {
		for (int j = 1; j <= n; j++) b[j] = a[j][i];
		sort(b+1, b+n+1);
		int x = b[(n+1)/2];
		for (int j = 1; j <= n; j++) ans += abs(x - b[j]);
	}
	cout << "Case #" << T << ": "  << ans << '\n';
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> t;
	for (int i = 1; i <= t; i++) solve(i);
	return 0;
}
```

---

## 作者：yuyang0974 (赞：1)

## 思路历程

本蒟蒻第一眼以为是推 dp ，直到看见这两句话：

> 规则一：选择一个字符，并**重复**它一次。
>
> 规则二：选择两个**相邻且相同**的字符，并删除其中一个。

我们先观察题目给出的一个样例：
```
gcj
cj
```
我们可以发现，两个字符串只差了一个字母 `g` 。

那我们能不能~~无中生有~~**凭空添加**一个 `g` 呢？

不行的，因为规则一里面说的是“选择一个字符”，我们得**先选择**出一个 `g` 才能给它复制一份！

那考虑能不能把第一个字符串中的那个 `g` **直接删掉**呢？

也是不行的，因为规则二里面又说了“选择两个相邻且相同的字符”，也就是说，我们不可能在**只剩下一个** `g` 的时候删除它！

哇塞，这个东西好像和字符串内由**连续相同字符**组成的串有关，例如在 `aaayyyhhakk` 中， `aaa` 、 `yyy` 、 `hh` 、 `a` 和 `kk` 都是由连续相同字符组成的串。

那我们不妨将他们类比成一个个**颜色块**，以下是我们推完样例后的发现：

- 每个字符串在题目中的两条规则下操作时，它颜色块的**数目**和**相对位置**永远保持**不变**。
- 两个字符串是可以转化成相同字符串的，当且仅当他们具有**完全一致**的颜色块数目和其分布的相对位置。

好的，我们现在已经知道如何判断 `Fegla Won` 啦。

那么，如何计算最小操作次数呢？

其实，我当时是想到了类比“曼哈顿距离总和的最小值”这个东西，只不过其通常用来描述 $2$ 维，而这里拓展到了 $n$ 维。

我们回顾一下曼哈顿距离（ $n$ 维坐标下）：

> $d(P, Q) = \sum \limits_{i = 1}^{n} \mid p_i - q_i \mid$

其中 $p$ 、 $q$ 是各维度坐标值。

由于曼哈顿距离是各维度坐标值之差的绝对值之和，所以我们常用的方法是：分离各维度坐标，单独计算。

考虑一个有序数列 $x_1 \le x_2 \le x_3 \le \cdots \le x_n$ ，那么其**曼哈顿中位数**必然是该序列的**中位数**（这个应该不用多讲吧，实在不会的话可以~~拷问 deepseek~~ ）

拓展到 $n$ 维的话，只需要对每一维都这么求中位数就行啦

那么就会有人问了：啊这和我们要求的最小操作次数有什么关系呢？

哈哈，我们可以把每一个**颜色块**看作一个**维度**，把其所含**字符个数**看作**坐标值**，然后是不是就变成了我们上面讨论的问题？

因为我们每次修改只会改变 1 个字符的长度，所以我们可以取 1 个字符为单位距离，用曼哈顿距离来类比就可以啦！

呼，我们来总结一下所有步骤吧：

1. 首先对第一个字符串分析，处理出颜色块的数量（类比维度）以及每个颜色块对应的字符，并顺便统计每个颜色块的大小
2. 然后我们挨个分析剩下的所有字符串，实时统计该串的颜色块数量，以及每个颜色块对应的字符，一旦不同于第一个字符串，直接返回 `Fegla Won` 即可。同时，不要忘记统计颜色快大小。
3. 最后，取每种颜色块对应数列的中位数，依次计算曼哈顿距离即可。

有一些容易错的点：

- 千万不要在没输入完字符串就输出 `Fegla Won` 然后 `return` 掉了，不然输入会错行的！
- 千万注意本题特殊的输出格式！

## AC代码（附注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn = 105; // -> 既代表字符串最长长度，又代表最多字符串个数
char s[maxn][maxn]; // -> 存储n个字符串
int siz; // -> 颜色块数量
int len; // -> 字符串长度
char ch[maxn]; // -> 每个颜色块对应的字符
int cnt[maxn][maxn]; // -> n个字符中，每个颜色块的大小(注意这里：cnt[i][j] -> 第“j”个字符串中，第“i”个颜色块的大小；这样设计是为了方便排序找中位数)

void Solve(int uid) { // -> uid代表测试数据组编号
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) scanf("%s", s[i] + 1);
    memset(cnt, 0, sizeof(cnt)); // -> 清空计数数组

    // 开始处理第一个字符串
    len = strlen(s[1] + 1);
    siz = 1;
    ch[1] = s[1][1];
    cnt[1][1] = 1;
    for(int i = 2; i <= len; i ++) {
        if(s[1][i] ^ s[1][i - 1]) { // 出现不同字符了，说明出现了新的颜色块
            ch[++ siz] = s[1][i];
        }
        cnt[siz][1] ++;
    }
    
    // 开始处理后续字符串
    for(int it = 2, tmp; it <= n; it ++) {
        len = strlen(s[it] + 1);
        if(s[it][1] != ch[1]) { //第一个字符都不符合，那肯定不可能了
            printf("Case #%d: Fegla Won\n", uid);
            return;
        }
        tmp = 1; // 用tmp维护该字符串的实时颜色块数目
        cnt[1][it] = 1;
        for(int i = 2; i <= len; i ++) {
            if(s[it][i] ^ s[it][i - 1]) { // 出现不同字符了，说明出现了新的颜色块
                tmp ++;
                if(tmp > siz || s[it][i] != ch[tmp]) { //你的颜色块数目太多了老弟，这不乘哦（bushi
                    printf("Case #%d: Fegla Won\n", uid);
                    return;
                }
            }
            cnt[tmp][it] ++;
        }
        if(tmp < siz) { //颜色块数目就这么点？这不乘哦（bushi
            printf("Case #%d: Fegla Won\n", uid);
            return;
        }
    }
    
    // 开始处理曼哈顿距离
    int mid = (n + 1) >> 1; // -> 注意不是 (n >> 1) ！不然会WA的很惨...
    for(int i = 1; i <= siz; i ++) sort(cnt[i] + 1, cnt[i] + n + 1); // 排个序，更好求中位数（注意这里索引先后顺序的设置，详见line 9）
    int ans = 0;
    for(int i = 1; i <= siz; i ++) {
        for(int j = 1; j <= n; j ++) {
            ans += abs(cnt[i][j] - cnt[i][mid]); // 懒得求和，挨个加起来吧
        }
    }
    printf("Case #%d: %d\n", uid, ans); // 正常输出就行啦
}
int main() {
    int T;
    scanf("%d", &T);
    for(int i = 1; i <= T; i ++) Solve(i);
    return 0;
}
```

---

## 作者：hlb44 (赞：0)

题目大意：

通过两种操作将多个字符串变得完全相同，计算最少操作次数。无解输出 ```Fegla Won```。

思路：

首先，需要将每个字符串转换为“字符序列 + 连续次数”的结构表示。比如字符串 aaabbb 可以分解为 $[ ( a , 3 ) , ( b , 3 ) ]$。

同时，所有字符串能被统一的前提是：它们的字符序列必须完全相同，任何差异都不行。

那怎么计算答案呢？只需对于每个位置，把所有字符串的连续次数调整为同一个值。最优目标值为中位数，答案为各字符串次数与中位数的差值之和。

```cpp
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
vector<pair<char,int>>d(const string&s) {
	vector<pair<char,int>>r;
	if(s.empty())return r;
	char c=s[0];
	int n=1;
	for(int i=1; i<s.size(); ++i)
		if(s[i]==c)n++;
		else {
			r.emplace_back(c,n);
			c=s[i];
			n=1;
		}
	r.emplace_back(c,n);
	return r;
}
int main() {
	int T;
	cin>>T;
	for(int _=1; _<=T; ++_) {
		int N;
		cin>>N;
		vector<string>s(N);
		for(int i=0; i<N; ++i)cin>>s[i];
		vector<vector<pair<char,int>>>v(N);
		for(int i=0; i<N; ++i)v[i]=d(s[i]);
		bool p=1;
		int l=v[0].size();
		for(int i=1; i<N&&p; ++i) {
			if(v[i].size()!=l) {
				p=0;
				break;
			}
			for(int j=0; j<l&&p; ++j)
				if(v[i][j].first!=v[0][j].first)p=0;
		}
		if(!p) {
			cout<<"Case #"<<_<<": Fegla Won\n";
			continue;
		}
		int t=0;
		for(int j=0; j<l; ++j) {
			vector<int>c;
			for(int i=0; i<N; ++i)c.push_back(v[i][j].second);
			sort(c.begin(),c.end());
			int m=c[N/2];
			for(int x:c)t+=abs(x-m);
		}
		cout<<"Case #"<<_<<": "<<t<<"\n";
	}
	return 0;
}

```

---

## 作者：IkillDream (赞：0)

# P13250 题解

## 前言

我今天在机房和同学讨论这道题，有某些菜鸟说这是动态规划，可能有这种写法吧，可能是我没想到，因为我只想到了贪心。

## 思路

首先，我们可以将每个字符串转换为字符及其连续出现次数的序列。例如，字符串 $aaabb$ 会被转换为 $[(a,3),(b,2)]$，然后检查所有字符串的字符序列是否完全相同，如果字符序列不同，直接判定为无法通过操作使所有字符串相同，输出 ```Fegla Won```，接着统计一下字符出现次数，例如，对于字符 $a$ 在三个字符串中的出现次数可能是 $[3,2,4]$，最后计算一下计算最小操作次数就可以了。

## [AC](https://www.luogu.com.cn/record/225063182) 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int cnt[105][105],num[105][105],kkk01[105],kkk02[105];
int main(){
	int t,n;
	cin>>t;
	for(int tt=1;tt<=t;tt++){
		cin>>n;
		string s[105];
		for(int i=0;i<n;i++) cin>>s[i];
		for(int i=0;i<n;i++){
			int len=s[i].size();
			char c=s[i][0];
			int ct=1,pos=0;
			for(int j=1;j<len;j++)
				if(s[i][j]==c) ct++;
				else{
					cnt[i][pos]=c;
					num[i][pos++]=ct;
					c=s[i][j];
					ct=1;
				}
			cnt[i][pos]=c;
			num[i][pos++]=ct;
			kkk01[i]=pos;
		}
		bool ok=1;
		for(int i=1;i<n;i++)
		if(kkk01[i]!=kkk01[0]) {ok=0;break;}
		if(ok)
			for(int i=1;i<n;i++)
				for(int j=0;j<kkk01[0];j++)
					if(cnt[i][j]!=cnt[0][j]){ok=0;break;}
		if(!ok){
			cout<<"Case #"<<tt<<": Fegla Won\n";
			continue;
		}
		int ans=0;
		for(int j=0;j<kkk01[0];j++){
			for(int i=0;i<n;i++) kkk02[i]=num[i][j];
			sort(kkk02,kkk02+n);
			int mid=kkk02[n/2];
			for(int i=0;i<n;i++) ans+=abs(kkk02[i]-mid);
		}
		cout<<"Case #"<<tt<<": "<<ans<<"\n";
	}
	return 0;
}
```

## 后记

新知识：

贪心算法

局部最优 $\to$ 全局最优

每一步都选择当前看起来最好的选项，希望最终结果也是最优的。

但不一定能保证全局最优，只有在特定问题中才成立。

高效但可能不精确

贪心算法通常运行速度快，但不一定能得到真正的最优解（除非问题具有——贪心选择性质）。

无后效性

当前的选择不会影响后续的选择（即过去的选择不会改变未来的可能性）。

推荐题目（从简单到难）：[P3742](https://www.luogu.com.cn/problem/P3742)，[P9749真题](https://www.luogu.com.cn/problem/P9749)，[P11299真题](https://www.luogu.com.cn/problem/P11229)，[P11854真题](https://www.luogu.com.cn/problem/P11854)。

题解制作不容易如果决的我的题解写的好的话可以点个赞吗 qwq。

题解可以抄，但是你要学会哦！

如果题解有写的不好的地方欢迎 AT 我，我会尽力改善。

---

