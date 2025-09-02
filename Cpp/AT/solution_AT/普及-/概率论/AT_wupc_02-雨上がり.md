# 雨上がり

## 题目描述

[problemUrl]: https://atcoder.jp/contests/wupc2nd/tasks/wupc_02

 雨が上がった．そろそろ大学に行こう． 僕の家から大学までは一本道の道路で結ばれている．道路は区間に分けることができ，ここでは，道路を一行の文字列で表すことにする．各文字が1つの区間に相当し，1文字目が家の前の区間，最後の文字が大学の前の区間を表している．  
  
 ここで，各文字の意味は次のとおりである．

```

 . : 普通の区間
 X : 水たまりのある区間
```

 僕は家の前の区間からスタートし大学へ向かう．僕は現在位置から$ 1 $つ，$ 2 $つ，もしくは$ 3 $つ先の区間(大学のある方向)へ進むことができる．もし，移動した先の区間に水たまりがある場合，僕は水たまりを踏むはめになる．買ったばかりの靴を汚したくないので，なるだけ水たまりを避けたい．また，大学の前の道路を超えて移動するようなことはできない．  
  
 家の前の道路から大学の前の道路まで適切な進み方で向かうとき，最低限踏まなければならない水たまりの数を求めてほしい．  
 入力は以下の形式で標準入力から与えられる． > $ N $ $ S $

- $ 1 $ 行目に区間の数を表す $ N $($ 3\ ≦\ N\ ≦\ 100 $) が与えられる．
- $ 2 $ 行目には，$ N $ 文字の文字列 $ S $ が与えられる．これらは道路の区間のデータである．
- $ S $ に出現する文字は '.', 'X' のいずれかであり，意味は上に記した通りである．
- $ S $ の最初と最後の文字は必ず '.' である．
 
 最低限踏まなければならない水たまりの数を標準出力に $ 1 $ 行で出力せよ．  
 なお、最後には改行を出力せよ． ```
<pre class="prettyprint linenums">
5
.XXX.
```

 ```
<pre class="prettyprint linenums">
1
```

 ```
<pre class="prettyprint linenums">
10
.X.XXXXXX.
```

 ```
<pre class="prettyprint linenums">
2
```

 ```
<pre class="prettyprint linenums">
7
.......
```

 ```
<pre class="prettyprint linenums">
0
```

# 题解

## 作者：珅肐 (赞：9)

感觉楼下的代码稍有些繁琐

根本不用动规，就是道简单的模拟

### 说一下思路：
因为步长为1、2、3, 所以如果水坑的连续个数不超过2, 就不用经过, 水坑的连续个数如果为3, 只需经过一个, 很容易发现经过连续水坑的个数为ans/3, 之后累加最终结果即可
#### 代码：
```cpp
#include<iostream>
using namespace std;
char s;//不用开数组, 在线做
int n,ans,sum;//ans用来统计连续的‘X’的个数, sum是最后结果
int main()
{
	cin>>n;
	for(int i=0;i<=n;i++){
		cin>>s;//输入
		if(s=='X')ans++;//统计连续的‘X’的个数
		else sum+=ans/3,ans=0;//如果不是‘X’, 累加和，ans清零
	}
	cout<<sum<<endl;//输出, 记得换行
	return 0;//好习惯
}
```

---

## 作者：ShineEternal (赞：7)

~~动规里最简单的就是有图的题了~~。

提醒一件事：这个网站输出最后必须要打回车！**打回车！**

**写在前面：代码内含bug，不过不影响看，~~只影响复制~~**


------------
```
#include<cstdio>
#include<cmath>//fmin要用
using namespace std;//想要做一个OIer,就要养成写名字空间的好习惯
int f[10001];//开大一点，以防不测
char s[10001]；//同上
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",s)；//scanf版输入字符串
	for(int i=0;i<n;i++)
	{
		if(s[i]=='X')
		f[i]=1;//初始化，也懒得只赋前三个了。
	}
	for(int i=3;i<n;i++)//从第三个开始循环，要不然越界
	{
		
		if(s[i]=='X')
		f[i]=fmin(fmin(f[i-1],f[i-2]),f[i-3])+1;//如果自身是水坑，从哪过来都得湿
		if(s[i]=='.')
		{
			f[i]=fmin(fmin(f[i-1],f[i-2]),f[i-3]);//自身不是水坑？听天由命吧(说不定从水坑过来，说不定不是呢)。
		}
	}
	printf("%d\n"，f[n-1]);//不要打成了f【n】，因为是从0开始。
   	return 0;

```

求过

---

## 作者：_Qer (赞：3)

题意：给定一条长为N的路，每一单位的路段可能为 _X_ （水坑）或  _._  （空地），要求经过最少的水坑到达N这里，每一步可以走1、2、3单位长的距离。

可以使用动态规划（雾）来做，用一个一维数组，第i个元素存走到i时最少经过的水坑数，而第i个数的值应为i-1，i-2，i-3中最小的数加上当前是否是水坑，是就加1，否则不加。最后需要输出数组第N个数，即为答案。

公式：**f[i]=(road[i]=='X')+min(f[i-3],min(f[i-2],f[i-1]))**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;//路的长度
string road;//存输入数据
int f[110];//动态规划的数组
int main(){
    cin>>n;
    cin>>road;
    f[0]=(road[0]=='X');
    f[1]=(road[1]=='X');
    f[2]=(road[2]=='X');
    //前三个特判一下，免得-3，-2，-1出问题
    //也可以让数组从3开始，前三个元素置为0，下面循环到N+3
    for(int i=3;i<n;++i){
        f[i]=(road[i]=='X')+min(f[i-3],min(f[i-2],f[i-1]));
    }//动态规划过程
    cout<<f[n-1]<<endl;//我的数组从0开始，所以输出是第N-1个
    return 0;
}
```

---

## 作者：lzxhdxx (赞：2)

# 题解AT360

~~竟然没有BFS题解~~

### 题意
给定一维地图和坐标偏移量，求从地图最左边走到最右边最少需要经过几个'X'。

### 方法
给定了地图和坐标偏移量，明显的搜索风格，我们就可以确定算法是搜索。

确定了算法以后，我们还要继续深究选用bfs还是dfs比较好，看到数据规模很小，只有$N\le100$，所以我们两种搜索都可以选择，作者在这里选择bfs

选用bfs算法以后，我们制定搜索策略，由题意易得每个点可能**经过多次**，且**不走回头路**，所以我们制定的策略如下：

从起点开始重复向右边扩展新状态，用vis[]数组来记录到达当前点经过最少'X'的个数，如果当前走到新状态所需要经过'X'的步数小于新状态记录的最少数量就扩展，搜索完后就输入vis[n]

### Code：
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

int len, dx[5] = { 0,1,2,3 }/*坐标偏移量*/, vis[110] = { 0 }/*记录数组*/;
char road[110]/*一维地图*/;

void BFS()
{
	queue<int>Q;//状态队列
	Q.push(1);//压入起点
	vis[1] = (road[1] == 'X');//如果起点是'X'就标记为1，否则就是0
	while (!Q.empty())
	{
		int nowx = Q.front();//取出队头
		for (int i = 1; i <= 3; i++)//扩展
		{
			int newx = nowx + dx[i];//新状态
			if (newx >= 1 && newx <= len/*不越界*/ && vis[newx] > vis[nowx] + (road[newx] == 'X')/*从当前点走到新状态经过的'X'数小于新状态记录的最小数量*/)
			{
				Q.push(newx);//压入新状态
				vis[newx] = vis[nowx] + (road[newx] == 'X');//刷新最小步数
			}
		}
		Q.pop();//弹出队头
	}
}

int main()
{
	memset(vis, 127 / 3, sizeof(vis));//先初始化为一个很大的数
	scanf("%d%s", &len, road + 1);//输入
	BFS();//搜索
	printf("%d\n", vis[len]);//输出终点处记录的最小步数
	return 0;
}
```
感谢各位观看

~~既然没有BFS题解那么管理大大们就给我过了吧~~

---

## 作者：蒟蒻取不来名 (赞：2)

$$QwQ$$
~~最近好迷“QwQ”~~

这题好水啊，连长度都不用判断

~~感觉根本不用发题解~~
```
#include<iostream>
#include<string>
using namespace std;
int n, i, qwq, ans;
string a;
int main()
{
	cin >> n >> a;
	for(i = 0; i < n; i ++)
	{
		if(a.substr(i, 1) == "X") qwq ++;
		else qwq = 0;
		if(qwq == 3){
			ans ++;
			qwq = 0;//因为一次最多只能走3步，所以当有3个泥潭连在一起的时候给qwq赋值为0，ans（答案）累加
		}
	}
	cout << ans;
}
```
PS：AT换行不换行会听取WA声一片的

---

## 作者：I_will (赞：1)

这题没人用~~动规~~吗？

**那我就大发慈悲的**用动规吧！

-----------------

* ①将X化为1，.化为0。b[i]
* ②动规：
```
1.跳一个判断：在i-1的1 2 3 个中找最小加b[i]。
2.跳两个判断：在i-2的1 2 3 个中找最小加b[i]。
3.跳三个判断：在i-3的1 2 3 个中找最小加b[i]。
```
* ③输出a[n]-1，a[n]-2，a[n]-3中最小的一个+endl/'\n'即可！

程序：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
char st;
int b[105];
int a[105][4];
int main()
{
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{
		cin>>st;
		if(st=='X')b[i]=1;
		else b[i]=0;
	}
	a[1][2]=b[1];
	a[1][3]=b[1];
	a[2][3]=b[2];
	for(int i=1;i<=n;i++)
	{
		a[i][1]=min(a[i-1][1],min(a[i-1][2],a[i-1][3]))+b[i];
		if(i>=2)a[i][2]=min(a[i-2][1],min(a[i-2][2],a[i-2][3]))+b[i];
		if(i>=3)a[i][3]=min(a[i-3][1],min(a[i-3][2],a[i-3][3]))+b[i];
		
		
	}
	cout<<min(a[n][1],min(a[n][2],a[n][3]))<<endl;
	return 0;
}
```


---

## 作者：田所浩二仙贝 (赞：1)

这道题采用动态规划，可以看出对于n>=3的任意一部，均有三种方法到达（即1，2，3步）所以首先对前三步赋值作为初始，是.为0是X为1，同理转移方程也一样，如果此时i是.不作处理，如果是X加一。
代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char s[110];
int dp[110];
int main()
{
    cin>>n;
    cin>>s;
    for(int i=0;i<=2;i++)
    {
        if(s[i]=='.')
        {
            dp[i]=0;
        }
        else
        {
            dp[i]=1;
        }
    }
    for(int i=3;i<=n-1;i++)
    {
        if(s[i]=='.')
        {
            dp[i]=min(min(dp[i-1],dp[i-2]),dp[i-3]);
        }
        else
        {
            dp[i]=min(min(dp[i-1],dp[i-2]),dp[i-3])+1;
        }
    }
   cout<<dp[n-1]<<endl;
    return 0;
}

```


---

## 作者：stry (赞：1)

~~这题真的不是红题吗~~

其实这题我们只需要统计一段连续的'X'有多少个，之后再加上每次除以3的个数就行了

之后再输出累加的个数就行了

程序：
```cpp
#include<iostream>
using namespace std;
char st;
long long n,he,zs;
int main()
{
    cin>>n;
    for(int i=0;i<=n;i++)
    {
        cin>>st;
        if(st=='X')
        {
            ans++;//统计连续的‘X’的个数
        }
        else
        {
            zs+=he/3;// 累加除以3的和
            ans=0;//如果不是‘X’，he清零
        }
    }
    cout<<zs<<endl;
    return 0;
}
```

求过！！！



---

## 作者：happybob (赞：0)

~~本题是AT360的题目！~~

大家都用的是 `DP`，然后我看见了标签有个 $ \color{red} \text{模拟}$，于是就用一个模拟过了这道题。

其实如果模拟对于贪心也要有基础，这道题怎么贪心呢？

1. 如果一段路都是空地，那一次走$1,2,3$格都一样，所以不用处理。

1. 如果现在是空地，而下面三个都是水洼，那无论是走$1,2,3$步，都要经过一个水洼，那这样，我们肯定选$3$个。

1. 如果现在是空地，而只有下面两个都是水洼，那无论是走$1,2$步，都要经过一个水洼，那这样，我们肯定选3个，不经过水洼。

1. 如果现在是空地，而只有下面一个是水洼，如果走$1$步，要经过一个水洼，那这样，我们肯定选$2$个，不经过水洼。那为什么不选三个？比如一组数据：

	```cpp
	5
	..X.X
	```
	正确答案应该是$1$（我想的），而在第二个空格我们就会做这个判断，如果我们往前走$3$格，就会碰到水洼，虽然这样与正确答案一样，但在某些情况下不是最优解

1. 如果现在是水洼，而下一个就是空地，直接走到空地上。

1. 如果现在是水洼，下两个是空地，走到空地。

1. 如果现在是水洼，下三个是空地，走到空地。

1. 如果现在是水洼，下面三个都不是空地，直接走三个。

还要注意，如果是水洼，统计一下。

代码如下：

```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	cin >> s >> s;
	int ans = 0, len = s.length() - 1;
	for (register int i = 0; i <= len; )
	{
		if (s[i] == 'X')
		{
			ans++;
			if (s[i + 1] == '.')
			{
				i++;
			}
			else if (s[i + 2] == '.') i += 2;
			else if (s[i + 3] == '.') i += 3;
			else i += 3;
		}
		else
		{
			if (s[i + 1] == 'X' && s[i + 2] == 'X' && s[i + 3] == 'X')
			{
				i += 3;
			}
			else if (s[i + 1] == 'X' && s[i + 2] == 'X')
			{
				i += 3;
			}
			else if (s[i + 1] == 'X')
			{
				i += 2;
			}
			else i++;
		}
	}
	cout << ans << endl;
	//system("pause");
	return 0;
}
```


---

## 作者：αnonymous (赞：0)

数据较水，一波暴力模拟AC

## 核心

●每次都由走三步开始往一步搜索，碰到没水坑的就走到那里并开始下一个循环；

●如果三步全是水坑，就直接走三步，这样可以减少走水坑次数
```cpp
#include <iostream>
using namespace std;
int n,ans;
bool b[10001];//储存哪里没有水坑
int main(){
	int i,j,k,flag;
	char c;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>c;
		if(c=='.')//没有水坑
			b[i]=1;
	}
	k=1;
	while(k<n){
		flag=0;
		for(i=k+3;i>k;i--)//最优方案：走得越多越好&&不走水坑
			if(b[i]==1){//没有水坑
				k=i;
				flag=1;
				break;
			}
		if(flag==0){//实在全是水坑，走三步
			k+=3;
			ans++;//计数
		}
	}
	cout<<ans<<endl;//换行毒瘤
	return 0;
}
```


---

## 作者：zzhhf (赞：0)

  之前题解有一个错误，修复一下
  这道题是一道很简单的动态规划题。很适合新手做。
  在这里介绍一下递归式：
    
    if(ch[i]=='X')dp[i]=min(min(dp[i-3],dp[i-2]),dp[i-1])+1;else
	      dp[i]=dp[i]=min(min(dp[i-3],dp[i-2]),dp[i-1]);
    //如果是水坑,那么肯定会踩到这个水坑，那么就去在到达水坑之前经过水坑最少的路线加1。
    //没水坑就直接取在到达水坑之前经过水坑最少的路线。
 源代码：
 
    #include<bits/stdc++.h>
    #include<math.h>
    using namespace std;
    int main()
    {
	    int n,i;
	    char ch[1000];
	    int dp[1000]={0};
	    cin>>n;
	    for(i=1;i<=n;i++) 
	      cin>>ch[i];
	    for(i=2;i<=n;i++)  //从2开始不然dp[i-3]会越界
	      if(ch[i]=='X')dp[i]=min(min(dp[i-3],dp[i-2]),dp[i-1])+1;else
	      dp[i]=dp[i]=min(min(dp[i-3],dp[i-2]),dp[i-1]);  //递推式
	    cout<<dp[n]<<endl;  
    } 

---

