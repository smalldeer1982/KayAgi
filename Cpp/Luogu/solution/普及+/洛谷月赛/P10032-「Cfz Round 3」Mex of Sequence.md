# 「Cfz Round 3」Mex of Sequence

## 题目描述

**请注意本题特殊的时间限制。**

给定一个长度为 $n$ 的序列 $a$ 和一个整数 $m$。

我们定义一次操作为，**同时**将序列 $a$ 中的**每个**元素 $a_i$ 替换为序列 $a$ 中除 $a_i$ 以外的所有元素的 $\operatorname{mex}$。

你需要求出进行 $m$ 次操作后的序列 $a$。

其中，一个序列的 $\operatorname{mex}$ 为该序列中**未出现过的最小自然数**，例如：

- $\operatorname{mex}\{1,2,3\}=0$；
- $\operatorname{mex}\{0\}=1$；
- $\operatorname{mex}\{1,0,2,4\}=3$；
- $\operatorname{mex}\{2,1,3,0,2\}=4$。

特别地，当序列为空时，该序列的 $\operatorname{mex}$ 为 $0$。 

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组数据，因为 $\operatorname{mex}\{0,1,2\}=3$，$\operatorname{mex}\{1,1,2\}=0$，$\operatorname{mex}\{1,0,2\}=3$，$\operatorname{mex}\{1,0,1\}=2$，所以进行 $1$ 次操作后的序列 $a$ 为 $\{3,0,3,2\}$。

#### 「数据范围」

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有数据，$1 \le T \le 1000$，$1 \le n \le 10^6$，$1 \le m \le 10^9$，$0 \le a_i \le 10^9$，$\sum n \le 10^6$。

**只有你通过本题的所有测试点，你才能获得本题的分数。**

## 样例 #1

### 输入

```
3
4 1
1 0 1 2
4 5
9 9 6 1
3 5
1 3 0```

### 输出

```
3 0 3 2
0 0 0 0
1 2 0```

# 题解

## 作者：Coffee_zzz (赞：15)

我们首先分析一下题目给出的操作。

对于某个元素 $a_i$，如果序列 $a$ 中存在另一个元素 $a_p$ 满足 $a_i=a_p$，那么显然，去掉 $a_i$ 后的序列 $a$ 的 $\operatorname{mex}$ 和原本的序列 $a$ 的 $\operatorname{mex}$ 相等，所以操作后，$a_i$ 会变成原本的序列 $a$ 的 $\operatorname{mex}$。

同时，对于某个元素 $a_j$，若其满足 $a_j$ 大于原本的序列 $a$ 的 $\operatorname{mex}$，那么显然，是否去掉 $a_j$ 对序列 $a$ 的 $\operatorname{mex}$ 没有影响，所以操作后，$a_j$ 也会变成原本的序列 $a$ 的 $\operatorname{mex}$。

我们再来考虑，对于某个元素 $a_k$，若其满足：

- 序列 $a$ 中不存在另一个元素 $a_p$ 满足 $a_k=a_p$；
- $a_k$ 小于原本序列 $a$ 的 $\operatorname{mex}$；

那么，去掉 $a_k$ 之后，序列 $a$ 的 $\operatorname{mex}$ 就会变成 $a_k$，所以操作前后，$a_k$ 的值不变。

于是我们明白了操作前后序列 $a$ 的变化。可以用桶维护，做到以 $\mathcal O(n)$ 的复杂度进行一次操作，那么对于 $m=1$ 的情况，我们直接模拟即可。

我们继续分析。

我们先进行第一次操作，把所有满足序列 $a$ 中存在另一个元素与其相等或其大于序列 $a$ 的 $\operatorname{mex}$ 的元素的值都修改为序列 $a$ 的 $\operatorname{mex}$。

然后我们再进行第二次操作，内容和第一次操作相同。

于是容易证明，此时的序列 $a$ 除最大值外，剩余的元素都满足不存在另一个元素 $a_p$ 与其相等，而且最大值要么等于序列 $a$ 的 $\operatorname{mex}$ 的值加一，要么等于序列 $a$ 的 $\operatorname{mex}$ 的值减一。

我们设序列 $a$ 中的最大值为 $x$。根据我们之前分析的内容，若序列 $a$ 中只有一个元素的值为 $x$，则 $x$ 的值不会再改变；若序列 $a$ 中有多个元素的值为 $x$，我们分两类讨论：

- 若 $x+1$ 等于序列 $a$ 的 $\operatorname{mex}$，则所有值等于 $x$ 的元素的值都会变为 $x+1$，此时新的序列 $a$ 的 $\operatorname{mex}$ 为 $x$；
- 若 $x-1$ 等于序列 $a$ 的 $\operatorname{mex}$，则所有值等于 $x$ 的元素的值都会变为 $x-1$，此时新的序列 $a$ 的 $\operatorname{mex}$ 为 $x$。

可以发现，若序列 $a$ 中有多个元素的值为 $x$，则进行多次操作时，$x$ 的值在一直循环，不断加一、减一，每两次操作的效果可以抵消，于是可以得到：

- 当 $m$ 为偶数时，进行 $m$ 次操作后的序列 $a$ 与进行 $2$ 次操作后的序列 $a$ 相同；
- 当 $m$ 为奇数且 $m\ne 1$ 时，进行 $m$ 次操作后的序列 $a$ 与进行 $3$ 次操作后的序列 $a$ 相同。

那我们直接根据此模拟即可。

```c++
#include <bits/stdc++.h>

using namespace std;
const int N=1e6+5;
int n,m,a[N],cnt[N];
void work(){
	int res=0;
	for(int i=0;i<=n;i++) cnt[i]=0;
	for(int i=1;i<=n;i++) if(a[i]<=n) cnt[a[i]]++;
	for(int i=n;i>=0;i--) if(cnt[i]==0) res=i;
	for(int i=1;i<=n;i++) if(a[i]>res||cnt[a[i]]>1) a[i]=res;
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	work();
	if(m!=1){
		work();
		if(m%2==1) work();
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<(i==n?'\n':' ');
}
signed main(){
	ios::sync_with_stdio(0);
	int T=1;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Loser_Syx (赞：9)

赛时不会 $O(n)$ 求 $\mathrm{mex}$，绷。

首先你手模一堆样例发现你操作完 $1$（或 $2$）次后陷入了一堆不断更迭的循环，之后都是以 $2$ 为一个循环节长度进行更换。

所以你大可先操作两次，然后直接讨论 $m$ 奇偶。  
$m$ 奇数说明还要操作一次，$m$ 偶数说明就是现在的序列了。

然后就开绷了，赛时写了一个 $n \log n$ 的树状数组和线段树求 $\mathrm{mex}$ 求法被卡常了。

你考虑如何 $O(n)$ 求，由于序列中的数只有 $n$ 个，那么 $\mathrm{mex}$ 一定存在于 $[0,n]$ 中，只要统计这个区间里哪些数出现了然后统计次数，最小的没出现的即为答案。之后你再考虑替换，如果这个数大于 $\mathrm{mex}$，说明它一定对 $\mathrm{mex}$ 无用，直接变成 $\mathrm{mex}$。或者小于 $\mathrm{mex}$，这样的话如果它只出现了一次，那么删掉它的话一定 $\mathrm{mex}$ 会是它，否则变成 $\mathrm{mex}$。

绷。

当然 $m=1$ 只需要操作一次。

---

## 作者：SJZ2010 (赞：5)

### 做法

$O(n \log n)$ 求 $\operatorname{mex}$ 做法，但常数很小。

先将 $a$ 排序，求出排序后第一个两个数之间相差 $>1$ 的位置，比如我们发现 $a_i < a_{i+1},a_{i+1}-a_i=2$，那我们记录 $lose=a_i+1$，然后我们将 $a$ 离散化，装进权值数组。

之后我们将 $a$（已经离散化）扫一遍，如果 $a_i$ 只出现一次，那么 $a_i$ 将变为 $\min\{lose,a_i\}$（变为原来的 $a_i$ 与 $lose$ 的最小值），否则 $a_i$ 变成 $lose$。

这样就可以求 $\operatorname{mex}$ 了。

然后我们模拟样例发现如果 $m=1$ 那我们 $\operatorname{mex}$ 一次就行了，否则 $\operatorname{mex}$ 后 $a$ 会循环，我们只要求出第 $2$ 与 $3$ 次的 $\operatorname{mex}$ 然后判断 $m$ 的奇偶性就行了。

### Code

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>

std::vector < int > change(std::vector < int > vec)
{
	int l = vec.size(), i;
	std::vector < int > temp = vec, res(l);
	std::sort(temp.begin(), temp.end());
	temp.erase(std::unique(temp.begin(), temp.end()), temp.end()); // 去重
	std::vector < int > t(temp.size() + 5), mp(t.size() + 5);
	bool flag = false; for (i = 0; i < l; i++) if (vec[i] == 0) { flag = 1; break; } // 没有 0 的话特判，lose=0
	for (i = 0; i < l; i++){
		int aa = std::lower_bound(temp.begin(), temp.end(), vec[i]) - temp.begin();
		mp[aa] = vec[i]; // 最后还要映射会原来的 ai
		vec[i] = aa; // 离散化
		t[vec[i]] ++; // 装进权值数组
	}
	int lose = mp[temp.size() - 1] + 1;
	for (i = 1; i < temp.size(); i++) // 判断第一个不连续的位置
		if (mp[i] - mp[i - 1] > 1)
		{
			lose = mp[i - 1] + 1;
			break;
		}
	if (!flag) lose = 0;
	for (i = 0; i < l; i++) // a -> mex
		if (t[vec[i]] == 1)
		{
			if (mp[vec[i]] < lose)
				res[i] = mp[vec[i]];
			else res[i] = lose;
		} else res[i] = lose;
	return res;
}
void print(std::vector < int > vec) // 输出一个 vector
{
	int i;
	for (i = 0; i < vec.size(); i++) printf("%d ", vec[i]);
	printf("\n");
}

int read()
{
    int res(0), ch(getchar());
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9')
        res = res * 10 + (ch ^ 48), ch = getchar();
    return res;
}

int main()
{
	int T, n, m, i;
	T = read();
	while (T--)
	{
		n = read(), m = read();
		std::vector < int > a(n);
		for (i = 0; i < n; i++) a[i] = read();
		std::vector < int > a_ = change(a);
		if (m == 1) { print(a_); continue; } // 
		a_ = change(a_);
		if (!(m & 1)) { print(a_); continue; } // 偶数
		a_ = change(a_);
		print(a_); // 剩下的就是奇数了，情况就是第 3 次操作后的情况
	}
	return 0;
}
```


---

## 作者：Vct14 (赞：4)

找规律易得从第 $2$ 次操作开始会有循环。证明如下。

分类讨论即可。

- 若每个数都只出现了一次，那么删去某一个数后，数列的 $\operatorname{mex}$ 仍然为这个数。因此数列不变。
- 若某个数出现了两次及以上，设为 $k$ 次，则删去这 $k$ 个数时，每个数都会变为数列的 $\operatorname{mex}$，那么这个数列就没有这个数了，下一次操作时这些数又会变回来。

因此模拟一下 $m\leqslant3$ 的情况，若 $m\ne1$，则答案为第 $m\bmod2+2$ 次操作后的结果。

---

## 作者：Erica_N_Contina (赞：3)

## 思路

一道关于 Mex 的规律题。

Mex 的一个至关重要的点就是序列中是否含有 $0$。所以我们从 $0$ 的数量入手，分类讨论。

- 没有 $0$：这种情况很简单，操作一次后序列全变成 $0$，再操作一次变成全一……如此往复，奇数次操作为全 $0$，偶数次操作为全 $1$，如此。

- 有 $≥2$ 个 $0$：这种情况也很简单。可以想到操作一次后序列全不为 $0$，再操作一次序列全 $0$。然后就和上面一种情况一模一样了。

- 恰好有 $1$ 个 $0$：这种情况是相对复杂一点的。可以想到这个 $0$ 会一直呆在那里，无论操作多少次它还是 $0$。所以我们考虑除去这个 $0$ 之后的子序列。可以发现在两次操作之后又开始了循环。下面给出两组这种情况的模拟。

```Plain Text
0 2 2 1 4 4
0 3 3 1 3 3
0 2 2 1 2 2
0 3 3 1 3 3
```


```Plain Text
1 0 3 3 5
1 0 2 2 4
1 0 3 3 3
1 0 2 2 2
1 0 3 3 3
```


所以我们只需要模拟最多两次 Mex 操作即可。

---

这里给出 $O(n)$ 的 Mex 操作方法：

- 扫描序列，用桶计数，找到最小的未出现的自然数 $mis$。

- 扫描序列，对于 $a_i≤mis$，不做修改；对于 $a_i>mis$，将其改为 $mis$。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define ps second
#define pf first
 
 
#define rd read()
inline int read(){
	int xx=0,ff=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') ff=-1;c=getchar();}
	while(c>='0'&&c<='9') xx=xx*10+(c-'0'),c=getchar();
	return xx*ff;
}
inline void write(int out){
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}
 
 
const int INF=1e9+5;
int MOD=1e9+7;
const int N=3e6+5;

int n,m,a[N],k;
unordered_map<int,int>cnt;

void mex(){
	int mis=0;
	cnt.clear();
	for(int i=1;i<=n;i++){
		if(a[i]<=n){
			cnt[a[i]]++;
		}
	}
	while(cnt.count(mis)){
		mis++;
	}
	for(int i=1;i<=n;i++){
		if(a[i]>mis||cnt[a[i]]>=2){
			a[i]=mis;
		}
	}
}
signed main(){
	int t=rd;
	while(t--){
		n=rd,m=rd;
		for(int i=1;i<=n;i++)a[i]=rd;
		if(m==1)mex();
		else if(m&1){
			for(int i=1;i<=3;i++)mex();
		}else{
			mex();mex();
		}
		for(int i=1;i<=n;i++)cout<<a[i]<<' ';
		cout<<endl;
	}
	return 0;
}

```




---

## 作者：szh_AK_all (赞：3)

有人说这道题不能用桶，我说：这是不可能的！

如果我们要求出一个序列中未出现过的最小自然数，那么，我们肯定要用一个同来记录那些数出现过，那些数没出现过。由于 $a_{i}$ 的值最大为 $10^9$，所以我们需要巧妙的换个角度想一下：一个序列中有 $n$ 个数，那么在 $0$ 到 $n$ 这 $n+1$ 个数里，必然有一个数没有出现。所以，桶的大小应设为 $n$ 的最大值，也即 $10^6$。

我们用一个桶来记录每个小于等于 $n$ 的数的出现的次数，并且还要知道那些数没有出现，还是最小的，也即我们要将一些没出现的数按照升序排序。那么，我们会自然而然地想到堆。

有如上思想后，这道题便很容易解决了。由于操作数 $m$ 的上限为 $10^9$，所以，我们不能单纯地模拟。由于序列的每个数改来改去，它的值终究还是在几个数中来回改变，所以，由经验得：序列在改变多次后，肯定会陷入循环。

证明：当序列进行第一次改变后，在以后的改变中，每个元素要么变成比它大或小的数，而变成比它大或小的数后又会便成原来的数（因为第 $i$ 次改变后的数补充了第 $i-1$ 次序列的未出现最小自然数，而第 $i+1$ 次改变又需要补充第 $i$ 次序列的未出现最小自然数）。

那么，我们只要像算小数的循环节一样，算序列的循环节。为了方便起见，我们将一个序列用字符串表示，那么判断这个序列有没有出现过时便很简单了。

下面给出代码，有很多巧妙的地方还是要在代码中感悟、理解，望大家看懂。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000005];
int tt[1000005];//tt数组为桶
int b[1000005];
string c[1000005];//记录循环

string zhuan(int x) {//将数字转换为字符串，注意字符串的顺序别反了
	string p = "";
	if (x == 0)
		p += '0';
	while (x) {
		p += char(x % 10 + '0');
		x /= 10;
	}
	string ppp = p;
	for (int i = 0, j = p.size() - 1; i < p.size(); i++, j--)
		ppp[j] = p[i];
	return ppp;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, q;
		cin >> n >> q;
		set<int>Q;
		map<string, int>qq;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			if (a[i] <= n)
				tt[a[i]]++;
		}
		for (int i = 0; i <= n; i++)
			if (!tt[i])
				Q.insert(i);//将没出现过的数加入set
		for (int i = 1; i <= q; i++) {
			for (int j = 1; j <= n; j++) {
				if (a[j] <= n) {//如果将a[j]删去，a[j]这个数便没有出现时
					if (tt[a[j]] == 1) {
						int x;
						for (int k : Q) {
							x = k;
							break;
						}
						b[j] = min(x, a[j]);
					} else {
						for (int k : Q) {
							b[j] = k;
							break;
						}
					}
				} else {
					for (int k : Q) {
						b[j] = k;
						break;
					}
				}
			}
			string pp = "";//序列转字符串
			for (int j = 1; j <= n; j++) {
				if (a[j] <= n) {
					tt[a[j]]--;
					if (tt[a[j]] == 0)
						Q.insert(a[j]);
				}
				a[j] = b[j];
				if (a[j] <= n) {
					tt[a[j]]++;
					if (tt[a[j]] == 1)
						Q.erase(a[j]);
				}
				pp += zhuan(a[j]);
				pp += " ";
			}
			if (qq[pp]) {//算循环节
				if (i - qq[pp] == 1)
					cout << c[qq[pp]];
				else if ((q - qq[pp] + 1) % (i - qq[pp]) == 0)
					cout << c[i - 1];
				else
					cout << c[qq[pp] - 1 + (q - qq[pp] + 1) % (i - qq[pp])];
				for (int j = 1; j <= i; j++)
					c[j] = "";
				break;
			}
			qq[pp] = i;
			c[i] = pp;
			if (i == q) {
				cout << pp;
				for (int j = 1; j <= i; j++)
					c[j] = "";
			}
		}
		cout << endl;
		memset(tt, 0, sizeof(tt));
	}
}
```
给个赞吧！
[赛时记录](https://www.luogu.com.cn/record/141590591)

---

## 作者：rnf5114 (赞：3)

显然的，不管 $a$ 数组的元素是什么，$\operatorname{mex}$ 的值一定小于等于 $1000000$，所以我们可以开一个桶，用来记录这个数在 $a$ 数组中出现了几次，第一个出现次数为 $0$ 的数就是我们想要的 $\operatorname{mex}$。

其次，我们稍微枚举一些数据可以发现，数组 $a$ 的变化是存在循环的，循环节的长度一定为 $2$，同时有一些序列进行第一次操作之后并不属于循环节，所以我们只要直接模拟出三次操作后的区间长什么样即可。

同时对于答案的变更，对于第 $i$ 个元素，如果 $a_i < \operatorname{mex}$ 同时它出现的次数只有一次，那么 $a_i$ 不用变，对剩下的情况 $a_i$ 变为 $\operatorname{mex}$，这样做的话复杂度是线性的。

关于只需要枚举 $3$ 次操作的证明：当我们做第一次操作的时候，得到的序列是无法确定值的变化具体大小的，但是之后每去除掉某个元素之后，得到 $\operatorname{mex}$ 是在不断地加 $1$ 或减 $1$ 的，因此构成循环，所以对于任意的 $m$，我们最多只需要枚举 $3$ 次操作即可求出 $m$ 次操作后的所有元素值。


Tips：在上面的统计次数中，如果 $a_i \ge 1000000$ 我们不用管它，直接更新成 $\operatorname{mex}$ 即可。 


# code

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,m,n,a[1000010],b[1000010],c[4][1000010];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		int flag0=0,ans=-1;
        memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]<=1000000)
				b[a[i]]++;
            if(a[i]==0)
			    flag0=1;
		}
		for(int i=0;i<=1000000;i++){
			if(b[i]==0){
				ans=i;
				break;
			}
		}
		if(n==1){
			cout<<0<<endl;
			continue;
		}
		int tmp=0;
		if(flag0==0){
			if(m%2){
				for(int i=1;i<=n;i++){
					cout<<0<<" ";
				}
			}
			else{
				for(int i=1;i<=n;i++){
					cout<<1<<" ";
				}
			}
		}
		else{
			for(int i=1;i<=n;i++)
				c[0][i]=a[i];
			for(int i=1;i<=3;i++){
				for(int j=1;j<=n;j++){
					c[i][j]=c[i-1][j];
				}
				for(int j=1;j<=n;j++){
					if(c[i][j]<ans&&b[c[i][j]]==1){
						c[i][j]=c[i][j];
					}
					else{
						c[i][j]=ans;
					}
				}
				memset(b,0,sizeof(b));
				for(int j=1;j<=n;j++){
					b[c[i][j]]++;
				}
				for(int i=0;i<=1000000;i++){
					if(b[i]==0){
						ans=i;
						break;
					}
				}
			}
			int flag=1;
			for(int i=1;i<=n;i++)
				if(c[1][i]!=c[3][i])
					flag=0;
			if(m==1){
				for(int i=1;i<=n;i++){
					cout<<c[1][i]<<" ";
				}
			}
			else if(m%2==0){
				for(int i=1;i<=n;i++){
					cout<<c[2][i]<<" ";
				}
			}
			else{
				for(int i=1;i<=n;i++){
					cout<<c[3][i]<<" ";
				}
			}
		}
		cout<<endl;
	}
    return 0;
}


/*
       ┏┓　　　┏┓
     ┏┛┻━━━┛┻┓
     ┃　　　　　　　┃
     ┃　　　━　　　┃
     ┃　┳┛　┗┳　┃
     ┃　　　　　　　┃
     ┃　　　┻　　　┃
     ┃　　　　　　　┃
     ┗━┓　　　┏━┛Codes are far away from bugs with the animal protecting
         ┃　　　┃    神兽保佑,代码无bug
         ┃　　　┃
         ┃　　　┗━━━┓
         ┃　　　　　 ┣┓
         ┃　　　　 ┏┛
         ┗┓┓┏━┳┓┏┛
           ┃┫┫　┃┫┫
           ┗┻┛　┗┻┛     ○|￣|_

*/
```


---

## 作者：Mu_leaf (赞：2)

~~赛时这道题打了快 1h。~~

## [思路]：
本题的难点分别可以分为两部分。

### Part 1:
发现 $m \leq 10^9$ 基本可以发现是找周期了，通过~~打表~~可得任意串在第三次操作后会出现循环，那么只需要操作 $(m-2)\%2$ 次就好啦。

### Part 2:

现在难点到了如何 $O(n)$ 求 mex 了。

考虑先求出 $A_i \leq n$ 的 mex，我们暂且将这个数称之为 $p$，因为 mex 的值不可能大于 $n$ 则对于值大于 $n$ 的直接替换 $p$ 就可以了。

现在考虑 $A_i \leq n$ 的如何替换，如果这个序列里仅有这一个数且它比 $p$ 小，那么这个数本身就是除去它以后整个数列的 mex 了。其余情况直接替换成 $p$ 就好啦。

# Code:
-------------

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
inline void read(int &x){
	int f=1;x=0;char c=getchar();
	while(c<'0'|| c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	x=x*f;
}
const int N = 1e6 + 5;
int a[N], n, b[N], tot,vis[N];
int t,m;
signed main(){
	read(t);
	while(t--){
		read(n);read(m);
//		memset(vis,0,sizeof(vis))
		for(int i=0;i<=n+1;i++) vis[i]=0;
		for(int i=1;i<=n;i++){
			read(a[i]);
			if(a[i]<=n)vis[a[i]]++;
		}
		m=(m-2)%2+2;
		int mex=0;
		for(int i=1;i<=m;i++){
			for(int j=0;j<=n+1;j++){
				if(!vis[j]){
					mex=j;//这里的 mex 就是上文提到的 p。
					break;
				}
			}
//			cout << mex << "\n";
			for(int j=1;j<=n;j++){
				if(a[j]>n) b[j]=mex;
				else{
					vis[a[j]]--;
					if(!vis[a[j]]) b[j]=min(a[j],mex);
					else b[j]=mex;
					vis[a[j]]++;
				}
			}
			for(int j=0;j<=n+1;j++) vis[j]=0;
			for(int j=1;j<=n;j++){
				a[j]=b[j];
				if(a[j]<=n)vis[a[j]]++;
			}
			
		}
		for(int i=1;i<=n;i++) cout << a[i] << " \n"[i==n];
	}
	return 0;
}
```


---

## 作者：zxh923 (赞：1)

# P10032 「Cfz Round 3」Mex of Sequence 题解

[题目传送门](https://www.luogu.com.cn/problem/P10032)

### 分析

这道题可以先把样例多算几次，就会发现变换的周期为 $2$，只不过找到开始次数即可。

这里分 $3$ 类情况：

第一种，原序列没有 $0$。

于是我们推出变换 $1$ 次后序列一定全是 $0$，下一次一定全是 $1$，这其实就是循环周期，直接输出即可。

第二种，原序列有 $1$ 个 $0$。

这里可以硬推几次第一个样例，可以发现是从第一次变换开始进行周期为 $2$ 的循环，判断 $m$ 后输出即可。

第三种，原序列的 $0$ 的数量大于等于 $2$。

我们发现第一次变换后序列中没有 $0$，再回到第一种情况即可。

这里还有一个小结论，因为 $n\le10^6$，所以序列中最小没有出现的数一定不超过 $10^6$。

简单的证明 $1$：

反证假设这个数超过 $10^6$，由此可以推出从 $0$ 到 $10^6$ 的每个数都存在，等价于 $n>10^6$，与题目矛盾，由此证明出了这个结论。

简单的证明 $2$：

为什么会有循环呢，这里分两种情况。

第一种有 $0$ 或 $2$ 个以上的 $0$。

$0$ 个非常显然，第一轮全是 $0$，第二轮全是 $1$，然后就循环回去了。

$2$ 个以上时，就算你去掉了 $1$ 个 $0$，也一定还有 $0$，所以你的新序列一定没有 $0$，这就回到了上述情况。

有 $1$ 个 $0$ 时有些复杂，首先如果你把 $0$ 去掉这一位还是 $0$，所以 $0$ 不会变。

于是我们考虑去掉这个 $0$ 序列没有大的影响，它只是保证余下的位置不会变成 $0$，所以又回到了上述情况，开始循环。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
#define N 1000005
using namespace std;
int t,n,m,a[N],cnt[N],ze,fi,ans1[N],ans2[N];
//cnt代表出现次数，ze代表0的个数，fi代表最小未出现的数
void init(){//初始化
	ze=0;
	fi=0;
	memset(cnt,0,sizeof(cnt));
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//读写优化
	cin>>t;
	while(t--){
		init();
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(!a[i])ze++;
			if(a[i]<=1e6)cnt[a[i]]++;
		}
		if(n==1){
			cout<<"0\n";//特判
			continue;
		}
		if(!ze){
			if(m&1)for(int i=1;i<=n;i++)cout<<"0 ";
			else for(int i=1;i<=n;i++)cout<<"1 ";
			cout<<'\n';
			continue;
		}
		for(int i=0;i<=1e6;i++){
			if(!cnt[i]){
				fi=i;//找到最小未出现的数
				break;
			}
		}
		//下面的部分按照分析模拟即可，这里不再注释，记住特判m=1
		if(ze>=2){
			if(m==1){
				for(int i=1;i<=n;i++){
					if(a[i]>1e6){
						cout<<fi<<' ';
					}
					else{
						if(cnt[a[i]]==1)cout<<min(a[i],fi)<<' ';
						else cout<<fi<<' ';
					}
				}
				cout<<'\n';
				continue;
			}
			else if(m&1){
				for(int i=1;i<=n;i++)cout<<"1 ";
			}
			else{
				for(int i=1;i<=n;i++)cout<<"0 ";
			}
			cout<<'\n';
			continue;
		}
		else{
			for(int i=1;i<=n;i++){
				if(a[i]>1e6)ans1[i]=fi;
				else{
					if(cnt[a[i]]==1)ans1[i]=min(a[i],fi);
					else ans1[i]=fi;
				}
			}
			if(m==1){
				for(int i=1;i<=n;i++)cout<<ans1[i]<<' ';
				cout<<'\n';
				continue;
			}
			memset(cnt,0,sizeof(cnt));
			for(int i=1;i<=n;i++){
				if(ans1[i]<=1e6)cnt[ans1[i]]++;
			}
			for(int i=0;i<=1e6;i++){
				if(!cnt[i]){
					fi=i;
					break;
				}
			}
			for(int i=1;i<=n;i++){
				if(ans1[i]>1e6)ans2[i]=fi;
				else{
					if(cnt[ans1[i]]==1)ans2[i]=min(ans1[i],fi);
					else ans2[i]=fi;
				}
			}
			memset(cnt,0,sizeof(cnt));
			for(int i=1;i<=n;i++){
				if(ans2[i]<=1e6)cnt[ans2[i]]++;
			}
			for(int i=0;i<=1e6;i++){
				if(!cnt[i]){
					fi=i;
					break;
				}
			}
			for(int i=1;i<=n;i++){
				if(ans2[i]>=1e6)ans1[i]=fi;
				else{
					if(cnt[ans2[i]]==1)ans1[i]=min(fi,ans2[i]);
					else ans1[i]=fi;
				}
			}
			if(m&1)for(int i=1;i<=n;i++)cout<<ans1[i]<<' ';
			else for(int i=1;i<=n;i++)cout<<ans2[i]<<' ';
			cout<<'\n';
			continue;
		}
	}
	return 0;
}
```


---

## 作者：b1tset (赞：1)

显然，打一份代码模拟题意即可找到规律：任意数列进行两次操作后就会陷入循环。  

### Part 1.证明：

分类讨论，讨论数列中 $0$ 的个数。

- 若数列中**没有** $0$：一次操作后就会全变为 $0$，再一次操作就会全变为  $1$，进入循环。
- 若数列中**只有一个** $0$ ： $0$ 一直不变，剩下数字等同于一个没有  $0$ 的数列，进入循环。
- 若序列中**有大于等于二个** $0$：第一次操作全变得非 $0$，再进行一次操作就全变成 $0$，进入循环。

综上，任意数列进行两次操作后就会陷入循环

所以我们只需要提前进行两次操作即可。若要求的操作数为奇数，则再进行一次操作。注意特判要求只做一次操作的情况。

[549ms](https://www.luogu.com.cn/record/141638227)。  

### Part 2.高效地进行操作

1. 我们先把每一个小于 $n$ 的数统计出来。我们知道，任意一个长度为 $l$ 的数列的 $mex$ 值一定在 $0$ 到 $l$ 之间，所以统计小于 $n$ 的数的个数即可。
1. 用 $O(n)$ 的复杂度求出数列的 $\operatorname{mex}$ 值。
1. 这时开始遍历数组，分三种情况。

- 若该数已经大于原数列的 $\operatorname{mex}$ 值，则数列除去该数后的 $\operatorname{mex}$ 值依然是 原数列的 $\operatorname{mex}$ 值。
- 若该数小于原数列的 $\operatorname{mex}$ 值且在数列中只出现了一次，则数列除去该数后的 $\operatorname{mex}$ 值是该数的值。
- 若该数小于原数列的 $\operatorname{mex}$ 值且在数列中出现了多次，则数列除去该数后的 $\operatorname{mex}$ 值依然是原数列的 $\operatorname{mex}$ 值。

我们就做到了在 $O(n)$ 的时间复杂度进行一次操作！

### code

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, mnx;
int a[1000005], vis[1000005];

void mex() //题目里的一次操作
{
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; i++) //记录每个数的出现次数。
		if (a[i] <= n) //记录从0~n的数即可，无需记到m
			vis[a[i]]++;
	for (int i = 0; i <= n; i++) //最小出现的自然数
        if (!vis[i])
       	{
       		mnx = i;
       		break ;
		}
	
	for (int i = 1; i <= n; i++)
	{
		int x = a[i];
		if (x > mnx) //比最小出现的自然数大
			a[i] = mnx;
		else if (vis[x] == 1) //只出现一次，且比最小出现的自然数小
			a[i] = x;
		else
			a[i] = mnx;
	}
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
    	memset(vis, 0, sizeof vis); //多测要清空。
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++)
        	scanf("%d", &a[i]);
        if (m == 1) //特判
        	mex();
        else
        {
	        mex();
	        mex(); //先进行两次操作
	        if (m & 1) //如果操作数为奇数则再操作一次
	        	mex();
	    }
        
        for (int i = 1; i <= n; i++) //输出
        	printf("%d ", a[i]);
        puts("");
    }
    return 0;
}

/*
不知不觉2024年了..
时间过得很快啊..
祝大家新年快乐！

Fighting & 做最好的自己！

iYW :)
*/
```

---

## 作者：Yuki_Ever (赞：1)

## solve

我们首先分析数列的变化情况。

分类考虑：

1. 当数列中没有 $0$ 时。
容易发现，第一次操作后，所有数字都会变成 $0$，下一次操作后，所有数字都会变成 $1$，之后就会进入循环，周期为 $2$。
1. 当数列中有 $2$ 个及以上 $0$ 时。
第一次变换后，所有数列中的数都将不会是 $0$，于是转变成第 $1$ 种情况，从第二次变换开始以 $2$ 为周期循环。
1. 当数列中只有 $1$ 个 $0$ 时。
显然 $0$ 数字不会变动。除去 $0$ 后考虑其他数字，以上面的思路去考虑，容易发现，同样进入了以 $2$ 为周期的循环。

综上，我们枚举出三次变换，记录下周期内的两个数组，根据 $m$ 判断取哪一个。

对于每次变换，我们记录每个数字在序列中出现的次数，从 $0$ 开始寻找首个出现次数为 $0$ 的数字，记为 $maxk$。然后对每个数一一判断，如果出现次数为 $1$，就取 $maxk$ 和这个数的较小值，否则直接赋值为 $maxk$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
long f[1001626];
long m1[1001626];
long m2[1001626];
int cnt[1001626];
int cnm[1001626];
int cnm2[1001626];
int main(){
	cin>>t;
	while(t--){
		long n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			scanf("%lld",&f[i]);
		}
		memset(cnt,0,sizeof(cnt));
		memset(cnm,0,sizeof(cnm));
		memset(cnm2,0,sizeof(cnm2));
		for(int i=1;i<=n;i++)if(f[i]<1000001)cnt[f[i]]++;
		long maxk;
		for(int i=0;i<=n+1;i++){
			if(cnt[i]==0){maxk=i;break;}
		}
		for(int i=1;i<=n;i++){
			if(f[i]<1000001){
				if(cnt[f[i]]==1) f[i]=min(f[i],maxk);
				else f[i]=maxk;
			}
			else f[i]=maxk;
		}
		if(m==1){
			for(int i=1;i<=n;i++)cout<<f[i]<<" ";
			cout<<endl;continue;
		}
		for(int i=1;i<=n;i++)if(f[i]<1000001)cnm[f[i]]++;
		for(int i=0;i<=n+1;i++)if(cnm[i]==0){maxk=i;break;}
		for(int i=1;i<=n;i++){
			if(f[i]<1000001){
				if(cnm[f[i]]==1)m1[i]=min(f[i],maxk);
				else m1[i]=maxk;
			}
			else m1[i]=maxk;
		}
		for(int i=1;i<=n;i++)if(m1[i]<1000001)cnm2[m1[i]]++;
		for(int i=0;i<=n+1;i++)if(cnm2[i]==0){maxk=i;break;}
		for(int i=1;i<=n;i++){
			if(m1[i]<1000001){
				if(cnm2[m1[i]]==1)m2[i]=min(m1[i],maxk);
				else m2[i]=maxk;
			}
			else m2[i]=maxk;
		}
		if(m%2==1)for(int i=1;i<=n;i++)cout<<m2[i]<<" ";
		else for(int i=1;i<=n;i++)cout<<m1[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：AAA404 (赞：1)

今年最后一篇题解。

题意相当好理解，不做赘述。

观察到 $m \le 10^9$，所以不可能暴力做。

因为 $\sum n \le 10^6$，思考线性做法。

先考虑一次操作怎么快速（指线性）完成。

对于每一个数，操作时判断其与序列的 $\operatorname{mex}$ 的关系，分讨一下：

### 如果当前数仅出现 $1$ 次

- 如果小于 $\operatorname{mex}$，则它是新的 $\operatorname{mex}$（指在删除了这个数的序列中），不变即可。

- 如果大于 $\operatorname{mex}$，那就修改为 $\operatorname{mex}$。

- **不可能等于 $\operatorname{mex}$。**

那么将这个数与序列的 $\operatorname{mex}$ 取 $\min$ 即可。

### 如果当前数出现不止 $1$ 次

那么删去这个数不会对序列的 $\operatorname{mex}$ 计算造成影响，直接赋为 $\operatorname{mex}$。

具体实现：

```cpp
unordered_map<int,int>ma;
void solve()
{
	ma.clear();
	for(int i=1;i<=n;i++)
	ma[a[i]]++;
	int mex=0;
	for(int i=0;i<=n;i++)
	if(ma.find(i)==ma.end()){mex=i;break;}
	for(int i=1;i<=n;i++)
	{
		if(ma[a[i]]==1)a[i]=min(a[i],mex);
		else a[i]=mex;
	}
	return;
}
```
求序列的 $\operatorname{mex}$ 是 $O(n)$ 的，因为至多只会有 $n$ 个数在序列里。

那么为了达到线性，**必须进行常数次操作**。

容易发现，一个序列在满足某些限制的情况下进行操作，其是形成了一个以 $2$ 为周期的循环的（具体可以自行手算一下，找找规律）。

那么我们试图找出这个限制（在本题中）。

例如，对于一个序列：$0, 0, 1, 1$。

一次操作后：$2, 2, 2, 2$。

两次操作后：$0, 0, 0, 0$。

三次操作后：$2, 2, 2, 2$。

四次操作后：$0, 0, 0, 0$。

...

到这里规律已经很明显了：**在一次操作后，继续进行操作会形成以 $2$ 为周期的循环。**

**证明（不那么严谨，感性理解）：** 第一次操作后序列与原序列没什么关联，但是继续操作会发现 $\operatorname{mex}$ 不断在加一、减一反复横跳（这个元素只可能大于 $\operatorname{mex}$ 或者小于 $\operatorname{mex}$ 且只出现一次），因为上面我们推导出**序列的变化是和 $\operatorname{mex}$ 有关的**，所以就会形成以 $2$ 为周期的循环。

于是按照 $m$ 的奇偶性决定操作次数即可，时间复杂度：$O(\sum n)$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+500;
int n,m,a[N],T;
unordered_map<int,int>ma;
void solve()
{
	ma.clear();
	for(int i=1;i<=n;i++)
	ma[a[i]]++;
	int mex=0;
	for(int i=0;i<=n;i++)
	if(ma.find(i)==ma.end()){mex=i;break;}
	for(int i=1;i<=n;i++)
	{
		if(ma[a[i]]==1)a[i]=min(a[i],mex);
		else a[i]=mex;
	}
	return;
}
int main()
{
	clock_t c1=clock();
#ifdef LOCAL
 	freopen("1.in","r",stdin);
 	freopen("1.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
 	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		if(m==1)solve();
		if(m==2)solve(),solve();
		if(m>=3)
		{
			solve(),solve();
			if(m&1)solve();
		}
		for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
		cout<<endl;
	}
#ifdef LOCAL
	cerr<<"Time used:"<<clock()-c1<<"ms";
#endif
 	return 0;
}
```


---

## 作者：I_will_AKIOI (赞：1)

看到数据范围：$m\le 10^9$。怎么可能让你真的操作 $10^9$ 次呢？废话不多说，打个表一探究竟。测下第一组数据，操作五次，得到答案：

```
3 0 3 2
1 0 1 1
2 0 2 2
1 0 1 1
2 0 2 2
```

猜测从第二次操作开始，会出现循环节，长度为 $2$。

若序列中没有 $0$，则操作一次后所有数都会归零，然后在 $01$ 直接循环。

若只有一个 $0$，则这个 $0$ 永远不变，相当于这个序列中去掉了这个 $0$，然后就这样递归考虑其他数字。也会出现长度为 $2$ 的循环。

若 $0$ 更多时，经过一次操作后 $0$ 都不见了，然后就会变成第一种情况 $01$ 循环。说明我们的猜测是正确的。

然后我们考虑到底操作几次。首先当 $m\le2$ 时，直接操作就行。否则当 $m$ 为偶数，就操作 $2$ 次，是奇数就操作 $3$ 次。**若操作 $1$ 次，可能会出现操作 $1$ 次与 $3$ 次的序列不同的情况。**

然后，就得求 $\operatorname{mex}$ 了。

最简单的方法可以参照打表程序，开一个 map，命名为 $vis$，存每个数出现的数量。然后假装去掉一个数，从 $0$ 开始依次访问 $vis$，直到一个数不存在为止。由于 $\operatorname{mex}$ 最大为 $n$，所以这种方法进行一次操作的复杂度最坏是 $O(n^2 \log n)$，必定 TLE。

考虑改进算法。每次操作只会去掉一个数，我们可以考虑从原序列中推出去掉一个数后的 $\operatorname{mex}$，这时候就得请出我们的分类讨论。设去掉的数为 $x$。

若 $x<\operatorname{mex}$，则变换后的 $\operatorname{mex}=x$。

否则，$\operatorname{mex}$ 不变。

所以我们先预处理出原序列的 $\operatorname{mex}$，再循环求解即可。最后别忘了重置 $vis$ 数组，于是这题就迎刃以解咯。**记得开 unordered_map，不然会 T。**

当然，我们前面提到 $\operatorname{mex}$ 最大为 $n$，所以只需要存下 $[0,n]$ 的整数即可，其他的可以扔掉，将复杂度优化为 $O(n)$。


建议本题评绿。本题与 C 题同为黄题，但 C 题通过率比 D 大，并且思考时间、代码实现难度均比 D 题小。
 
```
#include<bits/stdc++.h>
using namespace std;
int t,n,m,mex,a[1000005],vis[1000005];
int main()
{
  ios::sync_with_stdio(0);
  cin>>t;
  while(t--)
  {
  	memset(vis,0,sizeof(vis));
  	cin>>n>>m;
  	for(int i=1;i<=n;i++)
  	{
  	  cin>>a[i];
  	  if(a[i]<=1000000) vis[a[i]]++;
  	}
  	m=(m==1)?1:m%2+2;//求出最少操作次数
  	for(int i=1;i<=m;i++)
  	{
  	  int j=0;
  	  while(1)
  	  {
  	    if(vis[j]==0) {mex=j;break;}
	    j++;
	  }//求mex
  	  for(int j=1;j<=n;j++) if(!(a[j]<mex&&vis[a[j]]==1)) a[j]=mex;//推出去掉a[j]后的mex
	  memset(vis,0,sizeof(vis));
	  for(int j=1;j<=n;j++) vis[a[j]]++;//重置vis数组
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	cout<<"\n";
  }
  return 0;
}
```

---

## 作者：Wei_Han (赞：1)

**注意：本题卡 $O(n\log n)$ 做法**

## 思路

对于原序列，看不出什么规律，所以先对其手动进行几次操作。

会发现，此时序列中一定存在 $0$ , 对于 $0$ 的个数分类讨论：

$1.$ 当仅有一个 $0$ 时，如样例第 $1$ 组和第 $3$ 组 ，$0$ 将不再变化。

$2.$ 当存在大于一个 $0$ 时，如样例第 $2$ 组，所有 $0$ 将会以 $0~1~0~1$ 的规律变化。

再多算几个数字就能发现，假定此数为 $x$，(第一个个数大于 $1$ 的，且只会有一个)

当 $x$ 的个数大于 $1$ 时，所有大于等于 $x$ 的数都会以 $x+1$ , $x$ 的规律变化。

之后就愉快的按照思路写代码就可以了。

注意 ， 如果原序列已经没有超过一个的数或者只有最大数超过一个，可以直接进行变换的，需要特判 $+1$ 。（很离谱，但我的代码需要）

**注：如果你使用了 $O(n \log n)$ 的算法，将会被卡掉，所以请使用二维数组维护。 (详情见代码)**

## 代码

```cpp
/*
2024/1/1 P10032
码风有点烂，见谅啦 qwq 
*/ 
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ; i -- )
using namespace std;
typedef int ll;
typedef double db;
const ll N=1e6+5;
void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll t,n,m,a[N],b[N];
ll vis[6][1000005];//维护数字个数的二维数组 ， 第一维是维护下面提前 5 次变换用的 
int main(){
	read(t);
	while(t--){
		read(n),read(m);
		fo(0,j,5) fo(0,i,n+1) vis[j][i]=0;//注意预处理到 n+1 即可，否则会TLE 
		ll maxn=-1;
		fo(1,i,n){
			read(a[i]);
			maxn=max(maxn,a[i]);
			if(a[i]<=n) vis[0][a[i]]++;
		}
		ll flag=0,maxx=0,ans=0;
		while(vis[0][maxx]) maxx++;
		if(maxx>maxn){
			flag=1;
		}
		fo(1,i,n){
			if(a[i]>maxx) a[i]=maxx;
			else{
				if(vis[0][a[i]]-1!=0) a[i]=maxx;
			}
			b[i]=a[i];
		}
		m--;
		if(m<=0){fo(1,i,n) wr(b[i]),pp;pr;continue;}
		fo(1,k,min(5,m)){
			fo(1,i,n) vis[k][b[i]]++; 
			maxx=0;
			while(vis[k][maxx]) maxx++;
			fo(1,i,n){
				if(b[i]>maxx) b[i]=maxx;
				else{
					if(vis[k][b[i]]-1!=0) b[i]=maxx;
				}
				a[i]=b[i];
			}
			fo(1,i,n) b[i]=a[i];
		}
		if(m<=5){
			fo(1,i,n) wr(b[i]),pp;
			pr;
			continue;
		}
		m-=5;
		fo(0,i,n+1) vis[0][i]=0;//此处同上 
		fo(1,i,n) vis[0][b[i]]++;
		while(vis[0][ans]==1) ans++;
		ll op=ans;
		if(!(m&1)) op++;
		if(flag) op++;
		fo(1,i,n){
			if(b[i]>=ans) wr(op),pp;
			else wr(b[i]),pp;
		}
		pr;
	}
	return 0;
}
``````

---

## 作者：AK_heaven (赞：1)

## 解题思路如下：

1. 计算 $\operatorname{Mex}$ 的方法，set 维护

2. 找规律优化时间复杂度

## 一、计算 $\operatorname{Mex}$ 并正确的建桶

我们需要在一个非负整数序列当中排序，取最小的除开 $a _i$ 外的非负整数，考虑用 STL 当中的 set 来解决。

定义 set 中值的含义：所有在 $\operatorname{Mex}$ 选择范围内的数字。

我们可以把整个初始序列的数字装入对应的桶当中，然后从小到大遍历，遍历到的所有空桶都将其对应的数字加入到 set 中进行维护。

由于 set 中的元素默认为从小到大排序。所以，set 的第一个元素便是我们需要的 $\operatorname{Mex}$。

注意，因为 $0 \le a_i \le 10^9$，所以在建桶的时候需要处理它。

第一种方法是选用 map 来离散化，需要使用 unordered_map 才可以过。

第二种方法是可以证明 $0 \le \operatorname{Mex} \le n$，所以可以把大于 $n$ 的数字全部过滤掉，不进行装桶，时空比 map 更为优秀。

## 二、找规律优化时间复杂度

如果用上述的方法来进行模拟，$ m = 10$ 的时候就会直接爆掉，遑论 $ m = 10^9 $ 的情况。

这个时候我们就可以通过**打表**可以得到规律。

我们会得到一个结论：只有 $1 \sim 3$ 次操作是不重复的。

除此，后面的操作只会不断的在**奇数次**情况和**偶数次**情况之间变化。

证明如下：

由于 $\operatorname{Mex}$ 取序列中不存在的所有非负数中最小数的性质，当我们做第一次操作的时候，得到的序列中要不就是 $\operatorname{Mex}$ 或者是它本身。如果第一次 $\operatorname{Mex}$ 就取到了 $0$，那么序列就全部清为 $0$ 了。而如果 $\operatorname{Mex}$ 大于 $0$，那么第二次操作过后，第一次被修改过的数就会就会等于 $1$ 或 $0$。第三次操作只是在第二次操作上进行了变化。之后每去除掉某个元素之后，得到的 $\operatorname{Mex}$ 值不过是不断 $+1$ 或 $-1$，所以可以抵消，证毕。

所以，就可以将 $ 3 \le m$ 的情况归纳为 $ m = 2$ 
或 $ m = 3$ 两种情况。
 
 时间复杂度：$O(n \times T)$ 开 O2 可以过。
 
 赛时代码如下：
 
 ```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10; 
set<int> st;
int mp[maxn];
ll n, T, m, a[maxn];

void init() {
	for(int i = 1; i <= n; i++)
	  if(a[i] <= n) mp[a[i]]++;
	for(int i = 0; i <= n; i++)
	  if(!mp[i]) st.insert(i);
}

void work() {
	int f = -1, k;
	for(int i = 1; i <= n; i++, f = -1) {
		if(a[i] <= n) mp[a[i]]--; k = a[i];
		if(a[i] <= n && mp[a[i]] == 0) f = a[i], st.insert(a[i]);
		a[i] = *st.begin();
		if(f != -1) st.erase(f);
		if(k <= n) mp[k]++;
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while(T--) {
		memset(mp, 0, sizeof(mp)); st.clear();
		cin >> n >> m;
		for(int i = 1; i <= n; i++)
		  cin >> a[i];
		if(m >= 3) m = (m&1)?3:2;
		for(int i = 1; i <= m; i++) {
			init();
			work();
			memset(mp, 0, sizeof(mp));
			st.clear();
		}
		for(int j = 1; j <= n; j++)
		  cout << a[j] << ' ';
		cout << '\n';
	}
	return 0;
}
```
欢迎大家来我的博客玩，也欢迎大家能够优化我的蒟蒻代码。



---

## 作者：MicroSun (赞：0)

暴力/打表/手玩可以发现，循环从第 $2$ 次操作开始，循环节长度为 $2$。

这是为啥呢？简单证明如下：

第 $1$ 次操作毫无规律可言，简单模拟即可。

从第 $2$ 次操作开始，对于每个数 $i$，记其出现次数为 $b_i$。

1. $b_i=1$，因为已经进行了一次操作，删掉 $i$ 后，数列中会存在 $[0,i)$ 的所有数。所以其 $\operatorname{mex}$ 为 $i$。综上所述，当 $b_i=1$ 时，操作不会改变该数。

1. $b_i\ge2$，当删掉这个数的时候，不会影响该数列。$i$ 将变成该数列的 $\operatorname{mex}$。但是，所有 $i$ 都变成了 $\operatorname{mex}$，数组内就空出了一个位子，在下一次操作时，就会将所有 $i$ 转移回来。综上所述，当 $i\ge2$ 时，出现了循环节长度为 $2$ 的循环。

模拟上述内容即可。

```cpp
// Problem: P10032 「Cfz Round 3」Mex of Sequence
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb emplace_back
#define fst first
#define scd second
#define me(a,x) memset((a),(x),sizeof(a));
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using pii=pair<int,int>;
using ll=long long;
using db=double;

void exgcd(ll a,ll b,ll &x,ll &y){
	if(!b) x=1,y=0;
	else exgcd(b,a%b,y,x),y-=a/b*x;
}
void chmax(ll &a,ll b){a=max(a,b);}
void chmin(ll &a,ll b){a=min(a,b);}

const int maxn=1e6+10;

ll a[maxn],b[maxn],n,m;
void change(){
	rep(i,0,n) b[i]=0;
	rep(i,1,n) 
		if(a[i]<=n) b[a[i]]++;
	ll now=0;
	dep(i,n,0) if(!b[i]) now=i;
	rep(i,1,n){
		if(a[i]>now||b[a[i]]>1) a[i]=now;
	}
}
void solve(){
	cin>>n>>m;
	rep(i,1,n) cin>>a[i];
	change();
	if(m>1){
		change();
		if(m&1) change();
	}
	rep(i,1,n) cout<<a[i]<<' ';
	cout<<endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：indream (赞：0)

## P10032 「Cfz Round 3」Mex of Sequence 题解
[P10032](https://www.luogu.com.cn/problem/P10032) | [AC](https://www.luogu.com.cn/record/141622780)
### 思路
显然，一个序列中，除 $a_i$ 外所有元素的 $\operatorname{mex}$ 为自己本身（当本身小于原序列 $\operatorname{mex}$ 且序列中只有一个数为 $a_i$），否则该值应为原序列 $\operatorname{mex}$。

其次，打表发现，序列变化似乎有周期性规律：接下来讨论序列中 $0$ 的个数。

- 序列中没有 $0$：一次操作后全变为 $0$，再一次操作全变为 $1$，如此循环。
- 序列中有至少 $2$ 个 $0$：一次操作全变得不为 $0$，再一次操作全都是 $0$，接下来和上面一种情况相同。
- 序列中有 $1$ 个 $0$：显然 $0$ 一直不变，剩下数字以类似的方式“递归”讨论，亦可发现其从第二次开始进入了每两次一循环。

总结一下，就是先模拟一次，只要 $m\ne1$ 就再枚举 $m \bmod 2+1$ 次操作。~~似乎打个表发现得更快。~~


于是这道题基本结束了。我们要做的就是 $O(n)$ 求 $\operatorname{mex}$。

这里用**桶**的思路做，显然，$\operatorname{mex}<n$，所以桶只要存 $<n$ 的数即可。之后从 $n$ 减少枚举 $cnt_i$，最后一个满足 $cnt_i=0$ 的 $i$ 即为原序列的 $\operatorname{mex}$。求一次操作仅需按开始时的结论模拟。**记得清空 $cnt$ 数组！**

---

## 作者：MoonCake2011 (赞：0)

我们打表发现，第二次所生成的内容一定会在第 $2n$ 次出现，第三次所生成的内容一定会在第 $2n+1$ 次出现。

因为我们可以分类讨论。

1. 如果序列中没有 $0$，那么序列就会 $0,1$ 交替的变换。

2. 如果序列中有一个 $0$，序列会交替变换。我们把 $0$ 去掉，将其它数都减 $1$，继续递归，发现递归到最后，也会出现循环节。

3. 如果序列中有多个 $0$，序列就会转化为 $1$ 的情况。

于是操作只用执行三次，我们来想想怎么让每次操作做到 $O(n)$ 或 $O(n \log n)$。

先想怎么求出删去一个数的 $\text{mex}$。

要么是整个数列的 $\text{mex}$，要么是自己这个数。

我们用 `map` 记录，对做一次操作写一个函数。

```cpp
inline void T(){
	map<int,int>mp;
	for(int i=1;i<=n;i++) mp[a[i]]++;
	map<int,int>::iterator iter=mp.begin();
	int mex=0;
	while(mp.count(mex)) mex=iter->first+1,iter++; 
	for(int i=1;i<=n;i++){
		int u=a[i];
		if(mp[u]==1) a[i]=min(mex,u);
		else a[i]=mex;
	}
	m--;
}
```

于是就能很轻松的写出整个程序了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[1000010],b[1000010];
inline void T(){
	map<int,int>mp;
	for(int i=1;i<=n;i++) mp[a[i]]++;
	map<int,int>::iterator iter=mp.begin();
	int mex=0;
	while(mp.count(mex)) mex=iter->first+1,iter++; 
	for(int i=1;i<=n;i++){
		int u=a[i];
		if(mp[u]==1) a[i]=min(mex,u);
		else a[i]=mex;
	}
	m--;
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	//
	T();
	if(m==0){
		for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		cout<<"\n";
		return;
	}
	//
	T();
	//
	if(m==0){
		for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		cout<<"\n";
		return;
	}
	for(int i=1;i<=n;i++) b[i]=a[i];
	//
	T();
	//
	if(m%2==0){
		for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		cout<<"\n";
		return;
	}
	else{
		for(int i=1;i<=n;i++) cout<<b[i]<<" ";
		cout<<"\n";
		return;
	}
}
int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

以上是我赛时代码。

可是，没料到第 6 个测试点数据卡太严了，`map` 常数太大了，根本过不了。

于是赛时这题我一分没得。

赛后我们又想到，一个长度为 $n$ 的数列的 $\text{mex}$ 不会超过 $n+1$。

于是我们可以用桶记录小于等于 $n$ 的数，再去用桶求 $\text{mex}$。

如果 $a_i>n$ 的话，那么它会被改变为整个数列的 $\text{mex}$。

剩余的就与用 `map` 写的 `T` 函数思路一样了。

`T` 函数代码。

```cpp
inline void T(){
	for(int i=0;i<=n;i++) mp[i]=0;
	for(int i=1;i<=n;i++) if(a[i]<=n) mp[a[i]]++;
	int mex=0;
	while(mp[mex]) mex++;
	for(int i=1;i<=n;i++){
		int u=a[i];
		if(u>n) a[i]=mex;
		else if(mp[u]==1) a[i]=min(mex,u);
		else a[i]=mex;
	}
	m--;
}
```

整个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[1000010],b[1000010],mp[1000010];
inline void T(){
	for(int i=0;i<=n;i++) mp[i]=0;
	for(int i=1;i<=n;i++) if(a[i]<=n) mp[a[i]]++;
	int mex=0;
	while(mp[mex]) mex++;
	for(int i=1;i<=n;i++){
		int u=a[i];
		if(u>n) a[i]=mex;
		else if(mp[u]==1) a[i]=min(mex,u);
		else a[i]=mex;
	}
	m--;
}
inline void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	T();
	if(m==0){
		for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		cout<<"\n";
		return;
	}
	T();
	if(m==0){
		for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		cout<<"\n";
		return;
	}
	for(int i=1;i<=n;i++) b[i]=a[i];
	T(); 
	if(m%2==0){
		for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		cout<<"\n";
		return;
	}
	else{
		for(int i=1;i<=n;i++) cout<<b[i]<<" ";
		cout<<"\n";
		return;
	}
	return;
}
signed main() {
	ios::sync_with_stdio(0); 
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：modfish_ (赞：0)

## 思路
从 $0$ 的数量下手。

如果这个序列中没有 $0$，则在进行一次操作后，所有元素全部变成 $0$。

如果这个序列中有超过 $1$ 个 $0$，则进行一次操作后，序列中不再存在 $0$，成为第一种情况。

所以：若序列中无 $0$，则序列在进行 $1$ 次操作后，将以 $2$ 次操作为周期循环变换；若有超过 $1$ 个 $0$，则序列在进行 $2$ 次操作后，再以 $2$ 次操作为周期循环变换。

那如果只有一个 $0$ 呢？

容易发现此时这个 $0$ 永远不会变。再以类似的策略考虑 $1$，会发现，除去那个 $0$，其余元素的变化规律与前面是相似的。

得出结论：

对于第一个出现次数不为 $1$ 的元素 $x$，若其出现次数为 $0$，则序列在进行 $1$ 次操作后，将以 $2$ 次操作为周期循环变换；否则，序列在进行 $2$ 次操作后，再以 $2$ 次操作为周期循环变换。

所以预处理出序列变化前 $4$ 次的状态即可。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 5;

int a[maxn][5], tag[maxn];

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i ++){
			scanf("%d", &a[i][0]);
			if(a[i][0] <= n) tag[a[i][0]] ++;
		}
		int x = 0;
		while(tag[x] == 1) x ++;
		for(int k = 1; k <= 4; k ++){
			int mex = 0;
			while(tag[mex] > 0) mex ++;
			for(int i = 1; i <= n; i ++){
				a[i][k] = mex;
				if(a[i][k - 1] <= n && tag[a[i][k - 1]] == 1) a[i][k] = min(mex, a[i][k - 1]);
			}
			for(int i = 0; i <= n; i ++) tag[i] = 0;
			for(int i = 1; i <= n; i ++){
				if(a[i][k] <= n) tag[a[i][k]] ++;
			}
		}
		if(a[x] == 0){
			for(int i = 1; i <= n; i ++){
				printf("%d ", a[i][m % 2 == 0 ? 2 : 1]);
			}
		}else{
			for(int i = 1; i <= n; i ++){
				if(m <= 2) printf("%d ", a[i][m]);
				else printf("%d ", a[i][m % 2 + 2]);
			}
		}
		printf("\n");
		for(int i = 0; i <= n; i ++) tag[i] = 0;
	}
	return 0;
}
```


---

