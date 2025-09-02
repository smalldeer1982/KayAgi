# Japanese Game

## 题目描述

Joseph really likes the culture of Japan. Last year he learned Japanese traditional clothes and visual arts and now he is trying to find out the secret of the Japanese game called Nonogram.

In the one-dimensional version of the game, there is a row of $ n $ empty cells, some of which are to be filled with a pen. There is a description of a solution called a profile — a sequence of positive integers denoting the lengths of consecutive sets of filled cells. For example, the profile of $ [4, 3, 1] $ means that there are sets of four, three, and one filled cell, in that order, with at least one empty cell between successive sets.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/00e502cee5b1e7dd59d45d59dc6659a6a0146886.png)A suitable solution for $ n = 12 $ and $ p = [4, 3, 1] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/16bbe71feae06df40c8df421f6ec72b82b435ae1.png)A wrong solution: the first four filled cells should be consecutive.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/25f6dcf6154fe32ad9548fdf4a5f7e89e3b49fc5.png)A wrong solution: there should be at least one empty cell before the last filled cell.

Joseph found out that for some numbers $ n $ and profiles $ p $ there are lots of ways to fill the cells to satisfy the profile. Now he is in the process of solving a nonogram consisting of $ n $ cells and a profile $ p $ . He has already created a mask of $ p $ — he has filled all the cells that must be filled in every solution of the nonogram.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/c808943bd3773423d6c30a389b313c56fa04b926.png)The mask for $ n = 12 $ and $ p = [4, 3, 1] $ : all the filled cells above are filled in every solution.

After a break, he lost the source profile $ p $ . He only has $ n $ and the mask $ m $ . Help Joseph find any profile $ p' $ with the mask $ m $ or say that there is no such profile and Joseph has made a mistake.

## 说明/提示

**【题目描述】**

Joseph 特别喜欢日本文化。去年他学习了日本传统服装和日本艺术，但是现在他正在寻找日本拼图（一种日本传统游戏）的秘密。

在此游戏的一维版本上，连续 $n$ 个方格排成一排。Joseph 需要将一些格子涂黑。Joseph 还会得到一个数组 $p$。例如，若 $p = [4,3,1]$，则 Joseph 需要涂 $3$ 个区块，长度分别为 $4,3,1$，他们彼此不能相连，这是例子的一种正确涂色方法：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/00e502cee5b1e7dd59d45d59dc6659a6a0146886.png)

但下面两种是错误的：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/16bbe71feae06df40c8df421f6ec72b82b435ae1.png)

原因：前四个格子没有相连。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/25f6dcf6154fe32ad9548fdf4a5f7e89e3b49fc5.png)

原因：长度为 $3$ 的区块和长度为 $1$ 的区块连上了。

Joseph 发现，对于某些 $n$ 和 $p$，有不止一种方法完成日本拼图游戏，但是不论有多少种方法，有一些格子是必须涂色的，他现在正在将这些格子涂色。

例如，当 $n = 12$、$p = [4,3,1]$ 时，下图黑色的格子是必须涂色的：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/c808943bd3773423d6c30a389b313c56fa04b926.png)

Joseph 将这张图叫做 $m$。

但是在 Joseph 歇了一会后，他忘记了刚刚的 $p$ 数组，他现在只有 $n$ 和 $m$ 图。帮 Joseph 找到任意一种符合 $m$ 图涂色方块的 $p'$ 数组吧！如果没有符合的 $p'$ 数组，请输出 $-1$。

**【输入格式】**

输入共 $1$ 行：

第 $1$ 行，一个字符串 $m$，表示 $m$ 图，黑色的格子用 `#` 表示，其他格子用 `_` 表示。

**【输出格式】**

若没有符合要求的 $p'$ 数组，输出 $-1$。

否则输出共 $2$ 行：

第 $1$ 行，一个整数 $k$，表示找到的 $p'$ 数组的长度。

第 $2$ 行，输出 $k$ 个整数 $a_1, a_2, \cdots, a_k$，$a_i$ 表示数组 $p'$ 的第 $i$ 项。

**【样例】**

输入 #1：

```
__#_____
```

输出 #1：

```
2
3 2
```

输入 #2：

```
_#
```

输出 #2：

```
-1
```

输入 #3：

```
___
```

输出 #3：

```
0
```

**【数据范围】**

$|m| = n$。

$1 \le n \le 10^5$。

翻译贡献者 @[六八七十二](/user/341353)

## 样例 #1

### 输入

```
__#_____```

### 输出

```
2
3 2```

## 样例 #2

### 输入

```
_#```

### 输出

```
-1```

## 样例 #3

### 输入

```
___```

### 输出

```
0```

# 题解

## 作者：QAQQWQ (赞：14)

高妙贪心题。

先考虑给定 $p$ 时怎么求出 $m$。先全部都靠左放，然后全部靠右放。发现对于 $p_i$，在靠左放和靠右放都被染色的格子就是必须染色的格子。

假设全部都靠左放时，末尾剩有 $k$ 个空格子，那么必须染色的格子就是全都靠左放时对于 $p_i$ 去掉前 $k$ 个。（不足 $k$ 个则全去掉）

那么考虑给定 $m$ 时如何求 $p$，枚举 $k$，先在每个极长黑色连续段前加上 $k$ 个，如果不是第一段需要空一格，最后一段空白段减去 $k$ 个。考虑剩下的空白如何处理，发现我们需要在其中填入长度小于等于 $k$ 的连续段，而我们最多只需要长度为 $2$ 或 $3$ 的连续段就可以处理所有空白长度大于 $2$ 的段，那么 $k$ 只要枚举到 $4$，时间复杂度 $O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100009
inline int read(){
	int sum=0,fh=1;
	char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-')fh=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		sum*=10;
		sum+=c-'0';
		c=getchar();
	}
	return sum*fh;
}
int n,l[maxn],r[maxn],tot=0;
char s[maxn];
bool flag=false;
void check(int m){
	int top=0,p[maxn];
	for(int i=1;i<=tot;i++){
		int qwq=l[i]-r[i-1]-1-m-1;
		if(qwq<0)return ;
		if(qwq==1)return ;
		if(qwq>0){
			if(m){
			for(int j=1;j<=qwq/2;j++){
				p[++top]=1;
			}
			if(qwq%2){
				if(m>1)top--,p[++top]=2;
				else return ;
			}
			}
			else return ;
		}
		p[++top]=r[i]-l[i]+1+m;
	}
//	cout<<top<<endl;
//	for(int i=1;i<=top;i++){
//		cout<<p[i]<<" ";
//	}
//	cout<<endl;
	int qwq=n-r[tot]-m;
	if(qwq<0)return ;
	if(qwq==1)return ;
	if(qwq>0){
		if(m){
		for(int j=1;j<=qwq/2;j++){
			p[++top]=1;
		}
		if(qwq%2){
			if(m>1)top--,p[++top]=2;
			else return ;
		}
		}
		else return ;
	}
	flag=true;
	cout<<top<<endl;
	for(int i=1;i<=top;i++){
		cout<<p[i]<<" ";
	}
	cout<<endl;
	return ;
}
int main(){
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	cin>>s+1;n=strlen(s+1);
	int m=n;
	r[0]=-1;
	for(int i=1;i<=n;i++){
		if(s[i]=='#'){
			l[++tot]=i;r[tot]=i;
			while(s[r[tot]+1]=='#'){
				r[tot]++;
			}
			i=r[tot]+1;
			m=min(m,l[tot]-r[tot-1]);
//			cout<<l[tot]<<" "<<r[tot]<<endl; 
		}
	}
	if(tot==0){puts("0");return 0;} 
	m=min(m,n-r[tot]);
	m=min(m,4);	
	for(int i=0;i<=m;i++){
		check(i);
		if(flag){
			return 0;
		}
	} 
	puts("-1");
//	  fclose(stdin);
//    fclose(stdout);
	return 0;
}

```


---

## 作者：LinkyChristian (赞：6)

补充下上面题解的最后一个部分。

任何长度大于 $2$ 的空白段我们都可以用若干个 $p_i=1$ 和 $0/1$ 个 $p_i=2$ 填满。因此如果只考虑长度大于 $2$ 的空白段我们的 $k$ 枚举到 $2$ 就可以了。显然长度为 $1$ 的空白段我们不用考虑，而长度为 $2$ 的空白段存在即不合法，此时我们可以选择让 $k+1$ 来把长度为 $2$ 的空白段变成长度为 $1$ 的空白段，因此 $k$ 枚举到 $3$ 就可以了，而不是 $4$。 

```cpp
#include<bits/stdc++.h>
#define N 100010
using namespace std;
char s[N];
int n,tot,l[N],r[N],mn,a[N],an;
void work(int x) {
	for(int i=1; i<=tot; i++) l[i]-=x;
	l[tot+1]=n-x+2,an=0;
	for(int i=1; i<=tot+1; i++) {
		int len=l[i]-r[i-1]-2;
		if(len<0||len==1) return ;
		if(len) {
			if(len&1) {
				if(x<2) return ;
				a[++an]=2,len-=3;
			} 
			if(x<1) return ;
			while(len) a[++an]=1,len-=2;
		} if(i!=tot+1) a[++an]=r[i]-l[i]+1;
	}
	printf("%d\n",an);
	for(int i=1; i<=an; i++) printf("%d ",a[i]);
	exit(0);
}
int main() {
	scanf("%s",s+1),n=strlen(s+1),mn=n+1,r[0]=-1;
	for(int i=1; i<=n; i++) {
		if(s[i]=='#') {
			if(s[i-1]!='#') l[++tot]=i;
			r[tot]=i;
		}
	}
	if(!tot) {puts("0");return 0;}
	for(int i=0; i<4; i++) {
		work(i);
		for(int j=1; j<=tot; j++) l[j]+=i;
	}
	puts("-1");
}
```


---

## 作者：kczw (赞：1)

# 题意
有一串白色网格，有一序列 $p$，按顺序表示每组连续黑色块的长度，相邻的两组黑色连续块中间须有白色块阻隔。

现有字符串 $S$，若 $S_i$ 为 `#` 意味着一格所有黑色块合法的摆放方式下若都有黑色块，否则为 `_`。

现在给定 $S$，求 $p$。
# 思路
首先证明，若 $S_i$ 为 `#`，所有情况下覆盖第 $i$ 格的连续黑色块都是同一组。其实很好懂，若此格可被其他组连续块覆盖，但因组组之间有空白，那么必有空白出现在第 $i$ 格的情况，但又因 $S_i$ 为 `#`，于是此格便只可被同一组连续块覆盖了。

然后来想想，假设你已知 $p$ 如何求 $S$，那定然是所有组靠左摆放据连续块右边界取 `#` 右边界，再全靠右据连续块左边界取 `#` 的左边界，其中左、右边界相对位置不合法的（左边界于右边界右分）便是 `_`。

例如 $p={4,3,1},|S|=12$ 如下图分别为两种摆放情况及 $S$：
```
# # # # _ # # # _ # _ _
_ _ # # # # _ # # # _ #
_ _ # # _ _ _ # _ _ _ _
```
这里前两组连续块就按照上述方式取出来了各自 `#` 的左右边界，而第三组因为边界不合法无 `#` 表示。为方便，此处称同一组连续块两种极限情况相差距离为**偏移量**。

那么不难知道，若已知偏移量，便可根据 $S$，求出全部向左、右摆放的部分情况了。还是上文的例子求靠右摆放，不过假设我们只知道 $S$ 以及其偏移量为 $2$。
```
_ _ # # _ _ _ # _ _ _ _
_ _ # # # # _ # # # _ _
```
得到第二行后发现所有组全部靠右摆放后，竟有空白，但其实不难知道，这是因为组的长度小于等于偏移量导致的，我们只需要随便用一个可行方案填充即可。

至于具体的，分三种：

- 对于空白可填处长度为零的，则无解。
- 对于空白可填处长度为奇数，类 `_ _ _ _ _`，隔一填一即可，结果为 `# _ # _ #`。
- 对于空白可填处长度为偶数数，类 `_ _ _ _ _ _`，先填二，再隔一填一即可，结果为 `# # _ # _ #`。

说了这么多，离不开求出偏移量的基础。

最开始，我以为只需要求出 $S$ 中最短的可偏移空白长度（像是某两组 `#` 连续段之间空白长度减一或者边界空白长度）即可。

但是提交了却发现错了，思考后发现偏移量是需要枚举的，因为偏移量的不同会使得有些偏移量不会出现上文中的空白可填处长度为零情况，而有的则会出现。

于是，可先求出偏移量上界，然后从大往小枚举偏移量。

枚举时综合上述所言，对于将所有 `#` 对于该情况下补齐然后对空白填充，同时判断合法性，合法则输出退出程序，不合法的等到所有方案枚举过后输出即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e6+5;
char s[N];
int n,pre,num,mx=1e9;
inline void work(){
	num=0;
	vector<int> ans;//记 p 用
	for(int i=pre+1;i<=n;i++){
		if(s[i]=='#'){
			num++;//计连续块长度
			if(s[i+1]!='#'){//边界
				i+=pre;//复原右边界连续块
				if(i>n)return;//出界，不合法
				ans.emplace_back(num+pre);//连续块长度加上偏移量
				num=0;//计数器清零
			}
		}
		else{
			num++;//计连续空白长度
			if(i==n||s[i+1]=='#'){//边界
				if(i==n||num+pre==i)num++;//边界时无交界，赠一
				if(num==2//2 是算上了交界出不可填色的空白，去除后无空白可填充
                  		||(pre<2&&num%2==0)//偏移量小于 2，但是须填充长 2 连续块
                   		||(pre<1&&num>2)//不可偏移，但须填充
                  		)return;//统统不合法
				num-=2;//去除边界空白
				if(num%2==0)num-=3,ans.emplace_back(2);//偶数特殊处理
				for(int i=1;i<=(num+1)/2;i++)
					ans.emplace_back(1);
				num=0;//计数器清零
			}
		}
	}
	printf("%ld\n",ans.size());
	for(auto v:ans)
		printf("%d ",v);
	exit(0);
}
main(){
	scanf("%s",s+1);
	n=strlen(s+1);//字符串长度
	for(int i=1;i<=n;i++){
		if(s[i]=='_'){
			num++;//计算连续 _ 的数量
			if(s[i+1]=='#'||i==n){
				if(i==n||num==i)mx=min(mx,num);
				else mx=min(mx,num-1);//计算偏移量上界
				num=0;//清空计数器
			}
		}
	}
	if(mx==1e9 //没有 _
   	||s[1]=='#'//首连续段不可偏移
  	||s[n]=='#'//尾连续段不可偏移
      	)mx=0;
  	//特殊判断
	for(pre=mx;pre>=0;pre--)work();//枚举偏移量
	puts("-1");
}
```

---

## 作者：happybob (赞：0)

感觉比较直接的一个题啊，想法应该没有什么岔路可走吧。

显然地你需要考虑对于固定的 $p$，哪些位置是必须要填的。当然对于每个位置你有一个 $O(n)$ 的判断方式，就是强制这个点不选然后从前往后贪心。但这个东西不容易推广到式子里，自然就不好继续下去。

观察一下发现我们删掉一个位置的后果的其实是一部分格子被浪费。具体来说应该是，我们按照最优策略先将 $p$ 填进去后，这个位置所在连续黑色段的那段前缀。简单手玩可以发现假设最优策略填完 $p$ 最后还剩下了 $x$ 个白色空格，那么这个最优策略中每个极长连续黑色段的第 $x+1$ 个位置一直到这段结束都是必选位置，其他位置都不是必选位置。即每个极长黑色连续段有一段定长的前缀不是必选位置，然后那段后缀都是必选的。注意如果段长小于等于 $x$，那么整段都是非必选的。

然后一个直接想法是枚举 $x$。但是这样看着复杂度不太对。事实上 $x$ 必然有个上界，具体来说需要考虑给定的 $m$ 图中的黑色连续段之间，以及最前面和最后面的，这个地方细节挺多的，但推一推就出来了。

确定了 $x$ 的上界，我们从大到小枚举 $x$，此时可以注意到我们要做的就是段与段之间的。这部分直接填 $01$ 交错就好。特别注意这里和段与段之间长度奇偶性有关，推一下就好。如果 $x$ 合法就输出，不然继续枚举直到 $-1$。

事实上你发现 $x$ 取我们求出的上界通常是优的，除非你发现有时候选了 $x$ 会导致两端之间粘合在一起，比如两端中间只有两个位置没选，此时没办法构造，从而 $x$ 要减少。这个地方可以在预处理的时候求出一个合法的 $x$ 从而只需要一次构造即可。

总复杂度 $O(n)$，好想但细节一车。

[Submission Link](https://codeforces.com/problemset/submission/1510/264861752)。

---

