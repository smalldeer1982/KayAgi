# Marlin

## 题目描述

鱼托邦市可以想象成一个4行且每行包含n个奇数的网格。

它有两个主要的村庄：第一个位于左上方的方格（1，1），住在那里的人喜欢在右下方的方格（4，n）的金枪鱼池塘钓鱼。第二个村庄位于（4，1），人们喜欢（1，n）的鲑鱼池塘。

鱼托邦市市市长想在该市设立k家酒店，每家都占据一个方格。为了让人们可以从任何地方进入城市，酒店不应设在边缘。

如果两个方格均没有被旅馆占据并共用一条边，一个人可以从一个方格移动到另一个方格。

你能帮助市长把旅馆安置在一个地方，使得每个村子的人都有相同数量的最短路径到他们的首选池塘吗？

## 样例 #1

### 输入

```
7 2
```

### 输出

```
YES
.......
.#.....
.#.....
.......
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
YES
.....
.###.
.....
.....
```

# 题解

## 作者：Larry76 (赞：1)

## 前言：
关于原题目中的 *“旅馆”* 这一用词，个人感觉用起来十分不畅，于是下文中将会用 *“障碍物”* 一词来代指旅馆。 

## 题目大意：
有一座 $4 \times n$ 的矩阵，然后让你放置障碍物（其中，障碍物不能放置到矩阵的边缘，换句话说，障碍物只能放到位于中央的 $2 \times (n-1)$ 这一子矩阵中），使其保证从**左上到右下**的最短路径**条数**和从**左下到右上**的最短路径**条数**一致.

问能否构造出相应的矩阵，如果能，输出“YES”并输出构造出来的矩阵，否则输出“NO”。

**题目保证 $\boldsymbol{n}$ 为奇数**。

## 题目分析：
这道题显然有很多种做法，我这里来讲一讲我的做法，我的做法是：我们只需要保证障碍物在矩阵中保持**对称**，就能保证其最短路径条数一致。

理由是显然的（~~但我不会证~~），因为此时能保持对称的矩阵一共就如下几种：
1. 障碍物都在一行且左右对称分布。
2. 障碍物在两行上且上下对称分布。
3. 障碍物在两行上且左右对称分布（保证第一行填满了）。
4. 障碍物在两行上且左右对称分布（不保证第一行填满）

其中，第 $2,3,4$ 种是显然的，因为都相当于堵住了在同样的位置被障碍物堵死了。

至于第一种，不会证，但是浅浅的跑了一下从 $3 \sim 99$ 的程序来验证了一下，发现确实没啥问题，所以可以放心大胆的用这一条性质。

综上，我们的做题思路是：
1. 若 $k$ 为偶数，则可以构造第 $2$ 类矩阵。
2. 若 $k$ 为奇数，则先尝试构造第 $1$ 类矩阵，若第一行被填满后还有剩余，则在尝试构造第 $3$ 类矩阵。

## 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define TIME_LIMIT (time_t)1e3
#define dbg(x) cerr<<#x<<": "<<x<<endl;
bool block[100][100];
signed main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    time_t cs = clock();
#endif
//========================================
    int n,k;
    cin>>n>>k;
    cout<<"YES"<<endl;
    if(!(k&1)){
        for(int i=2;i<=1+k/2;i++){
            block[2][i] = 1;
            block[3][i] = 1;
        }
    }
    else{
        int row = 2;
        while(k>(n-2)){
            for(int i=2;i<=n-1;i++)
                block[row][i] = 1;
            k-=n-2;
            row++;
        }
        int space = n-2-k;
        for(int i=2;i<=1+k/2;i++)
            block[row][i] = 1;
        if(k&1){
            int center = n/2+1;
            block[row][center] = 1;
        }
        for(int i=2+k/2+space+(k&1);i<=n-1;i++)
            block[row][i] = 1;
    }
    for(int i=1;i<=4;i++){
        for(int j=1;j<=n;j++){
            if(block[i][j])
                cout<<'#';
            else
                cout<<'.';
        }
        cout<<'\n';
    }
    cout<<endl;
//========================================
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
    time_t ce = clock();
    cerr<< "Used Time: " << ce-cs << " ms."<<endl;
    if(TIME_LIMIT<ce-cs)
        cerr<< "Warning!! Time exceeded limit!!"<<endl;
#endif
    return 0;
}
```

---

## 作者：流绪 (赞：0)

题意：
有一个四行 $n$ 列区域，位于 $(1,1)$ 与 $(4,1)$ 两个位置分别前往$(4,n),(1,n)$。其中第二三行存在$k$个障碍物，求如何放这 $k$ 个障碍物，使得你走的每一条对应的路的路程相等。

思路：直接构造答案。观察样例，我们发现障碍物为偶数个时，只要把他们放在一起，构造成一个宽度两行的矩形即可。奇数个时，看做有 $k-1+1$ 个障碍物，即先构造一个 $k+1$ 的上述矩形然后从中间挖掉一个。注意如果在左右边界挖不行，这点可以画图看出。根据上述分析，显然一定有解，直接输出 $YES$ 即可。

下面是 $AC$ 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define mod 998244353
#define db(x) cout << x << endl; 
#define eps 0.0001
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	int n,k;
	cin >> n >> k;
	cout << "YES\n";
	for(int i=1;i<=n;i++)
		cout << ".";//第一行，输出.
	if(k%2==0)//偶数情况构造矩形
	{
		cout << endl << ".";
		for(int i=2;i<2+k/2;i++)
			cout << "#";
		for(int i=2+k/2;i<=n;i++)
			cout << ".";
		cout << "\n.";
		for(int i=2;i<2+k/2;i++)
			cout << "#";
		for(int i=2+k/2;i<=n;i++)
			cout << ".";
		cout << endl;
	}
	else
	{
		cout << endl;
		char a[2][100];
		memset(a,'.',sizeof(a));//先全部放.
		int pos = n/2+1;//找到中心位置
		a[0][pos] = '#';
		for(int i=1;i<=pos-2&&k>1;i++)//从中心向两个扩展放#
			a[0][pos-i] = a[0][pos+i] = '#',k-=2; 
		for(int i=1;i<=pos-2&&k>1;i++)
			a[1][pos-i] = a[1][pos+i] = '#',k-=2; 
		for(int i=0;i<=1;i++)
		{
			for(int j=1;j<=n;j++)
				cout << a[i][j];
			cout <<endl;//输出二三行
		}
	}
	for(int i=1;i<=n;i++)
		cout << ".";
	return 0;
}
```


---

