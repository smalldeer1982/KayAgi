# [ABC299D] Find by Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc299/tasks/abc299_d

この問題は **インタラクティブな問題**（あなたが作成したプログラムとジャッジプログラムが標準入出力を介して対話を行う形式の問題）です。

ジャッジが $ 0 $ と $ 1 $ のみからなる長さ $ N $ の文字列 $ S\ =\ S_1S_2\ldots\ S_N $ を持っています。 文字列 $ S $ は、$ S_1\ =\ 0 $ および $ S_N\ =\ 1 $ を満たします。

あなたには $ S $ の長さ $ N $ が与えられますが、$ S $ 自体は与えられません。 その代わり、あなたはジャッジに対して以下の質問を $ 20 $ 回まで行うことができます。

- $ 1\ \leq\ i\ \leq\ N $ を満たす整数 $ i $ を選び、$ S_i $ の値を尋ねる。
 
$ 1\ \leq\ p\ \leq\ N-1 $ かつ $ S_p\ \neq\ S_{p+1} $ を満たす整数 $ p $ を $ 1 $ 個出力してください。  
 なお、本問題の条件下でそのような整数 $ p $ が必ず存在することが示せます。

### Input &amp; Output Format

最初に、文字列 $ S $ の長さ $ N $ を標準入力から受け取ってください。

> $ N $

次に、あなたはジャッジに対して問題文中の質問を $ 20 $ 回まで繰り返すことができます。

質問は、以下の形式で標準出力に出力してください。 ここで、$ i $ は $ 1\ \leq\ i\ \leq\ N $ を満たす整数でなければなりません。

> ? $ i $

これに対する応答として、$ S_i $ の値が次の形式で標準入力から与えられます。

> $ S_i $

ここで、$ S_i $ は $ 0 $ または $ 1 $ です。

問題文中の条件を満たす整数 $ p $ を見つけたら、解答を以下の形式で出力してください。 その後、ただちにプログラムを終了してください。

> ! $ p $

答えが複数ある場合、どれを出力しても正解とみなされます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
 
### 注意点

- **出力を行うたびに、末尾に改行を入れて標準出力を flush してください。そうしなかった場合、ジャッジ結果が TLE となる可能性があります。**
- **対話の途中で不正な出力を行った、あるいはプログラムが途中で終了した場合のジャッジ結果は不定です。**
- 解答を出力したらただちにプログラムを終了してください。そうしない場合、ジャッジ結果は不定です。
- 文字列 $ S $ はあなたとジャッジの対話の開始時に固定され、あなたが行った質問などに応じて変更されることはありません。
 
### 入出力例

以下は、$ N\ =\ 7,\ S\ =\ 0010011 $ の場合の入出力例です。

    入力 出力 説明     `7`  $ N $ が与えられます。    `? 1` $ S_1 $ が何かをジャッジに質問します。     `0`  質問に対する答えとして $ S_1\ =\ 0 $ がジャッジから返されます。    `? 6` $ S_6 $ が何かをジャッジに質問します。     `1`  質問に対する答えとして $ S_6\ =\ 1 $ がジャッジから返されます。    `? 5` $ S_5 $ が何かをジャッジに質問します。     `0`  質問に対する答えとして $ S_5\ =\ 0 $ がジャッジから返されます。    `! 5` 問題文中の条件を満たす整数 $ p $ として、$ p\ =\ 5 $ を解答します。    解答した $ p\ =\ 5 $ について、$ 1\ \leq\ p\ \leq\ N-1 $ かつ $ S_p\ \neq\ S_{p+1} $ が成り立ちます。 よって、この後ただちにプログラムを終了することで、正解と判定されます。

# 题解

## 作者：六楼溜刘 (赞：5)

## 题意
- 交互题。
- 有一个长度为 $N$ 的 $01$ 串 $S_1,S_2,\dots S_N$，$S_1=0,S_N=1$。
- 你可以询问至多 $20$ 次，你输出一个数 $i$，交互库告诉你 $S_i$ 是多少。
- 最终输出一个 $P$，满足 $1 \le P \le N-1,S_p \ne S_{P+1}$。
- $2 \le n \le 2\times 10^5$

## 题解
~~很多人看到交互题第一反应是跳过看下一题，但其实这题并不难。~~

首先思考一下，为什么限制询问 $20$ 次。根据我们的经验，容易发现这个数差不多是 $\log n$ 级别的，我们考虑一个类似于二分的方法。

首先把左指针 $L$ 放在 $1$，右指针 $R$ 放在 $N$，每次询问中点，如果是 $0$ 就把左指针移到中点，如果是 $1$ 就把右指针移过来。这样无论何时都满足 $S_L=0,S_R=1$。在最终必定会有一个时刻，$R=L+1$，此时直接得到答案为 $L$。

## code
```cpp
#include<iostream>
using namespace std;
int n;
signed main(){
	cin>>n;//交互题建议用 cin cout，别惦记着你那快读快输了
	int ll=1,rr=n,mm;
	while(ll<rr-1){//注意边界条件
		mm=(ll+rr)>>1;
		cout<<"? "<<mm<<endl;
//endl 自带清空缓存区，这就是 C++ 风格输入输出带给我的自信
		int res;cin>>res;
		if(res==0) ll=mm;
		else rr=mm;
	}
	cout<<"! "<<ll<<endl;
}


```


---

## 作者：2huk (赞：4)

## 题目描述

这是一道交互题。

有一个长度为 $n$ 的 $01$ 序列 $s$，保证 $s_1 = 0,s_2 = 1$。开始只告诉你 $n$，你需要对交互库询问某个位置上的数，最多 $20$ 次。

请你找到一个整数 $p \in [1, n)$，满足 $s_p \ne s_{p +1}$。

## 输入输出

首先输入一个整数 $n$，表示序列长度。

如果你要询问 $s_i$ 的值，那么你需要输出 `? i`，交互库会给你输入。

如果你要输出答案，那么你需要输出 `! p`。

## 数据范围

$2 \le n \le 2 \times 10^5$

## 分析

这个交互题很有意思，但考察思维。

题目中已经给了我们提示，因为 $20$ 是约等于 $\log_n$ 的，因此考虑二分。

首先把 $l$ 指针指向第一个位置，$r$ 指针指向最后一个位置。接下来我们要做的是维护这两个指针并时刻满足 $s_l = 0$ 且 $s_r = 1$。

这样做的目的是，如果最后 $l$ 和 $r$ 交叉，那么 $s_l$ 一定不等于 $s_r$，答案直接输出即可。

二分过程中，首先记录下它们的中间值 $mid = \left \lfloor \dfrac{l+r}2 \right \rfloor$。

接下来我们对交互库询问 $s_{mid}$ 的值。

由于要维护两个指针满足条件，所以这里分成两类解决。

如果交互库给的答案为 $0$，那么我们需要把 $l$ 指针移到 $mid$ 这里。

否则，把 $r$ 指针移到 $mid$ 这里。

这样我们就能保证 $s_l = 0$ 且 $s_r = 1$ 这个条件了。

当 $l$ 和 $r$ 相差小于等于 $2$ 时，也就是 $l$ 和 $r$ 之间存在 $\le 1$ 个元素时，就可以推出二分的循环了。输出 $l$ 即可。

## 代码

```cpp
#include <iostream>

using namespace std;

int n, l, r, mid, res, x;

int main()
{
	// 读入 
	cin >> n;
	
	l = 1, r = n;
	
	while (l + 2 <= r)		 // 二分循环条件为 l 和 r 之间存在 > 1 个元素
	{
		mid = l + r >> 1;		// 求中间值 mid 
		cout << "? " << mid << '\n';		// 询问 mid 的值 
		cin >> x;
		
		// 维护两个指针 
		if (!x) l = mid;
		else r = mid;
	}
	
	cout << "! " << l;		// 输出答案 
	
	return 0;
}
```


---

## 作者：LHQing (赞：4)

### 题意概要：

交互题。给定一个由 `01` 构成的字符串 $S$，记其长度为 $n$，保证 $S_1$ 为 `0`，$S_n$ 为 `1`。你需要找到任意一个 $p$，满足 $S_p\neq S_{p+1}$ 你有以下操作：

操作 $1$：`? i`，表示询问 $S_i$ ；

操作 $2$：`! p`，表示答案。

其中对于前者，最多询问不超过 $20$ 次。

### 题目分析：

$20$ 显然是 $\log_2n$ 的量级，我们考虑二分。

- 结论 ：若 $l<r$，$S_l=0$，$S_r=1$，那么在 $[l,r)$ 中存在一个数满足题目中的 $p$。

- 证明：若 $[l,r)$ 不存在满足题目的 $p$，那么 $S_{l\sim r}$ 必然跟 $S_l$ 和 $S_r$ 相同，而 $S_l\neq S_r$，矛盾。

所以我们每次找到中间值 $mid$，询问 $S_{mid}$，若 $S_{mid}=0$ 则向右区间递归；否则向左区间递归。询问是 $\log_2 n$ 的量级。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pd(x) push_back(x)
#define all(x) x.begin(),x.end()
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}
	void write(int x){if(!x)return;write(x/10);putchar(x%10);}
	void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
}
namespace Debug{
	void DeVec(vector<int> c){for(auto y:c)printf("%d ",y);puts("");}
	void DeNum(int x){printf("%d\n",x);}
}
//==============================================================================
const int N=1e5+10;
int n;
int ask(int x){printf("? %d\n",x);fflush(stdout);scanf("%d",&x);return x;}
void query(int x){printf("! %d\n",x);fflush(stdout);return;}
void dfs(int l,int r){
	if(l>r){
		query(l-1);return;
	}
	int mid=l+r>>1;
	int x=ask(mid);
	if(!x)dfs(mid+1,r);
	else dfs(l,mid-1);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	if(n==2){query(1);return 0;}
	dfs(2,n-1);
	return 0;
}
```

---

## 作者：_AyachiNene (赞：2)

# 题意：
有一个长度为 $n$ 的序列 $s$，开始只知道 $s_1=0$ 和 $s_n=1$。可以查询 $20$ 次 $s_i$ 的值，找一个位置 $p$，使 $s_p \neq s_{p+1}$。
# 分析：
最多可以查询 $20$ 次，而 $n$ 的大小很大，所以就可以往二分的方向想。
# 思路：
应为这个序列只有两种数字，$0$ 或 $1$。不难发现，假如有一段区间 $s_l ,  s_{l+1} , s_{l+2}……s_r$ 只要 $s_l \neq s_r$，那么无论中间是什么数，总会找到答案。而题目给出 $s_1=0$ 和 $s_n=1$，所以我们可以用二分，询问中点后，看中点与左、右哪个端点相反，只要一直找左右端点不同的区间，答案就一定会在里面。最后输出最后找到的中点就行了。

**注意：最终的答案范围在 $1$ 到 $n-1$。**
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans; 
int main()
{
   	cin>>n;
   	int l=1,r=n-1;
   	while(l<=r)
    {
   		int x;
   		int mid=(l+r)/2;
   		ans=mid;
   		cout<<"?"<<" "<<mid<<endl;
    	cin>>x;
   		if(x==1)
   			r=mid-1;
   		else
		    l=mid+1;	
   	}
   	cout<<"!"<<" "<<(l+r)/2<<endl;
}
```


---

## 作者：_shine_ (赞：1)

### 1.题目大意
交互库中有一个长度为 $n$ 的序列 $s$，其中，$s_0=0,s_n=1$，询问最多 $20$ 次，现在问下标 $id\left( 1\le id \le n-1 \right)$，使得 $s_{id} \ne s_{id+1}$。
### 2.思路分析
显然对于本题，不能使用暴力查找 $s_{id} \ne s_{id+1}$ 这一环节，显然考虑使用二分的思想，二分答案中间节点 $s_m$。因为这是一个只有 $1$ 或 $0$ 的串，且在题目中说明了 $s_1=1,s_n=1$，所以可以发现：

- 如若 $s_m=1$，则有 $s_l=0$，此时即可把 $r=m$。
- 如若 $s_m=0$，则有 $s_r=1$，此时将 $l=m$。

因此，$l,r$ 区间会变得越来越小，最后即变成 $s_l=0,s_r=1,s_l\ne s_r$，答案因此就出来了。
### 3.Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;

signed main(){
	cin >> n;
	int l=1,r=n;
	while(l+1<=r-1){//判断是否越界。
		int m=(l+r)>>1;
		cout << "? " << m << endl;
		int cnt;
		cin >> cnt;
		if(cnt==1){//m=1时的情况。
			r=m;
		}else l=m;//m=0时的情况。
	}
	cout << "! " << l << endl;
	return 0;
}
```


---

## 作者：CodingOIer (赞：1)

## [ABC299D] Find by Query题解

### 0x00 题目分析

#### [题目传送门](https://www.luogu.com.cn/problem/AT_abc299_d)

经过分析，我们得到的几个**关键信息**：

> - $n \le 2 \times 10^5$
> - 最多可以问法官 $20$ 个问题。
> - `s[1]=0,s[n]=1`

分析 $n$ 的范围，发现 $\log_n = 17.6096$，刚好比 $20$ 小一点点。

这时便考虑二分的做法。

看到 `s[1]=0,s[n]=1`，得出结论：

> 对于一个 $i$（$1 \le i \le n$）：
> - 如果 `s[i]==0`，那么 `s[i]` 右侧肯定有为 `1` 的元素。
> - 如果 `s[i]==1`，那么 `s[i]` 左侧肯定有为 `0` 的元素。

接下来分析求出答案。

题目的意思为：输出一个 $i$（`s[i]!=s[i+1]`）。

那么，按照得出的结论，即可转换为 `s[i]==0&&s[i+1]==1`。

### 0x01 关键核心代码

二分代码如下

```cpp
for(;l<r;)
{
    mid=(l+r)/2;
    printf("? %d\n",mid);
    fflush(stdout);
    scanf("%d",&x);
    if(x==1)
    {
        ans=mid;
        l=mid+1;
    }
    else if(x==0)
    {
        ans=mid;
        r=mid-1;
    }
}
```

从而补全其他的代码得到完整的AC代码。

### 0x02 完整 AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int x;
int l,r;
int mid;
int ans;
int main()
{
    scanf("%d",&n);
    l=1;
    r=n;
	for(;l<=r;)
    {
        mid=(l+r)/2;
        printf("? %d\n",mid);
        fflush(stdout);
        scanf("%d",&x);
        if(x==1)
        {
            ans=mid;
            r=mid-1;
        }
        else if(x==0)
        {
            l=mid+1;
        }
    }
	printf("! %d\n",ans-1);
	fflush(stdout);
}
```

---

## 作者：hellolin (赞：1)

## AtCoder Beginner Contest 299 - D - Find by Query

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc299_d) | [AtCoder 题面](https://atcoder.jp/contests/abc299/tasks/abc299_d) | [AC 记录](https://www.luogu.com.cn/record/110148355) | $\texttt{\color{f2b373}*763}$

注意到 $\log(2\times 10^5)\approx 17$，小于最大次数 $20$，所以第一反应是二分。

但赛时我在这题犹豫了一下，真的可以用二分吗？

考虑一种数据：

$$00000\dots 11111$$

很明显像这种数据，二分可以秒杀。

之后，题中又告诉我们：$S_1=0$ 并且 $S_n=1$。

那么，当 $S_{mid}=0$ 时，一定存在 $S_{mid}=0$ 且 $S_r=1$；当 $S_{mid}=1$ 时，一定存在 $S_l=0$ 且 $S_{mid}=1$；

也就是说，无论什么样的数据，最终一定可以化成上面这种秒杀形式。

不信的话，我们举例看一下（红色是当前区间）：

$$
{\color{red}0001110101}\\
{\color{red}0001}110101\\
00{\color{red}01}110101\\
000{\color{red}1}110101
$$

完整代码如下：

```cpp
// 珍爱账号，请勿贺题
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
bool w;
int l,r,mid;

void solve() {
    cin>>n;
    l=1,r=n;
    while(l<=r){
        mid=(l+r)>>1;
        cout<<"? "<<mid<<endl;
        cin>>w;
        if(!w)l=mid+1;
        else r=mid-1;
    }
    cout<<"! "<<r<<endl; // 一定注意最后输出的是 r
}


int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
```


---

## 作者：_Ad_Astra_ (赞：0)

由于原来的串满足 $S_1=0,S_n=1$，不难想到对于 $S_l$ 至 $S_r$ 满足 $S_l=0,S_r=1$，如果在区间内取任意一个位置 $S_m$，此时若 $S_m=0$，那么 $S_m$ 至 $S_r$ 仍然满足首位为 $0$，末位为 $1$。反之，若 $S_m=1$，那么 $S_l$ 至 $S_m$ 也满足上述条件。那么这样就可以一直递归解决，直到满足 $r=l+1$，此时就是答案。

再回过头来考虑数据范围，最多 $20$ 次询问，而 $n$ 达到了 $2 \times 10^5$，猜测做法与 $\log n$ 有关。此时不难想到二分思想，即每次取 $m$ 时取中间的点（或更具体地，$\lfloor\frac{l+r}{2}\rfloor$），这样最后的询问次数就是 $O(\log n)$ 级别的，可以满足条件。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
signed main()
{
	cin>>n;
	int l=1,r=n;
	while(l+1<r)
	{
		int mid=l+r>>1;
		cout<<"? "<<mid<<endl;
		int x;
		cin>>x;
		if(x)r=mid;
		else l=mid;
	}
	cout<<"! "<<l;
	return 0;
} 
   	 
```

---

## 作者：Crazyouth (赞：0)

**翻译**

这是道交互题。给你一个字符串 $S$ 的长度 $n$，满足 $S_1=0,S_n=1$，你可以：

- 输出`! p`，这里 $p$ 代表你求出的答案，即任意一个满足 $S_p \not = S_{p+1},1\le p\le n$ 的整数 $p$。
- 输出`? x`，这里 $x$ 需满足 $1\le x\le n$，交互库会返回 $S_x$，并且保证是 $0$ 或 $1$。这个操作不可进行超过 $20$ 次。

---

**分析**

先说做法，二分查。

**由什么想到二分**

1. 注意到询问次数为 $20$，而 $n$ 为 $2\times 10^5$，易想到询问次数应为 $\log n$ 次，而二分正好是 $O(\log n)$ 复杂度。
1. 不管我们以什么方法做，都会出现这样一组极端数据：$00000000\dots 11111111$，而二分可以秒掉这种数据。
1. 因为 $S_1=0,S_n=1$，所以必然会出现一个 $0$ 和 $1$ 的交汇处，可以二分这个点的位置。

**想到二分怎么做**

这很容易。

因为 $0$ 位于左端，$1$ 位于右端，所以遇到 $1$ 就把上界下降，遇到 $0$ 就把下界上升，最后返回 $l$，结束条件是 $mid-l<1$。

---
**AC Code**

```
#include <bits/stdc++.h>
using namespace std;
int ch(int l,int r)//二分函数
{
	int mid=(l+r)/2,opt;//opt是交互库返回的内容
	if(mid-l<1) return l;//结束条件
	else
	{
		cout<<"? "<<mid<<endl;//询问
		fflush(stdout);//记得flush
		cin>>opt;
		if(!opt) return ch(mid,r);//下界上升
		else return ch(l,mid);//上界下降
	}
}
int main()
{
	int n,tp;
	cin>>n;
	int l=1,r=n;
	tp=ch(l,r);//二分
	cout<<"! "<<tp;//输出
	return 0;
}
```


---

## 作者：yujinning (赞：0)

## 题意

- 交互库内有一个长度为 $n$ 的 $01$ 串 $S=S_1S_2S_3\ldots S_n$，其中 $S_1=0$，$S_n=1$。

- 最多询问交互库 $20$ 个问题，每次询问一个数 $x$，交互库返回 $S_x$ 的值。

- 目标寻找到一个数 $id$，使得 $S_{id}\neq S_{id+1}$。

- $1\leq n \leq 2\times 10^5$。

## 解法

使用二分法。

具体地，令 $l=1$，$r=n$，$mid=\frac{l+r}{2}$，每次询问 $S_{mid}$ 的值。如果 $S_{mid}$ 已经与已知的 $S_{mid-1}$ 或 $S_{mid+1}$不等，直接输出答案即可。

若不能直接求解答案，存下 $S_{mid}$ 的值，此时由于 $S_1\neq S_n$，必然有 $S_l\neq S_r$，则 $S_{mid}$ 必然与 $S_l$ 与 $S_r$ 中一个数不等。

- 若 $S_l\neq S_{mid}$，取 $r=mid$。

- 若 $S_r\neq S_{mid}$，取 $l=mid$。

反复上述过程直到可以直接找出 $S_{mid-1}\neq S_{mid}$ 或 $S_{mid}\neq S_{mid+1}$ 即可。

询问次数为 $\log n$，而 $2\times 10^5<2^{20}$，则 $\log n<20$，因此可以通过本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){ int x=0,f=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48); ch=getchar();} return x*f;}
inline void write(int x){ if(x<0) putchar('-'),x=-x; if(x>9) write(x/10); putchar(x%10+'0');}
const int N=200009;
int n,a[N];
string ser,s;
int main(){
	n=read(); a[1]=1,a[n]=2;
	int l=1,r=n,mid=(l+r)>>1;
	while(true){
		mid=(l+r)>>1;
		cout<<"? "<<mid<<endl;
		int op; cin>>op; op++; a[mid]=op;
		if(a[mid-1]!=0&&op!=a[mid-1]) {cout<<"! "<<mid-1;break;}
		else if(a[mid+1]!=0&&op!=a[mid+1]) {cout<<"! "<<mid;break;}
		if(op!=a[l]) r=mid;
		else l=mid;
	}
	return 0;
}

```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc299_d)         
不难的交互题。         
注意到 $s_1=0$，$s_n=1$，所以我们可以以此进行二分。                 
我们每次取一个 $mid$，这里我们询问 $s_{mid}$ 的值，如果 $s_{mid}=0$，我们右移 $l$，易知这种情况里必然有一个 $p∈[l,r]$。如果 $s_{mid}=1$，我们左移 $r$，同样易知这种情况里必然也有一个 $p∈[l,r]$。        
最后循环终止，答案在 $r$ 中。        
[CODE](https://www.luogu.com.cn/paste/ofp7sl01)

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc299_d)
### 题解
看到查询次数不超过 $20$ 次，不难想到，这是一个二分级别的数据范围。

不难发现一个规律：若一个区间 $[l,r]$ 满足 $s_l\neq s_r$ 那么一定存在一个位置，使得 $s_i\neq s_{i+1}$。

设要求解答案的区间为 $[l,r]$，且 $s_l=0$，$s_r=1$，令 $mid=\lfloor\dfrac{l+r}{2}\rfloor$。
若 $s_{mid}=s_l$，那么 $s_{mid}= s_{l}\neq s_{r}$，所以有答案在 $[mid,r]$，则令 $l\gets mid$。
反之 $s_{mid}=s_r$，那么 $s_{mid}=s_r\neq s_l$，所以有答案在 $[l,mid]$，则令 $r\gets mid$。

当 $r-l=1$ 时，答案即为 $l$。 
### 代码
```cpp
#include <iostream>
using namespace std;
const int N = 200010;
int n;
int main () {
	cin >> n;
	int first;
	int l = 1,r = n;
	while (l + 1 < r) {
		int mid = l + r >> 1;
		cout << '?' << ' ' << mid << endl;
		fflush (stdout);
		int x;
		cin >> x;
		if (x) r = mid;
		else l = mid;
	}
	cout << '!' << ' ' << l << endl;
	fflush (stdout);
	return 0;
}
```

---

## 作者：Silence_World (赞：0)

# 思路

较为简单的一道交互，首先我们知道 $S_{1}$ $=0$，$S_{1}$ $=1$,且范围暴力查找肯定不行，那就试试二分，每次先询问 $mid$ 的值，根据返回结果左右查（具体根据代码理解），不管如何，在不停压缩之后，最后剩下的肯定后面与前面不一样，因为二分查找压缩 1 与 0，最后剩下的无非就是前面后面是 1 或 0 而自身相反，否则就被二分压缩掉了，最后输出结果搞定！
 
#  代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[100005];
int b[100005];
int c[100005];
int max1[100005];
main(){
	int n;
	cin>>n;
	int l=1,r=n-1;
	while(l<=r){
		int mid=(l+r)/2;
		cout<<"? "<<mid<<endl;
		int t;
		cin>>t;
		if(t==1){
			r=mid-1;
		}
		if(t==0){
			l=mid+1;
		}
	}
	int mid=(l+r)/2;
	cout<<"! "<<mid<<endl;
	return 0;
} 
```


---

