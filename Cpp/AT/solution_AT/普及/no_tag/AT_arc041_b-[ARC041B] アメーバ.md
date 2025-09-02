# [ARC041B] アメーバ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc041/tasks/arc041_b

縦 $ N $ マス、横 $ M $ マスの盤面がある。 上から $ i $ ($ 1≦i≦N $) マス目、左から $ j $ ($ 1≦j≦M $) マス目の位置を $ (i,j) $ と表す。

はじめ、マス $ (i,j) $ には $ a_{ij} $ 匹のアメーバがいた。 ただし、盤面の端にアメーバはいなかった。 すなわち、$ i=1,N $ または $ j=1,M $ ならば $ a_{ij}=0 $ である。

高橋君が大声を出すと、アメーバたちは驚いてそれぞれ次の行動をとった。

- $ 1 $ 匹のアメーバが $ 4 $ 匹に分裂し、上下左右のマスへ $ 1 $ 匹ずつ移動した。

その結果、マス $ (i,j) $ には $ b_{ij} $ 匹のアメーバがいることになった。

今のアメーバの配置 $ (b_{ij}) $ が与えられるので、はじめのアメーバの配置 $ (a_{ij}) $ を $ 1 $ つ求めよ。 ただし、$ (a_{ij}) $ は少なくとも $ 1 $ つ存在する。

## 样例 #1

### 输入

```
3 3
010
101
010```

### 输出

```
000
010
000```

## 样例 #2

### 输入

```
3 4
0230
2323
0230```

### 输出

```
0000
0230
0000```

## 样例 #3

### 输入

```
5 5
00100
03040
20903
05060
00300```

### 输出

```
00000
00100
02030
00300
00000```

# 题解

## 作者：wmrqwq (赞：4)

# 题目链接

[题目链接（AT）](https://atcoder.jp/contests/arc041/tasks/arc041_b)

[题目链接（Luogu）](https://www.luogu.com.cn/problem/AT_arc041_b)

# 解题思路

简单贪心，由于每个格子始终不超过 $9$ 个史莱姆，因此对于每四个格子 $a_{i-1,j},a_{i+1,j},a_{i,j-1},a_{i,j+1}$，我们只需要减去 $\min(a_{i-1,j},a_{i+1,j},a_{i,j-1},a_{i,j+1})$ 即可，由于我们是从上往下，从左往右枚举的，所以一开始搜到的一定不是中心点而是边角处，因此这样贪心一定是正确的。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
ll n,m,a[510][510],minn;
int main()
{
	//IOS;
	cin>>n>>m;
	forl(i,1,n)
		forl(j,1,m)
			scanf("%1lld",&a[i][j]);
	forl(i,1,n)
	{
		forl(j,1,m)
			minn=min({a[i-1][j],a[i+1][j],a[i][j-1],a[i][j+1]}),cout<<minn,a[i-1][j]-=minn,a[i+1][j]-=minn,a[i][j-1]-=minn,a[i][j+1]-=minn;
		cout<<endl;
	}
    /******************/
	/*while(L<q[i].l) */
	/*    del(a[L++]);*/
	/*while(L>q[i].l) */
	/*    add(a[--L]);*/
	/*while(R<q[i].r) */
	/*	  add(a[++R]);*/
	/*while(R>q[i].r) */
	/*    del(a[R--]);*/
    /******************/
	QwQ;
}
```

---

## 作者：_32bit_Silentnight (赞：3)

# AT_arc041_b アメーバ题解
## 题目分析
暴力练手题。

利用此题的特性（方阵四周原本没有史莱姆）从 $a_{1,1}$ 枚举到 $a_{n-1,m-1}$，如果 $a_{i,j}$ 有史莱姆，那么 $a_{i+1,j}$ 绝对有史莱姆！！！因此，将 $a_{i,j}$ 设置为 $0$，将 $a_{i+1,j-1},a_{i+1,j+1},a_{i+2,j}$ 各个减 $a_{i,j}$。

### 关于读入

注意！！！两个数字中间没有空格！！

所以，用 ```char``` 二维数组， ```char``` 只能有一个一位数字的占位，所以可以。
## 代码来了
```cpp
#include<bits/stdc++.h>
using namespace std;char a[505][505],b[505][505];//char 二维数组
int main(){
	int i,j,k,m,t;
	memset(b,'0',sizeof(b));//char 数字不 memset 会变为 '\0'，也就是空格，而题目要的是 0。
	cin>>k>>m;
    for(i=1;i<=k;i++)
        for(j=1;j<=m;j++)cin>>a[i][j];
    for(i=1;i<=k;i++)
        for(j=1;j<m;j++)
            if(a[i][j]>'0'){//发现有史莱姆向上分裂的痕迹
			t=a[i][j]-'0';
            	b[i+1][j]=a[i][j];//保存史莱姆的原始状态
            	a[i+2][j]-=t,a[i+1][j-1]-=t;a[i+1][j+1]-=t,a[i][j]=0;//原本的史莱姆，删除！
			}
    for(i=1;i<=k;i++){
        for(j=1;j<=m;j++)cout<<b[i][j];//输出原本矩阵。
        cout<<endl;
	}
}

---

## 作者：Guizy (赞：1)

## 题目大意

翻译很清楚了，不在赘述。

## 思路

我们可以从 $(1,1)$ 到 $(n,m)$ 扫一遍，对于每个 $(i,j)$，这个地方原本的史莱姆数量就是周围四个方向的最小值。算完之后把周围四个方向都减去它们的最小值。

由于我们从上到下，从左到右枚举的特性，我们每次都先枚举到 $(i,j)$ 的四周再枚举到它，所以这个方法正确。

## 实现

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[501][501];
char ch[501][501];

int main(){
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>ch[i][j],a[i][j]=ch[i][j]-48;
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int temp=min({a[i-1][j],a[i][j-1],a[i+1][j],a[i][j+1]});
			printf("%d",temp);
			a[i][j-1]-=temp,a[i-1][j]-=temp,a[i][j+1]-=temp,a[i+1][j]-=temp;
		}puts("");
	}
	
	return 0;
}
```

---

## 作者：Mzaaa (赞：1)

## 题目描述

有一个 $n \times m$ 的地图，上面的的每个点分别向四周扩散。

有扩散完的地图，求扩散前的地图。

## 题目分析

因为题目中的点 $(i,j)$ 向四周扩散，通过样例：
```latex
5 5
00100
03040
20903
05060
00300
```
可以得出  $(i,j)$ 位置的值就是四周的最小值，因为扩散后的值不可能更小。可以得出：

$(i,j)=\min((i+1,j),(i-1,j),(i,j+1),(i,j-1))$ 

同时题目中提到地图边缘都为 $0$，所以我们不用考虑边缘的情况。

## Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 700
long long n,m,a[N][N],ans[N][N],_min;
char c;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		cin>>c,
			a[i][j]=c-'0';
    for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			_min=min(a[i+1][j],min(a[i-1][j],min(a[i][j-1],a[i][j+1])));
			cout<<_min;
    		a[i+1][j]-=_min;
			a[i][j+1]-=_min;
    		a[i-1][j]-=_min;
    		a[i][j-1]-=_min;
		}
		cout<<endl;
	} 
    return 0;
}
```



---

## 作者：So_noSlack (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/AT_arc041_b)&[Atcoder 链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/arc041_b)

本篇题解为此题较**简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给定一个 $N \times M$ 的矩阵，此矩阵的每一个元素都**向上、下、左、右** $4$ 个方向同时扩散（**原来的位置不保留**）。

现给出原矩阵**扩散后的矩阵**，求**原矩阵**。

## 思路

对于扩散后的 $(i,j)$，是**原矩阵**的 $(i-1,j)$，$(i+1,j)$，$(i,j-1)$，$(i,j+1)$ **扩散而来**的，那么就可以**通过这 $4$ 个点推断出原矩阵上 $(i,j)$ 的数**。

例如：

```
010
101
010
```

这个样例中，只有 $(2,2)$ 周围 $4$ 个方向**都是非 $0$ 数**，所以从这个例子中就可推出计算原矩阵上 $(i,j)$ 的数的**方程式**了：

$$(i,j)=\min(\min((i-1,j),(i+1,j),\min((i,j-1),(i,j+1)))$$

那么就会产生一个疑问，对于边界有没有**特殊情况**？比如对于 $(1,1)$ 他的方程式带入就为：

$$(1,1)=\min(\min((0,1),(2,1)),\min((1,0),(1,2)))$$

所以对于**边界** $(0,1)$ 和 $(1,0)$ 的**初始化**就尤为重要，这里**建议初始化为** $0$，这样取 $\min$ 之后就为 $0$ 了。

处理完边界的初始化之后基本就没什么了，不过我们还是要**思考一下**，比如对于以下情况：

```
0000000
0001000
0030400
0209030
0050600
0003000
0000000
```

$(2,3)$ 并**不是**边界并且也**不满足**四周都是非 $0$ 数，那么它是不是一种**特殊情况**？会不会**不满足上面推出的方程式**？答案是肯定的，因为 $(2,3)$ 的上、左两个方向的数是 $0$，则取 $\min$ 之后就**一定**为 $0$ 了。

经过以上分析以及一些证明，基本就有大致的**代码框架**了：

```cpp
#include<iostream>
using namespace std;

int n, m, mp[505][505]; // mp 记录地图
char c; // 临时储存

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i ++) 
		for(int j = 1; j <= m; j ++) {
			cin >> c;
			mp[i][j] = c - '0'; // 转化为数字
		}
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			int minn = min(min(mp[i - 1][j], mp[i + 1][j]), min(mp[i][j - 1], mp[i][j + 1])); // 计算 minn 值
			cout << minn; // 可直接输出
        // 把周围扩散的数减去
			mp[i - 1][j] -= minn; mp[i + 1][j] -= minn; 
			mp[i][j - 1] -= minn; mp[i][j + 1] -= minn;
		}
		cout << endl; // 记得换行
	}
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/117511472)

$$\text{The End!}$$

---

## 作者：xuan_gong_dong (赞：1)

## 题面

[[ARC041B] アメーバ](https://www.luogu.com.cn/problem/AT_arc041_b)

## 分析
对于每一个点，他所分裂的个数与原来一定一样，故初始的个数就是四个方向的最小值，这里要注意到贴着墙的节点一定不会有初始史莱姆。

所以我们可以直接将整个 $n \times m$ 个点枚举一边，该点的答案就是四个方向的最小值，再让四个方向减去这个值就好了

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char c[1000][1000];
int a[1000][1000],ans[1000][1000];;
int nxt[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",c[i]+1);
		for(int j=1;j<=m;j++)a[i][j]=c[i][j]-'0';
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int Min=0x7f7f7f7f;
			for(int k=0;k<4;k++)
			{
				int tx=i+nxt[k][0];
				int ty=j+nxt[k][1];
				Min=min(Min,a[tx][ty]);
			}
			printf("%d",Min);
			for(int k=0;k<4;k++)
			{
				int tx=i+nxt[k][0];
				int ty=j+nxt[k][1];
				a[tx][ty]-=Min;
			}			
		}
		putchar(10);
	}
	return 0;
}
```


---

## 作者：Milthm (赞：0)

## AT_arc041_b 题解

### 前置知识

无

### 题目解法

这题千万不要读错题，问的是你高桥恶臭**之前**的数量。

然后我们思考一下，假设 $i,j$ 之前有个史莱姆，那么之后会分裂成四个。同样的，如果有四个位置 $(i,j-1),(i,j+1),(i-1,j),(i+1,j)$ 在分裂之后都有史莱姆，那么之前肯定 $(i,j)$ 也有史莱姆。那么有多少个呢？明显呢，这里只可能是四个位置的最小值（你不可能 $5$ 个史莱姆只分裂各 $4$ 个吧）。

然后四个位置都减去最小值，记录该位置的答案即可。

### AC 代码

```cpp
#include<iostream>
using namespace std;
int n,m,a[5005][5005],b[5005][5005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%1d",&a[i][j]);//输入可以这样输入
		}
	} 
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(a[i-1][j]&&a[i+1][j]&&a[i][j-1]&&a[i][j+1]){//如果都不是 0
				int p=min(a[i-1][j],min(a[i+1][j],min(a[i][j-1],a[i][j+1])));//取最小值
				a[i-1][j]-=p;
				a[i+1][j]-=p;
				a[i][j-1]-=p;
				a[i][j+1]-=p;
				b[i][j]=p;//记录答案
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cout<<b[i][j];
		}
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：fish_love_cat (赞：0)

作为本题的翻译，当然也有义务贡献篇题解啦。

**思路：**

模拟即可。既然是向四个方向扩散的，那么我们只要向里收缩就能推出原来的地图。显然，原来的点上的史莱姆数量是现在这个点四周的史莱姆数量中的最小值，四周的点都要减去这个最小值。

举例证明：

```
00000
00100
02030
00400
00000
```

~~并不严谨，所以别较真其他的，这里只看 $\sout{(3,3)}$ 上的数字是怎么来的。~~

可以发现，坐标 $(3,3)$ 上的数字可以由 $(2,3)$、$(4,3)$、$(3,2)$、$(3,4)$ 上的史莱姆数量中的**一部分**合并出来，而四周的位置都需要出一样的数量才能合并出来，所以根据[短板原理](https://www.baidu.com/s?ie=UTF-8&wd=%E7%9F%AD%E6%9D%BF%E5%8E%9F%E7%90%86)，四周的最小值就是这个点的值。

所以可得，坐标 $(3,3)$ 上的数字为 $1$。

---

**干净の代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[505][505],b[505][505];
int gx[]={0,0,1,-1};
int gy[]={-1,1,0,0};
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%1d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            int mini=10;
            for(int k=0;k<4;k++)
                mini=min(mini,a[i+gx[k]][j+gy[k]]);//求最小值
            b[i][j]=mini;
            for(int k=0;k<4;k++)
                a[i+gx[k]][j+gy[k]]-=mini;//减去最小值
        }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            cout<<b[i][j];
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：nkrqzjc_zzz (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_arc041_b)

------------
### 题意解析

在一个 $n \times m$ 的表格中，上面的的每个点有一个值这个点会使它上下左右的点加上它的值，而自己则变成零。现在给你一个已经操作完的地图，让你输出操作之前的地图。

**注**：所有地图中的数字为个位数（所以才可以用字符串输入）。

------------

### 思路

因为一次操作后，这个点的值就不再它自己原来的位置了，而即使附近还有一个点有值，也会给其他的位置赋值。简单来说，就是如果一个点在操作之前的值不为 $0$，那它在操作后就一定是在它上下左右中中间最小的。公式如下：

$(x,y)=\min((x,y+1),(x,y-1),(x+1,y),(x-1,y))$

而如果这个点在操作前是 $0$，操作后也一定有至少一个是 $0$ 的点，综上所述，所有的点皆可使用这个公式。

坑点：边缘一定是 $0$，不要像我一样，把边缘情况写完了发现不用特判。在周围的点还需要减去那个点的值，因为一个点可能会被多次操作，要避免找不到后面的答案，删掉四周的对应值。

------------

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long i,j,n,m,a[502][502],d[502][502],x;
string b;
main(){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++){
    	cin>>b;//字符串输入 
    	for(int j=0;j<m;j++)a[i][j+1]=b[j]-'0';
	}
    for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			x=min(a[i][j+1],min(a[i-1][j],min(a[i+1][j],a[i][j-1])));//找最小的点 
    		a[i+1][j]-=x,a[i-1][j]-=x,a[i][j+1]-=x,a[i][j-1]-=x;//减去周围的点 
    		cout<<x;
		}
		puts("");//puts换行永远的神 
	}
}
```

题外话：史莱姆？原神启动！

---

