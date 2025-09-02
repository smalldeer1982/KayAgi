# Domino (easy version)

## 题目描述

The only difference between this problem and D2 is that you don't have to provide the way to construct the answer in this problem, but you have to do it in D2.

There's a table of $ n \times m $ cells ( $ n $ rows and $ m $ columns). The value of $ n \cdot m $ is even.

A domino is a figure that consists of two cells having a common side. It may be horizontal (one of the cells is to the right of the other) or vertical (one of the cells is above the other).

You need to find out whether it is possible to place $ \frac{nm}{2} $ dominoes on the table so that exactly $ k $ of them are horizontal and all the other dominoes are vertical. The dominoes cannot overlap and must fill the whole table.

## 样例 #1

### 输入

```
8
4 4 2
2 3 0
3 2 3
1 2 0
2 4 2
5 2 2
2 17 16
2 1 1```

### 输出

```
YES
YES
YES
NO
YES
NO
YES
NO```

# 题解

## 作者：UperFicial (赞：11)

$\huge\text{Sol}$

赛时 $\color{red}\texttt{WA}$ 掉了/kk

题目中说 $n\times m$ 为偶数，所以考虑对 $n,m$ 的奇偶性分情况讨论。

- $n,m$ 都是偶数。

	- 那么显然我们可以将 $n\times m$ 的方格化为 $\dfrac{n}{2}\times\dfrac{m}{2}$ 个 $2\times 2$ 的方格，而对于一个 $2\times 2$ 的方格只能竖着放两个或横着放两个，所以这里要求 $k\equiv 0\bmod 2$。
    
- $n$ 是奇数且 $m$ 是偶数。

	- 考虑如果第 $1$ 行填满就转换为情况 $1$ 了。
    
   - 如果要填满第一行，那么肯定是要横着填 $\dfrac{m}{2}$ 个骨牌的。余下的 $\left( k-\dfrac{m}{2}\right)$ 个骨牌看看是否是偶数即可。
   
- $n$ 是偶数且 $m$ 是奇数。

	- 仍然考虑转换为情况 $1$。
    
   - 我们将最左面的一列填满后得到 $n\times (m-1)$ 的矩阵。这里 $n$ 和 $(m-1)$ 都是偶数，所以转化为第一种情况。
   
   - 但是还有一个问题，矩阵的大小变了，不一定 $k$ 个水平的多米诺骨牌全能放进去，所以 $k$ 的上界为 $\dfrac{n\times(m-1)}{2}$。
   
- $n$ 是奇数且 $m$ 是奇数。

	- 你觉得它们乘起来是偶数？

---

## 作者：断清秋 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1551D1)

题意：给定一个 $n$ 行 $m$ 列的方格，用 $k$ 块水平 $1×2$ 的多米诺骨牌覆盖后，余下部分能否被竖直的 $1×2$ 的多米诺骨牌覆盖。

显然是一道结论题。

题目中有 $nm$ 为偶数，考虑对 $n,m$ 的奇偶性进行讨论。

情况 $1$ ：$n,m$ 均为偶数。此时只要 $k$ 为偶数即可。

证明：每两块水平 $1×2$ 的多米诺骨牌必定能覆盖一个 $2×2$ 的方格，这样对原方格没有影响，因此 $k$ 为偶数时一定有解，反之无解。

情况 $2$：$n$ 为奇数，$m$ 为偶数。

发现这种情况下，只要将最上方一行全部填满，余下部分与情况 $1$ 相同。于是只需要判断第一行是否能被填满，且填满第一行后是否有解即可，即 $k≥\dfrac{m}{2}$，且 $k-\dfrac{m}{2}$ 为偶数则有解，反之无解。

情况 $3$：$n$ 为偶数，$m$ 为奇数。

发现这种情况下，只要将最左边一列全部填满，余下部分与情况 $1$ 相同。于是只需要判断第一列是否能被填满，且填满第一列后是否有解即可，即 $k$ 为偶数。

但是注意到，当填到只剩下 $1$ 列的时候就不能继续填了，因此 $k$ 有最大值，即 $k≤\dfrac{n(m-1)}{2}$。

综合一下，$k≤\dfrac{n(m-1)}{2}$ 且 $k$ 为偶数则有解，反之无解。

时间复杂度 $O(t)$。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int 
using namespace std;
int read()
{
	int x=0,f=1;
    char ch=getchar();
	while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
	while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
	back x*f;
}
string s;
ll t,n,m,k,a[200005];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k;
		if(n%2==0&&m%2==0)
		{
			if(k%2==0)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
			continue;
		}
		if(n%2==1&&m%2==0)
		{
			if((k-m/2)%2==0&&k>=m/2)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
			continue;
		}
		if(n%2==0&&m%2==1)
		{
			if(k%2==0&&k<=(m-1)*n/2)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
			continue;
		}
		
	}
    back 0;
}
```

---

## 作者：xuanyuan_Niubi (赞：1)

# 题意简述

给你一个 $ n \times m $ 的大长方形，要求你用 $ \frac{n\times m}{2}$ 个 $ 1\times 2$ 的小长方形填满这个大长方形，并且其中恰好有 $ k $ 个小长方形是水平放置。问能否达到要求。

# 分析

两个 $ 1\times 2 $ 的小正方形可以组成一个 $ 2\times 2 $ 的正方形。所以我们要让 $ k $ 个水平长方形放置后剩下的图形可以被分成若干个 $ 2 \times 2$ 的正方形。如果剩下单独的一列，只要 $ n $ 是偶数就一定可以用竖直的小长方形将这一列铺满。

所以如果 $ n $ 是偶数，$ k $ 也是偶数，那么剩下的一定可以由若干个 $ 2\times 2 $ 的正方形组成的图形，无论 $ m $ 是奇是偶。如果 $ k $ 是奇数，那就不行了。

但是如果 $ n $ 是奇数呢？如果 $m$ 也是奇数，那么一定会剩一个格子填不了。如果 $ m $ 是偶数，那么先把第一排的横着的填满，剩下的就可以按 $ n $ 是偶数的情况了。如果 $ k $ 连第一排都填不满，那就不可能满足，因为肯定会有某一列有 $ n $ 行，而此时 $n $ 是奇数。

哦，对了，首先要判断这个大长方形最多可以容纳的小长方形的个数是否 $ >k$，如果是就肯定不行。

#### 合并各种情况后的code

```c++
#include<cstdio>
#include<cstring>
using namespace std;
const int M=2e5+5;
inline int read(){
	char c=getchar();int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=0;
	for(;c<='9'&&c>='0';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return f?x:-x;
}
int main(){
	int T=read();
	while(T--){
		int n=read(),m=read(),k=read(),t=m/2;//t是一排最多横着放多少个
		if(!(m&1)&&n&1&&k>=t)k-=t,n--;//如果n是奇数，m是偶数，k可以把第一排填满
		if(n*t<k){//如果k超过了最多可以放置的个数
			printf("NO\n");continue;
		}
		if(!(n&1)&&!(k&1))printf("YES\n");//如果n、k是偶数
		else printf("NO\n");
	}
	return 0;
}
```



---

## 作者：Ryan_Adam (赞：0)

## 题解：CF1551D1 Domino (easy version)
## 分析
题目中保证 $n\times m$ 为偶数，下面进行分类讨论。
### 情况一
如果 $n$ 和 $m$ 都是偶数，那么可以分割成 $\frac{n}{2}\times\frac{m}{2}$ 个 $2\times2$ 的方块。

![](https://krseoul.imgtbl.com/i/2024/08/05/66b096799a4f6.png)

根据上图我们发现，只要 $k$ 满足 $0\le k\le \frac{n}{2}\times\frac{m}{2}\times 2$ 且 $2 \mid k$，就一定可以凑出来。
### 情况二
如果 $n$ 是奇数，$m$ 是偶数，我们考虑把 $n$ 变为偶数转化为第一种情况。

![](https://krseoul.imgtbl.com/i/2024/08/05/66b09679f086f.png)

如上图，可以先在第一行排 $\frac{m}{2}$ 个多米诺骨牌，这时如果 $k<\frac{m}{2}$ 就无解，否则就直接转化为了第一种情况，此时 $k$ 变为 $k-\frac{m}{2}$。

### 情况三
如果 $n$ 是偶数，$m$ 是奇数，我们考虑把 $m$ 变为偶数转化为第一种情况。

![](https://krseoul.imgtbl.com/i/2024/08/05/66b09679e3191.png)

如上图，可以先在第一列排 $\frac{n}{2}$ 个多米诺骨牌。由于 $k$ 的限制是横向的多米诺骨牌，所以 $k$ 不变，转换为情况一。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
bool check(int a,int b,int c)
{
    if(c&1)return 0;
    if(c>(a/2)*(b/2)*2)return 0;
    return 1;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n>>m>>k;
        if(!(n&1)&&!(m&1))
        {
            if(check(n,m,k))
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
        else if((n&1)&&!(m&1))
        {
            if(k<m/2)
            {
                cout<<"NO"<<endl;
                continue;
            }
            k-=m/2;
            n--;
            if(check(n,m,k))
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
        else if(!(n&1)&&(m&1))
        {
            m--;
            if(check(n,m,k))
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
    }
    return 0;
}
```

---

## 作者：dthythxth_Huge_Brain (赞：0)

## 前言
分类讨论水题。

## 解题思路

1. $n \equiv 0 \pmod{2}$ 且 $m \equiv 1 \pmod{2}$。  
   显然将网格分成 $2 \times 2$ 的小网格，每个小网格上可以放 $2$ 个横着的骨牌或 $2$ 个竖着的骨牌，所以需满足 $k \equiv 0 \pmod{2}$。
2. $n \equiv 1 \pmod{2}$ 且 $m \equiv 0 \pmod{2}$。  
   将第一行用横着的骨牌填满，剩下的见 1 的构造，可得 $k \ge \frac{m}{2}$ 且 $k - \frac{m}{2} \equiv 0 \pmod{2}$。
3. $n \equiv 0 \pmod{2}$ 且 $m \equiv 1 \pmod{2}$。  
   将第一列用竖着的骨牌填满，剩下的见 1 的构造，可得 $k \le \frac{n\times(m-1)}{2}$ 且 $k \equiv 0 \pmod{2}$。

于是 D1，D2 就喜提 AC 了。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
int t,n,m,k;
signed main(){
	scanf("%lld",&t);
	for(;t--;){
		scanf("%lld%lld%lld",&n,&m,&k);
		if(!((n&1))&&!((m&1))&&k&1)puts("NO");
		else if(n*m&1)puts("NO");
		else if((n&1)&&!((m&1))&&(k<m/2||k-m/2&1))puts("NO");
		else if(!((n&1))&&(m&1)&&(k&1||k>n*(m-1)/2))puts("NO");
		else puts("YES"); 
	}
	return 0;
}
```

---

## 作者：yingkeqian9217 (赞：0)

# 前言

这里提供一种实现起来比较方便的写法。

# 分析

注意到，$n,m$ 中有一个是偶数，所以我们不妨设 $n$，即高度为偶数，$m$ 不确定。

此时的 $k$ 显然为偶数，否则考虑它对每一列的影响，因为它覆盖了偶数列，所以必定有一列有奇数个横着的，此时该列剩下奇数个空位，无法放竖着的。

那么我们就得到了一种构造方案，就是两列为一组先排横着的，再一列一列排竖着的。

注意到我们无法确定 $m$ 足够横着的排，所以特判 $m\ge \lceil \frac{k}{n}\rceil \times 2$，否则显然横着的都排不下。

然后我们的构造就完成了。

# code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,k;
void solve(){
	scanf("%d%d%d",&n,&m,&k);
	if(n&1) k=n*m/2-k,swap(n,m);
	if(m<(k+n-1)/n*2) puts("NO");//向上取整偷懒写法qwq
	else puts(k%2?"NO":"YES");
}
signed main(){
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}

```

---

## 作者：cff_0102 (赞：0)

## Domino (easy version) 题解

看到题，首先想到对 $n$ 和 $m$ 分类讨论。

1. 当 $n,m$ 都是奇数，那么绝对无法铺满。当然，题中说了 $n\times m$ 是偶数，那么实际上不需要判断。经过测试，删掉相应代码也能过。
2. 当 $n,m$ 都是偶数，可以像下图一样把网格分成若干的 $2\times2$ 的小格子，它们都可以被两横或两竖铺满，那么只要横竖的数量都是偶数，也就是 $k$ 是偶数就行了。如果 $k$ 是奇数，必然不能铺满。\
![](https://cdn.luogu.com.cn/upload/image_hosting/c3tkanpd.png)
3. 如果 $n$ 是奇数，那么考虑先铺满一整行，再像上图一样铺满剩下 $(n-1)\times m$ 个就行了，那么，第一行会铺上 $\frac{m}{2}$ 个横向的，剩下的 $k-\frac{m}{2}$ 需要是偶数就行了。当然，$k-\frac{m}{2}$ 还必须大于等于 $0$。
4. 如果 $m$ 是奇数，那么考虑先铺满一整列，再像上图一样铺满剩下 $n\times(m-1)$ 个就行了，那么，第一行会铺上 $\frac{n}{2}$ 个横向的。剩下的 $(\frac{nm}{2}-k)-\frac{n}{2}=\frac{nm-2k-n}{2}=\frac{n(m-1)}{2}-k$ 需要是偶数就行了。因为 $\frac{n(m-1)}{2}$ 必为偶数，所以按理来说只需要判断 $k$ 是不是偶数就行了。但是，同样的，$\frac{n(m-1)}{2}-k$ 也需要大于等于 $0$，所以还需要判断 $\frac{n(m-1)}{2}$ 是否大于 $k$，才能知道是不是输出 `YES`。为了方便，那就直接使用 $\frac{n(m-1)}{2}-k$ 就行了。

分类讨论完了，下面是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m,k;
		cin>>n>>m>>k;
		if(n%2 && m%2){//最简单的情况，n*m是一个奇数，显然不行（其实不需要这个判断）
			cout<<"NO\n";//记得要换行 
		}else if(n%2){//奇数行 
			int d=k-m/2;//见上面第三条情况 
			if(d>=0 && d%2==0){
				cout<<"YeS\n";//题目中说到大小写不一样没问题，所以随便输出（ 
			}else{
				cout<<"nO\n";
			}
		}else if(m%2){//奇数列 
			int d=n/2*(m-1)-k;//见上面第四条情况 
			if(d>=0 && d%2==0){ 
				cout<<"yEs\n";
			}else{
				cout<<"No\n";
			}
		}else{//俩都是偶数 
			if(k%2==0){//第二种情况 
				cout<<"yeS\n";
			}else{
				cout<<"no\n";
			}
		} 
	}
	return 0;
}
```


---

## 作者：ncwzdlsd (赞：0)

## 题意

$t$ 组数据。对于每组数据有一个 $n \times m$ 的网格（$n$ 为网格高度，$m$ 为网格宽度，且网格的数量为偶数），要求在网格中放置多米诺骨牌，每个骨牌占据 $1\times2$ 的网格区域。对于这 $\dfrac{nm}{2}$ 个骨牌，要求正好有 $k$ 个横着放置，而剩下的 $\dfrac{nm}{2}-k$ 个竖着放置，正好铺满台面。现在要你给出对于每组 $n$, $m$ 和 $k$，是否有一种方案满足条件。如果有，输出 `YES`，反之输出 `NO`。

## 题解

这道题的考点主要是分类讨论和一些数学知识。

我们先考虑竖着放置的情况，显然，我们要每次选择两个相邻的列使得行数减少 $1$。最后，每一列的行数都必须是偶数。于是乎，我们分奇偶讨论即可。

具体的奇偶性讨论其他题解写的已经很详细了，这里不再赘述。

不知道为什么，我的代码量和其他人比少很多QwQ

主体代码如下：

```cpp
if(n%2==0) printf("%s\n",(k%2==0&&n*(m/2)>=k)?"yes":"no");
else printf("%s\n",(m%2==0&&(k-m/2)%2==0&&k>=m/2)?"yes":"no");

```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1551D1 题解



## 思路分析

显然考虑把 $k$ 个横着的都聚拢到最上面，那么每一列在除去横着的骨牌的数量后，剩下的高度应该是偶数，只有这样才能用竖着的骨牌填满这一列。

由于题目已经保证了 $2\mid nm$，因此我们可以按 $n\bmod 2,m\bmod 2$ 的值分成以下三类情况：

1. $n\bmod 2=0,m\bmod 2=1$：

此时最右边一列用竖着的骨牌填满，假如竖着的骨牌不足 $\dfrac n2$ 个则无解。

剩下的列考虑用 $2$ 个横着的骨牌组成一个 $2\times 2$ 的“方块”，这样每个“方块”填进去不会影响每一列剩下的高度的奇偶性，因此如果 $2\mid k$ 时我们可以构造一种合法的方案，同样我们也可以证明 $2\nmid k$ 时无解。

2. $n\bmod2=1,m\bmod 2=0$：

显然先把一行用横着的骨牌填满，假如横着的骨牌不足 $\dfrac m2$ 则无解。

剩下的一样考虑构造方块，类似上一种情况，当且仅当剩下的的骨牌数为偶数时有解。

3. $n\bmod2=0,m\bmod2=0$：

此时直接构造方块，有解当且仅当 $2\mid k$。

根据上面的分析，我们能够得到判定条件和构造方案，模拟即可。

时间复杂度 $\Theta(1)$。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
using namespace std;
inline void solve() {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	if(n%2==0&&m%2==1) {
		if(k>n*(m/2)) puts("NO");
		else {
			if(k%2==0) puts("YES");
			else puts("NO");	
		}
	}
	if(n%2==1&&m%2==0) {
		if(k<m/2) puts("NO");
		else {
			if((k-m/2)%2==0) puts("YES");
			else puts("NO");
		}
	}
	if(n%2==0&&m%2==0) {
		if(k%2==0) puts("YES");
		else puts("NO");
	}
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```





---

## 作者：KSToki (赞：0)

# 题目大意
问 $n\times m$ 的棋盘是否能用恰好 $k$ 个水平的多米诺骨牌（大小为 $1\times2$）全部覆盖，保证 $n\times m$ 为偶数且 $k\le \frac{nm}{2}$。区别于 D2 的地方在于，如果能，不需要输出方案。
# 题目分析
如果有一个 $2\times2$ 的空间，那么水平和竖直都能将其填满，整体就分为三种情况。

$n$ 为偶数，$m$ 为偶数是最简单的，水平的需成对存在，不然竖直的会有放不下的，即要求 $k$ 也为偶数。

$n$ 为偶数，$m$ 为奇数，第一列就必须放满竖直的，在第一种情况的基础上再判一下上界即可。

$n$ 为奇数，$m$ 为偶数，第一行就必须放满水平的，那么 $k$ 就有了下界，再判断 $k-\frac{m}{2}$ 是否为偶数即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,m,k;
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		k=read();
		if(n%2==0&&m%2==0)
		{
			if(k%2==0)
			{
				puts("YES");
			}
			else
				puts("NO");
		}
		else if(n%2==0&&m%2==1)
		{
			if(k<=m/2*n&&k%2==0)
			{
				puts("YES");
			}
			else
				puts("NO");
		}
		else
		{
			if(k>=m/2&&(k-m/2)%2==0)
			{
				puts("YES");
				
			}
			else
				puts("NO");
		}
	}
	return 0;
}

```

---

## 作者：staly (赞：0)

我们可以考虑一种最基本的情况，如果 $n$ 是偶数，$m$ 也是偶数，我们自然可以正好放置偶数张骨牌。因为我们可以把这张 $n\times m$的矩阵分成 $\frac{n}{2}\times\frac{m}{2}$ 的 $2\times 2$ 的子矩阵，对于每个子矩阵中的两张骨牌，骨牌既可以竖着放置，也可以横着放置。而放置奇数张骨牌就不行。因为如果要凑出偶数的高度，需要有若干张竖着放置的骨牌，和若干张（偶数）横着放置的骨牌。如果有奇数张骨牌，也就必然有一张骨牌无法与别的骨牌配对，也自然凑不出偶数的高度。

对于这道题除了这个最基本的情况还有两种情况，$n$ 是奇数的情况和 $m$ 是奇数的情况，对于前者，我们可以把这个矩阵分成最后一列和剩余的部分，最后一列有 $\frac{m}{2}$ 个横着的骨牌，而剩余的部分可以凑出任意偶数数目的横着的骨牌。所以我们可以证得当 $0\leq k-\frac{m}{2}\leq\frac{(n-1)m}{2}$   且 $k-\frac{m}{2}$ 为偶数时，有满足条件的方案。要凑出奇数的高度，就必须有若干张竖着放置的骨牌，和若干张（奇数）横着放置的骨牌。因为一张横着放置的骨牌的宽度为 $2$，所以至少要 $\frac{m}{2}$ 张骨牌才能使每列都满足条件，所以可以证明上述条件是正确的。对于后者，我们也可以类似地证明，当 $0\leq k \leq \frac{n(m-1)}{2}$ 且 $k$ 为偶数时，有满足条件的方案。

所以代码如下：

```cpp
// User: xinchengo
// Fear cuts deeper than swords.

#include<iostream>
using namespace std;
int t;
int n, m, k;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n >> m >> k;
        if (n % 2 == 0 && m % 2 == 0)
        { // n, m, 均为偶数，最基本的情况
            if (k % 2 == 0)
            { // 如果 k 是偶数则有解
                cout << "YES" << endl;
            }
            else
            { // 反之则无解
                cout << "NO" << endl;
            }
        }
        else if (n % 2 != 0 && m % 2 == 0)
        { // n（行数）为奇数的情况，前者
            if ((k - m / 2) % 2 == 0 && k - m / 2 >= 0 && (n - 1) * m >= k - m / 2)
            { // 前面证明的判断条件
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
        else if (n % 2 == 0 && m % 2 != 0)
        { // m（列数）为奇数的情况，后者
            if (k % 2 == 0 && n * (m - 1) / 2 >= k)
            { // 前面证明的判断条件
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
}
```


---

