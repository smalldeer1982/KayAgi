# [USACO07OPEN] 翻转棋 Fliptile S

## 题目描述

FJ 知道，智商高的奶牛产奶量也大，所以他为奶牛们准备了一个翻动瓦片的益智游戏。

在一个 $M \times N$ 的方阵上（$1 \leq M,N \leq 15$），每个格子都有一个可以翻转的瓦片。瓦片的一面是黑色，另一面是白色。对一个瓦片翻转，可以让它的颜色由黑到白，或是由白到黑。

然而奶牛们很笨拙，它们翻转一个格子的瓦片时，与其有公共边的所有瓦片也会翻转。

现在奶牛们想知道，至少需要多少次翻转，使所有的瓦片都变成白色朝上呢？

## 说明/提示

下面的方案操作次数同样是最小的，但是字典序不是最小的。

```plain
0 1 1 0
0 0 0 0
0 0 0 0
0 1 1 0
```

## 样例 #1

### 输入

```
4 4 	
1 0 0 1 	
0 1 1 0 	
0 1 1 0 	
1 0 0 1```

### 输出

```
0 0 0 0 	
1 0 0 1 	
1 0 0 1 	
0 0 0 0```

# 题解

## 作者：world_execute (赞：78)

> ## [[ 更好的阅读体验 ]](https://www.luogu.org/blog/execute/solution-p1985)
> ## [[    原题面    ]](https://www.luogu.org/problemnew/show/P1985)
------------

### 第零部分 —— 阅读题目

- 题目大意：有 M*N 个格子，一面是白色，另一面是黑色。给你一个操作，翻转某个位置，使这个位置和与它有公共边的所有格子变换一次颜色（黑->白，白->黑）。现在，给你一个初始状态，问你如何翻转，才能使翻转次数最小，如有多个解，输出字典序最小的那个，如果无解，输出“IMPOSSIBLE"（忽略引号）

- 数据范围：1 ≤ M, N ≤ 15

- So，看到这个数据范围，是不是觉得出题人很良心，但在看完题目之后，发现 2^30 太大了 ~~（连int都快存不下了）~~ 几乎无法得分

------------
### 第一部分 —— 开始分析
- 首先，我们可以从数据范围知道，单纯地去枚举每个位置的翻转情况是一定过不了全部的测试点的

- 这样枚举的时间复杂度约是 O（2^(n+m)），因为总共 n*m 个点，每个点可以反转或者不反转

- So，上面的时间复杂度是我们无法接受的，必须降下来

------------
### 第二部分 —— 初现思路

- 通过题目我们可以知道，我们要把所有点反转成白色

- So，我们要尽可能地让某一部分都变成白色，然后在保证之前的白色部分不会缩小的条件下，慢慢地扩大，直到覆盖整个棋盘 ~~（ 有没有一点像转魔方？ ）~~

------------
### 第三部分 —— 深入思考

- 通过上面的分析，我想出一种方法 ~~（当然，没看过题解 QAQ）~~：还是枚举 ~~（善变的我）~~

- 先枚举第一行（其实枚举任何一行，或任何一列都可以得出结果，见延伸阅读①  ）

- 再根据之前说的：“我们要慢慢扩大，直到覆盖整个棋盘” ，但是这句话的根本条件是保证白色部分不会缩小。

- So，如何保证白色区域不会缩小，是这道题的突破口


------------
### 第四部分 —— 解决问题
- ~~（这一部分的标题是不是很像大部分数学试卷的最后一大题？）~~

- 接着，分析题目，每一次反转，都会把一个“十”字形区域取反，it looks like this：

         ...+---+---+---+...
         ...|   | * |   |...
         ...+---+---+---+...
         ...| * | * | * |...
         ...+---+---+---+...
         ...|   | * |   |...
         ...+---+---+---+...
          （星号标注区取反）
           Tips: 取反  1->0  0->1 ,相当于 not 或 ! 
           		 但是代码中，本人喜欢使用 1-X 来取反

- ~~（新奇的画风）~~

- 如果哪一格不是0的话，我们就可以在它的下方进行反转。（具体为什么是下方，见 延伸阅读① ）

- 使用这样的方法，除了第一行以外，我们都可以解决，只用在完成之后，判断一下，最后一行是不是都是0，如果是，我们就得出了一个答案，在加上一些判断，这部分代码就完成了

- 在这一部分代码完成是，我们还需要注意的是，每次都要出现一个Shadow数组，在每次操作 ~~（骚操作？）~~ 之前，必须保存现场，~~（Sounds like a search algorithm）~~，在最后还原。

- So，在枚举时，我们用搜索解决好了 ~~（这更体现出了我的善变， o(*////▽////*)q ）~~ ，在加上前面的思路，与输入输出，代码就可以开始打啦。<(￣︶￣)↗[GO!]


------------

### 第五部分 —— 代码实现

- 输入部分，我相信大家都写得出啦

- 反转部分，这十分的简单，但是要注意如果使用坐标位置不要搞混

- 搜索部分，万一有比我还弱的蒟蒻的话，我只好写出来了：

```cpp
void Work(int k)
{
	if (!k) Doit();              // 全部枚举好了
	else
	{
		Work(k - 1);               // 递归不反转
		Reversal(1, k), ++b;       // 翻转一下，用来递归翻转情况
		Work(k - 1);               // 递归翻转
		Reversal(1, k), --b;       // 翻转一下，用来还原
	}
}
```
- 这个函数写的不是特别美观 ~~（如果有 int main(){} 这样的函数就好了）~~ 但也可以凑合看看

- 其中的 k 表示还有多少个位置没有选，b表示翻转了多少次，因为需要输出最少翻转次数

- 也许有的同学会问：为什么不用“选了多少个位置”来表示k呢？为了代码短，如果你有自己的习惯，请不要学本人

- Doit，这只需要把思路翻译成代码就好了，但是我还是觉得出示一下 ~~伪~~ 代码更好一点：

```cpp
void Doit()
{
	Map = Shadow
	For (i = 1..n-1)
		For (j = 1..m)
			If (Map[i][j])
				Reversal(i+1,j),++p;//注意i从1到n-1
	Flag = 1;
	for (int j=1..m; Flag&=(!Map[n][j++]));     //判断最后一行是不是全为0
	if ((p+b<D || (p+b==D && Judger()) || D==-1) && Flag)
	{
		Ans = ans
		D = p+b
	}                                           //判断是否符合替换要求
	Shadow = Map
    Ans[2][1] ~ Ans[n][m] = 0
}
```

- 其中D表示目前最优解的反转次数，Judger表示与当前解进行字典序比较，其他就自己去理解吧。 (>▽<)

- 输出，相信你们会写的比本人好的，我就不浪费笔墨了，主要就是无解时需要输出“IMPOSSIBLE”需要注意

- So，第五部分的代码实现就解决了，是不是觉得还比较简单，还有本人第一次在洛谷发布题解，不知道如何写才好，如果有没讲清楚的地方，尽管在评论中回复，我尽量做到有问必答。

------------

### 第六部分 —— 后记？

- 管理员大大要体谅我这个大年初一在家一个人码代码的人 ~~（空巢寂寞老人？？？）~~ 我已经尽力把这篇题解写好了，如果还有什么地方写的不好的 ~~(因为我们是为人民服务的QAQ)~~ ，我会继续改进的

- 当然，这不是真正的后记，还有延伸阅读没有写呢

- So，大家所期望的延伸阅读就成了第七部分 ~~（也许只有我期望）~~


------------

### 第七部分 —— 延伸阅读①

- 当然，并没有延伸阅读②

- 你可以选择任何一行或一列

- 如果你选择某一行，但是它不是第一行，或最后一行的话，那么每个数字，不管你想把他从“1”变成“0”，还是从“0”变成“0”，都会出现两种方案

- 因为在你想把“1”变成“0”时，可以在上方翻转，或是在下方翻转。当你想把“0”变成“0”时，有可能时上下都不翻转，或是上下同时翻转

- 这样，时间复杂度将会飙升，因为你又需要枚举的次数要增加 2^n 次，但最后总是能得出正确答案，但时间复杂度为 O(2^(n+1)+n^2)

- 列也一样，最好选择第一列或最后一列

- 这样，如果不是用第一行（列）或最后一行（列）的话，会非常麻烦，代码不好实现，时间复杂度也更打大，这是得不偿失的

- So，这就是为什么我用第一行作为起始行了 ~~（当然，第一列也可以）~~



------------

### 第八部分 —— 真·后记

- 不知不觉就写了这么多了呢，希望各位给我一个赞，或是给予我您的宝贵的意见

- So，题解就到这了吧

---

## 作者：kradcigam (赞：31)

## 讲讲我的做法

刚开始做这道题的时候，看到 $n<=15$，我这个 $6$ 年级的蒟蒻的第1反应是状压 $dp$。貌似不好做。然而，等到我在省中集训的时候，老师的一席话，让我豁然开朗。今天我准备来分享一下。
**老师的话是：除了第1行，其他格子要不要翻是由上一行决定的。**
听到这里，我想应该跟那时的我一样——豁然开朗了。

用 $dfs$ 或用2进制来枚举第1行要不要翻（推荐用 $dfs$，不容易 $WA$，并且时间充裕的很），然后去模拟后面的格子，最后再看最后一行是否全好了。

我们先来看看 $dfs$ 该怎么写

$code$：

```cpp
void dfs(int x){
	if(x==m+1){
		check();//打擂法
		return;//不要再做下去了，已经是终点了
	}
	f[x]=0;//先试0的情况
	dfs(x+1);//递归下去
	f[x]=1;//再试1的情况
	dfs(x+1);//递归下去
}
```
我也放一下二进制的代码吧
```cpp
for(int i=0;i<(1<<m);i++){
	for(int j=0;j<m;j++)f[j+1]=(i>>j)&1;
	check();
}
```
大家发现我这个 $check$ 竟然没有用$bool$，是因为我们第 $1$ 次找到的答案不一定就是最优解，最终的答案我们是通过打擂法求出来的。

给大家看一看 $check$ 函数的实现过程

```cpp
void work(int x,int y){
	c[x][y]=1-c[x][y];
	c[x-1][y]=1-c[x-1][y];
	c[x+1][y]=1-c[x+1][y];
	c[x][y-1]=1-c[x][y-1];
	c[x][y+1]=1-c[x][y+1];
}//这里为了方便写了个函数来模拟翻格子
void check(){
    memset(b,0,sizeof(b));
    int s=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            c[i][j]=a[i][j];//初始化
    for(int i=1;i<=m;i++)
        if(f[i]){
            work(1,i);//模拟出第一行的反转情况
            b[1][i]=1;
        }
    for(int i=2;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(c[i-1][j])b[i][j]=1,work(i,j);//跟据老师的那句话，去模拟
    for(int i=1;i<=m;i++)
        if(c[n][i])return;//如果是1直接结束
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(b[i][j]==1)s++;//计算值
    if(s<ans){//打擂
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                d[i][j]=b[i][j];
        ans=s;
    }
}
```
应该没有什么问题

我们来看一看完整的代码吧

$dfs:$
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
    register int s=0,f=1;
    register char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f*=-1;ch=getchar();}
    while(isdigit(ch))s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
    return s*f;
}//快读
void write(int x){
    if(x>9)write(x/10);
    putchar(x%10+48);
}
int a[25][25],f[25],n,m,b[25][25],c[25][25],ans=INT_MAX,d[25][25];
void work(int x,int y){
	c[x][y]=1-c[x][y];
	c[x-1][y]=1-c[x-1][y];
	c[x+1][y]=1-c[x+1][y];
	c[x][y-1]=1-c[x][y-1];
	c[x][y+1]=1-c[x][y+1];
}//这里为了方便写了个函数来模拟翻格子
void check(){
    memset(b,0,sizeof(b));
    int s=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            c[i][j]=a[i][j];//初始化
    for(int i=1;i<=m;i++)
        if(f[i]){
            work(1,i);//模拟出第一行的反转情况
            b[1][i]=1;
        }
    for(int i=2;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(c[i-1][j])b[i][j]=1,work(i,j);//跟据老师的那句话，去模拟
    for(int i=1;i<=m;i++)
        if(c[n][i])return;//如果是1直接结束
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(b[i][j]==1)s++;//计算值
    if(s<ans){//打擂
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                d[i][j]=b[i][j];//更新值
        ans=s;
    }
}
void dfs(int x){
    if(x==m+1){
        check();
        return;
    }
    f[x]=0;
    dfs(x+1);
    f[x]=1;
    dfs(x+1);
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            a[i][j]=read();//读入
    dfs(1);
    if(ans==INT_MAX)puts("IMPOSSIBLE");
    else{
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)cout<<d[i][j]<<' ';
            cout<<endl;
        }
    }
    return 0;
}
```
二进制：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
    register int s=0,f=1;
    register char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f*=-1;ch=getchar();}
    while(isdigit(ch))s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
    return s*f;
}
void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+48);
}
int a[25][25],f[25],n,m,b[25][25],c[25][25],ans=INT_MAX,d[25][25];
void work(int x,int y){
    c[x][y]=1-c[x][y];
    c[x-1][y]=1-c[x-1][y];
    c[x+1][y]=1-c[x+1][y];
    c[x][y-1]=1-c[x][y-1];
    c[x][y+1]=1-c[x][y+1];
}//这里为了方便写了个函数来模拟翻格子
void check(){
    memset(b,0,sizeof(b));
    int s=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            c[i][j]=a[i][j];//初始化
    for(int i=1;i<=m;i++)
        if(f[i]){
            work(1,i);//模拟出第一行的反转情况
            b[1][i]=1;
        }
    for(int i=2;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(c[i-1][j])b[i][j]=1,work(i,j);//跟据老师的那句话，去模拟
    for(int i=1;i<=m;i++)
        if(c[n][i])return;//如果是1直接结束
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(b[i][j]==1)s++;//计算值
    if(s<ans){//打擂
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                d[i][j]=b[i][j];
        ans=s;
    }
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=read();
	for(int i=0;i<(1<<m);i++){
	    for(int j=0;j<m;j++)f[j+1]=(i>>j)&1;
	    check();
	}
	if(ans==INT_MAX)puts("IMPOSSIBLE");
	else{
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)cout<<d[i][j]<<' ';
			cout<<endl;
		}
	}
	return 0;
}
```
## 后记
**Update：衷心感谢 @龙·海流 大佬帮我指出了一个致命的错误**

**Update：衷心感谢 @TheStars 大佬帮我指出了一个致命的错误**

这是我[原来的代码](https://www.luogu.org/paste/05qcgwu7)

**注意题目中说的是翻转次数少的优先，如果一样，再按照字典序排列。**我自己不认真读题，还去怪数据错误，还特判了数据。

衷心感谢省中集训的那位老师~~让我AC了一道蓝题~~。。

如果我的这篇题解对你有所帮助请点个赞，谢谢。。

有任何问题，请评论或私信我这个$6$年级的蒟蒻，谢谢。

---

## 作者：NightStriker (赞：9)

位运算好题。

---

我们考虑将输入进来的 $01$ 数组转换为一维数组，也就是把每一行看成一个二进制字符串再转化成数字。

这样的好处就是，中间进行操作的时候会方便很多。只需要行和行之间进行操作就可以了。

在这种情况下我们如何转化呢？可以参考整数输入的例子。

例如：我们要输入一个数组：$1\ 1\ 4\ 5\ 1\ 4$，我们要将其转化成变量 $114514$。

每次读入的时候将原先的答案 $\times 10$，将要输入进来的数字空出位置。

设输入的数为 $x$，每次只要将 $a_i \times 10+x$ 就可以了。

同样，在 $01$ 串下，每次可以将数字左移一位—— $111 \rightarrow 1110$，再或一下新的 $0/1$ 就可以了。

也就是 `a[i] = (a[i] << 1) | x`。

这样我们就解决了输入的问题。

```cpp
for(int i = 1; i<=n; i++) {
	t[i] = 0;
	for(int j = 1; j<=m; j++) {
		cin>>x;
		t[i] = t[i]<<1|x;
	}
}
```

---

这里补充一下位运算的一些简单的性质。会的就不用看了。

如果想截取一个数字 $x$ 的后 $n$ 位（在二进制下），可以使用 `x & ((1 << n) - 1)` 来解决。

`1<<n` 代表 $n$ 位的 $10000 \cdots$（共 $n-1$ 个 $0$），我们如果将它 $-1$ 这个 $01$串就会变成 $11111 \cdots$（$n-1$ 个 $1$）。众所周知，与 运算符只有在两位同时为 $1$ 的时候才会为 $1$，所以 $x$ 多出 $n$ 的那几位都会为 $0$，这样也就完美的截取了 $x$ 的前 $n$ 位。

---

这道题涉及一个递推的性质。

如何递推呢？只需要填出第一行，后面的就可以按照前面的贪心地来变化。

这样只要枚举第一行的所有修改可能，然后**每次按照上次没有改过来的 $1$ 尽量让他变成 $0$ 就可以了。**（贪心策略）

所以时间复杂度仅为 $\mathcal{O}(2^m n)$。

```cpp
cz[1] = i;
for(int j = 1; j<=n; j++) a[j] = t[j];//因为a数组会改变，t数组才是初始数组
	for(int j = 1; j<=n; j++) {
		cnt+=ljp(cz[j]);//统计
		a[j]^=(cz[j]^(cz[j]>>1)^(cz[j]<<1))&((1<<m)-1);//操作当前列
		a[j+1]^=cz[j];//先操作下一行。
		cz[j+1] = a[j];//下一列的操作是这一列。
	}
```

然后我们要打擂台取最小，编一个函数来计算数字中有多少个 $1$。以此判断出是否是最优解。

你也可以使用 `__builtin_popcount` 来解决。

```cpp
int ljp(int n) {
	int sum = 0;//计数器
	while(n>0) {
		if(n&1==1) sum++;//如果当前位是1计数器就+1
		n>>=1;//这一位看完了，看下一位。
	}
	return sum;
}
```

对于无解的情况下，如果答案还是原来的值，就输出 $\texttt{IMPOSSIBLE}$。

---

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,cnt,mn = INT_MAX,ans[17],t[17],a[17],cz[17];//ans为存储答案，t为初始数组，cz为操作。
int ljp(int n) {//统计有几个1
	int sum = 0;
	while(n>0) {
		if(n&1==1) sum++;
		n>>=1;
	}
	return sum;
}
int main() {
	cin>>n>>m;
	for(int i = 1; i<=n; i++) {
		t[i] = 0;
		for(int j = 1; j<=m; j++) {
			cin>>x;
			t[i] = t[i]<<1|x;//输入操作
		}
	}
	for(int i = 0; i<(1<<m); i++) {
		cnt = 0;
		cz[1] = i;
		for(int j = 1; j<=n; j++) a[j] = t[j];
		for(int j = 1; j<=n; j++) {
			cnt+=ljp(cz[j]);
			a[j]^=(cz[j]^(cz[j]>>1)^(cz[j]<<1))&((1<<m)-1);
			a[j+1]^=cz[j];
			cz[j+1] = a[j];
		}
		if(a[n]==0&&cnt<mn) {//取最小
			mn = cnt;
			for(int k = 1; k<=n; k++) ans[k] = cz[k];//保存答案
		}
	}
	if(mn==INT_MAX) {//判断无解
		cout<<"IMPOSSIBLE"<<endl;
		return 0;
	}
	for(int i = 1; i<=n; i++) {
		for(int j = m; j>=1; j--) {
			cout<<(ans[i]>>(j-1)&1)<<' ';//输出，注意要还原。
		}
		cout<<endl;
	}
	return 0;
}
```



---

## 作者：租酥雨 (赞：7)

今天上午考了这道题，得了60分，这里讲一下当时的思路和现在AC的思路

题目关键字：最小次数、字典序

首先大家可以想一想，翻动顺序改变是没有影响的，同一个点翻两次等于没翻。

so，每个点的翻动次数只可能是0或1

这自然让我们想到了dfs，我们从点（1,1）开始，每个点依次放置0和1，并且时刻留意剪枝；

剪枝的条件是酱紫的：因为任意一个位置的翻动会影响到上下左右四个位置，那么当我们依字典序搜到了某一位置并完成了翻动，就应该去检查其上方的位置是否已经满足要求（翻成白色），若不满足条件则剪枝

当我们搜到目标节点（m,n）时，前m-1行都已经翻完了，那么我们就要去判断是否最后一行可以翻完

一个问题：第一个搜到的不是正解！第一个搜到的不是正解！第一个搜到的不是正解！

如果我们只看字典序的话，就不能保证翻动次数一定最小，因此我们就需要一个record函数，用于记录最优解

精髓dfs最好带三个参，表示当前点的坐标以及已经翻动了多少次，与已记录到的最小值比较


具体详见代码

//因为下一行翻动会影响上一行 所以在i>=2时只检查上点（只有上点能确保不再被翻动）

//那么 在搜到底的时候 还要检查最下面一行是否满足







```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool map[16][16]={0};//当前棋盘的形式 1为黑(需要翻转) 0为白(不需要翻转) 
bool ans[16][16]={0};//记录答案 1为翻动了 0为没有翻动 
bool final[16][16]={0};//记录最优解 
int m,n;
int Min=2147483647;
bool check(int x,int y)
{
    if (x>=2)
    {
        if (map[x-1][y]==0) return true;
        else return false;
    }
    else return true;
}
bool check_final()
{
    for (int a=1;a<=n;a++)
       if (map[m][a]) return false;//一旦有1就说明不通过 
    return true; 
}
//本题不是单纯字典序！ 本题不是单纯字典序！ 本题不是单纯字典序！ 
// 这里标注一个问题：本题先求1数目最少的 再要求字典序最小的 
//so 找到第一个并不能直接输出 
void record(int t)
{
    if (t<Min)
    {
        for (int i=1;i<=m;i++)
           for (int j=1;j<=n;j++)
              final[i][j]=ans[i][j];
        Min=t;
    }
}
void turn(int x,int y)//对位置x y进行翻转 
{
    map[x][y]=map[x][y]?0:1;
    if (x>1) map[x-1][y]=map[x-1][y]?0:1;
    if (x<m) map[x+1][y]=map[x+1][y]?0:1;
    if (y>1) map[x][y-1]=map[x][y-1]?0:1;
    if (y<n) map[x][y+1]=map[x][y+1]?0:1;
}
void dfs(int i,int j,int t)//位置是(i,j) 当前翻转的次数为t
{
    for (int k=0;k<=1;k++)//选择翻还是不翻 先选0再选1 
    {
        ans[i][j]=k;
        if (k==1) turn(i,j);
        if (check(i,j)==0) //若不满足则剪掉 
        {
            if (k==1) turn(i,j);
            continue;
        }
        if (i==m&&j==n) //如果到了目标点 
        {
            if (check_final()==1) record(t+k);//若最终检查不通过 也不能过 
        }
        else if (j==n) dfs(i+1,1,t+k);
        else dfs(i,j+1,t+k);
        if (k==1) turn(i,j);
        if (t>=Min) return ;
    }
}
int main()
{
    //freopen("fliptile.in","r",stdin);
    //freopen("fliptile.out","w",stdout);
    scanf("%d %d",&m,&n);
    for (int i=1;i<=m;i++)
       for (int j=1;j<=n;j++)
          scanf("%d",&map[i][j]);
    dfs(1,1,0); 
    if (Min==2147483647) printf("IMPOSSIBLE");
    else for (int i=1;i<=m;i++)
    {
        for (int j=1;j<=n;j++)
            printf("%d ",final[i][j]);
        printf("\n");  
    }
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
```

---

## 作者：林则徐 (赞：5)

此题可建立异或方程组，再用高斯消元法来解。

首先建立一个$mn$个异或方程：

$a_{11}x_{1}$ XOR $a_{12}x_{2}$ XOR ... XOR $a_{1mn}x_{mn}$ = $b_{1}$

$a_{21}x_{1}$ XOR $a_{22}x_{2}$ XOR ... XOR $a_{2mn}x_{mn}$ = $b_{2}$

... ... ...

$a_{mn1}x_{1}$ XOR $a_{mn2}x_{2}$ XOR ... XOR $a_{mnmn}x_{mn}$ = $b_{mn}$

其中$b_{i}$表示$i$位置的初始状态；$a_{ij}$若为1，则表示$i$位置状态会随$j$位置状态的改变而改变（注意$i$和$j$不要记反），显然，在此题中，对于任意$ni+j$，仅$a_{ni+j,ni+j}$ 、$a_{(n-1)i+j,ni+j}$ 、$a_{(n+1)i+j,ni+j}$、$a_{ni+j-1,ni+j}$、$a_{ni+j+1,ni+j}$为1;$x_i$若为1，则表示要翻$i$位置。

然后建立增广矩阵，用高斯消元法消成阶梯形矩阵，即：

$a_{11}$ $a_{12}$ $a_{13}$  ... $a_{1mn}$ $b_{1}$  

0  $a_{22}$ $a_{23}$ ... $a_{2mn}$ $b_{2}$ 

0  0  $a_{33}$ ... $a_{3mn}$ $b_{3}$

... ... ...

0 0 0 ... $a_{mnmn}$ $b_{mn}$   

注意每次消是异或整行，不是加或减。

之后再从下往上消。若某行$a_{ii}$ 为 1 ，则$x_{i}$只有一个取值$b_{i}$；若$a_{ii}$与$b_{i}$均为0，则$x_{i}$为1或0均可，分别代入后取较优的；若$a_{ii}$为0但$b_{i}$为1，显然是无解的。           

时间复杂度为$O(m^3n^3)$，但是常数较小，可以0ms跑过。

附上代码：
```
#include<cstdio>
#include<algorithm>
#include<vector>
#define LL long long
#define Max(a,b) (((a)>(b))?(a):(b))
#define Min(a,b) (((a)>(b))?(b):(a))
#define For(a,b,c,d) for(register int a=b;a<=c;a+=d)
#define FOR(a,b,c,d) for(register int a=b;a<c;a+=d)
#define Rep(a,b,c,d) for(register int a=b;a>=c;a-=d)
#define REP(a,b,c,d) for(register int a=b;a>c;a-=d)
#define INF 0xffffff

const int N = 230 , mx[ 4 ] = { 1 , 0 , -1 , 0 } , my[ 4 ] = { 0 , 1 , 0 , -1 } ;
int n , m , r ; 
int a[ N ][ N ] , ans[ N ] , b[ N ] , minn ;

inline void Swap( int i , int j , int p ) {
    For( k , p , r , 1 ) {
        std::swap( a[ i ][ k ] , a[ j ][ k ] ) ;
    }
}

inline void Xor( int i , int j , int p ) {
    For( k , p , r , 1 ) {
        a[ i ][ k ] ^= a[ j ][ k ] ;
    }
}

void dfs( int res , int cnt ) {
	if( cnt > minn )
		return ;
	if( res < 0 ) {
		FOR( i , 0 , r , 1 ) {
			ans[ i ] = b[ i ] ;
		}
		minn = Min( minn , cnt ) ;
		return ; 
	}
 	if( !a[ res ][ res ] && a[ res ][ r ] ) {
    	return ;
    }
    std::vector< int > vis ;
    if( !a[ res ][ res ] && !a[ res ][ r ] ) {
    	b[ res ] = a[ res ][ r ] = 1 ;
        Rep( j , res - 1 , 0 , 1 ) {
	        if( a[ j ][ res ] ) {
	            a[ j ][ r ] ^= 1 ;
	            vis.push_back( j ) ;
	        }
    	}
    	dfs( res - 1 , cnt + 1 ) ;
		Rep( j , vis.size() - 1 , 0 , 1 ) {
			a[ vis[ j ] ][ r ] ^= 1 ;
		}
		a[ res ][ r ] = b[ res ] = 0 ; 
    	dfs( res - 1 , cnt ) ;
    	return ;
    }
    b[ res ] = a[ res ][ r ] ;
    if( b[ res ] ) {
	    Rep( j , res - 1 , 0 , 1 ) {
	        if( a[ j ][ res ] ) {
	            a[ j ][ r ] ^= 1 ;
	            vis.push_back( j ) ;
	        }
	    }
		dfs( res - 1 , cnt + b[ res ] ) ; 
		Rep( j , vis.size() - 1 , 0 , 1 ) {
			a[ vis[ j ] ][ r ] ^= 1 ;
		}
	}
	else {
		dfs( res - 1 , cnt ) ;
	}
}

int main() {
    scanf("%d %d ", &n , &m ) ;
    int t , p , tx , ty ;
    r = m * n ;
    FOR( i , 0 , n , 1 ) {
        FOR( j , 0 , m , 1 ) {
            p = i * m + j ;
            scanf("%d", &t ) ;
            if( t )
                a[ p ][ r ] = 1 ;
            a[ p ][ p ] = 1 ;
            For( k , 0 , 3 , 1 ) {
                tx = i + mx[ k ] ;
                ty = j + my[ k ] ;
                if( tx < 0 || ty < 0 || tx >= n || ty >= m )
                    continue ; 
                a[ tx * m + ty ][ p ] = 1 ;
            }
        } 
    }
    bool flag ;
    FOR( i , 0 , r , 1 ) {
        flag = 0 ;
        FOR( j , i , r , 1 ) {
            if( a[ j ][ i ] ) {
                flag = 1 ;
                Swap( j , i , i ) ;
                break ;
            }
        }
        if( !flag )
            continue ;
        FOR( j , i + 1 , r , 1 ) {
            if( a[ j ][ i ] )
                Xor( j , i , i ) ;
        }
    }
    minn = INF ;
    dfs( r - 1 , 0 ) ;
	if( minn == INF ) {
		printf("IMPOSSIBLE") ;
    	exit( 0 ) ;
	}
    FOR( i , 0 , n , 1 ) {
        FOR( j , 0 , m , 1 ) {
            printf("%d " , ans[ i * m + j ] ) ;
        }
        printf("\n") ;
    }
    return 0 ;
} 
```


---

## 作者：s_a_b_e_r (赞：4)

## 枚举

我们发现当第一行确定下来之后,要满足合法,只能通过改变下一行的情况来使上一行合法.

也就是说,当前行可以不用合法,但是再下一行进行的操作一定可以使当前行合法。

所以当前位置$(x_i,y_i)$需要改变的条件就是$(x_{i-1},y_i)$在本次操作前是1

这次操作全部合法就是最后一行改变后全是0;

于是就枚举第一行的改变,剩下的行和列就递推出来。

我枚举的方式是二进制~~(其实是不太会dfs)~~当前位置需要改变就是当前所在的二进制数是1

判断当前是否改变,只要看当前所枚举的数x and(1<<位置)就可以了

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cmath>
#define ll long long
using namespace std;
const int maxn=20;
inline int read(){
    int an=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){an=(an<<3)+(an<<1)+ch-'0';ch=getchar();}
    return an*f;
}
int n,m,map[maxn][maxn];
int Kasumi[maxn][maxn];
int remember[maxn][maxn];//输出答案
bool change[maxn][maxn];//当前改变的位置
int tep=2333333;//当前答案的操作次数
inline void kk(){
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)Kasumi[i][j]=map[i][j];
    memset(change,0,sizeof change);
}
inline void dfs(int prepare){
    kk();int tot=0;
    for(int i=1;i<=m;i++){
        if(!prepare)continue;
        if(prepare&(1<<i-1)){//从小到大,字典序最优
        int now=m-i+1;tot++;
        Kasumi[1][now-1]^=1;
        Kasumi[1][now+1]^=1;
        Kasumi[1][now]^=1;
        Kasumi[2][now]^=1;
        change[1][now]=1;
        }
    }
    for(int i=2;i<=n;i++)
    for(int j=1;j<=m;j++){
        if(Kasumi[i-1][j]){
        tot++;
        Kasumi[i][j-1]^=1;
        Kasumi[i][j+1]^=1;
        Kasumi[i][j]^=1;
        Kasumi[i+1][j]^=1;
        change[i][j]=1;
        }
    }
    if(tot<tep){
        for(int i=1;i<=m;i++)if(Kasumi[n][i])return ;//判断最后一行
        tep=tot;
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        remember[i][j]=change[i][j];
    }
}
int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)map[i][j]=read();
    for(int i=0;i<=(1<<m)-1;i++){//枚举
        dfs(i);
    }
    if(tep==2333333)cout<<"IMPOSSIBLE";
    else{
        for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)cout<<remember[i][j]<<" ";
        cout<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Eraine (赞：3)

# 1 题目简介
## 1.1 题目大纲
在一个 $N×M$ 的棋盘里，每个格子的颜色要不是黑，要不是白。
这时，约翰FJ 叫奶牛们在这种棋盘上进行一种操作：选定任意一个，该格和这个格子相邻的四个格子都会变色。请找出一种办法，使用尽量少的操作，使得棋上的所有格子都为白色。
## 1.2 题目难度
内容|实际难度
:-: | :-:
思路难度|戊
代码难度|丙
细节难度|乙
# 2 思路分析
这一题，看起来蛮难的，其实不难。大家的思路也许是——纯粹暴力枚举。当然，这道题的正解就是暴力枚举啦……可，关键是怎样暴力枚举。提供有两种办法，供大家参考。

**思路一**

最简单又最简朴的思路：就是每一种全部判定一遍啦……首先，得明白为什么每一个方格要不翻转一遍，要不不翻转。因为：若当任意一个已经翻过一遍了，再翻第二遍，显然，第一遍翻过的格子第二遍又被翻过一次，恢复原样，没有意义。所以最多翻一遍。每种格子要不翻一遍，要不不翻。所以我们递归的搜索每一个格子，执行两种情况：翻和不翻。

**DFS 搜索**

接下来就要搜索啦！
搜索的总思路如下：一般情况下，执行两种情况（如上述）；碰到该行边界时，跳到下一行去，继续搜索。那有的同学会问了：既然要最小值，那怎么统计呢？没关系，直到所有的递归搜索执行完毕，也就是递归到第 $m+1$ 行时，我们就可以执行统计。而这个统计也是稍较麻烦的。首先，我们把所有的状态全部统计出来了，其中必定有不是符合标准的状态，这种错误状态，也就是格子里有黑色棋子的 ($1$) 。我们就要在统计之前，把这种情况的状态结束运行。至于怎么写代码，就简单了。从第 $1$ 行第 $1$ 列到第 $m$ 行第 $n$ 列，持续搜索有没有出现 $1$ 的，若有，函数 $return;$ ，否则，继续运行。

```cpp
void search_dfs(int x,int y){//参数用来表示第x行第y列
	if(y==m+1){//当前节点越界（行）
		search_dfs(x+1,1);//跳至下一行
		return;//别忘记了，不然数组越界就麻烦了
	}
	if(x==n+1){//当前节点越界（列）
		int sum=0;//用来记录当前状态翻转总数
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
			if(a[i][j])return;//a数组储存当前状态
			if(b[i][j])sum++;//b数组记录每个节点翻转数
		}
		h=1;//h保存是否存在可行情况
		if(sum<minx){//当当前值小于最小值
			minx=sum;//保存
			for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
				c[i][j]=b[i][j];//保存最优状态
			}
		}
		return;
	}
	search_dfs(x,y+1);//字典序，先0后1
	for(int i=0;i<=4;i++){//翻转后，a的状态要改变
		a[x+d[i]][y+e[i]]=1-a[x+d[i]][y+e[i]];//当前、前后左右
	}
	b[x][y]=1;//当前节点已翻转过
	search_dfs(x,y+1);
	//下面均为回溯流程
	for(int i=0;i<=4;i++){
		a[x+d[i]][y+e[i]]=1-a[x+d[i]][y+e[i]];
	}
	b[x][y]=0;
}
```
$but$，实测 $47$ ，TLE $6$ 个数据点。还是要优化滴~

**思路二**

上一个思路TLE了……
那怎么优化呢？这个可是个难点。但是，可以想到如果第一行的状态确定下来了，第二行也就确定了。为什么呢？其实这很好想的。因为以第 $1$ 行第 $1$ 列为例，若当前状态为 $1$ ，第 $2$ 行第 $1$ 列必须是 $1$ ，这样才能满足  $1-1=0$ 。简单吧！

**DFS 搜索**

DFS 搜索和前面没什么区别啦……就是确定第一行就行了，所以只带一个参数

```cpp
void search_dfs(int x){
	if(x==m+1){//数组越界
		dp_xxpanduan(2,1);//跳到判断即可
		return;
	}
	search_dfs(x+1);
	for(int i=0;i<=4;i++){
		a[1+d[i]][x+e[i]]=1-a[1+d[i]][x+e[i]];
	}
	b[1][x]=1;
	search_dfs(x+1);
	for(int i=0;i<=4;i++){
		a[1+d[i]][x+e[i]]=1-a[1+d[i]][x+e[i]];
	}
	b[1][x]=0;
}
```

**判断**

难在判断啊！其实也不难。根据前面的推导，我们可以推出如下递推式： $dp_{i,j}=1-dp_{i-1,j}$。然后，推出第 $2$ 行至第 $n$ 行。但是推完后，我们还不能确定当前状态是否是一个正确的状态，所以还要加以判断啦！其实思路二大部分代码和思路一差不多。

```cpp
void dp_xxpanduan(int x,int y){
	if(y==m+1){
		dp_xxpanduan(x+1,1);
		return;
	}
	if(x==n+1){
		int sum=0;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
			if(a[i][j])return;
			if(b[i][j])sum++;
		}
		h=1;
		if(sum<minx){
			minx=sum;
			for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
				c[i][j]=b[i][j];
			}
		}
		return;
	}
	if(!a[x-1][y]){//先0后1
		dp_xxpanduan(x,y+1);
	}else{
		for(int i=0;i<=4;i++){
			a[x+d[i]][y+e[i]]=1-a[x+d[i]][y+e[i]];
		}
		b[x][y]=1;
		dp_xxpanduan(x,y+1);
		for(int i=0;i<=4;i++){
			a[x+d[i]][y+e[i]]=1-a[x+d[i]][y+e[i]];
		}
		b[x][y]=0;
	}
}
```

# 3 AC代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,a[20][20],b[20][20],c[20][20],d[5]={0,0,1,0,-1},e[5]={0,1,0,-1,0},minx,h;
void dp_xxpanduan(int x,int y){
	if(y==m+1){
		dp_xxpanduan(x+1,1);
		return;
	}
	if(x==n+1){
		int sum=0;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
			if(a[i][j])return;
			if(b[i][j])sum++;
		}
		h=1;
		if(sum<minx){
			minx=sum;
			for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
				c[i][j]=b[i][j];
			}
		}
		return;
	}
	if(!a[x-1][y]){
		dp_xxpanduan(x,y+1);
	}else{
		for(int i=0;i<=4;i++){
			a[x+d[i]][y+e[i]]=1-a[x+d[i]][y+e[i]];
		}
		b[x][y]=1;
		dp_xxpanduan(x,y+1);
		for(int i=0;i<=4;i++){
			a[x+d[i]][y+e[i]]=1-a[x+d[i]][y+e[i]];
		}
		b[x][y]=0;
	}
}
void search_dfs(int x){
	if(x==m+1){
		dp_xxpanduan(2,1);
		return;
	}
	search_dfs(x+1);
	for(int i=0;i<=4;i++){
		a[1+d[i]][x+e[i]]=1-a[1+d[i]][x+e[i]];
	}
	b[1][x]=1;
	search_dfs(x+1);
	for(int i=0;i<=4;i++){
		a[1+d[i]][x+e[i]]=1-a[1+d[i]][x+e[i]];
	}
	b[1][x]=0;
}
int main(){
	h=0;
	minx=400;
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		scanf("%d",&a[i][j]);
	}
	search_dfs(1);
	if(h){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				printf("%d ",c[i][j]);
			}
			printf("\n");
		}
	}else{
		if(minx==400)printf("IMPOSSIBLE");
		else{for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				printf("%d ",0);
			}
			printf("\n");
		}
		}
	}
	return 0;
}
```
//选自本人CSDN博客

---

## 作者：巨型方块 (赞：2)

显然我们可以用位运算来优化这道题目；

虽然好像没有某些双下划线跑的快哇；

题目怎么做呢就是我们把第一行要改的枚举一边，然后可以通过第一行的状态直接确定第二行的状态了；

那么时间复杂度就是

2^16\*16\*16

那么我们用位运算去压掉一位的时候

常数理论上就会减小16；

代码貌似也会短一点；

咋么二进制不说了，想不通可以看看我的B函数

```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const int N=20;
int a[N],b[N],c[N],d[N],p[1<<15];
int n,m,ans=1e9,x;
void B(int i,int v){//把b[i]这个值用v的操作反转，v二进制中的一位如果是1就带表这一位反转 
    int x=b[i]&v;
    int y=v-x;
    b[i]&=~x;
    b[i]|=y;
}
void dfs(int k,int v,int sum){//当前在做b[k]，v是这一行该怎么反转，sum就是翻了几个 
    sum+=p[v];
    if(sum>=ans)return;
    if(k>n){
        if(v!=0)return;
        ans=sum;
        for(int i=1;i<=n;i++)d[i]=c[i];
        return;
    }
    c[k]=v;
    B(k,v);B(k+1,v);B(k,(v<<1)&((1<<m)-1));B(k,(v>>1));
    dfs(k+1,(~b[k])&((1<<m)-1),sum);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<(1<<m);i++)
        for(int k=i;k;k-=k&-k)p[i]++;//这个叫lowbit 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            scanf("%d",&x);
            a[i]=a[i]*2+x^1;//由于我的算法原因，输入要反一下 
        }
    for(int i=0;i<(1<<m);i++){
        for(int j=1;j<=n;j++)b[j]=a[j];
        dfs(1,i,0);
    }
    if(ans==1e9)puts("IMPOSSIBLE");else 
    for(int i=1;i<=n;i++){
        for(int j=m;j;j--)
            if(d[i]>=(1<<(j-1)))d[i]-=(1<<(j-1)),printf("1 ");else printf("0 ");
        puts("");
    }
}
```

---

## 作者：独孤灬昊昊 (赞：1)

由于第一行的修改方案确定之后，每一行的修改方案就确定了，所以说我们只需要用dfs枚举第一行的修改方案。

而接下来的行数修改的最佳方案是将为1的数的正下方的数进行修改，这样的好处是每行处理完只需要考虑下一行，不需要考虑以上的行数。

              
            
                
                
```cpp
#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
using namespace std;  
int n,m,f[1001][1001],ans[1001][1001],cz[1001][1001],a[1001][1001],minn=1000000009;  
void dfs(int);
int main()  
{  
    scanf("%d%d",&n,&m);  
    for(int i=1;i<=n;i++)  
            for(int j=1;j<=m;j++)  
               cin>>a[i][j];
   dfs(1);  
        if(minn==1000000009) cout<<"IMPOSSIBLE";  //最小值没有改变，即不可能
    else  
    {  
        for(int i=1;i<=n;i++)  
        {  
            for(int j=1;j<=m;j++)  
            cout<<ans[i][j]<<" ";  
               cout<<endl;
        }  
    }  
}
void dfs(int lie)  
{  
    if(lie>m)  
    {  
        for(int i=1;i<=n;i++)  
            for(int j=1;j<=m;j++)  
            cz[i][j]=a[i][j];//定义一个操作数组来保存a数组；
        for(int i=1;i<=m;i++)  
            if(f[1][i])  //已知第一行的修改方案，进行题目要求修改。
                {  
                cz[1][i]^=1,cz[2][i]^=1;  
                    cz[1][i+1]^=1,cz[1][i-1]^=1;  
                }  
        for(int i=2;i<=n;i++)  
                for(int j=1;j<=m;j++)  
                {  
                if(cz[i-1][j]==1)  
                {  
                f[i][j]=1;  
                cz[i][j]^=1;  
                cz[i][j+1]^=1,cz[i][j-1]^=1;  
                cz[i+1][j]^=1,cz[i-1][j]^=1;  //若第i行为1，则修改i+1行，并按照题目要求修改旁边各点。
                  }  
            else f[i][j]=0;  
                if(cz[i-1][j]) return;  
        }  
        bool pd=false;  
        for(int i=1;i<=n;i++)  
               for(int j=1;j<=m;j++)  
            if(cz[i][j])  //修改完后，依然存在1，肯定impossible；
            {  
                pd=true;  
                    break;  
                }  
        if(!pd)  
        {  
            int sum=0;  
            for(int i=1;i<=n;i++)  
                   for(int j=1;j<=m;j++)  
                if(f[i][j]) sum++;  
                if(sum>=minn) return;  
                minn=sum;  
            for(int i=1;i<=n;i++)  
                for(int j=1;j<=m;j++)  
                ans[i][j]=f[i][j];  
        }  
        return;  
    }  
    for(int i=0;i<=1;i++)  
        {  
                f[1][lie]=i;  
               dfs(lie+1);  //dfs第一行的修改方案
        }  
}
```

---

## 作者：marTixx (赞：1)

[博客食用](https://www.ftoaj.xyz/index.php/archives/17/)

今天学搜索，正好水一发以前做的这道毒瘤题

话说这道题做了我一天，别人都是各种优化，不超100行

天真的我硬核刚了220行，全程0优化水过

~~但其实不用这么长，我有的函数写的有点重复了（~~

#### 思路：

显然是dfs，一行一行的来

搜到[i, j]时(i > 1)，看[i - 1, j]是否为黑，是的话就翻转[i, j],

也就是说搜完当前行就要保证上一行的棋全都翻成了白色

当搜到最后一行时，

既要保证上一行翻成白色，还要保证自己也都翻成白色，

最后还要特判一下最后两个的翻转.


当时年少轻狂，我想着层次一定要清晰，
于是就SB地分别打了四个函数：

1. 特判第一行,firstLineS
2. 当只有一列的时候,dfs1
3. 当搜到最后一行时或本来只有一行时，dfsn
4. 正常搜索,dfs


##### 这个题有个坑，92分卡了一下午:  搜到的第一个解不能直接输出，它是最优解，但不一定是字典序最小的，所以继续搜完

丢脸的代码:
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, a, minans = 99999;
int Chess[25][25], ans[25][25], minan[25][25];

void c(int i, int j) 
{
	if(Chess[i][j]%2 == 0) Chess[i][j] = 1;
	else Chess[i][j] = 0;
}
void print() 
{
	a = 0;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (Chess[i][j] % 2 == 1) return ;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			a += ans[i][j] % 2;
	if(minans > a) 
    {
	    minans = a;
	    for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				minan[i][j] = ans[i][j] % 2;
	}
}
int back1(int p) 
{
	if ( Chess[m][p] == 1 && p == n)
		return 1;
	else if (p != n)
		return 1;
	return 0;
}
int back2(int p) 
{
	if ( Chess[m][p] == 0 && p == n)
		return 0;
	else if (p != n)
		return 0;
	return 1;
}
void dfsn(int num) {	
    if (num == n + 1) {
		print();
		return ;
    }
    int line = m;
    if (m == 1)
    {
    	if (num == 1)
    	{
			dfsn(num + 1);    
		    c(line, num + 1);
		    c(line, num);
		    ans[line][num]++;
			dfsn(num + 1);
		}
		if (Chess[line][num - 1]==0 && back2(num)==0)
			dfsn(num+1);
		else if (Chess[line][num - 1]==1 && back1(num)==1)
    	{
			c(line, num - 1);
			c(line, num + 1);
			c(line, num);
			ans[line][num]++;
		
			dfsn(num + 1);
		}
	}
	else if (num == 1)
	{
		if (Chess[m - 1][1] == 0)
	    	dfsn(2);	
    
		else 
		{
	    	c(m - 1 , 1);
			c(m, 2);
			c(m, 1);
			ans[m][1]++;
		
			dfsn(2);
		}
	}
	
    else if (Chess[line - 1][num]==1 && Chess[line][num - 1]==1 && back1(num)==1)
	{
	    c(line - 1 , num);
		c(line, num - 1);
		c(line, num + 1);
		c(line, num);
		ans[line][num]++;
		
		dfsn(num + 1);
		/*	
		ans[line][num]--;
		c(line - 1, num);
		c(line, num - 1);
		c(line, num + 1);
		c(line, num);
		*/
	}
    else if (Chess[line - 1][num] == 0 && Chess[line - 1][num] == 0 && back2(num) == 0)
	    dfsn(num + 1);
}
void dfs(int line, int num)
{
	if (num == n + 1 && line == m - 1)
	{
		dfsn(1);
		return ;
	}
	if (num == n + 1)
	{
		dfs(line + 1, 1);
		return ;
	}
	if (Chess[line - 1][num] == 0)
		dfs(line, num + 1);
	else
	{
	    c(line - 1, num);
		c(line + 1, num);
		c(line, num - 1);
		c(line, num + 1);
		c(line, num);
		ans[line][num]++;
		dfs(line, num + 1);
 /*
		ans[line][num]--;		
		c(line - 1, num);
		c(line + 1, num);
		c(line, num - 1);
		c(line, num + 1);
		c(line, num);
*/
	}
}
void firstLineS(int k)
{
	if (k == n + 1) 
	{
		if (m > 2)
	    	dfs(2, 1);
		else if (m == 2)
			dfsn(1);
	    return ;
    } 
	firstLineS(k + 1);
	c(1, k);
	c(1, k - 1);
	c(1, k + 1);
	c(2, k);
    ans[1][k]++;
	firstLineS(k + 1);
	ans[1][k]--;
    c(1, k);
    c(1, k - 1);
	c(1, k + 1);
	c(2, k);
}
void dfs1(int num)
{
    if (num == m + 1) 
    {
    	print();
    	return ;
	}
	if (num == 1)
	{
		dfs1(num + 1);
		ans[num][1]++;
		c(num, 1);
		c(num + 1, 1);
		dfs1(num + 1);
		ans[num][1]--;
		c(num, 1);
		c(num + 1, 1);
	}
	if(Chess[num - 1][1] == 0)
	    dfs1(num + 1);
	else  {
		ans[num][1]++;
		c(num, 1);
		c(num + 1, 1);
		c(num - 1, 1);
		
		dfs1(num + 1); 
		
		ans[num][1]--;
		c(num + 1, 1);
		c(num - 1, 1);
		c(num, 1);
	}
}

int main()   
{
	cin >> m>> n;
    for (int i = 1; i <= m; i++)
    	for (int j = 1; j <= n; j++)
    	    cin >> Chess[i][j];
    if (m == 1) dfsn(1);
    if (n == 1) dfs1(1);
    firstLineS(1);
    if (minans==99999)
    	cout<<"IMPOSSIBLE"<<endl;
    else
        for (int i = 1; i <= m; i++)
		{	
			for (int j = 1; j <= n; j++)
				cout << minan[i][j]%2<<" ";
			cout << endl;
		}
	return 0;
}
```

---

## 作者：nihanchu (赞：0)

记得这道题在我初二的时候，老师给过一道差不多的题，唯一区别在于，那道题是打枪影响五个，这道题是翻瓦片。


唔，首先这道题是一个搜索，我们发现我们先确定了第一行哪些要翻，哪些不要翻，之后，第一行的状态就确定了，如果我们还想把第一行上的黑瓦片翻成白瓦片的话，就需要在下一行当前黑瓦片的正下方打一枪，而且必须在那里打，所以我们只要枚举第一行哪些要翻哪些不要翻，接下来的翻的次数就可以确定了。如果，翻完后，最后一行全为白瓦片就可以拿去更新答案了。至于字典序的问题，我是从0枚举到1的，所以越早得到的答案，字典序越优。


具体的话看一下程序吧。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#define INF 2100000000
using namespace std;
int n,m,ans1,tot[20][20],h[5]={0,-1,1,0,0},l[5]={0,0,0,-1,1},a[20][20];
int ans2[20][20],s[20],b[20][20];
bool check(int x,int y)
{
  if ((x<=0)||(x>m)||(y>n)||(y<=0)) return false;
  return true;
}
void dfs(int x)
{
  if (x==n+1)
//如果第一行的翻与不翻的状态已经确定下来了，就进行所需次数的统计
  {
      for (int i=1;i<=m;i++)
       for (int j=1;j<=n;j++)
       a[i][j]=b[i][j];
      int sum=0; 
      for (int i=1;i<=n;i++)
      if (s[i]==1) 
      {
        tot[1][i]=1;
        for (int j=0;j<=4;j++)
        if (check(1+h[j],i+l[j])) a[1+h[j]][i+l[j]]=a[1+h[j]][i+l[j]]^1;
//改变为相反的状态
        sum++;
    }
    else tot[1][i]=0;
    for (int i=2;i<=m;i++)
    for (int j=1;j<=n;j++)
    if (a[i-1][j]==1)
//由上一行来决定这一行是否要翻
    {
      tot[i][j]=1;
      for (int k=0;k<=4;k++)
      if (check(i+h[k],j+l[k])) a[i+h[k]][j+l[k]]=a[i+h[k]][j+l[k]]^1;
        sum++; 
    }
    else tot[i][j]=0;
    for (int i=1;i<=n;i++)if (a[m][i]==1) return ;
//如果最后一行还有黑瓦片，那么这种方案是不合法的，直接退出
//更新答案
    if (sum<ans1) 
    {
      ans1=sum;
      for (int i=1;i<=m;i++)
       for (int j=1;j<=n;j++)
       ans2[i][j]=tot[i][j];
    }
    return;
  }
  else for (int i=0;i<2;i++) 
  {
    s[x]=i;
//枚举状态
    dfs(x+1);
  }
}
int main()
{
  scanf("%d%d",&m,&n); getchar();
  ans1=INF;
  for (int i=1;i<=m;i++)
   for (int j=1;j<=n;j++)
    scanf("%d",&b[i][j]);
  dfs(1);
  if (ans1!=INF)
  {
  for (int i=1;i<=m;i++)
   for (int j=1;j<=n;j++)
   {
        printf("%d",ans2[i][j]);
        if (j==n) putchar('\n');
        else putchar(' ');
   }
  }
  else printf("IMPOSSIBLE\n");
  return 0;
}

```

---

## 作者：LLLM (赞：0)

其实能过的人都知道一旦第一行状态确定了，就能计算出最后能不能成功。这里关键是枚举第一行的状态，然后你要想清楚要开多少个图来保存做过的事。然后极简的DFS从第一行的操作（注意是操作！）0 0 0 0 . . .开始搜。最少步数也是蛮令人头疼的，所以又开了很多数组。当你知道什么东西存在哪里时，程序就清晰很多。。

还有把图从1 1开始存就不用判边界了233










        



```cpp
#include<stdio.h>
#include<stdlib.h>
int premap[20][20]; //原图
int nextmap[20][20];  //计算出的某次第一行操作后的图
int moves[20]; //枚举的第一行的操作
int ans[20][20]; //记录每次计算的答案
int finalans[20][20]; //记录最少步数的答案
int vol=0x7f, voltmp=0; //记录每次计算的步数
int m, n;
void printnextmap(){
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)
        {
            printf("%d ",nextmap[i][j]);
        }
        printf("\n");
    }
}
void flip(int n, int m){   //翻转不用判边界是因为图从1 1开始
    nextmap[n-1][m]=1-nextmap[n-1][m];
    nextmap[n][m-1]=1-nextmap[n][m-1];
    nextmap[n][m]=1-nextmap[n][m];
    nextmap[n][m+1]=1-nextmap[n][m+1];
    nextmap[n+1][m]=1-nextmap[n+1][m];
}
void copy(){
    for(int i=1;i<=n;i++)
        finalans[1][i]=moves[i];    //将第一行的操作也打上去
    for(int i=2;i<=m;i++)
        for(int j=1;j<=n;j++)
            finalans[i][j]=ans[i][j];
    vol=voltmp;
}
void expand(){   //导出状态
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            nextmap[i][j]=premap[i][j];
    for(int e=1;e<=m;e++){
        if(moves[e])
        {
            nextmap[1][e-1]=1-nextmap[1][e-1];
            nextmap[1][e+1]=1-nextmap[1][e+1];
            nextmap[1][e]=1-nextmap[1][e];
            nextmap[2][e]=1-nextmap[2][e];
        }
    }
}
void calculate(){  //计算步数
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            ans[i][j]=0;
    for(int i=2;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            if(nextmap[i-1][j])
            {        
                flip(i,j);
                ans[i][j]=1;
                voltmp++;
            }
        }
    for(int i=1;i<=n;i++)
        if(nextmap[m][i])
        {
            return ;
        }
    if(voltmp<vol)
        copy();
    return ;
}
void dfs(int step){
    if(step>=n)    {
        expand();
        //for(int q=1;q<=n;q++)    {printf("%d ",moves[q]);}
        //printf("\n");
        //printnextmap();
        int err=0;
        for(int i=1;i<=n;i++)
            if(moves[i])
                err++;
        voltmp=err;  //第一行的操作步数也要加上去
        calculate();
        return ;
    }
    step++;
    moves[step]=0;   //以下4行是朴素DFS
    dfs(step);
    moves[step]=1;
    dfs(step);
}
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&premap[i][j]);
        }
    dfs(0);
    if(vol<0x7f)    {
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
            {
                printf("%d ",finalans[i][j]);
            }
            printf("\n");
        }
    }
    else{
        printf("IMPOSSIBLE");
    }
    return 0;
}

```

---

