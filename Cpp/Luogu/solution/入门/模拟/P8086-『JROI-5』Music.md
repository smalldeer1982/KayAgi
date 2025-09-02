# 『JROI-5』Music

## 题目背景

**请注意到并不正常的时间限制**。

**本题读入量较大，建议使用较快的读入方式。**

小 C 每年都要给丁总氪钱。

## 题目描述



小 C 喜欢在网易云听歌，她希望你能帮助她计算一下她的网易云的听歌时间。

小 C 有 $n$ 条听歌记录，每条形如 `x t`，表示小 C 听了编号为 $x$ 的音乐 $t$ 分钟。听歌时间为所有有效记录的 $t$ 的总和。

首先，如果某条记录的 $t\leq1$，那么这条记录是无效的。

其次对于某一首歌，只有**第一条有效记录会被计算**，之后重复听这首歌的记录将不会被累计到听歌时间中。


## 说明/提示

【样例解释】

第一条记录：`1 114514` ，有效记录，可以累计。

第二条记录：`2 1` ，$t\leq1$，无效记录。

第三条记录：`2 1919180` ，有效记录，可以累计。

第四条记录：`1 10` ，编号为 $1$ 的音乐在第一条记录已经累计，本条记录有效，但不能累计。

第五条记录：`3 2` ，有效记录，可以累计。

答案即为 $114514+1919180+2=2033696$。

___

对于 $40\%$ 的数据，保证 $1\leq x\leq n\leq 10^4$。

对于 $100\%$ 的数据，保证 $1\leq n\leq 10^7,1\leq x,t_i\leq 10^7$。




## 样例 #1

### 输入

```
5
1 114514
2 1
2 1919180
1 10
3 2```

### 输出

```
2033696```

## 样例 #2

### 输入

```
见附件```

### 输出

```
见附件```

# 题解

## 作者：Cocoly1990 (赞：12)

官方题解。

**A**  

考虑顺序处理每一条记录，如何处理两个约束条件是本题的核心。

首先对于 $t\leq1$  可以在读入的时候直接判断处理，忽略即可。

```c++
cin >> x >> t;
if(t <= 1) continue;
```

 那么如何判断这首歌之前是否被累加过呢？一种做法是记录下所有的记录，扫描之前的判断是否累计过。

```c++
cin >> x0 >> t0;
if(t0 <= 1) continue;
bool f = 1;
for(int j = 1; j <= cnt; j ++){
	if(x[j] == x0) f = 0;
}
if(f) {
	ans += t0; x[++ cnt] = x0; t[cnt] = t0;
}
```

容易发现上述做法的时间复杂度是 $\mathcal{O}\left(n^2\right)$ 的，可以通过 $40\%$ 的数据。那么我们何不开一个桶，记录某首歌是否又被听过？

```c++
cin >> x >> t;
if(t <= 1) continue;
if(vis[i]) continue;
else {
	ans += t;vis[x] = 1;
}
```

上述做法的时间复杂度是 $\mathcal{O}\left(n\right)$ 的，可以通过 $100\%$ 的数据。

---

## 作者：Alan_Mathison_Turing (赞：8)

蒟蒻的第一篇题解。

## 思路：
其实根源上就是一个模拟相加的问题，但是，麻烦在于，不能统计两次，这时，我们就需要用一个数组进行统计是否重复（之前已经加过）了。还有一个条件：$<1$ 的不进行计算，所以我们特判一下就好啦！

可是，为什么我的大样例过不了呢？

我在当时也遇到了这样的问题，请注意，我们的 $a$ 数组可能开小了，$a$ 数组是需要开到最大编号的，也就是 $x$，我们看到题目：$x \leq 10^7$，我们将数组开到 $10000000+1$ 就可以愉快的过掉这一题啦！

## AC CODE:
```
#include<bits/stdc++.h>
#define ll long long
#define N 9999999
using namespace std;
ll a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll n,sum=0;
	cin >> n;
	for(int i = 0 ; i < n ; i++)
	{
		ll x,t;
		cin >> x >> t;
		if(t > 1 && a[x]==0)
		{
			sum += t;
			a[x]=1;
		}
	}
	cout << sum << endl;
	return 0;
}

```
关于这篇题解，有问题尽管私信这个蒟蒻哦！

---

## 作者：SunSkydp (赞：5)

Upd on 2022.2.8：修改错别字

注意坑点：看到题目，点进[赛时公告板](https://www.luogu.com.cn/paste/lueudpd5)，有一行字:**不保证数据类型一定正确**。说明什么？不开 long long 见祖宗！

然后就是模拟，因为 $n$ 有 $10^7$，所以得使用 $\Theta(n)$ 的复杂度，那么开一个 bool 数组，记录歌曲是否听过（虽然 bool 数组开 $10^7$ 有点危险，但不会 MLE）。

最后，上代码，习惯了，所以快读快写都放上了（说实话最后一个输出好像也没快多少）。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read() {
	int x = 0; bool flag = 1; char c = getchar();
	while(c < '0' || c > '9') { if(c == '-') flag = 0; c = getchar(); }
	while(c >= '0' && c <= '9') { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
	return (flag ? x : ~(x - 1));
}
inline void write(ll x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int n; 
ll ans; 
bool islisten[10000005];
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		int x = read();
		ll t = read();
		if(t <= 1 || islisten[x]) continue;
		else ans += t, islisten[x] = true;
	}
	write(ans);
	return 0;
}

```

---

## 作者：lemon_qwq (赞：5)

~~学霸题，听阴乐~~。

## $\mathcal{Sol}$。

这道题是一道模拟题，我们只要根据题目信息枚举就可以 AC。

首先我们先看一下题目信息，大概意思为只有大于 $1$ 且是第一次听的这首歌，这首歌的时间才能算到总数里面。

第一个条件大于 $1$ 好判断，接下来我们需要知道怎么判断是不是第一次听这首歌。

我们可以建一个结构体，里面分别为两个变量，时间和标记。标记的用处是判断这首歌听没听过，接下来我们的思路清晰，就可以模拟了。

## $\mathcal{Ac\ Code}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){//官方蜜汁小快读，不加直接 TLE
	int x=0;
	bool flag=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
struct node{//神奇の结构体
	int zw;//时间
	bool vis;//标记
}a[100000005];
long long ans=0;//总时间
int n,x,t;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		x=read(),t=read();
		if(a[x].vis==0&&t>1){//判断这条记录是否合法
			a[x].vis=1;//合法的话这首歌从没听过变为听过
			a[x].zw=t;//更新这首歌的听歌时间
			ans+=t;//累计听歌时间
		}
	}
	cout<<ans;//输出总时间
	return 0;//完美の结尾
}
```

~~十年咕值一场空，抄了题解见祖宗~~。

虽然抄红题题解不会棕名，但我还是建议大家手打一遍，把题搞懂才是真谛。

---

## 作者：hjl2011 (赞：4)

### 思路 :
用桶存储听的歌。

接下来就很简单了，直接模拟即可。

### C++ Code :

```cpp
#include <cstdio>
short flag[10000005]; // 听的歌
inline long long read() {
  int x = 0,f = 1;
  char ch = getchar();
  while(ch < '0' || ch > '9') {
    if(ch == '-') f = -1;
    ch = getchar();
  }
  while(ch >= '0' && ch <= '9') {
    x = x * 10 + ch - 48;
    ch = getchar();
  }
  return x * f;
} // 貌似并没有用的快读
int main() {
  int n = read(); // 读入
  long long sum = 0LL,x,t; // 0LL 指 (long long) 0，这里为了防止溢出，详见下文
  for(int i = 1;i <= n;i++) {
    x = read(); // 读入
    t = read(); // 读入
    if(t <= 1) continue; // 无效记录
    if(flag[x]) continue; // 记录过了
    flag[x]++; // 记录
    sum += t; // 累加
  }
  printf("%lld",sum); // 输出
  return 0;
}
```

`0LL` :
指用 `long long` 初始化的 `0`，防止出现两个 `int` 形变量累加已超过 `int`，返回值还是 `int` 的情况

---

## 作者：lym12321 (赞：3)

# P8086 『JROI-5』Music  
## 题意&分析  
有 $n$ 次输入，每次输入两个整数 $x$ 和 $t$ 代表一条听歌记录。  
只需判断该听歌记录是否为 **第一条有效记录** ，即：  

- $t > 1$  
- $x$ 是第一次出现  

若记录有效，则计入答案；否则，使用 `continue` 跳过。  
为了判断 $x$ 是否在此前的输入中出现过，我们需要开一个 `bool` 数组。  
数据范围：$1 \leq n \leq 10^7,1 \leq x_i,t_i \leq 10^7$，`ans` 变量需要开 `long long`。

## Code
```cpp
#include<cstdio>

inline int read(){
    // 快速读入
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x<<3) + (x<<1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

bool vis[10000005];				// vis数组记录 x 是否出现过
long long n, x, t, ans;

int main(){
    n = read();
    for(int i = 1; i <= n; i++){
        x = read(), t = read();
        if(t <= 1) continue;	// t <= 1, 无效记录
        if(vis[x]) continue;	// x 出现过，不计入答案
        vis[x] = true;			// 记录本次 x 的出现
        ans += t;				// 将符合题意的有效记录计入答案
    }
    printf("%lld\n", ans);
    return 0;
}

```

---

## 作者：精神小伙！ (赞：3)

## 思路

首先判断记录是否有效。如果记录无效，就不用标记，也不用累加，直接跳出循环。

否则判断 $ x $ 如果没被标记过，就累加，并且标记。

最后输出累加结果即可。

## 代码

```cpp
#include<iostream>
using namespace std;
bool vis[10000010];
int x,t;
long long sum=0;//不开long long会WA 
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>x>>t;
		if(t<=1||vis[x]==1) continue;
		vis[x]=1,sum+=t;
	}
	cout<<sum<<endl;
	return 0;
}
```

---

## 作者：Phartial (赞：2)

按题意模拟即可。

坑点：只有第一条 $t>1$ 的记录才会被计算。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kV = 1e7 + 1;

int n, x, t;
LL s;
bool b[kV];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  while (n--) {
    cin >> x >> t;
    if (t > 1 && !b[x]) {  // 如果 t>1 且之前没有算过
      s += t, b[x] = 1;   // 统计答案
    }
  }
  cout << s;
  return 0;
}
```


---

## 作者：苏联小渣 (赞：2)

### 题目大意

给定 $n$ 个 $x,t$，求在保证 $t>1$ 的前提下，所有第一次出现的 $x$ 所对应的 $t$ 的和。

### 分析

非常良心的第一题，好评。

直接根据题意模拟即可。由于 $x$ 不超过 $10^7$，我们用一个数组 $a$ 判断这个 $x$ 是否出现过。发现 `t<=1` 时直接跳过判断，否则：

- 若 $x$ 未出现过，记录 $x$ 已经出现过，并加上对应的时间 $t$。

- 若 $x$ 已出现，则直接跳过即可。

最后说一句：要开 `long long`（$10^7 \times 10^7$ 肯定爆 `int` 了）

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, t, x, s, a[10000010];
inline int read(){
	int s=0, w=1; char ch = getchar();
	while (ch < '0' || ch > '9'){if (ch == '-') w=-1; ch=getchar();}
	while (ch >= '0' && ch <= '9'){s=(s<<1)+(s<<3)+ch-48; ch=getchar();}
	return s * w;
}
signed main(){
	n = read();
	for (int i=1; i<=n; i++){
		x = read(), t = read();
		if (t <= 1) continue;
		if (!a[x]) a[x] = 1, s += t;
	}
	printf ("%lld\n", s);
	return 0;
}

```

---

## 作者：skyskyCCC (赞：1)

**前言。**

一道模拟题。

**分析。**

~~首先，这道题不好想。~~

思路一：

按照题意模拟：

如果 $t$ 大于 $1$ 就标记一下，表示这是有效记录，接着继续判断，如果该记录是有效记录且是第一次出现，答案就加上该记录的时间。

这种想法是很好实现的，代码也没有什么难点，再套上题目提供的快读，代码就完成了，但是，这里有个坑，在后记中会提到。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
using namespace std;
int n,x,t;
long long ans;
int a[10000005];
inline int read(){
    int x=0;
    bool flag=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            flag=0;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+c-'0';
        c=getchar();
    }
    return (flag?x:~(x-1));
}
int main(){
    n=read();
    for (int i=1;i<=n;i++){
        x=read();
        t=read();
        if(t>1){
            a[x]++;
        }
        if(t>1&&a[x]==1){
            ans+=t;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
思路二：

按照思路一的方法延伸，可以得到一个比思路一运行时间更长，占用内存更大的代码，~~好像想复杂了。~~

当然，还是建议大家用运行效率更高的方法。

这个方法与思路一的想法大同小异，仍是判断：

判断 $1$ ： $t$ 是否小于等于 $1$ 。

判断 $2$ ：该歌曲编号是否第一次出现。

如果前两项中第一项为真，或第二项为假，那么跳出该次循环，否则将 $timee$ 数组的第 $x$ 项设为该记录的时间，听歌记录设为该记录的编号。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,x,t;
int gqjl[10000005],timee[10000005];
long long ans;
int sum;
inline int read()
{
    int x=0;
    bool flag=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-')
            flag=0;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+c-'0';
        c=getchar();
    }
    return (flag?x:~(x-1));
}
int main(){
    ios::sync_with_stdio(false);
    n=read();
    for(int i=1;i<=n;i++){
        x=read();
        t=read();
        if(t<=1){
            continue;
        }
        if(timee[x]){
            continue;
        }
        timee[x]=t;
        gqjl[++sum]=x;
    }
    for(int i=1;i<=sum;i++){
        ans+=timee[gqjl[i]];
    }
    cout<<ans<<endl;
    return 0;
}
```
**后记。**

问题 $1$ :

为什么答案要开 ```long long``` ？

首先，题目中要求 $t$ 与 $n$ 小于等于十的七次方，如果我们设数据中的 $t$ 与 $n$ 为十的七次方，且都为有效记录，那么答案就是十的十四次方，超出了  ```int``` 的范围，所以要开 ``` long long``` 。

问题 $2$ ：

为什么数组 $timee$ 多加了一个 $e$ ？

因为 ```time``` 是 ```C++``` 的一个“敏感词”。


大家如有疑问，请在评论区提出，我会尽力解答的。
 

---

## 作者：Eason_AC (赞：1)

## Content
你在网易云有 $n$ 次听歌记录，每次听歌记录形如 `x t`，表示你听了编号为 $x$ 的歌 $t$ 分钟。现在你想统计这些听歌记录。对于某次听歌记录，不会将其统计进去，当且仅当 $t\leqslant 1$ 或者编号为 $x$ 的歌在之前已经被统计过。求统计进去的听歌记录的听歌时间总和。

**数据范围：$1\leqslant n,x,t_i\leqslant 10^7$。**
## Solution
简单的模拟题。

我们开个桶用来判断特定编号的歌曲是否有已经统计进去的听歌记录。边输入每次听歌记录的信息，边判断是否能够统计进去，直接对所有统计进去的听歌记录的听歌时间累加进答案即可。

注意两点：

- $x$ 的最大值可能到 $10^7$，直接用 `int` 数组作为桶的话会超出空间限制，建议使用 `bool` 数组作为桶。
- 答案的最大值可能到 $10^7\cdot 10^7=10^{14}$，因此要开 `long long`。

## Code
```cpp
namespace Solution {
	const int N = 1e7 + 7;
	int n, x, t; bool vis[N];
	ll ans;
	
	iv Main() {
		read(n);
		F(int, i, 1, n) {
			read(x, t);
			if(!vis[x] && t > 1) ans += t, vis[x] = 1;
		}
		write(ans);
		return;
	}
}
```

---

## 作者：rai1gun (赞：1)

#### 1.题目思路
我们这道题考虑用哈希法来解决。

将每一个 $x$ 看做一个桶，在遍历的过程中只需判断这个桶有没有数字即可。最后再累加一遍即可通过本题。

#### 2.赛时代码

```c++
#include<iostream>
using namespace std;
const int N = 1e7+5;
long long h[N],x,t;
inline long long read(){
	long long now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
int main(){
	long long T,ans;
	T=read();
	while(T--){
		x=read(),t=read();
		if(h[x]==0 && t>1)h[x]=t,ans+=t;
	}
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：Nygglatho (赞：1)

模拟，设第 $i$ 首歌为 $p_i$。

每一次，我们都先判断，如果 $t > 1$ 并且不是第一条有效记录，那么听歌时间 $s$ 就加上 $t$。

至于如何判断是否是第一条有效记录，可以判断完成以后，把 $p_i$ 变成真，代表已经有有效记录了，以后碰到歌时，判断 $p_i$ 是否为真就行了。

Code:
```cpp
#include <cstdio>

int p[10000001], N;
long long s;
inline int rd() {
	int x=0;
	bool flag=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
//来自快读模板 
int main() {
//	freopen ("big_sample.in", "r", stdin);
//	freopen ("big_sample.txt", "w", stdout);
	N = rd();
	for (int i = 1; i <= N; ++i) {
		int x = rd(), t = rd();
		if (t > 1 && p[x] == 0) {
			p[x] = 1;//为真
			s += t;
		}
	}
	printf ("%lld", s);
} 
```

---

## 作者：瀛洲仙子 (赞：1)

### 说明
本题解使用 Python 提交，因为预计将会有很多人使用 C/C++ 提交题解。
### 题目简述
主人公很喜欢听歌，在音乐软件里他有很多条听歌记录。
第 $i$ 条记录包含听了第 $x$ 首音乐 $t$ 分钟。注意：
* 如果一条记录的 $t$ 属性 $\le 1$，那么这条记录无效。
* 如果两条听歌记录的歌曲编号重复，只记录第一次听到时间。    
最终要求出听歌有效记录总时间。
### 思路分析
首先定义列表存储听过哪些歌。
```python
song=[]
```
接下来定义总时间，输入听歌记录数量。
```python
sm=0
dt=input()
dt=int(dt)
```
然后循环输入记录。
```python
while dt:
		dt=dt-1
        rec=input()
        rec=rec.split()
        rec[0]=int(rec[0])
        rec[1]=int(rec[1])
```
下一步时很关键的特判，如果 $t \le 1$ 或音乐已经被听过，那么跳过。
```python
if rec[1]<=1:
		continue
if rec[0] in song:
		continue
```
如果不符合特判，那么将进行一系列操作，我解释一下。
* 将时间总和增加 $t$。
* 将 $x$ 添加到已经听过的歌的列表里。
具体代码如下。
```python
sm=sm+rec[1]
song.append(rec[0])
```
最后跳出循环，输出听歌时间总和。
```python
print(sm)
```
### 代码分享
根据以上步骤，无注释代码如下。
```python
song=[]
sm=0
dt=input()
dt=int(dt)
while dt:
		dt=dt-1
        rec=input()
        rec=rec.split()
        rec[0]=int(rec[0])
        rec[1]=int(rec[1])
		if rec[1]<=1:
				continue
		if rec[0] in song:
				continue
		sm=sm+rec[1]
		song.append(rec[0])
print(sm)
```
**珍爱生命，远离抄袭！！**

---

## 作者：oddy (赞：0)

简单题，不简述题意了~~其实是因为懒~~。

## Analysis

开一个 `bool` 数组用于记录这首歌是否听过。

其他的地方直接模拟就可以。

这道题虽然时限只有 $500 \  \text{ms}$，但是用 `scanf` 也能过。

坑点：会爆 `int`，所以要开 `long long`。

## Code

```cpp
#include <cstdio>

bool a[10000001];

int main() {
    long long n, x, t, ans = 0;
    for(scanf("%lld", &n); n; n--) {
        scanf("%lld%lld", &x, &t);
        if(a[x] || t <= 1) continue;
        a[x] = true;
        ans += t;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：JerryTcl (赞：0)

注意到题目中保证 $x\le10^7$，于是可以开桶记录数据

具体而言，定义一个长为 $10^7+1$ 的数组，初始化为 $0$

当输入 $x$ 与 $t$ 时，若 $arr[x]\le 1$ 令 $arr[x]=t$

最后遍历 $1$ 到 $10^7$，若 $arr[x]\ge1$，则累加到 $ans$

---

## 作者：return_CE (赞：0)

## 题意
有 $ n $ 条记录，$ x $ 为歌曲序号，$ t $ 为听歌时间。首先，如果某条记录的 $ t > 1$，那么这条记录是有效的。其次对于某一首歌，只有**第一条有效记录**会被计算，之后重复听这首歌的记录将不会被累计到听歌时间中。
## 思路
首先明确哪些记录是有效的的。设总共听歌的时间为 $ ans $。如果第 $ i $ 条记录是有效的，并且是第 $ x $ 首歌的第一条有效记录，那么它就是可以记录的。 $ ans + = t$，并且将第 $ x $ 首歌曲标记为已听，如果之后有第 $ x $ 首的记录则都将无效
## 实现
用布尔数组记录每一首歌曲是否已经被听过，如果第 $ i $ 条记录是有效的并且是可以记录的，就把 $ a[x] $
修改为 $ 1 $，代表已听。数据量较大，尽量不要用 cin，快读是优选。

~~最后，希望可以过。~~
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,t,x;
ll ans;
bool a[10000005];
inline int read()
{
	int x=0;
	bool flag=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		x=read();t=read();
		if(!a[x]&&t>1){
			ans+=t;
			a[x]=1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Elgo87 (赞：0)

数据人题解。

微型模拟题，可以用一个数组 $v_i$ 记录第 $i$ 条歌是否被听过，然后按题意模拟即可。

参考代码（[AC 记录](https://www.luogu.com.cn/record/68461872)）：

```cpp
# include <bits/stdc++.h>
# define max(a,b) ((a)>(b) ? (a) : (b))
# define min(a,b) ((a)<(b) ? (a) : (b))
# define abs(a,b) ((a)> 0  ? (a) : -(a))
# define endl putchar('\n')
# define space putchar(' ');
# define int long long
using namespace std;

inline int read() {
	int num = 0, nev = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') nev = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { num = (num<<1) + (num<<3) + (ch ^ 48); ch = getchar(); }
	return num * nev;
}

inline void print(const int& x) {
	if (x < 0) { putchar('-'); print(-x); return ; }
	if (x < 10) { putchar(x+'0'); return ;}
	print(x/10), putchar(x%10 + '0'); return ;
}


bool v[10000005];
signed main()
{
	int n = read(), res = 0;
	for (int i = 1; i <= n; i ++)
	{
		int x = read(), t = read();
		if ( t > 1 && !v[x] ) res += t, v[x] = true;
	}

	print(res);
	return 0;
}

```



---

## 作者：expnoi (赞：0)

题目很简单，只需要判断 ```x``` 是否出现过和 ```t``` 是否等于 ```1``` 即可。

我们可以用一个数组来记录 ```x``` 是否出现过即可。

用 ```vis[x]=1``` 来标记 ```x``` 出现过。

最后在合法的情况下，累加求和即可。

下面是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int &x)
{
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
	x=s*w;
	return;
}
int n,s,t;
long long sum=0;
bool vis[10000001];
int main()
{
	read(n);
	while(n--)
	{
		read(s);
		read(t);
		if(t==1||vis[s])continue;
		else vis[s]=1,sum+=t;
	}
	printf("%lld",sum);
}
```


---

## 作者：hyc1026 (赞：0)

这道题根本不用快读，也不用什么高深的算法……

直接模拟就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;

bool vis[10000001]; //用以记录这首歌是否听过

int main()
{
    int n;
    cin >> n;
    long long sum = 0; //记录总时间的变量，不开longlong见祖宗
    for(int N=1; N<=n; N++) //输入n遍
    {
        int x,t;
        cin >> x >> t;
        if(vis[x]) continue; //如果听过，跳过
        if(t <= 1) continue; //如果时间不足，跳过
        sum += t; //没跳过，OK，记入总时间
        vis[x] = true; //标记这首歌听过
    }
    cout << sum << endl; //输出即可
}
```

---

## 作者：Unnamed114514 (赞：0)

题意很简单，直接模拟即可，注意输入数据规模大。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+5;
int n,x,t;
bool vis[maxn];//标记每首歌是否被听过
long long ans;//注意开 long long
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&x,&t);
		if(t>1&&!vis[x]){//有效信息
			vis[x]=1;//标记
			ans+=t;//更新答案
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：lsj2009 (赞：0)

[更好的阅读体验。](https://www.luogu.com.cn/blog/lvsiji/p8086-code)

## 题目大意
<https://www.luogu.com.cn/problem/P8086>。
## 思路
$t\le10^7$，刚好可以用一个 ``bool`` 数组或 ``bitset`` 装下，我们用 $a_i=0$ 表示编号 $i$ 的音乐没有出现过或出现过但 $t\le1$；而用 $a_i=1$ 表示编号 $i$ 的音乐出现过且 $t>1$。

则每次遇见 ``x t`` 的指令，如

- $a_x=0$ 且 $t>1$ 则将答案累加 $t$，并标注 $a_x=1$；
- $a_x=1$ 或 $t=1$，跳过该指令。

## AC code:
```cpp
#include<bits/stdc++.h>
#define int long long //十年 OI 一场空，不开 long long 见祖宗
using namespace std;
const int N=1e7+5;
bool used[N];
main() {
	int n,tot=0;
    cin>>n;
	while(n--) {
		int x,t;
        cin>>x>>t;
		if(!used[x]&&t>1) //a[x]=0 且 t>1 则该指令合法
			used[x]=true,tot+=t;
	}
	cout<<tot;
	return 1;
}
```

完美撒花！

---

## 作者：C_S_L (赞：0)

按照题意模拟即可。

用 bool 数组记录下每首歌是否听过。

如果这首歌没有听过，且时间 $t>1$ ，那么就将 $t$ 加到答案中。

记得开 long long 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10000010;
int n,x;
bool a[N];
long long t,ans;
int main() {
	scanf("%d",&n);
	while(n--) {
		scanf("%d%lld",&x,&t);
		if(a[x]||t<=1) {
			continue;
		}
		a[x]=1;
		ans+=t;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：happybob (赞：0)

传送门：[P8086 『JROI-5』Music](https://www.luogu.com.cn/problem/P8086)

# 题意

有 $n$ 条信息，每条信息形如 `x t`，若 $t \ge 2$ 且 $x$ 没有在以前的信息中出现过，则累加 $t$，否则不处理。问累加和为多少。

注意如果某个 $t \le 1$ 那么 $x$ 不被算为历史。也就是说例如：

```
3 1
3 2
```
$2$ 仍然会被累加，而 $1$ 不会，第一次的 `3 1` 不被记录成历史。

# 解法

模拟。用一个 `bool` 数组记录下某个 `x` 是否有出现过，没有出现且 $t \ge 2$ 则累加并更新数组的状态。

数据有点大，开快读好一些。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e7 + 5;
bool a[N];

inline int read()
{
	char ch = getchar();
	int b = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9')
	{
		b = (b << 1) + (b << 3) + (ch ^ 48);
		ch = getchar();
	}
	return b;
}

signed main()
{
	int n, x, t, ans = 0;
	n = read();
	while (n--)
	{
		x = read(), t = read();
		if (a[x] || t <= 1) continue;
		a[x] = true;
		ans += t; 
	}
	printf("%lld\n", ans);
	return 0;
} 
```
不开 O2 耗时 $263$ 毫秒。

---

## 作者：囧仙 (赞：0)

## 题解

使用循环语句依次读入每条记录。首先判断记录是否合法（只需要判断 $t$ 的大小。若 $t\le 1$ 直接忽略该条记录），再判断是否是编号为 $x$ 的音乐的第一条记录。开一个布尔型数组 $B$，若 $B_x=\mathrm{true}$ 则表示已有编号为 $x$ 的有效记录，否则没有。

因为本题 $x_i\le 10^7$，内存限制为 $128\text{MB}$，因此 $B$ 数组可以存的下。

但是这题由于输入量达到了 $10^7$ 个 $\text{int}$ 类型的整数，因此需要快读。一般快读的写法是不断读取字符，直到读取到第一个数字字符，存到变量 $r$ 中（$r\gets c-\verb!`0'!$）；接着不断读取数字字符，直到读取到非数字字符/文件结束，并且不断更新 $r$ 为 $10\times r+c-\verb!`0'!$。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=1e7+3;
bool V[MAXN]; i64 ans;
int n;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}

int main(){
    
    n=qread(); up(1,n,i){
        int x=qread(),t=qread(); if(t<=1) continue;
        if(!V[x]) ans+=t,V[x]=true;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：3a51_ (赞：0)

### 题目大意

给你 $n$ 组数据，每组数据包含两个正整数 $x,t$。最终我们要求对于所有 $x$ 其第一次对应出现的 $t$ 的总和。

### 思路分析

我们可以开一个数组 $a$ 来记录出现的值。每读入进来一条数据 $x,t$，判断一下 $a_x$ 是否为 $0$ 以及 $t$ 是否 $\le 1$。如果 $a_x \ne 0$ 且 $t \nleq 1$ 的话，就将 $a_x$ 赋值为 $t$。

### 温馨提示

题目说了，输入量较大（指 $4 \times 10^6$），要用快读。

### code

```cpp
#include<iostream>
using namespace std;
long long a[10000005],n,x,y,ans;
void read(long long &x)
{
    x=0;
    char ch=' ';
    while(ch>'9' || ch<'0')
		ch=getchar();
    while(ch>='0' && ch<='9')
    {
		x=x*10+ch-'0';
		ch=getchar();
    }
    return;
}
void print(long long x)
{
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
    return;
}
int main()
{
	read(n);
	for(long long i=1;i<=n;i++)
	{
		read(x);read(y);
		if(a[x] || y<=1)
			continue;
		a[x]=y;
	}
	for(long long i=1;i<=10000004;i++)
		ans+=a[i];
	print(ans);
	return 0;
}
```

---

