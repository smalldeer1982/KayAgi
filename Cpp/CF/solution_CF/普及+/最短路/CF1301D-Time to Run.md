# Time to Run

## 题目描述

Bashar was practicing for the national programming contest. Because of sitting too much in front of the computer without doing physical movements and eating a lot Bashar became much fatter. Bashar is going to quit programming after the national contest and he is going to become an actor (just like his father), so he should lose weight.

In order to lose weight, Bashar is going to run for $ k $ kilometers. Bashar is going to run in a place that looks like a grid of $ n $ rows and $ m $ columns. In this grid there are two one-way roads of one-kilometer length between each pair of adjacent by side cells, one road is going from the first cell to the second one, and the other road is going from the second cell to the first one. So, there are exactly $ (4 n m - 2n - 2m) $ roads.

Let's take, for example, $ n = 3 $ and $ m = 4 $ . In this case, there are $ 34 $ roads. It is the picture of this case (arrows describe roads):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301D/f8acc1bb44bf67b8a6e82d8abf101031f5e398f8.png)

Bashar wants to run by these rules:

- He starts at the top-left cell in the grid;
- In one move Bashar may go up (the symbol 'U'), down (the symbol 'D'), left (the symbol 'L') or right (the symbol 'R'). More formally, if he stands in the cell in the row $ i $ and in the column $ j $ , i.e. in the cell $ (i, j) $ he will move to: 
  - in the case 'U' to the cell $ (i-1, j) $ ;
  - in the case 'D' to the cell $ (i+1, j) $ ;
  - in the case 'L' to the cell $ (i, j-1) $ ;
  - in the case 'R' to the cell $ (i, j+1) $ ;
- He wants to run exactly $ k $ kilometers, so he wants to make exactly $ k $ moves;
- Bashar can finish in any cell of the grid;
- He can't go out of the grid so at any moment of the time he should be on some cell;
- Bashar doesn't want to get bored while running so he must not visit the same road twice. But he can visit the same cell any number of times.

Bashar asks you if it is possible to run by such rules. If it is possible, you should tell him how should he run.

You should give him $ a $ steps to do and since Bashar can't remember too many steps, $ a $ should not exceed $ 3000 $ . In every step, you should give him an integer $ f $ and a string of moves $ s $ of length at most $ 4 $ which means that he should repeat the moves in the string $ s $ for $ f $ times. He will perform the steps in the order you print them.

For example, if the steps are $ 2 $ RUD, $ 3 $ UUL then the moves he is going to move are RUD $ + $ RUD $ + $ UUL $ + $ UUL $ + $ UUL $ = $ RUDRUDUULUULUUL.

Can you help him and give him a correct sequence of moves such that the total distance he will run is equal to $ k $ kilometers or say, that it is impossible?

## 说明/提示

The moves Bashar is going to move in the first example are: "RRLL".

It is not possible to run $ 1000000000 $ kilometers in the second example because the total length of the roads is smaller and Bashar can't run the same road twice.

The moves Bashar is going to move in the third example are: "RRDDLLRR".

The moves Bashar is going to move in the fifth example are: "RRRLLLDRRRDULLLD". It is the picture of his run (the roads on this way are marked with red and numbered in the order of his running):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301D/eda2cf93789d47332ff1838d0a037b6665e63145.png)

## 样例 #1

### 输入

```
3 3 4```

### 输出

```
YES
2
2 R
2 L```

## 样例 #2

### 输入

```
3 3 1000000000```

### 输出

```
NO```

## 样例 #3

### 输入

```
3 3 8```

### 输出

```
YES
3
2 R
2 D
1 LLRR```

## 样例 #4

### 输入

```
4 4 9```

### 输出

```
YES
1
3 RLD```

## 样例 #5

### 输入

```
3 4 16```

### 输出

```
YES
8
3 R
3 L
1 D
3 R
1 D
1 U
3 L
1 D```

# 题解

## 作者：Kelin (赞：9)

## 题意

给你一个$n\times m$的网格,相邻的格子之间有双向边(来回两条边).

问是否能不经过重复的边的情况下从左上角出发遍历$k$条边.

$1\le n,m\le 500,1\le k\le10^9$

## [题解](https://blog.csdn.net/BeNoble_/article/details/104511611)

将格子抽象为点,可以注意到所有点的点度均为偶数,整张图是一个欧拉图.

故可以走完所有$2(2nm-n-m)$条边.

一种简单可行的走法为:

>$1.$向右走$m-1$步到达右上角.

>$2.$向下走$n-1$步再向上走$n-1$步回到原处.

>$3.$向左走一步.

>$4.$重复$2,3$步骤$m-1$遍,回到左上角.

>$5.$向下走一步.

>$6.$向右走$m-1$步再向左走$m-1$步回到原处.

>$7.$重复$5,6$步骤$n-1$遍,到达左下角.

>$8.$向上走$n-1$步,回到左上角.

当所需要走的剩余步数不足以完成当前步骤时输出答案退出即可.

```cpp
inline void Out(){
    printf("%d\n",(int)Ans.size());
    for(auto i:Ans)printf("%d %c\n",i.first,i.second);
    exit(0);
}
inline void Run(int s,char c){
    if(!s)return;
    if(k<=s)Ans.push_back({k,c}),Out();
    k-=s;Ans.push_back({s,c});
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    if(k>2*(2*n*m-n-m))return puts("NO"),0;
    puts("YES");Run(m-1,'R');
    for(int i=1;i<m;++i)
        Run(n-1,'D'),Run(n-1,'U'),Run(1,'L');
    fp(int i=1;i<n;++i)
        Run(1,'D'),Run(m-1,'R'),Run(m-1,'L');
    Run(n-1,'U');
return 0;
}
```

---

## 作者：CXY07 (赞：2)

# 趣味简单题

## 题目链接：[CF1301D 【Time to Run】](https://www.luogu.com.cn/problem/CF1301D)

> **本题解同步发布于 [My Blog](https://cxy07.blog/index.php/archives/16/)**

题意简介：

给定一个 $n \times m$ 的矩阵，相邻的两个格子之间有两条方向相反的有向边，长度均为 $1$，从左上角开始，每次可以向左、右、上、下走一格，但是不能重复走已经走过的路（可以重复经过到过的格子，不能走出网格图），问是否可能走出一条长度为 $k$ 的路径（不一定要在左上角结束），如果可以，需要输出方案。

$n,m \le 500$

这题一开始想，还以为是个什么欧拉路的题目，但是输出方案的方式给了我们提示...

输出方案最多 $3000$ 行，每一行一个数字 $f,f \le 10^9$ 和一个长度不超过 $4$ 的字符串。

字符串中使用字符 $L,R,U,D$，分别代表向左、右、上、下走一步。

$f$ 则意为重复按照字符串所说地走 $f$ 次。

这个输出方法很玄学，如果是我们找到了一种走法，再去考虑输出方案，显然我们还需要分割路径的字符串，这很麻烦。

所以考虑构造一种万能走法，能够囊括 **所有的长度**。

注意标黑的部分，那显然我们如果能找到一种走法，使得每一条边都能被遍历，显然就是最优的了。

![pic](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301D/f8acc1bb44bf67b8a6e82d8abf101031f5e398f8.png)

我们令左上角为 $(1,1)$ 第一行第二个为 $(1,2)$ 以此类推

我们很快可以找出一种走法，可以遍历完第一行格子之间的边，和第一行与第二行之间的所有边的走法（除了 $(2,1)$ 到 $(1,1)$ 一条）

![pic2](https://cdn.luogu.com.cn/upload/image_hosting/8r20goe1.png)

这中间蓝色显然是可以重复走的 ~~懒得画了~~，红色是 $R$ 重复，蓝色是 $DUL$ 的重复，黄色是一个 $D$，这样显然，第二行也可以用相同的走法，从而到达了第三行......以此类推

注意一下最后一行只能 $R$ 之后 $L$ 回来，不能走蓝色那种了，因为它没有下一行了，特判一下即可

最后，我们会到达 $(n,1)$ ，不难发现所有 $(i,1)$ 到 $(i-1,1)$ 的路径都是没走过的，那我们就一直 $U$ 上去即可。

那这种做法是否符合输出规范呢？

显然处理一行，我们需要的行数为 $3$ : 红色一行，蓝色一行，黄色一行

$n_{max} = 500$ ，所以大约需要 $1500$ 行的样子，显然 $1500 < 3000$，所以行数限制是没问题的。

再来看字符串长度问题，根据上面所说，我们只会走 $R,DUL,D,U,L$ 这 $5$ 种字符串，显然长度没有超过 $4$ ，这个限制也没有问题

再有 $f$ 的限制$(f\le 10^9)$，回想一下，我们的走法都在一行或者一列里面走，循环次数显然不会超过 $max(n,m)$ 那肯定就不会超过 $10^9$ 啦

那么我们就做完了。

**注意特判 $m=1$ 的情况！** 为什么？

因为我们的走法第一步就是 $R$ ，但是 $m=1$ 时，我们没有 $R$ 的余地！

所以特判一下直接 $D$ 再 $U$ 就好了

注意每走一步新的都要判断是否在这一步中结束，因为他要最先输出命令行数，所以我就把它丢到 $vector$ 里面了，两个 $vector$ 分别存放的是 $f$ 和对应的字符串，应该不难理解。

$Code:$

```cpp//Code By CXY
#include<bits/stdc++.h>
using namespace std;

int n,m,savk,k,lim;
vector<int> cnt;
vector<string> ans;

inline void print() {
	puts("YES");
	int len = cnt.size(),tmp;
	cout << len << endl;
	for(register int i = 0;i < len; ++i) {
		cout << cnt[i] << ' ' << ans[i] << endl;
		tmp += cnt[i] * ans[i].length();
	}
	return;
}//输出答案

int main () {
	//freopen("in.in","r",stdin); 
	cin >> n >> m >> k; savk = k;
	if(k > 4 * n * m - 2 * n - 2 * m) {puts("NO"); return 0;}//总共边数都没有这么多
	if(m == 1) {//特判
		lim = n - 1;
		if(k <= lim) {
			cnt.push_back(k),ans.push_back("D");
			k = 0;
			print();
			return 0;
		}// D下去
		k -= lim;
		cnt.push_back(lim),ans.push_back("D");
		if(k <= lim) {
			cnt.push_back(k),ans.push_back("U");
			k = 0;
			print();
			return 0;
		} 
		k -= lim;
		cnt.push_back(lim),ans.push_back("U");// U上来
		if(!k) print();
		else puts("NO");
		return 0;
	}
	lim = m - 1;//指红蓝两种走法最多走多少次，显然是m-1
	for(register int i = 1;i <= n; ++i) {
		if(k <= lim) {
			cnt.push_back(k),ans.push_back("R");
			k = 0;
			break;
		}
		k -= lim;
		cnt.push_back(lim),ans.push_back("R");//红
		if(i < n && k <= lim * 3) {//不是最后一行并且在这一步中结束
			int tmp = k / 3,_;
			if(tmp) {
				cnt.push_back(tmp),ans.push_back("DUL");
			}
			_ = k - tmp * 3;
			if(_ == 1) cnt.push_back(1),ans.push_back("D");
			else if(_ == 2) cnt.push_back(1),ans.push_back("DU");
			k = 0;//蓝中间结束，注意最后一下是 D 还是 DU
			break;
		}
		if(i < n) {//不是最后一行的情况
			k -= lim * 3;
			cnt.push_back(lim),ans.push_back("DUL");
			cnt.push_back(1),ans.push_back("D");//蓝
			k--;
		} else {//最后一行，直接L回去
			if(k <= lim) {
				cnt.push_back(k),ans.push_back("L");
				k = 0;
				break;
			} else {
				k -= lim;
				cnt.push_back(lim),ans.push_back("L");
			}
		}
		if(!k) break;
	}
	if(!k) {//如果走完了，输出
		print();
		return 0;
	}
	if(k <= n - 1) {//否则我们可以走 U n-1次
		cnt.push_back(k),ans.push_back("U");
		print();
	} else puts("NO");//肯定就不行了
	return 0;//End.
}
```

趣味题，作为一道 $Div2$ 的 $D$，有种让人耳目一新的感觉 ~~(主要是可以上分了)~~，注意特判，就没什么难的了。

初三的 $OIer$，请多关照

---

## 作者：Ryan_Adam (赞：0)

# CF1301D Time to Run 题解
思维题。
## 分析
把一个格子视作一个点，每个点的度数都是偶数，所以这是一张欧拉图。而需要走遍整个方格图，可以证明只要 $k$ 不超过 $4nm-2n-2m$ 就一定有解。

很明显存在很多种方案，这里我用的方案是：从左上角出发，向右走 $m-1$ 步到头，再向左走 $m-1$ 步回来，向下走一步。重复以上步骤，直到走到左下角。然后向右走一步，向上走 $n-1$ 步到头，向下走 $n-1$ 步回来。重复上面步骤，直到走到右下角。这时候你会发现你已经走完了这张网格图里的所有边。注意在走的过程中如果步数用完了中断输出答案即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    int const N = 3005;
    int n, m, k, num[N], cnt;
    char ans[N][5];
    signed work()
    {
        cin >> n >> m >> k;
        if (k > 4 * n * m - 2 * n - 2 * m)return cout << "NO" << endl, 0;
        int anss = 0, sum = k;
        cout << "YES" << endl;
        while (k)
        {
            int _min;
            if (sum - k < m - 1)
            {
                _min = min(k, m - 1);
                num[++cnt] = _min;
                ans[cnt][0] = 'R';
            }
            else if (sum - k < 2 * (m - 1))
            {
                _min = min(k, m - 1);
                num[++cnt] = _min;
                ans[cnt][0] = 'L';
            }
            else if (sum - k < 2 * (m - 1) + 1)
            {
                _min = 1;
                num[++cnt] = _min;
                ans[cnt][0] = 'D';
            }
            else if (sum - k >= 4 * n * m - 2 * n - 2 * m - (n - 1))
            {
                cnt++;
                _min = min(k, n - 1);
                num[cnt] = _min;
                ans[cnt][0] = 'U';
            }
            else if (anss % 3 == 0)
            {
                _min = min(k, m - 1);
                if (_min)
                {
                    cnt++;
                    num[cnt] = _min;
                    ans[cnt][0] = 'R';
                }
                anss++;
            }
            else if (anss % 3 == 1)
            {
                _min = min(k, 3 * (m - 1));
                int __min = _min / 3;
                if (__min)
                {
                    cnt++;
                    num[cnt] = __min;
                    ans[cnt][0] = 'U';
                    ans[cnt][1] = 'D';
                    ans[cnt][2] = 'L';
                }
                if (_min % 3 == 1)
                {
                    num[++cnt] = 1;
                    ans[cnt][0] = 'U';
                }
                if (_min % 3 == 2)
                {
                    num[++cnt] = 1;
                    ans[cnt][0] = 'U';
                    ans[cnt][1] = 'D';
                }
                anss++;
            }
            else
            {
                _min = 1;
                num[++cnt] = _min;
                ans[cnt][0] = 'D';
                anss++;
            }
            k -= _min;
        }
        cout << cnt << endl;
        for (int i = 1; i <= cnt; i++)cout<< num[i] << " " << ans[i] << endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

好像是到大水题吧。

对于给定的网格，我们可以计算出我们最多可以遍历多少条边。

我们也许会想到下面这种走法，并且可以证明原路返回一定不会走到重复的边：

从起点出发，对于每一个 $2\times 2$ 的网格单位，我们“最好的”走法是下右上，这样我们每一个单位就可以提供 $8$ 条边（包含返程边）。对于 $n,m$ 其中有偶数的情况，我们要特殊考虑。

但是！这种想法是错误的。

事实上，我们还有更简单的方法。并且本题可以不用找规律的，细心的童鞋就可以发现，每个点的度数都是偶数，**入度 $=$ 出度**。加之本题要求最多可以经过的边数且不能重复，那么我们就可以想到**欧拉图。**

所以说，我们可以走完所有的边！（所以说这就是为什么我们在尝试构造的时候总是可以找到经过边数更多的方案了）

那么总边数有多少呢？$2(2nm-n-m)$ 条边（题目中已说）。我们考虑一种可以走完所有边的方法，然后按照这个方法进行模拟，直到遍历 $k$ 条边或者无法走为止。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//
#include<bits/stdc++.h>

//
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*
#define pr pair<int,char>
#define pf first
#define ps second
#define pb push_back
//*/

//
using namespace std;
//
const int N=1e3+5;
const int M=1e3;
const int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
const int IINF=1e18;
const db eps=1e-9;
//
int n,m,a[N],b,q,s[N],op,idx,len[N],k,ans,res,tmp,cnt[N],id[N];
int L;
vector<pr> e;

void dfs(int s,char c){
    if(!s)return;
    if(k<=s){
    	e.push_back({k,c});
    	
    	int sz=e.size();//注意一定要转换
    	printf("%lld\n",sz);
	    for(auto i:e)printf("%lld %c\n",i.first,i.second);
	    exit(0);
	}
    k-=s;e.push_back({s,c});
}
signed main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    
    if(k>2*(2*n*m-n-m)){
		cout<<"NO"<<endl;
		return 0;
	}
    cout<<"YES"<<endl;
	
	dfs(m-1,'R');
    
    for(int i=1;i<m;i++){
    	dfs(n-1,'D');
		dfs(n-1,'U');
		dfs(1,'L');
	}
	
	cerr<<"OK"<<endl;
        
    for(int i=1;i<n;i++){
    	dfs(1,'D');
		dfs(m-1,'R');
		dfs(m-1,'L');
	}
       
    dfs(n-1,'U');
	return 0;
}
```




---

## 作者：123456zmy (赞：0)

~~特判！！！~~

题意：
给你一个 $n$ 行 $m$ 列的无向网格图，要不重复地走过 $k$ 条边，输出是否能达到以及走法（总步数不能超过 $3000$）。
___
如果 $k$ 比边的总数还多则不行，否则可以。

首先想到要这么走：（以$n =3$，$m=4$为例，~~图有点丑~~）

![](https://cdn.luogu.com.cn/upload/image_hosting/jnixpfdc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

然后走完 $k$ 步即可。

特判！！！$n=1$ 或 $m=1$ 时要防止输出 $0$ 以及走出地图的情况。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int ans[10001],ansn;
char ansf[10001];
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	if(k>(4*n*m-2*n-2*m))
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i=1;i<m;i++)if(k>(n-1<<1))
	{
		k-=(n-1<<1)+1;
		if(n-1)
		{
			ans[++ansn]=n-1;
			ansf[ansn]='D';
			ans[++ansn]=n-1;
			ansf[ansn]='U';
		}
		ans[++ansn]=1;
		ansf[ansn]='R';
	}
	else
	{
		if(k>n-1&&n-1)
		{
			ans[++ansn]=n-1,ansf[ansn]='D';
			ans[++ansn]=k-n+1,ansf[ansn]='U';
		}
		else if(k&&n-1)ans[++ansn]=k,ansf[ansn]='D';
		printf("%lld\n",ansn);
		for(int i=1;i<=ansn;i++)
		{
			printf("%lld ",ans[i]);
			putchar(ansf[i]);
			putchar(10);
		}
		return 0;
	}
	for(int i=2;i<=n;i++)if(k>(m-1<<1))
	{
		k-=(m-1<<1)+1;
		ans[++ansn]=1;
		ansf[ansn]='D';
		if(m-1)
		{
			ans[++ansn]=m-1;
			ansf[ansn]='L';
			ans[++ansn]=m-1;
			ansf[ansn]='R';
		}
	}
	else
	{
		if(k)
		{
			k--;
			ans[++ansn]=1;
			ansf[ansn]='D';
		}
		if(k>m-1&&m-1)
		{
			if(m-1)ans[++ansn]=m-1;
			ansf[ansn]='L';
			ans[++ansn]=k-m+1;
			ansf[ansn]='R';
		}
		else if(k&&m-1)ans[++ansn]=k,ansf[ansn]='L';
		printf("%lld\n",ansn);
		for(int i=1;i<=ansn;i++)
		{
			printf("%lld ",ans[i]);
			putchar(ansf[i]);
			putchar(10);
		}
		return 0;
	}
	if(k>n-1)
	{
		if(n-1)ans[++ansn]=n-1,ansf[ansn]='U';
		ans[++ansn]=k-n+1;
		ansf[ansn]='L';
	}
	else if(k&&n-1)
	{
		ans[++ansn]=k;
		ansf[ansn]='U';
	}
	printf("%lld\n",ansn);
	for(int i=1;i<=ansn;i++)
	{
		printf("%lld ",ans[i]);
		putchar(ansf[i]);
		putchar(10);
	}
	return 0;
}
```

---

