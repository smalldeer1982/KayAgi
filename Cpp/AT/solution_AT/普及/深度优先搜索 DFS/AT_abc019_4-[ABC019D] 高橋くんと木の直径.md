# [ABC019D] 高橋くんと木の直径

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc019/tasks/abc019_4

高橋くんは木の直径を求めるのに夢中です。 木とは、頂点とそれを結ぶ辺からなる構造「グラフ」の $ 1 $ 種で、頂点の数を $ N $ 個とすると、辺は $ N-1 $ 本あり、どの頂点も他の全ての頂点に辺で間接・直接的につながっています。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc019_4/cfb0270dd13592a982ed72200a9f86b2a95a3a4d.png)

この問題では、辺には整数の重みがついています。2頂点の間の距離を、その2つの頂点をつなぐ辺の重みの和と定義します。

木の直径とは、最も離れた2つの頂点の間の距離です。

以下のような木を考えてみましょう。辺の側に書かれた数が、その辺の重みです。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc019_4/a33a3d0111cd3e05457375697b0a6985f92b86a4.png)

この場合、頂点 $ 1 $ と $ 2 $ の距離は $ 1 $、頂点 $ 2 $ と $ 4 $ の間の距離は $ 1+2=3 $ となります。頂点 $ 3 $ と $ 5 $ の間の距離は $ 3+4=7 $、頂点 $ 4 $ と $ 5 $ の間の距離も $ 2+1+4=7 $ で、この距離がこの木の頂点の間では最大なので、木の直径は $ 7 $ となります。

高橋くんは、頂点の数と $ 2 $ 頂点間の距離の情報から、木の直径を求めることに興味が出てきました。 この問題では、あなたは木の頂点の数 $ N $ を最初に与えられ、$ 2 $ 頂点の間の距離を尋ねる質問を何回か行い、木の直径を求めます。

ただし、$ 2 $ 頂点間の距離を聞く回数には制限があります。

制限された質問の回数以内で木の直径を求めるプログラムを書いてください。

### Input &amp; Output Format

まず，木の頂点の数 $ N $ が標準入力に与えられる。

> $ N $

続いて，あなたのプログラムは何回か応答プログラムに質問をする．質問のフォーマットは以下のとおりである。

> ? $ a $ $ b $

この質問で，$ a,b $ 間の距離が標準入力に1行で渡される。$ 1\ ≦\ a,\ b\ ≦\ N $ かつ $ a≠b $ を満たしていなければならない。

何回か質問を行った後、あなたは木の直径を当てる。木の直径を $ diameter $ とおくと、

> ! $ diameter $

というフォーマットで出力する。木の直径を出力した後、あなたのプログラムは直ちに終了しなければならない。終了しなかった場合のジャッジ結果は不定である。

また、これら以外のフォーマットで出力した場合のジャッジ結果も不定である。

この問題ではテストケースごとに質問回数の上限値が設定されており、プログラムの行った質問の回数がその上限値を上回ると誤答と判定される。

正答かどうかは木の直径の出力で判断される。木の直径を特定し得ない質問しかしていない場合でも、直径が正しければ正答となる。

- - - - - -

頂点 $ 1 $ と頂点 $ 2 $ の間の距離を質問し、$ dist $ という変数で結果を受け取る例をいくつかの言語について示す。

ただし、ここに書かれている方法以外で入出力を行っても良い。

出力した後に、出力をflushしなければならないことに注意せよ。flushしなかった場合、TLEとなることがある。

C

```
<pre class="prettyprint linenums" style="font-size: 12px; letter-spacing: 0;">
printf("? %d %d\n", 1, 2);
fflush(stdout);
scanf("%d", &dist);
```

C++

```
<pre class="prettyprint linenums" style="font-size: 12px; letter-spacing: 0;">
cout > dist;
```

Java

```
<pre class="prettyprint linenums" style="font-size: 12px; letter-spacing: 0;">
System.out.printf("? %d %d\n", 1, 2);
Scanner scanner = new Scanner(System.in);
dist = scanner.nextInt();
```

C#

```
<pre class="prettyprint linenums" style="font-size: 12px; letter-spacing: 0;">
Console.WriteLine("? {0} {1}", 1, 2);
dist = int.Parse(Console.ReadLine());
```

D

```
<pre class="prettyprint linenums" style="font-size: 12px; letter-spacing: 0;">
writeln("? ", 1, " ", 2);
stdout.flush();
dist = readln.chomp.to!int;
```

PHP

```
<pre class="prettyprint linenums" style="font-size: 12px; letter-spacing: 0;">
echo "? ", 1, " ", 2, PHP_EOL;
$ dist\ =\ trim(fgets(STDIN));


Python

print\ "?\ {0}\ {1}".format(1,\ 2)
sys.stdout.flush()
dist\ =\ int(raw_input())


Perl $|=1;
print "? ", 1, " ", 2, "\n";
$dist = ;
```

Ruby

```
<pre class="prettyprint linenums" style="font-size: 12px; letter-spacing: 0;">
print "? ", 1, " ", 2, "\n"
STDOUT.flush
dist = gets.to_i
```

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 50 $
- $ 1\ ≦\ (それぞれの辺の重み)\ ≦\ 10^6 $

### 部分点

この問題には部分点が設定されている。

- $ 20 $ 点分のテストケースにおいて、質問回数の上限値は 1300 回である。
- 別の $ 80 $ 点分のテストケースにおいて、質問回数の上限値は 100 回である。

### 入出力例

木が以下のような形状のとき、

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc019_4/cee5f2e74e5e3c979be3ad1dfb861be11590dd76.png)

以下のような入出力が考えられる。

 プログラムへの入力 プログラムの出力 5     ? 1 2 5     ? 2 4 1     ? 4 5 2     ? 2 3 9     ? 1 5 8     ! 14これは入出力の一つの例であり、意味のある質問をしているとは限らない。

# 题解

## 作者：Post_Malone (赞：2)

## 一道入门难度的树形DP题  
首先我们必须要知道这样一个结论：  
```
任取一点为根结点，遍历整棵树，找到距离结点1最远的点s1。s1必为直径的一个端点。

以s1为根，找到距离s1最远的点s2，s1→s2即为直径。
```
蒟蒻的证明：(会证明的大佬自行跳过)  
假设距离结点1最远的点s1不是直径的端点，s3,s4才是直径端点 
因为s3→s4是直径  
所以易发现1→s3或1→s4必定大于1→s1。(可以自己画图试试)  
显然，s3或s4才是距离结点1最远的点，违反假设，假设不成立。原结论正确。    
证毕  
显然有了这个结论，这道题目已经不难AC了，代码：  
```cpp
#include<cstdio>
int a,b,s,n; //a:最大距离 b:记录结点
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)  //寻找距离1最远的s1
	{
		printf("? 1 %d\n",i);
		fflush(stdout);  //翻译已经说了输出格式
		scanf("%d",&s);
		if(a<s)a=s,b=i;  //记录s1和最大距离
	}
	for(int i=1;i<=n;i++)if(i!=b)  //再找距离s1最远的s2
	{
		printf("? %d %d\n",b,i);
		fflush(stdout);
		scanf("%d",&s);
		if(a<s)a=s;  //记录最大距离
	}
	printf("! %d\n",a);  //输出最大距离(换行！)
	fflush(stdout);
	return 0;
}
```
题目不是很难，大家一定要独立完成哦~

---

## 作者：cherubim (赞：0)

updata:修改了文章及代码格式。

## 题目 AT1204 高橋くんと木の直径

头一次见到这么简单的交互题。。可能这题重点不在题目本身而是熟悉交互的过程吧。


在普通的求树的直径的时候，我们一般用两次 dfs 来进行求解。不知道怎么求树的直径可以去 [OIWIKI](https://oi-wiki.org/graph/tree-diameter/) 看看。

但对于其中说到的两种方法，本题都用不到。因为两次 dfs 或 dp 的核心作用是求出两点之间的最短距离，但这题可以直接通过询问来得到，~~真是强大的交互库~~。

所以我们只需要从任意一节点开始对其他点询问，取最长的一个点作为树直径的一端。从这一节点开始对其他点进行询问，找到长度最长的一个点，这两点之间的距离即为这棵树的直径。  

### CODE


~~~cpp
#include <bits/stdc++.h>
using namespace std;
int n , point , len , dist ; 
int main ( ) 
{
    scanf ( "%d" , &n ) ; 
    for ( int i = 2 ; i <= n ; ++ i ) {
        printf ( "? 1 %d\n" , i ) ;//进行询问
        fflush ( stdout ) ; //按照题目中所说关掉输出缓存区
        scanf ( "%d", &dist ) ; //输入询问结果
        if ( len < dist ) 
            point = i , len = dist ; //更新答案
    }
    len = 0 ; //求到第一个点过后记得重置len的长度
    for ( int i = 1 ; i <= n ; ++ i ) {
        if ( i == point ) //不能自己到自己
            continue ; 
        printf ( "? %d %d\n" , point , i ) ; 
        fflush ( stdout ) ; 
        scanf ( "%d" , &dist ) ; 
        if ( len < dist ) 
            len = dist ; //更新答案
    }
    printf ( "! %d\n" , len ) ; 
    fflush ( stdout ) ; 
    return 0 ; 
}

~~~


---

