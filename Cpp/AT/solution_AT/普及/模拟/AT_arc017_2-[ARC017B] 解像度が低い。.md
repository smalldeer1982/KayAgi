# [ARC017B] 解像度が低い。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc017/tasks/arc017_2

大変なことになってしまった！！

なんと、我が社の次の決算報告会の発表者に僕が選ばれてしまったのだ！我が社のイメージのためにも、そして社内での僕の地位のためにも、なんとしても好印象を与える発表をせねばならない。

我が社の直近の業績は $ N $ 個の数からなる数列で表される。これを発表したいところだけれど……、あいにく、我が社の業績はそこまで良いとは言えないのが実情だ。一体どうすればいいんだろうか……。

途方に暮れた僕は、とりあえず発表会場の設備を調査した。なんと、これが僕の生まれ持った強運か、プロジェクターの解像度がとても低く、画面には一度に $ K $ 個の数を表示するのが限界であることがわかった。業績の数列のうちの連続する $ K $ 個をうまく選べれば、我が社の業績がうなぎのぼりであるように見せかけられるのではないだろうか？

これは最高のアイデアだと思ったが、聴衆から「それって業績の一部ですよね？他の部分も見せて頂けませんか？」と言われたらジ・エンドだ。そこで用意周到な僕は、業績の数列のうち、プロジェクターで映したときに業績が常に上昇しているように見せられるような箇所がいくつあるのか、事前に調べておくことにした。

常に成長を続ける企業であるとアピールするためには、ある値はその前の値より真に大きくなくてはいけない。つまり $ 100,\ 200,\ 300 $ という列は常に上昇していると考えるが、 $ 100,\ 200,\ 200 $ という列は常に上昇しているとは考えない。

※この問題文はフィクションです。業績はきちんと発表しましょう。

入力は以下の形式で標準入力から与えられる。

> $ N $ $ K $ $ A_1 $ $ A_2 $ : $ A_N $

- $ 1 $ 行目には、業績を表す数列の要素数 $ N\ (1\ \leq\ N\ \leq\ 300,000) $、プロジェクターで一度に表示できる数の個数 $ K\ (1\ \leq\ K\ \leq\ N) $ が半角空白区切りで与えられる。
- $ 2 $ 行目から $ N $ 行では、業績を表す数列が与えられる。このうち $ i $ 行目が $ i $ 番目の業績を表す整数 $ A_i\ (1\ \leq\ A_i\ \leq\ 300,000) $ である。

**注意:** この問題では最大で $ 300,000 $ 行ほどの入力を読み込む必要がある。ほとんどの言語では問題ないが、**Python 2.x で `input()` を使うと時間制限に間に合わないおそれがあるので、かわりに整数を読み込む際には `int(raw_input())` を使うこと。**

 業績を表す数列のうち、プロジェクターで画面に映せるような $ K $ 個の連続した部分で、その部分だけ見ると業績が常に上昇しているように見えるものの個数を標準出力に１行で出力せよ。 ```
<pre class="prettyprint linenums">
10 4
100
300
600
700
800
400
500
800
900
900
```

 ```
<pre class="prettyprint linenums">
3
```

 業績を表す $ 10 $ 個の数列から、連続する $ 4 $ 個を抜き出してみると、 - $ (100,\,\ 300,\,\ 600,\,\ 700) $ は常に上昇しているように見える
- $ (300,\,\ 600,\,\ 700,\,\ 800) $ は常に上昇しているように見える
- $ (600,\,\ 700,\,\ 800,\,\ 400) $ は常に上昇しているように見えない
- $ (700,\,\ 800,\,\ 400,\,\ 500) $ は常に上昇しているように見えない
- $ (800,\,\ 400,\,\ 500,\,\ 800) $ は常に上昇しているように見えない
- $ (400,\,\ 500,\,\ 800,\,\ 900) $ は常に上昇しているように見える
- $ (500,\,\ 800,\,\ 900,\,\ 900) $ は常に上昇しているように見えない
 
 となるので、答えは $ 3 $ であることがわかる。 ```
<pre class="prettyprint linenums">
10 3
10
40
50
80
90
30
20
40
90
95
```

 ```
<pre class="prettyprint linenums">
5
```

 この場合、常に上昇しているように見える箇所は以下の画像に矢印で示された 5 箇所となる。  
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc017_2/fb99d046b6e768145edbb7e1ae5398f78b193ad8.png)

 ```
<pre class="prettyprint linenums">
8 4
1
2
3
4
5
6
7
8
```

 ```
<pre class="prettyprint linenums">
5
```

 元々の業績が常に上昇しているので、どこをプロジェクターに映しても大丈夫である。 ```
<pre class="prettyprint linenums">
8 2
100000
90000
50000
30000
10000
4000
200
1
```

 ```
<pre class="prettyprint linenums">
0
```

 元々の業績があまりに良くない場合、どこを映しても業績を右肩上がりに見せかけられないことがある。

# 题解

## 作者：WOERDESUGX (赞：2)

本蒟蒻来写题解喽。

-----------------------

### 题目大意

在长度为 $n$ 的数组中找出长度为 $k$ 的上升序列。

------------

### 思路

设 $up$ 为目前的上升序列，$sum$ 为目前有几个上升的且等于 $k$ 的序列，$ans$ 为总共有几个长度为 $k$ 的上升序列。

从第一个开始判断本数与上一个数，如果大于，则 $up$ 加一，如果上升的序列大于等于 $k$，就将 $sum$ 变为 $up-k+1$，如果本数小于等于上一个数，就将 $ans$ 加上 $sum$，$up$ 初始为 $1$，$sum$ 初始为 $0$。

---------------------

### $ACcode$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[300050],ans=0,up=1,sum=0;
inline int read()
{
    char c = getchar();int x = 0,s = 1;
    while(c < '0' || c > '9') {if(c == '-') s = -1;c = getchar();}
    while(c >= '0' && c <= '9') {x = (x<<3)+(x<<1) + (c^48);c = getchar();}
    return x*s;
}
int main()
{
    // scanf("%d%d",&n,&k);
    n=read();k=read();
    a[0]=500000;//注意要初始为一个特别大的数以防多算
    for(int i=1;i<=n;i++) {
        // scanf("%d",&a[i]);
        a[i]=read();
        if(a[i]>a[i-1]) up++;
        else if(a[i]<=a[i-1]) {
            ans=ans+sum;up=1;sum=0;
        }
        if(up>=k) sum=up-k+1;
    }
    ans=ans+sum;//注意最后一定要加这个判断要不然会少情况
    printf("%d\n",ans);
    return 0;
}
```

----------------------------

这时我又想到了一个奇怪的方法，抱着~~逝一逝~~试一试的想法居然做对了，给大家分享一下。

-------------------

### 思路

变量和上个是一样的，只是少了一个 $sum$。

从第一个开始判断本数与上一个数，如果大于，则 $up$ 加一，当 $up$ 等于 $k$ 时，$ans$ 加一，因为我们需要继续往后判断，这时 $up$ 减一并继续向后推，不断循环，当本数小于等于上一个数时将 $up$ 变为 $1$。

----------------------

### $ACcode$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[300050],ans=0,up=1,sum=0;
inline int read()
{
    char c = getchar();int x = 0,s = 1;
    while(c < '0' || c > '9') {if(c == '-') s = -1;c = getchar();}//是符号
    while(c >= '0' && c <= '9') {x = (x<<3)+(x<<1) + (c^48);c = getchar();}//是数字
    return x*s;
}
int main()
{
    //scanf("%d%d",&n,&k);
    n=read();k=read();
    a[0]=500000;
    for(int i=1;i<=n;i++) {
        //scanf("%d",&a[i]);
        a[i]=read();
        if(a[i]>a[i-1]) up++;
        else if(a[i]<=a[i-1]) up=1;
        if(up==k) {
            ans++;
            up-=1;
        }
    }//这时不需要判断因为up是必小于k的
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：Syamoe (赞：1)

讲真的这道题黄有点过分了。

建议橙。

### 题意简述

给定一个长度为 $n$ 的数组 $a$，求有多少个 **最长连续上升子序列** 满足长度大于 $k$。

### 方法简述

首先从头开始找一遍 **最长连续上升子序列**，然后，把这个数量记录。

若数量大于 $k$，那么输出的答案就应该是 `子序列个数-k+1`

### 核心代码

~~这还有啥好写的~~

注意下数组要开的大小不然会像我一样 RE。

```cpp
int ans = 1, cnt = 0;
	for (int i = 2; i <= n; i++) {
		//找序列。
		if (a[i] > a[i - 1]) {
			ans++;
		}
		else {
			if (ans >= k) {
				cnt+= ans - k + 1;
			}
			ans = 1;
		}
	}
	if (ans >= k) {
		cnt += ans - k + 1;
	}
```

此题结。

写题解涨 rp。

---

## 作者：Soledad_S (赞：1)

**~~我做之前其实是红的，过了后刷新一下就黄了，个人认为应该普及-。~~**

因为是红题，什么都不看，~~直接打暴力~~

```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
inline int read() 
{  int bj=-1;
   char ch;
   while(!isdigit(ch=getchar()))if(ch=='-')bj=-1;
   int res=ch-'0';
   while(isdigit(ch=getchar()))
   res=(res<<1)+(res<<3)+ch-'0';
   return res;
}
int n,k,a[1000005],ans=0;
int main()//以上不解释 
{  n=read(),k=read();
   for(int i=1;i<=n;i++)a[i]=read();
   for(int i=1;i<=n+1-k;i++)//从1到n+1-k枚举序列头 
   {  int bj=1; 
      for(int j=i+1;j<=i+k-1;j++)if(a[j]<=a[j-1]){bj=0;break;}//加break爆3个，不加爆4个 
      if(bj)ans++;
   }
   printf("%d\n",ans);
   return 0;
}
```
优秀地TLE了3个点，~~话说红题还会错~~

迫不得已写正解……冷静下来想，这不就是一个LIS吗？[（不懂找度娘）](https://baike.baidu.com/item/LIS/16018280?fr=aladdin)，其实因为连续，比LIS更简单一点。于是就有了如此简明的动规：

```cpp
设f[i]为以a[i]结尾的最长连续上升子序列的长度。

初始化：f[1]=1;

状态转移方程：
  f[i]=f[i-1]+1;  (a[i]>a[i-1])
  f[i]=1;  (a[i]<=a[i-1])
  i∈(1,n];

答案：f[i]>=k的个数

```


------------

```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
inline int read()
{  int bj=-1;
   char ch;
   while(!isdigit(ch=getchar()))if(ch=='-')bj=-1;
   int res=ch-'0';
   while(isdigit(ch=getchar()))
   res=(res<<1)+(res<<3)+ch-'0';
   return res;
}
int n,k,a[1000005],ans=0,f[1000005];
int main()//以上不解释 
{  n=read();
   k=read();
   for(int i=1;i<=n;i++)
     a[i]=read();
   f[1]=1;//初始化 
   for(int i=2;i<=n;i++)
    if(a[i]>a[i-1])f[i]=f[i-1]+1;//状态转移 
      else f[i]=1;
   for(int i=1;i<=n;i++)if(f[i]>=k)ans++;//统计答案 
   cout<<ans<<endl;
   return 0;
}
```
我真是太蒟了，红题还用动态规划……

~~我为什么只写红题题解，因为我只会红题（而且也没有很多人看）~~

---

## 作者：duchengjun (赞：0)

# 题意

给你一个数组 $a$，让你求数组 $a$ 中最长连续上升子序列的长度大于 $k$ 个数。

# 分析

若 $a[i]>a[i-1]$ 就 $ans+1$,否则就把 $ans$ 置为 1。

若 $k\le ans$ 就累加求和即可。

### 注意

输出累加和后要输出换行。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=300000+10;
int n,k;
int a[N],ans=1,cnt;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=2;i<=n;i++){
		if(a[i]>a[i-1])
			ans++;
		else{
			if(ans>=k)
				cnt+=ans-k+1;
			ans=1;
		}
	}
	if(ans>=k)
		cnt+=ans-k+1;
	cout<<cnt<<endl;
	return 0;
}

```


---

## 作者：cjZYZtcl (赞：0)

## 这题可以用类似平台长度的方法来做。
我们用平台长度的方法找出每一个连续上升子序列，然后判断一下，如果这个上升子序列中的数的个数大于等于 $K$，那么可以发现，这个子序列的个数 $-K+1$ 就是这个子序列中连续的长度为 $K$ 的上升子序列的个数。

平台长度要注意一点：循环结束后还要单独在判断最后一个连续上升子序列。

## ~~人见人爱的~~代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[300005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	int s = 1, sum = 0;
	for(int i = 2; i <= n; i++){
		if(a[i] > a[i - 1]){
			s++;
		}
		else{
			if(s >= m) sum += s - m + 1;
			s = 1;
		}
	}
	if(s >= m) sum += s - m + 1;
	write(sum);
	putchar('\n');
}
```


---

## 作者：Aisaka_Taiga (赞：0)

题目翻译过来很简洁明了，就是问你长度为 k 的上升子序列的个数。

一开始我想着直接暴力枚举，每一个点都开始一个一个找，但是我觉得会超时，所以有了一个把所有数都只遍历一遍的方法：把数组从第二个数开始一个一个遍历，找到每一个上升子序列的长度，能组成的符合要求的答案数就是子序列长度减去 k 的值再加一。

知道了这些代码就很好实现了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010],n,m,ans=1,sum;//a存放每一个数的值，ans存放上升的子序列长度，sum存放答案 
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=2;i<=n;i++)
	{
		if(a[i]>a[i-1])ans++; //只要是上升的序列就一直累加长度 
		else
		{
		  if(ans>=m)sum+=ans-m+1;//只要符合m的长度能得到的长度为m的答案数就是ans减去m再加一
		  ans=1;//重置一下ans 
		}
	}
	if(ans>=m)sum+=ans-m+1;//最后的末尾处理 
	cout<<sum<<endl;//输出 
	return 0;//好习惯 
}
```

题目里面用的 $ k $,我用的 $ m $ 可能看起来有点别扭。

---

