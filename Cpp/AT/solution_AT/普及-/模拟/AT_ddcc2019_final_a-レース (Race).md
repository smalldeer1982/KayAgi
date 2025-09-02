# レース (Race)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ddcc2019-final/tasks/ddcc2019_final_a

高橋君はペンギンのレース場を作りました。

レース場は $ N $ 個の正方形のマスが西から東に一列に並んだ形状をしています。  
 これらのマスの状態は文字列 $ S $ により表され、西から $ i $ 番目のマスの状態は $ S $ の $ i $ 文字目が `-` なら「雪」、`>` なら「氷」です。  
 また、スタート地点は西端のマスの西の端、ゴール地点は東端のマスの東の端です。

高橋くんのペンギンが、スタート地点からゴール地点を目指して東に進みます。  
 ペンギンは、雪マスを $ 1 $ マス通過するのに $ 1 $ 秒、氷マスを $ 1 $ マス通過するのに $ 1/(k+2) $ 秒の時間を要します。  
 ここで、$ k $ はその氷マスの直前に連続して存在する氷マスの個数です。  
 例えば、雪マスの直後に氷マスが $ 2 $ つ存在する場合、$ 1 $ つ目の氷マスは $ 1/2 $ 秒、$ 2 $ つ目の氷マスは $ 1/3 $ 秒で通過します。

ペンギンがスタートする前に、高橋君は雪マスのうち $ 1 $ つを氷マスに変えることができます。  
 ペンギンがスタート地点を出発してからゴール地点に到達するまでに最小で何秒かかるでしょうか？

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 100\ 000 $
- $ S $ は `-`, `>` で構成される長さ $ N $ の文字列
- $ S_1\ =\ S_2\ =\ S_{N-1}\ =\ S_N\ = $ `-`
- **$ S $ において、`-` は必ず別の `-` と隣接して現れる**

### Sample Explanation 1

西から $ 4 $ 番目のマスを雪マスから氷マスに変えると、レース場は `--&gt;&gt;-` となります。 このとき、ペンギンは西から $ 1,\ 2,\ 3,\ 4,\ 5 $ 番目のマスの通過にそれぞれ $ 1,\ 1,\ 1/2,\ 1/3,\ 1 $ 秒、合計で $ 23/6\ =\ 3.83333333... $ 秒を要し、これが最短です。

### Sample Explanation 2

どのマスを雪マスから氷マスに変えても、ペンギンは $ 13/2\ =\ 6.5 $ 秒でゴールします。

### Sample Explanation 3

西から $ 2 $ 番目または $ 6 $ 番目のマスを雪マスから氷マスに変えると、ペンギンは $ 407/60\ =\ 6.783333333... $ 秒でゴールすることができます。

## 样例 #1

### 输入

```
5
-->--```

### 输出

```
3.83333333333333```

## 样例 #2

### 输入

```
7
-------```

### 输出

```
6.5```

## 样例 #3

### 输入

```
10
-->>>-->--```

### 输出

```
6.78333333333333```

# 题解

## 作者：David_yang (赞：2)

[传](https://www.luogu.com.cn/problem/AT_ddcc2019_final_a)送[门](https://atcoder.jp/contests/ddcc2019-final/tasks/ddcc2019_final_a)

第九篇题解，如有不妥请~~忽视~~指出。

## 题目大意：

企鹅要从左边滑到右边，经过 $1$ 个雪方块要花 $1$ 秒，经过 $1$ 个冰方块要花 $\frac{1}{k + 2}$ 秒（$k$ 为你之前连续通过的冰方块数量）。现在你可以把一个雪方块变成冰方块，求最少要花多少时间。

## 算法或数据结构：

只需想一想就可以了。

## 解析：

首先我们先别管什么把雪方块变成冰方块，先计算什么都不变的情况下时间为多少。$k$ 的值最开始为 $0$（因为你最开始没滑过任何一个冰方块）。当遇到冰方块时，按照题目说的计算，此时 $k$ 要加 $1$；当遇到雪方块时，将时间加 $1$，还要记住把 $k$ 清零（因为你中断了）。

这是不变的情况下的方法，看上去说了一大堆，实际上想一想很简单。接下来考虑怎么变时间最少。其实也不难，你把之前的 $k$ 取最大值就行了。当冰面越长，是不是 $\frac{1}{k + 2}$ 越小？我们只需要延长最长的冰面就行了。

整道题就这两点很重要，其它只需要注意保留 $15$ 位小数就行了，不用换行。接下来放代码了。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,mmax,cnt;					//我这里用cnt代替k
string s;
double sum;
int main()
{
	scanf("%d",&n);
	cin>>s;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='-')
		{
			sum+=1.0;
			mmax=max(mmax,cnt);				//记录最大值
			cnt=0;
		}
		else
		{
			sum+=(double)(1.0/(cnt+2.0));	//注意int和double的转换
			cnt++;
		}
	}
	printf("%.15lf",sum-1.0+(1.0/(mmax+2.0)));	//保留15位小数，同时把雪方块变成冰方块
	return 0;
}
```

注：代码已 AC 过，请放心食用。

最后，浏览过看过也要赞过！

---

## 作者：A_grasser (赞：2)

## 题意简化

求将一个雪块改为冰块后最远滑行距离。

## 需要注意的地方

1. 要输出 $15$ 位小数。

## 解法分析

就是模拟。

扫一遍，求出总时间 `ans` 和最长冰面的长度 `mx`。因为延续最长冰面，滑行时间最少，所以只要答案加上 $\dfrac{1}{mx+2}$，再减掉原先是雪的 $1$，就是答案。

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int n,mx,il;
string s;
double ans; 
int main(){
	cin>>n>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='>'){ 
			ans+=(1.0/(il+2));//答案加上 
			il++;//记录距离 
		}
		else{
			ans+=1; 
			mx=max(mx,il);//取最大冰面长度 
			il=0;//归零 
		}
	}
	cout<<fixed<<setprecision(15)<<ans-1+(1.0/(mx+2));//15位小数 
	return 0;
}
```

---

## 作者：NFGase (赞：2)

这道题比较好理解，按照题意模拟即可。

由于此题没有人做，更没有人交翻译和题解，我就把机翻放在[云剪贴板](https://www.luogu.com.cn/paste/0gits8hf)里了，若有问题，可以联系修改。

首先要明确本题要用的变量，变量 $sum$ 是用来存放最终的结果，字符串 $s$ 是用来存放地图的，变量 $len$ 用来存放 $s$ 的长度，变量 $cnt$ 是用来存放连续冰块个数，变量 $mx$ 是用来最大连续冰方块个数。

这道题是让我们把一个雪方块变成冰方块，使得走过这段路的速度最快。由题目公式可知，连续在一起的冰方块数越多，走过这些冰方块的速度就越快，所以我们只需要求一下最大连续冰方块个数，也就是求 $mx$ 的值，之后把 $sum$，这时候 $sum$ 还在存雪方块变冰方块的操作之前的值，这时候我们只需要把 $sum$ 的值减去 $1$，代表着删除一个雪方块，之后再加上 $\frac{1}{mx + 2}$ 就可以得出最终结果了。

还有些细节没有说，上面说的都是将雪方块变冰方块的操作之后的事情，那么之前的时候，$sum$ 的值怎么求？很简单，这只需要遍历一下字符串 $s$，之后如果是冰方块，就将 $sum$ 加上 $\frac{1}{cnt + 2}$，由于连着的冰方块数，也就是 $cnt$，又多了一个，这时就可以将 $cnt$ 自增，并求最大连续冰方块个数。但如果是雪方块，那就说明冰方块就不连续了，把 $cnt$ 设为 $0$ 并将 $sum$ 自增即可。

但是，这道题比较坑，你的 $mx$ 变量不得设为负数，因为会出现没有冰方块的情况，所以在处理将雪方块变冰方块的操作的时候，$mx$ 为负数是会出现大差错的。再就是这道题保留小数的时候不能用 `fixed << setprecision(15)`，对于第二个样例来说是会强制保留后面的所有小数的，但是在第二个样例的输出中，小数点后面仅有一位，所以要抛弃 `fixed`。

代码如下。

```cpp
#include <iostream>
#include <iomanip>
using namespace std;
int len, cnt = 0, mx = 0;
double sum = 0;
string s;
int main(){
    cin >> len >> s;
    for(int i = 0; i < len; i++){
        if(s[i] == '>'){
            sum += (1.0 / (cnt + 2));
            cnt++;
            mx = max(cnt, mx);
        }
        else{
            cnt = 0;
            sum++;
        }
    }
    sum--;
    // cout << sum << endl;
    // cout << (1.0 / (mx + 2)) << endl;
    sum += (1.0 / (mx + 2));
    cout << setprecision(15) << sum << endl;
    return 0;
}
```

[记录](https://www.luogu.com.cn/record/123441688)

---

## 作者：wyc0809 (赞：1)

传送门：[AT_ddcc2019_final_a](https://www.luogu.com.cn/problem/AT_ddcc2019_final_a)


------------
 
  切入正题

------------


## 思路

这道题其实就是一道大模拟再加一丢丢贪心。

通过一个雪方块的时间为 $1$ 秒，通过一个冰方块的时间为 $\frac{1}{k+2}$ 秒。（$k$ 为这个冰方块前连续的冰方块数量）

其实不难发现，如果想要在把 $1$ 个雪方块变成冰方块之后所用时间最少，就需要将这个方块添加在最长的连续的冰方块之后。

所以，我们可以先计算出来最长的连续的冰方块数量，以及再改变前的所需的时间，然后就可以得出在更改之后最少时间为：

现在所需时间减 $1$（更改前通过雪方块的时间）加 $\frac{1}{k+2}$（更改后通过冰方块的时间，此处假设最长联通冰方块数量为 $k$）
   
   

------------

   
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
double n,cnt,cnt2,k,ans;//n为总方块数量，cnt为统计连续冰方块数，cnt2为最长连续冰方块数，k为计算现在所需时间的统计值，ans为最终答案 
char a[100005];//开一个字符类型数组a存储滑雪道 
int main() {
	std::ios::sync_with_stdio(false);//关闭cin，cout同步流，可提速，萌新初学者可忽略 
	cin>>n;//输入总方块数 
	
	//计算最长连续冰方块数
	
	for(int i=1;i<=n;i++){//循环输入冰雪方块 
	 
		cin>>a[i];//输入冰雪方块 
		if(a[i]=='>'){
			cnt++;//统计当前连续冰方块数量 
			cnt2=max(cnt2,cnt);//不断更新最长连续冰方块数
		}
		else	cnt=0;//如果当前方块不为冰方块（'>'）时，停止统计。 
	}
	
	//计算现在所需时间 
	
	for(int i=1;i<=n;i++){
		if(a[i]=='>'){
			ans+=1/(k+2);//增加通过当前冰方块所需时间 
			k++;//增加联通冰块值 
		}
		else{
			k=0;//如果当前方块不为冰方块（'>'）时，停止统计。 
			ans++; //增加通过当前雪方块时间 
		}
	}
	cout<<setprecision(15)<<ans-1+1/(cnt2+2);//输出最后答案 
	return 0;
}
//问题解决~~
```
[AC记录](https://www.luogu.com.cn/record/141185841)

###### ~~审核员大大最好了，让孩砸过吧qwq~~

---

## 作者：_Tatsu_ (赞：0)

### 25.1.16 发现了奇怪的缩进，改一改
### 思路
此题需求改变一个雪块后最远的滑行距离。

我们使用 $maxx$ 存最大距离，$dis$ 存连续的冰块距离，按题目模拟即可。

### AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define fro for
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	int n,maxx=-1,dis=0;
	double sum=0;
	string s;
	cin>>n>>s;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='-')
        maxx=max(maxx,dis),sum++,dis=0;
		else
		sum+=1.0/(dis+2),dis++;
	}
	printf("%.15f",sum-1+(1.0)/(maxx+2));
	return 0;
}
```

---

## 作者：WaterSky (赞：0)

# [AT_ddcc2019_final_a レース (Race)](https://www.luogu.com.cn/problem/AT_ddcc2019_final_a)
简单模拟题，在思路上没什么好说的，那就放上几个小疑问的解答。

## 先放代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n,t,maxx;
double ans;
string a;
int main(){
	cin>>n>>a;
	a=" "+a;
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='>') t++,ans+=(1.0)/(t+1);
		else maxx=max(t,maxx),t=0,ans+=1;
        //计算在原赛道导航的时间，并且找到最长的连续的冰块长度。
	}
	printf("%.15f",ans-1+(1.0)/(maxx+2));//记得是十五位小数
	return 0;
}
```
## 疑问与解答：
- 问：如何证明将冰块放置于最长连续冰块后面的时间最短？

答：题目中可以发现**在连续的冰块上面滑行的速度递增**，那么意味着**放置在更长的冰块后能够省的时间会更多**，假设放置的不是在最长的冰块后，而是在其他的任意位置放置，速度都不会比在最长冰块后的速度更快，省下的时间也必然不会大于最后冰块后放置。

- 问：最后的公式是什么意思，又是怎么得出的？

答：我们在更换冰块后，相较于原滑道，少了一块雪，多了一块冰，所以时间是减少了 $1$（原先在雪上滑行的时间），增加了在冰上滑行的时间（具体见代码）。

## 最后的
感谢管理员审核！

---

## 作者：Mierstan085 (赞：0)

？怎么没关题解通道这种简单题

显然可以按照题意模拟。我们不妨计算最开始不更改所需要的总时间 $S$ 和最长的延续的冰面长度 $L$。不难发现，在最长的延续冰面前加雪可以获得最优解，答案为 $S - 1 + \frac{1}{L + 2}$。

代码中 `ans` 为 $S$，`maxn` 为 $L$。

```cpp
// Problem: レース (Race)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_ddcc2019_final_a
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
int n,mx,il;
string s;
double ans; 

int main(){
	int n;
	string s;
	cin >> n >> s;
	
	double ans = 0;
	int il = 0, maxn = -1;
	for (int i = 0; i < s.length(); i ++){
		if (s[i] == '>')
			ans += 1.0 / (double)(il ++ + 2);
		else{
			ans ++;
			maxn = max(maxn, il);
			il = 0;
		}
	}
	
	printf("%.15lf", ans - 1 + 1.0 / (double)(maxn + 2));
}
```

---

## 作者：Rieman_sum (赞：0)

### 题目大意

有一条赛道由 $n$ 个方格组成，每个方格不是雪就是冰。经过一个雪方格需要 $1$ 秒，经过一个冰方格需要 $\frac{1}{k+2}$ 秒，其中 $k$ 表示冰方格前面连续的雪方格快数。现在把一个雪方格变成冰方格，问滑行的最短时间。

### 解

记录没有改变之前，滑行全程的时间及冰面长度。贪心不难想到，连续的冰方格滑行速度最快，所以我们把最长连续冰方格后一个改为冰方格。答案要减 $1$ 的原因是：我们把雪方格改掉了，那么时间就减 $1$ 了。

### 坑

输出是小数，所以要开浮点型变量。

### 总结

考察贪心思想。

### 代码

```cpp
#include<iostream>
#include<iomanip>
using namespace std;
double n,maxn=-114514,ice,ans,len;
//我不喜欢开成整型又强转，所以我都开成浮点型，可以减少不必要的麻烦
//maxn是通过打擂台法求最大值，所以maxn开始赋为无穷小
string s;
int main()
{
	cin>>n>>s;
	len=s.size();
	for(int i=0;i<len;i++)
	{
		if(s[i]=='>') ans+=1/(ice+2),ice++;//如果是冰，就记录连续
		else ans++,maxn=max(maxn,ice),ice=0;//如果不是冰了，就判断是否为最大值
	}
	cout<<fixed<<setprecision(15)<<ans+(1/(maxn+2))-1;//保留十五位小数
	return 0;
}
```

---

## 作者：BK小鹿 (赞：0)

## 题意简述

一个长度为 $N$ 的赛道，每个方格是雪或冰。从西向东通过每个方格有不同的时间消耗。

企鹅从最西端开始滑行，可以将一个雪方格变为冰方格，求企鹅到终点的最短时间。

## 思路分析

数据范围很明显提示我们这是一个贪心。

首先直接求不太好想，正难则反。不难想到我们可以先把总时间求出来。然后想到连续最长的冰面时间肯定最短，先把最长冰面求出来，记为 $x$。

然后我们把总时间加上 $\frac{1}{x+2}$，又因为有一个雪方块，所以再减一即为答案。

## 注意事项

记得保留小数位输出即可。

此题比较简单，我就不放代码了，感谢你的观看！

---

## 作者：Chillturtle (赞：0)

# 题意

有一个长度为 $n$ 的字符串，由 ``-`` 和 ``>`` 两种字符组成，分别表示雪和冰。现在有一只小企鹅，它通过 ``-`` 的时间为1秒，通过 ``>`` 的时间为 $\frac{1}{k+2}$ 其中 $k$ 表示在当前 ``>`` 块之前，连续的 ``>`` 数量。

你可以将一个 ``-`` 变成一个 ``>``。求最后通过的最短时间。

# 思路

首先，我们要来考虑我们需要将哪一个 ``-`` 变成 ``>``。这是一个很简单的**贪心**。由题可知，通过每一个 ``>`` 方块的时间为 $\frac{1}{k+2}$ 我们想要让这个值最小，则就是让 $k$ 最大。所以我们需要将输入的字符串 $s$ 遍历一遍，来找到最长的 ``>`` 子序列的位置。并在这个子序列的前面或者后面的一个字符变成 ``-`` 就可以找到总时间的最小值。

特别地，如果我们选择在子序列的后面变化，那么在这个最长子序列的右端点位于原字符串的右端点时，需要在该子序列的前面变化。这里举个例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/h1hsbgit.png)

最后还有一点：当整个字符串中都没有 ``>`` 时，随便找一个位置变就可以了啦。我的代码是直接变的首位。

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	string s;
	cin>>s;
	int ice=0,maxx=-1,l=0,r=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='>'){
			ice++;
		}else if(s[i]=='-'&&ice!=0){
			if(ice>maxx){
				maxx=ice;
				r=i-1;
				l=i-ice;
			}
			ice=0;
		}
	}
	if(l==r&&l==0){
		s[0]='>';
	}else if(l!=0&&r==(s.size()-1)){
		s[l-1]='>';
	}else{
		s[r+1]='>';
	}
	double k=0;
	double ans=0.0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='-'){
			k=0;
			ans+=1;
		}else{
			ans+=(1/(k+2));
			k++;
		}
	}
	cout<<fixed<<setprecision(15)<<ans<<endl;
	return 0;
}
```

---

## 作者：chl090410 (赞：0)

## The Solution to AT_ddcc2019_final_a レース (Race)

### Description

企鹅经过 $1$ 个雪地方格需要 $1$ 秒，经过 $1$ 个冰地方格需要 $\dfrac{1}{(k+2)}$ 秒。这里，$k$ 是紧接着冰雪方格之前的冰雪方格数。

在企鹅开始之前，高桥可以把 $1$ 个雪方块变成冰方块。问企鹅离开起点后到达终点最少需要多少时间？

### Solution

由题，连续的冰方块越多，走过这些冰方块的速度就越快。所以被改为冰方块的雪方块的位置一定是使所有改动方案中包含被改动位置的连续冰方块数最多的位置。

我们先正着扫一遍这 $N$ 个方块，在倒着扫一遍，求出每个位置前后的冰方块数量，分别存在两个数组 $s,k$ 中，若改动第 $i$ 位，则包含第 $i$ 位的连续冰方块数为 $s_i+k_i+1$，我们只需遍历这两个数组，就能求出这个值的最大值及 $i$ 的值。

求出 $i$ 的值后，我们先将第 $i$ 个方块改为冰方块，再根据题目中的公式遍历这 $N$ 个方块求解即可。

### Accode

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[100005];
int s[100005],k[100005],hu[100005],n,x,e,y,h,u,p;
double cnt;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]=='>'){
			x++;
		}else{
			s[i]=x;
			x=0;
		}
	}
	x=0;
	for(int i=n;i>=1;i--){
		if(a[i]=='>'){
			x++;
		}else{
			k[i]=s[i]+x;
			x=0;
		}
	}
	for(int i=1;i<=n;i++){
		if(k[i]>=e){
			e=k[i];
			y=i;
		}
	}
	a[y]='>';
	hu[0]=1;
	for(int i=1;i<=n;i++){
		if(a[i]=='>'){
			hu[i]=hu[i-1]+1;
		}else{
			hu[i]=1;
		}
	}
	for(int i=1;i<=n;i++){
		cnt+=(1.0/hu[i]);
	}
	printf("%.14lf",cnt);
	return 0;
}

---

## 作者：封禁用户 (赞：0)

一道简单模拟题，直接按照题意模拟即可。

按照题意，我们需要存储**连续冰块数量**和**最多的连续冰块数量**。
- - -
代码比较容易实现。

下面的代码中 `k` 表示连续冰块数量，`maxn` 表示最多的连续冰块数量，每次更新两个变量即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,maxn,k;string s;double ans;
int main(){
    cin>>n>>s;
    int l=s.size();
    for(int i=0;i<l;i++)s[i]=='>'?(ans+=1/double((k++)+2)):(ans++,maxn=max(maxn,k),k=0);//模拟
    printf("%.15lf",ans+(1/double(maxn+2))-1);//保留十五位小数输出
    return 0;
}
```

---

## 作者：BinSky (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_ddcc2019_final_a)

## 题目描述：

 企鹅经过 $1$ 个雪地方格需要 $1$ 秒，经过 $1$ 个冰地方格需要 $\frac{1}{(k + 2)}$ 秒。$k$ 是紧接着冰雪方格之前的冰雪方格数。在企鹅开始之前，高桥可以把 $1$ 个雪方块变成冰方块。问企鹅离开起点后到达终点最少需要多少时间？

## 思路分析：

这道题是 **模拟+贪心** 题，企鹅连续通过的冰方块越多，通过时间便越少，我们只需要枚举连续的最长冰方块，同时把总时间记录下来，最后把雪方块替换掉（延长最长冰方块的数量）就行了。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,cntx=0,cntb=0;
double t=0;
string s;
int main()
{
	cin>>n;
	cin>>s;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='-')
		{
			t ++;
			cntb = 0;
		}
		if(s[i]=='>')
		{
			t += 1*1.0/(2+cntb);
			cntb ++;
			cntx = max(cntx,cntb);//更新最长冰方块
		}
		
	}
	printf("%.15lf",t+1*1.0/(cntx+2)-1);//保留15位小数
	return 0;
}

```


---

## 作者：_Memory (赞：0)

## 一、题意

这个是一道比较水的贪心小题，就是要保证时间最短，即实现连续冰块数最长，毕竟度过冰块的速度怎么样都会小于一。那么我们很容易就会想到要统计总共的连续冰块数量，但是用一个计数器是远远不够的！因为我们在统计雪数量的时候第一个计数器要清零。所以再设一个总共的冰块连续计数器实时更新就好啦，详细步骤见代码。

## 二、代码

```cpp

#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,maxnb,maxn;//maxnb,maxn分别是连续冰块数和总连续冰块数。 
double ans;
string s;
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		if(s[i]=='>'){//先来看s[i]是冰块的情况 
			ans+=(1.0/(maxnb+2));//加上时间 
			maxnb++;//局部连续冰块数自增 
			maxn=max(maxn,maxnb);//更新最终连续冰块数 
			
		}
		else{//再看是雪的情况 
			maxnb=0;//那么这里局部连续冰块数断了，就归零 
			ans++;//时间增加1 
		}
	}
	cout<<fixed<<setprecision(15)<<ans+(1.0/(maxn+2))-1;//最后时间就是雪的时间＋冰块时间
	//但因为改变了一块，所以减一 
	return 0;//好习惯 
}
```

---

## 作者：hmh100211 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_ddcc2019_final_a)

## 题意分析：

~~这么简单不用分析吧~~

## 思路：

要注意 `高桥可以把 1 个雪方块变成冰方块`。

因为连续经过的冰块越多，再经过冰块时的速度就越快。

用贪心思路可以想到：要时间最短，那就要把最长连续冰块延长。

剩下的按题意模拟即可。

# AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ice_lenth,max_ice_lenth; 
string s;
double ans;
int main(){
	cin>>n>>s;
	
	for(int i=0;i<=n-1;i++){
		if(s[i]=='>'){ //是冰块 
			ans+=(1.0/(ice_lenth+2)); //计算时间 
			ice_lenth++; //连续冰块长度自增
			
			//注意上面两行不能反 
			
			max_ice_lenth=max(ice_lenth,max_ice_lenth); //更新最长连续冰块长 
		}
		
		else if(s[i]=='-'){ //是雪块 
			ans++; //计算时间 
			ice_lenth=0; //连续冰块长度归零 
		}
	}
	ans+=(1.0/(max_ice_lenth+2))-1; //把最长连续冰块延长一个并计算时间，因为替换了一块雪方块所以还要减一 
	printf("%.14lf",ans); //输出（注意精度） 
	return 0;
} 
```

# [AC](https://www.luogu.com.cn/record/141205951)

---

