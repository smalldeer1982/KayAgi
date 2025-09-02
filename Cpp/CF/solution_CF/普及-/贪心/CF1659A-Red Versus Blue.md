# Red Versus Blue

## 题目描述

红队和蓝队进行了一场比赛，这场比赛分为了 $n$ 个阶段。

已知比赛中红队获胜的阶段数 $r$ 以及蓝队获胜的阶段数 $b$，由于蓝队实力不如红队，满足 $b<r$。你错过了这场比赛，想知道每个阶段的获胜队伍。

你用一个长 $n$ 的字符串来表示每个阶段的获胜队伍。具体地，将每一个阶段的获胜队伍连起来形成一个字符串，这个字符串的第 $i$ 位若为 $R$ 则表示红队赢了第 $i$ 个阶段，为 $B$ 则表示蓝队赢了这个阶段。你认为为了让比赛更有看头，某个队伍连续获胜的阶段数越少越好。

请输出一种可能的字符串，其中每一队连续获胜的阶段数的最大值最小，若有多解输出任意一种。

## 样例 #1

### 输入

```
3
7 4 3
6 5 1
19 13 6```

### 输出

```
RBRBRBR
RRRBRR
RRBRRBRRBRRBRRBRRBR```

## 样例 #2

### 输入

```
6
3 2 1
10 6 4
11 6 5
10 9 1
10 8 2
11 9 2```

### 输出

```
RBR
RRBRBRBRBR
RBRBRBRBRBR
RRRRRBRRRR
RRRBRRRBRR
RRRBRRRBRRR```

# 题解

## 作者：wdgm4 (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1659A)


------------

由于要让某个队伍**连续获胜**的阶段数越少越好（就是让连续字符的个数越少越好），并且保证 $ b<r $，所以我们可以把字符 $\texttt{B}$ 当做隔板，让隔板把一串全为字符 $\texttt{R}$ 的字符串分为 $b+1$ 个区间，例如 $n=7 , r=4 , b=3$ 时，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/vewuvc56.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

再例如 $n=6,r=5,b=1$ 时，

![](https://cdn.luogu.com.cn/upload/image_hosting/vvj38ch9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在我们计算时，我们可以先算出把全为字符 $\texttt{R}$ 的字符串平均分为 $b+1$ 段的字符数。但有时会多出几个 $\texttt{R}$，就像上图中的蓝圈里的 $\texttt{R}$，那我们只需要把这些多的匀给每一段，因为多的绝对不会超过 $b+1$。



------------
于是.......
### code

```cpp
#include<bits/stdc++.h>
#define XD 114514

using namespace std;
int t;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		int n,r,b,nem,nem1,nem2;
		scanf("%d%d%d",&n,&r,&b);
		nem=b+1;//nem求要把 R分成几段
		nem1=r/nem;//nem1求平均每段最少分几个
		nem2=r%nem;//nem2求平均分完剩下的，需要匀给每一段的
		for(int j=1;j<=nem;j++){
			for(int k=1;k<=nem1;k++) printf("R");
			if(nem2){
				printf("R");
				nem2--;
			}
			if(j!=nem) printf("B");
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：wangkangyou (赞：1)

前言：本蒟蒻刚学会写题解，各位 dalao 们不喜勿喷，谢谢。

### 首先我们先来分析一下题意：

有一个长度为 $n$ 的字符串由 $r$ 个字符 `R` 和 $b$ 个字符 `B` 组成，要求其中连续相同的字串长度最小。

从小学奥数问题"植树问题"中，我们可以发现：
1. 若两头都种树，则 划出的区间为 棵数 $ - 1$；
2. 若一头种树一头不种，则有 棵数 $=$ 区间数；
3. 若两头都不种树，则 划出的区间数 $=$ 树的棵数 $+ 1$。

那么若我们想要用同样的棵数划出更多的区间，就应该选择第三种方案，即用头尾不让蓝队赢，并用赢的比赛来隔断红队的连胜。

~~那么红队每个连胜段里到底赢几场呢？~~

别急，我来告诉你。由于红队赢的场数一定比蓝队多，我们将他们分为 $b + 1$ 段，每段 **至少** 有 $\lfloor \dfrac{n}{b+1}\rfloor$ 场 。 那多出来的场数我们就可以分配给前 $n \bmod (b + 1)$ 段，达到连胜场数最小的条件。

上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
   int sum=0,f=1;
   char ch=getchar();
   for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
   for(;isdigit(ch);ch=getchar()) sum=(sum<<3)+(sum<<1)+(ch^48);
   return sum*f;
}
void write(int x){
   if(x<0) putchar('-'),x=-x;
   if(x>9) write(x/10);
   putchar('0'+x%10);
   return;
}
const int inf=1e10;
const int N=1e6+10;
signed main(){
   int T = read ();
   while (T --){
      int n = read (), r = read (), b = read ();
      //由于r一定大于b，所以我们可以将r直接分为b+1段
      int x = r / (b + 1);
      int y = r % (b + 1);
      for (int i = 1; i <= b + 1; ++ i){
         if (i <= y){
            for (int j = 1; j <= x + 1; ++ j){
               putchar ('R');
            }
         }else{
            for (int j = 1; j <= x; ++ j){
               putchar ('R');
            }
         }
         if (i != b + 1) putchar ('B');
      }
      putchar ('\n');
   } 
   return 0;
}

```

---

## 作者：hhh_778899 (赞：1)

## 题意

- 给定 $r$ 个 $R$ 和 $b$ 个 $B$ ，要求输出最长连续相同字符个数最少的字符串。

## 思路

- 由于 $b<r$ ，所以考虑用 $b$ 个 $B$ 把 $r$ 个 $R$ 分割成尽量平均的 $(b+1)$ 段。

- 我们先给每段插入 $\left\lfloor\dfrac{r}{b+1}\right\rfloor$ 个 $R$ 字符，但此时会剩余 $r \bmod (b+1)$ 个 $R$ 。

- 该如何处理剩余字符呢？显然，将剩余字符平均分到 $r \bmod (b+1)$ 段中是最好的方法。

- 这样一来，每一段至多增加 $1$ 个 $R$ ，是最优解。

- 好了，有了上面的分析，让我们开始写代码吧。

## 代码

```cpp
#include <iostream>
using namespace std;

int main()
{
	int t,n,r,b;
	cin>>t;
	for(int x=1;x<=t;x++)
	{
		cin>>n>>r>>b;
		for(int y=1;y<=b+1;y++)//一共有(b+1)段
		{
			for(int z=1;z<=r/(b+1);z++) cout<<"R";
			if(r%(b+1)>=y) cout<<"R";
			if(b>=y) cout<<"B";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：___cjy__ (赞：1)

# CF1659A Red Versus Blue 题解

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-cf1659a)

[题目传送门](https://www.luogu.com.cn/problem/CF1659A)

### 题目大意：

给定一个字符串中有 $r$ 个 $R$ 和 $b$ 个 $B$，求一种能使字符串中最长的连续且相同的字符的长度最小的方案。

### 正文：

读懂题目之后，让我们先来分析一下题目给的样例。我们以第一组样例的第三组数据为例：（为了便于阅读我用颜色区分不同的字母）

$$\color{red}\text{RR}\color{blue}\text{B}\color{red}\text{RR}\color{blue}\text{B}\color{red}\text{RR}\color{blue}\text{B}\color{red}\text{RR}\color{blue}\text{B}\color{red}\text{RR}\color{blue}\text{B}\color{red}\text{RR}\color{blue}\text{B}\color{red}\text{R}$$

可以发现，每组 $R$ 都被一个 $B$ 隔开了，总共隔出了 $b+1$ 组。而每组 $R$ 的数量都十分接近，这样正好可以让每组 $R$ 的长度最小。所以，对于每组输入，我们只需要将所有的 $R$ 平均分成 $b+1$ 份，剩下的 $R$ 按顺序插入到每组 $R$ 中，再用 $B$ 隔开每一组 $R$，即可得到最终答案。

最后奉上代码：（含有少量注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T,n,r,b;
	cin>>T;
	while(T--){
		cin>>n>>r>>b;
		int x=r/(b+1),k=r%(b+1);//x表示每组R的数量，k表示剩下的R的数量 
		for(int i=1;i<=k;i++){
			for(int j=1;j<=x+1;j++) cout<<"R";//前k组输出x+1个R 
			cout<<"B";
		}
		for(int i=k+1;i<b+1;i++){
			for(int j=1;j<=x;j++) cout<<"R";
			cout<<"B";
		}
		for(int i=1;i<=x;i++) cout<<"R";//最后一组R后面没有B，单独输出 
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Terry2011 (赞：0)

# 题目分析：
本题要求每组同一队连续赢的阶段数最大值最小，所以，我们要尽可能地把 $R$ 和 $B$ 穿插着放。因为 $b<r$，所以，我们应当将 $b$ 个 $B$ 和 $r$ 个 $R$ 比较平均地分成 $b+1$ 段再输出。

接下来，我们来考虑剩余的字符：$R$ 还剩余 $r \bmod (b+1)$ 个。我们可以以此特判：每段最多增加一个 $R$。
# 代码：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int t,n,r,b;//声明定义t,n,r,b四个变量
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){//t次数据
        cin>>n>>r>>b;
		for(int j=1;j<=b+1;j++){//第一次的分段输出
			for(int k=1;k<=r/(b+1);k++){
            cout<<"R";
            }
			if(r%(b+1)>=j) cout<<"R";//特判
			if(b>=j) cout<<"B";	
            }
		cout<<endl;//换行
    }
	return 0;
}
```

---

## 作者：Bbaka (赞：0)

- 题目大意

给定 $r$ 个字符 $R$ 和 $b$ 个字符 $B$，需要找到一种 $R$ 和 $B$ 的排列方式使得最长的连续相同的字符个数最小。

- 思路

因为题目保证了 $b<r$ ，所以考虑将 $r$ 个 $R$ 字符插入到 $b$ 个 $B$ 字符之间。

$b$ 个 $B$ 字符中有 $b+1$ 段空隙可插入，先在每段中插入 $\lfloor \frac{r}{b+1} \rfloor$ 个 $R$ 字符，此时还会多出 $r\mod (b+1)$ 个 $R$，只需要任选 $r \mod (b+1)$ 段，每段多加入一个 $R$ 即可。

这样每段最多可能有 $\lfloor \frac{r}{b+1} \rfloor +1 $ 个连续的 $R$，若减少这段的 $R$ 必定会导致另一段连续 $R$ 个数变为 $\lfloor \frac{r}{b+1} \rfloor +1 $ 或 $\lfloor \frac{r}{b+1} \rfloor + 2$，从而导致答案可能不优。

- 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const char space=' ';
const double eps=0.001;
const double pi=3.1415;
int t,n,r,b;
int main () {
    cin>>t;
    while (t--) {
        cin>>n>>r>>b;
        int w=r/(b+1);
        int q=0;
        int p=r%(b+1);
        while (r) {
            cout<<"R";
            --r;
            ++q;
            if (q%w==0) {
                if (p) {
                    p-=1;
                    r-=1;
                    cout<<"R";
                }
                if (b) {
                    cout<<"B";
                    --b;
                }
            }
        }
        cout<<endl;
    }
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

很明显，最优做法是：用 $b$ 个 `B` 将 `R` 分成 $b+1$ 份，尽量使得 `R` 平均。

那么，我们就算出每个 `R` 最少连续出现次数 $x=\lfloor n/(b+1)\rfloor$。但是，肯定有 $y=r\operatorname{mod}(b+1)$ 段需要多输出一个 `R`。

模拟一下即可。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
#define max_n 100
int t;
int n;
int r;
int b;
int x;
int y;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1659A_1.in","r",stdin);
	freopen("CF1659A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&r,&b);
		x=r/(b+1);
		y=r%(b+1);
		for(int i=1;i<=b+1;++i){
			for(int j=1;j<=x;++j)printf("R");
			if(i<=y)printf("R");
			if(i<=b)printf("B");
		}
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/74293743)

By **dengziyue**

---

## 作者：wcop114514 (赞：0)

题目说要让连胜次数最小，所以我们要把红队胜利次数平均分成 $b + 1$ 段也就是蓝队胜利次数。

剩下的 $r \bmod b+1$ 增加在本段后方。

给各位大佬奉上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r,b;
void solve(){
	cin>>n>>r>>b;
		for(int j=1;j<=b+1;j++){
			for(int k=1;k<=r/(b+1);k++){
            cout<<"R";
            }
			if(r%(b+1)) cout<<"R";//特判
			if(b>=j) cout<<"B";	
            }
		cout<<endl;//换行

}
int main() {
	int t;
	cin>>t;
	while(t--)solve(); 
	return 0;//好孩子的习惯
}
```

---

## 作者：YangXiaopei (赞：0)

## Solution:

想要让 $R$ 的每段尽量少，就要让 $R$ 分成尽可能多的段，那最多多少段呢？很明显，一个 $B$ 可隔出一段，那 $b$ 个 $B$ 可隔成 $b+1$ 段。

然后模拟即可。

注：代码变量名与题目有出入。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, a, b, c;
int main(){
	cin >> t;
	while(t--){//t 组数据
		cin >> a >> b >> c;
		int x = b / (c + 1);//每段 x 个
		if(x * (c + 1) == b){
			for(int i = 1; i <= c; i++){//前 c 组有输 B 的
				for(int j = 1; j <= x; j++){
					cout << "R";
				}
				cout << "B";
			}
			for(int i = 1; i <= x; i++){//最后一组不输 B
				cout << "R";
			}
			cout << "\n";
		}
		else{//有剩余
			int y = b - x * (c + 1);//剩 y 个
			for(int i = 1; i <= y; i++){//y 组多 1 个的先输出。
				for(int j = 1; j <= x + 1; j++){
					cout << "R";
				}
				cout << "B";
			}
			for(int i = 1; i <= c - y; i++){// 再输出没多的后 c-y 组
				for(int j = 1; j <= x; j++){
					cout << "R";
				}
				cout << "B";
			}
			for(int i = 1; i <= x; i++){//单独一组
				cout << "R";
			}
			cout << "\n";
		}
	}
	return 0;
}
```

---

