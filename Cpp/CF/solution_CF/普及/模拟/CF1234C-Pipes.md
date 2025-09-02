# Pipes

## 题目描述

You are given a system of pipes. It consists of two rows, each row consists of $ n $ pipes. The top left pipe has the coordinates $ (1, 1) $ and the bottom right — $ (2, n) $ .

There are six types of pipes: two types of straight pipes and four types of curved pipes. Here are the examples of all six types:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/f58b589c4b7a5370d2912a5690db68318ac884a6.png) Types of pipes You can turn each of the given pipes $ 90 $ degrees clockwise or counterclockwise arbitrary (possibly, zero) number of times (so the types $ 1 $ and $ 2 $ can become each other and types $ 3, 4, 5, 6 $ can become each other).

You want to turn some pipes in a way that the water flow can start at $ (1, 0) $ (to the left of the top left pipe), move to the pipe at $ (1, 1) $ , flow somehow by connected pipes to the pipe at $ (2, n) $ and flow right to $ (2, n + 1) $ .

Pipes are connected if they are adjacent in the system and their ends are connected. Here are examples of connected pipes:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/c302dc3fb9fa832083fc1da665e39051a6975a62.png) Examples of connected pipes Let's describe the problem using some example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/af0d45bfd33558aed14bb2874c96920e8db881d3.png) The first example input And its solution is below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/108e6e3757d5df308ece8023b08c503aa013af65.png) The first example answer As you can see, the water flow is the poorly drawn blue line. To obtain the answer, we need to turn the pipe at $ (1, 2) $ $ 90 $ degrees clockwise, the pipe at $ (2, 3) $ $ 90 $ degrees, the pipe at $ (1, 6) $ $ 90 $ degrees, the pipe at $ (1, 7) $ $ 180 $ degrees and the pipe at $ (2, 7) $ $ 180 $ degrees. Then the flow of water can reach $ (2, n + 1) $ from $ (1, 0) $ .

You have to answer $ q $ independent queries.

## 说明/提示

The first query from the example is described in the problem statement.

## 样例 #1

### 输入

```
6
7
2323216
1615124
1
3
4
2
13
24
2
12
34
3
536
345
2
46
54
```

### 输出

```
YES
YES
YES
NO
YES
NO
```

# 题解

## 作者：pzc2004 (赞：6)

[题目传送门](https://www.luogu.org/problem/CF1234C)

因为可以旋转，所以直接将1、2视为一种，将3、4、5、6视为一种。

然后从1开始运行，显然只存在一条路径，所以如果遇到1、2就移到右边一格，遇到3、4、5、6时就判断一下，如果当前在第一行就移到下面一格，如果在第二行就移到上面一格，如果移到了(1,n)就输出YES。

代码：
``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[400001],vis[400001];
bool ans;
void dfs(int x,int y)
{
	if(x==n && y==2 && a[x+n]==2){ans=1;return;}
	if(a[x+(y-1)*n]==2)dfs(x+1,y);
	if(a[x+(y-1)*n]>=3 && a[x+(y-1)*n]<=6)
	{
		if(y==1)
		{
			if(a[x+n]>=3 && a[x+n]<=6)
			{
				if(x==n){ans=1;return;}
				dfs(x+1,2);
			}
		}
		else
		{
			if(a[x]>=3 && a[x]<=6)dfs(x+1,1);
		}
	}
}
int main()
{
	int q;
	scanf("%d",&q);
	while(q--)
	{
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){scanf("%1d",&a[i]);if(a[i]==1)a[i]=2;}
		for(int i=1;i<=n;i++){scanf("%1d",&a[i+n]);if(a[i+n]==1)a[i+n]=2;}
		dfs(1,1);
		if(ans)printf("YES\n");else printf("NO\n");
	}
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：minVan (赞：2)

**题目大意**

给定 $2 \times n$ 的管道网络，给出每个格子的管道类型，每个格子可以旋转任意次 $90$ 度。求从 $(1, 0)$ 向右流入的水流是否能够从 $(2, n)$ 向右流出。

**解题思路**

模拟、dfs。

从终点出发，可以发现只有对于这两种水管都只有一种选择的可能，我们这样就必然可以推导到下一个位置，如果不能那么就说明不能通水。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int t, n;
char s[3][N];
bool dfs(int x, int y, int nx, int ny) {
	if(x == 1 && y == 0) {
		return 1;
	}
	if(y == 0) {
		return 0;
	}
	if(s[x][y] <= '2') {
		if(x == nx) {
			return dfs(x, y - 1, x, y);
		} else {
			return 0;
		}
	} else {
		if(x == nx) {
			return dfs(x % 2 + 1, y, x, y);
		} else {
			return dfs(x, y - 1, x, y);
		}
	}
}
int main() {
	cin >> t;
	while(t--) {
		cin >> n;
		scanf("%s%s", s[1] + 1, s[2] + 1);
		bool f = dfs(2, n, 2, n + 1);
		if(!f) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
		}
	}
	return 0;
}
```

---

## 作者：Ludo (赞：1)

这东西还是想了好久... 我还是太**naive**了...

而且还写得很长...

## SOLUTION:

### 结论

1. 由于初始水流从左方来，因此在左上角的管中，如果是直的，它类型一定要转换成2；如果是弯的，类型一定要转换成4。

2. 路径貌似是唯一的(若有)。

3. 通过前一条管，可以推测出当前管的类型。

4. 跟其他大佬说的一样，水只会向右流。


### 在此题解的一些注明

1. 定义最左边的x坐标为1，最右边为n。

2. 上排的y坐标为1，下排为2。

### 要求

水流要流到(n,2).

1. 对于1号管：

路径中，不会有1号类型的管，不然水就流出去了… 要不然就是接不上。

2. 对于2号管：

这管可以接上2,4,5号管，并且可以分别讨论。

    a) 右边是一直管：
         2号管: 接在原来2号管的右边，y轴位置不变。
    b) 右边是一弯管：
         4号管: 当2号管的y坐标为1时，接在它的右边。
         5号管: 当5号管的y坐标为2时，接在它的右边。

水流向右移动。

3. 对于3号管：

这管可以接上2,4号管，并且可以分别讨论。

    a) 右边是一直管：

         2号管: 接在原来3号管的右边，y轴位置不变。
         
    b) 右边是一弯管：
         4号管: 接在原来3号管的右边，y轴位置不变。
         
水流向右移动。

4. 对于4号管：

必须在下方接上6号管，不然直接宣告失败。

水流向下移动。

5. 对于5号管：

必须在下方接上3号管，不然直接宣告失败。

水流向上移动。

6. 对于6号管：

这管可以接上2,5号管，并且可以分别讨论。

    a) 右边是一直管：

        2号管: 接在原来6号管的右边，y轴位置不变。

    b) 右边是一弯管：

        5号管: 接在原来6号管的右边，y轴位置不变。

水流向右移动。

### 一些边界得要考虑清楚，不然就WA了…

## 代码

```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
int a[200002][3],q,s,n,x,y;
char c[200002];
bool succ;
int main(void)
{
	cin>>q;
	while(q--)
	{
		cin>>n;s=1;succ=1;
		scanf("%s",c);
		for (int i=1;i<=n;i++)
		{
			a[i][1]=c[i-1]-'0';
		}
		scanf("%s",c);
		for (int i=1;i<=n;i++)
		{
			a[i][2]=c[i-1]-'0';
		}
		x=1;y=1;
		if (a[x][y]<=2) a[x][y]=2; 
		if (a[x][y]>2) a[x][y]=4;
		while (x!=n+1&&succ==1&&y>0&&y<3)
		{
			if (a[x][y]==2)
			{
				if (a[x+1][y]>2&&y==1) a[x+1][y]=4;
				else if (a[x+1][y]>2&&y==2) a[x+1][y]=5;
				else a[x+1][y]=2;
				x++;
			}
			else if (a[x][y]==4)
			{
				if (a[x][y+1]>2)a[x][y+1]=6,y++;
				else
				{
					cout<<"NO"<<endl;
					succ=0;
				}
			}
			else if (a[x][y]==3)
			{
				if (a[x+1][y]>2||x==n) a[x+1][y]=4;
				else a[x+1][y]=2;
				x++;
			}
			else if (a[x][y]==5)
			{
				if (a[x][y-1]>2) a[x][y-1]=3,y--;
				else 
				{
					cout<<"NO"<<endl;
					succ=0;
				}
			}
			else if (a[x][y]==6)
			{
				if (a[x+1][y]>2||x==n) a[x+1][y]=5,x++;
				else if (a[x+1][y]<3)
				{
					a[x+1][y]=2;
					x++;
				}
			}
		}
		if (succ==0) 
		{
			continue;
		}
		//cout<<y<<endl;
		if (y==2) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	} 
}

```


---

## 作者：serverkiller (赞：1)

# CF1234C 【Pipes】
---
题意:
给你一个管道阵 问是否可以通过旋转管道来从左上角到达右下角

这道题目直接模拟就可以了 如果说是直的就直接走,是弯的就看下面有没有接应的没有直接NO 有的话去下一列找就ok了

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[3][200005];
int flag,state;

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= 2; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                scanf("%1d",&a[i][j]);
            }
        }
        state = 1;
        flag = 1;
        for (int i = 1; i <= n; i++)
        {
            if (state == 1)
            {
                if (a[state][i] == 1 || a[state][i] == 2) continue;
                else if (a[state+1][i] >= 3 && a[state+1][i] <= 6)
                {
                    state = 2;
                    continue;
                }
                else
                {
                    flag = 0;
                    break;
                }
            }
            else
            {
                if (a[state][i] == 1 || a[state][i] == 2) continue;
                else if (a[state-1][i] >= 3 && a[state-1][i] <= 6)
                {
                    state = 1;
                    continue;
                }
                else
                {
                    flag = 0;
                    break;
                }
            }
        }
        if (state == 2 && flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```

---

## 作者：B_Qu1e7 (赞：1)

一道简单的模拟。

由于图只有两行，所以水只能从左向右流动。

所以状态更新向下一列转移。如果下一列是两个弯管，那么水只可能流到另一行。否则，如果当前行的下一列是直管，那么水只可能流到当前行。

最后判断能否流到$(N,1)$即可。
```
#include<cstdio>
#define rint register int
int Q,N,can=0;
bool a[200005][2];//数组开反了，严格来讲的话应该是[2][200005]两行才对，不过没影响。
void pre(rint x,register bool y)
{
	if(x==N)//流到了(N,1)，答案为yes,返回。
	{
		can=y;
		return;
	}
	if(!a[x+1][y])//下一列是直管
	{
		pre(x+1,y);//挪到下一列，当前行
	}
	else if(a[x+1][0]&&a[x+1][1])//下一列是两个弯管
	{
		pre(x+1,!y);//挪到下一列，另一行
	}
}
int main()
{
	scanf("%d",&Q);
	while(Q--)
	{
		can=0;
		scanf("%d",&N);
		for(rint i=1,b;i<=N;++i)
		{
			scanf("%1d",&b);
			a[i][0]=(b+1)>>2;
		}
		for(rint i=1,b;i<=N;++i)
		{
			scanf("%1d",&b);
			a[i][1]=(b+1)>>2;
		}
		//1 2转移成0，3 4 5 6转移成1
		pre(0,0);
		puts(can?"YES":"NO");
	}
}
```

---

## 作者：__JiCanDuck__ (赞：0)

好水。。。这是一篇不用搜索的题解。

### 思路

挺好想的，因为只有两行，水不会回流，所以可以一列一列的考虑。

如果目前这个是直的，那么下一行。如果是弯的，那么如果和我同一列的另一个也是直的，那么就冲出去了，NO，如果是弯的，那么水会换行。

![](https://z4请更换图床a.net/images/2023/01/01/5c18d193a038f5d49db3dc05fbb023ca.png)


### 代码

```cpp

#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 5;

int n, a[2][kMaxN], t;
char c;

int main() {
  for (cin >> t; t; t--) {
    cin >> n;
    for (int i = 0; i <= 1; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> c;
        a[i][j] = (c <= '2' ? 1 : 2);
      }
    }
    int k = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
      if (a[k][i] == 1) {
        continue;
      } else {
        if (a[!k][i] == 1) {
          ans = 1;
          break;
        } else {
          k = !k;
        }
      }
    }
    if(k == 0){
      ans = 1;
    }
    cout << (ans ? "NO" : "YES") << '\n';
  }
  return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[CF1234C](https://www.luogu.com.cn/problem/CF1234C)

[Pipes](https://codeforces.com/contest/1234/problem/C)

挺好玩的。

### 思路

一种不用递归的写法。

开始时没注意到这个网格只有 $2$ 行。呵呵。不妨设为第 $0$ 和第 $1$ 行。

从右侧进入 $(1,0)$。当从右侧进入点 $(x,y)$ 时，有一下几种情况：

##### 1.当前格管道为 $1$ 或 $2$。

由于在右侧进入，所以只能通过 $2$，从左侧出去，从右侧进入 $(x+1,y)$。

##### 2.当前格管道为 $3$ 至 $6$

由于在右侧进入，所以只能通过 $4$ 或 $6$，从上或下侧出去，进入 $(x, y\oplus 1)$，即去到另一行。

如果在 $(x, y\oplus 1)$ 处管道为直道，则无路可走，输出错误。否则拐弯，从右侧进入 $(x+1, y\oplus 1)$。

---

因此，从 $1$ 到 $n$ 走一遍，记录 $y$ 的变化即可。

### code

```cpp#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int t;
int n,a[maxn][3];
char c[maxn];
int y;
void sovle(){
	n=read();
	scanf("%s",c+1);
	for(int i=1;i<=n;i++){
		if(c[i]<='2')a[i][0]=2;
		else a[i][0]=4;
	}
	scanf("%s",c+1);
	for(int i=1;i<=n;i++){
		if(c[i]<='2')a[i][1]=2;
		else a[i][1]=4;
	}
	y=0;
	for(int i=1;i<=n;i++){
//		cout<<i<<" "<<y<<" ";
		if(a[i][y]==4){
			y^=1;
			if(a[i][y]==2){
				printf("NO\n");
				return ;
			}
		}
//		cout<<y<<endl;
	}
	if(!y)printf("NO\n");
	else printf("YES\n");
}
signed main(){
	t=read();
	while(t--){
		sovle();
	}
}

```


---

## 作者：wangyixuan_s_father (赞：0)

## CF1234C题解
~~这题是真的水~~
#### 题意
有六种水管（两种直的和四种弯的），样式如下：![图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1234C/f58b589c4b7a5370d2912a5690db68318ac884a6.png)
可以将水管旋转 $90$ 度，且次数不限。现有两行水管，每行n个，求是否能通过旋转使从（$1,0$）来的水流通过（$1,1$）和（$2,n$）流向（$2,n+1$）。
#### 思路
首先注意到 $90$ 度旋转次数不限，然后我们就可以惊喜的发现，后四种水管通过旋转可以互相得到（后四种水管等于一种），前两种水管也可以互相得到（前两种水管等于一种）。那么轻松地就能归纳出水流要经过的水管 $i$ 可能发生的情况：

1.第 $i$ 根水管是直的，水流畅通。

2.第 $i$ 根水管是弯的，另一行对应的水管也是弯的，水流换行。

3.第 $i$ 根水管是弯的，另一行对应的水管是直的，水流不通。

然后简单的模拟一下就能快乐地 $AC$ 啦！
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],b[200005],rw=1,f;
string s;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        cin>>s;
        for(int i=0;i<n;i++)//六种变两种
        {
            if(s[i]<='2')a[i+1]=1;
            else a[i+1]=2;
        }
        cin>>s;
        for(int i=0;i<n;i++)
        {
            if(s[i]<='2')b[i+1]=1;
            else b[i+1]=2;
        }
        for(int i=1;i<=n;i++)
        {
            if(a[i]==2&&b[i]==2)//都是弯的
            {
                if(rw==1)rw=2;
                else rw=1;
            }
            if(a[i]==2&&b[i]==1&&rw==1||a[i]==1&&b[i]==2&&rw==2)//一弯一直，恰巧水流经过弯水管
            {
                f=1;
                break;
            }
            //都是直的直接跳过
        }
        if(f==1||rw==1)//判断水流中途趋势或没到第二行
        {
            cout<<"NO"<<endl;
        }
        else cout<<"YES"<<endl;
        rw=1,f=0;//别忘了初始化
    }
    return 0;\\完结撒花
}
```


---

## 作者：xuorange (赞：0)

因为这些水管可以旋转且旋转多少次都不会影响答案，所以可将 $1,2$ 视为一种，将 $3,4,5,6$ 视为一种。

然后我们就可以直接模拟，一列一列的走，如果是 $1$ 或 $2$ 直接走去下一列（挡住了）。

走到 $3,4,5,6$ 的时候需要判断一下这一列的另一个是不是也是 $3,4,5,6$ ，如果是继续走，如果不是直接 $no$ 。

然后走到最后一列判断一下，是不是在第二列，如果是输出 $yes$ ，否则输出 $no$ 。

```
#include<bits\stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int len;
        string s[2];
        cin>>len;
        cin>>s[0];
        cin>>s[1];
        int k=0; //k表示当前处理的那个在第几行，第1行是0，第二行是1
		//开始从左上角出发，所以将k初始值设为0 
        bool ok=true; //是否满足 
        for(int i=0;i<len;i++){
           if(s[k][i]=='1'||s[k][i]=='2') continue;
           else{ //要是当前那一行不是1或2就需要切换到另一行 
               if(s[1-k][i]=='1'||s[1-k][i]=='2'){ //1-k就是另一行（k=0,1-k=1；k=1,1-k=0） 
                   ok=false; //开始就堵住了直接不行 
                   break;
               }
               else k=1-k; //同上，切到另一行 
		   }          
        }
        if(ok){ 
            if(k==1)cout<<"YES"<<endl; //如果最后那个在第二行，说明可以 
            else cout<<"NO"<<endl; //不在第二行也不行 
        }
        else cout<<"NO"<<endl;
    }
    return 0;
}
```

---

## 作者：开始新的记忆 (赞：0)

题目大意：现在有一个2*n的方格阵，每个格子都有一根水管，有以下六种可能（具体看题目），问你是否可以转动其中的一些格子使得从1，1到2，n+1有一条通路。

大致思路：我们发现，图1，2可以通过转动得到对方，而图3，4，5，6也可以，所以不妨把1，2记为1；3，4，5，6记为2。一开始假设我们从第一行通过，有以下三种情况：1.前面的管道是1，那么继续向前。2.前面是2，前下方是2，那么我们会走到下面一行。3.前面是2，下面是1，那么就不可能往前走。我们每次只需判断一下可不可以走，然后最后看有没有到达第二行即可。

```
#include<bits/stdc++.h>
using namespace std;
int q,n,a[200010][2];
string aa,aaa; 

int main()
{   cin>>q;
    while(q--)
    {
        int last=0,fl=1;
        memset(a,0,sizeof(a)); 
		cin>>n>>aa>>aaa;
        for(int i=1;i<=n;++i)
        {
            if(aa[i-1]=='1' || aa[i-1]=='2')
                a[i][0]=1;
            else
                a[i][0]=2;
        }
        for(int i=1;i<=n;++i)
        {
            if(aaa[i-1]=='1' || aaa[i-1]=='2')
                a[i][1]=1;
            else
                a[i][1]=2;
        }
        for(int i=1;i<=n;++i)
        {
            if(a[i][last]==1)
                continue;
            if(a[i][(last+1)%2]==1)
            {
                fl=0;
                break;
            }
            else
                last=(last+1)%2;
        }
        if(last==1 && fl==1)
            cout<<"YES"<<endl;
        else
        	cout<<"NO"<<endl;
    }
    return 0;
}
```


---

## 作者：littleseven (赞：0)

### 题目解析：

[博客地址](http://littleseven.top/)

由于我们只有两行水管，那么我们直接模拟就好啊（我是一条小水流$QwQ$）。

我们可以发现一些有趣的性质（假设当前点为$(i, j)$，$i,k$表示两行）：

- 如果$(i，j+1)$是直管($1,2$号)，那么我们只能走到$(i,j+ 1)$。
- 如果$(i,j+1)$和$(k,j + 1)$都是弯管（$3,4,5,6$号），那么我们只能走到$(k,j+1)$。

按照这个性质递归模拟就行，找到就是$YES$，否则就是$NO$。

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e5 + 10;
 
char s[N];
 
int mp[N][2];
 
int q, n, tag;
 
void work(int x, int y) {
	if (x > n) {
		return ;
	}
	if (x == n && y == 1) {
		tag = 1;
		return ;
	}
	if (mp[x + 1][y] == 0) {
		work(x + 1, y);
	}
	else if (mp[x + 1][y] && mp[x + 1][y ^ 1]) {
		work(x + 1, y ^ 1);
	}
	return ;
}
 
int main() {
	scanf("%d", &q);
	while (q -- ) {
		tag = 0;
		scanf("%d", &n);
		scanf("%s", s + 1);
		for (int i = 1; i <= n; i ++ ) {
			if (s[i] == '1' || s[i] == '2') {
				mp[i][0] = 0;
 
			}
			else {
				mp[i][0] = 1;
			}
		}
		scanf("%s", s + 1);
		for (int i = 1; i <= n; i ++ ) {
			if (s[i] == '1' || s[i] == '2') {
				mp[i][1] = 0;
			}
			else {
				mp[i][1] = 1;
			}
		}
		work(0, 0);
		if (tag == 1) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}
```


---

