# Gregor and the Pawn Game

## 题目描述

There is a chessboard of size $ n $ by $ n $ . The square in the $ i $ -th row from top and $ j $ -th column from the left is labelled $ (i,j) $ .

Currently, Gregor has some pawns in the $ n $ -th row. There are also enemy pawns in the $ 1 $ -st row. On one turn, Gregor moves one of his pawns. A pawn can move one square up (from $ (i,j) $ to $ (i-1,j) $ ) if there is no pawn in the destination square. Additionally, a pawn can move one square diagonally up (from $ (i,j) $ to either $ (i-1,j-1) $ or $ (i-1,j+1) $ ) if and only if there is an enemy pawn in that square. The enemy pawn is also removed.

Gregor wants to know what is the maximum number of his pawns that can reach row $ 1 $ ?

Note that only Gregor takes turns in this game, and the enemy pawns never move. Also, when Gregor's pawn reaches row $ 1 $ , it is stuck and cannot make any further moves.

## 说明/提示

In the first example, Gregor can simply advance all $ 3 $ of his pawns forward. Thus, the answer is $ 3 $ .

In the second example, Gregor can guarantee that all $ 4 $ of his pawns reach the enemy row, by following the colored paths as demonstrated in the diagram below. Remember, only Gregor takes turns in this "game"!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1549B/eb2df5f00e8c7d1290d3251e314fd1200ad28d29.png)In the third example, Gregor's only pawn is stuck behind the enemy pawn, and cannot reach the end.

In the fourth example, Gregor has no pawns, so the answer is clearly $ 0 $ .

## 样例 #1

### 输入

```
4
3
000
111
4
1111
1111
3
010
010
5
11001
00000```

### 输出

```
3
4
0
0```

# 题解

## 作者：XL4453 (赞：3)

### 解题思路：

考虑贪心，从左向右枚举棋子，对于当前的一个棋子若能向前移动到顶就移动到顶，否则若左边有敌方棋子就向左，最后考虑右边有敌方棋子则向右移动。

----
然后考虑如何保证这样的一个贪心的正确性：

对于第一种情况，当前行的空地只有当前行的能利用，所以直接考虑向前移动。

第二种，由于是从左往右枚举，则一旦过了这一格就再也没有棋子能利用这一格了，所以也直接利用。

第三种，这一种情况有可能占用到右边的第二个棋子的向左移动方案。但我们发现，假如向右移动不进行，若这时右边有棋子，那么这样的一个位置也只能提供 1 的价值，和直接向右移动无异，但如果右边没有棋子就不是最优方案了，考虑到以一定不会比不移劣，所以在贪心的时候可以直接选择移动。

----------
### 代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int T,n,a[200005],b[200005],ans;
int main(){
	scanf("%d",&T);
	while(T--){
		ans=0;
		scanf("%d",&n);
		a[0]=b[0]=a[n+1]=b[n+1]=0;
		for(int i=1;i<=n;i++)scanf("%1d",&a[i]);
		for(int i=1;i<=n;i++)scanf("%1d",&b[i]);
		for(int i=1;i<=n;i++)
		if(b[i]){
			if(a[i]==0)ans++;
			else
			if(a[i-1]==1)a[i-1]=2,ans++;
			else
			if(a[i+1]==1)a[i+1]=2,ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：nalemy (赞：2)

首先可以肯定，Gregor 的棋子在最后 $n-2$ 行的所有格子都只能向前走，所以我们假设 Gregor 的棋子一开始就在第二行。按照题意，它们现在有三种选择：

- 如果左前方有敌人棋子，可以走到左前方
- 如果右前方有敌人棋子，可以走到右前方
- 如果正前方无敌人棋子，可以走到正前方

我们考虑贪心。从左往右枚举每颗 Gregor 的棋子，能往左前方走就往左前方走，否则能往正前方走就往正前方走，实在不行才往右前方走。

我们发现有这么一个事实，如果一个棋子可以往前走，那么只有它可以到达它前面的位置。

至于证明贪心的正确性，我们得从贪心的条件**无后效性**入手。我们采用类似数学归纳法的思路：

考虑左边第一颗棋子，易得按照这种方法走，肯定能达到当前的局部最优。

考虑其他情况，我们假设它左边所有的棋子都能够通过这种走法达到最优，那么这颗棋子分两种情况:

1. 它有地可走，那么全局肯定是最优的
2. 它无地可走。如果它本来就无地可走，那无关紧要。否则的话，只能是因为自己正前方和右前方都走不了，左前方还被棋子占了。而占领这格的棋子一定是“迫不得已”才向右前方走来到这里的，因此，如果这颗棋子不走这里，那么必定会有一颗棋子不能到达。所以此时依然是全局最优解。

代码：

```C++
#include<iostream>
#include<cstring>
#define N 200000
using namespace std;

bool mch[N];
int main() {
    int t, n, cnt; string a, b; cin >> t;
    while (t--) {
        cin >> n >> a >> b, memset(mch, cnt=0, sizeof(mch));
        for (int i=0; i<n; i++) if (b[i] - 48) {
            if (i && !mch[i-1] && a[i-1] == '1') mch[i-1] = true, cnt++;
            else if (!mch[i] && a[i] == '0') mch[i] = true, cnt++;
            else if (!mch[i+1] && a[i+1] == '1') mch[i+1] = true, cnt++;
        }
        cout << cnt << '\n';
    }
    return 0;
}
```



---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1549B)

显然的贪心题。

**贪心思路**：

对于每个棋子：

- $1$. 若能向前移动就向前，直到不能继续向前；

- $2$. 若左边有敌方棋子就向左；

- $3$. 若右边有敌方棋子则向右。

优先级由 $1$ 至 $3$。

**正确性：**

$1$ 和 $2$ 的正确性显然；

对于 $3:$ 

- 若右边那一列有棋子，那么这种方案会阻止右边那一列的棋子向左移动，这时右边向左或左边向右都是一样的；

- 若右边那一列无棋子，那么向右移动会比不移动更优。

所以此贪心是正确的，时间复杂度 $O(N)$。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
	cin>>t;
	while(t--){
		int cnt=0,n;//多测要清空
		string str1,str2;
		cin>>n>>str1>>str2;
		for(int i=1;i<=n;i++){
			if(str2[i-1]=='1'&&str1[i-1]=='0')){
				cnt++;//向上
			}else if(str2[i-1]=='1'&&str1[i-2]=='1'){
			    cnt++;//向左
			}else if(str2[i-1]=='1'&&str1[i]=='1'){
				cnt++;//向右
				str1[i]='2';//更新
			}
		}
		cout<<cnt<<"\n";
	}
	return 0;
}
```


---

## 作者：ttq012 (赞：0)

这道题是一个模拟题，同时也要采用贪心的思想。

首先将棋盘中间的 $2\sim n-1$ 行删掉，缩成一个 $2\times n$ 的长方形棋盘。

移动的方式是很关键的。

我们可以从最左边的我方棋子开始枚举，一直枚举到最右边的我方棋子。

为了不影响右边的我方棋子，首先要判断左上角是否有敌方的棋子，如果有就走到那一个格子。

如果正前方没有任何棋子，那么移动正前方。

如果右上角有敌方的棋子，那么就走到那一个格子。

否则无法移动到第一行，就不管了。

移动后的棋子用字符 `2` 来表示

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T --)
    {
        int n, cnt = 0;
        scanf ("%d", &n);
        string s, t;
        cin >> s >> t;
        for (int i = 0; i < n; i ++)
            if (t[i] == '1')
                if (s[i - 1] == '1')
                    cnt ++, s[i - 1] = '2';
                else if (s[i + 1] == '1')
                    cnt ++, s[i + 1] = '2';
                else if (s[i] == '0')
                    cnt ++, s[i] = '2';
        printf ("%d\n", cnt);
    }
    return 0;
}

```


---

## 作者：Forever1507 (赞：0)

首先易证把所有的我方士兵挪至第二行对答案无影响，考虑贪心，若前方无士兵，则向前走且只能向前走，否则优先往左，其次往右。

关于正确性：

如果一个棋子可以到达前方，那么**只有它可以到前方，不去就浪费**，否则，如果能往左上角走，因为顺序枚举，一定不会影响到左边棋子的行动，右边棋子也鞭长莫及。如果向右上角走，反正右边的棋子此时也不能向左，右边两个的棋就算不能向右两个棋谁走到这里也没有影响，何乐而不为？

综上，贪心正确性显然。
```
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s1,s2;
int ans1[200005],ans2[200005];
bool vis[200005];
int main(){
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));//多测不清空，保龄两行泪
		cin>>n;
		cin>>s1>>s2;
		int num=0;
		for(int i=1;i<=n;i++){
			ans1[i]=s1[i-1]-'0';
			ans2[i]=s2[i-1]-'0';
		}
		for(int i=1;i<=n;i++){
			if(ans1[i]==0&&!vis[i]&&ans2[i]==1){
				num++;
				vis[i]=1;
			}
			else if(i!=1&&ans1[i-1]==1&&ans1[i]==1&&!vis[i-1]&&ans2[i]==1){
				num++;
				vis[i-1]=1;//被友军走了
			} 
            /*
            当然，第一个和最后一个因为地理原因要特殊考虑
            */
			else if(i!=n&&ans1[i+1]==1&&ans1[i]==1&&!vis[i+1]&&ans2[i]==1){
				num++;
				vis[i+1]=1;
			}
		}
		cout<<num<<'\n';
	} 
	return 0;
}

```


---

## 作者：qinyihao (赞：0)

### Hint 1
Gregor 的每个棋子可以下到的格子数量非常有限。

### Hint 2
确定一个贪心算法来最大化答案。

### Solution

由于只有一排敌方棋子，而且这些棋子从不移动，所以只有 $3$ 个可能的列， Gregor 的一个棋子可以在其中结束。

我们可以使用贪心算法解决这个问题，从第 $1$ 列到第 $N$ 列。在当前的第 $j$ 列，如果 Gregor 在这一列有一个卒，那么我们贪婪地考虑3种情况:
- 如果第 $j - 1$ 列有一个未被吃掉的敌方棋子，就把这个棋子标记为被吃掉，然后增加答案。第 $ j - 1$ 列将永远不会再被调整，所以这个决定是最佳的。
- 如果第 $j$ 列中没有卒，就把 Gregor 的卒往前移，然后增加答案。
- 如果第 $j + 1$ 列有一个未被吃掉的敌方棋子，就把这个棋子标记为被吃掉，并递增答案。

否则，这个卒子将不会到达第一行。

这个贪心算法可以保证产生最大的答案。

其时间复杂度为 $O(N)$ 。

[code](https://www.luogu.com.cn/paste/uvocb0t3)

---

## 作者：MikeC (赞：0)


 ## 分析

首先，显然对于 $n\ge 3$ 的情况，第 $2$ 行到第 $n-1$ 行可以忽略，故我们只需要考虑一个 $2\times n$ 的棋盘。

对于位于 $(i,j)$ 的白棋（己方），我们有 $3$ 种移动的方案：

- 当左上方即 $(i-1,j-1)$ 有黑棋时，可以向左上方即 $(i-1,j-1)$ 移动。
- 当正上方即 $(i-1,j)$ 没有黑棋时，可以向正上方即 $(i-1,j)$ 移动。
- 当右上方即 $(i-1,j+1)$ 有黑棋时，可以向右上方即 $(i-1,j+1)$ 移动。 

观察三种方案可以发现，向左上方或正上方移动显然不会影响位于 $(i,j+1)$ 至位于 $(i,n)$ 的所有白棋的移动，而向右上方移动会影响位于 $(i,j+1)$ 的白棋向左上方移动。至此我们得到了一个贪心方案：尽量向左上方或正上方移动。

多测记得清空数组，时间复杂度 $O(n)$。

## 代码

``````cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[200001],b[200001];
signed main(){
    scanf("%d",&t);
    while(t--){
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%1d",&a[i]);
        for(int i=1;i<=n;i++)scanf("%1d",&b[i]);
        int ans=0;
            for(int i=1;i<=n;i++){
                if(!b[i])continue;
                if(a[i]==0){
                    ans++;continue;
                }
                if(a[i-1]==1){
                    a[i-1]=2;
                    ans++;
                    continue;
                }if(a[i+1]==1){
                    a[i+1]=2;
                    ans++;
                    continue;
                }
            }
        printf("%d\n",ans);
    }
}
``````



---

## 作者：jiangtaizhe001 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/15106264.html)
## 题目大意
一个 $n\times n$ 的棋盘上有一些国际象棋的兵，一端是我方的，另一端是敌方的，用两个 01 串表示这个位置上是否有兵。假设敌方的棋子不懂，问我方棋子最多能到达对面一端的个数。其中国际象棋的兵可以直线前进或者吃掉斜前方的敌方棋子并且走上去，两个棋子不能在同一位置。
## 题目解析
首先考虑是否可以贪心。  
答案是可以的。我们从左到右考虑每一个我方的棋子，我们发现，如果棋子能尽量往左放就对后面的棋子影响最小，所以贪心策略就是尽量把棋子相左放。

代码：
```cpp
#include<cstdio>
#define maxn 200039
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
//#define debug
typedef int Type;
inline Type read(){
	Type sum=0;
	int flag=0;
	char c=getchar();
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') c=getchar(),flag=1;
	while('0'<=c&&c<='9'){
		sum=(sum<<1)+(sum<<3)+(c^48);
		c=getchar();
	}
	if(flag) return -sum;
	return sum;
}
int n,T,ans;
char a[maxn],b[maxn];
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
    T=read();
    while(T--){
    	n=read(); ans=0;
    	scanf("%s%s",a+1,b+1);
    	for(int i=1;i<=n;i++){
    		if(a[i-1]=='1'&&b[i]=='1'){
    			a[i-1]='2';
    			b[i]='0'; ans++;
			}
			if(a[i]=='0'&&b[i]=='1'){
				a[i]='2'; ans++;
				b[i]='0'; 
			}
			if(a[i+1]=='1'&&b[i]=='1'){
				a[i+1]='2';
    			b[i]='0'; ans++;
			}
		}
		printf("%d\n",ans);	
	}
	return 0;
}

```

---

## 作者：phil071128 (赞：0)

## 2021.8.1 CodeForces Div.2 B题

#### 题目大意:
给定一个 $N\times N$ 的棋盘，第一行有若干个敌方棋子，第 $N$ 行有若干个己方的棋子，敌方棋子**不可移动**，己方棋子有两种前进方式，求最多能有多少个己方棋子到达第一行。


### 对于一个坐标为 $(i,j)$ 的己方棋子，前进规则如下：

- 如果正上方上一格 $(i+1,j)$ **没有棋子**，则可以直接向正上方前进一格。

- 如果**左上方**一格 $(i+1,j-1)$ 或**右上方**一格 $(i+1,j+1)$ 有**对方**的棋子，则可以跳到左上方或右上方并**吃掉**对手的棋子。



## Solution

- **模拟**即可

- 首先我们可以直接**忽略**第 $2$ 行至 $n-1$ 行，因为敌方棋子不可移动且都在第 $1$ 行，中间这些部分都只能向上走一格，所以**只需要开两个一维数组**即可。


- 如果第 $i$ 列**没有敌方棋子**，则第 $i$ 列的己方棋子可以一路北上到第 $1$ 行。

- 如果第 $i-1$ 列**有敌方棋子**，则第 $i$ 列的己方棋子可以一路北上到第 $2$ 行再跳到左上方并吃掉敌方棋子。

- 如果第 $i+1$ 列**有敌方棋子**，则第 $i$ 列的己方棋子可以一路北上到第 $2$ 行再跳到右上方并吃掉敌方棋子。

- 计数器累加即可。

- 注意:
	1. 只有第 $i$ 列**有己方棋子**才可以进行上面这三种操作。
   2. 一枚棋子只可以到 $i-1$ ，$i$ ，$ i+1$ 这三处的其中之一，**不要重复计算**。
   3. 多次询问，数组不要忘了**初始化**。

## Node
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
bool a[N],b[N];
int main(){
	int T;
	cin>>T;
	int n;
	char x;
	int ans=0;
	while(T--){
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			a[i]=x-'0';
		}
		for(int i=1;i<=n;i++){
			cin>>x;
			b[i]=x-'0';
		}
		for(int i=1;i<=n;i++){
			if(a[i]==0&&b[i]==1){
				ans++;
			}else if(b[i]==1){
				if(a[i-1]==1){
					a[i-1]=0;
					ans++;
				}else if(a[i+1]==1){
					a[i+1]=0;
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```



---

## 作者：Xhesika_Frost (赞：0)

 首先观察一下题意，黑的是不会动的，白的要不斜着吃黑的，要不直行，那么除了第一行和最后一行，剩下的部分对于这个题是没有影响的。

考虑这两行，贪心地考虑，对于每一个白棋，它的选择对于后面要尽可能的小，那么如果它的正前方为空或者左上方为黑，那么往前走和吃都是没有影响的，而如果右上方可以吃的话，那么吃了它答案不会更差。
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int t;
int n;
char a[300001],b[300001];
int main(){
	scanf("%d",&t);
	while(t--){
		int tem=0;
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			cin>>a[i];
			a[i]-='0';
		}
		for(int i=1;i<=n;++i){
			cin>>b[i];
			b[i]-='0';
		}
		int ans=0;
		for(int i=1;i<=n;++i){
			if(b[i]==0) continue;
			if(a[i]==0) ans++;
			else{
				if(a[i-1]==1) ans++;
				else{
					if(i!=n&&a[i+1]==1){
						a[i+1]=2;
						ans++;
					}
				}
			}
		}
		tem=ans;
		cout<<tem<<endl;
	}
	return 0;
}
```

---

## 作者：Retired_lvmao (赞：0)

### 题意

在一个 $n\times n$ 的国际象棋棋盘上，第 $1$ 行有一些你的兵，第 $n$ 行有一些对手的兵，求你能走到终点的棋子数量。

### 题解

考虑贪心。当第 $n$ 行的第 $i$ 列有棋子时，可以优先考虑匹配第 $1$ 行第 $i-1$ 列的棋子，如果匹配上答案一定更优；如果无法匹配，可以考虑匹配 $i+1$ 列的棋子，答案一定不劣；如果这一格没有棋子，直接尝试匹配 $i$ 列的棋子即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
char s[200010],t[200010];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		scanf("%s",s+1);
		scanf("%s",t+1);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(s[i]=='0'&&t[i]=='1')
			{
				ans++;
				t[i]='0';
			}
			else if(s[i]=='1')
			{
				if(i>1&&t[i-1]=='1')
				{
					ans++;
					t[i-1]='0';
				}
				else if(i<n&&t[i+1]=='1')
				{
					ans++;
					t[i+1]='0';
				}
			}
		}
		printf("%d\n",ans);
	}
}
```

---

