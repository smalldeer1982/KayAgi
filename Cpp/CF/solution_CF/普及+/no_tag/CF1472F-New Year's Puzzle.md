# New Year's Puzzle

## 题目描述

Every year Santa Claus gives gifts to all children. However, each country has its own traditions, and this process takes place in different ways. For example, in Berland you need to solve the New Year's puzzle.

Polycarp got the following problem: given a grid strip of size $ 2 \times n $ , some cells of it are blocked. You need to check if it is possible to tile all free cells using the $ 2 \times 1 $ and $ 1 \times 2 $ tiles (dominoes).

For example, if $ n = 5 $ and the strip looks like this (black cells are blocked):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/b41649f0d0bdba5578287fa746baff1e8a9677b4.png)Then it can be tiled, for example, using two vertical and two horizontal tiles, as in the picture below (different tiles are marked by different colors).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/f3eba115e4f25b885841d9adf40142fd3358cffa.png)And if $ n = 3 $ and the strip looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/1bfdaad6e61d408b265451fa0ae69099925aea09.png)It is impossible to tile free cells.

Polycarp easily solved this task and received his New Year's gift. Can you solve it?

## 说明/提示

The first two test cases are explained in the statement.

In the third test case the strip looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1472F/fb18b851c5e691e6cc3d6920785bdb0ec1abf74e.png) It is easy to check that the unblocked squares on it can not be tiled.

## 样例 #1

### 输入

```
3

5 2
2 2
1 4

3 2
2 1
2 3

6 4
2 1
2 3
2 4
2 6```

### 输出

```
YES
NO
NO```

# 题解

## 作者：OMG_wc (赞：7)

对每列而言有四种情况：

1. 没封锁
2. 都封锁
3. 封锁上面
4. 封锁下面

如果只存在前两种情况，那肯定是能放下的，只要都竖着放就行了。也就是说，我们会尽可能地竖着放，直到遇到某个封锁 **单个格子** 的列。

一旦遇到 3、4 情况之一，显然就要横着放了，然后下一列也会受到影响必须横着放，下下列也是.....

这样，如果直到结束都没遇到下个有封锁的列，肯定是不合法的。

如果下一个有封锁的列是情况 2，也是不合法的。

记当前列封锁格子的 行号+列号 为 $T$，唯一合法的情况是下一个封锁列只封一个格子，并且该格子的 行号加列号 的奇偶性和 $T$ 不同。

然后这列以后又可以竖着放了........直到再次遇到3、4 情况之一。

用`map`写起来很简单，代码如下：

```c++
int main() {
    int _;
    cin >> _;
    while (_--) {
        int n, m;
        cin >> n >> m;
        map<int, int> mp;
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            mp[y] += x;
        }
        int ok = 1, last = -1;
        for (auto t : mp) {
            if (last == -1) {
                if (t.second != 3)
                    last = t.first + t.second;
            } else {
                if (t.second == 3) {
                    ok = 0;
                    break;
                }
                if ((last + t.first + t.second) % 2 == 0) {
                    ok = 0;
                    break;
                }
                last = -1;
            }
        }
        if (last != -1) ok = 0;
        puts(ok ? "YES" : "NO");
    }
    return 0;
}
```



---

## 作者：二gou子 (赞：3)

原题题目标签带着一些奇奇怪怪的东西。。。又有$dp$又有图论，但是其实是个贪心~~水题~~。

## 思路
其实这个题可以用分治的思想来做。首先我们想，对于一个已经被覆盖的方格，肯定要有一个方格跟它匹配，因为奇数个格子肯定是不可能填满的。那么我们就考虑这两个格子。手玩一下就可以知道，有两种情况：$1.$两个格子不在同一行，那么我们发现有一个格子上面或者下面有一个空格，此时我们必须把它填起来，也就是横着放一个。放完这一个之后，又多出来一个单独的空格，此时我们又要横着放一个。。。以此类推，最后可以得出一个关于奇偶性的结论。第二种情况同理，在此不再赘述。

填完了两个，我们可以发现，以这两个格子的连线为顶点的矩形正好被涂满，那也就可以看成放了$n$个面积为$2$的矩形，再处理下一对即可。

但是别忘了有一种特殊情况：假设找到了第一个格$c1$，第二个格$c2$，然后它们满足奇偶性合法。**但是，如果有一个格和$c2$在同一列，那么显然，你不能填起来这个大长方形，因为有奇数个点需要你填**。所以此时特判一下不合法即可。

具体实现就是加一步排序，然后如上操作即可。

## Code
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=200005;
int T,n,m;
bool flag;
struct Node{
	int x,y;
}po[N];
bool cmp(Node a,Node b){
	return a.y<b.y;
}
int main()
{
	scanf("%d",&T);
	while(T--){
		flag=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			scanf("%d%d",&po[i].x,&po[i].y);
		}
		if(m%2==1){
			printf("NO\n");
			continue;
		}
//		if(m==n*2){
//			printf("NO\n");
//			continue;
//		}
		sort(po+1,po+1+m,cmp);
		po[m+1].y=0,po[m+1].x=0;//这一行是万恶之源，耗费了我一个小时的时间。主要原因就是因为我要用到m+1，但是上一次的m+1没有清空，所以可能会导致错误答案。
//		for(int i=1;i<=m;i++){
//			printf("%d ",po[i].x);
//		}
//		printf("\n");
		
		for(int i=1;i<=m;i+=2){
			if(po[i].x==po[i+1].x){
				if((po[i+1].y-po[i].y-1)%2==1){
					flag=1;
					break;
				}
				if(po[i+1].y==po[i+2].y){
					flag=1;
					break;
				}
			}
			if(po[i].x!=po[i+1].x){
				if((po[i+1].y-po[i].y-1)%2==0){
					flag=1;
					break;
				}
				if(po[i+1].y==po[i+2].y){
					flag=1;
					break;
				}
			}
		}
		if(flag==1){
			printf("NO\n");
			continue;
		}
		else{
			printf("YES\n");
		}
	}
	return 0;
}
```

---

## 作者：胖头鱼学员 (赞：2)

# CF1472F

[CF传送门](http://codeforces.com/problemset/problem/1472/F)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1472F)

## $QuestionMeaning$

给定一个$2 \times n$的方格正方形，其中有$m$个被挡住了，问能不能用$1 \times 2$或$2 \times 1$的纸片只覆盖住没有被挡住的地方。

## $Solution$

分类讨论：

（注：一下所有被遮盖的为黑色，没有被覆盖的为白色）

### 1. 上下异色

首先是上下两行只有一个被遮盖的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/o7u8i673.png)

那么我们为了覆盖$(1,2)$的这个点，只能将$1 \times 2$的纸片放在$(1,2)$和$(2,2)$这两个块：

![](https://cdn.luogu.com.cn/upload/image_hosting/d2e77lih.png)

那么现在又为了覆盖$(2,1)$的这个点，只能将$1 \times 2$的纸片放在$(1,2)$和$(3,1)$这两个块：

![](https://cdn.luogu.com.cn/upload/image_hosting/lefov5zs.png)

反复如此即可。

之后会发现其实这种情况与两个方格的距离和所在行有关，即若为同一行，那么距离为偶数即可；若不是同一行，那么距离为奇数即可。

### 2. 上下同色

若上下两行皆被覆盖：

![](https://cdn.luogu.com.cn/upload/image_hosting/mfoyfy2n.png)

其实$(4,1)$和$(4,2)$都是被覆盖的，那么就是这两个点将这一个长方形一分为二：

![](https://cdn.luogu.com.cn/upload/image_hosting/i2b7jpkd.png)

再分开处理即可。

### 3. 上下无色

不讲，直接覆盖即可。

## $Code$
```
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 2;

struct E {
  int r, c;
  bool operator<(const E &e) const {
    return c < e.c;
  }
} e[kMaxN];

int t, n, l;

void M() {
  int m = 0;
  for (int i = 1; i <= n; i++) {
    if (e[i].c != e[m].c) {
      e[++m] = e[i];
    } else {
      e[m].r |= e[i].r;
    }
  }
  n = m;
}

bool C() {
  bool b = 1;
  for (int i = 1, s = 3; i <= n; i++) {
    if (s == 3) {
      s = e[i].r;
    } else {
      b &= e[i].r != 3 && (e[i].r != s) ^ ((e[i].c - e[i - 1].c) & 1);
      s = 3;
    }
  }
  return b;
}

int main() {
  cin >> t;
  while (t--) {
    cin >> l >> n;
    for (int i = 1; i <= n; i++) {
      cin >> e[i].r >> e[i].c;
    }
    e[++n] = {3, l + 1};
    sort(e + 1, e + 1 + n);
    M();
    cout << (C() ? "YES" : "NO") << endl;
  }
  return 0;
}

```

---

## 作者：Super_Builder (赞：1)

## 前言

只要题目给了图，你就要画图。

## 思路

首先，我们要明确一点：一个矩形，如果里面不存在任何被覆盖的方格，那么这个矩形是绝对可以被覆盖的。

如果现在有一个点被覆盖了。

[![pFmwFzR.png](https://s11.ax1x.com/2024/01/25/pFmwFzR.png)](https://imgse.com/i/pFmwFzR)

那么必定要有一个长方形从这个点下方往后。

然后继续在上方接长方形继续往后。

[![pFmw1SA.md.png](https://s11.ax1x.com/2024/01/25/pFmw1SA.md.png)](https://imgse.com/i/pFmw1SA)

直到出现了一个新节点被覆盖。

假设在新节点的上一个点之前，都是可以被完全覆盖的。

### 如果在同一行。

- 两个点之间的距离为偶数，那么这之间肯定可以被盖住。然后继续往后找。

[![pFmw5lR.md.png](https://s11.ax1x.com/2024/01/25/pFmw5lR.md.png)](https://imgse.com/i/pFmw5lR)

- 如果为奇数，稍加思考，可以证明这一段是不能被完全盖住的，直接跳出，无解。

### 接下来考虑不在同一行。

- 两个点之间的距离为奇数，那么这之间一定可以被完全盖住。

[![pFm0KBV.md.png](https://s11.ax1x.com/2024/01/25/pFm0KBV.md.png)](https://imgse.com/i/pFm0KBV)

- 两个点之间的距离为偶数，思考一下，能证明不能被完全盖住，跳出，无解。

- 两个点在同一列，如果前面还有点未找到对应点，也无解。

如果前面不能被完全盖住，那么会提前跳出，所以如果能到这里，那么前面一定合法。

最后，如果上一个点之后没有找到对应的下一个点，也无解。

在代码实现中，注意我们要将点排序。接着用一个变量记录前面是否还有未处理完的点，有则判断当前点与之前点是否合法，没有就把变量赋为 1，继续考虑下一个。

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct M{
	int x,y;
}a[200005];
inline bool cmp(M x,M y){
	return x.y<y.y;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		memset(a,0,sizeof a);
		for(int i=1;i<=m;i++){
			cin>>a[i].x>>a[i].y;
		}
		sort(a+1,a+m+1,cmp);
		bool ok=1,fg=0;
		for(int i=1;i<=m;i++){
			if(a[i].y==a[i+1].y){
				if(fg){
					ok=0;
					break;
				}
				i++;
			}
			else{
				if(fg){
					if(a[i-1].x==a[i].x){
						if((a[i].y-a[i-1].y-1)%2==0){
							fg=0;
						}
						else{
							ok=0;
							break;
						}
					}
					else{
						if((a[i].y-a[i-1].y-1)%2==1){
							fg=0;
						}
						else{
							ok=0;
							break;
						}
					}
				}
				else{
					fg=1;
				}
			}
		}
		if(!ok||fg)puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：GoldenFishX (赞：1)

### 时间复杂度:$O(tmlog(m))$
### 主要思路：贪心

1. $m$ 为奇数时，显然不行，排除（原因见下）

	![](https://cdn.luogu.com.cn/upload/image_hosting/kg1aowrk.png)

	这是一个点的情况，显然会无限延伸下去，**无论 $n$ 为多少，永远缺一个格子**。
   
   那三个点的情况呢？
   ![](https://cdn.luogu.com.cn/upload/image_hosting/eqffq3qw.png)
   可以发现，前面红框框住的一截是没有问题的，但后面又出现了这种情况。
   
   所以， $m$ 为奇数是必然会出现这种情况的，所以不可行。
   
1. 再来看红框框住的地方，可以发现，两个同行的黑块中间间隔的格子数是偶数
	
    那么显然**只要两个格子是同一行，并且中间间隔的格子数是偶数，这一截就一定可行**。(因为只能横着放，且长度为2，所以中间间隔的格子数必须是2的倍数)
    
   **还有一种特殊情况**
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/k9k14oat.png)
   
   这种情况显然是可行的，而且这种情况像上面这样判断也是可行的。
   
   但是，如果这种多米诺骨牌的长度为3时，这种情况是不可行的，但是如果用上面这种方式判断，这种方式是可行的 $(0\ \%\ 3 = 0)$
   
   所以，我们上面这种判断方法是**恰好**解决了这个问题。
    
1. 同一行要是偶数，那不是同一行呢？
	
   ![](https://cdn.luogu.com.cn/upload/image_hosting/7lij4964.png)
   
   如图，很显然，这种情况**中间的间隔的格子数要是奇数**就行了。
   
   **还有一种特殊情况**
   
   1.
	![](https://cdn.luogu.com.cn/upload/image_hosting/321hvcgn.png)
    
   这种情况显然可行，特批一下就行了。

1. 于是我们可以给这些黑块按照位置两两分组(首先按照位置排序)(如图)，判断每一组的可行性，只要有一组不可行整个就不可行。

	![](https://cdn.luogu.com.cn/upload/image_hosting/aqriwjge.png)
   
   虽然出现了红框中是不可行的，但它们不是一组，所以没有影响。
   
1. 但还有一个问题，会有两组重合的情况。(如图)
	
   ![](https://cdn.luogu.com.cn/upload/image_hosting/ptsfh303.png)
   
   这种情况显然不可行，可是每组却都是可行的，所以需要特判。
   

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
struct Node{
  int x1, x2;
}a[MAXN];
bool cmp(Node x, Node y) {
  return x.x2 < y.x2;
}
int mian() {
  int t;
  cin >> t;
  while(t--) {
    int n, m;
    bool ans = 1;
    cin >> n >> m;
    for(int i = 0; i < m; i ++) {
      cin >> a[i].x1 >> a[i].x2;
    }
    if(m % 2 == 1) { //m为奇数的情况
      ans = 0;
    }
    sort(a, a + m, cmp);
    for(int i = 1; i < m; i += 2) {
      Node last = a[i - 1];
      if(!(a[i].x1 != last.x1 && a[i].x2 == last.x2)) { //可行的特殊情况
        if(a[i].x1 == last.x1 && (a[i].x2 - last.x2 - 1) % 2 != 0) { 			//同行
          ans = 0;
          break;
        } else if(a[i].x1 != last.x1 && (a[i].x2 - last.x2 - 1) % 2 == 0) { 		//异行
          ans = 0;
          break;
        } else if(i + 1 < m && a[i + 1].x2 == a[i].x2 && a[i + 1].x1 != a[i].x1) { 	//重合
          ans = 0;
          break;
        }
      }
    }
    if(ans) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
} 
```

代码仅供参考，切勿抄袭

---

## 作者：lfxxx (赞：0)

首先 $O(n)$ 的 dp 是简单的，考虑状压上一列填的状态即可。

下文全空列表示这一列没有障碍，非空列表示这一列存在至少一个障碍。

然后你发现假若填的方案中全空列填竖直的或者对齐的两个横的，则可以直接删去全空列，若填两个刚好错一位的横的则只关心全空列是否存在以及奇偶性，按照这个原则将两个非空列之间补充一些全空列再舍弃原序列点全空列则可以做到 $O(m)$。

[代码](https://codeforces.com/contest/1472/submission/280480243)

---

## 作者：pzc2004 (赞：0)

提供一种比较暴力且无脑的做法。
# 题目分析
可以发现如果n比较小我们就可以直接 $O(N)$ 的去DP，具体方法为用 $f_{i,j}$ 表示第 $i$ 行之前全部涂满，第 $i$ 行的状态为 $j$ 的可行性，其中0表示全部涂满，1表示涂第一个格子，2表示涂第二个格子，然后就可以根据当前行的黑格子转移了，如果最后一列可以涂满就输出YES，否则输出NO。  
然后我们发现这题m的范围比较小，这启发我们根据黑点构造一个列数较小的新图。根据画图可以发现，两个列数差不小于2的黑格子可以被每次压缩2个格子，直到列数差小于等于2，但是再往下压缩就会出问题，还要注意处理一下第一列和最后一列。  
看图理解一下：
![](https://cdn.luogu.com.cn/upload/image_hosting/mzzd90gt.png)压缩为
![](https://cdn.luogu.com.cn/upload/image_hosting/9s6x3rdz.png)  
![](https://cdn.luogu.com.cn/upload/image_hosting/tu85379k.png)压缩为
![](https://cdn.luogu.com.cn/upload/image_hosting/co348llr.png)
这样压缩后新图的列数最多为2*m，就可以愉快AC了。
代码：
``` cpp
#include <bits/stdc++.h>
using namespace std;
template <class T>
inline void read(T &x)
{
	x= 0;
	char c= getchar();
	while(!isdigit(c)) c= getchar();
	while(isdigit(c)) x= x * 10 + (c & 15), c= getchar();
}
#define N 200005
int n, m, ma;
bool bb[N << 1][2], f[N << 1][3];
struct Block
{
	int x, y;
	inline Block(int x= 0, int y= 0) : x(x), y(y) {}
} a[N], b[N];
inline bool cmp(const Block &a, const Block &b) { return a.y < b.y; }
signed main()
{
	int T;
	read(T);
	while(T--)
	{
		read(n), read(m);
		for(int i= 1; i <= m; i++) read(a[i].x), read(a[i].y);
		a[++m]= Block(3, 1), a[++m]= Block(3, n);//讲第一列和最后一列也加入，统一处理
		if(m & 1)
		{
			printf("NO\n");
			continue;
		}
		sort(a + 1, a + m + 1, cmp);//排序后对图进行压缩
		b[1]= a[1];
		for(int i= 2; i <= m; i++)
			if(a[i].y - a[i - 1].y > 2)
			{
				b[i].x= a[i].x;
				int x= (a[i].y - a[i - 1].y - 1) & 1;
				b[i].y= b[i - 1].y + x + 1;
			}
			else
			{
				b[i].x= a[i].x;
				int x= (a[i].y - a[i - 1].y - 1);
				b[i].y= b[i - 1].y + x + 1;
			}
		ma= b[m].y;
		memset(bb + 1, 0, 2 * ma), memset(f + 1, 0, 3 * ma);//DP初始化
		for(int i= 1; i <= m; i++)
			if(b[i].x < 3) bb[b[i].y][b[i].x - 1]= 1;
		f[0][0]= 1;
		for(int i= 1; i <= ma; i++)//DP
		{
			if(bb[i][0] && bb[i][1])
				f[i][0]= f[i - 1][0];
			else if(bb[i][0] && !bb[i][1])
				f[i][0]= f[i - 1][1], f[i][1]= f[i - 1][0];
			else if(!bb[i][0] && bb[i][1])
				f[i][0]= f[i - 1][2], f[i][2]= f[i - 1][0];
			else if(!bb[i][0] && !bb[i][1])
				f[i][0]= f[i - 1][0], f[i][1]= f[i - 1][2], f[i][2]= f[i - 1][1];
		}
		if(f[ma][0])
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```

---

## 作者：pengyule (赞：0)

最开始看到这题思路是状压 dp，后来看到 $n\le10^9$ 就知道应该是注意判断每个障碍。

用 $pre1,pre2$ 记录第一排、第二排最后一个 **不能放的位置（被堵住或已放过）** ，显然这个位置及其前面的部分都已经放满了。对于每一个障碍：
1. 如果它这一列是两个格子都堵了，就把两个障碍一起考虑。那么记这是第 $x$ 列，则 $(x-1-pre1)\bmod 2=(x-1-pre2)\bmod2$，含义就是在障碍所在的这一列前面的（不含）可以放骨牌的格子，第一排和第二排都可以恰好横着放满，或者都多出一个（最后一个），这时再竖着放一个就可以把 $1\sim (x-1) $ 列全部填满。凡是不能填满的，显然就是不可能成功了。在可以成功的情况下，把 $pre1$ 更新为 $x$，$pre2$ 也更新为 $x$。
2. 如果它这一列是只有一个格子被堵，我们假设是上面的格子被堵，下面的格子被堵的情况同理。现在要做的事情同样就是填满 $1\sim(x-1)$ 列。那么假如上面一排横着填到最后还差一个格子（最后一个），下面的刚好填完，上面的那个空出来的格子就无论如何也不能填起来，于是这种情况被判为失败。如果上面和下面都刚好填完，或者上面下面填完都还差一个格子（这时竖着放一个），那么把 $pre1=x,pre2=x-1$。如果上面的填满了，下面的还差最后一个格子，那么选择将一个骨牌横着放在下面的 $(x-1),x$ 位置，这时更新 $pre1=pre2=x$。

到此我们就将所有情况考虑完毕，这题唯一需要注意的地方就是我们最好不要让骨牌超过位置 $x$，相当于可以理解成一种无后效性吧。下面是 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
pair<int,int> a[200005];
int main()
{
	int T,n,m;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=m;i++) cin>>a[i].second>>a[i].first;
		a[++m]=make_pair(n+1,1); a[++m]=make_pair(n+1,2); //填到整个网格的末尾，虚拟出的 n+1 位置是不能填的，我们可以人为地添加两个障碍
		sort(a+1,a+m+1);
		int pre1=0,pre2=0,ans=1;
		for(int i=1;i<=m;i++){
			bool flag=true;
			if(i<m && a[i+1].first==a[i].first){
				if((a[i].first-1-pre1)%2!=(a[i].first-1-pre2)%2) flag=false;
				pre1=pre2=a[i].first; i++; 
			}
			else {
				if(a[i].second==1){
					if((a[i].first-1-pre2)%2==0 && (a[i].first-1-pre1)%2==1) flag=false;
					else if((a[i].first-1-pre2)%2==(a[i].first-1-pre1)%2) pre1=a[i].first,pre2=a[i].first-1;
					else pre1=pre2=a[i].first;
				}
				else {
					if((a[i].first-1-pre1)%2==0 && (a[i].first-1-pre2)%2==1) flag=false;
					else if((a[i].first-1-pre1)%2==(a[i].first-1-pre2)%2) pre1=a[i].first-1,pre2=a[i].first;
					else pre1=pre2=a[i].first;
				}
			}
			if(!flag){
				ans=0;
				break;
			}
		}
		if(ans) cout<<"YES"<<endl; else cout<<"NO"<<endl;
	}
	return 0;
} 
```

---

