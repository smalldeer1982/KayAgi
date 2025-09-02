# 「GMOI R2-T1」轴对称

## 题目描述

你有一个 $n$ 行 $m$ 列的图片（矩阵），该图片的像素为 $n\times m$。

初始时，所有像素块均为黑色，RGB 是 $(0,0,0)$。每一次操作可以将一个像素块的 RGB 中的一个数字改变。

在每次操作过后，请你输出图片是否左右对称？

左右对称：即对于任何的 $i,j$，总满足第 $i$ 行第 $j$ 列的像素与第 $i$ 行第 $m-j+1$ 列的像素的 RGB 值相等。 

## 说明/提示

**本题使用 Subtask 捆绑测试。**

| Subtask | $n\le$ | $m\le$ | $q\le$ | $t\le$ | $c\le$ | 对应测试点 | 总分 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $10$ | $2$ | $50$ | $1$ | $255$ | $1\sim2$ | $10$ |
| $1$ | $100$ | $2$ | $500$ | $3$ | $10^9$ | $3\sim4$ | $15$ |
| $2$ | $100$ | $100$ | $500$ | $3$ | $10^9$ | $5\sim6$ | $15$ |
| $3$ | $100$ | $100$ | $1$ | $3$ | $10^9$ | $7\sim9$ | $15$ |
| $4$ | $100$ | $100$ | $500$ | $3$ | $10^9$ | $10\sim12$ | $45$ |

**对于 Subtask 2**，保证每个变量等概率随机生成。

对于 $100\%$ 的数据，$1\le n,m\le 100$，$1\le q\le 500$，$1\le i\le n$，$1\le j\le m$，$t\in \{1,2,3\}$，$1\le c\le 10^9$。

## 样例 #1

### 输入

```
6 6 9
1 2 3 4
5 6 3 4
1 5 3 4
5 1 3 4
1 3 2 260
1 4 2 4
2 2 3 5
2 5 3 7
2 2 3 258```

### 输出

```
No
No
No
Yes
No
Yes
No
No
Yes```

# 题解

## 作者：Nuyoah_awa (赞：12)

### 题目大意
给定一个 $n \times m$ 的矩阵，每个点有三个值，每次操作可将一个点的一个值改变，在每次操作过后，请你输出图片是否左右对称？

### 题目分析

我们可以按照题目要求每次更改一个数，再看是否对称。

时间复杂度 $\mathcal O(q \times n \times m)$。

我们发现，每回只改一个值，所以我们可以记一个 $cnt$ 表示矩阵共有 $cnt$ 对点左右不对称，每次更改一个数后有如下四种情况：

1. 原来这个点对称，后来这个点依旧对称（改了跟没改一样）：$cnt$ 不变。
2. 原来这个点对称，后来这个点不对称（改不对称了）：$cnt + 1$。
3. 原来这个点不对称，后来这个点依不旧对称（好像改了，但是没完全改）：$cnt$ 不变。
4. 原来这个点不对称，后来这个点对称（改对称了）：$cnt-1$。

每次改完后，如果 $cnt = 0$ 即没有点不对称，输出 `Yes`。

否则说明有点不对称，输出 `No`。

### code
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 105, MOD = 256;
struct node{
	int a[4];
}p[N][N];
int n, m, q, x, y, t, c, cnt;

bool operator == (node u, node v)
{
	for(int i = 1;i <= 3;i++)
		if(u.a[i] != v.a[i])
			return false;
	return true;
}

int main()
{
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1;i <= q;i++)
	{
		scanf("%d %d %d %d", &x, &y, &t, &c);
		if(p[x][y].a[t] == p[x][m - y + 1].a[t])
		{
			(p[x][y].a[t] += c) %= MOD;
			cnt += (p[x][y].a[t] == p[x][m - y + 1].a[t]) ? 0 : 1;
		}
		else
		{
			(p[x][y].a[t] += c) %= MOD;
			cnt += (p[x][y].a[t] == p[x][m - y + 1].a[t]) ? -1 : 0;
		}
		(cnt == 0) ? printf("Yes\n") : printf("No\n");
	}
	return 0;
}
```

---

## 作者：yinhy09 (赞：11)

## 官方题解

### 题意

一个 $n\times m$ 的矩阵，每一次操作可以改变一个格子的颜色，在每一次操作后输出图片是否对称。

### 题外话

这个题本来是 $n,m\le 10^9$，$q\le 5\times 10^5$ 的，因为~~不想被扣钱~~月赛要求通过率，所以削弱了。

### 本题正解

用个结构体存一下每个点。对于每次询问，暴力更改一个点，然后 $O(nm)$ 进行比较，找出左右是否对称。

### 标准版正解

定义一个变量 $d$，初始为 $0$，表示左右侧不对称的块的对数。

因为 $n,m\le 10^9$，所以不可能用数组存储。但又注意到最多会更改 $5\times 10^5$ 个格子，所以考虑用 map 记录。

在每一次修改前，判断被修改点和对应点是否相同：

- 相同：若修改后不同，$d+1\to d$，否则不变。

- 不同：若修改后相同，$d-1\to d$，否则不变。

修改过后，判断 $d$ 是否等于 $0$，如果是，输出 `Yes`，否则输出 `No`。

---

## 作者：what_can_I_do (赞：8)

[传送门](https://www.luogu.com.cn/problem/P9198)

[激励计划](https://www.luogu.com.cn/discuss/728989)好闪，拜谢激励计划。

先定义一个图片数组 $a_{i,j,k}$，表示第 $i$ 行第 $j$ 列的 RGB 中第 $k$ 个数为几。

接下来对于每一次操作只需要将 $a_{i,j,t}$ 加上 $c$ 并对 $256$ 取模就行了。

判断是否轴对称也不难，只需要枚举每一行判断该行是否满足第 $j$ 列中 RGB 元素与第 $m-j+1$ 列完全相同就行，如果有不同就让 $f=0$ 并退出循环，否则让 $f$ 会一直为 $1$。最后再判断 $f$ 是否为 $1$ 就行，为 $1$ 就说明是轴对称，否则不是。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[110][110][4]={0},q;
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	while(q--)
	{
		int x,y,t,c,f=1;
		scanf("%d%d%d%d",&x,&y,&t,&c);
		c%=256,a[x][y][t]+=c,a[x][y][t]%=256;
		for(register int i=1;i<=n;i++)
		{
			for(register int j=1;j<=m;j++)
			{
				for(register int k=1;k<=3;k++)
					if(a[i][m-j+1][k]!=a[i][j][k]){f=0;break;}
				if(!f) break;
			}
			if(!f) break;
		}
		if(!f) puts("No");
		else puts("Yes");
	}
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：3)

# P9198 「GMOI R2-T1」轴对称 题解

简单的模拟题。

由于这道题数据小，每次读入之后判断是否对称都不会超时。

### 解析

按题目模拟即可，注意读入时要对所有数取模 $256$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 256
int n,m,q;
int x,y,t,c;
struct square{ //每一个像素块所包含的信息 
	int r,g,b;
}sq[105][105];
bool flag;
bool check(){
	if(m%2==0){ //列数为偶数 
		for(int j=1;j<=m/2;j++){
			for(int i=1;i<=n;i++){
				if(sq[i][j].r==sq[i][m+1-j].r&&sq[i][j].g==sq[i][m+1-j].g&&sq[i][j].b==sq[i][m+1-j].b){
					continue;
				}
				else{
					return false;
				}
			}
		}
		return true;
	}
	else{ //列数为奇数 
		for(int j=1;j<=(m-1)/2;j++){
			for(int i=1;i<=n;i++){
				if(sq[i][j].r==sq[i][m+1-j].r&&sq[i][j].g==sq[i][m+1-j].g&&sq[i][j].b==sq[i][m+1-j].b){
					continue;
				}
				else{
					return false;
				}
			}
		}
		return true;
	}
}
int main(){
	ios::sync_with_stdio(0); //读写加速
	cin>>n>>m>>q; 
	while(q--){
		cin>>x>>y>>t>>c;
		switch(t){ //修改 
			case 1:sq[x][y].r+=c; sq[x][y].r%=mod; break;
			case 2:sq[x][y].g+=c; sq[x][y].g%=mod; break;
			case 3:sq[x][y].b+=c; sq[x][y].b%=mod; break;
		}
		if(check()){ //判断是否对称 
			printf("Yes\n");
		}
		else{
			printf("No\n");
		}
	}
return 0;
} 
```


---

## 作者：ncwzdlsd (赞：2)

分别记录每个格子的 RGB 值，然后对于每一次修改，都暴力判断一下 $(a,b,c)_{i,j}$ 是否等于 $(a,b,c)_{i,m-j+1}$ 即可。

时间复杂度 $O(mnq)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod=256;
int a[105][105],b[105][105],c[105][105],n,m;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

inline bool check()
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(a[i][j]!=a[i][m-j+1]||b[i][j]!=b[i][m-j+1]||c[i][j]!=c[i][m-j+1])
				return 0;
	return 1;
}

int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int q;n=read(),m=read(),q=read();
	while(q--)
	{
		int i=read(),j=read(),t=read(),cc=read();
		if(t==1) a[i][j]=(a[i][j]+cc)%mod;
		else if(t==2) b[i][j]=(b[i][j]+cc)%mod;
		else c[i][j]=(c[i][j]+cc)%mod;
		if(check()) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：ivyjiao (赞：2)

### 15 分：

```
while(q--) puts("No");
```
### 100 分：

对于每次询问，暴力修改及时取模，每次暴力判断是否左右对称即可。

至于左右对称的定义，题目中已经给了。

时间复杂度 $O(qnm)$。

代码：

```
#include<iostream>
using namespace std;
int n,m,q,x,y,t,c;
int a[1001][1001][4];
int main(){
    cin>>n>>m>>q;
    while(q--){
        cin>>x>>y>>t>>c;
        a[x][y][t]+=c;
        a[x][y][t]%=256;
        bool boo=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i][j][1]!=a[i][m-j+1][1]||a[i][j][2]!=a[i][m-j+1][2]||a[i][j][3]!=a[i][m-j+1][3]){
                    boo=1;
                }
            }
        }
        if(!boo) puts("Yes");
        else puts("No");
    }
}
```

---

## 作者：Magus (赞：1)

感谢激励计划。

简单模拟题。

用一个三维数组 $arr$ 表示图片，第一个数和第二个数表示坐标，第三个数表示 RGB。

随后根据题意模拟即可。

需要注意的是，题目中需要输入的 $i,j$ 可能与循环变量重名。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+10;
const int mod=256;//任何一个 RGB 值的任何一个数如果超出 255 则自动对 256 取模。
int n,m,q,i,j,t,c,arr[maxn][maxn][10];
int main()
{
	cin>>n>>m>>q;
	for(int a=1;a<=q;a++)//防止重名
	{
		int flag=0;
		cin>>i>>j>>t>>c;
		arr[i][j][t]+=c;
		arr[i][j][t]%=mod;
		for(int b=1;b<=n;b++)
		{
			for(int c=1;c<=m;c++)
			{
				if(arr[b][c][1]!=arr[b][m-c+1][1] or arr[b][c][2]!=arr[b][m-c+1][2] or arr[b][c][3]!=arr[b][m-c+1][3])//判断是否对称
				{
					flag=1;//如果不对称则直接输出 No 然后 break
					cout<<"No\n";
					break;
				}
			}
			if(flag==1)
			{
				break;
			}
		}
		if(flag==0)
		{
			cout<<"Yes\n";//对称输出 Yes
		}
	}
    防作弊
	return 0;
}
```

求管理大大给过。

---

## 作者：wzb13958817049 (赞：1)

# 思路
纯模拟，每一次改一个值，在重新跑一遍矩阵判断是否轴对称，时间复杂度 $O(n \cdot m \cdot q)$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,q,x,y,t,c;
struct data{long long r,g,b;}a[105][105];//结构体
bool pd(){//判断矩阵是否轴对称
	for(int i=1;i<=n;i++){
		for(int j=1;j<=(m+1)/2;j++){//(m+1)/2是为了避免m为奇数的情况下中间那一列没有判断
			if(a[i][j].r!=a[i][m-j+1].r) return false;//如果不同则直接返回false
			if(a[i][j].g!=a[i][m-j+1].g) return false;
			if(a[i][j].b!=a[i][m-j+1].b) return false;
		}
	}
	return true;//轴对称返回true
}
int main(){
	ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++){
		cin>>x>>y>>t>>c;
		if(t==1) a[x][y].r=(a[x][y].r+c)%256;
		if(t==2) a[x][y].g=(a[x][y].g+c)%256;
		if(t==3) a[x][y].b=(a[x][y].b+c)%256;
		if(pd()==true) cout<<"Yes\n";//如果轴对称输出Yes
		else cout<<"No\n";//否则输出No
	}
	return 0;
}
```


---

## 作者：Eason_cyx (赞：0)

简单题。直接模拟即可。

用三个二维数组来存就可以了啊。

判断对称？题目中已经告诉你了，枚举判断 $a_{i,j},b_{i,j},c_{i,j}$ 是否等于 $a_{i,m-j+1},b_{i,m-j+1},c_{i,m-j+1}$ 即可。

时间复杂度 $O(qnm)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105][105],b[105][105],c[105][105],n,m;
bool chk() {
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= m;j++) {
            if(a[i][j] != a[i][m-j+1] || b[i][j] != b[i][m-j+1]  || c[i][j] != c[i][m-j+1]) {
                return false;
            }
        }
    }
    return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int q; cin >> n >> m >> q;
    while(q--) {
        int i,j,t,q;
        cin >> i >> j >> t >> q;
        if(t == 1) {
            a[i][j] = (a[i][j] + q) % 256;
        }
        if(t == 2) {
            b[i][j] = (b[i][j] + q) % 256;
        }
        if(t == 3) {
            c[i][j] = (c[i][j] + q) % 256;
        }
        if(chk()) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```

---

