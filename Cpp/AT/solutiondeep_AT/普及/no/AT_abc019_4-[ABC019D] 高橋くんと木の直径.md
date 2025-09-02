# 题目信息

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

# AI分析结果



# [ABC019D] 高橋くんと木の直径

## 题目描述

高橋对树的直径求解产生了浓厚兴趣。树是由顶点和边构成的图结构，包含N个顶点和N-1条边，所有顶点相互连通。

给定一棵带权树，定义两顶点间距离为路径上边权之和。树的直径是相距最远的两顶点间距离。

你需要通过询问两顶点间距离的方式，在限定次数内确定树的直径。程序需完成交互式查询并输出直径值。

### 输入输出格式
程序首先读取顶点数N，通过"? a b"询问两点距离，最终以"! diameter"输出答案。每次查询后需刷新输出缓冲区。

## 算法分类
图论

## 题解综合分析
本题核心在于利用树的直径性质：任选一点u，找到离u最远的点v；再找离v最远的点w，则v-w即为直径。两次遍历即可确定直径，总查询次数为2(n-1)次，满足题目限制。

### 精选题解

1. Post_Malone（★★★★★）
关键亮点：
- 严格证明直径端点性质
- 代码简洁易读，变量命名清晰
- 完整实现两次遍历逻辑
核心代码：
```cpp
int main() {
    scanf("%d",&n);
    for(int i=2;i<=n;i++) {  // 第一次遍历找端点1的最远点
        printf("? 1 %d\n",i);
        fflush(stdout);
        scanf("%d",&s);
        if(a<s) a=s,b=i;
    }
    for(int i=1;i<=n;i++) if(i!=b) {  // 第二次遍历找最终直径
        printf("? %d %d\n",b,i);
        fflush(stdout);
        scanf("%d",&s);
        if(a<s) a=s;
    }
    printf("! %d\n",a);
    fflush(stdout);
}
```

2. cherubim（★★★★☆）
关键亮点：
- 交互流程说明清晰
- 包含算法复杂度分析
- 强调输出缓冲区刷新重要性
个人心得：
"在普通求直径时用两次DFS，但本题可以直接通过询问得到距离，交互式处理简化了算法实现"

## 最优关键思路
利用树的直径性质，通过两次遍历确定端点：
1. 任选起点找到最远端点v（必为直径端点）
2. 从v出发找到最远点w，v-w即为直径

## 拓展应用
类似树的直径问题：
1. 求树中心/重心（距离最远点最小）
2. 动态维护树的直径
3. 多直径处理问题

## 推荐习题
1. P5536【XR-3】核心城市（树的直径应用）
2. P1099 树网的核（直径相关优化）
3. P4408 [NOI2003] 逃学的小孩（直径性质应用）

---
处理用时：34.28秒