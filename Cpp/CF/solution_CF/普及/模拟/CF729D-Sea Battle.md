# Sea Battle

## 题目描述

Galya is playing one-dimensional Sea Battle on a $ 1×n $ grid. In this game $ a $ ships are placed on the grid. Each of the ships consists of $ b $ consecutive cells. No cell can be part of two ships, however, the ships can touch each other.

Galya doesn't know the ships location. She can shoot to some cells and after each shot she is told if that cell was a part of some ship (this case is called "hit") or not (this case is called "miss").

Galya has already made $ k $ shots, all of them were misses.

Your task is to calculate the minimum number of cells such that if Galya shoot at all of them, she would hit at least one ship.

It is guaranteed that there is at least one valid ships placement.

## 说明/提示

There is one ship in the first sample. It can be either to the left or to the right from the shot Galya has already made (the "1" character). So, it is necessary to make two shots: one at the left part, and one at the right part.

## 样例 #1

### 输入

```
5 1 2 1
00100
```

### 输出

```
2
4 2
```

## 样例 #2

### 输入

```
13 3 2 3
1000000010001
```

### 输出

```
2
7 11
```

# 题解

## 作者：Yizhixiaoyun (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF729D)

## 题目分析

本题做法为**贪心**。

考虑使用一个 $cnt$ ，记录所有连续 $0$ 的个数，每次碰到 $1$ 就清空 $cnt$。

比较 $cnt$ 与 $b$ 的大小。如果 $cnt \ge b + 1$ ，则将其位置插入数组。

最后可以找到 $ans$ 个位置。但是由于只需要炸到 $1$ 艘船即可，因此剩下的 $a - 1$ 艘船是不必要的，因此输出 $ans - (a - 1)$ 即可。

## 贴上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
int n,a,b,k;
int f[maxn];
int cnt,ans;
string s;
inline void init(){
	cin>>n>>a>>b>>k;
	cin>>s;
//	s=" "+s;
}
inline void duel(){
	for(register int i=0;i<n;++i){
        if(s[i]=='1'){
            cnt=0;
            continue;
        }
        cnt++;
        if(cnt==b){
        	f[++ans]=i+1;cnt=0;
		}
	}
	ans-=a-1;	
}
inline void print(){
	cout<<ans<<endl;
	for(register int i=1;i<=ans;++i) cout<<f[i]<<" ";
}
int main(){
	init();
	duel();
	print();
}
```

---

## 作者：_ouhsnaijgnat_ (赞：4)

这道题真坑。写完代码后样例老不过，跟题解区的大佬一对也一点问题都没有，一提交居然过了。~~所以样例有什么用。~~

# 思路

我的思路跟大佬们差不多，我来写一篇较为详细的题解。

先来分析一个样例。

```
9 1 4 2
100000001
```

这个样例有 $9$ 个格子，有 $1$ 艘船，船的长度为 $4$。

输出很容易看出来，在 $5$ 这个格子发射最优，因为这样后面的 $3$ 个格子也可以被探测出来，相当于一发子弹探测了 $7$ 个格子！

可以证明，在连续的 $0$ 里（长度 $>b$）一定在第 $b$ 个格子发射一发，因为这样可以最大的将后面尽可能多的格子也给探测出来，跟上面的样例是一样的。

因为题目的意思是最少探测出 $1$ 条船，所以算出的子弹数要将探测那 $a-1$ 艘船给去掉。

上代码。

# 代码
```
#include<bits/stdc++.h>
#define maxn 10000010//宏定义
using namespace std;
int n,a,b,k,l,sum,ans[200005],cnt;//
string s;
int main(){
	cin>>n>>a>>b>>k>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='0'){//连续的0
			sum++;
			if(sum==b){//①
				sum=0;
				ans[++cnt]=i+1;
			}
		}else sum=0;//②
	}
	cnt-=a-1;//③
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++)//全部输出出来
		cout<<ans[i]<<' ';
    return 0;  
}
```

# 注释

1. 此时是第 $b$ 个格子，上面说过了，在这个格子发射最优。

2. 这里很坑，因为如果是 $1$ 时，这段 $0$ 就结束了，应该清零。

3. 同上，只需要知道 $1$ 艘船就行了，所以将另外的 $a-1$ 发子弹来探测别的船的给去掉。

感谢观看！

---

## 作者：追梦之鲸 (赞：4)

本蒟蒻的第$012$篇题解。

[经典回顾CF729D](https://www.luogu.com.cn/problem/CF729D)

我自己理解的输入格式和输出格式：

### 输入格式

第一行读入四个数：$n,a,b,k$

第二行读入一个长度为 $n$ 的字符串，包含 $0,1$。

### 输出格式

第一行一个数 $x$，表示最少需要打几枪。

接下来 $x$ 个数，表示分别打在哪里

## 思路

我们需要没连续出现 $b$ 个 $0$ 就要炸一下，要不然就会有漏网之鱼，并且要炸最后一个位置，因为炸是最划算的。

因为假设 $b=3$，有 $8$ 个 $0$，那么每次炸最后一个位置炸两下就能搞定，但是不炸最后一个位置就要炸三次。

## 注意事项

- 数组一定要开大，否则会 $\color{purple}RE$。（我就在这个点上死了一次）

- 遇到 $1$ 要清零啊啊啊……（同上）

- 只需炸到一艘船即可，所以最后答案要减 $a-1$ 次。

### Code1：

```c
#include<bits/stdc++.h>
using namespace std;
string s;
int n,a,b,k,ans,x[220000],dan;//ans表示答案，x表示位置，dan是计数滴
//坑点1
int main()
{
	cin>>n>>a>>b>>k>>s;//陋习
	for(int i=0;i<n;i++)
	{
		if(s[i]=='0')//遇到0
		{
			dan++;
			if(dan==b)//开始判断
			{
				dan=0;//也要清零欧
				ans++;
				x[ans]=i+1;//记录答案，还有一定要加一，因为
			}
		}
		if(s[i]=='1') dan=0;//遇到1一定要清零！
        	//坑点2
	}
	ans-=a-1;//减a-1!
        //坑点3
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)cout<<x[i]<<" ";
	return 0;//结束了
}
```

### Code2:

只是边读边判断而已，但能节省许多空间和时间

```c
#include<bits/stdc++.h>
using namespace std;
char s;
int n,a,b,k,ans,x[220000],dan;

int main()
{
	cin>>n>>a>>b>>k;
	getchar();
	for(int i=1;i<=n;i++)
	{
		s=getchar();
		if(s=='0')
		{
			dan++;
			if(dan==b)
			{
				dan=0;
				ans++;
				x[ans]=i;
			}
		}
		if(s=='1') dan=0;
	}
	ans-=a-1;
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)cout<<x[i]<<" ";
	return 0;
}
```


最后蟹蟹管理大大的审核Orz

---

## 作者：AC_love (赞：3)

写的比较~~啰嗦~~详细，相对而言更适合小白阅读。

乍一眼看了一下，这道题很符合最不利原则。

最不利原则就是从最糟糕的情况（也就是极端情况）出发考虑问题。

我们举一个例子：

> 十个抽屉，五个里装有苹果，问：最少打开几个抽屉才能确保一定找到苹果？

根据最不利原则，我们从最糟糕的情况考虑，最糟糕的情况也就是前五次开盒发现都是空空如也，这时我们已经排除了所有空的抽屉，那么剩下的五个就都是有苹果的抽屉了，随便开一个就好了。

也就是说，如果 $p$ 个抽屉里装有 $a$ 个苹果，我们需要 $p - a$ 次开盒来排除所有空的抽屉，再用一次开盒来找到苹果，总的次数应该为 $p - a + 1$ 次。

所以至少要开六次才能确保一定找到苹果。

这和这道题又有什么关系呢？

分析一下题意，每两个射击的位置之间（或一个射击的位置到边缘）都有一段间隔，如果这段间隔足够长，足以容纳至少一条船，它就可以看做装苹果的抽屉，船就是装在抽屉里的苹果。

那么我们相当于把问题转化成了：

```
p 个抽屉里有 a 个苹果，每个抽屉至多装一个苹果，问：至少打开几个抽屉才能找到一个苹果？
```

这个问题我们在上面已经解决过了，答案是 $p - a + 1$ 次。

所以解决这个问题的大致思路我们就理清了，接下来就是细节问题：

首先，如何确定抽屉数量 $p$ 呢？

显而易见地，如果一个空隙能容纳且仅能容纳一条船，这个空隙就可以看做一个抽屉。

比如样例 1：

```
5 1 2 1
00100
```

显然，第一段空隙长度为 $2$，船的长度恰好也为 $2$，那么可以把第一段空隙视为一个抽屉。

同理，第二段空隙也可以看做一个抽屉，那么对于这组样例，一共有两个抽屉。

那么我们再来看看样例 2：

```
13 3 2 3
1000000010001
```

第一段空隙长度为 $7$，而船的长度为 $2$，根据~~高等数学~~小学数学知识，第一段空隙里至多可以容纳三艘船。

所以，理所应当地，我们把第一段空隙视为三个抽屉。

我们更细致地看待这个过程，首先我们遍历了这个空隙的前两个位置，发现已经足以容纳一艘船，那么这两个位置就被我们视作了一个抽屉，然后我们继续向后遍历。

所以我们只需要在遍历的时候，每次遇到一个 $0$ 就把间隙长度增加，当间隙长度等于 $b$ 的时候，我们在这里放一个抽屉，再将间隙长度归零即可。

解决了这个问题，我们再来看第二个细节，如何实现“打开抽屉”这个操作？

我们回忆一下打开抽屉的目的是什么？其实就是确定一个抽屉是否为空。

也就是说，在执行打开抽屉这个操作之后，我们一定要确保我们已经知道了当前抽屉的状态。

回到题目中，我举个例子：

有一段空隙长为 $6$，船的长度是 $4$，那么现在我们要确定这个空隙中有没有船，我们应当如何确定呢？

我们用问号代表一个位置有没有船是不确定的。

```
??????
```

假如头脑不太聪明的小明来解决这个问题，他先是射击了一下最左面的位置，发现没有，于是情况变成了这样：

```
X?????
```

显然，对于后面五个位置，情况仍然是不确定的，因为这一段的长度依然超过了船的长度，这一段依然可以作为一个抽屉，塞下一艘船。

相当于把抽屉打开一个缝，透过这个缝去看看里面有没有苹果，但是一个缝终究还是太小了，要打开你就大大方方打开啊，开个缝你能看见啥啊。

很显然，一个合适的解决问题的方案是在第四个位置射击，假如没有船，情况就变成了这样：

```
???X??
```

此时我们发现，虽然两边我们没有射击，但是它们的长度已经不足以容纳一艘船的长度了，所以可以确定，两边都没有船。

如果我们换到第五个位置射击又会怎么样呢？我们发现，射击之后，即使当前位置没有船，前面的四个位置也足以容纳一艘船了，相当于我们这次射击就是无效的。

所以，当我们已经确定了一个抽屉的位置时，直接到这个抽屉的第 $b$ 位射击就能确定这个抽屉是否为空了。

因为一个抽屉的长度最长为 $2b - 1$ （因为当一个空隙长为 $2b$ 时，这个空隙将被划分为两个长度为 $b$ 的抽屉），所以在第 $b$ 位射击一定可以同时兼顾前 $b$ 个位置和后 $b$ 个位置的情况，所以针对任何一个抽屉，我们只需在第 $b$ 位设计一次即可解决问题。

细节完善完成，接下来就是代码实现了：

```cpp

#include <bits/stdc++.h>
using namespace std;
int n, a, b, k;
string s;
int itv;	// interval 用来 
int cnt;	// cnt 用来存储抽屉个数 
int ct[1919810];	// ct 存储每个抽屉的起点 
int main()
{
	cin >> n >> a >> b >> k;
	cin >> s;
	for(int i = 0; i < n; i ++)
	{
		if(s[i] != '0')
			itv = 0;
			// 很好理解，如果当前这个位置已经射击过的话，之前的间隙长度就可以归零了
		else
			itv ++;
			// 反之，间隙长度 +1
		
		if((s[i] == '0' && s[i - 1] == '1') || (i == 0 && s[i] == '0'))
			// 这里的判断条件式如果一个位置没射击过但前一个位置设计过，那么将这个点存入起点数组中
			ct[cnt] = i;
			// 有的同学可能会担心这样会不会把一些不符合条件的点存进来，其实不需要有这种顾虑
			// 因为只要不符合条件 cnt 就不会增加
			// 这种情况下即使不符合情况的点被加入了数组中，也会被后来符合情况的点覆盖掉
			// 一定还有人想问了，那假如后来没有符合情况的点呢？
			// 好问题，我会在下面解释
		
		if(itv >= b)
		// 如果当前这个点的间隔已经等于 b 了
		{
			cnt ++;
			// 抽屉数增加
			s[i] = '1';
			// 由于我们在判断起点条件的时候要求起点的前一位必须是 1，所以为了判断下个起点方便，我们直接把这个抽屉的终点设置成 1
			// 理论上讲，这和 ct[cnt] = i + 1 是等价的
			itv = 0;
			// 将间隔设为 0
		}
	}
	cout << cnt - a + 1 << endl;
	for(int i = 0; i < cnt - a + 1; i = i + 1)
		cout << ct[i] + b << " ";
	// 上面的那个问题的解释在这里
	// 看到这个输出，想必你也知道刚才那个问题的答案了
	// 没错，输出的时候最大不能到 cnt - a + 1 处
	// 而 a 最小为 1，所以第 cnt 个位置的起点一定是输入不到的
	// 这样的话，即使这一位不合法也无所谓
	return 0;
}
```

完美 ~ 撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：wangyutian578 (赞：1)

#  CF729D Sea Battle 题解
## 思路
使用计数器 $cnt$ 统计，遇到 $0$ 就加一，否则清零。

然后判断 $cnt$ 和 $n$ 是否相等，如果相等，那么存入一个新数组。

最后由于只需要炸到一艘船，所以输出答案减去 $(a - 1)$。
## AC代码
```cpp
//上文已解释清楚，不在此多作解释
#include <bits/stdc++.h>
#define MX 1000000
using namespace std;
char s[MX + 10];
int f[MX + 10];
int main()
{
	int n,a,b,k,i,cnt = 0,ans = 0;
	cin >> n >> a >> b >> k >> s;
	for(i = 0;i < n;i++)
	{
		if(s[i] == '0')
		{
			cnt++;;
			if(cnt == b)
			{
				f[++ans] = i + 1;
				cnt = 0;
			}
		}
		else
		{
			cnt = 0;
		}
	}
	ans = ans - a + 1;
	cout << ans << endl;
	for(i = 1;i <= ans;i++)
	{
		cout << f[i] << ' ';
	}
	cout << endl;
	return 0;
}
```

---

## 作者：User757711 (赞：1)

# [CF729D Sea Battle](https://www.luogu.com.cn/problem/CF729D)题解
### 题目大意
题目翻译已经足够明确，在此不再赘述。
### 思路分析
每碰到一个 $0$ 计数器就加一。

如果碰到 $1$ 计数器就清零。

如果 $b \leq cnt$ 就把当前位置存入答案数组，计数器清零，射击数加一。

因为只需要击中 $1$ 条船，所以有 $a-1$ 艘船是不需要击中的，所以最后输出答案为 $ans-a+1$。
### 最后，附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int id[200050]; //id数组储存射击位置
int cnt,ans;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,a,b,k;
	cin>>n>>a>>b>>k; //k没用
	for(int i=1;i<=n;i++)
	{
		char c;
		cin>>c; //边输入便判断
		if(c=='0')
		{
			cnt++;
			if(cnt==b)
			{
				cnt=0; //计数器清零
				id[++ans]=i; //储存射击位置
			}
		}
		else
		{
			cnt=0; //计数器清零
		}
	}
	cout<<ans-a+1<<endl; //输出答案个数
	for(int i=1;i<=ans-a+1;i++)
	{
		cout<<id[i]<<" "; //输出答案
	}
	return 0;
}
```
### The End！

---

## 作者：fish_shit (赞：0)

## 思路
不难发现，为了让射击次数更少，我们只需要在连续未射击的部分每过 $b$ 个就射击一次。因为射这一次就能保证前面的部分如果有船就能射到，后面的部分需要射的次数也会少。

## 实现
十分简单，用一个计数器模拟一下过程就可以了。如果这个位置被射过，就将计数器清零；如果计数器达到了 $b$，就将该位置存在答案数组里面，并清零计数器；否则就将计数器加 $1$。

注意：最后输出最小射击次数是存在数组里的数的个数减去 $a - 1$，因为只需要击中 $1$ 条船。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int shoot[210000],zero,cnt,n,a,b,k;
int main(){
	char l;
	cin>>n>>a>>b>>k;
	for(int i=1;i<=n;i++){
		cin>>l;
		if(l=='1'){//如果是1就跳过 
			zero=0;
			continue;
		}	
		zero++;
		if(zero==b){//当计数器达到b时，存入答案 
			zero=0;
			shoot[++cnt]=i;
		}
	}
	cnt=cnt-(a-1);//因为只需要找出一艘船，所以减掉（a-1) 
	cout<<cnt<<'\n';
	for(int i=1;i<=cnt;i++){//输出答案 
		cout<<shoot[i]<<' ';
	}
	return 0;
}
```

---

## 作者：_775spacing747_ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF729D)
## 提醒：
这道题样例没过没事，题目说如果有多个答案，您可以打印其中任何一个。
## 解题思路：
**算法**：贪心

这道题我们需要一个计数器 $s$ 来统计连续 $0$ 的个数，因为每出现连续 $b$ 个 $0$ 我们就要记录，否则就会漏掉船只。
## 贪心证明：
可以自己举个例子试试。
## 注意事项：
由于题目让我们为求至少射击中一条船，所以输出的数组的长度是长度减去 $a-1$。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int v[200005];
int main()
{
	int n,a,b,ss,l,t=0,k=0;//t是记录0的个数，k是数组的长度
	string s;
	cin>>n>>a>>b>>ss>>s;//输入
	for(int i=0;i<s.size();i++)//遍历
		if(s[i]=='0')//判断是否为0
		{
			t++;//计数器++
			if(t==b)//等于b的话保存
			{
				v[++k]=i+1;//保存下标，由于i从0开始，要+1
				t=0;//清空很重要！！！
			}
		}
		else t=0;//清零
	k-=a-1;//减去
	cout<<k<<"\n";//输出
	for(int i=1;i<=k;i++)cout<<v[i]<<" ";//输出
   return 0;
}
```

---

## 作者：_Flame_ (赞：0)

## 思路

乍一看感觉很复杂，实际上并没有很难，用一个贪心加模拟的思路就可以解决。

我们可以模拟炸船的过程，用一个 $x$ 来表示当前打枪次数，对于每一个位置，只要它没有船，我们就炸一下，当连续炸了 $b$ 次后，肯定就可以炸到一条船，此时将 $x$ 清零，记录位置即可。

当遇到有船的位置时，则将 $x$ 清零，开始下一轮计数即可。

最后找到 $k$ 个位置，由于只要炸到一条船，输出 $k$ 与 $a-1$ 的差就行。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,a,b,k;
int a_ns[5000010];
int x;
int k;
string s; 

signed main(){
	cin>>n>>a>>b>>k;
	cin>>s;
	s=" "+s;
	for(int i=1;i<=n;i++){
		if(s[i]=='0'){
			x++;
			if(x==b){
				x=0;
				k++;
				a_ns[k]=i+1;
			}
		}
		if(s[i]=='1'){
			x=0;
		} 
	}
	cout<<k-a+1<<endl;
	for(int i=1;i<=k-a+1;i++){
		cout<<a_ns[i]<<" ";
	}
	return 0;
}

```

---

## 作者：codeLJH114514 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF729D)

# $\textbf{Problem}$

从前有 $n$ 个格子，$a$ 条船。每条船占 $b$ 个连续格子，没有一个格子属于两艘或以上的船。Galya 往 $k$ 个地方射击都没有射到船，请问至少需要再射几发才能保证打到船，输出打的位置（如果有很多解，输出任意一个）。

# $\textbf{Solution}$

我们设 $A = \sum \frac{\scriptsize{\text{连通块的大小}}}{b} $，则答案的第一个数一定是 $A - a + 1$。

因为最优方案一定是这样的：（以样例二为例）

|1|0|x|0|x|0|x|0|1|0|x|0|1|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|

我们只要打这几个，就不会让子弹浪费。

由于求的是至少要几枪才能**保证**一定打到，所以我们假设前 $A - a$ 枪（留 $a$ 个空够那放剩下的 $a$ 条船）都没有打中，所以一共的答案是 $A - a + 1$。

输出方案的话就直接输出连通块内第 $i (i \bmod b = 0)$ 个格子的编号，输出完 $A - a + 1$ 个就直接退出即可。

# $\textbf{Code}$

```cpp
#include <iostream>
#include <vector>
int n, a, b, k, ANS;
std::string s;
int LenZero;
std::vector<int> vc;
int main() {
    std::cin >> n >> a >> b >> k >> s;
    s += "1"; // 为判断连通块方便所以在字符串后加上一个 '1'
    for (int i = 0; i <= n; i++) {
        if (s[i] == '0')
            LenZero += 1;
        if (s[i] == '1') {
            ANS += LenZero / b;
            LenZero = 0;
        }
    }
    ANS -= a - 1; // 先求出答案的第一个数
    std::cout << ANS << "\n";
    bool FLAG = false;
    for (int i = 0; i <= n; i++) {
        if (s[i] == '0')
            LenZero += 1;
        if (s[i] == '1') {
            int Sta = i - LenZero;
            Sta += b - 1;
            for (int j = Sta; j < i; j += b) {
                vc.push_back(j);
                if (vc.size() == ANS) { // 满 A - a + 1 个退出
                    FLAG = true;
                    break;
                }
            }
            LenZero = 0;
        }
        if (FLAG) break;
    }
    for (auto it = vc.begin(); it != vc.end(); it++)
        std::cout << *it + 1 << " \n"[it == vc.end() - 1];
        // 注意输出要加一
    return 0;
}
```

---

## 作者：Nozebry (赞：0)

## $Problems$
在一个长度为 $n$ 的一个矩形内，一共有 $a$ 艘船，每只船长度为 $b$ ，其中有 $k$ 个已经轰炸过的位子 （$0$ 表示这个位置没被轰炸过， $1$ 表示这个位置已经被轰炸过了），保证这些轰炸过的位子一定不是船的某部分（即被轰炸的是整一艘船）。

现在问你最少再轰炸多少次，就能轰炸到一艘船。
## $Answer$
每连续的 $b$ 个 $0$ 就要炸一次，不然不知道有没有可能刚好就有一艘船在 $b$ 这个位置上面。我们利用贪心可知发现炸这 $b$ 个的最后一个最划算。

因为只要炸到一艘即可，所以答案减去 $a-1$，即有 $a-1$ 艘可以不管它。
## $Code$
```cpp
#include<bits/stdc++.h>
int a,b,n,k,d,ans,p[200010];
char s[200010];//开大一点总是保险的
int main()
{
    scanf("%d%d%d%d%s",&n,&a,&b,&k,s);
    for(int i=0;i<n;i++)
    {
        if(s[i]=='0')
        {
            d++;
            if(d==b)
            {
                d=0;
                ans++;
                p[ans]=i+1;
            }
        }
        if(s[i]=='1')d=0;
    }//去寻找b个0
    ans-=a-1;//把a-1个位置去除掉
    printf("%d\n",ans);
    for(int i=1;i<=ans;i++)printf("%d ",p[i]);//输出存着的位置
    return 0;//好习惯，记得return
}
```

---

