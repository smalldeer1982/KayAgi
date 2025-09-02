# [USACO25OPEN] Hoof Paper Scissors Minus One B

## 题目描述

在一局蹄子剪刀布游戏中，Bessie 和 Elsie 可以出 $N$ （$1 \leq N \leq 3000$）种不同的蹄子手势，编号为 $1\dots N$，每个手势对应一种不同的材料。不同材料之间的相互关系有一个复杂的表格，基于该表格，可能会：

- 一种手势获胜，另一种失败。
- 两种手势平局。

蹄子剪刀布-1.0 的规则类似，但 Bessie 和 Elsie 可以各自出两个手势，每只蹄子出一个。在观察到她们所出的四个手势后，她们各自选择其中一个手势进行游戏。结果根据正常的蹄子剪刀布的规则决定。

给定 Elsie 计划在每局游戏中出的 $M$（$1 \leq M \leq 3000$）个手势组合，Bessie 想知道有多少种不同的手势组合可以确保战胜 Elsie。一个手势组合定义为一个有序对 $(L,R)$，其中 $L$ 为奶牛用左蹄出的手势，$R$ 为奶牛用右蹄出的手势。你能为每局游戏进行计算吗？

## 说明/提示

在样例 1 解释：这对应于原始的蹄子剪刀布，我们可以设蹄子为 $1$，布为 $2$，剪刀为 $3$。布战胜蹄子，蹄子战胜剪刀，剪刀战胜布。Bessie 无法确保战胜蹄子 + 布或布 + 剪刀的组合。然而，如果 Elsie 出蹄子 + 蹄子，Bessie 可以采用以下任一组合进行反击。

- 布 + 布
- 布 + 剪刀
- 布 + 蹄子
- 蹄子 + 布
- 剪刀 + 布

如果 Bessie 出这些组合中的任意一个，她可以确保通过出布来获胜。

- 测试点 $2\sim 6$：$N,M\le 100$。

- 测试点 $7\sim 12$：没有额外限制。

## 样例 #1

### 输入

```
3 3
D
WD
LWD
1 2
2 3
1 1```

### 输出

```
0
0
5```

# 题解

## 作者：CSP_S_2023_T2 (赞：4)

### 思路

容易发现：如果 Bessie 要确保战胜 Elsie，当且仅当 Bessie 出的手势组合中至少有一个手势能够同时战胜 Elsie 手势组合中的所有手势。

不然，无论 Bessie 出哪个手势，Elsie 总有至少一个手势满足 Bessie 不能战胜 Elsie。

所以，对于 Elsie 计划出的每一个手势组合 $(L,R)$，我们需要枚举能同时战胜 $L$ 和 $R$ 的手势个数，记为 $ans$。

每一个能够同时战胜 $L$ 和 $R$ 的手势，都可以与所有手势进行搭配。注意到 $(L,R)$ 和 $(R,L)$ 算两种组合，所以满足要求的手势组合数量为 $ans \times n \times 2$。

但是，任意两个（可以相同）满足要求的手势的组合，都被统计了两次，所以答案应该减去 $ans \times ans$。

综上，答案即为 $ans \times (n \times 2-ans)$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,r;
bool a[3005][3005];   //胜：1 败或平：0 
string s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=1;j<=i;j++){
			if(s[j-1]=='W') a[i][j]=1;      //i 能战胜 j
			if(s[j-1]=='L') a[j][i]=1;      //j 能战胜 i
		}
	}
	while(m--){
		cin>>l>>r;
		int ans=0;
		for(int i=1;i<=n;i++){
			if(a[i][l]&&a[i][r]) ans++;     //统计能同时战胜 L 和 R 的手势个数
		}
		cout<<ans*(n*2-ans)<<'\n';          //输出答案
	}
	return 0;  //完结撒花
}
```

---

## 作者：hwc2011 (赞：2)

小时候经常玩的游戏，竟然被做进 USACO 了。\
因为想要必胜，出的两个手势中，必须有一个手势是可以击败对手两个手势的，所以本题需要先通过输赢的相反性找到所有手势可以战胜的手势，然后再找到可以同时战胜对手两个手势的手势，设其数量为 $c$，由于它可以和任何 $n$ 个手势搭配，而且两个手势可以互换左右蹄，所以总共有 $2nc$ 种情况，因为都可以同时战胜对手两个手势的手势之间的方案数被计算了两次，所以总共多计算了 $c^2$ 次，除去重复的方案数后总共有 $c(2n-c)$ 种方案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3+5;
int n,m,b[N][N],f,s;
char a[N][N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=i;j++){
		cin>>a[i][j];
		if(a[i][j]=='W') b[i][j]=1;
		if(a[i][j]=='L') b[j][i]=1; 
	}
	while(m--){
		cin>>f>>s;
		int c=0;
		for(int i=1;i<=n;i++) c+=(b[i][f]>0&&b[i][s]>0);
		cout<<c*(2*n-c)<<'\n';
	} 
}
```

---

## 作者：封禁用户 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P12022)
## 声明
本题解纯原创，禁止抄袭代码，将用样例。
```PHP
3 3
D
WD
LWD
1 2
2 3
1 1
```
举例说明。
## 想法
首先，看一下这道题的数据范围 $1\le N\le 3000$。$N$ 行，第 $i$ 行由 $i$ 个字符组成，所以要开一个大小为 $3000^2$ 的二维数组。
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[3010][3010];
```
紧接着是输入。
```cpp
int n,m;
cin>>n>>m;
for(int i=1;i<=n;i++)
{
  for(int j=1;j<=i;j++)
  {
    cin>>a[i][j];
    if(a[i][j]=='W')a[j][i]='L';
    else if(a[i][j]=='L')a[j][i]='W';
    else a[j][i]='D';
  }
}
```
此时的数组是。
```PHP
D L W
W D L
L W D
```
然后有 $M$ 行，每行包含两个空格分隔的整数 $s_1$ 和 $s_2$，$1\le s1,s2\le N$。
```cpp
for(int i=1;i<=m;i++)
  {
    int s1,s2;
    cin>>s1>>s2;
```
如果想要保证赢，就要使己方的某动作能赢对方的两个动作，即。
```cpp
a[j][s1]=='W'&&a[j][s2]=='W'
```
如果符合条件，把所有含有第 $j$ 个动作的组合枚举出来。设第 $k$ 个符合要件的我们称其为 $j_k$。$j_1$ 作为第一个动作时有 $n$ 个，作为第二个动作时也有 $n$ 个，去除 $a_{j_1,j_1}$ 总共有 $2n-1$ 个。下一个就多排除 $a_{j_1,j_2}$ 和 $a_{j_2,j_1}$ 两个，就是 $2n-3$...第 $k$ 个就是 $2n-(2k-1)=2n-2k+1$ 个，所以：
```cpp
int ans=0,now=2*n-1;
```
一旦到符合条件的就。
```cpp
ans+=now;
now-=2;
```
最后输出结果。
```cpp
  cout<<ans<<endl;
}
```
结合一下。
```cpp
for(int i=1;i<=m;i++)
  {
    int s1,s2;
    int ans=0,now=2*n-1;
    cin>>s1>>s2;
    for(int j=1;j<=n;j++)
      {
          if(a[j][s1]=='W'&&a[j][s2]=='W')
          {
              ans+=now;
              now-=2;
          }
      }
    cout<<ans<<endl;
  }
```
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[3010][3010];
int main()
{
  int n,m;
  cin>>n>>m;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=i;j++)
    {
      cin>>a[i][j];
      if(a[i][j]=='W')a[j][i]='L';
      else if(a[i][j]=='L')a[j][i]='W';
      else a[j][i]='D';
    }
  }
  for(int i=1;i<=m;i++)
    {
      int s1,s2;
      int ans=0,now=2*n-1;
      cin>>s1>>s2;
      for(int j=1;j<=n;j++)
        {
            if(a[j][s1]=='W'&&a[j][s2]=='W')
            {
                ans+=now;
                now-=2;
            }
        }
      cout<<ans<<endl;
    }
  return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/213050796)。

---

## 作者：htl2025 (赞：1)

## 题意简述
给定各个手势之间的胜负关系，Bessie 需要确保能选择一个手势击败对方，题目要求方案总数。

## 方法

无论 Bessie 出哪个手势，Elsie 总有至少一个手势满足 Bessie 不能战胜 Elsie。

对于 Elsie 计划出的每一个手势组合 ($L$,$R$)，枚举同时记战胜 $L$ 和 $R$ 的手势个数，记为 $res$。

能够同时战胜 $L$ 和 $R$ 的手势，要与所有手势进行搭配。注意： ($L$,$R$) 和 ($R$,$L$) 算 $2$ 种组合，所以满足要求的手势组合数量为 $res\times N\times2$。

满足要求的手势的组合，都被统计了两次，所以答案应该减去 $res\times res$。

答案为： $res\times (N\times2−res)$。

接下来输出答案就行了。

```cpp
#include<bits/stdc++.h>
#define QiuGuo return
#define I using
#define AK namespace
#define IOI std
I AK IOI;
int n,m,l,r;
string str;
bool s[3010][3010];
//s[i][j] 表示 i 是否能战胜 j ，能1，不能2 
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>str;
		for(int j=1;j<=i;j++)
		{
			if(str[j-1]=='L') s[j][i]=1;
			if(str[j-1]=='W') s[i][j]=1;
		}
	}
	while(m--)
	{
		cin>>l>>r;
		int res=0,ans;
		for(int i=1;i<=n;i++)
			if(s[i][l]==1&&s[i][r]==1) res++;
		ans=(2*n-res)*res;
		cout<<ans<<'\n';
	}
	QiuGuo 0;// 完结求过 
}
```

---

## 作者：IcyDragon (赞：1)

## 思路

每次询问时先求出有多少种手势能同时战胜 Elsie 的两种手势，记为 $c$，然后枚举每种手势作为 Bessie 左手上的手势，并分两种情况统计答案：

1. 这种手势能同时战胜 Elsie 的两种手势，此时将答案增加 $N$，因为无论 Bessie 右手选哪种手势，她都能用左手的手势战胜 Elsie。
2. 这种手势不能同时战胜 Elsie 的两种手势，此时将答案增加 $c$，因为只有 Bessie 右手选则这 $c$ 种能同时战胜 Elsie 的手势，她才能用右手的手势战胜 Elsie。

接下来输出答案就行了。

## 代码

```cpp
#include<iostream>
using namespace std;

bool a[3100][3100];
//a[i][j] 表示 i 是否能战胜 j

int main(){
	int n,m,x,y;
	char t;
	cin>>n>>m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= i; j++){
			cin>>t;
			if(t == 'D'){
				continue;
			}
			if(t == 'W'){
				a[i][j] = 1;
			}else{
				a[j][i] = 1;
			}
		}
	}
	int c,ans;
	//c 如上文所述，ans 为答案
	while(m--){
		cin>>x>>y;
		c = 0;
		//统计有多少种手势能同时战胜 Elsie 的两种手势
		for(int i = 1; i <= n; i++){
			if(a[i][x] && a[i][y]){
				c++;
			}
		}
		ans = 0;
		for(int i = 1; i <= n; i++){
			if(a[i][x] && a[i][y]){
				//第一种情况
				ans += n;
			}else{
				//第二种情况
				ans += c;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

Bessie 和 Elsie 在玩一个变种的石头剪刀布游戏。她们各自出两个手势，然后选择其中一个进行对决。Bessie 需要确保无论 Elsie 选择哪一个手势，自己都能选择一个手势击败对方。题目要求计算 Bessie 有多少种手势组合满足这一条件。

---

首先读取手势胜负关系表，构建每个手势能击败的所有手势的集合。

对于每个查询，找到能同时击败 Elsie 两个手势的集合 $C$。Bessie 的两个手势中至少有一个属于 $C$ 时，才能确保胜利。

计算属于 $C$ 的手势数目 $cnt$，有效组合数为 $cnt \times (2 \times N - cnt)$，其中 $N$ 为手势总数。


## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3001;
bitset<MAXN> b[MAXN];

int main() {
	int N, M;
	cin >> N >> M;
	
	for (int i = 1; i <= N; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= i; ++j) {
			char c = s[j-1];
			if (c == 'W') {
				b[j].set(i); // i输给j
			} else if (c == 'L') {
				b[i].set(j); // j输给i
			}
		}
	}
	
	while (M--) {
		int s1, s2;
		cin >> s1 >> s2;
		auto ans = b[s1] & b[s2];
		int cnt = ans.count();
		cout << cnt * (2LL * N - cnt) << '\n';
	}
	
	return 0;
}
```

---

## 作者：littlewhite_ (赞：0)

# 题目分析：

解题要点如下：

1. 绘制胜负判断表。

2. 判断多少种手势可保证必赢。

## Step 1

由于 $1 \le N \le 3000$，所以二维数组放心开就好啦。

初始状态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/yq0l2tmz.png)

根据输入，直接一次性把整张表绘制好不可能，需要自己填充剩余部分。

我们用 $1$ 表示会赢，用 $0$ 表示会平，用 $-1$ 表示会输。

以样例为例，输入的是这样的表格：

![](https://cdn.luogu.com.cn/upload/image_hosting/zbcw4ftk.png)

可以看出 Bessie 用 $1$ 手势能打败 $2$ 手势，那么用 $2$ 手势就会输给$1$手势。

同理，Bessie 用 $1$ 手势会输给 $3$ 手势，那么用 $3$ 手势就能打败 $1$ 手势。

所以这时候表格就填完了：

![](https://cdn.luogu.com.cn/upload/image_hosting/evpwktyz.png)


```cpp
for(int i=1;i<=n;i++)
    {
        char t[N];
        scanf("%s",t+1);
        for(int j=1;j<=i;j++)
        {
            if(t[j]=='W')
            {
                a[i][j]=1;
                a[j][i]=-1;
            }
            else if(t[j]=='L')
            {
                a[i][j]=-1;
                a[j][i]=1;
            }
            else 
            {
                a[i][j]=0;
                a[j][i]=0;
            }
        }
    }
```


## Step 2

由于 $1 \le M,N \le 3000$ ，所以直接遍历也是没问题的！

所以遍历 $n$ 次一一判断并统计就好，判断条件就是这种手势都能打败 Elsie 的左右手。 


```cpp
for(int i=1;i<=n;i++) if(a[i][l]==1&&a[i][r]==1) ans++;
```


但这里答案的输出**要注意**。

以样例的第三个点为例，这时 Elsie 的左右手都为手势 $1$。

根据上表，用手势 $3$ 就可获胜。

但是 Bessie **不一定**都用手势 $3$。

那答案是多少？

根据乘法原理，两只手各有 $3$ 种可选择的手势，共有 $$3 × 3 = 9$$ 种方案。

又根据加法原理，这 $9$ 种方案分为可行与不行两种。

所以只要再求出不可行的方案数即可。

因为求不可行的方案，所以手势 $3$ 不能选。

所以每只手就有 $$3 - 1 = 2$$ 种可选择的手势。

根据乘法原理，两只手各有 $2$ 种可选择的手势，共有 $$2 \times 2 = 4$$ 种不可行方案。

所以答案为 $$9 - 4 = 5$$。

按照以上方法推导，答案就为：

```
n*n-(n-ans)*(n-ans)
```
# AC代码


```cpp
#include<cstdio>
#define N 3005
using namespace std;
int n,m,a[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        char t[N];
        scanf("%s",t+1);
        for(int j=1;j<=i;j++)
        {
            if(t[j]=='W')
            {
                a[i][j]=1;
                a[j][i]=-1;
            }
            else if(t[j]=='L')
            {
                a[i][j]=-1;
                a[j][i]=1;
            }
            else 
            {
                a[i][j]=0;
                a[j][i]=0;
            }
        }
    }
    while(m--)
    {
        int l,r,ans=0;
        scanf("%d %d",&l,&r);
        for(int i=1;i<=n;i++) if(a[i][l]==1&&a[i][r]==1) ans++;
        printf("%d\n",n*n-(n-ans)*(n-ans));
    }
    return 0;
}
```

---

## 作者：qW__Wp (赞：0)

显然若一个组合 $(x_1,y_1)$ 必能打败 $(x_2,y_2)$，必然满足 **$x_1$ 或 $y_1$ 中的一个**能把 $x_2$ 和 $y_2$ **都打败**。对于每次查询，统计出能够把 $x_2$ 和 $y_2$ 都打败的手势数量 $sum$，则这 $sum$ 中的每一个手势和其他任一手势组合都能成为答案，共有 $sum \times N \times 2$ 种组合。

但是这样会有重复的情况。对于 $sum$ 中的某个手势 $i$ 和另一个手势 $j$，组合 $(i,j)$ 被计算了两次。总共重复计算了 $sum ^ 2$ 种情况。

综上，答案为 $sum \times N \times 2 - sum ^ 2$。

```C++
#include <bits/stdc++.h>

using namespace std;

const int N = 3005;

bool win[N][N];

signed main() {
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= i; j ++) {
			char c; cin >> c;
			if (c == 'W') win[i][j] = 1;
			else if (c == 'L') win[j][i] = 1;
		}
	}
	while (m --) {
		int x, y; cin >> x >> y;
		int res = 0;
		for (int i = 1; i <= n; i ++) {
			if (win[i][x] && win[i][y]) res ++;
		}
		cout << res * n * 2 - res * res << endl;
	}
	return 0;
}
```

---

## 作者：蒟蒻whker (赞：0)

简单题。写篇题解来挽救我的咕值。
## 方法简述
很难不想到将两种手势之间的胜负情况用一个二维数组存储，$a_{i,j}$ 表示第 $i$ 种手势和第 $j$ 种手势之间的胜负。   
接着由题意可得只要 Bessie 出的任意一个手势可以**同时打败**对方的两个手势，即可获胜。因此，枚举 $N$ 个手势，满足上述条件就记录答案 $sum$。  
枚举完后发现可能有重复，发现答案等于总数减去不满足条件的方案数。注意到奶牛有两只蹄子，所以两者都要是平方倍。因此答案是 $N^{2}-(N-sum)^{2}$。最后输出即可。

可以看代码注释辅助理解。
## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[3005][3005];//用数组存胜负关系
int main() {
	int n,m;
	cin>>n>>m;
	for (int i=1;i<=n;++i) {
		for (int j=1;j<=i;++j) {
			cin>>a[i][j];
			if (a[i][j]=='W')a[j][i]='L';//题目只给了一半，要推出另一半
			else if (a[i][j]=='L')a[j][i]='W';//a[i][j]和a[j][i]相反
			else a[j][i]='D';//平局不变
		}
	}
	while (m--) {
		int s1, s2;
		cin>>s1>>s2;
		int cnt=0;//计数器记得设为0
		for (int i=1;i<=n;++i) {//枚举n个手势
			if (a[i][s1]=='W'&&a[i][s2]=='W') ++cnt;//如果可以同时打败对方的两个手势就增加答案
		}
		cout<<n*n-(n-cnt)*(n-cnt)<<'\n';//求出答案
	}
	return 0;//完结撒花
}
```

The end.

---

## 作者：Tiger_Rory (赞：0)

## 题意简述

给定各个手势之间的胜负关系，求在对方出两个手势时出至少一个可以同时至少打平这两个手势的方案数。

## 解题思路

令可以打败或打平某个手势的手势为其“上级手势”，则我们考虑存储每个手势对应的若干个“上级手势”，预先排序，随后在询问时遍历每个手势，二分查找判断出当前手势是否可以同时打败给出的两个手势。统计答案时容易发现只要使用了满足上述要求的手势就能确保获胜，所以另一个手势是任意的，对于每个满足要求的手势都有 $2\times N-1$ 种搭配方案（同个手势出两个只会产生一种方案），直接做乘法统计。

但我们又注意到如果两个手势 $i$ 和 $j$ 都是满足条件的，那么计算答案时会把 $i,j$ 和 $j,i$ 都给统计两遍，所以要再扣除这种情况。然后就可以通过本题。

## 参考代码


```cpp
#include<bits/stdc++.h>
#define int long long
//很重要！！！
#define pb push_back
using namespace std;
int n,m; 
const int N=3005; 
char opt[N][N];
vector<int>w[N],ans;  
signed main() {
	cin.tie(0)->sync_with_stdio(0);cout.tie(0);
	cin>>n>>m; 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			cin>>opt[i][j]; 
			if(opt[i][j]=='L')w[i].pb(j); 
			else if(opt[i][j]=='W')w[j].pb(i);     
		}
	}
	for(int i=1;i<=n;i++)sort(w[i].begin(),w[i].end()); //排序 
	while(m--){
		int s1,s2;cin>>s1>>s2; 
		for(int i=1;i<=n;i++){
			if(binary_search(w[s1].begin(),w[s1].end(),i)&&binary_search(w[s2].begin(),w[s2].end(),i)) ans.pb(i); 
			//二分查找判断手势是否满足条件  
		}
		if(!ans.size()) {
			cout<<0<<'\n'; continue; 
			//没有手势满足条件 
		}
		int tmp=ans.size();//满足条件手势个数 
		int sum=tmp+tmp*(n-1)*2;//第一遍乘法    
		sum-=tmp*(tmp-1);//扣除多次计算的部分 
		cout<<sum<<'\n';
		ans.clear();//多测要清空  
	}
	return 0;
}

```

---

