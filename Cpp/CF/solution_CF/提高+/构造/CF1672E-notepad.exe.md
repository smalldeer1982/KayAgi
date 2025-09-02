# notepad.exe

## 题目描述

This is an interactive problem.

There are $ n $ words in a text editor. The $ i $ -th word has length $ l_i $ ( $ 1 \leq l_i \leq 2000 $ ). The array $ l $ is hidden and only known by the grader.

The text editor displays words in lines, splitting each two words in a line with at least one space. Note that a line does not have to end with a space. Let the height of the text editor refer to the number of lines used. For the given width, the text editor will display words in such a way that the height is minimized.

More formally, suppose that the text editor has width $ w $ . Let $ a $ be an array of length $ k+1 $ where $ 1=a_1 < a_2 < \ldots < a_{k+1}=n+1 $ . $ a $ is a valid array if for all $ 1 \leq i \leq k $ , $ l_{a_i}+1+l_{a_i+1}+1+\ldots+1+l_{a_{i+1}-1} \leq w $ . Then the height of the text editor is the minimum $ k $ over all valid arrays.

Note that if $ w < \max(l_i) $ , the text editor cannot display all the words properly and will crash, and the height of the text editor will be $ 0 $ instead.

You can ask $ n+30 $ queries. In one query, you provide a width $ w $ . Then, the grader will return the height $ h_w $ of the text editor when its width is $ w $ .

Find the minimum area of the text editor, which is the minimum value of $ w \cdot h_w $ over all $ w $ for which $ h_w \neq 0 $ .

The lengths are fixed in advance. In other words, the interactor is not adaptive.

## 说明/提示

In the first test case, the words are $ \{\texttt{glory},\texttt{to},\texttt{ukraine},\texttt{and},\texttt{anton},\texttt{trygub}\} $ , so $ l=\{5,2,7,3,5,6\} $ .

If $ w=1 $ , then the text editor is not able to display all words properly and will crash. The height of the text editor is $ h_1=0 $ , so the grader will return $ 0 $ .

If $ w=9 $ , then a possible way that the words will be displayed on the text editor is:

- $ \texttt{glory__to} $
- $ \texttt{ukraine__} $
- $ \texttt{and_anton} $
- $ \texttt{__trygub_} $

The height of the text editor is $ h_{9}=4 $ , so the grader will return $ 4 $ .

If $ w=16 $ , then a possible way that the words will be displayed on the text editor is:

- $ \texttt{glory_to_ukraine} $
- $ \texttt{and_anton_trygub} $

The height of the text editor is $ h_{16}=2 $ , so the grader will return $ 2 $ .

We have somehow figured out that the minimum area of the text editor is $ 32 $ , so we answer it.

## 样例 #1

### 输入

```
6

0

4

2```

### 输出

```
? 1

? 9

? 16

! 32```

# 题解

## 作者：Rushroom (赞：3)



[题目传送门](https://codeforces.com/contest/1672/problem/E)

> 交互题。
>
> 文本编辑器中有 $n$ 个单词，第 $i$ 个长度为 $l_i$。$l$ 仅对测评机可见。
>
> 文本编辑器一行一行展示文本，以空格分开相邻的两个单词，但是行末不一定有空格，即单词可以直接作为某一行的末尾。对于给定的屏幕宽度 $w$，高度 $h$ 为展示文本最少需要的行数。
>
> 如果 $w \le \max(l_i)$，那么文本编辑器将崩溃， $h = 0$ .
>
> 最多可以询问 $n + 30$ 次。每次询问宽度 $w$ 。测评机将返回 $h$。
>
> 输出最小面积，即 $min(w\times h_w)$。
>
> $n,l_i \le 2000$

良题。

看到 $n+30$，可以猜到询问是二分+ $O(n)$ 枚举。

先二分出最小的 $w=w_1$ 满足 $h=1$，即把所有单词放在一行的长度。

此时如果有更优的 $h$，最小宽度为 $w_h$，那么一定有 $w_h \le \left\lfloor \dfrac{w_1}{h}\right \rfloor$。

对比 $h$ 行与 $1$ 行两种方案，考虑最优的情况，$h$ 行每行末尾都没有空格，那么就在 $1\sim h-1$ 行的末尾各省下了一个空格，共 $h-1$ 个，所以又有 $w_h\cdot h \ge w_1-h+1$，进一步，$w_h \ge \dfrac{w1-h+1}{h} \ge \left\lfloor \dfrac{w_1}{h}\right \rfloor$。

所以可以得到 $w_h=\left\lfloor \dfrac{w_1}{h}\right \rfloor$。

接下来，我们就可以枚举 $2 \le h \le n$，然后对 $w=\left\lfloor \dfrac{w_1}{h}\right \rfloor$ 询问，用 $w\cdot h'$ 更新答案（$h'$ 为测评机返回的数）。

## Code

```cpp
ll n, w, a, ans;
void solve() {
    cin >> n;
    ll l = 1, r = 2000 * 3000, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        cout << "? " << mid << endl;
        cout.flush();
        cin >> a;
        if (a == 1)w = mid, r = mid - 1;
        else l = mid + 1;
    }
    ans = w;
    repp(i, n) {
        cout << "? " << w / i << endl;
        cout.flush();
        cin >> a;
        if (a)ans = min(ans, w / i * a);
    }
    cout << "! " << ans << endl;
    cout.flush();
}
```



---

## 作者：Mirasycle (赞：1)

询问的是宽度，而宽带范围太大我们无法直接枚举宽度找到最小行数。

于是暴力就是枚举所有可能的行数此时对应的 $w$ 是在一个区间内的，二分一下 $w$ 进行询问看看返回值是不是当前枚举的行，这样子的复杂度是 $O(n\log n)$ 的。

观察数据规模大概是在 $O(n+\log n)$ 级别的。

我们可以通过一次二分，找到全都放在第一行所需要的长度记为 $w_1$。我们枚举行数 $h$，发现放 $h$ 行如果比 $1$ 行更优的话，那么 $h$ 的长度 $w_h\le \lfloor\dfrac{w_1}{h} \rfloor$。我们又知道放 $h$ 行最多能节省的是单词之间的空格 $h-1$ 个，即 $h\times w_h\ge w_1-h+1$，所以 $w_h$ 只能取 $\lfloor\dfrac{w_1}{h} \rfloor$，对于每个 $h$ 询问 $\lfloor\dfrac{w_1}{h} \rfloor$，如果返回值是 $h$ 就去更新答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int query(int x){
	cout<<"? "<<x<<endl;
	int y; cin>>y; return y;
}
int main(){
	int n; cin>>n;
	int l=1,r=4e6;
	while(l<r){
		int mid=(l+r)>>1;
		if(query(mid)==1) r=mid;
		else l=mid+1;
	}
	int ans=l;
	for(int i=2;i<=n;i++){
		int x=l/i; if(query(x)==i) ans=min(ans,x*i);
	}
	cout<<"! "<<ans;
	return 0;
} 
```

---

## 作者：JS_TZ_ZHR (赞：1)

## 题意：

交互题。每次你可以询问一个文本每行长度为 $x$ 时要花多少行才能装下一个有 $n$ 个单词的句子。单词占的长度为它本身的长度，单词之间有占 $1$ 长度的空格（换行不算），一个单词不能换行写。一个文本所占的面积为它的每行长度乘行数。问能装下这个句子的文本面积最小多少。

## 题解：

看到 $n+30$ 的交互次数限制自然想到 $n+\log n$ 次交互。

先考虑二分求出只用一行的最短长度 $L$。

然后发现如果 $k$ 行更优秀的话，用的长度最多为 $\lfloor\frac{L}{k}\rfloor$。而又因为 $k$ 行比 $1$ 行最多节省 $k-1$ 个空格的空间，所以 $\lfloor\frac{L}{k}\rfloor -1$ 的每行长度对于 $k$ 行是不可能的。所以这时枚举 $2$ 到 $n$ 的每个行数 $k$，求每行长 $\lfloor\frac{L}{k}\rfloor$ 时的最少行数并更新答案即可。

```cpp
#include<bits/stdc++.h> 
#define int long long
#define N 1000005
using namespace std;
int n,l,r,ans,tmp,len;
void solve(int sum){
	ans=sum;
	for(int i=2;i<=n;i++){
		cout<<"?"<<' '<<sum/i<<endl;
		cin>>tmp;
		if(tmp==0)continue;
		ans=min(ans,sum/i*tmp);
	}
}
signed main(){
	cin>>n;
	l=1,r=2001*2001;
	while(r>=l){
		int mid=(l+r)>>1;
		cout<<"?"<< ' '<<mid<<endl;
		cin>>tmp;
		if(tmp==1)len=mid,r=mid-1;
		else{
			l=mid+1;
		}
	}
	solve(len);
	cout<<"!"<<' '<<ans<<endl;
}

```


---

## 作者：WoXitao (赞：0)

# CF1672E 交互题题解：

## 题意：

给你 $n$ 个单词，每个单词有一个长度 $l_i$，你最多可以查询 $n+30$ 次，每次给出一个宽度 $w$，交互器会告诉你需要多少行宽度为 $w$ 才可以放下所有单词，要求找到使用面积最小的方案，其中一行内放 $l_1\dots l_k$ 需要的长度至少是 $l_1+l_2+..+l_k+(k-1)$。

## 解答：
设所有单词的总长为 $sum$。

分析查询次数可以发现近似是 $n+\log{n}$，可以想到是一次二分加上一次遍历。考虑怎么处理，首先我们需要二分出把单词都放在一行时的长度，也就是 $sum+n-1$ 设此值为 $S$。

再考虑高度大于一的情况，我们可以发现当 $w_i\cdot h_i\le S$ 也就是 $w_i\le\lfloor\frac{S}{h_i}\rfloor$ 时才会有更佳的情况产生。

同时因为 $w_i\cdot h_i\ge sum$ 所以 $w_i \ge\lfloor\frac{S}{h_i}\rfloor$。神奇的发现只有 $w_i=\lfloor\frac{S}{h_i}\rfloor$ 才会出现更佳的情况，所以我们直接遍历 $h_i,n\ge h_i\ge 2$ 运算每一个对应的 $w_i$ 询问，看其返回的 $h'\cdot w_i$ 是否是更佳。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2003;
int main(){
	int n;
	cin>>n;
	int l=1,r=N*N,S;
	while(l<=r){
		int mid=(l+r)>>1;
		cout<<"? "<<mid<<endl;
		int h;
		cin>>h;
		if(h==1){
			S=mid;
			r=mid-1;
		}else l=mid+1;
	}
	int ans=S;
	for(int i=2;i<=n;i++){
		cout<<"? "<<(S/i)<<endl;
		int h;
		cin>>h;
		if(h==0) continue;
		ans=min(ans,h*(S/i));
	}
	cout<<"! "<<ans<<endl;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1762E 题解



## 思路分析

对于一个 $h\in[1,n]$，我们定义 $w(h)$ 为 $\min\{w|h(w)=h\}$，不难发现求出 $w(1)\sim w(n)$ 即可解决原问题。

首先可以二分出 $w(1)$，即 $\sum_{i=1}^nl_i+(n-1)$ 的值，记 $w(1)=L$，花费次数为 $\log_2L<30$。

注意到如下的观察：

> 观察：
>
> 对于所有 $h\in(1,n]$，$h\times w(h)\ge L-h+1$。
>
> 注意到 $h\times w(h)$ 即显示器大小，考虑最优的情况，$h$ 行字符每行后面都没有多余的空白，即每行字符串的长度都恰好为 $w(h)$，此时显示其大小 $h\times w(h)=\sum_{i=1}^nl_i+(n-h)=L-h+1$。

我们又知道对于每一个 $h\in(1,n]$，可能影响答案的 $h\times w(h)$ 一定是 $\le L$ 的，否则一定不优于 $h=1$ 的情况。

因此对于每个 $h\in(1,n]$，如果 $h$ 可能影响答案，那么 $h\times w(h)\in[L-h+1,L]$，注意到这个区间长度为 $h$，又因为 $h\mid h\times w(h)$，所以这样的 $h$ 对应的 $w(h)$ 都有 $w(h)=\left\lfloor\dfrac Lh\right\rfloor$。

因此我们可以在 $n-1$ 次询问内求每个 $h\in(1,n]$ 的答案，与 $L$ 取 $\min$ 就可以得到答案，询问次数 $n+\log_2 L$。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXL=2001*2001;
inline int read(int x) {
	cout<<"? "<<x<<endl;
	int ret; cin>>ret;
	return ret;
}
signed main() {
	int n;
	cin>>n;
	int l=1,r=MAXL,len=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(read(mid)==1) r=mid-1,len=mid;
		else l=mid+1;
	}
	int ans=len;
	for(int h=2;h<=n;++h) {
		int w=len/h;
		if(read(w)==h) ans=min(ans,h*w);
	}
	cout<<"! "<<ans<<endl;
	return 0;
}
```



---

## 作者：junee (赞：0)

# CF1672E 题解

## 题目分析

观察题目限制，发现最多可以询问 $n+30$ 次，而 $\log n \approx 30$，所以这题大概是一个二分的 $O(\log n)$ 加一个 $O(n)$。

考虑当只有一排的时候可以直接二分出 $w$，那么此时高度为 1，接着考虑更新 $h$ 依次枚举，询问 $\frac{w}{h}$ 再更新答案。

## Code

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
#include<chrono>
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
const int N=2e3+10;
int n; 
int w;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	int l=1,r=N*N;
	while(l<=r){
		int mid=(l+r)>>1,x;
		cout<<"? "<<mid<<endl;
		fflush(stdout);
		cin>>x;
		if(x==1)w=mid,r=mid-1;
		else l=mid+1;
	}
	int sum=w,ans=w;
	for(int i=2,x;i<=n;i++){
		cout<<"? "<<sum/i<<endl;
		fflush(stdout);
		cin>>x;
		if(!x)continue;
		ans=min(ans,sum/i*x);
	}
	cout<<"! "<<ans<<'\n';
	fflush(stdout);
	return 0;
}

```

---

## 作者：hongzy (赞：0)

~~老年退役选手复健，被这个普及题卡~~

按照题目中的记法，记 $h$ 为行数，$w$ 为列数。

假设不考虑询问次数，我们有个可行的思路，即从 $w=+\infty$ 开始询问，每次 $w$ 减去 $1$，问到 $w=1$。这样我们可以得到每个 $h$ 对应的最小的 $w$，然后 $\min(h\times w)$ 就是答案。

对于每个 $h$ 二分得到最小的 $w$，询问次数 $n\cdot \log(nm)$，$m=\max(l_i)$，还是无法通过。

接下来需要我们缩小答案所在空间。记 $h=1$ 时最小的 $w$ 为 $S$。对于特定的 $h$，我们可以假设所有行末都没有多余的空格，得到一个面积的下界 $S+h-1$，同时因为 $S$ 是可行解，我们只需考虑面积取值为 $[S+h-1,S]$ 的情况。有趣的是，$S$ 必须是 $h$ 的倍数，因此这 $h$ 个可能的取值里只有一种合法，即 $w = \lfloor\frac{S}{h}\rfloor$ 的情况，我们直接询问即可，询问次数 $\log(nm)+n$。

```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
int query(int x) {
  printf("? %d\n", x);
  fflush(stdout);
  scanf("%d", &x);
  return x;
}
int main() {
  int n;
  scanf("%d", &n);
  int l = n, r = n * 2001, S = 0;
  while(l <= r) {
    int mid = (l + r) >> 1;
    if(query(mid) == 1) r = (S = mid) - 1;
    else l = mid + 1;
  }
  int res = S;
  rep(i, 1, n) {  
    int w = S / i;
    if(query(w) == i)
      res = min(res, i * w);
  }
  printf("! %d\n", res);
  return 0;
}
```

---

