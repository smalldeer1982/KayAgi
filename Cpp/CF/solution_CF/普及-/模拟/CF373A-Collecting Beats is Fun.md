# Collecting Beats is Fun

## 题目描述

Cucumber boy is fan of Kyubeat, a famous music game.

Kyubeat has $ 16 $ panels for playing arranged in $ 4×4 $ table. When a panel lights up, he has to press that panel.

Each panel has a timing to press (the preffered time when a player should press it), and Cucumber boy is able to press at most $ k $ panels in a time with his one hand. Cucumber boy is trying to press all panels in perfect timing, that is he wants to press each panel exactly in its preffered time. If he cannot press the panels with his two hands in perfect timing, his challenge to press all the panels in perfect timing will fail.

You are given one scene of Kyubeat's panel from the music Cucumber boy is trying. Tell him is he able to press all the panels in perfect timing.

## 说明/提示

In the third sample boy cannot press all panels in perfect timing. He can press all the panels in timing in time 1, but he cannot press the panels in time 2 in timing with his two hands.

## 样例 #1

### 输入

```
1
.135
1247
3468
5789
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5
..1.
1111
..1.
..1.
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
1
....
12.1
.2..
.2..
```

### 输出

```
NO
```

# 题解

## 作者：Luo_gu_ykc (赞：1)

~~dalao们的题解都看不懂，只好自己来写一篇了~~
## 题目大意
有一个 $4 \times 4$ 的格子，第 $(i, j)$ 个格子需要在 $t_i, _j$ 时刻点击它（如果是点则不需要点击），你的一只手同一时刻可以点击 $k$ 个格子（你有两只手！！！），请问你能否完成任务。

## 思路
同一时刻需要点击的格子数应该 $≤ k \times 2$ 

如果大于，就不能完成任务；

否则，就可以完成；

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int n = 4, N = 25;
int k, cnt[N];
char c[N][N];
int main(){
	cin >> k;
	k = k * 2; // 注意是两只手
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin >> c[i][j];
			if(c[i][j] != '.'){
				cnt[c[i][j] - '0']++; // 统计同一时刻的需要点击的格子数
				if(cnt[c[i][j] - '0'] > k){ // 如果大于
					cout << "NO"; // 不能完成任务
					return 0;
				}
			}
		}
	}
	cout << "YES"; // 可以完成
	return 0;
}
```

---

## 作者：WinterRain208 (赞：1)

CF373A题解

### 题意

有 $16$ 个格子，在 $t_i$ 的时间时你需要点击它。

你一秒内可以点 $k * 2$ 个格子，求你是否能按要求完成点击。

### 做法

来个贪心，再规定的时间按要求去模拟。

如果对于某一刻 $time_i$ , $t_i$ 等于 $time_i$ 的个数比 $k * 2$ 多，那么不行。

否则可以按要求完成。

读入：有题意，数据很小，我们开一个桶记录。

然后遍历一下，判断 $bucket_i > k * 2$ 即可。

### 前置芝士后置介绍

题解有点短，我们介绍一下桶是什么：

当数据范围较小，在内存不超限制下把数据当作下标。

常见应用：

 $n$ 大于 $1e5$ 但 $a_i<=1e7$ 的排序。

记录各个数字 $<=1e7$ 出现的次数。

桶在普及也经常考，比如去年的直播获奖，还有明明的随机数之类的。

在入门者中是一个比较重要的知识。

回到正题，我还加了快读卡常数，也可以开个O2，数据大记得开快读，说不定能骗分。

完结撒花。

### 代码

放代码：

```cpp
#include<bits/stdc++.h>

#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;

int read(){
	long long f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<3)+(x<<1)+s-'0';s=getchar();}
	return x*f;
}

int k,t[10];
char c;
int main(){
	//ios::sync_with_stdio(false);
	scanf("%d",&k),k<<=1;
	F(i,1,25){
		c=getchar();
		if(c!='.')t[c^48]++;
	}
	F(i,1,9)
		if(t[i]>k)puts("NO"),exit(0);
	puts("YES");
	return 0;
}
```
### 题外话

题解不易

点个赞再走吧

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
一共有 $4\times4=16$ 个格子，每个格子 $(i,j)$ 需要在 $t_{i,j}$ 时刻点击（若为星号则不需要点击），你每只手同一时刻只能点击 $k$ 个格子（**注意你有两只手！**），求你是否能完成任务。  
$t_{i,j}$ 是一个 $1-9$ 的数字。
## $\text{Solution}$
水题。  
$4\times4$ 扫一遍，开一个桶记录每个时刻需要点多少个格子，最后判是否有桶超过 $2k$ 即可。
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e6+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m;
int bac[12];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=1;i<=4;i++){
    for(int j=1;j<=4;j++){
      char c;
      scanf(" %c",&c);
      if(c!='.') bac[c-'0']++;//debug("%d\n",c-'0');
    }
  }
  for(int i=1;i<=9;i++){
    if(bac[i]>2*n){
      printf("NO\n");return 0;
    }
  }
  printf("YES\n");
  return 0;
}
/*

*/

```


---

## 作者：int32 (赞：0)

## $\textsf{Description}$

给定 $4\times4$ 的方格，对于格子 $(i,j)$，要在 $t_{i,j}$ 点击它，疫苗最多点 $2k$ 个格子，求是否可以点完。

## $\textsf{Solution}$

用 $n_{x}$ 记录需要在时刻 $x$ 点击的格子数目。

当存在某个时刻 $x$ 时，满足 $n_x>2k$，那么必然输出 $\texttt{NO}$；否则输出 $\texttt{YES}$。

$n$ 数组开个桶记录即可。

## $\textsf{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
int p[15]; //桶
signed main(){
	cin>>k;
	k<<=1; //2k
	getchar(); //读入'\n'
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			char ch=getchar();
			if(ch!='.') ++p[ch-'0']; //不是'.'就统计
		}
		getchar(); //读入'\n'
	}
	for(int i=1;i<=9;i++)
		if(p[i]>k) return puts("NO"),0; //不满足
	puts("YES");
	return 0;
}
```

---

## 作者：阳歌童圣 (赞：0)

一道字符串的统计的~~水~~题
## 题目大意
给你一个数  _k_  ，表示男孩**一只手**能消除**一种数字**的数量，还有一个 4 × 4 的表格，由 ' . '和数字组成，你需要回答男孩一次能否消除掉所有数字。


------------
## 题目分析
显然，男孩有两只手，所以男孩一次能消除 2 ×  _k_  个数字，然后统计出表格中的各种数字的数量，判断是否符合题意。
既然已经有人用了桶，那这次我们就用 map 来写。map 在统计时是极为常用的，还不需要考虑数量，本质上与桶一样，但更为灵活。使用时需开 map 头文件。  
因为表格中还有 ' . ' ，需要将其数量初始值调小，防止出错。
##  _AC代码_ 
```cpp
#include<cstdio>
#include<map>
using namespace std;
char c[4][4];
map<char,int>m;//map 自动开出数组下标为 char 并且出现过的字符的“桶”
int main(){
    int k;
    m['.']=-20;//调小‘.’初始值
    scanf("%d",&k);
    for(int i=1;i<=4;i++)
        scanf("%s",c[i]);//用字符串的方式输入，避免输入为空格的情况
    for(int i=1;i<=4;i++){
        for(int j=0;j<4;j++){
            m[c[i][j]]++;
            if(m[c[i][j]]>k*2){
                return puts("NO") & 0;//& 0 使 return 的值一定为 0
            }
        }
    }return puts("YES") & 0;
}
```


---

## 作者：Allanljx (赞：0)

## 题意
给你 $16$ 个数，每次最多可以消除 $2*k$ 个数，一样的数字必须在同一次消除，问能否将所有数字消除完。

## 思路
模拟，记录每个数出现的次数。因为每个数都在 $1$ ~ $9$ 中，所以我们可以用一个桶来记录每个数出现的次数，最后再去判断，是不是每个数字都能被消除。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int book[11];//桶
int main()
{
	int k;
	cin>>k;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			char a;//字符型方便输入
			cin>>a;
			if(a=='.') continue;
			book[a-'0']++;
		}
	}
	for(int i=0;i<=9;i++)
	{
		if(book[i]>k*2)//判断
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```


---

