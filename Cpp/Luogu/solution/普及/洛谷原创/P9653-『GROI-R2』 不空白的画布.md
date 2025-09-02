# 『GROI-R2』 不空白的画布

## 题目描述

我们都知道爱丽丝躲起来之后，坦尼尔坐在了空白画布面前，拿起炭笔开始作画。

但是现在画布已经不再空白，因为画布上已经有了当下的风景。我们设画布的长度是 $n$，每一单位长度上的颜色可以用一个在 $[1,k]$ 范围内的正整数表示。

坦尼尔还要画他已经翻了的茶杯。每一次作画，他可以选定画布上的任意一个位置，然后将这个位置上的颜色涂改成 $[1,k]$ 范围内的任意正整数。

最后，我们都知道这幅画是有记忆的。定义画上留下的记忆碎片数量为画上的**相同颜色连续块个数**。现在坦尼尔想知道，如果给定他作画的次数**上限**，那么画上的记忆碎片个数**最多**有多少。

**形式化题面**

你有连续的 $n$ 个方格，每个方格上有一个初始颜色 $c_i$，且保证 $1\le c_i \le k$。

你可以操作**至多** $m$ 次，每个操作为改变某个方格颜色，要求改变后的颜色范围仍在 $[1,k]$ 内。

我们称一个**极长相同颜色连续段**为一块，要求求出经过至多 $m$ 次操作后的**最多**块数。


## 说明/提示

**样例解释**

对于第一组测试数据，坦尼尔可以将从左到右的第二个位置涂成颜色 $1$，得到 $\{c_n\}=\{2,1,2\}$，块数为 $3$。


对于第二组测试数据，坦尼尔可以将从左到右的第二个位置涂成颜色 $1$，将从左到右的第三个位置涂成颜色 $3$，得到 $\{c_n\}=\{2,1,3,2,3\}$，块数为 $5$。

**数据范围**

**本题采用捆绑测试**。

| $\text{Subtask}$ | $\sum n\le$ | $m\le$ | $k\le$ | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------:  |
| $1$ | $10$ | $10$ | $3$ | $10$ |
| $2$ | $5\times 10^5$ | $1$ | $5\times 10^5$ | $10$ |
| $3$ | $10^3$ | $10^3$ | $10^3$ | $15$ |
| $4$ | $5\times 10^5$ | $5\times 10^5$ | $3$ | $25$ |
| $5$ | $5\times 10^5$ | $5\times 10^5$ | $5\times 10^5$ | $40$ |

对于 $100\%$ 的数据满足 $1\le  n\le 5\times 10^5$，$1\le \sum n\le 5\times 10^5$，$1\le m\le n$，$3\le  k \le 5\times 10^5$，$1\le c_i\le k$。


## 样例 #1

### 输入

```
2
3 1 3
2 2 2
5 2 4
2 2 2 2 3```

### 输出

```
3
5```

# 题解

## 作者：fish_love_cat (赞：11)

贪心。

---

**约定：**

对于一组**连续两个颜色都相同的格子**，在下文中将被称作**双连**。

对于一组**连续两个的格子**，在下文中将被称作**连双**。

对于一组**连续三个颜色都相同的格子**，在下文中将被称作**三连**。

对于一组**连续三个的格子**，在下文中将被称作**连三**。

---

**思路：**

观察 $k$ 的取值，我们会发现 $k$ 至少为 $3$。这就说明，我们完全可以保证改动后的格子与两边不同色。那么，$k$ 的存在就没有多少意义了，只需要标记出哪些格子需要变色即可。

初始时先统计出未修改时的答案，再进行贪心的修改，让答案最大化。

显然的，对于一个三连，我们可以通过改变中间格子，而使答案块数加上 $2$。而对于双连，我们改变其中任意一个格子，收益都只为 $1$。

所以我们先枚举每一个连三，判断是否是三连，是则变中间格，不是略过，然后再枚举连双进行判断并依据判断结果进行改变即可。

这样显然能够最大化 $m$ 次修改所带来的收益。

---

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int jsq=-1;//修改赋特殊值保证不同不可能被判定成双/三连
int main(){
    int t;cin>>t;
    while(t--){
        int n,m,k;cin>>n>>m>>k;
        int c[500005]={},ans=0;
        for(int i=1,flag=(--jsq);i<=n;i++){
            cin>>c[i];
            if(flag!=c[i]) ans++,flag=c[i];//初始统计答案
        }
        for(int i=2;m&&i<n;i++) if(c[i-1]==c[i]&&c[i]==c[i+1]) m--,c[i]=(--jsq),ans+=2;//枚举连三判断三连
        for(int i=1;m&&i<n;i++) if(c[i]==c[i+1]) m--,c[i]=(--jsq),ans++;//枚举连双判断双连
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：kanzaki (赞：7)

## 题目分析




有 $n$ 个方格，$m$ 次修改机会，问总共有多少个不连续的段。

我们可以将方格拆成小段。如果有 $3$ 个连续的颜色相同的方格，我们可以将中间的颜色改变从而使其变成 $3$ 个不连续的段。

例如 $1,1,1$ 可以通过修改第 $2$ 个 $1$ 变成 $1,2,1$。

这样段数就从 $1$ 变成了 $3$ ,答案增加 $2$。

同样，如果有 $2$ 个连续的颜色相同的方格，我们可以将第 $1$ 个或第 $2$ 个方格的颜色改变从而使其变成 $2$ 个不连续的方格。

例如 $1,1$ 可以通过修改第 $1$ 个 $1$ 变成 $2,1$。

这样段数就从 $1$ 变成了 $2$ ,答案增加 $1$。

如果有 $1$ 个方格，则改不改颜色段的个数都不变。

可以发现，其他拆法都可以转化成这 $3$ 种情况。



## 思路

既然拆 $3$ 个连续的方格得到的新的段数多于 $2$ 个，并且不存在其他情况，我们就可以使用贪心的思路。

先找出有多少个连续的 $3$ 个方块。改变颜色后再找出有多少个连续的 $2$ 个方块并改变颜色。

这样所得到的段数一定是最多的。

观察 $k$ 的取值范围，发现 $k$ 总是大于等于 $3$ 的。

那么我们就不需要再考虑修改后的颜色是否会相同，因为有足够的颜色可用于改变。

所以只要遍历两遍所有的方格，第一次找出所有连续的 $3$ 个方格，第 $2$ 次找出所有连续的两个方格，最后输出答案即可。

需要注意的是，答案的值至少为修改方格颜色前段的个数。因为遍历是统计的只是增多的段，所以还要加上最开始段的个数。


## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 500005
int t,m,n,k;
int tmp,flag=-10,ans;//flag表示修改后的颜色，因为不能使修改后相邻的颜色相同，所以可以使用一个不会出现的数。 
int c[maxn];
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		ans=0,tmp=-10;//每组数据都要初始化ans 
		cin>>n>>m>>k;
		for(int j=1;j<=n;j++){
			cin>>c[j];
			if(tmp!=c[j]){
				ans++;
				tmp=c[j];
			}//判断初始有多少个段 
		}
		for(int j=2;j<n;j++){
			if(m<=0) break;//如果修改的次数达到上限，则不能再改变 
			if(c[j]==c[j-1]&&c[j]==c[j+1]){
				c[j]=flag;
				ans+=2;
				m--;
			}
		}//寻找有多少个3个连续的方格并统计ans 
		for(int j=1;j<n;j++){
			if(m<=0) break;
			if(c[j]==c[j+1]){
				c[j]=flag;
				ans++;
				m--;
			}
		}//寻找有多少个2个连续的方格并统计ans
		cout<<ans<<endl;
		for(int j=1;j<=n;j++){
			c[j]=0;
		}//初始化c数组，保证每组数据在输入前c数组没有输入上一组的颜色 
	}
	return 0;
} 
```



---

## 作者：Wi_Fi (赞：5)

提供一种很好想也很好写的思路。

题目的意思就是给定一个数列，通过改变元素的值使得这个数列的相等连续段尽量多。

很明显，要实现这个目标，我们就要尽量拆散一个长度长的相等连续段，然后拆完之后寻找下个最长的，这个过程我们可以用 STL 中的 ```priority_queue``` 来进行维护。

现在就只有一个问题，那就是怎么拆分一个相等连续段，是从中间拆分，还是拆分成长度为一个元素和另外一个序列？

很容易证明，第二种方法是更优的，因为第一种方法产生浪费的可能性比第二种大，即出现长度为 $2$ 的相等连续段的情况。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int INF=0x3f3f3f3f,N=5e5+5;
int i,T,n,m,k,c[N];
int main()
{
	cin>>T;
	while(T--)
	{
		int cnt=0,ans=0,sum=1;
		priority_queue<int>q;
		cin>>n>>m>>k;
		for(i=1;i<=n;i++)cin>>c[i];
		for(i=2;i<=n;i++)
		{
			if(c[i]==c[i-1])sum++;
			else q.push(sum),ans++,sum=1;
		}
		q.push(sum),ans++;
		for(i=1;i<=m;i++)
		{
			int fr=q.top(),l1,l2;
			if(fr==2)ans++;
			if(fr>=3)ans+=2;
			fr--,l1=1,l2=fr-1;
			q.pop(),q.push(l1),q.push(l2);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：4)

~~谁跟我一样只看形式化题意的？举个爪。~~

这道题考虑贪心，对于每个数，如果两边的数都与自己相等，则改变这个数，此时，由于 $k\ge3$，因此一定能将这个数改为一个数切不影响别的数，方便统计，可以直接改为 $0$。

接着，我们其次考虑一个数于前一个数相同，则改变这个数，不难证明此时没有任何两个 $0$ 相邻，因此可行，最后统计相同颜色块数即可，于是代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000009];
int main(){
	int t;
	cin>>t;
	while(t--){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=2;i<n;i++){//和前面后面都相同
		if(m==0){//操作次数不够
			break;
		}
		if(a[i]==a[i-1]&&a[i]==a[i+1]){
			m--;
			a[i]=0;
		}
	}
	for(int i=2;i<=n;i++){//和前面相同
		if(m==0){
			break;
		}
		if(a[i]==a[i-1]){
			m--;
			a[i]=0;
		}
	}
	int sum;
	sum=1;//先把第一块记上
	for(int i=2;i<=n;i++){
		if(a[i]!=a[i-1]){
			sum++;
		}
	}
	cout<<sum<<endl;	
	}
	
	return 0;
} 
```

---

## 作者：what_can_I_do (赞：2)

怎么就晚一点 P9652 就交不上题解了。

[传送门](https://www.luogu.com.cn/problem/P9653)

贪心。

首先我们很容易就能看出，如果一块的块长为 $2$，那么它不管怎样都只能比原先增加 $1$ 块。如果一块的块长大于 $2$，那么它们最好情况下能使其比原先多 $2$ 块。

那么我们就可以发现，如果序列中有块长大于 $2$ 的块，那么我们就先对其进行操作，操作方法：如果刚好有连续三个相同的元素，那么对第二个进行操作，答案加 $2$。如果只能刚好有连续两个相同的元素，那么就把它得数量先统计下来，如果前面的操作完后还有操作次数就去操作这些元素，每次操作答案加 $1$。并且这题 $3\le k$，所以不用担心遇到当 $k=2$ 时出现 `1 2 2` 这种情况。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m,k,a[500010];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int ans=0;
		scanf("%d%d%d",&n,&m,&k);
		for(register int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(register int i=1;i<=n;i++) if(a[i]!=a[i-1]) ans++;
		int l=1,kc=1,tj=0;
		for(register int i=2;i<=n;i++)
		{
			if(a[i]==a[i-1])
			{
				kc++;
				if(kc==2&&a[i+1]==a[i])
				{
				    ans+=2;
					m--,kc-=2,l+=2;
					if(m==0) break;
				}
				else if(kc==2) tj++;
			}
			else kc=1,l=i;
		}
		if(m==0) printf("%d\n",ans);
		else if(tj>m) printf("%d\n",ans+m);
		else printf("%d\n",ans+tj);
	}
	return 0;
}
```

---

## 作者：渡墨残殇 (赞：2)

## 分析

记忆碎片数量为画上的相同颜色连续块个数，要使记忆碎片的数量最多，即相同颜色的连续块数最少即可。我们有操作次数，使相同颜色的的连续块变成不同颜色的连续块，而保证绝对使颜色块不同且使改变后的颜色块不会与下一个颜色块再次连续起来即 $k\geq3$。

## 做法
首先遍历一下整个数组，统计出所有相同颜色的连续块。
考虑把他们分成三类：连续奇数块，连续偶数块，单个的一块。

这三类无论是否操作都有各自的一块，即先把所有的相同颜色的连续块统计起来。
单个的块无需操作，自成一块。

之后考虑奇数块，把任意奇数块在他们间隔的中间改变颜色每次产生的贡献为 $2$，例如 $ 2  $ $ 2 $ $2 $，只需要把中间的块改变即可 $ 2  $ $ 1 $ $2 $，除去原来自己本来的一块，改变之后多了两块。

再之后考虑偶数块，其实考虑起来和奇数块一样，只需要把偶数（$n\gt2$）的头块单独拎出来存起来先不考虑，之后偶数块变成奇数块和奇数块考虑的一样，贡献一样 $2$。

最后考虑被单独拎出来的偶数头块（$n$，取剩余的操作次数 $m$ 和 $n$ 的最小值即为剩余最多被改变的次数，贡献为 $1$。


不过由于单拎出来的偶数头快贡献为 $1$，所以它需要最后考虑。

最后，把所有的贡献都加起来即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10000000],f[1000000];
int main ()
{
  int t;cin>>t;
  while(t--)
  {
    int n,m,k;cin>>n>>m>>k;
    int sum=0,tt=1,ty=0;
    a[0]=-110;
    for(int i=1;i<=n;i++)
    {
      cin>>a[i];a[0]=a[i];
      if(a[i]==a[i-1])f[tt]++;
      else {f[++tt]=1;}
    }
    for(int i=1;i<=tt;i++)
    {
		sum++;
      if(f[i]==1||f[i]%2==0)continue;
      int p=f[i]/2;if(p>=m)p=m,m=0;else m-=p;
      sum+=2*p;
    }
    for(int i=1;i<=tt;i++)
    {
     if(f[i]%2!=0)continue;
     ++ty;
     int p=(f[i]-1)/2;if(p>=m)p=m,m=0;else m-=p;
      sum+=2*p;
    }
    sum+=min(m,ty);if(sum>n)sum=n;
    cout<<sum<<"\n";
    for(int i=1;i<=tt;i++)f[i]=0;
  }
  return 0;
}
```


---

## 作者：Moon_Wind (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9653)


------------


**题意简述**：


有 $n$ 个连续的方块，每个方块上有 $1$ 个数字 $c_i$，表示 $1$ 种颜色，保证 $1\le c_i\le k$。

现在可以对其进行 $m$ 次操作，每次操作可以修改其中的一个数，修改后的数也要在 $[1,k]$ 之间，求在 $m$ 次修改后，**极长相同颜色连续段**最多块数。

**算法分析**：

可以发现，先在连续三个相同的数中将中间的数修改，会比先修改只有连续两个相同的数更优。如图，当 $m=1$ 时，修改第三个方格会比修改第 $5$ 个或第 $6$ 个更优。

![](https://cdn.luogu.com.cn/upload/image_hosting/vjwl834a.png?x-oss-process=image/resize,m_lfit,h_570,w_1225)

所以，我们可以考虑**贪心**。先遍历一遍数组，如果发现有含有三个及以上连续相同数字的块时，将其中第 $2$ 个数修改，如果此时修改次数还没有超过 $m$ 的话，继续进行遍历。

如果遍历完之后，修改次数仍然没有 $m$ 次的话，就再次进行遍历，将那些连续两个相同的数字依次修改，如果修改次数达到 $m$ 时，就退出循环。最后计算出**极长相同颜色连续段**块数即可。

**代码部分**：



------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,a[1100001];
	cin>>t;
	while(t--){//有多组数据！！！
		int n,m,k,cnt=0;
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(k==1){
			cout<<1;
			continue;
		}
		for(int i=1;i<n-1;i++){
			if(a[i]==a[i+1]&&a[i+2]==a[i+1]&&m>0){
			      m--;//修改那些连续最少三个相同的数字块。
			      a[i+1]=k+1;
			}
		}
		for(int i=1;i<n;i++){
			if(a[i]==a[i+1]&&m>0){
			      m--;//修改那些连续两个相同的数字块。
			      a[i+1]=k+2;
			}
		}
		for(int i=1;i<=n;i++)
			if(a[i]!=a[i+1]) cnt++;//计算块数。
		cout<<cnt<<endl; 
	} 
	return 0;
} 
```


------------

本人只是一名蒟蒻，若有错误请多多包涵，谢谢大家。

---

## 作者：RJSPZ (赞：1)

裸的贪心。

思路：

读入时与左右比较，将左边和右边的颜色比较，相同的颜色块数放入 vector ，用 pair 存储下表和相同颜色块数，然后进行贪心。

怎么贪心呢？

如果我更新下表为 $ i $ 的颜色块能增加两个块，就更新，所以先更新更改后块数加 $ 2 $ 的，再更新加 $ 1 $ 的。

问：如何保证一定有颜色能使得左右两边不同？

答：$ k\ge 3 $。

证毕。

Code:
```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define PII pair<int,int>
#define x first
#define y second
using namespace std;
const int N=5e5+7;
int T,n,m,k,cnt;
int c[N];
vector<PII> res;
bool st[N];
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&k);
		memset(st,0,sizeof st);
		cnt=0;
		res.clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&c[i]);
			if(i>1&&c[i]==c[i-1]&&(!st[i-1])){
				st[i]=1;
			}
		}
		for(int i=2;i<=n;i++){
			if(st[i]){
				int k=0;
				if(c[i]==c[i-1]){
					k++;
				}
				if(c[i]==c[i+1]){
					k++;
				}
				res.push_back({i,k});
			}
		}
		sort(res.begin(),res.end(),[&](PII a,PII b){
			return a.y>b.y;
		});
		for(auto t:res){
			if(!m){
				break;
			}
			int i=t.x;
			for(int j=1;j<=k;j++){
				if(j!=c[i-1]&&j!=c[i+1]){
					c[i]=j;
					break;
				}
			}
			m--;
		}
		for(int i=1;i<=n;i++){
			if(c[i]!=c[i-1]){
				cnt++;
			}
		}
		printf("%d\n",cnt);
	}
	return 0;
}
```

---

## 作者：gyyyyx (赞：0)

[题面](https://www.luogu.com.cn/problem/P9653)

观察数据，发现 $k\geq 3$，显然我们改变某个格子颜色后一定能使它与前后两个格子颜色都不同。

因此我们只需要知道改变哪些格子。

发现如果出现连续 $3$ 个相同颜色的格子，改变中间格子可以让答案增加 $2$；如果出现连续 $2$ 个相同颜色的格子，改变任意一个都只能让答案增加 $1$。

可以贪心将所有连续超过 $3$ 个相同颜色的格子都处理了，再处理连续 $2$ 个相同颜色的格子。

代码：

```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;
int T,n,m,k,a[N],ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&k);
		for(int i(1);i<=n;++i){
			scanf("%d",&a[i]);
			if(a[i]^a[i-1]) ++ans;//处理初始答案
		}
		for(int i(2);i<n&&m;++i)
			if(a[i-1]==a[i]&&a[i]==a[i+1])
				--m,a[i]=0,ans+=2;//连续3个相同
		for(int i(1);i<n&&m;++i)
			if(a[i]&&a[i]==a[i+1])
				--m,a[i]=0,++ans;//连续2个相同
		printf("%d\n",ans);ans=0;
	}
	return 0;
}
```

---

## 作者：SakurajiamaMai (赞：0)

## 思路:
**可能是一种新奇的思路**

可以发现，连续的 $3$ 个可以从 $1$ 个变成 $3$ 个，此时答案增加了 $2$，同理，所有大于 $3$ 的连通块修改一次，答案数均增加 $2$。接着考虑连续 $2$ 个的连通块，很明显答案数只能增加 $1$，**但上面所有的情况都是建立在 $k$ 大于 $1$ 的情况下**。当 $k$ 等于 $1$ 的时候，无论怎么改都不变，直接输出答案即可。

利用大根堆维护所有的连通块的数量，每分割一次连通块，将它们分成 $1$ 和剩余块的数目即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e5+10;
int n,m,res,a[N],t,k,num;
void solve()
{
    cin>>n>>m>>k;
    num=1,res=0;
    priority_queue<int, vector<int>, less<int>>que;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]==a[i-1]) num++;
        else que.push(num),num=1,res++;
    }
    que.push(num);
    if(k==1) return cout<<res<<endl,void();
    while(!que.empty()){
        int now=que.top(); que.pop();
        if(now==1) continue;
        if(m==0) break;
        if(now>=3) m--,res+=2,que.push(1),que.push(now-2);
        else m--,res++,que.push(1),que.push(1);
    }
    cout<<res<<endl;
}
signed main()
{
    cin>>t; while(t--) solve();
}
```


---

## 作者：jqQt0220 (赞：0)

~~T1 通道关了没发上去，只好来发 T2~~

一眼贪心。主要就是两种情况：$a\ a\ a \to a\ b\ a$ 增加两块，和 $a\ a\ b\ \ or\ \ a\ b\ b  \to a\ c\ b$ 增加一块（不同字母颜色不同）。根据贪心思想，只要先尽可能多地执行前者，之后如果还有次数再执行后者 ~~（这个思路场上就想到了，但是没打出来）~~。所以只要枚举 $2\sim n-1$（下标从 $1$ 开始），如果相邻三个相等就把中间的换成不相等的，之后再枚举 $2\sim n$，如果这个和前面一个相等就把这个变成和两边的都不相等的。最后算一下块数就搞定了。

AC Code:
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t,n,m,k,c[500005];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++)
            scanf("%d",&c[i]);
        for(int i=2;i<n;i++)//前者
        {
            if(!m)
                break;
            if(c[i]==c[i-1]&&c[i]==c[i+1])
            {
                c[i]=c[i]==1?2:1;//如果两边的是 1 就变成 2 否则变成 1（很好理解）
                m--;
            }
        }
        for(int i=2;i<=n;i++)//后者
        {
            if(!m)
                break;
            if(c[i]==c[i-1])
            {
                for(int j=1;j<=3;j++)//只到 3 是因为要是两边分别为 1,2，那么最大也只有 3，如果两边是其他情况，都可以用 1 或 2 表示（这也是数据范围 k>=3 的原因）
                {
                    if(j!=c[i-1]&&j!=c[i+1])
                    {
                        c[i]=j;//找到就变
                        break;
                    }
                }
                m--;
            }
        }
        int s=1;
        for(int i=1;i<n;i++)//算有几块，不多说
            if(c[i]!=c[i+1])
                s++;
        printf("%d\n",s);
    }
    return 0;//完美结束 QAQ
}
```

---

## 作者：JimmyDong (赞：0)

## 思路

在一张画布上，想增加块数，有以下两种情况：

第一种：

$$a,a,a\Longrightarrow a,b,a\  (a\neq b) $$
增加 $2$ 块。

第二种：

$$a,b,b\ or\ a,a,b\Longrightarrow a,c,b\  (a\neq b\neq c) $$
增加 $1$ 块。

先考虑第一种，若次数有多，再考虑第二种即可，时间复杂度 $O(n)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll q,n,m,k,c[500005],change,ans;
int main()
{
	scanf("%lld",&q);
	while(q--)
	{
		ans=0;
		scanf("%lld%lld%lld",&n,&m,&k);
		for(int i=1;i<=n;i++)
			scanf("%lld",&c[i]);
     		//第一种
		for(int i=2;i<=n;i++)
		{
			if(c[i]==c[i-1]&&c[i]==c[i+1]&&m>0)
			{
				for(int j=1;j<=k;j++)
				{
					if(j!=c[i-1]&&j!=c[i+1])
					{
						change=j;
						break;
					}
				}
				c[i]=change;
				m--;
			}
			if(m==0) break;
		}
        	//第二种
		for(int i=2;i<=n;i++)
		{
			if(c[i]==c[i-1]&&m>0)
			{
				for(int j=1;j<=k;j++)
				{
					if(j!=c[i-1]&&j!=c[i+1])
					{
						change=j;
						break;
					}
				}
				c[i]=change;
				m--;
			}
			if(m==0) break;
		}
		for(int i=1;i<=n;i++) if(c[i]!=c[i-1]) ans++;
		cout<<ans<<endl;
	}
	return 0;
}
```


---

