# Corners

## 题目描述

You are given a matrix consisting of $ n $ rows and $ m $ columns. Each cell of this matrix contains $ 0 $ or $ 1 $ .

Let's call a square of size $ 2 \times 2 $ without one corner cell an L-shape figure. In one operation you can take one L-shape figure, with at least one cell containing $ 1 $ and replace all numbers in it with zeroes.

Find the maximum number of operations that you can do with the given matrix.

## 说明/提示

In the first testcase one of the optimal sequences of operations is the following (bold font shows l-shape figure on which operation was performed):

- Matrix before any operation was performed:  101111011110
- Matrix after $ 1 $ operation was performed:  100101011110
- Matrix after $ 2 $ operations were performed:  100100011110
- Matrix after $ 3 $ operations were performed:  100100010110
- Matrix after $ 4 $ operations were performed:  100000010110
- Matrix after $ 5 $ operations were performed:  100000010100
- Matrix after $ 6 $ operations were performed:  100000000100
- Matrix after $ 7 $ operations were performed:  000000000100
- Matrix after $ 8 $ operations were performed:  000000000000

In the third testcase from the sample we can not perform any operation because the matrix doesn't contain any ones.

In the fourth testcase it does not matter which L-shape figure we pick in our first operation. We will always be left with single one. So we will perform $ 2 $ operations.

## 样例 #1

### 输入

```
4
4 3
101
111
011
110
3 4
1110
0111
0111
2 2
00
00
2 2
11
11```

### 输出

```
8
9
0
2```

# 题解

## 作者：liangbowen (赞：26)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1720C)

[更好的阅读体验？](https://liangbowen.blog.luogu.org/solution-cf1720c)

赛时锁题后看别人代码，怎么都和我想法不一样？幸好没有被 hack。

## 思路

以下把 L 字形的覆盖网格，直接称为 L。

贪心思考，我们想让每次 L 覆盖的 $1$ 的数量少一些。

手玩一遍样例，我们发现：第一次 L 可能会覆盖多几个 $1$，**之后每次必定可以只覆盖一个** $1$。

为什么呢？看这张图。

![图炸了](https://cdn.luogu.com.cn/upload/image_hosting/zqfs04hu.png)

也就是说，假设第一次覆盖了 $k$ 个 $1$，整张地图共有 $x$ 个 $1$，那么总使用次数就是 $(x - k) + 1$。

上面这个可以理解为：第一次用 $1$ 个 L，之后每次消耗 $(x - k)$ 个 $1$，即 $(x - k)$ 个 L。共 $(x - k + 1)$ 个 L。

所以，我们应该使得 $k$ 最小。

只需对第一次 L 分情况考虑即可。枚举每一个 $2 \times 2$ 的矩阵：

![图炸了](https://cdn.luogu.com.cn/upload/image_hosting/s978vl2o.png)

然后模拟就搞定了。

需要注意，如果整张地图全是 $0$，答案应该为 $0$。特判即可。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
#define endl putchar('\n')
using namespace std;
void fastio()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
}
const int N = 505;
int a[N][N];
void solve()
{
	int n, m, sum = 0, minn = 114514;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			char x;
			cin >> x;
			a[i][j] = (x == '1'), sum += a[i][j]; //sum 统计 1 的个数
		}
	for (int i = 2; i <= n; i++)
		for (int j = 2; j <= m; j++)
		{
            //cnt 表示 2*2 方格内有多少个 1
			int cnt = a[i-1][j-1] + a[i-1][j] + a[i][j-1] + a[i][j];
			if (cnt == 0) continue;             //没有 1 说明无法构成 L 型
			if (cnt == 1) minn = min(minn, 1);  //一个 1 最少也要包含这个 1 否则不合法
			if (cnt == 2) minn = min(minn, 1);  //两个 1 仍然可以使 L 只覆盖一个 1
			if (cnt == 3) minn = min(minn, 2);  //三个 1 显然必须覆盖两个
			if (cnt == 4) minn = min(minn, 3);  //四个 1 明显覆盖 3 个
		}
	if (minn == 114514) {cout << 0 << '\n'; return;} //如果一个 L 都没法覆盖，就是 0
	cout << sum - minn + 1 << '\n';	 //否则，第一次用 1 个 L，之后每次消耗 (sum - minn) 个 1，共 (sum - minn + 1) 个 L
}
int main()
{
	fastio();
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

希望能帮助到大家！

---

## 作者：hyfzelda (赞：9)

# 思路

按照题意，每次操作要把 $3$ 个格子置为 $0$，
作为一个贪心的 OIer。

想要最大化操作次数，就要尽可能每次出现这种情况：

```plain
10 01 00 00
0X X0 X1 X1
```

如上，这种情况是最优的，每次消掉一个 $1$，那理想状态下就可以进行1的个数次操作。

但是，这题也不可能~~这么水~~，全部都是以上情况。

仔细观查可以发现，以上情况都会出现 $2$ 个$0$，而一次操作会出现 $3$ 个 $0$。

因此，第一次操作先选择含最少 $1$ 的情况。

用 $1$ 的总个数减去第一次操作的 $1$ 的个数，就是答案了。

找第一次操作中 ，最少 $1$ 数量的代码如下：

```cpp
int fx[4][2]= {{0,0},{1,1},{0,1},{1,0}};
bool flag2=0;
for(int i=1; i<n; i++)//防止跑到图外面
	for(int j=1; j<m; j++)
		for(int k=0; k<4; k++) {
			tmp=min(tmp,mp[i][j]+mp[i][j+1]+mp[i+1][j]+mp[i+1][j+1]-mp[i+fx[k][0]][j+fx[k][1]]);//选择2*2的一块格子，减去四个格子之一 
			if(mp[i][j]+mp[i][j+1]+mp[i+1][j]+mp[i+1][j+1]-mp[i+fx[k][0]][j+fx[k][1]]==0) flag2=1;//如果有三个0出现，标记 
		}
```
枚举减掉的那个格子就好了。

# 代码


```
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
signed main() {
	scanf("%d",&t);
	while(t--) {
		int ans=0,tmp=10;
		bool mp[505][505],flag=0;//flag存整个图是不是全部为0，mp数组存输入
		memset(mp,0,sizeof(mp));
		scanf("%d%d",&n,&m);
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				char a=' ';
				while(a!='1'&&a!='0') { //字符转bool
					scanf("%c",&a);
					if(a=='1') {
						flag=1;
						mp[i][j]=1;
						ans++;//ans存1个数 
					}

				}

			}
		}
		int fx[4][2]= {{0,0},{1,1},{0,1},{1,0}};
		bool flag2=0;
		for(int i=1; i<n; i++)//小于号用来防止跑到图外面
			for(int j=1; j<m; j++)
				for(int k=0; k<4; k++) {
					tmp=min(tmp,mp[i][j]+mp[i][j+1]+mp[i+1][j]+mp[i+1][j+1]-mp[i+fx[k][0]][j+fx[k][1]]);//选择2*2的一块格子，减去四个格子之一
					if(mp[i][j]+mp[i][j+1]+mp[i+1][j]+mp[i+1][j+1]-mp[i+fx[k][0]][j+fx[k][1]]==0) flag2=1;//如果有三个0出现，标记
				}
		if(flag==0) cout<<0<<endl;//没1输出0 
		else if(flag2==1) {
			cout<<ans<<endl;//初始有最优操作输出1的个数 
		} else cout<<ans-tmp+1<<endl;
	}
	return 0;
}
```









---

## 作者：FFTotoro (赞：6)

赛时因为把 $m$ 写成 $n$ 了，吃了好几次罚时……好在最后 AC 了。就当给大家做个提醒。

本题解题的关键点在于：如何让每次操作删除较少的 $1$？

我们定义一片“空区”为两个相邻的 $0$ 或者在对角线上相邻的 $0$。即，它们有可能长这样：

```
00
```
```
0
0
```

也有可能长这样（用 `x` 代表未知元素）：

```
0
x0
```

如果是这样，我们每次就可以消去可以与它们构成“L 形”的某个 $1$。容易证明，除非整个矩阵不存在“空区”或全都是 $0$，否则这样的操作每次可以消去 $1$ 个 $1$。

所以，如果整个矩阵刚开始存在空区，那么我们就可以让上面的操作一直执行下去，于是操作数就等于 $1$ 的个数。

但，如果刚开始的时候没有“空区”怎么办？

很显然，进行 $1$ 次任意操作后，必然会形成若干个“空区”。这是因为，操作后必然有若干个相邻的元素都是 $0$，而这也满足了我们形成“空区”的条件。

我们可以推出，如果整个矩阵刚开始没有“空区”，就分两种情况：有 $0$ 和没有 $0$。

如果有 $0$ 的话，就把其中某个 $0$ 和另外某 $2$ 个 $1$ 形成“L 形”，就可以构造出“空区”，接下来就可以开始进行有“空区”时的操作，总操作数等于 $1$ 的个数减去 $1$（第一次操作消去 $2$ 个 $1$）。

类似地，如果刚开始全都是 $1$，就随便选择 $3$ 个 $1$ 消除，形成“空区”后操作，总操作数等于 $1$ 的个数减去 $2$（第一次操作消去 $3$ 个 $1$）。

所以，设 $1$ 的个数为 $C_1$，记条件 $R$ 为“矩阵初始时有空区”，那么总操作数 $P$ 满足以下条件：

$P=\begin{cases}C_1&R\\C_1-2&\forall a_{i,j}=1\\C_1-1&\operatorname{otherwise}\end{cases}$

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[502][502];
signed main(){
    ios::sync_with_stdio(false);
    int t; cin>>t;
    while(t--){
        int n,m,c=2,x=0; cin>>n>>m;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
                x+=(a[i][j]-=48); // 统计 1 的个数
                if(!a[i][j])c=1; // 有 0
            }
        for(int i=1;i<=m;i++)a[n+1][i]=1;
        for(int j=1;j<=n;j++)a[j][m+1]=1;
        a[n+1][m+1]=1; // 把边缘全部设为 1，方便处理
        for(int i=1;i<=n;i++){
            bool flag=false;
            for(int j=1;j<=m;j++){
                if(!a[i][j]){
                    if(!a[i+1][j]||!a[i][j+1]||!a[i+1][j+1]||(j>1&&!a[i+1][j-1])){c=0; flag=true; break;} // 判断“空区”
                }
            }
            if(flag)break;
        }
        cout<<x-c<<endl; // 减去 c 后输出
    }
    return 0;
}
```

---

## 作者：white_carton (赞：4)

### 题意

有一个由 0 和 1 组成的矩阵。

每次操作可以选择一个 $2\times 2$ 的子矩阵，在这个子矩阵中选择一个 $L$ 形，将这个 $L$ 形里的 $3$ 个数变成 $0$，注意，这个 $L$ 形至少含有一个 $1$，你想最大化操作个数，问最多操作多少次。

### 解析

这题可以贪心的来做。

显然易知，在每一个 $L$ 型里， $0$ 更多更优，所以我们可以贪心的使每个 $L$ 型都包含更多的 $0$ 。

显然我们能发现，如果在矩阵里能找到一个 $2\times2$ 的子矩阵，使其内包含两个或以上个 $0$ ，我们一定可以把整个矩阵都通过 $1$ 的个数次操作清零，如果不包含这样的矩阵，那么我们就找到含 $0$ 最多的 $2\times2$ 矩阵进行一次操作将其转化为这种矩阵。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define fir first
#define sec second
#define inl inline
#define reg register
#define int long long
#define VI vector<int>
#define MII map<int,int>
#define PII pair<int,int>
#define PRT_Q priority_queue
using namespace std;
int t,a[510][510];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie();
	cout.tie();
	cin>>t;
	while(t--)
	{
		int n,m,flag=1,cnt=0;
		char ch;
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cin>>ch;
				if(ch=='0')
				{
					a[i][j]=0;
				}
				else
				{
					a[i][j]=1;
				}
				cnt+=a[i][j];
				if(i!=1)
				{
					if(a[i][j]==a[i-1][j]&&a[i][j]==0)
					{
						flag=0;
					}
				}
				if(j!=1)
				{
					if(a[i][j]==a[i][j-1]&&a[i][j]==0)
					{
						flag=0;
					}
				}
				if(j!=1&&i!=1)
				{
					if(a[i][j]==a[i-1][j-1]&&a[i][j]==0)
					{
						flag=0;
					}
				}
				if(j!=m&&i!=1)
				{
					if(a[i][j]==a[i-1][j+1]&&a[i][j]==0)
					{
						flag=0;
					}
				}
			}
		}
		if(flag)
		{
			if(n*m!=cnt)
			{
				cout<<cnt-1<<endl;
			}
			else
			{
				cout<<cnt-2<<endl;
			}
		}
		else
		{
			cout<<cnt<<endl;
		}
	}
	return 0;
}
```

码风很丑请各位将就着看吧

---

## 作者：AmaZingFantasy (赞：3)

## 题目大意

给你一个 $n \times m$ 的 $01$ 矩阵，每次取一个 $3$ 个字符组成的 L 形，并且至少包含一个 $1$，求最多可以取几次。

## 思路
不难想到，要让次数最多，最好情况是每次只取 $1$ 个 $1$。然而现实大多数时候往往达不到。

再考虑一下 L 形到底有什么好处。

所谓的 L 形可以看为是一个 $1 \times 2$ 的矩阵加上一个 $1 \times 1$ 的矩阵。这也就决定了只要我们的大矩阵里面有连续的两个 $0$，就可以每次只取一个 $1$。每次如果去掉了一个 $1$，就必然会有新的连续的两个 $0$ 出现。也就可以继续每次只取一个 $1$ 了。总共取的次数刚好等于这张图里面 $1$ 的个数。

推广一下，是不是只要在这张图里面任何 $2 \times 2$ 的子矩阵里面，有大于等于 $2$ 个 $0$，也可以做到每次只取 $1$ 个 $1$？

刚刚提到有两个 $0$ 的情况，但是如果没有呢？很简单，浪费 $1$ 个或 $2$ 个 $1$，将问题转化为上面的思路。如果整张图里面有 $0$，那么我们可以取包含这个 $0$ 的三个字符，最多浪费一个 $1$ 就可以用上面的做法做了。如果很不幸，整张图上全是 $1$，那么第一次怎么取都会取 $3$ 个，也就是浪费两个，这种情况最后加一个特判就可以了。

## 代码

```cpp

#include <iostream>
#include <cstring>
using namespace std;
typedef long long l;
const l maxn=505;
l arr[maxn][maxn];
int main(){
    l tt;
    cin>>tt;
    for(l u=0;u<tt;u++) {
        memset(arr,0,sizeof(arr));
        l n, m;
        cin >> n >> m;
        for (l i = 1; i <= n; i++) {
            for (l j = 1; j <= m; j++) {
                char c;
                cin >> c;//输入
                arr[i][j] = c - 48;
            }
        }
        bool flag = false;
        for (l i = 1; i < n; i++) {
            for (l j = 1; j < m; j++) {
                l cnt = (arr[i][j] == 0) + (arr[i + 1][j] == 0) + (arr[i][j + 1] == 0) + (arr[i + 1][j + 1] == 0);
                //统计每一个子矩阵是否有超过两个0。
                if (cnt >= 2) {
                    flag = true;
                }
            }
        }
        l tmp = 0;
        l ze = 0;
        for (l i = 1; i <= n; i++) {
            for (l j = 1; j <= m; j++) {
                tmp += (arr[i][j] == 1);//计算1的个数。
                ze += (arr[i][j] == 0);//计算是否有0。
            }
        }
        if (flag) {//如果子矩阵有大于等于2个0，输出1的个数。
            cout << tmp << endl;
        } else {//否则特判，这里压行了，写两个if也可以。
            cout << tmp + (ze != 0) - 2 << endl;
        }
    }
    return 0;
}
```

完结撒花。

---

## 作者：Pig_py (赞：1)

首先，我们可以发现，第一次将一个 $L$ 形变成零，要么出现一个 $2\times2$ 的全零矩阵，要么有一个 $2\times2$ 的矩阵只有一个 $1$.后者可以通过再来一次变成一个 $2\times2$ 的全零矩阵。

然后我们可以利用这个 $2\times2$ 的矩阵逐步往外扩散，每次选定一个只含有一个 $1$ 的 $L$
形，每次删掉一个 $1$.

因此，贪心地想，为了让步数尽可能多，我们只需让第一次选出来的 $L$ 形矩阵中的 $1$ 尽可能少就好。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m;
		scanf("%d%d",&n,&m);
		char a[505][505];
		int mn=3;//最多可以一下删掉三个，所以初始应赋值为 3 
		int ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				if(a[i][j]=='1')ans++;
			}
		} 
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++){
				if(i-1>=1&&j-1>=1)mn=min(mn,int(a[i][j])-48+int(a[i-1][j])-48+int(a[i][j-1])-48);
				if(i-1>=1&&j+1<=m)mn=min(mn,int(a[i][j])-48+int(a[i-1][j])-48+int(a[i][j+1])-48);
				if(i+1<=n&&j-1>=1)mn=min(mn,int(a[i][j])-48+int(a[i+1][j])-48+int(a[i][j-1])-48);
				if(i+1<=n&&j+1<=m)mn=min(mn,int(a[i][j])-48+int(a[i+1][j])-48+int(a[i][j+1])-48);					
			}
		}
		printf("%d\n",min(ans-mn+1,ans));
	}
}
```



---

## 作者：zfx_VeXl6 (赞：1)

### 思路
题目中说到的L型共有 $4$ 种，为了方便，我们把它们编号。以下从左到右为 $1$ 到 $4$ 号。

```
**  **  *    *
*    *  **  **
```

只需考虑第一次覆盖后消除的 $1$ 的个数即可，之后的覆盖都能做到只消除 $1$ 个 $1$。

考虑原图中含有 $1$ 的数量最小的 $2\times 2$ 的网格，把覆盖L型后 $1$ 的最小消除数量记为 $k$，分以下 $4$ 种情况讨论。

```
00
00
```

这个图为第一种情况，$k=0$。

```
10 & 11 & 10
00 & 00 & 01
```

这四个图为第二种情况，$k=1$。

```
11
10
```

这个图为第三种情况，$k=2$。

```
11
11
```

这个图为第四种情况，$k=3$。

设整个图中 $1$ 的数量为 $p$，则答案为：

$ans=\begin{cases}p&k\le1\\p-k+1&k>1\end{cases}$

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k,p;
char a[1001][1001];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		p=0;
		k=3;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				cin>>a[i][j];
				if(a[i][j]=='1')
					p++;	//统计1的数量
			}
		for(int i=1;i<n;i++)
			for(int j=1;j<m;j++)
			{
				int a1,a2,a3,a4;
				a1=a2=a3=a4=0;	//统计2*2网格中1的最小数量，ai代表第i个L型
				if(a[i][j]=='1')
				{
					a1++;
					a2++;
					a3++;
				}
				if(a[i+1][j]=='1')
				{
					a1++;
					a3++;
					a4++;
				}
				if(a[i][j+1]=='1')
				{
					a1++;
					a2++;
					a4++;
				}
				if(a[i+1][j+1]=='1')
				{
					a2++;
					a3++;
					a4++;
				}
				k=min(k,min(min(a1,a2),min(a3,a4)));
			}
		if(k<=1)
			cout<<p<<'\n';
		else
			cout<<p-k+1<<'\n';
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

## 前言

昨天晚上错过了这场 CF，很遗憾。

看了看这道题，觉得蛮有意思的，就想了想，一开始口胡了一个线段树做法（？？？）后来仔细想了想发现这道题其实是个诈骗题。

## 思路

首先，我们如果存在一个只包含一个 $1$ 的 `L` 形，那么显然我们消一次就可以消掉这个 $1$。然后，我们发现，这个 `L` 形的竖着两格都变空了，可以用来构造新的 `L` 形；横着的两格也变空了，也可以用来构造。因此，只要能找到这么一个 `L` 形，那么我们就可以做到每次只消掉一个 $1$，答案就是 $1$ 的个数。

如果找不到满足条件的这个 `L` 形，我们就必须去用一次操作暴力构造一个这样的 `L` 形。分成两种情况：

- 如果这个数组中全部是 $1$，那么第一次的 `L` 形操作会消掉 $3$ 个 $1$，所以最后的答案就是 $1$ 的个数减去 $2$。

- 如果这个数组有至少一个 $0$，那么 $0$ 一定能被某个 `L` 形覆盖到，因此这个 `L` 形只会消掉两个 $1$，最终的答案就是 $1$ 的个数减去 $1$。

最后还要特判一下，如果数组全部为 $0$，那么答案显然是 $0$。

代码一共包含两个模块：

1. 判断是否存在一个只包含一个 $1$ 的 `L` 形。

2. 如果不存在，判断是否全 $1$ / 全 $0$。

然后简单统计一下 $1$ 的个数，计算一下答案就行了。

## 代码

还是放一下吧（虽然非常好写）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=505;
char s[MAXN][MAXN];
int n,m,zer='0'+'0'+'0';
inline bool check(const int &x,const int &y){
	if(x>1 && y>1 && s[x-1][y]+s[x][y]+s[x][y-1]-zer==1) return 1; // 左上角 
	if(x>1 && y<m && s[x-1][y]+s[x][y]+s[x][y+1]-zer==1) return 1; // 右上角 
	if(x<n && y>1 && s[x+1][y]+s[x][y]+s[x][y-1]-zer==1) return 1; // 左下角 
	if(x<n && y>1 && s[x+1][y]+s[x][y]+s[x][y+1]-zer==1) return 1; // 右下角 
	return 0;
}
int main(){
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>(s[i]+1);
		bool flag=0; int cnt=0;
		for(register int i=1;i<=n;i++)
			for(register int j=1;j<=m;j++){
				flag|=check(i,j);
				cnt+=(s[i][j]=='1');
			}
		printf("%d\n",cnt-(!flag)+(cnt==0)-(cnt==n*m));
		/*
		上面那一行等价于：
		if(!flag && cnt!=0) cnt--; // 这里就是判断数组不是全 0 但是找不到这么一个 L 的情况 
		if(cnt==n*m) cnt--; // 这是判断数组全为 1 的情况 
		printf("%d\n",cnt); 
		*/ 
	} 
	return 0;
}
```

---

## 作者：Cloote (赞：1)

[更好的阅读体验？](https://www.cnblogs.com/Arcka/p/16601264.html)

## 题意简述
给你一个 $01$ 矩阵，每一次你可以在这个矩阵中找到一个 $L$ 型，将它全部变成 $0$。$L$ 型的定义是在一个 $2\times2$ 矩阵中，除开一个角之外的图形，其中必须包含至少一个 $1$。

现在需要你找到将整个矩阵变成 $1$ 的最大操作数。

## 题目分析

由于 $L$ 型是在一个 $2\times2$ 的矩阵中，所以我们不妨从这里开始分析。

设 $1$ 的个数为 $x$，$0$ 的个数为 $y$，操作数为 $ans$。

### 1. 如果矩阵没有 $0$
```
1 1
1 1
```
这种情况会有 $4$ 个 $1$。

显然，第一次操作至少会让三个 $1$ 变成 $0$，然后转到情况 $4$，这时候最大操作数是 **$2$**。

**此时，$ans=x-2$。**

### 2. 如果矩阵只有一个 $0$
```
0 1
1 1
```

其中的一种情况是上面这样的，这时候会有 $3$ 个 $1$。

同样的，第一次操作至少会让两个 $1$ 变成 $0$，然后转到情况 $4$，这时候最大的操作数是 **$2$**。

**此时，$ans=x-1$。**

### 3. 如果矩阵只有两个 $0$

```
0 1 | 0 0
1 0 | 1 1
```

其中有两种情况如上图，这时候会有 $2$ 个 $1$。

这时候第一次操作可以只改变一个 $1$，接着转到情况 $4$，最大的操作数是 **$2$**。

**此时，$ans=x$。**

### 4. 如果矩阵只有三个 $0$
```
0 0
0 1
```

其中一种情况如上，这时候有 $1$ 个 $1$.

这时候只能改变一个 1,操作数也就是 **$1$**。同时显然，矩阵中没有 $1$ 时操作数是 $0$，这里便不做分类讨论。

**此时，操作数 = 1 的个数。**

根据上面的分析，我们可以大胆猜想，则在 $2\times2$ 矩阵中：

$\begin{cases}
ans &= x-2 &(y=0) \\
ans &= x-1 &(y=1) \\
ans &=x &(y\ge2) 
\end{cases}$

我们尝试将结论推广到普通矩阵中。

没有 $0$ 的情况显然和之前一样。

而这时候就不是只有 $1$ 个 $0$ 的情况，而是在一个 $2\times2$ 矩阵中只有 $1$ 个 $0$。

同样，至少有 $2$ 个 $0$ 的情况也需要转移到在 $2\times2$ 矩阵中至少有 $2$ 个 $0$。

这样我们只要求出 $1$ 的个数并且判断在 $2\times2$ 矩阵中有没有至少两个 $0$ 即可。

为什么这种思路是正确的？

一个任意的 $n\times m$ 矩阵（$n,m\ge2$）,都会包含若干个 $2\times2$ 的矩阵，即使矩阵可能会重叠。

如果其中有一个矩阵有大于 $1$ 个的 $0$，就可以从这里开始操作，扩展到每个 $2\times2$ 矩阵都有大于 $1$ 个的 $0$，情况简化成最开始分析中的第三种情况。否则就只能按照第二种情况来扩展。

具体代码见下：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e2+5;
int n,m;
int a[N][N];

signed main(){
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--){
		cin>>n>>m;
		int suma=0,sumb=0;//suma是0的个数，sumb是1的个数。其实只记录其中的一个也可以 
		bool f=false;
		for(int i=1;i<=n;i++){
			string s;
			cin>>s;
			for(int j=0;j<m;j++) a[i][j+1]=s[j]-'0';
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i][j]==0){
					suma++;
					//下面判断2*2矩阵中有两个0的情况，注意判断数组越界，用循环也可以 
					if((i+1<=n&&a[i+1][j]==0)||(i-1>=1&&a[i-1][j]==0)||(j-1>=1&&a[i][j-1]==0)||(j+1<=m&&a[i][j+1]==0)) f=true;//两个0是相邻的 
					else if((i+1<=n&&j+1<=m&&a[i+1][j+1]==0)||(i-1>=1&&j-1>=1&&a[i-1][j-1]==0)||(i+1<=n&&j-1>=1&&a[i+1][j-1]==0)||(i-1>=1&&j+1<=m&&a[i-1][j+1]==0)) f=true;//两个0称对角 
				}
				else sumb++;
			}
		}
		if(suma==0) cout<<sumb-2<<"\n";//都是1 
		else if(sumb==0) cout<<"0\n";//都是0 
		else if(f==false) cout<<sumb-1<<"\n";//所有2*2矩阵中都只有一个0 
		else cout<<sumb<<"\n";//任意2*2矩阵中有至少两个0 
	}
	return 0;
}
~~~


---

## 作者：LuomuQDM (赞：1)

### 题意

翻译就是我写的，所以这里不再复述。

### 思路

容易想到为了使操作次数尽量多，那么每次操作消除的 $1$ 数量肯定得尽量少。当一个矩阵中出现一个 $L$ 型中仅含一个 $1$ 时，可以保证剩下每次操作都可以只消除一个 $1$。因为我们先消除这个 $L$ 型中的 $1$，接着就可以“借用”这个 $L$ 型中两个 $0$，再去消除其他 $1$。

直接这么说不太好理解，给各位举个例子。

```
1.
111
011
011
2.
111
001
011
3.
111
001
001
4.
011
001
001
...
```

由于可能初始矩阵中没有一个位置可以做到一次操作仅消除一个 $1$，所以我们要找到消除 $1$ 数量最小的第一次操作，从第二次操作开始就可以做到每次消除一个 $1$。先统计矩阵中 $1$ 的个数，记为 $sum$，若为 $0$，则无法操作，输出 $0$。否则枚举每个位置，并统计以这个位置为每一种形状的 $L$ 形的角时，$L$ 形内 $1$ 的个数，只要这个个数大于 $0$（因为每次操作的 $L$ 形中至少一个 $1$），就将其比较并更新变量 $Min$。最后 $Min$ 就是最佳的第一次操作所消除的 $1$ 的个数。答案即为 $sum-Min+1$。

---

## 作者：Daidly (赞：0)

[Codeforces Round #815 (Div. 2) 全场题解以及更好的阅读体验](https://www.cnblogs.com/Daidly/p/16607199.html)

我们最想一次操作选的 $L$ 形中有且只有一个 $1$，此时答案即为 $\sum a_i$，我们考虑什么时候不能达到。

对一个 $2\times 2$ 的子矩阵进行研究，发现当子矩阵中有一个 $1$ 时，最多操作 $1$ 次，没有浪费。

有两个 $1$ 时，不论是斜对角还是同行同列，都可以进行两次操作，没有浪费。

有三个 $1$ 时，只能进行两次操作，浪费了 $1$ 次。

有四个 $1$ 时，也只能进行两次操作，浪费了 $2$ 次。

而当我们清空出一个 $2\times 2$ 的子矩形时，其他所有 $1$ 都能被 $1$ 次操作消去，不会浪费。

统计每个子矩形中最小的浪费个数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
 
void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}
 
const int N=505;
int t,n,m,a[N][N],ans,minn,tmp;
char c;
 
int main(){
	t=read();
	while(t--){
		n=read(),m=read(),ans=0,minn=1e9;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cin>>c;
				if(c=='1')a[i][j]=1,ans++;
				else a[i][j]=0;
			}
		}
		for(int i=1;i<n;++i){
			for(int j=1;j<m;++j){
				tmp=a[i][j]+a[i][j+1]+a[i+1][j]+a[i+1][j+1];
				if(tmp==1||tmp==2)minn=min(minn,0);
				else if(tmp==3)minn=min(minn,1);
				else minn=min(minn,2);
			}
		}
		if(!ans)puts("0");
		else print(ans-minn),puts("");
	}
	return 0;
}
```

---

## 作者：sixrc (赞：0)

由于要最大化操作次数，所以考虑最小化每次删去的 $1$ 的个数。

我们希望每次都只删去一个 $1$，但很快发现不一定做得到。

但是有一种情况是可以保证往后的每次都只删掉一个 $1$，就是存在一个 L 字形，使得其中有两个点为 $0$。原因很显然，因为在这个 L 字形内只需要删去一个 $1$，而处理完这个 L 字形后，又肯定存在另外的 L 字形，满足其中有两个点为 $0$。这样就变成了和一开始一样的问题。

而如果不存在有两个点为 $0$ 的 L 字形，我们就通过一次操作强行变出来。此时如果能找到有一个 $0$ 的 L 字形，那最好；否则就只能第一次删去三个 $1$ 了。

然后代码就很显然了。

这就是一道 CF 的诈骗题。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, m, pd, tot, a[505][505];
int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1}, dy[] = {1, 1, 1, 0, -1, -1, -1, 0};
int main(){
	scanf ("%d", &t);
	while (t --){
		tot = 0, pd = 1;
		scanf ("%d%d", &n, &m);
		for (int i=1; i<=n; i++){
			for (int j=1; j<=m; j++){
				char ch;
				cin >> ch;
				if (ch == '1') a[i][j] = 1;
				else a[i][j] = 0;
				tot += a[i][j];
			}
		}
		for (int i=1; i<=n; i++){
			for (int j=1; j<=m; j++){
				for (int k=0; k<8; k++){
					int nx = i + dx[k], ny = j + dy[k];
					if (nx > 0 && ny > 0 && nx <= n && ny <= m){
						if (a[i][j] == 0 && a[nx][ny] == 0) pd = 0;
					}
				}
			}
		}
		printf ("%d\n", tot - pd - (tot == n * m));
	}
	return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

我们倒过来想，既然要让操作次数尽可能地多，我们就让每次删除 $1$ 的个数尽可能的少。

我们给出一个显然的结论，假如存在一个方格为 $0$，它在紧邻的八个方格中，有一个方格为 $0$，则答案就是 $1$ 的个数。因为我们每次都可以找到一个 $\texttt{L}$ 型，这三个格子中恰好有两个位置为 $0$，一个位置为 $1$，对这个位置进行一次操作，只会删除掉一个 $1$，显然这是最优的。

如果不存在上述所说的方格，这个时候我们随便进行一次操作，就会产生上述所说的方格，那么我们再分两种情况：

1. 所有方格全为 $1$，这个时候我们随便进行一次操作，都为删除 $3$ 个 $1$，所以答案为 $1$ 的个数 $-2$。
2. 存在有零的方格，这是我们选择一个含 $0$ 的区域进行一次操作，就会删除 $2$ 个 $1$，所以答案为 $1$ 的个数 $-1$。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
int a[505][505];
void cf(){
	int n=read(),m=read();
	int cnt1=0,cnt2=0;
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			char c=getchar();
			while(c!='0'&&c!='1'){
				c=getchar();
			}
			a[i][j]=c-'0';
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a[i][j]) ans++;
			if(!a[i][j]){
				if((i-1<=0||a[i-1][j])&&(j-1<=0||a[i][j-1])&&(i+1>n||a[i+1][j])&&(j+1>m||a[i][j+1])&&(j-1<=0||i-1<=0||a[i-1][j-1])&&(j-1<=0||i+1>n||a[i+1][j-1])&&(j+1>m||i-1<=0||a[i-1][j+1])&&(j+1>m||i+1>=n||a[i+1][j+1])) cnt1++;
				else cnt2++;
			}
		}
	if(cnt2) printf("%d\n",ans);
	else if(cnt1) printf("%d\n",ans-1);
	else printf("%d\n",ans-2);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=0;
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

## 作者：Qinzh (赞：0)

# CF1720C Corners
## 题意：

给定一个 $n \times m$ 的由 $0,1$ 组成的矩阵

规定 $L$ 型为一个缺一个角的 $2 \times 2$ 的图形

你可以对此矩阵进行操作：将一个包含至少一个 $1$ 的 $L$ 型内全部元素变为 $0$ 

求对此矩阵的最大操作数

## 分析：

我们可以得出，一个 $L$ 型有一下四种形状：

![](https://cdn.luogu.com.cn/upload/image_hosting/o0b4h45w.png)

而符合要求的 $L$ 型中，0的分布有6种情况

![](https://cdn.luogu.com.cn/upload/image_hosting/wd5eunhe.png)

容易得到，如果该 $L$ 型符合以上6种情况，即可做到每次都只删掉一个 $1$ 直到无法操作，达到了操作最大化

即：
	
矩阵中存在一个这样的 $L$ 型，最大操作数为 $1$ 的个数

若没有，但是存在单个的 $0$ ，则操作时必定删除两个 $1$ ,而操作数只加 $1$ 则浪费掉一个 $1$

若不存在 $0$ 则需删除任意一个普通 $L$ 型，则操作时必定删除三个 $1$ ,而操作数只加 $1$ 则浪费掉两个 $1$

所以我们可以设置一个变量 $bj$ ，初始值为 $2$ ，表示目前未发现 $0$ 

当找到一个 $0$ 时，$bj$ 设为 $1$ 

当找到一个 $L$ 时，$bj$ 设为 $0$

我们再统计一遍 $1$ 的个数，存入 $cnt1$ 变量中即可

答案即为 $cnt1-bj$
## AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[505][505];
int main(){
	cin>>t;
	for(int i=1;i<=t;++i){
		cin>>n>>m;
		int cnt1=0,bj=2;
		for(int j=0;j<=n;++j)a[j][0]=1;//边界设为1方便L型判断
		for(int j=1;j<=m;++j)a[0][j]=1;
		for(int j=1;j<=n;++j){
			for(int k=1;k<=m;++k){
				int ct=0;
				char v;
				cin>>v;
				a[j][k]=v-'0';
				if(a[j][k]==1)cnt1++;//若为1，则存入cnt1
				else bj=min(bj,1),ct++;//判断0
				if(a[j-1][k]==0) ct++;
				if(a[j][k-1]==0) ct++;
				if(a[j-1][k-1]==0) ct++;
				if(ct>=2)bj=0;//判断L型
			}
		}
		cout<<cnt1-bj<<endl;//千万别忘endl
	}
	return 0;
}
```
8.19.16:31

---

## 作者：OoXiao_QioO (赞：0)

# 思路

给大家分享一个超级简单的方法。

发现每次删除最多 $0$ 的次数的 $L$ 形最优，那我们只要保证每次删除的 $0$ 次数最大即可。

对于 $L$ 形的四种删法：

```
1:
ox
oo
2:
xo
oo
3:
oo
ox
4:
oo
xo
```

其中 $o$ 表示 $L$ 形，$x$ 表示其他元素。

发现每次消除均在一个 $2\times2$ 的空间里进行，其中保证 $0$ 的次数最多的只有如下几种：
```
1:
00
2:
0
0
3:
0
x0
```
可以定义以上三种情况为“多 $0$ 区”。

分别为横着连续两个 $0$，竖着连续两个 $0$，还有一种为对角线上有两个 $0$。如果消除的 $L$ 形内 $0$ 的分布是多 $0$ 区，就可以直接消掉剩下的其中一个 $1$。除非二位数组内不存在多 $0$ 区或者都为 $0$，我们都可以每次只消掉一个 $1$，保证收益最大。

那如果一开始并没有多 $0$ 区怎么办？

很显然可以发现，只要进行一次操作后，二维数组必定出现若干个多 $0$ 区，就像一开始给大家出示的 $L$ 形删法，删除一次后立刻就会在 $2\times2$ 的空间里出现 $3$ 个 $0$，即 $1$ 个 $1$，满足了我们对多 $0$ 区的条件。

说了这么多，我们就用一句话来概括以上全部内容：

- 如果没有出现多 $0$ 区，直接让总操作方案数 $-1$，来构造除一个多 $0$ 区，否则方案数为二维数组内出现 $1$ 的个数。

那么接下来还有一个判断，如果二维数组里面全是 $1$ 呢？例如

```
111
111
111
```
发现方案数为 $7$，$7 = 9-2$，为什么会少一个 $2$ 呢？我们的多 $0$ 区所包含的 $1$ 的个数只为 $1$，但是第一次消除，不管如何选择，$1$ 的个数始终为 $2$，所以我们需要减去 $2$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义
	
	 
	int t,n,m,i,j,cnt;
	bool f;
	char s[501][501];
	
	//输入
	 
	cin>>t;
	
	//处理 
	while(t--)
	{
		cin>>n>>m;
		getchar();//为了能让大家感受的更直观，我这里的二维字符数组行和列 都是从 1 开始的，而下面所用的 scanf("%c") 的效果等价于 getchar()，都会读入空格和换行这一类字符，所以我们要吞掉输入 n 和 m 后面的哪一个换行。 
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
				scanf("%c",&s[i][j]);
			getchar();//吞掉末尾的换行 
		}
		cnt = 0;//cnt 表示字符 '1' 的个数 
		f = 0;//f 表示是否出现多 0 区，初值为不出现。 
		for(i=1;i<n;i++)//注意超出边界的处理，我们循环只需要到 n-1 即可。 
			for(j=1;j<m;j++)//同上 
				if(s[i][j]+s[i+1][j+1]+s[i+1][j]+s[i][j+1]-(4*'0')<=2)//找出 (i,j) 所在的 2*2 空间是否为多 0 区。 
					f = 1;//是，让 f 变为 1。 
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(s[i][j]=='1')//查找 '1' 的个数。 
					cnt++;
		if(cnt==n*m)//特判 1，效果前文已讲。 
			cnt--;
		if(!f)//特判 2，即没有出现多 0 区。 
			cnt--;
		cout<<cnt<<endl;//输出 
	}
	return 0;
}
```


---

## 作者：ztlh (赞：0)

# Solution

设 $1$ 的数量为 $sum$。

- 当矩阵存在两个相邻（横向或斜着皆可）的 $0$ 时（即两个 $0$ 在一个 L 里），可以保证每次只消掉一个 $1$，输出 $sum$ 即可。

- 否则，如果存在 $0$，则第一次会消掉两个 $1$，接下来则与第一种情况同理，输出 $sum - 1$ 即可。

- 否则（$sum = n \times m$，即全为 $1$），第一次必然消去 $3$ 个，接下来与第一种情况同理，输出 $sum - 2$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T,n,m;
char s[505][505];
int sum;
bool flag;
int main(){
	scanf("%d",&T);
	while(T--){
		flag=sum=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				s[i][j]='\0';
		for(int i=1;i<=n;i++){
			scanf("%s",s[i]+1);
			for(int j=1;j<=m;j++)
				sum+=(s[i][j]=='1');
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(s[i][j]=='1') continue;
				if(i+1<=n&&s[i+1][j]=='0') flag=1;
				if(j+1<=m&&s[i][j+1]=='0') flag=1;
				if(i+1<=n&&j+1<=m&&s[i+1][j+1]=='0') flag=1;
				if(i+1<=n&&j-1>=1&&s[i+1][j-1]=='0') flag=1;
			}
		if(sum==n*m) printf("%d\n",sum-2);
		else if(flag) printf("%d\n",sum);
		else printf("%d\n",sum-1);
	}
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：0)

>有一个由 $0$ 和 $1$ 组成的矩阵。
>
>每次操作可以选择一个 $2\times 2$ 的子矩阵，在这个子矩阵中选择一个 L 形，将这个 L 形里的 $3$ 个数变成 $0$，注意，这个 L 形至少含有一个 1，你想最大化操作个数，问最多操作多少次。

为了方便起见，对于一个 L 形里的数我们用 `001`，`011` 这种形式体现。

因为你想最大化操作个数，那么我们就尽可能每次减少每次把 $1$ 变成 $0$ 的个数，比如你可以选择 `011` 和 `001`，你肯定选择 `001`，这是显然的。

那注意到我们每次操作完一次，就可以在原来的基础上继续操作，这样每次删除的个数都是 $1$。

以样例为例。

```plain
1110
0111
0111
```
我们肯定想找 `001` 这种 $2$ 个 $0$ 和 $1$ 个 $1$ 的，但是找不到，所以找 `110`，然后找到了，我们把他清零，就变成了：

```plain
0110
0011
0111
```

诶，你发现现在就有 `001` 了，然后我们在这个基础上，一直改下去，你发现一直都会有 `001`，所以就很简单了，具体见代码。

[参考代码](https://www.luogu.com.cn/paste/6pwrwbs4)。

---

## 作者：Aurora_Borealis_ (赞：0)

首先有定义：

- 下文所有“连通”均指八连通。

- 两个联通的 $0$ 叫做一个“基”

有以下做法：

首先可知，在一个“基”上可以通过一次操作使“基”所在 $L$ 型中的**一个** $1$ 变为 $0$。

设矩阵中 $1$ 的个数为 $num$。

所以，先暴力地找初始矩阵中是否存在一个“基”，如果存在，则答案为 $num$，如果不存在且矩阵中存在 $0$，答案为 $num-1$（因为第一次操作需要消耗两个 $1$）。剩下的情况，也就是全 $1$ 阵，答案为 $num-2$，原因与情况二同理。

code：

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,n,m;
char a[505][505];
int xx[8]={0,0,-1,1,1,-1,1,-1};
int yy[8]={1,-1,0,0,-1,1,1,-1};
int main(){
	cin>>t;
	while(t--){
		int ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				if(a[i][j]=='1'){
					ans++;
				}
			}
		} 
		bool flag=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i][j]=='0'){
					for(int k=0;k<8;k++){
						int tx=i+xx[k],ty=j+yy[k];
						if(a[tx][ty]=='0'&&tx>0&&tx<=n&&ty<=m&&ty>0){
							flag=1;
							break;
						}
					}
				}
			}
		} 
		if(ans==n*m){
			cout<<n*m-2<<endl;
		}else if(flag==1){
			cout<<ans<<endl;
		}else if(flag==0){
			cout<<ans-1<<endl;
		}
	}
	return 0;
}

```


---

## 作者：sgl654321 (赞：0)

### 题目大意
- 定义：一个 $2\times 2$ 的矩阵，减去任意一个角，剩下的 $3$ 个组成的图形称作 $L$ 形。
- 给定一个 $n\times m$ 的矩阵，所有元素都是 $0$ 或 $1$，每一次操作你可以选择一个含有至少一个 $1$ 的 $L$ 形，将里面的所有 $1$ 变成 $0$。
- 问把矩阵中所有的元素都改成 $0$，**最多**可以花费几次操作。

### 解题思路
由于让我们求的是最多，所以我们容易想到让每一次都只删除一个 $1$。思考：怎样的情况可以满足每次只删除一个 $1$？

对于一个 $2\times 2$ 的矩阵，要想最大化删除次数：

1. 若其中不含有 ```1```，则不能删除任何元素，理由略。
2. 若其中只含有一个 ```1```，则只能删除 $1$ 次，理由略。
3. 若其中含有两个 ```1```：则只能删除 $2$ 次，理由如下：

第一种情况如下图（可以翻转）：
```
1 1
0 0
```
对于这种情况我们可以先选择左上角，左下角，右下角的 $3$ 个数，修改成 ```0```。然后再修改掉右上角这个 ```1```。所以最多可以删除 $2$ 次。第二种情况如下图(可以翻转)：
```
0 1
1 0
```
对于这种情况我们也可以先选择左上角，左下角，右下角的 $3$ 个数，修改成 ```0```。然后再修改掉右上角这个 ```1```。所以最多可以删除 $2$ 次。

4. 若其中含有三个 ```1```，则最多可以删除 $2$ 次，理由如下：

如下图（可以翻转）：
```
1 1
1 0
```

第一次就必须删除 $2$ 个 ```1```，如选择左上角，左下角和右下角。然后再删除剩下的一个 ```1```。

5. 若其中含有四个 ```1```，则最多可以删除 $2$ 次，理由略。

根据上面的分类讨论，我们就得出了解题思路：
- 特殊情况：如果全图都是 ```0```，则输出 $0$。
- 如果全图都是 ```1```，则所有的 $2\times 2$ 的方格都是上面第五种情况，因此选择任意一个删除 $2$ 次，再以删除了的那个为根据地，慢慢向外扩张，每次删除 $1$ 个 ```1```。因此输出 $1$ 的个数减去 $2$。
- 如果找得到一个 $2\times 2$ 的方格含有三个以下（不含）的 ```1```，则这个方格最多删除 $2$ 次，再以删除了的那个为根据地，慢慢向外扩张，每次删除 $1$ 个 ```1```。因此输出 $1$ 的个数。
- 其余情况，就是所有的 $2\times 2$ 的方格都是第四种情况，则选择任意一个 $2\times 2$ 的方格，最多删除 $2$ 次，再以删除了的那个为根据地，慢慢向外扩张，每次删除 $1$ 个 ```1```。因此输出 $1$ 的个数减去 $1$。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,sum,num;
char ch[510][510];
bool p; 
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		sum=0;
		p=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				cin>>ch[i][j];
				if(ch[i][j]=='1')sum++;
			}
		if(sum==0){
			cout<<0<<endl;
			continue;
		}
		if(sum==n*m){
			cout<<sum-2<<endl;
			continue; 
		}
		if(sum==1){
			cout<<1<<endl;
			continue;
		}
		for(int i=1;i<=n-1;i++)
			for(int j=1;j<=m-1;j++){
				num=0;
				if(ch[i][j]=='1')num++;
				if(ch[i+1][j]=='1')num++;
				if(ch[i+1][j+1]=='1')num++;
				if(ch[i][j+1]=='1')num++;
				if(num==1||num==2){//一个区块里面只含有
				//1 或 2 个1，那么就可以以这个为落脚点，进行
				//每次删除一个 1。 
					p=1;
					break;
				}
			}
		if(p==1)cout<<sum<<endl;
		else cout<<sum-1<<endl;
	}
	return 0;
}
```

---

